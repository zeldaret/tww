#ifndef MSL_NEW_H_
#define MSL_NEW_H_

#include "stddef.h"

inline void* operator new(size_t size, void* ptr) {
    return ptr;
}

#endif
