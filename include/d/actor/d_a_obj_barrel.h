#ifndef D_A_OBJ_BARREL_H
#define D_A_OBJ_BARREL_H

#include "f_op/f_op_actor.h"
#include "c/c_damagereaction.h"
#include "d/d_a_obj.h"

namespace daObjBarrel {
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_CULL_W = 0x03,
            PRM_CULL_S = 0x1c,
        };

        struct Attr_c {
            /* 0x00 */ u16 m00;
            /* 0x02 */ u8 m02[0x4 - 0x2];
            /* 0x04 */ float m04;
            /* 0x08 */ float m08;
            /* 0x0C */ u8 m0C;
            /* 0x0D */ u8 m0D[0x10 - 0xD];
            /* 0x10 */ float m10;
            /* 0x14 */ u8 m14[0x18 - 0x14];
            /* 0x18 */ float m18;
            /* 0x1C */ float m1C;
            /* 0x20 */ float m20;
            /* 0x24 */ float m24;
            /* 0x28 */ short m28;
            /* 0x2A */ short m2A;
            /* 0x2C */ short m2C;
            /* 0x2E */ u8 m2E;
            /* 0x2F */ u8 m2F;
            /* 0x30 */ u8 m30;
            /* 0x31 */ u8 m31;
            /* 0x32 */ u8 m32[0x34 - 0x32];
            /* 0x34 */ float m34;
            /* 0x38 */ u8 m38; // ??
            /* 0x39 */ u8 m39;
            /* 0x3A */ u8 m3A;
            /* 0x3B */ u8 m3B;
            /* 0x3C */ u8 m3C;
            /* 0x3D */ u8 m3D[0x40 - 0x3D];
            /* 0x40 */ float m40;
            /* 0x44 */ float m44;
        };

        const Attr_c& attr() const { return M_attr; }
        void get_slant_angle() {}
        bool pos_init() {
            if (mMode == 0) {
                current.pos = home.pos;
                current.angle = home.angle;
                shape_angle = home.angle;
                return true;
            } else {
                return false;
            }
        }
        int prm_get_cull() const { daObj::PrmAbstract<Prm_e>(this, PRM_CULL_W, PRM_CULL_S); }
        void set_slant_angle(s16) {}
    
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        s32 _create();
        bool _delete();
        void mode_wait_init();
        void mode_wait();
        void mode_carry_init();
        void mode_carry();
        void mode_vib0_init();
        void mode_vib0();
        void mode_vib1_init();
        void mode_vib1();
        void mode_vib2_init();
        void mode_vib2();
        void mode_jump_init();
        void mode_jump();
        void mode_walk_init();
        void mode_walk();
        void vib_pos_ang();
        bool mode_proc_call();
        void set_mtx();
        void init_mtx();
        void set_walk_rot();
        void eff_break();
        void damaged(bool);
        void cull_set_draw();
        void cull_set_move();
        u32 get_se_map_hit() const;
        void set_senv(int, int) const;
        void se_fall_water();
        void eff_hit_water_splash();
        bool chk_sink_water();
        bool chk_sinkdown_water();
        void eff_land_smoke();
        bool damage_cc_proc();
        bool damage_bg_proc();
        bool damage_bg_proc_directly();
        bool _execute();
        bool _draw();

        static const char M_arcname[9];
        static const dCcD_SrcCyl M_cyl_src;
        static const Attr_c M_attr;
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ dBgS_Acch mAcch;
        /* 0x460 */ dBgS_AcchCir mAcchCir;
        /* 0x4A0 */ dCcD_Stts mStts;
        /* 0x4DC */ dCcD_Cyl mCyl;
        /* 0x60C */ int mMode;
        /* 0x610 */ short m610;
        /* 0x612 */ short m612;
        /* 0x614 */ int m614;
        /* 0x618 */ float m618;
        /* 0x61C */ short m61C;
        /* 0x61E */ u8 m61E[0x620 - 0x61E];
        /* 0x620 */ bool m620;
        /* 0x621 */ s8 m621;
        /* 0x622 */ bool m622;
        /* 0x623 */ bool m623;
        /* 0x624 */ cXyz m624;
        /* 0x630 */ short m630;
    };
    
    namespace Method {
        s32 Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_BARREL_H */
