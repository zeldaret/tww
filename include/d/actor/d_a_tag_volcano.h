#ifndef D_A_TAG_VOLCANO_H
#define D_A_TAG_VOLCANO_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"

namespace daTagvolcano {
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_TRB_W = 0x06,
            PRM_TRB_S = 0x00,
            PRM_TYPE_W = 0x02,
            PRM_TYPE_S = 0x06,
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x08,
            PRM_TIMER_W = 0x08,
            PRM_TIMER_S = 0x10,
        };

        u32 prm_get_bitTRB() const { return daObj::PrmAbstract<Prm_e>(this, PRM_TRB_W, PRM_TRB_S); }
        u32 prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        u32 prm_get_timer() const { return daObj::PrmAbstract<Prm_e>(this, PRM_TIMER_W, PRM_TIMER_S); }
        u32 prm_get_type() const { return daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S); }
    
        cPhs_State _create();
        bool check_timer_clear();
        bool _delete();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x290 */ u32 field_0x290;
        /* 0x294 */ u32 field_0x294;
        /* 0x298 */ u8 field_0x298;
        /* 0x299 */ u8 field_0x299;
        /* 0x29C */ s32 mType;
        /* 0x2A0 */ s32 field_0x2a0;
        /* 0x2A4 */ u8 field_0x2a4;
    };
};

#endif /* D_A_TAG_VOLCANO_H */
