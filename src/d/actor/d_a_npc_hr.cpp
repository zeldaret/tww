/**
 * d_a_npc_hr.cpp
 * NPC - Zephos & Cyclos
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_hr.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_hr.h"
#include "d/d_snap.h"
#include "d/d_kankyo_wether.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_ship.h"
#include "d/actor/d_a_tornado.h"
#include "d/d_item.h"
#include "f_op/f_op_actor_mng.h"

static fpc_ProcID l_msgId;
static msg_class* l_msg;

/* 00000078-000000A0       .text init__14daNpc_Wind_EffFv */
void daNpc_Wind_Eff::init() {
    mWindEffState = WIND_EFF_INACTIVE;
    mAlphaFactor = 0.0f;
    mSpeed.setall(0.0f);
    mpSquallPos = NULL;
}

/* 000000A0-000000EC       .text remove__14daNpc_Wind_EffFv */
void daNpc_Wind_Eff::remove() {
    if (mWindEffState != WIND_EFF_INACTIVE) {
        mpFollowECallBack.end();
        init();
    }
}

/* 000000EC-000001B0       .text create__14daNpc_Wind_EffFP4cXyz */
BOOL daNpc_Wind_Eff::create(cXyz* squallPos) {
    if (mWindEffState == WIND_EFF_INACTIVE) {
        mPos = *squallPos;

        mAlphaFactor = 1.0f;
        mpSquallPos = squallPos;
        JPABaseEmitter* pEmitter = dComIfGp_particle_set(dPa_name::ID_AK_JN_WINDLINE00, &mPos, NULL, NULL, 0xFF, &mpFollowECallBack);
        
        if (pEmitter == NULL) {
            return FALSE;
        } else {
            mWindEffState = WIND_EFF_FADE_IN;
            return TRUE;
        }
    }
    return FALSE;
}

/* 000001B0-000001E4       .text end__14daNpc_Wind_EffFv */
BOOL daNpc_Wind_Eff::end() {
    if (mWindEffState == WIND_EFF_FADE_IN || mWindEffState == WIND_EFF_ACTIVE) {
        mWindEffState = WIND_EFF_FADE_OUT;
        mpSquallPos = NULL;
        return TRUE;
    }
    return FALSE;
}

/* 000001E4-0000030C       .text proc__14daNpc_Wind_EffFv */
void daNpc_Wind_Eff::proc() {
    JPABaseEmitter* pEmitter;
    switch(mWindEffState) {
        case WIND_EFF_FADE_IN:
            pEmitter = mpFollowECallBack.getEmitter();
            if (mAlphaFactor < 0.9f) {
                mAlphaFactor += 0.1f;
                
            } else {
                mWindEffState = WIND_EFF_ACTIVE;
                mAlphaFactor = 1.0f;
            }
#if VERSION > VERSION_DEMO
            if (pEmitter != NULL) {
                pEmitter->setGlobalAlpha(mAlphaFactor * 128.0f);
            }
#else
            pEmitter->setGlobalAlpha(mAlphaFactor * 128.0f);
#endif

            setspd();
            move();
            break;
        case WIND_EFF_ACTIVE:
            setspd();
            move();
            break;
        case WIND_EFF_FADE_OUT:
            pEmitter = mpFollowECallBack.getEmitter();

            if (mAlphaFactor > 0.1f) {
                mAlphaFactor -= 0.1f;
                move();

#if VERSION == VERSION_DEMO
                pEmitter->setGlobalAlpha(mAlphaFactor * 128.0f);
#else
                if (pEmitter != NULL) {
                    pEmitter->setGlobalAlpha(mAlphaFactor * 128.0f);
                }
#endif
            } else {
                remove();
            }
            break;
    }
}

/* 0000030C-00000368       .text setspd__14daNpc_Wind_EffFv */
void daNpc_Wind_Eff::setspd() {
    cXyz speed = *mpSquallPos - mPos;
    mSpeed.set(speed);
}

/* 000003A4-000003D4       .text move__14daNpc_Wind_EffFv */
void daNpc_Wind_Eff::move() {
    mPos += mSpeed;
}

/* 000003D4-00000550       .text setSquallPos__18daNpc_Wind_ClothesFi */
void daNpc_Wind_Clothes::setSquallPos(int param_1) {
    fopAc_ac_c* a_actor = fopAcM_SearchByID(mProcId);
    JUT_ASSERT(DEMO_SELECT(398, 402), a_actor);

    mSquallPos[param_1] = a_actor->current.pos;

    cXyz temp;
    f32 temp2 = squallOrbitParam[2] * (cM_ssin((int)mSquallCounter[param_1]) * 0.2f + 1.0f); // fake?
    temp.x = squallOrbitParam[0]  + temp2 * cM_scos(mSquallCounter[param_1]);
    temp.y = squallOrbitParam[1] + temp2 * cM_ssin(mSquallCounter[param_1]);
    temp.z = squallOrbitParam[4] + param_1 * squallOrbitParam[3];
    fpoAcM_absolutePos(a_actor, &temp, &mSquallPos[param_1]);
}

/* 00000550-00000620       .text create__18daNpc_Wind_ClothesFP10fopAc_ac_cUcPfi */
BOOL daNpc_Wind_Clothes::create(fopAc_ac_c* i_this, u8 param_2, f32* param_3, int param_4) {
    mSquallState = param_2;
    mProcId = fopAcM_GetID(i_this);
    if (param_3 != NULL ) {
        for (int i = 0; i < param_4; i++) {
            squallOrbitParam[i] = param_3[i];
        }
    }

    for(int i = 0; i < 4; i++) {
        mSquallCounter[i] = i*0x4000;
        setSquallPos(i);
        mWindEff[i].create(&mSquallPos[i]);
    }
    return TRUE;
}

/* 00000620-00000678       .text end__18daNpc_Wind_ClothesFv */
BOOL daNpc_Wind_Clothes::end() {
    mSquallState = 0;
    for (int i = 0; i < 4; i++) {
        mWindEff[i].end();
    }
    return TRUE;
}

/* 00000678-0000075C       .text proc__18daNpc_Wind_ClothesFv */
void daNpc_Wind_Clothes::proc() {
    switch(mSquallState) {
        case 1:
            fopAc_ac_c* a_actor = fopAcM_SearchByID(mProcId);
            JUT_ASSERT(DEMO_SELECT(465, 469), a_actor);

            for (int i = 0; i < 4; i++) {
                mSquallCounter[i] += 0x100;
                setSquallPos(i);
            }
            break;
    }

    for(int i = 0; i < 4; i++) {
        mWindEff[i].proc();
    }
}

/* 0000075C-000007B0       .text init__18daNpc_Wind_ClothesFv */
void daNpc_Wind_Clothes::init() {
    mSquallState = 0;
    for(int i = 0; i < 4; i++) {
        mWindEff[i].init();
    }
}

/* 000007B0-00000800       .text remove__18daNpc_Wind_ClothesFv */
void daNpc_Wind_Clothes::remove() {
    for(int i = 0; i < 4; i++) {
        mWindEff[i].remove();
    }
}

static dCcD_SrcCyl dNpc_hr_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_NORMAL_ARROW | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW | AT_TYPE_LIGHT_ARROW,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 0.0f,
        /* Height */ 0.0f,
    }},
};

extern dCcD_SrcCyl dNpc_cyl_src;

/* 00000800-0000080C       .text getShapeType__10daNpc_Hr_cFv */
int daNpc_Hr_c::getShapeType() {
    return fopAcM_GetParam(this) & 0xFF;
}

/* 0000080C-00000818       .text getSwbit__10daNpc_Hr_cFv */
int daNpc_Hr_c::getSwbit() {
    return fopAcM_GetParam(this) >> 8 & 0xFF;
}

/* 00000818-00000838       .text daNpc_hr_XyCheckCB__FPvi */
static s16 daNpc_hr_XyCheckCB(void* i_this, int i_itemBtn) {
    return ((daNpc_Hr_c*)i_this)->XyCheckCB(i_itemBtn);
}

/* 00000838-0000085C       .text XyCheckCB__10daNpc_Hr_cFi */
s16 daNpc_Hr_c::XyCheckCB(int i_itemBtn) {
    return dComIfGp_getSelectItem(i_itemBtn) == dItem_WIND_WAKER_e ? TRUE : FALSE;
}

/* 0000085C-000008AC       .text daNpc_hr_XyEventCB__FPvi */
static s16 daNpc_hr_XyEventCB(void* i_this, int i_itemBtn) {
    daNpc_Hr_c* a_this = (daNpc_Hr_c*)i_this;
    a_this->mEventIdx = dComIfGp_evmng_getEventIdx("TACT_HT");
    return a_this->mEventIdx;
}

/* 000008AC-000008FC       .text onHide__10daNpc_Hr_cFi */
void daNpc_Hr_c::onHide(int param_1) {
    if (!chkFlag(HR_FLAG_00000010) || param_1 != 0) {
        setFlag(HR_FLAG_00000010);

#if VERSION == VERSION_DEMO
        if(mpEmitter != NULL) {
            mSmokeCallBack.end();
        }
        mpEmitter = NULL;
#else
        mSmokeCallBack.end();
#endif
    }
}

/* 000008FC-000009F0       .text offHide__10daNpc_Hr_cFi */
void daNpc_Hr_c::offHide(int param_1) {
    u16 particleID;
    if (chkFlag(HR_FLAG_00000010) || param_1 != 0) {
        clrFlag(HR_FLAG_00000010);

        switch (mType) {
            case 1:
                particleID = dPa_name::ID_IT_SN_KINTOUN_RT00;
                break;
            default:
                particleID = dPa_name::ID_IT_SN_KINTOUN_FT00;
                break;
        }
        
        JPABaseEmitter* pEmitter = dComIfGp_particle_set(particleID, &mCloudPos, &shape_angle, &scale, 0xFF, &mSmokeCallBack, fopAcM_GetRoomNo(this));

#if VERSION == VERION_DEMO
        mpEmitter = pEmitter;
#endif

        if(DEMO_SELECT(mpEmitter, pEmitter) != NULL && mType == 1) {
            DEMO_SELECT(mpEmitter, pEmitter)->setGlobalPrmColor(0x97, 0x76, 0xA9);
            DEMO_SELECT(mpEmitter, pEmitter)->setGlobalEnvColor(0x84, 0x70, 0x93);
        }
    }
}

/* 000009F0-00000A94       .text defaultSetPos__10daNpc_Hr_cFP4cXyz */
void daNpc_Hr_c::defaultSetPos(cXyz* param_1) {
    current.pos.set(*param_1);
    attention_info.position.set(current.pos);
    attention_info.position.y += 150.0f;

    mAttnBasePos = attention_info.position;
    eyePos.set(current.pos);
    eyePos.y += 100.0f;

    mEyePos = eyePos;
}

/* 00000A94-00000ADC       .text getNowEventAction__10daNpc_Hr_cFv */
s32 daNpc_Hr_c::getNowEventAction() {
    static char* action_table[] = {
        "WAIT",
        "SPEAK",
        "PATTEN",
        "TACT0",
        "TACT1",
        "TACT2",
        "TACT3",
        "WIND0",
        "WIND1",
        "HIDE_LINK",
        "DISP_LINK",
        "DISP_MY",
        "MOVE",
        "TURN_LINK",
        "LOOK",
        "SMALL",
        "INTRO",
        "CHANGE",
        "DEBUG",
    };

    return dComIfGp_evmng_getMyActIdx(mStaffIdx, action_table, ARRAY_SIZE(action_table), FALSE, 1);
}

/* 00000ADC-00000CD0       .text demoInitWind__10daNpc_Hr_cFv */
void daNpc_Hr_c::demoInitWind() {
    dScnKy_env_light_c& env_light = g_env_light;
    env_light.mWind.mWindVec.set(0.0f, 0.0f, 1.0f); // fake?
    dKyw_tact_wind_set(0, 0x4000);
    dKyw_tact_wind_set_go();
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    cXyz* pWindVec = dKyw_get_wind_vec();
    cSGlobe globe(*pWindVec);
    cSAngle angle(globe.U());
    angle += cSAngle::_90;
    f32 _40 = 40.0f;
    mScaleFactor = 1.0f;
    speed.set(0.0f, 0.0f, 40.0f);

    current.pos.set(pLink->current.pos);
    current.pos.x += angle.Cos() * 20.0f;
    current.pos.y += 150.0f + mScaleFactor * _40 * _40 * 0.5f;

    current.pos.z += angle.Sin() * 20.0f -  _40 * speed.z;
    speed.y = -(mScaleFactor * _40);
    
    cXyz unused(0.0f, 0.0f, 1.0f);

    current.angle.y = 0;
    shape_angle.y = 0;
    mMoveTimer = 0x8C;
    dKyw_custom_windpower(1.0f);
    pLink->setPlayerPosAndAngle(&pLink->current.pos, 0x7FFF);
    dComIfGs_offSwitch(getSwbit(), fopAcM_GetRoomNo(this));
    mDoAud_seStart(JA_SE_TAKT_WIND_DEMO);
}

/* 00000CD0-00000DE8       .text demoProcWind__10daNpc_Hr_cFi */
bool daNpc_Hr_c::demoProcWind(int param_1) {
    setFlag(HR_FLAG_00000020);
    if (param_1 == 0 && mMoveTimer > 0 && mMoveTimer <= 0x6E) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }

    if (mMoveTimer > 0) {
        mMoveTimer--;
        if (mMoveTimer > 0x3C) {
            fopAcM_posMove(this, NULL);
            speed.y += mScaleFactor;
        }
        if (mMoveTimer < 0xF) {
            dKyw_custom_windpower(0);
        }
    } else {
        speed.setall(0.0f);
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }

    eyePos.set(current.pos);
    attention_info.position.set(current.pos);
    return false;
}

/* 00000DE8-00000E50       .text demoInitWait__10daNpc_Hr_cFv */
void daNpc_Hr_c::demoInitWait() {
    int* pTimer = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Timer");
    if (pTimer != NULL) {
        mMoveTimer = *pTimer;
    } else {
        mMoveTimer = 0;
    }
}

/* 00000E50-00000EA0       .text demoProcWait__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::demoProcWait() {
    if (mMoveTimer > 0) {
        mMoveTimer--;
    } else {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return FALSE;
}

/* 00000EA0-00000F38       .text demoInitSpeak__10daNpc_Hr_cFv */
void daNpc_Hr_c::demoInitSpeak() {
    talkInit();
    int* a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "MsgNo");
    JUT_ASSERT(DEMO_SELECT(861, 871), a_intP);
    mMsgNo = *a_intP;
}

/* 00000F38-00000FA8       .text demoProcSpeak__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::demoProcSpeak() {
    u16 temp = talk();
    if (temp == fopMsgStts_BOX_CLOSED_e || temp == 0xFE) {
        dComIfGp_evmng_cutEnd(mStaffIdx);

        if (chkFlag(HR_FLAG_00000002)) {
            clrFlag(HR_FLAG_00000002);
        }
    }
    return TRUE;
}

/* 00000FA8-00001008       .text demoProcPatten__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::demoProcPatten() {
    u16 temp = talk();
    if (temp == fopMsgStts_BOX_CLOSED_e || temp == 0xFE || temp == fopMsgStts_INPUT_e) {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return TRUE;
}

/* 00001008-000010DC       .text demoProcTact0__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::demoProcTact0() {
    if (chkFlag(HR_FLAG_00000002)) {
        if (l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
            l_msg->mStatus = fopMsgStts_MSG_ENDS_e;
            fopMsgM_messageSendOn();
            clrFlag(HR_FLAG_00000200);
            
            if (dComIfGp_checkMesgCancelButton()) {
                setFlag(HR_FLAG_00000200);
            } else {
                execItemGet(TACT_SONG1);
            }
            dComIfGp_evmng_cutEnd(mStaffIdx);
            clrFlag(HR_FLAG_00000002);
        }
        return TRUE;
    }

    dComIfGp_evmng_cutEnd(mStaffIdx);
    return TRUE;
}

/* 000010DC-00001174       .text demoProcTact1__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::demoProcTact1() {
    u16 temp = talk();
    if (temp == fopMsgStts_BOX_CLOSED_e || temp == fopMsgStts_MSG_DESTROYED_e || temp == 0xFE) {
        if (chkFlag(HR_FLAG_00000200)) {
            endTalk();
            endTact();
        } else {
            dComIfGp_evmng_cutEnd(mStaffIdx);
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2708);
        }
    }
    return TRUE;
}

/* 00001174-000011AC       .text demoProcTact2__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::demoProcTact2() {
    dComIfGp_evmng_cutEnd(mStaffIdx);
    return TRUE;
}

/* 000011AC-00001268       .text demoProcTact3__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::demoProcTact3() {
    if(daPy_getPlayerLinkActorClass()->getTactTimerCancel() > 0) {
        mEventIdx = dComIfGp_evmng_getEventIdx("TACTM_RT");
        setEvFlag(EVFLAG_EVENT_CHANGE_REQ);
        fopAcM_orderChangeEventId(daPy_getPlayerLinkActorClass(), this, mEventIdx, 0, 0xFFFF);
    } else {
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    return TRUE;
}

/* 00001268-0000128C       .text calcKaijou__10daNpc_Hr_cFi */
int daNpc_Hr_c::calcKaijou(int param_1) {
    int sum = 0;
    for (int i = 1; param_1 >= 1; i++, param_1--) {
        sum += i;
    }
    return sum;
}

/* 0000128C-000015B4       .text demoInitMove__10daNpc_Hr_cFv */
void daNpc_Hr_c::demoInitMove() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    daShip_c* pShip = (daShip_c*)dComIfGp_getShipActor();

    cXyz* pPos = dComIfGp_evmng_getMyXyzP(mStaffIdx, "Pos");
    if(pPos != NULL) {
        mTargetPos.set(*pPos);
    } else {
        cXyz* pPos3 = dComIfGp_evmng_getMyXyzP(mStaffIdx, "Pos3");
        if(pPos3 != NULL && pShip != NULL) {
            fpoAcM_absolutePos(pShip, pPos3, &mTargetPos);
        } else {
            cXyz* pPos2 = dComIfGp_evmng_getMyXyzP(mStaffIdx, "Pos2");
            if(pPos2 != NULL) {
                fpoAcM_absolutePos(pLink, pPos2, &mTargetPos);
            }
        }
    }

    int* pTimer = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Timer");
    if(pTimer != NULL) {
        mMoveTimer = *pTimer;
        if(mMoveTimer < 10) {
            mMoveTimer = 10;
        }
    } else {
        mMoveTimer = 0x14;
    }

    int* pBrake = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Brake");
    if (pBrake != NULL) {
        mBrakeTime = *pBrake;
    } else {
        mBrakeTime = 0;
    }

    int* pAngleY = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "AngleY");
    if (pAngleY != NULL) {
        mTargetAngle = *pAngleY;
        if (chkEvFlag(EVFLAG_LOCK_ROTATION)) {
            current.angle.y = mTargetAngle;
        }
    } else {
        mTargetAngle = current.angle.y;
    }

    int* pSoundOff = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "SOUND_OFF");
    if (pSoundOff == NULL) {
        fopAcM_seStart(this, JA_SE_CM_HU_RC_MOVE_RAPID, 0);
    }

    setFlag(HR_FLAG_00000020);
    f32 temp2;
    if (mBrakeTime == 0) {
        temp2 = 1.0f/mMoveTimer;
    } else {
        temp2 = 1.0f/(mMoveTimer - mBrakeTime + (f32)calcKaijou(mBrakeTime) / mBrakeTime);
    }
    
    speed.x = temp2 * (mTargetPos.x - current.pos.x);
    speed.y = temp2 * (mTargetPos.y - current.pos.y);
    speed.z = temp2 * (mTargetPos.z - current.pos.z);
}

/* 000015B4-000015CC       .text demoInitSmall__10daNpc_Hr_cFv */
void daNpc_Hr_c::demoInitSmall() {
    mScaleFactor = 11.0f;
    mMoveTimer = 0;
}

/* 000015CC-00001688       .text demoProcSmall__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::demoProcSmall() {
    if (cLib_addCalc(&mScaleFactor, 1.0f, 0.1f, 100.0f, 0.3f) < 0.3f) {
        mScaleFactor = 1.0f;
        dComIfGp_evmng_cutEnd(mStaffIdx);
    }
    scale.setall(mScaleFactor);

    JPABaseEmitter* pEmitter = DEMO_SELECT(mpEmitter, mSmokeCallBack.getEmitter());

    if(pEmitter != NULL) {
        pEmitter->setGlobalScale(scale);
    }
    return TRUE;
}

/* 00001688-000017AC       .text demoProcMove__10daNpc_Hr_cFv */
bool daNpc_Hr_c::demoProcMove() {
    setFlag(HR_FLAG_00000020);
    if (mMoveTimer <= 0) {
        speed.setall(0.0f);
        dComIfGp_evmng_cutEnd(mStaffIdx);
    } else if (mMoveTimer < mBrakeTime) {
        f32 fac = mMoveTimer / (f32)(mMoveTimer+1);
        speed.x *= fac;
        speed.y *= fac;
        speed.z *= fac;
    }
    
    if (mMoveTimer > 0) {
        fopAcM_posMove(this, NULL);

        if (!chkEvFlag(EVFLAG_LOCK_ROTATION)) {
            cLib_addCalcAngleS2(&current.angle.y, mTargetAngle, mMoveTimer, 0x3FFF);
        }
        mMoveTimer--;
    }
    return true;
}

/* 000017AC-000018C0       .text demoInitChange__10daNpc_Hr_cFv */
void daNpc_Hr_c::demoInitChange() {
    int* a_intP = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "prm0");
    JUT_ASSERT(DEMO_SELECT(1169, 1185), a_intP);

    if(a_intP != NULL) {
        switch(*a_intP) {
            case 1:
                mEventIdx = dComIfGp_evmng_getEventIdx("TACT1_RT");;
                break;
            default:
                mEventIdx = dComIfGp_evmng_getEventIdx("PATTEN_RT");;
        }
        setEvFlag(EVFLAG_EVENT_CHANGE_REQ);
        fopAcM_orderChangeEventId(daPy_getPlayerLinkActorClass(), this, mEventIdx, 0, 0xFFFF);
    }
}

/* 000018C0-00001D84       .text demoInitCom__10daNpc_Hr_cFv */
void daNpc_Hr_c::demoInitCom() {
    daShip_c* pShip = (daShip_c*)dComIfGp_getShipActor();
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();

    int* turnPl = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "TURN_PL");
    if (turnPl != NULL) {
        if (*turnPl != 0) {
            setEvFlag(EVFLAG_LOCK_ROTATION);
        } else {
            clrEvFlag(EVFLAG_LOCK_ROTATION);
        }
    }

    int* tornado = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "TORNADO");
    if (tornado != NULL) {
        if (*tornado != 0) {
            setEvFlag(EVFLAG_TORNADO_ACTIVE);
        } else {
            clrEvFlag(EVFLAG_TORNADO_ACTIVE);
        }
    }

    int* update = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "UPDATE");
    if (update != NULL) {
        if (*update != 0) {
            clrEvFlag(EVFLAG_SKIP_UPDATE);
        } else {
            setEvFlag(EVFLAG_SKIP_UPDATE);
        }
    }

    int* tornado_off = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "TORNADE_OFF");
    if (tornado_off != NULL) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2710);
        dComIfGs_onSwitch(getSwbit(), fopAcM_GetRoomNo(this));
        mReturnState = 1;
    }

    int* anm = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "ANM");
    if (anm != NULL) {
        setAnm(*anm);
    }

    int* texAnm = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "TEXANM");
    if (texAnm != NULL) {
        setTexPtn(*texAnm);
    }

    int* soundInit = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Sound_Init");
    if (soundInit != NULL) {
        mDoAud_tact_reset();
    }

    int* soundPlay = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Sound_Play");
    if (soundPlay != NULL) {
        mDoAud_tact_melodyPlay(1);
    }

    int* soundEnd = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Sound_End");
    if (soundEnd != NULL) {
        mDoAud_tact_reset();
        clrEvFlag(EVFLAG_TACT_SOUND_ACTIVE);
    }

    cXyz* startPos = dComIfGp_evmng_getMyXyzP(mStaffIdx, "StartPos");
    if (startPos != NULL) {
        current.pos.set(*startPos);
    }

    cXyz* startPos2 = dComIfGp_evmng_getMyXyzP(mStaffIdx, "StartPos2");
    if (startPos2 != NULL) {
        fpoAcM_absolutePos(pLink, startPos2, &current.pos);
    }

    cXyz* startPos3 = dComIfGp_evmng_getMyXyzP(mStaffIdx, "StartPos3");
    if (startPos3 != NULL && pShip != NULL) {
        fpoAcM_absolutePos(pShip, startPos3, &current.pos);
    }

    int* wind = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Wind");
    f32* windPrm = dComIfGp_evmng_getMyFloatP(mStaffIdx, "WindPrm");

    if (wind != NULL) {
        switch(*wind) {
            case 1:
                if (windPrm != NULL) {
                    mClothes.create(this, *wind, windPrm, dComIfGp_evmng_getMySubstanceNum(mStaffIdx, "WindPrm"));
                }
                break;
            default:
                mClothes.end();
                break;
        }

    }

    int* away = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "AWAY");
    if (away != NULL) {
        mDoAud_seStart(JA_SE_CM_HU_RC_FLY_AWAY);
        if (getShapeType() == 1) {
            mDoAud_seStart(JA_SE_CV_RC_FLY_AWAY);
        } else {
            mDoAud_seStart(JA_SE_CV_HU_FLY_AWAY);
        }
    }
}

/* 00001D84-00001F08       .text demoProcCom__10daNpc_Hr_cFv */
void daNpc_Hr_c::demoProcCom() {
    if (chkEvFlag(EVFLAG_LOCK_ROTATION)) {
        setFlag(HR_FLAG_00000080);
    }

    if (chkEvFlag(EVFLAG_SKIP_UPDATE)) {
        setFlag(HR_FLAG_00000100);
    }

    if (chkEvFlag(EVFLAG_TACT_SOUND_ACTIVE)) {
        mDoAud_tact_ambientPlay();
    }

    if (!chkFlag(HR_FLAG_00000010)) {
        f32 _15 = 15.0f;

        f32 temp = speed.abs();
        if (temp > _15) {
            temp = _15;
        }
        fopAcM_seStart(this, JA_SE_CM_HU_RC_FLYING, (temp/_15)*100.0f);
    }
}

/* 00001F08-0000232C       .text demoProc__10daNpc_Hr_cFv */
bool daNpc_Hr_c::demoProc() {
    bool temp;
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    
    temp = true;
    if (chkEvFlag(EVFLAG_EVENT_CHANGE_REQ)) {
        mStaffIdx = dComIfGp_evmng_getMyStaffId("Hr2");
        clrEvFlag(EVFLAG_EVENT_CHANGE_REQ);
    }

    s32 eventAction = getNowEventAction();
    if(dComIfGp_evmng_getIsAddvance(mStaffIdx)) {
        demoInitCom();
        setFlag(HR_FLAG_00000002);
        switch(eventAction) {
            case 1:
            case 2:
                demoInitSpeak();
                break;
            case 7:
                demoInitWind();
                break;
            case 9:
                pLink->onPlayerNoDraw();
                dComIfGs_offSwitch(getSwbit(), fopAcM_GetRoomNo(this));
                break;
            case 10:
                pLink->offPlayerNoDraw();
                break;
            case 11: {
                cXyz* pPos = dComIfGp_evmng_getMyXyzP(mStaffIdx, "Pos");

                if (pPos != NULL) {
                    current.pos.set(*pPos);
                }

                int* pAngleY = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "AngleY");
                if (pAngleY != NULL) {
                    current.angle.y = *pAngleY;
                }

                offHide(0);
                demoInitWait();
                mAnmIdx = -1;
                setAnm(0);
                break;
            }
            case 12:
                demoInitMove();
                break;
            case 13: {
                mTargetAngle = fopAcM_searchActorAngleY(pLink, this);
                int* pTimer = dComIfGp_evmng_getMyIntegerP(mStaffIdx, "Timer");

                if (pTimer != NULL) {
                    mMoveTimer = *pTimer;
                } else {
                    mMoveTimer = 0;
                }
                break;
            }
            case 14:
                setAnm(0);
                demoInitWait();
                break;
            case 0:
                demoInitWait();
                break;
            case 15:
                demoInitSmall();
                break;
            case 16:
                speed.y = 0.0f;
                break;
            case 17:
                demoInitChange();
                break;
            case 5:
                clrFlag(HR_FLAG_00000200);
                break;
        }
    }
    
    switch(eventAction) {
        case 1:
            demoProcSpeak();
            break;
        case 2:
            demoProcPatten();
            break;
        case 7:
            temp = demoProcWind(0);
            break;
        case 8:
            temp = demoProcWind(1);
            break;
        case 12:
            temp = demoProcMove();
            break;
        case 11:
            demoProcWait();
            break;
        case 13:
            if (mMoveTimer > 0) {
                mMoveTimer--;
            } else {
                s16 angle = pLink->shape_angle.y;
                cLib_addCalcAngleS(&angle, mTargetAngle, 1, 0x800, 0x800);
                pLink->setPlayerPosAndAngle(NULL, angle);
                if (angle == mTargetAngle) {
                    dComIfGp_evmng_cutEnd(mStaffIdx);
                }
            }
            break;
        case 14:
            demoProcWait();
            setFlag(HR_FLAG_00000040);
            break;
        case 0:
            demoProcWait();
            break;
        case 3:
            demoProcTact0();
            break;
        case 4:
            demoProcTact1();
            break;
        case 5:
            demoProcTact2();
            break;
        case 6:
            demoProcTact3();
            break;
        case 15:
            demoProcSmall();
            break;
        case 16:
            if (cLib_addCalc(&current.pos.y, home.pos.y + 6000.0f, 0.5f, 100.0f, 5.0f) < 5.0f) {
                dComIfGp_evmng_cutEnd(mStaffIdx);
            }
            break;
        case 17:
            break;
        default:
            dComIfGp_evmng_cutEnd(mStaffIdx);
            break;
    }

    demoProcCom();
    return temp;
}

static const int l_bck_ix_tbl[] = {
    HR_BCK_H_WAIT01,
    HR_BCK_R_WAIT01,
    HR_BCK_R_WAIT02,
    HR_BCK_LOOK,
    HR_BCK_TALK01,
    HR_BCK_TALK01,
    HR_BCK_TALK01,
    HR_BCK_TALK02,
    HR_BCK_TALK02,
    HR_BCK_TALK03,
    HR_BCK_TALK03,
    HR_BCK_DAMAGE,
    HR_BCK_TALK03,
};

static const int l_btp_ix_tbl[] = {
    HR_BTP_MABA_H,
    HR_BTP_MABA_R01,
    HR_BTP_MABA_R02,
};

/* 0000232C-00002550       .text nodeCallBack_Hr__FP7J3DNodei */
static BOOL nodeCallBack_Hr(J3DNode* node, int calcTiming) {
    cXyz temp;
    cXyz temp2;
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Hr_c* i_this = (daNpc_Hr_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)node;
        int jntNo = joint->getJntNo();

        if(i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (jntNo == i_this->getHeadJntNum()) {
                cMtx_YrotM(*calc_mtx, -i_this->getHead_y());

                s16 angle;
                if (i_this->mAnmIdx != 1 && i_this->mAnmIdx != 9 && i_this->mAnmIdx != 10) {
                    angle = i_this->getHead_x();
                } else {
                    angle = 0;
                }
                cLib_addCalcAngleS(&i_this->mHeadRotation, angle, 8, 0x400, 0x100);
                cMtx_ZrotM(*calc_mtx, -i_this->mHeadRotation);
                temp.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&temp, &temp2);

                i_this->setAttentionBasePos(temp2);
                temp.set(20.0f, -20.0f, 0.0f);

                MtxPosition(&temp, &temp2);

                i_this->setEyePos(temp2);
                i_this->incAttnSetCount();
            } else if (jntNo == i_this->getBackboneJntNum()) {
                mDoMtx_XrotM(*calc_mtx, i_this->getBackbone_y());
            } else if (jntNo == i_this->m_waist_jnt_num) {
                temp.set(0.0f, 0.0f, 0.0f);
                MtxPosition(&temp, &i_this->mCloudPos);
            }
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, *calc_mtx);
        }
    }
    return TRUE;
}

/* 00002550-00002868       .text node_Ht_ant__10daNpc_Hr_cFi */
void daNpc_Hr_c::node_Ht_ant(int jntNo) {
    cXyz temp;
    cXyz temp2;
    cXyz temp3;
    if (jntNo == 0) {
        temp2.setall(0.0f);
        MtxPosition(&temp2, &temp);
        if (!chkFlag(HR_FLAG_00000800)) {
            setFlag(HR_FLAG_00000800);
            mPrevAntennaPos.set(temp);
            mAntennaVelocity.setall(0.0f);
            mAntennaOffset.setall(0.0f);
        }

        temp3 = mPrevAntennaPos - temp;

        if (scale.x >= 1.0f && scale.z >= 1.0f) {
            temp3.x /= scale.x;
            temp3.z /= scale.z;
        }
        
        f32 temp4 = std::fabsf(temp3.z);
        if (std::fabsf(temp3.x) > std::fabsf(temp3.z)) {
            temp4 = std::fabsf(temp3.x);
        }

        if (temp4 > 10.0f) {
            f32 fac = 10.f / temp4;
            temp3.x *= fac;
            temp3.z *= fac;
        }

        mAntennaVelocity.x *= 0.8f;
        mAntennaVelocity.z *= 0.8f;

        mAntennaVelocity.x -= mAntennaOffset.x * 0.2f;
        mAntennaVelocity.z -= mAntennaOffset.z * 0.2f;

        mAntennaVelocity.x += temp3.x;
        mAntennaVelocity.z += temp3.z;

        mAntennaOffset.x += mAntennaVelocity.x;
        mAntennaOffset.z += mAntennaVelocity.z;

        mAntennaRotation.x = mAntennaOffset.z * cM_ssin(current.angle.y) - mAntennaOffset.x * cM_scos(current.angle.y);
        mAntennaRotation.z = mAntennaOffset.z * cM_scos(current.angle.y) + mAntennaOffset.x * cM_ssin(current.angle.y);

        mAntennaRotation.x *= 0.05f;
        mAntennaRotation.z *= 0.05f;

        if (mAntennaRotation.x > 1.0f) {
            mAntennaRotation.x = 1.0f;
        }

        if (mAntennaRotation.z > 1.0f) {
            mAntennaRotation.z = 1.0f;
        }

        mPrevAntennaPos.set(temp);

    } else {
        cMtx_YrotM(*calc_mtx, mAntennaRotation.x * 3000.0f);
        cMtx_ZrotM(*calc_mtx, mAntennaRotation.z * 3000.0f);
    }
}

/* 00002868-00002918       .text nodeCallBack_Ht_ant__FP7J3DNodei */
static BOOL nodeCallBack_Ht_ant(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Hr_c* i_this = (daNpc_Hr_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)node;
        int jntNo = joint->getJntNo();

        if (i_this != NULL) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            i_this->node_Ht_ant(jntNo);
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, *calc_mtx);
        }
    }
    return TRUE;
}

/* 00002918-00002A28       .text initTexPatternAnm__10daNpc_Hr_cFb */
BOOL daNpc_Hr_c::initTexPatternAnm(bool i_modify) {
    J3DModelData* modelData = mpHrMorf->getModel()->getModelData();

    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Hr", l_btp_ix_tbl[mTexPatternIdx]);
    JUT_ASSERT(DEMO_SELECT(1768, 1784), m_head_tex_pattern != NULL);

    if (!mBtpAnm.init(modelData, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        return FALSE;
    }

    mBlinkFrame = 0;
    mBlinkTimer = 0;
    return TRUE;
}

/* 00002A28-00002AB4       .text playTexPatternAnm__10daNpc_Hr_cFv */
void daNpc_Hr_c::playTexPatternAnm() {
    if (cLib_calcTimer(&mBlinkTimer) == 0) {
        if (mBlinkFrame >= m_head_tex_pattern->getFrameMax()) {
            mBlinkFrame -= m_head_tex_pattern->getFrameMax();
            mBlinkTimer = cM_rndF(100.0f) + 30.0f;
        } else {
            mBlinkFrame++;
        }
    }
}

/* 00002AB4-00002AF0       .text setTexPtn__10daNpc_Hr_cFSc */
void daNpc_Hr_c::setTexPtn(s8 param_1) {
    if (param_1 != mTexPatternIdx) {
        mTexPatternIdx = param_1;
        initTexPatternAnm(true);
    }
}

/* 00002AF0-00002BB0       .text setAnm__10daNpc_Hr_cFSc */
void daNpc_Hr_c::setAnm(s8 anmIdx) {
    f32 morf = 8.0f;
    if (mAnmIdx == 3 || anmIdx == 3) {
        morf = 18.0f;
    }

    if (mAnmIdx == -1) {
        morf = 0.0f;
    }

    if (anmIdx != mAnmIdx && anmIdx != -1) {
        mAnmIdx = anmIdx;
        mAnmTimer = 0.0f;

        dNpc_setAnm(mpHrMorf, J3DFrameCtrl::EMode_NULL, morf, 1.0f, l_bck_ix_tbl[mAnmIdx], -1, "Hr");
        mAnmLoopCount = 0;
    }
}

/* 00002BB0-00002C1C       .text setAnmStatus__10daNpc_Hr_cFv */
void daNpc_Hr_c::setAnmStatus() {
    switch(mState) {
        case HR_STATE_RT_ANGRY:
            setAnm(2);
            break;
        default:
            if (getShapeType() == 1) {
                setAnm(1);
            } else {
                setAnm(0);
            }
            break;
    }
}

/* 00002C1C-00002C94       .text eventOrder__10daNpc_Hr_cFv */
void daNpc_Hr_c::eventOrder() {
    if (ChkOrder(1)) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
    }
    if (ChkOrder(2)) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        fopAcM_orderSpeakEvent(this);
    }
    if (ChkOrder(4)) {
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
    }
}

/* 00002C94-00002D3C       .text checkOrder__10daNpc_Hr_cFv */
void daNpc_Hr_c::checkOrder() {
    if (eventInfo.mCommand != dEvtCmd_INDEMO_e) {
        if (eventInfo.mCommand == dEvtCmd_INTALK_e && ChkOrder(7)) {
            if (dComIfGp_event_chkTalkXY()) {
                setFlag(HR_FLAG_00000008);
            } else {
                setFlag(HR_FLAG_00000001);
            }
            talkInit();
        }
    }
    ClrOrder();
}

/* 00002D3C-00002D88       .text next_msgStatus__10daNpc_Hr_cFPUl */
u16 daNpc_Hr_c::next_msgStatus(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;

    switch (*pMsgNo) {
        case 0x1906:
        case 0x1933:
        case 0x1934:
        case 0x1938:
            (*pMsgNo)++;
            break;

        default:
            msgStatus = fopMsgStts_MSG_ENDS_e;
            break;
    }

    return msgStatus;
}

/* 00002D88-00002E5C       .text getMsg__10daNpc_Hr_cFv */
u32 daNpc_Hr_c::getMsg() {
    u32 msgNo = 0;
    switch (mState) {
        case 7:
        case 10:
        case 3:
            msgNo = mMsgNo;
            switch(msgNo) {
                case 0x5B3:
                    if (mType == 0) {
                        dComIfGs_onSwitch(getSwbit(), fopAcM_GetRoomNo(this));
                        dComIfGp_setMelodyNum(0);
                    } else {
                        dComIfGp_setMelodyNum(1);
                    }
                    break;
            }
            break;
        case 2:
            msgNo = 0x1901;
            break;
    }
    return msgNo;
}

/* 00002E5C-00002F88       .text setCollision__10daNpc_Hr_cFv */
void daNpc_Hr_c::setCollision() {
    cXyz temp = current.pos;
    f32 temp1 = scale.x * 45.0f;
    f32 temp2 = scale.y * 100.0f;
    mCyl.SetC(temp);
    mCyl.SetR(temp1);
    mCyl.SetH(temp2);
    dComIfG_Ccsp()->Set(&mCyl);
    
    if (mType == 1) {
        temp.y += scale.y * -30.0f;
        temp1 = scale.x * 80.0f;
        temp2 = scale.y * 35.0f;
        mCyl2.SetC(temp);
        mCyl2.SetR(temp1);
        mCyl2.SetH(temp2);
        dComIfG_Ccsp()->Set(&mCyl2);
    }
}

/* 00002F88-00002FC0       .text nextAnm__10daNpc_Hr_cFSci */
void daNpc_Hr_c::nextAnm(s8 i_nextAnm, int loopCount) {
    if (mAnmLoopCount < loopCount) {
        mAnmLoopCount++;
    } else {
        setAnm(i_nextAnm);
    }
}

/* 00002FC0-0000300C       .text msgAnm__10daNpc_Hr_cFUc */
void daNpc_Hr_c::msgAnm(u8 param_1) {
    static s8 msg_anm_table[] = {
        0, 1, 3, 4, 7, 5, 9, 8, 6
    };

    if (mMsgAnmIdx != param_1) {
        mMsgAnmIdx = param_1;
        if (mMsgAnmIdx < 9) {
            setAnm(msg_anm_table[mMsgAnmIdx]);
        }
    }
}

/* 0000300C-00003020       .text talkInit__10daNpc_Hr_cFv */
void daNpc_Hr_c::talkInit() {
    mTalkState = TALK_INIT;
    mMsgAnmIdx = 0xFF;
}

/* 00003020-000031AC       .text talk__10daNpc_Hr_cFv */
u16 daNpc_Hr_c::talk() {
    u16 msgStatus = 0xFF;
    if (mTalkState == TALK_INIT) {
        l_msgId = fpcM_ERROR_PROCESS_ID_e;
        mCurrMsgNo = getMsg();
        mTalkState = TALK_MSG_CREATE;
    } else if (mTalkState != TALK_FINISHED) {
        if(l_msgId == fpcM_ERROR_PROCESS_ID_e) {
            cXyz temp(current.pos);
            temp.y += 100.0f;
            l_msgId = fopMsgM_messageSet(mCurrMsgNo, &temp);
        } else {
            msgAnm(dComIfGp_getMesgAnimeAttrInfo());
            switch(mTalkState) {
                case TALK_MSG_CREATE:
                    l_msg = fopMsgM_SearchByID(l_msgId);
                    if (l_msg != NULL) {
                        mTalkState = TALK_ACTIVE;
                    }
                    break;
                case TALK_ACTIVE:
                    msgStatus = l_msg->mStatus;
                    if(msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
                        l_msg->mStatus = next_msgStatus(&mCurrMsgNo);
                        if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                            fopMsgM_messageSet(mCurrMsgNo);
                        }
                    } else if(msgStatus == fopMsgStts_BOX_CLOSED_e) {
                        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                        mTalkState = TALK_FINISHED;
                    }
                    break;
            }
        }
    }

    return msgStatus;
}

/* 000031AC-00003410       .text init__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::init() {
    if(setAction(&daNpc_Hr_c::wait_action, NULL)) {
        mCloudPos = current.pos;
    }
        
    switch(mType) {
        case 1:

#if VERSION == VERSION_DEMO
            offHide(1);
#else
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2710)) {
                onHide(1);
            } else {
                offHide(1);
            }
#endif
            dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0404);
            break;
        default:
            onHide(1);
            attention_info.flags = fopAc_Attn_ACTION_SPEAK_e|fopAc_Attn_TALKFLAG_CHECK_e;
            attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x5B;
            break;
    }

    J3DModel* model = mpHrMorf->getModel();
    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    mpHrMorf->calc();

    mStts.Init(0xFE, 0xFF, this);
    mStts2.Init(0xFE, 0xFF, this);

    switch(mType) {
        case 1:
            mCyl.Set(dNpc_hr_src);
            mCyl2.Set(dNpc_hr_src);
            break;
        default:
            mCyl.Set(dNpc_cyl_src);
            eventInfo.setEventName("HT_TALK");
            break;
    }

    mCyl.SetStts(&mStts);
    mCyl2.SetStts(&mStts2);
    defaultSetPos(&current.pos);
    mClothes.init();
    return TRUE;
}

/* 00003410-00003484       .text setAttention__10daNpc_Hr_cFb */
void daNpc_Hr_c::setAttention(bool param_1) {
    if (chkFlag(HR_FLAG_00000010) || chkFlag(HR_FLAG_00000100)) {
        return;
    }

    if (!param_1 && mAttnSetCount >= 2) {
        return;
    }

    eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
    attention_info.position.set(mAttnBasePos.x, mAttnBasePos.y + 50.0f, mAttnBasePos.z);
}

/* 00003484-00003520       .text getNowJointY__10daNpc_Hr_cFv */
int daNpc_Hr_c::getNowJointY() {
    daTornado_c* tornadoActor = (daTornado_c*)fopAcM_SearchByID(mProcId);

    int i = 0;
    while (i < 10) {
        f32 jointY = tornadoActor->getJointYPos(i);
        if (current.pos.y + speed.y < jointY) {
            return i;
        }
        i++;
    }
    return i;
}

/* 00003520-00003730       .text getTornadoPos__10daNpc_Hr_cFiP4cXyz */
void daNpc_Hr_c::getTornadoPos(int jointY, cXyz* tornadoPos) {
    daTornado_c* tornadoActor = (daTornado_c*)fopAcM_SearchByID(mProcId);
    cXyz pos1;
    cXyz pos2;

    if(tornadoActor != NULL) {
        if(jointY == 0) {
            tornadoPos->set(tornadoActor->current.pos);
            return;
        } else {
            f32 temp = current.pos.y + speed.y;
            tornadoPos->y = temp;
            if (jointY == 10) {
                tornadoPos->x = tornadoActor->mpModel != NULL ? tornadoActor->mpModel->getAnmMtx(10)[0][3] : tornadoActor->current.pos.x;
                tornadoPos->z = tornadoActor->mpModel != NULL ? tornadoActor->mpModel->getAnmMtx(10)[2][3] : tornadoActor->current.pos.z;
            } else {
                pos1.set(
                    tornadoActor->mpModel != NULL ? tornadoActor->mpModel->getAnmMtx(jointY -1)[0][3] : tornadoActor->current.pos.x,
                    tornadoActor->mpModel != NULL ? tornadoActor->mpModel->getAnmMtx(jointY -1)[1][3] : tornadoActor->current.pos.y,
                    tornadoActor->mpModel != NULL ? tornadoActor->mpModel->getAnmMtx(jointY -1)[2][3] : tornadoActor->current.pos.z
                );

                pos2.set(
                    tornadoActor->mpModel != NULL ? tornadoActor->mpModel->getAnmMtx(jointY)[0][3] : tornadoActor->current.pos.x,
                    tornadoActor->mpModel != NULL ? tornadoActor->mpModel->getAnmMtx(jointY)[1][3] : tornadoActor->current.pos.y,
                    tornadoActor->mpModel != NULL ? tornadoActor->mpModel->getAnmMtx(jointY)[2][3] : tornadoActor->current.pos.z
                );

                f32 ratio = (temp - pos1.y) / (pos2.y - pos1.y);
                tornadoPos->x = ratio * pos2.x + (1.0f - ratio) * pos1.x;
                tornadoPos->z = ratio * pos2.z + (1.0f - ratio) * pos1.z;
            }
        }
    }
}

/* 00003730-00003818       .text rideTornado__10daNpc_Hr_cFv */
bool daNpc_Hr_c::rideTornado() {
    cXyz tornadoPos;
    fopAc_ac_c* actor = fopAcM_SearchByID(mProcId);
    if (actor == NULL) {
        speed.x *= 0.95f;
        speed.y = 0.0f;
        speed.z *= 0.95f;
        return false;
    } else {
        getTornadoPos(getNowJointY(), &tornadoPos);
        speed.x = speed.x * 0.2f + (tornadoPos.x - current.pos.x) * 0.8f;
        speed.z = speed.z * 0.2f + (tornadoPos.z - current.pos.z) * 0.8f;
    }
    return true;
}

/* 00003818-00003848       .text getLookBackMode__10daNpc_Hr_cFv */
u8 daNpc_Hr_c::getLookBackMode() {
    if (chkFlag(HR_FLAG_00000080)) {
        return 0;
    }
    if (chkFlag(HR_FLAG_00000040)) {
        return 1;
    }
    return 0xff;

}

/* 00003848-000039D0       .text lookBack__10daNpc_Hr_cFv */
void daNpc_Hr_c::lookBack() {
    cXyz temp2;
    cXyz temp(0.0f, 0.0f, 0.0f);
    cXyz* dstPos = NULL;
    s16 desiredYRot = current.angle.y;
    bool headOnlyFollow = false;
    switch(getLookBackMode()) {
        case 0:
            m_jnt.setTrn();
            temp2 = dNpc_playerEyePos(-20.0f);
            dstPos = &temp2;
            temp.set(current.pos);
            temp.y = eyePos.y;
            break;
        case 1:
            temp2 = dNpc_playerEyePos(-20.0f);
            dstPos = &temp2;
            temp.set(current.pos);
            temp.y = eyePos.y;
            headOnlyFollow = true;
            break;
        default:
            desiredYRot = current.angle.y;
            headOnlyFollow = true;
            break;
    }


    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&mMaxHeadTurnVelocity, 0x800, 4, 0x800);
    } else {
       mMaxHeadTurnVelocity = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos, temp, desiredYRot, mMaxHeadTurnVelocity, headOnlyFollow);

}

/* 000039D0-00003B44       .text rt_search__10daNpc_Hr_cFv */
bool daNpc_Hr_c::rt_search() {
    daNpc_Hr_c* ac = (daNpc_Hr_c*)fopAcM_searchFromName("Ytrnd00", 0, 0);
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_2710)) {
        return true;
    }

    if(ac != NULL) {
        mProcId = fopAcM_GetID(ac);
        mState = HR_STATE_RT_HIDE;
        mHitCount = 0;
        current.pos.y = home.pos.y - 1500.0f;
        scale.setall(11.0f);
        speed.setall(0.0f);

        JPABaseEmitter* pEmitter = DEMO_SELECT(mpEmitter, mSmokeCallBack.getEmitter());

        if(pEmitter != NULL) {
            pEmitter->setGlobalScale(scale);
        }

        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3D01)) {
            mEventIdx = dComIfGp_evmng_getEventIdx("INTRO_RT");
        } else {
            mEventIdx = dComIfGp_evmng_getEventIdx("INTRO_RT_F");
        }
        mMoveTimer = 0x14;
    }
    return false;

}

/* 00003B44-00003CEC       .text rt_hide__10daNpc_Hr_cFv */
bool daNpc_Hr_c::rt_hide() {
    daShip_c* pShip = dComIfGp_getShipActor();
    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();
    current.angle.y = fopAcM_searchActorAngleY(this, pLink);
    cXyz tornadoPos;
    getTornadoPos(0, &tornadoPos);
    current.pos = tornadoPos;
    current.pos.y -= 1500.0f;
    if(eventInfo.mCommand == dEvtCmd_INDEMO_e) {
        mReturnState = 8;
        mState = HR_STATE_RT_INTRO;
        mStaffIdx = dComIfGp_evmng_getMyStaffId("Hr2");
        setEvFlag(EVFLAG_TORNADO_ACTIVE);
        demoProc();
        mDoAud_seStart(JA_SE_CV_RC_ENTER);
        mDoAud_bgmAllMute(90);
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_3D01);
    } else if (pShip != NULL && pShip->checkTornadoFlg()) {
        if (mMoveTimer > 0) {
            mMoveTimer--;
        } else {
            fopAcM_orderOtherEventId(this, mEventIdx);
            dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0404);
        }
    }
    return true;
}

/* 00003CEC-00003D0C       .text rt_intro__10daNpc_Hr_cFv */
bool daNpc_Hr_c::rt_intro() {
    rt_hit1();
}

/* 00003D0C-00003DD8       .text to_rt_hit__10daNpc_Hr_cFv */
void daNpc_Hr_c::to_rt_hit() {
    mDoAud_seStart(JA_SE_CV_RC_DAMAGE);
    mDoAud_seStart(JA_SE_CV_RC_MODAE_1);
    setAnm(11);
    setTexPtn(1);
    setFlag(HR_FLAG_00000400);
    mHitDelayTimer = 0x52;
}

/* 00003DD8-00003EE4       .text to_rt_tact__10daNpc_Hr_cFv */
void daNpc_Hr_c::to_rt_tact() {
    mDoAud_seStart(JA_SE_CV_RC_DAMAGE);
    mDoAud_seStart(JA_SE_CV_RC_MODAE_2);

    mEventIdx = dComIfGp_evmng_getEventIdx("TACT0_RT");
    mReturnState = mState;
    mState = HR_STATE_RT_HIT_0;
    fopAcM_orderOtherEventId(this, mEventIdx);
    mHitDelayTimer = 0x52;
    mDoAud_subBgmStop();
}

/* 00003EE4-000041D8       .text rt_angry__10daNpc_Hr_cFv */
bool daNpc_Hr_c::rt_angry() {
    cXyz* hitPos;

    daPy_lk_c* pLink = (daPy_lk_c*)daPy_getPlayerLinkActorClass();

    current.angle.x += 0x100;
    f32 currentY = current.pos.y;
    speed.y = home.pos.y + 6000.0f + (1.0f - cM_scos(current.angle.x)) * 1000.0f - currentY;
    scale.setall(11.0f);
    current.angle.y = fopAcM_searchActorAngleY(this, daPy_getPlayerLinkActorClass());
    
    JPABaseEmitter* pEmitter = DEMO_SELECT(mpEmitter, mSmokeCallBack.getEmitter());

    if(pEmitter != NULL) {
        pEmitter->setGlobalScale(scale);
    }

    rideTornado();
    cCcD_Obj* hitObj = NULL;
    if (mCyl2.ChkTgHit()) {
        hitObj = mCyl2.GetTgHitObj();
        hitPos = mCyl2.GetTgHitPosP();
    } else {
        if (mCyl.ChkTgHit()) {
            hitObj = mCyl.GetTgHitObj();
            hitPos = mCyl.GetTgHitPosP();
        }
    }
    daShip_c* pShip = dComIfGp_getShipActor();

    if (pShip->checkTornadoUp()) {
        mState = HR_STATE_RT_WIN;
        fopAcM_OnStatus(this, fopAcStts_UNK800_e);

        setAnm(12);
        mDoAud_seStart(JA_SE_CV_RC_ENTER);
        return true;
    } else if (mHitDelayTimer != 0) {
        return true;

    } else {
        if (chkFlag(HR_FLAG_00000400)) {
            clrFlag(HR_FLAG_00000400);
            setAnm(2);
            setTexPtn(2);
        }

        if (hitObj != NULL && ((hitObj->GetAtType() & AT_TYPE_NORMAL_ARROW) != 0 || (hitObj->GetAtType() & AT_TYPE_FIRE_ARROW) != 0 || (hitObj->GetAtType() & AT_TYPE_ICE_ARROW) != 0 || (hitObj->GetAtType() & AT_TYPE_LIGHT_ARROW) != 0)) {
            cXyz scale(11.0f, 11.0f, 11.0f);
            cXyz temp = *hitPos - pLink->eyePos;
            if(!temp.isZero()) {
                temp.normalize();
                csXyz temp2;
                cM3d_CalcVecZAngle(temp, &temp2);
                dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, hitPos, &temp2, &scale);
            }
            mHitCount++;
            if(mHitCount >= 3) {
                to_rt_tact();
            } else {
                to_rt_hit();
            }
        }

    }
    return true;
}

/* 000041D8-00004208       .text rt_win__10daNpc_Hr_cFv */
bool daNpc_Hr_c::rt_win() {
    speed.y = 0.0f;
    rideTornado();
    return true;
}

/* 00004208-00004328       .text rt_hit0__10daNpc_Hr_cFv */
bool daNpc_Hr_c::rt_hit0() {
    daShip_c* pShip = dComIfGp_getShipActor();

    if(eventInfo.mCommand == dEvtCmd_INDEMO_e) {
        mState = HR_STATE_RT_HIT_1;
        mStaffIdx = dComIfGp_evmng_getMyStaffId("Hr2");
        setEvFlag(EVFLAG_TORNADO_ACTIVE);
        demoProc();
    } else if (pShip->checkTornadoUp()) {
        mState = HR_STATE_RT_WIN;
        fopAcM_OnStatus(this, fopAcStts_UNK800_e);
        setAnm(12);
        mDoAud_seStart(JA_SE_CV_RC_ENTER);

    } else {
        fopAcM_orderOtherEventId(this, mEventIdx);
    }

    speed.y = 0.0f;
    rideTornado();
    return true;
}

/* 00004328-000043D8       .text rt_hit1__10daNpc_Hr_cFv */
bool daNpc_Hr_c::rt_hit1() {
    if(chkEvFlag(EVFLAG_TORNADO_ACTIVE)) {
        rideTornado();
    }

    if(dComIfGp_evmng_endCheck(mEventIdx)) {
        if(mReturnState == 1) {
            onHide(0);
        }
        if(mState == HR_STATE_RT_INTRO) {
            mDoAud_subBgmStart(JA_BGM_DIOCTA_BATTLE);
        }
        endTalk();
        return false;
    }

    demoProc();
    return true;
}

/* 000043D8-0000456C       .text ht_hide__10daNpc_Hr_cFv */
bool daNpc_Hr_c::ht_hide() {
    if (chkFlag(HR_FLAG_00000008)) {
        fopAcM_seStart(this, JA_SE_PRE_TAKT, 0);
        mReturnState = mState;
        mState = HR_STATE_HT_TACT;
        setAnmStatus();
        mStaffIdx = dComIfGp_evmng_getMyStaffId("Hr");
        demoProc();
        dComIfGs_onSwitch(getSwbit(), fopAcM_GetRoomNo(this));
        dComIfGp_event_onHindFlag(-1);

    } else if (chkFlag(HR_FLAG_00000001)) {
        mReturnState = mState;
        mState = HR_STATE_TALK;
        setAnmStatus();
        daPy_getPlayerLinkActorClass()->onPlayerNoDraw();

    } else {
        if (fopAcM_seenActorAngleY(daPy_getPlayerLinkActorClass(), this) < 0x2AAA) {
            SetOrder(1);
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2708)) {
                SetOrder(4);
            }
        }
    }
    return true;
}

/* 0000456C-000045F0       .text wait01__10daNpc_Hr_cFv */
bool daNpc_Hr_c::wait01() {
    if (chkFlag(HR_FLAG_00000001)) {
        mReturnState = mState;
        mState = HR_STATE_TALK;
        setAnmStatus();
    } else {
        SetOrder(1);
    }
    return mpHrMorf->isMorf();
}

/* 000045F0-000045F8       .text wait02__10daNpc_Hr_cFv */
bool daNpc_Hr_c::wait02() {
    return TRUE;
}

/* 000045F8-00004658       .text endTalk__10daNpc_Hr_cFv */
void daNpc_Hr_c::endTalk() {
    mState = mReturnState;
    setAnmStatus();
    dComIfGp_event_reset();
    clrFlag(HR_FLAG_00000008|HR_FLAG_00000001);
    field_0x60A = 5;
}

/* 00004658-000046F4       .text endTact__10daNpc_Hr_cFv */
void daNpc_Hr_c::endTact() {
    onHide(0);
    defaultSetPos(&home.pos);
    current.angle.y = home.angle.y;
    shape_angle.y = home.angle.y;
    speed.setall(0.0f);
    speedF = 0.0f;
    if (mType == 0) {
        dComIfGs_offSwitch(getSwbit(), fopAcM_GetRoomNo(this));
    }
}

/* 000046F4-000047F4       .text setEmitFlash__10daNpc_Hr_cFf */
void daNpc_Hr_c::setEmitFlash(f32 param_1) {
    if(param_1 > 1.0f) {
        param_1 = 1.0f;
    }

    if(param_1 < 0.0f) {
        param_1 = 0.0f;
    }

#if VERSION == VERSION_DEMO
    mpEmitter->setGlobalPrmColor(param_1 * 104.0f + 151.0f, param_1 * 137.0f + 118.0f, param_1 * 86.0f + 169.0f);
    mpEmitter->setGlobalEnvColor(param_1 * 123.0f + 132.0f, param_1 * 143.0f + 112.0f, param_1 * 33.0f + 147.0f);
#else
    JPABaseEmitter* pEmitter = mSmokeCallBack.getEmitter();
    if(pEmitter != NULL) {
        pEmitter->setGlobalPrmColor(param_1 * 104.0f + 151.0f, param_1 * 137.0f + 118.0f, param_1 * 86.0f + 169.0f);
        pEmitter->setGlobalEnvColor(param_1 * 123.0f + 132.0f, param_1 * 143.0f + 112.0f, param_1 * 33.0f + 147.0f);
    }
#endif

}

/* 000047F4-000049B8       .text smokeProc__10daNpc_Hr_cFv */
void daNpc_Hr_c::smokeProc() {
#if VERSION > VERSION_DEMO
    JPABaseEmitter* pEmitter = mSmokeCallBack.getEmitter();
#endif

    if(!chkFlag(HR_FLAG_00000010) && DEMO_SELECT(mpEmitter, pEmitter) != NULL && mType == 1 && mHitDelayTimer != 0) {
        mHitDelayTimer--;
        if(mHitDelayTimer >= 0x50) {
            DEMO_SELECT(mpEmitter, pEmitter)->setGlobalPrmColor(0x7F, 0x5E, 0x91);
            DEMO_SELECT(mpEmitter, pEmitter)->setGlobalEnvColor(0x6C, 0x58, 0x7B);
        } else {
            if(mHitDelayTimer > 0xF) {
                int temp = (mHitDelayTimer - 0x10);
                setEmitFlash((temp % 8) / 7.0f);
            } else {
                setEmitFlash(mHitDelayTimer / 15.0f);

            }
        }

        if(mHitDelayTimer < 0x50) {
            if(mHitDelayTimer > 0xf) {
                f32 ratio = (mHitDelayTimer - 0xf) / 65.0f;
                dKy_actor_addcol_set(0x80, 0x80, 0x5A, ratio);
                dKy_vrbox_addcol_set(0x80, 0x80, 0x5A, ratio);
            } else {
                dKy_actor_addcol_set(0x80, 0x80, 0x5A, 0.0f);
                dKy_vrbox_addcol_set(0x80, 0x80, 0x5A, 0.0f);

            }
        }
    }
}

/* 000049B8-00004A38       .text talk01__10daNpc_Hr_cFv */
bool daNpc_Hr_c::talk01() {
    if (talk() == fopMsgStts_BOX_CLOSED_e) {
        endTalk();
        daPy_getPlayerLinkActorClass()->offPlayerNoDraw();
    }
    return mpHrMorf->isMorf();
}

/* 00004A38-00004AEC       .text ht_tact01__10daNpc_Hr_cFv */
bool daNpc_Hr_c::ht_tact01() {
    if(dComIfGp_evmng_endCheck(mEventIdx)) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2708)) {
            dScnKy_env_light_c& env_light = g_env_light;
            env_light.mWind.mWindVec.set(1.0f, 0.0f, 0.0f); // fake?
            dKyw_tact_wind_set(0, 0);
            dKyw_tact_wind_set_go();
        }
        endTalk();
        endTact();
        return false;
    }

    return demoProc();
}

/* 00004AEC-00004CB4       .text wait_action__10daNpc_Hr_cFPv */
BOOL daNpc_Hr_c::wait_action(void*) {
    if(mActionStatus == ACTION_STARTING) {
        switch(mType) {
            case 0:
                mState = HR_STATE_HT_HIDE;
                eventInfo.setXyCheckCB(&daNpc_hr_XyCheckCB);
                eventInfo.setXyEventCB(&daNpc_hr_XyEventCB);
                break;
            case 1:
#if VERSION == VERSION_DEMO
                mState = HR_STATE_RT_SEARCH;
#else
                if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_2710)) {
                    mState = HR_STATE_WAIT_02;
                } else {
                    mState = HR_STATE_RT_SEARCH;
                }
#endif
                break;
            default:
                mState = HR_STATE_WAIT_01;
                break;
        }
        setAnmStatus();
        mActionStatus++; // set to ACTION_ONGOING
    } else if (mActionStatus != ACTION_ENDING) {
        clrFlag(HR_FLAG_00000100|HR_FLAG_00000080|HR_FLAG_00000040);
        bool temp;
        switch (mState) {
            case HR_STATE_WAIT_01:
                temp = wait01();
                break;
            case HR_STATE_WAIT_02:
                temp = wait02();
                break;
            case HR_STATE_TALK:
                temp = talk01();
                break;
            case HR_STATE_HT_TACT:
                temp = ht_tact01();
                break;
            case HR_STATE_RT_SEARCH:
                temp = rt_search();
                break;
            case HR_STATE_RT_HIDE:
                temp = rt_hide();
                break;
            case HR_STATE_RT_INTRO:
                temp = rt_intro();
                break;
            case HR_STATE_RT_ANGRY:
                temp = rt_angry();
                break;
            case HR_STATE_RT_WIN:
                temp = rt_win();
                break;
            case HR_STATE_RT_HIT_0:
                temp = rt_hit0();
                break;
            case HR_STATE_RT_HIT_1:
                temp = rt_hit1();
                break;
            case HR_STATE_HT_HIDE:
                temp = ht_hide();
                break;
            default:
                temp = false;
                break;
        }
        lookBack();
        setAttention(temp);
        smokeProc();
    }
    return TRUE;
}

/* 00004CB4-00004E6C       .text _draw__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::_draw() {
    J3DModel* hrModel = mpHrMorf->getModel();
    J3DModelData* modelData = hrModel->getModelData();
    J3DModel* antennaModel = mpAntennaMorf->getModel();
    if(chkFlag(HR_FLAG_00000010)) {
        return FALSE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(hrModel, &tevStr);
    g_env_light.setLightTevColorType(mpBrowModel, &tevStr);
    g_env_light.setLightTevColorType(antennaModel, &tevStr);
    mBtpAnm.entry(modelData, mBlinkFrame);

    if(getShapeType() == 1) {
        J3DMaterialTable* bmt = (J3DMaterialTable*)dComIfG_getObjectRes("Hr", HR_BMT_R_BODY);
        modelData->setMaterialTable(bmt, J3DMatCopyFlag_Texture);
        mpHrMorf->entryDL(bmt);
    } else {
        mpHrMorf->entryDL();
    }

    mpBrowModel->setBaseTRMtx(hrModel->getAnmMtx(getHeadJntNum()));
    mDoExt_modelUpdateDL(mpBrowModel);
    antennaModel->setBaseTRMtx(hrModel->getAnmMtx(getHeadJntNum()));
    mpAntennaMorf->updateDL();
    mBtpAnm.remove(modelData);
    if (getShapeType() == 1 && mState == HR_STATE_RT_ANGRY) {
        dSnap_RegistFig(DSNAP_TYPE_HR, this, 1.0f, 1.0f, 1.0f);
    }

    return TRUE;
}

/* 00004E6C-000050FC       .text _execute__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::_execute() {
    m_jnt.setParam(
    /* mMaxBackboneX */ 0,
    /* mMaxBackboneY */ 0x1C70,
    /* mMinBackboneX */ 0,
    /* mMinBackboneY */ -0x1C70,
    /* mMaxHeadX */ 0x1FFE,
    /* mMaxHeadY */ 9000,
    /* mMinHeadX */ -0x1FFE,
    /* mMinHeadY */ -9000,
    /* mMaxTurnStep */ 0x1000
    );

    playTexPatternAnm();

    mAnmEnded = mpHrMorf->play(&eyePos, 0, 0);
    if(mpHrMorf->getFrame() < mAnmTimer) {
        mAnmEnded = 1;
    }
    mAnmTimer = mpHrMorf->getFrame();
    
    if(mAnmEnded != 0) {
        switch(mAnmIdx) {
            case 3:
                nextAnm(0, 2);
                break;
            case 4:
                nextAnm(0, 3);
                break;
            case 5:
                nextAnm(1, 3);
                break;
            case 8:
                nextAnm(1, 3);
                break;
            case 9:
                nextAnm(1, 3);
                break;
            case 10:
                nextAnm(2, 2);
                break;
            case 2:
                nextAnm(10,(int)(cM_rndF(4.0f) + 4.0f));
                break;
        }
    }
    checkOrder();
    (this->*mCurrActionFunc)(NULL);
    eventOrder();
    shape_angle.y = current.angle.y;
    if (!chkFlag(HR_FLAG_00000020)) {
        fopAcM_posMove(this, mStts.GetCCMoveP());
    }

    clrFlag(HR_FLAG_00000020);
    tevStr.mRoomNo = current.roomNo;
    J3DModel* hrModel = mpHrMorf->getModel();
    hrModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    hrModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpHrMorf->calc();
    if(chkFlag(HR_FLAG_00000010)) {
        mCyl.ClrCoSet();
    } else {
        if(mType != 1) {
            mCyl.OnCoSetBit();
        }
        setCollision();
    }
    mClothes.proc();
    return TRUE;
}

/* 000050FC-00005188       .text _delete__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::_delete() {
    dComIfG_resDelete(&mPhs, "Hr");
    if(mpHrMorf != NULL) {
        mpHrMorf->stopZelAnime();
    }

    mSmokeCallBack.end();
    if(mType == 1) {
        dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0404);
    }

    mClothes.remove();
    return TRUE;
}

/* 00005188-000051A8       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Hr_c*)i_this)->CreateHeap();
}

/* 000051A8-000052C4       .text _create__10daNpc_Hr_cFv */
cPhs_State daNpc_Hr_c::_create() {

    fopAcM_ct_Retail(this, daNpc_Hr_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Hr");
    if (state == cPhs_COMPLEATE_e) {
    fopAcM_ct_Demo(this, daNpc_Hr_c);
        switch(fopAcM_GetName(this)) {
            case PROC_NPC_HR:
                switch (getShapeType()) {
                    case 1:
                        mType = 1;
                        break;
                    default:
                        mType = 0;
                        break;
                }
                break;
            default:
                return cPhs_ERROR_e;
        }

        if (!fopAcM_entrySolidHeap(this, &CheckCreateHeap, 0xB7B0)) {
#if VERSION > VERSION_DEMO
            mpHrMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }

        cullMtx = mpHrMorf->getModel()->getBaseTRMtx();
        if (!init()) {
#if VERSION > VERSION_DEMO
            mpHrMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }
    }
    return state;
}

daNpc_Hr_c::daNpc_Hr_c() {}

/* 000057E4-00005CE8       .text CreateHeap__10daNpc_Hr_cFv */
BOOL daNpc_Hr_c::CreateHeap() {
    static int brow_bdl_table[] = {
        HR_BDL_H_BROW,
        HR_BDL_R_BROW
    };

    static int ant_bdl_table[] = {
        HR_BDL_H_ANT,
        HR_BDL_R_ANT
    };

    static u32 ant_bck_table[] = {
        HR_BCK_H_ANT,
        HR_BCK_R_ANT
    };

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Hr", HR_BDL_HR);
    JUT_ASSERT(DEMO_SELECT(3341, 3392), modelData);

    mpHrMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Hr", HR_BCK_H_WAIT01),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x15021222
    );
    
    if (mpHrMorf == NULL || mpHrMorf->getModel() == NULL) {
        return FALSE;
    }

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(DEMO_SELECT(3363, 3414), m_jnt.getHeadJntNum() >= 0);

    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone1"));
    JUT_ASSERT(DEMO_SELECT(3368, 3419), m_jnt.getBackboneJntNum() >= 0);

    m_waist_jnt_num = modelData->getJointName()->getIndex("waist");
    JUT_ASSERT(DEMO_SELECT(3372, 3423), m_waist_jnt_num >= 0);


    J3DModelData* browModelData = (J3DModelData*)dComIfG_getObjectRes("Hr", brow_bdl_table[getShapeType()]);
    JUT_ASSERT(DEMO_SELECT(3383, 3434), browModelData);

    mpBrowModel = mDoExt_J3DModel__create(browModelData, 0x80000, 0x11000022);

    if(mpBrowModel == NULL) {
        return FALSE;
    }

    J3DModelData* antModelData = (J3DModelData*)dComIfG_getObjectRes("Hr", ant_bdl_table[getShapeType()]);
    JUT_ASSERT(DEMO_SELECT(3404, 3455), antModelData);

    mpAntennaMorf = new mDoExt_McaMorf(
        antModelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Hr", ant_bck_table[getShapeType()]),
        J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x11000022
    );

    if (mpAntennaMorf == NULL || mpAntennaMorf->getModel() == NULL) {
        return FALSE;
    }

    if(getShapeType() == 1) {
        mTexPatternIdx = 2;
    } else {
        mTexPatternIdx = 0;
    }

#if VERSION == VERSION_DEMO
    initTexPatternAnm(false);
#else
    if(!initTexPatternAnm(false)) {
        return FALSE;
    }
#endif

    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == getHeadJntNum() || i == getBackboneJntNum() || i == m_waist_jnt_num) {
            mpHrMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Hr);
        }
    }

    mpHrMorf->getModel()->setUserArea((u32)this);

    for(u16 i = 0; i < antModelData->getJointNum(); i++) {
        mpAntennaMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ht_ant);
    }
    mpAntennaMorf->getModel()->setUserArea((u32)this);
    
    return TRUE;
}

/* 00005CE8-00005D08       .text daNpc_Hr_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Hr_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Hr_c*)i_this)->_create();
}

/* 00005D08-00005D28       .text daNpc_Hr_Delete__FP10daNpc_Hr_c */
static BOOL daNpc_Hr_Delete(daNpc_Hr_c* i_this) {
    return ((daNpc_Hr_c*)i_this)->_delete();
}

/* 00005D28-00005D48       .text daNpc_Hr_Execute__FP10daNpc_Hr_c */
static BOOL daNpc_Hr_Execute(daNpc_Hr_c* i_this) {
    return ((daNpc_Hr_c*)i_this)->_execute();
}

/* 00005D48-00005D68       .text daNpc_Hr_Draw__FP10daNpc_Hr_c */
static BOOL daNpc_Hr_Draw(daNpc_Hr_c* i_this) {
    return ((daNpc_Hr_c*)i_this)->_draw();
}

/* 00005D68-00005D70       .text daNpc_Hr_IsDelete__FP10daNpc_Hr_c */
static BOOL daNpc_Hr_IsDelete(daNpc_Hr_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Hr_Method = {
    (process_method_func)daNpc_Hr_Create,
    (process_method_func)daNpc_Hr_Delete,
    (process_method_func)daNpc_Hr_Execute,
    (process_method_func)daNpc_Hr_IsDelete,
    (process_method_func)daNpc_Hr_Draw,
};

actor_process_profile_definition g_profile_NPC_HR = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_HR,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Hr_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_HR,
    /* Actor SubMtd */ &l_daNpc_Hr_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
