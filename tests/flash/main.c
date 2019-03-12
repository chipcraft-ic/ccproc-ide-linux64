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
 * File Name : main.c
 * Author    : Maciej Plasota
 * ******************************************************************************
 * $Date: 2018-10-25 10:58:01 +0200 (czw) $
 * $Revision: 324 $
 *H*****************************************************************************/

#include "board.h"
#include <ccproc.h>
#include <ccproc-amba.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "test.h"

#ifdef MCU_CCNV1
    #include <ccproc-amba-flash.h>
    #include "flash.h"
    #define _BOARD_SUPPORTED_ 1
#endif

#ifdef _BOARD_SUPPORTED_

//if enabled, getting the processor to the state before test will require ERASE ALL command (and reprogramming)
#ifndef ERASE_ALL_REQUIRED_TESTS
    #define ERASE_ALL_REQUIRED_TESTS 0
#endif
//if enabled, getting the processor to the state before test will require CHIP ERASE command (reprogramming and reinitializing USER, MANUFACTURER and FACTORY data)
#ifndef CHIP_ERASE_REQUIRED_TESTS
    #define CHIP_ERASE_REQUIRED_TESTS 0
#endif
//if enabled, getting the processor to the state before test will require erasing NVR sector 1 of module 0 through the test interface
#ifndef TEST_INTF_ERASE_REQUIRED_TESTS
    #define TEST_INTF_ERASE_REQUIRED_TESTS 0
#endif
//if enabled, test will erase and rewrite first word of factory row (which may potentially be destructive)
#ifndef FACTORY_WRITE_READ_TESTS
    #define FACTORY_WRITE_READ_TESTS 0
#endif

static const uint32_t PAGE_SIZE_BYTES = 512;
static const uint32_t MODULE_SIZE_PAGES = 512;
static const uint32_t REGION_SIZE_PAGES = 16;
static const uint32_t NUMBER_OF_FLASH_MACRO_CELLS = 3;
/*
static void printRegDump()
{
    printf("\nRegister Dump:\n");
    printf("STATUS(%08X): %08X\n", & (AMBA_FLASH_PTR->STATUS), (unsigned int)AMBA_FLASH_PTR->STATUS);
    printf("CTRL(%08X): %08X\n", & (AMBA_FLASH_PTR->CTRL), (unsigned int)AMBA_FLASH_PTR->CTRL);
    printf("COMMAND(%08X): %08X\n", & (AMBA_FLASH_PTR->COMMAND), (unsigned int)AMBA_FLASH_PTR->COMMAND);
    printf("LOCK(%08X): %08X\n", & (AMBA_FLASH_PTR->LOCK), (unsigned int)AMBA_FLASH_PTR->LOCK);
    printf("ADDRESS(%08X): %08X\n", & (AMBA_FLASH_PTR->ADDRESS), (unsigned int)AMBA_FLASH_PTR->ADDRESS);
    printf("DATA(%08X): %08X\n", & (AMBA_FLASH_PTR->DATA), (unsigned int)AMBA_FLASH_PTR->DATA);
    printf("IRQM(%08X): %08X\n", & (AMBA_FLASH_PTR->IRQM), (unsigned int)AMBA_FLASH_PTR->IRQM);
    printf("IRQMAP(%08X): %08X\n", & (AMBA_FLASH_PTR->IRQMAP), (unsigned int)AMBA_FLASH_PTR->IRQMAP);
    printf("MASTER_LOCKS(%08X): %08X\n", & (AMBA_FLASH_PTR->MASTER_LOCKS), (unsigned int)AMBA_FLASH_PTR->MASTER_LOCKS);
    printf("INFO(%08X): %08X\n", & (AMBA_FLASH_PTR->INFO), (unsigned int)AMBA_FLASH_PTR->INFO);
    printf("REGION_LOCKS[0](%08X): %08X\n", & (AMBA_FLASH_PTR->REGION_LOCKS[0]), (unsigned int)AMBA_FLASH_PTR->REGION_LOCKS[0]);
    printf("REGION_LOCKS[1](%08X): %08X\n", & (AMBA_FLASH_PTR->REGION_LOCKS[1]), (unsigned int)AMBA_FLASH_PTR->REGION_LOCKS[1]);
}
*/
static void testFLASH_INFO()
{
    printf("\nFLASH info test\n");
    ok_eq(flash_get_page_size_in_bytes(), PAGE_SIZE_BYTES);
    ok_eq(flash_get_module_size_in_pages(), MODULE_SIZE_PAGES);
    ok_eq(flash_get_region_size_in_pages(), REGION_SIZE_PAGES);
    ok_eq(flash_get_number_of_modules(), NUMBER_OF_FLASH_MACRO_CELLS);
}

static void testFLASH_DebuggerReadLock()
{
    flash_access_status_t status;
    printf("\nDebugger Read Lock test\n");
    assertFalse(flash_is_debugger_read_locked());
    status = flash_lock_debugger_read();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);
    assertTrue(flash_is_debugger_read_locked());
}

static void testFLASH_DebuggerAccessLock()
{
    flash_access_status_t status;
    printf("\nDebugger Access Lock test\n");
    assertFalse(flash_is_debugger_access_locked());
    status = flash_lock_debugger_access();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);
    assertTrue(flash_is_debugger_access_locked());
}

static void testFLASH_ChipEraseLock()
{
    flash_access_status_t status;
    printf("\nChip Erase Lock test\n");
    assertFalse(flash_is_chip_erase_locked());
    status = flash_lock_chip_erase();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);
    assertTrue(flash_is_chip_erase_locked());

    status = flash_chip_erase();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, PROGRAMMING_ERROR);
}

static void testFLASH_MemoryWriteRead()
{
    printf("\nMemory write/read test\n");
    uint32_t* dataPointer = 0;
    flash_access_status_t status;
    uint32_t testVector[PAGE_SIZE_BYTES / 4];

    for(uint32_t idx_module = 0; idx_module < NUMBER_OF_FLASH_MACRO_CELLS; idx_module++)
    {
        for(uint32_t idx_row = 0; idx_row < 4; idx_row++)
        {
            for(uint32_t idx_col = 0; idx_col < PAGE_SIZE_BYTES/4; ++idx_col)
            {
                testVector[idx_col] = rand();
            }

            if(idx_row == 0)
            {
                dataPointer = (uint32_t*)(ROM_BASE + idx_module*MODULE_SIZE_PAGES*PAGE_SIZE_BYTES + (MODULE_SIZE_PAGES-3)*PAGE_SIZE_BYTES);
            }
            else if(idx_row == 1)
            {
                dataPointer = (uint32_t*)(ROM_BASE + idx_module*MODULE_SIZE_PAGES*PAGE_SIZE_BYTES + (MODULE_SIZE_PAGES-2)*PAGE_SIZE_BYTES);
            }
            else if(idx_row == 2)
            {
                dataPointer = (uint32_t*)(ROM_BASE + idx_module*MODULE_SIZE_PAGES*PAGE_SIZE_BYTES + (MODULE_SIZE_PAGES-1)*PAGE_SIZE_BYTES);
            }
            else
            {
                dataPointer = (uint32_t*)(ROM_BASE + idx_module*MODULE_SIZE_PAGES*PAGE_SIZE_BYTES + (MODULE_SIZE_PAGES-4)*PAGE_SIZE_BYTES);
            }

            assertFalse(flash_is_region_locked(dataPointer));

//            printf("\n - Erase");
            status = flash_erase_page(dataPointer);
            if(status == BUSY)
            {
                status = flash_loop_while_busy();
            }
            ok_eq(status, READY);

//            printf("\n - Write");
            if(idx_row == 0)
            {
//                printf(" Page slow");
                status = flash_write_page_slow(dataPointer, testVector, PAGE_SIZE_BYTES / 4);
                if(status == BUSY)
                {
                    status = flash_loop_while_busy();
                }
                ok_eq(status, READY);
            }
            else if(idx_row == 1)
            {
//                printf(" Word Immediate");
                for(uint32_t idx_data = 0; idx_data < PAGE_SIZE_BYTES/4; ++idx_data)
                {
                    status = flash_write_word_immediate(&dataPointer[idx_data], testVector[idx_data]);
                    if(status == BUSY)
                    {
                        status = flash_loop_while_busy();
                    }
                    ok_eq(status, READY);
                }
            }
            else if(idx_row == 2)
            {
//                printf(" Word");
                //check if it's locked
                for(uint32_t idx_data = 0; idx_data < PAGE_SIZE_BYTES/4; ++idx_data)
                {
                    status = flash_write_word(&dataPointer[idx_data], testVector[idx_data]);
                    if(status == BUSY)
                    {
                        status = flash_loop_while_busy();
                    }
                    ok_eq(status, READY);
                }
            }
            else
            {
//                printf(" Page");
                status = flash_write_page(dataPointer, testVector, PAGE_SIZE_BYTES / 4);
                if(status == BUSY)
                {
                    status = flash_loop_while_busy();
                }
                ok_eq(status, READY);
            }
//            printf("\n - Verify");
            for(uint32_t idx_col = 0; idx_col < PAGE_SIZE_BYTES/4; ++idx_col)
            {
                ok_eq(dataPointer[idx_col], testVector[idx_col]);
            }
        }
    }
}

static void testFLASH_MemoryLock()
{
    printf("\nMemory Lock test\n");
    uint32_t* dataPointer = 0;
    flash_access_status_t status;
    uint32_t testVector[PAGE_SIZE_BYTES / 4];

    for(uint32_t idx_module = 0; idx_module < NUMBER_OF_FLASH_MACRO_CELLS; idx_module++)
    {
        for(uint32_t idx_col = 0; idx_col < PAGE_SIZE_BYTES/4; ++idx_col)
        {
            testVector[idx_col] = rand() + 1;
        }

        dataPointer = (uint32_t*)(ROM_BASE + idx_module*MODULE_SIZE_PAGES*PAGE_SIZE_BYTES + (MODULE_SIZE_PAGES-3)*PAGE_SIZE_BYTES);
        assertFalse(flash_is_region_locked(dataPointer));

//        printf("\n - Erase");
        status = flash_erase_page(dataPointer);
        if(status == BUSY)
        {
            status = flash_loop_while_busy();
        }
        ok_eq(status, READY);

//        printf("\n - Write Page");
        status = flash_write_page(dataPointer, testVector, PAGE_SIZE_BYTES / 4);
        if(status == BUSY)
        {
            status = flash_loop_while_busy();
        }
        ok_eq(status, READY);

//        printf("\n - Verify");
        for(uint32_t idx_col = 0; idx_col < PAGE_SIZE_BYTES/4; ++idx_col)
        {
            ok_eq(dataPointer[idx_col], testVector[idx_col]);
        }

//        printf("\n - Lock Region");
        status = flash_lock_region(dataPointer);
        if(status == BUSY)
        {
            status = flash_loop_while_busy();
        }
        ok_eq(status, READY);

        assertTrue(flash_is_region_locked(dataPointer));

//        printf("\n - Erase");
        status = flash_erase_page(dataPointer);
        if(status == BUSY)
        {
            status = flash_loop_while_busy();
        }
        ok_eq(status, PROGRAMMING_ERROR);

//        printf("\n - Verify not erased");
        for(uint32_t idx_col = 0; idx_col < PAGE_SIZE_BYTES/4; ++idx_col)
        {
            ok_eq(dataPointer[idx_col], testVector[idx_col]);
        }

//        printf("\n - Locked Write Page");
        status = flash_write_page(dataPointer, testVector, PAGE_SIZE_BYTES / 4);
        if(status == BUSY)
        {
            status = flash_loop_while_busy();
        }
        ok_eq(status, PROGRAMMING_ERROR);
    }
}

static void testFLASH_ManufacturerWriteRead()
{
    printf("\nManufacturer write/read test\n");
    uint32_t testVector[PAGE_SIZE_BYTES / 4];
    uint32_t readWord = 0;
    flash_access_status_t status;

    //check if it's locked
    assertFalse(flash_is_manufacturer_row_locked());

//    printf("\n - Write\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        testVector[idx] = rand();
        if(idx%2 == 1) {
            status = flash_write_manufacturer_row_word_blocking(idx, testVector[idx]);
            ok_eq(status, READY);
        } else {
            status = flash_write_manufacturer_row_word(idx, testVector[idx]);
            if(status == BUSY)
            {
                status = flash_loop_while_busy();
            }
            ok_eq(status, READY);
        }
    }

//    printf("\n - Verify\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_manufacturer_row_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, testVector[idx]);
    }

//    printf("\n - Erase\n");
    status = flash_erase_manufacturer_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

//    printf("\n - Verify Erased\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_manufacturer_row_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, 0xFFFFFFFF);
    }
}

static void testFLASH_ManufacturerLock()
{
    printf("\nManufacturer lock test\n");
    uint32_t testVector[PAGE_SIZE_BYTES / 4];
    uint32_t readWord = 0;
    flash_access_status_t status;

    //check if it's locked
    assertFalse(flash_is_manufacturer_row_locked());

//    printf("\n - Erase\n");
    status = flash_erase_manufacturer_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

//    printf("\n - Write\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        testVector[idx] = rand();
        if(idx%2 == 1) {
            status = flash_write_manufacturer_row_word_blocking(idx, testVector[idx]);
            ok_eq(status, READY);
        } else {
            status = flash_write_manufacturer_row_word(idx, testVector[idx]);
            if(status == BUSY)
            {
                status = flash_loop_while_busy();
            }
            ok_eq(status, READY);
        }
    }

//    printf("\n - Verify\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_manufacturer_row_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, testVector[idx]);
    }

//    printf("\n - Lock Manufacturer Region\n");
    status = flash_lock_manufacturer_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

    //check if it's locked
    assertTrue(flash_is_manufacturer_row_locked());

//    printf("\n - Erase\n");
    status = flash_erase_manufacturer_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, PROGRAMMING_ERROR);

//    printf("\n - Verify not Erased\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_manufacturer_row_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, testVector[idx]);
    }
}

static void testFLASH_UserWriteRead()
{
    printf("\nUser write/read test\n");
    uint32_t testVector[PAGE_SIZE_BYTES / 4];
    uint32_t readWord = 0;
    flash_access_status_t status;

    //check if it's locked
    assertFalse(flash_is_user_row_locked());

//    printf("\n - Write\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        testVector[idx] = rand();
        if(idx%2 == 1) {
            status = flash_write_user_row_word_blocking(idx, testVector[idx]);
            ok_eq(status, READY);
        } else {
            status = flash_write_user_row_word(idx, testVector[idx]);
            if(status == BUSY)
            {
                status = flash_loop_while_busy();
            }
            ok_eq(status, READY);
        }
    }

//    printf("\n - Verify\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_user_row_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, testVector[idx]);
    }

//    printf("\n - Erase\n");
    status = flash_erase_user_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

//    printf("\n - Verify Erased\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_user_row_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, 0xFFFFFFFF);
    }
}

static void testFLASH_UserLock()
{
    printf("\nUser lock test\n");
    uint32_t testVector[PAGE_SIZE_BYTES / 4];
    uint32_t readWord = 0;
    flash_access_status_t status;

    //check if it's locked
    assertFalse(flash_is_user_row_locked());

    //    printf("\n - Erase\n");
    status = flash_erase_user_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

//    printf("\n - Write\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        testVector[idx] = rand();
        if(idx%2 == 1) {
            status = flash_write_user_row_word_blocking(idx, testVector[idx]);
            ok_eq(status, READY);
        } else {
            status = flash_write_user_row_word(idx, testVector[idx]);
            if(status == BUSY)
            {
                status = flash_loop_while_busy();
            }
            ok_eq(status, READY);
        }
    }

//    printf("\n - Verify\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_user_row_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, testVector[idx]);
    }

//    printf("\n - Lock Manufacturer Region\n");
    status = flash_lock_user_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

    //check if it's locked
    assertTrue(flash_is_user_row_locked());

//    printf("\n - Erase\n");
    status = flash_erase_user_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, PROGRAMMING_ERROR);

//    printf("\n - Verify not Erased\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_user_row_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, testVector[idx]);
    }
}

static void testFLASH_FactoryRead()
{
    printf("\nFactory read test\n");
    uint32_t readWord = 0;
    flash_access_status_t status;

    //check if it's locked
    assertFalse(flash_is_factory_row_locked());

    for(uint32_t idx = 0; idx < (PAGE_SIZE_BYTES / 4); idx++)
    {
        status = flash_read_factory_row_word(idx, &readWord);
        ok_eq(status, READY);
    }
}

static void testFLASH_FactoryWriteRead()
{
    printf("\nFactory write/read test\n");
    uint32_t testVector[PAGE_SIZE_BYTES / 4];
    uint32_t readWord = 0;
    flash_access_status_t status;

    //check if it's locked
    assertFalse(flash_is_factory_row_locked());

//    printf("\n - Read\n");
    status = flash_read_factory_row_word(0, &testVector[0]);
    ok_eq(status, READY);

//    printf("\n - Erase\n");
    status = flash_erase_factory_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

//    printf("\n - Write random data\n");
    readWord = rand();
    status = flash_write_factory_row_word(0, rand());
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

//    printf("\n - Verify\n");
    status = flash_read_factory_row_word(0, &readWord);
    ok_eq(status, READY);
    assertTrue(readWord != testVector[0]);

//    printf("\n - Erase\n");
    status = flash_erase_factory_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

//    printf("\n - Write back the old data\n");
    status = flash_write_factory_row_word(0, testVector[0]);
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);
}

static void testFLASH_FactoryLock()
{
    printf("\nFactory lock test\n");
    uint32_t testVector[PAGE_SIZE_BYTES / 4];
    uint32_t readWord = 0;
    flash_access_status_t status;

    //check if it's locked
    assertFalse(flash_is_factory_row_locked());

//    printf("\n - Lock Factory Region\n");
    status = flash_lock_factory_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

    //check if it's locked
    assertTrue(flash_is_factory_row_locked());

//    printf("\n - Erase\n");
    status = flash_erase_factory_row();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, PROGRAMMING_ERROR);

//    printf("\n - Verify not Erased\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_factory_row_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, 0);
    }
}

static void testFLASH_PageBufferWriteRead()
{
    printf("\nPageBuffer write/read test\n");
    uint32_t testVector[PAGE_SIZE_BYTES / 4];
    uint32_t readWord = 0;
    flash_access_status_t status;

    status = flash_clear_page_buffer();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }

//    printf("\n - Write\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        testVector[idx] = rand();
        if(idx%2 == 1) {
            status = flash_write_word_to_page_buffer_blocking(idx, testVector[idx]);
            ok_eq(status, READY);
        } else {
            status = flash_write_word_to_page_buffer(idx, testVector[idx]);
            if(status == BUSY)
            {
                status = flash_loop_while_busy();
            }
            ok_eq(status, READY);
        }
    }

//    printf("\n - Verify\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_page_buffer_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, testVector[idx]);
    }

//    printf("\n - Erase\n");
    status = flash_clear_page_buffer();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    ok_eq(status, READY);

//    printf("\n - Verify Erased\n");
    for(uint32_t idx = 0; idx < sizeof (testVector) / sizeof (*testVector); idx++)
    {
        status = flash_read_page_buffer_word(idx, &readWord);
        ok_eq(status, READY);
        ok_eq(readWord, 0xFFFFFFFF);
    }
}

#endif

int main(void)
{
#ifndef _BOARD_SUPPORTED_
    printf("\nFLASH unsupported\n");
#else

    /* Enable APB1 Bridge */
    AMBA_APB0_CFG_PTR->APB1_CFG = AMBA_APB1_EN;

    /* Configure Flash module */
    flash_configure(CORE_FREQ, FLASH_READ_WAIT_STATES_CALC(CORE_FREQ), false, false);

    srand (time(NULL));

    printf("\nStarting FLASH tests\n");

    testFLASH_INFO();
    testFLASH_MemoryWriteRead();
    testFLASH_ManufacturerWriteRead();
    testFLASH_UserWriteRead();
    testFLASH_PageBufferWriteRead();
    testFLASH_FactoryRead();
    #if FACTORY_WRITE_READ_TESTS > 0
        testFLASH_FactoryWriteRead();
    #endif
    #if ERASE_ALL_REQUIRED_TESTS > 0
        testFLASH_MemoryLock();
        testFLASH_DebuggerReadLock();
    #endif
    #if CHIP_ERASE_REQUIRED_TESTS > 0
        testFLASH_ManufacturerLock();
        testFLASH_UserLock();
        testFLASH_FactoryLock();
    #endif
    #if TEST_INTF_ERASE_REQUIRED_TESTS > 0
        testFLASH_DebuggerAccessLock();
        testFLASH_ChipEraseLock();
    #endif
#endif
    printTestSummary();

    return 0;
}

