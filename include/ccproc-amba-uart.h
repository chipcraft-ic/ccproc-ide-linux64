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
 * @file            ccproc-amba-uart.h
 * @brief           CC Processor AMBA UART definitions
 * @author          Rafal Harabien
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_UART_H
#define __CCPROC_AMBA_UART_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup uart UART Controller
 * UART Controller registers and definitions
 * @{
 *//************************/

/** AMBA UART registers */
typedef struct
{
    uint32_t STATUS;       /*!< Status Register                              */
    uint32_t PRES;         /*!< Prescaler Register (lo mantisa, hi fraction) */
    uint32_t CTRL;         /*!< Control Register                             */
    uint32_t MODE;         /*!< Mode Register                                */
    uint32_t TDR;          /*!< TX data Register                             */
    uint32_t RDR;          /*!< RX data Register                             */
    uint32_t IRQM;         /*!< Interrupt mask Register                      */
    uint32_t IRQF;         /*!< Interrupt flags Register                     */
    uint32_t IRQMAP;       /*!< Interrupt mapping                            */
    uint32_t TMNG;         /*!< RS485 timings Register                       */
} amba_uart_t;

#ifdef CCPROC_SDK

 #define AMBA_UART_BASE(index) (AMBA_UART0_BASE+(index)*0x100)                /*!< UART base address             */
 #define AMBA_UART_PTR(index) ((volatile amba_uart_t*)AMBA_UART_BASE(index))  /*!< UART pointer                  */
 #define AMBA_UART_IRQn(index) (AMBA_UART0_IRQn + (index) % 4)                /*!< UART default interrupt number */

#endif

/** UART STATUS register flags */
enum
{
    UART_STAT_RXC      = 0x01,  /*!< Reception Complete               */
    UART_STAT_TXC      = 0x02,  /*!< Transmission Complete            */
    UART_STAT_TXDRE    = 0x04,  /*!< Transmission Data Register Empty */
    UART_STAT_PERR     = 0x08,  /*!< Parity Error                     */
    UART_STAT_FRERR    = 0x10,  /*!< Framing Error                    */
    UART_STAT_OVERR    = 0x20,  /*!< Overrun Error                    */
    UART_STAT_RXBRK    = 0x40,  /*!< Break Reception                  */
    UART_STAT_CTS      = 0x80,  /*!< CTS (Clear To Send) Status       */
};

/** Prescaler helper macro */
#define AMBA_UART_PRES(mantisa, fraction) ((mantisa) | ((fraction) << 16))  /*!< Prescaler from mantisa and fraction */

/** UART CTRL register flags */
enum
{
    UART_CTRL_TXEN      = 0x01,  /*!< Transmitter Enable          */
    UART_CTRL_RXEN      = 0x02,  /*!< Receiver Enable             */
    UART_CTRL_RTSEN     = 0x04,  /*!< RTS Hardware Support Enable */
    UART_CTRL_CTSEN     = 0x08,  /*!< CTS Hardware Support Enable */
    UART_CTRL_BREAK     = 0x10,  /*!< Transmit BREAK Frame        */
    UART_CTRL_LOOP      = 0x20,  /*!< Loopback Mode Enable        */
};

/** UART MODE register flags */
enum
{
    UART_MODE_OVRS8          = 0x01,  /*!< OVERSAMPLING8 Enable */
    UART_MODE_BIG_ENDIAN     = 0x02,  /*!< Big Endian Enable    */

    /* Character Length */
    UART_MODE_CHRL5          = 0x3 << 2,  /*!< 5 Data Bits      */
    UART_MODE_CHRL6          = 0x2 << 2,  /*!< 6 Data Bits      */
    UART_MODE_CHRL7          = 0x1 << 2,  /*!< 7 Data Bits      */
    UART_MODE_CHRL8          = 0x0 << 2,  /*!< 8 Data Bits      */
    UART_MODE_CHRL9          = 0x4 << 2,  /*!< 9 Data Bits      */

    /* Stop Bits Number */
    UART_MODE_STOP_BITS_1    = 0x0 << 5,  /*!< 1 Stop Bit       */
    UART_MODE_STOP_BITS_2    = 0x1 << 5,  /*!< 2 Stop Bits      */

    /* Parity */
    UART_MODE_PARITY_NONE    = 0x0 << 7,  /*!< No Parity        */
    UART_MODE_PARITY_EVEN    = 0x1 << 7,  /*!< Even Parity      */
    UART_MODE_PARITY_ODD     = 0x2 << 7,  /*!< Odd Parity       */
    UART_MODE_PARITY_FORCED0 = 0x3 << 7,  /*!< Force 0 Parity   */
    UART_MODE_PARITY_FORCED1 = 0x4 << 7,  /*!< Force 1 Parity   */

    /* RS485 Mode */
    UART_MODE_RS485EN        = 1 << 10,  /*!< RS485 Mode Enable */
};

/** UART interrupt mask */
enum
{
    UART_RXCIE   = 0x0001,  /*!< Reception Complete Interrupt Enable           */
    UART_TXCIE   = 0x0002,  /*!< Transmission Complete Interrupt Enable        */
    UART_TXDIE   = 0x0004,  /*!< Transmit Data Register Empty Interrupt Enable */
    UART_PERIE   = 0x0008,  /*!< Parity Error Interrupt Enable                 */
    UART_FERIE   = 0x0010,  /*!< Framing Error Interrupt Enable                */
    UART_OVERIE  = 0x0020,  /*!< Overrun Error Interrupt Enable                */
    UART_BRKRIE  = 0x0040,  /*!< Break Reception Start Interrupt Enable        */
    UART_BRKEIE  = 0x0080,  /*!< Break Reception End Interrupt Enable          */
    UART_CTSRIE  = 0x0100,  /*!< Rising Edge on CTS Line Interrupt Enable      */
};

/** UART interrupt flags */
enum
{
    UART_RXCIF   = 0x0001,  /*!< Reception Complete Interrupt Flag           */
    UART_TXCIF   = 0x0002,  /*!< Transmission Complete Interrupt Flag        */
    UART_TXDIF   = 0x0004,  /*!< Transmit Data Register Empty Interrupt Flag */
    UART_PERIF   = 0x0008,  /*!< Parity Error Interrupt Flag                 */
    UART_FERIF   = 0x0010,  /*!< Framing Error Interrupt Flag                */
    UART_OVERIF  = 0x0020,  /*!< Overrun Error Interrupt Flag                */
    UART_BRKRIF  = 0x0040,  /*!< Break Reception Start Interrupt Flag        */
    UART_BRKEIF  = 0x0080,  /*!< Break Reception End Interrupt Flag          */
    UART_CTSRIF  = 0x0100,  /*!< Rising Edge on CTS Line Interrupt Flag      */
};

/** RS485 timings bit offsets */
enum
{
    UART_TMNG_485PRE_SHIFT     = 0,   /*!< RS485 mode pre-start bits shift    */
    UART_TMNG_485POST_SHIFT    = 16,  /*!< RS485 mode post-stop bits shift    */
};

/** RS485 timings bit masks */
enum
{
    UART_TMNG_485PRE_MASK     = 0x0F << UART_TMNG_485PRE_SHIFT,      /*!< RS485 mode pre-start bits mask    */
    UART_TMNG_485POST_MASK    = 0x0F << UART_TMNG_485POST_SHIFT,     /*!< RS485 mode post-stop bits mask    */
};

/** @} */

#endif /* __CCPROC_AMBA_UART_H */
/** @} */
