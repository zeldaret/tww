#ifndef JPAMATH_H
#define JPAMATH_H

#include "JSystem/JGeometry.h"
#include "dolphin/types.h"

void JPAGetYZRotateMtx(short, short, float(*)[4]);
void JPAGetXYZRotateMtx(short, short, short, float(*)[4]);
void JPAGetDirMtx(const JGeometry::TVec3<float>&, float(*)[4]);
void JPASetSVecfromMtx(float(*)[4], JGeometry::TVec3<float>&);
void JPASetRMtxTVecfromMtx(float(*)[4], float(*)[4], JGeometry::TVec3<float>&);
void JPASetRMtxSTVecfromMtx(float(*)[4], float(*)[4], JGeometry::TVec3<float>&, JGeometry::TVec3<float>&);
void JPAGetKeyFrameValue(float, unsigned short, const float*);
void JPAGetUnitVec(short, short, JGeometry::TVec3<float>&);

#endif /* JPAMATH_H */
