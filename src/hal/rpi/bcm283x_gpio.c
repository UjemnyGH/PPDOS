#include "bcm283x_gpio.h"

void rpi_hal_gpio_setFunction(const rpi_hal_uint8_t pin, const enum rpi_hal_gpio_functionSelect function) {
  /* Get index of table, 10 GPIOs ber index*/
  rpi_hal_uint8_t tableIndex = pin / 10;

  /* Error check */
  if(pin > 53) return;

  /* Reset that gpio function */
  gpio.functionSelect[tableIndex] &= ~(0x7 << ((pin % 10) * 3));
  /* Then select new function */
  gpio.functionSelect[tableIndex] |= (rpi_hal_uint32_t)function << ((pin % 10) * 3);
}

void rpi_hal_gpio_setSpecialAltFunction(const enum rpi_hal_gpio_functionSelect_allAltFunctions function) {
  gpio.functionSelect[((function & RPI_HAL_GPIO_ALT_FUNCTION_MAKER_PIN_MASK) >> 3) / 10] &= ~(0x7 << ((function & RPI_HAL_GPIO_ALT_FUNCTION_MAKER_SHIFT_MASK) >> 9));
  gpio.functionSelect[((function & RPI_HAL_GPIO_ALT_FUNCTION_MAKER_PIN_MASK) >> 3) / 10] |= (function & RPI_HAL_GPIO_ALT_FUNCTION_MAKER_FUNCTION_MASK) << ((function & RPI_HAL_GPIO_ALT_FUNCTION_MAKER_SHIFT_MASK) >> 9);
}

void rpi_hal_gpio_setOutputSet(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  gpio.pinOutputSet[tableIndex] |= (state & 0x1) << (pin % 32);
}

void rpi_hal_gpio_setOutputClear(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  gpio.pinOutputClear[tableIndex] |= (state & 0x1) << (pin % 32);
}

void rpi_hal_gpio_setPinEventDetectStatus(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  gpio.pinEventDetectStat[tableIndex] |= (state & 0x1) << (pin % 32);
}

void rpi_hal_gpio_setPinRisingEdgeDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  gpio.pinRisingEdgeDetectEnable[tableIndex] |= (state & 0x1) << (pin % 32);
}

void rpi_hal_gpio_setPinFallingEdgeDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  gpio.pinFallingEdgeDetectEnable[tableIndex] |= (state & 0x1) << (pin % 32);
}

void rpi_hal_gpio_setPinHighDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  gpio.pinHighDetectEnable[tableIndex] |= (state & 0x1) << (pin % 32);
}

void rpi_hal_gpio_setPinLowDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  gpio.pinLowDetectEnable[tableIndex] |= (state & 0x1) << (pin % 32);
}

void rpi_hal_gpio_setPinAsyncRisingEdgeDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  gpio.pinAsyncRisingEdgeDetect[tableIndex] |= (state & 0x1) << (pin % 32);
}

void rpi_hal_gpio_setPinAsyncFallingEdgeDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  gpio.pinAsyncFallingEdgeDetect[tableIndex] |= (state & 0x1) << (pin % 32);
}

void rpi_hal_gpio_setPullEnable(const enum rpi_hal_gpio_pinPullEnable pull) {
  gpio.pinPullEnable = pull; 
}

void rpi_hal_gpio_setPinPullEnableClock(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  gpio.pinPullEnableClk[tableIndex] |= (state & 0x1) << (pin % 32);
}

rpi_hal_uint32_t rpi_hal_gpio_getPinLevel(const rpi_hal_uint8_t pin) {
  rpi_hal_uint8_t tableIndex = 0;

  if(pin >= 32) 
    tableIndex = 1;

  return gpio.pinLevel[tableIndex] & 1 << (pin % 32);
}

