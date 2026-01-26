#ifndef WEAK_DATA_H
#define WEAK_DATA_H

#ifdef DECOMPCTX
#include "dolphin/mtx/mtx.h"

static inline void fake_data_2100() {
    static Vec data_2100 = {1.0f, 1.0f, 1.0f};
}

static inline void fake_data_2080() {
    static Vec data_2080 = {1.0f, 1.0f, 1.0f};
}

#include "dolphin/gx/GXEnum.h"

static inline void fake_getAttnFn() {
    static u8 attnFnTbl_1811[] = { GX_AF_NONE, GX_AF_SPEC, GX_AF_NONE, GX_AF_SPOT };
}

extern inline void fake_sqrtf(float x) {
    static double _three[1] = {3.0};
    static double _half[1] = {.5};
}
#endif

#endif /* WEAK_DATA_H */
