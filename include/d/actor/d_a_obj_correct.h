#ifndef D_A_OBJ_CORRECT_H
#define D_A_OBJ_CORRECT_H

#include "f_op/f_op_actor.h"
#include "d/actor/d_a_obj_try.h"

namespace daObjCorrect {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_evId() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}
    
        s32 _create();
        bool _delete();
        void chk_try_actor0(fopAc_ac_c*);
        void chk_try_actor1(daObjTry::Act_c*, daObjTry::Type_e, float) const;
        void chk_try_actor2(daObjTry::Act_c*, daObjTry::Type_e, bool, float, float) const;
        void search_movebox(void*, void*);
        void search_tryColSun(void*, void*);
        void search_tryColMer(void*, void*);
        void search_tryColJup(void*, void*);
        void search_tryKeyGate(void*, void*);
        void search_tryKeyDoor(void*, void*);
        void search_tryColGreen(void*, void*);
        void search_tryColBlue(void*, void*);
        void mode_off_init();
        void mode_off();
        void mode_on_init();
        void mode_on();
        void demo_non_init();
        void demo_non();
        void demo_req_init();
        void demo_req();
        void demo_run_init();
        void demo_run();
        bool _execute();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_CORRECT_H */
