#ifndef D_A_OBJ_TABLE_H
#define D_A_OBJ_TABLE_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"
#include "d/d_bg_s_movebg_actor.h"
#include "SSystem/SComponent/c_phase.h"

namespace daObjTable {
    class Act_c : public dBgS_MoveBgActor {
    public:
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        virtual BOOL Execute(Mtx**);
        virtual BOOL Draw();
        
        u8 prm_get_mdl() const { return daObj::PrmAbstract(this, PRM_MDL_W, PRM_MDL_S); }
        static Mtx M_tmp_mtx;
        static const char M_arcname[6];
        enum Prm_e {
            PRM_MDL_W = 8,
            PRM_MDL_S = 0,
        };

    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
    };
};

#endif /* D_A_OBJ_TABLE_H */
