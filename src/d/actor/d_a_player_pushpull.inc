/**
 * d_a_player_pushpull.inc
 *
 * Code relating to pushing and pulling other actors.
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

/* 801514B0-80151644       .text setPushPullKeepData__9daPy_lk_cFQ24dBgW13PushPullLabel */
BOOL daPy_lk_c::setPushPullKeepData(dBgW::PushPullLabel pp_label) {
    if (pp_label != dBgW::PPLABEL_NONE) {
        if (dComIfGs_getSelectEquip(2) == dItem_POWER_BRACELETS_e) {
            cLib_onBit<dBgW::PushPullLabel>(pp_label, dBgW::PPLABEL_HEAVY);
        }
        if (mProcVar0.m3570) {
            cLib_onBit<dBgW::PushPullLabel>(pp_label, dBgW::PPLABEL_UNK4);
        }
    }

    fopAc_ac_c* pp_actor = dComIfG_Bgsp()->PushPullCallBack(mPolyInfo, this, shape_angle.y, pp_label);
    if (pp_actor == NULL) {
        return FALSE;
    }

    if (pp_label != dBgW::PPLABEL_NONE) {
        if (pp_actor->shape_angle.y != m34D4) {
            cXyz local_28 = current.pos - m370C;
            mDoMtx_stack_c::transS(m370C);
            mDoMtx_stack_c::YrotM(pp_actor->shape_angle.y - m34D4);
            mDoMtx_stack_c::multVec(&local_28, &current.pos);
            s16 var_r28 = pp_actor->shape_angle.y - m34D4;
            shape_angle.y += var_r28;
            current.angle.y += var_r28;
        }
        current.pos.x += pp_actor->current.pos.x - m370C.x;
        current.pos.z += pp_actor->current.pos.z - m370C.z;
    }
    m370C = pp_actor->current.pos;
    m34D4 = pp_actor->shape_angle.y;
    return TRUE;
}

/* 80151644-801517C0       .text procPushPullWait_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procPushPullWait_init(int param_0) {
    commonProcInit(daPyProc_PUSH_PULL_WAIT_e);
    mProcVar0.m3570 = param_0;
    mVelocity = 0.0f;
    if (param_0 == 0 || mEquipItem == daPyItem_NONE_e) {
        if (checkEquipAnime()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
        }
        daPy_matAnm_c::offMabaFlg();
        setSingleMoveAnime(
            ANM_WAITPUSHPULL, daPy_HIO_pushpull_c0::m.field_0x0, 0.0f, -1, daPy_HIO_pushpull_c0::m.field_0x4
        );
        m34D6 = 0;
    } else {
        setBlendMoveAnime(daPy_HIO_basic_c0::m.field_0xC);
        setAnimeUnequip();
        m3598 = 0.0f;
        m34D6 = 1;
    }
    if (param_0 != 0) {
        m34D4 = m352C + 0x8000;
        m370C.x = m3724.x + 40.0f * cM_ssin(m352C);
        m370C.y = current.pos.y;
        m370C.z = m3724.z + 40.0f * cM_scos(m352C);
    }
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK4000000_e);
    return true;
}

/* 801517C0-8015198C       .text procPushPullWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procPushPullWait() {
    dComIfGp_setRStatus(dActStts_GRAB_e);
    setFrontWallType();
    if (m34D6 != 0) {
        if (checkNoUpperAnime()) {
            setSingleMoveAnime(
                ANM_WAITPUSHPULL, daPy_HIO_pushpull_c0::m.field_0x0, 0.0f, -1, daPy_HIO_pushpull_c0::m.field_0x4
            );
            m34D6 = 0;
        }
    } else if (spActionButton() && checkResetFlg0(daPyRFlg0_UNK8)) {
        if (mProcVar0.m3570 != 0) {
            s16 sVar1 = cLib_addCalcAngleS(&shape_angle.y, m34D4, 3, 0x800, 0x100);
            current.angle.y = shape_angle.y;
            f32 dVar2 = cLib_addCalc(&current.pos.x, m370C.x, 0.5f, 10.0f, 1.0f);
            dVar2 += cLib_addCalc(&current.pos.z, m370C.z, 0.5f, 10.0f, 1.0f);
            if (sVar1 == 0 && dVar2 < 5.0f && checkNoUpperAnime()) {
                current.pos.x = m370C.x;
                current.pos.z = m370C.z;
                mProcVar0.m3570 = 0;
            }
        }
        if (mProcVar0.m3570 == 0) {
            if (mStickDistance > 0.05f) {
                int direction = getDirectionFromShapeAngle();
                if (direction == DIR_FORWARD) {
                    procPushMove_init();
                } else if (direction == DIR_BACKWARD) {
                    procPullMove_init();
                }
            } else {
                setTextureAnime(mAnmDataTable[ANM_WAITPUSHPULL].mTexAnmIdx, 0);
            }
        }
    } else {
        checkNextMode(0);
    }
    return true;
}

/* 8015198C-80151A1C       .text procPushMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procPushMove_init() {
    if (!setPushPullKeepData(dBgW::PPLABEL_NONE)) {
        return false;
    }

    commonProcInit(daPyProc_PUSH_MOVE_e);
    setSingleMoveAnime(ANM_WALKPUSH, daPy_HIO_pushpull_c0::m.field_0x8, 0.0f, -1, daPy_HIO_pushpull_c0::m.field_0xC);
    mProcVar0.m3570 = 1;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK4000000_e);

    return true;
}

/* 80151A1C-80151B38       .text procPushMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procPushMove() {
    dComIfGp_setRStatus(dActStts_GRAB_e);
    int direction = getDirectionFromShapeAngle();
    setFrontWallType();
    if (!checkResetFlg0(daPyRFlg0_UNK8) || (!spActionButton() && !checkNoResetFlg0(daPyFlg0_PUSH_PULL_KEEP))) {
        checkNextMode(0);
    } else {
        if (!checkNoResetFlg0(daPyFlg0_PUSH_PULL_KEEP)) {
            if (mStickDistance > 0.05f) {
                if (direction == DIR_FORWARD) {
                    setPushPullKeepData(dBgW::PPLABEL_PUSH);
                    return true;
                }
                if (direction == DIR_BACKWARD) {
                    return procPullMove_init();
                }
            }
            return procPushPullWait_init(0);
        }
        if (mProcVar0.m3570 != 0) {
            voiceStart(19);
        }
        mProcVar0.m3570 = 0;
        setPushPullKeepData(dBgW::PPLABEL_PUSH);
    }
    return true;
}

/* 80151B38-80151BC8       .text procPullMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procPullMove_init() {
    if (!setPushPullKeepData(dBgW::PPLABEL_NONE)) {
        return false;
    }

    commonProcInit(daPyProc_PULL_MOVE_e);
    setSingleMoveAnime(ANM_WALKPULL, daPy_HIO_pushpull_c0::m.field_0x10, 0.0f, -1, daPy_HIO_pushpull_c0::m.field_0x14);
    mProcVar0.m3570 = 1;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK4000000_e);

    return true;
}

/* 80151BC8-80151E40       .text procPullMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procPullMove() {
    dComIfGp_setRStatus(dActStts_GRAB_e);
    int direction = getDirectionFromShapeAngle();
    setFrontWallType();
    if (!checkResetFlg0(daPyRFlg0_UNK8) || (!spActionButton() && !checkNoResetFlg0(daPyFlg0_PUSH_PULL_KEEP))) {
        checkNextMode(0);
    } else {
        if (!checkNoResetFlg0(daPyFlg0_PUSH_PULL_KEEP)) {
            if (mStickDistance > 0.05f) {
                if (direction == DIR_BACKWARD) {
                    f32 dVar4 = cM_ssin(shape_angle.y);
                    f32 dVar5 = cM_scos(shape_angle.y);
                    cXyz local_3c;
                    cXyz local_48;
                    local_3c.x = current.pos.x;
                    local_3c.y = current.pos.y + 30.1f;
                    local_3c.z = current.pos.z;
                    local_48.x = local_3c.x - (dVar4 * 105.0f);
                    local_48.y = local_3c.y;
                    local_48.z = local_3c.z - (dVar5 * 105.0f);
                    mLinkLinChk.Set(&local_3c, &local_48, this);
                    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                        return true;
                    }
                    local_3c.y = current.pos.y + 89.9f;
                    local_48.y = local_3c.y;
                    mLinkLinChk.Set(&local_3c, &local_48, this);
                    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                        return true;
                    }
                    local_48.x += (dVar4 * 29.0f);
                    local_48.z += (dVar5 * 29.0f);
                    mGndChk.SetPos(&local_48);
                    dVar4 = dComIfG_Bgsp()->GroundCross(&mGndChk);
                    if (!((dVar4 - current.pos.y) < -30.1f)) {
                        setPushPullKeepData(dBgW::PPLABEL_PULL);
                    }
                    return true;
                }
                if (direction == DIR_FORWARD) {
                    return procPushMove_init();
                }
            }
            return procPushPullWait_init(0);
        }
        if (mProcVar0.m3570 == 1) {
            voiceStart(19);
        }
        mProcVar0.m3570 = 0;
        setPushPullKeepData(dBgW::PPLABEL_PULL);
    }
    return true;
}
