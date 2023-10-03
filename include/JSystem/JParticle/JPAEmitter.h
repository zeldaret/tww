#ifndef JPAEMITTER_H
#define JPAEMITTER_H

#include "JSystem/JParticle/JPADraw.h"
#include "JSystem/JParticle/JPAField.h"
#include "JSystem/JParticle/JPAMath.h"
#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JMath/random.h"
#include "JSystem/JGeometry.h"
#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/mtx/mtx.h"

class JPADataBlockLinkInfo;

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
    virtual ~JPACallBackBase();
    
    virtual void init(JPABaseEmitter*);
    virtual void execute(JPABaseEmitter*);
    virtual void executeAfter(JPABaseEmitter*);
    virtual void draw(JPABaseEmitter*);
};

class JPABaseEmitter {
public:
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
    void createParticle();
    void calcParticle();
    void calcChild();
    void calcKey();
    void deleteParticle(JPABaseParticle*, JSUList<JPABaseParticle>*);
    void deleteAllParticle();
    void getPtclFromVacList();
    void doStartFrameProcess();
    void doTerminationProcess();
    void calcEmitterGlobalPosition(JGeometry::TVec3<float>&);
    void calcgReRDirection();
    void getPivotX();
    void getPivotY();

    void setStatus(u32 status) { mFlags |= status; }
    
    u8 getGlobalAlpha() { return mGlobalPrmColor.a; }
    void setGlobalAlpha(u8 alpha) { mGlobalPrmColor.a = alpha; }
    void setGlobalRTMatrix(MtxP mtx) {
        JPASetRMtxTVecfromMtx(mtx, mGlobalRotation, mGlobalTranslation);
    }

    void setVolumeSweep(float i_volSweep) { mVolumeSweep = i_volSweep; }
    void setLifeTime(s16 i_lifeTime) { mLifeTime = i_lifeTime; }
    void setRate(float i_rate) { mRate = i_rate; }
    void setMaxFrame(s32 i_maxFrame) { mMaxFrame = i_maxFrame; }

    void setGlobalDynamicsScale(JGeometry::TVec3<float>& i_vec) {
        mGlobalScale.x = i_vec.x;
        mGlobalScale.y = i_vec.y;
        mGlobalScale.z = i_vec.z;
    }
    void setGlobalParticleScale(JGeometry::TVec3<float>& i_vec) {
        mGlobalScale2D.x = i_vec.x;
        mGlobalScale2D.y = i_vec.y;
        mGlobalScale2D.z = i_vec.z;
    }

    void stopCreateParticle() { setStatus(JPAEmtrStts_StopEmit); }

    void becomeInvalidEmitter() {
        mMaxFrame = -1;
        stopCreateParticle();
    }
    
    /* 0x000 */ VolumeFunc mVolumeFunc;
    /* 0x00C */ cXyz mEmitterScale;
    /* 0x018 */ cXyz mEmitterTranslation;
    /* 0x024 */ csXyz mEmitterRot;
    /* 0x02A */ u8 mVolumeType;
    /* 0x02B */ u8 mRateStep;
    /* 0x02C */ cXyz mEmitterDir;
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
    /* 0x068 */ s16 mVolumeSize;
    /* 0x06A */ s16 mDivNumber;
    /* 0x06C */ f32 mInitialVelOmni;
    /* 0x070 */ f32 mInitialVelAxis;
    /* 0x074 */ f32 mInitialVelDir;
    /* 0x078 */ f32 mInitialVelRndm;
    /* 0x07C */ f32 mInitialVelRatio;
    /* 0x080 */ f32 mVolumeSweep;
    /* 0x084 */ f32 mVolumeMinRad;
    /* 0x088 */ s32 mDataFlag;
    /* 0x08C */ s32 mUseKeyFlag;
    /* 0x090 */ JSUPtrLink mLink;
    /* 0x0A0 */ JPADraw mDraw;
    /* 0x164 */ f32 mTick;
    /* 0x168 */ f32 mTime;
    /* 0x16C */ JPAFieldManager mFieldManager;
    /* 0x17C */ JSUPtrList mActiveParticles;
    /* 0x188 */ JSUPtrList mChildParticles;
    /* 0x194 */ JSUPtrList* mpPtclVacList;
    /* 0x198 */ JPADataBlockLinkInfo* mpDataLinkInfo;
    /* 0x19C */ JPACallBackBase<JPABaseEmitter>* mpEmitterCallBack;
    /* 0x1A0 */ JPACallBackBase2* mpParticleCallBack;
    /* 0x1A4 */ JMath::TRandom_fast_ mRandomSeed;
    /* 0x1A8 */ Mtx mGlobalRotation;
    /* 0x1D8 */ JGeometry::TVec3<f32> mGlobalScale;
    /* 0x1E4 */ JGeometry::TVec3<f32> mGlobalTranslation;
    /* 0x1F0 */ JGeometry::TVec3<f32> mGlobalScale2D;
    /* 0x1FC */ _GXColor mGlobalPrmColor;
    /* 0x200 */ _GXColor mGlobalEnvColor;
    /* 0x204 */ f32 mEmitCount;
    /* 0x208 */ f32 mRateStepTimer;
    /* 0x20C */ u32 mFlags;
    /* 0x210 */ u32 mUserData;
    /* 0x214 */ u8 mGroupID;
    /* 0x215 */ u8 mResMgrID;
    /* 0x216 */ u8 field_0x216[0x218 - 0x216];
};

#endif /* JPAEMITTER_H */
