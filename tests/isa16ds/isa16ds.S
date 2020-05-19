#H*****************************************************************************
#
# Copyright (c) 2018 ChipCraft Sp. z o.o. All rights reserved
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
# File Name : isa16ds.S
# Author    : Krzysztof Marcinek, Rafal Harabien
# ******************************************************************************
# $Date: 2019-08-21 14:53:23 +0200 (śro, 21 sie 2019) $
# $Revision: 445 $
#H******************************************************************************


#include <specialreg.h>

.set noat
.set noreorder

###################
# Global variables
###################

.data

expected_exception:
  .word 0
expected_break_code:
  .word 0
current_test_name:
  .word 0
exception_ret_addr:
  .word 0
g_failedTests:
  .word 0
g_totalTests:
  .word 0

.text

################
# Helper Macros
################

.macro test_begin name
.data
.test_title\@:
  .asciiz "\name"
.text

  li $a0, %hi((.test_title\@))
  sll $a0, $a0, 16
  li $a1, %lo((.test_title\@))
  or $a0, $a1

  li $v0, %hi(current_test_name)
  sll $v0, $v0, 16
  li $v1, %lo(current_test_name)
  or $v0, $v1

  sw $a0, ($v0)

.endm

.macro expect_exception_begin num, break_code=0

  li $a0, %hi(expected_exception)
  sll $a0, $a0, 16
  li $a1, %lo(expected_exception)
  or $a0, $a1

  li $v0, %hi(\num)
  sll $v0, $v0, 16
  li $v1, %lo(\num)
  or $v0, $v1

  sw $v0, ($a0)

  li $a0, %hi(expected_break_code)
  sll $a0, $a0, 16
  li $a1, %lo(expected_break_code)
  or $a0, $a1

  li $v0, %hi(\break_code)
  sll $v0, $v0, 16
  li $v1, %lo(\break_code)
  or $v0, $v1

  sw $v0, ($a0)

  li $a0, %hi(exception_ret_addr)
  sll $a0, $a0, 16
  li $a1, %lo(exception_ret_addr)
  or $a0, $a1

  li $v0, %hi(9f)
  sll $v0, $v0, 16
  li $v1, %lo(9f)
  or $v0, $v1

  sw $v0, ($a0)

9: # local label
.endm

.macro expect_exception_end
  li $a0, %hi(expected_exception)
  sll $a0, $a0, 16
  li $a1, %lo(expected_exception)
  or $a0, $a1

  lw $v0, ($a0)

  bnez $v0, fail

.endm

.macro inc_var var_name
  li $a3, %hi(\var_name)
  sll $a3, $a3, 16
  li $a2, %lo(\var_name)
  or $a3, $a2
  lw $a2, ($a3)
  addiu $a2, 1
  sw $a2, ($a3)
.endm

.macro clear_var var_name
  la $t9, \var_name
  lw $t8, ($t9)
  or $t8, $zero, $zero
  sw $t8, ($t9)
.endm

##############
# Entry point
##############

.data

intro_str:
  .asciiz "Starting ISA16 delay slot exception tests...\n"
noisa16_str:
  .asciiz "\nNo ISA16 found!\n\n"
icache_str:
  .asciiz "No icache test.\n"
dcache_str:
  .asciiz "No dcache test.\n"

.text

.global main
main:

#ifdef NO_ICACHE
  lui $t0, 0x3007   # cache controller base
  lw $t1, 0($t0)    # icache status
  li $t2, 0xfffffffe
  and $t1, $t1, $t2 # disable icache
  sw $t1, 0($t0)
  la $a0, icache_str
  jal printf
  nop
#endif
#ifdef NO_DCACHE
  lui $t0, 0x3007   # cache controller base
  lw $t1, 8192($t0) # dcache status
  li $t2, 0xfffffffe
  and $t1, $t1, $t2 # disable icache
  sw $t1, 8192($t0)
  la $a0, dcache_str
  jal printf
  nop
#endif

  # Enable exceptions
  lui $t0, 0x3003  # IRQ Controller
  lw $t1, 0($t0)   # read STATUS
  or $t1, 0x100    # enable IEN flag
  sw $t1, 0($t0)   # write STATUS
  li $t1, 0x1      # enable IRQ 0 (exceptions)
  sw $t1, 192($t0) # write IRQM_CORE

  #clear vars
  clear_var g_totalTests
  clear_var g_failedTests

  lw $t1, 32($t0)
  sll $t1, 7
  srl $t1, 31

  bne $t1, $0, found_isa16
  nop

  la $a0, noisa16_str
  jal printf
  nop
  j tests_end
  nop

found_isa16:
  la $a0, intro_str
  jal printf
  nop

##############
# TESTS BEGIN
##############

instr_tests:
  jalx  m16code
  nop

.set mips16

m16code:

taken_branch_break_test:
.insn
  test_begin "Testing break exception with taken branch"
  inc_var g_totalTests
  li $a2, 0
  beqz $a2, taken_branch_break_rest
  break 3
taken_branch_break_rest:

ntaken_branch_break_test:
.insn
  test_begin "Testing break exception with non-taken branch"
  inc_var g_totalTests
  expect_exception_begin CSR_EXC_BRK, 3
  beqz $a2, ntaken_branch_break_test
  break 3
  expect_exception_end
ntaken_branch_break_rest:

taken_branch_load_test:
.insn
  test_begin "Testing load exception with taken branch"
  inc_var g_totalTests
  li $a3, 3
  li $a2, 0
  beqz $a2, taken_branch_load_rest
  .set noautoextend
  lw $a2, 0($a3)
  .set autoextend
taken_branch_load_rest:

ntaken_branch_load_test:
.insn
  test_begin "Testing load exception with non-taken branch"
  inc_var g_totalTests
  li $a3, 3
  expect_exception_begin CSR_EXC_LE
  beqz $a2, ntaken_branch_load_test
  .set noautoextend
  lw $a2, 0($a3)
  .set autoextend
  expect_exception_end
ntaken_branch_load_rest:

taken_branch_dbus_test:
.insn
  test_begin "Testing data bus exception with taken branch"
  inc_var g_totalTests
  li $a3, 0x1fff
  sll $a3, $a3, 16
  li $a2, 0
  or $a3, $a2
  beqz $a2, taken_branch_dbus_rest
  .set noautoextend
  lw $a2, 0($a3)
  .set autoextend
taken_branch_dbus_rest:

ntaken_branch_dbus_test:
.insn
  test_begin "Testing data bus exception with non-taken branch"
  inc_var g_totalTests
  li $a3, 0x1fff
  sll $a3, $a3, 16
  li $a2, 0
  or $a3, $a2
  expect_exception_begin CSR_EXC_DBUS
  beqz $a3, ntaken_branch_dbus_rest
  .set noautoextend
  lw $a2, 0($a3)
  .set autoextend
  expect_exception_end
ntaken_branch_dbus_rest:

taken_jump_store_test:
.insn
  test_begin "Testing store exception with taken jump"
  inc_var g_totalTests
  li $a3, 3
  li $a2, %hi(taken_jump_store_rest)
  sll $a2, $a2, 16
  li $v1, %lo(taken_jump_store_rest)
  or $a2, $v1
  expect_exception_begin CSR_EXC_SE
  .set noautoextend
  jalr $a2
  sw $a2, 0($a3)
  .set autoextend
  expect_exception_end
taken_jump_store_rest:

taken_jal_store_test:
.insn
  test_begin "Testing store exception with taken jump and link"
  inc_var g_totalTests
  li $a3, 3
  expect_exception_begin CSR_EXC_SE
  .set noautoextend
  jal taken_jal_store_rest
  sw $a2, 0($a3)
  .set autoextend
  expect_exception_end
.align 2
taken_jal_store_rest:

taken_jump_ibus_test:
.insn
  test_begin "Testing instruction bus exception with taken jump"
  inc_var g_totalTests
  li $a3, 3
  li $a2, 0x1fff
  sll $a2, $a2, 16
  li $v1, 0
  or $a2, $v1
  expect_exception_begin CSR_EXC_IBUS
  .set noautoextend
  jalr $a2
  nop
  .set autoextend
  expect_exception_end
taken_jump_ibus_rest:

############
# TESTS END
############

  jalx tests_end
  nop

.align 4
test_jal_jump_loc:
  li $s0, 1
  jr $ra
  nop

fail:
  jalx mi32fail
  nop

.set nomips16
.align 4

tests_end:
# Done!!!
.data
tests_finished_str:
  .asciiz "\n%d/%d tests succeeded, %d tests failed!\n\n"
.text
  la $a0, tests_finished_str
  la $a3, g_failedTests
  lw $a3, ($a3)
  la $a2, g_totalTests
  lw $a2, ($a2)
  sub $a1, $a2, $a3
  jal printf
  nop
  j end
  nop

# Test failed
mi32fail:
  la $a0, failed_test_str
  la $a1, current_test_name
  lw $a1, ($a1)
  jal printf
  nop
  inc_var g_totalTests
  inc_var g_failedTests
  nop
  j tests_end
  nop

end:
  syscall SYSCALL_EXIT
  j end
  nop

####################
# Exception handler
####################

.global syscall_handler
syscall_handler:
  j .common_handler
  nop

.global exception_handler
exception_handler:
  j .common_handler
  nop

.common_handler:
  mfc0 $k1, C0_EPC    # read RET_PC
  mfc0 $k0, C0_CAUSE  # read EXC_CAUSE
  mfc0 $t7, C0_VADDR  # read_EXC_ADDR

  la $t8, exception_ret_addr
  lw $t8, ($t8)
  addi $t8, 2

.handler_ok:
  # Update expected exception variable
  la $t0, expected_exception
  lw $t1, ($t0)
  beq $k0, $t1, .exc_rsn_ok # check if this is expected exception
  nop

  # Invalid exception
  la $a0, unexp_exc_str
  la $a1, current_test_name
  lw $a1, ($a1)
  move $a2, $t1
  move $a3, $k0
  jal printf
  nop
  j mi32fail
  nop

.exc_rsn_ok:
  sub $t1, $k0
  sw $t1, ($t0)

  # check break exception (test non-taken branch)
.break_check:
  li $t9, CSR_EXC_BRK
  bne $k0, $t9, .no_break_check
  nop
  inc_var g_totalTests
  bne $t8, $k1, mi32fail
  nop
  inc_var g_totalTests
  bne $t8, $t7, mi32fail
  nop
.no_break_check:

  # check load exception (test non-taken branch)
.load_check:
  li $t9, CSR_EXC_LE
  bne $k0, $t9, .no_load_check
  nop
  inc_var g_totalTests
  bne $t8, $k1, mi32fail
  nop
  inc_var g_totalTests
  # compare voliating address
  li $t9, 3
  bne $t9, $t7, mi32fail
  nop
.no_load_check:

  # check dbus exception (test non-taken branch)
.dbus_check:
  li $t9, CSR_EXC_DBUS
  bne $k0, $t9, .no_dbus_check
  nop
  inc_var g_totalTests
  bne $t8, $k1, mi32fail
  nop
  inc_var g_totalTests
  # compare violating address
  li $t9, 0x1fff
  sll $t9, $t9, 16
  li $a2, 0
  or $t9, $a2
  bne $t9, $t7, mi32fail
  nop
.no_dbus_check:

  # check store exception (test taken jump)
.store_check:
  li $t9, CSR_EXC_SE
  bne $k0, $t9, .no_store_check
  nop
  # adjust to incremented t8
  addi $k1, 2
  inc_var g_totalTests
  bne $t8, $k1, mi32fail
  nop
  inc_var g_totalTests
  # compare voliating address
  li $t9, 3
  bne $t9, $t7, mi32fail
  nop
  # check branch delay slot bit
  inc_var g_totalTests
  mfc0 $k0, C0_STATUS  # read EXC_STATUS
  lui $a3, CSR_BD_MASK_HI
  and $k0, $k0, $a3
  beq $k0, $zero, mi32fail
  nop
  j .exit_rfe
  nop
.no_store_check:

  # check ibus exception (test taken jump)
.ibus_check:
  li $t9, CSR_EXC_IBUS
  bne $k0, $t9, .no_ibus_check
  nop
  li $t8, 0x1fff
  sll $t8, $t8, 16
  li $a2, 0
  or $t8, $a2
  # check return address
  inc_var g_totalTests
  bne $t8, $k1, mi32fail
  nop
  # check violating address
  inc_var g_totalTests
  bne $t8, $t7, mi32fail
  nop
  # load return address
  li $t8, %hi(taken_jump_ibus_rest)
  sll $t8, $t8, 16
  li $v1, %lo(taken_jump_ibus_rest)
  or $t8, $v1
  j .exit_exc
  nop
.no_ibus_check:

.exit_exc:

  # check branch delay slot bit
  inc_var g_totalTests
  mfc0 $k0, C0_STATUS  # read EXC_STATUS
  lui $a3, CSR_BD_MASK_HI
  and $k0, $k0, $a3
  bne $k0, $zero, mi32fail
  nop

.exit_rfe:
  # Return to next instruction
  addiu $t8, 2
  jr  $t8
  rfe

.set reorder


##########
# Strings
##########
.data
unexp_exc_str:
  .asciiz "[!] Unexpected exception in %s: expected reason 0x%x, got 0x%x\n"
failed_test_str:
  .asciiz "[!] Failed test: %s! Breaking...\n"
