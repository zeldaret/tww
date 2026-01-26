#ifndef J3DTRANSFORM_H
#define J3DTRANSFORM_H

#include "JSystem/JGeometry.h"
#include "dolphin/mtx/mtxvec.h"

struct J3DTextureSRTInfo;

struct J3DTransformInfo {
    /* 0x00 */ Vec mScale;
    /* 0x0C */ SVec mRotation;
    /* 0x14 */ Vec mTranslate;

    inline J3DTransformInfo& operator=(const J3DTransformInfo& b) {
        mScale = b.mScale;
        mRotation = b.mRotation;
        mTranslate = b.mTranslate;
        return *this;
    }
};  // Size: 0x20

extern J3DTransformInfo const j3dDefaultTransformInfo;
extern Vec const j3dDefaultScale;
extern Mtx const j3dDefaultMtx;
extern f32 PSMulUnit01[];

void J3DGQRSetup7(u32 param_0, u32 param_1, u32 param_2, u32 param_3);
f32 J3DCalcZValue(MtxP m, Vec v);
void J3DCalcBBoardMtx(Mtx);
void J3DCalcYBBoardMtx(Mtx);
void J3DPSCalcInverseTranspose(f32 (*param_0)[4], f32 (*param_1)[3]);
void J3DGetTranslateRotateMtx(J3DTransformInfo const&, Mtx);
void J3DGetTranslateRotateMtx(s16, s16, s16, f32, f32, f32, Mtx);
void J3DGetTextureMtx(const J3DTextureSRTInfo&, Vec, Mtx);
void J3DGetTextureMtxOld(const J3DTextureSRTInfo&, Vec, Mtx);
void J3DGetTextureMtxMaya(const J3DTextureSRTInfo&, Mtx);
void J3DGetTextureMtxMayaOld(const J3DTextureSRTInfo&, Mtx);
void J3DScaleNrmMtx(Mtx, const Vec&);
void J3DScaleNrmMtx33(Mtx33, const Vec&);
void J3DMtxProjConcat(Mtx, Mtx, Mtx);
void J3DPSMtx33Copy(Mtx3P src, Mtx3P dst);
void J3DPSMtx33CopyFrom34(MtxP src, Mtx3P dst);

inline void J3DPSMulMtxVec(register MtxP mtx, register Vec* vec, register Vec* dst) {
#ifdef __MWERKS__
    asm {
        psq_l f0, 0(vec), 0, 0
        psq_l f2, 0(mtx), 0, 0
        psq_l f1, 8(vec), 1, 0
        ps_mul f4, f2, f0
        psq_l f3, 8(mtx), 0, 0
        ps_madd f5, f3, f1, f4
        psq_l f8, 16(mtx), 0, 0
        ps_sum0 f6, f5, f6, f5
        psq_l f9, 24(mtx), 0, 0
        ps_mul f10, f8, f0
        psq_st f6, 0(dst), 1, 0
        ps_madd f11, f9, f1, f10
        psq_l f2, 32(mtx), 0, 0
        ps_sum0 f12, f11, f12, f11
        psq_l f3, 40(mtx), 0, 0
        ps_mul f4, f2, f0
        psq_st f12, 4(dst), 1, 0
        ps_madd f5, f3, f1, f4
        ps_sum0 f6, f5, f6, f5
        psq_st f6, 8(dst), 1, 0
    }
#endif
}

inline void J3DPSMulMtxVec(register MtxP mtx, register S16Vec* vec, register S16Vec* dst) {
#ifdef __MWERKS__
    asm {
        psq_l f0, 0(vec), 0, 7
        psq_l f2, 0(mtx), 0, 0
        psq_l f1, 4(vec), 1, 7
        ps_mul f4, f2, f0
        psq_l f3, 8(mtx), 0, 0
        ps_madd f5, f3, f1, f4
        psq_l f8, 16(mtx), 0, 0
        ps_sum0 f6, f5, f6, f5
        psq_l f9, 24(mtx), 0, 0
        ps_mul f10, f8, f0
        psq_st f6, 0(dst), 1, 7
        ps_madd f11, f9, f1, f10
        psq_l f2, 32(mtx), 0, 0
        ps_sum0 f12, f11, f12, f11
        psq_l f3, 40(mtx), 0, 0
        ps_mul f4, f2, f0
        psq_st f12, 2(dst), 1, 7
        ps_madd f5, f3, f1, f4
        ps_sum0 f6, f5, f6, f5
        psq_st f6, 4(dst), 1, 7
    }
#endif
}

// regalloc issues
inline void J3DPSMulMtxVec(register Mtx3P mtx, register Vec* vec, register Vec* dst) {
#ifdef __MWERKS__
    asm {
        lis r6, PSMulUnit01@ha
        psq_l f0, 0(vec), 0, 0
        addi r6, r6, PSMulUnit01@l
        psq_l f2, 0(mtx), 0, 0
        psq_l f13, 0(r6), 0, 0
        psq_l f1, 8(vec), 1, 0
        ps_add f1, f13, f1
        psq_l f3, 8(mtx), 1, 0
        ps_mul f4, f2, f0
        psq_l f8, 12(mtx), 0, 0
        ps_madd f5, f3, f1, f4
        ps_sum0 f6, f5, f6, f5
        psq_l f9, 20(mtx), 1, 0
        ps_mul f10, f8, f0
        psq_st f6, 0(dst), 1, 0
        ps_madd f11, f9, f1, f10
        psq_l f2, 24(mtx), 0, 0
        ps_sum0 f12, f11, f12, f11
        psq_l f3, 32(mtx), 1, 0
        ps_mul f4, f2, f0
        psq_st f12, 4(dst), 1, 0
        ps_madd f5, f3, f1, f4
        ps_sum0 f6, f5, f6, f5
        psq_st f6, 8(dst), 1, 0
    }
#endif
}

// regalloc issues
inline void J3DPSMulMtxVec(register Mtx3P mtx, register S16Vec* vec, register S16Vec* dst) {
#ifdef __MWERKS__
    asm {
        lis r6, PSMulUnit01@ha
        psq_l f0, 0(vec), 0, 7
        addi r6, r6, PSMulUnit01@l
        psq_l f2, 0(mtx), 0, 0
        psq_l f13, 0(r6), 0, 0
        psq_l f1, 4(vec), 1, 7
        ps_add f1, f13, f1
        psq_l f3, 8(mtx), 1, 0
        ps_mul f4, f2, f0
        psq_l f8, 12(mtx), 0, 0
        ps_madd f5, f3, f1, f4
        ps_sum0 f6, f5, f6, f5
        psq_l f9, 20(mtx), 1, 0
        ps_mul f10, f8, f0
        psq_st f6, 0(dst), 1, 7
        ps_madd f11, f9, f1, f10
        psq_l f2, 24(mtx), 0, 0
        ps_sum0 f12, f11, f12, f11
        psq_l f3, 32(mtx), 1, 0
        ps_mul f4, f2, f0
        psq_st f12, 2(dst), 1, 7
        ps_madd f5, f3, f1, f4
        ps_sum0 f6, f5, f6, f5
        psq_st f6, 4(dst), 1, 7
    }
#endif
}

#endif /* J3DTRANSFORM_H */
