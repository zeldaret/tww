#ifndef D_A_OBJ_HAMI2_H
#define D_A_OBJ_HAMI2_H

#include "f_op/f_op_actor.h"

namespace daObjHami2 {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_swSave() const {}
    
        void CreateHeap();
        s32 Create();
        cPhs_State Mthd_Create();
        BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void daObjHami2_close_stop();
        void daObjHami2_open_demo_wait();
        void daObjHami2_open_demo();
        void daObjHami2_open_stop();
        void daObjHami2_close_demo_wait();
        void daObjHami2_close_demo();
        void Execute(float(**)[3][4]);
        BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_HAMI2_H */
