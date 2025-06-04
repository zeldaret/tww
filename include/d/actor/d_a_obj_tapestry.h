#ifndef D_A_OBJ_TAPESTRY_H
#define D_A_OBJ_TAPESTRY_H


#include "d/d_a_obj.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_hostIO.h"
#include "d/res/res_mcrtn.h"
#include "weak_data_1811.h"

namespace{
#include "assets/l_matDL__d_a_obj_tapestry.h"
l_matDL__d_a_obj_tapestry(l_matDL);
#include "assets/l_Txm_curtainTEX.h"
GXColor l_color = {0x9D,0x9D,0x9D,0xFF};
}

class JPABaseEmitter;


class daObjTapestryPacket_c;


class daObjTapestryDrawVtx_c{
public:
    daObjTapestryDrawVtx_c(){};
public:
    cXyz mBufferVtx[8][6]; 
    cXyz mBufferNrm[8][6];  
    cXyz mBufferThree[8][6];
};
class daObjTapestryMoveVtx_c{
public:
    cXyz mBuffer[8][6];
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
// struct dlSegment{
//     u8 header[3];
//     u8 vtxlayout[12][4];
// };
// struct DrawDataDL{
//     dlSegment segment[7];
//     u8 endpad[0x20];
// };
public:

    daObjTapestryDrawData_c();

    static u32* dl() {return (u32*)l_matDL;}
    static u32 dl_size() {return 0x20;}//sizeof(l_matDL);}
    static ResTIMG* tex_coord() {return (ResTIMG*)&l_Txm_curtainTEX;}

    void ct_tex();
    void ct_dl();
public:

    f32 array[8*6*2];
    /* 0x180 */ u8 m_dl[0x185];
    /* 0x180 */ u8 pad[0x18];

};
int a = sizeof(daObjTapestryDrawData_c);
class daObjTapestry_c;

class daObjTapestryPacket_c : public J3DPacket{

public:
    static daObjTapestryDrawData_c m_draw_data;
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
                 daObjTapestryMoveVtx_c mMoveVtx;
                 u8 unkFD0[3][8][6];
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
    /* 0x1404 */ cXyz unk1404;                       /* inferred */
    /* 0x1410 */ cXyz unk1410;                       /* inferred */
    /* 0x141C */ cXyz unk141C;                       /* inferred */
    /* 0x1428 */ cXyz unk1428;                       /* inferred */
    /* 0x1434 */ cXyz unk1434;                       /* inferred */
    /* 0x1440 */ cXyz unk1440;                       /* inferred */
    /* 0x144C */ f32 unk144C;                       /* inferred */
    /* 0x1450 */ f32 unk1450;                       /* inferred */
    /* 0x1454 */ u8 unk1454;                        /* inferred */
    /* 0x1455 */ char pad1455[3];                   /* maybe part of unk1454[4]? */
    /* 0x1458 */ cXyz unk1458;                       /* inferred */
    /* 0x1464 */ u8 unk1464;                        /* inferred */
    /* 0x1465 */ u8 unk1465;                        /* inferred */
    /* 0x1466 */ u8 unk1466;                        /* inferred */
    /* 0x1467 */ char pad1467[1];
    /* 0x1468 */ daObjTapestrySmokeCB_c unk1468;       /* inferred */
    /* 0x147C */ cXyz unk147C;                       /* inferred */
    /* 0x1488 */ csXyz unk1488;                       /* inferred */
    /* 0x1490 */ s32 unk1490;                       /* inferred */
    /* 0x1494 */ daObjTapestryPLight_c unk1494;     /* inferred */
}; /* SIZE >= 0x14C0*/
class daObjTapestryAttr_c;
class daObjTapestry_c: public fopAc_ac_c {
    enum Prm_e {
        PRM_SWSAVE_W = 0x08,
        PRM_SWSAVE_S = 0x00,
    };
    typedef void(daObjTapestry_c::*ActProcFunc)();
    typedef void(daObjTapestry_c::*InitProcFunc)();


public:
    bool is_switch() const {return fopAcM_isSwitch((fopAc_ac_c*)this,param_get_swSave());}
    void on_switch() const {fopAcM_onSwitch((fopAc_ac_c*)this,param_get_swSave());}
    void param_get_evId() const {}
    int param_get_swSave() const {return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S);}

    bool chk_appear();
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
    unkC[0][0] = other.unkC[0][0];
    unkC[0][1] = other.unkC[0][1];
    unkC[1][0] = other.unkC[1][0];
    unkC[1][1] = other.unkC[1][1];
    unkC[2][0] = other.unkC[2][0];
    unkC[2][1] = other.unkC[2][1];
    unkC[3][0] = other.unkC[3][0];
    unkC[3][1] = other.unkC[3][1];
    unkC[4][0] = other.unkC[4][0];
    unkC[4][1] = other.unkC[4][1];
    unkC[5][0] = other.unkC[5][0];    
    unkC[5][1] = other.unkC[5][1];
    unkC[6][0] = other.unkC[6][0];
    unkC[6][1] = other.unkC[6][1];
    unkC[7][0] = other.unkC[7][0];
    unkC[7][1] = other.unkC[7][1];
    unk4C = other.unk4C; 
    unk4D = other.unk4D; 
    unk50 = other.unk50; 
    unk54 = other.unk54;
    unk58[0][0] = other.unk58[0][0];
    unk58[0][1] = other.unk58[0][1];
    unk58[1][0] = other.unk58[1][0];
    unk58[1][1] = other.unk58[1][1];
};
public:
    f32 unkC[8][2]; //[0][1] is spring stiffness. [0][0] is mass / spring scaling.
    s8 unk4C;
    s8 unk4D;
    float unk50;
    u8 unk54;
    f32 unk58[2][2];
};

class daObjTapestry_HIO_c : public JORReflexible{

public:
    inline const daObjTapestryAttr_c attr() const { return field_C; }

    daObjTapestry_HIO_c();
    virtual ~daObjTapestry_HIO_c(){};
public:
    s8 field_4;
    s8 field_5;
    s8 field_6;
    s32 field_8;
    daObjTapestryAttr_c field_C;
    bool field_68;
}; //Size 0x6C

#endif /* D_A_OBJ_TAPESTRY_H */
