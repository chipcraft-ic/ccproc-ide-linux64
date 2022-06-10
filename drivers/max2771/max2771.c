/*H*****************************************************************************
*
* Copyright (c) 2020 ChipCraft Sp. z o.o. All rights reserved
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
* File Name : max2771.c
* Author    : Krzysztof Siwiec
* ******************************************************************************
* $Date: 2022-01-10 10:09:36 +0100 (pon, 10 sty 2022) $
* $Revision: 808 $
*H*****************************************************************************/

#include <stdio.h>
#include <board.h>
#include <ccproc.h>
#include <ccproc-amba.h>
#include <ccproc-amba-gpio.h>
#include <ccproc-amba-spi.h>

#include "max2771.h"

//Configure GPIOs for MAX2771 programming
int max2771_gpio_conf()
{
    //set GPIOs as output
    AMBA_GPIO_PTR->OUTSET |= (1 << MAX2771_L1E1_CS) | (1 << MAX2771_L5E5_CS) | (1 << MAX2771_L2E6_CS);
    AMBA_GPIO_PTR->DIRSET |= (1 << MAX2771_L1E1_CS) | (1 << MAX2771_L5E5_CS) | (1 << MAX2771_L2E6_CS);
    return 1;
}

//Return to default GPIOs settings
int max2771_gpio_unconf()
{
    //reset GPIOs
    AMBA_GPIO_PTR->OUTCLR |= (1 << MAX2771_L1E1_CS) | (1 << MAX2771_L5E5_CS) | (1 << MAX2771_L2E6_CS);
    AMBA_GPIO_PTR->DIRCLR |= (1 << MAX2771_L1E1_CS) | (1 << MAX2771_L5E5_CS) | (1 << MAX2771_L2E6_CS);
    return 1;
}

//Configure SPI for MAX2771 programming
int max2771_spi_conf()
{
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->CTRL &= ~SPI_CTRL_MODE_MASK;
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->CTRL |= SPI_MODE0 << SPI_CTRL_MODE_SHIFT;
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->CTRL &= ~SPI_CTRL_FLEN_MASK;
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->CTRL |= SPI_FLEN16 << SPI_CTRL_FLEN_SHIFT;
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->CTRL &= ~SPI_CTRL_PRESCALER_MASK;
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->CTRL |= 16 << SPI_CTRL_PRESC_SHIFT;
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->CTRL |= SPI_CTRL_MSB;
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->CTRL |= SPI_CTRL_EN;
    return 1;
}

//Reset SPI
int max2771_spi_unconf()
{
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->CTRL = 0;
    return 1;
}

//Perform write operation
uint32_t max2771_spi_write(enum max2771_band band, uint32_t address,uint32_t data)
{

    uint32_t watchdog_spi = (10000 / (1000000000 / PERIPH0_FREQ)) + 1;
    while((AMBA_SPI_PTR(MAX2771_SPI_NUM)->STATUS & SPI_STAT_TDRE) == 0 && watchdog_spi > 0 )
    {
        watchdog_spi -= 1;
    }
    
    //chip select gpio number for proper band
    uint8_t max_gpio_cs;
    switch(band)
    {
        case L1E1:
            max_gpio_cs = MAX2771_L1E1_CS;
            break;
        case L5E5:
            max_gpio_cs = MAX2771_L5E5_CS;
            break;
        case L2E6:
            max_gpio_cs = MAX2771_L2E6_CS;
            break;
        default:
            max_gpio_cs = 0;
            return 0;
    }

    //Disable SPI at MAX2771
    AMBA_GPIO_PTR->OUTSET = 1 << max_gpio_cs;

    //Wait more than 100 ns
    watchdog_spi = (100 / (1000000000 / PERIPH0_FREQ)) + 1;
    while(watchdog_spi>0)
    {
        watchdog_spi -= 1;
    }

    //Enable SPI at MAX2771
    AMBA_GPIO_PTR->OUTCLR = 1 << max_gpio_cs;

    //Send frame
    //send address
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->TDR = ((((address & 0x0000000F) << 1) + 0) << 3);

    //wait for transmission end
    watchdog_spi = (100000 / (1000000000 / PERIPH0_FREQ)) + 1;
    while((AMBA_SPI_PTR(MAX2771_SPI_NUM)->STATUS & SPI_STAT_TDRE) == 0 && watchdog_spi > 0 )
    {
        watchdog_spi -= 1;
    }

    //send data MSB
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->TDR = ((data >> 16) & 0x0000FFFF);

    //wait for transmission end
    watchdog_spi = (100000 / (1000000000 / PERIPH0_FREQ)) + 1;
    while((AMBA_SPI_PTR(MAX2771_SPI_NUM)->STATUS & SPI_STAT_TDRE) == 0 && watchdog_spi > 0 )
    {
        watchdog_spi -= 1;
    }

    //send data LSB
    AMBA_SPI_PTR(MAX2771_SPI_NUM)->TDR = data & 0x0000FFFF;

    //wait for transmission end
    watchdog_spi = (100000 / (1000000000 / PERIPH0_FREQ)) + 1;
    while(((AMBA_SPI_PTR(MAX2771_SPI_NUM)->STATUS & SPI_STAT_TDRE) == 0 || (AMBA_SPI_PTR(MAX2771_SPI_NUM)->STATUS & SPI_STAT_TXC) == 0) && watchdog_spi > 0 )
    {
        watchdog_spi -= 1;
    }

    //Disable SPI at MAX2771
    AMBA_GPIO_PTR->OUTSET = 1 << max_gpio_cs;

    return 1;
}

//configure band
uint32_t max2771_conf_band(enum max2771_band band)
{
    max2771_gpio_conf();
    max2771_spi_conf();
    switch(band)
    {
        case L1E1:
            //write register 0
            max2771_spi_write(band,0x0,0xA224063D);
            //write register 1
            max2771_spi_write(band,0x1,0x28550288);
            //write register 2
            max2771_spi_write(band,0x2,0x0EBFB1DC);
            //write register 3
            max2771_spi_write(band,0x3,0x898C0000);
            //write register 4
            max2771_spi_write(band,0x4,0x000BE008);
            //write register 5
            max2771_spi_write(band,0x5,0x0F1CC770);
            //write register 6
            max2771_spi_write(band,0x6,0x08000000);
            //write register 7
            max2771_spi_write(band,0x7,0x010061B2);
            //write register 8
            max2771_spi_write(band,0x8,0x01E0F401);
            //write register 9
            max2771_spi_write(band,0x9,0x00000002);
            //write register 10
            max2771_spi_write(band,0xA,0x010061B0);
            break;
        case L5E5:
            //write register 0
            max2771_spi_write(band,0x0,0xBEA4B63D);
            //write register 1
            max2771_spi_write(band,0x1,0x28550288);
            //write register 2
            max2771_spi_write(band,0x2,0x0EAF31DC);
            //write register 3
            max2771_spi_write(band,0x3,0x998C0008);
            //write register 4
            max2771_spi_write(band,0x4,0x0047E040);
            //write register 5
            max2771_spi_write(band,0x5,0x0F565570);
            //write register 6
            max2771_spi_write(band,0x6,0x08000000);
            //write register 7
            max2771_spi_write(band,0x7,0x110061B2);
            //write register 8
            max2771_spi_write(band,0x8,0x01E0F401);
            //write register 9
            max2771_spi_write(band,0x9,0x00C00002);
            //write register 10
            max2771_spi_write(band,0xA,0x010061B0);
            break;
        case L2E6:
            //write register 0
            max2771_spi_write(band,0x0,0xA224063D);
            //write register 1
            max2771_spi_write(band,0x1,0x28550288);
            //write register 2
            max2771_spi_write(band,0x2,0x0EAFB1DC);
            //write register 3
            max2771_spi_write(band,0x3,0x898C0000);
            //write register 4
            max2771_spi_write(band,0x4,0x000BE008);
            //write register 5
            max2771_spi_write(band,0x5,0x0F1CC770);
            //write register 6
            max2771_spi_write(band,0x6,0x08000000);
            //write register 7
            max2771_spi_write(band,0x7,0x010061B6);
            //write register 8
            max2771_spi_write(band,0x7,0x01E0F401);
            //write register 9
            max2771_spi_write(band,0x7,0x00000002);
            //write register 10
            max2771_spi_write(band,0xA,0x010061B4);
            break;
        default:
            max2771_gpio_unconf();
            max2771_spi_unconf();
            return 0;

    }
    max2771_gpio_unconf();
    max2771_spi_unconf();
    return 1;
}

