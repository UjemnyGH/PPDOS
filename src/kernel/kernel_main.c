#include "../hal/rpi/bcm283x.h"
#include "../common/pp_memory.h"
#include "../common/shared_fn.h"
#include "../drivers/st7735s.h"
#include "../drivers/hd44780.h"
#include "../drivers/pcd8544.h"
#include "../drivers/usb.h"
#include "terminal.h"

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
st7735s_t st;

void tty_stSetPixel(uint32_t x, uint32_t y) {
  st7735_setPixel(&st, x, y, ST7735_COLOR_16(0x1F, 0x3F, 0x1F));
}

void tty_stDraw() {
  st7735_drawBuffered(&st);
  st7735_clearFrame(&st);
}

void kernel_main() {
  //rpi_hal_sd_hci_initialize(); 
  st7735_init(&st, 20, 16, 21, ST7735_USE_SPI_DEFAULT_CS1);

  st7735_clearFrame(&st);
  st7735_drawBuffered(&st);

  term_globalInit(tty_stSetPixel, tty_stDraw, ST7735_WIDTH, ST7735_HEIGHT); 

  puts("Initializing USB\n");

  usb_init(); 

  term_globalClear();
  puts("USB: OK\n");

  int screenTextIndex = 0;
  char screenText[0x1000];

  puts("Waiting for connection\n");
  usb_host_waitForDeviceConnection(-1);
  delay_ms(100);

  puts("Device found\n");

  usb_host_reset();

  puts("Port reset\n");

  while(!usb_host_isDevicePresent())
    delay_ms(1);

  puts("Device still present\n");

  usb_host_rebuildControlChannel0();

  puts("Channel0/Endpoint0 rebuilt\n"); 

  int keyboardChannel = usb_host_connect( &usb, 0x1);

  puts("USB device connected\n");
  usb_keyboard_report_t kb;

  while(1) {
    usb_host_receive(&usb.device[keyboardChannel], (uint8_t*)&kb, sizeof(usb_keyboard_report_t));     
 
    for(int i = 0; i < 6; i++) {
      if(kb.keycodes[i] == 0)
        break;

      screenText[screenTextIndex++] = keycodeToAscii(kb.keycodes[i], kb.mod);
    }

    puts(screenText);

    //asm volatile("wfi");
  }
}
