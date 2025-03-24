//
// Generated by dtk
// Translation Unit: d_a_bridge.cpp
//

#include "d/actor/d_a_bridge.h"
#include "d/d_bg_w.h"
#include "d/d_procname.h"

/* 00000078-00000504       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW*, fopAc_ac_c*, fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000540-00000614       .text kikuzu_set__FP12bridge_classP4cXyz */
void kikuzu_set(bridge_class*, cXyz*) {
    /* Nonmatching */
}

/* 00000614-000011EC       .text daBridge_Draw__FP12bridge_class */
static BOOL daBridge_Draw(bridge_class*) {
    /* Nonmatching */
}

/* 000011EC-00001580       .text control1__FP12bridge_classP4br_s */
void control1(bridge_class*, br_s*) {
    /* Nonmatching */
}

/* 00001580-0000178C       .text control2__FP12bridge_classP4br_s */
void control2(bridge_class*, br_s*) {
    /* Nonmatching */
}

/* 0000178C-000018A8       .text control3__FP12bridge_classP4br_s */
void control3(bridge_class*, br_s*) {
    /* Nonmatching */
}

/* 000018A8-00001B08       .text cut_control1__FP12bridge_classP4br_s */
void cut_control1(bridge_class*, br_s*) {
    /* Nonmatching */
}

/* 00001B08-00001D84       .text cut_control2__FP12bridge_classP4br_s */
void cut_control2(bridge_class*, br_s*) {
    /* Nonmatching */
}

/* 00001D84-00001FAC       .text himo_cut_control1__FP4cXyz */
void himo_cut_control1(cXyz*) {
    /* Nonmatching */
}

/* 00001FAC-00002A1C       .text bridge_move__FP12bridge_class */
void bridge_move(bridge_class*) {
    /* Nonmatching */
}

/* 00002A1C-00002A8C       .text s_a_b_sub__FPvPv */
void s_a_b_sub(void*, void*) {
    /* Nonmatching */
}

/* 00002A8C-00002AB8       .text search_aite__FP12bridge_class */
void search_aite(bridge_class*) {
    /* Nonmatching */
}

/* 00002AB8-00003C68       .text daBridge_Execute__FP12bridge_class */
static BOOL daBridge_Execute(bridge_class*) {
    /* Nonmatching */
}

/* 00003C68-00003CD4       .text daBridge_IsDelete__FP12bridge_class */
static BOOL daBridge_IsDelete(bridge_class*) {
    /* Nonmatching */
}

/* 00003CD4-00003D2C       .text daBridge_Delete__FP12bridge_class */
static BOOL daBridge_Delete(bridge_class*) {
    /* Nonmatching */
}

/* 00003D2C-00003E00       .text CreateInit__FP10fopAc_ac_c */
void CreateInit(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00003E00-00004310       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00004310-00004770       .text daBridge_Create__FP10fopAc_ac_c */
static cPhs_State daBridge_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daBridge_Method = {
    (process_method_func)daBridge_Create,
    (process_method_func)daBridge_Delete,
    (process_method_func)daBridge_Execute,
    (process_method_func)daBridge_IsDelete,
    (process_method_func)daBridge_Draw,
};

actor_process_profile_definition g_profile_BRIDGE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BRIDGE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bridge_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0089,
    /* Actor SubMtd */ &l_daBridge_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
