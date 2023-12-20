#ifndef C_M3D_G_CYL_H
#define C_M3D_G_CYL_H

#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_m3d_g_cps.h"
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
    /* 0x14 */ /* vtable */

public:
    cM3dGCyl() {}
    cM3dGCyl(const cXyz*, f32, f32);
    virtual ~cM3dGCyl() {}
    void SetC(const cXyz& pos);
    void SetH(f32 h);
    void SetR(f32 r);
    void Set(const cM3dGCylS & src) {
        SetC(src.mCenter);
        SetR(src.mRadius);
        SetH(src.mHeight);
    }
    void Set(const cXyz& center, f32 radius, f32 height) {
        SetC(center);
        SetR(radius);
        SetH(height);
    }
    bool cross(const cM3dGSph*, cXyz*) const;
    bool cross(const cM3dGCyl*, cXyz*) const;
    bool cross(const cM3dGSph*, f32*) const;
    bool cross(const cM3dGCyl*, f32*) const;
    bool Cross(const cM3dGCps* cps, cXyz* dst) const { return cM3d_Cross_CpsCyl(*cps, *this, dst); }
    bool Cross(const cM3dGTri& tri, cXyz* dst) const { return cM3d_Cross_CylTri(this, &tri, dst); }
    const cXyz* GetCP() const { return &mCenter; }
    f32 GetR() const { return mRadius; }
    f32 GetH() const { return mHeight; }
    cXyz& GetC() { return mCenter; }

    void GetC() const {}
    void GetCP() {}
    void GetRP() {}
};  // Size = 0x18

STATIC_ASSERT(0x18 == sizeof(cM3dGCyl));

#endif /* C_M3D_G_CYL_H */
