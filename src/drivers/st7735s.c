#include "st7735s.h"
#include "../hal/rpi/bcm283x_gpio.h"
#include "../hal/rpi/bcm283x_spi.h"
#include "../common/shared_fn.h"
#include "../common/pp_memory.h"

void _st7735_select(st7735s_t* const pSt) {
  rpi_hal_spi_init(4);

  if(pSt->chipSelectPin == ST7735_USE_SPI_DEFAULT_CS1)
    rpi_hal_spi_chipSelect(1);
  else
    rpi_hal_gpio_setOutputClear(pSt->chipSelectPin);
}

void _st7735_deselect(st7735s_t* const pSt) {
  if(pSt->chipSelectPin == ST7735_USE_SPI_DEFAULT_CS1)
    rpi_hal_spi_chipSelect(0);
  else 
    rpi_hal_gpio_setOutputSet(pSt->chipSelectPin);

  rpi_hal_spi_deinit();
}

void _st7735_sendCommand(st7735s_t* const pSt, const enum st7735s_command command) {
  rpi_hal_gpio_setOutputClear(pSt->dataCommandPin);

  delay_us(1);

  rpi_hal_spi_transferByte((uint8_t)command);

  delay_us(1);
}

void _st7735_sendDataByte(st7735s_t* const pSt, const uint8_t data) {
  rpi_hal_gpio_setOutputSet(pSt->dataCommandPin);

  delay_us(1);

  rpi_hal_spi_transferByte(data);

  delay_us(1);
}

void _st7735_sendData(st7735s_t* const pSt, const uint8_t* pData, const uint32_t length) {
  rpi_hal_gpio_setOutputSet(pSt->dataCommandPin);

  delay_us(1);

  rpi_hal_spi_transfer(pData, (uint8_t*)0, length);

  delay_us(1);
}

void _st7735_sendDMAData(st7735s_t* const pSt, const uint8_t* pData, const uint32_t length) {
  rpi_hal_gpio_setOutputSet(pSt->dataCommandPin);

  delay_us(1);

  rpi_hal_spi_dmaTransfer(0, pData, (uint8_t*)0, length);

  delay_us(1);
}

void st7735_switchInterfacePixelFormat(st7735s_t* const pSt, const enum st_interPixelFormat pixelFormat) {
  _st7735_select(pSt);

  _st7735_sendCommand(pSt, st_command_interPixelFormat);
  _st7735_sendDataByte(pSt, pixelFormat);

  _st7735_deselect(pSt);
}

void st7735_reset(st7735s_t *const pSt) {
  rpi_hal_gpio_setOutputSet(pSt->resetPin);
  delay_ms(50);
  rpi_hal_gpio_setOutputClear(pSt->resetPin);
  delay_ms(50);
  rpi_hal_gpio_setOutputSet(pSt->resetPin);
  delay_ms(150);
}

void st7735_init(st7735s_t* const pSt, uint8_t rst, uint8_t dc, uint8_t bl, uint8_t cs) {
  pSt->backlightPin = bl;
  pSt->chipSelectPin = cs;
  pSt->dataCommandPin = dc;
  pSt->resetPin = rst;

  /*For ce0 would be gpio8*/
  if(pSt->chipSelectPin == ST7735_USE_SPI_DEFAULT_CS1) {
    rpi_hal_gpio_setSpecialAltFunction(gpio7_functionSelect_alt0_spi0_ce1_n);
    rpi_hal_gpio_setPinPullEnableClock(7);
  }
  else
    rpi_hal_gpio_setFunction(pSt->chipSelectPin, gpio_functionSelect_output);
  /* Useless for now */
  //rpi_hal_gpio_setSpecialAltFunction(gpio9_functionSelect_alt0_spi0_miso);
  rpi_hal_gpio_setSpecialAltFunction(gpio10_functionSelect_alt0_spi0_mosi);
  rpi_hal_gpio_setSpecialAltFunction(gpio11_functionSelect_alt0_spi0_sclk);

  /* Setup other pins that uses gpio */
  rpi_hal_gpio_setFunction(pSt->backlightPin, gpio_functionSelect_output);
  rpi_hal_gpio_setFunction(pSt->dataCommandPin, gpio_functionSelect_output);
  rpi_hal_gpio_setFunction(pSt->resetPin, gpio_functionSelect_output);
  
  rpi_hal_gpio_setPinPullEnableClock(10);
  rpi_hal_gpio_setPinPullEnableClock(11);

  rpi_hal_gpio_setPinPullEnableClock(pSt->dataCommandPin);

  rpi_hal_gpio_setPullEnable(gpio_pinPullEnable_pullDown);

  _st7735_select(pSt);

  st7735_reset(pSt);

  _st7735_sendCommand(pSt, st_command_softReset);
  delay_ms(150);

  _st7735_sendCommand(pSt, st_command_sleepOut);
  delay_ms(150); 

  _st7735_sendCommand(pSt, st_command_frameCtl1Normal);
  uint8_t frameControl[] = { 0x01, 0x2C, 0x2D };
  _st7735_sendData(pSt, frameControl, sizeof(frameControl));

  _st7735_sendCommand(pSt, st_command_frameCtl2Idle);
  _st7735_sendData(pSt, frameControl, sizeof(frameControl));

  _st7735_sendCommand(pSt, st_command_displayInvCtl);
  _st7735_sendDataByte(pSt, 0x07);

  _st7735_sendCommand(pSt, st_command_powerCtl1);
  uint8_t powerCtl1[] = { 0xA2, 0x02, 0x84 };
  _st7735_sendData(pSt, powerCtl1, sizeof(powerCtl1));

  _st7735_sendCommand(pSt, st_command_powerCtl2);
  _st7735_sendDataByte(pSt, 0xC5);

  _st7735_sendCommand(pSt, st_command_powerCtl3Normal);
  uint8_t powerCtlNormal[] = { 0x0A, 0x00 };
  _st7735_sendData(pSt, powerCtlNormal, sizeof(powerCtlNormal));

  _st7735_sendCommand(pSt, st_command_powerCtl4Idle);
  uint8_t powerCtlIdle[] = { 0x8A, 0x2A };
  _st7735_sendData(pSt, powerCtlIdle, sizeof(powerCtlIdle));

  _st7735_sendCommand(pSt, st_command_powerCtl5Partial);
  uint8_t powerCtlPartial[] = { 0x8A, 0xEE };
  _st7735_sendData(pSt, powerCtlPartial, sizeof(powerCtlPartial));

  _st7735_sendCommand(pSt, st_command_vcomCtl1);
  _st7735_sendDataByte(pSt, 0x0E);

  _st7735_sendCommand(pSt, st_command_inversionOff);

  _st7735_sendCommand(pSt, st_command_memDataAccessCtl);
  _st7735_sendDataByte(pSt, st_memDataAccessCtl_rowColExch | st_memDataAccessCtl_rowAddrOrd);
  delay_ms(10);

  _st7735_sendCommand(pSt, st_command_interPixelFormat);
  _st7735_sendDataByte(pSt, st_interPixelFormat_16bit);
  delay_ms(20);

  _st7735_sendCommand(pSt, st_command_gammaPlus);
  uint8_t gammaPlus[] = { 0x0F, 0x1A, 0x0F, 0x18, 0x2F, 0x28, 0x20, 0x22, 0x1F, 0x1B, 0x23, 0x37, 0x00, 0x07, 0x02, 0x10 };
  _st7735_sendData(pSt, gammaPlus, sizeof(gammaPlus));

  _st7735_sendCommand(pSt, st_command_gammaMinus);
  uint8_t gammaMinus[] = { 0x0F, 0x1B, 0x0F, 0x17, 0x33, 0x2C, 0x29, 0x2E, 0x30, 0x30, 0x39, 0x3F, 0x00, 0x07, 0x03, 0x10 };
  _st7735_sendData(pSt, gammaMinus, sizeof(gammaMinus));

  _st7735_sendCommand(pSt, st_command_partialOff);
  delay_ms(10);

  _st7735_sendCommand(pSt, st_command_displayOn);
  delay_ms(100);

  _st7735_deselect(pSt);

  rpi_hal_gpio_setOutputSet(pSt->backlightPin);

  pSt->initialized = 1;
}

void st7735_clearFrame(st7735s_t* const pSt) {
  memset(pSt->framebuffer, 0, sizeof(pSt->framebuffer));
}

void st7735_setPixel(st7735s_t* const pSt, uint8_t x, uint8_t y, uint16_t color) {
  if(x < ST7735_WIDTH && y < ST7735_HEIGHT)
    pSt->framebuffer[ST7735_WIDTH * y + x] = color;
}

void st7735_drawBuffered(st7735s_t* const pSt) {
  _st7735_select(pSt);

  uint8_t columnAddr[] = { 0, ST7735_X_OFFSET_VERT, 0, ST7735_WIDTH + ST7735_X_OFFSET_VERT - 1 };
  _st7735_sendCommand(pSt, st_command_columnAddrSet);
  _st7735_sendData(pSt, columnAddr, sizeof(columnAddr));

  uint8_t rowAddr[] = { 0, ST7735_Y_OFFSET_VERT, 0, ST7735_HEIGHT + ST7735_Y_OFFSET_VERT - 1};
  _st7735_sendCommand(pSt, st_command_rowAddrSet);
  _st7735_sendData(pSt, rowAddr, sizeof(rowAddr));

  _st7735_sendCommand(pSt, st_command_memoryWrite);

  _st7735_sendData(pSt, (uint8_t*)pSt->framebuffer, ST7735_WIDTH * ST7735_HEIGHT * sizeof(uint16_t));

  _st7735_deselect(pSt);
}

void st7735_draw18BitPixel(st7735s_t* const pSt, uint8_t x, uint8_t y, uint32_t color) {
  _st7735_select(pSt);

  uint8_t colSet[] = { 0, x + ST7735_X_OFFSET_VERT, 0, x + ST7735_X_OFFSET_VERT };
  _st7735_sendCommand(pSt, st_command_columnAddrSet);
  _st7735_sendData(pSt, colSet, sizeof(colSet));

  uint8_t rowSet[] = { 0, y + ST7735_Y_OFFSET_VERT, 0, y + ST7735_Y_OFFSET_VERT };
  _st7735_sendCommand(pSt, st_command_rowAddrSet);
  _st7735_sendData(pSt, rowSet, sizeof(rowSet));

  _st7735_sendCommand(pSt, st_command_memoryWrite);

  _st7735_sendDataByte(pSt, (color & 0xFF0000) >> 16);
  _st7735_sendDataByte(pSt, (color & 0xFF00) >> 8);
  _st7735_sendDataByte(pSt, color & 0xFF);

  _st7735_deselect(pSt);
}

void st7735_backlight(st7735s_t* const pSt, uint32_t state) {
  if(state)
    rpi_hal_gpio_setOutputSet(pSt->backlightPin);
  else
    rpi_hal_gpio_setOutputClear(pSt->backlightPin);
}

void st7735_text(st7735s_t* const pSt, const char* text, uint8_t x, uint8_t y, uint8_t size) {
  uint32_t nextCharacterX = 0;
  uint32_t nextCharacterY = 0;

  uint16_t color = ST7735_COLOR_16(0x1F, 0x3F, 0x1F);

  for(uint32_t i = 0; i < strlen(text); i++) {
    char ch = text[i];

    if(ch == '\n') {
      nextCharacterY += 8 * size;
      nextCharacterX = 0;
    }

    if(ch == '\t')
      nextCharacterX += 12 * size;

    if(x + (nextCharacterX + 6) * size > ST7735_WIDTH) {
      nextCharacterY += 8;
      nextCharacterX = 0;
    }

    if(ch == '\e' && text[i + 1] == '[') {
      uint8_t r, g, b;

      r = text[i + 2] - '0';

      if(r > 10)
        r = text[i + 2] - 'A' + 10;

      if(r > 0xF)
        r = text[i + 2] - 'a' + 10;

      g = text[i + 3] - '0';

      if(g > 10)
        g = text[i + 3] - 'A' + 10;

      if(g > 0xF)
        g = text[i + 3] - 'a' + 10;

      b = text[i + 4] - '0';

      if(r > 10)
        b = text[i + 4] - 'A' + 10;

      if(r > 0xF)
        b = text[i + 4] - 'a' + 10;

      color = ST7735_COLOR_16((uint8_t)(((float)r / (float)0xF) * 0x1F), (uint8_t)(((float)g / (float)0xF) * 0x3F), (uint8_t)(((float)b / (float)0xF) * 0x1F));

      i += 4;

      continue;
    }

    if(ch < 32)
      continue;

    for(uint8_t _x = 0; _x < 5; _x++) {
      for(uint8_t _y = 0; _y < 7; _y++) {

        for(uint8_t xi = 0; xi < size; xi++) {
          for(uint8_t yi = 0; yi < size; yi++) {
            if(ST7735_FONT5X7[ch - 32][_x] & (1 << _y))
              st7735_setPixel(pSt, x + (_x + nextCharacterX) * size + xi, y + (_y + nextCharacterY) * size + yi, color);
          }
        }

      }
    }
    
    nextCharacterX += 6;
  }
}

void st7735_text18Bit(st7735s_t* const pSt, const char* text, uint8_t x, uint8_t y, uint8_t size) {
  uint32_t nextCharacterX = 0;
  uint32_t nextCharacterY = 0;

  uint32_t color = ST7735_COLOR_18(0x3F, 0x3F, 0x3F);

  for(uint32_t i = 0; i < strlen(text); i++) {
    char ch = text[i];

    if(ch == '\n') {
      nextCharacterY += 8;
      nextCharacterX = 0;
    }

    if(ch == '\t')
      nextCharacterX += 12;

    if(nextCharacterX + x + 6 > ST7735_WIDTH) {
      nextCharacterY += 8;
      nextCharacterX = 0;
    }

    if(ch == '\e' && text[i + 1] == '[') {
      uint8_t r, g, b;

      r = text[i + 2] - '0';

      if(r > 10)
        r = text[i + 2] - 'A' + 10;

      if(r > 0xF)
        r = text[i + 2] - 'a' + 10;

      g = text[i + 3] - '0';

      if(g > 10)
        g = text[i + 3] - 'A' + 10;

      if(g > 0xF)
        g = text[i + 3] - 'a' + 10;

      b = text[i + 4] - '0';

      if(r > 10)
        b = text[i + 4] - 'A' + 10;

      if(r > 0xF)
        b = text[i + 4] - 'a' + 10;

      color = ST7735_COLOR_18((uint8_t)(((float)r / (float)0xF) * 0x3F), (uint8_t)(((float)g / (float)0xF) * 0x3F), (uint8_t)(((float)b / (float)0xF) * 0x3F));

      i += 4;

      continue;
    }

    if(ch < 32)
      continue;

    for(uint8_t _x = 0; _x < 5; _x++) {
      for(uint8_t _y = 0; _y < 7; _y++) {

        for(uint8_t xi = 0; xi < size; xi++) {
          for(uint8_t yi = 0; yi < size; yi++) {
            if(ST7735_FONT5X7[ch - 32][_x] & (1 << _y))
              st7735_draw18BitPixel(pSt, x + (_x + nextCharacterX) * size + xi, y + (_y + nextCharacterY) * size + yi, color);
          }
        }

      }
    }
    
    nextCharacterX += 6;
  }

}

