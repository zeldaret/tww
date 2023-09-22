#ifndef D_A_ITEM_H
#define D_A_ITEM_H

#include "d/actor/d_a_itembase.h"
#include "d/d_particle.h"

class daItem_c : public daItemBase_c {
public:
    daItem_c() : mPtclFollowCb(0, 0), mPtclSmokeCb(1) {}
    
    float getYOffset();
    void set_mtx();
    void set_mtx_base(J3DModel*, cXyz, csXyz);
    void CreateInit();
    s32 _daItem_create();
    s32 _daItem_execute();
    void mode_proc_call();
    void execInitNormalDirection();
    void execMainNormalDirection();
    void execInitGetDemoDirection();
    void execWaitGetDemoDirection();
    void execMainGetDemoDirection();
    void execBringNezumi();
    void execWaitMain();
    void execWaitMainFromBoss();
    void scaleAnimFromBossItem();
    s32 _daItem_draw();
    void setTevStr();
    s32 _daItem_delete();
    void itemGetExecute();
    void itemDefaultRotateY();
    bool checkItemDisappear();
    void setItemTimer(int);
    BOOL checkPlayerGet();
    void itemActionForRupee();
    void itemActionForHeart();
    void itemActionForKey();
    void itemActionForEmono();
    void itemActionForSword();
    void itemActionForArrow();
    void checkWall();
    void set_bound_se();
    s32 checkGetItem();
    void timeCount();
    void mode_wait_init();
    void mode_water_init();
    void mode_wait();
    void mode_water();
    void initAction();
    s32 _daItem_isdelete();
    
    s32 checkControl();
    s32 startControl();
    s32 endControl();
    s32 checkLock();
    s32 setLock();
    s32 releaseLock();
    s32 checkActionNow();
    
    static dCcD_SrcCyl m_cyl_src;

public:
    /* 0x63C */ cXyz mScaleTarget;
    /* 0x648 */ s32 mSwitchId;
    /* 0x64C */ s32 mActivationSwitch;
    /* 0x650 */ f32 field3_0x650;
    /* 0x654 */ u8 field4_0x654[0x658 - 0x654];
    /* 0x658 */ s16 mItemTimer;
    /* 0x65A */ s16 field7_0x65a;
    /* 0x65C */ s16 field8_0x65c;
    /* 0x65E */ u8 field10_0x65e[0x667 - 0x65E];
    /* 0x667 */ u8 mUnknownParam;
    /* 0x668 */ u8 mItemAction;
    /* 0x669 */ u8 mStatusFlags;
    /* 0x66A */ u8 mMode;
    /* 0x66B */ u8 mCurState;
    /* 0x66C */ u8 field23_0x66c[0x674 - 0x66C];
    /* 0x674 */ dPa_rippleEcallBack mPtclRippleCb;
    /* 0x688 */ dPa_followEcallBack mPtclFollowCb;
    /* 0x69C */ dPa_smokeEcallBack mPtclSmokeCb;
    /* 0x6BC */ JPABaseEmitter* mpParticleEmitter;
};

STATIC_ASSERT(sizeof(daItem_c) == 0x6C0);

#endif /* D_A_ITEM_H */