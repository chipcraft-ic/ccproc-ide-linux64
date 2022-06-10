/* ----------------------------------------------------------------------
*
* Copyright (c) 2022 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2022-01-15 10:20:27 +0100 (sob, 15 sty 2022) $
* $Revision: 812 $
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
 * @file            ccproc-amba-tsmc40ulpfmc.h
 * @brief           CC Processor AMBA FLASH definitions
 * @author          Maciej Plasota
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_TSMC40ULPFMC_FLASH_H
#define __CCPROC_AMBA_TSMC40ULPFMC_FLASH_H

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
    volatile uint32_t STATUS;                    /*!< Status Register                           */
    volatile uint32_t CTRL;                      /*!< Control Register                          */
    volatile uint32_t TIMING;                    /*!< Time Count Settings Register              */
    volatile uint32_t SMWR_OPTION_0;             /*!< SMWR Settings - OPTION part 0 Register    */
    volatile uint32_t SMWR_OPTION_1;             /*!< SMWR Settings - OPTION part 1 Register    */
    volatile uint32_t SMWR_OPTION_2;             /*!< SMWR Settings - OPTION part 2 Register    */
    volatile uint32_t SMWR_OPTION_3;             /*!< SMWR Settings - OPTION part 3 Register    */
    volatile uint32_t SMWR_SMP_WHV_1;            /*!< SMWR Settings - SMP WHV part 0 Register   */
    volatile uint32_t SMWR_SMP_WHV_2;            /*!< SMWR Settings - SMP WHV part 1 Register   */
    volatile uint32_t SMWR_SME_WHV_1;            /*!< SMWR Settings - SME WHV part 0 Register   */
    volatile uint32_t SMWR_SME_WHV_2;            /*!< SMWR Settings - SME WHV part 1 Register   */
    volatile uint32_t COMMAND;                   /*!< Command Register                          */
    volatile uint32_t LOCK;                      /*!< Lock Register                             */
    volatile uint32_t ADDRESS;                   /*!< Address Register                          */
    volatile uint32_t DATA_WORD_0;               /*!< Data Word 0 Register                      */
    volatile uint32_t DATA_WORD_1;               /*!< Data Word 1 Register                      */
    volatile uint32_t DATA_WORD_2;               /*!< Data Word 2 Register                      */
    volatile uint32_t DATA_WORD_3;               /*!< Data Word 3 Register                      */
    volatile uint32_t IRQM;                      /*!< Interrupt Mask Register                   */
    volatile uint32_t IRQMAP;                    /*!< Interrupt Mapping Register                */
    volatile uint32_t INFO;                      /*!< Info Register                             */
#ifndef BOARD_CCNV2_A1
    volatile uint32_t ECC_CORRECTABLE_COUNT;     /*!< Correctable ECC Errors Count Register     */
    volatile uint32_t ECC_UNCORRECTABLE_COUNT;   /*!< Uncorrectable ECC Errors Count Register   */
    volatile uint32_t ECC_CORRECTABLE_ADDRESS;   /*!< Correctable ECC Errors Count Register     */
    volatile uint32_t ECC_UNCORRECTABLE_ADDRESS; /*!< Uncorrectable ECC Errors Count Register   */
#endif
    volatile uint32_t MASTER_LOCKS;              /*!< Master Lock Bits Register                 */
    volatile uint32_t REGION_LOCKS[4];           /*!< Region Lock Bits Register                 */
#ifndef BOARD_CCNV2_A1
    volatile uint32_t _reserved1[226];
#else
    volatile uint32_t _reserved1[230];
#endif
    volatile uint32_t SECTOR_BUFFER[256];        /*!< Sector Buffer Direct Access Space         */
} amba_flash_t;

#ifdef CCPROC_SDK
 static volatile amba_flash_t * const AMBA_FLASH_PTR = (amba_flash_t*)AMBA_FLASH_BASE;  /*!< Flash controller pointer  */
#endif

/** Flash Status Register Flags */
enum
{
    FLASH_STATUS_BUSY                  = 0x001, /*!< Busy Status bit mask               */
    FLASH_STATUS_PROGRAMMING_ERROR     = 0x002, /*!< Programming Error Status bit mask  */
    FLASH_STATUS_LOCK_ERROR            = 0x004, /*!< Lock Error Status bit mask         */
    FLASH_STATUS_CURRENT_COMMAND       = 0x1F8, /*!< Current Command bit mask           */
    FLASH_STATUS_CORRECTABLE_ECC_ERR   = 0x200, /*!< Correctable ECC Error bit mask     */
    FLASH_STATUS_UNCORRECTABLE_ECC_ERR = 0x400, /*!< Uncorrectable ECC Error bit mask   */
};

/** Flash Control Register Flags */
enum
{
    FLASH_CTRL_SEQUENTIAL_PREFETCH      = 0x00000001,   /*!< Sequential prefetch enable                 */
    FLASH_CTRL_ASSUME_READS_SEQUENTIAL  = 0x00000002,   /*!< Start all new reads as sequential enable   */
    FLASH_CTRL_REPROGRAM_ZEROS_ON_WRITE = 0x00000004,   /*!< Reprogram 0s during flash write enable     */
    FLASH_CTRL_HIGH_ENDURANCE_MODE      = 0x00000008,   /*!< Flash High Endurance Mode enable           */
    FLASH_CTRL_LOW_VOLTAGE_MODE         = 0x00000010,   /*!< Flash Low Voltage operating Mode enable    */
    FLASH_CTRL_ECC_ENABLE               = 0x00000020,   /*!< Flash ECC correction enable                */
    FLASH_CTRL_SMWR_PRESCALER           = 0x000000C0,   /*!< Smart Write prescaler                      */
    FLASH_CTRL_SELF_TIME_BYPASS_ENABLE  = 0x00000100,   /*!< Sector Buffer Self Time Bypass mode enable */
    FLASH_CTRL_READ_MARGIN_ENABLE       = 0x00000200,   /*!< Sector Buffer manual Read Margin enable    */
    FLASH_CTRL_READ_MARGIN              = 0x00003C00,   /*!< Sector Buffer manual Read Margin value     */
    FLASH_CTRL_REPORT_ECC_ON_AHB_ENABLE = 0x00008000,   /*!< Report ECC errors on AHB enable            */
    FLASH_CTRL_READ_WAIT_STATES         = 0x003F0000,   /*!< Read Memory wait states number             */
};

/** SMWR Prescaler values  */
typedef enum
{
    FLASH_CTRL_SMWR_PRESCALER_1         = 0,
    FLASH_CTRL_SMWR_PRESCALER_2         = 1,
    FLASH_CTRL_SMWR_PRESCALER_4         = 2,
    FLASH_CTRL_SMWR_PRESCALER_8         = 3
} amba_flash_SMWR_prescaler_t;

/** Flash Control Register flags offsets */
enum
{
    FLASH_CTRL_SEQUENTIAL_PREFETCH_OFFSET       = 0,
    FLASH_CTRL_ASSUME_READS_SEQUENTIAL_OFFSET   = 1,
    FLASH_CTRL_REPROGRAM_ZEROS_ON_WRITE_OFFSET  = 2,
    FLASH_CTRL_HIGH_ENDURANCE_MODE_OFFSET       = 3,
    FLASH_CTRL_LOW_VOLTAGE_MODE_OFFSET          = 4,
    FLASH_CTRL_ECC_ENABLE_OFFSET                = 5,
    FLASH_CTRL_SMWR_PRESCALER_OFFSET            = 6,
    FLASH_CTRL_SELF_TIME_BYPASS_ENABLE_OFFSET   = 8,
    FLASH_CTRL_READ_MARGIN_ENABLE_OFFSET        = 9,
    FLASH_CTRL_READ_MARGIN_OFFSET               = 10,
    FLASH_CTRL_REPORT_ECC_ON_AHB_ENABLE_OFFSET  = 15,
    FLASH_CTRL_READ_WAIT_STATES_OFFSET          = 16
};

/** Flash Control Special Values */
enum
{
    FLASH_CTRL_READ_WAIT_STATES_DEFAULT         = FLASH_CTRL_READ_WAIT_STATES
};

/** Flash Timing Register offsets */
enum
{
    FLASH_TIMING_COUNT_2_NS_OFFSET      = 0,
    FLASH_TIMING_COUNT_12_5_NS_OFFSET   = 3,
    FLASH_TIMING_COUNT_20_NS_OFFSET     = 8,
    FLASH_TIMING_COUNT_100_NS_OFFSET    = 13,
    FLASH_TIMING_COUNT_1_US_OFFSET      = 21,
};

/** Flash Timing Register masks */
enum
{
    FLASH_TIMING_COUNT_2_NS_MASK      = 0x07 << FLASH_TIMING_COUNT_2_NS_OFFSET,
    FLASH_TIMING_COUNT_12_5_NS_MASK   = 0x01F << FLASH_TIMING_COUNT_12_5_NS_OFFSET,
    FLASH_TIMING_COUNT_20_NS_MASK     = 0x01F << FLASH_TIMING_COUNT_20_NS_OFFSET,
    FLASH_TIMING_COUNT_100_NS_MASK    = 0x0FF << FLASH_TIMING_COUNT_100_NS_OFFSET,
    FLASH_TIMING_COUNT_1_US_MASK      = 0x07FF << FLASH_TIMING_COUNT_1_US_OFFSET,
};

/** Flash SMWR_OPTION_0 Register offsets */
enum
{
    FLASH_SMWR_OPTION_0_MV_OFFSET           = 14,
    FLASH_SMWR_OPTION_0_MV_FINAL_OFFSET     = 17,
    FLASH_SMWR_OPTION_0_WIPGM_OFFSET        = 24,
    FLASH_SMWR_OPTION_0_WIPGM_FINAL_OFFSET  = 26
};

/** Flash SMWR_OPTION_0 Register masks */
enum
{
    FLASH_SMWR_OPTION_0_MV_MASK             = 0x07 << FLASH_SMWR_OPTION_0_MV_OFFSET,
    FLASH_SMWR_OPTION_0_MV_FINAL_MASK       = 0x07 << FLASH_SMWR_OPTION_0_MV_FINAL_OFFSET,
    FLASH_SMWR_OPTION_0_WIPGM_MASK          = 0x03 << FLASH_SMWR_OPTION_0_WIPGM_OFFSET,
    FLASH_SMWR_OPTION_0_WIPGM_FINAL_MASK    = 0x03 << FLASH_SMWR_OPTION_0_WIPGM_FINAL_OFFSET,
};

/** Flash SMWR_OPTION_1 Register offsets */
enum
{
    FLASH_SMWR_OPTION_1_TERS_OFFSET         = 0,
    FLASH_SMWR_OPTION_1_TPGM_OFFSET         = 3,
    FLASH_SMWR_OPTION_1_TNVS_OFFSET         = 5,
    FLASH_SMWR_OPTION_1_TNVH_OFFSET         = 8,
    FLASH_SMWR_OPTION_1_TPGS_OFFSET         = 11,
    FLASH_SMWR_OPTION_1_MAX_ERASE_OFFSET    = 14,
    FLASH_SMWR_OPTION_1_MAX_PROG_OFFSET     = 23
};

/** Flash SMWR_OPTION_1 Register masks */
enum
{
    FLASH_SMWR_OPTION_1_TERS_MASK         = 0x07 << FLASH_SMWR_OPTION_1_TERS_OFFSET,
    FLASH_SMWR_OPTION_1_TPGM_MASK         = 0x03 << FLASH_SMWR_OPTION_1_TPGM_OFFSET,
    FLASH_SMWR_OPTION_1_TNVS_MASK         = 0x07 << FLASH_SMWR_OPTION_1_TNVS_OFFSET,
    FLASH_SMWR_OPTION_1_TNVH_MASK         = 0x07 << FLASH_SMWR_OPTION_1_TNVH_OFFSET,
    FLASH_SMWR_OPTION_1_TPGS_MASK         = 0x07 << FLASH_SMWR_OPTION_1_TPGS_OFFSET,
    FLASH_SMWR_OPTION_1_MAX_ERASE_MASK    = 0x01FF << FLASH_SMWR_OPTION_1_MAX_ERASE_OFFSET,
    FLASH_SMWR_OPTION_1_MAX_PROG_MASK     = 0x01F << FLASH_SMWR_OPTION_1_MAX_PROG_OFFSET
};

/** Flash SMWR_OPTION_2 Register offsets */
enum
{
    FLASH_SMWR_OPTION_2_THVS_OFFSET             = 0,
    FLASH_SMWR_OPTION_2_TRCV_OFFSET             = 3,
    FLASH_SMWR_OPTION_2_EPP_OFFSET              = 6,
    FLASH_SMWR_OPTION_2_EPE_OFFSET              = 8,
    FLASH_SMWR_OPTION_2_WHV_OFFSET              = 10,
    FLASH_SMWR_OPTION_2_POST_TERS_OFFSET        = 18,
    FLASH_SMWR_OPTION_2_POST_TPGM_OFFSET        = 21,
    FLASH_SMWR_OPTION_2_VERIFY_OFFSET           = 23,
    FLASH_SMWR_OPTION_2_TPGM_OPTION_OFFSET      = 25,
    FLASH_SMWR_OPTION_2_MASK0_OFFSET            = 27,
    FLASH_SMWR_OPTION_2_DISABLE_PRE_READ_OFFSET = 28
};

/** Flash SMWR_OPTION_2 Register masks */
enum
{
    FLASH_SMWR_OPTION_2_THVS_MASK             = 0x07 << FLASH_SMWR_OPTION_2_THVS_OFFSET,
    FLASH_SMWR_OPTION_2_TRCV_MASK             = 0x07 << FLASH_SMWR_OPTION_2_TRCV_OFFSET,
    FLASH_SMWR_OPTION_2_EPP_MASK              = 0x03 << FLASH_SMWR_OPTION_2_EPP_OFFSET,
    FLASH_SMWR_OPTION_2_EPE_MASK              = 0x03 << FLASH_SMWR_OPTION_2_EPE_OFFSET,
    FLASH_SMWR_OPTION_2_WHV_MASK              = 0xFF << FLASH_SMWR_OPTION_2_WHV_OFFSET,
    FLASH_SMWR_OPTION_2_POST_TERS_MASK        = 0x07 << FLASH_SMWR_OPTION_2_POST_TERS_OFFSET,
    FLASH_SMWR_OPTION_2_POST_TPGM_MASK        = 0x03 << FLASH_SMWR_OPTION_2_POST_TPGM_OFFSET,
    FLASH_SMWR_OPTION_2_VERIFY_MASK           = 0x03 << FLASH_SMWR_OPTION_2_VERIFY_OFFSET,
    FLASH_SMWR_OPTION_2_TPGM_OPTION_MASK      = 0x03 << FLASH_SMWR_OPTION_2_TPGM_OPTION_OFFSET,
    FLASH_SMWR_OPTION_2_MASK0_MASK            = 0x01 << FLASH_SMWR_OPTION_2_MASK0_OFFSET,
    FLASH_SMWR_OPTION_2_DISABLE_PRE_READ_MASK = 0x01 << FLASH_SMWR_OPTION_2_DISABLE_PRE_READ_OFFSET
};

/** Flash SMWR_OPTION_3 Register offsets */
enum
{
    FLASH_SMWR_OPTION_3_HEM_WHV_COUNTER_OFFSET  = 0,
    FLASH_SMWR_OPTION_3_HEM_MAX_ERASE_OFFSET    = 8,
};

/** Flash SMWR_OPTION_3 Register masks */
enum
{
    FLASH_SMWR_OPTION_3_HEM_WHV_COUNTER_MASK  = 0x0FF << FLASH_SMWR_OPTION_3_HEM_WHV_COUNTER_OFFSET,
    FLASH_SMWR_OPTION_3_HEM_MAX_ERASE_MASK    = 0x01FF << FLASH_SMWR_OPTION_3_HEM_MAX_ERASE_OFFSET,
};

/** Flash Command Register Flags */
typedef enum
{
    FLASH_COMMAND_MASK                              = 0x0000003F, /*!< Command code mask                                */
    FLASH_COMMAND_NOP                               = 0,          /*!< No operation                                     */
    FLASH_COMMAND_WRITE_SECTOR                      = 1,          /*!< Write Sector command                             */
    FLASH_COMMAND_WRITE_QWORD                       = 2,          /*!< Write Quad-Word from Sector Buffer command       */
    FLASH_COMMAND_WRITE_IMMEDIATE                   = 3,          /*!< Write Quad-Word from Data Registers command      */
    FLASH_COMMAND_ERASE_PAGE                        = 4,          /*!< Erase Page command                               */
    FLASH_COMMAND_ERASE_ALL                         = 5,          /*!< Erase All command                                */
    FLASH_COMMAND_CLR_SECTOR_BUFFER                 = 6,          /*!< Clear Sector Buffer command                      */
    FLASH_COMMAND_LOCK_REGION                       = 7,          /*!< Lock Data Region command                         */
    FLASH_COMMAND_LOCK_DEBUGGER_READ                = 8,          /*!< Lock Debugger Memory Read command                */
    FLASH_COMMAND_LOCK_DEBUGGER_ACCESS              = 9,          /*!< Lock Debugger Access command                     */
    FLASH_COMMAND_WRITE_FACTORY_ROW_SECTOR          = 10,         /*!< Write Factory Row Data Sector command            */
    FLASH_COMMAND_WRITE_FACTORY_ROW_QWORD           = 11,         /*!< Write Factory Row Data Quad-Word command         */
    FLASH_COMMAND_READ_FACTORY_ROW_QWORD            = 12,         /*!< Read Factory Row Data Quad-Word command          */
    FLASH_COMMAND_ERASE_FACTORY_ROW                 = 13,         /*!< Erase Factory Row command                        */
    FLASH_COMMAND_LOCK_FACTORY_ROW                  = 14,         /*!< Lock Factory Row command                         */
    FLASH_COMMAND_CHIP_ERASE                        = 15,         /*!< Chip Erase command                               */
    FLASH_COMMAND_LOCK_CHIP_ERASE                   = 16,         /*!< Lock access to Chip Erase command                */
    FLASH_COMMAND_WRITE_SECTOR_BUFFER_QWORD         = 17,         /*!< Write Data Quad-Word to Sector Buffer command    */
    FLASH_COMMAND_READ_SECTOR_BUFFER_QWORD          = 18,         /*!< Read Data Quad-Word from Sector Buffer command   */
    FLASH_COMMAND_READ_IFREN_QWORD                  = 19,         /*!< Read IFREN memory data Quad-Word command         */
    FLASH_COMMAND_WRITE_IFREN_QWORD                 = 20,         /*!< Write IFREN memory data Quad-Word command        */
    FLASH_COMMAND_WRITE_IFREN_SECTOR                = 21,         /*!< Write IFREN memory data Sector command           */
    FLASH_COMMAND_ERASE_IFREN_PAGE                  = 22,         /*!< Erase IFREN memory page command                  */
    FLASH_COMMAND_LOCK_DIRECT_IFREN_ACCESS          = 23,         /*!< Lock direct access to IFREN memory space         */
    FLASH_COMMAND_READ_IFREN1_QWORD                 = 24,         /*!< Read IFREN1 memory data Quad-Word command        */
    FLASH_COMMAND_WRITE_IFREN1_QWORD                = 25,         /*!< Write IFREN1 memory data Quad-Word command       */
    FLASH_COMMAND_ERASE_IFREN1_PAGE                 = 26,         /*!< Erase IFREN1 memory page command                 */
    FLASH_COMMAND_LOCK_DIRECT_IFREN1_ACCESS         = 27,         /*!< Lock direct access to IFREN1 memory space        */
    FLASH_COMMAND_READ_REDEN_CONFIG_LATCH           = 28,         /*!< Read REDEN config latch command                  */
    FLASH_COMMAND_WRITE_REDEN_CONFIG_LATCH          = 29,         /*!< Write REDEN config latch command                 */
    FLASH_COMMAND_LOCK_REDEN_CONFIG_LATCH_ACCESS    = 30,         /*!< Lock access to REDEN config latches              */
    FLASH_COMMAND_ERASE_REFERENCE_CELL              = 31,         /*!< Erase Reference Cell command                     */
    FLASH_COMMAND_LOCK_ERASE_REFERENCE_CELL_ACCESS  = 32,         /*!< Lock access to Erase Reference Cell command      */
    FLASH_COMMAND_WRITE_MANUFACTURER_ROW_SECTOR     = 33,         /*!< Write Manufacturer Row Data Sector command       */
    FLASH_COMMAND_WRITE_MANUFACTURER_ROW_QWORD      = 34,         /*!< Write Manufacturer Row Data Quad-Word command    */
    FLASH_COMMAND_READ_MANUFACTURER_ROW_QWORD       = 35,         /*!< Read Manufacturer Row Data Quad-Word command     */
    FLASH_COMMAND_ERASE_MANUFACTURER_ROW            = 36,         /*!< Erase Manufacturer Row command                   */
    FLASH_COMMAND_LOCK_MANUFACTURER_ROW             = 37,         /*!< Lock Manufacturer Row command                    */
    FLASH_COMMAND_WRITE_USER_ROW_SECTOR             = 38,         /*!< Write User Row Data Sector command               */
    FLASH_COMMAND_WRITE_USER_ROW_QWORD              = 39,         /*!< Write User Row Data Quad-Word command            */
    FLASH_COMMAND_READ_USER_ROW_QWORD               = 40,         /*!< Read User Row Data Quad-Word command             */
    FLASH_COMMAND_ERASE_USER_ROW                    = 41,         /*!< Erase User Row command                           */
    FLASH_COMMAND_LOCK_USER_ROW                     = 42,         /*!< Lock User Row command                            */
} amba_flash_command_t;

/** Flash Lock Register Flags */
enum
{
    FLASH_LOCK_ACCESS_PASSWORD                      = 0x554E4C4B,
    FLASH_LOCK_FACTORY_ROW_ACCESS_PASSWORD          = FLASH_LOCK_ACCESS_PASSWORD,
    FLASH_LOCK_USER_ROW_ACCESS_PASSWORD             = FLASH_LOCK_ACCESS_PASSWORD,
    FLASH_LOCK_MANUFACTURER_ROW_ACCESS_PASSWORD     = FLASH_LOCK_ACCESS_PASSWORD,
    FLASH_LOCK_IFREN_ACCESS_PASSWORD                = FLASH_LOCK_ACCESS_PASSWORD,
    FLASH_LOCK_IFREN1_ACCESS_PASSWORD               = FLASH_LOCK_ACCESS_PASSWORD,
    FLASH_LOCK_REDEN_CONFIG_ACCESS_PASSWORD         = FLASH_LOCK_ACCESS_PASSWORD,
    FLASH_LOCK_ERASE_REFERENCE_CELL_ACCESS_PASSWORD = FLASH_LOCK_ACCESS_PASSWORD,
};

/** Flash Interrupt Mask Register Flags */
enum
{
    FLASH_IRQM_READY_IE                     = 0x0001,  /*!< Flash Ready Interrupt Enable                    */
    FLASH_IRQM_PROGRAMMING_ERROR_IE         = 0x0002,  /*!< Flash Programming Error Interrupt Enable        */
    FLASH_IRQM_LOCK_ERROR_IE                = 0x0004,  /*!< Flash Locked Error Interrupt Enable             */
    FLASH_IRQM_ECC_CORRECTABLE_ERROR_IE     = 0x0008,  /*!< Flash Correctable ECC Error Interrupt Enable    */
    FLASH_IRQM_ECC_UNCORRECTABLE_ERROR_IE   = 0x0010,  /*!< Flash Uncorrectable ECC Error Interrupt Enable  */
};

/** Flash Master Locks Register Flags */
enum
{
    FLASH_MASTER_LOCKS_DEBUGGER_READ_DISABLED       = 0x00000001,  /*!< Flash Debugger Read Disabled bit mask               */
    FLASH_MASTER_LOCKS_DEBUGGER_ACCESS_DISABLED     = 0x00000002,  /*!< Flash Debugger Access Disabled bit mask             */
    FLASH_MASTER_LOCKS_FACTORY_ROW_LOCKED           = 0x00000004,  /*!< Flash Factory Row locked bit mask                   */
    FLASH_MASTER_LOCKS_MANUFACTURER_ROW_LOCKED      = 0x00000008,  /*!< Flash Manufacturer Row locked bit mask              */
    FLASH_MASTER_LOCKS_USER_ROW_LOCKED              = 0x00000010,  /*!< Flash User Row locked bit mask                      */
    FLASH_MASTER_LOCKS_ERASE_REFERENCE_CELL_LOCKED  = 0x08000000,  /*!< Flash Erase Reference Cell command locked bit mask  */
    FLASH_MASTER_LOCKS_REDEN_CONFIG_ACCESS_LOCKED   = 0x10000000,  /*!< Flash REDEN config access locked bit mask           */
    FLASH_MASTER_LOCKS_IFREN1_MEMORY_LOCKED         = 0x20000000,  /*!< Flash IFREN memory locked bit mask                  */
    FLASH_MASTER_LOCKS_IFREN_MEMORY_LOCKED          = 0x40000000,  /*!< Flash IFREN memory locked bit mask                  */
    FLASH_MASTER_LOCKS_CHIP_ERASE_LOCKED            = 0x80000000,  /*!< Flash Chip Erase command locked bit mask            */
};

/** Flash Info Register Masks */
enum
{
    FLASH_INFO_SECTOR_SIZE_OFFSET    = 0,                                               /*!< Flash Info Sector Size offset          */
    FLASH_INFO_SECTOR_SIZE_MASK      = 0x0000000F << FLASH_INFO_SECTOR_SIZE_OFFSET,     /*!< Flash Info Sector Size bit mask        */
    FLASH_INFO_PAGE_SIZE_OFFSET      = 4,                                               /*!< Flash Info Page Size offset            */
    FLASH_INFO_PAGE_SIZE_MASK        = 0x0000000F << FLASH_INFO_PAGE_SIZE_OFFSET,       /*!< Flash Info Page Size bit mask          */
    FLASH_INFO_REGION_SIZE_OFFSET    = 8,                                               /*!< Flash Info Region Size in pages offset */
#ifndef BOARD_CCNV2_A1
    FLASH_INFO_REGION_SIZE_MASK      = 0x000000FF << FLASH_INFO_REGION_SIZE_OFFSET,     /*!< Flash Info Region Size bit mask        */
    FLASH_INFO_MODULE_SIZE_OFFSET    = 16,                                              /*!< Flash Info Module Size offset          */
    FLASH_INFO_MODULE_SIZE_MASK      = 0x0000000F << FLASH_INFO_MODULE_SIZE_OFFSET,     /*!< Flash Info Module Size bit mask        */
    FLASH_INFO_MODULES_NUMBER_OFFSET = 20,                                              /*!< Flash Info Modules Number offset       */
    FLASH_INFO_MODULES_NUMBER_MASK   = 0x0000000F << FLASH_INFO_MODULES_NUMBER_OFFSET,  /*!< Flash Info Modules Number bit mask     */
#else
    FLASH_INFO_REGION_SIZE_MASK      = 0x0000000F << FLASH_INFO_REGION_SIZE_OFFSET,     /*!< Flash Info Region Size bit mask        */
    FLASH_INFO_MODULE_SIZE_OFFSET    = 12,                                              /*!< Flash Info Module Size offset          */
    FLASH_INFO_MODULE_SIZE_MASK      = 0x0000000F << FLASH_INFO_MODULE_SIZE_OFFSET,     /*!< Flash Info Module Size bit mask        */
    FLASH_INFO_MODULES_NUMBER_OFFSET = 16,                                              /*!< Flash Info Modules Number offset       */
    FLASH_INFO_MODULES_NUMBER_MASK   = 0x0000000F << FLASH_INFO_MODULES_NUMBER_OFFSET,  /*!< Flash Info Modules Number bit mask     */
#endif
};

/** Flash Info Register Sector Size Flags */
enum
{
    FLASH_INFO_SECTOR_SIZE_UNDEFINED = 0,   /*!< Flash Info Sector Size undefined    */
    FLASH_INFO_SECTOR_SIZE_1024B     = 1,   /*!< Flash Info Sector Size 1024 bytes   */
};

/** Flash Info Register Page Size Flags */
enum
{
    FLASH_INFO_PAGE_SIZE_UNDEFINED = 0,   /*!< Flash Info Page Size undefined    */
    FLASH_INFO_PAGE_SIZE_8_SECTORS = 1,   /*!< Flash Info Page Size 8 Sectors    */
};

/** Flash Info Register Module Size Flags */
enum
{
    FLASH_INFO_MODULE_SIZE_UNDEFINED = 0,  /*!< Flash Info Module Size undefined */
    FLASH_INFO_MODULE_SIZE_128_PAGES = 1,  /*!< Flash Info Module Size 128 pages */
};

/** @} */

#endif /* __CCPROC_AMBA_TSMC40ULPFMC_FLASH_H */
/** @} */
