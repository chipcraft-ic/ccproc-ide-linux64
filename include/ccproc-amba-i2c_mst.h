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
 * @file            ccproc-amba-i2c_mst.h
 * @brief           CC Processor AMBA I2C Master definitions
 * @author          Rafal Harabien
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_I2C_MST_H
#define __CCPROC_AMBA_I2C_MST_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup i2c_mst I2C Master Controller
 * I2C Master Controller registers and definitions
 * @{
 *//************************/

/** I2C Master Controller Registers */
typedef struct
{
    uint32_t STATUS;  /*!< Status Register                   */
    uint32_t CTRL;    /*!< Control Register                  */
    uint32_t CMD;     /*!< Command Register                  */
    uint32_t PRES;    /*!< Prescaler Register                */
    uint32_t CWGR;    /*!< Clock Waveform Generator Register */
    uint32_t COUNT;   /*!< Count Register                    */
    uint32_t ADDR;    /*!< Address Register                  */
    uint32_t TDR;     /*!< Transmission Data Register        */
    uint32_t RDR;     /*!< Reception Data Register           */
    uint32_t IRQM;    /*!< Interrupt Mask Register           */
    uint32_t IRQMAP;  /*!< Interrupt Mapping Register        */
    uint32_t FILTER;  /*!< Input Filter Register             */
} amba_i2c_mst_t;

#ifdef CCPROC_SDK
 #define AMBA_I2C_MST_BASE(index) (AMBA_I2C_MST_0_BASE+(index)*0x100)                     /*!< I2C Master base address             */
 #define AMBA_I2C_MST_PTR(index) ((volatile amba_i2c_mst_t*)AMBA_I2C_MST_BASE(index))     /*!< I2C Master pointer                  */
#endif

/** I2C Master Controller Status Register Flags */
enum
{
    I2C_MST_STAT_BS_UNK     = 0x0000,  /*!< Unknown Bus State            */
    I2C_MST_STAT_BS_IDLE    = 0x0001,  /*!< Idle Bus State               */
    I2C_MST_STAT_BS_OWN     = 0x0002,  /*!< Owned Bus State              */
    I2C_MST_STAT_BS_BUSY    = 0x0003,  /*!< Busy Bus State               */

    I2C_MST_STAT_TXC        = 0x0004,  /*!< Transmission Complete        */
    I2C_MST_STAT_TDRE       = 0x0008,  /*!< Transmit Data Register Empty */
    I2C_MST_STAT_RDRF       = 0x0010,  /*!< Receive Data Register Full   */
    I2C_MST_STAT_BUSY       = 0x0020,  /*!< Transmission in progress     */
    I2C_MST_STAT_ARB_LOST   = 0x0040,  /*!< Bus Arbitration Lost         */
    I2C_MST_STAT_BUS_HOLD   = 0x0080,  /*!< Holding the BUS              */

    I2C_MST_STAT_CMD_ACK    = 0x0100,  /*!< Current Command ACK          */
    I2C_MST_STAT_CMD_STOP   = 0x0200,  /*!< Current Command STOP         */
    I2C_MST_STAT_CMD_RESET  = 0x0300,  /*!< Current Command RESET        */

    I2C_MST_STAT_ACK        = 0x0400,  /*!< Received ACK bit             */
    I2C_MST_STAT_AACK       = 0x0800,  /*!< Address ACKed by Slave       */
    I2C_MST_STAT_DACK       = 0x1000,  /*!< Data ACKed by Slave          */
    I2C_MST_STAT_ANACK      = 0x2000,  /*!< Address NACKed by Slave      */
    I2C_MST_STAT_DNACK      = 0x4000,  /*!< Data NACKed by Slave         */
};

#define I2C_MST_STAT_BS_MASK  0x0003  /*!< I2C Master Status Register Bus State Bit Mask */

#define I2C_MST_STAT_GET_BS(status) ((status) & I2C_MST_STAT_BS_MASK)  /*!< Get I2C Master Bus State from Status Register */

/** I2C Master Controller Control Register Flags */
enum
{
    I2C_MST_CTRL_EN          = 0x01,  /*!< I2C Master Enable                      */
    I2C_MST_CTRL_10BIT_ADDR  = 0x02,  /*!< 10bit Addressing Mode Enable           */
    I2C_MST_CTRL_AUTO_CNT    = 0x04,  /*!< Automatic Byte Counting Enable         */
    I2C_MST_CTRL_AUTO_ACK    = 0x08,  /*!< Automatic ACK bit Transmission Enable  */
    I2C_MST_CTRL_AUTO_STOP   = 0x10,  /*!< Automatic STOP bit Transmission Enable */
};

/** I2C Master Controller Command Register Flags */
enum
{
    I2C_MST_CMD_ACK           = 0x01,  /*!< Command ACK   */
    I2C_MST_CMD_STOP          = 0x02,  /*!< Command STOP  */
    I2C_MST_CMD_RESET         = 0x03,  /*!< Command RESET */

    I2C_MST_CMD_ACK_BIT       = 0x04,  /*!< ACK bit       */
    I2C_MST_CMD_LAST_ACK_BIT  = 0x08,  /*!< Last ACK bit  */
};

#define I2C_MST_BUILD_PRES(i2cFreq, periphFreq) ((periphFreq) / (2*(i2cFreq)) - 1)  /*!< I2C Master Prescaler Helper Macro */

/** I2C Master Clock Waveform Generator Register Helper Macro */
#define I2C_MST_BUILD_CWGR(lowPeriod, highPeriod, setupHoldPeriod, startStopPeriod) \
    ((lowPeriod)|((highPeriod)<<8)|((setupHoldPeriod)<<16)|((startStopPeriod)<<24))

#define I2C_MST_ADDR_WR     0x00  /*!< I2C Master Address Register Write Mode           */
#define I2C_MST_ADDR_RD     0x01  /*!< I2C Master Address Register Read Mode            */
#define I2C_MST_ADDR_SHIFT  0x01  /*!< I2C Master Address Register Address Bit Shift    */

#define I2C_MST_BUILD_ADDR_WR(addr) (((addr) << I2C_MST_ADDR_SHIFT) | I2C_MST_ADDR_WR)  /*!< I2C Master Address (Write Mode) */
#define I2C_MST_BUILD_ADDR_RD(addr) (((addr) << I2C_MST_ADDR_SHIFT) | I2C_MST_ADDR_RD)  /*!< I2C Master Address (Read Mode)  */

/** I2C Master Controller Interrupt Mask Register Flags */
enum
{
    I2C_MST_TXCIE      = 0x0001,  /*!< Transmission Completed Interrupt Enable  */
    I2C_MST_TDREIE     = 0x0002,  /*!< TX Data Register Empty Interrupt Enable  */
    I2C_MST_RDRFIE     = 0x0004,  /*!< RX Data Register Full Interrupt Enable   */
    I2C_MST_ARBLOSTIE  = 0x0008,  /*!< Arbitration Lost Interrupt Enable        */
    I2C_MST_ANACKIE    = 0x0010,  /*!< Address NACK Received Interrupt Enable   */
    I2C_MST_AACKIE     = 0x0020,  /*!< Address ACK Received Interrupt Enable    */
    I2C_MST_DNACKIE    = 0x0040,  /*!< Data NACK Received Interrupt Enable      */
    I2C_MST_DACKIE     = 0x0080,  /*!< Data ACK Received Interrupt Enable       */
    I2C_MST_CNT0IE     = 0x0100,  /*!< Count Register Equals 0 Interrupt Enable */
};

/** @} */

#endif /* __CCPROC_AMBA_I2C_MST_H */
/** @} */
