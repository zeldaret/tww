#ifndef D_A_OBJ_ITNAK_H
#define D_A_OBJ_ITNAK_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

namespace daObjItnak {
    class Act_c : public fopAc_ac_c {
    public:
        void is_switch() const {}
        void param_get_arg0() const {}
        void param_get_swbit() const {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        s32 _create();
        bool _delete();
        void set_mtx();
        void set_co_se(dCcD_Cyl*);
        void manage_draw_flag();
        void set_collision();
        bool _execute();
        bool _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_ITNAK_H */
