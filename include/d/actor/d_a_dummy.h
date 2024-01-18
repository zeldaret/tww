#ifndef D_A_DUMMY_H
#define D_A_DUMMY_H

#include "f_op/f_op_actor.h"

namespace daDummy {
    class Act_c : public fopAc_ac_c {
    public:
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        s32 _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();

        virtual ~Act_c();

    public:
        /* Place member variables here */
        /* 0x290 */ // vtable
        /* 0x294 */ u8 field_0x294[0x29c - 0x294];
        /* 0x29c */ Mtx field_0x29c;
    };
};

#endif /* D_A_DUMMY_H */
