#ifndef D_A_TAG_LIGHT_H
#define D_A_TAG_LIGHT_H

#include "f_op/f_op_actor.h"
#include "JSystem/J3DGraphBase/J3DMaterial.h"

namespace daTagLight {
    class Act_c : public fopAc_ac_c {
    public:
        void get_cc_r() const;
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void _create();
        void _delete();
        void chk_sw() const;
        void chk_sch() const;
        void chk_light() const;
        void get_base_model_light_start_offset(cXyz*);
        void get_projection_info(cXyz*, cXyz*, cXyz*, const cXyz*, const cXyz*);
        void make_projection_mtx(const cXyz*, const cXyz*, const cXyz*, const cXyz*);
        void set_spot_mtx();
        void set_spot();
        void init_spot();
        void _execute();
        void set_material(J3DMaterial*, unsigned char);
        void _draw();
    
    public:
        /* Place member variables here */
    };
};

#endif /* D_A_TAG_LIGHT_H */
