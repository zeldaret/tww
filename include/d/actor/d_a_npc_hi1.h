#ifndef D_A_NPC_HI1_H
#define D_A_NPC_HI1_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"

class J3DNode;

class daNpc_Hi1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Hi1_c::*ActionFunc)(void*);

    struct anm_prm_c {
        s8 field_0x0;
        s8 field_0x1;
        f32 field_0x4;
        f32 field_0x8;
        int field_0xC;
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_HI1_0();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    int btkResID(int);
    bool setBtp(s8, bool);
    bool setBtk(s8, bool);
    bool init_texPttrnAnm(s8, bool);
    void play_btp_anm();
    void play_btk_anm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(u8);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    u16 next_msgStatus(u32*);
    u32 getMsg_HI1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_parts_notMov();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    bool set_action(ActionFunc, void*);
    void setStt(signed char);
    BOOL wait_1();
    BOOL talk_1();
    int wait_action1(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ char mArcName[3];
    /* 0x6D1 */ u8 field_0x6D1[0x6D4 - 0x6D1];
    /* 0x6D4 */ u32 mShadowId;
    /* 0x6D8 */ mDoExt_btkAnm mBtkAnm;
    /* 0x6EC */ u8 mBtkAnmFrame;
    /* 0x6ED */ u8 field_0x6ED[0x6F0 - 0x6ED];
    /* 0x6F0 */ mDoExt_btpAnm mBtpAnm;
    /* 0x704 */ u8 mBtpAnmFrame;
    /* 0x705 */ u8 field_0x705[0x706 - 0x705];
    /* 0x706 */ s16 mTimer1;
    /* 0x708 */ ActionFunc mCurrActionFunc;
    /* 0x714 */ u8 field_0x714[0x718 - 0x714];
    /* 0x718 */ u32 mPId;
    /* 0x71C */ u8 field_0x71C[0x724 - 0x71C];
    /* 0x724 */ cXyz field_0x724;
    /* 0x730 */ csXyz field_0x730;
    /* 0x736 */ csXyz field_0x736;
    /* 0x73C */ u8 field_0x73C[0x744 - 0x73C];
    /* 0x744 */ cXyz field_0x744;
    /* 0x750 */ cXyz field_0x750;
    /* 0x75C */ u8 field_0x75C[0x768 - 0x75C];
    /* 0x768 */ cXyz field_0x768;
    /* 0x774 */ u8 field_0x774[0x780 - 0x774];
    /* 0x780 */ f32 field_0x780;
    /* 0x784 */ u8 field_0x784[0x788 - 0x784];
    /* 0x788 */ csXyz field_0x788;
    /* 0x78E */ u8 field_0x78E[0x790 - 0x78E];
    /* 0x790 */ int field_0x790;
    /* 0x794 */ s16 mEventIdx[6];
    /* 0x7A0 */ s16 mTimer2;
    /* 0x7A2 */ u8 field_0x7A2[0x7AA - 0x7A2];
    /* 0x7AA */ s16 field_0x7AA;
    /* 0x7AC */ s8 field_0x7AC;
    /* 0x7AD */ u8 field_0x7AD;
    /* 0x7AE */ u8 mItemNo;
    /* 0x7AF */ u8 field_0x7AF[0x7B0 - 0x7AF];
    /* 0x7B0 */ bool field_0x7B0;
    /* 0x7B1 */ bool field_0x7B1;
    /* 0x7B2 */ bool field_0x7B2;
    /* 0x7B3 */ bool field_0x7B3;
    /* 0x7B4 */ bool field_0x7B4;
    /* 0x7B5 */ bool field_0x7B5;
    /* 0x7B6 */ bool field_0x7B6;
    /* 0x7B7 */ bool field_0x7B7;
    /* 0x7B8 */ bool field_0x7B8;
    /* 0x7B9 */ bool field_0x7B9;
    /* 0x7BA */ u8 field_0x7BA;
    /* 0x7BB */ s8 mActIdx;
    /* 0x7BC */ u8 field_0x7BC;
    /* 0x7BD */ u8 field_0x7BD;
    /* 0x7BE */ s8 field_0x7BE;
    /* 0x7BF */ u8 field_0x7BF;
    /* 0x7C0 */ s8 field_0x7C0;
    /* 0x7C1 */ s8 field_0x7C1;
    /* 0x7C2 */ s8 field_0x7C2;
    /* 0x7C3 */ s8 field_0x7C3;
    /* 0x7C4 */ s8 field_0x7C4;
    /* 0x7C5 */ s8 field_0x7C5;
    /* 0x7C6 */ s8 field_0x7C6;
    /* 0x7C7 */ s8 field_0x7C7;
    /* 0x7C8 */ s8 field_0x7C8;
    /* 0x7C9 */ u8 field_0x7C9[0x7CC - 0x7C9];
};  // Size: 0x7CC
#endif /* D_A_NPC_HI1_H */
