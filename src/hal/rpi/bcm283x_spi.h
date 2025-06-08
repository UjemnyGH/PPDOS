#ifndef _PPDOS_HAL_BCM283X_SPI_
#define _PPDOS_HAL_BCM283X_SPI_

#include "bcm283x_regs.h"

typedef struct rpi_hal_spi_s {
  rpi_hal_io32_t controlStat;
  rpi_hal_io32_t fifoData;
  rpi_hal_io32_t clockDiv;
  rpi_hal_io32_t dataLen;
  rpi_hal_io32_t lossiModeTOH;
  rpi_hal_io32_t dmaDataReqCtl;
} __attribute__((packed)) rpi_hal_spi_t;

enum rpi_hal_spi_controlStat {
  spi_controlStat_chipSelect0                   = 0x00000000,
  spi_controlStat_chipSelect1                   = 0x00000001,
  spi_controlStat_chipSelect2                   = 0x00000002,

  spi_controlStat_chipSelectMask                = 0x00000003,

  /*0 as mid*/
  spi_controlStat_clkPhaseTransitionBegDataBit  = 0x00000004,

  /*0 as low*/
  spi_controlStat_clkPolarityHigh               = 0x00000008,

  /*0 as no clear*/
  spi_controlStat_clearTxFIFO                   = 0x00000010,
  spi_controlStat_clearRxFIFO                   = 0x00000020,

  /*0 as low*/
  spi_controlStat_csPolarityActiveHigh          = 0x00000040,
  
  /*0 as inactive*/
  spi_controlStat_transferActive                = 0x00000080,

  /*0 as inactive*/
  spi_controlStat_dmaActive                     = 0x00000100,

  /*0 as dont gen*/
  spi_controlStat_genIntOnDone                  = 0x00000200,

  /*0 as dont gen*/
  spi_controlStat_genIntOnRXR                   = 0x00000400,

  /*0 as dont do it automaticly*/
  spi_controlStat_autoDeassertCSAtEndOfDMA      = 0x00000800,
  spi_controlStat_renReadEnable                 = 0x00001000,
  spi_controlStat_lenLOSSIEnable                = 0x00002000,
  spi_controlStat_transferDone                  = 0x00010000,
  spi_controlStat_rdxRxFIFOData                 = 0x00020000,
  spi_controlStat_tdxTxFIFOData                 = 0x00040000,
  spi_controlStat_rdxRxFIFONeedsReading         = 0x00080000,
  spi_controlStat_rdxRxFIFOFull                 = 0x00100000,

  /*0 on active low*/
  spi_controlStat_cs0PolarityActiveHigh         = 0x00200000,
  spi_controlStat_cs1PolarityActiveHigh         = 0x00400000,
  spi_controlStat_cs2PolarityActiveHigh         = 0x00800000,
  spi_controlStat_csPolarityActiveHighMask      = 0x00E00000,

  spi_controlStat_enableDMAInLOSSI              = 0x01000000,

  /*enableDMAInLOSSI must be set, enable 32bit word, 0 as 1 byte (8bits)*/
  spi_controlStat_enableLongDataWordInLOSSI     = 0x02000000,

  spi_controlStat_reset                         = 0x00041000
};

enum rpi_hal_spi_master_dmaDataReqCtl {
  /*8 bits*/
  spi_dmaDataReqCtl_dmaWriteReqThrshold         = 0x00000001,
  /*8 bits*/
  spi_dmaDataReqCtl_dmaWritePanicThrshold       = 0x00000100,
  /*8 bits*/
  spi_dmaDataReqCtl_dmaReadReqThrshold          = 0x00010000,
  /*8 bits*/
  spi_dmaDataReqCtl_dmaReadPanicThrshold        = 0x01000000,

  spi_dmaDataReqCtl_dmaWriteReqThresholdMask    = 0x000000FF,
  spi_dmaDataReqCtl_dmaWritePanicThresholdMask  = 0x0000FF00,
  spi_dmaDataReqCtl_dmaReadReqThresholdMask     = 0x00FF0000,
  spi_dmaDataReqCtl_dmaReadPanicThresholdMask   = 0xFF000000,

  spi_dmaDataReqCtl_reset                       = 0x30201020
};

#define spi             (*(rpi_hal_spi_t*)RPI_HAL_SPI0_BASE)

void rpi_hal_spi_init();

rpi_hal_uint8_t rpi_hal_spi_transferByte(const rpi_hal_uint8_t data);

void rpi_hal_spi_transfer(const rpi_hal_uint8_t* pSrc, rpi_hal_uint8_t* pDst, const rpi_hal_uint32_t len);

void rpi_hal_spi_deinit();

#endif
