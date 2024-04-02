#ifndef D_A_NPC_BTSW2_H
#define D_A_NPC_BTSW2_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

class daNpc_Btsw2_c : public fopNpc_npc_c {
public:
    typedef BOOL (daNpc_Btsw2_c::*ActionFunc)(void*);

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_ENDING   = -1,
    };

    void getAttentionBasePos() {}
    void setAction(ActionFunc func, void* arg) {
        if (mCurrActionFunc != func) {
            if (mCurrActionFunc) {
                mActionStatus = ACTION_ENDING;
                (this->*mCurrActionFunc)(arg);
            }
            mCurrActionFunc = func;
            mActionStatus = ACTION_STARTING;
            (this->*mCurrActionFunc)(arg);
        }
    }

    BOOL initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8);
    bool chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    virtual void anmAtr(u16);
    virtual u32 getMsg();
    virtual u16 next_msgStatus(u32*);
    void setAttention();
    void lookBack();
    BOOL CreateHeap();
    BOOL CreateInit();
    void wait01();
    void talk01();
    void pathMove();
    BOOL wait_action(void*);
    s32 _create();
    BOOL _delete();
    BOOL _execute();
    BOOL _draw();

    static const char m_arc_name[];

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ u32 mShadowId;
    /* 0x6D0 */ J3DModel* mpKabanModel; // Bag
    /* 0x6D4 */ J3DModel* mpTirasiModel; // Flyer
    /* 0x6D8 */ J3DAnmTexPattern* m_btp;
    /* 0x6DC */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F0 */ u8 mBtpFrame;
    /* 0x6F1 */ s8 m_handL_jnt_num;
    /* 0x6F2 */ s8 m_handR_jnt_num;
    /* 0x6F4 */ s16 mBlinkTimer;
    /* 0x6F6 */ u8 m6F6[0x704 - 0x6F6];
    /* 0x704 */ cXyz mAttPos;
    /* 0x710 */ u8 m710[0x714 - 0x710];
    /* 0x714 */ csXyz m714;
    /* 0x71A */ u8 m71A[0x71D - 0x71A];
    /* 0x71D */ bool mHasAttention;
    /* 0x71E */ bool m71E;
    /* 0x71F */ u8 m71F[0x724 - 0x71F];
    /* 0x724 */ u8 m724;
    /* 0x728 */ ActionFunc mCurrActionFunc;
    /* 0x734 */ s8 mPathNo;
    /* 0x735 */ u8 m735;
    /* 0x736 */ u8 m736;
    /* 0x738 */ dPath* mpPath;
    /* 0x73C */ s16 mFinalPathPntIdx;
    /* 0x73E */ s16 m73E;
    /* 0x740 */ s16 mPathPntIdx;
    /* 0x742 */ s16 m742;
    /* 0x744 */ s8 m744;
    /* 0x745 */ s8 m745;
    /* 0x746 */ s8 m746;
    /* 0x747 */ s8 m747;
    /* 0x748 */ u8 m748[0x74A - 0x748];
    /* 0x74A */ s8 mActionStatus;
};

class daNpc_Btsw2_HIO_c {
public:
    daNpc_Btsw2_HIO_c();
    virtual ~daNpc_Btsw2_HIO_c() {}

public:
    /* 0x04 */ s8 mChildID;
    /* 0x08 */ dNpc_HIO_c mNpc;
    /* 0x30 */ s16 m30;
    /* 0x32 */ s16 m32;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ s16 m3C;
    /* 0x3E */ s16 m3E;
};

#endif /* D_A_NPC_BTSW2_H */
