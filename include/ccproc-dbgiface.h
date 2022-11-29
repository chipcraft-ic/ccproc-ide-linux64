/* ----------------------------------------------------------------------
*
* Copyright (c) 2022 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2022-11-24 15:32:16 +0100 (czw, 24 lis 2022) $
* $Revision: 916 $
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
 * @file            ccproc-dbgiface.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_DBGIFACE_H
#define __CCPROC_DBGIFACE_H

#include <stdint.h>

/************************//**
 * @defgroup dbgiface Debug Interface Controller
 * Debug Interface Controller registers and definitions
 * @{
 *//************************/

/** Debug Interface Controller Registers */
 typedef struct
{
    uint32_t _reserved0[128];
    uint32_t CMD;      /*!< Command Register       */
    uint32_t ADDR;     /*!< Address Register       */
    uint32_t WDATA;    /*!< Write Date Register    */
    uint32_t RDATA;    /*!< Read Data Register     */
} dbgiface_regs_t;

static volatile dbgiface_regs_t * const DBGIFACE_PTR = (dbgiface_regs_t*)DBGIFACE_BASE;

/** Debug Interface Commands */
typedef enum
{
    DBGIFACE_CMD_IDLE       = 0,    /*!< Command Idle                           */
    DBGIFACE_CMD_READ       = 109,  /*!< Read Command                           */
    DBGIFACE_CMD_WRITE      = 119,  /*!< Write Command                          */
    DBGIFACE_CMD_CONTEXT    = 160,  /*!< Debug Context Command                  */
} dbgiface_cmd_t;

/** @} */

#endif /* __CCPROC_DBGIFACE_H */
/** @} */

