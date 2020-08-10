/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2020-07-22 21:42:29 +0200 (śro, 22 lip 2020) $
* $Revision: 614 $
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
 * @file            ccproc-mcore.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Rafal Harabien
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_MCORE_H
#define __CCPROC_MCORE_H

#include <stdint.h>

/************************//**
 * @defgroup multicore Multi-Core Controller
 * Multi-Core Controller registers and definitions
 * @{
 **/

/** Maximal number of cores */
#define MAX_NUM_OF_CORES 32

/** Multi-Core Controller Registers */
typedef struct
{
    uint32_t STATUS;         /*!< Core Status                         */
    uint32_t CORE_NUM;       /*!< Core Number                         */
    uint32_t CORE_SHDN;      /*!< Core Shut Down                      */
    uint32_t _reserved1[1];
    uint32_t CORE_ADDR[32];  /*!< Core Start Address                  */
    uint32_t _reserved2[18];
    uint32_t CORE_RUN[32];   /*!< Core Start Register                 */
    uint32_t _reserved3[32];
    uint32_t INJECT_MASK_0;  /*!< Core 0 Error Inject Mask (FT-only)  */
    uint32_t INJECT_MASK_1;  /*!< Core 1 Error Inject Mask (FT-only)  */
    uint32_t DEADLOCK_MAX;   /*!< Core Deadlock Counter Max (FT-only) */
} multicore_regs_t;

static volatile multicore_regs_t * const MCORE_PTR = (multicore_regs_t*)MCORE_BASE;

#define MCORE_RUN_KEY   0x000000A5  /*!< Core Run Key        */
#define MCORE_SHDN_KEY  0xA5000000  /*!< Core Shut Down Key  */

/** @} */

#endif /* __CCPROC_MCORE_H */
/** @} */

