//
// Generated by dtk
// Translation Unit: d_a_deku_item.cpp
//

#include "d/actor/d_a_deku_item.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

const char daDekuItem_c::m_arcname[] = "Deku";

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ TG_SPRM_SET | TG_SPRM_IS_OTHER,
        /* SrcObjCo  SPrm    */ CO_SPRM_SET | CO_SPRM_IS_UNK8 | CO_SPRM_VS_UNK2,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ G_TG_SPRM_NO_HIT_MARK,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cCcD_SrcCylAttr
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 50.0f,
        /* Height */ 100.0f,
    }};

/* 00000078-000000D0       .text _delete__12daDekuItem_cFv */
BOOL daDekuItem_c::_delete() {
    /* Nonmatching */
}

/* 000000D0-000000F0       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000000F0-000002C8       .text CreateHeap__12daDekuItem_cFv */
void daDekuItem_c::CreateHeap() {
    /* Nonmatching */
}

/* 000002C8-000003A8       .text CreateInit__12daDekuItem_cFv */
void daDekuItem_c::CreateInit() {
    /* Nonmatching */
}

/* 000003A8-00000598       .text _create__12daDekuItem_cFv */
s32 daDekuItem_c::_create() {
    /* Nonmatching */
}

/* 00000948-000009C8       .text set_mtx__12daDekuItem_cFv */
void daDekuItem_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);

    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000009C8-00000A74       .text _execute__12daDekuItem_cFv */
BOOL daDekuItem_c::_execute() {
    /* Nonmatching */
}

/* 00000A74-00000B30       .text mode_proc_call__12daDekuItem_cFv */
void daDekuItem_c::mode_proc_call() {
    /* Nonmatching */
}

/* 00000B30-00000C50       .text mode_wait__12daDekuItem_cFv */
void daDekuItem_c::mode_wait() {
    /* Nonmatching */
}

/* 00000C50-00000CB8       .text mode_getdemo_init__12daDekuItem_cFv */
void daDekuItem_c::mode_getdemo_init() {
    /* Nonmatching */
}

/* 00000CB8-00000D34       .text mode_getdemo_wait__12daDekuItem_cFv */
void daDekuItem_c::mode_getdemo_wait() {
    /* Nonmatching */
}

/* 00000D34-00000D38       .text mode_getdemo__12daDekuItem_cFv */
void daDekuItem_c::mode_getdemo() {
    /* Nonmatching */
}

/* 00000D38-00000D94       .text eventOrder__12daDekuItem_cFv */
void daDekuItem_c::eventOrder() {
    /* Nonmatching */
}

/* 00000D94-00000E54       .text checkOrder__12daDekuItem_cFv */
void daDekuItem_c::checkOrder() {
    /* Nonmatching */
}

/* 00000E54-00000ECC       .text _draw__12daDekuItem_cFv */
BOOL daDekuItem_c::_draw() {
    /* Nonmatching */
}

/* 00000ECC-00000EEC       .text daDekuItem_Create__FPv */
static s32 daDekuItem_Create(void* i_this) {
    return static_cast<daDekuItem_c*>(i_this)->_create();
}

/* 00000EEC-00000F10       .text daDekuItem_Delete__FPv */
static BOOL daDekuItem_Delete(void* i_this) {
    return static_cast<daDekuItem_c*>(i_this)->_delete();
}

/* 00000F10-00000F34       .text daDekuItem_Draw__FPv */
static BOOL daDekuItem_Draw(void* i_this) {
    return static_cast<daDekuItem_c*>(i_this)->_draw();
}

/* 00000F34-00000F58       .text daDekuItem_Execute__FPv */
static BOOL daDekuItem_Execute(void* i_this) {
    return static_cast<daDekuItem_c*>(i_this)->_execute();
}

/* 00000F58-00000F60       .text daDekuItem_IsDelete__FPv */
static BOOL daDekuItem_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daDekuItemMethodTable = {
    (process_method_func)daDekuItem_Create,
    (process_method_func)daDekuItem_Delete,
    (process_method_func)daDekuItem_Execute,
    (process_method_func)daDekuItem_IsDelete,
    (process_method_func)daDekuItem_Draw,
};

actor_process_profile_definition g_profile_DEKU_ITEM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_DEKU_ITEM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daDekuItem_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x00FF,
    /* Actor SubMtd */ &daDekuItemMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
