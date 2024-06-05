#ifndef D_A_OBJ_HBRF1_H
#define D_A_OBJ_HBRF1_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"

namespace daObjHbrf1 {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Mode_e {
            Mode_DOWN_STOP_e,
            Mode_UP_DEMO_WAIT_e,
            Mode_UP_DEMO_TIMER_e,
            Mode_UP_DEMO_e,
            Mode_UP_STOP_e,
            Mode_DOWN_DEMO_WAIT_e,
            Mode_DOWN_DEMO_TIMER_e,
            Mode_DOWN_DEMO_e,
        };

        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,

            PRM_TYPE_W   = 0x01,
            PRM_TYPE_S   = 0x08,

            PRM_EVENT_W  = 0x08,
            PRM_EVENT_S  = 0x10,
        };

        s32 prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        bool prm_get_Type() const { return daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S); }
        u8 prm_get_Event() const { return daObj::PrmAbstract<Prm_e>(this, PRM_EVENT_W, PRM_EVENT_S); }

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

        static Mtx M_tmp_mtx;

        static const char M_arcname[];
        static const char M_evname[];

    public:
        /* 0x2C8 */ f32 m2C8;
        /* 0x2CC */ request_of_phase_process_class mPhs;
        /* 0x2D4 */ J3DModel* mpModel;
        /* 0x2D8 */ Mode_e mMode;
        /* 0x2DC */ s16 mEventIdx;
        /* 0x2DE */ u8 m2DE[2]; // Padding?
        /* 0x2E0 */ s32 m2E0;
        /* 0x2E4 */ u8 m2E4;
    };
};

#endif /* D_A_OBJ_HBRF1_H */
