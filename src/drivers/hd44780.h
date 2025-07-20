#ifndef _PPDOS_DRIVER_HD44780_
#define _PPDOS_DRIVER_HD44780_

#include "../common/shared_fn.h"

typedef struct hd44780_s {
  uint8_t registerSelPin;
  uint8_t enablePin;
  uint8_t dataPins[8];
} hd44780_t;

void hd44780_init4(hd44780_t* const pHd, uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

void hd44780_clear(hd44780_t* const pHd);

void hd44780_home(hd44780_t* const pHd);

void hd44780_cursor(hd44780_t* const pHd, uint8_t col, uint8_t row);

//void hd44780_init8(hd44780_t* const pHd, uint8_t rs, uint8_t en, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

void hd44780_print(hd44780_t* const pHd, const char* text);

//void hd44780_printf(hd44780_t* const pHd, const char* fmt, ...);

#endif
