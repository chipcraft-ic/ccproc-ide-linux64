/* ----------------------------------------------------------------------
*
* Copyright (c) 2022 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2022-03-27 20:28:45 +0200 (nie, 27 mar 2022) $
* $Revision: 845 $
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
 * @file            crc-verification.h
 * @brief           CC Processor Support for firmware verification.
 * @author          Mateusz Jemielity
 *
 * @defgroup        CCVRFY Verification
 * Verification of firmware
 * @{
 */

#ifndef __CCPROC_VERIFICATION_H
# define __CCPROC_VERIFICATION_H

# include <stdbool.h>
# include <stddef.h>
# include <stdint.h>

# include "ccproc.h"

# ifdef __cplusplus
extern "C" {
# endif /* __cplusplus */

/** Firmware metadata structure, filled during firmware programming. */
typedef struct __attribute__((packed)) {
    uint32_t const reserved[ 2U ];
    uint32_t const size; /*!< Size of firmware in bytes, always big endian. */
    uint32_t const crc32; /*!< CRC32 calculated from firmware, always big endian. */
} cc_verification_firmware_metadata_t;

# define CC_VERIFICATION_FIRMWARE_START ROM_BASE

/** Firmware metadata memory layout. */
enum cc_verification_firmware_metadata_memory_layout_t
{
    CC_VERIFICATION_FIRMWARE_METADATA_BASE = ROM_BASE + 0x00000008 /*!< Start of firmware metadata in ROM. */
};

/** Utility macro returns ROM address of single cc_firmware_metadata member. */
# define CC_VERIFICATION_FIRMWARE_METADATA_ADDRESS_OF( MEMBER ) \
    ( \
        ( volatile void const * ) &( \
            ( \
                ( volatile cc_verification_firmware_metadata_t const * ) \
                    CC_VERIFICATION_FIRMWARE_METADATA_BASE \
            ) \
                ->MEMBER \
        ) \
    )

#define CC_VERIFICATION_CRC32_INITIAL_VALUE 0x00000000

/**
 * \brief Calculate CRC32 checksum of given data and its size.
 * \param data Binary data to checksum.
 * \param size Size of data in bytes.
 * \param initial Initial value of CRC32.
 *
 * CRC32 parameters:
 * width=32
 * poly=0x973AFB51
 * init=0x00000000
 * refin=false
 * refout=false
 * xorout=0x00000000
 * check=0x678b6786
 *
 * Allowing to pass initial value makes it possible for the algorithm to
 * properly work on data split into multiple parts. First function call has to
 * use CC_VERIFICATION_CRC32_INITIAL_VALUE. Following calls can use result of
 * the previous call:
~~~~
char buffer[ 2048U ] = ...;
char const * const buffer_1 = buffer;
char const * const buffer_2 = &( buffer[ 1024U ] );

uint32_t crc1;
uint32_t crc2;

crc1 =
    cc_verification_crc32(
        buffer_1,
        1024U,
        CC_VERIFICATION_CRC32_INITIAL_VALUE
    );
crc1 =
    cc_verification_crc32(
        buffer_2,
        1024U,
        crc1
    );

crc2 =
    cc_verification_crc32(
        buffer,
        2048U,
        CC_VERIFICATION_CRC32_INITIAL_VALUE
    );

assert( crc1 == crc2 );
~~~~
 * This is possible due to chosen CRC32 properties (zero xor, no reflection).
 */
uint32_t
cc_verification_crc32(
    volatile void const * const data,
    size_t const size,
    uint32_t initial
);

/** Calculate CRC32 of firmware stored in flash. */
uint32_t cc_verification_firmware_checksum( void );

/**
 * \brief Calculate firmware's CRC32, compare with value stored in metadata.
 * \return True on checksum match, false otherwise.
 */
bool cc_verification_firmware_checksum_compare( void );

# ifdef __cplusplus
}
# endif /* __cplusplus */

#endif /* __CCPROC_VERIFICATION_H */
/** @} */

