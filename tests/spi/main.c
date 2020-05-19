/*H*****************************************************************************
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions
* are met:
*   - Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   - Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in
*     the documentation and/or other materials provided with the
*     distribution.
*   - Neither the name of ChipCraft Sp. z o.o. nor the names of its
*     contributors may be used to endorse or promote products derived
*     from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
* "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
* LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
* FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
* COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
* INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
* BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
* CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
* LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
* ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
* POSSIBILITY OF SUCH DAMAGE.
*
* ******************************************************************************
* File Name : main.c
* Author    : Maciej Plasota
* ******************************************************************************
* $Date: 2020-03-01 10:46:31 +0100 (nie, 01 mar 2020) $
* $Revision: 532 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-csr.h>
#include <ccproc-dcache.h>
#include <ccproc-icache.h>
#include <ccproc-amba.h>
#include <ccproc-amba-spi.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include "spi.h"
#include "dma.h"

#define TEST_CONTEXT_FMT " spi %d"
#define TEST_CONTEXT_VARS ,g_spi_index
#include "test.h"

#ifndef ARRAY_SIZE
    #define ARRAY_SIZE(a) (sizeof (a) / sizeof ((a)[0]))
#endif

static unsigned g_spi_index;
static volatile amba_spi_t *gp_spi = NULL;
static volatile amba_dma_channel_t *gp_chnlTx = NULL;
static volatile amba_dma_channel_t *gp_chnlRx = NULL;
static volatile bool g_irq_tx_in_progress = false;
static volatile bool g_irq_rx_in_progress = false;
static void (*interruptHandlerFunction)(uint32_t status) = NULL;
static void (*dmaInterruptHandlerFunction)(uint32_t statusTx, uint32_t statusRx) = NULL;
static const uint32_t g_data_to_send_array[] = {0xF32A57C5, 0x352A6F7B, 0xA4B673A1, 0x3A45CD21, 0x434CA51E};
static uint32_t g_data_received_array[ARRAY_SIZE(g_data_to_send_array)];

void isr5(void)
{
    if(gp_spi != NULL)
    {
        if(interruptHandlerFunction != NULL)
        {
            uint32_t status = spi_get_status(gp_spi);
            interruptHandlerFunction(status);
        }
    }
}

void isr1(void)
{
    uint32_t statusTx = 0;
    uint32_t statusRx = 0;
    if(gp_chnlTx != NULL)
    {
        statusTx = dma_get_status(gp_chnlTx);
    }
    if(gp_chnlRx != NULL)
    {
        statusRx = dma_get_status(gp_chnlRx);
    }
    if(dmaInterruptHandlerFunction != NULL)
    {
        dmaInterruptHandlerFunction(statusTx, statusRx);
    }
}

static uint32_t getValueForFrameLength(uint32_t value, amba_spi_flen_t frameLength)
{
    switch(frameLength)
    {
        case SPI_FLEN8:
        {
            value &= 0x00FF;
            break;
        }
        case SPI_FLEN16:
        {
            value &= 0x00FFFF;
            break;
        }
        case SPI_FLEN24:
        {
            value &= 0x00FFFFFF;
            break;
        }
        case SPI_FLEN32:
            break;
    }
    return value;
}

static void interruptHandler_OVR(uint32_t status)
{
    assertTrue(spi_status_is_transmission_complete(status));
    assertFalse(spi_status_is_transmitting(status));
    assertTrue(spi_status_is_data_received(status));
    assertTrue(spi_status_is_received_data_overran(status));
    assertTrue(spi_status_is_ready_for_data_to_send(status));
    g_data_received_array[0] = spi_get(gp_spi);
    g_irq_tx_in_progress = false;
}

static void interruptHandler_DMA(uint32_t statusTx, uint32_t statusRx)
{
    if(g_irq_tx_in_progress == true)
    {
        dma_disable_TCZ_interrupt(gp_chnlTx);
        assertTrue(dma_status_is_channel_active(statusRx));
        assertFalse(dma_status_is_transfer_counter_equ_0(statusRx));
        assertTrue(dma_status_is_counter_reload_equ_0(statusRx));
        assertFalse(dma_status_is_mem_address_reloaded(statusRx));

        assertFalse(dma_status_is_channel_active(statusTx));
        assertTrue(dma_status_is_transfer_counter_equ_0(statusTx));
        assertTrue(dma_status_is_counter_reload_equ_0(statusTx));
        assertFalse(dma_status_is_mem_address_reloaded(statusTx));
        g_irq_tx_in_progress = false;
    }
    else
    {
        dma_disable_TCZ_interrupt(gp_chnlRx);
        assertFalse(dma_status_is_channel_active(statusRx));
        assertTrue(dma_status_is_transfer_counter_equ_0(statusRx));
        assertTrue(dma_status_is_counter_reload_equ_0(statusRx));
        assertFalse(dma_status_is_mem_address_reloaded(statusRx));
        assertFalse(dma_status_is_channel_active(statusTx));
        assertTrue(dma_status_is_transfer_counter_equ_0(statusTx));
        assertTrue(dma_status_is_counter_reload_equ_0(statusTx));
        assertFalse(dma_status_is_mem_address_reloaded(statusTx));
        g_irq_rx_in_progress = false;
    }
}

static bool test_polling_scheme_operation_in_loopback_mode(int spi_index,
                                                           bool transmit_MSB_first,
                                                           uint32_t baud_rate,
                                                           amba_spi_mode_t spi_mode,
                                                           amba_spi_flen_t spi_frame_length,
                                                           const uint32_t * p_data_to_send_array,
                                                           uint32_t * p_data_received_array,
                                                           uint32_t array_size)
{
    bool returned_value;
    uint32_t status_reg;
    volatile amba_spi_t *p_spi = AMBA_SPI_PTR(spi_index);
    unsigned data_index;

    //printf("\nConfigure for POLLING operation test");
    //pre-test configuration
    spi_enable_master_mode(p_spi);
    spi_enable_loopback_mode(p_spi);
    returned_value = spi_set_baud_div(p_spi, baud_rate, PERIPH0_FREQ);
    if(transmit_MSB_first)
    {
        spi_transmit_data_MSB_first(p_spi);
    }
    else
    {
        spi_transmit_data_LSB_first(p_spi);
    }
    spi_set_transmission_mode(p_spi, spi_mode);
    spi_set_frame_length(p_spi, spi_frame_length);
    spi_disable_TXC_interrupt(p_spi);
    spi_disable_TDRE_interrupt(p_spi);
    spi_disable_RDRF_interrupt(p_spi);
    spi_disable_OVERRUN_interrupt(p_spi);
    spi_enable(p_spi);
    //verify configuration
    assertTrue(returned_value);
    assertEq(spi_get_status(p_spi), SPI_STAT_TDRE);
    assertEq(p_spi->IRQM, 0);
    assertEq(spi_get_mapping_of_interrupts(p_spi), 1 << 5);
    assertEq(spi_get_frame_length(p_spi), spi_frame_length);
    assertEq(spi_get_transmission_mode(p_spi), spi_mode);
    //test
    //printf("\nTesting POLLING operation");
    memset(p_data_received_array, 0, array_size * sizeof(uint32_t));
    //spi_put(p_spi, p_data_to_send_array[0]);
    spi_put(p_spi, p_data_to_send_array[0]);
    for(data_index = 1; data_index < array_size; data_index++)
    {
        do
        {
            status_reg = spi_get_status(p_spi);
            assertFalse(spi_status_is_transmission_complete(status_reg));
            assertTrue(spi_status_is_transmitting(status_reg));
            assertFalse(spi_status_is_data_received(status_reg));
            assertFalse(spi_status_is_received_data_overran(status_reg));
        }while (!spi_status_is_ready_for_data_to_send(status_reg)); // wait for TX data register empty
        spi_put(p_spi, p_data_to_send_array[data_index]);
        do
        {
            status_reg = spi_get_status(p_spi);
            assertTrue(spi_status_is_transmitting(status_reg));
            assertFalse(spi_status_is_transmission_complete(status_reg));
            assertFalse(spi_status_is_received_data_overran(status_reg));
        }while (!spi_status_is_data_received(status_reg)); // wait for transmission complete
        p_data_received_array[data_index - 1] = spi_get(p_spi);
    }
    do
    {
        status_reg = spi_get_status(p_spi);
        assertFalse(spi_status_is_received_data_overran(status_reg));
    }while (!spi_status_is_data_received(status_reg)); // wait for transmission complete
    assertTrue(spi_status_is_transmission_complete(status_reg));
    assertFalse(spi_status_is_transmitting(status_reg));
    assertTrue(spi_status_is_ready_for_data_to_send(status_reg));
    p_data_received_array[array_size - 1] = spi_get(p_spi);
    //compare received data
    for(data_index = 0; data_index < array_size; data_index++)
    {
        assertEq(getValueForFrameLength(p_data_to_send_array[data_index], spi_frame_length), p_data_received_array[data_index]);
    }

    //post-test clean up
    //printf("\nCleaning up after test");
    spi_disable_TXC_interrupt(p_spi);
    spi_disable_TDRE_interrupt(p_spi);
    spi_disable_RDRF_interrupt(p_spi);
    spi_disable_OVERRUN_interrupt(p_spi);
    spi_disable(p_spi);

    return returned_value;
}

static bool test_polling_scheme_overrun_condition(int spi_index,
                                                  bool transmit_MSB_first,
                                                  uint32_t baud_rate,
                                                  amba_spi_mode_t spi_mode,
                                                  amba_spi_flen_t spi_frame_length,
                                                  const uint32_t * p_data_to_send_array,
                                                  uint32_t * p_data_received_array,
                                                  uint32_t array_size)
{
    bool returned_value;
    uint32_t status_reg;
    volatile amba_spi_t *p_spi = AMBA_SPI_PTR(spi_index);

    //printf("\nConfigure for OVERRUN indication test");
    //pre-test configuration
    spi_enable_master_mode(p_spi);
    spi_enable_loopback_mode(p_spi);
    returned_value = spi_set_baud_div(p_spi, baud_rate, PERIPH0_FREQ);
    if(transmit_MSB_first)
    {
        spi_transmit_data_MSB_first(p_spi);
    }
    else
    {
        spi_transmit_data_LSB_first(p_spi);
    }
    spi_set_transmission_mode(p_spi, spi_mode);
    spi_set_frame_length(p_spi, spi_frame_length);
    spi_disable_TXC_interrupt(p_spi);
    spi_disable_TDRE_interrupt(p_spi);
    spi_disable_RDRF_interrupt(p_spi);
    spi_disable_OVERRUN_interrupt(p_spi);
    spi_enable(p_spi);
    //verify configuration
    assertTrue(returned_value);
    assertEq(spi_get_status(p_spi), SPI_STAT_TDRE);
    assertEq(p_spi->IRQM, 0);
    assertEq(spi_get_mapping_of_interrupts(p_spi), 1 << 5);
    assertEq(spi_get_frame_length(p_spi), spi_frame_length);
    assertEq(spi_get_transmission_mode(p_spi), spi_mode);
    //test
    //printf("\nTesting OVERRUN indication");
    memset(p_data_received_array, 0, array_size * sizeof(uint32_t));
    //spi_put(p_spi, p_data_to_send_array[0]);
    spi_put(p_spi, p_data_to_send_array[0]);
    do
    {
        status_reg = spi_get_status(p_spi);
        assertFalse(spi_status_is_transmission_complete(status_reg));
        assertTrue(spi_status_is_transmitting(status_reg));
        assertFalse(spi_status_is_data_received(status_reg));
        assertFalse(spi_status_is_received_data_overran(status_reg));
    }while (!spi_status_is_ready_for_data_to_send(status_reg)); // wait for TX data register empty
    spi_put(p_spi, p_data_to_send_array[1]);
    do
    {
        status_reg = spi_get_status(p_spi);
    }while (!spi_status_is_transmission_complete(status_reg)); // wait for transmission complete
    assertTrue(spi_status_is_received_data_overran(status_reg));
    assertTrue(spi_status_is_transmission_complete(status_reg));
    assertFalse(spi_status_is_transmitting(status_reg));
    assertTrue(spi_status_is_ready_for_data_to_send(status_reg));
    p_data_received_array[0] = spi_get(p_spi);
    //compare received data
    assertEq(getValueForFrameLength(p_data_to_send_array[1], spi_frame_length), p_data_received_array[0]);
    //check status again
    status_reg = spi_get_status(p_spi);
    assertFalse(spi_status_is_transmission_complete(status_reg));
    assertFalse(spi_status_is_transmitting(status_reg));
    assertFalse(spi_status_is_data_received(status_reg));
    assertFalse(spi_status_is_received_data_overran(status_reg));
    assertTrue(spi_status_is_ready_for_data_to_send(status_reg));

    //post-test clean up
    //printf("\nCleaning up after test");
    spi_disable_TXC_interrupt(p_spi);
    spi_disable_TDRE_interrupt(p_spi);
    spi_disable_RDRF_interrupt(p_spi);
    spi_disable_OVERRUN_interrupt(p_spi);
    spi_disable(p_spi);

    return returned_value;
}

static bool test_overrun_interrupt_in_loopback_mode(int spi_index,
                                                       bool transmit_MSB_first,
                                                       uint32_t baud_rate,
                                                       amba_spi_mode_t spi_mode,
                                                       amba_spi_flen_t spi_frame_length)
{
    bool returned_value;
    uint32_t status_reg;
    volatile amba_spi_t *p_spi = AMBA_SPI_PTR(spi_index);

    //printf("\nConfigure for OVERRUN INTERRUPT test");
    //pre-test configuration
    spi_enable_master_mode(p_spi);
    spi_enable_loopback_mode(p_spi);
    returned_value = spi_set_baud_div(p_spi, baud_rate, PERIPH0_FREQ);
    if(transmit_MSB_first)
    {
        spi_transmit_data_MSB_first(p_spi);
    }
    else
    {
        spi_transmit_data_LSB_first(p_spi);
    }
    spi_set_transmission_mode(p_spi, spi_mode);
    spi_set_frame_length(p_spi, spi_frame_length);
    spi_disable_TXC_interrupt(p_spi);
    spi_disable_TDRE_interrupt(p_spi);
    spi_disable_RDRF_interrupt(p_spi);
    spi_disable_OVERRUN_interrupt(p_spi);
    spi_enable(p_spi);
    //verify configuration
    assertTrue(returned_value);
    assertEq(spi_get_status(p_spi), SPI_STAT_TDRE);
    assertEq(p_spi->IRQM, 0);
    assertEq(spi_get_mapping_of_interrupts(p_spi), 1 << 5);
    assertEq(spi_get_frame_length(p_spi), spi_frame_length);
    assertEq(spi_get_transmission_mode(p_spi), spi_mode);
    //test
    //printf("\nTesting OVERRUN INTERRUPT");
    memset(g_data_received_array, 0, ARRAY_SIZE(g_data_received_array) * sizeof(uint32_t));
    interruptHandlerFunction = interruptHandler_OVR;
    spi_disable_TXC_interrupt(p_spi);
    spi_disable_TDRE_interrupt(p_spi);
    spi_disable_RDRF_interrupt(p_spi);
    spi_enable_OVERRUN_interrupt(p_spi);
    spi_put(p_spi, g_data_to_send_array[0]);
    g_irq_tx_in_progress = true;
    do
    {
        status_reg = spi_get_status(p_spi);
        assertFalse(spi_status_is_transmission_complete(status_reg));
        assertTrue(spi_status_is_transmitting(status_reg));
        assertFalse(spi_status_is_data_received(status_reg));
        assertFalse(spi_status_is_received_data_overran(status_reg));
    }while (!spi_status_is_ready_for_data_to_send(status_reg)); // wait for TX data register empty
    spi_put(p_spi, g_data_to_send_array[1]);
    while(g_irq_tx_in_progress == true);
    //compare received data
    assertEq(getValueForFrameLength(g_data_to_send_array[1], spi_frame_length), g_data_received_array[0]);
    //check status again
    status_reg = spi_get_status(p_spi);
    assertFalse(spi_status_is_transmission_complete(status_reg));
    assertFalse(spi_status_is_transmitting(status_reg));
    assertFalse(spi_status_is_data_received(status_reg));
    assertFalse(spi_status_is_received_data_overran(status_reg));
    assertTrue(spi_status_is_ready_for_data_to_send(status_reg));

    //post-test clean up
    //printf("\nCleaning up after test");
    spi_disable_TXC_interrupt(p_spi);
    spi_disable_TDRE_interrupt(p_spi);
    spi_disable_RDRF_interrupt(p_spi);
    spi_disable_OVERRUN_interrupt(p_spi);
    spi_disable(p_spi);
    interruptHandlerFunction = NULL;
    return returned_value;
}

static bool test_dma_operation_in_loopback_mode(int spi_index,
                                                bool transmit_MSB_first,
                                                uint32_t baud_rate,
                                                amba_spi_mode_t spi_mode,
                                                amba_spi_flen_t spi_frame_length)
{
    static const unsigned TEST_DMA_UP_CHNL = 0;
    static const unsigned TEST_DMA_DOWN_CHNL = 0;
    unsigned data_index;
    bool returned_value;
    uint32_t status_reg;
    volatile amba_spi_t *p_spi = AMBA_SPI_PTR(spi_index);
    volatile amba_dma_channel_t *chnlTx = AMBA_DMA_DWN_CH_PTR(TEST_DMA_DOWN_CHNL);
    volatile amba_dma_channel_t *chnlRx = AMBA_DMA_UP_CH_PTR(TEST_DMA_UP_CHNL);
    gp_chnlTx = chnlTx;
    gp_chnlRx = chnlRx;

    //printf("\nConfigure for DMA operation test");
    //pre-test configuration
    spi_enable_master_mode(p_spi);
    spi_enable_loopback_mode(p_spi);
    returned_value = spi_set_baud_div(p_spi, baud_rate, PERIPH0_FREQ);
    if(transmit_MSB_first)
    {
        spi_transmit_data_MSB_first(p_spi);
    }
    else
    {
        spi_transmit_data_LSB_first(p_spi);
    }
    spi_set_transmission_mode(p_spi, spi_mode);
    spi_set_frame_length(p_spi, spi_frame_length);
    spi_disable_TXC_interrupt(p_spi);
    spi_disable_TDRE_interrupt(p_spi);
    spi_disable_RDRF_interrupt(p_spi);
    spi_disable_OVERRUN_interrupt(p_spi);
    spi_enable(p_spi);
    //verify SPI configuration
    assertTrue(returned_value);
    assertEq(spi_get_status(p_spi), SPI_STAT_TDRE);
    assertEq(p_spi->IRQM, 0);
    assertEq(spi_get_mapping_of_interrupts(p_spi), 1 << 5);
    assertEq(spi_get_frame_length(p_spi), spi_frame_length);
    assertEq(spi_get_transmission_mode(p_spi), spi_mode);

    //configure DMA
    dma_enable_upstream();
    dma_enable_downstream();
    assertTrue(dma_is_upstream_enabled());
    assertTrue(dma_is_downstream_enabled());
    status_reg = dma_get_status(chnlTx);
    assertFalse(dma_status_is_channel_active(status_reg));
    assertTrue(dma_status_is_transfer_counter_equ_0(status_reg));
    assertTrue(dma_status_is_counter_reload_equ_0(status_reg));
    assertFalse(dma_status_is_mem_address_reloaded(status_reg));

    dma_assign_peripheral(chnlTx, AMBA_DMA_SPI_PSELECT(spi_index));
    assertEq(dma_assigned_peripheral(chnlTx), AMBA_DMA_SPI_PSELECT(spi_index));
    dma_assign_peripheral(chnlRx, AMBA_DMA_SPI_PSELECT(spi_index));
    assertEq(dma_assigned_peripheral(chnlRx), AMBA_DMA_SPI_PSELECT(spi_index));

    status_reg = dma_get_status(chnlRx);
    assertFalse(dma_status_is_channel_active(status_reg));
    assertTrue(dma_status_is_transfer_counter_equ_0(status_reg));
    assertTrue(dma_status_is_counter_reload_equ_0(status_reg));
    assertFalse(dma_status_is_mem_address_reloaded(status_reg));

     // Setup receive channel
    memset(g_data_received_array, 0, ARRAY_SIZE(g_data_received_array) * sizeof(uint32_t));
    dma_set_memory_address(chnlRx, (uint32_t)g_data_received_array);
    assertEq(dma_get_memory_address(chnlRx), (uint32_t)g_data_received_array);
    if(spi_frame_length == SPI_FLEN8)
    {
        dma_set_transfer_count(chnlRx, ARRAY_SIZE(g_data_received_array) * sizeof(uint32_t));
        dma_set_transfer_unit(chnlRx, DMA_TRU8);
    }
    else if(spi_frame_length == SPI_FLEN16)
    {
        dma_set_transfer_count(chnlRx, ARRAY_SIZE(g_data_received_array) * sizeof(uint16_t));
        dma_set_transfer_unit(chnlRx, DMA_TRU16);
    }
    else
    {
        dma_set_transfer_count(chnlRx, ARRAY_SIZE(g_data_received_array));
        dma_set_transfer_unit(chnlRx, DMA_TRU32);
    }
    dma_ring_buffer_mode_disable(chnlRx);
    dma_mem_address_increment_enable(chnlRx);
    dma_set_memory_address_reload(chnlRx, 0);
    dma_set_transfer_count_reload(chnlRx, 0);
    dma_disable_TCZ_interrupt(chnlRx);
    dma_disable_TRCZ_interrupt(chnlRx);
    dma_disable_MAR_interrupt(chnlRx);
    dma_channel_enable(chnlRx);
    assertEq(dma_get_transfer_count_reload(chnlRx), 0);
    assertEq(dma_get_memory_address_reload(chnlRx), 0);
    assertTrue(dma_is_channel_enabled(chnlRx));
    assertFalse(dma_is_ring_buffer_mode_enabled(chnlRx));
    assertTrue(dma_is_mem_address_increment_enabled(chnlRx));

    // Setup transmission channel
    dma_set_memory_address(chnlTx, (uint32_t)g_data_to_send_array);
    assertEq(dma_get_memory_address(chnlTx), (uint32_t)g_data_to_send_array);
    if(spi_frame_length == SPI_FLEN8)
    {
        dma_set_transfer_count(chnlTx, ARRAY_SIZE(g_data_to_send_array) * sizeof(uint32_t));
        dma_set_transfer_unit(chnlTx, DMA_TRU8);
    }
    else if(spi_frame_length == SPI_FLEN16)
    {
        dma_set_transfer_count(chnlTx, ARRAY_SIZE(g_data_to_send_array) * sizeof(uint16_t));
        dma_set_transfer_unit(chnlTx, DMA_TRU16);
    }
    else
    {
        dma_set_transfer_count(chnlTx, ARRAY_SIZE(g_data_to_send_array));
        dma_set_transfer_unit(chnlTx, DMA_TRU32);
    }
    dma_ring_buffer_mode_disable(chnlTx);
    dma_mem_address_increment_enable(chnlTx);
    dma_set_memory_address_reload(chnlTx, 0);
    dma_set_transfer_count_reload(chnlTx, 0);
    dma_disable_TCZ_interrupt(chnlTx);
    dma_disable_TRCZ_interrupt(chnlTx);
    dma_disable_MAR_interrupt(chnlTx);

    assertEq(dma_get_transfer_count_reload(chnlTx), 0);
    assertEq(dma_get_memory_address_reload(chnlTx), 0);
    assertFalse(dma_is_ring_buffer_mode_enabled(chnlTx));
    assertTrue(dma_is_mem_address_increment_enabled(chnlTx));

    //enable interrupts to detect end of transmission
    dmaInterruptHandlerFunction = interruptHandler_DMA;
    dma_enable_TCZ_interrupt(chnlTx);
    dma_enable_TCZ_interrupt(chnlRx);
    //lastly enable TX DMA channel to start transmission
    dma_channel_enable(chnlTx);
    assertTrue(dma_is_channel_enabled(chnlTx));
    status_reg = dma_get_status(chnlRx);
    assertTrue(dma_status_is_channel_active(status_reg));
    assertFalse(dma_status_is_transfer_counter_equ_0(status_reg));
    assertTrue(dma_status_is_counter_reload_equ_0(status_reg));
    assertFalse(dma_status_is_mem_address_reloaded(status_reg));
    status_reg = dma_get_status(chnlTx);
    assertTrue(dma_status_is_channel_active(status_reg));
    assertFalse(dma_status_is_transfer_counter_equ_0(status_reg));
    assertTrue(dma_status_is_counter_reload_equ_0(status_reg));
    assertFalse(dma_status_is_mem_address_reloaded(status_reg));

    //set TX indicators
    g_irq_rx_in_progress = true;
    g_irq_tx_in_progress = true;
    //wait for transmission to finish
    while((g_irq_tx_in_progress == true) || (g_irq_rx_in_progress == true));
    //compare received data
    for(data_index = 0; data_index < ARRAY_SIZE(g_data_to_send_array); data_index++)
    {
        if(spi_frame_length == SPI_FLEN24)
        {
            assertEq(g_data_received_array[data_index], getValueForFrameLength(g_data_to_send_array[data_index], spi_frame_length));
        }
        else
        {
            assertEq(g_data_received_array[data_index], g_data_to_send_array[data_index]);
        }
    }

    //post-test clean up
    //printf("\nCleaning up after test");
    dma_disable_upstream();
    dma_disable_downstream();
    dma_ring_buffer_mode_disable(chnlRx);
    dma_ring_buffer_mode_disable(chnlTx);
    dma_mem_address_increment_disable(chnlRx);
    dma_mem_address_increment_disable(chnlTx);
    dma_set_memory_address_reload(chnlRx, 0);
    dma_set_memory_address_reload(chnlTx, 0);
    dma_set_transfer_count_reload(chnlRx, 0);
    dma_set_transfer_count_reload(chnlTx, 0);
    dma_disable_TCZ_interrupt(chnlRx);
    dma_disable_TRCZ_interrupt(chnlRx);
    dma_disable_MAR_interrupt(chnlRx);
    dma_disable_TCZ_interrupt(chnlTx);
    dma_disable_TRCZ_interrupt(chnlTx);
    dma_disable_MAR_interrupt(chnlTx);
    dma_channel_disable(chnlRx);
    dma_channel_disable(chnlTx);
    assertFalse(dma_is_channel_enabled(chnlTx));
    assertFalse(dma_is_channel_enabled(chnlRx));
    assertFalse(dma_is_upstream_enabled());
    assertFalse(dma_is_downstream_enabled());
    assertEq(dma_get_transfer_count_reload(chnlTx), 0);
    assertEq(dma_get_memory_address_reload(chnlTx), 0);
    assertFalse(dma_is_ring_buffer_mode_enabled(chnlTx));
    assertFalse(dma_is_mem_address_increment_enabled(chnlTx));
    assertEq(dma_get_transfer_count_reload(chnlRx), 0);
    assertEq(dma_get_memory_address_reload(chnlRx), 0);
    assertFalse(dma_is_ring_buffer_mode_enabled(chnlRx));
    assertFalse(dma_is_mem_address_increment_enabled(chnlRx));

    spi_disable_TXC_interrupt(p_spi);
    spi_disable_TDRE_interrupt(p_spi);
    spi_disable_RDRF_interrupt(p_spi);
    spi_disable_OVERRUN_interrupt(p_spi);
    spi_disable(p_spi);
    interruptHandlerFunction = NULL;
    dmaInterruptHandlerFunction = NULL;
    return returned_value;
}

void test_spi(int spiIndex)
{
    bool returned_value;
    unsigned mode_index;
    unsigned frame_index;
    unsigned direction_index;
    unsigned baud_rate_index;
    static const amba_spi_mode_t modes_under_test[] = {SPI_MODE0, SPI_MODE1, SPI_MODE2, SPI_MODE3};
    static const amba_spi_flen_t frame_lengths_under_test[] = {SPI_FLEN8, SPI_FLEN16, SPI_FLEN24, SPI_FLEN32};
    static const uint32_t SPI_BAUD_RATE[] = {200000, 350000, 500000};
    g_spi_index = spiIndex;
    gp_spi = AMBA_SPI_PTR(spiIndex);

    for(baud_rate_index = 0; baud_rate_index < ARRAY_SIZE(SPI_BAUD_RATE); baud_rate_index++)
    {

        // check if core frequency is enough to perform test
        if ((CORE_FREQ < 50000000 || PERIPH0_FREQ < 50000000) && SPI_BAUD_RATE[baud_rate_index] > 200000)
        continue;

        printf("\n\n===================");
        printf("\nBAUD RATE: %u", (unsigned int)SPI_BAUD_RATE[baud_rate_index]);
        printf("\n===================");
        ////////////////
        // POLLING SCHEME
        ////////////////
        printf("\n\nTesting POLLING operation...");

        for(direction_index = 0; direction_index < 2; direction_index++)
        {// MSB FIRST / LSB FIRST
            for(mode_index = 0; mode_index < ARRAY_SIZE(modes_under_test); mode_index++)
            {
                for(frame_index = 0; frame_index < ARRAY_SIZE(frame_lengths_under_test); frame_index++)
                {
                    //printf("\nData direction = %u , spi mode = %u, frame length = %u", direction_index, modes_under_test[mode_index], frame_lengths_under_test[frame_index]);
                    returned_value = test_polling_scheme_operation_in_loopback_mode(spiIndex,
                                                                                    (direction_index != 0),
                                                                                    SPI_BAUD_RATE[baud_rate_index],
                                                                                    modes_under_test[mode_index],
                                                                                    frame_lengths_under_test[frame_index],
                                                                                    g_data_to_send_array,
                                                                                    g_data_received_array,
                                                                                    ARRAY_SIZE(g_data_received_array));
                    assertTrue(returned_value);
                }
            }
        }

        ///////////////
        // OVERRUN INDICATION IN POLLING SCHEME
        ///////////////
        printf("\n\nTesting OVERRUN INDICATION in polling scheme...");

        for(direction_index = 0; direction_index < 2; direction_index++)
        {// MSB FIRST / LSB FIRST
            for(mode_index = 0; mode_index < ARRAY_SIZE(modes_under_test); mode_index++)
            {
                for(frame_index = 0; frame_index < ARRAY_SIZE(frame_lengths_under_test); frame_index++)
                {
                    //printf("\nData direction = %u , spi mode = %u, frame length = %u", direction_index, modes_under_test[mode_index], frame_lengths_under_test[frame_index]);
                    returned_value = test_polling_scheme_overrun_condition(    spiIndex,
                                                                            (direction_index != 0),
                                                                            SPI_BAUD_RATE[baud_rate_index],
                                                                            modes_under_test[mode_index],
                                                                            frame_lengths_under_test[frame_index],
                                                                            g_data_to_send_array,
                                                                            g_data_received_array,
                                                                            ARRAY_SIZE(g_data_received_array));
                    assertTrue(returned_value);
                }
            }
        }

        ////////////////
        // INTERRUPTS
        ////////////////
        printf("\n\nTesting OVERRUN interrupt...");

        for(direction_index = 0; direction_index < 2; direction_index++)
        {// MSB FIRST / LSB FIRST
            for(mode_index = 0; mode_index < ARRAY_SIZE(modes_under_test); mode_index++)
            {
                for(frame_index = 0; frame_index < ARRAY_SIZE(frame_lengths_under_test); frame_index++)
                {
                    //printf("\nData direction = %u , spi mode = %u, frame length = %u", direction_index, modes_under_test[mode_index], frame_lengths_under_test[frame_index]);
                    returned_value = test_overrun_interrupt_in_loopback_mode( spiIndex,
                                                                              (direction_index != 0),
                                                                              SPI_BAUD_RATE[baud_rate_index],
                                                                              modes_under_test[mode_index],
                                                                              frame_lengths_under_test[frame_index]);
                    assertTrue(returned_value);
                }
            }
        }
        printf("\n\nTesting DMA operation...");
        for(direction_index = 0; direction_index < 2; direction_index++)
        {// MSB FIRST / LSB FIRST
            for(mode_index = 0; mode_index < ARRAY_SIZE(modes_under_test); mode_index++)
            {
                for(frame_index = 0; frame_index < ARRAY_SIZE(frame_lengths_under_test); frame_index++)
                {
                    //printf("\nData direction = %u , spi mode = %u, frame length = %u", direction_index, modes_under_test[mode_index], frame_lengths_under_test[frame_index]);
                    returned_value = test_dma_operation_in_loopback_mode( spiIndex,
                                                                          (direction_index != 0),
                                                                          SPI_BAUD_RATE[baud_rate_index],
                                                                          modes_under_test[mode_index],
                                                                          frame_lengths_under_test[frame_index]);
                    assertTrue(returned_value);
                }
            }
        }
    }
}

int main(void)
{
    unsigned spi_num, i;

    spi_num = AMBA_SPI_COUNT();
    printf("\nStarting SPI test (found %u SPIs)\n", spi_num);

    // Test all SPIs
    for (i = 0; i < spi_num; ++i)
    {
        // Enable interrupts
        assertEq(spi_get_mapping_of_interrupts(AMBA_SPI_PTR(i)), 1 << AMBA_SPI_IRQn(i));
        spi_set_mapping_of_interrupts(AMBA_SPI_PTR(i), 1 << 5);

        assertEq(dma_get_mapping_of_interrupts(), 1 << AMBA_DMA_IRQn);
        dma_set_mapping_of_interrupts((1 << 1));
        // Enable exceptions and interrupts
        CSR_CTRL_PTR->IRQ_MASK = (1 << 5) | (1 << 1) | (1 << 0); // IRQ 1, 5 and exceptions
        CSR_CTRL_PTR->STATUS |= CSR_STAT_CIEN;

        printf("\n\nTesting SPI%u", i);
        test_spi(i);

        //restore IRQ mapping
        spi_set_mapping_of_interrupts(AMBA_SPI_PTR(i), 1 << AMBA_SPI_IRQn(i));
        dma_set_mapping_of_interrupts((1 << AMBA_DMA_IRQn));
    }

    print_test_summary();

    return 0;
}
