#include "bcm283x_gic.h"

void rpi_hal_gic_init() {
  (*(rpi_hal_io32_t*)RPI_HAL_GIC_CTL) = 1;
  gicInt.control = 1;
  gicInt.priMask = 0xFF;
}

void rpi_hal_gic_enableIRQ(const rpi_hal_uint32_t irq) {
  (*(rpi_hal_io32_t*)(unsigned long)(RPI_HAL_GIC_ENABLE_SET + (irq / 32) * 4)) = (1 << (irq % 32)); 
}

void rpi_hal_gic_disableIRQ(const rpi_hal_uint32_t irq) {
  (*(rpi_hal_io32_t*)(unsigned long)(RPI_HAL_GIC_ENABLE_CLEAR + (irq / 32) * 4)) = (1 << (irq % 32));
}

rpi_hal_uint32_t rpi_hal_gic_getIRQ();

void rpi_hal_gic_ackIRQ(const rpi_hal_uint32_t irq);
