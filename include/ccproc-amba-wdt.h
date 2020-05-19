/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2018-09-07 16:07:40 +0200 (pią, 07 wrz 2018) $
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
 * @file            ccproc-amba-wdt.h
 * @brief           CC Processor AMBA WATCHDOG definitions
 * @author          Rafal Harabien
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_WDT_H
#define __CCPROC_AMBA_WDT_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup wdt Watchdog Timer
 * Watchdog Timer registers and definitions
 * @{
 *//************************/

/** Watchdog Registers */
typedef struct
{
    uint32_t LOCK;        /*!< Lock Register          */
    uint32_t CTRL;        /*!< Control Register       */
    uint32_t COUNT;       /*!< Count Register         */
    uint32_t PER;         /*!< Period Register        */
    uint32_t PERCL;       /*!< Period Closed Register */
    uint32_t PRES;        /*!< Prescaler Register     */
} amba_wdt_t;

#ifdef CCPROC_SDK
 static volatile amba_wdt_t * const AMBA_WDT_PTR = (amba_wdt_t*)AMBA_WDT_BASE;  /*!< Watchdog pointer  */
#endif

/** Watchdog Lock Register Flags */
enum
{
    WDT_LOCK_CTRL   = 0x1,  /*!< Control Register Lock       */
    WDT_LOCK_PER    = 0x2,  /*!< Period Register Lock        */
    WDT_LOCK_PERCL  = 0x4,  /*!< Period Closed Register Lock */
    WDT_LOCK_PRES   = 0x8,  /*!< Prescaler Register Lock     */
};

/** Watchdog Control Register Flags */
enum
{
    WDT_CTRL_EN          = 0x00000001,  /*!< Module Enable bit           */

    WDT_CTRL_MODE_NORMAL = 0x00000000,  /*!< Normal Mode                 */
    WDT_CTRL_MODE_WINDOW = 0x00000002,  /*!< Window Mode                 */

    WDT_CTRL_DBG_STOP    = 0x80000000,  /*!< Stop counting in debug mode */
};

/** @} */

#endif /* __CCPROC_AMBA_WDT_H */
/** @} */
