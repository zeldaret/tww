#ifndef D_A_OBJ_MSDAN_H
#define D_A_OBJ_MSDAN_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

namespace daObjMsdan {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_evId() const {}
        void prm_get_size() const {}
        void prm_get_sound() const {}
        void prm_get_swSave() const {}

        cPhs_State Mthd_Create();
        BOOL Mthd_Execute();
        BOOL Mthd_Delete();

    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
    };
};

#endif /* D_A_OBJ_MSDAN_H */
