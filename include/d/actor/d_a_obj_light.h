#ifndef D_A_OBJ_LIGHT_H
#define D_A_OBJ_LIGHT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_w.h"
#include "d/d_particle.h"
#include "m_Do/m_Do_ext.h"

namespace daObjLight {
    class Act_c : public fopAc_ac_c {
    public:
        static int solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        void init_collision();
        void set_collision();
        cPhs_State _create();
        bool _delete();
        bool set_fire(int);
        void draw_fire();
        void exe_fire();
        void delete_fire();
        bool now_event(s16);
        BOOL set_event(s16);
        void exe_event();
        void set_mtx();
        void renew_angle();
        void control_light();
        void control_treasure();
        bool _execute();
        bool _draw();
        
        static bool renew_light_angle();
        static s16 get_light_angle();
        static s16 get_light_dif_angle();
        static bool set_light_dif_angle_LOD(s16);
        static bool set_light_dif_angle_FRRS(s16);

        static s16 M_S_light_angle;
        static u32 M_S_pre_set_frame_LOD;
        static u32 M_S_pre_set_frame_FRRS;
        static u8 M_S_lod_access;

        static const char M_arcname[];
        static const dCcD_SrcCyl M_cyl_src;

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mModels[3];
        /* 0x2a4 */ dBgW* mBgW;
        /* 0x2a8 */ Mtx mMtx;
        /* 0x2d8 */ s16 mLightAngle;
        /* 0x2da */ s16 mFireState;
        /* 0x2dc */ s16 mIsDay;
        /* 0x2de */ s16 mEventState;
        /* 0x2e0 */ dCcD_Stts mStts;
        /* 0x31c */ dCcD_Cyl mCyl;
        /* 0x44c */ dPa_followEcallBack mPa;
        /* 0x460 */ s16 mTimer;
        /* 0x462 */ s16 mFireAngle;
        /* 0x464 */ u8 mAlphaModelId;
        /* 0x465 */ u8 mPadding[3];
        /* 0x468 */ float mScale;
        /* 0x46c */ Mtx mFireMtx;
        /* 0x49c */ s16 mRunningEventIdx;
        /* 0x49e */ s16 mRunningEventState;
        /* 0x4a0 */ s16 mEventIdx;
        /* 0x4a2 */ u8 mPadding3[2];
    };
};

#endif /* D_A_OBJ_LIGHT_H */
