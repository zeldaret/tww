#ifndef D_A_OBJ_LIGHT_H
#define D_A_OBJ_LIGHT_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_xyz.h"
#include "d/d_drawlist.h"
#include "d/d_particle.h"
#include "d/d_com_inf_game.h"
#include "JSystem/JGeometry.h"
#include "dolphin/mtx/mtx.h"
#include "d/d_kankyo.h"
#include "m_Do/m_Do_ext.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/d_bg_s_movebg_actor.h"
#include "JSystem/J3DGraphBase/J3DSys.h"

namespace daObjLight {
    class Act_c : public fopAc_ac_c {
    public:
        static BOOL solidHeapCB(fopAc_ac_c*);

        BOOL create_heap();
        void init_collision();
        void set_collision();
        cPhs_State _create();
        bool _delete();
        BOOL set_fire(int);
        void draw_fire();
        void exe_fire();
        void delete_fire();
        BOOL now_event(s16);
        BOOL set_event(s16);
        void exe_event();
        void set_mtx();
        BOOL renew_angle();
        void control_light();
        void control_treasure();
        bool _execute();
        bool _draw();

        static bool renew_light_angle();
        static s16 get_light_angle();
        static s16 get_light_dif_angle();
        static BOOL set_light_dif_angle_LOD(s16);
        static BOOL set_light_dif_angle_FRRS(s16);

        static const dCcD_SrcCyl M_cyl_src;
        static const char M_arcname[];

        static s16 M_S_light_angle;
        static u32 M_S_pre_set_frame_LOD;
        static u32 M_S_pre_set_frame_FRRS;
        static u8 M_S_lod_access;

    public:
        /* 0x290 */ request_of_phase_process_class mPhase;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ J3DModel* mpModel2;
        /* 0x2A0 */ J3DModel* mpModel3;
        /* 0x2A4 */ dBgW* mpBgW;
        /* 0x2A8 */ Mtx mBgMtx;
        /* 0x2D8 */ s16 field_0x2D8;
        /* 0x2DA */ s16 field_0x2DA;
        /* 0x2DC */ s16 field_0x2DC;
        /* 0x2DE */ s16 field_0x2DE;

        /* 0x2E0 */ u8 field_0x2E0[0x16C];

        /* 0x44C */ dPa_followEcallBack mFirePa;
        /* 0x460 */ s16 mFireAngle;
        /* 0x462 */ s16 mFireRotX;
        /* 0x464 */ u8 mFireAlpha;
        /* 0x465 */ u8 field_0x465[0x3];
        /* 0x468 */ f32 mFireScale;
        /* 0x46C */ Mtx mFireMtx;

        /* 0x49C */ s16 mEvent;
        /* 0x49E */ s16 mEventFlag;
        /* 0x4A0 */ s16 field_0x4A0;
        /* 0x4A2 */ u8 field_0x4A2[0xA];
    };
};

#endif /* D_A_OBJ_LIGHT_H */
