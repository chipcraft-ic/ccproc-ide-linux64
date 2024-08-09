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
# File Name : startup.S
# Author    : Rafal Harabien, Krzysztof Marcinek
# ******************************************************************************
# $Date: 2024-02-01 10:30:21 +0100 (czw, 01 lut 2024) $
# $Revision: 1040 $
#H******************************************************************************

# Useful defines:
#
# _STARTUP_STACK_SIZE - size of initial stack
# _STARTUP_STACK_IN_RAM - use RAM instead of SPRAM
# _STARTUP_STACK_IN_RAM_NUM_CORES - maximal number of cores for stack allocation in RAM
#
# _DONT_BREAK_ON_EXCEPTION - do not break on exception
# _DONT_BREAK_ON_BREAK     - do not break on break instruction
#
# _MI16_ENABLE - MI16 ISE defined
#
# _HARD_FLOAT - hard-float defined
#
# _EXEC_TIMEOUT - define execution timeout using watchdog
#

#include <specialreg.h>

#ifdef _NO_SPRAM_MEMORY
  #define _STARTUP_STACK_IN_RAM
  #define _STARTUP_STACK_IN_RAM_NUM_CORES _CPU_NUM_CORES
  #ifndef _CPU_NUM_CORES
    #error _CPU_NUM_CORES not defined
  #endif
#endif

#ifndef _STARTUP_STACK_SIZE
  #define _STARTUP_STACK_SIZE 2048
  #ifdef _STARTUP_STACK_IN_RAM
    #warning _STARTUP_STACK_SIZE set to 2048
  #endif
#endif
#ifndef _STARTUP_STACK_IN_RAM_NUM_CORES
  #define _STARTUP_STACK_IN_RAM_NUM_CORES 1
  #ifdef _STARTUP_STACK_IN_RAM
    #error _STARTUP_STACK_IN_RAM_NUM_CORES not defined
  #endif
#endif


.section .boot, "ax", @progbits

.set noat
.set noreorder


.global __start
__start:
  j start                               # start code
  nop                                   # delay slot

file_meta:
  nop
  nop
file_size:
  nop                                   # updated by programming tool
file_crc:
  nop                                   # updated by programming tool

.global end_loop
end_loop:
  syscall SYSCALL_EXIT                  # simulation exit
  nop
end_jump:
  j end_jump
  nop

interrupt:
  j interrupt_handler
  nop
syscall:
  j syscall_handler
  nop
exception:
  j exception_handler
  nop

.global start
start:
  nop                                   # feed pipeline with nops (for x-prop ASIC simulation)
  nop
  nop
  nop
  jal common_start                      # common start
  nop                                   # delay slot
  j program                             # jump to rest of code
  nop                                   # delay slot

# Start used for main and additional cores
.global common_start
common_start:
  #break 0, BREAK_CODE
  or $at, $zero, $zero                  # clear register file
  or $v0, $zero, $zero
  or $v1, $zero, $zero
  or $a0, $zero, $zero
  or $a1, $zero, $zero
  or $a2, $zero, $zero
  or $a3, $zero, $zero
  or $t0, $zero, $zero
  or $t1, $zero, $zero
  or $t2, $zero, $zero
  or $t3, $zero, $zero
  or $t4, $zero, $zero
  or $t5, $zero, $zero
  or $t6, $zero, $zero
  or $t7, $zero, $zero
  or $s0, $zero, $zero
  or $s1, $zero, $zero
  or $s2, $zero, $zero
  or $s3, $zero, $zero
  or $s4, $zero, $zero
  or $s5, $zero, $zero
  or $s6, $zero, $zero
  or $s7, $zero, $zero
  or $t8, $zero, $zero
  or $t9, $zero, $zero
  or $k0, $zero, $zero
  or $k1, $zero, $zero
  or $gp, $zero, $zero
  or $sp, $zero, $zero
  or $fp, $zero, $zero
  #or $ra, $zero, $zero                 # saved in jal instruction

cache_init:
  lui $t0, CACHE_CTRL_BASE              # Cache Controller address
  or $t1, $zero, CACHE_SC_MASK          # cache scrambling enable mask
  sw $t1, ICACHE_STCR_OFFSET($t0)       # enable instruction cache scrambling
  sw $t1, DCACHE_STCR_OFFSET($t0)       # enable data cache scrambling
  sw $zero, ICACHE_FLUSH_OFFSET($t0)    # flush instruction cache
  sw $zero, DCACHE_FLUSH_OFFSET($t0)    # flush data cache
  or $t1, $zero, CACHE_EN_MASK          # cache enable mask
  or $t1, $t1, CACHE_FT_MASK            # cache parity/ecc enable mask
  or $t1, $t1, CACHE_HE_MASK            # cache hard error enable mask
  sw $t1, ICACHE_STCR_OFFSET($t0)       # enable instruction cache
  sw $t1, DCACHE_STCR_OFFSET($t0)       # enable data cache
  la $gp, _gp                           # init global pointer
  lui $t3, CSR_CTRL_BASE                # System Controller base address
#ifdef _STARTUP_STACK_IN_RAM
  mfc0 $t1, C0_STATUS                   # read STATUS register
  srl $t1, CORE_ID_SHIFT                # get core ID field
  add $t1, 1                            # increment $t1
  li $t2, _STARTUP_STACK_SIZE
  mul $t1, $t2, $t1                     # multiply stack size and (coreID + 1)
  la $sp, _stack_begin                  # init stack pointer
  add $sp, $t1                          # add dynamic offset based on coreID
  sub $t1, $sp, $t2                     # subtract stack size
  sw $t1, SPROT_MIN_OFFSET($t3)         # set stack pointer min. value
#else
  la $sp, _stack_end                    # init stack pointer
  la $t2, _stack_begin                  # init stack pointer
  sw $t2, SPROT_MIN_OFFSET($t3)         # set stack pointer min. value
#endif
  addi $t1, $sp, -4                     # decrement $t1
  sw $t1, SPROT_MAX_OFFSET($t3)         # set stack pointer max. value
  addi $t2, $zero, 1                    # load 1
  sw $t2, IRQ_MASK_OFFSET($t3)          # unmask exceptions
  mfc0 $t1, C0_STATUS                   # read STATUS register
  ori $t1, $t1, SPROT_EN_MASK           # enable stack protection
  ori $t1, $t1, IRQ_EN_MASK             # enable interrupts
  mtc0 $t1, C0_STATUS                   # write STATUS register

#ifdef _MI16_ENABLE
check_mips16:
  lui $s0, CSR_CTRL_BASE                # System Controller base address
  lw $s1, CPU_INFO1_OFFSET($s0)         # CPU features register
  lui $t0, MIPS16_EN_MASK
  and $t0, $t0, $s1                     # check if MIPS16 exists
  beq $t0, $zero, no_mips16
  nop
#endif

#ifdef _HARD_FLOAT
check_hardfloat:
  lui $s0, CSR_CTRL_BASE                # Sysem Controller base address
  lw $s1, CPU_INFO1_OFFSET($s0)         # CPU features register
  srl $s1, $s1, FPU_SHIFT               # shift to get FPU field
  ori $t0, $zero, FPU_MASK              # load FPU mask
  and $t0, $s1, $t0                     # check if FPU exists
  beq $t0, $zero, no_hardfloat
  nop
#endif

check_spram_size:
  lui $s0, CSR_CTRL_BASE                # System Controller base address
  lw $s1, CPU_INFO0_OFFSET($s0)         # CPU features register
  srl $t0, $s1, SPRAM_SIZE_SHIFT
  and $t0, SPRAM_SIZE_MASK              # $t0 = log2(SPRAM size)
  li $s2, 1
  sll $s2, $t0                          # $s2 = SPRAM size
  lui $s3, SPRAM_BASE                   # SPRAM memory base address
  add $s3, $s2                          # $s3 = SPRAM memory end
  la $t1, _espram_bss                   # SPRAM BSS section end address
  sub $t1, $s3, $t1                     # compare to end of physical SPRAM
  blt $t1, $zero, no_mem                # branch if there is not enough SPRAM memory
  nop

init_spram_data:
  la $t0, _sspram_data                  # data section start address
  la $t1, _espram_data                  # data section end address
  la $t2, _spram_data_load              # address of data in ROM memory
  beq $t0, $t1, init_spram_bss          # check if data section is empty
  sub $t1, 4                            # last valid address
copy_spram_data:
  lw $t3, 0($t2)                        # copy word from ROM memory
  add $t2, 4                            # increment source ptr
  sw $t3, 0($t0)                        # save word in SPRAM memory
  sub $t4, $t1, $t0                     # last ptr - cur ptr
  bgt $t4, $zero, copy_spram_data       # loop
  add $t0, 4                            # increment destination ptr
init_spram_bss:
  la $t0, _sspram_bss                   # SPRAM BSS section start address
  la $t1, _espram_bss                   # SPRAM BSS section end address
  beq $t0, $t1, common_done             # check if SPRAM BSS section is empty
  sub $t1, 4                            # last valid address
zero_spram_bss:
  sw $zero, 0($t0)                      # zero word in SPRAM BSS
  sub $t4, $t1, $t0                     # last ptr - cur ptr
  bgt $t4, $zero, zero_spram_bss        # loop
  add $t0, 4                            # increment pointer
common_done:
  jr $ra                                # return
  nop

program:

  lui $s0, CSR_CTRL_BASE                # System Controller base address
  lw $s1, CPU_INFO0_OFFSET($s0)         # CPU features register
  srl $t0, $s1, RAM_SIZE_SHIFT
  and $t0, RAM_SIZE_MASK                # $t0 = log2(RAM size)
  li $s2, 1
  sll $s2, $t0                          # $s2 = RAM size
  lui $s3, RAM_BASE                     # RAM memory base address
  add $s3, $s2                          # $s3 = RAM memory end

  srl $t1, $s1, ROM_SIZE_SHIFT
  and $t1, ROM_SIZE_MASK                # $t1 = log2(ROM size)
  li $s2, 1
  sll $s2, $t1                          # $s2 = ROM size
  lui $s1, ROM_BASE                     # RAM memory base address
  add $s2, $s1, $s2                     # $s2 = ROM memory end

check_ram_memory_size:
  la $t2, _sheap                        # start of unused RAM
  sub $t2, $s3, $t2                     # compare to end of physical RAM
  beq $t0, $zero, check_rom_memory_size # no on-chip memory, proceeed
  nop
  blt $t2, $zero, no_mem                # branch if there is not enough RAM memory
  nop

check_rom_memory_size:
  la $t2, _sdata                        # data section start address
  la $t0, _edata                        # data section end address
  sub $t2, $t0, $t2                     # size of data section
  la $t0, _data_load                    # address of data in ROM memory
  add $t2, $t2, $t0                     # end of data section in ROM
  sub $t2, $s2, $t2                     # compare to end of physical ROM
  beq $t1, $zero, init_data             # no on-chip memory, proceeed
  nop
  blt $t2, $zero, no_mem                # branch if there is not enough ROM memory
  nop

init_data:
  la $t0, _sdata                        # data section start address
  la $t1, _edata                        # data section end address
  la $t2, _data_load                    # address of data in ROM memory
  beq $t0, $t1, init_bss                # check if data section is empty
  sub $t1, 4                            # last valid address
copy_data:
  lw $t3, 0($t2)                        # copy word from ROM memory
  add $t2, 4                            # increment source ptr
  sw $t3, 0($t0)                        # save word in RAM memory
  sub $t4, $t1, $t0                     # last ptr - cur ptr
  bgt $t4, $zero, copy_data             # loop
  add $t0, 4                            # increment destination ptr

init_bss:
  la $t0, _sbss                         # BSS section start address
  la $t1, _ebss                         # BSS section end address
  beq $t0, $t1, done                    # check if BSS section is empty
  sub $t1, 4                            # last valid address
zero_bss:
  sw $zero, 0($t0)                      # zero word in BSS
  sub $t4, $t1, $t0                     # last ptr - cur ptr
  bgt $t4, $zero, zero_bss              # loop
  add $t0, 4                            # increment pointer

done:
  add $sp, -16                          # call arguments area

#ifdef _EXEC_TIMEOUT

  lui $t0, PWD_CTRL_BASE                # load power management controller base address
  lw $t1, RST_RSN_OFFSET($t0)           # read reset reason
  ori $t2, $zero, WDT_RESET_MASK        # load watchdog reset mask
  beq $t1, $t2, end_loop                # end simulation if watchdog reset
  nop

  lui $t0, AMBA_BASE                    # load amba base address
  lw $t1, AMBA_INFO0_OFFSET($t0)        # load AMBA_INFO_0
  lui $t2, WDT_MASK                     # load watchdog mask
  and $t1, $t1, $t2                     # check is watchdog is present
  beq $zero, $t1, end_loop              # end simulation if no watchdog
  nop
  ori $t0, $t0, WDT_ADDRESS             # load watchdog address
  ori $t1, $zero, WDT_UNLOCK_MASK       # load unlock mask
  ori $t2, $zero, _EXEC_TIMEOUT         # load period
  ori $t3, $zero, WDT_ENABLE_MASK       # load enable mask
wdt_pres:
  li $t5, 512                           # load prescaler value
  sw $t1, WDT_UNLOCK_OFFSET($t0)        # unlok registers
  sw $t5, WDT_PRES_OFFSET($t0)          # store period
  lw $t4, WDT_PRES_OFFSET($t0)          # load period
  bne $t5, $t4, wdt_pres                # check if prescaler stored
  nop
wdt_period:
  sw $t1, WDT_UNLOCK_OFFSET($t0)        # unlok registers
  sw $t2, WDT_PERIOD_OFFSET($t0)        # store period
  lw $t4, WDT_PERIOD_OFFSET($t0)        # load period
  bne $t2, $t4, wdt_period              # check if period stored
  nop
wdt_enable:
  sw $t1, WDT_UNLOCK_OFFSET($t0)        # unlok registers
  sw $t3, WDT_CTRL_OFFSET($t0)          # enable watchdog
  lw $t4, WDT_CTRL_OFFSET($t0)          # load control
  bne $t3, $t4, wdt_enable              # check if watchdog enabled
  nop

#endif

  jal board_init                        # board specific initialization
  nop
  jal __libc_init_array                 # init libc
  nop
  jal _ccsdk_init
  nop
#ifdef _NO_SPRAM_MEMORY
  jal __libc_impure_alloc               # allocate impure data
  nop
  jal __libc_impure_init                # initialize impure data
  nop
#endif
  jal main
  nop
  j end_loop                            # jump to end_loop
  nop

#ifdef _MI16_ENABLE
no_mips16:                              # no MIPS16 loop
#ifdef _EXEC_TIMEOUT
  j end_loop
#else
  break 0, BREAK_CODE
  j end_loop
#endif
  nop
#endif

#ifdef _HARD_FLOAT
no_hardfloat:                           # no FPU loop
#ifdef _EXEC_TIMEOUT
  j end_loop
#else
#ifndef _DONT_BREAK_ON_EXCEPTION
  break 0, BREAK_CODE
#else
  j end_loop
  nop
#endif
  j no_hardfloat
#endif
  nop
#endif

no_mem:                                 # no mem loop
#ifdef _EXEC_TIMEOUT
  j end_loop
#else
  break 0, BREAK_CODE
  j no_mem
#endif
  nop

.weak syscall_handler
syscall_handler:
  mfc0 $k1, C0_EPC                      # get Return Address
#ifndef _DONT_BREAK_ON_BREAK
  break 0, BREAK_CODE                   # break to debug mode
#endif
  add $k1, 4                            # go to next instruction
  jr $k1
  rfe

.weak exception_handler
exception_handler:
#ifndef _DONT_BREAK_ON_EXCEPTION
  break 0, BREAK_CODE                   # break to debug mode
#endif

  nop                                   # dummy insctructions for lockstep operation
  nop                                   # in corner case where exception occures
  nop                                   # immediately after previous one
  nop                                   # because of presence of signature buffer
  nop                                   # slave core can still be acknowledging
  nop                                   # previous exception while master core
  nop                                   # the current one
  nop                                   # because of that the number of instructions
  nop                                   # in exception handler should be greater
  nop                                   # than the signature buffer

  mfc0 $k1, C0_EPC                      # get Return Address
  add $k1, 4                            # go to next instruction
  jr $k1
  rfe

.weak interrupt_handler
interrupt_handler:
  # Note: interrups are disabled here
  #break 0, BREAK_CODE

int_enter:
  add $sp, -80-16-16                    # alloc stack
  sw $at, 32+0($sp)                     # save $at on stack
  mfc0 $k1, C0_EPC                      # read RET_PC register
  sw $k1, 16($sp)                       # save RET_PC on stack
  mfc0 $k1, C0_STATUS                   # read STATUS register
  sw $k1, 24($sp)                       # save STATUS on stack
  ori $k1, IRQ_EN_MASK                  # set IEN flag - enable IRQ preemption
  mtc0 $k1, C0_STATUS                   # write STATUS register

int_enter_stack:
  # Save registers on stack (except $at)
  sw $v0, 32+4($sp)
  sw $v1, 32+8($sp)
  sw $a0, 32+12($sp)
  sw $a1, 32+16($sp)
  sw $a2, 32+20($sp)
  sw $a3, 32+24($sp)
  sw $t0, 32+28($sp)
  sw $t1, 32+32($sp)
  sw $t2, 32+36($sp)
  sw $t3, 32+40($sp)
  sw $t4, 32+44($sp)
  sw $t5, 32+48($sp)
  sw $t6, 32+52($sp)
  sw $t7, 32+56($sp)
  sw $t8, 32+60($sp)
  sw $t9, 32+64($sp)
  sw $ra, 32+68($sp)
  # Registers $sN, $kN, $gp, $sp, $fp don't need saving
  mflo $t0
  sw $t0, 32+72($sp)                    # save LO register
  mfhi $t0
  sw $t0, 32+76($sp)                    # save HI register

int_enter_rest:
  lw $t0, 24($sp)                       # read saved STATUS register
  srl $a0, $t0, 14-2                    # shift right STATUS register
  and $a0, 0x1F << 2                    # $a0 = IRQ_NUM*4
  la $t0, int_vectors                   # address of IRQ vector table
  add $t0, $a0                          # address of IRQ handler
  lw $t0, ($t0)                         # load IRQ handler address
  la $ra, int_ret                       # set return address for IRQ handler
  jr $t0                                # jump to IRQ handler
  nop                                   # delay slot

int_ret:

int_ret_stack:
  # Restore registers from stack (except $at, $t0, $t1)
  lw $t0, 32+72($sp)
  mtlo $t0                              # restore LO register
  lw $t0, 32+76($sp)
  mthi $t0                              # restore HI register
  lw $v0, 32+4($sp)
  lw $v1, 32+8($sp)
  lw $a0, 32+12($sp)
  lw $a1, 32+16($sp)
  lw $a2, 32+20($sp)
  lw $a3, 32+24($sp)
  lw $t2, 32+36($sp)
  lw $t3, 32+40($sp)
  lw $t4, 32+44($sp)
  lw $t5, 32+48($sp)
  lw $t6, 32+52($sp)
  lw $t7, 32+56($sp)
  lw $t8, 32+60($sp)
  lw $t9, 32+64($sp)
  lw $ra, 32+68($sp)
  # Registers $sN, $kN, $gp, $sp, $fp don't need restoring

int_ret_rest:
  lw $t1, 24($sp)                       # read STATUS from stack
  mtc0 $t1, C0_STATUS                   # write STATUS register (without IEN flag - interrupts disabled now)
  lw $k1, 16($sp)                       # read RET_PC from stack

  lw $at, 32+0($sp)                     # restore $at
  lw $t0, 32+28($sp)                    # restore $t0
  lw $t1, 32+32($sp)                    # restore $t1
  add $sp, 80+16+16                     # free allocated stack
  jr $k1                                # jump to interrupted code
  rfe                                   # interrupt end

# IRQ Vectors
int_vectors:
  .word dummy_isr
  .word isr1
  .word isr2
  .word isr3
  .word isr4
  .word isr5
  .word isr6
  .word isr7
  .word isr8
  .word isr9
  .word isr10
  .word isr11
  .word isr12
  .word isr13
  .word isr14
  .word isr15

.weak isr1
isr1:
.weak isr2
isr2:
.weak isr3
isr3:
.weak isr4
isr4:
.weak isr5
isr5:
.weak isr6
isr6:
.weak isr7
isr7:
.weak isr8
isr8:
.weak isr9
isr9:
.weak isr10
isr10:
.weak isr11
isr11:
.weak isr12
isr12:
.weak isr13
isr13:
.weak isr14
isr14:
.weak isr15
isr15:
dummy_isr:
  # Dummy ISR
  break 0, BREAK_CODE
  jr $ra
  nop

# Dummy board_init
.weak board_init
board_init:
  jr $ra
  nop

#ifdef _STARTUP_STACK_IN_RAM
.data
#else
.section .spram_bss, "aw", @nobits
#endif
# Stack for startup
.global _stack_begin
.global _stack_end
.align 3 # stack should be double-word aligned
_stack_begin:
#ifdef _STARTUP_STACK_IN_RAM
  .space _STARTUP_STACK_SIZE*_STARTUP_STACK_IN_RAM_NUM_CORES
#else
  .space _STARTUP_STACK_SIZE
#endif
_stack_end:
