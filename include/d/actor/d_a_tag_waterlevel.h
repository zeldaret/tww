#ifndef D_A_TAG_WATERLEVEL_H
#define D_A_TAG_WATERLEVEL_H

#include "f_op/f_op_actor.h"

namespace daTagWaterlevel {
    class Act_c : public fopAc_ac_c {
    public:
        void get_now() {}
        void get_state() {}
    
        void _create();
        void _delete();
        void bgm_proc();
        void _execute();
        void _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_TAG_WATERLEVEL_H */
