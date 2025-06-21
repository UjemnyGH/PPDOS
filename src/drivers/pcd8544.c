#include "pcd8544.h"
#include "../common/pp_memory.h"
#include "../hal/rpi/bcm283x_spi.h"
#include "../hal/rpi/bcm283x_gpio.h"

void _pcd_select(pcd8544_t* const pPcd) {
  rpi_hal_spi_init(128);

  if(pPcd->chipSelectPin == PCD8544_USE_SPI_CS1)
    rpi_hal_spi_chipSelect(1);
  else
    rpi_hal_gpio_setOutputClear(pPcd->chipSelectPin);
}

void _pcd_deselect(pcd8544_t* const pPcd) {
  if(pPcd->chipSelectPin == PCD8544_USE_SPI_CS1)
    rpi_hal_spi_chipSelect(0);
  else
    rpi_hal_gpio_setOutputSet(pPcd->chipSelectPin);

  rpi_hal_spi_deinit();
}

void _pcd_send(pcd8544_t* const pPcd, const uint8_t data) {
  rpi_hal_gpio_setOutputClear(pPcd->dataCommandPin);

  rpi_hal_spi_transferByte(data);
}

void pcd_reset(pcd8544_t* const pPcd) {
  rpi_hal_gpio_setOutputClear(pPcd->resetPin);
  delay_ms(500);
  rpi_hal_gpio_setOutputSet(pPcd->resetPin);

  _pcd_select(pPcd);

  _pcd_send(pPcd, pcd_instruction_functionSet);
  _pcd_send(pPcd, pcd_instruction_displayControl | pcd_displayControl_normal);

  _pcd_send(pPcd, pcd_instruction_functionSet | pcd_function_extendedInstruction);
  _pcd_send(pPcd, pcd_extendedInstruction_setVop | 0x7F);
  _pcd_send(pPcd, pcd_instruction_functionSet);

  _pcd_send(pPcd, pcd_instruction_functionSet | pcd_function_extendedInstruction);
  _pcd_send(pPcd, pcd_extendedInstruction_setBias | 0x7);
  _pcd_send(pPcd, pcd_instruction_functionSet);

  _pcd_deselect(pPcd);
}

void pcd_clear(pcd8544_t* const pPcd) {
  memset(pPcd->framebuffer, 0, PCD8544_WIDTH * PCD8544_HEIGHT / 8);
}

void pcd_init(pcd8544_t* const pPcd, uint8_t rst, uint8_t dc, uint8_t bl, uint8_t cs) {
  pPcd->initialized = 0;

  pPcd->backlightPin = bl;
  pPcd->chipSelectPin = cs;
  pPcd->dataCommandPin = dc;
  pPcd->resetPin = rst;

  rpi_hal_gpio_setSpecialAltFunction(gpio10_functionSelect_alt0_spi0_mosi);
  rpi_hal_gpio_setSpecialAltFunction(gpio11_functionSelect_alt0_spi0_sclk);

  if(pPcd->chipSelectPin == PCD8544_USE_SPI_CS1)
    rpi_hal_gpio_setSpecialAltFunction(gpio7_functionSelect_alt0_spi0_ce1_n);
  else
    rpi_hal_gpio_setFunction(pPcd->chipSelectPin, gpio_functionSelect_output);

  rpi_hal_gpio_setFunction(pPcd->backlightPin, gpio_functionSelect_output);
  rpi_hal_gpio_setFunction(pPcd->dataCommandPin, gpio_functionSelect_output);
  rpi_hal_gpio_setFunction(pPcd->resetPin, gpio_functionSelect_output);

  pcd_reset(pPcd);

  rpi_hal_gpio_setOutputSet(pPcd->backlightPin);
}

void pcd_setPixel(pcd8544_t* const pPcd, uint8_t x, uint8_t y, uint32_t state) {
  if(x > PCD8544_WIDTH || y > PCD8544_HEIGHT)
    return;

  if(state)
    pPcd->framebuffer[(y / 8) * PCD8544_WIDTH + x] |= (1 << (y % 8));
  else
    pPcd->framebuffer[(y / 8) * PCD8544_WIDTH + x] &= ~(1 << (y % 8));
}

void pcd_draw(pcd8544_t* const pPcd) {
  _pcd_select(pPcd);

  _pcd_send(pPcd, pcd_instruction_functionSet);
  _pcd_send(pPcd, pcd_instruction_displayControl | pcd_displayControl_normal);

  for(uint8_t page = 0; page < PCD8544_HEIGHT / 8; page++) {
    _pcd_send(pPcd, pcd_instruction_setYAddress | page);
    _pcd_send(pPcd, pcd_instruction_setXAddress);

    rpi_hal_gpio_setOutputSet(pPcd->dataCommandPin);

    rpi_hal_spi_transfer(pPcd->framebuffer + (PCD8544_WIDTH * page), (uint8_t*)0, PCD8544_WIDTH);
  }

  _pcd_send(pPcd, pcd_instruction_setYAddress);

  _pcd_deselect(pPcd);
}

void pcd_text5x7(pcd8544_t* const pPcd, const char* text, uint8_t x, uint8_t y) {
  uint32_t nextCharacterX = 0;
  uint32_t nextCharacterY = 0;

  for(uint32_t i = 0; i < strlen(text); i++) {
    char ch = text[i];

    if(ch == '\n') {
      nextCharacterY += 8;
      nextCharacterX = 0;
    }

    if(ch == '\t')
      nextCharacterX += 12;

    if(nextCharacterX + x + 6 > PCD8544_WIDTH) {
      nextCharacterY += 8;
      nextCharacterX = 0;
    }

    if(ch < 32)
      continue;

    for(uint8_t _x = 0; _x < 5; _x++) {
      for(uint8_t _y = 0; _y < 7; _y++) {
        pcd_setPixel(pPcd, x + _x + nextCharacterX , y + _y + nextCharacterY, font5x7[ch - 32][_x] & (1 << _y));
      }
    }

    nextCharacterX += 6;
  }
}

