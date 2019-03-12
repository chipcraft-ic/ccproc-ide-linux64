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
 * @file            ccproc-debug.h
 * @brief           CC Processor Debugger definitions
 * @author          Rafal Harabien
 *
 * @defgroup        CCDBG On-Chip Debugger
 * Integrated debugger definitions
 * @{
 */

#ifndef __CCPROC_DEBUG_H
#define __CCPROC_DEBUG_H

#include <stdint.h>
#include "ccproc.h"

/** Additional Base Addresses in Debugger */
enum
{
    DBG_BREAKPOINTS_BASE = DEBUG_BASE + 0x00000000,  /*!< 4 hardware breakpoints                */
    DBG_WATCHPOINTS_BASE = DEBUG_BASE + 0x00000010,  /*!< 4 hardware watchpoints (read & write) */
    DBG_BURST_COUNT      = DEBUG_BASE + 0x00000020,  /*!< Burst Count Register                  */
    DBG_GPR_BASE         = DEBUG_BASE + 0x01000000,  /*!< 32 General Purpose Registers          */
    DBG_FPR_BASE         = DEBUG_BASE + 0x01000080,  /*!< 32 Floating Point Registers           */
    DBG_ICACHE_MEM_BASE  = DEBUG_BASE + 0x02000000,  /*!< Instruction Cache Memory              */
    DBG_ICACHE_TAG_BASE  = DEBUG_BASE + 0x02100000,  /*!< Instruction Cache Tag                 */
    DBG_DCACHE_MEM_BASE  = DEBUG_BASE + 0x02200000,  /*!< Data Cache Memory                     */
    DBG_DCACHE_TAG_BASE  = DEBUG_BASE + 0x02300000,  /*!< Data Cache Tag                        */
};

/**
 * @name Debugger Commands
 * @{
 */
#define DBG_OP_BREAK         'b'     /*!< Break if running                            */
#define DBG_OP_BREAKTEST     'B'     /*!< Get context if halted                       */
#define DBG_OP_ADDR          'a'     /*!< Change current address                      */
#define DBG_OP_READ          'm'     /*!< Read memory                                 */
#define DBG_OP_WRITE         'w'     /*!< Write memory                                */
#define DBG_OP_AUTOINC_ON    'I'     /*!< Enable current address auto-incrementation  */
#define DBG_OP_AUTOINC_OFF   'i'     /*!< Disable current address auto-incrementation */
#define DBG_OP_RUN           'f'     /*!< Continue                                    */
#define DBG_OP_STEP          's'     /*!< Step                                        */
#define DBG_OP_PROCRST       'r'     /*!< Reset processor                             */
#define DBG_OP_DEBUGRST      'R'     /*!< Reset debugger                              */
#define DBG_OP_CORESEL_BASE  '\xA0'  /*!< Change current core                         */
/** @} */

/** Standard Debugger Response */
#define DBG_ACK              '\x06'

/** Core Context Signature */
#define DBG_CORE_CTX_MARKER  '~'

/** Response for Break Condition */
#define DBG_BREAK_ACK        'U'

/**
 * @brief Core Context
 *
 * Note: processor sends 'packed' structure (no padding after core_num).
 *       It cannot be directly copied to this structure.
 */
typedef struct
{
    uint8_t  marker;   /*!< always DBG_CORE_CTX_MARKER       */
    uint8_t  core_num; /*!< core index                       */
    uint32_t addr;     /*!< address of instruction           */
    uint32_t instr;    /*!< opcode                           */
    uint32_t result;   /*!< result of arithmetic instruction */
    uint32_t data;     /*!< instruction dependent            */
    uint32_t lsaddr;   /*!< load/store address               */
    uint32_t ldata;    /*!< loaded data                      */
} dbg_core_context_t;

#endif /* __CCPROC_DEBUG_H */
/** @} */
