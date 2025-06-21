#include "bcm283x_spi.h"
#include "bcm283x_dma.h"

void rpi_hal_spi_init(rpi_hal_uint32_t clockDiv) {
  spi.controlStat = spi_controlStat_reset;
  
  for(int i = 0; i < 1000; i++);

  spi.controlStat = spi_controlStat_clearTxFIFO | spi_controlStat_clearRxFIFO;

  spi.clockDiv = clockDiv;

  spi.dataLen = 8;

  spi.controlStat &= ~spi_controlStat_chipSelectMask;
  spi.controlStat &= ~spi_controlStat_csPolarityActiveHighMask;

  spi.controlStat |= spi_controlStat_transferActive;
}

void rpi_hal_spi_chipSelect(rpi_hal_uint8_t cs) {
  if(cs > 2)
    cs = 2;

  spi.controlStat &= ~spi_controlStat_chipSelectMask;
  spi.controlStat |= spi_controlStat_chipSelect0 + cs;
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

void rpi_hal_spi_dmaTransfer(rpi_hal_uint8_t dmaChannel, const rpi_hal_uint8_t* pSrc, rpi_hal_uint8_t* pDst, const rpi_hal_uint32_t len) {
  spi.controlStat &= ~spi_controlStat_transferActive;

  if(pSrc) {
    rpi_hal_dma_init(dmaChannel);
  
    /* Transmit */
    rpi_hal_dma_setupTransfer(dmaChannel, pSrc, (rpi_hal_uint32_t*)&spi.fifoData, len);

    rpi_hal_dma_transferInfo(dmaChannel,  
      dma_transferInfo_srcAddrIncrement | 
      dma_transferInfo_waitForWriteResponse | 
      dma_transferInfo_ctlDstWriteWithDataReq | 
      dma_transferInfo_spi0TransmitMapping);
  }
  
  if(pDst) {
    rpi_hal_dma_init(dmaChannel + 1);

    /* Receive */
    rpi_hal_dma_setupTransfer(dmaChannel + 1, (rpi_hal_uint32_t*)&spi.fifoData, pDst, len);

    rpi_hal_dma_transferInfo(dmaChannel + 1,
      dma_transferInfo_dstAddrIncrement |
      dma_transferInfo_ctlSrcReadWithDataReq |
      dma_transferInfo_spi0ReceiveMapping);
  }

  /* Enable SPI for transfer in DMA*/
  spi.controlStat |= spi_controlStat_enableDMAInLOSSI | spi_controlStat_transferActive;

  /* Activate DMA channels */
  if(pSrc)
    rpi_hal_dma_activateChannel(dmaChannel);
  
  if(pDst)
    rpi_hal_dma_activateChannel(dmaChannel + 1);

  rpi_hal_uint32_t timeout = 1000000;
  /* Wait for DMA channels to cxomplete transfer */
  while((pSrc ? !rpi_hal_dma_transferComplete(dmaChannel) : 0 || pDst ? !rpi_hal_dma_transferComplete(dmaChannel + 1) : 0) && timeout--)
    asm volatile ("nop");

  if(pSrc)
    rpi_hal_dma_deinit(dmaChannel);
  
  if(pDst)
    rpi_hal_dma_deinit(dmaChannel + 1);
}

void rpi_hal_spi_deinit() {
  spi.controlStat &= ~(spi_controlStat_transferActive | spi_controlStat_enableDMAInLOSSI);
  spi.controlStat |= spi_controlStat_reset;
}
