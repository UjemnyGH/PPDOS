#ifndef _PPDOS_FAT16_STRUCTS_
#define _PPDOS_FAT16_STRUCTS_

#include "../shared_defs.h"

typedef struct fat16_boot_sector_s {
  uint8_t jump[3];
  char oem[8];
  uint16_t bytesPerSector;
  uint8_t sectorsPerCluster;
  uint16_t reservedSectors;
  uint8_t numFats;
  uint16_t rootEntryCount;
  uint16_t totalSectors16;
  uint8_t mediaDescriptor;
  uint16_t sectorsPerFat;
  uint16_t sectorsPerTrack;
  uint16_t numHeads;
  uint32_t hiddenSectors;
  uint32_t totalSectors32;

} __attribute__((packed)) fat16_boot_sector_t;

#endif
