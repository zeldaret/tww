/**
 * d_a_bdkobj.cpp
 * Object - Helmaroc King fight objects (wooden bridges, wooden planks floating in water, etc.).
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bdkobj.h"
#include "d/d_bg_w.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-00000104       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000104-00000184       .text hahen_draw__FP12bdkobj_class */
void hahen_draw(bdkobj_class*) {
    /* Nonmatching */
}

/* 00000184-000002C4       .text daBdkobj_Draw__FP12bdkobj_class */
static BOOL daBdkobj_Draw(bdkobj_class*) {
    /* Nonmatching */
}

/* 00000300-00000C08       .text top_hahen_move__FP12bdkobj_classP9bdo_eff_s */
void top_hahen_move(bdkobj_class*, bdo_eff_s*) {
    /* Nonmatching */
}

/* 00001214-00001640       .text kaidan_hahen_move__FP12bdkobj_classP9bdo_eff_s */
void kaidan_hahen_move(bdkobj_class*, bdo_eff_s*) {
    /* Nonmatching */
}

/* 000018E8-00001970       .text hahen_move__FP12bdkobj_class */
void hahen_move(bdkobj_class*) {
    /* Nonmatching */
}

/* 00001970-00001CF0       .text tower_kaidan_move__FP12bdkobj_class */
void tower_kaidan_move(bdkobj_class*) {
    /* Nonmatching */
}

/* 00001CF0-00002274       .text daBdkobj_Execute__FP12bdkobj_class */
static BOOL daBdkobj_Execute(bdkobj_class*) {
    /* Nonmatching */
}

/* 00002274-0000227C       .text daBdkobj_IsDelete__FP12bdkobj_class */
static BOOL daBdkobj_IsDelete(bdkobj_class*) {
    return TRUE;
}

/* 0000227C-000022E8       .text daBdkobj_Delete__FP12bdkobj_class */
static BOOL daBdkobj_Delete(bdkobj_class*) {
    /* Nonmatching */
}

/* 000022E8-000024C8       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000024C8-000027B8       .text daBdkobj_Create__FP10fopAc_ac_c */
static cPhs_State daBdkobj_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcCyl cc_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* Radius */ 100.0f,
            /* Height */ 450.0f,
        }},
    };
    static dCcD_SrcSph hahen_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
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
            /* Radius */ 30.0f,
        }},
    };
}

static actor_method_class l_daBdkobj_Method = {
    (process_method_func)daBdkobj_Create,
    (process_method_func)daBdkobj_Delete,
    (process_method_func)daBdkobj_Execute,
    (process_method_func)daBdkobj_IsDelete,
    (process_method_func)daBdkobj_Draw,
};

actor_process_profile_definition g_profile_BDKOBJ = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BDKOBJ,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bdkobj_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BDKOBJ,
    /* Actor SubMtd */ &l_daBdkobj_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
