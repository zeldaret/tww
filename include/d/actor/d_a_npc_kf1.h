#ifndef D_A_NPC_KF1_H
#define D_A_NPC_KF1_H

#include "f_op/f_op_actor.h"
#include "d/d_npc.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Kf1_c : public fopNpc_npc_c {

typedef BOOL (daNpc_Kf1_c::*ActionFunc)(int);
public:
    struct anm_prm_c {
        s8 m0;
        s8 m1;
        f32 m4;
        f32 m8;
        u32 mC;
    };

    void _nodeCB_Head(J3DNode*, J3DModel*);
    void _nodeCB_Neck(J3DNode*, J3DModel*);
    void _nodeCB_BackBone(J3DNode*, J3DModel*);
    bool init_KF1_0();
    bool createInit();
    void play_animation();
    void setMtx(bool);
    s32 bckResID(int);
    s32 btpResID(int);
    BOOL setBtp(signed char, bool);
    bool init_texPttrnAnm(signed char, bool);
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
    s32 getMsg_KF1_0();
    u32 getMsg();
    void eventOrder();
    void checkOrder();
    BOOL chk_talk();
    fopAc_ac_c* searchByID(fpc_ProcID, int*);
    void srch_Tsubo();
    void create_rupee(cXyz, int);
    void ready_kutaniCamera(int, int);
    void lookBack();
    void chkAttention();
    void setAttention(bool);
    bool decideType(int);
    void cut_init_ANGRY_START(int);
    void cut_move_ANGRY_START();
    void cut_init_BENSYOU_START(int);
    void cut_move_BENSYOU_START();
    void cut_init_TSUBO_CNT(int);
    void cut_move_TSUBO_CNT();
    void cut_init_BENSYOU(int);
    void cut_move_BENSYOU();
    void cut_init_GET_OUT(int);
    void cut_move_GET_OUT();
    void cut_init_DSP_RUPEE_CNT(int);
    void cut_move_DSP_RUPEE_CNT();
    void cut_init_PLYER_TRN(int);
    void cut_move_PLYER_TRN();
    void cut_init_RUPEE_CNT_END(int);
    void cut_move_RUPEE_CNT_END();
    void cut_init_START_AGE(int);
    void cut_move_START_AGE();
    void cut_init_PLYER_MOV(int);
    void cut_move_PLYER_MOV();
    void cut_init_RUPEE_SET(int);
    void cut_move_RUPEE_SET();
    void cut_init_TSUBO_ATN(int);
    void cut_move_TSUBO_ATN();
    void cut_init_TLK_MSG(int);
    void cut_init_CONTNUE_TLK(int);
    void cut_move_TLK_MSG();
    void privateCut(int);
    void endEvent();
    s32 isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Kf1_c::*)(void*), void*);
    void setStt(signed char);
    void set_pthPoint(unsigned char);
    void chk_tsubo();
    void orderTsuboEvent();
    void wait_1();
    void walk_1();
    void talk_1();
    int wait_action1(void*);
    bool demo();
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
    /* 0x6D0 */ J3DModel* m6D0;
    /* 0x6D4 */ char mArcName[4];
    /* 0x6D8 */ u32 mShadowId;
    /* 0x6DC */ mDoExt_btpAnm m6DC;
    /* 0x6F0 */ u8 m6F0;
    /* 0x6F1 */ u8 field_0x6F1[0x6F2 - 0x6F1];
    /* 0x6F2 */ s16 m6F2;
    /* 0x6F4 */ ActionFunc mCurrentAction;
    /* 0x700 */ s32 m700;
    /* 0x704 */ u8 m704;
    /* 0x705 */ u8 field_0x705[0x708 - 0x705];
    /* 0x708 */ dNpc_PathRun_c mPathRun;
    /* 0x710 */ cXyz m710;
    /* 0x71C */ csXyz m71C;
    /* 0x722 */ csXyz m722;
    /* 0x728 */ u8 field_0x728[0x730 - 0x728];
    /* 0x730 */ cXyz m730;
    /* 0x73C */ cXyz m73C;
    /* 0x748 */ u8 field_0x748[0x754 - 0x748];
    /* 0x754 */ cXyz m754;
    /* 0x760 */ u8 field_0x760[0x76C - 0x760];
    /* 0x76C */ f32 m76C;
    /* 0x770 */ u8 field_0x770[0x774 - 0x770];
    /* 0x774 */ u8 m774;
    /* 0x775 */ u8 field_0x775[0x776 - 0x775];
    /* 0x776 */ u8 m776;
    /* 0x777 */ u8 field_0x777[0x778 - 0x777];
    /* 0x778 */ u8 m778;
    /* 0x779 */ u8 field_0x779[0x77C - 0x779];
    /* 0x77C */ s32 m77C;
    /* 0x780 */ s16 m780[2];
    /* 0x784 */ u8 field_0x784[0x786 - 0x784];
    /* 0x786 */ s16 m786;
    /* 0x788 */ u8 field_0x788[0x78C - 0x788];
    /* 0x78C */ s16 m78C;
    /* 0x78E */ s16 m78E;
    /* 0x790 */ s16 m790;
    /* 0x792 */ s16 m792;
    /* 0x794 */ u8 m794;
    /* 0x795 */ u8 field_0x795[0x79A - 0x795];
    /* 0x79A */ u8 m79A;
    /* 0x79B */ u8 field_0x79B[0x79C - 0x79B];
    /* 0x79C */ s8 m79C;
    /* 0x79D */ u8 m79D;
    /* 0x79E */ u8 m79E;
    /* 0x79F */ s8 m79F;
    /* 0x7A0 */ u8 m7A0;
    /* 0x7A1 */ u8 m7A1;
    /* 0x7A2 */ u8 field_0x7A2[0x7A3 - 0x7A2];
    /* 0x7A3 */ bool m7A3;
    /* 0x7A4 */ bool m7A4;
    /* 0x7A5 */ bool m7A5;
    /* 0x7A6 */ bool m7A6;
    /* 0x7A7 */ u8 m7A7;
    /* 0x7A8 */ u8 m7A8;
    /* 0x7A9 */ u8 m7A9;
    /* 0x7AA */ bool m7AA;
    /* 0x7AB */ bool mbAttention;
    /* 0x7AC */ u8 m7AC;
    /* 0x7AD */ u8 m7AD;
    /* 0x7AE */ bool m7AE;
    /* 0x7AF */ u8 field_0x7AF[0x7B0 - 0x7AF];
    /* 0x7B0 */ u8 m7B0;
    /* 0x7B1 */ u8 field_0x7B1[0x7BC - 0x7B1];
    /* 0x7BC */ u8 m7BC;
    /* 0x7BD */ u8 field_0x7BD[0x7DC - 0x7BD];
    /* 0x7DC */ u8 m7DC;
    /* 0x7DD */ u8 field_0x7DD[0x7E8 - 0x7DD];
    /* 0x7E8 */ u32 m7E8;
    /* 0x7EC */ s16 m7EC;
    /* 0x7EE */ s16 m7EE;
    /* 0x7F0 */ u16 m7F0;
    // /* 0x7F1 */ u8 field_0x7F1[0x7F2 - 0x7F1];
    /* 0x7F2 */ u8 m7F2;
    /* 0x7F3 */ u8 m7F3;
    /* 0x7F4 */ u8 m7F4;
    /* 0x7F5 */ s8 m7F5;
    /* 0x7F6 */ s8 m7F6;
    /* 0x7F7 */ s8 m7F7;
    /* 0x7F8 */ s8 m7F8;
    /* 0x7F9 */ u8 m7F9;
    /* 0x7FA */ u8 m7FA;
    /* 0x7FB */ s8 m7FB;
    /* 0x7FC */ u8 m7FC;
    /* 0x7FD */ s8 m7FD;
    /* 0x7FE */ s8 m7FE;
    /* 0x7FF */ u8 field_0x7FF[0x800 - 0x7FF];
};  // Size: 0x800


class daNpc_Kf1_HIO_c : public mDoHIO_entry_c{
    struct hio_prm_c{
        s16 m0;
        s16 m2;
        s16 m4;
        s16 m6;
        s16 m8;
        s16 mA;
        s16 mC;
        s16 mE;
        s16 m10;
        s16 m12;
        s16 m14;
        s16 m16;
        s16 m18;
        s16 m1A;
        s16 m1C;
        s16 m1E;
        f32 m20;
        f32 m24;
        f32 m28;
        f32 m2C;
    }; //Size: 0x30
public:
    daNpc_Kf1_HIO_c();

public:
    s8 m0;
    s32 m4;
    hio_prm_c m8[3];
    /* Place member variables here */
};

#endif /* D_A_NPC_KF1_H */
