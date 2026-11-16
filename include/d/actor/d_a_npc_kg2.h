#ifndef D_A_NPC_KG2_H
#define D_A_NPC_KG2_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

class daNpc_Kg2_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Kg2_c::*ActionFunc)(void*);

    enum ActionStatus {
        ACTION_STARTING = 0,
        ACTION_ONGOING  = 1,
        ACTION_ENDING   = -1,
    };

    void getAttentionBasePos() {}
    void getEyePos() {}
    void seStart(u32) {}
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
    static void setCanonGameResult(u8 result) { canon_game_result = result; }

    void set_mtx();
    bool initTexPatternAnm(bool);
    void playTexPatternAnm();
    void setAnm(s8, f32);
    void subAnm();
    BOOL chkAttention(cXyz, s16);
    void eventOrder();
    void checkOrder();
    u32 getMsg();
    u16 next_msgStatus(u32*);
    void anmAtr(u16);
    void setAttention();
    void lookBack();
    void CreateHeap();
    int CreateInit();
    void wait01();
    void talk01();
    u32 evn_setAnm_init(int);
    BOOL evn_setAnm();
    u32 evn_jnt_lock_init(int);
    u32 evn_talk_init(int);
    BOOL evn_talk();
    u32 evn_createItem_init(int);
    s32 privateCut();
    u32 processMove();
    int wait_action(void*);
    u32 event_wait_action(void*);
    cPhs_State _create();
    BOOL _delete();
    BOOL _execute();
    BOOL _draw();

    static void init() {
        canon_game_result = 0;
    }

    static u8 canon_game_result;
    static daNpc_Kg2_c* l_kg2_pointer;

public:
    /* 0x6C4 */ u8 field_0x6C4[0x6C8 - 0x6C4];
    /* 0x6C8 */ request_of_phase_process_class mPhase;
    /* 0x6D0 */ u32 mShadowId;
    /* 0x6D4 */ J3DModel* field_0x6D4;
    /* 0x6D8 */ mDoExt_btpAnm field_0x6D8;
    /* 0x6EC */ J3DAnmTexPattern* m_btp;
    /* 0x6F0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x704 */ u8 field_0x704;
    /* 0x705 */ u8 field_0x705[0x706 - 0x705];
    /* 0x706 */ s16 field_0x706;
    /* 0x708 */ cXyz mAttPos;
    /* 0x714 */ u8 field_0x714[0x720 - 0x714];
    /* 0x720 */ s16 field_0x720;
    /* 0x722 */ u8 field_0x722[0x724 - 0x722];
    /* 0x724 */ csXyz mActorAngle;
    /* 0x72A */ u8 field_0x72A[0x72C - 0x72A];
    /* 0x72C */ u8 field_0x72C;
    /* 0x72D */ u8 field_0x72D[0x737 - 0x72D];
    /* 0x737 */ u8 field_0x737;
    /* 0x738 */ u8 field_0x738[0x739 - 0x738];
    /* 0x739 */ s8 field_0x739;
    /* 0x73A */ u8 field_0x73A[0x73C - 0x73A];
    /* 0x73C */ ActionFunc mCurrActionFunc;
    /* 0x748 */ s8 field_0x748;
    /* 0x749 */ s8 field_0x749;
    /* 0x74A */ u8 field_0x74A[0x74C - 0x74A];
    /* 0x74C */ int field_0x74C;
    /* 0x750 */ s8 field_0x750;
    /* 0x751 */ u8 field_0x751[0x754 - 0x751];
    /* 0x754 */ s32 mEventIdx;
    /* 0x758 */ s16 mEventIdTable[4];
    /* 0x760 */ s8 field_0x760;
    /* 0x761 */ u8 field_0x761[0x763 - 0x761];
    /* 0x763 */ s8 mActionStatus;
};  // Size: 0x764


class daNpc_Kg2_HIO_c : public JORReflexible {
public:
    daNpc_Kg2_HIO_c();
    virtual ~daNpc_Kg2_HIO_c() { }

    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x00 */ // vtable for daNpc_Kg2_HIO_C
    /* 0x04 */ s8 mNo;
    /* 0x05 */ // vtable for dNpc_HIO_c
    /* 0x08 */ dNpc_HIO_c mNpc;
    /* 0x30 */ u8 field_0x30[0x34 - 0x30];
};  // Size: 0x34

#endif /* D_A_NPC_KG2_H */
