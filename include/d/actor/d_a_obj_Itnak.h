#ifndef D_A_OBJ_ITNAK_H
#define D_A_OBJ_ITNAK_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_cc_d.h"

class J3DModel;

namespace daObjItnak {
    class Act_c : public fopAc_ac_c {
    public:
        bool is_switch() const { return fopAcM_isSwitch((fopAc_ac_c*)this, param_get_swbit()); }
        int param_get_arg0() const { return daObj::PrmAbstract<int>(this, 8, 0); }
        int param_get_swbit() const { return daObj::PrmAbstract<int>(this, 8, 8); }

        virtual ~Act_c() {}

        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        BOOL set_co_se(dCcD_Cyl*);
        void manage_draw_flag();
        void set_collision();
        bool _execute();
        bool _draw();

        static const char M_arcname[];

    public:
        /* 0x290 */ /* vtable */
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ J3DModel* mpModel;
        /* 0x2A0 */ Mtx mMtx;
        /* 0x2D0 */ u32 mShadowId;
        /* 0x2D4 */ dBgS_ObjGndChk mGndChk;
        /* 0x328 */ f32 mGroundY;
        /* 0x32C */ dCcD_Stts mStts0;
        /* 0x368 */ dCcD_Cyl mCyl0;
        /* 0x498 */ dCcD_Stts mStts1;
        /* 0x4D4 */ dCcD_Cyl mCyl1;
        /* 0x604 */ dCcD_Stts mStts2;
        /* 0x640 */ dCcD_Cyl mCyl2;
        /* 0x770 */ int mArg0;
        /* 0x774 */ int mDrawFlag;
    };  // Size: 0x778
};

#endif /* D_A_OBJ_ITNAK_H */
