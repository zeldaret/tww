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
    /* Nonmatching */
}

/* 8014ABA0-8014ABF4       .text setHookshotCarryOffset__9daPy_lk_cFUiPC4cXyz */
BOOL daPy_lk_c::setHookshotCarryOffset(fpc_ProcID, const cXyz*) {
    /* Nonmatching */
}

/* 8014ABF4-8014ACCC       .text setHookshotModel__9daPy_lk_cFv */
void daPy_lk_c::setHookshotModel() {
    /* Nonmatching */
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
    if (r30 || hookshot->mCps.ChkAtHit()) {
        BOOL r3;
        if (r30 && mHookshotRootPos.abs2(current.pos) > mRopeLinChk.GetCross().abs2(current.pos)) {
            mSightPacket.setPos(&mHookshotRootPos);
            r3 = FALSE;
        } else if (!r30) {
            mSightPacket.setPos(&hookshot->m2CC);
            r3 = TRUE;
        } else if (!hookshot->mCps.ChkAtHit()) {
            mSightPacket.setPos(&mRopeLinChk.GetCross());
            r3 = FALSE;
        } else if (mRopeLinChk.GetCross().abs2(mHookshotRootPos) > hookshot->m2CC.abs2(mHookshotRootPos)) {
            mSightPacket.setPos(&hookshot->m2CC);
            r3 = TRUE;
        } else {
            mSightPacket.setPos(&mRopeLinChk.GetCross());
            r3 = FALSE;
        }
        
        if (
            (r3 && hookshot->m2B0) ||
            (!r3 && dComIfG_Bgsp()->ChkPolyHSStick(mRopeLinChk))
        ) {
            if(mSightPacket.getLockFlg()) {
                mSightPacket.incFrame();
                if(mSightPacket.checkSEFrame()) {
                    mDoAud_seStart(JA_SE_INDICATOR_1);
                }
            }
            else {
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
    /* Nonmatching */
}

/* 8014B05C-8014B2B8       .text checkNextActionHookshotReady__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionHookshotReady() {
    /* Nonmatching */
    static JGeometry::TVec3<f32> eff_scale;
    static JGeometry::TVec3<f32> eff_dscale;
    static JGeometry::TVec3<f32> eff_pscale;
}

/* 8014B2B8-8014B350       .text checkNextHookshotMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextHookshotMode() {
    /* Nonmatching */
}

/* 8014B350-8014B3F4       .text procHookshotSubject_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotSubject_init() {
    if(mCurProc == daPyProc_HOOKSHOT_SUBJECT_e) {
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
    if(!checkItemModeActorPointer()) {
        return true;
    }

    daHookshot_c* hookshot = (daHookshot_c*)mActorKeepEquip.getActor();
    if(fopAcM_GetParam(hookshot) == 0) {
        dComIfGp_setDoStatus(7);
    }

    if(mpAttention->Lockon()) {
        setSpeedAndAngleAtn();
    }

    mSightPacket.offDrawFlg();

    if(checkNextMode(0) == 0 && fopAcM_GetParam(hookshot) == 0 && setBodyAngleToCamera() && fopAcM_GetParam(hookshot) == 0) {
        setHookshotSight();
    }

    if(fopAcM_GetParam(hookshot) == 0) {
        dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK40000_e);
    }
    else {
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK40000_e);
    }

    return true;
}

/* 8014B518-8014B5E8       .text procHookshotMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotMove_init() {
    /* Nonmatching */
}

/* 8014B5E8-8014B74C       .text procHookshotMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotMove() {
    /* Nonmatching */
}

/* 8014B74C-8014B854       .text procHookshotFly_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotFly_init() {
    /* Nonmatching */
}

/* 8014B854-8014BA84       .text procHookshotFly__9daPy_lk_cFv */
BOOL daPy_lk_c::procHookshotFly() {
    /* Nonmatching */
}
