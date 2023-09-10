#ifndef C_M2D_G_BOX_H
#define C_M2D_G_BOX_H

#include "SSystem/SComponent/c_xyz.h"

class cM2dGBox {
public:
    cXy mP0, mP1;

    void Set(cXy& pA, cXy& pB);
    f32 GetLen(const cXy& pXy) const;
};

#endif
