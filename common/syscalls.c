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
* File Name : syscalls.c
* Author    : Rafal Harabien
* ******************************************************************************
* $Date: 2020-06-05 17:38:11 +0200 (pią, 05 cze 2020) $
* $Revision: 590 $
*H*****************************************************************************/

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <sys/stat.h>
#include <sys/unistd.h>
#include <sys/time.h>
#include <sys/times.h>
#include <ccproc.h>
#include <ccproc-utils.h>
#include <ccproc-csr.h>
#include <ccproc-perfcnt.h>
#include <ccproc-amba.h>
#include <ccproc-amba-timer.h>
#include <ccproc-amba-systick.h>
#include <ccproc-amba-rtc.h>
#include <board.h>

#define RTC_FREQ                    (32768/(TIME_SOURCE_PRSC+1))

#define TIME_SOURCE_TIMER_FREQ      (PERIPH0_FREQ/(TIME_SOURCE_PRSC+1))
#define TIME_SOURCE_PERFCNT_FREQ    (CORE_FREQ/TIME_SOURCE_PRSC)

#if TIME_SOURCE==RTC
    #define TIME_SOURCE_FREQ RTC_FREQ
#elif TIME_SOURCE==PERFCNT
    #define TIME_SOURCE_FREQ TIME_SOURCE_PERFCNT_FREQ
    #ifndef TIME_SOURCE_PRSC
        #error "Define TIME_SOURCE_PRSC variable, eg.: 40!"
    #endif
#elif TIME_SOURCE==TIMER32
    #define TIME_SOURCE_FREQ TIME_SOURCE_TIMER_FREQ
    #ifndef TIME_SOURCE_TIMER_ID
        #error "Define TIME_SOURCE_TIMER_ID variable, eg.: 0!"
    #endif
    #ifndef TIME_SOURCE_PRSC
        #error "Define TIME_SOURCE_PRSC variable, eg.: 40!"
    #endif
#elif TIME_SOURCE==TIMER16
    #define TIME_SOURCE_FREQ TIME_SOURCE_TIMER_FREQ
    #ifndef TIME_SOURCE_TIMER_ID
        #error "Define TIME_SOURCE_TIMER_ID variable, eg.: 0!"
    #endif
    #ifndef TIME_SOURCE_PRSC
        #error "Define TIME_SOURCE_PRSC variable, eg.: 40!"
    #endif
#elif TIME_SOURCE==SYSTICK
    #define TIME_SOURCE_FREQ TIME_SOURCE_TIMER_FREQ
    #ifndef TIME_SOURCE_PRSC
        #error "Define TIME_SOURCE_PRSC variable, eg.: 40!"
    #endif
#elif TIME_SOURCE==NONE
    #define TIME_SOURCE_FREQ 1
#else
    #error "Define valid TIME_SOURCE variable!"
    #pragma message STR(ALLOWED_TIME_SOURCE)
#endif /* TIME_SOURCE */
#ifndef TIME_SOURCE
    #error "Define valid TIME_SOURCE variable!"
    #pragma message STR(ALLOWED_TIME_SOURCE)
#endif /* TIME_SOURCE */

int uart_init_blocking(int uart, uint32_t baudrate, int rtscts);
int uart_write_blocking(int uart, char data);
int uart_read_blocking(int uart, char *data);

/**
 * @brief heap top address
 */
extern void *_sheap[]; /* make it array to solve small-data section problem */
static char *heap_begin, *heap_end, *heap_top;

static void clock_init(void)
{
#if TIME_SOURCE==RTC
    do{
        AMBA_RTC_PTR->CTRL |= RTC_CTRL_EN;
    } while (((AMBA_RTC_PTR->IRQF & RTC_TRERRIF) != 0) || ((AMBA_RTC_PTR->CTRL & RTC_CTRL_EN) == 0));
    while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
    AMBA_RTC_PTR->PRES = TIME_SOURCE_PRSC;
    while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
    AMBA_RTC_PTR->PER = 0xFFFFFFFF;
    while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
    AMBA_RTC_PTR->COMPARE = 0xFFFFFFFF;
    while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
#elif TIME_SOURCE==PERFCNT
    PERFCNT_PTR->STATUS |= PERFCNT_STAT_EN;
#elif TIME_SOURCE==TIMER32
    AMBA_TIMER32_PTR(TIME_SOURCE_TIMER_ID)->PER = 0xFFFFFFFF;
    AMBA_TIMER32_PTR(TIME_SOURCE_TIMER_ID)->PRES = TIME_SOURCE_PRSC;
    AMBA_TIMER32_PTR(TIME_SOURCE_TIMER_ID)->COUNT = 0;
    AMBA_TIMER32_PTR(TIME_SOURCE_TIMER_ID)->CTRL = TIMER_CTRL_EN;
#elif TIME_SOURCE==TIMER16
    AMBA_TIMER16_PTR(TIME_SOURCE_TIMER_ID)->PER = 0xFFFFFFFF;
    AMBA_TIMER16_PTR(TIME_SOURCE_TIMER_ID)->PRES = TIME_SOURCE_PRSC;
    AMBA_TIMER16_PTR(TIME_SOURCE_TIMER_ID)->COUNT = 0;
    AMBA_TIMER16_PTR(TIME_SOURCE_TIMER_ID)->CTRL = TIMER_CTRL_EN;
#elif TIME_SOURCE==SYSTICK
    AMBA_SYSTICK_PTR->CTRL = 0;
    AMBA_SYSTICK_PTR->COUNT = 0;
    AMBA_SYSTICK_PTR->PRES = TIME_SOURCE_PRSC;
    AMBA_SYSTICK_PTR->PER = 0xFFFFFFFF;
    AMBA_SYSTICK_PTR->CTRL = SYSTICK_CTRL_EN;
#elif TIME_SOURCE==NONE
#endif /* TIME_SOURCE */
}

static uint32_t clock_read(void)
{
#if TIME_SOURCE==RTC
    while (AMBA_RTC_PTR->STATUS & RTC_STAT_BUSY);
    return AMBA_RTC_PTR->COUNT;
#elif TIME_SOURCE==PERFCNT
    volatile uint64_t clock_val;
    clock_val = (uint64_t)PERFCNT_PTR->CYCLE_LO;
    clock_val += ((uint64_t)PERFCNT_PTR->CYCLE_HI << 32);
    clock_val /= TIME_SOURCE_PRSC;
    return (uint32_t)clock_val;
#elif TIME_SOURCE==TIMER32
    return AMBA_TIMER32_PTR(TIME_SOURCE_TIMER_ID)->COUNT;
#elif TIME_SOURCE==TIMER16
    return AMBA_TIMER16_PTR(TIME_SOURCE_TIMER_ID)->COUNT;
#elif TIME_SOURCE==SYSTICK
    return AMBA_SYSTICK_PTR->COUNT;
#elif TIME_SOURCE==NONE
    return 0;
#endif /* TIME_SOURCE */
}

/**
 * @brief Initialize NewLib, called by __libc_init_array() from the startup script
 */
void _ccsdk_init(void)
{
    /* Setup heap */
    uint32_t cpu_info = CSR_CTRL_PTR->CPU_INFO_0;
    heap_begin = (char*)&_sheap;
    if (CPU_INFO_GET_DMSIZE_LOG(cpu_info) == 0)
        // in case of no on-chip RAM memory
        heap_end = (char*)(RAM_BASE + 0x0FFFFFFF);
    else
        heap_end = (char*)(RAM_BASE + CPU_INFO_GET_DMSIZE(cpu_info));
    heap_top = heap_begin;

    uart_init_blocking(STDIO_UART, STDIO_BAUDRATE, STDIO_RTSCTS);
    clock_init();
}

/**
 * @brief Free resources on NewLib de-initialization, not used for RIOT
 */
void _ccsdk_fini(void)
{
    /* nothing to do here */
}

/**
 * @brief Exit a program without cleaning up files
 *
 * If your system doesn't provide this, it is best to avoid linking with subroutines that
 * require it (exit, system).
 *
 * @param n the exit code, 0 for success, other value for error
 */
void _exit(int n)
{
    //BREAKPOINT();
    SYSCALLEXIT();
    while (1);
}

/**
 * @brief Allocate memory from the heap.
 *
 * @param r     _reent struct for the current thread
 * @param incr  Number of bytes to allocate or free in heap
 *
 * @return      Upon successful completion, sbrk() returns the prior break value.
 *              Otherwise, it returns (void *)-1 and sets errno to indicate the error.
 */
#ifndef NO_DEFAULT_SBRK
void *_sbrk_r(struct _reent *r, ptrdiff_t incr)
{
    char *res, *new_heap_top;

    new_heap_top = heap_top + incr;
    if (new_heap_top >= heap_begin && new_heap_top < heap_end) {
        res = heap_top;
        heap_top = new_heap_top;
    } else {
        res = (void*)-1;
        r->_errno = ENOMEM;
    }

    return res;
}
#endif

/**
 * @brief Get the process-ID of the current thread
 *
 * @return the process ID of the current thread
 */
int _getpid_r(void)
{
    return -1;
}

/**
 * @brief Send a signal to a given thread
 *
 * @param r     _reent struct for the current thread
 * @param pid   process ID
 * @param sig   signal number
 *
 * @return      Upon successful completion, 0 is returned.
 *              Otherwise, -1 is returned and errno set to indicate the error.
 */
int _kill_r(struct _reent *r, int pid, int sig)
{
    r->_errno = ESRCH;                      /* not implemented yet */
    return -1;
}

/**
 * @brief Open a file
 *
 * @param r     _reent struct for the current thread
 * @param name  file name or path
 * @param mode  file access mode
 *
 * @return      Upon successful completion, 0 is returned.
 *              Otherwise, -1 is returned and errno set to indicate the error.
 */
int _open_r(struct _reent *r, const char *name, int mode)
{
    r->_errno = ENODEV;                     /* not implemented yet */
    return -1;
}

/**
 * @brief Read from a file
 *
 * All input is read from STDIO. The function will block until a byte is actually read.
 *
 * Note: the read function does not buffer - data will be lost if the function is not
 * called fast enough.
 *
 * @param r      _reent struct for the current thread
 * @param fd     file descriptor
 * @param buffer buffer for result
 * @param count  buffer size
 *
 * @return       Upon successful completion, number of read bytes is returned.
 *               Otherwise, -1 is returned and errno set to indicate the error.
 */
int _read_r(struct _reent *r, int fd, void *buffer, unsigned int count)
{
    /* Only stdin stream is supported */
    if (fd != STDIN_FILENO) {
        r->_errno = EBADF;
        return -1;
    }

    /* Successfully handle nop read */
    if (count == 0) {
        return 0;
    }

    if (uart_read_blocking(STDIO_UART, (char*)buffer) != 0) {
        r->_errno = EIO;
        return -1;
    }

    return 1;
}
/**
 * @brief Write characters to a file
 *
 * All output is currently directed to STDIO, independent of the given file descriptor.
 * The write call will further block until the byte is actually written to the UART.
 *
 * @param r      _reent struct for the current thread
 * @param fd     file descriptor
 * @param data   pointer to buffer with data to be written
 * @param count  number of bytes to be written
 *
 * @return       Upon successful completion, number of written files is returned.
 *               Otherwise, -1 is returned and errno set to indicate the error.
 */
int __attribute__((nomips16)) _write_r(struct _reent *r, int fd, const void *data, unsigned int count)
{
    /* Only stdout and stderr streams are supported */
    if (fd != STDOUT_FILENO && fd != STDERR_FILENO) {
        r->_errno = EBADF;
        BREAKPOINT();
        return -1;
    }

    /* Write all bytes in blocking loop */
    r->_errno = 0;
    for (unsigned i = 0; i < count; i++) {
        char ch = ((char*)data)[i];
        if (uart_write_blocking(STDIO_UART, ch) != 0) {
            r->_errno = EIO;
            BREAKPOINT();
            return -1;
        }
    }

    return count;
}

/**
 * @brief Close a file
 *
 * @param r     _reent struct for the current thread
 * @param fd    file descriptor
 *
 * @return      Upon successful completion, 0 is returned.
 *              Otherwise, -1 is returned and errno set to indicate the error.
 */
int _close_r(struct _reent *r, int fd)
{
    r->_errno = ENODEV; /* not implemented yet */
    return -1;
}

/**
 * @brief Set position in a file
 *
 * @param r     _reent struct for the current thread
 * @param fd    file descriptor
 * @param pos   file offset
 * @param dir   seek direction
 *
 * @return      Upon successful completion, 0 is returned.
 *              Otherwise, -1 is returned and errno set to indicate the error.
 */
_off_t _lseek_r(struct _reent *r, int fd, _off_t pos, int dir)
{
    r->_errno = ENODEV; /* not implemented yet */
    return -1;
}

/**
 * @brief Status of an open file
 *
 * @param r     _reent struct for the current thread
 * @param fd    file descriptor
 * @param stat  returned file status
 *
 * @return      Upon successful completion, 0 is returned.
 *              Otherwise, -1 is returned and errno set to indicate the error.
 */
int _fstat_r(struct _reent *r, int fd, struct stat * st)
{
    memset(st, 0, sizeof(*st));
    r->_errno = ENODEV;                     /* not implemented yet */
    return -1;
}

/**
 * @brief Status of a file (by name)
 *
 * @param r     _reent struct for the current thread
 * @param name  file name or path
 * @param stat  returned file status
 *
 * @return      Upon successful completion, 0 is returned.
 *              Otherwise, -1 is returned and errno set to indicate the error.
 */
int _stat_r(struct _reent *r, char *name, struct stat *st)
{
    r->_errno = ENODEV; /* not implemented yet */
    return -1;
}

/**
 * @brief Query whether output stream is a terminal
 *
 * @param r     _reent struct for the current thread
 * @param fd    file descriptor
 *
 * @return      Upon successful completion, 0 is returned.
 *              Otherwise, -1 is returned and errno set to indicate the error.
 */
int _isatty_r(struct _reent *r, int fd)
{
    if (fd == STDOUT_FILENO || fd == STDERR_FILENO) {
        return 1;
    }
    else {
        return 0;
    }
}

/**
 * @brief  Remove a file's directory entry
 *
 * @param r     _reent struct for the current thread
 * @param path  file path
 *
 * @return      Upon successful completion, 0 is returned.
 *              Otherwise, -1 is returned and errno set to indicate the error.
 */
int _unlink_r(struct _reent *r, char* path)
{
    r->_errno = ENODEV; /* not implemented yet */
    return -1;
}

/**
 * @brief  Gets the current GMT time and the local timezone information.
 *
 * @param r          _reent struct for the current thread
 * @param ptimeval   number of seconds and microseconds since the Epoch
 * @param ptimezone  timezone information
 *
 * @return           Zero on success, nonzero on failure.
 */
int _gettimeofday_r(struct _reent *r, struct timeval *ptimeval, void *ptimezone)
{
    uint32_t count = clock_read();
    ptimeval->tv_sec = count / TIME_SOURCE_FREQ;
    ptimeval->tv_usec = (suseconds_t) ((count % TIME_SOURCE_FREQ) * 1000000ull / TIME_SOURCE_FREQ);
    return 0;
}

/**
 * @brief stores the current process times in the struct tms.
 */
int _times_r(struct _reent *r, struct tms *tmsbuf)
{
    unsigned long long count = clock_read();
    tmsbuf->tms_utime = (clock_t) (count * CLK_TCK / TIME_SOURCE_FREQ); /* user time */
    tmsbuf->tms_stime = 0;  /* system time */
    tmsbuf->tms_cutime = 0; /* user time of children */
    tmsbuf->tms_cstime = 0; /* system time of children */
    return 0;
}
