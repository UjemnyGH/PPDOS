#ifndef _PPDOS_HAL_BCM283X_CSI_
#define _PPDOS_HAL_BCM283X_CSI_

#include "bcm283x_regs.h"

typedef struct rpi_hal_csi_clkgate_s {
  rpi_hal_io32_t csi0ClkGate;
  rpi_hal_io32_t csi1ClkGate;
} rpi_hal_csi_clkgate_t;

#define csiClkGate              (*(rpi_hal_csi_clkgate_t*)(RPI_HAL_CSI0_BASE + 0x2000))

#endif
