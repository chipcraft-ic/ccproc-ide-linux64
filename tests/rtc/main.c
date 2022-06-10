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
* $Date: 2021-10-30 22:10:12 +0200 (sob, 30 paź 2021) $
* $Revision: 781 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-pwd.h>
#include <ccproc-dcache.h>
#include <ccproc-amba.h>
#include <ccproc-amba-rtc.h>
#include <pwd_util.h>
#include <rtc_util.h>
#include <stdio.h>
#include "test.h"

#define RTC_FREQ    32768
#define RAM_MEM_MAX 1024

#define BACK0       0x11223344
#define BACK1       0x55667788
#define BACK2       0x99AABBCC
#define BACK3       0xDDEEFF00

static void reset(void){
    printf("Reseting...\n");
    PWD_PTR->PWDRST = PWD_RST_KEY;
    for (;;);
}

static void TICKwait(void){
    static volatile int i;
    for (i=0;i<CORE_FREQ/RTC_FREQ;i++);
}

static void testRTCpwd(void){

    printf("Entering deep power down...\n");

    RTCwrite((uint32_t*)&AMBA_RTC_PTR->COMPARE, 1024);
    RTCwrite((uint32_t*)&AMBA_RTC_PTR->COUNT, 0);
    RTCwrite((uint32_t*)&AMBA_RTC_PTR->PRES, 0);
    RTCwrite((uint32_t*)&AMBA_RTC_PTR->CTRL, RTCread((uint32_t*)&AMBA_RTC_PTR->CTRL) | RTC_CTRL_WKUPCMP);

    // flush data cache
    DCACHE_PTR->FLUSH = 1;

    systemPowerDown();

    printf("Restored from deep power down.\n");
}

void RTCRAMtest(void){
    uint32_t ram_size = 1<<(RTC_GET_RAM_SIZE(RTCread((uint32_t*)&AMBA_RTC_PTR->STATUS))-2);
    if (ram_size > 0)
        ram_size = 1<<(ram_size-2);
    if (ram_size > RAM_MEM_MAX)
        ram_size = RAM_MEM_MAX;
    if (ram_size>0){
        printf("Testing RTC backup RAM...\n");
        for (int i=0;i<ram_size;i+=50)
        {
            RTCwrite((uint32_t*)&AMBA_BKPRAM_PTR[i],i);
        }
        for (int i=0;i<ram_size;i+=50)
        {
            assertEq(RTCread((uint32_t*)&AMBA_BKPRAM_PTR[i]),i);
        }
    }
}

int main(void){

    int count;

    if (PWD_PTR->RSTRSN != PWD_RSN_SOFT){

        printf("\nStarting RTC test\n");

        if ((AMBA_APB0_CFG_PTR->INFO_0 & AMBA_RTC) == 0){
            printf("No RTC found!\n");
            printTestSummary();
            return 0;
        }

        if (AMBA_RTC_PTR->CTRL & RTC_CTRL_EN){
            printf("RTC already running with COUNT = %d\n",(int)AMBA_RTC_PTR->COUNT);
            if (AMBA_RTC_PTR->PRES == 32768){
                printTestSummary();
                return 0;
            }
        }

        RTCenable();

        RTCRAMtest();

        RTCwrite((uint32_t*)&AMBA_RTC_PTR->PRES, 0);

        RTCwrite((uint32_t*)&AMBA_RTC_PTR->PER, 0xFFFFFFFF);
        RTCwrite((uint32_t*)&AMBA_RTC_PTR->COMPARE, 0xFFFFFFFF);
        RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP0, BACK0);
        RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP1, BACK1);
        RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP2, BACK2);
        RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP3, BACK3);
        RTCwrite((uint32_t*)&AMBA_RTC_PTR->COUNT, 0);

        count = AMBA_RTC_PTR->COUNT;
        TICKwait();
        assertTrue(AMBA_RTC_PTR->COUNT > count);

        assertEq(AMBA_RTC_PTR->BACKUP0, BACK0);
        assertEq(AMBA_RTC_PTR->BACKUP1, BACK1);
        assertEq(AMBA_RTC_PTR->BACKUP2, BACK2);
        assertEq(AMBA_RTC_PTR->BACKUP3, BACK3);

        RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP0, AMBA_RTC_PTR->COUNT);
        RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP1, g_totalTests);
        RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP2, g_failedTests);

        reset();

    }
    else{

        printf("Continuing RTC test...\n");

        RTCenable();

        g_totalTests = RTCread((uint32_t*)&AMBA_RTC_PTR->BACKUP1);
        g_failedTests = RTCread((uint32_t*)&AMBA_RTC_PTR->BACKUP2);

        assertTrue(RTCread((uint32_t*)&AMBA_RTC_PTR->COUNT) > AMBA_RTC_PTR->BACKUP0);
        assertEq(AMBA_RTC_PTR->BACKUP3, BACK3);

    }

    assertTrue(g_totalTests>6);

    testRTCpwd();

    printTestSummary();

    RTCwrite((uint32_t*)&AMBA_RTC_PTR->PRES, 32768);
    RTCwrite((uint32_t*)&AMBA_RTC_PTR->COUNT, 0);

    return 0;

}
