#ifndef _PPDOS_FAT16_STRUCTS_
#define _PPDOS_FAT16_STRUCTS_

#include "../shared_defs.h"

#define FAT16_TIME_FORMAT(hours, minutes, seconds) ( ((hours & 0x1F) << 11) | ((minutes & 0x1F) << 5) | (seconds & 0x1F) )
#define FAT16_DATE_FORMAT(day, month, year) ( (day & 0x1F) | ((month & 0xF) << 5) | ((year & 0x7F) << 9) ) 
#define FAT16_LONG_DIR_ENTRY_LAST_ORDER(order) ( 0x40 | (order) )

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
  
  uint8_t driveNumber;
  uint8_t RESERVED0;
  uint8_t bootSignature;
  uint32_t volumeId;
  uint8_t volumeLabel;
  uint8_t filesystemType[8];
} __attribute__((packed)) fat16_boot_sector_t;

typedef struct fat16_directory_entry_s {
  uint8_t name[11];
  uint8_t dirAttribute;
  uint8_t NT_RESERVED;
  uint8_t creationTimeTenth;
  uint16_t creationTime;
  uint16_t creationDate;
  uint16_t lastAccessDate;
  uint16_t firstClusterHighWord;
  uint16_t lastWriteTime;
  uint16_t lastWriteDate;
  uint16_t firstClusterLowWord;
  uint32_t fileSize;
} __attribute__((packed)) fat16_directory_entry_t;

typedef struct fat16_long_directory_entry_s {
  uint8_t order;  /*For long dsir entries must end with 0x40 mask*/
  uint8_t name[10];
  uint8_t dirAttrbute; /*Must be directoryEntry_dirAttribute_longName*/
  uint8_t type;
  uint8_t checkSum;
  uint8_t name2[12];
  uint16_t firstClusterLowWord; /*Must be 0*/
  uint8_t name3[4];
} __attribute__((packed)) fat16_long_directory_entry_t;

enum fat16_directory_entry_dirAttribute {
  directoryEntry_dirAttribute_readOnly  = 0x01,
  directoryEntry_dirAttribute_hidden    = 0x02,
  directoryEntry_dirAttribute_system    = 0x04,
  directoryEntry_dirAttribute_volumeId  = 0x08,
  directoryEntry_dirAttribute_directory = 0x10,
  directoryEntry_dirAttribute_archive   = 0x20,
  directoryEntry_dirAttribute_longName  = 0x0F
};

typedef struct fat16_volume_s {
  uint32_t rootDirBlockAddr;
  uint32_t dataRegionBlockAddr; 
  uint32_t rootDirSectors;
} fat16_volume_t;

typedef struct fat16_state_s {
  fat16_boot_sector_t bootSector;

  fat16_volume_t volume;
  fat16_directory_entry_t rootDir[512];
  uint16_t rootEntriesLoaded;
  uint32_t volumeInfoLoaded;
} fat16_state_t;

enum fat16_return_codes {
  fat16_success = 0,
  fat16_errorReadingBlock = 1,
  fat16_errorNoStatePresent = 2,
  fat16_errorReadingFile = 3,
  fat16_volumeInfoNotLoaded = 4,
  fat16_errorWritingFile = 5,
};

uint32_t fat16_loadBootSector(fat16_state_t* const pFat16State);

uint32_t fat16_loadVolumeInfo(fat16_state_t* const pFat16State);

uint8_t fat16_calculateChecksum(uint8_t* pFileShortName);

uint32_t fat16_loadRootDirectory(fat16_state_t* const pFat16State);

uint32_t fat16_readFile(fat16_state_t* const pFat16State, const char* name, void* pDst);

uint32_t fat16_writeFile(fat16_state_t* const pFat16State, const char* name, const void* pSrc, const uint64_t size);

#endif
