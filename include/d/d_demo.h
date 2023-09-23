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
    /* 0xD4 */ void* field_0xd4;
    /* 0xD8 */ int field_0xd8;
    /* 0xDC */ int mState;
};

#endif /* D_DEMO_H */