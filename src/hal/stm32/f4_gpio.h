#ifndef _PPDOS_HAL_STM32F4_GPIO_
#define _PPDOS_HAL_STM32F4_GPIO_

#include "f4_rcc.h"

typedef struct {
  f4_hal_io32_t mode;
  f4_hal_io32_t outputType;
  f4_hal_io32_t outputSpeed;
  f4_hal_io32_t pull;
  f4_hal_io32_t inputData;
  f4_hal_io32_t outputData;
  f4_hal_io32_t bitSetReset;
  f4_hal_io32_t configLock;
  f4_hal_io32_t altFuncLow;
  f4_hal_io32_t altFuncHigh;
} __attribute__((packed)) f4_hal_gpio_t;

enum f4_hal_gpio_mode {
  gpio_mode_input     = 0x0,
  gpio_mode_output    = 0x1,
  gpio_mode_altFunc   = 0x2,
  gpio_mode_analog    = 0x3,

  gpio_mode_reset     = 0x0,
  gpio_mode_resetA    = 0xA8000000,
  gpio_mode_resetB    = 0x00000280
};

enum f4_hal_gpio_outputType {
  gpio_outputType_pushPull  = 0x0,
  gpio_outputType_openDrain = 0x1,
  gpio_outputType_reset     = 0x0
};

enum f4_hal_gpio_outputSpeed {
  gpio_outputSpeed_low    = 0x0,
  gpio_outputSpeed_medium = 0x1,
  gpio_outputSpeed_fast   = 0x2,
  gpio_outputSpeed_high   = 0x3,

  gpio_outputSpeed_reset  = 0x0,
  gpio_outputSpeed_resetA = 0x0C000000,
  gpio_outputSpeed_resetB = 0x000000C0
};

enum f4_hal_gpio_pull {
  gpio_pull_none    = 0x0,
  gpio_pull_up      = 0x1,
  gpio_pull_down    = 0x2,

  gpio_pull_reset   = 0x0,
  gpio_pull_resetA  = 0x64000000,
  gpio_pull_resetB  = 0x00000100,
};

#define gpioA   (*(f4_hal_gpio_t*)F4_HAL_GPIOA_BASE)
#define gpioB   (*(f4_hal_gpio_t*)F4_HAL_GPIOB_BASE)
#define gpioC   (*(f4_hal_gpio_t*)F4_HAL_GPIOC_BASE)
#define gpioD   (*(f4_hal_gpio_t*)F4_HAL_GPIOD_BASE)
#define gpioE   (*(f4_hal_gpio_t*)F4_HAL_GPIOE_BASE)
#define gpioH   (*(f4_hal_gpio_t*)F4_HAL_GPIOH_BASE)

void f4_hal_initGPIO(f4_hal_gpio_t* const pGpio);

void f4_hal_setPinMode(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin, const enum f4_hal_gpio_mode mode);

void f4_hal_setOutputType(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin, const enum f4_hal_gpio_outputType type);

void f4_hal_setOutputSpeed(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin, const enum f4_hal_gpio_outputSpeed speed);

void f4_hal_setPull(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin, const enum f4_hal_gpio_pull pull);

void f4_hal_setOutput(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin, const f4_hal_uint8_t state);

void f4_hal_setBit(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin);

void f4_hal_clearBit(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin);

f4_hal_uint32_t f4_hal_getInput(f4_hal_gpio_t* const pGpio, const f4_hal_uint8_t pin);

#endif
