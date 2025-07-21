### src/drivers/pcd8544.c / .h - PCD8544 (Nokia 5110) 84x48 LCD screen driver

##### Definitions:
<a id="PCD8544_WIDTH"></a>
```C
PCD8544_WIDTH
```

###### Description
This defined PCD LCD screen width, which is 84

---
<a id="PCD8544_HEIGHT"></a>
```C
PCD8544_HEIGHT
```

###### Description
This defined PCD LCD screen height, which is 48

---
<a id="PCD8544_USE_SPI_CS1"></a>
```C
PCD8544_USE_SPI_CS1 
```

###### Description
This is used when user wants to use default SPI Chip Select 1 instead of GPIO, this sets cs argument in [`pcd_init`](#pcd_init) to max value (255)

##### Structs:
```C
typedef struct pcd8544_s {
  uint8_t chipSelectPin;
  uint8_t dataCommandPin;
  uint8_t resetPin;
  uint8_t backlightPin;

  uint8_t framebuffer[(PCD8544_WIDTH * PCD8544_HEIGHT) / 8];
} pcd8544_t;
```

###### Description
This is main PCD LCD screen struct, containing all pins and framebuffer for desired screen

###### Parameters
- **chipSelectPin** - chip select pin, can be set to GPIO pin value or [`PCD8544_USE_SPI_CS1`](#PCD8544_USE_SPI_CS1) to use default CS1 SPI pin
- **dataCommandPin** - pin controlling PCD LCD screen data and command transfer
- **resetPin** - pin that resets PCD LCD screen
- **backlightPin** - pin that lits up backlight
- **framebuffer** - array of 8 bit values of size <[PCD8544_WIDTH](#PCD8544_WIDTH) * [PCD8544_HEIGHT](#PCD8544_HEIGHT) / 8>, every bit represents one pixel on screen to save space

###### Example usage
```C
#include "drivers/pcd8544.h"

...

pcd8544_t pcd;
```

##### Functions:
```C
void pcd_reset(pcd8544_t* const pPcd);
```

###### Description
Resets desired PCD LCD screen.

###### Parameters
- **pPcd** - pointer to desired PCD LCD screen struct

###### Example usage
```C
#include "drivers/pcd8544.h"

...

#define PCD_RST 1
#define PCD_DC 2
#define PCD_BL 3

pcd8544_t pcd;

void kernel_main() {
    pcd_init(&pcd, PCD_RST, PCD_DC, PCD_BL, PCD8544_USE_SPI_CS1);

    pcd_reset(&pcd);

    ...
}

```

---
<a id="pcd_clear"></a>
```C
void pcd_clear(pcd8544_t* const pPcd);
```

###### Description
Clears desired PCD LCD screen framebuffer.
> [!NOTE]
> Use [`pcd_draw`](pcd_draw) along with [`pcd_setPixel`](#pcd_setPixel) to draw pixel or [`pcd_text5x7`](#pcd_text5x7) to draw 5x7 text on screen to see effects of this function.

> [!TIP]
> Use `pcd_clear` before setting any pixels using [`pcd_setPixel`](#pcd_setPixel) or [`pcd_text5x7`](#pcd_text5x7) in loop to clear framebuffer before drawing any pixels on it.

###### Parameters
- **pPcd** - pointer to desired PCD LCD screen, which framebuffer will be cleared

###### Example usage
```C
#include "drivers/pcd8544.h"

...

#define PCD_RST 1
#define PCD_DC 2
#define PCD_BL 3

pcd8544_t pcd;

void kernel_main() {
    pcd_init(&pcd, PCD_RST, PCD_DC, PCD_BL, PCD8544_USE_SPI_CS1);
    
    ...
    
    while(1) {
        // Set text on screen in position (0, 0)
        pcd_text5x7(&pcd, "Hello, world!", 0, 0);

        // Draw text on screen
        pcd_draw(&pcd);

        // Clear screen before drawing anything again
        pcd_clear(&pcd);
    }
}

```

---
<a id="pcd_init"></a>
```C
void pcd_init(pcd8544_t* const pPcd, uint8_t rst, uint8_t dc, uint8_t bl, uint8_t cs);
```

###### Description
Initializes desired PCD LCD screen and it's pins.
> [!NOTE]
> **cs** argument can be initialized with [`PCD8544_USE_SPI_CS1`](#PCD8544_USE_SPI_CS1) if user wants to use default CS1 SPI pin

###### Parameters
- **pPcd** - pointer to desired PCD LCD screen, that gonna be initialized
- **rst** - reset pin
- **dc** - data command select pin
- **bl** - backlight pin
- **cs** - chip select pin, can be GPIO pin or [`PCD8544_USE_SPI_CS1`](#PCD8544_USE_SPI_CS1) for default CS1 SPI pin

###### Example usage
```C
#include "drivers/pcd8544.h"

...

#define PCD_RST 1
#define PCD_DC 2
#define PCD_BL 3

pcd8544_t pcd;

void kernel_main() {
    // Initialize for default CS1 SPI pin
    pcd_init(&pcd, PCD_RST, PCD_DC, PCD_BL, PCD8544_USE_SPI_CS1);
    
    ...
}

```

---
<a id="pcd_setPixel"></a>
```C
void pcd_setPixel(pcd8544_t* const pPcd, uint8_t x, uint8_t y, uint32_t state);
```

###### Description
Sets pixel in desired position (x, y) on desired PCD LCD screen, with desired state (1 for set, 0 for clear).
`pcd_setPixel` function needs [`pcd_draw`](#pcd_draw) to draw this pixel on screen.
> [!NOTE]
> When I finally add boolean support, <state> argument will be able to use `true` or `false` values.

###### Parameters
- **pPcd** - pointer to desired PCD LCD screen
- **x** - X-axis of pixel
- **y** - Y-axis of pixel
- **state** - desired state of pixel, 1 for set, 0 for clear

###### Example usage
```C
#include "drivers/pcd8544.h"

...

#define PCD_RST 1
#define PCD_DC 2
#define PCD_BL 3

pcd8544_t pcd;

void kernel_main() {
    pcd_init(&pcd, PCD_RST, PCD_DC, PCD_BL, PCD8544_USE_SPI_CS1);
    
    ...
    
    while(1) {
        // Set pixel on screen in position (10, 10) to set
        pcd_setPixel(&pcd, 10, 10, 1);

        // Draw text on screen
        pcd_draw(&pcd);

        // Clear screen before drawing anything again
        pcd_clear(&pcd);
    }
}

```

---
<a id="pcd_draw"></a>
```C
void pcd_draw(pcd8544_t* const pPcd);
```
###### Description
Draws entire framebuffer from desired PCD LCD screen on desired PCD LCD screen.
> [!TIP]
> Use it once in your loop as drawing iterates through all pixels using for loops, so it can be heavy on performance. Lighter version could be implemented, but [`pcd_clear`](#pcd_clear) shouldn't be used while using lighter version as it defeats whole purpose of drawing section between (x0, y0) and (x1, y1).

###### Parameters
- **pPcd** - pointer to desired PCD LCD screen, on which framebuffer data would be drawn

###### Example usage
```C
#include "drivers/pcd8544.h"

...

#define PCD_RST 1
#define PCD_DC 2
#define PCD_BL 3

pcd8544_t pcd;

void kernel_main() {
    pcd_init(&pcd, PCD_RST, PCD_DC, PCD_BL, PCD8544_USE_SPI_CS1);
    
    ...
    
    while(1) {
        // Set pixel on screen in position (10, 10) to set
        pcd_setPixel(&pcd, 10, 10, 1);

        // Draw text on screen
        pcd_draw(&pcd);

        // Clear screen before drawing anything again
        pcd_clear(&pcd);
    }
}

```

---
<a id="pcd_text5x7"></a>
```C
void pcd_text5x7(pcd8544_t* const pPcd, const char* text, uint8_t x, uint8_t y);
```

###### Description
Draws text in desired place on desired PCD LCD screen. Text have 5x7 resolution as function name suggest.
> [!NOTE]
> `pcd_text5x7` needs [`pcd_draw`](#pcd_draw) to be displayed.

###### Parameters
- **pPcd** - pointer to desired PCD LCD screen, in which framebuffer, text pixels would be placed.
- **text** - text to be drawn
- **x** - X-axis of beginning of drawn text
- **y** - Y-axis of beginning of drawn text

###### Example usage
```C
#include "drivers/pcd8544.h"

...

#define PCD_RST 1
#define PCD_DC 2
#define PCD_BL 3

pcd8544_t pcd;

void kernel_main() {
    pcd_init(&pcd, PCD_RST, PCD_DC, PCD_BL, PCD8544_USE_SPI_CS1);
    
    ...
    
    while(1) {
        // Set text on screen in position (0, 0)
        pcd_text5x7(&pcd, "Hello, world!", 0, 0);

        // Draw text on screen
        pcd_draw(&pcd);

        // Clear screen before drawing anything again
        pcd_clear(&pcd);
    }
}

```

