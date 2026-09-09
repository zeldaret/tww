#ifndef D_A_OBJ_SWFLAT_H
#define D_A_OBJ_SWFLAT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"

namespace daObjSwflat {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Prm_e {
            PRM_TYPE_W = 2,
            PRM_TYPE_S = 0,

            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 8,

            PRM_SWSAVE2_W = 8,
            PRM_SWSAVE2_S = 16,
        };

        s32 prmGetSwNo() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prmGetSwNo2() const { return daObj::PrmAbstract(this, PRM_SWSAVE2_W, PRM_SWSAVE2_S); }
        s32 prmGetType() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }

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

        static const char M_arcname[];
        static Mtx M_tmp_mtx;

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ mDoExt_brkAnm* mpBrkAnm;
        /* 0x2D8 */ dCcD_Stts mStts;
        /* 0x314 */ dCcD_Cyl mCyl;
        /* 0x444 */ JPABaseEmitter* mpEmtrOff;
        /* 0x448 */ JPABaseEmitter* mpEmtrOn;
        /* 0x44C */ cXyz mPos;
        /* 0x458 */ s16 mFrame;
        /* 0x45A */ s16 mFrameMax;
        /* 0x45C */ s16 mDemoTimer;
        /* 0x45E */ s16 mWaitTimer;
        /* 0x460 */ u8 mType;
        /* 0x461 */ u8 mPressed;
        /* 0x462 */ u8 mPressedPrev;
        /* 0x463 */ u8 mSwNo;
        /* 0x464 */ u8 mSwNo2;
        /* 0x465 */ u8 mOffTimer;
        /* 0x466 */ u8 mOnTimer;
        /* 0x467 */ u8 mWaitFlag;
        /* 0x468 */ u8 mDemoState;
    };
};

class daObjSwflat_HIO_c : public JORReflexible {
public:
    daObjSwflat_HIO_c();
    virtual ~daObjSwflat_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mChildID;
    /* 0x08 */ s32 mRefCount;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 mHeight;
    /* 0x14 */ s16 mDelay;
    /* 0x16 */ s16 mWait;
    /* 0x18 */ u8 mbDebug;
    /* 0x19 */ u8 mbKeepSwitch;
};

#endif /* D_A_OBJ_SWFLAT_H */
