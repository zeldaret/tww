#ifndef JPAEMITTER_H
#define JPAEMITTER_H

#include "JSystem/JParticle/JPADraw.h"
#include "JSystem/JParticle/JPAField.h"
#include "JSystem/JParticle/JPAMath.h"
#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JMath/random.h"
#include "JSystem/JGeometry.h"
#include "JSystem/TPosition3.hh"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/mtx/mtx.h"

class JPADynamicsBlock;
class JPABaseShape;
class JPAExtraShape;
class JPASweepShape;
class JPAExTexShape;
class JPAKeyBlock;
class JPAFieldBlock;
class JPABaseEmitter;
class JPATextureResource;

class JPADataBlockLinkInfo {
public:
    JPADataBlockLinkInfo() {
        dynBlock = NULL;
        bspBlock = NULL;
        espBlock = NULL;
        sspBlock = NULL;
        etxBlock = NULL;
        keyBlocks = NULL;
        fldBlocks = NULL;
        texDataBase = NULL;
        fldNum = NULL;
        mTextureNum = NULL;
        keyNum = 0;
    }

    JPAFieldBlock ** getField() { return fldBlocks; }
    u8 getFieldNum() { return fldNum; }
    JPADynamicsBlock * getDynamics() { return dynBlock; }
    JPASweepShape * getSweepShape() { return sspBlock; }
    u8 getKeyNum() { return keyNum; }
    JPAKeyBlock ** getKey() { return keyBlocks; }
    JPAExtraShape * getExtraShape() { return espBlock; }
    u16 * getTextureDataBase() { return texDataBase; }
    JPAExTexShape * getExTexShape() { return etxBlock; }
    JPABaseShape * getBaseShape() { return bspBlock; }
    u8 getTextureNum() { return mTextureNum; }

public:
    /* 0x00 */ JPADynamicsBlock * dynBlock;
    /* 0x04 */ JPABaseShape * bspBlock;
    /* 0x08 */ JPAExtraShape * espBlock;
    /* 0x0C */ JPASweepShape * sspBlock;
    /* 0x10 */ JPAExTexShape * etxBlock;
    /* 0x14 */ JPAKeyBlock ** keyBlocks;
    /* 0x18 */ JPAFieldBlock ** fldBlocks;
    /* 0x1C */ u16 * texDataBase;
    /* 0x20 */ u8 fldNum;
    /* 0x21 */ u8 mTextureNum;
    /* 0x22 */ u8 keyNum;
    /* 0x23 */ u8 field_0x23;
};

enum {
    JPAEmtrStts_StopEmit = 0x01,
    JPAEmtrStts_StopCalc = 0x02,
    JPAEmtrStts_StopDraw = 0x04,
    JPAEmtrStts_EnableDeleteEmitter = 0x08,
    JPAEmtrStts_FirstEmit = 0x10,
    JPAEmtrStts_RateStepEmit = 0x20,
    JPAEmtrStts_Immortal = 0x40,
};

template<typename T>
class JPACallBackBase {
public:
    JPACallBackBase() {}
    virtual ~JPACallBackBase() {}

    inline virtual void init(T);
    inline virtual void execute(T);
    inline virtual void executeAfter(T);
    inline virtual void draw(T);
};  // Size: 0x04

template<>
void JPACallBackBase<JPABaseEmitter*>::init(JPABaseEmitter*) {}
template<>
void JPACallBackBase<JPABaseEmitter*>::execute(JPABaseEmitter*) {}
template<>
void JPACallBackBase<JPABaseEmitter*>::executeAfter(JPABaseEmitter*) {}
template<>
void JPACallBackBase<JPABaseEmitter*>::draw(JPABaseEmitter*) {}

template<typename T, typename U>
class JPACallBackBase2 {
public:
    JPACallBackBase2() {}
    virtual ~JPACallBackBase2() {}

    inline virtual void init(T, U);
    inline virtual void execute(T, U);
    inline virtual void draw(T, U);
};

template<>
void JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*>::init(JPABaseEmitter*, JPABaseParticle*) {}
template<>
void JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*>::execute(JPABaseEmitter*, JPABaseParticle*) {}
template<>
void JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*>::draw(JPABaseEmitter*, JPABaseParticle*) {}

struct JPAEmitterInfo {
public:
    JPAEmitterInfo() : mRandom(0) {}
    ~JPAEmitterInfo() {}

public:
    /* 0x000 */ JMath::TRandom_fast_ mRandom;
    /* 0x004 */ JPABaseEmitter * mpCurEmitter;
    /* 0x008 */ Mtx mEmitterGlobalSR;
    /* 0x038 */ Mtx mEmitterGlobalRot;
    /* 0x068 */ Mtx mGlobalRot;
    /* 0x098 */ Mtx mEmitterDirMtx;
    /* 0x0C8 */ JGeometry::TVec3<f32> mEmitterGlobalScale;
    /* 0x0D4 */ JGeometry::TVec3<f32> mEmitterTranslation;
    /* 0x0E0 */ JGeometry::TVec3<f32> mEmitterGlobalCenter;
    /* 0x0EC */ JGeometry::TVec3<f32> mPublicScale;
    /* 0x0F8 */ JGeometry::TVec3<f32> mgReRDir;
    /* 0x100 */ f32 mFovy;
    /* 0x104 */ f32 mAspect;
    /* 0x10C */ JGeometry::TVec3<f32> mVolumePos;
    /* 0x118 */ JGeometry::TVec3<f32> mVelOmni;
    /* 0x124 */ JGeometry::TVec3<f32> mVelAxis;
    /* 0x130 */ f32 mVolumeSize;
    /* 0x134 */ s32 mVolumeEmitCount;
    /* 0x138 */ s32 mVolumeEmitIdx;
    /* 0x13C */ s32 mVolumeEmitAngleCount;
    /* 0x140 */ s32 mVolumeEmitXCount;
    /* 0x144 */ s32 mVolumeEmitAngleMax;
    /* 0x148 */ s32 mDivNumber;
};

struct JPAFrameManager {
public:
    JPAFrameManager() : mFrame(0.0f) {}

    f32 getFrame() const { return mFrame; }
    void setFrame(f32 frame) { mFrame = frame; }
    void incFrame() {
        mFrame++;
        if (mFrame < 0.0f)
            mFrame = 0.0f;
    }

private:
    /* 0x00 */ f32 mFrame;
};

class JPABaseEmitter {
public:
    JPABaseEmitter() : mLink(this), mRandomSeed(0) {}
    ~JPABaseEmitter() {}

    typedef void (JPABaseEmitter::*VolumeFunc)();

    void calcVolumePoint();
    void calcVolumeLine();
    void calcVolumeCircle();
    void calcVolumeCube();
    void calcVolumeSphere();
    void calcVolumeCylinder();
    void calcVolumeTorus();
    void create(JPADataBlockLinkInfo*);
    void calcEmitterInfo();
    void calc();
    void calcCreatePtcls();
    void createChildren(JPABaseParticle*);
    JPABaseParticle* createParticle();
    void calcParticle();
    void calcChild();
    void calcKey();
    void deleteParticle(JPABaseParticle*, JSUList<JPABaseParticle>*);
    void deleteAllParticle();
    JPABaseParticle* getPtclFromVacList();
    bool doStartFrameProcess();
    bool doTerminationProcess();
    void calcEmitterGlobalPosition(JGeometry::TVec3<f32>&);
    void calcgReRDirection();
    u8 getPivotX();
    u8 getPivotY();

    void setStatus(u32 status) { mFlags |= status; }
    void clearStatus(u32 status) { mFlags &= ~status; }
    u32 checkStatus(u32 status) { return mFlags & status; }
    void initStatus(u32 status) { mFlags = status; }

    bool checkEmDataFlag(u32 mask) { return mDataFlag & mask; }

    int getParticleNumber() {
        return mActiveParticles.getNumLinks() + mChildParticles.getNumLinks();
    }

    u8 getGroupID() { return mGroupID; }
    u8 getResourceManagerID() { return mResMgrID; }

    JPADataBlockLinkInfo * getEmitterDataBlockInfoPtr() const { return mpDataLinkInfo; }
    bool isEnableDeleteEmitter() { return checkStatus(JPAEmtrStts_EnableDeleteEmitter) && getParticleNumber() == 0; }

    u8 getGlobalAlpha() { return mGlobalPrmColor.a; }
    void setGlobalAlpha(u8 alpha) { mGlobalPrmColor.a = alpha; }
    void setGlobalRTMatrix(MtxP mtx) {
        JPASetRMtxTVecfromMtx(mtx, mGlobalRotation, mGlobalTranslation);
    }
    void setGlobalSRTMatrix(MtxP mtx) {
        JPASetRMtxSTVecfromMtx(mtx, mGlobalRotation, mGlobalDynamicsScale, mGlobalTranslation);
    }
    void setGlobalRotation(const JGeometry::TVec3<s16>& rot) {
        JPAGetXYZRotateMtx(rot.x, rot.y, rot.z, mGlobalRotation);
    }
    void getGlobalTranslation(JGeometry::TVec3<f32>& out) const { out.set(mGlobalTranslation); }
    void setGlobalTranslation(f32 x, f32 y, f32 z) { mGlobalTranslation.set(x, y, z); }
    void setGlobalTranslation(const JGeometry::TVec3<f32>& trans) { mGlobalTranslation.set(trans); }
    void setGlobalScale(const JGeometry::TVec3<f32>& scale) {
        mGlobalDynamicsScale.set(scale);
        mGlobalParticleScale.set(scale);
    }
    void getGlobalParticleScale(JGeometry::TVec3<f32>& out) const {
        out.set(mGlobalParticleScale);
    }
    void setGlobalParticleScale(const JGeometry::TVec3<f32>& scale) {
        mGlobalParticleScale.set(scale);
    }
    void setGlobalDynamicsScale(const JGeometry::TVec3<f32>& scale) {
        mGlobalDynamicsScale.set(scale);
    }
    void setEmitterTranslation(const JGeometry::TVec3<f32>& trans) {
        mEmitterTranslation.set(trans);
    }
    void setEmitterScale(const JGeometry::TVec3<f32>& scale) {
        mEmitterScale.set(scale);
    }
    void setDirection(const JGeometry::TVec3<f32>& dir) {
        mEmitterDir.set(dir);
    }
    void setMaxFrame(s32 maxFrame) { mMaxFrame = maxFrame; }
    void setGlobalPrmColor(u8 r, u8 g, u8 b) {
        mGlobalPrmColor.r = r;
        mGlobalPrmColor.g = g;
        mGlobalPrmColor.b = b;
    }
    void setGlobalEnvColor(u8 r, u8 g, u8 b) {
        mGlobalEnvColor.r = r;
        mGlobalEnvColor.g = g;
        mGlobalEnvColor.b = b;
    }

    void setVolumeSweep(f32 i_volSweep) { mVolumeSweep = i_volSweep; }
    void setVolumeSize(u16 size) { mVolumeSize = size; }
    void setLifeTime(s16 i_lifeTime) { mLifeTime = i_lifeTime; }
    f32 getRate() const { return mRate; }
    void setRate(f32 i_rate) { mRate = i_rate; }
    void setRandomDirectionSpeed(f32 i_speed) { mInitialVelRndm = i_speed; }
    void setDirectionalSpeed(f32 i_speed) { mInitialVelDir = i_speed; }
    void setAwayFromAxisSpeed(f32 i_speed) { mInitialVelAxis = i_speed; }
    void setAwayFromCenterSpeed(f32 i_speed) { mInitialVelOmni = i_speed; }
    void setSpread(f32 i_spread) { mSpread = i_spread; }

    void stopCreateParticle() { setStatus(JPAEmtrStts_StopEmit); }
    void playCreateParticle() { clearStatus(JPAEmtrStts_StopEmit); }
    void stopDrawParticle() { setStatus(JPAEmtrStts_StopDraw); }
    void playDrawParticle() { clearStatus(JPAEmtrStts_StopDraw); }
    bool isDraw() { return !checkStatus(JPAEmtrStts_StopDraw); }
    void becomeImmortalEmitter() { setStatus(JPAEmtrStts_Immortal); }
    void quitImmortalEmitter() { clearStatus(JPAEmtrStts_Immortal); }

    void becomeContinuousParticle() { mMaxFrame = 0; }
    void becomeInvalidEmitter() {
        mMaxFrame = -1;
        stopCreateParticle();
    }

    void setEmitterCallBackPtr(JPACallBackBase<JPABaseEmitter*>* callback) {
        mpEmitterCallBack = callback;
    }
    void setParticleCallBackPtr(JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*>* callback) {
        mpParticleCallBack = callback;
    }
    void setParticleList(JSUList<JPABaseParticle>* list) { mpPtclVacList = list; }
    void setFieldList(JSUList<JPAFieldData>* list) { mFieldManager.mVacList = list; }
    JSUList<JPABaseParticle>* getParticleList() { return &mActiveParticles; }
    JSUList<JPABaseParticle>* getChildParticleList() { return &mChildParticles; }
    JSULink<JPABaseEmitter>* getLinkBufferPtr() { return &mLink; }

    void initDrawMgr(JPATextureResource* texRes) { mDraw.initialize(this, texRes); }
    void draw(MtxP cameraMtxP) { mDraw.draw(cameraMtxP); }
    bool isZDraw() { return mDraw.isZDraw(); }
    bool isChildDraw() { return mDraw.isChildDraw(); }
    MtxP getCamMtxPtr() { return mDraw.getCamMtxPtr(); }

    f32 getRandomF() { return mRandomSeed.get_ufloat_1(); }
    f32 getRandomRF() { f32 x = mRandomSeed.get_ufloat_1(); return x + x - 1.0f; }
    f32 getRandomSF() { return mRandomSeed.get_ufloat_1() - 0.5f; }
    s16 getRandomSS() { return mRandomSeed.get_bit16(); }

    u32 getUserWork() { return mUserData; }
    void setUserWork(u32 work) { mUserData = work; }

    // TODO
    void calcEmitterGlobalTranslation(JGeometry::TVec3<f32>&) {}
    void drawCB() {}
    void drawEmitterCallBack() {}
    void getAxisYVec(JGeometry::TVec3<f32>&) const {}
    void getBaseEnvColor(GXColor&) {}
    void getBasePrmColor(GXColor&) {}
    void getCurrentCreateNumber() const {}
    f32 getFrame() { return mTick.getFrame(); }
    void getgReRDirection(JGeometry::TVec3<f32>&) {}
    void isContinuousParticle() {}
    void loadTexture(u8, GXTexMapID) {}
    void setEmitterRotation(const JGeometry::TVec3<s16>&) {}
    void setGlobalParticleHeightScale(f32 y) { mGlobalParticleScale.y = y; }
    void setGlobalParticleScale(f32, f32) {}
    void setGlobalParticleWidthScale(f32) {}

    static JPAEmitterInfo emtrInfo;

    void getEmitterAxis(JGeometry::TVec3<f32>& vec0, JGeometry::TVec3<f32>& vec1, JGeometry::TVec3<f32>& vec2) const {
        // Not sure if this implementation is correct. It does seem to match for dPa_waveEcallBack::executeAfter, but
        // a non-static function (const) only referencing a static variable is unusual, and this implementation isn't
        // complex enough to match the size of the inline in the demo debug map (0x128 bytes).
        vec0.set(emtrInfo.mEmitterGlobalRot[0][0], emtrInfo.mEmitterGlobalRot[1][0], emtrInfo.mEmitterGlobalRot[2][0]);
        vec1.set(emtrInfo.mEmitterGlobalRot[0][1], emtrInfo.mEmitterGlobalRot[1][1], emtrInfo.mEmitterGlobalRot[2][1]);
        vec2.set(emtrInfo.mEmitterGlobalRot[0][2], emtrInfo.mEmitterGlobalRot[1][2], emtrInfo.mEmitterGlobalRot[2][2]);
    }

    static f32 getAspect() { return emtrInfo.mAspect; }
    static f32 getFovy() { return emtrInfo.mFovy; }

private:
    void calcAfterCB() {
        if (mpEmitterCallBack != NULL)
            mpEmitterCallBack->executeAfter(this);
    }
    void calcBeforeCB() {
        if (mpEmitterCallBack != NULL)
            mpEmitterCallBack->execute(this);
    }

public:
    /* 0x000 */ VolumeFunc mVolumeFunc;
    /* 0x00C */ JGeometry::TVec3<f32> mEmitterScale;
    /* 0x018 */ JGeometry::TVec3<f32> mEmitterTranslation;
    /* 0x024 */ JGeometry::TVec3<s16> mEmitterRot;
    /* 0x02A */ u8 mVolumeType;
    /* 0x02B */ u8 mRateStep;
    /* 0x02C */ JGeometry::TVec3<f32> mEmitterDir;
    /* 0x038 */ f32 mRate;
    /* 0x03C */ f32 mRateRndm;
    /* 0x040 */ f32 mAccel;
    /* 0x044 */ f32 mAccelRndm;
    /* 0x048 */ f32 mAirResist;
    /* 0x04C */ f32 mAirResistRndm;
    /* 0x050 */ f32 mMoment;
    /* 0x054 */ f32 mMomentRndm;
    /* 0x058 */ f32 mLifeTimeRndm;
    /* 0x05C */ f32 mSpread;
    /* 0x060 */ s32 mMaxFrame;
    /* 0x064 */ s16 mLifeTime;
    /* 0x066 */ s16 mStartFrame;
    /* 0x068 */ u16 mVolumeSize;
    /* 0x06A */ u16 mDivNumber;
    /* 0x06C */ f32 mInitialVelOmni;
    /* 0x070 */ f32 mInitialVelAxis;
    /* 0x074 */ f32 mInitialVelDir;
    /* 0x078 */ f32 mInitialVelRndm;
    /* 0x07C */ f32 mInitialVelRatio;
    /* 0x080 */ f32 mVolumeSweep;
    /* 0x084 */ f32 mVolumeMinRad;
    /* 0x088 */ s32 mDataFlag;
    /* 0x08C */ s32 mUseKeyFlag;
    /* 0x090 */ JSULink<JPABaseEmitter> mLink;
    /* 0x0A0 */ JPADraw mDraw;
    /* 0x164 */ JPAFrameManager mTick;
    /* 0x168 */ JPAFrameManager mTime;
    /* 0x16C */ JPAFieldManager mFieldManager;
    /* 0x17C */ JSUList<JPABaseParticle> mActiveParticles;
    /* 0x188 */ JSUList<JPABaseParticle> mChildParticles;
    /* 0x194 */ JSUList<JPABaseParticle>* mpPtclVacList;
    /* 0x198 */ JPADataBlockLinkInfo* mpDataLinkInfo;
    /* 0x19C */ JPACallBackBase<JPABaseEmitter*>* mpEmitterCallBack;
    /* 0x1A0 */ JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*>* mpParticleCallBack;
    /* 0x1A4 */ JMath::TRandom_fast_ mRandomSeed;
    /* 0x1A8 */ JGeometry::SMatrix34C<f32> mGlobalRotation;
    /* 0x1D8 */ JGeometry::TVec3<f32> mGlobalDynamicsScale;
    /* 0x1E4 */ JGeometry::TVec3<f32> mGlobalTranslation;
    /* 0x1F0 */ JGeometry::TVec3<f32> mGlobalParticleScale;
    /* 0x1FC */ GXColor mGlobalPrmColor;
    /* 0x200 */ GXColor mGlobalEnvColor;
    /* 0x204 */ f32 mEmitCount;
    /* 0x208 */ f32 mRateStepTimer;
    /* 0x20C */ u32 mFlags;
    /* 0x210 */ u32 mUserData;
    /* 0x214 */ u8 mGroupID;
    /* 0x215 */ u8 mResMgrID;
    /* 0x216 */ u16 field_0x216;
};

#endif /* JPAEMITTER_H */
