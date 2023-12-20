#ifndef JPAPARTICLE_H
#define JPAPARTICLE_H

#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "JSystem/JGeometry.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/gx/GXStruct.h"

class JKRHeap;
class JPABaseEmitter;
class JPABaseParticle;
class JPAEmitterCallBack;
class JPAEmitterManager;
class JPAParticleCallBack;
class JPAResourceManager;
struct JPAEmitterWorkData;

template<typename T>
class JPACallBackBase;
template<typename T, typename U>
class JPACallBackBase2;

class JPABaseParticle {
public:
    void initParticle();
    void initChild(JPABaseParticle*);
    void incFrame();
    void calcVelocity();
    void calcPosition();
    bool checkCreateChild();
    JSULink<JPABaseParticle>* getLinkBufferPtr() { return &mLink; }

    ~JPABaseParticle() {}
    JPABaseParticle() : mLink(this), mCurFrame(0.0f) {}
    void setOffsetPosition(f32 x, f32 y, f32 z) { mGlobalPosition.set(x, y, z); }
    void setOffsetPosition(const JGeometry::TVec3<f32>& pos) { mGlobalPosition.set(pos); }

    void calcCB(JPABaseEmitter*) {}
    void checkStatus(u32) {}
    void clearStatus(u32) {}
    void drawCB(JPABaseEmitter*) {}
    void getAge() const {}
    void getDrawParamCPtr() {}
    void getDrawParamPPtr() {}
    void getGlobalPosition(JGeometry::TVec3<f32>&) const {}
    void getHeight() {}
    void getLifeTime() const {}
    void getLocalPosition(JGeometry::TVec3<f32>&) const {}
    void getOffsetPosition(JGeometry::TVec3<f32>&) const {}
    void getVelVec(JGeometry::TVec3<f32>&) const {}
    void getWidth() {}
    void initStatus(u32) {}
    void isInvisibleParticle() {}
    void setCallBackPtr(JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*>*) {}
    void setDeleteParticleFlag() {}
    void setInvisibleParticleFlag() {}
    void setStatus(u32) {}

public:
    /* 0x00 */ JSULink<JPABaseParticle> mLink;
    /* 0x10 */ JGeometry::TVec3<f32> mGlobalPosition;
    /* 0x1C */ JGeometry::TVec3<f32> mLocalPosition;
    /* 0x28 */ JGeometry::TVec3<f32> mPosition;
    /* 0x34 */ JGeometry::TVec3<f32> mVelocity;
    /* 0x40 */ JGeometry::TVec3<f32> mBaseVel;
    /* 0x4C */ JGeometry::TVec3<f32> mAccel;
    /* 0x58 */ JGeometry::TVec3<f32> mFieldVel;
    /* 0x64 */ JGeometry::TVec3<f32> mFieldAccel;
    /* 0x70 */ f32 mAirResist;
    /* 0x74 */ f32 mMoment;
    /* 0x78 */ f32 mCurFrame;
    /* 0x7C */ f32 mLifeTime;
    /* 0x80 */ f32 mCurNormTime;
    /* 0x84 */ f32 mFieldDrag;
    /* 0x88 */ f32 mDrag;
    /* 0x8C */ JGeometry::TVec3<f32> mAxis;
    /* 0x98 */ f32 mScaleOut;
    /* 0x9C */ f32 mScaleX;
    /* 0xA0 */ f32 mScaleY;
    /* 0xA4 */ u8 field_0xA4[0xAC - 0xA4];
    /* 0xAC */ f32 mAlphaOut;
    /* 0xB0 */ f32 mAlphaWaveRandom;
    /* 0xB4 */ int mLoopOffset;
    /* 0xB8 */ GXColor mPrmColor;
    /* 0xBC */ GXColor mEnvColor;
    /* 0xC0 */ u16 mRotateAngle;
    /* 0xC2 */ s16 mRotateSpeed;
    /* 0xC4 */ u8 field_0xC4[0xC6 - 0xC4];
    /* 0xC6 */ u16 mTexIdx;
    /* 0xC8 */ JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*>* mpCallBack2;
    /* 0xCC */ u32 mStatus;
    /* 0xD0 */ u32 field_0xd0;
};

class JPAParticleCallBack {
public:
    JPAParticleCallBack() {}
    virtual ~JPAParticleCallBack();
    virtual void execute(JPABaseEmitter*, JPABaseParticle*);
    virtual void draw(JPABaseEmitter*, JPABaseParticle*);
};

// not sure where this belongs
static inline u32 COLOR_MULTI(u32 a, u32 b) {
    return ((a * (b + 1)) * 0x10000) >> 24;
}

#endif /* JPAPARTICLE_H */