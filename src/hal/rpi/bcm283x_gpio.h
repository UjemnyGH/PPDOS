#ifndef _PPDOS_HAL_BCM283X_GPIO_
#define _PPDOS_HAL_BCM283X_GPIO_

#include "bcm283x_regs.h"

typedef struct rpi_hal_gpio_s {
  rpi_hal_io32_t functionSelect[6];
  rpi_hal_uint32_t RESERVED0;
  rpi_hal_io32_t pinOutputSet[2];
  rpi_hal_uint32_t RESERVED1;
  rpi_hal_io32_t pinOutputClear[2];
  rpi_hal_uint32_t RESERVED2;
  rpi_hal_io32_t pinLevel[2];
  rpi_hal_uint32_t RESERVED3;
  rpi_hal_io32_t pinEventDetectStat[2];
  rpi_hal_uint32_t RESERVED4;
  rpi_hal_io32_t pinRisingEdgeDetectEnable[2];
  rpi_hal_uint32_t RESERVED5;
  rpi_hal_io32_t pinFallingEdgeDetectEnable[2];
  rpi_hal_uint32_t RESERVED6;
  rpi_hal_io32_t pinHighDetectEnable[2];
  rpi_hal_uint32_t RESERVED7;
  rpi_hal_io32_t pinLowDetectEnable[2];
  rpi_hal_uint32_t RESERVED8;
  rpi_hal_io32_t pinAsyncRisingEdgeDetect[2];
  rpi_hal_uint32_t RESERVED9;
  rpi_hal_io32_t pinAsyncFallingEdgeDetect[2];
  rpi_hal_uint32_t RESERVED10;
  rpi_hal_io32_t pinPullEnable;
  rpi_hal_io32_t pinPullEnableClk[2];
  rpi_hal_uint32_t RESERVED11[4];
  rpi_hal_io32_t test;
} __attribute__((packed)) rpi_hal_gpio_t; 

/* 9 pins per select, shift 3, 30 and 31 bit are reserved */
enum rpi_hal_gpio_functionSelect {
  gpio_functionSelect_input = 0x0,
  gpio_functionSelect_output = 0x1,
  gpio_functionSelect_alt0 = 0x4,
  gpio_functionSelect_alt1 = 0x5,
  gpio_functionSelect_alt2 = 0x6,
  gpio_functionSelect_alt3 = 0x7,
  gpio_functionSelect_alt4 = 0x3,
  gpio_functionSelect_alt5 = 0x2,

  gpio_functionSelect_reset = 0x0
};

/*

SDA0                BSC6 master 0 data line 
SCL0                BSC master 0 clock line 
SDA1                BSC master 1 data line 
SCL1                BSC master 1 clock line 
GPCLK0              General purpose Clock 0 
GPCLK1              General purpose Clock 1 
GPCLK2              General purpose Clock 2 
SPI0_CE1_N          SPI0 Chip select 1 
SPI0_CE0_N          SPI0 Chip select 0 
SPI0_MISO           SPI0 MISO 
SPI0_MOSI           SPI0 MOSI 
SPI0_SCLK           SPI0 Serial clock 
PWMx                Pulse Width Modulator 0..1 
TXD0                UART 0 Transmit Data 
RXD0                UART 0 Receive Data 
CTS0                UART 0 Clear To Send 
RTS0                UART 0 Request To Send 
PCM_CLK             PCM clock 
PCM_FS              PCM Frame Sync 
PCM_DIN             PCM Data in 
PCM_DOUT            PCM data out 
SAx                 Secondary mem Address bus 
SOE_N / SE          Secondary mem. Controls 
SWE_N / SRW_N       Secondary mem. Controls 
SDx                 Secondary mem. data bus 
BSCSL SDA / MOSI    BSC slave Data, SPI salve MOSI 
BSCSL SCL / SCLK    BSC slave Clock, SPI slave clock 
BSCSL - / MISO      BSC <not used>,SPI MISO 
BSCSL - / CE_N      BSC <not used>, SPI CSn 
SPI1_CEx_N          SPI1 Chip select 0-2 
SPI1_MISO           SPI1 MISO 
SPI1_MOSI           SPI1 MOSI 
SPI1_SCLK           SPI1 Serial clock 
TXD0                UART 1 Transmit Data 
RXD0                UART 1 Receive Data 
CTS0                UART 1 Clear To Send 
RTS0                UART 1 Request To Send 
SPI2_CEx_N          SPI2 Chip select 0-2
SPI2_MISO           SPI2 MISO
SPI2_MOSI           SPI2 MOSI
SPI2_SCLK           SPI2 Serial clock
ARM_TRST            ARM JTAG reset
ARM_RTCK            ARM JTAG return clock
ARM_TDO             ARM JTAG Data out
ARM_TCK             ARM JTAG Clock
ARM_TDI             ARM JTAG Data in
ARM_TMS             ARM JTAG Mode select 

*/

#define RPI_HAL_GPIO_ALT_FUNCTION_MAKER(altFunction, pin, shift) ((rpi_hal_uint32_t)(altFunction & 0x7) | ((rpi_hal_uint32_t)(pin & 0x3F) << 3) | ((rpi_hal_uint32_t)(shift & 0x1F) << 9))
#define RPI_HAL_GPIO_ALT_FUNCTION_MAKER_FUNCTION_MASK 0x7
#define RPI_HAL_GPIO_ALT_FUNCTION_MAKER_PIN_MASK 0x1F8
#define RPI_HAL_GPIO_ALT_FUNCTION_MAKER_SHIFT_MASK 0x3F00

enum rpi_hal_gpio_functionSelect_allAltFunctions {
  // GPIO 0
  gpio0_functionSelect_alt0_sda0               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 0, 0),
  gpio0_functionSelect_alt1_sa5                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 0, 0),

  // GPIO 1
  gpio1_functionSelect_alt0_scl0               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 1, 3),
  gpio1_functionSelect_alt1_sa4                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 1, 3),

  // GPIO 2
  gpio2_functionSelect_alt0_sda1               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 2, 6),
  gpio2_functionSelect_alt1_sa3                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 2, 6),

  // GPIO 3
  gpio3_functionSelect_alt0_scl1               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 3, 9),
  gpio3_functionSelect_alt1_sa2                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 3, 9),

  // GPIO 4
  gpio4_functionSelect_alt0_gpclk0             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 4, 12),
  gpio4_functionSelect_alt1_sa1                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 4, 12),
  gpio4_functionSelect_alt5_arm_tdi            = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 4, 12),

  // GPIO 5
  gpio5_functionSelect_alt0_gpclk1             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 5, 15),
  gpio5_functionSelect_alt1_sa0                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 5, 15),
  gpio5_functionSelect_alt5_arm_tdo            = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 5, 15),

  // GPIO 6
  gpio6_functionSelect_alt0_gpclk2             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 6, 18),
  gpio6_functionSelect_alt1_soe_n_se           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 6, 18),
  gpio6_functionSelect_alt5_arm_rtck           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 6, 18),

  // GPIO 7
  gpio7_functionSelect_alt0_spi0_ce1_n         = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 7, 21),
  gpio7_functionSelect_alt1_swe_n_srw_n        = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 7, 21),

  // GPIO 8
  gpio8_functionSelect_alt0_spi0_ce0_n         = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 8, 24),
  gpio8_functionSelect_alt1_sd0                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 8, 24),

  // GPIO 9
  gpio9_functionSelect_alt0_spi0_miso          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 9, 27),
  gpio9_functionSelect_alt1_sd1                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 9, 27),

  // GPIO 10
  gpio10_functionSelect_alt0_spi0_mosi         = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 10, 0),
  gpio10_functionSelect_alt1_sd2               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 10, 0),

  // GPIO 11
  gpio11_functionSelect_alt0_spi0_sclk         = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 11, 3),
  gpio11_functionSelect_alt1_sd3               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 11, 3),

  // GPIO 12
  gpio12_functionSelect_alt0_pwm0              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 12, 6),
  gpio12_functionSelect_alt1_sd4               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 12, 6),
  gpio12_functionSelect_alt5_arm_tms           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 12, 6),

  // GPIO 13
  gpio13_functionSelect_alt0_pwm1              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 13, 9),
  gpio13_functionSelect_alt1_sd5               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 13, 9),
  gpio13_functionSelect_alt5_arm_tck           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 13, 9),

  // GPIO 14
  gpio14_functionSelect_alt0_txd0              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 14, 12),
  gpio14_functionSelect_alt1_sd6               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 14, 12),
  gpio14_functionSelect_alt5_txd1              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 14, 12),

  // GPIO 15
  gpio15_functionSelect_alt0_rxd0              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 15, 15),
  gpio15_functionSelect_alt1_sd7               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 15, 15),
  gpio15_functionSelect_alt5_rxd1              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 15, 15),

  // GPIO 16
  gpio16_functionSelect_alt1_sd8               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 16, 18),
  gpio16_functionSelect_alt3_uart0_cts         = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 16, 18),
  gpio16_functionSelect_alt4_spi1_ce2_n        = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 16, 18),
  gpio16_functionSelect_alt5_uart1_cts         = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 16, 18),

  // GPIO 17
  gpio17_functionSelect_alt1_sd9               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 17, 21),
  gpio17_functionSelect_alt3_uart0_rts         = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 17, 21),
  gpio17_functionSelect_alt4_spi1_ce1_n        = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 17, 21),
  gpio17_functionSelect_alt5_uart1_rts         = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 17, 21),

  // GPIO 18
  gpio18_functionSelect_alt0_pcm_clk             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 18, 24),
  gpio18_functionSelect_alt1_sd10                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 18, 24),
  gpio18_functionSelect_alt3_bscsl_sda_mosi      = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 18, 24),
  gpio18_functionSelect_alt4_spi1_ce0_n          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 18, 24),
  gpio18_functionSelect_alt5_pwm0                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 18, 24),

  // GPIO 19
  gpio19_functionSelect_alt0_pcm_fs              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 19, 27),
  gpio19_functionSelect_alt1_sd11                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 19, 27),
  gpio19_functionSelect_alt3_bscsl_scl_sclk      = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 19, 27),
  gpio19_functionSelect_alt4_spi1_miso           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 19, 27),
  gpio19_functionSelect_alt5_pwm1                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 19, 27),

  // GPIO 20
  gpio20_functionSelect_alt0_pcm_din             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 20, 0),
  gpio20_functionSelect_alt1_sd12                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 20, 0),
  gpio20_functionSelect_alt3_bscsl_miso          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 20, 0),
  gpio20_functionSelect_alt4_spi1_mosi           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 20, 0),
  gpio20_functionSelect_alt5_gpclk0              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 20, 0),

  // GPIO 21
  gpio21_functionSelect_alt0_pcm_dout            = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 21, 3),
  gpio21_functionSelect_alt1_sd13                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 21, 3),
  gpio21_functionSelect_alt3_bscsl_ce_n          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 21, 3),
  gpio21_functionSelect_alt4_spi1_sclk           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 21, 3),
  gpio21_functionSelect_alt5_gpclk1              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 21, 3),

  // GPIO 22
  gpio22_functionSelect_alt1_sd14                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 22, 6),
  gpio22_functionSelect_alt3_sd1_clk             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 22, 6),
  gpio22_functionSelect_alt4_arm_trst            = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 22, 6),

  // GPIO 23
  gpio23_functionSelect_alt1_sd15                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 23, 9),
  gpio23_functionSelect_alt3_sd1_cmd             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 23, 9),  
  gpio23_functionSelect_alt4_arm_rtck            = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 23, 9),

  // GPIO 24
  gpio24_functionSelect_alt1_sd16                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 24, 12),
  gpio24_functionSelect_alt3_sd1_dat0            = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 24, 12),
  gpio24_functionSelect_alt4_arm_tdo             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 24, 12),

  // GPIO 25
  gpio25_functionSelect_alt1_sd17                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 25, 15),
  gpio25_functionSelect_alt3_sd1_dat1            = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 25, 15),
  gpio25_functionSelect_alt4_arm_tck             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 25, 15),

  // GPIO 26
  gpio26_functionSelect_alt3_sd1_dat2            = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 26, 18),
  gpio26_functionSelect_alt4_arm_tdi             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 26, 18),

  // GPIO 27
  gpio27_functionSelect_alt3_sd1_dat3            = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 27, 21),
  gpio27_functionSelect_alt4_arm_tms             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 27, 21),

  // GPIO 28
  gpio28_functionSelect_alt0_sda0                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 28, 24),
  gpio28_functionSelect_alt1_sa5                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 28, 24),
  gpio28_functionSelect_alt2_pcm_clk             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt2, 28, 24),

  // GPIO 29
  gpio29_functionSelect_alt0_scl0                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 29, 27),
  gpio29_functionSelect_alt1_sa4                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 29, 27),
  gpio29_functionSelect_alt2_pcm_fs              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt2, 29, 27),

  // GPIO 30
  gpio30_functionSelect_alt1_sa3                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 30, 0),
  gpio30_functionSelect_alt2_pcm_din             = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt2, 30, 0),
  gpio30_functionSelect_alt3_uart0_cts0          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 30, 0),
  gpio30_functionSelect_alt5_uart1_cts1          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 30, 0),

  // GPIO 31
  gpio31_functionSelect_alt1_sa2                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 31, 3),
  gpio31_functionSelect_alt2_pcm_dout            = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt2, 31, 3),
  gpio31_functionSelect_alt3_uart0_rts0          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 31, 3),
  gpio31_functionSelect_alt5_uart1_rts1          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 31, 3),

  // GPIO 32
  gpio32_functionSelect_alt0_gpclk0              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 32, 6),
  gpio32_functionSelect_alt1_sa1                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 32, 6),
  gpio32_functionSelect_alt3_uart0_txd0          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 32, 6),
  gpio32_functionSelect_alt5_uart1_txd1          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 32, 6),

  // GPIO 33
  gpio33_functionSelect_alt1_sa0                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 33, 9),
  gpio33_functionSelect_alt3_uart0_rxd0          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt3, 33, 9),
  gpio33_functionSelect_alt5_uart1_rxd1          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 33, 9),

  // GPIO 34
  gpio34_functionSelect_alt0_gpclk0              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 34, 12),
  gpio34_functionSelect_alt1_soe_n               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 34, 12),

  // GPIO 35
  gpio35_functionSelect_alt0_spi0_ce1_n          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 35, 15),
  gpio35_functionSelect_alt1_swe_n               = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 35, 15),

  // GPIO 36
  gpio36_functionSelect_alt0_spi0_ce0_n          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 36, 18),
  gpio36_functionSelect_alt1_sd0                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 36, 18),
  gpio36_functionSelect_alt2_uart0_txd0          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt2, 36, 18),

  // GPIO 37
  gpio37_functionSelect_alt0_spi0_miso           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 37, 21),
  gpio37_functionSelect_alt1_sd1                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 37, 21),
  gpio37_functionSelect_alt2_uart0_rxd0          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt2, 37, 21),

  // GPIO 38
  gpio38_functionSelect_alt0_spi0_mosi           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 38, 24),
  gpio38_functionSelect_alt1_sd2                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 38, 24),
  gpio38_functionSelect_alt2_uart0_rts0          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt2, 38, 24),

  // GPIO 39
  gpio39_functionSelect_alt0_spi0_sclk           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 39, 27),
  gpio39_functionSelect_alt1_sd3                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 39, 27),
  gpio39_functionSelect_alt2_uart0_cts0          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt2, 39, 27),

  // GPIO 40
  gpio40_functionSelect_alt0_pwm0                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 40, 0),
  gpio40_functionSelect_alt1_sd4                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 40, 0),
  gpio40_functionSelect_alt4_spi2_miso           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 40, 0),
  gpio40_functionSelect_alt5_uart1_txd1          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 40, 0),

  // GPIO 41
  gpio41_functionSelect_alt0_pwm1                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 41, 3),
  gpio41_functionSelect_alt1_sd5                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 41, 3),
  gpio41_functionSelect_alt4_spi2_mosi           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 41, 3),
  gpio41_functionSelect_alt5_uart1_rxd1          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 41, 3),

  // GPIO 42
  gpio42_functionSelect_alt0_gpclk1              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 42, 6),
  gpio42_functionSelect_alt1_sd6                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 42, 6),
  gpio42_functionSelect_alt4_spi2_sclk           = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 42, 6),
  gpio42_functionSelect_alt5_uart1_cts1          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 42, 6),

  // GPIO 43
  gpio43_functionSelect_alt0_gpclk2              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 43, 9),
  gpio43_functionSelect_alt1_sd7                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 43, 9),
  gpio43_functionSelect_alt4_spi2_ce0_n          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 43, 9),
  gpio43_functionSelect_alt5_uart1_rts1          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt5, 43, 9),

  // GPIO 44
  gpio44_functionSelect_alt0_gpclk1              = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 44, 12),
  gpio44_functionSelect_alt1_sd8                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 44, 12),
  gpio44_functionSelect_alt4_spi2_ce1_n          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 44, 12),

  // GPIO 45
  gpio45_functionSelect_alt0_pwm1                = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt0, 45, 15),
  gpio45_functionSelect_alt1_sd9                 = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt1, 45, 15),
  gpio45_functionSelect_alt4_spi2_ce2_n          = RPI_HAL_GPIO_ALT_FUNCTION_MAKER(gpio_functionSelect_alt4, 45, 15),
};

enum rpi_hal_gpio_pinPullEnable {
  gpio_pinPullEnable_off = 0x0,
  gpio_pinPullEnable_pullDown = 0x1,
  gpio_pinPullEnable_pullUp = 0x2,

  gpio_pinPullEnable_reset = 0x0
};

#define gpio        (*(rpi_hal_gpio_t*)RPI_HAL_GPIO_BASE)

void rpi_hal_gpio_setFunction(const rpi_hal_uint8_t pin, const enum rpi_hal_gpio_functionSelect function);

void rpi_hal_gpio_setSpecialAltFunction(const enum rpi_hal_gpio_functionSelect_allAltFunctions function);

void rpi_hal_gpio_setOutputSet(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state);

void rpi_hal_gpio_setOutputClear(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state);

void rpi_hal_gpio_setPinEventDetectStatus(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state);

void rpi_hal_gpio_setPinRisingEdgeDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state);

void rpi_hal_gpio_setPinFallingEdgeDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state);

void rpi_hal_gpio_setPinHighDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state);

void rpi_hal_gpio_setPinLowDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state);

void rpi_hal_gpio_setPinAsyncRisingEdgeDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state);

void rpi_hal_gpio_setPinAsyncFallingEdgeDetectEnable(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state);

void rpi_hal_gpio_setPullEnable(const enum rpi_hal_gpio_pinPullEnable pull);

void rpi_hal_gpio_setPinPullEnableClock(const rpi_hal_uint8_t pin, const rpi_hal_uint32_t state);

rpi_hal_uint32_t rpi_hal_gpio_getPinLevel(const rpi_hal_uint8_t pin);

#endif
