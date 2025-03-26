#ifndef D_A_OBJ_MONUMENT_H
#define D_A_OBJ_MONUMENT_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "d/d_a_obj.h"

namespace daObjMonument {
    namespace {
        enum Type_e {
            ONE_e,
            TWO_e,
        };

        struct Attr_c {
            /* 0x00 */ s16 mModelId;
            /* 0x01 */ s16 mBgWId;
        };
    }

    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_TYPE_W = 0x01,
            PRM_TYPE_S = 0x00,

            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x08,
        };

        static BOOL solidHeapCB(fopAc_ac_c *i_this);
        static const char M_arcname[6];

        Type_e prm_get_type() const { return (Type_e)daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S); }
        u32 prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }

        cPhs_State _create();
        bool _execute();
        bool _draw();
        bool _delete();
        bool create_heap();
        void init_mtx();
        void set_mtx();

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel * mpModel;
        /* 0x29C */ Type_e mType;
        /* 0x2A0 */ dBgW * mpBgW;
        /* 0x2A4 */ Mtx mtx;
    };
};

#endif /* D_A_OBJ_MONUMENT_H */
