/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2020-02-18 18:08:25 +0100 (wto, 18 lut 2020) $
* $Revision: 526 $
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
    uint32_t CFGREG_PMU_CONF;
    uint32_t CFGREG_PMU_STAT;
    uint32_t CFGREG_RTCSTAT;
    uint32_t CFGREG_RTCCONF;
    uint32_t CFGREG_COREFREQ_CLK;
    uint32_t CFGREG_COREFREQ_PLL;
    uint32_t CFGREG_COREFREQ_STAT;
    uint32_t CFGREG_GNSSAFE_CONF;
    uint32_t CFGREG_PM_STAT;
    uint32_t CFGREG_PM_CONF;
    uint32_t CFGREG_LNA15_STAT;
    uint32_t CFGREG_LNA15_TUNE_STAT;
    uint32_t CFGREG_LNA15_CONF;
    uint32_t CFGREG_LNA15_TUNE_CONF;
    uint32_t CFGREG_BALUN_MIXER1_CONF;
    uint32_t CFGREG_BALUN_MIXER5_CONF;
    uint32_t CFGREG_PROBE_CONF;
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
    uint32_t CFGREG_SPARE_CONF;
    uint32_t CFGREG_SPARE_STAT;
    uint32_t CFGREG_GNSSAFE_TEST_CONF;
    uint32_t CFGREG_GNSSAFE_TEST_STAT;
} cfg_regs_t;

static volatile cfg_regs_t * const CFG_REGS_PTR = (cfg_regs_t*)AMBA_REG_BASE;


/** Registers Default Values */
enum
{
     CFGREG_IRQMAP_DEF                                            = 0x00000000,  /*!<  Interrupt Mapping Register Default Value */
     CFGREG_UNLOCK_DEF                                            = 0x0000A55A,  /*!<  Unlock Register Default Value */
     CFGREG_IRQFLAGS_DEF                                          = 0x00000000,  /*!<  32kHz RTC Clock Interrupt Flags Default Value */
     CFGREG_PMU_CONF_DEF                                          = 0x0000001E,  /*!<  Power Management Unit Configuration Default Value */
     CFGREG_PMU_STAT_DEF                                          = 0x00000000,  /*!<  Power Management Unit Status Default Value */
     CFGREG_RTCSTAT_DEF                                           = 0x00000000,  /*!<  32kHz RTC Clock Status Default Value */
     CFGREG_RTCCONF_DEF                                           = 0x00000000,  /*!<  32kHz RTC Clock Configuration Default Value */
     CFGREG_COREFREQ_CLK_DEF                                      = 0x00000002,  /*!<  External XTAL Configuration Register Default Value */
     CFGREG_COREFREQ_PLL_DEF                                      = 0x00000080,  /*!<  PLL Configuration Register Default Value */
     CFGREG_COREFREQ_STAT_DEF                                     = 0x00000000,  /*!<  Core Clock Status Register Default Value */
     CFGREG_GNSSAFE_CONF_DEF                                      = 0x00000000,  /*!<  GNSS-AFE Configuration Register Default Value */
     CFGREG_PM_STAT_DEF                                           = 0x00000000,  /*!<  GNSS-AFE PM Status Register Default Value */
     CFGREG_PM_CONF_DEF                                           = 0x00000820,  /*!<  GNSS-AFE PM Configuration Register Default Value */
     CFGREG_LNA15_STAT_DEF                                        = 0x00000000,  /*!<  LNA15 Status Register Default Value */
     CFGREG_LNA15_TUNE_STAT_DEF                                   = 0x00000000,  /*!<  LNA15 Tune Status Register Default Value */
     CFGREG_LNA15_CONF_DEF                                        = 0x00402000,  /*!<  LNA15 Configuration Register Default Value */
     CFGREG_LNA15_TUNE_CONF_DEF                                   = 0x10001000,  /*!<  LNA15 Configuration Register Default Value */
     CFGREG_BALUN_MIXER1_CONF_DEF                                 = 0x00000018,  /*!<  BALUN and MIXER 1 Configuration Register Default Value */
     CFGREG_BALUN_MIXER5_CONF_DEF                                 = 0x00000018,  /*!<  BALUN and MIXER 5 Configuration Register Default Value */
     CFGREG_PROBE_CONF_DEF                                        = 0x00000000,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Default Value */
     CFGREG_PLL1_CONF_DEF                                         = 0x00C46A7E,  /*!<  PLL1 Configuration Register Default Value */
     CFGREG_PLL1TDC_CONF_DEF                                      = 0x00012000,  /*!<  PLL1 TDC Configuration Register Default Value */
     CFGREG_PLL1DCO_CONF_DEF                                      = 0x00004000,  /*!<  PLL1 DCO Configuration Register Default Value */
     CFGREG_PLL1_STAT_DEF                                         = 0x00000000,  /*!<  PLL1 Status Register Default Value */
     CFGREG_PLL1TDC_STAT_DEF                                      = 0x00000000,  /*!<  PLL1 TDC Status Register Default Value */
     CFGREG_PLL1DCO_STAT_DEF                                      = 0x00000000,  /*!<  PLL1 TDC Status Register Default Value */
     CFGREG_IF1_CONF_DEF                                          = 0x02C04020,  /*!<  IF1 Configuration Register Default Value */
     CFGREG_IF1_STAT_DEF                                          = 0x00000000,  /*!<  IF1 Status Register Default Value */
     CFGREG_ADC1_CONF_DEF                                         = 0x00000000,  /*!<  ADC1 Configuration Register Default Value */
     CFGREG_PLL5_CONF_DEF                                         = 0x00C46A7E,  /*!<  PLL5 Configuration Register Default Value */
     CFGREG_PLL5TDC_CONF_DEF                                      = 0x00012000,  /*!<  PLL5 TDC Configuration Register Default Value */
     CFGREG_PLL5DCO_CONF_DEF                                      = 0x00004000,  /*!<  PLL5 DCO Configuration Register Default Value */
     CFGREG_PLL5_STAT_DEF                                         = 0x00000000,  /*!<  PLL5 Status Register Default Value */
     CFGREG_PLL5TDC_STAT_DEF                                      = 0x00000000,  /*!<  PLL5 TDC Status Register Default Value */
     CFGREG_PLL5DCO_STAT_DEF                                      = 0x00000000,  /*!<  PLL5 TDC Status Register Default Value */
     CFGREG_IF5_CONF_DEF                                          = 0x00C04020,  /*!<  IF5 Configuration Register Default Value */
     CFGREG_IF5_STAT_DEF                                          = 0x00000000,  /*!<  IF5 Status Register Default Value */
     CFGREG_ADC5_CONF_DEF                                         = 0x00000000,  /*!<  ADC5 Configuration Register Default Value */
     CFGREG_SPARE_CONF_DEF                                        = 0x00000000,  /*!<  SPARE Configuration Register Default Value */
     CFGREG_SPARE_STAT_DEF                                        = 0x00000000,  /*!<  SPARE Configuration Register Default Value */
     CFGREG_GNSSAFE_TEST_CONF_DEF                                 = 0x00000000,  /*!<  TEST Configuration Register Default Value */
     CFGREG_GNSSAFE_TEST_STAT_DEF                                 = 0x00000000,  /*!<  TEST Configuration Register Default Value */
};

/** Registers Masks */
enum
{

     CFGREG_IRQMAP_IRQMAP_MASK                                    = 0x0000FFFE,  /*!<  Interrupt Mapping Register Mask Value */

     CFGREG_UNLOCK_UNLOCK_KEY_MASK                                = 0x0000FFFF,  /*!<  Unlock Register Mask Value */

     CFGREG_IRQFLAGS_PLL_FAIL_MASK                                = 0x00000004,  /*!<  32kHz RTC Clock Interrupt Flags Mask Value */
     CFGREG_IRQFLAGS_XTAL_CORE_FAIL_MASK                          = 0x00000002,  /*!<  32kHz RTC Clock Interrupt Flags Mask Value */
     CFGREG_IRQFLAGS_XTAL_RTC_FAIL_MASK                           = 0x00000001,  /*!<  32kHz RTC Clock Interrupt Flags Mask Value */

     CFGREG_PMU_CONF_IREF_CAL_EN_MASK                             = 0x00000400,  /*!<  Power Management Unit Configuration Mask Value */
     CFGREG_PMU_CONF_IREF_TRIM_VAL_SRC_MASK                       = 0x00000200,  /*!<  Power Management Unit Configuration Mask Value */
     CFGREG_PMU_CONF_IREF_TRIM_VAL_MASK                           = 0x000001FE,  /*!<  Power Management Unit Configuration Mask Value */
     CFGREG_PMU_CONF_IREF_TRIM_EN_MASK                            = 0x00000001,  /*!<  Power Management Unit Configuration Mask Value */

     CFGREG_PMU_STAT_IREF_TRIM_VAL_MASK                           = 0x000001FE,  /*!<  Power Management Unit Status Mask Value */
     CFGREG_PMU_STAT_IREF_CAL_RDY_MASK                            = 0x00000001,  /*!<  Power Management Unit Status Mask Value */

     CFGREG_RTCSTAT_RC_RTC_VAL_MASK                               = 0x000001FC,  /*!<  32kHz RTC Clock Status Mask Value */
     CFGREG_RTCSTAT_RC_RTC_RDY_MASK                               = 0x00000002,  /*!<  32kHz RTC Clock Status Mask Value */
     CFGREG_RTCSTAT_CLK_RTC_SEL_MASK                              = 0x00000001,  /*!<  32kHz RTC Clock Status Mask Value */

     CFGREG_RTCCONF_RC_RTC_VAL_SRC_MASK                           = 0x00000400,  /*!<  32kHz RTC Clock Configuration Mask Value */
     CFGREG_RTCCONF_RC_RTC_VAL_MASK                               = 0x000003F8,  /*!<  32kHz RTC Clock Configuration Mask Value */
     CFGREG_RTCCONF_RC_RTC_CAL_MASK                               = 0x00000004,  /*!<  32kHz RTC Clock Configuration Mask Value */
     CFGREG_RTCCONF_XTAL_RTC_SEL_MASK                             = 0x00000002,  /*!<  32kHz RTC Clock Configuration Mask Value */
     CFGREG_RTCCONF_XTAL_RTC_TEST_MASK                            = 0x00000001,  /*!<  32kHz RTC Clock Configuration Mask Value */

     CFGREG_COREFREQ_CLK_TEST_OUT_EN_MASK                         = 0x00000800,  /*!<  External XTAL Configuration Register Mask Value */
     CFGREG_COREFREQ_CLK_RC_CORE_VAL_SRC_MASK                     = 0x00000400,  /*!<  External XTAL Configuration Register Mask Value */
     CFGREG_COREFREQ_CLK_RC_CORE_VAL_MASK                         = 0x000003F0,  /*!<  External XTAL Configuration Register Mask Value */
     CFGREG_COREFREQ_CLK_RC_CORE_CAL_MASK                         = 0x00000008,  /*!<  External XTAL Configuration Register Mask Value */
     CFGREG_COREFREQ_CLK_CORE_SEL_MASK                            = 0x00000006,  /*!<  External XTAL Configuration Register Mask Value */
     CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_MASK                      = 0x00000001,  /*!<  External XTAL Configuration Register Mask Value */

     CFGREG_COREFREQ_PLL_PLL_VFB_EN_MASK                          = 0x00000400,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_TEST_MASK                                = 0x00000200,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_N_MASK                                   = 0x000001F0,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_M_MASK                                   = 0x0000000C,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_REF_SEL_MASK                             = 0x00000002,  /*!<  PLL Configuration Register Mask Value */
     CFGREG_COREFREQ_PLL_EN_MASK                                  = 0x00000001,  /*!<  PLL Configuration Register Mask Value */

     CFGREG_COREFREQ_STAT_RC_CORE_VAL_MASK                        = 0x000007E0,  /*!<  Core Clock Status Register Mask Value */
     CFGREG_COREFREQ_STAT_RC_CORE_RDY_MASK                        = 0x00000010,  /*!<  Core Clock Status Register Mask Value */
     CFGREG_COREFREQ_STAT_PLL_LOCK_MASK                           = 0x00000008,  /*!<  Core Clock Status Register Mask Value */
     CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_MASK                     = 0x00000004,  /*!<  Core Clock Status Register Mask Value */
     CFGREG_COREFREQ_STAT_CLK_CORE_SEL_MASK                       = 0x00000003,  /*!<  Core Clock Status Register Mask Value */

     CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_MASK                        = 0x00000002,  /*!<  GNSS-AFE Configuration Register Mask Value */
     CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_MASK                       = 0x00000001,  /*!<  GNSS-AFE Configuration Register Mask Value */

     CFGREG_PM_STAT_IREF_COMP_MASK                                = 0x00000004,  /*!<  GNSS-AFE PM Status Register Mask Value */
     CFGREG_PM_STAT_VREF_COMP_MASK                                = 0x00000002,  /*!<  GNSS-AFE PM Status Register Mask Value */
     CFGREG_PM_STAT_PWR_UP_MASK                                   = 0x00000001,  /*!<  GNSS-AFE PM Status Register Mask Value */

     CFGREG_PM_CONF_CAL_EN_MASK                                   = 0x00100000,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_TEST_EN_MASK                                  = 0x00080000,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_LDO_ADC_EN_MASK                               = 0x00040000,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_LDO_IF_EN_MASK                                = 0x00020000,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_LDO_DPLL_EN_MASK                              = 0x00010000,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_LDO_APLL_EN_MASK                              = 0x00008000,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_LDO_RF_EN_MASK                                = 0x00004000,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_VREF_EN_MASK                                  = 0x00002000,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_IREF_TRIM_SRC_MASK                            = 0x00001000,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_IREF_TRIM_MASK                                = 0x00000F00,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_IREF_EN_MASK                                  = 0x00000080,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_BGVR_TRIM_SRC_MASK                            = 0x00000040,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_BGVR_TRIM_MASK                                = 0x0000003C,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_BGVR_EN_MASK                                  = 0x00000002,  /*!<  GNSS-AFE PM Configuration Register Mask Value */
     CFGREG_PM_CONF_NRST_MASK                                     = 0x00000001,  /*!<  GNSS-AFE PM Configuration Register Mask Value */

     CFGREG_LNA15_STAT_CAL_RDY_L5_MASK                            = 0x00000002,  /*!<  LNA15 Status Register Mask Value */
     CFGREG_LNA15_STAT_CAL_RDY_L1_MASK                            = 0x00000001,  /*!<  LNA15 Status Register Mask Value */

     CFGREG_LNA15_TUNE_STAT_L5_MASK                               = 0xFFFF0000,  /*!<  LNA15 Tune Status Register Mask Value */
     CFGREG_LNA15_TUNE_STAT_L1_MASK                               = 0x0000FFFF,  /*!<  LNA15 Tune Status Register Mask Value */

     CFGREG_LNA15_CONF_L5_TUNE_SRC_MASK                           = 0x01000000,  /*!<  LNA15 Configuration Register Mask Value */
     CFGREG_LNA15_CONF_L1_TUNE_SRC_MASK                           = 0x00800000,  /*!<  LNA15 Configuration Register Mask Value */
     CFGREG_LNA15_CONF_CAL_WORD_L5_MASK                           = 0x007FC000,  /*!<  LNA15 Configuration Register Mask Value */
     CFGREG_LNA15_CONF_CAL_WORD_L1_MASK                           = 0x00003FE0,  /*!<  LNA15 Configuration Register Mask Value */
     CFGREG_LNA15_CONF_CAL_EN_L5_MASK                             = 0x00000010,  /*!<  LNA15 Configuration Register Mask Value */
     CFGREG_LNA15_CONF_CAL_EN_L1_MASK                             = 0x00000008,  /*!<  LNA15 Configuration Register Mask Value */
     CFGREG_LNA15_CONF_EN_L5_MASK                                 = 0x00000004,  /*!<  LNA15 Configuration Register Mask Value */
     CFGREG_LNA15_CONF_EN_L1_MASK                                 = 0x00000002,  /*!<  LNA15 Configuration Register Mask Value */
     CFGREG_LNA15_CONF_EN_MASK                                    = 0x00000001,  /*!<  LNA15 Configuration Register Mask Value */

     CFGREG_LNA15_TUNE_CONF_L5_MASK                               = 0xFFFF0000,  /*!<  LNA15 Configuration Register Mask Value */
     CFGREG_LNA15_TUNE_CONF_L1_MASK                               = 0x0000FFFF,  /*!<  LNA15 Configuration Register Mask Value */

     CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SRC_MASK                 = 0x00040000,  /*!<  BALUN and MIXER 1 Configuration Register Mask Value */
     CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_MASK                     = 0x0003FFFC,  /*!<  BALUN and MIXER 1 Configuration Register Mask Value */
     CFGREG_BALUN_MIXER1_CONF_BALUN_EN_MASK                       = 0x00000002,  /*!<  BALUN and MIXER 1 Configuration Register Mask Value */
     CFGREG_BALUN_MIXER1_CONF_MIXER_EN_MASK                       = 0x00000001,  /*!<  BALUN and MIXER 1 Configuration Register Mask Value */

     CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SRC_MASK                 = 0x00040000,  /*!<  BALUN and MIXER 5 Configuration Register Mask Value */
     CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_MASK                     = 0x0003FFFC,  /*!<  BALUN and MIXER 5 Configuration Register Mask Value */
     CFGREG_BALUN_MIXER5_CONF_BALUN_EN_MASK                       = 0x00000002,  /*!<  BALUN and MIXER 5 Configuration Register Mask Value */
     CFGREG_BALUN_MIXER5_CONF_MIXER_EN_MASK                       = 0x00000001,  /*!<  BALUN and MIXER 5 Configuration Register Mask Value */

     CFGREG_PROBE_CONF_PLL15FB_SEL_MASK                           = 0x00008000,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_CONF_PLL15FB_EN_MASK                            = 0x00004000,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_CONF_IF5_PROBEB_SELECT_MASK                     = 0x00003800,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_CONF_IF5_PROBEB_ENABLE_MASK                     = 0x00000400,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_CONF_IF5_PROBEA_SELECT_MASK                     = 0x00000380,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_CONF_IF1_PROBEB_SELECT_MASK                     = 0x00000070,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_CONF_IF1_PROBEB_ENABLE_MASK                     = 0x00000008,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */
     CFGREG_PROBE_CONF_IF1_PROBEA_SELECT_MASK                     = 0x00000007,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Mask Value */

     CFGREG_PLL1_CONF_LOPCB_EN_MASK                               = 0x04000000,  /*!<  PLL1 Configuration Register Mask Value */
     CFGREG_PLL1_CONF_TEST_EN_MASK                                = 0x02000000,  /*!<  PLL1 Configuration Register Mask Value */
     CFGREG_PLL1_CONF_FCW_MASK                                    = 0x01FFFFFE,  /*!<  PLL1 Configuration Register Mask Value */
     CFGREG_PLL1_CONF_EN_MASK                                     = 0x00000001,  /*!<  PLL1 Configuration Register Mask Value */

     CFGREG_PLL1TDC_CONF_GAIN_MASK                                = 0x00030000,  /*!<  PLL1 TDC Configuration Register Mask Value */
     CFGREG_PLL1TDC_CONF_SCALE_MASK                               = 0x0000FFFE,  /*!<  PLL1 TDC Configuration Register Mask Value */
     CFGREG_PLL1TDC_CONF_LOAD_MASK                                = 0x00000001,  /*!<  PLL1 TDC Configuration Register Mask Value */

     CFGREG_PLL1DCO_CONF_AMP_MASK                                 = 0x01E00000,  /*!<  PLL1 DCO Configuration Register Mask Value */
     CFGREG_PLL1DCO_CONF_AMP_LOAD_MASK                            = 0x00100000,  /*!<  PLL1 DCO Configuration Register Mask Value */
     CFGREG_PLL1DCO_CONF_CTRL_PVT_MASK                            = 0x000F0000,  /*!<  PLL1 DCO Configuration Register Mask Value */
     CFGREG_PLL1DCO_CONF_CTRL_FINE_MASK                           = 0x00007FFE,  /*!<  PLL1 DCO Configuration Register Mask Value */
     CFGREG_PLL1DCO_CONF_CTRL_LOAD_MASK                           = 0x00000001,  /*!<  PLL1 DCO Configuration Register Mask Value */

     CFGREG_PLL1_STAT_PHERR_MASK                                  = 0x3FFFFC00,  /*!<  PLL1 Status Register Mask Value */
     CFGREG_PLL1_STAT_NDIV_MASK                                   = 0x000003FC,  /*!<  PLL1 Status Register Mask Value */
     CFGREG_PLL1_STAT_PHSEL_MASK                                  = 0x00000002,  /*!<  PLL1 Status Register Mask Value */
     CFGREG_PLL1_STAT_LOCK_MASK                                   = 0x00000001,  /*!<  PLL1 Status Register Mask Value */

     CFGREG_PLL1TDC_STAT_SCALE_MASK                               = 0x00007FFF,  /*!<  PLL1 TDC Status Register Mask Value */

     CFGREG_PLL1DCO_STAT_AMP_MASK                                 = 0x00780000,  /*!<  PLL1 TDC Status Register Mask Value */
     CFGREG_PLL1DCO_STAT_AMP_LOW_MASK                             = 0x00040000,  /*!<  PLL1 TDC Status Register Mask Value */
     CFGREG_PLL1DCO_STAT_CTRL_PVT_MASK                            = 0x0003C000,  /*!<  PLL1 TDC Status Register Mask Value */
     CFGREG_PLL1DCO_STAT_CTRL_FINE_MASK                           = 0x00003FFF,  /*!<  PLL1 TDC Status Register Mask Value */

     CFGREG_IF1_CONF_AGC_IQ_SEP_MASK                              = 0x02000000,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_AGC_THR_MASK                                 = 0x01800000,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_LPF_CAL_MASK                                 = 0x00700000,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_LPF_GAIN_MASK                                = 0x000C0000,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_LPF_BAND_MASK                                = 0x00030000,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_LPF_EN_MASK                                  = 0x00008000,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PGA2_GAIN_MASK                               = 0x00006000,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PGA2_EN_MASK                                 = 0x00001000,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PGA1_1DB_GAIN_Q_MASK                         = 0x00000E00,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PGA1_1DB_GAIN_I_MASK                         = 0x000001C0,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PGA1_GAIN_MASK                               = 0x00000030,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PGA1_EN_MASK                                 = 0x00000008,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_PREAMP_EN_MASK                               = 0x00000004,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_LOAD_EN_MASK                                 = 0x00000002,  /*!<  IF1 Configuration Register Mask Value */
     CFGREG_IF1_CONF_EN_MASK                                      = 0x00000001,  /*!<  IF1 Configuration Register Mask Value */

     CFGREG_IF1_STAT_AGC_CTRL_Q_MASK                              = 0x0003FE00,  /*!<  IF1 Status Register Mask Value */
     CFGREG_IF1_STAT_AGC_CTRL_I_MASK                              = 0x000001FF,  /*!<  IF1 Status Register Mask Value */

     CFGREG_ADC1_CONF_CLK_SEL_MASK                                = 0x00000030,  /*!<  ADC1 Configuration Register Mask Value */
     CFGREG_ADC1_CONF_CLK_CONF_MASK                               = 0x0000000C,  /*!<  ADC1 Configuration Register Mask Value */
     CFGREG_ADC1_CONF_SAH_EN_MASK                                 = 0x00000002,  /*!<  ADC1 Configuration Register Mask Value */
     CFGREG_ADC1_CONF_ADC_EN_MASK                                 = 0x00000001,  /*!<  ADC1 Configuration Register Mask Value */

     CFGREG_PLL5_CONF_LOPCB_EN_MASK                               = 0x04000000,  /*!<  PLL5 Configuration Register Mask Value */
     CFGREG_PLL5_CONF_TEST_EN_MASK                                = 0x02000000,  /*!<  PLL5 Configuration Register Mask Value */
     CFGREG_PLL5_CONF_FCW_MASK                                    = 0x01FFFFFE,  /*!<  PLL5 Configuration Register Mask Value */
     CFGREG_PLL5_CONF_EN_MASK                                     = 0x00000001,  /*!<  PLL5 Configuration Register Mask Value */

     CFGREG_PLL5TDC_CONF_GAIN_MASK                                = 0x00030000,  /*!<  PLL5 TDC Configuration Register Mask Value */
     CFGREG_PLL5TDC_CONF_SCALE_MASK                               = 0x0000FFFE,  /*!<  PLL5 TDC Configuration Register Mask Value */
     CFGREG_PLL5TDC_CONF_LOAD_MASK                                = 0x00000001,  /*!<  PLL5 TDC Configuration Register Mask Value */

     CFGREG_PLL5DCO_CONF_AMP_MASK                                 = 0x01E00000,  /*!<  PLL5 DCO Configuration Register Mask Value */
     CFGREG_PLL5DCO_CONF_AMP_LOAD_MASK                            = 0x00100000,  /*!<  PLL5 DCO Configuration Register Mask Value */
     CFGREG_PLL5DCO_CONF_CTRL_PVT_MASK                            = 0x000F0000,  /*!<  PLL5 DCO Configuration Register Mask Value */
     CFGREG_PLL5DCO_CONF_CTRL_FINE_MASK                           = 0x00007FFE,  /*!<  PLL5 DCO Configuration Register Mask Value */
     CFGREG_PLL5DCO_CONF_CTRL_LOAD_MASK                           = 0x00000001,  /*!<  PLL5 DCO Configuration Register Mask Value */

     CFGREG_PLL5_STAT_PHERR_MASK                                  = 0x3FFFFC00,  /*!<  PLL5 Status Register Mask Value */
     CFGREG_PLL5_STAT_NDIV_MASK                                   = 0x000003FC,  /*!<  PLL5 Status Register Mask Value */
     CFGREG_PLL5_STAT_PHSEL_MASK                                  = 0x00000002,  /*!<  PLL5 Status Register Mask Value */
     CFGREG_PLL5_STAT_LOCK_MASK                                   = 0x00000001,  /*!<  PLL5 Status Register Mask Value */

     CFGREG_PLL5TDC_STAT_SCALE_MASK                               = 0x00007FFF,  /*!<  PLL5 TDC Status Register Mask Value */

     CFGREG_PLL5DCO_STAT_AMP_MASK                                 = 0x00780000,  /*!<  PLL5 TDC Status Register Mask Value */
     CFGREG_PLL5DCO_STAT_AMP_LOW_MASK                             = 0x00040000,  /*!<  PLL5 TDC Status Register Mask Value */
     CFGREG_PLL5DCO_STAT_CTRL_PVT_MASK                            = 0x0003C000,  /*!<  PLL5 TDC Status Register Mask Value */
     CFGREG_PLL5DCO_STAT_CTRL_FINE_MASK                           = 0x00003FFF,  /*!<  PLL5 TDC Status Register Mask Value */

     CFGREG_IF5_CONF_AGC_IQ_SEP_MASK                              = 0x02000000,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_AGC_THR_MASK                                 = 0x01800000,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_LPF_CAL_MASK                                 = 0x00700000,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_LPF_GAIN_MASK                                = 0x000C0000,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_LPF_BAND_MASK                                = 0x00030000,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_LPF_EN_MASK                                  = 0x00008000,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PGA2_GAIN_MASK                               = 0x00006000,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PGA2_EN_MASK                                 = 0x00001000,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PGA1_1DB_GAIN_Q_MASK                         = 0x00000E00,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PGA1_1DB_GAIN_I_MASK                         = 0x000001C0,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PGA1_GAIN_MASK                               = 0x00000030,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PGA1_EN_MASK                                 = 0x00000008,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_PREAMP_EN_MASK                               = 0x00000004,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_LOAD_EN_MASK                                 = 0x00000002,  /*!<  IF5 Configuration Register Mask Value */
     CFGREG_IF5_CONF_EN_MASK                                      = 0x00000001,  /*!<  IF5 Configuration Register Mask Value */

     CFGREG_IF5_STAT_AGC_CTRL_Q_MASK                              = 0x0003FE00,  /*!<  IF5 Status Register Mask Value */
     CFGREG_IF5_STAT_AGC_CTRL_I_MASK                              = 0x000001FF,  /*!<  IF5 Status Register Mask Value */

     CFGREG_ADC5_CONF_CLK_SEL_MASK                                = 0x00000030,  /*!<  ADC5 Configuration Register Mask Value */
     CFGREG_ADC5_CONF_CLK_CONF_MASK                               = 0x0000000C,  /*!<  ADC5 Configuration Register Mask Value */
     CFGREG_ADC5_CONF_SAH_EN_MASK                                 = 0x00000002,  /*!<  ADC5 Configuration Register Mask Value */
     CFGREG_ADC5_CONF_ADC_EN_MASK                                 = 0x00000001,  /*!<  ADC5 Configuration Register Mask Value */

     CFGREG_SPARE_CONF_SIG_MASK                                   = 0xFFFFFFFF,  /*!<  SPARE Configuration Register Mask Value */

     CFGREG_SPARE_STAT_SIG_MASK                                   = 0xFFFFFFFF,  /*!<  SPARE Configuration Register Mask Value */

     CFGREG_GNSSAFE_TEST_CONF_SIG_MASK                            = 0x0000FFFF,  /*!<  TEST Configuration Register Mask Value */

     CFGREG_GNSSAFE_TEST_STAT_SIG_MASK                            = 0x0000FFFF,  /*!<  TEST Configuration Register Mask Value */

};

/** Registers Shifts */
enum
{

     CFGREG_IRQMAP_IRQMAP_SHIFT                                   =  1,  /*!<  Interrupt Mapping Register Shift Value */

     CFGREG_UNLOCK_UNLOCK_KEY_SHIFT                               =  0,  /*!<  Unlock Register Shift Value */

     CFGREG_IRQFLAGS_PLL_FAIL_SHIFT                               =  2,  /*!<  32kHz RTC Clock Interrupt Flags Shift Value */
     CFGREG_IRQFLAGS_XTAL_CORE_FAIL_SHIFT                         =  1,  /*!<  32kHz RTC Clock Interrupt Flags Shift Value */
     CFGREG_IRQFLAGS_XTAL_RTC_FAIL_SHIFT                          =  0,  /*!<  32kHz RTC Clock Interrupt Flags Shift Value */

     CFGREG_PMU_CONF_IREF_CAL_EN_SHIFT                            = 10,  /*!<  Power Management Unit Configuration Shift Value */
     CFGREG_PMU_CONF_IREF_TRIM_VAL_SRC_SHIFT                      =  9,  /*!<  Power Management Unit Configuration Shift Value */
     CFGREG_PMU_CONF_IREF_TRIM_VAL_SHIFT                          =  1,  /*!<  Power Management Unit Configuration Shift Value */
     CFGREG_PMU_CONF_IREF_TRIM_EN_SHIFT                           =  0,  /*!<  Power Management Unit Configuration Shift Value */

     CFGREG_PMU_STAT_IREF_TRIM_VAL_SHIFT                          =  1,  /*!<  Power Management Unit Status Shift Value */
     CFGREG_PMU_STAT_IREF_CAL_RDY_SHIFT                           =  0,  /*!<  Power Management Unit Status Shift Value */

     CFGREG_RTCSTAT_RC_RTC_VAL_SHIFT                              =  2,  /*!<  32kHz RTC Clock Status Shift Value */
     CFGREG_RTCSTAT_RC_RTC_RDY_SHIFT                              =  1,  /*!<  32kHz RTC Clock Status Shift Value */
     CFGREG_RTCSTAT_CLK_RTC_SEL_SHIFT                             =  0,  /*!<  32kHz RTC Clock Status Shift Value */

     CFGREG_RTCCONF_RC_RTC_VAL_SRC_SHIFT                          = 10,  /*!<  32kHz RTC Clock Configuration Shift Value */
     CFGREG_RTCCONF_RC_RTC_VAL_SHIFT                              =  3,  /*!<  32kHz RTC Clock Configuration Shift Value */
     CFGREG_RTCCONF_RC_RTC_CAL_SHIFT                              =  2,  /*!<  32kHz RTC Clock Configuration Shift Value */
     CFGREG_RTCCONF_XTAL_RTC_SEL_SHIFT                            =  1,  /*!<  32kHz RTC Clock Configuration Shift Value */
     CFGREG_RTCCONF_XTAL_RTC_TEST_SHIFT                           =  0,  /*!<  32kHz RTC Clock Configuration Shift Value */

     CFGREG_COREFREQ_CLK_TEST_OUT_EN_SHIFT                        = 11,  /*!<  External XTAL Configuration Register Shift Value */
     CFGREG_COREFREQ_CLK_RC_CORE_VAL_SRC_SHIFT                    = 10,  /*!<  External XTAL Configuration Register Shift Value */
     CFGREG_COREFREQ_CLK_RC_CORE_VAL_SHIFT                        =  4,  /*!<  External XTAL Configuration Register Shift Value */
     CFGREG_COREFREQ_CLK_RC_CORE_CAL_SHIFT                        =  3,  /*!<  External XTAL Configuration Register Shift Value */
     CFGREG_COREFREQ_CLK_CORE_SEL_SHIFT                           =  1,  /*!<  External XTAL Configuration Register Shift Value */
     CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_SHIFT                     =  0,  /*!<  External XTAL Configuration Register Shift Value */

     CFGREG_COREFREQ_PLL_PLL_VFB_EN_SHIFT                         = 10,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_TEST_SHIFT                               =  9,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_N_SHIFT                                  =  4,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_M_SHIFT                                  =  2,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_REF_SEL_SHIFT                            =  1,  /*!<  PLL Configuration Register Shift Value */
     CFGREG_COREFREQ_PLL_EN_SHIFT                                 =  0,  /*!<  PLL Configuration Register Shift Value */

     CFGREG_COREFREQ_STAT_RC_CORE_VAL_SHIFT                       =  5,  /*!<  Core Clock Status Register Shift Value */
     CFGREG_COREFREQ_STAT_RC_CORE_RDY_SHIFT                       =  4,  /*!<  Core Clock Status Register Shift Value */
     CFGREG_COREFREQ_STAT_PLL_LOCK_SHIFT                          =  3,  /*!<  Core Clock Status Register Shift Value */
     CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_SHIFT                    =  2,  /*!<  Core Clock Status Register Shift Value */
     CFGREG_COREFREQ_STAT_CLK_CORE_SEL_SHIFT                      =  0,  /*!<  Core Clock Status Register Shift Value */

     CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_SHIFT                       =  1,  /*!<  GNSS-AFE Configuration Register Shift Value */
     CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_SHIFT                      =  0,  /*!<  GNSS-AFE Configuration Register Shift Value */

     CFGREG_PM_STAT_IREF_COMP_SHIFT                               =  2,  /*!<  GNSS-AFE PM Status Register Shift Value */
     CFGREG_PM_STAT_VREF_COMP_SHIFT                               =  1,  /*!<  GNSS-AFE PM Status Register Shift Value */
     CFGREG_PM_STAT_PWR_UP_SHIFT                                  =  0,  /*!<  GNSS-AFE PM Status Register Shift Value */

     CFGREG_PM_CONF_CAL_EN_SHIFT                                  = 20,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_TEST_EN_SHIFT                                 = 19,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_LDO_ADC_EN_SHIFT                              = 18,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_LDO_IF_EN_SHIFT                               = 17,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_LDO_DPLL_EN_SHIFT                             = 16,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_LDO_APLL_EN_SHIFT                             = 15,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_LDO_RF_EN_SHIFT                               = 14,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_VREF_EN_SHIFT                                 = 13,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_IREF_TRIM_SRC_SHIFT                           = 12,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_IREF_TRIM_SHIFT                               =  8,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_IREF_EN_SHIFT                                 =  7,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_BGVR_TRIM_SRC_SHIFT                           =  6,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_BGVR_TRIM_SHIFT                               =  2,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_BGVR_EN_SHIFT                                 =  1,  /*!<  GNSS-AFE PM Configuration Register Shift Value */
     CFGREG_PM_CONF_NRST_SHIFT                                    =  0,  /*!<  GNSS-AFE PM Configuration Register Shift Value */

     CFGREG_LNA15_STAT_CAL_RDY_L5_SHIFT                           =  1,  /*!<  LNA15 Status Register Shift Value */
     CFGREG_LNA15_STAT_CAL_RDY_L1_SHIFT                           =  0,  /*!<  LNA15 Status Register Shift Value */

     CFGREG_LNA15_TUNE_STAT_L5_SHIFT                              = 16,  /*!<  LNA15 Tune Status Register Shift Value */
     CFGREG_LNA15_TUNE_STAT_L1_SHIFT                              =  0,  /*!<  LNA15 Tune Status Register Shift Value */

     CFGREG_LNA15_CONF_L5_TUNE_SRC_SHIFT                          = 24,  /*!<  LNA15 Configuration Register Shift Value */
     CFGREG_LNA15_CONF_L1_TUNE_SRC_SHIFT                          = 23,  /*!<  LNA15 Configuration Register Shift Value */
     CFGREG_LNA15_CONF_CAL_WORD_L5_SHIFT                          = 14,  /*!<  LNA15 Configuration Register Shift Value */
     CFGREG_LNA15_CONF_CAL_WORD_L1_SHIFT                          =  5,  /*!<  LNA15 Configuration Register Shift Value */
     CFGREG_LNA15_CONF_CAL_EN_L5_SHIFT                            =  4,  /*!<  LNA15 Configuration Register Shift Value */
     CFGREG_LNA15_CONF_CAL_EN_L1_SHIFT                            =  3,  /*!<  LNA15 Configuration Register Shift Value */
     CFGREG_LNA15_CONF_EN_L5_SHIFT                                =  2,  /*!<  LNA15 Configuration Register Shift Value */
     CFGREG_LNA15_CONF_EN_L1_SHIFT                                =  1,  /*!<  LNA15 Configuration Register Shift Value */
     CFGREG_LNA15_CONF_EN_SHIFT                                   =  0,  /*!<  LNA15 Configuration Register Shift Value */

     CFGREG_LNA15_TUNE_CONF_L5_SHIFT                              = 16,  /*!<  LNA15 Configuration Register Shift Value */
     CFGREG_LNA15_TUNE_CONF_L1_SHIFT                              =  0,  /*!<  LNA15 Configuration Register Shift Value */

     CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SRC_SHIFT                = 18,  /*!<  BALUN and MIXER 1 Configuration Register Shift Value */
     CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SHIFT                    =  2,  /*!<  BALUN and MIXER 1 Configuration Register Shift Value */
     CFGREG_BALUN_MIXER1_CONF_BALUN_EN_SHIFT                      =  1,  /*!<  BALUN and MIXER 1 Configuration Register Shift Value */
     CFGREG_BALUN_MIXER1_CONF_MIXER_EN_SHIFT                      =  0,  /*!<  BALUN and MIXER 1 Configuration Register Shift Value */

     CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SRC_SHIFT                = 18,  /*!<  BALUN and MIXER 5 Configuration Register Shift Value */
     CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SHIFT                    =  2,  /*!<  BALUN and MIXER 5 Configuration Register Shift Value */
     CFGREG_BALUN_MIXER5_CONF_BALUN_EN_SHIFT                      =  1,  /*!<  BALUN and MIXER 5 Configuration Register Shift Value */
     CFGREG_BALUN_MIXER5_CONF_MIXER_EN_SHIFT                      =  0,  /*!<  BALUN and MIXER 5 Configuration Register Shift Value */

     CFGREG_PROBE_CONF_PLL15FB_SEL_SHIFT                          = 15,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_CONF_PLL15FB_EN_SHIFT                           = 14,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_CONF_IF5_PROBEB_SELECT_SHIFT                    = 11,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_CONF_IF5_PROBEB_ENABLE_SHIFT                    = 10,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_CONF_IF5_PROBEA_SELECT_SHIFT                    =  7,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_CONF_IF1_PROBEB_SELECT_SHIFT                    =  4,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_CONF_IF1_PROBEB_ENABLE_SHIFT                    =  3,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */
     CFGREG_PROBE_CONF_IF1_PROBEA_SELECT_SHIFT                    =  0,  /*!<  GNSS-AFE IF1 analog probing Configuration Register Shift Value */

     CFGREG_PLL1_CONF_LOPCB_EN_SHIFT                              = 26,  /*!<  PLL1 Configuration Register Shift Value */
     CFGREG_PLL1_CONF_TEST_EN_SHIFT                               = 25,  /*!<  PLL1 Configuration Register Shift Value */
     CFGREG_PLL1_CONF_FCW_SHIFT                                   =  1,  /*!<  PLL1 Configuration Register Shift Value */
     CFGREG_PLL1_CONF_EN_SHIFT                                    =  0,  /*!<  PLL1 Configuration Register Shift Value */

     CFGREG_PLL1TDC_CONF_GAIN_SHIFT                               = 16,  /*!<  PLL1 TDC Configuration Register Shift Value */
     CFGREG_PLL1TDC_CONF_SCALE_SHIFT                              =  1,  /*!<  PLL1 TDC Configuration Register Shift Value */
     CFGREG_PLL1TDC_CONF_LOAD_SHIFT                               =  0,  /*!<  PLL1 TDC Configuration Register Shift Value */

     CFGREG_PLL1DCO_CONF_AMP_SHIFT                                = 21,  /*!<  PLL1 DCO Configuration Register Shift Value */
     CFGREG_PLL1DCO_CONF_AMP_LOAD_SHIFT                           = 20,  /*!<  PLL1 DCO Configuration Register Shift Value */
     CFGREG_PLL1DCO_CONF_CTRL_PVT_SHIFT                           = 16,  /*!<  PLL1 DCO Configuration Register Shift Value */
     CFGREG_PLL1DCO_CONF_CTRL_FINE_SHIFT                          =  1,  /*!<  PLL1 DCO Configuration Register Shift Value */
     CFGREG_PLL1DCO_CONF_CTRL_LOAD_SHIFT                          =  0,  /*!<  PLL1 DCO Configuration Register Shift Value */

     CFGREG_PLL1_STAT_PHERR_SHIFT                                 = 10,  /*!<  PLL1 Status Register Shift Value */
     CFGREG_PLL1_STAT_NDIV_SHIFT                                  =  2,  /*!<  PLL1 Status Register Shift Value */
     CFGREG_PLL1_STAT_PHSEL_SHIFT                                 =  1,  /*!<  PLL1 Status Register Shift Value */
     CFGREG_PLL1_STAT_LOCK_SHIFT                                  =  0,  /*!<  PLL1 Status Register Shift Value */

     CFGREG_PLL1TDC_STAT_SCALE_SHIFT                              =  0,  /*!<  PLL1 TDC Status Register Shift Value */

     CFGREG_PLL1DCO_STAT_AMP_SHIFT                                = 19,  /*!<  PLL1 TDC Status Register Shift Value */
     CFGREG_PLL1DCO_STAT_AMP_LOW_SHIFT                            = 18,  /*!<  PLL1 TDC Status Register Shift Value */
     CFGREG_PLL1DCO_STAT_CTRL_PVT_SHIFT                           = 14,  /*!<  PLL1 TDC Status Register Shift Value */
     CFGREG_PLL1DCO_STAT_CTRL_FINE_SHIFT                          =  0,  /*!<  PLL1 TDC Status Register Shift Value */

     CFGREG_IF1_CONF_AGC_IQ_SEP_SHIFT                             = 25,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_AGC_THR_SHIFT                                = 23,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_LPF_CAL_SHIFT                                = 20,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_LPF_GAIN_SHIFT                               = 18,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_LPF_BAND_SHIFT                               = 16,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_LPF_EN_SHIFT                                 = 15,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PGA2_GAIN_SHIFT                              = 13,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PGA2_EN_SHIFT                                = 12,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PGA1_1DB_GAIN_Q_SHIFT                        =  9,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PGA1_1DB_GAIN_I_SHIFT                        =  6,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PGA1_GAIN_SHIFT                              =  4,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PGA1_EN_SHIFT                                =  3,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_PREAMP_EN_SHIFT                              =  2,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_LOAD_EN_SHIFT                                =  1,  /*!<  IF1 Configuration Register Shift Value */
     CFGREG_IF1_CONF_EN_SHIFT                                     =  0,  /*!<  IF1 Configuration Register Shift Value */

     CFGREG_IF1_STAT_AGC_CTRL_Q_SHIFT                             =  9,  /*!<  IF1 Status Register Shift Value */
     CFGREG_IF1_STAT_AGC_CTRL_I_SHIFT                             =  0,  /*!<  IF1 Status Register Shift Value */

     CFGREG_ADC1_CONF_CLK_SEL_SHIFT                               =  4,  /*!<  ADC1 Configuration Register Shift Value */
     CFGREG_ADC1_CONF_CLK_CONF_SHIFT                              =  2,  /*!<  ADC1 Configuration Register Shift Value */
     CFGREG_ADC1_CONF_SAH_EN_SHIFT                                =  1,  /*!<  ADC1 Configuration Register Shift Value */
     CFGREG_ADC1_CONF_ADC_EN_SHIFT                                =  0,  /*!<  ADC1 Configuration Register Shift Value */

     CFGREG_PLL5_CONF_LOPCB_EN_SHIFT                              = 26,  /*!<  PLL5 Configuration Register Shift Value */
     CFGREG_PLL5_CONF_TEST_EN_SHIFT                               = 25,  /*!<  PLL5 Configuration Register Shift Value */
     CFGREG_PLL5_CONF_FCW_SHIFT                                   =  1,  /*!<  PLL5 Configuration Register Shift Value */
     CFGREG_PLL5_CONF_EN_SHIFT                                    =  0,  /*!<  PLL5 Configuration Register Shift Value */

     CFGREG_PLL5TDC_CONF_GAIN_SHIFT                               = 16,  /*!<  PLL5 TDC Configuration Register Shift Value */
     CFGREG_PLL5TDC_CONF_SCALE_SHIFT                              =  1,  /*!<  PLL5 TDC Configuration Register Shift Value */
     CFGREG_PLL5TDC_CONF_LOAD_SHIFT                               =  0,  /*!<  PLL5 TDC Configuration Register Shift Value */

     CFGREG_PLL5DCO_CONF_AMP_SHIFT                                = 21,  /*!<  PLL5 DCO Configuration Register Shift Value */
     CFGREG_PLL5DCO_CONF_AMP_LOAD_SHIFT                           = 20,  /*!<  PLL5 DCO Configuration Register Shift Value */
     CFGREG_PLL5DCO_CONF_CTRL_PVT_SHIFT                           = 16,  /*!<  PLL5 DCO Configuration Register Shift Value */
     CFGREG_PLL5DCO_CONF_CTRL_FINE_SHIFT                          =  1,  /*!<  PLL5 DCO Configuration Register Shift Value */
     CFGREG_PLL5DCO_CONF_CTRL_LOAD_SHIFT                          =  0,  /*!<  PLL5 DCO Configuration Register Shift Value */

     CFGREG_PLL5_STAT_PHERR_SHIFT                                 = 10,  /*!<  PLL5 Status Register Shift Value */
     CFGREG_PLL5_STAT_NDIV_SHIFT                                  =  2,  /*!<  PLL5 Status Register Shift Value */
     CFGREG_PLL5_STAT_PHSEL_SHIFT                                 =  1,  /*!<  PLL5 Status Register Shift Value */
     CFGREG_PLL5_STAT_LOCK_SHIFT                                  =  0,  /*!<  PLL5 Status Register Shift Value */

     CFGREG_PLL5TDC_STAT_SCALE_SHIFT                              =  0,  /*!<  PLL5 TDC Status Register Shift Value */

     CFGREG_PLL5DCO_STAT_AMP_SHIFT                                = 19,  /*!<  PLL5 TDC Status Register Shift Value */
     CFGREG_PLL5DCO_STAT_AMP_LOW_SHIFT                            = 18,  /*!<  PLL5 TDC Status Register Shift Value */
     CFGREG_PLL5DCO_STAT_CTRL_PVT_SHIFT                           = 14,  /*!<  PLL5 TDC Status Register Shift Value */
     CFGREG_PLL5DCO_STAT_CTRL_FINE_SHIFT                          =  0,  /*!<  PLL5 TDC Status Register Shift Value */

     CFGREG_IF5_CONF_AGC_IQ_SEP_SHIFT                             = 25,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_AGC_THR_SHIFT                                = 23,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_LPF_CAL_SHIFT                                = 20,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_LPF_GAIN_SHIFT                               = 18,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_LPF_BAND_SHIFT                               = 16,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_LPF_EN_SHIFT                                 = 15,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PGA2_GAIN_SHIFT                              = 13,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PGA2_EN_SHIFT                                = 12,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PGA1_1DB_GAIN_Q_SHIFT                        =  9,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PGA1_1DB_GAIN_I_SHIFT                        =  6,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PGA1_GAIN_SHIFT                              =  4,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PGA1_EN_SHIFT                                =  3,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_PREAMP_EN_SHIFT                              =  2,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_LOAD_EN_SHIFT                                =  1,  /*!<  IF5 Configuration Register Shift Value */
     CFGREG_IF5_CONF_EN_SHIFT                                     =  0,  /*!<  IF5 Configuration Register Shift Value */

     CFGREG_IF5_STAT_AGC_CTRL_Q_SHIFT                             =  9,  /*!<  IF5 Status Register Shift Value */
     CFGREG_IF5_STAT_AGC_CTRL_I_SHIFT                             =  0,  /*!<  IF5 Status Register Shift Value */

     CFGREG_ADC5_CONF_CLK_SEL_SHIFT                               =  4,  /*!<  ADC5 Configuration Register Shift Value */
     CFGREG_ADC5_CONF_CLK_CONF_SHIFT                              =  2,  /*!<  ADC5 Configuration Register Shift Value */
     CFGREG_ADC5_CONF_SAH_EN_SHIFT                                =  1,  /*!<  ADC5 Configuration Register Shift Value */
     CFGREG_ADC5_CONF_ADC_EN_SHIFT                                =  0,  /*!<  ADC5 Configuration Register Shift Value */

     CFGREG_SPARE_CONF_SIG_SHIFT                                  =  0,  /*!<  SPARE Configuration Register Shift Value */

     CFGREG_SPARE_STAT_SIG_SHIFT                                  =  0,  /*!<  SPARE Configuration Register Shift Value */

     CFGREG_GNSSAFE_TEST_CONF_SIG_SHIFT                           =  0,  /*!<  TEST Configuration Register Shift Value */

     CFGREG_GNSSAFE_TEST_STAT_SIG_SHIFT                           =  0,  /*!<  TEST Configuration Register Shift Value */

};

/** Bits Set Helper Macros */

#define CFGREG_IRQMAP_IRQMAP_BITS_SET(x)                                       ((x << CFGREG_IRQMAP_IRQMAP_SHIFT) & CFGREG_IRQMAP_IRQMAP_MASK)                                                          /*!<  Interrupt Mapping Register Bits Set */

#define CFGREG_UNLOCK_UNLOCK_KEY_BITS_SET(x)                                   ((x << CFGREG_UNLOCK_UNLOCK_KEY_SHIFT) & CFGREG_UNLOCK_UNLOCK_KEY_MASK)                                                  /*!<  Unlock Register Bits Set */

#define CFGREG_IRQFLAGS_PLL_FAIL_BITS_SET(x)                                   ((x << CFGREG_IRQFLAGS_PLL_FAIL_SHIFT) & CFGREG_IRQFLAGS_PLL_FAIL_MASK)                                                  /*!<  32kHz RTC Clock Interrupt Flags Bits Set */
#define CFGREG_IRQFLAGS_XTAL_CORE_FAIL_BITS_SET(x)                             ((x << CFGREG_IRQFLAGS_XTAL_CORE_FAIL_SHIFT) & CFGREG_IRQFLAGS_XTAL_CORE_FAIL_MASK)                                      /*!<  32kHz RTC Clock Interrupt Flags Bits Set */
#define CFGREG_IRQFLAGS_XTAL_RTC_FAIL_BITS_SET(x)                              ((x << CFGREG_IRQFLAGS_XTAL_RTC_FAIL_SHIFT) & CFGREG_IRQFLAGS_XTAL_RTC_FAIL_MASK)                                        /*!<  32kHz RTC Clock Interrupt Flags Bits Set */

#define CFGREG_PMU_CONF_IREF_CAL_EN_BITS_SET(x)                                ((x << CFGREG_PMU_CONF_IREF_CAL_EN_SHIFT) & CFGREG_PMU_CONF_IREF_CAL_EN_MASK)                                            /*!<  Power Management Unit Configuration Bits Set */
#define CFGREG_PMU_CONF_IREF_TRIM_VAL_SRC_BITS_SET(x)                          ((x << CFGREG_PMU_CONF_IREF_TRIM_VAL_SRC_SHIFT) & CFGREG_PMU_CONF_IREF_TRIM_VAL_SRC_MASK)                                /*!<  Power Management Unit Configuration Bits Set */
#define CFGREG_PMU_CONF_IREF_TRIM_VAL_BITS_SET(x)                              ((x << CFGREG_PMU_CONF_IREF_TRIM_VAL_SHIFT) & CFGREG_PMU_CONF_IREF_TRIM_VAL_MASK)                                        /*!<  Power Management Unit Configuration Bits Set */
#define CFGREG_PMU_CONF_IREF_TRIM_EN_BITS_SET(x)                               ((x << CFGREG_PMU_CONF_IREF_TRIM_EN_SHIFT) & CFGREG_PMU_CONF_IREF_TRIM_EN_MASK)                                          /*!<  Power Management Unit Configuration Bits Set */

#define CFGREG_PMU_STAT_IREF_TRIM_VAL_BITS_SET(x)                              ((x << CFGREG_PMU_STAT_IREF_TRIM_VAL_SHIFT) & CFGREG_PMU_STAT_IREF_TRIM_VAL_MASK)                                        /*!<  Power Management Unit Status Bits Set */
#define CFGREG_PMU_STAT_IREF_CAL_RDY_BITS_SET(x)                               ((x << CFGREG_PMU_STAT_IREF_CAL_RDY_SHIFT) & CFGREG_PMU_STAT_IREF_CAL_RDY_MASK)                                          /*!<  Power Management Unit Status Bits Set */

#define CFGREG_RTCSTAT_RC_RTC_VAL_BITS_SET(x)                                  ((x << CFGREG_RTCSTAT_RC_RTC_VAL_SHIFT) & CFGREG_RTCSTAT_RC_RTC_VAL_MASK)                                                /*!<  32kHz RTC Clock Status Bits Set */
#define CFGREG_RTCSTAT_RC_RTC_RDY_BITS_SET(x)                                  ((x << CFGREG_RTCSTAT_RC_RTC_RDY_SHIFT) & CFGREG_RTCSTAT_RC_RTC_RDY_MASK)                                                /*!<  32kHz RTC Clock Status Bits Set */
#define CFGREG_RTCSTAT_CLK_RTC_SEL_BITS_SET(x)                                 ((x << CFGREG_RTCSTAT_CLK_RTC_SEL_SHIFT) & CFGREG_RTCSTAT_CLK_RTC_SEL_MASK)                                              /*!<  32kHz RTC Clock Status Bits Set */

#define CFGREG_RTCCONF_RC_RTC_VAL_SRC_BITS_SET(x)                              ((x << CFGREG_RTCCONF_RC_RTC_VAL_SRC_SHIFT) & CFGREG_RTCCONF_RC_RTC_VAL_SRC_MASK)                                        /*!<  32kHz RTC Clock Configuration Bits Set */
#define CFGREG_RTCCONF_RC_RTC_VAL_BITS_SET(x)                                  ((x << CFGREG_RTCCONF_RC_RTC_VAL_SHIFT) & CFGREG_RTCCONF_RC_RTC_VAL_MASK)                                                /*!<  32kHz RTC Clock Configuration Bits Set */
#define CFGREG_RTCCONF_RC_RTC_CAL_BITS_SET(x)                                  ((x << CFGREG_RTCCONF_RC_RTC_CAL_SHIFT) & CFGREG_RTCCONF_RC_RTC_CAL_MASK)                                                /*!<  32kHz RTC Clock Configuration Bits Set */
#define CFGREG_RTCCONF_XTAL_RTC_SEL_BITS_SET(x)                                ((x << CFGREG_RTCCONF_XTAL_RTC_SEL_SHIFT) & CFGREG_RTCCONF_XTAL_RTC_SEL_MASK)                                            /*!<  32kHz RTC Clock Configuration Bits Set */
#define CFGREG_RTCCONF_XTAL_RTC_TEST_BITS_SET(x)                               ((x << CFGREG_RTCCONF_XTAL_RTC_TEST_SHIFT) & CFGREG_RTCCONF_XTAL_RTC_TEST_MASK)                                          /*!<  32kHz RTC Clock Configuration Bits Set */

#define CFGREG_COREFREQ_CLK_TEST_OUT_EN_BITS_SET(x)                            ((x << CFGREG_COREFREQ_CLK_TEST_OUT_EN_SHIFT) & CFGREG_COREFREQ_CLK_TEST_OUT_EN_MASK)                                    /*!<  External XTAL Configuration Register Bits Set */
#define CFGREG_COREFREQ_CLK_RC_CORE_VAL_SRC_BITS_SET(x)                        ((x << CFGREG_COREFREQ_CLK_RC_CORE_VAL_SRC_SHIFT) & CFGREG_COREFREQ_CLK_RC_CORE_VAL_SRC_MASK)                            /*!<  External XTAL Configuration Register Bits Set */
#define CFGREG_COREFREQ_CLK_RC_CORE_VAL_BITS_SET(x)                            ((x << CFGREG_COREFREQ_CLK_RC_CORE_VAL_SHIFT) & CFGREG_COREFREQ_CLK_RC_CORE_VAL_MASK)                                    /*!<  External XTAL Configuration Register Bits Set */
#define CFGREG_COREFREQ_CLK_RC_CORE_CAL_BITS_SET(x)                            ((x << CFGREG_COREFREQ_CLK_RC_CORE_CAL_SHIFT) & CFGREG_COREFREQ_CLK_RC_CORE_CAL_MASK)                                    /*!<  External XTAL Configuration Register Bits Set */
#define CFGREG_COREFREQ_CLK_CORE_SEL_BITS_SET(x)                               ((x << CFGREG_COREFREQ_CLK_CORE_SEL_SHIFT) & CFGREG_COREFREQ_CLK_CORE_SEL_MASK)                                          /*!<  External XTAL Configuration Register Bits Set */
#define CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_BITS_SET(x)                         ((x << CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_SHIFT) & CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_MASK)                              /*!<  External XTAL Configuration Register Bits Set */

#define CFGREG_COREFREQ_PLL_PLL_VFB_EN_BITS_SET(x)                             ((x << CFGREG_COREFREQ_PLL_PLL_VFB_EN_SHIFT) & CFGREG_COREFREQ_PLL_PLL_VFB_EN_MASK)                                      /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_TEST_BITS_SET(x)                                   ((x << CFGREG_COREFREQ_PLL_TEST_SHIFT) & CFGREG_COREFREQ_PLL_TEST_MASK)                                                  /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_N_BITS_SET(x)                                      ((x << CFGREG_COREFREQ_PLL_N_SHIFT) & CFGREG_COREFREQ_PLL_N_MASK)                                                        /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_M_BITS_SET(x)                                      ((x << CFGREG_COREFREQ_PLL_M_SHIFT) & CFGREG_COREFREQ_PLL_M_MASK)                                                        /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_REF_SEL_BITS_SET(x)                                ((x << CFGREG_COREFREQ_PLL_REF_SEL_SHIFT) & CFGREG_COREFREQ_PLL_REF_SEL_MASK)                                            /*!<  PLL Configuration Register Bits Set */
#define CFGREG_COREFREQ_PLL_EN_BITS_SET(x)                                     ((x << CFGREG_COREFREQ_PLL_EN_SHIFT) & CFGREG_COREFREQ_PLL_EN_MASK)                                                      /*!<  PLL Configuration Register Bits Set */

#define CFGREG_COREFREQ_STAT_RC_CORE_VAL_BITS_SET(x)                           ((x << CFGREG_COREFREQ_STAT_RC_CORE_VAL_SHIFT) & CFGREG_COREFREQ_STAT_RC_CORE_VAL_MASK)                                  /*!<  Core Clock Status Register Bits Set */
#define CFGREG_COREFREQ_STAT_RC_CORE_RDY_BITS_SET(x)                           ((x << CFGREG_COREFREQ_STAT_RC_CORE_RDY_SHIFT) & CFGREG_COREFREQ_STAT_RC_CORE_RDY_MASK)                                  /*!<  Core Clock Status Register Bits Set */
#define CFGREG_COREFREQ_STAT_PLL_LOCK_BITS_SET(x)                              ((x << CFGREG_COREFREQ_STAT_PLL_LOCK_SHIFT) & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK)                                        /*!<  Core Clock Status Register Bits Set */
#define CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_BITS_SET(x)                        ((x << CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_SHIFT) & CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_MASK)                            /*!<  Core Clock Status Register Bits Set */
#define CFGREG_COREFREQ_STAT_CLK_CORE_SEL_BITS_SET(x)                          ((x << CFGREG_COREFREQ_STAT_CLK_CORE_SEL_SHIFT) & CFGREG_COREFREQ_STAT_CLK_CORE_SEL_MASK)                                /*!<  Core Clock Status Register Bits Set */

#define CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_BITS_SET(x)                           ((x << CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_SHIFT) & CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_MASK)                                  /*!<  GNSS-AFE Configuration Register Bits Set */
#define CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_BITS_SET(x)                          ((x << CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_SHIFT) & CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_MASK)                                /*!<  GNSS-AFE Configuration Register Bits Set */

#define CFGREG_PM_STAT_IREF_COMP_BITS_SET(x)                                   ((x << CFGREG_PM_STAT_IREF_COMP_SHIFT) & CFGREG_PM_STAT_IREF_COMP_MASK)                                                  /*!<  GNSS-AFE PM Status Register Bits Set */
#define CFGREG_PM_STAT_VREF_COMP_BITS_SET(x)                                   ((x << CFGREG_PM_STAT_VREF_COMP_SHIFT) & CFGREG_PM_STAT_VREF_COMP_MASK)                                                  /*!<  GNSS-AFE PM Status Register Bits Set */
#define CFGREG_PM_STAT_PWR_UP_BITS_SET(x)                                      ((x << CFGREG_PM_STAT_PWR_UP_SHIFT) & CFGREG_PM_STAT_PWR_UP_MASK)                                                        /*!<  GNSS-AFE PM Status Register Bits Set */

#define CFGREG_PM_CONF_CAL_EN_BITS_SET(x)                                      ((x << CFGREG_PM_CONF_CAL_EN_SHIFT) & CFGREG_PM_CONF_CAL_EN_MASK)                                                        /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_TEST_EN_BITS_SET(x)                                     ((x << CFGREG_PM_CONF_TEST_EN_SHIFT) & CFGREG_PM_CONF_TEST_EN_MASK)                                                      /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_LDO_ADC_EN_BITS_SET(x)                                  ((x << CFGREG_PM_CONF_LDO_ADC_EN_SHIFT) & CFGREG_PM_CONF_LDO_ADC_EN_MASK)                                                /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_LDO_IF_EN_BITS_SET(x)                                   ((x << CFGREG_PM_CONF_LDO_IF_EN_SHIFT) & CFGREG_PM_CONF_LDO_IF_EN_MASK)                                                  /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_LDO_DPLL_EN_BITS_SET(x)                                 ((x << CFGREG_PM_CONF_LDO_DPLL_EN_SHIFT) & CFGREG_PM_CONF_LDO_DPLL_EN_MASK)                                              /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_LDO_APLL_EN_BITS_SET(x)                                 ((x << CFGREG_PM_CONF_LDO_APLL_EN_SHIFT) & CFGREG_PM_CONF_LDO_APLL_EN_MASK)                                              /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_LDO_RF_EN_BITS_SET(x)                                   ((x << CFGREG_PM_CONF_LDO_RF_EN_SHIFT) & CFGREG_PM_CONF_LDO_RF_EN_MASK)                                                  /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_VREF_EN_BITS_SET(x)                                     ((x << CFGREG_PM_CONF_VREF_EN_SHIFT) & CFGREG_PM_CONF_VREF_EN_MASK)                                                      /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_IREF_TRIM_SRC_BITS_SET(x)                               ((x << CFGREG_PM_CONF_IREF_TRIM_SRC_SHIFT) & CFGREG_PM_CONF_IREF_TRIM_SRC_MASK)                                          /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_IREF_TRIM_BITS_SET(x)                                   ((x << CFGREG_PM_CONF_IREF_TRIM_SHIFT) & CFGREG_PM_CONF_IREF_TRIM_MASK)                                                  /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_IREF_EN_BITS_SET(x)                                     ((x << CFGREG_PM_CONF_IREF_EN_SHIFT) & CFGREG_PM_CONF_IREF_EN_MASK)                                                      /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_BGVR_TRIM_SRC_BITS_SET(x)                               ((x << CFGREG_PM_CONF_BGVR_TRIM_SRC_SHIFT) & CFGREG_PM_CONF_BGVR_TRIM_SRC_MASK)                                          /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_BGVR_TRIM_BITS_SET(x)                                   ((x << CFGREG_PM_CONF_BGVR_TRIM_SHIFT) & CFGREG_PM_CONF_BGVR_TRIM_MASK)                                                  /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_BGVR_EN_BITS_SET(x)                                     ((x << CFGREG_PM_CONF_BGVR_EN_SHIFT) & CFGREG_PM_CONF_BGVR_EN_MASK)                                                      /*!<  GNSS-AFE PM Configuration Register Bits Set */
#define CFGREG_PM_CONF_NRST_BITS_SET(x)                                        ((x << CFGREG_PM_CONF_NRST_SHIFT) & CFGREG_PM_CONF_NRST_MASK)                                                            /*!<  GNSS-AFE PM Configuration Register Bits Set */

#define CFGREG_LNA15_STAT_CAL_RDY_L5_BITS_SET(x)                               ((x << CFGREG_LNA15_STAT_CAL_RDY_L5_SHIFT) & CFGREG_LNA15_STAT_CAL_RDY_L5_MASK)                                          /*!<  LNA15 Status Register Bits Set */
#define CFGREG_LNA15_STAT_CAL_RDY_L1_BITS_SET(x)                               ((x << CFGREG_LNA15_STAT_CAL_RDY_L1_SHIFT) & CFGREG_LNA15_STAT_CAL_RDY_L1_MASK)                                          /*!<  LNA15 Status Register Bits Set */

#define CFGREG_LNA15_TUNE_STAT_L5_BITS_SET(x)                                  ((x << CFGREG_LNA15_TUNE_STAT_L5_SHIFT) & CFGREG_LNA15_TUNE_STAT_L5_MASK)                                                /*!<  LNA15 Tune Status Register Bits Set */
#define CFGREG_LNA15_TUNE_STAT_L1_BITS_SET(x)                                  ((x << CFGREG_LNA15_TUNE_STAT_L1_SHIFT) & CFGREG_LNA15_TUNE_STAT_L1_MASK)                                                /*!<  LNA15 Tune Status Register Bits Set */

#define CFGREG_LNA15_CONF_L5_TUNE_SRC_BITS_SET(x)                              ((x << CFGREG_LNA15_CONF_L5_TUNE_SRC_SHIFT) & CFGREG_LNA15_CONF_L5_TUNE_SRC_MASK)                                        /*!<  LNA15 Configuration Register Bits Set */
#define CFGREG_LNA15_CONF_L1_TUNE_SRC_BITS_SET(x)                              ((x << CFGREG_LNA15_CONF_L1_TUNE_SRC_SHIFT) & CFGREG_LNA15_CONF_L1_TUNE_SRC_MASK)                                        /*!<  LNA15 Configuration Register Bits Set */
#define CFGREG_LNA15_CONF_CAL_WORD_L5_BITS_SET(x)                              ((x << CFGREG_LNA15_CONF_CAL_WORD_L5_SHIFT) & CFGREG_LNA15_CONF_CAL_WORD_L5_MASK)                                        /*!<  LNA15 Configuration Register Bits Set */
#define CFGREG_LNA15_CONF_CAL_WORD_L1_BITS_SET(x)                              ((x << CFGREG_LNA15_CONF_CAL_WORD_L1_SHIFT) & CFGREG_LNA15_CONF_CAL_WORD_L1_MASK)                                        /*!<  LNA15 Configuration Register Bits Set */
#define CFGREG_LNA15_CONF_CAL_EN_L5_BITS_SET(x)                                ((x << CFGREG_LNA15_CONF_CAL_EN_L5_SHIFT) & CFGREG_LNA15_CONF_CAL_EN_L5_MASK)                                            /*!<  LNA15 Configuration Register Bits Set */
#define CFGREG_LNA15_CONF_CAL_EN_L1_BITS_SET(x)                                ((x << CFGREG_LNA15_CONF_CAL_EN_L1_SHIFT) & CFGREG_LNA15_CONF_CAL_EN_L1_MASK)                                            /*!<  LNA15 Configuration Register Bits Set */
#define CFGREG_LNA15_CONF_EN_L5_BITS_SET(x)                                    ((x << CFGREG_LNA15_CONF_EN_L5_SHIFT) & CFGREG_LNA15_CONF_EN_L5_MASK)                                                    /*!<  LNA15 Configuration Register Bits Set */
#define CFGREG_LNA15_CONF_EN_L1_BITS_SET(x)                                    ((x << CFGREG_LNA15_CONF_EN_L1_SHIFT) & CFGREG_LNA15_CONF_EN_L1_MASK)                                                    /*!<  LNA15 Configuration Register Bits Set */
#define CFGREG_LNA15_CONF_EN_BITS_SET(x)                                       ((x << CFGREG_LNA15_CONF_EN_SHIFT) & CFGREG_LNA15_CONF_EN_MASK)                                                          /*!<  LNA15 Configuration Register Bits Set */

#define CFGREG_LNA15_TUNE_CONF_L5_BITS_SET(x)                                  ((x << CFGREG_LNA15_TUNE_CONF_L5_SHIFT) & CFGREG_LNA15_TUNE_CONF_L5_MASK)                                                /*!<  LNA15 Configuration Register Bits Set */
#define CFGREG_LNA15_TUNE_CONF_L1_BITS_SET(x)                                  ((x << CFGREG_LNA15_TUNE_CONF_L1_SHIFT) & CFGREG_LNA15_TUNE_CONF_L1_MASK)                                                /*!<  LNA15 Configuration Register Bits Set */

#define CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SRC_BITS_SET(x)                    ((x << CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SRC_SHIFT) & CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SRC_MASK)                    /*!<  BALUN and MIXER 1 Configuration Register Bits Set */
#define CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_BITS_SET(x)                        ((x << CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SHIFT) & CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_MASK)                            /*!<  BALUN and MIXER 1 Configuration Register Bits Set */
#define CFGREG_BALUN_MIXER1_CONF_BALUN_EN_BITS_SET(x)                          ((x << CFGREG_BALUN_MIXER1_CONF_BALUN_EN_SHIFT) & CFGREG_BALUN_MIXER1_CONF_BALUN_EN_MASK)                                /*!<  BALUN and MIXER 1 Configuration Register Bits Set */
#define CFGREG_BALUN_MIXER1_CONF_MIXER_EN_BITS_SET(x)                          ((x << CFGREG_BALUN_MIXER1_CONF_MIXER_EN_SHIFT) & CFGREG_BALUN_MIXER1_CONF_MIXER_EN_MASK)                                /*!<  BALUN and MIXER 1 Configuration Register Bits Set */

#define CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SRC_BITS_SET(x)                    ((x << CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SRC_SHIFT) & CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SRC_MASK)                    /*!<  BALUN and MIXER 5 Configuration Register Bits Set */
#define CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_BITS_SET(x)                        ((x << CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SHIFT) & CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_MASK)                            /*!<  BALUN and MIXER 5 Configuration Register Bits Set */
#define CFGREG_BALUN_MIXER5_CONF_BALUN_EN_BITS_SET(x)                          ((x << CFGREG_BALUN_MIXER5_CONF_BALUN_EN_SHIFT) & CFGREG_BALUN_MIXER5_CONF_BALUN_EN_MASK)                                /*!<  BALUN and MIXER 5 Configuration Register Bits Set */
#define CFGREG_BALUN_MIXER5_CONF_MIXER_EN_BITS_SET(x)                          ((x << CFGREG_BALUN_MIXER5_CONF_MIXER_EN_SHIFT) & CFGREG_BALUN_MIXER5_CONF_MIXER_EN_MASK)                                /*!<  BALUN and MIXER 5 Configuration Register Bits Set */

#define CFGREG_PROBE_CONF_PLL15FB_SEL_BITS_SET(x)                              ((x << CFGREG_PROBE_CONF_PLL15FB_SEL_SHIFT) & CFGREG_PROBE_CONF_PLL15FB_SEL_MASK)                                        /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_CONF_PLL15FB_EN_BITS_SET(x)                               ((x << CFGREG_PROBE_CONF_PLL15FB_EN_SHIFT) & CFGREG_PROBE_CONF_PLL15FB_EN_MASK)                                          /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_CONF_IF5_PROBEB_SELECT_BITS_SET(x)                        ((x << CFGREG_PROBE_CONF_IF5_PROBEB_SELECT_SHIFT) & CFGREG_PROBE_CONF_IF5_PROBEB_SELECT_MASK)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_CONF_IF5_PROBEB_ENABLE_BITS_SET(x)                        ((x << CFGREG_PROBE_CONF_IF5_PROBEB_ENABLE_SHIFT) & CFGREG_PROBE_CONF_IF5_PROBEB_ENABLE_MASK)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_CONF_IF5_PROBEA_SELECT_BITS_SET(x)                        ((x << CFGREG_PROBE_CONF_IF5_PROBEA_SELECT_SHIFT) & CFGREG_PROBE_CONF_IF5_PROBEA_SELECT_MASK)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_CONF_IF1_PROBEB_SELECT_BITS_SET(x)                        ((x << CFGREG_PROBE_CONF_IF1_PROBEB_SELECT_SHIFT) & CFGREG_PROBE_CONF_IF1_PROBEB_SELECT_MASK)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_CONF_IF1_PROBEB_ENABLE_BITS_SET(x)                        ((x << CFGREG_PROBE_CONF_IF1_PROBEB_ENABLE_SHIFT) & CFGREG_PROBE_CONF_IF1_PROBEB_ENABLE_MASK)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */
#define CFGREG_PROBE_CONF_IF1_PROBEA_SELECT_BITS_SET(x)                        ((x << CFGREG_PROBE_CONF_IF1_PROBEA_SELECT_SHIFT) & CFGREG_PROBE_CONF_IF1_PROBEA_SELECT_MASK)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Set */

#define CFGREG_PLL1_CONF_LOPCB_EN_BITS_SET(x)                                  ((x << CFGREG_PLL1_CONF_LOPCB_EN_SHIFT) & CFGREG_PLL1_CONF_LOPCB_EN_MASK)                                                /*!<  PLL1 Configuration Register Bits Set */
#define CFGREG_PLL1_CONF_TEST_EN_BITS_SET(x)                                   ((x << CFGREG_PLL1_CONF_TEST_EN_SHIFT) & CFGREG_PLL1_CONF_TEST_EN_MASK)                                                  /*!<  PLL1 Configuration Register Bits Set */
#define CFGREG_PLL1_CONF_FCW_BITS_SET(x)                                       ((x << CFGREG_PLL1_CONF_FCW_SHIFT) & CFGREG_PLL1_CONF_FCW_MASK)                                                          /*!<  PLL1 Configuration Register Bits Set */
#define CFGREG_PLL1_CONF_EN_BITS_SET(x)                                        ((x << CFGREG_PLL1_CONF_EN_SHIFT) & CFGREG_PLL1_CONF_EN_MASK)                                                            /*!<  PLL1 Configuration Register Bits Set */

#define CFGREG_PLL1TDC_CONF_GAIN_BITS_SET(x)                                   ((x << CFGREG_PLL1TDC_CONF_GAIN_SHIFT) & CFGREG_PLL1TDC_CONF_GAIN_MASK)                                                  /*!<  PLL1 TDC Configuration Register Bits Set */
#define CFGREG_PLL1TDC_CONF_SCALE_BITS_SET(x)                                  ((x << CFGREG_PLL1TDC_CONF_SCALE_SHIFT) & CFGREG_PLL1TDC_CONF_SCALE_MASK)                                                /*!<  PLL1 TDC Configuration Register Bits Set */
#define CFGREG_PLL1TDC_CONF_LOAD_BITS_SET(x)                                   ((x << CFGREG_PLL1TDC_CONF_LOAD_SHIFT) & CFGREG_PLL1TDC_CONF_LOAD_MASK)                                                  /*!<  PLL1 TDC Configuration Register Bits Set */

#define CFGREG_PLL1DCO_CONF_AMP_BITS_SET(x)                                    ((x << CFGREG_PLL1DCO_CONF_AMP_SHIFT) & CFGREG_PLL1DCO_CONF_AMP_MASK)                                                    /*!<  PLL1 DCO Configuration Register Bits Set */
#define CFGREG_PLL1DCO_CONF_AMP_LOAD_BITS_SET(x)                               ((x << CFGREG_PLL1DCO_CONF_AMP_LOAD_SHIFT) & CFGREG_PLL1DCO_CONF_AMP_LOAD_MASK)                                          /*!<  PLL1 DCO Configuration Register Bits Set */
#define CFGREG_PLL1DCO_CONF_CTRL_PVT_BITS_SET(x)                               ((x << CFGREG_PLL1DCO_CONF_CTRL_PVT_SHIFT) & CFGREG_PLL1DCO_CONF_CTRL_PVT_MASK)                                          /*!<  PLL1 DCO Configuration Register Bits Set */
#define CFGREG_PLL1DCO_CONF_CTRL_FINE_BITS_SET(x)                              ((x << CFGREG_PLL1DCO_CONF_CTRL_FINE_SHIFT) & CFGREG_PLL1DCO_CONF_CTRL_FINE_MASK)                                        /*!<  PLL1 DCO Configuration Register Bits Set */
#define CFGREG_PLL1DCO_CONF_CTRL_LOAD_BITS_SET(x)                              ((x << CFGREG_PLL1DCO_CONF_CTRL_LOAD_SHIFT) & CFGREG_PLL1DCO_CONF_CTRL_LOAD_MASK)                                        /*!<  PLL1 DCO Configuration Register Bits Set */

#define CFGREG_PLL1_STAT_PHERR_BITS_SET(x)                                     ((x << CFGREG_PLL1_STAT_PHERR_SHIFT) & CFGREG_PLL1_STAT_PHERR_MASK)                                                      /*!<  PLL1 Status Register Bits Set */
#define CFGREG_PLL1_STAT_NDIV_BITS_SET(x)                                      ((x << CFGREG_PLL1_STAT_NDIV_SHIFT) & CFGREG_PLL1_STAT_NDIV_MASK)                                                        /*!<  PLL1 Status Register Bits Set */
#define CFGREG_PLL1_STAT_PHSEL_BITS_SET(x)                                     ((x << CFGREG_PLL1_STAT_PHSEL_SHIFT) & CFGREG_PLL1_STAT_PHSEL_MASK)                                                      /*!<  PLL1 Status Register Bits Set */
#define CFGREG_PLL1_STAT_LOCK_BITS_SET(x)                                      ((x << CFGREG_PLL1_STAT_LOCK_SHIFT) & CFGREG_PLL1_STAT_LOCK_MASK)                                                        /*!<  PLL1 Status Register Bits Set */

#define CFGREG_PLL1TDC_STAT_SCALE_BITS_SET(x)                                  ((x << CFGREG_PLL1TDC_STAT_SCALE_SHIFT) & CFGREG_PLL1TDC_STAT_SCALE_MASK)                                                /*!<  PLL1 TDC Status Register Bits Set */

#define CFGREG_PLL1DCO_STAT_AMP_BITS_SET(x)                                    ((x << CFGREG_PLL1DCO_STAT_AMP_SHIFT) & CFGREG_PLL1DCO_STAT_AMP_MASK)                                                    /*!<  PLL1 TDC Status Register Bits Set */
#define CFGREG_PLL1DCO_STAT_AMP_LOW_BITS_SET(x)                                ((x << CFGREG_PLL1DCO_STAT_AMP_LOW_SHIFT) & CFGREG_PLL1DCO_STAT_AMP_LOW_MASK)                                            /*!<  PLL1 TDC Status Register Bits Set */
#define CFGREG_PLL1DCO_STAT_CTRL_PVT_BITS_SET(x)                               ((x << CFGREG_PLL1DCO_STAT_CTRL_PVT_SHIFT) & CFGREG_PLL1DCO_STAT_CTRL_PVT_MASK)                                          /*!<  PLL1 TDC Status Register Bits Set */
#define CFGREG_PLL1DCO_STAT_CTRL_FINE_BITS_SET(x)                              ((x << CFGREG_PLL1DCO_STAT_CTRL_FINE_SHIFT) & CFGREG_PLL1DCO_STAT_CTRL_FINE_MASK)                                        /*!<  PLL1 TDC Status Register Bits Set */

#define CFGREG_IF1_CONF_AGC_IQ_SEP_BITS_SET(x)                                 ((x << CFGREG_IF1_CONF_AGC_IQ_SEP_SHIFT) & CFGREG_IF1_CONF_AGC_IQ_SEP_MASK)                                              /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_AGC_THR_BITS_SET(x)                                    ((x << CFGREG_IF1_CONF_AGC_THR_SHIFT) & CFGREG_IF1_CONF_AGC_THR_MASK)                                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_LPF_CAL_BITS_SET(x)                                    ((x << CFGREG_IF1_CONF_LPF_CAL_SHIFT) & CFGREG_IF1_CONF_LPF_CAL_MASK)                                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_LPF_GAIN_BITS_SET(x)                                   ((x << CFGREG_IF1_CONF_LPF_GAIN_SHIFT) & CFGREG_IF1_CONF_LPF_GAIN_MASK)                                                  /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_LPF_BAND_BITS_SET(x)                                   ((x << CFGREG_IF1_CONF_LPF_BAND_SHIFT) & CFGREG_IF1_CONF_LPF_BAND_MASK)                                                  /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_LPF_EN_BITS_SET(x)                                     ((x << CFGREG_IF1_CONF_LPF_EN_SHIFT) & CFGREG_IF1_CONF_LPF_EN_MASK)                                                      /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PGA2_GAIN_BITS_SET(x)                                  ((x << CFGREG_IF1_CONF_PGA2_GAIN_SHIFT) & CFGREG_IF1_CONF_PGA2_GAIN_MASK)                                                /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PGA2_EN_BITS_SET(x)                                    ((x << CFGREG_IF1_CONF_PGA2_EN_SHIFT) & CFGREG_IF1_CONF_PGA2_EN_MASK)                                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PGA1_1DB_GAIN_Q_BITS_SET(x)                            ((x << CFGREG_IF1_CONF_PGA1_1DB_GAIN_Q_SHIFT) & CFGREG_IF1_CONF_PGA1_1DB_GAIN_Q_MASK)                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PGA1_1DB_GAIN_I_BITS_SET(x)                            ((x << CFGREG_IF1_CONF_PGA1_1DB_GAIN_I_SHIFT) & CFGREG_IF1_CONF_PGA1_1DB_GAIN_I_MASK)                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PGA1_GAIN_BITS_SET(x)                                  ((x << CFGREG_IF1_CONF_PGA1_GAIN_SHIFT) & CFGREG_IF1_CONF_PGA1_GAIN_MASK)                                                /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PGA1_EN_BITS_SET(x)                                    ((x << CFGREG_IF1_CONF_PGA1_EN_SHIFT) & CFGREG_IF1_CONF_PGA1_EN_MASK)                                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_PREAMP_EN_BITS_SET(x)                                  ((x << CFGREG_IF1_CONF_PREAMP_EN_SHIFT) & CFGREG_IF1_CONF_PREAMP_EN_MASK)                                                /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_LOAD_EN_BITS_SET(x)                                    ((x << CFGREG_IF1_CONF_LOAD_EN_SHIFT) & CFGREG_IF1_CONF_LOAD_EN_MASK)                                                    /*!<  IF1 Configuration Register Bits Set */
#define CFGREG_IF1_CONF_EN_BITS_SET(x)                                         ((x << CFGREG_IF1_CONF_EN_SHIFT) & CFGREG_IF1_CONF_EN_MASK)                                                              /*!<  IF1 Configuration Register Bits Set */

#define CFGREG_IF1_STAT_AGC_CTRL_Q_BITS_SET(x)                                 ((x << CFGREG_IF1_STAT_AGC_CTRL_Q_SHIFT) & CFGREG_IF1_STAT_AGC_CTRL_Q_MASK)                                              /*!<  IF1 Status Register Bits Set */
#define CFGREG_IF1_STAT_AGC_CTRL_I_BITS_SET(x)                                 ((x << CFGREG_IF1_STAT_AGC_CTRL_I_SHIFT) & CFGREG_IF1_STAT_AGC_CTRL_I_MASK)                                              /*!<  IF1 Status Register Bits Set */

#define CFGREG_ADC1_CONF_CLK_SEL_BITS_SET(x)                                   ((x << CFGREG_ADC1_CONF_CLK_SEL_SHIFT) & CFGREG_ADC1_CONF_CLK_SEL_MASK)                                                  /*!<  ADC1 Configuration Register Bits Set */
#define CFGREG_ADC1_CONF_CLK_CONF_BITS_SET(x)                                  ((x << CFGREG_ADC1_CONF_CLK_CONF_SHIFT) & CFGREG_ADC1_CONF_CLK_CONF_MASK)                                                /*!<  ADC1 Configuration Register Bits Set */
#define CFGREG_ADC1_CONF_SAH_EN_BITS_SET(x)                                    ((x << CFGREG_ADC1_CONF_SAH_EN_SHIFT) & CFGREG_ADC1_CONF_SAH_EN_MASK)                                                    /*!<  ADC1 Configuration Register Bits Set */
#define CFGREG_ADC1_CONF_ADC_EN_BITS_SET(x)                                    ((x << CFGREG_ADC1_CONF_ADC_EN_SHIFT) & CFGREG_ADC1_CONF_ADC_EN_MASK)                                                    /*!<  ADC1 Configuration Register Bits Set */

#define CFGREG_PLL5_CONF_LOPCB_EN_BITS_SET(x)                                  ((x << CFGREG_PLL5_CONF_LOPCB_EN_SHIFT) & CFGREG_PLL5_CONF_LOPCB_EN_MASK)                                                /*!<  PLL5 Configuration Register Bits Set */
#define CFGREG_PLL5_CONF_TEST_EN_BITS_SET(x)                                   ((x << CFGREG_PLL5_CONF_TEST_EN_SHIFT) & CFGREG_PLL5_CONF_TEST_EN_MASK)                                                  /*!<  PLL5 Configuration Register Bits Set */
#define CFGREG_PLL5_CONF_FCW_BITS_SET(x)                                       ((x << CFGREG_PLL5_CONF_FCW_SHIFT) & CFGREG_PLL5_CONF_FCW_MASK)                                                          /*!<  PLL5 Configuration Register Bits Set */
#define CFGREG_PLL5_CONF_EN_BITS_SET(x)                                        ((x << CFGREG_PLL5_CONF_EN_SHIFT) & CFGREG_PLL5_CONF_EN_MASK)                                                            /*!<  PLL5 Configuration Register Bits Set */

#define CFGREG_PLL5TDC_CONF_GAIN_BITS_SET(x)                                   ((x << CFGREG_PLL5TDC_CONF_GAIN_SHIFT) & CFGREG_PLL5TDC_CONF_GAIN_MASK)                                                  /*!<  PLL5 TDC Configuration Register Bits Set */
#define CFGREG_PLL5TDC_CONF_SCALE_BITS_SET(x)                                  ((x << CFGREG_PLL5TDC_CONF_SCALE_SHIFT) & CFGREG_PLL5TDC_CONF_SCALE_MASK)                                                /*!<  PLL5 TDC Configuration Register Bits Set */
#define CFGREG_PLL5TDC_CONF_LOAD_BITS_SET(x)                                   ((x << CFGREG_PLL5TDC_CONF_LOAD_SHIFT) & CFGREG_PLL5TDC_CONF_LOAD_MASK)                                                  /*!<  PLL5 TDC Configuration Register Bits Set */

#define CFGREG_PLL5DCO_CONF_AMP_BITS_SET(x)                                    ((x << CFGREG_PLL5DCO_CONF_AMP_SHIFT) & CFGREG_PLL5DCO_CONF_AMP_MASK)                                                    /*!<  PLL5 DCO Configuration Register Bits Set */
#define CFGREG_PLL5DCO_CONF_AMP_LOAD_BITS_SET(x)                               ((x << CFGREG_PLL5DCO_CONF_AMP_LOAD_SHIFT) & CFGREG_PLL5DCO_CONF_AMP_LOAD_MASK)                                          /*!<  PLL5 DCO Configuration Register Bits Set */
#define CFGREG_PLL5DCO_CONF_CTRL_PVT_BITS_SET(x)                               ((x << CFGREG_PLL5DCO_CONF_CTRL_PVT_SHIFT) & CFGREG_PLL5DCO_CONF_CTRL_PVT_MASK)                                          /*!<  PLL5 DCO Configuration Register Bits Set */
#define CFGREG_PLL5DCO_CONF_CTRL_FINE_BITS_SET(x)                              ((x << CFGREG_PLL5DCO_CONF_CTRL_FINE_SHIFT) & CFGREG_PLL5DCO_CONF_CTRL_FINE_MASK)                                        /*!<  PLL5 DCO Configuration Register Bits Set */
#define CFGREG_PLL5DCO_CONF_CTRL_LOAD_BITS_SET(x)                              ((x << CFGREG_PLL5DCO_CONF_CTRL_LOAD_SHIFT) & CFGREG_PLL5DCO_CONF_CTRL_LOAD_MASK)                                        /*!<  PLL5 DCO Configuration Register Bits Set */

#define CFGREG_PLL5_STAT_PHERR_BITS_SET(x)                                     ((x << CFGREG_PLL5_STAT_PHERR_SHIFT) & CFGREG_PLL5_STAT_PHERR_MASK)                                                      /*!<  PLL5 Status Register Bits Set */
#define CFGREG_PLL5_STAT_NDIV_BITS_SET(x)                                      ((x << CFGREG_PLL5_STAT_NDIV_SHIFT) & CFGREG_PLL5_STAT_NDIV_MASK)                                                        /*!<  PLL5 Status Register Bits Set */
#define CFGREG_PLL5_STAT_PHSEL_BITS_SET(x)                                     ((x << CFGREG_PLL5_STAT_PHSEL_SHIFT) & CFGREG_PLL5_STAT_PHSEL_MASK)                                                      /*!<  PLL5 Status Register Bits Set */
#define CFGREG_PLL5_STAT_LOCK_BITS_SET(x)                                      ((x << CFGREG_PLL5_STAT_LOCK_SHIFT) & CFGREG_PLL5_STAT_LOCK_MASK)                                                        /*!<  PLL5 Status Register Bits Set */

#define CFGREG_PLL5TDC_STAT_SCALE_BITS_SET(x)                                  ((x << CFGREG_PLL5TDC_STAT_SCALE_SHIFT) & CFGREG_PLL5TDC_STAT_SCALE_MASK)                                                /*!<  PLL5 TDC Status Register Bits Set */

#define CFGREG_PLL5DCO_STAT_AMP_BITS_SET(x)                                    ((x << CFGREG_PLL5DCO_STAT_AMP_SHIFT) & CFGREG_PLL5DCO_STAT_AMP_MASK)                                                    /*!<  PLL5 TDC Status Register Bits Set */
#define CFGREG_PLL5DCO_STAT_AMP_LOW_BITS_SET(x)                                ((x << CFGREG_PLL5DCO_STAT_AMP_LOW_SHIFT) & CFGREG_PLL5DCO_STAT_AMP_LOW_MASK)                                            /*!<  PLL5 TDC Status Register Bits Set */
#define CFGREG_PLL5DCO_STAT_CTRL_PVT_BITS_SET(x)                               ((x << CFGREG_PLL5DCO_STAT_CTRL_PVT_SHIFT) & CFGREG_PLL5DCO_STAT_CTRL_PVT_MASK)                                          /*!<  PLL5 TDC Status Register Bits Set */
#define CFGREG_PLL5DCO_STAT_CTRL_FINE_BITS_SET(x)                              ((x << CFGREG_PLL5DCO_STAT_CTRL_FINE_SHIFT) & CFGREG_PLL5DCO_STAT_CTRL_FINE_MASK)                                        /*!<  PLL5 TDC Status Register Bits Set */

#define CFGREG_IF5_CONF_AGC_IQ_SEP_BITS_SET(x)                                 ((x << CFGREG_IF5_CONF_AGC_IQ_SEP_SHIFT) & CFGREG_IF5_CONF_AGC_IQ_SEP_MASK)                                              /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_AGC_THR_BITS_SET(x)                                    ((x << CFGREG_IF5_CONF_AGC_THR_SHIFT) & CFGREG_IF5_CONF_AGC_THR_MASK)                                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_LPF_CAL_BITS_SET(x)                                    ((x << CFGREG_IF5_CONF_LPF_CAL_SHIFT) & CFGREG_IF5_CONF_LPF_CAL_MASK)                                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_LPF_GAIN_BITS_SET(x)                                   ((x << CFGREG_IF5_CONF_LPF_GAIN_SHIFT) & CFGREG_IF5_CONF_LPF_GAIN_MASK)                                                  /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_LPF_BAND_BITS_SET(x)                                   ((x << CFGREG_IF5_CONF_LPF_BAND_SHIFT) & CFGREG_IF5_CONF_LPF_BAND_MASK)                                                  /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_LPF_EN_BITS_SET(x)                                     ((x << CFGREG_IF5_CONF_LPF_EN_SHIFT) & CFGREG_IF5_CONF_LPF_EN_MASK)                                                      /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PGA2_GAIN_BITS_SET(x)                                  ((x << CFGREG_IF5_CONF_PGA2_GAIN_SHIFT) & CFGREG_IF5_CONF_PGA2_GAIN_MASK)                                                /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PGA2_EN_BITS_SET(x)                                    ((x << CFGREG_IF5_CONF_PGA2_EN_SHIFT) & CFGREG_IF5_CONF_PGA2_EN_MASK)                                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PGA1_1DB_GAIN_Q_BITS_SET(x)                            ((x << CFGREG_IF5_CONF_PGA1_1DB_GAIN_Q_SHIFT) & CFGREG_IF5_CONF_PGA1_1DB_GAIN_Q_MASK)                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PGA1_1DB_GAIN_I_BITS_SET(x)                            ((x << CFGREG_IF5_CONF_PGA1_1DB_GAIN_I_SHIFT) & CFGREG_IF5_CONF_PGA1_1DB_GAIN_I_MASK)                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PGA1_GAIN_BITS_SET(x)                                  ((x << CFGREG_IF5_CONF_PGA1_GAIN_SHIFT) & CFGREG_IF5_CONF_PGA1_GAIN_MASK)                                                /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PGA1_EN_BITS_SET(x)                                    ((x << CFGREG_IF5_CONF_PGA1_EN_SHIFT) & CFGREG_IF5_CONF_PGA1_EN_MASK)                                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_PREAMP_EN_BITS_SET(x)                                  ((x << CFGREG_IF5_CONF_PREAMP_EN_SHIFT) & CFGREG_IF5_CONF_PREAMP_EN_MASK)                                                /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_LOAD_EN_BITS_SET(x)                                    ((x << CFGREG_IF5_CONF_LOAD_EN_SHIFT) & CFGREG_IF5_CONF_LOAD_EN_MASK)                                                    /*!<  IF5 Configuration Register Bits Set */
#define CFGREG_IF5_CONF_EN_BITS_SET(x)                                         ((x << CFGREG_IF5_CONF_EN_SHIFT) & CFGREG_IF5_CONF_EN_MASK)                                                              /*!<  IF5 Configuration Register Bits Set */

#define CFGREG_IF5_STAT_AGC_CTRL_Q_BITS_SET(x)                                 ((x << CFGREG_IF5_STAT_AGC_CTRL_Q_SHIFT) & CFGREG_IF5_STAT_AGC_CTRL_Q_MASK)                                              /*!<  IF5 Status Register Bits Set */
#define CFGREG_IF5_STAT_AGC_CTRL_I_BITS_SET(x)                                 ((x << CFGREG_IF5_STAT_AGC_CTRL_I_SHIFT) & CFGREG_IF5_STAT_AGC_CTRL_I_MASK)                                              /*!<  IF5 Status Register Bits Set */

#define CFGREG_ADC5_CONF_CLK_SEL_BITS_SET(x)                                   ((x << CFGREG_ADC5_CONF_CLK_SEL_SHIFT) & CFGREG_ADC5_CONF_CLK_SEL_MASK)                                                  /*!<  ADC5 Configuration Register Bits Set */
#define CFGREG_ADC5_CONF_CLK_CONF_BITS_SET(x)                                  ((x << CFGREG_ADC5_CONF_CLK_CONF_SHIFT) & CFGREG_ADC5_CONF_CLK_CONF_MASK)                                                /*!<  ADC5 Configuration Register Bits Set */
#define CFGREG_ADC5_CONF_SAH_EN_BITS_SET(x)                                    ((x << CFGREG_ADC5_CONF_SAH_EN_SHIFT) & CFGREG_ADC5_CONF_SAH_EN_MASK)                                                    /*!<  ADC5 Configuration Register Bits Set */
#define CFGREG_ADC5_CONF_ADC_EN_BITS_SET(x)                                    ((x << CFGREG_ADC5_CONF_ADC_EN_SHIFT) & CFGREG_ADC5_CONF_ADC_EN_MASK)                                                    /*!<  ADC5 Configuration Register Bits Set */

#define CFGREG_SPARE_CONF_SIG_BITS_SET(x)                                      ((x << CFGREG_SPARE_CONF_SIG_SHIFT) & CFGREG_SPARE_CONF_SIG_MASK)                                                        /*!<  SPARE Configuration Register Bits Set */

#define CFGREG_SPARE_STAT_SIG_BITS_SET(x)                                      ((x << CFGREG_SPARE_STAT_SIG_SHIFT) & CFGREG_SPARE_STAT_SIG_MASK)                                                        /*!<  SPARE Configuration Register Bits Set */

#define CFGREG_GNSSAFE_TEST_CONF_SIG_BITS_SET(x)                               ((x << CFGREG_GNSSAFE_TEST_CONF_SIG_SHIFT) & CFGREG_GNSSAFE_TEST_CONF_SIG_MASK)                                          /*!<  TEST Configuration Register Bits Set */

#define CFGREG_GNSSAFE_TEST_STAT_SIG_BITS_SET(x)                               ((x << CFGREG_GNSSAFE_TEST_STAT_SIG_SHIFT) & CFGREG_GNSSAFE_TEST_STAT_SIG_MASK)                                          /*!<  TEST Configuration Register Bits Set */


/** Bits Get Helper Macros */

#define CFGREG_IRQMAP_IRQMAP_BITS_GET(x)                                       ((x & CFGREG_IRQMAP_IRQMAP_MASK) >> CFGREG_IRQMAP_IRQMAP_SHIFT)                                                          /*!<  Interrupt Mapping Register Bits Get */

#define CFGREG_UNLOCK_UNLOCK_KEY_BITS_GET(x)                                   ((x & CFGREG_UNLOCK_UNLOCK_KEY_MASK) >> CFGREG_UNLOCK_UNLOCK_KEY_SHIFT)                                                  /*!<  Unlock Register Bits Get */

#define CFGREG_IRQFLAGS_PLL_FAIL_BITS_GET(x)                                   ((x & CFGREG_IRQFLAGS_PLL_FAIL_MASK) >> CFGREG_IRQFLAGS_PLL_FAIL_SHIFT)                                                  /*!<  32kHz RTC Clock Interrupt Flags Bits Get */
#define CFGREG_IRQFLAGS_XTAL_CORE_FAIL_BITS_GET(x)                             ((x & CFGREG_IRQFLAGS_XTAL_CORE_FAIL_MASK) >> CFGREG_IRQFLAGS_XTAL_CORE_FAIL_SHIFT)                                      /*!<  32kHz RTC Clock Interrupt Flags Bits Get */
#define CFGREG_IRQFLAGS_XTAL_RTC_FAIL_BITS_GET(x)                              ((x & CFGREG_IRQFLAGS_XTAL_RTC_FAIL_MASK) >> CFGREG_IRQFLAGS_XTAL_RTC_FAIL_SHIFT)                                        /*!<  32kHz RTC Clock Interrupt Flags Bits Get */

#define CFGREG_PMU_CONF_IREF_CAL_EN_BITS_GET(x)                                ((x & CFGREG_PMU_CONF_IREF_CAL_EN_MASK) >> CFGREG_PMU_CONF_IREF_CAL_EN_SHIFT)                                            /*!<  Power Management Unit Configuration Bits Get */
#define CFGREG_PMU_CONF_IREF_TRIM_VAL_SRC_BITS_GET(x)                          ((x & CFGREG_PMU_CONF_IREF_TRIM_VAL_SRC_MASK) >> CFGREG_PMU_CONF_IREF_TRIM_VAL_SRC_SHIFT)                                /*!<  Power Management Unit Configuration Bits Get */
#define CFGREG_PMU_CONF_IREF_TRIM_VAL_BITS_GET(x)                              ((x & CFGREG_PMU_CONF_IREF_TRIM_VAL_MASK) >> CFGREG_PMU_CONF_IREF_TRIM_VAL_SHIFT)                                        /*!<  Power Management Unit Configuration Bits Get */
#define CFGREG_PMU_CONF_IREF_TRIM_EN_BITS_GET(x)                               ((x & CFGREG_PMU_CONF_IREF_TRIM_EN_MASK) >> CFGREG_PMU_CONF_IREF_TRIM_EN_SHIFT)                                          /*!<  Power Management Unit Configuration Bits Get */

#define CFGREG_PMU_STAT_IREF_TRIM_VAL_BITS_GET(x)                              ((x & CFGREG_PMU_STAT_IREF_TRIM_VAL_MASK) >> CFGREG_PMU_STAT_IREF_TRIM_VAL_SHIFT)                                        /*!<  Power Management Unit Status Bits Get */
#define CFGREG_PMU_STAT_IREF_CAL_RDY_BITS_GET(x)                               ((x & CFGREG_PMU_STAT_IREF_CAL_RDY_MASK) >> CFGREG_PMU_STAT_IREF_CAL_RDY_SHIFT)                                          /*!<  Power Management Unit Status Bits Get */

#define CFGREG_RTCSTAT_RC_RTC_VAL_BITS_GET(x)                                  ((x & CFGREG_RTCSTAT_RC_RTC_VAL_MASK) >> CFGREG_RTCSTAT_RC_RTC_VAL_SHIFT)                                                /*!<  32kHz RTC Clock Status Bits Get */
#define CFGREG_RTCSTAT_RC_RTC_RDY_BITS_GET(x)                                  ((x & CFGREG_RTCSTAT_RC_RTC_RDY_MASK) >> CFGREG_RTCSTAT_RC_RTC_RDY_SHIFT)                                                /*!<  32kHz RTC Clock Status Bits Get */
#define CFGREG_RTCSTAT_CLK_RTC_SEL_BITS_GET(x)                                 ((x & CFGREG_RTCSTAT_CLK_RTC_SEL_MASK) >> CFGREG_RTCSTAT_CLK_RTC_SEL_SHIFT)                                              /*!<  32kHz RTC Clock Status Bits Get */

#define CFGREG_RTCCONF_RC_RTC_VAL_SRC_BITS_GET(x)                              ((x & CFGREG_RTCCONF_RC_RTC_VAL_SRC_MASK) >> CFGREG_RTCCONF_RC_RTC_VAL_SRC_SHIFT)                                        /*!<  32kHz RTC Clock Configuration Bits Get */
#define CFGREG_RTCCONF_RC_RTC_VAL_BITS_GET(x)                                  ((x & CFGREG_RTCCONF_RC_RTC_VAL_MASK) >> CFGREG_RTCCONF_RC_RTC_VAL_SHIFT)                                                /*!<  32kHz RTC Clock Configuration Bits Get */
#define CFGREG_RTCCONF_RC_RTC_CAL_BITS_GET(x)                                  ((x & CFGREG_RTCCONF_RC_RTC_CAL_MASK) >> CFGREG_RTCCONF_RC_RTC_CAL_SHIFT)                                                /*!<  32kHz RTC Clock Configuration Bits Get */
#define CFGREG_RTCCONF_XTAL_RTC_SEL_BITS_GET(x)                                ((x & CFGREG_RTCCONF_XTAL_RTC_SEL_MASK) >> CFGREG_RTCCONF_XTAL_RTC_SEL_SHIFT)                                            /*!<  32kHz RTC Clock Configuration Bits Get */
#define CFGREG_RTCCONF_XTAL_RTC_TEST_BITS_GET(x)                               ((x & CFGREG_RTCCONF_XTAL_RTC_TEST_MASK) >> CFGREG_RTCCONF_XTAL_RTC_TEST_SHIFT)                                          /*!<  32kHz RTC Clock Configuration Bits Get */

#define CFGREG_COREFREQ_CLK_TEST_OUT_EN_BITS_GET(x)                            ((x & CFGREG_COREFREQ_CLK_TEST_OUT_EN_MASK) >> CFGREG_COREFREQ_CLK_TEST_OUT_EN_SHIFT)                                    /*!<  External XTAL Configuration Register Bits Get */
#define CFGREG_COREFREQ_CLK_RC_CORE_VAL_SRC_BITS_GET(x)                        ((x & CFGREG_COREFREQ_CLK_RC_CORE_VAL_SRC_MASK) >> CFGREG_COREFREQ_CLK_RC_CORE_VAL_SRC_SHIFT)                            /*!<  External XTAL Configuration Register Bits Get */
#define CFGREG_COREFREQ_CLK_RC_CORE_VAL_BITS_GET(x)                            ((x & CFGREG_COREFREQ_CLK_RC_CORE_VAL_MASK) >> CFGREG_COREFREQ_CLK_RC_CORE_VAL_SHIFT)                                    /*!<  External XTAL Configuration Register Bits Get */
#define CFGREG_COREFREQ_CLK_RC_CORE_CAL_BITS_GET(x)                            ((x & CFGREG_COREFREQ_CLK_RC_CORE_CAL_MASK) >> CFGREG_COREFREQ_CLK_RC_CORE_CAL_SHIFT)                                    /*!<  External XTAL Configuration Register Bits Get */
#define CFGREG_COREFREQ_CLK_CORE_SEL_BITS_GET(x)                               ((x & CFGREG_COREFREQ_CLK_CORE_SEL_MASK) >> CFGREG_COREFREQ_CLK_CORE_SEL_SHIFT)                                          /*!<  External XTAL Configuration Register Bits Get */
#define CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_BITS_GET(x)                         ((x & CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_MASK) >> CFGREG_COREFREQ_CLK_XTAL_CORE_TEST_SHIFT)                              /*!<  External XTAL Configuration Register Bits Get */

#define CFGREG_COREFREQ_PLL_PLL_VFB_EN_BITS_GET(x)                             ((x & CFGREG_COREFREQ_PLL_PLL_VFB_EN_MASK) >> CFGREG_COREFREQ_PLL_PLL_VFB_EN_SHIFT)                                      /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_TEST_BITS_GET(x)                                   ((x & CFGREG_COREFREQ_PLL_TEST_MASK) >> CFGREG_COREFREQ_PLL_TEST_SHIFT)                                                  /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_N_BITS_GET(x)                                      ((x & CFGREG_COREFREQ_PLL_N_MASK) >> CFGREG_COREFREQ_PLL_N_SHIFT)                                                        /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_M_BITS_GET(x)                                      ((x & CFGREG_COREFREQ_PLL_M_MASK) >> CFGREG_COREFREQ_PLL_M_SHIFT)                                                        /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_REF_SEL_BITS_GET(x)                                ((x & CFGREG_COREFREQ_PLL_REF_SEL_MASK) >> CFGREG_COREFREQ_PLL_REF_SEL_SHIFT)                                            /*!<  PLL Configuration Register Bits Get */
#define CFGREG_COREFREQ_PLL_EN_BITS_GET(x)                                     ((x & CFGREG_COREFREQ_PLL_EN_MASK) >> CFGREG_COREFREQ_PLL_EN_SHIFT)                                                      /*!<  PLL Configuration Register Bits Get */

#define CFGREG_COREFREQ_STAT_RC_CORE_VAL_BITS_GET(x)                           ((x & CFGREG_COREFREQ_STAT_RC_CORE_VAL_MASK) >> CFGREG_COREFREQ_STAT_RC_CORE_VAL_SHIFT)                                  /*!<  Core Clock Status Register Bits Get */
#define CFGREG_COREFREQ_STAT_RC_CORE_RDY_BITS_GET(x)                           ((x & CFGREG_COREFREQ_STAT_RC_CORE_RDY_MASK) >> CFGREG_COREFREQ_STAT_RC_CORE_RDY_SHIFT)                                  /*!<  Core Clock Status Register Bits Get */
#define CFGREG_COREFREQ_STAT_PLL_LOCK_BITS_GET(x)                              ((x & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK) >> CFGREG_COREFREQ_STAT_PLL_LOCK_SHIFT)                                        /*!<  Core Clock Status Register Bits Get */
#define CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_BITS_GET(x)                        ((x & CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_MASK) >> CFGREG_COREFREQ_STAT_XTAL_CORE_LOCK_SHIFT)                            /*!<  Core Clock Status Register Bits Get */
#define CFGREG_COREFREQ_STAT_CLK_CORE_SEL_BITS_GET(x)                          ((x & CFGREG_COREFREQ_STAT_CLK_CORE_SEL_MASK) >> CFGREG_COREFREQ_STAT_CLK_CORE_SEL_SHIFT)                                /*!<  Core Clock Status Register Bits Get */

#define CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_BITS_GET(x)                           ((x & CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_MASK) >> CFGREG_GNSSAFE_CONF_GNSS_EXT_ADC_SHIFT)                                  /*!<  GNSS-AFE Configuration Register Bits Get */
#define CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_BITS_GET(x)                          ((x & CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_MASK) >> CFGREG_GNSSAFE_CONF_GNSS_OUT_BAND_SHIFT)                                /*!<  GNSS-AFE Configuration Register Bits Get */

#define CFGREG_PM_STAT_IREF_COMP_BITS_GET(x)                                   ((x & CFGREG_PM_STAT_IREF_COMP_MASK) >> CFGREG_PM_STAT_IREF_COMP_SHIFT)                                                  /*!<  GNSS-AFE PM Status Register Bits Get */
#define CFGREG_PM_STAT_VREF_COMP_BITS_GET(x)                                   ((x & CFGREG_PM_STAT_VREF_COMP_MASK) >> CFGREG_PM_STAT_VREF_COMP_SHIFT)                                                  /*!<  GNSS-AFE PM Status Register Bits Get */
#define CFGREG_PM_STAT_PWR_UP_BITS_GET(x)                                      ((x & CFGREG_PM_STAT_PWR_UP_MASK) >> CFGREG_PM_STAT_PWR_UP_SHIFT)                                                        /*!<  GNSS-AFE PM Status Register Bits Get */

#define CFGREG_PM_CONF_CAL_EN_BITS_GET(x)                                      ((x & CFGREG_PM_CONF_CAL_EN_MASK) >> CFGREG_PM_CONF_CAL_EN_SHIFT)                                                        /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_TEST_EN_BITS_GET(x)                                     ((x & CFGREG_PM_CONF_TEST_EN_MASK) >> CFGREG_PM_CONF_TEST_EN_SHIFT)                                                      /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_LDO_ADC_EN_BITS_GET(x)                                  ((x & CFGREG_PM_CONF_LDO_ADC_EN_MASK) >> CFGREG_PM_CONF_LDO_ADC_EN_SHIFT)                                                /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_LDO_IF_EN_BITS_GET(x)                                   ((x & CFGREG_PM_CONF_LDO_IF_EN_MASK) >> CFGREG_PM_CONF_LDO_IF_EN_SHIFT)                                                  /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_LDO_DPLL_EN_BITS_GET(x)                                 ((x & CFGREG_PM_CONF_LDO_DPLL_EN_MASK) >> CFGREG_PM_CONF_LDO_DPLL_EN_SHIFT)                                              /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_LDO_APLL_EN_BITS_GET(x)                                 ((x & CFGREG_PM_CONF_LDO_APLL_EN_MASK) >> CFGREG_PM_CONF_LDO_APLL_EN_SHIFT)                                              /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_LDO_RF_EN_BITS_GET(x)                                   ((x & CFGREG_PM_CONF_LDO_RF_EN_MASK) >> CFGREG_PM_CONF_LDO_RF_EN_SHIFT)                                                  /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_VREF_EN_BITS_GET(x)                                     ((x & CFGREG_PM_CONF_VREF_EN_MASK) >> CFGREG_PM_CONF_VREF_EN_SHIFT)                                                      /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_IREF_TRIM_SRC_BITS_GET(x)                               ((x & CFGREG_PM_CONF_IREF_TRIM_SRC_MASK) >> CFGREG_PM_CONF_IREF_TRIM_SRC_SHIFT)                                          /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_IREF_TRIM_BITS_GET(x)                                   ((x & CFGREG_PM_CONF_IREF_TRIM_MASK) >> CFGREG_PM_CONF_IREF_TRIM_SHIFT)                                                  /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_IREF_EN_BITS_GET(x)                                     ((x & CFGREG_PM_CONF_IREF_EN_MASK) >> CFGREG_PM_CONF_IREF_EN_SHIFT)                                                      /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_BGVR_TRIM_SRC_BITS_GET(x)                               ((x & CFGREG_PM_CONF_BGVR_TRIM_SRC_MASK) >> CFGREG_PM_CONF_BGVR_TRIM_SRC_SHIFT)                                          /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_BGVR_TRIM_BITS_GET(x)                                   ((x & CFGREG_PM_CONF_BGVR_TRIM_MASK) >> CFGREG_PM_CONF_BGVR_TRIM_SHIFT)                                                  /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_BGVR_EN_BITS_GET(x)                                     ((x & CFGREG_PM_CONF_BGVR_EN_MASK) >> CFGREG_PM_CONF_BGVR_EN_SHIFT)                                                      /*!<  GNSS-AFE PM Configuration Register Bits Get */
#define CFGREG_PM_CONF_NRST_BITS_GET(x)                                        ((x & CFGREG_PM_CONF_NRST_MASK) >> CFGREG_PM_CONF_NRST_SHIFT)                                                            /*!<  GNSS-AFE PM Configuration Register Bits Get */

#define CFGREG_LNA15_STAT_CAL_RDY_L5_BITS_GET(x)                               ((x & CFGREG_LNA15_STAT_CAL_RDY_L5_MASK) >> CFGREG_LNA15_STAT_CAL_RDY_L5_SHIFT)                                          /*!<  LNA15 Status Register Bits Get */
#define CFGREG_LNA15_STAT_CAL_RDY_L1_BITS_GET(x)                               ((x & CFGREG_LNA15_STAT_CAL_RDY_L1_MASK) >> CFGREG_LNA15_STAT_CAL_RDY_L1_SHIFT)                                          /*!<  LNA15 Status Register Bits Get */

#define CFGREG_LNA15_TUNE_STAT_L5_BITS_GET(x)                                  ((x & CFGREG_LNA15_TUNE_STAT_L5_MASK) >> CFGREG_LNA15_TUNE_STAT_L5_SHIFT)                                                /*!<  LNA15 Tune Status Register Bits Get */
#define CFGREG_LNA15_TUNE_STAT_L1_BITS_GET(x)                                  ((x & CFGREG_LNA15_TUNE_STAT_L1_MASK) >> CFGREG_LNA15_TUNE_STAT_L1_SHIFT)                                                /*!<  LNA15 Tune Status Register Bits Get */

#define CFGREG_LNA15_CONF_L5_TUNE_SRC_BITS_GET(x)                              ((x & CFGREG_LNA15_CONF_L5_TUNE_SRC_MASK) >> CFGREG_LNA15_CONF_L5_TUNE_SRC_SHIFT)                                        /*!<  LNA15 Configuration Register Bits Get */
#define CFGREG_LNA15_CONF_L1_TUNE_SRC_BITS_GET(x)                              ((x & CFGREG_LNA15_CONF_L1_TUNE_SRC_MASK) >> CFGREG_LNA15_CONF_L1_TUNE_SRC_SHIFT)                                        /*!<  LNA15 Configuration Register Bits Get */
#define CFGREG_LNA15_CONF_CAL_WORD_L5_BITS_GET(x)                              ((x & CFGREG_LNA15_CONF_CAL_WORD_L5_MASK) >> CFGREG_LNA15_CONF_CAL_WORD_L5_SHIFT)                                        /*!<  LNA15 Configuration Register Bits Get */
#define CFGREG_LNA15_CONF_CAL_WORD_L1_BITS_GET(x)                              ((x & CFGREG_LNA15_CONF_CAL_WORD_L1_MASK) >> CFGREG_LNA15_CONF_CAL_WORD_L1_SHIFT)                                        /*!<  LNA15 Configuration Register Bits Get */
#define CFGREG_LNA15_CONF_CAL_EN_L5_BITS_GET(x)                                ((x & CFGREG_LNA15_CONF_CAL_EN_L5_MASK) >> CFGREG_LNA15_CONF_CAL_EN_L5_SHIFT)                                            /*!<  LNA15 Configuration Register Bits Get */
#define CFGREG_LNA15_CONF_CAL_EN_L1_BITS_GET(x)                                ((x & CFGREG_LNA15_CONF_CAL_EN_L1_MASK) >> CFGREG_LNA15_CONF_CAL_EN_L1_SHIFT)                                            /*!<  LNA15 Configuration Register Bits Get */
#define CFGREG_LNA15_CONF_EN_L5_BITS_GET(x)                                    ((x & CFGREG_LNA15_CONF_EN_L5_MASK) >> CFGREG_LNA15_CONF_EN_L5_SHIFT)                                                    /*!<  LNA15 Configuration Register Bits Get */
#define CFGREG_LNA15_CONF_EN_L1_BITS_GET(x)                                    ((x & CFGREG_LNA15_CONF_EN_L1_MASK) >> CFGREG_LNA15_CONF_EN_L1_SHIFT)                                                    /*!<  LNA15 Configuration Register Bits Get */
#define CFGREG_LNA15_CONF_EN_BITS_GET(x)                                       ((x & CFGREG_LNA15_CONF_EN_MASK) >> CFGREG_LNA15_CONF_EN_SHIFT)                                                          /*!<  LNA15 Configuration Register Bits Get */

#define CFGREG_LNA15_TUNE_CONF_L5_BITS_GET(x)                                  ((x & CFGREG_LNA15_TUNE_CONF_L5_MASK) >> CFGREG_LNA15_TUNE_CONF_L5_SHIFT)                                                /*!<  LNA15 Configuration Register Bits Get */
#define CFGREG_LNA15_TUNE_CONF_L1_BITS_GET(x)                                  ((x & CFGREG_LNA15_TUNE_CONF_L1_MASK) >> CFGREG_LNA15_TUNE_CONF_L1_SHIFT)                                                /*!<  LNA15 Configuration Register Bits Get */

#define CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SRC_BITS_GET(x)                    ((x & CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SRC_MASK) >> CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SRC_SHIFT)                    /*!<  BALUN and MIXER 1 Configuration Register Bits Get */
#define CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_BITS_GET(x)                        ((x & CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_MASK) >> CFGREG_BALUN_MIXER1_CONF_BALUN_TUNE_SHIFT)                            /*!<  BALUN and MIXER 1 Configuration Register Bits Get */
#define CFGREG_BALUN_MIXER1_CONF_BALUN_EN_BITS_GET(x)                          ((x & CFGREG_BALUN_MIXER1_CONF_BALUN_EN_MASK) >> CFGREG_BALUN_MIXER1_CONF_BALUN_EN_SHIFT)                                /*!<  BALUN and MIXER 1 Configuration Register Bits Get */
#define CFGREG_BALUN_MIXER1_CONF_MIXER_EN_BITS_GET(x)                          ((x & CFGREG_BALUN_MIXER1_CONF_MIXER_EN_MASK) >> CFGREG_BALUN_MIXER1_CONF_MIXER_EN_SHIFT)                                /*!<  BALUN and MIXER 1 Configuration Register Bits Get */

#define CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SRC_BITS_GET(x)                    ((x & CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SRC_MASK) >> CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SRC_SHIFT)                    /*!<  BALUN and MIXER 5 Configuration Register Bits Get */
#define CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_BITS_GET(x)                        ((x & CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_MASK) >> CFGREG_BALUN_MIXER5_CONF_BALUN_TUNE_SHIFT)                            /*!<  BALUN and MIXER 5 Configuration Register Bits Get */
#define CFGREG_BALUN_MIXER5_CONF_BALUN_EN_BITS_GET(x)                          ((x & CFGREG_BALUN_MIXER5_CONF_BALUN_EN_MASK) >> CFGREG_BALUN_MIXER5_CONF_BALUN_EN_SHIFT)                                /*!<  BALUN and MIXER 5 Configuration Register Bits Get */
#define CFGREG_BALUN_MIXER5_CONF_MIXER_EN_BITS_GET(x)                          ((x & CFGREG_BALUN_MIXER5_CONF_MIXER_EN_MASK) >> CFGREG_BALUN_MIXER5_CONF_MIXER_EN_SHIFT)                                /*!<  BALUN and MIXER 5 Configuration Register Bits Get */

#define CFGREG_PROBE_CONF_PLL15FB_SEL_BITS_GET(x)                              ((x & CFGREG_PROBE_CONF_PLL15FB_SEL_MASK) >> CFGREG_PROBE_CONF_PLL15FB_SEL_SHIFT)                                        /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_CONF_PLL15FB_EN_BITS_GET(x)                               ((x & CFGREG_PROBE_CONF_PLL15FB_EN_MASK) >> CFGREG_PROBE_CONF_PLL15FB_EN_SHIFT)                                          /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_CONF_IF5_PROBEB_SELECT_BITS_GET(x)                        ((x & CFGREG_PROBE_CONF_IF5_PROBEB_SELECT_MASK) >> CFGREG_PROBE_CONF_IF5_PROBEB_SELECT_SHIFT)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_CONF_IF5_PROBEB_ENABLE_BITS_GET(x)                        ((x & CFGREG_PROBE_CONF_IF5_PROBEB_ENABLE_MASK) >> CFGREG_PROBE_CONF_IF5_PROBEB_ENABLE_SHIFT)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_CONF_IF5_PROBEA_SELECT_BITS_GET(x)                        ((x & CFGREG_PROBE_CONF_IF5_PROBEA_SELECT_MASK) >> CFGREG_PROBE_CONF_IF5_PROBEA_SELECT_SHIFT)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_CONF_IF1_PROBEB_SELECT_BITS_GET(x)                        ((x & CFGREG_PROBE_CONF_IF1_PROBEB_SELECT_MASK) >> CFGREG_PROBE_CONF_IF1_PROBEB_SELECT_SHIFT)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_CONF_IF1_PROBEB_ENABLE_BITS_GET(x)                        ((x & CFGREG_PROBE_CONF_IF1_PROBEB_ENABLE_MASK) >> CFGREG_PROBE_CONF_IF1_PROBEB_ENABLE_SHIFT)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */
#define CFGREG_PROBE_CONF_IF1_PROBEA_SELECT_BITS_GET(x)                        ((x & CFGREG_PROBE_CONF_IF1_PROBEA_SELECT_MASK) >> CFGREG_PROBE_CONF_IF1_PROBEA_SELECT_SHIFT)                            /*!<  GNSS-AFE IF1 analog probing Configuration Register Bits Get */

#define CFGREG_PLL1_CONF_LOPCB_EN_BITS_GET(x)                                  ((x & CFGREG_PLL1_CONF_LOPCB_EN_MASK) >> CFGREG_PLL1_CONF_LOPCB_EN_SHIFT)                                                /*!<  PLL1 Configuration Register Bits Get */
#define CFGREG_PLL1_CONF_TEST_EN_BITS_GET(x)                                   ((x & CFGREG_PLL1_CONF_TEST_EN_MASK) >> CFGREG_PLL1_CONF_TEST_EN_SHIFT)                                                  /*!<  PLL1 Configuration Register Bits Get */
#define CFGREG_PLL1_CONF_FCW_BITS_GET(x)                                       ((x & CFGREG_PLL1_CONF_FCW_MASK) >> CFGREG_PLL1_CONF_FCW_SHIFT)                                                          /*!<  PLL1 Configuration Register Bits Get */
#define CFGREG_PLL1_CONF_EN_BITS_GET(x)                                        ((x & CFGREG_PLL1_CONF_EN_MASK) >> CFGREG_PLL1_CONF_EN_SHIFT)                                                            /*!<  PLL1 Configuration Register Bits Get */

#define CFGREG_PLL1TDC_CONF_GAIN_BITS_GET(x)                                   ((x & CFGREG_PLL1TDC_CONF_GAIN_MASK) >> CFGREG_PLL1TDC_CONF_GAIN_SHIFT)                                                  /*!<  PLL1 TDC Configuration Register Bits Get */
#define CFGREG_PLL1TDC_CONF_SCALE_BITS_GET(x)                                  ((x & CFGREG_PLL1TDC_CONF_SCALE_MASK) >> CFGREG_PLL1TDC_CONF_SCALE_SHIFT)                                                /*!<  PLL1 TDC Configuration Register Bits Get */
#define CFGREG_PLL1TDC_CONF_LOAD_BITS_GET(x)                                   ((x & CFGREG_PLL1TDC_CONF_LOAD_MASK) >> CFGREG_PLL1TDC_CONF_LOAD_SHIFT)                                                  /*!<  PLL1 TDC Configuration Register Bits Get */

#define CFGREG_PLL1DCO_CONF_AMP_BITS_GET(x)                                    ((x & CFGREG_PLL1DCO_CONF_AMP_MASK) >> CFGREG_PLL1DCO_CONF_AMP_SHIFT)                                                    /*!<  PLL1 DCO Configuration Register Bits Get */
#define CFGREG_PLL1DCO_CONF_AMP_LOAD_BITS_GET(x)                               ((x & CFGREG_PLL1DCO_CONF_AMP_LOAD_MASK) >> CFGREG_PLL1DCO_CONF_AMP_LOAD_SHIFT)                                          /*!<  PLL1 DCO Configuration Register Bits Get */
#define CFGREG_PLL1DCO_CONF_CTRL_PVT_BITS_GET(x)                               ((x & CFGREG_PLL1DCO_CONF_CTRL_PVT_MASK) >> CFGREG_PLL1DCO_CONF_CTRL_PVT_SHIFT)                                          /*!<  PLL1 DCO Configuration Register Bits Get */
#define CFGREG_PLL1DCO_CONF_CTRL_FINE_BITS_GET(x)                              ((x & CFGREG_PLL1DCO_CONF_CTRL_FINE_MASK) >> CFGREG_PLL1DCO_CONF_CTRL_FINE_SHIFT)                                        /*!<  PLL1 DCO Configuration Register Bits Get */
#define CFGREG_PLL1DCO_CONF_CTRL_LOAD_BITS_GET(x)                              ((x & CFGREG_PLL1DCO_CONF_CTRL_LOAD_MASK) >> CFGREG_PLL1DCO_CONF_CTRL_LOAD_SHIFT)                                        /*!<  PLL1 DCO Configuration Register Bits Get */

#define CFGREG_PLL1_STAT_PHERR_BITS_GET(x)                                     ((x & CFGREG_PLL1_STAT_PHERR_MASK) >> CFGREG_PLL1_STAT_PHERR_SHIFT)                                                      /*!<  PLL1 Status Register Bits Get */
#define CFGREG_PLL1_STAT_NDIV_BITS_GET(x)                                      ((x & CFGREG_PLL1_STAT_NDIV_MASK) >> CFGREG_PLL1_STAT_NDIV_SHIFT)                                                        /*!<  PLL1 Status Register Bits Get */
#define CFGREG_PLL1_STAT_PHSEL_BITS_GET(x)                                     ((x & CFGREG_PLL1_STAT_PHSEL_MASK) >> CFGREG_PLL1_STAT_PHSEL_SHIFT)                                                      /*!<  PLL1 Status Register Bits Get */
#define CFGREG_PLL1_STAT_LOCK_BITS_GET(x)                                      ((x & CFGREG_PLL1_STAT_LOCK_MASK) >> CFGREG_PLL1_STAT_LOCK_SHIFT)                                                        /*!<  PLL1 Status Register Bits Get */

#define CFGREG_PLL1TDC_STAT_SCALE_BITS_GET(x)                                  ((x & CFGREG_PLL1TDC_STAT_SCALE_MASK) >> CFGREG_PLL1TDC_STAT_SCALE_SHIFT)                                                /*!<  PLL1 TDC Status Register Bits Get */

#define CFGREG_PLL1DCO_STAT_AMP_BITS_GET(x)                                    ((x & CFGREG_PLL1DCO_STAT_AMP_MASK) >> CFGREG_PLL1DCO_STAT_AMP_SHIFT)                                                    /*!<  PLL1 TDC Status Register Bits Get */
#define CFGREG_PLL1DCO_STAT_AMP_LOW_BITS_GET(x)                                ((x & CFGREG_PLL1DCO_STAT_AMP_LOW_MASK) >> CFGREG_PLL1DCO_STAT_AMP_LOW_SHIFT)                                            /*!<  PLL1 TDC Status Register Bits Get */
#define CFGREG_PLL1DCO_STAT_CTRL_PVT_BITS_GET(x)                               ((x & CFGREG_PLL1DCO_STAT_CTRL_PVT_MASK) >> CFGREG_PLL1DCO_STAT_CTRL_PVT_SHIFT)                                          /*!<  PLL1 TDC Status Register Bits Get */
#define CFGREG_PLL1DCO_STAT_CTRL_FINE_BITS_GET(x)                              ((x & CFGREG_PLL1DCO_STAT_CTRL_FINE_MASK) >> CFGREG_PLL1DCO_STAT_CTRL_FINE_SHIFT)                                        /*!<  PLL1 TDC Status Register Bits Get */

#define CFGREG_IF1_CONF_AGC_IQ_SEP_BITS_GET(x)                                 ((x & CFGREG_IF1_CONF_AGC_IQ_SEP_MASK) >> CFGREG_IF1_CONF_AGC_IQ_SEP_SHIFT)                                              /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_AGC_THR_BITS_GET(x)                                    ((x & CFGREG_IF1_CONF_AGC_THR_MASK) >> CFGREG_IF1_CONF_AGC_THR_SHIFT)                                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_LPF_CAL_BITS_GET(x)                                    ((x & CFGREG_IF1_CONF_LPF_CAL_MASK) >> CFGREG_IF1_CONF_LPF_CAL_SHIFT)                                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_LPF_GAIN_BITS_GET(x)                                   ((x & CFGREG_IF1_CONF_LPF_GAIN_MASK) >> CFGREG_IF1_CONF_LPF_GAIN_SHIFT)                                                  /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_LPF_BAND_BITS_GET(x)                                   ((x & CFGREG_IF1_CONF_LPF_BAND_MASK) >> CFGREG_IF1_CONF_LPF_BAND_SHIFT)                                                  /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_LPF_EN_BITS_GET(x)                                     ((x & CFGREG_IF1_CONF_LPF_EN_MASK) >> CFGREG_IF1_CONF_LPF_EN_SHIFT)                                                      /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PGA2_GAIN_BITS_GET(x)                                  ((x & CFGREG_IF1_CONF_PGA2_GAIN_MASK) >> CFGREG_IF1_CONF_PGA2_GAIN_SHIFT)                                                /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PGA2_EN_BITS_GET(x)                                    ((x & CFGREG_IF1_CONF_PGA2_EN_MASK) >> CFGREG_IF1_CONF_PGA2_EN_SHIFT)                                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PGA1_1DB_GAIN_Q_BITS_GET(x)                            ((x & CFGREG_IF1_CONF_PGA1_1DB_GAIN_Q_MASK) >> CFGREG_IF1_CONF_PGA1_1DB_GAIN_Q_SHIFT)                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PGA1_1DB_GAIN_I_BITS_GET(x)                            ((x & CFGREG_IF1_CONF_PGA1_1DB_GAIN_I_MASK) >> CFGREG_IF1_CONF_PGA1_1DB_GAIN_I_SHIFT)                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PGA1_GAIN_BITS_GET(x)                                  ((x & CFGREG_IF1_CONF_PGA1_GAIN_MASK) >> CFGREG_IF1_CONF_PGA1_GAIN_SHIFT)                                                /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PGA1_EN_BITS_GET(x)                                    ((x & CFGREG_IF1_CONF_PGA1_EN_MASK) >> CFGREG_IF1_CONF_PGA1_EN_SHIFT)                                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_PREAMP_EN_BITS_GET(x)                                  ((x & CFGREG_IF1_CONF_PREAMP_EN_MASK) >> CFGREG_IF1_CONF_PREAMP_EN_SHIFT)                                                /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_LOAD_EN_BITS_GET(x)                                    ((x & CFGREG_IF1_CONF_LOAD_EN_MASK) >> CFGREG_IF1_CONF_LOAD_EN_SHIFT)                                                    /*!<  IF1 Configuration Register Bits Get */
#define CFGREG_IF1_CONF_EN_BITS_GET(x)                                         ((x & CFGREG_IF1_CONF_EN_MASK) >> CFGREG_IF1_CONF_EN_SHIFT)                                                              /*!<  IF1 Configuration Register Bits Get */

#define CFGREG_IF1_STAT_AGC_CTRL_Q_BITS_GET(x)                                 ((x & CFGREG_IF1_STAT_AGC_CTRL_Q_MASK) >> CFGREG_IF1_STAT_AGC_CTRL_Q_SHIFT)                                              /*!<  IF1 Status Register Bits Get */
#define CFGREG_IF1_STAT_AGC_CTRL_I_BITS_GET(x)                                 ((x & CFGREG_IF1_STAT_AGC_CTRL_I_MASK) >> CFGREG_IF1_STAT_AGC_CTRL_I_SHIFT)                                              /*!<  IF1 Status Register Bits Get */

#define CFGREG_ADC1_CONF_CLK_SEL_BITS_GET(x)                                   ((x & CFGREG_ADC1_CONF_CLK_SEL_MASK) >> CFGREG_ADC1_CONF_CLK_SEL_SHIFT)                                                  /*!<  ADC1 Configuration Register Bits Get */
#define CFGREG_ADC1_CONF_CLK_CONF_BITS_GET(x)                                  ((x & CFGREG_ADC1_CONF_CLK_CONF_MASK) >> CFGREG_ADC1_CONF_CLK_CONF_SHIFT)                                                /*!<  ADC1 Configuration Register Bits Get */
#define CFGREG_ADC1_CONF_SAH_EN_BITS_GET(x)                                    ((x & CFGREG_ADC1_CONF_SAH_EN_MASK) >> CFGREG_ADC1_CONF_SAH_EN_SHIFT)                                                    /*!<  ADC1 Configuration Register Bits Get */
#define CFGREG_ADC1_CONF_ADC_EN_BITS_GET(x)                                    ((x & CFGREG_ADC1_CONF_ADC_EN_MASK) >> CFGREG_ADC1_CONF_ADC_EN_SHIFT)                                                    /*!<  ADC1 Configuration Register Bits Get */

#define CFGREG_PLL5_CONF_LOPCB_EN_BITS_GET(x)                                  ((x & CFGREG_PLL5_CONF_LOPCB_EN_MASK) >> CFGREG_PLL5_CONF_LOPCB_EN_SHIFT)                                                /*!<  PLL5 Configuration Register Bits Get */
#define CFGREG_PLL5_CONF_TEST_EN_BITS_GET(x)                                   ((x & CFGREG_PLL5_CONF_TEST_EN_MASK) >> CFGREG_PLL5_CONF_TEST_EN_SHIFT)                                                  /*!<  PLL5 Configuration Register Bits Get */
#define CFGREG_PLL5_CONF_FCW_BITS_GET(x)                                       ((x & CFGREG_PLL5_CONF_FCW_MASK) >> CFGREG_PLL5_CONF_FCW_SHIFT)                                                          /*!<  PLL5 Configuration Register Bits Get */
#define CFGREG_PLL5_CONF_EN_BITS_GET(x)                                        ((x & CFGREG_PLL5_CONF_EN_MASK) >> CFGREG_PLL5_CONF_EN_SHIFT)                                                            /*!<  PLL5 Configuration Register Bits Get */

#define CFGREG_PLL5TDC_CONF_GAIN_BITS_GET(x)                                   ((x & CFGREG_PLL5TDC_CONF_GAIN_MASK) >> CFGREG_PLL5TDC_CONF_GAIN_SHIFT)                                                  /*!<  PLL5 TDC Configuration Register Bits Get */
#define CFGREG_PLL5TDC_CONF_SCALE_BITS_GET(x)                                  ((x & CFGREG_PLL5TDC_CONF_SCALE_MASK) >> CFGREG_PLL5TDC_CONF_SCALE_SHIFT)                                                /*!<  PLL5 TDC Configuration Register Bits Get */
#define CFGREG_PLL5TDC_CONF_LOAD_BITS_GET(x)                                   ((x & CFGREG_PLL5TDC_CONF_LOAD_MASK) >> CFGREG_PLL5TDC_CONF_LOAD_SHIFT)                                                  /*!<  PLL5 TDC Configuration Register Bits Get */

#define CFGREG_PLL5DCO_CONF_AMP_BITS_GET(x)                                    ((x & CFGREG_PLL5DCO_CONF_AMP_MASK) >> CFGREG_PLL5DCO_CONF_AMP_SHIFT)                                                    /*!<  PLL5 DCO Configuration Register Bits Get */
#define CFGREG_PLL5DCO_CONF_AMP_LOAD_BITS_GET(x)                               ((x & CFGREG_PLL5DCO_CONF_AMP_LOAD_MASK) >> CFGREG_PLL5DCO_CONF_AMP_LOAD_SHIFT)                                          /*!<  PLL5 DCO Configuration Register Bits Get */
#define CFGREG_PLL5DCO_CONF_CTRL_PVT_BITS_GET(x)                               ((x & CFGREG_PLL5DCO_CONF_CTRL_PVT_MASK) >> CFGREG_PLL5DCO_CONF_CTRL_PVT_SHIFT)                                          /*!<  PLL5 DCO Configuration Register Bits Get */
#define CFGREG_PLL5DCO_CONF_CTRL_FINE_BITS_GET(x)                              ((x & CFGREG_PLL5DCO_CONF_CTRL_FINE_MASK) >> CFGREG_PLL5DCO_CONF_CTRL_FINE_SHIFT)                                        /*!<  PLL5 DCO Configuration Register Bits Get */
#define CFGREG_PLL5DCO_CONF_CTRL_LOAD_BITS_GET(x)                              ((x & CFGREG_PLL5DCO_CONF_CTRL_LOAD_MASK) >> CFGREG_PLL5DCO_CONF_CTRL_LOAD_SHIFT)                                        /*!<  PLL5 DCO Configuration Register Bits Get */

#define CFGREG_PLL5_STAT_PHERR_BITS_GET(x)                                     ((x & CFGREG_PLL5_STAT_PHERR_MASK) >> CFGREG_PLL5_STAT_PHERR_SHIFT)                                                      /*!<  PLL5 Status Register Bits Get */
#define CFGREG_PLL5_STAT_NDIV_BITS_GET(x)                                      ((x & CFGREG_PLL5_STAT_NDIV_MASK) >> CFGREG_PLL5_STAT_NDIV_SHIFT)                                                        /*!<  PLL5 Status Register Bits Get */
#define CFGREG_PLL5_STAT_PHSEL_BITS_GET(x)                                     ((x & CFGREG_PLL5_STAT_PHSEL_MASK) >> CFGREG_PLL5_STAT_PHSEL_SHIFT)                                                      /*!<  PLL5 Status Register Bits Get */
#define CFGREG_PLL5_STAT_LOCK_BITS_GET(x)                                      ((x & CFGREG_PLL5_STAT_LOCK_MASK) >> CFGREG_PLL5_STAT_LOCK_SHIFT)                                                        /*!<  PLL5 Status Register Bits Get */

#define CFGREG_PLL5TDC_STAT_SCALE_BITS_GET(x)                                  ((x & CFGREG_PLL5TDC_STAT_SCALE_MASK) >> CFGREG_PLL5TDC_STAT_SCALE_SHIFT)                                                /*!<  PLL5 TDC Status Register Bits Get */

#define CFGREG_PLL5DCO_STAT_AMP_BITS_GET(x)                                    ((x & CFGREG_PLL5DCO_STAT_AMP_MASK) >> CFGREG_PLL5DCO_STAT_AMP_SHIFT)                                                    /*!<  PLL5 TDC Status Register Bits Get */
#define CFGREG_PLL5DCO_STAT_AMP_LOW_BITS_GET(x)                                ((x & CFGREG_PLL5DCO_STAT_AMP_LOW_MASK) >> CFGREG_PLL5DCO_STAT_AMP_LOW_SHIFT)                                            /*!<  PLL5 TDC Status Register Bits Get */
#define CFGREG_PLL5DCO_STAT_CTRL_PVT_BITS_GET(x)                               ((x & CFGREG_PLL5DCO_STAT_CTRL_PVT_MASK) >> CFGREG_PLL5DCO_STAT_CTRL_PVT_SHIFT)                                          /*!<  PLL5 TDC Status Register Bits Get */
#define CFGREG_PLL5DCO_STAT_CTRL_FINE_BITS_GET(x)                              ((x & CFGREG_PLL5DCO_STAT_CTRL_FINE_MASK) >> CFGREG_PLL5DCO_STAT_CTRL_FINE_SHIFT)                                        /*!<  PLL5 TDC Status Register Bits Get */

#define CFGREG_IF5_CONF_AGC_IQ_SEP_BITS_GET(x)                                 ((x & CFGREG_IF5_CONF_AGC_IQ_SEP_MASK) >> CFGREG_IF5_CONF_AGC_IQ_SEP_SHIFT)                                              /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_AGC_THR_BITS_GET(x)                                    ((x & CFGREG_IF5_CONF_AGC_THR_MASK) >> CFGREG_IF5_CONF_AGC_THR_SHIFT)                                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_LPF_CAL_BITS_GET(x)                                    ((x & CFGREG_IF5_CONF_LPF_CAL_MASK) >> CFGREG_IF5_CONF_LPF_CAL_SHIFT)                                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_LPF_GAIN_BITS_GET(x)                                   ((x & CFGREG_IF5_CONF_LPF_GAIN_MASK) >> CFGREG_IF5_CONF_LPF_GAIN_SHIFT)                                                  /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_LPF_BAND_BITS_GET(x)                                   ((x & CFGREG_IF5_CONF_LPF_BAND_MASK) >> CFGREG_IF5_CONF_LPF_BAND_SHIFT)                                                  /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_LPF_EN_BITS_GET(x)                                     ((x & CFGREG_IF5_CONF_LPF_EN_MASK) >> CFGREG_IF5_CONF_LPF_EN_SHIFT)                                                      /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PGA2_GAIN_BITS_GET(x)                                  ((x & CFGREG_IF5_CONF_PGA2_GAIN_MASK) >> CFGREG_IF5_CONF_PGA2_GAIN_SHIFT)                                                /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PGA2_EN_BITS_GET(x)                                    ((x & CFGREG_IF5_CONF_PGA2_EN_MASK) >> CFGREG_IF5_CONF_PGA2_EN_SHIFT)                                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PGA1_1DB_GAIN_Q_BITS_GET(x)                            ((x & CFGREG_IF5_CONF_PGA1_1DB_GAIN_Q_MASK) >> CFGREG_IF5_CONF_PGA1_1DB_GAIN_Q_SHIFT)                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PGA1_1DB_GAIN_I_BITS_GET(x)                            ((x & CFGREG_IF5_CONF_PGA1_1DB_GAIN_I_MASK) >> CFGREG_IF5_CONF_PGA1_1DB_GAIN_I_SHIFT)                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PGA1_GAIN_BITS_GET(x)                                  ((x & CFGREG_IF5_CONF_PGA1_GAIN_MASK) >> CFGREG_IF5_CONF_PGA1_GAIN_SHIFT)                                                /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PGA1_EN_BITS_GET(x)                                    ((x & CFGREG_IF5_CONF_PGA1_EN_MASK) >> CFGREG_IF5_CONF_PGA1_EN_SHIFT)                                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_PREAMP_EN_BITS_GET(x)                                  ((x & CFGREG_IF5_CONF_PREAMP_EN_MASK) >> CFGREG_IF5_CONF_PREAMP_EN_SHIFT)                                                /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_LOAD_EN_BITS_GET(x)                                    ((x & CFGREG_IF5_CONF_LOAD_EN_MASK) >> CFGREG_IF5_CONF_LOAD_EN_SHIFT)                                                    /*!<  IF5 Configuration Register Bits Get */
#define CFGREG_IF5_CONF_EN_BITS_GET(x)                                         ((x & CFGREG_IF5_CONF_EN_MASK) >> CFGREG_IF5_CONF_EN_SHIFT)                                                              /*!<  IF5 Configuration Register Bits Get */

#define CFGREG_IF5_STAT_AGC_CTRL_Q_BITS_GET(x)                                 ((x & CFGREG_IF5_STAT_AGC_CTRL_Q_MASK) >> CFGREG_IF5_STAT_AGC_CTRL_Q_SHIFT)                                              /*!<  IF5 Status Register Bits Get */
#define CFGREG_IF5_STAT_AGC_CTRL_I_BITS_GET(x)                                 ((x & CFGREG_IF5_STAT_AGC_CTRL_I_MASK) >> CFGREG_IF5_STAT_AGC_CTRL_I_SHIFT)                                              /*!<  IF5 Status Register Bits Get */

#define CFGREG_ADC5_CONF_CLK_SEL_BITS_GET(x)                                   ((x & CFGREG_ADC5_CONF_CLK_SEL_MASK) >> CFGREG_ADC5_CONF_CLK_SEL_SHIFT)                                                  /*!<  ADC5 Configuration Register Bits Get */
#define CFGREG_ADC5_CONF_CLK_CONF_BITS_GET(x)                                  ((x & CFGREG_ADC5_CONF_CLK_CONF_MASK) >> CFGREG_ADC5_CONF_CLK_CONF_SHIFT)                                                /*!<  ADC5 Configuration Register Bits Get */
#define CFGREG_ADC5_CONF_SAH_EN_BITS_GET(x)                                    ((x & CFGREG_ADC5_CONF_SAH_EN_MASK) >> CFGREG_ADC5_CONF_SAH_EN_SHIFT)                                                    /*!<  ADC5 Configuration Register Bits Get */
#define CFGREG_ADC5_CONF_ADC_EN_BITS_GET(x)                                    ((x & CFGREG_ADC5_CONF_ADC_EN_MASK) >> CFGREG_ADC5_CONF_ADC_EN_SHIFT)                                                    /*!<  ADC5 Configuration Register Bits Get */

#define CFGREG_SPARE_CONF_SIG_BITS_GET(x)                                      ((x & CFGREG_SPARE_CONF_SIG_MASK) >> CFGREG_SPARE_CONF_SIG_SHIFT)                                                        /*!<  SPARE Configuration Register Bits Get */

#define CFGREG_SPARE_STAT_SIG_BITS_GET(x)                                      ((x & CFGREG_SPARE_STAT_SIG_MASK) >> CFGREG_SPARE_STAT_SIG_SHIFT)                                                        /*!<  SPARE Configuration Register Bits Get */

#define CFGREG_GNSSAFE_TEST_CONF_SIG_BITS_GET(x)                               ((x & CFGREG_GNSSAFE_TEST_CONF_SIG_MASK) >> CFGREG_GNSSAFE_TEST_CONF_SIG_SHIFT)                                          /*!<  TEST Configuration Register Bits Get */

#define CFGREG_GNSSAFE_TEST_STAT_SIG_BITS_GET(x)                               ((x & CFGREG_GNSSAFE_TEST_STAT_SIG_MASK) >> CFGREG_GNSSAFE_TEST_STAT_SIG_SHIFT)                                          /*!<  TEST Configuration Register Bits Get */

/** @} */

#endif /* __CFG_REGS_H */
/** @} */
