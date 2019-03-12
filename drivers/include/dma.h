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
* File Name : dma.h
* Author    : Maciej Plasota
* ******************************************************************************
* $Date: 2018-09-07 16:07:40 +0200 (pią) $
* $Revision: 296 $
*H*****************************************************************************/

#ifndef _DMA_H_
#define _DMA_H_
#pragma once

#include <ccproc-amba.h>
#include <ccproc-amba-dma.h>
#include <stdbool.h>

/*! \brief Enables DMA Upstream channels.
 */
static inline void dma_enable_upstream()
{
    AMBA_DMA_PTR->CONF |= DMA_CONF_USEN;
}

/*! \brief Disables DMA Upstream channels.
 */
static inline void dma_disable_upstream()
{
    AMBA_DMA_PTR->CONF &= ~DMA_CONF_USEN;
}

/*! \brief Tests if DMA Upstream is enabled.
 *
 * \return \c true if DMA Upstream is enabled, otherwise \c false.
 */
static inline bool dma_is_upstream_enabled()
{
    return ((AMBA_DMA_PTR->CONF & DMA_CONF_USEN) == DMA_CONF_USEN);
}

/*! \brief Enables DMA Downstream channels.
 */
static inline void dma_enable_downstream()
{
    AMBA_DMA_PTR->CONF |= DMA_CONF_DSEN;
}

/*! \brief Disables DMA Downstream channels.
 */
static inline void dma_disable_downstream()
{
    AMBA_DMA_PTR->CONF &= ~DMA_CONF_DSEN;
}

/*! \brief Tests if DMA Downstream is enabled.
 *
 * \return \c true if DMA Downstream is enabled, otherwise \c false.
 */
static inline bool dma_is_downstream_enabled()
{
    return ((AMBA_DMA_PTR->CONF & DMA_CONF_DSEN) == DMA_CONF_DSEN);
}

/*! \brief Enables round-robin arbitration scheme for DMA Upstream channels.
 */
static inline void dma_enable_upstream_round_robin()
{
    AMBA_DMA_PTR->CONF |= DMA_CONF_USARB;
}

/*! \brief Disables round-robin arbitration scheme for DMA Upstream channels.
 *
 * Channels are handled based on their numbers.
 */
static inline void dma_disable_upstream_round_robin()
{
    AMBA_DMA_PTR->CONF &= ~DMA_CONF_USARB;
}

/*! \brief Tests if round-robin arbitration scheme is enabled for DMA Upstream channels.
 *
 * \return \c true if round-robin arbitration scheme is enabled, otherwise \c false.
 */
static inline bool dma_is_upstream_round_robin_enabled()
{
    return ((AMBA_DMA_PTR->CONF & DMA_CONF_USARB) == DMA_CONF_USARB);
}

/*! \brief Enables round-robin arbitration scheme for DMA Downstream channels.
 */
static inline void dma_enable_downstream_round_robin()
{
    AMBA_DMA_PTR->CONF |= DMA_CONF_DSARB;
}

/*! \brief Disables round-robin arbitration scheme for DMA Downstream channels.
 *
 * Channels are handled based on their numbers.
 */
static inline void dma_disable_downstream_round_robin()
{
    AMBA_DMA_PTR->CONF &= ~DMA_CONF_DSARB;
}

/*! \brief Tests if round-robin arbitration scheme is enabled for DMA Downstream channels.
 *
 * \return \c true if round-robin arbitration scheme is enabled, otherwise \c false.
 */
static inline bool dma_is_downstream_round_robin_enabled()
{
    return ((AMBA_DMA_PTR->CONF & DMA_CONF_DSARB) == DMA_CONF_DSARB);
}

/*! \brief Configure mapping of the DMA peripheral interrupt.
 *
 * \param irq mapping mapping mask of the DMA peripheral interrupt.
 */
static inline void dma_set_mapping_of_interrupts(uint32_t irq_mapping)
{
    AMBA_DMA_PTR->IRQMAP = irq_mapping;
}

/*! \brief Returns mapping of the DMA peripheral interrupt.
 *
 * \return \c   mapping mapping mask of the DMA peripheral interrupt.
 */
static inline uint32_t dma_get_mapping_of_interrupts()
{
    return AMBA_DMA_PTR->IRQMAP;
}

/*! \brief Returns DMA channel status register.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c DMA status register.
 */
static inline uint32_t dma_get_status(volatile amba_dma_channel_t * channel)
{
    return channel->STATUS;
}

/*! \brief Tests if the status indicates channel is active (data transfer is in progress).
 *
 * \param status Content of the status register.
 *
 * \return \c true if DMA channel is active, otherwise \c false.
 */
static inline bool dma_status_is_channel_active(uint32_t status)
{
    return ((status & DMA_STAT_ACT) == DMA_STAT_ACT);
}

/*! \brief Tests if the status indicates channel data counter equal to 0 (i.e. no more data to transfer).
 *
 * \param status Content of the status register.
 *
 * \return \c true if no more data to transfer, otherwise \c false.
 */
static inline bool dma_status_is_transfer_counter_equ_0(uint32_t status)
{
    return ((status & DMA_STAT_TCZ) == DMA_STAT_TCZ);
}

/*! \brief Tests if the status indicates channel data counter reload equal to 0 (i.e. no more data to transfer).
 *
 * \param status Content of the status register.
 *
 * \return \c true if no more data to transfer, otherwise \c false.
 */
static inline bool dma_status_is_counter_reload_equ_0(uint32_t status)
{
    return ((status & DMA_STAT_RCZ) == DMA_STAT_RCZ);
}

/*! \brief Tests if the status indicates destination (for downstream)/source (for upstream) memory address has been reloaded
 * with the content of memory address reload register.
 *
 * \param status Content of the status register.
 *
 * \return \c true if memory address has been reloaded, otherwise \c false.
 */
static inline bool dma_status_is_mem_address_reloaded(uint32_t status)
{
    return ((status & DMA_STAT_MAR) == DMA_STAT_MAR);
}

/*! \brief Enable selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 */
static inline void dma_channel_enable(volatile amba_dma_channel_t * channel)
{
    channel->CTRL |= DMA_CTRL_EN;
}

/*! \brief Disable selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 */
static inline void dma_channel_disable(volatile amba_dma_channel_t * channel)
{
    channel->CTRL &= ~DMA_CTRL_EN;
}

/*! \brief Tests if DMA channel is enabled.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c true if channel is enabled, otherwise \c false.
 */
static inline bool dma_is_channel_enabled(volatile amba_dma_channel_t * channel)
{
    return ((channel->CTRL & DMA_CTRL_EN) == DMA_CTRL_EN);
}

/*! \brief Set the transfer unit (data size) for DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 * \param transfer_unit size of data transfer unit (8-bit, 16-bit or 32-bit).
 */
static inline void dma_set_transfer_unit(volatile amba_dma_channel_t * channel, amba_dma_tru_t transfer_unit)
{
    channel->CTRL = (channel->CTRL & ~DMA_CTRL_TRU_MASK) | (transfer_unit << DMA_CTRL_TRU_SHIFT);
}

/*! \brief Returns the transfer unit (data size) for DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c configured transfer unit size.
 */
static inline amba_dma_tru_t dma_get_transfer_unit(volatile amba_dma_channel_t * channel)
{
    return (amba_dma_tru_t) ((channel->CTRL & DMA_CTRL_TRU_MASK) >> DMA_CTRL_TRU_SHIFT);
}

/*! \brief Enable ring buffer mode for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * In ring buffer mode, memory and counter reload registers are not cleared upon reload.
 */
static inline void dma_ring_buffer_mode_enable(volatile amba_dma_channel_t * channel)
{
    channel->CTRL |= DMA_CTRL_RING;
}

/*! \brief Disable ring buffer mode for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * In ring buffer mode, memory and counter reload registers are not cleared upon reload.
 */
static inline void dma_ring_buffer_mode_disable(volatile amba_dma_channel_t * channel)
{
    channel->CTRL &= ~DMA_CTRL_RING;
}

/*! \brief Tests if ring buffer mode is enabled for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c true if ring buffer mode is enabled, otherwise \c false.
 */
static inline bool dma_is_ring_buffer_mode_enabled(volatile amba_dma_channel_t * channel)
{
    return ((channel->CTRL & DMA_CTRL_RING) == DMA_CTRL_RING);
}

/*! \brief Enable source/destination memory address increment upon data transfer.
 *
 * \param channel Base address of the DMA channel instance.
 *
 */
static inline void dma_mem_address_increment_enable(volatile amba_dma_channel_t * channel)
{
    channel->CTRL |= DMA_CTRL_INC;
}

/*! \brief Disable source/destination memory address increment upon data transfer.
 *
 * \param channel Base address of the DMA channel instance.
 *
 */
static inline void dma_mem_address_increment_disable(volatile amba_dma_channel_t * channel)
{
    channel->CTRL &= ~DMA_CTRL_INC;
}

/*! \brief Tests if source/destination memory address increment is enabled for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c true if source/destination memory address increment is enabled, otherwise \c false.
 */
static inline bool dma_is_mem_address_increment_enabled(volatile amba_dma_channel_t * channel)
{
    return ((channel->CTRL & DMA_CTRL_INC) == DMA_CTRL_INC) && ((channel->CTRL & DMA_CTRL_DEC) == 0);
}

/*! \brief Enable source/destination memory address decrement upon data transfer.
 *
 * \param channel Base address of the DMA channel instance.
 *
 */
static inline void dma_mem_address_decrement_enable(volatile amba_dma_channel_t * channel)
{
    channel->CTRL |= DMA_CTRL_DEC;
}

/*! \brief Disable source/destination memory address decrement upon data transfer.
 *
 * \param channel Base address of the DMA channel instance.
 *
 */
static inline void dma_mem_address_decrement_disable(volatile amba_dma_channel_t * channel)
{
    channel->CTRL &= ~DMA_CTRL_DEC;
}

/*! \brief Tests if source/destination memory address decrement is enabled for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c true if source/destination memory address decrement is enabled, otherwise \c false.
 */
static inline bool dma_is_mem_address_decrement_enabled(volatile amba_dma_channel_t * channel)
{
    return ((channel->CTRL & DMA_CTRL_DEC) == DMA_CTRL_DEC) && ((channel->CTRL & DMA_CTRL_INC) == 0);
}

/*! \brief Keep source/destination memory address unchanged upon data transfer for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 */
static inline void dma_mem_address_constant(volatile amba_dma_channel_t * channel)
{
    channel->CTRL &= ~(DMA_CTRL_DEC | DMA_CTRL_INC);
}

/*! \brief Tests if source/destination memory address will remain unchanged upon data transfer for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c true if source/destination memory address will remain unchanged upon data transfer, otherwise \c false.
 */
static inline bool dma_is_mem_address_constant(volatile amba_dma_channel_t * channel)
{
    return (((channel->CTRL & DMA_CTRL_DEC) == DMA_CTRL_DEC) == ((channel->CTRL & DMA_CTRL_INC) == DMA_CTRL_INC));
}

/*! \brief Assign peripheral to the selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 * \param peripheral_number Number of peripheral to be bounded with DMA channel.
 */
static inline void dma_assign_peripheral(volatile amba_dma_channel_t * channel, uint32_t peripheral_number)
{
    channel->PSELECT = peripheral_number;
}

/*! \brief Return peripheral assigned to the selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c number of peripheral bounded with DMA channel.
 */
static inline uint32_t dma_assigned_peripheral(volatile amba_dma_channel_t * channel)
{
    return channel->PSELECT;
}

/*! \brief Set source (for downstream)/destination (for upstream) memory address for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 * \param mem_address Memory address.
 */
static inline void dma_set_memory_address(volatile amba_dma_channel_t * channel, uint32_t mem_address)
{
    channel->ADDRESS = mem_address;
}

/*! \brief Return source (for downstream)/destination (for upstream) memory address for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c memory address.
 */
static inline uint32_t dma_get_memory_address(volatile amba_dma_channel_t * channel)
{
    return channel->ADDRESS;
}

/*! \brief Set memory address reload value for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 * \param mem_address Memory address.
 *
 * The content of memory address reload register will be loaded to memory address register when transfer count register reaches zero.
 * The value of this register should usually be set alongside transfer counter reload register. This way one may configure 2 subsequent transfer from
 * single peripheral to 2 memory locations. This register must be configured with the same value as memory address register, when ring buffer mode is selected.
 */
static inline void dma_set_memory_address_reload(volatile amba_dma_channel_t * channel, uint32_t mem_address)
{
    channel->ADDRESSREL = mem_address;
}

/*! \brief Return source memory address reload value for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c memory address.
 */
static inline uint32_t dma_get_memory_address_reload(volatile amba_dma_channel_t * channel)
{
    return channel->ADDRESSREL;
}

/*! \brief Set the number of data frames to be transferred by DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 * \param mem_address Memory address.
 */
static inline void dma_set_transfer_count(volatile amba_dma_channel_t * channel, uint32_t mem_address)
{
    channel->COUNTER = mem_address;
}

/*! \brief Return the number of data frames to be transferred by DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c number of data units to be transferred.
 */
static inline uint32_t dma_get_transfer_count(volatile amba_dma_channel_t * channel)
{
    return channel->COUNTER;
}

/*! \brief Set transfer count reload value for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 * \param mem_address Memory address.
 *
 * The content of transfer count reload register will be loaded to transfer count register when transfer count register reaches zero.
 * The value of this register should usually be set alongside memory address reload register. This way one may configure 2 subsequent transfer from
 * single peripheral to 2 memory locations. This register must be configured with the same value as transfer count register, when ring buffer mode is selected.
 */
static inline void dma_set_transfer_count_reload(volatile amba_dma_channel_t * channel, uint32_t count)
{
    channel->COUNTERREL = count;
}

/*! \brief Return transfer count reload value for selected DMA channel.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c transfer counter reload value.
 */
static inline uint32_t dma_get_transfer_count_reload(volatile amba_dma_channel_t * channel)
{
    return channel->COUNTERREL;
}

/*! \brief Activate interrupt when transfer count register equals 0.
 *
 * \param channel Base address of the DMA channel instance.
 */
static inline void dma_enable_TCZ_interrupt(volatile amba_dma_channel_t * channel)
{
    channel->IRQM |= DMA_TCZIE;
}

/*! \brief Deactivate interrupt when transfer count register equals 0.
 *
 * \param channel Base address of the DMA channel instance.
 */
static inline void dma_disable_TCZ_interrupt(volatile amba_dma_channel_t * channel)
{
    channel->IRQM &= ~DMA_TCZIE;
}

/*! \brief Tests if the interrupt when transfer count register equals 0 is enabled.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c true if the interrupt when transfer count register equals 0 is enabled, otherwise \c false.
 */
static inline bool dma_is_TCZ_interrupt_enabled(volatile amba_dma_channel_t * channel)
{
    return channel->IRQM & DMA_TCZIE;
}

/*! \brief Activate interrupt when transfer count reload register equals 0.
 *
 * \param channel Base address of the DMA channel instance.
 */
static inline void dma_enable_TRCZ_interrupt(volatile amba_dma_channel_t * channel)
{
    channel->IRQM |= DMA_RCZIE;
}

/*! \brief Deactivate interrupt when transfer count reload register equals 0.
 *
 * \param channel Base address of the DMA channel instance.
 */
static inline void dma_disable_TRCZ_interrupt(volatile amba_dma_channel_t * channel)
{
    channel->IRQM &= ~DMA_RCZIE;
}

/*! \brief Tests if the interrupt when transfer count reload register equals 0 is enabled.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c true if the interrupt when transfer count reload register equals 0 is enabled, otherwise \c false.
 */
static inline bool dma_is_TRCZ_interrupt_enabled(volatile amba_dma_channel_t * channel)
{
    return channel->IRQM & DMA_RCZIE;
}

/*! \brief Activate interrupt when memory address reload register equals 0.
 *
 * \param channel Base address of the DMA channel instance.
 */
static inline void dma_enable_MAR_interrupt(volatile amba_dma_channel_t * channel)
{
    channel->IRQM |= DMA_MARIE;
}

/*! \brief Dectivate interrupt when memory address reload register equals 0.
 *
 * \param channel Base address of the DMA channel instance.
 */
static inline void dma_disable_MAR_interrupt(volatile amba_dma_channel_t * channel)
{
    channel->IRQM &= ~DMA_MARIE;
}

/*! \brief Tests if the interrupt when memory address reload register equals 0 is enabled.
 *
 * \param channel Base address of the DMA channel instance.
 *
 * \return \c true if the interrupt when memory address reload register equals 0 is enabled, otherwise \c false.
 */
static inline bool dma_is_MAR_interrupt_enabled(volatile amba_dma_channel_t * channel)
{
    return channel->IRQM & DMA_MARIE;
}

#endif  // _DMA_H_
