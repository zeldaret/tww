#ifndef D_DEMO_H
#define D_DEMO_H

#include "dolphin/types.h"
#include "JSystem/JStage/JSGActor.h"
#include "JSystem/JStage/JSGAmbientLight.h"
#include "JSystem/JStage/JSGCamera.h"
#include "JSystem/JStage/JSGFog.h"
#include "JSystem/JStage/JSGLight.h"
#include "JSystem/JStage/JSGSystem.h"
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/J3DGraphAnimator/J3DModelData.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JUtility/JUTNameTab.h"
#include "JSystem/JStudio/JStudio/jstudio-control.h"
#include "JSystem/JStudio/JStudio_JAudio/control.h"
#include "JSystem/JStudio/JStudio_JMessage/control.h"
#include "JSystem/JStudio/JStudio_JParticle/control.h"
#include "JSystem/JStudio/JStudio_JStage/control.h"
#include "m_Do/m_Do_mtx.h"

class fopAc_ac_c;

class dMesg_tControl : public JMessage::TControl {
public:
    dMesg_tControl();

    /* 0x3C */ u8 field_0x3C[0x74 - 0x3C];
};  // Size: 0x74

class dDemo_actor_c : public JStage::TActor {
public:
    dDemo_actor_c();
    ~dDemo_actor_c();
    fopAc_ac_c* getActor();
    void setActor(fopAc_ac_c*);
    void* getP_BtpData(const char*);
    void* getP_BrkData(const char*);
    void* getP_BtkData(const char*);
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
    s32 JSGFindNodeID(const char* name) const {
        JUT_ASSERT(0x4d, mModel != 0);
        return mModel->getModelData()->getJointName()->getIndex(name);
    }
    int JSGGetNodeTransformation(u32 no, Mtx dst) const {
        JUT_ASSERT(0x52, mModel != 0);
        cMtx_copy(mModel->getAnmMtx((u16)no), dst);
        return 1;
    }
    f32 JSGGetAnimationFrameMax() const { return mAnimationFrameMax; }
    f32 JSGGetTextureAnimationFrameMax() const { return mTexAnimationFrameMax; }
    void JSGGetTranslation(Vec* dst) const { *dst = mTranslation; }
    void JSGGetScaling(Vec* dst) const { *dst = mScaling; }
    void JSGGetRotation(Vec* dst) const {
        dst->x = cM_sht2d(mRotation.x);
        dst->y = cM_sht2d(mRotation.y);
        dst->z = cM_sht2d(mRotation.z);
    }

    bool checkEnable(u16 mask) { return mFlags & mask; }
    csXyz* getRatate() { return &mRotation; }
    u32 getShapeId() { return mShapeId; }

    void getAnmFrame() {}
    void getAnmId() {}
    void getAnmTransition() {}
    void getOldAnmId() {}
    void getOldScrId() {}
    void getOldTevId() {}
    void getOldTexId() {}
    void getPrm() {}
    void getScale() {}
    void getTrans() {}
    void onEnable(u16) {}
    void setAnmFrameMax(f32) {}
    void setModel(J3DModel*) {}
    void setOldAnmId(u32) {}
    void setOldScrId(u32) {}
    void setOldTevId(u32) {}
    void setOldTexId(u32) {}
    void setTexAnmFrameMax(f32) {}

    /* 0x04 */ u16 mFlags;
    /* 0x06 */ u8 field_0x06[0x08 - 0x06];
    /* 0x08 */ cXyz mTranslation;
    /* 0x14 */ cXyz mScaling;
    /* 0x20 */ csXyz mRotation;
    /* 0x26 */ u8 field_0x26[0x28 - 0x26];
    /* 0x28 */ u32 mShapeId;
    /* 0x2C */ u32 mNextBckId;
    /* 0x30 */ f32 mAnimationFrame;
    /* 0x34 */ f32 mAnimationTransition;
    /* 0x38 */ f32 mAnimationFrameMax;
    /* 0x3C */ s32 mTexAnimation;
    /* 0x40 */ f32 mTexAnimationFrame;
    /* 0x44 */ f32 mTexAnimationFrameMax;
    /* 0x48 */ J3DModel* mModel;
    /* 0x4C */ u32 field_0x4c;
    /* 0x50 */ const void* field_0x50;
    /* 0x54 */ u32 field_0x54;
    /* 0x58 */ uint mActorPcId;
    /* 0x5C */ s32 mBckId;
    /* 0x60 */ s32 mBtpId;
    /* 0x64 */ s32 mBtkId;
    /* 0x68 */ s32 mBrkId;
};

class dDemo_camera_c : public JStage::TCamera {
public:
    dDemo_camera_c() { mFlags = 0; }
    ~dDemo_camera_c() {}
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

private:
    /* 0x04 */ u8 mFlags;
    /* 0x08 */ f32 mProjNear;
    /* 0x0C */ f32 mProjFar;
    /* 0x10 */ f32 mFovy;
    /* 0x14 */ f32 mAspect;
    /* 0x18 */ cXyz mViewPosition;
    /* 0x24 */ cXyz mUpVector;
    /* 0x30 */ cXyz mTargetPosition;
    /* 0x3C */ f32 mRoll;
};

class dDemo_ambient_c : public JStage::TAmbientLight {
public:
    dDemo_ambient_c() { mFlags = 0; }
    ~dDemo_ambient_c() {}
    void JSGSetColor(GXColor color);

private:
    /* 0x04 */ u8 mFlags;
    /* 0x08 */ GXColor mColor;
};

class dDemo_light_c : public JStage::TLight {
public:
    dDemo_light_c() { mFlags = 0; }
    ~dDemo_light_c() {}
    void JSGSetLightType(JStage::TELight);
    void JSGSetPosition(const Vec&);
    void JSGSetColor(_GXColor);
    void JSGSetDistanceAttenuation(f32, f32, GXDistAttnFn);
    void JSGSetAngleAttenuation(f32, GXSpotFn);
    void JSGSetDirection(const Vec&);

private:
    /* 0x04 */ u8 mFlags;
    /* 0x08 */ JStage::TELight mLightType;
    /* 0x0C */ GXDistAttnFn mAttnFn;
    /* 0x10 */ GXSpotFn mSpotFn;
    /* 0x14 */ cXyz mPosition;
    /* 0x20 */ GXColor mColor;
    /* 0x24 */ f32 mDistAttn0;
    /* 0x28 */ f32 mDistAttn1;
    /* 0x2C */ f32 mAngleAttn;
    /* 0x30 */ cXyz mDirection;
};

class dDemo_fog_c : public JStage::TFog {
public:
    dDemo_fog_c() { mFlags = 0; }
    ~dDemo_fog_c() {}
    void JSGSetFogFunction(_GXFogType);
    void JSGSetStartZ(f32);
    void JSGSetEndZ(f32);
    void JSGSetColor(_GXColor);

private:
    /* 0x04 */ u8 mFlags;
    /* 0x05 */ u8 mFogType;
    /* 0x08 */ f32 mStartZ;
    /* 0x0C */ f32 mEndZ;
    /* 0x10 */ GXColor mColor;
};

class dDemo_object_c {
public:
    dDemo_object_c();
    ~dDemo_object_c();

    dDemo_actor_c* appendActor(fopAc_ac_c*);
    dDemo_actor_c* getActor(u8);
    dDemo_camera_c* createCamera();
    dDemo_camera_c* getActiveCamera();
    dDemo_ambient_c* createAmbient();
    dDemo_light_c* appendLight();
    dDemo_fog_c* createFog();
    void remove();

    /* 0x00 */ u8 mNumActor;
    /* 0x01 */ u8 mNumLight;
    /* 0x04 */ dDemo_actor_c* mpActors[32];
    /* 0x84 */ dDemo_camera_c* mpActiveCamera;
    /* 0x88 */ dDemo_ambient_c* mpAmbient;
    /* 0x8C */ dDemo_light_c* mpLight[8];
    /* 0xAC */ dDemo_fog_c* mpFog;
};

class dDemo_system_c : public JStage::TSystem {
public:
    dDemo_system_c() : mObject(NULL) {}
    ~dDemo_system_c();
    void* JSGFindObject(const char*, JStage::TEObject) const;
    void setObject(dDemo_object_c* obj) { mObject = obj; }

private:
    /* 0x04 */ dDemo_object_c* mObject;
};

class dDemo_manager_c {
public:
    dDemo_manager_c();
    ~dDemo_manager_c();

    bool create(const u8*, cXyz*, f32);
    void remove();
    bool update();

    int getFrame() { return mFrame; }
    u32 getFrameNoMsg() { return mFrameNoMsg; }
    s32 getMode() { return mMode; }

    /* 0x00 */ dDemo_system_c* mSystem;
    /* 0x04 */ JStudio::TControl* mControl;
    /* 0x08 */ JStudio_JStage::TCreateObject* mStage;
    /* 0x0C */ JStudio_JAudio::TCreateObject* mAudio;
    /* 0x10 */ JStudio_JParticle::TCreateObject* mParticle;
    /* 0x14 */ JStudio::TFactory* mFactory;
    /* 0x18 */ dMesg_tControl* mMesgControl;
    /* 0x1C */ JStudio_JMessage::TCreateObject* mMessage;
    /* 0x20 */ dDemo_object_c mDemoObj;
    /* 0xD0 */ char* mCurFile;
    /* 0xD4 */ int mFrame;
    /* 0xD8 */ int mFrameNoMsg;
    /* 0xDC */ int mMode;
};

class mDoExt_McaMorf;
BOOL dDemo_setDemoData(fopAc_ac_c*, u8, mDoExt_McaMorf*, const char*, int, u16*, u32, s8);

#endif /* D_DEMO_H */
