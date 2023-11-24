#ifndef D_A_OBJ_HOMEN_H
#define D_A_OBJ_HOMEN_H

#include "f_op/f_op_actor.h"

namespace daObjHomen {
    class Act_c : public fopAc_ac_c {
    public:
        void is_switch() const {}
        void on_switch() const {}
        void param_get_arg0() const {}
        void param_get_enemy() const {}
        void param_get_item() const {}
        void param_get_itembit() const {}
        void param_get_sw() const {}
    
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        s32 _create();
        BOOL _delete();
        void set_mtx();
        void init_mtx();
        void exe_event();
        void make_enemy();
        void make_item();
        void manage_item_timer();
        void manage_enemy_timer();
        void get_norse_offset(cXyz*, int);
        void get_norse_point(cXyz*, int);
        void process_free_init();
        void process_free_main();
        void process_wait_falldown_init();
        void process_wait_falldown_main();
        void process_falldown_init();
        void process_falldown_main();
        void process_wait_init();
        void process_wait_main();
        void process_none_init();
        void process_none_main();
        void process_init(short);
        void process_main();
        void set_co_collision();
        void set_at_collision();
        void adjust_hookshot();
        BOOL _execute();
        BOOL _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_HOMEN_H */
