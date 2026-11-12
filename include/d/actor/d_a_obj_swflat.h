#ifndef D_A_OBJ_SWFLAT_H
#define D_A_OBJ_SWFLAT_H

#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_cc_d.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

class JPABaseEmitter;

namespace daObjSwflat {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_TYPE_W = 0x02,
            PRM_TYPE_S = 0x00,

            PRM_SWNO_W = 0x08,
            PRM_SWNO_S = 0x08,

            PRM_SWNO2_W = 0x08,
            PRM_SWNO2_S = 0x10,
        };

        int prmGetSwNo() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWNO_W, PRM_SWNO_S); }
        int prmGetSwNo2() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWNO2_W, PRM_SWNO2_S); }
        int prmGetType() const { return daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S); }

        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
        virtual BOOL IsDelete();

        static Mtx M_tmp_mtx;
        static const char M_arcname[];

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ mDoExt_brkAnm* mpBrkAnm;
        /* 0x2D8 */ dCcD_Stts mStts;
        /* 0x314 */ dCcD_Cyl mCyl;
        /* 0x444 */ JPABaseEmitter* mpEmitterOff;
        /* 0x448 */ JPABaseEmitter* mpEmitterOn;
        /* 0x44C */ cXyz mEffPos;
        /* 0x458 */ s16 mFrame;
        /* 0x45A */ s16 mFrameMax;
        /* 0x45C */ s16 mTimer;
        /* 0x45E */ s16 mFixTimer;
        /* 0x460 */ u8 mType;
        /* 0x461 */ u8 mIsOn;
        /* 0x462 */ u8 mWasOn;
        /* 0x463 */ u8 mSwNo;
        /* 0x464 */ u8 mSwNo2;
        /* 0x465 */ u8 mAlphaOff;
        /* 0x466 */ u8 mAlphaOn;
        /* 0x467 */ u8 mFixed;
        /* 0x468 */ u8 mEvState;
    };  // Size: 0x46C
};

#endif /* D_A_OBJ_SWFLAT_H */
