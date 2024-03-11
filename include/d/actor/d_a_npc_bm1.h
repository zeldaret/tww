#ifndef D_A_NPC_BM1_H
#define D_A_NPC_BM1_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Bm1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void IamKakkuto() {}
    void IamSukketo() {}
    void clr_manzai() {}
    void getOdoroki() {}
    void getStt() {}
    void get_oldMsgStat() {}
    void setFocus() {}
    void setTelescopeDemo() {}
    void set_manzai() {}

    void nodeWngControl(J3DNode*, J3DModel*);
    void nodeArmControl(J3DNode*, J3DModel*);
    void nodeBm1Control(J3DNode*, J3DModel*);
    void chk_appCnd();
    void init_PST_0();
    void init_PST_1();
    void init_PST_2();
    void init_PST_3();
    void init_PST_4();
    void init_BMB_0();
    void init_BMB_1();
    void init_BMB_2();
    void init_BMC_0();
    void init_BMC_1();
    void init_BMC_2();
    void init_BMC_3();
    void init_BMD_0();
    void init_BMD_1();
    void init_SKT_0();
    void init_KKT_0();
    void createInit();
    void setMtx(bool);
    void anmNum_toResID(int);
    void headAnmNum_toResID(int);
    void wingAnmNum_toResID(int);
    void btpNum_toResID(int);
    void setBtp(bool, int);
    void iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(signed char);
    void setAnm_anm(anm_prm_c*);
    void setAnm_NUM(int, int);
    void setAnm();
    void setPlaySpd(float);
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(unsigned char);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void eventOrder();
    void checkOrder();
    void chk_manzai();
    void chk_talk();
    void chk_partsNotMove();
    void lookBack();
    void next_msgStatus(unsigned long*);
    void getBitMask();
    void getMsg_PST_1();
    void getMsg_PST_3();
    void getMsg_SKT_0();
    void getMsg_KKT_0();
    void getMsg_BMB_0();
    void getMsg_BMB_1();
    void getMsg_BMB_2();
    void getMsg_BMC_0();
    void getMsg_BMC_2();
    void getMsg_BMC_3();
    void getMsg_BMD_0();
    void getMsg_BMD_1();
    void getMsg();
    void chkAttention();
    void setAttention(bool);
    void searchByID(uint);
    void partner_srch_sub(void* (*)(void*, void*));
    void partner_srch();
    void bm_movPass(bool);
    void bm_setFlyAnm();
    void bm_clcFlySpd();
    void bm_clcMovSpd();
    void bm_flyMove();
    void bm_nMove();
    void setPrtcl_Flyaway();
    void delPrtcl_Flyaway();
    void setPrtcl_Land0();
    void delPrtcl_Land0();
    void setPrtcl_Hane0();
    void flwPrtcl_Hane0();
    void delPrtcl_Hane0();
    void setPrtcl_Hane1();
    void flwPrtcl_Hane1();
    void delPrtcl_Hane1();
    void decideType(int, int);
    void eInit_setLocFlag(int*);
    void eInit_setShapeAngleY(int*, short);
    void eInit_setEvTimer(int*);
    void eInit_calcRelativPos(cXyz*, int*);
    void eInit_ATTENTION_(int*, int*, int*, cXyz*, int*, int*, int*);
    void eInit_SET_PLYER_GOL_(int*, cXyz*, int*);
    void eInit_prmFloat(float*, float);
    void eInit_FLY_(int*, float*, float*, float*, float*);
    void eInit_DEL_ACTOR_();
    void eInit_WLK_(int*, float*, float*, cXyz*, int*, int*, int*);
    void eInit_INI_EVN_1_();
    void eInit_SET_NXT_PTH_INF_();
    void eInit_SET_ANM_(int*);
    void eInit_MOV_PTH_POINT_(int*, int*, int*, int*);
    void event_actionInit(int);
    void eMove_ATTENTION_();
    void eMove_KMA_FLY_();
    void eMove_FLY_();
    void eMove_WLK_();
    void event_action();
    void cut_init_360_TRN(int);
    void cut_move_360_TRN();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Bm1_c::*)(void*), void*);
    void setStt(signed char);
    void d_wait();
    void lookup();
    void orooro();
    void wait_1();
    void talk_1();
    void talk_2();
    void manzai();
    void wait_4();
    void flyawy();
    void wait_5();
    void h_wait();
    void wait_7();
    void wait_3();
    void wait_8();
    void wait_2();
    void walk_1();
    void CHKwai();
    void demo_action1(void*);
    void wait_action1(void*);
    void wait_action2(void*);
    void wait_action3(void*);
    void wait_action4(void*);
    void wait_action5(void*);
    void wait_action6(void*);
    void wait_action7(void*);
    void wait_action8(void*);
    void wait_action9(void*);
    void wait_actionA(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void create_Anm();
    void create_hed_Anm();
    void create_wng_Anm();
    void create_arm_Anm();
    void create_itm_Mdl();
    void CreateHeap();

public:
    /* 0x6C4 */ u8 m6C4[0x6CC - 0x6C4];
    /* 0x6CC */ char mArcName[4];
    /* 0x6D0 */ u8 mHeadJntIdx;
    /* 0x6D1 */ u8 mBackboneJntIdx;
    /* 0x6D2 */ u8 mNeckJntIdx;
    /* 0x6D3 */ u8 mArmLJntIdx;
    /* 0x6D4 */ u8 mArmRJntIdx;
    /* 0x6D5 */ u8 m6D5[0x734 - 0x6D5];
    /* 0x734 */ Mtx mLeftArmMtx;
    /* 0x764 */ Mtx mRightArmMtx;
    /* 0x794 */ u8 m794[0x80C - 0x794];
    /* 0x80C */ cXyz m80C;
    /* 0x818 */ csXyz m818;
    /* 0x81E */ u8 m81E[0x820 - 0x81E];
    /* 0x820 */ cXyz mEyePos;
    /* 0x82C */ u8 m82C[0x86E - 0x82C];
    /* 0x86E */ s16 m86E;
    /* 0x870 */ u8 m870[0x874 - 0x870];
    /* 0x874 */ s16 m874;
    /* 0x876 */ s16 m876;
    /* 0x878 */ u8 m878[0x881 - 0x878];
    /* 0x881 */ u8 m881;
    /* 0x882 */ u8 m882[0x884 - 0x882];
    /* 0x884 */ u8 m884;
    /* 0x885 */ u8 m885[0x887 - 0x885];
    /* 0x887 */ u8 m887;
    /* 0x888 */ u8 m888[0x894 - 0x888];
    /* 0x894 */ u8 m894;
    /* 0x895 */ u8 m895;
    /* 0x896 */ bool m896;
    /* 0x897 */ u8 m897[0x8FD - 0x897];
    /* 0x8FD */ u8 m8FD;
    /* 0x8FE */ u8 m8FE[0x900 - 0x8FE];
    /* 0x900 */ u8 m900;
    /* 0x901 */ u8 mType;
    /* 0x902 */ u8 mSpecificType;
    /* 0x903 */ u8 mSpawnCondition;
    /* 0x904 */ u8 m904[0x908 - 0x904];
};

class daNpc_Bm1_childHIO_c {
public:
    daNpc_Bm1_childHIO_c();

public:
    /* Place member variables here */
};

class daNpc_Bm1_HIO_c {
public:
    daNpc_Bm1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_BM1_H */
