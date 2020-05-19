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
# File Name : stackprotect.S
# Author    : Rafal Harabien
# ******************************************************************************
# $Date: 2019-05-16 23:26:56 +0200 (czw, 16 maj 2019) $
# $Revision: 419 $
#H******************************************************************************

#include <specialreg.h>

.set noreorder

.macro inc_var var_name
  la $t9, \var_name
  lw $t8, ($t9)
  add $t8, 1
  sw $t8, ($t9)
.endm

#define MERGE(a, b)  a##b
#define OK_LABEL_(line) MERGE(.ok, line)
#define OK_LABEL OK_LABEL_(__LINE__)

#define ASSERT_ZERO(reg) \
  beqz reg, OK_LABEL; \
  _ASSERT_REST

#define ASSERT_NOT_ZERO(reg) \
  bnez reg, OK_LABEL; \
  _ASSERT_REST

#define ASSERT_EQ(reg, validReg) \
  beq reg, validReg, OK_LABEL; \
  _ASSERT_REST

#define _ASSERT_REST \
  nop; \
  inc_var g_failedTests; \
  la $a0, test_failed_str; \
  li $a1, __LINE__; \
  jal safe_printf; \
  nop; \
OK_LABEL: \
  inc_var g_totalTests

#define EXPECT_EXCEPTION_BEGIN(num) \
  la $t9, expected_exception; \
  li $t8, num; \
  sw $t8, ($t9);

#define EXPECT_EXCEPTION_END \
  la $t9, expected_exception; \
  lw $t9, ($t9); \
  ASSERT_ZERO($t9)

.data

safe_printf_buffer:
  .word 0 # System Controller Status Register
  .word 0 # Stack Pointer
  .word 0 # Return Address

test_val:
  .word 0xFFFFFFFF

.text

safe_printf:
  la $t7, safe_printf_buffer
  sw $sp, 4($t7)                 # save Stack Pointer in buffer
  sw $ra, 8($t7)                 # save Return Address in buffer
  li $t9, (CSR_CTRL_BASE << 16)  # System Controller base address
  lw $t8, ($t9)                  # load Status Register
  sw $t8, 0($t7)                 # save Status Register in buffer
  li $t6, ~(SPROT_EN_MASK)       # disable Stack Protection
  and $t8, $t6
  sw $t8, ($t9)                  # update Status Register
  la $sp, safe_printf_stack_end
  jal printf                     # do the printing job
  nop
  li $t9, (CSR_CTRL_BASE << 16)  # System Controller base address
  la $t7, safe_printf_buffer
  lw $t8, 0($t7)                 # read old Status Register value
  lw $sp, 4($t7)                 # restore Stack Pointer
  lw $ra, 8($t7)                 # restore Return Address
  sw $t8, 0($t9)                 # restore Status Register
  jr $ra
  nop

.global testStackProtection
testStackProtection:
  add $sp, -16                   # alloc stack
  sw $s0, 0($sp)                 # save s0 on stack
  sw $s1, 4($sp)                 # save s1 on stack
  sw $s2, 8($sp)                 # save s2 on stack
  sw $s3, 12($sp)                # save s3 on stack

  move $s0, $sp                  # save current Stack Pointer
  move $s1, $ra                  # save Return Address

  la $sp, stack_end              # set temporary stack
  li $s2, (CSR_CTRL_BASE << 16)  # System Controller Base base address
  la $t2, stack_begin
  sw $t2, SPROT_MIN_OFFSET($s2)  # update SP_MIN register
  sw $sp, SPROT_MAX_OFFSET($s2)  # update SP_MAX register
  lw $s3, 0($s2)                 # load Status Register
  ori $s3, SPROT_EN_MASK         # enable Stack Protection
  sw $s3, 0($s2)                 # store Status Register
  addi $sp, $sp, -4

  # now test Stack Protection

  lw $zero, -4($sp)  # ok

  lh $zero, -4($sp)  # ok
  lh $zero, -2($sp)  # ok

  lb $zero, -4($sp)  # ok
  lb $zero, -3($sp)  # ok
  lb $zero, -2($sp)  # ok
  lb $zero, -1($sp)  # ok

  sw $zero, -4($sp)  # ok

  sh $zero, -4($sp)  # ok
  sh $zero, -2($sp)  # ok

  sb $zero, -4($sp)  # ok
  sb $zero, -3($sp)  # ok
  sb $zero, -2($sp)  # ok
  sb $zero, -1($sp)  # ok

  sb $zero, 0($sp)  # ok
  sb $zero, 1($sp)  # ok
  sb $zero, 2($sp)  # ok
  sb $zero, 3($sp)  # ok
  sb $zero, 4($sp)  # ok

  sh $zero, 0($sp)  # ok
  sh $zero, 2($sp)  # ok
  sh $zero, 4($sp)  # ok

  sw $zero, 0($sp)  # ok
  sw $zero, 4($sp)  # ok

  lb $zero, 0($sp)  # ok
  lb $zero, 1($sp)  # ok
  lb $zero, 2($sp)  # ok
  lb $zero, 3($sp)  # ok
  lb $zero, 4($sp)  # ok

  lh $zero, 0($sp)  # ok
  lh $zero, 2($sp)  # ok
  lh $zero, 4($sp)  # ok

  lw $zero, 0($sp)  # ok
  lw $zero, 4($sp)  # ok

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sb $zero, 5($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sb $zero, 6($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sb $zero, 7($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sb $zero, 8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sh $zero, 6($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sh $zero, 8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sw $zero, 8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lb $zero, 5($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lb $zero, 6($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lb $zero, 7($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lb $zero, 8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lh $zero, 6($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lh $zero, 8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lw $zero, 8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sb $zero, -5($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sb $zero, -6($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sb $zero, -7($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sb $zero, -8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sh $zero, -6($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sh $zero, -8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  sw $zero, -8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lb $zero, -5($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lb $zero, -6($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lb $zero, -7($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lb $zero, -8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lh $zero, -6($sp)  # fail
  EXPECT_EXCEPTION_END
  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lh $zero, -8($sp)  # fail
  EXPECT_EXCEPTION_END

  EXPECT_EXCEPTION_BEGIN(CSR_EXC_SP)
  lw $zero, -8($sp)  # fail
  EXPECT_EXCEPTION_END

  xor $s3, SPROT_EN_MASK         # disable Stack Protection
  sw $s3, 0($s2)                 # store Status Register

  move $sp, $s0                  # restore Stack Pointer
  move $ra, $s1                  # restore Return Address
  lw $s0, 0($sp)                 # restore s0 from stack
  lw $s1, 4($sp)                 # restore s1 from stack
  lw $s2, 8($sp)                 # restore s2 from stack
  lw $s3, 12($sp)                # restore s3 from stack
  add $sp, 16                    # free stack
  jr $ra                         # return
  nop


###################
# Exception handler
####################

.global syscall_handler
syscall_handler:
  j .common_handler
  nop

.global exception_handler
exception_handler:
.common_handler:
  mfc0 $k0, C0_CAUSE             # read EXC_CAUSE

  #j .exit_exc
  #nop

  # Check if reason is not 0
  beqz $k0, .invalid_handler
  nop

  j .handler_ok
  nop

  # Invalid handler
.invalid_handler:
  la $a0, invalid_handler_str
  mfc0 $a1, C0_EPC               # read RET_PC
  jal safe_printf
  nop

.handler_ok:
  # Update expected exception variable
  la $k1, expected_exception
  lw $k1, ($k1)
  beq $k0, $k1, .exc_rsn_ok      # check if this is expected exception
  nop

  # Invalid exception
  la $a0, unexp_exc_str
  mfc0 $a1, C0_EPC               # read RET_PC
  move $a2, $k1
  move $a3, $k0
  jal safe_printf
  nop
  j .exit_exc
  nop

.exc_rsn_ok:
  la $k1, expected_exception
  sw $zero, ($k1)                # clear expected_exception

.exit_exc:
  mfc0 $k1, C0_EPC               # read RET_PC
  addiu $k1, 4                   # go to next instruction
  jr $k1                         # return
  rfe                            # end of exception handler

#ifndef _NO_SPRAM_MEMORY
.section .spram_bss, "aw", @nobits
#else
.data
#endif
  .space 8, 0 # space before
stack_begin:
  .space 8, 0
stack_end:
  .space 8, 0 # space after

safe_printf_stack_begin:
  .space 512, 0
safe_printf_stack_end:

##########
# Strings
##########

.data

test_failed_str:
  .ascii "(" __FILE__ ":%u) Test failed!\n\0"
unexp_exc_str:
  .asciiz "Unexpected exception on address %p: expected reason 0x%x, got 0x%x\n"
invalid_handler_str:
  .asciiz "Invalid handler called (syscall vs exception) from address %p\n"

expected_exception:
  .word 0
