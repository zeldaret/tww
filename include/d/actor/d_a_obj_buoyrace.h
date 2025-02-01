#ifndef D_A_OBJ_BUOYRACE_H
#define D_A_OBJ_BUOYRACE_H

#include "f_op/f_op_actor.h"

namespace daObjBuoyrace {
    class Act_c : public fopAc_ac_c {
    public:
        inline s32 _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        void attr() const {}
        void prm_get_id() const {}
        void prm_get_line() const {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void create_load();
        void set_mtx();
        void init_mtx();
        void set_water_pos();
        void afl_calc_sway();
        void afl_calc();
        void set_rope_pos();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_BUOYRACE_H */
