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
        virtual ~FuseSmokeCB_c() {}

        
        void setOldPosP(const cXyz*, const cXyz*);
        void deleteCallBack();

        void execute(JPABaseEmitter*);
        void executeAfter(JPABaseEmitter*);
        void draw(JPABaseEmitter*);

        void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);

        /* 0x04 */ s16 field_0x04;
        /* 0x08 */ const cXyz* mpPos;
        /* 0x0C */ const cXyz* field_0x0C;
        /* 0x10 */ const cXyz* field_0x10;
        /* 0x14 */ JPABaseEmitter* mpEmitter;
    }; // Size 0x18
    
    class FuseSparksCB_c : public dPa_levelEcallBack {
    public:
        FuseSparksCB_c() {}
        virtual ~FuseSparksCB_c() {}

        void deleteCallBack();

        void execute(JPABaseEmitter*);
        void draw(JPABaseEmitter*);

        void setup(JPABaseEmitter*, cXyz const*, csXyz const*, s8);

        /* 0x04 */ const cXyz* mpPos;
        /* 0x08 */ JPABaseEmitter* mpEmitter;
    }; // Size 0x0C
    
    class Env_c {
    public:
        void set(const cXyz&);
        void clean();
        bool is_end() const;
        void proc(const cXyz&);

    private:
        /* 0x00 */ LIGHT_INFLUENCE mPntLight;
        /* 0x20 */ WIND_INFLUENCE mPntWind;
        /* 0x4C */ u8 field_0x4C;
        /* 0x50 */ f32 field_0x50;
    }; // Size 0x54

    enum Start_e {
        
    };

    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_start() const {}
        void prm_get_stick() const {}
        void prm_make(Start_e, bool) {}
    
        Act_c();
        
        //d_a_bomb_static functions
        void remove_fuse_effect();
        void set_time(int);
        int get_time() const;
        bool chk_eat() const;
        void set_eat();
        void set_no_hit();
        bool chk_explode();

        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap_nut();
        bool create_heap();
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
        //some of these might need updating since i initially copied them from daBomb_c
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_bckAnm mBck0;
        /* 0x2AC */ mDoExt_brkAnm mBrk0;
        /* 0x2C4 */ dBgS_BombAcch mAcch;
        /* 0x488 */ dBgS_AcchCir mCir;
        /* 0x4C8 */ dBgS_ObjGndChk_Yogan mGndChk;
        /* 0x51C */ f32 field_0x51C;
        /* 0x520 */ f32 field_0x520;
        /* 0x524 */ bool field_0x524;
        /* 0x525 */ bool mbWaterIn;
        /* 0x526 */ u8 field_0x526;
        /* 0x528 */ f32 field_0x528;
        /* 0x52C */ dCcD_Stts mStts;
        /* 0x568 */ dCcD_Sph mSph;
        /* 0x694 */ int field_0x694;
        /* 0x698 */ int field_0x698;

        /* 0x69C */ FuseSmokeCB_c mSmoke;
        /* 0x6B4 */ FuseSparksCB_c mSparks;
        /* 0x6C0 */ cXyz field_0x6C0;
        /* 0x6CC */ cXyz field_0x6CC;
        /* 0x6D8 */ cXyz field_0x6D8;
        /* 0x6E4 */ Env_c mEnv;
        /* 0x738 */ int field_0x738;
        /* 0x73C */ int field_0x73C;
        /* 0x740 */ u8 field_0x740;
        /* 0x741 */ u8 field_0x741;
        /* 0x742 */ u8 field_0x742;
        /* 0x743 */ u8 field_0x743;
        /* 0x744 */ bool field_0x744;
        /* 0x745 */ bool field_0x745;
        /* 0x748 */ cXyz field_0x748;
        /* 0x754 */ Mtx field_0x754;
        /* 0x784 */ f32 field_0x784;
        /* 0x788 */ f32 field_0x788;
        /* 0x78C */ f32 field_0x78C;
        /* 0x790 */ f32 field_0x790;
        /* 0x794 */ f32 field_0x794;
        /* 0x798 */ f32 field_0x798;
        /* 0x79C */ f32 field_0x79C;
        /* 0x7A0 */ f32 field_0x7A0;
        /* 0x7A4 */ f32 field_0x7A4;
        /* 0x7A8 */ s32 field_0x7A8;

        static dCcD_SrcSph M_sph_src;
    }; // Size 0x7AC
}

#endif /* D_A_BOMB_2_H */
