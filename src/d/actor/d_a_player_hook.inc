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

#include "SSystem/SComponent/c_math.h"
#include "d/actor/d_a_hookshot.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_player_main.h"
#include "f_op/f_op_actor_mng.h"

/* 8014AB5C-8014ABA0       .text checkHookshotReturn__9daPy_lk_cFv */
BOOL daPy_lk_c::checkHookshotReturn() {
    daHookshot_c *hookshot = (daHookshot_c *)mActorKeepEquip.getActor();

    if ((mEquipItem != dItem_HOOKSHOT_e) || (hookshot == NULL)) {
        return false;
    } else {
        return ((fopAcM_GetParam(hookshot) == 3) ||
                (fopAcM_GetParam(hookshot) == 2));
    }
}

/* 8014ABA0-8014ABF4       .text setHookshotCarryOffset__9daPy_lk_cFUiPC4cXyz */
BOOL daPy_lk_c::setHookshotCarryOffset(fpc_ProcID param_0,
                                       const cXyz *param_1) {
    daHookshot_c *hookshot = (daHookshot_c *)mActorKeepEquip.getActor();

    if ((mEquipItem != dItem_HOOKSHOT_e) || (hookshot == NULL)) {
        return false;
    } else {
        if (param_0 != hookshot->mCarryActorID) {
            return false;
        }
        hookshot->m50C = *param_1;
        return true;
    }
}

/* 8014ABF4-8014ACCC       .text setHookshotModel__9daPy_lk_cFv */
void daPy_lk_c::setHookshotModel() {
    J3DAnmTransform *bck = getItemAnimeResource(LKANM_BCK_HOOKSHOTA);
    JKRHeap *oldHeap = setItemHeap();
    J3DModelData *tmp_modelData =
        initModel(&mpEquipItemModel, LINK_BDL_HOOKSHOT, 0x37221222);
    int ret = mSwordAnim.init(tmp_modelData, bck, false,
                              J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) {
        JUT_ASSERT(100, FALSE);
    }
    mDoExt_setCurrentHeap(oldHeap);
    m35EC = 0.0f;
}

/* 8014ACCC-8014B02C       .text setHookshotSight__9daPy_lk_cFv */
void daPy_lk_c::setHookshotSight() {
    /* Nonmatching - floats */
    cXyz sp50(cM_ssin(shape_angle.y) * cM_scos(mBodyAngle.x),
              -cM_ssin(mBodyAngle.x),
              cM_scos(shape_angle.y) * cM_scos(mBodyAngle.x));
    cXyz sp44;
    cXyz sp38;
    sp38 = mHookshotRootPos + sp50 * 1500.0f;
    sp44 = mHookshotRootPos - sp50 * 60.0f;
    mRopeLinChk.Set(&sp44, &sp38, this);
    daHookshot_c *hookshot = (daHookshot_c *)mActorKeepEquip.getActor();
    BOOL r30 = dComIfG_Bgsp()->LineCross(&mRopeLinChk);
    mSightPacket.onDrawFlg();
    if (r30 || hookshot->mCps.ChkAtHit()) {
        BOOL r3;
        if (r30 && mHookshotRootPos.abs2(current.pos) >
                       mRopeLinChk.GetCross().abs2(current.pos)) {
            mSightPacket.setPos(&mHookshotRootPos);
            r3 = FALSE;
        } else if (!r30) {
            mSightPacket.setPos(&hookshot->m2CC);
            r3 = TRUE;
        } else if (!hookshot->mCps.ChkAtHit()) {
            mSightPacket.setPos(&mRopeLinChk.GetCross());
            r3 = FALSE;
        } else if (mRopeLinChk.GetCross().abs2(mHookshotRootPos) >
                   hookshot->m2CC.abs2(mHookshotRootPos)) {
            mSightPacket.setPos(&hookshot->m2CC);
            r3 = TRUE;
        } else {
            mSightPacket.setPos(&mRopeLinChk.GetCross());
            r3 = FALSE;
        }

        if ((r3 && hookshot->m2B0) ||
            (!r3 && dComIfG_Bgsp()->ChkPolyHSStick(mRopeLinChk))) {
            if (mSightPacket.getLockFlg()) {
                mSightPacket.incFrame();
                if (mSightPacket.checkSEFrame()) {
                    mDoAud_seStart(JA_SE_INDICATOR_1);
                }
            } else {
                mSightPacket.onLockFlg();
                mDoAud_seStart(JA_SE_INDICATOR_1);
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
    daHookshot_c *hookshot = (daHookshot_c *)mActorKeepEquip.getActor();
    if (hookshot == NULL) {
        return;
    }
    if (fopAcM_GetParam(hookshot) == 0) {
        return;
    }
    fopAcM_SetParam(hookshot, 2);
    return;
}

/* 8014B05C-8014B2B8       .text checkNextActionHookshotReady__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionHookshotReady() {
    /* Nonmatching - sbss */
    static JGeometry::TVec3<f32> eff_scale(1.0f, 1.0f, 0.0f);
    static JGeometry::TVec3<f32> eff_dscale(0.2f, 0.2f, 0.2f);
    static JGeometry::TVec3<f32> eff_pscale(0.4f, 0.4f, 0.4f);
    daHookshot_c *hookshot = (daHookshot_c *)mActorKeepEquip.getActor();

    if (fopAcM_GetParam(hookshot) == 0) {
        if (((itemButton()) && (mEquipItem == getReadyItem())) &&
            (m355C == 0)) {
            m355E = 1;
        } else {
            if ((!itemButton()) && (m355E != 0)) {
                m355E = 0;
                fopAcM_SetParam(hookshot, 1);
                mVelocity = 0.0f;
                daPy_matAnm_c::m_maba_flg = 0;
                daPy_matAnm_c::m_maba_timer = 1;
                seStartOnlyReverb(JA_SE_LK_HS_SHOOT);
                voiceStart(41);
                resetFootEffect();
                if (m34B8 != 2) {
                    m34B8 = 2;
                }
                current.angle.y = shape_angle.y + 0x4000;
                onModeFlg(ModeFlg_00000001);
                m3598 = 0.0f;
                setBlendAtnMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
                mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
                mFrameCtrlUnder[UNDER_MOVE1_e].setRate(0.0f);
                mFrameCtrlUpper[UPPER_MOVE0_e].setRate(
                    daPy_HIO_atnMove_c0::m.field_0x24);
                mFrameCtrlUpper[UPPER_MOVE1_e].setRate(0.0f);
                mFrameCtrlUpper[UPPER_MOVE2_e].setRate(0.0f);
                return true;
            }
        }
    } else {
        if (fopAcM_GetParam(hookshot) == 1) {
            if ((itemTrigger()) && (mEquipItem == getReadyItem())) {
                fopAcM_SetParam(hookshot, 2);
            }
            return true;
        }
        if (fopAcM_GetParam(hookshot) == 2) {
            return true;
        }
        if (fopAcM_GetParam(hookshot) == 3) {
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
    if (mpAttention->Lockon()) {
        procHookshotMove_init();
    } else {
        procHookshotSubject_init();
    }
    return;
}

/* 8014B350-8014B3F4       .text procHookshotSubject_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotSubject_init() {
    if (mCurProc == daPyProc_HOOKSHOT_SUBJECT_e) {
        return false;
    }

    commonProcInit(daPyProc_HOOKSHOT_SUBJECT_e);

    mVelocity = 0.0f;

    setActAnimeUpper(LKANM_BCK_HOOKSHOTWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1,
                     -1.0f);
    setSingleMoveAnime(ANM_ATNLS, 0.0f, 0.0f, -1,
                       daPy_HIO_basic_c0::m.field_0xC);

    dComIfGp_setPlayerStatus0(0, daPyStts0_HOOKSHOT_AIM_e);

    return true;
}

/* 8014B3F4-8014B518       .text procHookshotSubject__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotSubject() {
    if (!checkItemModeActorPointer()) {
        return true;
    }

    daHookshot_c *hookshot = (daHookshot_c *)mActorKeepEquip.getActor();
    if (fopAcM_GetParam(hookshot) == 0) {
        dComIfGp_setDoStatus(7);
    }

    if (mpAttention->Lockon()) {
        setSpeedAndAngleAtn();
    }

    mSightPacket.offDrawFlg();

    if (checkNextMode(0) == 0 && fopAcM_GetParam(hookshot) == 0 &&
        setBodyAngleToCamera() && fopAcM_GetParam(hookshot) == 0) {
        setHookshotSight();
    }

    if (fopAcM_GetParam(hookshot) == 0) {
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
    } else {
        commonProcInit(daPyProc_HOOKSHOT_MOVE_e);
        if (m34B8 == 3) {
            current.angle.y = shape_angle.y + -0x4000;
        } else {
            m34B8 = 2;
            current.angle.y = shape_angle.y + 0x4000;
        }
        daHookshot_c *hookshot = (daHookshot_c *)mActorKeepEquip.getActor();
        if (fopAcM_GetParam(hookshot) == 0) {
            setActAnimeUpper(LKANM_BCK_HOOKSHOTWAIT, UPPER_MOVE2_e, 1.0f, 0.0f,
                             -1, -1.0f);
            setBlendAtnMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
        }
        dComIfGp_setPlayerStatus0(0, daPyStts0_HOOKSHOT_AIM_e);
        return true;
    }
}

/* 8014B5E8-8014B74C       .text procHookshotMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotMove() {
    if (!checkItemModeActorPointer()) {
        return true;
    }
    daHookshot_c *hookshot = (daHookshot_c *)mActorKeepEquip.getActor();
    mSightPacket.offDrawFlg();
    if (fopAcM_GetParam(hookshot) == 0) {
        if (mpAttnActorLockOn != NULL) {
            setSpeedAndAngleAtnActor();
        } else if (m355E == 0 && !mpAttention->Lockon()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        } else {
            setSpeedAndAngleAtn();
        }
    }
    if (!checkNextMode(0)) {
        f32 fVar1 = -1.0f;
        if (std::fabsf(mVelocity) < 0.001f) {
            onModeFlg(ModeFlg_00000001);
            if (m34B8 != 2) {
                m34B8 = 2;
                fVar1 = daPy_HIO_basic_c0::m.field_0xC;
            }
            current.angle.y = shape_angle.y + 0x4000;
        } else {
            offModeFlg(ModeFlg_00000001);
        }
        if (fopAcM_GetParam(hookshot) == 0) {
            setBlendAtnMoveAnime(fVar1);
            setBodyAngleXReadyAnime();
        }
    }
    return true;
}

/* 8014B74C-8014B854       .text procHookshotFly_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotFly_init() {
    /* Nonmatching - floats */
    daHookshot_c *hookshot = (daHookshot_c *)mActorKeepEquip.getActor();
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
    } else {
        daHookshot_c *hookshot = (daHookshot_c *)mActorKeepEquip.getActor();
        if (fopAcM_GetParam(hookshot) != 3) {
            if ((hookshot->m2A2 != 0) && (procShipJumpRide_init())) {
                return true;
            }
            if ((!mAcch.ChkGroundHit()) && (changeFrontWallTypeProc())) {
                voiceStart(10);
                return true;
            } else {
                mLinkLinChk.Set(&m370C, &current.pos, this);
                if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                    current.pos = mLinkLinChk.GetCross();
                }
                current.pos.x =
                    hookshot->current.pos.x - 35.0f * cM_ssin(shape_angle.y);
                current.pos.z =
                    hookshot->current.pos.z - 35.0f * cM_scos(shape_angle.y);
                m3688 = current.pos;
                m35F0 = m3688.y;
                m35F4 = m3688.y;
                if (mAcch.ChkGroundHit()) {
                    checkNextMode(0);
                } else {
                    procFall_init(1, 0.0f);
                }
                voiceStart(10);
            }
        } else {
            shape_angle.x = hookshot->shape_angle.x;
            shape_angle.y = hookshot->shape_angle.y;
            current.angle.y = shape_angle.y;
            current.pos += hookshot->getMoveVec();
            m370C = old.pos;
        }
    }
    return true;
}
