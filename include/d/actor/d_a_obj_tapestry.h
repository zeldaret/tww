#ifndef D_A_OBJ_TAPESTRY_H
#define D_A_OBJ_TAPESTRY_H

#include "SSystem/SComponent/c_bg_w.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
class JPABaseEmitter;
//class daObjTapestryDrawVtx_c;
class daObjTapestryPacket_c;
class daObjTapestryDrawVtx_c{
public:
    daObjTapestryDrawVtx_c();
public:
     /* 0x000 */ char pad0[0x240];
    /* 0x240 */ dCcD_Stts *unk240(cXyz*);      /* inferred */
    /* 0x240 */ char pad240[0x240];
    /* 0x480 */ dCcD_Stts *unk480(cXyz*);      /* inferred */
    /* 0x480 */ char pad480[1];
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

class daObjTapestryFireEff_c: public dPa_followEcallBack {
public:
    void get_pos() const {}
    void set_pos(const cXyz&) {}
    void set_spd(const cXyz&) {}

    void execute(JPABaseEmitter*);
};

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
    void eff_start_chk(int, int);
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
    /* 0x0010 */ dCcD_Stts *unk10(cXyz *);      /* inferred */
    /* 0x0010 */ char pad10[0x170];
    ///* 0x0180 */ @unnamed@d_a_obj_tapestry_cpp@ unk180; /* inferred */
    /* 0x0180 */ char pad180[0xC10];
    /* 0x0D90 */ dCcD_Stts *unkD90(cXyz *);     /* inferred */
    /* 0x0D90 */ char padD90[0x2D0];
    /* 0x1060 */ s32 unk1060;                       /* inferred */
    /* 0x1064 */ dCcD_Stts *unk1064(cXyz *);    /* inferred */
    /* 0x1064 */ char pad1064[0x2C0];
    /* 0x1324 */ s32 unk1324;                       /* inferred */
    /* 0x1328 */ cXyz unk1328;                      /* inferred */

    /* 0x1334 */ mDoMtx_stack_c unk1334;            /* inferred */
    /* 0x1334 */ char pad1334[0x2F];
    /* 0x1364 */ mDoMtx_stack_c unk1364;            /* inferred */
    /* 0x1364 */ char pad1364[0x2F];
    /* 0x1394 */ mDoMtx_stack_c unk1394;            /* inferred */
    /* 0x1394 */ char pad1394[0x2F];
    /* 0x13C4 */ u8 unk13C4;                        /* inferred */
    /* 0x13C5 */ char pad13C5[3];                   /* maybe part of unk13C4[4]? */
    /* 0x13C8 */ f32 unk13C8;                       /* inferred */
    /* 0x13CC */ f32 unk13CC;                       /* inferred */
    /* 0x13D0 */ f32 unk13D0;                       /* inferred */
    /* 0x13D4 */ f32 unk13D4;                       /* inferred */
    /* 0x13D8 */ f32 unk13D8;                       /* inferred */
    /* 0x13DC */ f32 unk13DC;                       /* inferred */
    /* 0x13E0 */ s16 unk13E0;                       /* inferred */
    /* 0x13E2 */ char pad13E2[2];
    /* 0x13E4 */ f32 unk13E4;                       /* inferred */
    /* 0x13E8 */ f32 unk13E8;                       /* inferred */
    /* 0x13EC */ f32 unk13EC;                       /* inferred */
    /* 0x13F0 */ s16 unk13F0;                       /* inferred */
    /* 0x13F2 */ s16 unk13F2;                       /* inferred */
    /* 0x13F4 */ s16 unk13F4;                       /* inferred */
    /* 0x13F6 */ char pad13F6[2];
    /* 0x13F8 */ f32 unk13F8;                       /* inferred */
    /* 0x13FC */ f32 unk13FC;                       /* inferred */
    /* 0x1400 */ f32 unk1400;                       /* inferred */
    /* 0x1404 */ f32 unk1404;                       /* inferred */
    /* 0x1408 */ f32 unk1408;                       /* inferred */
    /* 0x140C */ f32 unk140C;                       /* inferred */
    /* 0x1410 */ f32 unk1410;                       /* inferred */
    /* 0x1414 */ f32 unk1414;                       /* inferred */
    /* 0x1418 */ f32 unk1418;                       /* inferred */
    /* 0x141C */ f32 unk141C;                       /* inferred */
    /* 0x1420 */ f32 unk1420;                       /* inferred */
    /* 0x1424 */ f32 unk1424;                       /* inferred */
    /* 0x1428 */ f32 unk1428;                       /* inferred */
    /* 0x142C */ f32 unk142C;                       /* inferred */
    /* 0x1430 */ f32 unk1430;                       /* inferred */
    /* 0x1434 */ f32 unk1434;                       /* inferred */
    /* 0x1438 */ f32 unk1438;                       /* inferred */
    /* 0x143C */ f32 unk143C;                       /* inferred */
    /* 0x1440 */ f32 unk1440;                       /* inferred */
    /* 0x1444 */ f32 unk1444;                       /* inferred */
    /* 0x1448 */ f32 unk1448;                       /* inferred */
    /* 0x144C */ f32 unk144C;                       /* inferred */
    /* 0x1450 */ f32 unk1450;                       /* inferred */
    /* 0x1454 */ u8 unk1454;                        /* inferred */
    /* 0x1455 */ char pad1455[3];                   /* maybe part of unk1454[4]? */
    /* 0x1458 */ f32 unk1458;                       /* inferred */
    /* 0x145C */ f32 unk145C;                       /* inferred */
    /* 0x1460 */ f32 unk1460;                       /* inferred */
    /* 0x1464 */ u8 unk1464;                        /* inferred */
    /* 0x1465 */ u8 unk1465;                        /* inferred */
    /* 0x1466 */ u8 unk1466;                        /* inferred */
    /* 0x1467 */ char pad1467[1];
    /* 0x1468 */ dPa_followEcallBack unk1468;       /* inferred */
    /* 0x147C */ f32 unk147C;                       /* inferred */
    /* 0x1480 */ f32 unk1480;                       /* inferred */
    /* 0x1484 */ f32 unk1484;                       /* inferred */
    /* 0x1488 */ s32 unk1488;                       /* inferred */
    /* 0x148C */ u16 unk148C;                       /* inferred */
    /* 0x148E */ char pad148E[2];
    /* 0x1490 */ s32 unk1490;                       /* inferred */
    /* 0x1494 */ daObjTapestryPLight_c unk1494;     /* inferred */
    ///* 0x1494 */ char pad1494[1];
}; /* SIZE >= 0x14C0*/

class daObjTapestry_c: public fopAc_ac_c {
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
    void checkCollision();
    void set_eye_pos();
    cPhs_State _create();
    bool _delete();
    void wait_act_proc();
    void demo_request_act_proc();
    void burn_act_proc();
    void burn_act_init_proc();
    void fine_act_init_proc();
    void setup_action(int);
    bool _execute();
    bool _draw();
public:
    /* 0x0290 */ request_of_phase_process_class unk290; /* inferred */
    /* 0x0298 */ daObjTapestryPacket_c packet;      /* inferred */
    /* 0x1758 */ J3DModel* unk1758;
    /* 0x175C */ char pad175C[0x4];
    /* 0x1760 */ Mtx unk1760;
    /* 0x1790 */ dCcD_Tri mTris[2];
    /* 0x1A30 */ dCcD_Stts mStts[2];    /* inferred */
    /* 0x1AA8 */ s16 unk1AA8;                       /* inferred */
    /* 0x1AAA */ s8 unk1AAA;                        /* inferred */
    /* 0x1AAB */ char pad1AAB[1];
    /* 0x1AAC */ s16 unk1AAC;                       /* inferred */
    /* 0x1AAE */ char pad1AAE[2];
    /* 0x1AB0 */ f32 unk1AB0;                       /* inferred */
    /* 0x1AB4 */ s32 unk1AB4;                       /* inferred */
    /* 0x1AB8 */ s32 unk1AB8;                       /* inferred */
    /* 0x1ABC */ s32 unk1ABC;                       /* inferred */
    /* 0x1AC0 */ s32 unk1AC0;                       /* inferred */
}; /* SIZE = 0x1AC4 */

class daObjTapestry_HIO_c : public JORReflexible{
public:
    daObjTapestry_HIO_c();
    virtual ~daObjTapestry_HIO_c();
public:
    s32 field_4;
    s32 field_8;
    s32 field_C;
    s8  field_10[0x6C-0x10];
    /* Place member variables here */
}; //Size 0x6C

#endif /* D_A_OBJ_TAPESTRY_H */
