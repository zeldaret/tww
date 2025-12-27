/**
 * d_a_gm.cpp
 * Mini-Boss - Mothula / Enemy - Mothula Larva
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_gm.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-0000032C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000368-0000048C       .text draw_SUB__FP8gm_class */
void draw_SUB(gm_class*) {
    /* Nonmatching */
}

/* 0000048C-00000908       .text daGM_Draw__FP8gm_class */
static BOOL daGM_Draw(gm_class*) {
    /* Nonmatching */
}

/* 00000908-00000A34       .text anm_init__FP8gm_classifUcfi */
void anm_init(gm_class*, int, float, unsigned char, float, int) {
    /* Nonmatching */
}

/* 00000A34-00000D00       .text wing_cut_stat__FP8gm_class */
void wing_cut_stat(gm_class*) {
    /* Nonmatching */
}

/* 00000D3C-0000170C       .text body_atari_check__FP8gm_class */
void body_atari_check(gm_class*) {
    /* Nonmatching */
}

/* 0000170C-000017D8       .text BG_check__FP8gm_class */
void BG_check(gm_class*) {
    /* Nonmatching */
}

/* 000017D8-00001B84       .text Line_check__FP8gm_class4cXyz */
void Line_check(gm_class*, cXyz) {
    /* Nonmatching */
}

/* 00001FBC-0000212C       .text ks_set_rtn__FP8gm_class */
void ks_set_rtn(gm_class*) {
    /* Nonmatching */
}

/* 0000212C-00002204       .text wing_ret_set__FP8gm_class */
void wing_ret_set(gm_class*) {
    /* Nonmatching */
}

/* 00002204-000022C4       .text fuwafuwa_set__FP8gm_class */
void fuwafuwa_set(gm_class*) {
    /* Nonmatching */
}

/* 000022C4-00002474       .text fly_move__FP8gm_class */
void fly_move(gm_class*) {
    /* Nonmatching */
}

/* 00002474-00002AB8       .text action_dousa__FP8gm_class */
void action_dousa(gm_class*) {
    /* Nonmatching */
}

/* 00002AB8-00002C9C       .text action_hane_rakka__FP8gm_class */
void action_hane_rakka(gm_class*) {
    /* Nonmatching */
}

/* 00002C9C-000030FC       .text action_uchiwa_dousa__FP8gm_class */
void action_uchiwa_dousa(gm_class*) {
    /* Nonmatching */
}

/* 000030FC-00003E54       .text action_totugeki__FP8gm_class */
void action_totugeki(gm_class*) {
    /* Nonmatching */
}

/* 00003E54-00004204       .text action_kabehari__FP8gm_class */
void action_kabehari(gm_class*) {
    /* Nonmatching */
}

/* 00004204-000046F0       .text action_fly_damage__FP8gm_class */
void action_fly_damage(gm_class*) {
    /* Nonmatching */
}

/* 000046F0-00005C78       .text action_ground_attack__FP8gm_class */
void action_ground_attack(gm_class*) {
    /* Nonmatching */
}

/* 00005C78-00006A98       .text action_demo__FP8gm_class */
void action_demo(gm_class*) {
    /* Nonmatching */
}

/* 00006A98-00007770       .text daGM_Execute__FP8gm_class */
static BOOL daGM_Execute(gm_class*) {
    /* Nonmatching */
}

/* 00007770-00007778       .text daGM_IsDelete__FP8gm_class */
static BOOL daGM_IsDelete(gm_class*) {
    return TRUE;
}

/* 00007778-000078C4       .text daGM_Delete__FP8gm_class */
static BOOL daGM_Delete(gm_class*) {
    /* Nonmatching */
}

/* 000078C4-00007E74       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00007EBC-0000842C       .text daGM_Create__FP10fopAc_ac_c */
static cPhs_State daGM_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph weapon_co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_UNK2,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
        }},
    };
    static dCcD_SrcCyl body_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK5,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
    static dCcD_SrcCyl wing_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ dCcG_SE_UNK5,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK6,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
    static dCcD_SrcCyl wind_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_WIND,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e | cCcD_AtSPrm_NoTgHitInfSet_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_VsOther_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };
}

static actor_method_class l_daGM_Method = {
    (process_method_func)daGM_Create,
    (process_method_func)daGM_Delete,
    (process_method_func)daGM_Execute,
    (process_method_func)daGM_IsDelete,
    (process_method_func)daGM_Draw,
};

actor_process_profile_definition g_profile_GM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_GM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(gm_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_GM,
    /* Actor SubMtd */ &l_daGM_Method,
    /* Status       */ fopAcStts_SHOWMAP_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
