/**
 * d_a_lstair.cpp
 * Object - Tower of the Gods - Glowing stairs
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_lstair.h"
#include "d/d_stage.h"
#include "res/Object/Gkai00.h"

const char daLStair_c::m_arcname[] = "Gkai00";

/* 00000078-000000D4       .text _delete__10daLStair_cFv */
bool daLStair_c::_delete() {
    if (heap != NULL) {
        dComIfG_Bgsp()->Release(mpBgW);
    }

    dComIfG_resDelete(&mPhase, m_arcname);

    return TRUE;
}

/* 000000D4-000000F4       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daLStair_c*>(i_this)->CreateHeap();
}

/* 000000F4-000004F8       .text CreateHeap__10daLStair_cFv */
BOOL daLStair_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_GKAI00_BDL_GKAI00_e);
    JUT_ASSERT(0xD8, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000223);
    if (mpModel == NULL) {
        return FALSE;
    }

    J3DAnmTransform* pbck = (J3DAnmTransform*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_GKAI00_BCK_GKAI00_e);
    JUT_ASSERT(0xE9, pbck != NULL);

    if (!mBckAnm.init(modelData, pbck, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false)) {
        return FALSE;
    }

    J3DAnmTextureSRTKey* pbtk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_GKAI00_BTK_GKAI00_e);
    JUT_ASSERT(0xF4, pbtk != NULL);

    if (!mBtkAnm.init(modelData, pbtk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }

    J3DAnmColor* pbpk = (J3DAnmColor*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_GKAI00_BPK_GKAI00_01_e);
    JUT_ASSERT(0xFF, pbpk != NULL);

    if (!mBpkAnm0.init(modelData, pbpk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }

    pbpk = (J3DAnmColor*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_GKAI00_BPK_GKAI00_02_e);
    JUT_ASSERT(0x10A, pbpk != NULL);

    if (!mBpkAnm1.init(modelData, pbpk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }

    J3DAnmTevRegKey* pbrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_GKAI00_BRK_GKAI00_e);
    JUT_ASSERT(0x116, pbrk != NULL);

    if (!mBrkAnm.init(modelData, pbrk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
        return FALSE;
    }

    mpBgW = new dBgW();
    if (mpBgW != NULL) {
        cBgD_t* bgd_data = (cBgD_t*)dComIfG_getObjectRes(m_arcname, dRes_INDEX_GKAI00_DZB_GKAI00_e);

        if (mpBgW->Set(bgd_data, cBgW::MOVE_BG_e, &mBgMtx) == true) {
            return FALSE;
        } else {
            return TRUE;
        }
    }

    return FALSE;
}

/* 000004F8-00000638       .text CreateInit__10daLStair_cFv */
void daLStair_c::CreateInit() {
    cullMtx = mpModel->getBaseTRMtx();
    fopAcM_setCullSizeBox(this, -200.0f, -300.0f, -100.0f, 200.0f, 100.0f, 700.0f);
    cullSizeFar = 1.5f;
    mSwitchNo = fopAcM_GetParam(this) & 0xFF; 
    mSwitchStatus = dComIfGs_isSwitch(mSwitchNo, fopAcM_GetHomeRoomNo(this)) != 0;
    mEnemyGone = fopAcM_myRoomSearchEnemy(fopAcM_GetRoomNo(this)) == NULL;
    mEventIdx = dComIfGp_evmng_getEventIdx("STAIRAPPEAR", 0xFF);
    mStairYOffset = -330.0f;
    mAppearTimer = -1;

    if ((mSwitchNo == 0xFF && mEnemyGone) || (mSwitchNo != 0xFF && mSwitchStatus)) {
        mStairYOffset = 0.0f; 
    }

    setMoveBGMtx();
    dComIfG_Bgsp()->Regist(mpBgW, this);
    mpBgW->Move();
    set_mtx();
}

/* 00000638-00000758       .text _create__10daLStair_cFv */
cPhs_State daLStair_c::_create() {
    fopAcM_ct(this, daLStair_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhase, m_arcname);
    
    if (phase_state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x2960)) {
            return cPhs_ERROR_e; 
        }
        
        CreateInit();
    }

    return phase_state;
}

/* 00000910-00000998       .text set_mtx__10daLStair_cFv */
void daLStair_c::set_mtx() {
    mpModel->setBaseScale(scale);

    mDoMtx_stack_c::transS(
        current.pos.x,
        current.pos.y + mStairYOffset,
        current.pos.z
    );
    mDoMtx_stack_c::YrotM(current.angle.y);
   
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000998-00000A1C       .text setMoveBGMtx__10daLStair_cFv */
void daLStair_c::setMoveBGMtx() {
    f32 y = current.pos.y;
    f32 h = mStairYOffset;
    f32 c = -300.0f;

    mDoMtx_stack_c::transS(
        current.pos.x,
        h + (y + c),
        current.pos.z
    );

    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
    mDoMtx_copy(mDoMtx_stack_c::get(), mBgMtx);
}

/* 00000A1C-00000ACC       .text _execute__10daLStair_cFv */
bool daLStair_c::_execute() {
    bool switch_status = dComIfGs_isSwitch(mSwitchNo, fopAcM_GetHomeRoomNo(this));
    bool enemy_gone = fopAcM_myRoomSearchEnemy(fopAcM_GetRoomNo(this)) == NULL;

    checkAppear();
    demoMove();
    moveBG();

    mBtkAnm.play();
    mBpkAnm0.play();
    mBpkAnm1.play();
    mBrkAnm.play();

    set_mtx();

    mSwitchStatus = switch_status;
    mEnemyGone = enemy_gone;

    return 1;
}

/* 00000ACC-00000B8C       .text demoMove__10daLStair_cFv */
void daLStair_c::demoMove() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_endCheck(mEventIdx)) {
            dComIfGp_event_reset();
        }
    } else if (mEventState == 1) {
        fopAcM_orderOtherEventId(this, mEventIdx, 0xFF, 0xFFFF, 0, 1);
        eventInfo.onCondition(dEvtCnd_UNK2_e);
    }

    if (dComIfGp_evmng_startCheck(mEventIdx)) {
        mEventState = 0;
    }
}

/* 00000B8C-00000C88       .text checkAppear__10daLStair_cFv */
void daLStair_c::checkAppear() {
    bool switch_status = dComIfGs_isSwitch(
        mSwitchNo,
        fopAcM_GetHomeRoomNo(this)
    );
    bool enemy_gone = fopAcM_myRoomSearchEnemy(current.roomNo) == NULL;

    if (mSwitchNo != 0xFF) {
        if (switch_status != mSwitchStatus) {
            if (switch_status) {
                appear_stair();
            } else {
                disappear_stair();
            }
        }
    } else {
        if (enemy_gone != mEnemyGone) {
            if (enemy_gone) {
                mAppearTimer = 0x33;
            } else {
                disappear_stair();
            }
        }

        s8 timer = mAppearTimer;
        if (timer > 0) {
            mAppearTimer = timer - 1;
        } else if (timer == 0) {
            appear_stair();
            mAppearTimer = mAppearTimer - 1;
        }
    }
}

/* 00000C88-00000D78       .text moveBG__10daLStair_cFv */
void daLStair_c::moveBG() {
    bool switch_status = dComIfGs_isSwitch(mSwitchNo, home.roomNo);
    bool enemy_gone = fopAcM_myRoomSearchEnemy(current.roomNo) == NULL;

    f32 target;
    if ((mSwitchNo != 0xFF && switch_status) ||
        (mSwitchNo == 0xFF && enemy_gone)) {
        target = 0.0f;
    } else {
        target = -300.0f;
    }

    if (mAppearTimer < 0) {
        if (cLib_calcTimer(&mTimer) == 0) {
            cLib_addCalc(&mStairYOffset, target, 1.0f / 60.0f, 10.0f, 5.0f);
        }
    }

    setMoveBGMtx();
    mpBgW->Move();
}

/* 00000D78-00000F74       .text appear_stair__10daLStair_cFv */
void daLStair_c::appear_stair() {
    cXyz local_20 = home.pos; 
    cXyz local_2c(-148.0f, 0.0f, 0.0f);
    cXyz local_38(148.0f, 0.0f, 0.0f);

    mDoMtx_stack_c::transS(
        current.pos.x,
        home.pos.y - 300.0f,
        current.pos.z
    );
    mDoMtx_stack_c::YrotM(current.angle.y);

    PSMTXMultVec(mDoMtx_stack_c::get(), &local_2c, &local_2c);
    PSMTXMultVec(mDoMtx_stack_c::get(), &local_38, &local_38);

    local_20.y -= 300.0f;

    dComIfGp_particle_set(dPa_name::ID_IT_SN_RSTAIRS_F00, &local_20, &current.angle);
    dComIfGp_particle_set(dPa_name::ID_IT_SN_RSTAIRS_S00, &local_2c, &current.angle);
    dComIfGp_particle_set(dPa_name::ID_IT_SN_RSTAIRS_S00, &local_38, &current.angle);

    set_on_se();

    mBpkAnm0.setFrame(0.0f);
    mBpkAnm0.setPlaySpeed(1.0f);
    mBpkAnm1.setFrame(0.0f);
    mBpkAnm1.setPlaySpeed(1.0f);
    mBtkAnm.setFrame(0.0f);
    mBtkAnm.setPlaySpeed(1.0f);
    mBrkAnm.setPlaySpeed(1.0f);

    mTimer = 0x28;
    mEventState = 1;
}

/* 00000F74-0000103C       .text disappear_stair__10daLStair_cFv */
void daLStair_c::disappear_stair() {
    set_off_se();

    mBpkAnm0.setFrame(mBpkAnm0.getEndFrame());
    mBpkAnm0.setPlaySpeed(-1.0f);

    mBpkAnm1.setFrame(mBpkAnm1.getEndFrame());
    mBpkAnm1.setPlaySpeed(-1.0f);

    mBtkAnm.setFrame(mBtkAnm.getEndFrame());
    mBtkAnm.setPlaySpeed(-1.0f);

    mBrkAnm.setPlaySpeed(-1.0f);

    mTimer = 0x28;
}

/* 0000103C-000010D4       .text set_on_se__10daLStair_cFv */
void daLStair_c::set_on_se() {
    stage_stag_info_class* stage_info = dComIfGp_getStage().getStagInfo();

    if ((dStage_stagInfo_GetSaveTbl(stage_info)) == dStageType_FF1_e) {
        fopAcM_seStart(this, JA_SE_OBJ_R_STAIR_APPEAR, 0);
    }
}

/* 000010D4-00001144       .text set_off_se__10daLStair_cFv */
void daLStair_c::set_off_se() {
    fopAcM_seStart(this, JA_SE_OBJ_L_BRIDGE_OFF, 0);
}

/* 00001144-00001164       .text daLStair_Create__FPv */
static cPhs_State daLStair_Create(void* i_this) {
    return static_cast<daLStair_c*>(i_this)->_create();
}

/* 00001164-00001188       .text daLStair_Delete__FPv */
static BOOL daLStair_Delete(void* i_this) {
    return static_cast<daLStair_c*>(i_this)->_delete();
}

inline BOOL daLStair_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    J3DModelData* modelData = mpModel->getModelData();
    mBtkAnm.entry(modelData, mBtkAnm.getFrame());
    modelData = mpModel->getModelData();
    mBpkAnm0.entry(modelData, mBpkAnm0.getFrame());
    modelData = mpModel->getModelData();
    mBpkAnm1.entry(modelData, mBpkAnm1.getFrame());
    modelData = mpModel->getModelData();
    mBrkAnm.entry(modelData, mBrkAnm.getFrame());

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();

    return TRUE;
}

/* 00001188-0000128C       .text daLStair_Draw__FPv */
static BOOL daLStair_Draw(void* i_this) {
    return static_cast<daLStair_c*>(i_this)->_draw();
}

/* 0000128C-000012B0       .text daLStair_Execute__FPv */
static BOOL daLStair_Execute(void* i_this) {
    return static_cast<daLStair_c*>(i_this)->_execute();
}

/* 000012B0-000012B8       .text daLStair_IsDelete__FPv */
static BOOL daLStair_IsDelete(void*) {
    return TRUE;
}

static actor_method_class daLStairMethodTable = {
    (process_method_func)daLStair_Create,
    (process_method_func)daLStair_Delete,
    (process_method_func)daLStair_Execute,
    (process_method_func)daLStair_IsDelete,
    (process_method_func)daLStair_Draw,
};

actor_process_profile_definition g_profile_LIGHTSTAIR = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_LIGHTSTAIR_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daLStair_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_LIGHTSTAIR_e,
    /* Actor SubMtd */ &daLStairMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
