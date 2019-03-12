/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2019-02-26 16:15:44 +0100 (wto) $
* $Revision: 386 $
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
 * @file            ccproc-irq.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Rafal Harabien
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_IRQ_H
#define __CCPROC_IRQ_H

#include <stdint.h>

/************************//**
 * @defgroup irq Interrupt Controller
 * Interrupt Controller registers and definitions
 * @{
 *//************************/

/** IRQ Controller Registers */
typedef struct
{
    uint32_t STATUS;            /*!< Status Register                        */
    uint32_t RET_PC;            /*!< Return Address                         */
    uint32_t EXC_CAUSE;         /*!< Exception Cause                        */
    uint32_t BAD_ADDR;          /*!< Bad Address Register                   */
    uint32_t LL_ADDR;           /*!< Load Linked Address Register           */
    uint32_t ROM_UNLOCK;        /*!< ROM Unlock Register                    */
    uint32_t IRQ_HIST;          /*!< IRQ History                            */
    uint32_t CPU_INFO_0;        /*!< CPU Features 0                         */
    uint32_t CPU_INFO_1;        /*!< CPU Features 1                         */
    uint32_t CPU_INFO_2;        /*!< CPU Features 2                         */
    uint32_t MEM_REMAP;         /*!< Memory Remap                           */
    uint32_t ICORE_IRQMAP;      /*!< Inter-Core IRQ Mapping                 */
    uint32_t ICORE_IRQTRIG;     /*!< Inter-Core IRQ Trigger                 */
    uint32_t ICORE_IRQF;        /*!< Inter-Core IRQ Flags                   */
    uint32_t SP_MIN;            /*!< Stack Protection Min Value             */
    uint32_t SP_MAX;            /*!< Stack Protection Max Value             */
    uint32_t IRQ_PRIOR[16];     /*!< Interrupt Priority                     */
    uint32_t _reserved[16];
    uint32_t IRQ_MASK;          /*!< Interrupt Mask                         */
    uint32_t CPU_TILE_ID;       /*!< Processor Tile Index                   */
    uint32_t CPU_IDCODE;        /*!< JTAG Format Processor IDCODE           */
    uint32_t DBG_BAUD;          /*!< Debug Baud Rate (mantisa and fraction) */
} irq_regs_t;

static volatile irq_regs_t * const IRQ_CTRL_PTR = (irq_regs_t*)IRQ_CTRL_BASE;

#define IRQ_REMAP_KEY        0x000000A5    /*!< Bootloader Remap Key      */
#define IRQ_ROM_UNLOCK_KEY   0xA5000000    /*!< ROM Unlock Key            */

/** IRQ Controller Status Register flags */
enum
{
    IRQ_STAT_EXC       = 0x0001,     /*!< Exception Support         */
    IRQ_STAT_LLBIT     = 0x0004,     /*!< Load Linked Bit           */
    IRQ_STAT_SPROTEN   = 0x0008,     /*!< Stack Protection Enable   */
    IRQ_STAT_IP        = 0x0010,     /*!< Interrupt Pending         */
    IRQ_STAT_DCLS      = 0x0020,     /*!< Dual-core Lockstep Mode   */
    IRQ_STAT_MR        = 0x0080,     /*!< Memory Remap              */
    IRQ_STAT_CIEN      = 0x0100,     /*!< Current Interrupt Enable  */
    IRQ_STAT_PIEN      = 0x0200,     /*!< Previous Interrupt Enable */
    IRQ_STAT_OIEN      = 0x0400,     /*!< Old Interrupt Enable      */
    IRQ_STAT_CMODE     = 0x0800,     /*!< Current Core Mode         */
    IRQ_STAT_PMODE     = 0x1000,     /*!< Previous Core Mode        */
    IRQ_STAT_OMODE     = 0x2000,     /*!< Old Core Mode             */
    IRQ_STAT_IRQn      = 0x4000,     /*!< Pending Interrupt Number  */
    IRQ_STAT_BD        = 0x80000,    /*!< Branch Delay              */
};

/** IRQ Controller Status Register bit offsets */
enum
{
    IRQ_STAT_IRQ_NUM_SHIFT = 14, /*!< IRQ Number bitfield offset  */
    IRQ_STAT_CORE_ID_SHIFT = 24, /*!< Core ID bitfield offset     */
};

/** IRQ Controller Status Register masks */
enum
{
    IRQ_STAT_IRQ_NUM_MASK = 0x0F << IRQ_STAT_IRQ_NUM_SHIFT,  /*!< IRQ Number bitmask */
    IRQ_STAT_CORE_ID_MASK = 0xFF << IRQ_STAT_CORE_ID_SHIFT,  /*!< Core ID bitmask    */
};

/**
 * @name IRQ Controller Status Register macros
 * @{
 */
#define IRQ_STATUS_GET_IRQ_NUM(status) ((status & IRQ_STAT_IRQ_NUM_MASK) >> IRQ_STAT_IRQ_NUM_SHIFT)  /*!< Gets IRQ Number      */
#define IRQ_STATUS_GET_CORE_ID(status) ((status & IRQ_STAT_CORE_ID_MASK) >> IRQ_STAT_CORE_ID_SHIFT)  /*!< Gets Current Core ID */
/** @} */

/** IRQ Controller Exception Cause codes */
enum
{
    IRQ_EXC_OVF      = 0x00000001,     /*!< Overflow Exception                         */
    IRQ_EXC_LOAD     = 0x00000002,     /*!< Load Exception                             */
    IRQ_EXC_STORE    = 0x00000003,     /*!< Store Exception                            */
    IRQ_EXC_SYS      = 0x00000004,     /*!< Syscall Exception                          */
    IRQ_EXC_BRK      = 0x00000005,     /*!< Break Exception                            */
    IRQ_EXC_UNK      = 0x00000006,     /*!< Unknown Exception                          */
    IRQ_EXC_ADDR     = 0x00000007,     /*!< Address Exception                          */
    IRQ_EXC_PIPE     = 0x00000008,     /*!< Pipeline Error Exception                   */
    IRQ_EXC_STACK    = 0x00000009,     /*!< Stack Protection Exception                 */
    IRQ_EXC_PRVDATA  = 0x0000000A,     /*!< MPU Data Exception                         */
    IRQ_EXC_PRVINST  = 0x0000000B,     /*!< MPU Instruction Exception                  */
    IRQ_EXC_TRAP     = 0x0000000C,     /*!< Trap Exception                             */
    IRQ_EXC_PERIPH   = 0x0000000D,     /*!< Peripheral Exception                       */
    IRQ_EXC_AMBA     = 0x0000000E,     /*!< AMBA Exception                             */
    IRQ_EXC_IBUS     = 0x0000000F,     /*!< Instruction Bus Exception                  */
    IRQ_EXC_DBUS     = 0x00000010,     /*!< Data Bus Exception                         */
    IRQ_EXC_FPU      = 0x00000011,     /*!< Floating Point Unit Exception (deferred)   */

    IRQ_EXC_IRQ      = 0x80000000,     /*!< Interrupt Exception                        */

};

/** IRQ Controller CPU Info 0 Register bit offsets */
enum
{
    CPU_IMSIZE_SHIFT  = 0,   /*!< Instruction Memory Size Offset */
    CPU_DMSIZE_SHIFT  = 5,   /*!< Data Memory Size Offset        */
    CPU_ICSIZE_SHIFT  = 11,  /*!< Instruction Cache Size Offset  */
    CPU_SPRSIZE_SHIFT = 18,  /*!< Scratch-Pad RAM Size Offset    */
    CPU_ICWAY_SHIFT   = 29,  /*!< Instruction Cache Ways Offset  */
};

/** IRQ Controller CPU Info 0 Register masks */
enum
{
    CPU_IMSIZE_MASK  = 0x1F << CPU_IMSIZE_SHIFT,   /*!< Instruction Memory Size Mask */
    CPU_DMSIZE_MASK  = 0x1F << CPU_DMSIZE_SHIFT,   /*!< Data Memory Size Mask        */
    CPU_ICSIZE_MASK  = 0x1F << CPU_ICSIZE_SHIFT,   /*!< Instruction Cache Size Mask  */
    CPU_SPRSIZE_MASK = 0x1F << CPU_SPRSIZE_SHIFT,  /*!< Scratch-Pad RAM Size Mask    */
    CPU_ICWAY_MASK   = 0x03 << CPU_ICWAY_SHIFT,    /*!< Instruction Cache Ways Mask  */
};

/** IRQ Controller CPU Info 0 Register bits */
enum
{
    CPU_ICACHE = 1 << 10,  /*!< Instruction Cache       */
    CPU_MCORE  = 1 << 16,  /*!< Multicore Controller    */
    CPU_SPRAM  = 1 << 17,  /*!< Scratch-Pad RAM         */
    CPU_PWD    = 1 << 23,  /*!< Power Management        */
    CPU_IRQ    = 1 << 24,  /*!< Interrupt Controller    */
    CPU_USER   = 1 << 25,  /*!< User Mode               */
    CPU_MPU    = 1 << 26,  /*!< Memory Protection Unit  */
    CPU_FFT    = 1 << 27,  /*!< FFT Unit                */
    CPU_SPROT  = 1 << 28,  /*!< Stack Protection        */
};

/**
 * @name IRQ Controller CPU Info 0 Register helper macros
 * @{
 */
#define CPU_INFO_GET_IMSIZE_LOG(cpu_info0)   ((cpu_info0 & CPU_IMSIZE_MASK)  >> CPU_IMSIZE_SHIFT)   /*!< Instruction Memory Size Logarithm  */
#define CPU_INFO_GET_DMSIZE_LOG(cpu_info0)   ((cpu_info0 & CPU_DMSIZE_MASK)  >> CPU_DMSIZE_SHIFT)   /*!< Data Memory Size Logarithm         */
#define CPU_INFO_GET_ICSIZE_LOG(cpu_info0)   ((cpu_info0 & CPU_ICSIZE_MASK)  >> CPU_ICSIZE_SHIFT)   /*!< Instruction Cache Size Logarithm   */
#define CPU_INFO_GET_SPRSIZE_LOG(cpu_info0)  ((cpu_info0 & CPU_SPRSIZE_MASK) >> CPU_SPRSIZE_SHIFT)  /*!< Scratch-Pad RAM Size Logarithm     */
#define CPU_INFO_GET_ICWAY(cpu_info0)        ((cpu_info0 & CPU_ICWAY_MASK)   >> CPU_ICWAY_SHIFT)    /*!< Instruction Cache Ways             */
#define CPU_INFO_GET_IMSIZE(cpu_info0)       (1 << CPU_INFO_GET_IMSIZE_LOG(cpu_info0))              /*!< Instruction Memory Size            */
#define CPU_INFO_GET_DMSIZE(cpu_info0)       (1 << CPU_INFO_GET_DMSIZE_LOG(cpu_info0))              /*!< Data Memory Size                   */
#define CPU_INFO_GET_ICSIZE(cpu_info0)       (1 << CPU_INFO_GET_ICSIZE_LOG(cpu_info0))              /*!< Instruction Cache Size             */
#define CPU_INFO_GET_SPRSIZE(cpu_info0)      (1 << CPU_INFO_GET_SPRSIZE_LOG(cpu_info0))             /*!< Scratch-Pad RAM Size               */
/** @} */

/** IRQ Controller CPU Info 1 Register bit offsets */
enum
{
    CPU_DCSIZE_SHIFT      = 1,    /*!< Data Cache Size Offset  */
    CPU_DCWAY_SHIFT       = 6,    /*!< Data Cache Ways Offset  */
    CPU_FPU_SHIFT         = 12,   /*!< FPU Offset              */
    CPU_GNSS_ISE_SHIFT    = 26,   /*!< GNSS Channels Offset    */
};

/** IRQ Controller CPU Info 1 Register masks */
enum
{
    CPU_DCSIZE_MASK      = 0x1F << CPU_DCSIZE_SHIFT,   /*!< Data Cache Size Mask      */
    CPU_DCWAY_MASK       = 0x03 << CPU_DCWAY_SHIFT,    /*!< Data Cache Ways Mask      */
    CPU_FPU_MASK         = 0x0F << CPU_FPU_SHIFT,      /*!< FPU Mask                  */
    CPU_GNSS_ISE_MASK    = 0x3F << CPU_GNSS_ISE_SHIFT, /*!< GNSS Channels Number Mask */
};

/** IRQ Controller CPU Info 1 Register bits */
enum
{
    CPU_DCACHE     = 1 << 0,  /*!< Data Cache                    */
    CPU_MBIST      = 1 << 10, /*!< Memory BIST Controller        */
    CPU_PERFCNT    = 1 << 11, /*!< Performance Counter           */
    CPU_MI16       = 1 << 24, /*!< Compressed ISA Mode Support   */
    CPU_GNSS       = 1 << 25, /*!< GNSS Controller               */
};

/**
 * @name IRQ Controller CPU Info 1 Register helper macros
 * @{
 */
#define CPU_INFO_GET_DCSIZE_LOG(cpu_info1)   ((cpu_info1 & CPU_DCSIZE_MASK)      >> CPU_DCSIZE_SHIFT)        /*!< Data Cache Size Logarithm  */
#define CPU_INFO_GET_DCWAY(cpu_info1)        ((cpu_info1 & CPU_DCWAY_MASK)       >> CPU_DCWAY_SHIFT)         /*!< Data Cache Ways            */
#define CPU_INFO_GET_DCSIZE(cpu_info1)       (1 << CPU_INFO_GET_DCSIZE_LOG(cpu_info1))                       /*!< Data Cache Size            */
#define CPU_INFO_GET_FPU(cpu_info1)          ((cpu_info1 & CPU_FPU_MASK)         >> CPU_FPU_SHIFT)           /*!< FPU Number                 */
#define CPU_INFO_GET_GNSS_ISE_NUM(cpu_info1) ((cpu_info1 & CPU_GNSS_ISE_MASK)    >> CPU_GNSS_ISE_SHIFT)      /*!< GNSS Channels Number       */
/** @} */

/** IRQ Controller ROM Unlock Register Flags */
enum
{
    IRQ_ROM_UNLOCK = 0x01,  /*!< ROM Unlock Enable bit           */
};

/** @} */

#endif /* __CCPROC_IRQ_H */
/** @} */
