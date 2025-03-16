#ifndef D_A_TAG_LIGHT_H
#define D_A_TAG_LIGHT_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"

class J3DMaterial;

namespace daTagLight {
    static void get_cross_plane_line(cXyz*, float, float, float, float, float, float, float, float, float, float);
    
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_CONERATIO_W = 0x04,
            PRM_CONERATIO_S = 0x0A,
        };

        void chk_inside(const cXyz* pos) const {
            /* Nonmatching */
            // M_box_x_min
            // M_box_x_max
            // M_box_y_min
            // M_box_y_max
            // M_box_z_min
            // M_box_z_max
            // M_cone_lower
            // M_cone_upper
            prm_get_coneRatio();
            // M_cone_r
        }
        void prm_get_ccR() const {}
        int prm_get_coneRatio() const { return daObj::PrmAbstract(this, PRM_CONERATIO_W, PRM_CONERATIO_S); }
        void prm_get_fadeType() const {}
        void prm_get_sch() const {}
        void prm_get_swSave() const {}
        void prm_get_swSave2() const {}
        void prm_get_type() const {}
    
        void get_cc_r() const;
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        s32 _create();
        bool _delete();
        void chk_sw() const;
        void chk_sch() const;
        void chk_light() const;
        void get_base_model_light_start_offset(cXyz*);
        void get_projection_info(cXyz*, cXyz*, cXyz*, const cXyz*, const cXyz*);
        void make_projection_mtx(const cXyz*, const cXyz*, const cXyz*, const cXyz*);
        void set_spot_mtx();
        void set_spot();
        void init_spot();
        bool _execute();
        void set_material(J3DMaterial*, unsigned char);
        bool _draw();
        
        static const f32 M_box_x_min;
        static const f32 M_box_x_max;
        static const f32 M_box_y_min;
        static const f32 M_box_y_max;
        static const f32 M_box_z_min;
        static const f32 M_box_z_max;
        static const f32 M_cone_lower;
        static const f32 M_cone_upper;
        static const f32 M_cone_r;
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_TAG_LIGHT_H */
