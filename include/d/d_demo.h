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
#include "f_pc/f_pc_base.h"

class fopAc_ac_c;
class dMesg_tControl;

// TODO: made up, figure out what this is
struct dDemo_prm_data {
    /* 0x0 */ u8 field_0x0[0x4 - 0x0];
    /* 0x4 */ s8 field_0x4;
    /* 0x5 */ u8 field_0x5[0x6 - 0x5];
    /* 0x6 */ s8 field_0x6;
    /* 0x7 */ s8 field_0x7;
    /* 0x8 */ u8 field_0x8[0xB - 0x8];
    /* 0xB */ s8 field_0xb;
    /* 0xC */ u8 field_0xc[0xF - 0xC];
    /* 0xF */ s8 field_0xf;
};

class dDemo_prm_c {
public:
    u32 getId() { return mId; }
    dDemo_prm_data* getData() { return mData; }

public:
    /* 0x0 */ u32 mId;
    /* 0x4 */ dDemo_prm_data* mData;
};

class dDemo_actor_c : public JStage::TActor {
public:
    enum Enable_e {
        /* 0x001 */ ENABLE_UNK_e = (1 << 0),
        /* 0x002 */ ENABLE_TRANS_e = (1 << 1),
        /* 0x004 */ ENABLE_SCALE_e = (1 << 2),
        /* 0x008 */ ENABLE_ROTATE_e = (1 << 3),
        /* 0x010 */ ENABLE_SHAPE_e = (1 << 4),
        /* 0x020 */ ENABLE_ANM_e = (1 << 5),
        /* 0x040 */ ENABLE_ANM_FRAME_e = (1 << 6),
        /* 0x080 */ ENABLE_TEX_ANM = (1 << 7),
        /* 0x100 */ ENABLE_TEX_ANM_FRAME_e = (1 << 8),
    };

    dDemo_actor_c();
    ~dDemo_actor_c();
    fopAc_ac_c* getActor();
    void setActor(fopAc_ac_c*);
    void* getP_BtpData(const char*);
    void* getP_BrkData(const char*);
    void* getP_BtkData(const char*);
    f32 getPrm_Morf();
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
        JUT_ASSERT(0x4d, mModel != NULL);
        return mModel->getModelData()->getJointName()->getIndex(name);
    }
    bool JSGGetNodeTransformation(u32 no, Mtx dst) const {
        JUT_ASSERT(0x52, mModel != NULL);
        cMtx_copy(mModel->getAnmMtx((u16)no), dst);
        return true;
    }
    f32 JSGGetAnimationFrameMax() const { return mAnmFrameMax; }
    f32 JSGGetTextureAnimationFrameMax() const { return mTexAnimationFrameMax; }
    void JSGGetTranslation(Vec* dst) const { *dst = mTrans; }
    void JSGGetScaling(Vec* dst) const { *dst = mScale; }
    void JSGGetRotation(Vec* dst) const {
        dst->x = cM_sht2d(mRotate.x);
        dst->y = cM_sht2d(mRotate.y);
        dst->z = cM_sht2d(mRotate.z);
    }

    u32 checkEnable(u16 mask) { return mFlags & mask; }
    void onEnable(u16 flag) { mFlags |= flag; }
    cXyz* getTrans() { return &mTrans; }
    cXyz* getScale() { return &mScale; }
    csXyz* getRatate() { return &mRotate; }
    u32 getShapeId() { return mShapeId; }
    u32 getAnmId() { return mAnmId; }
    f32 getAnmFrame() { return mAnmFrame; }
    f32 getAnmTransition() { return mAnmTransition; }
    void setAnmFrameMax(f32 max) { mAnmFrameMax = max; }
    void setModel(J3DModel* model) { mModel = model; }
    dDemo_prm_c* getPrm() { return &mPrm; }
    u32 getOldAnmId() { return mOldAnmId; }
    void setOldAnmId(u32 id) { mOldAnmId = id; }

    void getOldScrId() {}
    void getOldTevId() {}
    void getOldTexId() {}
    void setOldScrId(u32) {}
    void setOldTevId(u32) {}
    void setOldTexId(u32) {}
    void setTexAnmFrameMax(f32) {}

private:
    /* 0x04 */ u16 mFlags;
    /* 0x08 */ cXyz mTrans;
    /* 0x14 */ cXyz mScale;
    /* 0x20 */ csXyz mRotate;
    /* 0x28 */ u32 mShapeId;
    /* 0x2C */ u32 mAnmId;
    /* 0x30 */ f32 mAnmFrame;
    /* 0x34 */ f32 mAnmTransition;
    /* 0x38 */ f32 mAnmFrameMax;
    /* 0x3C */ s32 mTexAnimation;
    /* 0x40 */ f32 mTexAnimationFrame;
    /* 0x44 */ f32 mTexAnimationFrameMax;
    /* 0x48 */ J3DModel* mModel;
    /* 0x4C */ dDemo_prm_c mPrm;
    /* 0x54 */ u32 field_0x54;
    /* 0x58 */ fpc_ProcID mActorId;
    /* 0x5C */ s32 mOldAnmId;
    /* 0x60 */ s32 mBtpId;
    /* 0x64 */ s32 mBtkId;
    /* 0x68 */ s32 mBrkId;
}; // size = 0x6C

class dDemo_camera_c : public JStage::TCamera {
public:
    enum Enable_e {
        /* 0x01 */ ENABLE_PROJ_NEAR_e = (1 << 0),
        /* 0x02 */ ENABLE_PROJ_FAR_e = (1 << 1),
        /* 0x04 */ ENABLE_PROJ_FOVY_e = (1 << 2),
        /* 0x08 */ ENABLE_PROJ_ASPECT_e = (1 << 3),
        /* 0x10 */ ENABLE_VIEW_POS_e = (1 << 4),
        /* 0x20 */ ENABLE_VIEW_UP_VEC_e = (1 << 5),
        /* 0x40 */ ENABLE_VIEW_TARG_POS_e = (1 << 6),
        /* 0x80 */ ENABLE_VIEW_ROLL_e = (1 << 7),
    };

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

    bool checkEnable(u8 mask) { return mFlags & mask; }
    void onEnable(u8 flag) { mFlags |= flag; }

    f32 getFovy() { return mFovy; }
    f32 getRoll() { return mRoll; }
    cXyz& getTarget() { return mTargetPosition; }
    cXyz& getTrans() { return mViewPosition; }
    cXyz& getUp() { return mUpVector; }

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
    enum Enable_e {
        /* 0x1 */ ENABLE_COLOR_e = (1 << 0),
    };

    dDemo_ambient_c() { mFlags = 0; }
    ~dDemo_ambient_c() {}
    void JSGSetColor(GXColor color);

    void onEnable(u8 flag) { mFlags |= flag; }

private:
    /* 0x04 */ u8 mFlags;
    /* 0x08 */ GXColor mColor;
};

class dDemo_light_c : public JStage::TLight {
public:
    enum Enable_e {
        /* 0x01 */ ENABLE_LIGHT_TYPE_e = (1 << 0),
        /* 0x02 */ ENABLE_POSITION_e = (1 << 1),
        /* 0x04 */ ENABLE_COLOR_e = (1 << 2),
        /* 0x08 */ ENABLE_DIST_ATTEN_e = (1 << 3),
        /* 0x10 */ ENABLE_ANGLE_ATTEN_e = (1 << 4),
        /* 0x20 */ ENABLE_DIRECTION_e = (1 << 5),
    };

    dDemo_light_c() { mFlags = 0; }
    ~dDemo_light_c() {}
    void JSGSetLightType(JStage::TELight);
    void JSGSetPosition(const Vec&);
    void JSGSetColor(GXColor);
    void JSGSetDistanceAttenuation(f32, f32, GXDistAttnFn);
    void JSGSetAngleAttenuation(f32, GXSpotFn);
    void JSGSetDirection(const Vec&);

    void onEnable(u8 flag) { mFlags |= flag; }

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
    enum Enable_e {
        /* 0x1 */ ENABLE_FOG_FN_e = (1 << 0),
        /* 0x2 */ ENABLE_START_Z_e = (1 << 1),
        /* 0x4 */ ENABLE_END_Z_e = (1 << 2),
        /* 0x8 */ ENABLE_COLOR_e = (1 << 3),
    };

    dDemo_fog_c() { mFlags = 0; }
    ~dDemo_fog_c() {}
    void JSGSetFogFunction(GXFogType);
    void JSGSetStartZ(f32);
    void JSGSetEndZ(f32);
    void JSGSetColor(GXColor);

    void onEnable(u8 flag) { mFlags |= flag; }

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

    dDemo_camera_c* getCamera() { return mpCamera; }
    void createEditorCamera() {}
    void getEditorCamera() {}
    void removeEditorCamera() {}

private:
    /* 0x00 */ u8 mNumActor;
    /* 0x01 */ u8 mNumLight;
    /* 0x04 */ dDemo_actor_c* mpActors[32];
    /* 0x84 */ dDemo_camera_c* mpCamera;
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

    dDemo_system_c* getSystem() { return mSystem;}
    JStudio::TControl* getControl() { return mControl; }
    dMesg_tControl* getMesgControl() { return mMesgControl; }
    dDemo_object_c* getObject() { return &mDemoObj; }
    int getFrame() { return mFrame; }
    u32 getFrameNoMsg() { return mFrameNoMsg; }
    s32 getMode() { return mMode; }

private:
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
#if VERSION == VERSION_DEMO
BOOL dDemo_setDemoData(fopAc_ac_c*, u8, mDoExt_McaMorf*, const char*, int = 0, u16* = NULL);
#else
BOOL dDemo_setDemoData(fopAc_ac_c*, u8, mDoExt_McaMorf*, const char*, int = 0, u16* = NULL, u32 = 0, s8 = 0);
#endif

#endif /* D_DEMO_H */
