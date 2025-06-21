#ifndef _PPDOS_HAL_BCM283X_UART_
#define _PPDOS_HAL_BCM283X_UART_

#include "bcm283x_regs.h"

typedef struct rpi_hal_uart_s {
  rpi_hal_io32_t data;
  rpi_hal_io32_t receiveStatErrorClear;
  rpi_hal_uint32_t RESERVED0[5];
  rpi_hal_io32_t flag;
  rpi_hal_uint32_t RESERVED1;
  rpi_hal_io32_t intBaudrateDiv; /* 15:0 bit */
  rpi_hal_io32_t fracBaudrateDiv; /* 5:0 bit */
  rpi_hal_io32_t lineCtl;
  rpi_hal_io32_t control;
  rpi_hal_io32_t intFIFOLevelSel;
  rpi_hal_io32_t intMaskSetClear;
  rpi_hal_io32_t rawIntStat;
  rpi_hal_io32_t maskedIntStat;
  rpi_hal_io32_t intClear;
  rpi_hal_io32_t dmaControl;
  rpi_hal_uint32_t RESERVED2[14];
  rpi_hal_io32_t testControl;
  rpi_hal_io32_t testIn;
  rpi_hal_io32_t testOut;
  rpi_hal_io32_t testData;
} __attribute__((packed)) rpi_hal_uart_t;

enum rpi_hal_uart_data {
  uart_data_dataMask      = 0x00FF,
  uart_data_framingError  = 0x0100,
  uart_data_parityError   = 0x0200,
  uart_data_breakError    = 0x0400,
  uart_data_overrunError  = 0x0800,

  uart_data_reset         = 0x0000
};

enum rpi_hal_uart_receiveStatErrorClear {
  uart_receiveStatErrorClear_framingError = 0x1,
  uart_receiveStatErrorClear_parityError  = 0x2,
  uart_receiveStatErrorClear_breakError   = 0x4,
  uart_receiveStatErrorClear_overrunError = 0x8,

  uart_receiveStatErrorClear_reset        = 0x0
};

enum rpi_hal_uart_flag {
  uart_flag_clearToSend           = 0x01,
  uart_flag_busy                  = 0x08,
  uart_flag_receiveFIFOEmpty      = 0x10,
  uart_flag_transmitFIFOFull      = 0x20,
  uart_flag_receiveFIFOFull       = 0x40,
  uart_flag_transmitFIFOEmpty     = 0x80,

  uart_flag_reset                 = 0x80
};

enum rpi_hal_uart_lineCtl {
  uart_lineCtl_sendBreak          = 0x01,
  uart_lineCtl_parityEnable       = 0x02,
  uart_lineCtl_evenParitySelect   = 0x04,
  uart_lineCtl_twoStopBitsSelect  = 0x08,
  uart_lineCtl_enableFIFO         = 0x10,

  uart_lineCtl_wordLength6Bit     = 0x20,
  uart_lineCtl_wordLength7Bit     = 0x40,
  uart_lineCtl_wordLength8Bit     = 0x60,
  uart_lineCtl_wordLengthMask     = 0x60,
  
  uart_lineCtl_stickParitySelect  = 0x80,

  uart_lineCtl_reset              = 0x00
};

enum rpi_hal_uart_control {
  uart_control_enable             = 0x0001,
  uart_control_loopbackEnable     = 0x0080,
  uart_control_transmitEnable     = 0x0100,
  uart_control_receiveEnable      = 0x0200,
  uart_control_requestToSend      = 0x0800,
  uart_control_rtsHardwareEnable  = 0x4000,
  uart_control_ctsHardwareEnable  = 0x8000,

  uart_control_reset              = 0x0300
};

enum rpi_hal_uart_intFIFOLevelSel {
  uart_intFIFOLevelSel_txFIFO_0_125_Full  = 0x00,
  uart_intFIFOLevelSel_txFIFO_0_25_Full   = 0x01,
  uart_intFIFOLevelSel_txFIFO_0_5_Full    = 0x02,
  uart_intFIFOLevelSel_txFIFO_0_75_Full   = 0x03,
  uart_intFIFOLevelSel_txFIFO_0_875_Full  = 0x04,
  uart_intFIFOLevelSel_txFIFOFullMask     = 0x07,

  uart_intFIFOLevelSel_rxFIFO_0_125_Full  = 0x00,
  uart_intFIFOLevelSel_rxFIFO_0_25_Full   = 0x08,
  uart_intFIFOLevelSel_rxFIFO_0_5_Full    = 0x10,
  uart_intFIFOLevelSel_rxFIFO_0_75_Full   = 0x18,
  uart_intFIFOLevelSel_rxFIFO_0_875_Full  = 0x20,
  uart_intFIFOLevelSel_rxFIFOFullMask     = 0x38,

  uart_intFIFOLevelSel_reset              = 0x00
};

/* Apply for intMaskSetClear, rawIntStat, maskedIntStat, intClear */
enum rpi_hal_uart_intStat {
  uart_intStat_ctsModemIntMask            = 0x0002,
  uart_intStat_receiveIntMask             = 0x0010,
  uart_intStat_transmitIntMask            = 0x0020,
  uart_intStat_receiveTimeoutIntMask      = 0x0040,
  uart_intStat_framingErrIntMask          = 0x0080,
  uart_intStat_parityErrIntMask           = 0x0100,
  uart_intStat_breakErrIntMask            = 0x0200,
  uart_intStat_overrunErrIntMask          = 0x0400,

  uart_intStat_reset                      = 0x0000
};

enum rpi_hal_uart_testControl {
  uart_testControl_enable       = 0x1,
  uart_testControl_fifoEnable   = 0x2,

  uart_testControl_reset        = 0x0
};

enum rpi_hal_uart_testIn {
  uart_testIn_rxRead    = 0x1,
  uart_testIn_ctsRead   = 0x8,

  uart_testIn_reset     = 0x0
};

enum rpi_hal_uart_testOut {
  uart_testOut_txWrite  = 0x1,
  uart_testOut_rtsWrite = 0x8,

  uart_testOut_reset    = 0x0
};

/* For custom calculation use 3MHz / baudrate = <integer>.<fractional>, where fractional = 0 + 0.5 + 0.25 + 0.125 + 0.0625 + 0.0312 + 0.0156 (0x0 + 0x20 + 0x10 + 0x8 + 0x4 + 0x2 + 0x1)*/
#define RPI_HAL_UART_BAUDRATE_MAKER(integer, fractional) (fractional | (integer << 5))

enum rpi_hal_uart_baudrate { 
  uart_baudrate_4800    = RPI_HAL_UART_BAUDRATE_MAKER(625, 0),
  uart_baudrate_9600    = RPI_HAL_UART_BAUDRATE_MAKER(312, (1 << 5) /* 1/2    | 0.5000  | 312.50 */),
  uart_baudrate_19200   = RPI_HAL_UART_BAUDRATE_MAKER(156, (1 << 4) /* 1/4    | 0.2500  | 156.25 */),
  uart_baudrate_38400   = RPI_HAL_UART_BAUDRATE_MAKER(78, (1 << 3)  /* 1/8    | 0.1250  | 78.125 */),
  uart_baudrate_57600   = RPI_HAL_UART_BAUDRATE_MAKER(52, (3 << 1)  /* 3/32   | 0.0937  | 52.083 -> 52.0937 */),
  uart_baudrate_115200  = RPI_HAL_UART_BAUDRATE_MAKER(26, 3         /* 3/64   | 0.0468  | 26.041 -> 26.0468 */),
  uart_baudrate_230400  = RPI_HAL_UART_BAUDRATE_MAKER(13, 1         /* 1/64   | 0.0156  | 13.020 -> 13.0156 */),
  uart_baudrate_460800  = RPI_HAL_UART_BAUDRATE_MAKER(6, 0x21       /* 33/64  | 0.5156  | 6.5104 -> 6.5156  */),
  uart_baudrate_921600  = RPI_HAL_UART_BAUDRATE_MAKER(3, 0x11       /* 17/64  | 0.2656  | 3.2552 -> 3.2656  */)
};

#define uart          (*(rpi_hal_uart_t*)RPI_HAL_UART0_BASE)

void rpi_hal_uart_init(const enum rpi_hal_uart_lineCtl control, const enum rpi_hal_uart_baudrate baudrate);

void rpi_hal_uart_transmitByte(const rpi_hal_uint8_t data);

rpi_hal_uint8_t rpi_hal_uart_receiveByte();

void rpi_hal_uart_deinit();

#endif
