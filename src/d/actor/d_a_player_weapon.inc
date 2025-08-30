/**
 * d_a_player_weapon.inc
 *
 * Code relating to using enemy weapons.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_boko.h"

/* 80153554-801535D8       .text setEnemyWeaponAtParam__9daPy_lk_cFi */
void daPy_lk_c::setEnemyWeaponAtParam(BOOL r4) {
    static const u8 cut_type[] = {
        /* daBoko_c::Type_STICK_e    */ 0x0B,
        /* daBoko_c::Type_MACHETE_e  */ 0x0D,
        /* daBoko_c::Type_CLUB_e     */ 0x14,
        /* daBoko_c::Type_DN_SWORD_e */ 0x16,
        /* daBoko_c::Type_SPEAR_e    */ 0x18,
        /* daBoko_c::Type_PG_SWORD_e */ 0x1C,
    };
    daBoko_c* boko = (daBoko_c*)mActorKeepEquip.getActor();
    u8 cutType = cut_type[fopAcM_GetParam(boko)];
    dCcG_At_Spl spl;
    u8 hitMark;
    if (r4) {
        spl = dCcG_At_Spl_UNK1;
        hitMark = dCcG_AtHitMark_Big_e;
        cutType++;
    } else {
        spl = dCcG_At_Spl_UNK0;
        hitMark = dCcG_AtHitMark_Nrm_e;
    }
    setAtParam(boko->getAtType(), boko->getAtPoint(), spl, boko->getSeType(), hitMark, cutType, boko->getCpsR());
}

/* 801535D8-8015372C       .text procWeaponNormalSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponNormalSwing_init() {
    if (mActorKeepEquip.getActor() == NULL) {
        return false;
    }

    commonProcInit(daPyProc_WEAPON_NORMAL_SWING_e);
    setSingleMoveAnime(
        ANM_CUTBOKO,
        daPy_HIO_cutBoko_c0::m.field_0x10,
        daPy_HIO_cutBoko_c0::m.field_0x18,
        daPy_HIO_cutBoko_c0::m.field_0x6,
        daPy_HIO_cutBoko_c0::m.field_0x34
    );
    current.angle.y = shape_angle.y;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    voiceStart(1);
    if (checkAttentionLock() || mStickDistance <= 0.05f) {
        m34D4 = shape_angle.y;
    } else {
        m34D4 = m34E8;
    }
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    m351E = m34DC;
    setBlurPosResource(LKANM__CUTBOKO_POS);
    setEnemyWeaponAtParam(0);
    m34D0 = daPy_HIO_cutBoko_c0::m.field_0x4;

    return true;
}

/* 8015372C-801539C8       .text procWeaponNormalSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponNormalSwing() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    if (swordButton() && mActorKeepEquip.getActor() != NULL) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    if (frameCtrl.getRate() < 0.01f || mActorKeepEquip.getActor() == NULL) {
        if (mActorKeepEquip.getActor() == NULL) {
            m34D0 = 0;
            offNoResetFlg0(daPyFlg0_UNK4);
        }
        if (m34D0 > 0) {
            m34D0--;
        } else {
            mVelocity = 0.0f;
            mDirection = DIR_RIGHT;
            checkNextMode(0);
            return true;
        }
    } else if (frameCtrl.getFrame() > daPy_HIO_cutBoko_c0::m.field_0x1C) {
        f32 dVar4 = mVelocity;
        u8 orig_direction = mDirection;
        mVelocity = 0.0f;
        mDirection = DIR_RIGHT;
        if (checkNextMode(1)) {
            return true;
        }
        mVelocity = dVar4;
        mDirection = orig_direction;
    }

    if (changeCutReverseProc(ANM_CUTRER)) {
        return true;
    }

    m34C2 = 1;
    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        m34D4 = shape_angle.y;
    } else {
        cLib_addCalcAngleS(
            &shape_angle.y,
            m34D4,
            daPy_HIO_turn_c0::m.field_0x4,
            daPy_HIO_turn_c0::m.field_0x0,
            daPy_HIO_turn_c0::m.field_0x2
        );
    }

    current.angle.y = shape_angle.y;
    if (frameCtrl.checkPass(daPy_HIO_cutBoko_c0::m.field_0x38)) {
        mVelocity = std::fabsf(speedF) * daPy_HIO_cutBoko_c0::m.field_0x20 + daPy_HIO_cutBoko_c0::m.field_0x24;
    }
    if (frameCtrl.checkPass(daPy_HIO_cutBoko_c0::m.field_0x3C)) {
        frameCtrl.setRate(daPy_HIO_cutBoko_c0::m.field_0x14);
    }
    if (frameCtrl.getFrame() >= daPy_HIO_cutBoko_c0::m.field_0x40 &&
        frameCtrl.getFrame() < daPy_HIO_cutBoko_c0::m.field_0x44)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    cLib_addCalc(
        &mVelocity,
        0.0f,
        daPy_HIO_cutBoko_c0::m.field_0x30,
        daPy_HIO_cutBoko_c0::m.field_0x28,
        daPy_HIO_cutBoko_c0::m.field_0x2C
    );

    return true;
}

/* 801539C8-80153A68       .text procWeaponSideSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponSideSwing_init() {
    commonProcInit(daPyProc_WEAPON_SIDE_SWING_e);
    setSingleMoveAnime(
        ANM_HAMSWINGA,
        daPy_HIO_cutBoko_c0::m.field_0x48,
        daPy_HIO_cutBoko_c0::m.field_0x4C,
        daPy_HIO_cutBoko_c0::m.field_0x8,
        daPy_HIO_cutBoko_c0::m.field_0x54
    );
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    voiceStart(1);
    m34D4 = shape_angle.y;
    setBlurPosResource(LKANM__HAMMERSIDE_POS);
    setEnemyWeaponAtParam(0);
    return true;
}

/* 80153A68-80153C30       .text procWeaponSideSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponSideSwing() {
    if (swordButton() && mActorKeepEquip.getActor() != NULL) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }

    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f || mActorKeepEquip.getActor() == NULL) {
        mVelocity = 0.0f;
        mDirection = DIR_RIGHT;
        checkNextMode(0);
        return true;
    }

    if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_cutBoko_c0::m.field_0x50) {
        f32 dVar4 = mVelocity;
        u8 orig_direction = mDirection;
        mVelocity = 0.0f;
        mDirection = DIR_RIGHT;
        if (checkNextMode(1)) {
            return true;
        }
        mVelocity = dVar4;
        mDirection = orig_direction;
    }

    if (changeCutReverseProc(ANM_CUTREL)) {
        return true;
    }

    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        m34D4 = shape_angle.y;
    } else {
        cLib_addCalcAngleS(
            &shape_angle.y,
            m34D4,
            daPy_HIO_turn_c0::m.field_0x4,
            daPy_HIO_turn_c0::m.field_0x0,
            daPy_HIO_turn_c0::m.field_0x2
        );
    }
    current.angle.y = shape_angle.y;
    if ((mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= daPy_HIO_cutBoko_c0::m.field_0x58) &&
        (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() < daPy_HIO_cutBoko_c0::m.field_0x5C))
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }

    return true;
}

/* 80153C30-80153D1C       .text procWeaponFrontSwingReady_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwingReady_init() {
    commonProcInit(daPyProc_WEAPON_FRONT_SWING_READY_e);
    setSingleMoveAnime(
        ANM_HAMSWINGBPRE,
        daPy_HIO_cutBoko_c0::m.field_0x60,
        daPy_HIO_cutBoko_c0::m.field_0x64,
        daPy_HIO_cutBoko_c0::m.field_0xA,
        daPy_HIO_cutBoko_c0::m.field_0x68
    );
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    if (checkAttentionLock() || mStickDistance <= 0.05f) {
        m34D4 = shape_angle.y;
    } else {
        m34D4 = m34E8;
    }
    setEnemyWeaponAtParam(0);
    voiceStart(7);
    return true;
}

/* 80153D1C-80153DBC       .text procWeaponFrontSwingReady__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwingReady() {
    if (mActorKeepEquip.getActor() == NULL) {
        return checkNextMode(0);
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        return procWeaponFrontSwing_init();
    }

    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        m34D4 = shape_angle.y;
    } else {
        cLib_addCalcAngleS(
            &shape_angle.y,
            m34D4,
            daPy_HIO_turn_c0::m.field_0x4,
            daPy_HIO_turn_c0::m.field_0x0,
            daPy_HIO_turn_c0::m.field_0x2
        );
    }

    current.angle.y = shape_angle.y;
    return true;
}

/* 80153DBC-80153ED8       .text procWeaponFrontSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwing_init() {
    commonProcInit(daPyProc_WEAPON_FRONT_SWING_e);
    setSingleMoveAnime(
        ANM_HAMSWINGBHIT,
        4.0f * daPy_HIO_cutBoko_c0::m.field_0x6C,
        daPy_HIO_cutBoko_c0::m.field_0x70,
        daPy_HIO_cutBoko_c0::m.field_0xC,
        0.0f
    );
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    voiceStart(1);
    if (checkAttentionLock() || mStickDistance <= 0.05f) {
        m34D4 = shape_angle.y;
    } else {
        m34D4 = m34E8;
    }
    m34D4 = shape_angle.y;
    setBlurPosResource(LKANM__HAMMERFRONT_POS);
    setEnemyWeaponAtParam(0);
    onResetFlg0(daPy_RFLG0(daPyRFlg0_UNK1 | daPyRFlg0_UNK2));
    m34D0 = 0;
    return true;
}

/* 80153ED8-80153FA0       .text procWeaponFrontSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwing() {
    if (mActorKeepEquip.getActor() == NULL) {
        return checkNextMode(0);
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        return procWeaponFrontSwingEnd_init();
    }
    if (changeCutReverseProc(ANM_CUTREL)) {
        return true;
    }

    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        m34D4 = shape_angle.y;
    } else {
        cLib_addCalcAngleS(
            &shape_angle.y,
            m34D4,
            daPy_HIO_turn_c0::m.field_0x4,
            daPy_HIO_turn_c0::m.field_0x0,
            daPy_HIO_turn_c0::m.field_0x2
        );
    }
    current.angle.y = shape_angle.y;
    onResetFlg0(daPyRFlg0_UNK2);
    return true;
}

/* 80153FA0-80154014       .text procWeaponFrontSwingEnd_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwingEnd_init() {
    commonProcInit(daPyProc_WEAPON_FRONT_SWING_END_e);
    setSingleMoveAnime(
        ANM_HAMSWINGBEND,
        daPy_HIO_cutBoko_c0::m.field_0x74,
        daPy_HIO_cutBoko_c0::m.field_0x78,
        daPy_HIO_cutBoko_c0::m.field_0xE,
        daPy_HIO_cutBoko_c0::m.field_0x80
    );
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    setEnemyWeaponAtParam(0);
    return true;
}

/* 80154014-801540B4       .text procWeaponFrontSwingEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponFrontSwingEnd() {
    if (swordButton() && mActorKeepEquip.getActor() != NULL) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }

    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f || mActorKeepEquip.getActor() == NULL) {
        return checkNextMode(0);
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_cutBoko_c0::m.field_0x7C) {
        return checkNextMode(1);
    } else {
        return true;
    }
}

/* 801540B4-8015411C       .text procWeaponThrow_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponThrow_init() {
    commonProcInit(daPyProc_WEAPON_THROW_e);
    setSingleMoveAnime(ANM_CUTA, 1.0f, 0.0f, -1, 5.0f);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    m34C2 = 1;
    return true;
}

/* 8015411C-80154334       .text procWeaponThrow__9daPy_lk_cFv */
BOOL daPy_lk_c::procWeaponThrow() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    if (frameCtrl.getRate() < 0.01f || mActorKeepEquip.getActor() == NULL) {
        return checkNextMode(0);
    }
    if (frameCtrl.getFrame() > 100.0f) {
        return checkNextMode(1);
    }

    if (frameCtrl.checkPass(10.0f)) {
        daBoko_c* boko = static_cast<daBoko_c*>(mActorKeepEquip.getActor());
        s16 uVar2 = 0xf400;
        if (mpAttnActorLockOn != NULL) {
            cXyz local_34 = mpAttnActorLockOn->eyePos - boko->current.pos;
            f32 dVar5 = local_34.abs();
            if (dVar5 >= 1.0f) {
                dVar5 = local_34.absXZ();
                uVar2 = cM_atan2s(-local_34.y, dVar5);
            }
        }
        boko->setThrow(uVar2);
        voiceStart(0);
        deleteEquipItem(FALSE);
    }

    return true;
}
