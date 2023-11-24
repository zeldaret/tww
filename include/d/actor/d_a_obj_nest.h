#ifndef D_A_OBJ_NEST_H
#define D_A_OBJ_NEST_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

namespace daObjNest {
    class Act_c : public fopAc_ac_c {
    public:
        void CreateHeap();
        void Create();
        void Mthd_Create();
        void Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        void vib_set(float);
        void vib_proc();
        void Execute(float(**)[3][4]);
        void Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_NEST_H */
