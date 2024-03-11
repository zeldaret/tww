#ifndef D_A_ITEM_H
#define D_A_ITEM_H

#include "d/actor/d_a_itembase.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor_mng.h"
#include "SSystem/SComponent/c_lib.h"

class daItem_c : public daItemBase_c {
public:
    typedef void (daItem_c::*ModeFunc)();
    
    enum State {
        STATUS_UNK0          = 0x0,
        STATUS_UNK1          = 0x1,
        STATUS_WAIT_MAIN     = 0x2,
        STATUS_BRING_NEZUMI  = 0x3,
        STATUS_UNK4          = 0x4,
        STATUS_INIT_NORMAL   = 0x5,
        STATUS_MAIN_NORMAL   = 0x6,
        STATUS_INIT_GET_DEMO = 0x7,
        STATUS_WAIT_GET_DEMO = 0x8,
        STATUS_MAIN_GET_DEMO = 0x9,
        STATUS_WAIT_BOSS1    = 0xA,
        STATUS_WAIT_BOSS2    = 0xB,
    };
    
    enum Flag {
        FLAG_UNK02 = 0x02,
        FLAG_UNK04 = 0x04,
        FLAG_BOOMERANG = 0x08,
        FLAG_UNK10 = 0x10,
        FLAG_QUAKE = 0x20,
        FLAG_HOOK = 0x40,
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
    
    BOOL checkControl();
    BOOL startControl();
    BOOL endControl();
    BOOL checkLock();
    BOOL setLock();
    BOOL releaseLock();
    BOOL checkActionNow();
    
    u32 getItemNo() const { return m_itemNo; }
    void setItemTimerForIball(s16 param_1, s16 param_2) {
        mDisappearTimer = param_1;
        field_0x65a = param_2;
    }
    void setFlag(u8 flag) { cLib_onBit(mFlag, flag); }
    void clrFlag(u8 flag) { cLib_offBit(mFlag, flag); }
    bool checkFlag(u8 flag) { return cLib_checkBit(mFlag, flag); }
    void setStatus(u8 status) { mItemStatus = status; }
    void printStatus() {} // this might be a debug-only function
    
    static dCcD_SrcCyl m_cyl_src;
    static s32 m_timer_max;

public:
    /* 0x63C */ cXyz mScaleTarget;
    /* 0x648 */ s32 mSpawnSwitchNo;
    /* 0x64C */ s32 mCollideSwitchNo;
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
    /* 0x669 */ u8 mFlag;
    /* 0x66A */ u8 mMode;
    /* 0x66B */ u8 mItemStatus;
    /* 0x66C */ u8 mOnGroundTimer;
    /* 0x66D */ u8 field_0x66D[0x670 - 0x66D];
    /* 0x670 */ uint mDemoItemBsPcId;
    /* 0x674 */ dPa_rippleEcallBack mPtclRippleCb;
    /* 0x688 */ dPa_followEcallBack mPtclFollowCb;
    /* 0x69C */ dPa_smokeEcallBack mPtclSmokeCb;
    /* 0x6BC */ JPABaseEmitter* mpParticleEmitter;
    
    // TODO add enums for type, action, flags, mode, and status
    // status 7 is probably "about to start an item get demo"
};

STATIC_ASSERT(sizeof(daItem_c) == 0x6C0);

namespace daItem_prm {
    inline u32 getType(daItem_c* item) { return (fopAcM_GetParam(item) & 0x03000000) >> 0x18; }
    inline u32 getAction(daItem_c* item) { return (fopAcM_GetParam(item) & 0xFC000000) >> 0x1A; }
    inline u32 getItemNo(daItem_c* item) { return (fopAcM_GetParam(item) & 0x000000FF) >> 0x00; }
    inline u32 getItemBitNo(daItem_c* item) { return (fopAcM_GetParam(item) & 0x0000FF00) >> 0x08; }
    inline u32 getSwitchNo(daItem_c* item) { return (item->home.angle.z & 0x00FF) >> 0; }
    inline u32 getSwitchNo2(daItem_c* item) { return (fopAcM_GetParam(item) & 0x00FF0000) >> 0x10; }
};

#endif /* D_A_ITEM_H */