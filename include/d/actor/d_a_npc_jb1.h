#ifndef D_A_NPC_JB1_H
#define D_A_NPC_JB1_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"

class daNpc_Jb1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    typedef BOOL (daNpc_Jb1_c::*ActionFunc)(void*);

    void init_JB1_0();
    void createInit();
    void setMtx();
    void playBrkAnm(J3DAnmTevRegKey*, short*);
    void anmNum_toResID(int);
    void setAnm_anm(anm_prm_c*);
    void setAnm();
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(unsigned char);
    void control_anmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    void eventOrder();
    void checkOrder();
    void next_msgStatus(unsigned long*);
    void getMsg_JB1_0();
    void getMsg();
    void chkAttention();
    void setAttention();
    void charDecide(int);
    void event_actionInit(int);
    void event_action();
    void privateCut(int);
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Jb1_c::*)(void*), void*);
    void setStt(signed char);
    void wait_1();
    void wait_action1(void*);
    void demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void create_Anm();
    void create_lgt();
    void CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mReqPhaseProc;
    /* 0x6CC */ s8 mCaseJointIndex;
    /* 0x6CD */ u8 m6CD[0x818 - 0x6CD];
    /* 0x818 */ J3DAnmTevRegKey* mLampBrkAnim;
    /* 0x81C */ mDoExt_brkAnm mBrkAnimator;
    /* 0x834 */ u8 m834[0x838 - 0x834];
    /* 0x838 */ J3DModelData* mpModelData;
    /* 0x83C */ u8 m83C[0x848 - 0x83C];
    /* 0x848 */ J3DAnmTevRegKey* mCurrentBrkAnim;
    /* 0x84C */ u8 m84C[0x85C - 0x84C];
    /* 0x85C */ ActionFunc mCurStateFunc;
    /* 0x868 */ u8 m868[0x8E0 - 0x868];
    /* 0x8E0 */ cXyz mCurrentPos;
    /* 0x8EC */ csXyz mCurrentRot;
    /* 0x8F2 */ u8 m8F2[0x924 - 0x8F2];
};

class daNpc_Jb1_HIO_c {
public:
    daNpc_Jb1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_JB1_H */
