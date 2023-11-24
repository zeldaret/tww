#ifndef D_A_OBJ_HBRF1_H
#define D_A_OBJ_HBRF1_H

#include "f_op/f_op_actor.h"

namespace daObjHbrf1 {
    class Act_c : public fopAc_ac_c {
    public:
        void CreateHeap();
        void Create();
        void Mthd_Create();
        void Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void daObjHbrf1_down_stop();
        void daObjHbrf1_up_demo_wait();
        void daObjHbrf1_up_demo_timer();
        void daObjHbrf1_up_demo();
        void daObjHbrf1_up_stop();
        void daObjHbrf1_down_demo_wait();
        void daObjHbrf1_down_demo_timer();
        void daObjHbrf1_down_demo();
        void Execute(float(**)[3][4]);
        void Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_HBRF1_H */
