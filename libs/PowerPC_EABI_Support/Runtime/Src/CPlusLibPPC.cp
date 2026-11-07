#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

extern void* __copy(char*, char*, size_t);

#ifdef __cplusplus
}
#endif

void* __copy(char* dest, char* src, size_t size) {
    char* p;

    if (dest && size) {
        p = dest;
        do {
            *p = *src;
            ++p;
            ++src;
            --size;
        } while (size);
    }
    return dest;
}
