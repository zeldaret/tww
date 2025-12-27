#ifndef D_PARTICLE
#define D_PARTICLE

#include "d/d_particle_name.h" // IWYU pragma: export
#include "JSystem/J3DGraphBase/J3DVertex.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "JSystem/JGeometry.h"
#include "JSystem/JKernel/JKRSolidHeap.h"
#include "JSystem/JParticle/JPAParticle.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "JSystem/JParticle/JPAEmitterManager.h"
#include "SSystem/SComponent/c_list.h"
#include "m_Do/m_Do_ext.h"

class mDoDvdThd_toMainRam_c;
class dKy_tevstr_c;
class cBgS_PolyInfo;
class JPADrawInfo;
class JKRHeap;
class JPABaseEmitter;
class JPAEmitterManager;
class J3DModelData;
class csXyz;

class dPa_simpleData_c {
public:
    dPa_simpleData_c();
    ~dPa_simpleData_c() {}

    /* 0x00 */ Vec mPos;
    /* 0x0C */ GXColor mPrmColor;
    /* 0x10 */ u8 mEnvColor[3];
    /* 0x13 */ u8 mbAffectedByWind;
};

class dPa_levelEcallBack : public JPACallBackBase<JPABaseEmitter*> {
public:
    virtual ~dPa_levelEcallBack() {}
    virtual void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8) = 0;
};  // Size: 0x04

class dPa_followEcallBack : public dPa_levelEcallBack {
public:
    dPa_followEcallBack(u8=0, u8=0);
    virtual ~dPa_followEcallBack() {}

    virtual void execute(JPABaseEmitter*);
    virtual void draw(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);
    virtual void end();

    JPABaseEmitter* getEmitter() { return mpEmitter; }
    void setRateOff(u8 param_0) { mRateOff = param_0; }
    bool isEnd() { return mFlag & 1; }
    void onEnd() { mFlag |= 1; }
    void remove() { end(); }
    void setFollowOff() { field_0x12 = 1; }

protected:
    /* 0x04 */ JPABaseEmitter* mpEmitter;
    /* 0x08 */ const cXyz* mPos;
    /* 0x0C */ const csXyz* mAngle;
    /* 0x10 */ u8 mFlag;
    /* 0x11 */ u8 mRateOff;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
};  // Size: 0x14

STATIC_ASSERT(sizeof(dPa_followEcallBack) == 0x14);

class dPa_smokeEcallBack : public dPa_followEcallBack {
public:
    dPa_smokeEcallBack(u8=1);
    dPa_smokeEcallBack(u8, u8, u8, u8);
    dPa_smokeEcallBack(const GXColor&, dKy_tevstr_c*, u8);
    virtual ~dPa_smokeEcallBack() {}

    virtual void draw(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);
    virtual void end();

    void setTevStr(dKy_tevstr_c* tevStr) { mTevstr = tevStr; }
    void remove() { end(); }

    void offWindOff() { mWindOff = 0; }
    void onWindOff() { mWindOff = 1; }
    void setColor(const GXColor& color) { mColor = color; }

private:
    /* 0x14 */ s8 field_0x14;
    /* 0x15 */ u8 mWindOff;
    /* 0x16 */ GXColor mColor;
    /* 0x1C */ dKy_tevstr_c* mTevstr;
};  // Size: 0x20

STATIC_ASSERT(sizeof(dPa_smokeEcallBack) == 0x20);

class dPa_simpleEcallBack : public JPACallBackBase<JPABaseEmitter*> {
public:
    dPa_simpleEcallBack();
    virtual ~dPa_simpleEcallBack() {}

    void executeAfter(JPABaseEmitter*);
    void draw(JPABaseEmitter*);
    JPABaseEmitter* create(JPAEmitterManager*, u16, u8);
    JPABaseEmitter* createEmitter(JPAEmitterManager*);
    bool set(cXyz const*, u8, GXColor const&, GXColor const&, int);

    u16 getID() { return mResID; }

    /* 0x004 */ JPABaseEmitter* mpBaseEmitter;
    /* 0x008 */ u16 mResID;
    /* 0x00A */ u8 mGrpID;
    /* 0x00B */ u8 mbIsSmoke;
    /* 0x00C */ s16 mCount;
    /* 0x00E */ u8 field_0x00E[0x010 - 0x00E];
    /* 0x010 */ dPa_simpleData_c mSimpleData[32];
};

class dPa_waveEcallBack : public dPa_levelEcallBack {
public:
    void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);
    void remove();
    void executeAfter(JPABaseEmitter*);
    void draw(JPABaseEmitter*);

    JPABaseEmitter* getEmitter() { return mpBaseEmitter; }
    void setTimer(s16 timerVal) { mFadeTimer = timerVal; }
    void setSpeed(f32 vel) { mVelFade1 = vel; }
    void setPitch(f32 pitch) { mVelFade2 = pitch; }
    void setMaxSpeed(f32 vel) { mMaxParticleVelocity = vel; }
    void setMaxDisSpeed(f32 vel) { mVelSpeed = vel; }
    void setAnchor(const cXyz* anchorPos1, const cXyz* anchorPos2) { mCollapsePos[0].set(*anchorPos1); mCollapsePos[1].set(*anchorPos2); }

    virtual ~dPa_waveEcallBack() {}

    /* 0x04 */ s16 mState;
    /* 0x06 */ s16 mFadeTimer;
    /* 0x08 */ f32 mVelFade1;
    /* 0x0C */ f32 mVel;
    /* 0x10 */ f32 mVelSpeed;
    /* 0x14 */ f32 mVelFade2;
    /* 0x18 */ f32 mMaxParticleVelocity;
    /* 0x1C */ cXyz mCollapsePos[2];
    /* 0x34 */ const cXyz* mpPos;
    /* 0x38 */ const csXyz* mpRot;
    /* 0x3C */ Vec mRotMtx[3];
    /* 0x60 */ JPABaseEmitter* mpBaseEmitter;
};

class dPa_splashEcallBack : public dPa_levelEcallBack {
public:
    void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);
    void remove();
    void execute(JPABaseEmitter*);

    JPABaseEmitter* getEmitter() { return mpBaseEmitter; }
    void setSpeed (f32 vel) { mScaleTimer = vel; }
    void setMaxSpeed (f32 vel) { mMaxScaleTimer = vel; }

    virtual ~dPa_splashEcallBack() {}

    /* 0x04 */ s16 mState;
    /* 0x08 */ f32 mScaleTimer;
    /* 0x0C */ f32 mMaxScaleTimer;
    /* 0x10 */ const cXyz* mpPos;
    /* 0x14 */ const csXyz* mpRot;
    /* 0x18 */ JPABaseEmitter* mpBaseEmitter;
};

class dPa_trackEcallBack : public dPa_levelEcallBack {
public:
    void getMaxWaterY(JGeometry::TVec3<f32>*);
    void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);
    void remove();
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);
    void stop() { mState = 1; }

    JPABaseEmitter* getEmitter() { return mpBaseEmitter; }
    void setIndirectTexData(f32 exTransY, f32 exScaleY) { mExTransY = exTransY; mExScaleY = exScaleY; }
    void setSpeed(f32 vel) { mVel = vel; }
    void setLimitSpeed(f32 vel) { mMinVel = vel; }
    void setWaterY(f32 y) { mBaseY = y; }
    void setWaterFlatY(f32 y) { mMinY = y; }

    virtual ~dPa_trackEcallBack() {}

    /* 0x04 */ s16 mState;
    /* 0x08 */ f32 mBaseY;
    /* 0x0C */ f32 mMinY;
    /* 0x10 */ JGeometry::TVec3<f32> mPos[3];
    /* 0x34 */ const cXyz* mpPos;
    /* 0x38 */ const csXyz* mpRot;
    /* 0x3C */ f32 mExTransY;
    /* 0x40 */ f32 mExScaleY;
    /* 0x44 */ f32 mVel;
    /* 0x48 */ f32 mMinVel;
    /* 0x4C */ JPABaseEmitter* mpBaseEmitter;
};

class dPa_rippleEcallBack : public dPa_levelEcallBack {
public:
    dPa_rippleEcallBack() { mpBaseEmitter = NULL; }
    virtual ~dPa_rippleEcallBack() {}

    void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);
    void end();
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);

    JPABaseEmitter* getEmitter() { return mpBaseEmitter; }
    void isStatus(u8) {}
    void offStatus(int flag) { mFlags &= ~flag; }
    void onStatus(int flag) { mFlags |= flag;}
    void remove() { end(); }
    void setRate(f32 rate) { mRate = rate; }

    /* 0x04 */ JPABaseEmitter* mpBaseEmitter;
    /* 0x08 */ const cXyz* mPos;
    /* 0x0C */ u32 mFlags;
    /* 0x10 */ f32 mRate;
}; // size = 0x14

class dPa_modelEmitter_c : public node_class {
public:
    dPa_modelEmitter_c();
    virtual ~dPa_modelEmitter_c() {}
    virtual void draw() = 0;
};

class JKRSolidHeap;

class dPa_J3DmodelEmitter_c : public dPa_modelEmitter_c {
public:
    dPa_J3DmodelEmitter_c(JPABaseEmitter*, J3DModelData*, dKy_tevstr_c&, J3DAnmTexPattern*, u16, int);
    virtual ~dPa_J3DmodelEmitter_c();

    virtual void draw();

    /* 0x10 */ JPABaseEmitter* mpBaseEmitter;
    /* 0x14 */ JKRSolidHeap* mpHeap;
    /* 0x18 */ J3DModelData* modelData;
    /* 0x1C */ J3DAnmTexPattern* field_0x1c;
    /* 0x20 */ J3DTexNoAnm* field_0x20;
    /* 0x24 */ u16 field_0x24;
    /* 0x26 */ u8 field_0x26;
    /* 0x5C */ dKy_tevstr_c tevStr;
};

class dPa_J3Dmodel_c {
public:
    dPa_J3Dmodel_c();

public:
    /* 0x00 */ u8 mInit;
    /* 0x04 */ J3DModel* mModel;
};

class dPa_smokePcallBack : public JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*> {
public:
    dPa_smokePcallBack() {}
    virtual ~dPa_smokePcallBack() {}

    virtual void execute(JPABaseEmitter*, JPABaseParticle*);
    virtual void draw(JPABaseEmitter*, JPABaseParticle*);
};

class dPa_selectTexEcallBack : public dPa_levelEcallBack {
public:
    dPa_selectTexEcallBack(u8 tex) { mTexNo = tex; }
    virtual ~dPa_selectTexEcallBack() {}

    virtual void draw(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);

    /* 0x04 */ u8 mTexNo;
};

class dPa_windPcallBack : public JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*> {
public:
    dPa_windPcallBack() {}
    virtual ~dPa_windPcallBack() {}

    virtual void execute(JPABaseEmitter*, JPABaseParticle*);
};

class dPa_singleRippleEcallBack : public dPa_levelEcallBack {
public:
    dPa_singleRippleEcallBack() {}
    virtual ~dPa_singleRippleEcallBack() {}

    virtual void execute(JPABaseEmitter*);
    virtual void draw(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
};

class dPa_ripplePcallBack : public JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*> {
public:
    dPa_ripplePcallBack() {}
    virtual ~dPa_ripplePcallBack() {}

    virtual void execute(JPABaseEmitter*, JPABaseParticle*);
    virtual void draw(JPABaseEmitter*, JPABaseParticle*);
};

class dPa_cutTurnEcallBack_c : public dPa_levelEcallBack {
public:
    dPa_cutTurnEcallBack_c() {}
    virtual ~dPa_cutTurnEcallBack_c() {}

    virtual void executeAfter(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
    void end();

    u8 getAlpha() { return mAlpha; }
    void setAlpha(u8 alpha) { mAlpha = alpha;}
    void remove() { end(); }
    void setPosArray(cXyz* pos_array, s16 param_2) {
        mPosArray = pos_array;
        field_0x6 = param_2;
    }

public:
    /* 0x04 */ u8 mAlpha;
    /* 0x05 */ u8 field_0x5;
    /* 0x06 */ u16 field_0x6;
    /* 0x08 */ cXyz* mPosArray;
    /* 0x0C */ JPABaseEmitter* mpBaseEmitter;
};  // Size: 0x10

STATIC_ASSERT(sizeof(dPa_cutTurnEcallBack_c) == 0x10);

class dPa_stripesEcallBack : public dPa_levelEcallBack {
public:
    dPa_stripesEcallBack() {}
    virtual ~dPa_stripesEcallBack() {}

    virtual void draw(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
};

class dPa_kageroEcallBack : public JPACallBackBase<JPABaseEmitter*> {
public:
    dPa_kageroEcallBack() {}
    virtual ~dPa_kageroEcallBack() {}

    virtual void draw(JPABaseEmitter*);
};

class dPa_bombSmokeEcallBack : public dPa_levelEcallBack {
public:
    dPa_bombSmokeEcallBack() {}
    virtual ~dPa_bombSmokeEcallBack() {}

    virtual void execute(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
};

class dPa_setColorEcallBack : public dPa_levelEcallBack {
public:
    dPa_setColorEcallBack(const GXColor& color) { mColor = color; }
    virtual ~dPa_setColorEcallBack() {}

    virtual void draw(JPABaseEmitter*) { GXSetTevColor(GX_TEVREG1, mColor); }
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8) {}

public:
    /* 0x04 */ GXColor mColor;
};  // Size: 0x08

class dPa_modelControl_c : public node_list_class {
public:
    dPa_modelControl_c(J3DModelData*);
    ~dPa_modelControl_c();

    static J3DModel * newModel(J3DModelData*);
    void draw();
    int add(dPa_modelEmitter_c *emitter) { return cLs_Addition(this, emitter); }

    static dPa_J3Dmodel_c * mModel;
};

class dPa_control_c {
public:
    dPa_control_c();

    enum {
        /* 0x0 */ dPtclGroup_Normal_e,
        /* 0x1 */ dPtclGroup_NormalP1_e,
        /* 0x2 */ dPtclGroup_Toon_e,
        /* 0x3 */ dPtclGroup_ToonP1_e,
        /* 0x4 */ dPtclGroup_Projection_e,
        /* 0x5 */ dPtclGroup_ShipTail_e,
        /* 0x6 */ dPtclGroup_Wind_e,
        /* 0x7 */ dPtclGroup_2Dfore_e,
        /* 0x8 */ dPtclGroup_2Dback_e,
        /* 0x9 */ dPtclGroup_2DmenuFore_e,
        /* 0xA */ dPtclGroup_2DmenuBack_e,
    };

    static u8 getRM_ID(u16);
    void swapFrameBufferTexture();
    void createCommon(void const*);
    void createRoomScene(void const*);
    bool readScene(u8, mDoDvdThd_toMainRam_c**);
    void createScene(void const*);
    bool removeRoomScene();
    void removeScene();
    void calc3D();
    void calc2D();
    void calcMenu();
    void draw(JPADrawInfo*, u8);
    JPABaseEmitter* set(u8, u16, cXyz const*, csXyz const*, cXyz const*, u8, dPa_levelEcallBack*,
                        s8, GXColor const*, GXColor const*, cXyz const*);
    JPABaseEmitter* setBombSmoke(u16, cXyz const*, csXyz const*, cXyz const*, u8);
    JPABaseEmitter* setSimpleLand(int, cXyz const*, csXyz const*, f32, f32, f32, dKy_tevstr_c*, int*, int);
    JPABaseEmitter* setSimpleLand(cBgS_PolyInfo&, cXyz const*, csXyz const*, f32, f32, f32, dKy_tevstr_c*, int*, int);
    s32 checkAtrCodeEffect(int);
    JPABaseEmitter* setNormalStripes(u16, cXyz const*, csXyz const*, cXyz const*, u8, u16);
    bool newSimple(u16, u8);
    bool setSimple(u16, cXyz const*, u8, GXColor const&, GXColor const&, int);
    dPa_simpleEcallBack* getSimple(u16);

    JPABaseEmitter* setNormal(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(dPtclGroup_Normal_e, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setNormalP1(u16 particleID, const cXyz* pos, const csXyz* angle,
                                const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                                s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                                const cXyz* pScale2D) {
        return set(dPtclGroup_NormalP1_e, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setToon(u16 particleID, const cXyz* pos, const csXyz* angle,
                            const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                            s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                            const cXyz* pScale2D) {
        return set(dPtclGroup_Toon_e, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setToonP1(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(dPtclGroup_ToonP1_e, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setProjection(u16 particleID, const cXyz* pos, const csXyz* angle,
                                  const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                                  s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                                  const cXyz* pScale2D) {
        return set(dPtclGroup_Projection_e, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setShipTail(u16 particleID, const cXyz* pos, const csXyz* angle,
                                const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                                s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                                const cXyz* pScale2D) {
        return set(dPtclGroup_ShipTail_e, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* set2Dfore(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(dPtclGroup_2Dfore_e, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* set2Dback(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(dPtclGroup_2Dback_e, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* set2DmenuFore(u16 particleID, const cXyz* pos, const csXyz* angle,
                                  const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                                  s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                                  const cXyz* pScale2D) {
        return set(dPtclGroup_2DmenuFore_e, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setSingleRipple(u16 particleID, const cXyz* pos, const csXyz* angle,
                                    const cXyz* scale, u8 alpha) {
        return set(dPtclGroup_ShipTail_e, particleID, pos, angle, scale, alpha, &mSingleRippleEcallBack, -1, NULL, NULL, NULL);
    }

    void draw(JPADrawInfo* inf) { draw(inf, dPtclGroup_Normal_e); }
    void drawP1(JPADrawInfo* inf) { draw(inf, dPtclGroup_NormalP1_e); }
    void drawToon(JPADrawInfo* inf) { draw(inf, dPtclGroup_Toon_e); }
    void drawToonP1(JPADrawInfo* inf) { draw(inf, dPtclGroup_ToonP1_e); }
    void drawProjection(JPADrawInfo* inf) { draw(inf, dPtclGroup_Projection_e); }
    void drawShipTail(JPADrawInfo* inf) { draw(inf, dPtclGroup_ShipTail_e); }
    void drawWind(JPADrawInfo* inf) { draw(inf, dPtclGroup_Wind_e); }
    void draw2Dfore(JPADrawInfo* inf) { draw(inf, dPtclGroup_2Dfore_e); }
    void draw2Dback(JPADrawInfo* inf) { draw(inf, dPtclGroup_2Dback_e); }
    void draw2DmenuFore(JPADrawInfo* inf) { draw(inf, dPtclGroup_2DmenuFore_e); }
    void draw2DmenuBack(JPADrawInfo* inf) { draw(inf, dPtclGroup_2DmenuBack_e); }

    u32 getParticleNum() { return mEmitterMng->getParticleNumber(); }
    u32 getEmitterNum() { return mEmitterMng->getEmitterNumber(); }

    int addModelEmitter(dPa_modelEmitter_c *emitter) { return mModelControl->add(emitter); }
    void drawModelParticle() { mModelControl->draw(); }
    JKRHeap * getHeap() { return mHeap; }

    static dPa_selectTexEcallBack mTsubo[4];

    static dPa_setColorEcallBack* getLifeBallSetColorEcallBack(int idx) { return &mLifeBall[idx]; }
    static dPa_setColorEcallBack mLifeBall[3];

    static bool isStatus(u8 status) { return mStatus & status; }
    static void onStatus(u8 status) { mStatus |= status; }
    static void offStatus(u8 status) { mStatus &= ~status; }
    static u8 mStatus;

    static JPAEmitterManager* getEmitterManager() { return mEmitterMng; }
    static void forceDeleteEmitter(JPABaseEmitter* emitter) { mEmitterMng->forceDeleteEmitter(emitter); }
    static JPAEmitterManager* mEmitterMng;

    static dPa_stripesEcallBack mStripes;
    static dPa_kageroEcallBack mKagero;
    static dPa_smokeEcallBack mSmokeEcallback;
    static dPa_smokePcallBack mSmokePcallback;
    static dPa_singleRippleEcallBack mSingleRippleEcallBack;
    static dPa_ripplePcallBack mRipplePcallBack;
    static dPa_bombSmokeEcallBack mBombSmokeEcallBack;

    static MtxP getWindViewMatrix() { return mWindViewMatrix; }
    static Mtx mWindViewMatrix;

    static dPa_selectTexEcallBack* getTsuboSelectTexEcallBack(int index) { return &mTsubo[index]; }

    /* 0x0000 */ JKRSolidHeap* mHeap;
    /* 0x0004 */ JPAResourceManager* mCommonResMng;
    /* 0x0008 */ dPa_modelControl_c* mModelControl;
    /* 0x000C */ JKRSolidHeap* mSceneHeap;
    /* 0x0010 */ const void* mpData;
    /* 0x0014 */ JPAResourceManager* mSceneResMng;
    /* 0x0018 */ u8 mSceneNo;
    /* 0x0019 */ u8 mCount;
    /* 0x001A */ u8 mNumSimple;
    /* 0x001B */ u8 mNumSimpleCommon;
    /* 0x001C */ dPa_simpleEcallBack mSimpleCallbacks[25];
};

#endif /* D_PARTICLE */
