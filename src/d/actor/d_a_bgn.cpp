/**
 * d_a_bgn.cpp
 * Boss - Puppet Ganon (Phase 1)
 */

#include "d/actor/d_a_bgn.h"
#include "d/actor/d_a_bgn2.h"
#include "d/actor/d_a_bgn3.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_cc_d.h"

/* 000000EC-000003F0       .text __ct__11daBgn_HIO_cFv */
daBgn_HIO_c::daBgn_HIO_c() {
    /* Nonmatching */
}

/* 000005BC-000008BC       .text part_draw__FP9bgn_classP6part_s */
void part_draw(bgn_class*, part_s*) {
    /* Nonmatching */
}

/* 000008F8-00000B70       .text water0_disp__FP9bgn_class */
void water0_disp(bgn_class*) {
    /* Nonmatching */
}

/* 00000B70-00000CAC       .text water1_disp__FP9bgn_class */
void water1_disp(bgn_class*) {
    /* Nonmatching */
}

/* 00000CAC-00000FCC       .text daBgn_DrawS__FP9bgn_class */
void daBgn_DrawS(bgn_class*) {
    /* Nonmatching */
}

/* 00000FCC-000012D0       .text daBgn2_Draw__FP10bgn2_class */
static BOOL daBgn2_Draw(bgn2_class*) {
    /* Nonmatching */
}

/* 000012D0-00001754       .text daBgn3_Draw__FP10bgn3_class */
static BOOL daBgn3_Draw(bgn3_class*) {
    /* Nonmatching */
}

/* 00001754-00001898       .text room_disp__FP9bgn_class */
void room_disp(bgn_class*) {
    /* Nonmatching */
}

/* 00001898-0000192C       .text ten_a_d_sub__FPvPv */
void ten_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 0000192C-00001998       .text ki_a_d_sub__FPvPv */
void ki_a_d_sub(void*, void*) {
    /* Nonmatching */
}

/* 00001998-000019F4       .text obj_disp__FP9bgn_class */
void obj_disp(bgn_class*) {
    /* Nonmatching */
}

/* 000019F4-00001A40       .text bgn2_s_sub__FPvPv */
void bgn2_s_sub(void*, void*) {
    /* Nonmatching */
}

/* 00001A40-00001A8C       .text bgn3_s_sub__FPvPv */
void bgn3_s_sub(void*, void*) {
    /* Nonmatching */
}

/* 00001A8C-00001C40       .text daBgn_Draw__FP9bgn_class */
static BOOL daBgn_Draw(bgn_class*) {
    /* Nonmatching */
}

/* 00001C40-00001C8C       .text ki_del_sub__FPvPv */
void ki_del_sub(void*, void*) {
    /* Nonmatching */
}

/* 00001C8C-00001CD8       .text ks_del_sub__FPvPv */
void ks_del_sub(void*, void*) {
    /* Nonmatching */
}

/* 00001CD8-00001D30       .text ki_c_sub__FPvPv */
void ki_c_sub(void*, void*) {
    /* Nonmatching */
}

/* 00001D30-00001D74       .text ki_check__FP9bgn_class */
void ki_check(bgn_class*) {
    /* Nonmatching */
}

/* 00001D74-00001FA0       .text move_se_set__FP9bgn_class */
void move_se_set(bgn_class*) {
    /* Nonmatching */
}

/* 00001FA0-00002330       .text gr_check__FP9bgn_classP4cXyz */
void gr_check(bgn_class*, cXyz*) {
    /* Nonmatching */
}

/* 00002768-0000290C       .text s_b_sub__FPvPv */
void s_b_sub(void*, void*) {
    /* Nonmatching */
}

/* 0000290C-00002938       .text bomb_splash_check__FP9bgn_class */
void bomb_splash_check(bgn_class*) {
    /* Nonmatching */
}

/* 00002938-00002CD4       .text attack_eff_set__FP9bgn_class4cXyzi */
void attack_eff_set(bgn_class*, cXyz, int) {
    /* Nonmatching */
}

/* 00002CD4-00003144       .text part_control_0__FP9bgn_classiP6part_sP6move_sf */
void part_control_0(bgn_class*, int, part_s*, move_s*, float) {
    /* Nonmatching */
}

/* 00003144-00003624       .text part_control_0Z__FP9bgn_classiP6part_sP6move_sf */
void part_control_0Z(bgn_class*, int, part_s*, move_s*, float) {
    /* Nonmatching */
}

/* 00003624-0000385C       .text part_control_2__FP9bgn_classiP6part_sf */
void part_control_2(bgn_class*, int, part_s*, float) {
    /* Nonmatching */
}

/* 0000385C-00003FD0       .text part_mtx_set__FP9bgn_classiP6part_sii */
void part_mtx_set(bgn_class*, int, part_s*, int, int) {
    /* Nonmatching */
}

/* 00003FD0-000044DC       .text damage_check__FP9bgn_class */
void damage_check(bgn_class*) {
    /* Nonmatching */
}

/* 00004518-000047D0       .text size_set__FP9bgn_class */
void size_set(bgn_class*) {
    /* Nonmatching */
}

/* 000047D0-000056DC       .text shape_calc__FP9bgn_class */
void shape_calc(bgn_class*) {
    /* Nonmatching */
}

/* 000056DC-000058F4       .text dance_A__FP9bgn_class */
void dance_A(bgn_class*) {
    /* Nonmatching */
}

/* 000058F4-00005ACC       .text dance_B__FP9bgn_class */
void dance_B(bgn_class*) {
    /* Nonmatching */
}

/* 00005ACC-00005B2C       .text ki_set__FP9bgn_class */
void ki_set(bgn_class*) {
    /* Nonmatching */
}

/* 00005B2C-0000616C       .text dance_0__FP9bgn_class */
void dance_0(bgn_class*) {
    /* Nonmatching */
}

/* 0000616C-00007108       .text punch_LR__FP9bgn_class */
void punch_LR(bgn_class*) {
    /* Nonmatching */
}

/* 00007108-000071C0       .text start__FP9bgn_class */
void start(bgn_class*) {
    /* Nonmatching */
}

/* 000071C0-000076F4       .text body_attack__FP9bgn_class */
void body_attack(bgn_class*) {
    /* Nonmatching */
}

/* 000076F4-000078D0       .text tail_attack__FP9bgn_class */
void tail_attack(bgn_class*) {
    /* Nonmatching */
}

/* 000078D0-00007B38       .text damage__FP9bgn_class */
void damage(bgn_class*) {
    /* Nonmatching */
}

/* 00007B38-00007CF0       .text head_recover__FP9bgn_class */
void head_recover(bgn_class*) {
    /* Nonmatching */
}

/* 00007CF0-000084B4       .text hensin__FP9bgn_class */
void hensin(bgn_class*) {
    /* Nonmatching */
}

/* 000084B4-00008888       .text himo_control__FP9bgn_classP6move_sP4cXyz */
void himo_control(bgn_class*, move_s*, cXyz*) {
    /* Nonmatching */
}

/* 00008888-00008C20       .text last_himo_control__FP9bgn_class */
void last_himo_control(bgn_class*) {
    /* Nonmatching */
}

/* 00008C20-000092B8       .text action_s__FP9bgn_classP6move_si */
void action_s(bgn_class*, move_s*, int) {
    /* Nonmatching */
}

/* 000092B8-0000960C       .text action_main__FP9bgn_class */
void action_main(bgn_class*) {
    /* Nonmatching */
}

/* 0000960C-00009F6C       .text move__FP9bgn_class */
void move(bgn_class*) {
    /* Nonmatching */
}

/* 0000A104-0000AE8C       .text demo_camera__FP9bgn_class */
void demo_camera(bgn_class*) {
    /* Nonmatching */
}

/* 0000AE8C-0000B134       .text daBgn_Execute__FP9bgn_class */
static BOOL daBgn_Execute(bgn_class*) {
    /* Nonmatching */
}

/* 0000B134-0000B13C       .text daBgn_IsDelete__FP9bgn_class */
static BOOL daBgn_IsDelete(bgn_class*) {
    /* Nonmatching */
}

/* 0000B13C-0000B238       .text daBgn_Delete__FP9bgn_class */
static BOOL daBgn_Delete(bgn_class*) {
    /* Nonmatching */
}

/* 0000B238-0000B284       .text part_init__FP6part_sP12J3DModelData */
void part_init(part_s*, J3DModelData*) {
    /* Nonmatching */
}

/* 0000B284-0000B994       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000B9DC-0000CA80       .text daBgn_Create__FP10fopAc_ac_c */
static cPhs_State daBgn_Create(fopAc_ac_c* i_this) {
    /* Nonmatching */
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8,
            /* SrcObjAt  Atp     */ 4,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK9,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 50.0f,
        },
    };
    static dCcD_SrcSph core_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_LIGHT_ARROW,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK9,
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
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 70.0f,
        },
    };
    fopAcM_SetupActor(i_this, bgn_class);
}

static actor_method_class l_daBgn_Method = {
    (process_method_func)daBgn_Create,
    (process_method_func)daBgn_Delete,
    (process_method_func)daBgn_Execute,
    (process_method_func)daBgn_IsDelete,
    (process_method_func)daBgn_Draw,
};

actor_process_profile_definition g_profile_BGN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BGN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bgn_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BGN,
    /* Actor SubMtd */ &l_daBgn_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
