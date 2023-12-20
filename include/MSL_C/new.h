#ifndef MSL_NEW_H_
#define MSL_NEW_H_

#include "MSL_C/MSL_Common/Src/stddef.h"

inline void* operator new(size_t size, void* ptr) {
    return ptr;
}

#endif
