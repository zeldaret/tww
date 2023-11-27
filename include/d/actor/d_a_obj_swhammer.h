#ifndef D_A_OBJ_SWHAMMER_H
#define D_A_OBJ_SWHAMMER_H

#include "f_op/f_op_actor.h"

class J3DNode;

namespace daObjSwhammer {
    class Act_c : public fopAc_ac_c {
    public:
        void is_switch() const {}
        void off_switch2() const {}
        void on_switch() const {}
        void prm_get_swSave() const {}
        void prm_get_swSave2() const {}
    
        void CreateHeap();
        s32 Create();
        s32 _create();
        BOOL Delete();
        BOOL _delete();
        void set_mtx();
        void init_mtx();
        void set_damage();
        void vib_start(short, float);
        void vib_proc();
        void crush_start();
        void crush_proc();
        void eff_crush();
        void calc_top_pos();
        void jnodeCB(J3DNode*, int);
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void Execute(float(**)[3][4]);
        BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_SWHAMMER_H */
