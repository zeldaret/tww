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

        enum Mode {
            MODE_WAIT  = 0x0,
            MODE_CARRY = 0x1,
            MODE_VIB0  = 0x2,
            MODE_VIB1  = 0x3,
            MODE_VIB2  = 0x4,
            MODE_JUMP  = 0x5,
            MODE_WALK  = 0x6,
        };

        struct Attr_c {
            /* 0x00 */ u16 mBdlIdx;
            /* 0x02 */ u8 mShadowSize;
            /* 0x03 */ bool mEnableCutoff;
            /* 0x04 */ float mAttnH;
            /* 0x08 */ float mNormalGravity;
            /* 0x0C */ u8 mWeight;
            /* 0x10 */ float mSinkDownDepth;
            /* 0x14 */ float m14; // unused
            /* 0x18 */ float mVib0SpeedY;
            /* 0x1C */ float mVib0Gravity;
            /* 0x20 */ float mVib1Gravity;
            /* 0x24 */ float mVib2Gravity;
            /* 0x28 */ short m28;
            /* 0x2A */ short m2A;
            /* 0x2C */ short m2C;
            /* 0x2E */ u8 mVib0Duration;
            /* 0x2F */ u8 mVib1Duration;
            /* 0x30 */ u8 mVib2Duration;
            /* 0x31 */ u8 m31;
            /* 0x34 */ float mFallDmgH;
            /* 0x38 */ u8 m38; // unused
            /* 0x39 */ u8 mSeBreakP1;
            /* 0x3A */ u8 mSeBreakP2;
            /* 0x3B */ u8 mSeHitP1;
            /* 0x3C */ u8 mSeHitP2;
            /* 0x40 */ float mWPillarScaleXZ;
            /* 0x44 */ float mWPillarScaleY;
        };

        const Attr_c& attr() const { return M_attr; }
        s16 get_slant_angle() { return m61C; }
        void set_slant_angle(s16 angle) { m61C = angle; }
        bool pos_init() {
            if (mMode == MODE_WAIT) {
                current.pos = home.pos;
                current.angle = home.angle;
                shape_angle = home.angle;
                return true;
            } else {
                return false;
            }
        }
        int prm_get_cull() const { return daObj::PrmAbstract<Prm_e>(this, PRM_CULL_W, PRM_CULL_S); }
    
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        cPhs_State _create();
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
        static const float l_s_radius;
        static const float l_l_radius;
        static const float l_gnd_fric;
        static const short l_gnd_deg;
        static const float l_viscous_resist;
        static const float l_inert_resist;
        static const float l_max_move;
        static const short l_max_vib_angl;
        static const float l_min_move_dir;
        static const float l_wind_max;
        static const float l_shape_vec;
        static const float l_tgr_ratio;
        static const dCcD_SrcCyl M_cyl_src;
        static const Attr_c M_attr;
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ dBgS_ObjAcch mAcch;
        /* 0x460 */ dBgS_AcchCir mAcchCir;
        /* 0x4A0 */ dCcD_Stts mStts;
        /* 0x4DC */ dCcD_Cyl mCyl;
        /* 0x60C */ int mMode;
        /* 0x610 */ s16 m610;
        /* 0x612 */ s16 m612;
        /* 0x614 */ int mTimer;
        /* 0x618 */ float mLastGroundY;
        /* 0x61C */ s16 m61C;
        /* 0x61E */ u8 m61E[0x620 - 0x61E];
        /* 0x620 */ bool mOnGround;
        /* 0x621 */ s8 mInitTimer;
        /* 0x622 */ bool mForceExec;
        /* 0x623 */ bool mSunk;
        /* 0x624 */ cXyz mMove;
        /* 0x630 */ s16 m630;
    }; // Size: 0x634

    STATIC_ASSERT(sizeof(Act_c) == 0x634);
    
    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_OBJ_BARREL_H */
