#ifndef D_A_TAG_EVSW_H
#define D_A_TAG_EVSW_H

#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"

namespace daTagEvsw {
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 0,
            
            PRM_EVENTBITID_W = 16,
            PRM_EVENTBITID_S = 8,
            
            PRM_TYPE_W = 2,
            PRM_TYPE_S = 24,
        };

        int prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        u16 prm_get_eventbitID() const { return daObj::PrmAbstract(this, PRM_EVENTBITID_W, PRM_EVENTBITID_S); }
        u16 prm_get_Type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
    
        cPhs_State _create();
        bool _delete();
        bool _execute();
        bool _draw();
    
    public:
        /* 0x290 */ u8 m290[0x29C - 0x290];
        /* 0x29C */ dCcD_Stts mStts;
        /* 0x2D8 */ dCcD_Cyl mCyl;
    };
};

#endif /* D_A_TAG_EVSW_H */
