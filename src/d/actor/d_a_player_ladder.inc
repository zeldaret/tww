/**
 * d_a_player_ladder.inc
 *
 * Code relating to getting on, getting off, and climbing ladders.
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

/* 80132F34-80132F58       .text getLadderMoveAnmSpeed__9daPy_lk_cFv */
f32 daPy_lk_c::getLadderMoveAnmSpeed() {
    return getAnmSpeedStickRate(daPy_HIO_ladder_c0::m.field_0x28, daPy_HIO_ladder_c0::m.field_0x24);
}

/* 80132F58-80133058       .text setLadderFootSe__9daPy_lk_cFv */
void daPy_lk_c::setLadderFootSe() {
    cXyz local_28(
        current.pos.x + cM_ssin(shape_angle.y) * 50.0f, current.pos.y, current.pos.z + cM_scos(shape_angle.y) * 50.0f
    );

    mLinkLinChk.Set(&current.pos, &local_28, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        mDoAud_seStart(JA_SE_FT_LADDER_CLIMB_D, &current.pos, dComIfG_Bgsp()->GetMtrlSndId(mLinkLinChk), mReverb);
    } else {
        seStartOnlyReverb(JA_SE_FT_LADDER_CLIMB_D);
    }
}

/* 80133058-80133240       .text changeLadderMoveProc__9daPy_lk_cFi */
int daPy_lk_c::changeLadderMoveProc(int param_0) {
    cXyz local_2c;
    cXyz local_38;
    int direction;

    cLib_addCalc(&current.pos.x, m370C.x, 0.5f, 0.5f, 0.05f);
    cLib_addCalc(&current.pos.y, m370C.y, 0.5f, 0.5f, 0.05f);
    cLib_addCalc(&current.pos.z, m370C.z, 0.5f, 0.5f, 0.05f);
    if (mStickDistance > 0.05f) {
        int iVar2 = abs((s16)(m34E8 - shape_angle.y));
        if (iVar2 > 0x3c72 && iVar2 < 0x438e) {
            return false;
        }
        local_2c.x = current.pos.x;
        local_2c.z = current.pos.z;
        if (iVar2 < 0x4000) {
            local_2c.y = 50.0f + (125.0f + current.pos.y);
            direction = DIR_FORWARD;
        } else {
            local_2c.y = current.pos.y - 50.0f;
            direction = DIR_BACKWARD;
        }
        local_38.x = local_2c.x + cM_ssin(shape_angle.y) * 50.0f;
        local_38.z = local_2c.z + cM_scos(shape_angle.y) * 50.0f;
        local_38.y = local_2c.y;
        mLinkLinChk.Set(&local_2c, &local_38, this);
        if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk) || dComIfG_Bgsp()->GetWallCode(mLinkLinChk) != 4) {
            if (iVar2 < 0x4000) {
                procLadderUpEnd_init(param_0);
            } else {
                procLadderDownEnd_init(param_0);
            }
        } else {
            procLadderMove_init(param_0, direction, &m370C);
        }
    }
    return false;
}

/* 80133240-801333A8       .text setMoveBGLadderCorrect__9daPy_lk_cFv */
int daPy_lk_c::setMoveBGLadderCorrect() {
    if (dComIfG_Bgsp()->ChkPolySafe(mPolyInfo)) {
        if (dComIfG_Bgsp()->ChkMoveBG(mPolyInfo)) {
            dComIfG_Bgsp()->MoveBgTransPos(mPolyInfo, true, &current.pos, &current.angle, &shape_angle);
            dComIfG_Bgsp()->MoveBgTransPos(mPolyInfo, true, &m370C, NULL, NULL);
        }
    }
    cXyz local_18(m370C.x + cM_ssin(current.angle.y) * 50.0f, m370C.y, m370C.z + cM_scos(current.angle.y) * 50.0f);
    mLinkLinChk.Set(&m370C, &local_18, this);
    if ((!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) || (dComIfG_Bgsp()->GetWallCode(mLinkLinChk) != 4)) {
        return procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
    } else {
        mPolyInfo = mLinkLinChk;
        return false;
    }
}

/* 801333A8-80133414       .text procLadderUpStart_init_sub__9daPy_lk_cFv */
void daPy_lk_c::procLadderUpStart_init_sub() {
    setSingleMoveAnime(ANM_LADDERUPST, daPy_HIO_ladder_c0::m.field_0x4, 0.0f, -1, daPy_HIO_ladder_c0::m.field_0x8);
    mProcVar0.m3570 = 1;
    m34C2 = 4;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000000_e);
}

/* 80133414-8013356C       .text procLadderUpStart_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procLadderUpStart_init() {
    commonProcInit(daPyProc_LADDER_UP_START_e);
    gravity = 0.0f;
    speed.y = 0.0f;
    mVelocity = 0.0f;
    speedF = 0.0f;
    if (mEquipItem == daPyItem_NONE_e) {
        if (checkEquipAnime()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        }
        procLadderUpStart_init_sub();
    } else {
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
        setAnimeUnequip();
        mProcVar0.m3570 = 0;
        m3598 = 0.0f;
    }
    f32 fVar1 = cM_ssin(m352C);
    f32 fVar2 = cM_scos(m352C);
    current.pos.x = m3724.x + 25.0f * fVar1;
    current.pos.y = m3724.y;
    current.pos.z = m3724.z + 25.0f * fVar2;
    shape_angle.y = m352C + 0x8000;
    current.angle.y = shape_angle.y;
    m370C.x = (m3724.x + fVar1 * 20.5f) - fVar2;
    m370C.y = m3724.y + 37.5f;
    m370C.z = fVar1 + (m3724.z + fVar2 * 20.5f);
    m34D4 = 0;
    return true;
}

/* 8013356C-80133670       .text procLadderUpStart__9daPy_lk_cFv */
BOOL daPy_lk_c::procLadderUpStart() {
    if (setMoveBGLadderCorrect()) {
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
                changeLadderMoveProc(1);
            }
        } else {
            if (frameCtrl.checkPass(9.0f)) {
                setLadderFootSe();
            }
        }
    }
    return true;
}

/* 80133670-80133710       .text procLadderUpEnd_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procLadderUpEnd_init(int param_0) {
    daPy_ANM dVar2;

    commonProcInit(daPyProc_LADDER_UP_END_e);
    if (param_0 != 0) {
        dVar2 = ANM_LADDERUPEDL;
    } else {
        dVar2 = ANM_LADDERUPEDR;
    }
    setSingleMoveAnime(dVar2, daPy_HIO_ladder_c0::m.field_0xC, 0.0f, -1, daPy_HIO_ladder_c0::m.field_0x10);
    m34C2 = 7;
    gravity = 0.0f;
    speed.y = 0.0f;
    mVelocity = 0.0f;
    speedF = 0.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000000_e);
    return true;
}

/* 80133710-801337B4       .text procLadderUpEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procLadderUpEnd() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    if (setMoveBGLadderCorrect()) {
        return true;
    }

    if (frameCtrl.getRate() < 0.01f) {
        checkNextMode(0);
    } else {
        if (frameCtrl.checkPass(9.0f) || frameCtrl.checkPass(19.0f)) {
            setLadderFootSe();
        }
        m34C2 = 5;
    }
    return true;
}

/* 801337B4-8013384C       .text procLadderDownStart_init_sub__9daPy_lk_cFv */
void daPy_lk_c::procLadderDownStart_init_sub() {
    setSingleMoveAnime(ANM_LADDERDWST, daPy_HIO_ladder_c0::m.field_0x14, 0.0f, -1, daPy_HIO_ladder_c0::m.field_0x18);
    mProcVar0.m3570 = 1;
    m34C2 = 4;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000000_e);
    setOldRootQuaternion(0, -0x8000, 0);
    shape_angle.y += 0x8000;
    current.angle.y = shape_angle.y;
}

/* 8013384C-8013399C       .text procLadderDownStart_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procLadderDownStart_init() {
    commonProcInit(daPyProc_LADDER_DOWN_START_e);
    gravity = 0.0f;
    speed.y = 0.0f;
    mVelocity = 0.0f;
    speedF = 0.0f;
    shape_angle.y = m352C + 0x8000;
    current.angle.y = m352C;
    if (mEquipItem == daPyItem_NONE_e) {
        if (checkEquipAnime()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        }
        procLadderDownStart_init_sub();
    } else {
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
        setAnimeUnequip();
        mProcVar0.m3570 = 0;
        m3598 = 0.0f;
    }
    f32 fVar1 = cM_ssin(m352C);
    f32 fVar2 = cM_scos(m352C);
    current.pos.x = m3724.x + 25.0f * fVar1;
    current.pos.y = m3724.y;
    current.pos.z = m3724.z + 25.0f * fVar2;
    m370C.x = fVar2 + (m3724.x - fVar1 * 30.5f);
    m370C.y = m3724.y - 112.5f;
    m370C.z = (m3724.z - fVar2 * 30.5f) - fVar1;
    return true;
}

/* 8013399C-80133AB8       .text procLadderDownStart__9daPy_lk_cFv */
BOOL daPy_lk_c::procLadderDownStart() {
    if (setMoveBGLadderCorrect()) {
        return true;
    }

    if (mProcVar0.m3570 == 0) {
        if (checkNoUpperAnime()) {
            procLadderDownStart_init_sub();
        }
    } else {
        J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
        m34C2 = 5;
        if (frameCtrl.getRate() < 0.01f) {
            dComIfGp_setDoStatus(dActStts_LET_GO_e);
            if (doTrigger()) {
                m34C2 = 0;
                procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
            } else {
                changeLadderMoveProc(1);
            }
        } else {
            if (frameCtrl.checkPass(26.0f) || frameCtrl.checkPass(36.0f) || frameCtrl.checkPass(43.0f)) {
                setLadderFootSe();
            }
        }
    }
    return true;
}

/* 80133AB8-80133B4C       .text procLadderDownEnd_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procLadderDownEnd_init(int param_0) {
    commonProcInit(daPyProc_LADDER_DOWN_END_e);
    daPy_ANM anm;
    if (param_0 != 0) {
        anm = ANM_LADDERDWEDL;
    } else {
        anm = ANM_LADDERDWEDR;
    }
    setSingleMoveAnime(anm, daPy_HIO_ladder_c0::m.field_0x1C, 0.0f, -1, daPy_HIO_ladder_c0::m.field_0x20);
    m34C2 = 7;
    gravity = 0.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000000_e);
    return true;
}

/* 80133B4C-80133BB4       .text procLadderDownEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procLadderDownEnd() {
    if (setMoveBGLadderCorrect()) {
        return true;
    }

    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        checkNextMode(0);
    } else {
        m34C2 = 5;
    }
    return true;
}

/* 80133BB4-80133E28       .text procLadderMove_init__9daPy_lk_cFiiP4cXyz */
BOOL daPy_lk_c::procLadderMove_init(int param_0, int direction, cXyz* param_2) {
    int uVar3 = checkModeFlg(ModeFlg_MIDAIR) ? true : false;
    float dVar4 = getLadderMoveAnmSpeed();

    commonProcInit(daPyProc_LADDER_MOVE_e);
    if (uVar3 == 0) {
        if (direction == DIR_FORWARD) {
            m370C.y = param_2->y + 37.5f;
        } else {
            dVar4 *= -1.0f;
            m370C.y = param_2->y - 37.5f;
        }
    } else {
        m370C.y = param_2->y;
    }
    m370C.x = param_2->x;
    m370C.z = param_2->z;

    daPy_ANM anm;
    if (param_0 != 0) {
        if (uVar3 != 0) {
            mProcVar0.m3570 = 1;
        } else {
            mProcVar0.m3570 = 0;
            m370C.x = m370C.x - 2.0f * cM_scos(shape_angle.y);
            m370C.z = m370C.z - -2.0f * cM_ssin(shape_angle.y);
        }
        if (dVar4 >= 0.0f) {
            anm = ANM_LADDERLTOR;
        } else {
            anm = ANM_LADDERRTOL;
        }
    } else {
        mProcVar0.m3570 = 1;
        if (dVar4 >= 0.0f) {
            anm = ANM_LADDERRTOL;
        } else {
            anm = ANM_LADDERLTOR;
        }
        m370C.x = m370C.x + 2.0f * cM_scos(shape_angle.y);
        m370C.z = m370C.z + -2.0f * cM_ssin(shape_angle.y);
    }

    setSingleMoveAnime(anm, dVar4, 0.0f, -1, daPy_HIO_ladder_c0::m.field_0x2C);
    mDirection = direction;
    if (direction == DIR_FORWARD) {
        setTextureAnime(10, 0);
    } else {
        setTextureAnime(0xb, 0);
    }
    m34C2 = 7;
    gravity = 0.0f;
    speed.y = 0.0f;
    mVelocity = 0.0f;
    speedF = 0.0f;
    m34D0 = 1;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000000_e);
    return true;
}

/* 80133E28-80133F1C       .text procLadderMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procLadderMove() {
    if (setMoveBGLadderCorrect()) {
        return true;
    }
    m34C2 = 5;
    dComIfGp_setDoStatus(dActStts_LET_GO_e);

    if (doTrigger()) {
        m34C2 = 0;
        procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
    } else if (std::fabsf(mFrameCtrlUnder[UNDER_MOVE0_e].getRate()) < 0.01f) {
        if (m34D0 > 0) {
            m34D0--;
            setLadderFootSe();
        } else {
            changeLadderMoveProc(mProcVar0.m3570);
        }
    } else {
        f32 dVar2 = getLadderMoveAnmSpeed();
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.0f) {
            dVar2 *= -1.0f;
        }
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(dVar2);
    }

    return true;
}
