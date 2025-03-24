#ifndef D_A_DUMMY_H
#define D_A_DUMMY_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

namespace daDummy {
    class Act_c : public fopAc_ac_c {
    public:
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();

        virtual ~Act_c() {}

    public:
        /* 0x290 */ // vtable
        /* 0x294 */ request_of_phase_process_class mPhase; // Unused
        /* 0x29c */ Mtx mMtx;
    };
};

#endif /* D_A_DUMMY_H */
