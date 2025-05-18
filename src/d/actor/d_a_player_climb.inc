/**
 * d_a_player_climb.inc
 *
 * Code relating to climbing on walls (like vines).
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"

/* 80135B50-80135B74       .text getClimbMoveAnmSpeed__9daPy_lk_cFv */
f32 daPy_lk_c::getClimbMoveAnmSpeed() {
    return daPy_HIO_ladder_c0::m.field_0x34 +
           (mStickDistance * (daPy_HIO_ladder_c0::m.field_0x30 - daPy_HIO_ladder_c0::m.field_0x34));
}

/* 80135B74-80135DA0       .text setClimbShapeOffset__9daPy_lk_cFv */
void daPy_lk_c::setClimbShapeOffset() {
    cXyz local_40;
    cXyz local_4c;
    cXyz local_58;
    cXyz local_64;

    s16 uVar3 = m34EC;
    s32 uVar4 = shape_angle.y;
    uVar3 += uVar4;
    f32 fVar4 = cM_ssin(uVar3);
    f32 fVar3 = cM_scos(uVar3);
    f32 fVar2 = cM_ssin((s32)uVar4);
    local_58.x = current.pos.x + 20.5f * fVar2;
    local_58.y = current.pos.y - 62.5f;
    f32 fVar1 = cM_scos(uVar4);
    local_58.z = current.pos.z + 20.5f * fVar1;
    local_40.set(local_58.x - fVar4 * 50.0f, local_58.y, local_58.z - fVar3 * 50.0f);
    local_4c.set(local_58.x + fVar4 * 50.0f, local_58.y, local_58.z + fVar3 * 50.0f);
    f32 dVar10 = fVar3 * 20.0f;
    f32 dVar9 = fVar4 * -20.0f;
    local_40.x += dVar10;
    local_40.z += dVar9;
    local_4c.x += dVar10;
    local_4c.z += dVar9;
    mLinkLinChk.Set(&local_40, &local_4c, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        local_64 = mLinkLinChk.GetCross();
    } else {
        m34EC = 0;
        return;
    }
    local_40.x -= dVar10 * 2.0f;
    local_40.z -= dVar9 * 2.0f;
    local_4c.x -= dVar10 * 2.0f;
    local_4c.z -= dVar9 * 2.0f;
    mLinkLinChk.Set(&local_40, &local_4c, this);
    if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        m34EC = 0;
    } else {
        local_64 -= mLinkLinChk.GetCross();
        m34EC = (cM_atan2s(local_64.x, local_64.z) - 0x4000 - shape_angle.y);
    }
}

/* 80135DA0-80135E14       .text getClimbDirectionFromAngle__9daPy_lk_cFv */
int daPy_lk_c::getClimbDirectionFromAngle() {
    s16 angle = m34E8 - shape_angle.y;
    if (abs(angle) > 0x7000) {
        return DIR_BACKWARD;
    } else if (angle >= 0x1000) {
        return DIR_LEFT;
    } else if (angle <= -0x1000) {
        return DIR_RIGHT;
    } else {
        return DIR_FORWARD;
    }
}

/* 80135E14-80135E98       .text changeClimbMoveProc__9daPy_lk_cFi */
void daPy_lk_c::changeClimbMoveProc(int param_0) {
    s16 sVar1;

    sVar1 = m34EC;
    if (mStickDistance > 0.05f) {
        mDirection = getClimbDirectionFromAngle();
        if (mDirection == DIR_FORWARD || mDirection == DIR_BACKWARD) {
            procClimbMoveUpDown_init(param_0);
        } else {
            procClimbMoveSide_init(param_0);
        }
    }
    m34EC = sVar1;
}

/* 80135E98-80136154       .text setMoveBGCorrectClimb__9daPy_lk_cFv */
BOOL daPy_lk_c::setMoveBGCorrectClimb() {
    if (dComIfG_Bgsp()->ChkPolySafe(mPolyInfo) && dComIfG_Bgsp()->ChkMoveBG(mPolyInfo)) {
        dComIfG_Bgsp()->MoveBgTransPos(mPolyInfo, true, &current.pos, &current.angle, &shape_angle);
    }
    if (checkNoResetFlg1(daPyFlg1_VINE_CATCH)) {
        return procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
    }

    if (mCurProc == daPyProc_CLIMB_DOWN_START_e && (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() > 0.01f)) {
        return 0;
    }
    cXyz local_1c;
    cXyz local_28;
    local_1c.set(current.pos.x, current.pos.y + 30.0f, current.pos.z);
    local_28.set(
        current.pos.x + cM_ssin(shape_angle.y) * 80.0f, local_1c.y, current.pos.z + cM_scos(shape_angle.y) * 80.0f
    );
    mLinkLinChk.Set(&local_1c, &local_28, this);
    if ((!dComIfG_Bgsp()->LineCross(&mLinkLinChk) || dComIfG_Bgsp()->GetWallCode(mLinkLinChk) != 1 ||
         std::fabsf(dComIfG_Bgsp()->GetTriPla(mLinkLinChk)->GetNP()->y) > 0.05f) ||
        ((mCurProc == daPyProc_CLIMB_MOVE_UP_DOWN_e || mCurProc == daPyProc_CLIMB_MOVE_SIDE_e) &&
         current.pos.y - 15.0f < mAcch.GetGroundH()))
    {
        return procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
    }

    cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
    s16 uVar6 = cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z);
    if (cLib_distanceAngleS(uVar6, shape_angle.y) <= 0x549f) {
        return procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
    }

    current.pos.x = mLinkLinChk.GetCrossP()->x + 20.5f * cM_ssin(uVar6);
    current.pos.z = mLinkLinChk.GetCrossP()->z + 20.5f * cM_scos(uVar6);
    s16 sVar1 = shape_angle.y;
    shape_angle.y = uVar6 + 0x8000;
    current.angle.y += (s16)(shape_angle.y - sVar1);
    m34EC += (s16)(sVar1 - shape_angle.y);

    return 0;
}

/* 80136154-80136200       .text checkBgCorrectClimbMove__9daPy_lk_cFP4cXyzP4cXyz */
void daPy_lk_c::checkBgCorrectClimbMove(cXyz* i_startPos, cXyz* i_endPos) {
    mLinkLinChk.Set(i_startPos, i_endPos, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        cM3dGPla* tri_plane = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
        if (cLib_distanceAngleS(cM_atan2s(tri_plane->GetNP()->x, tri_plane->GetNP()->z), shape_angle.y) < 0x549F) {
            current.pos += mLinkLinChk.GetCross() - *i_endPos;
        }
    }
}

/* 80136200-80136588       .text checkBgClimbMove__9daPy_lk_cFv */
void daPy_lk_c::checkBgClimbMove() {
    cXyz local_5c;
    cXyz local_68;

    f32 dVar7 = cM_ssin(shape_angle.y);
    f32 dVar6 = cM_scos(shape_angle.y);
    f32 dVar5 = 30.0f * dVar6;
    f32 dVar4 = -30.0f * dVar7;
    local_5c.set(current.pos.x + dVar5, current.pos.y, current.pos.z + dVar4);
    checkBgCorrectClimbMove(&current.pos, &local_5c);

    local_5c.set(current.pos.x - dVar5, current.pos.y, current.pos.z - dVar4);
    checkBgCorrectClimbMove(&current.pos, &local_5c);

    local_68.set(current.pos.x, current.pos.y + 125.0f, current.pos.z);
    local_5c.set(local_68.x + dVar5, local_68.y, local_68.z + dVar4);
    checkBgCorrectClimbMove(&local_68, &local_5c);

    local_5c.set(local_68.x - dVar5, local_68.y, local_68.z - dVar4);
    checkBgCorrectClimbMove(&local_68, &local_5c);

    local_5c.set(current.pos.x + dVar5, current.pos.y, current.pos.z + dVar4);
    mRoofChk.SetPos(local_5c);
    f32 dVar3 = dComIfG_Bgsp()->RoofChk(&mRoofChk);
    if (dVar3 - 125.0f < current.pos.y) {
        current.pos.y = dVar3 - 125.0f;
    }
    local_5c.set(current.pos.x - dVar5, current.pos.y, current.pos.z - dVar4);
    mRoofChk.SetPos(local_5c);
    dVar3 = dComIfG_Bgsp()->RoofChk(&mRoofChk);
    if (dVar3 - 125.0f < current.pos.y) {
        current.pos.y = dVar3 - 125.0f;
    }
    local_5c.x = local_68.x + (100.0f * dVar7);
    local_5c.y = local_68.y;
    local_5c.z = local_68.z + (100.0f * dVar6);
    mLinkLinChk.Set(&local_68, &local_5c, this);
    if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        local_5c.set(current.pos.x + (25.0f * dVar7), local_68.y + 30.0f, current.pos.z + (25.0f * dVar6));
        mGndChk.SetPos(&local_5c);
        dVar3 = dComIfG_Bgsp()->GroundCross(&mGndChk);
        if (C_BG_MIN_HEIGHT != dVar3 && cBgW_CheckBGround(dComIfG_Bgsp()->GetTriPla(mGndChk)->GetNP()->y) &&
            dVar3 >= local_68.y - 30.0f)
        {
            dVar4 = 3.0f;
            current.pos.x = local_5c.x - (dVar4 * dVar7);
            current.pos.y = dVar3;
            current.pos.z = local_5c.z - (dVar4 * dVar6);
            procHangClimb_init(daPy_HIO_wallCatch_c0::m.field_0x2C);
        } else {
            procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
        }
    } else {
        setClimbShapeOffset();
    }
}

/* 80136588-801365F4       .text procClimbUpStart_init_sub__9daPy_lk_cFv */
void daPy_lk_c::procClimbUpStart_init_sub() {
    setSingleMoveAnime(ANM_LADDERUPST, daPy_HIO_ladder_c0::m.field_0x4, 0.0f, -1, daPy_HIO_ladder_c0::m.field_0x8);
    mProcVar0.m3570 = 1;
    m34C2 = 4;
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK10000_e);
}

/* 801365F4-80136708       .text procClimbUpStart_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procClimbUpStart_init() {
    commonProcInit(daPyProc_CLIMB_UP_START_e);
    gravity = 0.0f;
    speed.y = 0.0f;
    mVelocity = 0.0f;
    speedF = 0.0f;
    if (mEquipItem == daPyItem_NONE_e) {
        if (checkEquipAnime()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        }
        procClimbUpStart_init_sub();
    } else {
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
        setAnimeUnequip();
        mProcVar0.m3570 = 0;
        m3598 = 0.0f;
    }
    f32 fVar2 = cM_ssin(m352C);
    f32 fVar1 = cM_scos(m352C);
    current.pos.x = m3724.x + 25.0f * fVar2;
    current.pos.z = m3724.z + 25.0f * fVar1;
    shape_angle.y = m352C + 0x8000;
    current.angle.y = shape_angle.y;
    m34D4 = 0;
    return true;
}

/* 80136708-8013680C       .text procClimbUpStart__9daPy_lk_cFv */
BOOL daPy_lk_c::procClimbUpStart() {
    if (setMoveBGCorrectClimb()) {
        return true;
    }

    if (mProcVar0.m3570 == 0) {
        if (checkNoUpperAnime()) {
            procLadderUpStart_init_sub();
        }
    } else {
        J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
        m34C2 = 5;
        if (frameCtrl.getRate() < 0.01f) {
            dComIfGp_setDoStatus(dActStts_LET_GO_e);
            if (m34D4 == 0) {
                setLadderFootSe();
                m34D4 = 1;
            }
            if (doTrigger()) {
                m34C2 = 0;
                procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
            } else {
                changeClimbMoveProc(1);
            }
        } else if (frameCtrl.checkPass(9.0f)) {
            setLadderFootSe();
        }
    }

    return true;
}

/* 8013680C-8013693C       .text procClimbDownStart_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procClimbDownStart_init(s16 param_0) {
    commonProcInit(daPyProc_CLIMB_DOWN_START_e);
    gravity = 0.0f;
    speed.y = 0.0f;
    mVelocity = 0.0f;
    speedF = 0.0f;
    deleteEquipItem(TRUE);
    setSingleMoveAnime(ANM_LADDERDWST, daPy_HIO_ladder_c0::m.field_0x14, 30.0f, -1, 3.0f);
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK10000_e);
    setOldRootQuaternion(0, -0x8000, 0);
    shape_angle.y = param_0 + 0x8000;
    current.angle.y = shape_angle.y;
    current.pos.x = current.pos.x - 35.0f * cM_ssin(param_0);
    current.pos.y = current.pos.y - 20.0f;
    current.pos.z = current.pos.z - 35.0f * cM_scos(param_0);
    m35E0 = 43.67353f;
    mProcVar0.m3570 = 1;
    return true;
}

/* 8013693C-80136A34       .text procClimbDownStart__9daPy_lk_cFv */
BOOL daPy_lk_c::procClimbDownStart() {
    if (setMoveBGCorrectClimb()) {
        return true;
    }

    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m34C2 = 5;
    if (frameCtrl.getRate() < 0.01f) {
        dComIfGp_setDoStatus(dActStts_LET_GO_e);
        if (doTrigger()) {
            m34C2 = 0;
            procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
        } else {
            changeClimbMoveProc(1);
        }
    } else if (frameCtrl.checkPass(26.0f) || frameCtrl.checkPass(36.0f) || frameCtrl.checkPass(43.0f)) {
        setLadderFootSe();
    }

    return true;
}

/* 80136A34-80136B80       .text procClimbMoveUpDown_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procClimbMoveUpDown_init(int param_0) {
    daPy_ANM dVar2;
    float dVar3;

    dVar3 = getLadderMoveAnmSpeed();
    commonProcInit(daPyProc_CLIMB_MOVE_UP_DOWN_e);
    current.angle.y = shape_angle.y;
    if (mDirection == DIR_BACKWARD) {
        dVar3 *= -1.0f;
    }
    if (param_0 != 0) {
        mProcVar0.m3570 = 0;
        if (mDirection == DIR_FORWARD) {
            dVar2 = ANM_LADDERLTOR;
        } else {
            dVar2 = ANM_LADDERRTOL;
        }
    } else {
        mProcVar0.m3570 = 1;
        if (mDirection == DIR_FORWARD) {
            dVar2 = ANM_LADDERRTOL;
        } else {
            dVar2 = ANM_LADDERLTOR;
        }
    }
    setSingleMoveAnime(dVar2, dVar3, 0.0f, -1, daPy_HIO_ladder_c0::m.field_0x2C);
    if (mDirection == DIR_FORWARD) {
        setTextureAnime(10, 0);
    } else {
        setTextureAnime(11, 0);
    }
    m34C2 = 7;
    gravity = 0.0f;
    speed.y = 0.0f;
    mVelocity = 0.0f;
    speedF = 0.0f;
    m34D0 = 1;
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK10000_e);
    return true;
}

/* 80136B80-80136C7C       .text procClimbMoveUpDown__9daPy_lk_cFv */
BOOL daPy_lk_c::procClimbMoveUpDown() {
    if (setMoveBGCorrectClimb()) {
        return true;
    }

    m34C2 = 5;
    dComIfGp_setDoStatus(dActStts_LET_GO_e);
    if (doTrigger()) {
        m34C2 = 0;
        procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
    } else if (std::fabsf(mFrameCtrlUnder[UNDER_MOVE0_e].getRate()) < 0.01f) {
        if (m34D0 != 0) {
            m34D0 = 0;
            setLadderFootSe();
        } else {
            changeClimbMoveProc(mProcVar0.m3570);
        }
    } else {
        f32 dVar2 = getLadderMoveAnmSpeed();
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.0f) {
            dVar2 *= -1.0f;
        }
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(dVar2);
        checkBgClimbMove();
    }
    return true;
}

/* 80136C7C-80136E28       .text procClimbMoveSide_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procClimbMoveSide_init(int param_0) {
    daPy_ANM dVar2;
    float dVar4;

    dVar4 = getClimbMoveAnmSpeed();
    commonProcInit(daPyProc_CLIMB_MOVE_SIDE_e);
    m34D4 = m34E8 - shape_angle.y;
    m34C2 = 7;
    mProcVar0.m3570 = param_0;
    if (param_0 != 0) {
        dVar2 = ANM_FCLIMBSLIDELUP;
        if (mDirection == DIR_RIGHT) {
            dVar4 *= -1.0f;
        }
    } else {
        dVar2 = ANM_FCLIMBSLIDERUP;
        if (mDirection == DIR_LEFT) {
            dVar4 *= -1.0f;
        }
    }
    setSingleMoveAnime(
        dVar2,
        dVar4,
        daPy_HIO_ladder_c0::m.field_0x38,
        daPy_HIO_ladder_c0::m.field_0x0,
        daPy_HIO_ladder_c0::m.field_0x3C
    );
    gravity = 0.0f;
    speed.y = 0.0f;
    mVelocity = 0.0f;
    speedF = 0.0f;
    m34D0 = 1;
    dComIfGp_setPlayerStatus1(0, daPyStts1_UNK10000_e);
    cXyz local_38 = mRightHandPos - mLeftHandPos;
    dVar4 = local_38.absXZ();
    m35A0 = dVar4;
    return true;
}

/* 80136E28-8013707C       .text procClimbMoveSide__9daPy_lk_cFv */
BOOL daPy_lk_c::procClimbMoveSide() {
    if (setMoveBGCorrectClimb()) {
        return true;
    }

    m34C2 = 5;
    dComIfGp_setDoStatus(dActStts_LET_GO_e);
    if (doTrigger()) {
        m34C2 = 0;
        procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
    } else if (std::fabsf(mFrameCtrlUnder[UNDER_MOVE0_e].getRate()) < 0.01f) {
        if (m34D0 != 0) {
            m34D0 = 0;
            setLadderFootSe();
        } else {
            changeClimbMoveProc(mProcVar0.m3570);
        }
    } else {
        f32 dVar5 = getClimbMoveAnmSpeed();
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.0f) {
            dVar5 *= -1.0f;
        }
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(dVar5);
        cXyz local_28 = mRightHandPos - mLeftHandPos;
        dVar5 = local_28.absXZ();
        f32 fVar1 = std::fabsf(dVar5 - m35A0) * daPy_HIO_ladder_c0::m.field_0x40;
        f32 fVar2 = fVar1 * cM_ssin(m34D4);
        current.pos.y += fVar1 * cM_scos(m34D4);
        current.pos.x += fVar2 * cM_scos(shape_angle.y);
        current.pos.z -= fVar2 * cM_ssin(shape_angle.y);
        m35A0 = dVar5;
        checkBgClimbMove();
    }
    return true;
}
