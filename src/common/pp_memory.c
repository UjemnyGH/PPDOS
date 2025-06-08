#include "pp_memory.h"

void* memset(void* ptr, int value, unsigned long num) {
  for(unsigned long i = 0; i < num; i++) {
    ((unsigned char*)ptr)[i] = value;
  }

  return ptr;
}

void* memcpy(void* pDst, const void* pSrc, unsigned long num) {
  for(unsigned long i = 0; i < num; i++) {
    ((unsigned char*)pDst)[i] = ((unsigned char*)pSrc)[i];
  }

  return pDst;
}

int memcmp(const void *ptr1, const void *ptr2, const unsigned long num) {
  for(unsigned long i = 0; i < num; i++) {
    if(((unsigned char*)ptr1)[i] != ((unsigned char*)ptr2)[i])
      return ((unsigned char*)ptr1)[i] - ((unsigned char*)ptr2)[i];
  }

  return 0;
}

void* memchr(void* ptr, int value, unsigned long num) {
  for(unsigned long i = 0; i < num; i++) {
    if(((unsigned char*)ptr)[i] == value)
      return ptr + i;
  }

  return (void*)0;
}
