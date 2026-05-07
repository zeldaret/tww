#ifndef D_A_OBJ_SWLIGHT_H
#define D_A_OBJ_SWLIGHT_H

#include "f_op/f_op_actor.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_a_obj.h"
#include "f_op/f_op_actor_mng.h"

class J3DNode;
class J3DMaterial;
class dBgW;

namespace daObjSwlight {
    static void setMaterial(J3DMaterial*, unsigned char);
    static void setMaterial_Before_mirror(J3DMaterial*, unsigned char);

    class Act_c : public fopAc_ac_c {
        typedef void (Act_c::*ModeFunc)();

    public:
        struct Attr_c {
            /* 0x00 */ s16 m00;
            /* 0x04 */ f32 m04;
            /* 0x08 */ f32 m08;
            /* 0x0C */ f32 m0C;
        }; // size = 0x10

        enum Prm_e {
            PRM_SWSAVE_W = 0x08,
            PRM_SWSAVE_S = 0x00,
            
            PRM_SWSAVE2_W = 0x08,
            PRM_SWSAVE2_S = 0x08,
            
            PRM_TYPE_W = 0x01,
            PRM_TYPE_S = 0x10,
        };
   
        void get_power() const {}
        bool is_switch() const {
            return fopAcM_isSwitch(const_cast<Act_c*>(this), prm_get_swSave());
        }
        void off_switch() const {
            fopAcM_offSwitch(const_cast<Act_c*>(this), prm_get_swSave());
        }
        void on_switch() const {
            fopAcM_onSwitch(const_cast<Act_c*>(this), prm_get_swSave());
        }
        s32 prm_get_swSave() const {
            return daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S);
        }
        s32 prm_get_swSave2() const {
            return daObj::PrmAbstract(this, PRM_SWSAVE2_W, PRM_SWSAVE2_S);
        }
        s32 prm_get_type() const {
            return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S);
        }
    
        bool is_switch2() const;
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
        bool _delete();
        static BOOL jnodeCB_moon(J3DNode*, int);
        void set_mtx();
        void init_mtx();
        void init_cc();
        void set_cc_pos();
        void set_cc();
        void init_eye_pos();
        bool chk_light();
        bool power_up();
        bool power_down();
        void mode_norm_moon_init();
        void mode_norm_moon();
        void mode_norm_sun_init();
        void mode_norm_sun();
        void mode_active_moon_init();
        void mode_active_moon();
        void mode_active_sun_init();
        void mode_active_sun();
        bool _execute();
        bool _draw();

        static const char M_arcname[];
        static const dCcD_SrcTri M_tri_src;
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhase;
        /* 0x298 */ J3DModel* m298;
        /* 0x29C */ mDoExt_btkAnm m29C;
        /* 0x2B0 */ mDoExt_bckAnm m2B0;
        /* 0x2C0 */ dBgW* m2C0;
        /* 0x2C4 */ dCcD_Tri m2C4[8];
        /* 0xD44 */ dCcD_Stts mD44[8];
        /* 0xF24 */ s32 mF24;
        /* 0xF28 */ s32 mF28;
        /* 0xF2C */ s16 mF2C;
        /* 0xF2E */ u8 mF2E[0xF30 - 0xF2E];
        /* 0xF30 */ f32 mF30;
        /* 0xF34 */ u8 mF34[0xF38 - 0xF34];
        /* 0xF38 */ Mtx mF38;
    };  // Size: 0xF68
};

#endif /* D_A_OBJ_SWLIGHT_H */
