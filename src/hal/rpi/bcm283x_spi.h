#ifndef _PPDOS_HAL_BCM283X_SPI_
#define _PPDOS_HAL_BCM283X_SPI_

#include "bcm283x_regs.h"

typedef struct rpi_hal_spi_master_s {
  rpi_hal_io32_t controlStat;
  rpi_hal_io32_t mastrTxRxFIFOData;
  rpi_hal_io32_t masterClkDiv;
  rpi_hal_io32_t masterDataLen;
  rpi_hal_io32_t lossiModeTOH;
  rpi_hal_io32_t dmaDreqCtl;
} __attribute__((packed)) rpi_hal_spi_master_t;

typedef struct rpi_hal_spi_slave_s {
  rpi_hal_io32_t data;
  rpi_hal_io32_t statusAndErrClear;
  rpi_hal_io32_t slaveAddrValue;
  rpi_hal_io32_t control;
  rpi_hal_io32_t flag;
  rpi_hal_io32_t intFIFOLevelSelect;
  rpi_hal_io32_t intMaskSetClear;
  rpi_hal_io32_t rawIntStat;
  rpi_hal_io32_t maskedIntStat;
  rpi_hal_io32_t intClear;
  rpi_hal_io32_t dmaCtl;
  rpi_hal_io32_t fifoTestData;
  rpi_hal_io32_t gpuStat;
  rpi_hal_io32_t hostCtl;
  rpi_hal_io32_t i2cDebug;
  rpi_hal_io32_t spiDebug;

} __attribute__((packed)) rpi_hal_spi_slave_t;

enum rpi_hal_spi_master_controlStat {
  spiMaster_controlStat_chipSelect0 = 0x0,
  spiMaster_controlStat_chipSelect1 = 0x1,
  spiMaster_controlStat_chipSelect2 = 0x2,

  /*0 as mid*/
  spiMaster_controlStat_clkPhaseTransitionBegDataBit = 0x4,

  /*0 as low*/
  spiMaster_controlStat_clkPolarityHigh = 0x8,

  /*0 as no clear*/
  spiMaster_controlStat_clearTxFIFO = 0x10,
  spiMaster_controlStat_clearRxFIFO = 0x20,

  /*0 as low*/
  spiMaster_controlStat_csPolarityActiveHigh = 0x40,
  
  /*0 as inactive*/
  spiMaster_controlStat_transferActive = 0x80,

  /*0 as inactive*/
  spiMaster_controlStat_dmaActive = 0x100,

  /*0 as dont gen*/
  spiMaster_controlStat_genIntOnDone = 0x200,

  /*0 as dont gen*/
  spiMaster_controlStat_genIntOnRXR = 0x400,

  /*0 as dont do it automaticly*/
  spiMaster_controlStat_autoDeassertCSAtEndOfDMA = 0x800,
  spiMaster_controlStat_renReadEnable = 0x1000,
  spiMaster_controlStat_lenLOSSIEnable = 0x2000,
  spiMaster_controlStat_transferDone = 0x10000,
  spiMaster_controlStat_rdxRxFIFOData = 0x20000,
  spiMaster_controlStat_tdxTxFIFOData = 0x40000,
  spiMaster_controlStat_rdxRxFIFONeedsReading = 0x80000,
  spiMaster_controlStat_rdxRxFIFOFull = 0x100000,

  /*0 on active low*/
  spiMaster_controlStat_cs0PolarityActiveHigh = 0x200000,
  spiMaster_controlStat_cs1PolarityActiveHigh = 0x400000,
  spiMaster_controlStat_cs2PolarityActiveHigh = 0x800000,

  spiMaster_controlStat_enableDMAInLOSSI = 0x1000000,

  /*enableDMAInLOSSI must be set, enable 32bit word, 0 as 1 byte (8bits)*/
  spiMaster_controlStat_enableLongDataWordInLOSSI = 0x2000000,

  spiMaster_controlStat_reset = 0x41000
};

enum rpi_hal_spi_master_dmaDreqCtl {
  /*8 bits*/
  spiMaster_dmaDreqCtl_dmaWriteReqThrshld = 0x1,
  /*8 bits*/
  spiMaster_dmaDreqCtl_dmaWritePanicThrshld = 0x100,
  /*8 bits*/
  spiMaster_dmaDreqCtl_dmaReadReqThrshld = 0x10000,
  /*8 bits*/
  spiMaster_dmaDreqCtl_dmaReadPanicThrshld = 0x1000000,

  spiMaster_dmaDreqCtl_reset = 0x30201020
};

#define spiMaster       (*(rpi_hal_spi_master_t*)RPI_HAL_SPI0_BASE)
#define spiSlave        (*(rpi_hal_spi_slave_t*)RPI_HAL_BSC_SPI_SLAVE_BASE)

#endif
