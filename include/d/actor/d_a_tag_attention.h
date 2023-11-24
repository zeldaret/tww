#ifndef D_A_TAG_ATTENTION_H
#define D_A_TAG_ATTENTION_H

#include "f_op/f_op_actor.h"

namespace daTagAttention {
    class Act_c : public fopAc_ac_c {
    public:
        void _create();
        void _execute();
        void chk_inside(cXyz*) const;
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_TAG_ATTENTION_H */
