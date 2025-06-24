#include "../hal/rpi/bcm283x.h"
#include "../common/pp_memory.h"
#include "../common/shared_fn.h"
#include "../drivers/st7735s.h"
#include "../drivers/hd44780.h"
#include "../drivers/pcd8544.h"
#include "../drivers/usb.h"

typedef struct {
  uint8_t mod;
  uint8_t reserved;
  uint8_t keycodes[6];
} __attribute__((packed)) usb_keyboard_report_t;

char keycodeToAscii(uint8_t key, uint8_t mod) {
  // Nothing pressed
  if(key == 0x0)
    return 0;

  if(mod == 0x2 || mod == 0x20) {
    if(key >= 0x4 && key <= 0x1D)
      return 'A' + (key - 0x4);
  }
  else {
    if(key >= 0x4 && key <= 0x1D)
      return 'a' + (key - 0x4);

    if(key >= 0x1E && key <= 0x26)
      return '1' + (key - 0x1E);

    if(key == 0x27)
      return '0';
  }

  if(key == 0x28)
    return '\n';

  if(key == 0x2A)
    return '\b';

  if(key == 0x2B)
    return '\t';

  if(key == 0x2C)
    return ' ';

  return 0;
}

usb_base_t usb;

void kernel_main() {
  //rpi_hal_sd_hci_initialize(); 
  usb_init();

  st7735s_t st;
  st7735_init(&st, 20, 16, 21, ST7735_USE_SPI_DEFAULT_CS1);

  st7735_clearFrame(&st);
  st7735_drawBuffered(&st);

  st7735_switchInterfacePixelFormat(&st, st_interPixelFormat_18bit); 

  int screenTextIndex = 0;
  char screenText[0x1000];

  st7735_text18Bit(&st, "\x1b[00FWaiting for connection", 0, 120, 1);
  usb_host_waitForDeviceConnection(-1);
  delay_ms(100);

  st7735_text18Bit(&st, "Device found", 0, 112, 1);

  usb_host_reset();

  st7735_text18Bit(&st, "Port reset", 0, 104, 1);

  while(!usb_host_isDevicePresent())
    delay_ms(1);

  st7735_text18Bit(&st, "Device still present", 0, 96, 1);

  while(!usb_host_isPortEnabled())
    delay_ms(1);

  st7735_text18Bit(&st, "Port enabled", 0, 88, 1);

  usb_host_rebuildControlChannel0();

  st7735_text18Bit(&st, "Channel0 rebuilt", 0, 80, 1); 

  int keyboardChannel = usb_host_connect(&st, &usb, 0x1);

  st7735_text18Bit(&st, "Connected", 0, 64, 1);
  usb_keyboard_report_t kb;

  while(1) {
    st7735_switchInterfacePixelFormat(&st, st_interPixelFormat_18bit);

    usb_host_receive(&usb.device[keyboardChannel], (uint8_t*)&kb, sizeof(usb_keyboard_report_t));     
 
    st7735_switchInterfacePixelFormat(&st, st_interPixelFormat_16bit); 

    for(int i = 0; i < 6; i++) {
      if(kb.keycodes[i] == 0)
        break;

      screenText[screenTextIndex++] = keycodeToAscii(kb.keycodes[i], kb.mod);
    }

    st7735_text(&st, screenText, 0, 0, 1);

    st7735_drawBuffered(&st);

    st7735_clearFrame(&st);
  }
}
