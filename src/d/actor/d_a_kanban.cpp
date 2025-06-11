/**
 * d_a_kanban.cpp
 * Object - Cuttable sign
 */

#include "d/actor/d_a_kanban.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

/* 000000EC-0000012C       .text __ct__14daKanban_HIO_cFv */
daKanban_HIO_c::daKanban_HIO_c() {
    /* Nonmatching */
}

/* 00000174-0000047C       .text daKanban_Draw__FP12kanban_class */
static BOOL daKanban_Draw(kanban_class*) {
    /* Nonmatching */
}

/* 0000047C-0000055C       .text shibuki_set__FP12kanban_class4cXyzf */
void shibuki_set(kanban_class*, cXyz, float) {
    /* Nonmatching */
}

/* 0000055C-00000884       .text sea_water_check__FP12kanban_class */
void sea_water_check(kanban_class*) {
    /* Nonmatching */
}

/* 00000884-00000940       .text bom_search_sub__FPvPv */
void bom_search_sub(void*, void*) {
    /* Nonmatching */
}

/* 00000940-00000B84       .text shock_damage_check__FP12kanban_class */
void shock_damage_check(kanban_class*) {
    /* Nonmatching */
}

/* 00000B84-00000E6C       .text cut_point_check__FP12kanban_class */
void cut_point_check(kanban_class*) {
    /* Nonmatching */
}

/* 00000E6C-000012B8       .text mother_move__FP12kanban_class */
void mother_move(kanban_class*) {
    /* Nonmatching */
}

/* 000012B8-0000134C       .text mother_water_swim__FP12kanban_class */
void mother_water_swim(kanban_class*) {
    /* Nonmatching */
}

/* 0000134C-00001580       .text ret_keisan_move__FP12kanban_class */
void ret_keisan_move(kanban_class*) {
    /* Nonmatching */
}

/* 00001580-00001770       .text mother_return_move__FP12kanban_class */
void mother_return_move(kanban_class*) {
    /* Nonmatching */
}

/* 00001770-00001B50       .text parts_move__FP12kanban_class */
void parts_move(kanban_class*) {
    /* Nonmatching */
}

/* 00001B50-00001D58       .text chield_parts_move__FP12kanban_class */
void chield_parts_move(kanban_class*) {
    /* Nonmatching */
}

/* 00001D58-00001DEC       .text chield_water_swim__FP12kanban_class */
void chield_water_swim(kanban_class*) {
    /* Nonmatching */
}

/* 00001DEC-000022A8       .text daKanban_Execute__FP12kanban_class */
static BOOL daKanban_Execute(kanban_class*) {
    /* Nonmatching */
}

/* 000022A8-000022B0       .text daKanban_IsDelete__FP12kanban_class */
static BOOL daKanban_IsDelete(kanban_class*) {
    return TRUE;
}

/* 000022B0-00002300       .text daKanban_Delete__FP12kanban_class */
static BOOL daKanban_Delete(kanban_class*) {
    /* Nonmatching */
}

/* 00002300-0000249C       .text setTex__FP12J3DModelData */
void setTex(J3DModelData*) {
    /* Nonmatching */
}

/* 0000249C-00002614       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00002614-00002A5C       .text daKanban_Create__FP10fopAc_ac_c */
static cPhs_State daKanban_Create(fopAc_ac_c*) {
    /* Nonmatching */
    static dCcD_SrcCyl cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcG_TgHitMark_Unk255_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {
            /* Center */ 0.0f, 0.0f, 0.0f,
            /* Radius */ 0.0f,
            /* Height */ 0.0f,
        },
    };
}

static actor_method_class l_daKanban_Method = {
    (process_method_func)daKanban_Create,
    (process_method_func)daKanban_Delete,
    (process_method_func)daKanban_Execute,
    (process_method_func)daKanban_IsDelete,
    (process_method_func)daKanban_Draw,
};

actor_process_profile_definition g_profile_KANBAN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KANBAN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kanban_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KANBAN,
    /* Actor SubMtd */ &l_daKanban_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
