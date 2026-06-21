#ifndef D_A_TAG_WATERLEVEL_H
#define D_A_TAG_WATERLEVEL_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"

namespace daTagWaterlevel {
    enum State_e {
        STATE_1 = 1,
        STATE_2 = 2,
        STATE_4 = 4,
    };
    
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_SCH_W = 8,
            PRM_SCH_S = 0,
        };


        static f32 get_now() { return M_now; }
        static State_e get_state() { return M_state; }
        inline u8 prm_get_sch() const { return daObj::PrmAbstract(this, PRM_SCH_W, PRM_SCH_S); }
    
        cPhs_State _create();
        bool _delete();
        void bgm_proc();
        bool _execute();
        bool _draw();

        static State_e M_state;
        static f32 M_now;

    public:
        /* 0x290 */ f32 field_0x290;
        /* 0x294 */ s32 mAction;
    };
};

#endif /* D_A_TAG_WATERLEVEL_H */
