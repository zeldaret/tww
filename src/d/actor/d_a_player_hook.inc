/**
 * d_a_player_hook.inc
 *
 * Code relating to the Hookshot item.
 *
 * This file is not a standalone translation unit and is instead directly
 * included into d_a_player_main.cpp.
 *
 * The original name of this file is known because of an assert contained within
 * a function from this file.
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "SSystem/SComponent/c_math.h"
#include "d/actor/d_a_hookshot.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_player_main.h"
#include "f_op/f_op_actor_mng.h"

/* 8014AB5C-8014ABA0       .text checkHookshotReturn__9daPy_lk_cFv */
BOOL daPy_lk_c::checkHookshotReturn() {
    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
    if (mEquipItem != dItem_HOOKSHOT_e || hookshot == NULL) {
        return false;
    }

    return hookshot->checkPull() || hookshot->checkReturn();
}

/* 8014ABA0-8014ABF4       .text setHookshotCarryOffset__9daPy_lk_cFUiPC4cXyz */
BOOL daPy_lk_c::setHookshotCarryOffset(fpc_ProcID carryActorID, const cXyz* offset) {
    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
    if (mEquipItem != dItem_HOOKSHOT_e || hookshot == NULL) {
        return false;
    }
    if (carryActorID != hookshot->getCarryActorID()) {
        return false;
    }

    hookshot->setCarryOffset(offset);
    return true;
}

/* 8014ABF4-8014ACCC       .text setHookshotModel__9daPy_lk_cFv */
void daPy_lk_c::setHookshotModel() {
    J3DAnmTransform* bck = getItemAnimeResource(LKANM_BCK_HOOKSHOTA);
    JKRHeap* oldHeap = setItemHeap();
    J3DModelData* tmp_modelData = initModel(&mpEquipItemModel, LINK_BDL_HOOKSHOT, 0x37221222);
    int ret = mSwordAnim.init(tmp_modelData, bck, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) {
        JUT_ASSERT(100, FALSE);
    }
    mDoExt_setCurrentHeap(oldHeap);
    m35EC = 0.0f;
}

/* 8014ACCC-8014B02C       .text setHookshotSight__9daPy_lk_cFv */
void daPy_lk_c::setHookshotSight() {
    cXyz sp50(
        cM_ssin(shape_angle.y) * cM_scos(mBodyAngle.x),
        -cM_ssin(mBodyAngle.x),
        cM_scos(shape_angle.y) * cM_scos(mBodyAngle.x)
    );
    cXyz sp44;
    cXyz sp38;
    sp38 = mHookshotRootPos + sp50 * 1500.0f;
    sp44 = mHookshotRootPos - sp50 * 60.0f;
    mRopeLinChk.Set(&sp44, &sp38, this);

    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
    BOOL r30 = dComIfG_Bgsp()->LineCross(&mRopeLinChk);
    mSightPacket.onDrawFlg();
    if (r30 || hookshot->getSightHit()) {
        BOOL r3;
        if (r30 && mHookshotRootPos.abs2(current.pos) > mRopeLinChk.GetCross().abs2(current.pos)) {
            mSightPacket.setPos(&mHookshotRootPos);
            r3 = FALSE;
        } else if (!r30) {
            mSightPacket.setPos(hookshot->getObjSightCrossPos());
            r3 = TRUE;
        } else if (!hookshot->getSightHit()) {
            mSightPacket.setPos(&mRopeLinChk.GetCross());
            r3 = FALSE;
        } else if (mRopeLinChk.GetCross().abs2(mHookshotRootPos) >
                   hookshot->getObjSightCrossPos()->abs2(mHookshotRootPos))
        {
            mSightPacket.setPos(hookshot->getObjSightCrossPos());
            r3 = TRUE;
        } else {
            mSightPacket.setPos(&mRopeLinChk.GetCross());
            r3 = FALSE;
        }

        if ((r3 && hookshot->getObjHookFlg()) || (!r3 && dComIfG_Bgsp()->ChkPolyHSStick(mRopeLinChk))) {
            if (mSightPacket.getLockFlg()) {
                mSightPacket.incFrame();
                if (mSightPacket.checkSEFrame()) {
                    seStartSystem(JA_SE_INDICATOR_1);
                }
            } else {
                mSightPacket.onLockFlg();
                seStartSystem(JA_SE_INDICATOR_1);
            }
        } else {
            mSightPacket.offLockFlg();
        }
    } else {
        mSightPacket.setPos(&sp38);
        mSightPacket.offLockFlg();
    }
}

/* 8014B02C-8014B05C       .text freeHookshotItem__9daPy_lk_cFv */
void daPy_lk_c::freeHookshotItem() {
    if (mEquipItem != dItem_HOOKSHOT_e) {
        return;
    }
    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
    if (hookshot == NULL) {
        return;
    }
    if (hookshot->checkWait()) {
        return;
    }
    hookshot->setReturn();
}

/* 8014B05C-8014B2B8       .text checkNextActionHookshotReady__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionHookshotReady() {
    static JGeometry::TVec3<f32> eff_scale(1.0f, 1.0f, 0.0f);
    static JGeometry::TVec3<f32> eff_dscale(0.2f, 0.2f, 0.2f);
    static JGeometry::TVec3<f32> eff_pscale(0.4f, 0.4f, 0.4f);
    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();

    if (hookshot->checkWait()) {
        if (itemButton() && mEquipItem == getReadyItem() && m355C == 0) {
            m355E = 1;
        } else if (!itemButton() && m355E != 0) {
            m355E = 0;
            hookshot->setShot();
            mVelocity = 0.0f;
            daPy_matAnm_c::offMabaFlg();
            seStartOnlyReverb(JA_SE_LK_HS_SHOOT);
            voiceStart(41);
            resetFootEffect();
            if (mDirection != DIR_LEFT) {
                mDirection = DIR_LEFT;
            }
            current.angle.y = shape_angle.y + 0x4000;
            onModeFlg(ModeFlg_00000001);
            m3598 = 0.0f;
            setBlendAtnMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
            mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
            mFrameCtrlUnder[UNDER_MOVE1_e].setRate(0.0f);
            mFrameCtrlUpper[UPPER_MOVE0_e].setRate(daPy_HIO_atnMove_c0::m.field_0x24);
            mFrameCtrlUpper[UPPER_MOVE1_e].setRate(0.0f);
            mFrameCtrlUpper[UPPER_MOVE2_e].setRate(0.0f);
            return true;
        }
    } else {
        if (hookshot->checkShot()) {
            if (itemTrigger() && mEquipItem == getReadyItem()) {
                hookshot->setReturn();
            }
            return true;
        }
        if (hookshot->checkReturn()) {
            return true;
        }
        if (hookshot->checkPull()) {
            procHookshotFly_init();
            return true;
        }
    }

    if (m355C > 0) {
        m355C--;
    }

    return cancelItemUpperReadyAnime();
}

/* 8014B2B8-8014B350       .text checkNextHookshotMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextHookshotMode() {
    if (!checkHookshotReadyAnime()) {
        m355C = 10;
        m355E = 0;
        seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
    }
    if (checkAttentionLock()) {
        return procHookshotMove_init();
    } else {
        return procHookshotSubject_init();
    }
}

/* 8014B350-8014B3F4       .text procHookshotSubject_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotSubject_init() {
    if (mCurProc == daPyProc_HOOKSHOT_SUBJECT_e) {
        return false;
    }

    commonProcInit(daPyProc_HOOKSHOT_SUBJECT_e);

    mVelocity = 0.0f;

    setActAnimeUpper(LKANM_BCK_HOOKSHOTWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
    setSingleMoveAnime(ANM_ATNLS, 0.0f, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);

    dComIfGp_setPlayerStatus0(0, daPyStts0_HOOKSHOT_AIM_e);

    return true;
}

/* 8014B3F4-8014B518       .text procHookshotSubject__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotSubject() {
    if (!checkItemModeActorPointer()) {
        return true;
    }

    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
    if (hookshot->checkWait()) {
        dComIfGp_setDoStatus(dActStts_RETURN_e);
    }

    if (checkAttentionLock()) {
        setSpeedAndAngleAtn();
    }

    mSightPacket.offDrawFlg();

    if (checkNextMode(0) == 0 && hookshot->checkWait() && setBodyAngleToCamera() && hookshot->checkWait()) {
        setHookshotSight();
    }

    if (hookshot->checkWait()) {
        dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK40000_e);
    } else {
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK40000_e);
    }

    return true;
}

/* 8014B518-8014B5E8       .text procHookshotMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotMove_init() {
    if (mCurProc == daPyProc_HOOKSHOT_MOVE_e) {
        return false;
    }

    commonProcInit(daPyProc_HOOKSHOT_MOVE_e);
    if (mDirection == DIR_RIGHT) {
        current.angle.y = shape_angle.y + -0x4000;
    } else {
        mDirection = DIR_LEFT;
        current.angle.y = shape_angle.y + 0x4000;
    }
    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
    if (hookshot->checkWait()) {
        setActAnimeUpper(LKANM_BCK_HOOKSHOTWAIT, UPPER_MOVE2_e, 1.0f, 0.0f, -1, -1.0f);
        setBlendAtnMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    }
    dComIfGp_setPlayerStatus0(0, daPyStts0_HOOKSHOT_AIM_e);
    return true;
}

/* 8014B5E8-8014B74C       .text procHookshotMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotMove() {
    if (!checkItemModeActorPointer()) {
        return true;
    }

    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
    mSightPacket.offDrawFlg();
    if (hookshot->checkWait()) {
        if (mpAttnActorLockOn != NULL) {
            setSpeedAndAngleAtnActor();
        } else if (m355E == 0 && !checkAttentionLock()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        } else {
            setSpeedAndAngleAtn();
        }
    }
    if (!checkNextMode(0)) {
        f32 fVar1 = -1.0f;
        if (std::fabsf(mVelocity) < 0.001f) {
            onModeFlg(ModeFlg_00000001);
            if (mDirection != DIR_LEFT) {
                mDirection = DIR_LEFT;
                fVar1 = daPy_HIO_basic_c0::m.field_0xC;
            }
            current.angle.y = shape_angle.y + 0x4000;
        } else {
            offModeFlg(ModeFlg_00000001);
        }
        if (hookshot->checkWait()) {
            setBlendAtnMoveAnime(fVar1);
            setBodyAngleXReadyAnime();
        }
    }
    return true;
}

/* 8014B74C-8014B854       .text procHookshotFly_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotFly_init() {
    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
    commonProcInit(daPyProc_HOOKSHOT_FLY_e);
    for (int i = 0; i < 3; i++) {
        mAcchCir[i].SetWallR(70.0f);
    }
    mAcchCir[0].SetWallH(-25.0f);
    mAcchCir[1].SetWallH(0.0f);
    mAcchCir[2].SetWallH(50.0f);
    setSingleMoveAnime(ANM_HOOKSHOTJMP, 1.0f, 0.0f, -1, 0.0f);
    mBodyAngle.x = 0;
    gravity = 0.0f;
    mVelocity = 0.0f;
    m34C2 = 11;
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK10_e);
    voiceStart(6);
    m370C = old.pos;
    shape_angle.x = hookshot->shape_angle.x;
    shape_angle.y = hookshot->shape_angle.y;
    return true;
}

/* 8014B854-8014BA84       .text procHookshotFly__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotFly() {
    if (!checkItemModeActorPointer()) {
        voiceStart(10);
        return true;
    }

    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
    if (!hookshot->checkPull()) {
        if (hookshot->checkShipRideFlg() && procShipJumpRide_init()) {
            return true;
        }
        if (!mAcch.ChkGroundHit() && changeFrontWallTypeProc()) {
            voiceStart(10);
            return true;
        }

        mLinkLinChk.Set(&m370C, &current.pos, this);
        if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
            current.pos = mLinkLinChk.GetCross();
        }
        current.pos.x = hookshot->current.pos.x - 35.0f * cM_ssin(shape_angle.y);
        current.pos.z = hookshot->current.pos.z - 35.0f * cM_scos(shape_angle.y);
        m3688 = current.pos;
        m35F0 = m3688.y;
        m35F4 = m3688.y;
        if (mAcch.ChkGroundHit()) {
            checkNextMode(0);
        } else {
            procFall_init(1, 0.0f);
        }
        voiceStart(10);
    } else {
        shape_angle.x = hookshot->shape_angle.x;
        shape_angle.y = hookshot->shape_angle.y;
        current.angle.y = shape_angle.y;
        current.pos += hookshot->getMoveVec();
        m370C = old.pos;
    }
    return true;
}
