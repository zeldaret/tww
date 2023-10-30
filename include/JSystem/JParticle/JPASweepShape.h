#ifndef JPASWEEPSHAPE_H
#define JPASWEEPSHAPE_H

#include "JSystem/JParticle/JPAParticle.h"

class JPASweepShape {
public:
    virtual ~JPASweepShape() {};
    virtual void getType() = 0;
    virtual void getDirType() = 0;
    virtual void getRotType() = 0;
    virtual void getBasePlaneType() = 0;
    virtual void getLife() = 0;
    virtual s16 getRate() = 0;
    virtual void getTiming() = 0;
    virtual void getStep() = 0;
    virtual void getPosRndm() = 0;
    virtual void getVelInfRate() = 0;
    virtual void getBaseVel() = 0;
    virtual void getBaseVelRndm() = 0;
    virtual void getGravity() = 0;
    virtual void isEnableField() = 0;
    virtual void isEnableDrawParent() = 0;
    virtual void isClipOn() = 0;
    virtual void isEnableScaleOut() = 0;
    virtual void isEnableAlphaOut() = 0;
    virtual void isEnableRotate() = 0;
    virtual void isInheritedScale() = 0;
    virtual void isInheritedAlpha() = 0;
    virtual void isInheritedRGB() = 0;
    virtual void getTextureIndex() = 0;
    virtual void getScaleX() = 0;
    virtual void getScaleY() = 0;
    virtual void getPrm() = 0;
    virtual void getEnv() = 0;
    virtual void getPrmAlpha() = 0;
    virtual void getEnvAlpha() = 0;
    virtual void getRotateSpeed() = 0;
    virtual void getInheritScale() = 0;
    virtual void getInheritAlpha() = 0;
    virtual void getInheritRGB() = 0;
};

#endif /* JPASWEEPSHAPE_H */
