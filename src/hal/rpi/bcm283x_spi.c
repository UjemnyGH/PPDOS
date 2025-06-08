#include "bcm283x_spi.h"

void rpi_hal_spi_init() {
  spi.controlStat = spi_controlStat_reset;
  
  for(int i = 0; i < 1000; i++);

  spi.controlStat = spi_controlStat_clearTxFIFO | spi_controlStat_clearRxFIFO;

  spi.clockDiv = 256; /* 4MHz as 1000MHz / 4MHz = 250*/

  spi.dataLen = 8;

  spi.controlStat &= ~spi_controlStat_chipSelectMask;
  spi.controlStat &= ~spi_controlStat_csPolarityActiveHighMask;

  spi.controlStat |= spi_controlStat_transferActive;
}

rpi_hal_uint8_t rpi_hal_spi_transferByte(const rpi_hal_uint8_t data) {
  while((spi.controlStat & spi_controlStat_tdxTxFIFOData) == 0);

  spi.fifoData = data;

  while((spi.controlStat & spi_controlStat_rdxRxFIFOData) == 0);

  return (rpi_hal_uint8_t)(spi.fifoData & 0xFF);
}

void rpi_hal_spi_transfer(const rpi_hal_uint8_t* pSrc, rpi_hal_uint8_t* pDst, const rpi_hal_uint32_t len) {
  for(rpi_hal_uint32_t i = 0; i < len; i++) {
    rpi_hal_uint8_t data = pSrc ? pSrc[i] : 0xFF;
    rpi_hal_uint8_t recv = rpi_hal_spi_transferByte(data);

    if(pDst)
      pDst[i] = recv;
  }
}

void rpi_hal_spi_deinit() {

}
