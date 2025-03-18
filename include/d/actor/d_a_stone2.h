#ifndef D_A_STONE2_H
#define D_A_STONE2_H

#include "d/d_bg_s_movebg_actor.h"

namespace daStone2 {
    class Act_c : public dBgS_MoveBgActor {
    public:
        Act_c();
        
        void attr() {}
        void prmZ_get_evId() const {}
        void prm_get_cull() const {}
        void prm_get_itemNo() const {}
        void prm_get_itemSave() const {}
        void prm_get_shadow() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}
    
        void prmZ_init();
        void is_switch() const;
        void on_switch() const;
        virtual BOOL CreateHeap();
        virtual BOOL Create();
        void chk_appear();
        cPhs_State Mthd_Create();
        virtual BOOL Delete();
        BOOL Mthd_Delete();
        void set_mtx();
        void init_mtx();
        void cull_set_draw();
        void cull_set_move();
        void damaged(int);
        void damage_cc_proc();
        void damage_bg_proc();
        void damage_bg_proc_directly();
        void eff_m_break(unsigned short, unsigned short);
        void eff_b_break(unsigned short);
        void eff_break_ebrock();
        void eff_break_ekao();
        void eff_break_ebrock2();
        void eff_lift_smoke_start();
        void eff_lift_smoke_end();
        void eff_lift_smoke_remove();
        void set_senv(int, int) const;
        void cam_lockoff() const;
        void mode_wait_init();
        void mode_wait();
        void mode_carry_init();
        void mode_carry();
        void mode_drop_init();
        void mode_drop();
        void mode_fine_init();
        void mode_fine();
        void mode_proc_call();
        void demo_non_init();
        void demo_non();
        void demo_req_init();
        void demo_req();
        void demo_run_init();
        void demo_run();
        void demo_proc_call();
        virtual BOOL Execute(Mtx**);
        void draw_shadow();
        virtual BOOL Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_STONE2_H */
