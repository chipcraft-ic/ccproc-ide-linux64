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
# File Name : isa32.S
# Author    : Krzysztof Marcinek, Rafal Harabien
# ******************************************************************************
# $Date: 2019-10-03 19:22:07 +0200 (czw, 03 paź 2019) $
# $Revision: 474 $
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

.macro expect_exception_begin num, break_code=0
  la $s7, expected_exception
  li $t9, \num
  sw $t9, ($s7)
  la $t8, expected_break_code
  li $t9, \break_code
  sw $t9, ($t8)
  la $t8, exception_ret_addr
  la $t9, 9f # local label
  sw $t9, ($t8)
9: # local label
.endm

.macro expect_exception_end
  lw $t9, ($s7)
  bnez $t9, fail
  nop
.endm

##############
# Entry point
##############

.data

intro_str:
  .asciiz "Starting ISA32 architecture tests...\n"
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

#
# Test .ASCIIZ
#
.data

str0: .asciiz ""
str1: .asciiz "a"
str2: .asciiz "bb"
str3: .asciiz "ccc"
str4: .asciiz "dddd"
str5: .asciiz "eeeee"
str06:  .asciiz "", "a", "bb", "ccc", "dddd", "eeeee"

.text
  test_begin "Testing .asciiz"

  la $a0, str0
  li $a1, 6
  jal ck_strings
  nop

  la $a0, str06
  li $a1, 6
  jal ck_strings
  nop

  j instr_tests
  nop

ck_strings:
  move $s0, $a0
  move $s1, $a1
  move $s2, $zero
  move $s3, $ra

l_asciiz1:
  move $a0, $s0
  jal strlen
  nop

  bne $v0, $s2, fail
  nop
  inc_var g_totalTests

  add $s0, $v0  # skip string
  add $s0, 1    # skip null byte

  # loop for all strings (s1 - count)
  add $s2, 1
  slt $at, $s2, $s1
  bnez $at, l_asciiz1
  nop

  move $ra, $s3
  jal $ra
  nop

#
# Now, test each instruction
#
instr_tests:

unk_test:
  test_begin "Testing unknown instruction"
  expect_exception_begin CSR_EXC_UNK
  .word 1
  expect_exception_end

add_test:
  test_begin "Testing ADD"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  add $a0, $zero, $zero
  bnez $a0, fail
  nop
  inc_var g_totalTests
  add $a0, $zero, $v0
  bne $a0, $v0, fail
  nop
  inc_var g_totalTests
  add $a0, $a0, $v1
  bnez $a0, fail
  nop
  inc_var g_totalTests

  lui $v1, 0x7fff
  ori $v1, $v1, 0xffff
  expect_exception_begin CSR_EXC_OV
  add $v1, $v1, $v0
  expect_exception_end

addi_test:
  test_begin "Testing ADDI"
  li $t0, 0
  li $t1, 1
  addi $t0, $zero, 1
  bne $t0, $t1, fail
  nop
  inc_var g_totalTests

  addi $t1, $t1, -1
  bnez $t1, fail
  nop
  inc_var g_totalTests

  li $t0, 0x80000000
  expect_exception_begin CSR_EXC_OV
  addi $t0, $t0, -10
  expect_exception_end

  test_begin "Testing ADDIU"
  ori $v0, $zero, 1
  lui   $v1, 0x8000
  ori   $v1, 0x0001
  addiu $a0, $zero, 0
  bnez $a0, fail
  nop
  inc_var g_totalTests
  addiu $a0, $zero, 1
  bne $a0, $v0, fail
  nop
  inc_var g_totalTests
  addiu $a0, $a0, -1
  bnez $a0, fail
  nop
  inc_var g_totalTests
  lui   $v0, 0x7fff
  ori   $v0, 0xffff
  addiu $v0, $v0, 2             # should not trap
  bne $v0, $v1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing ADDU"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  lui $a1, 0xffff
  ori $a1, $a1, 0xfffe
  addu $a0, $zero, $zero
  bnez $a0, fail
  nop
  inc_var g_totalTests
  addu $a0, $zero, $v0
  bne $a0, $v0, fail
  nop
  inc_var g_totalTests
  addu $a0, $a0, $v1
  bnez $a0, fail
  nop
  inc_var g_totalTests
  lui   $v0, 0x7fff
  ori   $v0, 0xffff
  addu $v0, $v0, $v0            # should not trap
  bne $v0, $a1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing AND"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  and $a0, $zero, $zero
  bnez $a0, fail
  nop
  inc_var g_totalTests
  and $a0, $v0, $v0
  beqz $a0, fail
  nop
  inc_var g_totalTests
  and $a0, $v0, $v1
  bne $a0, $v0, fail
  nop
  inc_var g_totalTests

  test_begin "Testing ANDI"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  andi $a0, $zero, 0
  bnez $a0, fail
  nop
  inc_var g_totalTests
  and $a0, $v0, 1
  beqz $a0, fail
  nop
  inc_var g_totalTests
.set at
  and $a0, $v0, -1
.set noat
  bne $a0, $v0, fail
  nop
  inc_var g_totalTests
.set at
  and $a0, $v1, -1
.set noat
  bne $a0, $v1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing BEQ"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  beq $zero, $zero, b1
  nop
  j fail
  nop
  inc_var g_totalTests

b1:
  beq $v0, $v0, b2
  nop
  j fail
  nop
  inc_var g_totalTests

b2:
  beq $v1, $v0, fail
  nop
  inc_var g_totalTests
  beq $v0, $v0, far_away        # Check long branch
  nop
  j fail
  nop
  inc_var g_totalTests
  come_back:

  ori $v0, $zero, 3
b2_1:
  subu $v0, $v0, 1
  bnez $v0, b2_1
  nop

  addiu $v0, $zero, 0
  beq $zero, $zero, x020
  addiu $v0, $zero, 1           # Delayed instruction
x020:
  addiu $v1, $zero, 1
  bne $v0, $v1, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  ori $v1, $zero, 1
  ori $a0, $zero, 2
  ori $a1, $zero, 0
  ori $a3, $zero, 5
  beq $v0, $a0, fail
  nop
  inc_var g_totalTests
  beq $v0, $a0, x021
  addu $a1, $zero, 5            # Delay slot
x021:   bne $a1, $a3, fail
  nop
  inc_var g_totalTests

  test_begin "Testing BGEZ"
  ori $v1, $zero, 1
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  bgez $zero, x3
  nop
  j fail
  nop
  inc_var g_totalTests
x3: bgez $v1, x4
  nop
  j fail
  nop
  inc_var g_totalTests
x4: bgez $v0, fail
  nop
  inc_var g_totalTests

  addiu $v0, $zero, 0
  bgez $zero, x030
  addiu $v0, $zero, 1           # Delayed instruction
x030:
  addiu $v1, $zero, 1
  bne $v0, $v1, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  ori $a0, $zero, 2
  ori $a1, $zero, 0
  ori $a3, $zero, 5
  bgez $v1, fail
  nop
  inc_var g_totalTests
  bgez $v0, x031
  addu $a1, $zero, 5            # Delay slot
x031:
  bne $a1, $a3, fail
  nop
  inc_var g_totalTests

  test_begin "Testing BGEZAL"
  ori $v1, $zero, 1
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  bgezal $zero, x5
  nop
  j fail
  nop
  inc_var g_totalTests
  bgezal $v0, fail
  nop
  inc_var g_totalTests
x5: bgezal $v1, x6
  nop
x55:j fail
  nop
  inc_var g_totalTests
x6: la $a0, x55
  or $ra, $ra, $ra
  bne $ra, $a0, fail
  nop
  inc_var g_totalTests

  test_begin "Testing BGTZ"
  ori $v1, $zero, 1
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  bgtz $zero, fail
  nop
  inc_var g_totalTests
x7: bgtz $v1, x8
  nop
  j fail
  nop
  inc_var g_totalTests
x8: bgtz $v0, fail
  nop
  inc_var g_totalTests

  addiu $v0, $zero, 0
  bgtz $zero, x040
  addiu $v0, $zero, 1           # Delayed instruction
  addiu $v0, $zero, 2
x040:   addiu $v1, $zero, 2
  bne $v0, $v1, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  ori $a0, $zero, 2
  ori $a1, $zero, 0
  ori $a3, $zero, 5
  bgtz $v1, fail
  nop
  inc_var g_totalTests
  bgtz $v0, x041
  addu $a1, $zero, 5            # Delay slot
x041:   bne $a1, $a3, fail
  nop
  inc_var g_totalTests

  test_begin "Testing BLEZ"
  ori $v1, $zero, 1
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  blez $zero, x9
  nop
  j fail
  nop
  inc_var g_totalTests
x9:
  blez $v0, x10
  nop
  j fail
  nop
  inc_var g_totalTests
x10:
  blez $v1, fail
  nop
  inc_var g_totalTests

  addiu $v0, $zero, 0
  blez $zero, x050
  addiu $v0, $zero, 1           # Delayed instruction
x050:
  addiu $v1, $zero, 1
  bne $v0, $v1, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  ori $a0, $zero, 2
  ori $a1, $zero, 0
  ori $a3, $zero, 5
  blez $v0, fail
  nop
  inc_var g_totalTests
  blez $v1, x051
  addu $a1, $zero, 5            # Delay slot
x051:
  bne $a1, $a3, fail
  nop
  inc_var g_totalTests

  test_begin "Testing BLTZ"
  li $v1, 1
  li $v0, -1
  bltz $zero, fail
  nop
  inc_var g_totalTests
x11:
  bltz $v0, x12
  nop
  j fail
  nop
  inc_var g_totalTests
x12:
  bltz $v1, fail
  nop
  inc_var g_totalTests

  addiu $v0, $zero, 0
  bltz $zero, x060
  addiu $v0, $zero, 1           # Delayed instruction
  addiu $v0, $zero, 2
x060:
  addiu $v1, $zero, 2
  bne $v0, $v1, fail
  nop
  inc_var g_totalTests
  li $v0, 1
  li $v1, -1
  ori $a0, $zero, 2
  ori $a1, $zero, 0
  bltz $v0, fail
  nop
  inc_var g_totalTests
  bltz $v1, x061
  addu $a1, $zero, 5            # Delay slot
x061:
  li $a3, 5
  bne $a1, $a3, fail
  nop
  inc_var g_totalTests

  test_begin "Testing BLTZAL"
  ori $v1, $zero, 1
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  bltzal $zero, fail
  nop
  inc_var g_totalTests
  bltzal $v1, fail
  nop
  inc_var g_totalTests
x13:bltzal $v0, x15
  nop
x14:j fail
  nop
  inc_var g_totalTests
x15:lui $a0, %hi(x14)
  ori   $a0, %lo(x14)
  bne $ra, $a0, fail
  nop
  inc_var g_totalTests

  test_begin "Testing BNE"
  ori $v1, $zero, 1
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  bne $zero, $zero, fail
  nop
  inc_var g_totalTests
  bne $v0, $v0, fail
  nop
  inc_var g_totalTests
  bne $v1, $v0, x16
  nop
x16:
  addiu $v0, $zero, 0
  bne $zero, $zero, x070
  addiu $v0, $zero, 1           # Delayed instruction
x070:
  addiu $v1, $zero, 1
  bne $v0, $v1, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  ori $v1, $zero, 1
  ori $a0, $zero, 2
  ori $a1, $zero, 0
  ori $a3, $zero, 5
  bne $v0, $v1, fail
  nop
  inc_var g_totalTests
  bne $v0, $a0, x071
  addu $a1, $zero, 5            # Delay slot
x071:
  bne $a1, $a3, fail
  nop
  inc_var g_totalTests

break_test:
  test_begin "Testing BREAK"
  expect_exception_begin CSR_EXC_BRK, 3
  break 3
  expect_exception_end

  test_begin "Testing DIV"
  ori $v0, $zero, 4
  ori $v1, $zero, 2
  li $a0, -2
.set at
  div $a1, $v0, $v1
.set noat
  bne $a1, $v1, fail # 4/2==2
  nop
  inc_var g_totalTests
  mfhi $a1
  bnez $a1, fail
  nop
  inc_var g_totalTests
.set at
  div $a1, $v0, $a0
.set noat
  bne $a1, $a0, fail
  nop
  inc_var g_totalTests
  mfhi $a1
  bnez $a1, fail
  nop
  inc_var g_totalTests
  lui $v0, 0x8000
  li $a0, -1
.set at
  expect_exception_begin CSR_EXC_TRAP # GAS adds overflow checking code...
  div $a1, $v0, $a0 # Overflows, but should not cause overflow
  expect_exception_end
.set noat
  li $v0, 1
  li $a0, -1
.set at
  div $a1, $v0, $a0
.set noat
  bne $a1, $a0, fail
  nop
  inc_var g_totalTests
  mfhi $a1
  bnez $a1, fail
  nop
  inc_var g_totalTests
  # Expect exception caused by divide by 0
  expect_exception_begin CSR_EXC_TRAP
  div $a1, $v0, $zero
  expect_exception_end

  test_begin "Testing DIVU"
  ori $v0, $zero, 4
  ori $v1, $zero, 2
  lui $a0, 0xffff
  ori $a0, $a0, 0xfffe
.set at
  divu $a1, $v0, $v1
.set noat
  bne $a1, $v1, fail
  nop
  inc_var g_totalTests
  mfhi $a1
  bne $a1, $zero, fail
  nop
  inc_var g_totalTests
.set at
  divu $zero, $v0, $v1
.set noat
  mflo $a1
  bne $a1, $v1, fail
  nop
  inc_var g_totalTests
  mfhi $a1
  bne $a1, $zero, fail
  nop
  inc_var g_totalTests
.set at
  divu $a1, $v0, $a0
.set noat
  bne $a1, $zero, fail
  nop
  inc_var g_totalTests
  mfhi $a1
  bne $a1, $v0, fail
  nop
  inc_var g_totalTests
  lui $v0, 0x8000
  lui $a0, 0xffff
  ori   $a0, $a0, 0xffff
.set at
  divu $a1, $v0, $a0            # Overflows, but should not cause overflow
.set noat
  ori $v0, $zero, 1
  lui $a0, 0xffff
  ori   $a0, $a0, 0xffff
.set at
  divu $a1, $v0, $a0
.set noat
  bne $a1, $zero, fail
  nop
  inc_var g_totalTests
  mfhi $a1
  bne $a1, $v0, fail
  nop
  inc_var g_totalTests
  # Expect exception caused by divide by 0
  expect_exception_begin CSR_EXC_TRAP
  divu $a1, $v0, $zero
  expect_exception_end

  test_begin "Testing J"
  j x17
  nop
  j fail
  nop
  inc_var g_totalTests
x17:
  nop

  test_begin "Testing JAL"
  jal x18
  nop
x19:
  j fail
  nop
  inc_var g_totalTests
x18:
  la $t0, x19
  bne $ra, $t0, fail
  nop
  inc_var g_totalTests

  test_begin "Testing JALR"
  lui   $v0, %hi(x21)
  ori   $v0, %lo(x21)
  jalr $v1, $v0
  nop
x23:
  j x22
  nop
x21:
  lui   $a0, %hi(x23)
  ori   $a0, %lo(x23)
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  jr $v1
  nop

x22:
  lui   $v0, %hi(x21a)
  ori   $v0, %lo(x21a)
  jalr $v0
  nop
x23a:
  j x22a
  nop
x21a:
  lui   $a0, %hi(x23a)
  ori   $a0, %lo(x23a)
  bne $ra, $a0, fail
  nop
  inc_var g_totalTests
  jr $ra
  nop

x22a:
  la $v0, x24
  add $v0, $v0, 2
x24:
  expect_exception_begin CSR_EXC_ADD
  jalr $v1, $v0
  nop
  expect_exception_end

  test_begin "Testing JR"
  la $v0, x25
  jr $v0
  nop
  j fail
  nop
  inc_var g_totalTests
x25:
  la $v0, x27
  add $v0, $v0, 2
x27:
  expect_exception_begin CSR_EXC_ADD
  jr $v0
  nop
  expect_exception_end

.data
  lbd_:   .byte 1, -1, 0, 128
  lbd1_:  .word 0x10325476, 0x98badcfe
.text
  test_begin "Testing LB"
  la $v0, lbd_
  lb $v1, 0($v0)
  addu $a0, $zero, 1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  lb $v1, 1($v0)
  addiu $a0, $zero, -1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  lb $v1, 2($v0)
  addu $zero, $zero, $zero  # Nop
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lb $v1, 3($v0)
  lui $a0, 0xffff
  ori $a0, 0xff80
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  la $t0, lbd1_
  lb $t1, 0($t0)
  addi $a0, $zero, 0x10
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lb $t1, 1($t0)
  addi $a0, $zero, 0x32
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lb $t1, 2($t0)
  addi $a0, $zero, 0x54
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lb $t1, 3($t0)
  addi $a0, $zero, 0x76
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lb $t1, 4($t0)
  lui $a0, 0xffff
  addiu $a0, $zero, 0xff98
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lb $t1, 5($t0)
  lui $a0, 0xffff
  addiu $a0, $zero, 0xffba
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lb $t1, 6($t0)
  lui $a0, 0xffff
  addiu $a0, $zero, 0xffdc
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lb $t1, 7($t0)
  lui $a0, 0xffff
  addiu $a0, $zero, 0xfffe
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests

  #lui $t5, 0x7fff
  #ori $t5, $t5, 0xffff
  #lb $v1, 1000($t5)

  test_begin "Testing LBU"
  # la $v0 lbd_
  lui $v0, %hi(lbd_)
  ori $v0, $v0, %lo(lbd_)
  lbu $v1, 0($v0)
  addi $a0, $zero, 1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  lbu $v1, 1($v0)
  addi $a0, $zero, 0xff
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  lbu $v1, 2($v0)
  addu $zero, $zero, $zero # Nop
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lbu $v1, 3($v0)
  addu $a0, $zero, 128
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  la $t0, lbd1_
  lbu $t1, 0($t0)
  addi $a0, $zero, 0x10
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lbu $t1, 1($t0)
  addi $a0, $zero, 0x32
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lbu $t1, 2($t0)
  addi $a0, $zero, 0x54
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lbu $t1, 3($t0)
  addi $a0, $zero, 0x76
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lbu $t1, 4($t0)
  addi $a0, $zero, 0x98
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lbu $t1, 5($t0)
  addi $a0, $zero, 0xba
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lbu $t1, 6($t0)
  addi $a0, $zero, 0xdc
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  lbu $t1, 7($t0)
  addi $a0, $zero, 0xfe
  bne $t1, $a0, fail
  nop
  inc_var g_totalTests
  #lui $t5, 0x7fff
  #ori $t5, $t5, 0xffff
  #lbu $v1, 1000($t5)

.data
  lhd_: .half 1, -1, 0, 0x8000
.text
  test_begin "Testing LH"
  ori $a1, $zero, 1
  lui $a2, 0xffff
  ori $a2, $a2, 0xffff
  lui $a3, 0xffff
  ori $a3, $a3, 0x8000
  lui $v0, %hi(lhd_)
  ori $v0, $v0, %lo(lhd_)
  lh $v1, 0($v0)
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lh $v1, 2($v0)
  bne $v1, $a2, fail
  nop
  inc_var g_totalTests
  lh $v1, 4($v0)
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lh $v1, 6($v0)
  bne $v1, $a3, fail
  nop
  inc_var g_totalTests
  #lui $t5, 0x7fff
  #ori $t5, $t5, 0xffff
  #lh $v1, 1000($t5)
  lui $t5, 0x0000
  ori $t5, $t5, 0x0000
  expect_exception_begin CSR_EXC_LE
  lh $v1, 1($t5)
  expect_exception_end

  test_begin "Testing LHU"
  ori $a1, $zero, 1
  ori $a2, $zero, 0xffff
  ori $a3, $zero, 0x8000
  lui $v0, %hi(lhd_)
  ori $v0, $v0, %lo(lhd_)
  lhu $v1, 0($v0)
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lhu $v1, 2($v0)
  bne $v1, $a2, fail
  nop
  inc_var g_totalTests
  lhu $v1, 4($v0)
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lhu $v1, 6($v0)
  bne $v1, $a3, fail
  nop
  inc_var g_totalTests
  #lui $t5, 0x7fff
  #ori $t5, $t5, 0xfff0
  #lhu $v1, 1000($t5)
  lui $t5, 0x0000
  ori $t5, $t5, 0x0000
  expect_exception_begin CSR_EXC_LE
  lhu $v1, 1($t5)
  expect_exception_end

#check number of cores
#lui $t0, 0x3001   # MT Controller
#lw  $t1, 4($t0)   # read number of cores
#ori $t2, $zero, 1
#beq $t1, $t2, single_core
#nop

.data
  ll_temp:  .word 10
  ll_dummy00: .word 0
  ll_dummy01: .word 0
  ll_dummy02: .word 0
  ll_dummy03: .word 0
  ll_dummy04: .word 0
  ll_dummy05: .word 0
  ll_dummy06: .word 0
  ll_dummy07: .word 0
  ll_dummy08: .word 0
  ll_dummy09: .word 0
  ll_dummy10: .word 0
  ll_dummy11: .word 0
  ll_dummy12: .word 0
  ll_dummy13: .word 0
  ll_dummy14: .word 0
  ll_dummy15: .word 0
  ll_dummy16: .word 0
  ll_temp2: .word 11
.text
  test_begin "Testing LL/SC"
.set at
  la $t1, ll_temp
  la $t2, ll_temp2

  ll $t0, ($t1)
  bne $t0, 10, fail # check if LL reads properly
  nop
  inc_var g_totalTests
  li $t0, 20
  sc $t0, ($t1)
  bne $t0, 1, fail  # SC should return 1 on success
  nop
  inc_var g_totalTests
  lw $t0, ($t1)
  bne $t0, 20, fail # check if LW reads written value
  nop
  inc_var g_totalTests
  ll $t0, ($t2)
  bne $t0, 11, fail
  nop
  inc_var g_totalTests
  ll $t0, ($t1)    # Twice LL in the row should work
  bne $t0, 20, fail
  nop
  inc_var g_totalTests
  sc $t0, ($t1)
  bne $t0, 1, fail # SC should return 1 on success
  nop
  inc_var g_totalTests
  sc $t0, ($t1)
  bne $t0, 0, fail # SC without LL should fail
  nop
  inc_var g_totalTests

  ll $t0, ($t1)
  sc $t0, ($t2)
  bne $t0, 0, fail # SC with different address works fine
  nop
  inc_var g_totalTests

  ll $t0, ($t1)
  expect_exception_begin CSR_EXC_BRK, 3
  break 3
  expect_exception_end
  la $t1, ll_temp
  li $t0, 30
  sc $t0, ($t1)
  bne $t0, 0, fail # check if RFE causes SC to fail
  nop
  inc_var g_totalTests
  lw $t0, ($t1)
  bne $t0, 20, fail # check if LW reads old value
  nop
  inc_var g_totalTests

  or $t5, $t1, $zero
  expect_exception_begin CSR_EXC_LE
  ll $t0, 1($t5) # LL from unaligned address
  expect_exception_end

  expect_exception_begin CSR_EXC_SE
  sc $t0, 1($t5) # SC from unaligned address
  expect_exception_end

single_core:

.set noat

  test_begin "Testing LUI"
  lui $v0, 0
  bne $v0, $zero, fail
  nop
  inc_var g_totalTests
  lui $v0, 1
  srl $v0, $v0, 16
  addiu $v0, $v0, -1    # Don't do compare directly since it uses LUI
  bne $v0, $zero, fail
  nop
  inc_var g_totalTests
  lui $v0, 1
  andi $v0, $v0, 0xffff
  bne $v0, $zero, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  srl $v0, $v0, 16
  addiu $v0, $v0, 1
  andi $v0, $v0, 0xffff
  bne $v0, $zero, fail
  nop
  inc_var g_totalTests

.data
  lwd_: .word 1, -1, 0, 0x8000000
.text
  test_begin "Testing LW"
  lui $v0, %hi(lwd_)
  ori $v0, %lo(lwd_)
  ori $a1, $zero, 1
  lui $a2, 0xffff
  ori $a2, $a2, 0xffff
  lui $a3, 0x0800
  lw $v1, 0($v0)
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lw $v1, 4($v0)
  bne $v1, $a2, fail
  nop
  inc_var g_totalTests
  lw $v1, 8($v0)
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lw $v1, 12($v0)
  bne $v1, $a3, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 0
  lw $v1, lwd_($v0)
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  addi $v0, $v0, 4
  lw $v1, lwd_($v0)
  bne $v1, $a2, fail
  nop
  inc_var g_totalTests
  addi $v0, $v0, 4
  lw $v1, lwd_($v0)
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  addi $v0, $v0, 4
  lw $v1, lwd_($v0)
  bne $v1, $a3, fail
  nop
  inc_var g_totalTests
  lui $v0, %hi(lwd_)
  ori $v0, %lo(lwd_)
  add $v0, $v0, 12
  lw $v1, -12($v0)
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lw $v1, -8($v0)
  bne $v1, $a2, fail
  nop
  inc_var g_totalTests
  lw $v1, -4($v0)
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lw $v1, 0($v0)
  bne $v1, $a3, fail
  nop
  inc_var g_totalTests
  #lui $t0, 0x7fff
  #ori $t0, $t0, 0xfff0
  #lw $v1, 1000($t0)
  or $t5, $zero, $zero
  expect_exception_begin CSR_EXC_LE
  lw $a0, 1($t5)
  expect_exception_end

  # commented to have the same voliating address - 1($t5)
  #expect_exception_begin CSR_EXC_LE
  #lw $a1, 2($zero)
  #expect_exception_end
  #expect_exception_begin CSR_EXC_LE
  #lw $a2, 3($zero)
  #expect_exception_end

  lui $t5, 0x0FFF
  ori $t5, $t5, 0xEFFF
  expect_exception_begin CSR_EXC_DBUS
  lw $a0, 1($t5)
  expect_exception_end

  test_begin "Testing move to/from HI/LO"
  mthi $zero
  mfhi $v0
  bnez $v0, fail
  nop
  inc_var g_totalTests
  mtlo $zero
  mflo $v0
  bnez $v0, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  mthi $v0
  mfhi $v1
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  mtlo $v0
  mflo $v1
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  mthi $v0
  mfhi $v1
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  mtlo $v0
  mflo $v1
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests

  test_begin "Testing MULT"
  ori $v0, $zero, 1
  ori $a1, $zero, 10
  mult $v0, $zero
  mflo $v1
  bnez $v1, fail
  nop
  inc_var g_totalTests
  mult $v0, $v0
  mflo $v1
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  mult $v0, $a1
  mflo $v1
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  mult $zero, $zero
  mflo $v0
  bnez $v0, fail
  nop
  inc_var g_totalTests
  mfhi $v1
  bnez $v1, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bnez $v1, fail
  nop
  inc_var g_totalTests
  ori $a0, $zero, 1
  mult $a0, $a0
  mflo $v0
  bne $v0, $a0, fail
  nop
  inc_var g_totalTests
  mfhi $v1
  bnez $v1, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  lui $a2, 0xffff
  ori $a2, $a2, 0xffff
  mult $a2, $a2
  mflo $v0
  bne $v0, $a0, fail
  nop
  inc_var g_totalTests
  mfhi $v1
  bnez $v1, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  lui $a0, 0xffff
  ori $a0, $a0, 0xffff
  ori $a1, $zero, 1
  mult $a0, $a1
  mflo $v0
  bne $v0, $a0, fail
  nop
  inc_var g_totalTests
  mfhi $v1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  lui $a0, 0x0001
  mult $a0, $a0
  mflo $v0
  bne $v0, $zero, fail
  nop
  inc_var g_totalTests
  mfhi $v1
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lui $a0, 0x8000
  mult $a0, $a0
  mflo $v0
  bne $v0, $zero, fail
  nop
  inc_var g_totalTests
  lui $a3, 0x4000
  mfhi $v1
  bne $v1, $a3, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests

  test_begin "Testing MULTU"
  multu $zero, $zero
  mfhi $v1
  bnez $v1, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bnez $v1, fail
  nop
  inc_var g_totalTests
  ori $a0,$zero, 1
  multu $a0, $a0
  mfhi $v1
  bnez $v1, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  li $a0, -1
  li $a1, -2
  li $a2, 1
  multu $a0, $a0
  mfhi $v1
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $a2, fail
  nop
  inc_var g_totalTests
  lui $a0, 0xffff
  ori $a0, $a0, 0xffff
  ori $a1, $zero, 0
  multu $a0, $a1
  mfhi $v1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lui $a0, 0xffff
  ori $a0, $a0, 0xffff
  ori $a1, $zero, 1
  multu $a0, $a1
  mfhi $v1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  lui $a0, 1
  multu $a0, $a0
  mfhi $v1
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lui $a0, 0x8000
  lui $a1, 0x4000
  multu $a0, $a0
  mfhi $v1
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lui $v1, 0xcecb
  ori $v1, $v1, 0x8f27
  lui $a0, 0xfd87
  ori $a0, $a0, 0xb5f2
  lui $a1, 0xcccc
  ori $a1, $a1, 0xcccb
  lui $a2, 0x7134
  ori $a2, $a2, 0xe5de
  multu $v1, $a0
  mfhi $v1
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  mflo $v1
  bne $v1, $a2, fail
  nop
  inc_var g_totalTests

  test_begin "Testing NOR"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  lui $a1, 0xffff
  ori $a1, $a1, 0xfffe
  nor $a0, $zero, $zero
  bne $a0, $v1, fail
  nop
  inc_var g_totalTests
  nor $a0, $v0, $v0
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  nor $a0, $v0, $v1
  bne $a0, $zero, fail
  nop
  inc_var g_totalTests

  test_begin "Testing OR"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  or $a0, $zero, $zero
  bne $a0, $zero, fail
  nop
  inc_var g_totalTests
  or $a0, $v0, $v0
  bne $a0, $v0, fail
  nop
  inc_var g_totalTests
  or $a0, $v0, $v1
  bne $a0, $v1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing ORI"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  ori $a1, $zero, 0xffff
  ori $a0, $zero, 0
  bne $a0, $zero, fail
  nop
  inc_var g_totalTests
  ori $a0, $v0, 1
  bne $a0, $v0, fail
  nop
  inc_var g_totalTests
  ori $a0, $v0, 0xffff
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests

.data
.align 2
sbd_:   .byte 0, 0, 0, 0
.text
  test_begin "Testing SB"
  ori $v1, $zero, 1
  lui   $v0, %hi(sbd_)
  ori   $v0, %lo(sbd_)
  lui $a1, 0x100
  sb $v1, 0($v0)
  lw $a0, 0($v0)
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  ori $v1, $zero, 2
  lui $a1, 0x102
  sb $v1, 1($v0)
  lw $a0, 0($v0)
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  ori $v1, $zero, 3
  sb $v1, 2($v0)
  lw $a0, 0($v0)
  ori $a1, $a1, 0x300
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  ori $v1, $zero, 4
  ori $a1, $a1, 0x4
  sb $v1, 3($v0)
  lw $a0, 0($v0)
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  #lui $t5, 0x7fff
  #ori $t5, $t5, 0xffff
  #sb $v1, 1000($t5)

.data
.align 2
shd_:   .byte 0, 0, 0, 0
.text
  test_begin "Testing SH"
  ori $v1, $zero, 1
  lui   $v0, %hi(shd_)
  ori   $v0, %lo(shd_)
  sh $v1, 0($v0)
  lw $a0, 0($v0)
  lui $a1, 0x1
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  ori $v1, $zero, 2
  ori $a1, $a1, 2
  sh $v1, 2($v0)
  lw $a0, 0($v0)
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  #lui $t5, 0x7fff
  #ori $t5, $t5, 0xffff
  #sh $v1, 1000($t5)
  or $t5, $zero, $zero
  expect_exception_begin CSR_EXC_SE
  sh $v1, 1($t5)
  expect_exception_end

  test_begin "Testing SLL"
  ori $v0, $zero, 1
  ori $a1, $zero, 2
  sll $v1, $v0, 0
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  sll $v1, $v0, 1
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lui $a1, 0x1
  sll $v1, $v0, 16
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lui $a1, 0x8000
  sll $v1, $v0, 31
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing SLLV"
  ori $v0, $zero, 1
  ori $a0, $zero, 0
  sllv $v1, $v0, $a0
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  ori $a0, $zero, 1
  ori $a1, $zero, 2
  sllv $v1, $v0, $a0
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  ori $a0, $zero, 16
  lui $a1, 1
  sllv $v1, $v0, $a0
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  ori $a0, $zero, 32
  ori $a1, $zero, 1
  sllv $v1, $v0, $a0
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing SLT"
  slt $v1, $zero, $zero
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  slt $v1, $v0, $zero
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  slt $v1, $zero, $v0
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  ori $a1, $zero, 1
  slt $v1, $v0, $zero
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  slt $v1, $zero, $v0
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  ori $a0, $zero, 1
  slt $v1, $v0, $a0
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests

  test_begin "Testing SLTI"
  slti $v1, $zero, 0
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  slti $v1, $v0, 0
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  slti $v1, $zero, 1
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  ori $a1, $zero, 1
  slti $v1, $v0, 0
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  slti $v1, $zero, -1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  ori $a0, $zero, 1
  slti $v1, $v0, 1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests
  slti $v1, $a0, -1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests

  test_begin "Testing SLTIU"
  sltiu $v1, $zero, 0
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  sltiu $v1, $v0, 0
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  sltiu $v1, $zero, 1
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  sltiu $v1, $v0, 0
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  sltiu $v1, $zero, -1
  ori $a1, $zero, 1
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  ori $a0, $zero, 1
  sltiu $v1, $v0, 1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  sltiu $v1, $a0, -1
  bne $v1, $a0, fail
  nop
  inc_var g_totalTests

  test_begin "Testing SLTU"
  sltu $v1, $zero, $zero
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 1
  sltu $v1, $v0, $zero
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  sltu $v1, $zero, $v0
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  sltu $v1, $v0, $zero
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  ori $a1, $zero, 1
  sltu $v1, $zero, $v0
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lui $v0, 0xffff
  ori $v0, $v0, 0xffff
  ori $a0, $zero, 1
  sltu $v1, $v0, $a0
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests

  test_begin "Testing SRA"
  ori $v0, $zero, 1
  sra $v1, $v0, 0
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  sra $v1, $v0, 1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 0x1000
  ori $a1, $zero, 0x100
  sra $v1, $v0, 4
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lui $v0, 0x8000
  lui $a1, 0xf800
  sra $v1, $v0, 4
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing SRAV"
  ori $v0, $zero, 1
  ori $a0, $zero, 0
  srav $v1, $v0, $a0
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  ori $a0, $zero, 1
  srav $v1, $v0, $a0
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 0x1000
  ori $a0, $zero, 4
  srav $v1, $v0, $a0
  ori $a1, $zero, 0x100
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lui $v0, 0x8000
  ori $a0, $zero, 4
  srav $v1, $v0, $a0
  lui $a1, 0xf800
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing SRL"
  ori $v0, $zero, 1
  srl $v1, $v0, 0
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  srl $v1, $v0, 1
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 0x1000
  srl $v1, $v0, 4
  ori $a1, $zero, 0x100
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lui $v0, 0x8000
  srl $v1, $v0, 4
  lui $a1, 0x0800
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing SRLV"
  ori $v0, $zero, 1
  ori $a0, $zero, 0
  srlv $v1, $v0, $a0
  bne $v1, $v0, fail
  nop
  inc_var g_totalTests
  ori $a0, $zero, 1
  srlv $v1, $v0, $a0
  bne $v1, $zero, fail
  nop
  inc_var g_totalTests
  ori $v0, $zero, 0x1000
  ori $a0, $zero, 4
  srlv $v1, $v0, $a0
  ori $a1, $zero, 0x100
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests
  lui $v0, 0x8000
  ori $a0, $zero, 4
  srlv $v1, $v0, $a0
  lui $a1, 0x0800
  bne $v1, $a1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing SUB"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  sub $a0, $zero, $zero
  bnez $a0, fail
  nop
  inc_var g_totalTests
  sub $a0, $zero, $v0
  bne $a0, $v1, fail
  sub $a0, $v0, $zero
  bne $a0, $v0, fail
  nop
  inc_var g_totalTests
  sub $a0, $v0, $v1
  ori $a1, $zero, 2
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  sub $a0, $v1, $v0
  lui $a1, 0xffff
  ori $a1, $a1, 0xfffe
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  lui $v0, 0x8000
  ori $v1, $zero, 1
  expect_exception_begin CSR_EXC_OV
  sub $a0, $v1, $v0
  expect_exception_end

  test_begin "Testing SUBU"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  subu $a0, $zero, $zero
  bnez $a0, fail
  nop
  inc_var g_totalTests
  subu $a0, $zero, $v0
  bne $a0, $v1, fail
  nop
  inc_var g_totalTests
  subu $a0, $v0, $zero
  bne $a0, $v0, fail
  nop
  inc_var g_totalTests
  subu $a0, $v0, $v1
  ori $a1, $zero, 2
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  subu $a0, $v1, $v0
  lui $a1, 0xffff
  ori $a1, $a1, 0xfffe
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  lui $v0, 0x8000
  ori $v1, $zero, 1
  subu $a0, $v1, $v0

.data
.align 2
swd_:   .byte 0, 0, 0, 0
.text
  test_begin "Testing SW"
  lui $v1, 0x7f7f
  ori $v1, $v1, 0x7f7f
  lui   $v0, %hi(swd_)
  ori   $v0, %lo(swd_)
  sw $v1, 0($v0)
  lw $a0, 0($v0)
  bne $a0, $v1, fail
  nop
  inc_var g_totalTests
  #lui $t4, 0x7fff
  #ori $t4, $t4, 0xffff
  #sw $v1, 1000($t4)
  lui $t5, 0x4000
  expect_exception_begin CSR_EXC_SE
  sw $v1, 1($t5)
  expect_exception_end

  # commented to have the same violating address - 1($t5)
  #expect_exception_begin CSR_EXC_SE
  #sw $v1, 2($t5)
  #expect_exception_end
  #expect_exception_begin CSR_EXC_SE
  #sw $v1, 3($t5)
  #expect_exception_end

syscall_test:
  test_begin "Testing SYSCALL"
  expect_exception_begin CSR_EXC_SYS
  syscall
  expect_exception_end

  test_begin "Testing XOR"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  xor $a0, $zero, $zero
  bne $a0, $zero, fail
  nop
  inc_var g_totalTests
  xor $a0, $v1, $v1
  bne $a0, $zero, fail
  nop
  inc_var g_totalTests
  xor $a0, $v0, $v1
  lui $a1, 0xffff
  ori $a1, $a1, 0xfffe
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing XORI"
  ori $v0, $zero, 1
  lui $v1, 0xffff
  ori $v1, $v1, 0xffff
  xori $a0, $zero, 0
  bne $a0, $zero, fail
  nop
  inc_var g_totalTests
  xori $a0, $v1, 0xffff
  lui $a1, 0xffff
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests
  xori $a0, $v0, 0xffff
  ori $a1, $zero, 0xfffe
  bne $a0, $a1, fail
  nop
  inc_var g_totalTests

  test_begin "Testing IBUS exception"
  lui $t0, 0x0FFF
  expect_exception_begin CSR_EXC_IBUS
  jr $t0
  nop
  expect_exception_end
.ibus_exc_return:

# MIPS II tests

test_begin "Testing TEQ"
  li $t0, 222222
  li $t1, 111111
  teq $t0, $t1
  li $t1, 333333
  teq $t0, $t1
  li $t1, 222222
  expect_exception_begin CSR_EXC_TRAP
  teq $t0, $t1
  expect_exception_end

test_begin "Testing TEQI"
  li $t0, 2222
  teqi $t0, 1111
  teqi $t0, 3333
  expect_exception_begin CSR_EXC_TRAP
  teqi $t0, 2222
  expect_exception_end

test_begin "Testing TGE"
  li $t0, 222222
  li $t1, 333333
  tge $t0, $t1
  li $t1, 111111
  expect_exception_begin CSR_EXC_TRAP
  tge $t0, $t1
  expect_exception_end
  li $t1, 222222
  expect_exception_begin CSR_EXC_TRAP
  tge $t0, $t1
  expect_exception_end

test_begin "Testing TGEI"
  li $t0, 2222
  tgei $t0, 3333
  expect_exception_begin CSR_EXC_TRAP
  tgei $t0, 1111
  expect_exception_end
  expect_exception_begin CSR_EXC_TRAP
  tgei $t0, 2222
  expect_exception_end

test_begin "Testing TLT"
  li $t0, 222222
  li $t1, 222222
  tlt $t0, $t1
  li $t1, 111111
  tlt $t0, $t1
  li $t1, 333333
  expect_exception_begin CSR_EXC_TRAP
  tlt $t0, $t1
  expect_exception_end

test_begin "Testing TLTI"
  li $t0, 2222
  tlti $t0, 2222
  tlti $t0, 1111
  expect_exception_begin CSR_EXC_TRAP
  tlti $t0, 3333
  expect_exception_end

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

  # Check if reason is not 0
  beqz $k0, .invalid_handler
  nop

  j .handler_ok
  nop

  # Invalid handler
.invalid_handler:
  la $a0, invalid_handler_str
  la $a1, current_test_name
  lw $a1, ($a1)
  jal printf
  nop
  j fail
  nop

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
  j fail
  nop

.exc_rsn_ok:
  sub $t1, $k0
  sw $t1, ($t0)

  # load bad address register
  mfc0 $t8, C0_VADDR
  or $t7, $k1, $zero

  # check bad address with ibus exception
  # and return safely
.ibus_check:
  li $t9, CSR_EXC_IBUS
  bne $k0, $t9, .dbus_check
  nop
  bne $k1, $t8, fail
  nop
  j .ibus_exc_return
  rfe

  # check bad address with dbus exception
.dbus_check:
  li $t9, CSR_EXC_DBUS
  or $t7, $t5, $zero
  beq $k0, $t9, .badd_check
  addi $t7, $t7, 1

  # check bad address with load
.load_check:
  li $t9, CSR_EXC_LE
  or $t7, $t5, $zero
  beq $k0, $t9, .badd_check
  addi $t7, $t7, 1

  # check bad address with store
.store_check:
  li $t9, CSR_EXC_SE
  or $t7, $t5, $zero
  beq $k0, $t9, .badd_check
  addi $t7, $t7, 1
  or $t7, $k1, $zero

  # address exception
.addr_check:
  li $t9, CSR_EXC_ADD
  bne $k0, $t9, .badd_check
  nop
  # load jump register instead of expect_ret_addr
  or $t7, $v0, $zero

.badd_check:
  # check if bad address equals expect_ret_addr
  bne $t8, $t7, fail
  nop

.trap_check:
  # Handle trap code
  # Skip address checking and return
  # GAS breaks expected return address with DIV
  li $t9, CSR_EXC_TRAP
  bne $k0, $t9, .break_check
  nop
.trap_exc:
  la $k0, exception_ret_addr
  lw $k0, ($k0)
  addiu $k1, 4
  jr $k1
  rfe

.break_check:
  # Handle break code
  li $t9, CSR_EXC_BRK
  bne $k0, $t9, .exit_exc
  nop
.break_exc:
  lw  $k0, 0($k1)
  sra $k0, $k0, 16
  la $t9, expected_break_code
  lw $t9, ($t9)
  beqz $t9, .exit_exc
  nop
  beq $k0, $t9, .exit_exc
  nop

  # Invalid break code
  la $a0, unexp_break_code_str
  la $a1, current_test_name
  lw $a1, ($a1)
  move $a2, $t9
  move $a3, $k0
  jal printf
  nop
  j fail
  nop

.exit_exc:

  # check branch delay slot bit
  inc_var g_totalTests
  mfc0 $k0, C0_STATUS  # read EXC_STATUS
  lui $a3, CSR_BD_MASK_HI
  and $k0, $k0, $a3
  bne $k0, $zero, fail
  nop

  # check if return address equals expect_ret_addr and return
  la $k0, exception_ret_addr
  lw $k0, ($k0)
  inc_var g_totalTests
  bne $k0, $k1, fail
  addiu $k1, 4
  jr $k1
  rfe

.set reorder

##########
# Strings
##########
.data
unexp_exc_str:
  .asciiz "[!] Unexpected exception in %s: expected reason 0x%x, got 0x%x\n"
unexp_break_code_str:
  .asciiz "[!] Unexpected break in %s: expected code 0x%x, got 0x%x\n"
failed_test_str:
  .asciiz "[!] Failed test: %s! Breaking...\n"
invalid_handler_str:
  .asciiz "[!] Invalid handler called (syscall vs exception) in test %s\n"

#
# Fragment of jump test
#
.text 0x7000
far_away:
  beq $zero, $zero, come_back
  nop
