#ifndef D_A_OBJ_AJAV_H
#define D_A_OBJ_AJAV_H

#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor.h"

namespace daObjAjav {
    static void daObjAjav_make_splash(cXyz, float);
    static void check_angle(short*, short);
    static void daObjAjav_limit_angle(short*, short);
    static void daObjAjav_get_rot_speed(cXyz, cXyz, short);
    
    class Act_c;
    
    class Part_c {
    public:
        typedef void(Part_c::*daObjAjavPartCallback)(daObjAjav::Act_c*);
    public:
        void checkExeProc(void (daObjAjav::Part_c::*)(daObjAjav::Act_c*)) {}
        void draw(daObjAjav::Act_c*) {}
        void execute(daObjAjav::Act_c*) {}
        void setDrawProc(daObjAjavPartCallback i_drawProc) {}
        void setExeProc(daObjAjavPartCallback i_exeProc) {}
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
    public:
        /* 0x00 */ cXyz field_0x00;
        /* 0x0C */ cXyz field_0x0C;
        /* 0x18 */ cXyz field_0x18;
        /* 0x24 */ cXyz field_0x24;
        /* 0x30 */ u8 field_0x30[0x3C - 0x30];
        /* 0x3C */ csXyz field_0x3C;
        /* 0x42 */ u8 field_0x42[0x6C - 0x42];
        /* 0x6C */ cXyz field_0x6C;
        /* 0x78 */ J3DModel* field_0x78;
        /* 0x7C */ dKy_tevstr_c* field_0x7C;
        /* 0x80 */ daObjAjavPartCallback field_0x80;
        /* 0x8C */ daObjAjavPartCallback field_0x8C;
    };  // Size: 0x98
    STATIC_ASSERT(sizeof(Part_c) == 0x98);


    class Act_c : public fopAc_ac_c {
    public:
        static const char M_arcname[];
    public:
        void check_ev() {}
        void check_sw() {}
        void on_sw() {}
        
        static BOOL solidHeapCB(fopAc_ac_c*);
        BOOL create_heap();
        cPhs_State _create();
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
        /* 0x290 */ u32 field_0x290;
        /* 0x294 */ request_of_phase_process_class mPhs;
        /* 0x29C */ dCcD_Stts field_0x29C;
        /* 0x2D8 */ dCcD_Sph field_0x2D8;
        /* 0x404 */ u8 field_0x404[0x410 - 0x404];
        /* 0x410 */ dCcD_Stts field_0x410;
        /* 0x44C */ dCcD_Cyl field_0x44C;
        /* 0x57C */ dCcD_Stts field_0x57C[2];
        /* 0x5F4 */ dCcD_Cyl field_0x5F4[2];
        /* 0x854 */ Mtx field_0x854;
        /* 0x884 */ u8 field_0x884[0x890 - 0x884];
        /* 0x890 */ Part_c field_0x890[6];
        /* 0xC20 */ s16 field_0xC20;
        /* 0xC22 */ s8 field_0xC22;
        /* 0xC23 */ s8 field_0xC23;
        /* 0xC24 */ s8 field_0xC24;
        /* 0xC25 */ u8 field_0xC25[0xC26 - 0xC25];
        /* 0xC26 */ s16 field_0xC26;
        /* 0xC28 */ s8 field_0xC28;
        /* 0xC29 */ u8 field_0xC29[0xC2C - 0xC29];
        /* 0xC2C */ dBgW* field_0xC2C;
    };  // Size: 0xC30
    STATIC_ASSERT(sizeof(Act_c) == 0xC30);
};

#endif /* D_A_OBJ_AJAV_H */
