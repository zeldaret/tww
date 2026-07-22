#ifndef D_A_NPC_ZK1_H
#define D_A_NPC_ZK1_H

#include "d/d_lib.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Zk1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Zk1_c::*ActionFunc)(void*);



    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_ZK1_0();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    int bckResID(int);
    int btpResID(int);
    bool setBtp(s8, bool);
    bool init_texPttrnAnm(s8, bool);
    void play_btp_anm();
    void setAnm_anm(dLib_anm_prm_c*);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    u16 next_msgStatus(unsigned long*);
    u32 getMsg_ZK1_0();
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
    /* 0x6D1 */ u8 m6D1[0x6D4 - 0x6D1];
    /* 0x6D4 */ u32 mShadowId;
    /* 0x6D8 */ mDoExt_btpAnm mBtpAnm;
    /* 0x6EC */ u8 mBtpFrame;
    /* 0x6ED */ u8 field_0x6ED;
    /* 0x6EE */ s16 mTimer1;
    /* 0x6F0 */ ActionFunc mCurrActionFunc;
    /* 0x6FD */ fpc_ProcID mProcId1;
    /* 0x700 */ fpc_ProcID mProcId2;
    /* 0x704 */ u8 m704[0x70C - 0x704];
    /* 0x70C */ cXyz field_0x70C;
    /* 0x718 */ csXyz field_0x718;
    /* 0x71E */ csXyz mAngle;
    /* 0x724 */ u8 m724[0x72C - 0x724];
    /* 0x72C */ cXyz mTransformedEyePos;
    /* 0x738 */ cXyz mPlayerEyePos;
    /* 0x744 */ u8 m738[0x750 - 0x744];
    /* 0x750 */ cXyz field_0x750;
    /* 0x75C */ u8 m75C[0x768 - 0x75C];
    /* 0x768 */ f32 mFrame;
    /* 0x76C */ u8 m76C[0x770 - 0x76C];
    /* 0x770 */ s16 mActorAngleY;
    /* 0x772 */ s16 mJointHeadY;
    /* 0x774 */ s16 mJointBackboneY;
    /* 0x776 */ s16 field_0x776;
    /* 0x778 */ BOOL mbSetEyePos;
    /* 0x77C */ s16 mEventIdx[6];
    /* 0x788 */ s16 mTimer2;
    /* 0x78A */ u8 m78A[0x792 - 0x78A];
    /* 0x792 */ s16 field_0x792;
    /* 0x794 */ u8 mAnmEnded;
    /* 0x795 */ u8 field_0x795;
    /* 0x796 */ u8 mItemNo;
    /* 0x797 */ bool field_0x797;
    /* 0x798 */ bool field_0x798;
    /* 0x799 */ u8 field_0x799;
    /* 0x79A */ u8 field_0x79A;
    /* 0x79B */ bool mbResLoadIsComplete;
    /* 0x79C */ u8 field_0x79C;
    /* 0x79D */ u8 field_0x79D;
    /* 0x79E */ u8 field_0x79E;
    /* 0x79F */ bool field_0x79F;
    /* 0x7A0 */ bool mHasAttention;
    /* 0x7A1 */ bool field_0x7A1;
    /* 0x7A2 */ bool field_0x7A2;
    /* 0x7A3 */ u8 field_0x7A3;
    /* 0x7A4 */ u8 field_0x7A4;
    /* 0x7A5 */ s8 mActIdx;
    /* 0x7A6 */ u8 field_0x7A6;
    /* 0x7A7 */ u8 field_0x7A7;
    /* 0x7A8 */ s8 mBtpResIDIndex;
    /* 0x7A9 */ s8 mCurrAnmIdx;
    /* 0x7AA */ s8 field_0x7AA;
    /* 0x7AB */ s8 field_0x7AB;
    /* 0x7AC */ s8 field_0x7AC;
    /* 0x7AD */ s8 field_0x7AD;
    /* 0x7AE */ s8 field_0x7AE;
    /* 0x7AF */ s8 field_0x7AF;
    /* 0x7B0 */ s8 field_0x7B0;
    /* 0x7B1 */ s8 field_0x7B1;
    /* 0x7B2 */ u8 field_0x7B2;
    /* 0x7B3 */ u8 field_0x7B3;
};

#endif /* D_A_NPC_ZK1_H */
