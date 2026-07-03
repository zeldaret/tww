#ifndef D_A_OBJ_DRIFT_H
#define D_A_OBJ_DRIFT_H

#include "SSystem/SComponent/c_xyz.h"
#include "d/d_bg_s_movebg_actor.h"
#include "dolphin/types.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

namespace daObjDrift {
    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Mode {
            MODE_WAIT  = 0x0,
            MODE_ROT   = 0x1,
        };
        
        enum Prm_e {
            PRM_TYPE_S = 0,
            PRM_TYPE_W = 4,

            PRM_STATE_W = 3,
            PRM_STATE_S = 0,
        };
        
        int prm_get_type() const {
            return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S);
        }
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        void make_flower();
        void calc_flower_param(cXyz*, csXyz*);
        void set_flower_current();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void mode_wait_init();
        void mode_wait();
        void mode_rot_init();
        void mode_rot();
        void set_mtx();
        void init_mtx();
        static void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        void set_current();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static const char M_arcname[];
        static const dCcD_SrcCyl M_cyl_src;
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhase;
        /* 0x2D0 */ J3DModel* mModel;
        /* 0x2D4 */ dCcD_Stts mStts;
        /* 0x310 */ dCcD_Cyl mCyl;
        /* 0x440 */ int mType;
        /* 0x444 */ Mtx mMtx;
        /* 0x474 */ fpc_ProcID mFlowerPid;
        /* 0x478 */ s32 mMode;
        /* 0x47C */ f32 mState[7];
        /* 0x498 */ short mRotSpeedX;
        /* 0x49A */ short mRotSpeedY;
        /* 0x49C */ short mRotSpeedZ;
        /* 0x49E */ bool mRideFlag;
        /* 0x49F */ u8 field_0x49F;
        /* 0x4A0 */ short mTargetAngleY;
        /* 0x4A2 */ short mAngleChaseY;
        /* 0x4A4 */ cXyz mTargetPos;
        /* 0x4B0 */ cXyz mScaleModifier;
        /* 0x4BC */ cXyz mHomePosCopy;
        /* 0x4C8 */ f32 mPrevMtxTransY;
        /* 0x4CC */ f32 mPrevPrevMtxTransY;
        /* 0x4D0 */ f32 field_0x4D0;
        /* 0x4D4 */ f32 field_0x4D4;
        /* 0x4D8 */ f32 mRotTimer;
    };
};

#endif /* D_A_OBJ_DRIFT_H */
