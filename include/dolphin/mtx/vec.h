#ifndef VEC_H
#define VEC_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Vec {
    f32 x, y, z;
} Vec;

typedef Vec* VecPtr;
typedef Vec Point3d;
typedef Vec* Point3dPtr;

typedef struct SVec {
    s16 x, y, z;
} SVec;

void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECNormalize(const Vec* src, Vec* unit);
f32 PSVECSquareMag(const Vec* v);
f32 PSVECMag(const Vec* v);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
void PSVECCrossProduct(const Vec* a, const Vec* b, Vec* axb);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
f32 PSVECDistance(const Vec* a, const Vec* b);

void C_VECHalfAngle(const Vec* a, const Vec* b, Vec* half);
void C_VECReflect(const Vec* src, const Vec* normal, Vec* dst);

inline void C_VECAdd(register const Vec* a, register const Vec* b, register Vec* ab) {
    ab->x = a->x + b->x;
    ab->y = a->y + b->y;
    ab->z = a->z + b->z;
}

inline void C_VECSubtract(register const Vec* a, register const Vec* b, register Vec* ab) {
    ab->x = a->x - b->x;
    ab->y = a->y - b->y;
    ab->z = a->z - b->z;
}

inline f32 C_VECSquareMag(const Vec* v) {
    return v->x * v->x + v->y * v->y + v->z * v->z;
}

inline BOOL checkScaleOne(Vec v) {
    if (v.x == 1.0f && v.y == 1.0f && v.z == 1.0f) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* When compiling in debug mode, use C implementations */
#if 0
#define VECAdd C_VECAdd
#define VECSubtract C_VECSubtract
#define VECScale C_VECScale
#define VECNormalize C_VECNormalize
#define VECSquareMag C_VECSquareMag
#define VECMag C_VECMag
#define VECDotProduct C_VECDotProduct
#define VECCrossProduct C_VECCrossProduct
#define VECSquareDistance C_VECSquareDistance
#define VECDistance C_VECDistance
#else
#define VECAdd PSVECAdd
#define VECSubtract PSVECSubtract
#define VECScale PSVECScale
#define VECNormalize PSVECNormalize
#define VECSquareMag PSVECSquareMag
#define VECMag PSVECMag
#define VECDotProduct PSVECDotProduct
#define VECCrossProduct PSVECCrossProduct
#define VECSquareDistance PSVECSquareDistance
#define VECDistance PSVECDistance
#endif

#ifdef __cplusplus
};
#endif

#endif /* VEC_H */
