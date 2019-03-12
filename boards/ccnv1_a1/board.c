/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2018-12-04 14:27:17 +0100 (wto) $
* $Revision: 362 $
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

/**
 * @brief Initialize the CCNV1 board
 */
void board_init(void)
{

    /* Enable GPIO controller */
    AMBA_GPIO_PTR->CTRL |= GPIO_CTRL_EN;

    /* Set UART3 to GPIO 16, 17, 18, 19 */
    //AMBA_GPIO_PTR->ALTER_HI |= GPIO_CONFIG_MASK(16,GPIO_ALTER_0);
    //AMBA_GPIO_PTR->ALTER_HI |= GPIO_CONFIG_MASK(17,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_HI |= GPIO_CONFIG_MASK(18,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_HI |= GPIO_CONFIG_MASK(19,GPIO_ALTER_0);

    /* Set I2C0 to GPIO 10, 11 */
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(10,GPIO_ALTER_0);
    AMBA_GPIO_PTR->ALTER_LO |= GPIO_CONFIG_MASK(11,GPIO_ALTER_0);

    /* Set pull-up to GPIO 10, 11 */
    AMBA_GPIO_PTR->PULL_LO |= GPIO_CONFIG_MASK(10,GPIO_PULL_UP);
    AMBA_GPIO_PTR->PULL_LO |= GPIO_CONFIG_MASK(11,GPIO_PULL_UP);

    /* Disable GPIO controller */
    AMBA_GPIO_PTR->CTRL &= ~GPIO_CTRL_EN;

    /* Enable APB1 Bridge */
    AMBA_APB0_CFG_PTR->APB1_CFG = AMBA_APB1_EN;

    /* Configure Flash Controller */
    flash_configure(CORE_FREQ,(uint8_t)FLASH_READ_WAIT_STATES_CALC(CORE_FREQ),1,0);

    /* Configure PLL */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_PLL = CFGREG_COREFREQ_PLL_PLL_EN_MASK | (5 << CFGREG_COREFREQ_PLL_PLL_N_SHIFT) | CFGREG_COREFREQ_PLL_REF_SEL_MASK;
    while ((CFG_REGS_PTR->CFGREG_COREFREQ_STAT & CFGREG_COREFREQ_STAT_PLL_LOCK_MASK) == 0);

    /* Switch to PLL */
    CFG_REGS_PTR->CFGREG_UNLOCK = CFGREG_UNLOCK_DEF;
    CFG_REGS_PTR->CFGREG_COREFREQ_CLK = 2 << CFGREG_COREFREQ_CLK_CLK_CORE_SEL_SHIFT;

    /* Disable APB1 Bridge */
    AMBA_APB0_CFG_PTR->APB1_CFG &= ~AMBA_APB1_EN;

}
