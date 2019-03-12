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
# File Name : isa32ds.S
# Author    : Krzysztof Marcinek, Rafal Harabien
# ******************************************************************************
# $Date: 2019-01-30 15:24:26 +0100 (śro) $
# $Revision: 381 $
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
exception_ret_addr:
  .word 0
current_test_name:
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
  la $a0, .test_title\@
  la $t0, current_test_name
  sw $a0, ($t0)
  #jal puts
  #nop
.endm

.macro inc_var var_name
  la $t9, \var_name
  lw $t8, ($t9)
  add $t8, 1
  sw $t8, ($t9)
.endm

.macro clear_var var_name
  la $t9, \var_name
  lw $t8, ($t9)
  or $t8, $zero, $zero
  sw $t8, ($t9)
.endm

.macro exception_common_start test_start
  inc_var g_totalTests
  mfc0 $k0, C0_STATUS # read EXC_STATUS
  lui $a3, IRQ_BD_MASK_HI
  and $k0, $k0, $a3
  beq $k0, $zero, fail
  nop
  inc_var g_totalTests
  la $a3, \test_start
  bne $a3, $k1, fail
  nop
.endm

.macro exception_common_rest test_rest
  la $k1, \test_rest
  j $k1
  rfe
.endm

##############
# Entry point
##############

.data

intro_str:
  .asciiz "Starting ISA32 delay slot exception tests...\n"

.text

.global main
main:
  # Enable exceptions
  lui $t0, 0x3003   # IRQ Controller
  lw $t1, 0($t0)    # read STATUS
  or $t1, 0x100     # enable IEN flag
  sw $t1, 0($t0)    # write STATUS
  li $t1, 0x1       # enable IRQ 0 (exceptions)
  sw $t1, 192($t0)  # write IRQM_CORE

  la $a0, intro_str
  jal printf
  nop

  #clear vars
  clear_var g_totalTests
  clear_var g_failedTests

##############
# TESTS BEGIN
##############

tests_begin:

.text
  test_begin "Testing unknown instruction in delay slot"
  inc_var g_totalTests
.unknown_test:
  j .unknown_rest
  .word 1
.unknown_rest:

  test_begin "Testing overflow exception in delay slot"
  inc_var g_totalTests
  lui $v1, 0x7fff
  ori $v1, $v1, 0xffff
.ovf_test:
  j .ovf_rest
  add $v1, $v1, $v0
.ovf_rest:

  test_begin "Testing break exception in delay slot"
  inc_var g_totalTests
.break_test:
  j .break_rest
  break 3
.break_rest:

  test_begin "Testing load exception in delay slot"
  inc_var g_totalTests
.load_test:
  j .load_rest
  lw $4, 1($0)
.load_rest:

  test_begin "Testing store exception in delay slot"
  inc_var g_totalTests
.store_test:
  j .load_rest
  sw $4, 1($0)
.store_rest:

  test_begin "Testing dbus exception in delay slot"
  inc_var g_totalTests
  lui $t5, 0x1FFF
  ori $t5, $t5, 0xEFFF
.dbus_test:
  j .dbus_rest
  lw $a0, 1($t5)
.dbus_rest:

  test_begin "Testing syscall exception in delay slot"
  inc_var g_totalTests
.sys_test:
  j .sys_rest
  syscall
.sys_rest:

  test_begin "Testing trap exception in delay slot"
  inc_var g_totalTests
.trap_test:
  j .trap_rest
  tne $t8, $zero
.trap_rest:

############
# TESTS END
############

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
fail:
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
end_loop:
  j end_loop
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

.unknown_check:
  li $t9, IRQ_EXC_UNK
  bne $k0, $t9, .no_unknown_check
  nop
  # check unknown exception
  exception_common_start .unknown_test
  exception_common_rest .unknown_rest
.no_unknown_check:

.ovf_check:
  li $t9, IRQ_EXC_OV
  bne $k0, $t9, .no_ovf_check
  nop
  # check overflow exception
  exception_common_start .ovf_test
  exception_common_rest .ovf_rest
.no_ovf_check:

.break_check:
  li $t9, IRQ_EXC_BRK
  bne $k0, $t9, .no_break_check
  nop
  # check break exception
  exception_common_start .break_test
  exception_common_rest .break_rest
.no_break_check:

.load_check:
  li $t9, IRQ_EXC_LE
  bne $k0, $t9, .no_load_check
  nop
  # check load exception
  exception_common_start .load_test
  inc_var g_totalTests
  mfc0 $t8, C0_VADDR
  li $t9, 1
  bne $t8, $t9, fail
  nop
  exception_common_rest .load_rest
.no_load_check:

.store_check:
  li $t9, IRQ_EXC_SE
  bne $k0, $t9, .no_store_check
  nop
  # check break exception
  exception_common_start .store_test
  inc_var g_totalTests
  mfc0 $t8, C0_VADDR
  li $t9, 1
  bne $t8, $t9, fail
  nop
  exception_common_rest .store_rest
.no_store_check:

.dbus_check:
  li $t9, IRQ_EXC_DBUS
  bne $k0, $t9, .no_dbus_check
  nop
  # check data bus exception
  exception_common_start .dbus_test
  inc_var g_totalTests
  mfc0 $t8, C0_VADDR
  li $t9, 0x1ffff000
  bne $t8, $t9, fail
  nop
  exception_common_rest .dbus_rest
.no_dbus_check:

.sys_check:
  li $t9, IRQ_EXC_SYS
  bne $k0, $t9, .no_sys_check
  nop
  # check syscall exception
  exception_common_start .sys_test
  exception_common_rest .sys_rest
.no_sys_check:

.trap_check:
  li $t9, IRQ_EXC_TRAP
  bne $k0, $t9, .no_trap_check
  nop
  # check trap exception
  exception_common_start .trap_test
  exception_common_rest .trap_rest
.no_trap_check:

  # unexpected exception, fail
  j fail

.set reorder

##########
# Strings
##########
.data
failed_test_str:
  .asciiz "[!] Failed test: %s! Breaking...\n"
