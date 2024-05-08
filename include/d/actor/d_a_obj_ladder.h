#ifndef D_A_OBJ_LADDER_H
#define D_A_OBJ_LADDER_H

#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor.h"

namespace daObjLadder {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_evId() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}

        BOOL CreateHeap();
        int Create();
        s32 Mthd_Create();
        BOOL Delete();
        BOOL Mthd_Delete();
        void demo_end_reset();
        void mode_wait_init();
        void mode_wait();
        void mode_demoreq_init();
        void mode_demoreq();
        void mode_vib_init();
        void mode_vib();
        void mode_drop_init();
        void mode_drop();
        void mode_fell_init();
        void mode_fell();
        void set_mtx();
        void init_mtx();
        int Execute(Mtx**);
        BOOL Draw();

        static Mtx M_tmp_mtx;
        static const char M_arcname[];

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
    };
};

#endif /* D_A_OBJ_LADDER_H */
