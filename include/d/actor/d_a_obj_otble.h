#ifndef D_A_OBJ_OTBLE_H
#define D_A_OBJ_OTBLE_H

#include "f_op/f_op_actor.h"

namespace daObj_Otble {
    class Act_c : public fopAc_ac_c {
    public:
        inline s32 _create();
        inline BOOL _delete();
        void attr() const {}
    
        void set_mtx();
        BOOL _execute();
        BOOL _draw();
        void _createHeap();
        void CreateInit();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_OTBLE_H */
