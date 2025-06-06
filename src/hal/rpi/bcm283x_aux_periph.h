#ifndef _PPDOS_HAL_BCM283X_AUX_PERIPH_
#define _PPDOS_HAL_BCM283X_AUX_PERIPH_

#include "bcm283x_regs.h"

typedef struct rpi_hal_aux_periph_s {
  rpi_hal_io32_t intStatus;
  rpi_hal_io32_t enables;
  
  rpi_hal_uint32_t RESERVED0[15];
    
  struct {
    rpi_hal_io32_t IOData;
    rpi_hal_io32_t intEnable;
    rpi_hal_io32_t intId;
    rpi_hal_io32_t lineClt;
    rpi_hal_io32_t modemCtl;
    rpi_hal_io32_t lineStat;
    rpi_hal_io32_t modemStat;
    rpi_hal_io32_t scratch;
    rpi_hal_io32_t extraCtl;
    rpi_hal_io32_t extraStat;
    rpi_hal_io32_t baudrate;
  } miniUart;
  
  rpi_hal_uint32_t RESERVED1[6];

  struct {
    rpi_hal_io32_t ctl0;
    rpi_hal_io32_t ctl1;
    rpi_hal_io32_t stat;
    rpi_hal_io32_t data;
    rpi_hal_io32_t peek;
  } spi0;

  rpi_hal_uint32_t RESERVED2[11];

  struct {
    rpi_hal_io32_t ctl0;
    rpi_hal_io32_t ctl1;
    rpi_hal_io32_t stat;
    rpi_hal_io32_t data;
    rpi_hal_io32_t peek;
  } spi1;
} __attribute__((packed)) rpi_hal_aux_periph_t;

enum rpi_hal_aux_periph_intStatus {
  auxPeriph_intStatus_miniUartIntPending = 0x1,
  auxPeriph_intStatus_spi0IntPending = 0x2,
  auxPeriph_intStatus_spi1IntPending = 0x4,
  
  auxPeriph_intStatus_reset = 0x0
};

enum rpi_hal_aux_periph_enables {
  auxPeriph_enables_miniUart = 0x1,
  auxPeriph_enables_spi0 = 0x2,
  auxPeriph_enables_spi1 = 0x4,

  auxPeriph_enables_reset = 0x0
};

enum rpi_hal_aux_periph_miniUart_intEnable {
  auxPeriph_miniUart_intEnable_receiveInt = 0x1,
  auxPeriph_miniUart_intEnable_transmitInt = 0x2,

  auxPeriph_miniUart_intEnable_reset = 0xFC
};

enum rpi_hal_aux_periph_miniUart_intId {
  auxPeriph_miniUart_intId_intPending = 0x1,
  auxPeriph_miniUart_intId_readTransmitHoldsEmpty = 0x2,
  auxPeriph_miniUart_intId_readReceiverHoldsValidByte = 0x4,
  auxPeriph_miniUart_intId_writeClearReceiveFIFO = 0x2,
  auxPeriph_miniUart_intId_writeClearTransmitFIFO = 0x4,

  auxPeriph_miniUart_intId_reset = 0xC1
};

enum rpi_hal_aux_periph_miniUart_lineCtl {
  auxPeriph_miniUart_lineCtl_uart8BitMode = 0x3,
  auxPeriph_miniUart_lineCtl_break = 0x40,
  auxPeriph_miniUart_lineCtl_dlabAccess = 0x80,

  auxPeriph_miniUart_lineCtl_reset = 0x0
};

enum rpi_hal_aux_periph_miniUart_modemCtl {
  auxPeriph_miniUart_modemCtl_rts = 0x2,

  auxPeriph_miniUart_modemCtl_reset = 0x0
};

enum rpi_hal_aux_periph_miniUart_lineStat {
  auxPeriph_miniUart_lineStat_dataReady = 0x1,
  auxPeriph_miniUart_lineStat_receiverOverrun = 0x2,
  auxPeriph_miniUart_lineStat_transmitterEmpty = 0x20,
  auxPeriph_miniUart_lineStat_transmitterIdle = 0x40,

  auxPeriph_miniUart_lineStat_reset = 0x40
};

enum rpi_hal_aux_periph_miniUart_modemStat {
  auxPeriph_miniUart_modemStat_ctsStatus = 0x20
};

enum rpi_hal_aux_periph_miniUart_extraCtl {
  auxPeriph_miniUart_extraCtl_receiverEnable = 0x1,
  auxPeriph_miniUart_extraCtl_transmitterEnable = 0x2,
  auxPeriph_miniUart_extraCtl_autoReceiveEnable = 0x4,
  auxPeriph_miniUart_extraCtl_autoTransmitEnable = 0x8,
  auxPeriph_miniUart_extraCtl_autoReceiveFIFO3EmptySpaces = 0x0,
  auxPeriph_miniUart_extraCtl_autoReceiveFIFO2EmptySpaces = 0x10,
  auxPeriph_miniUart_extraCtl_autoReceiveFIFO1EmptySpaces = 0x20,
  auxPeriph_miniUart_extraCtl_autoReceiveFIFO4EmptySpaces = 0x30,
  auxPeriph_miniUart_extraCtl_rtsAssert = 0x40,
  auxPeriph_miniUart_extraCtl_ctsAssert = 0x80,

  auxPeriph_miniUart_extraCtl_reset = 0x3
};

enum rpi_hal_aux_periph_miniUart_extraStat {
  auxPeriph_miniUart_extraStat_symbolAvailable = 0x1,
  auxPeriph_miniUart_extraStat_spaceAvailable = 0x2,
  auxPeriph_miniUart_extraStat_receiverIdle = 0x4,
  auxPeriph_miniUart_extraStat_transmitterIdle = 0x8,
  auxPeriph_miniUart_extraStat_receiverOverrun = 0x10,
  auxPeriph_miniUart_extraStat_transmitFIFOFull = 0x20,
  auxPeriph_miniUart_extraStat_rtsStatus = 0x40,
  auxPeriph_miniUart_extraStat_ctsLine = 0x80,
  auxPeriph_miniUart_extraStat_transmitFIFOEmpty = 0x100,
  auxPeriph_miniUart_extraStat_transmitterDone = 0x200,
  auxPeriph_miniUart_extraStat_receiveFIFOFillLevel = 0x10000,
  auxPeriph_miniUart_extraStat_transmitFIFOFillLevel = 0x1000000,

  auxPeriph_miniUart_extraStat_reset = 0x30C
};

enum rpi_hal_aux_periph_spi_ctl0 {
  auxPeriph_spi_ctl0_shiftLenght = 0x1,
  auxPeriph_spi_ctl0_shiftOutMSFirst = 0x20,
  auxPeriph_spi_ctl0_invertSpiClk = 0x40,
  auxPeriph_spi_ctl0_outRising = 0x80,
  auxPeriph_spi_ctl0_clerFIFO = 0x100,
  auxPeriph_spi_ctl0_inRising = 0x200,
  auxPeriph_spi_ctl0_enable = 0x400,
  auxPeriph_spi_ctl0_doutHoldTime1ClockExtra = 0x800,
  auxPeriph_spi_ctl0_doutHoldTime4ClockExtra = 0x1000,
  auxPeriph_spi_ctl0_doutHoldTime7ClockExtra = 0x1800,
  auxPeriph_spi_ctl0_varWidth = 0x2000,
  auxPeriph_spi_ctl0_varCS = 0x4000,
  auxPeriph_spi_ctl0_postInputMode = 0x8000,
  auxPeriph_spi_ctl0_chipSelects = 0x10000,
  auxPeriph_spi_ctl0_speed = 0x80000,

  auxPeriph_spi_ctl0_reset = 0x70000
};

enum rpi_hal_aux_periph_spi_ctl1 {
  auxPeriph_spi_clt1_keepInput = 0x1,
  auxPeriph_spi_clt1_shiftInMSFirst = 0x2,
  auxPeriph_spi_clt1_doneIrq = 0x40,
  auxPeriph_spi_clt1_transmitEmptyIrq = 0x80,
  auxPeriph_spi_ctl1_csHighTime = 0x100,

  auxPeriph_spi_ctl1_reset = 0x0
};

enum rpi_hal_aux_periph_spi_stat {
  auxPeriph_spi_stat_bitCount = 0x1,
  auxPeriph_spi_stat_receiveEmpty = 0x4,
  auxPeriph_spi_stat_transmitEmpty = 0x8,
  auxPeriph_spi_stat_transmitFull = 0x10,
  auxPeriph_spi_stat_busy = 0x40,
  auxPeriph_spi_stat_receiveFIFOLevel = 0x1000,
  auxPeriph_spi_stat_transmitFIFOLevel = 0x2000000,

  auxPeriph_spi_stat_reset = 0x0
};

#define auxPeriph               (*(rpi_hal_aux_periph_t*)RPI_HAL_AUX_PERIPH_BASE)

#endif
