#ifndef D_A_OBJ_LADDER_H
#define D_A_OBJ_LADDER_H

#include "f_op/f_op_actor.h"

namespace daObjLadder {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_evId() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}
    
        void CreateHeap();
        s32 Create();
        void Mthd_Create();
        BOOL Delete();
        void Mthd_Delete();
        void demo_end_reset();
        void mode_wait_init();
        void mode_wait();
        void mode_demoreq_init();
        void mode_demoreq();
        void mode_vib_init();
        void mode_vib();
        void mode_drop_init();
        void mode_drop();
        void mode_fell_init();
        void mode_fell();
        void set_mtx();
        void init_mtx();
        void Execute(float(**)[3][4]);
        BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_LADDER_H */
