#ifndef J3DSTRUCT_H
#define J3DSTRUCT_H

#include "dolphin/gx/GXStruct.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/mtx/mtx44.h"
#include "dolphin/mtx/vec.h"
#include "global.h"

class J3DLightInfo {
public:
    void operator=(J3DLightInfo const& other) {
        mLightPosition = other.mLightPosition;
        mLightDirection = other.mLightDirection;
        mColor = other.mColor;
        mCosAtten = other.mCosAtten;
        mDistAtten = other.mDistAtten;
    }

    /* 0x00 */ Vec mLightPosition;
    /* 0x0C */ Vec mLightDirection;
    /* 0x18 */ GXColor mColor;
    /* 0x1C */ Vec mCosAtten;
    /* 0x28 */ Vec mDistAtten;
};  // Size = 0x34

struct J3DTextureSRTInfo {
    /* 0x00 */ f32 mScaleX;
    /* 0x04 */ f32 mScaleY;
    /* 0x08 */ s16 mRotation;
    /* 0x0C */ f32 mTranslationX;
    /* 0x10 */ f32 mTranslationY;
};  // Size: 0x14

enum J3DTexMtxMode {
    J3DTexMtxMode_None,
    J3DTexMtxMode_EnvmapBasic,
    J3DTexMtxMode_ProjmapBasic,
    J3DTexMtxMode_ViewProjmapBasic,
    J3DTexMtxMode_Unknown4,
    J3DTexMtxMode_Unknown5,
    J3DTexMtxMode_EnvmapOld,
    J3DTexMtxMode_Envmap,
    J3DTexMtxMode_Projmap,
    J3DTexMtxMode_ViewProjmap,
    J3DTexMtxMode_EnvmapOldEffectMtx,
    J3DTexMtxMode_EnvmapEffectMtx,
};

struct J3DTexMtxInfo {
    void operator=(J3DTexMtxInfo const& other) {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                mEffectMtx[i][j] = other.mEffectMtx[i][j];
            }
        }
        mCenter = other.mCenter;
        mProjection = other.mProjection;
        mInfo = other.mInfo;
        mSRT = other.mSRT;
    }
    void setEffectMtx(Mtx m) {
        mEffectMtx[0][0] = m[0][0];
        mEffectMtx[0][1] = m[0][1];
        mEffectMtx[0][2] = m[0][2];
        mEffectMtx[0][3] = m[0][3];
        mEffectMtx[1][0] = m[1][0];
        mEffectMtx[1][1] = m[1][1];
        mEffectMtx[1][2] = m[1][2];
        mEffectMtx[1][3] = m[1][3];
        mEffectMtx[2][0] = m[2][0];
        mEffectMtx[2][1] = m[2][1];
        mEffectMtx[2][2] = m[2][2];
        mEffectMtx[2][3] = m[2][3];
        mEffectMtx[3][2] = 0.0f;
        mEffectMtx[3][1] = 0.0f;
        mEffectMtx[3][0] = 0.0f;
        mEffectMtx[3][3] = 1.0f;
    }

    /* 0x00 */ u8 mProjection;
    /* 0x01 */ u8 mInfo;
    /* 0x02 */ u8 padding[2];
    /* 0x04 */ Vec mCenter;
    /* 0x10 */ J3DTextureSRTInfo mSRT;
    /* 0x24 */ Mtx44 mEffectMtx;
};  // Size: 0x64

struct J3DIndTexMtxInfo {
    void operator=(const J3DIndTexMtxInfo& other) {
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 3; j++) {
                mOffsetMtx[i][j] = other.mOffsetMtx[i][j];
            }
        }
        mScaleExp = other.mScaleExp;
    }
    /* 0x00 */ Mtx23 mOffsetMtx;
    /* 0x18 */ s8 mScaleExp;
};  // Size: 0x1C

struct J3DFogInfo {
    void operator=(const J3DFogInfo& other) {
        mType = other.mType;
        mAdjEnable = other.mAdjEnable;
        mCenter = other.mCenter;
        mStartZ = other.mStartZ;
        mEndZ = other.mEndZ;
        mNearZ = other.mNearZ;
        mFarZ = other.mFarZ;
        mColor = other.mColor;
        for (int i = 0; i < 10; i++) {
            mFogAdjTable[i] = other.mFogAdjTable[i];
        }
    }

    /* 0x00 */ u8 mType;
    /* 0x01 */ u8 mAdjEnable;
    /* 0x02 */ u16 mCenter;
    /* 0x04 */ f32 mStartZ;
    /* 0x08 */ f32 mEndZ;
    /* 0x0C */ f32 mNearZ;
    /* 0x10 */ f32 mFarZ;
    /* 0x14 */ GXColor mColor;
    /* 0x18 */ u16 mFogAdjTable[10];
};  // Size: 0x2C

struct J3DNBTScaleInfo {
    /* 0x0 */ u8 mbHasScale;
    /* 0x4 */ Vec mScale;

    inline void operator=(const J3DNBTScaleInfo & other) { mbHasScale = other.mbHasScale; mScale = other.mScale; }
};  // Size: 0x10

struct J3DIndTexOrderInfo {
    void operator=(const J3DIndTexOrderInfo& other) {
        mCoord = other.mCoord;
        mMap = other.mMap;
    }

    /* 0x0 */ u8 mCoord;
    /* 0x1 */ u8 mMap;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
};

struct J3DTevSwapModeInfo {
    /* 0x0 */ u8 field_0x0 ALIGN_DECL(4);
    /* 0x1 */ u8 field_0x1;
};

struct J3DTevSwapModeTableInfo {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
};

struct J3DTevStageInfo {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 field_0x6;
    /* 0x7 */ u8 field_0x7;
    /* 0x8 */ u8 field_0x8;
    /* 0x9 */ u8 field_0x9;
    /* 0xA */ u8 field_0xa;
    /* 0xB */ u8 field_0xb;
    /* 0xC */ u8 field_0xc;
    /* 0xD */ u8 field_0xd;
    /* 0xE */ u8 field_0xe;
    /* 0xF */ u8 field_0xf;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
};

struct J3DIndTevStageInfo {
    /* 0x0 */ u8 mIndStage ALIGN_DECL(4);
    /* 0x1 */ u8 mIndFormat;
    /* 0x2 */ u8 mBiasSel;
    /* 0x3 */ u8 mMtxSel;
    /* 0x4 */ u8 mWrapS;
    /* 0x5 */ u8 mWrapT;
    /* 0x6 */ u8 mPrev;
    /* 0x7 */ u8 mLod;
    /* 0x8 */ u8 mAlphaSel;
};

struct J3DTexCoordInfo {
    /* 0x0 */ u8 mTexGenType ALIGN_DECL(4);
    /* 0x1 */ u8 mTexGenSrc;
    /* 0x2 */ u8 mTexGenMtx;
};

struct J3DIndTexCoordScaleInfo {
    void operator=(const J3DIndTexCoordScaleInfo& other) {
        mScaleS = other.mScaleS;
        mScaleT = other.mScaleT;
    }

    /* 0x0 */ u8 mScaleS;
    /* 0x1 */ u8 mScaleT;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
};

struct J3DBlendInfo {
    /* 0x0 */ u8 mBlendMode;
    /* 0x1 */ u8 mSrcFactor;
    /* 0x2 */ u8 mDstFactor;
    /* 0x3 */ u8 mLogicOp;
};

struct J3DTevOrderInfo {
    /* 0x0 */ u8 mTexCoord ALIGN_DECL(2);
    /* 0x1 */ u8 mTexMap;
    /* 0x2 */ u8 mColorChan;
};

struct J3DColorChanInfo {
    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 field_0x1;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 field_0x3;
    /* 0x4 */ u8 field_0x4;
    /* 0x5 */ u8 field_0x5;
    /* 0x6 */ u8 field_0x6;
    /* 0x7 */ u8 field_0x7;
};

struct J3DZModeInfo {
    /* 0x0 */ u8 mCompareEnable;
    /* 0x1 */ u8 mFunc;
    /* 0x2 */ u8 mUpdateEnable;
};

STATIC_ASSERT(sizeof(J3DTevStageInfo) == 0x14);

#endif /* J3DSTRUCT_H */
