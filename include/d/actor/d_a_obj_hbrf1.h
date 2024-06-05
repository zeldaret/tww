#ifndef D_A_OBJ_HBRF1_H
#define D_A_OBJ_HBRF1_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"

namespace daObjHbrf1 {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_Event() const {}
        void prm_get_Type() const {}
        void prm_get_swSave() const {}

        BOOL CreateHeap();
        int Create();
        s32 Mthd_Create();
        BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void daObjHbrf1_down_stop();
        void daObjHbrf1_up_demo_wait();
        void daObjHbrf1_up_demo_timer();
        void daObjHbrf1_up_demo();
        void daObjHbrf1_up_stop();
        void daObjHbrf1_down_demo_wait();
        void daObjHbrf1_down_demo_timer();
        void daObjHbrf1_down_demo();
        BOOL Execute(Mtx** mtx);
        BOOL Draw();

        static const char M_arcname[];
        static const char M_evname[];

    public:
        /* 0x2C8 */ f32 m2C8;
        /* 0x2CC */ request_of_phase_process_class mPhs;
        /* 0x2D4 */ J3DModel* mpModel;
        /* 0x2D8 */ u32 m2D8; // State idx?
        /* 0x2DC */ s16 mEventIdx;
        /* 0x2DE */ u8 m2DE[2]; // Padding?
        /* 0x2E0 */ s32 m2E0;
        /* 0x2E4 */ u8 m2E4;
    };
};

#endif /* D_A_OBJ_HBRF1_H */
