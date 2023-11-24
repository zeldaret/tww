#ifndef D_A_KOMORE_H
#define D_A_KOMORE_H

#include "f_op/f_op_actor.h"

namespace daKomore {
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
        /* Place member variables here */
    };
};

#endif /* D_A_KOMORE_H */
