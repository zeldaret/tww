#ifndef D_A_STONE_H
#define D_A_STONE_H

#include "f_op/f_op_actor.h"

namespace daStone {
    static BOOL CreateHeapCB(fopAc_ac_c*);
    
    struct Data_c {
        
    };
    
    class Act_c : public fopAc_ac_c {
    public:
        void data() {}
        void prm_get_cull() const {}
        void prm_get_itemNo() const {}
        void prm_get_itemSave() const {}
        void prm_get_moveBg() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}
        void prm_off_moveBg() {}
        
        void create_heap();
        void chk_appear();
        s32 _create();
        bool _delete();
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
        void damaged(int);
        void damage_cc_proc();
        void damage_bg_proc();
        void damage_bg_proc_directly();
        void set_mtx();
        void init_mtx();
        void init_rot_throw();
        void init_rot_clean();
        void set_drop_rot();
        void set_sink_rot();
        void eff_break();
        void eff_hit_water_splash();
        void eff_hit_lava_splash();
        void eff_land_smoke();
        void bg_crr_water();
        void bg_crr_lava();
        void chk_sink_lava();
        void chk_sink_water();
        void water_tention();
        void se_fall_water();
        void se_fall_lava();
        void set_senv(int, int) const;
        void cam_lockoff() const;
        bool _execute();
        bool _draw();
    
    public:
        /* Place member variables here */
    };
    
    namespace Method {
        s32 Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_STONE_H */
