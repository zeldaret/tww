#ifndef D_A_OBJ_SWHEAVY_H
#define D_A_OBJ_SWHEAVY_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

namespace daObjSwheavy {
    class Act_c : public fopAc_ac_c {
    public:
        void attr() const {}
        void is_switch() const {}
        void off_switch() const {}
        void on_switch() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}
        void rev_switch() const {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void _create();
        void _delete();
        void set_mtx();
        void init_mtx();
        void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        void calc_top_pos();
        void top_bg_aim_req(float, short);
        void set_push_flag();
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void _execute();
        void _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_SWHEAVY_H */
