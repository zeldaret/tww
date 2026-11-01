/**
 * d_a_waterfall.cpp
 * Object - Waterfall with gate
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_waterfall.h"
#include "d/d_bg_s_func.h"
#include "d/d_bg_s_wtr_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_lib.h"
#include "math.h"

const char daWfall_c::m_arcname[] = "Wfall";
const s8 daWfall_c::m_wait_timer = 50;
const s16 daWfall_c::m_heapsize[2] = {0x35A0, 0x4870};

/* 00000078-000000F0       .text _delete__9daWfall_cFv */
bool daWfall_c::_delete() {
    mPtclCallBack0.remove();
    mPtclCallBack1.remove();
    dComIfG_resDelete(&mPhs, m_arcname);
    mDoAud_seDeleteObject(&mGatePos);
    return true;
}

/* 000000F0-00000110       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daWfall_c*)i_this)->CreateHeap();
}

/* 00000110-0000048C       .text CreateHeap__9daWfall_cFv */
BOOL daWfall_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 0xB);
    JUT_ASSERT(0xFD, modelData != 0);
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);
    if (mpModel == NULL) {
        return FALSE;
    }

    J3DAnmTextureSRTKey* pbtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(m_arcname, 0x12);
    JUT_ASSERT(0x10D, pbtk != 0);
    if (!mBtk.init(modelData, pbtk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }
    mBtk.setPlaySpeed(1.0f);

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 0x7);
    JUT_ASSERT(0x119, modelData != 0);
    mpGateModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpGateModel == NULL) {
        return FALSE;
    }

    if (mType == 1) {
        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, 0xA);
        JUT_ASSERT(0x129, modelData != 0);
        mpMinamoModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000222);
        if (mpMinamoModel == NULL) {
            return FALSE;
        }

        pbtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(m_arcname, 0x11);
        JUT_ASSERT(0x138, pbtk != 0);
        if (!mMinamoBtk.init(modelData, pbtk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
            return FALSE;
        }

        J3DAnmTevRegKey* pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(m_arcname, 0xE);
        JUT_ASSERT(0x143, pbrk != 0);
        if (!mMinamoBrk.init(modelData, pbrk, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0)) {
            return FALSE;
        }
        mMinamoBrk.setPlaySpeed(0.0f);
    }

    return TRUE;
}

/* 0000048C-00000708       .text CreateInit__9daWfall_cFv */
void daWfall_c::CreateInit() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    if (mType == 1) {
        fopAcM_setCullSizeBox(this, -1000.0f, 0.0f, -200.0f, 1200.0f, 1000.0f, 3800.0f);
    } else {
        fopAcM_setCullSizeBox(this, -250.0f, 0.0f, 0.0f, 250.0f, 1000.0f, 800.0f);
    }
    fopAcM_setCullSizeFar(this, 2.5f);
    set_mtx();

    mEmitter0Pos = current.pos;
    mEmitter1Pos = current.pos;
    mEmitter0Angle = current.angle;
    mEmitter1Angle = current.angle;
    dComIfGp_particle_set(0x810D, &mEmitter0Pos, &mEmitter0Angle, NULL, 0xFF, &mPtclCallBack0);
    dComIfGp_particle_set(0x810E, &mEmitter1Pos, &mEmitter1Angle, NULL, 0xFF, &mPtclCallBack1);

    mSwitchNo = fopAcM_GetParam(this) & 0xFF;
    if (dComIfGs_isSwitch(mSwitchNo, fopAcM_GetHomeRoomNo(this))) {
        mode_wtr_off_init();
        mGatePos = current.pos;
        mDemoState = 10;
        if (mType == 1) {
            mMinamoBrk.setFrame(mMinamoBrk.getEndFrame());
        }
    } else {
        mode_wtr_on_init();
        mGatePos = current.pos;
        mGatePos.y += 863.0f;
        if (mType == 1) {
            mMinamoBrk.setFrame(0.0f);
        }
    }

    mEventIdx = dComIfGp_evmng_getEventIdx("GATECLOSE", 0xFF);
}

/* 00000708-00000838       .text _create__9daWfall_cFv */
cPhs_State daWfall_c::_create() {
    fopAcM_ct(this, daWfall_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, m_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        mType = (fopAcM_GetParam(this) >> 8) & 0xF;
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, m_heapsize[mType])) {
            return cPhs_ERROR_e;
        }
        CreateInit();
    }
    return ret;
}

/* 00000938-000009B8       .text set_mtx__9daWfall_cFv */
void daWfall_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000009B8-00000A1C       .text set_gate_mtx__9daWfall_cFv */
void daWfall_c::set_gate_mtx() {
    mDoMtx_stack_c::transS(mGatePos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpGateModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000A1C-00000AD0       .text set_minamo_mtx__9daWfall_cFv */
void daWfall_c::set_minamo_mtx() {
    getWaterHeight();
    cXyz scl(1.0f, 1.0f, 1.0f);
    cXyz pos(0.0f, 0.0f, 0.0f);
    pos.y = dBgS_ObjGndChk_Wtr_Func(pos) + 1.0f;
    mpMinamoModel->setBaseScale(scl);
    mDoMtx_stack_c::transS(pos);
    mpMinamoModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000AD0-00000C94       .text _execute__9daWfall_cFv */
bool daWfall_c::_execute() {
    switch (mDemoState) {
    case 0:
        if (eventInfo.checkCommandDemoAccrpt() || dComIfGp_evmng_startCheck(mEventIdx)) {
            mDemoState++;
        } else if (dComIfGs_isSwitch(mSwitchNo, fopAcM_GetHomeRoomNo(this))) {
            fopAcM_orderOtherEventId(this, mEventIdx, 0xFF, 0xFFFF, 0, 1);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
        break;
    case 1:
        if (dComIfGp_evmng_startCheck(mEventIdx)) {
            mode_wtr_off_init();
            mDemoState++;
        }
        break;
    case 2:
        if (dComIfGp_evmng_endCheck(mEventIdx)) {
            dComIfGp_event_reset();
            mDemoState = 10;
        }
        break;
    case 10:
        field_0x352 = 0;
        break;
    }

    if (!dComIfGs_isSwitch(mSwitchNo, fopAcM_GetHomeRoomNo(this))) {
        mode_wtr_on_init();
        mDemoState = 0;
    }

    if (mType == 1) {
        mMinamoBrk.play();
        mMinamoBtk.play();
        set_minamo_mtx();
    }

    mode_proc_call();
    set_mtx();
    set_gate_mtx();
    return true;
}

/* 00000C94-00000D20       .text mode_proc_call__9daWfall_cFv */
void daWfall_c::mode_proc_call() {
    static ModeProcFunc mode_proc[] = {
        &daWfall_c::mode_wtr_on,
        &daWfall_c::mode_wtr_off,
    };

    (this->*mode_proc[mMode])();
}

/* 00000D20-00000D48       .text mode_wtr_on_init__9daWfall_cFv */
void daWfall_c::mode_wtr_on_init() {
    mMode = 0;
    if (mType == 1) {
        mMinamoBrk.setPlaySpeed(-1.0f);
    }
}

/* 00000D48-00000DEC       .text mode_wtr_on__9daWfall_cFv */
void daWfall_c::mode_wtr_on() {
    cLib_addCalc(&mGatePos.y, 100.0f + (760.0f + current.pos.y), 0.1f, 10.0f, 5.0f);
    scale.y = getWaterScaleFromGatePos();
    mBtk.setPlaySpeed(1.0f);
    mBtk.play();
    BOOL ret = FALSE;
    ret |= setEmitter00Pos();
    ret |= setEmitter01Pos();
    if (ret) {
        set_se();
    }
}

/* 00000DEC-00000E14       .text mode_wtr_off_init__9daWfall_cFv */
void daWfall_c::mode_wtr_off_init() {
    mMode = 1;
    if (mType == 1) {
        mMinamoBrk.setPlaySpeed(1.0f);
    }
}

/* 00000E14-00000EE8       .text mode_wtr_off__9daWfall_cFv */
void daWfall_c::mode_wtr_off() {
    cLib_addCalc(&mGatePos.y, current.pos.y, 0.1f, 10.0f, 5.0f);
    f32 s = getWaterScaleFromGatePos();
    scale.y = s;
    if (s > 0.0f) {
        mBtk.setPlaySpeed(1.0f);
        mBtk.play();
        BOOL ret = FALSE;
        ret |= setEmitter00Pos();
        ret |= setEmitter01Pos();
        if (ret) {
            set_se();
        }
    } else {
        if (mPtclCallBack0.getEmitter() != NULL) {
            mPtclCallBack0.getEmitter()->stopCreateParticle();
        }
        if (mPtclCallBack1.getEmitter() != NULL) {
            mPtclCallBack1.getEmitter()->stopCreateParticle();
        }
    }
}

/* 00000EE8-00000FF0       .text setEmitter00Pos__9daWfall_cFv */
BOOL daWfall_c::setEmitter00Pos() {
    BOOL ret = FALSE;
    mEmitter0Pos = current.pos;
    f32 height = getWaterHeight();
    if (height > mGatePos.y) {
        if (mPtclCallBack0.getEmitter() != NULL) {
            mPtclCallBack0.getEmitter()->stopCreateParticle();
        }
    } else {
        if (mPtclCallBack0.getEmitter() != NULL) {
            mPtclCallBack0.getEmitter()->playCreateParticle();
        }
        ret = TRUE;
    }
    mEmitter0Pos.y = height;
    f32 ratio = fabs(height - current.pos.y) / (760.0f * scale.y);
    if (ratio > 1.0f) {
        ratio = 1.0f;
    }
    if (ratio < -1.0f) {
        ratio = -1.0f;
    }
    f32 angle = asin(ratio);
    mEmitter0Pos.x += 250.0f * scale.y * angle;
    return ret;
}

/* 00000FF0-00001098       .text setEmitter01Pos__9daWfall_cFv */
BOOL daWfall_c::setEmitter01Pos() {
    BOOL ret = FALSE;
    f32 height = getWaterHeight();
    if (height > mGatePos.y) {
        if (mPtclCallBack1.getEmitter() != NULL) {
            mPtclCallBack1.getEmitter()->stopCreateParticle();
        }
    } else {
        if (mPtclCallBack1.getEmitter() != NULL) {
            mPtclCallBack1.getEmitter()->playCreateParticle();
        }
        ret = TRUE;
    }
    mEmitter1Pos.y = current.pos.y - 760.0f * (1.0f - scale.y);
    return ret;
}

/* 00001098-000010D8       .text getWaterScaleFromGatePos__9daWfall_cFv */
f32 daWfall_c::getWaterScaleFromGatePos() {
    f32 scale = mGatePos.y - current.pos.y;
    if (scale < 0.0f) {
        scale = 0.0f;
    }
    scale /= 760.0f;
    if (scale > 1.0f) {
        scale = 1.0f;
    }
    return scale;
}

/* 000010D8-0000124C       .text getWaterHeight__9daWfall_cFv */
f32 daWfall_c::getWaterHeight() {
    dBgS_WtrChk wtrChk;
    cXyz pos = current.pos;
    f32 height = current.pos.y;
    pos.x -= 400.0f;
    wtrChk.Set(pos, 1500.0f + pos.y);
    if (dComIfG_Bgsp()->SplGrpChk(&wtrChk)) {
        height = wtrChk.GetHeight();
    }
    return height;
}

/* 00001370-000013E0       .text set_se__9daWfall_cFv */
void daWfall_c::set_se() {
    mDoAud_seStart(0x701F, &mGatePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
}

bool daWfall_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mBtk.entry(mpModel->getModelData());
    mDoExt_modelUpdateDL(mpModel);

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpGateModel, &tevStr);
    mDoExt_modelUpdateDL(mpGateModel);

    if (mType == 1) {
        g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpMinamoModel, &tevStr);
        mMinamoBtk.entry(mpMinamoModel->getModelData());
        mMinamoBrk.entry(mpMinamoModel->getModelData());
        mDoExt_modelUpdateDL(mpMinamoModel);
    }
    return true;
}

/* 000013E0-00001400       .text daWfall_Create__FPv */
static cPhs_State daWfall_Create(void* i_this) {
    return ((daWfall_c*)i_this)->_create();
}

/* 00001400-00001424       .text daWfall_Delete__FPv */
static BOOL daWfall_Delete(void* i_this) {
    return ((daWfall_c*)i_this)->_delete();
}

/* 00001424-00001550       .text daWfall_Draw__FPv */
static BOOL daWfall_Draw(void* i_this) {
    return ((daWfall_c*)i_this)->_draw();
}

/* 00001550-00001574       .text daWfall_Execute__FPv */
static BOOL daWfall_Execute(void* i_this) {
    return ((daWfall_c*)i_this)->_execute();
}

/* 00001574-0000157C       .text daWfall_IsDelete__FPv */
static BOOL daWfall_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daWfallMethodTable = {
    (process_method_func)daWfall_Create,
    (process_method_func)daWfall_Delete,
    (process_method_func)daWfall_Execute,
    (process_method_func)daWfall_IsDelete,
    (process_method_func)daWfall_Draw,
};

actor_process_profile_definition g_profile_WATERFALL = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_WATERFALL_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daWfall_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_WATERFALL_e,
    /* Actor SubMtd */ &daWfallMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
