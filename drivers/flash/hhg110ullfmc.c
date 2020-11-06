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
 * $Date: 2020-10-30 11:47:46 +0100 (pią, 30 paź 2020) $
 * $Revision: 641 $
 *H*****************************************************************************/

#include "flash.h"

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
 * \param address Address to start read from.
 * \param data Pointer to output data.
 * \param words Number of words to read.
 */
void flash_read(uint32_t* address, uint32_t* data, uint32_t words)
{
    for (uint32_t i=0; i<words; i++)
    {
        data[i] = *(address+i);
    }
}
