#include "../hal/rpi/bcm283x.h"
#include "../common/pp_memory.h"
#include "../shared_defs.h"

void delay(uint64_t delay) {
  while(delay--) asm volatile ("nop");
}

void kernel_main() {
  //rpi_hal_sd_hci_initialize(); 
  
  /*Blinky on pin 17 (11th form the start)*/

  rpi_hal_gpio_setFunction(17, gpio_functionSelect_output); 

  while(1) {
    rpi_hal_gpio_setOutputSet(17);
    delay(1000000);
    rpi_hal_gpio_setOutputClear(17);
    delay(1000000);
  }
}
