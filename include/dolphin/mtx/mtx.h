#ifndef MTX_H
#define MTX_H

#include "dolphin/mtx/mtx44.h" // IWYU pragma: export
#include "dolphin/mtx/quat.h"
#include "dolphin/types.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef f32 Mtx[3][4];
typedef f32 Mtx33[3][3];
typedef f32 Mtx23[2][3];
typedef f32 (*MtxP)[4];
typedef f32 (*Mtx3P)[3];
typedef const f32 (*CMtxP)[4];  // Change name later?

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
#endif

#define MTXRotDeg(m, axis, deg) MTXRotRad(m, axis, MTXDegToRad(deg))
#define MTXRotAxisDeg(m, axis, deg) MTXRotAxisRad(m, axis, MTXDegToRad(deg))

#ifdef __cplusplus
};
#endif

#endif /* MTX_H */
