/*
    This file is part of the AdNW keyboard firmware.

    Copyright 2010-2016 Stefan Fröbe, <frobiac /at/ gmail [d0t] com>

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <util/delay.h>

#include "ps2mouse.h"
#include "trackpoint.h"

volatile uint8_t     scrollcnt;
volatile uint32_t    mouse_timer; /// toggle mouse mode for a specified time
volatile uint16_t    accel; /// toggle mouse mode for a specified time


bool ps2_send_recv(uint8_t send, uint8_t *recv)
{
    if(!g_ps2_connected)
        return false;

    if( ! ps2_host_send(send) ) {
        printf("\nPS/2 failed to send %x.", send); 
        return false;
    }
    *recv = ps2_host_recv_response();

    return true;
}


bool ps2_send_expect(uint8_t send, uint8_t expect)
{
    if(!g_ps2_connected)
        return false;

    uint8_t recv;
    ps2_send_recv(send, &recv);
    if(recv != expect) {
        printf("\nPS/2 %02x -> %02x, expected %02x.", send, recv, expect);
        return false;
    }
    return true;
}

// checking wrapper around ps2_host_recv_response()
bool ps2_read(uint8_t * res) {
    if(!g_ps2_connected)
        return false;

    *res=ps2_host_recv_response();
    return true;
}


/**
 * Setup PS/2 connection
 */ 
bool ps2_init_mouse(void)
{
    g_mouse_enabled = 0;
    scrollcnt = 0;

    uint8_t d[2];

#ifndef BLACKFLAT
    tp_reset();
#endif

    // set temporarily for first try...
    g_ps2_connected=1;
    uint8_t retries=0; 
    while(retries<5 && !ps2_send_expect(0xff, PS2_ACK) ) {
        ++retries;
        printf(".");
    }
    if(retries>=5) {
        // No PS/2 device attached? We should stop all further PS/2 accesses then...
        printf("\nPS/2: No device detected.");
        g_ps2_connected=0; // this stops all tries to send or read 
        return false;
    }

    ps2_read(&d[0]);  // Bat
    ps2_read(&d[1]);  // dev ID

    //Enable Data reporting
    if ( ! ps2_send_expect(0xf4, PS2_ACK) )
        return false;

     //ps2_send_expect(0xe8, PS2_ACK); // set resolution
     //ps2_send_expect(0x01, PS2_ACK); // 8 counts/mm
     //ps2_send_expect(0xf3, PS2_ACK); // set sample rate
     //ps2_send_expect(0x01, PS2_ACK);
    //ps2_host_send(0x64); //200 smaples a second

    //Set remote mode
    if( ! ps2_send_expect(0xf0, PS2_ACK) )
        return false;

    printf("\nTP init: Bat:%02x Id:%02x",d[0],d[1]);

    tp_init();

    /// @todo Set only on successful init
    g_mouse_enabled = 1;

    return true;
}

/*
 *
 */
void ps2_read_mouse(int *dx, int *dy, uint8_t *BTNS )
{
    if(!g_ps2_connected)
        return;

    *BTNS=0;
    int mouseinf;
    {
        if(ps2_send_expect(0xeb, PS2_ACK)) {
            mouseinf=ps2_host_recv_response();
            /// Bits 2 1 0 correspond to  M R L button so swap M&R for RML
            /// @todo Make mouse button order mapping configurable
            *BTNS = ((mouseinf & 0x01) /*LMB*/ << 0) |
                    ((mouseinf & 0x04) /*MMB*/ << 1) |
                    ((mouseinf & 0x02) /*RMB*/ << 2);

            *dx= ps2_host_recv_response();
            *dy= ps2_host_recv_response();

            if(mouseinf&0x10)
                *dx=-(256-*dx);

            if(mouseinf&0x20)
                *dy=-(256-*dy);

            return;
        }
    }
}

/**
 * Rotate 90° by exchanging x and y and changing sign of new x
 */
void rotateXY(int8_t *x, int8_t *y)
{
#ifdef TP_ROTATE
    int8_t tmp = *y;
    *y = *x;
    *x = -tmp;
#endif
}

/**
 * @brief getMouseReport
 * @param MouseReport
 * @return 0 unless mouse report data was changed
 */
uint8_t getMouseReport(USB_WheelMouseReport_Data_t *MouseReport)
{
    if(!g_mouse_enabled)
        return 0;

    int16_t dx=0, dy=0;
    uint8_t ps2_buttons=0;

#ifdef PS2MOUSE
    ps2_read_mouse(&dx, &dy, &ps2_buttons);
#endif

    if( (g_mouse_keys & 0x0F) || (ps2_buttons & 0x07) || (dx!=0) || (dy!=0) ) {
        if(g_mouse_keys_enabled==0) {
            enable_mouse_keys(1);
            accel=0;
        }

        mouse_timer=idle_count;
        if(accel<ACC_RAMPTIME)
            accel++;

        // reset mouse mode after inactivity: idle_count is incremented 61 times per second
        // After last detected trackpoint movement that much time remains to press a button.
    } else {
        if(idle_count-mouse_timer > 1/*seconds*/ *61 ) {
            enable_mouse_keys(0);
            accel=0;
            scrollcnt=0;
        }
        return 0; // no data to send
    }

    if(g_mouse_keys_enabled || ps2_buttons) {
        // factor = 1 + [0..400]*1.5/400 = 1..2.5
        //factor= 1 + accel * (ACC_MAX-1) / ACC_RAMPTIME;

        // keyboard mouse buttons only in mousemode
        if( (ps2_buttons & 0x05)==0x05 || (g_mouse_keys & 0x08)) {
            int8_t sx = (dx&0xFF00) ? -(256-(dx+0x100)) : dx;
            int8_t sy = (dy&0xFF00) ? -(256-(dy+0x100)) : dy;

            // scrollcnt = scrollcnt+abs(sy)+abs(sx); abs(v) = v*((v<0)*(-1)+(v>0));
            scrollcnt += sy*((sy<0)*(-1)+(sy>0)) + sx*((sx<0)*(-1)+(sx>0));

            // limit 10 and emiting as is way to fast in windows.
            if(scrollcnt>10) {
                scrollcnt=0;
                MouseReport->X=0;
                MouseReport->Y=0;
                // only move by 1 ?!
                // factor here had been mapped to 0..0.5 -> use 0.25
                MouseReport->H = -sx>>2;
                MouseReport->V = -sy>>2;
                rotateXY(&MouseReport->V, &MouseReport->H);
            }
        } else { // no scroll-wheel support or not active
            MouseReport->X = -dx;
            MouseReport->Y = dy;
            rotateXY(&(MouseReport->X), &(MouseReport->Y));
            MouseReport->Button = g_mouse_keys & ~(0x08); // do not emit the scroll button
            MouseReport->Button |= ps2_buttons;           // PS/2 buttons if set
        }
        g_mouse_keys=0;

        return sizeof(USB_WheelMouseReport_Data_t);
    }
    return 0;
}

