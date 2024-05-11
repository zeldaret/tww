#ifndef D_A_OBJ_LADDER_H
#define D_A_OBJ_LADDER_H

#include "d/d_a_obj.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor.h"

namespace daObjLadder {
    enum Type_e {
        MHSG6_e,
        MHSG9_e,
        MHSG12_e,
        MHSG15_e,
        MHSG4H_e,
    };

    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Mode_e {
            Mode_WAIT_e,
            Mode_DEMOREQ_e,
            Mode_VIB_e,
            Mode_DROP_e,
            Mode_FELL_e,
        };

        enum Prm_e {
            PRM_EV_ID_W = 0x08,
            PRM_EV_ID_S = 0x10,

            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x08,

            PRM_TYPE_W = 0x03,
            PRM_TYPE_S = 0x00,
        };

        u8 prm_get_evId() const { return daObj::PrmAbstract<Prm_e>(this, PRM_EV_ID_W, PRM_EV_ID_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        Type_e prm_get_type() const { return (Type_e)daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S); }

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
        /* 0x2D4 */ Type_e mType;
        /* 0x2D8 */ Mode_e mMode;
        /* 0x2DC */ s16 unk2DC;
        /* 0x2DE */ s16 unk2DE;
        /* 0x2E0 */ f32 mGndY;
        /* 0x2E4 */ dBgS_ObjGndChk mGndChk;
        /* 0x338 */ s16 unk338;
        /* 0x33A */ s16 unk33A;
        /* 0x33C */ f32 unk33C;
        /* 0x340 */ f32 unk340;
        /* 0x344 */ s16 mEventIdx;
        /* 0x346 */ u8 unk346;
    };
};

#endif /* D_A_OBJ_LADDER_H */
