#include "bcm283x_dwc2_otg.h"

void rpi_hal_dwc2_core_config() {
  dwc2Core.ahbCfg |= dwc2Core_ahbCfg_enableDMA | dwc2Core_ahbCfg_waitAxiWrites;
  dwc2Core.ahbCfg &= ~dwc2Core_ahbCfg_maxAxiBurstMask;
}

void rpi_hal_dwc2_core_disableIntMask() {
  dwc2Core.intMask = 0;
}

void rpi_hal_dwc2_core_setIntMask(const enum rpi_hal_dwc2_core_intStat mask) {
  dwc2Core.intMask = mask;
}

void rpi_hal_dwc2_core_flush(const rpi_hal_uint32_t channel, int tx, int rx) {
  while(!(dwc2Core.resetCtl & dwc2Core_resetCtl_idle));

  if(tx) {
    dwc2Core.resetCtl = dwc2Core_resetCtl_txFlush | (channel << 6);

    while(dwc2Core.resetCtl & dwc2Core_resetCtl_txFlush);
  }

  if(rx) {
    dwc2Core.resetCtl = dwc2Core_resetCtl_rxFlush;

    while(dwc2Core.resetCtl & dwc2Core_resetCtl_rxFlush);
  }
}

void rpi_hal_dwc2_core_reset() {
  while(!(dwc2Core.resetCtl & dwc2Core_resetCtl_idle));

  dwc2Core.resetCtl |= dwc2Core_resetCtl_softReset;

  while(dwc2Core.resetCtl & dwc2Core_resetCtl_softReset);

  while(!(dwc2Core.resetCtl & dwc2Core_resetCtl_idle));
}

rpi_hal_uint32_t rpi_hal_dwc2_core_getHighSpeedPhysicalDeviceType() {
  return (dwc2Core.hardwareCfg[1] >> 6) & 3;
}

rpi_hal_uint32_t rpi_hal_dwc2_core_getFullSpeedPhysicalDeviceType() {
  return (dwc2Core.hardwareCfg[1] >> 8) & 3;
}

void rpi_hal_dwc2_core_init() {
  dwc2Core.ahbCfg &= ~dwc2Core_ahbCfg_enableInt;

  dwc2Core.usbCfg &= ~(dwc2Core_usbCfg_usbLowPinInterfaceVbusDriveExt | dwc2Core_usbCfg_termSelectDataLinePulse);
  dwc2Core.resetCtl = 0;

  rpi_hal_dwc2_core_reset();

  dwc2Core.usbCfg &= ~(dwc2Core_usbCfg_usbInterfaceSelect | dwc2Core_usbCfg_16BitPhysicalInterface);

  if(rpi_hal_dwc2_core_getHighSpeedPhysicalDeviceType() == 2 && rpi_hal_dwc2_core_getFullSpeedPhysicalDeviceType() == 1)
    dwc2Core.usbCfg |= dwc2Core_usbCfg_usbLowPinInterefaceFullSpeed | dwc2Core_usbCfg_usbLowPinInterfaceClockSuspend;
  else
    dwc2Core.usbCfg &= ~(dwc2Core_usbCfg_usbLowPinInterefaceFullSpeed | dwc2Core_usbCfg_usbLowPinInterfaceClockSuspend);
  
  rpi_hal_dwc2_core_config();
  
  dwc2Core.usbCfg &= ~(dwc2Core_usbCfg_secureRemoteParingCapable | dwc2Core_usbCfg_hostNegotiationProtocolCapable);

  dwc2Core.interrupt = 0xFFFFFFFF;
  dwc2Core.intStat = 0xFFFFFFFF;

  dwc2Core.ahbCfg |= dwc2Core_ahbCfg_enableInt;
}
