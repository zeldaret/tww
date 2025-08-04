#ifndef C_M3D_G_SPH_H_
#define C_M3D_G_SPH_H_

#include "SSystem/SComponent/c_m3d.h"
#include "SSystem/SComponent/c_xyz.h"
#include "global.h"

class cM3dGCyl;

struct cM3dGSphS {
    /* 0x0 */ Vec mCenter;
    /* 0xC */ f32 mRadius;
};  // Size: 0x10

class cM3dGSph {
private:
public:
    /* 0x00 */ cXyz mCenter;
    /* 0x0C */ f32 mRadius;
    /* 0x10 vtable */

    cM3dGSph() {}
    virtual ~cM3dGSph() {}
#if VERSION == VERSION_DEMO
    void SetC(const cXyz& p) { mCenter = p; }
    void SetR(f32 r) { mRadius = r; }
#else
    void SetC(const cXyz& p);
    void SetR(f32 r);
#endif
    void SetC(f32 x, f32 y, f32 z) { mCenter.x = x; mCenter.y = y; mCenter.z = z; }
    void Set(const cM3dGSphS & src) {
        SetC(src.mCenter);
        SetR(src.mRadius);
    }
    void Set(const cXyz& srcCenter, f32 srcRadius) {
        SetC(srcCenter);
        SetR(srcRadius);
    }
    bool Cross(const cM3dGCps* cps, cXyz* dst) const {
        return cM3d_Cross_CpsSph(*cps, *this, dst);
    }
    bool Cross(const cM3dGTri& tri, cXyz* dst) const {
        return cM3d_Cross_SphTri(this, &tri, dst);
    }
    bool cross(const cM3dGCyl*, cXyz*) const;
    bool cross(const cM3dGSph*, cXyz*) const;
    bool cross(const cM3dGSph*, f32*) const;
    bool cross(const cM3dGCyl* cyl, f32* out) const {
        cXyz temp;
        return cM3d_Cross_CylSph(cyl, this, &temp, out);
    }
    bool cross(const cM3dGTri *param_1) const {
        return cM3d_Cross_SphTri(this, param_1);
    }
    const cXyz& GetC() const { return mCenter; }
    cXyz& GetC() { return mCenter; }
    const cXyz* GetCP() const { return &mCenter; }
    cXyz* GetCP() { return &mCenter; }
    const f32 GetR() const { return mRadius; }
    f32 GetCX() const { return mCenter.x; }
    f32 GetCY() const { return mCenter.y; }
    f32 GetCZ() const { return mCenter.z; }
};  // Size = 0x14

STATIC_ASSERT(0x14 == sizeof(cM3dGSph));

#endif
