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
        static void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        void vib_set(float);
        void vib_proc();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static Mtx M_tmp_mtx;
        static const char M_arcname[];
    
    public:
        /* Place member variables here */
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ cXyz mcXyz_0x2D4;
        /* 0x2E0 */ csXyz mcsXyz_0x2E0;
        /* 0x2E6 */ csXyz mcsXyz_0x2E6;
    };
};

#endif /* D_A_OBJ_NEST_H */
