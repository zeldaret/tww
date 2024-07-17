#ifndef D_A_OBJ_TIMER_H
#define D_A_OBJ_TIMER_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"

namespace daObjTimer {
    class Act_c : public fopAc_ac_c {
    public:
        typedef void (Act_c::*ModeFunc)();

        enum Mode_e {
            Mode_WAIT_e,
            Mode_COUNT_e,
        };

        enum Prm_e {
            PRM_TIME_W   = 0x08,
            PRM_TIME_S   = 0x00,

            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x10,
        };

        s32 prm_get_swSave() const { return daObj::PrmAbstract<Prm_e>(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_time() const { return daObj::PrmAbstract<Prm_e>(this, PRM_TIME_W, PRM_TIME_S); }
        void stopTimer() { mIsStop = true;}

        s32 _create();
        bool _delete();
        void mode_wait_init();
        void mode_wait();
        void mode_count_init();
        void mode_count();
        bool _execute();

    public:
        /* 0x290 */ Mode_e mMode;
        /* 0x294 */ s32 mTimer;
        /* 0x298 */ bool mIsStop;
    };
};

#endif /* D_A_OBJ_TIMER_H */
