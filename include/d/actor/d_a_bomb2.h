#ifndef D_A_BOMB2_H
#define D_A_BOMB2_H

#include "JSystem/JParticle/JPAEmitter.h"
#include "f_op/f_op_actor.h"

namespace daBomb2 {
    class Env_c {
    public:
        void set(const cXyz&);
        void clean();
        void is_end() const;
        void proc(const cXyz&);
    };
    
    class FuseSmokeCB_c {
    public:
        ~FuseSmokeCB_c();
        
        void setOldPosP(const cXyz*, const cXyz*);
        void deleteCallBack();
        void execute(JPABaseEmitter*);
        void executeAfter(JPABaseEmitter*);
        void draw(JPABaseEmitter*);
        void setup(JPABaseEmitter*, const cXyz*, const csXyz*, signed char);
    };
    
    class FuseSparksCB_c {
    public:
        ~FuseSparksCB_c();
        
        void deleteCallBack();
        void execute(JPABaseEmitter*);
        void draw(JPABaseEmitter*);
        void setup(JPABaseEmitter*, const cXyz*, const csXyz*, signed char);
    };
    
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            
        };
        
        void remove_fuse_effect();
        void set_time(int);
        s32 get_time() const;
        bool chk_eat() const;
        void set_eat();
        void set_no_hit();
        void chk_explode();
        
        void solidHeapCB(fopAc_ac_c*);
        void create_heap_nut();
        void create_heap();
        void crr_init();
        void cc_init();
        void start_explode_instant();
        void start_explode_interval();
        void start_carry();
        void start_proc_call();
        void create_init();
        void _create();
        Act_c();
        void _delete();
        void set_mtx();
        void init_mtx();
        void cc_set();
        void camera_lockoff() const;
        void posMoveF();
        void bgCrrPos();
        void bgCrrPos_lava();
        void bgCrrPos_water();
        void chk_water_in() const;
        void chk_lava_in() const;
        void setRoomInfo();
        void bound(float);
        void set_nut_exp_interval();
        void anm_play();
        void set_wind_vec();
        void eff_explode();
        void eff_explode_normal(const csXyz*);
        void eff_explode_water();
        void eff_fuse_init();
        void eff_fuse_start();
        void eff_fuse_move();
        void eff_fuse_end();
        void eff_water_splash();
        void se_fall_water();
        void se_explode();
        void se_explode_water();
        void se_ignition();
        void set_sound_env(int, int);
        void chk_exp_cc_nut();
        void chk_exp_cc();
        void chk_exp_bg_nut();
        void chk_exp_bg();
        void chk_exp_timer();
        void chk_sink_bg_nut();
        void chk_sink_bg();
        void chk_exp_pre();
        void chk_exp_post();
        void chk_sink_post();
        void set_real_shadow_flag();
        void carry_fuse_start();
        void on_carry();
        void off_carry();
        void mode_wait_init();
        void mode_wait();
        void mode_carry_init();
        void mode_carry();
        void mode_explode_init();
        void mode_explode();
        void mode_sink_init();
        void mode_sink();
        void mode_proc_call();
        void tensor_init();
        void vib_init();
        void vib_proc();
        void set_vib_tensor();
        void tensor_wait();
        void tensor_wait_drop();
        void tensor_wait_ground();
        void tensor_carry();
        void tensor_explode();
        void tensor_sink();
        void tensor_proc_call();
        void _execute();
        void is_draw();
        void draw_nut();
        void draw_shadow();
        void _draw();
    };
};

#endif /* D_A_BOMB2_H */
