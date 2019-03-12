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
* Author    : Krzysztof Marcinek
* ******************************************************************************
* $Date: 2018-10-08 11:52:38 +0200 (pon) $
* $Revision: 320 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-pwd.h>
#include <ccproc-dcache.h>
#include <ccproc-amba.h>
#include <ccproc-amba-rtc.h>
#include <pwd_util.h>
#include <stdio.h>
#include "test.h"

#define RTC_FREQ    32768

#define BACK0       0x11223344
#define BACK1       0x55667788
#define BACK2       0x99AABBCC
#define BACK3       0xDDEEFF00

int test;

static void reset(void){
    printf("Reseting...\n");
    PWD_PTR->PWDRST = PWD_RST_KEY;
    for (;;);
}

static void TICKwait(void){
    static volatile int i;
    for (i=0;i<CORE_FREQ/RTC_FREQ;i++);
}

static void RTCwait(void){
    while((AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY) != 0);
}

static void testRTCpwd(void){

    printf("Entering deep power down...\n");

    RTCwait();
    AMBA_RTC_PTR->COMPARE = 1024;
    RTCwait();
    AMBA_RTC_PTR->COUNT = 0;
    RTCwait();
    AMBA_RTC_PTR->PRES = 0;
    RTCwait();
    AMBA_RTC_PTR->CTRL |= RTC_CTRL_WKUPCMP;
    RTCwait();

    PWD_PTR->CTRL |= (1<<PWD_CTRL_COREINT_SHIFT) | (3<<PWD_CTRL_PER2INT_SHIFT) | (2<<PWD_CTRL_PER0INT_SHIFT) | PWD_CTRL_KEY;

    // flush data cache
    DCACHE_PTR->FLUSH = 1;

    systemPowerDown();

    printf("Restored from deep power down.\n");
}

int main(void){

    if (PWD_PTR->RSTRSN != PWD_RSN_SOFT){

        printf("\nStarting RTC test\n");

        if ((AMBA_APB0_CFG_PTR->INFO_0 & AMBA_RTC) == 0){
            printf("No RTC found!\n");
            printTestSummary();
            return 0;
        }

        do{
            AMBA_RTC_PTR->CTRL |= RTC_CTRL_EN;
        } while (((AMBA_RTC_PTR->IRQF & RTC_TRERRIF) != 0) || ((AMBA_RTC_PTR->CTRL & RTC_CTRL_EN) == 0));

        RTCwait();
        AMBA_RTC_PTR->PRES = 0;

        assertEq(AMBA_RTC_PTR->COUNT, 0);

        RTCwait();
        AMBA_RTC_PTR->PER = 0xFFFFFFFF;

        RTCwait();
        AMBA_RTC_PTR->COMPARE = 0xFFFFFFFF;

        RTCwait();
        AMBA_RTC_PTR->BACKUP0 = BACK0;
        RTCwait();
        AMBA_RTC_PTR->BACKUP1 = BACK1;
        RTCwait();
        AMBA_RTC_PTR->BACKUP2 = BACK2;
        RTCwait();
        AMBA_RTC_PTR->BACKUP3 = BACK3;

        RTCwait();
        AMBA_RTC_PTR->COUNT = 0;

        assertEq(AMBA_RTC_PTR->COUNT, 0);

        test = 0;
        TICKwait();
        if (AMBA_RTC_PTR->COUNT > 0)
            test++;

        assertEq(test, 1);
        assertEq(AMBA_RTC_PTR->BACKUP0, BACK0);
        assertEq(AMBA_RTC_PTR->BACKUP1, BACK1);
        assertEq(AMBA_RTC_PTR->BACKUP2, BACK2);
        assertEq(AMBA_RTC_PTR->BACKUP3, BACK3);

        RTCwait();
        AMBA_RTC_PTR->BACKUP0 = AMBA_RTC_PTR->COUNT;
        RTCwait();
        AMBA_RTC_PTR->BACKUP1 = g_totalTests;
        RTCwait();
        AMBA_RTC_PTR->BACKUP2 = g_failedTests;

        reset();

    }
    else{

        printf("Continuing RTC test...\n");

        do{
            AMBA_RTC_PTR->CTRL |= RTC_CTRL_EN;
        } while (((AMBA_RTC_PTR->IRQF & RTC_TRERRIF) != 0) || ((AMBA_RTC_PTR->CTRL & RTC_CTRL_EN) == 0));

        RTCwait();
        g_totalTests = AMBA_RTC_PTR->BACKUP1;
        RTCwait();
        g_failedTests = AMBA_RTC_PTR->BACKUP2;

        test = 0;
        RTCwait();
        if (AMBA_RTC_PTR->COUNT > AMBA_RTC_PTR->BACKUP0)
            test++;

        assertEq(test, 1);
        assertEq(AMBA_RTC_PTR->BACKUP3, BACK3);

    }

    assertTrue(g_totalTests>8);

    testRTCpwd();

    printTestSummary();

    return 0;

}
