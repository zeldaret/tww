#ifndef D_A_ITEM_H
#define D_A_ITEM_H

#include "d/actor/d_a_itembase.h"
#include "d/d_particle.h"
#include "f_pc/f_pc_manager.h"

class daItem_c : public daItemBase_c {
public:
    typedef void (daItem_c::*daItem_c_ModeFunc)();
    
    enum State {
        STATE_WAIT_MAIN     = 0x2,
        STATE_BRING_NEZUMI  = 0x3,
        STATE_INIT_NORMAL   = 0x5,
        STATE_MAIN_NORMAL   = 0x6,
        STATE_INIT_GET_DEMO = 0x7,
        STATE_WAIT_GET_DEMO = 0x8,
        STATE_MAIN_GET_DEMO = 0x9,
        STATE_WAIT_BOSS1    = 0xA,
        STATE_WAIT_BOSS2    = 0xB,
    };
    
    float getYOffset();
    void set_mtx();
    void set_mtx_base(J3DModel*, cXyz, csXyz);
    void CreateInit();
    s32 _daItem_create();
    BOOL _daItem_execute();
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
    BOOL _daItem_draw();
    void setTevStr();
    BOOL _daItem_delete();
    void itemGetExecute();
    void itemDefaultRotateY();
    BOOL checkItemDisappear();
    void setItemTimer(int);
    BOOL checkPlayerGet();
    BOOL itemActionForRupee();
    BOOL itemActionForHeart();
    BOOL itemActionForKey();
    BOOL itemActionForEmono();
    BOOL itemActionForSword();
    BOOL itemActionForArrow();
    void checkWall();
    void set_bound_se();
    BOOL checkGetItem();
    BOOL timeCount();
    void mode_wait_init();
    void mode_water_init();
    void mode_wait();
    void mode_water();
    BOOL initAction();
    BOOL _daItem_isdelete();
    
    s32 checkControl();
    s32 startControl();
    s32 endControl();
    s32 checkLock();
    s32 setLock();
    s32 releaseLock();
    s32 checkActionNow();
    
    static dCcD_SrcCyl m_cyl_src;
    static s32 m_timer_max;

public:
    /* 0x63C */ cXyz mScaleTarget;
    /* 0x648 */ s32 mSwitchId;
    /* 0x64C */ s32 mActivationSwitch;
    /* 0x650 */ f32 field_0x650;
    /* 0x654 */ s16 field_0x654;
    /* 0x656 */ s16 mTargetAngleX;
    /* 0x658 */ s16 mDisappearTimer;
    /* 0x65A */ s16 field_0x65a;
    /* 0x65C */ s16 field_0x65c;
    /* 0x65E */ s16 mExtraZRot;
    /* 0x660 */ s16 field_0x660;
    /* 0x662 */ u8 field_0x662[0x666 - 0x662];
    /* 0x666 */ u8 field_0x666;
    /* 0x667 */ u8 mType;
    /* 0x668 */ u8 mAction;
    /* 0x669 */ u8 mStatusFlags; // TODO rename this
    /* 0x66A */ u8 mMode;
    /* 0x66B */ u8 mCurState;
    /* 0x66C */ u8 mOnGroundTimer;
    /* 0x66D */ u8 field_0x66D[0x670 - 0x66D];
    /* 0x670 */ u32 mDemoItemBsPcId;
    /* 0x674 */ dPa_rippleEcallBack mPtclRippleCb;
    /* 0x688 */ dPa_followEcallBack mPtclFollowCb;
    /* 0x69C */ dPa_smokeEcallBack mPtclSmokeCb;
    /* 0x6BC */ JPABaseEmitter* mpParticleEmitter;
    
    // TODO add enums for type, action, state, and status flags
    // state 7 is probably "about to start an item get demo"
};

STATIC_ASSERT(sizeof(daItem_c) == 0x6C0);

namespace daItem_prm {
    inline u32 getType(daItem_c* item) { return (fpcM_GetParam(item) & 0x03000000) >> 0x18; }
    inline u32 getAction(daItem_c* item) { return (fpcM_GetParam(item) & 0xFC000000) >> 0x1A; }
    inline u32 getItemNo(daItem_c* item) { return (fpcM_GetParam(item) & 0x000000FF) >> 0x00; }
    inline u32 getItemBitNo(daItem_c* item) { return (fpcM_GetParam(item) & 0x0000FF00) >> 0x08; }
    inline u32 getSwitchNo(daItem_c* item) { return (item->orig.angle.z & 0x00FF) >> 0; }
    inline u32 getSwitchNo2(daItem_c* item) { return (fpcM_GetParam(item) & 0x00FF0000) >> 0x10; }
};

#endif /* D_A_ITEM_H */