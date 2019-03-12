/*H*****************************************************************************
*
* Copyright (c) 2019 ChipCraft Sp. z o.o. All rights reserved
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
* $Date: 2019-02-15 14:56:41 +0100 (pią) $
* $Revision: 383 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-irq.h>
#include <ccproc-pwd.h>
#include <ccproc-mcore.h>
#include <ccproc-mbist.h>
#include <stdio.h>
#include "test.h"

int main(void)
{

    uint32_t status, mask, core_num, i;
    uint32_t *ptr, *reg;

    core_num = MCORE_PTR->CORE_NUM;

    if ((IRQ_CTRL_PTR->CPU_INFO_1 & CPU_MBIST) == 0){
        printf("No MBIST found!\n");
        printTestSummary();
        return 0;
    }
    if ((IRQ_CTRL_PTR->CPU_INFO_0 & CPU_PWD) == 0){
        printf("Power management controller required to test MBIST!\n");
        printTestSummary();
        return 0;
    }

    if (PWD_PTR->RSTRSN == PWD_RSN_MBIST){

        g_failedTests = MBIST_PTR->SCRATCH0;
        g_totalTests = MBIST_PTR->SCRATCH1;

        if (MBIST_PTR->EXT_LOGS == 0){
            assertTrue(1);
            printf("No external MBIST detected.\n");
        }
        else if (MBIST_PTR->EXT_LOGS == 3){
            assertTrue(1);
            printf("External MBIST ok.\n");
        }
        else {
            assertTrue(0);
            printf("External MBIST failed.\n");
        }

        ptr = (uint32_t*)&(MBIST_PTR->INT_LOGS);
        for (i=0;i<core_num;i++){
            reg = ptr + i;
            status = *(reg);
            reg = ptr + i + core_num;
            mask = *(reg);
            assertTrue(mask!=0);
            if (mask == status){
                assertTrue(1);
                printf("Internal Core %d MBIST ok.\n",(unsigned int)i);
            }
            else{
                assertTrue(0);
                printf("Internal Core %d MBIST failed.\n",(unsigned int)i);
            }
        }

        MBIST_PTR->SCRATCH0 = g_failedTests;
        MBIST_PTR->SCRATCH1 = g_totalTests;

        if ((MBIST_PTR->CTRL&MBIST_CTRL_ALG_MASK)>>MBIST_CTRL_ALG_SHIFT == MBIST_ALG_ZERO_ONE){
            printf("Algorithm: MATS+.\n");
            MBIST_PTR->CTRL = MBIST_ALG_MATS_P << MBIST_CTRL_ALG_SHIFT;
            MBIST_PTR->RUN = MBIST_RUN_KEY;
            for(;;);
        }
        else if ((MBIST_PTR->CTRL&MBIST_CTRL_ALG_MASK)>>MBIST_CTRL_ALG_SHIFT == MBIST_ALG_MATS_P){
            printf("Algorithm: March C-.\n");
            MBIST_PTR->CTRL = MBIST_ALG_MARCH_CM << MBIST_CTRL_ALG_SHIFT;
            MBIST_PTR->RUN = MBIST_RUN_KEY;
            for(;;);
        }
        else if ((MBIST_PTR->CTRL&MBIST_CTRL_ALG_MASK)>>MBIST_CTRL_ALG_SHIFT == MBIST_ALG_MARCH_CM){
            printTestSummary();
            return 0;
        }

    }

    printf("\nStarting MBIST test.\n");
    printf("Algorithm: Zero-one.\n");
    MBIST_PTR->CTRL = MBIST_ALG_ZERO_ONE << MBIST_CTRL_ALG_SHIFT;
    MBIST_PTR->RUN = MBIST_RUN_KEY;
    for(;;);

}
