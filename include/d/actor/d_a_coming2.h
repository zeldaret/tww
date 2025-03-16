#ifndef D_A_COMING2_H
#define D_A_COMING2_H

#include "f_op/f_op_actor.h"
#include "d/actor/d_a_obj_barrel2.h"

namespace daComing2 {
    static void get_speed(fopAc_ac_c*);
    static void position_is_safety_call_back(void*, void*);
    static void position_is_none_obj(cXyz*);
    static void checkLineCrossXZ(cXyz*, cXyz*, cXyz*, cXyz*);

    class Act_c : public fopAc_ac_c {
    public:
        void get_coming_point() {}
        void init_coming_point() {}
        void minus_coming_point1() {}
        void minus_coming_point2() {}
        void pluss_coming_point1() {}
    
        void chase_ship();
        void renew_scope_info();
        void no_ship_obstacle(cXyz*);
        void check_in_large_sea(const cXyz*);
        void get_water_height(float*, const cXyz*);
        void init_barrelN_info(int);
        void init_barrel_info();
        void init_flag_info();
        void init_coming_info();
        void make_coming_param(cXyz*, daObjBarrel2::Type_e*, int*, bool*);
        void request_barrel_exitN(int);
        void request_all_barrel_exit();
        void request_all_flag_exit();
        void barrel_execute(int);
        void barrel_main();
        void coming_clear_init();
        void coming_clear_main();
        void coming_wait_init();
        void coming_wait_main();
        void coming_setF_init();
        void coming_setF_main();
        void coming_checkS_init();
        void coming_checkS_main();
        void coming_game_init();
        void coming_game_main();
        void coming_process_init(short);
        void coming_process_main();
        s32 _create();
        bool _delete();
        bool _execute();
        bool _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_COMING2_H */
