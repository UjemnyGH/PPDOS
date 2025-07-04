#ifndef _PPDOS_HAL_BCM283X_SYS_TIMER_
#define _PPDOS_HAL_BCM283X_SYS_TIMER_

#include "bcm283x_regs.h"

typedef struct rpi_hal_sys_timer_s {
  rpi_hal_io32_t controlStat;
  rpi_hal_io32_t counterLow;
  rpi_hal_io32_t counterHigh;
  rpi_hal_io32_t compare[4];
} __attribute__((packed)) rpi_hal_sys_timer_t;

enum rpi_hal_sys_timer_controlStat {
  sysTimer_controlStat_match0 = 0x1,
  sysTimer_controlStat_match1 = 0x2,
  sysTimer_controlStat_match2 = 0x4,
  sysTimer_controlStat_match3 = 0x8
};

#define sysTimer        (*(rpi_hal_sys_timer_t*)RPI_HAL_SYSTIMER_BASE)

unsigned long long rpi_hal_sys_timer_read();

void rpi_hal_sys_timer_interruptIn(const rpi_hal_uint32_t us);

#endif
