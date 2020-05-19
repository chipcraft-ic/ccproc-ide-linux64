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
* $Date: 2019-10-21 09:43:30 +0200 (pon, 21 paź 2019) $
* $Revision: 477 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-pwd.h>
#include <ccproc-amba.h>
#include <ccproc-amba-rtc.h>
#include <ccproc-amba-wdt.h>
#include <rtc_util.h>
#include <stdio.h>
#include <stdlib.h>
#include "test.h"

static volatile uint32_t* reset_count;
static volatile uint32_t reset_guard;

static void RTCrestore(void){
    g_totalTests = RTCread((uint32_t*)&AMBA_RTC_PTR->BACKUP1);
    g_failedTests = RTCread((uint32_t*)&AMBA_RTC_PTR->BACKUP2);
    reset_guard = RTCread((uint32_t*)&AMBA_RTC_PTR->BACKUP3);
}

static void RTCbackup(void){
    RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP1,g_totalTests);
    RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP2,g_failedTests);
    RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP3,reset_guard);
}

static void RTCstart(void){
    RTCenable();
    RTCwrite((uint32_t*)&AMBA_RTC_PTR->PER,0xFFFFFFFF);
    RTCwrite((uint32_t*)&AMBA_RTC_PTR->COMPARE,0xFFFFFFFF);
}

static void testWDT(void)
{
    reset_guard++;
    RTCbackup();
    do {
        AMBA_WDT_PTR->LOCK = 3;
        AMBA_WDT_PTR->CTRL = 1;
    } while ((AMBA_WDT_PTR->CTRL & WDT_CTRL_EN) == 0);
    do {
        AMBA_WDT_PTR->LOCK = 3;
        AMBA_WDT_PTR->PER = 50;
    } while (AMBA_WDT_PTR->PER != 50);
    for (;;);
}

static void testRST(void){
    reset_guard++;
    RTCbackup();
    PWD_PTR->PWDRST = PWD_RST_KEY;
    for (;;);
}

int main(void)
{

    reset_count = malloc(sizeof *reset_count * (1));

    if ((AMBA_APB0_CFG_PTR->INFO_0 & AMBA_WDT) == 0){
        printf("\nStarting system reset tests\n");
        printf("No WDT found!\n");
        printTestSummary();
        return 0;
    }
    else{
        if ((AMBA_APB0_CFG_PTR->INFO_0 & AMBA_RTC) == 0){
            printf("\nStarting system reset tests\n");
            printf("No RTC found!\n");
            printTestSummary();
            return 0;
        }
    }

    PWD_PTR->CTRL |= (1<<PWD_CTRL_COREINT_SHIFT) | (3<<PWD_CTRL_PER2INT_SHIFT) | (2<<PWD_CTRL_PER0INT_SHIFT) | PWD_CTRL_KEY;

    RTCstart();
    RTCrestore();

    if (reset_guard == 0){
        printf("\nStarting system reset tests\n");
        if ((PWD_PTR->RSTRSN == PWD_RSN_PWRON) || (PWD_PTR->RSTRSN == PWD_RSN_DBG)){
            *reset_count = 1;
        }
        else{
            *reset_count = 0;
        }
        assertEq(*reset_count, 1);                          // power on reset or debug reset
        testWDT();
    }
    else if (reset_guard == 1){
        printf("Continuing after WDT reset...\n");
        assertEq(PWD_PTR->RSTRSN, PWD_RSN_WDT);             // WDT reset
        *reset_count += 1;
        assertEq(*reset_count, 2);
        testRST();
    }
    else if (reset_guard == 2){
        printf("Continuing after software reset...\n");
        assertEq(PWD_PTR->RSTRSN, PWD_RSN_SOFT);            // software reset
        *reset_count += 1;
        assertEq(*reset_count, 3);
    }

    assertTrue(g_totalTests>4);

    printTestSummary();

    return 0;
}
