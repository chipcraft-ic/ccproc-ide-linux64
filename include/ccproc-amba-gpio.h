/* ----------------------------------------------------------------------
*
* Copyright (c) 2017 ChipCraft Sp. z o.o. All rights reserved
*
* $Date: 2019-12-19 12:13:42 +0100 (czw, 19 gru 2019) $
* $Revision: 491 $
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
 * @file            ccproc-amba-gpio.h
 * @brief           CC Processor AMBA GPIO definitions
 * @author          Rafal Harabien
 *
 * @addtogroup      CCAMBA
 * AMBA Bus Peripherials
 * @{
 */

#ifndef __CCPROC_AMBA_GPIO_H
#define __CCPROC_AMBA_GPIO_H

#include <stdint.h>

#ifdef CCPROC_SDK
 #include "ccproc.h"
#endif

/************************//**
 * @defgroup gpio GPIO Controller
 * GPIO Controller registers and definitions
 * @{
 *//************************/

/** GPIO Registers */
typedef struct
{
    uint32_t DIR;            /*!< Direction Register                    */
    uint32_t DIRSET;         /*!< Set Direction Register                */
    uint32_t DIRCLR;         /*!< Clear Direction Register              */
    uint32_t DIRTGL;         /*!< Toggle Direction Register             */
    uint32_t OUT;            /*!< Output Register                       */
    uint32_t OUTSET;         /*!< Set Output Register                   */
    uint32_t OUTCLR;         /*!< Clear Output Register                 */
    uint32_t OUTTGL;         /*!< Toggle Output Register                */
    uint32_t IN;             /*!< Input Register                        */
    uint32_t INT0;           /*!< Interrupt 0 Register                  */
    uint32_t INT1;           /*!< Interrupt 1 Register                  */
    uint32_t IRQF;           /*!< Interrupt Flags Register              */
    uint32_t CTRL;           /*!< Control Register                      */
    uint32_t IRQMAP;         /*!< Interrupt Mapping Register            */
    uint32_t INVERT;         /*!< Invert I/O Register                   */
    uint32_t SLEW_RATE;      /*!< High Slew Rate Register               */
    uint32_t HYST;           /*!< Hysteresis Register                   */
    uint32_t SENSE_LO;       /*!< Sense Register for pins 0-15          */
    uint32_t SENSE_HI;       /*!< Sense Register for pins 16-31         */
    uint32_t _reserved[2];
    uint32_t PULL_LO;        /*!< Pull Config Register for pins 0-15    */
    uint32_t PULL_HI;        /*!< Pull Config Register for pins 16-31   */
    uint32_t DRIVER_LO;      /*!< Driver Config Register for pins 0-15  */
    uint32_t DRIVER_HI;      /*!< Driver Config Register for pins 16-31 */
    uint32_t ALTER_LO;       /*!< Alternative Function Config Register  */
    uint32_t ALTER_HI;       /*!< Alternative Function Config Register  */
} amba_gpio_t;

#ifdef CCPROC_SDK
 static volatile amba_gpio_t * const AMBA_GPIO_PTR = (amba_gpio_t*)AMBA_GPIO_BASE; /*!< GPIO Controller pointer */
#endif

/** GPIO Control flags */
enum
{
    GPIO_CTRL_EN = 0x01,  /*!< GPIO Enable */
};

/** GPIO Sense Config */
enum
{
    GPIO_SENSE_RISING   = 0x01,  /*!< Rising Edge Detection             */
    GPIO_SENSE_FALLING  = 0x02,  /*!< Falling Edge Detection            */
    GPIO_SENSE_BOTH     = 0x03,  /*!< Rising and Falling Edge Detection */
    GPIO_SENSE_LO       = 0x00,  /*!< Low State Detection               */
};

/** GPIO Pull Config */
enum
{
    GPIO_PULL_NONE       = 0x00,  /*!< No Pull    */
    GPIO_PULL_UP         = 0x01,  /*!< Pull Up    */
    GPIO_PULL_DOWN       = 0x02,  /*!< Pull Down  */
    GPIO_PULL_BUS_KEEPER = 0x03,  /*!< Bus Keeper */
};

/** GPIO Alternative Functions Config */
enum
{
    GPIO_ALTER_GPIO    = 0x00,  /*!< GPIO                      */
    GPIO_ALTER_0       = 0x01,  /*!< Alternative function 0    */
    GPIO_ALTER_1       = 0x02,  /*!< Alternative function 1    */
    GPIO_ALTER_2       = 0x03,  /*!< Alternative function 2    */
};

/** GPIO Drive Strength Config */
enum
{
    GPIO_DRIVE_0    = 0x00,  /*!< Base                      */
    GPIO_DRIVE_1    = 0x01,  /*!< Base x 2                  */
    GPIO_DRIVE_2    = 0x02,  /*!< Base x 4                  */
    GPIO_DRIVE_3    = 0x03,  /*!< Base x 6                  */
};

/** GPIO config macro */
#define GPIO_CONFIG_MASK(gpio, function) (function << ((gpio % 16) << 1))  /*!< GPIO alternative, sense and pull config macro */

/** @} */

#endif /* __CCPROC_AMBA_GPIO_H */
/** @} */
