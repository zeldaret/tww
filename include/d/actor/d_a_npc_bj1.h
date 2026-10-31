#ifndef D_A_NPC_BJ1_H
#define D_A_NPC_BJ1_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "d/d_npc.h"
#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Bj1_c : public fopNpc_npc_c {
public:
    struct anm_prm_c {
        /* 0x00 */ s8 anmNum;
        /* 0x01 */ s8 btpNum;
        /* 0x04 */ f32 morf;
        /* 0x08 */ f32 speed;
        /* 0x0C */ int loopMode;
        /* 0x10 */ BOOL hasArms;
    };

    typedef BOOL (daNpc_Bj1_c::*ActionFunc)(void*);

    void nodeBj1Control(J3DNode*, J3DModel*);
    void nodePrpControl(J3DNode*, J3DModel*);
    void init_BJ4_0();
    void init_BJ6_0();
    void init_BJ7_0();
    void init_BJX_0();
    void init_BJX_1();
    void createInit();
    void setMtx_anmProc();
    void setMtx(bool);
    void anmNum_toResID(int);
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int);
    void setAnm();
    void setAnm_prp(s8);
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(u8);
    void control_anmAtr();
    void setAnm_ATR();
    void anmAtr(u16);
    void eventOrder();
    void checkOrder();
    void chk_talk();
    void chk_drct(f32);
    void chk_partsNotMove();
    void lookBack();
    void getMaskInf(u8*);
    void chkReg(u16);
    void setReg(u16);
    u16 next_msgStatus(u32*);
    void getMsg_BJ1_0();
    void getMsg_BJ2_0();
    void getMsg_BJ3_0();
    void getMsg_BJ4_0();
    void getMsg_BJ5_0();
    void getMsg_BJ6_0();
    void getMsg_BJ7_0();
    void getMsg_BJ8_0();
    void getMsg_BJ9_0();
    void getMsg_Corog();
    u32 getMsg();
    void chkAttention();
    void setAttention(bool);
    fopAc_ac_c* searchByID(fpc_ProcID);
    bool partner_srch_sub(fpcLyIt_JudgeFunc);
    void partner_srch();
    void setCollision_SP_();
    void set_pthPoint(u8);
    void bj_clcFlySpd();
    void bj_movPass(bool);
    void bj_flyMove();
    void bj_clcMovSpd();
    void bj_nMove();
    void setPrtcl_drugPot_1();
    void setPrtcl_drugPot_2();
    void delPrtcl_drugPot();
    void setPrtcl_danceLR();
    void flwPrtcl_danceLR();
    void delPrtcl_danceLR();
    void setPrtcl_peraProOpen();
    void createSeed();
    void deleteSeed();
    void charDecide(int);
    void eInit_setLocFlag(int*);
    void eInit_setShapeAngleY(int*, s16);
    void eInit_setEvTimer(int*);
    void eInit_calcRelativPos(cXyz*, int*);
    void eInit_prmFloat(f32*, f32);
    void eInit_ATTENTION_(int*, int*, int*, cXyz*, int*, int*, int*);
    void eInit_PLYER_MOV_1_();
    void eInit_MOV_(f32*, f32*, f32*, int*);
    void eInit_JMP_(f32*, f32*);
    void eInit_CHG_PTH_(int*, int*);
    void eInit_END_MOV_();
    void eInit_SET_TNE_();
    void eInit_DEL_TNE_();
    void eInit_SET_ANM_(int*, f32*);
    void event_actionInit(int);
    void eMove_ATTENTION_();
    void eMove_MOV_();
    void eMove_JMP_();
    void eMove_SET_TNE_();
    void eMove_PTH_MOV_();
    void event_action();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(ActionFunc, void*);
    void setStt(s8);
    void wait_1();
    void wait_2();
    void wait_3();
    void wait_4();
    void flyMov();
    void fall01();
    void talk_1();
    void walk_1();
    void wait_action1(void*);
    void wait_action2(void*);
    void wait_action3(void*);
    void wait_action4(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void create_Anm();
    void create_prp_Anm();
    bool create_itm_Mdl();
    BOOL CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class field_0x6C4;
    /* 0x6CC */ s8 field_0x6CC;
    /* 0x6CD */ s8 field_0x6CD;
    /* 0x6CE */ u8 field_0x6CE;
    /* 0x6CF */ s8 field_0x6CF;
    /* 0x6D0 */ int* field_0x6D0;
    /* 0x6D4 */ J3DModel* field_0x6D4;
    /* 0x6D8 */ J3DModel* field_0x6D8;
    /* 0x6DC */ s8 field_0x6DC;
    /* 0x6DD */ s8 field_0x6DD;
    /* 0x6DE */ u8 padding_0x6DE[0x6E0 - 0x6DE];
    /* 0x6E0 */ int field_0x6E0;
    /* 0x6E4 */ mDoExt_McaMorf* field_0x6E4;
    /* 0x6E8 */ s8 field_0x6E8;
    /* 0x6E9 */ s8 field_0x6E9;
    /* 0x6EA */ u8 padding_0x6EA[0x6F0 - 0x6EA];
    /* 0x6F0 */ s16 field_0x6F0;
    /* 0x6F2 */ s16 field_0x6F2;
    /* 0x6F4 */ u8 padding_0x6F4[0x6F8 - 0x6F4];
    /* 0x6F8 */ ActionFunc field_0x6F8;
    /* 0x704 */ Mtx field_0x704;
    /* 0x734 */ dNpc_PathRun_c field_0x734;
    /* 0x73C */ dNpc_EventCut_c field_0x73C;
    /* 0x7A8 */ u32 field_0x7A8;
    /* 0x7AC */ cXyz field_0x7AC;
    /* 0x7B8 */ s16 field_0x7B8;
    /* 0x7BA */ s16 field_0x7BA;
    /* 0x7BC */ s16 field_0x7BC;
    /* 0x7BE */ u8 padding_0x7BE[0x7C0 - 0x7BE];
    /* 0x7C0 */ cXyz field_0x7C0;
    /* 0x7CC */ cXyz field_0x7CC;
    /* 0x7D8 */ cXyz field_0x7D8;
    /* 0x7E4 */ cXyz field_0x7E4;
    /* 0x7F0 */ f32 field_0x7F0;
    /* 0x7F4 */ f32 field_0x7F4;
    /* 0x7F8 */ f32 field_0x7F8;
    /* 0x7FC */ f32 field_0x7FC;
    /* 0x800 */ f32 field_0x800;
    /* 0x804 */ f32 field_0x804;
    /* 0x808 */ f32 field_0x808;
    /* 0x80C */ f32 field_0x80C;
    /* 0x810 */ u8 padding_0x810[0x814 - 0x810];
    /* 0x814 */ f32 field_0x814;
    /* 0x818 */ u8 padding_0x818[0x81C - 0x818];
    /* 0x81C */ f32 field_0x81C;
    /* 0x820 */ s16 field_0x820;
    /* 0x822 */ s16 field_0x822;
    /* 0x824 */ s16 field_0x824;
    /* 0x826 */ u16 field_0x826;
    /* 0x828 */ u8 padding_0x828[0x82C - 0x828];
    /* 0x82C */ s16 field_0x82C;
    /* 0x82E */ u16 field_0x82E;
    /* 0x830 */ u16 field_0x830;
    /* 0x832 */ u16 field_0x832;
    /* 0x834 */ u16 field_0x834;
    /* 0x836 */ u8 padding_0x836[0x838 - 0x836];
    /* 0x838 */ s16 field_0x838;
    /* 0x83A */ s16 field_0x83A;
    /* 0x83C */ u8 field_0x83C;
    /* 0x83D */ u8 field_0x83D;
    /* 0x83E */ u8 field_0x83E;
    /* 0x83F */ u8 field_0x83F;
    /* 0x840 */ u8 field_0x840;
    /* 0x841 */ u8 field_0x841;
    /* 0x842 */ u8 field_0x842;
    /* 0x843 */ u8 field_0x843;
    /* 0x844 */ u8 field_0x844;
    /* 0x845 */ u8 field_0x845;
    /* 0x846 */ u8 field_0x846;
    /* 0x847 */ u8 field_0x847;
    /* 0x848 */ u8 field_0x848;
    /* 0x849 */ u8 field_0x849;
    /* 0x84A */ u8 field_0x84A;
    /* 0x84B */ u8 field_0x84B;
    /* 0x84C */ u8 field_0x84C;
    /* 0x84D */ u8 field_0x84D;
    /* 0x84E */ u8 field_0x84E;
    /* 0x84F */ u8 padding_0x84F[0x850 - 0x84F];
    /* 0x850 */ int field_0x850;
    /* 0x854 */ u8 field_0x854;
    /* 0x855 */ u8 field_0x855;
    /* 0x856 */ u8 field_0x856;
    /* 0x857 */ u8 field_0x857;
    /* 0x858 */ csXyz field_0x858;
    /* 0x85E */ u8 padding_0x85E[0x860 - 0x85E];
    /* 0x860 */ cXyz field_0x860;
    /* 0x86C */ cXyz field_0x86C;
    /* 0x878 */ JPABaseEmitter* field_0x878;
    /* 0x87C */ JPABaseEmitter* field_0x87C;
    /* 0x880 */ JPABaseEmitter* field_0x880;
    /* 0x884 */ JPABaseEmitter* field_0x884;
    /* 0x888 */ int field_0x888;
    /* 0x88C */ JPABaseEmitter* field_0x88C;
    /* 0x890 */ JPABaseEmitter* field_0x890;
    /* 0x894 */ u16 field_0x894;
    /* 0x896 */ u8 padding_0x896[0x898 - 0x896];
    /* 0x898 */ int field_0x898;
    /* 0x89C */ u8 padding_0x89C[0x8A8 - 0x89C];
    /* 0x8A8 */ u8 field_0x8A8;
    /* 0x8A9 */ s8 field_0x8A9;
    /* 0x8AA */ u8 field_0x8AA;
    /* 0x8AB */ u8 field_0x8AB;
    /* 0x8AC */ u8 field_0x8AC;
    /* 0x8AD */ u8 field_0x8AD;
    /* 0x8AE */ u8 field_0x8AE;
    /* 0x8AF */ u8 field_0x8AF;
    /* 0x8B0 */ u8 field_0x8B0;
    /* 0x8B1 */ u8 field_0x8B1;
    /* 0x8B2 */ u8 field_0x8B2;
    /* 0x8B3 */ u8 field_0x8B3;
    /* 0x8B4 */ s8 field_0x8B4;
    /* 0x8B5 */ u8 field_0x8B5;
    /* 0x8B6 */ u8 field_0x8B6;
    /* 0x8B7 */ u8 field_0x8B7;
}; // size 0x8B8;

class daNpc_Bj1_childHIO_c {
public:
    struct hio_prm_c {
        /* 0x00 */ u8 field_0x00[0x64];
    }; // Size: 0x64

    daNpc_Bj1_childHIO_c();

public:
    /* Place member variables here */
};

class daNpc_Bj1_HIO_c {
public:
    daNpc_Bj1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_BJ1_H */
