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
#include <ccproc-irq.h>
#include <ccproc-pwd.h>
#include <ccproc-amba.h>
#include <ccproc-amba-systick.h>
#include <ccproc-amba-eth.h>
#include <stdio.h>

#include "test.h"

#define ETH_IRQ_NUM 2
#define ETH_MII_CLKDIV 100
#define ETH_PACKET_LEN 1403

#define TEST_PATTERN 0x12345678

#ifdef ETH_SIM_TEST
    #define ETH_PHY_ADDR       0x01
#else
    #define ETH_PHY_ADDR       0x07
#endif

volatile uint32_t dummy;
volatile uint32_t finish;
volatile uint32_t error = 0;

volatile uint8_t tx_frame[ETH_PACKET_LEN+200];
volatile uint8_t rx_frame[ETH_PACKET_LEN+200];

void isr1(void)
{

    if (AMBA_ETH_PTR(0)->INT &ETH_INT_TXE){
        error += 2;
    }
    if (AMBA_ETH_PTR(0)->INT &ETH_INT_RXE){
        error += 4;
    }

    AMBA_ETH_PTR(0)->INT = 0x7F;
    finish = 1;

    AMBA_SYSTICK_PTR->CTRL &= ~SYSTICK_CTRL_EN;

}

void isr3(void)
{

    AMBA_SYSTICK_PTR->IRQF |= 0;
    finish++;
    error++;

    AMBA_SYSTICK_PTR->CTRL &= ~SYSTICK_CTRL_EN;

}

void systick_timeout(){

    IRQ_CTRL_PTR->IRQ_MASK |= 1 | (1 << 3);

    AMBA_SYSTICK_PTR->CTRL = 0;
    AMBA_SYSTICK_PTR->COUNT = 0;
    AMBA_SYSTICK_PTR->PRES = 255;
    AMBA_SYSTICK_PTR->PER = 2048;
    AMBA_SYSTICK_PTR->IRQMAP = 1 << 3;
    AMBA_SYSTICK_PTR->CTRL |= SYSTICK_CTRL_IE | SYSTICK_CTRL_EN;
}

int main(void)
{

    volatile uint32_t *addr;
    //volatile uint32_t data;
    int i;

    addr = (uint32_t*)0x1000;
    for (i=0;i<1600;i++){
        if (i < 32)
            tx_frame[i] = 0xFF;
        else
            tx_frame[i] = *addr;
        addr++;
    }

    printf("\nStarting ETH test\n\n");

    #ifdef ETH_SIM_TEST
        printf("ETH_SIM_TEST: defined.\n");
    #else
        printf("ETH_SIM_TEST: undefined.\n");
    #endif

    if (AMBA_APB2_EXIST() == 0){
        printf("No ETH found!\n");
        printTestSummary();
        return 0;
    }

    if (AMBA_ETH_COUNT() == 0){
        printf("No ETH found!\n");
        printTestSummary();
        return 0;
    }

    finish = 0;

    IRQ_CTRL_PTR->IRQ_MASK |= (1 << 1);
    IRQ_CTRL_PTR->STATUS |= IRQ_STAT_CIEN;

    AMBA_APB2_CFG_PTR->ETHMAP_0 = ETH_IRQ_NUM;
    AMBA_APB2_CFG_PTR->CLOCK_0 |= AMBA_ETH0_CLK;

    printf("\nTESTING FIFO MEMORY\n");
    addr = AMBA_ETH_RX_FIFO_PTR(0);
    for (i=0;i<ETH_FIFO_SIZE*2;i++){
        *addr = TEST_PATTERN ^ (uint32_t)addr;
        addr++;
    }
    addr = AMBA_ETH_RX_FIFO_PTR(0);
    for (i=0;i<ETH_FIFO_SIZE*2;i++){
        assertEq(*addr,TEST_PATTERN ^ (uint32_t)addr);
        addr++;
    }

    printf("ETH MDIO READ\n");

    AMBA_ETH_PTR(0)->MIIMODER = ETH_MII_CLKDIV;
    AMBA_ETH_PTR(0)->MIIADDRESS = 0x0000 | ETH_PHY_ADDR;
    AMBA_ETH_PTR(0)->MIICOMMAND = ETH_MIICOMMAND_RSTAT;
    while (AMBA_ETH_PTR(0)->MIISTATUS & ETH_MIISTATUS_BUSY){};

    //printf("data = 0x%08x\n",(unsigned)AMBA_ETH_PTR(0)->MIIRX_DATA);

    printf("ETH MDIO WRITE\n");

    AMBA_ETH_PTR(0)->MIIADDRESS = 0x0000 | ETH_PHY_ADDR;

    #ifdef ETH_SIM_TEST
        AMBA_ETH_PTR(0)->MIITX_DATA = 0x2000; // | 0x8000;
    #else
        AMBA_ETH_PTR(0)->MIITX_DATA = 0x2000 | 0x8000;
    #endif

    AMBA_ETH_PTR(0)->MIICOMMAND = ETH_MIICOMMAND_WCTRLDATA;
    while (AMBA_ETH_PTR(0)->MIISTATUS & ETH_MIISTATUS_BUSY){};

    AMBA_ETH_PTR(0)->MIIADDRESS = 0x0000 | ETH_PHY_ADDR;
    AMBA_ETH_PTR(0)->MIICOMMAND = ETH_MIICOMMAND_RSTAT;
    while (AMBA_ETH_PTR(0)->MIISTATUS & ETH_MIISTATUS_BUSY){};

    //printf("data = 0x%08x\n",(unsigned)AMBA_ETH_PTR(0)->MIIRX_DATA);

    #ifdef ETH_SIM_TEST
        PWD_PTR->CTRL |= (1<<PWD_CTRL_COREINT_SHIFT) | (3<<PWD_CTRL_PER2INT_SHIFT) | (2<<PWD_CTRL_PER0INT_SHIFT) | PWD_CTRL_KEY;
    #endif

    //printf("ETH WB MST TEST\n");

    AMBA_ETH_PTR(0)->INT = ETH_INT_RXF | ETH_INT_RXE | ETH_INT_TXE;
    AMBA_ETH_PTR(0)->INT_MASK = ETH_INT_MASK_RXF | ETH_INT_MASK_TXE | ETH_INT_MASK_RXE;

    AMBA_ETH_PTR(0)->MODER = ETH_MODER_RXEN | ETH_MODER_TXEN | ETH_MODER_LOOPBCK | ETH_MODER_CRCEN | ETH_MODER_PAD;

    AMBA_ETH_RXBD_DEF_PTR(0,0)->ADDR = (uint32_t)(&rx_frame[1]);
    AMBA_ETH_RXBD_DEF_PTR(0,0)->LEN_STATUS = ETH_BD_MAKE_LEN(ETH_PACKET_LEN) | ETH_RX_BD_EMPTY | ETH_RX_BD_IRQ;

    AMBA_ETH_TXBD_DEF_PTR(0,0)->LEN_STATUS = ETH_BD_MAKE_LEN(ETH_PACKET_LEN) | ETH_TX_BD_IRQ | ETH_TX_BD_PAD | ETH_TX_BD_CRC;
    AMBA_ETH_TXBD_DEF_PTR(0,0)->ADDR = (uint32_t)(&tx_frame[1]);

    //printf("desc = 0x%x ",(unsigned)AMBA_ETH_TXBD_DEF_PTR(0,0)->LEN_STATUS);
    //printf("0x%x\n",(unsigned)AMBA_ETH_TXBD_DEF_PTR(0,0)->ADDR);

    AMBA_ETH_TXBD_DEF_PTR(0,0)->LEN_STATUS |= ETH_TX_BD_WRAP;

    //printf("desc = 0x%x\n",(unsigned)AMBA_ETH_TXBD_DEF_PTR(0,0)->LEN_STATUS);

    AMBA_ETH_TXBD_DEF_PTR(0,0)->LEN_STATUS |= ETH_TX_BD_READY;

    addr = &dummy;

    systick_timeout();

    // to make some traffic
    while (finish == 0){
        *addr = finish;
    }

    if (error > 0){
        assertTrue(0);
        printf("\nTIMEOUT ERROR RECEIVING FRAME\n");
    }
    else {
        for (i=0;i<1;i++){
            //assertEq(rx_frame[i+1],tx_frame[i+1]);
            if (tx_frame[i+1] != rx_frame[i+1]){
                printf("\nERROR at position: %d\n",i);
                printf("TX address: 0x%8x\n",(unsigned)&tx_frame[i+1]);
                printf("RX address: 0x%8x\n",(unsigned)&rx_frame[i+1]);
                printf("Received: %d\n",rx_frame[i+1]);
                printf("Should be: %d\n",tx_frame[i+1]);
            }
        }
    }

    if (AMBA_ETH_RXBD_DEF_PTR(0,0)->LEN_STATUS & ETH_RX_BD_OVERRUN){
        printf("\nRECEIVE DESCRIPTOR OVERRUN\n");
        assertTrue(0);
    }
    else{
        assertTrue(1);
    }

    if (AMBA_ETH_TXBD_DEF_PTR(0,0)->LEN_STATUS & ETH_TX_BD_UNDERRUN){
        printf("\nTRANSMIT DESCRIPTOR UNDERRUN\n");
        assertTrue(0);
    }
    else{
        assertTrue(1);
    }

    printf("TESTING BUFFER MEMORY\n");
    addr = (uint32_t*)AMBA_ETH_TXBD_DEF_PTR(0,0);
    for (i=0;i<ETH_BD_NUM*2;i++){
        *addr = TEST_PATTERN ^ (uint32_t)addr;
        addr++;
    }
    addr = (uint32_t*)AMBA_ETH_TXBD_DEF_PTR(0,0);
    for (i=0;i<ETH_BD_NUM*2;i++){
        assertEq(*addr,TEST_PATTERN ^ (uint32_t)addr);
        addr++;
    }

    printf("\nFINISH CODE: %d\n",(int)error);

    printTestSummary();

    return 0;

}
