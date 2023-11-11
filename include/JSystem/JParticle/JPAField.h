#ifndef JPAFIELD_H
#define JPAFIELD_H

#include "JSystem/JSupport/JSUList.h"
#include "JSystem/JGeometry.h"

class JPADataBlockLinkInfo;
class JPAEmitterInfo;
class JPAFieldData;
class JPABaseParticle;
class JPABaseField;

class JPAFieldManager {
public:
    void initField(JPADataBlockLinkInfo*, JPAEmitterInfo*);
    void init(JPABaseParticle*);
    void preCalc();
    void calc(JPABaseParticle*);
    void deleteField(JPAFieldData*);
    void deleteAllField();
    
public:
    /* 0x00 */ JSUList<JPAFieldData> mList;
    /* 0x0C */ JSUList<JPAFieldData>* mVacList;
};

class JPAFieldData {
public:
    JPAFieldData();
    virtual ~JPAFieldData();
    JSULink<JPAFieldData>* getLinkBufferPtr() { return &mLink; }

public:
    /* 0x04 */ JPABaseField * mpBaseField;
    /* 0x08 */ JSULink<JPAFieldData> mLink;
    /* 0x18 */ JGeometry::TVec3<f32> mVel;
    /* 0x24 */ JGeometry::TVec3<f32> mAirPos;
    /* 0x30 */ f32 mAirMinDist;
    /* 0x34 */ u32 field_0x34;
    /* 0x38 */ u32 field_0x38;
    /* 0x3C */ JGeometry::TVec3<f32> mAirDir;
    /* 0x48 */ u32 field_0x48;
    /* 0x4C */ f32 mFadeOutRate;
    /* 0x50 */ f32 mFadeInRate;
    /* 0x54 */ JGeometry::TVec3<f32> mPos;
    /* 0x60 */ JGeometry::TVec3<f32> mDir;
    /* 0x6C */ f32 mMag;
    /* 0x70 */ f32 mMagRndm;
    /* 0x74 */ f32 mMaxDist;
    /* 0x78 */ f32 mVal1;
    /* 0x7C */ f32 mVal2;
    /* 0x80 */ f32 mVal3;
    /* 0x84 */ f32 mFadeIn;
    /* 0x88 */ f32 mFadeOut;
    /* 0x8C */ f32 mEnTime;
    /* 0x90 */ f32 mDisTime;
    /* 0x94 */ u16 mSttFlag;
    /* 0x96 */ u8 mType;
    /* 0x97 */ u8 mID;
    /* 0x98 */ u8 mVelType;
    /* 0x99 */ u8 mCycle;
};

#endif /* JPAFIELD_H */
