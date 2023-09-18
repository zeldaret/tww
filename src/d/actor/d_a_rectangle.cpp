/**
 * d_a_rectangle.cpp
 */
#include "f_op/f_op_actor.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

struct RECTANGLE_class{};

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
static BOOL daRct_Create(fopAc_ac_c*) {
    return 0x4;
}

static actor_method_class RECTANGLE_class = {
    (process_method_func)daRct_Create,
    (process_method_func)daRct_Delete,
    (process_method_func)daRct_Execute,
    (process_method_func)daRct_IsDelete,
    (process_method_func)daRct_Draw,
};

extern actor_process_profile_definition g_profile_RECTANGLE = {
    fpcLy_CURRENT_e,
    0x0007FFFD,
    0x00B50000,
    PROC_RECTANGLE,
    0x00000290,
    0x00000000,
    0x00000000,
    g_fopAc_Method,
    0x009F0000,
    l_daRct_Method,
    0x00040000,
    0x00000000
};
