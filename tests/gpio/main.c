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
* $Date: 2020-06-18 08:20:40 +0200 (czw, 18 cze 2020) $
* $Revision: 602 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-csr.h>
#include <ccproc-amba.h>
#include <ccproc-amba-gpio.h>
#include <stdio.h>
#include "test.h"

#ifdef BOARD_CCNV1_C1
#define TEST_PIN 10
#else
#define TEST_PIN 6
#endif

static volatile uint32_t g_expectedIrq = 0;

void isr3(void)
{
    assertEq(AMBA_GPIO_PTR->IRQF, g_expectedIrq);
    AMBA_GPIO_PTR->IRQF = AMBA_GPIO_PTR->IRQF; // zero flags
    g_expectedIrq = 0;
}

static inline void setGpioPinPullCfg(unsigned pin, uint32_t pullCfg)
{
    if (pin < 16)
        AMBA_GPIO_PTR->PULL_LO = GPIO_CONFIG_MASK(pin,pullCfg);
    else
        AMBA_GPIO_PTR->PULL_HI = GPIO_CONFIG_MASK(pin,pullCfg);
}

static inline void setGpioPinSense(unsigned pin, uint32_t sense)
{
    if (pin < 16)
        AMBA_GPIO_PTR->SENSE_LO = GPIO_CONFIG_MASK(pin,sense);
    else
        AMBA_GPIO_PTR->SENSE_HI = GPIO_CONFIG_MASK(pin,sense);
}

static void testPin(unsigned pin)
{
    unsigned pinFlag = 1 << pin;
    volatile unsigned i = 0;

    // test DIR register
    AMBA_GPIO_PTR->DIR = 0;
    assertEq(AMBA_GPIO_PTR->DIR, 0);
    AMBA_GPIO_PTR->DIRSET = pinFlag;
    assertEq(AMBA_GPIO_PTR->DIR, pinFlag);
    AMBA_GPIO_PTR->DIRCLR = pinFlag;
    assertEq(AMBA_GPIO_PTR->DIR, 0);
    AMBA_GPIO_PTR->DIRTGL = pinFlag;
    assertEq(AMBA_GPIO_PTR->DIR, pinFlag);
    AMBA_GPIO_PTR->DIRTGL = pinFlag;
    assertEq(AMBA_GPIO_PTR->DIR, 0);

    // test OUTPUT register
    AMBA_GPIO_PTR->OUT = 0;
    assertEq(AMBA_GPIO_PTR->OUT, 0);
    AMBA_GPIO_PTR->OUTSET = pinFlag;
    assertEq(AMBA_GPIO_PTR->OUT, pinFlag);
    AMBA_GPIO_PTR->OUTCLR = pinFlag;
    assertEq(AMBA_GPIO_PTR->OUT, 0);
    AMBA_GPIO_PTR->OUTTGL = pinFlag;
    assertEq(AMBA_GPIO_PTR->OUT, pinFlag);
    AMBA_GPIO_PTR->OUTTGL = pinFlag;
    assertEq(AMBA_GPIO_PTR->OUT, 0);

    // test Pull Up
    AMBA_GPIO_PTR->DIR = 0;
    setGpioPinPullCfg(pin, GPIO_PULL_UP);
    for (i = 0; i < 100; ++i);
    assertEq(AMBA_GPIO_PTR->IN & pinFlag, pinFlag);

    // test Pull Down
    setGpioPinPullCfg(pin, GPIO_PULL_DOWN);
    for (i = 0; i < 100; ++i);
#if CCSDK_BOARD != ml605
    assertEq(AMBA_GPIO_PTR->IN & pinFlag, 0);
#endif

    // reset pull and out config
    setGpioPinPullCfg(pin, GPIO_PULL_NONE);

    // test output
    AMBA_GPIO_PTR->DIR = pinFlag;
    AMBA_GPIO_PTR->OUT = pinFlag;
    for (i = 0; i < 100; ++i);
    assertEq(AMBA_GPIO_PTR->IN & pinFlag, pinFlag);
    AMBA_GPIO_PTR->OUT = 0;
    for (i = 0; i < 100; ++i);
    assertEq(AMBA_GPIO_PTR->IN & pinFlag, 0);

    // interrupts
    AMBA_GPIO_PTR->IRQMAP = 1 << 3;
    CSR_CTRL_PTR->IRQ_MASK |= 1 << 3;
    AMBA_GPIO_PTR->DIR = 0; // input

    setGpioPinPullCfg(pin, GPIO_PULL_DOWN);
    for (i = 0; i < 100; ++i);
    setGpioPinSense(pin, GPIO_SENSE_RISING);
    AMBA_GPIO_PTR->INT0 = pinFlag;
    g_expectedIrq = 1;
    setGpioPinPullCfg(pin, GPIO_PULL_UP);
    for (i = 0; i < 100; ++i);
#if CCSDK_BOARD != ml605
    assertFalse(g_expectedIrq);
#endif

    setGpioPinSense(pin, GPIO_SENSE_FALLING);
    g_expectedIrq = 1;
    setGpioPinPullCfg(pin, GPIO_PULL_DOWN);
    for (i = 0; i < 100; ++i);
#if CCSDK_BOARD != ml605
    assertFalse(g_expectedIrq);
#endif
}

int main(void)
{
    printf("\nStarting GPIO test\n");

    if (TEST_PIN >= AMBA_GPIO_COUNT()) {
        printf("Cannot run test! Number of GPIO pins: %lu\n", AMBA_GPIO_COUNT());
        printTestSummary();
        return 0;
    }

    CSR_CTRL_PTR->IRQ_MASK = 1; // enable exceptions
    CSR_CTRL_PTR->STATUS |= CSR_STAT_CIEN;

    printf("Found %lu pins.\n", AMBA_GPIO_COUNT());

    AMBA_GPIO_PTR->CTRL = GPIO_CTRL_EN;
    assertEq(AMBA_GPIO_PTR->CTRL & GPIO_CTRL_EN, GPIO_CTRL_EN);
    assertEq(AMBA_GPIO_PTR->IRQMAP, 1 << AMBA_GPIO0_IRQn);

    testPin(TEST_PIN);

    printTestSummary();

    return 0;
}
