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
* File Name : spi.h
* Author    : Maciej Plasota
* ******************************************************************************
* $Date: 2018-12-06 22:15:13 +0100 (czw, 06 gru 2018) $
* $Revision: 366 $
*H*****************************************************************************/

#ifndef _SPI_H_
#define _SPI_H_
#pragma once

#include <ccproc-amba.h>
#include <ccproc-amba-spi.h>
#include <stdbool.h>

/*! \brief Calculates and sets the SPI prescaler.
 *
 * \param spi The SPI module address
 * \param baudrate The expected baudrate on the SPI.
 * \param clkper_hz  SPI module input clock frequency (Peripheral clock, Hz).
 *
 * \return Status of operation.
 *   \retval true  Success.
 *   \retval false Error.
 */
bool spi_set_baud_div(volatile amba_spi_t *spi, uint32_t baudrate, uint32_t clkper_hz);

/*! \brief Enables the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable(volatile amba_spi_t *spi)
{
    spi->CTRL |= SPI_CTRL_EN;
}

/*! \brief Disables the SPI.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_disable(volatile amba_spi_t *spi)
{
    spi->CTRL &= ~SPI_CTRL_EN;
}

/*! \brief Tests if the SPI is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c true if the SPI is enabled, otherwise \c false.
 */
static inline bool spi_is_enabled(volatile amba_spi_t *spi)
{
    return spi->CTRL & SPI_CTRL_EN ? true : false;
}

/*! \brief Put one data frame to a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 * \param data The data frame to be loaded.
 *
 */
static inline void spi_put(volatile amba_spi_t *spi, uint32_t data)
{
    spi->TDR = data;
}

/*! \brief Get one data frame from a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 * \return The data frame
 *
 */
static inline uint32_t spi_get(volatile amba_spi_t *spi)
{
    return spi->RDR;
}

/*! \brief Activate SPI master mode of a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_master_mode(volatile amba_spi_t *spi)
{
    spi->CTRL &= ~SPI_CTRL_SLAVE;
}

/*! \brief Activate SPI slave mode of a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_slave_mode(volatile amba_spi_t *spi)
{
    spi->CTRL |= SPI_CTRL_SLAVE;
}

/*! \brief Tests if the SPI master mode of a SPI peripheral is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c true if the SPI master mode is enabled, otherwise \c false.
 */
static inline bool spi_is_master_mode(volatile amba_spi_t *spi)
{
    return !((spi->CTRL & SPI_CTRL_SLAVE) == SPI_CTRL_SLAVE);
}

/*! \brief Activate SPI loopback mode of a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_loopback_mode(volatile amba_spi_t *spi)
{
    spi->CTRL |= SPI_CTRL_LOOP;
}

/*! \brief Dectivate SPI loopback mode of a SPI peripheral.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_disable_loopback_mode(volatile amba_spi_t *spi)
{
    spi->CTRL &= ~SPI_CTRL_LOOP;
}

/*! \brief Tests if the SPI loopback mode of a SPI peripheral is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c true if the SPI loopback mode is enabled, otherwise \c false.
 */
static inline bool spi_is_loopback_mode_enabled(volatile amba_spi_t *spi)
{
    return ((spi->CTRL & SPI_CTRL_LOOP) == SPI_CTRL_LOOP);
}

/*! \brief Sets SPI peripheral to transmit frame starting with MSB.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_transmit_data_MSB_first(volatile amba_spi_t *spi)
{
    spi->CTRL |= SPI_CTRL_MSB;
}

/*! \brief Sets SPI peripheral to transmit frame starting with LSB.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_transmit_data_LSB_first(volatile amba_spi_t *spi)
{
    spi->CTRL &= ~SPI_CTRL_MSB;
}

/*! \brief Tests if the  SPI peripheral is configured to transmit frame starting with MSB.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c true if the transmit MSB first mode is enabled, otherwise \c false.
 */
static inline bool spi_is_data_transmit_MSB_first(volatile amba_spi_t *spi)
{
    return ((spi->CTRL & SPI_CTRL_MSB) == SPI_CTRL_MSB);
}

/*! \brief Configures SPI peripheral transmission mode.
 *
 * \param spi Base address of the SPI instance.
 * \param mode Transmission mode.
 */
static inline void spi_set_transmission_mode(volatile amba_spi_t *spi, amba_spi_mode_t mode)
{
    spi->CTRL = (spi->CTRL & ~SPI_CTRL_MODE_MASK) | (mode << SPI_CTRL_MODE_SHIFT);
}

/*! \brief Returns SPI peripheral transmission mode.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c SPI mode.
 */
static inline amba_spi_mode_t spi_get_transmission_mode(volatile amba_spi_t *spi)
{
    return (spi->CTRL & SPI_CTRL_MODE_MASK) >> SPI_CTRL_MODE_SHIFT;
}

/*! \brief Configures SPI peripheral frame length.
 *
 * \param spi Base address of the SPI instance.
 * \param mode Frame length.
 */
static inline void spi_set_frame_length(volatile amba_spi_t *spi, amba_spi_flen_t frame_length)
{
    spi->CTRL = (spi->CTRL & ~SPI_CTRL_FLEN_MASK) | (frame_length << SPI_CTRL_FLEN_SHIFT);
}

/*! \brief Returns SPI peripheral frame length.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c SPI frame length.
 */
static inline amba_spi_flen_t spi_get_frame_length(volatile amba_spi_t *spi)
{
    return (spi->CTRL & SPI_CTRL_FLEN_MASK) >> SPI_CTRL_FLEN_SHIFT;
}

/*! \brief Returns SPI status register.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c SPI status register.
 */
static inline uint32_t spi_get_status(volatile amba_spi_t *spi)
{
    return spi->STATUS;
}

/*! \brief Tests if the status indicates data transmission has completed.
 *
 * \param status Content of the status register.
 *
 * \return \c true if transmission has been completed, otherwise \c false.
 */
static inline bool spi_status_is_transmission_complete(uint32_t status)
{
    return status & SPI_STAT_TXC;
}

/*! \brief Tests if the status indicates transmission in progress.
 *
 * \param status Content of the status register.
 *
 * \return \c true if the module is busy, otherwise \c false.
 */
static inline bool spi_status_is_transmitting(uint32_t status)
{
    return status & SPI_STAT_BUSY;
}

/*! \brief Tests if the status indicates valid received data.
 *
 * \param status Content of the status register.
 *
 * \return \c true if data received register is valid, otherwise \c false.
 */
static inline bool spi_status_is_data_received(uint32_t status)
{
    return status & SPI_STAT_RDRF;
}

/*! \brief Tests if the status indicates reception register overrun.
 *
 * \param status Content of the status register.
 *
 * \return \c true if reception register has been overrun, otherwise \c false.
 */
static inline bool spi_status_is_received_data_overran(uint32_t status)
{
    return status & SPI_STAT_OVR;
}

/*! \brief Tests if the status indicates transmission register underrun (only valid in slave opeartion mode).
 *
 * \param status Content of the status register.
 *
 * \return \c true if transmission register has been underrun, otherwise \c false.
 */
static inline bool spi_status_is_received_data_underran(uint32_t status)
{
    return status & SPI_STAT_UNR;
}

/*! \brief Tests if the status indicates transmit data register empty.
 *
 * \param status Content of the status register.
 *
 * \return \c true if transmit data register is empty, otherwise \c false.
 */
static inline bool spi_status_is_ready_for_data_to_send(uint32_t status)
{
    return status & SPI_STAT_TDRE;
}

/*! \brief Activate interrupt at the end of transmission.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_TXC_interrupt(volatile amba_spi_t *spi)
{
    spi->IRQM |= SPI_TXCIE;
}

/*! \brief Deactivate interrupt at the end of transmission.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_disable_TXC_interrupt(volatile amba_spi_t *spi)
{
    spi->IRQM &= ~SPI_TXCIE;
}

/*! \brief Tests if the interrupt at the end of transmission is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c true if the interrupt at the end of transmission is enabled, otherwise \c false.
 */
static inline bool spi_is_TXC_interrupt_enabled(volatile amba_spi_t *spi)
{
    return spi->IRQM & SPI_TXCIE;
}

/*! \brief Activate interrupt when SPI peripheral is ready to accept next data to be send.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_TDRE_interrupt(volatile amba_spi_t *spi)
{
    spi->IRQM |= SPI_TXDREIE;
}

/*! \brief Deactivate interrupt when SPI peripheral is ready to accept next data to be send.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_disable_TDRE_interrupt(volatile amba_spi_t *spi)
{
    spi->IRQM &= ~SPI_TXDREIE;
}

/*! \brief Tests if the interrupt when SPI peripheral is ready to accept next data to be send is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c true if the interrupt when SPI peripheral is ready to accept next data to be send is enabled, otherwise \c false.
 */
static inline bool spi_is_TDRE_interrupt_enabled(volatile amba_spi_t *spi)
{
    return spi->IRQM & SPI_TXDREIE;
}

/*! \brief Activate interrupt on data reception.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_RDRF_interrupt(volatile amba_spi_t *spi)
{
    spi->IRQM |= SPI_RDRFIE;
}

/*! \brief Deactivate interrupt on data reception.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_disable_RDRF_interrupt(volatile amba_spi_t *spi)
{
    spi->IRQM &= ~SPI_RDRFIE;
}

/*! \brief Tests if the interrupt on data reception is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c true if the interrupt at the end of transmission is enabled, otherwise \c false.
 */
static inline bool spi_is_RDRF_interrupt_enabled(volatile amba_spi_t *spi)
{
    return spi->IRQM & SPI_RDRFIE;
}

/*! \brief Activate interrupt on reception register overrun.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_OVERRUN_interrupt(volatile amba_spi_t *spi)
{
    spi->IRQM |= SPI_OVRIE;
}

/*! \brief Deactivate interrupt on reception register overrun.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_disable_OVERRUN_interrupt(volatile amba_spi_t *spi)
{
    spi->IRQM &= ~SPI_OVRIE;
}

/*! \brief Tests if the interrupt on reception register overrun is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c true if the interrupt on reception register overrun is enabled, otherwise \c false.
 */
static inline bool spi_is_OVERRUN_interrupt_enabled(volatile amba_spi_t *spi)
{
    return spi->IRQM & SPI_OVRIE;
}

/*! \brief Activate interrupt on tranmsission register underrun.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_enable_UNDERRUN_interrupt(volatile amba_spi_t *spi)
{
    spi->IRQM |= SPI_UNRIE;
}

/*! \brief Deactivate interrupt on transmission register underrun.
 *
 * \param spi Base address of the SPI instance.
 */
static inline void spi_disable_UNDERRUN_interrupt(volatile amba_spi_t *spi)
{
    spi->IRQM &= ~SPI_UNRIE;
}

/*! \brief Tests if the interrupt on transmission register underrun is enabled.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c true if the interrupt on transmission register underrun is enabled, otherwise \c false.
 */
static inline bool spi_is_UNDERRUN_interrupt_enabled(volatile amba_spi_t *spi)
{
    return spi->IRQM & SPI_UNRIE;
}

/*! \brief Configure mapping of the SPI peripheral interrupt.
 *
 * \param spi Base address of the SPI instance.
 * \param irq mapping mapping mask of the SPI peripheral interrupt.
 */
static inline void spi_set_mapping_of_interrupts(volatile amba_spi_t *spi, uint32_t irq_mapping)
{
    spi->IRQMAP = irq_mapping;
}

/*! \brief Returns mapping of the SPI peripheral interrupt.
 *
 * \param spi Base address of the SPI instance.
 *
 * \return \c 	mapping mapping mask of the SPI peripheral interrupt.
 */
static inline uint32_t spi_get_mapping_of_interrupts(volatile amba_spi_t *spi)
{
    return spi->IRQMAP;
}

#endif  // _SPI_H_
