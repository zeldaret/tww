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
    void SetC(const cXyz&);
    void SetR(f32);
    bool cross(const cM3dGSph*, cXyz*) const;
    bool cross(const cM3dGCyl*, cXyz*) const;
    bool cross(const cM3dGSph*, f32*) const;
    const cXyz& GetC(void) const { return mCenter; }
    const cXyz* GetCP() const { return &mCenter; }
    const f32 GetR(void) const { return mRadius; }
    f32 GetCX(void) const { return mCenter.x; }
    f32 GetCY(void) const { return mCenter.y; }
    f32 GetCZ(void) const { return mCenter.z; }
};  // Size = 0x14

STATIC_ASSERT(0x14 == sizeof(cM3dGSph));

// additional symbols needed for cM3dGSph
extern "C" {
void Set__8cM3dGSphFRC4cXyzf(void);
}

#endif
