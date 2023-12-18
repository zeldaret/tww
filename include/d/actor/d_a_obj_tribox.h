#ifndef D_A_OBJ_TRIBOX_H
#define D_A_OBJ_TRIBOX_H

#include "f_op/f_op_actor.h"
#include "d/d_bg_w.h"

namespace daObjTribox {
    class Act_c : public fopAc_ac_c {
    public:
        void is_switch() const {}
        void on_switch() const {}
        void prm_get_swSave() const {}
        void prm_get_type() const {}
    
        void set_state();
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void block_init();
        void chk_light() const;
        void correct_before_init();
        void correct_after_init();
        void controll_set();
        void controll_clear();
        void create_block_before();
        void create_block_after();
        void create_correct_before();
        void create_correct_after();
        s32 _create();
        BOOL _delete();
        void set_mtx();
        void init_mtx();
        void push_pullCB(fopAc_ac_c*, fopAc_ac_c*, short, dBgW::PushPullLabel);
        void line_cross(const cXyz*, const cXyz*) const;
        void chk_wall(int) const;
        void chk_space() const;
        void eff_flash();
        void eff_smoke_start();
        void eff_smoke_pos();
        void eff_smoke_end();
        void eff_smoke_remove();
        void eff_sink_smoke_init();
        void eff_sink_smoke_start();
        void eff_sink_smoke_end();
        void eff_sink_smoke_remove();
        void vib_sink_init();
        void vib_sink_start();
        void vib_sink_end();
        void search_block(void*, void*);
        void sound_pos_init();
        void sound_pos_delete();
        void sound_get_mapinfo(const cXyz&);
        void sound_sink_down_block();
        void sound_sink_stop_block();
        void sound_flash_shine();
        void sound_flash_light();
        void mode_block_wait_init();
        void mode_block_wait();
        void mode_block_walk_init();
        void mode_block_walk();
        void mode_block_sink_init();
        void mode_block_sink();
        void mode_block_lower_init();
        void mode_block_lower();
        void mode_correct_off_init();
        void mode_correct_off();
        void mode_correct_on_init();
        void mode_correct_on();
        void mode_correct_demoreq_init();
        void mode_correct_demoreq();
        void mode_correct_demorun_init();
        void mode_correct_demorun();
        void mode_correct_end_init();
        void mode_correct_end();
        void mode_correct_dummy_init();
        void mode_correct_dummy();
        void mode_proc_call();
        void execute_block();
        void execute_correct();
        BOOL _execute();
        BOOL _draw();

        static void reset();

        static cXyz M_sound_pos;
        static int M_correct_cnt;
        static bool M_correct_flag;
        static int M_b_cont_cnt;
        static int M_c_cont_cnt;
        static u8 M_sink_start;

    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_TRIBOX_H */
