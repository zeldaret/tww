#ifndef D_A_OBJ_VFAN_H
#define D_A_OBJ_VFAN_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_movebg_actor.h"
#include "SSystem/SComponent/c_phase.h"

namespace daObjVfan {
    class Act_c : public dBgS_MoveBgActor {
    public:
        void prm_get_swSave() const {}
    
        int CreateHeap();
        int Create();
        void Mthd_Create();
        BOOL Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void ParticleSet();
        int Execute(float(**)[3][4]);
        BOOL Draw();
    
    public:
        /* 0x2C8 */ request_of_phase_process_class mPhs;
        /* 0x2D0 */ J3DModel* mpModel;
        /* 0x2D4 */ dCcD_Stts mStts;
        /* 0x310 */ dCcD_Cyl mCyl;
        /* 0x440 */ int mSwitchNo;
        /* 0x444 */ u8 m444;
        /* 0x445 */ u8 m445[0x448 - 0x445];
        /* 0x448 */ int m448;
    };
};

#endif /* D_A_OBJ_VFAN_H */
