/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2020-03-01 10:46:31 +0100 (nie, 01 mar 2020) $
* $Revision: 532 $
*
*  ----------------------------------------------------------------------
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
 * -------------------------------------------------------------------- */

/*
    File : core_portme.c
*/
/*
    Author : Rafal Harabien
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <ccproc.h>
#include <ccproc-icache.h>
#include <ccproc-dcache.h>
#include <ccproc-csr.h>
#include <ccproc-utils.h>
#include <ccproc-mcore.h>
#include <core_util.h>
#include <pwd_util.h>
#include "coremark.h"

#if (MEM_METHOD==MEM_MALLOC)
#include <malloc.h>
/* Function: portable_malloc
    Provide malloc() functionality in a platform specific way.
*/
void *portable_malloc(size_t size) {
    void *ptr = malloc(size);
    memset(ptr, 0, size);
    return ptr;
}
/* Function: portable_free
    Provide free() functionality in a platform specific way.
*/
void portable_free(void *p) {
    free(p);
}
#else
void *portable_malloc(size_t size) {
    return NULL;
}
void portable_free(void *p) {
    p=NULL;
}
#endif

#if VALIDATION_RUN
    volatile ee_s32 seed1_volatile=0x3415;
    volatile ee_s32 seed2_volatile=0x3415;
    volatile ee_s32 seed3_volatile=0x66;
#endif
#if PERFORMANCE_RUN
    volatile ee_s32 seed1_volatile=0x0;
    volatile ee_s32 seed2_volatile=0x0;
    volatile ee_s32 seed3_volatile=0x66;
#endif
#if PROFILE_RUN
    volatile ee_s32 seed1_volatile=0x8;
    volatile ee_s32 seed2_volatile=0x8;
    volatile ee_s32 seed3_volatile=0x8;
#endif
    volatile ee_s32 seed4_volatile=ITERATIONS;
    volatile ee_s32 seed5_volatile=0;
/* Porting : Timing functions
    How to capture time and convert to seconds must be ported to whatever is supported by the platform.
    e.g. Read value from on board RTC, read value from cpu clock cycles performance counter etc.
    Sample implementation for standard time.h and windows.h definitions included.
*/
/* Define : TIMER_RES_DIVIDER
    Divider to trade off timer resolution and total time that can be measured.

    Use lower values to increase resolution, but make sure that overflow does not occur.
    If there are issues with the return value overflowing, increase this value.
    */
#define CORETIMETYPE struct timeval
#define GETMYTIME(_t) gettimeofday(_t, NULL)
#define MYTIMEDIFF(fin,ini) ((fin).tv_usec/1000+(fin).tv_sec*1000-(ini).tv_usec/1000-(ini).tv_sec*1000)
#define EE_TICKS_PER_SEC 1000

/** Define Host specific (POSIX), or target specific global time variables. */
static CORETIMETYPE start_time_val, stop_time_val;

/* Function : start_time
    This function will be called right before starting the timed portion of the benchmark.

    Implementation may be capturing a system timer (as implemented in the example code)
    or zeroing some system parameters - e.g. setting the cpu clocks cycles to 0.
*/
void start_time(void) {
    GETMYTIME(&start_time_val);
}
/* Function : stop_time
    This function will be called right after ending the timed portion of the benchmark.

    Implementation may be capturing a system timer (as implemented in the example code)
    or other system parameters - e.g. reading the current value of cpu cycles counter.
*/
void stop_time(void) {
    GETMYTIME(&stop_time_val);
}
/* Function : get_time
    Return an abstract "ticks" number that signifies time on the system.

    Actual value returned may be cpu cycles, milliseconds or any other value,
    as long as it can be converted to seconds by <time_in_secs>.
    This methodology is taken to accomodate any hardware or simulated platform.
    The sample implementation returns millisecs by default,
    and the resolution is controlled by <TIMER_RES_DIVIDER>
*/
CORE_TICKS get_time(void) {
    CORE_TICKS elapsed=(CORE_TICKS)(MYTIMEDIFF(stop_time_val, start_time_val));
    return elapsed;
}
/* Function : time_in_secs
    Convert the value returned by get_time to seconds.

    The <secs_ret> type is used to accomodate systems with no support for floating point.
    Default implementation implemented by the EE_TICKS_PER_SEC macro above.
*/
secs_ret time_in_secs(CORE_TICKS ticks) {
    secs_ret retval=((secs_ret)ticks) / (secs_ret)EE_TICKS_PER_SEC;
    return retval;
}

ee_u32 default_num_contexts=MULTITHREAD;

/* Function : portable_init
    Target specific initialization code
    Test for some common mistakes.
*/
void portable_init(core_portable *p, int *argc, char *argv[])
{
    if (sizeof(ee_ptr_int) != sizeof(ee_u8 *)) {
        ee_printf("ERROR! Please define ee_ptr_int to a type that holds a pointer!\n");
    }
    if (sizeof(ee_u32) != 4) {
        ee_printf("ERROR! Please define ee_u32 to a 32b unsigned type!\n");
    }
    p->portable_id=1;
    printf("Starting CoreMark...\n");
}
/* Function : portable_fini
    Target specific final code
*/
void portable_fini(core_portable *p)
{
    p->portable_id=0;
}

#if (MULTITHREAD>1)

static core_results * volatile current_res;
static volatile int core_starting = 0;
static unsigned parallel_counter = 0;
static core_results ram_results[MULTITHREAD];

#if USE_SPRAM

static SPRAM_BSS core_results spram_results;
static SPRAM_BSS ee_u8 spram_memblock[TOTAL_DATA_SIZE];

/* Prepare valid results structure in SPRAM memory */
static void prepare_results_in_spram(const core_results *in)
{
    unsigned i;

    /* Copy input parameters */
    memcpy(&spram_results, in, offsetof(core_results, crc));

    /* Init memory blocks */
    spram_results.memblock[0] = spram_memblock;
    for (i=0; i<NUM_ALGORITHMS; i++) {
        spram_results.memblock[i+1] = in->memblock[i+1] - in->memblock[0] + spram_memblock;
    }

    /* Init all structures (copied from CoreMark main function) */
    if (spram_results.execs & ID_LIST) {
        spram_results.list=core_list_init(spram_results.size,spram_results.memblock[1],spram_results.seed1);
    }
    if (spram_results.execs & ID_MATRIX) {
        core_init_matrix(spram_results.size, spram_results.memblock[2], (ee_s32)spram_results.seed1 | (((ee_s32)spram_results.seed2) << 16), &(spram_results.mat) );
    }
    if (spram_results.execs & ID_STATE) {
        core_init_state(spram_results.size,spram_results.seed1,spram_results.memblock[3]);
    }
}

/* Copy results from structure in SPRAM memory to RAM */
static void copy_results_from_spram(core_results *out)
{
    out->crc = spram_results.crc;
    out->crclist = spram_results.crclist;
    out->crcmatrix = spram_results.crcmatrix;
    out->crcstate = spram_results.crcstate;
    out->err = spram_results.err;
}

#endif /* USE_SPRAM */

/* Copy results to SPRAM if needed and start iterating */
static void prepare_results_and_iterate(core_results *res)
{
    core_results *res2;

#if USE_SPRAM
    /* Copy results structure to SPRAM */
    prepare_results_in_spram(res);
    res2 = &spram_results;
#else
    res2 = res;
#endif

    /* Start benchmarking now */
    iterate(res2);

#if USE_SPRAM
    copy_results_from_spram(res);
#endif
}

/* Core entry-point is implemented in Assembly */
void core_entrypoint(void);

/* Called from core entry-point */
void core_main(void)
{
    core_results *res;

    /* Copy input parameter and inform main thread that we are ready */
    res = current_res;
    core_starting = 0;

    /* Start benchmark */
    prepare_results_and_iterate(res);
}

/* Function: core_start_parallel
    Start benchmarking in a parallel context.
*/
ee_u8 core_start_parallel(core_results *res)
{
    unsigned core_index;
    //volatile unsigned i;

    if (MULTITHREAD > MCORE_PTR->CORE_NUM){
        ee_printf("WARNING! Not enough cores to perform benchmark!\n");
        __asm__ __volatile__ ("jal end_loop");
    }

    core_index = parallel_counter;
    ++parallel_counter;
    res->port.portable_id = core_index;
    //printf("core_start_parallel %u\n", core_index);

    if (res->port.portable_id == 0)
    {
        /* First core - its current context but we cannot do a blocking call.
           Postpone benchmarking to core_stop_parallel function */

        // Disable lockstep mode if present
        if (lockstepDisable() == 0){
            ee_printf("Disabling lockstep mode!\n");
        }

        return 0;
    }
    else
    {
        /* Use global variable to pass results pointer to core procedure.
           Copy input parameters to RAM variable because CoreMark puts them on stack which is in SPRAM */
        current_res = &ram_results[core_index];
        memcpy(current_res, res, offsetof(core_results, crc));

        /* Start core */
        core_starting = 1;
        // flush write buffer
        MEMORY_BARRIER();
        MCORE_PTR->CORE_ADDR[core_index] = (uint32_t)core_entrypoint;
        MCORE_PTR->CORE_RUN[core_index] = MCORE_RUN_KEY;

        /* Wait for start */
        while (core_starting != 0);
        //for (i=0;i<100;i++);
    }

    return 0;
}

/* Function: core_stop_parallel
    Stop a parallel context execution of coremark, and gather the results.
*/
ee_u8 core_stop_parallel(core_results *res)
{
    //printf("core_stop_parallel %u (mcore status %x)\n", res->port.portable_id, MCORE_PTR->STATUS);

    if (res->port.portable_id == 0)
    {
        /* First core - lets start postponed benchmarking now */
        prepare_results_and_iterate(res);
    }
    else
    {
        unsigned core_flag;
        core_results *res_copy;

        /* Wait for core to exit */
        core_flag = 1 << res->port.portable_id;
        while (MCORE_PTR->STATUS & core_flag);

        /* Copy results */
        res_copy = (core_results*)&ram_results[res->port.portable_id];
        res->crc = res_copy->crc;
        res->crclist = res_copy->crclist;
        res->crcmatrix = res_copy->crcmatrix;
        res->crcstate = res_copy->crcstate;
        res->err = res_copy->err;
    }

    return 0;
}

#endif /* MULTITHREAD>1 */
