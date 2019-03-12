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
 * @file            ccproc-amba-systick.h
 * @brief           CC Processor AMBA SYSTICK definitions
 * @author          Rafal Harabien
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_SYSTICK_H
#define __CCPROC_AMBA_SYSTICK_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup systick Systick Timer
 * Systick Timer registers and definitions
 * @{
 *//************************/

/** Systick Registers */
typedef struct
{
    uint32_t CTRL;    /*!< Control Register           */
    uint32_t COUNT;   /*!< Count Register (16 bit)    */
    uint32_t PER;     /*!< Period Register (16 bit)   */
    uint32_t PRES;    /*!< Prescaler Register (8 bit) */
    uint32_t IRQF;    /*!< Interrupt Flag Register    */
    uint32_t IRQMAP;  /*!< Interrupt Mapping Register */
} amba_systick_t;

#ifdef CCPROC_SDK
 static volatile amba_systick_t * const AMBA_SYSTICK_PTR = (amba_systick_t*)AMBA_SYSTICK_BASE;  /*!< Systick pointer  */
#endif

/** Systick Control Register flags */
enum
{
    SYSTICK_CTRL_EN       = 0x00000001,  /*!< Module Enable               */
    SYSTICK_CTRL_IE       = 0x00000002,  /*!< Interrupt Enable            */
    SYSTICK_CTRL_DBG_STOP = 0x80000000,  /*!< Stop counting in debug mode */
};

/** Systick Interrupt Flag Register bits */
enum
{
    SYSTICK_IF = 0x1,  /*!< Systick Interrupt Flag */
};

/** @} */

#endif /* __CCPROC_AMBA_SYSTICK_H */
/** @} */
