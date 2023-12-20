#ifndef D_A_BOMB_H
#define D_A_BOMB_H

#include "f_op/f_op_actor_mng.h"
#include "d/d_a_obj.h"
#include "d/d_particle.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_ext.h"

class daBomb_fuseSmokeEcallBack : public dPa_levelEcallBack {
public:
    daBomb_fuseSmokeEcallBack() {}
    ~daBomb_fuseSmokeEcallBack() {}
    
    void execute(JPABaseEmitter*);
    void executeAfter(JPABaseEmitter*);
    void draw(JPABaseEmitter*);
    
    void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);

    /* 0x04 */ s16 field_0x04;
    /* 0x08 */ const cXyz* mpPos;
    /* 0x0C */ cXyz* field_0x0C;
    /* 0x10 */ cXyz* field_0x10;
    /* 0x14 */ JPABaseEmitter* mpEmitter;
}; // Size 0x18

class daBomb_fuseSparksEcallBack : public dPa_levelEcallBack {
public:
    daBomb_fuseSparksEcallBack() {}
    ~daBomb_fuseSparksEcallBack() {}
    
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);

    void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);

    /* 0x04 */ const cXyz* mpPos;
    /* 0x08 */ JPABaseEmitter* mpEmitter;
}; // Size 0x0C

class dBgS_BombAcch : public dBgS_Acch {
public:
    dBgS_BombAcch() { mbBombThrough = true; }
}; // Size 0x1C4


class daBomb_c : public fopAc_ac_c {
public:
    daBomb_c();

    void draw_norm();
    void draw_nut();
    BOOL draw();
    bool checkExplodeCc_norm();
    bool checkExplodeCc_nut();
    bool checkExplodeCc_cannon();
    bool checkExplodeCc();
    bool checkExplodeTimer();
    bool checkExplode();
    bool checkExplodeBg_norm();
    bool checkExplodeBg_nut();
    bool checkExplodeBg_cannon();
    bool checkExplodeBg();
    void water_tention();
    void posMoveF();
    void bgCrrPos();
    void bgCrrPos_lava();
    void bgCrrPos_water();
    bool chk_water_land();
    bool chk_water_in();
    bool chk_water_sink();
    bool chk_lava_hit();
    bool chk_dead_zone();
    void bound(f32);
    void set_real_shadow_flag();
    void setRoomInfo();
    void makeFireEffect(cXyz&, csXyz&);
    void makeWaterEffect();
    void setFuseEffect();
    void eff_explode_normal(const csXyz*);
    void eff_explode_cheap(const csXyz*);
    void eff_explode();
    int procExplode_init();
    bool procExplode();
    bool procCarry_init();
    bool procCarry();
    bool procWait_init();
    bool procWait();
    bool waitState_cannon();
    void waitState_bomtyu();
    bool procSink();
    BOOL execute();
    void set_wind_vec();
    void anm_play_nut();
    void set_mtx();
    void init_mtx();
    void se_cannon_fly_set();
    void se_cannon_fly_stop();
    void eff_water_splash();
    bool bombDelete();
    bool createHeap();
    int create();
    void create_init();

    enum State_e {
        STATE_0 = 0,
        STATE_1 = 1,
        STATE_2 = 2,
        STATE_3 = 3,
        STATE_4 = 4,
        STATE_5 = 5,
        STATE_6 = 6,
        STATE_7 = 7,
        STATE_8 = 8
    };

    enum Prm_e {
        PRM_STATE_W = 8,
        PRM_STATE_S = 0x00,

        PRM_CHEAP_EFF_W = 1,
        PRM_CHEAP_EFF_S = 0x10,

        PRM_ANGXZERO_W = 1,
        PRM_ANGXZERO_S = 0x11,
    
        PRM_VERSION_W = 1,
        PRM_VERSION_S = 0x1F,
    };

    struct Attr_c {
        const char* resName;
        u32 heapSize;
    };

    const Attr_c& attrType() const { return m_attrType[mType]; }

    s16 getBombRestTime();
    s16 getBombCheck_Flag();
    void setBombCheck_Flag();
    void setBombFire_ON();
    void setBombNoHit();
    void setBombOffCoSet();
    void setBombOnCoSet();
    void setBombNoEff();
    void setBombRestTime(s16 time);
    void setNoGravityTime(s16 time);
    static int prm_make(daBomb_c::State_e, bool, bool);
    bool chk_state(State_e) const;
    void change_state(State_e);
    int prm_get_state() const;
    bool get_explode_instant() const;
    bool prm_get_cheapEff() const;
    bool prm_get_angXZero() const;
    int prm_get_version() const;
    void _prm_chk_version() const;

private:
    typedef bool(daBomb_c::*procFunc)();

    /* 0x290 */ procFunc mFunc;
    /* 0x29C */ request_of_phase_process_class mPhs;
    /* 0x2A4 */ J3DModel* mpModel;
    /* 0x2A8 */ mDoExt_bckAnm mBck0;
    /* 0x2B8 */ mDoExt_bckAnm mBck1;
    /* 0x2C8 */ mDoExt_brkAnm mBrk0;
    /* 0x2E0 */ mDoExt_brkAnm mBrk1;
    /* 0x2F8 */ s32 mType;
    /* 0x2FC */ dBgS_BombAcch mAcch;
    /* 0x4C0 */ dBgS_AcchCir mCir;
    /* 0x500 */ dBgS_ObjGndChk_Yogan mGndChk;
    /* 0x554 */ cXyz field_0x554;
    /* 0x560 */ bool field_0x560;
    /* 0x561 */ bool mbWaterIn;
    /* 0x562 */ u8 field_0x562;
    /* 0x564 */ dCcD_Stts mStts;
    /* 0x5A0 */ dCcD_Sph mSph;
    /* 0x6CC */ daBomb_fuseSmokeEcallBack mSmoke;
    /* 0x6E4 */ daBomb_fuseSparksEcallBack mSparks;
    /* 0x6F0 */ u8 field_0x6F0;
    /* 0x6F1 */ u8 field_0x6F1;
    /* 0x6F2 */ u8 field_0x6F2;
    /* 0x6F3 */ u8 field_0x6F3;
    /* 0x6F4 */ u8 field_0x6F4;
    /* 0x6F5 */ u8 field_0x6F5;
    /* 0x6F6 */ u8 field_0x6F6;
    /* 0x6F7 */ u8 field_0x6F7;
    /* 0x6F8 */ s32 mInitialState;
    /* 0x6FC */ s16 mRestTime;
    /* 0x6FE */ s16 field_0x6FE;
    /* 0x700 */ s16 mNoGravityTime;
    /* 0x702 */ s16 field_0x702;
    /* 0x704 */ cXyz mFusePos; //should figure out what this 3 cXyz thing really is
    /* 0x710 */ cXyz mFusePos2; //seems like several particle structures use it and a couple construct it as a TVec3<f32> array
    /* 0x71C */ cXyz mFusePos3; //others have no special construction, and it gets passed to functions that take cXyz sometimes
    /* 0x728 */ LIGHT_INFLUENCE mPntLight;
    /* 0x748 */ WIND_INFLUENCE mPntWind;
    /* 0x774 */ u8 field_0x774;
    /* 0x778 */ f32 field_0x778;
    /* 0x77C */ u8 field_0x77C;
    /* 0x77D */ u8 field_0x77D;
    /* 0x77E */ u8 field_0x77E;
    /* 0x77F */ u8 field_0x77F;
    /* 0x780 */ u8 field_0x780;
    /* 0x781 */ u8 field_0x781;
    /* 0x782 */ u8 field_0x782;
    /* 0x784 */ int field_0x784;
    /* 0x788 */ cXyz mWindVec;
    /* 0x794 */ u8 field_0x794[0x7C4 - 0x794];
    /* 0x7C4 */ int mMassCounter;
    /* 0x7C8 */ int field_0x7C8;
    
    static const Attr_c m_attrType[];
}; // Size 0x7CC

#endif /* D_A_BOMB_H */
