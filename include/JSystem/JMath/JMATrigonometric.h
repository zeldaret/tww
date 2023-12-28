#ifndef JMATRIGONOMETRIC_H
#define JMATRIGONOMETRIC_H

#include "dolphin/types.h"
#include "utility.h"

extern u32 jmaSinShift;
extern f32 *jmaSinTable;
extern f32 *jmaCosTable;

inline f32 JMASCos(s16 v) {
    return jmaCosTable[static_cast<u16>(v) >> jmaSinShift];
}
inline f32 JMASSin(s16 v) {
    return jmaSinTable[static_cast<u16>(v) >> jmaSinShift];
}

#endif /* JMATRIGONOMETRIC_H */
