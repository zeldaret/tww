#ifndef D_PARTICLE
#define D_PARTICLE

#include "JSystem/J3DGraphBase/J3DVertex.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "JSystem/JGeometry.h"
#include "JSystem/JParticle/JPAParticle.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "f_pc/f_pc_node.h"
#include "m_Do/m_Do_ext.h"

class mDoDvdThd_toMainRam_c;
class dPa_levelEcallBack;
class dKy_tevstr_c;
class cBgS_PolyInfo;
class JPADrawInfo;
class JKRHeap;
class JPABaseEmitter;
class JPAEmitterManager;
class J3DModelData;
struct csXyz;

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
};

class dPa_followEcallBack : public dPa_levelEcallBack {
public:
    dPa_followEcallBack(u8=0, u8=0);
    virtual ~dPa_followEcallBack() {}
    
    virtual void execute(JPABaseEmitter*);
    virtual void draw(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);
    virtual void end();
    
    JPABaseEmitter* getEmitter() { return mpEmitter; }
    void setRateOff(u8 param_0) { field_0x11 = param_0; }
    
    /* 0x04 */ JPABaseEmitter* mpEmitter;
    /* 0x08 */ u8 field_0x08[0x10 - 0x08];
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
};

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
    
    /* 0x14 */ s8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ GXColor field_0x16;
    /* 0x1A */ u8 field_0x1A[0x1C - 0x1A];
    /* 0x1C */ dKy_tevstr_c* mTevstr;
};

STATIC_ASSERT(sizeof(dPa_smokeEcallBack) == 0x20);

class dPa_simpleEcallBack : public JPACallBackBase<JPABaseEmitter*> {
public:
    dPa_simpleEcallBack();
    virtual ~dPa_simpleEcallBack() {}

    void executeAfter(JPABaseEmitter*);
    void draw(JPABaseEmitter*);
    void create(JPAEmitterManager*, u16, u8);
    void createEmitter(JPAEmitterManager*);
    void set(cXyz const*, u8, GXColor const&, GXColor const&, int);

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

    virtual ~dPa_waveEcallBack() {}

    /* 0x04 */ s16 mState;
    /* 0x06 */ s16 mFadeTimer;
    /* 0x08 */ f32 mVelFade1;
    /* 0x0C */ f32 mVel;
    /* 0x10 */ f32 mVelSpeed;
    /* 0x14 */ f32 mVelFade2;
    /* 0x18 */ f32 mMaxParticleVelocity;
    /* 0x1C */ cXyz mCollapsePos[2];
    /* 0x34 */ cXyz* mpPos;
    /* 0x38 */ csXyz* mpRot;
    // /* 0x3C */ cXyz mRotMtx[3];
    /* 0x60 */ JPABaseEmitter* mpBaseEmitter;
};

class dPa_splashEcallBack : public dPa_levelEcallBack {
public:
    void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);
    void remove();
    void execute(JPABaseEmitter*);

    virtual ~dPa_splashEcallBack() {}

    /* 0x04 */ s16 mState;
    /* 0x08 */ f32 mScaleTimer;
    /* 0x0C */ f32 mMaxScaleTimer;
    /* 0x10 */ cXyz* mpPos;
    /* 0x14 */ csXyz* mpRot;
    /* 0x18 */ JPABaseEmitter* mpBaseEmitter;
};

class dPa_trackEcallBack : public dPa_levelEcallBack {
public:
    void getMaxWaterY(JGeometry::TVec3<f32>*);
    void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);
    void remove();
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);

    virtual ~dPa_trackEcallBack() {}

    /* 0x04 */ s16 mState;
    /* 0x08 */ f32 mBaseY;
    /* 0x0C */ f32 mMinY;
    // /* 0x10 */ cXyz mPos[3];
    /* 0x34 */ cXyz* mpPos;
    /* 0x38 */ csXyz* mpRot;
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

    /* 0x04 */ JPABaseEmitter* mpBaseEmitter;
    /* 0x08 */ cXyz* mPos;
    /* 0x0C */ u32 mFlags;
    /* 0x10 */ f32 mRate;
};

class dPa_modelEmitter_c {
public:
    u8 temp[0xC];
    
    dPa_modelEmitter_c();
    virtual ~dPa_modelEmitter_c() {}
};

class JKRSolidHeap;

class dPa_J3DmodelEmitter_c : public dPa_modelEmitter_c {
public:
    u8 temp2[4];
    JKRSolidHeap* mpHeap;
    
    dPa_J3DmodelEmitter_c(JPABaseEmitter*, J3DModelData*, dKy_tevstr_c&, J3DAnmTexPattern*, unsigned short, int);
    virtual ~dPa_J3DmodelEmitter_c();
    
    virtual void draw();
};

class dPa_J3Dmodel_c {
public:
    dPa_J3Dmodel_c();
};

class dPa_smokePcallBack : public JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*> {
public:
    dPa_smokePcallBack();
    virtual ~dPa_smokePcallBack() {}
    
    virtual void execute(JPABaseEmitter*, JPABaseParticle*);
    virtual void draw(JPABaseEmitter*, JPABaseParticle*);
};

class dPa_selectTexEcallBack : public dPa_levelEcallBack {
public:
    dPa_selectTexEcallBack();
    virtual ~dPa_selectTexEcallBack() {}
    
    virtual void draw(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
};

class dPa_windPcallBack : public JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*> {
public:
    dPa_windPcallBack();
    virtual ~dPa_windPcallBack() {}
    
    virtual void execute(JPABaseEmitter*, JPABaseParticle*);
};

class dPa_singleRippleEcallBack : public dPa_levelEcallBack {
public:
    dPa_singleRippleEcallBack();
    virtual ~dPa_singleRippleEcallBack() {}
    
    virtual void execute(JPABaseEmitter*);
    virtual void draw(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
};

class dPa_ripplePcallBack : public JPACallBackBase2<JPABaseEmitter*, JPABaseParticle*> {
public:
    dPa_ripplePcallBack();
    virtual ~dPa_ripplePcallBack() {}
    
    virtual void execute(JPABaseEmitter*, JPABaseParticle*);
    virtual void draw(JPABaseEmitter*, JPABaseParticle*);
};

class dPa_cutTurnEcallBack_c : public dPa_levelEcallBack {
public:
    dPa_cutTurnEcallBack_c();
    virtual ~dPa_cutTurnEcallBack_c() {}
    
    virtual void executeAfter(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
    void end();

public:
    /* 0x04 */ u8 field_0x04[0x0c];
};

STATIC_ASSERT(sizeof(dPa_cutTurnEcallBack_c) == 0x10);

class dPa_stripesEcallBack : public dPa_levelEcallBack {
public:
    dPa_stripesEcallBack();
    virtual ~dPa_stripesEcallBack() {}
    
    virtual void draw(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
};

class dPa_kageroEcallBack : public JPACallBackBase<JPABaseEmitter*> {
public:
    dPa_kageroEcallBack();
    virtual ~dPa_kageroEcallBack() {}
    
    virtual void draw(JPABaseEmitter*);
};

class dPa_bombSmokeEcallBack : public dPa_levelEcallBack {
public:
    dPa_bombSmokeEcallBack();
    virtual ~dPa_bombSmokeEcallBack() {}
    
    virtual void execute(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
};

class dPa_setColorEcallBack : public dPa_levelEcallBack {
public:
    dPa_setColorEcallBack();
    virtual ~dPa_setColorEcallBack() {}
    
    virtual void draw(JPABaseEmitter*);
    virtual void setup(JPABaseEmitter*, const cXyz*, const csXyz*, s8);
};

class dPa_modelControl_c {
public:
    dPa_modelControl_c(J3DModelData*);
    ~dPa_modelControl_c();

    void newModel(J3DModelData*);
    void draw();

    /* 0x00 */ node_list_class parent;
    /* 0x0C */ void* field_0x0c;
    /* 0x10 */ void* field_0x10;
    /* 0x14 */ void* field_0x14;
    /* 0x18 */ void* field_0x18;
    /* 0x1C */ void* field_0x1c;
    /* 0x20 */ void* field_0x20;
    /* 0x24 */ void* field_0x24;
    /* 0x28 */ void* field_0x28;
    /* 0x2C */ void* field_0x2c;
    /* 0x30 */ void* field_0x30;
    /* 0x34 */ void* field_0x34;
    /* 0x38 */ void* field_0x38;
    /* 0x3C */ void* field_0x3c;
    /* 0x40 */ void* field_0x40;
    /* 0x44 */ void* field_0x44;
    /* 0x48 */ void* field_0x48;
    /* 0x4C */ void* field_0x4c;
    /* 0x50 */ void* field_0x50;
    /* 0x54 */ void* field_0x54;
    /* 0x58 */ void* field_0x58;
    /* 0x5C */ void* field_0x5c;
    /* 0x60 */ void* field_0x60;
    /* 0x64 */ void* field_0x64;
    /* 0x68 */ void* field_0x68;
    /* 0x6C */ void* field_0x6c;
    /* 0x70 */ void* field_0x70;
    /* 0x74 */ void* field_0x74;
    /* 0x78 */ void* field_0x78;
    /* 0x7C */ void* field_0x7c;
    /* 0x80 */ void* field_0x80;
    // /* 0x84 */ J3DVertexData mVertexData;
};

class dPa_control_c {
public:
    dPa_control_c();

    void getRM_ID(u16);
    void swapFrameBufferTexture();
    void createCommon(void const*);
    void createRoomScene(void const*);
    bool readScene(u8, mDoDvdThd_toMainRam_c**);
    void createScene(void const*);
    void removeRoomScene();
    void removeScene();
    void calc3D();
    void calc2D();
    void calcMenu();
    void draw(JPADrawInfo*, u8);
    JPABaseEmitter* set(u8, u16, cXyz const*, csXyz const*, cXyz const*, u8, dPa_levelEcallBack*,
                        s8, GXColor const*, GXColor const*, cXyz const*);
    JPABaseEmitter* setBombSmoke(u16, cXyz const*, csXyz const*, cXyz const*, u8);
    void setSimpleLand(int, cXyz const*, csXyz const*, f32, f32, f32, dKy_tevstr_c*, int*, int);
    void setSimpleLand(cBgS_PolyInfo&, cXyz const*, csXyz const*, f32, f32, f32, dKy_tevstr_c*,
                       int*, int);
    void checkAtrCodeEffect(int);
    void setNormalStripes(u16, cXyz const*, csXyz const*, cXyz const*, u8, u16);
    void newSimple(u16, u8);
    void setSimple(u16, cXyz const*, u8, GXColor const&, GXColor const&, int);
    void getSimple(u16);

    JPABaseEmitter* setNormal(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(0, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setNormalP1(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(1, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setToon(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(2, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setToonP1(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(3, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setProjection(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(4, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* setShipTail(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(5, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* set2Dfore(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(7, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* set2Dback(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(8, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }
    JPABaseEmitter* set2DmenuFore(u16 particleID, const cXyz* pos, const csXyz* angle,
                              const cXyz* scale, u8 alpha, dPa_levelEcallBack* pCallBack,
                              s8 setupInfo, const GXColor* pPrmColor, const GXColor* pEnvColor,
                              const cXyz* pScale2D) {
        return set(9, particleID, pos, angle, scale, alpha, pCallBack, setupInfo, pPrmColor, pEnvColor, pScale2D);
    }

    
    void drawModelParticle() { mModelCtrl->draw(); }
    JKRHeap * getHeap() { return mpHeap; }

    /* 0x0000 */ JKRHeap* mpHeap;
    /* 0x0004 */ JPAResourceManager* mpCommonResMgr;
    /* 0x0008 */ dPa_modelControl_c* mModelCtrl;
    /* 0x000C */ JKRHeap* mpSceneHeap;
    /* 0x0010 */ void* mpData;
    /* 0x0014 */ JPAResourceManager* mpSceneResMgr;
    /* 0x0018 */ u8 mSceneNo;
    /* 0x0019 */ u8 mCount;
    /* 0x001A */ u8 mNumSimple;
    /* 0x001B */ u8 mNumSimpleCommon;
    /* 0x001C */ dPa_simpleEcallBack mSimpleCallbacks[25];
};

#endif /* D_PARTICLE */
