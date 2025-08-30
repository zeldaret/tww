/**
 * d_a_obj_majyuu_door.cpp
 * Object - Forsaken Fortress - Large wooden barricade (blocks entrance, destroyed with Bombs)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_majyuu_door.h"
#include "d/d_cc_d.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
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
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 75.0f,
        /* Height */ 115.0f,
    }},
};


/* 000000EC-0000010C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000010C-00000130       .text TgHitCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void TgHitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 00000130-00000154       .text __ct__17daObj_MjDoorHIO_cFv */
daObj_MjDoorHIO_c::daObj_MjDoorHIO_c() {
    /* Nonmatching */
}

/* 0000019C-00000240       .text set_mtx__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::set_mtx() {
    /* Nonmatching */
}

/* 00000240-000003A0       .text _createHeap__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::_createHeap() {
    /* Nonmatching */
}

/* 000003A0-000003AC       .text getArg__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::getArg() {
    /* Nonmatching */
}

/* 000003AC-00000478       .text CreateInit__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::CreateInit() {
    /* Nonmatching */
}

/* 00000478-000005B4       .text _create__14daObj_MjDoor_cFv */
cPhs_State daObj_MjDoor_c::_create() {
    /* Nonmatching */
}

/* 000007F0-00000884       .text _delete__14daObj_MjDoor_cFv */
bool daObj_MjDoor_c::_delete() {
    /* Nonmatching */
}

/* 00000884-000009D4       .text setCollision__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::setCollision() {
    /* Nonmatching */
}

/* 000009D4-000009E0       .text modeWaitInit__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::modeWaitInit() {
    /* Nonmatching */
}

/* 000009E0-00000A34       .text modeWait__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::modeWait() {
    /* Nonmatching */
}

/* 00000A34-00000AEC       .text smoke_set__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::smoke_set() {
    /* Nonmatching */
}

/* 00000AEC-00000D64       .text modeDeleteInit__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::modeDeleteInit() {
    /* Nonmatching */
}

/* 00000D64-00000DF0       .text modeDelete__14daObj_MjDoor_cFv */
void daObj_MjDoor_c::modeDelete() {
    /* Nonmatching */
}

/* 00000DF0-00000EB4       .text _execute__14daObj_MjDoor_cFv */
bool daObj_MjDoor_c::_execute() {
    /* Nonmatching */
}

/* 00000EB4-00000F28       .text _draw__14daObj_MjDoor_cFv */
bool daObj_MjDoor_c::_draw() {
    /* Nonmatching */
}

/* 00000F28-00000F48       .text daObj_MjDoorCreate__FPv */
static cPhs_State daObj_MjDoorCreate(void* i_this) {
    return ((daObj_MjDoor_c*)i_this)->_create();
}

/* 00000F48-00000F6C       .text daObj_MjDoorDelete__FPv */
static BOOL daObj_MjDoorDelete(void* i_this) {
    return ((daObj_MjDoor_c*)i_this)->_delete();
}

/* 00000F6C-00000F90       .text daObj_MjDoorExecute__FPv */
static BOOL daObj_MjDoorExecute(void* i_this) {
    return ((daObj_MjDoor_c*)i_this)->_execute();
}

/* 00000F90-00000FB4       .text daObj_MjDoorDraw__FPv */
static BOOL daObj_MjDoorDraw(void* i_this) {
    return ((daObj_MjDoor_c*)i_this)->_draw();
}

/* 00000FB4-00000FBC       .text daObj_MjDoorIsDelete__FPv */
static BOOL daObj_MjDoorIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_MjDoorMethodTable = {
    (process_method_func)daObj_MjDoorCreate,
    (process_method_func)daObj_MjDoorDelete,
    (process_method_func)daObj_MjDoorExecute,
    (process_method_func)daObj_MjDoorIsDelete,
    (process_method_func)daObj_MjDoorDraw,
};

actor_process_profile_definition g_profile_OBJ_MJDOOR = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_MJDOOR,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_MjDoor_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_MJDOOR,
    /* Actor SubMtd */ &daObj_MjDoorMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
