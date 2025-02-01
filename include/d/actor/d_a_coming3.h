#ifndef D_A_COMING3_H
#define D_A_COMING3_H

#include "f_op/f_op_actor.h"

namespace daComing3 {
    static void position_is_safety_call_back(void*, void*);
    static void position_is_none_obj(cXyz*);
    
    class Act_c : public fopAc_ac_c {
    public:
        void get_water_height(float*, int*, const cXyz*);
        void get_challenge_id();
        void get_limit_dist();
        void coming_start_init();
        void coming_start_main();
        void coming_game_init();
        void coming_game_main();
        void coming_wait_init();
        void coming_wait_main();
        void coming_process_init(short);
        void eff_break_tsubo();
        void coming_process_main();
        void set_mtx();
        void collision_init();
        void collision_main();
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        s32 _create();
        bool _delete();
        bool _execute();
        bool _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_COMING3_H */
