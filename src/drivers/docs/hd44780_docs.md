### src/drivers/hd44780.c / .h - HD44780 LCD driver

[**Back**](../drivers_docs.md)

##### Structs:
<a name="hd44780_t"></a>
```C
typedef struct hd44780_s {
    uint8_t registerSelPin;
    uint8_t enablePin;
    uint8_t dataPins[8];
} hd44780_t;
```

###### Description
HD44780 LCD needs defined struct in code to initialize pins that screen utilizes.
> [!NOTE]
> Currently there is only possibility to set HD44780 in 4 bit mode. 4 bit mode utilizes `hd44780_t.dataPins[0..3]` for 4 bit transactions, other pins are set to **0xFF**

###### Fields
- **registerSelPin** - pin on GPIO that should be used as RS (register/select) pin and is connected to RS pin on HD44780
- **enablePin** - pin on GPIO that should be used as E (enable) pin and is connected to E pin on HD44780
- **dataPins[0..7]** - pins on GPIO (0..4 or 0..7) that are used as D<0..7 or 4..7> (data) pins and are connected to D<0..7 or 4..7> pins on HD44780

###### Example usage
```C
#include "drivers/hd44780.h"

...

hd44780_t lcd;

...

```

##### Functions:
```C
void hd44780_init4(hd44780_t* const pHd, uint8_t rs, uint8_t en, uint8_t d4, uint8_t d5, uint8_t d6, uint8_t d7);
```

###### Description
Initializes [`hd44780_t`](hd44780_t) struct with RS, E and D<4..7> pins info and the pins itself.
> [!NOTE]
> 8 bit version is not available currently as 4 bit is more efficient with pins usage. I strongly advise to use 4 bit version. 8 bit support would be added later!

###### Parameters
- **pHd** - pointer to [`hd44780_t`](hd44780_t) struct
- **rs** - RS (register select) pin
- **en** - E (enable) pin
- **d<4..7>** - D<4..7> (data) pins

###### Example usage
```C
#include "drivers/hd44780.h"

...

#define LCD_RS 2
#define LCD_EN 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

hd44780_t lcd;

...

void kernel_main() {
    hd44780_init4(&lcd, LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    ...
}
```

---
<a name="hd44780_clear"></a>
```C
void hd44780_clear(hd44780_t* const pHd);
```

###### Description
Clears desired HD44780 LCD from characters.
> [!TIP]
> Best used with [`hd44780_home`](hd44780_home) function

###### Parameters
- **pHd** - pointer to desired [`hd44780_t`](hd44780_t) LCD struct, which screen would be cleared from characters 

###### Example usage
```C
#include "drivers/hd44780.h"

...

#define LCD_RS 2
#define LCD_EN 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

hd44780_t lcd;

...

void kernel_main() {
    hd44780_init4(&lcd, LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    
    hd44780_print(&lcd, "Hello, world!");

    // Clears screen from "Hello, world!" text
    hd44780_clear(&lcd);

    ...
}

```

---
<a name="hd44780_home"></a>
```C
void hd44780_home(hd44780_t* const pHd);
```
###### Description
Moves cursor to default (0) position.
> [!TIP]
> Best used with [`hd44780_clear`](hd44780_clear) function.

###### Parameters
- **pHd** - pointer to desired [`hd44780_t`](hd44780_t) LCD struct, which cursor would be moved back to default (0) position.

###### Example usage
```C
#include "drivers/hd44780.h"

...

#define LCD_RS 2
#define LCD_EN 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

hd44780_t lcd;

...

void kernel_main() {
    hd44780_init4(&lcd, LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    
    hd44780_print(&lcd, "Hello, world!");

    // Clears screen from "Hello, world!" text
    hd44780_clear(&lcd);
    // Go back to default cursor position after clearing screen
    hd44780_home(&lcd);

    ...
}

```

---
```C
void hd44780_cursor(hd44780_t* const pHd, uint8_t col, uint8_t row);
```

###### Description
Moves cursor on desired LCD to desired column and row.

###### Parameters
- **pHd** - pointer to desired [`hd44780_t`](hd44780_t) LCD struct, which cursor would be moved to desired column and row
- **col** - desired column that cursor would be moved to
- **row** - desired row that cursor would be moved to

###### Example usage
```C
#include "drivers/hd44780.h"

...

#define LCD_RS 2
#define LCD_EN 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

hd44780_t lcd;

...

void kernel_main() {
    hd44780_init4(&lcd, LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    
    // Set character position to col 1 row 2
    hd44780_cursor(&lcd, 1, 2);
    // Print
    hd44780_print(&lcd, "Hello, world!");

    ...
}

```

---
```C
void hd44780_print(hd44780_t* const pHd, const char* text);
```

###### Description
Prints characters on desired [`hd44780_t`](hd44780_t) LCD screen

###### Parameters
- **pHd** - pointer to desired [`hd44780_t`](hd44780_t) LCD screen on which text would be printed
- **text** - text to be printed on LCD

###### Example usage
```C
#include "drivers/hd44780.h"

...

#define LCD_RS 2
#define LCD_EN 3
#define LCD_D4 4
#define LCD_D5 5
#define LCD_D6 6
#define LCD_D7 7

hd44780_t lcd;

...

void kernel_main() {
    hd44780_init4(&lcd, LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);
    
    // Print "Hello, world!"
    hd44780_print(&lcd, "Hello, world!");

    ...
}

```

