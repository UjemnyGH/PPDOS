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

int strlen(const char *str) {
  int len = 0;

  while(str[len] != '\0') {
    len++;
  }

  return len;
}

int strcmp(const char* a, const char* b) {
  for(int i = 0; i < (strlen(a) > strlen(b) ? strlen(b) : strlen(a)); i++) {
    if(a[i] != b[i])
      return a[i] - b[i];
  }

  return 0;
}

int strncmp(const char* a, const char* b, const unsigned long size) {
  const int stringSize = strlen(a) > strlen(b) ? strlen(b) : strlen(a);

  for(int i = 0; i < (stringSize > size ? size : stringSize); i++) {
    if(a[i] != b[i])
      return a[i] - b[i];
  }

  return 0;
}

const char* strchr(const char* str, const int character) {
  return memchr((void*)str, character, strlen(str));
}

const char* strstr(const char* a, const char* b) {
  for(int i = 0; i < strlen(a); i++) {
    if(strcmp(a + i, b) == 0)
      return a +i;
  }

  return NULL;
}

char* strcat(char* dst, const char* src) {
  return strcpy(dst + strlen(dst), src);  
}

char* strncat(char* dst, const char* src, const unsigned long size) {
  return strncpy(dst + strlen(dst), src, size);
}

char* strcpy(char* dst, const char* src) {
  return memcpy(dst, src, strlen(src));
}

char* strncpy(char* dst, const char* src, const unsigned long size) {
  return memcpy(dst, src, (size > strlen(src) ? strlen(src) : size));
}

