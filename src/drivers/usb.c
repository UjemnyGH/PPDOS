#include "usb.h"

void usb_init() {
  rpi_hal_dwc2_core_init();

  dwc2Power.ctlLegacy = 0;

  dwc2Host.config &= ~dwc2Host_config_clockMask;

  if(rpi_hal_dwc2_core_getHighSpeedPhysicalDeviceType() == 2 && rpi_hal_dwc2_core_getFullSpeedPhysicalDeviceType() == 1 && dwc2Core.usbCfg & dwc2Core_usbCfg_usbLowPinInterefaceFullSpeed)
    dwc2Host.config |= dwc2Host_config_clock48MHz;
  else 
    dwc2Host.config |= dwc2Host_config_clock30_60MHz;

  rpi_hal_dwc2_core_flush(0x10, 1, 1);

  dwc2Host.portCtlStat &= ~(dwc2Host_portCtlStat_connectChanged | dwc2Host_portCtlStat_enable | dwc2Host_portCtlStat_enableChanged | dwc2Host_portCtlStat_overcurrentChanged);

  if(!(dwc2Host.portCtlStat & dwc2Host_portCtlStat_power))
    dwc2Host.portCtlStat |= dwc2Host_portCtlStat_power;

  usb_resetPort();

  rpi_hal_dwc2_core_disableIntMask();

  dwc2Core.interrupt = 0xFFFFFFFF;
  dwc2Core.intStat = 0xFFFFFFFF;

  rpi_hal_dwc2_core_setIntMask(dwc2Core_intStat_startOfFrame | dwc2Core_intStat_hostChannelInt | dwc2Core_intStat_portInt | dwc2Core_intStat_usbDeviceDisconnected);
}

void usb_controlTransfer(const int channel, const rpi_hal_uint8_t addr, usb_control_request_t* const setup, void* data, const int length) {
  usb_allocChannel(channel);
  usb_setChannelAddress(channel, addr);
  usb_setChannelMaxPacketSize(channel, 8);

  dwc2Host.channel[channel].character |= dwc2Host_channel_character_channelEnable;
  dwc2Host.channel[channel].transferSize = sizeof(usb_control_request_t);
  dwc2Host.channel[channel].dmaAddr = (rpi_hal_uint32_t)setup;

  while(!(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_transferComplete));

  dwc2Host.channel[channel].interrupt = 0xFFFFFFFF;

  if(length > 0) {
    dwc2Host.channel[channel].character &= ~dwc2Host_channel_character_endpointDirectionIn;

    if(setup->requestType & 0x80)
      dwc2Host.channel[channel].character |= dwc2Host_channel_character_endpointDirectionIn;

    dwc2Host.channel[channel].transferSize = length;
    dwc2Host.channel[channel].dmaAddr = (rpi_hal_uint32_t)(unsigned long)data;
    dwc2Host.channel[channel].character |= dwc2Host_channel_character_channelEnable;

    while(!(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_transferComplete));

    dwc2Host.channel[channel].interrupt = 0xFFFFFFFF;
  }

  dwc2Host.channel[channel].character &= ~dwc2Host_channel_character_channelEnable;

  if(setup->requestType & 0x80)
    dwc2Host.channel[channel].character |= dwc2Host_channel_character_channelEnable;

  dwc2Host.channel[channel].transferSize = 0;
  dwc2Host.channel[channel].dmaAddr = 0;
  dwc2Host.channel[channel].character |= dwc2Host_channel_character_channelEnable;

  while(!(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_transferComplete));

  dwc2Host.channel[channel].interrupt = 0xFFFFFFFF;
}

void usb_allocChannel(const int channel) {
  dwc2Host.channel[channel].character = 0;
  dwc2Host.channel[channel].intMask = 0;
  dwc2Host.channel[channel].interrupt = 0xFFFFFFFF;
}

void usb_resetPort() {
  dwc2Host.portCtlStat |= dwc2Host_portCtlStat_reset;
  
  for(rpi_hal_uint32_t i = 0; i < 1000000; i++);

  dwc2Host.portCtlStat &= ~dwc2Host_portCtlStat_reset;

  for(rpi_hal_uint32_t i = 0; i < 1000000; i++);
}

void usb_setChannelAddress(const int channel, const rpi_hal_uint8_t address) {
  dwc2Host.channel[channel].character &= ~dwc2Host_channel_character_deviceAddressMask;
  dwc2Host.channel[channel].character |= (address << dwc2Host_channel_character_deviceAddressShift) & dwc2Host_channel_character_deviceAddressMask;
}

void usb_setChannelMaxPacketSize(const int channel, rpi_hal_uint16_t maxPacketSize) {
  dwc2Host.channel[channel].character &= ~dwc2Host_channel_character_maxPacketSizeMask;
  dwc2Host.channel[channel].character |= maxPacketSize & dwc2Host_channel_character_maxPacketSizeMask;
}

