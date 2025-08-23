/**
 * d_a_item.cpp
 * Item - Field Item
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/d_item.h"
#include "d/d_item_data.h"
#include "d/actor/d_a_item.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_sea.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_controller_pad.h"

s32 daItem_c::m_timer_max = 10000;

/* 800F4BC8-800F4BD4       .text getData__12daItemBase_cFv */
const daItemBase_c_m_data* daItemBase_c::getData() {
    return &daItemBase_c::m_data;
}

/* 800F4BD4-800F4C4C       .text setArrowTrans__Fs4cXyz */
cXyz setArrowTrans(s16 yRot, cXyz offset) {
    cXyz arrowTrans = offset;
    mDoMtx_stack_c::YrotS(yRot);
    mDoMtx_stack_c::multVec(&arrowTrans, &arrowTrans);
    return arrowTrans;
}

/* 800F4C4C-800F4CD8       .text getYOffset__8daItem_cFv */
float daItem_c::getYOffset() {
    switch (m_itemNo) {
    case BOKO_BELT:
        return 0.0f;
    case dItem_SKULL_NECKLACE_e:
        return 0.0f;
    case dItem_BOKOBABA_SEED_e:
        return 0.0f;
    case dItem_GOLDEN_FEATHER_e:
        return 0.0f;
    case dItem_RED_JELLY_e:
    case dItem_GREEN_JELLY_e:
    case dItem_BLUE_JELLY_e:
        return 0.0f;
    case dItem_SMALL_KEY_e:
    case dItem_BOSS_KEY_e:
        return 0.0f;
    case dItem_SHIELD_e:
        return 23.0f;
    case dItem_SWORD_e:
        return 20.0f;
    case dItem_DROPPED_SWORD_e:
        return 10.0f;
    case dItem_HEART_PIECE_e:
    case dItem_HEART_CONTAINER_e:
        return 0.0f;
    case dItem_GREEN_RUPEE_e:
    case dItem_BLUE_RUPEE_e:
    case dItem_YELLOW_RUPEE_e:
    case dItem_RED_RUPEE_e:
    case dItem_PURPLE_RUPEE_e:
    case dItem_ORANGE_RUPEE_e:
    case dItem_SILVER_RUPEE_e:
        return 0.0f;
    case dItem_HEART_e:
        return 0.0f;
    default:
        return 0.0f;
    }
}

/* 800F4CD8-800F4E6C       .text set_mtx__8daItem_cFv */
void daItem_c::set_mtx() {
    cXyz pos = current.pos;
    csXyz rot = current.angle;
#if VERSION > VERSION_DEMO
    if (m_itemNo == dItem_HEART_CONTAINER_e) {
        rot.y = shape_angle.y;
    }
#endif
    set_mtx_base(mpModel, pos, rot);
    
    if (isArrow(m_itemNo)) {
        cXyz offset(5.0f, 0.0f, 10.0f);
        cXyz arrowTrans = setArrowTrans(current.angle.y, offset);
        
        pos += arrowTrans;
        set_mtx_base(mpModelArrow[0], pos, rot);
        
        pos += arrowTrans;
        set_mtx_base(mpModelArrow[1], pos, rot);
    }
}

/* 800F4E6C-800F4FDC       .text set_mtx_base__8daItem_cFP8J3DModel4cXyz5csXyz */
void daItem_c::set_mtx_base(J3DModel* pModel, cXyz pos, csXyz rot) {
    if (!pModel) {
        return;
    }
    
    pModel->setBaseScale(scale);
    
    mDoMtx_stack_c::transS(pos.x, pos.y + getYOffset(), pos.z);
    
    if (isRupee(m_itemNo)) {
        u8 height = dItem_data::getH(m_itemNo);
        mDoMtx_stack_c::transM(0.0f, height/2.0f, 0.0f);
    }
    
    mDoMtx_stack_c::ZXYrotM(rot.x, rot.y, rot.z + mExtraZRot);
    
    if (isRupee(m_itemNo)) {
        u8 height = dItem_data::getH(m_itemNo);
        mDoMtx_stack_c::transM(0.0f, -height/2.0f, 0.0f);
    }
    
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 800F4FDC-800F5044       .text itemGetCallBack__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void itemGetCallBack(fopAc_ac_c* item_actor, dCcD_GObjInf*, fopAc_ac_c* collided_actor, dCcD_GObjInf*) {
    daItem_c* item = (daItem_c*)item_actor;
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    if (item && item->checkPlayerGet() && collided_actor && collided_actor == link) {
        item->itemGetExecute();
    }
}

/* 800F5044-800F53EC       .text CreateInit__8daItem_cFv */
void daItem_c::CreateInit() {
    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
    mAcch.ClrWaterNone();
    mAcch.ClrRoofNone();

    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());

    mStts.Init(0, 0xFF, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.SetCoHitCallback(&itemGetCallBack);
    

    f32 height = dItem_data::getH(m_itemNo);
    f32 radius = dItem_data::getR(m_itemNo);

    if (scale.x > 1.0f) {
        height *= scale.x;
        radius *= scale.x;
    }
    mCyl.SetR(radius);
    mCyl.SetH(height);
    
    mWaitTimer = getData()->mWaitTime;
    mDisappearTimer = getData()->mDisappearTime;
    field_0x650 = fopAcM_GetSpeed(this).y;
    mItemStatus = STATUS_UNK0;
    
    mType = daItem_prm::getType(this);
    if (daItem_prm::getType(this) == daItemType_3_e || daItem_prm::getType(this) == daItemType_1_e) {
        setFlag(FLAG_UNK02);
    }
    mAction = daItem_prm::getAction(this);
    
    show();
    
    if (dItem_data::checkSpecialEffect(m_itemNo) && (m_itemNo != dItem_SMALL_KEY_e || (m_itemNo == dItem_SMALL_KEY_e && checkFlag(FLAG_UNK02)))) {
        u16 particleID = dItem_data::getSpecialEffect(m_itemNo);
        dComIfGp_particle_set(particleID, &current.pos, NULL, NULL, 0xFF, &mPtclFollowCb);
    }
    
    switch (m_itemNo) {
    case dItem_BOMB_5_e:
    case dItem_BOMB_10_e:
    case dItem_BOMB_20_e:
    case dItem_BOMB_30_e:
        mScaleTarget.setall(0.6f);
        break;
    default:
        mScaleTarget.setall(1.0f);
        break;
    }
    
    mSpawnSwitchNo = daItem_prm::getSwitchNo2(this);
    if (mSpawnSwitchNo != 0xFF && !fopAcM_isSwitch(this, mSpawnSwitchNo)) {
        hide();
        setFlag(0x02);
    }
    mCollideSwitchNo = daItem_prm::getSwitchNo(this);
    
    current.angle.z = 0;
    home.angle.z = 0;
    initAction();
    
    switch (m_itemNo) {
    case dItem_SWORD_e:
    case dItem_SHIELD_e:
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
        break;
    case dItem_DROPPED_SWORD_e:
        current.angle.x = 0x4000;
        break;
    }
    
    set_mtx();
    animPlay(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    
    if (fopAcM_SearchByName(PROC_BST)) { // Gohdan
        mpParticleEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_81E1, &current.pos);
    }
}

/* 800F53EC-800F5668       .text _daItem_create__8daItem_cFv */
cPhs_State daItem_c::_daItem_create() {
    fopAcM_SetupActor(this, daItem_c);
    
    m_itemNo = daItem_prm::getItemNo(this);
    
    if (!dItem_data::getFieldArc(m_itemNo)) {
        setLoadError();
        return cPhs_ERROR_e;
    }
    
    mItemBitNo = daItem_prm::getItemBitNo(this);
#if VERSION > VERSION_DEMO
    if (m_itemNo != dItem_BLUE_JELLY_e) // Blue Chu Jelly uses mItemBitNo as if it was a switch.
#endif
    {
        mItemBitNo &= 0x7F;
        if (fopAcM_isItem(this, mItemBitNo) && mItemBitNo != 0x7F) {
            // Already picked up, don't create the item again.
            setLoadError();
            return cPhs_ERROR_e;
        }
    }
    
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, dItem_data::getFieldArc(m_itemNo));
    if (phase_state == cPhs_COMPLEATE_e) {
#if VERSION == VERSION_DEMO
        u32 heap_size = dItem_data::getHeapSize(m_itemNo);
#else
        u32 heap_size = dItem_data::getFieldHeapSize(m_itemNo);
#endif
        if (!fopAcM_entrySolidHeap(this, CheckFieldItemCreateHeap, heap_size)) {
            return cPhs_ERROR_e;
        }
        CreateInit();
    }
    
    return phase_state;
}

/* 800F5668-800F5834       .text _daItem_execute__8daItem_cFv */
BOOL daItem_c::_daItem_execute() {
    if (mSpawnSwitchNo != 0xFF && !fopAcM_isSwitch(this, mSpawnSwitchNo)) {
        return TRUE;
    }
    if (mSpawnSwitchNo != 0xFF && fopAcM_isSwitch(this, mSpawnSwitchNo)) {
        show();
    }
    
    timeCount();
    
    eyePos = current.pos;
    eyePos.y += dItem_data::getH(m_itemNo) / 2.0f;
    attention_info.position = current.pos;
    
    switch (mItemStatus) {
    case STATUS_BRING_NEZUMI:
        execBringNezumi();
        break;
    case STATUS_UNK0:
    case STATUS_UNK1:
        if (checkActionNow()) {
            mItemStatus = STATUS_UNK1;
        } else {
            mItemStatus = STATUS_UNK0;
        }
    case STATUS_WAIT_MAIN:
        execWaitMain();
        break;
    case STATUS_INIT_NORMAL:
        execInitNormalDirection();
    case STATUS_MAIN_NORMAL:
        execMainNormalDirection();
        break;
    case STATUS_INIT_GET_DEMO:
        execInitGetDemoDirection();
        break;
    case STATUS_WAIT_GET_DEMO:
        execWaitGetDemoDirection();
        break;
    case STATUS_MAIN_GET_DEMO:
        execMainGetDemoDirection();
        break;
    case STATUS_WAIT_BOSS1:
    case STATUS_WAIT_BOSS2:
        execWaitMainFromBoss();
        break;
    }
    
    animPlay(1.0f, 1.0f, 1.0f, 1.0f, 1.0f);
    set_mtx();
    
    return TRUE;
}

/* 800F5834-800F59CC       .text mode_proc_call__8daItem_cFv */
void daItem_c::mode_proc_call() {
    static ModeFunc mode_proc[] = {
        &daItem_c::mode_wait,
        &daItem_c::mode_wait,
        &daItem_c::mode_water,
    };
    
    if (mType == daItemType_1_e) {
        itemDefaultRotateY();
    } else {
        (this->*mode_proc[mMode])();
    }
    
    if (checkFlag(FLAG_BOOMERANG)) {
        fopAc_ac_c* boomerang = (fopAc_ac_c*)fopAcM_SearchByName(PROC_BOOMERANG);
        if (boomerang) {
            current.pos = boomerang->current.pos;
        } else {
            clrFlag(FLAG_BOOMERANG);
        }
    }
    
    if (checkFlag(FLAG_HOOK)) {
        fopAc_ac_c* grappling_hook = (fopAc_ac_c*)fopAcM_SearchByName(PROC_HIMO2);
        if (grappling_hook) {
            current.pos = grappling_hook->current.pos;
        } else {
            clrFlag(FLAG_HOOK);
        }
    }
    
#if VERSION > VERSION_DEMO
    if (mType == daItemType_1_e && (fopAcM_checkHookCarryNow(this) || checkFlag(FLAG_BOOMERANG))) {
        mType = daItemType_3_e;
    }
#endif
}

/* 800F59CC-800F5AFC       .text execInitNormalDirection__8daItem_cFv */
void daItem_c::execInitNormalDirection() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz headPos = player->getHeadTopPos();
    headPos.y += 15.0f;
    current.pos = headPos;
    current.angle.z = 0;
    current.angle.x = 0;
    scale.set(mScaleTarget.x, mScaleTarget.y, mScaleTarget.z);
    mExtraZRot = 0;
    
    mSimpleExistTimer = getData()->mSimpleExistTime;
    fopAcM_SetSpeed(this, 0, getData()->mGetDemoLaunchSpeed, 0);
    fopAcM_SetGravity(this, getData()->mGetDemoGravity);
    
    show();
    
    mCyl.SetTgType(0);
    mCyl.OffCoSetBit();
    
    mPtclSmokeCb.remove();
    if (mpParticleEmitter) {
        mpParticleEmitter->becomeInvalidEmitter();
        mpParticleEmitter = NULL;
    }
    
    mItemStatus = STATUS_MAIN_NORMAL;
}

/* 800F5AFC-800F5BC8       .text execMainNormalDirection__8daItem_cFv */
void daItem_c::execMainNormalDirection() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz headPos = player->getHeadTopPos();
    headPos.y += 15.0f;
    current.pos.x = headPos.x;
    current.pos.z = headPos.z;
    fopAcM_posMoveF(this, NULL);
    if (current.pos.y < headPos.y) {
        current.pos.y = headPos.y;
    }
    
    current.angle = dComIfGp_getCamera(0)->mAngle;
    
    mSimpleExistTimer--;
    if (mSimpleExistTimer < 0) {
        fopAcM_delete(this);
    }
}

/* 800F5BC8-800F5C68       .text execInitGetDemoDirection__8daItem_cFv */
void daItem_c::execInitGetDemoDirection() {
    fopAc_ac_c* player = daPy_getPlayerActorClass();
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    
    hide();
    mPtclFollowCb.remove();
    
    if (player == link) {
        fopAcM_orderItemEvent(this);
        eventInfo.onCondition(dEvtCnd_CANGETITEM_e);
        mDemoItemBsPcId = fopAcM_createItemForTrBoxDemo(&current.pos, m_itemNo, -1, fopAcM_GetRoomNo(this));
        mItemStatus = STATUS_WAIT_GET_DEMO;
    }
}

/* 800F5C68-800F5CDC       .text execWaitGetDemoDirection__8daItem_cFv */
void daItem_c::execWaitGetDemoDirection() {
    hide();
    
    if (eventInfo.checkCommandItem()) {
        mItemStatus = STATUS_MAIN_GET_DEMO;
        if (mDemoItemBsPcId != fpcM_ERROR_PROCESS_ID_e) {
            dComIfGp_event_setItemPartnerId(mDemoItemBsPcId);
        }
    } else {
        fopAcM_orderItemEvent(this);
        eventInfo.onCondition(dEvtCnd_CANGETITEM_e);
    }
}

/* 800F5CDC-800F5D44       .text execMainGetDemoDirection__8daItem_cFv */
void daItem_c::execMainGetDemoDirection() {
    hide();
    
    if (dComIfGp_evmng_endCheck("DEFAULT_GETITEM")) {
        dComIfGp_event_reset();
        fopAcM_delete(this);
    }
}

/* 800F5D44-800F5D88       .text execBringNezumi__8daItem_cFv */
void daItem_c::execBringNezumi() {
    if (mType != daItemType_1_e) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    mode_proc_call();
}

/* 800F5D88-800F5F40       .text execWaitMain__8daItem_cFv */
void daItem_c::execWaitMain() {
    checkGetItem();
    if (mType != daItemType_1_e) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    mode_proc_call();
    
    if (!checkFlag(FLAG_UNK02)) {
        f32 scaleStepX = mScaleTarget.x / getData()->mScaleAnimSpeed;
        f32 scaleStepY = mScaleTarget.y / getData()->mScaleAnimSpeed;
        f32 scaleStepZ = mScaleTarget.z / getData()->mScaleAnimSpeed;
        cLib_chaseF(&scale.x, mScaleTarget.x, scaleStepX);
        cLib_chaseF(&scale.y, mScaleTarget.y, scaleStepY);
        cLib_chaseF(&scale.z, mScaleTarget.z, scaleStepZ);
    }
    
    if (checkItemDisappear() && mWaitTimer == 0) {
        if (mDisappearTimer == 0) {
            fopAcM_delete(this);
        }

        if (m_timer % getData()->mFlashCycleTime == 0) {
            changeDraw();
        }
    }
    
    if (!dItem_data::chkFlag(m_itemNo, 2)) {
        if (mCollideSwitchNo == 0xFF || (mCollideSwitchNo != 0xFF && fopAcM_isSwitch(this, mCollideSwitchNo))) {
            mCyl.SetC(current.pos);
            dComIfG_Ccsp()->Set(&mCyl);
        }
    }
}

/* 800F5F40-800F5FC0       .text execWaitMainFromBoss__8daItem_cFv */
void daItem_c::execWaitMainFromBoss() {
    checkGetItem();
    if (mType != daItemType_1_e) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    mode_proc_call();
    
    if (mItemStatus != STATUS_WAIT_BOSS2) {
        scaleAnimFromBossItem();
    }
    
    mCyl.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 800F5FC0-800F60C0       .text scaleAnimFromBossItem__8daItem_cFv */
void daItem_c::scaleAnimFromBossItem() {
    if (m_get_timer < 30) {
        scale.x = cM_ssin(m_timer*0x2000 - 0x4000)*2.0f / m_timer+1.0f;
        if (scale.x < 0.0f) {
            scale.x = 0.0f;
        }
        scale.y = scale.x;
        scale.z = scale.x;
    } else {
        if (m_get_timer == 30) {
            fopAcM_seStart(this, JA_SE_CM_BOSS_HEART_APPEAR, 0);
        }
        scale.setall(1.0f);
    }
}

/* 800F60C0-800F6110       .text _daItem_draw__8daItem_cFv */
BOOL daItem_c::_daItem_draw() {
    if (chkDraw()) {
        return DrawBase();
    }
    return TRUE;
}

/* 800F6110-800F61C8       .text setTevStr__8daItem_cFv */
void daItem_c::setTevStr() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    
    tevStr.mColorC0.r = 0x96;
    tevStr.mColorC0.g = 0x96;
    tevStr.mColorC0.b = 0x96;
    tevStr.mColorK0.r = 0xFF;
    tevStr.mColorK0.g = 0xFF;
    tevStr.mColorK0.b = 0xFF;
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    
    for (int i = 0; i < 2; i++) {
        if (!mpModelArrow[i]) {
            continue;
        }
        g_env_light.setLightTevColorType(mpModelArrow[i], &tevStr);
    }
}

/* 800F61C8-800F6268       .text _daItem_delete__8daItem_cFv */
BOOL daItem_c::_daItem_delete() {
    mPtclRippleCb.remove();
    mPtclFollowCb.remove();
    mPtclSmokeCb.remove();
    if (mpParticleEmitter) {
        mpParticleEmitter->becomeInvalidEmitter();
        mpParticleEmitter = NULL;
    }
    
    DeleteBase(dItem_data::getFieldArc(m_itemNo));
    
    return TRUE;
}

/* 800F6268-800F6434       .text Reflect__FR4cXyzP4cXyzff */
bool Reflect(cXyz& surfVec, cXyz* moveVec, f32 param_2, f32 xzMult) {
    // Reflects a vector off the normal of a surface.
    cXyz reflectVec;
    cXyz moveNorm;
    cXyz surfNorm;
    f32 mag = moveVec->abs();
    moveNorm = moveVec->normalize();
    surfNorm = surfVec.normalize();
    moveNorm = moveNorm * -1.0f;
    f32 dot = 2.0f*surfNorm.getDotProduct(moveNorm);
    bool hitFront = true;
    if (dot < 0.0f) {
        hitFront = false;
    }
    reflectVec = (surfNorm * dot) - moveNorm;
    reflectVec *= mag;
    moveVec->x = reflectVec.x * xzMult;
    moveVec->y = reflectVec.y;
    moveVec->z = reflectVec.z * xzMult;
    return hitFront;
}

/* 800F6434-800F6D24       .text itemGetExecute__8daItem_cFv */
void daItem_c::itemGetExecute() {
    if (mItemStatus == STATUS_INIT_NORMAL) {
        return;
    }
    mItemStatus = STATUS_INIT_NORMAL;
    
    switch (m_itemNo) {
    case dItem_HEART_e:
        mDoAud_seStart(JA_SE_HEART_PIECE);
        execItemGet(m_itemNo);
        break;
    case dItem_GREEN_RUPEE_e:
        mDoAud_seStart(JA_SE_LUPY_GET);
        execItemGet(m_itemNo);
        break;
    case dItem_BLUE_RUPEE_e:
        mDoAud_seStart(JA_SE_BLUE_LUPY_GET);
        execItemGet(m_itemNo);
        break;
    case dItem_YELLOW_RUPEE_e:
        mDoAud_seStart(JA_SE_BLUE_LUPY_GET);
        execItemGet(m_itemNo);
        break;
    case dItem_RED_RUPEE_e:
        mDoAud_seStart(JA_SE_RED_LUPY_GET);
        execItemGet(m_itemNo);
        break;
    case dItem_PURPLE_RUPEE_e:
        mDoAud_seStart(JA_SE_RED_LUPY_GET);
        execItemGet(m_itemNo);
        break;
    case dItem_ORANGE_RUPEE_e:
        mDoAud_seStart(JA_SE_RED_LUPY_GET);
        execItemGet(m_itemNo);
        break;
    case dItem_SILVER_RUPEE_e:
        mDoAud_seStart(JA_SE_RED_LUPY_GET);
        execItemGet(m_itemNo);
        break;
    case dItem_HEART_PIECE_e:
        mDoAud_seStart(JA_SE_HEART_PIECE);
        mItemStatus = STATUS_INIT_GET_DEMO;
        break;
    case dItem_HEART_CONTAINER_e:
        mDoAud_seStart(JA_SE_HEART_PIECE);
        mItemStatus = STATUS_INIT_GET_DEMO;
        break;
    case dItem_SMALL_MAGIC_e:
        mDoAud_seStart(JA_SE_MAGIC_POT_GET_S);
        execItemGet(m_itemNo);
        break;
    case dItem_LARGE_MAGIC_e:
        mDoAud_seStart(JA_SE_MAGIC_POT_GET_L);
        execItemGet(m_itemNo);
        break;
    case dItem_BOMB_5_e:
    case dItem_BOMB_10_e:
    case dItem_BOMB_20_e:
    case dItem_BOMB_30_e:
    case dItem_ARROW_10_e:
    case dItem_ARROW_20_e:
    case dItem_ARROW_30_e:
        mDoAud_seStart(JA_SE_CONSUMP_ITEM_GET);
        execItemGet(m_itemNo);
        break;
    case dItem_SMALL_KEY_e:
        mItemStatus = STATUS_INIT_GET_DEMO;
        break;
    case dItem_TRIPLE_HEART_e:
        mDoAud_seStart(JA_SE_HEART_PIECE);
        execItemGet(m_itemNo);
        break;
    case dItem_JOY_PENDANT_e:
        mDoAud_seStart(JA_SE_SPOILS_GET);
        if (!dComIfGs_isGetItemBeast(7)) {
            mItemStatus = STATUS_INIT_GET_DEMO;
            dComIfGs_onGetItemBeast(7);
        } else {
            execItemGet(m_itemNo);
        }
        break;
    case dItem_DEKU_LEAF_e:
        mItemStatus = STATUS_INIT_GET_DEMO;
        break;
    case dItem_SWORD_e: {
        daItem_c* item = (daItem_c*)fopAcM_SearchByName(PROC_ITEM);
        if (item && item->m_itemNo == dItem_SHIELD_e) {
            item->itemGetExecute();
        }
        mItemStatus = STATUS_INIT_GET_DEMO;
        break;
    }
    case dItem_SHIELD_e: {
        daItem_c* item = (daItem_c*)fopAcM_SearchByName(PROC_ITEM);
        if (item && item->m_itemNo == dItem_SWORD_e) {
            item->itemGetExecute();
        }
        mItemStatus = STATUS_INIT_GET_DEMO;
        break;
    }
    case dItem_DROPPED_SWORD_e:
        mItemStatus = STATUS_INIT_GET_DEMO;
        break;
    case dItem_SKULL_NECKLACE_e:
        mDoAud_seStart(JA_SE_SPOILS_GET);
        if (!dComIfGs_isGetItemBeast(0)) {
            mItemStatus = STATUS_INIT_GET_DEMO;
            dComIfGs_onGetItemBeast(0);
        } else {
            execItemGet(m_itemNo);
        }
        break;
    case dItem_BOKOBABA_SEED_e:
        mDoAud_seStart(JA_SE_SPOILS_GET);
        if (!dComIfGs_isGetItemBeast(1)) {
            mItemStatus = STATUS_INIT_GET_DEMO;
            dComIfGs_onGetItemBeast(1);
        } else {
            execItemGet(m_itemNo);
        }
        break;
    case dItem_GOLDEN_FEATHER_e:
        mDoAud_seStart(JA_SE_SPOILS_GET);
        if (!dComIfGs_isGetItemBeast(2)) {
            mItemStatus = STATUS_INIT_GET_DEMO;
            dComIfGs_onGetItemBeast(2);
        } else {
            execItemGet(m_itemNo);
        }
        break;
    case BOKO_BELT:
        mDoAud_seStart(JA_SE_SPOILS_GET);
        if (!dComIfGs_isGetItemBeast(3)) {
            mItemStatus = STATUS_INIT_GET_DEMO;
            dComIfGs_onGetItemBeast(3);
        } else {
            execItemGet(m_itemNo);
        }
        break;
    case dItem_RED_JELLY_e:
        mDoAud_seStart(JA_SE_SPOILS_GET);
        if (!dComIfGs_isGetItemBeast(4)) {
            mItemStatus = STATUS_INIT_GET_DEMO;
            dComIfGs_onGetItemBeast(4);
        } else {
            execItemGet(m_itemNo);
        }
        break;
    case dItem_GREEN_JELLY_e:
        mDoAud_seStart(JA_SE_SPOILS_GET);
        if (!dComIfGs_isGetItemBeast(5)) {
            mItemStatus = STATUS_INIT_GET_DEMO;
            dComIfGs_onGetItemBeast(5);
        } else {
            execItemGet(m_itemNo);
        }
        break;
    case dItem_BLUE_JELLY_e:
        mDoAud_seStart(JA_SE_SPOILS_GET);
        if (!dComIfGs_isGetItemBeast(6)) {
            mItemStatus = STATUS_INIT_GET_DEMO;
            dComIfGs_onGetItemBeast(6);
        } else {
            execItemGet(m_itemNo);
        }
        break;
    case dItem_BIRD_BAIT_5_e:
        mDoAud_seStart(JA_SE_ESA_GET);
        if (!dComIfGs_isGetItemBait(0)) {
            mItemStatus = STATUS_INIT_GET_DEMO;
            dComIfGs_onGetItemBait(0);
        } else {
            execItemGet(m_itemNo);
        }
        break;
    case dItem_HYOI_PEAR_e:
        mDoAud_seStart(JA_SE_ESA_GET);
        if (!dComIfGs_isGetItemBait(1)) {
            mItemStatus = STATUS_INIT_GET_DEMO;
            dComIfGs_onGetItemBait(1);
        } else {
            execItemGet(m_itemNo);
        }
        break;
    }
    
    fopAcM_onItemForIb(mItemBitNo, m_itemNo, current.roomNo);
    
    clrFlag(FLAG_UNK04);
    
#if VERSION > VERSION_DEMO
    mCyl.SetTgType(0);
    mCyl.OffCoSetBit();
    mCyl.ClrTgHit();
    mCyl.ClrCoHit();
#endif
}

/* 800F6D24-800F6D78       .text itemDefaultRotateY__8daItem_cFv */
void daItem_c::itemDefaultRotateY() {
    // Rotates at a fixed speed.
    s16 rotationSpeed = 0xFFFF / getData()->mRotateYSpeed;
    fopAcM_addAngleY(this, current.angle.y + rotationSpeed, rotationSpeed);
}

/* 800F6D78-800F6E54       .text checkItemDisappear__8daItem_cFv */
BOOL daItem_c::checkItemDisappear() {
    BOOL disappearing = TRUE;
    if (mItemStatus == STATUS_BRING_NEZUMI) {
        disappearing = FALSE;
        show();
    }
    if (checkFlag(FLAG_UNK02)) {
        disappearing = FALSE;
    }
    if (checkFlag(FLAG_UNK10)) {
        disappearing = FALSE;
    }
    if (dItem_data::chkFlag(m_itemNo, 0x01)) {
        disappearing = FALSE;
    }
    if (dComIfGp_event_runCheck()) {
        disappearing = FALSE;
    }
    if (mItemStatus == STATUS_UNK4) {
        disappearing = FALSE;
    }
    if (checkFlag(FLAG_BOOMERANG) || checkFlag(FLAG_HOOK) || fopAcM_CheckStatus(this, fopAcStts_HOOK_CARRY_e)) {
        disappearing = FALSE;
        show();
    }
    return disappearing;
}

/* 800F6E54-800F6E74       .text setItemTimer__8daItem_cFi */
void daItem_c::setItemTimer(int timer) {
    if (timer == -1) {
        setFlag(FLAG_UNK10);
        return;
    }
    mWaitTimer = timer;
}

/* 800F6E74-800F6EC8       .text checkPlayerGet__8daItem_cFv */
BOOL daItem_c::checkPlayerGet() {
    if (m_get_timer < getData()->mNoGetTime) {
        return FALSE;
    }
    if (mItemStatus == STATUS_BRING_NEZUMI) {
        return FALSE;
    }
    return TRUE;
}

/* 800F6EC8-800F7028       .text itemActionForRupee__8daItem_cFv */
BOOL daItem_c::itemActionForRupee() {
    mAcch.CrrPos(*dComIfG_Bgsp());
    checkWall();
    
    if (mAcch.ChkGroundLanding()) {
        f32 temp2 = field_0x650 * getData()->mGroundReflect;
        if (temp2 > gravity - 0.5f) {
            fopAcM_SetSpeedF(this, 0.0f);
        } else {
            fopAcM_GetSpeed(this).set(0.0f, -temp2, 0.0f);
        }
        
        mOnGroundTimer++;
        if (mOnGroundTimer >= 2) {
            clrFlag(FLAG_UNK04);
        }
        
        set_bound_se();
    } else if (mAcch.ChkGroundHit()) {
        itemDefaultRotateY();
        fopAcM_SetSpeedF(this, 0.0f);
        clrFlag(FLAG_UNK04);
        mOnGroundTimer = 1;
    }
    
    if (fopAcM_GetSpeed(this).y != 0.0f) {
        field_0x650 = fopAcM_GetSpeed(this).y;
    }
    
    mRotateSpeed = getData()->mRotateXSpeed;
    
    if (mOnGroundTimer == 0) {
        mTargetAngleX = current.angle.x + mRotateSpeed;
    } else {
        mTargetAngleX = 0;
    }
    
    if (!checkFlag(FLAG_UNK02)) {
        cLib_chaseAngleS(&current.angle.x, mTargetAngleX, mRotateSpeed);
    }
    
    return TRUE;
}

/* 800F7028-800F713C       .text itemActionForHeart__8daItem_cFv */
BOOL daItem_c::itemActionForHeart() {
    f32 origSpeedY = fopAcM_GetSpeed(this).y;
    if (origSpeedY < 0.0f) {
        fopAcM_SetGravity(this, 0.0f);
        fopAcM_SetSpeed(this, 0.0f, getData()->mHeartFallSpeed, 0.0f);
    }
    
    mAcch.CrrPos(*dComIfG_Bgsp());
    
    if (mAcch.ChkGroundLanding() || mAcch.ChkGroundHit()) {
        clrFlag(FLAG_UNK04);
        mExtraZRot = 0;
        fopAcM_SetSpeed(this, 0.0f, -1.0f, 0.0f);
        fopAcM_SetSpeedF(this, 0.0f);
        itemDefaultRotateY();
    } else if (origSpeedY < 0.0f) {
        origSpeedY = getData()->mHeartAmplitude;
        fopAcM_SetSpeedF(this, origSpeedY * cM_ssin(m_timer * getData()->mHeartFallCycleTime));
    }
    
    return TRUE;
}

/* 800F713C-800F72A4       .text itemActionForKey__8daItem_cFv */
BOOL daItem_c::itemActionForKey() {
    mAcch.CrrPos(*dComIfG_Bgsp());
    checkWall();
    
    if (mAcch.ChkGroundLanding()) {
        f32 temp2 = field_0x650 * getData()->mGroundReflect;
        if (temp2 > gravity - 0.5f) {
            speedF = 0.0f;
            current.angle.x = 0x4000;
            mTargetAngleX = current.angle.x;
            mRotateSpeed = 0;
        } else {
            speed.set(0.0f, -temp2, 0.0f);
        }
        
        mOnGroundTimer++;
        if (mOnGroundTimer >= 2) {
            clrFlag(FLAG_UNK04);
        }
    } else if (mAcch.ChkGroundHit()) {
        mOnGroundTimer = 1;
        mTargetAngleX = 0;
        current.angle.x = 0;
        clrFlag(FLAG_UNK04);
        itemDefaultRotateY();
    }
    
    if (fopAcM_GetSpeed(this).y != 0.0f) {
        field_0x650 = fopAcM_GetSpeed(this).y;
    }
    
    mRotateSpeed = getData()->mRotateXSpeed;
    
    if (mOnGroundTimer == 0) {
        mTargetAngleX = current.angle.x + mRotateSpeed;
    } else {
        mTargetAngleX = 0;
    }
    
    cLib_chaseAngleS(&current.angle.x, mTargetAngleX, mRotateSpeed);
    
    return TRUE;
}

/* 800F72A4-800F73A4       .text itemActionForEmono__8daItem_cFv */
BOOL daItem_c::itemActionForEmono() {
    mAcch.CrrPos(*dComIfG_Bgsp());
    
    if (mAcch.ChkGroundLanding()) {
        f32 temp2 = field_0x650 * getData()->mGroundReflect;
        if (temp2 > gravity - 0.5f) {
            speedF = 0.0f;
        } else {
            speed.set(0.0f, -temp2, 0.0f);
        }
        
        set_bound_se();
    } else if (mAcch.ChkGroundHit()) {
        s16 rotationSpeed = 0xFFFF / getData()->mRotateYSpeed;
        rotationSpeed = rotationSpeed / 2;
        fopAcM_addAngleY(this, current.angle.y + rotationSpeed, rotationSpeed);
        speedF = 0.0f;
    }
    
    if (fopAcM_GetSpeed(this).y != 0.0f) {
        field_0x650 = fopAcM_GetSpeed(this).y;
    }
    
    return TRUE;
}

/* 800F73A4-800F7898       .text itemActionForSword__8daItem_cFv */
BOOL daItem_c::itemActionForSword() {
    /* Nonmatching - regalloc */
    mAcch.CrrPos(*dComIfG_Bgsp());
    
    bool isQuake = dComIfGp_getDetect().chk_quake(&current.pos);
    if (isQuake && !checkFlag(FLAG_QUAKE) && mAcch.ChkGroundHit()) {
        fopAcM_SetSpeed(this, 0.0f, 21.0f, 0.0f);
        fopAcM_SetGravity(this, -3.5f);
    }
    
    if (mAcch.ChkGroundLanding()) {
        f32 temp = field_0x650 * 0.9f;
        fopAcM_SetSpeed(this, 0.0f, -temp, 0.0f);
        
        if (m_itemNo == dItem_SWORD_e) {
            if (m_get_timer > 15) {
                fopAcM_seStart(this, JA_SE_OBJ_LNK_SWORD_FALL, 0);
            }
        } else if (m_itemNo == dItem_SHIELD_e) {
            if (m_get_timer > 15) {
                fopAcM_seStart(this, JA_SE_OBJ_LNK_SHIELD_FALL, 0);
            }
        }
    }
    
    dBgS_ObjGndChk gndChk;
    cXyz bottomPos(0.0f, 0.0f, 0.0f);
    cXyz topPos(0.0f, 50.0f, 0.0f);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(current.angle);
    mDoMtx_stack_c::multVec(&bottomPos, &bottomPos);
    mDoMtx_stack_c::multVec(&topPos, &topPos);
    gndChk.SetPos(&bottomPos);
    f32 groundY = dComIfG_Bgsp()->GroundCross(&gndChk);
    f32 temp3 = groundY - bottomPos.y;
    gndChk.SetPos(&topPos);
    groundY = dComIfG_Bgsp()->GroundCross(&gndChk);
    f32 temp4 = groundY - topPos.y;
    
    if (field_0x666 == 1) {
        field_0x660 = 0x2000;
    }
    
    if (temp3 > 0.0f || temp4 > 0.0f) {
        if (temp3 > 0.0f) {
            field_0x660 = -0.8f * field_0x660;
        } else if (temp4 > 0.0f) {
            field_0x660 = -0.8f * field_0x660;
        }
        field_0x666++;
    }
    
    if (field_0x660 == 0) {
        field_0x666 = 0;
    } else {
        cLib_addCalcAngleS2(&current.angle.x, field_0x660 + 0x4000, 10, 0x800);
    }
    
    if (isQuake) {
        setFlag(FLAG_QUAKE);
    } else {
        clrFlag(FLAG_QUAKE);
    }
    
    return TRUE;
}

/* 800F7898-800F7AF0       .text itemActionForArrow__8daItem_cFv */
BOOL daItem_c::itemActionForArrow() {
    mAcch.CrrPos(*dComIfG_Bgsp());
    
    if (mOnGroundTimer == 0 && mpParticleEmitter && fopAcM_SearchByName(PROC_BST)) { // Gohdan
        mpParticleEmitter->setGlobalTranslation(current.pos);
    }
    
    if (mAcch.ChkGroundLanding()) {
        f32 temp_f3 = field_0x650 * getData()->mGroundReflect;
        if (temp_f3 > gravity - 0.5f) {
            speedF = 0.0f;
        } else {
            speed.set(0.0f, -temp_f3, 0.0f);
            speedF *= 0.5f;
        }
        
        mOnGroundTimer++;
        
        if (mOnGroundTimer == 1 && fopAcM_SearchByName(PROC_BST)) { // Gohdan
            JPABaseEmitter* emitter = dComIfGp_particle_set(dPa_name::ID_SCENE_A1E2, &current.pos, NULL, NULL, 0xFF, &mPtclSmokeCb, fopAcM_GetRoomNo(this));
            if (emitter) {
                emitter->setMaxFrame(1);
            }
        }
        
        if (mpParticleEmitter) {
            mpParticleEmitter->becomeInvalidEmitter();
            mpParticleEmitter = NULL;
        }
        
        set_bound_se();
    } else if (mAcch.ChkGroundHit()) {
        speedF = 0.0f;
        
#if VERSION > VERSION_DEMO
        if (m_itemNo != dItem_HEART_CONTAINER_e)
#endif
        {
            itemDefaultRotateY();
        }
    }
    
#if VERSION > VERSION_DEMO
    if (m_itemNo == dItem_HEART_CONTAINER_e) {
        if (mOnGroundTimer != 0) {
            getData();
            s16 rotationSpeed = 0xFFFF / getData()->mRotateYSpeed;
            cLib_addCalcAngleS(&mRotateSpeed, rotationSpeed, 10, 0x400, 0x100);
        }
        
        cLib_chaseAngleS(&shape_angle.y, shape_angle.y + mRotateSpeed, mRotateSpeed);
    }
#endif
    
    if (fopAcM_GetSpeed(this).y != 0.0f) {
        field_0x650 = fopAcM_GetSpeed(this).y;
    }
    
    return TRUE;
}

/* 800F7AF0-800F7BF8       .text checkWall__8daItem_cFv */
void daItem_c::checkWall() {
    // If the item hit a wall, bounce off.
    if (!mAcch.ChkWallHit()) {
        return;
    }
    
    cM3dGPla* wallPlane = dComIfG_Bgsp()->GetTriPla(mAcchCir);
    cXyz wallNorm = *wallPlane->GetNP();
    
    cXyz vel;
    vel.x = speedF * cM_ssin(current.angle.y);
    vel.y = speed.y;
    vel.z = speedF * cM_scos(current.angle.y);
    
    if (!cM3d_IsZero(vel.x) || !cM3d_IsZero(vel.z)) {
        Reflect(wallNorm, &vel, 1.0f, 1.0f);
        if (!cM3d_IsZero(vel.x)) {
            current.angle.y = cM_atan2s(vel.x, vel.z);
        }
    }
}

/* 800F7BF8-800F7DDC       .text set_bound_se__8daItem_cFv */
void daItem_c::set_bound_se() {
    if (m_get_timer < 10) {
        return;
    }
    
    u32 temp = std::fabsf(field_0x650) * 2.0f;
    if (temp > 100) {
        temp = 100;
    }
    
    switch (m_itemNo) {
    case dItem_GREEN_RUPEE_e:
    case dItem_BLUE_RUPEE_e:
    case dItem_YELLOW_RUPEE_e:
    case dItem_RED_RUPEE_e:
    case dItem_PURPLE_RUPEE_e:
    case dItem_ORANGE_RUPEE_e:
        fopAcM_seStart(this, JA_SE_OBJ_LUPY_BOUND, temp);
        break;
    case dItem_SMALL_MAGIC_e:
    case dItem_LARGE_MAGIC_e:
        fopAcM_seStart(this, JA_SE_OBJ_M_POT_BOUND, temp);
        break;
    case dItem_ARROW_10_e:
    case dItem_ARROW_20_e:
    case dItem_ARROW_30_e:
    case dItem_MAGIC_ARROW_e:
    case dItem_LIGHT_ARROW_e:
        fopAcM_seStart(this, JA_SE_CM_BST_ARROW_BOUND, temp);
        break;
    case dItem_HEART_PIECE_e:
    case dItem_HEART_CONTAINER_e:
        fopAcM_seStart(this, JA_SE_CM_BST_HEART_BOUND, temp);
        break;
    case dItem_BOMB_5_e:
    case dItem_BOMB_10_e:
    case dItem_BOMB_20_e:
    case dItem_BOMB_30_e:
        fopAcM_seStart(this, JA_SE_CM_BST_BOMB_BOUND, temp);
        break;
    }
}

/* 800F7DDC-800F7E6C       .text checkGetItem__8daItem_cFv */
BOOL daItem_c::checkGetItem() {
    if (!checkPlayerGet()) {
        return FALSE;
    }
    
    if (mCyl.ChkTgHit()) {
        cCcD_Obj* hitObj = mCyl.GetTgHitObj();
        if (hitObj) {
            if (hitObj->ChkAtType(AT_TYPE_SWORD)) {
                itemGetExecute();
                return TRUE;
            } else if (hitObj->ChkAtType(AT_TYPE_BOOMERANG)) {
                setFlag(FLAG_BOOMERANG);
            }
        }
    }
    
    return FALSE;
}

/* 800F7E6C-800F7F0C       .text timeCount__8daItem_cFv */
BOOL daItem_c::timeCount() {
    m_timer++;
    if (m_get_timer < m_timer_max) {
        m_get_timer++;
    }
    
    if (checkPlayerGet() && !dComIfGp_event_runCheck()) {
        if (mWaitTimer > 0) {
            mWaitTimer--;
        } else if (mDisappearTimer > 0) {
            mDisappearTimer--;
        }
    }
    
    return TRUE;
}

/* 800F7F0C-800F7F50       .text mode_wait_init__8daItem_cFv */
void daItem_c::mode_wait_init() {
    mMode = MODE_WAIT;
    fopAcM_SetGravity(this, getData()->mGravity);
    mPtclRippleCb.remove();
}

/* 800F7F50-800F80CC       .text mode_water_init__8daItem_cFv */
void daItem_c::mode_water_init() {
    mMode = MODE_WATER;
    
    if (daSea_ChkArea(current.pos.x, current.pos.z)) {
        f32 seaH = daSea_calcWave(current.pos.x, current.pos.z);
        if (seaH > current.pos.y) {
            current.pos.y = seaH;
        }
    } else {
        if (!mAcch.ChkWaterHit() || mAcch.m_wtr.GetHeight() < current.pos.y) {
            mode_wait_init();
        }
        current.pos.y = mAcch.m_wtr.GetHeight();
    }
    
    fopAcM_SetSpeed(this, 0.0f, 0.0f, 0.0f);
    fopAcM_SetSpeedF(this, 0.0f);
    current.angle.x = current.angle.z = 0;
    mExtraZRot = 0;
    mRotateSpeed = 0;
    clrFlag(FLAG_UNK04);
    scale.set(mScaleTarget.x, mScaleTarget.y, mScaleTarget.z);
    
    cXyz particleScale;
    f32 temp3 = (f32)dItem_data::getShadowSize(m_itemNo) / dItem_data::getShadowSize(dItem_GREEN_RUPEE_e);
    temp3 *= scale.x;
    particleScale.setall(temp3);
    
    dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &current.pos, NULL, &particleScale, 0xFF, &mPtclRippleCb);
    mPtclRippleCb.mRate = 0.0f;
}

/* 800F80CC-800F844C       .text mode_wait__8daItem_cFv */
void daItem_c::mode_wait() {
    if (checkFlag(FLAG_UNK04) && dItem_data::checkAppearEffect(m_itemNo)) {
        u16 appearEffect = dItem_data::getAppearEffect(m_itemNo);
        dComIfGp_particle_setSimple(appearEffect, &current.pos);
    }
    
    switch (m_itemNo) {
    case dItem_HEART_e:
    case dItem_TRIPLE_HEART_e:
        itemActionForHeart();
        break;
    case dItem_HEART_PIECE_e:
    case dItem_HEART_CONTAINER_e:
    case dItem_BOMB_5_e:
    case dItem_BOMB_10_e:
    case dItem_BOMB_20_e:
    case dItem_BOMB_30_e:
    case dItem_ARROW_10_e:
    case dItem_ARROW_20_e:
    case dItem_ARROW_30_e:
    case dItem_MAGIC_ARROW_e:
    case dItem_LIGHT_ARROW_e:
        itemActionForArrow();
        break;
    case dItem_SMALL_KEY_e:
        itemActionForKey();
        break;
    case dItem_SMALL_MAGIC_e:
    case dItem_LARGE_MAGIC_e:
#if VERSION > VERSION_DEMO
    case dItem_JOY_PENDANT_e:
#endif
    case dItem_SKULL_NECKLACE_e:
    case dItem_BOKOBABA_SEED_e:
    case dItem_GOLDEN_FEATHER_e:
    case BOKO_BELT:
    case dItem_RED_JELLY_e:
    case dItem_GREEN_JELLY_e:
    case dItem_BLUE_JELLY_e:
        itemActionForEmono();
        break;
    case dItem_SWORD_e:
    case dItem_SHIELD_e:
    case dItem_DROPPED_SWORD_e:
        itemActionForSword();
        break;
    default:
        itemActionForRupee();
        break;
    }
    
    if ((mAcch.ChkWaterHit() && mAcch.m_wtr.GetHeight() > current.pos.y) ||
        (daSea_ChkArea(current.pos.x, current.pos.z) && daSea_calcWave(current.pos.x, current.pos.z) > current.pos.y))
    {
        mode_water_init();
    }
    
    dBgS_ObjGndChk_Yogan lavaChk;
    cXyz temp;
    temp.set(old.pos.x, old.pos.y, old.pos.z);
    lavaChk.SetPos(&temp);
    f32 lavaY = dComIfG_Bgsp()->GroundCross(&lavaChk);
    if (lavaY != -G_CM3D_F_INF && lavaY > current.pos.y) {
        fopAcM_delete(this);
    }
}

/* 800F844C-800F8528       .text mode_water__8daItem_cFv */
void daItem_c::mode_water() {
    mAcch.CrrPos(*dComIfG_Bgsp());
    
    if (daSea_ChkArea(current.pos.x, current.pos.z)) {
        f32 seaH = daSea_calcWave(current.pos.x, current.pos.z);
        if (seaH >= current.pos.y) {
            current.pos.y = seaH;
        } else {
            mode_wait_init();
        }
    } else if (!mAcch.ChkWaterHit() || mAcch.m_wtr.GetHeight() < current.pos.y) {
        mode_wait_init();
    } else {
        current.pos.y = mAcch.m_wtr.GetHeight();
    }
    
    s16 rotationSpeed = 0xFFFF / daItemBase_c::m_data.mRotateYSpeed;
    fopAcM_addAngleY(this, current.angle.y + rotationSpeed, rotationSpeed);
}

/* 800F8528-800F8950       .text initAction__8daItem_cFv */
BOOL daItem_c::initAction() {
    if (checkFlag(FLAG_UNK02)) {
        scale.set(mScaleTarget.x, mScaleTarget.y, mScaleTarget.z);
        
        switch (mAction) {
        case daItemAct_4_e: {
            current.angle.y = cM_rndF((f32)0xFFFF);
            f32 temp = getData()->field_0x2C + cM_rndF(5.0f);
            speedF = cM_rndF(getData()->field_0x30);
            speed.set(0.0f, temp, 0.0f);
            break;
        }
        case daItemAct_BOSS_DISAPPEAR_e:
            speed.setall(0.0f);
            speedF = 0.0f;
            scale.setall(0.0f);
            mItemStatus = STATUS_WAIT_BOSS1;
            fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
#if VERSION > VERSION_DEMO
            mRotateSpeed = 0x4A8;
#endif
            break;
        case daItemAct_BOSS_e:
            scale.setall(1.0f);
            mItemStatus = STATUS_WAIT_BOSS2;
            fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
#if VERSION > VERSION_DEMO
            mRotateSpeed = 0x4A8;
#endif
            break;
        }
        
        fopAcM_SetGravity(this, getData()->mGravity);
        clrFlag(FLAG_UNK04);
        mMode = MODE_WAIT;
        
        return TRUE;
    }
    
    // Bug: Usage of uninitialized variable y_speed (register f31) in some cases.
    // In practice only daItem_c::CreateInit calls daItem_c::initAction, which means y_speed will
    // be set to the item's collision height if the action is 0, 5, or 0xA.
    f32 y_speed;
    switch (mAction) {
    case daItemAct_1_e:
        y_speed = getData()->mLaunchSpeed + cM_rndFX(5.0f);
        speedF = getData()->mSpeedH / 10.0f;
        if (g_mDoCPd_cpadInfo[0].mMainStickValue) {
            speedF = getData()->mSpeedH;
        }
        current.angle.y = cM_rndF((f32)0xFFFF);
        break;
    case daItemAct_3_e:
        y_speed = 25.0f;
        current.angle.y = cM_rndF((f32)0xFFFF);
        speedF = getData()->mVelocityScale;
        break;
    case daItemAct_7_e:
        speedF = getData()->mVelocityScale * 1.5f;
        current.angle.y = cM_rndF((f32)0xFFFF);
        y_speed = getData()->mLaunchSpeed + cM_rndFX(5.0f);
        break;
    case daItemAct_2_e:
    case daItemAct_4_e:
    case daItemAct_9_e:
        speedF = 0.0f;
        current.angle.y = cM_rndF((f32)0xFFFF);
        y_speed = getData()->mLaunchSpeed + cM_rndFX(5.0f);
        break;
    case daItemAct_8_e:
        current.angle.y = cM_rndF((f32)0xFFFF);
        y_speed = getData()->field_0x44 + cM_rndFX(5.0f);
        speedF = getData()->mVelocityScale;
        break;
    case daItemAct_A_e:
        gravity = getData()->mGravity;
        scale.setall(0.0f);
        mMode = MODE_WAIT;
        break;
    case daItemAct_B_e:
        current.angle.y = cM_rndF((f32)0xFFFF);
        y_speed = 0.0f;
        speedF = 0.0f;
        break;
    case daItemAct_6_e:
        y_speed = getData()->mLaunchSpeed + cM_rndFX(5.0f);
        break;
    case daItemAct_0_e:
    case daItemAct_BOSS_DISAPPEAR_e:
        break;
    }
    
    mExtraZRot = 0;
    
    if (isHeart(m_itemNo)) {
        speedF = 2.0f * speedF;
        mExtraZRot = cM_rndFX(getData()->mHeartTilt);
    }

    fopAcM_SetGravity(this, getData()->mGravity);
    fopAcM_SetSpeed(this, 0.0f, y_speed, 0.0f);
    // This line setting speedF to itself gets optimized out and produces no code, but affects regalloc.
    fopAcM_SetSpeedF(this, speedF);
    scale.setall(0.0f);
    
    mMode = MODE_WAIT;
    
    setFlag(FLAG_UNK04);
    
    return TRUE;
}

/* 800F8950-800F8970       .text daItem_Draw__FP8daItem_c */
static BOOL daItem_Draw(daItem_c* i_this) {
    return i_this->_daItem_draw();
}

/* 800F8970-800F8990       .text daItem_Execute__FP8daItem_c */
static BOOL daItem_Execute(daItem_c* i_this) {
    return i_this->_daItem_execute();
}

/* 800F8990-800F89B0       .text daItem_IsDelete__FP8daItem_c */
static BOOL daItem_IsDelete(daItem_c* i_this) {
    return i_this->_daItem_isdelete();
}

/* 800F89B0-800F89D0       .text daItem_Delete__FP8daItem_c */
static BOOL daItem_Delete(daItem_c* i_this) {
    return i_this->_daItem_delete();
}

/* 800F89D0-800F89F0       .text daItem_Create__FP10fopAc_ac_c */
static cPhs_State daItem_Create(fopAc_ac_c* i_this) {
    return ((daItem_c*)i_this)->_daItem_create();
}

/* 800F89F0-800F89F8       .text _daItem_isdelete__8daItem_cFv */
BOOL daItem_c::_daItem_isdelete() {
    return TRUE;
}

dCcD_SrcCyl daItem_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 10.0f,
        /* Height */ 50.0f,
    }},
};

static actor_method_class l_daItem_Method = {
    (process_method_func)daItem_Create,
    (process_method_func)daItem_Delete,
    (process_method_func)daItem_Execute,
    (process_method_func)daItem_IsDelete,
    (process_method_func)daItem_Draw,
};

actor_process_profile_definition g_profile_ITEM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_ITEM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daItem_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_ITEM,
    /* Actor SubMtd */ &l_daItem_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
