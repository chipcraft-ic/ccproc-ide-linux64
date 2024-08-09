/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2024-01-14 21:55:43 +0100 (nie, 14 sty 2024) $
* $Revision: 1038 $
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
 * @file            ccproc-dcache.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_DCACHE_H
#define __CCPROC_DCACHE_H

#include <stdint.h>

/************************//**
 * @defgroup dcache Data Cache Controller
 * Data Cache Controller registers and definitions
 * @{
 *//************************/

/** Data Cache Registers */
typedef struct
{
    uint32_t STCR;              /*!< Status and Control Register      */
    uint32_t FLUSH;             /*!< Flush Tag Memory                 */
    uint32_t INFO;              /*!< Cache Info Register              */
    uint32_t ERR_CNT_0;         /*!< Error Counter 0 (FT-only)        */
    uint32_t ERR_CNT_1;         /*!< Error Counter 1 (FT-only)        */
    uint32_t INJECT_MASK_LO;    /*!< Error Injection Mask (FT-only)   */
    uint32_t INJECT_MASK_HI;    /*!< Error Injection Mask (FT-only)   */
    uint32_t ERR_ADDR;          /*!< Error Address (FT-only)          */
    uint32_t ERR_STAT;          /*!< Error Statistics (FT-only)       */
} dcache_regs_t;

static volatile dcache_regs_t * const DCACHE_PTR = (dcache_regs_t*)DCACHE_BASE;

/** DCC Status Register bits */
enum
{
    DCACHE_STCR_EN                = 1 << 0,  /*!< Data Cache Enable                                             */
    DCACHE_STCR_FLUSH             = 1 << 1,  /*!< Data Cache Flush in Progress (not available in lockstep mode) */
    DCACHE_STCR_BUSY              = 1 << 2,  /*!< Data Cache Write Buffer Busy (not available in lockstep mode) */
    DCACHE_STCR_ECC_EN            = 1 << 3,  /*!< ECC Enable (FT-only)                                          */
    DCACHE_STCR_ERR_TRIG          = 1 << 4,  /*!< Error Count Trigger (FT-only)                                 */
    DCACHE_STCR_SCRAMBLE_EN       = 1 << 5,  /*!< Scramble Enable (FT-only)                                     */
    DCACHE_STCR_MEM_ERR_INJECT    = 1 << 6,  /*!< Memory Error Injection Enable (FT-only)                       */
    DCACHE_STCR_TAG_ERR_INJECT    = 1 << 7,  /*!< Tag Error Injection Enable (FT-only)                          */
    DCACHE_STCR_HARD_ERR_EN       = 1 << 8,  /*!< Hard error enable (FT-only)                                   */
};

/** DCC Info Register bit offsets */
enum
{
    DCACHE_DCWAY_SHIFT   = 0,  /*!< Data Cache Ways Offset            */
    DCACHE_DCSIZE_SHIFT  = 3,  /*!< Data Cache Size Offset            */
    DCACHE_DCLINE_SHIFT  = 8,  /*!< Data Cache Line Offset            */
    DCACHE_DCALG_SHIFT   = 13, /*!< Data Cache Algorithm Offset       */
    DCACHE_DCTAG_SHIFT   = 15, /*!< Data Cache Tag Offset             */
    DCACHE_IMPL_SHIFT    = 28, /*!< Data Cache Implementation Offset  */
};

/** DCC Info Register masks */
enum
{
    DCACHE_DCWAY_MASK  = 0x07 << DCACHE_DCWAY_SHIFT,   /*!< Data Cache Ways Mask           */
    DCACHE_DCSIZE_MASK = 0x1F << DCACHE_DCSIZE_SHIFT,  /*!< Data Cache Size Mask           */
    DCACHE_DCLINE_MASK = 0x0F << DCACHE_DCLINE_SHIFT,  /*!< Data Cache Line Mask           */
    DCACHE_DCALG_MASK  = 0x03 << DCACHE_DCALG_SHIFT,   /*!< Data Cache Algorithm Mask      */
    DCACHE_DCTAG_MASK  = 0x7F << DCACHE_DCTAG_SHIFT,   /*!< Data Cache Tag Mask            */
    DCACHE_IMPL_MASK   = 0x0F << DCACHE_IMPL_SHIFT,    /*!< Data Cache Implementation Mask */
};

/** DCC Implementation */
enum
{
    DCACHE_IMPL_HP = 0x00, /*!< High-performance data cache implementation */
    DCACHE_IMPL_HS = 0x01, /*!< High-speed data cache implementation       */
    DCACHE_IMPL_LP = 0x02, /*!< Low-power data cache implementation        */
    DCACHE_IMPL_FT = 0x03, /*!< Fault-tolerant data cache implementation   */
};

/** @} */

#endif /* __CCPROC_DCACHE_H */
/** @} */
