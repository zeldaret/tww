#ifndef D_A_TAG_EVSW_H
#define D_A_TAG_EVSW_H

#include "f_op/f_op_actor.h"

namespace daTagEvsw {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_Type() const {}
        void prm_get_eventbitID() const {}
        void prm_get_swSave() const {}
    
        s32 _create();
        BOOL _delete();
        BOOL _execute();
        BOOL _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_TAG_EVSW_H */
