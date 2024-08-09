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
* File Name : pwd_util.c
* Author    : Krzysztof Marcinek
* ******************************************************************************
* $Date: 2024-01-14 21:55:43 +0100 (nie, 14 sty 2024) $
* $Revision: 1038 $
*H*****************************************************************************/

#include <ccproc.h>
#include <ccproc-pwd.h>
#include <ccproc-csr.h>
#include <ccproc-dcache.h>
#include <ccproc-utils.h>

/*! \brief Power down the main core and wait for interrupt or till other cores are stopped.
 *
 * \param flush_dcache Whether to flush data cache before power down.
 * \return \c false if executing core is not the main one, otherwise \c true.
 *
 */
int mainPowerDown(uint32_t flush_dcache)
{
    // check core id
    if (CSR_STATUS_GET_CORE_ID(CSR_CTRL_PTR->STATUS) != 0) return -1;
    // flush data cache
    if (flush_dcache) DCACHE_PTR->FLUSH = 1;
    // flush write buffer
    while (DCACHE_PTR->STCR & DCACHE_STCR_BUSY);
    MEMORY_BARRIER();
    // main core power down
    PWD_PTR->CTRL |= PWD_CTRL_MAINPWD | PWD_CTRL_KEY;
    CLEAR_PIPELINE();
    return 0;
}

/*! \brief Power down core and wait for interrupt.
 *
 * \param flush_dcache Whether to flush data cache before power down.
 *
 */
void corePowerDown(uint32_t flush_dcache)
{
    // flush data cache
    if (flush_dcache) DCACHE_PTR->FLUSH = 1;
    // flush write buffer
    while (DCACHE_PTR->STCR & DCACHE_STCR_BUSY);
    MEMORY_BARRIER();
    // core power down
    PWD_PTR->CTRL |= PWD_CTRL_COREPWD | PWD_CTRL_KEY;
    CLEAR_PIPELINE();
}

/*! \brief Power down system. Wake-up on RTC or external GPIO only. */
void systemPowerDown(void)
{
    // flush write buffer
    while (DCACHE_PTR->STCR & DCACHE_STCR_BUSY);
    MEMORY_BARRIER();
    // system power down
    PWD_PTR->CTRL |= PWD_CTRL_SYSPWD | PWD_CTRL_KEY;
    CLEAR_PIPELINE();
}
