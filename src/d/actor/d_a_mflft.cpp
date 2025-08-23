/**
 * d_a_mflft.cpp
 * Object - Dragon Roost Cavern - Flame lift (platform lifted up by lava plume)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mflft.h"
#include "d/d_bg_w.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 00000078-00000170       .text setLiftUp__11mflft_classF4cXyz */
void mflft_class::setLiftUp(cXyz) {
    /* Nonmatching */
}

/* 000001AC-00000408       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000408-00000488       .text himo_Draw__FP11mflft_class */
void himo_Draw(mflft_class*) {
    /* Nonmatching */
}

/* 00000488-00000530       .text daMflft_Draw__FP11mflft_class */
static BOOL daMflft_Draw(mflft_class*) {
    /* Nonmatching */
}

/* 00000530-00000614       .text kikuzu_set__FP11mflft_classP4cXyz */
void kikuzu_set(mflft_class*, cXyz*) {
    /* Nonmatching */
}

/* 00000614-00000AB8       .text himo_cut_control__FP11mflft_classP4cXyzPUcUc */
void himo_cut_control(mflft_class*, cXyz*, unsigned char*, unsigned char) {
    /* Nonmatching */
}

/* 00000E38-00001718       .text mflft_move__FP11mflft_class */
void mflft_move(mflft_class*) {
    /* Nonmatching */
}

/* 000019C0-00001E5C       .text himo_move__FP11mflft_class */
void himo_move(mflft_class*) {
    /* Nonmatching */
}

/* 00001E5C-00002008       .text eff_cont__FP11mflft_class */
void eff_cont(mflft_class*) {
    /* Nonmatching */
}

/* 00002008-00002284       .text daMflft_Execute__FP11mflft_class */
static BOOL daMflft_Execute(mflft_class*) {
    /* Nonmatching */
}

/* 00002284-0000228C       .text daMflft_IsDelete__FP11mflft_class */
static BOOL daMflft_IsDelete(mflft_class*) {
    return TRUE;
}

/* 0000228C-00002310       .text daMflft_Delete__FP11mflft_class */
static BOOL daMflft_Delete(mflft_class*) {
    /* Nonmatching */
}

/* 00002310-000024C8       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000024C8-00002A34       .text daMflft_Create__FP10fopAc_ac_c */
static cPhs_State daMflft_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcCyl himo_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 10.0f,
            /* Height */ 1000.0f,
        }},
    };
}

static actor_method_class l_daMflft_Method = {
    (process_method_func)daMflft_Create,
    (process_method_func)daMflft_Delete,
    (process_method_func)daMflft_Execute,
    (process_method_func)daMflft_IsDelete,
    (process_method_func)daMflft_Draw,
};

actor_process_profile_definition g_profile_MFLFT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MFLFT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(mflft_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MFLFT,
    /* Actor SubMtd */ &l_daMflft_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
