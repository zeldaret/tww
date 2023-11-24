#ifndef D_A_TAG_VOLCANO_H
#define D_A_TAG_VOLCANO_H

#include "f_op/f_op_actor.h"

namespace daTagvolcano {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_bitTRB() const {}
        void prm_get_swSave() const {}
        void prm_get_timer() const {}
        void prm_get_type() const {}
    
        void _create();
        void check_timer_clear();
        void _delete();
        void _execute();
        void _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_TAG_VOLCANO_H */
