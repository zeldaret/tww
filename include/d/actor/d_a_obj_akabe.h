#ifndef D_A_OBJ_AKABE_H
#define D_A_OBJ_AKABE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_a_obj.h"

namespace daObjAkabe {
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 0,

            PRM_SCL_W = 2,
            PRM_SCL_S = 8,

            PRM_ALWAYS_W = 1,
            PRM_ALWAYS_S = 12,

            PRM_ARG0_W = 4,
            PRM_ARG0_S = 16,
        };

        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_scl() const { return daObj::PrmAbstract(this, PRM_SCL_W, PRM_SCL_S); }
        s32 prm_get_always() const { return daObj::PrmAbstract(this, PRM_ALWAYS_W, PRM_ALWAYS_S); }
        s32 prm_get_arg0() const { return daObj::PrmAbstract(this, PRM_ARG0_W, PRM_ARG0_S); }
    
        s32 _create();
        u8 create_heap();
        bool _delete();
        void init_scale();
        void init_mtx();
        bool chk_appear();
        bool _execute();
        bool _draw();

        static BOOL solidHeapCB(fopAc_ac_c*);
        static const char* const M_arcname[4];

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ dBgW* mpBgW;
        /* 0x29C */ Mtx mMtx;
        /* 0x2CC */ s32 mType;
        /* 0x2D0 */ u8 mbAppear;
    };
};

#endif /* D_A_OBJ_AKABE_H */
