#include "bcm283x_sd.h"

static rpi_hal_uint32_t sdHciCardInitialized = 0;
static rpi_hal_uint32_t sdHciCardRca = 0;
const rpi_hal_uint32_t sdHciCardBlockSize = 512;
const rpi_hal_uint32_t sdHciTimeout = 1000000;
static rpi_hal_uint32_t sdHciIsHighCapacity = 0;

rpi_hal_uint32_t rpi_hal_sd_hci_getMasterRCA() {
  return sdHciCardRca;
}

rpi_hal_uint32_t rpi_hal_sd_hci_waitForCommandReady() {
  for(rpi_hal_uint32_t i = 0; i < sdHciTimeout; i++) {
    if((sdhci.presentState & sdhci_presentState_commandInhibit) == 0)
      return 1;
  }

  return 0;
}

rpi_hal_uint32_t rpi_hal_sd_hci_waitForDataReady() {
  for(rpi_hal_uint32_t i = 0; i < sdHciTimeout; i++) {
    if((sdhci.presentState & sdhci_presentState_dataInhibit) == 0)
      return 1;
  }

  return 0;
}

void rpi_hal_sd_hci_clearInterrupts() {
  sdhci.intStat = 0xFFFFFFFF;
}

rpi_hal_uint32_t rpi_hal_sd_hci_sendCommand(const rpi_hal_uint32_t command, const rpi_hal_uint32_t arg) {
  if(!rpi_hal_sd_hci_waitForCommandReady())
    return 0;

  if(command & eMMC_command_app_preeraseBlocksForWrite_arg)
    sdhci.argument2 = arg;
  else
    sdhci.argument = arg;
  sdhci.command = command;

  for(rpi_hal_uint32_t i = 0; i < sdHciTimeout; i++) {
    if(sdhci.intStat & sdhci_intStat_response) {
      rpi_hal_sd_hci_clearInterrupts();

      return 1;
    }
  }

  return 0;
}

rpi_hal_uint32_t rpi_hal_sd_hci_readBlock(const rpi_hal_uint32_t logicalBlockAddr, void* pDst) {
  if(!sdHciCardInitialized || pDst == (void*)0 || !rpi_hal_sd_hci_waitForCommandReady() || !rpi_hal_sd_hci_waitForDataReady())
    return 0;

  sdhci.blockCount = 1;
  sdhci.blockSize = sdHciCardBlockSize;
  sdhci.transferMode = sdhci_transferMode_read;

  if(!rpi_hal_sd_hci_sendCommand(eMMC_command_readSingleBlock_arg | sdhci_command_responseLong, logicalBlockAddr))
    return 0;

  if(!rpi_hal_sd_hci_waitForCommandReady())
    return 0;

  for(rpi_hal_uint32_t i = 0; i < (sdHciCardBlockSize / 4); i++) {
    ((rpi_hal_uint32_t*)pDst)[i] = sdhci.bufferDataPort;
  }

  return 1;
}

rpi_hal_uint32_t rpi_hal_sd_hci_writeBlock(const rpi_hal_uint32_t logicalBlockAddr, const void* pSrc) {
  if(!sdHciCardInitialized || pSrc == (void*)0 || !rpi_hal_sd_hci_waitForCommandReady() || !rpi_hal_sd_hci_waitForDataReady())
    return 0;

  sdhci.blockCount = 1;
  sdhci.blockSize = sdHciCardBlockSize;
  sdhci.transferMode &= ~sdhci_transferMode_read;

  if(!rpi_hal_sd_hci_sendCommand(eMMC_command_writeSingleBlock_arg | sdhci_command_responseLong, logicalBlockAddr))
    return 0;

  if(!rpi_hal_sd_hci_waitForCommandReady())
    return 0;

  for(rpi_hal_uint32_t i = 0; i < (sdHciCardBlockSize / 4); i++) {
    sdhci.bufferDataPort = ((rpi_hal_uint32_t*)pSrc)[i];
  }

  return 1;
}

rpi_hal_uint32_t rpi_hal_sd_hci_readMultipleBlocks(const rpi_hal_uint32_t logicalBlockAddr, const rpi_hal_uint32_t count, void* pDst) {
  if(!sdHciCardInitialized || pDst == (void*)0 || !rpi_hal_sd_hci_waitForCommandReady() || !rpi_hal_sd_hci_waitForDataReady())
    return 0;

  sdhci.blockCount = count;
  sdhci.blockSize = sdHciCardBlockSize;
  sdhci.transferMode = sdhci_transferMode_read | sdhci_transferMode_blockCountEnable | sdhci_transferMode_multiBlock | sdhci_transferMode_autoCMD12StopTrans;

  if(!rpi_hal_sd_hci_sendCommand(eMMC_command_readMultipleBlocks_arg | sdhci_command_responseLong, logicalBlockAddr))
    return 0;

  if(!rpi_hal_sd_hci_waitForCommandReady())
    return 0;

  for(rpi_hal_uint32_t i = 0; i < (count * sdHciCardBlockSize / 4); i++) {
    while(!(sdhci.presentState & sdhci_presentState_readReady))
      continue;

    ((rpi_hal_uint32_t*)pDst)[i] = sdhci.bufferDataPort;
  }

  return 1;
}

rpi_hal_uint32_t rpi_hal_sd_hci_writeMultipleBlocks(const rpi_hal_uint32_t logicalBlockAddr, const rpi_hal_uint32_t count, const void* pSrc) {
  if(!sdHciCardInitialized || pSrc == (void*)0 || !rpi_hal_sd_hci_waitForCommandReady() || !rpi_hal_sd_hci_waitForDataReady())
    return 0;
  
  sdhci.blockCount = count;
  sdhci.blockSize = sdHciCardBlockSize;
  sdhci.transferMode = sdhci_transferMode_blockCountEnable | sdhci_transferMode_multiBlock | sdhci_transferMode_autoCMD12StopTrans;

  if(!rpi_hal_sd_hci_sendCommand(eMMC_command_writeMultipleBlocks_arg | sdhci_command_responseLong, logicalBlockAddr))
    return 0;

  if(!rpi_hal_sd_hci_waitForCommandReady())
    return 0;

  for(rpi_hal_uint32_t i = 0; i < (count * sdHciCardBlockSize / 4); i++) {
    while(!(sdhci.presentState & sdhci_presentState_writeReady))
      continue;

    sdhci.bufferDataPort = ((rpi_hal_uint32_t*)pSrc)[i];
  }

  return 1;
}

rpi_hal_uint32_t rpi_hal_sd_hci_initialize() {
  rpi_hal_sd_hci_sendCommand(eMMC_command_goIdleState, 0);

  rpi_hal_sd_hci_sendCommand(eMMC_command_sendIfCond_arg, 0x1AA);

  if((sdhci.response[0] & 0xFFF) != 0x1AA)
    return 0;

  while(!(sdhci.response[0] & (1 << 31))) {
    rpi_hal_sd_hci_sendCommand(eMMC_command_nextCommandAppSpecific_arg, 0);
    rpi_hal_sd_hci_sendCommand(eMMC_command_app_sendHostCapacitySupport_arg, 0x40300000);
  }

  sdHciIsHighCapacity = (sdhci.response[0] & (1 << 30)) != 0;

  rpi_hal_sd_hci_sendCommand(eMMC_command_sendRelativeCardAddr, 0);
  sdHciCardRca = sdhci.response[0] >> 16;

  if(sdHciCardRca == 0)
    return 0;

  rpi_hal_sd_hci_sendCommand(eMMC_command_select_arg, sdHciCardRca << 16);

  sdHciCardInitialized = 1;

  rpi_hal_sd_hci_sendCommand(eMMC_command_setBlockLength_arg, 512);

  return 1;
}

rpi_hal_uint32_t rpi_hal_sd_hci_isHighCapacity() {
  return sdHciIsHighCapacity;
}

rpi_hal_uint32_t rpi_hal_sd_hci_readCardSpecificData(const rpi_hal_uint32_t rca) {
  return rpi_hal_sd_hci_sendCommand(eMMC_command_sendCSD_arg | sdhci_command_responseLong, ((rca << 16) & 0xFFFF0000));
}

rpi_hal_uint32_t rpi_hal_sd_hci_readStatus(const rpi_hal_uint32_t rca, rpi_hal_uint32_t* pStatus) {
  if(!pStatus)
    return 0;

  if(!rpi_hal_sd_hci_sendCommand(eMMC_command_sendStatus_arg | sdhci_command_responseShort, ((rca << 16) & 0xFFFF0000)))
    return 0;
  
  *pStatus = sdhci.response[0];

  return 1;
}

rpi_hal_uint32_t rpi_hal_sd_hci_setBlockLength(const rpi_hal_uint32_t length) {
  return rpi_hal_sd_hci_sendCommand(eMMC_command_setBlockLength_arg | sdhci_command_responseShort, length);
}

rpi_hal_uint32_t rpi_hal_sd_hci_switch(const rpi_hal_uint8_t mode, const rpi_hal_uint32_t arg) {
  return rpi_hal_sd_hci_sendCommand(eMMC_command_switchFunction_arg | sdhci_command_responseShort, ((((rpi_hal_uint32_t)mode) << 31) | (arg & 0x0FFFFFFF)));
}

rpi_hal_uint32_t rpi_hal_sd_hci_sendAppCommand(const rpi_hal_uint32_t rca) {
  return rpi_hal_sd_hci_sendCommand(eMMC_command_nextCommandAppSpecific_arg | sdhci_command_responseShort, ((rca << 16) & 0xFFFF0000));
}

rpi_hal_uint32_t rpi_hal_sd_hci_readNumWrittenBlocks(const rpi_hal_uint32_t rca, rpi_hal_uint32_t* pNumBlocks) {
  if(!rpi_hal_sd_hci_sendAppCommand(rca))
    return 0;

  if(!rpi_hal_sd_hci_sendCommand(eMMC_command_app_sendWriteBlocksNumber | sdhci_command_responseShort, 0))
    return 0;

  if(pNumBlocks)
    *pNumBlocks = sdhci.response[0];

  return 1;
}

rpi_hal_uint32_t rpi_hal_sd_hci_setWriteBlockEraseCount(const rpi_hal_uint32_t rca, const rpi_hal_uint32_t eraseCount) {
  if(!rpi_hal_sd_hci_sendAppCommand(rca))
    return 0;

  return rpi_hal_sd_hci_sendCommand(eMMC_command_app_preeraseBlocksForWrite_arg | sdhci_command_responseShort, eraseCount);
}

rpi_hal_uint32_t rpi_hal_sd_hci_eraseStart(const rpi_hal_uint32_t startBlock) {
  return rpi_hal_sd_hci_sendCommand(eMMC_command_eraseBlockStart_arg | sdhci_command_responseShort, startBlock);
}

rpi_hal_uint32_t rpi_hal_sd_hci_eraseEnd(const rpi_hal_uint32_t endBlock) {
  return rpi_hal_sd_hci_sendCommand(eMMC_command_eraseBlockEnd_arg | sdhci_command_responseShort, endBlock);
}

rpi_hal_uint32_t rpi_hal_sd_hci_erase() {
  return rpi_hal_sd_hci_sendCommand(eMMC_command_erase | sdhci_command_responseShort, 0);
}

