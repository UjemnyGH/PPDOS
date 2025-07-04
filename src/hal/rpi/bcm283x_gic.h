#ifndef _PPDOS_HAL_BCM283X_GIC_
#define _PPDOS_HAL_BCM283X_GIC_

#include "bcm283x_regs.h"

#define RPI_HAL_GIC_CTL             (RPI_HAL_GIC_DIST_BASE + 0x000)
#define RPI_HAL_GIC_ENABLE_SET      (RPI_HAL_GIC_DIST_BASE + 0x100)
#define RPI_HAL_GIC_ENABLE_CLEAR    (RPI_HAL_GIC_DIST_BASE + 0x180)
#define RPI_HAL_GIC_PRI             (RPI_HAL_GIC_DIST_BASE + 0x400)
#define RPI_HAL_GIC_CONFIG          (RPI_HAL_GIC_DIST_BASE + 0xC00)

typedef struct rpi_hal_gic_int_s {
  rpi_hal_io32_t control;
  rpi_hal_io32_t priMask;
  rpi_hal_uint32_t RESERVED0;
  rpi_hal_io32_t ia;
  rpi_hal_io32_t eoi;
} __attribute__((packed)) rpi_hal_gic_int_t;

#define gicInt    (*(rpi_hal_gic_int_t*)RPI_HAL_GIC_INT_BASE)

void rpi_hal_gic_init();

void rpi_hal_gic_enableIRQ(const rpi_hal_uint32_t irq);

void rpi_hal_gic_disableIRQ(const rpi_hal_uint32_t irq);

rpi_hal_uint32_t rpi_hal_gic_getIRQ();

void rpi_hal_gic_ackIRQ(const rpi_hal_uint32_t irq);

#endif
