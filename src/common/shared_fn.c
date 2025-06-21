#include "shared_fn.h"
#include "../hal/rpi/bcm283x_sys_timer.h"

void delay_us(uint64_t us) {
  uint64_t start = rpi_hal_sys_timer_read();

  while(rpi_hal_sys_timer_read() - start < us);
}

void delay_ms(uint64_t ms) {
  delay_us(ms * 1000);
}
