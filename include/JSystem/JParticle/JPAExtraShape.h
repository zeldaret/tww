#ifndef JPAEXTRASHAPE_H
#define JPAEXTRASHAPE_H

#include "JSystem/JParticle/JPAParticle.h"

struct JPAExtraShapeData {
    /* 0x00 */ u32 mFlag;
    /* 0x04 */ u32 field_0x04;
    /* 0x08 */ f32 mAlphaInTiming;
    /* 0x0C */ f32 mAlphaOutTiming;
    /* 0x10 */ f32 mAlphaInValue;
    /* 0x14 */ f32 mAlphaBaseValue;
    /* 0x18 */ f32 mAlphaOutValue;
    /* 0x1C */ f32 mAlphaWaveParam1;
    /* 0x20 */ f32 mAlphaWaveParam2;
    /* 0x24 */ f32 mAlphaWaveParam3;
    /* 0x28 */ f32 mAlphaWaveRandom;
    /* 0x2C */ f32 mScaleInTiming;
    /* 0x30 */ f32 mScaleOutTiming;
    /* 0x34 */ f32 mScaleInValueX;
    /* 0x38 */ f32 mScaleOutValueX;
    /* 0x3C */ f32 mScaleInValueY;
    /* 0x40 */ f32 mScaleOutValueY;
    /* 0x44 */ f32 mRandomScale;
    /* 0x48 */ s16 mAnmCycleX;
    /* 0x4A */ s16 mAnmCycleY;
    /* 0x4C */ f32 mRotateAngle;
    /* 0x50 */ f32 mRotateSpeed;
    /* 0x54 */ f32 mRotateRandomAngle;
    /* 0x58 */ f32 mRotateRandomSpeed;
    /* 0x5C */ f32 mRotateDirection;
};

class JPAExtraShape {
public:
    virtual ~JPAExtraShape() {}
    virtual BOOL isEnableScale() = 0;
    virtual BOOL isDiffXY() = 0;
    virtual BOOL isEnableScaleAnmX() = 0;
    virtual BOOL isEnableScaleAnmY() = 0;
    virtual BOOL isEnableScaleBySpeedX() = 0;
    virtual BOOL isEnableScaleBySpeedY() = 0;
    virtual f32 getScaleInTiming() = 0;
    virtual f32 getScaleOutTiming() = 0;
    virtual f32 getScaleInValueX() = 0;
    virtual f32 getScaleInValueY() = 0;
    virtual u8 getAnmTypeX() = 0;
    virtual u8 getAnmTypeY() = 0;
    virtual u32 getAnmCycleX() = 0;
    virtual u32 getAnmCycleY() = 0;
    virtual f32 getIncreaseRateX() = 0;
    virtual f32 getIncreaseRateY() = 0;
    virtual f32 getDecreaseRateX() = 0;
    virtual f32 getDecreaseRateY() = 0;
    virtual u8 getPivotX() = 0;
    virtual u8 getPivotY() = 0;
    virtual f32 getRandomScale() = 0;
    virtual BOOL isEnableAlpha() = 0;
    virtual BOOL isEnableSinWave() = 0;
    virtual f32 getAlphaInTiming() = 0;
    virtual f32 getAlphaOutTiming() = 0;
    virtual f32 getAlphaInValue() = 0;
    virtual f32 getAlphaBaseValue() = 0;
    virtual u8 getAlphaWaveType() = 0;
    virtual f32 getAlphaWaveParam1() = 0;
    virtual f32 getAlphaWaveParam2() = 0;
    virtual f32 getAlphaWaveParam3() = 0;
    virtual f32 getAlphaWaveRandom() = 0;
    virtual f32 getAlphaIncreaseRate() = 0;
    virtual f32 getAlphaDecreaseRate() = 0;
    virtual BOOL isEnableRotate() = 0;
    virtual f32 getRotateAngle() = 0;
    virtual f32 getRotateSpeed() = 0;
    virtual f32 getRotateRandomAngle() = 0;
    virtual f32 getRotateRandomSpeed() = 0;
    virtual f32 getRotateDirection() = 0;
};

class JPAExtraShapeArc : public JPAExtraShape {
public:
    JPAExtraShapeArc(const u8*);
    virtual ~JPAExtraShapeArc() {}
    virtual BOOL isEnableScale() { return (mpData->mFlag & 0x100); }
    virtual BOOL isDiffXY() { return (mpData->mFlag & 0x200); }
    virtual BOOL isEnableScaleAnmX() { return (mpData->mFlag & 0x800); }
    virtual BOOL isEnableScaleAnmY() { return (mpData->mFlag & 0x400); }
    virtual BOOL isEnableScaleBySpeedX() { return (mpData->mFlag & 0x2000); }
    virtual BOOL isEnableScaleBySpeedY() { return (mpData->mFlag & 0x1000); }
    virtual f32 getScaleInTiming() { return mpData->mScaleInTiming; }
    virtual f32 getScaleOutTiming() { return mpData->mScaleOutTiming; }
    virtual f32 getScaleInValueX() { return mpData->mScaleInValueX; }
    virtual f32 getScaleInValueY() { return mpData->mScaleInValueY; }
    virtual u8 getAnmTypeX() { return (mpData->mFlag >> 18) & 0x01; }
    virtual u8 getAnmTypeY() { return (mpData->mFlag >> 19) & 0x01; }
    virtual u32 getAnmCycleX() { return mpData->mAnmCycleX; }
    virtual u32 getAnmCycleY() { return mpData->mAnmCycleY; }
    virtual f32 getIncreaseRateX() { return mIncreaseRateX; }
    virtual f32 getIncreaseRateY() { return mIncreaseRateY; }
    virtual f32 getDecreaseRateX() { return mDecreaseRateX; }
    virtual f32 getDecreaseRateY() { return mDecreaseRateY; }
    virtual u8 getPivotX() { return (mpData->mFlag >> 14) & 0x03; }
    virtual u8 getPivotY() { return (mpData->mFlag >> 16) & 0x03; }
    virtual f32 getRandomScale() { return mpData->mRandomScale; }
    virtual BOOL isEnableAlpha() { return (mpData->mFlag & 0x01); }
    virtual BOOL isEnableSinWave() { return (mpData->mFlag & 0x02); }
    virtual f32 getAlphaInTiming() { return mpData->mAlphaInTiming; }
    virtual f32 getAlphaOutTiming() { return mpData->mAlphaOutTiming; }
    virtual f32 getAlphaInValue() { return mpData->mAlphaInValue; }
    virtual f32 getAlphaBaseValue() { return mpData->mAlphaBaseValue; }
    virtual u8 getAlphaWaveType() { return (mpData->mFlag >> 2) & 0x03; }
    virtual f32 getAlphaWaveParam1() { return mpData->mAlphaWaveParam1; }
    virtual f32 getAlphaWaveParam2() { return mpData->mAlphaWaveParam2; }
    virtual f32 getAlphaWaveParam3() { return mpData->mAlphaWaveParam3; }
    virtual f32 getAlphaWaveRandom() { return mpData->mAlphaWaveRandom; }
    virtual f32 getAlphaIncreaseRate() { return mAlphaIncreaseRate; }
    virtual f32 getAlphaDecreaseRate() { return mAlphaDecreaseRate; }
    virtual BOOL isEnableRotate() { return (mpData->mFlag & 0x01000000); }
    virtual f32 getRotateAngle() { return mpData->mRotateAngle; }
    virtual f32 getRotateSpeed() { return mpData->mRotateSpeed; }
    virtual f32 getRotateRandomAngle() { return mpData->mRotateRandomAngle; }
    virtual f32 getRotateRandomSpeed() { return mpData->mRotateRandomSpeed; }
    virtual f32 getRotateDirection() { return mpData->mRotateDirection; }

public:
    /* 0x04 */ const JPAExtraShapeData * mpData;
    /* 0x08 */ f32 mAlphaIncreaseRate;
    /* 0x0C */ f32 mAlphaDecreaseRate;
    /* 0x10 */ f32 mIncreaseRateX;
    /* 0x14 */ f32 mDecreaseRateX;
    /* 0x18 */ f32 mIncreaseRateY;
    /* 0x1C */ f32 mDecreaseRateY;
};

#endif /* JPAEXTRASHAPE_H */
