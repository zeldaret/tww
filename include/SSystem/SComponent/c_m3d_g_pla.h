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
    void SetupNP0(const Vec& pNormal, const Vec& pPoint);
    
    f32 getPlaneFunc(const Vec *p) const {
        return mD + VECDotProduct(&mNormal, p);
    }

    cXyz* GetNP() { return &mNormal; }
    const cXyz* GetNP() const { return &mNormal; }
    f32 GetD() const { return mD; }
    bool getCrossY(const cXyz& i_axis, f32* i_value) const {
        if (cM3d_IsZero(mNormal.y)) {
            return false;
        }
        *i_value = (-mNormal.x * i_axis.x - mNormal.z * i_axis.z - mD) / mNormal.y;
        return true;
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
    void Set(const cM3dGPla* pla) {
        mNormal = *pla->GetNP();
        mD = pla->GetD();
    }
    void SetupFrom3Vtx(const Vec* a, const Vec* b, const Vec* c) {
        cM3d_CalcPla(a, b, c, &mNormal, &mD);
    }
    
    virtual ~cM3dGPla() {}

    // TODO
    cM3dGPla(const cXyz*, f32) {}
    void cross(const cM3dGLin&, Vec&) const {}
};  // Size: 0x14

#endif
