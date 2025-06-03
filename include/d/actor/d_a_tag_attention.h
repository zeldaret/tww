#ifndef D_A_TAG_ATTENTION_H
#define D_A_TAG_ATTENTION_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"

namespace daTagAttention {
    class Act_c : public fopAc_ac_c {
    public:
        bool chk_inside(cXyz*) const;
        int prm_get_Type() const 
        {
            return daObj::PrmAbstract(this, PRM_1_W, PRM_1_S);
        }

        int prm_get_swSave() const 
        {
            return daObj::PrmAbstract(this, PRM_2_W, PRM_2_S);
        }
    
        cPhs_State _create();
        bool _execute();

        enum Prm_e {
            PRM_1_W = 0x02,
            PRM_1_S = 0x08,
            PRM_2_W = 0x08,
            PRM_2_S = 0x00,
        };

    public:
        /* Place member variables here */
        /* 0x290 */ bool m_b0x290;
        /* padding */ s8 mPad[8];
        /* 0x2B8 */ dCcD_Stts mStts;
        /* 0x2D8 */ dCcD_Sph mSph;
    };
};

#endif /* D_A_TAG_ATTENTION_H */
