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
    uint32_t STATUS;    /*!< Control Register           */
    uint32_t FLUSH;     /*!< Flush Tag Memory           */
    uint32_t INFO;      /*!< Cache Info Register        */
} dcache_regs_t;

static volatile dcache_regs_t * const DCACHE_PTR = (dcache_regs_t*)DCACHE_BASE;

/** DCC Status Register bits */
enum
{
    DCACHE_STAT_EN    = 1 << 0,  /*!< Data Cache Enable                     */
    DCACHE_STAT_FLUSH = 1 << 1,  /*!< Data Cache Flush in Progress          */
    DCACHE_STAT_BUSY  = 1 << 2,  /*!< Data Cache Write Buffer Busy          */
};

/** DCC Info Register bit offsets */
enum
{
    DCACHE_DCWAY_SHIFT   = 0,  /*!< Data Cache Ways Offset        */
    DCACHE_DCSIZE_SHIFT  = 3,  /*!< Data Cache Size Offset        */
    DCACHE_DCLINE_SHIFT  = 8,  /*!< Data Cache Line Offset        */
    DCACHE_DCALG_SHIFT   = 13, /*!< Data Cache Algorithm Offset   */
    DCACHE_DCTAG_SHIFT   = 15, /*!< Data Cache Tag Offset         */
};

/** DCC Info Register masks */
enum
{
    DCACHE_DCWAY_MASK  = 0x03 << DCACHE_DCWAY_SHIFT,   /*!< Data Cache Ways Mask       */
    DCACHE_DCSIZE_MASK = 0x1F << DCACHE_DCSIZE_SHIFT,  /*!< Data Cache Size Mask       */
    DCACHE_DCLINE_MASK = 0x0F << DCACHE_DCLINE_SHIFT,  /*!< Data Cache Line Mask       */
    DCACHE_DCALG_MASK  = 0x03 << DCACHE_DCALG_SHIFT,   /*!< Data Cache Algorithm Mask  */
    DCACHE_DCTAG_MASK  = 0x7F << DCACHE_DCTAG_SHIFT,   /*!< Data Cache Tag Mask        */
};

/** @} */

#endif /* __CCPROC_DCACHE_H */
/** @} */
