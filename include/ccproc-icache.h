/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2019-05-16 23:26:56 +0200 (czw, 16 maj 2019) $
* $Revision: 419 $
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
 * @file            ccproc-icache.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_ICACHE_H
#define __CCPROC_ICACHE_H

#include <stdint.h>

/************************//**
 * @defgroup icache Instruction Cache Controller
 * Instruction Cache Controller registers and definitions
 * @{
 *//************************/

/** Instruction Cache Controller Registers */
typedef struct
{
    uint32_t STATUS;          /*!< Status Register                  */
    uint32_t FLUSH;           /*!< Flush Tag Memory                 */
    uint32_t INFO;            /*!< Cache Info Register              */
    uint32_t ERR_CNT_0;       /*!< Error Counter 0 (FT-only)        */
    uint32_t ERR_CNT_1;       /*!< Error Counter 1 (FT-only)        */
    uint32_t INJECT_MASK_LO;  /*!< Error Injection Mask (FT-only)   */
    uint32_t INJECT_MASK_HI;  /*!< Error Injection Mask (FT-only)   */
} icache_regs_t;

static volatile icache_regs_t * const ICACHE_PTR = (icache_regs_t*)ICACHE_BASE;

/** ICC Status Register bits */
enum
{
    ICACHE_STAT_EN              = 1 << 0,  /*!< Instruction Cache Enable                 */
    ICACHE_STAT_PARITY_EN       = 1 << 3,  /*!< Parity Enable (FT-only)                  */
    ICACHE_STAT_ERR_TRIG        = 1 << 4,  /*!< Error Count Trigger (FT-only)            */
    ICACHE_STAT_SCRAMBLE_EN     = 1 << 5,  /*!< Scramble Enable (FT-only)                */
    ICACHE_STAT_MEM_ERR_INJECT  = 1 << 6,  /*!< Memory Error Injection Enable (FT-only)  */
    ICACHE_STAT_TAG_ERR_INJECT  = 1 << 7,  /*!< Tag Error Injection Enable (FT-only)     */
};

/** ICC Info Register bit offsets */
enum
{
    ICACHE_ICWAY_SHIFT   = 0,  /*!< Instruction Cache Ways Offset           */
    ICACHE_ICSIZE_SHIFT  = 3,  /*!< Instruction Cache Size Offset           */
    ICACHE_ICLINE_SHIFT  = 8,  /*!< Instruction Cache Line Offset           */
    ICACHE_ICALG_SHIFT   = 13, /*!< Instruction Cache Algorithm Offset      */
    ICACHE_ICTAG_SHIFT   = 15, /*!< Instruction Cache Tag Offset            */
    ICACHE_IMPL_SHIFT    = 28, /*!< Instruction Cache Implementation Offset */
};

/** ICC Info Register masks */
enum
{
    ICACHE_ICWAY_MASK  = 0x03 << ICACHE_ICWAY_SHIFT,   /*!< Instruction Cache Ways Mask           */
    ICACHE_ICSIZE_MASK = 0x1F << ICACHE_ICSIZE_SHIFT,  /*!< Instruction Cache Size Mask           */
    ICACHE_ICLINE_MASK = 0x0F << ICACHE_ICLINE_SHIFT,  /*!< Instruction Cache Line Mask           */
    ICACHE_ICALG_MASK  = 0x03 << ICACHE_ICALG_SHIFT,   /*!< Instruction Cache Algorithm Mask      */
    ICACHE_ICTAG_MASK  = 0x7F << ICACHE_ICTAG_SHIFT,   /*!< Instruction Cache Tag Mask            */
    ICACHE_IMPL_MASK   = 0x0F << ICACHE_IMPL_SHIFT,    /*!< Instruction Cache Implementation Mask */
};

/** ICC Implementation */
enum
{
    ICACHE_IMPL_HP = 0x00, /*!< High-performance instruction cache implementation */
    ICACHE_IMPL_FT = 0x03, /*!< Fault-tolerant instruction cache implementation   */
};

/** @} */

#endif /* __CCPROC_ICACHE_H */
/** @} */
