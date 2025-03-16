#ifndef D_A_OBJ_AJAV_H
#define D_A_OBJ_AJAV_H

#include "f_op/f_op_actor.h"

namespace daObjAjav {
    static void daObjAjav_make_splash(cXyz, float);
    static void check_angle(short*, short);
    static void daObjAjav_limit_angle(short*, short);
    static void daObjAjav_get_rot_speed(cXyz, cXyz, short);
    
    class Act_c;
    
    class Part_c {
    public:
        void checkExeProc(void (daObjAjav::Part_c::*)(daObjAjav::Act_c*)) {}
        void draw(daObjAjav::Act_c*) {}
        void execute(daObjAjav::Act_c*) {}
        void setDrawProc(void (daObjAjav::Part_c::*)(daObjAjav::Act_c*)) {}
        void setExeProc(void (daObjAjav::Part_c::*)(daObjAjav::Act_c*)) {}
        void set_se_pos(cXyz) {}
        
        void make_hamon(cXyz, float);
        void no_proc(daObjAjav::Act_c*);
        void init_data(cXyz, cXyz, dKy_tevstr_c*, cXyz*);
        void set_mdl_area(const char*, int, unsigned long);
        void init_mtx(cXyz, csXyz, cXyz);
        void set_flaw_mtx(cXyz, csXyz);
        void set_fall_mtx(cXyz, csXyz);
        void fall_init(cXyz, csXyz, short, unsigned short);
        void fall_0(daObjAjav::Act_c*);
        void fall_1(daObjAjav::Act_c*);
        void flaw(daObjAjav::Act_c*);
        void draw_normal(daObjAjav::Act_c*);
        void draw_flashing(daObjAjav::Act_c*);
        void draw_flashing_normal(daObjAjav::Act_c*);
        void draw_shy(daObjAjav::Act_c*);
        void make_fall_rock(int);
    };
    
    class Act_c : public fopAc_ac_c {
    public:
        void check_ev() {}
        void check_sw() {}
        void on_sw() {}
        
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        s32 _create();
        bool _delete();
        void init_mtx();
        void set_tex();
        void set_co_offset();
        void check_all_wait();
        void check_end();
        void to_broken();
        void damage_part();
        void make_shot_rock();
        void make_hamon2(cXyz, float);
        void set_hamon(float);
        bool _execute();
        bool _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_OBJ_AJAV_H */
