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
* $Date: 2018-09-07 16:07:40 +0200 (pią) $
* $Revision: 296 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-irq.h>
#include <ccproc-amba.h>
#include <ccproc-amba-systick.h>
#include <stdio.h>
#include "test.h"

static volatile uint32_t g_expectedIrq3 = 0;
static volatile uint32_t g_expectedIrq4 = 0;

void isr3(void)
{
    volatile uint32_t i;

    //assertEq(AMBA_SYSTICK_PTR->COUNT, 1000); // check COUNT first
    i = (AMBA_SYSTICK_PTR->COUNT)%1000;
    assertEq(i, 0); // check COUNT first
    assertTrue(g_expectedIrq3);
    g_expectedIrq3 = 0;
    assertEq(AMBA_SYSTICK_PTR->IRQF, SYSTICK_IF);
    assertEq(AMBA_SYSTICK_PTR->IRQF, 0);
}

void isr4(void)
{
    volatile uint32_t i;

    //assertEq(AMBA_SYSTICK_PTR->COUNT, 1000); // check COUNT first
    i = (AMBA_SYSTICK_PTR->COUNT)%1000;
    assertEq(i, 0); // check COUNT first
    assertTrue(g_expectedIrq4);
    g_expectedIrq4 = 0;
    AMBA_SYSTICK_PTR->IRQF = SYSTICK_IF;
    assertEq(AMBA_SYSTICK_PTR->IRQF, 0);
}

static void testSysTick(void)
{
    volatile unsigned i = 0;

    AMBA_SYSTICK_PTR->CTRL = 0;
    AMBA_SYSTICK_PTR->COUNT = 0;
    AMBA_SYSTICK_PTR->PRES = 255;
    AMBA_SYSTICK_PTR->PER = 1000;
    for (i = 0; i < 1000; ++i);
    assertEq(AMBA_SYSTICK_PTR->COUNT, 0);
    assertEq(AMBA_SYSTICK_PTR->IRQF, 0);

    AMBA_SYSTICK_PTR->CTRL = SYSTICK_CTRL_EN;

    while (AMBA_SYSTICK_PTR->COUNT == 0);
    assertEq(AMBA_SYSTICK_PTR->COUNT, 1);

    while (AMBA_SYSTICK_PTR->COUNT == 1);
    assertEq(AMBA_SYSTICK_PTR->COUNT, 2);

    assertEq(AMBA_SYSTICK_PTR->IRQF, 0);

    AMBA_SYSTICK_PTR->COUNT = 998;
    while (AMBA_SYSTICK_PTR->COUNT == 998);
    assertEq(AMBA_SYSTICK_PTR->COUNT, 999);
    assertEq(AMBA_SYSTICK_PTR->IRQF, 0);
    while (AMBA_SYSTICK_PTR->COUNT == 999);
    assertEq(AMBA_SYSTICK_PTR->COUNT, 1000);
    assertEq(AMBA_SYSTICK_PTR->IRQF, SYSTICK_IF);
    assertEq(AMBA_SYSTICK_PTR->IRQF, 0); // reading IRQF cleared flags
    while (AMBA_SYSTICK_PTR->COUNT == 1000);
    assertEq(AMBA_SYSTICK_PTR->COUNT, 0);
    while (AMBA_SYSTICK_PTR->COUNT == 0);
    assertEq(AMBA_SYSTICK_PTR->COUNT, 1);
    assertEq(AMBA_SYSTICK_PTR->IRQF, 0);

    // Interrupt
    assertEq(AMBA_SYSTICK_PTR->IRQMAP, 1 << AMBA_STT_IRQn);
    AMBA_SYSTICK_PTR->IRQMAP = 1 << 3;
    AMBA_SYSTICK_PTR->CTRL |= SYSTICK_CTRL_IE;
    g_expectedIrq3 = 1;
    AMBA_SYSTICK_PTR->COUNT = 999;
    while (AMBA_SYSTICK_PTR->COUNT != 100);

    assertFalse(g_expectedIrq3);
    AMBA_SYSTICK_PTR->IRQMAP = 1 << 4;
    g_expectedIrq4 = 1;
    AMBA_SYSTICK_PTR->COUNT = 999;
    while (AMBA_SYSTICK_PTR->COUNT != 100);
    assertFalse(g_expectedIrq4);

    AMBA_SYSTICK_PTR->COUNT = 1000; // set to PER -> no interrupt
    while (AMBA_SYSTICK_PTR->COUNT == 1000);
    assertEq(AMBA_SYSTICK_PTR->COUNT, 0);

    AMBA_SYSTICK_PTR->COUNT = 1005; // above PER - SysTick doesn't reset
    assertEq(AMBA_SYSTICK_PTR->COUNT, 1005);
    while (AMBA_SYSTICK_PTR->COUNT == 1005);
    assertEq(AMBA_SYSTICK_PTR->COUNT, 1006);
    while (AMBA_SYSTICK_PTR->COUNT == 1006);
    assertEq(AMBA_SYSTICK_PTR->COUNT, 1007);

    // Disable
    AMBA_SYSTICK_PTR->CTRL = 0;
}

int main(void)
{
    printf("\nStarting SysTick test\n");

    IRQ_CTRL_PTR->IRQ_MASK = 1 | (1 << 3) | (1 << 4); // enable exceptions, IRQ3 & IRQ4
    IRQ_CTRL_PTR->STATUS |= IRQ_STAT_CIEN;

    if (AMBA_APB0_CFG_PTR->INFO_0 & AMBA_STT)
        testSysTick();
    else
        printf("No SysTick found!\n");

    printTestSummary();

    return 0;
}
