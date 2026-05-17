#ifndef D_A_OBJ_ITNAK_H
#define D_A_OBJ_ITNAK_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_gnd_chk.h"

namespace daObjItnak {
    class Act_c : public fopAc_ac_c {
    public:
        struct Attr_c {
            /* 0x00 */ f32 m00;
            /* 0x04 */ f32 m04;
            /* 0x08 */ f32 m08;
            /* 0x0C */ f32 m0C;
            /* 0x10 */ f32 m10;
            /* 0x14 */ f32 m14;
            /* 0x18 */ f32 m18;
            /* 0x1C */ f32 m1C;
            /* 0x20 */ f32 m20;
            /* 0x24 */ f32 m24;
            /* 0x28 */ f32 m28;
            /* 0x2C */ f32 m2C;
        }; // size = 0x30 (12 f32, verified from orig .rodata)

        bool is_switch() const {
            return fopAcM_isSwitch(const_cast<Act_c*>(this), param_get_swbit());
        }
        void param_get_arg0() const {}
        s32 param_get_swbit() const {
            return daObj::PrmAbstract(this, 8, 8);
        }

        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        int set_co_se(dCcD_Cyl*);
        void manage_draw_flag();
        void set_collision();
        bool _execute();
        bool _draw();

        static const char M_arcname[];

    public:
        /* 0x290 */ u8 field_0x290[0x294 - 0x290];
        /* 0x294 */ request_of_phase_process_class mPhase;
        /* 0x29C */ J3DModel* mpModel;
        /* 0x2A0 */ Mtx mMtx;
        /* 0x2D0 */ u32 mShadowId;
        /* 0x2D4 */ dBgS_ObjGndChk mGndChk;
        /* 0x328 */ f32 mGroundY;
        /* 0x32C */ dCcD_Stts mStts1;
        /* 0x368 */ dCcD_Cyl mCyl1;
        /* 0x498 */ dCcD_Stts mStts2;
        /* 0x4D4 */ dCcD_Cyl mCyl2;
        /* 0x604 */ dCcD_Stts mStts3;
        /* 0x640 */ dCcD_Cyl mCyl3;
        /* 0x770 */ s32 mType;
        /* 0x774 */ s32 mDrawFlag;
    };
};

#endif /* D_A_OBJ_ITNAK_H */
