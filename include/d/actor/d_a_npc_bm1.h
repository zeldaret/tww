#ifndef D_A_NPC_BM1_H
#define D_A_NPC_BM1_H

#include "d/d_npc.h"
#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;

typedef s8 SpecificType;
enum {
    Quill_0,
    Quill_1,
    Quill_2,
    Quill_3,
    Quill_4,
    Akoot,  //0x5
    Skett,  //0x6
    Basht,
    Bisht,
    Hoskit,
    Ilari_0xA,
    Ilari_0xB,
    Ilari_0xC,
    Pashli,
    Namali,
    Kogoli,
    Invalid = 0xFF
};



class daNpc_Bm1_c : public fopNpc_npc_c {
public:
    // struct anm_prm_c {
        
    // }; //Size: 0x14?
    struct anm_prm_c{
        s32 m0;
        s32 m4;
        s32 m8;
        s32 mC;
        s32 m10;
        f32 m14;
        s32 m18;
        s32 m1C;
        f32 m20;
        f32 m24;
        f32 m28;
        f32 m2C;
        f32 m30;
        s32 m34;
        f32 m38;
        f32 m3C;
        f32 m40;
        f32 m44;
        f32 m48;
    };

    typedef BOOL (daNpc_Bm1_c::*ActionFunc)(void*);

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
    bool chk_appCnd();
    BOOL init_PST_0();
    BOOL init_PST_1();
    BOOL init_PST_2();
    bool init_PST_3();
    bool init_PST_4();
    bool init_BMB_0();
    bool init_BMB_1();
    bool init_BMB_2();
    bool init_BMC_0();
    bool init_BMC_1();
    bool init_BMC_2();
    bool init_BMC_3();
    bool init_BMD_0();
    bool init_BMD_1();
    bool init_SKT_0();
    bool init_KKT_0();
    bool createInit();
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
    u16 next_msgStatus(unsigned long*);
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
    u32 getMsg();
    void chkAttention();
    void setAttention(bool);
    void searchByID(fpc_ProcID);
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
    bool decideType(int, int);
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
    BOOL demo_action1(void*);
    BOOL wait_action1(void*);
    BOOL wait_action2(void*);
    BOOL wait_action3(void*);
    BOOL wait_action4(void*);
    BOOL wait_action5(void*);
    BOOL wait_action6(void*);
    BOOL wait_action7(void*);
    BOOL wait_action8(void*);
    BOOL wait_action9(void*);
    BOOL wait_actionA(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    void create_hed_Anm();
    void create_wng_Anm();
    void create_arm_Anm();
    void create_itm_Mdl();
    void CreateHeap();

public:
    /* 0x6C4 */ request_of_phase_process_class mPhs;
    /* 0x6CC */ char mArcName[4];
    /* 0x6D0 */ s8 m_hed_jnt_num;
    /* 0x6D1 */ s8 m_bbone_jnt_num;
    /* 0x6D2 */ s8 m_nec_jnt_num;
    /* 0x6D3 */ s8 m_arm_L_jnt_num;
    /* 0x6D4 */ s8 m_arm_R_jnt_num;
    /* 0x6D5 */ u8 field_0x6D5[0x6EC - 0x6D5];
    /* 0x6EC */ mDoExt_McaMorf* field_0x6EC;
    /* 0x6F0 */ u8 field_0x6F0[0x6F4 - 0x6F0];
    /* 0x6F4 */ mDoExt_btpAnm field_0x6F4;
    /* 0x708 */ u8 field_0x708[0x710 - 0x708];
    /* 0x710 */ mDoExt_McaMorf* field_0x710;
    /* 0x714 */ u8 field_0x714[0x71C - 0x714];
    /* 0x71C */ mDoExt_McaMorf* field_0x71C;
    /* 0x720 */ u8 field_0x720[0x734 - 0x720];
    /* 0x734 */ Mtx mLeftArmMtx;
    /* 0x764 */ Mtx mRightArmMtx;
                u32 m794;
    /* 0x794 */ u8 m798[0x80C - 0x798];
    /* 0x80C */ cXyz m80C;
    /* 0x818 */ csXyz m818;
    /* 0x81E */ u8 m81E[0x820 - 0x81E];
    /* 0x820 */ cXyz mEyePos;
    /* 0x82C */ u8 m82C[0x838 - 0x82C];
    /* 0x838 */ Vec m838;
    /* 0x844 */ u8 m844[0x86E - 0x844];
    /* 0x86E */ s16 m86E;
    /* 0x870 */ u8 m870[0x874 - 0x870];
    /* 0x874 */ s16 m874;
    /* 0x876 */ s16 m876;
    /* 0x878 */ u8 m878[0x87F - 0x878];
    /* 0x87F */ bool m87F;
    /* 0x880 */ u8 m880[0x881 - 0x880];
    /* 0x881 */ u8 m881;
    /* 0x882 */ u8 m882[0x884 - 0x882];
    /* 0x884 */ u8 m884;
    /* 0x885 */ u8 m885[0x887 - 0x885];
    /* 0x887 */ u8 m887;
    /* 0x888 */ u8 m888[0x890 - 0x888];
    /* 0x890 */ s32 m890;
    /* 0x894 */ u8 m894;
    /* 0x895 */ u8 m895;
    /* 0x896 */ bool m896;
    /* 0x897 */ u8 m897[0x898 - 0x897];
    /* 0x898 */ cXyz m898;
    /* 0x8A4 */ cXyz m8A4;
    /* 0x8B0 */ cXyz m8B0;
    /* 0x8BC */ cXyz m8BC;
    /* 0x8C8 */ u8 m8C8;
    /* 0x8C9 */ u8 m8C9[0x8CC - 0x8C9];
    /* 0x8CC */ u8 m8CC;
    /* 0x8CD */ u8 m8CD[0x8D4 - 0x8CD];
    /* 0x8D4 */ void* m8D4;
    /* 0x8D8 */ void* m8D8;
    /* 0x8DC */ void* m8DC;
    /* 0x8E0 */ void* m8E0;
    /* 0x8E4 */ void* m8E4;
    /* 0x8E8 */ void* m8E8;
    /* 0x8EC */ void* m8EC;
    /* 0x8F0 */ void* m8F0;
    /* 0x8F4 */ u8 m8F4;
    /* 0x8F5 */ u8 m8F5;
    /* 0x8F6 */ u8 m8F6[0x8F7 - 0x8F6];
    /* 0x8F7 */ u8 m8F7;
    /* 0x8F8 */ u8 m8F8;
    /* 0x8F9 */ u8 m8F9;
    /* 0x8FA */ u8 m8FA;
    /* 0x8FB */ u8 m8FB[0x8FD - 0x8FB];
    /* 0x8FD */ u8 m8FD;
    /* 0x8FE */ u8 m8FE;
    /* 0x8FF */ u8 m8FF;
    /* 0x900 */ u8 m900;
    /* 0x901 */ s8 mType;
    /* 0x902 */ SpecificType mSpecificType;
    /* 0x903 */ s8 mSpawnCondition;
    /* 0x904 */ u8 m904;
    /* 0x904 */ u8 m905;   



//     /* 0x880 */ u8 field_0x880[0x881 - 0x880];
//     /* 0x881 */ u8 field_0x881;
//     /* 0x882 */ u8 field_0x882[0x884 - 0x882];
//     /* 0x884 */ u8 field_0x884;
//     /* 0x885 */ u8 field_0x885[0x887 - 0x885];
//     /* 0x887 */ u8 field_0x887;
//     /* 0x888 */ u8 field_0x888[0x890 - 0x888];
//     /* 0x890 */ s32 field_0x890;
//     /* 0x894 */ u8 field_0x894;
//     /* 0x895 */ u8 field_0x895;
//     /* 0x896 */ bool field_0x896;
//     /* 0x897 */ u8 field_0x897[0x898 - 0x897];
//     /* 0x898 */ cXyz m898;
//     /* 0x8A4 */ cXyz m8A4;
//     /* 0x8B0 */ cXyz m8B0;
//     /* 0x8BC */ cXyz m8BC;
//     /* 0x8C8 */ u8 m8C8;
//     /* 0x8C9 */ u8 field_0x8C9[0x8CC - 0x8C9];
//     /* 0x8CC */ u8 m8CC;
//     /* 0x8CD */ u8 field_0x8CD[0x8D4 - 0x8CD];
//     /* 0x8D4 */ void* field_0x8D4;
//     /* 0x8D8 */ void* field_0x8D8;
//     /* 0x8DC */ void* field_0x8DC;
//     /* 0x8E0 */ void* field_0x8E0;
//     /* 0x8E4 */ void* field_0x8E4;
//     /* 0x8E8 */ void* field_0x8E8;
//     /* 0x8EC */ void* field_0x8EC;
//     /* 0x8F0 */ void* field_0x8F0;
//     /* 0x8F4 */ u8 m8F4;
//     /* 0x8F5 */ u8 m8F5;
//     /* 0x8F6 */ u8 field_0x8F6[0x8F7 - 0x8F6];
//     /* 0x8F7 */ u8 m8F7;
//     /* 0x8F8 */ u8 m8F8;
//     /* 0x8F9 */ u8 m8F9;
//     /* 0x8FA */ u8 m8FA;
//     /* 0x8FB */ u8 field_0x8FB[0x8FD - 0x8FB];
//     /* 0x8FD */ u8 m8FD;
//     /* 0x8FE */ u8 m8FE;
//     /* 0x8FF */ u8 m8FF;
//     /* 0x900 */ u8 m900;
//     /* 0x901 */ daNpc_Bm1_c__Type mType;
//     /* 0x902 */ daNpc_Bm1_c__SpecificType mSpecificType;
//     /* 0x903 */ u8 mSpawnCondition;
//     /* 0x904 */ u8 m904;
//     /* 0x905 */ u8 m905;
//     /* 0x906 */ u8 field_0x906[0x908 - 0x906];
// };  // Size: 0x908
}; 
STATIC_ASSERT(sizeof(daNpc_Bm1_c) == 0x908);

class daNpc_Bm1_childHIO_c : public mDoHIO_entry_c{
public:
    daNpc_Bm1_childHIO_c();

public:

    daNpc_Bm1_c::anm_prm_c anm_prm;
    u32 m50;
    /* Place member variables here */
    //SIZE: 0x54
};

class daNpc_Bm1_HIO_c :public mDoHIO_entry_c{
public:
    daNpc_Bm1_HIO_c();

public:

    s8 m4;
    s32 m8;
    daNpc_Bm1_childHIO_c children[10];
    s32 m350;
    /* Place member variables here */
};
    //SIZE: 0x354
#endif /* D_A_NPC_BM1_H */
