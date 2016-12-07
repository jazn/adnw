#ifndef TMK_MISSING_H
#define TMK_MISSING_H

/** Missing includes or defines from TMK PS/2 import.
 * These are simply put here to not clutter the originl sources too much
 */


// #include "wait.h"
#if defined(__AVR__)
#   include <util/delay.h>
#   define wait_ms(ms)  _delay_ms(ms)
#   define wait_us(us)  _delay_us(us)
#endif

// #include "print.h"
#include "../config.h"
#include "../hhstdio.h"
#define print(s)    printf(s)
#define println(s)  printf(s "\n")
#define xprintf     printf
#define phex(s)     printf("%02x", s)


#endif
