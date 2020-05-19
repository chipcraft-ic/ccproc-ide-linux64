/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2020-02-13 09:24:01 +0100 (czw, 13 lut 2020) $
* $Revision: 523 $
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

/**
 * @file    test.h
 * @brief   Test utility functions and macros
 * @author  Rafal Harabien
 */
#pragma once

#ifndef TEST_COUNTERS_MODIFIERS
#define TEST_COUNTERS_MODIFIERS static volatile
#endif

/* test counters - volatile for multicore tests */
TEST_COUNTERS_MODIFIERS unsigned g_failedTests, g_totalTests;

#ifndef TEST_CONTEXT_FMT
#define TEST_CONTEXT_FMT // empty
#endif

#ifndef TEST_CONTEXT_VARS
#define TEST_CONTEXT_VARS // empty
#endif

extern int DebugPrintf(const char* format, ...);
#ifndef TEST_PRINTF
#define TEST_PRINTF printf
#endif

#define ok(expr, fmt, ...) \
    do { \
        if (!(expr)) { \
            TEST_PRINTF("(%s:%u" TEST_CONTEXT_FMT ") Test failed: " fmt, __FILE__, __LINE__ TEST_CONTEXT_VARS, ##__VA_ARGS__); \
            ++g_failedTests; \
        } \
        ++g_totalTests; \
    } while (0)

#define assertEq(value, expected) \
    do { \
        uint32_t valCopy = (value); \
        ok((valCopy) == (uint32_t)(expected), "invalid " #value " - expected " #expected " (%lx), got %lx\n", (uint32_t)(expected), (uint32_t)(valCopy)); \
    } while (0)

#define assertStrEq(value, expected, len) \
    do { \
        const char *valCopy = (const char*)(value); \
        ok(!strcmp(valCopy, expected), "invalid " #value " - expected " #expected " (%s), got %s\n", expected, valCopy); \
    } while (0)

#define assertStrEq2(value, expected, len) \
    do { \
        const char *valCopy = (const char*)(value); \
        ok(!strncmp(valCopy, expected, len), "invalid " #value " - expected " #expected " (%.*s), got %.*s\n", len, expected, len, valCopy); \
    } while (0)

#define assertTrue(expr) ok(expr, "expected " #expr "\n")

#define assertFalse(expr) ok(!(expr), "unexpected " #expr "\n")

static inline void printTestSummary()
{
    unsigned succeededTests = g_totalTests - g_failedTests;
    TEST_PRINTF("\n\n%u/%u tests succeeded, %u tests failed!\n\n", succeededTests, g_totalTests, g_failedTests);
}

// deprecated names
#define ok_eq assertEq
#define print_test_summary printTestSummary
