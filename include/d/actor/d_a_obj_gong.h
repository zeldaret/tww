#ifndef D_A_OBJ_GONG_H
#define D_A_OBJ_GONG_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

class mDoExt_McaMorf;

namespace daObjGong {
    class Act_c : public fopAc_ac_c {
    public:
        static BOOL solidHeapCB(fopAc_ac_c *i_this);
    
        static const char M_arcname[6];
    
        cPhs_State _create();
        bool _execute();
        bool _draw();
        bool _delete();
        bool create_heap();
        void init_mtx();
        void set_mtx();
        bool demo_move();
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ mDoExt_McaMorf * mpMorf;
    };
};

#endif /* D_A_OBJ_GONG_H */
