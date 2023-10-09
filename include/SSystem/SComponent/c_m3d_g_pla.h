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
    /* 0x10   vtable */

    cM3dGPla() {}
    void CalcAngleXz(short* pAngleX, short* pAngleY) const;
    void SetupNP0(const Vec&, const Vec&);
    
    f32 getPlaneFunc(const Vec *p) const {
        return mD + VECDotProduct(&mNormal, p);
    }

    const cXyz * GetNP() const { return &mNormal; }
    f32 getCrossY(const cXyz& i_axis, float* i_value) const {
        if (!cM3d_IsZero(mNormal.y)) {
            *i_value = (-mNormal.x * i_axis.x -
                         mNormal.z * i_axis.z -
                         mD) / mNormal.y;
        }
    }
    
    virtual ~cM3dGPla() {}
};

#endif
