#ifndef C_M3D_G_PLA_H_
#define C_M3D_G_PLA_H_

#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_m3d.h"
#include "dolphin/mtx/vec.h"

// Plane with a normal
class cM3dGPla {
public:
    /* 0x00 */ cXyz mNormal;
    /* 0x0C */ f32 mD;
    /* 0x10 */ /* vtable */

public:
    cM3dGPla() {}
    void CalcAngleXz(short* pAngleX, short* pAngleY) const;
    void SetupNP0(const Vec&, const Vec&);
    
    f32 getPlaneFunc(const Vec *p) const {
        return mD + VECDotProduct(&mNormal, p);
    }

    cXyz* GetNP() { return &mNormal; }
    const cXyz* GetNP() const { return &mNormal; }
    f32 GetD() const { return mD; }
    float getCrossY(const cXyz& i_axis) const { // fake inline
        return (-mNormal.x * i_axis.x - mNormal.z * i_axis.z - mD) / mNormal.y;
    }
    void getCrossY(const cXyz& i_axis, float* i_value) const {
        if (!cM3d_IsZero(mNormal.y)) {
            *i_value = getCrossY(i_axis);
        }
    }
    f32 getSignedLenPos(const cXyz* param_1) const {
        return cM3d_SignedLenPlaAndPos(this, param_1);
    }
    
    virtual ~cM3dGPla() {}

    // TODO
    void Set(const cM3dGPla*) {}
    void SetupFrom3Vtx(const Vec*, const Vec*, const Vec*) {}
    cM3dGPla(const cXyz*, float) {}
    void cross(const cM3dGLin&, Vec&) const {}
    void getCrossYLessD(const Vec&, float*) const {}
    void getCrossY_NonIsZero(const cXyz&) const {}
    void operator=(const cM3dGPla&) {}
};  // Size: 0x14

#endif
