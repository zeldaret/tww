#ifndef D_A_OBJ_ESKBAN_H
#define D_A_OBJ_ESKBAN_H

#include "f_op/f_op_actor.h"

namespace daObjEskban {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_swSave() const {}
    
        void CreateHeap();
        s32 Create();
        void Mthd_Create();
        BOOL Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void eff_m_break(unsigned short, unsigned short);
        void eff_b_break(unsigned short);
        void daObjEskban_effect_set();
        void Execute(float(**)[3][4]);
        BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_ESKBAN_H */
