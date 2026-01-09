#ifndef D_A_OBJ_BUOYRACE_H
#define D_A_OBJ_BUOYRACE_H

#include "d/d_a_obj.h"
#include "f_op/f_op_actor.h"

namespace daObjBuoyrace {
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_ID_W = 0x08,
            PRM_ID_S = 0x00,

            PRM_LINE_W = 0x08,
            PRM_LINE_S = 0x08
        };

        struct Attr_c {
            f32 m00;
            f32 m04;
            f32 m08;
            f32 m0C;
            s16 m10;
            f32 m14;
            f32 m18;
            f32 m1C;
            f32 m20;
        }; 
        STATIC_ASSERT(sizeof(Attr_c) == 0x24);

    public:
        static const char M_arcname_kiba[];
        static const char M_arcname_hasi[];
        static const Attr_c M_attr;
        static BOOL solidHeapCB(fopAc_ac_c*);

    public:
        cPhs_State _create();
        bool _delete();
        bool _draw();
        bool _execute();
        const Attr_c& attr() const { return M_attr; }
        int prm_get_id() const { return daObj::PrmAbstract(this, PRM_ID_W, PRM_ID_S); }
        int prm_get_line() const { return daObj::PrmAbstract(this, PRM_LINE_W, PRM_LINE_S); }
    
        bool create_heap();
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
        /* 0x2A2 */ u8 field_0x2A2[0x2AC - 0x2A2];
        /* 0x2AC */ f32 field_0x2AC;
        /* 0x2B0 */ f32 field_0x2B0;
        /* 0x2B4 */ f32 field_0x2B4;
        /* 0x2B8 */ f32 field_0x2B8;
        /* 0x2BC */ f32 field_0x2BC;
        /* 0x2C0 */ f32 field_0x2C0;
        /* 0x2C4 */ request_of_phase_process_class field_0x2C4;
        /* 0x2CC */ request_of_phase_process_class field_0x2CC;
        /* 0x2D4 */ J3DModel* field_0x2D4;
        /* 0x2D8 */ J3DModel* field_0x2D8;
    };  // Size: 0x2DC
};

#endif /* D_A_OBJ_BUOYRACE_H */
