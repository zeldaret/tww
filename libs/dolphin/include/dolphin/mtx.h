#ifndef MTX_H
#define MTX_H

#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef f32 Mtx[3][4];
typedef f32 Mtx44[4][4];
typedef f32 Mtx33[3][3];
typedef f32 Mtx23[2][3];
typedef f32 (*MtxP)[4];
typedef f32 (*Mtx3P)[3];
typedef const f32 (*CMtxP)[4];  // Change name later?

typedef struct Vec {
    f32 x, y, z;
} Vec;

typedef Vec* VecPtr;
typedef Vec Point3d;
typedef Vec* Point3dPtr;

typedef struct SVec {
    s16 x, y, z;
} SVec;

typedef struct S16Vec {
    s16 x, y, z;
} S16Vec;

typedef struct Quaternion {
    f32 x, y, z, w;
} Quaternion;

void C_MTXIdentity(Mtx m);
void PSMTXIdentity(Mtx m);
void C_MTXCopy(const Mtx src, Mtx dst);
void PSMTXCopy(const Mtx src, Mtx dst);
void C_MTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
u32 C_MTXInverse(const Mtx src, Mtx inv);
u32 PSMTXInverse(const Mtx src, Mtx inv);
void C_MTXRotRad(Mtx m, u8 axis, f32 rad);
void PSMTXRotRad(Mtx m, u8 axis, f32 rad);
void C_MTXRotTrig(Mtx m, u8 axis, f32 sin, f32 cos);
void PSMTXRotTrig(Mtx m, u8 axis, f32 sin, f32 cos);
void C_MTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void __PSMTXRotAxisRadInternal(Mtx m, const Vec* axis, f32 sT, f32 cT);
void PSMTXRotAxisRad(Mtx m, const Vec* axis, f32 rad);
void C_MTXTrans(Mtx m, f32 x, f32 y, f32 z);
void PSMTXTrans(Mtx m, f32 x, f32 y, f32 z);
void C_MTXTransApply(const Mtx src, Mtx dst, f32 x, f32 y, f32 z);
void PSMTXTransApply(const Mtx src, Mtx dst, f32 x, f32 y, f32 z);
void C_MTXScale(Mtx m, f32 x, f32 y, f32 z);
void PSMTXScale(Mtx m, f32 x, f32 y, f32 z);
void C_MTXScaleApply(const Mtx src, Mtx dst, f32 x, f32 y, f32 z);
void PSMTXScaleApply(const Mtx src, Mtx dst, f32 x, f32 y, f32 z);
void C_MTXQuat(Mtx m, const Quaternion* q);
void PSMTXQuat(Mtx m, const Quaternion* q);

void C_MTXLookAt(Mtx m, const Vec* camPos, const Vec* camUp, const Vec* target);
void C_MTXLightPerspective(Mtx m, f32 fovY, f32 aspect, f32 scale_s, f32 scale_t, f32 trans_s,
                           f32 trans_t);
void C_MTXLightOrtho(Mtx m, f32 top, f32 bottom, f32 left, f32 right, f32 scale_s, f32 scale_t,
                     f32 trans_s, f32 trans_t);

void C_MTXPerspective(Mtx44 m, f32 fovy, f32 aspect, f32 near, f32 far);
void C_MTXOrtho(Mtx44 m, f32 top, f32 bottom, f32 left, f32 right, f32 near, f32 far);

void C_MTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void C_MTXMultVecArray(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);
void PSMTXMultVecArray(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);
void C_MTXMultVecSR(const Mtx m, const Vec* src, Vec* dst);
void PSMTXMultVecSR(const Mtx m, const Vec* src, Vec* dst);
void C_MTXMultVecArraySR(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);
void PSMTXMultVecArraySR(const Mtx m, const Vec* srcBase, Vec* dstBase, u32 count);

void C_VECAdd(const Vec* a, const Vec* b, Vec* ab);
void PSVECAdd(const Vec* a, const Vec* b, Vec* ab);
void C_VECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void PSVECSubtract(const Vec* a, const Vec* b, Vec* a_b);
void C_VECScale(const Vec* src, Vec* dst, f32 scale);
void PSVECScale(const Vec* src, Vec* dst, f32 scale);
void C_VECNormalize(const Vec* src, Vec* unit);
void PSVECNormalize(const Vec* src, Vec* unit);
f32 C_VECSquareMag(const Vec* v);
f32 PSVECSquareMag(const Vec* v);
f32 C_VECMag(const Vec* v);
f32 PSVECMag(const Vec* v);
f32 C_VECDotProduct(const Vec* a, const Vec* b);
f32 PSVECDotProduct(const Vec* a, const Vec* b);
void C_VECCrossProduct(const Vec* a, const Vec* b, Vec* axb);
void PSVECCrossProduct(const Vec* a, const Vec* b, Vec* axb);
f32 C_VECSquareDistance(const Vec* a, const Vec* b);
f32 PSVECSquareDistance(const Vec* a, const Vec* b);
f32 C_VECDistance(const Vec* a, const Vec* b);
f32 PSVECDistance(const Vec* a, const Vec* b);

void C_VECHalfAngle(const Vec* a, const Vec* b, Vec* half);
void C_VECReflect(const Vec* src, const Vec* normal, Vec* dst);

void C_QUATMultiply(const Quaternion* a, const Quaternion* b, Quaternion* ab);
void PSQUATMultiply(const Quaternion* a, const Quaternion* b, Quaternion* ab);
void C_QUATNormalize(const Quaternion* src, Quaternion* unit);
void PSQUATNormalize(const Quaternion* src, Quaternion* unit);
void C_QUATRotAxisRad(Quaternion* q, const Vec* axis, f32 rad);
void C_QUATSlerp(const Quaternion* p, const Quaternion* q, Quaternion* r, f32 t);

#define MTXDegToRad(deg) ((deg) * 0.01745329252f)
#define MTXRadToDeg(rad) ((rad) * 57.29577951f)

/* When compiling in debug mode, use C implementations */
#if defined(DEBUG) || !defined(__MWERKS__)
#define MTXIdentity C_MTXIdentity
#define MTXCopy C_MTXCopy
#define MTXConcat C_MTXConcat
#define MTXInverse C_MTXInverse
#define MTXRotRad C_MTXRotRad
#define MTXRotTrig C_MTXRotTrig
#define MTXRotAxisRad C_MTXRotAxisRad
#define MTXTrans C_MTXTrans
#define MTXTransApply C_MTXTransApply
#define MTXScale C_MTXScale
#define MTXScaleApply C_MTXScaleApply
#define MTXQuat C_MTXQuat
#define MTXMultVec C_MTXMultVec
#define MTXMultVecSR C_MTXMultVecSR
#define MTXMultVecArray C_MTXMultVecArray
#define MTXMultVecArraySR C_MTXMultVecArraySR
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
#define QUATMultiply C_QUATMultiply
#define QUATNormalize C_QUATNormalize
#else
#define MTXIdentity PSMTXIdentity
#define MTXCopy PSMTXCopy
#define MTXConcat PSMTXConcat
#define MTXInverse PSMTXInverse
#define MTXRotRad PSMTXRotRad
#define MTXRotTrig PSMTXRotTrig
#define MTXRotAxisRad PSMTXRotAxisRad
#define MTXTrans PSMTXTrans
#define MTXTransApply PSMTXTransApply
#define MTXScale PSMTXScale
#define MTXScaleApply PSMTXScaleApply
#define MTXQuat PSMTXQuat
#define MTXMultVec PSMTXMultVec
#define MTXMultVecSR PSMTXMultVecSR
#define MTXMultVecArray PSMTXMultVecArray
#define MTXMultVecArraySR PSMTXMultVecArraySR
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
#define QUATMultiply PSQUATMultiply
#define QUATNormalize PSQUATNormalize
#endif

#define MTXRotDeg(m, axis, deg) MTXRotRad(m, axis, MTXDegToRad(deg))
#define MTXRotAxisDeg(m, axis, deg) MTXRotAxisRad(m, axis, MTXDegToRad(deg))

#define QUATRotAxisRad C_QUATRotAxisRad

#ifdef __cplusplus
};
#endif

#endif /* MTX_H */
