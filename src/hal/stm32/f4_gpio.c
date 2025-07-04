#include "f4_gpio.h"

void f4_hal_initGPIO(f4_hal_gpio_t* const pGpio) {
  switch((f4_hal_uint32_t)(unsigned long)pGpio) {
    case F4_HAL_GPIOA_BASE: 
      rcc.ahb1Enable |= 0x1; 
      break;

    case F4_HAL_GPIOB_BASE: 
      rcc.ahb1Enable |= 0x2; 
      break;

    case F4_HAL_GPIOC_BASE: 
      rcc.ahb1Enable |= 0x4; 
      break;

    case F4_HAL_GPIOD_BASE: 
      rcc.ahb1Enable |= 0x8; 
      break;

    case F4_HAL_GPIOE_BASE: 
      rcc.ahb1Enable |= 0x10; 
      break;

    case F4_HAL_GPIOH_BASE: 
      rcc.ahb1Enable |= 0x80; 
      break;

    default: 
      break;
  }
}

void f4_hal_setPinMode(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin, const enum f4_hal_gpio_mode mode) {
  f4_hal_initGPIO(pGpio);

  pGpio->mode &= ~(3 << (pin * 2));
  pGpio->mode |= mode << (pin * 2);
}

void f4_hal_setOutputType(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin, const enum f4_hal_gpio_outputType type) {
  f4_hal_initGPIO(pGpio);

  pGpio->outputType &= ~(1 << pin);
  pGpio->outputType |= type << pin;
}

void f4_hal_setOutputSpeed(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin, const enum f4_hal_gpio_outputSpeed speed) {
  f4_hal_initGPIO(pGpio);

  pGpio->outputSpeed &= ~(3 << (pin * 2));
  pGpio->outputSpeed |= speed << (pin * 2);
}

void f4_hal_setPull(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin, const enum f4_hal_gpio_pull pull) {
  f4_hal_initGPIO(pGpio);

  pGpio->pull &= ~(3 << (pin * 2));
  pGpio->pull |= pull << (pin * 2);
}

void f4_hal_setOutput(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin, const f4_hal_uint8_t state) {
  f4_hal_initGPIO(pGpio);

  pGpio->outputData = (pGpio->outputData & ~(1 << pin)) | ((!!state) << pin);
}

void f4_hal_setBit(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin) {
  f4_hal_initGPIO(pGpio);

  pGpio->bitSetReset |= 1 << pin;
}

void f4_hal_clearBit(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin) {
  f4_hal_initGPIO(pGpio);

  pGpio->bitSetReset |= (1 << 16) << pin;
}

f4_hal_uint32_t f4_hal_getInput(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin) { 
  f4_hal_initGPIO(pGpio);

  return !!(pGpio->inputData & (1 << pin));
}
