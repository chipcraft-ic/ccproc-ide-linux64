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
* File Name : main.c
* Author    : Mateusz Jemielity
* ******************************************************************************
* $Date: 2025-01-14 20:57:02 +0100 (wto, 14 sty 2025) $
* $Revision: 1128 $
*H*****************************************************************************/

#include "board.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

/* UART settings */
static int const data_uart = 3;
static uint32_t const baudrate = STDIO_BAUDRATE;
static int const flags = 0;

typedef enum {
    RX = 0U,
    TX = 1U,
    STAGE_MAX = 2U
} stage;

static char const * const stage2string[ STAGE_MAX ] = {
    [ RX ] = "RX",
    [ TX ] = "TX"
};

#define PING_PONG_MESSAGE_LENGTH 4U

static char const tx_data[ STAGE_MAX ][ PING_PONG_MESSAGE_LENGTH + 1U ] =
{
    [ RX ] = "pong",
    [ TX ] = "ping"
};
static char rx_data[ PING_PONG_MESSAGE_LENGTH + 1U ];

static unsigned stage_counter;

int uart_init_blocking(int uart, uint32_t baudrate, int rtscts);
int uart_write_blocking(int uart, char data);
int uart_read_blocking(int uart, char *data);

typedef bool (* fn)( stage const type );

static bool
rx( stage const type )
{
    int result = -1;

    memset( rx_data, '\0', sizeof( rx_data ));

    for ( size_t i = 0U; i < ( sizeof( rx_data ) - 1U ); ++i ) {
#if PING_PONG_DEBUG
        printf( "[ %s ] receiving character\n", stage2string[ type ] );
        result = 0;
#else /* ! PING_PONG_DEBUG */
        result = uart_read_blocking( data_uart, &( rx_data[ i ] ));
#endif /* PING_PONG_DEBUG */
        if ( 0 != result ) {
            printf(
                "[ %s ] transmission failure, counter: %u, character: %u\n",
                stage2string[ type ],
                stage_counter,
                ( unsigned ) i
            );
            goto failure_rx;
        }
    }

    printf( "[ %s ] received: %s\n", stage2string[ type ], rx_data );

failure_rx:
    return ( result == 0 );
}

static bool
tx( stage const type )
{
    int result = -1;

    for ( size_t i = 0U; i < ( sizeof( tx_data[ type ] ) - 1U ); ++i ) {
#if PING_PONG_DEBUG
        printf(
            "[ %s ] sending: %c\n",
            stage2string[ type ],
            tx_data[ type ][ i ]
        );
        result = 0;
#else /* ! PING_PONG_DEBUG */
        result = uart_write_blocking( data_uart, tx_data[ type ][ i ] );
#endif /* PING_PONG_DEBUG */
        if ( 0 != result ) {
            printf(
                "[ %s ] transmission failure, counter: %u, character: %c\n",
                stage2string[ type ],
                stage_counter,
                tx_data[ type ][ i ]
            );
            goto failure_tx;
        }
    }

    printf( "[ %s ] transmitted: %s\n", stage2string[ type ], tx_data[ type ] );

failure_tx:
    return ( result == 0 );
}

static fn const action[ STAGE_MAX ] ={
    [ RX ] = rx,
    [ TX ] = tx
};

static stage
next( stage const current )
{
    static stage const swap[ STAGE_MAX ] = {
        [ RX ] = TX,
        [ TX ] = RX
    };
    return swap[ current ];
}

int
main( void )
{
    {
        int const init = uart_init_blocking( data_uart, baudrate, flags );
        if ( 0 != init ) {
            puts( "failure initializing data UART" );
            goto failure_init;
        }
    }

    stage_counter = 0U;
    stage type = PING_PONG_TRX;
    bool loop = false;
    do {
        loop = action[ type ]( PING_PONG_TRX );
        type = next( type );
        printf( "transmission count: %u\n", stage_counter );
        ++stage_counter;
    } while ( loop );

    puts( "connection interrupted" );

failure_init:
    return 0;
}

