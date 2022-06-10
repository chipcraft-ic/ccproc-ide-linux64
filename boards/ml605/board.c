/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2021-12-19 17:42:38 +0100 (nie, 19 gru 2021) $
* $Revision: 804 $
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
#include <ccproc-csr.h>

#include "max2771.h"

/**
 * @brief Initialize the ML605 board
 */
void board_init(void)
{
    /* check if external DDR3 instruction memory is used, if yes, overwrite to 256MB */
    if (CPU_INFO_GET_IMSIZE_LOG(CSR_CTRL_PTR->CPU_INFO_0) == 0){
        CSR_CTRL_PTR->CPU_INFO_0 |= 28;
    }
    /* check if external DDR3 data memory is used, if yes, overwrite to 256MB        */
    if (CPU_INFO_GET_DMSIZE_LOG(CSR_CTRL_PTR->CPU_INFO_0) == 0){
        CSR_CTRL_PTR->CPU_INFO_0 |= 28 << CPU_DMSIZE_SHIFT;
    }
}

/**
 * @brief Initialize GNSS AFE for ML605 board
 */
int gnss_afe_init(void)
{
    max2771_conf_band(L1E1);
    max2771_conf_band(L5E5);
    max2771_conf_band(L2E6);
    return 0;
}

