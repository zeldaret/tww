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
    s8 createInit();
    void setMtx(bool);
    s32 anmNum_toResID(int);
    s32 headAnmNum_toResID(int);
    s32 balloon_anmNum_toResID(int);
    s32 btpNum_toResID(int);
    bool setBtp(bool, int);
    void iniTexPttrnAnm(bool);
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
    void isEventEntry();
    void event_proc(int);
    s32 set_action(ActionFunc, void*);
    void clrSpd();
    void setStt(signed char);
    bool wait_1();
    bool wait_2();
    bool wait_3();
    bool wait_4();
    bool wait_5(signed char);
    bool wait_6();
    bool wait_7();
    bool wait_9();
    bool wait_a();
    bool walk_1();
    bool walk_2(signed char, signed char);
    bool walk_3();
    void swim_1();
    void swim_2();
    void attk_1();
    void attk_2(signed char, signed char);
    void attk_3();
    void down_1(signed char);
    void talk_1();
    void talk_2();
    void manzai();
    void neru_1();
    void neru_2();
    int hana_action1(void*);
    int hana_action2(void*);
    int hana_action3(void*);
    int hana_action4(void*);
    int hana_action5(void*);
    int wait_action1(void*);
    int wait_action2(void*);
    int wait_action3(void*);
    int wait_action4(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    cPhs_State _create();
    void create_Anm();
    void create_hed_Anm();
    void create_bln_Anm();
    void create_itm_Mdl();
    void CreateHeap();

public:
    u8 pad6C4[0x8];
    s8 field_0x6CC;
    s8 field_0x6CD;
    s8 field_0x6CE;       
    s8 field_0x6CF;
    s8 field_0x6D0;
    s8 field_0x6D1;
    Mtx field_0x6D4;
    mDoExt_McaMorf* field_0x704;  
    J3DModel* field_0x708;
    u32 pad70C;
    mDoExt_McaMorf* field_0x710;
    /*0x714*/ J3DAnmTexPattern* m_hed_tex_pttrn;
    mDoExt_btpAnm field_0x718;
    u8 field_0x72C;
    s16 field_0x72E;
    ActionFunc field_0x730;
    /*0x73C*/ dNpc_PathRun_c mPathRun;
    /*0x744*/ void* field_0x744;
    /*0x748*/ dNpc_EventCut_c mEventCut;
    fpc_ProcID field_0x7B4[2];
    u8 field_0x7BC;
    s32 field_0x7C0;
    cXyz field_0x7C4;
    csXyz field_0x7D0;
    csXyz field_0x7D6;
    cXyz field_0x7DC;
    cXyz field_0x7E8;
    cXyz field_0x7F4;
    u8 pad800[0x805-0x800];
    u8 field_0x805;
    u8 pad806[0x80C-0x806];
    cXyz field_0x80C;
    cXyz field_0x818;
    f32 field_0x824;
    f32 field_0x828;
    f32 field_0x82C;
    f32 field_0x830;
    f32 field_0x834;
    f32 field_0x838;
    f32 field_0x83C;
    s16 field_0x840;
    s16 field_0x842;
    s16 field_0x844;
    s16 field_0x846;
    u32 field_0x848;
    u16 field_0x84C;
    s16 field_0x84E;
    s16 field_0x850;
    s16 field_0x852;
    s16 field_0x854;
    s16 field_0x856;
    s16 field_0x858;
    s16 field_0x85A;
    s16 field_0x85C;
    s8 field_0x85E;
    s8 field_0x85F;
    s8 field_0x860;
    s8 field_0x861;
    s8 field_0x862;
    u8 field_0x863;
    u8 field_0x864;
    u8 field_0x865;
    u8 pad866[0x869 - 0x866]; 
    u8 field_0x869;   
    u8 field_0x86A;   
    u8 field_0x86B;      
    u8 field_0x86C;
    u8 field_0x86D;
    s32 field_0x870;
    u8 field_0x874;
    u8 field_0x875; 
    bool field_0x876; 
    u8 field_0x877;
    dPa_rippleEcallBack field_0x878;
    JPABaseEmitter* field_0x88C;
    JPABaseEmitter* field_0x890;
    JPABaseEmitter* field_0x894;
    s8 field_0x898;
    u8 field_0x899;
    s8 field_0x89A;
    u8 field_0x89B;
    u8 field_0x89C;
    u8 field_0x89D;
    s8 field_0x89E;
    s8 field_0x89F;
    u8 pad8A0;
    s8 field_0x8A1;
    s8 field_0x8A2;
    s8 field_0x8A3;
    s8 field_0x8A4;
    s8 field_0x8A5;  
    s8 field_0x8A6;
    s8 field_0x8A7;
    s8 field_0x8A8;
    s8 field_0x8A9;
    s8 field_0x8AA;
    s8 field_0x8AB;
};

class daNpc_Ko1_childHIO_c: public mDoHIO_entry_c {
public:
    daNpc_Ko1_childHIO_c();

public:
    char pad04[0x16-0x04];
    s16  field16;
    f32 field18;
    f32 field1C;
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
    u32 field5C;
    /* Place member variables here */
};

class daNpc_Ko1_HIO_c: public mDoHIO_entry_c {
    struct hio_prm_child_c{
        u8 pad[0x58];
    };
public:
    daNpc_Ko1_HIO_c();

public:
    s8 mNo;
    u32 field8;
    daNpc_Ko1_childHIO_c children[2];
    struct hio_prm_c {
        hio_prm_child_c childtable[2];
	// .4byte 0x20001F40
	// .4byte 0xE0C0E0C0
	// .4byte 0x00001F40
	// .4byte 0x0000E0C0
	// .4byte 0x07D00640
	// .4byte 0x42B40000
	// .4byte 0x00000004
	// .4byte 0x08000000
	// .4byte 0x3F666666
	// .4byte 0x3F800000
	// .4byte 0x3F000000
	// .4byte 0x41A80000
	// .4byte 0x3DCCCCCD
	// .4byte 0x41200000
	// .4byte 0x3E99999A
	// .4byte 0x42200000
	// .4byte 0x42A00000
	// .4byte 0x43480000
	// .4byte 0x43960000
	// .4byte 0x43160000
	// .4byte 0x44898000
	// .4byte 0x44BB8000
	// .4byte 0x20001F40
	// .4byte 0xE0C0E0C0
	// .4byte 0x00001F40
	// .4byte 0x0000E0C0
	// .4byte 0x07D00640
	// .4byte 0x42B40000
	// .4byte 0x00000006
	// .4byte 0x08000000
	// .4byte 0x3E99999A
	// .4byte 0x40C00000
	// .4byte 0x3ECCCCCD
	// .4byte 0x41A80000
	// .4byte 0x3DCCCCCD
	// .4byte 0x41400000
	// .4byte 0x3FC00000
	// .4byte 0x42C80000
	// .4byte 0x00000000
	// .4byte 0x43AF0000
	// .4byte 0x43FA0000
	// .4byte 0x43160000
	// .4byte 0x00000000
	// .4byte 0x00000000
    };
    /* Place member variables here */
};

#endif /* D_A_NPC_KO1_H */
