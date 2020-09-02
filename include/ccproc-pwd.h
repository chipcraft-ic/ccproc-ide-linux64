/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2020-08-30 22:54:21 +0200 (nie, 30 sie 2020) $
* $Revision: 632 $
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
 * @file            ccproc-pwd.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Rafal Harabien
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_PWD_H
#define __CCPROC_PWD_H

#include <stdint.h>

/************************//**
 * @defgroup pwd Power Management Controller
 * Power Management Controller registers and definitions
 * @{
 *//************************/

/** Power Management Controller Registers */
 typedef struct
{
    uint32_t CTRL;     /*!< Control                */
    uint32_t RSTRSN;   /*!< Reset Reason           */
    uint32_t PWDRST;   /*!< Power Management Reset */
    uint32_t DPRST;    /*!< Deep Reset             */
    uint32_t STAT;     /*!< Status Register        */
    uint32_t INFO;     /*!< Info Register          */
} pwd_regs_t;

static volatile pwd_regs_t * const PWD_PTR = (pwd_regs_t*)PWD_BASE;

#define PWD_CTRL_KEY  0xA0        /*!< Power Management CTRL Key     */
#define PWD_RST_KEY   0xA5        /*!< Power Management RST Key      */

/** Power Management Control Register flags */
enum
{
    PWD_CTRL_MAINPWD = 0x01,      /*!< Main Core Power Down       */
    PWD_CTRL_COREPWD = 0x02,      /*!< Core Power Down            */
    PWD_CTRL_SYSPWD  = 0x04,      /*!< System Power Down          */
};

/** Power Management Control Register bit offsets */
enum
{
    PWD_CTRL_COREINT_SHIFT    = 8,   /*!< Main Clock Prescaler                  */
    PWD_CTRL_PER0INT_SHIFT    = 12,  /*!< Peripheral Clock0 Prescaler Integer   */
    PWD_CTRL_WKUPMODE_SHIFT   = 16,  /*!< Wake Up Mode                          */
    PWD_CTRL_WKUPSEL_SHIFT    = 19,  /*!< Wake Up Pin Selection                 */
    PWD_CTRL_PER2INT_SHIFT    = 24,  /*!< Peripheral Clock2 Prescaler Integer   */
    PWD_CTRL_PER0FRACT_SHIFT  = 28,  /*!< Peripheral Clock0 Prescaler Fraction  */
    PWD_CTRL_PER2FRACT_SHIFT  = 30,  /*!< Peripheral Clock2 Prescaler Fraction  */
};

/** Power Management Control Register masks */
enum
{
    PWD_CTRL_COREINT_MASK   = 0x0F << PWD_CTRL_COREINT_SHIFT,   /*!< Main Clock Prescaler Mask                 */
    PWD_CTRL_PER0INT_MASK   = 0x0F << PWD_CTRL_PER0INT_SHIFT,   /*!< Peripheral Clock0 Prescaler Integer Mask  */
    PWD_CTRL_PER2INT_MASK   = 0x0F << PWD_CTRL_PER2INT_SHIFT,   /*!< Peripheral Clock2 Prescaler Integer Mask  */
    PWD_CTRL_PER0FRACT_MASK = 0x03 << PWD_CTRL_PER0FRACT_SHIFT, /*!< Peripheral Clock0 Prescaler Fraction Mask */
    PWD_CTRL_PER2FRACT_MASK = 0x03 << PWD_CTRL_PER2FRACT_SHIFT, /*!< Peripheral Clock2 Prescaler Fraction Mask */
    PWD_CTRL_WKUPMODE_MASK  = 0x07 << PWD_CTRL_WKUPMODE_SHIFT,  /*!< Wake Up Mode Mask                         */
    PWD_CTRL_WKUPSEL_MASK   = 0x1F << PWD_CTRL_WKUPSEL_SHIFT,   /*!< Wake Up Pin Selection Mask                */
};

/** Power Management RSTRSN Register flags */
enum
{
    PWD_RSN_PWRON          = 0x01,  /*!< Power On Reset                                 */
    PWD_RSN_DBG            = 0x02,  /*!< Debug Reset                                    */
    PWD_RSN_SOFT           = 0x04,  /*!< Software Reset                                 */
    PWD_RSN_WDT            = 0x08,  /*!< Watchdog Reset                                 */
    PWD_RSN_MBIST          = 0x10,  /*!< MBIST Reset                                    */
    PWD_RSN_LS_HARD_ERR    = 0x20,  /*!< Lockstep Hard Error Reset (FT-only)            */
    PWD_RSN_DC_HARD_ERR    = 0x40,  /*!< Data-cache Hard Error Reset (FT-only)          */
    PWD_RSN_IC_HARD_ERR    = 0x80,  /*!< Instruction-cache Hard Error Reset (FT-only)   */
    PWD_RSN_DL_HARD_ERR    = 0x100, /*!< Core Deadlock Hard Error Reset (FT-only)       */
};

/** Power Management Info Register flags */
enum
{
    PWD_INFO_MAINPWD  = 0x01,      /*!< Main Core Power Down              */
    PWD_INFO_COREPWD  = 0x02,      /*!< Core Power Down                   */
    PWD_INFO_SYSPWD   = 0x04,      /*!< System Power Down                 */
    PWD_INFO_COREPRES = 0x08,      /*!< Core Clock Prescaler              */
    PWD_INFO_PER0PRES = 0x10,      /*!< Peripheral Clock0 Prescaler       */
    PWD_INFO_PER2PRES = 0x20,      /*!< Peripheral Clock2 Prescaler       */
};

/** @} */

#endif /* __CCPROC_PWD_H */
/** @} */
