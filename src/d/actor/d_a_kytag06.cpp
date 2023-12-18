/**
 * d_a_kytag06.cpp
 */

#include "d/actor/d_a_kytag06.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_kankyo_wether.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

static bool daKytag06_Draw(kytag06_class*) {
    return true;
}

static BOOL daKytag06_Execute(kytag06_class* i_this) {
    f32 time;
    int date;

    if (g_dComIfG_gameInfo.play.mEvtCtrl.mMode == 0) {
        return TRUE;
    }
    if(dComIfGp_evmng_startCheck("ARRIVAL_BRK") == 0) {
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

static BOOL daKytag06_IsDelete(kytag06_class*) {
    return true;
}

static BOOL daKytag06_Delete(kytag06_class*) {
    return true;
}

static int daKytag06_Create(fopAc_ac_c* i_this) {
    kytag06_class* tag = (kytag06_class*)i_this;
    int var;

    fopAcM_SetupActor(tag, kytag06_class);

    if(dComIfGs_isSymbol(0) != 0) {
        var = 5;
    } else {
        tag->field_0x294 = 0;
        var = 4;
    }

    return var;
}

static actor_method_class l_daKytag06_Method = {
    (process_method_func)daKytag06_Create,
    (process_method_func)daKytag06_Delete,
    (process_method_func)daKytag06_Execute,
    (process_method_func)daKytag06_IsDelete,
    (process_method_func)daKytag06_Draw,
};

actor_process_profile_definition g_profile_KYTAG06 = {
    fpcLy_CURRENT_e,
    7,
    fpcLy_CURRENT_e,
    PROC_KYTAG06,
    &g_fpcLf_Method.mBase,
    sizeof(kytag06_class),
    0,
    0,
    &g_fopAc_Method.base,
    0xA6,
    &l_daKytag06_Method,
    fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};
