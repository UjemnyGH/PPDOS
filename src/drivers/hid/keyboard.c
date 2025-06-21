#include "keyboard.h"

keyboard_info_t keyboard_findEndpoint(const uint8_t* desc, uint64_t totalLength) {
  keyboard_info_t info = { 0 };
  info.found = 0;

  const uint8_t* ptr = desc;
  const uint8_t* end = desc + totalLength;
  int foundInterface = 0;

  while(ptr + 2 <= end) {
    uint8_t len = ptr[0];
    uint8_t type = ptr[1];

    if(ptr + len > end || len < 2)
      break;

    if(type == usb_value_descriptorType_interface) {
      usb_interface_descriptor_t* interfaceDescPtr = (usb_interface_descriptor_t*)ptr;

      /* HID && Boot && Keyboard */
      if(interfaceDescPtr->interfaceClass == 0x03 && interfaceDescPtr->interfaceSubclass == 0x01 && interfaceDescPtr->interfaceProtocol == 0x01) {
        info.interfaceNumber = interfaceDescPtr->interfaceNumber;
        foundInterface = 1;
      }
      else 
        foundInterface = 0;
    }
    else if(type == usb_value_descriptorType_endpoint && foundInterface) {
      usb_endpoint_descriptor_t* endpointDescPtr = (usb_endpoint_descriptor_t*)ptr;
      
      /* In && Interrupt */
      if((endpointDescPtr->endpointAddress & usb_requestType_in) && (endpointDescPtr->attributes & 0x03) == 0x03) {
        info.endpointAddress = endpointDescPtr->endpointAddress;
        info.maxPackedSize = endpointDescPtr->maxPacketSize;
        info.found = 1;

        break;
      }
    }

    ptr += len;
  }

  return info;
}

void keyboard_config(const int channel, const uint8_t address) {

}
