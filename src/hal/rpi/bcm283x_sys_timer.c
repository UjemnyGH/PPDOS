#include "bcm283x_sys_timer.h"

unsigned long long rpi_hal_sys_timer_read() {
  return ((unsigned long long)sysTimer.counterHigh << 32) | sysTimer.counterLow;
}
