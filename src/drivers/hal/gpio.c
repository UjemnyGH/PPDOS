#include "gpio.h"
// Lower level HAL is hidden from user to prevent any missuse of selected functions that only exist on some CPU/MCU/SoC
#include "../../hal/rpi/bcm283x_gpio.h"

void gpio_setFunction(const uint32_t function) {
  rpi_hal_gpio_setSpecialAltFunction(function); 
}

void gpio_setOutput(const uint8_t pin, const uint8_t state) {
  if(state)
    rpi_hal_gpio_setOutputSet(pin);
  else
    rpi_hal_gpio_setOutputClear(pin);
}

uint32_t gpio_getInput(const uint8_t pin) {
  return rpi_hal_gpio_getPinLevel(pin);
}
