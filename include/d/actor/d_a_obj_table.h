#ifndef D_A_OBJ_TABLE_H
#define D_A_OBJ_TABLE_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"
#include "SSystem/SComponent/c_phase.h"

namespace daObjTable {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_mdl() const {}
    
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
    };
};

#endif /* D_A_OBJ_TABLE_H */
