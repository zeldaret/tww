#ifndef D_A_OBJ_GASHIP_H
#define D_A_OBJ_GASHIP_H

#include "f_op/f_op_actor.h"
#include "SSystem/SComponent/c_phase.h"

namespace daObjGaship {
    class Act_c : public fopAc_ac_c {
    public:
        virtual ~Act_c() {}
        void birth_flag();
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        void set_mtx();
        bool _execute();
        bool _draw();

        static const char M_arcname[];

    public:
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ J3DModel* mModel;
        /* 0x2A0 */ Mtx mtx;
        /* 0x2D0 */ bool birthFlag[2];
    };
};

#endif /* D_A_OBJ_GASHIP_H */
