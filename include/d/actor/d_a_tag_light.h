#ifndef D_A_TAG_LIGHT_H
#define D_A_TAG_LIGHT_H

#include "f_op/f_op_actor.h"
#include "d/d_a_obj.h"
#include "m_Do/m_Do_mtx.h"

class J3DMaterial;
class mDoExt_btkAnm;

namespace daTagLight {
    static bool get_cross_plane_line(cXyz*, float, float, float, float, float, float, float, float, float, float);
    
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_TYPE_W = 2,
            PRM_TYPE_S = 0,

            PRM_SWSAVE2_W = 8,
            PRM_SWSAVE2_S = 2,

            PRM_CCR_W = 2,
            PRM_CCR_S = 8,

            PRM_CONERATIO_W = 4,
            PRM_CONERATIO_S = 10,

            PRM_FADETYPE_W = 2,
            PRM_FADETYPE_S = 14,

            PRM_SWSAVE_W = 8,
            PRM_SWSAVE_S = 16,

            PRM_SCH_W = 8,
            PRM_SCH_S = 24,
        };

        bool chk_inside(const cXyz* pos) const {
            if (m304) {
                cXyz sp18;
                mDoMtx_multVec(m2D4, pos, &sp18);

                if (m2A0 == 0) {
                    bool bVar2 = false;
                    if (sp18.x >= M_box_x_min && sp18.x <= M_box_x_max &&
                        sp18.y >= M_box_y_min && sp18.y <= M_box_y_max && 
                        sp18.z >= M_box_z_min && sp18.z <= M_box_z_max) {
                        bVar2 = true;
                    }
                    return bVar2;
                }
                
                if (m2A0 == 1 && sp18.y >= M_cone_lower&& sp18.y <= M_cone_upper) {
                    f32 abs = sp18.absXZ();
                    f32 fVar5 = (sp18.y - M_cone_lower) * (1.0f / (M_cone_upper - M_cone_lower));
                    f32 ratio = prm_get_coneRatio();
                    ratio = ratio * 0.06666667f;

                    return abs <= ((1.0f - fVar5) + fVar5 * ratio) * M_cone_r;
                }
            }

            return false;
        }

        s32 prm_get_ccR() const { return daObj::PrmAbstract(this, PRM_CCR_W, PRM_CCR_S); }
        s32 prm_get_coneRatio() const { return daObj::PrmAbstract(this, PRM_CONERATIO_W, PRM_CONERATIO_S); }
        s32 prm_get_fadeType() const { return daObj::PrmAbstract(this, PRM_FADETYPE_W, PRM_FADETYPE_S); }
        u8 prm_get_sch() const { return daObj::PrmAbstract(this, PRM_SCH_W, PRM_SCH_S); }
        s32 prm_get_swSave() const { return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S); }
        s32 prm_get_swSave2() const { return daObj::PrmAbstract(this, PRM_SWSAVE2_W, PRM_SWSAVE2_S); }
        s32 prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
    
        f32 get_cc_r() const;
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        bool chk_sw() const;
        bool chk_sch() const;
        bool chk_light() const;
        void get_base_model_light_start_offset(cXyz*);
        void get_projection_info(cXyz*, cXyz*, cXyz*, const cXyz*, const cXyz*);
        void make_projection_mtx(const cXyz*, const cXyz*, const cXyz*, const cXyz*);
        void set_spot_mtx();
        void set_spot();
        void init_spot();
        bool _execute();
        static void set_material(J3DMaterial*, unsigned char);
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

        static const char M_arcname[];
        static const dCcD_SrcSph M_sph_src;
        static const f32 M_alpha_spd[];
        static const s16 M_cc_r[];
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhase;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_btkAnm* mpBtk;
        /* 0x2A0 */ s32 m2A0;
        /* 0x2A4 */ Mtx m2A4;
        /* 0x2D4 */ Mtx m2D4;
        /* 0x304 */ bool m304;
        /* 0x305 */ bool m305;
        /* 0x306 */ s16 m306;
        /* 0x308 */ f32 m308;
        /* 0x30C */ dCcD_Stts mStts;
        /* 0x348 */ dCcD_Sph mSph;
        /* 0x474 */ Mtx m474;
        /* 0x4A4 */ cXyz m4A4;
        
    }; // size = 0x4B0
};

#endif /* D_A_TAG_LIGHT_H */
