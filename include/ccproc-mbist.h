/* ----------------------------------------------------------------------
*
* Copyright (c) 2019 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2024-08-19 09:13:00 +0200 (pon, 19 sie 2024) $
* $Revision: 1100 $
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
 * @file            ccproc-mbist.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_MBIST_H
#define __CCPROC_MBIST_H

#include <stdint.h>

/************************//**
 * @defgroup mbist Memory BIST Controller
 * Memory BIST Controller registers and definitions
 * @{
 *//************************/

/** Power Management Controller Registers */
 typedef struct
{
    uint32_t RUN;           /*!< Run Register               */
    uint32_t CTRL;          /*!< Control Register           */
    uint32_t INJ;           /*!< Injection Control Register */
    uint32_t INJ_ADDR0;     /*!< Port0 Address Register     */
    uint32_t INJ_ADDR1;     /*!< Port1 Address Register     */
    uint32_t _reserved0[8];
    uint32_t SCRATCH0;      /*!< Scratch register 0         */
    uint32_t SCRATCH1;      /*!< Scratch register 1         */
    uint32_t EXT_LOGS;      /*!< External Logs Region       */
    uint32_t INT_LOGS;      /*!< Internal Logs Region       */
    uint32_t _reserved1[63];
    uint32_t MSC_LOGS;      /*!< Miscellaneous Logs Region  */
    uint32_t _reserved2[63];
    uint32_t DET_LOGS[26];  /*!< Detailed Logs Region       */
} mbist_regs_t;

static volatile mbist_regs_t * const MBIST_PTR = (mbist_regs_t*)MBIST_BASE;

#define MBIST_RUN_KEY  0x42495354 /*!< Memory BIST Run Key     */

/** MBIST Controller Control Register bit offsets */
enum
{
    MBIST_CTRL_ALG_SHIFT  = 0,  /*!< Algorithm selection shift */
    MBIST_CTRL_SEED_SHIFT = 7,  /*!< Seed selection shift      */
    MBIST_CTRL_CORE_SHIFT = 11, /*!< Core selection shift      */
    MBIST_CTRL_REGN_SHIFT = 16, /*!< Region selection shift    */
};

/** MBIST Controller Control Register masks */
enum
{
	MBIST_CTRL_ALG_MASK  = 0x0F << MBIST_CTRL_ALG_SHIFT,  /*!< Algorithm selection mask */
	MBIST_CTRL_SEED_MASK = 0x0F << MBIST_CTRL_SEED_SHIFT, /*!< Seed selection mask      */
	MBIST_CTRL_CORE_MASK = 0x1F << MBIST_CTRL_CORE_SHIFT, /*!< Core selection mask      */
	MBIST_CTRL_REGN_MASK = 0x1F << MBIST_CTRL_REGN_SHIFT, /*!< Region selection mask    */
};

/** MBIST Controller Control Register bits */
enum
{
    MBIST_CTRL_SINGLE       = 1 << 4,  /*!< Single MBIST run    */
    MBIST_CTRL_SECOND_PORT  = 1 << 5,  /*!< MBIST second port   */
    MBIST_CTRL_SWITCH_PORTS = 1 << 6,  /*!< MBIST switch ports  */
};

/** Memory BIST Algorithms */
enum
{
    MBIST_ALG_ZERO_ONE   = 0x00, /*!< Zero-one algorithm   */
    MBIST_ALG_MATS_P     = 0x01, /*!< MATS+ algorithm      */
    MBIST_ALG_MARCH_CM   = 0x02, /*!< March C- algorithm   */
    MBIST_ALG_MARCH_S2PF = 0x03, /*!< March s2PF algorithm */
    MBIST_ALG_MARCH_D2PF = 0x04, /*!< March d2PF algorithm */
};

/** MBIST Controller Fault Injection Register bit offsets */
enum
{
    MBIST_INJ_IDX_PORT0_SHIFT   = 8,  /*!< Fault injection port0 index shift */
    MBIST_INJ_IDX_PORT1_SHIFT   = 16, /*!< Fault injection port1 index shift */
};

/** MBIST Controller Fault Injection Register masks */
enum
{
	MBIST_INJ_IDX_PORT0_MASK    = 0xFF << MBIST_INJ_IDX_PORT0_SHIFT,  /*!< Fault injection port0 index mask */
	MBIST_INJ_IDX_PORT1_MASK    = 0xFF << MBIST_INJ_IDX_PORT1_SHIFT,  /*!< Fault injection port1 index mask */
};

/** MBIST Controller Fault Injection Register bits */
enum
{
    MBIST_INJ_PORT0_EN      = 1 << 0,  /*!< Port0 fault injection enable */
    MBIST_INJ_PORT1_EN      = 1 << 1,  /*!< Port1 fault injection enable */
};

/** @} */

#endif /* __CCPROC_MBIST_H */
/** @} */
