/* ----------------------------------------------------------------------
*
* Copyright (c) 2018 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2019-11-03 23:10:21 +0100 (nie, 03 lis 2019) $
* $Revision: 481 $
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
 * @file            ccproc-amba-hhg110ullfmc.h
 * @brief           CC Processor AMBA FLASH definitions
 * @author          Maciej Plasota
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_FLASH_H
#define __CCPROC_AMBA_FLASH_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup flash Flash Controller
 * Flash Controller registers and definitions
 * @{
 *//************************/

/** Flash Controller Registers */
typedef struct
{
    volatile uint32_t STATUS;                    /*!< Status Register                      */
    volatile uint32_t CTRL;                      /*!< Control Register                     */
    volatile uint32_t COMMAND;                   /*!< Command Register                     */
    volatile uint32_t LOCK;                      /*!< Lock Register                        */
    volatile uint32_t ADDRESS;                   /*!< Address Register                     */
    volatile uint32_t DATA;                      /*!< Data Register                        */
    volatile uint32_t IRQM;                      /*!< Interrupt Mask Register              */
    volatile uint32_t IRQMAP;                    /*!< Interrupt Mapping Register           */
    volatile uint32_t MASTER_LOCKS;              /*!< Master Lock Bits Register            */
    volatile uint32_t INFO;                      /*!< Info Register                        */
    volatile uint32_t REGION_LOCKS[2];           /*!< Region Lock Bits Register            */
    volatile uint32_t _reserved1[116];
    volatile uint32_t USER_ROW[128];             /*!< User Row Direct Access Space         */
    volatile uint32_t MANUFACTURER_ROW[128];     /*!< Manufacturer Row Direct Access Space */
    volatile uint32_t FACTORY_ROW[128];          /*!< Factory Row Direct Access Space      */
    volatile uint32_t _reserved2[128];
    volatile uint32_t PAGE_BUFFER[128];          /*!< Page Buffer Direct Access Space      */
} amba_flash_t;

#ifdef CCPROC_SDK
 static volatile amba_flash_t * const AMBA_FLASH_PTR = (amba_flash_t*)AMBA_FLASH_BASE;  /*!< Flash controller pointer  */
#endif

/** Flash Status Register Flags */
enum
{
    FLASH_STATUS_BUSY               = 0x01, /*!< Busy Status bit mask               */
    FLASH_STATUS_PROGRAMMING_ERROR  = 0x02, /*!< Programming Error Status bit mask  */
    FLASH_STATUS_LOCK_ERROR         = 0x04, /*!< Lock Error Status bit mask         */
    FLASH_STATUS_CURRENT_COMMAND    = 0xF8, /*!< Current Command bit mask           */
};

/** Flash Control Register Flags */
enum
{
    FLASH_CTRL_HCLK_FREQ                = 0x0000001F,   /*!< HCLK current frequency mask    */
    FLASH_CTRL_SEQUENTIAL_PREFETCH      = 0x00000020,   /*!< Sequential Prefetch enable     */
    FLASH_CTRL_ASSUME_READS_SEQUENTIAL  = 0x00000040,   /*!< Start all new reads as sequential enable */
    FLASH_CTRL_READ_WAIT_STATES         = 0x00000F80,   /*!< Read Memory wait states number */
};

/** HCLK current frequency values  */
enum
{
    FLASH_CTRL_HCLK_FREQ_600kHz     = 0,
    FLASH_CTRL_HCLK_FREQ_750kHz     = 1,
    FLASH_CTRL_HCLK_FREQ_1MHz       = 2,
    FLASH_CTRL_HCLK_FREQ_1_25MHz    = 3,
    FLASH_CTRL_HCLK_FREQ_1_5MHz     = 4,
    FLASH_CTRL_HCLK_FREQ_2MHz       = 5,
    FLASH_CTRL_HCLK_FREQ_2_5MHz     = 6,
    FLASH_CTRL_HCLK_FREQ_3MHz       = 7,
    FLASH_CTRL_HCLK_FREQ_4MHz       = 8,
    FLASH_CTRL_HCLK_FREQ_4_5MHz     = 9,
    FLASH_CTRL_HCLK_FREQ_5_5MHz     = 10,
    FLASH_CTRL_HCLK_FREQ_7MHz       = 11,
    FLASH_CTRL_HCLK_FREQ_9MHz       = 12,
    FLASH_CTRL_HCLK_FREQ_12MHz      = 13,
    FLASH_CTRL_HCLK_FREQ_16MHz      = 14,
    FLASH_CTRL_HCLK_FREQ_21MHz      = 15,
    FLASH_CTRL_HCLK_FREQ_27MHz      = 16,
    FLASH_CTRL_HCLK_FREQ_35MHz      = 17,
    FLASH_CTRL_HCLK_FREQ_45MHz      = 18,
    FLASH_CTRL_HCLK_FREQ_60MHz      = 19,
    FLASH_CTRL_HCLK_FREQ_80MHz      = 20,
    FLASH_CTRL_HCLK_FREQ_100MHz     = 21,
    FLASH_CTRL_HCLK_FREQ_120MHz     = 22,
    FLASH_CTRL_HCLK_FREQ_140MHz     = 23,
    FLASH_CTRL_HCLK_FREQ_180MHz     = 24,
    FLASH_CTRL_HCLK_FREQ_200MHz     = 25,
    FLASH_CTRL_HCLK_FREQ_220MHz     = 26,
    FLASH_CTRL_HCLK_FREQ_250MHz     = 27,
};

enum
{
    FLASH_CTRL_READ_WAIT_STATES_OFFSET  = 7,        /*!< Read Memory wait states number offset within CTRL register */
};

/** Flash Command Register Flags */
typedef enum
{
    FLASH_COMMAND_MASK                          = 0x0000001F,     /*!< Command code mask                        */
    FLASH_COMMAND_NOP                           = 0,              /*!< No operation                             */
    FLASH_COMMAND_WRITE_PAGE                    = 1,              /*!< Write Page command                       */
    FLASH_COMMAND_WRITE_WORD                    = 2,              /*!< Write Word from Page Buffer command      */
    FLASH_COMMAND_WRITE_IMMEDIATE               = 3,              /*!< Write Word from Data Register command    */
    FLASH_COMMAND_ERASE_PAGE                    = 4,              /*!< Erase Page command                       */
    FLASH_COMMAND_ERASE_ALL                     = 5,              /*!< Erase All command                        */
    FLASH_COMMAND_CLR_PAGE_BUFFER               = 6,              /*!< Clear Page Buffer command                */
    FLASH_COMMAND_LOCK_REGION                   = 7,              /*!< Lock Data Region command                 */
    FLASH_COMMAND_LOCK_DEBUGGER_READ            = 8,              /*!< Lock Debugger Memory Read command        */
    FLASH_COMMAND_LOCK_DEBUGGER_ACCESS          = 9,              /*!< Lock Debugger Access command             */
    FLASH_COMMAND_WRITE_FACTORY_ROW_PAGE        = 10,             /*!< Write Factory Row Data Page command      */
    FLASH_COMMAND_WRITE_FACTORY_ROW_WORD        = 11,             /*!< Write Factory Row Data Word command      */
    FLASH_COMMAND_READ_FACTORY_ROW_WORD         = 12,             /*!< Read Factory Row Data Word command       */
    FLASH_COMMAND_ERASE_FACTORY_ROW             = 13,             /*!< Erase Factory Row command                */
    FLASH_COMMAND_LOCK_FACTORY_ROW              = 14,             /*!< Lock Factory Row command                 */
    FLASH_COMMAND_WRITE_USER_ROW_PAGE           = 15,             /*!< Write User Row Data Page command         */
    FLASH_COMMAND_WRITE_USER_ROW_WORD           = 16,             /*!< Write User Row Data Word command         */
    FLASH_COMMAND_READ_USER_ROW_WORD            = 17,             /*!< Read User Row Data Word command          */
    FLASH_COMMAND_ERASE_USER_ROW                = 18,             /*!< Erase User Row command                   */
    FLASH_COMMAND_LOCK_USER_ROW                 = 19,             /*!< Lock User Row command                    */
    FLASH_COMMAND_WRITE_MANUFACTURER_ROW_PAGE   = 20,             /*!< Write Manufacturer Row Data Page command */
    FLASH_COMMAND_WRITE_MANUFACTURER_ROW_WORD   = 21,             /*!< Write Manufacturer Row Data Word command */
    FLASH_COMMAND_READ_MANUFACTURER_ROW_WORD    = 22,             /*!< Read Manufacturer Row Data Word command  */
    FLASH_COMMAND_ERASE_MANUFACTURER_ROW        = 23,             /*!< Erase Manufacturer Row command           */
    FLASH_COMMAND_LOCK_MANUFACTURER_ROW         = 24,             /*!< Lock Manufacturer Row command            */
    FLASH_COMMAND_CHIP_ERASE                    = 25,             /*!< Chip Erase command                       */
    FLASH_COMMAND_LOCK_CHIP_ERASE               = 26,             /*!< Lock access to Chip Erase command        */
    FLASH_COMMAND_WRITE_PAGE_BUFFER_WORD        = 27,             /*!< Write Data Word to Page Buffer command   */
    FLASH_COMMAND_READ_PAGE_BUFFER_WORD         = 28,             /*!< Read Data Word from Page Buffer command  */
    FLASH_COMMAND_LOCK_DIRECT_NVR_ACCESS        = 32,             /*!< Lock direct access to NVR registers      */
    FLASH_COMMAND_LOCK_CONFIG_LATCH_ACCESS      = 35              /*!< Lock access to config latches            */
} amba_flash_command_t;

/** Flash Lock Register Flags */
enum
{
    FLASH_LOCK_ACCESS_PASSWORD                  = 0x554E4C4B,
    FLASH_LOCK_FACTORY_ROW_ACCESS_PASSWORD      = FLASH_LOCK_ACCESS_PASSWORD,
    FLASH_LOCK_USER_ROW_ACCESS_PASSWORD         = FLASH_LOCK_ACCESS_PASSWORD,
    FLASH_LOCK_MANUFACTURER_ROW_ACCESS_PASSWORD = FLASH_LOCK_ACCESS_PASSWORD,
};

/** Flash Interrupt Mask Register Flags */
enum
{
    FLASH_IRQM_READY_IE             = 0x0001,  /*!< Flash Ready Interrupt Enable  */
    FLASH_IRQM_PROGRAMMING_ERROR_IE = 0x0002,  /*!< Flash Programming Error Interrupt Enable  */
    FLASH_IRQM_LOCK_ERROR_IE        = 0x0004,  /*!< Flash Locked Error Interrupt Enable  */
};

/** Flash Master Locks Register Flags */
enum
{
    FLASH_MASTER_LOCKS_DEBUGGER_READ_DISABLED   = 0x00000001,  /*!< Flash Debugger Read Disabled bit mask     */
    FLASH_MASTER_LOCKS_DEBUGGER_ACCESS_DISABLED = 0x00000002,  /*!< Flash Debugger Access Disabled bit mask   */
    FLASH_MASTER_LOCKS_MANUFACTURER_ROW_LOCKED  = 0x00000004,  /*!< Flash Manufacturer Row locked bit mask    */
    FLASH_MASTER_LOCKS_FACTORY_ROW_LOCKED       = 0x00000008,  /*!< Flash Factory Row locked bit mask         */
    FLASH_MASTER_LOCKS_USER_ROW_LOCKED          = 0x00000010,  /*!< Flash User Row locked bit mask            */
    FLASH_MASTER_LOCKS_CONFIG_ACCESS_LOCKED     = 0x20000000,  /*!< Flash User Row locked bit mask            */
    FLASH_MASTER_LOCKS_NVR_ACCESS_LOCKED        = 0x40000000,  /*!< Flash User Row locked bit mask            */
    FLASH_MASTER_LOCKS_CHIP_ERASE_LOCKED        = 0x80000000,  /*!< Flash Chip Erase command locked bit mask  */
};

/** Flash Info Register Masks */
enum
{
    FLASH_INFO_PAGE_SIZE_OFFSET      = 0,           /*!< Flash Info Page Size offset in bytes       */
    FLASH_INFO_PAGE_SIZE_MASK        = 0x0000000F,  /*!< Flash Info Page Size bit mask              */
    FLASH_INFO_MODULE_SIZE_OFFSET    = 4,           /*!< Flash Info Module Size offset in bytes     */
    FLASH_INFO_MODULE_SIZE_MASK      = 0x000000F0,  /*!< Flash Info Module Size bit mask            */
    FLASH_INFO_REGION_SIZE_OFFSET    = 8,           /*!< Flash Info Region Size offset in bytes     */
    FLASH_INFO_REGION_SIZE_MASK      = 0x0000FF00,  /*!< Flash Info Region Size bit mask            */
    FLASH_INFO_MODULES_NUMBER_OFFSET = 16,          /*!< Flash Info Modules Number offset in bytes  */
    FLASH_INFO_MODULES_NUMBER_MASK   = 0x000F0000,  /*!< Flash Info Modules Number bit mask         */
};

/** Flash Info Register Page Size Flags */
enum
{
    FLASH_INFO_PAGE_SIZE_UNDEFINED = 0,   /*!< Flash Info Page Size undefined    */
    FLASH_INFO_PAGE_SIZE_512B = 1,        /*!< Flash Info Page Size 512 bytes    */
};

/** Flash Info Register Module Size Flags */
enum
{
    FLASH_INFO_MODULE_SIZE_UNDEFINED = 0,  /*!< Flash Info Module Size undefined */
    FLASH_INFO_MODULE_SIZE_512_PAGES = 1,  /*!< Flash Info Module Size 512 pages */
};

/** Helper macro for calculating read wait states count */
#define FLASH_READ_WAIT_STATES_CALC(hclk) ( FLASH_DELAY / (1000000000UL/(hclk)) )

/** @} */

#endif /* __CCPROC_AMBA_FLASH_H */
/** @} */
