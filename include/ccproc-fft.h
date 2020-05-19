/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2019-01-09 12:10:59 +0100 (śro, 09 sty 2019) $
* $Revision: 374 $
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
 * @file            ccproc-fft.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_FFT_H
#define __CCPROC_FFT_H

#include <stdint.h>
#include "ccproc.h"

/************************//**
 * @defgroup fft FFT Controller
 * FFT Controller registers and definitions
 * @{
 *//************************/

/** FFT Controller Registers */
typedef struct
{
    uint32_t STATUS;    /*!< Status Register                */
    uint32_t REDLA;     /*!< RE Download Address            */
    uint32_t IMDLA;     /*!< IM Download Address            */
    uint32_t REULA;     /*!< RE Upload Address              */
    uint32_t IMULA;     /*!< IM Upload Address              */
    uint32_t IRQF;      /*!< Interrupt Flags Register       */
    uint32_t IRQMAP;    /*!< Interrupt Mapping Register     */
    uint32_t FFTSIZE;   /*!< Configure FFT Size             */
} fft_regs_t;

static volatile fft_regs_t * const FFT_PTR = (fft_regs_t*)FFT_BASE;

#define FFT_MEMORY_BASE (FFT_BASE+0x8000)       /*!< FFT Internal Memory base address */
static volatile uint32_t * const FFT_MEMORY_PTR = (uint32_t*)FFT_MEMORY_BASE; /*!< FFT Internal Memory pointer */

/** FFT Controller Status Register Flags */
enum
{
    FFT_STAT_BUSY    = 1 << 0,  /*!< FFT Busy                        */
    FFT_STAT_START   = 1 << 1,  /*!< FFT Start                       */
    FFT_STAT_FFT     = 1 << 2,  /*!< Perform FFT operation           */
    FFT_STAT_IFFT    = 1 << 3,  /*!< Inverse FFT                     */
    FFT_STAT_DL      = 1 << 4,  /*!< Download to internal memory     */
    FFT_STAT_DLREV   = 1 << 5,  /*!< Download with reverse bit order */
    FFT_STAT_DLSCL   = 1 << 6,  /*!< Download with data scale        */
    FFT_STAT_UL      = 1 << 7,  /*!< Upload from internal memory     */
    FFT_STAT_ULREV   = 1 << 8,  /*!< Upload with reverse bit order   */
    FFT_STAT_ULSCL   = 1 << 9,  /*!< Upload with data scale          */
    FFT_STAT_ABSSQR  = 1 << 10, /*!< Calculate absolute square       */
    FFT_STAT_CONJU   = 1 << 11, /*!< Calculate conjugate             */
    FFT_STAT_IE      = 1 << 12, /*!< Interrupt enable                */
    FFT_STAT_ERROR   = 1 << 13, /*!< Memory error indicator          */
};

/** FFT Controller Status Register bit offsets */
enum
{
    FFT_STAT_TASK_SHIFT  = 16,   /*!< FFT Task Shift        */
    FFT_STAT_SIZE_SHIFT  = 24,   /*!< FFT Size Shift        */
};

/** FFT Controller Status Register masks */
enum
{
    FFT_STAT_TASK_MASK   = 0x07 << FFT_STAT_TASK_SHIFT,  /*!< FFT Task Mask       */
    FFT_STAT_SIZE_MASK   = 0xFF << FFT_STAT_SIZE_SHIFT,  /*!< FFT Size Mask       */
};

/** FFT Interrupt Flags */
enum
{
    FFT_IRQ_FLAG         = 0x01,  /*!< Interrupt flag     */
    FFT_ERROR_FLAG       = 0x02,  /*!< Error flag         */
};

/** FFT Tasks */
enum
{
    FFT_TASK_IDLE        = 0x00,  /*!< Idle task             */
    FFT_TASK_DOWNLOAD    = 0x01,  /*!< Download task         */
    FFT_TASK_UPLOAD      = 0x02,  /*!< Upload task           */
    FFT_TASK_FFT         = 0x03,  /*!< FFT task              */
    FFT_TASK_ABSSQR      = 0x04,  /*!< Absolute square task  */
    FFT_TASK_CONJUATE    = 0x05,  /*!< Conjuate task         */
};

/**
 * @name FFT Controller Status Register macros
 * @{
 */
#define FFT_STATUS_GET_TASK(status) ((status & FFT_STAT_TASK_MASK) >> FFT_STAT_TASK_SHIFT)  /*!< Gets FFT Task      */
#define FFT_STATUS_GET_SIZE(status) ((status & FFT_STAT_SIZE_MASK) >> FFT_STAT_SIZE_SHIFT)  /*!< Gets FFT Size      */
/** @} */

/** @} */

#endif /* __CCPROC_FFT_H */
/** @} */
