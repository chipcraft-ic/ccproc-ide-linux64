#H*****************************************************************************
#
# Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#   - Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#   - Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in
#     the documentation and/or other materials provided with the
#     distribution.
#   - Neither the name of ChipCraft Sp. z o.o. nor the names of its
#     contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
#
# ******************************************************************************
# File Name : specialreg.h
# Author    : Krzysztof Marcinek
# ******************************************************************************
# $Date: 2020-07-13 19:33:44 +0200 (pon, 13 lip 2020) $
# $Revision: 610 $
#H******************************************************************************

#ifndef _SPECIALREG_H_
#define _SPECIALREG_H_

/*
* Coprocessor 0 (system coprocessor) register numbers
*/
#define C0_VADDR                $8          /* virtual address of failing memory access          */
#define C0_STATUS               $12         /* processor status register                         */
#define C0_CAUSE                $13         /* exception cause register                          */
#define C0_EPC                  $14         /* exception PC register                             */

/*
 * Exception codes definitions
 */
#define CSR_EXC_OV              0x00000001   /* Overflow Exception                               */
#define CSR_EXC_LE              0x00000002   /* Load Exception                                   */
#define CSR_EXC_SE              0x00000003   /* Store Exception                                  */
#define CSR_EXC_SYS             0x00000004   /* Syscall Exception                                */
#define CSR_EXC_BRK             0x00000005   /* Break Exception                                  */
#define CSR_EXC_UNK             0x00000006   /* Unknown Exception                                */
#define CSR_EXC_ADD             0x00000007   /* Address Exception                                */
#define CSR_EXC_PIPE            0x00000008   /* Pipeline Error Exception                         */
#define CSR_EXC_SP              0x00000009   /* Stack Protection Exception                       */
#define CSR_EXC_PDATA           0x0000000A   /* Privileged Data Exception                        */
#define CSR_EXC_PINST           0x0000000B   /* Privileged Instruction Exception                 */
#define CSR_EXC_TRAP            0x0000000C   /* Trap Exception                                   */
#define CSR_EXC_PERIPH          0x0000000D   /* Tightly-coupled Peripheral Exception             */
#define CSR_EXC_AMBA            0x0000000E   /* AMBA Peripheral Exception                        */
#define CSR_EXC_IBUS            0x0000000F   /* Instruction Bus Exception                        */
#define CSR_EXC_DBUS            0x00000010   /* Data Bus Exception                               */
#define CSR_EXC_FPU             0x00000011   /* Floating Point Unit Exception (deferred)         */

#define CSR_EXC_IRQ             0x80000000   /* Interrupt Exception                              */

/*
 * BREAK/SYSCALL codes
 */
#define BREAK_CODE              15
#define SYSCALL_EXIT            15
#define SYSCALL_STOP_CORE       15

/*
 * Cache Controller Utils
 */
#define CACHE_CTRL_BASE         0x3007       /* Upper base address of Cache Controller (I&D)     */
#define ICACHE_STAT_OFFSET      0x0000       /* Instruction Cache Controller Status offset       */
#define ICACHE_FLUSH_OFFSET     0x0004       /* Instruction Cache Controller Flush offset        */
#define DCACHE_STAT_OFFSET      0x2000       /* Data Cache Controller Status offset              */
#define DCACHE_FLUSH_OFFSET     0x2004       /* Data Cache Controller Flush offset               */
#define DCACHE_BUSY_MASK        0x0004       /* Data Cache Controller busy bit mask              */

/*
 * Processor Startup Utils
 */
#define PWD_CTRL_BASE           0x3002       /* Upper base address of Power Management           */
#define CSR_CTRL_BASE           0x3003       /* Upper base address of System Controller          */
#define IRQ_MASK_OFFSET         0x00C0       /* Interrupt Mask offset                            */
#define IRQ_EN_MASK             0x0100       /* Interrupt Enable bit mask                        */
#define CSR_BD_MASK_HI          0x8          /* STATUS register branch delay mask slot           */
#define CORE_ID_SHIFT           24           /* STATUS register Core ID field shift              */
#define CPU_INFO0_OFFSET        0x001C       /* CPU Features 0 offset                            */
#define CPU_INFO1_OFFSET        0x0020       /* CPU Features 1 offset                            */
#define CPU_INFO2_OFFSET        0x0024       /* CPU Features 2 offset                            */
#define SPROT_MIN_OFFSET        0x0038       /* Stack Pointer Protection Min. offset             */
#define SPROT_MAX_OFFSET        0x003C       /* Stack Pointer Protection Max. offset             */
#define SPROT_EN_MASK           0x0008       /* Stack Protection Enable bit mask                 */
#define MIPS16_EN_MASK          0x100        /* MIPS16 ISE mask                                  */
#define FPU_MASK                0xF          /* FPU mask                                         */
#define FPU_SHIFT               12           /* FPU shift                                        */
#define ROM_SIZE_SHIFT          0            /* ROM size shift                                   */
#define ROM_SIZE_MASK           0x1F         /* ROM size mask                                    */
#define ROM_BASE                0x0000       /* ROM memory upper base address                    */
#define RAM_SIZE_SHIFT          5            /* RAM size shift                                   */
#define RAM_SIZE_MASK           0x1F         /* RAM size mask                                    */
#define RAM_BASE                0x4000       /* RAM memory upper base address                    */
#define SPRAM_SIZE_SHIFT        18           /* SPRAM size shift                                 */
#define SPRAM_SIZE_MASK         0x1F         /* SPRAM size mask                                  */
#define SPRAM_BASE              0x2000       /* SPRAM memory upper base address                  */
#define AMBA_BASE               0x8000       /* Upper base address of AMBA bus                   */
#define AMBA_INFO0_OFFSET       0x0          /* AMBA_INFO_0 offset                               */
#define WDT_MASK                0x200        /* AMBA_INFO_0 watchdog mask                        */
#define WDT_ADDRESS             0x1500       /* watchdog address on AMBA bus                     */
#define WDT_UNLOCK_MASK         11           /* watchdog unlock mask                             */
#define WDT_ENABLE_MASK         1            /* watchdog enable mask                             */
#define WDT_UNLOCK_OFFSET       0x0          /* watchdog unlock offset                           */
#define WDT_CTRL_OFFSET         0x4          /* watchdog control offset                          */
#define WDT_PERIOD_OFFSET       0xC          /* watchdog period offset                           */
#define WDT_PRES_OFFSET         0x14         /* watchdog prescaler offset                        */
#define WDT_RESET_MASK          0x8          /* watchdog reset mask                              */
#define RST_RSN_OFFSET          0x4          /* power management reset reason offset             */
#define CACHE_EN_MASK           0x1          /* cache enable mask                                */
#define CACHE_FT_MASK           0x8          /* cache parity/ecc enable mask                     */
#define CACHE_SC_MASK           0x20         /* cache scrambling enable mask                     */
#define CACHE_HE_MASK           0x100        /* hard error mask                                  */

#endif /* _SPECIALREG_H_ */
