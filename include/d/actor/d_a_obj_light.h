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
namespace daObjLight {
    class Act_c : public fopAc_ac_c {
    static const dCcD_SrcCyl M_cyl_src;
    static const char M_arcname[];
    public:
        void solidHeapCB(fopAc_ac_c*);
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

public:
    /* 0x10C */ dKy_tevstr_c tevStr;
    /* 0x290 */ u8 field_0x290[0x14];
    /* 0x2A4 */ dBgW* mpBgW;
    /* 0x2A8 */ u8 field_0x2A8[0x36];
    /* 0x2DE */ s16 field_0x2DE;
    /* 0x2E0 */ u8 field_0x2E0[0x16C];
    /* 0x298 */ J3DModel* mpModel;
    /* 0x44C */ dPa_followEcallBack mFirePa;
    /* 0x460 */ s16 mFireAngle;
    /* 0x462 */ s16 mFireRotX;
    /* 0x464 */ u8 mFireAlpha;
    /* 0x465 */ u8 field_0x465[0x3];
    /* 0x468 */ f32 mFireScale;
    /* 0x46C */ Mtx mFireMtx;
    /* 0x49C */ s16 mEvent;
    /* 0x49E */ s16 mEventFlag;
    /* 0x4A0 */ cXyz mLightPos;
    };
};

#endif /* D_A_OBJ_LIGHT_H */
