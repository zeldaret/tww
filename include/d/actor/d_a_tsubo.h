#ifndef D_A_TSUBO_H
#define D_A_TSUBO_H

#include "f_op/f_op_actor.h"
#include "d/d_cc_d.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_acch.h"
#include "SSystem/SComponent/c_bg_s_poly_info.h"
#include "d/d_particle.h"
#include "d/d_a_obj.h"
#include "SSystem/SComponent/c_angle.h"
#include "SSystem/SComponent/c_phase.h"
#include "m_Do/m_Do_mtx.h"

namespace daTsubo {
    enum DataFlag_e {
        DATA_FLAG_1_e = 0x1,
        DATA_FLAG_2_e = 0x2,
        DATA_FLAG_4_e = 0x4,
        DATA_FLAG_8_e = 0x8,
        DATA_FLAG_10_e = 0x10,
        DATA_FLAG_20_e = 0x20,
    };

    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_ITEMNO_W = 6,
            PRM_ITEMNO_S = 0,

            PRM_SPEC_W = 6,
            PRM_SPEC_S = 8,

            PRM_MOVEBG_W = 2,
            PRM_MOVEBG_S = 14,

            PRM_ITEMSAVE_W = 7,
            PRM_ITEMSAVE_S = 16,

            PRM_TYPE_W = 4,
            PRM_TYPE_S = 24,

            PRM_CULL_W = 3,
            PRM_CULL_S = 28,

            PRM_STICK_W = 1,
            PRM_STICK_S = 31,
        };
        
        enum Type {
            TYPE_WATER_JUG = 0x2,
            TYPE_KUTANI = 0xE,
        };

        struct Data_c {
            const Vec* get_particle_scale() const { return &m74; }

            /* 0x00 */ f32 mGravity;
            /* 0x04 */ f32 m04;
            /* 0x08 */ f32 mAttnY;
            /* 0x0C */ f32 mModelScale;
            /* 0x10 */ u8 m10;
            /* 0x14 */ f32 m14;
            /* 0x18 */ f32 m18;
            /* 0x1C */ f32 m1C;
            /* 0x20 */ f32 m20;
            /* 0x24 */ f32 m24;
            /* 0x28 */ s16 m28;
            /* 0x2A */ s16 m2A;
            /* 0x2C */ s16 m2C;
            /* 0x30 */ f32 m30;
            /* 0x34 */ f32 m34;
            /* 0x38 */ f32 m38;
            /* 0x3C */ f32 m3C;
            /* 0x40 */ f32 m40;
            /* 0x44 */ f32 m44;
            /* 0x48 */ f32 m48;
            /* 0x4C */ f32 m4C;
            /* 0x50 */ f32 m50;
            /* 0x54 */ s16 m54;
            /* 0x56 */ s16 m56;
            /* 0x58 */ f32 m58;
            /* 0x5C */ f32 m5C;
            /* 0x60 */ u8 m60;
            /* 0x61 */ u8 m61;
            /* 0x62 */ u8 m62;
            /* 0x63 */ u8 m63;
            /* 0x64 */ u8 m64;
            /* 0x65 */ u8 m65;
            /* 0x68 */ DataFlag_e mFlag;
            /* 0x6C */ u16 m6C;
            /* 0x6E */ u8 m6E;
            /* 0x6F */ u8 mAcchCirRad;
            /* 0x70 */ u8 m70;
            /* 0x71 */ u8 mAcchRoofHeight;
            /* 0x72 */ u8 mAttnDist;
            /* 0x74 */ Vec m74;
            /* 0x80 */ u32 m80;
            /* 0x84 */ s32 mSoundID_Break;
            /* 0x88 */ s32 m88;
            /* 0x8C */ s32 mSoundID_FallLava;
            /* 0x90 */ s32 mSoundID_FallWater;
            /* 0x94 */ s32 mSoundID_Hit;
            /* 0x98 */ s16 mCullSphX_Move;
            /* 0x9A */ s16 mCullSphY_Move;
            /* 0x9C */ s16 mCullSphZ_Move;
            /* 0x9E */ s16 mCullSphR_Move;
            /* 0xA0 */ u8 mA0[0xA4 - 0xA0];
            /* 0xA4 */ s16 mCullSphX_Draw;
            /* 0xA6 */ s16 mCullSphY_Draw;
            /* 0xA8 */ s16 mCullSphZ_Draw;
            /* 0xAA */ s16 mCullSphR_Draw;
            /* 0xAC */ u8 mAC[0xB0 - 0xAC];
            /* 0xB0 */ f32 mB0;
            /* 0xB4 */ u8 mB4[0xB8 - 0xB4];
            /* 0xB8 */ u32 mHeapSize;
            /* 0xBC */ f32 mBC;
            /* 0xC0 */ f32 mC0;
            /* 0xC4 */ f32 mC4;
            /* 0xC8 */ f32 mC8;
        }; // size = 0xCC

        struct AttrSpine_c {
            /* 0x00 */ f32 m00;
            /* 0x04 */ f32 m04;
            /* 0x08 */ f32 m08;
            /* 0x0C */ f32 m0C;
            /* 0x10 */ f32 m10;
            /* 0x14 */ f32 m14;
            /* 0x18 */ s16 m18;
            /* 0x1A */ s16 m1A;
            /* 0x1C */ s16 m1C;
            /* 0x1E */ s16 m1E;
            /* 0x20 */ f32 m20;
            /* 0x24 */ f32 m24;
            /* 0x28 */ f32 m28;
            /* 0x2C */ f32 m2C;
            /* 0x30 */ s16 m30;
        }; // size = 0x34

        struct SpecBokoData {
            /* 0x00 */ s16 m00;
            /* 0x02 */ s16 m02;
            /* 0x04 */ f32 m04;
            /* 0x08 */ f32 m08;
        }; // size = 0xC

        struct M7A0 {
            /* 0x00 */ fpc_ProcID m00;
            /* 0x04 */ u8 m04;
            /* 0x06 */ s16 m06;
            /* 0x08 */ s16 m08;
            /* 0x0C */ f32 m0C;
            /* 0x10 */ f32 m10;
            /* 0x14 */ f32 m14;
            /* 0x18 */ s8 m18;
        }; // size = 0x1C
        
        int prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        bool prm_chk_type_kutani() const { return prm_get_type() == TYPE_KUTANI; }
        
        const AttrSpine_c& attrSpine() { return M_attrSpine; }
        const Data_c& data() const { return M_data[mType]; }
        const SpecBokoData& data_spec_boko(int index) { return M_data_spec_boko[index]; }
        BOOL is_switch() const { 
            int sw = prmZ_get_swSave();
            return fopAcM_isSwitch(const_cast<Act_c*>(this), sw);
        }

        bool pos_init() {
            if (m678 == 2) {
                current.pos = home.pos;
                current.angle = home.angle;
                shape_angle = home.angle;

                m688.Val(cSAngle::_0);
                m68A.Val(cSAngle::_0);
                m68C.Val(cSAngle::_0);
                m68E.Val(cSAngle::_0);
                m690.Val(cSAngle::_0);
                m692.Val(current.angle.y);

                mDoMtx_identity(mPoseMtx);
                return true;
            }
            return false;
        }

        u8 prmZ_get_swSave() const { return mSwitchNo; }
        s32 prm_get_cull() const { return daObj::PrmAbstract(this, PRM_CULL_W, PRM_CULL_S); }
        s32 prm_get_itemNo() const { return daObj::PrmAbstract(this, PRM_ITEMNO_W, PRM_ITEMNO_S); }
        s32 prm_get_itemSave() const { return daObj::PrmAbstract(this, PRM_ITEMSAVE_W, PRM_ITEMSAVE_S); }
        bool prm_get_moveBg() const { return daObj::PrmAbstract(this, PRM_MOVEBG_W, PRM_MOVEBG_S) == 1u; }
        s32 prm_get_spec() const { return daObj::PrmAbstract(this, PRM_SPEC_W, PRM_SPEC_S); }

        bool prm_get_stick() const {
            return daObj::PrmAbstract(this, PRM_STICK_W, PRM_STICK_S);
        }
        
        static s32 prm_make_acorn(bool arg1, int item_no, int bit_no) {
            s32 a1 = (arg1 ? 0x4 : 0x3F);
            s32 param = 0;

            param |= ((bit_no & 0x7F) << 16);
            param |= ((item_no & 0x3F) << 0) | (a1 << 8);
            param |= ((7 << 24) | (1 << 31));

            return param;
        }

        void prm_make_skull() {}
        void prm_make_yw1() {}
        void prm_off_moveBg() { fopAcM_SetParam(this, base.mParameters | 0xC000); }
        void prm_off_stick() { fopAcM_SetParam(this, base.mParameters & ~0x80000000); }
        void prm_set_cull_non() { fopAcM_SetParam(this, base.mParameters & ~0x70000000); }
        void prm_set_itemNo(int) {}
        void set_drop_spd_y0(float) {}
        bool spec_chk_prm_boko() const { return prm_get_spec() != 0x3F; }
    
        void prmZ_init();
        static BOOL solidHeapCB(fopAc_ac_c*);
        bool create_heap();
        void create_init_cull();
        void create_init_cc();
        void create_init_bgc();
        cPhs_State _create();
        bool _is_delete();
        bool _delete();
        void spec_make_boko(int);
        void spec_init();
        void spec_set_actor();
        void spec_clr_actor();
        void spec_carry_spec();
        void spec_mode_carry_init();
        void spec_mode_carry(bool);
        void spec_mode_put_init();
        void spec_set_room();
        void spec_remove();
        void spec_kill();
        void spec_mtx();
        void mode_hide_init();
        void mode_hide();
        void mode_appear_init();
        void mode_appear();
        void mode_wait_init();
        void mode_wait();
        void mode_walk_init();
        void mode_walk();
        void mode_carry_init();
        void mode_carry();
        void mode_drop_init();
        void mode_drop();
        void mode_sink_init();
        void mode_sink();
        void mode_afl_init();
        void mode_afl();
        bool mode_proc_call();
        void cull_set_draw();
        void cull_set_move();
        void damaged(int, cBgS_PolyInfo*, bool, const cXyz*);
        void damaged(int, cBgS_PolyInfo*);
        void damaged_lava();
        bool damage_tg_acc();
        bool damage_cc_proc();
        bool damage_bg_proc();
        bool damage_bg_proc_directly();
        bool damage_kill_proc();
        void crr_pos(const cXyz&);
        void crr_pos_water();
        void crr_pos_lava();
        void water_tention();
        static f32 reflect(cXyz*, const cBgS_PolyInfo&, float);
        void bound(float);
        void moment_small(const cXyz*);
        void moment_big(const cXyz*);
        void moment_water(const cXyz*);
        void moment_barrel(const cXyz*);
        void moment_stool(const cXyz*);
        void moment_skull(const cXyz*);
        void moment_pail(const cXyz*);
        void moment_spine(const cXyz*);
        void moment_hbox2S(const cXyz*);
        void moment_tryColSun(const cXyz*);
        void moment_tryColMer(const cXyz*);
        void moment_tryColJup(const cXyz*);
        void moment_tryKeyGate(const cXyz*);
        void moment_pinecone(const cXyz*);
        void moment_kutani(const cXyz*);
        void moment_woodS(const cXyz*);
        void moment_proc_call();
        void set_wind_vec();
        void init_mtx();
        void set_mtx();
        void set_tensor(const cXyz*);
        void init_rot_throw();
        void init_rot_clean();
        void set_tensor_hide();
        void set_tensor_appear();
        void set_tensor_wait();
        void set_tensor_walk();
        void set_tensor_carry();
        void set_tensor_drop();
        void set_tensor_sink();
        void set_tensor_afl();
        void eff_drop_water();
        void eff_land_smoke();
        void eff_break_barrel();
        void eff_break_tsubo();
        void eff_break_stool();
        void eff_break_skull();
        void eff_break_pail();
        void eff_break_spine();
        void eff_break_hbox2S();
        void eff_break_try();
        void eff_break_pinecone();
        void eff_break_woodS();
        void eff_hit_water_splash();
        void eff_hit_lava_splash();
        void eff_kutani_set();
        void eff_kutani_init();
        void bg_crr_lava();
        bool chk_sink_lava();
        bool chk_sink_water();
        bool chk_sinkdown_water();
        void calc_drop_param(float*, float*, float*) const;
        void calc_afl_param(float*, float*, float*) const;
        void se_fall_water();
        void se_fall_lava();
        void se_break(cBgS_PolyInfo*);
        void se_pickup_carry();
        void se_pickup_carry_init();
        void se_pickup();
        void set_senv(int, int) const;
        void cam_lockoff() const;
        bool _execute();
        bool _draw();

        #if VERSION == VERSION_DEMO
        static dBgS_ObjGndChk_Yogan M_bg_lava;
        #endif
        static fopAc_ac_c* M_spec_act[];
        static const char* const M_arcname[];
        static const dCcD_SrcCyl M_cyl_src;
        static const Data_c M_data[];
        static const SpecBokoData M_data_spec_boko[];
        static const AttrSpine_c M_attrSpine;
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhase;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ mDoExt_brkAnm* mpBrk;
        /* 0x2A0 */ dBgS_ObjAcch mAcch;
        /* 0x464 */ dBgS_AcchCir mAcchCir;
#if VERSION == VERSION_DEMO
        /* 0x638 */ dCcD_Stts mStts;
        /* 0x4F8 */ f32 m4F8;
        /* 0x508 */ dCcD_Cyl mCyl;
#else
        /* 0x4A4 */ dBgS_ObjGndChk_Yogan mGndChkYogan;
        /* 0x4F8 */ f32 m4F8;
        /* 0x4FC */ f32 m4FC;
        /* 0x500 */ f32 m500;
        /* 0x504 */ bool m504;
        /* 0x505 */ bool m505;
        /* 0x508 */ dCcD_Cyl mCyl;
        /* 0x638 */ dCcD_Stts mStts;
#endif
        /* 0x674 */ s32 mType;
        /* 0x678 */ s32 m678;
        /* 0x67C */ u16 mSwitchNo;
        /* 0x67E */ u8 m67E;
        /* 0x67F */ u8 m67F;
        /* 0x680 */ u8 m680;
        /* 0x681 */ s8 m681;
        /* 0x682 */ u8 m682;
        /* 0x683 */ u8 m683;
        /* 0x684 */ u8 m684;
        /* 0x685 */ bool m685;
        /* 0x686 */ u8 m686;
        /* 0x687 */ u8 m687[0x688 - 0x687];
        /* 0x688 */ cSAngle m688;
        /* 0x68A */ cSAngle m68A;
        /* 0x68C */ cSAngle m68C;
        /* 0x68E */ cSAngle m68E;
        /* 0x690 */ cSAngle m690;
        /* 0x692 */ cSAngle m692;
        /* 0x694 */ Quaternion m694;
        /* 0x6A4 */ u8 m6A4[0x6B0 - 0x6A4];
        /* 0x6B0 */ cXyz m6B0;
        /* 0x6BC */ Mtx mPoseMtx;
        /* 0x6EC */ f32 m6EC;
        /* 0x6F0 */ cXyz m6F0;
        /* 0x6FC */ f32 m6FC;
        /* 0x700 */ cXyz m700;
        /* 0x70C */ dPa_followEcallBack m70C[3];
        /* 0x748 */ dPa_followEcallBack m748[3];
        /* 0x784 */ dPa_followEcallBack m784;
        /* 0x798 */ u8 m798;
        /* 0x799 */ u8 m799[0x7A0 - 0x799];
        /* 0x7A0 */ M7A0 m7A0[3];
        /* 0x7F4 */ cXyz m7F4;
        /* 0x800 */ s16 m800;
        /* 0x802 */ s16 m802;
        /* 0x804 */ s16 m804;
        /* 0x806 */ s16 m806;
        /* 0x808 */ f32 m808;
        /* 0x80C */ f32 m80C;
        /* 0x810 */ u8 m810;
        /* 0x811 */ u8 m811;
        /* 0x814 */ cXyz m814;
    };  // Size: 0x820
    
    namespace Method {
        cPhs_State Create(void*);
        BOOL Delete(void*);
        BOOL Execute(void*);
        BOOL Draw(void*);
        BOOL IsDelete(void*);
        extern actor_method_class Table;
    };
};

#endif /* D_A_TSUBO_H */
