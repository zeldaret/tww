/*
 * d_a_seatag.cpp
 */
#include "JSystem/JKernel/JKRHeap.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_procname.h"

struct daSeatag_c : public fopAc_ac_c {
public:
    /* 0x00 */ int field_0x00;
    /* 0x04 */ int field_0x04;
}; // size 0x298

static BOOL daSeatag_Draw(daSeatag_c*) {
    return true;
}

static  BOOL daSeatag_Execute(daSeatag_c*) {
    return true;
}

static BOOL daSeatag_IsDelete(daSeatag_c*) {
    return true;
}

static BOOL daSeatag_Delete(daSeatag_c* a_this) {
    a_this->~daSeatag_c();
    return 1;
}

static int daSeatag_Create(fopAc_ac_c* a_this) {
    fopAcM_SetupActor(a_this, daSeatag_c);
    return 4;
}
static actor_method_class l_daSeatag_Method = {
    (process_method_func)daSeatag_Create,
    (process_method_func)daSeatag_Delete,
    (process_method_func)daSeatag_Execute,
    (process_method_func)daSeatag_IsDelete,
    (process_method_func)daSeatag_Draw,
};

actor_process_profile_definition g_profile_SEATAG = {
    fpcLy_CURRENT_e,
    2,
    fpcLy_CURRENT_e,
    PROC_SEATAG,
    &g_fpcLf_Method.mBase,
    sizeof(daSeatag_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x01DF,
    &l_daSeatag_Method,
    fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};
