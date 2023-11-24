#ifndef D_A_OBJ_LIGHT_H
#define D_A_OBJ_LIGHT_H

#include "f_op/f_op_actor.h"

namespace daObjLight {
    class Act_c : public fopAc_ac_c {
    public:
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void init_collision();
        void set_collision();
        s32 _create();
        BOOL _delete();
        void set_fire(int);
        void draw_fire();
        void exe_fire();
        void delete_fire();
        void now_event(short);
        void set_event(short);
        void exe_event();
        void set_mtx();
        void renew_angle();
        void control_light();
        void control_treasure();
        BOOL _execute();
        BOOL _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_LIGHT_H */
