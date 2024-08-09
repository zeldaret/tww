#ifndef _MSL_COMMON_STRING_H
#define _MSL_COMMON_STRING_H

#include "stddef.h"
#include "extras.h"
#include "global.h"

#ifdef __cplusplus
extern "C" {
#endif

SECTION_INIT void* memcpy(void* dest, const void* src, size_t n);
SECTION_INIT void __fill_mem(void* dest, int val, size_t count);
SECTION_INIT void* memset(void* dest, int val, size_t count);

int memcmp(const void* lhs, const void* rhs, size_t count);
void* __memrchr(const void* ptr, int ch, size_t count);
void* memchr(const void* ptr, int ch, size_t count);
void* memmove(void* dst, const void* src, size_t n);
char* strrchr(const char* str, int c);
char* strchr(const char* str, int c);
int strncmp(const char* str1, const char* str2, size_t n);
int strcmp(const char* str1, const char* str2);
char* strcat(char* dst, const char* src);
char* strncpy(char* dst, const char* src, size_t n);
char* strcpy(char* dst, const char* src);
size_t strlen(const char* str);

#ifdef __cplusplus
};


namespace std {
using ::strlen;
using ::strrchr;
}; // namespace std
#endif

#endif /* _MSL_COMMON_STRING_H */
