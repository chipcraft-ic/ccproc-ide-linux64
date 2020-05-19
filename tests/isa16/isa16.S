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
# File Name : isa16.S
# Author    : Krzysztof Marcinek
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

_lsdata:
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
  .asciiz "Starting ISA16 architecture tests...\n"
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

#
# Now, test each instruction
#
instr_tests:
  jalx  m16code
  nop

.align 4
test_jalx_jump_loc:
  lui $16, 1
  jalx jalx_return
  nop

.set mips16

m16code:
.insn
  test_begin "Testing ADDIU (2-operand)"

  li $s0, 0

  addiu $s0, 16
  cmpi $s0, 16
  btnez fail
  inc_var g_totalTests

  addiu $s0, 256
  cmpi $s0, 272
  btnez fail
  inc_var g_totalTests

test_addiu_3op:
  test_begin "Testing ADDIU (3-operand)"

  li $s0, 0
  li $s1, 0

  addiu $s0, $s1, 16
  cmpi $s0, 16
  btnez fail
  inc_var g_totalTests

  addiu $s1, $s0, 256
  cmpi $s1, 272
  btnez fail
  inc_var g_totalTests

test_addiu_3pc:
  test_begin "Testing ADDIU (3-operand, PC relative)"

  li $s0, 16
  li $s1, 1
  nop

.align 4
test_addiu_3pc1_addr:

  .set noautoextend
  addiu $s0, $pc, 16
  .set autoextend
  jal test_addiu_3pc1

  nop

.align 4
test_addiu_3pc1:
  li $v0, %hi(test_addiu_3pc1)
  sll $v0, $v0, 16
  li $v1, %lo(test_addiu_3pc1)
  or $v0, $v1
  srl $v0, $v0, 1
  sll $v0, $v0, 1

  cmp $s0, $v0
  btnez fail
  inc_var g_totalTests

.align 4
test_addiu_3pc2_addr:
  .set noautoextend
  addiu $s0, $pc, 32
  .set autoextend

.align 4
  li $v0, %hi(test_addiu_3pc2_addr+32)
  sll $v0, $v0, 16
  li $v1, %lo(test_addiu_3pc2_addr+32)
  or $v0, $v1
  srl $v0, $v0, 1
  sll $v0, $v0, 1

  cmp $s0, $v0
  btnez fail
  inc_var g_totalTests

test_addiu_2sp:
  test_begin "Testing ADDIU (2-operand, SP relative)"

  move $a1, $29
  li   $s1, 0
  move $29, $s1

  addiu $sp, 1
  move $s0, $29
  li $s1, 0xFF
  and $s0, $s1
  cmpi $s0, 1
  btnez fail
  inc_var g_totalTests

  addiu $sp, -1

  addiu $sp, 16
  move $s0, $29
  li $s1, 0xFFFF
  and $s0, $s1
  cmpi $s0, 16
  btnez fail
  inc_var g_totalTests

  addiu $sp, -16

  move $29, $a1

test_addiu3sp:
  test_begin "Testing ADDIU (3-operand, SP relative)"

  move $a1, $29
  li   $s1, 0
  move $29, $s1

  addiu $s0, $sp, 1
  li $s1, 0xFF
  and $s0, $s1
  cmpi $s0, 1
  btnez fail
  inc_var g_totalTests

  addiu $s0, $sp, 16
  li $s1, 0xFFFF
  and $s0, $s1
  cmpi $s0, 16
  btnez fail
  inc_var g_totalTests

  move $29, $a1

test_addu:
  test_begin "Testing ADDU"

  li $s0, 10
  li $s1, 12
  addu $s0, $s0, $s1
  cmpi $s0, 22
  btnez fail
  inc_var g_totalTests

test_and:
  test_begin "Testing AND"

  li $s0, 0x31
  li $s1, 0x01
  and $s1, $s0
  cmpi $s1, 0x01
  btnez fail
  inc_var g_totalTests

test_b:
  test_begin "Testing B"

  b test_beqz
  b fail
  nop
  inc_var g_totalTests

test_beqz:
.insn
  test_begin "Testing BEQZ"

  li $s0, 13
  beqz $s0, fail
  inc_var g_totalTests

  li $s0, 0
  beqz $s0, test_bnez
  b fail
  inc_var g_totalTests

test_bnez:
.insn
  test_begin "Testing BNEZ"

  li $s0, 0
  bnez $s0, fail
  inc_var g_totalTests

  li $s0, 26
  bnez $s0, test_break
  b fail
  inc_var g_totalTests

test_break:
.insn
  test_begin "Testing BREAK"

  expect_exception_begin CSR_EXC_BRK, 3
  break 3
  expect_exception_end

test_bteqz:
  test_begin "Testing BTEQZ"

  li $s0, 22
  cmpi $s0, 53
  bteqz fail
  inc_var g_totalTests

  cmpi $s0, 22
  bteqz test_btnez
  b fail
  inc_var g_totalTests

test_btnez:
.insn
  test_begin "Testing BTNEZ"

  li $s0, 56
  cmpi $s0, 56
  btnez fail
  inc_var g_totalTests

  cmpi $s0, 22
  btnez test_cmp
  b fail
  inc_var g_totalTests

test_cmp:
.insn
  test_begin "Testing CMP"

  li $s0, 56
  li $s1, 56
  cmp $s0, $s1
  btnez fail
  inc_var g_totalTests

  li $s1, 22
  cmp $s0, $s1
  bteqz fail
  inc_var g_totalTests

test_cmpi:
  test_begin "Testing CMPI"

  li $s0, 22
  cmpi $s0, 22
  btnez fail
  inc_var g_totalTests

  cmpi $s0, 56
  bteqz fail
  inc_var g_totalTests

test_div:
  test_begin "Testing DIV"

  li $s0, 144
  neg $s0
  li $s1, 12
  div $s0, $s1

  mflo $s0
  li $s1, 12
  neg $s1
  cmp $s0, $s1
  btnez fail
  inc_var g_totalTests

  mfhi $s0
  bnez $s0, fail
  inc_var g_totalTests

  li $s0, 22
  li $s1, 3
  div $s0, $s1

  mflo $s0
  cmpi $s0, 7
  btnez fail
  inc_var g_totalTests

  mfhi $s0
  cmpi $s0, 1
  btnez fail
  inc_var g_totalTests

test_divu:
  test_begin "Testing DIVU"

  li $s0, 144
  li $s1, 12
  divu $s0, $s1

  mflo $s0
  cmpi $s0, 12
  btnez fail
  inc_var g_totalTests

  mfhi $s0
  bnez $s0, fail
  inc_var g_totalTests

  li $s0, 22
  li $s1, 3
  divu $s0, $s1

  mflo $s0
  cmpi $s0, 7
  btnez fail
  inc_var g_totalTests

  mfhi $s0
  cmpi $s0, 1
  btnez fail
  inc_var g_totalTests

test_jal:
  test_begin "Testing JAL"

  li $s0, 0
  jal test_jal_jump_loc
  nop

  beqz $s0, fail
  inc_var g_totalTests

  li $s1, %hi(test_jal_jump_loc)
  sll $s1, $s1, 16
  li $s0, %lo(test_jal_jump_loc)
  or $s1, $s0

  li $s0, 0
  jalr $ra, $s1
  nop

  beqz $s0, fail
  inc_var g_totalTests

  li $s0, 0

.align 4
  jalx test_jalx_jump_loc
  nop

.align 4
jalx_return:

  beqz $s0, fail
  inc_var g_totalTests

test_sblb:
  test_begin "Testing SB/LB"

  li $s1, %hi(_lsdata)
  sll $s1, $s1, 16
  li $v0, %lo(_lsdata)
  or $s1, $v0

  li $v0, 0xFFFF
  sll $v0, $v0, 16
  li $v1, 0xFFAA
  or $v0, $v1

  sb $v0, 2($s1)

  lb $s0, 2($s1)

  cmp $s0, $v0
  btnez fail
  inc_var g_totalTests

test_lbu:
  test_begin "Testing LBU"

  li $s1, %hi(_lsdata)
  sll $s1, $s1, 16
  li $v0, %lo(_lsdata)
  or $s1, $v0

  lbu $s0, 2($s1)
  cmpi $s0, 0xAA
  btnez fail
  inc_var g_totalTests

test_shlh:
  test_begin "Testing SH/LH"

  li $s1, %hi(_lsdata)
  sll $s1, $s1, 16
  li $v0, %lo(_lsdata)
  or $s1, $v0

  li $v0, 0xAA55
  li $v1, 0xFFFF
  sll $v1, 16
  or $v0, $v1

  sh $v0, 2($s1)

  lh $s0, 2($s1)

  cmp $s0, $v0
  btnez fail
  inc_var g_totalTests

  expect_exception_begin CSR_EXC_LE
  lh $s0, 1($s1)
  expect_exception_end
  nop
  expect_exception_begin CSR_EXC_SE
  sh $s1, 1($s1)
  expect_exception_end
  nop

test_lhu:
  test_begin "Testing LHU"

  li $s1, %hi(_lsdata)
  sll $s1, $s1, 16
  li $v0, %lo(_lsdata)
  or $s1, $v0

  lhu $s0, 2($s1)
  cmpi $s0, 0xAA55
  btnez fail
  inc_var g_totalTests

  expect_exception_begin CSR_EXC_LE
  lhu $s0, 1($s1)
  expect_exception_end
  nop

test_li:
  test_begin "Testing LI"

  li $s0, 0xAA
  cmpi $s0, 0xAA
  btnez fail
  inc_var g_totalTests

  li $s0, 0x5555
  cmpi $s0, 0x5555
  btnez fail
  inc_var g_totalTests

test_swlw:
  test_begin "Testing SW/LW"

  li $s1, %hi(_lsdata)
  sll $s1, $s1, 16
  li $v0, %lo(_lsdata)
  or $s1, $v0

  li $v0, 0x55AA
  li $v1, 0x55AA

  sll $v1, 16
  or $v0, $v1

  sw $v0, 4($s1)

  lw $s0, 4($s1)

  cmp $v0, $s0
  btnez fail
  inc_var g_totalTests

  expect_exception_begin CSR_EXC_LE
  lw $s0, 1($s1)
  expect_exception_end
  nop
  expect_exception_begin CSR_EXC_LE
  lw $s0, 2($s1)
  expect_exception_end
  nop
  expect_exception_begin CSR_EXC_LE
  lw $s0, 3($s1)
  expect_exception_end
  nop
  expect_exception_begin CSR_EXC_SE
  sw $s1, 1($s1)
  expect_exception_end
  nop
  expect_exception_begin CSR_EXC_SE
  sw $s1, 2($s1)
  expect_exception_end
  nop
  expect_exception_begin CSR_EXC_SE
  sw $s1, 3($s1)
  expect_exception_end
  nop

test_lwpc:
  test_begin "Testing LW (PC relative)"

  li $s1, %hi(_lsdata)
  sll $s1, $s1, 16
  li $v0, %lo(_lsdata)
  or $s1, $v0

.align 4
  jal test_lwpc1
  lw $s0, 16($pc)
.align 4
.word 0xAA55AA55

test_lwpc1:
  li $v0, 0xAA55
  li $v1, 0xAA55
  sll $v1, 16
  or $v0, $v1

  cmp $s0, $v0
  btnez fail
  inc_var g_totalTests

test_swlwsp:
  test_begin "Testing LW/SW (SP relative)"

  xor $s0, $s0
  sw $v0, ($sp)
  lw $s0, ($sp)

  cmp $s0, $v0
  btnez fail
  inc_var g_totalTests

  move $s1, $ra
  sw $ra, ($sp)
  lw $s0, ($sp)

  cmp $s0, $s1
  btnez fail
  inc_var g_totalTests

  move $ra, $s1

test_mov:
  test_begin "Testing MOV"

  xor $s0, $s0
  move $1, $v0
  move $s0, $1

  cmp $s0, $v0
  btnez fail
  inc_var g_totalTests

test_mult:
  test_begin "Testing MULT"

  li $s0, 14
  li $s1, 18
  mult $s0, $s1

  mfhi $s1
  mflo $s0

  cmpi $s0, 252
  btnez fail
  inc_var g_totalTests

  bnez $s1, fail
  inc_var g_totalTests

  li $s0, 21
  li $s1, 2
  neg $s1
  mult $s0, $s1

  mflo $s0

  li $s1, 42
  neg $s1
  cmp $s0, $s1
  btnez fail
  inc_var g_totalTests

test_multu:
  test_begin "Testing MULTU"

  li $s0, 14
  li $s1, 18
  multu $s0, $s1

  mfhi $s1
  mflo $s0

  cmpi $s0, 252
  btnez fail
  inc_var g_totalTests
  bnez $s1, fail
  inc_var g_totalTests

test_neg:
  test_begin "Testing NEG"

  li $s0, 23
  neg $s0

  li $s1, 23
  not $s1
  addiu $s1, 1

  cmp $s0, $s1
  btnez fail
  inc_var g_totalTests

test_not:
  test_begin "Testing NOT"

  li $v0, 0xFFFF

  li $s0, 0xAAAA
  not $s0
  and $s0, $v0

  li $s1, 0x5555

  cmp $s0, $s1
  btnez fail
  inc_var g_totalTests

test_or:
  test_begin "Testing OR"

  li $s0, 0xAA
  li $s1, 0x55

  or $s0, $s1
  cmpi $s0, 0xFF
  btnez fail
  inc_var g_totalTests

/*test_seb:
  test_begin "Testing SEB"

  li $s0, 1
  #seb $s0
  srl $s0, 16
  cmpi $s0, 0x0000
  #btnez fail
  inc_var g_totalTests

  li $s0, 255
  #seb $s0
  srl $s0, 16
  cmpi $s0, 0xFFFF
  #btnez fail
  inc_var g_totalTests

test_seh:
  test_begin "Testing SEH"

  li $s0, 1
  #seh $s0
  srl $s0, 16
  cmpi $s0, 0x0000
  #btnez fail
  inc_var g_totalTests

  li $s0, 0xF000
  #seh $s0
  srl $s0, 16
  cmpi $s0, 0xFFFF
  #btnez fail
  inc_var g_totalTests
*/

test_sll:
  test_begin "Testing SLL"

  li $s0, 0xFF
  sll $s0, 4
  cmpi $s0, 0xFF0
  btnez fail
  inc_var g_totalTests

test_sllv:
  test_begin "Testing SLLV"

  li $s0, 0xFF
  li $s1, 4
  sllv $s0, $s1
  cmpi $s0, 0xFF0
  btnez fail
  inc_var g_totalTests

test_slt:
  test_begin "Testing SLT"

  li $s0, 5
  li $s1, 10

  slt $s0, $s1
  bteqz fail
  inc_var g_totalTests

  slt $s1, $s0
  btnez fail
  inc_var g_totalTests

test_slti:
  test_begin "Testing SLTI"

  li $s0, 10
  slti $s0, 11
  bteqz fail
  inc_var g_totalTests

  slti $s0, -9
  btnez fail
  inc_var g_totalTests

test_sltiu:
  test_begin "Testing SLTIU"

  li $s0, 10
  sltiu $s0, 11
  bteqz fail
  inc_var g_totalTests

  sltiu $s0, 9
  btnez fail
  inc_var g_totalTests

test_sltu:
  test_begin "Testing SLTU"

  li $s0, 5
  li $s1, 10

  sltu $s0, $s1
  bteqz fail
  inc_var g_totalTests

  sltu $s1, $s0
  btnez fail
  inc_var g_totalTests

test_sra:
  test_begin "Testing SRA"

  li $s0, 8
  neg $s0

  li $s1, 4
  neg $s1

  sra $s0, 1
  cmp $s0, $s1
  btnez fail
  inc_var g_totalTests

test_srav:
  test_begin "Testing SRAV"

  li $s0, 32
  neg $s0

  li $s1, 2

  srav $s0, $s1

  li $s1, 8
  neg $s1

  cmp $s0, $s1
  btnez fail
  inc_var g_totalTests

test_srl:
  test_begin "Testing SRL"

  li $s0, 1
  neg $s0

  srl $s0, 16
  cmpi $s0, 0xFFFF
  btnez fail
  inc_var g_totalTests

test_srlv:
  test_begin "Testing SRLV"

  li $s0, 16
  li $s1, 2

  srlv $s0, $s1
  cmpi $s0, 4
  btnez fail
  inc_var g_totalTests

test_subu:
  test_begin "Testing SUBU"

  li $s0, 50
  li $s1, 23

  subu $s0, $s0, $s1
  cmpi $s0, 27
  btnez fail
  inc_var g_totalTests

test_xor:
  test_begin "Testing XOR"

  li $s0, 0b00110011
  li $s1, 0b11110011

  xor $s0, $s1
  cmpi $s0, 0b11000000
  btnez fail
  inc_var g_totalTests

/*test_zeb:
  test_begin "Testing ZEB"

  li $s0, 0xFFFF
  #zeb $s0
  cmpi $s0, 0xFF
  #btnez fail
  inc_var g_totalTests

test_zeh:
  test_begin "Testing ZEH"

  li $s0, 0xFF
  #seb $s0
  #zeh $s0
  cmpi $s0, 0xFFFF
  #btnez fail
  inc_var g_totalTests
*/

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
  j mi32fail
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
  j mi32fail
  nop

.exc_rsn_ok:
  sub $t1, $k0
  sw $t1, ($t0)

  # Handle break code
  li $t9, CSR_EXC_BRK
  bne $k0, $t9, .exit_exc
  nop
.break_exc:
  srl $t8, $k1, 1
  sll $t8, $t8, 1
  lh  $k0, 0($t8)
  sll $k0, $k0, 21
  srl $k0, $k0, 26
  la $t9, expected_break_code
  lw $t9, ($t9)
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
  j mi32fail
  nop

.exit_exc:

  # check branch delay slot bit
  inc_var g_totalTests
  mfc0 $k0, C0_STATUS # read EXC_STATUS
  lui $a3, CSR_BD_MASK_HI
  and $k0, $k0, $a3
  bne $k0, $zero, mi32fail
  nop

  # Return to next instruction
  addiu $k1, 2
  jr  $k1
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
#  beq $zero, $zero, come_back
  nop
