/**
 * d_a_player_fan.inc
 *
 * Code relating to the Deku Leaf item.
 *
 * This file is not a standalone translation unit and is instead directly
 * included into d_a_player_main.cpp.
 *
 * The original name of this file is known because of an assert contained within
 * a function from this file.
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_kankyo_wether.h"

extern char l_arcName[];

/* 8014BAA0-8014BAEC       .text fanWindEffectDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::fanWindEffectDraw() {
    return mpYuchw00Brk->getFrame() <= mpYuchw00Brk->getFrameMax() - 0.5f;
}

/* 8014BAEC-8014BB38       .text fanWindCrashEffectDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::fanWindCrashEffectDraw() {
    return mpYbafo00Btk->getFrame() <= mpYbafo00Btk->getFrameMax() - 0.5f;
}

/* 8014BB38-8014BBE8       .text fanJointCB__9daPy_lk_cFi */
BOOL daPy_lk_c::fanJointCB(int param_0) {
    if (param_0 == 2) {
        mDoMtx_stack_c::ZrotS(m3558);
    } else {
        mDoMtx_stack_c::ZrotS(m355A);
    }
    mDoMtx_stack_c::revConcat(mpEquipItemModel->getAnmMtx(param_0));
    mpEquipItemModel->setAnmMtx(1 * param_0, mDoMtx_stack_c::get());
    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    return true;
}

/* 8014BBE8-8014BC2C       .text daPy_fanJointCallback__FP7J3DNodei */
BOOL daPy_fanJointCallback(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        s32 jntNo = joint->getJntNo();
        i_this->fanJointCB(jntNo);
    }
    return TRUE;
}

/* 8014BC2C-8014BD08       .text parachuteJointCB__9daPy_lk_cFi */
BOOL daPy_lk_c::parachuteJointCB(int param_0) {
    if (param_0 == 3 || param_0 == 9) {
        mDoMtx_stack_c::transS(m3600, 0.0f, 0.0f);
    } else if (param_0 == 1 || param_0 == 7) {
        mDoMtx_stack_c::YrotS(m355E);
    } else {
        return true;
    }
    mDoMtx_stack_c::revConcat(mpEquipItemModel->getAnmMtx(param_0));
    mpEquipItemModel->setAnmMtx(1 * param_0, mDoMtx_stack_c::get());
    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    return true;
}

/* 8014BD08-8014BD4C       .text daPy_parachuteJointCallback__FP7J3DNodei */
BOOL daPy_parachuteJointCallback(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        J3DModel* model = j3dSys.getModel();
        daPy_lk_c* i_this = reinterpret_cast<daPy_lk_c*>(model->getUserArea());
        s32 jntNo = joint->getJntNo();
        i_this->parachuteJointCB(jntNo);
    }
    return TRUE;
}

/* 8014BD4C-8014BE50       .text setShapeFanLeaf__9daPy_lk_cFv */
int daPy_lk_c::setShapeFanLeaf() {
    J3DMaterial* mtl;
    if (mpEquipItemModel != NULL) {
        mtl = mpEquipItemModel->getModelData()->getJointNodePointer(0x00)->getMesh()->getNext();
    }
    m355C = m355C + 0x82f;
    m3558 = 1536.0f * cM_ssin(m355C);
    m355A = 2048.0f * cM_ssin(m355C - 0xe00U);
    if (dComIfGs_getMagic() >= 1) {
        // Show material:
        // * "leafAMat"
        for (; mtl != NULL; mtl = mtl->getNext()) {
            mtl->getShape()->show();
        }
        return true;
    } else {
        // Hide material:
        // * "leafAMat"
        for (; mtl != NULL; mtl = mtl->getNext()) {
            mtl->getShape()->hide();
        }
        return false;
    }
}

/* 8014BE50-8014BEEC       .text checkFanGlideProc__9daPy_lk_cFi */
BOOL daPy_lk_c::checkFanGlideProc(int param_0) {
    if (checkSetItemTrigger(dItem_DEKU_LEAF_e, 1)) {
        if (dComIfGs_getMagic() >= 1) {
            return procFanGlide_init(param_0);
        }
        seStartSystem(JA_SE_ITEM_TARGET_OUT);
    }
    return false;
}

/* 8014BEEC-8014BFBC       .text setFanModel__9daPy_lk_cFv */
void daPy_lk_c::setFanModel() {
    J3DAnmTransform* bck = getItemAnimeResource(LKANM_BCK_USEFANAA);
    JKRHeap* oldHeap = setItemHeap();
    J3DModelData* tmp_modelData = initModel(&mpEquipItemModel, LINK_BDL_FAN, 0x37221222);
    int ret = mSwordAnim.init(tmp_modelData, bck, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) {
        JUT_ASSERT(242, FALSE);
    }
    mDoExt_setCurrentHeap(oldHeap);
}

/* 8014BFBC-8014C0C0       .text setSmallFanModel__9daPy_lk_cFv */
void daPy_lk_c::setSmallFanModel() {
    J3DModelData* tmp_modelData;
    J3DAnmTransform* bck = getItemAnimeResource(LKANM_BCK_FANWAIT);
    JKRHeap* oldHeap = setItemHeap();
    tmp_modelData = initModel(&mpEquipItemModel, LINK_BDL_FANSMALL, 0x37221222);
    int ret = mSwordAnim.init(tmp_modelData, bck, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) {
        JUT_ASSERT(275, FALSE);
    }
    mDoExt_setCurrentHeap(oldHeap);
    mpEquipItemModel->setUserArea(reinterpret_cast<u32>(this));
    tmp_modelData->getJointNodePointer(0x02)->setCallBack(daPy_fanJointCallback);
    tmp_modelData->getJointNodePointer(0x03)->setCallBack(daPy_fanJointCallback);
    m355C = 0;
}

/* 8014C0C0-8014C254       .text setParachuteFanModel__9daPy_lk_cFf */
void daPy_lk_c::setParachuteFanModel(f32 f31) {
    J3DAnmTransform* bck = getItemAnimeResource(LKANM_BCK_FANBA);
    JKRHeap* oldHeap = setItemHeap();
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcName, LINK_BDL_FANB));

    mpParachuteFanMorf = new mDoExt_McaMorf(
        modelData,
        NULL,
        NULL,
        bck,
        J3DFrameCtrl::EMode_NONE,
        daPy_HIO_fan_c0::m.field_0x20,
        f31,
        daPy_HIO_fan_c0::m.field_0x4,
        0,
        NULL,
        0x00000000,
        0x11020203
    );
    if (mpParachuteFanMorf == NULL || mpParachuteFanMorf->getModel() == NULL) {
        JUT_ASSERT(323, FALSE);
    }

    mpEquipItemModel = mpParachuteFanMorf->getModel();
    mDoExt_setCurrentHeap(oldHeap);
    mpEquipItemModel->setUserArea(reinterpret_cast<u32>(this));
    modelData->getJointNodePointer(0x01)->setCallBack(daPy_parachuteJointCallback); // Lroot joint
    modelData->getJointNodePointer(0x07)->setCallBack(daPy_parachuteJointCallback); // Rroot joint
    modelData->getJointNodePointer(0x03)->setCallBack(daPy_parachuteJointCallback); // LarmB joint
    modelData->getJointNodePointer(0x09)->setCallBack(daPy_parachuteJointCallback); // RarmB joint
}

/* 8014C254-8014C34C       .text procFanSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procFanSwing_init() {
    commonProcInit(daPyProc_FAN_SWING_e);
    setSingleMoveAnime(
        ANM_USEFANA,
        daPy_HIO_fan_c0::m.field_0xC,
        daPy_HIO_fan_c0::m.field_0x10,
        daPy_HIO_fan_c0::m.field_0x2,
        daPy_HIO_fan_c0::m.field_0x14
    );
    setFanModel();
    mProcVar0.m3570 = 0;
    voiceStart(7);
    setAtParam(AT_TYPE_UNK2000000, 1, dCcG_At_Spl_UNK0, dCcG_SE_UNK4, dCcG_AtHitMark_Nrm_e, 0, 50.0f);
    m35EC = daPy_HIO_fan_c0::m.field_0x10;
    if (setShapeFanLeaf()) {
        m34D0 = 1;
        seStartOnlyReverb(JA_SE_LK_FAN_PRE_SWING);
        dComIfGp_setPlayerStatus1(0, daPyStts1_DEKU_LEAF_FAN_e);
    } else {
        m34D0 = 0;
    }
    return true;
}

/* 8014C34C-8014CA1C       .text procFanSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procFanSwing() {
    JPABaseEmitter* pJVar5;
    cXyz local_6c;
    cXyz local_60;
    cXyz local_54;
    cXyz local_48;
    cXyz local_3c;
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    if (mpAttnActorLockOn != NULL) {
        onModeFlg(ModeFlg_00000080);
    } else {
        offModeFlg(ModeFlg_00000080);
    }

    if (changeCutReverseProc(ANM_CUTREL)) {
        return true;
    }

    if (frameCtrl.checkPass(4.0f) && m34D0 != 0) {
        if (mFanSwingCb.getEmitter() != NULL) {
            mFanSwingCb.deleteCallBack();
        }
        mDoMtx_multVecZero(mpCLModel->getAnmMtx(0), &local_6c);
        dComIfGp_particle_setP1(dPa_name::ID_COMMON_004A, &local_6c, &shape_angle, NULL, 0xff, &mFanSwingCb, -1);
    }

    if (frameCtrl.getFrame() < 22.0f) {
        cLib_addCalc(
            &mVelocity,
            0.0f,
            daPy_HIO_move_c0::m.field_0x24,
            daPy_HIO_move_c0::m.field_0x1C,
            daPy_HIO_move_c0::m.field_0x20
        );
    } else if (mProcVar0.m3570 == 0) {
        if (m34D0 != 0) {
            if (!checkHeavyStateOn() &&
                (!mAcch.ChkGroundHit() || checkNoResetFlg0(daPy_FLG0(daPyFlg0_UNK80000000 | daPyFlg0_UNK20000000)) ||
                 !dComIfG_Bgsp()->ChkPolySafe(mAcch.m_gnd) || !dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd)))
            {
                mVelocity = 10.0f;
                current.angle.y = shape_angle.y + 0x8000;
                if (mCurrAttributeCode == dBgS_Attr_ICE_e) {
                    m36A0.x += 10.0f * cM_ssin(current.angle.y);
                    m36A0.z += 10.0f * cM_scos(current.angle.y);
                }
            }
            m3534 = 10;
            m353A = 3;
            local_60.set(current.pos.x, current.pos.y + 70.0f, current.pos.z);
            m3536 = shape_angle.y;
            if (mpAttnActorLockOn == NULL) {
                m3538 = 0;
            } else {
                local_54 = mpAttnActorLockOn->eyePos - current.pos;
                m3538 = cM_atan2s(-local_54.y, local_54.absXZ());
            }
            mpYuchw00Brk->setFrame(0.0f);
            m33E8.end();
            m33E8.makeEmitter(dPa_name::ID_COMMON_0032, mpYuchw00Model->getAnmMtx(2), &local_60, NULL);
            pJVar5 = m33E8.getEmitter();
            if (pJVar5 != NULL) {
                pJVar5->setGlobalPrmColor(tevStr.mColorC0.r, tevStr.mColorC0.g, tevStr.mColorC0.b);
            }
            mFanWindCps.SetStartEnd(current.pos, local_60);
            seStartOnlyReverb(JA_SE_LK_FAN_SWING);
            local_48.set(
                current.pos.x + 100.0f * cM_ssin(shape_angle.y),
                current.pos.y + 50.0f,
                current.pos.z + 100.0f * cM_scos(shape_angle.y)
            );
            mGndChk.SetPos(&local_48);
            local_48.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
            if (local_48.y >= current.pos.y - 50.0f) {
                int attrib_code = dComIfG_Bgsp()->GetAttributeCode(mGndChk);
                if (!strcmp(dComIfGp_getStartStageName(), "Adanmae")) {
                    dComIfGp_particle_setP1(dPa_name::ID_SCENE_8236, &local_48, &shape_angle);
                }
                dPa_control_c::mSmokeEcallback.onWindOff();
                int iStack_84;
                pJVar5 = dComIfGp_particle_setSimpleLand(
                    attrib_code, &local_48, NULL, 1.0f, 1.0f, 1.0f, &tevStr, &iStack_84, 0x17
                );
                dPa_control_c::mSmokeEcallback.offWindOff();
                if (pJVar5) {
                    csXyz local_80;
                    local_80.y = shape_angle.y + 0x8000;
                    local_80.x = getGroundAngle(&(mGndChk), local_80.y);
                    local_80.z = getGroundAngle(&(mGndChk), local_80.y + -0x4000);
                    mDoMtx_stack_c::transS(local_48);
                    mDoMtx_stack_c::ZXYrotM(local_80.x, local_80.y, local_80.z);
                    pJVar5->setGlobalRTMatrix(mDoMtx_stack_c::get());
                    pJVar5->setSpread(0.45f);
                    if (attrib_code == dBgS_Attr_GRASS_e) {
                        pJVar5->setRate(100.0f);
                    } else {
                        pJVar5->setRate(50.0f);
                    }
                }
            }
            local_3c.set(current.pos.x, current.pos.y + 50.0f, current.pos.z);
            dKyw_squal_set(&local_3c, 1000, shape_angle.y, 280.0f, 1000.0f, 1.0f, 140.0f, 0.08f);
        } else {
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        voiceStart(1);
        mProcVar0.m3570 = 1;
    } else if (cLib_addCalc(&mVelocity, 0.0f, 0.5f, 1.5f, 0.3f) < 0.5f) {
        resetFootEffect();
    }

    m35EC = frameCtrl.getFrame();
    if (frameCtrl.getRate() < 0.01f) {
        mVelocity = 0.0f;
        checkNextMode(0);
    }

    return true;
}

/* 8014CA1C-8014CB94       .text procFanGlide_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procFanGlide_init(int param_0) {
    f32 fVar1;

    commonProcInit(daPyProc_FAN_GLIDE_e);
    deleteEquipItem(FALSE);
    if (param_0 != 0) {
        fVar1 = daPy_HIO_fan_c0::m.field_0x24;
    } else {
        fVar1 = daPy_HIO_fan_c0::m.field_0x28;
    }
    setSingleMoveAnime(
        ANM_USEFANB, daPy_HIO_fan_c0::m.field_0x20, fVar1, daPy_HIO_fan_c0::m.field_0x4, daPy_HIO_fan_c0::m.field_0x2C
    );
    mEquipItem = daPyItem_UNK102_e;
    setParachuteFanModel(fVar1);
    m3600 = 0.0f;
    m3604 = 0.0f;
    m34D0 = 0;
    m34D4 = 0;
    m34D6 = 0;
    m34D8 = 0;
    mProcVar0.m3570 = 0;
    m34DA = 0;
    m3730 = cXyz::Zero;
    voiceStart(5);
    seStartOnlyReverb(JA_SE_LK_FAN_CHUTE_OPEN);
    m3574 = daPy_HIO_fan_c0::m.field_0x8;
    if (!checkHeavyStateOn()) {
        dComIfGp_setItemMagicCount(-1);
    }
    dComIfGp_setPlayerStatus1(0, daPyStts1_DEKU_LEAF_FLY_e);
    m34D2 = daPy_HIO_fan_c0::m.field_0xA;
    return true;
}

/* 8014CB94-8014D778       .text procFanGlide__9daPy_lk_cFv */
BOOL daPy_lk_c::procFanGlide() {
    cXyz local_60;
    cXyz local_54;
    cXyz local_48;
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];

    if ((int)m34D2 != 0) {
        m34D2--;
    }
    if (frameCtrl.checkPass(4.0f)) {
        JPABaseEmitter* emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_004B, &current.pos);
        if (emitter) {
            emitter->setGlobalRTMatrix(mpCLModel->getAnmMtx(0xf));
        }
    }
    if (frameCtrl.getRate() < 0.01f && mProcVar0.m3570 == 0 && m32E4.getEmitter() == NULL) {
        m32E4.makeEmitter(dPa_name::ID_COMMON_004C, mpCLModel->getAnmMtx(0xf), &current.pos, NULL);
    }

    if (frameCtrl.getFrame() > 2.0f || mProcVar0.m3570 != 0) {
        if (mAcch.ChkGroundHit()) {
            if (checkHeavyStateOn()) {
                return changeLandProc(daPy_HIO_fan_c0::m.field_0x50);
            } else {
                return procLand_init(daPy_HIO_fan_c0::m.field_0x50, 1);
            }
        } else if (checkJumpFlower() || checkJumpRideShip()) {
            return true;
        }

        if (m3280.getEmitter() != NULL) {
            if ((int)m34DA == 0) {
                seStartOnlyReverb(JA_SE_LK_FAN_CHUTE_WATER);
                m34DA = 6;
            } else {
                m34DA--;
            }
        }

        if (m34D0 <= 0) {
            if (!checkHeavyStateOn()) {
                maxFallSpeed = daPy_HIO_fan_c0::m.field_0x38;
                if (m34D0 == 0) {
                    speed.y = daPy_HIO_fan_c0::m.field_0x40;
                    mVelocity = daPy_HIO_fan_c0::m.field_0x48;
                } else {
                    speed.y = daPy_HIO_fan_c0::m.field_0x44;
                }
            }
            m34D0 = 1;
        } else {
            if (!dComIfGp_event_runCheck()) {
                m3574--;
                if (m3574 == 0 && dComIfGs_getMagic() >= 1) {
                    dComIfGp_setItemMagicCount(-1);
                    m3574 = daPy_HIO_fan_c0::m.field_0x8;
                }
            }
            if (m34D2 == 0) {
                dComIfGp_setDoStatus(dActStts_CANCEL_e);
            }
            if ((m34D2 == 0 && (doTrigger() || cancelTrigger())) || (dComIfGs_getMagic() < 1 && m3574 == 0)) {
                m3688 = current.pos;
                m35F0 = m3688.y;
                seStartOnlyReverb(JA_SE_LK_FAN_CHUTE_CLOSE);
                if (swordTrigger()) {
                    setAnimeEquipSword(0);
                }
                return procFall_init(2, daPy_HIO_wallCatch_c0::m.field_0x54);
            }
            if (speed.y < -gravity && !checkHeavyStateOn()) {
                gravity = daPy_HIO_fan_c0::m.field_0x3C;
                maxFallSpeed = daPy_HIO_fan_c0::m.field_0x38;
            }
            if (checkSetItemTrigger(dItem_DEKU_LEAF_e, 1) && frameCtrl.getRate() < 0.01f && mProcVar0.m3570 == 0) {
                setSingleMoveAnime(
                    ANM_USEFANB,
                    daPy_HIO_fan_c0::m.field_0x20,
                    daPy_HIO_fan_c0::m.field_0x28,
                    daPy_HIO_fan_c0::m.field_0x4,
                    daPy_HIO_fan_c0::m.field_0x2C
                );
                mpParachuteFanMorf->setAnm(
                    getItemAnimeResource(LKANM_BCK_FANBA),
                    0,
                    daPy_HIO_fan_c0::m.field_0x2C,
                    daPy_HIO_fan_c0::m.field_0x20,
                    daPy_HIO_fan_c0::m.field_0x28,
                    daPy_HIO_fan_c0::m.field_0x4,
                    NULL
                );
                gravity = daPy_HIO_autoJump_c0::m.field_0xC;
                voiceStart(5);
                seStartOnlyReverb(JA_SE_LK_FAN_CHUTE_RISE);
                m353A = 5;
            }
            if (mAcch.ChkWallHit()) {
                dBgS_AcchCir* pdVar11 = &mAcchCir[0];
                for (int i = 0; i < 3; i++, pdVar11++) {
                    if (pdVar11->ChkWallHit() &&
                        (cLib_distanceAngleS(current.angle.y, pdVar11->GetWallAngleY()) > 0x6000))
                    {
                        mVelocity *= -1.0f;
                        break;
                    }
                }
            }
            if (checkHeavyStateOn()) {
                cLib_chaseF(&mVelocity, 0.0f, (0.1f * daPy_HIO_autoJump_c0::m.field_0x3C));
            }

            f32 local_64;
            dKyw_get_AllWind_vec(&mHeadTopPos, &local_60, &local_64);
            int uVar6 = m34E8 - shape_angle.y;
            cLib_addCalc(
                &mVelocity,
                (daPy_HIO_fan_c0::m.field_0x48 * mStickDistance) * cM_scos(uVar6),
                0.5f,
                (0.1f + 0.4f * mStickDistance),
                0.01f
            );
            cLib_addCalcAngleS(&m34D4, (512.0f * mStickDistance) * cM_ssin(uVar6), 5, 0x40, 8);

            f32 dVar13;
            if (mWindCyl.ChkTgHit()) {
                local_54 = *mWindCyl.GetTgRVecP();
                dVar13 = local_54.abs();
                if (dVar13 > 50.0f) {
                    local_54 *= (50.0f / dVar13);
                }
                f32 fVar1 = 1.0f;
                dVar13 = 20.0f;
                local_64 = 1.0f;
                if (mProcVar0.m3570 == 0) {
                    mProcVar0.m3570 = 1;
                    setSingleMoveAnime(ANM_USEFANB2, fVar1, 0.0f, -1, daPy_HIO_fan_c0::m.field_0x30);
                    mpParachuteFanMorf->setAnm(
                        getItemAnimeResource(LKANM_BCK_FANB2A),
                        0,
                        daPy_HIO_fan_c0::m.field_0x30,
                        1.0f,
                        0.0f,
                        -1.0f,
                        NULL
                    );
                }
            } else {
                local_64 *= 1.5f;
                if (local_64 >= 1.0f) {
                    local_64 = 1.0f;
                }
                local_54.x = local_64 * daPy_HIO_fan_c0::m.field_0x4C * local_60.x;
                local_54.y = 0.5f * local_64 * local_60.y;
                local_54.z = local_64 * daPy_HIO_fan_c0::m.field_0x4C * local_60.z;
                dVar13 = 3.0f;
                if (mProcVar0.m3570 != 0) {
                    mProcVar0.m3570 = 0;
                    setSingleMoveAnime(
                        ANM_USEFANB,
                        daPy_HIO_fan_c0::m.field_0x20,
                        daPy_HIO_fan_c0::m.field_0x4 - 0.001f,
                        daPy_HIO_fan_c0::m.field_0x4,
                        daPy_HIO_fan_c0::m.field_0x34
                    );
                    mpParachuteFanMorf->setAnm(
                        getItemAnimeResource(LKANM_BCK_FANBA),
                        0,
                        daPy_HIO_fan_c0::m.field_0x34,
                        daPy_HIO_fan_c0::m.field_0x20,
                        daPy_HIO_fan_c0::m.field_0x4 - 0.001f,
                        daPy_HIO_fan_c0::m.field_0x4,
                        NULL
                    );
                }
            }

            cLib_addCalc(&m3730.x, local_54.x, 0.5f, dVar13, 1.0f);
            cLib_addCalc(&m3730.y, local_54.y, 0.5f, dVar13, 1.0f);
            cLib_addCalc(&m3730.z, local_54.z, 0.5f, dVar13, 1.0f);
            current.pos += m3730;
            shape_angle.y = shape_angle.y + m34D4;
            current.angle.y = shape_angle.y;
            f32 sin = cM_ssin(shape_angle.y);
            f32 cos = cM_scos(shape_angle.y);
            local_48.set(m3730.x * cos - m3730.z * sin, m3730.y, m3730.x * sin + m3730.z * cos);

            f32 mult = 1.0f / 50.0f;
            f32 f4 = -local_48.x * mult;
            f32 f3 = local_48.z * mult;

            if (f4 > 1.0f) {
                f4 = 1.0f;
            } else if (f4 < -1.0f) {
                f4 = -1.0f;
            }
            if (f3 > 1.0f) {
                f3 = 1.0f;
            } else if (f3 < -1.0f) {
                f3 = -1.0f;
            }

            int r0 = m34D4 * -8;
            s16 r30 = (r0 + (f4 * 0x1800));
            s16 prev = m34F2;
            s16 r4 = 0x1800 * (f3 + (mVelocity * mult));
            cLib_addCalcAngleS(&m34F2, r4, 5, 0x800, 0x100);
            m34E0 = m34E0 + m34D6;
            m34E0 -= (s16)(m34F2 - prev);
            m34D6 += ((s16)(m34F2 - prev) >> 1);
            if (m34D6 > 0x380) {
                m34D6 = 0x380;
            } else if (m34D6 < -0x380) {
                m34D6 = -0x380;
            }
            cLib_addCalcAngleS(&m34E0, 0, 5, 0x80, 0x30);
            cLib_addCalcAngleS(&m34D6, 0, 5, 0x50, 0x30);
            if (m34E0 > 0x2000) {
                m34E0 = 0x2000;
            } else if (m34E0 < -0x2000) {
                m34E0 = -0x2000;
            }
            prev = m34F4;
            cLib_addCalcAngleS(&m34F4, r30, 5, 0x800, 0x100);
            m34E4 += m34D8;
            m34E4 = m34E4 - (s16)(prev - m34F4);
            m34D8 = m34D8 + (s16)(prev - m34F4);
            if (m34D8 > 0x380) {
                m34D8 = 0x380;
            } else if (m34D8 < -0x380) {
                m34D8 = -0x380;
            }
            cLib_addCalcAngleS(&m34E4, 0, 5, 0x80, 0x30);
            cLib_addCalcAngleS(&m34D8, 0, 5, 0x50, 0x30);
            if (m34E4 > 0x2000) {
                m34E4 = 0x2000;
            } else if (m34E4 < -0x2000) {
                m34E4 = -0x2000;
            }
            local_64 *= 0.75f;
            m3600 = (((1.5f + local_64) + cM_rndFX(0.3f)) * cM_ssin(m355C));
            m355E = ((600.0f + cM_rndFX(100.0f)) * cM_ssin(m355C));
            m355C += (6000.0f + (2000.0f * local_64)) + ((12000.0f + (3000.0f * local_64)) * cM_rnd());
        }
    }
    return true;
}
