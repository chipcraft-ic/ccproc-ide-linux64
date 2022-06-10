/* ----------------------------------------------------------------------
*
* Copyright (c) 2020 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2022-03-21 13:29:18 +0100 (pon, 21 mar 2022) $
* $Revision: 831 $
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
 * @file            ccproc-viterbi.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_VITERBI_H
#define __CCPROC_VITERBI_H

#include <stdint.h>
#include "ccproc.h"

/************************//**
 * @defgroup viterbi Viterbi Decoder Controller
 * Viterbi Decoder Controller registers and definitions
 * @{
 *//************************/

/** Viterbi Decoder Controller Registers */
typedef struct
{
    uint32_t STATUS;    /*!< Status Register                */
    uint32_t CTRL;      /*!< Control Register               */
    uint32_t DATA_IN;   /*!< Data Input Register            */
    uint32_t DATA_OUT;  /*!< Data Output Register           */
} viterbi_regs_t;

static volatile viterbi_regs_t * const VITERBI_PTR = (viterbi_regs_t*)VITERBI_BASE;

/** Viterbi Decoder Status Register Flags */
enum
{
    VIT_STAT_BUSY     = 1 << 0,  /*!< Viterbi Decoder Busy                                  */
    VIT_STAT_FIN_PROG = 1 << 1,  /*!< Viterbi Decoder Programmable Final State              */
};

/** Viterbi Decoder Status Register bit offsets */
enum
{
    VIT_STAT_MAX_LEN_SHIFT  = 16,   /*!< Message Max Length Shift          */
};

/** Viterbi Decoder Status Register masks */
enum
{
    VIT_STAT_MAX_LEN_MASK   = 0xFFFF << VIT_STAT_MAX_LEN_SHIFT,   /*!< Message Max Length Mask           */
};

/** Viterbi Decoder Control Register Flags */
enum
{
    VIT_CTRL_INVG2    = 1 << 18,  /*!< Invert G2 Branch                    */
    VIT_CTRL_CFGEN    = 1 << 19,  /*!< Load Decoder Configuration          */
    VIT_CTRL_START    = 1 << 31,  /*!< Start Processing                    */
};

/** Viterbi Decoder Control Register bit offsets */
enum
{
    VIT_CTRL_LEN_SHIFT   = 0,   /*!< Message Length Shift          */
    VIT_CTRL_INIT_SHIFT  = 12,  /*!< Viterbi Initial State Shift   */
    VIT_CTRL_FINAL_SHIFT = 20,  /*!< Viterbi Final State Shift     */
};

/** Viterbi Decoder Control Register masks */
enum
{
    VIT_CTRL_LEN_MASK   = 0xFFF << VIT_CTRL_LEN_SHIFT,    /*!< Message Length Mask           */
    VIT_CTRL_INIT_MASK  = 0x3F  << VIT_CTRL_INIT_SHIFT,   /*!< Viterbi Initial State Mask    */
    VIT_CTRL_FINAL_MASK = 0x3F  << VIT_CTRL_FINAL_SHIFT,  /*!< Viterbi Final State Mask      */
};

/** @} */

#endif /* __CCPROC_VITERBI_H */
/** @} */

