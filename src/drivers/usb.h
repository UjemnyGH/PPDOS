#ifndef _PPDOS_DRIVER_USB_
#define _PPDOS_DRIVER_USB_

#include "../common/shared_fn.h"
#include "../hal/rpi/bcm283x_dwc2_otg.h"

#include "st7735s.h"

#define USB_DIR_IN            1
#define USB_DIR_OUT           2
#define USB_TYPE_CONTROL      dwc2Host_channel_character_endpointTypeControl
#define USB_TYPE_ISOCHRONOUS  dwc2Host_channel_character_endpointTypeIsochronous
#define USB_TYPE_BULK         dwc2Host_channel_character_endpointTypeBulk
#define USB_TYPE_INTERRUPT    dwc2Host_channel_character_endpointTypeInterrupt

#define USB_DESCRIPTOR_MAX_SIZE 512

#define USB_MAX_CHANNELS_IN_USE 16

typedef struct {
  uint8_t address;
  uint8_t endpointIn;
  uint8_t endpointOut;
  int channelRx;
  int channelTx;
  uint32_t endpointTypeIn;
  uint32_t endpointTypeOut;
  uint16_t maxPacketSize;
  uint8_t interfaceClass;
  uint8_t interfaceProtocol;
  uint8_t descriptorData[USB_DESCRIPTOR_MAX_SIZE];
} usb_device_t;

typedef struct {
  uint8_t channelAllocationState[USB_MAX_CHANNELS_IN_USE];
  usb_device_t device[USB_MAX_CHANNELS_IN_USE];
} usb_base_t;

typedef struct {
  uint8_t requestType;
  uint8_t request;
  uint16_t value;
  uint16_t index;
  uint16_t length;
} __attribute__((packed)) usb_control_packet_t;

typedef struct {
  uint8_t length;
  uint8_t descriptorType;
  uint16_t usbSpec;
  uint8_t deviceClass;
  uint8_t deviceSubclass;
  uint8_t deviceProtocol;
  uint8_t maxPacketSize;
  uint16_t vendorId;
  uint16_t productId;
  uint16_t deviceReleaseNum;
  uint8_t manufacturerIndex;
  uint8_t productIndex;
  uint8_t serialNumberIndex;
  uint8_t numberOfConfigs;
} __attribute__((packed)) usb_device_descriptor_t;

typedef struct {
  uint8_t length;
  uint8_t descriptorType;
  uint16_t totalLength;
  uint8_t numberOfInterfaces;
  uint8_t configValue;
  uint8_t configIndex;
  uint8_t attributes;
  uint8_t maxPower;
} __attribute__((packed)) usb_config_descriptor_t;

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
} __attribute__((packed)) usb_interface_descriptor_t;

typedef struct {
  uint8_t length;
  uint8_t descriptorType;
  uint8_t endpointAddress;
  uint8_t attributes;
  uint16_t maxPacketSize;
  uint8_t interval;
} __attribute__((packed)) usb_endpoint_descriptor_t;

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

void usb_host_reset();

int usb_host_waitForDeviceConnection(int timeout);

void usb_host_rebuildControlChannel0();

void usb_host_initChannel(const int channel, const uint8_t address, const uint16_t maxPacketSize, const int isDirectionIn, const int type, const uint8_t endpointNumber);

int usb_host_isNewDeviceConnected();

int usb_host_isDeviceDisconnected();

int usb_host_isPortEnabled();

int usb_host_isDevicePresent();

int usb_host_allocateChannel(usb_base_t* const pUsbBase);

void usb_host_freeChannel(usb_base_t* const pUsbBase, const int channel);

int usb_host_connect(st7735s_t* const pSt, usb_base_t* const pUsbBase, const uint8_t address);

void usb_host_disconnect(usb_base_t* const pUsbBase, usb_device_t* const pDevice);

int usb_host_pollDevices(const uint8_t address, const uint16_t maxPacketSize);

int usb_host_controlTransfer(usb_control_packet_t control, const uint8_t* tx, uint8_t* rx);

int usb_host_receive(usb_device_t* const pDevice, uint8_t* data, const uint32_t length);

int usb_host_send(usb_device_t* const pDevice, const uint8_t* data, const uint32_t length);

#endif
