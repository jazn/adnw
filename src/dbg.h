#ifndef __DBG_H__
#define __DBG_H__

#define print(s)    printf(s)
#define println(s)  printf(s "\n")
#define xprintf     printf
#define phex(s)     printf("%02x", s)

/// define DEBUG_OUTPUT in makefile to enable printf() for hid_listen.
#ifdef DEBUG_OUTPUT
    #include "Descriptors.h"
    #include "hhstdio.h"
    #include "mem-check.h"

    typedef struct {
        char data[DBG_EPSIZE];
    } USB_DBGReport_Data_t;

    uint8_t DBG__get_report(USB_DBGReport_Data_t* report);

    #define TRACE(...)

#else
    #define TRACE(...)
    #define printf(...)
    
    typedef struct {
        char data[0];
    } USB_DBGReport_Data_t;

    uint8_t DBG__get_report(USB_DBGReport_Data_t* report); // { return 0; } ;
#endif

#endif // __DBG_H__
