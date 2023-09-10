#ifndef C_M3D_G_TRI_H_
#define C_M3D_G_TRI_H_

#include "SSystem/SComponent/c_m3d_g_pla.h"
#include "dolphin/types.h"

class cM3dGCyl;

struct cM3dGTriS {
    Vec a;
    Vec b;
    Vec c;
};

class cM3dGTri : public cM3dGPla {
    // private:
public:
    // cM3dGPla mPlane;
    Vec mA;
    Vec mB;
    Vec mC;

    cM3dGTri(const Vec *pA, const Vec *pB, const Vec *pC);
    bool cross(const cM3dGCyl*, Vec*) const;
};

#endif
