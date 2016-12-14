/*********************************************************************************
 * Title: PS/2 Library
 * Author: Akshay Srinivasan<akshaysrinivasan@nitk.ac.in>
 * Date: 22 June 2009
 * Software: AVR-GCC 4.3.2

 *-------------------------------------------------------------------------------------
 * "THE BEER-WARE LICENSE" (Revision 42):
 * <akshaysrinivasan@gmail.com> wrote this file.  As long as you retain this notice you
 * can do whatever you want with this stuff. If we meet some day, and you think
 * this stuff is worth it, you can buy me a beer in return.        Akshay Srinivasan
 *-------------------------------------------------------------------------------------

 DESCRIPTION
    This library provides an abstraction layer for the PS/2 protocol. This library
    provides functions for receiving and sending bytes via PS/2. This library can
    be used to read and write data in PS/2 devices, although interpreting the data
    is left for you to do.

    For more information goto,
    http://computer-engineering.org/ps2protocol/
**********************************************************************************/

#include<avr/io.h>
#include<util/delay.h>

#include "config.h"
#include "pstwo.h"

// >42590 to register connected TP correctly
// <50000 to not hang if no TP connected
#define NOP_MAX_CNT 48000
volatile uint32_t cnt = 0;

void data(uint8_t x)
{
    PS2_DATA_DDR |= (1 << PS2_DATA_BIT);
    if(x==0)
        PS2_DATA_PORT &= ~(1 << PS2_DATA_BIT);
    else if(x==1)
        PS2_DATA_PORT |= (1 << PS2_DATA_BIT);
    return;
}

void clk(uint8_t x)
{
    PS2_CLOCK_DDR |= (1 << PS2_CLOCK_BIT);
    if(x==0)
        PS2_CLOCK_PORT &= ~(1 << PS2_CLOCK_BIT);
    else if(x==1)
        PS2_CLOCK_PORT |= (1 << PS2_CLOCK_BIT);
    return;
}



void serout(uint8_t bit)
{
    cnt=0;
    while(CLK && ++cnt < NOP_MAX_CNT) {
        __asm__("nop");
    }
    data(bit);
    cnt = 0;
    while(!CLK && ++cnt < NOP_MAX_CNT) {
        __asm__("nop");
    }
}

uint8_t serin()
{
    uint8_t state;
    cnt=0;
    while(CLK && ++cnt < NOP_MAX_CNT) {
        __asm__("nop");
    }
    state = DATA;
    cnt = 0;
    while(!CLK && ++cnt < NOP_MAX_CNT) {
        __asm__("nop");
    }
    return state;
}

uint8_t oparity(uint8_t byte)
{
    uint8_t par=1;
    par ^= ((byte & (1 << 0)) >> 0);
    par ^= ((byte & (1 << 1)) >> 1);
    par ^= ((byte & (1 << 2)) >> 2);
    par ^= ((byte & (1 << 3)) >> 3);
    par ^= ((byte & (1 << 4)) >> 4);
    par ^= ((byte & (1 << 5)) >> 5);
    par ^= ((byte & (1 << 6)) >> 6);
    par ^= ((byte & (1 << 7)) >> 7);
    return par;
}



bool ps2_host_send(uint8_t byte)
{
    /// @todo Error checking in PS/2 code
    uint8_t sent_retries=0;
    uint8_t parity = oparity(byte);

    do {
        clk(0);
        _delay_us(PS2_DELAY);
        data(0); //Start
        _delay_us(PS2_DELAY/2);
        clk(1);
        PS2_CLOCK_DDR &= ~(1 << PS2_CLOCK_BIT); // Release clock
        PS2_CLOCK_PORT |= (1 << PS2_CLOCK_BIT); //Set the pull up on Clock

        /////////////
        serout((byte & (1 << 0)) >> 0);
        serout((byte & (1 << 1)) >> 1);
        serout((byte & (1 << 2)) >> 2);
        serout((byte & (1 << 3)) >> 3);
        serout((byte & (1 << 4)) >> 4);
        serout((byte & (1 << 5)) >> 5);
        serout((byte & (1 << 6)) >> 6);
        serout((byte & (1 << 7)) >> 7);
        serout(parity);

        serout(1); //Stop

        PS2_DATA_DDR &= ~(1 << PS2_DATA_BIT); //Release the Data line
        PS2_DATA_PORT |= (1 << PS2_DATA_BIT); //Set the pull up on Data

        sent_retries++;
    } while (serin() != 0 && sent_retries < 5 );

    return (sent_retries<5);
}

uint8_t ps2_host_recv_response(void)
{
    uint8_t byte=0,par;
    serin(); //Start
    byte |= (serin() << 0);
    byte |= (serin() << 1);
    byte |= (serin() << 2);
    byte |= (serin() << 3);
    byte |= (serin() << 4);
    byte |= (serin() << 5);
    byte |= (serin() << 6);
    byte |= (serin() << 7);
    par = serin(); //Parity
    serin(); //Stop

    if(par != oparity(byte))
        ps2_host_send(0xfe); //Resend

    return byte;
}
