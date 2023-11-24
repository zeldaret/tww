#ifndef D_A_OBJ_MSDAN2_H
#define D_A_OBJ_MSDAN2_H

#include "f_op/f_op_actor.h"

namespace daObjMsdan2 {
    class Act_c : public fopAc_ac_c {
    public:
        void Mthd_Create();
        void Mthd_Execute();
        void Mthd_Delete();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_MSDAN2_H */
