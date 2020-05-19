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
* File Name : main.c
* Author    : Rafal Harabien
* ******************************************************************************
* $Date: 2019-04-23 10:51:59 +0200 (wto, 23 kwi 2019) $
* $Revision: 412 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-csr.h>
#include <ccproc-amba.h>
#include <ccproc-amba-uart.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#define TEST_CONTEXT_FMT " uart %d"
#define TEST_CONTEXT_VARS ,uart_index
#include "test.h"

#define UART_BAUDRATE 38400

static volatile uint32_t expected_irqf;
static unsigned uart_index;
static volatile amba_uart_t *uart;

void isr1(void)
{
    uint32_t flags = uart->IRQF;
    ok_eq(flags, expected_irqf);
    ok_eq(uart->IRQF, expected_irqf); // reading doesnt clear flag
    uart->IRQF = ~expected_irqf;
    ok_eq(uart->IRQF, expected_irqf); // active written bits clears flags

    if (flags & UART_TXDIE)
        uart->IRQM = 0;
        //uart->TDR = ' '; // something has to be written to TDR

    uart->IRQF = flags; // writing to register clears flags
    ok_eq(uart->IRQF, 0);
    
    expected_irqf = 0;
}

static unsigned long long getusec()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv.tv_sec*1000000ULL + tv.tv_usec;
}

void test_uart(int index)
{
    volatile unsigned i;
    uint64_t startUsec;
    unsigned dt;

    uart_index = index;
    uart = AMBA_UART_PTR(index);

    uart->PRES = AMBA_UART_PRES((PERIPH0_FREQ / UART_BAUDRATE) / 16, (PERIPH0_FREQ / UART_BAUDRATE) % 16);
    uart->MODE = UART_MODE_CHRL8 | UART_MODE_STOP_BITS_1 | UART_MODE_PARITY_NONE;
    uart->CTRL = UART_CTRL_TXEN | UART_CTRL_RXEN; // RX enable, TX enable

    ok_eq(uart->STATUS, UART_STAT_TXDRE);
    ok_eq(uart->IRQM, 0);
    ok_eq(uart->IRQF, 0);
    ok_eq(uart->IRQMAP, 1 << AMBA_UART_IRQn(index));

    uart->TDR = ' ';
    for (i = 0; i < 10; ++i);
    ok_eq(uart->STATUS, UART_STAT_TXDRE); // data copied to internal buffer

    while (!(uart->STATUS & UART_STAT_TXC)); // wait for transmision complete
    ok_eq(uart->STATUS, UART_STAT_TXC|UART_STAT_TXDRE);
    ok_eq(uart->IRQF, 0);

    // start using loopback
    uart->CTRL |= UART_CTRL_LOOP;

    // test simple transmission
    uart->TDR = ' ';
    while (!(uart->STATUS & UART_STAT_RXC)); // wait for reception complete
    ok_eq(uart->STATUS, UART_STAT_TXDRE|UART_STAT_RXC); // RXC is set before TXC
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for transmision complete
    ok_eq(uart->STATUS, UART_STAT_TXC|UART_STAT_TXDRE|UART_STAT_RXC);
    ok_eq(uart->IRQF, 0);
    ok_eq(uart->RDR, ' '); // reading from RDR resets RXC flag
    ok_eq(uart->STATUS, UART_STAT_TXC|UART_STAT_TXDRE);

    // test overrun
    uart->TDR = ' ';
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for transmision complete
    ok_eq(uart->STATUS, UART_STAT_TXC|UART_STAT_TXDRE|UART_STAT_RXC);

    // fill aurt rx fifo
    uart->TDR = ' '; // send next byte before reception
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for transmision complete
    uart->TDR = ' '; // send next byte before reception
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for transmision complete
    uart->TDR = ' '; // send next byte before reception
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for transmision complete
    uart->TDR = ' '; // send next byte before reception
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for transmision complete

    ok_eq(uart->STATUS, UART_STAT_TXC|UART_STAT_TXDRE|UART_STAT_RXC|UART_STAT_OVERR);
    ok_eq(uart->IRQF, 0);

    ok_eq(uart->RDR, ' ');
    ok_eq(uart->RDR, ' ');
    ok_eq(uart->RDR, ' ');
    ok_eq(uart->RDR, ' '); // reading from RDR fifo resets RXC flag
    ok_eq(uart->STATUS, UART_STAT_TXC|UART_STAT_TXDRE);

    // start BREAK frame
    uart->CTRL |= UART_CTRL_BREAK;
    for (i = 0; i < 100000; ++i);
    ok_eq(uart->STATUS, UART_STAT_TXDRE|UART_STAT_RXBRK);
    ok_eq(uart->IRQF, 0);
    ok_eq(uart->RDR, ' '); // old value
    ok_eq(uart->STATUS, UART_STAT_TXDRE|UART_STAT_RXBRK); // RXBRK has not been reset

    // end BREAK frame
    uart->CTRL &= ~UART_CTRL_BREAK;
    for (i = 0; i < 100000; ++i);
    ok_eq(uart->STATUS, UART_STAT_TXC|UART_STAT_RXC|UART_STAT_TXDRE|UART_STAT_RXBRK);
    ok_eq(uart->IRQF, 0);
    ok_eq(uart->RDR, 0); // reset RXC and RXBRK flags
    ok_eq(uart->STATUS, UART_STAT_TXDRE|UART_STAT_TXC);

    ////////////////
    // INTERRUPTS
    ////////////////

    uart->IRQMAP = 1 << 1;

    // test RXCIE
    uart->IRQM = UART_RXCIE;
    expected_irqf = UART_RXCIF;
    uart->TDR = ' ';
    while (!(uart->STATUS & UART_STAT_RXC)); // wait for reception complete
    while (!(uart->STATUS & UART_STAT_TXC));
    for (i = 0; i < 10; ++i);
    ok_eq(expected_irqf, 0);
    ok_eq(uart->RDR, ' '); // reset RXC flag

    // test TXCIE
    uart->IRQM = UART_TXCIE;
    uart->TDR = ' ';
    expected_irqf = UART_TXCIF;
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for reception complete (TXC is after RXC)
    for (i = 0; i < 10; ++i);
    ok_eq(expected_irqf, 0);
    ok_eq(uart->RDR, ' '); // reset RXC flag

    // test TXDIE
    expected_irqf = UART_TXDIF;
    uart->IRQM = UART_TXDIE;
    uart->TDR = ' ';
    while (!(uart->STATUS & UART_STAT_RXC)); // wait for reception complete
    while (!(uart->STATUS & UART_STAT_TXC));
    for (i = 0; i < 10; ++i);
    ok_eq(expected_irqf, 0);
    ok_eq(uart->RDR, ' '); // reset RXC flag

    // TODO: how to test PERIE and FERIE?

    // test OVERIE
    uart->IRQM = UART_OVERIE;
    uart->TDR = ' ';
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for reception complete
    expected_irqf = UART_OVERIF;

    // fill aurt rx fifo
    uart->TDR = ' ';
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for reception complete
    uart->TDR = ' ';
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for reception complete
    uart->TDR = ' ';
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for reception complete
    uart->TDR = ' ';
    while (!(uart->STATUS & UART_STAT_TXC)); // wait for reception complete

    for (i = 0; i < 100; ++i);
    ok_eq(uart->STATUS, UART_STAT_TXC|UART_STAT_TXDRE|UART_STAT_RXC|UART_STAT_OVERR);
    ok_eq(expected_irqf, 0);

    ok_eq(uart->RDR, ' ');
    ok_eq(uart->RDR, ' ');
    ok_eq(uart->RDR, ' ');
    ok_eq(uart->RDR, ' '); // reading from RDR fifo resets RXC flag

    // test BRKRIE
    uart->IRQM = UART_BRKRIE;
    expected_irqf = UART_BRKRIF;
    uart->CTRL |= UART_CTRL_BREAK;
    for (i = 0; i < 10000; ++i);
    ok_eq(expected_irqf, 0);

    // test BRKEIE
    uart->IRQM = UART_BRKEIE;
    expected_irqf = UART_BRKEIF;
    uart->CTRL &= ~UART_CTRL_BREAK;
    for (i = 0; i < 10000; ++i);
    ok_eq(expected_irqf, 0);
    ok_eq(uart->RDR, 0); // reset RXC flag

    // TODO: how to test UART_CTSRIE

    uart->IRQM = 0;

    ////////////////////
    // test MODE (CHRL)
    ////////////////////

    uart->MODE = UART_MODE_CHRL5;
    uart->TDR = 0xFFFF;
    while (!(uart->STATUS & UART_STAT_RXC));
    ok_eq(uart->RDR, 0x1F);

    uart->MODE = UART_MODE_CHRL6;
    uart->TDR = 0xFFFF;
    while (!(uart->STATUS & UART_STAT_RXC));
    ok_eq(uart->RDR, 0x3F);

    uart->MODE = UART_MODE_CHRL7;
    uart->TDR = 0xFFFF;
    while (!(uart->STATUS & UART_STAT_RXC));
    ok_eq(uart->RDR, 0x7F);

    uart->MODE = UART_MODE_CHRL8;
    uart->TDR = 0xFFFF;
    while (!(uart->STATUS & UART_STAT_RXC));
    ok_eq(uart->RDR, 0xFF);

    uart->MODE = UART_MODE_CHRL9;
    uart->TDR = 0xFFFF;
    while (!(uart->STATUS & UART_STAT_RXC));
    ok_eq(uart->RDR, 0x1FF);

    // check if OVRS8 doesnt break anything
    uart->MODE = UART_MODE_OVRS8;
    uart->TDR = 17;
    while (!(uart->STATUS & UART_STAT_RXC));
    ok_eq(uart->RDR, 17);

    // check if BIG_ENDIAN doesnt break anything
    uart->MODE = UART_MODE_BIG_ENDIAN;
    uart->TDR = 12;
    while (!(uart->STATUS & UART_STAT_RXC));
    ok_eq(uart->RDR, 12);

    uart->MODE = UART_MODE_CHRL8; // back to normal

    ///////////////
    // test PRSC
    ///////////////

    uart->CTRL &= ~UART_CTRL_LOOP;

    uart->PRES = AMBA_UART_PRES((PERIPH0_FREQ / 9600) / 16, (PERIPH0_FREQ / 19200) % 16);
    startUsec = getusec();
    uart->TDR = ' ';
    while ((uart->STATUS & (UART_STAT_TXC)) != (UART_STAT_TXC));
    dt = (unsigned)(getusec() - startUsec);
    ok(dt > 1000 && dt < 1250, "Expected baudrate 9600 (dt %u)", dt);

    uart->PRES = AMBA_UART_PRES((PERIPH0_FREQ / 19200) / 16, (PERIPH0_FREQ / 19200) % 16);
    startUsec = getusec();
    uart->TDR = ' ';
    while ((uart->STATUS & (UART_STAT_TXC)) != (UART_STAT_TXC));
    dt = (unsigned)(getusec() - startUsec);
    ok(dt > 500 && dt < 625, "Expected baudrate 19200 (dt %u)", dt);
}

int main(void)
{
    unsigned uart_num, i;

    uart_num = AMBA_UART_COUNT();
    printf("\nStarting UART test (found %u UARTs)\n", uart_num);

    // Enable interrupts
    CSR_CTRL_PTR->IRQ_MASK |= (1 << 1) | (1 << 0); // IRQ 1 and exceptions
    CSR_CTRL_PTR->STATUS |= CSR_STAT_CIEN;

    // Test all UARTs
    for (i = 0; i < uart_num; ++i)
    {
        if (i != STDIO_UART && i != 0)
            test_uart(i);
    }

    print_test_summary();

    return 0;
}
