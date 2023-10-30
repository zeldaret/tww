#ifndef JPAEXTRASHAPE_H
#define JPAEXTRASHAPE_H

#include "JSystem/JParticle/JPAParticle.h"

class JPAExtraShape {
public:
    virtual ~JPAExtraShape() {};
    virtual void isEnableScale() = 0;
    virtual void isDiffXY() = 0;
    virtual void isEnableScaleAnmX() = 0;
    virtual void isEnableScaleAnmY() = 0;
    virtual void isEnableScaleBySpeedX() = 0;
    virtual void isEnableScaleBySpeedY() = 0;
    virtual void getScaleInTiming() = 0;
    virtual void getScaleOutTiming() = 0;
    virtual void getScaleInValueX() = 0;
    virtual void getScaleInValueY() = 0;
    virtual void getAnmTypeX() = 0;
    virtual void getAnmTypeY() = 0;
    virtual void getAnmCycleX() = 0;
    virtual void getAnmCycleY() = 0;
    virtual void getIncreaseRateX() = 0;
    virtual void getIncreaseRateY() = 0;
    virtual void getDecreaseRateX() = 0;
    virtual void getDecreaseRateY() = 0;
    virtual u32 getPivotX() = 0;
    virtual u32 getPivotY() = 0;
    virtual void getRandomScale() = 0;
    virtual void isEnableAlpha() = 0;
    virtual void isEnableSinWave() = 0;
    virtual void getAlphaInTiming() = 0;
    virtual void getAlphaOutTiming() = 0;
    virtual void getAlphaInValue() = 0;
    virtual void getAlphaBaseValue() = 0;
    virtual void getAlphaWaveType() = 0;
    virtual void getAlphaWaveParam1() = 0;
    virtual void getAlphaWaveParam2() = 0;
    virtual void getAlphaWaveParam3() = 0;
    virtual void getAlphaWaveRandom() = 0;
    virtual void getAlphaIncreaseRate() = 0;
    virtual void getAlphaDecreaseRate() = 0;
    virtual void isEnableRotate() = 0;
    virtual void getRotateAngle() = 0;
    virtual void getRotateSpeed() = 0;
    virtual void getRotateRandomAngle() = 0;
    virtual void getRotateRandomSpeed() = 0;
    virtual void getRotateDirection() = 0;
};

#endif /* JPAEXTRASHAPE_H */
