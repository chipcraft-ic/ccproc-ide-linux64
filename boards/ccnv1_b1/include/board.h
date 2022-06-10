/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2021-10-02 21:48:05 +0200 (sob, 02 paź 2021) $
* $Revision: 763 $
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

#ifndef _BOARD_H
#define _BOARD_H

#include <stdint.h>

/* DO NOT MODIFY */
#define IDCODE_PART_NUM         1
#define IDCODE_PART_VER         1
#define FLASH_DELAY             36UL
#define FLASH_SIZE              (1024*1024)
#define FLASH_PAGE_SIZE         512

//#define PERIPH0_FREQ            40920000UL
//#define CORE_FREQ               81840000UL

//#define PERIPH0_FREQ            49104000UL
//#define CORE_FREQ               98208000UL

#define PERIPH0_FREQ            65472000UL
#define CORE_FREQ               130944000UL

//#define PERIPH0_FREQ            65472000UL
//#define CORE_FREQ               130944000UL

#define DBG_BAUDRATE            921600

#define STDIO_UART              0
#define STDIO_BAUDRATE          460800
#define STDIO_RTSCTS            0

#define TIME_SOURCE             TIMER32
#define TIME_SOURCE_TIMER_ID    0
#define TIME_SOURCE_PRSC        ((PERIPH0_FREQ/1000000)-1)

/* Initialize GNSS AFE */
void gnss_afe_init(void);
/* Increment ADC L1/E1 band */
void gnss_agc1_inc(void);
/* Decrement ADC L1/E1 band */
void gnss_agc1_dec(void);
/* Increment ADC L5/E5 band */
void gnss_agc5_inc(void);
/* Decrement ADC L5/E5 band */
void gnss_agc5_dec(void);
/* Maintain AGC */
void gnss_agc_maintanance(uint32_t noise, uint8_t dwells_mult_1ms);
/*  Calibrate PLL1 */
void gnss_pll1_calibrate(uint8_t *dco_pvt, uint8_t *dco_fine);
/* PLL1 control loop */
void gnss_pll1_loop(uint8_t dco_pvt, uint8_t dco_fine);
/*  PLL1 control loop */
void gnss_pll1_maintanance(void);

#endif /* _BOARD_H */
