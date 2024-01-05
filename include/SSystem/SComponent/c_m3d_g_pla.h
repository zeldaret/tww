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
    void getCrossY(const cXyz& i_axis, f32* i_value) const {
        if (!cM3d_IsZero(mNormal.y)) {
            *i_value = (-mNormal.x * i_axis.x - mNormal.z * i_axis.z - mD) / mNormal.y;
        }
    }
    f32 getCrossY_NonIsZero(const cXyz& i_axis) const {
        return (-mNormal.x * i_axis.x - mNormal.z * i_axis.z - mD) / mNormal.y;
    }
    bool getCrossYLessD(const Vec& i_axis, f32* i_value) const {
        if (cM3d_IsZero(mNormal.y)) {
            return false;
        }
        *i_value = (-mNormal.x * i_axis.x - mNormal.z * i_axis.z) / mNormal.y;
        return true;
    }
    f32 getSignedLenPos(const cXyz* param_1) const {
        return cM3d_SignedLenPlaAndPos(this, param_1);
    }
    
    virtual ~cM3dGPla() {}

    // TODO
    void Set(const cM3dGPla*) {}
    void SetupFrom3Vtx(const Vec*, const Vec*, const Vec*) {}
    cM3dGPla(const cXyz*, f32) {}
    void cross(const cM3dGLin&, Vec&) const {}
};  // Size: 0x14

#endif
