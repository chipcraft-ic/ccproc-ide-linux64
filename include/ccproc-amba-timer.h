/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2024-08-19 14:59:12 +0200 (pon, 19 sie 2024) $
* $Revision: 1101 $
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
 * @file            ccproc-amba-timer.h
 * @brief           CC Processor AMBA TIMER definitions
 * @author          Rafal Harabien
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_TIMER_H
#define __CCPROC_AMBA_TIMER_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup timer Timers
 * Timer Controller registers and definitions
 * @{
 *//************************/

/** Timer Registers */
typedef struct
{
    uint32_t CTRL;                    /*!< Control Register                */
    uint32_t PER;                     /*!< Period Register                 */
    uint32_t PERBUF;                  /*!< Period Buffer Register          */
    uint32_t PRES;                    /*!< Prescaler Register              */
    uint32_t PRESBUF;                 /*!< Prescaler Buffer Register       */
    uint32_t COUNT;                   /*!< Count Register                  */
    uint32_t IRQM;                    /*!< Interrupt Mask                  */
    uint32_t IRQF;                    /*!< Interrupt Flags                 */
    uint32_t IRQMAP;                  /*!< Interrupt Mapping               */
    uint32_t BUFVD;                   /*!< Buffer Valid Flags Register     */
    uint32_t COMPDEF;                 /*!< Compare Output Default Register */
} amba_timer_t;

/** Timer Channel Registers */
typedef struct
{
    uint32_t CCCTRL;             /*!< Channel Control Register        */
    uint32_t CCDATA;             /*!< Capture/Compare Register        */
    uint32_t CCDATABUF;          /*!< Capture/Compare Buffer Register */
} timer_channel_regs_t;

#ifdef CCPROC_SDK

 #define AMBA_TIMER32_BASE(index) (AMBA_TIMER32_0_BASE+(index)*0x100)  /*!< Timer 32 base address */
 #define AMBA_TIMER16_BASE(index) (AMBA_TIMER16_0_BASE+(index)*0x100)  /*!< Timer 16 base address */

 #define AMBA_TIMER32_CHANNEL_BASE(index, channel) (AMBA_TIMER32_BASE(index) + sizeof(amba_timer_t) + (channel)*sizeof(timer_channel_regs_t))  /*!< Timer 32 channel base address */
 #define AMBA_TIMER16_CHANNEL_BASE(index, channel) (AMBA_TIMER16_BASE(index) + sizeof(amba_timer_t) + (channel)*sizeof(timer_channel_regs_t))  /*!< Timer 16 channel base address */

 #define AMBA_TIMER32_PTR(index) ((volatile amba_timer_t*)AMBA_TIMER32_BASE(index))  /*!< Timer 32 pointer */
 #define AMBA_TIMER16_PTR(index) ((volatile amba_timer_t*)AMBA_TIMER16_BASE(index))  /*!< Timer 16 pointer */

 #define AMBA_TIMER32_CHANNEL_PTR(index, channel) ((volatile timer_channel_regs_t*)AMBA_TIMER32_CHANNEL_BASE(index, channel))  /*!< Timer 32 channel pointer */
 #define AMBA_TIMER16_CHANNEL_PTR(index, channel) ((volatile timer_channel_regs_t*)AMBA_TIMER16_CHANNEL_BASE(index, channel))  /*!< Timer 16 channel pointer */

#endif

/** Timer Control Register */
enum
{
    TIMER_CTRL_EN            = 0x00000001,  /*!< Timer Enable bit                                                */

    TIMER_CTRL_DIR_UP        = 0x00000000,  /*!< count direction - increment                                     */
    TIMER_CTRL_DIR_DOWN      = 0x00000002,  /*!< count direction - decrement                                     */

    TIMER_CTRL_CMD_RESTART   = 1 << 2,      /*!< update registers with "BUFFERED" values and restart counting    */
    TIMER_CTRL_CMD_UPDATE    = 2 << 2,      /*!< update registers with "BUFFERED" values                         */
    TIMER_CTRL_CMD_RESET     = 3 << 2,      /*!< clear all registers                                             */

    TIMER_CTRL_MODE_NORMAL   = 0 << 4,      /*!< timer mode                                                      */
    TIMER_CTRL_MODE_CAPTURE  = 1 << 4,      /*!< capture mode                                                    */
    TIMER_CTRL_MODE_WAVEFORM = 2 << 4,      /*!< waveform generator mode                                         */

    TIMER_CTRL_CAP_NORMAL    = 0 << 6,      /*!< normal mode                                                     */
    TIMER_CTRL_CAP_PERIOD    = 1 << 6,      /*!< period mode                                                     */
    TIMER_CTRL_CAP_PULSE     = 2 << 6,      /*!< pulse width mode                                                */

    TIMER_CTRL_WAVE_SINGLE   = 0 << 8,      /*!< single slope mode                                               */
    TIMER_CTRL_WAVE_DUAL     = 1 << 8,      /*!< dual slope mode                                                 */

    TIMER_CTRL_DBG_STOP      = 0x80000000,  /*!< Stop counting in debug mode                                     */
};

/** Timer Control Register bit offsets */
enum
{
    TIMER_CTRL_CMD_SHIFT     = 2,   /*!<  Timer Control Register Command Shift    */
    TIMER_CTRL_MODE_SHIFT    = 4,   /*!<  Timer Control Register Mode Shift       */
    TIMER_CTRL_CAP_SHIFT     = 6,   /*!<  Timer Control Register Capture Shift    */
    TIMER_CTRL_CC_NUM_SHIFT  = 16,  /*!<  Timer Control Register CC Number Shift  */
};

/** Timer Control Register masks */
enum
{
    TIMER_CTRL_CMD_MASK      = 0x03 << TIMER_CTRL_CMD_SHIFT,      /*!<  Timer Control Register Command Mask    */
    TIMER_CTRL_MODE_MASK     = 0x03 << TIMER_CTRL_MODE_SHIFT,     /*!<  Timer Control Register Mode Mask       */
    TIMER_CTRL_CAP_MASK      = 0x03 << TIMER_CTRL_CAP_SHIFT,      /*!<  Timer Control Register Capture Mask    */
    TIMER_CTRL_CC_NUM_MASK   = 0xFF << TIMER_CTRL_CC_NUM_SHIFT,   /*!<  Timer Control Register CC Number Mask  */
};

/**
 * @name Timer Control Register helper macros
 * @{
 */
#define TIMER_CTRL_GET_CC_NUM(timer_ctl)  ((timer_ctl & TIMER_CTRL_CC_NUM_MASK)  >> TIMER_CTRL_CC_NUM_SHIFT)   /*!< Timer Control Register CC Number */
/** @} */

/** Timer Interrupt Mask Bits */
enum
{
    TIMER_OVFIE     = 0x1,  /*!< Overflow Interrupt Enable        */
    TIMER_ERRIE     = 0x2,  /*!< Error Interrupt Enable           */
    TIMER_CCIE_BASE = 0x4,  /*!< Capture/Compare Interrupt Enable */
};
#define TIMER_CCIE(ch) (TIMER_CCIE_BASE << (ch))  /*!< Channel Capture/Compare Interrupt Enable */

/** Timer Interrupt Flags */
enum
{
    TIMER_OVFIF     = 0x1,  /*!< Overflow Interrupt Flag        */
    TIMER_ERRIF     = 0x2,  /*!< Error Interrupt Flag           */
    TIMER_CCIF_BASE = 0x4,  /*!< Capture/Compare Interrupt Flag */
};
#define TIMER_CCIF(ch) (TIMER_CCIF_BASE << (ch))  /*!< Channel Capture/Compare Interrupt Flag */

/** Timer Buffer Valid Flags */
enum
{
    TIMER_PRESBV    = 0x1,  /*!< Prescaler Buffer Valid       */
    TIMER_PERBV     = 0x2,  /*!< Period Buffer Valid          */
    TIMER_CCVD_BASE = 0x4,  /*!< Capture/Compare Buffer Valid */
};
#define TIMER_CCVD(ch) (TIMER_CCVD_BASE << (ch))  /*!< Channel Capture/Compare Buffer Valid */

/** Timer Compare Output Default Bits */
enum
{
    TIMER_CCDEF_BASE = 0x4,  /*!< Capture Output Default Value */
};
#define TIMER_CCDEF(ch) (TIMER_CCDEF_BASE << (ch))  /*!< Channel Capture Output Default Value */

/** Timer Channel Control Register */
enum
{
    TIMER_CC_EN = 0x01, /*!< Channel enable */

    /* Capture Event Configuration */
    TIMER_CC_MODE_RISING_EDGE  = 0 << 1,  /*!< Rising Edge  */
    TIMER_CC_MODE_FALLING_EDGE = 1 << 1,  /*!< Falling Edge */
    TIMER_CC_MODE_BOTH_EDGES   = 2 << 1,  /*!< Both Edges   */
};

/** @} */

#endif /* __CCPROC_AMBA_TIMER_H */
/** @} */
