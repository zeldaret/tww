#ifndef D_A_OBJ_EKSKZ_H
#define D_A_OBJ_EKSKZ_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"

namespace daObjEkskz {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_swSave() const {}
    
        int CreateHeap();
        int Create();
        void Mthd_Create();
        BOOL Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        int Execute(float(**)[3][4]);
        BOOL Draw();
    
    public:
        /* 0x2C8 */ u8 m2C8[0x2D0 - 0x2C8];
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
        /* 0x504 */ u8 m504[0x50C - 0x504];
        /* 0x50C */ JPABaseEmitter* mpSmoke0;
        /* 0x510 */ u8 m510[0x514 - 0x510];
        /* 0x514 */ dKy_tevstr_c mTevStr;
    };
};

#endif /* D_A_OBJ_EKSKZ_H */
