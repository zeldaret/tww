#ifndef D_A_OBJ_BUOYRACE_H
#define D_A_OBJ_BUOYRACE_H

#include "f_op/f_op_actor.h"

namespace daObjBuoyrace {
    class Act_c : public fopAc_ac_c {
    public:
        struct Attr_c {
            f32 _00;
            f32 _04;
            f32 _08;
            f32 _0C;
            f32 _10;
            f32 _14;
            f32 _18;
            f32 _1C;
            f32 _20;
        }; 
        STATIC_ASSERT(sizeof(Attr_c) == 0x24);

    public:
        static const char M_arcname_kiba[];
        static const char M_arcname_hasi[];
        static const Attr_c M_attr;
        static BOOL solidHeapCB(fopAc_ac_c*);

    public:
        cPhs_State _create();
        inline bool _delete();
        inline bool _draw();
        inline bool _execute();
        const Attr_c& attr() const { return M_attr; }
        void prm_get_id() const {}
        void prm_get_line() const {}
    
        void create_heap();
        cPhs_State create_load();
        void set_mtx();
        void init_mtx();
        void set_water_pos();
        void afl_calc_sway();
        void afl_calc();
        void set_rope_pos();
    
    public:
        /* 0x290 */ f32 field_0x290;
        /* 0x294 */ cXyz field_0x294;
        /* 0x2A0 */ s16 field_0x2A0;
        /* 0x2A2 */ u8 field_0x2A2[0x2C4 - 0x2A2];
        /* 0x2C4 */ request_of_phase_process_class field_0x2C4;
        /* 0x2CC */ request_of_phase_process_class field_0x2CC;
        /* 0x2D4 */ J3DModel* field_0x2D4;
        /* 0x2D8 */ J3DModel* field_0x2D8;
    };  // Size: 0x2DC
};

#endif /* D_A_OBJ_BUOYRACE_H */
