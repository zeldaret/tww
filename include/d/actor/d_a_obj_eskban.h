#ifndef D_A_OBJ_ESKBAN_H
#define D_A_OBJ_ESKBAN_H

#include "d/d_bg_s_movebg_actor.h"

namespace daObjEskban {

    static const int DESTROY_VIBRATION_LEN = 35;
    static const int DESTROY_VIBRATION_SHOCK_FRAME_IDX = 28;
    static const int DESTROY_SMOKE_ANM_LEN = 20;

    class Act_c : public dBgS_MoveBgActor {
    public:
        static const char M_arcname[7];
        static const char M_evname[7];
        static Mtx M_tmp_mtx;

        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,
        };
        s32 param_get_swSave() const {
            return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S);
        }

        enum actor_state {
            ST_WAIT = 0,
            ST_DESTROYED = 1,
            ST_CUTSCENING = 2,
            ST_VIBRATING = 3,
            ST_SMOKING = 4,
        };

        Act_c();

        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void eff_m_break(unsigned short, unsigned short);
        void eff_b_break(unsigned short);
        void daObjEskban_effect_set();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

    public:
        /* 0x2C4 Act_c vtable */
        /* 0x2C8 */ dPa_smokeEcallBack* M_smoke;  // name used in assert
        /* 0x2CC */ cXyz mSmokePos;
        /* 0x2D8 */ request_of_phase_process_class mPhs;
        /* 0x2E0 */ J3DModel* mpModel;
        /* 0x2E4 */ dCcD_Stts mCheckStts;
        /* 0x320 */ dCcD_Cyl mCheckCyl;
        /* 0x450 */ dCcD_Stts mCameraStts;
        /* 0x48C */ dCcD_Cyl mCameraCyl;
        /* 0x5BC */ fpc_ProcID mActorID;
        /* 0x5C0 */ dCcD_Stts mCheckSphStts;
        /* 0x5FC */ dCcD_Sph mCheckSph;
        /* 0x728 */ s32 mActorState;
        /* 0x72C */ s32 mRemainingSmokeAnm;
        /* 0x730 */ s32 mRemainingVibration;
        /* 0x734 */ u8 mIsVisible;
    };
};

#endif /* D_A_OBJ_ESKBAN_H */
