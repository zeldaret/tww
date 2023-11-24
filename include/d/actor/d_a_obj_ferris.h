#ifndef D_A_OBJ_FERRIS_H
#define D_A_OBJ_FERRIS_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

namespace daObjFerris {
    class Act_c : public fopAc_ac_c {
    public:
        void is_switch() const {}
        void off_switch() const {}
        void param_get_swSave() const {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        void _create();
        void _delete();
        void set_mtx(int);
        void init_mtx();
        void now_event(short);
        void set_event(short);
        void exe_event();
        void angle_mng();
        void rot_mng();
        void set_collision();
        void make_lean();
        void _execute();
        void _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_FERRIS_H */
