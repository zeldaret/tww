#ifndef D_A_OBJ_EKSKZ_H
#define D_A_OBJ_EKSKZ_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"

namespace daObjEkskz {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,
        };

        s32 prm_get_swSave() const {
            return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S);
        }

        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static const char M_arcname[];
        static Mtx M_tmp_mtx;

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhase;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ dCcD_Stts mStts;
        /* 0x310 */ dCcD_Cyl mCyl;
        /* 0x440 */ J3DModel* mpModelEff;
        /* 0x444 */ mDoExt_bckAnm mBckAnm;
        /* 0x454 */ mDoExt_brkAnm mBrkAnm;
        /* 0x46C */ mDoExt_btkAnm mBtkAnm;
        /* 0x480 */ u8 m480;
        /* 0x481 */ u8 m481[0x484 - 0x481];
        /* 0x484 */ dPa_smokeEcallBack mSmokeCallback[4];
        /* 0x504 */ JPABaseEmitter* mpSmokeEmtr[4];
        /* 0x514 */ dKy_tevstr_c mTevStr;
    };
};

#endif /* D_A_OBJ_EKSKZ_H */
