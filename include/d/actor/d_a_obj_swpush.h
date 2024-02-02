#ifndef D_A_OBJ_SWPUSH_H
#define D_A_OBJ_SWPUSH_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

class J3DNode;

namespace daObjSwpush {
    class Act_c : public fopAc_ac_c {
    public:
        void attr() const {}
        void is_switch() const {}
        void off_switch() const {}
        void on_switch() const {}
        void prmZ_get_swSave2() const {}
        void prm_get_evId() const {}
        void prm_get_mdl() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}
        void prm_get_version() const {}
        void rev_switch() const {}
    
        void prmZ_init();
        void is_switch2() const;
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void create_res_load();
        void Mthd_Create();
        void Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void set_btp_frame();
        void rideCB(dBgW*, fopAc_ac_c*, fopAc_ac_c*);
        static BOOL jnodeCB(J3DNode*, int);
        void calc_top_pos();
        void top_bg_aim_req(float, short);
        void set_push_flag();
        void mode_upper_init();
        void mode_upper();
        void mode_u_l_init();
        void mode_u_l();
        void mode_lower_init();
        void mode_lower();
        void mode_l_u_init();
        void mode_l_u();
        void demo_non_init();
        void demo_non();
        void demo_reqPause_init();
        void demo_reqPause();
        void demo_runPause_init();
        void demo_runPause();
        void demo_stop_puase();
        void demo_reqSw_init();
        void demo_reqSw();
        void demo_runSw_init();
        void demo_runSw();
        void Mthd_Execute();
        void Mthd_Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_SWPUSH_H */
