/*H*****************************************************************************
*
* Copyright (c) 2018 ChipCraft Sp. z o.o. All rights reserved
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
* File Name : async_uart.c
* Author    : Rafal Harabien
* ******************************************************************************
* $Date: 2020-05-05 19:26:31 +0200 (wto, 05 maj 2020) $
* $Revision: 572 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-csr.h>
#include <ccproc-amba.h>
#include <ccproc-amba-uart.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include "async_uart.h"

#ifndef STDOUT_BUF_SIZE
 #define STDOUT_BUF_SIZE 256
#endif

char g_StdOutBuf[STDOUT_BUF_SIZE];
volatile int g_StdOutBufReadPos = 0, g_StdOutBufWritePos = 0;

void isr1(void)
{
    volatile amba_uart_t *uart = AMBA_UART_PTR(0);
    uint32_t flags = uart->IRQF;
    if (flags & UART_TXCIF)
    {
        uart->IRQF |= UART_TXCIE;
        char ch = g_StdOutBuf[g_StdOutBufReadPos];
        uart->TDR = ch;
        g_StdOutBufReadPos = (g_StdOutBufReadPos + 1) % STDOUT_BUF_SIZE;
        // critical section begin
        if (g_StdOutBufReadPos == g_StdOutBufWritePos)
        {
            uart->IRQM = 0;
            // disable interrupt
        }
        // critical section end
    }
}

static void uartStartAsyncWriting(unsigned uart, unsigned writePos)
{
    volatile amba_uart_t *uartPtr = AMBA_UART_PTR(uart);
    // critical section
    g_StdOutBufWritePos = writePos;
    // is writing active?
    if (!(uartPtr->IRQM & UART_TXCIE))
    {
        // enable interrupt
        uartPtr->IRQM = UART_TXCIE;
        // write first character
        char ch = g_StdOutBuf[g_StdOutBufReadPos];
        g_StdOutBufReadPos = (g_StdOutBufReadPos + 1) % STDOUT_BUF_SIZE;
        uartPtr->TDR = ch;
    }
    // critical section end
}

void uartWriteAsync(unsigned uart, const char *data, unsigned int count)
{
    volatile amba_uart_t *uartPtr = AMBA_UART_PTR(uart);
    unsigned writePos = g_StdOutBufWritePos;
    for (unsigned i = 0; i < count; i++) {
        if ((writePos + 1) % STDOUT_BUF_SIZE == g_StdOutBufReadPos) // full
        {
            // start writting process if not already running
            uartStartAsyncWriting(uart, writePos);
            // wait for free space in buffer
            while ((writePos + 1) % STDOUT_BUF_SIZE == g_StdOutBufReadPos);
        }
        // add character at the end of buffer
        char ch = data[i];
        g_StdOutBuf[writePos] = ch;
        writePos = (writePos + 1) % STDOUT_BUF_SIZE;
    }
    uartStartAsyncWriting(uart, writePos);
    
}

void uartInitAsync(unsigned uart)
{
    volatile amba_uart_t *uartPtr = AMBA_UART_PTR(uart);
    CSR_CTRL_PTR->IRQ_MASK |= (1 << 1);
    CSR_CTRL_PTR->STATUS |= CSR_STAT_CIEN;
}
