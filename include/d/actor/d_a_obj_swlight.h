#ifndef D_A_OBJ_SWLIGHT_H
#define D_A_OBJ_SWLIGHT_H

#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphAnimator/J3DNode.h"

namespace daObjSwlight {
    class Act_c : public fopAc_ac_c {
    public:
        void get_power() const {}
        void is_switch() const {}
        void off_switch() const {}
        void on_switch() const {}
        void prm_get_swSave() const {}
        void prm_get_swSave2() const {}
        void prm_get_type() const {}
    
        void is_switch2() const;
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void _create();
        void _delete();
        void jnodeCB_moon(J3DNode*, int);
        void set_mtx();
        void init_mtx();
        void init_cc();
        void set_cc_pos();
        void set_cc();
        void init_eye_pos();
        void chk_light();
        void power_up();
        void power_down();
        void mode_norm_moon_init();
        void mode_norm_moon();
        void mode_norm_sun_init();
        void mode_norm_sun();
        void mode_active_moon_init();
        void mode_active_moon();
        void mode_active_sun_init();
        void mode_active_sun();
        void _execute();
        void _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_SWLIGHT_H */
