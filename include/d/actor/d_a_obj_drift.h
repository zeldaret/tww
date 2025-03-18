#ifndef D_A_OBJ_DRIFT_H
#define D_A_OBJ_DRIFT_H

#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

namespace daObjDrift {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_type() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        void make_flower();
        void calc_flower_param(cXyz*, csXyz*);
        void set_flower_current();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void mode_wait_init();
        void mode_wait();
        void mode_rot_init();
        void mode_rot();
        void set_mtx();
        void init_mtx();
        void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        void set_current();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_DRIFT_H */
