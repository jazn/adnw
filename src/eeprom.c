#include "eeprom.h"

/*
uint8_t EEMEM  eeFooByte = 0x12;

uint16_t EEMEM eeFooWord = 0x345;

float eeFooFloat EEMEM;

uint8_t eeFooByteArray1[] EEMEM = { 0x11, 0x22, 0x33 };
uint8_t eeFooByteArray2[] EEMEM = { 0x44, 0x55, 0x66 };

uint16_t eeFooWordArray1[4] EEMEM;

static uint8_t EEMEM SFR = 0xFF;
*/

uint8_t readMacro(uint8_t * macro/*[MACROLEN]*/, uint8_t idx)
{
    printf("\nEE readMacro #%d @%d", idx,EE_ADDR_MACRO(idx) );
    eeprom_read_block (( void *) macro , ( const void *) EE_ADDR_MACRO(idx) , MACROLEN);
    //macro[MACROLEN-1]='\0';
    printf(" : \"%s\"", macro );

    return 0;
}


uint8_t writeMacro(uint8_t * macro/*[MACROLEN]*/, uint8_t idx)
{

    printf("\n### EE WRITE #### ");
    //uint8_t str[MACROLEN];
    //readMacro(str, idx);
    eeprom_update_block (( const void *) macro , (void *) EE_ADDR_MACRO(idx) , MACROLEN);
    //readMacro(str, idx);

    return 0;
    /*

    eeprom_update_byte(&SFR, 128);
    uint8_t myByte;

    // myByte lesen (Wert = 123)
    myByte = eeprom_read_byte (&eeFooByte);

    // der Wert 99 wird im EEPROM an die Adresse der
    // Variablen eeFooByte geschrieben
    myByte = 99;
    eeprom_write_byte(&eeFooByte, myByte); // schreiben

    myByte = eeprom_read_byte (&eeFooByteArray1[1]);
    // myByte hat nun den Wert 3

    // Beispiel zur "Sicherung" gegen leeres EEPROM nach "Chip Erase"
    // (z. B. wenn die .eep-Datei nach Programmierung einer neuen Version
    // des Programms nicht in den EEPROM uebertragen wurde und EESAVE
    // deaktiviert ist (unprogrammed/1)
    //
    // Vorsicht: wenn EESAVE "programmed" ist, hilft diese Sicherung nicht
    // weiter, da die Speicheraddressen in einem neuen/erweiterten Programm
    // moeglicherweise verschoben wurden. An der Stelle &eeFooByte steht
    // dann u.U. der Wert einer anderen Variable aus einer "alten" Version.

    uint8_t fooByteDefault = 222;
    if ((myByte = eeprom_read_byte (&eeFooByte)) == EEPROM_DEF)
    {
        myByte = fooByteDefault;
    }
    */
}
