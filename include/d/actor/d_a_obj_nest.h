#ifndef D_A_OBJ_NEST_H
#define D_A_OBJ_NEST_H

#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

namespace daObjNest {
    class Act_c : public dBgS_MoveBgActor {
    public:
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        void vib_set(float);
        void vib_proc();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_NEST_H */
