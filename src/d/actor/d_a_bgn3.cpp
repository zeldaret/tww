/**
 * d_a_bgn3.cpp
 * Boss - Puppet Ganon (Phase 3)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bgn3.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-000001F4       .text __ct__12daBgn3_HIO_cFv */
daBgn3_HIO_c::daBgn3_HIO_c() {
    /* Nonmatching */
}

/* 000001F4-00000240       .text bgn_s_sub__FPvPv */
void bgn_s_sub(void*, void*) {
    /* Nonmatching */
}

/* 00000240-00000368       .text daBgn3_Draw__FP10bgn3_class */
static BOOL daBgn3_Draw(bgn3_class*) {
    /* Nonmatching */
}

/* 00000368-000006F8       .text gr_check__FP10bgn3_classP4cXyz */
void gr_check(bgn3_class*, cXyz*) {
    /* Nonmatching */
}

/* 00000B6C-00000D90       .text tail_eff_set__FP10bgn3_class */
void tail_eff_set(bgn3_class*) {
    /* Nonmatching */
}

/* 00000D90-00000EB8       .text move_splash_set__FP10bgn3_class */
void move_splash_set(bgn3_class*) {
    /* Nonmatching */
}

/* 00000EB8-0000101C       .text drop_eff_set__FP10bgn3_class */
void drop_eff_set(bgn3_class*) {
    /* Nonmatching */
}

/* 0000101C-00001068       .text esa_s_sub__FPvPv */
void esa_s_sub(void*, void*) {
    /* Nonmatching */
}

/* 00001068-000013D0       .text part_control__FP10bgn3_class */
void part_control(bgn3_class*) {
    /* Nonmatching */
}

/* 000013D0-00001800       .text checkWall__FP10bgn3_class */
void checkWall(bgn3_class*) {
    /* Nonmatching */
}

/* 00001800-00001848       .text checkGround__FP10bgn3_class */
void checkGround(bgn3_class*) {
    /* Nonmatching */
}

/* 00001848-000018EC       .text pos_move__FP10bgn3_class */
void pos_move(bgn3_class*) {
    /* Nonmatching */
}

/* 000018EC-00001D64       .text move0__FP10bgn3_class */
void move0(bgn3_class*) {
    /* Nonmatching */
}

/* 00001D64-00001E6C       .text mahi__FP10bgn3_class */
void mahi(bgn3_class*) {
    /* Nonmatching */
}

/* 00001E6C-00002100       .text damage__FP10bgn3_class */
void damage(bgn3_class*) {
    /* Nonmatching */
}

/* 00002100-00002524       .text end__FP10bgn3_class */
void end(bgn3_class*) {
    /* Nonmatching */
}

/* 00002524-00002C18       .text damage_check__FP10bgn3_class */
void damage_check(bgn3_class*) {
    /* Nonmatching */
}

/* 00002C18-00002E4C       .text ke_control__FP9bgn3_ke_sif */
void ke_control(bgn3_ke_s*, int, float) {
    /* Nonmatching */
}

/* 00002E4C-00002EE4       .text ke_move__FP19mDoExt_3DlineMat0_cP9bgn3_ke_sif */
void ke_move(mDoExt_3DlineMat0_c*, bgn3_ke_s*, int, float) {
    /* Nonmatching */
}

/* 00002EE4-00003110       .text move_se_set__FP10bgn3_class */
void move_se_set(bgn3_class*) {
    /* Nonmatching */
}

/* 00003110-00004058       .text move__FP10bgn3_class */
void move(bgn3_class*) {
    /* Nonmatching */
}

/* 00004058-000040B0       .text ki_c_sub__FPvPv */
void ki_c_sub(void*, void*) {
    /* Nonmatching */
}

/* 000040B0-000040F4       .text ki_check__FP10bgn3_class */
void ki_check(bgn3_class*) {
    /* Nonmatching */
}

/* 000040F4-00004358       .text daBgn3_Execute__FP10bgn3_class */
static BOOL daBgn3_Execute(bgn3_class*) {
    /* Nonmatching */
}

/* 00004358-00004360       .text daBgn3_IsDelete__FP10bgn3_class */
static BOOL daBgn3_IsDelete(bgn3_class*) {
    return TRUE;
}

/* 00004360-000043EC       .text daBgn3_Delete__FP10bgn3_class */
static BOOL daBgn3_Delete(bgn3_class*) {
    /* Nonmatching */
}

/* 000043EC-00004848       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00004890-00004BC0       .text daBgn3_Create__FP10fopAc_ac_c */
static cPhs_State daBgn3_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
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
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 50.0f,
        }},
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
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
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
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 70.0f,
        }},
    };
}

static actor_method_class l_daBgn3_Method = {
    (process_method_func)daBgn3_Create,
    (process_method_func)daBgn3_Delete,
    (process_method_func)daBgn3_Execute,
    (process_method_func)daBgn3_IsDelete,
    (process_method_func)daBgn3_Draw,
};

actor_process_profile_definition g_profile_BGN3 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BGN3,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bgn3_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BGN3,
    /* Actor SubMtd */ &l_daBgn3_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
