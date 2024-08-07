//
// Generated by dtk
// Translation Unit: jstudio-math.cpp
//

#include "JSystem/JStudio/JStudio/jstudio-math.h"
#include "dolphin/types.h"

namespace JStudio {
namespace math {
    
/* 8026E610-8026E778       .text getRotation_xyz__Q27JStudio4mathFPA4_ffff */
void getRotation_xyz(MtxP param_1, f32 x, f32 y, f32 z) {
    f32 cosx = std::cosf(DEG_TO_RAD(x));
    f32 sinx = std::sinf(DEG_TO_RAD(x));
    f32 cosy = std::cosf(DEG_TO_RAD(y));
    f32 siny = std::sinf(DEG_TO_RAD(y));
    f32 cosz = std::cosf(DEG_TO_RAD(z));
    f32 sinz = std::sinf(DEG_TO_RAD(z));
    f32 cosxcosz = cosx * cosz;
    f32 cosxsinz = cosx * sinz;
    f32 sinxcosz = sinx * cosz;
    f32 sinxsinz = sinx * sinz;

    param_1[0][0] = cosy * cosz;
    param_1[1][0] = cosy * sinz;
    param_1[2][0] = -siny;
    param_1[2][1] = sinx * cosy;
    param_1[2][2] = cosx * cosy;
    param_1[0][1] = ((sinxcosz * siny) - cosxsinz);
    param_1[0][2] = (sinxsinz + (cosxcosz * siny));
    param_1[1][1] = (cosxcosz + (sinxsinz * siny));
    param_1[1][2] = (((cosxsinz) * siny) - sinxcosz);
    param_1[0][3] = 0.0f;
    param_1[1][3] = 0.0f;
    param_1[2][3] = 0.0f;
}

/* 8026E778-8026E7C4       .text rotate_xyz__Q27JStudio4mathFPA4_fPA4_Cffff */
void rotate_xyz(MtxP param_0, CMtxP param_1, f32 param_2, f32 param_3, f32 param_4) {
    Mtx amStack_30;
    getRotation_xyz(amStack_30, param_2, param_3, param_4);
    MTXConcat(amStack_30, param_1, param_0);
}

/* 8026E7C4-8026E81C       .text rotate_y__Q27JStudio4mathFPA4_fPA4_Cff */
void rotate_y(MtxP param_0, CMtxP param_1, f32 param_2) {
    Mtx afStack_38;
    getRotation_y(afStack_38, param_2);
    MTXConcat(afStack_38, param_1, param_0);
}

/* 8026E81C-8026E898       .text getTransformation_SRxyzT__Q27JStudio4mathFPA4_fRC3VecRC3VecRC3Vec */
void getTransformation_SRxyzT(MtxP param_1, const Vec& param_2, const Vec& param_3, const Vec& param_4) {
    Mtx afStack_40;
    MTXScale(afStack_40, param_2.x, param_2.y, param_2.z);
    Mtx amStack_70;
    rotate_xyz(amStack_70, afStack_40, param_3);
    MTXTransApply(amStack_70, param_1, param_4.x, param_4.y, param_4.z);
}

/* 8026E898-8026E8F8       .text getTransformation_RyT__Q27JStudio4mathFPA4_ffRC3Vec */
void getTransformation_RyT(MtxP param_0, f32 param_2, const Vec& param_1) {
    Mtx amStack_40;
    getRotation_y(amStack_40, param_2);
    MTXTransApply(amStack_40, param_0, param_1.x, param_1.y, param_1.z);
}

};  // namespace math
};  // namespace JStudio
