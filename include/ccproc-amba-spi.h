/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2019-10-03 19:22:07 +0200 (czw, 03 paź 2019) $
* $Revision: 474 $
*
*  ----------------------------------------------------------------------
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
 * -------------------------------------------------------------------- */

/**
 * @file            ccproc-amba-spi.h
 * @brief           CC Processor AMBA SPI definitions
 * @author          Rafal Harabien
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_SPI_H
#define __CCPROC_AMBA_SPI_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup spi SPI Controller
 * SPI Controller registers and definitions
 * @{
 *//************************/

/** SPI registers */
typedef struct
{
    uint32_t STATUS;  /*!< Status Register          */
    uint32_t CTRL;    /*!< Control Register         */
    uint32_t TDR;     /*!< Transmit Data Register   */
    uint32_t RDR;     /*!< Receive Data Register    */
    uint32_t IRQM;    /*!< Interrupt Mask Register  */
    uint32_t IRQMAP;  /*!< Interrupt Mapping        */
    uint32_t INFO;    /*!< Info Register            */
    uint32_t NSS;     /*!< Slave Select Register    */
} amba_spi_t;

#ifdef CCPROC_SDK
 #define AMBA_SPI_BASE(index) (AMBA_SPI0_BASE+(index)*0x100)               /*!< SPI base address             */
 #define AMBA_SPI_PTR(index) ((volatile amba_spi_t*)AMBA_SPI_BASE(index))  /*!< SPI pointer                  */
 #define AMBA_SPI_IRQn(index) (AMBA_SPI0_IRQn + (index) % 2)               /*!< SPI default interrupt number */
#endif

/** SPI status bits */
enum
{
    SPI_STAT_TXC    = 0x01,  /*!< Transmission Complete            */
    SPI_STAT_TDRE   = 0x02,  /*!< Transmission Data Register Empty */
    SPI_STAT_RDRF   = 0x04,  /*!< Read Data Register Full          */
    SPI_STAT_OVR    = 0x08,  /*!< Overrun Error                    */
    SPI_STAT_BUSY   = 0x10,  /*!< Busy                             */
    SPI_STAT_NSS_RE = 0x20,  /*!< NSS rising edge                  */
    SPI_STAT_NSS_FE = 0x40,  /*!< NSS falling edge                 */
    SPI_STAT_NSS    = 0x80,  /*!< NSS state                        */
    SPI_STAT_UNR    = 0x100  /*!< Underrun Error                   */
};

/** SPI Control Register Shifts */
enum
{
    SPI_CTRL_MODE_SHIFT  = 4,  /*!< Mode Bit Offset                     */
    SPI_CTRL_FLEN_SHIFT  = 6,  /*!< Frame Length Bit Offset             */
    SPI_CTRL_PRESC_SHIFT = 8,  /*!< SCK Generator Prescaler Bit Offset  */
};

/** SPI Mode codes */
typedef enum
{
    SPI_MODE0   = 0,  /*!< SPI Mode 0 Enable - sampling at first edge,  first edge is rising  */
    SPI_MODE1   = 1,  /*!< SPI Mode 1 Enable - sampling at second edge, first edge is rising  */
    SPI_MODE2   = 2,  /*!< SPI Mode 2 Enable - sampling at first edge,  first edge is falling */
    SPI_MODE3   = 3,  /*!< SPI Mode 3 Enable - sampling at second edge, first edge is falling */
} amba_spi_mode_t;

/** SPI Frame Length codes */
typedef enum
{
    SPI_FLEN8   = 0,  /*!< 8 Bits Per Frame                                                   */
    SPI_FLEN16  = 1,  /*!< 16 Bits Per Frame                                                  */
    SPI_FLEN24  = 2,  /*!< 24 Bits Per Frame                                                  */
    SPI_FLEN32  = 3,  /*!< 32 Bits Per Frame                                                  */
} amba_spi_flen_t;

#define SPI_FRAME_LENGTH_IN_BYTES(spi_frame_length_code) (spi_frame_length_code + 1) /*!< SPI Frame Length in bytes */

/** SPI control bits */
enum
{
    SPI_CTRL_EN      = 0x01,    /*!< SPI Enable                                                         */

    SPI_CTRL_MASTER  = 0x00,    /*!< SPI Master Mode                                                    */
    SPI_CTRL_SLAVE   = 0x02,

    SPI_CTRL_MSB     = 0x04,    /*!< MSB First                                                          */
    SPI_CTRL_LOOP    = 0x08,    /*!< Loopback Mode Enable                                               */

    SPI_CTRL_MODE0   = SPI_MODE0 << SPI_CTRL_MODE_SHIFT,   /*!< SPI Mode 0 Enable - sampling at first edge,  first edge is rising  */
    SPI_CTRL_MODE1   = SPI_MODE1 << SPI_CTRL_MODE_SHIFT,   /*!< SPI Mode 1 Enable - sampling at second edge, first edge is rising  */
    SPI_CTRL_MODE2   = SPI_MODE2 << SPI_CTRL_MODE_SHIFT,   /*!< SPI Mode 2 Enable - sampling at first edge,  first edge is falling */
    SPI_CTRL_MODE3   = SPI_MODE3 << SPI_CTRL_MODE_SHIFT,   /*!< SPI Mode 3 Enable - sampling at second edge, first edge is falling */
    SPI_CTRL_MODE_MASK = 0x03    << SPI_CTRL_MODE_SHIFT,

    SPI_CTRL_FLEN8   = SPI_FLEN8  << SPI_CTRL_FLEN_SHIFT,  /*!< 8 Bits Per Frame                                                   */
    SPI_CTRL_FLEN16  = SPI_FLEN16 << SPI_CTRL_FLEN_SHIFT,  /*!< 16 Bits Per Frame                                                  */
    SPI_CTRL_FLEN24  = SPI_FLEN24 << SPI_CTRL_FLEN_SHIFT,  /*!< 24 Bits Per Frame                                                  */
    SPI_CTRL_FLEN32  = SPI_FLEN32 << SPI_CTRL_FLEN_SHIFT,  /*!< 32 Bits Per Frame                                                  */
    SPI_CTRL_FLEN_MASK = 0x03     << SPI_CTRL_FLEN_SHIFT,

    SPI_CTRL_PRESCALER_MASK = 0xFF00,
};

/** SPI interrupt mask */
typedef enum
{
    SPI_TXCIE     = 0x01,  /*!< Transmission Complete Interrupt Enable        */
    SPI_TXDREIE   = 0x02,  /*!< Transmit Data Register Empty Interrupt Enable */
    SPI_RDRFIE    = 0x04,  /*!< Receive Data Register Empty Interrupt Enable  */
    SPI_OVRIE     = 0x08,  /*!< Overrun Error Interrupt Enable                */
    SPI_NSSREIE   = 0x10,  /*!< NSS Rising Edge Interrupt Enable              */
    SPI_NSSFEIE   = 0x20,  /*!< NSS Falling Edge Interrupt Enable             */
    SPI_UNRIE     = 0x40,  /*!< Underrun Error Interrupt Enable               */
} amba_spi_irqm_t;

/** Helper macro for calculating prescaller value in SPI Control Register */
#define SPI_CTRL_PRESC(fsck, fpclk) ((fpclk) / ((fsck) * 2) - 1)

/** @} */

#endif /* __CCPROC_AMBA_SPI_H */
/** @} */
