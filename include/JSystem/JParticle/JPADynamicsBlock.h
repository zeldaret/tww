#ifndef JPADYNAMICSBLOCK_H
#define JPADYNAMICSBLOCK_H

#include "JSystem/JGeometry.h"

struct JPADynamicsBlockData {
    /* 0x00 */ u32 mFlags;
    /* 0x04 */ f32 mVolumeSweep;
    /* 0x08 */ f32 mVolumeMinRad;
    /* 0x0C */ u16 mVolumeSize;
    /* 0x0E */ u16 mDivNumber;
    /* 0x10 */ f32 mRate;
    /* 0x14 */ f32 mRateRndm;
    /* 0x18 */ u8 mRateStep;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ s16 mMaxFrame;
    /* 0x1C */ s16 mStartFrame;
    /* 0x1E */ s16 mLifeTime;
    /* 0x20 */ f32 mLifeTimeRndm;
    /* 0x24 */ f32 mInitVelOmni;
    /* 0x28 */ f32 mInitVelAxis;
    /* 0x2C */ f32 mInitVelRndm;
    /* 0x30 */ f32 mInitVelDir;
    /* 0x34 */ f32 mInitVelRatio;
    /* 0x38 */ f32 mSpread;
    /* 0x3C */ f32 mAirResist;
    /* 0x40 */ f32 mAirResistRndm;
    /* 0x44 */ f32 mMoment;
    /* 0x48 */ f32 mMomentRndm;
    /* 0x4C */ f32 mAccel;
    /* 0x50 */ f32 mAccelRndm;
    /* 0x54 */ JGeometry::TVec3<f32> mEmitterScl;
    /* 0x60 */ JGeometry::TVec3<f32> mEmitterTrs;
    /* 0x6C */ JGeometry::TVec3<f32> mEmitterDir;
    /* 0x78 */ JGeometry::TVec3<s16> mEmitterRot;
};  // Size: 0x80

enum {
    JPADynFlag_FixedDensity = 0x01,
    JPADynFlag_FixedInterval = 0x02,
    JPADynFlag_InheritScale = 0x04,
    JPADynFlag_FollowEmtr = 0x08,
    JPADynFlag_FollowEmtrChld = 0x10,
};

class JPADynamicsBlock {
public:
    virtual ~JPADynamicsBlock() {};
    virtual u32 getDataFlag() = 0;
    virtual u32 getUseKeyFlag() = 0;
    virtual void getEmitterScl(JGeometry::TVec3<f32>&) = 0;
    virtual void getEmitterRot(JGeometry::TVec3<s16>&) = 0;
    virtual void getEmitterTrs(JGeometry::TVec3<f32>&) = 0;
    virtual void getEmitterDir(JGeometry::TVec3<f32>&) = 0;
    virtual f32 getInitVelOmni() = 0;
    virtual f32 getInitVelAxis() = 0;
    virtual f32 getInitVelRndm() = 0;
    virtual f32 getInitVelDir() = 0;
    virtual f32 getSpread() = 0;
    virtual f32 getInitVelRatio() = 0;
    virtual u32 getVolumeType() = 0;
    virtual u32 getVolumeSize() = 0;
    virtual f32 getVolumeSweep() = 0;
    virtual f32 getVolumeMinRad() = 0;
    virtual u32 getDivNumber() = 0;
    virtual f32 getRate() = 0;
    virtual f32 getRateRndm() = 0;
    virtual u32 getRateStep() = 0;
    virtual s16 getMaxFrame() = 0;
    virtual u32 getStartFrame() = 0;
    virtual u32 getLifeTime() = 0;
    virtual f32 getLifeTimeRndm() = 0;
    virtual f32 getAccel() = 0;
    virtual f32 getAccelRndm() = 0;
    virtual f32 getAirResist() = 0;
    virtual f32 getAirResistRndm() = 0;
    virtual f32 getMoment() = 0;
    virtual f32 getMomentRndm() = 0;
};

class JPADynamicsBlockArc : public JPADynamicsBlock {
public:
    JPADynamicsBlockArc(const u8*);
    virtual ~JPADynamicsBlockArc() {}
    virtual u32 getDataFlag() { return mpData->mFlags; }
    virtual u32 getUseKeyFlag() { return 0; }
    virtual void getEmitterScl(JGeometry::TVec3<f32>& out) { out.set(mpData->mEmitterScl.x, mpData->mEmitterScl.y, mpData->mEmitterScl.z); }
    virtual void getEmitterRot(JGeometry::TVec3<s16>& out) { out.set(mpData->mEmitterRot.x, mpData->mEmitterRot.y, mpData->mEmitterRot.z); }
    virtual void getEmitterTrs(JGeometry::TVec3<f32>& out) { out.set(mpData->mEmitterTrs.x, mpData->mEmitterTrs.y, mpData->mEmitterTrs.z); }
    virtual void getEmitterDir(JGeometry::TVec3<f32>& out) { out.set(mpData->mEmitterDir.x, mpData->mEmitterDir.y, mpData->mEmitterDir.z); }
    virtual u32 getVolumeType() { return (mpData->mFlags >> 8) & 0x07; }
    virtual u32 getVolumeSize() { return mpData->mVolumeSize; }
    virtual f32 getVolumeSweep() { return mpData->mVolumeSweep; }
    virtual f32 getVolumeMinRad() { return mpData->mVolumeMinRad; }
    virtual u32 getDivNumber() { return mpData->mDivNumber; }
    virtual f32 getRate() { return mpData->mRate; }
    virtual f32 getRateRndm() { return mpData->mRateRndm; }
    virtual u32 getRateStep() { return mpData->mRateStep; }
    virtual s16 getMaxFrame() { return mpData->mMaxFrame; }
    virtual u32 getStartFrame() { return mpData->mStartFrame; }
    virtual u32 getLifeTime() { return mpData->mLifeTime; }
    virtual f32 getLifeTimeRndm() { return mpData->mLifeTimeRndm; }
    virtual f32 getInitVelOmni() { return mpData->mInitVelOmni; }
    virtual f32 getInitVelAxis() { return mpData->mInitVelAxis; }
    virtual f32 getInitVelRndm() { return mpData->mInitVelRndm; }
    virtual f32 getInitVelDir() { return mpData->mInitVelDir; }
    virtual f32 getSpread() { return mpData->mSpread; }
    virtual f32 getInitVelRatio() { return mpData->mInitVelRatio; }
    virtual f32 getAccel() { return mpData->mAccel; }
    virtual f32 getAccelRndm() { return mpData->mAccelRndm; }
    virtual f32 getAirResist() { return mpData->mAirResist; }
    virtual f32 getAirResistRndm() { return mpData->mAirResistRndm; }
    virtual f32 getMoment() { return mpData->mMoment; }
    virtual f32 getMomentRndm() { return mpData->mMomentRndm; }

public:
    /* 0x04 */ const JPADynamicsBlockData* mpData;
};

#endif /* JPADynamicsBlock_H */
