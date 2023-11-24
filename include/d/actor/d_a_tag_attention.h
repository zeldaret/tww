#ifndef D_A_TAG_ATTENTION_H
#define D_A_TAG_ATTENTION_H

#include "f_op/f_op_actor.h"

namespace daTagAttention {
    class Act_c : public fopAc_ac_c {
    public:
        void chk_inside(cXyz*) const {}
        void prm_get_Type() const {}
        void prm_get_swSave() const {}
    
        s32 _create();
        BOOL _execute();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_TAG_ATTENTION_H */
