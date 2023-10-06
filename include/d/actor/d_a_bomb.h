#ifndef D_A_BOMB_H
#define D_A_BOMB_H

#include "d/d_particle.h"
#include "d/d_bg_s_acch.h"
#include "f_op/f_op_actor.h"

class daBomb_fuseSmokeEcallBack : public dPa_levelEcallBack {
public:
    void executeAfter(JPABaseEmitter*);
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, signed char);
};

class daBomb_fuseSparksEcallBack : public dPa_levelEcallBack {
public:
    void execute(JPABaseEmitter*);
    void draw(JPABaseEmitter*);
    void setup(JPABaseEmitter*, const cXyz*, const csXyz*, signed char);
};

class daBomb_c : public fopAc_ac_c {
public:
    enum State_e {
        
    };
    
    s16 getBombRestTime();
    s16 getBombCheck_Flag();
    void setBombCheck_Flag();
    void setBombFire_ON();
    void setBombNoHit();
    void setBombOffCoSet();
    void setBombOnCoSet();
    void setBombNoEff();
    void setBombRestTime(short);
    void setNoGravityTime(short);
    void prm_make(State_e, bool, bool);
    void chk_state(State_e) const;
    void change_state(State_e);
    void prm_get_state() const;
    void get_explode_instant() const;
    void prm_get_cheapEff() const;
    void prm_get_angXZero() const;
    void prm_get_version() const;
    void _prm_chk_version() const;
    
    void draw_norm();
    void draw_nut();
    void draw();
    void checkExplodeCc_norm();
    void checkExplodeCc_nut();
    void checkExplodeCc_cannon();
    void checkExplodeCc();
    void checkExplodeTimer();
    void checkExplode();
    void checkExplodeBg_norm();
    void checkExplodeBg_nut();
    void checkExplodeBg_cannon();
    void checkExplodeBg();
    void water_tention();
    void posMoveF();
    void bgCrrPos();
    void bgCrrPos_lava();
    void bgCrrPos_water();
    void chk_water_land();
    void chk_water_in();
    void chk_water_sink();
    void chk_lava_hit();
    void chk_dead_zone();
    void bound(float);
    void set_real_shadow_flag();
    void setRoomInfo();
    void makeFireEffect(cXyz&, csXyz&);
    void makeWaterEffect();
    void setFuseEffect();
    void eff_explode_normal(const csXyz*);
    void eff_explode_cheap(const csXyz*);
    void eff_explode();
    void procExplode_init();
    void procExplode();
    void procCarry_init();
    void procCarry();
    void procWait_init();
    void procWait();
    void waitState_cannon();
    void waitState_bomtyu();
    void procSink();
    void execute();
    void set_wind_vec();
    void anm_play_nut();
    void set_mtx();
    void init_mtx();
    void se_cannon_fly_set();
    void se_cannon_fly_stop();
    void eff_water_splash();
    void bombDelete();
    void createHeap();
    void create();
    daBomb_c();
    void create_init();
};

class dBgS_BombAcch : public dBgS_Acch {
public:
    
};

#endif /* D_A_BOMB_H */
