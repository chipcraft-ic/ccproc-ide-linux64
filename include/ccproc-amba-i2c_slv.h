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
 * @file            ccproc-amba-i2c_slv.h
 * @brief           CC Processor AMBA I2C Slave definitions
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_I2C_SLV_H
#define __CCPROC_AMBA_I2C_SLV_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup i2c_slv I2C Slave Controller
 * I2C Slave Controller registers and definitions
 * @{
 *//************************/

/** I2C Slave Controller Registers */
typedef struct
{
    uint32_t STATUS;  /*!< Status Register                   */
    uint32_t CTRL;    /*!< Control Register                  */
    uint32_t CMD;     /*!< Command Register                  */
    uint32_t FILTER;  /*!< Input Filter Register             */
    uint32_t TMNG;    /*!< Timings Register                  */
    uint32_t COUNT;   /*!< Count Register                    */
    uint32_t ADDR;    /*!< Address Register                  */
    uint32_t TDR;     /*!< Transmit Data Register            */
    uint32_t RDR;     /*!< Reception Data Register           */
    uint32_t IRQM;    /*!< Interrupt Mask Register           */
    uint32_t IRQMAP;  /*!< Interrupt Mapping Register        */
} amba_i2c_slv_t;

#ifdef CCPROC_SDK
 #define AMBA_I2C_SLV_BASE(index) (AMBA_I2C_SLV_BASE+(index)*0x100)                    /*!< I2C Slave base address             */
 #define AMBA_I2C_SLV_PTR(index) ((volatile amba_i2c_slv_t*)AMBA_I2C_SLV_BASE(index))  /*!< I2C Slave pointer                  */
#endif

/** I2C Slave Controller Status Register Flags */
enum
{
    I2C_SLV_STAT_BS_ERR     = 0x00001,  /*!< Bus Error                    */
    I2C_SLV_STAT_TXC        = 0x00002,  /*!< Transmission Complete        */
    I2C_SLV_STAT_TDRE       = 0x00004,  /*!< Transmit Data Register Empty */
    I2C_SLV_STAT_RDRF       = 0x00008,  /*!< Read Data Register Full      */
    I2C_SLV_STAT_TXINPR     = 0x00010,  /*!< Transmission in progress     */
    I2C_SLV_STAT_HOLD       = 0x00020,  /*!< Bus Hold                     */
    I2C_SLV_STAT_PACK       = 0x00400,  /*!< Last received ACK bit        */
    I2C_SLV_STAT_DACK       = 0x00800,  /*!< Data ACK received            */
    I2C_SLV_STAT_DNACK      = 0x01000,  /*!< Data NACK received           */
    I2C_SLV_STAT_S_REC      = 0x02000,  /*!< Start received               */
    I2C_SLV_STAT_SR_REC     = 0x04000,  /*!< Repeated Start received      */
    I2C_SLV_STAT_ADDR_MATCH = 0x08000,  /*!< Slave addressed matched      */
    I2C_SLV_STAT_RDM        = 0x10000,  /*!< Read mode                    */
    I2C_SLV_STAT_GC_MATCH   = 0x20000,  /*!< General Call Address matched */
    I2C_SLV_STAT_PRI_MATCH  = 0x40000,  /*!< Primary Address matched      */
    I2C_SLV_STAT_SEC_MATCH  = 0x80000,  /*!< Secondary Address matched    */
};

/** I2C Slave Controller Status Register bit offsets */
enum
{
    I2C_SLV_STAT_CMD_SHIFT     = 6,   /*!<  I2C Slave Controller Status Register Command Shift    */
};

/** I2C Slave Controller Status Register masks */
enum
{
    I2C_SLV_STAT_CMD_MASK      = 0x0F << I2C_SLV_STAT_CMD_SHIFT,      /*!<  I2C Slave Controller Status Register Command Mask    */
};

/** I2C Slave Status Command Helper Macro */
#define I2C_SLV_STAT_GET_CMD(status)  ((status & I2C_SLV_STAT_CMD_MASK) >> I2C_SLV_STAT_CMD_SHIFT) /*!< I2C Slave Status Register Command get */

/** I2C Slave Controller Commands */
enum
{
    I2C_SLV_CMD_NOOP      = 0x00,  /*!< No Command          */
    I2C_SLV_CMD_ACK       = 0x01,  /*!< ACK Command         */
    I2C_SLV_CMD_STOP      = 0x02,  /*!< Stop Command        */
    I2C_SLV_CMD_RESET     = 0x03,  /*!< Reset Command       */
    I2C_SLV_CMD_TDR_CLEAR = 0x04,  /*!< Clear TDR Command   */
    I2C_SLV_CMD_RDR_CLEAR = 0x05,  /*!< Clear RDR Command   */
};

/** I2C Slave Controller Control Register Flags */
enum
{
    I2C_SLV_CTRL_EN         = 0x001,  /*!< I2C Slave Enable                         */
    I2C_SLV_CTRL_AUTO_CNT   = 0x002,  /*!< Automatic Byte Counting Enable           */
    I2C_SLV_CTRL_AUTO_ACK   = 0x004,  /*!< Automatic ACK Bit Transmission Enable    */
    I2C_SLV_CTRL_ADDR_ACK   = 0x008,  /*!< Automatic Address ACK Send Enable        */
    I2C_SLV_CTRL_GC_MATCH   = 0x010,  /*!< General Call Address Match Enabled       */
    I2C_SLV_CTRL_PRI_MATCH  = 0x020,  /*!< Primary Address Match Enabled            */
    I2C_SLV_CTRL_PRI_10B    = 0x040,  /*!< Primary Address 10 Bits Enabled          */
    I2C_SLV_CTRL_SEC_MATCH  = 0x080,  /*!< Secondary Address Match Enabled          */
    I2C_SLV_CTRL_SEC_10B    = 0x100,  /*!< Secondary Address 10 Bits Enabled        */
};

/** I2C Slave Controller Timings Register bit offsets */
enum
{
    I2C_SLV_TMNG_SETUP_SHIFT      = 0,   /*!<  I2C Slave Controller Timings Register Setup Shift    */
    I2C_SLV_TMNG_HOLD_SHIFT       = 8,   /*!<  I2C Slave Controller Timings Register Hold Shift     */
};

/** I2C Slave Controller Timings Register masks */
enum
{
    I2C_SLV_TMNG_SETUP_MASK      = 0xFF << I2C_SLV_TMNG_SETUP_SHIFT,      /*!<  I2C Slave Controller Timings Register Setup Mask    */
    I2C_SLV_TMNG_HOLD_MASK       = 0xFF << I2C_SLV_TMNG_HOLD_SHIFT,       /*!<  I2C Slave Controller Timings Register Hold Mask     */
};


/**
 * @name I2C Slave Timings Register Helper Macros
 * @{
 */
#define I2C_SLV_BUILD_TMNG(setupPeriod, holdPeriod) ((setupPeriod << I2C_SLV_TMNG_SETUP_SHIFT) | (holdPeriod << I2C_SLV_TMNG_HOLD_SHIFT)) /*!< I2C Slave Timings Register Build     */
#define I2C_SLV_GET_TMNG_SETUP(timings) ((timings & I2C_SLV_TMNG_SETUP_MASK) >> I2C_SLV_TMNG_SETUP_SHIFT)                                 /*!< I2C Slave Timings Register Get Setup */
#define I2C_SLV_GET_TMNG_HOLD(timings) ((timings & I2C_SLV_TMNG_HOLD_MASK) >> I2C_SLV_TMNG_HOLD_SHIFT)                                    /*!< I2C Slave Timings Register Get Hold  */
/** @} */

/** I2C Slave Controller Address Register bit offsets */
enum
{
    I2C_SLV_ADDR_PRI_SHIFT      = 0,   /*!<  I2C Slave Controller Address Register Primary Address Shift    */
    I2C_SLV_ADDR_SEC_SHIFT      = 16,  /*!<  I2C Slave Controller Address Register Secondary Address Shift  */
};

/** I2C Slave Controller Address Register masks */
enum
{
    I2C_SLV_ADDR_PRI_MASK      = 0x3FF << I2C_SLV_ADDR_PRI_SHIFT,      /*!<  I2C Slave Controller Address Register Primary Address Mask    */
    I2C_SLV_ADDR_SEC_MASK      = 0x3FF << I2C_SLV_ADDR_SEC_SHIFT,      /*!<  I2C Slave Controller Address Register Secondary Address Mask  */
};

/**
 * @name I2C Slave Address Register Helper Macros
 * @{
 */
#define I2C_SLV_BUILD_ADDR(priAddr, secAddr) ((priAddr << I2C_SLV_ADDR_PRI_SHIFT) | (secAddr << I2C_SLV_ADDR_SEC_SHIFT)) /*!< I2C Slave Address Register Build         */
#define I2C_SLV_GET_ADDR_PRI(addr) ((addr & I2C_SLV_ADDR_PRI_MASK) >> I2C_SLV_ADDR_PRI_SHIFT)                            /*!< I2C Slave Address Register Get Primary   */
#define I2C_SLV_GET_ADDR_SEC(addr) ((addr & I2C_SLV_ADDR_SEC_MASK) >> I2C_SLV_ADDR_SEC_SHIFT)                            /*!< I2C Slave Address Register Get Secondary */
/** @} */

/** I2C Controller Interrupt Mask Register Flags */
enum
{
    I2C_SLV_TXCIE      = 0x001,  /*!< Transmission Completed Interrupt Enable  */
    I2C_SLV_TDREIE     = 0x002,  /*!< TX Data Register Empty Interrupt Enable  */
    I2C_SLV_RDRFIE     = 0x004,  /*!< RX Data Register Full Interrupt Enable   */
    I2C_SLV_BUSERRIE   = 0x008,  /*!< Bus Error Interrupt Enable               */
    I2C_SLV_SLADDRIE   = 0x010,  /*!< Slave Addressed Interrupt Enable         */
    I2C_SLV_DNACKIE    = 0x020,  /*!< Data NACK Interrupt Enable               */
    I2C_SLV_DACKIE     = 0x040,  /*!< Data ACK Interrupt Enable                */
    I2C_SLV_CNT0IE     = 0x080,  /*!< Count Register Equals 0 Interrupt Enable */
};

/** @} */

#endif /* __CCPROC_AMBA_I2C_SLV_H */
/** @} */
