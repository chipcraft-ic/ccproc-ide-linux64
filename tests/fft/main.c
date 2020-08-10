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
* $Date: 2020-08-06 13:45:31 +0200 (czw, 06 sie 2020) $
* $Revision: 627 $
*H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-csr.h>
#include <ccproc-mcore.h>
#include <ccproc-fft.h>
#include <ccproc-pwd.h>
#include <ccproc-amba.h>
#include <core_util.h>
#include <pwd_util.h>
#include <stdio.h>
#include "test.h"

// align to 1kB
static volatile int __attribute__((aligned(1024))) int_test1_re[768];
// align to 1kB
static volatile int __attribute__((aligned(1024))) int_test1_im[768];

// FFT data format: Q16.15

// each array contains dummy -1 int to make sure at least some cross 1kB boundary
int re[] = {2097152,2293760,2490368,2719744,2883584,3080192,3276800,3440640,3571712,3702784,3833856,3932160,4030464,4096000,4161536,4194304,4194304,4194304,4161536,4096000,4030464,3932160,3833856,3702784,3571712,3440640,3276800,3080192,2883584,2719744,2490368,2293760,2097152,1900544,1703936,1474560,1310720,1114112,917504,753664,622592,491520,360448,262144,163840,98304,32768,0,0,0,32768,98304,163840,262144,360448,491520,622592,753664,917504,1114112,1310720,1474560,1703936,1900544,2097152,2293760,2490368,2719744,2883584,3080192,3276800,3440640,3571712,3702784,3833856,3932160,4030464,4096000,4161536,4194304,4194304,4194304,4161536,4096000,4030464,3932160,3833856,3702784,3571712,3440640,3276800,3080192,2883584,2719744,2490368,2293760,2097152,1900544,1703936,1474560,1310720,1114112,917504,753664,622592,491520,360448,262144,163840,98304,32768,0,0,0,32768,98304,163840,262144,360448,491520,622592,753664,917504,1114112,1310720,1474560,1703936,1900544,2097152,2293760,2490368,2719744,2883584,3080192,3276800,3440640,3571712,3702784,3833856,3932160,4030464,4096000,4161536,4194304,4194304,4194304,4161536,4096000,4030464,3932160,3833856,3702784,3571712,3440640,3276800,3080192,2883584,2719744,2490368,2293760,2097152,1900544,1703936,1474560,1310720,1114112,917504,753664,622592,491520,360448,262144,163840,98304,32768,0,0,0,32768,98304,163840,262144,360448,491520,622592,753664,917504,1114112,1310720,1474560,1703936,1900544,2097152,2293760,2490368,2719744,2883584,3080192,3276800,3440640,3571712,3702784,3833856,3932160,4030464,4096000,4161536,4194304,4194304,4194304,4161536,4096000,4030464,3932160,3833856,3702784,3571712,3440640,3276800,3080192,2883584,2719744,2490368,2293760,2097152,1900544,1703936,1474560,1310720,1114112,917504,753664,622592,491520,360448,262144,163840,98304,32768,0,0,0,32768,98304,163840,262144,360448,491520,622592,753664,917504,1114112,1310720,1474560,1703936,1900544,-1};
int im[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,-1};

int re_ref_res[]  = {536810576,1455,3577,3023,-2331,-2231,-1955,-571,-1230,-256,-365,-128,1974,-71,-105,-38,675,-12,-2,7,-1486,12,28,19,343,19,50,25,-589,48,86,44,1967,46,90,46,1287,53,107,52,461,49,101,60,777,52,105,56,983,51,105,52,-264,48,106,57,472,52,109,53,1589,57,111,56,4064,49,107,47,339,74,130,59,501,63,118,59,490,67,124,61,1015,55,121,61,38,55,124,64,507,61,129,69,203,56,117,62,2034,57,125,60,499,57,121,57,501,63,124,68,328,52,117,56,1008,56,123,61,193,52,115,57,492,58,118,55,1044,59,119,63,8176,61,121,63,1047,63,115,59,492,56,115,56,194,61,123,60,1007,60,118,55,328,66,126,67,505,59,120,61,499,66,122,60,2033,58,116,58,201,65,127,62,505,61,123,58,35,60,123,62,1015,69,127,64,492,58,122,63,502,62,125,71,341,49,109,54,4064,59,115,63,1589,50,106,53,473,57,108,49,-266,55,110,53,983,49,103,45,772,51,106,50,461,53,101,49,1291,46,91,42,1966,47,93,48,-583,21,49,29,345,19,28,2,-1484,4,-5,-14,674,-32,-95,-73,1975,-142,-375,-257,-1234,-556,-1952,-2239,-2330,3035,3597,1451,-1};
int re_iref_res[] = {536810576,1451,3597,3035,-2330,-2239,-1952,-556,-1234,-257,-375,-142,1975,-73,-95,-32,674,-14,-5,4,-1484,2,28,19,345,29,49,21,-583,48,93,47,1966,42,91,46,1291,49,101,53,461,50,106,51,772,45,103,49,983,53,110,55,-266,49,108,57,473,53,106,50,1589,63,115,59,4064,54,109,49,341,71,125,62,502,63,122,58,492,64,127,69,1015,62,123,60,35,58,123,61,505,62,127,65,201,58,116,58,2033,60,122,66,499,61,120,59,505,67,126,66,328,55,118,60,1007,60,123,61,194,56,115,56,492,59,115,63,1047,63,121,61,8176,63,119,59,1044,55,118,58,492,57,115,52,193,61,123,56,1008,56,117,52,328,68,124,63,501,57,121,57,499,60,125,57,2034,62,117,56,203,69,129,61,507,64,124,55,38,61,121,55,1015,61,124,67,490,59,118,63,501,59,130,74,339,47,107,49,4064,56,111,57,1589,53,109,52,472,57,106,48,-264,52,105,51,983,56,105,52,777,60,101,49,461,52,107,53,1287,46,90,46,1967,44,86,48,-589,25,50,19,343,19,28,12,-1486,7,-2,-12,675,-38,-105,-71,1974,-128,-365,-256,-1230,-571,-1955,-2231,-2331,3023,3577,1455,-1};

int im_ref_res[]  = {0,-5175,-5202,-1727,-268057023,-1041,-1730,-740,-5192,-566,-1030,-470,283063,-393,-736,-338,-5146,-300,-567,-267,-476108,-233,-458,-220,-1687,-197,-383,-181,1055244,-167,-331,-161,-4943,-149,-289,-142,367996,-127,-253,-124,-956,-110,-222,-110,-265132,-98,-201,-95,-1533,-94,-186,-90,-217976,-81,-162,-74,-625,-75,-149,-70,334825,-69,-135,-64,-4096,-63,-124,-59,1052756,-52,-108,-55,-419,-46,-99,-51,325712,-45,-90,-44,-684,-40,-80,-36,-8436,-34,-73,-33,-272,-33,-63,-23,-557418,-30,-57,-27,-848,-25,-54,-25,-133724,-21,-43,-20,-156,-21,-34,-13,-689232,-14,-28,-12,-203,-13,-25,-9,-400717,-9,-12,-14,-49,-7,-9,-3,66966,-10,-2,-5,0,3,4,1,-66969,1,10,4,50,6,18,8,400719,11,20,10,204,8,29,15,689232,15,32,18,155,19,41,25,133724,21,47,27,847,25,57,32,557418,31,69,30,274,32,72,38,8436,42,79,41,685,42,90,44,-325714,45,98,52,421,59,109,58,-1052757,59,121,64,4096,59,134,69,-334824,72,148,79,621,82,159,85,217978,91,182,92,1530,92,198,100,265132,104,223,115,956,119,253,131,-367998,140,285,149,4944,157,330,171,-1055246,185,387,202,1682,215,456,241,476104,270,574,298,5147,337,741,387,-283061,457,1024,572,5197,731,1729,1039,268057030,1712,5216,5201,-1};
int im_iref_res[] = {0,5201,5216,1712,268057030,1039,1729,731,5197,572,1024,457,-283061,387,741,337,5147,298,574,270,476104,241,456,215,1682,202,387,185,-1055246,171,330,157,4944,149,285,140,-367998,131,253,119,956,115,223,104,265132,100,198,92,1530,92,182,91,217978,85,159,82,621,79,148,72,-334824,69,134,59,4096,64,121,59,-1052757,58,109,59,421,52,98,45,-325714,44,90,42,685,41,79,42,8436,38,72,32,274,30,69,31,557418,32,57,25,847,27,47,21,133724,25,41,19,155,18,32,15,689232,15,29,8,204,10,20,11,400719,8,18,6,50,4,10,1,-66969,1,4,3,0,-5,-2,-10,66966,-3,-9,-7,-49,-14,-12,-9,-400717,-9,-25,-13,-203,-12,-28,-14,-689232,-13,-34,-21,-156,-20,-43,-21,-133724,-25,-54,-25,-848,-27,-57,-30,-557418,-23,-63,-33,-272,-33,-73,-34,-8436,-36,-80,-40,-684,-44,-90,-45,325712,-51,-99,-46,-419,-55,-108,-52,1052756,-59,-124,-63,-4096,-64,-135,-69,334825,-70,-149,-75,-625,-74,-162,-81,-217976,-90,-186,-94,-1533,-95,-201,-98,-265132,-110,-222,-110,-956,-124,-253,-127,367996,-142,-289,-149,-4943,-161,-331,-167,1055244,-181,-383,-197,-1687,-220,-458,-233,-476108,-267,-567,-300,-5146,-338,-736,-393,283063,-470,-1030,-566,-5192,-740,-1730,-1041,-268057023,-1727,-5202,-5175,-1};

int fft_size;

static volatile int core_started = 0;

static volatile int irq_entered = 0;

void isr4(void){
    irq_entered++;
    FFT_PTR->IRQF = FFT_IRQ_FLAG;
}

void fftWait(void){
    while ((FFT_PTR->STATUS & FFT_STAT_BUSY) == 0);
    while ((FFT_PTR->STATUS & FFT_STAT_BUSY) == 1);
}

static void testFFTProc(){

    int loc_re[256];
    int loc_im[256];
    int i;

    core_started++;

    // wait for all cores
    while (MCORE_PTR->STATUS != (1<<MCORE_PTR->CORE_NUM)-1);

    FFT_PTR->REDLA = (int)&re;
    FFT_PTR->IMDLA = (int)&im;
    FFT_PTR->REULA = (int)&loc_re;
    FFT_PTR->IMULA = (int)&loc_im;
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_DLREV | FFT_STAT_FFT | FFT_STAT_UL | FFT_STAT_START;

    fftWait();

    while(core_started > CSR_STATUS_GET_CORE_ID(CSR_CTRL_PTR->STATUS));

    for (i=0; i<fft_size; i++){
        assertEq(re_ref_res[i], loc_re[i]);
    }
    for (i=0; i<fft_size; i++){
        assertEq(im_ref_res[i], loc_im[i]);
    }

    FFT_PTR->REDLA = (int)&re;
    FFT_PTR->IMDLA = (int)&im;
    FFT_PTR->REULA = (int)&loc_re;
    FFT_PTR->IMULA = (int)&loc_im;
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_DLREV | FFT_STAT_FFT | FFT_STAT_UL | FFT_STAT_START | FFT_STAT_IFFT;

    fftWait();

    for (i=0; i<fft_size; i++){
        assertEq(re_iref_res[i], loc_re[i]);
    }
    for (i=0; i<fft_size; i++){
        assertEq(im_iref_res[i], loc_im[i]);
    }

    core_started--;

}

void testFFT(void){

    int loc_re[256];
    int loc_im[256];
    int k, i, numOfCores;

    // enable interrupts
    CSR_CTRL_PTR->IRQ_MASK |= (1 << FFT_IRQn);
    CSR_CTRL_PTR->STATUS |= CSR_STAT_CIEN;

    // start cores
    numOfCores = MCORE_PTR->CORE_NUM;
    core_started = 0;
    for (k = 2; k < numOfCores; ++k){
        coreStart(k, &testFFTProc, NULL);
    }

    FFT_PTR->REDLA = (int)&re;
    FFT_PTR->IMDLA = (int)&im;
    FFT_PTR->REULA = (int)&loc_re;
    FFT_PTR->IMULA = (int)&loc_im;
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_DLREV | FFT_STAT_FFT | FFT_STAT_UL | FFT_STAT_START | FFT_STAT_IE;

    fftWait();

    // wait for other cores to complete
    while (MCORE_PTR->STATUS != 3);

    for (i=0; i<fft_size; i++){
        assertEq(re_ref_res[i], loc_re[i]);
    }
    for (i=0; i<fft_size; i++){
        assertEq(im_ref_res[i], loc_im[i]);
    }

    FFT_PTR->REDLA = (int)&re;
    FFT_PTR->IMDLA = (int)&im;
    FFT_PTR->REULA = (int)&loc_re;
    FFT_PTR->IMULA = (int)&loc_im;
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_DLREV | FFT_STAT_FFT | FFT_STAT_UL | FFT_STAT_START | FFT_STAT_IFFT;

    fftWait();

    for (i=0; i<fft_size; i++){
        assertEq(re_iref_res[i], loc_re[i]);
    }
    for (i=0; i<fft_size; i++){
        assertEq(im_iref_res[i], loc_im[i]);
    }

    assertEq(irq_entered, 1);

}

int sqrAbsMul(int valin){

    int loc_val;

    uint32_t val;
    uint32_t part0;
    uint32_t part1;
    uint32_t part2;
    uint32_t res;

    loc_val = valin;
    if (valin < 0){
        loc_val = -valin;
    }
    val = (uint32_t)loc_val;

    part0 = val & 0xffff;
    part0 *= part0;
    part0 >>= 30;

    part1 = (val & 0xffff);
    part1 *= val >> 16;
    part1 >>= 14;

    part2 = val & 0xffff0000;
    part2 >>= 16;
    part2 *= part2;
    part2 <<= 2;

    res = part0 + part1 + part1 + part2;

    return res;
}

void testSqrAbs(void){

    uint32_t i;
    uint32_t sqr[2];
    volatile uint32_t *ptr;

    FFT_PTR->REDLA = (int)&re_ref_res;
    FFT_PTR->IMDLA = (int)&im_ref_res;
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_ABSSQR | FFT_STAT_START;

    fftWait();

    ptr = (uint32_t*)FFT_MEMORY_BASE;

    for (i=0; i<fft_size; i++){
        sqr[0] = sqrAbsMul(re_ref_res[i]);
        sqr[1] = sqrAbsMul(im_ref_res[i]);
        assertEq(sqr[0] + sqr[1], *ptr);
        ptr++;
    }

}

void testConjugate(void){

    uint32_t i;
    volatile uint32_t *ptr;

    FFT_PTR->REDLA = (int)&re_ref_res;
    FFT_PTR->IMDLA = (int)&im_ref_res;
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_CONJU | FFT_STAT_START;

    fftWait();

    ptr = (uint32_t*)FFT_MEMORY_BASE;

    for (i=0; i<fft_size; i++){
        assertEq(re_ref_res[i], *ptr);
        ptr++;
    }
    for (i=0; i<fft_size; i++){
        assertEq(-im_ref_res[i], *ptr);
        ptr++;
    }
}

void clearInternalMem(void){
    uint32_t i;
    volatile uint32_t *ptr;
    ptr = (uint32_t*)FFT_MEMORY_BASE;
    for (i=0; i<fft_size; i++){
        ptr[i] = 0xa5a5a5a5;
    }
}

void testInternalMemory(void){

    uint32_t i, j, k;
    volatile uint32_t *ptr;

    int loc_re[512];
    int loc_im[512];

    clearInternalMem();

    for (i=0; i<fft_size; i++){
        loc_re[i] = 0xa5a5a5a5;
        loc_im[i] = 0xa5a5a5a5;
    }

    // test download to internal memory from shared with boundary crossing

    k=245;
    printf("Shared download:\nRun:");

    // special case first (burst into not burst)
    for (i=0; i<fft_size; i++){
        int_test1_re[i] = i;
        int_test1_im[k+i] = fft_size + i;
    }
    FFT_PTR->REDLA = (int)(int_test1_re);
    FFT_PTR->IMDLA = (int)(int_test1_im+k);
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_START;
    fftWait();
    ptr = (uint32_t*)FFT_MEMORY_BASE;
    for (i=0; i<fft_size; i++){
        assertEq(int_test1_re[i], *ptr);
        ptr++;
    }
    for (i=0; i<fft_size; i++){
        assertEq(int_test1_im[k+i], *ptr);
        ptr++;
    }

    // rest
    for (j=0; j<50; j++){

        if (j%5 == 0){
            printf("\n");
        }
        printf("%2d ",(int)j);

        for (i=0; i<fft_size; i++){
            int_test1_re[k+j+i] = i;
            int_test1_im[k+j+i] = fft_size + i;
        }

        FFT_PTR->REDLA = (int)(int_test1_re+k+j);
        FFT_PTR->IMDLA = (int)(int_test1_im+k+j);
        FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_START;

        fftWait();

        ptr = (uint32_t*)FFT_MEMORY_BASE;

        for (i=0; i<fft_size; i++){
            assertEq(int_test1_re[k+j+i], *ptr);
            ptr++;
        }
        for (i=0; i<fft_size; i++){
            assertEq(int_test1_im[k+j+i], *ptr);
            ptr++;
        }

        clearInternalMem();

    }

    // test upload from internal memory to spram

    FFT_PTR->REDLA = (int)&re_ref_res;
    FFT_PTR->IMDLA = (int)&im_ref_res;
    FFT_PTR->REULA = (int)&loc_re;
    FFT_PTR->IMULA = (int)&loc_im;
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_UL | FFT_STAT_START;

    fftWait();

    for (i=0; i<fft_size; i++){
        assertEq(re_ref_res[i], loc_re[i]);
        ptr++;
    }
    for (i=0; i<fft_size; i++){
        assertEq(im_ref_res[i], loc_im[i]);
        ptr++;
    }

    clearInternalMem();

    // test download to internal memory from spram

    FFT_PTR->REDLA = (int)&loc_re;
    FFT_PTR->IMDLA = (int)&loc_im;
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_START;

    fftWait();

    ptr = (uint32_t*)FFT_MEMORY_BASE;

    for (i=0; i<fft_size; i++){
        assertEq(loc_re[i], *ptr);
        ptr++;
    }
    for (i=0; i<fft_size; i++){
        assertEq(loc_im[i], *ptr);
        ptr++;
    }

    // test upload from internal memory to shared

    printf("\nShared upload:\nRun:");

    ptr = (uint32_t*)FFT_MEMORY_BASE;

    for (i=0; i<2*fft_size; i++){
        *ptr = i;
        ptr++;
    }

    // special case first (burst into not burst)
    FFT_PTR->REULA = (int)(int_test1_re);
    FFT_PTR->IMULA = (int)(int_test1_im+k);
    FFT_PTR->STATUS = FFT_STAT_UL | FFT_STAT_START;
    fftWait();
    ptr = (uint32_t*)FFT_MEMORY_BASE;
    for (i=0; i<fft_size; i++){
        assertEq(int_test1_re[i], *ptr);
        ptr++;
    }
    for (i=0; i<fft_size; i++){
        assertEq(int_test1_im[k+i], *ptr);
        ptr++;
    }

    // rest
    for (j=0; j<50; j++){

        if (j%5 == 0){
            printf("\n");
        }
        printf("%2d ",(int)j);

        FFT_PTR->REULA = (int)(int_test1_re+k+j);
        FFT_PTR->IMULA = (int)(int_test1_im+k+j);
        FFT_PTR->STATUS = FFT_STAT_UL | FFT_STAT_START;

        fftWait();

        ptr = (uint32_t*)FFT_MEMORY_BASE;

        for (i=0; i<fft_size; i++){
            assertEq(int_test1_re[k+j+i], *ptr);
            ptr++;
        }
        for (i=0; i<fft_size; i++){
            assertEq(int_test1_im[k+j+i], *ptr);
            ptr++;
        }

    }

    printf("\n");

}

void testScaling(void){

    uint32_t i;
    volatile uint32_t *ptr;

    int loc_re[512];
    int loc_im[512];

    int scale = 8;
    if (fft_size == 512)
        scale = 9;

    // test scaled download to internal memory

    FFT_PTR->REDLA = (int)&re;
    FFT_PTR->IMDLA = (int)&im_ref_res;
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_START | FFT_STAT_DLSCL;

    fftWait();

    ptr = (uint32_t*)FFT_MEMORY_BASE;

    for (i=0; i<fft_size; i++){
        assertEq(re[i]>>scale, *ptr);
        ptr++;
    }
    for (i=0; i<fft_size; i++){
        assertEq(im_ref_res[i]>>scale, *ptr);
        ptr++;
    }

    // test scaled upload from internal memory
    FFT_PTR->REDLA = (int)&re;
    FFT_PTR->IMDLA = (int)&im_ref_res;
    FFT_PTR->REULA = (int)&loc_re;
    FFT_PTR->IMULA = (int)&loc_im;
    FFT_PTR->STATUS = FFT_STAT_DL | FFT_STAT_UL | FFT_STAT_START | FFT_STAT_ULSCL;

    fftWait();

    for (i=0; i<fft_size; i++){
        assertEq(re[i]>>scale, loc_re[i]);
        ptr++;
    }
    for (i=0; i<fft_size; i++){
        assertEq(im_ref_res[i]>>scale, loc_im[i]);
        ptr++;
    }

}

static void coreMain()
{
    if (CSR_CTRL_PTR->CPU_INFO_0 & CPU_FFT){

        fft_size = 1 << FFT_STATUS_GET_SIZE(FFT_PTR->STATUS);
        if (fft_size == 1)
            fft_size = 256;
        printf("\nStarting FFT %d test\n",fft_size);

        if (fft_size == 256 || fft_size == 512){
            printf("Test Internal Memory\n");
            testInternalMemory();
            if (fft_size == 256){
                printf("Test Scaling\n");
                testScaling();
                printf("Test Conjugate\n");
                testConjugate();
                printf("Test SqrAbs\n");
                testSqrAbs();
                if (CSR_CTRL_PTR->CPU_INFO_0 & CPU_SPRAM) {
                    printf("Test FFT %d\n",fft_size);
                    testFFT();
                }
                else {
                    printf("No SPRAM to test FFT.\n");
                }
            }
            else{
                printf("FFT 512 test TBD!\n");
            }
        }
        else{
            printf("Not supported FFT test size!\n");
        }
    }
    else{
        printf("\nStarting FFT test\n");
        printf("No FFT found!\n");
        //return;
    }

    printTestSummary();
}

int main(void)
{

    if (MCORE_PTR->CORE_NUM < 2){
        printf("\nStarting FFT test\n");
        printf("Not enough cores to perform test!\n");
        return 0;
    }

    // Disable lockstep mode if present
    if (lockstepDisable() == 0){
        printf("Disabling lockstep mode!\n");
    }

    coreStart(1, &coreMain, NULL);
    mainPowerDown(0);
    while (MCORE_PTR->STATUS != 1);

    return 0;

}
