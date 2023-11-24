#ifndef D_A_OBJ_COMING_H
#define D_A_OBJ_COMING_H

#include "f_op/f_op_actor.h"

namespace daObjComing {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_waitTime() const;
        void chk_switch();
        void _create();
        void _delete();
        void get_aqua_y(const cXyz*);
        void chk_ship_range(const fopAc_ac_c*) const;
        void chk_ship_spd(const fopAc_ac_c*) const;
        void get_make_pos(const fopAc_ac_c*, cXyz*) const;
        void chk_make_pos_gnd(const daObjComing::Act_c::MakeTmp_c*) const;
        void chk_make_pos_wall(const daObjComing::Act_c::MakeTmp_c*) const;
        void chk_make_pos_act(void*, void*);
        void chk_make_pos(const daObjComing::Act_c::MakeTmp_c*) const;
        void barrel2_get_ptn() const;
        void barrel2_get_type(daObjComing::Act_c::Ptn_e);
        void barrel2_get_item(daObjComing::Act_c::Ptn_e);
        void barrel2_get_buoy(daObjComing::Act_c::Ptn_e);
        void barrel2_get_param(daObjComing::PrmBarrel2_c*);
        void mode_barrel2_wait(daObjComing::Ctrl_c*);
        void mode_barrel2_appear(daObjComing::Ctrl_c*);
        void mode_barrel2_leave(daObjComing::Ctrl_c*);
        void _execute();
        void _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_COMING_H */
