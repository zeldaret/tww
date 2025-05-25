/**
 * d_a_player_hammer.inc
 *
 * Code relating to the Skull Hammer item.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is known because of an assert contained within
 * a function from this file.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"

extern JGeometry::TVec3<f32> l_hammer_splash_particle_scale;

/* 8015023C-80150324       .text setHammerModel__9daPy_lk_cFv */
void daPy_lk_c::setHammerModel() {
    J3DAnmTransform* bck = getItemAnimeResource(LKANM_BCK_HAMMERDAM);
    JKRHeap* oldHeap = setItemHeap();
    J3DModelData* tmp_modelData = initModel(&mpEquipItemModel, LINK_BDL_HAMMER, 0x37221222);
    int ret = mSwordAnim.init(tmp_modelData, bck, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) {
        JUT_ASSERT(32, FALSE);
    }
    mSwBlur.mpPosBuffer = new (0x20) Vec[2 * 0x300];
    mDoExt_setCurrentHeap(oldHeap);
    m35EC = 0.0f;
}

/* 80150324-801508FC       .text setHammerQuake__9daPy_lk_cFP13cBgS_PolyInfoPC4cXyzi */
void daPy_lk_c::setHammerQuake(cBgS_PolyInfo* param_1, const cXyz* param_2, int param_3) {
    static JGeometry::TVec3<f32> smoke_kusa_particle_scale(2.0f, 2.0f, 2.0f);
    static JGeometry::TVec3<f32> emitter_scale(1.0f, 0.1f, 1.0f);
    static JGeometry::TVec3<f32> emitter_trans(0.0f, 10.0f, 0.0f);
    float local_54;
    BOOL bVar2;
    int attrib_code;
    int iVar6;
    JPABaseEmitter* emitter;
    f32 dVar9;
    int iStack_58;
    cXyz local_2c;
    cXyz local_38;

    dComIfGp_getVibration().StartShock(6, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    onResetFlg0(daPyRFlg0_HAMMER_QUAKE);
    if (!checkNoResetFlg0(daPyFlg0_UNK10000000)) {
        if (param_3 == -1) {
            local_2c.set(mSwordTopPos.x, mSwordTopPos.y + 100.0f, mSwordTopPos.z);
            mGndChk.SetPos(&local_2c);
            dVar9 = dComIfG_Bgsp()->GroundCross(&mGndChk);
            if (-G_CM3D_F_INF != dVar9) {
                iVar6 = dComIfG_Bgsp()->GetMtrlSndId(mGndChk);
            } else {
                iVar6 = mMtrlSndId;
            }
        } else {
            iVar6 = param_3;
        }
        mDoAud_seStart(JA_SE_LK_HAMMER_HIT, &mSwordTopPos, iVar6, mReverb);
    }
    if (param_1 != NULL && m355C == 0) {
        mDoMtx_stack_c::transS(param_2->x, param_2->y, param_2->z);
        mDoMtx_stack_c::ZXYrotM(
            getGroundAngle(param_1, shape_angle.y), shape_angle.y, getGroundAngle(param_1, shape_angle.y + -0x4000)
        );
        mDoMtx_stack_c::transM(0.0f, 0.0f, -30.0f);
        local_38.x = mDoMtx_stack_c::now[0][3];
        local_38.y = mDoMtx_stack_c::now[1][3];
        local_38.z = mDoMtx_stack_c::now[2][3];
        if (!fopAcM_getWaterY(&local_38, &local_54) || (local_54 < (5.0f + local_38.y))) {
            emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_0214, &local_38);
            if (emitter != NULL) {
                JPASetRMtxTVecfromMtx(mDoMtx_stack_c::get(), emitter->mGlobalRotation, emitter->mGlobalTranslation);
            }
            emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_0215, &local_38);
            if (emitter != NULL) {
                JPASetRMtxTVecfromMtx(mDoMtx_stack_c::get(), emitter->mGlobalRotation, emitter->mGlobalTranslation);
            }
            emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_0216, &local_38);
            if (emitter != NULL) {
                JPASetRMtxTVecfromMtx(mDoMtx_stack_c::get(), emitter->mGlobalRotation, emitter->mGlobalTranslation);
            }
            bVar2 = false;
        } else {
            bVar2 = true;
            local_38.y = local_54;
            mDoMtx_stack_c::transS(local_38.x, local_54, local_38.z);
            mDoMtx_stack_c::YrotM(shape_angle.y);
        }
        if (bVar2) {
            attrib_code = dBgS_Attr_WATER_e;
            dComIfGp_particle_setP1(dPa_name::ID_COMMON_027C, &local_38);
            dComIfGp_particle_setShipTail(
                dPa_name::ID_COMMON_003D, &local_38, NULL, NULL, 0xFF, &dPa_control_c::mSingleRippleEcallBack
            );
        } else {
            attrib_code = dComIfG_Bgsp()->GetAttributeCode(*param_1);
        }
        emitter =
            dComIfGp_particle_setSimpleLand(attrib_code, &local_38, NULL, 1.0f, 1.0f, 1.0f, &tevStr, &iStack_58, 0x1E);
        if (emitter != NULL) {
            JPASetRMtxTVecfromMtx(mDoMtx_stack_c::get(), emitter->mGlobalRotation, emitter->mGlobalTranslation);
            if (attrib_code == dBgS_Attr_WATER_e || attrib_code == dBgS_Attr_GRASS_e) {
                emitter->setRate(60.0f);
                emitter->setSpread(1.0f);
                if (attrib_code == dBgS_Attr_WATER_e) {
                    emitter->setDirectionalSpeed(10.0f);
                    emitter->setGlobalParticleScale(l_hammer_splash_particle_scale);
                } else {
                    emitter->setDirectionalSpeed(40.0f);
                    emitter->setGlobalParticleScale(smoke_kusa_particle_scale);
                }
            } else {
                emitter->setRate(45.0f);
                emitter->setSpread(0.0f);
                emitter->setLifeTime(0x28);
                emitter->setEmitterScale(emitter_scale);
                emitter->setEmitterTranslation(emitter_trans);
                emitter->setAwayFromCenterSpeed(50.0f);
                emitter->setGlobalParticleScale(smoke_kusa_particle_scale);
            }
        }
    }
    m355C = 1;
    dKy_Sound_set(current.pos, 500, fopAcM_GetID(this), 10);
}

/* 801508FC-80150B60       .text setHammerWaterSplash__9daPy_lk_cFv */
void daPy_lk_c::setHammerWaterSplash() {
    f32 local_50;
    cXyz local_28;

    if (mCurProc != daPyProc_HAMMER_FRONT_SWING_e || (m35EC <= mFrameCtrlUnder[UNDER_MOVE0_e].getRate())) {
        return;
    }
    if (m355C == 0) {
        local_28 = m36C4 - mSwordTopPos;
        local_28.normalize();
        local_28 = mSwordTopPos + (local_28 * 30.0f);
        if (fopAcM_getWaterY(&local_28, &local_50) && local_50 >= local_28.y + 5.0f) {
            local_28.y += 150.0f;
            mGndChk.SetPos(&local_28);
            if (!(local_50 < dComIfG_Bgsp()->GroundCross(&mGndChk) + 5.0f)) {
                local_28.y = local_50;
                dComIfGp_particle_setP1(dPa_name::ID_COMMON_027C, &local_28);
                dComIfGp_particle_setShipTail(
                    dPa_name::ID_COMMON_003D, &local_28, NULL, NULL, 0xFF, &dPa_control_c::mSingleRippleEcallBack
                );
                GXColor amb, dif;
                dKy_get_seacolor(&amb, &dif);
                JPABaseEmitter* emitter =
                    dComIfGp_particle_setP1(dPa_name::ID_COMMON_0023, &local_28, NULL, NULL, 0xFF, NULL, -1, &amb);
                if (emitter != NULL) {
                    emitter->setRate(60.0f);
                    emitter->setSpread(1.0f);
                    emitter->setMaxFrame(1);
                    emitter->setDirectionalSpeed(10.0f);
                    emitter->setGlobalParticleScale(l_hammer_splash_particle_scale);
                }
                m355C = 1;
            }
        }
    }
}

/* 80150B60-80150C40       .text procHammerSideSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerSideSwing_init() {
    commonProcInit(daPyProc_HAMMER_SIDE_SWING_e);
    setSingleMoveAnime(
        ANM_HAMSWINGA,
        daPy_HIO_ham_c0::m.field_0x8,
        daPy_HIO_ham_c0::m.field_0xC,
        daPy_HIO_ham_c0::m.field_0x0,
        daPy_HIO_ham_c0::m.field_0x14
    );
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    voiceStart(1);
    m34D4 = shape_angle.y;
    setBlurPosResource(LKANM__HAMMERSIDE_POS);
    setAtParam(AT_TYPE_SKULL_HAMMER, 4, dCcG_At_Spl_UNK0, dCcG_SE_UNK5, dCcG_AtHitMark_Nrm_e, 17, 50.0f);
    mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_HAMSWINGAA));
    m35EC = daPy_HIO_ham_c0::m.field_0xC;
    return true;
}

/* 80150C40-80150DDC       .text procHammerSideSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerSideSwing() {
    m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        mVelocity = 0.0f;
        mDirection = DIR_RIGHT;
        checkNextMode(0);
        return true;
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_ham_c0::m.field_0x10) {
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
        setHammerQuake(NULL, NULL, -1);
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
    if ((mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= daPy_HIO_ham_c0::m.field_0x18) &&
        (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() < daPy_HIO_ham_c0::m.field_0x1C))
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_HAMMER_SWING);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    return true;
}

/* 80150DDC-80150F08       .text procHammerFrontSwingReady_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwingReady_init() {
    commonProcInit(daPyProc_HAMMER_FRONT_SWING_READY_e);
    setSingleMoveAnime(
        ANM_HAMSWINGBPRE,
        daPy_HIO_ham_c0::m.field_0x20,
        daPy_HIO_ham_c0::m.field_0x24,
        daPy_HIO_ham_c0::m.field_0x2,
        daPy_HIO_ham_c0::m.field_0x28
    );
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    if (mpAttention->Lockon() || mStickDistance <= 0.05f) {
        m34D4 = shape_angle.y;
    } else {
        m34D4 = m34E8;
    }
    setAtParam(AT_TYPE_SKULL_HAMMER, 4, dCcG_At_Spl_UNK0, dCcG_SE_UNK5, dCcG_AtHitMark_Nrm_e, 18, 50.0f);
    voiceStart(7);
    mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_HAMSWINGBPREA));
    m35EC = daPy_HIO_ham_c0::m.field_0x24;
    m355C = 0;
    return true;
}

/* 80150F08-80150F98       .text procHammerFrontSwingReady__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwingReady() {
    m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        return procHammerFrontSwing_init();
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

/* 80150F98-801510DC       .text procHammerFrontSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwing_init() {
    commonProcInit(daPyProc_HAMMER_FRONT_SWING_e);
    setSingleMoveAnime(
        ANM_HAMSWINGBHIT,
        4.0f * daPy_HIO_ham_c0::m.field_0x2C,
        daPy_HIO_ham_c0::m.field_0x30,
        daPy_HIO_ham_c0::m.field_0x4,
        0.0f
    );
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    voiceStart(1);
    if (mpAttention->Lockon() || mStickDistance <= 0.05f) {
        m34D4 = shape_angle.y;
    } else {
        m34D4 = m34E8;
    }
    m34D4 = shape_angle.y;
    setBlurPosResource(LKANM__HAMMERFRONT_POS);
    mCutType = 18;
    offResetFlg0(daPyRFlg0_UNK8000000);
    onResetFlg0(daPy_RFLG0(daPyRFlg0_UNK1 | daPyRFlg0_UNK2));
    m34D0 = 0;
    mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_HAMSWINGBHITA));
    m35EC = daPy_HIO_ham_c0::m.field_0x30;
    return true;
}

/* 801510DC-801513D4       .text procHammerFrontSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwing() {
    m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    f32 f1 = mFrameCtrlUnder[UNDER_MOVE0_e].getRate();
    if (f1 < 0.01f) {
        if (m34D0 == 0) {
            return procHammerFrontSwingEnd_init();
        } else {
            m34D0--;
        }
        return true;
    }
    if (m35EC > f1 && changeCutReverseProc(ANM_CUTREL)) {
        if (mCurProc == daPyProc_HAMMER_FRONT_SWING_e) {
            cXyz sp08(mSwordTopPos.x, current.pos.y + 300.0f, mSwordTopPos.z);
            mGndChk.SetPos(&sp08);
            sp08.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
            if (sp08.y > mSwordTopPos.y) {
                int r27;
                int r26;
                r26 = -1;
                f32 f30 = 300.0f;
                f32 f31 = -G_CM3D_F_INF;
                for (r27 = 0; r27 < mSwBlur.field_0x014; r27++) {
                    sp08.set(mSwBlur.field_0x034[r27].x, f30 + mSwBlur.field_0x034[r27].y, mSwBlur.field_0x034[r27].z);
                    mGndChk.SetPos(&sp08);
                    sp08.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
                    if (f31 != sp08.y && mSwBlur.field_0x034[r27].y > sp08.y) {
                        r26 = dComIfG_Bgsp()->GetMtrlSndId(mGndChk);
                        break;
                    }
                }
                f32 f4 = mFrameCtrlUnder[UNDER_MOVE0_e].getRate();
                f32 f5 = (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - f4) - 0.1f * (r27 * f4);
                if (r27 != 0 && r27 < mSwBlur.field_0x014) {
                    f32 f6 = mSwBlur.field_0x034[r27].y - mSwBlur.field_0x034[r27 - 1].y;
                    if (std::abs(f6) > 1.0f) {
                        f32 temp = (1.0f - (sp08.y - (&mSwBlur.field_0x034[0])[r27 - 1].y) / f6);
                        f5 = f5 + 0.1f * (temp * f4);
                    }
                }
                if (f5 < 0.0f) {
                    f5 = 0.0f;
                }
                mFrameCtrlUnder[UNDER_MOVE0_e].setFrame(f5);
                mFrameCtrlUnder[UNDER_MOVE0_e].setRate(0.0f);
                m35EC = f5;
                m34D0 = 10;
                setHammerQuake(&mGndChk, &sp08, r26);
                return true;
            }
        } else {
            setHammerQuake(NULL, NULL, -1);
            return true;
        }
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

/* 801513D4-80151450       .text procHammerFrontSwingEnd_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwingEnd_init() {
    commonProcInit(daPyProc_HAMMER_FRONT_SWING_END_e);
    setSingleMoveAnime(
        ANM_HAMSWINGBEND,
        daPy_HIO_ham_c0::m.field_0x34,
        daPy_HIO_ham_c0::m.field_0x38,
        daPy_HIO_ham_c0::m.field_0x6,
        daPy_HIO_ham_c0::m.field_0x40
    );
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    mCutType = 18;
    offResetFlg0(daPyRFlg0_UNK8000000);
    return true;
}

/* 80151450-801514B0       .text procHammerFrontSwingEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwingEnd() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        return checkNextMode(0);
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_ham_c0::m.field_0x3C) {
        return checkNextMode(1);
    } else {
        return true;
    }
}
