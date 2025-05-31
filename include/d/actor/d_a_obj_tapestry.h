#ifndef D_A_OBJ_TAPESTRY_H
#define D_A_OBJ_TAPESTRY_H

#include "SSystem/SComponent/c_bg_w.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
class JPABaseEmitter;


class daObjTapestryPacket_c;


class daObjTapestryDrawVtx_c{
public:
    daObjTapestryDrawVtx_c();
public:
    cXyz mBufferZero[8][6];
    cXyz mBufferOne[8][6];  
    cXyz mBufferTwo[8][6];  
};


class daObjTapestryPLight_c{
public:
    void plight_delete();
    void plight_move(cXyz, csXyz);
    void plight_make();
    void setPointLight(cXyz, csXyz);

public:
    /* 0x00 */ u8 field_0;                             /* inferred */
    /* 0x01 */ char pad1[3];                        /* maybe part of unk0[4]? */
    /* 0x04 */ LIGHT_INFLUENCE field_4;                /* inferred */
    /* 0x24 */ JPABaseEmitter *field_24;                         /* inferred */
    /* 0x28 */ f32 field_28;                           /* inferred */
    /* Place member variables here */
};

class daObjTapestrySmokeCB_c : public dPa_followEcallBack{
public:

};

class daObjTapestryFireEff_c: public dPa_followEcallBack {
public:
    daObjTapestryFireEff_c(){unk14 = cXyz::Zero; unk20 = cXyz::Zero;}
    void get_pos() const {}
    void set_pos(const cXyz&) {}
    void set_spd(const cXyz&) {}

    void execute(JPABaseEmitter*);
public:
    /* 0x14 */ cXyz unk14;
    /* 0x20 */ cXyz unk20;
}; /* SIZE 2C */

class daObjTapestryDrawData_c {
public:
    daObjTapestryDrawData_c();

    void dl() const {}
    void dl_size() const {}
    void tex_coord() const {}

    void ct_tex();
    void ct_dl();
public:
    //f32 array[8][6][2];
    f32 array[8*6*2];
    /* 0x180 */u32 m_dl[4][3];

};

class daObjTapestry_c;

class daObjTapestryPacket_c : public J3DPacket{

public:
    daObjTapestryPacket_c();

    void set_wind_fun(const cXyz&) {}

    void init(daObjTapestry_c*);
    void update();
    void calc_acc_spring_sub(const cXyz*, const cXyz*, float, float);
    void calc_acc_spring(int, int);
    void calc_acc_gravity();
    void calc_acc_wave(int, int);
    void calc_acc_hit(int, int);
    void calc_spd(int, int);
    void calc_pos_crr(int, int);
    void calc_pos();
    void calc_nrm();
    void calc_wind();
    void calc_hit();
    void calc_fire_leap(int, int);
    void calc_fire();
    void calc(daObjTapestry_c*);
    void set_hit(cXyz, cXyz, float, float, bool);
    cXyz* get_now_pos(int, int);
    void eff_start(int, int);
    u8 eff_start_chk(int, int);
    void eff_end();
    void eff_pos();
    void eff_delete();
    void smokeCallback_init();
    void smoke_set();
    void smoke_move(fopAc_ac_c*);
    void setup_vtx(daObjTapestryDrawVtx_c*);
    void load_tex();
    void setup_rendar();
    void setup_tev_stage();
    void setup_tevColReg(daObjTapestry_c*);
    void draw();
public:
                daObjTapestryDrawVtx_c mDrawVtx[2];
                cXyz unkD90[8][6];
                u8 unkFD0[3][8][6];

    /* 0x1000 */ //u8 unk1000[8][6];
                 char pad1030[0x30];
    /* 0x1060 */ s32 unk1060;                       /* inferred */
    /* 0x1064 */ daObjTapestryFireEff_c unk1064[16];    /* inferred */
    /* 0x1324 */ s32 unk1324;                       /* inferred */
    /* 0x1328 */ cXyz unk1328;                      /* inferred */

    /* 0x1334 */ Mtx unk1334;            /* inferred */
    /* 0x1364 */ Mtx unk1364;            /* inferred */
    /* 0x1394 */ Mtx unk1394;            /* inferred */
    /* 0x13C4 */ u8 unk13C4;                        /* inferred */
    /* 0x13C5 */ char pad13C5[3];                   /* maybe part of unk13C4[4]? */
    /* 0x13C8 */ cXyz unk13C8;                       /* inferred */
    /* 0x13D4 */ cXyz unk13D4;                       /* inferred */

    /* 0x13E0 */ s16 unk13E0;                       /* inferred */
    /* 0x13E2 */ char pad13E2[2];
    /* 0x13E4 */ cXyz unk13E4;                       /* inferred */
    /* 0x13F0 */ s16 unk13F0;                       /* inferred */
    /* 0x13F2 */ s16 unk13F2;                       /* inferred */
    /* 0x13F4 */ s16 unk13F4;                       /* inferred */
    /* 0x13F6 */ char pad13F6[2];
    /* 0x13F8 */ cXyz unk13F8;                       /* inferred */
    // /* 0x13FC */ f32 unk13FC;                       /* inferred */
    // /* 0x1400 */ f32 unk1400;                       /* inferred */
    /* 0x1404 */ cXyz unk1404;                       /* inferred */
    // /* 0x1408 */ f32 unk1408;                       /* inferred */
    // /* 0x140C */ f32 unk140C;                       /* inferred */
    /* 0x1410 */ cXyz unk1410;                       /* inferred */
    // /* 0x1414 */ f32 unk1414;                       /* inferred */
    // /* 0x1418 */ f32 unk1418;                       /* inferred */
    /* 0x141C */ cXyz unk141C;                       /* inferred */
    // /* 0x1420 */ f32 unk1420;                       /* inferred */
    // /* 0x1424 */ f32 unk1424;                       /* inferred */
    /* 0x1428 */ cXyz unk1428;                       /* inferred */
    // /* 0x142C */ f32 unk142C;                       /* inferred */
    // /* 0x1430 */ f32 unk1430;                       /* inferred */
    /* 0x1434 */ cXyz unk1434;                       /* inferred */
    // /* 0x1438 */ f32 unk1438;                       /* inferred */
    // /* 0x143C */ f32 unk143C;                       /* inferred */
    /* 0x1440 */ cXyz unk1440;                       /* inferred */
    // /* 0x1444 */ f32 unk1444;                       /* inferred */
    // /* 0x1448 */ f32 unk1448;                       /* inferred */
    /* 0x144C */ f32 unk144C;                       /* inferred */
    /* 0x1450 */ f32 unk1450;                       /* inferred */
    /* 0x1454 */ u8 unk1454;                        /* inferred */
    /* 0x1455 */ char pad1455[3];                   /* maybe part of unk1454[4]? */
    /* 0x1458 */ cXyz unk1458;                       /* inferred */
    // /* 0x145C */ f32 unk145C;                       /* inferred */
    // /* 0x1460 */ f32 unk1460;                       /* inferred */
    /* 0x1464 */ u8 unk1464;                        /* inferred */
    /* 0x1465 */ u8 unk1465;                        /* inferred */
    /* 0x1466 */ u8 unk1466;                        /* inferred */
    /* 0x1467 */ char pad1467[1];
    /* 0x1468 */ daObjTapestrySmokeCB_c unk1468;       /* inferred */
    /* 0x147C */ cXyz unk147C;                       /* inferred */
    /* 0x1488 */ csXyz unk1488;                       /* inferred */
    //csXyz unk148A;
    // /* 0x1488 */ s16 unk148A;                       /* inferred */
    // /* 0x148C */ u16 unk148C;                       /* inferred */
    // /* 0x148E */ char pad148E[2];
    /* 0x1490 */ s32 unk1490;                       /* inferred */
    /* 0x1494 */ daObjTapestryPLight_c unk1494;     /* inferred */
    ///* 0x1494 */ char pad1494[1];
}; /* SIZE >= 0x14C0*/

class daObjTapestry_c: public fopAc_ac_c {
typedef bool(daObjTapestry_c::*ActProcFunc)();
typedef void(daObjTapestry_c::*InitProcFunc)();

public:
    void is_switch() const {}
    void on_switch() const {}
    void param_get_evId() const {}
    void param_get_swSave() const {}

    void chk_appear();
    void set_mtx();
    void init_mtx();
    int solidHeapCB(fopAc_ac_c*);
    bool create_heap();
    void create_res_load();
    void init_cc();
    void set_cc_pos();
    bool checkCollision();
    void set_eye_pos();
    cPhs_State _create();
    bool _delete();
    bool wait_act_proc();
    bool demo_request_act_proc();
    bool burn_act_proc();
    void burn_act_init_proc();
    void fine_act_init_proc();
    void setup_action(int);
    bool _execute();
    bool _draw();
public:
    /* 0x0290 */ request_of_phase_process_class unk290; /* inferred */
    /* 0x0298 */ daObjTapestryPacket_c packet;      /* inferred */
    /* 0x1758 */ J3DModel* unk1758;
    /* 0x175C */ dBgW* unk175C;
    /* 0x1760 */ Mtx unk1760;
    /* 0x1790 */ dCcD_Tri mTris[2];
    /* 0x1A30 */ dCcD_Stts mStts[2];                /* inferred */
    /* 0x1AA8 */ s16 unk1AA8;                       /* inferred */
    /* 0x1AAA */ s8 unk1AAA;                        /* inferred */
    /* 0x1AAB */ char pad1AAB[1];
    /* 0x1AAC */ s16 unk1AAC;                       /* inferred */
    /* 0x1AAE */ char pad1AAE[2];
    /* 0x1AB0 */ f32 unk1AB0;                       /* inferred */
    /* 0x1AB4 */ ActProcFunc unk1AB4;                       /* inferred */
    /* 0x1AC0 */ s32 unk1AC0;                       /* inferred */
}; /* SIZE = 0x1AC4 */

class daObjTapestryAttr_c { 
public:
    daObjTapestryAttr_c operator=(const daObjTapestryAttr_c& other){

    this->unkC[0] = other.unkC[0];
    unkC[1] = other.unkC[1];
    unkC[2] = other.unkC[2];
    unkC[3] = other.unkC[3];
    unkC[4] = other.unkC[4];
    unkC[5] = other.unkC[5];
    unkC[6] = other.unkC[6];
    unkC[7] = other.unkC[7];
    unkC[8] = other.unkC[8];
    unkC[9] = other.unkC[9];
    unkC[10] = other.unkC[10];
    unkC[11] = other.unkC[11];
    unkC[12] = other.unkC[12];
    unkC[13] = other.unkC[13];
    unkC[14] = other.unkC[14];
    unkC[15] = other.unkC[15];
    unk4C = other.unk4C; 
    unk4D = other.unk4D; 
    unk50 = other.unk50; 
    unk54 = other.unk54;
    unk58 = other.unk58;
    unk5C = other.unk5C;
    unk60 = other.unk60;
    unk64 = other.unk64;

    };
    f32 unkC[16];
    s8 unk4C;
    s8 unk4D;
    float unk50;
    s8 unk54;
    float unk58;
    float unk5C;
    float unk60;
    float unk64;
};

class daObjTapestry_HIO_c : public JORReflexible{
public:
    daObjTapestry_HIO_c();
    virtual ~daObjTapestry_HIO_c(){};
public:
    s8 field_4;
    s8 field_5;
    s8 field_6;
    s32 field_8;
    daObjTapestryAttr_c field_C;
    s8 field_68;
}; //Size 0x6C

#endif /* D_A_OBJ_TAPESTRY_H */
