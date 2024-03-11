#ifndef D_A_NPC_KO1_H
#define D_A_NPC_KO1_H

#include "f_op/f_op_actor.h"

class J3DNode;

class daNpc_Ko1_c : public fopAc_ac_c {
public:
    struct anm_prm_c {
        
    };

    void nodeHedControl(J3DNode*, J3DModel*);
    void nodeBlnControl(J3DNode*, J3DModel*);
    void nodeKo1Control(J3DNode*, J3DModel*);
    void init_HNA_0();
    void init_HNA_1();
    void init_HNA_2();
    void init_HNA_3();
    void init_HNA_4();
    void init_BOU_0();
    void init_BOU_1();
    void init_BOU_2();
    void init_BOU_3();
    void createInit();
    void setMtx(bool);
    void anmNum_toResID(int);
    void headAnmNum_toResID(int);
    void balloon_anmNum_toResID(int);
    void btpNum_toResID(int);
    void setBtp(bool, int);
    void iniTexPttrnAnm(bool);
    void plyTexPttrnAnm();
    void setAnm_tex(signed char);
    void setAnm_anm(anm_prm_c*);
    void set_balloonAnm_anm(anm_prm_c*);
    void set_balloonAnm_NUM(int);
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
    void chk_talk();
    void chk_manzai_1();
    void chk_partsNotMove();
    void lookBack();
    void next_msgStatus(unsigned long*);
    void getMsg_HNA_0();
    void getMsg_HNA_1();
    void getMsg_HNA_2();
    void getMsg_HNA_3();
    void getMsg_BOU_0();
    void getMsg_BOU_1();
    void bitCount(unsigned char);
    void getMsg_BOU_2();
    void getMsg();
    void chkAttention();
    void setAttention(bool);
    void searchByID(uint);
    void partner_srch_sub(void* (*)(void*, void*));
    void partner_srch();
    void check_landOn();
    void ko_setPthPos();
    void set_tgtPos(cXyz);
    void ko_movPass();
    void ko_clcMovSpd();
    void ko_clcSwmSpd();
    void ko_nMove();
    void chk_routeAngle(cXyz&, short*);
    void routeWallCheck(cXyz&, cXyz&, short*);
    void chk_ForwardGroundY(short);
    void chk_wallJump(short);
    void routeCheck(float, short*);
    void chk_start_swim();
    void get_crsActorID();
    void chk_areaIn(float, cXyz);
    void setPrtcl_Hamon(float, float);
    void setPrtcl_HanaPachi();
    void charDecide(int);
    void event_actionInit(int);
    void event_action();
    void privateCut(int);
    void endEvent();
    void isEventEntry();
    void event_proc(int);
    void set_action(int (daNpc_Ko1_c::*)(void*), void*);
    void clrSpd();
    void setStt(signed char);
    void wait_1();
    void wait_2();
    void wait_3();
    void wait_4();
    void wait_5(signed char);
    void wait_6();
    void wait_7();
    void wait_9();
    void wait_a();
    void walk_1();
    void walk_2(signed char, signed char);
    void walk_3();
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
    void hana_action1(void*);
    void hana_action2(void*);
    void hana_action3(void*);
    void hana_action4(void*);
    void hana_action5(void*);
    void wait_action1(void*);
    void wait_action2(void*);
    void wait_action3(void*);
    void wait_action4(void*);
    void demo();
    void shadowDraw();
    BOOL _draw();
    BOOL _execute();
    BOOL _delete();
    s32 _create();
    void create_Anm();
    void create_hed_Anm();
    void create_bln_Anm();
    void create_itm_Mdl();
    void CreateHeap();

public:
    /* 0x6C4 */ u8 m6C4[0x8AC - 0x6C4];
};

class daNpc_Ko1_childHIO_c {
public:
    daNpc_Ko1_childHIO_c();

public:
    /* Place member variables here */
};

class daNpc_Ko1_HIO_c {
public:
    daNpc_Ko1_HIO_c();

public:
    /* Place member variables here */
};

#endif /* D_A_NPC_KO1_H */
