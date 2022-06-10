/*H*****************************************************************************
*
* Copyright (c) 2022 ChipCraft Sp. z o.o. All rights reserved
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
* Author    : Mateusz Jemielity
* ******************************************************************************
* $Date: 2022-03-21 15:18:59 +0100 (pon, 21 mar 2022) $
* $Revision: 834 $
*H*****************************************************************************/

#include <ccproc.h>
#include <ccproc-verification.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>

#include "test.h"

#define big_endian_to_native( VALUE ) ( VALUE )

int main(void)
{
    printf( "Starting CRC32 test\n" );

    cc_verification_firmware_metadata_t const * const meta =
        ( cc_verification_firmware_metadata_t const * )
            CC_VERIFICATION_FIRMWARE_METADATA_BASE;
    uint32_t size = big_endian_to_native( meta->size );
    printf( "Size of firmware: %" PRIu32 "\n", size );
    uint32_t const programmed = big_endian_to_native( meta->crc32 );
    printf( "Programmed CRC32: %" PRIx32 "\n", programmed );

    printf( "Calculating CRC32...\n" );
    uint32_t const calculated = cc_verification_firmware_checksum();
    printf( "Calculated CRC32: %" PRIx32 "\n", calculated );

    assertEq( programmed, calculated );

    printf( "Check single-function check of CRC32...\n" );
    bool const test = cc_verification_firmware_checksum_compare();
    printf( "Result is: %s\n", ( test ? "true" : "false" ));
    assertTrue( test );

    printTestSummary();
    return 0;
}

