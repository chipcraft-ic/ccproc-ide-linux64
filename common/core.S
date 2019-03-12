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
# File Name : core.S
# Author    : Rafal Harabien
# ******************************************************************************
# $Date: 2018-10-08 11:52:38 +0200 (pon) $
# $Revision: 320 $
#H******************************************************************************

#include <specialreg.h>

.set noreorder

.global core_entrypoint
core_entrypoint:

  nop                                 # feed pipeline with nops (for x-prop ASIC simulation)
  nop
  nop
  nop
  nop
  nop
  nop

  jal common_start                    # common core init (startup.S)
  nop

  add $sp, -16                        # call argument area
  jal core_main
  nop

  mfc0 $t1, C0_STATUS                 # disable interrupts
  ori $t2, $t0, IRQ_EN_MASK
  not $t2, $t2
  and $t1, $t1, $t2
  mtc0 $t1, C0_STATUS

  lui $t0, CACHE_CTRL_BASE            # Cache Controller base address
  sw $zero, ICACHE_STAT_OFFSET($t0)   # disable instruction cache
  sw $zero, DCACHE_STAT_OFFSET($t0)   # disable data cache

write_buffer_wait:
  lw $t1, DCACHE_STAT_OFFSET($t0)
  andi $t1, $t1, DCACHE_BUSY_MASK
  bgtz $t1, write_buffer_wait
  nop

  syscall SYSCALL_STOP_CORE
  nop

# safety loop
safety_loop:
  j safety_loop
  nop
