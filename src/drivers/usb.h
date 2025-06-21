#ifndef _PPDOS_DRIVER_USB_
#define _PPDOS_DRIVER_USB_

#include "../common/shared_fn.h"
#include "../hal/rpi/bcm283x_dwc2_otg.h"

typedef struct {
  uint8_t requestType;
  uint8_t request;
  uint16_t value;
  uint16_t index;
  uint16_t length;
} usb_control_request_t;

typedef struct {
  uint8_t length;
  uint8_t descriptorType;
} usb_descriptor_header_t;

typedef struct {
  uint8_t length;
  uint8_t descriptorType;
  uint8_t interfaceNumber;
  uint8_t alternateSettings;
  uint8_t numberOfEndpoints;
  uint8_t interfaceClass;
  uint8_t interfaceSubclass;
  uint8_t interfaceProtocol;
  uint8_t interface;
} usb_interface_descriptor_t;

typedef struct {
  uint8_t length;
  uint8_t descriptorType;
  uint8_t endpointAddress;
  uint8_t attributes;
  uint16_t maxPacketSize;
  uint8_t interval;
} usb_endpoint_descriptor_t;

enum usb_requestType {
  usb_requestType_out       = 0x00,
  usb_requestType_in        = 0x80,

  usb_requestType_standard  = 0x00,
  usb_requestType_class     = 0x20,
  usb_requestType_vendor    = 0x40,

  usb_requestType_device    = 0x00,
  usb_requestType_interface = 0x01,
  usb_requestType_endpoint  = 0x02,
  usb_requestType_other     = 0x03
};

enum usb_request {
  usb_request_getStatus     = 0x00,
  usb_request_clearFeature  = 0x01,
  usb_request_setFeature    = 0x03,
  usb_request_setAddress    = 0x05,
  usb_request_getDescriptor = 0x06,
  usb_request_setDescriptor = 0x07,
  usb_request_getConfig     = 0x08,
  usb_request_setConfig     = 0x09,
  usb_request_getInterface  = 0x0A,
  usb_request_setInterface  = 0x0B,
  usb_request_syncFrame     = 0x0C
};

enum usb_value_descriptorType {
  usb_value_descriptorType_device           = 0x01,
  usb_value_descriptorType_config           = 0x02,
  usb_value_descriptorType_string           = 0x03,
  usb_value_descriptorType_interface        = 0x04,
  usb_value_descriptorType_endpoint         = 0x05,
  usb_value_descriptorType_deviceQualifier  = 0x06,
  usb_value_descriptorType_otherSpeedConfig = 0x07,
  usb_value_descriptorType_interfacePower   = 0x08,
  usb_value_descriptorType_hid              = 0x21,
  usb_value_descriptorType_report           = 0x22,
  usb_value_descriptorType_physical         = 0x23
};

void usb_init();

void usb_controlTransfer(const int channel, const rpi_hal_uint8_t addr, usb_control_request_t* const setup, void* data, const int length);

void usb_allocChannel(const int channel);

void usb_resetPort();

void usb_setChannelAddress(const int channel, const rpi_hal_uint8_t address);

void usb_setChannelMaxPacketSize(const int channel, rpi_hal_uint16_t maxPacketSize);

#endif
