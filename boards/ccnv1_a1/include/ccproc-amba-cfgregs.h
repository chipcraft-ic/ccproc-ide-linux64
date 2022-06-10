/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2022-01-10 10:09:36 +0100 (pon, 10 sty 2022) $
* $Revision: 808 $
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

/**
 * @brief           CC Processor AMBA cfg_regs definitions
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CFG_REGS_H
#define __CFG_REGS_H

#include <stdint.h>

/************************//**
 * @defgroup cfg_regs CFG_REGS Controller
 * cfg_regs registers and definitions
 * @{
 *//************************/

/** @brief cfg_regs Registers */
typedef struct
{
    uint32_t CFGREG_IRQMAP;
    uint32_t CFGREG_UNLOCK;
    uint32_t CFGREG_IRQFLAGS;
    uint32_t CFGREG_RTCSTAT;
    uint32_t CFGREG_RTCCONF;
    uint32_t CFGREG_COREFREQ_CLK;
    uint32_t CFGREG_COREFREQ_PLL;
    uint32_t CFGREG_COREFREQ_STAT;
    uint32_t CFGREG_GNSSAFE_CONF;
    uint32_t CFGREG_PM_CONF;
    uint32_t CFGREG_PM_GNSSAFE1_CONF;
    uint32_t CFGREG_PM_GNSSAFE5_CONF;
    uint32_t CFGREG_DCDC_CONF;
    uint32_t CFGREG_LNA1_CONF;
    uint32_t CFGREG_BALUN_MIXER1_CONF;
    uint32_t CFGREG_LNA5_CONF;
    uint32_t CFGREG_BALUN_MIXER5_CONF;
    uint32_t CFGREG_LNA15_TUNE_CONF;
    uint32_t CFGREG_LNA15_CONF;
    uint32_t CFGREG_PROBE_IF1_CONF;
    uint32_t CFGREG_PROBE_IF5_CONF;
    uint32_t CFGREG_PLL1_CONF;
    uint32_t CFGREG_PLL1TDC_CONF;
    uint32_t CFGREG_PLL1DCO_CONF;
    uint32_t CFGREG_PLL1_STAT;
    uint32_t CFGREG_PLL1TDC_STAT;
    uint32_t CFGREG_PLL1DCO_STAT;
    uint32_t CFGREG_IF1_CONF;
    uint32_t CFGREG_IF1_STAT;
    uint32_t CFGREG_ADC1_CONF;
    uint32_t CFGREG_PLL5_CONF;
    uint32_t CFGREG_PLL5TDC_CONF;
    uint32_t CFGREG_PLL5DCO_CONF;
    uint32_t CFGREG_PLL5_STAT;
    uint32_t CFGREG_PLL5TDC_STAT;
    uint32_t CFGREG_PLL5DCO_STAT;
    uint32_t CFGREG_IF5_CONF;
    uint32_t CFGREG_IF5_STAT;
    uint32_t CFGREG_ADC5_CONF;
} cfg_regs_t;

static volatile cfg_regs_t * const CFG_REGS_PTR = (cfg_regs_t*)AMBA_REG_BASE;


/** Registers Default Values */
enum
{
     CFGREG_IRQMAP_DEF                                            = 0x00000000,  /*!<  Interrupt Mapping Register Default Value */
     CFGREG_UNLOCK_DEF                                            = 0x0000A55A,  /*!<  Unlock Register Default Value */
     CFGREG_IRQFLAGS_DEF                                          = 0x00000000,  /*!<  32kHz RTC Clock Interrupt Flags Default Value */
     CFGREG_RTCSTAT_DEF                                           = 0x00000000,  /*!<  32kHz RTC Clock Status Default Value */
     CFGREG_RTCCONF_DEF                                           = 0x00000000,  /*!<  32kHz RTC Clock Configuration Default Value */
     CFGREG_COREFREQ_CLK_DEF                                      = 0x00000002,  /*!<  External XTAL Configuration Register Default Value */
     CFGREG_COREFREQ_PLL_DEF                                      = 0x00000080,  /*!<  PLL Configuration Register Default Value */
     CFGREG_COREFREQ_STAT_DEF                                     = 0x00000000,  /*!<  Core Clock Status Register Default Value */
     CFGREG_GNSSAFE_CONF_DEF                                      = 0x00000000,  /*!<  GNSS-AFE Configuration Register Default Value */
     CFGREG_PM_CONF_DEF                                           = 0x00000010,  /*!<  PM GLOBAL Configuration Register Default Value */
     CFGREG_PM_GNSSAFE1_CONF_DEF                                  = 0x006DB6DB,  /*!<  PM GNSS-AFE1 Configuration Register Default Value */
     CFGREG_PM_GNSSAFE5_CONF_DEF                                  = 0x006DB6DB,  /*!<  PM GNSS-AFE5 Configuration Register Default Value */
     CFGREG_DCDC_CONF_DEF                                         = 0x0000000E,  /*!<  DCDC Configuration Register Default Value */
     CFGREG_LNA1_CONF_DEF                                         = 0x0000000C,  /*!<  LNA1 Configuration Register Default Value */
     CFGREG_BALUN_MIXER1_CONF_DEF                                 = 0x00000018,  /*!<  BALUN and MIXER 1 Configuration Register Default Value */
     CFGREG_LNA5_CONF_DEF                                         = 0x0000000C,  /*!<  LNA5 Configuration Register Default Value */
     CFGREG_BALUN_MIXER5_CONF_DEF                                 = 0x00000018,  /*!<  BALUN and MIXER 5 Configuration Register Default Value */
     CFGREG_LNA15_TUNE_CONF_DEF                                   = 0x00000000,  /*!<  LNA15 Tuning Configuration Register Default Value */
     CFGREG_LNA15_CONF_DEF                                        = 0x00000000,  /*!<  LNA15 Configuration Register Default Value */
     CFGREG_PROBE_IF1_CONF_DEF                                    = 0x00000000,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Default Value */
     CFGREG_PROBE_IF5_CONF_DEF                                    = 0x00000000,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Default Value */
     CFGREG_PLL1_CONF_DEF                                         = 0x00C46A7E,  /*!<  PLL1 Configuration Register Default Value */
     CFGREG_PLL1TDC_CONF_DEF                                      = 0x00002000,  /*!<  PLL1 TDC Configuration Register Default Value */
     CFGREG_PLL1DCO_CONF_DEF                                      = 0x00104000,  /*!<  PLL1 DCO Configuration Register Default Value */
     CFGREG_PLL1_STAT_DEF                                         = 0x00000000,  /*!<  PLL1 Status Register Default Value */
     CFGREG_PLL1TDC_STAT_DEF                                      = 0x00000000,  /*!<  PLL1 TDC Status Register Default Value */
     CFGREG_PLL1DCO_STAT_DEF                                      = 0x00000000,  /*!<  PLL1 TDC Status Register Default Value */
     CFGREG_IF1_CONF_DEF                                          = 0x00010120,  /*!<  IF1 Configuration Register Default Value */
     CFGREG_IF1_STAT_DEF                                          = 0x00000000,  /*!<  IF1 Status Register Default Value */
     CFGREG_ADC1_CONF_DEF                                         = 0x00000000,  /*!<  ADC1 Configuration Register Default Value */
     CFGREG_PLL5_CONF_DEF                                         = 0x00C46A7E,  /*!<  PLL5 Configuration Register Default Value */
     CFGREG_PLL5TDC_CONF_DEF                                      = 0x00002000,  /*!<  PLL5 TDC Configuration Register Default Value */
     CFGREG_PLL5DCO_CONF_DEF                                      = 0x00104000,  /*!<  PLL5 DCO Configuration Register Default Value */
     CFGREG_PLL5_STAT_DEF                                         = 0x00000000,  /*!<  PLL5 Status Register Default Value */
     CFGREG_PLL5TDC_STAT_DEF                                      = 0x00000000,  /*!<  PLL5 TDC Status Register Default Value */
     CFGREG_PLL5DCO_STAT_DEF                                      = 0x00000000,  /*!<  PLL5 TDC Status Register Default Value */
     CFGREG_IF5_CONF_DEF                                          = 0x00010120,  /*!<  IF5 Configuration Register Default Value */
     CFGREG_IF5_STAT_DEF                                          = 0x00000000,  /*!<  IF5 status Register Default Value */
     CFGREG_ADC5_CONF_DEF                                         = 0x00000000,  /*!<  ADC5 Configuration Register Default Value */
};

/** Registers Masks */
enum
{

     CFGREG_IRQMAP_IRQMAP_MASK                                    = 0x0000FFFE,  /*!<  Interrupt Mapping Register Mask Value */

     CFGREG_UNLOCK_UNLOCK_KEY_MASK                                = 0x0000FFFF,  /*!<  Unlock Register Mask Value */

     CFGREG_IRQFLAGS_PLL_FAIL_MASK                                = 0x00000004,  /*!<  32kHz RTC Clock Interrupt Flags Mask Value */
     CFGREG_IRQFLAGS_XTAL_CORE_FAIL_MASK                          = 0x00000002,  /*!<  32kHz RTC Clock Interrupt Flags Mask Value */
     CFGREG_IRQFLAGS_XTAL_RTC_FAIL_MASK                           = 0x00000001,  /*!<  32kHz RTC Clock Interrupt Flags Mask Value */

     CFGREG_RTCSTAT_RC_RTC_VAL_MASK                               = 0x000001FC,  /*!<  32kHz RTC Clock Status Mask Value */
     CFGREG_RTCSTAT_RC_RTC_RDY_MASK                               = 0x00000002,  /*!<  32kHz RTC Clock Status Mask Value */
     CFGREG_RTCSTAT_CLK_RTC_SEL_MASK                              = 0x00000001,  /*!<  32kHz RTC Clock Status Mask Value */

     CFGREG_RTCCONF_RC_RTC_CAL_MASK                               = 0x00000004,  /*!<  32kHz RTC Clock Configuration Mask Value */
     CFGREG_RTCCONF_XTAL_RTC_SEL_MASK                             = 0x00000002,  /*!<  32kHz RTC Clock Configuration Mask Value */
     CFGREG_RTCCONF_XTAL_RTC_TEST_MASK                            = 0x00000001,  /*!<  32kHz RTC Clock Configuration Mask Value */

     CFGREG_COREFREQ_CLK_TEST_OUT_EN_MASK                         = 0x00000010,  /*!<  External XTAL Configuration Register Mask Value */
     CFGREG_COREFREQ_CLK_RC_CORE_CAL_MASK                         = 0x00000008,  /*!<  External XTAL Configuration Register Mask Value */
     CFGREG_COREFREQ_CLK_CLK_CORE_SEL_MASK                        = 0x00000006,  /*!<  External XTAL Configuration Register Mask Value */
     CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_MASK                      = 0x00000001,  /*!<  External XTAL Configuration Register Mask Value */

     CFGREG_COREFREQ_PLL_PLL_VFB_EN_MASK                          = 0x00001000,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_PLL_VCONT_SF_MASK                        = 0x00000800,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_PLL_VCONT_EN_MASK                        = 0x00000400,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_PLL_TEST_MASK                            = 0x00000200,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_PLL_N_MASK                               = 0x000001F0,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_PLL_M_MASK                               = 0x0000000C,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_REF_SEL_MASK                             = 0x00000002,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_PLL_EN_MASK                              = 0x00000001,  /*!<  PLL Configuration Register Mask Value */

     CFGREG_COREFREQ_STAT_RC_CORE_VAL_MASK                        = 0x000007E0,  /*!<  Core Clock Status Register Mask Value */
     CFGREG_COREFREQ_STAT_RC_CORE_RDY_MASK                        = 0x00000010,  /*!<  Core Clock Status Register Mask Value */
     CFGREG_COREFREQ_STAT_PLL_LOCK_MASK                           = 0x00000008,  /*!<  Core Clock Status Register Mask Value */
     CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_MASK                     = 0x00000004,  /*!<  Core Clock Status Register Mask Value */
     CFGREG_COREFREQ_STAT_CLK_CORE_SEL_MASK                       = 0x00000003,  /*!<  Core Clock Status Register Mask Value */

     CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_MASK                        = 0x00000002,  /*!<  GNSS-AFE Configuration Register Mask Value */
     CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_MASK                       = 0x00000001,  /*!<  GNSS-AFE Configuration Register Mask Value */

     CFGREG_PM_CONF_PM_ITRIM_MASK                                 = 0x0000001E,  /*!<  PM GLOBAL Configuration Register Mask Value */
     CFGREG_PM_CONF_PM_EN_MASK                                    = 0x00000001,  /*!<  PM GLOBAL Configuration Register Mask Value */

     CFGREG_PM_GNSSAFE1_CONF_IREG_SPARE1_MASK                     = 0x00E00000,  /*!<  PM GNSS-AFE1 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_TEST_MASK                       = 0x001C0000,  /*!<  PM GNSS-AFE1 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_PLL1_MASK                       = 0x00038000,  /*!<  PM GNSS-AFE1 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_ADC1_MASK                       = 0x00007000,  /*!<  PM GNSS-AFE1 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_IF1_MASK                        = 0x00000E00,  /*!<  PM GNSS-AFE1 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_MIXER1_MASK                     = 0x000001C0,  /*!<  PM GNSS-AFE1 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_BALUN1_MASK                     = 0x00000038,  /*!<  PM GNSS-AFE1 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_LNA1_MASK                       = 0x00000007,  /*!<  PM GNSS-AFE1 Configuration Register Mask Value */

     CFGREG_PM_GNSSAFE5_CONF_IREG_SPARE5_MASK                     = 0x00E00000,  /*!<  PM GNSS-AFE5 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_LNA15_MASK                      = 0x001C0000,  /*!<  PM GNSS-AFE5 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_PLL5_MASK                       = 0x00038000,  /*!<  PM GNSS-AFE5 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_ADC5_MASK                       = 0x00007000,  /*!<  PM GNSS-AFE5 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_IF5_MASK                        = 0x00000E00,  /*!<  PM GNSS-AFE5 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_MIXER5_MASK                     = 0x000001C0,  /*!<  PM GNSS-AFE5 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_BALUN5_MASK                     = 0x00000038,  /*!<  PM GNSS-AFE5 Configuration Register Mask Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_LNA5_MASK                       = 0x00000007,  /*!<  PM GNSS-AFE5 Configuration Register Mask Value */

     CFGREG_DCDC_CONF_DCDC_TRIM_MASK                              = 0x0000001E,  /*!<  DCDC Configuration Register Mask Value */
     CFGREG_DCDC_CONF_DCDC_EN_MASK                                = 0x00000001,  /*!<  DCDC Configuration Register Mask Value */

     CFGREG_LNA1_CONF_LNA_TUNE_MASK                               = 0x0001FFFE,  /*!<  LNA1 Configuration Register Mask Value */
     CFGREG_LNA1_CONF_EN_MASK                                     = 0x00000001,  /*!<  LNA1 Configuration Register Mask Value */

     CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_MASK                     = 0x0003FFFC,  /*!<  BALUN and MIXER 1 Configuration Register Mask Value */
     CFGREG_BALUN_MIXER1_CONF_BALUN_EN_MASK                       = 0x00000002,  /*!<  BALUN and MIXER 1 Configuration Register Mask Value */
     CFGREG_BALUN_MIXER1_CONF_MIXER_EN_MASK                       = 0x00000001,  /*!<  BALUN and MIXER 1 Configuration Register Mask Value */

     CFGREG_LNA5_CONF_LNA_TUNE_MASK                               = 0x0001FFFE,  /*!<  LNA5 Configuration Register Mask Value */
     CFGREG_LNA5_CONF_EN_MASK                                     = 0x00000001,  /*!<  LNA5 Configuration Register Mask Value */

     CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_MASK                     = 0x0003FFFC,  /*!<  BALUN and MIXER 5 Configuration Register Mask Value */
     CFGREG_BALUN_MIXER5_CONF_BALUN_EN_MASK                       = 0x00000002,  /*!<  BALUN and MIXER 5 Configuration Register Mask Value */
     CFGREG_BALUN_MIXER5_CONF_MIXER_EN_MASK                       = 0x00000001,  /*!<  BALUN and MIXER 5 Configuration Register Mask Value */

     CFGREG_LNA15_TUNE_CONF_BAND5_TUNE_MASK                       = 0xFFFF0000,  /*!<  LNA15 Tuning Configuration Register Mask Value */
     CFGREG_LNA15_TUNE_CONF_BAND1_TUNE_MASK                       = 0x0000FFFF,  /*!<  LNA15 Tuning Configuration Register Mask Value */

     CFGREG_LNA15_CONF_SPARE_TUNE_MASK                            = 0x0001FFFE,  /*!<  LNA15 Configuration Register Mask Value */
     CFGREG_LNA15_CONF_EN_MASK                                    = 0x00000001,  /*!<  LNA15 Configuration Register Mask Value */

     CFGREG_PROBE_IF1_CONF_PROBEB_SELECT_MASK                     = 0x000000C0,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF1_CONF_PROBEB_SOURCE_MASK                     = 0x00000020,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF1_CONF_PROBEB_EN_MASK                         = 0x00000010,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF1_CONF_PROBEA_SELECT_MASK                     = 0x0000000C,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF1_CONF_PROBEA_SOURCE_MASK                     = 0x00000002,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF1_CONF_PROBEA_EN_MASK                         = 0x00000001,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */

     CFGREG_PROBE_IF5_CONF_NRST_TEST_MASK                         = 0x00000800,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF5_CONF_PLL15FB_SEL_MASK                       = 0x00000400,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF5_CONF_PLL_VCONT_EN_MASK                      = 0x00000200,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF5_CONF_IBIAS_TEST_EN_MASK                     = 0x00000100,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF5_CONF_PROBEB_SELECT_MASK                     = 0x000000C0,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF5_CONF_PROBEB_SOURCE_MASK                     = 0x00000020,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF5_CONF_PROBEB_EN_MASK                         = 0x00000010,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF5_CONF_PROBEA_SELECT_MASK                     = 0x0000000C,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF5_CONF_PROBEA_SOURCE_MASK                     = 0x00000002,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_IF5_CONF_PROBEA_EN_MASK                         = 0x00000001,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Mask Value */

     CFGREG_PLL1_CONF_TEST_EN_MASK                                = 0x02000000,  /*!<  PLL1 Configuration Register Mask Value */
     CFGREG_PLL1_CONF_FCW_MASK                                    = 0x01FFFFFE,  /*!<  PLL1 Configuration Register Mask Value */
     CFGREG_PLL1_CONF_EN_MASK                                     = 0x00000001,  /*!<  PLL1 Configuration Register Mask Value */

     CFGREG_PLL1TDC_CONF_SCALE_MASK                               = 0x0000FFFE,  /*!<  PLL1 TDC Configuration Register Mask Value */
     CFGREG_PLL1TDC_CONF_LOAD_MASK                                = 0x00000001,  /*!<  PLL1 TDC Configuration Register Mask Value */

     CFGREG_PLL1DCO_CONF_CTRL_PVT_MASK                            = 0x001F0000,  /*!<  PLL1 DCO Configuration Register Mask Value */
     CFGREG_PLL1DCO_CONF_CTRL_FINE_MASK                           = 0x00007FFE,  /*!<  PLL1 DCO Configuration Register Mask Value */
     CFGREG_PLL1DCO_CONF_CTRL_LOAD_MASK                           = 0x00000001,  /*!<  PLL1 DCO Configuration Register Mask Value */

     CFGREG_PLL1_STAT_PHERR_MASK                                  = 0x3FFFFC00,  /*!<  PLL1 Status Register Mask Value */
     CFGREG_PLL1_STAT_NDIV_MASK                                   = 0x000003FC,  /*!<  PLL1 Status Register Mask Value */
     CFGREG_PLL1_STAT_PHSEL_MASK                                  = 0x00000002,  /*!<  PLL1 Status Register Mask Value */
     CFGREG_PLL1_STAT_LOCK_MASK                                   = 0x00000001,  /*!<  PLL1 Status Register Mask Value */

     CFGREG_PLL1TDC_STAT_SCALE_MASK                               = 0x00007FFF,  /*!<  PLL1 TDC Status Register Mask Value */

     CFGREG_PLL1DCO_STAT_CTRL_PVT_MASK                            = 0x0007C000,  /*!<  PLL1 TDC Status Register Mask Value */
     CFGREG_PLL1DCO_STAT_CTRL_FINE_MASK                           = 0x00003FFF,  /*!<  PLL1 TDC Status Register Mask Value */

     CFGREG_IF1_CONF_LPF_CAL_MASK                                 = 0x0001C000,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_LPF_GAIN_MASK                                = 0x00003000,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_LPF_BAND_MASK                                = 0x00000C00,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_LPF_EN_MASK                                  = 0x00000200,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PGA2_GAIN_MASK                               = 0x00000180,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PGA2_EN_MASK                                 = 0x00000040,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PGA1_GAIN_MASK                               = 0x00000030,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PGA1_EN_MASK                                 = 0x00000008,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PREAMP_EN_MASK                               = 0x00000004,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_LOAD_EN_MASK                                 = 0x00000002,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_EN_MASK                                      = 0x00000001,  /*!<  IF1 Configuration Register Mask Value */

     CFGREG_IF1_STAT_AGC_CTRL_MASK                                = 0x0000003F,  /*!<  IF1 Status Register Mask Value */

     CFGREG_ADC1_CONF_CLK_CONF_MASK                               = 0x0000000C,  /*!<  ADC1 Configuration Register Mask Value */
     CFGREG_ADC1_CONF_SAH_EN_MASK                                 = 0x00000002,  /*!<  ADC1 Configuration Register Mask Value */
     CFGREG_ADC1_CONF_ADC_EN_MASK                                 = 0x00000001,  /*!<  ADC1 Configuration Register Mask Value */

     CFGREG_PLL5_CONF_TEST_EN_MASK                                = 0x02000000,  /*!<  PLL5 Configuration Register Mask Value */
     CFGREG_PLL5_CONF_FCW_MASK                                    = 0x01FFFFFE,  /*!<  PLL5 Configuration Register Mask Value */
     CFGREG_PLL5_CONF_EN_MASK                                     = 0x00000001,  /*!<  PLL5 Configuration Register Mask Value */

     CFGREG_PLL5TDC_CONF_SCALE_MASK                               = 0x0000FFFE,  /*!<  PLL5 TDC Configuration Register Mask Value */
     CFGREG_PLL5TDC_CONF_LOAD_MASK                                = 0x00000001,  /*!<  PLL5 TDC Configuration Register Mask Value */

     CFGREG_PLL5DCO_CONF_CTRL_PVT_MASK                            = 0x001F0000,  /*!<  PLL5 DCO Configuration Register Mask Value */
     CFGREG_PLL5DCO_CONF_CTRL_FINE_MASK                           = 0x00007FFE,  /*!<  PLL5 DCO Configuration Register Mask Value */
     CFGREG_PLL5DCO_CONF_CTRL_LOAD_MASK                           = 0x00000001,  /*!<  PLL5 DCO Configuration Register Mask Value */

     CFGREG_PLL5_STAT_PHERR_MASK                                  = 0x3FFFFC00,  /*!<  PLL5 Status Register Mask Value */
     CFGREG_PLL5_STAT_NDIV_MASK                                   = 0x000003FC,  /*!<  PLL5 Status Register Mask Value */
     CFGREG_PLL5_STAT_PHSEL_MASK                                  = 0x00000002,  /*!<  PLL5 Status Register Mask Value */
     CFGREG_PLL5_STAT_LOCK_MASK                                   = 0x00000001,  /*!<  PLL5 Status Register Mask Value */

     CFGREG_PLL5TDC_STAT_SCALE_MASK                               = 0x00007FFF,  /*!<  PLL5 TDC Status Register Mask Value */

     CFGREG_PLL5DCO_STAT_CTRL_PVT_MASK                            = 0x0007C000,  /*!<  PLL5 TDC Status Register Mask Value */
     CFGREG_PLL5DCO_STAT_CTRL_FINE_MASK                           = 0x00003FFF,  /*!<  PLL5 TDC Status Register Mask Value */

     CFGREG_IF5_CONF_LPF_CAL_MASK                                 = 0x0001C000,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_LPF_GAIN_MASK                                = 0x00003000,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_LPF_BAND_MASK                                = 0x00000C00,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_LPF_EN_MASK                                  = 0x00000200,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PGA2_GAIN_MASK                               = 0x00000180,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PGA2_EN_MASK                                 = 0x00000040,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PGA1_GAIN_MASK                               = 0x00000030,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PGA1_EN_MASK                                 = 0x00000008,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PREAMP_EN_MASK                               = 0x00000004,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_LOAD_EN_MASK                                 = 0x00000002,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_EN_MASK                                      = 0x00000001,  /*!<  IF5 Configuration Register Mask Value */

     CFGREG_IF5_STAT_AGC_CTRL_MASK                                = 0x0000003F,  /*!<  IF5 status Register Mask Value */

     CFGREG_ADC5_CONF_CLK_CONF_MASK                               = 0x0000000C,  /*!<  ADC5 Configuration Register Mask Value */
     CFGREG_ADC5_CONF_SAH_EN_MASK                                 = 0x00000002,  /*!<  ADC5 Configuration Register Mask Value */
     CFGREG_ADC5_CONF_ADC_EN_MASK                                 = 0x00000001,  /*!<  ADC5 Configuration Register Mask Value */

};

/** Registers Shifts */
enum
{

     CFGREG_IRQMAP_IRQMAP_SHIFT                                   =  1,  /*!<  Interrupt Mapping Register Shift Value */

     CFGREG_UNLOCK_UNLOCK_KEY_SHIFT                               =  0,  /*!<  Unlock Register Shift Value */

     CFGREG_IRQFLAGS_PLL_FAIL_SHIFT                               =  2,  /*!<  32kHz RTC Clock Interrupt Flags Shift Value */
     CFGREG_IRQFLAGS_XTAL_CORE_FAIL_SHIFT                         =  1,  /*!<  32kHz RTC Clock Interrupt Flags Shift Value */
     CFGREG_IRQFLAGS_XTAL_RTC_FAIL_SHIFT                          =  0,  /*!<  32kHz RTC Clock Interrupt Flags Shift Value */

     CFGREG_RTCSTAT_RC_RTC_VAL_SHIFT                              =  2,  /*!<  32kHz RTC Clock Status Shift Value */
     CFGREG_RTCSTAT_RC_RTC_RDY_SHIFT                              =  1,  /*!<  32kHz RTC Clock Status Shift Value */
     CFGREG_RTCSTAT_CLK_RTC_SEL_SHIFT                             =  0,  /*!<  32kHz RTC Clock Status Shift Value */

     CFGREG_RTCCONF_RC_RTC_CAL_SHIFT                              =  2,  /*!<  32kHz RTC Clock Configuration Shift Value */
     CFGREG_RTCCONF_XTAL_RTC_SEL_SHIFT                            =  1,  /*!<  32kHz RTC Clock Configuration Shift Value */
     CFGREG_RTCCONF_XTAL_RTC_TEST_SHIFT                           =  0,  /*!<  32kHz RTC Clock Configuration Shift Value */

     CFGREG_COREFREQ_CLK_TEST_OUT_EN_SHIFT                        =  4,  /*!<  External XTAL Configuration Register Shift Value */
     CFGREG_COREFREQ_CLK_RC_CORE_CAL_SHIFT                        =  3,  /*!<  External XTAL Configuration Register Shift Value */
     CFGREG_COREFREQ_CLK_CLK_CORE_SEL_SHIFT                       =  1,  /*!<  External XTAL Configuration Register Shift Value */
     CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_SHIFT                     =  0,  /*!<  External XTAL Configuration Register Shift Value */

     CFGREG_COREFREQ_PLL_PLL_VFB_EN_SHIFT                         = 12,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_PLL_VCONT_SF_SHIFT                       = 11,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_PLL_VCONT_EN_SHIFT                       = 10,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_PLL_TEST_SHIFT                           =  9,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_PLL_N_SHIFT                              =  4,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_PLL_M_SHIFT                              =  2,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_REF_SEL_SHIFT                            =  1,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_PLL_EN_SHIFT                             =  0,  /*!<  PLL Configuration Register Shift Value */

     CFGREG_COREFREQ_STAT_RC_CORE_VAL_SHIFT                       =  5,  /*!<  Core Clock Status Register Shift Value */
     CFGREG_COREFREQ_STAT_RC_CORE_RDY_SHIFT                       =  4,  /*!<  Core Clock Status Register Shift Value */
     CFGREG_COREFREQ_STAT_PLL_LOCK_SHIFT                          =  3,  /*!<  Core Clock Status Register Shift Value */
     CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_SHIFT                    =  2,  /*!<  Core Clock Status Register Shift Value */
     CFGREG_COREFREQ_STAT_CLK_CORE_SEL_SHIFT                      =  0,  /*!<  Core Clock Status Register Shift Value */

     CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_SHIFT                       =  1,  /*!<  GNSS-AFE Configuration Register Shift Value */
     CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_SHIFT                      =  0,  /*!<  GNSS-AFE Configuration Register Shift Value */

     CFGREG_PM_CONF_PM_ITRIM_SHIFT                                =  1,  /*!<  PM GLOBAL Configuration Register Shift Value */
     CFGREG_PM_CONF_PM_EN_SHIFT                                   =  0,  /*!<  PM GLOBAL Configuration Register Shift Value */

     CFGREG_PM_GNSSAFE1_CONF_IREG_SPARE1_SHIFT                    = 21,  /*!<  PM GNSS-AFE1 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_TEST_SHIFT                      = 18,  /*!<  PM GNSS-AFE1 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_PLL1_SHIFT                      = 15,  /*!<  PM GNSS-AFE1 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_ADC1_SHIFT                      = 12,  /*!<  PM GNSS-AFE1 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_IF1_SHIFT                       =  9,  /*!<  PM GNSS-AFE1 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_MIXER1_SHIFT                    =  6,  /*!<  PM GNSS-AFE1 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_BALUN1_SHIFT                    =  3,  /*!<  PM GNSS-AFE1 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE1_CONF_IREG_LNA1_SHIFT                      =  0,  /*!<  PM GNSS-AFE1 Configuration Register Shift Value */

     CFGREG_PM_GNSSAFE5_CONF_IREG_SPARE5_SHIFT                    = 21,  /*!<  PM GNSS-AFE5 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_LNA15_SHIFT                     = 18,  /*!<  PM GNSS-AFE5 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_PLL5_SHIFT                      = 15,  /*!<  PM GNSS-AFE5 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_ADC5_SHIFT                      = 12,  /*!<  PM GNSS-AFE5 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_IF5_SHIFT                       =  9,  /*!<  PM GNSS-AFE5 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_MIXER5_SHIFT                    =  6,  /*!<  PM GNSS-AFE5 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_BALUN5_SHIFT                    =  3,  /*!<  PM GNSS-AFE5 Configuration Register Shift Value */
     CFGREG_PM_GNSSAFE5_CONF_IREG_LNA5_SHIFT                      =  0,  /*!<  PM GNSS-AFE5 Configuration Register Shift Value */

     CFGREG_DCDC_CONF_DCDC_TRIM_SHIFT                             =  1,  /*!<  DCDC Configuration Register Shift Value */
     CFGREG_DCDC_CONF_DCDC_EN_SHIFT                               =  0,  /*!<  DCDC Configuration Register Shift Value */

     CFGREG_LNA1_CONF_LNA_TUNE_SHIFT                              =  1,  /*!<  LNA1 Configuration Register Shift Value */
     CFGREG_LNA1_CONF_EN_SHIFT                                    =  0,  /*!<  LNA1 Configuration Register Shift Value */

     CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SHIFT                    =  2,  /*!<  BALUN and MIXER 1 Configuration Register Shift Value */
     CFGREG_BALUN_MIXER1_CONF_BALUN_EN_SHIFT                      =  1,  /*!<  BALUN and MIXER 1 Configuration Register Shift Value */
     CFGREG_BALUN_MIXER1_CONF_MIXER_EN_SHIFT                      =  0,  /*!<  BALUN and MIXER 1 Configuration Register Shift Value */

     CFGREG_LNA5_CONF_LNA_TUNE_SHIFT                              =  1,  /*!<  LNA5 Configuration Register Shift Value */
     CFGREG_LNA5_CONF_EN_SHIFT                                    =  0,  /*!<  LNA5 Configuration Register Shift Value */

     CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SHIFT                    =  2,  /*!<  BALUN and MIXER 5 Configuration Register Shift Value */
     CFGREG_BALUN_MIXER5_CONF_BALUN_EN_SHIFT                      =  1,  /*!<  BALUN and MIXER 5 Configuration Register Shift Value */
     CFGREG_BALUN_MIXER5_CONF_MIXER_EN_SHIFT                      =  0,  /*!<  BALUN and MIXER 5 Configuration Register Shift Value */

     CFGREG_LNA15_TUNE_CONF_BAND5_TUNE_SHIFT                      = 16,  /*!<  LNA15 Tuning Configuration Register Shift Value */
     CFGREG_LNA15_TUNE_CONF_BAND1_TUNE_SHIFT                      =  0,  /*!<  LNA15 Tuning Configuration Register Shift Value */

     CFGREG_LNA15_CONF_SPARE_TUNE_SHIFT                           =  1,  /*!<  LNA15 Configuration Register Shift Value */
     CFGREG_LNA15_CONF_EN_SHIFT                                   =  0,  /*!<  LNA15 Configuration Register Shift Value */

     CFGREG_PROBE_IF1_CONF_PROBEB_SELECT_SHIFT                    =  6,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF1_CONF_PROBEB_SOURCE_SHIFT                    =  5,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF1_CONF_PROBEB_EN_SHIFT                        =  4,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF1_CONF_PROBEA_SELECT_SHIFT                    =  2,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF1_CONF_PROBEA_SOURCE_SHIFT                    =  1,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF1_CONF_PROBEA_EN_SHIFT                        =  0,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */

     CFGREG_PROBE_IF5_CONF_NRST_TEST_SHIFT                        = 11,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF5_CONF_PLL15FB_SEL_SHIFT                      = 10,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF5_CONF_PLL_VCONT_EN_SHIFT                     =  9,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF5_CONF_IBIAS_TEST_EN_SHIFT                    =  8,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF5_CONF_PROBEB_SELECT_SHIFT                    =  6,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF5_CONF_PROBEB_SOURCE_SHIFT                    =  5,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF5_CONF_PROBEB_EN_SHIFT                        =  4,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF5_CONF_PROBEA_SELECT_SHIFT                    =  2,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF5_CONF_PROBEA_SOURCE_SHIFT                    =  1,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_IF5_CONF_PROBEA_EN_SHIFT                        =  0,  /*!<  GNSS-AFE IF5 analog probing Configuration Register Shift Value */

     CFGREG_PLL1_CONF_TEST_EN_SHIFT                               = 25,  /*!<  PLL1 Configuration Register Shift Value */
     CFGREG_PLL1_CONF_FCW_SHIFT                                   =  1,  /*!<  PLL1 Configuration Register Shift Value */
     CFGREG_PLL1_CONF_EN_SHIFT                                    =  0,  /*!<  PLL1 Configuration Register Shift Value */

     CFGREG_PLL1TDC_CONF_SCALE_SHIFT                              =  1,  /*!<  PLL1 TDC Configuration Register Shift Value */
     CFGREG_PLL1TDC_CONF_LOAD_SHIFT                               =  0,  /*!<  PLL1 TDC Configuration Register Shift Value */

     CFGREG_PLL1DCO_CONF_CTRL_PVT_SHIFT                           = 16,  /*!<  PLL1 DCO Configuration Register Shift Value */
     CFGREG_PLL1DCO_CONF_CTRL_FINE_SHIFT                          =  1,  /*!<  PLL1 DCO Configuration Register Shift Value */
     CFGREG_PLL1DCO_CONF_CTRL_LOAD_SHIFT                          =  0,  /*!<  PLL1 DCO Configuration Register Shift Value */

     CFGREG_PLL1_STAT_PHERR_SHIFT                                 = 10,  /*!<  PLL1 Status Register Shift Value */
     CFGREG_PLL1_STAT_NDIV_SHIFT                                  =  2,  /*!<  PLL1 Status Register Shift Value */
     CFGREG_PLL1_STAT_PHSEL_SHIFT                                 =  1,  /*!<  PLL1 Status Register Shift Value */
     CFGREG_PLL1_STAT_LOCK_SHIFT                                  =  0,  /*!<  PLL1 Status Register Shift Value */

     CFGREG_PLL1TDC_STAT_SCALE_SHIFT                              =  0,  /*!<  PLL1 TDC Status Register Shift Value */

     CFGREG_PLL1DCO_STAT_CTRL_PVT_SHIFT                           = 14,  /*!<  PLL1 TDC Status Register Shift Value */
     CFGREG_PLL1DCO_STAT_CTRL_FINE_SHIFT                          =  0,  /*!<  PLL1 TDC Status Register Shift Value */

     CFGREG_IF1_CONF_LPF_CAL_SHIFT                                = 14,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_LPF_GAIN_SHIFT                               = 12,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_LPF_BAND_SHIFT                               = 10,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_LPF_EN_SHIFT                                 =  9,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PGA2_GAIN_SHIFT                              =  7,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PGA2_EN_SHIFT                                =  6,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PGA1_GAIN_SHIFT                              =  4,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PGA1_EN_SHIFT                                =  3,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PREAMP_EN_SHIFT                              =  2,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_LOAD_EN_SHIFT                                =  1,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_EN_SHIFT                                     =  0,  /*!<  IF1 Configuration Register Shift Value */

     CFGREG_IF1_STAT_AGC_CTRL_SHIFT                               =  0,  /*!<  IF1 Status Register Shift Value */

     CFGREG_ADC1_CONF_CLK_CONF_SHIFT                              =  2,  /*!<  ADC1 Configuration Register Shift Value */
     CFGREG_ADC1_CONF_SAH_EN_SHIFT                                =  1,  /*!<  ADC1 Configuration Register Shift Value */
     CFGREG_ADC1_CONF_ADC_EN_SHIFT                                =  0,  /*!<  ADC1 Configuration Register Shift Value */

     CFGREG_PLL5_CONF_TEST_EN_SHIFT                               = 25,  /*!<  PLL5 Configuration Register Shift Value */
     CFGREG_PLL5_CONF_FCW_SHIFT                                   =  1,  /*!<  PLL5 Configuration Register Shift Value */
     CFGREG_PLL5_CONF_EN_SHIFT                                    =  0,  /*!<  PLL5 Configuration Register Shift Value */

     CFGREG_PLL5TDC_CONF_SCALE_SHIFT                              =  1,  /*!<  PLL5 TDC Configuration Register Shift Value */
     CFGREG_PLL5TDC_CONF_LOAD_SHIFT                               =  0,  /*!<  PLL5 TDC Configuration Register Shift Value */

     CFGREG_PLL5DCO_CONF_CTRL_PVT_SHIFT                           = 16,  /*!<  PLL5 DCO Configuration Register Shift Value */
     CFGREG_PLL5DCO_CONF_CTRL_FINE_SHIFT                          =  1,  /*!<  PLL5 DCO Configuration Register Shift Value */
     CFGREG_PLL5DCO_CONF_CTRL_LOAD_SHIFT                          =  0,  /*!<  PLL5 DCO Configuration Register Shift Value */

     CFGREG_PLL5_STAT_PHERR_SHIFT                                 = 10,  /*!<  PLL5 Status Register Shift Value */
     CFGREG_PLL5_STAT_NDIV_SHIFT                                  =  2,  /*!<  PLL5 Status Register Shift Value */
     CFGREG_PLL5_STAT_PHSEL_SHIFT                                 =  1,  /*!<  PLL5 Status Register Shift Value */
     CFGREG_PLL5_STAT_LOCK_SHIFT                                  =  0,  /*!<  PLL5 Status Register Shift Value */

     CFGREG_PLL5TDC_STAT_SCALE_SHIFT                              =  0,  /*!<  PLL5 TDC Status Register Shift Value */

     CFGREG_PLL5DCO_STAT_CTRL_PVT_SHIFT                           = 14,  /*!<  PLL5 TDC Status Register Shift Value */
     CFGREG_PLL5DCO_STAT_CTRL_FINE_SHIFT                          =  0,  /*!<  PLL5 TDC Status Register Shift Value */

     CFGREG_IF5_CONF_LPF_CAL_SHIFT                                = 14,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_LPF_GAIN_SHIFT                               = 12,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_LPF_BAND_SHIFT                               = 10,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_LPF_EN_SHIFT                                 =  9,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PGA2_GAIN_SHIFT                              =  7,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PGA2_EN_SHIFT                                =  6,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PGA1_GAIN_SHIFT                              =  4,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PGA1_EN_SHIFT                                =  3,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PREAMP_EN_SHIFT                              =  2,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_LOAD_EN_SHIFT                                =  1,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_EN_SHIFT                                     =  0,  /*!<  IF5 Configuration Register Shift Value */

     CFGREG_IF5_STAT_AGC_CTRL_SHIFT                               =  0,  /*!<  IF5 status Register Shift Value */

     CFGREG_ADC5_CONF_CLK_CONF_SHIFT                              =  2,  /*!<  ADC5 Configuration Register Shift Value */
     CFGREG_ADC5_CONF_SAH_EN_SHIFT                                =  1,  /*!<  ADC5 Configuration Register Shift Value */
     CFGREG_ADC5_CONF_ADC_EN_SHIFT                                =  0,  /*!<  ADC5 Configuration Register Shift Value */

};

/** Bits Set Helper Macros */

#define CFGREG_IRQMAP_IRQMAP_BITS_SET(x)                                       ((x << CFGREG_IRQMAP_IRQMAP_SHIFT) & CFGREG_IRQMAP_IRQMAP_MASK)                                                          /*!<  Interrupt Mapping Register Bits Set */

#define CFGREG_UNLOCK_UNLOCK_KEY_BITS_SET(x)                                   ((x << CFGREG_UNLOCK_UNLOCK_KEY_SHIFT) & CFGREG_UNLOCK_UNLOCK_KEY_MASK)                                                  /*!<  Unlock Register Bits Set */

#define CFGREG_IRQFLAGS_PLL_FAIL_BITS_SET(x)                                   ((x << CFGREG_IRQFLAGS_PLL_FAIL_SHIFT) & CFGREG_IRQFLAGS_PLL_FAIL_MASK)                                                  /*!<  32kHz RTC Clock Interrupt Flags Bits Set */
#define CFGREG_IRQFLAGS_XTAL_CORE_FAIL_BITS_SET(x)                             ((x << CFGREG_IRQFLAGS_XTAL_CORE_FAIL_SHIFT) & CFGREG_IRQFLAGS_XTAL_CORE_FAIL_MASK)                                      /*!<  32kHz RTC Clock Interrupt Flags Bits Set */
#define CFGREG_IRQFLAGS_XTAL_RTC_FAIL_BITS_SET(x)                              ((x << CFGREG_IRQFLAGS_XTAL_RTC_FAIL_SHIFT) & CFGREG_IRQFLAGS_XTAL_RTC_FAIL_MASK)                                        /*!<  32kHz RTC Clock Interrupt Flags Bits Set */

#define CFGREG_RTCSTAT_RC_RTC_VAL_BITS_SET(x)                                  ((x << CFGREG_RTCSTAT_RC_RTC_VAL_SHIFT) & CFGREG_RTCSTAT_RC_RTC_VAL_MASK)                                                /*!<  32kHz RTC Clock Status Bits Set */
#define CFGREG_RTCSTAT_RC_RTC_RDY_BITS_SET(x)                                  ((x << CFGREG_RTCSTAT_RC_RTC_RDY_SHIFT) & CFGREG_RTCSTAT_RC_RTC_RDY_MASK)                                                /*!<  32kHz RTC Clock Status Bits Set */
#define CFGREG_RTCSTAT_CLK_RTC_SEL_BITS_SET(x)                                 ((x << CFGREG_RTCSTAT_CLK_RTC_SEL_SHIFT) & CFGREG_RTCSTAT_CLK_RTC_SEL_MASK)                                              /*!<  32kHz RTC Clock Status Bits Set */

#define CFGREG_RTCCONF_RC_RTC_CAL_BITS_SET(x)                                  ((x << CFGREG_RTCCONF_RC_RTC_CAL_SHIFT) & CFGREG_RTCCONF_RC_RTC_CAL_MASK)                                                /*!<  32kHz RTC Clock Configuration Bits Set */
#define CFGREG_RTCCONF_XTAL_RTC_SEL_BITS_SET(x)                                ((x << CFGREG_RTCCONF_XTAL_RTC_SEL_SHIFT) & CFGREG_RTCCONF_XTAL_RTC_SEL_MASK)                                            /*!<  32kHz RTC Clock Configuration Bits Set */
#define CFGREG_RTCCONF_XTAL_RTC_TEST_BITS_SET(x)                               ((x << CFGREG_RTCCONF_XTAL_RTC_TEST_SHIFT) & CFGREG_RTCCONF_XTAL_RTC_TEST_MASK)                                          /*!<  32kHz RTC Clock Configuration Bits Set */

#define CFGREG_COREFREQ_CLK_TEST_OUT_EN_BITS_SET(x)                            ((x << CFGREG_COREFREQ_CLK_TEST_OUT_EN_SHIFT) & CFGREG_COREFREQ_CLK_TEST_OUT_EN_MASK)                                    /*!<  External XTAL Configuration Register Bits Set */
#define CFGREG_COREFREQ_CLK_RC_CORE_CAL_BITS_SET(x)                            ((x << CFGREG_COREFREQ_CLK_RC_CORE_CAL_SHIFT) & CFGREG_COREFREQ_CLK_RC_CORE_CAL_MASK)                                    /*!<  External XTAL Configuration Register Bits Set */
#define CFGREG_COREFREQ_CLK_CLK_CORE_SEL_BITS_SET(x)                           ((x << CFGREG_COREFREQ_CLK_CLK_CORE_SEL_SHIFT) & CFGREG_COREFREQ_CLK_CLK_CORE_SEL_MASK)                                  /*!<  External XTAL Configuration Register Bits Set */
#define CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_BITS_SET(x)                         ((x << CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_SHIFT) & CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_MASK)                              /*!<  External XTAL Configuration Register Bits Set */

#define CFGREG_COREFREQ_PLL_PLL_VFB_EN_BITS_SET(x)                             ((x << CFGREG_COREFREQ_PLL_PLL_VFB_EN_SHIFT) & CFGREG_COREFREQ_PLL_PLL_VFB_EN_MASK)                                      /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_PLL_VCONT_SF_BITS_SET(x)                           ((x << CFGREG_COREFREQ_PLL_PLL_VCONT_SF_SHIFT) & CFGREG_COREFREQ_PLL_PLL_VCONT_SF_MASK)                                  /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_PLL_VCONT_EN_BITS_SET(x)                           ((x << CFGREG_COREFREQ_PLL_PLL_VCONT_EN_SHIFT) & CFGREG_COREFREQ_PLL_PLL_VCONT_EN_MASK)                                  /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_PLL_TEST_BITS_SET(x)                               ((x << CFGREG_COREFREQ_PLL_PLL_TEST_SHIFT) & CFGREG_COREFREQ_PLL_PLL_TEST_MASK)                                          /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_PLL_N_BITS_SET(x)                                  ((x << CFGREG_COREFREQ_PLL_PLL_N_SHIFT) & CFGREG_COREFREQ_PLL_PLL_N_MASK)                                                /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_PLL_M_BITS_SET(x)                                  ((x << CFGREG_COREFREQ_PLL_PLL_M_SHIFT) & CFGREG_COREFREQ_PLL_PLL_M_MASK)                                                /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_REF_SEL_BITS_SET(x)                                ((x << CFGREG_COREFREQ_PLL_REF_SEL_SHIFT) & CFGREG_COREFREQ_PLL_REF_SEL_MASK)                                            /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_PLL_EN_BITS_SET(x)                                 ((x << CFGREG_COREFREQ_PLL_PLL_EN_SHIFT) & CFGREG_COREFREQ_PLL_PLL_EN_MASK)                                              /*!<  PLL Configuration Register Bits Set */

#define CFGREG_COREFREQ_STAT_RC_CORE_VAL_BITS_SET(x)                           ((x << CFGREG_COREFREQ_STAT_RC_CORE_VAL_SHIFT) & CFGREG_COREFREQ_STAT_RC_CORE_VAL_MASK)                                  /*!<  Core Clock Status Register Bits Set */
#define CFGREG_COREFREQ_STAT_RC_CORE_RDY_BITS_SET(x)                           ((x << CFGREG_COREFREQ_STAT_RC_CORE_RDY_SHIFT) & CFGREG_COREFREQ_STAT_RC_CORE_RDY_MASK)                                  /*!<  Core Clock Status Register Bits Set */
#define CFGREG_COREFREQ_STAT_PLL_LOCK_BITS_SET(x)                              ((x << CFGREG_COREFREQ_STAT_PLL_LOCK_SHIFT) & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK)                                        /*!<  Core Clock Status Register Bits Set */
#define CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_BITS_SET(x)                        ((x << CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_SHIFT) & CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_MASK)                            /*!<  Core Clock Status Register Bits Set */
#define CFGREG_COREFREQ_STAT_CLK_CORE_SEL_BITS_SET(x)                          ((x << CFGREG_COREFREQ_STAT_CLK_CORE_SEL_SHIFT) & CFGREG_COREFREQ_STAT_CLK_CORE_SEL_MASK)                                /*!<  Core Clock Status Register Bits Set */

#define CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_BITS_SET(x)                           ((x << CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_SHIFT) & CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_MASK)                                  /*!<  GNSS-AFE Configuration Register Bits Set */
#define CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_BITS_SET(x)                          ((x << CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_SHIFT) & CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_MASK)                                /*!<  GNSS-AFE Configuration Register Bits Set */

#define CFGREG_PM_CONF_PM_ITRIM_BITS_SET(x)                                    ((x << CFGREG_PM_CONF_PM_ITRIM_SHIFT) & CFGREG_PM_CONF_PM_ITRIM_MASK)                                                    /*!<  PM GLOBAL Configuration Register Bits Set */
#define CFGREG_PM_CONF_PM_EN_BITS_SET(x)                                       ((x << CFGREG_PM_CONF_PM_EN_SHIFT) & CFGREG_PM_CONF_PM_EN_MASK)                                                          /*!<  PM GLOBAL Configuration Register Bits Set */

#define CFGREG_PM_GNSSAFE1_CONF_IREG_SPARE1_BITS_SET(x)                        ((x << CFGREG_PM_GNSSAFE1_CONF_IREG_SPARE1_SHIFT) & CFGREG_PM_GNSSAFE1_CONF_IREG_SPARE1_MASK)                            /*!<  PM GNSS-AFE1 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_TEST_BITS_SET(x)                          ((x << CFGREG_PM_GNSSAFE1_CONF_IREG_TEST_SHIFT) & CFGREG_PM_GNSSAFE1_CONF_IREG_TEST_MASK)                                /*!<  PM GNSS-AFE1 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_PLL1_BITS_SET(x)                          ((x << CFGREG_PM_GNSSAFE1_CONF_IREG_PLL1_SHIFT) & CFGREG_PM_GNSSAFE1_CONF_IREG_PLL1_MASK)                                /*!<  PM GNSS-AFE1 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_ADC1_BITS_SET(x)                          ((x << CFGREG_PM_GNSSAFE1_CONF_IREG_ADC1_SHIFT) & CFGREG_PM_GNSSAFE1_CONF_IREG_ADC1_MASK)                                /*!<  PM GNSS-AFE1 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_IF1_BITS_SET(x)                           ((x << CFGREG_PM_GNSSAFE1_CONF_IREG_IF1_SHIFT) & CFGREG_PM_GNSSAFE1_CONF_IREG_IF1_MASK)                                  /*!<  PM GNSS-AFE1 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_MIXER1_BITS_SET(x)                        ((x << CFGREG_PM_GNSSAFE1_CONF_IREG_MIXER1_SHIFT) & CFGREG_PM_GNSSAFE1_CONF_IREG_MIXER1_MASK)                            /*!<  PM GNSS-AFE1 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_BALUN1_BITS_SET(x)                        ((x << CFGREG_PM_GNSSAFE1_CONF_IREG_BALUN1_SHIFT) & CFGREG_PM_GNSSAFE1_CONF_IREG_BALUN1_MASK)                            /*!<  PM GNSS-AFE1 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_LNA1_BITS_SET(x)                          ((x << CFGREG_PM_GNSSAFE1_CONF_IREG_LNA1_SHIFT) & CFGREG_PM_GNSSAFE1_CONF_IREG_LNA1_MASK)                                /*!<  PM GNSS-AFE1 Configuration Register Bits Set */

#define CFGREG_PM_GNSSAFE5_CONF_IREG_SPARE5_BITS_SET(x)                        ((x << CFGREG_PM_GNSSAFE5_CONF_IREG_SPARE5_SHIFT) & CFGREG_PM_GNSSAFE5_CONF_IREG_SPARE5_MASK)                            /*!<  PM GNSS-AFE5 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_LNA15_BITS_SET(x)                         ((x << CFGREG_PM_GNSSAFE5_CONF_IREG_LNA15_SHIFT) & CFGREG_PM_GNSSAFE5_CONF_IREG_LNA15_MASK)                              /*!<  PM GNSS-AFE5 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_PLL5_BITS_SET(x)                          ((x << CFGREG_PM_GNSSAFE5_CONF_IREG_PLL5_SHIFT) & CFGREG_PM_GNSSAFE5_CONF_IREG_PLL5_MASK)                                /*!<  PM GNSS-AFE5 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_ADC5_BITS_SET(x)                          ((x << CFGREG_PM_GNSSAFE5_CONF_IREG_ADC5_SHIFT) & CFGREG_PM_GNSSAFE5_CONF_IREG_ADC5_MASK)                                /*!<  PM GNSS-AFE5 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_IF5_BITS_SET(x)                           ((x << CFGREG_PM_GNSSAFE5_CONF_IREG_IF5_SHIFT) & CFGREG_PM_GNSSAFE5_CONF_IREG_IF5_MASK)                                  /*!<  PM GNSS-AFE5 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_MIXER5_BITS_SET(x)                        ((x << CFGREG_PM_GNSSAFE5_CONF_IREG_MIXER5_SHIFT) & CFGREG_PM_GNSSAFE5_CONF_IREG_MIXER5_MASK)                            /*!<  PM GNSS-AFE5 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_BALUN5_BITS_SET(x)                        ((x << CFGREG_PM_GNSSAFE5_CONF_IREG_BALUN5_SHIFT) & CFGREG_PM_GNSSAFE5_CONF_IREG_BALUN5_MASK)                            /*!<  PM GNSS-AFE5 Configuration Register Bits Set */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_LNA5_BITS_SET(x)                          ((x << CFGREG_PM_GNSSAFE5_CONF_IREG_LNA5_SHIFT) & CFGREG_PM_GNSSAFE5_CONF_IREG_LNA5_MASK)                                /*!<  PM GNSS-AFE5 Configuration Register Bits Set */

#define CFGREG_DCDC_CONF_DCDC_TRIM_BITS_SET(x)                                 ((x << CFGREG_DCDC_CONF_DCDC_TRIM_SHIFT) & CFGREG_DCDC_CONF_DCDC_TRIM_MASK)                                              /*!<  DCDC Configuration Register Bits Set */
#define CFGREG_DCDC_CONF_DCDC_EN_BITS_SET(x)                                   ((x << CFGREG_DCDC_CONF_DCDC_EN_SHIFT) & CFGREG_DCDC_CONF_DCDC_EN_MASK)                                                  /*!<  DCDC Configuration Register Bits Set */

#define CFGREG_LNA1_CONF_LNA_TUNE_BITS_SET(x)                                  ((x << CFGREG_LNA1_CONF_LNA_TUNE_SHIFT) & CFGREG_LNA1_CONF_LNA_TUNE_MASK)                                                /*!<  LNA1 Configuration Register Bits Set */
#define CFGREG_LNA1_CONF_EN_BITS_SET(x)                                        ((x << CFGREG_LNA1_CONF_EN_SHIFT) & CFGREG_LNA1_CONF_EN_MASK)                                                            /*!<  LNA1 Configuration Register Bits Set */

#define CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_BITS_SET(x)                        ((x << CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SHIFT) & CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_MASK)                            /*!<  BALUN and MIXER 1 Configuration Register Bits Set */
#define CFGREG_BALUN_MIXER1_CONF_BALUN_EN_BITS_SET(x)                          ((x << CFGREG_BALUN_MIXER1_CONF_BALUN_EN_SHIFT) & CFGREG_BALUN_MIXER1_CONF_BALUN_EN_MASK)                                /*!<  BALUN and MIXER 1 Configuration Register Bits Set */
#define CFGREG_BALUN_MIXER1_CONF_MIXER_EN_BITS_SET(x)                          ((x << CFGREG_BALUN_MIXER1_CONF_MIXER_EN_SHIFT) & CFGREG_BALUN_MIXER1_CONF_MIXER_EN_MASK)                                /*!<  BALUN and MIXER 1 Configuration Register Bits Set */

#define CFGREG_LNA5_CONF_LNA_TUNE_BITS_SET(x)                                  ((x << CFGREG_LNA5_CONF_LNA_TUNE_SHIFT) & CFGREG_LNA5_CONF_LNA_TUNE_MASK)                                                /*!<  LNA5 Configuration Register Bits Set */
#define CFGREG_LNA5_CONF_EN_BITS_SET(x)                                        ((x << CFGREG_LNA5_CONF_EN_SHIFT) & CFGREG_LNA5_CONF_EN_MASK)                                                            /*!<  LNA5 Configuration Register Bits Set */

#define CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_BITS_SET(x)                        ((x << CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SHIFT) & CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_MASK)                            /*!<  BALUN and MIXER 5 Configuration Register Bits Set */
#define CFGREG_BALUN_MIXER5_CONF_BALUN_EN_BITS_SET(x)                          ((x << CFGREG_BALUN_MIXER5_CONF_BALUN_EN_SHIFT) & CFGREG_BALUN_MIXER5_CONF_BALUN_EN_MASK)                                /*!<  BALUN and MIXER 5 Configuration Register Bits Set */
#define CFGREG_BALUN_MIXER5_CONF_MIXER_EN_BITS_SET(x)                          ((x << CFGREG_BALUN_MIXER5_CONF_MIXER_EN_SHIFT) & CFGREG_BALUN_MIXER5_CONF_MIXER_EN_MASK)                                /*!<  BALUN and MIXER 5 Configuration Register Bits Set */

#define CFGREG_LNA15_TUNE_CONF_BAND5_TUNE_BITS_SET(x)                          ((x << CFGREG_LNA15_TUNE_CONF_BAND5_TUNE_SHIFT) & CFGREG_LNA15_TUNE_CONF_BAND5_TUNE_MASK)                                /*!<  LNA15 Tuning Configuration Register Bits Set */
#define CFGREG_LNA15_TUNE_CONF_BAND1_TUNE_BITS_SET(x)                          ((x << CFGREG_LNA15_TUNE_CONF_BAND1_TUNE_SHIFT) & CFGREG_LNA15_TUNE_CONF_BAND1_TUNE_MASK)                                /*!<  LNA15 Tuning Configuration Register Bits Set */

#define CFGREG_LNA15_CONF_SPARE_TUNE_BITS_SET(x)                               ((x << CFGREG_LNA15_CONF_SPARE_TUNE_SHIFT) & CFGREG_LNA15_CONF_SPARE_TUNE_MASK)                                          /*!<  LNA15 Configuration Register Bits Set */
#define CFGREG_LNA15_CONF_EN_BITS_SET(x)                                       ((x << CFGREG_LNA15_CONF_EN_SHIFT) & CFGREG_LNA15_CONF_EN_MASK)                                                          /*!<  LNA15 Configuration Register Bits Set */

#define CFGREG_PROBE_IF1_CONF_PROBEB_SELECT_BITS_SET(x)                        ((x << CFGREG_PROBE_IF1_CONF_PROBEB_SELECT_SHIFT) & CFGREG_PROBE_IF1_CONF_PROBEB_SELECT_MASK)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF1_CONF_PROBEB_SOURCE_BITS_SET(x)                        ((x << CFGREG_PROBE_IF1_CONF_PROBEB_SOURCE_SHIFT) & CFGREG_PROBE_IF1_CONF_PROBEB_SOURCE_MASK)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF1_CONF_PROBEB_EN_BITS_SET(x)                            ((x << CFGREG_PROBE_IF1_CONF_PROBEB_EN_SHIFT) & CFGREG_PROBE_IF1_CONF_PROBEB_EN_MASK)                                    /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF1_CONF_PROBEA_SELECT_BITS_SET(x)                        ((x << CFGREG_PROBE_IF1_CONF_PROBEA_SELECT_SHIFT) & CFGREG_PROBE_IF1_CONF_PROBEA_SELECT_MASK)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF1_CONF_PROBEA_SOURCE_BITS_SET(x)                        ((x << CFGREG_PROBE_IF1_CONF_PROBEA_SOURCE_SHIFT) & CFGREG_PROBE_IF1_CONF_PROBEA_SOURCE_MASK)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF1_CONF_PROBEA_EN_BITS_SET(x)                            ((x << CFGREG_PROBE_IF1_CONF_PROBEA_EN_SHIFT) & CFGREG_PROBE_IF1_CONF_PROBEA_EN_MASK)                                    /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */

#define CFGREG_PROBE_IF5_CONF_NRST_TEST_BITS_SET(x)                            ((x << CFGREG_PROBE_IF5_CONF_NRST_TEST_SHIFT) & CFGREG_PROBE_IF5_CONF_NRST_TEST_MASK)                                    /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF5_CONF_PLL15FB_SEL_BITS_SET(x)                          ((x << CFGREG_PROBE_IF5_CONF_PLL15FB_SEL_SHIFT) & CFGREG_PROBE_IF5_CONF_PLL15FB_SEL_MASK)                                /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF5_CONF_PLL_VCONT_EN_BITS_SET(x)                         ((x << CFGREG_PROBE_IF5_CONF_PLL_VCONT_EN_SHIFT) & CFGREG_PROBE_IF5_CONF_PLL_VCONT_EN_MASK)                              /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF5_CONF_IBIAS_TEST_EN_BITS_SET(x)                        ((x << CFGREG_PROBE_IF5_CONF_IBIAS_TEST_EN_SHIFT) & CFGREG_PROBE_IF5_CONF_IBIAS_TEST_EN_MASK)                            /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF5_CONF_PROBEB_SELECT_BITS_SET(x)                        ((x << CFGREG_PROBE_IF5_CONF_PROBEB_SELECT_SHIFT) & CFGREG_PROBE_IF5_CONF_PROBEB_SELECT_MASK)                            /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF5_CONF_PROBEB_SOURCE_BITS_SET(x)                        ((x << CFGREG_PROBE_IF5_CONF_PROBEB_SOURCE_SHIFT) & CFGREG_PROBE_IF5_CONF_PROBEB_SOURCE_MASK)                            /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF5_CONF_PROBEB_EN_BITS_SET(x)                            ((x << CFGREG_PROBE_IF5_CONF_PROBEB_EN_SHIFT) & CFGREG_PROBE_IF5_CONF_PROBEB_EN_MASK)                                    /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF5_CONF_PROBEA_SELECT_BITS_SET(x)                        ((x << CFGREG_PROBE_IF5_CONF_PROBEA_SELECT_SHIFT) & CFGREG_PROBE_IF5_CONF_PROBEA_SELECT_MASK)                            /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF5_CONF_PROBEA_SOURCE_BITS_SET(x)                        ((x << CFGREG_PROBE_IF5_CONF_PROBEA_SOURCE_SHIFT) & CFGREG_PROBE_IF5_CONF_PROBEA_SOURCE_MASK)                            /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_IF5_CONF_PROBEA_EN_BITS_SET(x)                            ((x << CFGREG_PROBE_IF5_CONF_PROBEA_EN_SHIFT) & CFGREG_PROBE_IF5_CONF_PROBEA_EN_MASK)                                    /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Set */

#define CFGREG_PLL1_CONF_TEST_EN_BITS_SET(x)                                   ((x << CFGREG_PLL1_CONF_TEST_EN_SHIFT) & CFGREG_PLL1_CONF_TEST_EN_MASK)                                                  /*!<  PLL1 Configuration Register Bits Set */
#define CFGREG_PLL1_CONF_FCW_BITS_SET(x)                                       ((x << CFGREG_PLL1_CONF_FCW_SHIFT) & CFGREG_PLL1_CONF_FCW_MASK)                                                          /*!<  PLL1 Configuration Register Bits Set */
#define CFGREG_PLL1_CONF_EN_BITS_SET(x)                                        ((x << CFGREG_PLL1_CONF_EN_SHIFT) & CFGREG_PLL1_CONF_EN_MASK)                                                            /*!<  PLL1 Configuration Register Bits Set */

#define CFGREG_PLL1TDC_CONF_SCALE_BITS_SET(x)                                  ((x << CFGREG_PLL1TDC_CONF_SCALE_SHIFT) & CFGREG_PLL1TDC_CONF_SCALE_MASK)                                                /*!<  PLL1 TDC Configuration Register Bits Set */
#define CFGREG_PLL1TDC_CONF_LOAD_BITS_SET(x)                                   ((x << CFGREG_PLL1TDC_CONF_LOAD_SHIFT) & CFGREG_PLL1TDC_CONF_LOAD_MASK)                                                  /*!<  PLL1 TDC Configuration Register Bits Set */

#define CFGREG_PLL1DCO_CONF_CTRL_PVT_BITS_SET(x)                               ((x << CFGREG_PLL1DCO_CONF_CTRL_PVT_SHIFT) & CFGREG_PLL1DCO_CONF_CTRL_PVT_MASK)                                          /*!<  PLL1 DCO Configuration Register Bits Set */
#define CFGREG_PLL1DCO_CONF_CTRL_FINE_BITS_SET(x)                              ((x << CFGREG_PLL1DCO_CONF_CTRL_FINE_SHIFT) & CFGREG_PLL1DCO_CONF_CTRL_FINE_MASK)                                        /*!<  PLL1 DCO Configuration Register Bits Set */
#define CFGREG_PLL1DCO_CONF_CTRL_LOAD_BITS_SET(x)                              ((x << CFGREG_PLL1DCO_CONF_CTRL_LOAD_SHIFT) & CFGREG_PLL1DCO_CONF_CTRL_LOAD_MASK)                                        /*!<  PLL1 DCO Configuration Register Bits Set */

#define CFGREG_PLL1_STAT_PHERR_BITS_SET(x)                                     ((x << CFGREG_PLL1_STAT_PHERR_SHIFT) & CFGREG_PLL1_STAT_PHERR_MASK)                                                      /*!<  PLL1 Status Register Bits Set */
#define CFGREG_PLL1_STAT_NDIV_BITS_SET(x)                                      ((x << CFGREG_PLL1_STAT_NDIV_SHIFT) & CFGREG_PLL1_STAT_NDIV_MASK)                                                        /*!<  PLL1 Status Register Bits Set */
#define CFGREG_PLL1_STAT_PHSEL_BITS_SET(x)                                     ((x << CFGREG_PLL1_STAT_PHSEL_SHIFT) & CFGREG_PLL1_STAT_PHSEL_MASK)                                                      /*!<  PLL1 Status Register Bits Set */
#define CFGREG_PLL1_STAT_LOCK_BITS_SET(x)                                      ((x << CFGREG_PLL1_STAT_LOCK_SHIFT) & CFGREG_PLL1_STAT_LOCK_MASK)                                                        /*!<  PLL1 Status Register Bits Set */

#define CFGREG_PLL1TDC_STAT_SCALE_BITS_SET(x)                                  ((x << CFGREG_PLL1TDC_STAT_SCALE_SHIFT) & CFGREG_PLL1TDC_STAT_SCALE_MASK)                                                /*!<  PLL1 TDC Status Register Bits Set */

#define CFGREG_PLL1DCO_STAT_CTRL_PVT_BITS_SET(x)                               ((x << CFGREG_PLL1DCO_STAT_CTRL_PVT_SHIFT) & CFGREG_PLL1DCO_STAT_CTRL_PVT_MASK)                                          /*!<  PLL1 TDC Status Register Bits Set */
#define CFGREG_PLL1DCO_STAT_CTRL_FINE_BITS_SET(x)                              ((x << CFGREG_PLL1DCO_STAT_CTRL_FINE_SHIFT) & CFGREG_PLL1DCO_STAT_CTRL_FINE_MASK)                                        /*!<  PLL1 TDC Status Register Bits Set */

#define CFGREG_IF1_CONF_LPF_CAL_BITS_SET(x)                                    ((x << CFGREG_IF1_CONF_LPF_CAL_SHIFT) & CFGREG_IF1_CONF_LPF_CAL_MASK)                                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_LPF_GAIN_BITS_SET(x)                                   ((x << CFGREG_IF1_CONF_LPF_GAIN_SHIFT) & CFGREG_IF1_CONF_LPF_GAIN_MASK)                                                  /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_LPF_BAND_BITS_SET(x)                                   ((x << CFGREG_IF1_CONF_LPF_BAND_SHIFT) & CFGREG_IF1_CONF_LPF_BAND_MASK)                                                  /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_LPF_EN_BITS_SET(x)                                     ((x << CFGREG_IF1_CONF_LPF_EN_SHIFT) & CFGREG_IF1_CONF_LPF_EN_MASK)                                                      /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PGA2_GAIN_BITS_SET(x)                                  ((x << CFGREG_IF1_CONF_PGA2_GAIN_SHIFT) & CFGREG_IF1_CONF_PGA2_GAIN_MASK)                                                /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PGA2_EN_BITS_SET(x)                                    ((x << CFGREG_IF1_CONF_PGA2_EN_SHIFT) & CFGREG_IF1_CONF_PGA2_EN_MASK)                                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PGA1_GAIN_BITS_SET(x)                                  ((x << CFGREG_IF1_CONF_PGA1_GAIN_SHIFT) & CFGREG_IF1_CONF_PGA1_GAIN_MASK)                                                /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PGA1_EN_BITS_SET(x)                                    ((x << CFGREG_IF1_CONF_PGA1_EN_SHIFT) & CFGREG_IF1_CONF_PGA1_EN_MASK)                                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PREAMP_EN_BITS_SET(x)                                  ((x << CFGREG_IF1_CONF_PREAMP_EN_SHIFT) & CFGREG_IF1_CONF_PREAMP_EN_MASK)                                                /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_LOAD_EN_BITS_SET(x)                                    ((x << CFGREG_IF1_CONF_LOAD_EN_SHIFT) & CFGREG_IF1_CONF_LOAD_EN_MASK)                                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_EN_BITS_SET(x)                                         ((x << CFGREG_IF1_CONF_EN_SHIFT) & CFGREG_IF1_CONF_EN_MASK)                                                              /*!<  IF1 Configuration Register Bits Set */

#define CFGREG_IF1_STAT_AGC_CTRL_BITS_SET(x)                                   ((x << CFGREG_IF1_STAT_AGC_CTRL_SHIFT) & CFGREG_IF1_STAT_AGC_CTRL_MASK)                                                  /*!<  IF1 Status Register Bits Set */

#define CFGREG_ADC1_CONF_CLK_CONF_BITS_SET(x)                                  ((x << CFGREG_ADC1_CONF_CLK_CONF_SHIFT) & CFGREG_ADC1_CONF_CLK_CONF_MASK)                                                /*!<  ADC1 Configuration Register Bits Set */
#define CFGREG_ADC1_CONF_SAH_EN_BITS_SET(x)                                    ((x << CFGREG_ADC1_CONF_SAH_EN_SHIFT) & CFGREG_ADC1_CONF_SAH_EN_MASK)                                                    /*!<  ADC1 Configuration Register Bits Set */
#define CFGREG_ADC1_CONF_ADC_EN_BITS_SET(x)                                    ((x << CFGREG_ADC1_CONF_ADC_EN_SHIFT) & CFGREG_ADC1_CONF_ADC_EN_MASK)                                                    /*!<  ADC1 Configuration Register Bits Set */

#define CFGREG_PLL5_CONF_TEST_EN_BITS_SET(x)                                   ((x << CFGREG_PLL5_CONF_TEST_EN_SHIFT) & CFGREG_PLL5_CONF_TEST_EN_MASK)                                                  /*!<  PLL5 Configuration Register Bits Set */
#define CFGREG_PLL5_CONF_FCW_BITS_SET(x)                                       ((x << CFGREG_PLL5_CONF_FCW_SHIFT) & CFGREG_PLL5_CONF_FCW_MASK)                                                          /*!<  PLL5 Configuration Register Bits Set */
#define CFGREG_PLL5_CONF_EN_BITS_SET(x)                                        ((x << CFGREG_PLL5_CONF_EN_SHIFT) & CFGREG_PLL5_CONF_EN_MASK)                                                            /*!<  PLL5 Configuration Register Bits Set */

#define CFGREG_PLL5TDC_CONF_SCALE_BITS_SET(x)                                  ((x << CFGREG_PLL5TDC_CONF_SCALE_SHIFT) & CFGREG_PLL5TDC_CONF_SCALE_MASK)                                                /*!<  PLL5 TDC Configuration Register Bits Set */
#define CFGREG_PLL5TDC_CONF_LOAD_BITS_SET(x)                                   ((x << CFGREG_PLL5TDC_CONF_LOAD_SHIFT) & CFGREG_PLL5TDC_CONF_LOAD_MASK)                                                  /*!<  PLL5 TDC Configuration Register Bits Set */

#define CFGREG_PLL5DCO_CONF_CTRL_PVT_BITS_SET(x)                               ((x << CFGREG_PLL5DCO_CONF_CTRL_PVT_SHIFT) & CFGREG_PLL5DCO_CONF_CTRL_PVT_MASK)                                          /*!<  PLL5 DCO Configuration Register Bits Set */
#define CFGREG_PLL5DCO_CONF_CTRL_FINE_BITS_SET(x)                              ((x << CFGREG_PLL5DCO_CONF_CTRL_FINE_SHIFT) & CFGREG_PLL5DCO_CONF_CTRL_FINE_MASK)                                        /*!<  PLL5 DCO Configuration Register Bits Set */
#define CFGREG_PLL5DCO_CONF_CTRL_LOAD_BITS_SET(x)                              ((x << CFGREG_PLL5DCO_CONF_CTRL_LOAD_SHIFT) & CFGREG_PLL5DCO_CONF_CTRL_LOAD_MASK)                                        /*!<  PLL5 DCO Configuration Register Bits Set */

#define CFGREG_PLL5_STAT_PHERR_BITS_SET(x)                                     ((x << CFGREG_PLL5_STAT_PHERR_SHIFT) & CFGREG_PLL5_STAT_PHERR_MASK)                                                      /*!<  PLL5 Status Register Bits Set */
#define CFGREG_PLL5_STAT_NDIV_BITS_SET(x)                                      ((x << CFGREG_PLL5_STAT_NDIV_SHIFT) & CFGREG_PLL5_STAT_NDIV_MASK)                                                        /*!<  PLL5 Status Register Bits Set */
#define CFGREG_PLL5_STAT_PHSEL_BITS_SET(x)                                     ((x << CFGREG_PLL5_STAT_PHSEL_SHIFT) & CFGREG_PLL5_STAT_PHSEL_MASK)                                                      /*!<  PLL5 Status Register Bits Set */
#define CFGREG_PLL5_STAT_LOCK_BITS_SET(x)                                      ((x << CFGREG_PLL5_STAT_LOCK_SHIFT) & CFGREG_PLL5_STAT_LOCK_MASK)                                                        /*!<  PLL5 Status Register Bits Set */

#define CFGREG_PLL5TDC_STAT_SCALE_BITS_SET(x)                                  ((x << CFGREG_PLL5TDC_STAT_SCALE_SHIFT) & CFGREG_PLL5TDC_STAT_SCALE_MASK)                                                /*!<  PLL5 TDC Status Register Bits Set */

#define CFGREG_PLL5DCO_STAT_CTRL_PVT_BITS_SET(x)                               ((x << CFGREG_PLL5DCO_STAT_CTRL_PVT_SHIFT) & CFGREG_PLL5DCO_STAT_CTRL_PVT_MASK)                                          /*!<  PLL5 TDC Status Register Bits Set */
#define CFGREG_PLL5DCO_STAT_CTRL_FINE_BITS_SET(x)                              ((x << CFGREG_PLL5DCO_STAT_CTRL_FINE_SHIFT) & CFGREG_PLL5DCO_STAT_CTRL_FINE_MASK)                                        /*!<  PLL5 TDC Status Register Bits Set */

#define CFGREG_IF5_CONF_LPF_CAL_BITS_SET(x)                                    ((x << CFGREG_IF5_CONF_LPF_CAL_SHIFT) & CFGREG_IF5_CONF_LPF_CAL_MASK)                                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_LPF_GAIN_BITS_SET(x)                                   ((x << CFGREG_IF5_CONF_LPF_GAIN_SHIFT) & CFGREG_IF5_CONF_LPF_GAIN_MASK)                                                  /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_LPF_BAND_BITS_SET(x)                                   ((x << CFGREG_IF5_CONF_LPF_BAND_SHIFT) & CFGREG_IF5_CONF_LPF_BAND_MASK)                                                  /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_LPF_EN_BITS_SET(x)                                     ((x << CFGREG_IF5_CONF_LPF_EN_SHIFT) & CFGREG_IF5_CONF_LPF_EN_MASK)                                                      /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PGA2_GAIN_BITS_SET(x)                                  ((x << CFGREG_IF5_CONF_PGA2_GAIN_SHIFT) & CFGREG_IF5_CONF_PGA2_GAIN_MASK)                                                /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PGA2_EN_BITS_SET(x)                                    ((x << CFGREG_IF5_CONF_PGA2_EN_SHIFT) & CFGREG_IF5_CONF_PGA2_EN_MASK)                                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PGA1_GAIN_BITS_SET(x)                                  ((x << CFGREG_IF5_CONF_PGA1_GAIN_SHIFT) & CFGREG_IF5_CONF_PGA1_GAIN_MASK)                                                /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PGA1_EN_BITS_SET(x)                                    ((x << CFGREG_IF5_CONF_PGA1_EN_SHIFT) & CFGREG_IF5_CONF_PGA1_EN_MASK)                                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PREAMP_EN_BITS_SET(x)                                  ((x << CFGREG_IF5_CONF_PREAMP_EN_SHIFT) & CFGREG_IF5_CONF_PREAMP_EN_MASK)                                                /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_LOAD_EN_BITS_SET(x)                                    ((x << CFGREG_IF5_CONF_LOAD_EN_SHIFT) & CFGREG_IF5_CONF_LOAD_EN_MASK)                                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_EN_BITS_SET(x)                                         ((x << CFGREG_IF5_CONF_EN_SHIFT) & CFGREG_IF5_CONF_EN_MASK)                                                              /*!<  IF5 Configuration Register Bits Set */

#define CFGREG_IF5_STAT_AGC_CTRL_BITS_SET(x)                                   ((x << CFGREG_IF5_STAT_AGC_CTRL_SHIFT) & CFGREG_IF5_STAT_AGC_CTRL_MASK)                                                  /*!<  IF5 status Register Bits Set */

#define CFGREG_ADC5_CONF_CLK_CONF_BITS_SET(x)                                  ((x << CFGREG_ADC5_CONF_CLK_CONF_SHIFT) & CFGREG_ADC5_CONF_CLK_CONF_MASK)                                                /*!<  ADC5 Configuration Register Bits Set */
#define CFGREG_ADC5_CONF_SAH_EN_BITS_SET(x)                                    ((x << CFGREG_ADC5_CONF_SAH_EN_SHIFT) & CFGREG_ADC5_CONF_SAH_EN_MASK)                                                    /*!<  ADC5 Configuration Register Bits Set */
#define CFGREG_ADC5_CONF_ADC_EN_BITS_SET(x)                                    ((x << CFGREG_ADC5_CONF_ADC_EN_SHIFT) & CFGREG_ADC5_CONF_ADC_EN_MASK)                                                    /*!<  ADC5 Configuration Register Bits Set */


/** Bits Get Helper Macros */

#define CFGREG_IRQMAP_IRQMAP_BITS_GET(x)                                       ((x & CFGREG_IRQMAP_IRQMAP_MASK) >> CFGREG_IRQMAP_IRQMAP_SHIFT)                                                          /*!<  Interrupt Mapping Register Bits Get */

#define CFGREG_UNLOCK_UNLOCK_KEY_BITS_GET(x)                                   ((x & CFGREG_UNLOCK_UNLOCK_KEY_MASK) >> CFGREG_UNLOCK_UNLOCK_KEY_SHIFT)                                                  /*!<  Unlock Register Bits Get */

#define CFGREG_IRQFLAGS_PLL_FAIL_BITS_GET(x)                                   ((x & CFGREG_IRQFLAGS_PLL_FAIL_MASK) >> CFGREG_IRQFLAGS_PLL_FAIL_SHIFT)                                                  /*!<  32kHz RTC Clock Interrupt Flags Bits Get */
#define CFGREG_IRQFLAGS_XTAL_CORE_FAIL_BITS_GET(x)                             ((x & CFGREG_IRQFLAGS_XTAL_CORE_FAIL_MASK) >> CFGREG_IRQFLAGS_XTAL_CORE_FAIL_SHIFT)                                      /*!<  32kHz RTC Clock Interrupt Flags Bits Get */
#define CFGREG_IRQFLAGS_XTAL_RTC_FAIL_BITS_GET(x)                              ((x & CFGREG_IRQFLAGS_XTAL_RTC_FAIL_MASK) >> CFGREG_IRQFLAGS_XTAL_RTC_FAIL_SHIFT)                                        /*!<  32kHz RTC Clock Interrupt Flags Bits Get */

#define CFGREG_RTCSTAT_RC_RTC_VAL_BITS_GET(x)                                  ((x & CFGREG_RTCSTAT_RC_RTC_VAL_MASK) >> CFGREG_RTCSTAT_RC_RTC_VAL_SHIFT)                                                /*!<  32kHz RTC Clock Status Bits Get */
#define CFGREG_RTCSTAT_RC_RTC_RDY_BITS_GET(x)                                  ((x & CFGREG_RTCSTAT_RC_RTC_RDY_MASK) >> CFGREG_RTCSTAT_RC_RTC_RDY_SHIFT)                                                /*!<  32kHz RTC Clock Status Bits Get */
#define CFGREG_RTCSTAT_CLK_RTC_SEL_BITS_GET(x)                                 ((x & CFGREG_RTCSTAT_CLK_RTC_SEL_MASK) >> CFGREG_RTCSTAT_CLK_RTC_SEL_SHIFT)                                              /*!<  32kHz RTC Clock Status Bits Get */

#define CFGREG_RTCCONF_RC_RTC_CAL_BITS_GET(x)                                  ((x & CFGREG_RTCCONF_RC_RTC_CAL_MASK) >> CFGREG_RTCCONF_RC_RTC_CAL_SHIFT)                                                /*!<  32kHz RTC Clock Configuration Bits Get */
#define CFGREG_RTCCONF_XTAL_RTC_SEL_BITS_GET(x)                                ((x & CFGREG_RTCCONF_XTAL_RTC_SEL_MASK) >> CFGREG_RTCCONF_XTAL_RTC_SEL_SHIFT)                                            /*!<  32kHz RTC Clock Configuration Bits Get */
#define CFGREG_RTCCONF_XTAL_RTC_TEST_BITS_GET(x)                               ((x & CFGREG_RTCCONF_XTAL_RTC_TEST_MASK) >> CFGREG_RTCCONF_XTAL_RTC_TEST_SHIFT)                                          /*!<  32kHz RTC Clock Configuration Bits Get */

#define CFGREG_COREFREQ_CLK_TEST_OUT_EN_BITS_GET(x)                            ((x & CFGREG_COREFREQ_CLK_TEST_OUT_EN_MASK) >> CFGREG_COREFREQ_CLK_TEST_OUT_EN_SHIFT)                                    /*!<  External XTAL Configuration Register Bits Get */
#define CFGREG_COREFREQ_CLK_RC_CORE_CAL_BITS_GET(x)                            ((x & CFGREG_COREFREQ_CLK_RC_CORE_CAL_MASK) >> CFGREG_COREFREQ_CLK_RC_CORE_CAL_SHIFT)                                    /*!<  External XTAL Configuration Register Bits Get */
#define CFGREG_COREFREQ_CLK_CLK_CORE_SEL_BITS_GET(x)                           ((x & CFGREG_COREFREQ_CLK_CLK_CORE_SEL_MASK) >> CFGREG_COREFREQ_CLK_CLK_CORE_SEL_SHIFT)                                  /*!<  External XTAL Configuration Register Bits Get */
#define CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_BITS_GET(x)                         ((x & CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_MASK) >> CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_SHIFT)                              /*!<  External XTAL Configuration Register Bits Get */

#define CFGREG_COREFREQ_PLL_PLL_VFB_EN_BITS_GET(x)                             ((x & CFGREG_COREFREQ_PLL_PLL_VFB_EN_MASK) >> CFGREG_COREFREQ_PLL_PLL_VFB_EN_SHIFT)                                      /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_PLL_VCONT_SF_BITS_GET(x)                           ((x & CFGREG_COREFREQ_PLL_PLL_VCONT_SF_MASK) >> CFGREG_COREFREQ_PLL_PLL_VCONT_SF_SHIFT)                                  /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_PLL_VCONT_EN_BITS_GET(x)                           ((x & CFGREG_COREFREQ_PLL_PLL_VCONT_EN_MASK) >> CFGREG_COREFREQ_PLL_PLL_VCONT_EN_SHIFT)                                  /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_PLL_TEST_BITS_GET(x)                               ((x & CFGREG_COREFREQ_PLL_PLL_TEST_MASK) >> CFGREG_COREFREQ_PLL_PLL_TEST_SHIFT)                                          /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_PLL_N_BITS_GET(x)                                  ((x & CFGREG_COREFREQ_PLL_PLL_N_MASK) >> CFGREG_COREFREQ_PLL_PLL_N_SHIFT)                                                /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_PLL_M_BITS_GET(x)                                  ((x & CFGREG_COREFREQ_PLL_PLL_M_MASK) >> CFGREG_COREFREQ_PLL_PLL_M_SHIFT)                                                /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_REF_SEL_BITS_GET(x)                                ((x & CFGREG_COREFREQ_PLL_REF_SEL_MASK) >> CFGREG_COREFREQ_PLL_REF_SEL_SHIFT)                                            /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_PLL_EN_BITS_GET(x)                                 ((x & CFGREG_COREFREQ_PLL_PLL_EN_MASK) >> CFGREG_COREFREQ_PLL_PLL_EN_SHIFT)                                              /*!<  PLL Configuration Register Bits Get */

#define CFGREG_COREFREQ_STAT_RC_CORE_VAL_BITS_GET(x)                           ((x & CFGREG_COREFREQ_STAT_RC_CORE_VAL_MASK) >> CFGREG_COREFREQ_STAT_RC_CORE_VAL_SHIFT)                                  /*!<  Core Clock Status Register Bits Get */
#define CFGREG_COREFREQ_STAT_RC_CORE_RDY_BITS_GET(x)                           ((x & CFGREG_COREFREQ_STAT_RC_CORE_RDY_MASK) >> CFGREG_COREFREQ_STAT_RC_CORE_RDY_SHIFT)                                  /*!<  Core Clock Status Register Bits Get */
#define CFGREG_COREFREQ_STAT_PLL_LOCK_BITS_GET(x)                              ((x & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK) >> CFGREG_COREFREQ_STAT_PLL_LOCK_SHIFT)                                        /*!<  Core Clock Status Register Bits Get */
#define CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_BITS_GET(x)                        ((x & CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_MASK) >> CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_SHIFT)                            /*!<  Core Clock Status Register Bits Get */
#define CFGREG_COREFREQ_STAT_CLK_CORE_SEL_BITS_GET(x)                          ((x & CFGREG_COREFREQ_STAT_CLK_CORE_SEL_MASK) >> CFGREG_COREFREQ_STAT_CLK_CORE_SEL_SHIFT)                                /*!<  Core Clock Status Register Bits Get */

#define CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_BITS_GET(x)                           ((x & CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_MASK) >> CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_SHIFT)                                  /*!<  GNSS-AFE Configuration Register Bits Get */
#define CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_BITS_GET(x)                          ((x & CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_MASK) >> CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_SHIFT)                                /*!<  GNSS-AFE Configuration Register Bits Get */

#define CFGREG_PM_CONF_PM_ITRIM_BITS_GET(x)                                    ((x & CFGREG_PM_CONF_PM_ITRIM_MASK) >> CFGREG_PM_CONF_PM_ITRIM_SHIFT)                                                    /*!<  PM GLOBAL Configuration Register Bits Get */
#define CFGREG_PM_CONF_PM_EN_BITS_GET(x)                                       ((x & CFGREG_PM_CONF_PM_EN_MASK) >> CFGREG_PM_CONF_PM_EN_SHIFT)                                                          /*!<  PM GLOBAL Configuration Register Bits Get */

#define CFGREG_PM_GNSSAFE1_CONF_IREG_SPARE1_BITS_GET(x)                        ((x & CFGREG_PM_GNSSAFE1_CONF_IREG_SPARE1_MASK) >> CFGREG_PM_GNSSAFE1_CONF_IREG_SPARE1_SHIFT)                            /*!<  PM GNSS-AFE1 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_TEST_BITS_GET(x)                          ((x & CFGREG_PM_GNSSAFE1_CONF_IREG_TEST_MASK) >> CFGREG_PM_GNSSAFE1_CONF_IREG_TEST_SHIFT)                                /*!<  PM GNSS-AFE1 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_PLL1_BITS_GET(x)                          ((x & CFGREG_PM_GNSSAFE1_CONF_IREG_PLL1_MASK) >> CFGREG_PM_GNSSAFE1_CONF_IREG_PLL1_SHIFT)                                /*!<  PM GNSS-AFE1 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_ADC1_BITS_GET(x)                          ((x & CFGREG_PM_GNSSAFE1_CONF_IREG_ADC1_MASK) >> CFGREG_PM_GNSSAFE1_CONF_IREG_ADC1_SHIFT)                                /*!<  PM GNSS-AFE1 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_IF1_BITS_GET(x)                           ((x & CFGREG_PM_GNSSAFE1_CONF_IREG_IF1_MASK) >> CFGREG_PM_GNSSAFE1_CONF_IREG_IF1_SHIFT)                                  /*!<  PM GNSS-AFE1 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_MIXER1_BITS_GET(x)                        ((x & CFGREG_PM_GNSSAFE1_CONF_IREG_MIXER1_MASK) >> CFGREG_PM_GNSSAFE1_CONF_IREG_MIXER1_SHIFT)                            /*!<  PM GNSS-AFE1 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_BALUN1_BITS_GET(x)                        ((x & CFGREG_PM_GNSSAFE1_CONF_IREG_BALUN1_MASK) >> CFGREG_PM_GNSSAFE1_CONF_IREG_BALUN1_SHIFT)                            /*!<  PM GNSS-AFE1 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE1_CONF_IREG_LNA1_BITS_GET(x)                          ((x & CFGREG_PM_GNSSAFE1_CONF_IREG_LNA1_MASK) >> CFGREG_PM_GNSSAFE1_CONF_IREG_LNA1_SHIFT)                                /*!<  PM GNSS-AFE1 Configuration Register Bits Get */

#define CFGREG_PM_GNSSAFE5_CONF_IREG_SPARE5_BITS_GET(x)                        ((x & CFGREG_PM_GNSSAFE5_CONF_IREG_SPARE5_MASK) >> CFGREG_PM_GNSSAFE5_CONF_IREG_SPARE5_SHIFT)                            /*!<  PM GNSS-AFE5 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_LNA15_BITS_GET(x)                         ((x & CFGREG_PM_GNSSAFE5_CONF_IREG_LNA15_MASK) >> CFGREG_PM_GNSSAFE5_CONF_IREG_LNA15_SHIFT)                              /*!<  PM GNSS-AFE5 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_PLL5_BITS_GET(x)                          ((x & CFGREG_PM_GNSSAFE5_CONF_IREG_PLL5_MASK) >> CFGREG_PM_GNSSAFE5_CONF_IREG_PLL5_SHIFT)                                /*!<  PM GNSS-AFE5 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_ADC5_BITS_GET(x)                          ((x & CFGREG_PM_GNSSAFE5_CONF_IREG_ADC5_MASK) >> CFGREG_PM_GNSSAFE5_CONF_IREG_ADC5_SHIFT)                                /*!<  PM GNSS-AFE5 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_IF5_BITS_GET(x)                           ((x & CFGREG_PM_GNSSAFE5_CONF_IREG_IF5_MASK) >> CFGREG_PM_GNSSAFE5_CONF_IREG_IF5_SHIFT)                                  /*!<  PM GNSS-AFE5 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_MIXER5_BITS_GET(x)                        ((x & CFGREG_PM_GNSSAFE5_CONF_IREG_MIXER5_MASK) >> CFGREG_PM_GNSSAFE5_CONF_IREG_MIXER5_SHIFT)                            /*!<  PM GNSS-AFE5 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_BALUN5_BITS_GET(x)                        ((x & CFGREG_PM_GNSSAFE5_CONF_IREG_BALUN5_MASK) >> CFGREG_PM_GNSSAFE5_CONF_IREG_BALUN5_SHIFT)                            /*!<  PM GNSS-AFE5 Configuration Register Bits Get */
#define CFGREG_PM_GNSSAFE5_CONF_IREG_LNA5_BITS_GET(x)                          ((x & CFGREG_PM_GNSSAFE5_CONF_IREG_LNA5_MASK) >> CFGREG_PM_GNSSAFE5_CONF_IREG_LNA5_SHIFT)                                /*!<  PM GNSS-AFE5 Configuration Register Bits Get */

#define CFGREG_DCDC_CONF_DCDC_TRIM_BITS_GET(x)                                 ((x & CFGREG_DCDC_CONF_DCDC_TRIM_MASK) >> CFGREG_DCDC_CONF_DCDC_TRIM_SHIFT)                                              /*!<  DCDC Configuration Register Bits Get */
#define CFGREG_DCDC_CONF_DCDC_EN_BITS_GET(x)                                   ((x & CFGREG_DCDC_CONF_DCDC_EN_MASK) >> CFGREG_DCDC_CONF_DCDC_EN_SHIFT)                                                  /*!<  DCDC Configuration Register Bits Get */

#define CFGREG_LNA1_CONF_LNA_TUNE_BITS_GET(x)                                  ((x & CFGREG_LNA1_CONF_LNA_TUNE_MASK) >> CFGREG_LNA1_CONF_LNA_TUNE_SHIFT)                                                /*!<  LNA1 Configuration Register Bits Get */
#define CFGREG_LNA1_CONF_EN_BITS_GET(x)                                        ((x & CFGREG_LNA1_CONF_EN_MASK) >> CFGREG_LNA1_CONF_EN_SHIFT)                                                            /*!<  LNA1 Configuration Register Bits Get */

#define CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_BITS_GET(x)                        ((x & CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_MASK) >> CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SHIFT)                            /*!<  BALUN and MIXER 1 Configuration Register Bits Get */
#define CFGREG_BALUN_MIXER1_CONF_BALUN_EN_BITS_GET(x)                          ((x & CFGREG_BALUN_MIXER1_CONF_BALUN_EN_MASK) >> CFGREG_BALUN_MIXER1_CONF_BALUN_EN_SHIFT)                                /*!<  BALUN and MIXER 1 Configuration Register Bits Get */
#define CFGREG_BALUN_MIXER1_CONF_MIXER_EN_BITS_GET(x)                          ((x & CFGREG_BALUN_MIXER1_CONF_MIXER_EN_MASK) >> CFGREG_BALUN_MIXER1_CONF_MIXER_EN_SHIFT)                                /*!<  BALUN and MIXER 1 Configuration Register Bits Get */

#define CFGREG_LNA5_CONF_LNA_TUNE_BITS_GET(x)                                  ((x & CFGREG_LNA5_CONF_LNA_TUNE_MASK) >> CFGREG_LNA5_CONF_LNA_TUNE_SHIFT)                                                /*!<  LNA5 Configuration Register Bits Get */
#define CFGREG_LNA5_CONF_EN_BITS_GET(x)                                        ((x & CFGREG_LNA5_CONF_EN_MASK) >> CFGREG_LNA5_CONF_EN_SHIFT)                                                            /*!<  LNA5 Configuration Register Bits Get */

#define CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_BITS_GET(x)                        ((x & CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_MASK) >> CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SHIFT)                            /*!<  BALUN and MIXER 5 Configuration Register Bits Get */
#define CFGREG_BALUN_MIXER5_CONF_BALUN_EN_BITS_GET(x)                          ((x & CFGREG_BALUN_MIXER5_CONF_BALUN_EN_MASK) >> CFGREG_BALUN_MIXER5_CONF_BALUN_EN_SHIFT)                                /*!<  BALUN and MIXER 5 Configuration Register Bits Get */
#define CFGREG_BALUN_MIXER5_CONF_MIXER_EN_BITS_GET(x)                          ((x & CFGREG_BALUN_MIXER5_CONF_MIXER_EN_MASK) >> CFGREG_BALUN_MIXER5_CONF_MIXER_EN_SHIFT)                                /*!<  BALUN and MIXER 5 Configuration Register Bits Get */

#define CFGREG_LNA15_TUNE_CONF_BAND5_TUNE_BITS_GET(x)                          ((x & CFGREG_LNA15_TUNE_CONF_BAND5_TUNE_MASK) >> CFGREG_LNA15_TUNE_CONF_BAND5_TUNE_SHIFT)                                /*!<  LNA15 Tuning Configuration Register Bits Get */
#define CFGREG_LNA15_TUNE_CONF_BAND1_TUNE_BITS_GET(x)                          ((x & CFGREG_LNA15_TUNE_CONF_BAND1_TUNE_MASK) >> CFGREG_LNA15_TUNE_CONF_BAND1_TUNE_SHIFT)                                /*!<  LNA15 Tuning Configuration Register Bits Get */

#define CFGREG_LNA15_CONF_SPARE_TUNE_BITS_GET(x)                               ((x & CFGREG_LNA15_CONF_SPARE_TUNE_MASK) >> CFGREG_LNA15_CONF_SPARE_TUNE_SHIFT)                                          /*!<  LNA15 Configuration Register Bits Get */
#define CFGREG_LNA15_CONF_EN_BITS_GET(x)                                       ((x & CFGREG_LNA15_CONF_EN_MASK) >> CFGREG_LNA15_CONF_EN_SHIFT)                                                          /*!<  LNA15 Configuration Register Bits Get */

#define CFGREG_PROBE_IF1_CONF_PROBEB_SELECT_BITS_GET(x)                        ((x & CFGREG_PROBE_IF1_CONF_PROBEB_SELECT_MASK) >> CFGREG_PROBE_IF1_CONF_PROBEB_SELECT_SHIFT)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF1_CONF_PROBEB_SOURCE_BITS_GET(x)                        ((x & CFGREG_PROBE_IF1_CONF_PROBEB_SOURCE_MASK) >> CFGREG_PROBE_IF1_CONF_PROBEB_SOURCE_SHIFT)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF1_CONF_PROBEB_EN_BITS_GET(x)                            ((x & CFGREG_PROBE_IF1_CONF_PROBEB_EN_MASK) >> CFGREG_PROBE_IF1_CONF_PROBEB_EN_SHIFT)                                    /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF1_CONF_PROBEA_SELECT_BITS_GET(x)                        ((x & CFGREG_PROBE_IF1_CONF_PROBEA_SELECT_MASK) >> CFGREG_PROBE_IF1_CONF_PROBEA_SELECT_SHIFT)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF1_CONF_PROBEA_SOURCE_BITS_GET(x)                        ((x & CFGREG_PROBE_IF1_CONF_PROBEA_SOURCE_MASK) >> CFGREG_PROBE_IF1_CONF_PROBEA_SOURCE_SHIFT)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF1_CONF_PROBEA_EN_BITS_GET(x)                            ((x & CFGREG_PROBE_IF1_CONF_PROBEA_EN_MASK) >> CFGREG_PROBE_IF1_CONF_PROBEA_EN_SHIFT)                                    /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */

#define CFGREG_PROBE_IF5_CONF_NRST_TEST_BITS_GET(x)                            ((x & CFGREG_PROBE_IF5_CONF_NRST_TEST_MASK) >> CFGREG_PROBE_IF5_CONF_NRST_TEST_SHIFT)                                    /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF5_CONF_PLL15FB_SEL_BITS_GET(x)                          ((x & CFGREG_PROBE_IF5_CONF_PLL15FB_SEL_MASK) >> CFGREG_PROBE_IF5_CONF_PLL15FB_SEL_SHIFT)                                /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF5_CONF_PLL_VCONT_EN_BITS_GET(x)                         ((x & CFGREG_PROBE_IF5_CONF_PLL_VCONT_EN_MASK) >> CFGREG_PROBE_IF5_CONF_PLL_VCONT_EN_SHIFT)                              /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF5_CONF_IBIAS_TEST_EN_BITS_GET(x)                        ((x & CFGREG_PROBE_IF5_CONF_IBIAS_TEST_EN_MASK) >> CFGREG_PROBE_IF5_CONF_IBIAS_TEST_EN_SHIFT)                            /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF5_CONF_PROBEB_SELECT_BITS_GET(x)                        ((x & CFGREG_PROBE_IF5_CONF_PROBEB_SELECT_MASK) >> CFGREG_PROBE_IF5_CONF_PROBEB_SELECT_SHIFT)                            /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF5_CONF_PROBEB_SOURCE_BITS_GET(x)                        ((x & CFGREG_PROBE_IF5_CONF_PROBEB_SOURCE_MASK) >> CFGREG_PROBE_IF5_CONF_PROBEB_SOURCE_SHIFT)                            /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF5_CONF_PROBEB_EN_BITS_GET(x)                            ((x & CFGREG_PROBE_IF5_CONF_PROBEB_EN_MASK) >> CFGREG_PROBE_IF5_CONF_PROBEB_EN_SHIFT)                                    /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF5_CONF_PROBEA_SELECT_BITS_GET(x)                        ((x & CFGREG_PROBE_IF5_CONF_PROBEA_SELECT_MASK) >> CFGREG_PROBE_IF5_CONF_PROBEA_SELECT_SHIFT)                            /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF5_CONF_PROBEA_SOURCE_BITS_GET(x)                        ((x & CFGREG_PROBE_IF5_CONF_PROBEA_SOURCE_MASK) >> CFGREG_PROBE_IF5_CONF_PROBEA_SOURCE_SHIFT)                            /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_IF5_CONF_PROBEA_EN_BITS_GET(x)                            ((x & CFGREG_PROBE_IF5_CONF_PROBEA_EN_MASK) >> CFGREG_PROBE_IF5_CONF_PROBEA_EN_SHIFT)                                    /*!<  GNSS-AFE IF5 analog probing Configuration Register Bits Get */

#define CFGREG_PLL1_CONF_TEST_EN_BITS_GET(x)                                   ((x & CFGREG_PLL1_CONF_TEST_EN_MASK) >> CFGREG_PLL1_CONF_TEST_EN_SHIFT)                                                  /*!<  PLL1 Configuration Register Bits Get */
#define CFGREG_PLL1_CONF_FCW_BITS_GET(x)                                       ((x & CFGREG_PLL1_CONF_FCW_MASK) >> CFGREG_PLL1_CONF_FCW_SHIFT)                                                          /*!<  PLL1 Configuration Register Bits Get */
#define CFGREG_PLL1_CONF_EN_BITS_GET(x)                                        ((x & CFGREG_PLL1_CONF_EN_MASK) >> CFGREG_PLL1_CONF_EN_SHIFT)                                                            /*!<  PLL1 Configuration Register Bits Get */

#define CFGREG_PLL1TDC_CONF_SCALE_BITS_GET(x)                                  ((x & CFGREG_PLL1TDC_CONF_SCALE_MASK) >> CFGREG_PLL1TDC_CONF_SCALE_SHIFT)                                                /*!<  PLL1 TDC Configuration Register Bits Get */
#define CFGREG_PLL1TDC_CONF_LOAD_BITS_GET(x)                                   ((x & CFGREG_PLL1TDC_CONF_LOAD_MASK) >> CFGREG_PLL1TDC_CONF_LOAD_SHIFT)                                                  /*!<  PLL1 TDC Configuration Register Bits Get */

#define CFGREG_PLL1DCO_CONF_CTRL_PVT_BITS_GET(x)                               ((x & CFGREG_PLL1DCO_CONF_CTRL_PVT_MASK) >> CFGREG_PLL1DCO_CONF_CTRL_PVT_SHIFT)                                          /*!<  PLL1 DCO Configuration Register Bits Get */
#define CFGREG_PLL1DCO_CONF_CTRL_FINE_BITS_GET(x)                              ((x & CFGREG_PLL1DCO_CONF_CTRL_FINE_MASK) >> CFGREG_PLL1DCO_CONF_CTRL_FINE_SHIFT)                                        /*!<  PLL1 DCO Configuration Register Bits Get */
#define CFGREG_PLL1DCO_CONF_CTRL_LOAD_BITS_GET(x)                              ((x & CFGREG_PLL1DCO_CONF_CTRL_LOAD_MASK) >> CFGREG_PLL1DCO_CONF_CTRL_LOAD_SHIFT)                                        /*!<  PLL1 DCO Configuration Register Bits Get */

#define CFGREG_PLL1_STAT_PHERR_BITS_GET(x)                                     ((x & CFGREG_PLL1_STAT_PHERR_MASK) >> CFGREG_PLL1_STAT_PHERR_SHIFT)                                                      /*!<  PLL1 Status Register Bits Get */
#define CFGREG_PLL1_STAT_NDIV_BITS_GET(x)                                      ((x & CFGREG_PLL1_STAT_NDIV_MASK) >> CFGREG_PLL1_STAT_NDIV_SHIFT)                                                        /*!<  PLL1 Status Register Bits Get */
#define CFGREG_PLL1_STAT_PHSEL_BITS_GET(x)                                     ((x & CFGREG_PLL1_STAT_PHSEL_MASK) >> CFGREG_PLL1_STAT_PHSEL_SHIFT)                                                      /*!<  PLL1 Status Register Bits Get */
#define CFGREG_PLL1_STAT_LOCK_BITS_GET(x)                                      ((x & CFGREG_PLL1_STAT_LOCK_MASK) >> CFGREG_PLL1_STAT_LOCK_SHIFT)                                                        /*!<  PLL1 Status Register Bits Get */

#define CFGREG_PLL1TDC_STAT_SCALE_BITS_GET(x)                                  ((x & CFGREG_PLL1TDC_STAT_SCALE_MASK) >> CFGREG_PLL1TDC_STAT_SCALE_SHIFT)                                                /*!<  PLL1 TDC Status Register Bits Get */

#define CFGREG_PLL1DCO_STAT_CTRL_PVT_BITS_GET(x)                               ((x & CFGREG_PLL1DCO_STAT_CTRL_PVT_MASK) >> CFGREG_PLL1DCO_STAT_CTRL_PVT_SHIFT)                                          /*!<  PLL1 TDC Status Register Bits Get */
#define CFGREG_PLL1DCO_STAT_CTRL_FINE_BITS_GET(x)                              ((x & CFGREG_PLL1DCO_STAT_CTRL_FINE_MASK) >> CFGREG_PLL1DCO_STAT_CTRL_FINE_SHIFT)                                        /*!<  PLL1 TDC Status Register Bits Get */

#define CFGREG_IF1_CONF_LPF_CAL_BITS_GET(x)                                    ((x & CFGREG_IF1_CONF_LPF_CAL_MASK) >> CFGREG_IF1_CONF_LPF_CAL_SHIFT)                                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_LPF_GAIN_BITS_GET(x)                                   ((x & CFGREG_IF1_CONF_LPF_GAIN_MASK) >> CFGREG_IF1_CONF_LPF_GAIN_SHIFT)                                                  /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_LPF_BAND_BITS_GET(x)                                   ((x & CFGREG_IF1_CONF_LPF_BAND_MASK) >> CFGREG_IF1_CONF_LPF_BAND_SHIFT)                                                  /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_LPF_EN_BITS_GET(x)                                     ((x & CFGREG_IF1_CONF_LPF_EN_MASK) >> CFGREG_IF1_CONF_LPF_EN_SHIFT)                                                      /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PGA2_GAIN_BITS_GET(x)                                  ((x & CFGREG_IF1_CONF_PGA2_GAIN_MASK) >> CFGREG_IF1_CONF_PGA2_GAIN_SHIFT)                                                /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PGA2_EN_BITS_GET(x)                                    ((x & CFGREG_IF1_CONF_PGA2_EN_MASK) >> CFGREG_IF1_CONF_PGA2_EN_SHIFT)                                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PGA1_GAIN_BITS_GET(x)                                  ((x & CFGREG_IF1_CONF_PGA1_GAIN_MASK) >> CFGREG_IF1_CONF_PGA1_GAIN_SHIFT)                                                /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PGA1_EN_BITS_GET(x)                                    ((x & CFGREG_IF1_CONF_PGA1_EN_MASK) >> CFGREG_IF1_CONF_PGA1_EN_SHIFT)                                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PREAMP_EN_BITS_GET(x)                                  ((x & CFGREG_IF1_CONF_PREAMP_EN_MASK) >> CFGREG_IF1_CONF_PREAMP_EN_SHIFT)                                                /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_LOAD_EN_BITS_GET(x)                                    ((x & CFGREG_IF1_CONF_LOAD_EN_MASK) >> CFGREG_IF1_CONF_LOAD_EN_SHIFT)                                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_EN_BITS_GET(x)                                         ((x & CFGREG_IF1_CONF_EN_MASK) >> CFGREG_IF1_CONF_EN_SHIFT)                                                              /*!<  IF1 Configuration Register Bits Get */

#define CFGREG_IF1_STAT_AGC_CTRL_BITS_GET(x)                                   ((x & CFGREG_IF1_STAT_AGC_CTRL_MASK) >> CFGREG_IF1_STAT_AGC_CTRL_SHIFT)                                                  /*!<  IF1 Status Register Bits Get */

#define CFGREG_ADC1_CONF_CLK_CONF_BITS_GET(x)                                  ((x & CFGREG_ADC1_CONF_CLK_CONF_MASK) >> CFGREG_ADC1_CONF_CLK_CONF_SHIFT)                                                /*!<  ADC1 Configuration Register Bits Get */
#define CFGREG_ADC1_CONF_SAH_EN_BITS_GET(x)                                    ((x & CFGREG_ADC1_CONF_SAH_EN_MASK) >> CFGREG_ADC1_CONF_SAH_EN_SHIFT)                                                    /*!<  ADC1 Configuration Register Bits Get */
#define CFGREG_ADC1_CONF_ADC_EN_BITS_GET(x)                                    ((x & CFGREG_ADC1_CONF_ADC_EN_MASK) >> CFGREG_ADC1_CONF_ADC_EN_SHIFT)                                                    /*!<  ADC1 Configuration Register Bits Get */

#define CFGREG_PLL5_CONF_TEST_EN_BITS_GET(x)                                   ((x & CFGREG_PLL5_CONF_TEST_EN_MASK) >> CFGREG_PLL5_CONF_TEST_EN_SHIFT)                                                  /*!<  PLL5 Configuration Register Bits Get */
#define CFGREG_PLL5_CONF_FCW_BITS_GET(x)                                       ((x & CFGREG_PLL5_CONF_FCW_MASK) >> CFGREG_PLL5_CONF_FCW_SHIFT)                                                          /*!<  PLL5 Configuration Register Bits Get */
#define CFGREG_PLL5_CONF_EN_BITS_GET(x)                                        ((x & CFGREG_PLL5_CONF_EN_MASK) >> CFGREG_PLL5_CONF_EN_SHIFT)                                                            /*!<  PLL5 Configuration Register Bits Get */

#define CFGREG_PLL5TDC_CONF_SCALE_BITS_GET(x)                                  ((x & CFGREG_PLL5TDC_CONF_SCALE_MASK) >> CFGREG_PLL5TDC_CONF_SCALE_SHIFT)                                                /*!<  PLL5 TDC Configuration Register Bits Get */
#define CFGREG_PLL5TDC_CONF_LOAD_BITS_GET(x)                                   ((x & CFGREG_PLL5TDC_CONF_LOAD_MASK) >> CFGREG_PLL5TDC_CONF_LOAD_SHIFT)                                                  /*!<  PLL5 TDC Configuration Register Bits Get */

#define CFGREG_PLL5DCO_CONF_CTRL_PVT_BITS_GET(x)                               ((x & CFGREG_PLL5DCO_CONF_CTRL_PVT_MASK) >> CFGREG_PLL5DCO_CONF_CTRL_PVT_SHIFT)                                          /*!<  PLL5 DCO Configuration Register Bits Get */
#define CFGREG_PLL5DCO_CONF_CTRL_FINE_BITS_GET(x)                              ((x & CFGREG_PLL5DCO_CONF_CTRL_FINE_MASK) >> CFGREG_PLL5DCO_CONF_CTRL_FINE_SHIFT)                                        /*!<  PLL5 DCO Configuration Register Bits Get */
#define CFGREG_PLL5DCO_CONF_CTRL_LOAD_BITS_GET(x)                              ((x & CFGREG_PLL5DCO_CONF_CTRL_LOAD_MASK) >> CFGREG_PLL5DCO_CONF_CTRL_LOAD_SHIFT)                                        /*!<  PLL5 DCO Configuration Register Bits Get */

#define CFGREG_PLL5_STAT_PHERR_BITS_GET(x)                                     ((x & CFGREG_PLL5_STAT_PHERR_MASK) >> CFGREG_PLL5_STAT_PHERR_SHIFT)                                                      /*!<  PLL5 Status Register Bits Get */
#define CFGREG_PLL5_STAT_NDIV_BITS_GET(x)                                      ((x & CFGREG_PLL5_STAT_NDIV_MASK) >> CFGREG_PLL5_STAT_NDIV_SHIFT)                                                        /*!<  PLL5 Status Register Bits Get */
#define CFGREG_PLL5_STAT_PHSEL_BITS_GET(x)                                     ((x & CFGREG_PLL5_STAT_PHSEL_MASK) >> CFGREG_PLL5_STAT_PHSEL_SHIFT)                                                      /*!<  PLL5 Status Register Bits Get */
#define CFGREG_PLL5_STAT_LOCK_BITS_GET(x)                                      ((x & CFGREG_PLL5_STAT_LOCK_MASK) >> CFGREG_PLL5_STAT_LOCK_SHIFT)                                                        /*!<  PLL5 Status Register Bits Get */

#define CFGREG_PLL5TDC_STAT_SCALE_BITS_GET(x)                                  ((x & CFGREG_PLL5TDC_STAT_SCALE_MASK) >> CFGREG_PLL5TDC_STAT_SCALE_SHIFT)                                                /*!<  PLL5 TDC Status Register Bits Get */

#define CFGREG_PLL5DCO_STAT_CTRL_PVT_BITS_GET(x)                               ((x & CFGREG_PLL5DCO_STAT_CTRL_PVT_MASK) >> CFGREG_PLL5DCO_STAT_CTRL_PVT_SHIFT)                                          /*!<  PLL5 TDC Status Register Bits Get */
#define CFGREG_PLL5DCO_STAT_CTRL_FINE_BITS_GET(x)                              ((x & CFGREG_PLL5DCO_STAT_CTRL_FINE_MASK) >> CFGREG_PLL5DCO_STAT_CTRL_FINE_SHIFT)                                        /*!<  PLL5 TDC Status Register Bits Get */

#define CFGREG_IF5_CONF_LPF_CAL_BITS_GET(x)                                    ((x & CFGREG_IF5_CONF_LPF_CAL_MASK) >> CFGREG_IF5_CONF_LPF_CAL_SHIFT)                                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_LPF_GAIN_BITS_GET(x)                                   ((x & CFGREG_IF5_CONF_LPF_GAIN_MASK) >> CFGREG_IF5_CONF_LPF_GAIN_SHIFT)                                                  /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_LPF_BAND_BITS_GET(x)                                   ((x & CFGREG_IF5_CONF_LPF_BAND_MASK) >> CFGREG_IF5_CONF_LPF_BAND_SHIFT)                                                  /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_LPF_EN_BITS_GET(x)                                     ((x & CFGREG_IF5_CONF_LPF_EN_MASK) >> CFGREG_IF5_CONF_LPF_EN_SHIFT)                                                      /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PGA2_GAIN_BITS_GET(x)                                  ((x & CFGREG_IF5_CONF_PGA2_GAIN_MASK) >> CFGREG_IF5_CONF_PGA2_GAIN_SHIFT)                                                /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PGA2_EN_BITS_GET(x)                                    ((x & CFGREG_IF5_CONF_PGA2_EN_MASK) >> CFGREG_IF5_CONF_PGA2_EN_SHIFT)                                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PGA1_GAIN_BITS_GET(x)                                  ((x & CFGREG_IF5_CONF_PGA1_GAIN_MASK) >> CFGREG_IF5_CONF_PGA1_GAIN_SHIFT)                                                /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PGA1_EN_BITS_GET(x)                                    ((x & CFGREG_IF5_CONF_PGA1_EN_MASK) >> CFGREG_IF5_CONF_PGA1_EN_SHIFT)                                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PREAMP_EN_BITS_GET(x)                                  ((x & CFGREG_IF5_CONF_PREAMP_EN_MASK) >> CFGREG_IF5_CONF_PREAMP_EN_SHIFT)                                                /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_LOAD_EN_BITS_GET(x)                                    ((x & CFGREG_IF5_CONF_LOAD_EN_MASK) >> CFGREG_IF5_CONF_LOAD_EN_SHIFT)                                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_EN_BITS_GET(x)                                         ((x & CFGREG_IF5_CONF_EN_MASK) >> CFGREG_IF5_CONF_EN_SHIFT)                                                              /*!<  IF5 Configuration Register Bits Get */

#define CFGREG_IF5_STAT_AGC_CTRL_BITS_GET(x)                                   ((x & CFGREG_IF5_STAT_AGC_CTRL_MASK) >> CFGREG_IF5_STAT_AGC_CTRL_SHIFT)                                                  /*!<  IF5 status Register Bits Get */

#define CFGREG_ADC5_CONF_CLK_CONF_BITS_GET(x)                                  ((x & CFGREG_ADC5_CONF_CLK_CONF_MASK) >> CFGREG_ADC5_CONF_CLK_CONF_SHIFT)                                                /*!<  ADC5 Configuration Register Bits Get */
#define CFGREG_ADC5_CONF_SAH_EN_BITS_GET(x)                                    ((x & CFGREG_ADC5_CONF_SAH_EN_MASK) >> CFGREG_ADC5_CONF_SAH_EN_SHIFT)                                                    /*!<  ADC5 Configuration Register Bits Get */
#define CFGREG_ADC5_CONF_ADC_EN_BITS_GET(x)                                    ((x & CFGREG_ADC5_CONF_ADC_EN_MASK) >> CFGREG_ADC5_CONF_ADC_EN_SHIFT)                                                    /*!<  ADC5 Configuration Register Bits Get */

/** @} */

#endif /* __CFG_REGS_H */
/** @} */
