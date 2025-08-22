/**
 * d_a_player_whide.inc
 *
 * Code relating to "wall hiding" (sidling).
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

/* 8013707C-801371E0       .text setBlendWHideMoveAnime__9daPy_lk_cFf */
void daPy_lk_c::setBlendWHideMoveAnime(f32 param_0) {
    f32 fVar1;
    f32 fVar5;
    daPy_ANM dVar6;
    s16 sVar1;
    f32 fVar6;
    f32 fVar3;
    daPy_ANM dVar5;

    if (!checkNoResetFlg0(daPyFlg0_UNK10000)) {
        fVar1 = daPy_HIO_wall_c0::m.field_0x14;
        fVar5 = daPy_HIO_wall_c0::m.field_0x40;
        dVar6 = ANM_WALL;
        sVar1 = daPy_HIO_wall_c0::m.field_0x8;
        fVar6 = daPy_HIO_wall_c0::m.field_0x60;
        fVar3 = daPy_HIO_wall_c0::m.field_0x58;
        if (mDirection == DIR_LEFT) {
            dVar5 = ANM_WALLWR;
        } else {
            dVar5 = ANM_WALLWL;
        }
    } else {
        fVar1 = daPy_HIO_wall_c0::m.field_0x18;
        fVar5 = daPy_HIO_wall_c0::m.field_0x44;
        dVar6 = ANM_WALLDW;
        sVar1 = daPy_HIO_wall_c0::m.field_0xA;
        fVar6 = daPy_HIO_wall_c0::m.field_0x64;
        fVar3 = daPy_HIO_wall_c0::m.field_0x5C;
        if (mDirection == DIR_LEFT) {
            dVar5 = ANM_WALLWRDW;
        } else {
            dVar5 = ANM_WALLWLDW;
        }
    }
    fVar5 *= param_0;
    
    f32 fVar7;
    fVar7 = mVelocity / mMaxNormalSpeed;
    if (fVar7 < 0.0f) {
        fVar7 = 0.0f;
    }
    f32 fVar4;
    if (fVar7 < fVar3) {
        fVar4 = 1.0f - fVar7 / fVar3;
        m3598 = 1.0f;
    } else {
        fVar4 = 0.0f;
        m3598 = (1.0f - ((1.0f - fVar6) * (fVar7 - fVar3)) / (1.0f - fVar3));
    }
    
    setMoveAnime(fVar4, fVar1, 0.0f, dVar5, dVar6, 5, fVar5);
    
    mFrameCtrlUnder[UNDER_MOVE0_e].setEnd(sVar1);
    mFrameCtrlUnder[UNDER_MOVE1_e].setFrame(mFrameCtrlUnder[UNDER_MOVE1_e].getEnd() - 0.001f);
    mFrameCtrlUnder[UNDER_MOVE1_e].setRate(0.0f);
    mAnmRatioUnder[UNDER_MOVE1_e].getAnmTransform()->setFrame(mFrameCtrlUnder[UNDER_MOVE1_e].getFrame());
}

/* 801371E0-80137608       .text getWHideModePolygon__9daPy_lk_cFP4cXyzP4cXyzP4cXyzi */
cM3dGPla* daPy_lk_c::getWHideModePolygon(cXyz* param_0, cXyz* param_1, cXyz* param_2, int direction) {
    if (param_0 != NULL) {
        mLinkLinChk.Set(param_0, param_1, this);
        if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
            return NULL;
        }
    }

    dBgS* bgs = dComIfG_Bgsp(); // Maybe fakematch? Fixes regalloc

    cM3dGPla* triPla = bgs->GetTriPla(mLinkLinChk);
    s16 uVar3 = cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z);
    if (std::fabsf(triPla->GetNP()->y) > 0.05f) {
        return NULL;
    }
    int iVar4 = bgs->GetSpecialCode(mLinkLinChk);
    if (iVar4 == 3) {
        return NULL;
    }

    *param_2 = mLinkLinChk.GetCross();
    cXyz local_3c;
    local_3c.x = param_2->x + cM_ssin(uVar3) * daPy_HIO_wall_c0::m.field_0x50;
    local_3c.y = param_2->y;
    local_3c.z = param_2->z + cM_ssin(uVar3) * daPy_HIO_wall_c0::m.field_0x50;
    mGndChk.SetPos(&local_3c);
    float f31 = bgs->GroundCross(&mGndChk);
    if (-G_CM3D_F_INF != f31 && (!cBgW_CheckBGround(bgs->GetTriPla(mGndChk)->GetNP()->y))) {
        return NULL;
    }

    if (direction == DIR_NONE) {
        f31 = 49.9f;
    } else {
        f31 = 99.8f;
    }
    s16 sVar7 = uVar3;
    cXyz local_48;
    if (direction != DIR_RIGHT) {
        local_3c.set(
            param_2->x + (f31 * triPla->GetNP()->z) + (triPla->GetNP()->x * 1.25f),
            param_2->y,
            param_2->z - (f31 * triPla->GetNP()->x) + (triPla->GetNP()->z * 1.25f)
        );
        local_48.set(local_3c.x - (2.5f * triPla->GetNP()->x), local_3c.y, local_3c.z - (2.5f * triPla->GetNP()->z));
        mLinkLinChk.Set(&local_3c, &local_48, this);
        if (!bgs->LineCross(&mLinkLinChk)) {
            return NULL;
        }
        cM3dGPla* pfVar5;
        pfVar5 = bgs->GetTriPla(mLinkLinChk);
        iVar4 = cM_atan2s(pfVar5->GetNP()->x, pfVar5->GetNP()->z);
        if (sVar7 != (s16)iVar4) {
            return NULL;
        }
    }

    if (direction != DIR_LEFT) {
        local_3c.set(
            param_2->x - (f31 * triPla->GetNP()->z) + (triPla->GetNP()->x * 1.25f),
            param_2->y,
            param_2->z + (f31 * triPla->GetNP()->x) + (triPla->GetNP()->z * 1.25f)
        );
        local_48.set(local_3c.x - (2.5f * triPla->GetNP()->x), local_3c.y, local_3c.z - (2.5f * triPla->GetNP()->z));
        mLinkLinChk.Set(&local_3c, &local_48, this);
        if (!bgs->LineCross(&mLinkLinChk)) {
            return NULL;
        }
        cM3dGPla* pfVar5;
        pfVar5 = bgs->GetTriPla(mLinkLinChk);
        iVar4 = cM_atan2s(pfVar5->GetNP()->x, pfVar5->GetNP()->z);
        if (sVar7 != (s16)iVar4) {
            return NULL;
        }
    }

    if (direction != DIR_NONE) {
        if (direction == DIR_LEFT) {
            sVar7 = sVar7 - shape_angle.y;
            param_2->x += daPy_HIO_wall_c0::m.field_0x54 * triPla->GetNP()->z;
            param_2->z -= daPy_HIO_wall_c0::m.field_0x54 * triPla->GetNP()->x;
        } else {
            sVar7 = shape_angle.y - sVar7;
            param_2->x -= daPy_HIO_wall_c0::m.field_0x54 * triPla->GetNP()->z;
            param_2->z += daPy_HIO_wall_c0::m.field_0x54 * triPla->GetNP()->x;
        }
        if (sVar7 > 0x2aaa) {
            return NULL;
        }
    } else if (abs((s16)((sVar7 + -0x8000) - (current.angle.y))) > 0x1555) {
        return NULL;
    }

    return triPla;
}

/* 80137608-80137640       .text getWHideBasePos__9daPy_lk_cFP4cXyz */
void daPy_lk_c::getWHideBasePos(cXyz* param_0) {
    f32 fVar3;

    if (checkNoResetFlg0(daPyFlg0_UNK10000)) {
        fVar3 = 89.9f;
    } else {
        fVar3 = 125.0f;
    }
    param_0->set(current.pos.x, current.pos.y + fVar3, current.pos.z);
}

/* 80137640-8013769C       .text getWHideNextPos__9daPy_lk_cFP4cXyzP4cXyz */
void daPy_lk_c::getWHideNextPos(cXyz* param_0, cXyz* param_1) {
    param_1->set(
        param_0->x + cM_ssin(current.angle.y) * daPy_HIO_wall_c0::m.field_0x54,
        param_0->y,
        param_0->z + cM_scos(current.angle.y) * daPy_HIO_wall_c0::m.field_0x54
    );
}

/* 8013769C-80137754       .text checkWHideBackWall__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::checkWHideBackWall(cXyz* param_0) {
    if (param_0 == NULL) {
        return true;
    }

    cXyz local_18;
    local_18.set(param_0->x - 25.0f * cM_ssin(shape_angle.y), param_0->y, param_0->z - 25.0f * cM_scos(shape_angle.y));
    mLinkLinChk.Set(param_0, &local_18, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        return true;
    }

    return false;
}

/* 80137754-80137828       .text checkWHideFrontFloor__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::checkWHideFrontFloor(cXyz* param_0) {
    cXyz local_10(param_0->x + 40.0f * cM_ssin(shape_angle.y), param_0->y, param_0->z + 40.0f * cM_scos(shape_angle.y));
    mGndChk.SetPos(&local_10);
    f32 ground_y = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if (checkNoResetFlg0(daPyFlg0_UNK80000000) && current.pos.y > ground_y) {
        ground_y = current.pos.y;
    }
    return std::fabsf(ground_y - current.pos.y) < 5.0f;
}

/* 80137828-80137914       .text checkWHideModeChange__9daPy_lk_cFP4cXyz */
int daPy_lk_c::checkWHideModeChange(cXyz* param_0) {
    if (!checkNoResetFlg0(daPyFlg0_UNK10000)) {
        if (!checkWHideFrontFloor(param_0)) {
            dComIfGp_setRStatus(dActStts_BLANK_e);
        } else if (spActionButton()) {
            return 1;
        }
    } else {
        cXyz local_18;
        local_18.set(param_0->x, current.pos.y + 125.0f, param_0->z);
        if (!spActionButton() && !mAcch.ChkRoofHit() && checkWHideBackWall(&local_18)) {
            return -1;
        }
    }
    if (checkModeFlg(ModeFlg_00000001) && mCurProc != daPyProc_WHIDE_PEEP_e) {
        setTextureAnime(mAnmDataTable[ANM_WALL].mTexAnmIdx, 0);
    }
    return 0;
}

/* 80137914-80137A00       .text changeWHideEndProc__9daPy_lk_cFP4cXyz */
int daPy_lk_c::changeWHideEndProc(cXyz* param_0) {
    dComIfGp_setDoStatus(dActStts_SIDLE_e);
    dComIfGp_setRStatus(dActStts_CROUCH_e);

    if (((!doButton() && (!checkNoResetFlg0(daPyFlg0_UNK10000) || !mAcch.ChkRoofHit())) ||
         (!checkUpperAnime(LKANM_BCK_REST) && swordTrigger())) ||
        !checkWHideBackWall(param_0))
    {
        mVelocity = 0.7f * mMaxNormalSpeed;
        current.angle.y = shape_angle.y;
        return checkNextMode(0);
    }

    if (checkNoResetFlg0(daPyFlg0_UNK10000) && mAcch.ChkRoofHit()) {
        onModeFlg(ModeFlg_04000000);
    } else {
        offModeFlg(ModeFlg_04000000);
    }

    return false;
}

/* 80137A00-80137BD8       .text procWHideReady_init__9daPy_lk_cFP8cM3dGPlaP4cXyz */
BOOL daPy_lk_c::procWHideReady_init(cM3dGPla* param_0, cXyz* param_1) {
    BOOL uVar1 = checkModeFlg(ModeFlg_WHIDE) ? TRUE : FALSE;
    offNoResetFlg0(daPyFlg0_UNK10000);
    commonProcInit(daPyProc_WHIDE_READY_e);
    mVelocity = 0.0f;
    current.angle.y = shape_angle.y;
    m370C.x = param_1->x;
    m370C.y = param_1->y;
    m370C.z = param_1->z;
    if (param_0 != NULL) {
        m34D4 = cM_atan2s(param_0->mNormal.x, param_0->mNormal.z);
        m370C.x += param_0->mNormal.x * daPy_HIO_wall_c0::m.field_0x50;
        m370C.z += param_0->mNormal.z * daPy_HIO_wall_c0::m.field_0x50;
    } else {
        m34D4 = m352C;
        m370C.x += cM_ssin(m352C) * daPy_HIO_wall_c0::m.field_0x50;
        m370C.z += cM_scos(m352C) * daPy_HIO_wall_c0::m.field_0x50;
    }
    if (mEquipItem == daPyItem_NONE_e) {
        if (checkEquipAnime()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        }
        setSingleMoveAnime(ANM_WALL, 0.0f, daPy_HIO_wall_c0::m.field_0x24, -1, daPy_HIO_wall_c0::m.field_0x34);
        mProcVar0.m3570 = 1;
    } else {
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
        setAnimeUnequip();
        mProcVar0.m3570 = 0;
    }
    if (uVar1 != 0) {
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK1_e);
    }
    return true;
}

/* 80137BD8-80137CD0       .text procWHideReady__9daPy_lk_cFv */
BOOL daPy_lk_c::procWHideReady() {
    if (changeWHideEndProc(NULL)) {
        return true;
    }
    if (mProcVar0.m3570 == 0) {
        if (checkNoUpperAnime()) {
            setSingleMoveAnime(ANM_WALL, 0.0f, daPy_HIO_wall_c0::m.field_0x24, -1, daPy_HIO_wall_c0::m.field_0x34);
            mProcVar0.m3570 = 1;
        }
        return true;
    }
    cLib_addCalc(&current.pos.x, m370C.x, 0.25f, 10.0f, 4.0f);
    cLib_addCalc(&current.pos.z, m370C.z, 0.25f, 10.0f, 4.0f);
    if (!cLib_addCalcAngleS(&shape_angle.y, m34D4, 2, 0x2000, 0x800)) {
        daPy_matAnm_c::offMabaFlg();
        procWHideWait_init();
    }
    return true;
}

/* 80137CD0-80137DF0       .text procWHideWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWHideWait_init() {
    f32 fVar1;
    daPy_ANM dVar3;
    f32 dVar4;
    f32 dVar5;
    s16 sVar2;

    if (!checkNoResetFlg0(daPyFlg0_UNK10000)) {
        dVar3 = ANM_WALL;
        sVar2 = daPy_HIO_wall_c0::m.field_0x0;
        dVar4 = daPy_HIO_wall_c0::m.field_0x38;
    } else {
        dVar3 = ANM_WALLDW;
        sVar2 = daPy_HIO_wall_c0::m.field_0x2;
        dVar4 = daPy_HIO_wall_c0::m.field_0x3C;
    }
    if (mCurProc == daPyProc_WHIDE_READY_e) {
        fVar1 = daPy_HIO_wall_c0::m.field_0x24;
    } else {
        fVar1 = sVar2 - 0.001f;
    }
    dVar5 = fVar1;
    commonProcInit(daPyProc_WHIDE_WAIT_e);
    mVelocity = 0.0f;
    setSingleMoveAnime(dVar3, daPy_HIO_wall_c0::m.field_0xC, dVar5, sVar2, dVar4);
    current.angle.y = shape_angle.y;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK1_e);
    return true;
}

/* 80137DF0-80138074       .text procWHideWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procWHideWait() {
    cXyz cStack_3c;
    cXyz cStack_48;

    getWHideBasePos(&cStack_3c);
    if (changeWHideEndProc(&cStack_3c)) {
        return true;
    }

    int iVar1 = checkWHideModeChange(&cStack_3c);
    if (iVar1 == 1) {
        setSingleMoveAnime(
            ANM_WALLDW,
            daPy_HIO_wall_c0::m.field_0x10,
            daPy_HIO_wall_c0::m.field_0x28,
            daPy_HIO_wall_c0::m.field_0x2,
            daPy_HIO_wall_c0::m.field_0x3C
        );
        onNoResetFlg0(daPyFlg0_UNK10000);
        mAcchCir[2].SetWallH(89.9f);
    } else if (iVar1 == -1) {
        setSingleMoveAnime(
            ANM_WALLDW,
            -daPy_HIO_wall_c0::m.field_0x10,
            daPy_HIO_wall_c0::m.field_0x28,
            daPy_HIO_wall_c0::m.field_0x2,
            daPy_HIO_wall_c0::m.field_0x3C
        );
        mFrameCtrlUnder[UNDER_MOVE0_e].setFrame(daPy_HIO_wall_c0::m.field_0x2 - 0.001f);
        mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform()->setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
        offNoResetFlg0(daPyFlg0_UNK10000);
        mAcchCir[2].SetWallH(125.0f);
    }

    if (mStickDistance > 0.05f && -G_CM3D_F_INF != mAcch.GetGroundH() &&
        cBgW_CheckBGround(dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd)->GetNP()->y))
    {
        int direction = getDirectionFromCurrentAngle();
        if (direction == DIR_RIGHT || direction == DIR_LEFT) {
            if (direction == DIR_RIGHT) {
                current.angle.y = shape_angle.y + -0x4000;
                mDirection = DIR_RIGHT;
            } else {
                current.angle.y = shape_angle.y + 0x4000;
                mDirection = DIR_LEFT;
            }

            getWHideNextPos(&cStack_3c, &cStack_48);
            BOOL iVar1 = checkWHideBackWall(&cStack_48);
            if (iVar1 && (!checkNoResetFlg0(daPyFlg0_UNK10000) || checkWHideFrontFloor(&cStack_48))) {
                return procWHideMove_init();
            }
            if (!iVar1) {
                cStack_48 += (cStack_48 - cStack_3c) * 0.25f;
                mLinkLinChk.Set(&cStack_3c, &cStack_48, this);
                if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                    return procWHidePeep_init();
                }
            }
        }
    }

    current.angle.y = shape_angle.y;
    return true;
}

/* 80138074-801380F0       .text procWHideMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWHideMove_init() {
    commonProcInit(daPyProc_WHIDE_MOVE_e);
    if (mDirection == DIR_LEFT) {
        current.angle.y = shape_angle.y + 0x4000;
    } else {
        current.angle.y = shape_angle.y + -0x4000;
    }
    setBlendWHideMoveAnime(1.0f);
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK1_e);
    return true;
}

/* 801380F0-8013852C       .text procWHideMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procWHideMove() {
    if (changeSlideProc()) {
        return true;
    }

    cXyz acStack_24;
    getWHideBasePos(&acStack_24);
    s16 uVar1 = current.angle.y;
    if (changeWHideEndProc(&acStack_24)) {
        if (!doButton() && mStickDistance > 0.05f) {
            uint uVar3 = (uint)uVar1;
            current.pos.x += 50.0f * cM_ssin(uVar3);
            current.pos.z += 50.0f * cM_scos(uVar3);
        }
        return true;
    }

    cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
    s16 sVar8 = cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z);
    f32 fVar2;
    if (checkWHideModeChange(&acStack_24) != 0) {
        fVar2 = 0.0f;
    } else if (mStickDistance > 0.05f && -G_CM3D_F_INF != mAcch.GetGroundH() &&
               cBgW_CheckBGround(dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd)->GetNP()->y))
    {
        int direction = getDirectionFromCurrentAngle();
        if (direction == DIR_BACKWARD) {
            current.angle.y -= -0x8000;
            mVelocity *= 0.5f;
            if (mDirection == DIR_LEFT) {
                mDirection = DIR_RIGHT;
            } else {
                mDirection = DIR_LEFT;
            }
            setBlendWHideMoveAnime(2.0f);
        }
        if (direction == DIR_FORWARD || direction == DIR_BACKWARD) {
            fVar2 = daPy_HIO_move_c0::m.field_0x14;
            fVar2 *= mStickDistance;
        } else {
            fVar2 = 0.0f;
        }
    } else {
        fVar2 = 0.0f;
    }

    cXyz cStack_30;
    setNormalSpeedF(fVar2, 0.5f, 2.0f, 0.25f);
    getWHideNextPos(&acStack_24, &cStack_30);
    if (checkNoResetFlg0(daPyFlg0_UNK10000) && !checkWHideFrontFloor(&cStack_30)) {
        mVelocity = 0.0f;
        return procWHideWait_init();
    }

    cXyz cStack_3c;
    triPla = getWHideModePolygon(&acStack_24, &cStack_30, &cStack_3c, mDirection);
    if (triPla != NULL) {
        return procWHideReady_init(triPla, &cStack_3c);
    }
    if (std::fabsf(mVelocity) <= 0.001f) {
        return procWHideWait_init();
    }
    if (mAcch.GetGroundH() == -G_CM3D_F_INF || !cBgW_CheckBGround(dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd)->GetNP()->y) ||
        !checkWHideBackWall(&cStack_30))
    {
        mVelocity = 0.0f;
        return procWHideWait_init();
    }

    cXyz cStack_48;
    if (sVar8 != shape_angle.y && getWHideModePolygon(NULL, NULL, &cStack_48, mDirection) != NULL) {
        if ((s16)(current.angle.y - shape_angle.y) > 0) {
            current.angle.y = sVar8 + 0x4000;
        } else {
            current.angle.y = sVar8 - 0x4000;
        }
        shape_angle.y = sVar8;
        current.pos.x += 8.0f * cM_ssin(current.angle.y);
        current.pos.z += 8.0f * cM_scos(current.angle.y);
    }
    current.pos.x -= 0.8f * daPy_HIO_wall_c0::m.field_0x50 * cM_ssin(shape_angle.y);
    current.pos.z -= 0.8f * daPy_HIO_wall_c0::m.field_0x50 * cM_scos(shape_angle.y);
    setBlendWHideMoveAnime(-1.0f);
    return true;
}

/* 8013852C-801385EC       .text procWHidePeep_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procWHidePeep_init() {
    f32 fVar1;
    f32 fVar2;
    f32 fVar3;
    s16 sVar4;
    daPy_ANM dVar2;

    commonProcInit(daPyProc_WHIDE_PEEP_e);
    if (!checkNoResetFlg0(daPyFlg0_UNK10000)) {
        fVar1 = daPy_HIO_wall_c0::m.field_0x1C;
        fVar3 = daPy_HIO_wall_c0::m.field_0x48;
        fVar2 = daPy_HIO_wall_c0::m.field_0x2C;
        sVar4 = daPy_HIO_wall_c0::m.field_0x4;
        if (mDirection == DIR_LEFT) {
            dVar2 = ANM_WALLPR;
        } else {
            dVar2 = ANM_WALLPL;
        }
    } else {
        fVar1 = daPy_HIO_wall_c0::m.field_0x20;
        fVar3 = daPy_HIO_wall_c0::m.field_0x4C;
        fVar2 = daPy_HIO_wall_c0::m.field_0x30;
        sVar4 = daPy_HIO_wall_c0::m.field_0x6;
        if (mDirection == DIR_LEFT) {
            dVar2 = ANM_WALLPRDW;
        } else {
            dVar2 = ANM_WALLPLDW;
        }
    }
    setSingleMoveAnime(dVar2, fVar1, fVar2, sVar4, fVar3);
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK1_e);
    return true;
}

/* 801385EC-801387A4       .text procWHidePeep__9daPy_lk_cFv */
BOOL daPy_lk_c::procWHidePeep() {
    cXyz cStack_38;

    getWHideBasePos(&cStack_38);
    if (changeWHideEndProc(&cStack_38)) {
        return true;
    }

    f32 dVar3 = mFrameCtrlUnder[UNDER_MOVE0_e].getRate();
    if (std::fabsf(dVar3) < 0.01f) {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() < (mFrameCtrlUnder[UNDER_MOVE0_e].getStart() + 1)) {
            return procWHideWait_init();
        }
    }

    if (std::fabsf(dVar3) < 0.01f) {
        if (mDirection == DIR_LEFT) {
            dComIfGp_setPlayerStatus0(0, daPyStts0_UNK40_e);
        } else {
            dComIfGp_setPlayerStatus0(0, daPyStts0_UNK20_e);
        }
        if (!checkNoResetFlg0(daPyFlg0_UNK10000)) {
            dVar3 = daPy_HIO_wall_c0::m.field_0x1C;
        } else {
            dVar3 = daPy_HIO_wall_c0::m.field_0x20;
        }
    }

    if (checkWHideModeChange(&cStack_38) != 0) {
        if (dVar3 > 0.0f) {
            mFrameCtrlUnder[UNDER_MOVE0_e].setRate(-dVar3);
        }
    } else if (mStickDistance > 0.05f) {
        int direction = getDirectionFromCurrentAngle();
        if ((direction != DIR_FORWARD && dVar3 > 0.0f) || (direction == 0 && dVar3 < 0.0f)) {
            mFrameCtrlUnder[UNDER_MOVE0_e].setRate(-dVar3);
        }
    } else if (dVar3 > 0.0f) {
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(-dVar3);
    }

    return true;
}
