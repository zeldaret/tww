/**
 * d_a_player_battle.inc
 *
 * Code relating to parrying enemies.
 *
 * This file is not a standalone translation unit and is instead directly
 * included into d_a_player_main.cpp.
 *
 * The original name of this file is not known, but a best guess was taken
 * based on the original names of the functions it contains.
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_player_main.h"

/* 8013E250-8013E384       .text setSpecialBattle__9daPy_lk_cFi */
void daPy_lk_c::setSpecialBattle(BOOL param_0) {
    if (param_0 && strcmp(dComIfGp_getStartStageName(), "GTower") != 0) {
        return;
    }
    if (mpAttnEntryA == NULL) {
        return;
    }
    if (mpAttnEntryA->mType != fopAc_Attn_TYPE_BATTLE_e) {
        return;
    }
    if (mpAttnActorLockOn == NULL) {
        return;
    }
    if (mpAttnActorLockOn->group != fopAc_ENEMY_e) {
        return;
    }
    fopEn_enemy_c* enemy = (fopEn_enemy_c*)mpAttnActorLockOn;
    if (checkPlayerGuard()) {
        return;
    }
    if (daPy_dmEcallBack_c::checkCurse()) {
        return;
    }
    if (mEquipItem != daPyItem_SWORD_e) {
        return;
    }
    if (enemy->getBtAttackType() == 0) {
        return;
    }
    if (enemy->getBtStartFrame() - daPy_HIO_battle_c0::m.field_0x4 <= enemy->getBtNowFrame() &&
        enemy->getBtNowFrame() < enemy->getBtEndFrame() &&
        enemy->getBtMaxDis() > fopAcM_searchActorDistanceXZ(this, enemy))
    {
        dComIfGp_setDoStatus(dActStts_PARRY_e);
    }
}

/* 8013E384-8013E454       .text changeSpecialBattle__9daPy_lk_cFv */
BOOL daPy_lk_c::changeSpecialBattle() {
    if (mpAttnActorLockOn != NULL && (dComIfGp_getDoStatus() == dActStts_PARRY_e || (m34C5 == 5))) {
        fopEn_enemy_c* enemy = (fopEn_enemy_c*)mpAttnActorLockOn;
        if (m34C5 == 5 || (spBattleTrigger() && enemy->getBtStartFrame() <= enemy->getBtNowFrame())) {
            if (enemy->getBtAttackType() == 1) {
                return procBtJump_init(enemy);
            }
            if (enemy->getBtAttackType() == 2) {
                return procBtRoll_init(enemy);
            }
            if (enemy->getBtAttackType() == 3) {
                return procBtVerticalJump_init(enemy);
            }
            if (enemy->getBtAttackType() == 4) {
                onNoResetFlg1(daPyFlg1_LAST_COMBO_WAIT);
                return true;
            }
        }
    }

    return false;
}

/* 8013E454-8013E72C       .text procBtJump_init__9daPy_lk_cFP13fopEn_enemy_c */
BOOL daPy_lk_c::procBtJump_init(fopEn_enemy_c* enemy) {
    f32 fVar1;
    s16 sVar2;
    f32 dVar3;
    f32 dVar5;

    cXyz local_34 = enemy->current.pos - current.pos;
    commonProcInit(daPyProc_BT_JUMP_e);
    gravity = daPy_HIO_b_jump_c0::m.field_0x20;
    setSingleMoveAnime(
        ANM_MJMP,
        daPy_HIO_b_jump_c0::m.field_0x8,
        daPy_HIO_b_jump_c0::m.field_0x14,
        -1,
        daPy_HIO_b_jump_c0::m.field_0x10
    );
    fVar1 = local_34.y + enemy->getBtHeight();
    if (local_34.y + enemy->getBtHeight() < 30.0f) {
        fVar1 = 30.0f;
    }
    dVar5 = std::sqrtf((-2.0f * fVar1) / gravity);
    m35A0 = dVar5 * -gravity;
    dVar3 = local_34.absXZ();
    m35A4 = dVar3 / dVar5;
    sVar2 = fopAcM_searchActorAngleY(this, enemy);
    current.angle.y = sVar2;
    shape_angle.y = current.angle.y;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2_e);
    m34D0 = 0;
    m370C.x = enemy->current.pos.x - enemy->getBtBodyR() * cM_ssin(enemy->shape_angle.y);
    m370C.y = enemy->current.pos.y;
    m370C.z = enemy->current.pos.z - enemy->getBtBodyR() * cM_scos(enemy->shape_angle.y);
    if (daPy_HIO_b_jump_c0::m.field_0x18 <= 0.0f) {
        speed.y = m35A0;
        mVelocity = m35A4;
        mProcVar0.m3570 = 1;
    } else {
        mProcVar0.m3570 = 0;
    }
    voiceStart(6);
    offNoResetFlg0(daPyFlg0_NO_FALL_VOICE);
    endFlameDamageEmitter();
    return true;
}

/* 8013E72C-8013E860       .text procBtJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procBtJump() {
    if (mProcVar0.m3570 == 0) {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= daPy_HIO_b_jump_c0::m.field_0x18) {
            speed.y = m35A0;
            mVelocity = m35A4;
            mProcVar0.m3570 = 1;
        }
    } else {
        if (mAcch.ChkGroundHit()) {
            return changeLandProc(daPy_HIO_b_jump_c0::m.field_0xC);
        }
        if (mProcVar0.m3570 == 1) {
            m34D0++;
            if (speed.y < -gravity) {
                return procBtJumpCut_init(&m370C);
            }
        } else {
            u32 uVar2 = cM_atan2s(mVelocity, -speed.y);
            f32 temp = cM_ssin(uVar2 * 2);
            m34F2 = -daPy_HIO_b_jump_c0::m.field_0x6 * temp;
            setFallVoice();
        }
    }
    return true;
}

/* 8013E860-8013E9D4       .text procBtJumpCut_init__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::procBtJumpCut_init(cXyz* param_0) {
    commonProcInit(daPyProc_BT_JUMP_CUT_e);
    setSingleMoveAnime(
        ANM_MJMPC,
        daPy_HIO_b_jump_c0::m.field_0x28,
        daPy_HIO_b_jump_c0::m.field_0x30,
        daPy_HIO_b_jump_c0::m.field_0x4,
        daPy_HIO_b_jump_c0::m.field_0x2C
    );
    if (checkNormalSwordEquip()) {
        mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_MJMPCA));
    } else {
        mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_MJMPCMS));
    }
    m35EC = daPy_HIO_b_jump_c0::m.field_0x30;
    mVelocity = 0.0f;
    gravity = 0.0f;
    speed.y = 0.0f;
    m370C = *param_0;
    mProcVar0.m3570 = 0;
    dComIfGp_setPlayerStatus0(0, (daPyStts0_UNK2_e | daPyStts0_UNK400_e));
    voiceStart(1);
    setBlurPosResource(LKANM__BTJUMPCUT_POS);
    setExtraFinishCutAtParam(5);
    dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    return true;
}

/* 8013E9D4-8013EBD0       .text procBtJumpCut__9daPy_lk_cFv */
BOOL daPy_lk_c::procBtJumpCut() {
    m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if (speed.y < 0.0f && daPy_HIO_b_jump_c0::m.field_0x0 == 1) {
        u32 uVar2 = cM_atan2s(mVelocity, -speed.y);
        f32 temp = cM_ssin(uVar2 * 2);
        m34F2 = -daPy_HIO_b_jump_c0::m.field_0x6 * temp;
    }

    f32 frame = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if (frame >= daPy_HIO_b_jump_c0::m.field_0x44 && frame < daPy_HIO_b_jump_c0::m.field_0x48) {
        onResetFlg0(daPyRFlg0_UNK2);
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
    }

    if (mAcch.ChkGroundHit()) {
        return changeLandProc(daPy_HIO_b_jump_c0::m.field_0xC);
    }

    if (mProcVar0.m3570 == 0 && mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        gravity = daPy_HIO_b_jump_c0::m.field_0x3C;
        speed.y = daPy_HIO_b_jump_c0::m.field_0x34;
        mVelocity = daPy_HIO_b_jump_c0::m.field_0x38;
        mProcVar0.m3570 = 1;
    } else if (mProcVar0.m3570 == 1 && speed.y < -gravity && daPy_HIO_b_jump_c0::m.field_0x0 == 1) {
        mProcVar0.m3570 = 2;
        setSingleMoveAnime(ANM_JMPEDS, 0.0f, 0.0f, -1, daPy_HIO_b_jump_c0::m.field_0x40);
        offModeFlg(ModeFlg_00000400);
        setTextureAnime(0x37, 0);
        resetSeAnime();
    }

    setFallVoice();

    return true;
}

/* 8013EBD0-8013EC50       .text procBtSlide__9daPy_lk_cFv */
BOOL daPy_lk_c::procBtSlide() {
    f32 dVar1 = cLib_addCalc(
        &mVelocity,
        0.0f,
        daPy_HIO_b_slide_c0::m.field_0x4,
        daPy_HIO_b_slide_c0::m.field_0x8,
        daPy_HIO_b_slide_c0::m.field_0xC
    );
    if (dVar1 <= 0.001f) {
        checkNextMode(0);
    }
    if (mVelocity < 2.5f) {
        resetFootEffect();
    }
    return true;
}

/* 8013EC50-8013EE64       .text procBtRoll_init__9daPy_lk_cFP13fopEn_enemy_c */
BOOL daPy_lk_c::procBtRoll_init(fopEn_enemy_c* enemy) {
    commonProcInit(daPyProc_BT_ROLL_e);
    mVelocity = 0.0f;

    cXyz local_38;
    local_38.x = 0.5f * (current.pos.x + (enemy->current.pos.x - enemy->getBtBodyR() * cM_ssin(enemy->shape_angle.y)));
    local_38.y = 0.5f * (enemy->current.pos.y + current.pos.y);
    local_38.z = 0.5f * (current.pos.z + (enemy->current.pos.z - enemy->getBtBodyR() * cM_scos(enemy->shape_angle.y)));

    daPy_ANM anm;
    if (mDirection == DIR_LEFT) {
        m34D4 = -0x7FF0;
        anm = ANM_MROLLL;
    } else {
        m34D4 = 0x7FF0;
        anm = ANM_MROLLR;
    }
    setSingleMoveAnime(
        anm,
        daPy_HIO_b_roll_c0::m.field_0xC,
        daPy_HIO_b_roll_c0::m.field_0x10,
        daPy_HIO_b_roll_c0::m.field_0x6,
        daPy_HIO_b_roll_c0::m.field_0x14
    );

    cXyz local_2c = current.pos - local_38;
    f32 dVar5 = local_2c.absXZ();
    m35A0 = dVar5;
    m34D6 = cM_atan2s(local_2c.x, local_2c.z);
    shape_angle.y = fopAcM_searchActorAngleY(this, enemy);
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2_e);
    m34BE = 4;
    voiceStart(7);
    endFlameDamageEmitter();
    return true;
}

/* 8013EE64-8013F010       .text procBtRoll__9daPy_lk_cFv */
BOOL daPy_lk_c::procBtRoll() {
    s16 sVar1 = m34D4;
    cLib_addCalcAngleS(
        &m34D4, 0, daPy_HIO_b_roll_c0::m.field_0x4, daPy_HIO_b_roll_c0::m.field_0x0, daPy_HIO_b_roll_c0::m.field_0x2
    );

    s16 sVar3 = sVar1 - m34D4;
    if (sVar1 > 0) {
        current.angle.y = m34D6 + 0x4000;
    } else {
        current.angle.y = m34D6 + -0x4000;
    }

    cXyz local_28;
    local_28.x = current.pos.x - m35A0 * cM_ssin(m34D6);
    local_28.y = current.pos.y;
    local_28.z = current.pos.z - m35A0 * cM_scos(m34D6);
    m34D6 += sVar3;
    current.pos.x = local_28.x + m35A0 * cM_ssin(m34D6);
    current.pos.z = local_28.z + m35A0 * cM_scos(m34D6);
    shape_angle.y = m34D6 + 0x8000;
    if (abs((int)sVar3) < daPy_HIO_b_roll_c0::m.field_0x2) {
        resetFootEffect();
    }

    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    if (frameCtrl.getRate() < 0.01f) {
        procBtRollCut_init(&local_28);
    } else if (frameCtrl.checkPass(10.0f)) {
        endFlameDamageEmitter();
    }

    return true;
}

/* 8013F010-8013F200       .text procBtRollCut_init__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::procBtRollCut_init(cXyz* param_0) {
    daPy_ANM dVar4;

    commonProcInit(daPyProc_BT_ROLL_CUT_e);

    s16 angle_y_delta = current.angle.y - shape_angle.y;
    if (angle_y_delta > 0) {
        dVar4 = ANM_MROLLLC;
        mProcVar0.m3570 = 1;
        m34EC = 1;
        setBlurPosResource(LKANM__BTROTATECUTL_POS);
    } else {
        dVar4 = ANM_MROLLRC;
        mProcVar0.m3570 = -1;
        m34EC = -1;
        setBlurPosResource(LKANM__BTROTATECUTR_POS);
    }

    setSingleMoveAnime(
        dVar4,
        daPy_HIO_b_roll_c0::m.field_0x1C,
        daPy_HIO_b_roll_c0::m.field_0x20,
        daPy_HIO_b_roll_c0::m.field_0x8,
        daPy_HIO_b_roll_c0::m.field_0x24
    );

    if (checkNormalSwordEquip()) {
        mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_MROLLCA));
    } else {
        mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_MROLLCMS));
    }

    m35EC = daPy_HIO_b_roll_c0::m.field_0x20;
    m370C = *param_0;
    m34D4 = 0;
    mVelocity = daPy_HIO_b_roll_c0::m.field_0x28;
    speed.y = daPy_HIO_b_roll_c0::m.field_0x2C;
    gravity = daPy_HIO_b_roll_c0::m.field_0x30;
    voiceStart(1);
    setExtraFinishCutAtParam(15);
    offNoResetFlg0(daPyFlg0_NO_FALL_VOICE);
    onResetFlg0(daPyRFlg0_UNK2);
    onResetFlg0(daPyRFlg0_UNK1);
    seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
    dComIfGp_setPlayerStatus0(0, (daPyStts0_UNK2_e | daPyStts0_UNK400_e));
    dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    return true;
}

/* 8013F200-8013F3E8       .text procBtRollCut__9daPy_lk_cFv */
BOOL daPy_lk_c::procBtRollCut() {
    m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    s16 sVar2 = cLib_targetAngleY(&current.pos, &m370C);
    cLib_addCalcAngleS(&shape_angle.y, sVar2, 5, 0x5e8, 0x13c);
    current.angle.y = shape_angle.y + mProcVar0.m3570 * 0x4000;
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (m34D4 == 0) {
            m34D4 = 1;
            onResetFlg0(daPyRFlg0_UNK2);
        } else if (m34D4 == 1) {
            setSingleMoveAnime(ANM_JMPEDS, 0.0f, 0.0f, -1, daPy_HIO_b_roll_c0::m.field_0x38);
            offModeFlg(ModeFlg_00000400);
            setTextureAnime(0x37, 0);
            resetSeAnime();
            m34D4 = 2;
        }
        if (m34D4 > 1) {
            int iVar3 = mProcVar0.m3570;
            if ((iVar3 > 0 && m34EC < 0) || (iVar3 < 0 && m34EC > 0)) {
                cLib_addCalcAngleS(&m34EC, -iVar3, 4, daPy_HIO_b_roll_c0::m.field_0xA, 0x200);
            } else {
                m34EC += iVar3 * daPy_HIO_b_roll_c0::m.field_0xA;
            }
        }
        if (mAcch.ChkGroundHit()) {
            shape_angle.y = shape_angle.y + m34EC;
            current.angle.y = shape_angle.y;
            return changeLandProc(daPy_HIO_autoJump_c0::m.field_0x24);
        }
    } else {
        onResetFlg0(daPyRFlg0_UNK2);
    }
    if (speed.y < -gravity) {
        gravity = daPy_HIO_b_roll_c0::m.field_0x34;
    }
    setFallVoice();
    return true;
}

/* 8013F3E8-8013F4A8       .text procBtVerticalJump_init__9daPy_lk_cFP13fopEn_enemy_c */
BOOL daPy_lk_c::procBtVerticalJump_init(fopEn_enemy_c* enemy) {
    commonProcInit(daPyProc_BT_VERTICAL_JUMP_e);
    setSingleMoveAnime(
        ANM_MSTEPOVER,
        daPy_HIO_b_verJump_c0::m.field_0x8,
        daPy_HIO_b_verJump_c0::m.field_0xC,
        daPy_HIO_b_verJump_c0::m.field_0x0,
        daPy_HIO_b_verJump_c0::m.field_0x10
    );
    mVelocity = 0.0f;
    gravity = daPy_HIO_b_verJump_c0::m.field_0x14;
    speed.y = daPy_HIO_b_verJump_c0::m.field_0x18;
    offNoResetFlg0(daPyFlg0_NO_FALL_VOICE);
    current.angle.y = shape_angle.y;
    voiceStart(6);
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2_e);
    endFlameDamageEmitter();
    return true;
}

/* 8013F4A8-8013F520       .text procBtVerticalJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procBtVerticalJump() {
    setFallVoice();
    if (mAcch.ChkGroundHit()) {
        changeLandProc(daPy_HIO_autoJump_c0::m.field_0x24);
    } else if (speed.y < -(gravity * 2.0f)) {
        procBtVerticalJumpCut_init();
    }
    return true;
}

/* 8013F520-8013F5BC       .text procBtVerticalJumpCut_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBtVerticalJumpCut_init() {
    commonProcInit(daPyProc_BT_VERTICAL_JUMP_CUT_e);
    setSingleMoveAnime(
        ANM_MSTEPOVERA,
        daPy_HIO_b_verJump_c0::m.field_0x1C,
        daPy_HIO_b_verJump_c0::m.field_0x20,
        daPy_HIO_b_verJump_c0::m.field_0x2,
        daPy_HIO_b_verJump_c0::m.field_0x24
    );
    mpCutfBpk->setFrame(0.0f);
    mpCutfBtk->setFrame(0.0f);
    gravity = daPy_HIO_b_verJump_c0::m.field_0x28;
    setExtraFinishCutAtParam(16);
    dComIfGp_setPlayerStatus0(0, (daPyStts0_UNK2_e | daPyStts0_UNK400_e));
    return true;
}

/* 8013F5BC-8013F6E4       .text procBtVerticalJumpCut__9daPy_lk_cFv */
BOOL daPy_lk_c::procBtVerticalJumpCut() {
    setFallVoice();

    f32 frame = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - 9.0f;
    if (frame < 0.0f) {
        frame = 0.0f;
    } else if (mpCutfBpk->getFrameMax() >= frame) {
        frame = mpCutfBpk->getFrameMax() - 0.001f;
    }
    mpCutfBpk->setFrame(frame);
    mpCutfBtk->setFrame(frame);

    if (mAcch.ChkGroundHit()) {
        procBtVerticalJumpLand_init();
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            voiceStart(1);
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
            gravity = daPy_HIO_b_verJump_c0::m.field_0x2C;
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }

    return true;
}

/* 8013F6E4-8013F7F0       .text procBtVerticalJumpLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procBtVerticalJumpLand_init() {
    f32 fVar1 = m35F0 - current.pos.y;

    if (!dComIfGp_event_runCheck()) {
        if (fVar1 >= 100.0f * daPy_HIO_fall_c0::m.field_0x10) {
            setDamagePoint(-2.0f);
        } else if (fVar1 >= 100.0f * daPy_HIO_fall_c0::m.field_0x14) {
            setDamagePoint(-1.0f);
        }
    }
    commonProcInit(daPyProc_BT_VERTICAL_JUMP_LAND_e);
    setSingleMoveAnime(
        ANM_MSTEPOVERLAND,
        daPy_HIO_b_verJump_c0::m.field_0x30,
        daPy_HIO_b_verJump_c0::m.field_0x34,
        daPy_HIO_b_verJump_c0::m.field_0x4,
        daPy_HIO_b_verJump_c0::m.field_0x38
    );
    dComIfGp_getVibration().StartShock(6, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    if (!checkNoResetFlg0(daPyFlg0_UNK10000000)) {
        seStartOnlyReverb(JA_SE_LK_JUMP_ATTACK);
    }
    return true;
}

/* 8013F7F0-8013F848       .text procBtVerticalJumpLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procBtVerticalJumpLand() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        procBackJump_init();
        mVelocity = daPy_HIO_b_verJump_c0::m.field_0x3C;
        speed.y = daPy_HIO_b_verJump_c0::m.field_0x40;
    }
    return true;
}
