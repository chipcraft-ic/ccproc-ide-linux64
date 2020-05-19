/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2019-10-03 19:22:07 +0200 (czw, 03 paź 2019) $
* $Revision: 474 $
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
 * @file            ccproc-amba-rtc.h
 * @brief           CCRV32 Processor AMBA RTC definitions
 * @author          Rafal Harabien
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_RTC_H
#define __CCPROC_AMBA_RTC_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup rtc Real-Time Clock
 * RTC Controller registers and definitions
 * @{
 *//************************/

/** RTC Registers */
typedef struct
{
    uint32_t CTRL;           /*!< Control Register                */
    uint32_t SHDNCTRL;       /*!< Shutdown Control Register       */
    uint32_t STATUS;         /*!< Status Register                 */
    uint32_t PRES;           /*!< Prescaler Register (16 bit)     */
    uint32_t PER;            /*!< Period Register (32 bit)        */
    uint32_t COMPARE;        /*!< Compare Register (32 bit)       */
    uint32_t COUNT;          /*!< Count Register (32 bit)         */
    uint32_t WKUP0DBCN;      /*!< Wakeup Debounce Config Register */
    uint32_t IRQM;           /*!< Interrupt Mask Register         */
    uint32_t IRQF;           /*!< Interrupt Flags Register        */
    uint32_t IRQMAP;         /*!< Interrupt Mapping Register      */
    uint32_t BACKUP0;        /*!< Backup 0 Register               */
    uint32_t BACKUP1;        /*!< Backup 1 Register               */
    uint32_t BACKUP2;        /*!< Backup 2 Register               */
    uint32_t BACKUP3;        /*!< Backup 3 Register               */
    uint32_t TMSTMPCTRL;     /*!< Timestamp Control Register      */
    uint32_t TMSTMPSTAT;     /*!< Timestamp Status Register       */
    uint32_t TMSTMP;         /*!< Timestamp Register              */
} amba_rtc_t;

#ifdef CCPROC_SDK
 static volatile amba_rtc_t * const AMBA_RTC_PTR = (amba_rtc_t*)AMBA_RTC_BASE;  /*!< RTC pointer  */
#endif

/** RTC Control Register Flags */
enum
{
    RTC_CTRL_EN          = 0x00000001,  /*!< RTC Enable bit                       */
    RTC_CTRL_WKUPOVF     = 0x00000002,  /*!< Overflow Wakeup Enable               */
    RTC_CTRL_WKUPCMP     = 0x00000004,  /*!< Compare Match Wakeup Enable          */
    RTC_CTRL_WKUPWK0     = 0x00000008,  /*!< WKUP0 Wakeup Enable                  */
    RTC_CTRL_SHDNROVF    = 0x00000010,  /*!< SHND Release on Overflow Enable      */
    RTC_CTRL_SHDNRCMP    = 0x00000020,  /*!< SHND Release on Compare Match Enable */
    RTC_CTRL_SHDNRWK0    = 0x00000040,  /*!< SHND Release on WKUP0 Enable         */
    RTC_CTRL_SHDNINV     = 0x00000080,  /*!< SHND Inverted                        */
    RTC_CTRL_WKUP0R      = 0x00000100,  /*!< SHND Rising Edge Detection           */
    RTC_CTRL_WKUP0F      = 0x00000200,  /*!< SHND Falling Edge Detection          */
    RTC_CTRL_DBG_STOP    = 0x80000000,  /*!< Stop counting in debug mode          */
};

/** RTC Shutdown Control Register Flags */
enum
{
    RTC_SHDNCTRL_SHDNEN     = 0x00000001,  /*!< RTC SHDN Enable  */
    RTC_SHDNCTRL_SHDROVF    = 0x00000002,  /*!< RTC SHDN Release on Overflow  */
    RTC_SHDNCTRL_SHDRCMP    = 0x00000004,  /*!< RTC SHDN Release on Compare Match  */
    RTC_SHDNCTRL_SHDRWK0    = 0x00000008,  /*!< RTC SHDN Release on WKUP0 Event  */
    RTC_SHDNCTRL_ACCK_MASK  = 0xFF000000,  /*!< RTC SHDN Access Key  */
};

#define RTC_ACCESS_KEY 0xA5000000 /*!< RTC Access Key */

/** RTC Status Register Flags */
enum
{
    RTC_STAT_BUSY  = 0x00000001,  /*!< RTC Busy Flag  */
};

/** RTC Interrupt Mask Bits */
enum
{
    RTC_OVFIE     = 0x1,  /*!< Overflow Interrupt Enable            */
    RTC_CMPIE     = 0x2,  /*!< Compare Match Interrupt Enable       */
    RTC_WKUP0IE   = 0x4,  /*!< WKUP0 Interrupt Enable               */
    RTC_READYIE   = 0x8,  /*!< READY Interrupt Enable               */
    RTC_TRERRIE   = 0x10, /*!< Transmission Error Interrupt Enable  */
    RTC_TSCAPTIE  = 0x20  /*!< Timestamp Captured Interrupt Eanble  */
};

/** RTC Interrupt Flags */
enum
{
    RTC_OVFIF     = 0x1,  /*!< Overflow Interrupt Flag              */
    RTC_CMPIF     = 0x2,  /*!< Compare Match Interrupt Flag         */
    RTC_WKUP0IF   = 0x4,  /*!< WKUP0 Interrupt Flag                 */
    RTC_READYIF   = 0x8,  /*!< READY Interrupt Flag                 */
    RTC_TRERRIF   = 0x10, /*!< Transmission Error Interrupt Flag    */
    RTC_TSCAPTIF  = 0x20  /*!< Timestamp Captured Interrupt Flag    */
};

/** @} */

#endif /* __CCPROC_AMBA_RTC_H */
/** @} */
