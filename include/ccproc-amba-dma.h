/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2018-09-07 16:07:40 +0200 (pią) $
* $Revision: 296 $
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
 * @file            ccproc-amba-dma.h
 * @brief           CC Processor AMBA DMA definitions
 * @author          Rafal Harabien
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_DMA_H
#define __CCPROC_AMBA_DMA_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup dma DMA Controller
 * DMA Controller registers and definitions
 * @{
 *//************************/

/** @brief DMA Registers */
typedef struct
{
    uint32_t CONF;    /*!< Base Configuration */
    uint32_t IRQMAP;  /*!< Interrupt Mapping  */
    uint32_t INFO;    /*!< Info Register      */
} amba_dma_t;

#ifdef CCPROC_SDK
 static volatile amba_dma_t * const AMBA_DMA_PTR = (amba_dma_t*)AMBA_DMA_BASE; /*!< DMA Controller pointer */
#endif

/** DMA Base Configuration Register flags */
enum
{
    DMA_CONF_DSEN     = 0x00000001,  /*!< Downstream Enable           */
    DMA_CONF_DSARB    = 0x00000002,  /*!< Downstream Arbitration Mode */
    DMA_CONF_USEN     = 0x00000004,  /*!< Upstream Enable             */
    DMA_CONF_USARB    = 0x00000008,  /*!< Upstream Arbitration Mode   */
    DMA_CONF_DBG_STOP = 0x80000000,  /*!< Stop in Debug               */
};

/** DMA Channel Registers */
typedef struct
{
    uint32_t STATUS;          /*!< Status Register         */
    uint32_t CTRL;            /*!< Control Register        */
    uint32_t PSELECT;         /*!< Peripheral Select       */
    uint32_t ADDRESS;         /*!< Memory Address          */
    uint32_t ADDRESSREL;      /*!< Memory Address Reload   */
    uint32_t COUNTER;         /*!< Transfer Counter        */
    uint32_t COUNTERREL;      /*!< Transfer Counter Reload */
    uint32_t IRQM;            /*!< Interrupt Mask          */
} amba_dma_channel_t;

#ifdef CCPROC_SDK

 #define AMBA_DMA_CH_BASE(index) (AMBA_DMA_BASE+(index+1)*0x20)                          /*!< DMA Channel Base Address            */
 #define AMBA_DMA_CH_PTR(index) ((volatile amba_dma_channel_t*)AMBA_DMA_CH_BASE(index))  /*!< DMA Channel Pointer                 */

 #define AMBA_DMA_DWN_CH_BASE(index) AMBA_DMA_CH_BASE(index)                             /*!< DMA Downstream Channel Base Address */
 #define AMBA_DMA_DWN_CH_PTR(index) AMBA_DMA_CH_PTR(index)                               /*!< DMA Downstream Channel Pointer      */

 #define AMBA_DMA_UP_CH_BASE(index) AMBA_DMA_CH_BASE(AMBA_DMA_DWN_COUNT() + (index))     /*!< DMA Upstream Channel Base Address   */
 #define AMBA_DMA_UP_CH_PTR(index)  AMBA_DMA_CH_PTR(AMBA_DMA_DWN_COUNT() + (index))      /*!< DMA Upstream Channel Pointer        */

 #define AMBA_DMA_UART_PSELECT(index) (index)                                            /*!< DMA UART PSELECT                    */
 #define AMBA_DMA_SPI_PSELECT(index) (AMBA_UART_COUNT()+index)                           /*!< DMA SPI PSELECT                     */
 #define AMBA_DMA_I2C_PSELECT(index) (AMBA_UART_COUNT()+AMBA_SPI_COUNT()+index)          /*!< DMA I2C PSELECT                     */

#endif

/** DMA Channel Status Register flags */
enum
{
    DMA_STAT_ACT    = 0x01,  /*!< Channel Active        */
    DMA_STAT_TCZ    = 0x02,  /*!< Transfer Counter Zero */
    DMA_STAT_RCZ    = 0x04,  /*!< Counter Reload Zero   */
    DMA_STAT_MAR    = 0x08,  /*!< Memory Address Reload */
    DMA_STAT_MERR   = 0x10,  /*!< Memory Access Error   */
};

/** DMA Channel Control Register Shifts */
enum
{
    DMA_CTRL_TRU_SHIFT  = 4, /*!< Transfer Unit Offset  */
};

typedef enum
{
    DMA_TRU32  = 0x0,  /*!< Transfer Unit Size - 32 bits (default) */
    DMA_TRU8   = 0x1,  /*!< Transfer Unit Size - 8 bits            */
    DMA_TRU16  = 0x2,  /*!< Transfer Unit Size - 16 bits           */
} amba_dma_tru_t;

/** DMA Channel Control Register flags */
enum
{
    DMA_CTRL_EN     = 0x01,  /*!< Transfer Enable                        */
    DMA_CTRL_RING   = 0x02,  /*!< Ring Buffer                            */
    DMA_CTRL_DEC    = 0x04,  /*!< Address Decrement                      */
    DMA_CTRL_INC    = 0x08,  /*!< Address Increment                      */

    DMA_CTRL_TRU8     = DMA_TRU8  << DMA_CTRL_TRU_SHIFT,  /*!< Transfer Unit Size - 8 bits            */
    DMA_CTRL_TRU16    = DMA_TRU16 << DMA_CTRL_TRU_SHIFT,  /*!< Transfer Unit Size - 16 bits           */
    DMA_CTRL_TRU32    = DMA_TRU32 << DMA_CTRL_TRU_SHIFT,  /*!< Transfer Unit Size - 32 bits (default) */
    DMA_CTRL_TRU_MASK = 0x30,
};


/** DMA Channel Interrupt Mask bits */
enum
{
    DMA_TCZIE  = 0x01,  /*!< Transfer Counter Zero Interrupt Enable */
    DMA_RCZIE  = 0x02,  /*!< Reload Counter Zero Interrupt Enable   */
    DMA_MARIE  = 0x04,  /*!< Memory Address Reload Interrupt Enable */
    DMA_MERRIE = 0x08,  /*!< Memory Access Error Interrupt Enable   */
};


/** DMA Info Register bit offsets */
enum
{
    DMA_INFO_DS_SHIFT      = 0,   /*!<  DMA Info Register Downstream Shift  */
    DMA_INFO_US_SHIFT      = 8,   /*!<  DMA Info Register Upstream Shift    */
    DMA_INFO_PERIPH_SHIFT  = 16,  /*!<  DMA Info Register Periph Shift      */
};

/** Timer Control Register masks */
enum
{
    DMA_INFO_DS_MASK       = 0xFF << DMA_INFO_DS_SHIFT,      /*!<  DMA Info Register Downstream Mask    */
    DMA_INFO_US_MASK       = 0xFF << DMA_INFO_US_SHIFT,      /*!<  DMA Info Register Upstream Mask      */
    DMA_INFO_PERIPH_MASK   = 0xFF << DMA_INFO_PERIPH_SHIFT,  /*!<  DMA Info Register Periph Mask        */
};

/**
 * @name Info Register helper macros
 * @{
 */
#define DMA_GET_DOWNSTREAM_NUM(dma_info)  ((dma_info & DMA_INFO_DOWNSTEAM_MASK) >> DMA_INFO_DOWNSTREAM_SHIFT) /*!< DMA Downstream Channels Number */
#define DMA_GET_UPSTREAM_NUM(dma_info)    ((dma_info & DMA_INFO_UPSTREAM_MASK)  >> DMA_INFO_UPSTREAM_SHIFT)   /*!< DMA Upstream Number */
#define DMA_GET_PERIPH_NUM(dma_info)      ((dma_info & DMA_INFO_PERIPH_MASK)    >> DMA_INFO_PERIPH_SHIFT)     /*!< DMA Peripherals Number */
/** @} */

/** @} */

#endif /* __CCPROC_AMBA_DMA_H */
/** @} */
