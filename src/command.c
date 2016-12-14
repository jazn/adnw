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

#include "global_config.h"
#include "command.h"
#include "hid_usage.h"
#include "keyboard_class.h"
#include "keymap.h"
#include "trackpoint.h"
#include "jump_bootloader.h"
#include "passhash/passhash.h"
#include "_private_data.h"

#ifdef PS2MOUSE
    #include "trackpoint.h"
#endif
#include "macro.h"

bool g_cmd_mode_active=false;

#define TAGLEN 32
char tag[TAGLEN+1];
char ph_master_pw[TAGLEN+1];

led_t led_save;

/// possible subcommands
enum {
    SUB_NONE=0,
    SUB_TP,
    SUB_LAYOUT,
    SUB_MACRO,
    SUB_MACRO_REC,
    SUB_PASSHASH,
    SUB_CONFIG,
    SUB_END
};

static uint8_t subcmd;           ///< currently active subcommand

#ifdef PH_ENABLED
    static bool passhash_pw_entered = false;
#endif

void setCommandMode(bool on)
{
    if(on!=g_cmd_mode_active) {
        if(on) {
            led_save = g_led;
            g_led = (led_t) { .brightness=5, .on=30,  .off=30 };
        } else {
            g_led = led_save;
        }

        g_cmd_mode_active=on;
        subcmd = SUB_NONE;
    }
}

bool commandMode(void) { return g_cmd_mode_active; }
void handleSubCmd(char c);


/** Called when command mode is active.
 *
 *  First pressed key is mapped to first layer defined and evaluated. Use only a-z and 0-9 for commands, others exit this mode.
 *
 *  @todo: leave automatically on unknown command or timeout, or signal mode through leds.
 *
 *  @return: bool whether we handled the command, e.g. false means print character normally
 *
 */
bool handleCommand(uint8_t hid_now, uint8_t mod_now)
{
    if( !commandMode() )
        return false;

    // generally return "true" below as we are in command mode which should not echo.

    static uint8_t hid_prev, mod_prev, act_prev;
    uint8_t act_now = activeKeys.keycnt;

    if((hid_now==hid_prev) && (mod_now==mod_prev) && (act_now==act_prev))
        return true;

    // ok, something changed:
    uint8_t hid = hid_prev;
    uint8_t mod = mod_prev; // these may be used later
    hid_prev=hid_now; mod_prev=mod_now; act_prev = act_now;

    if( !(hid_now==0 && hid != 0) ) {
        // no release detected
        return true;
    }

    if(macroRecording()) {
        macro_key(hid,mod);
        return false; // macro should be echoed!
    }

    char curChar = hid2asciicode(hid, mod);

    if(subcmd) {
        handleSubCmd(curChar);
        return true;
    }

    switch(curChar) {
#ifdef PINKYDROP
        case 'd':
            g_pinkydrop = g_pinkydrop ? 0 : 1;
            printf("Pinkydrop %d\n", g_pinkydrop);
            eeprom_write_byte(&ee_pinkyDrop, g_pinkydrop);
            setCommandMode(false);
            break;
#endif
        case 'v':
            printf("AdNW %s\n", FW_VERSION);
            setCommandMode(false);
            break;
        case 'q':
            setCommandMode(false);
            break;
        case 'b':
            jump_bootloader();
            break;
        case 'c': 
            subcmd=SUB_CONFIG;
            break;
            
/// @todo Trackpoint availability
#ifdef PS2MOUSE
        case 't':
            ps2_init_mouse();
            setCommandMode(false);
            break;
#endif

#ifdef ALTERNATE_LAYER
        case 'l':
            g_alternateLayer = g_alternateLayer ? 0 : 1;
            eeprom_write_byte(&ee_alternateLayer,g_alternateLayer);
            printf("AltL %s\n", g_alternateLayer ? "on" : "off");
            setCommandMode(false);
            break;
#endif

#ifdef PS2MOUSE
        case 'm':
            // @TODO  only activate if init worked!
            g_mouse_enabled = g_mouse_enabled > 0 ? 0 : 1;
            printf("Mouse %sabled\n", g_mouse_enabled ? "en" : "dis");
            setCommandMode(false);
            break;
#endif
        case 'x':
            subcmd=SUB_MACRO;
            break;
        case 'r':
            printf("Rec macro\n");
            subcmd=SUB_MACRO_REC;
            break;
        case 'h':
            /// only activate passhash generation if defined during compile.
#ifdef PH_ENABLED
            memset(tag,0,TAGLEN);
            subcmd=SUB_PASSHASH;
#else
            printf("PassHash inactive\n");
            setCommandMode(false);
#endif
            break;

        default:
            setCommandMode(false);
            break;
    }

    return true;
}


void handleSubCmd(char c)
{
    switch( subcmd ) {
        case SUB_MACRO:
            printMacro( (((uint8_t)c)%MACROCOUNT) );
            setCommandMode(false);
            break;
        case SUB_MACRO_REC:
            // stay in command mode until macro is read.
            if(!setMacroRecording(((uint8_t)c)%MACROCOUNT))
                setCommandMode(false);
            break;
#ifdef PH_ENABLED
        case SUB_PASSHASH:
            // press return immediately to unset password
            // on first call enter password
            // on subsequent runs enter tag [len [type]]
            //
            // read until return=10 is pressed or maximum length reached
            if( (uint8_t)(c) != 10 && strlen(tag) < TAGLEN) {
                tag[strlen(tag)]= c;
            } else {
                setCommandMode(false);
                if(strlen(tag) == 0) {
                    memset(ph_master_pw,0,TAGLEN);
                    passhash_pw_entered = false;
                    printf("PH clear\n");
                    return;
                }

                char password[PH_MAX_LEN+1];
                if( passhash_pw_entered == false ) {
                    sscanf(tag, "%s", ph_master_pw);
                    if(verifyHash(PH_PRIV_KEY, ph_master_pw,  PH_TEST /*tag len type hash*/ ))
                        passhash_pw_entered = true;

                    return;
                }

                uint16_t type=PH_TYPE_ALNUMSYM;
                uint16_t len=12;
                char splitTag[TAGLEN+1];

                // parse input into "tag len type"
                sscanf(tag,"%s %u %u", splitTag, &len, &type);
                if(len<PH_MIN_LEN||len>PH_MAX_LEN)
                    len=12;
                if(type<PH_TYPE_ALNUMSYM||type>PH_TYPE_NUM)
                    type=PH_TYPE_ALNUMSYM;
                /// PH_PRIV_KEY  "secret" is the Twik private key of a profile
                /// ph_master_pw "key" is the master password needed to create pass hashes for a tag
                uint8_t ret = passHash(password, (uint8_t)len, (uint8_t)type, PH_PRIV_KEY, ph_master_pw, splitTag);
                if(ret==0) {
                    //printf("PH len=%d tag=%s type=%d = %s\n", len, splitTag, type, password);
                    setOutputString(password);
                }
                memset(tag,0,TAGLEN);
            }
            break;
#endif
        
        case SUB_CONFIG:
            #ifdef HAS_LED
                printf("\nLED: %d/%d@%d",led_save.on, led_save.off, led_save.brightness);
            #endif
            #ifdef PS2MOUSE
                printf("\nTP:%d/%d",g_tp_sens_low, g_tp_sens);
            #endif

            switch(c) {

              #ifdef PS2MOUSE
                // change sensitivity for initial and normal operation
                ///@TODO generic interface, always allow '0' (no %256)
                case '.': g_tp_sens = (g_tp_sens+5) % 256; break;
                case 'a': g_tp_sens = (g_tp_sens-5) % 256; break;
                case ':': g_tp_sens_low = (g_tp_sens_low+1) % 256; break;
                case 'A': g_tp_sens_low = (g_tp_sens_low-1) % 256;break;

                case 'x': tp_ram_toggle(0x2C, (1<<TP_FLIPX));  tp_read_config(); break;
                case 'y': tp_ram_toggle(0x2C, (1<<TP_FLIPY));  tp_read_config(); break;
                case 'X': tp_ram_toggle(0x2C, (1<<TP_SWAPXY)); tp_read_config(); break;
                case 'Y': tp_ram_toggle(0x2C, (1<<TP_PTS));    tp_read_config(); break;
              #endif

              #ifdef HAS_LED
                // Operate on the saved config that will be restored when leaving command mode
                case 'j': led_save.off = (led_save.off-5) % 256; break;
                case 'J': led_save.off = (led_save.off+5) % 256; break;
                case 'o': led_save.on = (led_save.on-5) % 256; break;
                case 'O': led_save.on = (led_save.on+5) % 256; break;
                case 'e': led_save.brightness = (led_save.brightness-5) % 256; break;
                case 'E': led_save.brightness = (led_save.brightness+5) % 256; break;
              #endif

                case 'q':
                default:
                    setCommandMode(false);
                    break;    
            }
            break; // allow consecutive changes to variables

        default:
            setCommandMode(false);
            break;
    }
}


