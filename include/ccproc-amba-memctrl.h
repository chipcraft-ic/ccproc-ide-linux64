/* ----------------------------------------------------------------------
*
* Copyright (c) 2019 ChipCraft Sp. z o.o. All rights reserved
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
 * @file            ccproc-amba-memctrl.h
 * @brief           CC Processor AMBA External Memory Controller definitions
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_MEMCTRL_H
#define __CCPROC_AMBA_MEMCTRL_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup memctrl External Memory Controller
 * External Memory Controller registers and definitions
 * @{
 *//************************/

/** External Memory Controller Registers */
typedef struct
{
    uint32_t STATUS;                    /*!< Status Register                      */
    uint32_t CONF;                      /*!< Config Register                      */
    uint32_t COMMAND;                   /*!< Command Register                     */
    uint32_t IRQ;                       /*!< Interrupt Register                   */
    uint32_t _reserved0[12];
    uint32_t COMMAND_DATA[2];           /*!< Command Data Register                */
    uint32_t DEVICE_DATA;               /*!< Device Data Register                 */
    uint32_t _reserved1[109];
    uint32_t DEVICE_CONF[8];            /*!< Device Configuration Register        */
    uint32_t _reserved2[8];
    uint32_t DEVICE_ADDR_HI[8];         /*!< Device High Address Register         */
    uint32_t _reserved3[8];
    uint32_t DEVICE_ADDR_LO[8];         /*!< Device Low Address Register          */
} amba_memctrl_t;

#ifdef CCPROC_SDK
 static volatile amba_memctrl_t * const AMBA_MEMCTRL_PTR = (amba_memctrl_t*)AMBA_MEMCTRL_BASE;  /*!< External Memory Controller pointer  */
#endif

/** Device Configuration Flags */
enum
{
    MEMCTRL_DEVICE_CONF_EN        = 1 << 9,  /*!< Device Enable                */
};

/** Device Configuration Register bit offsets */
enum
{
    MEMCTRL_DEVICE_CONF_LATENCY_SHIFT  = 0,  /*!< Device Latency Shift         */
};

/** Device Configuration Register masks */
enum
{
    MEMCTRL_DEVICE_CONF_LATENCY_MASK   = 0x23F << MEMCTRL_DEVICE_CONF_LATENCY_SHIFT,  /*!< Device Latency Mask       */
};

#define MEMCTRL_BUILD_LATENCY(latency) ((latency << MEMCTRL_DEVICE_CONF_LATENCY_SHIFT) & MEMCTRL_DEVICE_CONF_LATENCY_MASK)  /*!< Device Latency Build Macro */

/** External Memory Controller Configuration Flags */
enum
{
    MEMCTRL_CONF_CKPAD_EN     = 1 << 9,  /*!< Clock Pad Enable                */
    MEMCTRL_CONF_CSPAD_EN     = 1 << 10, /*!< Chip Select Pad Enable          */
    MEMCTRL_CONF_CKMST_EN     = 1 << 31, /*!< Master Clock Enable             */
};

/** External Memory Controller Configuration Register bit offsets */
enum
{
    MEMCTRL_CONF_BURST_SHIFT    = 12, /*!< Transfer Burst Shift         */
    MEMCTRL_CONF_PRES_SHIFT     = 16, /*!< Clock Prescaler Shift        */
};

/** External Memory Controller Configuration Register masks */
enum
{
    MEMCTRL_CONF_PRES_MASK   = 0xFF << MEMCTRL_CONF_PRES_SHIFT,  /*!< Clock Prescaler Mask */
    MEMCTRL_CONF_BURST_MASK  = 0x3  << MEMCTRL_CONF_BURST_SHIFT, /*!< Transfer Burst Mask  */
};

#define MEMCTRL_BUILD_PRESCALER(pres) ((pres << MEMCTRL_CONF_PRES_SHIFT) & MEMCTRL_CONF_PRES_MASK)  /*!< Clock Prescaler Build Macro */
#define MEMCTRL_BUILD_BURST(burst) ((burst << MEMCTRL_CONF_BURST_SHIFT) & MEMCTRL_CONF_BURST_MASK)  /*!< Burst Build Macro           */

/** @} */

#endif /* __CCPROC_AMBA_MEMCTRL_H */
/** @} */
