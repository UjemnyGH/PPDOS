#ifndef _PPDOS_DRIVER_PCD8544_
#define _PPDOS_DRIVER_PCD8544_

#include "../common/shared_fn.h"

#define PCD8544_WIDTH 84
#define PCD8544_HEIGHT 48
#define PCD8544_USE_SPI_CS1 255

typedef struct pcd8544_s {
  uint8_t chipSelectPin;
  uint8_t dataCommandPin;
  uint8_t resetPin;
  uint8_t backlightPin;

  uint8_t framebuffer[(PCD8544_WIDTH * PCD8544_HEIGHT) / 8];
} pcd8544_t;

void pcd_reset(pcd8544_t* const pPcd);

void pcd_clear(pcd8544_t* const pPcd);

void pcd_init(pcd8544_t* const pPcd, uint8_t rst, uint8_t dc, uint8_t bl, uint8_t cs);

void pcd_setPixel(pcd8544_t* const pPcd, uint8_t x, uint8_t y, uint32_t state);

void pcd_draw(pcd8544_t* const pPcd);

void pcd_text5x7(pcd8544_t* const pPcd, const char* text, uint8_t x, uint8_t y);

#endif
