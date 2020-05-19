/* ----------------------------------------------------------------------
*
* Copyright (c) 2018 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2019-10-03 19:22:07 +0200 (czw, 03 paź 2019) $
* $Revision: 474 $
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
 * @file            ccproc-jtag.h
 * @brief           CC Processor Core Peripheral Access Layer Header File.
 * @author          Krzysztof Marcinek
 *
 * @addtogroup      CCPROC
 * CC Processor core definitions
 * @{
 */

#ifndef __CCPROC_JTAG_H
#define __CCPROC_JTAG_H

/************************//**
 * @defgroup jtag JTAG
 * JTAG definitions
 * @{
 *//************************/

#define CCPROC_JEDEC_MANUF_ID_DECIMAL 125     /*!< Decimal value of ChipCraft Sp. z o.o. JEDEC Manufacturer ID number */
#define CCPROC_JEDEC_MANUF_ID_BANK    10      /*!< Bank number of ChipCraft Sp. z o.o. JEDEC Manufacturer ID number   */

#define CCPROC_JTAG_MANUF_ID_HEX      0x4FD   /*!< IEEE-1149.1 JTAG number of ChipCraft Sp. z o.o. Manufacturer ID    */

/** JTAG IDCODE bit offsets */
enum
{
    JTAG_IDCODE_MANUF_ID_SHIFT = 1,  /*!< JTAG IDCODE Manufacturer ID offset  */
    JTAG_IDCODE_PART_NUM_SHIFT = 12, /*!< JTAG IDCODE part number offset      */
    JTAG_IDCODE_PART_VER_SHIFT = 28, /*!< JTAG IDCODE part version offset     */
};

/** JTAG IDCODE bit masks */
enum
{
    JTAG_IDCODE_MANUF_ID_MASK = 0x07FF << JTAG_IDCODE_MANUF_ID_SHIFT, /*!< JTAG IDCODE Manufacturer ID mask  */
    JTAG_IDCODE_PART_NUM_MASK = 0xFFFF << JTAG_IDCODE_PART_NUM_SHIFT, /*!< JTAG IDCODE part number mask      */
    JTAG_IDCODE_PART_VER_MASK = 0x000F << JTAG_IDCODE_PART_VER_SHIFT, /*!< JTAG IDCODE part version mask     */
};

/**
 * @name JTAG IDCODE helper macros
 * @{
 */
#define IDCODE_GET                       (CSR_CTRL_PTR->CPU_IDCODE)                                                 /*!< JTAG IDCODE get                          */
#define IDCODE_GET_MANUF_ID              ((IDCODE_GET & (JTAG_IDCODE_MANUF_ID_MASK)) >> JTAG_IDCODE_MANUF_ID_SHIFT) /*!< JTAG IDCODE get Manufacturer ID          */
#define IDCODE_GET_PART_NUM              ((IDCODE_GET & (JTAG_IDCODE_PART_NUM_MASK)) >> JTAG_IDCODE_PART_NUM_SHIFT) /*!< JTAG IDCODE get part number              */
#define IDCODE_GET_PART_VER              ((IDCODE_GET & (JTAG_IDCODE_PART_VER_MASK)) >> JTAG_IDCODE_PART_VER_SHIFT) /*!< JTAG IDCODE get part version             */
#define IDCODE_MATCH_MANUF_ID            (IDCODE_GET_MANUF_ID == CCPROC_JTAG_MANUF_ID_HEX)                          /*!< JTAG IDCODE check Manufacturer ID match  */
#define IDCODE_MATCH_PART_NUM(part_num)  (IDCODE_GET_PART_NUM == part_num)                                          /*!< JTAG IDCODE check part number match      */
#define IDCODE_MATCH_PART_VER(part_ver)  (IDCODE_GET_PART_VER == part_ver)                                          /*!< JTAG IDCODE check part version match     */
/** @} */

/** @} */

#endif /* __CCPROC_JTAG_H */
/** @} */
