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
 * File Name : hhg110ullfmc.h
 * Author    : Maciej Plasota
 * ******************************************************************************
 * $Date: 2019-04-23 10:51:59 +0200 (wto, 23 kwi 2019) $
 * $Revision: 412 $
 *H*****************************************************************************/

#ifndef _FLASH_H_
#define _FLASH_H_
#pragma once

#include <ccproc-amba.h>
#include <ccproc-amba-flash.h>
#include <ccproc-csr.h>
#include <stdbool.h>

/*! \brief flash driver status returned by some of the functions.
 */
typedef enum
{
    READY = 0, BUSY, PROGRAMMING_ERROR, LOCK_ERROR, ARGUMENT_ERROR
} flash_access_status_t;

/*! \brief Sets the frequency of HCLK clock.
 *
 * \param hclk_freq_hz The frequency of HCLK clock to be configured.
 *
 */
void flash_set_HCLK_freq(uint32_t hclk_freq_hz);

/*! \brief Configure READ wait states count.
 *
 * \param wait_states_count The number of READ wait states to be set.
 *
 * This function configures the number of wait states to be used when reading flash memory content.
 */
static inline void flash_set_wait_states(uint8_t wait_states_count)
{
    AMBA_FLASH_PTR->CTRL = (AMBA_FLASH_PTR->CTRL & ~FLASH_CTRL_READ_WAIT_STATES) | ( (wait_states_count << FLASH_CTRL_READ_WAIT_STATES_OFFSET) & FLASH_CTRL_READ_WAIT_STATES);
}

/*! \brief Read READ wait states count.
 *
 * This function reads back the number of wait states to be used when reading flash memory content.
 *
 * \return Number of wait states during READ operation.
 */
static inline uint8_t flash_get_wait_states()
{
    return ( (AMBA_FLASH_PTR->CTRL & FLASH_CTRL_READ_WAIT_STATES) >> FLASH_CTRL_READ_WAIT_STATES_OFFSET);
}

/*! \brief Enable sequential prefetch.
 */
static inline void flash_enable_sequential_prefetch()
{
    AMBA_FLASH_PTR->CTRL |= FLASH_CTRL_SEQUENTIAL_PREFETCH;
}

/*! \brief Disable sequential prefetch.
 */
static inline void flash_disable_sequential_prefetch()
{
    AMBA_FLASH_PTR->CTRL &= ~FLASH_CTRL_SEQUENTIAL_PREFETCH;
}

/*! \brief Check if sequential prefetch is enabled.
 *
 * \return State of sequential prefetch configuration
 *  \retval true sequential prefetch is enabled
 *  \retval false sequential prefetch is disabled
 */
static inline bool flash_is_sequential_prefetch_enabled()
{
    return ( (AMBA_FLASH_PTR->CTRL & FLASH_CTRL_SEQUENTIAL_PREFETCH) != 0);
}

/*! \brief Enable treating all new reads as start of a sequential burst.
 */
static inline void flash_enable_start_all_reads_as_sequential()
{
    AMBA_FLASH_PTR->CTRL |= FLASH_CTRL_ASSUME_READS_SEQUENTIAL;
}

/*! \brief Disable treating all new reads as start of a sequential burst.
 */
static inline void flash_disable_start_all_reads_as_sequential()
{
    AMBA_FLASH_PTR->CTRL &= ~FLASH_CTRL_ASSUME_READS_SEQUENTIAL;
}

/*! \brief Check if treating all new reads as start of a sequential burst is enabled.
 *
 * \return State of treating all new reads as start of a sequential burst configuration
 *  \retval true treating all new reads as start of a sequential burst is enabled
 *  \retval false treating all new reads as start of a sequential burst is disabled
 */
static inline bool flash_is_start_all_reads_as_sequential_enabled()
{
    return ( (AMBA_FLASH_PTR->CTRL & FLASH_CTRL_ASSUME_READS_SEQUENTIAL) != 0);
}

/*! \brief Sets the configuration of the Flash controller.
 *
 * \param hclk_freq_hz The frequency of HCLK clock to be configured.
 * \param wait_states_count The number of wait states for read operation.
 * \param sequential_prefetch_enable Enables sequential prefetch feature.
 * \param start_all_reads_as_sequential_enable Enables treating all new reads as start of a sequential burst feature.
 */
void flash_configure(uint32_t hclk_freq_hz, uint8_t wait_states_count, bool sequential_prefetch_enable, bool start_all_reads_as_sequential_enable);

/*! \brief Unlock access to COMMAND register.
 *
 * This function will unlock access to commands modifying content of program memory and its fuse bits.
 */
static inline void flash_unlock_command()
{
    AMBA_FLASH_PTR->LOCK = FLASH_LOCK_ACCESS_PASSWORD;
}

/*! \brief Unlock access to COMMAND register.
 *
 * This function will unlock access to commands modifying content of user page and its fuse bits.
 */
static inline void flash_unlock_user_row_command()
{
    AMBA_FLASH_PTR->LOCK = FLASH_LOCK_USER_ROW_ACCESS_PASSWORD;
}

/*! \brief Unlock access to COMMAND register.
 *
 * This function will unlock access to commands modifying content of factory row and its fuse bits.
 */
static inline void flash_unlock_factory_row_command()
{
    AMBA_FLASH_PTR->LOCK = FLASH_LOCK_FACTORY_ROW_ACCESS_PASSWORD;
}

/*! \brief Unlock access to COMMAND register.
 *
 * This function will unlock access to commands modifying content of manufacturer page and its fuse bits.
 */
static inline void flash_unlock_manufacturer_row_command()
{
    AMBA_FLASH_PTR->LOCK = FLASH_LOCK_MANUFACTURER_ROW_ACCESS_PASSWORD;
}

/*! \brief Issue command to the controller (via COMMAND register).
 */
static inline void flash_issue_command(amba_flash_command_t command)
{
    AMBA_FLASH_PTR->COMMAND = command;
}

/*! \brief Clears (set to 0xFF) the content of Page Buffer.
 *
 * \return Status of operation.
 *   \retval READY operation completed.
 *   \retval BUSY operation in progress.
 *   \retval PROGRAMMING_ERROR programming error occurred - data page could not be erased due to invalid parameters or asset being inaccessible (region locked).
 *   \retval LOCK_ERROR operation should have been unlocked first.
 */
flash_access_status_t flash_clear_page_buffer();

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
flash_access_status_t flash_write_word_to_page_buffer(uint8_t page_buffer_word_offset, uint32_t data_word);

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
flash_access_status_t flash_write_word_to_page_buffer_blocking(uint8_t page_buffer_word_offset, uint32_t data_word);

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
flash_access_status_t flash_read_page_buffer_word(uint8_t page_buffer_word_offset, uint32_t* data_word);

/*! \brief Unlocks ability to write data into page buffer by directly addressing FLASH memory address range.
 */
static inline void flash_unlock_write_page_data(void)
{
    CSR_CTRL_PTR->ROM_UNLOCK = CSR_ROM_UNLOCK_KEY | CSR_ROM_UNLOCK;
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
flash_access_status_t flash_write_page(uint32_t* destination_address, uint32_t* data_buffer, uint8_t num_words);

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
flash_access_status_t flash_write_page_slow(uint32_t* destination_address, uint32_t* data_buffer, uint8_t num_words);

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
flash_access_status_t flash_write_word(uint32_t* destination_address, uint32_t data_word);

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
flash_access_status_t flash_write_word_immediate(uint32_t* destination_address, uint32_t data_word);

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
flash_access_status_t flash_erase_page(uint32_t* destination_address);

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
flash_access_status_t flash_erase_all();

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
flash_access_status_t flash_lock_region(uint32_t* address_within_region_to_lock);

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
flash_access_status_t flash_lock_debugger_read();

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
flash_access_status_t flash_lock_debugger_access();

bool flash_is_region_locked(uint32_t* address_within_region_to_check_lock);

/*! \brief Check if read flash memory through debugger is enabled.
 *
 * \return State of debugger read access
 *  \retval true debugger read is disabled
 *  \retval false debugger read is enabled
 */
static inline bool flash_is_debugger_read_locked()
{
    return ( (AMBA_FLASH_PTR->MASTER_LOCKS & FLASH_MASTER_LOCKS_DEBUGGER_READ_DISABLED) != 0);
}

/*! \brief Check if access through debugger is enabled.
 *
 * \return State of debugger access to the processor
 *  \retval true debugger access is disabled
 *  \retval false debugger access is enabled
 */
static inline bool flash_is_debugger_access_locked()
{
    return ( (AMBA_FLASH_PTR->MASTER_LOCKS & FLASH_MASTER_LOCKS_DEBUGGER_ACCESS_DISABLED) != 0);
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
flash_access_status_t flash_write_factory_row_word(uint8_t word_offset_in_row, uint32_t data_word);

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
flash_access_status_t flash_write_factory_row_word_blocking(uint8_t word_offset_in_row, uint32_t data_word);

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
flash_access_status_t flash_erase_factory_row();

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
flash_access_status_t flash_read_factory_row_word(uint8_t word_offset_in_row, uint32_t* data_word);

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
flash_access_status_t flash_lock_factory_row();

/*! \brief Check if read/write/erase access to factory row is allowed.
 *
 * \return State of factory row access
 *  \retval true factory row is locked
 *  \retval false factory row is accessible
 */
static inline bool flash_is_factory_row_locked()
{
    return ( (AMBA_FLASH_PTR->MASTER_LOCKS & FLASH_MASTER_LOCKS_FACTORY_ROW_LOCKED) != 0);
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
flash_access_status_t flash_write_user_row_word(uint8_t word_offset_in_row, uint32_t data_word);

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
flash_access_status_t flash_write_user_row_word_blocking(uint8_t word_offset_in_row, uint32_t data_word);

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
flash_access_status_t flash_read_user_row_word(uint32_t word_offset_in_row, uint32_t* data_word);

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
flash_access_status_t flash_erase_user_row();

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
flash_access_status_t flash_lock_user_row();

/*! \brief Check if write/erase access to user page is allowed.
 *
 * \return Status of user page accessibility
 *  \retval true user page is locked
 *  \retval false user page is accessible
 */
static inline bool flash_is_user_row_locked()
{
    return ( (AMBA_FLASH_PTR->MASTER_LOCKS & FLASH_MASTER_LOCKS_USER_ROW_LOCKED) != 0);
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
flash_access_status_t flash_write_manufacturer_row_word(uint8_t word_offset_in_row, uint32_t data_word);

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
flash_access_status_t flash_write_manufacturer_row_word_blocking(uint8_t word_offset_in_row, uint32_t data_word);

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
flash_access_status_t flash_erase_manufacturer_row();

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
flash_access_status_t flash_read_manufacturer_row_word(uint8_t word_offset_in_row, uint32_t* data_word);

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
flash_access_status_t flash_lock_manufacturer_row();

/*! \brief Check if write/erase access to manufacturer page is allowed.
 *
 * \return Status of manufacturer page accessibility
 *  \retval true manufacturer page is locked
 *  \retval false manufacturer page is accessible
 */
static inline bool flash_is_manufacturer_row_locked()
{
    return ( (AMBA_FLASH_PTR->MASTER_LOCKS & FLASH_MASTER_LOCKS_MANUFACTURER_ROW_LOCKED) != 0);
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
flash_access_status_t flash_chip_erase();

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
flash_access_status_t flash_lock_chip_erase();

/*! \brief Check if chip erase command is available.
 *
 * \return Status of chip erase command
 *  \retval true access to chip erase command is locked
 *  \retval false chip erase command is allowed
 */
static inline bool flash_is_chip_erase_locked()
{
    return ( (AMBA_FLASH_PTR->MASTER_LOCKS & FLASH_MASTER_LOCKS_CHIP_ERASE_LOCKED) != 0);
}

/*! \brief Enables FLASH READY interrupt.
 */
static inline void flash_enable_ready_interrupt()
{
    AMBA_FLASH_PTR->IRQM |= FLASH_IRQM_READY_IE;
}

/*! \brief Disables FLASH READY interrupt.
 */
static inline void flash_disable_ready_interrupt()
{
    AMBA_FLASH_PTR->IRQM &= ~FLASH_IRQM_READY_IE;
}

/*! \brief Check if FLASH READY interrupt is enabled.
 *
 * \return Status of FLASH READY interrupt
 *  \retval true interrupt is enabled
 *  \retval false interrupt is disabled
 */
static inline bool flash_is_ready_interrupt_enabled()
{
    return ( (AMBA_FLASH_PTR->IRQM & FLASH_IRQM_READY_IE) != 0);
}

/*! \brief Enables PROGRAMMING ERROR interrupt.
 */
static inline void flash_enable_programming_error_interrupt()
{
    AMBA_FLASH_PTR->IRQM |= FLASH_IRQM_PROGRAMMING_ERROR_IE;
}

/*! \brief Disables PROGRAMMING ERROR interrupt.
 */
static inline void flash_disable_programming_error_interrupt()
{
    AMBA_FLASH_PTR->IRQM &= ~FLASH_IRQM_PROGRAMMING_ERROR_IE;
}

/*! \brief Check if PROGRAMMING ERROR interrupt is enabled.
 *
 * \return Status of PROGRAMMING ERROR interrupt
 *  \retval true interrupt is enabled
 *  \retval false interrupt is disabled
 */
static inline bool flash_is_programming_error_interrupt_enabled()
{
    return ( (AMBA_FLASH_PTR->IRQM & FLASH_IRQM_PROGRAMMING_ERROR_IE) != 0);
}

/*! \brief Enables LOCK ERROR interrupt.
 */
static inline void flash_enable_lock_error_interrupt()
{
    AMBA_FLASH_PTR->IRQM |= FLASH_IRQM_LOCK_ERROR_IE;
}

/*! \brief Disables LOCK ERROR interrupt.
 */
static inline void flash_disable_lock_error_interrupt()
{
    AMBA_FLASH_PTR->IRQM &= ~FLASH_IRQM_LOCK_ERROR_IE;
}

/*! \brief Check if LOCK ERROR interrupt is enabled.
 *
 * \return Status of LOCK ERROR interrupt
 *  \retval true interrupt is enabled
 *  \retval false interrupt is disabled
 */
static inline bool flash_is_lock_error_interrupt_enabled()
{
    return ( (AMBA_FLASH_PTR->IRQM & FLASH_IRQM_LOCK_ERROR_IE) != 0);
}

/*! \brief Returns programmable page size (in bytes)
 *
 * \return Size of data page in bytes.
 */
uint32_t flash_get_page_size_in_bytes();

/*! \brief Returns number of paged within single flash memory module.
 *
 * \return Number of data pages within memory module
 */
uint32_t flash_get_module_size_in_pages();

/*! \brief Return the number of pages per program memory region.
 *
 * \return The number of pages contained in a single region (the smallest entity that can be locked).
 */
static inline uint32_t flash_get_region_size_in_pages()
{
    return (AMBA_FLASH_PTR->INFO & FLASH_INFO_REGION_SIZE_MASK) >> FLASH_INFO_REGION_SIZE_OFFSET;
}

/*! \brief Return the number of flash memory modules.
 *
 * \return The number of flash memory modules.
 */
static inline uint32_t flash_get_number_of_modules()
{
    return (AMBA_FLASH_PTR->INFO & FLASH_INFO_MODULES_NUMBER_MASK) >> FLASH_INFO_MODULES_NUMBER_OFFSET;
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
flash_access_status_t flash_loop_while_busy();

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
flash_access_status_t flash_check_status();

/*! \brief Configure mapping of the FLASH peripheral interrupt.
 *
 * \param irq_mapping mapping mask of the FLASH peripheral interrupt.
 */
static inline void flash_set_mapping_of_interrupts(uint32_t irq_mapping)
{
    AMBA_FLASH_PTR->IRQMAP = irq_mapping;
}

/*! \brief Returns mapping of the FLASH peripheral interrupt.
 *
 * \return \c 	mapping mapping mask of the FLASH peripheral interrupt.
 */
static inline uint32_t flash_get_mapping_of_interrupts()
{
    return AMBA_FLASH_PTR->IRQMAP;
}

#endif  // _FLASH_H_
