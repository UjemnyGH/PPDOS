#ifndef _PPDOS_HAL_BCM283X_DMA_
#define _PPDOS_HAL_BCM283X_DMA_

#include "bcm283x_regs.h"

typedef struct rpi_hal_dma_s {
  rpi_hal_io32_t controlStat;       /* dma_controlStat_X flags */
  rpi_hal_io32_t ctlBlockAddr;

  rpi_hal_io32_t cbTransferInfo;    /* dma_transferStat_X flags */
  rpi_hal_io32_t cbSrcAddr;
  rpi_hal_io32_t cbDstAddr;
  rpi_hal_io32_t cbTransferLen;     /* dma_transferLen_x/yLengthMask (yLengthMask only for dma 0-6) */
  rpi_hal_io32_t cb2DStride;        /* dma_2DStride_src/dstStrideMask (only for dma 0-6) */
  rpi_hal_io32_t cbNextAddr;

  rpi_hal_io32_t debug;
} __attribute__((packed)) rpi_hal_dma_t;

typedef struct {
  rpi_hal_uint32_t transferInfo;    /* dma_transferStat_X flags */
  rpi_hal_uint32_t srcAddr;
  rpi_hal_uint32_t dstAddr;
  rpi_hal_uint32_t transferLen;     /* dma_transferLen_x/yLengthMask (yLengthMask only for dma 0-6) */
  rpi_hal_uint32_t stride2D;        /* dma_2DStride_src/dstStrideMask (only for dma 0-6) */
  rpi_hal_uint32_t nextAddr;
  rpi_hal_uint32_t RESERVED0[2];
} __attribute__((packed)) rpi_hal_dma_control_block_t;

typedef struct rpi_hal_dma_status_s {
  rpi_hal_io32_t intStatus;
  rpi_hal_io32_t enable;
} __attribute__((packed)) rpi_hal_dma_status_t;

enum rpi_hal_dma_controlStat {
  dma_controlStat_activateDMA             = 0x00000001,
  dma_controlStat_clearTransferComplete   = 0x00000002,
  dma_controlStat_clearIntStatus          = 0x00000004,
  dma_controlStat_dataReqState            = 0x00000008,
  dma_controlStat_pausedState             = 0x00000010,
  dma_controlStat_dataReqPausedStatus     = 0x00000020,
  dma_controlStat_dmaWaitingForLastWrite  = 0x00000040,
  dma_controlStat_error                   = 0x00000100,

  dma_controlStat_axiPriorityMask         = 0x000F0000,
  dma_controlStat_axiPanicPriorityMask    = 0x00F00000,

  dma_controlStat_waitForLastWrite        = 0x10000000,
  dma_controlStat_disableDebugPauseSignal = 0x20000000,
  dma_controlStat_abort                   = 0x40000000,
  dma_controlStat_channelReset            = 0x80000000,

  dma_controlStat_reset                   = 0x00000000
};

enum rpi_hal_dma_transferInfo {
  dma_transferInfo_intEnable              = 0x00000001,
  dma_transferInfo_2DMode                 = 0x00000002,   /* Only for dma 0-6 */
  dma_transferInfo_waitForWriteResponse   = 0x00000008,

  dma_transferInfo_dstAddrIncrement       = 0x00000010,
  dma_transferInfo_dstTransferWide        = 0x00000020,
  dma_transferInfo_ctlDstWriteWithDataReq = 0x00000040,
  dma_transferInfo_ignoreWrites           = 0x00000080,

  dma_transferInfo_srcAddrIncrement       = 0x00000100,
  dma_transferInfo_srcTransferWide        = 0x00000200,
  dma_transferInfo_ctlSrcReadWithDataReq  = 0x00000400,
  dma_transferInfo_ignoreReads            = 0x00000800,

  dma_transferInfo_burstTransferLenMask   = 0x0000F000,
  
  dma_transferInfo_pcmI2STransmitMapping  = 0x00020000,
  dma_transferInfo_pcmI2SReceiveMapping   = 0x00030000,
  dma_transferInfo_spi0TransmitMapping    = 0x00060000,
  dma_transferInfo_spi0ReceiveMapping     = 0x00070000,
  dma_transferInfo_spi1TransmitMapping    = 0x00080000,
  dma_transferInfo_spi1ReceiveMapping     = 0x00090000,
  dma_transferInfo_spi2TransmitMapping    = 0x000A0000,
  dma_transferInfo_spi2ReceiveMapping     = 0x000B0000,

  dma_transferInfo_peripheralMappingMask  = 0x001F0000,

  dma_transferInfo_waitCycleMask          = 0x03E00000,
  
  dma_transferInfo_noWideBurst            = 0x04000000,   /* Only for dma 0-6 */

  dma_transferInfo_reset                  = 0x00000000
};

enum rpi_hal_dma_transferLen {
  dma_transferLen_xLengthMask             = 0x0000FFFF,
  dma_transferLen_yLengthMask             = 0x3FFF0000,   /* Only for dma 0-6 */

  dma_transferLen_reset                   = 0x00000000
};

enum rpi_hal_dma_2DStride {
  dma_2DStride_srcStrideMask              = 0x0000FFFF,   /* Only for dma 0-6 */
  dma_2DStride_dstStrideMask              = 0xFFFF0000,   /* Only for dma 0-6 */

  dma_2DStride_reset                      = 0x00000000
};

enum rpi_hal_dma_debug {
  dma_debug_readLastNotSetError           = 0x00000001,
  dma_debug_fifoError                     = 0x00000002,
  dma_debug_slaveReadResponseError        = 0x00000004,

  dma_debug_outstandingWritesCounterMask  = 0x000000F0,
  dma_debug_dmaIdMask                     = 0x0000FF00,
  dma_debug_dmaStateMachineStateMask      = 0x01FF0000,
  dma_debug_dmaVersionMask                = 0x0E000000,

  dma_debug_dmaLite                       = 0x10000000,

  dma_debug_reset                         = 0x06000000,   /* Only for dma 0-6 */

  dma_debug_reset2                        = 0x16000000    /* Only for dma 7-14 */
};

/* Direct Memory Access registers accessed by id, possible values are between 0-14 */
#define dma(id)             (*(rpi_hal_dma_t*)((unsigned long long)(RPI_HAL_DMA_BASE + (0x100 * id))))
#define dmaStatus           (*(rpi_hal_dma_status_t*)(RPI_HAL_DMA_BASE + 0x0FE0))

void rpi_hal_dma_init(rpi_hal_uint8_t dmaChannel);

void rpi_hal_dma_setupTransfer(rpi_hal_uint8_t dmaChannel, const void* pSrc, void *pDst, rpi_hal_uint32_t length);

void rpi_hal_dma_transferInfo(rpi_hal_uint8_t dmaChannel, const enum rpi_hal_dma_transferInfo transferInfo);

void rpi_hal_dma_activateChannel(rpi_hal_uint8_t dmaChannel);

rpi_hal_uint32_t rpi_hal_dma_transferComplete(rpi_hal_uint8_t dmaChannel);

void rpi_hal_dma_deinit(rpi_hal_uint8_t dmaChannel);

#endif
