#ifndef D_A_OBJ_HAMI3_H
#define D_A_OBJ_HAMI3_H

#include "f_op/f_op_actor.h"

namespace daObjHami3 {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_sound() const {}
        void prm_get_swSave() const {}
        void prm_get_swSave2() const {}
    
        void CreateHeap();
        void Create();
        void Mthd_Create();
        void Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void daObjHami3_close_stop();
        void daObjHami3_open_demo_wait();
        void daObjHami3_open_demo();
        void daObjHami3_open_stop();
        void daObjHami3_close_demo_wait();
        void daObjHami3_close_demo();
        void Execute(float(**)[3][4]);
        void Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_HAMI3_H */
