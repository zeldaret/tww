/**
 * d_a_rectangle.cpp
 */
#include "f_op/f_op_actor.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

struct RECTANGLE_class : fopAc_ac_c {};

/* 00000078-00000080       .text daRct_Draw__FP15RECTANGLE_class */
static BOOL daRct_Draw(RECTANGLE_class*) {
    return true;
}

/* 00000080-00000088       .text daRct_Execute__FP15RECTANGLE_class */
static BOOL daRct_Execute(RECTANGLE_class*) {
    return true;
}

/* 00000088-00000090       .text daRct_IsDelete__FP15RECTANGLE_class */
static BOOL daRct_IsDelete(RECTANGLE_class*) {
    return true;
}

/* 00000090-00000098       .text daRct_Delete__FP15RECTANGLE_class */
static BOOL daRct_Delete(RECTANGLE_class*) {
    return true;
}

/* 00000098-000000A0       .text daRct_Create__FP10fopAc_ac_c */
static int daRct_Create(fopAc_ac_c*) {
    return 0x4;
}

static actor_method_class l_daRct_Method = {
    (process_method_func)daRct_Create,
    (process_method_func)daRct_Delete,
    (process_method_func)daRct_Execute,
    (process_method_func)daRct_IsDelete,
    (process_method_func)daRct_Draw,
};

extern actor_process_profile_definition g_profile_RECTANGLE = {
    fpcLy_CURRENT_e,
    7,
    fpcLy_CURRENT_e,
    PROC_RECTANGLE,
    &g_fpcLf_Method.mBase,
    sizeof(RECTANGLE_class),
    0,
    0,
    &g_fopAc_Method.base,
    0x9F,
    &l_daRct_Method,
    fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};
