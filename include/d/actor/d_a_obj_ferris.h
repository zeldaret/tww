#ifndef D_A_OBJ_FERRIS_H
#define D_A_OBJ_FERRIS_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_a_obj.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"

class dBgW;

namespace daObjFerris {
    namespace {
        enum Type_e {
            ONE_e,
        };

        struct Attr_c {
            /* 0x00 */ s16 field_0x00;
            /* 0x02 */ s16 field_0x02;
            /* 0x04 */ f32 mCylR;
            /* 0x08 */ f32 mCylH;
            /* 0x0C */ f32 field_0x0c;
            /* 0x10 */ f32 field_0x10;
            /* 0x14 */ f32 field_0x14;
            /* 0x18 */ f32 field_0x18;
            /* 0x1C */ f32 field_0x1c;
            /* 0x20 */ f32 field_0x20;
        };
    }

    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,
        };

        bool is_switch() const { return fopAcM_isSwitch(const_cast<Act_c*>(this), param_get_swSave()); }
        void off_switch() const { return fopAcM_offSwitch(const_cast<Act_c*>(this), param_get_swSave()); }
        s32 param_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

        bool create_heap();
        s32 _create();
        bool _delete();
        void set_mtx(int);
        void init_mtx();
        bool now_event(short);
        BOOL set_event(short);
        void exe_event();
        void angle_mng();
        void rot_mng();
        void set_collision();
        void make_lean();
        bool _execute();
        bool _draw();

        static BOOL solidHeapCB(fopAc_ac_c*);
        static void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        static const char M_arcname[8];
        static const dCcD_SrcCyl M_cyl_src;
        static const dCcD_SrcSph M_sph_src;

    public:
        /* 0x0290 */ dBgW* mpBgW[6];
        /* 0x02A8 */ s32 mRideState[6];
        /* 0x02C0 */ cXyz mRidePos;
        /* 0x02CC */ request_of_phase_process_class mPhs;
        /* 0x02D4 */ dCcD_Stts field_0x02d4[5];
        /* 0x0400 */ dCcD_Cyl field_0x0400[5];
        /* 0x09F0 */ dCcD_Stts field_0x09f0[5];
        /* 0x0B1C */ dCcD_Cyl field_0x0b1c[5];
        /* 0x110C */ dCcD_Stts field_0x110c[5];
        /* 0x1238 */ dCcD_Sph field_0x1238[5];
        /* 0x1814 */ J3DModel* mpModel[6];
        /* 0x182C */ Mtx mMtx[6];
        /* 0x194C */ s16 mRotTimer;
        /* 0x194E */ s16 mRotState;
        /* 0x1950 */ s16 mRotAngle;
        /* 0x1952 */ s16 mRotSpeed;
        /* 0x1954 */ s16 mEventIdx_kanban_vive;
        /* 0x1956 */ s16 mEventIdx_kanban_start;
        /* 0x1958 */ s16 mFrameTimer;
        /* 0x195A */ s16 mGondolaWaveAngle;
        /* 0x195C */ s16 mGondolaWaveTimer;
        /* 0x195E */ s16 mRideWaveAngle[5];
        /* 0x1968 */ s16 mRideWaveTarget[5];
        /* 0x1972 */ s16 mEventIdx;
        /* 0x1974 */ s16 mEventState;
        /* 0x1976 */ s16 field_0x1976;
    };
};

#endif /* D_A_OBJ_FERRIS_H */
