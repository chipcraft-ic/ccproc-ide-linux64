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
* File Name : ate_test_functions.c
* Author    : Krzysztof Siwiec
* ******************************************************************************
* $Date: 2024-07-04 21:54:52 +0200 (czw, 04 lip 2024) $
* $Revision: 1069 $
*H*****************************************************************************/

#include <core_util.h>
#include <board.h>
#include <ccproc-amba.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <ccproc-gnss-ise.h>
#include <ccproc-amba-cfgregs.h>
#include <ccproc-amba-gpio.h>
#include <ccproc-amba-flash.h>
#include <ccproc-csr.h>
#include <ccproc-gnss.h>
#include <ccproc-mcore.h>
#include <ccproc-perfcnt.h>
#include <crc-verification.h>
#include <ate_test_functions.h>

#define RTC_RDY_CNT_MAX     (1000000)
#define CORE_RDY_CNT_MAX    (1000000)

#define GNSS_CHANN_PER_CORE (16)
#define GNSS_CHANN_PER_BANK (16)
#define GNSS_START_CORE     (1)
#define GNSS_FSAMPLE_TCK    (65472000)
#define GNSS_CARR_PIPQ_PQMI (1)
#define GNSS_LOCK_DEF_SCALE (1)
#define GNSS_IRQ_NUM_BIST   (4)

static const uint64_t   GNSS_Q32_OVF    = ((uint64_t)1<<32);       ///< constant containing one bit set on 32. position
static volatile uint8_t afe_bist_stat   = 0;

/**
 * @brief Function to convert local to global channel number
 */
static uint16_t GnssGetCoreToGlobalChannelNumBist(uint16_t channel_num)
{
    return channel_num + GNSS_CHANN_PER_CORE*(CSR_STATUS_GET_CORE_ID(CSR_CTRL_PTR->STATUS)-GNSS_START_CORE);
}

/**
 * @brief Function to convert global channel number to local core channel number
 */
static uint16_t GnssGetGlobalToCoreChannelNumBist(uint16_t channel_num)
{
    uint16_t tmp = channel_num - GNSS_CHANN_PER_CORE*(CSR_STATUS_GET_CORE_ID(CSR_CTRL_PTR->STATUS)-GNSS_START_CORE);
    return tmp % GNSS_CHANN_PER_CORE;
}

/**
 * @brief Function to start accumulators for tracking
 */
static void GnssStartAccumulatorsTrackingBist(uint16_t channel_num, uint64_t start_time_tmr)
{
    uint16_t core_channel_num = GnssGetGlobalToCoreChannelNumBist(channel_num);
    uint16_t bank_channel_num = core_channel_num % GNSS_CHANN_PER_BANK;
    uint32_t int_start_time_tmr = (uint32_t)start_time_tmr;
    if (int_start_time_tmr == 0) int_start_time_tmr++; // int_start_time_tmr = 0 is invalid, see GNSS-ISE documentation
    GNSS_CHANN_SET(core_channel_num);
    GNSS_FREE_ACCU_WR(1<<bank_channel_num,int_start_time_tmr);
}

/**
 * @brief Function to get current time
 */
static uint64_t GnssGetTimeBist(void)
{
    volatile uint32_t hi, lo;
    lo = PERFCNT_PTR->CYCLE_LO;
    hi = PERFCNT_PTR->CYCLE_HI;
    return (((uint64_t)hi << 32) | lo);
}

/**
 * @brief Setup Afe Bist carrier
 */
static void GnssSetChannelCarrierAfeBist(uint16_t channel_num,  int32_t carrier_freq_hz, bool acquisition, uint32_t* nco_freq_base)
{
    uint16_t core_channel_num = GnssGetGlobalToCoreChannelNumBist(channel_num);
    uint32_t fsample_hz;
    uint32_t nco_freq;
    fsample_hz = GNSS_FSAMPLE_TCK;

    if(carrier_freq_hz < 0)
    {
        carrier_freq_hz = - carrier_freq_hz;
        nco_freq = GNSS_Q32_OVF - (GNSS_Q32_OVF * carrier_freq_hz) / fsample_hz;
    }
    else
    {
        nco_freq = (GNSS_Q32_OVF * carrier_freq_hz) / fsample_hz;
    }

    //TODO: handle wrong frequency better
    if ((uint32_t) carrier_freq_hz > fsample_hz/2)
    {
        //LOG(LOG_DEBUG,"(%s:%u) Invalid carrier NCO frequency %d!\n",__FILE__,__LINE__,(int)carrier_freq_hz);
    }
    if (nco_freq_base != NULL)
    {
        *nco_freq_base = nco_freq;
    }
    GNSS_CHANN_SET(core_channel_num);
    uint32_t carr_ptr = 0;

    GNSS_CARR_SET(carr_ptr, GNSS_CARR_PIPQ_PQMI);
    GNSS_CARR_FREQ(nco_freq);
}

/**
 * @brief Setup Afe Bist channel
 */
static uint32_t GnssSetChannelCodeAfeBist(uint16_t channel_num)
{
    uint32_t prn_chips;
    prn_chips = 1023;
    uint16_t prn_words = (prn_chips/32)+1;
    uint32_t prn_array[33] = { 0U, };
    uint32_t* prn_result;

    prn_result = &(prn_array[0]);

    GNSS_CHANN_SET(channel_num);
    GNSS_PCODE_ADDR_SET(0,0);
    for (int i=0; i<prn_words; i++)
    {
        GNSS_PCODE_WR(prn_result[i]);
    }

    // after channel initialization set lock coefficient to single integration period
    GNSS_PCODE_LEN(prn_chips, 1, 10, GNSS_LOCK_DEF_SCALE);
    // secondary code is disabled
    GNSS_SCODE_LEN(0);

    // set code nco
    uint32_t code_freq_hz = 1023000;
    uint32_t chip_freq = 2;
    uint32_t epl_freq = 1;

    uint64_t nco_freq_check = (GNSS_Q32_OVF * code_freq_hz * chip_freq) / GNSS_FSAMPLE_TCK;

    if (nco_freq_check == 0 || nco_freq_check >= GNSS_Q32_OVF )
    {
        if (nco_freq_check == GNSS_Q32_OVF)
            nco_freq_check = GNSS_Q32_OVF - 1;
        else
        {
            //LOG(LOG_DEBUG,"(%s:%u) Invalid code NCO frequency!\n",__FILE__,__LINE__);
        }
    }

    uint32_t nco_freq_hz = (uint32_t) nco_freq_check;
    //LOG(LOG_INFO,"(%s:%u) Set code for channel %d, nco_freq %u!\n",__FILE__,__LINE__,(int)channel_num,(unsigned)nco_freq_hz);
    GNSS_CHANN_SET(channel_num);
    GNSS_CODE_NCO_FREQ(nco_freq_hz, 0);
    GNSS_CODE_EPL_FREQ(epl_freq,chip_freq);
    GNSS_PCODE_ADDR_SET(0,0);
    return nco_freq_hz;
}

/**
 * @brief Setup Afe Bist accumulator
 */
static void GnssSetupAccumulatorsAfeBist(uint16_t channel_num, bool pll_update, bool dll_update, bool tracking)
{
    uint16_t core_channel_num = GnssGetGlobalToCoreChannelNumBist(channel_num);
    uint16_t bank_channel_num = core_channel_num % GNSS_CHANN_PER_BANK;
    GNSS_CHANN_SET(core_channel_num);

    GNSS_FREE_UPDATE_WR(GNSS_FREE_UPDATE_RD() & ~((1 << bank_channel_num) | (1 << (bank_channel_num+16)))); // clear PLL and DLL update bits
    GNSS_FREE_UPDATE_WR(GNSS_FREE_UPDATE_RD() | ((pll_update << bank_channel_num) | (dll_update << (bank_channel_num+16)))); // set PLL and DLL update bits

    GNSS_FREE_ACCU_WR(GNSS_FREE_ACCU_RD() & ~((1 << bank_channel_num) | (1 << (bank_channel_num+16))),0); // clear very early/late branches and free running bits

    // clear remaining data in accumulators
    //GNSS_ACCU_ADD(0,1<<31); // TODO: may break gathering ranges in tracking

    if (tracking == true)
    {
        GNSS_FREE_ACCU_WR(GNSS_FREE_ACCU_RD(),0);
    }
    else // acquisition, use very early and very late branches
    {
        GNSS_FREE_ACCU_WR(GNSS_FREE_ACCU_RD() | (1 << (bank_channel_num+16)),0); // set very early/late branches bits
    }

}

/**
 * @brief Setup Afe Bist
 */
static void GnssSetupGnssAfeBist(uint16_t channel_num, enum gnss_ise_rfafe_enum rfafe)
{

    uint16_t core_channel_num = GnssGetGlobalToCoreChannelNumBist(channel_num);
    uint16_t bank_channel_num = core_channel_num % GNSS_CHANN_PER_BANK;

    GNSS_CHANN_SET(core_channel_num);
    uint32_t gnss_afe_mask = GNSS_AFE_RD();
    gnss_afe_mask &= ~(3 << (bank_channel_num*2)); // clear AFE bitsGnssSetChannelCarrierAfeBist
    gnss_afe_mask |= (rfafe << (bank_channel_num*2)); // set AFE bits
    GNSS_AFE_WR(gnss_afe_mask);

}

/**
 * @brief Run single Afe Bist
 */
static float GnssRunSingleAfeBist(uint8_t lpf_band, uint8_t mod_att, uint8_t mod_presc, uint8_t mod_mode, uint8_t imag, enum gnss_ise_rfafe_enum rfafe, uint32_t *signal)
{
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_IF1_CONF  = (CFG_REGS_PTR->CFGREG_IF1_CONF & ~CFGREG_IF1_CONF_LPF_BAND_MASK) | (lpf_band << CFGREG_IF1_CONF_LPF_BAND_SHIFT);
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_IF5_CONF  = (CFG_REGS_PTR->CFGREG_IF5_CONF & ~CFGREG_IF5_CONF_LPF_BAND_MASK) | (lpf_band << CFGREG_IF5_CONF_LPF_BAND_SHIFT);
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL1_CONF |= CFGREG_PLL1_CONF_TEST_EN_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL5_CONF |= CFGREG_PLL5_CONF_TEST_EN_MASK;
    /* Configure PLL */
    /*CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_CLK = 1 << CFGREG_COREFREQ_CLK_CORE_SEL_SHIFT;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_PLL = (6 << CFGREG_COREFREQ_PLL_N_SHIFT) | CFGREG_COREFREQ_PLL_REF_SEL_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_PLL = CFGREG_COREFREQ_PLL_EN_MASK | (6 << CFGREG_COREFREQ_PLL_N_SHIFT) | CFGREG_COREFREQ_PLL_REF_SEL_MASK;
    while ((CFG_REGS_PTR->CFGREG_COREFREQ_STAT & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK) == 0);
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_CLK = 2 << CFGREG_COREFREQ_CLK_CORE_SEL_SHIFT;*/

    uint32_t mcu_freq = CORE_FREQ;

    int32_t test_rf_hz;

    if(((mod_mode + imag) % 2) > 0)
        test_rf_hz = (-1) * (int32_t)(mcu_freq / (4<<mod_presc));
    else
        test_rf_hz = (int32_t)(mcu_freq / (4<<mod_presc));

    uint32_t nco_freq_base = 0;

    if(rfafe == GNSS_ISE_RFAFE_L1E1)
    {
        CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
        CFG_REGS_PTR->CFGREG_SPARE_CONF = 0x1 | (mod_mode << 1) | (mod_presc << 2)| (mod_att << 8);
    }
    else if(rfafe == GNSS_ISE_RFAFE_L5E5)
    {
        CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
        CFG_REGS_PTR->CFGREG_SPARE_CONF = 0x10 | (mod_mode << 5) | (mod_presc << 6)| (mod_att << 8);
    }

    GNSS_PTR->IRQMAP = 0;
    GNSS_PTR->CTRL |= GNSS_CTRL_CODE_TICK_IE | GNSS_CTRL_CODE_OVR_IE | GNSS_CTRL_CODE_ERR_IE;

    uint64_t start_time_tmr = GnssGetTimeBist() + 1e-3*GNSS_FSAMPLE_TCK;
    for(uint8_t i=0;i < GNSS_CHANN_PER_CORE; i = i + 1)
    {
        // setup channel 0 for tracking
        GnssSetChannelCarrierAfeBist(i, test_rf_hz+i*10e3, false, &nco_freq_base);
        GnssSetChannelCodeAfeBist(i);
        GnssSetupGnssAfeBist(i, rfafe);
        GnssSetupAccumulatorsAfeBist(i, false, false, true);
        GnssStartAccumulatorsTrackingBist(i, start_time_tmr);
    }

    uint8_t channel_count = 0;
    int32_t data_i[GNSS_CHANN_PER_CORE];
    int32_t data_q[GNSS_CHANN_PER_CORE];

    while(channel_count < GNSS_CHANN_PER_CORE)
    {
        int i=0;
        //for (int i=0; i<GnssGetBanksNum(); i++)
        //{
            //GNSS_BANK_SET(i);
            if(GNSS_PTR->TICKF != 0)
            {
                for (int j=0; j<GNSS_CHANN_PER_BANK; j++)
                {
                    uint16_t global_channel_num = GnssGetCoreToGlobalChannelNumBist((i*GNSS_CHANN_PER_BANK)+j);
                    if (GNSS_PTR->TICKF & (1<<j))
                    {

                        GNSS_CHANN_SET(j);
                        GNSS_ACCU_GET();
                        data_i[global_channel_num] = GNSS_ACCU_GET();
                        data_q[global_channel_num] = GNSS_ACCU_GET();
                        GNSS_ACCU_GET();
                        GNSS_ACCU_GET();
                        GNSS_ACCU_GET();
                        GNSS_ACCU_GET();
                        GNSS_ACCU_GET();
                        GNSS_ACCU_GET();
                        GNSS_ACCU_GET();
                        GNSS_ACCU_GET();

                        GNSS_CHANN_SET(j);
                        GNSS_FREE_ACCU_WR(GNSS_FREE_ACCU_RD() & ~(1 << j),0); // clear free running bit

                        GNSS_PTR->TICKF = (1<<j); // clear flag
                        channel_count += 1;
                    }
                }
            }
        //}
    }

    /* Configure PLL */
    /*CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_CLK = 1 << CFGREG_COREFREQ_CLK_CORE_SEL_SHIFT;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_PLL = (6 << CFGREG_COREFREQ_PLL_N_SHIFT) | CFGREG_COREFREQ_PLL_REF_SEL_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_PLL = CFGREG_COREFREQ_PLL_EN_MASK | (6 << CFGREG_COREFREQ_PLL_N_SHIFT) | CFGREG_COREFREQ_PLL_REF_SEL_MASK;
    while ((CFG_REGS_PTR->CFGREG_COREFREQ_STAT & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK) == 0);
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_CLK = 2 << CFGREG_COREFREQ_CLK_CORE_SEL_SHIFT;*/

    //GNSS_PTR->IRQMAP = 1 << GNSS_IRQ_NUM_BIST;
    uint64_t noise_std = 0;

    for(uint8_t i=0;i < GNSS_CHANN_PER_CORE; i = i + 1)
    {
        if(i>0)
            noise_std += ((int64_t)data_i[i])*((int64_t)data_i[i]) + ((int64_t)data_q[i])*((int64_t)data_q[i]);
    }

    noise_std = sqrt(noise_std/GNSS_CHANN_PER_CORE);

    *signal = sqrt(((int64_t)data_i[0])*((int64_t)data_i[0]) + ((int64_t)data_q[0])*((int64_t)data_q[0]));

    return 20*log10((float)(*signal)/noise_std);
}

/**
 * @brief Core Afe Bist function
 */
static void core_FunctionAfeBist()
{

    uint8_t lpf_band = 3;
    uint8_t mod_mode = 0;
    uint8_t mod_att = 8;
    uint8_t mod_presc =3;
    uint8_t imag = 0;
    enum gnss_ise_rfafe_enum rfafe = GNSS_ISE_RFAFE_L1E1;
    uint32_t signal_l1;
    uint32_t signal_l1_hf;
    uint32_t imag_l1;
    uint32_t signal_l5;
    uint32_t signal_l5_hf;
    uint32_t imag_l5;

    if ((GNSS_STATUS_RD() & 1) == 0)
    {
        GNSS_STATUS_WR(1);
    }

    GNSS_PTR->STCR |= 0x70; //GNSS_STCR_L1E1_EN | GNSS_STCR_L5E5_EN | GNSS_STCR_L2E6_EN;
    PERFCNT_PTR->STATUS |= (PERFCNT_STAT_SRC_AFE << PERFCNT_STAT_SRC_SHIFT) & PERFCNT_STAT_SRC_MASK; // initialize time source
    PERFCNT_PTR->STATUS |= PERFCNT_STAT_EN;

    //uint32_t test_start = GnssGetUsec();
    float snr_l1_sig = GnssRunSingleAfeBist(lpf_band, mod_att, mod_presc, mod_mode, imag, rfafe, &signal_l1);
    imag = 1;
    float snr_l1_imag = GnssRunSingleAfeBist(lpf_band, mod_att, mod_presc, mod_mode, imag, rfafe, &imag_l1);
    rfafe = GNSS_ISE_RFAFE_L5E5;
    imag = 1;
    float snr_l5_imag = GnssRunSingleAfeBist(lpf_band, mod_att, mod_presc, mod_mode, imag, rfafe, &imag_l5);
    imag = 0;
    float snr_l5_sig = GnssRunSingleAfeBist(lpf_band, mod_att, mod_presc, mod_mode, imag, rfafe, &signal_l5);
    mod_att = 2;
    mod_presc =0;
    float snr_l5_sig_hf = GnssRunSingleAfeBist(lpf_band, mod_att, mod_presc, mod_mode, imag, rfafe, &signal_l5_hf);
    rfafe = GNSS_ISE_RFAFE_L1E1;
    float snr_l1_sig_hf = GnssRunSingleAfeBist(lpf_band, mod_att, mod_presc, mod_mode, imag, rfafe, &signal_l1_hf);

    /*uint32_t test_stop = GnssGetUsec();
    LOG(LOG_INFO,"(%s:%u) Test time %u\n", __FILE__,__LINE__,(unsigned)(test_stop-test_start));

    LOG(LOG_INFO,"(%s:%u) SNR_L1_SIG %f, env %u\n", __FILE__,__LINE__,snr_l1_sig, (unsigned) signal_l1);
    LOG(LOG_INFO,"(%s:%u) SNR_L1_SIG_HF %f, env %u\n", __FILE__,__LINE__,snr_l1_sig_hf, (unsigned) signal_l1_hf);
    LOG(LOG_INFO,"(%s:%u) SNR_L1_IMAG %f, env %u\n", __FILE__,__LINE__,snr_l1_imag, (unsigned) imag_l1);
    LOG(LOG_INFO,"(%s:%u) SNR_L5_SIG %f, env %u\n", __FILE__,__LINE__,snr_l5_sig, (unsigned) signal_l5);
    LOG(LOG_INFO,"(%s:%u) SNR_L5_SIG_HF %f, env %u\n", __FILE__,__LINE__,snr_l5_sig_hf, (unsigned) signal_l5_hf);
    LOG(LOG_INFO,"(%s:%u) SNR_L5_IMAG %f, env %u\n", __FILE__,__LINE__,snr_l5_imag, (unsigned) imag_l5);*/

    /*printf("(%s:%u) SNR_L1_SIG %u, env %u\n", __FILE__,__LINE__,(unsigned)snr_l1_sig, (unsigned) signal_l1);
    printf("(%s:%u) SNR_L1_SIG_HF %u, env %u\n", __FILE__,__LINE__,(unsigned)snr_l1_sig_hf, (unsigned) signal_l1_hf);
    printf("(%s:%u) SNR_L1_IMAG %u, env %u\n", __FILE__,__LINE__,(unsigned)snr_l1_imag, (unsigned) imag_l1);
    printf("(%s:%u) SNR_L5_SIG %u, env %u\n", __FILE__,__LINE__,(unsigned)snr_l5_sig, (unsigned) signal_l5);
    printf("(%s:%u) SNR_L5_SIG_HF %u, env %u\n", __FILE__,__LINE__,(unsigned)snr_l5_sig_hf, (unsigned) signal_l5_hf);
    printf("(%s:%u) SNR_L5_IMAG %u, env %u\n", __FILE__,__LINE__,(unsigned)snr_l5_imag, (unsigned) imag_l5);*/

    uint32_t snr_l1_sig_u, snr_l5_sig_u, snr_l1_imag_u, snr_l5_imag_u, snr_l1_sig_hf_u, snr_l5_sig_hf_u;
    snr_l1_sig_u = (snr_l1_sig < 0) ? ((uint32_t) 0) : ((uint32_t) snr_l1_sig);
    snr_l5_sig_u = (snr_l5_sig < 0) ? ((uint32_t) 0) : ((uint32_t) snr_l5_sig);
    snr_l1_imag_u = (snr_l1_imag < 0) ? ((uint32_t) 0) : ((uint32_t) snr_l1_imag);
    snr_l5_imag_u = (snr_l5_imag < 0) ? ((uint32_t) 0) : ((uint32_t) snr_l5_imag);
    snr_l1_sig_hf_u = (snr_l1_sig_hf < 0) ? ((uint32_t) 0) : ((uint32_t) snr_l1_sig_hf);
    snr_l5_sig_hf_u = (snr_l5_sig_hf < 0) ? ((uint32_t) 0) : ((uint32_t) snr_l5_sig_hf);


    AMBA_FLASH_PTR->LOCK = FLASH_LOCK_MANUFACTURER_ROW_ACCESS_PASSWORD;
    AMBA_FLASH_PTR->MANUFACTURER_ROW[1] = (snr_l5_imag_u << 24) + (snr_l5_sig_u << 16) + (snr_l1_imag_u << 8) + snr_l1_sig_u;

    while( AMBA_FLASH_PTR->STATUS & FLASH_STATUS_BUSY) ;

    AMBA_FLASH_PTR->LOCK = FLASH_LOCK_MANUFACTURER_ROW_ACCESS_PASSWORD;
    AMBA_FLASH_PTR->MANUFACTURER_ROW[2] = (snr_l5_sig_hf_u << 8) + snr_l1_sig_hf_u;

    if((snr_l1_sig - snr_l1_imag) < 10)
    {
        afe_bist_stat = 11;
        return;
    }

    if((snr_l5_sig - snr_l5_imag) < 10)
    {
        afe_bist_stat = 11;
        return;
    }

    if((snr_l1_sig_hf - snr_l1_imag) < 10)
    {
        afe_bist_stat = 11;
        return;
    }

    if((snr_l5_sig_hf - snr_l5_imag) < 10)
    {
        afe_bist_stat = 11;
        return;
    }

    //printf("(%s:%u) Test passed!\n", __FILE__,__LINE__);
    afe_bist_stat = 10;
    return;

}

/**
 * @brief GNSS AFE Bist function
 */
static int GnssAfeBist(void)
{
    gnss_afe_regs();
    coreStart(1, &core_FunctionAfeBist, NULL);
    while(afe_bist_stat < 10) ;
    if(afe_bist_stat == 11)
        return 1;
    return 0;
}

/**
 * @brief Calibrate analog
 */
int analog_bist(void)
{
    // Write if calibration has been performed earlier
    // Enable APB1 bridge
    AMBA_APB0_CFG_PTR->APB1_CFG = 1;
    // Wait till Flash memory is busy
    while( AMBA_FLASH_PTR->STATUS & FLASH_STATUS_BUSY) ;

    if(ANALOG_BIST_CLB_MARKER_PTR == ANALOG_BIST_CLB_PASS)
        return 0;

    int res = -1;
    // verify firmware fist
    res -= ( cc_verification_firmware_checksum_compare() ? 0 : 1 );

    if (res == -1)
        res += Rc32kOscCal();
    if (res == -1)
        res += Rc16mOscCal();
    if (res == -1)
        res += GnssAfePmCal();
    if (res == -1)
        res += GnssAfeBist();

    if (res == -1)
    {
        AMBA_FLASH_PTR->LOCK = FLASH_LOCK_MANUFACTURER_ROW_ACCESS_PASSWORD;
        ANALOG_BIST_CLB_MARKER_PTR = ANALOG_BIST_CLB_PASS;
    }

    return res;

}

/**
 * @brief Calibrate internal 32 kHz oscillator
 */
int Rc32kOscCal(void)
{

    AMBA_GPIO_PTR->CTRL = GPIO_CTRL_EN;

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_RTCCONF |= CFGREG_RTCCONF_RC_RTC_CAL_MASK;

    int cnt;
    for (cnt=0; cnt<RTC_RDY_CNT_MAX; cnt++)
    {
        if ((CFG_REGS_PTR->CFGREG_RTCSTAT & CFGREG_RTCSTAT_RC_RTC_RDY_MASK) != 0)
            break;
    }
    if (cnt>=RTC_RDY_CNT_MAX)
    {
        CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
        CFG_REGS_PTR->CFGREG_RTCCONF &= ~CFGREG_RTCCONF_RC_RTC_CAL_MASK;
        return -1;
    }

    // Write cal values to flash
    // Enable APB1 bridge
    AMBA_APB0_CFG_PTR->APB1_CFG = 1;
    // Wait till Flash memory is busy
    while( AMBA_FLASH_PTR->STATUS & FLASH_STATUS_BUSY) ;

    // get current settings

    uint32_t temp;
    temp = ANALOG_BIST_OSC_CALIB_PTR;
    // clear BGVR and IREF trim fields
    temp &= ~(0x1FC0);
    temp |= ((CFG_REGS_PTR->CFGREG_RTCSTAT & CFGREG_RTCCONF_RC_RTC_VAL_MASK) >> CFGREG_RTCCONF_RC_RTC_VAL_SHIFT) << 6;

    AMBA_FLASH_PTR->LOCK = FLASH_LOCK_ACCESS_PASSWORD;
    ANALOG_BIST_OSC_CALIB_PTR = temp;

    // Wait till Flash memory is busy
    while( AMBA_FLASH_PTR->STATUS & FLASH_STATUS_BUSY) ;

    //printf("OSC 32K calibration %x\n",(unsigned)((ANALOG_BIST_OSC_CALIB_PTR>>6)&0x7F));

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_RTCCONF &= ~CFGREG_RTCCONF_RC_RTC_VAL_SRC_MASK;


    return 0;
}

/**
 * @brief Calibrate internal 16 MHz oscillator
 */
int Rc16mOscCal(void)
{

    AMBA_GPIO_PTR->CTRL = GPIO_CTRL_EN;

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_CLK |= CFGREG_COREFREQ_CLK_RC_CORE_CAL_MASK;

    int cnt;
    for (cnt=0; cnt<CORE_RDY_CNT_MAX; cnt++)
    {
        if ((CFG_REGS_PTR->CFGREG_COREFREQ_STAT & CFGREG_COREFREQ_STAT_RC_CORE_RDY_MASK) != 0)
            break;
    }
    if (cnt>=CORE_RDY_CNT_MAX)
    {
        CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
        CFG_REGS_PTR->CFGREG_COREFREQ_CLK &= ~CFGREG_COREFREQ_CLK_RC_CORE_CAL_MASK;
        return -1;
    }

    // Write cal values to flash
    // Enable APB1 bridge
    AMBA_APB0_CFG_PTR->APB1_CFG = 1;
    // Wait till Flash memory is busy
    while( AMBA_FLASH_PTR->STATUS & FLASH_STATUS_BUSY) ;

    // get current settings

    uint32_t temp;
    temp = ANALOG_BIST_OSC_CALIB_PTR;
    // clear BGVR and IREF trim fields
    temp &= ~(0x3F);
    temp |= (CFG_REGS_PTR->CFGREG_COREFREQ_STAT & CFGREG_COREFREQ_CLK_RC_CORE_VAL_MASK) >> CFGREG_COREFREQ_CLK_RC_CORE_VAL_SHIFT;


    AMBA_FLASH_PTR->LOCK = FLASH_LOCK_ACCESS_PASSWORD;
    ANALOG_BIST_OSC_CALIB_PTR = temp;

    // Wait till Flash memory is busy
    while( AMBA_FLASH_PTR->STATUS & FLASH_STATUS_BUSY) ;

    //printf("OSC 16M calibration %x\n",(unsigned)(ANALOG_BIST_OSC_CALIB_PTR&0x3F));

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_CLK &= ~CFGREG_COREFREQ_CLK_RC_CORE_VAL_SRC_MASK;

    return 0;
}

/**
 * @brief Calibrate GNSS AFE Power Management
 */
int GnssAfePmCal(void)
{
    gnss_afe_regs();

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PM_CONF = CFGREG_PM_CONF_LDO_ADC_EN_MASK | CFGREG_PM_CONF_LDO_IF_EN_MASK | CFGREG_PM_CONF_LDO_DPLL_EN_MASK | CFGREG_PM_CONF_LDO_APLL_EN_MASK | CFGREG_PM_CONF_LDO_RF_EN_MASK
                                    | CFGREG_PM_CONF_VREF_EN_MASK | CFGREG_PM_CONF_IREF_TRIM_SRC_MASK | CFGREG_PM_CONF_IREF_EN_MASK | CFGREG_PM_CONF_BGVR_TRIM_SRC_MASK | CFGREG_PM_CONF_BGVR_EN_MASK;

    //printf("PM conf is set to %x, IREF to %u VREF %u\n",(unsigned)CFG_REGS_PTR->CFGREG_PM_CONF,(unsigned)((CFG_REGS_PTR->CFGREG_PM_CONF&CFGREG_PM_CONF_IREF_TRIM_MASK)>>CFGREG_PM_CONF_IREF_TRIM_SHIFT),(unsigned)((CFG_REGS_PTR->CFGREG_PM_CONF&CFGREG_PM_CONF_BGVR_TRIM_MASK)>>CFGREG_PM_CONF_BGVR_TRIM_SHIFT));

    while( (CFG_REGS_PTR->CFGREG_PM_STAT & CFGREG_PM_STAT_PWR_UP_MASK) == 0) ;

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PM_CONF = CFGREG_PM_CONF_LDO_ADC_EN_MASK | CFGREG_PM_CONF_LDO_IF_EN_MASK | CFGREG_PM_CONF_LDO_DPLL_EN_MASK | CFGREG_PM_CONF_LDO_APLL_EN_MASK | CFGREG_PM_CONF_LDO_RF_EN_MASK
                                    | CFGREG_PM_CONF_VREF_EN_MASK | CFGREG_PM_CONF_IREF_TRIM_SRC_MASK | CFGREG_PM_CONF_IREF_EN_MASK | CFGREG_PM_CONF_BGVR_TRIM_SRC_MASK | CFGREG_PM_CONF_BGVR_EN_MASK
                                    | CFGREG_PM_CONF_BGVR_TRIM_MASK| CFGREG_PM_CONF_CAL_EN_MASK | CFGREG_PM_CONF_TEST_EN_MASK;

    uint8_t iref_end = 0;

    //printf("PM conf is set to %x, IREF to %u VREF %u\n",(unsigned)CFG_REGS_PTR->CFGREG_PM_CONF,(unsigned)((CFG_REGS_PTR->CFGREG_PM_CONF&CFGREG_PM_CONF_IREF_TRIM_MASK)>>CFGREG_PM_CONF_IREF_TRIM_SHIFT),(unsigned)((CFG_REGS_PTR->CFGREG_PM_CONF&CFGREG_PM_CONF_BGVR_TRIM_MASK)>>CFGREG_PM_CONF_BGVR_TRIM_SHIFT));

    for(uint8_t i = 1; i < 16; i = i + 1)
    {
        uint8_t comp;
        for(uint16_t k = 4096; k>0;k=k-1)
        {
            asm("NOP");
        }

        comp = ((CFG_REGS_PTR->CFGREG_PM_STAT & CFGREG_PM_STAT_IREF_COMP_MASK) >> CFGREG_PM_STAT_IREF_COMP_SHIFT);
        if(iref_end == 0)
        {
            if(comp == 0)
            {
                uint32_t temp = CFG_REGS_PTR->CFGREG_PM_CONF;
                temp = (temp & ~CFGREG_PM_CONF_IREF_TRIM_MASK) | (i << CFGREG_PM_CONF_IREF_TRIM_SHIFT);
                CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
                CFG_REGS_PTR->CFGREG_PM_CONF = temp;
                //printf("SET PM conf to %x, IREF to %u VREF %u\n",(unsigned)CFG_REGS_PTR->CFGREG_PM_CONF,(unsigned)((CFG_REGS_PTR->CFGREG_PM_CONF&CFGREG_PM_CONF_IREF_TRIM_MASK)>>CFGREG_PM_CONF_IREF_TRIM_SHIFT),(unsigned)((CFG_REGS_PTR->CFGREG_PM_CONF&CFGREG_PM_CONF_BGVR_TRIM_MASK)>>CFGREG_PM_CONF_BGVR_TRIM_SHIFT));
            }
            else
            {
                iref_end = 1;
            }
        }

        if(iref_end == 1)
            break;
    }

    // Write cal values to flash
    // Enable APB1 bridge
    AMBA_APB0_CFG_PTR->APB1_CFG = 1;
    // Wait till Flash memory is busy
    while( AMBA_FLASH_PTR->STATUS & FLASH_STATUS_BUSY) ;

    // get current settings

    uint32_t temp;
    temp = ANALOG_BIST_AFE_CALIB_PTR;
    // clear BGVR and IREF trim fields
    temp &= ~(0xFF << 12);
    temp |= ((((CFG_REGS_PTR->CFGREG_PM_CONF & CFGREG_PM_CONF_BGVR_TRIM_MASK) >> CFGREG_PM_CONF_BGVR_TRIM_SHIFT))  | (((CFG_REGS_PTR->CFGREG_PM_CONF & CFGREG_PM_CONF_IREF_TRIM_MASK) >> (CFGREG_PM_CONF_IREF_TRIM_SHIFT - 4)))) << 12;


    AMBA_FLASH_PTR->LOCK = FLASH_LOCK_ACCESS_PASSWORD;
    ANALOG_BIST_AFE_CALIB_PTR = temp;
    
    // Wait till Flash memory is busy
    while( AMBA_FLASH_PTR->STATUS & FLASH_STATUS_BUSY) ;
    
    //printf("Calibration pointer %x, VREF %u, IREF %u\n",(unsigned)ANALOG_BIST_AFE_CALIB_PTR,(unsigned)((ANALOG_BIST_AFE_CALIB_PTR>>12)&0xF),(unsigned)((ANALOG_BIST_AFE_CALIB_PTR>>16)&0xF));    

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PM_CONF &= ~(CFGREG_PM_CONF_IREF_TRIM_SRC_MASK | CFGREG_PM_CONF_BGVR_TRIM_SRC_MASK);

    return 0;
}
