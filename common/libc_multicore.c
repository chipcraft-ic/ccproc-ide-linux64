/*H*****************************************************************************
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
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
*
* ******************************************************************************
* File Name : libc_multicore.c
* Author    : Rafal Harabien
* ******************************************************************************
* $Date: 2018-10-08 11:52:38 +0200 (pon) $
* $Revision: 320 $
*H*****************************************************************************/

#include <sys/reent.h>
#include <sys/lock.h>
#include <ccproc.h>
#include <ccproc-irq.h>
#include <ccproc-utils.h>

static struct _reent SPRAM_DATA g_spramImpureData = _REENT_INIT(g_spramImpureData);

static inline int __attribute__((nomips16)) __ll(int *ptr)
{
    int res;
    __asm__ __volatile__ ("ll %0, %1"
        : "=r" (res) /* output */
        : "m" (*ptr) /* input */
    );
    return res;
}

static inline int __attribute__((nomips16)) __sc(int *ptr, int data)
{
    int res;
    __asm__ __volatile__ ("sc %0, %1"
        : "=r" (res), "=m" (*ptr) /* output */
        : "0" (data) /* input */
    );
    return res;
}

void __libc_lock_init(_LOCK_T *lock)
{
    lock->core = 0;
}

void __libc_lock_init_recursive(_LOCK_RECURSIVE_T *lock)
{
    lock->core = 0;
    lock->count = 0;
}

void __libc_lock_close(_LOCK_T *lock)
{
    return;
}

void __libc_lock_close_recursive(_LOCK_RECURSIVE_T *lock)
{
    return;
}

int __libc_lock_try_acquire(_LOCK_T *lock)
{
    /* 0 is used for free lock so add 1 to core ID */
    int currentCore = IRQ_STATUS_GET_CORE_ID(IRQ_CTRL_PTR->STATUS) + 1;
    int lockCore = __ll(&lock->core);
    if (lockCore != 0)
    {
        /* lock is already acquired */
        return -1;
    }
    /* lock is free - try acquire */
    if (!__sc(&lock->core, currentCore))
    {
        /* lock has been acquired by different core or exception occured */
        return -1;
    }
    /* Lock acquired successfully */
    return 0;
}

int __libc_lock_try_acquire_recursive(_LOCK_RECURSIVE_T *lock)
{
    /* 0 is used for free lock so add 1 to core ID */
    int currentCore = IRQ_STATUS_GET_CORE_ID(IRQ_CTRL_PTR->STATUS) + 1;
    int lockCore = __ll(&lock->core);
    if (!lockCore)
    {
        /* lock is free - try acquire */
        if (!__sc(&lock->core, currentCore))
        {
            /* lock has been acquired by different core or exception occured */
            return -1;
        }
    }
    else if (lockCore != currentCore)
    {
        /* lock is already acquired by different core */
        return -1;
    }
    /* Make sure count is read after acquiring the lock by issuing
       a compiler memory barrier */
    COMPILER_BARRIER();
    /* Current core has exclusive access - update recursion counter */
    ++lock->count;
    return 0;
}

void __libc_lock_acquire(_LOCK_T *lock)
{
    while (__libc_lock_try_acquire(lock) != 0);
}

void __libc_lock_acquire_recursive(_LOCK_RECURSIVE_T *lock)
{
    while (__libc_lock_try_acquire_recursive(lock) != 0);
}

void __libc_lock_release(_LOCK_T *lock)
{
    lock->core = 0;
}

void __libc_lock_release_recursive(_LOCK_RECURSIVE_T *lock)\
{
    /* Assume lock was properly acquired and decrement recursion counter */
    //int currentCore = IRQ_STATUS_GET_CORE_ID(IRQ_CTRL_PTR->STATUS) + 1;
    //ASSERT(g_mlock == currentCore);
    /* Decrement the counter */
    --lock->count;
    /* If counter value is zero lock should be released */
    if (!lock->count)
    {
        /* Make sure count is written before releasing the lock by issuing
           a compiler memory barrier */
        COMPILER_BARRIER();
        /* Release the lock */
        lock->core = 0;
    }
}

struct _reent * __getreent(void)
{
    return &g_spramImpureData;
}
