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
 * @file            ccproc-amba.h
 * @brief           CC Processor AMBA definitions
 * @author          Rafal Harabien
 *
 * @defgroup        CCAMBA AMBA Peripherials
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_H
#define __CCPROC_AMBA_H

#include <stdint.h>
#include "ccproc.h"

/** 
 * @cond
 * enable/disable static assertions
 */
#if 0
 #define STATIC_ASSERT(expr, msg) _Static_assert(expr, msg)
#else
 #define STATIC_ASSERT(expr, msg)
#endif

/** @endcond */

/** 
 * @cond
 * enable/disable ccproc sdk integration
 */
#if 1
 #define CCPROC_SDK
#endif

/** @endcond */

/** AMBA addresses */
enum
{
    AMBA_UART0_BASE      = AMBA_BASE + 0x00000100,          /*!< UART 0 base address                        */
    AMBA_UART1_BASE      = AMBA_BASE + 0x00000200,          /*!< UART 1 base address                        */
    AMBA_UART2_BASE      = AMBA_BASE + 0x00000300,          /*!< UART 2 base address                        */
    AMBA_UART3_BASE      = AMBA_BASE + 0x00000400,          /*!< UART 3 base address                        */
    AMBA_UART4_BASE      = AMBA_BASE + 0x00000500,          /*!< UART 4 base address                        */
    AMBA_UART5_BASE      = AMBA_BASE + 0x00000600,          /*!< UART 5 base address                        */
    AMBA_UART6_BASE      = AMBA_BASE + 0x00000700,          /*!< UART 6 base address                        */
    AMBA_UART7_BASE      = AMBA_BASE + 0x00000800,          /*!< UART 7 base address                        */
    AMBA_SPI0_BASE       = AMBA_BASE + 0x00000A00,          /*!< SPI 0 base address                         */
    AMBA_SPI1_BASE       = AMBA_BASE + 0x00000B00,          /*!< SPI 1 base address                         */
    AMBA_SPI2_BASE       = AMBA_BASE + 0x00000C00,          /*!< SPI 2 base address                         */
    AMBA_SPI3_BASE       = AMBA_BASE + 0x00000D00,          /*!< SPI 3 base address                         */
    AMBA_GPIO_BASE       = AMBA_BASE + 0x00000E00,          /*!< GPIO base address                          */
    AMBA_TIMER32_0_BASE  = AMBA_BASE + 0x00000F00,          /*!< Timers 32 0 base address                   */
    AMBA_TIMER32_1_BASE  = AMBA_BASE + 0x00001000,          /*!< Timers 32 1 base address                   */
    AMBA_TIMER16_0_BASE  = AMBA_BASE + 0x00001100,          /*!< Timers 16 0 base address                   */
    AMBA_TIMER16_1_BASE  = AMBA_BASE + 0x00001200,          /*!< Timers 16 1 base address                   */
    AMBA_SYSTICK_BASE    = AMBA_BASE + 0x00001300,          /*!< Systick base address                       */
    AMBA_RTC_BASE        = AMBA_BASE + 0x00001400,          /*!< Real-Time Clock base address               */
    AMBA_WDT_BASE        = AMBA_BASE + 0x00001500,          /*!< Watchdog base address                      */
    AMBA_I2C_MST_0_BASE  = AMBA_BASE + 0x00001600,          /*!< I2C Master 0 base address                  */
    AMBA_I2C_MST_1_BASE  = AMBA_BASE + 0x00001700,          /*!< I2C Master 1 base address                  */
    AMBA_I2C_SLV_BASE    = AMBA_BASE + 0x00001800,          /*!< I2C Slave base address                     */
    AMBA_PROM_BASE       = AMBA_BASE + 0x00001900,          /*!< PROM base address                          */
    AMBA_1WIRE_BASE      = AMBA_BASE + 0x00001A00,          /*!< 1 WIRE base address                        */
    AMBA_ADC_BASE        = AMBA_BASE + 0x00006000,          /*!< ADC base address                           */
    AMBA_REG_BASE        = AMBA_BASE + 0x00007000,          /*!< Config Registers base address              */
    AMBA_DMA_BASE        = AMBA_BASE + 0x00008000,          /*!< DMA base address                           */
    AMBA_CAN0_BASE       = AMBA_BASE + 0x00009000,          /*!< CAN 0 base address                         */
    AMBA_CAN1_BASE       = AMBA_BASE + 0x0000A000,          /*!< CAN 1 base address                         */
    AMBA_BLE0_BASE       = AMBA_BASE + 0x0000B000,          /*!< BLE 0 base address                         */
    AMBA_BLE1_BASE       = AMBA_BASE + 0x0000C000,          /*!< BLE 1 base address                         */
    AMBA_APB1_BASE       = AMBA_BASE + 0x01000000,          /*!< APB 1 Bridge base address                  */
    AMBA_APB2_BASE       = AMBA_BASE + 0x02000000,          /*!< APB 2 Bridge base address                  */
    AMBA_FLASH_BASE      = AMBA_APB1_BASE + 0x00000000,     /*!< Embedded Flash base address                */
    AMBA_MEMCTRL_BASE    = AMBA_APB1_BASE + 0x00001000,     /*!< External Memory Controller base address    */
    AMBA_ETH0_BASE       = AMBA_APB2_BASE + 0x00001000,     /*!< ETH0 base address                          */
    AMBA_ETH1_BASE       = AMBA_APB2_BASE + 0x00002000,     /*!< ETH1 base address                          */
};

/** APB0 Configuration Registers */
typedef struct
{
    uint32_t INFO_0;    /*!< APB0 Info Register 0        */
    uint32_t INFO_1;    /*!< APB0 Info Register 1        */
    uint32_t APB1_CFG;  /*!< APB1 Configuration Register */
} amba_apb0_cfg_t;

#ifdef CCPROC_SDK
 static volatile amba_apb0_cfg_t * const AMBA_APB0_CFG_PTR = (amba_apb0_cfg_t*)AMBA_BASE;  /*!< APB0 Configuration Registers pointer  */
#endif

/** APB2 Configuration Registers */
typedef struct
{
    uint32_t INFO_0;    /*!< APB2 Info Register 0            */
    uint32_t INFO_1;    /*!< APB2 Info Register 1            */
    uint32_t _reserved[2];
    uint32_t CLOCK_0;   /*!< Clock Configuration Register 0  */
    uint32_t CLOCK_1;   /*!< Clock Configuration Register 1  */
    uint32_t ETHMAP_0;  /*!< ETH0 Interrupt Mapping Register */
    uint32_t ETHMAP_1;  /*!< ETH1 Interrupt Mapping Register */
} amba_apb2_cfg_t;

#ifdef CCPROC_SDK
 static volatile amba_apb2_cfg_t * const AMBA_APB2_CFG_PTR = (amba_apb2_cfg_t*)AMBA_APB2_BASE;  /*!< APB2 Configuration Registers pointer  */
#endif

/** AMBA0 Info 0 bitfield offsets */
enum
{
    AMBA_UART_COUNT_SHIFT     = 0,   /*!< Number of UART Controllers bitfield offset        */
    AMBA_SPI_COUNT_SHIFT      = 4,   /*!< Number of SPI Controllers bitfield offset         */
    AMBA_GPIO_COUNT_SHIFT     = 7,   /*!< Number of GPIO Pins bitfield offset               */
    AMBA_DMA_DWN_COUNT_SHIFT  = 13,  /*!< Number of DMA DOWN Channels bitfield offset       */
    AMBA_DMA_UP_COUNT_SHIFT   = 16,  /*!< Number of DMA UP Channels bitfield offset         */
    AMBA_TIMER32_COUNT_SHIFT  = 19,  /*!< Number of 32-Bit Timers bitfield offset           */
    AMBA_TIMER16_COUNT_SHIFT  = 21,  /*!< Number of 16-Bit Timers bitfield offset           */
    AMBA_I2C_MST_COUNT_SHIFT  = 26,  /*!< Number of I2C Master Controllers bitfield offset  */
    AMBA_CAN_COUNT_SHIFT      = 30,  /*!< Number of CAN Controllers bitfield offset         */
};

/** AMBA0 Info 1 bitfield offsets */
enum
{
    AMBA_BLE_COUNT_SHIFT      = 0,   /*!< Number of BLE Controllers bitfield offset     */
    AMBA_AIDCODE_SHIFT        = 16,  /*!< Analog IDCODE bitfield offset                 */
};

/** AMBA2 Info 0 bitfield offsets */
enum
{
    AMBA_ETH_COUNT_SHIFT      = 0,   /*!< Number of ETH Controllers bitfield offset     */
};

/**
 * @name Maximal number of devices supported by AMBA register bits
 * @{
 */

#define MAX_NUM_OF_UART     0x0F  /*!< Maximal number of UART Controllers       */
#define MAX_NUM_OF_SPI      0x07  /*!< Maximal number of SPI Controllers        */
#define MAX_NUM_OF_GPIO     0x3F  /*!< Maximal number of GPIO Pins              */
#define MAX_NUM_OF_DMA_DWN  0x07  /*!< Maximal number of DMA DOWN Channels      */
#define MAX_NUM_OF_DMA_UP   0x07  /*!< Maximal number of DMA UP Channels        */
#define MAX_NUM_OF_TIMER32  0x03  /*!< Maximal number of 32-Bit Timers          */
#define MAX_NUM_OF_TIMER16  0x03  /*!< Maximal number of 16-Bit Timers          */
#define MAX_NUM_OF_I2C_MST  0x03  /*!< Maximal number of I2C Master Controllers */
#define MAX_NUM_OF_CAN      0x03  /*!< Maximal number of CAN Controllers        */
#define MAX_NUM_OF_BLE      0x03  /*!< Maximal number of BLE Controllers        */
#define MAX_NUM_OF_ETH      0x03  /*!< Maximal number of ETH Controllers        */
#define MAX_AIDCODE         0xFF  /*!< Maximal value of Analog IDCODE           */

/** @} */

/**
 * @name Macros for getting number of devices on AMBA bus
 * @{
 */

#define AMBA_UART_COUNT()     ((AMBA_APB0_CFG_PTR->INFO_0 >> AMBA_UART_COUNT_SHIFT)    & MAX_NUM_OF_UART)    /*!< Number of UART Controllers        */
#define AMBA_SPI_COUNT()      ((AMBA_APB0_CFG_PTR->INFO_0 >> AMBA_SPI_COUNT_SHIFT)     & MAX_NUM_OF_SPI)     /*!< Number of SPI Controllers         */
#define AMBA_GPIO_COUNT()     ((AMBA_APB0_CFG_PTR->INFO_0 >> AMBA_GPIO_COUNT_SHIFT)    & MAX_NUM_OF_GPIO)    /*!< Number of GPIO pins               */
#define AMBA_DMA_DWN_COUNT()  ((AMBA_APB0_CFG_PTR->INFO_0 >> AMBA_DMA_DWN_COUNT_SHIFT) & MAX_NUM_OF_DMA_DWN) /*!< Number of DMA DOWN Channels       */
#define AMBA_DMA_UP_COUNT()   ((AMBA_APB0_CFG_PTR->INFO_0 >> AMBA_DMA_UP_COUNT_SHIFT)  & MAX_NUM_OF_DMA_UP)  /*!< Number of DMA UP Channels         */
#define AMBA_TIMER32_COUNT()  ((AMBA_APB0_CFG_PTR->INFO_0 >> AMBA_TIMER32_COUNT_SHIFT) & MAX_NUM_OF_TIMER32) /*!< Number of 32-Bit Timers           */
#define AMBA_TIMER16_COUNT()  ((AMBA_APB0_CFG_PTR->INFO_0 >> AMBA_TIMER16_COUNT_SHIFT) & MAX_NUM_OF_TIMER16) /*!< Number of 16-Bit Timers           */
#define AMBA_I2C_MST_COUNT()  ((AMBA_APB0_CFG_PTR->INFO_0 >> AMBA_I2C_MST_COUNT_SHIFT) & MAX_NUM_OF_I2C_MST) /*!< Number of I2C Master Controllers  */
#define AMBA_CAN_COUNT()      ((AMBA_APB0_CFG_PTR->INFO_0 >> AMBA_CAN_COUNT_SHIFT)     & MAX_NUM_OF_CAN)     /*!< Number of CAN Controllers         */

#define AMBA_BLE_COUNT()      ((AMBA_APB0_CFG_PTR->INFO_1 >> AMBA_BLE_COUNT_SHIFT)     & MAX_NUM_OF_BLE)     /*!< Number of BLE Controllers         */
#define AMBA_ETH_COUNT()      ((AMBA_APB2_CFG_PTR->INFO_0 >> AMBA_ETH_COUNT_SHIFT)     & MAX_NUM_OF_ETH)     /*!< Number of ETH Controllers         */

#define AMBA_AIDCODE()        ((AMBA_APB0_CFG_PTR->INFO_1 >> AMBA_AIDCODE_SHIFT)       & MAX_AIDCODE)        /*!< Get Analog IDCODE                 */

#define AMBA_APB1_EXIST()     (AMBA_APB0_CFG_PTR->INFO_0 & AMBA_APB1)                                        /*!< Check if APB1 bridge exists       */
#define AMBA_APB2_EXIST()     (AMBA_APB0_CFG_PTR->INFO_1 & AMBA_APB2)                                        /*!< Check if APB2 bridge exists       */

/** @} */

/** AMBA0 Info 0 Register Flags */
enum
{
    AMBA_STT    = 1 << 23,  /*!< System Tick Timer */
    AMBA_RTC    = 1 << 24,  /*!< Real-Time Clock   */
    AMBA_WDT    = 1 << 25,  /*!< Watchdog Timer    */
    AMBA_PROM   = 1 << 28,  /*!< PROM Memory       */
    AMBA_APB1   = 1 << 29,  /*!< APB1 Bridge       */
};

/** AMBA0 Info 1 Register Flags */
enum
{
    AMBA_REG        = 1 << 2,  /*!< Config Registers        */
    AMBA_I2C_SLV    = 1 << 3,  /*!< I2C Slave Controller    */
    AMBA_1WIRE      = 1 << 4,  /*!< 1 Wire Controller       */
    AMBA_APB2       = 1 << 15, /*!< APB2 Bridge             */
};

/** AMBA0 APB1 Configuration Masks */
enum
{
    AMBA_APB1_EN    = 1 << 0,  /*!< APB1 Bridge Enable      */
};

/** AMBA2 Clock 0 Register Masks */
enum
{
    AMBA_ETH0_CLK   = 1 << 0,  /*!< ETH 0 Clock   */
    AMBA_ETH1_CLK   = 1 << 1,  /*!< ETH 1 Clock   */
};

#endif /* __CCPROC_AMBA_H */
/** @} */
