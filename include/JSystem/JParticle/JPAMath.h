#ifndef JPAMATH_H
#define JPAMATH_H

#include "JSystem/JGeometry.h"
#include "dolphin/types.h"

void JPAGetYZRotateMtx(s16, s16, f32(*)[4]);
void JPAGetXYZRotateMtx(s16, s16, s16, f32(*)[4]);
void JPAGetDirMtx(const JGeometry::TVec3<f32>&, f32(*)[4]);
void JPASetSVecfromMtx(f32(*)[4], JGeometry::TVec3<f32>&);
void JPASetRMtxTVecfromMtx(f32(*)[4], f32(*)[4], JGeometry::TVec3<f32>&);
void JPASetRMtxSTVecfromMtx(f32(*)[4], f32(*)[4], JGeometry::TVec3<f32>&, JGeometry::TVec3<f32>&);
f32 JPAGetKeyFrameValue(f32, u16, const f32*);
void JPAGetUnitVec(s16, s16, JGeometry::TVec3<f32>&);

#endif /* JPAMATH_H */
