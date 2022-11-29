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
 * @file            crc-verification.c
 * @brief           CC Processor Support for firmware verification.
 * @author          Mateusz Jemielity
 *
 * @defgroup        CCVRFY Verification
 * Verification of firmware
 * @{
 */

#include <limits.h>
#include <stddef.h> /* size_t */
#include <stdint.h> /* uint32_t */

#include <crc-verification.h>

#define BITS_IN_BYTE CHAR_BIT
#define BITS_IN_UINT32 32U

/*
 * Generated with http://www.sunshine2k.de/coding/javascript/crc/crc_js.html
 */
static uint32_t const lut[ 256U ] = {
    0x00000000, 0x973AFB51, 0xB94F0DF3, 0x2E75F6A2,
    0xE5A4E0B7, 0x729E1BE6, 0x5CEBED44, 0xCBD11615,
    0x5C733A3F, 0xCB49C16E, 0xE53C37CC, 0x7206CC9D,
    0xB9D7DA88, 0x2EED21D9, 0x0098D77B, 0x97A22C2A,
    0xB8E6747E, 0x2FDC8F2F, 0x01A9798D, 0x969382DC,
    0x5D4294C9, 0xCA786F98, 0xE40D993A, 0x7337626B,
    0xE4954E41, 0x73AFB510, 0x5DDA43B2, 0xCAE0B8E3,
    0x0131AEF6, 0x960B55A7, 0xB87EA305, 0x2F445854,
    0xE6F613AD, 0x71CCE8FC, 0x5FB91E5E, 0xC883E50F,
    0x0352F31A, 0x9468084B, 0xBA1DFEE9, 0x2D2705B8,
    0xBA852992, 0x2DBFD2C3, 0x03CA2461, 0x94F0DF30,
    0x5F21C925, 0xC81B3274, 0xE66EC4D6, 0x71543F87,
    0x5E1067D3, 0xC92A9C82, 0xE75F6A20, 0x70659171,
    0xBBB48764, 0x2C8E7C35, 0x02FB8A97, 0x95C171C6,
    0x02635DEC, 0x9559A6BD, 0xBB2C501F, 0x2C16AB4E,
    0xE7C7BD5B, 0x70FD460A, 0x5E88B0A8, 0xC9B24BF9,
    0x5AD6DC0B, 0xCDEC275A, 0xE399D1F8, 0x74A32AA9,
    0xBF723CBC, 0x2848C7ED, 0x063D314F, 0x9107CA1E,
    0x06A5E634, 0x919F1D65, 0xBFEAEBC7, 0x28D01096,
    0xE3010683, 0x743BFDD2, 0x5A4E0B70, 0xCD74F021,
    0xE230A875, 0x750A5324, 0x5B7FA586, 0xCC455ED7,
    0x079448C2, 0x90AEB393, 0xBEDB4531, 0x29E1BE60,
    0xBE43924A, 0x2979691B, 0x070C9FB9, 0x903664E8,
    0x5BE772FD, 0xCCDD89AC, 0xE2A87F0E, 0x7592845F,
    0xBC20CFA6, 0x2B1A34F7, 0x056FC255, 0x92553904,
    0x59842F11, 0xCEBED440, 0xE0CB22E2, 0x77F1D9B3,
    0xE053F599, 0x77690EC8, 0x591CF86A, 0xCE26033B,
    0x05F7152E, 0x92CDEE7F, 0xBCB818DD, 0x2B82E38C,
    0x04C6BBD8, 0x93FC4089, 0xBD89B62B, 0x2AB34D7A,
    0xE1625B6F, 0x7658A03E, 0x582D569C, 0xCF17ADCD,
    0x58B581E7, 0xCF8F7AB6, 0xE1FA8C14, 0x76C07745,
    0xBD116150, 0x2A2B9A01, 0x045E6CA3, 0x936497F2,
    0xB5ADB816, 0x22974347, 0x0CE2B5E5, 0x9BD84EB4,
    0x500958A1, 0xC733A3F0, 0xE9465552, 0x7E7CAE03,
    0xE9DE8229, 0x7EE47978, 0x50918FDA, 0xC7AB748B,
    0x0C7A629E, 0x9B4099CF, 0xB5356F6D, 0x220F943C,
    0x0D4BCC68, 0x9A713739, 0xB404C19B, 0x233E3ACA,
    0xE8EF2CDF, 0x7FD5D78E, 0x51A0212C, 0xC69ADA7D,
    0x5138F657, 0xC6020D06, 0xE877FBA4, 0x7F4D00F5,
    0xB49C16E0, 0x23A6EDB1, 0x0DD31B13, 0x9AE9E042,
    0x535BABBB, 0xC46150EA, 0xEA14A648, 0x7D2E5D19,
    0xB6FF4B0C, 0x21C5B05D, 0x0FB046FF, 0x988ABDAE,
    0x0F289184, 0x98126AD5, 0xB6679C77, 0x215D6726,
    0xEA8C7133, 0x7DB68A62, 0x53C37CC0, 0xC4F98791,
    0xEBBDDFC5, 0x7C872494, 0x52F2D236, 0xC5C82967,
    0x0E193F72, 0x9923C423, 0xB7563281, 0x206CC9D0,
    0xB7CEE5FA, 0x20F41EAB, 0x0E81E809, 0x99BB1358,
    0x526A054D, 0xC550FE1C, 0xEB2508BE, 0x7C1FF3EF,
    0xEF7B641D, 0x78419F4C, 0x563469EE, 0xC10E92BF,
    0x0ADF84AA, 0x9DE57FFB, 0xB3908959, 0x24AA7208,
    0xB3085E22, 0x2432A573, 0x0A4753D1, 0x9D7DA880,
    0x56ACBE95, 0xC19645C4, 0xEFE3B366, 0x78D94837,
    0x579D1063, 0xC0A7EB32, 0xEED21D90, 0x79E8E6C1,
    0xB239F0D4, 0x25030B85, 0x0B76FD27, 0x9C4C0676,
    0x0BEE2A5C, 0x9CD4D10D, 0xB2A127AF, 0x259BDCFE,
    0xEE4ACAEB, 0x797031BA, 0x5705C718, 0xC03F3C49,
    0x098D77B0, 0x9EB78CE1, 0xB0C27A43, 0x27F88112,
    0xEC299707, 0x7B136C56, 0x55669AF4, 0xC25C61A5,
    0x55FE4D8F, 0xC2C4B6DE, 0xECB1407C, 0x7B8BBB2D,
    0xB05AAD38, 0x27605669, 0x0915A0CB, 0x9E2F5B9A,
    0xB16B03CE, 0x2651F89F, 0x08240E3D, 0x9F1EF56C,
    0x54CFE379, 0xC3F51828, 0xED80EE8A, 0x7ABA15DB,
    0xED1839F1, 0x7A22C2A0, 0x54573402, 0xC36DCF53,
    0x08BCD946, 0x9F862217, 0xB1F3D4B5, 0x26C92FE4
};

uint32_t
cc_verification_crc32(
    volatile void const * const data,
    size_t const size,
    uint32_t initial
)
{
    uint32_t result = initial;
    volatile uint8_t const * const bytes = data;
    for ( size_t i = 0U; i < size; ++i ) {
        /*
         * XOR-in next input byte into MSB of crc and get this MSB,
         * that's our new intermediate divident
         */
        uint8_t const intermediate =
            ( uint8_t )(
                (
                    result
                    ^ (
                        (( uint32_t ) bytes[ i ] )
                        << ( BITS_IN_UINT32 - BITS_IN_BYTE )
                    )
                ) >> ( BITS_IN_UINT32 - BITS_IN_BYTE )
            );
        /*
         * Shift out the MSB used for division per lookuptable
         * and XOR with the remainder
         */
        result = ( result << BITS_IN_BYTE ) ^ lut[ intermediate ];
    }
    /* Final round xors against 0x00, which can be omitted. */
    return result;
}

#define big_endian_to_native( VALUE ) ( VALUE )

uint32_t cc_verification_firmware_checksum( void )
{
    static cc_verification_firmware_metadata_t const zero;

    cc_verification_firmware_metadata_t const * const meta =
        ( cc_verification_firmware_metadata_t const * )
            CC_VERIFICATION_FIRMWARE_METADATA_BASE;
    uint32_t size = big_endian_to_native( meta->size );

    uint32_t result = CC_VERIFICATION_CRC32_INITIAL_VALUE;
    result =
        cc_verification_crc32(
            ( volatile void const * ) CC_VERIFICATION_FIRMWARE_START,
            ( size_t ) CC_VERIFICATION_FIRMWARE_METADATA_BASE,
            result
        );
    size -= CC_VERIFICATION_FIRMWARE_METADATA_BASE;
    /* supply zeroes for metadata filled by ccprog */
    result =
        cc_verification_crc32(
            &zero,
            sizeof( cc_verification_firmware_metadata_t ),
            result
        );
    size -= sizeof( cc_verification_firmware_metadata_t );
    result =
        cc_verification_crc32(
            ( volatile void const * )(
                CC_VERIFICATION_FIRMWARE_METADATA_BASE
                + sizeof( cc_verification_firmware_metadata_t )
            ),
            ( size_t ) size,
            result
        );

    return result;
}

bool cc_verification_firmware_checksum_compare( void )
{
    cc_verification_firmware_metadata_t const * const meta =
        ( cc_verification_firmware_metadata_t const * )
            CC_VERIFICATION_FIRMWARE_METADATA_BASE;
    uint32_t const programmed = big_endian_to_native( meta->crc32 );
    uint32_t const calculated = cc_verification_firmware_checksum();

    bool const result = ( programmed == calculated );
    return result;
}

/** @} */

