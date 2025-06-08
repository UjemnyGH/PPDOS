#ifndef _PPDOS_HAL_BCM283X_VC4_MAILBOX_
#define _PPDOS_HAL_BCM283X_VC4_MAILBOX_

#include "bcm283x_regs.h"

rpi_hal_uint32_t rpi_hal_vc4_mailbox_call(const rpi_hal_uint8_t channel);

void rpi_hal_vc4_enablePower();

void rpi_hal_vc4_setClock(const rpi_hal_uint32_t hz);

#endif
