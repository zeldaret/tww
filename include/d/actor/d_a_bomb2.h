#ifndef D_A_BOMB_2_H
#define D_A_BOMB_2_H

#include "f_op/f_op_actor_mng.h"
#include "d/d_a_obj.h"
#include "d/d_particle.h"
#include "d/d_bg_s_acch.h"
#include "d/d_cc_d.h"
#include "d/actor/d_a_bomb.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_ext.h"

namespace daBomb2 {
    class FuseSmokeCB_c : public dPa_levelEcallBack {
    public:
        FuseSmokeCB_c() {}
        virtual ~FuseSmokeCB_c();

        
        void setOldPosP(const cXyz*, const cXyz*);
        void deleteCallBack();

        //void init(JPABaseEmitter*);
        void execute(JPABaseEmitter*);
        void executeAfter(JPABaseEmitter*);
        void draw(JPABaseEmitter*);

        void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);

        s16 field_0x04;
        const cXyz* mpPos;
        const cXyz* field_0x0C;
        const cXyz* field_0x10;
        JPABaseEmitter* mpEmitter;
    };
    
    class FuseSparksCB_c : public dPa_levelEcallBack {
    public:
        FuseSparksCB_c() {}
        virtual ~FuseSparksCB_c();

        void deleteCallBack();

        //void init(JPABaseEmitter*);
        void execute(JPABaseEmitter*);
        //void executeAfter(JPABaseEmitter*);
        void draw(JPABaseEmitter*);

        void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);

        const cXyz* mpPos;
        JPABaseEmitter* mpEmitter;
    };
    
    class Env_c {
    public:
        void set(const cXyz&);
        void clean();
        bool is_end() const;
        void proc(const cXyz&);

        LIGHT_INFLUENCE mPntLight;
        WIND_INFLUENCE mPntWind;
        u8 field_0x4C;
        f32 field_0x50;
    };

    class Act_c : public fopAc_ac_c { 
    public:
        Act_c();
        
        //d_a_bomb_static functions
        void remove_fuse_effect();
        void set_time(int);
        int get_time() const;
        bool chk_eat() const;
        void set_eat();
        void set_no_hit();
        bool chk_explode();

        static int solidHeapCB(fopAc_ac_c*);
        int create_heap_nut();
        int create_heap();
        void crr_init();
        void cc_init();
        void start_explode_instant();
        void start_explode_interval();
        void start_carry();
        void start_proc_call();
        void create_init();
        int _create();
        bool _delete();
        void set_mtx();
        void init_mtx();
        void cc_set();
        void camera_lockoff() const;
        void posMoveF();
        void bgCrrPos();
        void bgCrrPos_lava();
        void bgCrrPos_water();
        bool chk_water_in() const;
        bool chk_lava_in() const;
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
        bool chk_exp_cc_nut();
        bool chk_exp_cc();
        bool chk_exp_bg_nut();
        bool chk_exp_bg();
        bool chk_exp_timer();
        bool chk_sink_bg_nut();
        bool chk_sink_bg();
        bool chk_exp_pre();
        bool chk_exp_post();
        bool chk_sink_post();
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
        bool _execute();
        bool is_draw();
        void draw_nut();
        void draw_shadow();
        bool _draw();

        enum Prm_e {
            PRM_1_W = 1,
            PRM_1_S = 0x08,

            PRM_2_W = 2,
            PRM_2_S = 0x00,
        };

    private: 
        //some of these might be extra since i initially copied them from daBomb_c
        request_of_phase_process_class mPhs;
        J3DModel* mpModel;
        mDoExt_bckAnm mBck0;
        mDoExt_brkAnm mBrk0;
        dBgS_BombAcch mAcch;
        dBgS_AcchCir mCir;
        dBgS_ObjGndChk_Yogan mGndChk;
        f32 field_0x51C;
        f32 field_0x520;
        bool field_0x524;
        bool mbWaterIn;
        u8 field_0x526;
        f32 field_0x528;
        dCcD_Stts mStts;
        dCcD_Sph mSph;
        int field_0x694;
        int field_0x698;

        FuseSmokeCB_c mSmoke;
        FuseSparksCB_c mSparks;
        cXyz field_0x6C0;
        cXyz field_0x6CC;
        cXyz field_0x6D8;
        Env_c mEnv;
        int field_0x738;
        int field_0x73C;
        u8 field_0x740;
        u8 field_0x741;
        u8 field_0x742;
        u8 field_0x743;
        bool field_0x744;
        bool field_0x745;
        cXyz field_0x748;
        Mtx field_0x754;

        static dCcD_SrcSph M_sph_src;
    };
}

#endif /* D_A_BOMB_2_H */
