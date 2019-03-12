/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2018-09-07 16:07:40 +0200 (pią) $
* $Revision: 296 $
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
 * @file            ccproc-gnss.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_GNSS_H
#define __CCPROC_GNSS_H

#include <stdint.h>
#include "ccproc.h"

/************************//**
 * @defgroup gnss GNSS Controller
 * GNSS Controller registers and definitions
 * @{
 *//************************/

/** GNSS Controller Registers */
typedef struct
{
    uint32_t STATUS;    /*!< Status Register                                      */
    uint32_t COUNT;     /*!< Count Register                                       */
    uint32_t ADDRI;     /*!< I Array Address                                      */
    uint32_t ADDRQ;     /*!< Q Array Address                                      */
    uint32_t COUNTI;    /*!< Remaining I Count Register                           */
    uint32_t COUNTQ;    /*!< Remaining Q Count Register                           */
    uint32_t CTRL;      /*!< GNSS-ISE Control Register                            */
    uint32_t TICKF;     /*!< GNSS-ISE Code Tick Interrupt Flags Register          */
    uint32_t OVRF;      /*!< GNSS-ISE Code Tick Overrun Interrupt Flags Register  */
    uint32_t ERRF;      /*!< GNSS-ISE Code Error Interrupt Flags Register         */
    uint32_t IRQMAP;    /*!< Interrupt Mapping Register                           */
    uint32_t FIFOCNT;   /*!< FIFO Count Override (for diagnostics only)           */
    uint32_t FIFOWR;    /*!< FIFO Write Override (for diagnostics only)           */
    uint32_t TMSTMP_LO; /*!< Timestamp LO                                         */
    uint32_t TMSTMP_HI; /*!< Timestamp HI                                         */
    uint32_t ADCVAL;    /*!< Test ADC input (for diagnostics only)                */
} gnss_regs_t;

static volatile gnss_regs_t * const GNSS_PTR = (gnss_regs_t*)GNSS_BASE;

#define GNSS_I_FIFO_BASE (GNSS_BASE+0x6000)       /*!< GNSS Real FIFO base address (for diagnostics, access only by core 0)        */
#define GNSS_Q_FIFO_BASE (GNSS_BASE+0x6400)       /*!< GNSS Imaginary FIFO base address (for diagnostics, access only by core 0)   */
#define GNSS_FIFO_SIZE   256                      /*!< GNSS FIFO size in 32-bit words                                              */

#define GNSS_CODE_BASE   (GNSS_BASE+0x8000)       /*!< GNSS-ISE code memory base address (for diagnostics only)                    */

/** GNSS Controller Status Register Flags */
enum
{
    GNSS_STAT_L1      = 1 << 0,  /*!< GNSS L1 Available                           */
    GNSS_STAT_L5      = 1 << 1,  /*!< GNSS L5 Available                           */
    GNSS_STAT_L2      = 1 << 2,  /*!< GNSS L2 Available                           */
    GNSS_STAT_L1_EN   = 1 << 4,  /*!< Enable L1 FIFO                              */
    GNSS_STAT_L5_EN   = 1 << 5,  /*!< Enable L5 FIFO                              */
    GNSS_STAT_L2_EN   = 1 << 6,  /*!< Enable L2 FIFO                              */
    GNSS_STAT_MODE    = 1 << 10, /*!< GNSS FIFO Mode                              */
    GNSS_STAT_BUSY    = 1 << 12, /*!< GNSS FIFO Busy                              */
    GNSS_STAT_START   = 1 << 13, /*!< GNSS FIFO Start                             */
    GNSS_STAT_ERR     = 1 << 16, /*!< GNSS FIFO Error                             */
    GNSS_STAT_OVF_I   = 1 << 17, /*!< GNSS FIFO I Overflow                        */
    GNSS_STAT_OVF_Q   = 1 << 18, /*!< GNSS FIFO Q Overflow                        */
    GNSS_STAT_ACQIE   = 1 << 20, /*!< Acquisition Interrupt Enable                */
    GNSS_STAT_ACQIF   = 1 << 21, /*!< Acquisition Interrupt Flag                  */
};

/** GNSS Controller Status Register bit offsets */
enum
{
    GNSS_STAT_RFAFE_SHIFT  = 8,   /*!< GNSS RF AFE Shift        */
};

/** GNSS Controller Status Register masks */
enum
{
    GNSS_STAT_RFAFE_MASK   = 0x03 << GNSS_STAT_RFAFE_SHIFT,  /*!< GNSS RF AFE Mask       */
};

/** GNSS Controller Status RF AFE */
enum
{
    GNSS_RFAFE_L1     = 0x0,  /*!< GNSS L1 RF AFE              */
    GNSS_RFAFE_L5     = 0x1,  /*!< GNSS L5 RF AFE              */
    GNSS_RFAFE_L2     = 0x2,  /*!< GNSS L2 RF AFE              */
};

/** GNSS Controller GNSS-ISE Control Register Flags */
enum
{
    GNSS_CTRL_CODE_TICK_IE   = 0x1,  /*!< GNSS-ISE Code Tick Interrupt Enable            */
    GNSS_CTRL_CODE_OVR_IE    = 0x2,  /*!< GNSS-ISE Code Overrun Interrupt Enable         */
    GNSS_CTRL_CODE_ERR_IE    = 0x4,  /*!< GNSS-ISE Code Error Interrupt Enable           */
};

/**
 * @name GNSS Controller Status Register macros
 * @{
 */
#define GNSS_STATUS_GET_RFAFE(status)  ((status & GNSS_STAT_RFAFE_MASK) >> GNSS_STAT_RFAFE_SHIFT)  /*!< Gets GNSS RF AFE     */
#define GNSS_STATUS_BUILD_RFAFE(rfafe) ((rfafe << GNSS_STAT_RFAFE_SHIFT) & GNSS_STAT_RFAFE_MASK)   /*!< Builds GNSS RF AFE   */
/** @} */

/** @} */

#endif /* __CCPROC_GNSS_H */
/** @} */
