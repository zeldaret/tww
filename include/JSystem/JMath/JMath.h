#ifndef JMATH_H
#define JMATH_H

#include "dolphin/mtx/mtx.h"

bool JMANewSinTable(u8 numBits);
void JMAEulerToQuat(s16 x, s16 y, s16 z, Quaternion* out);
void JMAQuatLerp(Quaternion* a, Quaternion* b, f32 t, Quaternion* out);
f32 JMAHermiteInterpolation(f32 frame, f32 time0, f32 value0, f32 tangent0, f32 time1, f32 value1, f32 tangent1);

inline f32 JMAFastReciprocal(f32 value) {
    return __fres(value);
}

inline float __frsqrtes(register double f) {
    register float out;
    // clang-format off
    asm {
        frsqrte out, f
    }
    // clang-format on
    return out;
}

inline f32 JMAFastSqrt(register f32 input) {
    if (input > 0.0f) {
        register f32 out;
        asm {
            frsqrte out, input
        }
        return out * input;
    } else {
        return input;
    }
}

namespace JMath {

inline f32 fastReciprocal(f32 value) {
    return JMAFastReciprocal(value);
}

inline void gekko_ps_copy3(register void* dst, register const void* src) {
    register f32 src0;
    register f32 src1;
    asm {
        psq_l src0, 0(src), 0, 0
        lfs src1, 8(src)
        psq_st src0, 0(dst), 0, 0
        stfs src1, 8(dst)
    };
}

inline void gekko_ps_copy6(register void* dst, register const void* src) {
    register f32 src0;
    register f32 src1;
    register f32 src2;
    asm {
        psq_l src0, 0(src), 0, 0
        psq_l src1, 8(src), 0, 0
        psq_l src2, 16(src), 0, 0
        psq_st src0, 0(dst), 0, 0
        psq_st src1, 8(dst), 0, 0
        psq_st src2, 16(dst), 0, 0
    };
}

inline void gekko_ps_copy12(register void* dst, register const void* src) {
    register f32 src0;
    register f32 src1;
    register f32 src2;
    register f32 src3;
    register f32 src4;
    register f32 src5;
    asm {
        psq_l src0, 0(src), 0, 0
        psq_l src1, 8(src), 0, 0
        psq_l src2, 16(src), 0, 0
        psq_l src3, 24(src), 0, 0
        psq_l src4, 32(src), 0, 0
        psq_l src5, 40(src), 0, 0
        psq_st src0, 0(dst), 0, 0
        psq_st src1, 8(dst), 0, 0
        psq_st src2, 16(dst), 0, 0
        psq_st src3, 24(dst), 0, 0
        psq_st src4, 32(dst), 0, 0
        psq_st src5, 40(dst), 0, 0
    };
}

inline void gekko_ps_copy16(register void* dst, register const void* src) {
    register f32 src0;
    register f32 src1;
    register f32 src2;
    register f32 src3;
    register f32 src4;
    register f32 src5;
    register f32 src6;
    register f32 src7;
    asm {
        psq_l src0, 0(src), 0, 0
        psq_l src1, 8(src), 0, 0
        psq_l src2, 16(src), 0, 0
        psq_l src3, 24(src), 0, 0
        psq_l src4, 32(src), 0, 0
        psq_l src5, 40(src), 0, 0
        psq_l src6, 48(src), 0, 0
        psq_l src7, 56(src), 0, 0
        psq_st src0, 0(dst), 0, 0
        psq_st src1, 8(dst), 0, 0
        psq_st src2, 16(dst), 0, 0
        psq_st src3, 24(dst), 0, 0
        psq_st src4, 32(dst), 0, 0
        psq_st src5, 40(dst), 0, 0
        psq_st src6, 48(dst), 0, 0
        psq_st src7, 56(dst), 0, 0
    };
}

};  // namespace JMath

#endif /* JMATH_H */
