/**
 * d_a_kytag06.cpp
 * Tag - Weather Tag 6
 */

#include "d/actor/d_a_kytag06.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_kankyo_wether.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

/* 00000078-00000080       .text daKytag06_Draw__FP13kytag06_class */
static BOOL daKytag06_Draw(kytag06_class*) {
    return TRUE;
}

/* 00000080-00000194       .text daKytag06_Execute__FP13kytag06_class */
static BOOL daKytag06_Execute(kytag06_class* i_this) {
    f32 time;
    int date;

    if (dComIfGp_event_runCheck() == FALSE) {
        return TRUE;
    }
    if(!dComIfGp_evmng_startCheck("ARRIVAL_BRK")) {
        return TRUE;
    }

    time = dComIfGs_getTime();
    date = dComIfGs_getDate();
    if (time >= 90.0f && time < 345) {
        time += 0.05f;
    }
    dComIfGs_setTime(time);
    dComIfGs_setDate(date);

    dKy_change_colpat(1);
    date = i_this->field_0x294 * 250.0f;
    if (date > g_env_light.mRainCount) {
        dKyw_rain_set(date);
    }
    g_env_light.mThunderEff.mMode = 1;
    cLib_addCalc(&i_this->field_0x294, 1.0f, 0.1f, 0.001f, 0.0001f);
    return TRUE;
}

/* 00000194-0000019C       .text daKytag06_IsDelete__FP13kytag06_class */
static BOOL daKytag06_IsDelete(kytag06_class*) {
    return true;
}

/* 0000019C-000001A4       .text daKytag06_Delete__FP13kytag06_class */
static BOOL daKytag06_Delete(kytag06_class*) {
    return true;
}

/* 000001A4-00000224       .text daKytag06_Create__FP10fopAc_ac_c */
static cPhs_State daKytag06_Create(fopAc_ac_c* i_this) {
#if VERSION > VERSION_DEMO
    fopAcM_SetupActor(i_this, kytag06_class);
#endif
    kytag06_class* a_this = (kytag06_class*)i_this;

    cPhs_State phase_state;
    if(dComIfGs_isSymbol(0)) {
        phase_state = cPhs_ERROR_e;
    } else {
#if VERSION == VERSION_DEMO
        fopAcM_SetupActor(i_this, kytag06_class);
#endif
        a_this->field_0x294 = 0;
        phase_state = cPhs_COMPLEATE_e;
    }

    return phase_state;
}

static actor_method_class l_daKytag06_Method = {
    (process_method_func)daKytag06_Create,
    (process_method_func)daKytag06_Delete,
    (process_method_func)daKytag06_Execute,
    (process_method_func)daKytag06_IsDelete,
    (process_method_func)daKytag06_Draw,
};

actor_process_profile_definition g_profile_KYTAG06 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KYTAG06,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kytag06_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KYTAG06,
    /* Actor SubMtd */ &l_daKytag06_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
