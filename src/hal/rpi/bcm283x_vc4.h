#ifndef _PPDOS_HAL_BCM283X_VC4_
#define _PPDOS_HAL_BCM283X_VC4_

#include "bcm283x_regs.h"

typedef struct rpi_hal_vc4_s {
  rpi_hal_io32_t identification[3]; /*0x00 - 0x08*/
  rpi_hal_io32_t scratch[4];        /*0xC - 0x1C*/

  rpi_hal_io32_t l2CacheCtl;        /*0x20*/
  rpi_hal_io32_t sliceCacheCtl;     /*0x24*/

  rpi_hal_uint32_t RESERVED0[2];    /*0x28 - 0x2C*/
  
  rpi_hal_io32_t intControl;        /*0x30*/
  rpi_hal_io32_t intEnable;         /*0x34*/
  rpi_hal_io32_t intDisable;        /*0x38*/

  rpi_hal_uint32_t RESERVED1[0x31];   /*0x3C-0xFC*/

  rpi_hal_io32_t ctlListStat[2];      /*0x100 - 0x104*/
  rpi_hal_io32_t ctlListEnd[2];       /*0x108 - 0x10C*/
  rpi_hal_io32_t ctlListCurrentAddr[2]; /*0x110 - 0x114*/
  rpi_hal_io32_t ctlListReturnAddr[2];
  rpi_hal_io32_t ctlListLength[2];
  rpi_hal_io32_t ctlListPrimitiveCounter[2];
  
  rpi_hal_io32_t 

  rpi_hal_uint32_t RESERVED2[36];

  rpi_hal_io32_t binningFramebufferCfg;
  rpi_hal_io32_t renderingFramebufferCfg;
  rpi_hal_io32_t binningPolyCountAddr;
  rpi_hal_io32_t binningPolyCountSize;
  rpi_hal_io32_t binningTileMemAddr;
  rpi_hal_io32_t binningExecCfg;

  rpi_hal_uint32_t RESERVED3[9];

  rpi_hal_io32_t shaderQueueReserved[2];
  rpi_hal_io32_t shaderQueueCtl;
  rpi_hal_io32_t shaderRequestPC;
  rpi_hal_io32_t shaderRequestAddr;
  rpi_hal_io32_t shaderRequestLength;
  rpi_hal_io32_t shaderRequesrCtlStat;

  rpi_hal_uint32_t RESERVED4;

  rpi_hal_io32_t vertexPipelineCtl;
  rpi_hal_io32_t vertexPipelineMemoryBase;

  rpi_hal_uint32_t RESERVED5[54];

  rpi_hal_io32_t pipelineCtlStat;
  rpi_hal_io32_t binningFIFOCfg2;
  rpi_hal_io32_t renderingFIFOCfg2;

  rpi_hal_uint32_t RESERVED6[125];

  rpi_hal_io32_t vpmAddr;
  rpi_hal_io32_t vpmDataLoad;
  rpi_hal_io32_t vpmDataLoadLength;

  rpi_hal_uint32_t RESERVED7[125];

  struct {
    rpi_hal_io32_t count;
    rpi_hal_io32_t mapping;
  } performanceCounter[16];
} __attribute__((packed)) rpi_hal_vc4_t;

/* Apply for intControl, intEnable, intDisable */
enum rpi_hal_vc4_interrupt {
  vc4_interrupt_binningFIFODone   = 0x1,
  vc4_interrupt_renderingFIFODone = 0x2,
  vc4_interrupt_tileFIFODone      = 0x4,

  vc4_interrupt_fifoDoneMask      = 0x7
};

enum rpi_hal_vc4_ctlListStat {
  vc4_ctlListStat_active = 0x1,
  vc4_ctlListStat_endReached = 0x2,
  vc4_ctlListStat_stalled = 0x4,
  vc4_ctlListStat_exception = 0x8,

  vc4_ctlListStat_priorityMask = 0x30,
  /* As there is no docs for VC4 it is needed */
  vc4_ctlListStat_priorityShift = 4,

  vc4_ctlListStat_flush = 0x40
};

#define vc4       (*(rpi_hal_vc4_t*)RPI_HAL_VC4_BASE)

#endif
