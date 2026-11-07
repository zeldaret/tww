#ifndef JSTUDIO_MATH_H
#define JSTUDIO_MATH_H

#include "dolphin/mtx.h"
#include "math.h"

namespace JStudio {
namespace math {
    void getRotation_xyz(MtxP, f32, f32, f32);
    void rotate_xyz(MtxP, CMtxP, f32, f32, f32);
    void rotate_y(MtxP, CMtxP, f32);
    void getTransformation_SRxyzT(MtxP, const Vec&, const Vec&, const Vec&);
    void getTransformation_RyT(MtxP, f32, const Vec&);

    inline void getRotation_y(Mtx param_0, f32 param_1) {
        MTXRotRad(param_0, 0x79, DEG_TO_RAD(param_1));
    }

    inline void rotate_xyz(MtxP param_0, CMtxP param_1, const Vec& param_2) {
        rotate_xyz(param_0, param_1, param_2.x, param_2.y, param_2.z);
    }
};
};  // namespace JStudio

#endif /* JSTUDIO_MATH_H */
