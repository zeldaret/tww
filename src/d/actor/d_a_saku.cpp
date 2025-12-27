/**
 * d_a_saku.cpp
 * Object - Brown wooden barricade
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_saku.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

const dCcD_SrcCyl daSaku_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_SWORD | AT_TYPE_UNK8 | AT_TYPE_BOMB | AT_TYPE_FIRE | AT_TYPE_MACHETE | AT_TYPE_UNK800 | AT_TYPE_SKULL_HAMMER | AT_TYPE_UNK20000 | AT_TYPE_FIRE_ARROW,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 50.0f,
        /* Height */ 200.0f,
    }},
};


class J3DModelData;
class J3DMaterial;

/* 000000EC-00000200       .text CreateInit__8daSaku_cFv */
void daSaku_c::CreateInit() {
    /* Nonmatching */
}

/* 00000200-000003A8       .text saku_draw_sub__8daSaku_cFi */
void daSaku_c::saku_draw_sub(int) {
    /* Nonmatching */
}

/* 000003A8-00000590       .text mode_break_none__8daSaku_cFi */
void daSaku_c::mode_break_none(int) {
    /* Nonmatching */
}

/* 000005CC-000006A8       .text mode_break_fire__8daSaku_cFi */
void daSaku_c::mode_break_fire(int) {
    /* Nonmatching */
}

/* 000006A8-0000083C       .text mode_break_throw_obj__8daSaku_cFi */
void daSaku_c::mode_break_throw_obj(int) {
    /* Nonmatching */
}

/* 0000083C-000008EC       .text RecreateHeap__8daSaku_cFii */
void daSaku_c::RecreateHeap(int, int) {
    /* Nonmatching */
}

/* 000008EC-000009B0       .text CreateHeap__8daSaku_cFii */
void daSaku_c::CreateHeap(int, int) {
    /* Nonmatching */
}

/* 000009B0-00000A4C       .text GetDzbId__8daSaku_cFi */
void daSaku_c::GetDzbId(int) {
    /* Nonmatching */
}

/* 00000A4C-00000ADC       .text CreateDummyHeap__8daSaku_cFi */
void daSaku_c::CreateDummyHeap(int) {
    /* Nonmatching */
}

/* 00000ADC-00000BE8       .text loadMoveBG__8daSaku_cFiii */
void daSaku_c::loadMoveBG(int, int, int) {
    /* Nonmatching */
}

/* 00000BE8-00000D7C       .text loadModel__8daSaku_cFiii */
void daSaku_c::loadModel(int, int, int) {
    /* Nonmatching */
}

/* 00000D7C-00000E8C       .text burn__8daSaku_cFv */
void daSaku_c::burn() {
    /* Nonmatching */
}

/* 00000E8C-00000F60       .text broken__8daSaku_cFi */
void daSaku_c::broken(int) {
    /* Nonmatching */
}

/* 00000F60-00000FF4       .text changeCollision__8daSaku_cFi */
void daSaku_c::changeCollision(int) {
    /* Nonmatching */
}

/* 00000FF4-0000113C       .text setMtx__8daSaku_cFv */
void daSaku_c::setMtx() {
    /* Nonmatching */
}

/* 0000113C-0000120C       .text setMoveBGMtx__8daSaku_cFv */
void daSaku_c::setMoveBGMtx() {
    /* Nonmatching */
}

/* 0000120C-0000134C       .text checkCol__8daSaku_cFv */
void daSaku_c::checkCol() {
    /* Nonmatching */
}

/* 0000134C-00001510       .text setCol__8daSaku_cFv */
void daSaku_c::setCol() {
    /* Nonmatching */
}

/* 00001510-00001598       .text MoveBGResist__8daSaku_cFii */
void daSaku_c::MoveBGResist(int, int) {
    /* Nonmatching */
}

/* 00001598-000016C0       .text setEffFire__8daSaku_cFi */
void daSaku_c::setEffFire(int) {
    /* Nonmatching */
}

/* 000016C0-000019AC       .text setEffBreak__8daSaku_cFi */
void daSaku_c::setEffBreak(int) {
    /* Nonmatching */
}

/* 000019AC-00001A50       .text matAlphaAnim__FP12J3DModelDataUcb */
void matAlphaAnim(J3DModelData*, unsigned char, bool) {
    /* Nonmatching */
}

/* 00001A50-00001B98       .text changeXluMaterialAlpha__FP11J3DMaterialUcb */
void changeXluMaterialAlpha(J3DMaterial*, unsigned char, bool) {
    /* Nonmatching */
}

/* 00001B98-00001BB8       .text daSaku_Create__FP10fopAc_ac_c */
static cPhs_State daSaku_Create(fopAc_ac_c* i_this) {
    return ((daSaku_c*)i_this)->_daSaku_create();
}

/* 00001BB8-00001F28       .text _daSaku_create__8daSaku_cFv */
cPhs_State daSaku_c::_daSaku_create() {
    /* Nonmatching */
}

/* 00002264-000023D8       .text daSaku_Delete__FP8daSaku_c */
static BOOL daSaku_Delete(daSaku_c*) {
    /* Nonmatching */
}

/* 000023D8-000023E0       .text daSaku_IsDelete__FP8daSaku_c */
static BOOL daSaku_IsDelete(daSaku_c*) {
    return TRUE;
}

/* 000023E0-0000242C       .text daSaku_Draw__FP8daSaku_c */
static BOOL daSaku_Draw(daSaku_c*) {
    /* Nonmatching */
}

/* 0000242C-00002560       .text daSaku_Execute__FP8daSaku_c */
static BOOL daSaku_Execute(daSaku_c*) {
    /* Nonmatching */
}

static actor_method_class l_daSaku_Method = {
    (process_method_func)daSaku_Create,
    (process_method_func)daSaku_Delete,
    (process_method_func)daSaku_Execute,
    (process_method_func)daSaku_IsDelete,
    (process_method_func)daSaku_Draw,
};

actor_process_profile_definition g_profile_SAKU = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_SAKU,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daSaku_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_SAKU,
    /* Actor SubMtd */ &l_daSaku_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_9_e,
};
