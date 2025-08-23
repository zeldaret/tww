/**
 * d_a_yougan.cpp
 * Object - Unused - Lava bubbles
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_yougan.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 000000EC-00000158       .text __ct__14daYOUGAN_HIO_cFv */
daYOUGAN_HIO_c::daYOUGAN_HIO_c() {
    /* Nonmatching */
}

/* 00000158-00000178       .text daYougan_Draw__FP10daYougan_c */
static BOOL daYougan_Draw(daYougan_c* i_this) {
    return ((daYougan_c*)i_this)->_daYougan_draw();
}

/* 00000178-000002A8       .text _daYougan_draw__10daYougan_cFv */
BOOL daYougan_c::_daYougan_draw() {
    /* Nonmatching */
}

/* 000002A8-000002C8       .text daYougan_Execute__FP10daYougan_c */
static BOOL daYougan_Execute(daYougan_c* i_this) {
    return ((daYougan_c*)i_this)->_daYougan_execute();
}

/* 000002C8-00000554       .text _daYougan_execute__10daYougan_cFv */
BOOL daYougan_c::_daYougan_execute() {
    /* Nonmatching */
}

/* 00000554-00000574       .text daYougan_IsDelete__FP10daYougan_c */
static BOOL daYougan_IsDelete(daYougan_c* i_this) {
    return ((daYougan_c*)i_this)->_daYougan_isdelete();
}

/* 00000574-0000057C       .text _daYougan_isdelete__10daYougan_cFv */
BOOL daYougan_c::_daYougan_isdelete() {
    /* Nonmatching */
}

/* 0000057C-0000059C       .text daYougan_Delete__FP10daYougan_c */
static BOOL daYougan_Delete(daYougan_c* i_this) {
    return ((daYougan_c*)i_this)->_daYougan_delete();
}

/* 0000059C-00000600       .text _daYougan_delete__10daYougan_cFv */
BOOL daYougan_c::_daYougan_delete() {
    /* Nonmatching */
}

/* 00000600-00000884       .text useHeapInit__10daYougan_cFv */
BOOL daYougan_c::useHeapInit() {
    /* Nonmatching */
}

/* 00000884-000008A4       .text daYougan_solidHeapCB__FP10fopAc_ac_c */
static BOOL daYougan_solidHeapCB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000008A4-000008C4       .text daYougan_Create__FP10fopAc_ac_c */
static cPhs_State daYougan_Create(fopAc_ac_c* i_this) {
    return ((daYougan_c*)i_this)->_daYougan_create();
}

/* 000008C4-000009C8       .text _daYougan_create__10daYougan_cFv */
cPhs_State daYougan_c::_daYougan_create() {
    /* Nonmatching */
}

static actor_method_class l_daYougan_Method = {
    (process_method_func)daYougan_Create,
    (process_method_func)daYougan_Delete,
    (process_method_func)daYougan_Execute,
    (process_method_func)daYougan_IsDelete,
    (process_method_func)daYougan_Draw,
};

actor_process_profile_definition g_profile_YOUGAN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_YOUGAN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daYougan_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_YOUGAN,
    /* Actor SubMtd */ &l_daYougan_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
