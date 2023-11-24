#ifndef D_A_OBJ_ITNAK_H
#define D_A_OBJ_ITNAK_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

namespace daObjItnak {
    class Act_c : public fopAc_ac_c {
    public:
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void _create();
        void _delete();
        void set_mtx();
        void set_co_se(dCcD_Cyl*);
        void manage_draw_flag();
        void set_collision();
        void _execute();
        void _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_ITNAK_H */
