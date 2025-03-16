#ifndef JPAMATH_H
#define JPAMATH_H

#include "JSystem/JGeometry.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/types.h"

void JPAGetYZRotateMtx(s16, s16, Mtx);
void JPAGetXYZRotateMtx(s16, s16, s16, Mtx);
void JPAGetDirMtx(const JGeometry::TVec3<f32>&, Mtx);
void JPASetSVecfromMtx(Mtx, JGeometry::TVec3<f32>&);
void JPASetRMtxTVecfromMtx(Mtx, Mtx, JGeometry::TVec3<f32>&);
void JPASetRMtxSTVecfromMtx(Mtx, Mtx, JGeometry::TVec3<f32>&, JGeometry::TVec3<f32>&);
f32 JPAGetKeyFrameValue(f32, u16, const f32*);
void JPAGetUnitVec(s16, s16, JGeometry::TVec3<f32>&);

#endif /* JPAMATH_H */
