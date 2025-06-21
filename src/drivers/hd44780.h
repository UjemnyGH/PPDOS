#ifndef _PPDOS_DRIVER_HD44780_
#define _PPDOS_DRIVER_HD44780_

#include "../common/shared_fn.h"

#define HD44780_UNUSED_PIN  0xFF

typedef struct hd44780_s {
  uint8_t registerSelPin;
  uint8_t enablePin;
  uint8_t dataPins[8];
} hd44780_t;

enum hd_lcd_instructions {
  hd_lcd_instruction_clearDisplay   = 0x01,
  hd_lcd_instruction_returnHome     = 0x02,
  hd_lcd_instruction_entryModeSet   = 0x04,
  hd_lcd_instruction_displayControl = 0x08,
  hd_lcd_instruction_displayShift   = 0x10,
  hd_lcd_instruction_functionSet    = 0x20,
  hd_lcd_instruction_setCGRAMAddr   = 0x40,
  hd_lcd_instruction_setDDRAMAddr   = 0x80
};

enum hd_lcd_entryMode {
  hd_lcd_entryMode_displayShift = 0x1,
  hd_lcd_entryMode_increment    = 0x2
};

enum hd_lcd_displayControl {
  hd_lcd_displayControl_blinkingOn  = 0x1,
  hd_lcd_displayControl_cursorOn    = 0x2,
  hd_lcd_displayControl_displayOn   = 0x4
};

enum hd_lcd_displayShift {
  hd_lcd_displayShift_shiftRight    = 0x4,
  hd_lcd_displayShift_displayShift  = 0x8
};

enum hd_lcd_function {
  hd_lcd_function_5x10Dots  = 0x4,
  hd_lcd_function_2Lines    = 0x8,
  hd_lcd_function_8Bits     = 0x10,
};

void hd44780_init4(hd44780_t* const pHd, uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

void hd44780_clear(hd44780_t* const pHd);

void hd44780_home(hd44780_t* const pHd);

void hd44780_cursor(hd44780_t* const pHd, uint8_t col, uint8_t row);

//void hd44780_init8(hd44780_t* const pHd, uint8_t rs, uint8_t en, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

void hd44780_print(hd44780_t* const pHd, const char* text);

//void hd44780_printf(hd44780_t* const pHd, const char* fmt, ...);

#endif
