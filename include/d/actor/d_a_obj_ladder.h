#ifndef D_A_OBJ_LADDER_H
#define D_A_OBJ_LADDER_H

#include "d/d_a_obj.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor.h"

namespace daObjLadder {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_EV_ID_W = 0x08,
            PRM_EV_ID_S = 0x10,

            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x08,

        };

        u8 prm_get_evId() const { return daObj::PrmAbstract<Prm_e>(this, PRM_EV_ID_W, PRM_EV_ID_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
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
        /* 0x2D4 */ s32 unk2D4;         /* inferred */
        /* 0x2D8 */ s32 unk2D8;         /* inferred */
        /* 0x2DC */ s16 unk2DC;         /* inferred */
        /* 0x2DE */ s16 unk2DE;         /* inferred */
        /* 0x2E0 */ f32 unk2E0;         /* inferred */
        ///* 0x2E4 */ cBgS_GndChk unk2E4; /* inferred */
        /* 0x2E4 */ char pad2E4[8];
        /* 0x2EC */ s32 unk2EC;           /* inferred */
        /* 0x2F0 */ char pad2F0[8];       /* maybe part of unk2EC[3]? */
        ///* 0x2F8 */ cBgS_PolyInfo unk2F8; /* inferred */
        /* 0x2F8 */ char pad2F8[0x10];
        /* 0x308 */ f32 unk308;        /* inferred */
        /* 0x30C */ f32 unk30C;        /* inferred */
        /* 0x310 */ f32 unk310;        /* inferred */
        /* 0x314 */ char pad314[0x24]; /* maybe part of unk310[0xA]? */
        /* 0x338 */ s16 unk338;        /* inferred */
        /* 0x33A */ s16 unk33A;        /* inferred */
        /* 0x33C */ f32 unk33C;        /* inferred */
        /* 0x340 */ f32 unk340;        /* inferred */
        /* 0x344 */ s16 mEventIdx;        /* inferred */
        /* 0x346 */ u8 unk346;         /* inferred */
    };
};

#endif /* D_A_OBJ_LADDER_H */
