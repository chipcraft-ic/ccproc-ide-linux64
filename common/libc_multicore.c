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
* $Date: 2020-03-23 18:54:21 +0100 (pon, 23 mar 2020) $
* $Revision: 542 $
*H*****************************************************************************/

#include <sys/reent.h>
#include <sys/lock.h>
#include <ccproc.h>
#include <ccproc-csr.h>
#include <ccproc-mcore.h>
#include <ccproc-utils.h>

#ifndef _NO_SPRAM_MEMORY
  static struct _reent SPRAM_DATA g_spramImpureData = _REENT_INIT(g_spramImpureData);
#else
  static struct _reent * g_spramImpureData_array;
#endif

#ifndef NO_DEFAULT_LOCK

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
    int currentCore = CSR_STATUS_GET_CORE_ID(CSR_CTRL_PTR->STATUS) + 1;
    int lockCore = __ll(&lock->core);
    if (lockCore != 0)
    {
        /* lock is already acquired */
        return -1;
    }
    /* lock is free - try acquire */
    if (!__sc(&lock->core, currentCore))
    {
        /* lock has been acquired by different core or exception occurred */
        return -1;
    }
    /* Lock acquired successfully */
    return 0;
}

int __libc_lock_try_acquire_recursive(_LOCK_RECURSIVE_T *lock)
{
    /* 0 is used for free lock so add 1 to core ID */
    int currentCore = CSR_STATUS_GET_CORE_ID(CSR_CTRL_PTR->STATUS) + 1;
    int lockCore = __ll(&lock->core);
    if (!lockCore)
    {
        /* lock is free - try acquire */
        if (!__sc(&lock->core, currentCore))
        {
            /* lock has been acquired by different core or exception occurred */
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
    MEMORY_BARRIER();
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
    //int currentCore = CSR_STATUS_GET_CORE_ID(CSR_CTRL_PTR->STATUS) + 1;
    //ASSERT(g_mlock == currentCore);
    /* Decrement the counter */
    --lock->count;
    /* If counter value is zero lock should be released */
    if (!lock->count)
    {
        /* Make sure count is written before releasing the lock by issuing
           a compiler memory barrier */
        MEMORY_BARRIER();
        /* Release the lock */
        lock->core = 0;
    }
}

#endif

#ifndef _NO_SPRAM_MEMORY
struct _reent * __getreent(void)
{
    return &g_spramImpureData;
}
#else

extern void *_sbrk_r(struct _reent *r, ptrdiff_t incr);

struct _reent * __getreent(void)
{
    return &g_spramImpureData_array[CSR_STATUS_GET_CORE_ID(CSR_CTRL_PTR->STATUS)];
}

void __libc_impure_alloc(void)
{
    g_spramImpureData_array = (struct _reent *)((int)(_sbrk_r(0, (MCORE_PTR->CORE_NUM * sizeof(struct _reent))+3)+3)&(~3));
}

void __libc_impure_init(void)
{
    _REENT_INIT_PTR(__getreent());
}

#endif
