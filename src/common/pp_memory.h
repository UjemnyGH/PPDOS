#ifndef _PPDOS_MEMORY_
#define _PPDOS_MEMORY_

#define NULL ((void*)0)

void* memset(void* ptr, int value, unsigned long num);

void* memcpy(void* pDst, const void* pSrc, unsigned long num);

int memcmp(const void* ptr1, const void* ptr2, const unsigned long num);

void* memchr(void* ptr, int value, unsigned long num);

/* String */

int strlen(const char* str);

int strcmp(const char* a, const char* b);

int strncmp(const char* a, const char* b, const unsigned long size);

const char* strchr(const char* str, const int character);

const char* strstr(const char* a, const char* b);

char* strcat(char* dst, const char* src);

char* strncat(char* dst, const char* src, const unsigned long size);

char* strcpy(char* dst, const char* src);

char* strncpy(char* dst, const char* src, const unsigned long size);

#endif
