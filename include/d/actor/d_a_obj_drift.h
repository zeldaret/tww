#ifndef D_A_OBJ_DRIFT_H
#define D_A_OBJ_DRIFT_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

namespace daObjDrift {
    class Act_c : public fopAc_ac_c {
    public:
        void CreateHeap();
        void Create();
        void Mthd_Create();
        void make_flower();
        void calc_flower_param(cXyz*, csXyz*);
        void set_flower_current();
        void Delete();
        void Mthd_Delete();
        void mode_wait_init();
        void mode_wait();
        void mode_rot_init();
        void mode_rot();
        void set_mtx();
        void init_mtx();
        void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        void set_current();
        void Execute(float(**)[3][4]);
        void Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_DRIFT_H */
