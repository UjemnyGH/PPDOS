#ifndef _PPDOS_HAL_BCM283X_HDMI_
#define _PPDOS_HAL_BCM283X_HDMI_

#include "bcm283x_regs.h"

typedef struct rpi_hal_hdmi_s {
  rpi_hal_io32_t coreRev;
  rpi_hal_io32_t softwareReset;
  rpi_hal_io32_t hotplug;
  rpi_hal_io32_t fifoCtl;
  rpi_hal_io32_t scheduler;
  rpi_hal_io32_t clockCtl;
  rpi_hal_io32_t videoCtl;
  rpi_hal_io32_t videoStat;
  rpi_hal_io32_t hTimingA;
  rpi_hal_io32_t hTimingB;
  rpi_hal_io32_t vTimingA0;
  rpi_hal_io32_t vTimingB0;
  rpi_hal_io32_t vTimingA1;
  rpi_hal_io32_t vTimingB1;
  rpi_hal_io32_t videoSource;
  rpi_hal_io32_t videoBlackLevel;
  rpi_hal_io32_t frameCounter;
  rpi_hal_io32_t intMask;
  rpi_hal_io32_t intStat;
  rpi_hal_io32_t coreCfg;
  rpi_hal_io32_t ramPacketCfg;
  rpi_hal_io32_t ramPacketData;
  rpi_hal_io32_t physicalCtl;
  rpi_hal_io32_t physicalStat;
  rpi_hal_io32_t audioCtl;
  rpi_hal_io32_t audioFreq;
  rpi_hal_io32_t audioLayout;

} __attribute__((packed)) rpi_hal_hdmi_t;

#endif
