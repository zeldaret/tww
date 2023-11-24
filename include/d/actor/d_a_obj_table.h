#ifndef D_A_OBJ_TABLE_H
#define D_A_OBJ_TABLE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"
#include "SSystem/SComponent/c_phase.h"

namespace daObjTable {
    class Act_c : public fopAc_ac_c {
    public:
        void CreateHeap();
        void Create();
        void Mthd_Create();
        void Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void Execute(float(**)[3][4]);
        void Draw();
    
    public:
        /* 0x000 */ dBgS_MoveBgActor parent;
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
    };
};

#endif /* D_A_OBJ_TABLE_H */
