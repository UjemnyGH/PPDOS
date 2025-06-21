#include "bcm283x_dma.h"

void rpi_hal_dma_init(rpi_hal_uint8_t dmaChannel) {
  if(dmaChannel > 14)
    dmaChannel = 14;

  dmaStatus.enable |= (1 << dmaChannel);
  dma(dmaChannel).controlStat = dma_controlStat_reset;
}

void rpi_hal_dma_setupTransfer(rpi_hal_uint8_t dmaChannel, const void* pSrc, void *pDst, rpi_hal_uint32_t length) {
  if(dmaChannel > 14)
    dmaChannel = 14;

  if(length > dma_transferLen_xLengthMask)
    dmaChannel = 6;

  dma(dmaChannel).cbDstAddr = (rpi_hal_uint32_t)((unsigned long long)pDst);
  dma(dmaChannel).cbSrcAddr = (rpi_hal_uint32_t)((unsigned long long)pSrc);
  dma(dmaChannel).cbTransferLen = length;
}

void rpi_hal_dma_transferInfo(rpi_hal_uint8_t dmaChannel, const enum rpi_hal_dma_transferInfo transferInfo) {
  if(dmaChannel > 14)
    dmaChannel = 14;

  dma(dmaChannel).cbTransferInfo = transferInfo | dma_transferInfo_intEnable;
}

void rpi_hal_dma_activateChannel(rpi_hal_uint8_t dmaChannel) {
  if(dmaChannel > 14)
    dmaChannel = 14;

  dma(dmaChannel).controlStat |= dma_controlStat_activateDMA;
}

rpi_hal_uint32_t rpi_hal_dma_transferComplete(rpi_hal_uint8_t dmaChannel) {
  if(dmaChannel > 14)
    dmaChannel = 14;

  return !!(dmaStatus.intStatus & (1 << dmaChannel));
}

void rpi_hal_dma_deinit(rpi_hal_uint8_t dmaChannel) {
  if(dmaChannel > 14)
    dmaChannel = 14;

  dma(dmaChannel).controlStat &= ~dma_controlStat_activateDMA;
  dma(dmaChannel).controlStat = dma_controlStat_clearIntStatus; 
}
