#ifndef D_DEMO_H
#define D_DEMO_H

#include "dolphin/types.h"

class dDemo_actor_c;
class dDemo_camera_c;
class dDemo_ambient_c;
class dDemo_light_c;
class dDemo_system_c;
class TControl;
class dMesg_tControl;
class fopAc_ac_c;

class dDemo_actor_c /* : public JStage::TActor */ {
public:
    void setActor(fopAc_ac_c*);
    
    bool checkEnable(u16 mask) { return mFlags & mask; }
    csXyz* getRatate() { return &mRotation; }
    
    /* 0x00 */ u8 parent_placeholder[0x04 - 0x00];
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

class dDemo_manager_c {
public:
    dDemo_manager_c();
    ~dDemo_manager_c();

    void create(u8 const*, cXyz*, f32);
    void remove();
    void update();
    
    int getFrame() { return mFrame; }

    /* 0x00 */ dDemo_system_c* mpSystem;
    /* 0x04 */ TControl* mpControl;
    /* 0x08 */ void* mpStage;
    /* 0x0C */ void* mpAudio;
    /* 0x10 */ void* mpParticle;
    /* 0x14 */ void* field_0x14;
    /* 0x18 */ dMesg_tControl* mpMesgControl;
    /* 0x1C */ void* mpMessage;
    /* 0x20 */ dDemo_object_c mDemoObj;
    /* 0xD0 */ void* field_0xd0;
    /* 0xD4 */ int mFrame;
    /* 0xD8 */ int field_0xd8;
    /* 0xDC */ int mState;
};

void dDemo_setDemoData(fopAc_ac_c*, u8, mDoExt_McaMorf*, const char*, int, u16*, u32, s8);

#endif /* D_DEMO_H */