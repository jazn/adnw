/*
                   The HumbleHacker Keyboard Project
                 Copyright © 2008-2010, David Whetstone
               david DOT whetstone AT humblehacker DOT com

  This file is a part of The HumbleHacker Keyboard Project.

  The HumbleHacker Keyboard Project is free software: you can redistribute
  it and/or modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  The HumbleHacker Keyboard Project is distributed in the hope that it will
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
  Public License for more details.

  You should have received a copy of the GNU General Public License along
  with The HumbleHacker Keyboard Project.  If not, see
  <http://www.gnu.org/licenses/>.

*/

#ifndef __HHSTDIO_H__
#define __HHSTDIO_H__

#include <stdio.h>
#include <stdbool.h>
#include <LUFA/Drivers/USB/Class/HID.h>

void stdio_init(void);
void stdio_fill_report(char ch, USB_KeyboardReport_Data_t *report);
bool stdout_is_empty(void);
bool stdout_is_full(void);
char stdout_popchar(void);

static const USB_KeyboardReport_Data_t ascii_table[];


/*
                    The HumbleHacker Keyboard Project
                 Copyright © 2008-2010, David Whetstone
               david DOT whetstone AT humblehacker DOT com

  This file is a part of The HumbleHacker Keyboard Project.

  The HumbleHacker Keyboard Project is free software: you can redistribute
  it and/or modify it under the terms of the GNU General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  The HumbleHacker Keyboard Project is distributed in the hope that it will
  be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General
  Public License for more details.

  You should have received a copy of the GNU General Public License along
  with The HumbleHacker Keyboard Project.  If not, see
  <http://www.gnu.org/licenses/>.

*/

/*
   The largest HID usage code is AC_Distribute_Vertically from the Consumer
   Control usage page.  Its id is 0x29c, which requires 10 bits.  The largest
   usage page used by a keyboard, on the other hand, is 0x0c, which requires
   only 4 bits.  So we pack the usage id in the lower 10 bits of a 16 bit int,
   and the usage page in the upper 6 bits.
*/

#define MAKE_USAGE(page,id) (((page)<<10)|(id))
#define USAGE_ID(usage)     (usage&~(0xffff<<10))
#define USAGE_PAGE(usage)   (usage>>10)

typedef uint8_t  UsagePage;
typedef uint8_t  UsageID;
typedef enum {
    HID_USAGE_NONE = 0UL,

    /* USAGE PAGE:  Keyboard_and_Keypad */
#define HID_USAGE_PAGE_KEYBOARD_AND_KEYPAD 0x07

    HID_USAGE_RESERVED__LPARENNO_EVENT_INDICATED_RPAREN = MAKE_USAGE(0x07, 0x00),
    HID_USAGE_ERRORROLLOVER = MAKE_USAGE(0x07, 0x01),
    HID_USAGE_POSTFAIL = MAKE_USAGE(0x07, 0x02),
    HID_USAGE_ERRORUNDEFINED = MAKE_USAGE(0x07, 0x03),
    HID_USAGE_A_AND_A = MAKE_USAGE(0x07, 0x04),
    HID_USAGE_B_AND_B = MAKE_USAGE(0x07, 0x05),
    HID_USAGE_C_AND_C = MAKE_USAGE(0x07, 0x06),
    HID_USAGE_D_AND_D = MAKE_USAGE(0x07, 0x07),
    HID_USAGE_E_AND_E = MAKE_USAGE(0x07, 0x08),
    HID_USAGE_F_AND_F = MAKE_USAGE(0x07, 0x09),
    HID_USAGE_G_AND_G = MAKE_USAGE(0x07, 0x0a),
    HID_USAGE_H_AND_H = MAKE_USAGE(0x07, 0x0b),
    HID_USAGE_I_AND_I = MAKE_USAGE(0x07, 0x0c),
    HID_USAGE_J_AND_J = MAKE_USAGE(0x07, 0x0d),
    HID_USAGE_K_AND_K = MAKE_USAGE(0x07, 0x0e),
    HID_USAGE_L_AND_L = MAKE_USAGE(0x07, 0x0f),
    HID_USAGE_M_AND_M = MAKE_USAGE(0x07, 0x10),
    HID_USAGE_N_AND_N = MAKE_USAGE(0x07, 0x11),
    HID_USAGE_O_AND_O = MAKE_USAGE(0x07, 0x12),
    HID_USAGE_P_AND_P = MAKE_USAGE(0x07, 0x13),
    HID_USAGE_Q_AND_Q = MAKE_USAGE(0x07, 0x14),
    HID_USAGE_R_AND_R = MAKE_USAGE(0x07, 0x15),
    HID_USAGE_S_AND_S = MAKE_USAGE(0x07, 0x16),
    HID_USAGE_T_AND_T = MAKE_USAGE(0x07, 0x17),
    HID_USAGE_U_AND_U = MAKE_USAGE(0x07, 0x18),
    HID_USAGE_V_AND_V = MAKE_USAGE(0x07, 0x19),
    HID_USAGE_W_AND_W = MAKE_USAGE(0x07, 0x1a),
    HID_USAGE_X_AND_X = MAKE_USAGE(0x07, 0x1b),
    HID_USAGE_Y_AND_Y = MAKE_USAGE(0x07, 0x1c),
    HID_USAGE_Z_AND_Z = MAKE_USAGE(0x07, 0x1d),
    HID_USAGE_1_AND__EXCLAMATION = MAKE_USAGE(0x07, 0x1e),
    HID_USAGE_2_AND__ATSIGN = MAKE_USAGE(0x07, 0x1f),
    HID_USAGE_3_AND__POUND = MAKE_USAGE(0x07, 0x20),
    HID_USAGE_4_AND__DOLLAR = MAKE_USAGE(0x07, 0x21),
    HID_USAGE_5_AND__PERCENT = MAKE_USAGE(0x07, 0x22),
    HID_USAGE_6_AND__CARET = MAKE_USAGE(0x07, 0x23),
    HID_USAGE_7_AND__AMPERSAND = MAKE_USAGE(0x07, 0x24),
    HID_USAGE_8_AND__ASTERISK = MAKE_USAGE(0x07, 0x25),
    HID_USAGE_9_AND__LPAREN = MAKE_USAGE(0x07, 0x26),
    HID_USAGE_0_AND__RPAREN = MAKE_USAGE(0x07, 0x27),
    HID_USAGE_RETURN_OR_ENTER = MAKE_USAGE(0x07, 0x28),
    HID_USAGE_ESCAPE = MAKE_USAGE(0x07, 0x29),
    HID_USAGE_BACKSPACE = MAKE_USAGE(0x07, 0x2a),
    HID_USAGE_TAB = MAKE_USAGE(0x07, 0x2b),
    HID_USAGE_SPACEBAR = MAKE_USAGE(0x07, 0x2c),
    HID_USAGE__MINUS_AND_UNDERSCORE = MAKE_USAGE(0x07, 0x2d),
    HID_USAGE__EQUALS_AND__PLUS = MAKE_USAGE(0x07, 0x2e),
    HID_USAGE__LSQUAREBRACKET_AND__LCURLYBRACE = MAKE_USAGE(0x07, 0x2f),
    HID_USAGE__RSQUAREBRACKET_AND__RCURLYBRACE = MAKE_USAGE(0x07, 0x30),
    HID_USAGE__BACKSLASH_AND__PIPE = MAKE_USAGE(0x07, 0x31),
    HID_USAGE_NONUS__POUND_AND__TILDE = MAKE_USAGE(0x07, 0x32),
    HID_USAGE__SEMICOLON_AND__COLON = MAKE_USAGE(0x07, 0x33),
    HID_USAGE_SQUOTE_AND_DQUOTE = MAKE_USAGE(0x07, 0x34),
    HID_USAGE__BACKTICK_AND__TILDE = MAKE_USAGE(0x07, 0x35),
    HID_USAGE__COMMA_AND__LESSTHAN = MAKE_USAGE(0x07, 0x36),
    HID_USAGE__PERIOD_AND__GREATERTHAN = MAKE_USAGE(0x07, 0x37),
    HID_USAGE__SLASH_AND__QUESTION = MAKE_USAGE(0x07, 0x38),
    HID_USAGE_CAPS_LOCK = MAKE_USAGE(0x07, 0x39),
    HID_USAGE_F1 = MAKE_USAGE(0x07, 0x3a),
    HID_USAGE_F2 = MAKE_USAGE(0x07, 0x3b),
    HID_USAGE_F3 = MAKE_USAGE(0x07, 0x3c),
    HID_USAGE_F4 = MAKE_USAGE(0x07, 0x3d),
    HID_USAGE_F5 = MAKE_USAGE(0x07, 0x3e),
    HID_USAGE_F6 = MAKE_USAGE(0x07, 0x3f),
    HID_USAGE_F7 = MAKE_USAGE(0x07, 0x40),
    HID_USAGE_F8 = MAKE_USAGE(0x07, 0x41),
    HID_USAGE_F9 = MAKE_USAGE(0x07, 0x42),
    HID_USAGE_F10 = MAKE_USAGE(0x07, 0x43),
    HID_USAGE_F11 = MAKE_USAGE(0x07, 0x44),
    HID_USAGE_F12 = MAKE_USAGE(0x07, 0x45),
    HID_USAGE_PRINTSCREEN = MAKE_USAGE(0x07, 0x46),
    HID_USAGE_SCROLL_LOCK = MAKE_USAGE(0x07, 0x47),
    HID_USAGE_KEYBOARD_PAUSE = MAKE_USAGE(0x07, 0x48),
    HID_USAGE_INSERT = MAKE_USAGE(0x07, 0x49),
    HID_USAGE_HOME = MAKE_USAGE(0x07, 0x4a),
    HID_USAGE_PAGEUP = MAKE_USAGE(0x07, 0x4b),
    HID_USAGE_DELETE_FORWARD = MAKE_USAGE(0x07, 0x4c),
    HID_USAGE_END = MAKE_USAGE(0x07, 0x4d),
    HID_USAGE_PAGEDOWN = MAKE_USAGE(0x07, 0x4e),
    HID_USAGE_RIGHTARROW = MAKE_USAGE(0x07, 0x4f),
    HID_USAGE_LEFTARROW = MAKE_USAGE(0x07, 0x50),
    HID_USAGE_DOWNARROW = MAKE_USAGE(0x07, 0x51),
    HID_USAGE_UPARROW = MAKE_USAGE(0x07, 0x52),
    HID_USAGE_KEYPAD_NUM_LOCK_AND_CLEAR = MAKE_USAGE(0x07, 0x53),
    HID_USAGE_KEYPAD__SLASH = MAKE_USAGE(0x07, 0x54),
    HID_USAGE_KEYPAD__ASTERISK = MAKE_USAGE(0x07, 0x55),
    HID_USAGE_KEYPAD__MINUS = MAKE_USAGE(0x07, 0x56),
    HID_USAGE_KEYPAD__PLUS = MAKE_USAGE(0x07, 0x57),
    HID_USAGE_KEYPAD_ENTER = MAKE_USAGE(0x07, 0x58),
    HID_USAGE_KEYPAD_1_AND_END = MAKE_USAGE(0x07, 0x59),
    HID_USAGE_KEYPAD_2_AND_DOWN_ARROW = MAKE_USAGE(0x07, 0x5a),
    HID_USAGE_KEYPAD_3_AND_PAGEDN = MAKE_USAGE(0x07, 0x5b),
    HID_USAGE_KEYPAD_4_AND_LEFT_ARROW = MAKE_USAGE(0x07, 0x5c),
    HID_USAGE_KEYPAD_5 = MAKE_USAGE(0x07, 0x5d),
    HID_USAGE_KEYPAD_6_AND_RIGHT_ARROW = MAKE_USAGE(0x07, 0x5e),
    HID_USAGE_KEYPAD_7_AND_HOME = MAKE_USAGE(0x07, 0x5f),
    HID_USAGE_KEYPAD_8_AND_UP_ARROW = MAKE_USAGE(0x07, 0x60),
    HID_USAGE_KEYPAD_9_AND_PAGEUP = MAKE_USAGE(0x07, 0x61),
    HID_USAGE_KEYPAD_0_AND_INSERT = MAKE_USAGE(0x07, 0x62),
    HID_USAGE_KEYPAD__PERIOD_AND_DELETE = MAKE_USAGE(0x07, 0x63),
    HID_USAGE_NONUS__BACKSLASH_AND__PIPE = MAKE_USAGE(0x07, 0x64),
    HID_USAGE_APPLICATION = MAKE_USAGE(0x07, 0x65),
    HID_USAGE_KEYBOARD_POWER = MAKE_USAGE(0x07, 0x66),
    HID_USAGE_KEYPAD__EQUALS = MAKE_USAGE(0x07, 0x67),
    HID_USAGE_F13 = MAKE_USAGE(0x07, 0x68),
    HID_USAGE_F14 = MAKE_USAGE(0x07, 0x69),
    HID_USAGE_F15 = MAKE_USAGE(0x07, 0x6a),
    HID_USAGE_F16 = MAKE_USAGE(0x07, 0x6b),
    HID_USAGE_F17 = MAKE_USAGE(0x07, 0x6c),
    HID_USAGE_F18 = MAKE_USAGE(0x07, 0x6d),
    HID_USAGE_F19 = MAKE_USAGE(0x07, 0x6e),
    HID_USAGE_F20 = MAKE_USAGE(0x07, 0x6f),
    HID_USAGE_F21 = MAKE_USAGE(0x07, 0x70),
    HID_USAGE_F22 = MAKE_USAGE(0x07, 0x71),
    HID_USAGE_F23 = MAKE_USAGE(0x07, 0x72),
    HID_USAGE_F24 = MAKE_USAGE(0x07, 0x73),
    HID_USAGE_KEYBOARD_EXECUTE = MAKE_USAGE(0x07, 0x74),
    HID_USAGE_KEYBOARD_HELP = MAKE_USAGE(0x07, 0x75),
    HID_USAGE_KEYBOARD_MENU = MAKE_USAGE(0x07, 0x76),
    HID_USAGE_KEYBOARD_SELECT = MAKE_USAGE(0x07, 0x77),
    HID_USAGE_KEYBOARD_STOP = MAKE_USAGE(0x07, 0x78),
    HID_USAGE_KEYBOARD_AGAIN = MAKE_USAGE(0x07, 0x79),
    HID_USAGE_KEYBOARD_UNDO = MAKE_USAGE(0x07, 0x7a),
    HID_USAGE_KEYBOARD_CUT = MAKE_USAGE(0x07, 0x7b),
    HID_USAGE_KEYBOARD_COPY = MAKE_USAGE(0x07, 0x7c),
    HID_USAGE_KEYBOARD_PASTE = MAKE_USAGE(0x07, 0x7d),
    HID_USAGE_KEYBOARD_FIND = MAKE_USAGE(0x07, 0x7e),
    HID_USAGE_KEYBOARD_MUTE = MAKE_USAGE(0x07, 0x7f),
    HID_USAGE_KEYBOARD_VOLUME_UP = MAKE_USAGE(0x07, 0x80),
    HID_USAGE_KEYBOARD_VOLUME_DOWN = MAKE_USAGE(0x07, 0x81),
    HID_USAGE_LOCKING_CAPS_LOCK = MAKE_USAGE(0x07, 0x82),
    HID_USAGE_LOCKING_NUM_LOCK = MAKE_USAGE(0x07, 0x83),
    HID_USAGE_LOCKING_SCROLL_LOCK = MAKE_USAGE(0x07, 0x84),
    HID_USAGE_KEYPAD_COMMA = MAKE_USAGE(0x07, 0x85),
    HID_USAGE_KEYPAD_EQUAL_SIGN = MAKE_USAGE(0x07, 0x86),
    HID_USAGE_INTERNATIONAL1 = MAKE_USAGE(0x07, 0x87),
    HID_USAGE_INTERNATIONAL2 = MAKE_USAGE(0x07, 0x88),
    HID_USAGE_INTERNATIONAL3 = MAKE_USAGE(0x07, 0x89),
    HID_USAGE_INTERNATIONAL4 = MAKE_USAGE(0x07, 0x8a),
    HID_USAGE_INTERNATIONAL5 = MAKE_USAGE(0x07, 0x8b),
    HID_USAGE_INTERNATIONAL6 = MAKE_USAGE(0x07, 0x8c),
    HID_USAGE_INTERNATIONAL7 = MAKE_USAGE(0x07, 0x8d),
    HID_USAGE_INTERNATIONAL8 = MAKE_USAGE(0x07, 0x8e),
    HID_USAGE_INTERNATIONAL9 = MAKE_USAGE(0x07, 0x8f),
    HID_USAGE_LANG1 = MAKE_USAGE(0x07, 0x90),
    HID_USAGE_LANG2 = MAKE_USAGE(0x07, 0x91),
    HID_USAGE_LANG3 = MAKE_USAGE(0x07, 0x92),
    HID_USAGE_LANG4 = MAKE_USAGE(0x07, 0x93),
    HID_USAGE_LANG5 = MAKE_USAGE(0x07, 0x94),
    HID_USAGE_LANG6 = MAKE_USAGE(0x07, 0x95),
    HID_USAGE_LANG7 = MAKE_USAGE(0x07, 0x96),
    HID_USAGE_LANG8 = MAKE_USAGE(0x07, 0x97),
    HID_USAGE_LANG9 = MAKE_USAGE(0x07, 0x98),
    HID_USAGE_ALTERNATE_ERASE = MAKE_USAGE(0x07, 0x99),
    HID_USAGE_SYSREQ_SLASHATTENTION = MAKE_USAGE(0x07, 0x9a),
    HID_USAGE_CANCEL = MAKE_USAGE(0x07, 0x9b),
    HID_USAGE_CLEAR = MAKE_USAGE(0x07, 0x9c),
    HID_USAGE_PRIOR = MAKE_USAGE(0x07, 0x9d),
    HID_USAGE_RETURN = MAKE_USAGE(0x07, 0x9e),
    HID_USAGE_SEPARATOR = MAKE_USAGE(0x07, 0x9f),
    HID_USAGE_OUT = MAKE_USAGE(0x07, 0xa0),
    HID_USAGE_OPER = MAKE_USAGE(0x07, 0xa1),
    HID_USAGE_CLEAR_SLASHAGAIN = MAKE_USAGE(0x07, 0xa2),
    HID_USAGE_CRSEL_SLASHPROPS = MAKE_USAGE(0x07, 0xa3),
    HID_USAGE_EXSEL = MAKE_USAGE(0x07, 0xa4),
    HID_USAGE_KEYPAD_00 = MAKE_USAGE(0x07, 0xb0),
    HID_USAGE_KEYPAD_000 = MAKE_USAGE(0x07, 0xb1),
    HID_USAGE_THOUSANDS_SEPARATOR = MAKE_USAGE(0x07, 0xb2),
    HID_USAGE_DECIMAL_SEPARATOR = MAKE_USAGE(0x07, 0xb3),
    HID_USAGE_CURRENCY_UNIT = MAKE_USAGE(0x07, 0xb4),
    HID_USAGE_CURRENCY_SUB_MINUSUNIT = MAKE_USAGE(0x07, 0xb5),
    HID_USAGE_KEYPAD__LPAREN = MAKE_USAGE(0x07, 0xb6),
    HID_USAGE_KEYPAD__RPAREN = MAKE_USAGE(0x07, 0xb7),
    HID_USAGE_KEYPAD__LCURLYBRACE = MAKE_USAGE(0x07, 0xb8),
    HID_USAGE_KEYPAD__RCURLYBRACE = MAKE_USAGE(0x07, 0xb9),
    HID_USAGE_KEYPAD_TAB = MAKE_USAGE(0x07, 0xba),
    HID_USAGE_KEYPAD_BACKSPACE = MAKE_USAGE(0x07, 0xbb),
    HID_USAGE_KEYPAD_A = MAKE_USAGE(0x07, 0xbc),
    HID_USAGE_KEYPAD_B = MAKE_USAGE(0x07, 0xbd),
    HID_USAGE_KEYPAD_C = MAKE_USAGE(0x07, 0xbe),
    HID_USAGE_KEYPAD_D = MAKE_USAGE(0x07, 0xbf),
    HID_USAGE_KEYPAD_E = MAKE_USAGE(0x07, 0xc0),
    HID_USAGE_KEYPAD_F = MAKE_USAGE(0x07, 0xc1),
    HID_USAGE_KEYPAD_XOR = MAKE_USAGE(0x07, 0xc2),
    HID_USAGE_KEYPAD__CARET = MAKE_USAGE(0x07, 0xc3),
    HID_USAGE_KEYPAD__PERCENT = MAKE_USAGE(0x07, 0xc4),
    HID_USAGE_KEYPAD__LESSTHAN = MAKE_USAGE(0x07, 0xc5),
    HID_USAGE_KEYPAD__GREATERTHAN = MAKE_USAGE(0x07, 0xc6),
    HID_USAGE_KEYPAD__AMPERSAND = MAKE_USAGE(0x07, 0xc7),
    HID_USAGE_KEYPAD__AMPERSAND_AMPERSAND = MAKE_USAGE(0x07, 0xc8),
    HID_USAGE_KEYPAD__PIPE = MAKE_USAGE(0x07, 0xc9),
    HID_USAGE_KEYPAD__PIPE_PIPE = MAKE_USAGE(0x07, 0xca),
    HID_USAGE_KEYPAD__COLON = MAKE_USAGE(0x07, 0xcb),
    HID_USAGE_KEYPAD__POUND = MAKE_USAGE(0x07, 0xcc),
    HID_USAGE_KEYPAD_SPACE = MAKE_USAGE(0x07, 0xcd),
    HID_USAGE_KEYPAD__ATSIGN = MAKE_USAGE(0x07, 0xce),
    HID_USAGE_KEYPAD__EXCLAMATION = MAKE_USAGE(0x07, 0xcf),
    HID_USAGE_KEYPAD_MEMORY_STORE = MAKE_USAGE(0x07, 0xd0),
    HID_USAGE_KEYPAD_MEMORY_RECALL = MAKE_USAGE(0x07, 0xd1),
    HID_USAGE_KEYPAD_MEMORY_CLEAR = MAKE_USAGE(0x07, 0xd2),
    HID_USAGE_KEYPAD_MEMORY_ADD = MAKE_USAGE(0x07, 0xd3),
    HID_USAGE_KEYPAD_MEMORY_SUBTRACT = MAKE_USAGE(0x07, 0xd4),
    HID_USAGE_KEYPAD_MEMORY_MULTIPLY = MAKE_USAGE(0x07, 0xd5),
    HID_USAGE_KEYPAD_MEMORY_DIVIDE = MAKE_USAGE(0x07, 0xd6),
    HID_USAGE_KEYPAD__PLUS_SLASH_MINUS216_D8_KEYPAD_CLEAR = MAKE_USAGE(0x07, 0xd7),
    HID_USAGE_KEYPAD_CLEAR_ENTRY = MAKE_USAGE(0x07, 0xd9),
    HID_USAGE_KEYPAD_BINARY = MAKE_USAGE(0x07, 0xda),
    HID_USAGE_KEYPAD_OCTAL = MAKE_USAGE(0x07, 0xdb),
    HID_USAGE_KEYPAD_DECIMAL = MAKE_USAGE(0x07, 0xdc),
    HID_USAGE_KEYPAD_HEXADECIMAL = MAKE_USAGE(0x07, 0xdd),
    HID_USAGE_LEFT_CONTROL = MAKE_USAGE(0x07, 0xe0),
    HID_USAGE_LEFT_SHIFT = MAKE_USAGE(0x07, 0xe1),
    HID_USAGE_LEFT_ALT = MAKE_USAGE(0x07, 0xe2),
    HID_USAGE_LEFT_GUI = MAKE_USAGE(0x07, 0xe3),
    HID_USAGE_RIGHT_CONTROL = MAKE_USAGE(0x07, 0xe4),
    HID_USAGE_RIGHT_SHIFT = MAKE_USAGE(0x07, 0xe5),
    HID_USAGE_RIGHT_ALT = MAKE_USAGE(0x07, 0xe6),
    HID_USAGE_RIGHT_GUI = MAKE_USAGE(0x07, 0xe7),
    /* USAGE PAGE:  Consumer_Control */
#define HID_USAGE_PAGE_CONSUMER_CONTROL 0x0c

    HID_USAGE_UNASSIGNED = MAKE_USAGE(0x0c, 0x00),
    HID_USAGE_CONSUMER_CONTROL = MAKE_USAGE(0x0c, 0x01),
    HID_USAGE_NUMERIC_KEY_PAD = MAKE_USAGE(0x0c, 0x02),
    HID_USAGE_PROGRAMMABLE_BUTTONS = MAKE_USAGE(0x0c, 0x03),
    HID_USAGE_MICROPHONE = MAKE_USAGE(0x0c, 0x04),
    HID_USAGE_HEADPHONE = MAKE_USAGE(0x0c, 0x05),
    HID_USAGE_GRAPHIC_EQUALIZER = MAKE_USAGE(0x0c, 0x06),
    HID_USAGE_CC10 = MAKE_USAGE(0x0c, 0x20),
    HID_USAGE_CC100 = MAKE_USAGE(0x0c, 0x21),
    HID_USAGE_AM_SLASHPM = MAKE_USAGE(0x0c, 0x22),
    HID_USAGE_POWER = MAKE_USAGE(0x0c, 0x30),
    HID_USAGE_RESET = MAKE_USAGE(0x0c, 0x31),
    HID_USAGE_SLEEP = MAKE_USAGE(0x0c, 0x32),
    HID_USAGE_SLEEP_AFTER = MAKE_USAGE(0x0c, 0x33),
    HID_USAGE_SLEEP_MODE = MAKE_USAGE(0x0c, 0x34),
    HID_USAGE_ILLUMINATION = MAKE_USAGE(0x0c, 0x35),
    HID_USAGE_FUNCTION_BUTTONS = MAKE_USAGE(0x0c, 0x36),
    HID_USAGE_MENU = MAKE_USAGE(0x0c, 0x40),
    HID_USAGE_MENU_PICK = MAKE_USAGE(0x0c, 0x41),
    HID_USAGE_MENU_UP = MAKE_USAGE(0x0c, 0x42),
    HID_USAGE_MENU_DOWN = MAKE_USAGE(0x0c, 0x43),
    HID_USAGE_MENU_LEFT = MAKE_USAGE(0x0c, 0x44),
    HID_USAGE_MENU_RIGHT = MAKE_USAGE(0x0c, 0x45),
    HID_USAGE_MENU_ESCAPE = MAKE_USAGE(0x0c, 0x46),
    HID_USAGE_MENU_VALUE_INCREASE = MAKE_USAGE(0x0c, 0x47),
    HID_USAGE_MENU_VALUE_DECREASE = MAKE_USAGE(0x0c, 0x48),
    HID_USAGE_DATA_ON_SCREEN = MAKE_USAGE(0x0c, 0x60),
    HID_USAGE_CLOSED_CAPTION = MAKE_USAGE(0x0c, 0x61),
    HID_USAGE_CLOSED_CAPTION_SELECT = MAKE_USAGE(0x0c, 0x62),
    HID_USAGE_VCR_SLASHTV = MAKE_USAGE(0x0c, 0x63),
    HID_USAGE_BROADCAST_MODE = MAKE_USAGE(0x0c, 0x64),
    HID_USAGE_SNAPSHOT = MAKE_USAGE(0x0c, 0x65),
    HID_USAGE_STILL = MAKE_USAGE(0x0c, 0x66),
    HID_USAGE_SELECTION = MAKE_USAGE(0x0c, 0x80),
    HID_USAGE_ASSIGN_SELECTION = MAKE_USAGE(0x0c, 0x81),
    HID_USAGE_MODE_STEP = MAKE_USAGE(0x0c, 0x82),
    HID_USAGE_RECALL_LAST = MAKE_USAGE(0x0c, 0x83),
    HID_USAGE_ENTER_CHANNEL = MAKE_USAGE(0x0c, 0x84),
    HID_USAGE_ORDER_MOVIE = MAKE_USAGE(0x0c, 0x85),
    HID_USAGE_CHANNEL = MAKE_USAGE(0x0c, 0x86),
    HID_USAGE_MEDIA_SELECTION = MAKE_USAGE(0x0c, 0x87),
    HID_USAGE_MEDIA_SELECT_COMPUTER = MAKE_USAGE(0x0c, 0x88),
    HID_USAGE_MEDIA_SELECT_TV = MAKE_USAGE(0x0c, 0x89),
    HID_USAGE_MEDIA_SELECT_WWW = MAKE_USAGE(0x0c, 0x8a),
    HID_USAGE_MEDIA_SELECT_DVD = MAKE_USAGE(0x0c, 0x8b),
    HID_USAGE_MEDIA_SELECT_TELEPHONE = MAKE_USAGE(0x0c, 0x8c),
    HID_USAGE_MEDIA_SELECT_PROGRAM_GUIDE = MAKE_USAGE(0x0c, 0x8d),
    HID_USAGE_MEDIA_SELECT_VIDEO_PHONE = MAKE_USAGE(0x0c, 0x8e),
    HID_USAGE_MEDIA_SELECT_GAMES = MAKE_USAGE(0x0c, 0x8f),
    HID_USAGE_MEDIA_SELECT_MESSAGES = MAKE_USAGE(0x0c, 0x90),
    HID_USAGE_MEDIA_SELECT_CD = MAKE_USAGE(0x0c, 0x91),
    HID_USAGE_MEDIA_SELECT_VCR = MAKE_USAGE(0x0c, 0x92),
    HID_USAGE_MEDIA_SELECT_TUNER = MAKE_USAGE(0x0c, 0x93),
    HID_USAGE_QUIT = MAKE_USAGE(0x0c, 0x94),
    HID_USAGE_HELP = MAKE_USAGE(0x0c, 0x95),
    HID_USAGE_MEDIA_SELECT_TAPE = MAKE_USAGE(0x0c, 0x96),
    HID_USAGE_MEDIA_SELECT_CABLE = MAKE_USAGE(0x0c, 0x97),
    HID_USAGE_MEDIA_SELECT_SATELLITE = MAKE_USAGE(0x0c, 0x98),
    HID_USAGE_MEDIA_SELECT_SECURITY = MAKE_USAGE(0x0c, 0x99),
    HID_USAGE_MEDIA_SELECT_HOME = MAKE_USAGE(0x0c, 0x9a),
    HID_USAGE_MEDIA_SELECT_CALL = MAKE_USAGE(0x0c, 0x9b),
    HID_USAGE_CHANNEL_INCREMENT = MAKE_USAGE(0x0c, 0x9c),
    HID_USAGE_CHANNEL_DECREMENT = MAKE_USAGE(0x0c, 0x9d),
    HID_USAGE_MEDIA_SELECT_SAP = MAKE_USAGE(0x0c, 0x9e),
    HID_USAGE_VCR_PLUS = MAKE_USAGE(0x0c, 0xa0),
    HID_USAGE_ONCE = MAKE_USAGE(0x0c, 0xa1),
    HID_USAGE_DAILY = MAKE_USAGE(0x0c, 0xa2),
    HID_USAGE_WEEKLY = MAKE_USAGE(0x0c, 0xa3),
    HID_USAGE_MONTHLY = MAKE_USAGE(0x0c, 0xa4),
    HID_USAGE_PLAY = MAKE_USAGE(0x0c, 0xb0),
    HID_USAGE_PAUSE = MAKE_USAGE(0x0c, 0xb1),
    HID_USAGE_RECORD = MAKE_USAGE(0x0c, 0xb2),
    HID_USAGE_FAST_FORWARD = MAKE_USAGE(0x0c, 0xb3),
    HID_USAGE_REWIND = MAKE_USAGE(0x0c, 0xb4),
    HID_USAGE_SCAN_NEXT_TRACK = MAKE_USAGE(0x0c, 0xb5),
    HID_USAGE_SCAN_PREVIOUS_TRACK = MAKE_USAGE(0x0c, 0xb6),
    HID_USAGE_STOP = MAKE_USAGE(0x0c, 0xb7),
    HID_USAGE_EJECT = MAKE_USAGE(0x0c, 0xb8),
    HID_USAGE_RANDOM_PLAY = MAKE_USAGE(0x0c, 0xb9),
    HID_USAGE_SELECT_DISC = MAKE_USAGE(0x0c, 0xba),
    HID_USAGE_ENTER_DISC = MAKE_USAGE(0x0c, 0xbb),
    HID_USAGE_REPEAT = MAKE_USAGE(0x0c, 0xbc),
    HID_USAGE_TRACKING = MAKE_USAGE(0x0c, 0xbd),
    HID_USAGE_TRACK_NORMAL = MAKE_USAGE(0x0c, 0xbe),
    HID_USAGE_SLOW_TRACKING = MAKE_USAGE(0x0c, 0xbf),
    HID_USAGE_FRAME_FORWARD = MAKE_USAGE(0x0c, 0xc0),
    HID_USAGE_FRAME_BACK = MAKE_USAGE(0x0c, 0xc1),
    HID_USAGE_MARK = MAKE_USAGE(0x0c, 0xc2),
    HID_USAGE_CLEAR_MARK = MAKE_USAGE(0x0c, 0xc3),
    HID_USAGE_REPEAT_FROM_MARK = MAKE_USAGE(0x0c, 0xc4),
    HID_USAGE_RETURN_TO_MARK = MAKE_USAGE(0x0c, 0xc5),
    HID_USAGE_SEARCH_MARK_FORWARD = MAKE_USAGE(0x0c, 0xc6),
    HID_USAGE_SEARCH_MARK_BACKWARDS = MAKE_USAGE(0x0c, 0xc7),
    HID_USAGE_COUNTER_RESET = MAKE_USAGE(0x0c, 0xc8),
    HID_USAGE_SHOW_COUNTER = MAKE_USAGE(0x0c, 0xc9),
    HID_USAGE_TRACKING_INCREMENT = MAKE_USAGE(0x0c, 0xca),
    HID_USAGE_TRACKING_DECREMENT = MAKE_USAGE(0x0c, 0xcb),
    HID_USAGE_STOP_SLASHEJECT = MAKE_USAGE(0x0c, 0xcc),
    HID_USAGE_PLAY_SLASHPAUSE = MAKE_USAGE(0x0c, 0xcd),
    HID_USAGE_PLAY_SLASHSKIP = MAKE_USAGE(0x0c, 0xce),
    HID_USAGE_VOLUME = MAKE_USAGE(0x0c, 0xe0),
    HID_USAGE_BALANCE = MAKE_USAGE(0x0c, 0xe1),
    HID_USAGE_MUTE = MAKE_USAGE(0x0c, 0xe2),
    HID_USAGE_BASS = MAKE_USAGE(0x0c, 0xe3),
    HID_USAGE_TREBLE = MAKE_USAGE(0x0c, 0xe4),
    HID_USAGE_BASS_BOOST = MAKE_USAGE(0x0c, 0xe5),
    HID_USAGE_SURROUND_MODE = MAKE_USAGE(0x0c, 0xe6),
    HID_USAGE_LOUDNESS = MAKE_USAGE(0x0c, 0xe7),
    HID_USAGE_MPX = MAKE_USAGE(0x0c, 0xe8),
    HID_USAGE_VOLUME_INCREMENT = MAKE_USAGE(0x0c, 0xe9),
    HID_USAGE_VOLUME_DECREMENT = MAKE_USAGE(0x0c, 0xea),
    HID_USAGE_SPEED_SELECT = MAKE_USAGE(0x0c, 0xf0),
    HID_USAGE_PLAYBACK_SPEED = MAKE_USAGE(0x0c, 0xf1),
    HID_USAGE_STANDARD_PLAY = MAKE_USAGE(0x0c, 0xf2),
    HID_USAGE_LONG_PLAY = MAKE_USAGE(0x0c, 0xf3),
    HID_USAGE_EXTENDED_PLAY = MAKE_USAGE(0x0c, 0xf4),
    HID_USAGE_SLOW = MAKE_USAGE(0x0c, 0xf5),
    HID_USAGE_FAN_ENABLE = MAKE_USAGE(0x0c, 0x100),
    HID_USAGE_FAN_SPEED = MAKE_USAGE(0x0c, 0x101),
    HID_USAGE_LIGHT_ENABLE = MAKE_USAGE(0x0c, 0x102),
    HID_USAGE_LIGHT_ILLUMINATION_LEVEL = MAKE_USAGE(0x0c, 0x103),
    HID_USAGE_CLIMATE_CONTROL_ENABLE = MAKE_USAGE(0x0c, 0x104),
    HID_USAGE_ROOM_TEMPERATURE = MAKE_USAGE(0x0c, 0x105),
    HID_USAGE_SECURITY_ENABLE = MAKE_USAGE(0x0c, 0x106),
    HID_USAGE_FIRE_ALARM = MAKE_USAGE(0x0c, 0x107),
    HID_USAGE_POLICE_ALARM = MAKE_USAGE(0x0c, 0x108),
    HID_USAGE_PROXIMITY = MAKE_USAGE(0x0c, 0x109),
    HID_USAGE_MOTION = MAKE_USAGE(0x0c, 0x10a),
    HID_USAGE_DURESS_ALARM = MAKE_USAGE(0x0c, 0x10b),
    HID_USAGE_HOLDUP_ALARM = MAKE_USAGE(0x0c, 0x10c),
    HID_USAGE_MEDICAL_ALARM = MAKE_USAGE(0x0c, 0x10d),
    HID_USAGE_BALANCE_RIGHT = MAKE_USAGE(0x0c, 0x150),
    HID_USAGE_BALANCE_LEFT = MAKE_USAGE(0x0c, 0x151),
    HID_USAGE_BASS_INCREMENT = MAKE_USAGE(0x0c, 0x152),
    HID_USAGE_BASS_DECREMENT = MAKE_USAGE(0x0c, 0x153),
    HID_USAGE_TREBLE_INCREMENT = MAKE_USAGE(0x0c, 0x154),
    HID_USAGE_TREBLE_DECREMENT = MAKE_USAGE(0x0c, 0x155),
    HID_USAGE_SPEAKER_SYSTEM = MAKE_USAGE(0x0c, 0x160),
    HID_USAGE_CHANNEL_LEFT = MAKE_USAGE(0x0c, 0x161),
    HID_USAGE_CHANNEL_RIGHT = MAKE_USAGE(0x0c, 0x162),
    HID_USAGE_CHANNEL_CENTER = MAKE_USAGE(0x0c, 0x163),
    HID_USAGE_CHANNEL_FRONT = MAKE_USAGE(0x0c, 0x164),
    HID_USAGE_CHANNEL_CENTER_FRONT = MAKE_USAGE(0x0c, 0x165),
    HID_USAGE_CHANNEL_SIDE = MAKE_USAGE(0x0c, 0x166),
    HID_USAGE_CHANNEL_SURROUND = MAKE_USAGE(0x0c, 0x167),
    HID_USAGE_CHANNEL_LOW_FREQUENCY_ENHANCEMENT = MAKE_USAGE(0x0c, 0x168),
    HID_USAGE_CHANNEL_TOP = MAKE_USAGE(0x0c, 0x169),
    HID_USAGE_CHANNEL_UNKNOWN = MAKE_USAGE(0x0c, 0x16a),
    HID_USAGE_SUB_MINUSCHANNEL = MAKE_USAGE(0x0c, 0x170),
    HID_USAGE_SUB_MINUSCHANNEL_INCREMENT = MAKE_USAGE(0x0c, 0x171),
    HID_USAGE_SUB_MINUSCHANNEL_DECREMENT = MAKE_USAGE(0x0c, 0x172),
    HID_USAGE_ALTERNATE_AUDIO_INCREMENT = MAKE_USAGE(0x0c, 0x173),
    HID_USAGE_ALTERNATE_AUDIO_DECREMENT = MAKE_USAGE(0x0c, 0x174),
    HID_USAGE_APPLICATION_LAUNCH_BUTTONS = MAKE_USAGE(0x0c, 0x180),
    HID_USAGE_AL_LAUNCH_BUTTON_CONFIGURATION_TOOL = MAKE_USAGE(0x0c, 0x181),
    HID_USAGE_AL_PROGRAMMABLE_BUTTON_CONFIGURATION = MAKE_USAGE(0x0c, 0x182),
    HID_USAGE_AL_CONSUMER_CONTROL_CONFIGURATION = MAKE_USAGE(0x0c, 0x183),
    HID_USAGE_AL_WORD_PROCESSOR = MAKE_USAGE(0x0c, 0x184),
    HID_USAGE_AL_TEXT_EDITOR = MAKE_USAGE(0x0c, 0x185),
    HID_USAGE_AL_SPREADSHEET = MAKE_USAGE(0x0c, 0x186),
    HID_USAGE_AL_GRAPHICS_EDITOR = MAKE_USAGE(0x0c, 0x187),
    HID_USAGE_AL_PRESENTATION_APP = MAKE_USAGE(0x0c, 0x188),
    HID_USAGE_AL_DATABASE_APP = MAKE_USAGE(0x0c, 0x189),
    HID_USAGE_AL_EMAIL_READER = MAKE_USAGE(0x0c, 0x18a),
    HID_USAGE_AL_NEWSREADER = MAKE_USAGE(0x0c, 0x18b),
    HID_USAGE_AL_VOICEMAIL = MAKE_USAGE(0x0c, 0x18c),
    HID_USAGE_AL_CONTACTS_SLASHADDRESS_BOOK = MAKE_USAGE(0x0c, 0x18d),
    HID_USAGE_AL_CALENDAR_SLASHSCHEDULE = MAKE_USAGE(0x0c, 0x18e),
    HID_USAGE_AL_TASK_SLASHPROJECT_MANAGER = MAKE_USAGE(0x0c, 0x18f),
    HID_USAGE_AL_LOG_SLASHJOURNAL_SLASHTIMECARD = MAKE_USAGE(0x0c, 0x190),
    HID_USAGE_AL_CHECKBOOK_SLASHFINANCE = MAKE_USAGE(0x0c, 0x191),
    HID_USAGE_AL_CALCULATOR = MAKE_USAGE(0x0c, 0x192),
    HID_USAGE_AL_A_SLASHV_CAPTURE_SLASHPLAYBACK = MAKE_USAGE(0x0c, 0x193),
    HID_USAGE_AL_LOCAL_MACHINE_BROWSER = MAKE_USAGE(0x0c, 0x194),
    HID_USAGE_AL_LAN_SLASHWAN_BROWSER = MAKE_USAGE(0x0c, 0x195),
    HID_USAGE_AL_INTERNET_BROWSER = MAKE_USAGE(0x0c, 0x196),
    HID_USAGE_AL_REMOTE_NETWORKING_SLASHISP_CONNECT = MAKE_USAGE(0x0c, 0x197),
    HID_USAGE_AL_NETWORK_CONFERENCE = MAKE_USAGE(0x0c, 0x198),
    HID_USAGE_AL_NETWORK_CHAT = MAKE_USAGE(0x0c, 0x199),
    HID_USAGE_AL_TELEPHONY_SLASHDIALER = MAKE_USAGE(0x0c, 0x19a),
    HID_USAGE_AL_LOGON = MAKE_USAGE(0x0c, 0x19b),
    HID_USAGE_AL_LOGOFF = MAKE_USAGE(0x0c, 0x19c),
    HID_USAGE_AL_LOGON_SLASHLOGOFF = MAKE_USAGE(0x0c, 0x19d),
    HID_USAGE_AL_TERMINAL_LOCK_SLASHSCREENSAVER = MAKE_USAGE(0x0c, 0x19e),
    HID_USAGE_AL_CONTROL_PANEL = MAKE_USAGE(0x0c, 0x19f),
    HID_USAGE_AL_COMMAND_LINE_PROCESSOR_SLASHRUN = MAKE_USAGE(0x0c, 0x1a0),
    HID_USAGE_AL_PROCESS_SLASHTASK_MANAGER = MAKE_USAGE(0x0c, 0x1a1),
    HID_USAGE_AL_SELECT_TASK_SLASHAPPLICATION = MAKE_USAGE(0x0c, 0x1a2),
    HID_USAGE_AL_NEXT_TASK_SLASHAPPLICATION = MAKE_USAGE(0x0c, 0x1a3),
    HID_USAGE_AL_PREVIOUS_TASK_SLASHAPPLICATION = MAKE_USAGE(0x0c, 0x1a4),
    HID_USAGE_AL_PREEMPTIVE_HALT_TASK_SLASHAPPLICATION = MAKE_USAGE(0x0c, 0x1a5),
    HID_USAGE_AL_INTEGRATED_HELP_CENTER = MAKE_USAGE(0x0c, 0x1a6),
    HID_USAGE_AL_DOCUMENTS = MAKE_USAGE(0x0c, 0x1a7),
    HID_USAGE_AL_THESAURUS = MAKE_USAGE(0x0c, 0x1a8),
    HID_USAGE_AL_DICTIONARY = MAKE_USAGE(0x0c, 0x1a9),
    HID_USAGE_AL_DESKTOP = MAKE_USAGE(0x0c, 0x1aa),
    HID_USAGE_AL_SPELL_CHECK = MAKE_USAGE(0x0c, 0x1ab),
    HID_USAGE_AL_GRAMMAR_CHECK = MAKE_USAGE(0x0c, 0x1ac),
    HID_USAGE_AL_WIRELESS_STATUS = MAKE_USAGE(0x0c, 0x1ad),
    HID_USAGE_AL_KEYBOARD_LAYOUT = MAKE_USAGE(0x0c, 0x1ae),
    HID_USAGE_AL_VIRUS_PROTECTION = MAKE_USAGE(0x0c, 0x1af),
    HID_USAGE_AL_ENCRYPTION = MAKE_USAGE(0x0c, 0x1b0),
    HID_USAGE_AL_SCREEN_SAVER = MAKE_USAGE(0x0c, 0x1b1),
    HID_USAGE_AL_ALARMS = MAKE_USAGE(0x0c, 0x1b2),
    HID_USAGE_AL_CLOCK = MAKE_USAGE(0x0c, 0x1b3),
    HID_USAGE_AL_FILE_BROWSER = MAKE_USAGE(0x0c, 0x1b4),
    HID_USAGE_AL_POWER_STATUS = MAKE_USAGE(0x0c, 0x1b5),
    HID_USAGE_AL_IMAGE_BROWSER = MAKE_USAGE(0x0c, 0x1b6),
    HID_USAGE_AL_AUDIO_BROWSER = MAKE_USAGE(0x0c, 0x1b7),
    HID_USAGE_AL_MOVIE_BROWSER = MAKE_USAGE(0x0c, 0x1b8),
    HID_USAGE_AL_DIGITAL_RIGHTS_MANAGER = MAKE_USAGE(0x0c, 0x1b9),
    HID_USAGE_AL_DIGITAL_WALLET = MAKE_USAGE(0x0c, 0x1ba),
    HID_USAGE_AL_INSTANT_MESSAGING = MAKE_USAGE(0x0c, 0x1bc),
    HID_USAGE_AL_OEM_FEATURES_SLASH_TIPS_SLASHTUTORIAL_BROWSER = MAKE_USAGE(0x0c, 0x1bd),
    HID_USAGE_AL_OEM_HELP = MAKE_USAGE(0x0c, 0x1be),
    HID_USAGE_AL_ONLINE_COMMUNITY = MAKE_USAGE(0x0c, 0x1bf),
    HID_USAGE_AL_ENTERTAINMENT_CONTENT_BROWSER = MAKE_USAGE(0x0c, 0x1c0),
    HID_USAGE_AL_ONLINE_SHOPPING_BROWSER = MAKE_USAGE(0x0c, 0x1c1),
    HID_USAGE_AL_SMARTCARD_INFORMATION_SLASHHELP = MAKE_USAGE(0x0c, 0x1c2),
    HID_USAGE_AL_MARKET_MONITOR_SLASHFINANCE_BROWSER = MAKE_USAGE(0x0c, 0x1c3),
    HID_USAGE_AL_CUSTOMIZED_CORPORATE_NEWS_BROWSER = MAKE_USAGE(0x0c, 0x1c4),
    HID_USAGE_AL_ONLINE_ACTIVITY_BROWSER = MAKE_USAGE(0x0c, 0x1c5),
    HID_USAGE_AL_RESEARCH_SLASHSEARCH_BROWSER = MAKE_USAGE(0x0c, 0x1c6),
    HID_USAGE_AL_AUDIO_PLAYER = MAKE_USAGE(0x0c, 0x1c7),
    HID_USAGE_GENERIC_GUI_APPLICATION_CONTROLS = MAKE_USAGE(0x0c, 0x200),
    HID_USAGE_AC_NEW = MAKE_USAGE(0x0c, 0x201),
    HID_USAGE_AC_OPEN = MAKE_USAGE(0x0c, 0x202),
    HID_USAGE_AC_CLOSE = MAKE_USAGE(0x0c, 0x203),
    HID_USAGE_AC_EXIT = MAKE_USAGE(0x0c, 0x204),
    HID_USAGE_AC_MAXIMIZE = MAKE_USAGE(0x0c, 0x205),
    HID_USAGE_AC_MINIMIZE = MAKE_USAGE(0x0c, 0x206),
    HID_USAGE_AC_SAVE = MAKE_USAGE(0x0c, 0x207),
    HID_USAGE_AC_PRINT = MAKE_USAGE(0x0c, 0x208),
    HID_USAGE_AC_PROPERTIES = MAKE_USAGE(0x0c, 0x209),
    HID_USAGE_AC_UNDO = MAKE_USAGE(0x0c, 0x21a),
    HID_USAGE_AC_COPY = MAKE_USAGE(0x0c, 0x21b),
    HID_USAGE_AC_CUT = MAKE_USAGE(0x0c, 0x21c),
    HID_USAGE_AC_PASTE = MAKE_USAGE(0x0c, 0x21d),
    HID_USAGE_AC_SELECT_ALL = MAKE_USAGE(0x0c, 0x21e),
    HID_USAGE_AC_FIND = MAKE_USAGE(0x0c, 0x21f),
    HID_USAGE_AC_FIND_AND_REPLACE = MAKE_USAGE(0x0c, 0x220),
    HID_USAGE_AC_SEARCH = MAKE_USAGE(0x0c, 0x221),
    HID_USAGE_AC_GO_TO = MAKE_USAGE(0x0c, 0x222),
    HID_USAGE_AC_HOME = MAKE_USAGE(0x0c, 0x223),
    HID_USAGE_AC_BACK = MAKE_USAGE(0x0c, 0x224),
    HID_USAGE_AC_FORWARD = MAKE_USAGE(0x0c, 0x225),
    HID_USAGE_AC_STOP = MAKE_USAGE(0x0c, 0x226),
    HID_USAGE_AC_REFRESH = MAKE_USAGE(0x0c, 0x227),
    HID_USAGE_AC_PREVIOUS_LINK = MAKE_USAGE(0x0c, 0x228),
    HID_USAGE_AC_NEXT_LINK = MAKE_USAGE(0x0c, 0x229),
    HID_USAGE_AC_BOOKMARKS = MAKE_USAGE(0x0c, 0x22a),
    HID_USAGE_AC_HISTORY = MAKE_USAGE(0x0c, 0x22b),
    HID_USAGE_AC_SUBSCRIPTIONS = MAKE_USAGE(0x0c, 0x22c),
    HID_USAGE_AC_ZOOM_IN = MAKE_USAGE(0x0c, 0x22d),
    HID_USAGE_AC_ZOOM_OUT = MAKE_USAGE(0x0c, 0x22e),
    HID_USAGE_AC_ZOOM = MAKE_USAGE(0x0c, 0x22f),
    HID_USAGE_AC_FULL_SCREEN_VIEW = MAKE_USAGE(0x0c, 0x230),
    HID_USAGE_AC_NORMAL_VIEW = MAKE_USAGE(0x0c, 0x231),
    HID_USAGE_AC_VIEW_TOGGLE = MAKE_USAGE(0x0c, 0x232),
    HID_USAGE_AC_SCROLL_UP = MAKE_USAGE(0x0c, 0x233),
    HID_USAGE_AC_SCROLL_DOWN = MAKE_USAGE(0x0c, 0x234),
    HID_USAGE_AC_SCROLL = MAKE_USAGE(0x0c, 0x235),
    HID_USAGE_AC_PAN_LEFT = MAKE_USAGE(0x0c, 0x236),
    HID_USAGE_AC_PAN_RIGHT = MAKE_USAGE(0x0c, 0x237),
    HID_USAGE_AC_PAN = MAKE_USAGE(0x0c, 0x238),
    HID_USAGE_AC_NEW_WINDOW = MAKE_USAGE(0x0c, 0x239),
    HID_USAGE_AC_TILE_HORIZONTALLY = MAKE_USAGE(0x0c, 0x23a),
    HID_USAGE_AC_TILE_VERTICALLY = MAKE_USAGE(0x0c, 0x23b),
    HID_USAGE_AC_FORMAT = MAKE_USAGE(0x0c, 0x23c),
    HID_USAGE_AC_EDIT = MAKE_USAGE(0x0c, 0x23d),
    HID_USAGE_AC_BOLD = MAKE_USAGE(0x0c, 0x23e),
    HID_USAGE_AC_ITALICS = MAKE_USAGE(0x0c, 0x23f),
    HID_USAGE_AC_UNDERLINE = MAKE_USAGE(0x0c, 0x240),
    HID_USAGE_AC_STRIKETHROUGH = MAKE_USAGE(0x0c, 0x241),
    HID_USAGE_AC_SUBSCRIPT = MAKE_USAGE(0x0c, 0x242),
    HID_USAGE_AC_SUPERSCRIPT = MAKE_USAGE(0x0c, 0x243),
    HID_USAGE_AC_ALL_CAPS = MAKE_USAGE(0x0c, 0x244),
    HID_USAGE_AC_ROTATE = MAKE_USAGE(0x0c, 0x245),
    HID_USAGE_AC_RESIZE = MAKE_USAGE(0x0c, 0x246),
    HID_USAGE_AC_FLIP_HORIZONTAL = MAKE_USAGE(0x0c, 0x247),
    HID_USAGE_AC_FLIP_VERTICAL = MAKE_USAGE(0x0c, 0x248),
    HID_USAGE_AC_MIRROR_HORIZONTAL = MAKE_USAGE(0x0c, 0x249),
    HID_USAGE_AC_MIRROR_VERTICAL = MAKE_USAGE(0x0c, 0x24a),
    HID_USAGE_AC_FONT_SELECT = MAKE_USAGE(0x0c, 0x24b),
    HID_USAGE_AC_FONT_COLOR = MAKE_USAGE(0x0c, 0x24c),
    HID_USAGE_AC_FONT_SIZE = MAKE_USAGE(0x0c, 0x24d),
    HID_USAGE_AC_JUSTIFY_LEFT = MAKE_USAGE(0x0c, 0x24e),
    HID_USAGE_AC_JUSTIFY_CENTER_H = MAKE_USAGE(0x0c, 0x24f),
    HID_USAGE_AC_JUSTIFY_RIGHT = MAKE_USAGE(0x0c, 0x250),
    HID_USAGE_AC_JUSTIFY_BLOCK_H = MAKE_USAGE(0x0c, 0x251),
    HID_USAGE_AC_JUSTIFY_TOP = MAKE_USAGE(0x0c, 0x252),
    HID_USAGE_AC_JUSTIFY_CENTER_V = MAKE_USAGE(0x0c, 0x253),
    HID_USAGE_AC_JUSTIFY_BOTTOM = MAKE_USAGE(0x0c, 0x254),
    HID_USAGE_AC_JUSTIFY_BLOCK_V = MAKE_USAGE(0x0c, 0x255),
    HID_USAGE_AC_INDENT_DECREASE = MAKE_USAGE(0x0c, 0x256),
    HID_USAGE_AC_INDENT_INCREASE = MAKE_USAGE(0x0c, 0x257),
    HID_USAGE_AC_NUMBERED_LIST = MAKE_USAGE(0x0c, 0x258),
    HID_USAGE_AC_RESTART_NUMBERING = MAKE_USAGE(0x0c, 0x259),
    HID_USAGE_AC_BULLETED_LIST = MAKE_USAGE(0x0c, 0x25a),
    HID_USAGE_AC_PROMOTE = MAKE_USAGE(0x0c, 0x25b),
    HID_USAGE_AC_DEMOTE = MAKE_USAGE(0x0c, 0x25c),
    HID_USAGE_AC_YES = MAKE_USAGE(0x0c, 0x25d),
    HID_USAGE_AC_NO = MAKE_USAGE(0x0c, 0x25e),
    HID_USAGE_AC_CANCEL = MAKE_USAGE(0x0c, 0x25f),
    HID_USAGE_AC_CATALOG = MAKE_USAGE(0x0c, 0x260),
    HID_USAGE_AC_BUY_SLASHCHECKOUT = MAKE_USAGE(0x0c, 0x261),
    HID_USAGE_AC_ADD_TO_CART = MAKE_USAGE(0x0c, 0x262),
    HID_USAGE_AC_EXPAND = MAKE_USAGE(0x0c, 0x263),
    HID_USAGE_AC_EXPAND_ALL = MAKE_USAGE(0x0c, 0x264),
    HID_USAGE_AC_COLLAPSE = MAKE_USAGE(0x0c, 0x265),
    HID_USAGE_AC_COLLAPSE_ALL = MAKE_USAGE(0x0c, 0x266),
    HID_USAGE_AC_PRINT_PREVIEW = MAKE_USAGE(0x0c, 0x267),
    HID_USAGE_AC_PASTE_SPECIAL = MAKE_USAGE(0x0c, 0x268),
    HID_USAGE_AC_INSERT_MODE = MAKE_USAGE(0x0c, 0x269),
    HID_USAGE_AC_DELETE = MAKE_USAGE(0x0c, 0x26a),
    HID_USAGE_AC_LOCK = MAKE_USAGE(0x0c, 0x26b),
    HID_USAGE_AC_UNLOCK = MAKE_USAGE(0x0c, 0x26c),
    HID_USAGE_AC_PROTECT = MAKE_USAGE(0x0c, 0x26d),
    HID_USAGE_AC_UNPROTECT = MAKE_USAGE(0x0c, 0x26e),
    HID_USAGE_AC_ATTACH_COMMENT = MAKE_USAGE(0x0c, 0x26f),
    HID_USAGE_AC_DELETE_COMMENT = MAKE_USAGE(0x0c, 0x270),
    HID_USAGE_AC_VIEW_COMMENT = MAKE_USAGE(0x0c, 0x271),
    HID_USAGE_AC_SELECT_WORD = MAKE_USAGE(0x0c, 0x272),
    HID_USAGE_AC_SELECT_SENTENCE = MAKE_USAGE(0x0c, 0x273),
    HID_USAGE_AC_SELECT_PARAGRAPH = MAKE_USAGE(0x0c, 0x274),
    HID_USAGE_AC_SELECT_COLUMN = MAKE_USAGE(0x0c, 0x275),
    HID_USAGE_AC_SELECT_ROW = MAKE_USAGE(0x0c, 0x276),
    HID_USAGE_AC_SELECT_TABLE = MAKE_USAGE(0x0c, 0x277),
    HID_USAGE_AC_SELECT_OBJECT = MAKE_USAGE(0x0c, 0x278),
    HID_USAGE_AC_REDO_SLASHREPEAT = MAKE_USAGE(0x0c, 0x279),
    HID_USAGE_AC_SORT = MAKE_USAGE(0x0c, 0x27a),
    HID_USAGE_AC_SORT_ASCENDING = MAKE_USAGE(0x0c, 0x27b),
    HID_USAGE_AC_SORT_DESCENDING = MAKE_USAGE(0x0c, 0x27c),
    HID_USAGE_AC_FILTER = MAKE_USAGE(0x0c, 0x27d),
    HID_USAGE_AC_SET_CLOCK = MAKE_USAGE(0x0c, 0x27e),
    HID_USAGE_AC_VIEW_CLOCK = MAKE_USAGE(0x0c, 0x27f),
    HID_USAGE_AC_SELECT_TIME_ZONE = MAKE_USAGE(0x0c, 0x280),
    HID_USAGE_AC_EDIT_TIME_ZONES = MAKE_USAGE(0x0c, 0x281),
    HID_USAGE_AC_SET_ALARM = MAKE_USAGE(0x0c, 0x282),
    HID_USAGE_AC_CLEAR_ALARM = MAKE_USAGE(0x0c, 0x283),
    HID_USAGE_AC_SNOOZE_ALARM = MAKE_USAGE(0x0c, 0x284),
    HID_USAGE_AC_RESET_ALARM = MAKE_USAGE(0x0c, 0x285),
    HID_USAGE_AC_SYNCHRONIZE = MAKE_USAGE(0x0c, 0x286),
    HID_USAGE_AC_SEND_SLASHRECEIVE = MAKE_USAGE(0x0c, 0x287),
    HID_USAGE_AC_SEND_TO = MAKE_USAGE(0x0c, 0x288),
    HID_USAGE_AC_REPLY = MAKE_USAGE(0x0c, 0x289),
    HID_USAGE_AC_REPLY_ALL = MAKE_USAGE(0x0c, 0x28a),
    HID_USAGE_AC_FORWARD_MSG = MAKE_USAGE(0x0c, 0x28b),
    HID_USAGE_AC_SEND = MAKE_USAGE(0x0c, 0x28c),
    HID_USAGE_AC_ATTACH_FILE = MAKE_USAGE(0x0c, 0x28d),
    HID_USAGE_AC_UPLOAD = MAKE_USAGE(0x0c, 0x28e),
    HID_USAGE_AC_DOWNLOAD__LPARENSAVE_TARGET_AS_RPAREN = MAKE_USAGE(0x0c, 0x28f),
    HID_USAGE_AC_SET_BORDERS = MAKE_USAGE(0x0c, 0x290),
    HID_USAGE_AC_INSERT_ROW = MAKE_USAGE(0x0c, 0x291),
    HID_USAGE_AC_INSERT_COLUMN = MAKE_USAGE(0x0c, 0x292),
    HID_USAGE_AC_INSERT_FILE = MAKE_USAGE(0x0c, 0x293),
    HID_USAGE_AC_INSERT_PICTURE = MAKE_USAGE(0x0c, 0x294),
    HID_USAGE_AC_INSERT_OBJECT = MAKE_USAGE(0x0c, 0x295),
    HID_USAGE_AC_INSERT_SYMBOL = MAKE_USAGE(0x0c, 0x296),
    HID_USAGE_AC_SAVE_AND_CLOSE = MAKE_USAGE(0x0c, 0x297),
    HID_USAGE_AC_RENAME = MAKE_USAGE(0x0c, 0x298),
    HID_USAGE_AC_MERGE = MAKE_USAGE(0x0c, 0x299),
    HID_USAGE_AC_SPLIT = MAKE_USAGE(0x0c, 0x29a),
    HID_USAGE_AC_DISRIBUTE_HORIZONTALLY = MAKE_USAGE(0x0c, 0x29b),
    HID_USAGE_AC_DISTRIBUTE_VERTICALLY = MAKE_USAGE(0x0c, 0x29c),
    /* USAGE PAGE:  Generic_Desktop */
#define HID_USAGE_PAGE_GENERIC_DESKTOP 0x01

    HID_USAGE_UNDEFINED = MAKE_USAGE(0x01, 0x00),
    HID_USAGE_POINTER = MAKE_USAGE(0x01, 0x01),
    HID_USAGE_MOUSE = MAKE_USAGE(0x01, 0x02),
    HID_USAGE_JOYSTICK = MAKE_USAGE(0x01, 0x04),
    HID_USAGE_GAME_PAD = MAKE_USAGE(0x01, 0x05),
    HID_USAGE_KEYBOARD = MAKE_USAGE(0x01, 0x06),
    HID_USAGE_KEYPAD = MAKE_USAGE(0x01, 0x07),
    HID_USAGE_MULTI_MINUSAXIS_CONTROLLER = MAKE_USAGE(0x01, 0x08),
    HID_USAGE_TABLET_PC_SYSTEM_CONTROLS = MAKE_USAGE(0x01, 0x09),
    HID_USAGE_X = MAKE_USAGE(0x01, 0x30),
    HID_USAGE_Y = MAKE_USAGE(0x01, 0x31),
    HID_USAGE_Z = MAKE_USAGE(0x01, 0x32),
    HID_USAGE_RX = MAKE_USAGE(0x01, 0x33),
    HID_USAGE_RY = MAKE_USAGE(0x01, 0x34),
    HID_USAGE_RZ = MAKE_USAGE(0x01, 0x35),
    HID_USAGE_SLIDER = MAKE_USAGE(0x01, 0x36),
    HID_USAGE_DIAL = MAKE_USAGE(0x01, 0x37),
    HID_USAGE_WHEEL = MAKE_USAGE(0x01, 0x38),
    HID_USAGE_HAT_SWITCH = MAKE_USAGE(0x01, 0x39),
    HID_USAGE_COUNTED_BUFFER = MAKE_USAGE(0x01, 0x3a),
    HID_USAGE_BYTE_COUNT = MAKE_USAGE(0x01, 0x3b),
    HID_USAGE_MOTION_WAKEUP = MAKE_USAGE(0x01, 0x3c),
    HID_USAGE_START = MAKE_USAGE(0x01, 0x3d),
    HID_USAGE_SELECT = MAKE_USAGE(0x01, 0x3e),
    HID_USAGE_VX = MAKE_USAGE(0x01, 0x40),
    HID_USAGE_VY = MAKE_USAGE(0x01, 0x41),
    HID_USAGE_VZ = MAKE_USAGE(0x01, 0x42),
    HID_USAGE_VBRX = MAKE_USAGE(0x01, 0x43),
    HID_USAGE_VBRY = MAKE_USAGE(0x01, 0x44),
    HID_USAGE_VBRZ = MAKE_USAGE(0x01, 0x45),
    HID_USAGE_VNO = MAKE_USAGE(0x01, 0x46),
    HID_USAGE_FEATURE_NOTIFICATION = MAKE_USAGE(0x01, 0x47),
    HID_USAGE_RESOLUTION_MULTIPLIER = MAKE_USAGE(0x01, 0x48),
    HID_USAGE_SYSTEM_CONTROL = MAKE_USAGE(0x01, 0x80),
    HID_USAGE_SYSTEM_POWER_DOWN = MAKE_USAGE(0x01, 0x81),
    HID_USAGE_SYSTEM_SLEEP = MAKE_USAGE(0x01, 0x82),
    HID_USAGE_SYSTEM_WAKE_UP = MAKE_USAGE(0x01, 0x83),
    HID_USAGE_SYSTEM_CONTEXT_MENU = MAKE_USAGE(0x01, 0x84),
    HID_USAGE_SYSTEM_MAIN_MENU = MAKE_USAGE(0x01, 0x85),
    HID_USAGE_SYSTEM_APP_MENU = MAKE_USAGE(0x01, 0x86),
    HID_USAGE_SYSTEM_MENU_HELP = MAKE_USAGE(0x01, 0x87),
    HID_USAGE_SYSTEM_MENU_EXIT = MAKE_USAGE(0x01, 0x88),
    HID_USAGE_SYSTEM_MENU_SELECT = MAKE_USAGE(0x01, 0x89),
    HID_USAGE_SYSTEM_MENU_RIGHT = MAKE_USAGE(0x01, 0x8a),
    HID_USAGE_SYSTEM_MENU_LEFT = MAKE_USAGE(0x01, 0x8b),
    HID_USAGE_SYSTEM_MENU_UP = MAKE_USAGE(0x01, 0x8c),
    HID_USAGE_SYSTEM_MENU_DOWN = MAKE_USAGE(0x01, 0x8d),
    HID_USAGE_SYSTEM_COLD_RESTART = MAKE_USAGE(0x01, 0x8e),
    HID_USAGE_SYSTEM_WARM_RESTART = MAKE_USAGE(0x01, 0x8f),
    HID_USAGE_D_MINUSPAD_UP = MAKE_USAGE(0x01, 0x90),
    HID_USAGE_D_MINUSPAD_DOWN = MAKE_USAGE(0x01, 0x91),
    HID_USAGE_D_MINUSPAD_RIGHT = MAKE_USAGE(0x01, 0x92),
    HID_USAGE_D_MINUSPAD_LEFT = MAKE_USAGE(0x01, 0x93),
    HID_USAGE_SYSTEM_DOCK = MAKE_USAGE(0x01, 0xa0),
    HID_USAGE_SYSTEM_UNDOCK = MAKE_USAGE(0x01, 0xa1),
    HID_USAGE_SYSTEM_SETUP = MAKE_USAGE(0x01, 0xa2),
    HID_USAGE_SYSTEM_BREAK = MAKE_USAGE(0x01, 0xa3),
    HID_USAGE_SYSTEM_DEBUGGER_BREAK = MAKE_USAGE(0x01, 0xa4),
    HID_USAGE_APPLICATION_BREAK = MAKE_USAGE(0x01, 0xa5),
    HID_USAGE_APPLICATION_DEBUGGER_BREAK = MAKE_USAGE(0x01, 0xa6),
    HID_USAGE_SYSTEM_SPEAKER_MUTE = MAKE_USAGE(0x01, 0xa7),
    HID_USAGE_SYSTEM_HIBERNATE = MAKE_USAGE(0x01, 0xa8),
    HID_USAGE_SYSTEM_DISPLAY_INVERT = MAKE_USAGE(0x01, 0xb0),
    HID_USAGE_SYSTEM_DISPLAY_INTERNAL = MAKE_USAGE(0x01, 0xb1),
    HID_USAGE_SYSTEM_DISPLAY_EXTERNAL = MAKE_USAGE(0x01, 0xb2),
    HID_USAGE_SYSTEM_DISPLAY_BOTH = MAKE_USAGE(0x01, 0xb3),
    HID_USAGE_SYSTEM_DISPLAY_DUAL = MAKE_USAGE(0x01, 0xb4),
    HID_USAGE_SYSTEM_DISPLAY_TOGGLE_INT_SLASHEXT = MAKE_USAGE(0x01, 0xb5),
    HID_USAGE_SYSTEM_DISPLAY_SWAP_PRIMARY_SLASHSECONDARY = MAKE_USAGE(0x01, 0xb6),
    HID_USAGE_SYSTEM_DISPLAY_LCD_AUTOSCALE = MAKE_USAGE(0x01, 0xb7),

} Usage;

typedef enum {
    NONE  = 0,
    L_CTL = (1<<0),
    L_SHF = (1<<1),
    L_ALT = (1<<2),
    L_GUI = (1<<3),
    R_CTL = (1<<4),
    R_SHF = (1<<5),
    R_ALT = (1<<6),
    R_GUI = (1<<7),
    A_CTL = (1<<8),
    A_SHF = (1<<9),
    A_ALT = (1<<10),
    A_GUI = (1<<11),
} Modifier;

static inline
Modifier
get_modifier(Usage usage)
{
    switch(usage) {
    case HID_USAGE_LEFT_CONTROL:
        return L_CTL;
    case HID_USAGE_LEFT_SHIFT:
        return L_SHF;
    case HID_USAGE_LEFT_ALT:
        return L_ALT;
    case HID_USAGE_LEFT_GUI:
        return L_GUI;
    case HID_USAGE_RIGHT_CONTROL:
        return R_CTL;
    case HID_USAGE_RIGHT_SHIFT:
        return R_SHF;
    case HID_USAGE_RIGHT_ALT:
        return R_ALT;
    case HID_USAGE_RIGHT_GUI:
        return R_GUI;
    default:
        return NONE;
    }
}


#endif // __HHSTDIO_H__
