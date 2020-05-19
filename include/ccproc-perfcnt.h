/* ----------------------------------------------------------------------
*
* Copyright (c) 2018 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2019-10-21 09:43:30 +0200 (pon, 21 paź 2019) $
* $Revision: 477 $
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
 * @file            ccproc-perfcnt.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_PERFCNT_H
#define __CCPROC_PERFCNT_H

#include <stdint.h>

/************************//**
 * @defgroup perfcnt Performance Counter
 * Performance Counter registers and definitions
 * @{
 *//************************/

/** Performance Counter Registers */
typedef struct
{
    uint32_t STATUS;            /*!< Status Register                        */
    uint32_t CYCLE_LO;          /*!< Clock Cycle Counter LO                 */
    uint32_t CYCLE_HI;          /*!< Clock Cycle Counter HI                 */
} perfcnt_regs_t;

static volatile perfcnt_regs_t * const PERFCNT_PTR = (perfcnt_regs_t*)PERFCNT_BASE;

/** Performance Counter Status Register flags */
enum
{
    PERFCNT_STAT_EN       = 0x0001,     /*!< Performance Counter Enable      */
};

/** Performance Counter Status Register bit offsets */
enum
{
    PERFCNT_STAT_SRC_SHIFT   = 4,       /*!< Performance Counter Source Shift    */
    PERFCNT_STAT_BITS_SHIFT  = 16,      /*!< Performance Counter Bits Shift      */
};

/** Performance Counter Status Register masks */
enum
{
    PERFCNT_STAT_SRC_MASK   = 0xF << PERFCNT_STAT_SRC_SHIFT,     /*!< Performance Counter Source Mask     */
    PERFCNT_STAT_BITS_MASK  = 0x7F << PERFCNT_STAT_BITS_SHIFT,   /*!< Performance Counter Bits Mask       */
};

/** Performance Counter Sources */
enum
{
    PERFCNT_STAT_SRC_CORE   = 0x0,  /*!< Processor Clock Source       */
    PERFCNT_STAT_SRC_L1E1   = 0x1,  /*!< GNSS L1/E1 Source            */
    PERFCNT_STAT_SRC_L5E5   = 0x2,  /*!< GNSS L5/E5 Source            */
    PERFCNT_STAT_SRC_L2E6   = 0x3,  /*!< GNSS L2/E6 Source            */
    PERFCNT_STAT_SRC_VIRT   = 0x4,  /*!< GNSS Virtual Frontend Source */
};

/**
 * @name Performance Counter Status Register macros
 * @{
 */
#define PERFCNT_STATUS_GET_BITS(status)   ((status & PERFCNTT_STAT_BITS_MASK) >> PERFCNT_STAT_BITS_SHIFT)  /*!< Gets Performance Counter Bits     */
#define PERFCNT_STATUS_GET_SOURCE(status) ((status & PERFCNTT_STAT_SRC_MASK) >> PERFCNT_STAT_SRC_SHIFT)    /*!< Gets Performance Counter Source   */
/** @} */

/** @} */

#endif /* __CCPROC_PERFCNT_H */
/** @} */
