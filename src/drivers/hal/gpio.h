/**
 * This src/drivers/hal/ is another abstraction layer to wrap every CPU/MCU/SoC into 1 library
 * This libraries are rather simple and only wraps lower level HALs
 * Naming convenction is self explainatory
 */

#ifndef _PPDOS_DRIVER_HAL_GPIO_
#define _PPDOS_DRIVER_HAL_GPIO_

#include "../../common/shared_defs.h"

// This must be the same as x_hal_gpio, for convinience reasons
// Macro used for setting desired pin function inside gpio_setFunction()
// This macro does not need third <shift> parameter, but works in the same way as lower (eg. RPI_HAL_GPIO_ALT_FUNCTION_MAKER) Hardware Abstraction Layer (HAL) libraries.
#define GPIO_MAKE_FUNCTION(function, pin) ((uint32_t)(altFunction & 0x7) | ((uint32_t)(pin & 0x3F) << 3) | ((uint32_t)(((pin % 10) * 3) & 0x1F) << 9))
#define GPIO_MAKE_FUNCTION_FUNCTION_MASK  0x0007
#define GPIO_MAKE_FUNCTION_PIN_MASK       0x01F8
#define GPIO_MAKE_FUNCTION_SHIFT_MASK     0x3F00

// General Purpose Input/Output (GPIO) function for setting desired pin function. Should be used with GPIO_MAKE_FUNCTION or any lower level function maker like RPI_HAL_GPIO_ALT_FUNCTION_MAKER.
// Also can take predefined values from rpi_hal_gpio_functionSelect_allAltFunctions enum.
void gpio_setFunction(const uint32_t function);

// Sets output on desired pin to low or high state, on <state> == 0 pin is low, on <state> != 0 pin is high.
// For manipulating desired pin state, you need to call gpio_setFunction(GPIO_MAKE_FUNCTION(gpio_functionSelect_output, <pin>)); before to prepare pin as output.
void gpio_setOutput(const uint8_t pin, const uint8_t state);

// Gets desired pin state. For getting desired pin state, you need to call gpio_setFunction(GPIO_MAKE_FUNCTION(gpio_functionSelect_input, <pin>)); before to prepare pin as input.
uint32_t gpio_getInput(const uint8_t pin);

#endif
