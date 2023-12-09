#ifndef D_A_OBJ_TABLE_H
#define D_A_OBJ_TABLE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"
#include "SSystem/SComponent/c_phase.h"

namespace daObjTable {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_mdl() const {}
    
        int CreateHeap();
        int Create();
        void Mthd_Create();
        BOOL Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        int Execute(float(**)[3][4]);
        BOOL Draw();
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
    };
};

#endif /* D_A_OBJ_TABLE_H */
