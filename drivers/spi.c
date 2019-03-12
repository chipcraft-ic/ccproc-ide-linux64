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
* File Name : spi.c
* Author    : Maciej Plasota
* ******************************************************************************
* $Date: 2018-09-07 16:07:40 +0200 (pią) $
* $Revision: 296 $
*H*****************************************************************************/

#include "spi.h"

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
bool spi_set_baud_div(volatile amba_spi_t *spi, uint32_t baudrate, uint32_t clkper_hz)
{
    uint32_t prescaler;

    // Sanity check, requested baudrate can't be 0
    if (baudrate == 0)
    {
        return false;
    }

    prescaler = SPI_CTRL_PRESC(baudrate, clkper_hz);

    if (prescaler > UINT8_MAX)
    {
        /*
         * Highest possible divisor is 255 so fail since we can't get
         * low enough baudrate.
         */
        return false;
    }
    /*
     * We now know that the divisor is 255 or lower.
     * Update register and make sure to clear out any leftover bits
     */
    spi->CTRL = (spi->CTRL & ~SPI_CTRL_PRESCALER_MASK) | (prescaler << SPI_CTRL_PRESC_SHIFT);

    return true;
}
