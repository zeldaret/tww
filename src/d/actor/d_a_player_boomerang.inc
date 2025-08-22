/**
 * d_a_player_boomerang.inc
 *
 * Code relating to the Boomerang item.
 *
 * This file is not a standalone translation unit and is instead directly
 * included into d_a_player_main.cpp.
 *
 * The original name of this file is not known, but a best guess was taken
 * based on the original names of the functions it contains.
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_boomerang.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_player_main.h"

/* 8014956C-80149590       .text checkBoomerangAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkBoomerangAnime() const {
    return checkBoomerangReadyAnime() || checkBoomerangThrowAnime();
}

/* 80149590-80149698       .text throwBoomerang__9daPy_lk_cFv */
void daPy_lk_c::throwBoomerang() {
    daBoomerang_c* boomerang = (daBoomerang_c*)mActorKeepEquip.getActor();

    fopAcM_SetParam(boomerang, 1);
    if (mpAttnActorLockOn != NULL) {
        boomerang->setAimActor(mpAttnActorLockOn);
    }
    boomerang->shape_angle.y = shape_angle.y;
    mActorKeepThrow = mActorKeepEquip;
    mActorKeepEquip.clearData();
    mEquipItem = daPyItem_NONE_e;
    dComIfGp_setPlayerStatus0(0, daPyStts0_BOOMERANG_WAIT_e);
    shape_angle.y += mBodyAngle.y;
    current.angle.y = shape_angle.y;
    mBodyAngle.y = 0;
    voiceStart(0);
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        dComIfGp_clearPlayerStatus0(0, daPyStts0_BOOMERANG_AIM_e);
        offModeFlg(ModeFlg_SUBJECT);
        onModeFlg(ModeFlg_00000080);
    } else if (mAcch.ChkGroundHit()) {
        procWait_init();
    }
}

/* 80149698-801497A4       .text returnBoomerang__9daPy_lk_cFv */
int daPy_lk_c::returnBoomerang() {
    dComIfGp_clearPlayerStatus0(0, daPyStts0_BOOMERANG_WAIT_e);

    if (mEquipItem == daPyItem_NONE_e && !checkNoControll() && !dComIfGp_event_runCheck() && mDemo.getDemoType() == 0 &&
        (checkNoUpperAnime() || checkPlayerGuard() || checkDashDamageAnime() || checkBoomerangAnime()) &&
        (!checkModeFlg(
             // These combine to: 0x01FD2810
             ModeFlg_WHIDE | ModeFlg_ROPE | ModeFlg_IN_SHIP | ModeFlg_CLIMB | ModeFlg_SWIM | ModeFlg_00080000 |
             ModeFlg_GRAB | ModeFlg_PUSHPULL | ModeFlg_LADDER | ModeFlg_CROUCH | ModeFlg_CRAWL
         ) ||
         mCurProc == daPyProc_SHIP_BOOMERANG_e))
    {
        mActorKeepEquip = mActorKeepThrow;
        mActorKeepThrow.clearData();
        mEquipItem = dItem_BOOMERANG_e;
        onNoResetFlg0(daPyFlg0_UNK20);
        return true;
    }

    mActorKeepThrow.clearData();
    return false;
}

/* 801497A4-8014984C       .text checkNextActionBoomerangReady__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionBoomerangReady() {
    if (!itemButton() && (mpAttnActorLockOn != NULL || dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x10))) {
        setActAnimeUpper(
            LKANM_BCK_BOOMTHROW,
            UPPER_MOVE2_e,
            daPy_HIO_boom_c0::m.field_0x4,
            daPy_HIO_boom_c0::m.field_0x8,
            daPy_HIO_boom_c0::m.field_0x0,
            daPy_HIO_boom_c0::m.field_0xC
        );
        setPriTextureAnime(0x48, 0);
        return true;
    }
    return cancelItemUpperReadyAnime();
}

/* 8014984C-801498D8       .text checkNextActionBoomerangFly__9daPy_lk_cFv */
void daPy_lk_c::checkNextActionBoomerangFly() {
    if (checkBoomerangReadyAnime()) {
        checkNextActionBoomerangReady();
    } else if (itemTrigger() && mEquipItem == getReadyItem()) {
        setActAnimeUpper(
            LKANM_BCK_BOOMWAIT, UPPER_MOVE2_e, daPy_HIO_boom_c0::m.field_0x18, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC
        );
    }
}

/* 801498D8-80149964       .text checkNextBoomerangMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextBoomerangMode() {
    if (!checkBoomerangAnime()) {
        seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
    }
    if (checkAttentionLock()) {
        return procBoomerangMove_init();
    } else {
        return procBoomerangSubject_init();
    }
}

/* 80149964-80149A44       .text changeBoomerangCatchProc__9daPy_lk_cFv */
BOOL daPy_lk_c::changeBoomerangCatchProc() {
    if (checkNoResetFlg0(daPyFlg0_UNK20)) {
        if (!dComIfGp_event_runCheck() && mDemo.getDemoType() == 0 && checkModeFlg(ModeFlg_00020000) &&
            (checkNoUpperAnime() || checkBoomerangThrowAnime()))
        {
            setActAnimeUpper(
                LKANM_BCK_BOOMCATCH,
                UPPER_MOVE2_e,
                daPy_HIO_boom_c0::m.field_0x20,
                daPy_HIO_boom_c0::m.field_0x24,
                daPy_HIO_boom_c0::m.field_0x2,
                daPy_HIO_boom_c0::m.field_0x28
            );
            setPriTextureAnime(0x49, 0);
            seStartOnlyReverb(JA_SE_LK_BOOM_CATCH);
            if (checkModeFlg(ModeFlg_00000001)) {
                return procBoomerangCatch_init();
            }
        }
        offNoResetFlg0(daPyFlg0_UNK20);
    }
    return false;
}

/* 80149A44-80149AF0       .text procBoomerangSubject_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangSubject_init() {
    if (mCurProc == daPyProc_BOOMERANG_SUBJECT_e) {
        return false;
    }

    commonProcInit(daPyProc_BOOMERANG_SUBJECT_e);

    mVelocity = 0.0f;

    setActAnimeUpper(LKANM_BCK_BOOMWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
    setSingleMoveAnime(ANM_ATNRS, 0.0f, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);

    dComIfGp_setPlayerStatus0(0, daPyStts0_BOOMERANG_AIM_e);

    current.angle.y = shape_angle.y;

    return true;
}

/* 80149AF0-80149C00       .text procBoomerangSubject__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangSubject() {
    if (!checkItemModeActorPointer()) {
        return true;
    }

    if (checkBoomerangReadyAnime()) {
        dComIfGp_setDoStatus(dActStts_RETURN_e);
    }

    setShapeAngleToAtnActor();

    if (checkAttentionLock()) {
        setSpeedAndAngleAtn();
    }

    if (checkNextMode(0) == 0) {
        if (setBodyAngleToCamera()) {
            daBoomerang_c* boomerang = (daBoomerang_c*)mActorKeepEquip.getActor();
            if (boomerang != NULL) {
                cXyz sight;
                checkSightLine(boomerang->getFlyMax(), &sight);
                mSightPacket.setPos(&sight);
                mSightPacket.onDrawFlg();
            }
        }
    } else {
        mSightPacket.offDrawFlg();
    }

    return true;
}

/* 80149C00-80149CC8       .text procBoomerangMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangMove_init() {
    if (mCurProc == daPyProc_BOOMERANG_MOVE_e) {
        return false;
    }

    commonProcInit(daPyProc_BOOMERANG_MOVE_e);
    if (mDirection == DIR_LEFT) {
        current.angle.y = shape_angle.y + 0x4000;
    } else {
        mDirection = DIR_RIGHT;
        current.angle.y = shape_angle.y + -0x4000;
    }
    setActAnimeUpper(LKANM_BCK_BOOMWAIT, UPPER_MOVE2_e, daPy_HIO_boom_c0::m.field_0x18, 0.0f, -1, -1.0f);
    setBlendAtnMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
    dComIfGp_setPlayerStatus0(0, daPyStts0_BOOMERANG_AIM_e);
    return true;
}

/* 80149CC8-80149DA4       .text procBoomerangMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangMove() {
    if (!checkItemModeActorPointer()) {
        return true;
    }

    if (mpAttnActorLockOn != NULL) {
        setSpeedAndAngleAtnActor();
    } else {
        setSpeedAndAngleAtn();
    }

    if (!checkNextMode(0)) {
        f32 fVar1 = -1.0f;
        if (std::fabsf(mVelocity) < 0.001f) {
            onModeFlg(ModeFlg_00000001);
            if (mDirection != DIR_RIGHT) {
                mDirection = DIR_RIGHT;
                fVar1 = daPy_HIO_basic_c0::m.field_0xC;
            }
        } else {
            offModeFlg(ModeFlg_00000001);
        }
        setBlendAtnMoveAnime(fVar1);
        setBodyAngleXReadyAnime();
    }

    return true;
}

/* 80149DA4-80149E1C       .text procBoomerangCatch_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangCatch_init() {
    if (mCurProc == daPyProc_BOOMERANG_CATCH_e) {
        return false;
    }

    commonProcInit(daPyProc_BOOMERANG_CATCH_e);
    setSingleMoveAnime(
        ANM_BOOMCATCH,
        daPy_HIO_boom_c0::m.field_0x20,
        daPy_HIO_boom_c0::m.field_0x24,
        daPy_HIO_boom_c0::m.field_0x2,
        daPy_HIO_boom_c0::m.field_0x28
    );
    offNoResetFlg0(daPyFlg0_UNK20);
    return true;
}

/* 80149E1C-80149ECC       .text procBoomerangCatch__9daPy_lk_cFv */
BOOL daPy_lk_c::procBoomerangCatch() {
    if (checkAttentionLock()) {
        setSpeedAndAngleAtn();
    } else {
        setSpeedAndAngleNormal(daPy_HIO_move_c0::m.field_0x0);
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
    }
    checkNextMode(0);
    return true;
}
