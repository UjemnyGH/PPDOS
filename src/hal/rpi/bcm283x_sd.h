#ifndef _PPDOS_HAL_BCM283X_SD_
#define _PPDOS_HAL_BCM283X_SD_

#include "bcm283x_regs.h"

/* Yet to be implemented */
typedef struct rpi_hal_sd_host_s {
  rpi_hal_io32_t command;
  rpi_hal_io32_t argument;
  rpi_hal_io32_t timeout;
  rpi_hal_io32_t clockDivider;
  rpi_hal_io32_t response[4];
  rpi_hal_io32_t hostStatus;
  rpi_hal_uint32_t RESERVED0[4];
  rpi_hal_io32_t powerCtl;
  rpi_hal_io32_t emergencyDebugMode;
  rpi_hal_io32_t hostConfig;
  rpi_hal_io32_t hostByteCount;
  rpi_hal_io32_t data;
  rpi_hal_uint32_t RESERVED1[4];
  rpi_hal_io32_t hostBlockCount;
} __attribute__((packed)) rpi_hal_sd_host_t;

typedef struct rpi_hal_sd_hci_s {
  rpi_hal_io32_t argument2;       /*0x0, also dma address and 32 bit block count */
  rpi_hal_io16_t blockSize;       /*0x4*/
  rpi_hal_io16_t blockCount;      /*0x6*/
  rpi_hal_io32_t argument;        /*0x8*/
  rpi_hal_io16_t transferMode;    /*0xC*/
  rpi_hal_io16_t command;         /*0xE*/
  rpi_hal_io32_t response[4];     /*0x10*/
  rpi_hal_io32_t bufferDataPort;  /*0x20*/
  rpi_hal_io32_t presentState;    /*0x24*/
  rpi_hal_io8_t  hostCtl;         /*0x28*/
  rpi_hal_io8_t  powerCtl;        /*0x29*/
  rpi_hal_io8_t  blockGapCtl;     /*0x2A*/
  rpi_hal_io8_t  wakeUpCtl;       /*0x2B*/
  rpi_hal_io16_t clockCtl;        /*0x2C*/
  rpi_hal_io8_t  timeoutCtl;      /*0x2E*/
  rpi_hal_io8_t  softwareReset;   /*0x2F*/
  rpi_hal_io32_t intStat;         /*0x30*/
  rpi_hal_io32_t intEnable;       /*0x34*/
  rpi_hal_io32_t signalEnable;    /*0x38*/
  rpi_hal_io16_t autoCommandStat; /*0x3C*/
  rpi_hal_io16_t hostCtl2;        /*0x3E*/
  rpi_hal_io32_t capabilities[2]; /*0x40*/
  rpi_hal_io32_t maxCurrent;      /*0x48*/
  rpi_hal_uint32_t RESERVED0;     /*0x4C*/
  rpi_hal_io16_t setACMD12Err;    /*0x50*/
  rpi_hal_io16_t setIntErr;       /*0x52*/
  rpi_hal_io32_t admaErr;         /*0x54*/
  rpi_hal_io32_t admaAddr;        /*0x58*/
  rpi_hal_io32_t admaAddrHigh;    /*0x5C*/
  rpi_hal_uint32_t RESERVED1;     /*0x60*/
  rpi_hal_uint32_t RESERVED2[38]; /*0x64-0xF0*/
  rpi_hal_io16_t slotIntStat;     /*0xFC*/
  rpi_hal_io16_t hostVersion;     /*0xFE*/
} __attribute__((packed)) rpi_hal_sd_hci_t;

enum rpi_hal_sd_hci_transferMode {
  sdhci_transferMode_dma                = 0x01,
  sdhci_transferMode_blockCountEnable   = 0x02,
  sdhci_transferMode_autoCMD12StopTrans = 0x04,
  sdhci_transferMode_multiBlock         = 0x10,
  sdhci_transferMode_write              = 0x20
};

enum rpi_hal_sd_hci_command {
  sdhci_command_responseNone          = 0x0000,
  sdhci_command_responseLong          = 0x0100,
  sdhci_command_responseShort         = 0x0200,
  sdhci_command_responseShortBusy     = 0x0300,
  
  sdhci_command_responseMask          = 0x0300,

  sdhci_command_crc                   = 0x0800,
  sdhci_command_index                 = 0x1000,
  sdhci_command_data                  = 0x2000,
  sdhci_command_abortCommand          = 0xC000
};

enum rpi_hal_sd_hci_presentState {
  sdhci_presentState_commandInhibit   = 0x00000001,
  sdhci_presentState_dataInhibit      = 0x00000002,
  sdhci_presentState_writting         = 0x00000100,
  sdhci_presentState_reading          = 0x00000200,
  sdhci_presentState_spaceAvailable   = 0x00000400,
  sdhci_presentState_dataAvailable    = 0x00000800,
  sdhci_presentState_writeReady       = 0x00010000,
  sdhci_presentState_readReady        = 0x00020000,
  sdhci_presentState_cdLevel          = 0x00040000,
  sdhci_presentState_writeProtect     = 0x00080000,
  
  sdhci_presentState_dataLevelMask    = 0x00F00000,
  sdhci_presentState_data0LevelMask   = 0x00100000,

  sdhci_presentState_commandLevel     = 0x01000000
};

enum rpi_hal_sd_hci_hostCtl {
  sdhci_hostCtl_led           = 0x01,
  sdhci_hostCtl_4bitBus       = 0x02,
  sdhci_hostCtl_highSpeed     = 0x04,
  
  sdhci_hostCtl_sdma          = 0x00,
  sdhci_hostCtl_adma1         = 0x08,
  sdhci_hostCtl_adma32        = 0x10,
  sdhci_hostCtl_adma64        = 0x18,
  sdhci_hostCtl_adma3         = 0x18,

  sdhci_hostCtl_dmaMask       = 0x18,

  sdhci_hostCtl_8bitBus       = 0x20,
  sdhci_hostCtl_cdTestInsert  = 0x40,
  sdhci_hostCtl_cdTestEnable  = 0x80
};

enum rpi_hal_sd_hci_powerCtl {
  sdhci_powerCtl_on  = 0x01,
  sdhci_powerCtl_180 = 0x0A,
  sdhci_powerCtl_300 = 0x0C,
  sdhci_powerCtl_330 = 0x0E
};

enum rpi_hal_sd_hci_wakeUpCtl {
  sdhci_wakeUpCtl_onInterrupt = 0x01,
  sdhci_wakeUpCtl_onInsert    = 0x02,
  sdhci_wakeUpCtl_onRemove    = 0x04
};

enum rpi_hal_sd_hci_clockCtl {
  sdhci_clockCtl_dividerMask      = 0x00FF,
  sdhci_clockCtl_dividerHighMask  = 0x0300,

  sdhci_clockCtl_interruptEnable  = 0x0001,
  sdhci_clockCtl_interruptStable  = 0x0002,
  sdhci_clockCtl_cardEnable       = 0x0004,
  sdhci_clockCtl_pllEnable        = 0x0008,
  sdhci_clockCtl_programableMode  = 0x0020
};

enum rpi_hal_sd_hci_softwareReset {
  sdhci_softwareReset_all     = 0x01,
  sdhci_softwareReset_command = 0x02,
  sdhci_softwareReset_data    = 0x04
};

enum rpi_hal_sd_hci_intStat {
  sdhci_intStat_response            = 0x00000001,
  sdhci_intStat_dataEnd             = 0x00000002,
  sdhci_intStat_blockGap            = 0x00000004,
  sdhci_intStat_dmaEnd              = 0x00000008,
  sdhci_intStat_spaceAvailable      = 0x00000010,
  sdhci_intStat_dataAvailable       = 0x00000020,
  sdhci_intStat_cardInsert          = 0x00000040,
  sdhci_intStat_cardRemove          = 0x00000080,
  sdhci_intStat_cardInterrupt       = 0x00000100,
  sdhci_intStat_retune              = 0x00001000,
  sdhci_intStat_cqe                 = 0x00004000,
  sdhci_intStat_error               = 0x00008000,
  sdhci_intStat_timeout             = 0x00010000,
  sdhci_intStat_crc                 = 0x00020000,
  sdhci_intStat_endBit              = 0x00040000,
  sdhci_intStat_index               = 0x00080000,
  sdhci_intStat_dataTimeout         = 0x00100000,
  sdhci_intStat_dataCrc             = 0x00200000,
  sdhci_intStat_dataEndBit          = 0x00400000,
  sdhci_intStat_busPower            = 0x00800000,
  sdhci_intStat_autoCommandError    = 0x01000000,
  sdhci_intStat_admaError           = 0x02000000,

  sdhci_intStat_normalMask          = 0x00007FFF,
  sdhci_intStat_errorMask           = 0xFFFF8000,
  sdhci_intStat_commandMask         = 0x010F0001,
  sdhci_intStat_dataMask            = 0x0270003E,
  sdhci_intStat_cqeErrorMask        = 0x02FF0000,
  sdhci_intStat_cqeMask             = 0x02FF4000,
  sdhci_intStat_allMask             = 0xFFFFFFFF
};

enum rpi_hal_sd_hci_autoCommandStat {
  sdhci_autoCommandStat_timeout = 0x02,
  sdhci_autoCommandStat_crc     = 0x04,
  sdhci_autoCommandStat_endBit  = 0x08,
  sdhci_autoCommandStat_index   = 0x10
};

enum rpi_hal_sd_hci_hostCtl2 {
  sdhci_hostCtl2_uhsMask          = 0x0007,
  
  sdhci_hostCtl2_uhsSdr12         = 0x0000,
  sdhci_hostCtl2_uhsSdr25         = 0x0001,
  sdhci_hostCtl2_uhsSdr50         = 0x0002,
  sdhci_hostCtl2_uhsSdr104        = 0x0003,
  sdhci_hostCtl2_uhsDdr50         = 0x0004,
  sdhci_hostCtl2_hs400            = 0x0005,

  sdhci_hostCtl2_vdd180           = 0x0008,
  
  sdhci_hostCtl2_driverTypeMask   = 0x0030,
  sdhci_hostCtl2_driverTypeB      = 0x0000,
  sdhci_hostCtl2_driverTypeA      = 0x0010,
  sdhci_hostCtl2_driverTypeC      = 0x0020,
  sdhci_hostCtl2_driverTypeD      = 0x0030,

  sdhci_hostCtl2_execTuning       = 0x0040,
  sdhci_hostCtl2_tunedClock       = 0x0080,
  sdhci_hostCtl2_cmd23Enable      = 0x0800,
  sdhci_hostCtl2_v4Mode           = 0x1000,
  sdhci_hostCtl2_64bitAddress     = 0x2000,
  sdhci_hostCtl2_presetValEnable  = 0x8000
};

enum rpi_hal_sd_hci_capabilities0 {
  sdhci_capabilities0_timeoutClockMask    = 0x0000003F,
  
  sdhci_capabilities0_timeoutClockUnit    = 0x00000080,

  sdhci_capabilities0_clockBaseMask       = 0x00003F00,
  sdhci_capabilities0_clockV3BaseMask     = 0x0000FF00,
  sdhci_capabilities0_maxBlockMask        = 0x00030000,

  sdhci_capabilities0_8bit                = 0x00040000,
  sdhci_capabilities0_adma2               = 0x00080000,
  sdhci_capabilities0_adma1               = 0x00100000,
  sdhci_capabilities0_highSpeed           = 0x00200000,
  sdhci_capabilities0_sdma                = 0x00400000,
  sdhci_capabilities0_suspend             = 0x00800000,
  sdhci_capabilities0_vdd330              = 0x01000000,
  sdhci_capabilities0_vdd300              = 0x02000000,
  sdhci_capabilities0_vdd180              = 0x04000000,
  sdhci_capabilities0_64bitV4             = 0x08000000,
  sdhci_capabilities0_64bit               = 0x10000000,
  sdhci_capabilities0_asyncInterrupt      = 0x20000000,
  sdhci_capabilities0_slotTypeEmbedded    = 0x40000000
};

enum rpi_hal_sd_hci_capabilities1 {
  sdhci_capabilities1_sdr50                   = 0x00000001,
  sdhci_capabilities1_sdr104                  = 0x00000002,
  sdhci_capabilities1_ddr50                   = 0x00000004,
  sdhci_capabilities1_driverTypeA             = 0x00000010,
  sdhci_capabilities1_driverTypeC             = 0x00000020,
  sdhci_capabilities1_driverTypeD             = 0x00000040,
  sdhci_capabilities1_retuningTimerCountMask  = 0x00000F00,
  sdhci_capabilities1_useSdr50Tuning          = 0x00002000,
  sdhci_capabilities1_retuningModeMask        = 0x0000C000,
  sdhci_capabilities1_clockMultiplierMask     = 0x00FF0000,
  sdhci_capabilities1_retimerEnable           = 0x01000000,
  sdhci_capabilities1_adma3                   = 0x08000000,
  sdhci_capabilities1_hs400                   = 0x80000000
};

enum rpi_hal_sd_hci_maxCurrent {
  sdhci_maxCurrent_limit    = 0x000000FF,
  sdhci_maxCurrent_330mask  = 0x000000FF,
  sdhci_maxCurrent_300mask  = 0x0000FF00,
  sdhci_maxCurrent_180mask  = 0x00FF0000,

  sdhci_maxCurrent_multiplier = 4
};

enum rpi_hal_sd_hci_hostVersion {
  sdhci_hostVersion_vendorMask    = 0xFF00,
  sdhci_hostVersion_specMask      = 0x00FF,
  sdhci_hostVersion_spec100       = 0x0,
  sdhci_hostVersion_spec200       = 0x1,
  sdhci_hostVersion_spec300       = 0x2,
  sdhci_hostVersion_spec400       = 0x3,
  sdhci_hostVersion_spec410       = 0x4,
  sdhci_hostVersion_spec420       = 0x5
};

enum rpi_hal_eMMC_commands {
  /* General purpose commands */

  eMMC_command_goIdleState                    = 0,    /*Arg = 0; software reset*/
  eMMC_command_sendOpCond_arg                 = 1,    /*Arg = voltage range (MMC only, SD uses ACMD41)*/
  eMMC_command_allSendCardID                  = 2,    /*Arg = 0; request CID from all cards*/
  eMMC_command_sendRelativeCardAddr           = 3,    /*Arg = 0 or rca; assing rca (default SD RCA = 0x1)*/
  eMMC_command_setDriverStrength_arg          = 4,    /*Arg = 16bit DSR << 16*/
  eMMC_command_switchFunction_arg             = 6,    /*Arg = func specific value; SD: select bus speed*/
  eMMC_command_select_arg                     = 7,    /*Arg = RCA << 16; select or deselect card*/
  eMMC_command_sendIfCond_arg                 = 8,    /*Arg = 0x1AA; checks voltage range and pattern (SD 2.0+)*/
  eMMC_command_sendCSD_arg                    = 9,    /*Arg = RCA << 16; get CSD reg*/
  eMMC_command_sendCardID_arg                 = 10,   /*Arg = RCA << 16; get Card ID reg*/
  eMMC_command_voltageSwitch180               = 11,   /*Arg = 0; set voltage to 1.8V for I/O*/
  eMMC_command_stopTransmission               = 12,   /*Arg = 0; end multiblock transfer*/
  eMMC_command_sendStatus_arg                 = 13,   /*Arg = RCA << 16; ask sd for status*/
  eMMC_command_setBlockLength_arg             = 16,   /*Arg = block size (eg. 512); set block length (SDHC/SDXC ignore)*/
  eMMC_command_readSingleBlock_arg            = 17,   /*Arg = block address; read single block*/
  eMMC_command_readMultipleBlocks_arg         = 18,   /*Arg = block address; read multiple blocks*/
  eMMC_command_writeSingleBlock_arg           = 24,   /*Arg = block address; write single block*/
  eMMC_command_writeMultipleBlocks_arg        = 25,   /*Arg = block address; write multiple blocks*/
  eMMC_command_programCSD                     = 27,   /*Arg = 0; modify programable bits in CSD*/
  eMMC_command_setWriteProtection_arg         = 28,   /*Arg = block address; set write protection*/
  eMMC_command_clearWriteProtection_arg       = 29,   /*Arg = block address; clear write protection*/
  eMMC_command_sendWriteProtectionStatus_arg  = 30,   /*Arg = block address; check if block is write protected*/
  eMMC_command_eraseBlockStart_arg            = 32,   /*Arg = start block address; start of erase range*/
  eMMC_command_eraseBlockEnd_arg              = 33,   /*Arg = end block address; end of erase range*/
  eMMC_command_erase                          = 38,   /*Arg = 0; erase selected between eraseBlockStart_arg and eraseBlockEnd_arg range*/
  eMMC_command_nextCommandAppSpecific_arg     = 55,   /*Arg = RCA << 16 or 0 if idle; must be used before any command_app (ACMD)*/
  eMMC_command_nextCommandGeneralPurpose_arg  = 56,   /*Arg = something; general purpose commands*/

  /* Application specific commands */

  eMMC_command_app_setBusWidth_arg            = 6,    /*Arg = 0 - 1bit, 2 - 4bit; set bus width*/
  eMMC_command_app_sdStatus                   = 13,   /*Arg = 0; get sd status*/
  eMMC_command_app_sendWriteBlocksNumber      = 22,   /*Arg = 0; sends info about how many blocks will be written*/
  eMMC_command_app_preeraseBlocksForWrite_arg = 23,   /*Arg = count; pre erase blocks for multiple write*/
  eMMC_command_app_sendHostCapacitySupport_arg = 41,  /*Arg = OCR + HCS + (S18R if 1.8V); SD card initialization (must poll)*/
  eMMC_command_app_pullUpResistorOnCD_DAT3_arg = 42,  /*Arg = 0 - connect pullup; Control DAT3/CD*/
  eMMC_command_app_getSDConfigRegister        = 51    /*Arg = 0; read sd config register (SCR)*/
};

#define sdhci       (*(rpi_hal_sd_hci_t*)RPI_HAL_SD_CTL_BASE)

rpi_hal_uint32_t rpi_hal_sd_hci_getMasterRCA();

rpi_hal_uint32_t rpi_hal_sd_hci_waitForCommandReady();

rpi_hal_uint32_t rpi_hal_sd_hci_waitForDataReady();

void rpi_hal_sd_hci_clearInterrupts();

rpi_hal_uint32_t rpi_hal_sd_hci_sendCommand(const rpi_hal_uint32_t command, const rpi_hal_uint32_t arg);

rpi_hal_uint32_t rpi_hal_sd_hci_readBlock(const rpi_hal_uint32_t logicalBlockAddr, void* pDst);

rpi_hal_uint32_t rpi_hal_sd_hci_writeBlock(const rpi_hal_uint32_t logicalBlockAddr, const void* pSrc);

rpi_hal_uint32_t rpi_hal_sd_hci_readMultipleBlocks(const rpi_hal_uint32_t logicalBlockAddr, const rpi_hal_uint32_t count, void* pDst);

rpi_hal_uint32_t rpi_hal_sd_hci_writeMultipleBlocks(const rpi_hal_uint32_t logicalBlockAddr, const rpi_hal_uint32_t count, const void* pSrc);

rpi_hal_uint32_t rpi_hal_sd_hci_initialize();

rpi_hal_uint32_t rpi_hal_sd_hci_isHighCapacity();

rpi_hal_uint32_t rpi_hal_sd_hci_readCardSpecificData(const rpi_hal_uint32_t rca);

rpi_hal_uint32_t rpi_hal_sd_hci_readStatus(const rpi_hal_uint32_t rca, rpi_hal_uint32_t* pStatus);

rpi_hal_uint32_t rpi_hal_sd_hci_setBlockLength(const rpi_hal_uint32_t length);

rpi_hal_uint32_t rpi_hal_sd_hci_switch(const rpi_hal_uint8_t mode, const rpi_hal_uint32_t arg);

rpi_hal_uint32_t rpi_hal_sd_hci_sendAppCommand(const rpi_hal_uint32_t rca);

rpi_hal_uint32_t rpi_hal_sd_hci_readNumWrittenBlocks(const rpi_hal_uint32_t rca, rpi_hal_uint32_t* pNumBlocks);

rpi_hal_uint32_t rpi_hal_sd_hci_setWriteBlockEraseCount(const rpi_hal_uint32_t rca, const rpi_hal_uint32_t eraseCount);

rpi_hal_uint32_t rpi_hal_sd_hci_eraseStart(const rpi_hal_uint32_t startBlock);

rpi_hal_uint32_t rpi_hal_sd_hci_eraseEnd(const rpi_hal_uint32_t endBlock);

rpi_hal_uint32_t rpi_hal_sd_hci_erase();

#endif
