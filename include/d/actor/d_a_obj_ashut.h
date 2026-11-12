#ifndef D_A_OBJ_ASHUT_H
#define D_A_OBJ_ASHUT_H

#include "d/d_bg_s_movebg_actor.h"
#include "d/d_a_obj.h"
#include "f_op/f_op_actor_mng.h"

class J3DModel;

namespace daObjAshut {
    struct Attr_c {
        /* 0x00 */ f32 mUpperY;
        /* 0x04 */ f32 mCloseAccel;
        /* 0x08 */ f32 mCloseDrag;
        /* 0x0C */ u8 mCloseBoundNum;
        /* 0x10 */ f32 mCloseBoundRatio;
        /* 0x14 */ f32 mCloseBoundSpeedMax;
        /* 0x18 */ f32 mOpenAccel;
        /* 0x1C */ f32 mOpenDrag;
        /* 0x20 */ f32 mOpenDragSlow;
        /* 0x24 */ u8 mOpenTimer;
        /* 0x25 */ u8 mOpenSlowTime;
        /* 0x26 */ u8 mOpenBoundNum;
        /* 0x28 */ f32 mOpenBoundRatio;
        /* 0x2C */ f32 mOpenBoundSpeedMin;
    };  // Size: 0x30

    class Act_c : public dBgS_MoveBgActor {
    public:
        enum Mode_e {
            Mode_UPPER = 0,
            Mode_U_L = 1,
            Mode_LOWER = 2,
            Mode_L_U = 3,
            Mode_DEMOREQ = 4,
            Mode_NONE = 5,
        };

        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,

            PRM_EVID_W = 0x08,
            PRM_EVID_S = 0x08,
        };

        BOOL is_switch() const { return fopAcM_isSwitch((fopAc_ac_c*)this, prm_get_swSave()); }
        u8 prm_get_evId() const { return daObj::PrmAbstract<Prm_e>(this, PRM_EVID_W, PRM_EVID_S); }
        int prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        bool chk_safe_area() const;
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void mode_demoreq_init(Mode_e);
        void mode_demoreq();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();

        static Mtx M_tmp_mtx;
        static const char M_arcname[];

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ int mMode;
        /* 0x2D8 */ f32 mY;
        /* 0x2DC */ f32 mSpeed;
        /* 0x2E0 */ u8 mBoundNum;
        /* 0x2E2 */ s16 mTimer;
        /* 0x2E4 */ bool mDemoDone;
        /* 0x2E6 */ s16 mEventIdx;
        /* 0x2E8 */ Mode_e mDemoNext;
    };  // Size: 0x2EC
};

#endif /* D_A_OBJ_ASHUT_H */
