#include "../hal/rpi/bcm283x.h"
#include "../common/pp_memory.h"
#include "../common/shared_fn.h"
#include "../drivers/st7735s.h"
#include "../drivers/hd44780.h"
#include "../drivers/pcd8544.h"

void kernel_main() {
  //rpi_hal_sd_hci_initialize(); 

  st7735s_t st;
  st7735_init(&st, 20, 16, 21, ST7735_USE_SPI_DEFAULT_CS1);

  int draw18Bit = 0;

  char* colorPreset[] = {
    "F00",
    "0F0",
    "00F",
    "0FF",
    "F0F",
    "FF0",
    "FFF",
  };

  char* dvdLogo = "\e[FFFDVD";

  int x = 1, y = 1;
  uint8_t posX = 1, posY = 1;
  uint8_t colorIter = 0;

  while(1) {
    if(draw18Bit) {
      st7735_switchInterfacePixelFormat(&st, st_interPixelFormat_18bit);

      for(uint8_t x = 0; x < ST7735_WIDTH; x++) {
        for(uint8_t y = 0; y < ST7735_HEIGHT; y++) {
          st7735_draw18BitPixel(&st, x, y, ST7735_COLOR_18(x % 0x40, 0, y % 0x40));
        }
      }
    }
    else {
      st7735_switchInterfacePixelFormat(&st, st_interPixelFormat_16bit);

      st7735_clearFrame(&st); // Ensures framebuffer is 0

      /*for(uint8_t x = 0; x < 0x1F; x++) {
        for(uint8_t y = 0; y < 0x1F; y++) {   
          st7735_setPixel(&st, x + 10, y + 10, ST7735_COLOR_16(x, 0x3F, y));
        }
      }*/

      posX += x;
      posY += y;

      if(posX == ST7735_WIDTH - 36) {
        x = -1;

        memcpy(dvdLogo + 2, colorPreset[colorIter], 3);

        colorIter++;

        if(colorIter >= (sizeof(colorPreset) / sizeof(colorPreset[0]))) colorIter = 0;
      }

      if(posY == ST7735_HEIGHT - 14) {
        y = -1;
     
        memcpy(dvdLogo + 2, colorPreset[colorIter], 3);

        colorIter++;

        if(colorIter >= (sizeof(colorPreset) / sizeof(colorPreset[0]))) colorIter = 0;
      }

      if(posX == 0) {
        x = 1;

        memcpy(dvdLogo + 2, colorPreset[colorIter], 3);

        colorIter++;

        if(colorIter >= (sizeof(colorPreset) / sizeof(colorPreset[0]))) colorIter = 0;
      }

      if(posY == 0) {
        y = 1;
        
        memcpy(dvdLogo + 2, colorPreset[colorIter], 3);

        colorIter++;

        if(colorIter >= (sizeof(colorPreset) / sizeof(colorPreset[0]))) colorIter = 0;
      }

      st7735_text(&st, dvdLogo, posX, posY, 2); 
      
      st7735_drawBuffered(&st);
    }
  }

  /*pcd8544_t pcd;
  pcd_init(&pcd, 6, 5, 4, PCD8544_USE_SPI_CS1);

  int t = 1;
  int r = 1;

  uint8_t pt = 0;
  uint8_t pr = 0;

  while(1) {
    pcd_clear(&pcd);

    pcd_text5x7(&pcd, "Hello, world!\nTest\tTab1232456", 2, 2);

    for(uint8_t x = 0; x < 10; x++) {
      for(uint8_t y = 0; y < 10; y++) {
        pcd_setPixel(&pcd, x + pr, y + pt, 1);
      }
    }

    pr += r;
    pt += t;

    if(pr == PCD8544_WIDTH - 10)
      r = -1;

    if(pr == 0)
      r = 1;

    if(pt == PCD8544_HEIGHT - 10)
      t = -1;

    if(pt == 0)
      t = 1;

    //delay_ms(5);

    pcd_draw(&pcd);
  }*/
}
