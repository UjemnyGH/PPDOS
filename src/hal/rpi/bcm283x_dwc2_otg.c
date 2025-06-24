#include "bcm283x_dwc2_otg.h"

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

void rpi_hal_dwc2_device_write(const rpi_hal_uint32_t channel, const rpi_hal_uint8_t* data, const rpi_hal_uint32_t length) {
  const rpi_hal_uint32_t words = (length + 3) / 4;

  for(rpi_hal_uint32_t i = 0; i < words; i++) {
    rpi_hal_uint32_t value = 0;

    for(rpi_hal_uint32_t j = 0; j < 4; j++) {
      const rpi_hal_uint32_t idx = i * 4 + j;

      if(idx < length)
        value |= ((rpi_hal_uint32_t)data[idx]) << (8 * j);
    }

    dwc2FIFORam(channel)[i] = value;
  }
}

void rpi_hal_dwc2_device_read(const rpi_hal_uint32_t channel, rpi_hal_uint8_t* data, const rpi_hal_uint32_t length) {
  const rpi_hal_uint32_t words = (length + 3) / 4;

  for(rpi_hal_uint32_t i = 0; i < words; i++) {
    const rpi_hal_uint32_t value = dwc2FIFORam(channel)[i];

    for(rpi_hal_uint32_t j = 0; j < 4; j++) {
      const rpi_hal_uint32_t idx = i * 4 + j;

      if(idx < length)
        data[idx] = (value >> (8 * j)) & 0xFF;
    }
  }
}

int rpi_hal_dwc2_host_transfer(const rpi_hal_uint32_t channel, rpi_hal_uint8_t* data, rpi_hal_uint32_t length, const rpi_hal_uint8_t pid) {
  if(length <= 0)
    return -5;

  rpi_hal_dwc2_host_disableChannel(channel);

  dwc2Host.channel[channel].dmaAddr = (rpi_hal_uint32_t)(unsigned long)data;
  dwc2Host.channel[channel].transferSize = (length & 0x7FFFF) | (1 << 19) | (pid << 29);
  rpi_hal_dwc2_host_enableChannel(channel);

  if(!(dwc2Host.channel[channel].character & dwc2Host_channel_character_channelEnable) && (dwc2Host.channel[channel].character & dwc2Host_channel_character_channelDisable))
    return -4;

  int timeout = 1000000;
  while(!(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_transferComplete) && timeout--);

  if(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_NAKReceived)
    return -2;

  if(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_stall)
    return -3;

  if(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_ahbError)
    return -6;

  rpi_hal_dwc2_host_disableChannel(channel);

  if(timeout <= 0)
    return -1;

  return 0;
}

void rpi_hal_dwc2_host_allocChannel(const rpi_hal_uint32_t channel) {
  dwc2Host.channel[channel].character = 0;
  dwc2Host.channel[channel].intMask =
    dwc2Host_channel_interrupt_transferComplete |
    dwc2Host_channel_interrupt_NAKReceived |
    dwc2Host_channel_interrupt_stall |
    dwc2Host_channel_interrupt_ahbError |
    dwc2Host_channel_interrupt_channelHalted;
  dwc2Host.channel[channel].interrupt = 0xFFFFFFFF;
}

void rpi_hal_dwc2_host_setChannelAddress(const rpi_hal_uint32_t channel, const rpi_hal_uint8_t address) {
  dwc2Host.channel[channel].character &= ~dwc2Host_channel_character_deviceAddressMask;
  dwc2Host.channel[channel].character |= (address << dwc2Host_channel_character_deviceAddressShift) & dwc2Host_channel_character_deviceAddressMask;
}

void rpi_hal_dwc2_host_setChannelMaxPacketSize(const rpi_hal_uint32_t channel, rpi_hal_uint16_t maxPacketSize) {
  dwc2Host.channel[channel].character &= ~dwc2Host_channel_character_maxPacketSizeMask;
  dwc2Host.channel[channel].character |= maxPacketSize & dwc2Host_channel_character_maxPacketSizeMask;
}

void rpi_hal_dwc2_host_setChannelEndpointNumber(const rpi_hal_uint32_t channel, const rpi_hal_uint8_t epNum) {
  dwc2Host.channel[channel].character &= ~dwc2Host_channel_character_endpointNumberMask;
  dwc2Host.channel[channel].character |= (epNum << dwc2Host_channel_character_endpointNumberShift) & dwc2Host_channel_character_endpointNumberMask;
}

int rpi_hal_dwc2_host_isNewDeviceConnected() {
  if(dwc2Host.portCtlStat & dwc2Host_portCtlStat_connected) {
    dwc2Host.portCtlStat |= dwc2Host_portCtlStat_connected;

    return 1;
  }

  return 0;
}

int rpi_hal_dwc2_host_isDeviceDisconnected() {
  if(dwc2Host.portCtlStat & dwc2Host_portCtlStat_connected) {
    int portEnabled = (dwc2Host.portCtlStat & dwc2Host_portCtlStat_enabled) != 0;

    dwc2Host.portCtlStat |= dwc2Host_portCtlStat_connected;

    if(portEnabled)
      return 1;
  }

  return 0;
}

int rpi_hal_dwc2_host_isPortEnabled() {
  return (dwc2Host.portCtlStat & dwc2Host_portCtlStat_enabled) != 0;
}

int rpi_hal_dwc2_host_isDevicePresent() {
  return (dwc2Host.portCtlStat & dwc2Host_portCtlStat_connectStatus) != 0;
}

void rpi_hal_dwc2_host_enableChannel(const rpi_hal_uint32_t channel) {
  dwc2Host.channel[channel].interrupt = 0xFFFFFFFF;
  dwc2Host.channel[channel].dmaAddr = 0;
  dwc2Host.channel[channel].transferSize = 0;

  dwc2Host.channel[channel].character &= ~dwc2Host_channel_character_channelDisable;
  dwc2Host.channel[channel].character |= dwc2Host_channel_character_channelEnable;
}

void rpi_hal_dwc2_host_disableChannel(const rpi_hal_uint32_t channel) {
  dwc2Host.channel[channel].interrupt = 0xFFFFFFFF;

  dwc2Host.channel[channel].character |= dwc2Host_channel_character_channelDisable;
  int timeout = 1000000;
  while(dwc2Host.channel[channel].character & dwc2Host_channel_character_channelEnable && timeout);
}

