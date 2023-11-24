#ifndef D_A_OBJ_TRY_H
#define D_A_OBJ_TRY_H

#include "f_op/f_op_actor.h"

namespace daObjTry {
    class Act_c : public fopAc_ac_c {
    public:
        void to_correct_pos(const cXyz*, short, bool, bool) {}
    
        void prm_set_swSave(int);
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void init_cc();
        void search_sameType(void*, void*);
        void chk_appear() const;
        void _create();
        void _delete();
        void mode_restart_init();
        void mode_restart();
        void mode_wait_init();
        void mode_wait();
        void mode_carry_init();
        void mode_carry();
        void mode_drop_init();
        void mode_drop();
        void mode_sink_init();
        void mode_sink();
        void mode_proc_call();
        void cull_set_draw();
        void cull_set_move();
        void damaged();
        void damage_cc_proc();
        void damage_bg_proc();
        void damage_bg_proc_directly();
        void chk_sink_water();
        void chk_sinkdown_water();
        void calc_drop_param(float*, float*, float*) const;
        void bound();
        void se_fall_water();
        void set_senv(int, int) const;
        void cam_lockoff() const;
        void set_mtx();
        void init_mtx();
        void eff_set_bingo(bool, bool);
        void eff_clr_bingo();
        void eff_land_smoke();
        void eff_hit_water_splash();
        void make_vib();
        void check_circle();
        void get_water_h();
        void _execute();
        void _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_TRY_H */
