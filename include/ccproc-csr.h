/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2022-11-24 15:32:16 +0100 (czw, 24 lis 2022) $
* $Revision: 916 $
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
 * @file            ccproc-csr.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Rafal Harabien
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_CSR_H
#define __CCPROC_CSR_H

#include <stddef.h>
#include <stdint.h>

/************************//**
 * @defgroup csr System Controller
 * System Controller registers and definitions
 * @{
 *//************************/

/** System Controller Registers */
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
} csr_regs_t;

static volatile csr_regs_t * const CSR_CTRL_PTR = (csr_regs_t*)CSR_CTRL_BASE;

#define CSR_REMAP_KEY        0x000000A5    /*!< Bootloader Remap Key      */
#define CSR_ROM_UNLOCK_KEY   0xA5000000    /*!< ROM Unlock Key            */
#define CSR_DBG_BAUD_OFFSET ( offsetof(csr_regs_t, DBG_BAUD) )
#define CSR_MEM_REMAP_OFFSET ( offsetof(csr_regs_t, MEM_REMAP) )

/** System Controller Status Register flags */
enum
{
    CSR_STAT_EXC       = 0x0001,     /*!< Exception Support                 */
    CSR_STAT_LLBIT     = 0x0004,     /*!< Load Linked Bit                   */
    CSR_STAT_SPROTEN   = 0x0008,     /*!< Stack Protection Enable           */
    CSR_STAT_IP        = 0x0010,     /*!< Interrupt Pending                 */
    CSR_STAT_DCLS      = 0x0020,     /*!< Dual-core Lockstep Mode           */
    CSR_STAT_MR        = 0x0080,     /*!< Memory Remap                      */
    CSR_STAT_CIEN      = 0x0100,     /*!< Current Interrupt Enable          */
    CSR_STAT_PIEN      = 0x0200,     /*!< Previous Interrupt Enable         */
    CSR_STAT_OIEN      = 0x0400,     /*!< Old Interrupt Enable              */
    CSR_STAT_CMODE     = 0x0800,     /*!< Current Core Mode                 */
    CSR_STAT_PMODE     = 0x1000,     /*!< Previous Core Mode                */
    CSR_STAT_OMODE     = 0x2000,     /*!< Old Core Mode                     */
    CSR_STAT_IRQn      = 0x4000,     /*!< Pending Interrupt Number          */
    CSR_STAT_BD        = 0x80000,    /*!< Branch Delay                      */
    CSR_STAT_BPREDDIS  = 0x800000,   /*!< Dynamic Branch Prediction Disable */
};

/** System Controller Status Register bit offsets */
enum
{
    CSR_STAT_IRQ_NUM_SHIFT = 14, /*!< IRQ Number bitfield offset  */
    CSR_STAT_CORE_ID_SHIFT = 24, /*!< Core ID bitfield offset     */
};

/** System Controller Status Register masks */
enum
{
    CSR_STAT_IRQ_NUM_MASK = 0x0F << CSR_STAT_IRQ_NUM_SHIFT,  /*!< IRQ Number bitmask */
    CSR_STAT_CORE_ID_MASK = 0xFF << CSR_STAT_CORE_ID_SHIFT,  /*!< Core ID bitmask    */
};

/**
 * @name System Controller Status Register macros
 * @{
 */
#define CSR_STATUS_GET_IRQ_NUM(status) ((status & CSR_STAT_IRQ_NUM_MASK) >> CSR_STAT_IRQ_NUM_SHIFT)  /*!< Gets IRQ Number      */
#define CSR_STATUS_GET_CORE_ID(status) ((status & CSR_STAT_CORE_ID_MASK) >> CSR_STAT_CORE_ID_SHIFT)  /*!< Gets Current Core ID */
/** @} */

/** System Controller Exception Cause codes */
enum
{
    CSR_EXC_OVF      = 0x00000001,     /*!< Overflow Exception                         */
    CSR_EXC_LOAD     = 0x00000002,     /*!< Load Exception                             */
    CSR_EXC_STORE    = 0x00000003,     /*!< Store Exception                            */
    CSR_EXC_SYS      = 0x00000004,     /*!< Syscall Exception                          */
    CSR_EXC_BRK      = 0x00000005,     /*!< Break Exception                            */
    CSR_EXC_UNK      = 0x00000006,     /*!< Unknown Exception                          */
    CSR_EXC_ADDR     = 0x00000007,     /*!< Address Exception                          */
    CSR_EXC_PIPE     = 0x00000008,     /*!< Pipeline Error Exception                   */
    CSR_EXC_STACK    = 0x00000009,     /*!< Stack Protection Exception                 */
    CSR_EXC_PRVDATA  = 0x0000000A,     /*!< MPU Data Exception                         */
    CSR_EXC_PRVINST  = 0x0000000B,     /*!< MPU Instruction Exception                  */
    CSR_EXC_TRAP     = 0x0000000C,     /*!< Trap Exception                             */
    CSR_EXC_PERIPH   = 0x0000000D,     /*!< Peripheral Exception                       */
    CSR_EXC_AMBA     = 0x0000000E,     /*!< AMBA Exception                             */
    CSR_EXC_IBUS     = 0x0000000F,     /*!< Instruction Bus Exception                  */
    CSR_EXC_DBUS     = 0x00000010,     /*!< Data Bus Exception                         */
    CSR_EXC_FPU      = 0x00000011,     /*!< Floating Point Unit Exception (deferred)   */

    CSR_EXC_IRQ      = 0x80000000,     /*!< Interrupt Exception                        */

};

/** System Controller CPU Info 0 Register bit offsets */
enum
{
    CPU_IMSIZE_SHIFT  = 0,   /*!< Instruction Memory Size Offset */
    CPU_DMSIZE_SHIFT  = 5,   /*!< Data Memory Size Offset        */
    CPU_ICSIZE_SHIFT  = 11,  /*!< Instruction Cache Size Offset  */
    CPU_SPRSIZE_SHIFT = 18,  /*!< Scratch-Pad RAM Size Offset    */
    CPU_ICWAY_SHIFT   = 29,  /*!< Instruction Cache Ways Offset  */
};

/** System Controller CPU Info 0 Register masks */
enum
{
    CPU_IMSIZE_MASK  = 0x1F << CPU_IMSIZE_SHIFT,   /*!< Instruction Memory Size Mask */
    CPU_DMSIZE_MASK  = 0x1F << CPU_DMSIZE_SHIFT,   /*!< Data Memory Size Mask        */
    CPU_ICSIZE_MASK  = 0x1F << CPU_ICSIZE_SHIFT,   /*!< Instruction Cache Size Mask  */
    CPU_SPRSIZE_MASK = 0x1F << CPU_SPRSIZE_SHIFT,  /*!< Scratch-Pad RAM Size Mask    */
    CPU_ICWAY_MASK   = 0x07 << CPU_ICWAY_SHIFT,    /*!< Instruction Cache Ways Mask  */
};

/** System Controller CPU Info 0 Register bits */
enum
{
    CPU_ICACHE = 1 << 10,  /*!< Instruction Cache       */
    CPU_MCORE  = 1 << 16,  /*!< Multicore Controller    */
    CPU_SPRAM  = 1 << 17,  /*!< Scratch-Pad RAM         */
    CPU_PWD    = 1 << 23,  /*!< Power Management        */
    CPU_CSR    = 1 << 24,  /*!< System Controller       */
    CPU_USER   = 1 << 25,  /*!< User Mode               */
    CPU_MPU    = 1 << 26,  /*!< Memory Protection Unit  */
    CPU_FFT    = 1 << 27,  /*!< FFT Unit                */
    CPU_SPROT  = 1 << 28,  /*!< Stack Protection        */
};

/**
 * @name System Controller CPU Info 0 Register helper macros
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

/** System Controller CPU Info 1 Register bit offsets */
enum
{
    CPU_DCSIZE_SHIFT      = 1,    /*!< Data Cache Size Offset      */
    CPU_DCWAY_SHIFT       = 6,    /*!< Data Cache Ways Offset      */
    CPU_FPU_SHIFT         = 12,   /*!< FPU Offset                  */
    CPU_MUL_SHIFT         = 17,   /*!< Multiplier Offset           */
    CPU_BPRED_SHIFT       = 21,   /*!< Branch Prediction Offset    */
    CPU_GNSS_ISE_SHIFT    = 26,   /*!< GNSS Channels Offset        */
};

/** System Controller CPU Info 1 Register masks */
enum
{
    CPU_DCSIZE_MASK      = 0x1F << CPU_DCSIZE_SHIFT,   /*!< Data Cache Size Mask      */
    CPU_DCWAY_MASK       = 0x07 << CPU_DCWAY_SHIFT,    /*!< Data Cache Ways Mask      */
    CPU_FPU_MASK         = 0x0F << CPU_FPU_SHIFT,      /*!< FPU Mask                  */
    CPU_MUL_MASK         = 0x03 << CPU_MUL_SHIFT,      /*!< Multiplier Mask           */
    CPU_BPRED_MASK       = 0x07 << CPU_BPRED_SHIFT,    /*!< Branch Prediction Mask    */
    CPU_GNSS_ISE_MASK    = 0x3F << CPU_GNSS_ISE_SHIFT, /*!< GNSS Channels Number Mask */
};

/** System Controller CPU Info 1 Register bits */
enum
{
    CPU_DCACHE     = 1 << 0,  /*!< Data Cache                    */
    CPU_MBIST      = 1 << 10, /*!< Memory BIST Controller        */
    CPU_PERFCNT    = 1 << 11, /*!< Performance Counter           */
    CPU_AROPT      = 1 << 16, /*!< Area Optimization             */
    CPU_TECH       = 1 << 19, /*!< Target Technology             */
    CPU_MULFAST    = 1 << 20, /*!< Fast Multiplication           */
    CPU_MI16       = 1 << 24, /*!< Compressed ISA Mode Support   */
    CPU_GNSS       = 1 << 25, /*!< GNSS Controller               */
};

/**
 * @name System Controller CPU Info 1 Register helper macros
 * @{
 */
#define CPU_INFO_GET_DCSIZE_LOG(cpu_info1)   ((cpu_info1 & CPU_DCSIZE_MASK)      >> CPU_DCSIZE_SHIFT)        /*!< Data Cache Size Logarithm  */
#define CPU_INFO_GET_DCWAY(cpu_info1)        ((cpu_info1 & CPU_DCWAY_MASK)       >> CPU_DCWAY_SHIFT)         /*!< Data Cache Ways            */
#define CPU_INFO_GET_DCSIZE(cpu_info1)       (1 << CPU_INFO_GET_DCSIZE_LOG(cpu_info1))                       /*!< Data Cache Size            */
#define CPU_INFO_GET_FPU(cpu_info1)          ((cpu_info1 & CPU_FPU_MASK)         >> CPU_FPU_SHIFT)           /*!< FPU Number                 */
#define CPU_INFO_GET_GNSS_ISE_NUM(cpu_info1) ((cpu_info1 & CPU_GNSS_ISE_MASK)    >> CPU_GNSS_ISE_SHIFT)      /*!< GNSS Channels Number       */
/** @} */

/** System Controller CPU Info 2 Register bits */
enum
{
    CPU_VITERBI = 1 << 8,  /*!< Viterbi Decoder             */
    CPU_XPRAM   = 1 << 9,  /*!< Executable Scratch-Pad RAM  */
};

/** System Controller CPU Info 2 Register bit offsets */
enum
{
    CPU_ARCH_SHIFT        = 0,    /*!< CPU Architecture Offset  */
    CPU_GNSS_BANKS_SHIFT  = 4,    /*!< GNSS Banks Number Offset  */
};

/** System Controller CPU Info 2 Register bit masks */
enum
{
    CPU_ARCH_MASK         = 0x7 << CPU_ARCH_SHIFT,        /*!< GNSS Architecture Mask  */
    CPU_GNSS_BANKS_MASK   = 0xF << CPU_GNSS_BANKS_SHIFT,  /*!< GNSS Banks Number Mask  */
};

/** System Controller CPU Info 2 Register bits */
enum
{
    CPU_DCLS = 1 << 3,  /*!< Dual-core Lockstep Controller       */
};

/** System Controller ROM Unlock Register Flags */
enum
{
    CSR_ROM_UNLOCK = 0x01,  /*!< ROM Unlock Enable bit           */
};

/** Debug prescaler helper macro */
#define DBG_UART_PRES(mantisa, fraction) ((mantisa) | ((fraction) << 16))  /*!< Debug prescaler from mantisa and fraction */

/** @} */

#endif /* __CCPROC_CSR_H */
/** @} */
