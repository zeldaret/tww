#ifndef C_M3D_G_PLA_H_
#define C_M3D_G_PLA_H_

#include "SSystem/SComponent/c_xyz.h"

// Plane with a normal
class cM3dGPla {
public:
    /* 0x00 */ cXyz mNormal;
    /* 0x0C */ f32 mD;
    /* 0x10   vtable */

    cM3dGPla() {}
    void CalcAngleXz(short* pAngleX, short* pAngleY) const;
    void SetupNP0(const Vec&, const Vec&);
    
    virtual ~cM3dGPla() {}
};

#endif
