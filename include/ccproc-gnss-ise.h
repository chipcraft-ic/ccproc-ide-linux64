/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2019-11-14 09:00:25 +0100 (czw, 14 lis 2019) $
* $Revision: 484 $
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
 * @file        ccproc-gnss-ise.h
 * @brief       CC Processor GNSS definitions
 * @author      Rafal Harabien
 *
 * @defgroup    ccgnss GNSS Instructions
 * @{
 */
#ifndef __CCPROC_GNSS_ISE_H__
#define __CCPROC_GNSS_ISE_H__

#include <stdint.h>

#ifndef __GNUC__
 #error Only GCC is supported by this header! Use your compiler inline assembly feature manually.
#endif

#ifndef INLINE
/// define INLINE
# define INLINE static __inline__
#endif

/** GNSS-ISE RF AFE Selection */
enum gnss_ise_rfafe_enum
{
    GNSS_ISE_RFAFE_INVALID    = -1, /*!< GNSS-ISE Invalid RF AFE         */

    GNSS_ISE_RFAFE_L1E1       = 0,  /*!< GNSS-ISE L1/E1 RF AFE           */
    GNSS_ISE_RFAFE_L5E5       = 1,  /*!< GNSS-ISE L5/E5 RF AFE           */
    GNSS_ISE_RFAFE_L2E6       = 2,  /*!< GNSS-ISE L2/E6 RF AFE           */
    GNSS_ISE_RFAFE_VIRT       = 3,  /*!< GNSS-ISE Virtual RF AFE         */

    GNSS_ISE_RFAFE_MAX        = 4,  /*!< GNSS-ISE Guard Value            */
};

/**
 * \defgroup common Common
 * @{
 */

/**
 * write status
 * @param status bits[0] = clock
 */
INLINE void GNSS_STATUS_WR(uint32_t status)
{
    __asm__ __volatile__ ("gnss.stat.wr %0"
        : /* output */
        : "r" (status) /* input */
    );
}

/**
 * read status
 * @return bits[0] = clock
 */
INLINE uint32_t GNSS_STATUS_RD(void)
{
    volatile uint32_t res;
    __asm__ __volatile__ ("gnss.stat.rd %0"
        : "=r" (res) /* output */
    );
    return res;
}

/**
 * store data in GNSS engine frontend register
 */
INLINE void GNSS_AFE_WR(uint32_t val)
{
    __asm__ __volatile__ ("gnss.afe.wr %0"
        : /* output */
        : "r" (val) /* input */
    );
}

/** read selected analog frontend of GNSS channels.
 */
INLINE int32_t GNSS_AFE_RD(void)
{
    volatile uint32_t res;
    __asm__ __volatile__ ("gnss.afe.rd %0"
        : "=r" (res) /* output */
    );
    return res;
}

/**
 * write free accu mode
 * @param val bits[0:15] = accu_loop[0:15]
 * @param trigger start trigger for current channel
 */
INLINE void GNSS_FREE_ACCU_WR(uint32_t val, uint32_t trigger)
{
    __asm__ __volatile__ ("gnss.free.accu.wr %0, %1"
        : /* output */
        : "r" (val), "r" (trigger) /* input */
    );
}

/** write free update
 * @param val bits[0:15] = pll_loop[0:15], bits[15:31] = dll_loop[0:15]
 */
INLINE void GNSS_FREE_UPDATE_WR(uint32_t val)
{
    __asm__ __volatile__ ("gnss.free.update.wr %0"
        : /* output */
        : "r" (val) /* input */
    );
}

/**
 * read free accu
 * @return val bits[0] = accu_loop[0], bits[1] = accu_loop[1], ...
 */
INLINE int32_t GNSS_FREE_ACCU_RD(void)
{
    volatile uint32_t res;
    __asm__ __volatile__ ("gnss.free.accu.rd %0"
        : "=r" (res) /* output */
    );
    return res;
}

/**
 * read free update
 * @return bits[0:15] = pll_loop[0:15], bits[15:31] = dll_loop[0:15]
 */
INLINE int32_t GNSS_FREE_UPDATE_RD(void)
{
    volatile uint32_t res;
    __asm__ __volatile__ ("gnss.free.update.rd %0"
        : "=r" (res) /* output */
    );
    return res;
}

/// perform single tracking step
INLINE void GNSS_TRACK_STEP(uint32_t val)
{
    __asm__ __volatile__ ("gnss.track.step %0"
        : /* output */
        : "r" (val) /* input */
    );
}

/// set channel index
INLINE void GNSS_CHANN_SET(uint32_t chanNr)
{
    __asm__ __volatile__ ("gnss.chann.set %0"
        : /* output */
        : "r" (chanNr) /* input */
    );
}

/// get channel index
INLINE uint32_t GNSS_CHANN_GET(void)
{
    volatile uint32_t res;
    __asm__ __volatile__ ("gnss.chann.get %0"
        : "=r" (res) /* output */
    );
    return res;
}

/**
 * @}
 *
 * \defgroup carrier_nco Carrier NCO
 * @{
 */

/// set carrier frequency
INLINE void GNSS_CARR_FREQ(uint32_t freq)
{
    __asm__ __volatile__ ("gnss.carr.freq %0"
        : /* output */
        : "r" (freq) /* input */
    );
}

/// execute carrier discriminator
INLINE int32_t GNSS_CARR_DISC(int32_t disc)
{
    volatile uint32_t res;
    __asm__ __volatile__ ("gnss.carr.disc %0, %1"
        : "=r" (res) /* output */
        : "r" (disc) /* input */
    );
    return res;
}

/// get carrier sample
INLINE uint32_t GNSS_CARR_REM(uint32_t val, int32_t aid)
{
    volatile uint32_t res;
    __asm__ __volatile__ ("gnss.carr.rem %0, %1, %2"
        : "=r" (res) /* output */
        : "r" (val), "r" (aid) /* input */
    );
    return res;
}

/// set carrier register
INLINE void GNSS_CARR_SET(uint32_t val, uint32_t conf)
{
    __asm__ __volatile__ ("gnss.carr.set %0, %1"
        : /* output */
        : "r" (val), "r" (conf) /* input */
    );
}

/**
 * @}
 *
 * \defgroup correlator Correlator
 * @{
 */

/// accumulator add
INLINE void GNSS_ACCU_ADD(uint32_t vIn, uint32_t codes)
{
    __asm__ __volatile__ ("gnss.accu.add %0, %1"
        : /* output */
        : "r" (vIn), "r" (codes) /* input */
    );
}

/// accumulator get
INLINE int32_t GNSS_ACCU_GET(void)
{
    volatile int32_t res;
    __asm__ __volatile__ ("gnss.accu.get %0"
        : "=r" (res) /* output */
    );
    return res;
}

/**
 * @}
 *
 * \defgroup discriminators Discriminators
 * @{
 */

/// compute PLL discriminator
INLINE int32_t GNSS_PLL_DISC(int32_t I, int32_t Q)
{
    volatile int32_t res;
    __asm__ __volatile__ ("gnss.pll.disc %0, %1, %2"
        : "=r" (res) /* output */
        : "r" (I), "r" (Q) /* input */
    );
    return res;
}

/// define costas discriminator
#define GNSS_COST_DISC GNSS_PLL_COST
/// compute costas discriminator
INLINE int32_t GNSS_PLL_COST(int32_t I, int32_t Q)
{
    volatile int32_t res;
    __asm__ __volatile__ ("gnss.pll.cost %0, %1, %2"
        : "=r" (res) /* output */
        : "r" (I), "r" (Q) /* input */
    );
    return res;
}

/// compute DLL discriminator
INLINE int32_t GNSS_DLL_DISC(int32_t I0, int32_t Q0, int32_t I2, int32_t Q2)
{
    volatile int32_t res;
    __asm__ __volatile__ ("gnss.dll.disc.a %0, %1"
        : /* output */
        : "r" (I0), "r" (Q0) /* input */
    );
    __asm__ __volatile__ ("gnss.dll.disc.b %0, %1, %2"
        : "=r" (res) /* output */
        : "r" (I2), "r" (Q2) /* input */
    );
    return res;
}

/**
 * @}
 *
 * \defgroup filters Filters
 * @{
 */

/// PLL filter reset
INLINE void GNSS_PLL_FLT_RST(void)
{
    __asm__ __volatile__ ("gnss.pll.flt.rst");
}

/// DLL filter reset
INLINE void GNSS_DLL_FLT_RST(void)
{
    __asm__ __volatile__ ("gnss.dll.flt.rst");
}

/// PLL filter set coefficients
INLINE void GNSS_PLL_FLT_COEF(uint32_t c1, uint32_t c2)
{
    __asm__ __volatile__ ("gnss.pll.flt.coef %0, %1"
        : /* output */
        : "r" (c1), "r" (c2) /* input */
    );
}

/// DLL filter set coefficients
INLINE void GNSS_DLL_FLT_COEF(uint32_t c1, uint32_t c2)
{
    __asm__ __volatile__ ("gnss.dll.flt.coef %0, %1"
        : /* output */
        : "r" (c1), "r" (c2) /* input */
    );
}

/// PLL filter get
INLINE int32_t GNSS_PLL_FLT(int32_t disc)
{
    volatile int32_t res;
    __asm__ __volatile__ ("gnss.pll.flt %0, %1"
        : "=r" (res) /* output */
        : "r" (disc) /* input */
    );
    return res;
}

/// DLL filter get
INLINE int32_t GNSS_DLL_FLT(int32_t disc)
{
    volatile int32_t res;
    __asm__ __volatile__ ("gnss.dll.flt %0, %1"
        : "=r" (res) /* output */
        : "r" (disc) /* input */
    );
    return res;
}

/**
 * @}
 *
 * \defgroup code_generator Code Generator
 * @{
 */

/// get code sample
INLINE uint32_t GNSS_CODE_GET(void)
{
    volatile uint32_t res;
    __asm__ __volatile__ ("gnss.code.get %0"
        : "=r" (res) /* output */
    );
    return res;
}

/// set code generator address
INLINE void GNSS_PCODE_ADDR_SET(uint32_t addr, uint32_t nco)
{
    __asm__ __volatile__ ("gnss.pcode.addr.set %0, %1"
        : /* output */
        : "r" (addr), "r" (nco) /* input */
    );
}

/// write data
INLINE void GNSS_PCODE_WR(uint32_t val)
{
    __asm__ __volatile__ ("gnss.pcode.wr %0"
        : /* output */
        : "r" (val) /* input */
    );
}

/// set code length
INLINE void GNSS_PCODE_LEN(uint32_t len, uint32_t integr_mult, uint32_t coef, uint32_t scale)
{
    uint32_t val = (((integr_mult&31)<<16)|(scale&3)<<4)|(coef&15);
    __asm__ __volatile__ ("gnss.pcode.len %0, %1"
        : /* output */
        : "r" (len), "r" (val) /* input */
    );
}

/// set main and boc frequency
INLINE void GNSS_CODE_NCO_FREQ(uint32_t freq, uint32_t boc)
{
    __asm__ __volatile__ ("gnss.code.nco.freq %0, %1"
        : /* output */
        : "r" (freq), "r" (boc) /* input */
    );
}

/// set epl and code frequency
INLINE void GNSS_CODE_EPL_FREQ(uint32_t epl, uint32_t code)
{
    __asm__ __volatile__ ("gnss.code.epl.freq %0, %1"
        : /* output */
        : "r" (epl), "r" (code) /* input */
    );
}

/// set code generator address
INLINE void GNSS_SCODE_ADDR_SET(uint32_t addr)
{
    __asm__ __volatile__ ("gnss.scode.addr.set %0"
        : /* output */
        : "r" (addr) /* input */
    );
}

/// write data
INLINE void GNSS_SCODE_WR(uint32_t val)
{
    __asm__ __volatile__ ("gnss.scode.wr %0"
        : /* output */
        : "r" (val) /* input */
    );
}

/// set code length
INLINE void GNSS_SCODE_LEN(uint32_t len)
{
    __asm__ __volatile__ ("gnss.scode.len %0"
        : /* output */
        : "r" (len) /* input */
    );
}

/// execute code discriminator
INLINE int32_t GNSS_CODE_DISC(int32_t disc)
{
    volatile uint32_t res;
    __asm__ __volatile__ ("gnss.code.disc %0, %1"
        : "=r" (res) /* output */
        : "r" (disc) /* input */
    );
    return res;
}

/// get pseudorange parameters of currently selected channel
INLINE uint32_t GNSS_CODE_RNG(int32_t channel)
{
    volatile uint32_t res;
    __asm__ __volatile__ ("gnss.code.rng %0, %1"
        : "=r" (res) /* output */
        : "r" (channel) /* input */
    );
    return res;
}

/** @} */

#endif /* __CCPROC_GNSS_ISE_H__ */

/** @} */
