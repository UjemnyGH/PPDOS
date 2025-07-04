#include "bcm283x_sys_timer.h"

unsigned long long rpi_hal_sys_timer_read() {
  return ((unsigned long long)sysTimer.counterHigh << 32) | sysTimer.counterLow;
}

void rpi_hal_sys_timer_interruptIn(const rpi_hal_uint32_t us) {
  const rpi_hal_uint32_t lNow = sysTimer.counterLow;
  sysTimer.compare[1] = lNow + us;
  sysTimer.controlStat = sysTimer_controlStat_match1;
}

