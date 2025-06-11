/**
 * d_a_himo3.cpp
 * Object - Rope (Pirate Ship rope minigame, Forsaken Fortress)
 */

#include "d/actor/d_a_himo3.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-00000C58       .text himo3_control__FP11himo3_classP7himo3_s */
void himo3_control(himo3_class*, himo3_s*) {
    /* Nonmatching */
}

/* 00000C58-00000D1C       .text ga_draw__FP11himo3_class */
void ga_draw(himo3_class*) {
    /* Nonmatching */
}

/* 00000D1C-00000EF8       .text daHimo3_Draw__FP11himo3_class */
static BOOL daHimo3_Draw(himo3_class*) {
    /* Nonmatching */
}

/* 00000EF8-00001108       .text ga_move__FP11himo3_class */
void ga_move(himo3_class*) {
    /* Nonmatching */
}

/* 00001108-00001128       .text setActorHang__11himo3_classF4cXyzs */
void himo3_class::setActorHang(cXyz, short) {
    /* Nonmatching */
}

/* 00001128-000014F8       .text path_move__FP11himo3_class */
void path_move(himo3_class*) {
    /* Nonmatching */
}

/* 000014F8-00001A3C       .text daHimo3_Execute__FP11himo3_class */
static BOOL daHimo3_Execute(himo3_class*) {
    /* Nonmatching */
}

/* 00001A3C-00001A44       .text daHimo3_IsDelete__FP11himo3_class */
static BOOL daHimo3_IsDelete(himo3_class*) {
    return TRUE;
}

/* 00001A44-00001AE0       .text daHimo3_Delete__FP11himo3_class */
static BOOL daHimo3_Delete(himo3_class*) {
    /* Nonmatching */
}

/* 00001AE0-00001DD4       .text useHeapInit__FP11himo3_class */
void useHeapInit(himo3_class*) {
    /* Nonmatching */
}

/* 00001DD4-00002128       .text daHimo3_Create__FP10fopAc_ac_c */
static cPhs_State daHimo3_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcCyl cc_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 50.0f,
            /* Height */ 4000.0f,
        },
    };
    static dCcD_SrcSph sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
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
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 50.0f,
        },
    };
    static dCcD_SrcSph sph2_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 80.0f,
        },
    };
}

static actor_method_class l_daHimo3_Method = {
    (process_method_func)daHimo3_Create,
    (process_method_func)daHimo3_Delete,
    (process_method_func)daHimo3_Execute,
    (process_method_func)daHimo3_IsDelete,
    (process_method_func)daHimo3_Draw,
};

actor_process_profile_definition g_profile_HIMO3 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_HIMO3,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(himo3_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_HIMO3,
    /* Actor SubMtd */ &l_daHimo3_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
