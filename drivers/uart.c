/*H*****************************************************************************
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
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
*
* ******************************************************************************
* File Name : uart.c
* Author    : Rafal Harabien
* ******************************************************************************
* $Date: 2019-12-27 16:05:17 +0100 (pią, 27 gru 2019) $
* $Revision: 494 $
*H*****************************************************************************/

#include <stddef.h>
#include <ccproc.h>
#include <ccproc-amba.h>
#include <ccproc-amba-uart.h>
#include <board.h>

int uart_init_blocking(int uart, uint32_t baudrate, int rtscts)
{
    /* Check if baudrate is valid */
    if (PERIPH0_FREQ / baudrate / 16 == 0 || PERIPH0_FREQ / baudrate / 16 > 65535) {
        return -1;
    }

    /* Update UART registers */
    volatile amba_uart_t *u = AMBA_UART_PTR(uart);
    u->PRES = AMBA_UART_PRES((PERIPH0_FREQ / baudrate) / 16, (PERIPH0_FREQ / baudrate) % 16);
    u->MODE = UART_MODE_CHRL8 | UART_MODE_STOP_BITS_1 | UART_MODE_PARITY_NONE;
    u->CTRL = UART_CTRL_TXEN | UART_CTRL_RXEN; // RX enable, TX enable
    if (rtscts) {
        u->CTRL |= UART_CTRL_RTSEN | UART_CTRL_CTSEN; // RTS/CTS enable
    }
    return 0;
}

int uart_write_blocking(int uart, char data)
{
    volatile amba_uart_t *u = AMBA_UART_PTR(uart);

    /* Check if TX is enabled */
    if (!(u->CTRL & UART_CTRL_TXEN)) {
        return -1;
    }

    /* wait for empty TX buffer */
    while (!(u->STATUS & UART_STAT_TXDRE));

    /* begin transmission */
    u->TDR = data;

    /* wait for transmission end */
    while (!(u->STATUS & UART_STAT_TXC));

    return 0;
}

int uart_read_blocking(int uart, char *data)
{
    volatile amba_uart_t *u = AMBA_UART_PTR(uart);

    /* Check if RX is enabled*/
    if (!(u->CTRL & UART_CTRL_RXEN)) {
        return -1;
    }

    /* wait for data reception */
    while (!(u->STATUS & UART_STAT_RXC));

    /* read data */
    *data = u->RDR;

    return 0;
}
