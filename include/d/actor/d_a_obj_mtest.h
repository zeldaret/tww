#ifndef D_A_OBJ_MTEST_H
#define D_A_OBJ_MTEST_H

#include "f_op/f_op_actor.h"

namespace daObjMtest {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_arg0() const {}
        void prm_get_arg1() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}
    
        void chk_appear();
        void CreateHeap();
        void Create();
        void Mthd_Create();
        void Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void Execute(float(**)[3][4]);
        void Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_MTEST_H */
