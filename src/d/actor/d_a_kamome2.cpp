#include "d/actor/d_a_kamome2.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

static void anm_init(kamome2_class*, int, f32, u8, f32, int) {
    /* Nonmatching */
}

static BOOL daKamome2_Draw(kamome2_class*) {
    /* Nonmatching */
}

static void kamome2_bgcheck(kamome2_class*) {
    /* Nonmatching */
}

static void key_move(kamome2_class*) {
    /* Nonmatching */
}

static BOOL daKamome2_Execute(kamome2_class*) {
    /* Nonmatching */
}

static BOOL daKamome2_IsDelete(kamome2_class*) {
    /* Nonmatching */
}

static BOOL daKamome2_Delete(kamome2_class*) {
    /* Nonmatching */
}

static BOOL useHeapInit(fopAc_ac_c*) {
    /* Nonmatching */
}

static cPhs_State daKamome2_Create(fopAc_ac_c*) {
    /* Nonmatching */
}

static actor_method_class l_daKamome2_Method = {
    (process_method_func)daKamome2_Create,
    (process_method_func)daKamome2_Delete,
    (process_method_func)daKamome2_Execute,
    (process_method_func)daKamome2_IsDelete,
    (process_method_func)daKamome2_Draw,
};

actor_process_profile_definition g_profile_KAMOME2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KAMOME2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kamome2_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KAMOME2,
    /* Actor SubMtd */ &l_daKamome2_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
