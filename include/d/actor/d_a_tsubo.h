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
    class Act_c : public fopAc_ac_c {
    public:
        enum Prm_e {
            PRM_TYPE_W = 0x04,
            PRM_TYPE_S = 0x18,

            PRM_STICK_W = 0x01,
            PRM_STICK_S = 0x1F,
        };
        
        enum Type {
            TYPE_WATER_JUG = 0x2,
            TYPE_KUTANI = 0xE,
        };
        
        int prm_get_type() const { return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S); }
        bool prm_chk_type_kutani() const { return prm_get_type() == TYPE_KUTANI; }
        
        void attrSpine() {}
        void data() const {}
        void data_spec_boko(int) {}
        void is_switch() const {}
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
            } else {
                return false;
            }
        }
        void prmZ_get_swSave() const {}
        void prm_get_cull() const {}
        void prm_get_itemNo() const {}
        void prm_get_itemSave() const {}
        void prm_get_moveBg() const {}
        void prm_get_spec() const {}

        int prm_get_stick() const {
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
        void prm_off_moveBg() {}
        void prm_off_stick() {}
        void prm_set_cull_non() {}
        void prm_set_itemNo(int) {}
        void set_drop_spd_y0(float) {}
        void spec_chk_prm_boko() const {}
    
        void prmZ_init();
        void solidHeapCB(fopAc_ac_c*);
        void create_heap();
        void create_init_cull();
        void create_init_cc();
        void create_init_bgc();
        cPhs_State _create();
        void _is_delete();
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
        void mode_proc_call();
        void cull_set_draw();
        void cull_set_move();
        void damaged(int, cBgS_PolyInfo*, bool, const cXyz*);
        void damaged(int, cBgS_PolyInfo*);
        void damaged_lava();
        void damage_tg_acc();
        void damage_cc_proc();
        void damage_bg_proc();
        void damage_bg_proc_directly();
        void damage_kill_proc();
        void crr_pos(const cXyz&);
        void crr_pos_water();
        void crr_pos_lava();
        void water_tention();
        void reflect(cXyz*, const cBgS_PolyInfo&, float);
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
        void chk_sink_lava();
        void chk_sink_water();
        void chk_sinkdown_water();
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
    
    public:
        /* 0x290 */ request_of_phase_process_class mPhs;
        /* 0x298 */ J3DModel* mpModel;
        /* 0x29C */ u8 m29C[0x2A0 - 0x29C];
        /* 0x2A0 */ dBgS_Acch mAcch;
        /* 0x464 */ dBgS_AcchCir mAcchCir;
        /* 0x4A4 */ dBgS_GndChk mGndChk;
        /* 0x4F8 */ u32 m4F8;
        /* 0x4FC */ u32 m4FC;
        /* 0x500 */ u32 m500;
        /* 0x504 */ u8 m504[0x508 - 0x504];
        /* 0x508 */ dCcD_Cyl mCyl;
        /* 0x638 */ dCcD_Stts mStts;
        /* 0x674 */ int mType;
        /* 0x678 */ int m678;
        /* 0x67C */ u16 mSwitchNo;
        /* 0x67E */ u8 m67E[0x67F - 0x67E];
        /* 0x67F */ u8 m67F;
        /* 0x680 */ u8 m680[0x682 - 0x680];
        /* 0x682 */ u8 m682;
        /* 0x683 */ u8 m683;
        /* 0x684 */ u8 m684[0x686 - 0x684];
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
        /* 0x798 */ u8 m798[0x800 - 0x798];
        /* 0x800 */ s16 m800;
        /* 0x802 */ u8 m802[0x814 - 0x802];
        /* 0x814 */ cXyz m814;
        /* 0x820 */ u8 m820[0xF00 - 0x820];
    };  // Size: 0xF00
    
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
