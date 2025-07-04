### src/drivers/hal/gpio.c / .h - General Purpose IO multiplatform wrapper

##### Macros:
```C
GPIO_MAKE_FUNCTION(function, pin) 
```
###### Description
Macro used for setting desired pin function inside `gpio_setFunction()`<br><br>
This macro does not need third <*shift*> parameter, but works in the same way as lower (eg. ***RPI_HAL_GPIO_ALT_FUNCTION_MAKER***) Hardware Abstraction Layer (HAL) libraries.

###### Parameters
- <*function*> - desired pin function (eg. gpio_functionSelect_input)
- <*pin*> - pin number (eg. 1)

###### Example usage
```C
#include "driver/hal/gpio.h" // Location could differ
#include "hal/rpi/bcm283x_gpio.h" // For gpio_functionSelect_output
#define LED_PIN 13

...

int kernel_main() {
    ...
    // LED_PIN (pin 13) as a output
    gpio_setFunction(GPIO_MAKE_FUNCTION(gpio_functionSelect_output, LED_PIN));
    ...
}
```

##### Functions:
```C
void gpio_setFunction(const uint32_t function);
``` 
###### Description
General Purpose Input/Output (GPIO) function for setting desired pin function. Should be used with ***GPIO_MAKE_FUNCTION*** or any lower level function maker macro like ***RPI_HAL_GPIO_ALT_FUNCTION_MAKER***.
Also can take predefined values from ***rpi_hal_gpio_functionSelect_allAltFunctions*** enum.

###### Parameters
- <*function*> - desired pin function along with encoded pin and shift (eg. GPIO_MAKE_FUNCTION(gpio_functionSelect_output, 2) )

###### Example usage
```C
#include "driver/hal/gpio.h" // Location could differ
#include "hal/rpi/bcm283x_gpio.h" // For gpio_functionSelect_output
#define LED_PIN 13

...

int kernel_main() {
    ...
    // LED_PIN (pin 13) as a output
    gpio_setFunction(GPIO_MAKE_FUNCTION(gpio_functionSelect_output, LED_PIN));
    ...

    // Pin 11 with alternate function 0 (SPI clock)
    // This is basically same as gpio_setFunction(GPIO_MAKE_FUNCTION(gpio_functionSelect_alt0, 11))
    gpio_setFunction(gpio11_functionSelect_alt0_spi0_sclk);
    ...
}
```

-----

```C
void gpio_setOutput(const uint8_t pin, const uint8_t state);
```

###### Description
Sets output on desired pin to low or high state, on **<*state*> == 0** pin is low, on **<*state*> != 0** pin is high. <br>
For manipulating desired pin state, you need to call `gpio_setFunction(GPIO_MAKE_FUNCTION(gpio_functionSelect_output, <pin>));` before to prepare pin as output.

###### Parameters
- <*pin*> - desired pin to manipulate state of
- <*state*> - state of pin, **0 = low**, **!0 = high**

###### Example usage
```C
#include "driver/hal/gpio.h" // Location could differ
#include "hal/rpi/bcm283x_gpio.h" // For gpio_functionSelect_output
#define LED_PIN 13

...

int kernel_main() {
    ...
    // LED_PIN (pin 13) as a output
    gpio_setFunction(GPIO_MAKE_FUNCTION(gpio_functionSelect_output, LED_PIN));
    ...

    // Set output as high
    gpio_setOutput(LED_PIN, 1);

    // Set output as low
    gpio_setOutput(LED_PIN, 0);
    ...
}

```

-----

```C
uint32_t gpio_getInput(const uint8_t pin);
```

###### Description
Gets desired pin state. For getting desired pin state, you need to call `gpio_setFunction(GPIO_MAKE_FUNCTION(gpio_functionSelect_input, <pin>));` before to prepare pin as input.

###### Parameters
- <*pin*> - desired pin that should return it's state

###### Return value
- 0 - pin state is low
- !0 - pin state is high

###### Example usage
```C
#include "driver/hal/gpio.h" // Location could differ
#include "hal/rpi/bcm283x_gpio.h" // For gpio_functionSelect_output
#define LED_PIN 13
#define BUTTON_PIN 12

...

int kernel_main() {
    ...
    gpio_setFunction(GPIO_MAKE_FUNCTION(gpio_functionSelect_output, LED_PIN));
    gpio_setFunction(GPIO_MAKE_FUNCTION(gpio_functionSelect_input, BUTTON_PIN));
    ...

    // Check if pin state is high
    if(gpio_getInput(BUTTON_PIN))
        // Set output as high
        gpio_setOutput(LED_PIN, 1);
    else 
        // Set output as low
        gpio_setOutput(LED_PIN, 0);
    ...
}

```

