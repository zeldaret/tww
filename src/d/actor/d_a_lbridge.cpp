//
// Generated by dtk
// Translation Unit: d_a_lbridge.cpp
//

#include "d/actor/d_a_lbridge.h"
#include "d/d_procname.h"

const char daLbridge_c::m_arcname[] = "Gbrg00";

/* 00000078-00000098       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daLbridge_c*>(i_this)->CreateHeap();
}

/* 00000098-00000384       .text CreateHeap__11daLbridge_cFv */
BOOL daLbridge_c::CreateHeap() {
    /* Nonmatching */
}

/* 00000384-00000544       .text CreateInit__11daLbridge_cFv */
void daLbridge_c::CreateInit() {
    /* Nonmatching */
}

/* 00000544-0000063C       .text _create__11daLbridge_cFv */
s32 daLbridge_c::_create() {
    fopAcM_SetupActor(this, daLbridge_c);

    s32 ret = dComIfG_resLoad(&mPhs, m_arcname);

    if (ret == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x2E10U)) {
            return cPhs_ERROR_e;
        }
        CreateInit();
    }


    return ret;
}

/* 00000798-00000818       .text set_mtx__11daLbridge_cFv */
void daLbridge_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000818-00000888       .text setMoveBGMtx__11daLbridge_cFv */
void daLbridge_c::setMoveBGMtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale);
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);
}

/* 00000888-00000914       .text _execute__11daLbridge_cFv */
BOOL daLbridge_c::_execute() {
    bool sw = fopAcM_isSwitch(this, mSwitchNo);

    sw_check();
    demo();
    mBtkAnm.play();
    mBpkAnm.play();
    mBrkAnm.play();
    set_mtx();

    unk31F = sw;

    return TRUE;
}

/* 00000914-00000A6C       .text sw_check__11daLbridge_cFv */
void daLbridge_c::sw_check() {
    /* Nonmatching */
}

/* 00000A6C-00000C18       .text demo__11daLbridge_cFv */
void daLbridge_c::demo() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(unk318) != FALSE && unk31C == 1) {
            unk31C = 0;
        }
        
        if (dComIfGp_evmng_startCheck(unk31A) != FALSE && unk31C == 2) {
            unk31C = 0;
        }

        if (dComIfGp_evmng_endCheck(unk318) != FALSE) {
            dComIfGp_event_reset();
            dComIfGs_onEventBit(0xE01U);
        }

        if (dComIfGp_evmng_endCheck(unk31A) != FALSE) {
            dComIfGp_event_reset();
            dComIfGs_onEventBit(0xF40U);
        }
    } else {
        if (dComIfGs_isEventBit(0xE01U) == FALSE && this->unk31C == 1) {
            const int i = sizeof(daLbridge_c);
            fopAcM_orderOtherEventId(this, unk318);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        } else if (dComIfGs_isEventBit(0xF40U) == FALSE && this->unk31C == 2) {
            fopAcM_orderOtherEventId(this, unk31A);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
    }
}

/* 00000C18-00000D90       .text appear_bridge__11daLbridge_cFv */
void daLbridge_c::appear_bridge() {
    /* Nonmatching */
}

/* 00000D90-00000E30       .text disappear_bridge__11daLbridge_cFv */
void daLbridge_c::disappear_bridge() {
    /* Nonmatching */
}

/* 00000E30-00000EA0       .text set_on_se__11daLbridge_cFv */
void daLbridge_c::set_on_se() {
    fopAcM_seStart(this, JA_SE_OBJ_L_BRIDGE_ON, 0);
}

/* 00000EA0-00000F10       .text set_off_se__11daLbridge_cFv */
void daLbridge_c::set_off_se() {
    fopAcM_seStart(this, JA_SE_OBJ_L_BRIDGE_OFF, 0);
}

/* 00000F10-00000FF8       .text _draw__11daLbridge_cFv */
BOOL daLbridge_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    mBtkAnm.entry(mpModel->getModelData());
    mBpkAnm.entry(mpModel->getModelData());
    mBrkAnm.entry(mpModel->getModelData());

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();

    return TRUE;
}

BOOL daLbridge_c::_delete() {
    /* Nonmatching */
}

/* 00000FF8-00001018       .text daLbridge_Create__FPv */
static s32 daLbridge_Create(void* i_this) {
    return static_cast<daLbridge_c*>(i_this)->_create();
}

/* 00001018-000010D4       .text daLbridge_Delete__FPv */
static BOOL daLbridge_Delete(void* i_this) {
    return static_cast<daLbridge_c*>(i_this)->_delete();
}

/* 000010D4-000010F8       .text daLbridge_Draw__FPv */
static BOOL daLbridge_Draw(void* i_this) {
    return (u8)static_cast<daLbridge_c*>(i_this)->_draw();
}

/* 000010F8-0000111C       .text daLbridge_Execute__FPv */
static BOOL daLbridge_Execute(void* i_this) {
    return (u8)static_cast<daLbridge_c*>(i_this)->_execute();
}

/* 0000111C-00001124       .text daLbridge_IsDelete__FPv */
static BOOL daLbridge_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daLbridgeMethodTable = {
    (process_method_func)daLbridge_Create,
    (process_method_func)daLbridge_Delete,
    (process_method_func)daLbridge_Execute,
    (process_method_func)daLbridge_IsDelete,
    (process_method_func)daLbridge_Draw,
};

actor_process_profile_definition g_profile_LIGHTBRIDGE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_LIGHTBRIDGE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daLbridge_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0196,
    /* Actor SubMtd */ &daLbridgeMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
