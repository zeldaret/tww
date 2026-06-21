#ifndef D_A_NPC_JB1_H
#define D_A_NPC_JB1_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_npc.h"

class daNpc_Jb1_c : public fopNpc_npc_c {
public:
    struct anm_prm_c {
        s8 field_0x0;
        s8 field_0x1;
        f32 mMorf;
        f32 mPlaySpeed;
        int mLoopMode;
    };

    typedef BOOL (daNpc_Jb1_c::*ActionFunc)(void*);

    daNpc_Jb1_c();
    bool init_JB1_0();
    bool createInit();
    void setMtx();
    void playBrkAnm(J3DAnmTevRegKey*, s16*);
    int anmNum_toResID(int);
    BOOL setAnm_anm(anm_prm_c*);
    BOOL setAnm();
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(u8);
    void control_anmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    u16 next_msgStatus(u32*);
    u32 getMsg_JB1_0();
    u32 getMsg();
    bool chkAttention();
    void setAttention();
    bool charDecide(int);
    void event_actionInit(int);
    bool event_action();
    void privateCut(int);
    int isEventEntry();
    void event_proc(int);
    BOOL set_action(ActionFunc, void*);
    void setStt(s8);
    BOOL wait_1();
    BOOL wait_action1(void*);
    bool demo();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    bool create_lgt();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_cse_jnt_num;
    /* 0x6CD */ u8 field_0x6CD[0x6D0 - 0x6CD];
    /* 0x6D0 */ cXyz field_0x6D0;
    /* 0x6DC */ dKy_tevstr_c field_0x6DC; // not used
    /* 0x78C */ u8 field_0x78C[0x7A8 - 0x78C];
    /* 0x7A8 */ mDoExt_bckAnm mBckAnm; // not used maybe related to the unused JUT_ASSERTS
    /* 0x7B8 */ u8 field_0x7B8[0x7C0 - 0x7B8];
    /* 0x7C0 */ mDoExt_btkAnm mBtkAnm; // not used maybe related to the unused JUT_ASSERTS
    /* 0x7D4 */ u8 field_0x7D4[0x7DC - 0x7D4];
    /* 0x7DC */ mDoExt_brkAnm mBrkAnm3; // not used maybe related to the unused JUT_ASSERTS
    /* 0x7F4 */ u8 field_0x7F4[0x7F8 - 0x7F4];
    /* 0x7F8 */ LIGHT_INFLUENCE field_0x7F8;
    /* 0x818 */ J3DAnmTevRegKey* m_lmp_brk;
    /* 0x81C */ mDoExt_brkAnm mBrkAnm;
    /* 0x834 */ s16 field_0x834;
    /* 0x836 */ u8 field_0x836[0x838 - 0x836];
    /* 0x838 */ J3DModel* m_lgt_mdl;
    /* 0x83C */ J3DAnmTevRegKey* m_lgt_brk;
    /* 0x840 */ mDoExt_brkAnm mBrkAnm2;
    /* 0x858 */ s16 field_0x858;
    /* 0x85A */ u8 field_0x85A[0x85C - 0x85A];
    /* 0x85C */ ActionFunc mCurrActionFunc;
    /* 0x868 */ u8 field_0x868[0x870 - 0x868];
    /* 0x870 */ dNpc_EventCut_c mEventCut;
    /* 0x8DC */ u8 field_0x8DC[0x8E0 - 0x8DC];
    /* 0x8E0 */ cXyz mCurrentPos;
    /* 0x8EC */ csXyz mCurrentRot;
    /* 0x8F2 */ u8 field_0x8F2[0x8F4 - 0x8F2];
    /* 0x8F4 */ cXyz field_0x8F4;
    /* 0x900 */ f32 mFrame;
    /* 0x904 */ u8 field_0x904[0x908 - 0x904];
    /* 0x908 */ s8 field_0x908;
    /* 0x909 */ bool field_0x909;
    /* 0x90A */ u8 field_0x90A[0x90C - 0x90A];
    /* 0x90C */ bool field_0x90C;
    /* 0x90D */ bool field_0x90D;
    /* 0x90E */ bool field_0x90E;
    /* 0x90F */ bool field_0x90F;
    /* 0x910 */ BOOL field_0x910;
    /* 0x914 */ bool mHasAttention;
    /* 0x915 */ s8 field_0x915;
    /* 0x916 */ u8 field_0x916[0x917 - 0x916];
    /* 0x917 */ bool field_0x917;
    /* 0x918 */ s8 mActIdx;
    /* 0x919 */ s8 mActNo;
    /* 0x91A */ u8 field_0x91A;
    /* 0x91B */ u8 field_0x91B;
    /* 0x91C */ s8 field_0x91C;
    /* 0x91D */ s8 field_0x91D;
    /* 0x91E */ s8 field_0x91E;
    /* 0x91F */ u8 field_0x91F[0x920 - 0x91F];
    /* 0x920 */ s8 field_0x920;
    /* 0x921 */ s8 field_0x921;
    /* 0x922 */ s8 field_0x922;
    /* 0x923 */ s8 field_0x923;
};  // Size: 0x924

#endif /* D_A_NPC_JB1_H */
