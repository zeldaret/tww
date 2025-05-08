/**
 * d_a_player_rope.inc
 *
 * Code relating to the Grappling Hook item.
 *
 * This file is not a standalone translation unit and is instead directly
 * included into d_a_player_main.cpp.
 *
 * The original name of this file is not known, but a best guess was taken
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_himo2.h"
#include "d/d_attention.h"
#include "d/d_procname.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_audio.h"

/* 80142D08-80142D68       .text checkRopeAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkRopeAnime() const {
    return (checkRopeReadyAnime()) || (checkUpperAnime(LKANM_BCK_ROPETHROW));
}

/* 80142D68-80142E0C       .text freeRopeItem__9daPy_lk_cFv */
void daPy_lk_c::freeRopeItem() {
    if (mEquipItem == dItem_GRAPPLING_HOOK_e) {
        fopAc_ac_c* rope = mActorKeepRope.getActor();
        if (mActorKeepEquip.getActor() != NULL) {
            onResetFlg0(daPyRFlg0_UNK40000000);
        }
        if (rope != NULL) {
            if (fopAcM_GetName(rope) == PROC_HIMO2) {
                fopAcM_SetParam(rope, 4);
                mActorKeepRope.clearData();
                onResetFlg0(daPyRFlg0_UNK40000000);
            } else if (fopAcM_GetName(rope) == PROC_HIMO3) {
                mEquipItem = daPyItem_NONE_e;
                fopAcM_SetParam(rope, 3);
                mActorKeepRope.clearData();
            }
        }
    }
}

/* 80142E0C-80142E98       .text checkRopeRoofHit__9daPy_lk_cFs */
f32 daPy_lk_c::checkRopeRoofHit(s16 param_0) {
    cXyz local_c;

    local_c.set(current.pos.x - 15.0f * cM_ssin(param_0), current.pos.y, current.pos.z - 15.0f * cM_scos(param_0));
    mRoofChk.SetPos(local_c);
    return dComIfG_Bgsp()->RoofChk(&mRoofChk);
}

/* 80142E98-80142FC8       .text changeRopeSwingProc__9daPy_lk_cFv */
int daPy_lk_c::changeRopeSwingProc() {
    if (mCyl.ChkCoHit() != 0) {
        fopAc_ac_c* pfVar2 = mCyl.GetCoHitAc();
        if ((pfVar2 != NULL) && (fopAcM_GetName(pfVar2) == PROC_HIMO3)) {
            cXyz local_24 = pfVar2->current.pos - current.pos;
            if ((local_24.abs() - 95.0f >= 100.0f) && (pfVar2->current.pos.y > current.pos.y)) {
                return procRopeSwing_init(pfVar2, 0x1800);
            }
        }
    }
    return false;
}

/* 80142FC8-801430D4       .text changeRopeEndProc__9daPy_lk_cFi */
int daPy_lk_c::changeRopeEndProc(int param_0) {
    dComIfGp_setDoStatus(dActStts_LET_GO_ROPE_e);
    if (doTrigger() || cancelTrigger() || (!checkRopeTag() && itemTrigger())) {
        freeRopeItem();
        voiceStart(6);
        if ((cancelTrigger()) && (!checkBossGomaStage())) {
            setAnimeEquipSword(0);
        }
        if (param_0 != 0) {
            procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
        }
        onNoResetFlg0(daPyFlg0_UNK400000);
        onNoResetFlg1(daPyFlg1_UNK8000000);
        return true;
    }
    return false;
}

/* 801430D4-80143138       .text checkSpecialRope__9daPy_lk_cFv */
BOOL daPy_lk_c::checkSpecialRope() {
    if ((!strcmp(dComIfGp_getStartStageName(), "GanonK")) && (mActorKeepEquip.getActor() == NULL)) {
        return true;
    } else {
        return false;
    }
}

/* 80143138-8014327C       .text changeRopeToHangProc__9daPy_lk_cFv */
int daPy_lk_c::changeRopeToHangProc() {
    if (mProcVar0.m3570 == 0) {
        return false;
    }
    f32 fVar1 = cM_ssin(shape_angle.y);
    f32 fVar2 = cM_scos(shape_angle.y);
    cXyz local_1c;
    cXyz local_28;
    local_1c.set(mRopePos.x - 20.0f * fVar1, mRopePos.y, mRopePos.z - 20.0f * fVar2);
    local_28.set(local_1c.x + 50.0f * fVar1, local_1c.y, local_1c.z + 50.0f * fVar2);
    mLinkLinChk.Set(&local_1c, &local_28, this);
    if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        return false;
    }
    cM3dGPla* pfVar4 = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
    s16 iVar5 = cM_atan2s(pfVar4->GetNP()->x, pfVar4->GetNP()->z);
    if (cLib_distanceAngleS(iVar5, shape_angle.y + 0x8000) > 0x2000) {
        return false;
    } else {
        m352C = iVar5;
        procRopeUpHang_init();
        return true;
    }
}

/* 8014327C-80143694       .text checkRopeSwingWall__9daPy_lk_cFP4cXyzP4cXyzPsPf */
BOOL daPy_lk_c::checkRopeSwingWall(cXyz*, cXyz*, s16*, f32*) {
    /* Nonmatching */
    static JGeometry::TVec3<f32> dynamic_scale;
    static JGeometry::TVec3<f32> particle_scale;
}

/* 80143694-80143A44       .text setBlendRopeMoveAnime__9daPy_lk_cFi */
void daPy_lk_c::setBlendRopeMoveAnime(int param_0) {
    daPy_ANM anm;
    f32 dVar6;
    f32 f30;
    f32 f2;
    f32 sp08;

    f30 = m35A4 * m35A8;
    f2 = std::fabsf(f30);
    if (checkModeFlg(ModeFlg_00000400)) {
        sp08 = 0.0f;
        anm = ANM_ROPESWINGB;
    } else {
        sp08 = m_pbCalc[PART_UNDER_e]->getRatio(1);
        if (m34D0 != 0) {
            if (m34D0 == -1) {
                anm = ANM_ROPESWINGF;
            } else {
                anm = ANM_ROPESWINGB;
            }
            dVar6 = 1.0f;
            cLib_chaseF(&sp08, dVar6, 0.05f);
            if (((m34D0 == -1) && (M_PI / 2 < f30)) || (m34D0 == 1 && (-M_PI / 2 < f30))) {
                m34D0 = 0;
            }
        } else if (((param_0 != 0) || (mStickDistance <= 0.05f)) || (spActionButton())) {
            if (f2 <= M_PI / 2) {
                anm = ANM_ROPESWINGB;
            } else {
                anm = ANM_ROPESWINGF;
            }
            dVar6 = (0.6f * m34D4) / daPy_HIO_rope_c0::m.field_0x0;
            if (checkSpecialRope()) {
                dVar6 *= 8.0f;
            }
            if (dVar6 > 0.6f) {
                dVar6 = 0.6f;
            }
        } else {
            if ((M_PI / 2 > f30) && (M_PI / 10 <= f30)) {
                setMoveAnime(0.0f, daPy_HIO_rope_c0::m.field_0x18, 1.0f, ANM_ROPECATCH, ANM_ROPESWINGF, 7, 7.0f);
                m34D0 = -1;
                return;
            }
            if ((-M_PI / 2 > f30) && (-2.8274333f <= f30)) {
                setMoveAnime(0.0f, daPy_HIO_rope_c0::m.field_0x18, 1.0f, ANM_ROPECATCH, ANM_ROPESWINGB, 7, 7.0f);
                m34D0 = 1;
                return;
            }
            if (f2 <= M_PI / 2) {
                anm = ANM_ROPESWINGB;
            } else {
                anm = ANM_ROPESWINGF;
            }
            dVar6 = (0.6f * m34D4) / daPy_HIO_rope_c0::m.field_0x0;
            if (checkSpecialRope()) {
                dVar6 *= 8.0f;
            }
            if (dVar6 > 0.6f) {
                dVar6 = 0.6f;
            }
        }
        u16 anm_bck = getAnmData(anm)->mUnderBckIdx;
        if (anm_bck != m_anm_heap_under[UNDER_MOVE1_e].mIdx) {
            cLib_addCalc(&sp08, -dVar6, 0.5f, 0.05f, 0.005f);
            if (sp08 <= 0.0f) {
                sp08 = 0.0f;
            } else {
                if (anm == ANM_ROPESWINGB) {
                    anm = ANM_ROPESWINGF;
                } else {
                    anm = ANM_ROPESWINGB;
                }
            }
        } else {
            if (m34D0 == 0) {
                cLib_addCalc(&sp08, dVar6, 0.5f, 0.05f, 0.005f);
            }
        }
    }
    f32 f4;
    if (param_0 != 0) {
        f4 = daPy_HIO_rope_c0::m.field_0x20;
    } else {
        f4 = -1.0f;
    }
    setMoveAnime(sp08, daPy_HIO_rope_c0::m.field_0x18, 1.0f, ANM_ROPECATCH, anm, 7, f4);
}

/* 80143A44-80143C5C       .text throwRope__9daPy_lk_cFv */
int daPy_lk_c::throwRope() {
    himo2_class* rope = (himo2_class*)mActorKeepEquip.getActor();
    setActAnimeUpper(
        LKANM_BCK_ROPETHROW,
        UPPER_MOVE2_e,
        daPy_HIO_rope_c0::m.field_0x44,
        daPy_HIO_rope_c0::m.field_0x48,
        daPy_HIO_rope_c0::m.field_0x8,
        -1.0f
    );
    setPriTextureAnime(0x48, 0);
    mVelocity = 0.0f;
    if (mDirection != DIR_RIGHT) {
        mDirection = DIR_RIGHT;
    }
    current.angle.y = shape_angle.y + -0x4000;
    onModeFlg(ModeFlg_00000001);
    setBlendAtnMoveAnime(daPy_HIO_rope_c0::m.field_0x4C);
    cXyz local_1c;
    if (mCurProc == daPyProc_ROPE_MOVE_e) {
        fopAc_ac_c* pfVar4 = mpAttnActorLockOn;
        if (pfVar4 != NULL) {
            local_1c = pfVar4->eyePos;
        } else {
            f32 fVar3 = 500.0f * cM_scos(mBodyAngle.x);
            local_1c.set(
                current.pos.x + fVar3 * cM_ssin(shape_angle.y),
                (100.0f + current.pos.y) - 500.0f * cM_ssin(mBodyAngle.x),
                current.pos.z + fVar3 * cM_scos(shape_angle.y)
            );
        }
        cXyz local_28;
        local_28.set(current.pos.x, current.pos.y + 100.0f, current.pos.z);
        mRopeLinChk.Set(&local_28, &local_1c, this);
        if (dComIfG_Bgsp()->LineCross(&mRopeLinChk)) {
            local_1c = *mRopeLinChk.GetCrossP();
        }
    } else {
        checkSightLine(2200.0f, &local_1c);
    }
    rope->setTargetPos(&local_1c, &m3600, &m3604);
    fopAcM_SetParam(rope, 1);
    seStartOnlyReverb(JA_SE_LK_ROPE_LAUNCH);
    mSightPacket.offDrawFlg();
    resetFootEffect();
    return true;
}

/* 80143C5C-80143DF4       .text checkNextActionRopeReady__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionRopeReady() {
    himo2_class* rope = (himo2_class*)mActorKeepEquip.getActor();
    u32 uVar2 = fopAcM_GetParam(rope);
    if (uVar2 == 2) {
        return procRopeReady_init();
    }
    if (uVar2 == 0) {
        if (checkUpperAnime(LKANM_BCK_ROPETHROW)) {
            if (mFrameCtrlUpper[UPPER_MOVE2_e].getRate() < 0.01f) {
                return procRopeThrowCatch_init();
            } else {
                return true;
            }
        } else if (!mpAttention->Lockon()) {
            dComIfGp_setDoStatus(dActStts_RETURN_e);
        }
        if (((itemButton()) && (mEquipItem == getReadyItem())) && (m355C == 0)) {
            m355E = 1;
        } else {
            if ((!itemButton()) && (m355E != 0)) {
                m355E = 0;
                if (throwRope()) {
                    return true;
                }
            }
        }
        if (cancelItemUpperReadyAnime()) {
            return true;
        }
    } else if (((rope->field_0x2DC == 5) || (rope->field_0x2DC == 8)) || (rope->field_0x2DC == 9)) {
        return procRopeThrowCatch_init();
    } else {
        checkNextRopeMode();
        return true;
    }
    if (0 < m355C) {
        m355C--;
    }
    return false;
}

/* 80143DF4-80143EAC       .text checkNextRopeMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextRopeMode() {
    if ((!checkRopeReadyAnime()) && (!fopAcM_GetParam(mActorKeepEquip.getActor()))) {
        m355C = 10;
        m355E = 0;
        seStartOnlyReverb(JA_SE_LK_ITEM_TAKEOUT);
    }
    if (mpAttention->Lockon()) {
        return procRopeMove_init();
    } else {
        return procRopeSubject_init();
    }
}

/* 80143EAC-80143F3C       .text checkHangRopeActorNull__9daPy_lk_cFv */
BOOL daPy_lk_c::checkHangRopeActorNull() {
    if (mActorKeepRope.getActor() == NULL) {
        if (checkRopeTag()) {
            mEquipItem = daPyItem_NONE_e;
        }
        procFall_init(1, daPy_HIO_wallCatch_c0::m.field_0x54);
        onNoResetFlg0(daPyFlg0_UNK400000);
        onNoResetFlg1(daPyFlg1_UNK8000000);
        return true;
    } else {
        return false;
    }
}

/* 80143F3C-80144038       .text procRopeSubject_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeSubject_init() {
    if (mCurProc == daPyProc_ROPE_SUBJECT_e) {
        return false;
    }

    commonProcInit(daPyProc_ROPE_SUBJECT_e);

    mVelocity = 0.0f;

    if (fopAcM_GetParam(mActorKeepEquip.getActor()) == 0) {
        setActAnimeUpper(LKANM_BCK_ROPETHROWWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
        setSingleMoveAnime(ANM_ATNRS, 0.0f, 0.0f, -1, daPy_HIO_rope_c0::m.field_0x54);
    }

    dComIfGp_setPlayerStatus0(0, daPyStts0_ROPE_AIM_e);

    current.angle.y = shape_angle.y;

    mDoAud_seStart(JA_SE_CAMERA_L_MOVE);

    mProcVar0.m3570 = 0;
    m3600 = -1.0f;
    m3604 = -1.0f;

    return true;
}

/* 80144038-8014422C       .text procRopeSubject__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeSubject() {
    if (!checkItemModeActorPointer()) {
        return true;
    }

    himo2_class* grapple = (himo2_class*)mActorKeepEquip.getActor();
    if (fopAcM_GetParam(grapple) == 0) {
        dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK40000_e);
    } else {
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK40000_e);
    }

    if (mpAttention->Lockon()) {
        setSpeedAndAngleAtn();
    }

    if (checkNextMode(0) == 0 && setBodyAngleToCamera()) {
        if (mBodyAngle.x > 0) {
            mBodyAngle.x = 0;
        }

        cXyz sight;
        checkSightLine(2200.0f, &sight);
        mSightPacket.onDrawFlg();
        mSightPacket.setPos(&sight);

        if (grapple->setTargetPos(&sight, &m3600, &m3604)) {
            mSightPacket.onDrawFlg();
            if (mSightPacket.getLockFlg()) {
                mSightPacket.incFrame();

                if (mSightPacket.checkSEFrame()) {
                    mDoAud_seStart(JA_SE_INDICATOR_1);
                }
            } else {
                mSightPacket.onLockFlg();
                mDoAud_seStart(JA_SE_INDICATOR_1);
            }
        } else {
            mSightPacket.offLockFlg();
        }
    }

    return true;
}

/* 8014422C-80144464       .text procRopeReady_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeReady_init() {
    fopAc_ac_c* rope = mActorKeepEquip.getActor();
    commonProcInit(daPyProc_ROPE_READY_e);
    setMoveAnime(
        0.5f, daPy_HIO_rope_c0::m.field_0x18, 1.0f, ANM_ROPECATCH, ANM_ROPESWINGB, 7, daPy_HIO_rope_c0::m.field_0x20
    );
    mFrameCtrlUnder[UNDER_MOVE0_e].setStart(daPy_HIO_rope_c0::m.field_0x1C);
    mFrameCtrlUnder[UNDER_MOVE0_e].setEnd(daPy_HIO_rope_c0::m.field_0x4);
    mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform()->setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
    m3688 = current.pos;
    m35F0 = m3688.y;
    m35F4 = m3688.y;
    current.pos.y += 95.0f;
    m370C.x = rope->current.pos.x;
    if (m3600 >= 0.0f) {
        m370C.y = rope->current.pos.y - m3600;
    } else {
        if ((checkBossGomaStage()) && (rope->current.pos.y - current.pos.y > 700.0f)) {
            m370C.y = rope->current.pos.y - 700.0f;
        } else {
            mGndChk.SetPos(&rope->current.pos);
            f32 dVar4 = dComIfG_Bgsp()->GroundCross(&mGndChk);
            if (dVar4 > ((current.pos.y - 125.0f) - 50.0f)) {
                m370C.y = 50.0f + (125.0f + dVar4);
            } else {
                m370C.y = current.pos.y;
            }
        }
    }
    m3600 = m370C.y;
    m370C.z = rope->current.pos.z;
    gravity = 0.0f;
    mVelocity = 0.0f;
    m35A0 = 0.0f;
    fopAcM_SetParam(rope, 3);
    m34D4 = 0x1800;
    shape_angle.y = cM_atan2s((m370C.x - current.pos.x), (m370C.z - current.pos.z));
    current.angle.y = shape_angle.y;
    mRopePos = rope->current.pos;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK800000_e);
    return true;
}

/* 80144464-80144620       .text procRopeReady__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeReady() {
    if (!checkItemModeActorPointer()) {
        return true;
    }
    mRopePos = mActorKeepEquip.getActor()->current.pos;
    m370C.x = mRopePos.x;
    m370C.z = mRopePos.z;
    cXyz local_48 = m370C - current.pos;
    f32 dVar5 = local_48.abs();
    cLib_chaseF(&m35A0, 50.0f, 5.0f);
    shape_angle.x = (0.025f * (m34D4 * m35A0));
    if (dVar5 > m35A0) {
        current.pos += local_48 * (m35A0 / dVar5);
    }
    if (dVar5 <= (2.0f * m35A0)) {
        procRopeSwing_init(mActorKeepEquip.getActor(), shape_angle.x);
    }
    return true;
}

/* 80144620-80144C58       .text procRopeSwing_init__9daPy_lk_cFP10fopAc_ac_cs */
BOOL daPy_lk_c::procRopeSwing_init(fopAc_ac_c* param_0, s16 param_1) {
    float dVar8;
    float dVar9;
    cXyz local_84;
    cXyz local_78;

    himo2_class* pfVar7 = (himo2_class*)param_0;
    commonProcInit(daPyProc_ROPE_SWING_e);
    if (param_0 != NULL) {
        mActorKeepRope.setData(param_0);
        if (fopAcM_GetName(param_0) == PROC_HIMO3) {
            fopAcM_SetParam(param_0, 1);
            deleteEquipItem(TRUE);
            mEquipItem = dItem_GRAPPLING_HOOK_e;
            local_84 = param_0->current.pos - current.pos;
            dVar8 = (local_84.abs() - 95.0f);
            dVar9 = ((himo2_class*)param_0)->field_0x15F8.y;
            if (dVar8 > dVar9) {
                dVar8 = dVar9;
            }
            local_84.normalize();
            current.pos = (param_0->current.pos - (local_84 * dVar8));
        }
    } else {
        param_0 = mActorKeepRope.getActor();
    }
    local_84 = param_0->current.pos - current.pos;
    m35A0 = local_84.abs();
    f32 dVar11 = std::sqrtf(2.0f / m35A0);
    m35A4 = dVar11;
    dVar11 = M_PI / 2 / m35A4;
    if (pfVar7 != NULL) {
        m34D4 = daPy_HIO_rope_c0::m.field_0x0;
        if (checkSpecialRope()) {
            m34D4 *= 0.125f;
        }
        f32 fVar1 = cM_ssin(shape_angle.y);
        f32 fVar2 = cM_scos(shape_angle.y);
        local_78.x = fVar2 * local_84.x - fVar1 * local_84.z;
        local_78.y = local_84.y;
        local_78.z = fVar1 * local_84.x + fVar2 * local_84.z;
        s16 sVar4 = cM_atan2s(-local_78.z, local_78.y);
        if (sVar4 > m34D4) {
            sVar4 = m34D4;
        } else if (sVar4 < -m34D4) {
            sVar4 = -m34D4;
        }

        dVar8 = ((f32)sVar4 / m34D4);
        dVar9 = std::sqrtf(1.0f - (dVar8 * dVar8));
        dVar8 = cM_atan2f(dVar8, dVar9);
        m35A8 = dVar8 / m35A4;
        dVar8 = std::sqrtf(local_78.y * local_78.y + local_78.z * local_78.z);
        m34D6 = cM_atan2s(-local_78.x, dVar8);
        if (m34D6 > 0) {
            m35AC = dVar11;
        } else {
            m35AC = -dVar11;
        }
    } else {
        m34D4 = abs(param_1);
        if (param_1 < 0) {
            m35A8 = dVar11;
        } else {
            m35A8 = -dVar11;
        }
        m34D6 = 0;
        m35AC = 0.0f;
    }
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    speed.y = 0.0f;
    gravity = 0.0f;
    mRopePos = param_0->current.pos;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK800000_e);
    if ((pfVar7 == NULL) || (mActorKeepEquip.getActor() != NULL)) {
        offModeFlg(ModeFlg_00000400);
        onModeFlg(ModeFlg_00000100);
        setTextureAnime(8, 0);
    } else {
        setBlendRopeMoveAnime(1);
    }
    if (pfVar7 == NULL) {
        m_old_fdata->initOldFrameMorf(15.0f, 0, 0x2A);
    }
    mFrameCtrlUnder[UNDER_MOVE0_e].setStart(daPy_HIO_rope_c0::m.field_0x1C);
    mFrameCtrlUnder[UNDER_MOVE0_e].setEnd(daPy_HIO_rope_c0::m.field_0x4);
    if ((pfVar7 != NULL) && (mActorKeepEquip.getActor() == NULL)) {
        mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform()->setFrame(mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
    }
    m34D0 = 0;
    shape_angle.x = param_1;
    return true;
}

/* 80144C58-801456D8       .text procRopeSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeSwing() {
    if (checkHangRopeActorNull()) {
        return true;
    }

    cXyz sp34;
    mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x28), &sp34);
    fopAc_ac_c* rope = mActorKeepRope.getActor();
    mRopePos = rope->current.pos;
    dComIfGp_setRStatus(dActStts_STOP_e);
    f32 f30 = m35A8 * m35A4;
    f32 dVar13 = m35AC * m35A4;
    mDoMtx_stack_c::ZrotS(-shape_angle.z);
    mDoMtx_stack_c::XrotM(-shape_angle.x);
    mDoMtx_stack_c::YrotM(-shape_angle.y);
    mDoMtx_stack_c::transM(-current.pos.x, -current.pos.y, -current.pos.z);
    cXyz sp28;
    mDoMtx_stack_c::multVec(&sp34, &sp28);

    if (checkSpecialRope()) {
        f30 = 0.0f;
        dVar13 = 0.0f;
    } else {
        if ((0.0f <= f30) && (f30 <= M_PI / 2)) {
            f30 = -0.45f * cM_fsin(f30);
        } else {
            if (f30 <= -M_PI / 2) {
                f30 = 0.45f * cM_fsin(f30);
            } else {
                f30 = 0.0f;
            }
        }
        if ((0.0f <= dVar13) && (dVar13 <= M_PI / 2)) {
            dVar13 = -0.45f * cM_fsin(dVar13);
        } else {
            if (dVar13 <= -M_PI / 2) {
                dVar13 = 0.45f * cM_fsin(dVar13);
            } else {
                dVar13 = 0.0f;
            }
        }
    }

    f32 dVar11 = 1.0f;
    m35A8 = m35A8 + (dVar11 + f30);
    m35AC = m35AC + (dVar11 + dVar13);
    f32 sp0C = m35A8 * m35A4;
    f30 = m35AC * m35A4;
    if (sp0C >= M_PI) {
        sp0C = sp0C - M_PI * 2;
        m35A8 = sp0C / m35A4;
    }
    if (f30 >= M_PI) {
        f30 = f30 - M_PI * 2;
        m35AC = f30 / m35A4;
    }
    if ((checkModeFlg(ModeFlg_00000400)) && (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f)) {
        offModeFlg(ModeFlg_00000400);
        onModeFlg(ModeFlg_00000100);
        setTextureAnime(8, 0);
    }
    setBlendRopeMoveAnime(0);

    s16 r30;
    s16 r28;
    s16 r29;
    if (checkSpecialRope()) {
        r30 = daPy_HIO_rope_c0::m.field_0x0 / 8.0f;
        r28 = 4;
        r29 = 8;
    } else {
        r30 = daPy_HIO_rope_c0::m.field_0x0;
        r28 = 0x20;
        r29 = 0x40;
    }
    if (spActionButton()) {
        cLib_chaseS(&m34D4, 0, r28 * 10);
        cLib_chaseS(&m34D6, 0, r28 * 10);
    } else {
        cLib_chaseS(&m34D6, 0, r28);
        f32 f1 = std::fabsf(sp0C);
        if (mStickDistance > 0.05f) {
            m34D4 += r29 * std::abs(cM_fcos(f1));
        } else {
            cLib_chaseS(&m34D4, 0, r28);
        }
    }
    if (m34D4 > r30) {
        m34D4 = r30;
    }

    s16 sp08 = -m34D4 * cM_fsin(sp0C);
    s16 r29_2 = m34D6 * cM_fsin(f30);
    s16 r28_2;
    if (m34D0 != 0) {
        dVar13 = m_pbCalc[PART_UNDER_e]->getRatio(1);
        f32 f2 = -m34D4 * cM_fsin(sp0C);
        f32 f0 = 0.5f * m34D4 * m34D0;
        r28_2 = f2 + (f0 * dVar13);
    } else {
        r28_2 = -m34D4 * cM_fsin(sp0C - (M_PI / 5));
    }
    cLib_addCalcAngleS(&shape_angle.x, r28_2, 8, 0xc00, 0x100);
    dVar13 = cM_fcos(f30);
    cLib_addCalcAngleS(
        &shape_angle.z, m34D6 * cM_fsin(f30 - 1.0995574f), 8, 0x400 + (0x800 * dVar13), 0x80 + (0x80 * dVar13)
    );
    cXyz sp1C(0.0f, -m35A0, 0.0f);
    mDoMtx_stack_c::transS(mRopePos.x, mRopePos.y, mRopePos.z);
    mDoMtx_stack_c::ZXYrotM(sp08, shape_angle.y, r29_2);
    mDoMtx_stack_c::multVec(&sp1C, &current.pos);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(-m34D4 * cM_fsin(sp0C + m35A4), shape_angle.y, r29_2);
    cXyz sp10;
    mDoMtx_stack_c::multVec(&sp28, &sp10);
    if (!checkRopeSwingWall(&sp34, &sp10, &sp08, &sp0C)) {
        static cXyz local_height_offset(0.0f, -105.0f, 0.0f);
        mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
        mDoMtx_stack_c::multVec(&local_height_offset, &sp10);
        if (!checkRopeSwingWall(&current.pos, &sp10, &sp08, &sp0C)) {
            resetFootEffect();
        }
    }

    f30 = ((f32)m34D4 / r30);
    if (changeRopeEndProc(0)) {
        dVar13 = (m35A0 / (100.0f * daPy_HIO_rope_c0::m.field_0x14));
        if (dVar13 < 1.0f) {
            dVar13 = 1.0f;
        }
        f30 *= dVar13;
        mVelocity = daPy_HIO_rope_c0::m.field_0xC * f30;
        if (std::abs(sp0C) > M_PI / 2) {
            current.angle.y = shape_angle.y + 0x8000;
        }
        speed.y = daPy_HIO_rope_c0::m.field_0x10 * f30;
        procFall_init(0, daPy_HIO_wallCatch_c0::m.field_0x54);
        onNoResetFlg1(daPyFlg1_UNK8000000);
    } else if ((m34D4 == 0) && (m34D6 == 0)) {
        procRopeHangWait_init(0);
    } else if (f30 > 0.6f) {
        if (cM_fcos(sp0C) > 0.77f) {
            mDoAud_seStart(JA_SE_LK_ROPE_SWING_F, &mRopePos, NULL, mReverb);
        }
    }

    return true;
}

/* 801456D8-801457FC       .text procRopeHangWait_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procRopeHangWait_init(int param_0) {
    commonProcInit(daPyProc_ROPE_HANG_WAIT_e);
    fopAc_ac_c* rope = mActorKeepRope.getActor();
    mRopePos = rope->current.pos;
    current.pos.x = mRopePos.x;
    current.pos.z = mRopePos.z;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK800000_e);
    gravity = 0.0f;
    if (param_0 == 0) {
        m34D0 = daPy_HIO_rope_c0::m.field_0x6;
        setSingleMoveAnime(
            ANM_ROPECATCH, 1.0f, mFrameCtrlUnder[UNDER_MOVE0_e].getEnd() - 0.001f, -1, daPy_HIO_rope_c0::m.field_0x28
        );
        setTextureAnime(2, 0);
    } else {
        m34D0 = -1;
        setSingleMoveAnime(ANM_ROPEWAIT, daPy_HIO_rope_c0::m.field_0x24, 0.0f, -1, daPy_HIO_rope_c0::m.field_0x28);
    }
    m34D4 = 0;
    return true;
}

/* 801457FC-80145B38       .text procRopeHangWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeHangWait() {
    /* Nonmatching */
    bool bVar1;
    s16 unaff_r29;
    float dVar4;

    dComIfGp_setRStatus(dActStts_STOP_e);
    if (m34D0 > 0) {
        m34D0--;
    }
    if (checkHangRopeActorNull()) {
        return true;
    }
    if (!changeRopeEndProc(1)) {
        bVar1 = false;
        fopAc_ac_c* rope = mActorKeepRope.getActor();
        mRopePos = rope->current.pos;
        current.pos.x = mRopePos.x;
        current.pos.z = mRopePos.z;
        s16 r30 = 0;
        if (mStickDistance > 0.05f) {
            int direction = getDirectionFromAngle(m34DC);
            if (spActionButton()) {
                if (direction == DIR_FORWARD) {
                    if (abs((int)m34D4) <= 0x80) {
                        procRopeUp_init();
                    }
                    bVar1 = true;
                    unaff_r29 = 0;
                } else if (direction == DIR_BACKWARD) {
                    if (abs((int)m34D4) <= 0x80) {
                        procRopeDown_init();
                    }
                    bVar1 = true;
                    unaff_r29 = 0;
                } else if (direction == DIR_LEFT) {
                    s16 r5 = 512.0f * mStickDistance;
                    if (r5 > m34D4) {
                        s16 r0 = 64.0f * mStickDistance;
                        m34D4 += r0;
                        if (m34D4 > r5) {
                            m34D4 = r5;
                        }
                        unaff_r29 = m34D4;
                    } else {
                        unaff_r29 = r5;
                    }
                } else { // DIR_RIGHT
                    s16 r5 = -512.0f * mStickDistance;
                    if (r5 < m34D4) {
                        s16 r0 = 64.0f * mStickDistance;
                        m34D4 -= r0;
                        if (m34D4 < r5) {
                            m34D4 = r5;
                        }
                        unaff_r29 = m34D4;
                    } else {
                        unaff_r29 = r5;
                    }
                }
                bVar1 = true;
                if (m34D0 != -1) {
                    m34D0 = -1;
                    setSingleMoveAnime(
                        ANM_ROPEWAIT, daPy_HIO_rope_c0::m.field_0x24, 0.0f, -1, daPy_HIO_rope_c0::m.field_0x2C
                    );
                }
            } else if ((direction == DIR_FORWARD) || (direction == DIR_BACKWARD)) {
                procRopeSwingStart_init();
            }
            unaff_r29 = 0;
            bVar1 = true;
        } else if (m34D0 == 0) {
            m34D0 = -1;
            setSingleMoveAnime(ANM_ROPEWAIT, daPy_HIO_rope_c0::m.field_0x24, 0.0f, -1, daPy_HIO_rope_c0::m.field_0x2C);
        }
        unaff_r29 = 0;
        bVar1 = true;
        if (bVar1) {
            cLib_addCalcAngleS(&m34D4, unaff_r29, 3, 0x40, 0x10);
            if (m34D4 > 0) {
                dVar4 = checkRopeRoofHit(shape_angle.y + 0x2000);
            } else {
                dVar4 = checkRopeRoofHit(shape_angle.y + -0x2000);
            }
            if (5.0f + (dVar4 - 60.0f) > current.pos.y) {
                shape_angle.y = shape_angle.y + m34D4;
                current.angle.y = shape_angle.y;
            }
        }
    }
    return true;
}

/* 80145B38-80145C3C       .text specialRopeHangUp__9daPy_lk_cFv */
int daPy_lk_c::specialRopeHangUp() {
    if (checkSpecialRope()) {
        u32 uVar1 = shape_angle.y >= 0x4000 ? 0 : 1;
        int iVar2 = abs(uVar1);
        if (iVar2 != 0) {
            current.pos.z = -15.8f;
            shape_angle.y = 0;
        } else {
            current.pos.z = 15.8f;
            shape_angle.y = -0x8000;
        }
        current.pos.x = 361.4f;
        current.pos.y = 4464.8f;
        old.pos = current.pos;
        current.angle.y = shape_angle.y;
        m3724 = current.pos;
        m352C = shape_angle.y + 0x8000;
        setSingleMoveAnime(ANM_VJMP, 1.0f, 10.0f, -1, 3.0f);
        return procHangStart_init();
    } else {
        return false;
    }
}

/* 80145C3C-80145DBC       .text procRopeUp_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeUp_init() {
    fopAc_ac_c* rope = mActorKeepRope.getActor();
    mRopePos = rope->current.pos;
    mProcVar0.m3570 = 0;
    f32 dVar4;
    if (checkBossGomaStage()) {
        dVar4 = mRopePos.y - 200.0f;
    } else {
        dVar4 = mRopePos.y - 100.0f;
        f32 dVar5 = checkRopeRoofHit(shape_angle.y);
        dVar5 = dVar5 - 60.0f;
        if (dVar5 < dVar4) {
            dVar4 = dVar5;
        } else if ((fopAcM_GetName(rope)) == PROC_HIMO2 || (checkSpecialRope())) {
            mProcVar0.m3570 = 1;
        }
    }
    if (dVar4 <= current.pos.y) {
        if (specialRopeHangUp()) {
            return true;
        } else if (changeRopeToHangProc()) {
            return true;
        } else {
            return procRopeHangWait_init(0);
        }
    } else {
        commonProcInit(daPyProc_ROPE_UP_e);
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK800000_e);
        setSingleMoveAnime(ANM_ROPECLIMB, daPy_HIO_rope_c0::m.field_0x30, 0.0f, -1, daPy_HIO_rope_c0::m.field_0x34);
        mFrameCtrlUnder[UNDER_MOVE0_e].setAttribute(J3DFrameCtrl::EMode_NONE);
        m35A0 = dVar4;
        gravity = 0.0f;
        return true;
    }
}

/* 80145DBC-80145F64       .text procRopeUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeUp() {
    dComIfGp_setRStatus(dActStts_STOP_e);
    if (checkHangRopeActorNull()) {
        return true;
    }
    if (!changeRopeEndProc(1)) {
        mRopePos = mActorKeepRope.getActor()->current.pos;
        current.pos.x = mRopePos.x;
        current.pos.z = mRopePos.z;
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
            int direction = getDirectionFromAngle(m34DC);
            if (mStickDistance <= 0.05f) {
                procRopeHangWait_init(0);
            } else {
                if (!spActionButton()) {
                    procRopeSwingStart_init();
                } else if (direction == DIR_BACKWARD) {
                    procRopeDown_init();
                } else if (direction == DIR_FORWARD) {
                    if (m35A0 <= current.pos.y) {
                        if (!specialRopeHangUp()) {
                            procRopeHangWait_init(0);
                        }
                    } else {
                        setSingleMoveAnime(ANM_ROPECLIMB, daPy_HIO_rope_c0::m.field_0x30, 0.0f, -1, -1.0f);
                        mFrameCtrlUnder[UNDER_MOVE0_e].setAttribute(J3DFrameCtrl::EMode_NONE);
                    }
                } else {
                    procRopeHangWait_init(0);
                }
            }
        } else {
            cLib_chaseF(&current.pos.y, m35A0, 5.0f);
            if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= 12.0f) {
                onResetFlg0(daPyRFlg0_ROPE_GRAB_RIGHT_HAND);
            }
        }
    }
    return true;
}

/* 80145F64-801460EC       .text procRopeDown_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeDown_init() {
    fopAc_ac_c* rope = mActorKeepRope.getActor();
    mRopePos = rope->current.pos;
    if (mActorKeepEquip.getActor() != NULL) {
        if (m3604 >= 0.0f) {
            m35A4 = m3600 - m3604;
        } else if (checkBossGomaStage()) {
            m35A4 = m3600 - 100.0f;
        } else {
            m35A4 = m3600 - 300.0f;
            mGndChk.SetPos(&mRopePos);
            f32 dVar5 = dComIfG_Bgsp()->GroundCross(&mGndChk);
            if (dVar5 > ((m35A4 - 125.0f) - 50.0f)) {
                m35A4 = 50.0f + (125.0f + dVar5);
            }
        }
    } else {
        himo2_class* rope = (himo2_class*)mActorKeepRope.getActor();
        m35A4 = mRopePos.y - rope->field_0x15F8.y;
    }
    if (current.pos.y <= m35A4) {
        return procRopeHangWait_init(1);
    } else {
        commonProcInit(daPyProc_ROPE_DOWN_e);
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK800000_e);
        setSingleMoveAnime(ANM_ROPEDOWN, daPy_HIO_rope_c0::m.field_0x38, 0.0f, -1, daPy_HIO_rope_c0::m.field_0x3C);
        gravity = 0.0f;
        m35A0 = 0.0f;
        return true;
    }
}

/* 801460EC-80146240       .text procRopeDown__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeDown() {
    dComIfGp_setRStatus(dActStts_STOP_e);
    if (checkHangRopeActorNull()) {
        return true;
    }
    if (!changeRopeEndProc(1)) {
        mRopePos = mActorKeepRope.getActor()->current.pos;
        current.pos.x = mRopePos.x;
        current.pos.z = mRopePos.z;
        int direction = getDirectionFromAngle(m34DC);
        if (mStickDistance <= 0.05f) {
            procRopeHangWait_init(1);
        } else {
            if (!spActionButton()) {
                procRopeSwingStart_init();
            } else if (direction == DIR_FORWARD) {
                procRopeUp_init();
            } else if (direction == DIR_BACKWARD) {
                m35A0 += 1.5f;
                if (m35A0 > daPy_HIO_rope_c0::m.field_0x40) {
                    m35A0 = daPy_HIO_rope_c0::m.field_0x40;
                }
                if (cLib_chaseF(&current.pos.y, m35A4, m35A0)) {
                    procRopeHangWait_init(1);
                }
            } else {
                procRopeHangWait_init(1);
            }
        }
    }
    return true;
}

/* 80146240-801463E8       .text procRopeSwingStart_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeSwingStart_init() {
    mRopePos = mActorKeepRope.getActor()->current.pos;
    commonProcInit(daPyProc_ROPE_SWING_START_e);
    m35A0 = mRopePos.abs(current.pos);
    m35A4 = 500.0f / m35A0;
    if (m35A4 > 1.0f) {
        m35A4 = 1.0f;
    }
    setSingleMoveAnime(ANM_ROPESWINGB, 1.0f, 0.0f, -1, 20.0f);
    m34D4 = 2048.0f * m35A4;
    if (checkSpecialRope()) {
        m34D4 *= 0.125f;
    }
    gravity = 0.0f;
    m34D0 = 0;
    mRopePos = mActorKeepRope.getActor()->current.pos;
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK800000_e);
    return true;
}

/* 801463E8-80146610       .text procRopeSwingStart__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeSwingStart() {
    dComIfGp_setRStatus(dActStts_STOP_e);
    cXyz local_28;
    local_28.set(0.0f, -m35A0, 0.0f);
    if (checkHangRopeActorNull()) {
        return true;
    }
    if (!changeRopeEndProc(1)) {
        mRopePos = mActorKeepRope.getActor()->current.pos;
        if (m34D0 == 1) {
            if (!cLib_addCalcAngleS(&shape_angle.x, m34D4, 5, 0x180, 0x40)) {
                procRopeSwing_init(NULL, shape_angle.x);
            }
        } else {
            if (!cLib_addCalcAngleS(&shape_angle.x, m34D4, 5, 0xa0, 0x40)) {
                if (m34D4 > 0) {
                    setSingleMoveAnime(ANM_ROPESWINGF, 1.0f, 0.0f, -1, 10.0f);
                    m34D4 = -4096.0f * m35A4;
                } else {
                    setSingleMoveAnime(ANM_ROPESWINGB, 1.0f, 0.0f, -1, 10.0f);
                    m34D4 = 4096.0f * m35A4;
                }
                m34D0 = 1;
                if (checkSpecialRope()) {
                    m34D4 *= 0.125f;
                }
            }
        }
        if (mAcch.ChkWallHit()) {
            procRopeSwing_init(NULL, shape_angle.x);
        }
    }
    mDoMtx_stack_c::transS(mRopePos.x, mRopePos.y, mRopePos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, 0);
    mDoMtx_stack_c::multVec(&local_28, &current.pos);
    return true;
}

/* 80146610-801466E8       .text procRopeMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeMove_init() {
    if (mCurProc == daPyProc_ROPE_MOVE_e) {
        return false;
    }
    commonProcInit(daPyProc_ROPE_MOVE_e);
    if (mDirection == DIR_LEFT) {
        current.angle.y = shape_angle.y + 0x4000;
    } else {
        mDirection = DIR_RIGHT;
        current.angle.y = shape_angle.y + -0x4000;
    }
    if (fopAcM_GetParam(mActorKeepEquip.getActor()) == 0) {
        setActAnimeUpper(LKANM_BCK_ROPETHROWWAIT, UPPER_MOVE2_e, daPy_HIO_rope_c0::m.field_0x50, 0.0f, -1, -1.0f);
        setBlendAtnMoveAnime(daPy_HIO_rope_c0::m.field_0x54);
    }
    dComIfGp_setPlayerStatus0(0, daPyStts0_ROPE_AIM_e);
    return true;
}

/* 801466E8-80146848       .text procRopeMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeMove() {
    if (!checkItemModeActorPointer()) {
        return true;
    }
    if ((fopAcM_GetParam(mActorKeepEquip.getActor()) == 0) && (checkRopeReadyAnime())) {
        if (mpAttnActorLockOn != NULL) {
            setSpeedAndAngleAtnActor();
        } else {
            if ((m355E == 0) && (!mpAttention->Lockon())) {
                resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
            } else {
                setSpeedAndAngleAtn();
            }
        }
    }
    if (checkNextMode(0) == 0) {
        f32 fVar1 = -1.0f;
        if (std::abs(mVelocity) < 0.001f) {
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

/* 80146848-801468C4       .text procRopeThrowCatch_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeThrowCatch_init() {
    commonProcInit(daPyProc_ROPE_THROW_CATCH_e);
    setSingleMoveAnime(
        ANM_ROPETHROWCATCH,
        daPy_HIO_rope_c0::m.field_0x58,
        daPy_HIO_rope_c0::m.field_0x5C,
        daPy_HIO_rope_c0::m.field_0xA,
        daPy_HIO_rope_c0::m.field_0x64
    );
    mVelocity = 0.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_ROPE_AIM_e);
    m34D0 = 0x1e;
    return true;
}

/* 801468C4-801469A8       .text procRopeThrowCatch__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeThrowCatch() {
    if (!checkItemModeActorPointer()) {
        return true;
    }
    if (mpAttention->Lockon()) {
        dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK40000_e);
    } else {
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK40000_e);
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        m34D0--;
        himo2_class* rope = (himo2_class*)mActorKeepEquip.getActor();
        if (rope->field_0x2DC == 0 || (m34D0 == 0)) {
            checkNextRopeMode();
        }
    }
    return true;
}

/* 801469A8-80146A44       .text procRopeUpHang_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeUpHang_init() {
    commonProcInit(daPyProc_ROPE_UP_HANG_e);
    dComIfGp_setPlayerStatus0(0, daPyStts0_UNK800000_e);
    setSingleMoveAnime(ANM_VJMP, 1.0f, 10.0f, -1, 3.0f);
    gravity = 0.0f;
    shape_angle.y = m352C + 0x8000;
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    speed.y = 0.0f;
    current.pos.y -= 80.0f;
    return true;
}

/* 80146A44-80146AF0       .text procRopeUpHang__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeUpHang() {
    if (checkHangRopeActorNull()) {
        return true;
    }
    mRopePos = mActorKeepRope.getActor()->current.pos;
    current.pos.x = mRopePos.x;
    current.pos.z = mRopePos.z;
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        m3724 = mRopePos;
        m352C = shape_angle.y + 0x8000;
        procHangStart_init();
    }
    return true;
}
