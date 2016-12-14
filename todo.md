**UNSORTED TODO LIST**
==================

BUGS
----
* Compiled with TP support, firmware hangs on init if TP error / not connected
* Find leaner printf replacement

ISSUES
------
* Modifier mismatch: Press (and hold) "/" and additional character will be capitalized: 
    may be explained as "/" implies shift on german layout
* REDTILT: Left thumb rests on center key (space), while right one on second from middle (Shift)
        Win/Ctrl/Spc not like other boards...

CONFIG
----
* general configuration interface: Storage in eeprom, control via command mode menu
* dump config on request
* usage help for command mode?

LUFA
----
* inquire about upstream horizontal scroll support

Documentation
-------------
* license check on older files (hhkb)
* code
* pinout for different controllers
* case files and pictures


Trackpoint
----------
* initialization not really thought out
* document most important registers ( see trackpoint.[ch] from kernel)
* configuration editable at runtime + eeprom store
* startup even if TP is disabled
* PS/2 -> 3.3V on Raspberry Pi:
    - http://www.deater.net/weave/vmwprod/hardware/pi-ps2/
      https://github.com/deater/vmw-meter/tree/master/pi-ps2/hardware
    - Diode https://sites.google.com/site/thepihacker/ps2pi
            https://sites.google.com/site/thepirow/home/ps2pi
    - Voltage divider: https://www.seanet.com/~karllunt/bareRasPi.html

HW
--
* PS/2 pull-ups needed

Refactor
--------
* english / german host layout
* check licenses
* Code refactor: http://www.avrfreaks.net/forum/tut-modularizing-c-code-managing-large-projects?name=PNphpBB2&file=viewtopic&t=48535
    - global vars
    - static functions

Layout
------
* Alt on redtilt, Ctrl-Alt usage
* BU-TECK better?
* usage page for system keys
* copy/paste


Git
---
* hooks (beautify, sanitize)
* document workflow


Macro
-----
* dedicated macro key instead ob subcommands?
* Macro not index based but for each character?

Commandmode
-----------
* cleanup layer switching between different layouts
* read data like tp settings
* hierarchical command structure

BUGS
----
Test sizes:
* avr-nm --size-sort --print-size -td *.elf
* avr-size --mcu=atmega32u4 --format=avr *.elf

- mousekey accel not working: normal, slow, fast

Coding style
------------
* astyle --style=linux --convert-tabs --lineend=linux --indent=spaces=4  -o -O -S src/\*.[ch]
* astyle -o -O -S src/\*.[ch]
* astyle --options=$(pwd)/.astyle.rc -R "src/*.h" "src/*.c"

Ideas
-----
- copy paste on mouse middle btn on Win possible?
- prntscreen...
- openmoko touchpad?
- analog input for 2-wire matrix-scan


Thumbkey double usage
---------------------
- outmost column only on hypernano
- make lower center keys mousebuttons for TP
                               _____         _____
                              |     |       | M3  |
                              |     |       |     |
  |- HN:only                  |     |       |     |                         |- HN only, uses pinky key
 _V___________________________|_____|       |_____|_________________________V____
|     |     | ALT |CTRL |     | WIN |       | M2  | M0  | M1  |AltGr|     |MOUSE |
|     |     |     |     |     |     |       |     |     |     |     |     |      |
|     |     |     |     |SPACE| TAB |       | ESC | <-| |ENTER|     |     |      |
 -----------------------------------         ------------------------------------

Unsorted
--------
Testcases/mode
Pinkydrop again ?!

Passhash
--------
naming of key secret
url and name of alternatives
twik 
testcases
