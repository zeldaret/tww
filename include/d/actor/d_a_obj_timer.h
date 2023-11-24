#ifndef D_A_OBJ_TIMER_H
#define D_A_OBJ_TIMER_H

#include "f_op/f_op_actor.h"

namespace daObjTimer {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_swSave() const {}
        void prm_get_time() const {}
        void stopTimer() {}
    
        s32 _create();
        BOOL _delete();
        void mode_wait_init();
        void mode_wait();
        void mode_count_init();
        void mode_count();
        BOOL _execute();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_TIMER_H */
