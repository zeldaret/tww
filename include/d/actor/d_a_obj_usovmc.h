#ifndef D_A_OBJ_USOVMC_H
#define D_A_OBJ_USOVMC_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"

namespace daObjUsovmc {
    class Act_c : public dBgS_MoveBgActor {
    public:
        virtual BOOL CreateHeap() /* override */;
        virtual BOOL Create() /* override */;
        virtual BOOL Delete() /* override */;
        virtual BOOL Execute(Mtx**) /* override */;
        virtual BOOL Draw() /* override */;

        cPhs_State Mthd_Create();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();

    public:
        static const char M_arcname[];
        static Mtx M_tmp_mtx;

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mModel;
    };
};

#endif /* D_A_OBJ_USOVMC_H */
