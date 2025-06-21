#ifndef _PPDOS_DRIVER_HID_KEYBOARD_
#define _PPDOS_DRIVER_HID_KEYBOARD_

#include "../usb.h"
#include "../../common/shared_fn.h"

typedef struct {
  uint8_t interfaceNumber;
  uint8_t endpointAddress;
  uint16_t maxPackedSize;
  uint8_t found;
} keyboard_info_t;

keyboard_info_t keyboard_findEndpoint(const uint8_t* desc, uint64_t totalLength);

void keyboard_config(const int channel, const uint8_t address);

#endif
