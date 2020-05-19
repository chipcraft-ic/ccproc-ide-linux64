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
* $Date: 2019-12-19 12:13:42 +0100 (czw, 19 gru 2019) $
* $Revision: 491 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-csr.h>
#include <ccproc-pwd.h>
#include <ccproc-amba.h>
#include <ccproc-amba-rtc.h>
#include <rtc_util.h>
#include <stdio.h>

#include "test.h"

extern volatile uint32_t _flag;

#ifdef MEM_SIM_TEST
    #define VERBOSE 0
#else
    #define VERBOSE 1
#endif

void test_nonword_store_access(uint32_t start, uint32_t end, uint32_t size, uint32_t halfw){
    volatile uint32_t *ptr;
    volatile uint32_t data;
    uint32_t i;

    ptr = (uint32_t *)start;

    while (((uint32_t)ptr < end) && (((uint32_t)ptr > 0) || ((uint32_t)ptr == start))){
        if (VERBOSE) printf("0x%08x ",(unsigned int)ptr);
        for (i=0;i<size;i++){
            _flag = 0;

            if (halfw == 1){
                __asm__ __volatile__ (
                    ".set noreorder\n\t"
                    "sh %0, 0(%1)\n\t"
                    ".set reorder\n\t"
                    : "=r" (data)
                    : "r" (ptr));
            }
            else{
                __asm__ __volatile__ (
                    ".set noreorder\n\t"
                    "sb %0, 0(%1)\n\t"
                    ".set reorder"
                    : "=r" (data)
                    : "r" (ptr));
            }

            if (VERBOSE) putchar('-'); // exception
            ptr++;
            assertEq(_flag,1);
        }
        if (VERBOSE) putchar('\n');
    }
    //if (VERBOSE) putchar('\n');

}

void test_nonword_load_access(uint32_t start, uint32_t end, uint32_t size, uint32_t halfw){
    volatile uint32_t *ptr;
    volatile uint32_t data;
    uint32_t i;

    ptr = (uint32_t *)start;

    while (((uint32_t)ptr < end) && (((uint32_t)ptr > 0) || ((uint32_t)ptr == start))){
        if (VERBOSE) printf("0x%08x ",(unsigned int)ptr);
        for (i=0;i<size;i++){
            _flag = 0;

            if (halfw == 1){
                __asm__ __volatile__ (
                    ".set noreorder\n\t"
                    "lh %0, 0(%1)\n\t"
                    ".set reorder"
                    : "=r" (data)
                    : "r" (ptr));
            }
            else{
                __asm__ __volatile__ (
                    ".set noreorder\n\t"
                    "lb %0, 0(%1)\n\t"
                    ".set reorder"
                    : "=r" (data)
                    : "r" (ptr));
            }

            if (VERBOSE) putchar('-'); // exception
            ptr++;
            assertEq(_flag,1);
        }
        if (VERBOSE) putchar('\n');
    }
    //if (VERBOSE) putchar('\n');

}

void test_mem_access(uint32_t start, uint32_t end, uint32_t size){
    volatile uint32_t *ptr;
    volatile uint32_t data;
    uint32_t i;

    ptr = (uint32_t *)start;

    while (((uint32_t)ptr < end) && (((uint32_t)ptr > 0) || ((uint32_t)ptr == start))){
        if (VERBOSE) printf("0x%08x ",(unsigned int)ptr);
        for (i=0;i<size;i++){
            _flag = 0;

            __asm__ __volatile__ (
                ".set noreorder\n\t"
                "lw %0, 0(%1)\n\t"
                ".set reorder"
                : "=r" (data)
                : "r" (ptr));

            if (VERBOSE){
                if (_flag == 0){
                    if (data != 0){
                        data = data ^ (data>>8) ^ (data>>16) ^ (data>>24);
                        data &= 0x7F;
                        if (data < 33)
                            data += 33;
                        if (data == '-')
                            data--;
                        if (data == '?')
                            data--;
                        if (data == '.')
                            data++;
                        if (data > 126)
                            data = '?';
                        putchar(data);
                    }
                    else
                        putchar('.');
                }
                else{
                    putchar('-'); // exception
                }
            }
            ptr++;
            if (start > 0x83000000){
                assertEq(_flag,1);
            }
            /*if (start < 0x80000000){
                assertEq(_flag,0);
            }*/
        }
        if (VERBOSE) putchar('\n');
    }
    //if (VERBOSE) putchar('\n');

}

int check_reset_cause(void){
    if (PWD_PTR->RSTRSN == PWD_RSN_SOFT) {
        RTCenable();
        g_totalTests = RTCread((uint32_t*)&AMBA_RTC_PTR->BACKUP0);
        g_failedTests = RTCread((uint32_t*)&AMBA_RTC_PTR->BACKUP1);
        printTestSummary();
        return 1;
    }
    return 0;
}

void test_ram_space(void){

    uint32_t *addr;
    uint32_t totalTests = 0;
    uint32_t failedTests = 0;
    uint32_t ram_end = RAM_BASE + CPU_INFO_GET_DMSIZE(CSR_CTRL_PTR->CPU_INFO_0);

    if ((AMBA_APB0_CFG_PTR->INFO_0 & AMBA_RTC) == 0){
        printf("\nNo RTC found to test RAM space!\n\n");
        return;
    }
    if (CPU_INFO_GET_DMSIZE(CSR_CTRL_PTR->CPU_INFO_0) > 0x80000){
        printf("\nToo large RAM size to test!\n\n");
        return;
    }

    RTCenable();

    printf("\nTesting RAM space.\n\n");

    totalTests = g_totalTests;
    failedTests = g_failedTests;

    for (addr=(uint32_t*)RAM_BASE; (int)addr < ram_end; addr++){
        *addr=(int)addr;
    }
    for (addr=(uint32_t*)RAM_BASE; (int)addr < ram_end; addr++){
        totalTests++;
        if (*addr != (int)addr) {
            failedTests++;
        }
    }

    RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP0,totalTests);
    RTCwrite((uint32_t*)&AMBA_RTC_PTR->BACKUP1,failedTests);

    PWD_PTR->PWDRST = PWD_RST_KEY;
    for (;;);

}

int main(void)
{

    if (check_reset_cause()) return 0;

    printf("Creating memory access map.\n\n");

    #ifdef MEM_SIM_TEST
        printf("MEM_SIM_TEST: defined.\n\n");
    #else
        printf("MEM_SIM_TEST: undefined.\n\n");
    #endif

    CSR_CTRL_PTR->IRQ_MASK = 1;
    CSR_CTRL_PTR->STATUS |= CSR_STAT_CIEN;

    #ifdef MEM_SIM_TEST
        PWD_PTR->CTRL |= (1<<PWD_CTRL_PER2INT_SHIFT) | (2<<PWD_CTRL_PER0INT_SHIFT) | PWD_CTRL_KEY;
    #endif

    test_mem_access(0x00000000,0x00000504,64);
    //test_mem_access(0x0FFFFF00,0x10000000,64); <- do not read HYPERBUS address space
    //test_mem_access(0x10000000,0x10000504,64); <- do not read HYPERBUS address space

    //test_mem_access(0x1FFFFF00,0x20000504,64); <- do not read HYPERBUS address space
    test_mem_access(0x2FFFFF00,0x30000504,64);

    test_mem_access(0x3000FE00,0x30010200,64);
    test_mem_access(0x3001FE00,0x30020200,64);
    test_mem_access(0x3002FE00,0x30030200,64);
    test_mem_access(0x30031E00,0x30032200,64);
    test_mem_access(0x3003FE00,0x30040200,64);
    test_mem_access(0x3004FE00,0x30050200,64);
    test_mem_access(0x3005FE00,0x30060200,64);
    test_mem_access(0x3006FE00,0x30070200,64);
    //test_mem_access(0x30071E00,0x30072200,64); <- do not read 0x30072000 address in lockstep
    test_mem_access(0x3007FE00,0x30080200,64);
    test_mem_access(0x30087E00,0x30088A00,64);

    test_mem_access(0x3FFFFF00,0x40000504,64);
    test_mem_access(0x4007FF00,0x40080204,64);
    //test_mem_access(0x4FFFFF00,0x50000504,64); <- do not read HYPERBUS address space
    //test_mem_access(0x5FFFFF00,0x60000504,64); <- do not read HYPERBUS address space
    test_mem_access(0x6FFFFF00,0x70000504,64);
    test_mem_access(0x7FFFFF00,0x80000000,64);

    if (AMBA_APB0_CFG_PTR->INFO_0 != 0){

        test_mem_access(0x80000000,0x80010004,64);

        test_mem_access(0x80FFFF00,0x81000104,64);

        test_mem_access(0x81FFFF00,0x82000104,64);

        test_mem_access(0x82000000,0x82000204,64);
        test_mem_access(0x82000F00,0x82003000,64);
        test_mem_access(0x82FFFF00,0x83000104,64);

        test_mem_access(0x8FFFFF00,0x90000104,64);

    }

    test_mem_access(0x9FFFFF00,0xA0000104,64);
    test_mem_access(0xAFFFFF00,0xB0000104,64);
    test_mem_access(0xBFFFFF00,0xC0000104,64);
    test_mem_access(0xCFFFFF00,0xD0000104,64);
    test_mem_access(0xDFFFFF00,0xE0000104,64);
    test_mem_access(0xEFFFFF00,0xF0000104,64);
    test_mem_access(0xFFFFFF00,0xFFFFFFFC,64);

    printf("\nTesting non-word load access.\n\n");

    test_nonword_load_access(0x3000FE00,0x30010200,64,0);
    test_nonword_load_access(0x3000FE00,0x30010200,64,1);
    test_nonword_load_access(0x80000000,0x80000204,64,0);
    test_nonword_load_access(0x80000000,0x80000204,64,1);
    test_nonword_load_access(0x82000000,0x80000204,64,0);
    test_nonword_load_access(0x82000000,0x80000204,64,1);

    printf("\nTesting non-word store access.\n\n");

    test_nonword_store_access(0x3000FE00,0x30010200,64,0);
    test_nonword_store_access(0x3000FE00,0x30010200,64,1);
    test_nonword_store_access(0x80000000,0x80000204,64,0);
    test_nonword_store_access(0x80000000,0x80000204,64,1);
    test_nonword_store_access(0x82000000,0x80000204,64,0);
    test_nonword_store_access(0x82000000,0x80000204,64,1);

    test_ram_space();

    printf("\nDone.\n");

    printTestSummary();

    return 0;

}
