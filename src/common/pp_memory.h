#ifndef _PPDOS_MEMORY_
#define _PPDOS_MEMORY_

void* memset(void* ptr, int value, unsigned long num);

void* memcpy(void* pDst, const void* pSrc, unsigned long num);

int memcmp(const void* ptr1, const void* ptr2, const unsigned long num);

void* memchr(void* ptr, int value, unsigned long num);

int strlen(const char* str);

#endif
