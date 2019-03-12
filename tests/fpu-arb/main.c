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
* $Date: 2019-02-26 16:15:44 +0100 (wto) $
* $Revision: 386 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-irq.h>
#include <ccproc-mcore.h>
#include <core_util.h>
#include <stdio.h>
#include "test.h"

#define FPU_ITER  10000
#define FPU_BASE  0.013
#define FPU_SCALE 0.018

int fpu_ref[]       = {996154275,996596915,996656911,996675703,996683825,996688021,996690439,996691872,996692835,996693490,996693873,996694120,996694258,996694361,996694361,996694176};
int fpu_res[16];

static void testFpuArb(){
    float fpu_base;
    uint32_t i, res;

    fpu_base = FPU_BASE + (FPU_SCALE * IRQ_STATUS_GET_CORE_ID(IRQ_CTRL_PTR->STATUS));
    __asm__ __volatile__ ("mtc1 %0, $f0"
        : /* output */
        : "r" (fpu_base) /* input */
    );
    for (i=0;i<FPU_ITER;i++){
        __asm__ __volatile__ ("    \
            add.s $f1, $f0, $f0;   \
            mul.s $f2, $f1, $f0;   \
            sub.s $f0, $f2, $f0;   \
        ");
    }
    __asm__ __volatile__ ("mfc1 %0, $f0"
        : "=r" (res) /* output */
    );

    fpu_res[IRQ_STATUS_GET_CORE_ID(IRQ_CTRL_PTR->STATUS)] = res;

}

int main(void)
{

    uint32_t i;

    if (CPU_INFO_GET_FPU(IRQ_CTRL_PTR->CPU_INFO_1) == 0){
        printf("No FPU found!\n");
        printTestSummary();
        return 0;
    }
    if (MCORE_PTR->CORE_NUM > 16){
        printf("Unsupported number of cores!\n");
        printTestSummary();
        return 0;
    }

    printf("\nStarting FPU arbiter test.\n");

    // check if in lockstep mode
    if (MCORE_PTR->STATUS == 3){
        testFpuArb();
        printTestSummary();
        return 0;
    }

    for (i = 1; i < MCORE_PTR->CORE_NUM; ++i){
        coreStart(i, &testFpuArb, NULL);
    }
    if (MCORE_PTR->CORE_NUM > 1){
        while (MCORE_PTR->STATUS == 1);
    }
    testFpuArb();

    while (MCORE_PTR->STATUS != 1);
    for (i = 0; i < MCORE_PTR->CORE_NUM; ++i){
        assertEq(fpu_res[i],fpu_ref[i]);
    }

    printTestSummary();
    return 0;

}
