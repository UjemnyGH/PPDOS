#ifndef _PPDOS_HAL_STM32F4_RCC_
#define _PPDOS_HAL_STM32F4_RCC_

#include "f4_regs.h"

typedef struct {
  f4_hal_io32_t control;
  f4_hal_io32_t pllCfg;
  f4_hal_io32_t clockCfg;
  f4_hal_io32_t clockInt;
  f4_hal_io32_t ahb1Reset;
  f4_hal_io32_t ahb2Reset;
  f4_hal_uint32_t RESERVED0[2];
  f4_hal_io32_t apb1Reset;
  f4_hal_io32_t apb2Reset;
  f4_hal_uint32_t RESERVED1[2];
  f4_hal_io32_t ahb1Enable;
  f4_hal_io32_t ahb2Enable;
  f4_hal_uint32_t RESERVED2[2];
  f4_hal_io32_t apb1Enable;
  f4_hal_io32_t apb2Enable;
  f4_hal_uint32_t RESERVED3[2];
  f4_hal_io32_t ahb1LPEnable;
  f4_hal_io32_t ahb2LPEnable;
  f4_hal_uint32_t RESERVED4[2];
  f4_hal_io32_t apb1LPEnable;
  f4_hal_io32_t apb2LPEnable;
  f4_hal_uint32_t RESERVED5[2];
  f4_hal_io32_t backupDomainCtl;
  f4_hal_io32_t clockCtlStat;
  f4_hal_uint32_t RESERVED6[2];
  f4_hal_io32_t spreadSpectrumCltGen;
  f4_hal_io32_t pllI2SCfg;
  f4_hal_io32_t dedicatedClkCfg;
} __attribute__((packed)) f4_hal_rcc_t;

#define rcc     (*(f4_hal_rcc_t*)F4_HAL_RCC_BASE)

#endif
