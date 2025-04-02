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
    if (m3570 != 0) {
        f32 fVar1 = 1.5f;
        f32 fVar2 = 0.5f;
        return (mStickDistance * fVar1) + fVar2;
    }
    return daPy_HIO_crouch_c0::m.field_0x34 +
           (mStickDistance * (daPy_HIO_crouch_c0::m.field_0x30 - daPy_HIO_crouch_c0::m.field_0x34));
}

/* 801387EC-80138868       .text getCrawlMoveSpeed__9daPy_lk_cFv */
f32 daPy_lk_c::getCrawlMoveSpeed() {
    /* Nonmatching - floats */
    float fVar1;

    fVar1 = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if (fVar1 >= 17.0f) {
        fVar1 = fVar1 - 17.0f;
    }
    return (daPy_HIO_crouch_c0::m.field_0x3C * mFrameCtrlUnder[UNDER_MOVE0_e].getRate()) *
           cM_ssin(cM_rad2s(0.18479957f * fVar1));
}

/* 80138868-801389D0       .text setCrawlMoveDirectionArrow__9daPy_lk_cFv */
void daPy_lk_c::setCrawlMoveDirectionArrow() {
    u8 direction = 0;
    camera_class* cam = dComIfGp_getCamera(mCameraInfoIdx);
    BOOL bVar = cLib_distanceAngleS(fopCamM_GetAngleY(cam), shape_angle.y) > 0x4000;
    if (m3570 & 4) {
        if (!bVar) {
            direction |= 1;
        } else {
            direction |= 4;
        }
    }
    if (m3570 & 8) {
        if (!bVar) {
            direction |= 4;
        } else {
            direction |= 1;
        }
    }
    if (m3570 & 1) {
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
void daPy_lk_c::changeCrawlAutoMoveProc(cXyz*) {
    /* Nonmatching */
}

/* 80138D50-80138F28       .text getCrawlMoveVec__9daPy_lk_cFP4cXyzP4cXyzP4cXyz */
int daPy_lk_c::getCrawlMoveVec(cXyz* param_0, cXyz* param_1, cXyz* param_2) {
    /* Nonmatching - floats */
    mLinkLinChk.Set(param_0, param_1, this);
    if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
        cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
        int iVar4 = dComIfG_Bgsp()->GetSpecialCode(mLinkLinChk);
        float fVar1 = triPla->GetNP()->y;
        bool bVar2;
        if (!((fVar1 >= 0.5f) || (fVar1 < -0.8f))) {
            bVar2 = true;
        } else {
            bVar2 = false;
        }
        if (bVar2) {
            cXyz local_3c = (*param_1 - mLinkLinChk.GetCross());
            float dVar7 = local_3c.absXZ();
            param_2->x = (float)(-dVar7 * triPla->GetNP()->x);
            param_2->y = local_3c.y;
            param_2->z = (float)(-dVar7 * triPla->GetNP()->z);
            return true;
        } else if ((iVar4 == 1) || (fVar1 < 0.643832f && (iVar4 == 2))) {
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

    cMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_top_offset, &cStack_50);
    iVar1 = getCrawlMoveVec(&cStack_50, param_0, &cStack_44);
    cMtx_multVec(mpCLModel->getBaseTRMtx(), &l_crawl_top_up_offset, &cStack_50);
    iVar2 = getCrawlMoveVec(&cStack_50, param_1, &cStack_38);
    if ((iVar1 != 0) && (iVar2 != 0)) {
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
BOOL daPy_lk_c::checkCrawlSideWall(cXyz*, cXyz*, cXyz*, cXyz*, s16*, s16*) {
    /* Nonmatching */
}

/* 801392BC-80139424       .text setDoStatusCrawl__9daPy_lk_cFv */
void daPy_lk_c::setDoStatusCrawl() {
    /* Nonmatching */
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
    cMtx_multVec(mpCLModel->getBaseTRMtx(), &local_20, &afStack_2c);
    local_20.y = 50.0f;
    cMtx_multVec(mpCLModel->getBaseTRMtx(), &local_20, &cStack_38);
    crawlBgCheck(&cStack_38, &cStack_38);
    if ((!spActionButton()) || (m35D0 > 15.0f + current.pos.y)) {
        procCrawlEnd_init(0, shape_angle.x, shape_angle.z);
    } else if ((mStickDistance > 0.05f) &&
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
    /* Nonmatching - floats */
    mRoofChk.SetPos(*param_0);
    return dComIfG_Bgsp()->RoofChk(&mRoofChk) - current.pos.y <= 125.0f;
}

/* 801396B0-80139760       .text checkNotCrawlStand__9daPy_lk_cFP4cXyzP4cXyz */
BOOL daPy_lk_c::checkNotCrawlStand(cXyz* param_0, cXyz* param_1) {
    cXyz local_2c = (*param_0 + *param_1);
    if (checkNotCrawlStand(&local_2c)) {
        return true;
    }
    local_2c = (*param_0 - *param_1);
    if (checkNotCrawlStand(&local_2c)) {
        return true;
    }
    return false;
}

/* 80139760-80139878       .text procCrawlMove_init__9daPy_lk_cFss */
BOOL daPy_lk_c::procCrawlMove_init(s16 param_0, s16 param_1) {
    BOOL var_r29;
    BOOL var_r28 = 0;

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
        if (getDirectionFromShapeAngle() == 1) {
            dVar4 *= -1.0f;
        }
        current.angle.y = shape_angle.y;
        setSingleMoveAnime(ANM_LIEFORWARD, (float)dVar4, 0.0f, -1, daPy_HIO_crouch_c0::m.field_0x38);
    } else {
        onResetFlg0(daPyRFlg0_UNK1000);
    }
    m35A0 = -1.0f;
    m3570 = var_r29 ^ 1;
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
    /* Nonmatching */
}

/* 8013A004-8013A0F0       .text procCrawlAutoMove_init__9daPy_lk_cFiP4cXyz */
BOOL daPy_lk_c::procCrawlAutoMove_init(int param_0, cXyz* param_1) {
    /* Nonmatching - floats, extrwi
    at beginning of function. */
    BOOL uVar1 = dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK2000_e);
    commonProcInit(daPyProc_CRAWL_AUTO_MOVE_e);
    m370C = *param_1;
    m35E4 = 1.0f;
    m3570 = param_0;
    m34D0 = 0x14;
    m34D6 = 300;
    dComIfGp_setPlayerStatus0(0, daPyStts0_CRAWL_e);
    setCrawlMoveDirectionArrow();
    mVelocity = 0.0f;
    onResetFlg0(daPyRFlg0_UNK1000);
    for (int i = 0; i < 3; i++) {
        mAcchCir[i].SetWallR(9.99f);
    }
    if (uVar1 != 0) {
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK2000_e);
    }
    return true;
}

/* 8013A0F0-8013A630       .text procCrawlAutoMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrawlAutoMove() {
    /* Nonmatching */
}

/* 8013A630-8013A7C4       .text procCrawlEnd_init__9daPy_lk_cFiss */
BOOL daPy_lk_c::procCrawlEnd_init(int, s16, s16) {
    /* Nonmatching */
}

/* 8013A7C4-8013A85C       .text procCrawlEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procCrawlEnd() {
    m35E4 = m35A0 * (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() - daPy_HIO_crouch_c0::m.field_0x48);
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() > -0.01f) {
        checkNextMode(0);
    } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() < daPy_HIO_crouch_c0::m.field_0x48) {
            if (!checkNextMode(1)) {
                m34C2 = 1;
            }
        } else {
            m34C2 = 1;
        }
    }
    return true;
}
