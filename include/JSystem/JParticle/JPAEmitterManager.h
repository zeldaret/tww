#ifndef JPAEMITTERMANAGER_H
#define JPAEMITTERMANAGER_H

#include "JSystem/JGeometry.h"
#include "JSystem/JParticle/JPAEmitter.h"

class JPABaseEmitter;
class JPABaseParticle;
class JPAResourceManager;
class JKRHeap;

class JPADrawInfo {
public:
    JPADrawInfo(MtxP cameraMtxPtr, f32 fovy, f32 aspect) : mCameraMtxPtr(cameraMtxPtr), mFovy(fovy), mAspect(aspect) {}
    MtxP getCameraMtxPtr() { return mCameraMtxPtr; }
    f32 getFovy() { return mFovy; }
    void setFovy(f32 fovy) { mFovy = fovy; }
    f32 getAspect() { return mAspect; }
    void setAspect(f32 aspect) { mAspect = aspect; }

    /* 0x00 */ MtxP mCameraMtxPtr;
    /* 0x04 */ f32 mFovy;
    /* 0x08 */ f32 mAspect;
};

class JPAEmitterManager {
public:
    JPAEmitterManager(JPAResourceManager*, u32, u32, u32, JKRHeap*);
    JPABaseEmitter* createSimpleEmitterID(const JGeometry::TVec3<float>&, u16, u8, u8, JPACallBackBase<JPABaseEmitter*>*, JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*>*);
    void calc(u8);
    void draw(JPADrawInfo*, u8);
    void deleteEmitter(JPABaseEmitter*);
    void forceDeleteEmitter(JPABaseEmitter*);
    void forceDeleteAllEmitter();
    void clearResourceManager(u8);
    u32 getParticleNumber() { return mPtclNum - mPtclPool.getNumLinks(); }
    u32 getEmitterNumber() { return mEmtrNum - mEmtrPool.getNumLinks(); }

public:
    /* 0x00 */ JSUList<JPABaseParticle> mPtclPool;
    /* 0x0C */ JSUList<JPABaseEmitter> mEmtrPool;
    /* 0x18 */ JSUList<JPAFieldData> mFieldPool;
    /* 0x24 */ u32 mPtclNum;
    /* 0x28 */ u32 mEmtrNum;
    /* 0x2C */ u32 mFieldNum;
    /* 0x30 */ JPAResourceManager * pResMgrArray[8];
    /* 0x50 */ JSUList<JPABaseEmitter> mEmtrGroup[16];
};

#endif /* JPAEMITTERMANAGER_H */
