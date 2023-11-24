#ifndef D_A_OBJ_HLIFT_H
#define D_A_OBJ_HLIFT_H

#include "f_op/f_op_actor.h"

namespace daObjHlift {
    class Act_c : public fopAc_ac_c {
    public:
        void prm_get_dist() const {}
        void prm_get_evId() const {}
        void prm_get_size() const {}
        void prm_get_swSave() const {}
    
        void CreateHeap();
        s32 Create();
        void Mthd_Create();
        BOOL Delete();
        void Mthd_Delete();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_demoreq_init(daObjHlift::Act_c::Mode_e);
        void mode_demoreq();
        void set_mtx();
        void init_mtx();
        void rot_set();
        void vib_set();
        void vib_proc();
        void chk_demo_end();
        void se_whole();
        void Execute(float(**)[3][4]);
        BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_HLIFT_H */
