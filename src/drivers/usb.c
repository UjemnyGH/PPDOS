#include "usb.h"

st7735s_t* gpst;

int _usb_host_transfer(const int channel, uint8_t* data, uint32_t length, const uint8_t pid) {
  //int retVal = rpi_hal_dwc2_host_transfer(channel, data, length, pid);

  int retVal = 0;

  if(length < 0)
    st7735_text18Bit(gpst, "LEN < 0", 0, 0, 2);

  rpi_hal_dwc2_host_disableChannel(channel);

  dwc2Host.channel[channel].dmaAddr = (uint32_t)(unsigned long)(uint32_t*)data;
  dwc2Host.channel[channel].transferSize = (length & 0x7FFFF) | (1 << 19) | (pid << 29);
  rpi_hal_dwc2_host_enableChannel(channel);

  delay_ms(10);

  int timeout = 500;
  while(!(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_transferComplete) && timeout--) {
    uint32_t intr = dwc2Host.channel[channel].interrupt;

    if(intr == 0)
      continue;

    delay_ms(1);
  }

  if(timeout <= 0)
   st7735_text18Bit(gpst, "TOUT", 0, 70, 2); 

  if(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_NAKReceived)
   st7735_text18Bit(gpst, "NAK", 0, 14, 2); 

  if(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_stall)
   st7735_text18Bit(gpst, "STALL", 0, 28, 2); 

  if(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_ahbError)
   st7735_text18Bit(gpst, "\x1b[F00AHBERR", 0, 42, 2); 

  if(dwc2Host.channel[channel].interrupt & dwc2Host_channel_interrupt_ACKReceived)
    st7735_text18Bit(gpst, "\x1b[0F0ACK", 0, 56, 2);    

  rpi_hal_dwc2_host_disableChannel(channel);

  return !retVal;
}

void usb_init() {
  // Initialize core (host specific)
  dwc2Core.ahbCfg |= dwc2Core_ahbCfg_enableInt | dwc2Core_ahbCfg_enableDMA | (1 << 5) /* burst length */;

  delay_ms(10);

  // Reset core
  dwc2Core.usbCfg |= dwc2Core_usbCfg_forceHostMode;
  dwc2Core.usbCfg &= ~dwc2Core_usbCfg_forceDeviceMode;

  // Soft reset
  dwc2Core.resetCtl |= dwc2Core_resetCtl_softReset;
  while(dwc2Core.resetCtl & dwc2Core_resetCtl_softReset);

  delay_ms(10);
  
  // Flush tx and rx
  rpi_hal_dwc2_core_flush(0, 1, 1);

  // Disable power and clock gating
  dwc2Power.ctlLegacy = 0;

  // Select ulpi or phy
  if(dwc2Core.usbCfg & dwc2Core_usbCfg_16BitPhysicalInterface)
    dwc2Core.usbCfg &= ~dwc2Core_usbCfg_16BitPhysicalInterface;
  else
    dwc2Core.usbCfg |= dwc2Core_usbCfg_16BitPhysicalInterface;

  // Force host
  dwc2Core.usbCfg |= dwc2Core_usbCfg_forceHostMode;

  // Set host as 6MHz base
  dwc2Host.config &= ~dwc2Host_config_clockMask;

  // Select clock speed
  if(dwc2Core.usbCfg & dwc2Core_usbCfg_16BitPhysicalInterface)
    dwc2Host.config |= dwc2Host_config_clock48MHz;
  else 
    dwc2Host.config |= dwc2Host_config_clock30_60MHz;

  // Select appropriate intterupt masks for host mode
  dwc2Core.intMask |= 
    dwc2Core_intStat_hostChannelInt | 
    dwc2Core_intStat_portInt | 
    dwc2Core_intStat_startOfFrame | 
    dwc2Core_intStat_usbResetDetected | 
    dwc2Core_intStat_enumerationComplete |
    dwc2Core_intStat_usbDeviceDisconnected;

  // Enable interrupts
  dwc2Core.ahbCfg |= dwc2Core_ahbCfg_enableInt | dwc2Core_ahbCfg_enableDMA;

  // Host initialization
  dwc2Host.portCtlStat |= (dwc2Host_portCtlStat_connected | dwc2Host_portCtlStat_enableChanged | dwc2Host_portCtlStat_overcurrentChange);

  dwc2Host.portCtlStat |= dwc2Host_portCtlStat_power;
  delay_ms(200);

  usb_host_reset();

  // Make control channel 0 as endpoint0
  usb_host_rebuildControlChannel0();
}

/**
 * Some helper functions waiting to introduce more hal libraries for other CPUs
 */

void usb_host_reset() {
  dwc2Host.portCtlStat |= (dwc2Host_portCtlStat_connected | dwc2Host_portCtlStat_enableChanged | dwc2Host_portCtlStat_overcurrentChange);

  dwc2Host.portCtlStat |= dwc2Host_portCtlStat_power;

  delay_ms(50);

  int timeout = 10000;
  while(!(dwc2Host.portCtlStat & dwc2Host_portCtlStat_power) && timeout--)
    delay_ms(1);

  delay_ms(10);

  dwc2Host.portCtlStat |= dwc2Host_portCtlStat_reset;

  delay_ms(50);

  dwc2Host.portCtlStat &= ~dwc2Host_portCtlStat_reset;
  
  delay_ms(20); 
}

int usb_host_waitForDeviceConnection(int timeout) {
  while(timeout--) {
    if(usb_host_isNewDeviceConnected() || usb_host_isDevicePresent())
      return 1;
    delay_ms(1);
  }

  return 0;
}

void usb_host_rebuildControlChannel0() {
  uint32_t portStatus = dwc2Host.portCtlStat;

  rpi_hal_dwc2_host_allocChannel(0);
  rpi_hal_dwc2_host_setChannelAddress(0, 0);
  rpi_hal_dwc2_host_setChannelMaxPacketSize(0, 8);
  rpi_hal_dwc2_host_setChannelEndpointNumber(0, 0);

  if(portStatus & dwc2Host_portCtlStat_lowSpeedDevice)
    dwc2Host.channel[0].character |= dwc2Host_channel_character_lowSpeedDevice;

  dwc2Host.channel[0].transferSize = 0;
  dwc2Host.channel[0].character |= dwc2Host_channel_character_endpointTypeControl;

  dwc2Host.channel[0].character &= ~dwc2Host_channel_character_endpointDirectionIn;
  dwc2Host.channel[0].character |= 8;
  dwc2Host.channel[0].dmaAddr = 0;

  delay_ms(50);
}

void usb_host_initChannel(const int channel, const uint8_t address, const uint16_t maxPacketSize, const int isDirectionIn, const int type, const uint8_t endpointNumber) {
  rpi_hal_dwc2_host_allocChannel(channel);
  rpi_hal_dwc2_host_setChannelAddress(channel, address);
  rpi_hal_dwc2_host_setChannelMaxPacketSize(channel, maxPacketSize);
  rpi_hal_dwc2_host_setChannelEndpointNumber(channel, endpointNumber);

  if(isDirectionIn)
    dwc2Host.channel[channel].character |= dwc2Host_channel_character_endpointDirectionIn;
  else
    dwc2Host.channel[channel].character &= ~dwc2Host_channel_character_endpointDirectionIn;

  dwc2Host.channel[channel].character |= type;
}

int usb_host_isNewDeviceConnected() {
  return rpi_hal_dwc2_host_isNewDeviceConnected();
}

int usb_host_isDeviceDisconnected() {
  return rpi_hal_dwc2_host_isDeviceDisconnected();
}

int usb_host_isPortEnabled() {
  return rpi_hal_dwc2_host_isPortEnabled();
}

int usb_host_isDevicePresent() {
  return rpi_hal_dwc2_host_isDevicePresent();
}

int usb_host_allocateChannel(usb_base_t* const pUsbBase) {
  if(!pUsbBase)
    return -1;

  for(uint8_t i = 1; i < USB_MAX_CHANNELS_IN_USE; i++) {
    if(pUsbBase->channelAllocationState[i]) {
      pUsbBase->channelAllocationState[i] = 1;
      pUsbBase->device[i] = (usb_device_t){};

      return i;
    }
  }

  return -1;
}

void usb_host_freeChannel(usb_base_t* const pUsbBase, const int channel) {
  if(!pUsbBase)
    return;

  if(channel > 0 && channel < USB_MAX_CHANNELS_IN_USE) {
    pUsbBase->channelAllocationState[channel] = 0;
    pUsbBase->device[channel] = (usb_device_t){};
  }
}

int usb_host_connect(st7735s_t* const pSt, usb_base_t* const pUsbBase, const uint8_t address) {
  gpst = pSt;

  st7735_text18Bit(pSt, "\x1b[0F0Start", 0, 0, 1);

  if(!pUsbBase || address > 128 || address < 1)
    return -2;

  st7735_text18Bit(pSt, "Addr and base exist", 0, 8, 1);

  static usb_device_t result = {};
  result.address = address;
  result.endpointIn = 0xFF;
  result.endpointOut = 0xFF;

  static usb_control_packet_t getDescriptor = {
    usb_requestType_in,
    usb_request_getDescriptor,
    (usb_value_descriptorType_device << 8) | 0x00,
    0x0000,
    sizeof(usb_device_descriptor_t)
  };

  static usb_device_descriptor_t descriptor = {};

  if(usb_host_controlTransfer(getDescriptor, (uint8_t*)0, (uint8_t*)&descriptor) != 1)
    return -1;

  st7735_text18Bit(pSt, "Got descriptor", 0, 16, 1);

  result.maxPacketSize = descriptor.maxPacketSize;

  static usb_control_packet_t getConfig = {
    usb_requestType_in,
    usb_request_getDescriptor,
    (usb_value_descriptorType_config << 8) | 0x00,
    0x0000,
    sizeof(usb_config_descriptor_t)
  };

  static usb_config_descriptor_t config = {};

  if(usb_host_controlTransfer(getConfig, (uint8_t*)0, (uint8_t*)&config) != 1)
    return -1;

  st7735_text18Bit(pSt, "Got config", 0, 24, 1);

  static usb_control_packet_t getFullConfig = {
    usb_requestType_in,
    usb_request_getDescriptor,
    (usb_value_descriptorType_config << 8) | 0x00,
    0x0000
  };

  getFullConfig.length = config.totalLength;
  
  if(usb_host_controlTransfer(getFullConfig, (uint8_t*)0, result.descriptorData) != 1)
    return -1;

  st7735_text18Bit(pSt, "Got full config", 0, 32, 1);

  uint32_t offset = 0;

  while(offset < config.totalLength) {
    uint8_t len = result.descriptorData[offset];
    uint8_t type = result.descriptorData[offset];

    switch(type) {
      case usb_value_descriptorType_interface: {
        usb_interface_descriptor_t* interface = (usb_interface_descriptor_t*)&result.descriptorData[offset];
        
        result.interfaceClass = interface->interfaceClass;
        result.interfaceProtocol = interface->interfaceProtocol;
      
        break;
      }
      case usb_value_descriptorType_endpoint: {
        usb_endpoint_descriptor_t* endpoint = (usb_endpoint_descriptor_t*)&result.descriptorData[offset];

        if((endpoint->endpointAddress & usb_requestType_in) == 0) {
          result.endpointOut = endpoint->endpointAddress & 0xF;
          result.endpointTypeOut = (endpoint->attributes & 0x3) << dwc2Host_channel_character_endpointTypeShift;
        }
        else {
          result.endpointIn = endpoint->endpointAddress & 0xF;
          result.endpointTypeIn = (endpoint->attributes & 0x3) << dwc2Host_channel_character_endpointTypeShift;
        }

        break;
      }
    }

    offset += len;
  }

  static usb_control_packet_t setAddress = {
    usb_requestType_out,
    usb_request_setAddress,
    0,
    0x0000,
    0
  };

  setAddress.value = result.address & 0x7F;

  if(usb_host_controlTransfer(setAddress, (uint8_t*)0, (uint8_t*)0) != 1)
    return -1;

  st7735_text18Bit(pSt, "Set address", 0, 40, 1);

  int channel = 0;

  if(result.endpointOut != 0xFF) {
    result.channelTx = usb_host_allocateChannel(pUsbBase);

    channel = result.channelTx;

    if(result.channelTx == -1)
      return -1;

    usb_host_initChannel(result.channelTx, result.address, result.maxPacketSize, 0, result.endpointTypeOut, result.endpointOut);

    pUsbBase->device[result.channelTx] = result;

    st7735_text18Bit(pSt, "Allocated TX", 0, 48, 1);
  }

  if(result.endpointIn != 0xFF) {
    result.channelRx = usb_host_allocateChannel(pUsbBase);

    channel = result.channelRx;

    if(result.channelRx == -1)
      return -1;
    
    usb_host_initChannel(result.channelRx, result.address, result.maxPacketSize, 1, result.endpointTypeIn, result.endpointIn);

    pUsbBase->device[result.channelRx] = result;

    st7735_text18Bit(pSt, "Allocated RX", 0, 56, 1);
  }

  return channel;
}

void usb_host_disconnect(usb_base_t* const pUsbBase, usb_device_t* const pDevice) {
  if(!pUsbBase || !pDevice)
    return;

  if(pDevice->channelRx > 0) {
    rpi_hal_dwc2_host_disableChannel(pDevice->channelRx);
    dwc2Host.channel[pDevice->channelRx].character |= dwc2Host_channel_character_channelDisable;

    rpi_hal_dwc2_host_allocChannel(pDevice->channelRx);
  
    usb_host_freeChannel(pUsbBase, pDevice->channelRx);
  }

  if(pDevice->channelTx > 0) {
    rpi_hal_dwc2_host_disableChannel(pDevice->channelTx);
    dwc2Host.channel[pDevice->channelTx].character |= dwc2Host_channel_character_channelDisable;

    rpi_hal_dwc2_host_allocChannel(pDevice->channelTx);
  
    usb_host_freeChannel(pUsbBase, pDevice->channelTx);
  }
}

int usb_host_controlTransfer(usb_control_packet_t control, const uint8_t* tx, uint8_t* rx) {
  usb_control_packet_t tmpCtl = control;

  dwc2Host.channel[0].character &= ~dwc2Host_channel_character_endpointDirectionIn;

  st7735_text18Bit(gpst, "Bef att", 80, 16, 1);

  dwc2Host.channel[0].character &= ~dwc2Host_channel_character_endpointTypeMask;
  dwc2Host.channel[0].character |= dwc2Host_channel_character_endpointTypeControl;

  if(!_usb_host_transfer(0, (uint8_t*)&tmpCtl, sizeof(usb_control_packet_t), 3))
    return -1;

  st7735_text18Bit(gpst, "Aft att", 80, 24, 1);

  if(tx && control.length > 0 && (control.requestType & usb_requestType_in) == 0) {
    dwc2Host.channel[0].character &= ~dwc2Host_channel_character_endpointDirectionIn;

    if(!_usb_host_transfer(0, (uint8_t*)tx, control.length, 0))
      return -2;
  }
  else if(rx) {
    dwc2Host.channel[0].character |= dwc2Host_channel_character_endpointDirectionIn;

    if(!_usb_host_transfer(0, rx, control.length, 1))
      return -3;
  }

  if((control.requestType & usb_requestType_in) == 0) {
    dwc2Host.channel[0].character |= dwc2Host_channel_character_endpointDirectionIn;

    if(!_usb_host_transfer(0, (uint8_t*)0, 0, 2))
      return -4;
  }
  else {
    dwc2Host.channel[0].character &= ~dwc2Host_channel_character_endpointDirectionIn;

    if(!_usb_host_transfer(0, (uint8_t*)0, 0, 2))
      return -5;
  }
  
  return 1;
}

int usb_host_receive(usb_device_t* const pDevice, uint8_t* data, const uint32_t length) {
  if(!pDevice)
    return -1;

  // 1 as PID = DATA1 - IN
  if(pDevice->channelRx >= 0)
    return _usb_host_transfer(pDevice->channelRx, data, length, 1);
  
  return -2;
}

int usb_host_send(usb_device_t* const pDevice, const uint8_t* data, const uint32_t length) {
  if(!pDevice)
    return -1;

  // 0 as PID = DATA0 - OUT
  if(pDevice->channelTx >= 0)
    return _usb_host_transfer(pDevice->channelTx, (uint8_t*)data, length, 0);
  
  return -2;
}
