#ifndef D_A_STONE2_H
#define D_A_STONE2_H

#include "f_op/f_op_actor.h"

namespace daStone2 {
    class Act_c : public fopAc_ac_c {
    public:
        void attr() {}
    
        void prmZ_init();
        void is_switch() const;
        void on_switch() const;
        void CreateHeap();
        void Create();
        void chk_appear();
        void Mthd_Create();
        void Delete();
        void Mthd_Delete();
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
        void Execute(float(**)[3][4]);
        void draw_shadow();
        void Draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_STONE2_H */
