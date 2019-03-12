/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2018-12-05 20:12:57 +0100 (śro) $
* $Revision: 365 $
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
 * @file            ccproc-amba-can.h
 * @brief           CC Processor AMBA CAN definitions
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_CAN_H
#define __CCPROC_AMBA_CAN_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup can CAN Controller
 * CAN Controller registers and definitions
 * @{
 *//************************/

/** @brief CAN Basic Registers */
typedef struct
{
    uint32_t CTRL;              /*!< Control Register                         */
    uint32_t CMD;               /*!< Command Register                         */
    uint32_t STATUS;            /*!< Status Register                          */
    uint32_t IRQ;               /*!< Interrupt Register                       */
    uint32_t ACC_CODE;          /*!< Acceptance Code Register                 */
    uint32_t ACC_MASK;          /*!< Acceptance Mask Register                 */
    uint32_t TMNG0;             /*!< Bus Timing 0 Register                    */
    uint32_t TMNG1;             /*!< Bus Timing 1 Register                    */
    uint32_t _reserved1[2];
    uint32_t TX_ID0;            /*!< TX Identifier Byte 0 Register            */
    uint32_t TX_ID1;            /*!< TX Identifier Byte 1 Register            */
    uint32_t TX_DATA1;          /*!< TX Data Byte 1 Register                  */
    uint32_t TX_DATA2;          /*!< TX Data Byte 2 Register                  */
    uint32_t TX_DATA3;          /*!< TX Data Byte 3 Register                  */
    uint32_t TX_DATA4;          /*!< TX Data Byte 4 Register                  */
    uint32_t TX_DATA5;          /*!< TX Data Byte 5 Register                  */
    uint32_t TX_DATA6;          /*!< TX Data Byte 6 Register                  */
    uint32_t TX_DATA7;          /*!< TX Data Byte 7 Register                  */
    uint32_t TX_DATA8;          /*!< TX Data Byte 8 Register                  */
    uint32_t RX_ID0;            /*!< RX Identifier Byte 0 Register            */
    uint32_t RX_ID1;            /*!< RX Identifier Byte 1 Register            */
    uint32_t RX_DATA1;          /*!< RX Data Byte 1 Register                  */
    uint32_t RX_DATA2;          /*!< RX Data Byte 2 Register                  */
    uint32_t RX_DATA3;          /*!< RX Data Byte 3 Register                  */
    uint32_t RX_DATA4;          /*!< rX Data Byte 4 Register                  */
    uint32_t RX_DATA5;          /*!< RX Data Byte 5 Register                  */
    uint32_t RX_DATA6;          /*!< RX Data Byte 6 Register                  */
    uint32_t RX_DATA7;          /*!< RX Data Byte 7 Register                  */
    uint32_t RX_DATA8;          /*!< RX Data Byte 8 Register                  */
    uint32_t _reserved2[1];
    uint32_t CLKDIV;            /*!< Clock Divider Register                   */
    uint32_t _reserved3[32];
    uint32_t CLKREQ;            /*!< Clock Request Register                   */
    uint32_t IRQMAP;            /*!< Interrupt Mapping Register               */
} amba_can_basic_t;

#ifdef CCPROC_SDK
 #define AMBA_CAN_BSC_BASE(index) (AMBA_CAN0_BASE+(index)*0x1000)                            /*!< CAN Basic base address             */
 #define AMBA_CAN_BSC_PTR(index)  ((volatile amba_can_basic_t*)AMBA_CAN_BSC_BASE(index))     /*!< CAN Basic pointer                  */
#endif

/** CAN Basic Controller Control Register flags */
enum
{
    CAN_BSC_CTRL_RST       = 0x0001,     /*!< Reset Request             */
    CAN_BSC_CTRL_RIE       = 0x0002,     /*!< Receive Interrupt Enable  */
    CAN_BSC_CTRL_TIE       = 0x0004,     /*!< Transmit Interrupt Enable */
    CAN_BSC_CTRL_ERRIE     = 0x0008,     /*!< Error Interrupt Enable    */
    CAN_BSC_CTRL_OVRIE     = 0x0010,     /*!< Overrun Interrupt Enable  */
};

/** CAN Basic Controller Command Register flags */
enum
{
    CAN_BSC_CMD_TXREQ      = 0x0001,     /*!< Transmit Request          */
    CAN_BSC_CMD_ABORT      = 0x0002,     /*!< Abort Transmission        */
    CAN_BSC_CMD_RXREL      = 0x0004,     /*!< Release Receive Buffer    */
    CAN_BSC_CMD_OVRCLR     = 0x0008,     /*!< Clear Data Overrun        */
};

/** CAN Basic Controller Status Register flags */
enum
{
    CAN_BSC_STAT_RXBUF     = 0x0001,     /*!< Receive Buffer Status     */
    CAN_BSC_STAT_OVR       = 0x0002,     /*!< Data Overrun Status       */
    CAN_BSC_STAT_TXBUF     = 0x0004,     /*!< Transmit Buffer Status    */
    CAN_BSC_STAT_TXC       = 0x0008,     /*!< Transmission Complete     */
    CAN_BSC_STAT_RX        = 0x0010,     /*!< Receive Status            */
    CAN_BSC_STAT_TX        = 0x0020,     /*!< Transmit Status           */
    CAN_BSC_STAT_ERR       = 0x0040,     /*!< Error Status              */
    CAN_BSC_STAT_BUS       = 0x0080,     /*!< Bus Status                */
};

/** CAN Basic Controller Interrupt Register flags */
enum
{
    CAN_BSC_IRQ_RX         = 0x0001,     /*!< Receive Interrupt         */
    CAN_BSC_IRQ_TX         = 0x0002,     /*!< Transmit Interrupt        */
    CAN_BSC_IRQ_ERR        = 0x0004,     /*!< Error Interrupt           */
    CAN_BSC_IRQ_OVR        = 0x0008,     /*!< Overrun Interrupt         */
};

/** CAN Basic Controller Clock Request Register flags */
enum
{
    CAN_BSC_CLKREQ_CLKREQ  = 0x0001,     /*!< Clock Request             */
};

/** CAN Basic Controller Clock Divider Register flags */
enum
{
    CAN_BSC_CLKDIV_BASIC       = 0x0000,     /*!< Basic CAN Mode        */
    CAN_BSC_CLKDIV_EXTENDED    = 0x0080,     /*!< Basic CAN Extended    */
};

/** @brief CAN Extended Registers */
typedef struct
{
    uint32_t MODE;              /*!< Mode Register                            */
    uint32_t _reserved1[1];
    uint32_t STATUS;            /*!< Status Register                          */
    uint32_t IRQ;               /*!< Interrupt Register                       */
    uint32_t IRQEN;             /*!< Interrupt Enable Register                */
    uint32_t _reserved2[1];
    uint32_t TMNG0;             /*!< Bus Timing 0 Register                    */
    uint32_t TMNG1;             /*!< Bus Timing 1 Register                    */
    uint32_t _reserved3[3];
    uint32_t ARBLOST;           /*!< Arbitration Lost Capture Register        */
    uint32_t ERRCODE;           /*!< Error Code Capture Register              */
    uint32_t ERRLIM;            /*!< Error Warning Limit Register             */
    uint32_t RX_ERR_CNT;        /*!< RX Error Counter Register                */
    uint32_t TX_ERR_CNT;        /*!< TX Error Counter Register                */
    uint32_t STRUCT_PTR;        /*!< Depending on Configured Layout           */
    uint32_t _reserved4[12];
    uint32_t RX_MSG_CNT;        /*!< RX Message Counter Register              */
    uint32_t _reserved5[1];
    uint32_t CLKDIV;            /*!< Clock Divider Register                   */
    uint32_t _reserved6[32];
    uint32_t CLKREQ;            /*!< Clock Request Register                   */
    uint32_t IRQMAP;            /*!< Interrupt Mapping Register               */
} amba_can_ext_t;

/** @brief CAN Extended Acceptance Frame */
typedef struct
{
    uint32_t ACC_EXT_CODE0;         /*!< Acceptance Code 0 Register               */
    uint32_t ACC_EXT_CODE1;         /*!< Acceptance Code 1 Register               */
    uint32_t ACC_EXT_CODE2;         /*!< Acceptance Code 2 Register               */
    uint32_t ACC_EXT_CODE3;         /*!< Acceptance Code 3 Register               */
    uint32_t ACC_EXT_MASK0;         /*!< Acceptance Mask 0 Register               */
    uint32_t ACC_EXT_MASK1;         /*!< Acceptance Mask 1 Register               */
    uint32_t ACC_EXT_MASK2;         /*!< Acceptance Mask 2 Register               */
    uint32_t ACC_EXT_MASK3;         /*!< Acceptance Mask 3 Register               */
} amba_can_ext_acc_t;

/** @brief CAN Extended Standard RX Frame */
typedef struct
{
	uint32_t RX_EXT_INFO;           /*!< RX Frame Information Register            */
    uint32_t RX_EXT_ID0;            /*!< RX Identifier Byte 0 Register            */
    uint32_t RX_EXT_ID1;            /*!< RX Identifier Byte 1 Register            */
    uint32_t RX_EXT_DATA1;          /*!< RX Data Byte 1 Register                  */
    uint32_t RX_EXT_DATA2;          /*!< RX Data Byte 2 Register                  */
    uint32_t RX_EXT_DATA3;          /*!< RX Data Byte 3 Register                  */
    uint32_t RX_EXT_DATA4;          /*!< RX Data Byte 4 Register                  */
    uint32_t RX_EXT_DATA5;          /*!< RX Data Byte 5 Register                  */
    uint32_t RX_EXT_DATA6;          /*!< RX Data Byte 6 Register                  */
    uint32_t RX_EXT_DATA7;          /*!< RX Data Byte 7 Register                  */
    uint32_t RX_EXT_DATA8;          /*!< RX Data Byte 8 Register                  */
} amba_can_ext_rx_sff_t;

/** @brief CAN Extended Extended RX Frame */
typedef struct
{
    uint32_t RX_EXT_INFO;           /*!< RX Frame Information Register            */
    uint32_t RX_EXT_ID0;            /*!< RX Identifier Byte 0 Register            */
    uint32_t RX_EXT_ID1;            /*!< RX Identifier Byte 1 Register            */
    uint32_t RX_EXT_ID2;            /*!< RX Identifier Byte 2 Register            */
    uint32_t RX_EXT_ID3;            /*!< RX Identifier Byte 3 Register            */
    uint32_t RX_EXT_DATA1;          /*!< RX Data Byte 1 Register                  */
    uint32_t RX_EXT_DATA2;          /*!< RX Data Byte 2 Register                  */
    uint32_t RX_EXT_DATA3;          /*!< RX Data Byte 3 Register                  */
    uint32_t RX_EXT_DATA4;          /*!< RX Data Byte 4 Register                  */
    uint32_t RX_EXT_DATA5;          /*!< RX Data Byte 5 Register                  */
    uint32_t RX_EXT_DATA6;          /*!< RX Data Byte 6 Register                  */
    uint32_t RX_EXT_DATA7;          /*!< RX Data Byte 7 Register                  */
    uint32_t RX_EXT_DATA8;          /*!< RX Data Byte 8 Register                  */
} amba_can_ext_rx_eff_t;

/** @brief CAN Extended Standard TX Frame */
typedef struct
{
    uint32_t TX_EXT_INFO;           /*!< TX Frame Information Register            */
    uint32_t TX_EXT_ID0;            /*!< TX Identifier Byte 0 Register            */
    uint32_t TX_EXT_ID1;            /*!< TX Identifier Byte 1 Register            */
    uint32_t TX_EXT_DATA1;          /*!< TX Data Byte 1 Register                  */
    uint32_t TX_EXT_DATA2;          /*!< TX Data Byte 2 Register                  */
    uint32_t TX_EXT_DATA3;          /*!< TX Data Byte 3 Register                  */
    uint32_t TX_EXT_DATA4;          /*!< TX Data Byte 4 Register                  */
    uint32_t TX_EXT_DATA5;          /*!< TX Data Byte 5 Register                  */
    uint32_t TX_EXT_DATA6;          /*!< TX Data Byte 6 Register                  */
    uint32_t TX_EXT_DATA7;          /*!< TX Data Byte 7 Register                  */
    uint32_t TX_EXT_DATA8;          /*!< TX Data Byte 8 Register                  */
} amba_can_ext_tx_sff_t;

/** @brief CAN Extended Extended TX Frame */
typedef struct
{
    uint32_t TX_EXT_INFO;           /*!< TX Frame Information Register            */
    uint32_t TX_EXT_ID0;            /*!< TX Identifier Byte 0 Register            */
    uint32_t TX_EXT_ID1;            /*!< TX Identifier Byte 1 Register            */
    uint32_t TX_EXT_ID2;            /*!< TX Identifier Byte 2 Register            */
    uint32_t TX_EXT_ID3;            /*!< TX Identifier Byte 3 Register            */
    uint32_t TX_EXT_DATA1;          /*!< TX Data Byte 1 Register                  */
    uint32_t TX_EXT_DATA2;          /*!< TX Data Byte 2 Register                  */
    uint32_t TX_EXT_DATA3;          /*!< TX Data Byte 3 Register                  */
    uint32_t TX_EXT_DATA4;          /*!< TX Data Byte 4 Register                  */
    uint32_t TX_EXT_DATA5;          /*!< TX Data Byte 5 Register                  */
    uint32_t TX_EXT_DATA6;          /*!< TX Data Byte 6 Register                  */
    uint32_t TX_EXT_DATA7;          /*!< TX Data Byte 7 Register                  */
    uint32_t TX_EXT_DATA8;          /*!< TX Data Byte 8 Register                  */
} amba_can_ext_tx_eff_t;

#ifdef CCPROC_SDK

 #define AMBA_CAN_EXT_BASE(index)         (AMBA_CAN0_BASE+(index)*0x100)                           /*!< CAN Extended base address             */
 #define AMBA_CAN_EXT_PTR(index)          ((volatile amba_can_ext_t*)AMBA_CAN_EXT_BASE(index))     /*!< CAN Extended pointer                  */

 #define AMBA_CAN_EXT_ACC_PTR(index)      ((volatile amba_can_ext_acc_t*)(AMBA_CAN_EXT_PTR(index).STRUCT_PTR))       /*!< CAN Extended Acceptance Frame      */
 #define AMBA_CAN_EXT_RXSFF_PTR(index)    ((volatile amba_can_ext_rx_sff_t*)(AMBA_CAN_EXT_PTR(index).STRUCT_PTR))    /*!< CAN Extended Standard RX Frame     */
 #define AMBA_CAN_EXT_RXEFF_PTR(index)    ((volatile amba_can_ext_rx_eff_t*)(AMBA_CAN_EXT_PTR(index).STRUCT_PTR))    /*!< CAN Extended Extended RX Frame     */
 #define AMBA_CAN_EXT_TXSFF_PTR(index)    ((volatile amba_can_ext_tx_sff_t*)(AMBA_CAN_EXT_PTR(index).STRUCT_PTR))    /*!< CAN Extended Standard TX Frame     */
 #define AMBA_CAN_EXT_TXEFF_PTR(index)    ((volatile amba_can_ext_tx_eff_t*)(AMBA_CAN_EXT_PTR(index).STRUCT_PTR))    /*!< CAN Extended Extended TX Frame     */

#endif

/** CAN Extended Controller Mode Register flags */
enum
{
    CAN_EXT_MODE_RST       = 0x0001,     /*!< Reset Mode                */
    CAN_EXT_MODE_LISTEN    = 0x0002,     /*!< Listen Only Mode          */
    CAN_EXT_MODE_TEST      = 0x0004,     /*!< Self Test Mode            */
    CAN_EXT_MODE_ACC       = 0x0008,     /*!< Acceptance Filter Mode    */
};

/** CAN Extended Controller Command Register flags */
enum
{
    CAN_EXT_CMD_TXREQ      = 0x0001,     /*!< Transmit Request          */
    CAN_EXT_CMD_ABORT      = 0x0002,     /*!< Abort Transmission        */
    CAN_EXT_CMD_RXREL      = 0x0004,     /*!< Release Receive Buffer    */
    CAN_EXT_CMD_OVRCLR     = 0x0008,     /*!< Clear Data Overrun        */
    CAN_EXT_CMD_SELFREC    = 0x0010,     /*!< Self Reception Request    */
};

/** CAN Extended Controller Status Register flags */
enum
{
    CAN_EXT_STAT_RXBUF     = 0x0001,     /*!< Receive Buffer Status     */
    CAN_EXT_STAT_OVR       = 0x0002,     /*!< Data Overrun Status       */
    CAN_EXT_STAT_TXBUF     = 0x0004,     /*!< Transmit Buffer Status    */
    CAN_EXT_STAT_TXC       = 0x0008,     /*!< Transmission Complete     */
    CAN_EXT_STAT_RX        = 0x0010,     /*!< Receive Status            */
    CAN_EXT_STAT_TX        = 0x0020,     /*!< Transmit Status           */
    CAN_EXT_STAT_ERR       = 0x0040,     /*!< Error Status              */
    CAN_EXT_STAT_BUS       = 0x0080,     /*!< Bus Status                */
};

/** CAN Extended Controller Interrupt Register flags */
enum
{
    CAN_EXT_IRQ_RX         = 0x0001,     /*!< Receive Interrupt             */
    CAN_EXT_IRQ_TX         = 0x0002,     /*!< Transmit Interrupt            */
    CAN_EXT_IRQ_ERR        = 0x0004,     /*!< Error Interrupt               */
    CAN_EXT_IRQ_OVR        = 0x0008,     /*!< Overrun Interrupt             */
    CAN_EXT_IRQ_PARERR     = 0x0020,     /*!< Error Passive Interrupt       */
    CAN_EXT_IRQ_ARBLOST    = 0x0040,     /*!< Arbitration Lost Interrupt    */
    CAN_EXT_IRQ_BUSERR     = 0x0080,     /*!< Bus Error Interrupt           */
};

/** CAN Extended Controller Arbitration Lost Capture Register bit offsets */
enum
{
    CAN_EXT_ARBLOST_ALC_SHIFT     = 0,   /*!<  CAN Extended Slave Controller Arbitration Lost Capture Register Shift    */
};

/** CAN Extended Controller Arbitration Lost Capture Register masks */
enum
{
    CAN_EXT_ARBLOST_ALC_MASK      = 0x1F << CAN_EXT_ARBLOST_ALC_SHIFT,      /*!<  CAN Extended Slave Controller Arbitration Lost Capture Register Mask    */
};

/** @} */

#endif /* __CCPROC_AMBA_CAN_H */
/** @} */
