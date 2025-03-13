#ifndef C_M3D_G_CIR_H
#define C_M3D_G_CIR_H

#include "global.h"

class cM2dGCir {
public:
    f32 mPosX;
    f32 mPosY;
    f32 mRadius;
    
    f32 GetCx() const { return mPosX; }
    f32 GetCy() const { return mPosY; }
    f32 GetR() const { return mRadius; }
    void Set(f32 x, f32 y, f32 r) {
        mPosX = x;
        mPosY = y;
        mRadius = r;
    }

    cM2dGCir() {}
    virtual ~cM2dGCir() {}
};  // Size: 0x10

STATIC_ASSERT(sizeof(cM2dGCir) == 0x10);

class cM3dGCir : public cM2dGCir {
    f32 mPosZ;

public:
    cM3dGCir() {}
    virtual ~cM3dGCir() {}
    void Set(f32 x, f32 y, f32 z, f32 r) {
        cM2dGCir::Set(x, y, r);
        mPosZ = z;
    }
};  // Size: 0x14

STATIC_ASSERT(sizeof(cM3dGCir) == 0x14);

#endif /* C_M3D_G_CIR_H */
