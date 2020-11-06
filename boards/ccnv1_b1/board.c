/* ----------------------------------------------------------------------
*
* Copyright (c) 2020 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2020-09-15 14:33:30 +0200 (wto, 15 wrz 2020) $
* $Revision: 640 $
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
#include <ccproc-amba-memctrl.h>
#include <flash.h>
#include <board.h>

/**
 * @brief Trim flash macros
 */
void flash_trim(void)
{

    AMBA_FLASH_PTR->ADDRESS = 4*0x390;
    AMBA_FLASH_PTR->DATA = 0xFFFFFFFF;
    AMBA_FLASH_PTR->COMMAND = 0x1D;
    while (AMBA_FLASH_PTR->COMMAND & FLASH_STATUS_BUSY);
    if (AMBA_FLASH_PTR->DATA == 0x5A5A5A5A)
        return;

    for (int i=0; i<4; i++)
    {
        for (int j=0; j<16; j++)
        {
            AMBA_FLASH_PTR->ADDRESS = i*0x10000 + 4*j;
            AMBA_FLASH_PTR->DATA = 0xFFFFFFFF;
            AMBA_FLASH_PTR->LOCK = FLASH_LOCK_ACCESS_PASSWORD;
            AMBA_FLASH_PTR->COMMAND = 0x22;
            while (AMBA_FLASH_PTR->COMMAND & FLASH_STATUS_BUSY);
        }
    }
}

/**
 * @brief Initialize the CCNV1 board
 */
void board_init(void)
{

    /* Enable APB1 Bridge */
    AMBA_APB0_CFG_PTR->APB1_CFG = AMBA_APB1_EN;

    /* trim flash macros */
    flash_trim();

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

    /* Disable GPIO controller */
    AMBA_GPIO_PTR->CTRL &= ~GPIO_CTRL_EN;

    /* Configure Flash Controller */
    flash_configure(CORE_FREQ,(uint8_t)FLASH_READ_WAIT_STATES_CALC(CORE_FREQ),1,1);

    /* Configure PLL */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_PLL = CFGREG_COREFREQ_PLL_PLL_EN_MASK | (5 << CFGREG_COREFREQ_PLL_PLL_N_SHIFT) | CFGREG_COREFREQ_PLL_REF_SEL_MASK;
    while ((CFG_REGS_PTR->CFGREG_COREFREQ_STAT & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK) == 0);

    /* Switch to PLL */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_CLK = 2 << CFGREG_COREFREQ_CLK_CLK_CORE_SEL_SHIFT;

    /* switch debugger to new baud rate */
    CSR_CTRL_PTR->DBG_BAUD = DBG_UART_PRES((CORE_FREQ / DBG_BAUDRATE) / 16, (CORE_FREQ / DBG_BAUDRATE) % 16);

    /* Disable APB1 Bridge */
    AMBA_APB0_CFG_PTR->APB1_CFG &= ~AMBA_APB1_EN;

}

/**
 * @brief Initialize GNSS AFE
 */
void gnss_afe_init(void)
{

    /* Configure GNSSAFE1 */
    /* Configure PM */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PM_CONF  = CFGREG_PM_CONF_DEF | CFGREG_PM_CONF_BGVR_EN_MASK | CFGREG_PM_CONF_IREF_EN_MASK | CFGREG_PM_CONF_VREF_EN_MASK | CFGREG_PM_CONF_LDO_RF_EN_MASK | CFGREG_PM_CONF_LDO_APLL_EN_MASK | CFGREG_PM_CONF_LDO_DPLL_EN_MASK | CFGREG_PM_CONF_LDO_IF_EN_MASK | CFGREG_PM_CONF_LDO_ADC_EN_MASK | CFGREG_PM_CONF_IREF_TRIM_SRC_MASK | (15 << CFGREG_PM_CONF_IREF_TRIM_SHIFT) | CFGREG_PM_CONF_BGVR_TRIM_SRC_MASK | (15 << CFGREG_PM_CONF_BGVR_TRIM_SHIFT);
    while((CFG_REGS_PTR->CFGREG_PM_STAT & CFGREG_PM_STAT_PWR_UP_MASK) == 0) ;
    /* Configure LNA1 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_LNA15_CONF = CFGREG_LNA15_CONF_DEF | CFGREG_LNA15_CONF_EN_MASK | CFGREG_LNA15_CONF_EN_L1_MASK | CFGREG_LNA15_CONF_EN_L5_MASK;
    /* Configure MIXER_BALUN1 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_BALUN_MIXER1_CONF = CFGREG_BALUN_MIXER1_CONF_DEF | CFGREG_BALUN_MIXER1_CONF_BALUN_EN_MASK | CFGREG_BALUN_MIXER1_CONF_MIXER_EN_MASK;
    /* Configure PLL1 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL1TDC_CONF  = (0x205B << CFGREG_PLL1TDC_CONF_SCALE_SHIFT) | CFGREG_PLL1TDC_CONF_LOAD_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL1DCO_CONF  = (0 << CFGREG_PLL1DCO_CONF_AMP_SHIFT) | CFGREG_PLL1DCO_CONF_AMP_LOAD_MASK | (0 << CFGREG_PLL1DCO_CONF_CTRL_PVT_SHIFT) | (0x2000 << CFGREG_PLL1DCO_CONF_CTRL_FINE_SHIFT) | CFGREG_PLL1DCO_CONF_CTRL_LOAD_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL1_CONF  = (CFGREG_PLL1_CONF_DEF & (~CFGREG_PLL1_CONF_FCW_MASK)) | (0x600000 << CFGREG_PLL1_CONF_FCW_SHIFT) | CFGREG_PLL1_CONF_EN_MASK;
    /* Configure IF1 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_IF1_CONF  = CFGREG_IF1_CONF_DEF | CFGREG_IF1_CONF_EN_MASK | CFGREG_IF1_CONF_LPF_EN_MASK | (1 << CFGREG_IF1_CONF_LPF_BAND_SHIFT)  | CFGREG_IF1_CONF_PGA2_EN_MASK | CFGREG_IF1_CONF_PGA1_EN_MASK | CFGREG_IF1_CONF_PREAMP_EN_MASK | (0 << CFGREG_IF1_CONF_AGC_THR_SHIFT);
    /* Configure ADC1 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_ADC1_CONF  = (0 << CFGREG_ADC1_CONF_CLK_SEL_SHIFT) | CFGREG_ADC1_CONF_DEF | CFGREG_ADC1_CONF_SAH_EN_MASK | CFGREG_ADC1_CONF_ADC_EN_MASK;

    /* Configure GNSSAFE5 */
    /* Configure MIXER_BALUN5 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_BALUN_MIXER5_CONF  = CFGREG_BALUN_MIXER5_CONF_DEF | CFGREG_BALUN_MIXER5_CONF_BALUN_EN_MASK | CFGREG_BALUN_MIXER5_CONF_MIXER_EN_MASK;
    /* Configure PLL5 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL5TDC_CONF  = (0x1893 << CFGREG_PLL5TDC_CONF_SCALE_SHIFT) | CFGREG_PLL5TDC_CONF_LOAD_MASK;
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL5_CONF  = (CFGREG_PLL5_CONF_DEF & (~CFGREG_PLL5_CONF_FCW_MASK)) | (0x480000 << CFGREG_PLL5_CONF_FCW_SHIFT) | CFGREG_PLL5_CONF_EN_MASK;
    /* Configure IF5 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_IF5_CONF  = CFGREG_IF5_CONF_DEF | CFGREG_IF5_CONF_EN_MASK | CFGREG_IF5_CONF_LPF_EN_MASK | (2 << CFGREG_IF5_CONF_LPF_BAND_SHIFT) | CFGREG_IF5_CONF_PGA2_EN_MASK | CFGREG_IF5_CONF_PGA1_EN_MASK | CFGREG_IF5_CONF_PREAMP_EN_MASK | (0 << CFGREG_IF5_CONF_AGC_THR_SHIFT);
    /* Configure ADC5 */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_ADC5_CONF  = (0  << CFGREG_ADC5_CONF_CLK_SEL_SHIFT) | CFGREG_ADC5_CONF_DEF | CFGREG_ADC5_CONF_SAH_EN_MASK | CFGREG_ADC5_CONF_ADC_EN_MASK;

    /* Releas AFE reset */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PM_CONF |= CFGREG_PM_CONF_NRST_MASK;

}

/**
 * @brief Calibrate PLL1
 */
void gnss_pll1_calibrate(uint8_t *dco_pvt, uint8_t *dco_fine)
{
    int8_t ph_err = 1;
    uint32_t temp;
    int8_t dco_ctrl_pvt;

    // start PVT calibration
    for(uint16_t i = 0;i<32768;i=i+1) 
        temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;
    
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PM_CONF |= CFGREG_PM_CONF_NRST_MASK;

    for(dco_ctrl_pvt = 0;dco_ctrl_pvt < 16; dco_ctrl_pvt = dco_ctrl_pvt + 1)
    {
        temp = CFG_REGS_PTR->CFGREG_PLL1DCO_CONF;
        temp &= ~CFGREG_PLL1DCO_CONF_CTRL_PVT_MASK;
        temp |= (dco_ctrl_pvt << CFGREG_PLL1DCO_CONF_CTRL_PVT_SHIFT);
        CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
        CFG_REGS_PTR->CFGREG_PLL1DCO_CONF = temp;

        for(uint16_t i = 0;i<32768;i=i+1) 
            temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;;
        ph_err = 0;
        for(uint8_t i = 0;i<3;i=i+1)
        {
            temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;
            temp = temp & (1 << (19 + CFGREG_PLL1_STAT_PHERR_SHIFT));
            if(temp > 0)
                ph_err -= 1;
            else
                ph_err += 1;
            for(uint16_t i = 0;i<32768;i=i+1) 
                temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;
        }

        if((ph_err == 1) || (ph_err == -1))
            dco_ctrl_pvt -= 1;
        if(ph_err == -3)
            break;
    }

    // check if do not need to decrement PVT
    temp = CFG_REGS_PTR->CFGREG_PLL1DCO_CONF;
    temp &= ~CFGREG_PLL1DCO_CONF_CTRL_FINE_MASK;
    temp |= (0 << CFGREG_PLL1DCO_CONF_CTRL_FINE_SHIFT);
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_PLL1DCO_CONF = temp;

    for(uint16_t i = 0;i<32768;i=i+1) 
        temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;;
    ph_err = 0;
    while((ph_err == 3) || (ph_err == -3))
    {
        for(uint16_t i = 0;i<32768;i=i+1) 
            temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;;
        ph_err = 0;
        for(uint8_t i = 0;i<3;i=i+1)
        {
            temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;
            temp = temp & (1 << (19 + CFGREG_PLL1_STAT_PHERR_SHIFT));
            if(temp > 0)
                ph_err -= 1;
            else
                ph_err += 1;
            for(uint16_t i = 0;i<32768;i=i+1) 
                temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;
        }
    }
    if(ph_err == 3)
        dco_ctrl_pvt -= 1;

    // start fine calibration
    int8_t dco_ctrl_fine;
    for(dco_ctrl_fine = 0;dco_ctrl_fine < 64; dco_ctrl_fine = dco_ctrl_fine + 1)
    {
        temp = CFG_REGS_PTR->CFGREG_PLL1DCO_CONF;
        temp &= ~CFGREG_PLL1DCO_CONF_CTRL_FINE_MASK;
        temp |= (dco_ctrl_fine << (CFGREG_PLL1DCO_CONF_CTRL_FINE_SHIFT+8));
        CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
        CFG_REGS_PTR->CFGREG_PLL1DCO_CONF = temp;

        for(uint16_t i = 0;i<32768;i=i+1) 
            temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;;
        ph_err = 0;
        for(uint8_t i = 0;i<3;i=i+1)
        {
            temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;
            temp = temp & (1 << (19 + CFGREG_PLL1_STAT_PHERR_SHIFT));
            if(temp > 0)
                ph_err -= 1;
            else
                ph_err += 1;
            for(uint16_t i = 0;i<32768;i=i+1) 
                temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;
        }

         if((ph_err == 1) || (ph_err == -1))
            dco_ctrl_fine -= 1;
        if(ph_err == -3)
            break;
    }

    *dco_pvt = (uint8_t) dco_ctrl_pvt;
    *dco_fine = (uint8_t) dco_ctrl_fine;
}

/**
 * @brief PLL1 control loop
 */
void gnss_pll1_loop(uint8_t dco_pvt, uint8_t dco_fine)
{
    uint16_t dco_ctrl_fine;

    uint32_t freq_counter;
    uint16_t acc = 0;
    int32_t temp;
    dco_ctrl_fine  = dco_fine;
    freq_counter = (dco_ctrl_fine << 20) + (1<<19);

    // start loop
    while(1)
    {
        temp = CFG_REGS_PTR->CFGREG_PLL1_STAT;
        temp = temp & (1 << (19 + CFGREG_PLL1_STAT_PHERR_SHIFT));

        acc = acc + ((freq_counter >>  12) % (1 << 8));

        if(temp > 0)
        {
            freq_counter -= 1;
            dco_ctrl_fine = (freq_counter >> 20) - 0;
        }
        else
        {
            freq_counter += 1;
            dco_ctrl_fine = (freq_counter >> 20) + 1;
        }

        if(acc >= (1<<8))
        {
            acc -= (1<<8);
            dco_ctrl_fine += 1;
        }
        else
        {
            dco_ctrl_fine -= 0;
        }

        CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
        CFG_REGS_PTR->CFGREG_PLL1DCO_CONF = CFGREG_PLL1DCO_CONF_CTRL_LOAD_MASK | CFGREG_PLL1DCO_CONF_AMP_LOAD_MASK | (dco_ctrl_fine << (CFGREG_PLL1DCO_CONF_CTRL_FINE_SHIFT + 8)) | (dco_pvt << CFGREG_PLL1DCO_CONF_CTRL_PVT_SHIFT);

    }
}

/**
 * @brief PLL1 control loop
 */
void gnss_pll1_maintanance(void)
{
    uint8_t dco_pvt;
    uint8_t dco_fine;
    while(1)
    {
        gnss_pll1_calibrate(&dco_pvt, &dco_fine);
        gnss_pll1_loop(dco_pvt, dco_fine);
    }
}

/**
 * @brief Initialize hyperbus
 */
void hyperbus_configure(void)
{

    uint32_t data;

    /* Enable GPIO controller */
    AMBA_GPIO_PTR->CTRL |= GPIO_CTRL_EN;

    /* Enable APB1 Bridge */
    AMBA_APB0_CFG_PTR->APB1_CFG = AMBA_APB1_EN;

    /* Set Hyperbus pins */
    for (int i=16; i<29; i++){
        AMBA_GPIO_PTR->ALTER_HI  |= GPIO_CONFIG_MASK(i,GPIO_ALTER_0);
        AMBA_GPIO_PTR->DRIVER_HI |= GPIO_CONFIG_MASK(i,GPIO_DRIVE_1);
        AMBA_GPIO_PTR->SLEW_RATE |= 1<<i;
    }

    AMBA_MEMCTRL_PTR->DEVICE_ADDR_LO[0] = ROM_EXT_BASE;
    AMBA_MEMCTRL_PTR->DEVICE_ADDR_HI[0] = ROM_EXT_BASE + 0x4000000 - 1;
    AMBA_MEMCTRL_PTR->DEVICE_ADDR_LO[1] = RAM_EXT_BASE;
    AMBA_MEMCTRL_PTR->DEVICE_ADDR_HI[1] = RAM_EXT_BASE + 0x0800000 - 1;

    AMBA_MEMCTRL_PTR->DEVICE_CONF[1] = MEMCTRL_DEVICE_CONF_EN | MEMCTRL_BUILD_LATENCY(6);

    AMBA_MEMCTRL_PTR->CONF = MEMCTRL_CONF_CKPAD_EN | MEMCTRL_CONF_CSPAD_EN | MEMCTRL_CONF_CKMST_EN | MEMCTRL_BUILD_PRESCALER(1);

                                      // read             register space   linear burst     conf0
    AMBA_MEMCTRL_PTR->COMMAND_DATA[1] = (1 << (47-16)) | (1 << (46-16)) | (1 << (45-16)) | (1 << (24-16));
    AMBA_MEMCTRL_PTR->COMMAND_DATA[0] = 0;

    // set CS
    AMBA_MEMCTRL_PTR->CONF |= 2 | (1<<8);
    // issue read command
    AMBA_MEMCTRL_PTR->COMMAND = 1;
    // wait for busy
    while (AMBA_MEMCTRL_PTR->STATUS & 1);
    // clear CS
    AMBA_MEMCTRL_PTR->CONF &= ~(2 | (1<<8));

    data = AMBA_MEMCTRL_PTR->STATUS >> 16;
    //printf("Config reg 0 = 0x%x\n",(unsigned int)data);

                                      // register space   linear burst     conf0
    AMBA_MEMCTRL_PTR->COMMAND_DATA[1] = (1 << (46-16)) | (1 << (45-16)) | (1 << (24-16));
    // defaults + 3 cycle latency
    data &= ~(0xF << 4);
    data |= 0xE << 4;
    AMBA_MEMCTRL_PTR->COMMAND_DATA[0] = data;

    // set CS
    AMBA_MEMCTRL_PTR->CONF |= 2 | (1<<8);
    // issue zero delay write
    AMBA_MEMCTRL_PTR->COMMAND = 4;
    // wait for busy
    while (AMBA_MEMCTRL_PTR->STATUS & 1);
    // clear CS
    AMBA_MEMCTRL_PTR->CONF &= ~(2 | (1<<8));

    // set new latency
    AMBA_MEMCTRL_PTR->DEVICE_CONF[1] = MEMCTRL_DEVICE_CONF_EN | MEMCTRL_BUILD_LATENCY(3);

}
