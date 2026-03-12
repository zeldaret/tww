/**
 * d_a_player_hang.inc
 *
 * Code relating to hanging and moving on a ledge.
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

/* 80133F1C-80133F40       .text getHangMoveAnmSpeed__9daPy_lk_cFv */
f32 daPy_lk_c::getHangMoveAnmSpeed() {
    return getAnmSpeedStickRate(m_HIO->mHang.m.field_0x24, m_HIO->mHang.m.field_0x28);
}

/* 80133F40-80133FB4       .text getHangDirectionFromAngle__9daPy_lk_cFv */
int daPy_lk_c::getHangDirectionFromAngle() {
    s16 angle = m34E8 - shape_angle.y;
    if (abs(angle) > 0x78E4) {
        return 1;
    }

    if (angle >= 0x071C) {
        return 2;
    }

    if (angle <= -0x071C) {
        return 3;
    }

    return 0;
}

/* 80133FB4-801342D8       .text changeHangMoveProc__9daPy_lk_cFi */
BOOL daPy_lk_c::changeHangMoveProc(int i_direction) {
    s16 uVar1;

    if ((!(mAcch.ChkGroundHit())) || !dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd)) {
        return false;
    }
    if (dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd)->GetNP()->y < 0.9986f) {
        return false;
    }

    if (i_direction == 2) {
        uVar1 = shape_angle.y + 0x4000;
    } else if (i_direction == 3) {
        uVar1 = shape_angle.y + -0x4000;
    } else {
        uVar1 = current.angle.y;
    }
    cXyz local_28;
    cXyz local_34;
    local_28.x = current.pos.x;
    local_28.y = 5.0f + current.pos.y;
    local_28.z = current.pos.z;
    local_34.x = local_28.x + 30.0f * cM_ssin(uVar1);
    local_34.y = local_28.y;
    local_34.z = local_28.z + 30.0f * cM_scos(uVar1);
    mLinkLinChk.Set(&local_28, &local_34, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        return false;
    }

    mGndChk.SetPos(&local_34);
    if (std::fabsf(dComIfG_Bgsp()->GroundCross(&mGndChk) - current.pos.y) > 5.0f) {
        cXyz local_40;
        cXyz local_4c;
        local_40.x = local_34.x;
        local_40.y = current.pos.y - 5.0f;
        local_40.z = local_34.z;
        local_4c.x = local_34.x + 90.0f * cM_ssin(shape_angle.y);
        local_4c.y = local_40.y;
        local_4c.z = local_34.z + 90.0f * cM_scos(shape_angle.y);
        mLinkLinChk.Set(&local_40, &local_4c, this);
        if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
            return false;
        }
        cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
        if (cLib_distanceAngleS(cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z), shape_angle.y) < 0x549f) {
            return false;
        }
    }
    cXyz local_58;
    local_58.x = cM_ssin(shape_angle.y) * 4.5f;
    local_58.y = 62.5f;
    local_58.z = cM_scos(shape_angle.y) * 4.5f;
    VECSubtract(&local_28, &local_58, &local_28);
    VECSubtract(&local_34, &local_58, &local_34);
    mLinkLinChk.Set(&local_28, &local_34, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
        if (cLib_distanceAngleS(cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z), shape_angle.y) < 0x549f) {
            return false;
        }
    }
    return true;
}

/* 801342D8-80134440       .text changeHangEndProc__9daPy_lk_cFi */
int daPy_lk_c::changeHangEndProc(int param_0) {
    MtxP pMVar6 = mpCLModel->getAnmMtx(0);
    cXyz pos;

    pos.x = pMVar6[0][3] - cM_ssin(shape_angle.y) * 4.0f;
    pos.y = pMVar6[1][3];
    pos.z = pMVar6[2][3] - cM_scos(shape_angle.y) * 4.0f;

    mGndChk.SetPos(&pos);
    mHangGroundH = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if (-G_CM3D_F_INF != mHangGroundH) {
        m3588 = dComIfG_Bgsp()->GetAttributeCode(mGndChk);
    } else {
        m3588 = dBgS_Attr_UNK1B_e;
    }
    if (mHangGroundH > mFootData[1].field_0x018.y + current.pos.y) {
        return procLand_init(m_HIO->mAutoJump.m.field_0x24, 0);
    }
    if (param_0 != 0) {
        dComIfGp_setDoStatus(dActStts_LET_GO_e);
        if (doTrigger()) {
            speed.y = 0.0f;
            return procFall_init(1, m_HIO->mWallCatch.m.field_0x54);
        }
    }
    return false;
}

/* 80134440-80134630       .text setHangShapeOffset__9daPy_lk_cFv */
void daPy_lk_c::setHangShapeOffset() {
    cXyz local_40;
    cXyz local_4c;
    cXyz local_58;

    s16 iVar7 = m34EC + shape_angle.y;
    f32 fVar4 = cM_ssin(iVar7);
    f32 fVar3 = cM_scos(iVar7);
    local_40.set(current.pos.x - fVar4 * 50.0f, current.pos.y - 5.0f, current.pos.z - fVar3 * 50.0f);
    local_4c.set(current.pos.x + fVar4 * 50.0f, current.pos.y - 5.0f, current.pos.z + fVar3 * 50.0f);
    f32 dVar10 = fVar3 * 20.0f;
    f32 dVar9 = fVar4 * -20.0f;
    local_40.x += dVar10;
    local_40.z += dVar9;
    local_4c.x += dVar10;
    local_4c.z += dVar9;
    mLinkLinChk.Set(&local_40, &local_4c, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        local_58 = mLinkLinChk.GetCross();
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
        local_58 -= mLinkLinChk.GetCross();
        m34EC = (cM_atan2s(local_58.x, local_58.z) - 0x4000 - shape_angle.y);
    }
}

/* 80134630-80134908       .text procHangStart_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHangStart_init() {
    cXyz local_1c;
    cXyz local_28;
    cXyz local_34;

    if (mCurProc != daPyProc_ROPE_UP_HANG_e && mCurProc != daPyProc_ROPE_UP_e) {
        local_34.set(m3724.x, 0.0f, m3724.z);
        local_28.set(current.pos.x, 0.0f, current.pos.z);
        if (local_34.abs(local_28) > (mAcchCir[0].GetWallR() + 20.0f)) {
            return false;
        }
    }
    s32 sVar3 = 0;
    if (mCurProc != daPyProc_ROPE_UP_HANG_e && mCurProc != daPyProc_ROPE_UP_e) {
        local_1c.x = m3724.x - 1.5f * cM_ssin(m352C);
        local_1c.y = m3724.y + 10.0f;
        local_1c.z = m3724.z - 1.5f * cM_scos(m352C);
        mGndChk.SetPos(&local_1c);
        local_1c.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
        if (std::fabsf(local_1c.y - m3724.y) > 30.1f) {
            return false;
        }
    } else {
        local_1c.x = m3724.x - 2.25f * cM_ssin(m352C);
        local_1c.y = m3724.y + 10.0f;
        local_1c.z = m3724.z - 2.25f * cM_scos(m352C);
        if (!strcmp(dComIfGp_getStartStageName(), "GanonK")) {
            sVar3 = 1;
        }
    }
    commonProcInit(daPyProc_HANG_START_e);
    mProcVar0.m3570 = sVar3;
    setSingleMoveAnime(
        ANM_VJMPCHA,
        m_HIO->mWallCatch.m.field_0x44,
        m_HIO->mWallCatch.m.field_0x4C,
        m_HIO->mWallCatch.m.field_0x2,
        m_HIO->mWallCatch.m.field_0x48
    );
    current.pos = local_1c;
    shape_angle.y = m352C + 0x8000;
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    speed.y = 0.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK100_e);
    mHangGroundH = mAcch.GetGroundH();
    return true;
}

/* 80134908-801349D8       .text procHangStart__9daPy_lk_cFv */
BOOL daPy_lk_c::procHangStart() {
    if (changeHangEndProc(1)) {
        return true;
    }

    if (((mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) ||
         (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mWallCatch.m.field_0x50)) &&
        (mStickDistance > 0.05f || mProcVar0.m3570 != 0))
    {
        if (getDirectionFromShapeAngle() == DIR_FORWARD || mProcVar0.m3570 != 0) {
            procHangClimb_init(m_HIO->mWallCatch.m.field_0x2C);
        }
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
            procHangWait_init();
        }
    }
    return true;
}

/* 801349D8-80134DF8       .text procHangFallStart_init__9daPy_lk_cFP8cM3dGPla */
BOOL daPy_lk_c::procHangFallStart_init(cM3dGPla* param_0) {
    cXyz local_40;
    cXyz local_4c;

    s16 uVar5 = cM_atan2s(param_0->GetNP()->x, param_0->GetNP()->z);
    current.pos.x -= param_0->GetNP()->x * 1.5f;
    current.pos.z -= param_0->GetNP()->z * 1.5f;
    s16 iVar7 = uVar5 - 0x4000;
    f32 dVar11 = cM_ssin(iVar7) * 30.0f;
    f32 dVar10 = cM_scos(iVar7) * 30.0f;
    local_40.set(
        current.pos.x + (cM_ssin(uVar5) * 4.5f), current.pos.y - 62.5f, current.pos.z + (cM_scos(uVar5) * 4.5f)
    );
    local_4c.set(local_40.x - dVar11, local_40.y, local_40.z - dVar10);
    mLinkLinChk.Set(&local_40, &local_4c, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        param_0 = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
        if (cLib_distanceAngleS(cM_atan2s(param_0->GetNP()->x, param_0->GetNP()->z), shape_angle.y) < 0x549f) {
            current.pos.x += dVar11;
            current.pos.z += dVar10;
            local_40.x += dVar11;
            local_40.z += dVar10;
        }
    }
    local_4c.x = local_40.x + dVar11;
    local_4c.y = local_40.y;
    local_4c.z = local_40.z + dVar10;
    mLinkLinChk.Set(&local_40, &local_4c, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        param_0 = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
        if (cLib_distanceAngleS(cM_atan2s(param_0->GetNP()->x, param_0->GetNP()->z), shape_angle.y) < 0x549f) {
            current.pos.x -= dVar11;
            current.pos.z -= dVar10;
        }
    }
    cXyz local_34;
    local_34.set(current.pos.x, current.pos.y + 50.0f, current.pos.z);
    mGndChk.SetPos(&local_34);
    f32 cross = dComIfG_Bgsp()->GroundCross(&mGndChk);
    local_34.y = cross;
    if (local_34.y != -G_CM3D_F_INF) {
        if (local_34.y < -30.1f + current.pos.y) {
            return false;
        }
        current.pos.y = local_34.y;
    }
    local_34.x += dVar11;
    local_34.y = 50.0f + current.pos.y;
    local_34.z += dVar10;
    mGndChk.SetPos(&local_34);
    cross = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if (cross < (current.pos.y - 50.0f)) {
        local_34.x = current.pos.x - dVar11;
        local_34.z = current.pos.z - dVar10;
        mGndChk.SetPos(&local_34);
        cross = dComIfG_Bgsp()->GroundCross(&mGndChk);
        local_34.y = cross;
        if (local_34.y < current.pos.y - 50.0f) {
            return false;
        }
        current.pos = local_34;
    }
    setOldRootQuaternion(0, shape_angle.y - (uVar5 + 0x8000), 0);
    shape_angle.y = uVar5 + 0x8000;
    current.angle.y = shape_angle.y;

    f32 morf;
    if (mCurProc == daPyProc_FRONT_ROLL_e) {
        morf = 0.0f;
    } else {
        morf = m_HIO->mHang.m.field_0x10;
    }
    commonProcInit(daPyProc_HANG_FALL_START_e);
    setSingleMoveAnime(
        ANM_HANGING, m_HIO->mHang.m.field_0x4, m_HIO->mHang.m.field_0x8, m_HIO->mHang.m.field_0x0, morf
    );
    mVelocity = 0.0f;
    speed.y = 0.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK100_e);
    voiceStart(11);
    return true;
}

/* 80134DF8-80134EF0       .text procHangFallStart__9daPy_lk_cFv */
BOOL daPy_lk_c::procHangFallStart() {
    int iVar2;

    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f ||
        mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mHang.m.field_0xC)
    {
        iVar2 = 1;
    } else {
        iVar2 = 0;
    }
    if (changeHangEndProc(iVar2)) {
        return true;
    }

    if (iVar2 != 0) {
        if (checkModeFlg(ModeFlg_00000400)) {
            offModeFlg(ModeFlg_00000400);
            onModeFlg(ModeFlg_00000100);
        }
        if (checkModeFlg(ModeFlg_00000100)) {
            setTextureAnime(7, 0);
        }
        iVar2 = getHangDirectionFromAngle();
        if (mStickDistance > 0.05f && iVar2 != 1) {
            procHangUp_init(iVar2);
        }
    }
    return true;
}

/* 80134EF0-80134F74       .text procHangUp_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procHangUp_init(int param_0) {
    commonProcInit(daPyProc_HANG_UP_e);
    setSingleMoveAnime(
        ANM_HANGUP,
        m_HIO->mHang.m.field_0x14,
        m_HIO->mHang.m.field_0x18,
        m_HIO->mHang.m.field_0x2,
        m_HIO->mHang.m.field_0x20
    );
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK100_e);
    mProcVar0.m3570 = param_0;
    mVelocity = 0.0f;
    return true;
}

/* 80134F74-80135094       .text procHangUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procHangUp() {
    if (changeHangEndProc(1)) {
        if (mCurProc == daPyProc_FALL_e) {
            current.pos.x = current.pos.x - 8.0f * cM_ssin(shape_angle.y);
            current.pos.z = current.pos.z - 8.0f * cM_scos(shape_angle.y);
        }
        return true;
    }

    if ((mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) ||
        (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mHang.m.field_0x1C))
    {
        if (mProcVar0.m3570 == 0) {
            procHangClimb_init(m_HIO->mWallCatch.m.field_0x2C);
        } else if (changeHangMoveProc(mProcVar0.m3570)) {
            procHangMove_init(mProcVar0.m3570);
        } else {
            procHangWait_init();
        }
    }
    return true;
}

/* 80135094-80135140       .text procHangWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHangWait_init() {
    commonProcInit(daPyProc_HANG_WAIT_e);
    setSingleMoveAnime(ANM_VJMPCHA, 0.0f, m_HIO->mWallCatch.m.field_0x2, -1, 5.0f);
    setTextureAnime(9, 0);
    mpSeAnmFrameCtrl = NULL;
    mVelocity = 0.0f;
    speed.y = 0.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK100_e);
    return true;
}

/* 80135140-801351FC       .text procHangWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procHangWait() {
    int iVar2;

    iVar2 = changeHangEndProc(1);
    if (iVar2 != 0) {
        return true;
    }

    setHangShapeOffset();

    if (mStickDistance > 0.05f) {
        iVar2 = getHangDirectionFromAngle();
        if (iVar2 == 0) {
            procHangClimb_init(m_HIO->mWallCatch.m.field_0x2C);
        } else if (iVar2 != 1 && changeHangMoveProc(iVar2)) {
            s16 sVar1 = m34EC;
            procHangMove_init(iVar2);
            m34EC = sVar1;
        }
    }
    return true;
}

/* 801351FC-80135354       .text procHangMove_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procHangMove_init(int param_0) {
    daPy_ANM dVar1;

    commonProcInit(daPyProc_HANG_MOVE_e);
    if (param_0 == 2) {
        dVar1 = ANM_HANGMOVEL;
        current.angle.y = shape_angle.y + 0x4000;
    } else {
        dVar1 = ANM_HANGMOVER;
        current.angle.y = shape_angle.y + -0x4000;
    }
    f32 dVar3 = getHangMoveAnmSpeed();
    setSingleMoveAnime(dVar1, dVar3, 0.0f, -1, m_HIO->mHang.m.field_0x2C);
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK100_e);
    mVelocity = 0.0f;
    cXyz local_1c = mLeftHandPos - mRightHandPos;
    dVar3 = local_1c.absXZ();
    m35A0 = dVar3;
    return true;
}

/* 80135354-801357C0       .text procHangMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procHangMove() {
    int iVar7 = getHangDirectionFromAngle();

    if (!changeHangEndProc(1)) {
        if (iVar7 == 0 && mStickDistance > 0.05f) {
            procHangClimb_init(m_HIO->mWallCatch.m.field_0x2C);
        } else {
            J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
            frameCtrl.setRate(getHangMoveAnmSpeed());
            if (frameCtrl.checkPass(0.0f) != 0) {
                s16 sVar3 = m34EC;
                if (mStickDistance > 0.05f && iVar7 != 1 && changeHangMoveProc(iVar7)) {
                    procHangMove_init(iVar7);
                } else {
                    procHangWait_init();
                }
                m34EC = sVar3;
            } else {
                cXyz local_64 = mRightHandPos - mLeftHandPos;
                float dVar12 = local_64.absXZ();
                if (changeHangMoveProc(4)) {
                    mVelocity = std::fabsf(dVar12 - m35A0) * m_HIO->mHang.m.field_0x30;
                    float fVar1 = cM_ssin(shape_angle.y);
                    float fVar2 = cM_scos(shape_angle.y);
                    float dVar13 = cM_ssin(current.angle.y);
                    float dVar11 = cM_scos(current.angle.y);
                    cXyz local_70;
                    local_70.set(
                        current.pos.x + (mVelocity * dVar13) - 30.0f * fVar1,
                        current.pos.y - 5.0f,
                        current.pos.z + (mVelocity * dVar11) - 30.0f * fVar2
                    );
                    cXyz local_7c;
                    local_7c.set(local_70.x + 60.0f * fVar1, local_70.y, local_70.z + 60.0f * fVar2);
                    mLinkLinChk.Set(&local_70, &local_7c, this);
                    if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                        mVelocity = 0.0f;
                    } else {
                        cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
                        s16 sVar6 = cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z) + 0x8000;
                        if (sVar6 != shape_angle.y) {
                            if ((s16)(current.angle.y - shape_angle.y) > 0) {
                                current.angle.y = sVar6 + 0x4000;
                            } else {
                                current.angle.y = sVar6 + -0x4000;
                            }
                            s16 sVar7 = shape_angle.y - sVar6;
                            m34EC += sVar7;
                            shape_angle.y = sVar6;
                            cXyz local_88;
                            local_88.set(*mLinkLinChk.GetLinP()->GetEndP());
                            local_88.x -= triPla->GetNP()->x * 1.5f;
                            local_88.y += 25.0f;
                            local_88.z -= triPla->GetNP()->z * 1.5f;
                            mGndChk.SetPos(&local_88);
                            local_88.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
                            if (std::fabsf(local_88.y - current.pos.y) <= 5.0f) {
                                current.pos = local_88;
                            }
                        } else {
                            current.pos.x = (mLinkLinChk.GetLinP()->GetEndP()->x - 1.5f * triPla->GetNP()->x) -
                                            (mVelocity * dVar13);
                            current.pos.z = (mLinkLinChk.GetLinP()->GetEndP()->z - 1.5f * triPla->GetNP()->z) -
                                            (mVelocity * dVar11);
                        }
                    }
                } else {
                    mVelocity = 0.0f;
                }
                m35A0 = dVar12;
            }
            if (checkModeFlg(ModeFlg_HANG)) {
                setHangShapeOffset();
            }
        }
    }
    return true;
}

/* 801357C0-80135874       .text procHangClimb_init__9daPy_lk_cFf */
BOOL daPy_lk_c::procHangClimb_init(f32 param_0) {
    if (mAcch.ChkRoofHit()) {
        return false;
    }

    commonProcInit(daPyProc_HANG_CLIMB_e);
    setSingleMoveAnime(
        ANM_VJMPCL,
        m_HIO->mWallCatch.m.field_0x24,
        param_0,
        m_HIO->mWallCatch.m.field_0x4,
        m_HIO->mWallCatch.m.field_0x28
    );
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK200_e);
    mVelocity = 0.0f;
    voiceStart(32);
    return true;
}

/* 80135874-801358D0       .text procHangClimb__9daPy_lk_cFv */
BOOL daPy_lk_c::procHangClimb() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        checkNextMode(0);
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > m_HIO->mWallCatch.m.field_0x38) {
        checkNextMode(1);
    }
    return true;
}

/* 801358D0-80135AE0       .text procHangWallCatch_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHangWallCatch_init() {
    cXyz local_1c;
    cXyz local_28;
    cXyz local_34;

    local_34.set(m3724.x, 0.0f, m3724.z);
    local_28.set(current.pos.x, 0.0f, current.pos.z);
    if (local_34.abs(local_28) > (mAcchCir[0].GetWallR() + 20.0f)) {
        return false;
    }
    local_1c.x = m3724.x - 1.5f * cM_ssin(m352C);
    local_1c.y = m3724.y + 10.0f;
    local_1c.z = m3724.z - 1.5f * cM_scos(m352C);
    mGndChk.SetPos(&local_1c);
    local_1c.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if (std::fabsf(local_1c.y - m3724.y) > 30.1f) {
        return false;
    }
    commonProcInit(daPyProc_HANG_WALL_CATCH_e);
    setSingleMoveAnime(
        ANM_VJMPCHB,
        m_HIO->mWallCatch.m.field_0x1C,
        m_HIO->mWallCatch.m.field_0x34,
        m_HIO->mWallCatch.m.field_0x0,
        m_HIO->mWallCatch.m.field_0x20
    );
    current.pos = local_1c;
    shape_angle.y = m352C + 0x8000;
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    speed.y = 0.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK100_e);
    return true;
}

/* 80135AE0-80135B50       .text procHangWallCatch__9daPy_lk_cFv */
BOOL daPy_lk_c::procHangWallCatch() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f && !procHangClimb_init(m_HIO->mWallCatch.m.field_0x30)) {
        return procFall_init(1, m_HIO->mWallCatch.m.field_0x54);
    } else {
        return true;
    }
}
