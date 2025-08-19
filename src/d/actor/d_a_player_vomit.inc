/**
 * d_a_player_vomit.inc
 *
 * Code relating to being launched in the air (like from a Boko Bulb).
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
#include "d/d_procname.h"

/* 8014F8A0-8014F994       .text checkJumpFlower__9daPy_lk_cFv */
BOOL daPy_lk_c::checkJumpFlower() {
    fopAc_ac_c* iVar1;
    short sVar3;

    iVar1 = mCyl.GetCoHitAc();
    if (mCyl.ChkCoHit() && iVar1 != 0 && fopAcM_GetName(iVar1) == PROC_JBO) {
        if (checkModeFlg(ModeFlg_MIDAIR)) {
            if (speed.y <= 0.0f && current.pos.y > iVar1->current.pos.y - 50.0f) {
                return procVomitWait_init();
            }
        } else {
            sVar3 = fopAcM_searchActorAngleY(this, iVar1);
            if (cLib_distanceAngleS(sVar3, shape_angle.y) < 0x2000 && mStickDistance > 0.2f) {
                return procVomitReady_init(sVar3, fopAcM_searchActorDistanceXZ(this, iVar1));
            }
        }
    }
    return false;
}

/* 8014F994-8014FA88       .text procVomitReady_init__9daPy_lk_cFsf */
BOOL daPy_lk_c::procVomitReady_init(s16 param_0, f32 param_1) {
    commonProcInit(daPyProc_VOMIT_READY_e);
    setSingleMoveAnime(
        ANM_MSTEPOVER,
        daPy_HIO_vomit_c0::m.field_0xC,
        daPy_HIO_vomit_c0::m.field_0x10,
        daPy_HIO_vomit_c0::m.field_0x0,
        daPy_HIO_vomit_c0::m.field_0x14
    );
    speed.y = daPy_HIO_vomit_c0::m.field_0x18;
    mVelocity = (param_1 * -gravity) / (2.0f * daPy_HIO_vomit_c0::m.field_0x18);
    if (checkHeavyStateOn()) {
        speed.y *= 1.5f;
        mVelocity *= 1.5f;
    }
    shape_angle.y = param_0;
    current.angle.y = shape_angle.y;
    voiceStart(6);
    return true;
}

/* 8014FA88-8014FB64       .text procVomitReady__9daPy_lk_cFv */
BOOL daPy_lk_c::procVomitReady() {
    setFallVoice();
    if (!checkJumpFlower()) {
        if (mAcch.ChkGroundHit()) {
            changeLandProc(daPy_HIO_autoJump_c0::m.field_0x24);
        } else if (checkFanGlideProc(0)) {
            return true;
        } else if (speed.y < -gravity) {
            setSingleMoveAnime(ANM_JMPEDS, 0.0f, 0.0f, -1, daPy_HIO_wallCatch_c0::m.field_0x54);
            offModeFlg(ModeFlg_00000400);
            setTextureAnime(0x37, 0);
            resetSeAnime();
        }
    }
    return true;
}

/* 8014FB64-8014FC20       .text procVomitWait_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procVomitWait_init() {
    commonProcInit(daPyProc_VOMIT_WAIT_e);
    setSingleMoveAnime(ANM_VOMITJMP, 1.0f, 0.0f, -1, 5.0f);
    fopAc_ac_c* iVar1 = mCyl.GetCoHitAc();
    current.pos = iVar1->current.pos;
    old.pos = current.pos;
    m34C2 = 11;
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    m34D4 = 0;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK80_e);
#if VERSION == VERSION_PAL
    m34D0 = 0;
#endif
    return true;
}

/* 8014FC20-8014FD8C       .text procVomitWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procVomitWait() {
    s16 r30 = 0;

#if VERSION < VERSION_PAL
    if (checkNoResetFlg1(daPyFlg1_FORCE_VOMIT_JUMP)) {
        procVomitJump_init(0);
    }
#else
    if (checkNoResetFlg1(daPyFlg1_FORCE_VOMIT_JUMP) || m34D0) {
        if (!dComIfGp_event_runCheck()) {
            procVomitJump_init(0);
        } else {
            m34D0 = 1;
        }
    }
#endif
    else {
        if (mStickDistance > 0.05f) {
            int direction = getDirectionFromAngle(m34DC);
            if (direction == DIR_LEFT) {
                s16 r5 = 512.0f * mStickDistance;
                if (r5 > m34D4) {
                    s16 r0 = 64.0f * mStickDistance;
                    m34D4 += r0;
                    if (m34D4 > r5) {
                        m34D4 = r5;
                    }
                    r30 = m34D4;
                } else {
                    r30 = r5;
                }
            } else if (direction == DIR_RIGHT) {
                s16 r5 = -512.0f * mStickDistance;
                if (r5 < m34D4) {
                    s16 r0 = 64.0f * mStickDistance;
                    m34D4 -= r0;
                    if (m34D4 < r5) {
                        m34D4 = r5;
                    }
                    r30 = m34D4;
                } else {
                    r30 = r5;
                }
            } else {
                r30 = 0;
            }
        } else {
            r30 = 0;
        }

        cLib_addCalcAngleS(&m34D4, r30, 3, 0x40, 0x10);
        shape_angle.y += m34D4;
        current.angle.y = shape_angle.y;
    }
    return true;
}

/* 8014FD8C-8014FF0C       .text procVomitJump_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procVomitJump_init(int param_0) {
    commonProcInit(daPyProc_VOMIT_JUMP_e);
    m35C4 = 40.0f;
    float fVar1;
    if (param_0 == 2 || param_0 == 3) {
        fVar1 = 3.0f;
    } else {
        fVar1 = -1.0f;
    }
    mProcVar0.m3570 = param_0;
    setSingleMoveAnime(ANM_VOMITJMP, 1.0f, 0.0f, -1, fVar1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK80000000_e);
    mStts.ClrCcMove();
    m34D4 = 0;
    m34D0 = 2;
    m33A8.makeEmitterColor(
        dPa_name::ID_SCENE_8112,
        mpCLModel->getAnmMtx(0x12),
        &current.pos,
        (csXyz*)&shape_angle,
        &tevStr.mColorK0,
        &tevStr.mColorK0
    );
    if (param_0 == 0) {
        dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
    }
    if (param_0 == 1) {
        gravity = 0.0f;
        m34D2 = 0x14;
    } else {
        voiceStart(0);
        if (param_0 == 3) {
            speed.y = 46.0f;
            mProcVar0.m3570 = 1;
        } else {
            speed.y = daPy_HIO_vomit_c0::m.field_0x1C;
        }
        m34D2 = 0;
    }
    return true;
}

/* 8014FF0C-801500E4       .text procVomitJump__9daPy_lk_cFv */
BOOL daPy_lk_c::procVomitJump() {
    if ((s32)m34D2 != 0) {
        m34D2--;
        if (m34D2 == 0) {
            voiceStart(0);
            speed.y = 46.0f;
            gravity = daPy_HIO_autoJump_c0::m.field_0xC;
        }
        mStts.ClrCcMove();
        return true;
    }

    if (m34D0 != 0) {
        mStts.ClrCcMove();
        m34D0--;
    }
    if (!checkJumpFlower()) {
        if (mAcch.ChkGroundHit()) {
            changeLandProc(daPy_HIO_autoJump_c0::m.field_0x24);
        } else {
            s16 sVar1 = shape_angle.x;
            shape_angle.x = sVar1 + daPy_HIO_vomit_c0::m.field_0x2;
            if (sVar1 < 0 && 0 < shape_angle.x) {
                seStartOnlyReverb(JA_SE_LK_JUMP_FLOWER_OUT);
            }
            if (mProcVar0.m3570 == 1) {
                cLib_addCalc(&mVelocity, daPy_HIO_vomit_c0::m.field_0x20, 0.5f, 2.0f, 0.1f);
            } else {
                f32 fVar2;
                if (!checkFanGlideProc(1)) {
                    if (mStickDistance > 0.05f) {
                        int direction = getDirectionFromShapeAngle();
                        if (direction == DIR_FORWARD) {
                            fVar2 = 1.0f;
                        } else if (direction == DIR_BACKWARD) {
                            fVar2 = -1.0f;
                        } else {
                            fVar2 = 0.0f;
                        }
                    } else {
                        fVar2 = 0.0f;
                    }
                    cLib_addCalc(
                        &mVelocity, (daPy_HIO_vomit_c0::m.field_0x20 * mStickDistance * fVar2), 0.5f, 2.0f, 0.1f
                    );
                }
            }
        }
    }
    return true;
}

/* 801500E4-80150164       .text procVomitLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procVomitLand_init() {
    commonProcInit(daPyProc_VOMIT_LAND_e);
    mVelocity = 0.0f;
    setSingleMoveAnime(
        ANM_LANDDAMA,
        daPy_HIO_vomit_c0::m.field_0x24,
        daPy_HIO_vomit_c0::m.field_0x28,
        daPy_HIO_vomit_c0::m.field_0x4,
        daPy_HIO_vomit_c0::m.field_0x2C
    );
    m34D0 = daPy_HIO_vomit_c0::m.field_0x6;
    mProcVar0.m3570 = 0;
    m34BE = 5;
    return true;
}

/* 80150164-8015023C       .text procVomitLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procVomitLand() {
    resetFootEffect();
    if (mProcVar0.m3570 != 0) {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
            checkNextMode(0);
        } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_vomit_c0::m.field_0x3C) {
            checkNextMode(1);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (m34D0 > 0) {
            m34D0--;
        } else {
            setSingleMoveAnime(
                ANM_LANDDAMAST,
                daPy_HIO_vomit_c0::m.field_0x30,
                daPy_HIO_vomit_c0::m.field_0x34,
                daPy_HIO_vomit_c0::m.field_0x8,
                daPy_HIO_vomit_c0::m.field_0x38
            );
            mProcVar0.m3570 = 1;
        }
    }
    return true;
}
