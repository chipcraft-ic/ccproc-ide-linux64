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
* $Date: 2020-06-18 08:20:40 +0200 (czw, 18 cze 2020) $
* $Revision: 602 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-amba.h>
#include <ccproc-amba-gpio.h>
#include <ccproc-amba-i2c_mst.h>
#include <stdio.h>
#include "test.h"

#define I2C_FREQ 100000

#define TEST_I2C0_ONLY

#ifdef BOARD_CCNV1_C1
void setup_ccnv1_c1(void){
    AMBA_GPIO_PTR->ALTER_LO &= ~GPIO_CONFIG_MASK(4,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO &= ~GPIO_CONFIG_MASK(5,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(4,GPIO_ALTER_1);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(5,GPIO_ALTER_1);
    AMBA_GPIO_PTR->PULL_LO |= GPIO_CONFIG_MASK(4,GPIO_PULL_UP);
    AMBA_GPIO_PTR->PULL_LO |= GPIO_CONFIG_MASK(5,GPIO_PULL_UP);
}
#endif

void testI2C(int index){

    static volatile uint32_t delay;

    uint32_t status;
    uint32_t aack[128];
    uint32_t i, j, addr;

    for(i=0;i<128;i++){
        aack[i] = 0xff;
    }

    printf("\nTesting I2C %d...\n",index);

    AMBA_I2C_MST_PTR(index)->FILTER = 5;

    for(i=3;i<120;i++){

        AMBA_I2C_MST_PTR(index)->CTRL = I2C_MST_CTRL_EN | I2C_MST_CTRL_AUTO_CNT | I2C_MST_CTRL_AUTO_STOP | I2C_MST_CTRL_AUTO_ACK;
        AMBA_I2C_MST_PTR(index)->PRES = I2C_MST_BUILD_PRES(I2C_FREQ,PERIPH0_FREQ) / 10;
        AMBA_I2C_MST_PTR(index)->CWGR = I2C_MST_BUILD_CWGR(5, 9, 1, 4);

        assertEq(I2C_MST_STAT_GET_BS(AMBA_I2C_MST_PTR(index)->STATUS),I2C_MST_STAT_BS_UNK);
        AMBA_I2C_MST_PTR(index)->STATUS = I2C_MST_STAT_BS_IDLE;
        assertEq(I2C_MST_STAT_GET_BS(AMBA_I2C_MST_PTR(index)->STATUS),I2C_MST_STAT_BS_IDLE);
        AMBA_I2C_MST_PTR(index)->CMD = I2C_MST_CMD_LAST_ACK_BIT;

        aack[i] = 0;
        AMBA_I2C_MST_PTR(index)->COUNT = 1;

        AMBA_I2C_MST_PTR(index)->ADDR = i*2+1;

        do{
            status = AMBA_I2C_MST_PTR(index)->STATUS;
            if (status & I2C_MST_STAT_AACK){
                aack[i]++;
            }
            if (status & I2C_MST_STAT_ANACK){
                AMBA_I2C_MST_PTR(index)->CMD = I2C_MST_CMD_STOP;
                while (I2C_MST_STAT_GET_BS(AMBA_I2C_MST_PTR(index)->STATUS) != I2C_MST_STAT_BS_IDLE);
                break;
            }
        }
        while ((status & I2C_MST_STAT_RDRF) == 0);

        status = AMBA_I2C_MST_PTR(index)-> RDR;

        if (aack[i]){
            while ((AMBA_I2C_MST_PTR(index)->STATUS & I2C_MST_STAT_TXC) == 0);
        }

        AMBA_I2C_MST_PTR(index)->CMD = I2C_MST_CMD_RESET;
        for(delay=0;delay<I2C_MST_BUILD_PRES(I2C_FREQ,PERIPH0_FREQ)/5;delay++);
        assertEq(I2C_MST_STAT_GET_BS(AMBA_I2C_MST_PTR(index)->STATUS),I2C_MST_STAT_BS_UNK);

        for(delay=0;delay<I2C_MST_BUILD_PRES(I2C_FREQ,PERIPH0_FREQ)/5;delay++);

    }

    addr = 0;
    printf("\nI2C %d address table\n",index);
    printf("\n     0  1  2  3  4  5  6  7  8  9  a  b  c  d  e  f\n");
    for (i=0;i<8;i++){
        printf("%d0:",(unsigned)i);
        for (j=0;j<16;j++){
            if(aack[addr] == 0xff){
                printf("   ");
            }
            else if(aack[addr] == 0x00){
                printf(" --");
            }
            else if(aack[addr] == 0x01){
                printf(" %x%x",(unsigned)i,(unsigned)j);
            }
            addr++;
        }
        printf("\n");
    }
    printf("\n");

}

int main(void)
{

#ifndef TEST_I2C0_ONLY
    int i = 0;
#endif

#ifdef BOARD_CCNV1_C1
    setup_ccnv1_c1();
#endif

    printf("\nStarting I2C tests\n");
    if (AMBA_I2C_MST_COUNT() == 0){
        printf("No I2C found!\n");
        printTestSummary();
        return 0;
    }

#ifdef TEST_I2C0_ONLY
    testI2C(0);
#else
    for (i=0;i<AMBA_I2C_MST_COUNT();i++){
        testI2C(i);
    }
#endif

    printTestSummary();

    return 0;
}


