#ifndef C_M3D_G_CYL_H
#define C_M3D_G_CYL_H

#include "SSystem/SComponent/c_xyz.h"
#include "global.h"

// Cylinder
struct cM3dGCylS {
    /* 0x00 */ Vec mCenter;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 mHeight;
};  // Size = 0x14

class cM3dGSph;

class cM3dGCyl {
public:
    /* 0x00 */ cXyz mCenter;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 mHeight;
    /* 0x14 vtable */
    cM3dGCyl() {}
    cM3dGCyl(const cXyz*, f32, f32);
    virtual ~cM3dGCyl() {}
    void SetC(const cXyz& pos);
    void SetH(f32 h);
    void SetR(f32 r);
    bool cross(const cM3dGSph*, cXyz*) const;
    bool cross(const cM3dGCyl*, cXyz*) const;
    bool cross(const cM3dGSph*, f32*) const;
    bool cross(const cM3dGCyl*, f32*) const;
    const cXyz* GetCP(void) const { return &mCenter; }
    f32 GetR(void) const { return mRadius; }
    f32 GetH(void) const { return mHeight; }
    cXyz& GetC() { return mCenter; }
};  // Size = 0x18

STATIC_ASSERT(0x18 == sizeof(cM3dGCyl));

#endif /* C_M3D_G_CYL_H */
