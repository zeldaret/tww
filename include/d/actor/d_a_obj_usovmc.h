#ifndef D_A_OBJ_USOVMC_H
#define D_A_OBJ_USOVMC_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"

namespace daObjUsovmc {
    class Act_c : public dBgS_MoveBgActor {
    public:
        virtual int CreateHeap() /* override */;
        virtual int Create() /* override */;
        virtual int Delete() /* override */;
        virtual int Execute(Mtx**) /* override */;
        virtual int Draw() /* override */;

        s32 Mthd_Create();
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
