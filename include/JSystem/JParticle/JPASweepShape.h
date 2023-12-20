#ifndef JPASWEEPSHAPE_H
#define JPASWEEPSHAPE_H

#include "JSystem/JParticle/JPAParticle.h"
#include "JSystem/JUtility/TColor.h"

struct JPASweepShapeData {
    /* 0x00 */ u32 mFlag;
    /* 0x04 */ f32 mPosRndm;
    /* 0x08 */ f32 mBaseVel;
    /* 0x0C */ f32 mBaseVelRndm;
    /* 0x10 */ f32 mVelInfRate;
    /* 0x14 */ f32 mGravity;
    /* 0x18 */ f32 mTiming;
    /* 0x1C */ s16 mLife;
    /* 0x1E */ s16 mRate;
    /* 0x20 */ u8 mStep;
    /* 0x24 */ f32 mScaleX;
    /* 0x28 */ f32 mScaleY;
    /* 0x2C */ f32 mRotateSpeed;
    /* 0x30 */ f32 mInheritScale;
    /* 0x34 */ f32 mInheritAlpha;
    /* 0x38 */ f32 mInheritRGB;
    /* 0x3C */ JUtility::TColor mPrm;
    /* 0x40 */ JUtility::TColor mEnv;
    /* 0x44 */ u8 mTextureIndex;
};

class JPASweepShape {
public:
    virtual ~JPASweepShape() {};
    virtual u8 getType() = 0;
    virtual u8 getDirType() = 0;
    virtual u8 getRotType() = 0;
    virtual u8 getBasePlaneType() = 0;
    virtual s16 getLife() = 0;
    virtual s16 getRate() = 0;
    virtual f32 getTiming() = 0;
    virtual u32 getStep() = 0;
    virtual f32 getPosRndm() = 0;
    virtual f32 getVelInfRate() = 0;
    virtual f32 getBaseVel() = 0;
    virtual f32 getBaseVelRndm() = 0;
    virtual f32 getGravity() = 0;
    virtual BOOL isEnableField() = 0;
    virtual BOOL isEnableDrawParent() = 0;
    virtual BOOL isClipOn() = 0;
    virtual BOOL isEnableScaleOut() = 0;
    virtual BOOL isEnableAlphaOut() = 0;
    virtual BOOL isEnableRotate() = 0;
    virtual BOOL isInheritedScale() = 0;
    virtual BOOL isInheritedAlpha() = 0;
    virtual BOOL isInheritedRGB() = 0;
    virtual u8 getTextureIndex() = 0;
    virtual f32 getScaleX() = 0;
    virtual f32 getScaleY() = 0;
    virtual GXColor getPrm() = 0;
    virtual GXColor getEnv() = 0;
    virtual u8 getPrmAlpha() = 0;
    virtual u8 getEnvAlpha() = 0;
    virtual f32 getRotateSpeed() = 0;
    virtual f32 getInheritScale() = 0;
    virtual f32 getInheritAlpha() = 0;
    virtual f32 getInheritRGB() = 0;
};

class JPASweepShapeArc : public JPASweepShape {
public:
    JPASweepShapeArc(const u8*);
    virtual ~JPASweepShapeArc() {};
    virtual u8 getType() { return (mpData->mFlag >> 0) & 0x0F; }
    virtual u8 getDirType() { return (mpData->mFlag >> 4) & 0x07; }
    virtual u8 getRotType() { return (mpData->mFlag >> 7) & 0x07; }
    virtual u8 getBasePlaneType() { return (mpData->mFlag >> 10) & 0x01; }
    virtual s16 getLife() { return mpData->mLife; }
    virtual s16 getRate() { return mpData->mRate; }
    virtual f32 getTiming() { return mpData->mTiming; }
    virtual u32 getStep() { return mpData->mStep; }
    virtual f32 getPosRndm() { return mpData->mPosRndm; }
    virtual f32 getVelInfRate() { return mpData->mVelInfRate; }
    virtual f32 getBaseVel() { return mpData->mBaseVel; }
    virtual f32 getBaseVelRndm() { return mpData->mBaseVelRndm; }
    virtual f32 getGravity() { return mpData->mGravity; }
    virtual BOOL isEnableField() { return (mpData->mFlag & 0x00200000); }
    virtual BOOL isEnableDrawParent() { return (mpData->mFlag & 0x00080000); }
    virtual BOOL isClipOn() { return (mpData->mFlag & 0x00100000); }
    virtual BOOL isEnableScaleOut() { return (mpData->mFlag & 0x00400000); }
    virtual BOOL isEnableAlphaOut() { return (mpData->mFlag & 0x00800000); }
    virtual BOOL isEnableRotate() { return (mpData->mFlag & 0x01000000); }
    virtual BOOL isInheritedScale() { return (mpData->mFlag & 0x00010000); }
    virtual BOOL isInheritedAlpha() { return (mpData->mFlag & 0x00020000); }
    virtual BOOL isInheritedRGB() { return (mpData->mFlag & 0x00040000); }
    virtual u8 getTextureIndex() { return mpData->mTextureIndex; }
    virtual f32 getScaleX() { return mpData->mScaleX; }
    virtual f32 getScaleY() { return mpData->mScaleY; }
    virtual GXColor getPrm() { return mpData->mPrm; }
    virtual GXColor getEnv() { return mpData->mEnv; }
    virtual u8 getPrmAlpha() { return mpData->mPrm.a; }
    virtual u8 getEnvAlpha() { return mpData->mEnv.a; }
    virtual f32 getRotateSpeed() { return mpData->mRotateSpeed; }
    virtual f32 getInheritScale() { return mpData->mInheritScale; }
    virtual f32 getInheritAlpha() { return mpData->mInheritAlpha; }
    virtual f32 getInheritRGB() { return mpData->mInheritRGB; }

public:
    /* 0x04 */ const JPASweepShapeData* mpData;
};

#endif /* JPASWEEPSHAPE_H */
