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
 * @file            ccproc-amba-eth.h
 * @brief           CC Processor AMBA ETH definitions
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_ETH_H
#define __CCPROC_AMBA_ETH_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup eth ETH Controller
 * ETH Controller registers and definitions
 * @{
 *//************************/

/** @brief ETH Registers */
typedef struct
{
    uint32_t MODER;        /*!<  Mode Register */
    uint32_t INT;          /*!<  Interrupt Source Register */
    uint32_t INT_MASK;     /*!<  Interrupt Mask Register */
    uint32_t IPGT;         /*!<  Back to Bak Inter Packet Gap Register */
    uint32_t IPGR1;        /*!<  Non Back to Back Inter Packet Gap Register 1 */
    uint32_t IPGR2;        /*!<  Non Back to Back Inter Packet Gap Register 2 */
    uint32_t PACKETLEN;    /*!<  Packet Length Register (min. and max.) */
    uint32_t COLLCONF;     /*!<  Collision and Retry Configuration Register */
    uint32_t TX_BD_NUM;    /*!<  Transmit Buffer Descriptor Number Register */
    uint32_t CTRLMODER;    /*!<  Control Module Mode Register */
    uint32_t MIIMODER;     /*!<  MII Mode Register */
    uint32_t MIICOMMAND;   /*!<  MII Command Register */
    uint32_t MIIADDRESS;   /*!<  MII Address Register */
    uint32_t MIITX_DATA;   /*!<  MII Transmit Data Register */
    uint32_t MIIRX_DATA;   /*!<  MII Receive Data Register */
    uint32_t MIISTATUS;    /*!<  MII Status Register */
    uint32_t MAC_ADDR0;    /*!<  MAC Individual Address Register 0 */
    uint32_t MAC_ADDR1;    /*!<  MAC Individual Address Register 1 */
    uint32_t HASH_ADDR0;   /*!<  Hash Register 0 */
    uint32_t HASH_ADDR1;   /*!<  Hash Register 1 */
    uint32_t TX_CTRL;      /*!<  Tx Control Register */
} amba_eth_t;

#define ETH_RX_FIFO_OFFSET 0x800        /*!< RX FIFO address offset        */
#define ETH_TX_FIFO_OFFSET 0xC00        /*!< TX FIFO address offset        */
#define ETH_FIFO_SIZE      256          /*!< FIFO size in words            */

/** @brief ETH buffer descriptor */
typedef struct{
    uint32_t LEN_STATUS;     /*!<  Buffer length and status */
    uint32_t ADDR;           /*!<  Buffer address           */
} amba_eth_bd_t;

#define ETH_BD_BASE 0x400                 /*!< Buffer Base   */
#define ETH_BD_NUM  128                   /*!< Buffer Number */

#define ETH_TXBD_DEF_BASE 0x400           /*!< Default TX Buffer Base */
#define ETH_RXBD_DEF_BASE 0x600           /*!< Default RX Buffer Base */

#define ETH_BD_MAKE_LEN(len) (len << 16)  /*!< Make Buffer Len */

#ifdef CCPROC_SDK
 #define AMBA_ETH_BASE(index) (AMBA_ETH0_BASE+(index)*0x1000)                                                          /*!< Ethernet base address           */
 #define AMBA_ETH_PTR(index) ((volatile amba_eth_t*)AMBA_ETH_BASE(index))                                              /*!< Ethernet pointer                */
 #define AMBA_ETH_RXBD_DEF_PTR(index,bd) ((volatile amba_eth_bd_t*)(AMBA_ETH_BASE(index)+ETH_RXBD_DEF_BASE+((bd)*8)))  /*!< Ethernet default RX pointer     */
 #define AMBA_ETH_TXBD_DEF_PTR(index,bd) ((volatile amba_eth_bd_t*)(AMBA_ETH_BASE(index)+ETH_TXBD_DEF_BASE+((bd)*8)))  /*!< Ethernet default RX pointer     */
 #define AMBA_ETH_RX_FIFO_PTR(index) ((uint32_t*)(AMBA_ETH_BASE(index)+ETH_RX_FIFO_OFFSET))                            /*!< Ethernet Rx Fifo Pointer        */
 #define AMBA_ETH_TX_FIFO_PTR(index) ((uint32_t*)(AMBA_ETH_BASE(index)+ETH_TX_FIFO_OFFSET))                            /*!< Ethernet Tx Fifo Pointer        */
#endif

/** MODER Register */
enum
{
    ETH_MODER_RXEN     = 0x00000001, /*!< Receive Enable  */
    ETH_MODER_TXEN     = 0x00000002, /*!< Transmit Enable */
    ETH_MODER_NOPRE    = 0x00000004, /*!< No Preamble  */
    ETH_MODER_BRO      = 0x00000008, /*!< Reject Broadcast */
    ETH_MODER_IAM      = 0x00000010, /*!< Use Individual Hash */
    ETH_MODER_PRO      = 0x00000020, /*!< Promiscuous (receive all) */
    ETH_MODER_IFG      = 0x00000040, /*!< Min. IFG not required */
    ETH_MODER_LOOPBCK  = 0x00000080, /*!< Loop Back */
    ETH_MODER_NOBCKOF  = 0x00000100, /*!< No Backoff */
    ETH_MODER_EXDFREN  = 0x00000200, /*!< Excess Defer */
    ETH_MODER_FULLD    = 0x00000400, /*!< Full Duplex */
    ETH_MODER_RST      = 0x00000800, /*!< Reset MAC */
    ETH_MODER_DLYCRCEN = 0x00001000, /*!< Delayed CRC Enable */
    ETH_MODER_CRCEN    = 0x00002000, /*!< CRC Enable */
    ETH_MODER_HUGEN    = 0x00004000, /*!< Huge Enable */
    ETH_MODER_PAD      = 0x00008000, /*!< Pad Enable */
    ETH_MODER_RECSMALL = 0x00010000, /*!< Receive Small */
};

/**  Interrupt Source Register */
enum
{
    ETH_INT_TXB        = 0x00000001, /*!< Transmit Buffer IRQ */
    ETH_INT_TXE        = 0x00000002, /*!< Transmit Error IRQ */
    ETH_INT_RXF        = 0x00000004, /*!< Receive Frame IRQ */
    ETH_INT_RXE        = 0x00000008, /*!< Receive Error IRQ */
    ETH_INT_BUSY       = 0x00000010, /*!< Busy IRQ */
    ETH_INT_TXC        = 0x00000020, /*!< Transmit Control Frame IRQ */
    ETH_INT_RXC        = 0x00000040, /*!< Received Control Frame IRQ */
};

/**  Interrupt Mask Register */
enum
{
    ETH_INT_MASK_TXB   = 0x00000001, /*!< Transmit Buffer IRQ Mask */
    ETH_INT_MASK_TXE   = 0x00000002, /*!< Transmit Error IRQ Mask */
    ETH_INT_MASK_RXF   = 0x00000004, /*!< Receive Frame IRQ Mask */
    ETH_INT_MASK_RXE   = 0x00000008, /*!< Receive Error IRQ Mask */
    ETH_INT_MASK_BUSY  = 0x00000010, /*!< Busy IRQ Mask */
    ETH_INT_MASK_TXC   = 0x00000020, /*!< Transmit Control Frame IRQ Mask */
    ETH_INT_MASK_RXC   = 0x00000040, /*!< Received Control Frame IRQ Mask */
};

/**  Control Module Mode Register */
enum
{
    ETH_CTRLMODER_PASSALL = 0x00000001, /*!< Pass Control Frames */
    ETH_CTRLMODER_RXFLOW  = 0x00000002, /*!< Receive Control Flow Enable */
    ETH_CTRLMODER_TXFLOW  = 0x00000004, /*!< Transmit Control Flow Enable */
};

/**  MII Mode Register */
enum
{
    ETH_MIIMODER_CLKDIV   = 0x000000FF, /*!< Clock Divider */
    ETH_MIIMODER_NOPRE    = 0x00000100, /*!< No Preamble */
    ETH_MIIMODER_RST      = 0x00000200, /*!< MIIM Reset */
};

/**  MII Command Register */
enum
{
    ETH_MIICOMMAND_SCANSTAT  = 0x00000001, /*!< Scan Status */
    ETH_MIICOMMAND_RSTAT     = 0x00000002, /*!< Read Status */
    ETH_MIICOMMAND_WCTRLDATA = 0x00000004, /*!< Write Control Data */
};

/**  MII Address Register */
enum
{
    ETH_MIIADDRESS_FIAD = 0x0000001F, /*!< PHY Address  */
    ETH_MIIADDRESS_RGAD = 0x00001F00, /*!< RGAD Address */
};

/**  MII Status Register */
enum
{
    ETH_MIISTATUS_LINKFAIL = 0x00000001, /*!< Link Fail */
    ETH_MIISTATUS_BUSY     = 0x00000002, /*!< MII Busy */
    ETH_MIISTATUS_NVALID   = 0x00000004, /*!< Data in MII Status Register is invalid */
};

/** Rx BD */
enum
{
    ETH_RX_BD_EMPTY    = 0x8000,  /*!< Rx BD Empty */
    ETH_RX_BD_IRQ      = 0x4000,  /*!< Rx BD IRQ Enable */
    ETH_RX_BD_WRAP     = 0x2000,  /*!< Rx BD Wrap (last BD) */
    ETH_RX_BD_MISS     = 0x0080,  /*!< Rx BD Miss Status */
    ETH_RX_BD_OVERRUN  = 0x0040,  /*!< Rx BD Overrun Status */
    ETH_RX_BD_INVSIMB  = 0x0020,  /*!< Rx BD Invalid Symbol Status */
    ETH_RX_BD_DRIBBLE  = 0x0010,  /*!< Rx BD Dribble Nibble Status */
    ETH_RX_BD_TOOLONG  = 0x0008,  /*!< Rx BD Too Long Status */
    ETH_RX_BD_SHORT    = 0x0004,  /*!< Rx BD Too Short Frame Status */
    ETH_RX_BD_CRCERR   = 0x0002,  /*!< Rx BD CRC Error Status */
    ETH_RX_BD_LATECOL  = 0x0001,  /*!< Rx BD Late Collision Status */
};

/** Tx BD */
enum
{
    ETH_TX_BD_READY    = 0x8000,  /*!< Tx BD Ready */
    ETH_TX_BD_IRQ      = 0x4000,  /*!< Tx BD IRQ Enable */
    ETH_TX_BD_WRAP     = 0x2000,  /*!< Tx BD Wrap (last BD) */
    ETH_TX_BD_PAD      = 0x1000,  /*!< Tx BD Pad Enable */
    ETH_TX_BD_CRC      = 0x0800,  /*!< Tx BD CRC Enable */
    ETH_TX_BD_UNDERRUN = 0x0100,  /*!< Tx BD Underrun Status */
    ETH_TX_BD_RETRY    = 0x00F0,  /*!< Tx BD Retry Status */
    ETH_TX_BD_RETLIM   = 0x0008,  /*!< Tx BD Retransmission Limit Status */
    ETH_TX_BD_LATECOL  = 0x0004,  /*!< Tx BD Late Collision Status */
    ETH_TX_BD_DEFER    = 0x0002,  /*!< Tx BD Defer Status */
    ETH_TX_BD_CARRIER  = 0x0001,  /*!< Tx BD Carrier Sense Lost Status */
};

/** @} */

#endif /* __CCPROC_AMBA_ETH_H */
/** @} */

