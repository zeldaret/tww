#ifndef D_A_NPC_SARACE_H
#define D_A_NPC_SARACE_H

#include "d/actor/d_a_obj_barrel2.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Sarace_c : public fopNpc_npc_c {
public:

    typedef BOOL (daNpc_Sarace_c::*ProcFunc)(void*);

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_ENDING   = -1,
    };

    void getAttentionBasePos() {}
    void getEyePos() {}
    daObjBarrel2::Act_c * getHBarrelP() {
        return (daObjBarrel2::Act_c* )fopAcM_SearchByID(mHBarrelId);
    }
    daObjBarrel2::Act_c * getVBarrelP() {
        return (daObjBarrel2::Act_c* )fopAcM_SearchByID(mVBarrelId);
    }
    void init() {}
    void setAction(ProcFunc func, void* arg) {
        if (mCurrActionFunc != func) {
            if (mCurrActionFunc) {
                mActionStatus = ACTION_ENDING;
                (this->*mCurrActionFunc)(NULL);
            }
            mCurrActionFunc = func;
            mActionStatus = ACTION_STARTING;
            (this->*mCurrActionFunc)(arg);
        }
    }

    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8, f32);
    bool chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void anmAtr(u16);
    BOOL CreateInit();
    void setAttention();
    void lookBack();
    void wait01();
    void talk01();
    BOOL dummy_action(void*);
    BOOL wait_action(void*);
    BOOL event_endCheck_action(void*);
    void set_mtx();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void CreateHeap();
    
    static s32 ship_race_rupee;
    static s32 ship_race_result;

public:


    /* 0x6C4 */ u8 field_0x6C4[0x6CC - 0x6C4];
    /* 0x6CC */ mDoExt_McaMorf* mpHeadMorf;
    /* 0x6D0 */ u8 field_0x6D0[0x6D8 - 0x6D0];
    /* 0x6D8 */ fpc_ProcID mHBarrelId;
    /* 0x6DC */ fpc_ProcID mVBarrelId;
    /* 0x6E0 */ J3DAnmTexPattern* m_btp;
    /* 0x6E4 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F8 */ u8 mBlinkFrame;
    /* 0x6F9 */ u8 field_0x6F9[0x6FA - 0x6F9];
    /* 0x6FA */ s16 mBlinkTimer;
    /* 0x6FC */ cXyz mEyePos;
    /* 0x708 */ cXyz mAttPos;
    /* 0x714 */ s16 mLookAtMaxVel;
    /* 0x716 */ u8 field_0x716[0x718 - 0x716];
    /* 0x718 */ csXyz m718;
    /* 0x71E */ u8 field_0x71E[0x724 - 0x71E];
    /* 0x724 */ u32 mMiniGameMessage;
    /* 0x728 */ u8 mHasAttention;
    /* 0x729 */ u8 m729;
    /* 0x72A */ u8 field_0x72A[0x730 - 0x72A];
    /* 0x730 */ s8 m730;
    /* 0x731 */ u8 field_0x731[0x734 - 0x731];
    /* 0x734 */ ProcFunc mCurrActionFunc;
    /* 0x740 */ s8 mTexPatternNum;
    /* 0x741 */ s8 mCurrentAnm;
    /* 0x742 */ s8 mEventState;
    /* 0x743 */ s8 mLookBackState;
    /* 0x744 */ u8 field_0x744[0x746 - 0x744];
    /* 0x746 */ s8 mActionStatus;
    /* 0x747 */ u8 field_0x747[0x748 - 0x747];
};  // Size: 0x748

class daNpc_Sarace_HIO_c : public JORReflexible {
public:

    daNpc_Sarace_HIO_c();
    virtual ~daNpc_Sarace_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05[0x08 - 0x05];
    /* 0x08 */ dNpc_HIO_c mNpc;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
};  // Size: 0x38

#endif /* D_A_NPC_SARACE_H */
