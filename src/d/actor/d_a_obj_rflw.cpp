//
// Generated by dtk
// Translation Unit: d_a_obj_rflw.cpp
//

#include "d/actor/d_a_obj_rflw.h"
#include "m_Do/m_Do_ext.h"
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
        /* SrcObjTg  Type    */ AT_TYPE_BOMB,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
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
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 30.0f,
        /* Height */ 200.0f,
    },
};


/* 00000078-00000098       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000098-000001E0       .text CreateHeap__11daObjRflw_cFv */
void daObjRflw_c::CreateHeap() {
    /* Nonmatching */
}

/* 000001E0-00000284       .text CreateInit__11daObjRflw_cFv */
void daObjRflw_c::CreateInit() {
    /* Nonmatching */
}

/* 00000284-00000368       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000368-000003E8       .text set_mtx__11daObjRflw_cFv */
void daObjRflw_c::set_mtx() {
    /* Nonmatching */
}

/* 000003E8-0000051C       .text daObjRflw_Create__FPv */
static cPhs_State daObjRflw_Create(void*) {
    /* Nonmatching */
}

/* 000006D4-00000704       .text daObjRflw_Delete__FPv */
static BOOL daObjRflw_Delete(void*) {
    /* Nonmatching */
}

/* 00000704-000007A8       .text daObjRflw_Draw__FPv */
static BOOL daObjRflw_Draw(void*) {
    /* Nonmatching */
}

/* 000007A8-000009EC       .text daObjRflw_Execute__FPv */
static BOOL daObjRflw_Execute(void*) {
    /* Nonmatching */
}

/* 000009EC-000009F4       .text daObjRflw_IsDelete__FPv */
static BOOL daObjRflw_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_RflwMethodTable = {
    (process_method_func)daObjRflw_Create,
    (process_method_func)daObjRflw_Delete,
    (process_method_func)daObjRflw_Execute,
    (process_method_func)daObjRflw_IsDelete,
    (process_method_func)daObjRflw_Draw,
};

actor_process_profile_definition g_profile_Obj_Rflw = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Rflw,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjRflw_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Rflw,
    /* Actor SubMtd */ &daObj_RflwMethodTable,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
