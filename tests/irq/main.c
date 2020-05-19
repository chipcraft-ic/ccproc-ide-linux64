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
#include <ccproc-amba-timer.h>
#include <stdio.h>

#define TEST_COUNTERS_MODIFIERS extern
#include "test.h"

#define TEST_MARKER 0x12345678
#define GUARD_MARKER 0x87654321
#define BIT(n) (1 << (n))


unsigned g_failedTests, g_totalTests;
static volatile unsigned expectIrq1 = 0, expectIrq2 = 0, expectIrq3 = 0, expectIrq4 = 0;
static volatile unsigned g_irqTestState = 0;

static void assertMemSize(uint32_t base, uint32_t size, char writeable)
{

    /* TODO: Need to be rewritten. Now core can assert exception on memory overflow */

    //volatile uint32_t data1, data2, *ptr;

    /*if (writeable)
        *((uint32_t*)base) = TEST_MARKER;

    data1 = *((uint32_t*)base);
    data2 = *((uint32_t*)(base + size));
    assertTrue(data1 == data2);

    if (writeable)
    {
        // write at the end of memory - lets assume we dont break anything
        ptr = (uint32_t*)(base + size);
        --ptr;
        *ptr = TEST_MARKER;

        assertEq(*(uint32_t*)(base + size - 4), TEST_MARKER);   // should match

        ptr = (uint32_t*)(base + size/2);
        --ptr;
        *ptr = GUARD_MARKER;

        assertEq(*(uint32_t*)(base + size - 4), TEST_MARKER);   // should match again
        assertEq(*(uint32_t*)(base + size*2 - 4), TEST_MARKER); // should overflow
    }*/
}

static void testCpuInfo(void)
{
    uint32_t info;

    info = CSR_CTRL_PTR->CPU_INFO_0;

    assertMemSize(ROM_BASE, CPU_INFO_GET_IMSIZE(info), 0);
    assertMemSize(RAM_BASE, CPU_INFO_GET_DMSIZE(info), 1);
    assertMemSize(SPRAM_BASE, CPU_INFO_GET_SPRSIZE(info), 1);
}

void isr1(void)
{
    assertTrue(expectIrq1);
    expectIrq1 = 0;
    AMBA_TIMER32_PTR(0)->IRQM = 0;
    AMBA_TIMER32_PTR(0)->IRQF = TIMER_OVFIF; // clear flag

    assertTrue(CSR_CTRL_PTR->STATUS & CSR_STAT_CIEN); // set in startup.S
    assertTrue(CSR_CTRL_PTR->STATUS & CSR_STAT_PIEN);

    if (g_irqTestState == 1)
    {
        g_irqTestState = 2;
        expectIrq2 = 1;
        AMBA_TIMER32_PTR(1)->IRQM = TIMER_OVFIE;

        // we are now preempted by IRQ2
        while (g_irqTestState != 7);

        // we are back
        g_irqTestState = 8;
    }
}

void isr2(void)
{
    assertTrue(expectIrq2);
    expectIrq2 = 0;
    AMBA_TIMER32_PTR(1)->IRQM = 0;
    AMBA_TIMER32_PTR(1)->IRQF = TIMER_OVFIF; // clear flag

    if (g_irqTestState == 2)
    {
        g_irqTestState = 3;
        expectIrq3 = 1;
        AMBA_TIMER16_PTR(0)->IRQM = TIMER_OVFIE;

        // we are now preempted by IRQ3
        while (g_irqTestState != 6);

        // we are back
        g_irqTestState = 7;
    }
}

void isr3(void)
{
    assertTrue(expectIrq3);
    expectIrq3 = 0;
    AMBA_TIMER16_PTR(0)->IRQM = 0;
    AMBA_TIMER16_PTR(0)->IRQF = TIMER_OVFIF; // clear flag

    assertTrue(CSR_CTRL_PTR->STATUS & CSR_STAT_CIEN); // set in startup.S
    assertTrue(CSR_CTRL_PTR->STATUS & CSR_STAT_PIEN);

    if (g_irqTestState == 3)
    {
        g_irqTestState = 4;
        expectIrq4 = 1;
        AMBA_TIMER16_PTR(1)->IRQM = TIMER_OVFIE;

        // we are now preempted by IRQ4
        while (g_irqTestState != 5);

        // we are back
        g_irqTestState = 6;
    }
}

void isr4(void)
{
    assertTrue(expectIrq4);
    expectIrq4 = 0;
    AMBA_TIMER16_PTR(1)->IRQM = 0;
    AMBA_TIMER16_PTR(1)->IRQF = TIMER_OVFIF; // clear flag

    if (g_irqTestState == 4)
        g_irqTestState = 5;
}

static void configTimerForIrqTest(volatile amba_timer_t *timer, unsigned irqNum)
{
    timer->PER = 3000;
    timer->PRES = 100;
    timer->COUNT = 0;
    timer->CTRL = TIMER_CTRL_EN;
    timer->IRQMAP = BIT(irqNum);
}

static void testInterrupts(void)
{
    volatile unsigned i = 0;

    g_irqTestState = 0;

    // Enable interrupts on core 0
    CSR_CTRL_PTR->IRQ_MASK |= BIT(1) | BIT(2) | BIT(3) | BIT(4); // IRQ 1 - 4
    CSR_CTRL_PTR->STATUS |= CSR_STAT_CIEN;

    // Configure 4 timers
    configTimerForIrqTest(AMBA_TIMER32_PTR(0), 1);
    configTimerForIrqTest(AMBA_TIMER32_PTR(1), 2);
    configTimerForIrqTest(AMBA_TIMER16_PTR(0), 3);
    configTimerForIrqTest(AMBA_TIMER16_PTR(1), 4);

    // Test single interrupt
    expectIrq1 = 1;
    AMBA_TIMER32_PTR(0)->IRQM = TIMER_OVFIE;
    for (i = 0; expectIrq1 && i < 10000000; ++i);
    assertFalse(expectIrq1);
    assertTrue(CSR_CTRL_PTR->STATUS & CSR_STAT_CIEN); // interrupts should still be enabled

    // Test preemption - first set priorities
    CSR_CTRL_PTR->IRQ_PRIOR[1] = 4;
    CSR_CTRL_PTR->IRQ_PRIOR[2] = 3;
    CSR_CTRL_PTR->IRQ_PRIOR[3] = 2;
    CSR_CTRL_PTR->IRQ_PRIOR[4] = 1;

    // Start testing IRQ preemption: IRQ1 -> IRQ2 -> IRQ3 -> IRQ4
    g_irqTestState = 1;
    expectIrq1 = 1;
    AMBA_TIMER32_PTR(0)->IRQM = TIMER_OVFIE;

    for (i = 0; g_irqTestState != 8 && i < 10000000; ++i);
    assertEq(g_irqTestState, 8);
    assertFalse(expectIrq1);
    assertFalse(expectIrq2);
    assertFalse(expectIrq3);
    assertFalse(expectIrq4);
    assertTrue(CSR_CTRL_PTR->STATUS & CSR_STAT_CIEN); // interrupts should still be enabled

    // disable IRQ 1 - 4
    CSR_CTRL_PTR->IRQ_MASK = BIT(0);
}

void testStackProtection(void);

int main(void)
{
    uint32_t status;

    printf("\nStarting IRQ Controller test.\n");
    CSR_CTRL_PTR->IRQ_MASK = BIT(0); // enable exceptions
    CSR_CTRL_PTR->STATUS |= CSR_STAT_CIEN;

    if ((AMBA_TIMER32_COUNT() < 2) || (AMBA_TIMER16_COUNT() < 2)){
        printf("Not enough timers to perform irq tests!\n");
        printTestSummary();
        return 0;
    }

    status = CSR_CTRL_PTR->STATUS;
    assertTrue(status & CSR_STAT_EXC);
    // NOTE: this bit is always zero in lockstep mode
    assertFalse(status & CSR_STAT_IP);
    assertFalse(status & CSR_STAT_BD);

    testCpuInfo();
    testInterrupts();

    if (CSR_CTRL_PTR->CPU_INFO_0 & CPU_SPROT)
    {
        printf("Detected stack protection.\n");
        testStackProtection();
    }

    printTestSummary();

    return 0;
}
