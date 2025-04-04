/*H*****************************************************************************
 *
 * Copyright (c) 2018 ChipCraft Sp. z o.o. All rights reserved
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
 * File Name : hhg110ullfmc.c
 * Author    : Maciej Plasota
 * ******************************************************************************
 * $Date: 2025-03-03 13:31:11 +0100 (pon, 03 mar 2025) $
 * $Revision: 1131 $
 *H*****************************************************************************/

#include <limits.h>
#include <stddef.h>
#include <stdint.h>

#include <ccproc.h>
#include <ccproc-dcache.h>

#include "flash.h"

/*
 * We need to get the word that contains given (possibly unaligned) address.
 * This means we should align down, by zeroing two least significant bits.
 */
#define WORD_ALIGN( address ) \
    ( \
        ( \
            ( address ) \
            | ( sizeof( uint32_t ) - 1U ) \
        ) \
            ^ \
        ( sizeof( uint32_t ) - 1U ) \
    )

#define PAGE_ALIGN( address ) \
    ( \
        ( \
            ( address ) \
            | ( flash_get_page_size_in_bytes() - 1U ) \
        ) \
            ^ \
        ( flash_get_page_size_in_bytes() - 1U ) \
    )

#define BYTE2WORD( byte, index ) \
    ( uint32_t ) ( \
        ( ( uint32_t ) ( byte ) ) \
        << ( ( sizeof( uint32_t ) - 1U - ( index ) ) * CHAR_BIT ) \
    )

#define WORD2BYTE( word, index ) \
	( uint8_t ) ( \
		( ( uint32_t ) ( word ) ) \
		>> ( ( sizeof( uint32_t ) - 1U - ( index ) ) * CHAR_BIT ) \
	)

#define CLEARBYTE( word, index ) \
    { \
        ( word ) |= BYTE2WORD( 0xFF, ( index ) ); \
        ( word ) ^= BYTE2WORD( 0xFF, ( index ) ); \
    }

#define IS_PAGE_ALIGNED( ADDRESS ) \
    ( \
        0U == ( ADDRESS & ( flash_get_page_size_in_bytes() - 1U )) \
    )

/*! \brief Sets the frequency of HCLK clock.
 *
 * \param hclk_freq_hz The frequency of HCLK clock to be configured.
 *
 */
void flash_set_HCLK_freq(uint32_t hclk_freq_hz)
{
    if(hclk_freq_hz <= 600000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_600kHz;
    }
    else if(hclk_freq_hz <= 750000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_750kHz;
    }
    else if(hclk_freq_hz <= 1000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_1MHz;
    }
    else if(hclk_freq_hz <= 1250000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_1_25MHz;
    }
    else if(hclk_freq_hz <= 1500000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_1_5MHz;
    }
    else if(hclk_freq_hz <= 2000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_2MHz;
    }
    else if(hclk_freq_hz <= 2500000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_2_5MHz;
    }
    else if(hclk_freq_hz <= 3000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_3MHz;
    }
    else if(hclk_freq_hz <= 4000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_4MHz;
    }
    else if(hclk_freq_hz <= 4500000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_4_5MHz;
    }
    else if(hclk_freq_hz <= 5500000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_5_5MHz;
    }
    else if(hclk_freq_hz <= 7000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_7MHz;
    }
    else if(hclk_freq_hz <= 9000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_9MHz;
    }
    else if(hclk_freq_hz <= 12000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_12MHz;
    }
    else if(hclk_freq_hz <= 16000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_16MHz;
    }
    else if(hclk_freq_hz <= 21000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_21MHz;
    }
    else if(hclk_freq_hz <= 27000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_27MHz;
    }
    else if(hclk_freq_hz <= 35000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_35MHz;
    }
    else if(hclk_freq_hz <= 45000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_45MHz;
    }
    else if(hclk_freq_hz <= 60000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_60MHz;
    }
    else if(hclk_freq_hz <= 80000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_80MHz;
    }
    else if(hclk_freq_hz <= 100000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_100MHz;
    }
    else if(hclk_freq_hz <= 120000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_120MHz;
    }
    else if(hclk_freq_hz <= 140000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_140MHz;
    }
    else if(hclk_freq_hz <= 180000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_180MHz;
    }
    else if(hclk_freq_hz <= 200000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_200MHz;
    }
    else if(hclk_freq_hz <= 220000000)
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_220MHz;
    }
    else
    {
        AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_HCLK_FREQ) | FLASH_CTRL_HCLK_FREQ_250MHz;
    }
}

/*! \brief Sets the configuration of the Flash controller.
 *
 * \param hclk_freq_hz The frequency of HCLK clock to be configured.
 * \param wait_states_count The number of wait states for read operation.
 * \param sequential_prefetch_enable Enables sequential prefetch feature.
 * \param branch_prefetch_enable Enables branch prefetch feature.
 */
void flash_configure(uint32_t hclk_freq_hz, uint8_t wait_states_count, bool sequential_prefetch_enable, bool start_all_reads_as_sequential_enable)
{
    flash_set_HCLK_freq(hclk_freq_hz);
    flash_set_wait_states(wait_states_count);
    sequential_prefetch_enable ? flash_enable_sequential_prefetch() : flash_disable_sequential_prefetch();
    start_all_reads_as_sequential_enable ? flash_enable_start_all_reads_as_sequential() : flash_disable_start_all_reads_as_sequential();
}

/*! \brief Writes single word of data into the page buffer.
 *
 * \param page_buffer_word_offset The word offset of the data within the page buffer.
 * \param data_word The data word to be written into page buffer.
 *
 * This function sets up all registers and starts the write operation but doesn't wait for it to complete.
 * User is expected to monitor status until the write process is completed
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred (data could not be written to the buffer due to invalid parameters or asset being inaccessible).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_word_to_page_buffer(uint8_t page_buffer_word_offset, uint32_t data_word)
{
    if(page_buffer_word_offset > (sizeof (AMBA_FLASH_PTR->PAGE_BUFFER) / sizeof (* (AMBA_FLASH_PTR->PAGE_BUFFER))))
    {
        return ARGUMENT_ERROR;
    }
    AMBA_FLASH_PTR->DATA = data_word;
    AMBA_FLASH_PTR->ADDRESS = page_buffer_word_offset * 4;
    flash_unlock_command();
    flash_issue_command (FLASH_COMMAND_WRITE_PAGE_BUFFER_WORD);
    return flash_check_status();
}

/*! \brief Writes single word of data into the page buffer.
 *
 * \param page_buffer_word_offset The word offset of the data within the page buffer.
 * \param data_word The data word to be written into page buffer.
 *
 * This function uses direct access to the Page Buffer, meaning it won't exit until the write actually completed.
 * Status returned shall either be READY or one of the error codes.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval PROGRAMMING_ERROR programming error occurred (data could not be written to the buffer due to invalid parameters or asset being inaccessible).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_word_to_page_buffer_blocking(uint8_t page_buffer_word_offset, uint32_t data_word)
{
    if(page_buffer_word_offset > (sizeof (AMBA_FLASH_PTR->PAGE_BUFFER) / sizeof (* (AMBA_FLASH_PTR->PAGE_BUFFER))))
    {
        return ARGUMENT_ERROR;
    }
    AMBA_FLASH_PTR->PAGE_BUFFER[page_buffer_word_offset] = data_word;
    return flash_check_status();
}

/*! \brief Clears (set to 0xFF) the content of Page Buffer.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - page buffer could not be erased due to invalid parameters or asset being inaccessible.
 */
flash_access_status_t flash_clear_page_buffer()
{
    flash_issue_command (FLASH_COMMAND_CLR_PAGE_BUFFER);
    return flash_check_status();
}

/*! \brief Check status of the flash controller.
 *
 * Function can be used to check status of operation performed by the flash controller.
 * The status only applies complex operations (like program/erase) initiated through COMMAND interface.
 *
 * \return Status of flash controller.
 *   \retval READY all operations completed. Ready for next command
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred (data could not be written to the buffer due to invalid parameters or asset being inaccessible).
 *   \retval LOCK_ERROR command should have been unlocked first (by writing a password to LOCK register).
 */
flash_access_status_t flash_check_status()
{
    volatile uint32_t status = AMBA_FLASH_PTR->STATUS;
    if(status & FLASH_STATUS_PROGRAMMING_ERROR)
    {
        return PROGRAMMING_ERROR;
    }
    else if(status & FLASH_STATUS_LOCK_ERROR)
    {
        return LOCK_ERROR;
    }
    else if(status & FLASH_STATUS_BUSY)
    {
        return BUSY;
    }
    else
    {
        return READY;
    }
}

/*! \brief Loop while module is busy.
 *
 * Function can be used to poll the status of flash controller. Polling will stop, when busy status gets deasserted.
 *
 * \return Status of flash controller.
 *   \retval READY all operations completed. Ready for next command
 *   \retval PROGRAMMING_ERROR programming error occurred (data could not be written to the buffer due to invalid parameters or asset being inaccessible).
 *   \retval LOCK_ERROR command should have been unlocked first (by writing a password to LOCK register).
 */
flash_access_status_t flash_loop_while_busy()
{
    volatile uint32_t status;
    do
    {
        status = AMBA_FLASH_PTR->STATUS;
    }while( (status & FLASH_STATUS_BUSY) != 0);

    if(status & FLASH_STATUS_PROGRAMMING_ERROR)
    {
        return PROGRAMMING_ERROR;
    }
    else if(status & FLASH_STATUS_LOCK_ERROR)
    {
        return LOCK_ERROR;
    }
    else
    {
        return READY;
    }
}

/*! \brief Reads single word of data from the page buffer.
 *
 * \param page_buffer_word_offset The word offset of the data within the page buffer.
 * \param data_word The data word to read from page buffer.
 *
 * This function reads single data word from the Page Buffer. Direct access scheme is used.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval PROGRAMMING_ERROR data could not be read from the buffer due to invalid parameters or asset being inaccessible.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_read_page_buffer_word(uint8_t page_buffer_word_offset, uint32_t* data_word)
{
    if(page_buffer_word_offset > (sizeof (AMBA_FLASH_PTR->PAGE_BUFFER) / sizeof (* (AMBA_FLASH_PTR->PAGE_BUFFER))))
    {
        return ARGUMENT_ERROR;
    }
    *data_word = AMBA_FLASH_PTR->PAGE_BUFFER[page_buffer_word_offset];
    return flash_check_status();
}

/*! \brief Writes single page content to program memory.
 *
 * \param destination_address The start address of memory to be written.
 * \param data_buffer The pointer to memory buffer containing data to be written.
 * \param num_words The number of words to be written.
 *
 * This function copies provided data to page buffer and initiates write operation.
 * This function will not wait for the write to finish.
 * Input buffer can contain partial page data, but it may not cross the page boundary (128 words).
 * It's also allowed to write single bytes within the word (in that case, uninitialized bytes should be set to 0xFF).
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data could not be written to flash memory due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_page(uint32_t* destination_address, uint32_t* data_buffer, uint8_t num_words)
{
    uint32_t index;
    volatile flash_access_status_t status;
    if( ( ((uint32_t)destination_address % 4) != 0) || ((uint32_t)destination_address + num_words * 4 > ( ( ((uint32_t)destination_address / 512) + 1) * 512)))
    {
        return ARGUMENT_ERROR;
    }
    status = flash_clear_page_buffer();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    if(status == READY)
    {
        flash_unlock_write_page_data();
        for(index = 0; index < num_words; index++)
        {
            destination_address[index] = data_buffer[index];
        }
        AMBA_FLASH_PTR->ADDRESS = (uint32_t)destination_address;
        flash_unlock_command();
        flash_issue_command (FLASH_COMMAND_WRITE_PAGE);
        status = flash_check_status();
    }
    return status;
}

/*! \brief Writes single page content to program memory.
 *
 * \param destination_address The start address of memory to be written.
 * \param data_buffer The pointer to memory buffer containing data to be written.
 * \param num_words The number of words to be written.
 *
 * This function copies provided data to page buffer through APB interface and initiates write operation.
 * This function will not wait for the write to finish.
 * Input buffer can contain partial page data, but it may not cross the page boundary (128 words).
 * It's also allowed to write single bytes within the word (in that case, uninitialized bytes should be set to 0xFF).
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data could not be written to flash memory due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_page_slow(uint32_t* destination_address, uint32_t* data_buffer, uint8_t num_words)
{
    uint32_t index;
    volatile flash_access_status_t status;
    if( ( ((uint32_t)destination_address % 4) != 0) || ((uint32_t)destination_address + num_words * 4 > ( ( ((uint32_t)destination_address / 512) + 1) * 512)))
    {
        return ARGUMENT_ERROR;
    }
    status = flash_clear_page_buffer();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    if(status == READY)
    {
        for(index = 0; index < num_words; index++)
        {
            AMBA_FLASH_PTR->PAGE_BUFFER[(((uint32_t)destination_address%512)/4) + index] = data_buffer[index];
        }
        AMBA_FLASH_PTR->ADDRESS = (uint32_t)destination_address;
        flash_unlock_command();
        flash_issue_command (FLASH_COMMAND_WRITE_PAGE);
        status = flash_check_status();
    }
    return status;
}

/*! \brief Writes single data word to program memory.
 *
 * \param destination_address The address of memory to be written.
 * \param data_word Data word to be written.
 *
 * This function copies provided data word to page buffer and initiates write operation (previous page buffer content is lost).
 * This function will not wait for the write to finish.
 * It's allowed to write single bytes within the word (in that case, uninitialized bytes should be set to 0xFF).
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data could not be written to flash memory due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_word(uint32_t* destination_address, uint32_t data_word)
{
    volatile flash_access_status_t status;
    if( ((uint32_t)destination_address % 4) != 0)
    {
        return ARGUMENT_ERROR;
    }
    status = flash_clear_page_buffer();
    if(status == BUSY)
    {
        status = flash_loop_while_busy();
    }
    if(status == READY)
    {
        flash_unlock_write_page_data();
        *destination_address = data_word;
        AMBA_FLASH_PTR->ADDRESS = (uint32_t)destination_address;
        flash_unlock_command();
        flash_issue_command (FLASH_COMMAND_WRITE_WORD);
        status = flash_check_status();
    }
    return status;
}

/*! \brief Writes single data word to program memory.
 *
 * \param destination_address The address of memory to be written.
 * \param data_word Data word to be written.
 *
 * This function writes single data word to program memory. It doesn't use page buffer to do this, so it's content will be untouched.
 * This function will not wait for the write operation to finish.
 * It's allowed to write single bytes within the word (in that case, uninitialized bytes should be set to 0xFF).
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data could not be written to flash memory due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_word_immediate(uint32_t* destination_address, uint32_t data_word)
{
    if( ((uint32_t)destination_address % 4) != 0)
    {
        return ARGUMENT_ERROR;
    }
    AMBA_FLASH_PTR->DATA = data_word;
    AMBA_FLASH_PTR->ADDRESS = (uint32_t)destination_address;
    flash_unlock_command();
    flash_issue_command (FLASH_COMMAND_WRITE_IMMEDIATE);
    return flash_check_status();
}

/*! \brief Erases single data page from program memory.
 *
 * \param destination_address Address within the memory page to be erased.
 *
 * This function initializes erasure of single data page from program memory.
 * It will not wait for the erase operation to complete.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_erase_page(uint32_t* destination_address)
{
    AMBA_FLASH_PTR->ADDRESS = (uint32_t)destination_address;
    flash_unlock_command();
    flash_issue_command (FLASH_COMMAND_ERASE_PAGE);
    return flash_check_status();
}

/*! \brief Erases whole program memory.
 *
 * This function initializes erasure of whole program memory (data + region lock bits + debugger lock bits).
 * It will not wait for the erase operation to complete.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_erase_all()
{
    flash_unlock_command();
    flash_issue_command (FLASH_COMMAND_ERASE_ALL);
    return flash_check_status();
}

/*! \brief Locks region of program memory for write and erase.
 *
 * \param address_within_region_to_lock Address within the memory region to be locked.
 *
 * This function initializes procedure for locking single memory region. It will not wait for the operation to finish.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_lock_region(uint32_t* address_within_region_to_lock)
{
    AMBA_FLASH_PTR->ADDRESS = (uint32_t)address_within_region_to_lock;
    flash_unlock_command();
    flash_issue_command (FLASH_COMMAND_LOCK_REGION);
    return flash_check_status();
}

/*! \brief Locks ability to read memory content via debugger.
 *
 * This function initializes procedure for locking debugger read access to memory.
 * It will not wait for the operation to finish.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_lock_debugger_read()
{
    flash_unlock_command();
    flash_issue_command (FLASH_COMMAND_LOCK_DEBUGGER_READ);
    return flash_check_status();
}

/*! \brief Locks ability to access processor through debugger.
 *
 * This function initializes procedure for locking debugger access.
 * It will not wait for the operation to finish.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_lock_debugger_access()
{
    flash_unlock_command();
    flash_issue_command (FLASH_COMMAND_LOCK_DEBUGGER_ACCESS);
    return flash_check_status();
}

/*! \brief Checks if region containing provided address is locked for write/erase access.
 *
 * \param address_within_region_to_check_lock Address within the region to check for.
 *
 * \return State of the region to check for.
 *   \retval true region is locked for write/erase
 *   \retval false region is open for write/erase
 */
bool flash_is_region_locked(uint32_t* address_within_region_to_check_lock)
{
    uint32_t memory_offset = (uint32_t)address_within_region_to_check_lock - ROM_BASE;
    uint8_t region_locks_reg_offset = 0;
    uint8_t region_locks_bit_offset = 0;
    uint32_t region_lock_bit_number = (memory_offset / flash_get_page_size_in_bytes()) / flash_get_region_size_in_pages();

    region_locks_reg_offset = region_lock_bit_number / 32;
    region_locks_bit_offset = region_lock_bit_number % 32;

    return ( (AMBA_FLASH_PTR->REGION_LOCKS[region_locks_reg_offset] & (1 << region_locks_bit_offset)) != 0);
}

/*! \brief Returns programmable page size (in bytes)
 *
 * \return Size of data page in bytes.
 */
uint32_t flash_get_page_size_in_bytes()
{
    uint32_t page_size = (AMBA_FLASH_PTR->INFO & FLASH_INFO_PAGE_SIZE_MASK) >> FLASH_INFO_PAGE_SIZE_OFFSET;
    if(page_size == FLASH_INFO_PAGE_SIZE_512B)
    {
        return 512;
    }
    else
    {
        return 512;
    }
}

/*! \brief Returns number of paged within single flash memory module.
 *
 * \return Number of data pages within memory module
 */
uint32_t flash_get_module_size_in_pages()
{
    uint32_t module_size = (AMBA_FLASH_PTR->INFO & FLASH_INFO_MODULE_SIZE_MASK) >> FLASH_INFO_MODULE_SIZE_OFFSET;
    if(module_size == FLASH_INFO_MODULE_SIZE_512_PAGES)
    {
        return 512;
    }
    else
    {
        return 512;
    }
}

/*! \brief Writes single word of data into the factory row.
 *
 * \param word_offset_in_row The word offset of the data within the factory row.
 * \param data_word The data word to be written into the factory row.
 *
 * This function sets up all registers and starts the write operation but doesn't wait for it to complete.
 * User is expected to monitor status to learn when the write process is completed.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred (data could not be written to the buffer due to invalid parameters or asset being inaccessible).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_factory_row_word(uint8_t word_offset_in_row, uint32_t data_word)
{
    if(word_offset_in_row > (sizeof (AMBA_FLASH_PTR->FACTORY_ROW) / sizeof (* (AMBA_FLASH_PTR->FACTORY_ROW))))
    {
        return ARGUMENT_ERROR;
    }
    AMBA_FLASH_PTR->DATA = data_word;
    AMBA_FLASH_PTR->ADDRESS = word_offset_in_row * 4;
    flash_unlock_factory_row_command();
    flash_issue_command (FLASH_COMMAND_WRITE_FACTORY_ROW_WORD);
    return flash_check_status();
}

/*! \brief Writes single word of data into the factory row.
 *
 * \param word_offset_in_row The word offset of the data within the factory row.
 * \param data_word The data word to be written into the factory row.
 *
 * This function uses direct access to the factory row, meaning it won't exit until the write actually completed.
 * Status returned shall either be READY or one of the error codes.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval PROGRAMMING_ERROR programming error occurred (data could not be written to the buffer due to invalid parameters or asset being inaccessible).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_factory_row_word_blocking(uint8_t word_offset_in_row, uint32_t data_word)
{
    if(word_offset_in_row > (sizeof (AMBA_FLASH_PTR->FACTORY_ROW) / sizeof (* (AMBA_FLASH_PTR->FACTORY_ROW))))
    {
        return ARGUMENT_ERROR;
    }
    flash_unlock_factory_row_command();
    AMBA_FLASH_PTR->FACTORY_ROW[word_offset_in_row] = data_word;
    return flash_check_status();
}

/*! \brief Erases content of factory row.
 *
 * This function initializes erasure of the data contained in factory row.
 * It will not wait for the erase operation to complete.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_erase_factory_row()
{
    flash_unlock_factory_row_command();
    flash_issue_command (FLASH_COMMAND_ERASE_FACTORY_ROW);
    return flash_check_status();
}

/*! \brief Reads single word of data from the factory row.
 *
 * \param word_offset_in_row The word offset of the data within the factory row.
 * \param data_word The data word to read from the factory row.
 *
 * This function reads single data word from the factory row. Direct access scheme is used.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval PROGRAMMING_ERROR data could not be read from the buffer due to invalid parameters or asset being inaccessible.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_read_factory_row_word(uint8_t word_offset_in_row, uint32_t* data_word)
{
    if(word_offset_in_row > (sizeof (AMBA_FLASH_PTR->FACTORY_ROW) / sizeof (* (AMBA_FLASH_PTR->FACTORY_ROW))))
    {
        return ARGUMENT_ERROR;
    }
    *data_word = AMBA_FLASH_PTR->FACTORY_ROW[word_offset_in_row];
    return flash_check_status();
}

/*! \brief Locks ability to write, read and erase data within factory row.
 *
 * This function initializes procedure for locking factory row write/read/erase access to memory.
 * It will not wait for the operation to finish.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_lock_factory_row()
{
    flash_unlock_factory_row_command();
    flash_issue_command (FLASH_COMMAND_LOCK_FACTORY_ROW);
    return flash_check_status();
}

/*! \brief Writes single word of data into the user page.
 *
 * \param word_offset_in_row The word offset of the data within the user page.
 * \param data_word The data word to be written into the user page.
 *
 * This function sets up all registers and starts the write operation but doesn't wait for it to complete.
 * User is expected to monitor status to learn when the write process is completed.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred (data could not be written to the buffer due to invalid parameters or asset being inaccessible).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_user_row_word(uint8_t word_offset_in_row, uint32_t data_word)
{
    if(word_offset_in_row > (sizeof (AMBA_FLASH_PTR->USER_ROW) / sizeof (* (AMBA_FLASH_PTR->USER_ROW))))
    {
        return ARGUMENT_ERROR;
    }
    AMBA_FLASH_PTR->DATA = data_word;
    AMBA_FLASH_PTR->ADDRESS = word_offset_in_row * 4;
    flash_unlock_user_row_command();
    flash_issue_command (FLASH_COMMAND_WRITE_USER_ROW_WORD);
    return flash_check_status();
}

/*! \brief Writes single word of data into the user page.
 *
 * \param word_offset_in_row The word offset of the data within the user page.
 * \param data_word The data word to be written into the user page.
 *
 * This function uses direct access to the user page, meaning it won't exit until the write actually completed.
 * Status returned shall either be READY or one of the error codes.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval PROGRAMMING_ERROR programming error occurred (data could not be written to the buffer due to invalid parameters or asset being inaccessible).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_user_row_word_blocking(uint8_t word_offset_in_row, uint32_t data_word)
{
    if(word_offset_in_row > (sizeof (AMBA_FLASH_PTR->USER_ROW) / sizeof (* (AMBA_FLASH_PTR->USER_ROW))))
    {
        return ARGUMENT_ERROR;
    }
    flash_unlock_user_row_command();
    AMBA_FLASH_PTR->USER_ROW[word_offset_in_row] = data_word;
    return flash_check_status();
}

/*! \brief Reads single word of data from the user page.
 *
 * \param word_offset_in_row The word offset of the data within the user page.
 * \param data_word The data word to read from the user page.
 *
 * This function reads single data word from the user page. Direct access scheme is used.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_read_user_row_word(uint32_t word_offset_in_row, uint32_t* data_word)
{
    if(word_offset_in_row > (sizeof (AMBA_FLASH_PTR->USER_ROW) / sizeof (* (AMBA_FLASH_PTR->USER_ROW))))
    {
        return ARGUMENT_ERROR;
    }
    *data_word = AMBA_FLASH_PTR->USER_ROW[word_offset_in_row];
    return flash_check_status();
}

/*! \brief Erases content of user page.
 *
 * This function initializes erasure of the data contained in user page.
 * It will not wait for the erase operation to complete.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_erase_user_row()
{
    flash_unlock_user_row_command();
    flash_issue_command (FLASH_COMMAND_ERASE_USER_ROW);
    return flash_check_status();
}

/*! \brief Locks ability to write and erase data within user page.
 *
 * This function initializes procedure for locking user row write/erase access to memory.
 * It will not wait for the operation to finish.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_lock_user_row()
{
    flash_unlock_user_row_command();
    flash_issue_command (FLASH_COMMAND_LOCK_USER_ROW);
    return flash_check_status();
}

/*! \brief Writes single word of data into the manufacturer page.
 *
 * \param word_offset_in_row The word offset of the data within the manufacturer page.
 * \param data_word The data word to be written into the manufacturer page.
 *
 * This function sets up all registers and starts the write operation but doesn't wait for it to complete.
 * User is expected to monitor status to learn when the write process is completed.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred (data could not be written to the buffer due to invalid parameters or asset being inaccessible).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_manufacturer_row_word(uint8_t word_offset_in_row, uint32_t data_word)
{
    if(word_offset_in_row > (sizeof (AMBA_FLASH_PTR->MANUFACTURER_ROW) / sizeof (* (AMBA_FLASH_PTR->MANUFACTURER_ROW))))
    {
        return ARGUMENT_ERROR;
    }
    AMBA_FLASH_PTR->DATA = data_word;
    AMBA_FLASH_PTR->ADDRESS = word_offset_in_row * 4;
    flash_unlock_manufacturer_row_command();
    flash_issue_command (FLASH_COMMAND_WRITE_MANUFACTURER_ROW_WORD);
    return flash_check_status();
}

/*! \brief Writes single word of data into the manufacturer page.
 *
 * \param word_offset_in_row The word offset of the data within the manufacturer page.
 * \param data_word The data word to be written into the manufacturer page.
 *
 * This function uses direct access to the manufacturer page, meaning it won't exit until the write actually completed.
 * Status returned shall either be READY or one of the error codes.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval PROGRAMMING_ERROR programming error occurred (data could not be written to the buffer due to invalid parameters or asset being inaccessible).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_write_manufacturer_row_word_blocking(uint8_t word_offset_in_row, uint32_t data_word)
{
    if(word_offset_in_row > (sizeof (AMBA_FLASH_PTR->MANUFACTURER_ROW) / sizeof (* (AMBA_FLASH_PTR->MANUFACTURER_ROW))))
    {
        return ARGUMENT_ERROR;
    }
    flash_unlock_manufacturer_row_command();
    AMBA_FLASH_PTR->MANUFACTURER_ROW[word_offset_in_row] = data_word;
    return flash_check_status();
}

/*! \brief Erases content of manufacturer page.
 *
 * This function initializes erasure of the data contained in manufacturer page.
 * It will not wait for the erase operation to complete.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_erase_manufacturer_row()
{
    flash_unlock_manufacturer_row_command();
    flash_issue_command (FLASH_COMMAND_ERASE_MANUFACTURER_ROW);
    return flash_check_status();
}

/*! \brief Reads single word of data from the manufacturer page.
 *
 * \param word_offset_in_row The word offset of the data within the manufacturer page.
 * \param data_word The data word to read from the manufacturer page.
 *
 * This function reads single data word from the manufacturer page. Direct access scheme is used.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t flash_read_manufacturer_row_word(uint8_t word_offset_in_row, uint32_t* data_word)
{
    if(word_offset_in_row > (sizeof (AMBA_FLASH_PTR->MANUFACTURER_ROW) / sizeof (* (AMBA_FLASH_PTR->MANUFACTURER_ROW))))
    {
        return ARGUMENT_ERROR;
    }
    *data_word = AMBA_FLASH_PTR->MANUFACTURER_ROW[word_offset_in_row];
    return flash_check_status();
}

/*! \brief Locks ability to write and erase data within manufacturer page.
 *
 * This function initializes procedure for locking manufacturer page write/erase access to memory.
 * It will not wait for the operation to finish.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_lock_manufacturer_row()
{
    flash_unlock_manufacturer_row_command();
    flash_issue_command (FLASH_COMMAND_LOCK_MANUFACTURER_ROW);
    return flash_check_status();
}

/*! \brief Erases whole flash memory (including all rows and lock bits).
 *
 * This function initializes erasure of whole flash memory (data + all data rows + all lock bits).
 * It will not wait for the erase operation to complete.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_chip_erase()
{
    flash_unlock_command();
    flash_issue_command (FLASH_COMMAND_CHIP_ERASE);
    return flash_check_status();
}

/*! \brief Locks ability to issue chip erase command.
 *
 * This function initializes procedure for locking access to chip erase command.
 * It will not wait for the operation to finish.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_lock_chip_erase()
{
    flash_unlock_command();
    flash_issue_command (FLASH_COMMAND_LOCK_CHIP_ERASE);
    return flash_check_status();
}

/*! \brief Reads data from main array.
 *
 * \param address Address to start reading from.
 * \param data Pointer to output data buffer.
 * \param bytes Number of bytes to read, must fit in output data buffer.
 *
 * The read access is done using AHB interface.
 * The address is allowed to be unaligned.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t
flash_read(
    void const * const address,
    uint8_t * const data,
    size_t const bytes
)
{
    flash_access_status_t result = ARGUMENT_ERROR;
    if ( NULL == data ) {
        goto failure_arguments;
    }

    /*
     * by setting end byte to last actually read we work around situation
     * where one byte after is the first byte of a new word
     * depending on position (first of new word or not), we would need to
     * either not read a word or do read it, using branch
     * if instead we use last read, we don't have such problem, because
     * we always know we'll read the word including last byte
     */
    uintptr_t const uintptr_start = ( uintptr_t ) address;
    uintptr_t const uintptr_end = uintptr_start + bytes - 1U;

    /* TODO: check against flash size. */

    /* just in case */
    flash_loop_while_busy();

    /* AHB operates on words, calculate first and last word to read */
    uintptr_t const uintptr_start_word = WORD_ALIGN( uintptr_start );
    /* last word containing last read byte */
    uintptr_t const uintptr_end_word = WORD_ALIGN( uintptr_end );
	/* where the first byte is in first word, between 0 and 3 */
	size_t const uintptr_start_word_offset = uintptr_start - uintptr_start_word;
	/* where the last byte is in last word, between 0 and 3 */
	size_t const uintptr_end_word_offset = uintptr_end - uintptr_end_word;
    /*
     * difference_in_words == 0U: we stay within the same word
     * else we need to get at least two different words
     * ultimately we read (difference_in_words + 1) words
     */
    size_t const difference_in_words =
        ( uintptr_end_word - uintptr_start_word ) / sizeof( uint32_t );
    bool const manual_prefetch_control = ! flash_sequential_prefetch_state();

    if ( manual_prefetch_control && ( 0U < difference_in_words )) {
        flash_sequential_prefetch_enable();
    }

    /*
     * Reading is done word-aligned so it's faster.
     * Possible unaligned bytes in first and last words are handled separately.
     */

    uint32_t wordbuffer = 0U;
    size_t buffer_index = 0U;

	/*
	 * handle first word:
	 * copy bytes from uintptr_start_word_offset to either
	 * end of word or uintptr_end_word_offset (inclusive)
	 */
	{
		/* h/w translates into AHB access */
		wordbuffer = *( ( uint32_t const * ) ( uintptr_start_word ) );
		register size_t const last_byte_offset = /* will be read often */
			(
				( 0U == difference_in_words )
					?
						( uintptr_end_word_offset + 1U ) /* max 4 */
					:
						sizeof( uint32_t )
			);
		for (
			size_t i = uintptr_start_word_offset;
			i < last_byte_offset;
			( ++i ), ( ++buffer_index )
		) {
			data[ buffer_index ] = WORD2BYTE( wordbuffer, i );
		}
	}

	if ( 0U == difference_in_words ) {
		goto skip; /* we're done */
	}

	/*
	 * handle intermediate full words, only if > 2 words are read
	 * note: words read == (difference_in_words + 1)
	 * so if only two words are read, we won't enter this loop
	 */
	for (
		size_t i = 1U;
		i < difference_in_words;
		( ++i ), ( buffer_index += sizeof( uint32_t ) )
	) {
		/* h/w translates into AHB access */
		wordbuffer =
			*(
				( uint32_t const * ) (
					uintptr_start_word + ( sizeof( uint32_t ) * i )
				)
			);
		/* looks better unrolled */
		data[ buffer_index + 0U ] = WORD2BYTE( wordbuffer, 0U );
		data[ buffer_index + 1U ] = WORD2BYTE( wordbuffer, 1U );
		data[ buffer_index + 2U ] = WORD2BYTE( wordbuffer, 2U );
		data[ buffer_index + 3U ] = WORD2BYTE( wordbuffer, 3U );
	}

	/*
	 * handle last word:
	 * copy bytes from start of word to uintptr_end_word_offset
	 */
	{
		/* h/w translates into AHB access */
		wordbuffer = *( ( uint32_t const * ) ( uintptr_end_word ) );
		for (
			size_t i = 0U;
			i < ( uintptr_end_word_offset + 1U ); /* so max 4 */
			( ++i ), ( ++buffer_index )
		) {
			data[ buffer_index ] = WORD2BYTE( wordbuffer, i );
		}
	}


    if ( manual_prefetch_control && ( 0U < difference_in_words )) {
        flash_sequential_prefetch_disable();
    }

skip:
    result = flash_check_status();

failure_arguments:
    return result;
}

/*! \brief Writes contents of the page buffer into program memory.
 *
 * \param offset Flash offset (needs to be aligned to page size).
 *
 * This function stores current contents of the page buffer in program memory.
 * The write is done using APB indirect access.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval PROGRAMMING_ERROR data could not be read from the buffer due to invalid parameters or asset being inaccessible.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t
flash_page_buffer_write(
    void * const address
)
{
    flash_access_status_t result = ARGUMENT_ERROR;
    uint32_t const offset = ( uintptr_t ) address;
    if ( ! IS_PAGE_ALIGNED( offset )) {
        goto failure_arguments;
    }

    AMBA_FLASH_PTR->ADDRESS = offset;

    flash_unlock_command();
    flash_issue_command( FLASH_COMMAND_WRITE_PAGE );
    result = flash_check_status();

failure_arguments:
    return result;
}

static size_t
memcpy_hhg110ullfmc(
    uintptr_t const start,
    uintptr_t const end,
    uint8_t const * const src
) {
    size_t index = 0U;

    for (
        uintptr_t i = start;
        i < end;
        ( i += sizeof( uint32_t )), ( index += sizeof( uint32_t ))
    ) {
        /* we have to read byte by byte, because src may not be aligned */
        register uint32_t const wordbuffer =
            0U
            | BYTE2WORD( src[ index + 0U ], 0U )
            | BYTE2WORD( src[ index + 1U ], 1U )
            | BYTE2WORD( src[ index + 2U ], 2U )
            | BYTE2WORD( src[ index + 3U ], 3U )
            ;
        uint32_t volatile * const ahb = ( uint32_t volatile * ) ( i );
        *ahb = wordbuffer;
    }

    return index;
}

/*! \brief Write data to main array.
 *
 * \param address Address to start writing from.
 * \param data Pointer to output data buffer.
 * \param bytes Number of bytes to write, must fit in output data buffer.
 *
 * The write access is done using AHB interface.
 * The address is allowed to be unaligned.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 *   \retval ARGUMENT_ERROR invalid function input parameter.
 */
flash_access_status_t
flash_write(
    void * const address,
    uint8_t const * const data,
    size_t const bytes
)
{
    flash_access_status_t result = ARGUMENT_ERROR;
    if ( NULL == data ) {
        goto failure_arguments;
    }

    size_t const page_size = flash_get_page_size_in_bytes();
    /*
     * by setting end byte to last actually written we work around situation
     * where one byte after is the first byte of a new word
     * depending on position (first of new word or not), we would need to
     * either not write a word or do write it, using branch
     * if instead we use last write, we don't have such problem, because
     * we always know we'll write the word including last byte
     */
    uintptr_t const uintptr_start = ( uintptr_t ) address;
    uintptr_t const uintptr_end = uintptr_start + bytes - 1U;

    /* TODO: check against flash size. */

    /* just in case */
    flash_loop_while_busy();

    /* writes operate on pages, calculate first and last page to write */
    uintptr_t const uintptr_start_page = PAGE_ALIGN( uintptr_start );
    /* last page containing last write byte */
    uintptr_t const uintptr_end_page = PAGE_ALIGN( uintptr_end );
    /*
     * AHB operates on words, calculate first and last words
     * to write in page, between 0 and ( page size / sizeof( uint32_t ) - 1
     */
    uintptr_t const uintptr_start_word = WORD_ALIGN( uintptr_start);
    uintptr_t const uintptr_end_word = WORD_ALIGN( uintptr_end );
    /* where the first byte is in first word, between 0 and 3 */
    size_t const uintptr_start_page_first_word_offset =
        ( uintptr_start - uintptr_start_word );
    /* where the last byte is in last word, between 0 and 3 */
    size_t const uintptr_end_page_last_word_offset =
        ( uintptr_end - uintptr_end_word );
    /*
     * difference_in_pages == 0U: we stay within the same page
     * else we need to get at least two different pages
     * ultimately we write (difference_in_pages + 1) pages
     */
    size_t const difference_in_pages =
        ( uintptr_end_page - uintptr_start_page ) / page_size;
    size_t const difference_in_words =
        ( uintptr_end_word - uintptr_start_word ) / ( sizeof( uint32_t ));

    uint32_t wordbuffer = 0U;
    size_t buffer_index = 0U;

    /*
     * handle first page:
     * 1. read words from start of page to
     *    uintptr_start_page_first_word_offset (exclusive), copy them to
     *    page buffer via AHB write
     * 2. read uintptr_start_first_page_word_offset word into variable
     * 3. modify bytes from uintptr_start_page_first_word_offset to either:
     *    uintptr_end_page_last_word_offset or end of word, depending on bytes
     *    to write
     * 4. write modified word into page buffer via AHB
     * 5. write words from buffer to page buffer via AHB, until end of page
     *    buffer
     * 6. commit page buffer
     */
    {
        flash_clear_page_buffer();
        flash_loop_while_busy();

        /* copy words from flash to page buffer without modification */
        ( void ) memcpy_hhg110ullfmc(
            uintptr_start_page,
            uintptr_start_word,
            ( uint8_t const * ) uintptr_start_page
        );
        /* get word that could be modified */
        {
            uint32_t volatile * const ahb =
                ( uint32_t volatile * ) ( uintptr_start_word );
            /* AHB interface reads from flash memory cells */
            /* modify the word */
            {
                register size_t last_byte_offset = /* will be read often */
                    (
                        ( 0U == difference_in_pages )
                        && ( 0U == difference_in_words )
                    )
                        ?
                            (
                                uintptr_end_page_last_word_offset
                                + 1U
                            )
                        :
                            sizeof( uint32_t )
                        ;
                for (
                    /* iterate through bytes in a word in a page */
                    size_t i = uintptr_start_page_first_word_offset;
                    i < last_byte_offset;
                    ( ++i ), ( ++buffer_index )
                ) {
                    CLEARBYTE( wordbuffer, i );
                    /* modify wordbuffer from buffer */
                    wordbuffer |=
                        BYTE2WORD(
                            data[ buffer_index ],
                            i
                        );
                }
            }
            /* write modified word to page buffer */
            *ahb = wordbuffer;
        }

        if ( 0U == difference_in_words ) {
            goto handle_end_page;
        }

        /* copy words from given bufffer to page buffer until it fills */
        {
            uintptr_t const last_word =
                (
                    ( 0U == difference_in_pages )
                        ?
                            /* same page */
                            uintptr_end_word
                        :
                            /* last word in this page */
                            ( uintptr_start_page + page_size )
                );
            buffer_index +=
                memcpy_hhg110ullfmc(
                    ( uintptr_start_word + sizeof( uint32_t )),
                    last_word,
                    &( data[ buffer_index ] )
                );
        }

        if ( 0U == difference_in_pages ) {
            goto handle_end_word;
        }

        /* we've written full page buffer */
        result =
            flash_erase_page(( uint32_t * ) uintptr_start_page );
        if ( BUSY < result ) {
            goto failure_page_buffer_write;
        }
        flash_loop_while_busy();
        result =
            flash_page_buffer_write(( void * ) uintptr_start_page );
        if ( BUSY < result ) {
            goto failure_page_buffer_write;
        }
        flash_loop_while_busy();
    }

    /*
     * handle intermediate full pages, only if > 2 pages are written:
     * 1. read words from buffer to page buffer untill full page is ready
     * 2. commit page
     * note: pages written == (difference_in_pages + 1)
     * so if only two pages are written, we won't enter this loop
     */
    for (
        size_t i = 1U; /* iterate through pages */
        i < difference_in_pages;
        ++i
    ) {
        uintptr_t const page_to_handle =
            uintptr_start_page + ( page_size * i );
        flash_clear_page_buffer();
        flash_loop_while_busy();

        buffer_index +=
            memcpy_hhg110ullfmc(
                page_to_handle,
                ( page_to_handle + page_size ),
                &( data[ buffer_index ] )
            );

        result =
            flash_erase_page(( uint32_t * ) page_to_handle );
        if ( BUSY < result ) {
            goto failure_page_buffer_write;
        }
        flash_loop_while_busy();
        result =
            flash_page_buffer_write(( void * ) page_to_handle );
        if ( BUSY < result ) {
            goto failure_page_buffer_write;
        }
        flash_loop_while_busy();
    }

    /*
     * handle last page:
     * 1. write words from buffer to page buffer, starting from first word in
     *    page to uintptr_end_page_word_offset (exclusive)
     * 2. read uintptr_end_page_word_offset word into variable
     * 3. modify bytes from start of word, until
     *    uintptr_end_page_last_word_offset in the variable
     * 4. write modified word into page buffer
     * 5. read words from uintptr_end_page_word_offset (exclusive) to end of
     *    page, copy them to page buffer
     * 6. commit page buffer
     */
    {
        flash_clear_page_buffer();
        flash_loop_while_busy();

        buffer_index +=
            memcpy_hhg110ullfmc(
                uintptr_end_page,
                uintptr_end_word,
                &( data[ buffer_index ] )
            );

handle_end_word:
        /* get word that will be modified */
        {
            uint32_t volatile * const ahb =
                ( uint32_t volatile * ) uintptr_end_word;
            /* AHB interface reads from flash memory cells */
            /* modify the word */
            for (
                /* iterate through bytes in a word in a page */
                size_t i = 0U;
                i < uintptr_end_page_last_word_offset + 1U;
                ( ++i ), ( ++buffer_index )
            ) {
                CLEARBYTE( wordbuffer, i);
                /* modify wordbuffer from buffer */
                wordbuffer |=
                    BYTE2WORD(
                        data[ buffer_index ],
                        i
                    );
            }
            /* write modified word to page buffer */
            *ahb = wordbuffer;
        }

handle_end_page:
        ( void ) memcpy_hhg110ullfmc(
            ( uintptr_end_word + sizeof( uint32_t )),
            ( uintptr_end_page + page_size ),
            ( uint8_t const * )( uintptr_end_word + sizeof( uint32_t ))
        );

        result =
            flash_erase_page(( uint32_t * ) uintptr_end_page );
        if ( BUSY < result ) {
            goto failure_page_buffer_write;
        }
        flash_loop_while_busy();
        result =
            flash_page_buffer_write(( void * ) uintptr_end_page );
        if ( BUSY < result ) {
            goto failure_page_buffer_write;
        }
        flash_loop_while_busy();
    }

    /*
     * Need to flush data cache,
     * as it may not see updated values
     * in AHB address space
     * TODO: find less magicky way to do it
     */
    {
        DCACHE_PTR->FLUSH = 1U;
    }

    result = flash_check_status();

failure_page_buffer_write:
failure_arguments:
    return result;
}

/* Dummy function to maintain compatibility with CCRV32 API. */
flash_access_status_t
flash_sync( void )
{
    static flash_access_status_t const result = READY;
    /* Do nothing. */
    return result;
}

/* Dummy function to maintain compatibility with CCRV32 API. */
bool
flash_cache_buffer_allocated( void const * const address )
{
    /* Do nothing */
    return false;
}

/* Dummy function to maintain compatibility with CCRV32 API. */
int16_t
flash_cache_buffer_writes( void const * const address )
{
    /* Do nothing */
    return -1;
}

/* Dummy function to maintain compatibility with CCRV32 API. */
void
flash_cache_threshold( uint8_t const min, uint8_t const max )
{
    ( void ) min;
    ( void ) max;
    /* Do nothing. */
}

