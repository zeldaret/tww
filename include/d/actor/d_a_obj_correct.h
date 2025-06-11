#ifndef D_A_OBJ_CORRECT_H
#define D_A_OBJ_CORRECT_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"
#include "d/actor/d_a_obj_try.h"

namespace daObjCorrect {
    enum Type_e {
        UNK_4 = 4,
        UNK_5 = 5,
    };

    class Act_c : public fopAc_ac_c {
    public:
        typedef void(Act_c::*ModeProcFunc)();
        typedef void(Act_c::*DemoProcFunc)();

        enum Prm_e {
            PRM_EV_ID_S = 0x10,
            PRM_EV_ID_W = 8,

            PRM_SWSAVE_S = 8,
            PRM_SWSAVE_W = 8,

            PRM_TYPE_S = 0,
            PRM_TYPE_W = 4,
        };

        u8 prm_get_evId() const {
            return daObj::PrmAbstract(this, PRM_EV_ID_W, PRM_EV_ID_S);
        }
        int prm_get_swSave() const {
            return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S);
        }
        int prm_get_type() const {
            return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S);
        }
    
        cPhs_State _create();
        bool _delete();
        static daObjTry::Act_c* chk_try_actor0(fopAc_ac_c*);
        void* chk_try_actor1(daObjTry::Act_c*, daObjTry::Type_e, float) const;
        void* chk_try_actor2(daObjTry::Act_c*, daObjTry::Type_e, bool, float, float) const;
        static void* search_movebox(void*, void*);
        static void* search_tryColSun(void*, void*);
        static void* search_tryColMer(void*, void*);
        static void* search_tryColJup(void*, void*);
        static void* search_tryKeyGate(void*, void*);
        static void* search_tryKeyDoor(void*, void*);
        static void* search_tryColGreen(void*, void*);
        static void* search_tryColBlue(void*, void*);
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

        const static fopAcIt_JudgeFunc M_search_proc[];
    
    public:
        /* 0x290 */ s16 field_0x290;
        /* 0x294 */ s32 field_0x294;
        /* 0x298 */ s32 field_0x298;
        /* 0x29C */ Type_e mType;
        /* 0x2A0 */ s16 mEventIdx;
        /* 0x2A4 */ f32 field_0x2A4;
    };  // Size: 0x2A8

    STATIC_ASSERT(sizeof(Act_c) == 0x2A8);

} // namespace daObjCorrect

#endif /* D_A_OBJ_CORRECT_H */
