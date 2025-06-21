#include "hd44780.h"
#include "../hal/rpi/bcm283x_gpio.h"
#include "../common/pp_memory.h"
#include <stdarg.h>

void _hd44780_enable(hd44780_t* const pHd) {
  rpi_hal_gpio_setOutputSet(pHd->enablePin);
  delay_us(1);
  rpi_hal_gpio_setOutputClear(pHd->enablePin);
delay_us(50);
}

void _hd44780_write4Low(hd44780_t* const pHd, uint8_t low) {
  for(uint32_t i = 0; i < 4; i++)
    (low & (1 << i)) ? rpi_hal_gpio_setOutputSet(pHd->dataPins[i]) : rpi_hal_gpio_setOutputClear(pHd->dataPins[i]);

  _hd44780_enable(pHd);
}

void _hd44780_sendCommand(hd44780_t* const pHd, uint8_t cmd) {
  rpi_hal_gpio_setOutputClear(pHd->registerSelPin);
  _hd44780_write4Low(pHd, cmd >> 4);
  _hd44780_write4Low(pHd, cmd & 0x0F);
  delay_us(40);
}

void _hd44780_putc(hd44780_t* const pHd, int c) {
  rpi_hal_gpio_setOutputSet(pHd->registerSelPin);
  _hd44780_write4Low(pHd, (c & 0xF0) >> 4);
  _hd44780_write4Low(pHd, c & 0xF);
  delay_us(40);
}

void hd44780_init4(hd44780_t* const pHd, uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7) {
  delay_ms(50);

  pHd->enablePin = en;
  pHd->registerSelPin = rs;
  pHd->dataPins[0] = d4;
  pHd->dataPins[1] = d5;
  pHd->dataPins[2] = d6;
  pHd->dataPins[3] = d7;
  pHd->dataPins[4] = HD44780_UNUSED_PIN;
  pHd->dataPins[5] = HD44780_UNUSED_PIN;
  pHd->dataPins[6] = HD44780_UNUSED_PIN;
  pHd->dataPins[7] = HD44780_UNUSED_PIN;

  rpi_hal_gpio_setFunction(pHd->enablePin, gpio_functionSelect_output);
  rpi_hal_gpio_setFunction(pHd->registerSelPin, gpio_functionSelect_output);

  for(uint32_t i = 0; i < 4; i++)
    rpi_hal_gpio_setFunction(pHd->dataPins[i], gpio_functionSelect_output);

  rpi_hal_gpio_setOutputClear(pHd->registerSelPin);

  _hd44780_write4Low(pHd, 0x3);
  delay_ms(5);
  _hd44780_write4Low(pHd, 0x3);
  delay_ms(2);
  _hd44780_write4Low(pHd, 0x3);

  _hd44780_write4Low(pHd, 0x2);
  
  _hd44780_sendCommand(pHd, hd_lcd_instruction_functionSet | hd_lcd_function_2Lines);
  _hd44780_sendCommand(pHd, hd_lcd_instruction_displayControl);
  _hd44780_sendCommand(pHd, hd_lcd_instruction_clearDisplay);
  _hd44780_sendCommand(pHd, hd_lcd_instruction_entryModeSet | hd_lcd_entryMode_increment);
  delay_ms(2);
  _hd44780_sendCommand(pHd, hd_lcd_instruction_displayControl | hd_lcd_displayControl_displayOn);
}

void hd44780_clear(hd44780_t *const pHd) {
  _hd44780_sendCommand(pHd, hd_lcd_instruction_clearDisplay);
  delay_ms(2);
}

void hd44780_home(hd44780_t *const pHd) {
  _hd44780_sendCommand(pHd, hd_lcd_instruction_setDDRAMAddr | 0x0);
  //_hd44780_sendCommand(pHd, hd_lcd_instruction_returnHome);
}

void hd44780_cursor(hd44780_t* const pHd, uint8_t col, uint8_t row) {
  if(row > 4)
    return;

  uint8_t address = col + (row == 0 ? 0x0 : (row == 1 ? 0x40 : (row == 2 ? 0x14 : 0x54)));

  _hd44780_sendCommand(pHd, hd_lcd_instruction_setDDRAMAddr | address);
}

//void hd44780_init8(hd44780_t* const pHd, uint8_t rs, uint8_t en, uint8_t d0, uint8_t d1, uint8_t d2, uint8_t d3, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);

void hd44780_print(hd44780_t* const pHd, const char* text) {
  while(*text)
    _hd44780_putc(pHd, *text++);
}

/*void hd44780_printf(hd44780_t* const pHd, const char* fmt, ...) {
  va_list args;

  int charControl = 0;

  for(va_start(args, fmt); *fmt != 0; fmt++) {
    if(charControl) {
      switch (*fmt) {
      case 'd':
      case 'i':
        
        break;

      case 'u':

        break;

      case 'o':

        break;

      case 'x':

        break;

      case 'X':

        break;

      case 'f':

        break;

      case 'c':
        char ch = (char)va_arg(args, char);
        _hd44780_putc(pHd, ch); 
        break;

      case 's':
        char* str = (char*)va_arg(args, char*);

        for(uint32_t i = 0; i < strlen(str); i++) {
          _hd44780_putc(pHd, str[i]);
        }
        break;

      case 'p':
        
        break;

      case '%':
        _hd44780_putc(pHd, '%');
        break;

      default:
          _hd44780_putc(pHd, *fmt);
          break;
      }
    }

    charControl = (*fmt == '%');
  }

  va_end(args);
}*/
