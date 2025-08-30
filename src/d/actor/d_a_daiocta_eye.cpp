/**
 * d_a_daiocta_eye.cpp
 * Mini-Boss - Big Octo (eye)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_daiocta_eye.h"
#include "d/d_cc_d.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

static dCcD_SrcSph l_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 180.0f,
    }},
};


/* 000000EC-000001B0       .text __ct__19daDaiocta_Eye_HIO_cFv */
daDaiocta_Eye_HIO_c::daDaiocta_Eye_HIO_c() {
    /* Nonmatching */
}

/* 000001B0-000001FC       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode*, int) {
    /* Nonmatching */
}

/* 000001FC-000002B8       .text _nodeControl__15daDaiocta_Eye_cFP7J3DNodeP8J3DModel */
void daDaiocta_Eye_c::_nodeControl(J3DNode*, J3DModel*) {
    /* Nonmatching */
}

/* 000002B8-000002D8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000002D8-000004E4       .text _createHeap__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::_createHeap() {
    /* Nonmatching */
}

/* 000004E4-00000510       .text coHit_CB__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void coHit_CB(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 00000510-000005D0       .text _coHit__15daDaiocta_Eye_cFP10fopAc_ac_c */
void daDaiocta_Eye_c::_coHit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000005D0-000006C0       .text setMtx__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::setMtx() {
    /* Nonmatching */
}

/* 000006C0-00000A6C       .text checkTgHit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::checkTgHit() {
    /* Nonmatching */
}

/* 00000A6C-00000A78       .text modeWaitInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeWaitInit() {
    /* Nonmatching */
}

/* 00000A78-00000A98       .text modeWait__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeWait() {
    /* Nonmatching */
}

/* 00000A98-00000BD8       .text modeDamageInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDamageInit() {
    /* Nonmatching */
}

/* 00000BD8-00000CD0       .text modeDamage__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDamage() {
    /* Nonmatching */
}

/* 00000CD0-00000E20       .text modeDeathInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDeathInit() {
    /* Nonmatching */
}

/* 00000E20-00000E2C       .text modeDeath__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeDeath() {
    /* Nonmatching */
}

/* 00000E2C-00000ED0       .text modeProcCall__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::modeProcCall() {
    /* Nonmatching */
}

/* 00000ED0-00001120       .text _execute__15daDaiocta_Eye_cFv */
bool daDaiocta_Eye_c::_execute() {
    /* Nonmatching */
}

/* 00001120-000011EC       .text _draw__15daDaiocta_Eye_cFv */
bool daDaiocta_Eye_c::_draw() {
    /* Nonmatching */
}

/* 000011EC-000012D4       .text createInit__15daDaiocta_Eye_cFv */
void daDaiocta_Eye_c::createInit() {
    /* Nonmatching */
}

/* 000012D4-00001450       .text _create__15daDaiocta_Eye_cFv */
cPhs_State daDaiocta_Eye_c::_create() {
    /* Nonmatching */
}

/* 00001764-000017B4       .text _delete__15daDaiocta_Eye_cFv */
bool daDaiocta_Eye_c::_delete() {
    /* Nonmatching */
}

/* 000017B4-000017D4       .text daDaiocta_EyeCreate__FPv */
static cPhs_State daDaiocta_EyeCreate(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_create();
}

/* 000017D4-000017F8       .text daDaiocta_EyeDelete__FPv */
static BOOL daDaiocta_EyeDelete(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_delete();
}

/* 000017F8-0000181C       .text daDaiocta_EyeExecute__FPv */
static BOOL daDaiocta_EyeExecute(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_execute();
}

/* 0000181C-00001840       .text daDaiocta_EyeDraw__FPv */
static BOOL daDaiocta_EyeDraw(void* i_this) {
    return ((daDaiocta_Eye_c*)i_this)->_draw();
}

/* 00001840-00001848       .text daDaiocta_EyeIsDelete__FPv */
static BOOL daDaiocta_EyeIsDelete(void*) {
    return TRUE;
}

static actor_method_class daDaiocta_EyeMethodTable = {
    (process_method_func)daDaiocta_EyeCreate,
    (process_method_func)daDaiocta_EyeDelete,
    (process_method_func)daDaiocta_EyeExecute,
    (process_method_func)daDaiocta_EyeIsDelete,
    (process_method_func)daDaiocta_EyeDraw,
};

actor_process_profile_definition g_profile_DAIOCTA_EYE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DAIOCTA_EYE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daDaiocta_Eye_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_DAIOCTA_EYE,
    /* Actor SubMtd */ &daDaiocta_EyeMethodTable,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
