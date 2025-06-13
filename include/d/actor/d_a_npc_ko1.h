#ifndef D_A_NPC_KO1_H
#define D_A_NPC_KO1_H

#include "d/d_npc.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_msg.h"
#include "m_Do/m_Do_hostIO.h"

class J3DNode;

class ko_hna_class : public fopAc_ac_c{};
class ko_bou_class : public fopAc_ac_c{};
class ko_ob_class : public fopAc_ac_c{};

class daNpc_Ko1_c : public fopNpc_npc_c {

public:
    typedef int (daNpc_Ko1_c::*ActionFunc)(void*);
    struct anm_prm_c {
        s8 field0;
        s8 field1;
        f32 field4;
        f32 field8;
        s32 fieldC;
        s32 field10;
    };

    void nodeHedControl(J3DNode*, J3DModel*);
    void nodeBlnControl(J3DNode*, J3DModel*);
    void nodeKo1Control(J3DNode*, J3DModel*);
    bool init_HNA_0();
    bool init_HNA_1();
    bool init_HNA_2();
    bool init_HNA_3();
    bool init_HNA_4();
    bool init_BOU_0();
    bool init_BOU_1();
    bool init_BOU_2();
    bool init_BOU_3();
    bool createInit();
    void setMtx(bool);
    s32 anmNum_toResID(int);
    s32 headAnmNum_toResID(int);
    s32 balloon_anmNum_toResID(int);
    s32 btpNum_toResID(int);
    bool setBtp(bool, int);
    bool iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(signed char);
    s32 setAnm_anm(anm_prm_c*);
    s32 set_balloonAnm_anm(anm_prm_c*);
    void set_balloonAnm_NUM(int);
    void setAnm_NUM(int, int);
    bool setAnm();
    void setPlaySpd(float);
    void chg_anmTag();
    void control_anmTag();
    void chg_anmAtr(unsigned char);
    void control_anmAtr();
    void setAnm_ATR(int);
    void anmAtr(unsigned short);
    void eventOrder();
    void checkOrder();
    bool chk_talk();
    bool chk_manzai_1();
    bool chk_partsNotMove();
    void lookBack();
    u16 next_msgStatus(unsigned long*);
    s32 getMsg_HNA_0();
    s32 getMsg_HNA_1();
    s32 getMsg_HNA_2();
    s32 getMsg_HNA_3();
    s32 getMsg_BOU_0();
    s32 getMsg_BOU_1();
    s8 bitCount(unsigned char);
    s32 getMsg_BOU_2();
    u32 getMsg();
    bool chkAttention();
    void setAttention(bool);
    fopAc_ac_c* searchByID(fpc_ProcID);
    fpc_ProcID  partner_srch_sub(void* (*)(void*, void*));
    void partner_srch();
    bool check_landOn();
    void ko_setPthPos();
    cXyz set_tgtPos(cXyz);
    u32 ko_movPass();
    void ko_clcMovSpd();
    void ko_clcSwmSpd();
    void ko_nMove();
    void chk_routeAngle(cXyz&, short*);
    void routeWallCheck(cXyz&, cXyz&, short*);
    f32 chk_ForwardGroundY(short);
    f32 chk_wallJump(short);
    s32 routeCheck(float, short*);
    bool chk_start_swim();
    fpc_ProcID get_crsActorID();
    bool chk_areaIn(float, cXyz);
    void setPrtcl_Hamon(float, float);
    void setPrtcl_HanaPachi();
    bool charDecide(int);
    void event_actionInit(int);
    bool event_action();
    void privateCut(int);
    void endEvent();
    int isEventEntry();
    void event_proc(int);
    s32 set_action(ActionFunc, void*);
    void clrSpd();
    void setStt(signed char);
    BOOL wait_1();
    BOOL wait_2();
    BOOL wait_3();
    BOOL wait_4();
    BOOL wait_5(signed char);
    BOOL wait_6();
    BOOL wait_7();
    BOOL wait_9();
    BOOL wait_a();
    BOOL walk_1();
    BOOL walk_2(signed char, signed char);
    BOOL walk_3();
    BOOL swim_1();
    BOOL swim_2();
    BOOL attk_1();
    BOOL attk_2(signed char, signed char);
    BOOL attk_3();
    BOOL down_1(signed char);
    BOOL talk_1();
    BOOL talk_2();
    BOOL manzai();
    BOOL neru_1();
    BOOL neru_2();
    int hana_action1(void*);
    int hana_action2(void*);
    int hana_action3(void*);
    int hana_action4(void*);
    int hana_action5(void*);
    int wait_action1(void*);
    int wait_action2(void*);
    int wait_action3(void*);
    int wait_action4(void*);
    u8 demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    J3DModelData* create_Anm();
    J3DModelData* create_hed_Anm();
    J3DModelData* create_bln_Anm();
    bool create_itm_Mdl();
    BOOL CreateHeap();

public:
    /*0x6C4*/   request_of_phase_process_class field_0x6C4;
    /*0x6CC*/   s8 m_hed_jnt_num;
    /*0x6CD*/   s8 m_bbone_jnt_num;
    /*0x6CE*/   s8 m_armR2_jnt_num;       
    /*0x6CF*/   s8 m_hed_2_jnt_num;
    /*0x6D0*/   s8 m_bln_loc_jnt_num;
    /*0x6D1*/   s8 m_bln_jnt_num;
    /*0x6D4*/   Mtx field_0x6D4;
    /*0x704*/   mDoExt_McaMorf* mBlnAnm;  
    /*0x708*/   J3DModel* field_0x708;
    /*0x70C*/   u32 mShadowID;
    /*0x710*/   mDoExt_McaMorf* field_0x710;
    /*0x714*/   J3DAnmTexPattern* m_hed_tex_pttrn;
    /*0x718*/   mDoExt_btpAnm mBtpAnm;
    /*0x72C*/   u8 mBtpFrame;
    /*0x72E*/   s16 field_0x72E;
    /*0x730*/   ActionFunc field_0x730;
    /*0x73C*/   dNpc_PathRun_c mPathRun;
    /*0x744*/   void* field_0x744;
    /*0x748*/   dNpc_EventCut_c mEventCut;
    /*0x7B4*/   fpc_ProcID field_0x7B4[2];
    /*0x7BC*/   u8 field_0x7BC;
    /*0x7C0*/   fpc_ProcID field_0x7C0;
    /*0x7C4*/   cXyz field_0x7C4;
    /*0x7D0*/   csXyz field_0x7D0;
    /*0x7D6*/   csXyz field_0x7D6;
    /*0x7DC*/   cXyz field_0x7DC;
    /*0x7E8*/   cXyz field_0x7E8;
    /*0x7F4*/   cXyz field_0x7F4;
    /*0x800*/   u8 pad800[0x805-0x800];
    /*0x805*/   u8 field_0x805;
    /*0x806*/   u8 pad806[0x80C-0x806];
    /*0x80C*/   cXyz field_0x80C;
    /*0x818*/   cXyz field_0x818;
    /*0x824*/   f32 field_0x824;
    /*0x828*/   f32 field_0x828;
    /*0x82C*/   f32 field_0x82C;
    /*0x830*/   f32 field_0x830;
    /*0x834*/   f32 field_0x834;
    /*0x838*/   f32 field_0x838;
    /*0x83C*/   f32 field_0x83C;
    /*0x840*/   s16 field_0x840;
    /*0x842*/   s16 field_0x842;
    /*0x844*/   s16 field_0x844;
    /*0x846*/   s16 field_0x846;
    /*0x848*/   u32 field_0x848;
    /*0x84C*/   u16 field_0x84C;
    /*0x84E*/   s16 field_0x84E;
    /*0x850*/   s16 field_0x850;
    /*0x852*/   s16 field_0x852;
    /*0x854*/   s16 field_0x854;
    /*0x856*/   s16 field_0x856;
    /*0x858*/   s16 field_0x858;
    /*0x85A*/   s16 field_0x85A;
    /*0x85C*/   s16 field_0x85C;
    /*0x85E*/   s8 field_0x85E;
    /*0x85F*/   s8 field_0x85F;
    /*0x860*/   s8 field_0x860;
    /*0x861*/   s8 field_0x861;
    /*0x862*/   s8 field_0x862;
    /*0x863*/   u8 field_0x863;
    /*0x864*/   u8 field_0x864;
    /*0x865*/   u8 field_0x865;
    /*0x866*/   u8 field_0x866;
    /*0x867*/   u8 field_0x867;
    /*0x868*/   u8 field_0x868; 
    /*0x869*/   u8 field_0x869;   
    /*0x86A*/   u8 field_0x86A;   
    /*0x86B*/   u8 field_0x86B;      
    /*0x86C*/   u8 field_0x86C;
    /*0x86D*/   u8 field_0x86D;
    /*0x86E*/   u8 field_0x86E;
    /*0x870*/   s32 field_0x870;
    /*0x874*/   bool field_0x874;
    /*0x875*/   u8 field_0x875; 
    /*0x876*/   bool field_0x876; 
    /*0x877*/   u8 field_0x877;
    /*0x878*/   dPa_rippleEcallBack field_0x878;
    /*0x88C*/   JPABaseEmitter* field_0x88C;
    /*0x890*/   JPABaseEmitter* field_0x890;
    /*0x894*/   JPABaseEmitter* field_0x894;
    /*0x88C*/   s8 field_0x898;
    /*0x899*/   u8 field_0x899;
    /*0x89A*/   s8 field_0x89A;
    /*0x89B*/   u8 field_0x89B;
    /*0x89C*/   u8 field_0x89C;
    /*0x89D*/   u8 field_0x89D;
    /*0x89E*/   s8 field_0x89E;
    /*0x89F*/   s8 field_0x89F;
    /*0x8A0*/   u8 field_0x8A0;
    /*0x8A1*/   s8 field_0x8A1;
    /*0x8A2*/   s8 field_0x8A2;
    /*0x8A3*/   s8 field_0x8A3;
    /*0x8A4*/   s8 field_0x8A4;
    /*0x8A5*/   s8 field_0x8A5;  
    /*0x8A6*/   s8 field_0x8A6;
    /*0x8A7*/   s8 field_0x8A7;
    /*0x8A8*/   s8 field_0x8A8;
    /*0x8A9*/   s8 field_0x8A9;
    /*0x8AA*/   s8 field_0x8AA;
    /*0x8AB*/   s8 field_0x8AB;
};
struct hio_prm_child_c{
    s16 mMaxHeadX;
    s16 mMaxHeadY;
    s16 mMinHeadX;
    s16 mMinHeadY;
    s16 mMaxBackboneX;
    s16 mMaxBackboneY;
    s16 mMinBackboneX;
    s16 mMinBackboneY;
    s16 mMaxTurnStep;
    s16 field16;
    f32 field18;
    u8 field1C;
    u16 field1E;
    s16 field20;
    s16 field22;
    f32 field24;
    f32 field28;
    f32 field2C;
    f32 field30;
    f32 field34;
    f32 field38;
    f32 field3C;
    f32 field40;
    f32 field44;
    f32 field48;
    f32 field4C;
    f32 field50;
    f32 field54;
    f32 field58;
};
class daNpc_Ko1_childHIO_c: public mDoHIO_entry_c {
public:
    daNpc_Ko1_childHIO_c();

public:

    hio_prm_child_c hio_prm;
    u32 field5C;
    /* Place member variables here */
};

class daNpc_Ko1_HIO_c: public mDoHIO_entry_c {


public:
    daNpc_Ko1_HIO_c();

public:
    s8 mNo;
    u32 field8;
    daNpc_Ko1_childHIO_c children[2];

    /* Place member variables here */
};

#endif /* D_A_NPC_KO1_H */
