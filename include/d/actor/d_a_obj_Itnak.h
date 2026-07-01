#ifndef D_A_OBJ_ITNAK_H
#define D_A_OBJ_ITNAK_H

#include "cstdint.h"
#include "d/d_bg_s_gnd_chk.h"
#include "dolphin/types.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_bg_s_gnd_chk.h"
#include "d/d_bg_s_gnd_chk.h"

namespace daObjItnak {

    struct Unknown_Struct_0x290;

    class Act_c : public fopAc_ac_c {
    public:
        void is_switch() const {}
        void param_get_arg0() const {}
        void param_get_swbit() const {}
    
        BOOL solidHeapCB(fopAc_ac_c*);
        BOOL create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        void set_co_se(dCcD_Cyl*);
        void manage_draw_flag();
        void set_collision();
        bool _execute();
        bool _draw();

        static const char M_arcname[];
    
    public:
        /* 0x290 */ Unknown_Struct_0x290* field_0x290;
        /* 0x294 */ request_of_phase_process_class mPhase;
        /* 0x29C */ J3DModel* mModel;
        /* 0x2A0 */ f32 field_0x2a0[3][4];
        /* 0x2D0 */ unsigned long mId;
        /* 0x2D4 */ dBgS_ObjGndChk mFloorPoly;
        /* 0x328 */ f32 mGroundY;
        /* 0x32C */ dCcD_Stts field_0x32c;
        /* 0x368 */ dCcD_Cyl field_0x368;
        /* 0x498 */ dCcD_Stts field_0x498;
        /* 0x4D4 */ dCcD_Cyl field_0x4d4;
        /* 0x604 */ dCcD_Stts field_0x604;
        /* 0x640 */ dCcD_Cyl field_0x640;
        /* 0x770 */ BOOL mDrawMode;
        /* 0x774 */ BOOL mVisible;
    };
};

#endif /* D_A_OBJ_ITNAK_H */
