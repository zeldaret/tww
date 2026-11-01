#ifndef D_A_OBJ_LIGHT_H
#define D_A_OBJ_LIGHT_H

#include "d/d_cc_d.h"
#include "d/d_particle.h"
#include "f_op/f_op_actor.h"

class dBgW;
class J3DModel;

namespace daObjLight {
    class Act_c : public fopAc_ac_c {
    public:
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        void init_collision();
        void set_collision();
        cPhs_State _create();
        bool _delete();
        BOOL set_fire(int);
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
        static BOOL set_light_dif_angle_LOD(s16);
        static BOOL set_light_dif_angle_FRRS(s16);

        static s16 M_S_light_angle;
        static u32 M_S_pre_set_frame_LOD;
        static u32 M_S_pre_set_frame_FRRS;
        static u8 M_S_lod_access;
        static const char M_arcname[8];
        static const dCcD_SrcCyl M_cyl_src;

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel[3];
        /* 0x2A4 */ dBgW* mpBgW;
        /* 0x2A8 */ Mtx mBgMtx[1];
        /* 0x2D8 */ s16 mAngle;
        /* 0x2DA */ s16 mLightState;
        /* 0x2DC */ s16 mFireOn;
        /* 0x2DE */ s16 mTreasureTimer;
        /* 0x2E0 */ dCcD_Stts mStts;
        /* 0x31C */ dCcD_Cyl mCyl;
        /* 0x44C */ dPa_followEcallBack mFireCb;
        /* 0x460 */ s16 mFireTimer;
        /* 0x462 */ s16 mFireRotX;
        /* 0x464 */ u8 mFireAlpha;
        /* 0x468 */ f32 mFireScale;
        /* 0x46C */ Mtx mFireMtx;
        /* 0x49C */ s16 mEvtId;
        /* 0x49E */ s16 mEvtState;
        /* 0x4A0 */ s16 mEventIdx;
    };  // Size: 0x4A4
};

#endif /* D_A_OBJ_LIGHT_H */
