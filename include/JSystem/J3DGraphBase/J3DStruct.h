#ifndef J3DSTRUCT_H
#define J3DSTRUCT_H

#include "dolphin/gx/GXStruct.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/mtx/mtx44.h"
#include "dolphin/mtx/vec.h"

class J3DLightInfo {
public:
    /* 803256C4 */ void operator=(J3DLightInfo const&);

    /* 0x00 */ Vec mLightPosition;
    /* 0x0C */ Vec mLightDirection;
    /* 0x18 */ GXColor mColor;
    /* 0x1C */ Vec mCosAtten;
    /* 0x28 */ Vec mDistAtten;
};  // Size = 0x34

extern "C" extern J3DLightInfo const j3dDefaultLightInfo;

class J3DLightObj {
public:
    /* 80018C0C */ J3DLightObj() { mInfo = j3dDefaultLightInfo; }
    /* 80323590 */ void load(u32) const;

    J3DLightInfo& getLightInfo() { return mInfo; }
    J3DLightObj& operator=(J3DLightObj const& other) {
        mInfo = other.mInfo;
        return *this;
    }

    /* 0x00 */ J3DLightInfo mInfo;
    /* 0x34 */ u8 field_0x34[64];
};  // Size = 0x74

struct J3DTextureSRTInfo {
    /* 0x00 */ f32 mScaleX;
    /* 0x04 */ f32 mScaleY;
    /* 0x08 */ s16 mRotation;
    /* 0x0C */ f32 mTranslationX;
    /* 0x10 */ f32 mTranslationY;
};  // Size: 0x14

struct J3DTexMtxInfo {
    /* 80325718 */ void operator=(J3DTexMtxInfo const&);
    /* 80325794 */ void setEffectMtx(Mtx);

    /* 0x00 */ u8 mProjection;
    /* 0x01 */ s8 mInfo;
    /* 0x04 */ Vec mCenter;
    /* 0x10 */ J3DTextureSRTInfo mSRT;
    /* 0x24 */ Mtx44 mEffectMtx;    
};  // Size: 0x64

struct J3DIndTexMtxInfo {
    /* 0x00 */ Mtx23 field_0x0;
    /* 0x18 */ u8 field_0x18;
};  // Size: 0x1C

struct J3DFogInfo {
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

#endif /* J3DSTRUCT_H */
