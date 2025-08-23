/**
 * d_a_obj_balancelift.cpp
 * Object - Tower of the Gods - Pair of scales
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_balancelift.h"
#include "d/d_bg_w.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 200.0f,
    }},
};


/* 000000EC-00000160       .text __ct__19daBalancelift_HIO_cFv */
daBalancelift_HIO_c::daBalancelift_HIO_c() {
    /* Nonmatching */
}

/* 0000019C-00000264       .text daObjBlift_ride_actor_check__FP10fopAc_ac_c */
void daObjBlift_ride_actor_check(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000264-0000033C       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000033C-00000510       .text calc_quat__15daBalancelift_cFv */
void daBalancelift_c::calc_quat() {
    /* Nonmatching */
}

/* 00000510-00000670       .text set_mtx__15daBalancelift_cFv */
void daBalancelift_c::set_mtx() {
    /* Nonmatching */
}

/* 00000670-00000984       .text calc_weight__15daBalancelift_cFv */
void daBalancelift_c::calc_weight() {
    /* Nonmatching */
}

/* 00000984-000009A4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000009A4-00000BA0       .text CreateHeap__15daBalancelift_cFv */
void daBalancelift_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000BA0-00000F34       .text CreateInit__15daBalancelift_cFv */
void daBalancelift_c::CreateInit() {
    /* Nonmatching */
}

/* 00000F34-000010E0       .text daBalanceliftCreate__FPv */
static cPhs_State daBalanceliftCreate(void*) {
    /* Nonmatching */
}

/* 0000129C-00001318       .text daBalanceliftDelete__FPv */
static BOOL daBalanceliftDelete(void*) {
    /* Nonmatching */
}

/* 00001318-0000133C       .text daBalanceliftExecute__FPv */
static BOOL daBalanceliftExecute(void* i_this) {
    return ((daBalancelift_c*)i_this)->_execute();
}

/* 0000133C-000016F0       .text _execute__15daBalancelift_cFv */
bool daBalancelift_c::_execute() {
    /* Nonmatching */
}

/* 000016F0-00001774       .text daBalanceliftDraw__FPv */
static BOOL daBalanceliftDraw(void*) {
    /* Nonmatching */
}

/* 00001774-0000177C       .text daBalanceliftIsDelete__FPv */
static BOOL daBalanceliftIsDelete(void*) {
    return TRUE;
}

static actor_method_class daBalanceliftMethodTable = {
    (process_method_func)daBalanceliftCreate,
    (process_method_func)daBalanceliftDelete,
    (process_method_func)daBalanceliftExecute,
    (process_method_func)daBalanceliftIsDelete,
    (process_method_func)daBalanceliftDraw,
};

actor_process_profile_definition g_profile_Balancelift = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Balancelift,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBalancelift_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Balancelift,
    /* Actor SubMtd */ &daBalanceliftMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
