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

enum JPAParticleStatus {
    JPAPtclStts_FirstFrame = 0x01,
    JPAPtclStts_Delete = 0x02,
    JPAPtlcStts_Child = 0x04,
    JPAPtclStts_Invisible = 0x08,
    JPAPtclStts_UNK_10 = 0x10,
    JPAPtclStts_UNK_20 = 0x20,
    JPAPtclStts_UNK_40 = 0x40,
    JPAPtclStts_UNK_80 = 0x80,
};

// fake name
struct JPADrawParams {
    /* 0x00 */ JGeometry::TVec3<f32> mAxis;
    /* 0x0C */ f32 mScaleOut;
    /* 0x10 */ f32 mScaleX;
    /* 0x14 */ f32 mScaleY;
    /* 0x18 */ u8 field_0x18[0x20 - 0x18];
    /* 0x20 */ f32 mAlphaOut;
    /* 0x24 */ f32 mAlphaWaveRandom;
    /* 0x28 */ int mLoopOffset;
    /* 0x2C */ GXColor mPrmColor;
    /* 0x30 */ GXColor mEnvColor;
    /* 0x34 */ u16 mRotateAngle;
    /* 0x36 */ s16 mRotateSpeed;
    /* 0x38 */ u8 field_0x38[0x3A - 0x38];
    /* 0x3A */ u16 mTexIdx;
};  // Size: 0x3C

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
    void setOffsetPosition(f32 x, f32 y, f32 z) { mOffsetPosition.set(x, y, z); }
    void setOffsetPosition(const JGeometry::TVec3<f32>& pos) { mOffsetPosition.set(pos); }
    void getOffsetPosition(JGeometry::TVec3<f32>& out) const { out.set(mOffsetPosition); }
    void getLocalPosition(JGeometry::TVec3<f32>& out) const { out.set(mLocalPosition); }
    void getGlobalPosition(JGeometry::TVec3<f32>& out) const { out.set(mGlobalPosition); }
    void getVelVec(JGeometry::TVec3<f32>& out) const { out.set(mVelocity); }
    s32 getAge() const { return mCurFrame; } // TODO: Not sure about this one, especially the cast to s32; this could also be mCurNormTime?
    void calcCB(JPABaseEmitter* emtr) { if (mpCallBack2 != NULL) mpCallBack2->execute(emtr, this); }
    void drawCB(JPABaseEmitter* emtr) { if (mpCallBack2 != NULL) mpCallBack2->draw(emtr, this); }
    void setCallBackPtr(JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*>* cb) { mpCallBack2 = cb; }

    bool checkStatus(u32 flag) { return mStatus & flag; }
    void initStatus(u32 flag) { mStatus = flag; }
    void setStatus(u32 flag) { mStatus |= flag; }
    void clearStatus(u32 flag) { mStatus &= ~flag; }
    void setDeleteParticleFlag() { setStatus(JPAPtclStts_Delete); }
    bool isInvisibleParticle() { return checkStatus(JPAPtclStts_Invisible); }
    void setInvisibleParticleFlag() { setStatus(JPAPtclStts_Invisible); }

    JPADrawParams* getDrawParamPPtr() { return &mDrawParams; }
    void getDrawParamCPtr() {}

    void getWidth() {}
    void getHeight() {}
    void getLifeTime() const {}

public:
    /* 0x00 */ JSULink<JPABaseParticle> mLink;
    /* 0x10 */ JGeometry::TVec3<f32> mOffsetPosition;
    /* 0x1C */ JGeometry::TVec3<f32> mLocalPosition;
    /* 0x28 */ JGeometry::TVec3<f32> mGlobalPosition;
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
    /* 0x8C */ JPADrawParams mDrawParams;
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

#endif /* JPAPARTICLE_H */
