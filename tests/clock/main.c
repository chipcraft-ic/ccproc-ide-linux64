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
* File Name : main.c
* Author    : Krzysztof Marcinek
* ******************************************************************************
* $Date: 2018-10-25 10:58:01 +0200 (czw) $
* $Revision: 324 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-utils.h>
#include <ccproc-irq.h>
#include <ccproc-jtag.h>
#include <ccproc-perfcnt.h>
#include <ccproc-amba.h>
#include <ccproc-amba-rtc.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <test.h>

#ifdef MCU_CCNV1
    #include <ccproc-amba-cfgregs.h>
    #define _BOARD_SUPPORTED_ 1
#endif

#ifdef _BOARD_SUPPORTED_

#define XTAL_FREQ 16000000
#define RTC_FREQ  32768
#define FREQ_DEV  10

#define N_CASE 10
#define M_CASE 1

#define BIT(n) (1 << (n))

uint32_t expectIrq1 = 0;
uint32_t enteredIrqs = 0;
uint32_t sumIrqs = 0;

void isr1(void){
    assertTrue(expectIrq1);
    expectIrq1 = 0;
    enteredIrqs++;
    CFG_REGS_PTR->CFGREG_UNLOCK = 0xA55A;
    CFG_REGS_PTR->CFGREG_COREFREQ_PLL &= ~(1 << CFGREG_COREFREQ_PLL_PLL_TEST_SHIFT);
}

void startRTC(void){
    do{
        AMBA_RTC_PTR->CTRL |= RTC_CTRL_EN;
    } while (((AMBA_RTC_PTR->IRQF & RTC_TRERRIF) != 0) || ((AMBA_RTC_PTR->CTRL & RTC_CTRL_EN) == 0));
    while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
    AMBA_RTC_PTR->PRES = 0;
    while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
    AMBA_RTC_PTR->PER = 0xFFFFFFFF;
    while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
    AMBA_RTC_PTR->COMPARE = 0xFFFFFFFF;
    while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
}

void startPERF(void){
    PERFCNT_PTR->STATUS |= PERFCNT_STAT_EN;
}

void testPLL(void){

    uint32_t start_rtc, stop_rtc;
    uint32_t start_perf, stop_perf;
    uint32_t rtc_time, pll_time, pll_freq;
    uint32_t i, val;
    uint32_t ref_sel;
    volatile uint32_t j;

    /* Configure PLL */
    CFG_REGS_PTR->CFGREG_UNLOCK = 0xA55A;
    CFG_REGS_PTR->CFGREG_COREFREQ_PLL = CFGREG_COREFREQ_PLL_PLL_EN_MASK | (5 << CFGREG_COREFREQ_PLL_PLL_N_SHIFT);
    while ((CFG_REGS_PTR->CFGREG_COREFREQ_STAT & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK) == 0);

    /* Switch to PLL */
    CFG_REGS_PTR->CFGREG_UNLOCK = 0xA55A;
    CFG_REGS_PTR->CFGREG_COREFREQ_CLK = 2 << CFGREG_COREFREQ_CLK_CLK_CORE_SEL_SHIFT;

    for (ref_sel=0; ref_sel<2;ref_sel++){

        // Test allowed N values
        //printf("Testing ref_sel = %d\n",(int)ref_sel);
        for (i=5;i>=4;i--){

            //printf("Testing N = %d\n",(int)i);
            val = CFG_REGS_PTR->CFGREG_COREFREQ_PLL;
            val &= ~CFGREG_COREFREQ_PLL_PLL_N_MASK;
            val &= ~CFGREG_COREFREQ_PLL_PLL_M_MASK;
            val |= (i << CFGREG_COREFREQ_PLL_PLL_N_SHIFT) | (ref_sel << CFGREG_COREFREQ_PLL_REF_SEL_SHIFT);
            CFG_REGS_PTR->CFGREG_UNLOCK = 0xA55A;
            CFG_REGS_PTR->CFGREG_COREFREQ_PLL = val;
            while ((CFG_REGS_PTR->CFGREG_COREFREQ_STAT & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK) == 0);

            start_perf = PERFCNT_PTR->CYCLE_LO;
            while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
            start_rtc = AMBA_RTC_PTR->COUNT;

            for (j=0;j<20000;j++);

            stop_perf = PERFCNT_PTR->CYCLE_LO;
            while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
            stop_rtc = AMBA_RTC_PTR->COUNT;

            rtc_time = (stop_rtc-start_rtc) * (1000000000/RTC_FREQ);
            pll_freq = XTAL_FREQ * i;
            pll_time = (stop_perf-start_perf) * (1000000000/pll_freq);

            //printf("pll_time = %d, rtc_time = %d\n",(int)pll_time,(int)rtc_time);
            ok(pll_time > (rtc_time - rtc_time/FREQ_DEV) && pll_time < (rtc_time + rtc_time/FREQ_DEV), "Expected system frequency %uHz", (unsigned int)pll_freq);

        }

        // Test one M case
        val = CFG_REGS_PTR->CFGREG_COREFREQ_PLL;
        val &= ~CFGREG_COREFREQ_PLL_PLL_N_MASK;
        val &= ~CFGREG_COREFREQ_PLL_PLL_M_MASK;
        val |= (N_CASE << CFGREG_COREFREQ_PLL_PLL_N_SHIFT) | (M_CASE << CFGREG_COREFREQ_PLL_PLL_M_SHIFT);
        CFG_REGS_PTR->CFGREG_UNLOCK = 0xA55A;
        CFG_REGS_PTR->CFGREG_COREFREQ_PLL = val;
        while ((CFG_REGS_PTR->CFGREG_COREFREQ_STAT & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK) == 0);

        start_perf = PERFCNT_PTR->CYCLE_LO;
        while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
        start_rtc = AMBA_RTC_PTR->COUNT;

        for (j=0;j<20000;j++);

        stop_perf = PERFCNT_PTR->CYCLE_LO;
        while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
        stop_rtc = AMBA_RTC_PTR->COUNT;

        rtc_time = (stop_rtc-start_rtc) * (1000000000/RTC_FREQ);
        pll_freq = (XTAL_FREQ * N_CASE)/(M_CASE+1);
        pll_time = (stop_perf-start_perf) * (1000000000/pll_freq);

        //printf("pll_time = %d, rtc_time = %d\n",(int)pll_time,(int)rtc_time);
        ok(pll_time > (rtc_time - rtc_time/FREQ_DEV) && pll_time < (rtc_time + rtc_time/FREQ_DEV), "Expected system frequency %uHz", (unsigned int)pll_freq);

    }

    // Test interrupt on PLL fail
    IRQ_CTRL_PTR->IRQ_MASK = BIT(1);
    IRQ_CTRL_PTR->STATUS |= IRQ_STAT_CIEN;
    expectIrq1 = 1;
    sumIrqs++;
    CFG_REGS_PTR->CFGREG_UNLOCK = 0xA55A;
    CFG_REGS_PTR->CFGREG_IRQMAP = BIT(1);
    CFG_REGS_PTR->CFGREG_UNLOCK = 0xA55A;
    CFG_REGS_PTR->CFGREG_COREFREQ_PLL |= 1 << CFGREG_COREFREQ_PLL_PLL_TEST_SHIFT;

    // wait for a while
    for (j=0;j<20000;j++);

    assertEq(enteredIrqs,sumIrqs);

}

#endif

int main(void)
{

#ifndef _BOARD_SUPPORTED_
    printf("\nUnsupported mcu IDCODE = 0x%08x!\n",(unsigned int)IDCODE_GET);
#else

    if (IDCODE_MATCH_MANUF_ID && IDCODE_MATCH_PART_NUM(IDCODE_PART_NUM)){
        printf("\nStarting %s board clock system tests\n",STR(BOARD));
        startRTC();
        startPERF();
        testPLL();
    }

#endif

    printTestSummary();

    return 0;
}
