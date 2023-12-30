#ifndef D_A_OBJ_BARREL_H
#define D_A_OBJ_BARREL_H

#include "f_op/f_op_actor.h"

namespace daObjBarrel {
    class Act_c : public fopAc_ac_c {
    public:
        void attr() const {}
        void get_slant_angle() {}
        void pos_init() {}
        void prm_get_cull() const {}
        void set_slant_angle(short) {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        s32 _create();
        BOOL _delete();
        void mode_wait_init();
        void mode_wait();
        void mode_carry_init();
        void mode_carry();
        void mode_vib0_init();
        void mode_vib0();
        void mode_vib1_init();
        void mode_vib1();
        void mode_vib2_init();
        void mode_vib2();
        void mode_jump_init();
        void mode_jump();
        void mode_walk_init();
        void mode_walk();
        void vib_pos_ang();
        void mode_proc_call();
        void set_mtx();
        void init_mtx();
        void set_walk_rot();
        void eff_break();
        void damaged(bool);
        void cull_set_draw();
        void cull_set_move();
        void get_se_map_hit() const;
        void set_senv(int, int) const;
        void se_fall_water();
        void eff_hit_water_splash();
        void chk_sink_water();
        void chk_sinkdown_water();
        void eff_land_smoke();
        void damage_cc_proc();
        void damage_bg_proc();
        void damage_bg_proc_directly();
        BOOL _execute();
        BOOL _draw();
    
    public:
        /* Place member variables here */
    };
    
    namespace Method {
        s32 Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
    };
};

#endif /* D_A_OBJ_BARREL_H */
