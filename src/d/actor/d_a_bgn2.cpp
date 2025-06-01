/**
 * d_a_bgn2.cpp
 * Boss - Puppet Ganon (Phase 2)
 */

#include "d/actor/d_a_bgn2.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-00000194       .text __ct__12daBgn2_HIO_cFv */
daBgn2_HIO_c::daBgn2_HIO_c() {
    /* Nonmatching */
}

/* 00000194-000002BC       .text anm_init__FP10bgn2_classifUcfi */
void anm_init(bgn2_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 000002BC-00000308       .text bgn_s_sub__FPvPv */
void bgn_s_sub(void*, void*) {
    /* Nonmatching */
}

/* 00000308-00000354       .text bgn3_s_sub__FPvPv */
void bgn3_s_sub(void*, void*) {
    /* Nonmatching */
}

/* 00000354-0000035C       .text daBgn2_Draw__FP10bgn2_class */
static BOOL daBgn2_Draw(bgn2_class*) {
    /* Nonmatching */
}

/* 0000035C-000006EC       .text gr_check__FP10bgn2_classP4cXyz */
void gr_check(bgn2_class*, cXyz*) {
    /* Nonmatching */
}

/* 00000B60-00000CA0       .text asi_eff_set__FP10bgn2_class */
void asi_eff_set(bgn2_class*) {
    /* Nonmatching */
}

/* 00000CA0-00000D88       .text asi_hamon_set__FP10bgn2_class */
void asi_hamon_set(bgn2_class*) {
    /* Nonmatching */
}

/* 00000D88-00000FA8       .text attack_eff_set__FP10bgn2_class4cXyz */
void attack_eff_set(bgn2_class*, cXyz) {
    /* Nonmatching */
}

/* 00000FA8-00000FE4       .text checkGround__FP10bgn2_class */
void checkGround(bgn2_class*) {
    /* Nonmatching */
}

/* 00000FE4-00001210       .text move_se_set__FP10bgn2_class */
void move_se_set(bgn2_class*) {
    /* Nonmatching */
}

/* 00001210-0000137C       .text pos_move__FP10bgn2_class */
void pos_move(bgn2_class*) {
    /* Nonmatching */
}

/* 0000137C-0000144C       .text start__FP10bgn2_class */
void start(bgn2_class*) {
    /* Nonmatching */
}

/* 0000144C-00001474       .text ki_set__FP10bgn2_class */
void ki_set(bgn2_class*) {
    /* Nonmatching */
}

/* 00001474-00001860       .text plesattack__FP10bgn2_class */
void plesattack(bgn2_class*) {
    /* Nonmatching */
}

/* 00001860-00001C5C       .text jumpattack__FP10bgn2_class */
void jumpattack(bgn2_class*) {
    /* Nonmatching */
}

/* 00001C5C-00001D4C       .text mahi__FP10bgn2_class */
void mahi(bgn2_class*) {
    /* Nonmatching */
}

/* 00001D4C-00001EB4       .text damage__FP10bgn2_class */
void damage(bgn2_class*) {
    /* Nonmatching */
}

/* 00001EB4-00002320       .text hensin__FP10bgn2_class */
void hensin(bgn2_class*) {
    /* Nonmatching */
}

/* 00002320-000026A4       .text move__FP10bgn2_class */
void move(bgn2_class*) {
    /* Nonmatching */
}

/* 000026A4-00002C88       .text damage_check__FP10bgn2_class */
void damage_check(bgn2_class*) {
    /* Nonmatching */
}

/* 00002C88-00002CE0       .text ki_c_sub__FPvPv */
void ki_c_sub(void*, void*) {
    /* Nonmatching */
}

/* 00002CE0-00002D24       .text ki_check__FP10bgn2_class */
void ki_check(bgn2_class*) {
    /* Nonmatching */
}

/* 00002D24-000037B0       .text daBgn2_Execute__FP10bgn2_class */
static BOOL daBgn2_Execute(bgn2_class*) {
    /* Nonmatching */
}

/* 000037B0-000037B8       .text daBgn2_IsDelete__FP10bgn2_class */
static BOOL daBgn2_IsDelete(bgn2_class*) {
    /* Nonmatching */
}

/* 000037B8-00003828       .text daBgn2_Delete__FP10bgn2_class */
static BOOL daBgn2_Delete(bgn2_class*) {
    /* Nonmatching */
}

/* 00003828-00003C60       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00003CA8-00003FF4       .text daBgn2_Create__FP10fopAc_ac_c */
static cPhs_State daBgn2_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8,
            /* SrcObjAt  Atp     */ 4,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNKA,
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
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNKA,
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
}

static actor_method_class l_daBgn2_Method = {
    (process_method_func)daBgn2_Create,
    (process_method_func)daBgn2_Delete,
    (process_method_func)daBgn2_Execute,
    (process_method_func)daBgn2_IsDelete,
    (process_method_func)daBgn2_Draw,
};

actor_process_profile_definition g_profile_BGN2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BGN2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bgn2_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BGN2,
    /* Actor SubMtd */ &l_daBgn2_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
