#ifndef D_A_NPC_DE1_H
#define D_A_NPC_DE1_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "d/d_particle.h"
#include "d/d_bg_w_deform.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_De1_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_De1_c::*ActionFunc)(void*);

    enum {
        ANM_WAIT01,
        ANM_SLEEP,
        ANM_WAKE,
        ANM_SUFFER,
        ANM_TALK01,
        ANM_TALK02,
        ANM_TALK03,
        ANM_END,
    };

    struct anm_prm_c {
        /* 0x00 */ s8 mAnmIdx;
        /* 0x04 */ f32 mMorf;
        /* 0x08 */ f32 mPlaySpeed;
        /* 0x0C */ int mLoopMode;
    };

    bool createInit();
    void setMtx();
    BOOL anmResID(int, int*, int*);
    BOOL setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    void setStt(s8);
    u16 next_msgStatus(u32*);
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chkAttention();
    void setAttention();
    fopAc_ac_c* searchByID(fpc_ProcID);
    void setDemoStartCenter();
    BOOL partner_srch();
    void ccCreate();
    void cc_set();
    void set_pa_happa();
    void del_pa_happa();
    void followPa_happa();
    BOOL decideType(int);

    void event_actionInit(int);
    BOOL event_action();
    void privateCut();
    void endEvent();
    void event_proc();
    BOOL set_action(ActionFunc, void*);
    BOOL wait01();
    BOOL wait02();
    BOOL wait03();
    BOOL wait04();
    BOOL wait05();
    BOOL talk01();
    BOOL talk02();
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    u8 demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_head_jnt_num;
    /* 0x6CD */ s8 m_branchL_jnt_num;
    /* 0x6D0 */ dBgWDeform* mpBgWSv;
    /* 0x6D4 */ ActionFunc mActionFunc;
    /* 0x6E0 */ dNpc_EventCut_c mEventCut;
    /* 0x74C */ csXyz mOrigAngle;
    /* 0x754 */ cXyz mOrigPos;
    /* 0x760 */ cXyz mAttentionBasePos;
    /* 0x76C */ cXyz mAttentionPos;
    /* 0x778 */ cXyz mHomePos;
    /* 0x784 */ cXyz mDemoCenterPos;
    /* 0x790 */ f32 mPrevMorfFrame;
    /* 0x794 */ u8 field_0x794[4];
    /* 0x798 */ s16 mSoundTimer;
    /* 0x79A */ s16 mTimer;
    /* 0x79C */ u8 field_0x79C[2];
    /* 0x79E */ s16 mDemoTimer;
    /* 0x7A0 */ u8 field_0x7A0[4];
    /* 0x7A4 */ s8 mPlayMorfResult;
    /* 0x7A5 */ u8 field_0x7A5;
    /* 0x7A6 */ u8 field_0x7A6;
    /* 0x7A7 */ u8 field_0x7A7;
    /* 0x7A8 */ u8 mExecMode;
    /* 0x7AC */ s32 mMorfFrame;
    /* 0x7B0 */ u8 field_0x7B0[4];
    /* 0x7B4 */ u8 mNearPlayer;
    /* 0x7B5 */ u8 mPartnerNearPlayer;
    /* 0x7B6 */ u8 field_0x7B6;
    /* 0x7B7 */ u8 mNoPlayMorf;
    /* 0x7B8 */ u8 mIsFirstTalk;
#if VERSION == VERSION_DEMO
    /* 0x7BC */ JPABaseEmitter* mpPaHappa;
    /* 0x7C0 */ dPa_followEcallBack mPaHappa;
    /* 0x7D4 */ cXyz mPaHappaPos;
    /* 0x7E0 */ fpc_ProcID m_cc_ID[10];
    /* 0x808 */ s8 m_c0_jnt_num[10];
    /* 0x814 */ fpc_ProcID mPartnerID;
    /* 0x818 */ s8 mCutType;
    /* 0x819 */ s8 mActNo;
    /* 0x81A */ u8 mAnmAtr;
    /* 0x81B */ u8 mAnmTag;
    /* 0x81C */ s8 mCurAnmIdx;
    /* 0x81D */ s8 mDemoMode;
    /* 0x81E */ s8 mStatus;
    /* 0x81F */ s8 mTalk02State;
    /* 0x820 */ s8 mHeapType;
    /* 0x821 */ s8 mType;
    /* 0x822 */ s8 mActionState;
    /* 0x823 */ s8 mMsgTypingState;
#else
    /* 0x7BC */ dPa_followEcallBack mPaHappa;
    /* 0x7D0 */ cXyz mPaHappaPos;
    /* 0x7DC */ fpc_ProcID m_cc_ID[10];
    /* 0x804 */ s8 m_c0_jnt_num[10];
    /* 0x810 */ fpc_ProcID mPartnerID;
    /* 0x814 */ s8 mCutType;
    /* 0x815 */ s8 mActNo;
    /* 0x816 */ u8 mAnmAtr;
    /* 0x817 */ u8 mAnmTag;
    /* 0x818 */ s8 mCurAnmIdx;
    /* 0x819 */ s8 mDemoMode;
    /* 0x81A */ s8 mStatus;
    /* 0x81B */ s8 mTalk02State;
    /* 0x81C */ s8 mHeapType;
    /* 0x81D */ s8 mType;
    /* 0x81E */ s8 mActionState;
    /* 0x81F */ s8 mMsgTypingState;
#endif
};  // Size: 0x820 (Demo: 0x824)

class daNpc_De1_HIO_c {
public:
    struct hio_prm_c {
        /* 0x00 */ f32 m00;
        /* 0x04 */ f32 m04;
        /* 0x08 */ f32 m08;
        /* 0x0C */ f32 m0C;
        /* 0x10 */ f32 m10;
        /* 0x14 */ f32 m14;
        /* 0x18 */ f32 m18;
        /* 0x1C */ f32 m1C;
    };  // Size: 0x20

    daNpc_De1_HIO_c();
    virtual ~daNpc_De1_HIO_c() {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ s32 mNum;
    /* 0x0C */ hio_prm_c mPrm;
};  // Size: 0x2C

#endif /* D_A_NPC_DE1_H */
