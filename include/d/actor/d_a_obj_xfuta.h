#ifndef D_A_OBJ_XFUTA_H
#define D_A_OBJ_XFUTA_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

namespace daObjXfuta {
    class Act_c : public fopAc_ac_c {
    public:
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void _create();
        void _delete();
        void set_mtx();
        void _execute();
        void _draw();
    
    public:
        /* 0x290 */ void* vtbl;
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ J3DModel* mpModel;
    };
};

#endif /* D_A_OBJ_XFUTA_H */
