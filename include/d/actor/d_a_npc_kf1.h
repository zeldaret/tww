#ifndef D_A_NPC_KF1_H
#define D_A_NPC_KF1_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "f_pc/f_pc_base.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Kf1_c : public fopNpc_npc_c {
public:
    typedef int (daNpc_Kf1_c::*JudgeFunc)(void*);
    struct anm_prm_c {
        /* 0x00 */ s8 anmId;
        /* 0x01 */ s8 flag;
        /* 0x04 */ float morf;
        /* 0x08 */ float animSpeed;
        /* 0x0C */ s32 loopMode;
        
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_Neck(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    BOOL init_KF1_0();
    BOOL createInit();
    void play_animation();
    void setMtx(bool);
    s32 bckResID(int);
    s32 btpResID(int);
    bool setBtp(signed char, bool);
    BOOL init_texPttrnAnm(signed char, bool);
    void play_btp_anm();
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void chngAnmTag();
    void ctrlAnmTag();
    void chngAnmAtr(unsigned char);
    void ctrlAnmAtr();
    void setAnm_ATR();
    void anmAtr(unsigned short);
    u16 next_msgStatus(unsigned long*);
    u32 getMsg_KF1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    BOOL chk_talk();
    fopAc_ac_c *searchByID(fpc_ProcID, int*);
    BOOL srch_Tsubo();
    void create_rupee(cXyz, int);
    void ready_kutaniCamera(int, int);
    void lookBack();
    bool chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void cut_init_ANGRY_START(int);
    bool cut_move_ANGRY_START();
    void cut_init_BENSYOU_START(int);
    bool cut_move_BENSYOU_START();
    void cut_init_TSUBO_CNT(int);
    bool cut_move_TSUBO_CNT();
    void cut_init_BENSYOU(int);
    bool cut_move_BENSYOU();
    void cut_init_GET_OUT(int);
    bool cut_move_GET_OUT();
    void cut_init_DSP_RUPEE_CNT(int);
    bool cut_move_DSP_RUPEE_CNT();
    void cut_init_PLYER_TRN(int);
    bool cut_move_PLYER_TRN();
    void cut_init_RUPEE_CNT_END(int);
    BOOL cut_move_RUPEE_CNT_END();
    void cut_init_START_AGE(int);
    void cut_move_START_AGE();
    void cut_init_PLYER_MOV(int);
    bool cut_move_PLYER_MOV();
    void cut_init_RUPEE_SET(int);
    void cut_move_RUPEE_SET();
    void cut_init_TSUBO_ATN(int);
    void cut_move_TSUBO_ATN();
    void cut_init_TLK_MSG(int);
    void cut_init_CONTNUE_TLK(int);
    void cut_move_TLK_MSG();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Kf1_c::*)(void*), void*);
    void setStt(signed char);
    void set_pthPoint(unsigned char);
    s16 chk_tsubo();
    void orderTsuboEvent();
    void wait_1();
    void walk_1();
    void talk_1();
    BOOL wait_action1(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    BOOL bodyCreateHeap();
    BOOL itemCreateHeap();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ s8 m_hed_jnt_num;
    /* 0x6CD */ s8 m_bbone_jnt_num;
    /* 0x6CE */ s8 m_nck_jnt_num;
    /* 0x6D0 */ J3DModel* mModel;
    /* 0x6D4 */ char field_0x6d4[4];
    s32 pad;
    /* 0x6DC */ mDoExt_btpAnm mBtpAnm;
    /* 0x6F0 */ u8 field_0x6F0;
    /* 0x6F2 */ s16 field_0x6F2;
    /* 0x6F3 */ u8 m6D5[12];
    u32 field_0x700;
    /* 0x704 */ fpc_ProcID field_0x704;
    /* 0x708 */ dNpc_PathRun_c pathRun;
    /* 0x710 */ u8 m710[0x722 - 0x710];
    /* 0x722 */ csXyz mAngle;
    u8 m728[0x730 - 0x728];
    /* 0x730 */ cXyz head_anm_vec;
    /* 0x73C */ cXyz field_0x73C;
    u8 m73C[0x754 - 0x748];
    /* 0x754 */ cXyz mMtx;
    u8 m760[0x76C - 0x760];
    /* 0x76C */ f32 mAnimTimer;
    u8 m770[0x774 - 0x770];
    s16 field_0x774;
    s16 field_0x776;
    s16 field_0x778;
    u8 m77A[0x77C - 0x77A];
    s32 field_0x77C;
    /* 0x780 */ s16 field_0x780[4];
    u8 m788[0x78C - 0x788];
    s16 field_0x78C;
    u8 m78E[0x794 - 0x78E];
    /* 0x794 */ s16 field_0x794;
    u8 m796[0x79a - 0x796];
    s16 field_0x79A;
    s8 field_0x79C;
    u8 field_0x79D;
    u8 field_0x79E;
    /* 0x79F */ u8 field_0x79F;
    /* 0x7A0 */ u8 field_0x7A0;
    /* 0x7A0 */ u8 field_0x7A1;
    u8 m7a2[0x7a6 - 0x7a4];
    /* 0x7A6 */ bool field_0x7A6;
    u8 m7a7[0x7ac - 0x7a7];
    /* 0x7AC */ u8 field_0x7AC;
    /* 0x7AD */ bool field_0x7AD;
    u8 m7ae[0x7bc - 0x7ae];
    fpc_ProcID field_0x7BC[12];

    /* 0x7EC */ s16 field_0x7EC;
    // tenth of rupee cost
    /* 0x7EE */ s16 field_0x7EE;
    /* 0x7FF */ u16 field_0x7F0;
    /* 0x7F2 */ u8 field_0x7F2;
    /* 0x7F3 */ u8 field_0x7F3;
    /* 0x7F4 */ u8 field_0x7F4;
    /* 0x7F5 */ s8 field_0x7F5;
    /* 0x7F6 */ s8 mAnmId;
    /* 0x7F7 */ s8 field_0x7F7;
    /* 0x7F8 */ s8 field_0x7F8;
    /* 0x7F9 */ u8 field_0x7F9;
    // some kind of state variable?
    /* 0x7FA */ s8 field_0x7FA;
    /* 0x7FB */ s8 field_0x7FB;
    /* 0x7FC */ s8 field_0x7FC;
    /* 0x7FD */ u8 field_0x7FD;
    /* 0x7FE */ s8 field_0x7FE;
};

class daNpc_Kf1_HIO_c : public mDoHIO_entry_c{
public:
    daNpc_Kf1_HIO_c();
    virtual ~daNpc_Kf1_HIO_c() {}

public:
    /* 0x00 */ s8 a;
    /* 0x04 */ s32 b;
    /* 0x0C */ f32 yoffset;
    /* 0x10 */ u32 _1;
    /* 0x14 */ u32 _2;
    /* 0x18 */ u32 _3;
    /* 0x1C */ u16 _4;
    /* 0x1E */ s16 field_0x1e;
    u8 data[0x30];
    /* Place member variables here */
};

#endif /* D_A_NPC_KF1_H */
