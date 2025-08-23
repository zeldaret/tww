/**
 * d_a_klft.cpp
 * Object - Forbidden Woods - Lift (moving wooden platform)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_klft.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 00000078-00000374       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000003B0-0000046C       .text nodeCallBack_main__FP7J3DNodei */
static BOOL nodeCallBack_main(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000046C-00000520       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000520-000005A0       .text himo_Draw__FP10klft_class */
void himo_Draw(klft_class*) {
    /* Nonmatching */
}

/* 000005A0-00000688       .text daKlft_Draw__FP10klft_class */
static BOOL daKlft_Draw(klft_class*) {
    /* Nonmatching */
}

/* 00000688-00000F24       .text klft_move__FP10klft_class */
void klft_move(klft_class*) {
    /* Nonmatching */
}

/* 00000F24-00001140       .text himo_move__FP10klft_class */
void himo_move(klft_class*) {
    /* Nonmatching */
}

/* 00001140-00001444       .text daKlft_Execute__FP10klft_class */
static BOOL daKlft_Execute(klft_class*) {
    /* Nonmatching */
}

/* 00001444-0000144C       .text daKlft_IsDelete__FP10klft_class */
static BOOL daKlft_IsDelete(klft_class*) {
    return TRUE;
}

/* 0000144C-00001520       .text daKlft_Delete__FP10klft_class */
static BOOL daKlft_Delete(klft_class*) {
    /* Nonmatching */
}

/* 00001520-000017C4       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000017C4-00001C78       .text daKlft_Create__FP10fopAc_ac_c */
static cPhs_State daKlft_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcSph utiwa_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_WIND,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
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
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 250.0f,
        }},
    };
    static dCcD_SrcCyl p_co_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK6,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 40.0f,
            /* Height */ 60.0f,
        }},
    };
}

static actor_method_class l_daKlft_Method = {
    (process_method_func)daKlft_Create,
    (process_method_func)daKlft_Delete,
    (process_method_func)daKlft_Execute,
    (process_method_func)daKlft_IsDelete,
    (process_method_func)daKlft_Draw,
};

actor_process_profile_definition g_profile_KLFT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KLFT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(klft_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KLFT,
    /* Actor SubMtd */ &l_daKlft_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
