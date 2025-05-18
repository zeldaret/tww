/**
 * d_a_player_crawl.inc
 *
 * Code relating to crawling.
 *
 * This file is not a standalone translation unit and is instead directly
 * included into d_a_player_main.cpp.
 *
 * The original name of this file is not known, but a best guess was taken
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_main_data.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_camera_mng.h"

/* 801387A4-801387EC       .text getCrawlMoveAnmSpeed__9daPy_lk_cFv */
f32 daPy_lk_c::getCrawlMoveAnmSpeed() {
    if (mProcVar0.m3570 != 0) {
        f32 fVar1 = 1.5f;
        f32 fVar2 = 0.5f;
        return (mStickDistance * fVar1) + fVar2;
    }
    return daPy_HIO_crouch_c0::m.field_0x34 +
           (mStickDistance * (daPy_HIO_crouch_c0::m.field_0x30 - daPy_HIO_crouch_c0::m.field_0x34));
}

/* 801387EC-80138868       .text getCrawlMoveSpeed__9daPy_lk_cFv */
f32 daPy_lk_c::getCrawlMoveSpeed() {
    float fVar1;

    fVar1 = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if (fVar1 >= 17.0f) {
        fVar1 = fVar1 - 17.0f;
    }
    return (daPy_HIO_crouch_c0::m.field_0x3C * mFrameCtrlUnder[UNDER_MOVE0_e].getRate()) * cM_fsin((M_PI / 17) * fVar1);
}

/* 80138868-801389D0       .text setCrawlMoveDirectionArrow__9daPy_lk_cFv */
void daPy_lk_c::setCrawlMoveDirectionArrow() {
    u8 direction = 0;
    camera_class* cam = dComIfGp_getCamera(mCameraInfoIdx);
    BOOL bVar = cLib_distanceAngleS(fopCamM_GetAngleY(cam), shape_angle.y) > 0x4000;
    if (mProcVar0.m3570 & 4) {
        if (!bVar) {
            direction |= 1;
        } else {
            direction |= 4;
        }
    }
    if (mProcVar0.m3570 & 8) {
        if (!bVar) {
            direction |= 4;
        } else {
            direction |= 1;
        }
    }
    if (mProcVar0.m3570 & 1) {
        if (shape_angle.y == current.angle.y) {
            if (!bVar) {
                direction |= 8;
            } else {
                direction |= 2;
            }
        } else if (!bVar) {
            direction |= 2;
        } else {
            direction |= 8;
        }
    }
    if (shape_angle.y == current.angle.y) {
        if (!bVar) {
            direction |= 2;
        } else {
            direction |= 8;
        }
    } else if (!bVar) {
        direction |= 8;
    } else {
        direction |= 2;
    }
    dComIfGp_setAdvanceDirection(direction);
}

/* 801389D0-80138D50       .text changeCrawlAutoMoveProc__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::changeCrawlAutoMoveProc(cXyz* param_1) {
    cXyz sp70;
    cXyz sp64;
    cXyz sp58;
    cXyz sp4C;
    cXyz sp40;
    cXyz sp34;
    cXyz sp28;
    f32 spC;
    s16 spA;
    s16 sp8;
    f32 temp_f31 = cM_ssin(current.angle.y);
    f32 temp_f30 = cM_scos(current.angle.y);
    f32 temp_f29 = cM_ssin(shape_angle.y);
    f32 temp_f28 = cM_scos(shape_angle.y);
    int var_r29 = 0;

    sp70.x = param_1->x + (75.0f * temp_f31);
    sp70.y = param_1->y;
    sp70.z = param_1->z + (75.0f * temp_f30);
    mLinkLinChk.Set(param_1, &sp70, (fopAc_ac_c*)this);
    if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        sp4C.x = sp70.x + (50.0f * temp_f30);
        sp4C.y = sp70.y;
        sp4C.z = sp70.z - (50.0f * temp_f31);

        if (checkCrawlSideWall(&sp70, &sp4C, &sp34, &sp28, &spA, &sp8)) {
            var_r29 |= 1;
        } else {
            return false;
        }
    }
    sp4C.x = param_1->x + (50.0f * temp_f28);
    sp4C.y = param_1->y;
    sp4C.z = param_1->z - (50.0f * temp_f29);

    sp40 = (*param_1 * 2.0f) - sp4C;
    mLinkLinChk.Set(param_1, &sp4C, (fopAc_ac_c*)this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        var_r29 |= 8;
        sp58.x = sp40.x + (75.0f * temp_f29);
        sp58.y = sp40.y;
        sp58.z = sp40.z + (75.0f * temp_f28);
        if (!checkCrawlSideWall(&sp40, &sp58, &sp34, &sp28, &spA, &sp8)) {
            return false;
        }
    } else {
        var_r29 |= 4;
        sp58.x = sp4C.x - (75.0f * temp_f29);
        sp58.y = sp4C.y;
        sp58.z = sp4C.z - (75.0f * temp_f28);
        if (!checkCrawlSideWall(&sp4C, &sp58, &sp34, &sp28, &spA, &sp8)) {
            return false;
        }
        mLinkLinChk.Set(param_1, &sp40, (fopAc_ac_c*)this);
        if (!dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
            var_r29 |= 8;
        }
    }
    if (cM3d_Len2dSqPntAndSegLine(
            0.5f * (sp34.x + sp28.x),
            0.5f * (sp34.z + sp28.z),
            sp70.x,
            sp70.z,
            param_1->x - (75.0f * temp_f31),
            param_1->z - (75.0f * temp_f30),
            &sp64.x,
            &sp64.z,
            &spC
        ))
    {
        sp64.y = current.pos.y;
        return procCrawlAutoMove_init(var_r29, &sp64);
    }
    return false;
}

/* 80138D50-80138F28       .text getCrawlMoveVec__9daPy_lk_cFP4cXyzP4cXyzP4cXyz */
int daPy_lk_c::getCrawlMoveVec(cXyz* param_0, cXyz* param_1, cXyz* param_2) {
    mLinkLinChk.Set(param_0, param_1, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
        int iVar4 = dComIfG_Bgsp()->GetSpecialCode(mLinkLinChk);
        if (cBgW_CheckBWall(triPla->GetNP()->y)) {
            cXyz local_3c = (*param_1 - mLinkLinChk.GetCross());
            f32 dVar7 = local_3c.absXZ();
            param_2->x = -dVar7 * triPla->GetNP()->x;
            param_2->y = local_3c.y;
            param_2->z = -dVar7 * triPla->GetNP()->z;
            return true;
        } else if (iVar4 == 1 || (triPla->GetNP()->y < 0.643832f && iVar4 == 2)) {
            *param_2 = (*param_1 - mLinkLinChk.GetCross());
            return true;
        }
    }
    return false;
}

/* 80138F28-801390B8       .text crawlBgCheck__9daPy_lk_cFP4cXyzP4cXyz */
void daPy_lk_c::crawlBgCheck(cXyz* param_0, cXyz* param_1) {
    int iVar1;
    int iVar2;
    cXyz cStack_50;
    cXyz cStack_44;
    cXyz cStack_38;

    mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_top_offset, &cStack_50);
    iVar1 = getCrawlMoveVec(&cStack_50, param_0, &cStack_44);
    mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_top_up_offset, &cStack_50);
    iVar2 = getCrawlMoveVec(&cStack_50, param_1, &cStack_38);
    if (iVar1 != 0 && iVar2 != 0) {
        if (cStack_44.abs2() > cStack_38.abs()) {
            current.pos -= cStack_44;
        } else {
            current.pos -= cStack_38;
        }
    } else if (iVar1 != 0) {
        current.pos -= cStack_44;
    } else if (iVar2 != 0) {
        current.pos -= cStack_38;
    }
}

/* 801390B8-801392BC       .text checkCrawlSideWall__9daPy_lk_cFP4cXyzP4cXyzP4cXyzP4cXyzPsPs */
BOOL daPy_lk_c::checkCrawlSideWall(
    cXyz* param_1, cXyz* param_2, cXyz* param_3, cXyz* param_4, s16* param_5, s16* param_6
) {
    cXyz local_78;
    cXyz local_90;

    mLinkLinChk.Set(param_1, param_2, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        *param_3 = mLinkLinChk.GetCross();
        cM3dGPla* pfVar1 = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
        *param_5 = cM_atan2s(pfVar1->GetNP()->x, pfVar1->GetNP()->z);
        local_90 = *param_3 + (pfVar1->mNormal * 75.0f);
        local_78 = (local_90 + *param_3) * 0.5f;
        mLinkLinChk.Set(&local_78, &local_90, this);
        if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
            *param_4 = mLinkLinChk.GetCross();
            pfVar1 = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
            *param_6 = cM_atan2s(pfVar1->GetNP()->x, pfVar1->GetNP()->z);
            cXyz local_9c = *param_3 - *param_4;
            f32 temp_f31 = local_9c.abs2XZ();
            if (cLib_distanceAngleS(*param_5, *param_6) > 0x7F00 && temp_f31 < 5625.0f && temp_f31 > 3600.0f) {
                return true;
            }
        }
    }
    return false;
}

/* 801392BC-80139424       .text setDoStatusCrawl__9daPy_lk_cFv */
void daPy_lk_c::setDoStatusCrawl() {
    dComIfGp_setRStatus(dActStts_CROUCH_e);
    if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x80)) {
        dComIfGp_setAStatus(dActStts_RETURN_e);
        if (checkSubjectEnd(1) || m35D0 > current.pos.y) {
            dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK2000_e);
        } else {
            dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000_e);
        }
    } else if (dCam_getBody()->ChangeModeOK(4)) {
        if (m35D0 <= current.pos.y) {
            onResetFlg0(daPyRFlg0_UNK4000000);
            if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x1000) && !dComIfGp_event_runCheck()) {
                setSubjectMode();
            }
        }
    }
    if (dComIfGp_checkCameraAttentionStatus(mCameraInfoIdx, 0x80) &&
        (mCurProc != daPyProc_CRAWL_MOVE_e || mProcVar0.m3570 == 0))
    {
        setBodyAngleToCamera();
        if (mBodyAngle.x > 0) {
            mBodyAngle.x = 0;
        }
    } else {
        mBodyAngle.x = 0;
    }
}

/* 80139424-801394F0       .text procCrawlStart_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrawlStart_init() {
    commonProcInit(daPyProc_CRAWL_START_e);
    m3700 = cXyz::Zero;
    m34C2 = 1;
    setSingleMoveAnime(
        ANM_LIE,
        daPy_HIO_crouch_c0::m.field_0x20,
        daPy_HIO_crouch_c0::m.field_0x24,
        daPy_HIO_crouch_c0::m.field_0x6,
        daPy_HIO_crouch_c0::m.field_0x2C
    );
    mVelocity = 0.0f;
    current.angle.y = shape_angle.y;
    m35A0 = 1.0f / (daPy_HIO_crouch_c0::m.field_0x28 - daPy_HIO_crouch_c0::m.field_0x24);
    m35E4 = 0.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_CRAWL_e);
    return true;
}

/* 801394F0-80139640       .text procCrawlStart__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrawlStart() {
    setDoStatusCrawl();
    m35E4 = 1.0f - m35A0 * ((daPy_HIO_crouch_c0::m.field_0x28) - mFrameCtrlUnder[UNDER_MOVE0_e].getFrame());
    cXyz local_20(l_crawl_front_offset.x, l_crawl_front_offset.y, l_crawl_front_offset.z * m35E4);
    cXyz afStack_2c;
    cXyz cStack_38;
    mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &local_20, &afStack_2c);
    local_20.y = 50.0f;
    mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &local_20, &cStack_38);
    crawlBgCheck(&cStack_38, &cStack_38);
    if (!spActionButton() || m35D0 > 15.0f + current.pos.y) {
        procCrawlEnd_init(0, shape_angle.x, shape_angle.z);
    } else if (mStickDistance > 0.05f &&
               ((mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) ||
                (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_crouch_c0::m.field_0x28)))
    {
        procCrawlMove_init(shape_angle.x, shape_angle.z);
    } else {
        m34C2 = 1;
    }
    return true;
}

/* 80139640-801396B0       .text checkNotCrawlStand__9daPy_lk_cFP4cXyz */
BOOL daPy_lk_c::checkNotCrawlStand(cXyz* param_0) {
    mRoofChk.SetPos(*param_0);
    return dComIfG_Bgsp()->RoofChk(&mRoofChk) - current.pos.y <= 125.0f;
}

/* 801396B0-80139760       .text checkNotCrawlStand__9daPy_lk_cFP4cXyzP4cXyz */
BOOL daPy_lk_c::checkNotCrawlStand(cXyz* param_0, cXyz* param_1) {
    cXyz local_2c = *param_0 + *param_1;
    if (checkNotCrawlStand(&local_2c)) {
        return true;
    }
    local_2c = *param_0 - *param_1;
    if (checkNotCrawlStand(&local_2c)) {
        return true;
    }
    return false;
}

/* 80139760-80139878       .text procCrawlMove_init__9daPy_lk_cFss */
BOOL daPy_lk_c::procCrawlMove_init(s16 param_0, s16 param_1) {
    BOOL var_r29;
    if (mCurProc == daPyProc_CRAWL_AUTO_MOVE_e) {
        var_r29 = 0;
    } else {
        var_r29 = 1;
    }
    BOOL var_r27;
    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000_e)) {
        var_r27 = 1;
    } else {
        var_r27 = 0;
    }
    commonProcInit(daPyProc_CRAWL_MOVE_e);
    if (var_r29 != 0) {
        f32 dVar4 = getCrawlMoveAnmSpeed();
        if (getDirectionFromShapeAngle() == DIR_BACKWARD) {
            dVar4 *= -1.0f;
        }
        current.angle.y = shape_angle.y;
        setSingleMoveAnime(ANM_LIEFORWARD, dVar4, 0.0f, -1, daPy_HIO_crouch_c0::m.field_0x38);
    } else {
        onResetFlg0(daPyRFlg0_UNK1000);
    }
    m35A0 = -1.0f;
    mProcVar0.m3570 = var_r29 ^ 1;
    shape_angle.x = param_0;
    shape_angle.z = param_1;
    m35E4 = 1.0f;
    dComIfGp_setPlayerStatus0(0, daPyStts0_CRAWL_e);
    if (var_r27 != 0) {
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000_e);
    }
    return true;
}

/* 80139878-8013A004       .text procCrawlMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrawlMove() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    float fVar1;
    BOOL bVar4;
    BOOL bVar5;
    int iVar6;
    int iVar7;
    int iVar8;
    int iVar9;
    f32 dVar11;
    cXyz sp124;
    cXyz sp118;
    cXyz sp10C;
    cXyz sp100;
    cXyz spF4;
    cXyz spE8;
    cXyz spDC;
    cXyz spD0;
    cXyz spC4;
    cXyz spB8;
    cXyz spAC;
    cXyz spA0;
    cXyz sp94;
    cXyz sp88;

    setDoStatusCrawl();
    mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_stand_up_offset, &sp118);
    mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_front_up_offset, &sp124);
    mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_back_up_offset, &sp10C);
    mDoMtx_multVecSR(mpCLModel->getBaseTRMtx(), &l_crawl_min_side_offset, &sp100);
    iVar6 = checkNotCrawlStand(&sp118);
    iVar7 = checkNotCrawlStand(&sp124);
    iVar8 = checkNotCrawlStand(&sp10C);
    if ((((iVar6 != 0 || iVar7 != 0) || iVar8 != 0) ||
         (checkNotCrawlStand(&sp124, &sp100) || checkNotCrawlStand(&sp10C, &sp100))) ||
        checkNotCrawlStand(&sp118, &sp100))
    {
        bVar5 = false;
        onModeFlg(ModeFlg_04000000);
    } else {
        bVar5 = true;
        offModeFlg(ModeFlg_04000000);
    }
    if ((bVar5 != false && !spActionButton()) || (getSlidePolygon() != NULL || m35D0 > current.pos.y + 15.0f)) {
        procCrawlEnd_init(1, shape_angle.x, shape_angle.z);
    } else {
        bVar4 = false;
        dVar11 = getCrawlMoveAnmSpeed();
        if (frameCtrl.getRate() > 0.0f) {
            frameCtrl.setRate(dVar11);
        } else if (frameCtrl.getRate() < 0.0f) {
            frameCtrl.setRate(-dVar11);
        } else {
            bVar4 = true;
        }
        if ((bVar4 == true || frameCtrl.checkPass(0.0f)) || frameCtrl.checkPass(17.0f)) {
            if (mStickDistance > 0.05f) {
                if (getDirectionFromShapeAngle() != 1) {
                    frameCtrl.setRate(dVar11);
                    frameCtrl.setLoop(0);
                } else {
                    frameCtrl.setRate(-dVar11);
                    frameCtrl.setLoop(frameCtrl.getEnd());
                }
                initSeAnime();
            } else if (!bVar4) {
                if (frameCtrl.checkPass(0.0f)) {
                    fVar1 = 0.0f;
                } else {
                    fVar1 = 17.0f;
                }
                frameCtrl.setRate(0.0f);
                frameCtrl.setFrame(fVar1);
                ((mAnmRatioUnder[UNDER_MOVE0_e]).getAnmTransform())->setFrame(fVar1);
            }
        }
        iVar9 = mProcVar0.m3570;
        mProcVar0.m3570 = 0;
        s16 sp0A;
        s16 sp08;

        mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_side_offset, &spE8);
        mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_top_up_offset, &spF4);

        if (frameCtrl.getRate() >= 0.0f) {
            spB8 = (sp124 - spF4) * 0.5f;
        } else if (frameCtrl.getRate() < 0.0f) {
            spB8 = (sp10C - spF4) * 0.5f;
        }

        spE8 += spB8;
        spF4 += spB8;
        spDC = (spF4 * 2.0f) - spE8;

        if (!bVar5 && (checkCrawlSideWall(&spF4, &spE8, &spD0, &spC4, &sp0A, &sp08) ||
                       checkCrawlSideWall(&spF4, &spDC, &spC4, &spD0, &sp08, &sp0A)))
        {
            mProcVar0.m3570 = 1;
            mResetFlg0 = mResetFlg0 | 0x1000;
            m370C = ((spD0 + spC4) * 0.5f) - spB8;
            m34D4 = sp0A + 0x4000;
        }

        if (mProcVar0.m3570 != 0) {
            if (frameCtrl.getRate()) {
                cLib_addCalcAngleS(&shape_angle.y, m34D4, 5, 0x1000, 0x800);
                current.angle.y = shape_angle.y;
            }

            if (std::abs(current.pos.x - m370C.x) > 1.0f) {
                cLib_addCalc(&current.pos.x, m370C.x, 0.5f, 10.0f, 1.0f);
            }

            if (std::abs(current.pos.z - m370C.z) > 1.0f) {
                cLib_addCalc(&current.pos.z, m370C.z, 0.5f, 10.0f, 1.0f);
            }
        } else {
            if (iVar9 != 0 && iVar6 != 0 && iVar7 != 0 && iVar8 != 0 && changeCrawlAutoMoveProc(&spF4)) {
                return true;
            }
            if (mStickDistance > 0.05f && (frameCtrl.getRate() > 0.0f)) {
                s16 r24 = shape_angle.y;

                cLib_addCalcAngleS(
                    &shape_angle.y,
                    m34E8,
                    daPy_HIO_crouch_c0::m.field_0x8,
                    daPy_HIO_crouch_c0::m.field_0xA,
                    daPy_HIO_crouch_c0::m.field_0xC
                );

                if (shape_angle.y != r24) {
                    if ((s16)(shape_angle.y - r24) > 0) {
                        cMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_lside_front_offset, &spAC);
                        cMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_lside_offset, &sp94);
                    } else {
                        cMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_rside_front_offset, &spAC);
                        cMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_rside_offset, &sp94);
                    }

                    mGndChk.SetPos(&spAC);
                    spA0.set(spAC.x - sp94.x, dComIfG_Bgsp()->GroundCross(&mGndChk) - sp94.y, spAC.z - sp94.z);

                    if (cLib_distanceAngleS((cM_atan2s(-spA0.y, spA0.absXZ())), shape_angle.x) > 0x800) {
                        shape_angle.y = r24;
                    }
                }
                current.angle.y = shape_angle.y;
            }
        }
        dVar11 = getCrawlMoveSpeed();
        mVelocity = dVar11;
        if (mVelocity < 0.0f) {
            mVelocity *= -1.0f;
            current.angle.y = shape_angle.y + 0x8000;
            mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_back_offset, &sp88);
            crawlBgCheck(&sp88, &sp10C);
        } else {
            mDoMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_front_offset, &sp88);
            crawlBgCheck(&sp88, &sp124);
        }
    }
    return true;
}

/* 8013A004-8013A0F0       .text procCrawlAutoMove_init__9daPy_lk_cFiP4cXyz */
BOOL daPy_lk_c::procCrawlAutoMove_init(int param_0, cXyz* param_1) {
    BOOL uVar1 = dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000_e) ? TRUE : FALSE;
    commonProcInit(daPyProc_CRAWL_AUTO_MOVE_e);
    m370C = *param_1;
    m35E4 = 1.0f;
    mProcVar0.m3570 = param_0;
    m34D0 = 0x14;
    m34D6 = 300;
    dComIfGp_setPlayerStatus0(0, daPyStts0_CRAWL_e);
    setCrawlMoveDirectionArrow();
    mVelocity = 0.0f;
    onResetFlg0(daPyRFlg0_UNK1000);
    for (int i = 0; i < 3; i++) {
        mAcchCir[i].SetWallR(9.99f);
    }
    if (uVar1) {
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000_e);
    }
    return true;
}

/* 8013A0F0-8013A630       .text procCrawlAutoMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrawlAutoMove() {
    f32 fVar2;
    f32 fVar3;

    dComIfGp_setRStatus(dActStts_CROUCH_e);
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    onResetFlg0(daPyRFlg0_UNK1000);
    s16 sVar4 = shape_angle.y;
    s16 sVar5 = current.angle.y;
    if (m34D0 > 0) {
        if (frameCtrl.checkPass(0.0f) || frameCtrl.checkPass(17.0f)) {
            fVar3 = 0.0f;
            if (frameCtrl.checkPass(0.0f)) {
                fVar2 = 0.0f;
            } else {
                fVar2 = 17.0f;
            }
            frameCtrl.setRate(0.0f);
            frameCtrl.setFrame(fVar2);
            mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform()->setFrame(fVar2);
            mVelocity = fVar3;
        } else if (std::fabsf(frameCtrl.getRate()) < 0.01f) {
            mVelocity = 0.0f;
            m34D0--;
        }
        setCrawlMoveDirectionArrow();
        setDoStatusCrawl();
        shape_angle.y = sVar4;
        current.angle.y = sVar5;
    } else if (m34D0 == 0) {
        setCrawlMoveDirectionArrow();
        if (mStickDistance > 0.05f) {
            int direction = getDirectionFromShapeAngle();
            f32 fVar2 = cM_ssin(shape_angle.y);
            f32 fVar3 = cM_scos(shape_angle.y);
            if (direction == DIR_LEFT && (mProcVar0.m3570 & 4)) {
                m370C.x += 75.0f * fVar3;
                m370C.z -= 75.0f * fVar2;
                m34D4 = current.angle.y + 0x4000;
                if (current.angle.y == shape_angle.y) {
                    m35A0 = 1.0f;
                } else {
                    m35A0 = -1.0f;
                }
                m34D0 = -1;
            } else if (direction == DIR_RIGHT && (mProcVar0.m3570 & 8)) {
                m370C.x -= 75.0f * fVar3;
                m370C.z += 75.0f * fVar2;
                m34D4 = current.angle.y + -0x4000;
                if (current.angle.y == shape_angle.y) {
                    m35A0 = 1.0f;
                } else {
                    m35A0 = -1.0f;
                }
                m34D0 = -1;
            } else if ((mProcVar0.m3570 & 1) && ((shape_angle.y == current.angle.y && direction == DIR_FORWARD) ||
                                                    (shape_angle.y != current.angle.y && direction == DIR_BACKWARD)))
            {
                m370C.x += 75.0f * cM_ssin(current.angle.y);
                m370C.z += 75.0f * cM_scos(current.angle.y);
                m34D4 = shape_angle.y;
                m35A0 = 0.0f;
                m34D0 = -1;
            } else if ((shape_angle.y == current.angle.y && direction == DIR_BACKWARD) ||
                        (shape_angle.y != current.angle.y && direction == DIR_FORWARD))
            {
                current.angle.y += 0x8000;
                m370C.x -= 75.0f * cM_ssin(current.angle.y);
                m370C.z -= 75.0f * cM_scos(current.angle.y);
                m34D4 = shape_angle.y;
                m35A0 = 0.0f;
                m34D0 = -1;
            }
            if (m34D0 == -1) {
                g_dComIfG_gameInfo.play.mDirection = 0;
                if (shape_angle.y == current.angle.y) {
                    frameCtrl.setRate(2.0f);
                    frameCtrl.setLoop(0);
                } else {
                    frameCtrl.setRate(-2.0f);
                    frameCtrl.setLoop(frameCtrl.getEnd());
                }
                initSeAnime();
            }
        } else {
            setDoStatusCrawl();
            shape_angle.y = sVar4;
            current.angle.y = sVar5;
        }
    } else {
        BOOL bVar1 = true;
        if (m34D6 > 0) {
            m34D6--;
        }
        if (std::fabsf(m35A0) > 0.5f) {
            if (cLib_addCalcAngleS(&shape_angle.y, m34D4, 5, 0x480, 0x80)) {
                bVar1 = 0;
            }
            if (m35A0 < -0.5f) {
                current.angle.y = shape_angle.y + 0x8000;
            } else {
                current.angle.y = shape_angle.y;
            }
            cLib_addCalc(&current.pos.x, m370C.x, 0.5f, 3.0f, 1.0f);
            cLib_addCalc(&current.pos.z, m370C.z, 0.5f, 3.0f, 1.0f);
        }
        cXyz local_28 = m370C - current.pos;
        if (cLib_distanceAngleS(cM_atan2s(local_28.x, local_28.z), current.angle.y) < 0x6000) {
            bVar1 = false;
        }
        mVelocity = getCrawlMoveSpeed();
        if (mVelocity < 0.0f) {
            mVelocity *= -1.0f;
            current.angle.y = shape_angle.y + 0x8000;
        }
        if (bVar1 != 0 || m34D6 == 0) {
            procCrawlMove_init(shape_angle.x, shape_angle.z);
        }
    }
    return true;
}

/* 8013A630-8013A7C4       .text procCrawlEnd_init__9daPy_lk_cFiss */
BOOL daPy_lk_c::procCrawlEnd_init(int param_1, s16 param_2, s16 param_3) {
    f32 fVar1;
    J3DAnmTransform* pJVar2;
    f32 dVar4;
    J3DTransformInfo auStack_58;

    dVar4 = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    commonProcInit(daPyProc_CRAWL_END_e);
    current.angle.y = shape_angle.y;
    m34C2 = 1;
    if (param_1 != 0) {
        fVar1 = daPy_HIO_crouch_c0::m.field_0x4C;
    } else {
        fVar1 = -1.0f;
    }
    setSingleMoveAnime(
        ANM_LIE,
        daPy_HIO_crouch_c0::m.field_0x40,
        daPy_HIO_crouch_c0::m.field_0x44,
        daPy_HIO_crouch_c0::m.field_0xE,
        fVar1
    );
    if (param_1 == 0) {
        if (daPy_HIO_crouch_c0::m.field_0x44 > dVar4) {
            dVar4 = daPy_HIO_crouch_c0::m.field_0x44;
        } else if (daPy_HIO_crouch_c0::m.field_0xE <= dVar4) {
            dVar4 = daPy_HIO_crouch_c0::m.field_0xE - 0.001f;
        }
        mFrameCtrlUnder[UNDER_MOVE0_e].setFrame(dVar4);
        mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform()->setFrame(dVar4);
    }
    pJVar2 = mAnmRatioUnder[UNDER_MOVE0_e].getAnmTransform();
    pJVar2->getTransform(0, &auStack_58);
    m3700.x = auStack_58.mTranslate.x;
    m3700.y = auStack_58.mTranslate.y;
    m3700.z = auStack_58.mTranslate.z;
    mVelocity = 0.0f;
    shape_angle.x = param_2;
    shape_angle.z = param_3;
    m35A0 = 1.0f / (daPy_HIO_crouch_c0::m.field_0xE - daPy_HIO_crouch_c0::m.field_0x48);
    return true;
}

/* 8013A7C4-8013A85C       .text procCrawlEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrawlEnd() {
    m35E4 = m35A0 * (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - daPy_HIO_crouch_c0::m.field_0x48);
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() > -0.01f) {
        checkNextMode(0);
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() < daPy_HIO_crouch_c0::m.field_0x48) {
        if (!checkNextMode(1)) {
            m34C2 = 1;
        }
    } else {
        m34C2 = 1;
    }
    return true;
}
