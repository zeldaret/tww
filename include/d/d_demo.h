#ifndef D_DEMO_H
#define D_DEMO_H

#include "dolphin/types.h"
#include "JSystem/JStage/JSGActor.h"
#include "JSystem/JStage/JSGAmbientLight.h"
#include "JSystem/JStage/JSGCamera.h"
#include "JSystem/JStage/JSGFog.h"
#include "JSystem/JStage/JSGLight.h"
#include "JSystem/JStage/JSGSystem.h"
#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"

class dDemo_system_c;
class TControl;
class dMesg_tControl;
class fopAc_ac_c;

class dDemo_actor_c : public JStage::TActor {
public:
    dDemo_actor_c();
    ~dDemo_actor_c();
    void getActor();
    void setActor(fopAc_ac_c*);
    void getP_BtpData(const char*);
    void getP_BrkData(const char*);
    void getP_BtkData(const char*);
    void getPrm_Morf();
    void JSGSetData(u32, const void*, u32);
    void JSGSetTranslation(const Vec&);
    void JSGSetScaling(const Vec&);
    void JSGSetRotation(const Vec&);
    void JSGSetShape(u32);
    void JSGSetAnimation(u32);
    void JSGSetAnimationFrame(f32);
    void JSGSetAnimationTransition(f32);
    void JSGSetTextureAnimation(u32);
    void JSGSetTextureAnimationFrame(f32);
    s32 JSGFindNodeID(const char*) const;
    int JSGGetNodeTransformation(u32, f32(*)[4]) const;
    f32 JSGGetAnimationFrameMax() const;
    f32 JSGGetTextureAnimationFrameMax() const;
    void JSGGetTranslation(Vec*) const;
    void JSGGetScaling(Vec*) const;
    void JSGGetRotation(Vec*) const;

    bool checkEnable(u16 mask) { return mFlags & mask; }
    csXyz* getRatate() { return &mRotation; }

    /* 0x04 */ u16 mFlags;
    /* 0x06 */ u8 field_0x06[0x08 - 0x06];
    /* 0x08 */ cXyz mTranslation;
    /* 0x14 */ cXyz mScaling;
    /* 0x20 */ csXyz mRotation;
    /* 0x26 */ u8 field_0x26[0x28 - 0x26];
    /* 0x28 */ u32 mShape;
    /* 0x2C */ u32 mNextBckId;
    /* 0x30 */ f32 mAnimationFrame;
    /* 0x34 */ f32 mAnimationTransition;
    /* 0x38 */ f32 mAnimationFrameMax;
    /* 0x3C */ s32 mTexAnimation;
    /* 0x40 */ f32 mTexAnimationFrame;
    /* 0x44 */ void* mTexAnimationFrameMax;
    /* 0x48 */ J3DModel* mpModel;
    /* 0x4C */ u32 field_0x4c;
    /* 0x50 */ void* field_0x50;
    /* 0x54 */ u32 field_0x54;
    /* 0x58 */ s32 mActorPcId;
    /* 0x5C */ s32 mBckId;
    /* 0x60 */ s32 mBtpId;
    /* 0x64 */ s32 mBtkId;
    /* 0x68 */ s32 mBrkId;
};

class dDemo_camera_c : public JStage::TCamera {
public:
    ~dDemo_camera_c();
    f32 JSGGetProjectionNear() const;
    void JSGSetProjectionNear(f32);
    f32 JSGGetProjectionFar() const;
    void JSGSetProjectionFar(f32);
    f32 JSGGetProjectionFovy() const;
    void JSGSetProjectionFovy(f32);
    f32 JSGGetProjectionAspect() const;
    void JSGSetProjectionAspect(f32);
    void JSGGetViewPosition(Vec*) const;
    void JSGSetViewPosition(const Vec&);
    void JSGGetViewUpVector(Vec*) const;
    void JSGSetViewUpVector(const Vec&);
    void JSGGetViewTargetPosition(Vec*) const;
    void JSGSetViewTargetPosition(const Vec&);
    f32 JSGGetViewRoll() const;
    void JSGSetViewRoll(f32);
};

class dDemo_ambient_c : public JStage::TAmbientLight {
public:
    ~dDemo_ambient_c();
    void JSGSetColor(_GXColor);
};

class dDemo_light_c : public JStage::TLight {
public:
    ~dDemo_light_c();
    void JSGSetLightType(JStage::TELight);
    void JSGSetPosition(const Vec&);
    void JSGSetColor(_GXColor);
    void JSGSetDistanceAttenuation(f32, f32, _GXDistAttnFn);
    void JSGSetAngleAttenuation(f32, _GXSpotFn);
    void JSGSetDirection(const Vec&);
};

class dDemo_fog_c : public JStage::TFog {
public:
    ~dDemo_fog_c();
    void JSGSetFogFunction(_GXFogType);
    void JSGSetStartZ(f32);
    void JSGSetEndZ(f32);
    void JSGSetColor(_GXColor);
};

class dDemo_object_c {
public:
    dDemo_object_c();
    ~dDemo_object_c();

    void appendActor(fopAc_ac_c*);
    dDemo_actor_c* getActor(u8);
    void createCamera();
    void getActiveCamera();
    void createAmbient();
    void appendLight();
    void createFog();
    void remove();

    /* 0x00 */ u8 mNumActor;
    /* 0x01 */ u8 mNumLight;
    /* 0x04 */ dDemo_actor_c* mpActors[32];
    /* 0x84 */ dDemo_camera_c* mpActiveCamera;
    /* 0x88 */ dDemo_ambient_c* mpAmbient;
    /* 0x8C */ dDemo_light_c* mpLight[8];
    /* 0xAC */ u8 field_0xac[4];
};

class dDemo_system_c : public JStage::TSystem {
public:
    ~dDemo_system_c();
    bool JSGFindObject(const char*, JStage::TEObject) const;
};

class dDemo_manager_c {
public:
    dDemo_manager_c();
    ~dDemo_manager_c();

    void create(u8 const*, cXyz*, f32);
    void remove();
    void update();

    int getFrame() { return mFrame; }
    u32 getFrameNoMsg() { return mFrameNoMsg; }
    s32 getMode() { return mMode; }

    /* 0x00 */ dDemo_system_c* mSystem;
    /* 0x04 */ TControl* mControl;
    /* 0x08 */ void* mStage;
    /* 0x0C */ void* mAudio;
    /* 0x10 */ void* mParticle;
    /* 0x14 */ void* mFactory;
    /* 0x18 */ dMesg_tControl* mMesgControl;
    /* 0x1C */ void* mMessage;
    /* 0x20 */ dDemo_object_c mDemoObj;
    /* 0xD0 */ void* field_0xd0;
    /* 0xD4 */ int mFrame;
    /* 0xD8 */ int mFrameNoMsg;
    /* 0xDC */ int mMode;
};

class mDoExt_McaMorf;
BOOL dDemo_setDemoData(fopAc_ac_c*, u8, mDoExt_McaMorf*, const char*, int, u16*, u32, s8);

#endif /* D_DEMO_H */
