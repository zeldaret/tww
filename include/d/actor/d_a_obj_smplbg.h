#ifndef D_A_OBJ_SMPLBG_H
#define D_A_OBJ_SMPLBG_H

#include "f_op/f_op_actor.h"

namespace daObjSmplbg {
    class Act_c : public fopAc_ac_c {
    public:
        void attr() const {}
        void isStop() {}
        void offStop() {}
        void onStop() {}
        void prm_get_type() const {}
    
        void CreateHeap();
        void Create();
        void Mthd_Create();
        void Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void exec_qtkhd();
        void Execute(float(**)[3][4]);
        void Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_SMPLBG_H */
