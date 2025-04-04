/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2024-12-20 15:31:17 +0100 (pią, 20 gru 2024) $
* $Revision: 1119 $
*
*  ----------------------------------------------------------------------
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
 * -------------------------------------------------------------------- */

#include <ccproc.h>
#include <ccproc-utils.h>
#include <ccproc-amba.h>
#include <ccproc-amba-gpio.h>
#include <ccproc-amba-cfgregs.h>
#include <ccproc-amba-flash.h>
#include <flash.h>
#include <board.h>
#include <ate_test_functions.h>

/**
 * @brief Initialize the CCNV1 board
 */
void board_init(void)
{

    /* Enable GPIO controller */
    AMBA_GPIO_PTR->CTRL |= GPIO_CTRL_EN;

    /* Set UART0 to GPIO 0, 1, 2, 3 */
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(0,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(1,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(2,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(3,GPIO_ALTER_0);

    /* Set UART1 to GPIO 4, 5, 6, 7 */
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(4,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(5,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(6,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(7,GPIO_ALTER_0);

    /* Set I2C slave to GPIO 8, 9 */
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(8,GPIO_ALTER_1);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(9,GPIO_ALTER_1);

    /* Set pull-up to GPIO 8, 9 */
    AMBA_GPIO_PTR->PULL_LO |= GPIO_CONFIG_MASK(8,GPIO_PULL_UP);
    AMBA_GPIO_PTR->PULL_LO |= GPIO_CONFIG_MASK(9,GPIO_PULL_UP);

    /* Set UART3 to GPIO 12, 13, 14, 15 */
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(12,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(13,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(14,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(15,GPIO_ALTER_0);

    /* Enable PPS output */
    AMBA_GPIO_PTR->ALTER_HI |= GPIO_CONFIG_MASK(30,GPIO_ALTER_2);

    /* Disable GPIO controller */
    AMBA_GPIO_PTR->CTRL &= ~GPIO_CTRL_EN;

    /* Enable APB1 Bridge */
    AMBA_APB0_CFG_PTR->APB1_CFG = AMBA_APB1_EN;

    /* Configure Flash Controller */
    flash_configure(CORE_FREQ,(uint8_t)FLASH_READ_WAIT_STATES_CALC(CORE_FREQ),1,0);

    /* Configure PLL */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_PLL = CFGREG_COREFREQ_PLL_EN_MASK | (6 << CFGREG_COREFREQ_PLL_N_SHIFT) | (0 << CFGREG_COREFREQ_PLL_M_SHIFT) | CFGREG_COREFREQ_PLL_REF_SEL_MASK;
    while ((CFG_REGS_PTR->CFGREG_COREFREQ_STAT & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK) == 0);

    /* Switch to PLL */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_CLK = 2 << CFGREG_COREFREQ_CLK_CORE_SEL_SHIFT;

    /* switch debugger to new baud rate */
    CSR_CTRL_PTR->DBG_BAUD = DBG_UART_PRES((CORE_FREQ / DBG_BAUDRATE) / 16, (CORE_FREQ / DBG_BAUDRATE) % 16);

    /* Disable APB1 Bridge */
    AMBA_APB0_CFG_PTR->APB1_CFG &= ~AMBA_APB1_EN;

}

/**
 * @brief Power cycle function to drain power from external capacitors after reset
 */
void gnss_power_cycle(void)
{

    /* enable subblocks to drain power from external capacitors */

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_BALUN_MIXER1_CONF = CFGREG_BALUN_MIXER1_CONF_DEF | CFGREG_BALUN_MIXER1_CONF_BALUN_EN_MASK | CFGREG_BALUN_MIXER1_CONF_MIXER_EN_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_BALUN_MIXER5_CONF  = CFGREG_BALUN_MIXER5_CONF_DEF | CFGREG_BALUN_MIXER5_CONF_BALUN_EN_MASK | CFGREG_BALUN_MIXER5_CONF_MIXER_EN_MASK;

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_IF1_CONF  = CFGREG_IF1_CONF_DEF | CFGREG_IF1_CONF_EN_MASK | CFGREG_IF1_CONF_LPF_EN_MASK | CFGREG_IF1_CONF_PGA2_EN_MASK | CFGREG_IF1_CONF_PGA1_EN_MASK | CFGREG_IF1_CONF_PREAMP_EN_MASK | (3 << CFGREG_IF1_CONF_LPF_BAND_SHIFT);

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_IF5_CONF  = CFGREG_IF5_CONF_DEF | CFGREG_IF5_CONF_EN_MASK | CFGREG_IF5_CONF_LPF_EN_MASK | CFGREG_IF5_CONF_PGA2_EN_MASK | CFGREG_IF5_CONF_PGA1_EN_MASK | CFGREG_IF5_CONF_PREAMP_EN_MASK | (3 << CFGREG_IF5_CONF_LPF_BAND_SHIFT);

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_ADC1_CONF  = CFGREG_ADC1_CONF_DEF | CFGREG_ADC1_CONF_SAH_EN_MASK | CFGREG_ADC1_CONF_ADC_EN_MASK | (1 << CFGREG_ADC1_CONF_CLK_SEL_SHIFT) | (0 << CFGREG_ADC1_CONF_CLK_CONF_SHIFT);
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_ADC5_CONF  = CFGREG_ADC5_CONF_DEF | CFGREG_ADC5_CONF_SAH_EN_MASK | CFGREG_ADC5_CONF_ADC_EN_MASK | (1 << CFGREG_ADC5_CONF_CLK_SEL_SHIFT) | (0 << CFGREG_ADC5_CONF_CLK_CONF_SHIFT);

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_LNA15_CONF = CFGREG_LNA15_CONF_DEF | CFGREG_LNA15_CONF_EN_MASK | CFGREG_LNA15_CONF_EN_L1_MASK | CFGREG_LNA15_CONF_EN_L5_MASK | CFGREG_LNA15_CONF_L1_TUNE_SRC_MASK | CFGREG_LNA15_CONF_L5_TUNE_SRC_MASK;

    /* wait loop */

#ifdef _CCSDK_SIMULATION_FLOW
    for (int i=0; i<500; i++)
#else
    for (int i=0; i<5000000; i++)
#endif
        __asm__ __volatile__("nop");

    /* disable subblocks */

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_BALUN_MIXER1_CONF = CFGREG_BALUN_MIXER1_CONF_DEF;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_BALUN_MIXER5_CONF  = CFGREG_BALUN_MIXER5_CONF_DEF;

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_IF1_CONF  = CFGREG_IF1_CONF_DEF;

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_IF5_CONF  = CFGREG_IF5_CONF_DEF;

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_ADC1_CONF  = CFGREG_ADC1_CONF_DEF;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_ADC5_CONF  = CFGREG_ADC5_CONF_DEF; 

    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_LNA15_CONF = CFGREG_LNA15_CONF_DEF;

#ifdef _CCSDK_SIMULATION_FLOW
    for (int i=0; i<500; i++)
#else
    for (int i=0; i<500000; i++)
#endif
        __asm__ __volatile__("nop");

}

/**
 * @brief Initialize GNSS AFE registers
 */
void gnss_afe_regs(void)
{

    // Check if calibration has been performed
    bool cal_done = false;
    AMBA_APB0_CFG_PTR->APB1_CFG = 1;
    // Wait till Flash memory is busy
    while( AMBA_FLASH_PTR->STATUS & FLASH_STATUS_BUSY) ; 
    if(ANALOG_BIST_CLB_MARKER_PTR == ANALOG_BIST_CLB_PASS)
        cal_done = true;

    /* Configure GNSSAFE1 */
    /* Configure PM */
    if(cal_done)
    {
        CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
        CFG_REGS_PTR->CFGREG_PM_CONF = CFGREG_PM_CONF_DEF | CFGREG_PM_CONF_BGVR_EN_MASK | CFGREG_PM_CONF_IREF_EN_MASK | CFGREG_PM_CONF_VREF_EN_MASK | CFGREG_PM_CONF_LDO_RF_EN_MASK | CFGREG_PM_CONF_LDO_APLL_EN_MASK | CFGREG_PM_CONF_LDO_DPLL_EN_MASK | CFGREG_PM_CONF_LDO_IF_EN_MASK | CFGREG_PM_CONF_LDO_ADC_EN_MASK;
    }
    else
    {
        CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
        CFG_REGS_PTR->CFGREG_PM_CONF = CFGREG_PM_CONF_DEF | CFGREG_PM_CONF_BGVR_EN_MASK | CFGREG_PM_CONF_IREF_EN_MASK | CFGREG_PM_CONF_VREF_EN_MASK | CFGREG_PM_CONF_LDO_RF_EN_MASK | CFGREG_PM_CONF_LDO_APLL_EN_MASK | CFGREG_PM_CONF_LDO_DPLL_EN_MASK | CFGREG_PM_CONF_LDO_IF_EN_MASK | CFGREG_PM_CONF_LDO_ADC_EN_MASK | CFGREG_PM_CONF_IREF_TRIM_SRC_MASK | CFGREG_PM_CONF_BGVR_TRIM_SRC_MASK | CFGREG_PM_CONF_BGVR_TRIM_MASK;
    }
    while((CFG_REGS_PTR->CFGREG_PM_STAT & CFGREG_PM_STAT_PWR_UP_MASK) == 0) ;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PM_CONF |= CFGREG_PM_CONF_NRST_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_SPARE_CONF = 0x2E;
    /* Configure LNA1 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_LNA15_CONF = CFGREG_LNA15_CONF_DEF | CFGREG_LNA15_CONF_EN_MASK | CFGREG_LNA15_CONF_EN_L1_MASK | CFGREG_LNA15_CONF_EN_L5_MASK | CFGREG_LNA15_CONF_L1_TUNE_SRC_MASK | CFGREG_LNA15_CONF_L5_TUNE_SRC_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_LNA15_TUNE_CONF = (0x00FF << CFGREG_LNA15_TUNE_CONF_L1_SHIFT) | (0x00FF << CFGREG_LNA15_TUNE_CONF_L5_SHIFT);
    /* Configure MIXER_BALUN1 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_BALUN_MIXER1_CONF = CFGREG_BALUN_MIXER1_CONF_DEF | CFGREG_BALUN_MIXER1_CONF_BALUN_EN_MASK | CFGREG_BALUN_MIXER1_CONF_MIXER_EN_MASK;
    /* Configure PLL1 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL1DCO_CONF  = CFGREG_PLL1DCO_CONF_DEF | (0 << CFGREG_PLL1DCO_CONF_AMP_SHIFT) | CFGREG_PLL1DCO_CONF_AMP_LOAD_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL1_CONF  = (0x600000 << CFGREG_PLL1_CONF_FCW_SHIFT) | CFGREG_PLL1_CONF_EN_MASK;
    //CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    //CFG_REGS_PTR->CFGREG_PLL1DCO_CONF  = CFGREG_PLL1DCO_CONF_DEF | (15 << CFGREG_PLL1DCO_CONF_AMP_SHIFT);
    /* Configure IF1 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_IF1_CONF  = CFGREG_IF1_CONF_DEF | CFGREG_IF1_CONF_EN_MASK | CFGREG_IF1_CONF_LPF_EN_MASK | CFGREG_IF1_CONF_PGA2_EN_MASK | CFGREG_IF1_CONF_PGA1_EN_MASK | CFGREG_IF1_CONF_PREAMP_EN_MASK | (3 << CFGREG_IF1_CONF_LPF_BAND_SHIFT);
    /* Configure ADC1 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_ADC1_CONF  = CFGREG_ADC1_CONF_DEF | CFGREG_ADC1_CONF_SAH_EN_MASK | CFGREG_ADC1_CONF_ADC_EN_MASK | (1 << CFGREG_ADC1_CONF_CLK_SEL_SHIFT) | (0 << CFGREG_ADC1_CONF_CLK_CONF_SHIFT);

    /* Configure GNSSAFE5 */
    /* Configure MIXER_BALUN5 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_BALUN_MIXER5_CONF  = CFGREG_BALUN_MIXER5_CONF_DEF | CFGREG_BALUN_MIXER5_CONF_BALUN_EN_MASK | CFGREG_BALUN_MIXER5_CONF_MIXER_EN_MASK;
    /* Configure PLL5 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL5DCO_CONF  = CFGREG_PLL5DCO_CONF_DEF | (0 << CFGREG_PLL5DCO_CONF_AMP_SHIFT) | CFGREG_PLL5DCO_CONF_AMP_LOAD_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL5_CONF  = (0x480000 << CFGREG_PLL5_CONF_FCW_SHIFT) | CFGREG_PLL5_CONF_EN_MASK;
    //CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    //CFG_REGS_PTR->CFGREG_PLL5DCO_CONF  = CFGREG_PLL5DCO_CONF_DEF | (15 << CFGREG_PLL5DCO_CONF_AMP_SHIFT);
    /* Configure IF5 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_IF5_CONF  = CFGREG_IF5_CONF_DEF | CFGREG_IF5_CONF_EN_MASK | CFGREG_IF5_CONF_LPF_EN_MASK | CFGREG_IF5_CONF_PGA2_EN_MASK | CFGREG_IF5_CONF_PGA1_EN_MASK | CFGREG_IF5_CONF_PREAMP_EN_MASK | (3 << CFGREG_IF5_CONF_LPF_BAND_SHIFT);
    /* Configure ADC5 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_ADC5_CONF  = CFGREG_ADC5_CONF_DEF | CFGREG_ADC5_CONF_SAH_EN_MASK | CFGREG_ADC5_CONF_ADC_EN_MASK | (1 << CFGREG_ADC5_CONF_CLK_SEL_SHIFT) | (0 << CFGREG_ADC5_CONF_CLK_CONF_SHIFT);

}


/**
 * @brief Initialize GNSS AFE
 */
int gnss_afe_init(void)
{
    int res = 0;
    gnss_power_cycle();
    gnss_afe_regs();
    res = analog_bist();
    return res;
}

/***********************************************************************************************************************
 * Name            : GnssReadL1AgcDb
 * Function to read L1/E1 AGC gain in dB
 *
 * Parameters  :
 * Name         I/O             Type        Unit      Desc
 * gain_i       I/O         uint8_t*         n/a      Pointer to variable where I gain will be saved
 * gain_q       I/O         uint8_t*         n/a      Pointer to variable where Q gain will be saved
 * returned       O           int8_t         n/a      Returns -1 in case of error
 **********************************************************************************************************************/
/** \copydoc GnssReadL1AgcDb */
int GnssGnssReadL1AgcDb(uint8_t *gain_i, uint8_t *gain_q)
{
    uint32_t agc_i;
    uint32_t agc_q;
    uint32_t agc_temp;
 
    agc_temp = CFG_REGS_PTR->CFGREG_IF1_STAT;
    agc_i = (agc_temp & CFGREG_IF1_STAT_AGC_CTRL_I_MASK) >>  CFGREG_IF1_STAT_AGC_CTRL_I_SHIFT;
    agc_q = (agc_temp & CFGREG_IF1_STAT_AGC_CTRL_Q_MASK) >>  CFGREG_IF1_STAT_AGC_CTRL_Q_SHIFT;

    *gain_i = (uint8_t) ((agc_i & 0x00000007) + ((agc_i >> 3) & 0x00000003)*6 + ((agc_i >> 5) & 0x00000003)*6 + ((agc_i >> 7) & 0x00000003)*6);
    *gain_q = (uint8_t) ((agc_q & 0x00000007) + ((agc_q >> 3) & 0x00000003)*6 + ((agc_q >> 5) & 0x00000003)*6 + ((agc_q >> 7) & 0x00000003)*6);
    return 0;
}

/***********************************************************************************************************************
 * Name            : GnssReadL5AgcDb
 * Function to read L5/E5 AGC gain in dB
 *
 * Parameters  :
 * Name         I/O             Type        Unit      Desc
 * gain_i       I/O         uint8_t*         n/a      Pointer to variable where I gain will be saved
 * gain_q       I/O         uint8_t*         n/a      Pointer to variable where Q gain will be saved
 * returned       O           int8_t         n/a      Returns -1 in case of error
 **********************************************************************************************************************/
/** \copydoc GnssReadL5AgcDb */
int GnssGnssReadL5AgcDb(uint8_t *gain_i, uint8_t *gain_q)
{
    uint32_t agc_i;
    uint32_t agc_q;
    uint32_t agc_temp;
 
    agc_temp = CFG_REGS_PTR->CFGREG_IF5_STAT;
    agc_i = (agc_temp & CFGREG_IF5_STAT_AGC_CTRL_I_MASK) >>  CFGREG_IF5_STAT_AGC_CTRL_I_SHIFT;
    agc_q = (agc_temp & CFGREG_IF5_STAT_AGC_CTRL_Q_MASK) >>  CFGREG_IF5_STAT_AGC_CTRL_Q_SHIFT;

    *gain_i = (uint8_t) ((agc_i & 0x00000007) + ((agc_i >> 3) & 0x00000003)*6 + ((agc_i >> 5) & 0x00000003)*6 + ((agc_i >> 7) & 0x00000003)*6);
    *gain_q = (uint8_t) ((agc_q & 0x00000007) + ((agc_q >> 3) & 0x00000003)*6 + ((agc_q >> 5) & 0x00000003)*6 + ((agc_q >> 7) & 0x00000003)*6);
    return 0;
}

