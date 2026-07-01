#ifndef D_A_OBJ_ITNAK_H
#define D_A_OBJ_ITNAK_H

#include "cstdint.h"
#include "d/d_bg_s_gnd_chk.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/types.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_bg_s_gnd_chk.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_a_obj.h"

namespace daObjItnak {

    struct Unknown_Struct_0x290;

    enum Prm_e {
        PRM_VISIBLE_W = 0x8,
        PRM_VISIBLE_S = 0x0,
        PRM_SWBIT_W = 0x8,
        PRM_SWBIT_S = 0x8,
    };

    class Act_c : public fopAc_ac_c {
    public:
        void is_switch() const {}
        void param_get_arg0() const {}
        s32 param_get_swbit() const {
            return daObj::PrmAbstract<int>(this, PRM_SWBIT_W, PRM_SWBIT_S);
        }
    
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        void set_co_se(dCcD_Cyl*);
        void manage_draw_flag();
        void set_collision();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x290 */ Unknown_Struct_0x290* field_0x290;
        /* 0x294 */ request_of_phase_process_class mPhase;
        /* 0x29C */ J3DModel* mModel;
        /* 0x2A0 */ Mtx mMtx;
        /* 0x2D0 */ unsigned long mId;
        /* 0x2D4 */ dBgS_ObjGndChk mGndChk;
        /* 0x328 */ f32 mGroundY;
        /* 0x32C */ dCcD_Stts mStts0; // Body? TN_MAIN1
        /* 0x368 */ dCcD_Cyl mCyl0;   // Body? TN_MAIN1
        /* 0x498 */ dCcD_Stts mStts1; // Shield? TN_TATE1
        /* 0x4D4 */ dCcD_Cyl mCyl1;   // Shield? TN_TATE1
        /* 0x604 */ dCcD_Stts mStts2; // Sword? TN_KEN1
        /* 0x640 */ dCcD_Cyl mCyl2;   // Sword? TN_KEN1
        /* 0x770 */ BOOL mDrawMode;
        /* 0x774 */ BOOL mVisible;
    };
};

#endif /* D_A_OBJ_ITNAK_H */
