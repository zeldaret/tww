/**
 * d_a_obj_ice.cpp
 * Object - Block of ice (blocks treasure chests, enemies, rupees, etc.)
 */

#include "d/actor/d_a_obj_ice.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

class J3DMaterial;

/* 00000078-000000F0       .text chk_appear__10daObjIce_cFv */
void daObjIce_c::chk_appear() {
    /* Nonmatching */
}

/* 000000F0-0000018C       .text set_mtx__10daObjIce_cFv */
void daObjIce_c::set_mtx() {
    /* Nonmatching */
}

/* 0000018C-000001C8       .text init_mtx__10daObjIce_cFv */
void daObjIce_c::init_mtx() {
    /* Nonmatching */
}

/* 000001C8-000001EC       .text solidHeapCB__10daObjIce_cFP10fopAc_ac_c */
void daObjIce_c::solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000001EC-000002E4       .text create_heap__10daObjIce_cFv */
void daObjIce_c::create_heap() {
    /* Nonmatching */
}

/* 000002E4-000005F4       .text tg_hitCallback__10daObjIce_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daObjIce_c::tg_hitCallback(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 000005F4-000008C0       .text _create__10daObjIce_cFv */
cPhs_State daObjIce_c::_create() {
    /* Nonmatching */
}

/* 00000A78-00000B18       .text _delete__10daObjIce_cFv */
bool daObjIce_c::_delete() {
    /* Nonmatching */
}

/* 00000B18-00000CA4       .text wait_act_proc__10daObjIce_cFv */
void daObjIce_c::wait_act_proc() {
    /* Nonmatching */
}

/* 00000CA4-00000DFC       .text fade_out_retire_act_proc__10daObjIce_cFv */
void daObjIce_c::fade_out_retire_act_proc() {
    /* Nonmatching */
}

/* 00000DFC-00000EB8       .text _execute__10daObjIce_cFv */
bool daObjIce_c::_execute() {
    /* Nonmatching */
}

/* 00000EB8-00000F48       .text set_material_sub__FP11J3DMaterialUc */
void set_material_sub(J3DMaterial*, unsigned char) {
    /* Nonmatching */
}

/* 00000F48-00000FB0       .text set_material__FP8J3DModelUc */
void set_material(J3DModel*, unsigned char) {
    /* Nonmatching */
}

/* 00000FB0-00001070       .text _draw__10daObjIce_cFv */
bool daObjIce_c::_draw() {
    /* Nonmatching */
}

/* 00001070-000013A0       .text setEffectMtx__10daObjIce_cFv */
void daObjIce_c::setEffectMtx() {
    /* Nonmatching */
}

/* 000013A0-000013C0       .text daObjIce_Create__FP10fopAc_ac_c */
static cPhs_State daObjIce_Create(fopAc_ac_c* i_this) {
    return ((daObjIce_c*)i_this)->_create();
}

/* 000013C0-000013E4       .text daObjIce_Delete__FP10daObjIce_c */
static BOOL daObjIce_Delete(daObjIce_c* i_this) {
    return ((daObjIce_c*)i_this)->_delete();
}

/* 000013E4-00001408       .text daObjIce_Execute__FP10daObjIce_c */
static BOOL daObjIce_Execute(daObjIce_c* i_this) {
    return ((daObjIce_c*)i_this)->_execute();
}

/* 00001408-0000142C       .text daObjIce_Draw__FP10daObjIce_c */
static BOOL daObjIce_Draw(daObjIce_c* i_this) {
    return ((daObjIce_c*)i_this)->_draw();
}

/* 0000142C-00001434       .text daObjIce_IsDelete__FP10daObjIce_c */
static BOOL daObjIce_IsDelete(daObjIce_c*) {
    return TRUE;
}

static actor_method_class l_daObjIce_Method = {
    (process_method_func)daObjIce_Create,
    (process_method_func)daObjIce_Delete,
    (process_method_func)daObjIce_Execute,
    (process_method_func)daObjIce_IsDelete,
    (process_method_func)daObjIce_Draw,
};

actor_process_profile_definition g_profile_Obj_Ice = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ice,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjIce_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Ice,
    /* Actor SubMtd */ &l_daObjIce_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
