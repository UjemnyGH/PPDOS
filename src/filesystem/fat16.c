#include "fat16.h"
#include "../hal/rpi/bcm283x_sd.h"
#include "../common/pp_memory.h"

uint32_t fat16_loadBootSector(fat16_state_t *const pFat16State) {
  if(!pFat16State)
    return fat16_errorNoStatePresent;

  uint8_t sectorBuffer[512];

  if(rpi_hal_sd_hci_readBlock(0, sectorBuffer))
    return fat16_errorReadingBlock;

  memcpy(&pFat16State->bootSector, sectorBuffer, sizeof(fat16_boot_sector_t));

  return fat16_success;
}

uint32_t fat16_loadVolumeInfo(fat16_state_t* const pFat16State) {
  if(fat16_loadBootSector(pFat16State) != fat16_success)
    return fat16_errorReadingBlock;

  pFat16State->volume.rootDirSectors = ((pFat16State->bootSector.rootEntryCount * 32) + (pFat16State->bootSector.bytesPerSector - 1)) / pFat16State->bootSector.bytesPerSector;
  pFat16State->volume.rootDirBlockAddr = pFat16State->bootSector.reservedSectors + pFat16State->bootSector.numFats * pFat16State->bootSector.sectorsPerFat;
  pFat16State->volume.dataRegionBlockAddr = pFat16State->volume.rootDirBlockAddr + pFat16State->volume.rootDirSectors;

  pFat16State->volumeInfoLoaded = 1;

  return fat16_success;
}

uint8_t fat16_calculateChecksum(uint8_t *pFileShortName) {
  uint8_t sum = 0;

  for(short i = 11; i != 0; i--) 
    sum = ((sum & 1) ? 0x80 : 0) + (sum >> 1) + *pFileShortName++;

  return sum;
}

uint32_t fat16_loadRootDirectory(fat16_state_t* const pFat16State) {
  if(!pFat16State)
    return fat16_errorNoStatePresent;

  for(uint32_t i = 0; i < pFat16State->volume.rootDirSectors; i++) {
    if(!rpi_hal_sd_hci_readBlock(pFat16State->volume.rootDirBlockAddr + i, ((uint8_t*)pFat16State->rootDir) + (i * pFat16State->bootSector.bytesPerSector)))
      return fat16_errorReadingBlock;
  }

  pFat16State->rootEntriesLoaded = pFat16State->bootSector.rootEntryCount;

  return fat16_success;
}

uint32_t fat16_readFile(fat16_state_t* const pFat16State, const char* name, void* pDst) {  
  return fat16_errorReadingFile;
}

uint32_t fat16_writeFile(fat16_state_t* const pFat16State, const char* name, const void* pSrc, const uint64_t size) {
  return fat16_errorWritingFile;
}

