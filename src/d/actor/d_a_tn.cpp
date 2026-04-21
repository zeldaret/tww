/**
 * d_a_tn.cpp
 * Enemy - Darknut / Mini-Boss - Darknut (Tower of the Gods)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_tn.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_jnt_hit.h"
#include "d/d_material.h"
#include "d/d_camera.h"
#include "d/d_meter.h"
#include "d/d_path.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/res/res_tn.h"
#include "JAZelAudio/JAZelAudio_BGM.h"
#include "JAZelAudio/JAZelAudio_SE.h"
#include "JSystem/J3DGraphAnimator/J3DJoint.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "JSystem/JUtility/JUTReport.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_actor_iter.h"
#include "f_pc/f_pc_executor.h"
#include "f_pc/f_pc_searcher.h"

namespace {

class tnHIO_c : public mDoHIO_entry_c {
public:
    tnHIO_c();
    virtual ~tnHIO_c() {}

    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05[4];
    /* 0x09 */ u8 field_0x09[0xD8 - 0x09];
    /* 0xD8 */ JntHit_HIO_c mJntHitHIO;
};

template <typename T>
static inline void init_hio_field(tnHIO_c& hio, size_t offset, T value) {
    *reinterpret_cast<T*>(reinterpret_cast<u8*>(&hio) + offset) = value;
};

tnHIO_c::tnHIO_c() {
    field_0x05[0] = 0;
    field_0x05[1] = 0;
    field_0x05[2] = 0;
    field_0x05[3] = 0;

    init_hio_field<s16>(*this, 0x0A, 50);
    init_hio_field<f32>(*this, 0x0C, 1.0f);
    init_hio_field<f32>(*this, 0x14, 1.0f);
    init_hio_field<f32>(*this, 0x18, 25.0f);
    init_hio_field<s16>(*this, 0x1C, 0);
    init_hio_field<s16>(*this, 0x1E, 0x00B9);
    init_hio_field<s16>(*this, 0x20, 0x000C);
    init_hio_field<f32>(*this, 0x24, 100.0f);
    init_hio_field<f32>(*this, 0x28, 20000.0f);
    init_hio_field<f32>(*this, 0x2C, 400.0f);
    init_hio_field<f32>(*this, 0x30, 250.0f);
    init_hio_field<s16>(*this, 0x34, 0x59D8);
    init_hio_field<s16>(*this, 0x36, 0x2AF8);
    init_hio_field<f32>(*this, 0x38, 400.0f);
    init_hio_field<f32>(*this, 0x3C, 500.0f);
    init_hio_field<f32>(*this, 0x40, 130.0f);
    init_hio_field<f32>(*this, 0x44, 500.0f);
    init_hio_field<f32>(*this, 0x48, -125.0f);
    init_hio_field<f32>(*this, 0x4C, 20.0f);
    init_hio_field<f32>(*this, 0x50, 20.0f);
    init_hio_field<f32>(*this, 0x54, 70.0f);
    init_hio_field<f32>(*this, 0x58, 90.0f);
    init_hio_field<f32>(*this, 0x5C, 10.0f);
    init_hio_field<f32>(*this, 0x60, 10.0f);
    init_hio_field<f32>(*this, 0x64, 70.0f);
    init_hio_field<f32>(*this, 0x68, 1.0f);
    init_hio_field<s16>(*this, 0x6C, 30);
    init_hio_field<f32>(*this, 0x70, 75.0f);
    init_hio_field<f32>(*this, 0x74, 80.0f);
    init_hio_field<f32>(*this, 0x78, 80.0f);
    init_hio_field<f32>(*this, 0x7C, 70.0f);
    init_hio_field<s16>(*this, 0x80, 30);
    init_hio_field<s16>(*this, 0x82, 300);
    init_hio_field<f32>(*this, 0x84, 0.9f);
    init_hio_field<f32>(*this, 0x88, 1.0f);
    init_hio_field<f32>(*this, 0x8C, 1.0f);
    init_hio_field<s16>(*this, 0xC4, 14);
    init_hio_field<f32>(*this, 0x90, 1.0f);
    init_hio_field<f32>(*this, 0x94, 1.0f);
    init_hio_field<f32>(*this, 0x98, 1.0f);
    init_hio_field<s16>(*this, 0xC6, 24);
    init_hio_field<f32>(*this, 0x9C, 1.1f);
    init_hio_field<f32>(*this, 0xA0, 1.0f);
    init_hio_field<f32>(*this, 0xA4, 1.0f);
    init_hio_field<s16>(*this, 0xC8, 22);
    init_hio_field<f32>(*this, 0xA8, 0.5f);
    init_hio_field<f32>(*this, 0xAC, 1.0f);
    init_hio_field<f32>(*this, 0xB0, 1.2f);
    init_hio_field<s16>(*this, 0xCA, 5);
    init_hio_field<f32>(*this, 0xB4, 1.0f);
    init_hio_field<s16>(*this, 0xCC, 100);
    init_hio_field<f32>(*this, 0xB8, 1.0f);
    init_hio_field<f32>(*this, 0xBC, 1.0f);
    init_hio_field<f32>(*this, 0xC0, 1.0f);
    init_hio_field<s16>(*this, 0xCE, 28);
    init_hio_field<f32>(*this, 0xD0, 0.0f);
    init_hio_field<f32>(*this, 0xD4, 500.0f);
}

static u8 hio_set;
static tnHIO_c l_tnHIO;

typedef char tnHIO_c_size_check[sizeof(tnHIO_c) == 0x104 ? 1 : -1];

static s8 joint_check[] = {
    -1, -1, 12, 11, 7, 3, 10, 6, 2, -1, 19, 9, 5, 1, 17, 100, 100,
    100, 8, 4, 0, 16, 20, -1, -1, -1, 13, 18, -1, -1, -1, -1, -1,
};

static s8 search_sp;
static s8 s_check;
static fopAc_ac_c* target_info[10];
static s32 target_info_count;

static Vec kosi_cyl_offset[] = {
    {0.0f, 20.0f, 0.0f},
    {0.0f, -20.0f, 0.0f},
};

static Vec asi_cyl_offset[] = {
    {20.0f, 0.0f, 0.0f},
    {-20.0f, 0.0f, 0.0f},
};

static Vec mune_cyl_offset[] = {
    {30.0f, 0.0f, 0.0f},
    {-10.0f, 0.0f, 0.0f},
};

static Vec kata_l_cyl_offset[] = {
    {40.0f, -5.0f, 0.0f},
    {-20.0f, 0.0f, 0.0f},
};

static Vec kata_r_cyl_offset[] = {
    {40.0f, 5.0f, 0.0f},
    {-20.0f, 0.0f, 0.0f},
};

static Vec kubi_cyl_offset[] = {
    {20.0f, 0.0f, 0.0f},
    {-25.0f, 0.0f, 0.0f},
};

static Vec atama_cyl_offset[] = {
    {40.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f},
};

static Vec mimi_cyl_offset[] = {
    {20.0f, 0.0f, 3.0f},
    {0.0f, 0.0f, 0.0f},
};

static GXColor turn_prim0 = {0x40, 0x40, 0xFF, 0xFF};
static GXColor turn_prim1 = {0xDC, 0xDC, 0xFF, 0xFF};
static GXColor turn_env = {0x78, 0x78, 0xFF, 0xFF};
static GXColor roll_prim0 = {0xC8, 0xFF, 0x40, 0xFF};
static GXColor roll_prim1 = {0xFF, 0xFF, 0xDC, 0xFF};
static GXColor roll_env = {0xC8, 0xFF, 0x78, 0xFF};
static u16 spin_eff_name[] = {0x25, 0x26, 0x28};

static __jnt_hit_data_c search_data[] = {
    {JntHitType_CYL_e, 0x01, 20.0f, kosi_cyl_offset},
    {JntHitType_CYL_THROW_e, 0x03, 10.0f, asi_cyl_offset},
    {JntHitType_CYL_THROW_e, 0x06, 10.0f, asi_cyl_offset},
    {JntHitType_CYL_DELETE_e, 0x1B, 30.0f, kubi_cyl_offset},
    {JntHitType_CYL_DELETE_e, 0x1C, 25.0f, atama_cyl_offset},
    {JntHitType_CYL_DELETE_e, 0x1E, 19.0f, mimi_cyl_offset},
    {JntHitType_CYL_DELETE_e, 0x20, 2.0f, mimi_cyl_offset},
    {JntHitType_CYL_e, 0x0A, 30.0f, mune_cyl_offset},
    {JntHitType_CYL_e, 0x0B, 18.0f, kata_l_cyl_offset},
    {JntHitType_CYL_e, 0x13, 18.0f, kata_r_cyl_offset},
};

struct tn_part_info {
    /* 0x00 */ J3DModel* mpModel;
    /* 0x04 */ mDoExt_brkAnm* mpBrkAnm;
    /* 0x08 */ s8 mState;
};

template <typename T>
static inline T& tn_field(tn_class* i_this, size_t offset) {
    return *reinterpret_cast<T*>(reinterpret_cast<u8*>(i_this) + offset);
}

template <typename T>
static inline T& actor_field(fopAc_ac_c* actor, size_t offset) {
    return *reinterpret_cast<T*>(reinterpret_cast<u8*>(actor) + offset);
}

template <typename T>
static inline T& reg_hio_field(size_t offset) {
    return *reinterpret_cast<T*>(reinterpret_cast<u8*>(&g_regHIO) + offset);
}

template <typename T>
static inline T& tn_hio_field(size_t offset) {
    return *reinterpret_cast<T*>(reinterpret_cast<u8*>(&l_tnHIO) + offset);
}

static inline mDoExt_McaMorf* get_main_morf(tn_class* i_this) {
    return tn_field<mDoExt_McaMorf*>(i_this, 0x2C4);
}

static inline mDoExt_McaMorf* get_tate_morf(tn_class* i_this) {
    return tn_field<mDoExt_McaMorf*>(i_this, 0x2C8);
}

static inline mDoExt_McaMorf* get_yoroi_morf(tn_class* i_this) {
    return tn_field<mDoExt_McaMorf*>(i_this, 0x2CC);
}

static inline s16& get_action_flag(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x3EC);
}

static inline int& get_yari_state(tn_class* i_this) {
    return tn_field<int>(i_this, 0x0C38);
}

static inline int& get_yari_actor_flag(tn_class* i_this) {
    return tn_field<int>(i_this, 0x0C34);
}

static inline fpc_ProcID& get_yari_actor_id(tn_class* i_this) {
    return tn_field<fpc_ProcID>(i_this, 0x1410);
}

static inline cXyz& get_smoke_pos(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x041C);
}

static inline csXyz& get_smoke_angle(tn_class* i_this) {
    return tn_field<csXyz>(i_this, 0x0428);
}

static inline s16& get_smoke_rot(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x042E);
}

static inline s16& get_smoke_timer(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x0430);
}

static inline u8& get_smoke_mode(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x0432);
}

static inline u8& get_smoke_active(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x0433);
}

static inline dPa_smokeEcallBack& get_smoke_cb(tn_class* i_this) {
    return tn_field<dPa_smokeEcallBack>(i_this, 0x0434);
}

static inline f32& get_ground_target_y(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x0B58);
}

static inline csXyz& get_joint_rot(tn_class* i_this, int idx) {
    return tn_field<csXyz>(i_this, 0x04FC + idx * sizeof(csXyz));
}

static inline cXyz& get_joint_pos(tn_class* i_this, int idx) {
    return tn_field<cXyz>(i_this, 0x0574 + idx * sizeof(cXyz));
}

static inline s16& get_head_angle(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x0414);
}

static inline cXyz& get_part_pos_13a8(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x13A8);
}

static inline cXyz& get_part_pos_13b4(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x13B4);
}

static inline cXyz& get_part_pos_0c3c(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x0C3C);
}

static inline cXyz& get_part_pos_139c(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x139C);
}

static inline cXyz& get_part_pos_1390(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x1390);
}

static inline tn_part_info& get_part_info(tn_class* i_this, int idx) {
    return *reinterpret_cast<tn_part_info*>(&i_this->parts[idx]);
}

static inline u32& get_shadow_id(tn_class* i_this) {
    return tn_field<u32>(i_this, 0x02D4);
}

static inline mDoExt_brkAnm* get_main_brk(tn_class* i_this) {
    return tn_field<mDoExt_brkAnm*>(i_this, 0x02D8);
}

static inline J3DModel*& get_part_model(tn_class* i_this) {
    return tn_field<J3DModel*>(i_this, 0x032C);
}

static inline f32& get_acch_ground_y(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x0A24);
}

static inline cBgS_PolyInfo& get_acch_ground_poly(tn_class* i_this) {
    return tn_field<cBgS_PolyInfo>(i_this, 0x0A78);
}

static inline s8& get_draw_skip_flag(tn_class* i_this) {
    return tn_field<s8>(i_this, 0x1518);
}

static inline u8& get_draw_disable_flag(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x02C1);
}

static inline u8& get_shape_hide_flag(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x1400);
}

static inline s16& get_search_mode(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x03FC);
}

static inline f32& get_player_distance(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x0400);
}

static inline fopAc_ac_c*& get_bomb_actor(tn_class* i_this) {
    return tn_field<fopAc_ac_c*>(i_this, 0x1418);
}

static inline u16& get_search_flags(tn_class* i_this) {
    return tn_field<u16>(i_this, 0x141C);
}

static inline u8& get_player_search_state(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x0B87);
}

static inline cXyz& get_waypoint_pos(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x0404);
}

static inline s16& get_view_angle_state(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x0416);
}

static inline s16& get_side_step_angle(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x0418);
}

static inline s16& get_behavior_mode(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x0478);
}

static inline s16& get_behavior_action(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x047A);
}

static inline dCcD_Cyl& get_search_cyl(tn_class* i_this) {
    return tn_field<dCcD_Cyl>(i_this, 0x0D8C);
}

static inline fopAc_ac_c*& get_player_actor(tn_class* i_this) {
    return tn_field<fopAc_ac_c*>(i_this, 0x0B88);
}

static inline u8& get_fight_state_flag(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x0B84);
}

static inline s16& get_target_angle(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x0944);
}

static inline u32& get_status_flags_9b8(tn_class* i_this) {
    return tn_field<u32>(i_this, 0x09B8);
}

static inline s16& get_timer_3e4(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x03E4);
}

static inline s16& get_timer_3e0(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x03E0);
}

static inline s16& get_timer_3e6(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x03E6);
}

static inline s16& get_timer_3e8(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x03E8);
}

static inline s16& get_timer_3ea(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x03EA);
}

static inline s16& get_timer_3ee(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x03EE);
}

static inline u32& get_flags_3d8(tn_class* i_this) {
    return tn_field<u32>(i_this, 0x03D8);
}

static inline u8& get_ground_check_result(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x03FE);
}

static inline s16& get_timer_3f0(tn_class* i_this) {
    return i_this->m03F0;
}

static inline s16& get_timer_3f2(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x03F2);
}

static inline dCcD_Stts& get_cc_stts_0b98(tn_class* i_this) {
    return tn_field<dCcD_Stts>(i_this, 0x0B98);
}

static inline u8& get_path_search_flag(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x13FF);
}

static inline s8& get_path_found_count(tn_class* i_this) {
    return tn_field<s8>(i_this, 0x1424);
}

static inline s8& get_path_point_index(tn_class* i_this) {
    return tn_field<s8>(i_this, 0x1425);
}

static inline s8& get_path_point_step(tn_class* i_this) {
    return tn_field<s8>(i_this, 0x1426);
}

static inline dPath*& get_path_data(tn_class* i_this) {
    return tn_field<dPath*>(i_this, 0x1428);
}

static inline s32& get_shot_search_state(tn_class* i_this) {
    return tn_field<s32>(i_this, 0x1420);
}

static inline fpc_ProcID& get_support_actor_id(tn_class* i_this) {
    return tn_field<fpc_ProcID>(i_this, 0x1448);
}

static inline s32& get_attack_kind(tn_class* i_this) {
    return tn_field<s32>(i_this, 0x0C48);
}

static inline s8& get_attack_counter(tn_class* i_this) {
    return tn_field<s8>(i_this, 0x0C66);
}

static inline s8& get_attack_reverse_flag(tn_class* i_this) {
    return tn_field<s8>(i_this, 0x0C67);
}

static inline u8& get_weapon_hit_flag(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x13FC);
}

static inline u8& get_weapon_swing_started(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x13FD);
}

static inline cXyz& get_weapon_tip_pos_a(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x13C0);
}

static inline cXyz& get_weapon_tip_pos_b(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x13CC);
}

static inline cXyz& get_weapon_tip_pos_prev(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x13D8);
}

static inline dCcD_Sph& get_weapon_sph_a(tn_class* i_this) {
    return tn_field<dCcD_Sph>(i_this, 0x112C);
}

static inline dCcD_Sph& get_weapon_sph_b(tn_class* i_this) {
    return tn_field<dCcD_Sph>(i_this, 0x1258);
}

static inline cXyz& get_guard_effect_scale2d(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x0454);
}

static inline s16& get_mode_timer_14f4(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x14F4);
}

static inline s16& get_mode_timer_14f6(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x14F6);
}

static inline s8& get_fail_hold_flag(tn_class* i_this) {
    return tn_field<s8>(i_this, 0x14F8);
}

static inline s16& get_watch_turn_angle(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x1404);
}

static inline fpc_ProcID& get_watch_target_id(tn_class* i_this) {
    return tn_field<fpc_ProcID>(i_this, 0x1408);
}

static inline u8& get_guard_pose_flag(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x1444);
}

static inline s16& get_hukki_timer_8f4(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x08F4);
}

static inline s16& get_hukki_timer_8fc(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x08FC);
}

static inline s16& get_hukki_timer_8fe(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x08FE);
}

static inline s16& get_hukki_angle_8f6(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x08F6);
}

static inline f32& get_hukki_f32_8e8(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x08E8);
}

static inline f32& get_hukki_f32_8ec(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x08EC);
}

static inline u8& get_timer_1434(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x1434);
}

static inline s16& get_timer_1436(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x1436);
}

static inline cXyz& get_pos_1438(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x1438);
}

static inline u8& get_demo_cam_state(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x14F8);
}

static inline s16& get_demo_cam_timer(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x14FA);
}

static inline cXyz& get_demo_cam_eye(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x14FC);
}

static inline cXyz& get_demo_cam_center(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x1508);
}

static inline f32& get_demo_cam_fovy(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x1514);
}

static inline u32& get_flags_ca0(tn_class* i_this) {
    return tn_field<u32>(i_this, 0x0CA0);
}

static inline cM3dGSph& get_sph_1244(tn_class* i_this) {
    return tn_field<cM3dGSph>(i_this, 0x1244);
}

static inline cXyz& get_pos_604(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x0604);
}

static inline request_of_phase_process_class& get_phase_2ac(tn_class* i_this) {
    return tn_field<request_of_phase_process_class>(i_this, 0x02AC);
}

static inline request_of_phase_process_class& get_phase_2b4(tn_class* i_this) {
    return tn_field<request_of_phase_process_class>(i_this, 0x02B4);
}

static inline u8& get_hio_created_1433(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x1433);
}

static inline JntHit_c*& get_arrow_hit_1b04(tn_class* i_this) {
    return tn_field<JntHit_c*>(i_this, 0x1B04);
}

static inline enemyfire& get_enemy_fire_18dc(tn_class* i_this) {
    return tn_field<enemyfire>(i_this, 0x18DC);
}

static inline void call_vtbl_method_20(void* obj) {
    if (obj == NULL) {
        return;
    }

    void** vtbl = *reinterpret_cast<void***>(obj);
    if (vtbl == NULL || vtbl[0x20 / sizeof(void*)] == NULL) {
        return;
    }

    typedef void (*VirtualFn)(void*);
    reinterpret_cast<VirtualFn>(vtbl[0x20 / sizeof(void*)])(obj);
}

static inline f32& get_f32_b94(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x0B94);
}

static inline u8& get_demo_flag_1519(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x1519);
}

static inline s16& get_angle_20e(tn_class* i_this) {
    return tn_field<s16>(i_this, 0x020E);
}

static inline BOOL is_morf_motion_done(mDoExt_McaMorf* morf) {
    if (((*reinterpret_cast<u8*>(reinterpret_cast<u8*>(morf) + 0x5D) & 1) == 0) &&
        (*reinterpret_cast<f32*>(reinterpret_cast<u8*>(morf) + 0x64) != 0.0f))
    {
        return FALSE;
    }

    return TRUE;
}

static inline f32& get_hukki_pos_a_x(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x05EC);
}

static inline f32& get_hukki_pos_a_z(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x05F4);
}

static inline f32& get_hukki_pos_b_x(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x0610);
}

static inline f32& get_hukki_pos_b_z(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x0618);
}

static inline cXyz& get_hukki_step_vec(tn_class* i_this) {
    return tn_field<cXyz>(i_this, 0x08CC);
}

static inline f32& get_hukki_y_offset(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x08C4);
}

static inline f32& get_fx_f32_298(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x0298);
}

static inline f32& get_fx_f32_29c(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x029C);
}

static inline f32& get_fx_f32_2a0(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x02A0);
}

static inline f32& get_fx_f32_2a4(tn_class* i_this) {
    return tn_field<f32>(i_this, 0x02A4);
}

static inline u8& get_fx_u8_2a8(tn_class* i_this) {
    return tn_field<u8>(i_this, 0x02A8);
}

static inline BOOL check_player_special_state(fopAc_ac_c* actor) {
    if (actor == NULL) {
        return FALSE;
    }

    typedef BOOL (*PlayerCheckFn)(fopAc_ac_c*);
    void** vtable = *reinterpret_cast<void***>(actor);
    return reinterpret_cast<PlayerCheckFn>(vtable[0x30 / sizeof(void*)])(actor);
}

} // namespace

/* 000000EC-00000220       .text anm_init__FP8tn_classifUcfi */
void anm_init(tn_class* i_this, int bckFileIdx, float morf, unsigned char loopMode, float speed, int soundFileIdx) {
    if (get_action_flag(i_this) != 0) {
        return;
    }

    if (soundFileIdx >= 0) {
        get_main_morf(i_this)->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Tn", bckFileIdx), loopMode, morf, speed, 0.0f,
            -1.0f, dComIfG_getObjectRes("Tn", soundFileIdx));
    } else {
        get_main_morf(i_this)->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Tn", bckFileIdx), loopMode, morf, speed, 0.0f,
            -1.0f, NULL);
    }
}

/* 00000220-000002D4       .text tate_anm_init__FP8tn_classifUcf */
void tate_anm_init(tn_class* i_this, int bckFileIdx, float morf, unsigned char loopMode, float speed) {
    if (get_action_flag(i_this) != 0) {
        return;
    }

    get_tate_morf(i_this)->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectRes("Tn", bckFileIdx), loopMode, morf, speed, 0.0f,
        -1.0f, NULL);
}

/* 000002D4-00000398       .text yoroi_anm_init__FP8tn_classifUcf */
void yoroi_anm_init(tn_class* i_this, int bckFileIdx, float morf, unsigned char loopMode, float speed) {
    if (get_action_flag(i_this) != 0) {
        return;
    }

    if (!(i_this->mRemainingEquipmentPieces & 1)) {
        return;
    }

    get_yoroi_morf(i_this)->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectRes("Tn", bckFileIdx), loopMode, morf, speed, 0.0f,
        -1.0f, NULL);
}

/* 00000398-00000730       .text yari_off_check__FP8tn_class */
void yari_off_check(tn_class* i_this) {
    if (get_yari_state(i_this) == 0) {
        return;
    }

    fopAc_ac_c* yari_actor = fopAcM_SearchByID(get_yari_actor_id(i_this));
    if (yari_actor != NULL) {
        fopAcM_cancelCarryNow(yari_actor);

        if (get_yari_state(i_this) != 2) {
            actor_field<s16>(yari_actor, 0x2C2) = (s16)cM_rndFX(2000.0f);

            s16 angle = i_this->shape_angle.y + 0x8000 + (s16)cM_rndFX(8000.0f);
            yari_actor->speed.y = 20.0f + cM_rndF(20.0f);
            yari_actor->speedF = 20.0f + cM_rndF(10.0f);
            yari_actor->current.angle.y = angle;
        }

        dBgS_LinChk linChk;
        linChk.Set(&i_this->eyePos, &yari_actor->current.pos, i_this);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            MTXCopy(get_main_morf(i_this)->getModel()->getAnmMtx(0x10), *calc_mtx);

            void* extra_mtx_owner = actor_field<void*>(yari_actor, 0x298);
            if (extra_mtx_owner != NULL) {
                MTXCopy(*calc_mtx, reinterpret_cast<MtxP>(reinterpret_cast<u8*>(extra_mtx_owner) + 0x24));
            }

            cXyz zero(0.0f, 0.0f, 0.0f);
            MtxPosition(&zero, &yari_actor->current.pos);
        }

        fopAcM_monsSeStart(i_this, 0x488C, &i_this->eyePos, 0);
    }

    get_yari_state(i_this) = 0;
    get_yari_actor_flag(i_this) = 0;
}

/* 00000BA4-00001074       .text smoke_set_s__FP8tn_classf */
void smoke_set_s(tn_class* i_this, float rate) {
    dBgS_LinChk linChk;
    s32 attribCode = 0;

    cXyz startPos = get_smoke_pos(i_this);
    startPos.y += 100.0f;
    cXyz endPos = get_smoke_pos(i_this);
    endPos.y -= 100.0f;

    linChk.Set(&startPos, &endPos, i_this);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        endPos = linChk.GetCross();
        get_smoke_pos(i_this).y = endPos.y;
        attribCode = dComIfG_Bgsp()->GetAttributeCode(linChk);
    } else {
        get_smoke_pos(i_this).y -= 20000.0f;
    }

    if (get_smoke_active(i_this) != 0 && attribCode != dBgS_Attr_GRASS_e) {
        return;
    }

    get_smoke_active(i_this)++;

    switch (attribCode) {
    case dBgS_Attr_NORMAL_e:
    case dBgS_Attr_DIRT_e:
    case dBgS_Attr_WOOD_e:
    case dBgS_Attr_STONE_e:
    case dBgS_Attr_SAND_e: {
        get_smoke_cb(i_this).remove();
        JPABaseEmitter* emitter = dComIfGp_particle_setToon(
            dPa_name::ID_AK_JT_ELEMENTSMOKE00, &get_smoke_pos(i_this), &get_smoke_angle(i_this),
            NULL, (u8)tn_hio_field<s16>(0x1E), &get_smoke_cb(i_this), fopAcM_GetRoomNo(i_this));
        if (emitter != NULL) {
            emitter->setRate(rate);
            emitter->setSpread(1.0f);

            JGeometry::TVec3<f32> scale;
            scale.x = scale.y = scale.z = 1.0f + reg_hio_field<f32>(0x58);
            emitter->setGlobalScale(scale);

            scale.x = scale.y = scale.z = 3.0f + reg_hio_field<f32>(0x38);
            emitter->setGlobalParticleScale(scale);
        }
        break;
    }
    case dBgS_Attr_GRASS_e: {
        JPABaseEmitter* emitter = dComIfGp_particle_set(
            dPa_name::ID_AK_JN_ELEMENTKUSA00, &get_smoke_pos(i_this), &get_smoke_angle(i_this));
        if (emitter != NULL) {
            emitter->setRate(rate * 0.5f);
            emitter->setMaxFrame(3);
        }
        break;
    }
    }
}

/* 00001074-00001244       .text ground_smoke_set__FP8tn_class */
void ground_smoke_set(tn_class* i_this) {
    if (get_smoke_timer(i_this) == 0) {
        return;
    }

    get_smoke_timer(i_this)--;
    if (get_smoke_timer(i_this) >= tn_hio_field<s16>(0x20)) {
        get_smoke_angle(i_this).x = 0;
        get_smoke_angle(i_this).z = 0;

        cXyz offset(0.0f, 0.0f, 0.0f);
        MtxTrans(i_this->current.pos.x, i_this->current.pos.y + 7.5f, i_this->current.pos.z, 0);

        if (get_smoke_mode(i_this) == 0) {
            offset.z = -200.0f;
            cMtx_YrotM(*calc_mtx, get_smoke_rot(i_this));
            MtxPosition(&offset, &get_smoke_pos(i_this));
            get_smoke_angle(i_this).y = get_smoke_rot(i_this);
            smoke_set_s(i_this, 3.0f + reg_hio_field<f32>(0x48));
            get_smoke_rot(i_this) += reg_hio_field<s16>(0x92) + 0x07D0;
        } else if (get_smoke_mode(i_this) == 1) {
            cMtx_YrotM(*calc_mtx, i_this->shape_angle.y);
            cMtx_YrotM(*calc_mtx, get_smoke_rot(i_this));
            offset.z = -53.0f;
            MtxPosition(&offset, &get_smoke_pos(i_this));
            get_smoke_angle(i_this).y = get_smoke_rot(i_this);
            smoke_set_s(i_this, 4.0f + reg_hio_field<f32>(0x5C));
            get_smoke_rot(i_this) += 0x1FA0;
        }
    } else {
        get_smoke_pos(i_this).y = get_ground_target_y(i_this) - 200.0f;
    }

    if (get_smoke_timer(i_this) == 0) {
        get_smoke_cb(i_this).remove();
        get_smoke_active(i_this) = 0;
    }
}

/* 00001244-0000149C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        s32 jointNo = joint_check[jntNo];
        J3DModel* model = j3dSys.getModel();
        tn_class* i_this = (tn_class*)model->getUserArea();

        if (i_this != NULL) {
            if (jntNo >= 0x0B && jntNo < 0x12 && (i_this->mRemainingEquipmentPieces & 4) &&
                i_this->mEnemyIce.mFreezeTimer == 0)
            {
                MTXCopy(get_tate_morf(i_this)->getModel()->getAnmMtx(jntNo), model->getAnmMtx(jntNo));
            }

            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);

            if (jointNo < 100) {
                cMtx_YrotM(*calc_mtx, get_joint_rot(i_this, jointNo).y);
                cMtx_XrotM(*calc_mtx, get_joint_rot(i_this, jointNo).x);
                cMtx_ZrotM(*calc_mtx, get_joint_rot(i_this, jointNo).z);
            }

            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);

            cXyz offset(0.0f, 0.0f, 0.0f);
            if (jointNo == 0x12) {
                offset.z = 200.0f;
                cXyz neckTarget;
                MtxPosition(&offset, &neckTarget);

                offset.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&offset, &i_this->eyePos);
                i_this->attention_info.position = i_this->eyePos;
                i_this->attention_info.position.y += tn_hio_field<f32>(0x24);
                get_head_angle(i_this) = cM_atan2s(
                    neckTarget.x - i_this->eyePos.x, neckTarget.z - i_this->eyePos.z);

                offset.x = 20.75f;
                offset.y = 0.0f;
                offset.z = -45.0f;
                MtxPosition(&offset, &i_this->m1384);
            }

            if (jointNo < 100) {
                MtxPosition(&offset, &get_joint_pos(i_this, jointNo));
            }
        }
    }

    return TRUE;
}

/* 0000149C-00001630       .text nodeCallBack_P__FP7J3DNodei */
static BOOL nodeCallBack_P(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        s32 jointNo = joint_check[jntNo];
        J3DModel* model = j3dSys.getModel();
        tn_class* i_this = (tn_class*)model->getUserArea();

        if (i_this != NULL) {
            if (jntNo >= 0x0B && jntNo < 0x12 && (i_this->mRemainingEquipmentPieces & 4) &&
                i_this->mEnemyIce.mFreezeTimer == 0)
            {
                MTXCopy(get_tate_morf(i_this)->getModel()->getAnmMtx(jntNo), model->getAnmMtx(jntNo));
                MTXCopy(model->getAnmMtx(jntNo), J3DSys::mCurrentMtx);
            }

            if (jointNo < 100) {
                MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);

                cXyz offset(0.0f, 0.0f, 0.0f);
                if (jointNo == 0x11) {
                    offset.x = 17.5f;
                    offset.y = -8.75f;
                    MtxPosition(&offset, &get_part_pos_13a8(i_this));
                } else if (jointNo == 0x10) {
                    MtxPosition(&offset, &get_part_pos_13b4(i_this));
                } else if (jointNo == 0x14) {
                    MtxPosition(&offset, &get_part_pos_0c3c(i_this));

                    offset.x = -50.0f;
                    MtxPosition(&offset, &get_part_pos_139c(i_this));

                    offset.x = 165.0f;
                    MtxPosition(&offset, &get_part_pos_1390(i_this));
                }

                MtxPosition(&offset, &get_joint_pos(i_this, jointNo));
            }
        }
    }

    return TRUE;
}

/* 00001630-000016F0       .text nodeCallBack_mimi__FP7J3DNodei */
static BOOL nodeCallBack_mimi(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        tn_class* i_this = (tn_class*)model->getUserArea();

        if (i_this != NULL && (i_this->mRemainingEquipmentPieces & 2)) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cMtx_YrotM(*calc_mtx, -0x8000);
            model->setAnmMtx(jntNo, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }

    return TRUE;
}

/* 000016F0-00001770       .text nodeCallBack_kata__FP7J3DNodei */
static BOOL nodeCallBack_kata(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        tn_class* i_this = (tn_class*)model->getUserArea();

        if (i_this != NULL) {
            MTXCopy(get_main_morf(i_this)->getModel()->getAnmMtx(jntNo), model->getAnmMtx(jntNo));
            MTXCopy(model->getAnmMtx(jntNo), J3DSys::mCurrentMtx);
        }
    }

    return TRUE;
}

/* 00001770-000018B0       .text part_draw__FP8tn_classSc */
void part_draw(tn_class* i_this, signed char frozen) {
    for (int i = 0; i < 3; i++) {
        tn_part_info& part = get_part_info(i_this, i);
        if (part.mState < 0) {
            continue;
        }

        if (i == 0) {
            if (frozen != 0) {
                dMat_control_c::iceEntryDL(get_yoroi_morf(i_this), -1, NULL);
            } else {
                J3DModel* model = get_yoroi_morf(i_this)->getModel();
                part.mpBrkAnm->entry(model->getModelData());
                g_env_light.setLightTevColorType(model, &i_this->tevStr);
                get_yoroi_morf(i_this)->entryDL();
            }

            continue;
        }

        if (i == 2 && !(i_this->mRemainingEquipmentPieces & 4)) {
            continue;
        }

        J3DModel* model = part.mpModel;
        if (frozen != 0) {
            dMat_control_c::iceUpdateDL(model, -1, NULL);
        } else {
            if (i < 3) {
                part.mpBrkAnm->entry(model->getModelData());
            }

            g_env_light.setLightTevColorType(model, &i_this->tevStr);
            mDoExt_modelUpdateDL(model);
        }
    }
}

/* 000018B0-00001B7C       .text daTn_Draw__FP8tn_class */
static BOOL daTn_Draw(tn_class* i_this) {
    J3DModel* model = get_main_morf(i_this)->getModel();

    if (get_draw_skip_flag(i_this) != 0 || get_draw_disable_flag(i_this) != 0) {
        return TRUE;
    }

    if (i_this->mEnemyIce.mFreezeTimer > 20) {
        dMat_control_c::iceEntryDL(get_main_morf(i_this), -1, NULL);
        part_draw(i_this, 1);
        return TRUE;
    }

    if (i_this->mEquipmentType >= 4) {
        dSnap_RegistFig(0xC1, i_this, 1.0f, 1.0f, 1.0f);
    } else if (i_this->mRemainingEquipmentPieces & 4) {
        dSnap_RegistFig(0xC0, i_this, 1.0f, 1.0f, 1.0f);
    } else {
        dSnap_RegistFig(0xBF, i_this, 1.0f, 1.0f, 1.0f);
    }

    g_env_light.setLightTevColorType(model, &i_this->tevStr);
    get_main_brk(i_this)->entry(model->getModelData());

    J3DShape* faceShape = model->getModelData()->getMaterialNodePointer(0)->getShape();
    if (reg_hio_field<s16>(0x86) != 0 || get_shape_hide_flag(i_this) != 0) {
        faceShape->hide();
    } else {
        faceShape->show();
    }

    get_main_morf(i_this)->entryDL();

    cXyz shadowPos(i_this->current.pos.x, i_this->current.pos.y + 300.0f + reg_hio_field<f32>(0x4D4),
                   i_this->current.pos.z);
    get_shadow_id(i_this) = dComIfGd_setShadow(
        get_shadow_id(i_this), 1, model, &shadowPos, 1300.0f + reg_hio_field<f32>(0x4D8),
        200.0f, i_this->current.pos.y, get_acch_ground_y(i_this), get_acch_ground_poly(i_this),
        &i_this->tevStr);

    if (get_shadow_id(i_this) != 0) {
        if (get_yari_actor_flag(i_this) != 0) {
            fopAc_ac_c* yariActor = fopAcM_SearchByID(get_yari_actor_id(i_this));
            if (yariActor != NULL) {
                J3DModel* yariModel = actor_field<J3DModel*>(yariActor, 0x24C);
                if (yariModel != NULL) {
                    dComIfGd_addRealShadow(get_shadow_id(i_this), yariModel);
                }
            }
        }

        if (i_this->mRemainingEquipmentPieces & 2) {
            dComIfGd_addRealShadow(get_shadow_id(i_this), get_part_model(i_this));
        }

        if (i_this->mRemainingEquipmentPieces & 1) {
            dComIfGd_addRealShadow(get_shadow_id(i_this), get_yoroi_morf(i_this)->getModel());
        }

        if (i_this->mRemainingEquipmentPieces & 4) {
            dComIfGd_addRealShadow(get_shadow_id(i_this), get_tate_morf(i_this)->getModel());
        }
    }

    part_draw(i_this, 0);
    return TRUE;
}

/* 00001B7C-00002020       .text way_pos_check__FP8tn_classP4cXyz */
static void way_pos_check(tn_class* i_this, cXyz* outPos) {
    dBgS_LinChk linChk;
    dBgS_GndChk gndChk;
    cXyz offset(0.0f, 50.0f, 0.0f);
    cXyz rotated;
    cXyz start = i_this->current.pos;
    start.y += 50.0f;

    for (int i = 0; i < 100; i++) {
        offset.z = 300.0f + cM_rndF(200.0f);
        MtxRotY(cM_rndF(6.2831855f), 0);
        MtxPosition(&offset, &rotated);

        outPos->x = i_this->current.pos.x + rotated.x;
        outPos->y = i_this->current.pos.y + rotated.y;
        outPos->z = i_this->current.pos.z + rotated.z;

        linChk.Set(&start, outPos, i_this);
        if (!dComIfG_Bgsp()->LineCross(&linChk)) {
            gndChk.SetPos(outPos);
            if (get_acch_ground_y(i_this) - dComIfG_Bgsp()->GroundCross(&gndChk) < 200.0f) {
                break;
            }
        }
    }
}

/* 000021B8-00002480       .text ground_4_check__FP8tn_classisf */
static u8 ground_4_check(tn_class* i_this, int count, s16 angle, f32 dist) {
    static f32 xad[] = {0.0f, 0.0f, 1.0f, -1.0f};
    static f32 zad[] = {1.0f, -1.0f, 0.0f, 0.0f};
    static u8 check_bit[] = {0x01, 0x02, 0x04, 0x08};

    dBgS_GndChk gndChk;
    u8 result = 0;

    mDoMtx_YrotS(*calc_mtx, angle);

    cXyz offset;
    offset.y = 100.0f;

    for (int i = 0; i < count; i++) {
        offset.x = xad[i] * dist;
        offset.z = zad[i] * dist;

        cXyz checkPos;
        MtxPosition(&offset, &checkPos);
        checkPos += i_this->current.pos;

        gndChk.SetPos(&checkPos);
        checkPos.y = dComIfG_Bgsp()->GroundCross(&gndChk);
        if (checkPos.y == -G_CM3D_F_INF) {
            checkPos.y = G_CM3D_F_INF;
        }

        if (get_acch_ground_y(i_this) - checkPos.y > 200.0f) {
            result |= check_bit[i];
        }
    }

    return result;
}

/* 00002480-00002870       .text daTn_other_bg_check__FP8tn_classP10fopAc_ac_c */
static BOOL daTn_other_bg_check(tn_class* i_this, fopAc_ac_c* actor) {
    if (actor == NULL) {
        return TRUE;
    }

    dBgS_LinChk linChk;
    cXyz end = actor->current.pos;
    end.y += 50.0f;
    cXyz start = i_this->eyePos;
    linChk.Set(&start, &end, i_this);
    return dComIfG_Bgsp()->LineCross(&linChk) ? TRUE : FALSE;
}

/* 00002870-0000289C       .text get_view_H__FP8tn_class */
static s16 get_view_H(tn_class* i_this) {
    return (i_this->mRemainingEquipmentPieces & 2) != 0 ? tn_hio_field<s16>(0x36)
                                                         : tn_hio_field<s16>(0x34);
}

/* 0000289C-00002918       .text s_w_sub__FPvPv */
static void* s_w_sub(void* actor, void*) {
    if (fopAc_IsActor(actor) && fopAcM_GetName((fopAc_ac_c*)actor) == PROC_BOKO &&
        !fopAcM_checkCarryNow((fopAc_ac_c*)actor))
    {
        if (target_info_count < (s32)ARRAY_SIZE(target_info)) {
            target_info[target_info_count] = (fopAc_ac_c*)actor;
            target_info_count++;
        }
    }

    return NULL;
}

/* 00002918-00002BF4       .text search_wepon__FP8tn_class */
static fpc_ProcID search_wepon(tn_class* i_this) {
    target_info_count = 0;
    for (int i = 0; i < (s32)ARRAY_SIZE(target_info); i++) {
        target_info[i] = NULL;
    }

    fpcM_Search(s_w_sub, i_this);

    f32 distanceLimit = 50.0f;
    if (target_info_count == 0) {
        return fpcM_ERROR_PROCESS_ID_e;
    }

    int idx = 0;
    while (idx < target_info_count) {
        fopAc_ac_c* target = target_info[idx];
        cXyz rel;
        rel.x = target->current.pos.x - i_this->eyePos.x;
        rel.y = 50.0f + target->current.pos.y - i_this->eyePos.y;
        rel.z = target->current.pos.z - i_this->eyePos.z;

        f32 distanceXZ = std::sqrtf(rel.x * rel.x + rel.z * rel.z);
        if (distanceXZ < distanceLimit && !daTn_other_bg_check(i_this, target)) {
            if (std::fabsf(target->current.pos.y + 50.0f - i_this->eyePos.y) <= tn_hio_field<f32>(0x38)) {
                s16 angleDiff = get_head_angle(i_this) - cM_atan2s(rel.x, rel.z);
                if (angleDiff < 0) {
                    angleDiff = -angleDiff;
                }

                if ((u16)angleDiff < 0x1800) {
                    return target != NULL ? fopAcM_GetID(target) : fpcM_ERROR_PROCESS_ID_e;
                }

                mDoMtx_YrotS(*calc_mtx, -i_this->current.angle.y);
                cXyz local;
                MtxPosition(&rel, &local);
                if (std::fabsf(local.x) < tn_hio_field<f32>(0x3C) &&
                    std::fabsf(local.y) < tn_hio_field<f32>(0x40) &&
                    local.z > tn_hio_field<f32>(0x48) &&
                    local.z < tn_hio_field<f32>(0x44))
                {
                    return target != NULL ? fopAcM_GetID(target) : fpcM_ERROR_PROCESS_ID_e;
                }
            }
        }

        idx++;
        if (idx == target_info_count) {
            idx = 0;
            distanceLimit += 50.0f;
            if (distanceLimit > 1500.0f) {
                return fpcM_ERROR_PROCESS_ID_e;
            }
        }
    }

    return fpcM_ERROR_PROCESS_ID_e;
}

/* 00002BF4-00002C78       .text s_b_sub__FPvPv */
static void* s_b_sub(void* actor, void*) {
    if (fopAc_IsActor(actor) && fopAcM_GetName((fopAc_ac_c*)actor) == PROC_BOMB &&
        !((daBomb_c*)actor)->chk_state(daBomb_c::STATE_0))
    {
        if (target_info_count < (s32)ARRAY_SIZE(target_info)) {
            target_info[target_info_count] = (fopAc_ac_c*)actor;
            target_info_count++;
        }
    }

    return NULL;
}

/* 00002C78-00002F84       .text search_bomb__FP8tn_classi */
static fopAc_ac_c* search_bomb(tn_class* i_this, int checkView) {
    if ((get_search_flags(i_this) & 0x0200) == 0) {
        return NULL;
    }

    target_info_count = 0;
    for (int i = 0; i < (s32)ARRAY_SIZE(target_info); i++) {
        target_info[i] = NULL;
    }

    fpcM_Search(s_b_sub, i_this);

    f32 distanceLimit = 50.0f;
    if (target_info_count == 0) {
        return NULL;
    }

    int idx = 0;
    while (idx < target_info_count) {
        fopAc_ac_c* target = target_info[idx];
        cXyz eyeRel;
        eyeRel.x = target->current.pos.x - i_this->eyePos.x;
        eyeRel.y = 50.0f + target->current.pos.y - i_this->eyePos.y;
        eyeRel.z = target->current.pos.z - i_this->eyePos.z;

        cXyz posRel;
        posRel.x = target->current.pos.x - i_this->current.pos.x;
        posRel.z = target->current.pos.z - i_this->current.pos.z;

        f32 eyeDistance = std::sqrtf(eyeRel.x * eyeRel.x + eyeRel.z * eyeRel.z);
        f32 posDistance = std::sqrtf(posRel.x * posRel.x + posRel.z * posRel.z);
        if (eyeDistance < distanceLimit && !(posDistance > 30.0f + get_player_distance(i_this)) &&
            !(daTn_other_bg_check(i_this, target) && checkView))
        {
            if (checkView != 0) {
                if (std::fabsf(target->current.pos.y + 50.0f - i_this->eyePos.y) <= tn_hio_field<f32>(0x38)) {
                    s16 angleDiff = get_head_angle(i_this) - cM_atan2s(eyeRel.x, eyeRel.z);
                    if (angleDiff < 0) {
                        angleDiff = -angleDiff;
                    }

                    if ((u16)angleDiff < (u16)get_view_H(i_this)) {
                        return target;
                    }

                    mDoMtx_YrotS(*calc_mtx, -i_this->current.angle.y);
                    cXyz local;
                    MtxPosition(&eyeRel, &local);
                    if (std::fabsf(local.x) < tn_hio_field<f32>(0x3C) &&
                        std::fabsf(local.y) < tn_hio_field<f32>(0x40) &&
                        local.z > tn_hio_field<f32>(0x48) &&
                        local.z < tn_hio_field<f32>(0x44))
                    {
                        return target;
                    }
                }
            } else {
                return target;
            }
        }

        idx++;
        if (idx == target_info_count) {
            idx = 0;
            distanceLimit += 50.0f;
            if (distanceLimit > 1500.0f) {
                return NULL;
            }
        }
    }

    return NULL;
}

/* 00002F84-00002FD8       .text daTn_bomb_view_check__FP8tn_class */
static BOOL daTn_bomb_view_check(tn_class* i_this) {
    if (i_this->mRemainingEquipmentPieces & 1) {
        return FALSE;
    }

    get_bomb_actor(i_this) = search_bomb(i_this, TRUE);
    return get_bomb_actor(i_this) != NULL ? TRUE : FALSE;
}

/* 00002FD8-00003018       .text daTn_bomb_check__FP8tn_class */
static BOOL daTn_bomb_check(tn_class* i_this) {
    get_bomb_actor(i_this) = search_bomb(i_this, FALSE);
    return get_bomb_actor(i_this) != NULL ? TRUE : FALSE;
}

/* 00003018-00003094       .text daTn_wepon_view_check__FP8tn_class */
static BOOL daTn_wepon_view_check(tn_class* i_this) {
    if (get_search_mode(i_this) != 0) {
        return FALSE;
    }

    get_yari_actor_id(i_this) = search_wepon(i_this);
    if (get_yari_actor_id(i_this) != fpcM_ERROR_PROCESS_ID_e &&
        fopAcM_SearchByID(get_yari_actor_id(i_this)) != NULL)
    {
        return TRUE;
    }

    return FALSE;
}

/* 00003094-000033E8       .text daTn_player_bg_check__FP8tn_classP4cXyz */
static BOOL daTn_player_bg_check(tn_class* i_this, cXyz* pos) {
    if (search_sp != 0) {
        return FALSE;
    }

    dBgS_LinChk linChk;
    cXyz end = *pos;
    end.y += 75.0f;
    cXyz start = i_this->current.pos;
    start.y = i_this->eyePos.y;

    linChk.Set(&start, &end, i_this);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        get_player_search_state(i_this) = 0;
        return TRUE;
    }

    return FALSE;
}

/* 000033E8-00003598       .text daTn_player_view_check__FP8tn_classP4cXyzss */
static BOOL daTn_player_view_check(tn_class* i_this, cXyz* pos, s16 angle, s16 viewAngle) {
    daPy_py_c* player = daPy_getPlayerActorClass();

    if (search_sp != 0) {
        return TRUE;
    }

    if (daTn_player_bg_check(i_this, pos)) {
        return FALSE;
    }

    if (std::fabsf(player->current.pos.y + 50.0f - i_this->eyePos.y) > tn_hio_field<f32>(0x38)) {
        return FALSE;
    }

    s16 angleDiff = get_head_angle(i_this) - angle;
    if (angleDiff < 0) {
        angleDiff = -angleDiff;
    }

    if ((u16)angleDiff < (u16)viewAngle) {
        get_player_search_state(i_this) = 1;
        return TRUE;
    }

    mDoMtx_YrotS(*calc_mtx, -i_this->current.angle.y);
    cXyz rel(pos->x - i_this->current.pos.x, pos->y - i_this->current.pos.y,
             pos->z - i_this->current.pos.z);
    cXyz local;
    MtxPosition(&rel, &local);

    if (std::fabsf(local.x) < tn_hio_field<f32>(0x3C) &&
        std::fabsf(local.y) < tn_hio_field<f32>(0x40) &&
        local.z > tn_hio_field<f32>(0x48) &&
        local.z < tn_hio_field<f32>(0x44))
    {
        get_player_search_state(i_this) = 2;
        return TRUE;
    }

    get_player_search_state(i_this) = 0;
    return FALSE;
}

/* 00003598-000035DC       .text daTn_player_way_check__FP8tn_class */
static BOOL daTn_player_way_check(tn_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    s16 angleDiff = i_this->current.angle.y - player->shape_angle.y;
    if (angleDiff < 0) {
        angleDiff = -angleDiff;
    }

    return (u16)angleDiff >= 0x4000 ? TRUE : FALSE;
}

/* 000035DC-00003664       .text wait_set__FP8tn_class */
static void wait_set(tn_class* i_this) {
    anm_init(i_this, 0x37, 75.0f, 2, 1.0f, -1);
    yoroi_anm_init(i_this, 0x65, 75.0f, 2, 1.0f);
    i_this->m03E2 = (s16)(50.0f + cM_rndF(30.0f));
}

/* 00003664-000036CC       .text walk_set__FP8tn_class */
static void walk_set(tn_class* i_this) {
    anm_init(i_this, 0x3E, 10.0f, 2, 1.0f, 0x11);
    yoroi_anm_init(i_this, 0x67, 10.0f, 2, 1.0f);
}

/* 000036CC-0000379C       .text fight_run_set__FP8tn_class */
static void fight_run_set(tn_class* i_this) {
    if (i_this->mRemainingEquipmentPieces & 1) {
        anm_init(i_this, 0x3E, 5.0f, 2, 1.5f, 0x11);
        yoroi_anm_init(i_this, 0x67, 5.0f, 2, 1.5f);
        return;
    }

    if (get_yari_actor_flag(i_this) != 0) {
        anm_init(i_this, 0x50, 5.0f, 2, 1.0f, 0x20);
    } else {
        anm_init(i_this, 0x51, 5.0f, 2, 1.0f, 0x21);
    }

    yoroi_anm_init(i_this, 0x64, 5.0f, 0, 1.0f);
}

/* 0000379C-00003C0C       .text path_check__FP8tn_class */
void path_check(tn_class* i_this) {
    if (get_path_data(i_this) == NULL) {
        return;
    }

    if (get_yari_actor_flag(i_this) == 0 && get_path_search_flag(i_this) == 0) {
        return;
    }

    u8 checkIndex[0x100] = {};
    cXyz start = i_this->current.pos;
    start.y += 100.0f;

    dPnt* point = get_path_data(i_this)->m_points;
    for (int i = 0; i < get_path_data(i_this)->m_num; i++, point++) {
        cXyz end = point->m_position;
        end.y += 100.0f;

        dBgS_LinChk linChk;
        linChk.Set(&start, &end, i_this);
        checkIndex[i] = dComIfG_Bgsp()->LineCross(&linChk) ? 0 : 1;
    }

    f32 distLimit = 0.0f;
    BOOL found = FALSE;

    for (int i = 0; i < 100 && !found; i++, distLimit += 50.0f) {
        point = get_path_data(i_this)->m_points;
        for (int j = 0; j < get_path_data(i_this)->m_num; j++, point++) {
            if (checkIndex[j] == 0) {
                continue;
            }

            cXyz diff = i_this->current.pos - point->m_position;
            if (diff.abs() < distLimit) {
                get_path_point_index(i_this) = j - get_path_point_step(i_this);
                if (get_path_point_index(i_this) >= (s8)get_path_data(i_this)->m_num) {
                    get_path_point_index(i_this) = get_path_data(i_this)->m_num;
                } else if (get_path_point_index(i_this) < 0) {
                    get_path_point_index(i_this) = 0;
                }

                found = TRUE;
                break;
            }
        }
    }

    if (!found) {
        get_path_found_count(i_this) = 0;
    } else {
        get_path_found_count(i_this) = i_this->mPathIndex + 1;
    }
}

/* 00003C0C-00004388       .text jyunkai__FP8tn_class */
void jyunkai(tn_class* i_this) {
    get_search_cyl(i_this).SetR(40.0f + reg_hio_field<f32>(0x44));

    if (i_this->mBehaviorType == 4) {
        get_behavior_action(i_this) = 1;
        get_behavior_mode(i_this) = 50;
        return;
    }

    switch (get_behavior_mode(i_this)) {
    case -10:
        i_this->m03E2 = 60;
        get_behavior_mode(i_this) = -9;
        // fallthrough
    case -9:
        if (i_this->m03E2 == 0) {
            get_behavior_mode(i_this) = 2;
        }

        i_this->speedF = 0.0f;
        if (i_this->m03E2 > 30) {
            return;
        }
        break;

    case -1:
        walk_set(i_this);
        // fallthrough
    case 0:
        get_behavior_mode(i_this) = 1;

        if (get_yari_actor_flag(i_this) != 0 || get_path_search_flag(i_this) != 0) {
            if (get_path_found_count(i_this) != 0) {
                get_path_point_index(i_this) += get_path_point_step(i_this);
                if (get_path_point_index(i_this) >= (s8)get_path_data(i_this)->m_num) {
                    if (dPath_ChkClose(get_path_data(i_this))) {
                        get_path_point_index(i_this) = 0;
                    } else {
                        get_path_point_step(i_this) = -1;
                        get_path_point_index(i_this) = get_path_data(i_this)->m_num - 2;
                    }

                    if ((s32)get_path_data(i_this)->m_nextID != 0xFFFF) {
                        get_path_data(i_this) = dPath_GetRoomPath(get_path_data(i_this)->m_nextID,
                                                                 fopAcM_GetRoomNo(i_this));
                        JUT_ASSERT(0x7C2, get_path_data(i_this) != NULL);
                    }
                } else if (get_path_point_index(i_this) < 0) {
                    get_path_point_step(i_this) = 1;
                    get_path_point_index(i_this) = 1;
                }

                dPnt* point = &get_path_data(i_this)->m_points[get_path_point_index(i_this)];
                get_waypoint_pos(i_this) = point->m_position;
            } else {
                way_pos_check(i_this, &get_waypoint_pos(i_this));
            }
        } else {
            way_pos_check(i_this, &get_waypoint_pos(i_this));
            i_this->m03E2 = (s16)(30.0f + cM_rndF(25.0f));
        }

        get_timer_3e4(i_this) = 30;
        break;

    case 1: {
        s16 angleStep;
        f32 targetSpeed;
        if (get_yari_actor_flag(i_this) != 0 || get_path_search_flag(i_this) != 0) {
            angleStep = 0x0400;
            targetSpeed = tn_hio_field<f32>(0x4C);
        } else {
            angleStep = 0x1000;
            targetSpeed = tn_hio_field<f32>(0x50);
        }

        cXyz rel(get_waypoint_pos(i_this).x - i_this->current.pos.x, 0.0f,
                 get_waypoint_pos(i_this).z - i_this->current.pos.z);
        get_target_angle(i_this) = cM_atan2s(rel.x, rel.z);

        if (get_path_found_count(i_this) != 0 &&
            (get_yari_actor_flag(i_this) != 0 || get_path_search_flag(i_this) != 0))
        {
            if (std::sqrtf(rel.x * rel.x + rel.z * rel.z) < 2.0f * 0.25f * targetSpeed) {
                u8 pathArg = get_path_data(i_this)->m_points[get_path_point_index(i_this)].mArg3;
                if (pathArg == 3 || pathArg == 7 || pathArg == 8) {
                    wait_set(i_this);
                    if (pathArg >= 7) {
                        i_this->m03E2 = (s16)(70.0f + cM_rndF(80.0f));
                    }
                    get_behavior_mode(i_this) = 2;
                } else {
                    get_behavior_mode(i_this) = -1;
                }
            }
        } else if (std::sqrtf(rel.x * rel.x + rel.z * rel.z) < 2.0f * 0.25f * targetSpeed ||
                   (get_timer_3e4(i_this) == 0 &&
                    (((get_status_flags_9b8(i_this) & 0x00000010) != 0) ||
                     ground_4_check(i_this, 1, i_this->current.angle.y, 200.0f) != 0)))
        {
            wait_set(i_this);
            get_behavior_mode(i_this) = 2;
        }

        cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 4, angleStep);
        cLib_addCalc2(&i_this->speedF, targetSpeed, 1.0f, 5.0f);
        break;
    }

    case 2:
        i_this->speedF = 0.0f;
        if (i_this->m03E2 == 0) {
            if (get_path_found_count(i_this) != 0 &&
                (get_yari_actor_flag(i_this) != 0 || get_path_search_flag(i_this) != 0))
            {
                u8 pathArg = get_path_data(i_this)->m_points[get_path_point_index(i_this)].mArg3;
                if (pathArg == 7 || pathArg == 8) {
                    get_behavior_mode(i_this) = 4;
                    i_this->m03E2 = (s16)(100.0f + cM_rndF(100.0f));
                    if (pathArg == 7) {
                        get_target_angle(i_this) -= 0x4000;
                    } else {
                        get_target_angle(i_this) += 0x4000;
                    }
                    break;
                }
            }

            get_behavior_mode(i_this) = 0;
            if (get_yari_actor_flag(i_this) == 0 && get_path_search_flag(i_this) == 0 &&
                get_timer_3ea(i_this) == 0)
            {
                get_path_search_flag(i_this) = 1;
            }
        }
        break;

    case 4:
        cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 4, 0x1000);
        // fallthrough
    case 3:
        i_this->speedF = 0.0f;
        if (i_this->m03E2 == 0) {
            get_behavior_mode(i_this) = 0;
        }
        break;
    }

    s32 foundPlayer = fopAcM_otoCheck(i_this, tn_hio_field<f32>(0x28));
    if (get_support_actor_id(i_this) != (fpc_ProcID)0xFFFF) {
        fpc_ProcID procId = get_support_actor_id(i_this);
        fopAc_ac_c* supportActor = (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &procId);
        if (supportActor != NULL && actor_field<s16>(supportActor, 0x1C0E) != 0) {
            foundPlayer |= 2;
        }
    }

    foundPlayer += search_sp;
    if (get_yari_actor_flag(i_this) != 0 || get_path_search_flag(i_this) != 0) {
        if (foundPlayer != 0 ||
            (get_player_distance(i_this) < tn_hio_field<f32>(0x28) &&
             daTn_player_view_check(i_this, &get_player_actor(i_this)->current.pos, get_view_angle_state(i_this),
                                    get_view_H(i_this))))
        {
            get_behavior_action(i_this) = 4;
            get_behavior_mode(i_this) = -10;
            fopAcM_monsSeStart(i_this, 0x4885, 0);
        }
    }

    if (get_yari_actor_flag(i_this) == 0 && daTn_wepon_view_check(i_this)) {
        get_behavior_action(i_this) = 12;
        get_behavior_mode(i_this) = -1;
    }

    if (daTn_bomb_view_check(i_this)) {
        get_behavior_action(i_this) = 9;
        get_behavior_mode(i_this) = 0;
    }
}

/* 00004388-000043D4       .text shot_s_sub__FPvPv */
void* shot_s_sub(void* actor, void*) {
    if (fopAc_IsActor(actor) && fopAcM_GetName((fopAc_ac_c*)actor) == PROC_HIMO2) {
        return actor;
    }

    return NULL;
}

/* 000043D4-00004CFC       .text fight_run__FP8tn_class */
void fight_run(tn_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    f32 stickX = g_mDoCPd_cpadInfo[0].mMainStickPosX;

    get_fight_state_flag(i_this) = 1;
    get_target_angle(i_this) = get_view_angle_state(i_this);

    if (get_action_flag(i_this) == 0 && get_behavior_mode(i_this) != 0) {
        s16 angleStep = get_behavior_mode(i_this) == 1 ? 0x0800 : 0x0400;
        cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 4, angleStep);
    }

    switch (get_behavior_mode(i_this)) {
    case -10:
        if (get_timer_3e8(i_this) == 0) {
            anm_init(i_this, 0x36, 10.0f, 0, 1.0f, -1);
            yoroi_anm_init(i_this, 0x63, 10.0f, 0, 1.0f);
            get_behavior_mode(i_this) = -9;
        } else {
            get_behavior_mode(i_this) = 0;
            i_this->m03E2 = 0;
        }
        break;

    case -9:
        i_this->speedF = 0.0f;
        if (get_main_morf(i_this)->isStop()) {
            get_behavior_mode(i_this) = 0;
            i_this->m03E2 = 0;
        }
        break;

    case 0:
        if (i_this->m03E2 == 0) {
            fight_run_set(i_this);
            get_behavior_mode(i_this) = 1;
            get_shot_search_state(i_this) = 0;
        } else {
            i_this->speedF = 0.0f;
        }
        break;

    case 1: {
        f32 targetSpeed;
        if (i_this->mRemainingEquipmentPieces & 1) {
            targetSpeed = 0.25f * tn_hio_field<f32>(0x4C);
        } else {
            targetSpeed = tn_hio_field<f32>(0x54);
        }

        cLib_addCalc2(&i_this->speedF, targetSpeed, 1.0f, 5.0f);
        if (daTn_player_way_check(i_this)) {
            if (get_player_distance(i_this) < tn_hio_field<f32>(0x2C)) {
                get_behavior_mode(i_this) = 2;
                get_timer_3e6(i_this) = 40;
            }
        } else if (get_player_distance(i_this) < tn_hio_field<f32>(0x30)) {
            get_behavior_action(i_this) = 5;
            get_behavior_mode(i_this) = 0;
            goto check_bomb_and_ground;
        }
        break;
    }

    case 2:
        if (std::fabsf(stickX) > 0.1f) {
            if (get_yari_actor_flag(i_this) != 0) {
                anm_init(i_this, 0x3B, 5.0f, 2, 1.0f, 0x10);
            } else {
                anm_init(i_this, 0x53, 5.0f, 2, 1.0f, 0x23);
            }

            get_behavior_mode(i_this) = stickX > 0.0f ? 5 : 6;
        } else {
            if (get_yari_actor_flag(i_this) != 0) {
                anm_init(i_this, 0x3A, 5.0f, 2, 1.0f, 0x0F);
            } else {
                anm_init(i_this, 0x52, 5.0f, 2, 1.0f, 0x22);
            }

            if (get_player_distance(i_this) < tn_hio_field<f32>(0x30)) {
                get_behavior_mode(i_this) = 4;
            } else {
                get_behavior_mode(i_this) = 3;
            }
        }

        i_this->m03E2 = (s16)(10.0f + cM_rndF(10.0f));
        break;

    case 3:
        cLib_addCalc2(&i_this->speedF, tn_hio_field<f32>(0x5C), 1.0f, 10.0f);
        if (i_this->m03E2 == 0) {
            get_behavior_mode(i_this) = 2;
        }
        break;

    case 4:
        if (get_ground_check_result(i_this) != 2) {
            cLib_addCalc2(&i_this->speedF, -tn_hio_field<f32>(0x5C), 1.0f, 10.0f);
            if (i_this->m03E2 == 0) {
                get_behavior_mode(i_this) = 2;
            }
        } else {
            get_behavior_mode(i_this) = 3;
            anm_init(i_this, 0x3E, 5.0f, 2, 1.0f, 0x11);
        }
        break;

    case 5:
        if (get_ground_check_result(i_this) != 4) {
            get_side_step_angle(i_this) = 0x4000;
        } else {
            get_behavior_mode(i_this) = 6;
            get_side_step_angle(i_this) = -0x4000;
        }

        cLib_addCalc2(&i_this->speedF, tn_hio_field<f32>(0x60), 1.0f, 30.0f);
        if (i_this->m03E2 == 0) {
            get_behavior_mode(i_this) = 2;
        }
        break;

    case 6:
        if (get_ground_check_result(i_this) != 8) {
            get_side_step_angle(i_this) = -0x4000;
        } else {
            get_behavior_mode(i_this) = 5;
            get_side_step_angle(i_this) = 0x4000;
        }

        cLib_addCalc2(&i_this->speedF, tn_hio_field<f32>(0x60), 1.0f, 30.0f);
        if (i_this->m03E2 == 0) {
            get_behavior_mode(i_this) = 2;
        }
        break;
    }

    if (get_behavior_mode(i_this) >= 3) {
        if (get_player_distance(i_this) > 60.0f + tn_hio_field<f32>(0x2C)) {
            get_behavior_action(i_this) = 0;
            path_check(i_this);
            wait_set(i_this);
            get_behavior_mode(i_this) = 0;
            goto check_bomb_and_ground;
        }

        if (get_yari_actor_flag(i_this) != 0 && check_player_special_state(player)) {
            get_behavior_action(i_this) = 5;
            get_behavior_mode(i_this) = 10;
            goto check_bomb_and_ground;
        }

        if (get_player_distance(i_this) < tn_hio_field<f32>(0x30) + 60.0f &&
            get_player_distance(i_this) > tn_hio_field<f32>(0x30) - 60.0f && get_timer_3e6(i_this) == 0)
        {
            get_timer_3e6(i_this) = tn_hio_field<s16>(0x6C);
            if (cM_rndF(100.0f) < tn_hio_field<f32>(0x70)) {
                get_behavior_action(i_this) = 5;
                get_behavior_mode(i_this) = 0;
                goto check_bomb_and_ground;
            }
        }

        if (get_timer_3f2(i_this) == 0) {
            BOOL shotNear = FALSE;
            fopAc_ac_c* shotActor = (fopAc_ac_c*)fpcEx_Search(shot_s_sub, i_this);
            if (shotActor != NULL && shotActor->speedF > 5.0f) {
                cXyz rel = shotActor->current.pos - i_this->current.pos;
                if (rel.abs() < 5.0f * shotActor->speedF) {
                    shotNear = TRUE;
                }
            }

            if (daTn_player_way_check(i_this)) {
                if (!shotNear) {
                    if (actor_field<u8>(player, 0x290) != 0) {
                        shotNear = TRUE;
                        dAttention_c& attention = dComIfGp_getAttention();
                        if (!attention.Lockon()) {
                            shotNear = FALSE;
                        }

                        if (shotNear && attention.LockonTarget(0) != i_this) {
                            shotNear = FALSE;
                        }
                    }
                }

                if (shotNear) {
                    if ((get_flags_3d8(i_this) & 3) == 0 && (i_this->mRemainingEquipmentPieces & 4) &&
                        cM_rndF(1.0f) < 0.8f)
                    {
                        get_behavior_action(i_this) = 10;
                        get_behavior_mode(i_this) = 0;
                        i_this->m03E2 = actor_field<u8>(player, 0x290) == 0x0A ? 30 : 15;
                        fopAcM_monsSeStart(i_this, 0x488B, 0);
                        goto check_bomb_and_ground;
                    }

                    if ((i_this->mRemainingEquipmentPieces & 1) == 0) {
                        get_behavior_action(i_this) = 5;
                        get_behavior_mode(i_this) = -20;
                        get_timer_3f0(i_this) = 10;
                        if (get_yari_actor_flag(i_this) != 0) {
                            anm_init(i_this, 0x48, 2.0f, 0, 1.0f, 0x1B);
                        } else {
                            anm_init(i_this, 0x49, 2.0f, 0, 1.0f, 0x1C);
                        }

                        i_this->speedF = -60.0f + reg_hio_field<f32>(0x18);
                        i_this->speed.y = 80.0f + reg_hio_field<f32>(0x1C);
                        fopAcM_monsSeStart(i_this, 0x488A, 0);
                        goto check_bomb_and_ground;
                    }
                }
            }
        }
    }

    if (daTn_player_bg_check(i_this, &player->current.pos)) {
        get_behavior_action(i_this) = 0;
        path_check(i_this);
        wait_set(i_this);
        get_behavior_mode(i_this) = -10;
        goto check_bomb_and_ground;
    }

    if (get_yari_actor_flag(i_this) == 0 && daTn_wepon_view_check(i_this)) {
        get_behavior_action(i_this) = 12;
        get_behavior_mode(i_this) = -1;
    }

check_bomb_and_ground:
    if (daTn_bomb_view_check(i_this)) {
        get_behavior_action(i_this) = 9;
        get_behavior_mode(i_this) = 0;
    }

    get_ground_check_result(i_this) = ground_4_check(
        i_this, 4, i_this->current.angle.y, 90.0f + reg_hio_field<f32>(0x388));
    get_timer_3e8(i_this) = 50;
}

/* 00004CFC-00005098       .text wepon_hit_check__FP8tn_class */
fopAc_ac_c* wepon_hit_check(tn_class* i_this) {
    static int atp_0[] = {2, 2, 1, 2, 8, 8};
    static int atp_1[] = {4, 4, 2, 4, 12, 12};

    get_weapon_hit_flag(i_this) = 0;
    get_weapon_tip_pos_prev(i_this) = get_weapon_tip_pos_a(i_this);

    int frame = (int)get_main_morf(i_this)->getFrame();
    int startFrame = 0;
    int endFrame = 1000;

    switch (get_attack_kind(i_this)) {
    case 0:
        startFrame = 0x13;
        endFrame = 0x1A;
        break;
    case 1:
        if (i_this->mRemainingEquipmentPieces & 1) {
            startFrame = 0x13;
            endFrame = 0x1C;
        } else {
            startFrame = 0x0E;
            endFrame = 0x17;
        }
        break;
    case 2:
        startFrame = 0x07;
        endFrame = 0x09;
        break;
    case 3:
        startFrame = 0x14;
        endFrame = 0x18;
        break;
    case 4:
        startFrame = 0x14;
        endFrame = 0x1A;
        break;
    case 5:
        startFrame = 0;
        endFrame = 1000;
        break;
    }

    if (frame < startFrame || frame > endFrame) {
        return NULL;
    }

    if (get_attack_counter(i_this) < 0) {
        return NULL;
    }

    int atp = (i_this->mEquipmentType & 1) ? atp_1[get_attack_kind(i_this)]
                                           : atp_0[get_attack_kind(i_this)];
    get_weapon_sph_a(i_this).SetAtAtp(atp);
    get_weapon_sph_b(i_this).SetAtAtp(atp);

    if (get_attack_kind(i_this) == 3) {
        PSMTXCopy(get_main_morf(i_this)->getModel()->getAnmMtx(5), *calc_mtx);
    } else {
        PSMTXCopy(get_main_morf(i_this)->getModel()->getAnmMtx(23), *calc_mtx);
    }

    cXyz offset(0.0f, 0.0f, 0.0f);
    if (get_attack_kind(i_this) != 2 && get_attack_kind(i_this) != 3) {
        offset.z = 22.0f;
    }

    MtxPosition(&offset, &get_weapon_tip_pos_a(i_this));
    offset.z *= 0.33332288f;
    MtxPosition(&offset, &get_weapon_tip_pos_b(i_this));

    get_weapon_sph_a(i_this).SetAtType(AT_TYPE_UNK8);
    get_weapon_sph_b(i_this).SetAtType(AT_TYPE_UNK8);

    if (get_weapon_swing_started(i_this) == 0) {
        get_weapon_swing_started(i_this)++;
        get_weapon_sph_a(i_this).StartCAt(get_weapon_tip_pos_a(i_this));
        get_weapon_sph_b(i_this).StartCAt(get_weapon_tip_pos_b(i_this));
    } else {
        get_weapon_sph_a(i_this).SetR(60.0f + reg_hio_field<f32>(0x40));
        get_weapon_sph_a(i_this).MoveCAt(get_weapon_tip_pos_a(i_this));
        get_weapon_sph_b(i_this).MoveCAt(get_weapon_tip_pos_b(i_this));
        get_weapon_sph_b(i_this).SetR(40.0f + reg_hio_field<f32>(0x44));
    }

    if (get_attack_kind(i_this) <= 1) {
        get_weapon_sph_a(i_this).SetAtSe(dCcG_SE_UNK6);
        get_weapon_sph_b(i_this).SetAtSe(dCcG_SE_UNK6);
    } else if (get_attack_kind(i_this) == 4 || get_attack_kind(i_this) == 5) {
        get_weapon_sph_a(i_this).SetAtSe(dCcG_SE_ARROW);
        get_weapon_sph_b(i_this).SetAtSe(dCcG_SE_ARROW);
    } else {
        get_weapon_sph_a(i_this).SetAtSe(0);
        get_weapon_sph_b(i_this).SetAtSe(0);
    }

    dComIfG_Ccsp()->Set(&get_weapon_sph_a(i_this));
    dComIfG_Ccsp()->Set(&get_weapon_sph_b(i_this));

    if (get_weapon_sph_a(i_this).ChkAtHit() || get_weapon_sph_b(i_this).ChkAtHit()) {
        cCcD_Obj* hitObj = get_weapon_sph_a(i_this).ChkAtHit() ? get_weapon_sph_a(i_this).GetAtHitObj()
                                                                : get_weapon_sph_b(i_this).GetAtHitObj();
        if (hitObj != NULL) {
            fopAc_ac_c* hitActor = hitObj->GetAc();
            if (hitActor != NULL) {
                return hitActor;
            }
            return NULL;
        }

        JUTReport(0x1B8, 0xDC, "TN AT HITOBJ NON");
    }

    return NULL;
}

/* 00005098-00005EB0       .text fight__FP8tn_class */
void fight(tn_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    BOOL retreat = FALSE;
    BOOL specialCut = FALSE;
    f32 stickX = g_mDoCPd_cpadInfo[0].mMainStickPosX;

    get_fight_state_flag(i_this) = 1;

    u8 cutType = player->getCutType();
    if (cutType == 8 || cutType == 9) {
        specialCut = TRUE;
    }

    switch (get_behavior_mode(i_this)) {
    case -20:
        if (get_main_morf(i_this)->isStop()) {
            if (cM_rndF(1.0f) < 0.5f) {
                if (get_yari_actor_flag(i_this) != 0) {
                    anm_init(i_this, 0x3F, 3.0f, 0, 1.0f, 0x12);
                    get_attack_kind(i_this) = 4;
                    fopAcM_monsSeStart(i_this, JA_SE_CV_TN_JUMP, 0);
                } else {
                    anm_init(i_this, 0x43, 3.0f, 0, 1.0f, 0x16);
                    get_attack_kind(i_this) = 3;
                    get_attack_reverse_flag(i_this) = 1;
                }

                get_behavior_mode(i_this) = 1;
                get_timer_3e4(i_this) = 8;
                get_weapon_swing_started(i_this) = 0;
                get_attack_counter(i_this) = 1;
            } else {
                retreat = TRUE;
            }
        }

        if (get_status_flags_9b8(i_this) & 0x20) {
            i_this->speedF = 0.0f;
        }
        break;

    case 0:
        if (get_yari_actor_flag(i_this) != 0) {
            if (cM_rndF(100.0f) < tn_hio_field<f32>(0x78)) {
                if (i_this->mRemainingEquipmentPieces & 1) {
                    anm_init(i_this, 0x2E, 5.0f, 0, 1.0f, 0x0B);
                } else {
                    anm_init(i_this, 0x46, 5.0f, 0, 1.0f, 0x19);
                }

                yoroi_anm_init(i_this, 0x5C, 5.0f, 0, 1.0f);
                get_attack_kind(i_this) = 0;
            } else {
                if (i_this->mRemainingEquipmentPieces & 1) {
                    anm_init(i_this, 0x2F, 5.0f, 0, 1.0f, 0x0C);
                } else {
                    anm_init(i_this, 0x47, 5.0f, 0, 1.0f, 0x1A);
                }

                yoroi_anm_init(i_this, 0x5D, 5.0f, 0, 1.0f);
                get_attack_kind(i_this) = 1;
                fopAcM_monsSeStart(i_this, JA_SE_CV_TN_KAMAE_S, 0);
            }
        } else {
            if (cM_rndF(100.0f) < tn_hio_field<f32>(0x7C) || (i_this->mRemainingEquipmentPieces & 1)) {
                anm_init(i_this, 0x45, 3.0f, 0, 1.0f, 0x18);
                get_attack_kind(i_this) = 2;
                fopAcM_monsSeStart(i_this, JA_SE_CV_TN_PUNCH_S, 0);
            } else {
                anm_init(i_this, 0x43, 3.0f, 0, 1.0f, 0x16);
                get_attack_kind(i_this) = 3;
                fopAcM_monsSeStart(i_this, JA_SE_CV_TN_KICK, 0);
            }
        }

        get_behavior_mode(i_this) = 1;
        get_timer_3e4(i_this) = 8;
        get_weapon_swing_started(i_this) = 0;
        get_attack_counter(i_this) = 1;
        get_attack_reverse_flag(i_this) = 0;
        break;

    case 1: {
        f32 frame = get_main_morf(i_this)->getFrame();

        if (get_attack_kind(i_this) == 3 && frame >= 12.0f && frame <= 30.0f) {
            if (get_attack_reverse_flag(i_this) != 0) {
                i_this->speedF = 80.0f + reg_hio_field<f32>(0x34);
            } else {
                i_this->speedF = 50.0f + reg_hio_field<f32>(0x30);
            }
        } else if (get_attack_kind(i_this) == 4 && frame >= 4.0f && frame <= 21.0f) {
            i_this->speedF = 50.0f + reg_hio_field<f32>(0x4C);
            if ((int)frame == 20) {
                fopAcM_monsSeStart(i_this, JA_SE_CV_TN_ATTACK_L, 0);
            }
        } else {
            cLib_addCalc0(&i_this->speedF, 1.0f, 20.0f + reg_hio_field<f32>(0x34));
        }

        f32 fx0 = 1000.0f;
        f32 fx1 = 1000.0f;
        u8 fxType = 0;

        if (get_attack_counter(i_this) > 0) {
            if (get_attack_kind(i_this) == 0) {
                fx0 = 0.0f;
                fx1 = 40.0f;
                fxType = 2;
                if ((int)frame == 20) {
                    fopAcM_monsSeStart(i_this, JA_SE_CV_TN_ATTACK_S, 0);
                }
            } else if (get_attack_kind(i_this) == 1) {
                fx0 = 0.0f;
                fx1 = 40.0f;
                fxType = 1;

                if ((int)frame == reg_hio_field<s16>(0x88) + 17) {
                    get_smoke_timer(i_this) = reg_hio_field<s16>(0x8A) + tn_hio_field<s16>(0x20) + 14;
                    get_smoke_mode(i_this) = 0;
                    get_smoke_rot(i_this) = i_this->current.angle.y + reg_hio_field<s16>(0x94) + 0x2000;
                }

                if ((int)frame == 20) {
                    fopAcM_monsSeStart(i_this, JA_SE_CV_TN_ATTACK_S, 0);
                }
            }

            if (get_attack_kind(i_this) == 0 || get_attack_kind(i_this) == 4) {
                int seFrame;
                if ((i_this->mRemainingEquipmentPieces & 1) || get_attack_kind(i_this) == 4) {
                    seFrame = 0x15;
                } else {
                    seFrame = 0x13;
                }

                if ((int)frame == seFrame) {
                    dComIfGp_particle_set(dPa_name::ID_IT_ST_TN_KENSMOKE00, &i_this->current.pos,
                                          &i_this->shape_angle, NULL, 0xFF, NULL, 0xB9,
                                          NULL, NULL, &get_guard_effect_scale2d(i_this));
                }
            }
        }

        get_fx_f32_29c(i_this) = fx0;
        get_fx_f32_2a0(i_this) = fx1;
        get_fx_f32_298(i_this) = tn_hio_field<f32>(0xD4);
        get_fx_u8_2a8(i_this) = fxType;
        get_fx_f32_2a4(i_this) = frame;

        fopAc_ac_c* hitActor = wepon_hit_check(i_this);
        if (hitActor != NULL && fopAcM_GetName(hitActor) == PROC_PLAYER) {
            if (player->checkPlayerGuard() &&
                (get_attack_kind(i_this) == 0 || get_attack_kind(i_this) == 1))
            {
                get_main_morf(i_this)->setPlaySpeed(-1.0f);
                get_attack_counter(i_this) = -1;
                get_main_morf(i_this)->play(&i_this->eyePos, 0, 0);

                anm_init(i_this, 0x32, 5.0f + reg_hio_field<f32>(0x1C), 0, 1.0f, 0x0D);
                yoroi_anm_init(i_this, 0x5F, 5.0f + reg_hio_field<f32>(0x1C), 0, 1.0f);
            }
        }

        if (frame < 10.0f) {
            get_target_angle(i_this) = get_view_angle_state(i_this);
            cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 4, 0x0400);
        }

        if (get_main_morf(i_this)->isStop()) {
            retreat = TRUE;
        }
        break;
    }

    case 10:
        get_attack_kind(i_this) = 5;
        get_behavior_mode(i_this) = 12;
        fopAcM_monsSeStart(i_this, JA_SE_CV_TN_KAMAE_L, 0);
        break;

    case 12:
        if (std::fabsf(stickX) > 0.1f) {
            anm_init(i_this, 0x2D, 5.0f, 2, 1.0f, 0x0A);
            if (stickX > 0.0f) {
                get_behavior_mode(i_this) = 15;
            } else {
                get_behavior_mode(i_this) = 16;
            }
        } else {
            if (get_player_distance(i_this) < tn_hio_field<f32>(0x30) + 25.0f &&
                get_player_distance(i_this) > tn_hio_field<f32>(0x30) - 25.0f)
            {
                anm_init(i_this, 0x28, 5.0f, 2, 1.0f, -1);
                get_behavior_mode(i_this) = 18;
            } else {
                if (get_player_distance(i_this) < tn_hio_field<f32>(0x30)) {
                    get_behavior_mode(i_this) = 14;
                } else {
                    get_behavior_mode(i_this) = 13;
                }

                anm_init(i_this, 0x2C, 5.0f, 2, 1.0f, 0x09);
            }
        }

        yoroi_anm_init(i_this, 0x58, 5.0f, 2, 1.0f);
        i_this->m03E2 = (s16)(20.0f + cM_rndF(20.0f));
        break;

    case 13:
        cLib_addCalc2(&i_this->speedF, tn_hio_field<f32>(0x5C), 1.0f, 10.0f);
        break;

    case 14:
        cLib_addCalc2(&i_this->speedF, -tn_hio_field<f32>(0x5C), 1.0f, 10.0f);
        break;

    case 15:
        get_side_step_angle(i_this) = 0x4000;
        cLib_addCalc2(&i_this->speedF, tn_hio_field<f32>(0x60), 1.0f, 30.0f);
        break;

    case 16:
        get_side_step_angle(i_this) = -0x4000;
        cLib_addCalc2(&i_this->speedF, tn_hio_field<f32>(0x60), 1.0f, 30.0f);
        break;

    case 18:
        i_this->speedF = 0.0f;
        break;

    case 20:
        if (get_main_morf(i_this)->isStop()) {
            get_behavior_mode(i_this) = 21;
            anm_init(i_this, 0x2A, 1.0f, 2, 1.0f, 0x07);
            yoroi_anm_init(i_this, 0x5A, 1.0f, 2, 1.0f);
            get_mode_timer_14f4(i_this) = 1;
        }
        break;

    case 21:
        i_this->speedF = 0.0f;

        if (player->getCutType() == 9) {
            get_mode_timer_14f6(i_this) = 7;
        } else {
            get_mode_timer_14f6(i_this) = 3;
        }

        wepon_hit_check(i_this);

        if (!specialCut) {
            get_behavior_mode(i_this) = 22;
            anm_init(i_this, 0x2B, 1.0f, 0, 1.0f, 0x08);
            yoroi_anm_init(i_this, 0x5B, 1.0f, 0, 1.0f);
            fopAcM_monsSeStart(i_this, JA_SE_CV_TN_ATTACK_L, 0);
        }

        if (get_support_actor_id(i_this) != (fpc_ProcID)0xFFFF) {
            fpc_ProcID procId = get_support_actor_id(i_this);
            fopAc_ac_c* supportActor =
                (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &procId);
            if (supportActor != NULL) {
                cLib_addCalc2(&actor_field<f32>(supportActor, 0x1BF8), 50.0f + reg_hio_field<f32>(0x24),
                              1.0f, 10.0f);
                cLib_addCalc2(&actor_field<f32>(supportActor, 0x1BFC),
                              10000.0f + reg_hio_field<f32>(0x28), 1.0f, 0.2f);
            }
        }
        break;

    case 22:
        if (get_main_morf(i_this)->isStop()) {
            retreat = TRUE;
        }
        break;
    }

    if (get_behavior_mode(i_this) >= 13 && get_behavior_mode(i_this) <= 16) {
        if (i_this->m03E2 == 0) {
            get_behavior_mode(i_this) = 12;
        }

        if (!check_player_special_state(player)) {
            retreat = TRUE;
        }

        if (specialCut) {
            retreat = FALSE;
            get_behavior_mode(i_this) = 20;
            anm_init(i_this, 0x29, 2.0f, 0, 1.0f, 0x06);
            yoroi_anm_init(i_this, 0x59, 2.0f, 0, 1.0f);
            fopAcM_monsSeStart(i_this, JA_SE_CV_TN_ATTACK_L, 0);
        }
    } else if (get_behavior_mode(i_this) == 18) {
        if (i_this->m03E2 == 0) {
            get_behavior_mode(i_this) = 12;
        }

        if (!check_player_special_state(player)) {
            retreat = TRUE;
        }

        if (specialCut) {
            retreat = FALSE;
            get_behavior_mode(i_this) = 20;
            anm_init(i_this, 0x29, 2.0f, 0, 1.0f, 0x06);
            yoroi_anm_init(i_this, 0x59, 2.0f, 0, 1.0f);
            fopAcM_monsSeStart(i_this, JA_SE_CV_TN_ATTACK_L, 0);
        }
    }

    get_timer_3e8(i_this) = 50;

    if (retreat) {
        if (get_player_distance(i_this) < tn_hio_field<f32>(0x2C)) {
            if (daTn_player_view_check(i_this, &get_player_actor(i_this)->current.pos,
                                       get_view_angle_state(i_this), get_view_H(i_this)))
            {
                if (cM_rndF(1.0f) < 0.5f) {
                    get_behavior_action(i_this) = 4;
                    get_behavior_mode(i_this) = 2;
                    get_timer_3e6(i_this) = (s16)(10.0f + cM_rndF(10.0f));
                } else {
                    get_behavior_mode(i_this) = 0;
                }
            } else {
                get_behavior_action(i_this) = 8;
                get_behavior_mode(i_this) = 0;
            }
        } else {
            get_behavior_action(i_this) = 0;
            path_check(i_this);
            wait_set(i_this);
            get_behavior_mode(i_this) = 0;
        }
    }
}

/* 00005EB0-00005FFC       .text p_lost__FP8tn_class */
void p_lost(tn_class* i_this) {
    get_fight_state_flag(i_this) = 0;

    switch (get_behavior_mode(i_this)) {
    case 0:
        get_behavior_mode(i_this) = 1;
        anm_init(i_this, 0x37, 5.0f, 0, 1.0f, -1);
        yoroi_anm_init(i_this, 0x65, 5.0f, 0, 1.0f);
        i_this->speedF = 0.0f;
        break;

    case 1:
        if (get_main_morf(i_this)->isStop()) {
            get_behavior_action(i_this) = 0;
            path_check(i_this);
            wait_set(i_this);
            get_behavior_mode(i_this) = 0;
        }
        break;
    }

    if ((int)get_main_morf(i_this)->getFrame() > 0x19) {
        if (daTn_player_view_check(i_this, &get_player_actor(i_this)->current.pos,
                                   get_view_angle_state(i_this), get_view_H(i_this)))
        {
            get_behavior_action(i_this) = 4;
            get_behavior_mode(i_this) = -10;
            i_this->m03E2 = 0;
        }
    }
}

/* 00005FFC-00006450       .text wepon_search__FP8tn_class */
void wepon_search(tn_class* i_this) {
    fpc_ProcID procId = get_yari_actor_id(i_this);
    fopAc_ac_c* yariActor =
        (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &procId);

    if (get_behavior_mode(i_this) < 2 &&
        (yariActor == NULL || fopAcM_checkCarryNow(yariActor)))
    {
        get_behavior_action(i_this) = 0;
        path_check(i_this);
        wait_set(i_this);
        get_behavior_mode(i_this) = 2;
        return;
    }

    f32 distance = 10000.0f;
    if (yariActor != NULL) {
        f32 dx = yariActor->current.pos.x - i_this->current.pos.x;
        f32 dz = yariActor->current.pos.z - i_this->current.pos.z;
        get_target_angle(i_this) = cM_atan2s(dx, dz);
        distance = std::sqrtf(dx * dx + dz * dz);
    }

    switch (get_behavior_mode(i_this)) {
    case -1:
        get_behavior_mode(i_this) = 0;
        get_path_search_flag(i_this) = 0;
        anm_init(i_this, 0x36, 3.0f, 0, 1.0f, -1);
        yoroi_anm_init(i_this, 0x63, 3.0f, 0, 1.0f);
        if (distance < 900.0f) {
            i_this->m03E2 = 20;
        } else {
            i_this->m03E2 = 200;
        }
        get_timer_3ee(i_this) = 5;
        break;

    case 0:
        i_this->speedF = 0.0f;
        if (get_timer_3ee(i_this) == 0) {
            cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 2, 0x3000);

            if (get_main_morf(i_this)->isStop() || i_this->m03E2 == 0) {
                get_behavior_mode(i_this) = 1;
                get_timer_3ea(i_this) = tn_hio_field<s16>(0x82);
                fight_run_set(i_this);
            }
        }
        break;

    case 1:
        cLib_addCalc2(&i_this->speedF, tn_hio_field<f32>(0x58), 1.0f, 10.0f);
        cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 4, 0x1000);

        if (distance < 150.0f + reg_hio_field<f32>(0x494)) {
            get_behavior_mode(i_this) = 2;
            anm_init(i_this, 0x4C, 2.0f, 0, 1.0f, 0x1D);
            i_this->m03E2 = 0x1D;
            break;
        }

        if (get_timer_3ea(i_this) == 0) {
            get_behavior_action(i_this) = 4;
            i_this->m03E2 = 0;
            get_path_search_flag(i_this) = 1;
        } else if ((get_status_flags_9b8(i_this) & 0x20) && (get_status_flags_9b8(i_this) & 0x10)) {
            get_behavior_action(i_this) = 0;
            path_check(i_this);
            wait_set(i_this);
            get_behavior_mode(i_this) = 2;
            get_search_mode(i_this) = 0x46;
        }
        break;

    case 2:
        i_this->speedF = 0.0f;

        if (i_this->m03E2 == reg_hio_field<s16>(0x92) + 0x12) {
            if (yariActor != NULL && !fopAcM_checkCarryNow(yariActor)) {
                get_yari_state(i_this) = 2;
                fopAcM_setCarryNow(yariActor, FALSE);
            } else {
                get_behavior_action(i_this) = 0;
                path_check(i_this);
                wait_set(i_this);
                get_behavior_mode(i_this) = 2;
            }
        }

        if (i_this->m03E2 < 14) {
            get_fight_state_flag(i_this) = 1;
            get_target_angle(i_this) = get_view_angle_state(i_this);
            cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 3, 0x800);
        }

        if (get_main_morf(i_this)->isStop()) {
            get_behavior_action(i_this) = 0;
            path_check(i_this);
            wait_set(i_this);
            get_behavior_mode(i_this) = 2;
        }
        break;
    }
}

/* 00006450-00006950       .text b_nige__FP8tn_class */
void b_nige(tn_class* i_this) {
    if (!daTn_bomb_check(i_this)) {
        get_behavior_action(i_this) = 0;
        path_check(i_this);
        wait_set(i_this);
        get_behavior_mode(i_this) = 2;
        return;
    }

    f32 dx = get_bomb_actor(i_this)->current.pos.x - i_this->current.pos.x;
    f32 dz = get_bomb_actor(i_this)->current.pos.z - i_this->current.pos.z;
    get_target_angle(i_this) = cM_atan2s(-dx, -dz);
    f32 bombDistance = std::sqrtf(dx * dx + dz * dz);

    switch (get_behavior_mode(i_this)) {
    case 0:
        get_behavior_mode(i_this) = 1;
        anm_init(i_this, 0x36, 3.0f, 0, 1.0f, -1);
        fopAcM_monsSeStart(i_this, 0x4885, 0);
        i_this->m03E2 = 10;
        // Fall-through
    case 1:
        i_this->speedF = 0.0f;
        cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this) + 0x8000, 2, 0x3000);

        if (i_this->m03E2 == 0) {
            get_behavior_mode(i_this) = 2;
            if (get_yari_actor_flag(i_this) != 0) {
                anm_init(i_this, 0x48, 2.0f, 0, 1.0f, 0x1B);
            } else {
                anm_init(i_this, 0x49, 2.0f, 0, 1.0f, 0x1C);
            }

            i_this->speedF = 200.0f + reg_hio_field<f32>(0x18);
            i_this->speed.y = 25.0f + reg_hio_field<f32>(0x1C);
            fopAcM_monsSeStart(i_this, 0x488A, 0);
        }
        break;

    case 2:
        if ((get_status_flags_9b8(i_this) & 0x20) == 0 || !get_main_morf(i_this)->isStop()) {
            break;
        }

        i_this->speedF = 0.0f;
        if (bombDistance > 800.0f) {
            get_behavior_mode(i_this) = 4;
            if (get_yari_actor_flag(i_this) != 0) {
                anm_init(i_this, 0x35, 5.0f, 2, 1.0f, -1);
            } else {
                anm_init(i_this, 0x4D, 5.0f, 2, 1.0f, -1);
            }
        } else {
            get_behavior_mode(i_this) = 3;
            fight_run_set(i_this);
        }
        break;

    case 3:
        i_this->speedF = tn_hio_field<f32>(0x58);
        cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 4, 0x1000);

        if (bombDistance > 800.0f) {
            get_behavior_mode(i_this) = 4;
            if (get_yari_actor_flag(i_this) != 0) {
                anm_init(i_this, 0x35, 5.0f, 2, 1.0f, -1);
            } else {
                anm_init(i_this, 0x4D, 5.0f, 2, 1.0f, -1);
            }
        }
        break;

    case 4:
        i_this->speedF = 0.0f;
        get_target_angle(i_this) = get_view_angle_state(i_this);
        cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 3, 0x1000);

        if (bombDistance < 700.0f) {
            get_behavior_mode(i_this) = 0;
        }
        break;
    }
}

/* 00006950-00006AC0       .text defence__FP8tn_class */
void defence(tn_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();

    get_fight_state_flag(i_this) = 1;
    get_target_angle(i_this) = get_view_angle_state(i_this);
    cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 4, 0x400);

    switch (get_behavior_mode(i_this)) {
    case 0:
        get_behavior_mode(i_this) = 1;

        if (get_yari_actor_flag(i_this) != 0) {
            anm_init(i_this, 0x30, 2.0f, 0, 1.0f, -1);
            tate_anm_init(i_this, 0x30, 2.0f, 0, 1.0f);
        } else {
            anm_init(i_this, 0x31, 2.0f, 0, 1.0f, -1);
            tate_anm_init(i_this, 0x31, 2.0f, 0, 1.0f);
        }

        yoroi_anm_init(i_this, 0x5E, 2.0f, 0, 1.0f);
        // Fall-through
    case 1:
        i_this->speedF = 0.0f;
        get_guard_pose_flag(i_this) = 1;

        if (i_this->m03E2 == 0 && actor_field<u8>(player, 0x0290) == 0) {
            get_behavior_action(i_this) = 4;
            i_this->m03E2 = 0;
            get_behavior_mode(i_this) = 0;
            tate_anm_init(i_this, 0x3C, 10.0f, 2, 1.0f);
        }
        break;
    }
}

/* 00006AC0-00006DD4       .text hukki__FP8tn_class */
void hukki(tn_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();

    cXyz offset;
    offset.x = get_hukki_pos_a_x(i_this) - get_hukki_pos_b_x(i_this);
    offset.z = get_hukki_pos_a_z(i_this) - get_hukki_pos_b_z(i_this);
    mDoMtx_YrotS(*calc_mtx, cM_atan2s(offset.x, offset.z));

    offset.x = 0.0f;
    offset.y = 0.0f;
    get_timer_3f0(i_this) = 2;

    switch (get_behavior_mode(i_this)) {
    case 10:
        anm_init(i_this, 0x4E, 0.0f, 0, 1.0f, 0x1E);
        yoroi_anm_init(i_this, 0x64, 10.0f, 0, 1.0f);
        get_timer_3e4(i_this) = 0x0F;
        // Fall-through
    case 12:
        if (get_behavior_mode(i_this) == 12) {
            anm_init(i_this, 0x4F, 0.0f, 0, 1.0f, 0x1F);
            yoroi_anm_init(i_this, 0x64, 10.0f, 0, 1.0f);
            get_timer_3e4(i_this) = reg_hio_field<s16>(0x8E) + 0x0F;
        }

        i_this->speedF = 0.0f;
        get_behavior_mode(i_this) = 13;
        get_hukki_timer_8f4(i_this) = 0;

        offset.z = 125.0f;
        MtxPosition(&offset, &get_hukki_step_vec(i_this));

        i_this->current.pos.y -= get_hukki_y_offset(i_this);
        i_this->old.pos.y -= get_hukki_y_offset(i_this);
        get_hukki_y_offset(i_this) = 0.0f;
        // Fall-through
    case 13:
        if (get_timer_3e4(i_this) <= reg_hio_field<s16>(0x3EE) + 6) {
            f32 accel = 0.1f * (25.0f + reg_hio_field<f32>(0x380));
            cLib_addCalc0(&tn_field<f32>(i_this, 0x08CC), 1.0f, accel);
            cLib_addCalc0(&tn_field<f32>(i_this, 0x08D4), 1.0f, accel);

            if (get_timer_3e4(i_this) >= reg_hio_field<s16>(0x3F0) + 1) {
                cXyz step;
                offset.z = 100.0f;
                MtxPosition(&offset, &step);
                i_this->current.pos.x += step.x;
                i_this->current.pos.z += step.z;
            }
        }

        if (get_main_morf(i_this)->isStop()) {
            if (actor_field<f32>(player, 0x02B0) >= 0.0f &&
                get_player_distance(i_this) < tn_hio_field<f32>(0x2C))
            {
                get_behavior_mode(i_this) = 14;
                i_this->m03E2 = 10;
            } else {
                get_behavior_action(i_this) = 0;
                path_check(i_this);
                wait_set(i_this);
                get_behavior_mode(i_this) = 0;
            }

            get_hukki_timer_8fc(i_this) = 0;
        }
        break;

    case 14:
        get_fight_state_flag(i_this) = 1;
        get_target_angle(i_this) = get_view_angle_state(i_this);
        cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 3, 0x1000);

        if (i_this->m03E2 == 0) {
            get_behavior_action(i_this) = 5;
            get_behavior_mode(i_this) = 0;
        }
        break;
    }
}

/* 00006DD4-00006EB4       .text aite_miru__FP8tn_class */
void aite_miru(tn_class* i_this) {
    switch (get_behavior_mode(i_this)) {
    case 0:
        i_this->m03E2 = reg_hio_field<s16>(0x94) + 0x14;
        i_this->speedF = 0.0f;
        get_behavior_mode(i_this) = 1;
        // Fall-through
    case 1:
        cLib_addCalcAngleS2(&get_watch_turn_angle(i_this), 0x2EE0, 2, 0x1800);
        get_fight_state_flag(i_this) = 1;

        if (get_watch_target_id(i_this) != fpcM_ERROR_PROCESS_ID_e) {
            fpc_ProcID procId = get_watch_target_id(i_this);
            fopAc_ac_c* actor =
                (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &procId);
            if (actor != NULL) {
                get_player_actor(i_this) = actor;
            }
        }

        if (i_this->m03E2 == 0) {
            get_watch_target_id(i_this) = fpcM_ERROR_PROCESS_ID_e;
            get_behavior_action(i_this) = 0;
            get_behavior_mode(i_this) = 0;
            path_check(i_this);
        }
        break;
    }
}

/* 00006EB4-00006FF0       .text fail__FP8tn_class */
void fail(tn_class* i_this) {
    get_timer_3f0(i_this) = 5;
    fopAcM_OffStatus(i_this, 0);
    i_this->attention_info.flags = 0;
    i_this->speedF = 0.0f;
    i_this->speed.y = 0.0f;

    switch (get_behavior_mode(i_this)) {
    case 0: {
        cXyz pos = i_this->current.pos;
        pos.y += 100.0f + tn_hio_field<f32>(0x18);

        u8 dropType = daDisItem_IBALL_e;
        if (get_timer_3e4(i_this) >= 1000) {
            dropType = daDisItem_NONE1_e;
        }

        fopAcM_createDisappear(i_this, &pos, 10, dropType, i_this->stealItemBitNo);

        if (get_fail_hold_flag(i_this) != 0) {
            get_draw_skip_flag(i_this) = 1;
            get_behavior_mode(i_this)++;
        } else {
            fopAcM_delete(i_this);
        }

        if (i_this->mDisableSpawnOnDeathSwitch != 0) {
            dComIfGs_onSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(i_this));
        }

        fopAcM_onActor(i_this);
        get_behavior_mode(i_this) = 1;
        break;
    }
    }
}

/* 00006FF0-0000719C       .text yogan_fail__FP8tn_class */
void yogan_fail(tn_class* i_this) {
    get_timer_3f0(i_this) = 5;
    fopAcM_OffStatus(i_this, 0);
    i_this->attention_info.flags = 0;
    i_this->speedF = 0.0f;

    switch (get_behavior_mode(i_this)) {
    case 0:
        get_behavior_mode(i_this) = 1;
        i_this->speed.y = 190.0f + reg_hio_field<f32>(0x58);
        tn_field<f32>(i_this, 0x08D0) = 0.0f;
        get_hukki_y_offset(i_this) = 0.0f;

        if (get_yari_actor_flag(i_this) != 0) {
            get_yari_state(i_this) = 1;
        }
        break;
    }

    dComIfGp_particle_setSimple(dPa_name::ID_IT_SN_O_FIREK_KASU, &i_this->current.pos);
    dComIfGp_particle_setSimple(dPa_name::ID_IT_SN_O_MAGT_FCHIP, &i_this->current.pos);

    if ((get_flags_3d8(i_this) & 7) == 0) {
        get_smoke_angle(i_this).y = (s16)cM_rndF(65536.0f);
        get_smoke_angle(i_this).x = -0x2000;
        dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &i_this->m1384, &get_smoke_angle(i_this));
    }

    cLib_addCalcAngleS2(&i_this->current.angle.x, -0x4000, 10, 0x200);

    if (i_this->speed.y < 0.0f) {
        get_behavior_action(i_this) = 0x14;
        get_behavior_mode(i_this) = 0;
        get_timer_3e4(i_this) = 2000;
    }
}

/* 0000719C-000072C8       .text d_mahi__FP8tn_class */
void d_mahi(tn_class* i_this) {
    switch (get_behavior_mode(i_this)) {
    case 0:
        get_behavior_mode(i_this) = 1;
        anm_init(i_this, 0x38, 3.0f, 0, 1.0f, -1);
        yoroi_anm_init(i_this, 0x66, 3.0f, 0, 1.0f);
        get_timer_3e0(i_this) = 0x3C;
        break;
    }

    if (get_timer_3e0(i_this) <= 0x28 && get_timer_3e0(i_this) >= 0x0A) {
        if (get_timer_3e0(i_this) == 0x28) {
            enemy_piyo_set(i_this);
        }

        fopAcM_seStart(i_this, JA_SE_CM_MD_PIYO, 0);
    }

    i_this->speedF = 0.0f;

    if (get_timer_3e0(i_this) == 0) {
        get_behavior_action(i_this) = 0;
        path_check(i_this);
        wait_set(i_this);
        get_behavior_mode(i_this) = 2;
    }
}

/* 000072C8-00007440       .text d_sit__FP8tn_class */
void d_sit(tn_class* i_this) {
    get_timer_3f0(i_this) = 5;

    switch (get_behavior_mode(i_this)) {
    case 0:
        get_behavior_mode(i_this) = 1;
        anm_init(i_this, 0x34, 2.0f, 0, 1.0f, 0x0E);
        yoroi_anm_init(i_this, 0x61, 2.0f, 0, 1.0f);
        break;

    case 1:
        i_this->speedF = 0.0f;

        if (get_main_morf(i_this)->isStop()) {
            get_behavior_action(i_this) = 0;
            path_check(i_this);
            wait_set(i_this);
            get_behavior_mode(i_this) = 2;
        }
        break;

    case 10:
        get_behavior_mode(i_this) = 0x0B;
        anm_init(i_this, 0x37, 5.0f, 2, 2.0f, -1);
        yoroi_anm_init(i_this, 0x65, 5.0f, 2, 2.0f);
        get_timer_3e0(i_this) = 0x37;
        break;

    case 11:
        i_this->speedF = 0.0f;

        if (get_timer_3e0(i_this) == 0) {
            get_behavior_action(i_this) = 0;
            path_check(i_this);
            wait_set(i_this);
            get_behavior_mode(i_this) = 2;
        }
        break;
    }
}

/* 00007440-000079AC       .text stand__FP8tn_class */
void stand(tn_class* i_this) {
    get_fight_state_flag(i_this) = 0;

    s32 foundPlayer = fopAcM_otoCheck(i_this, 1000.0f);
    if (get_support_actor_id(i_this) != (fpc_ProcID)0xFFFF) {
        fpc_ProcID procId = get_support_actor_id(i_this);
        fopAc_ac_c* supportActor =
            (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &procId);
        if (supportActor != NULL && actor_field<s16>(supportActor, 0x1C0E) != 0) {
            foundPlayer |= 2;
        }
    }

    switch (get_behavior_mode(i_this)) {
    case 0:
        get_behavior_mode(i_this) = 1;
        if (get_yari_actor_flag(i_this) != 0) {
            anm_init(i_this, 0x39, tn_field<f32>(i_this, 0x151C), 2, 1.0f, -1);
        } else {
            anm_init(i_this, 0x3D, tn_field<f32>(i_this, 0x151C), 2, 1.0f, -1);
        }

        yoroi_anm_init(i_this, 0x64, tn_field<f32>(i_this, 0x151C), 0, 1.0f);
        // fallthrough
    case 1:
        cLib_addCalc2(&i_this->current.pos.x, i_this->home.pos.x, 0.5f, i_this->speed.x * 0.25f);
        cLib_addCalc2(&i_this->current.pos.z, i_this->home.pos.z, 0.5f, i_this->speed.z * 0.25f);
        cLib_addCalcAngleS2(&i_this->current.angle.y, i_this->home.angle.y, 2, 0x800);
        i_this->speedF = 0.0f;
        break;

    case 10:
        if (i_this->m03E2 == 30) {
            anm_init(i_this, 0x36, 3.0f, 0, 1.0f, -1);
        }

        if (i_this->m03E2 == 0) {
            anm_init(i_this, 0x37, 10.0f, 0, 1.0f, -1);
            get_behavior_mode(i_this) = 11;
            get_timer_3e6(i_this) = 30.0f + cM_rndF(30.0f);
        }
        break;

    case 11:
        if (get_timer_3e6(i_this) == 0) {
            get_behavior_mode(i_this) = 0;
        }
        break;

    case 20:
        if (i_this->m03E2 < 10) {
            get_fight_state_flag(i_this) = 1;
        }

        if (i_this->m03E2 == 0) {
            get_behavior_action(i_this) = 4;
            i_this->m03E2 = 0;
            get_behavior_mode(i_this) = 0;
            return;
        }
        break;

    case 50:
        anm_init(i_this, 0x37, 10.0f, 0, 1.0f, -1);
        get_behavior_mode(i_this)++;
        i_this->m03E2 = 50;
        // fallthrough
    case 51:
        i_this->speedF = 0.0f;
        if (i_this->m03E2 == 0) {
            fight_run_set(i_this);
            get_behavior_mode(i_this)++;
            get_timer_3e4(i_this) = 60;
        }
        break;

    case 52: {
        cXyz rel = i_this->home.pos - i_this->current.pos;
        get_target_angle(i_this) = cM_atan2s(rel.x, rel.z);

        if (std::sqrtf(rel.x * rel.x + rel.z * rel.z) < tn_hio_field<f32>(0x54) * 0.25f * 5.0f) {
            get_behavior_mode(i_this) = 0;
        }

        cLib_addCalcAngleS2(&i_this->current.angle.y, get_target_angle(i_this), 4, 0x1000);
        cLib_addCalc2(&i_this->speedF, tn_hio_field<f32>(0x54), 1.0f, 5.0f);
        break;
    }
    }

    if (get_behavior_mode(i_this) < 10 && foundPlayer != 0) {
        get_behavior_mode(i_this) = 10;
        i_this->m03E2 = 45.0f + cM_rndF(10.0f);
    }

    if (get_timer_3e4(i_this) == 0 && get_behavior_mode(i_this) != 20) {
        f32 range;
        if (i_this->mRangeOrFrozenAnim != 0xFF) {
            range = 10.0f * i_this->mRangeOrFrozenAnim;
        } else {
            range = 500.0f;
        }

        if (get_player_distance(i_this) < range &&
            daTn_player_view_check(i_this, &get_player_actor(i_this)->current.pos,
                                   get_view_angle_state(i_this), get_view_H(i_this)))
        {
            if (get_behavior_mode(i_this) >= 50) {
                get_behavior_action(i_this) = 4;
                i_this->m03E2 = 0;
                get_behavior_mode(i_this) = 0;
            } else {
                get_behavior_mode(i_this) = 20;
                anm_init(i_this, 0x36, 3.0f, 0, 1.0f, -1);
                i_this->m03E2 = 30;
                fopAcM_monsSeStart(i_this, JA_SE_CV_TN_FOUND, 0);
            }
        }

        if (daTn_bomb_view_check(i_this)) {
            get_behavior_action(i_this) = 9;
            get_behavior_mode(i_this) = 0;
        }
    }

    if (get_yari_actor_flag(i_this) == 0 && daTn_wepon_view_check(i_this)) {
        get_behavior_action(i_this) = 12;
        get_behavior_mode(i_this) = -1;
    }
}

/* 000079AC-00007B7C       .text d_dozou__FP8tn_class */
void d_dozou(tn_class* i_this) {
    get_timer_3f0(i_this) = 5;
    fopAcM_OffStatus(i_this, 0);
    i_this->attention_info.flags = 0;
    tn_field<s32>(i_this, 0x280) = 0;

    switch (get_behavior_mode(i_this)) {
    case 0:
        get_behavior_mode(i_this) = 1;
        get_cc_stts_0b98(i_this).Init(0xFF, 0xFF, i_this);

        if (i_this->mRangeOrFrozenAnim == 0) {
            anm_init(i_this, 0x37, 1.0f, 0, 0.0f, -1);
            get_main_morf(i_this)->setFrame(41.0f);
        } else {
            anm_init(i_this, 0x2F, 1.0f, 0, 0.0f, 0x0C);
            get_main_morf(i_this)->setFrame(27.0f);
        }

        yoroi_anm_init(i_this, 0x64, 0.0f, 0, 1.0f);
        // fallthrough
    case 1:
        if ((i_this->mEnableSpawnSwitch != 0xFF &&
             dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, fopAcM_GetRoomNo(i_this))) ||
            (i_this->mEnableSpawnSwitch == 0xFF &&
             dComIfGs_isEventBit(dSv_event_flag_c::COLORS_IN_HYRULE)))
        {
            get_main_morf(i_this)->setPlaySpeed(1.0f);
            get_behavior_mode(i_this) = 2;
        }
        break;

    case 2: {
        mDoExt_McaMorf* morf = get_main_morf(i_this);
        BOOL done = TRUE;

        if (((*reinterpret_cast<u8*>(reinterpret_cast<u8*>(morf) + 0x5D) & 1) == 0) &&
            (*reinterpret_cast<f32*>(reinterpret_cast<u8*>(morf) + 0x64) != 0.0f))
        {
            done = i_this != NULL;
        }

        if (done) {
            get_cc_stts_0b98(i_this).Init(0xF0, 0xFF, i_this);
            get_behavior_action(i_this) = 0;
            get_behavior_mode(i_this) = 0;
            tn_field<s32>(i_this, 0x280) = 4;
        }
        break;
    }
    }
}

/* 00007B7C-00008490       .text s_demo__FP8tn_class */
void s_demo(tn_class* i_this) {
    get_timer_3f0(i_this) = 5;
    fopAcM_OffStatus(i_this, 0);
    tn_field<s32>(i_this, 0x280) = 0;

    daPy_py_c* player = daPy_getPlayerActorClass();
    int frame = (int)get_main_morf(i_this)->getFrame();

    switch (get_behavior_mode(i_this)) {
    case 0:
        get_behavior_mode(i_this) = 1;
        anm_init(i_this, 0x39, 10.0f, 2, 1.0f, -1);
        yoroi_anm_init(i_this, 0x64, 10.0f, 0, 1.0f);
        // fallthrough
    case 1:
        if (reg_hio_field<s16>(0x84) == 0 &&
            !dComIfGs_isSwitch(i_this->mEnableSpawnSwitch, fopAcM_GetRoomNo(i_this)))
        {
            return;
        }

        mDoAud_bgmAllMute(30);
        anm_init(i_this, 0x54, 3.0f, 0, 1.0f, 0x24);
        yoroi_anm_init(i_this, 0x56, 3.0f, 0, 1.0f);
        get_behavior_mode(i_this) = 2;
        break;

    case 2:
        if (frame == 0x7F) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_TN_FOUND, 0);
        }

        if (frame == 0xAC) {
            mDoAud_subBgmStart(0x80000019);
        }

        if (frame == 0xC1) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_TN_KAMAE_L, 0);
        }

        if (frame == 0xE7 || frame == 0x106) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_TN_ATTACK_L, 0);
        }

        if (is_morf_motion_done(get_main_morf(i_this))) {
            get_behavior_action(i_this) = 4;
            get_behavior_mode(i_this) = 0;
        }
        break;

    case 10: {
        get_f32_b94(i_this) = 10000.0f;
        i_this->current.pos.y = i_this->home.pos.y + 5000.0f;
        i_this->speed.y = 0.0f;

        dEvent_manager_c* eventMgr = dComIfGp_getPEvtManager();
        BOOL hasEvent =
            (eventMgr->getEventData(dComIfGp_evmng_getEventIdx("btl_of_swroom")) != NULL) ||
            (eventMgr->getEventData(dComIfGp_evmng_getEventIdx("btl_of_swroom2")) != NULL);

        if (!hasEvent && s_check == 0) {
            return;
        }

        int staffId = dComIfGp_evmng_getMyStaffId("Tn", NULL, 0);
        if (staffId == -1 && s_check == 0) {
            return;
        }

        if (s_check == 0 && strcmp(eventMgr->getMyNowCutName(staffId), "Tkwn") != 0) {
            return;
        }

        mDoAud_bgmAllMute(30);
        i_this->current.pos.z -= 0.2f;

        if (i_this->home.pos.x < 0.0f) {
            i_this->current.pos.x += 250.0f;
            i_this->current.pos.y = i_this->home.pos.y + 2750.0f;
            get_demo_flag_1519(i_this) = 1;
        } else {
            i_this->current.pos.x += -130.0f;
            i_this->current.pos.y = i_this->home.pos.y + 10.0f;
            get_demo_flag_1519(i_this) = 0;
        }

        mDoAud_seStart(0x5929, &i_this->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        s_check++;

        anm_init(i_this, 0x55, 3.0f, 0, 1.0f, 0x25);
        yoroi_anm_init(i_this, 0x57, 3.0f, 0, 1.0f);
        tate_anm_init(i_this, 0x55, 3.0f, 2, 1.0f);
        get_behavior_mode(i_this) = 11;
        break;
    }

    case 11: {
        dEvent_manager_c* eventMgr = dComIfGp_getPEvtManager();
        BOOL hasEvent =
            (eventMgr->getEventData(dComIfGp_evmng_getEventIdx("btl_of_swroom")) != NULL) ||
            (eventMgr->getEventData(dComIfGp_evmng_getEventIdx("btl_of_swroom2")) != NULL);

        if (hasEvent) {
            int staffId = dComIfGp_evmng_getMyStaffId("Tn", NULL, 0);
            if (staffId != -1 && strcmp(eventMgr->getMyNowCutName(staffId), "GanonJ") == 0) {
                i_this->current.pos.x = i_this->home.pos.x;

                if (player != NULL) {
                    get_angle_20e(i_this) =
                        cM_atan2s(player->current.pos.x - i_this->current.pos.x,
                                  player->current.pos.z - i_this->current.pos.z);
                }
            }
        }

        if ((get_status_flags_9b8(i_this) & 0x20) != 0) {
            get_main_morf(i_this)->setPlaySpeed(1.0f);
            get_yoroi_morf(i_this)->setPlaySpeed(1.0f);
            get_tate_morf(i_this)->setPlaySpeed(1.0f);

            mDoAud_seStart(0x592A, &i_this->current.pos, 0,
                           dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));

            if ((s8)get_demo_flag_1519(i_this) == 0) {
                get_behavior_mode(i_this) = 12;
            } else {
                get_behavior_mode(i_this) = 13;
            }

            if (i_this->home.pos.x < 0.0f) {
                dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
            } else {
                dComIfGp_getVibration().StartShock(2, -0x11, cXyz(0.0f, 1.0f, 0.0f));
            }
        }
        break;
    }

    case 12:
        if (frame == 0x2B) {
            if (s_check == 10) {
                get_behavior_mode(i_this) = 13;
            } else {
                get_main_morf(i_this)->setPlaySpeed(0.0f);
                get_yoroi_morf(i_this)->setPlaySpeed(0.0f);
                get_tate_morf(i_this)->setPlaySpeed(0.0f);
            }
        }
        break;

    case 13:
        get_main_morf(i_this)->setPlaySpeed(1.0f);
        get_yoroi_morf(i_this)->setPlaySpeed(1.0f);
        get_tate_morf(i_this)->setPlaySpeed(1.0f);

        if (frame == 0x2B) {
            s_check = 10;
        }

        if (frame == 0x3F) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_TN_KAMAE_L, 0);
        }

        if (frame == 0x73) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_TN_ATTACK_L, 0);
        }

        if (frame == reg_hio_field<s16>(0x92) + 0xD2) {
            tate_anm_init(i_this, 0x3C, 5.0f, 2, 1.0f);
        }

        if (is_morf_motion_done(get_main_morf(i_this))) {
            get_behavior_action(i_this) = 4;
            get_behavior_mode(i_this) = 0;
            get_f32_b94(i_this) = 1000.0f;
            mDoAud_subBgmStart(0x80000019);
        }
        break;

    case 20:
        get_behavior_mode(i_this) = 21;
        anm_init(i_this, 0x39, 1.0f, 2, 1.0f, -1);
        yoroi_anm_init(i_this, 0x64, 1.0f, 0, 1.0f);
        get_timer_3e0(i_this) = 30;
        // fallthrough
    case 21:
        if (get_timer_3e0(i_this) == 0) {
            anm_init(i_this, 0x35, 15.0f, 2, 1.0f, -1);
            get_timer_3e0(i_this) = 30;
            get_behavior_mode(i_this) = 22;
            fopAcM_monsSeStart(i_this, JA_SE_CV_TN_KAMAE_L, 0);
        }
        break;

    case 22:
        if (get_timer_3e0(i_this) == 0) {
            get_behavior_action(i_this) = 4;
            get_behavior_mode(i_this) = 2;
            get_timer_3e6(i_this) = 60;
        }
        break;
    }
}

/* 00008490-000086D4       .text demo_camera__FP8tn_class */
void demo_camera(tn_class* i_this) {
    dCamera_c* camera = dCam_getBody();

    BOOL cameraActive = TRUE;

    switch ((s8)get_demo_cam_state(i_this)) {
    case 0:
        cameraActive = FALSE;
        break;

    case 50:
        if (!i_this->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(i_this, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            i_this->eventInfo.onCondition(dEvtCnd_UNK2_e);
            cameraActive = FALSE;
            break;
        }

        camera->Stop();
        camera->SetTrimSize(1);
        get_demo_cam_state(i_this) = 0x33;

        u8* cameraInfo = *reinterpret_cast<u8**>(reinterpret_cast<u8*>(&g_dComIfG_gameInfo) + 0x5B10);
        get_demo_cam_eye(i_this).x = *reinterpret_cast<f32*>(cameraInfo + 0xD8);
        get_demo_cam_eye(i_this).y = *reinterpret_cast<f32*>(cameraInfo + 0xDC);
        get_demo_cam_eye(i_this).z = *reinterpret_cast<f32*>(cameraInfo + 0xE0);
        get_demo_cam_center(i_this).x = *reinterpret_cast<f32*>(cameraInfo + 0xE4);
        get_demo_cam_center(i_this).y = *reinterpret_cast<f32*>(cameraInfo + 0xE8);
        get_demo_cam_center(i_this).z = *reinterpret_cast<f32*>(cameraInfo + 0xEC);
        get_demo_cam_fovy(i_this) = 55.0f;
        get_demo_cam_timer(i_this) = 0;
        // fallthrough

    case 51:
    case 52:
    case 53:
        cLib_addCalc2(&get_demo_cam_fovy(i_this), 30.0f + reg_hio_field<f32>(0x40), 0.2f,
                      0.6f + reg_hio_field<f32>(0x44));

        if (get_draw_skip_flag(i_this) == 0) {
            cLib_addCalc2(&get_demo_cam_center(i_this).x, i_this->current.pos.x, 0.1f, 10.0f);
            cLib_addCalc2(&get_demo_cam_center(i_this).y,
                          230.0f + i_this->current.pos.y + reg_hio_field<f32>(0x3C), 0.1f,
                          10.0f);
            cLib_addCalc2(&get_demo_cam_center(i_this).z, i_this->current.pos.z, 0.1f, 10.0f);
        }

        get_demo_cam_timer(i_this)++;

        if (get_demo_cam_timer(i_this) > 150) {
            camera->SetTrimSize(0);
            camera->Start();
            dMeter_mtrShow();

            u16& eventCtrl = *reinterpret_cast<u16*>(reinterpret_cast<u8*>(&g_dComIfG_gameInfo) +
                                                     0x52C0);
            eventCtrl |= 8;

            fopAcM_delete(i_this);
        }
        break;
    }

    if (cameraActive) {
        camera->Set(get_demo_cam_center(i_this), get_demo_cam_eye(i_this), get_demo_cam_fovy(i_this),
                    0);
    }
}

/* 000086D4-00008C5C       .text Tn_move__FP8tn_class */
void Tn_move(tn_class* i_this) {
    daPy_py_c* player = daPy_getPlayerActorClass();

    get_side_step_angle(i_this) = 0;
    get_fight_state_flag(i_this) = 0;
    cLib_addCalcAngleS2(&get_watch_turn_angle(i_this), 0, 2, 0x800);

    if (get_behavior_mode(i_this) <= -100) {
        get_timer_3f0(i_this) = 5;

        if (std::fabsf(get_hukki_f32_8ec(i_this)) > 40.0f) {
            if ((get_status_flags_9b8(i_this) & 0x20) == 0) {
                get_sph_1244(i_this).SetC(get_pos_604(i_this));
                get_sph_1244(i_this).SetR(108.0f);

                tn_field<u32>(i_this, 0x112C) &= ~4;
                tn_field<u32>(i_this, 0x1158) |= 1;
                tn_field<u8>(i_this, 0x119B) = 1;

                dComIfG_Ccsp()->Set(&get_weapon_sph_a(i_this));
                dComIfG_Ccsp()->SetMass(&get_weapon_sph_a(i_this), 3);

                if (get_weapon_sph_a(i_this).ChkAtHit()) {
                    if (i_this->speed.y < 50.0f) {
                        i_this->speed.y = 0.0f;
                        get_hukki_f32_8e8(i_this) = 5.0f;
                    }
                }
            }

            get_flags_ca0(i_this) &= ~1;
            return;
        }
    }

    tn_field<u32>(i_this, 0x112C) |= 4;
    get_flags_ca0(i_this) |= 1;

    bool skipActionUpdate = false;
    if (get_hukki_timer_8fe(i_this) != 0 && get_hukki_timer_8fc(i_this) == 0) {
        if (get_hukki_timer_8fe(i_this) == 1) {
            get_behavior_action(i_this) = 4;
            get_behavior_mode(i_this) = 0;
            i_this->m03E2 = 0;
        } else {
            get_target_angle(i_this) = get_view_angle_state(i_this);
            i_this->speedF = -30.0f;
        }

        skipActionUpdate = true;
    }

    if (!skipActionUpdate) {
        cXyz rel;
        if (get_timer_1436(i_this) != 0) {
            get_timer_1436(i_this)--;
            rel = get_pos_1438(i_this) - i_this->current.pos;
        } else {
            get_player_actor(i_this) = player;
            rel = get_player_actor(i_this)->current.pos - i_this->current.pos;
        }

        get_player_distance(i_this) = std::sqrtf(rel.x * rel.x + rel.z * rel.z);
        get_view_angle_state(i_this) = cM_atan2s(rel.x, rel.z);
        get_search_cyl(i_this).SetR(80.0f + reg_hio_field<f32>(0x18));

        if ((s8)get_timer_1434(i_this) != 0) {
            get_timer_1434(i_this)--;
            if ((s8)get_timer_1434(i_this) == 0) {
                get_behavior_action(i_this) = 18;
                get_behavior_mode(i_this) = 0;
            }
        }

        switch (get_behavior_action(i_this)) {
        case 0:
            jyunkai(i_this);
            break;
        case 1:
            stand(i_this);
            break;
        case 4:
            fight_run(i_this);
            break;
        case 5:
            fight(i_this);
            break;
        case 8:
            p_lost(i_this);
            break;
        case 9:
            b_nige(i_this);
            break;
        case 10:
            defence(i_this);
            break;
        case 11:
            hukki(i_this);
            break;
        case 12:
            wepon_search(i_this);
            break;
        case 14:
            aite_miru(i_this);
            break;
        case 17:
            d_sit(i_this);
            break;
        case 18:
            d_mahi(i_this);
            break;
        case 20:
            fail(i_this);
            break;
        case 21:
            yogan_fail(i_this);
            break;
        case 23:
            d_dozou(i_this);
            break;
        case 25:
            s_demo(i_this);
            break;
        }
    }

    if (i_this->mBehaviorType == 4 && get_behavior_action(i_this) == 4) {
        cXyz homeRel = i_this->home.pos - i_this->current.pos;

        f32 distLimit;
        if (i_this->mRangeOrFrozenAnim != 0xFF) {
            distLimit = 1.5f * (10.0f * i_this->mRangeOrFrozenAnim);
        } else {
            distLimit = 750.0f;
        }

        if (std::sqrtf(homeRel.x * homeRel.x + homeRel.z * homeRel.z) > distLimit) {
            if (i_this->mBehaviorType == 4) {
                get_behavior_action(i_this) = 1;
            }

            get_behavior_mode(i_this) = 0x33;
            i_this->m03E2 = 0;
            get_timer_3e4(i_this) = 60;
        }
    }

    cXyz moveVec(0.0f, 0.0f, i_this->speedF);

    if (get_behavior_action(i_this) != 11 && get_behavior_action(i_this) != 20 &&
        get_hukki_timer_8fe(i_this) == 0)
    {
        get_hukki_angle_8f6(i_this) = i_this->current.angle.y;
        mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y + get_side_step_angle(i_this));
    } else {
        mDoMtx_YrotS(*calc_mtx, get_target_angle(i_this));
    }

    cXyz out;
    MtxPosition(&moveVec, &out);
    i_this->speed.x = out.x;
    i_this->speed.z = out.z;
}

/* 00008C5C-00008F9C       .text yoroi_break__FP8tn_classP4cXyzUc */
void yoroi_break(tn_class*, cXyz*, unsigned char) {
    /* Nonmatching */
}

/* 00008F9C-00009E2C       .text damage_check__FP8tn_class */
void damage_check(tn_class*) {
    /* Nonmatching */
}

/* 00009E68-0000AC54       .text part_move__FP8tn_classi */
void part_move(tn_class*, int) {
    /* Nonmatching */
}

/* 0000AC54-0000AEA8       .text spin_blur_set__FP8tn_class */
void spin_blur_set(tn_class* i_this) {
    if (get_mode_timer_14f4(i_this) == 0) {
        return;
    }

    cXyz trail_base(0.0f, 0.0f, 250.0f + reg_hio_field<f32>(0x1C));
    MTXCopy(get_main_morf(i_this)->getModel()->getAnmMtx(0x11), *calc_mtx);

    cXyz transformed_base;
    MtxPosition(&trail_base, &transformed_base);
    trail_base = transformed_base - i_this->current.pos;

    cXyz* pos_array = &tn_field<cXyz>(i_this, 0x147C);
    for (int i = 0; i < 10; i++) {
        mDoMtx_YrotS(*calc_mtx, i * (reg_hio_field<s16>(0x88) - 0x320));
        MtxPosition(&trail_base, &pos_array[i]);
        PSVECAdd(&pos_array[i], &i_this->current.pos, &pos_array[i]);
    }

    for (int i = 0; i < 3; i++) {
        dPa_cutTurnEcallBack_c& callback = tn_field<dPa_cutTurnEcallBack_c>(i_this, 0x144C + i * 0x10);

        if (get_mode_timer_14f6(i_this) == 0) {
            callback.end();
        } else {
            if (get_mode_timer_14f4(i_this) == 1) {
                const GXColor* prim_color;
                const GXColor* env_color;

                if (get_mode_timer_14f6(i_this) >= 5) {
                    prim_color = i == 1 ? &roll_prim1 : &roll_prim0;
                    env_color = &roll_env;
                } else {
                    prim_color = i == 1 ? &turn_prim1 : &turn_prim0;
                    env_color = &turn_env;
                }

                JPABaseEmitter* emitter = dComIfGp_particle_set(
                    spin_eff_name[i], &i_this->current.pos, &i_this->shape_angle, &i_this->scale,
                    0xFF, &callback, 0, prim_color, env_color, NULL);

                if (emitter != NULL) {
                    emitter->mGlobalParticleScale.x = 1.5f + reg_hio_field<f32>(0x50);
                }

                get_mode_timer_14f4(i_this)++;
            }

            callback.setPosArray(pos_array, 10);
        }
    }

    if (get_mode_timer_14f6(i_this) == 0) {
        get_mode_timer_14f4(i_this) = 0;
    } else {
        get_mode_timer_14f6(i_this)--;
    }
}

/* 0000AEA8-0000BCE4       .text daTn_Execute__FP8tn_class */
static BOOL daTn_Execute(tn_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    if ((s8)tn_field<u8>(i_this, 0x1520) != 0) {
        tn_field<u8>(i_this, 0x1520)--;
        if ((s8)tn_field<u8>(i_this, 0x1520) == 0) {
            tn_field<u32>(i_this, 0x01C4) &= ~0x4000;
        }
    }

    if (enemy_ice(&tn_field<enemyice>(i_this, 0x1524))) {
        if ((s8)tn_field<u8>(i_this, 0x152A) == 0) {
            if (get_behavior_action(i_this) == 23) {
                get_main_morf(i_this)->setPlaySpeed(3.0f);
                get_tate_morf(i_this)->setPlaySpeed(3.0f);
                get_yoroi_morf(i_this)->setPlaySpeed(3.0f);
                fopAcM_monsSeStart(i_this, 0x488A, 0);
            }

            get_main_morf(i_this)->play(&i_this->eyePos, 0, 0);
            get_yoroi_morf(i_this)->play(NULL, 0, 0);
            get_tate_morf(i_this)->play(NULL, 0, 0);
        }

        get_main_morf(i_this)->calc();
        get_tate_morf(i_this)->calc();
        get_yoroi_morf(i_this)->calc();

        for (int i = 0; i < 3; i++) {
            if ((s8)tn_field<u8>(i_this, 0x02E8 + i * 0x4C) >= 0) {
                part_move(i_this, i);
            }
        }

        tn_field<u8>(i_this, 0x02DD) = 0;

        if (get_behavior_action(i_this) == 1) {
            path_check(i_this);
            wait_set(i_this);
            tate_anm_init(i_this, TN_BCK_ATATE_ON1, 1.0f, J3DFrameCtrl::EMode_LOOP, 3.0f);
        }

        return TRUE;
    }

    if (i_this->home.pos.y - i_this->current.pos.y > 4000.0f) {
        fopAcM_delete(i_this);
        return TRUE;
    }

    if (tn_hio_field<u8>(0x06) == 0 || CPad_CHECK_TRIG_B(0) || CPad_CHECK_HOLD_Y(0)) {
        get_flags_3d8(i_this)++;

        for (int i = 0; i < 5; i++) {
            s16& timer = tn_field<s16>(i_this, 0x03E0 + i * 2);
            if (timer != 0) {
                timer--;
            }
        }

        if (get_timer_3ea(i_this) != 0) {
            get_timer_3ea(i_this)--;
        }

        if (get_search_mode(i_this) != 0) {
            get_search_mode(i_this)--;
        }

        if (tn_field<s16>(i_this, 0x1402) != 0) {
            tn_field<s16>(i_this, 0x1402)--;
        }

        if (get_hukki_timer_8fe(i_this) != 0) {
            get_hukki_timer_8fe(i_this)--;
        }

        if (get_timer_3f0(i_this) != 0) {
            get_timer_3f0(i_this)--;
        }

        if (get_timer_3f2(i_this) != 0) {
            get_timer_3f2(i_this)--;
        }

        if ((s8)tn_field<u8>(i_this, 0x140C) != 0) {
            fpc_ProcID procId = get_yari_actor_id(i_this);
            fopAc_ac_c* actor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &procId);
            if (actor != NULL) {
                tn_field<u8>(i_this, 0x140C) = 0;
                fopAcM_setCarryNow(actor, FALSE);
            }
        }

        if (get_draw_disable_flag(i_this) != 0) {
            if (reg_hio_field<s16>(0x84) != 0 ||
                dComIfGs_isSwitch(get_draw_disable_flag(i_this) - 1, fopAcM_GetRoomNo(i_this)))
            {
                get_draw_disable_flag(i_this) = 0;
            } else {
                tn_field<s32>(i_this, 0x0280) = 0;

                fpc_ProcID procId = get_yari_actor_id(i_this);
                fopAc_ac_c* actor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &procId);
                if (actor != NULL) {
                    MtxTrans(-10000.0f, -10000.0f, 0.0f, 0);
                    void* matrixOwner = actor_field<void*>(actor, 0x0298);
                    if (matrixOwner != NULL) {
                        MTXCopy(*calc_mtx,
                                reinterpret_cast<MtxP>(reinterpret_cast<u8*>(matrixOwner) + 0x24));
                    }
                }

                if (get_support_actor_id(i_this) != (fpc_ProcID)0xFFFF) {
                    fpc_ProcID supportId = get_support_actor_id(i_this);
                    fopAc_ac_c* support =
                        (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &supportId);
                    if (support != NULL) {
                        actor_field<f32>(support, 0x1BE0) = -10000.0f;
                        actor_field<f32>(support, 0x1BE4) = 0.0f;
                        actor_field<f32>(support, 0x1BE8) = -50.0f;
                        actor_field<f32>(support, 0x1BEC) = -10000.0f;
                        actor_field<f32>(support, 0x1BF0) = 0.0f;
                        actor_field<f32>(support, 0x1BF4) = -50.0f;
                    }
                }

                return TRUE;
            }
        }

        if ((s8)tn_field<u8>(i_this, 0x14F8) == 0) {
            tn_field<s32>(i_this, 0x0280) = 4;
            tn_field<u32>(i_this, 0x01C4) |= 0x20;
        } else {
            tn_field<s32>(i_this, 0x0280) = 0;
            tn_field<u32>(i_this, 0x01C4) &= ~0x20;
        }

        if (get_timer_3ee(i_this) == 0) {
            get_main_morf(i_this)->play(&i_this->eyePos, 0, 0);
            get_yoroi_morf(i_this)->play(NULL, 0, 0);
            if ((i_this->mRemainingEquipmentPieces & 4) != 0) {
                get_tate_morf(i_this)->play(NULL, 0, 0);
            }
        }

        if (get_main_brk(i_this) != NULL) {
            get_main_brk(i_this)->setFrame(i_this->mArmorColorIndex);
        }

        get_fx_f32_29c(i_this) = 1.0f;
        get_fx_f32_2a0(i_this) = 1.0f;
        get_fx_f32_298(i_this) = 50.0f;
        get_fx_u8_2a8(i_this) = 0;
        get_fx_f32_2a4(i_this) = 0.0f;

        damage_check(i_this);
        Tn_move(i_this);
        demo_camera(i_this);
        ground_smoke_set(i_this);

        if (get_timer_3ee(i_this) != 0) {
            get_timer_3ee(i_this)--;
        }

        tn_field<fopAc_ac_c*>(i_this, 0x0474) = i_this;
        tn_field<s16>(i_this, 0x047C) = 3;
    }

    i_this->shape_angle = i_this->current.angle;

    int damageResult = 0;
    int reaction = damage_reaction(&tn_field<damagereaction>(i_this, 0x0474));
    if (reaction != 0) {
        tn_field<s16>(i_this, 0x0430) = 1;
        get_watch_target_id(i_this) = fpcM_ERROR_PROCESS_ID_e;

        switch (reaction) {
        case 1:
            anm_init(i_this, TN_BCK_BDOWN_A1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            if (get_yari_actor_flag(i_this) != 0 && i_this->mRangeOrFrozenAnim > 0 && damageResult < 4 &&
                cM_rndF(1.0f) < 0.5f)
            {
                get_yari_state(i_this) = 1;
            }
            get_behavior_action(i_this) = 0;
            break;

        case 2:
            anm_init(i_this, TN_BCK_BDOWN_U1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            break;

        case 5:
            if (get_behavior_action(i_this) != 4 && get_behavior_action(i_this) != 11) {
                wait_set(i_this);
                get_behavior_action(i_this) = 4;
                get_behavior_mode(i_this) = 0;
                i_this->m03E2 = 30;
            }
            tn_field<s16>(i_this, 0x041A) = 5;
            tn_field<s16>(i_this, 0x0428) = -0x4000;
            break;

        case 10:
            wait_set(i_this);
            get_behavior_mode(i_this) = 2;
            get_behavior_action(i_this) = 0;
            path_check(i_this);
            break;

        case 20:
            tn_field<s16>(i_this, 0x041A) = 1;
            tn_field<s16>(i_this, 0x0428) = -0x4000;
            tn_field<s16>(i_this, 0x0430) = tn_hio_field<s16>(0x20) + 16;
            tn_field<u8>(i_this, 0x0432) = 1;
            tn_field<s16>(i_this, 0x0940) = tn_hio_field<s16>(0x80);
            break;

        case 21:
            tn_field<s16>(i_this, 0x041A) = 1;
            tn_field<s16>(i_this, 0x0428) = 0;
            tn_field<s16>(i_this, 0x0940) = tn_hio_field<s16>(0x80);
            break;

        case 30:
            anm_init(i_this, TN_BCK_BDOWN_U1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            if (get_yari_actor_flag(i_this) != 0) {
                get_yari_state(i_this) = 1;
            }
            get_behavior_action(i_this) = 0;
            break;
        }
    }

    get_main_morf(i_this)->getModel()->setBaseTRMtx(*calc_mtx);

    if ((i_this->mRemainingEquipmentPieces & 4) != 0) {
        get_tate_morf(i_this)->getModel()->setBaseTRMtx(*calc_mtx);
        get_tate_morf(i_this)->calc();
    }

    get_main_morf(i_this)->calc();
    enemy_fire(&tn_field<enemyfire>(i_this, 0x18DC));

    yari_off_check(i_this);

    for (int i = 0; i < 3; i++) {
        if ((s8)tn_field<u8>(i_this, 0x02E8 + i * 0x4C) >= 0) {
            part_move(i_this, i);
        }
    }

    tn_field<u8>(i_this, 0x02DD) = 0;
    spin_blur_set(i_this);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->current.pos, &i_this->tevStr);

    return TRUE;
}

/* 0000BCE4-0000BCEC       .text daTn_IsDelete__FP8tn_class */
static BOOL daTn_IsDelete(tn_class*) {
    return TRUE;
}

/* 0000BCEC-0000BE58       .text daTn_Delete__FP8tn_class */
static BOOL daTn_Delete(tn_class* i_this) {

    dComIfG_resDelete(&get_phase_2b4(i_this), "Tkwn");
    dComIfG_resDelete(&get_phase_2ac(i_this), "Tn");

    if (get_hio_created_1433(i_this) != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_tnHIO.mNo);
    }

    tn_field<dPa_cutTurnEcallBack_c>(i_this, 0x144C).end();
    tn_field<dPa_cutTurnEcallBack_c>(i_this, 0x145C).end();
    tn_field<dPa_cutTurnEcallBack_c>(i_this, 0x146C).end();

    call_vtbl_method_20(reinterpret_cast<u8*>(i_this) + 0x0434);
    call_vtbl_method_20(reinterpret_cast<u8*>(i_this) + 0x0454);
    call_vtbl_method_20(reinterpret_cast<u8*>(i_this) + 0x0BE8);

    if (i_this->heap != NULL) {
        get_main_morf(i_this)->stopZelAnime();
    }

    if (get_support_actor_id(i_this) != (fpc_ProcID)0xFFFF) {
        fpc_ProcID procId = get_support_actor_id(i_this);
        fopAc_ac_c* actor = (fopAc_ac_c*)fopAcIt_Judge(fpcSch_JudgeByID, &procId);
        if (actor != NULL) {
            fopAcM_delete(actor);
        }
    }

    if ((s8)i_this->mRangeOrFrozenAnim == -0x80 && (tn_field<u32>(i_this, 0x01C4) & 0x04000000) != 0)
    {
        if (s_check == 0) {
            mDoAud_subBgmStop();
        } else {
            s_check = 0;
        }
    }

    enemy_fire_remove(&get_enemy_fire_18dc(i_this));
    return TRUE;
}

/* 0000BE58-0000BEBC       .text useArrowHeapInit__FP10fopAc_ac_c */
static BOOL useArrowHeapInit(fopAc_ac_c* i_actor) {
    tn_class* i_this = reinterpret_cast<tn_class*>(i_actor);
    get_arrow_hit_1b04(i_this) = JntHit_create(get_main_morf(i_this)->getModel(), search_data, 10);

    if (get_arrow_hit_1b04(i_this) != NULL) {
        tn_field<JntHit_c*>(i_this, 0x0250) = get_arrow_hit_1b04(i_this);
        return TRUE;
    }

    return FALSE;
}

/* 0000BEBC-0000C498       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_actor) {
    tn_class* i_this = reinterpret_cast<tn_class*>(i_actor);

    mDoExt_McaMorf*& mainMorf = tn_field<mDoExt_McaMorf*>(i_this, 0x02C4);
    mDoExt_McaMorf*& tateMorf = tn_field<mDoExt_McaMorf*>(i_this, 0x02C8);
    mDoExt_McaMorf*& yoroiMorf = tn_field<mDoExt_McaMorf*>(i_this, 0x02CC);
    mDoExt_brkAnm*& mainBrk = tn_field<mDoExt_brkAnm*>(i_this, 0x02D8);

    mainMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Tn", TN_BMD_TN_MAIN), NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("Tn", TN_BCK_ANIOU1), J3DFrameCtrl::EMode_LOOP,
        1.0f, 0, -1, 0, NULL, 0, 0x11020203);

    if (mainMorf == NULL || mainMorf->getModel() == NULL) {
        return FALSE;
    }

    J3DModel* mainModel = mainMorf->getModel();
    mainModel->setUserArea((u32)i_this);

    for (u16 i = 0; i <= 0x20; i++) {
        s32 joint = joint_check[i];
        if (joint >= 0) {
            if ((joint >= 0x0E && joint <= 0x11) || joint == 0x14) {
                mainModel->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_P);
            } else {
                mainModel->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
            }
        } else if (i == 0x1E || i == 0x20) {
            mainModel->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_mimi);
        }
    }

    tateMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Tn", TN_BMD_TN_MAIN), NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("Tn", TN_BCK_ATATE_ON1), J3DFrameCtrl::EMode_LOOP,
        1.0f, 0, -1, 0, NULL, 0, 0x11020203);

    if (tateMorf == NULL || tateMorf->getModel() == NULL) {
        return FALSE;
    }

    J3DModel* tateModel = tateMorf->getModel();
    tateModel->setUserArea((u32)i_this);
    tateModel->getModelData()->getJointNodePointer(10)->setCallBack(nodeCallBack_kata);

    mainBrk = new mDoExt_brkAnm();
    if (mainBrk == NULL) {
        return FALSE;
    }

    if (!mainBrk->init(mainMorf->getModel()->getModelData(),
                                    (J3DAnmTevRegKey*)dComIfG_getObjectRes("Tn", TN_BRK_TN_MAIN),
                                    TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false))
    {
        return FALSE;
    }

    for (int i = 0; i < 3; i++) {
        tn_part_info& part = get_part_info(i_this, i);

        if (i == 0) {
            yoroiMorf = new mDoExt_McaMorf(
                (J3DModelData*)dComIfG_getObjectRes("Tn", TN_BMD_TN_YOROI1), NULL, NULL,
                (J3DAnmTransform*)dComIfG_getObjectRes("Tn", TN_BCK_YKIHON1),
                J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 0, NULL, 0, 0x11020203);

            if (yoroiMorf == NULL || yoroiMorf->getModel() == NULL) {
                return FALSE;
            }

            part.mpModel = yoroiMorf->getModel();
        } else {
            u16 bmdId = TN_BMD_TN_TATE1;
            if (i == 1) {
                bmdId = (i_this->mEquipmentType & 1) ? TN_BMD_TN_KABUTO2 : TN_BMD_TN_KABUTO1;
            }

            part.mpModel = mDoExt_J3DModel__create(
                (J3DModelData*)dComIfG_getObjectRes("Tn", bmdId), 0, 0x11020203);

            if (part.mpModel == NULL) {
                return FALSE;
            }
        }

        part.mpBrkAnm = new mDoExt_brkAnm();
        if (part.mpBrkAnm == NULL) {
            return FALSE;
        }

        u16 brkId;
        if (i == 0) {
            brkId = TN_BRK_TN_YOROI1;
        } else if (i == 1) {
            brkId = (i_this->mEquipmentType & 1) ? TN_BRK_TN_KABUTO2 : TN_BRK_TN_KABUTO1;
        } else {
            brkId = TN_BRK_TN_TATE1;
        }

        if (!part.mpBrkAnm->init(part.mpModel->getModelData(),
                                 (J3DAnmTevRegKey*)dComIfG_getObjectRes("Tn", brkId), TRUE,
                                 J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false))
        {
            return FALSE;
        }
    }

    return useArrowHeapInit(i_actor) ? 4 : 0;
}

/* 0000C4E0-0000CBFC       .text daTn_Create__FP10fopAc_ac_c */
static cPhs_State daTn_Create(fopAc_ac_c* i_actor) {
    static dCcD_SrcCyl co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 90.0f,
            /* Height */ 125.0f,
        }},
    };
    static dCcD_SrcCyl tg_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 45.0f,
            /* Height */ 137.5f,
        }},
    };
    static dCcD_SrcSph head_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 55.0f,
        }},
    };
    static dCcD_SrcSph wepon_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8 | AT_TYPE_SKULL_HAMMER,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 100.0f,
        }},
    };
    static dCcD_SrcSph wepon2_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8 | AT_TYPE_SKULL_HAMMER,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 62.5f,
        }},
    };
    static dCcD_SrcSph defence_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 62.5f,
        }},
    };

    static u8 fire_j[] = {
        0x13,
        0x14,
        0x15,
        0x16,
        0x11,
        0x12,
        0x0F,
        0x10,
        0x0D,
        0x0E,
    };

    static f32 fire_sc[] = {
        2.0f,
        1.5f,
        1.2f,
        1.0f,
        1.2f,
        1.0f,
        1.2f,
        1.0f,
        1.2f,
        1.0f,
    };

    tn_class* i_this = reinterpret_cast<tn_class*>(i_actor);
    fopAcM_SetupActor(i_this, tn_class);

    cPhs_State phase = dComIfG_resLoad(&get_phase_2b4(i_this), "Tkwn");
    if (phase != cPhs_COMPLEATE_e) {
        return phase;
    }

    phase = dComIfG_resLoad(&get_phase_2ac(i_this), "Tn");
    if (phase != cPhs_COMPLEATE_e) {
        return phase;
    }

    tn_field<u8>(i_this, 0x0466) = 1;
    tn_field<u8>(i_this, 0x01C2) = 3;

    if (strcmp(dComIfGp_getStartStageName(), "ITest63") == 0 ||
        strcmp(dComIfGp_getStartStageName(), "GanonJ") == 0)
    {
        search_sp = 1;
    } else {
        search_sp = 0;
    }

    u32 params = fopAcM_GetParam(i_this);
    i_this->mBehaviorType = params & 0xF;
    i_this->mArmorColorIndex = (params >> 24) & 0xF;
    i_this->mRangeOrFrozenAnim = (params >> 16) & 0xFF;
    i_this->mPathIndex = (params >> 8) & 0xFF;
    i_this->mEnableSpawnSwitch = (params >> 24) & 0xFF;
    i_this->mDisableSpawnOnDeathSwitch = (u8)i_this->home.angle.x;

    if (reg_hio_field<s16>(0x84) != 0 ||
        (i_this->mDisableSpawnOnDeathSwitch != 0 && i_this->mDisableSpawnOnDeathSwitch <= 0x7F))
    {
        tn_field<u32>(i_this, 0x01C4) |= 0x04000000;
        search_sp = 1;
    }

    if (i_this->mEnableSpawnSwitch != 0xFF) {
        get_draw_disable_flag(i_this) = i_this->mEnableSpawnSwitch + 1;
        tn_field<u32>(i_this, 0x01C4) |= 0x4000;
        tn_field<u8>(i_this, 0x1520) = 10;
    }

    i_this->mEquipmentType = (i_this->home.angle.z >> 5) & 7;
    i_this->home.angle.x = 0;
    i_this->home.angle.z = 0;

    if (i_this->mArmorColorIndex > 5) {
        i_this->mArmorColorIndex = 5;
    }

    if (i_this->mEquipmentType > 5) {
        i_this->mEquipmentType = 5;
    }

    if (i_this->mEquipmentType < 2) {
        i_this->mRemainingEquipmentPieces = 0x0B;
    } else {
        i_this->mRemainingEquipmentPieces = 0x0F;
    }

    if (i_this->mDisableSpawnOnDeathSwitch == 0xFF) {
        i_this->mDisableSpawnOnDeathSwitch = 0;
    }

    if (i_this->mDisableSpawnOnDeathSwitch != 0 &&
        dComIfGs_isSwitch(i_this->mDisableSpawnOnDeathSwitch, fopAcM_GetRoomNo(i_this)))
    {
        return cPhs_ERROR_e;
    }

    s_check = 0;

    if (i_this->mBehaviorType == 0x0D || i_this->mBehaviorType == 0x0E) {
        tn_field<u32>(i_this, 0x01C4) |= 0x04000000;
        search_sp = 1;

        if (i_this->mBehaviorType == 0x0D) {
            get_behavior_mode(i_this) = 0;
        } else {
            get_behavior_mode(i_this) = 10;
            i_this->current.pos.y += 1000.0f;
            tn_field<u32>(i_this, 0x01C4) |= 0x4000;
        }

        get_behavior_action(i_this) = 0x19;
        i_this->mBehaviorType = 0;
        get_draw_disable_flag(i_this) = 0;
    } else if (i_this->mBehaviorType == 0x0C) {
        get_behavior_action(i_this) = 0x19;
        i_this->mBehaviorType = 0;
        get_behavior_mode(i_this) = 20;
    }

    if (i_this->mBehaviorType == 4) {
        get_behavior_action(i_this) = 1;
    } else if (i_this->mBehaviorType == 0x0F) {
        get_behavior_action(i_this) = 0x17;
        get_draw_disable_flag(i_this) = 0;
    }

    tn_field<s32>(i_this, 0x0288) = dComIfGp_evmng_getEventIdx("Tn", 0);

    if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x00029808)) {
        return cPhs_ERROR_e;
    }

    if (hio_set == 0) {
        l_tnHIO.mNo = mDoHIO_createChild("ダークナック", &l_tnHIO);
        get_hio_created_1433(i_this) = 1;
        hio_set = 1;
    }

    fopAcM_SetMin(i_this, -200.0f, -50.0f, -100.0f);
    fopAcM_SetMax(i_this, 125.0f, 250.0f, 250.0f);
    fopAcM_SetMtx(i_this, get_main_morf(i_this)->getModel()->getBaseTRMtx());

    tn_field<f32>(i_this, 0x0290) = 220.5f;
    tn_field<f32>(i_this, 0x0294) = 125.0f;
    tn_field<u8>(i_this, 0x0B80) = 1;
    get_ground_target_y(i_this) = i_this->current.pos.y;
    get_f32_b94(i_this) = 1000.0f;
    tn_field<s16>(i_this, 0x0942) = 5;
    tn_field<s32>(i_this, 0x0280) = 4;

    if (i_this->mPathIndex != 0xFF) {
        get_path_data(i_this) = dPath_GetRoomPath(i_this->mPathIndex, fopAcM_GetRoomNo(i_this));
        if (get_path_data(i_this) == NULL) {
            return cPhs_ERROR_e;
        }

        get_path_found_count(i_this) = i_this->mPathIndex + 1;
        get_path_point_step(i_this) = 1;
    }

    tn_field<dBgS_ObjAcch>(i_this, 0x0990).Set(
        fopAcM_GetPosition_p(i_this), fopAcM_GetOldPosition_p(i_this), i_this, 1,
        &tn_field<dBgS_AcchCir>(i_this, 0x0950), fopAcM_GetSpeed_p(i_this));

    tn_field<dBgS_AcchCir>(i_this, 0x0950).SetWall(50.0f, 50.0f);
    get_status_flags_9b8(i_this) &= ~0x00000008;
    tn_field<f32>(i_this, 0x0A50) = 50.0f;

    if (i_this->mEquipmentType & 1) {
        tn_field<u8>(i_this, 0x0285) = 0x1E;
        tn_field<u8>(i_this, 0x0284) = 0x1E;
    } else {
        tn_field<u8>(i_this, 0x0285) = 0x0F;
        tn_field<u8>(i_this, 0x0284) = 0x0F;
    }

    get_cc_stts_0b98(i_this).Init(0xF0, 0xFF, i_this);

    dCcD_Cyl& co_cyl = tn_field<dCcD_Cyl>(i_this, 0x0C74);
    dCcD_Cyl& tg_cyl = tn_field<dCcD_Cyl>(i_this, 0x0DA4);
    dCcD_Sph& head_sph = tn_field<dCcD_Sph>(i_this, 0x0ED4);
    dCcD_Sph& wepon_sph = tn_field<dCcD_Sph>(i_this, 0x112C);
    dCcD_Sph& wepon2_sph = tn_field<dCcD_Sph>(i_this, 0x1258);
    dCcD_Sph& defence_sph = tn_field<dCcD_Sph>(i_this, 0x1000);

    co_cyl.Set(co_cyl_src);
    co_cyl.SetStts(&get_cc_stts_0b98(i_this));

    tg_cyl.Set(tg_cyl_src);
    tg_cyl.SetStts(&get_cc_stts_0b98(i_this));

    head_sph.Set(head_sph_src);
    head_sph.SetStts(&get_cc_stts_0b98(i_this));

    wepon_sph.Set(wepon_sph_src);
    wepon_sph.SetStts(&get_cc_stts_0b98(i_this));

    wepon2_sph.Set(wepon2_sph_src);
    wepon2_sph.SetStts(&get_cc_stts_0b98(i_this));

    defence_sph.Set(defence_sph_src);
    defence_sph.SetStts(&get_cc_stts_0b98(i_this));

    i_this->stealItemLeft = 3;

    cXyz yariPos(i_this->current.pos.x,
                 i_this->current.pos.y + (70.0f + reg_hio_field<f32>(0x3C)),
                 i_this->current.pos.z);
    get_yari_actor_id(i_this) =
        fopAcM_create(PROC_BOKO, 3, &yariPos, fopAcM_GetRoomNo(i_this));
    tn_field<u8>(i_this, 0x140C) = 1;
    get_yari_actor_flag(i_this) = 1;

    if (i_this->mEquipmentType < 4) {
        get_support_actor_id(i_this) = fpcM_ERROR_PROCESS_ID_e;
    } else {
        get_support_actor_id(i_this) =
            fopAcM_create(PROC_MANT, 0, &i_this->current.pos, fopAcM_GetRoomNo(i_this));
    }

    enemyice& enemyIce = tn_field<enemyice>(i_this, 0x1524);
    enemyIce.mpActor = i_this;
    enemyIce.mCylHeight = 70.0f + reg_hio_field<f32>(0x24);
    enemyIce.mWallRadius = 200.0f + reg_hio_field<f32>(0x28);
    enemyIce.mParticleScale = 1.5f;
    enemyIce.mDeathSwitch = i_this->mDisableSpawnOnDeathSwitch;

    enemyfire& enemyFire = get_enemy_fire_18dc(i_this);
    enemyFire.mpMcaMorf = get_main_morf(i_this);
    enemyFire.mpActor = i_this;

    for (int i = 0; i < ARRAY_SIZE(enemyFire.mFlameJntIdxs); i++) {
        enemyFire.mFlameJntIdxs[i] = fire_j[i];
        enemyFire.mParticleScale[i] = fire_sc[i];
    }

    tn_field<f32>(i_this, 0x151C) = 1.0f;
    tn_field<u8>(i_this, 0x028D) = 5;

    for (int i = 0; i < 3; i++) {
        daTn_Execute(i_this);
    }

    tn_field<f32>(i_this, 0x151C) = 10.0f;

    if (get_behavior_action(i_this) == 0x17) {
        if (dComIfGs_isEventBit(0x3802)) {
            tn_field<u32>(i_this, 0x01C4) &= ~0x4000;
        } else {
            tn_field<u32>(i_this, 0x01C4) |= 0x4000;
        }
    }

    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daTn_Method = {
    (process_method_func)daTn_Create,
    (process_method_func)daTn_Delete,
    (process_method_func)daTn_Execute,
    (process_method_func)daTn_IsDelete,
    (process_method_func)daTn_Draw,
};

actor_process_profile_definition g_profile_TN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(tn_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_TN,
    /* Actor SubMtd */ &l_daTn_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
