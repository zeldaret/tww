//
// Generated by dtk
// Translation Unit: d_a_item.cpp
//

#include "d/d_item.h"
#include "d/d_item_data.h"
#include "d/actor/d_a_itembase_static.h"
#include "d/actor/d_a_item.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "d/d_procname.h"
#include "dolphin/types.h"

class dCcD_GObjInf;

static dCcD_SrcCyl m_cyl_src = {
    0,
    0,
    0,
    0,
    0xFFFFFFFF, // Tg damage types
    9,
    0x59,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    0,
    4,
    0,
    
    // Cylinder
    0.0, // X
    0.0, // Y
    0.0, // Z
    10.0, // Radius
    50.0, // Height
};

/* 800F4BC8-800F4BD4       .text getData__12daItemBase_cFv */
daItemBase_c_m_data* daItemBase_c::getData() {
    return &daItemBase_c::m_data;
}

/* 800F4BD4-800F4C4C       .text setArrowTrans__Fs4cXyz */
void setArrowTrans(short, cXyz) {
    /* Nonmatching */
}

/* 800F4C4C-800F4CD8       .text getYOffset__8daItem_cFv */
float daItem_c::getYOffset() {
    switch (m_itemNo) {
    case HEART:
        return 0.0;
    case SKULL_NECKLACE:
        return 0.0;
    case BOKOBABA_SEED:
        return 0.0;
    case GOLDEN_FEATHER:
        return 0.0;
    case BOKO_BELT:
        return 0.0;
    case RED_JELLY:
    case GREEN_JELLY:
    case BLUE_JELLY:
        return 0.0;
    case SWORD:
        return 20.0;
    case SHIELD:
        return 23.0;
    case DROPPED_SWORD:
        return 10.0;
    case GREEN_RUPEE:
    case BLUE_RUPEE:
    case YELLOW_RUPEE:
    case RED_RUPEE:
    case PURPLE_RUPEE:
    case ORANGE_RUPEE:
    case SILVER_RUPEE:
        return 0.0;
    case KAKERA_HEART:
    case UTUWA_HEART:
        return 0.0;
    case SMALL_KEY:
    case BOSS_KEY:
        return 0.0;
    default:
        return 0.0;
    }
}

/* 800F4CD8-800F4E6C       .text set_mtx__8daItem_cFv */
void daItem_c::set_mtx() {
    /* Nonmatching */
}

/* 800F4E6C-800F4FDC       .text set_mtx_base__8daItem_cFP8J3DModel4cXyz5csXyz */
void daItem_c::set_mtx_base(J3DModel*, cXyz, csXyz) {
    /* Nonmatching */
}

/* 800F4FDC-800F5044       .text itemGetCallBack__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void itemGetCallBack(fopAc_ac_c*, dCcD_GObjInf*, fopAc_ac_c*, dCcD_GObjInf*) {
    /* Nonmatching */
}

/* 800F5044-800F53EC       .text CreateInit__8daItem_cFv */
void daItem_c::CreateInit() {
    /* Nonmatching */
    mAcchCir.SetWall(30.0, 30.0);
    cXyz* speedPtr = &speed;
    mAcch.Set(&current.pos, &next.pos, this, 1, &mAcchCir, speedPtr, NULL, NULL);
    mAcch.m_flags &= ~0x400;
    mAcch.m_flags &= ~0x8;
    mCullMtx = mModel->mBaseTransformMtx;
    mStts.Init(0, 0xFF, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetCoHitCallback(&itemGetCallBack);
    
    dItem_data_item_info* item_info = &dItem_data::item_info[m_itemNo];
    f32 height = item_info->mCollisionH;
    f32 radius = item_info->mCollisionR;
    if (mScale.x > 1.0) {
        height *= mScale.x;
        radius *= mScale.x;
    }
    mCyl.SetR(radius);
    mCyl.SetH(height);
    
    mItemTimer = getData()->mDuration;
    field7_0x65a = getData()->field7_0x18;
    mCurState = 0;
    field3_0x650 = speedPtr->y;
    mStatusFlags |= 2;
    
    mUnknownParam = (fpcM_GetParam(this) & 0x03000000) >> 0x18;
    mItemAction = (fpcM_GetParam(this) & 0xFC000000) >> 0x1A;
    
    show();
    
    if (dItem_data::checkSpecialEffect(m_itemNo) && (m_itemNo != SMALL_KEY || (mStatusFlags & 2))) {
        dItem_data::getSpecialEffect(m_itemNo);
        // TODO: dPa_control_c::set
    }
    
    switch (m_itemNo) {
    case BOMB_5:
    case BOMB_10:
    case BOMB_20:
    case BOMB_30:
        mScaleTarget.x = 0.6;
        mScaleTarget.y = 0.6;
        mScaleTarget.z = 0.6;
        break;
    default:
        mScaleTarget.x = 1.0;
        mScaleTarget.y = 1.0;
        mScaleTarget.z = 1.0;
        break;
    }
    
    mSwitchId = (fpcM_GetParam(this) & 0x00FF0000) >> 0x10;
    if (mSwitchId != 0xFF && i_fopAcM_isSwitch(this, mSwitchId)) {
        hide();
        mStatusFlags |= 2;
    }
    mActivationSwitch = (orig.angle.z & 0x00FF) >> 0;
    
    initAction();
    
    switch (m_itemNo) {
    case SHIELD:
        mStatus |= 0x4000;
        break;
    case DROPPED_SWORD:
        current.angle.x = 0x4000;
        break;
    }
    
    set_mtx();
    animPlay(1.0, 1.0, 1.0, 1.0, 1.0);
    
    s16 procname = PROC_BST; // Gohdan
    if (fopAcIt_Judge(&fpcSch_JudgeForPName, &procname)) {
        // TODO: dPa_control_c::set
        mpParticleEmitter = 0;
    }
}

/* 800F53EC-800F5668       .text _daItem_create__8daItem_cFv */
s32 daItem_c::_daItem_create() {
    /* Nonmatching */
    fopAcM_SetupActor(this, daItem_c);
    
    m_itemNo = (fpcM_GetParam(this) & 0x000000FF) >> 0x00;
    
    if (!dItem_data::field_item_res[m_itemNo].mModelArcName) {
        setLoadError();
        return cPhs_ERROR_e;
    }
    
    mPickupFlag = (fpcM_GetParam(this) & 0x0000FF00) >> 0x08;
    if (m_itemNo != BLUE_JELLY) { // Blue Chu Jelly uses mPickupFlag as if it was a switch.
        mPickupFlag &= 0x7F;
        if (dComIfGs_isItem(mPickupFlag, orig.roomNo) && mPickupFlag != 0x7F) {
            // Already picked up, don't create the item again.
            setLoadError();
            return cPhs_ERROR_e;
        }
    }
    
    s32 phase_state = dComIfG_resLoad(&mPhs, dItem_data::field_item_res[m_itemNo].mModelArcName);
    if (phase_state == cPhs_COMPLEATE_e) {
        u16 heapSize = dItem_data::field_item_res[m_itemNo].mHeapSize;
        s32 result = fopAcM_entrySolidHeap(this, (heapCallbackFunc)&CheckFieldItemCreateHeap, heapSize);
        if (!result) {
            return cPhs_ERROR_e;
        }
        
        CreateInit();
    }
    
    return phase_state;
}

/* 800F5668-800F5834       .text _daItem_execute__8daItem_cFv */
s32 daItem_c::_daItem_execute() {
    /* Nonmatching */
}

/* 800F5834-800F59CC       .text mode_proc_call__8daItem_cFv */
void daItem_c::mode_proc_call() {
    /* Nonmatching */
}

/* 800F59CC-800F5AFC       .text execInitNormalDirection__8daItem_cFv */
void daItem_c::execInitNormalDirection() {
    /* Nonmatching */
    daPy_getPlayerActorClass()->getHeadTopPos();
    
    field8_0x65c = getData()->field45_0x40;
    
    f32 speedY = getData()->mPickedUpInitialSpeedY;
    speed.x = 0;
    speed.y = speedY;
    speed.z = 0;
    mGravity = getData()->mPickedUpGravity;
    
    show();
    
    // TODO dPa_smokeEcallBack
    // TODO mpParticleEmitter
}

/* 800F5AFC-800F5BC8       .text execMainNormalDirection__8daItem_cFv */
void daItem_c::execMainNormalDirection() {
    /* Nonmatching */
}

/* 800F5BC8-800F5C68       .text execInitGetDemoDirection__8daItem_cFv */
void daItem_c::execInitGetDemoDirection() {
    /* Nonmatching */
}

/* 800F5C68-800F5CDC       .text execWaitGetDemoDirection__8daItem_cFv */
void daItem_c::execWaitGetDemoDirection() {
    /* Nonmatching */
}

/* 800F5CDC-800F5D44       .text execMainGetDemoDirection__8daItem_cFv */
void daItem_c::execMainGetDemoDirection() {
    /* Nonmatching */
}

/* 800F5D44-800F5D88       .text execBringNezumi__8daItem_cFv */
void daItem_c::execBringNezumi() {
    if (mUnknownParam != 1) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    mode_proc_call();
}

/* 800F5D88-800F5F40       .text execWaitMain__8daItem_cFv */
void daItem_c::execWaitMain() {
    /* Nonmatching */
}

/* 800F5F40-800F5FC0       .text execWaitMainFromBoss__8daItem_cFv */
void daItem_c::execWaitMainFromBoss() {
    /* Nonmatching */
}

/* 800F5FC0-800F60C0       .text scaleAnimFromBossItem__8daItem_cFv */
void daItem_c::scaleAnimFromBossItem() {
    /* Nonmatching */
}

/* 800F60C0-800F6110       .text _daItem_draw__8daItem_cFv */
s32 daItem_c::_daItem_draw() {
    if (chkDraw()) {
        return DrawBase();
    }
    return 1;
}

/* 800F6110-800F61C8       .text setTevStr__8daItem_cFv */
void daItem_c::setTevStr() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, getPositionP(), &mTevStr);
    
    mTevStr.mColorC0.r = 0x96;
    mTevStr.mColorC0.g = 0x96;
    mTevStr.mColorC0.b = 0x96;
    mTevStr.mColorK0.r = 0xFF;
    mTevStr.mColorK0.g = 0xFF;
    mTevStr.mColorK0.b = 0xFF;
    g_env_light.setLightTevColorType(mModel, &mTevStr);
    
    for (int i = 0; i < 2; i++) {
        if (!mModelArrow[i]) {
            continue;
        }
        g_env_light.setLightTevColorType(mModelArrow[i], &mTevStr);
    }
}

/* 800F61C8-800F6268       .text _daItem_delete__8daItem_cFv */
s32 daItem_c::_daItem_delete() {
    /* Nonmatching */
    // TODO: dPa_rippleEcallBack::end()
    DeleteBase(dItem_data::field_item_res[m_itemNo].mModelArcName);
}

/* 800F6268-800F6434       .text Reflect__FR4cXyzP4cXyzff */
void Reflect(cXyz&, cXyz*, float, float) {
    /* Nonmatching */
}

/* 800F6434-800F6D24       .text itemGetExecute__8daItem_cFv */
void daItem_c::itemGetExecute() {
    /* Nonmatching */
    execItemGet(m_itemNo);
}

/* 800F6D24-800F6D78       .text itemDefaultRotateY__8daItem_cFv */
void daItem_c::itemDefaultRotateY() {
    // Rotates at a fixed speed.
    s16 rotationSpeed = 0xFFFF / getData()->mNumFramesPerFullSpin;
    fopAcM_addAngleY(this, current.angle.y + rotationSpeed, rotationSpeed);
}

/* 800F6D78-800F6E54       .text checkItemDisappear__8daItem_cFv */
bool daItem_c::checkItemDisappear() {
    bool disappearing = true;
    if (mCurState == 3) {
        disappearing = false;
        show();
    }
    if (mStatusFlags & 0x02) {
        disappearing = false;
    }
    if (mStatusFlags & 0x10) {
        disappearing = false;
    }
    if (dItem_data::item_info[m_itemNo].mSpecialBehaviors & 0x01) {
        disappearing = false;
    }
    if (g_dComIfG_gameInfo.play.mEvtCtrl.mMode != 0) {
        disappearing = false;
    }
    if (mCurState == 4) {
        disappearing = false;
    }
    if ((mStatusFlags & 0x08) || (mStatusFlags & 0x40) || (mStatus & 0x100000)) {
        disappearing = false;
        show();
    }
    return disappearing;
}

/* 800F6E54-800F6E74       .text setItemTimer__8daItem_cFi */
void daItem_c::setItemTimer(int timer) {
    if (timer == -1) {
        mStatusFlags |= 0x10;
        return;
    }
    mItemTimer = timer;
}

/* 800F6E74-800F6EC8       .text checkPlayerGet__8daItem_cFv */
BOOL daItem_c::checkPlayerGet() {
    if (field20_0x638 < getData()->field47_0x42) {
        return FALSE;
    }
    if (mCurState == 3) {
        return FALSE;
    }
    return TRUE;
}

/* 800F6EC8-800F7028       .text itemActionForRupee__8daItem_cFv */
void daItem_c::itemActionForRupee() {
    /* Nonmatching */
}

/* 800F7028-800F713C       .text itemActionForHeart__8daItem_cFv */
void daItem_c::itemActionForHeart() {
    /* Nonmatching */
}

/* 800F713C-800F72A4       .text itemActionForKey__8daItem_cFv */
void daItem_c::itemActionForKey() {
    /* Nonmatching */
}

/* 800F72A4-800F73A4       .text itemActionForEmono__8daItem_cFv */
void daItem_c::itemActionForEmono() {
    /* Nonmatching */
}

/* 800F73A4-800F7898       .text itemActionForSword__8daItem_cFv */
void daItem_c::itemActionForSword() {
    /* Nonmatching */
}

/* 800F7898-800F7AF0       .text itemActionForArrow__8daItem_cFv */
void daItem_c::itemActionForArrow() {
    /* Nonmatching */
}

/* 800F7AF0-800F7BF8       .text checkWall__8daItem_cFv */
void daItem_c::checkWall() {
    /* Nonmatching */
}

/* 800F7BF8-800F7DDC       .text set_bound_se__8daItem_cFv */
void daItem_c::set_bound_se() {
    /* Nonmatching */
}

/* 800F7DDC-800F7E6C       .text checkGetItem__8daItem_cFv */
s32 daItem_c::checkGetItem() {
    if (!checkPlayerGet()) {
        return 0;
    }
    
    if (mCyl.ChkTgHit()) {
        cCcD_Obj* hitObj = mCyl.GetTgHitObj();
        if (hitObj) {
            u32 atType = hitObj->GetAtType();
            if (atType & AT_TYPE_SWORD) {
                itemGetExecute();
                return 1;
            } else if (atType & AT_TYPE_BOOMERANG) {
                mStatusFlags |= 0x08;
            }
        }
    }
    
    return 0;
}

/* 800F7E6C-800F7F0C       .text timeCount__8daItem_cFv */
void daItem_c::timeCount() {
    /* Nonmatching */
}

/* 800F7F0C-800F7F50       .text mode_wait_init__8daItem_cFv */
void daItem_c::mode_wait_init() {
    /* Nonmatching */
}

/* 800F7F50-800F80CC       .text mode_water_init__8daItem_cFv */
void daItem_c::mode_water_init() {
    /* Nonmatching */
}

/* 800F80CC-800F844C       .text mode_wait__8daItem_cFv */
void daItem_c::mode_wait() {
    /* Nonmatching */
}

/* 800F844C-800F8528       .text mode_water__8daItem_cFv */
void daItem_c::mode_water() {
    /* Nonmatching */
}

/* 800F8528-800F8950       .text initAction__8daItem_cFv */
void daItem_c::initAction() {
    /* Nonmatching */
}

/* 800F8950-800F8970       .text daItem_Draw__FP8daItem_c */
s32 daItem_Draw(daItem_c* i_this) {
    return i_this->_daItem_draw();
}

/* 800F8970-800F8990       .text daItem_Execute__FP8daItem_c */
s32 daItem_Execute(daItem_c* i_this) {
    return i_this->_daItem_execute();
}

/* 800F8990-800F89B0       .text daItem_IsDelete__FP8daItem_c */
s32 daItem_IsDelete(daItem_c* i_this) {
    return i_this->_daItem_isdelete();
}

/* 800F89B0-800F89D0       .text daItem_Delete__FP8daItem_c */
s32 daItem_Delete(daItem_c* i_this) {
    return i_this->_daItem_delete();
}

/* 800F89D0-800F89F0       .text daItem_Create__FP10fopAc_ac_c */
s32 daItem_Create(fopAc_ac_c* i_this) {
    ((daItem_c*)i_this)->_daItem_create();
}

/* 800F89F0-800F89F8       .text _daItem_isdelete__8daItem_cFv */
s32 daItem_c::_daItem_isdelete() {
    return 1;
}

/* 800F89F8-800F8A14       .text getHeadTopPos__9daPy_py_cCFv */
void daPy_py_c::getHeadTopPos() const {
    /* Nonmatching */
}

static actor_method_class l_daItem_Method = {
    (process_method_func)daItem_Create,
    (process_method_func)daItem_Delete,
    (process_method_func)daItem_Execute,
    (process_method_func)daItem_IsDelete,
    (process_method_func)daItem_Draw,
};

extern actor_process_profile_definition g_profile_ITEM = {
    fpcLy_CURRENT_e,
    7,
    fpcPi_CURRENT_e,
    PROC_ITEM,
    &g_fpcLf_Method.mBase,
    sizeof(daItem_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x00F5,
    &l_daItem_Method,
    0x000C0100,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_0_e,
};
