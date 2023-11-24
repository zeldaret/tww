#ifndef D_A_OBJ_OSPBOX_H
#define D_A_OBJ_OSPBOX_H

#include "f_op/f_op_actor.h"

namespace daObjOspbox {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_itemNo() const {}
        void prm_get_spec() const {}
    
        void CreateHeap();
        void Create();
        void Mthd_Create();
        void Delete();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void make_item();
        void eff_break();
        void sound_break();
        void set_ground();
        void init_ground();
        void Execute(float(**)[3][4]);
        void Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_OSPBOX_H */
