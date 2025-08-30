/**
 * d_a_obj_timer.cpp
 * Object - Timer
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_timer.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h" // IWYU pragma: keep // Needed for dComIfGs_isSwitch inline definition

/* 00000078-00000114       .text _create__Q210daObjTimer5Act_cFv */
cPhs_State daObjTimer::Act_c::_create() {
    fopAcM_SetupActor(this, daObjTimer::Act_c);

    fopAcM_offDraw(this);

    if (fopAcM_isSwitch(this, prm_get_swSave())) {
        mode_count_init();
    } else {
        mode_wait_init();
    }

    return cPhs_COMPLEATE_e;
}

/* 00000114-0000011C       .text _delete__Q210daObjTimer5Act_cFv */
bool daObjTimer::Act_c::_delete() {
    return true;
}

/* 0000011C-0000012C       .text mode_wait_init__Q210daObjTimer5Act_cFv */
void daObjTimer::Act_c::mode_wait_init() {
    mTimer = 0;
    mMode = Mode_WAIT_e;
}

/* 0000012C-00000188       .text mode_wait__Q210daObjTimer5Act_cFv */
void daObjTimer::Act_c::mode_wait() {
    if (fopAcM_isSwitch(this, prm_get_swSave())) {
        mode_count_init();
    }
}

/* 00000188-000001CC       .text mode_count_init__Q210daObjTimer5Act_cFv */
void daObjTimer::Act_c::mode_count_init() {
    mTimer = 15 * prm_get_time();
    mMode = Mode_COUNT_e;
}

/* 000001CC-00000304       .text mode_count__Q210daObjTimer5Act_cFv */
void daObjTimer::Act_c::mode_count() {
    if (mIsStop) return;

    mTimer -= 1;
    if (mTimer % 30 == 0) {
        s32 secondsLeft = mTimer / 30;
        if (secondsLeft <= 20) {
            u32 soundId;
            if (secondsLeft > 10) {
                soundId = JA_SE_SYS_EV_TIMER_20;
            } else if (secondsLeft > 5) {
                soundId = JA_SE_SYS_EV_TIMER_10;
            } else if (secondsLeft > 0) {
                soundId = JA_SE_SYS_EV_TIMER_5;
            } else {
                soundId = JA_SE_SYS_EV_TIMER_0;
            }

            mDoAud_seStart(soundId);
        }
    }

    if (mTimer <= 0 || !fopAcM_isSwitch(this, prm_get_swSave())) {
        fopAcM_offSwitch(this, prm_get_swSave());
        mode_wait_init();
    }
}

/* 00000304-00000394       .text _execute__Q210daObjTimer5Act_cFv */
bool daObjTimer::Act_c::_execute() {
    static ModeFunc mode_proc[] = {
        &Act_c::mode_wait,
        &Act_c::mode_count,
    };
    (this->*mode_proc[mMode])();

    return true;
}

namespace daObjTimer {
namespace {
/* 00000394-000003B4       .text Mthd_Create__Q210daObjTimer27@unnamed@d_a_obj_timer_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return static_cast<daObjTimer::Act_c*>(i_this)->_create();
}

/* 000003B4-000003D8       .text Mthd_Delete__Q210daObjTimer27@unnamed@d_a_obj_timer_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return static_cast<daObjTimer::Act_c*>(i_this)->_delete();
}

/* 000003D8-000003FC       .text Mthd_Execute__Q210daObjTimer27@unnamed@d_a_obj_timer_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return static_cast<daObjTimer::Act_c*>(i_this)->_execute();
}

/* 000003FC-00000404       .text Mthd_Draw__Q210daObjTimer27@unnamed@d_a_obj_timer_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return TRUE;
}

/* 00000404-0000040C       .text Mthd_IsDelete__Q210daObjTimer27@unnamed@d_a_obj_timer_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjTimer

actor_process_profile_definition g_profile_Obj_Timer = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x000A,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Timer,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjTimer::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Timer,
    /* Actor SubMtd */ &daObjTimer::Mthd_Table,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
