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
 * @file            ccproc-amba-i2c_wkup.h
 * @brief           CC Processor AMBA I2C Wakeup definitions
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_I2C_WKUP_H
#define __CCPROC_AMBA_I2C_WKUP_H

#include <stdint.h>

/************************//**
 * @defgroup i2c_wkup I2C Wakeup Controller
 * I2C Wakeup Controller registers and definitions
 * @{
 *//************************/

/** I2C Wakeup Controller Registers */
typedef struct
{
    uint32_t STATUS;  /*!< Status Register                   */
    uint32_t CTRL;    /*!< Control Register                  */
    uint32_t IRQMAP;  /*!< Interrupt Mapping Register        */
} amba_i2c_wkup_t;

/** I2C Wakeup Controller Status Register Flags */
enum
{
    I2C_WKUP_STAT_EN         = 0x00001,  /*!< I2C Wakeup Enable             */
    I2C_WKUP_STAT_WKP7       = 0x00002,  /*!< 7-bit Address Mode Interrupt  */
    I2C_WKUP_STAT_WKP10      = 0x00004,  /*!< 10-bit Address Mode Interrupt */
    I2C_WKUP_STAT_ACK1       = 0x00800,  /*!< ACK1 Transmission Error       */
    I2C_WKUP_STAT_ACK2       = 0x01000,  /*!< ACK2 Transmission Error       */
    I2C_WKUP_STAT_ACK3       = 0x02000,  /*!< ACK3 Transmission Error       */
};

/** I2C Wakeup Controller Status Register bit offsets */
enum
{
    I2C_WKUP_STAT_DATA_SHIFT     = 3,   /*!<  I2C Wakeup Controller Status Register Data Shift    */
};

/** I2C Wakeup Controller Status Register masks */
enum
{
    I2C_WKUP_STAT_DATA_MASK      = 0xFF << I2C_WKUP_STAT_DATA_SHIFT,      /*!<  I2C Wakeup Controller Status Register Command Mask    */
};

/** I2C Wakeup Status Register Get Data Helper Macro */
#define I2C_WKUP_STAT_GET_DATA(status) ((status & I2C_WKUP_STAT_DATA_MASK) >> I2C_WKUP_STAT_DATA_SHIFT) /*!< I2C Wakeup Status Register Get Data */

/** I2C Wakeup Controller Control Register Flags */
enum
{
    I2C_WKUP_CTRL_A7EN       = 0x00001,  /*!< 7-bit Address Mode Enable     */
    I2C_WKUP_CTRL_A10EN      = 0x00002,  /*!< 10-bit Address Mode Enable    */
    I2C_WKUP_CTRL_DEN        = 0x00004,  /*!< Data Reception Enable         */
    I2C_WKUP_CTRL_ACK        = 0x00008,  /*!< ACK Bit Value                 */
    I2C_WKUP_CTRL_AEN        = 0x00010,  /*!< ACK Enable                    */
    I2C_WKUP_CTRL_AIE        = 0x00020,  /*!< ACK Interrupt Enable          */
};

/** I2C Wakeup Controller Control Register bit offsets */
enum
{
    I2C_WKUP_CTRL_ADDR7_SHIFT     =  6,   /*!<  I2C Wakeup Controller Control Register Address7 Shift    */
    I2C_WKUP_CTRL_ADDR10_SHIFT    = 13,   /*!<  I2C Wakeup Controller Control Register Address10 Shift   */
};

/** I2C Wakeup Controller Status Register masks */
enum
{
    I2C_WKUP_CTRL_ADDR7_MASK      = 0x7F  << I2C_WKUP_CTRL_ADDR7_SHIFT,      /*!<  I2C Wakeup Controller Control Register Address7 Mask    */
    I2C_WKUP_CTRL_ADDR10_MASK     = 0x3FF << I2C_WKUP_CTRL_ADDR10_SHIFT,     /*!<  I2C Wakeup Controller Control Register Address10 Mask   */
};

/**
 * @name I2C Wakeup Control Register Helper Macros
 * @{
 */
#define I2C_WKUP_CTRL_BUILD_ADDR(addr7, addr10) ((addr7 << I2C_WKUP_CTRL_ADDR7_SHIFT) | (addr10 << I2C_WKUP_CTRL_ADDR10_SHIFT)) /*!< I2C Wakeup Control Register Address Build         */
#define I2C_WKUP_CTRL_GET_ADDR7(ctrl)           ((ctrl & I2C_WKUP_CTRL_ADDR7_MASK) >> I2C_WKUP_CTRL_ADDR7_SHIFT)                /*!< I2C Wakeup Control Register Address7 Get          */
#define I2C_WKUP_CTRL_GET_ADDR10(ctrl)          ((ctrl & I2C_WKUP_CTRL_ADDR10_MASK) >> I2C_WKUP_CTRL_ADDR10_SHIFT)              /*!< I2C Wakeup control register Address10 Get         */
/** @} */

/** @} */

#endif /* __CCPROC_AMBA_I2C_WKUP_H */
/** @} */
