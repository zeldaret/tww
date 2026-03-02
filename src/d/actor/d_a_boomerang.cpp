/**
 * d_a_boomerang.cpp
 * Item - Boomerang
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_boomerang.h"
#include "d/d_camera.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_material.h"
#include "d/actor/d_a_player_main.h"
#include "d/res/res_link.h"
#include "dolphin/gf/GF.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_camera_mng.h"
#include "m_Do/m_Do_lib.h"

static cXyz l_blur_top(40.0f, 0.0f, 0.0f);
static cXyz l_blur_root(-40.0f, 0.0f, 0.0f);

/* 800E0C08-800E0D44       .text initBlur__18daBoomerang_blur_cFPA4_fs */
void daBoomerang_blur_c::initBlur(MtxP mtx, s16 yRot) {
    cMtx_multVec(mtx, &l_blur_top, &trail0_vtxArr0[0]);
    cMtx_multVec(mtx, &l_blur_root, &trail0_vtxArr1[0]);
    trail0_vtxArr0[1] = trail0_vtxArr0[0];
    trail0_vtxArr1[1] = trail0_vtxArr1[0];

    numTrailSegments = 0;

    pos.x = mtx[0][3];
    pos.y = mtx[1][3];
    pos.z = mtx[2][3];

    mDoMtx_stack_c::copy(mtx);
    mDoMtx_stack_c::YrotM(-(yRot * 2));
    mDoMtx_stack_c::multVec(&l_blur_top, &trail1_vtxArr0[0]);
    mDoMtx_stack_c::multVec(&l_blur_root, &trail1_vtxArr1[0]);
    trail1_vtxArr0[1] = trail1_vtxArr0[0];
    trail1_vtxArr1[1] = trail1_vtxArr1[0];
}

/* 800E0D44-800E101C       .text copyBlur__18daBoomerang_blur_cFPA4_fs */
void daBoomerang_blur_c::copyBlur(MtxP mtx, s16 yRot) {
    for (int i = 54; i >= 0; i--) {
        trail0_vtxArr0[SEGMENTS_PER_STEP + i] = trail0_vtxArr0[i];
        trail0_vtxArr1[SEGMENTS_PER_STEP + i] = trail0_vtxArr1[i];
        trail1_vtxArr0[SEGMENTS_PER_STEP + i] = trail1_vtxArr0[i];
        trail1_vtxArr1[SEGMENTS_PER_STEP + i] = trail1_vtxArr1[i];
    }

    float t = 0.0f;

    cXyz inPos;
    inPos.x = mtx[0][3];
    inPos.y = mtx[1][3];
    inPos.z = mtx[2][3];

    cXyz diff = pos - inPos;

    pos = inPos;

    mDoMtx_stack_c::push();

    int i;
    for (i = 0; i < SEGMENTS_PER_STEP; i++) {
        mDoMtx_stack_c::multVec(&l_blur_top, &trail0_vtxArr0[i]);
        mDoMtx_stack_c::multVec(&l_blur_root, &trail0_vtxArr1[i]);
        VECAdd(&trail0_vtxArr0[i], &(diff * t), &trail0_vtxArr0[i]);
        VECAdd(&trail0_vtxArr1[i], &(diff * t), &trail0_vtxArr1[i]);
        t += 1.0f / SEGMENTS_PER_STEP;
        mDoMtx_stack_c::YrotM(0x633);
    }

    t = 0.0f;

    mDoMtx_stack_c::pop();

    mDoMtx_stack_c::YrotM(-(yRot * 2));

    for (i = 0; i < SEGMENTS_PER_STEP; i++) {
        // FIXME: i is in the wrong register.
        mDoMtx_stack_c::multVec(&l_blur_top, &trail1_vtxArr0[i]);
        mDoMtx_stack_c::multVec(&l_blur_root, &trail1_vtxArr1[i]);
        VECAdd(&trail1_vtxArr0[i], &(diff * t), &trail1_vtxArr0[i]);
        VECAdd(&trail1_vtxArr1[i], &(diff * t), &trail1_vtxArr1[i]);
        t += 1.0f / SEGMENTS_PER_STEP;
        mDoMtx_stack_c::YrotM(-0x633);
    }

    numTrailSegments += SEGMENTS_PER_STEP;

    if (numTrailSegments >= 59) {
        numTrailSegments = 58;
    }
}

/* 800E101C-800E13A4       .text draw__18daBoomerang_blur_cFv */
void daBoomerang_blur_c::draw() {
    /* Nonmatching */

#include "assets/l_matDL__draw__18daBoomerang_blur_cFv.h"

    static GXVtxDescList l_vtxDescList[] = {
        {GX_VA_POS, GX_DIRECT},
        {GX_VA_TEX0, GX_DIRECT},
        {GX_VA_NULL, GX_NONE},
    };

    static GXVtxAttrFmtList l_vtxAttrFmtList[] = {
        {GX_VA_POS, GX_POS_XYZ, GX_F32, 0x00},
        {GX_VA_TEX0, GX_TEX_ST, GX_S16, 0x08},
        {GX_VA_NULL, GX_POS_XYZ, GX_F32, 0x00},
    };

    static GXTexObj texObj;

    j3dSys.reinitGX();

    GXSetNumIndStages(0);
    GXInitTexObj(&texObj, imageData, 16, 4, GX_TF_I4, GX_CLAMP, GX_CLAMP, FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, FALSE, FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    GXCallDisplayList(l_matDL, 0x80);

    // Light yellow color for the trail.
    static GXColor color0 = {0xFF, 0xFF, 0x7B, 0x96};
    GFSetTevColor(GX_TEVREG0, color0);

    const s32 uCoordStep = 0xFF / ((numTrailSegments >> 1) + 1);
    s16 uCoord1 = uCoordStep;
    s16 uCoord0 = 0;

    GFSetVtxDescv(l_vtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_vtxAttrFmtList);

    GFLoadPosMtxImm(j3dSys.getViewMtx(), GX_PNMTX0);

#define QUAD_VTX(xyz, u, v)                                                                                                                                    \
    GFPosition3f32((xyz).x, (xyz).y, (xyz).z);                                                                                                                 \
    GFTexCoord2s16((u), (v))

    {
        GFBegin(GX_QUADS, GX_VTXFMT0, numTrailSegments * 4 + 4);

        for (int i = numTrailSegments; i >= 0; i--) {
            QUAD_VTX(trail0_vtxArr0[i], uCoord1, 0x00);
            QUAD_VTX(trail0_vtxArr1[i], uCoord1, 0xFF);
            QUAD_VTX(trail0_vtxArr1[i + 1], uCoord0, 0xFF);
            QUAD_VTX(trail0_vtxArr0[i + 1], uCoord0, 0x00);

            uCoord0 = uCoord1;
            uCoord1 += uCoordStep;
        }

        GFEnd();
    }

    {
        uCoord1 = uCoordStep;
        uCoord0 = 0;

        GFBegin(GX_QUADS, GX_VTXFMT0, numTrailSegments * 4 + 4);

        for (int i = numTrailSegments; i >= 0; i--) {
            QUAD_VTX(trail1_vtxArr0[i], uCoord1, 0x00);
            QUAD_VTX(trail1_vtxArr1[i], uCoord1, 0xFF);
            QUAD_VTX(trail1_vtxArr1[i + 1], uCoord0, 0xFF);
            QUAD_VTX(trail1_vtxArr0[i + 1], uCoord0, 0x00);

            uCoord0 = uCoord1;
            uCoord1 += uCoordStep;
        }

        GFEnd();
    }

#if VERSION > VERSION_JPN
    J3DShape::resetVcdVatCache();
#endif
}

#include "assets/l_sightMatDL.h"
#include "assets/l_sightDL__d_a_boomerang.h"

/* 800E13A4-800E14F0       .text draw__25daBoomerang_sightPacket_cFv */
void daBoomerang_sightPacket_c::draw() {
    static GXVtxDescList l_vtxDescList[] = {
        {GX_VA_POS, GX_DIRECT},
        {GX_VA_TEX0, GX_DIRECT},
        {GX_VA_NULL, GX_NONE},
    };

    static GXVtxAttrFmtList l_vtxAttrFmtList[] = {
        {GX_VA_POS, GX_POS_XYZ, GX_S8, 0x00},
        {GX_VA_TEX0, GX_TEX_ST, GX_U8, 0x00},
        {GX_VA_NULL, GX_POS_XYZ, GX_F32, 0x00},
    };

    GXTexObj texObj;

    const GXBool mipmap = mImage->mipmapCount > 1 ? TRUE : FALSE;
    GXInitTexObj(&texObj, mTex, mImage->width, mImage->height, GXTexFmt(mImage->format), GXTexWrapMode(mImage->wrapS), GXTexWrapMode(mImage->wrapT), mipmap);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, FALSE, FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    GXCallDisplayList(l_sightMatDL, 0x60);
    GFSetVtxDescv(l_vtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_vtxAttrFmtList);

    GXColor color0 = {0xFF, 0xFF, 0x32, 0xFF};
    GXColor color1 = {0xFF, 0xFF, 0x32, 0xFF};

    for (int i = 0; i < BOOM_TARGET_MAX; i++) {
        if (mSightOnFlg & (1 << i)) {
            color0.a = mScaleArr[i];
            color1.a = mScaleArr[i];
            GFSetTevColor(GX_TEVREG0, color0);
            GFSetTevColor(GX_TEVREG1, color1);
            GFLoadPosMtxImm(mMtxArr[i], GX_PNMTX0);
            GXCallDisplayList(l_sightDL, 0x20);
        }
    }
}

/* 800E14F0-800E1718       .text setSight__25daBoomerang_sightPacket_cFP4cXyzi */
void daBoomerang_sightPacket_c::setSight(cXyz* pPos, int n) {
    if (pPos != NULL) {
        s32 animFrame = mFrameArr[n];
        f32 pingPongAnim;
        f32 imageRot;
        if (animFrame < (u32)HALF_ANIM_LENGTH) {
            pingPongAnim = 1.0f - animFrame / (f32)HALF_ANIM_LENGTH;
            imageRot = -pingPongAnim;
        } else {
            pingPongAnim = (animFrame - HALF_ANIM_LENGTH) / (f32)HALF_ANIM_LENGTH;
            imageRot = pingPongAnim;
        }
        mScaleArr[n] = pingPongAnim * 30.0f + 150.0f;

        f32 scale = (pingPongAnim * 35.0f + 65.0f) * 0.01f;
        f32 scaleX = scale * mImage->width;
        f32 scaleY = scale * mImage->height;

        cXyz proj;
        mDoLib_project(pPos, &proj);
        mDoMtx_stack_c::transS(proj);
        mDoMtx_stack_c::scaleM(scaleX, scaleY, scale);

        mDoMtx_stack_c::ZrotM(cM_ssin(imageRot * 16384.0f) * 32768.0f);
        MTXCopy(mDoMtx_stack_c::get(), mMtxArr[n]);

        mSightOnFlg |= 1 << n;
    } else {
        mSightOnFlg &= ~(1 << n);
    }
}

/* 800E1718-800E1754       .text play__25daBoomerang_sightPacket_cFi */
void daBoomerang_sightPacket_c::play(int n) {
    u8* p = &mFrameArr[0];
    for (int i = 0; i < n; i++) {
        *p = *p + 1;
        if (*p == ANIM_LENGTH) {
            *p = 0;
        }
        p++;
    }
}

/* 800E1754-800E1998       .text draw__13daBoomerang_cFv */
BOOL daBoomerang_c::draw() {
    g_dComIfG_gameInfo.drawlist.setOpaListP1();
    g_dComIfG_gameInfo.drawlist.setXluListP1();

    if (!mThirdPerson && mNumTargets != 0) {
        mSightPacket.resetSightOn();
        for (int i = mCurTargetIdx; i < mNumTargets; i++) {
            fopAc_ac_c* pActor = mTargetPtrs[i];
            if (pActor) {
                mSightPacket.setSight(&pActor->eyePos, i);
            } else {
                mSightPacket.setSight(NULL, i);
            }
        }

        dComIfGd_set2DXlu(&mSightPacket);
    }

    if (mBlur.numTrailSegments > 0) {
        dComIfGd_entryZSortXluList(&mBlur, current.pos);
    }

    if (daPy_getPlayerActorClass()->checkPlayerNoDraw() && fpcM_GetParam(this) == 0) {
        g_dComIfG_gameInfo.drawlist.setOpaList();
        g_dComIfG_gameInfo.drawlist.setXluList();
        return TRUE;
    }

    dKy_getEnvlight().settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    dKy_getEnvlight().setLightTevColorType(mpModel, &tevStr);

    if (fpcM_GetParam(this) == 0 && daPy_getPlayerLinkActorClass()->checkFreezeState()) {
        dMat_control_c::iceUpdateDL(mpModel, -1, NULL);
    } else {
        mDoExt_modelUpdateDL(mpModel);
    }

    g_dComIfG_gameInfo.drawlist.setOpaList();
    g_dComIfG_gameInfo.drawlist.setXluList();

    if (mGroundY != -G_CM3D_F_INF && fpcM_GetParam(this) == 1) {
        cXyz* pFloorNrm = dComIfG_Bgsp()->GetTriPla(mGndChk)->GetNP();
        if (pFloorNrm) {
            dComIfGd_setSimpleShadow(&current.pos, mGroundY, 30.0f, pFloorNrm);
        }
    }

    return TRUE;
}

/* 800E1998-800E19B8       .text daBoomerang_Draw__FP13daBoomerang_c */
static BOOL daBoomerang_Draw(daBoomerang_c* i_this) {
    return ((daBoomerang_c*)i_this)->draw();
}

/* 800E19B8-800E1A14       .text getFlyMax__13daBoomerang_cFv */
float daBoomerang_c::getFlyMax() {
    if (dComIfGp_checkPlayerStatus0(0, 0x10000) != 0) {
        return 5000.0f;
    }

    if (strcmp(dComIfGp_getStartStageName(), "GanonK") != 0) {
        return 2500.0f;
    }

    return 5000.0f;
}

/* 800E1A14-800E1AAC       .text rockLineCallback__13daBoomerang_cFP10fopAc_ac_c */
void daBoomerang_c::rockLineCallback(fopAc_ac_c* pHitActor) {
    if (fpcM_GetParam(this) == 0) {
        if (pHitActor) {
            setLockActor(pHitActor, TRUE);
        }
    } else {
        for (int i = 0; i < BOOM_TARGET_MAX; i++) {
            if (mTargetPtrs[i] == pHitActor) {
                mTargetIds[i] = -1;
                mTargetPtrs[i] = NULL;
                if (i == mCurTargetIdx) {
                    field_0xF2E = true;
                    mCurTargetIdx++;
                }
            }
        }
    }
}

/* 800E1AAC-800E1AD0       .text daBoomerang_rockLineCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daBoomerang_rockLineCallback(fopAc_ac_c* i_actor, dCcD_GObjInf*, fopAc_ac_c* i_hit, dCcD_GObjInf*) {
    ((daBoomerang_c*)i_actor)->rockLineCallback(i_hit);
}

/* 800E1AD0-800E1B20       .text setAimActor__13daBoomerang_cFP10fopAc_ac_c */
void daBoomerang_c::setAimActor(fopAc_ac_c* param_1) {
    resetLockActor();
    mThirdPerson = true;
    setLockActor(param_1, FALSE);
}

/* 800E1B20-800E1C20       .text setLockActor__13daBoomerang_cFP10fopAc_ac_ci */
BOOL daBoomerang_c::setLockActor(fopAc_ac_c* i_actor, BOOL doSoundEffect) {
    if (mNumTargets >= BOOM_TARGET_MAX) {
        return FALSE;
    }

    fpc_ProcID id = fopAcM_GetID(i_actor);

    for (int i = 0; i < mNumTargets; i++) {
        if (mTargetIds[i] == id) {
            return FALSE;
        }
    }

    mTargetIds[mNumTargets] = id;
    mTargetPtrs[mNumTargets] = i_actor;
    mSightPacket.initFrame(mNumTargets);

    if (doSoundEffect) {
        static const u32 se_flg[BOOM_TARGET_MAX] = {
            JA_SE_BOOM_LOCK_ON_1,
            JA_SE_BOOM_LOCK_ON_2,
            JA_SE_BOOM_LOCK_ON_3,
            JA_SE_BOOM_LOCK_ON_4,
            JA_SE_BOOM_LOCK_ON_5,
        };

        mDoAud_seStart(se_flg[mNumTargets]);
    }

    mNumTargets++;
    return TRUE;
}

/* 800E1C20-800E1C58       .text resetLockActor__13daBoomerang_cFv */
void daBoomerang_c::resetLockActor() {
    for (int i = 0; i < BOOM_TARGET_MAX; i++) {
        mTargetIds[i] = fpcM_ERROR_PROCESS_ID_e;
        mTargetPtrs[i] = NULL;
    }

    mNumTargets = 0;
    mCurTargetIdx = 0;
}

/* 800E1C58-800E1CFC       .text setRoomInfo__13daBoomerang_cFv */
void daBoomerang_c::setRoomInfo() {
    mGndChk.SetPos(&current.pos);

    f32 groundY = dComIfG_Bgsp()->GroundCross(&mGndChk);
    s32 roomNo;
    if (groundY != -G_CM3D_F_INF) {
        roomNo = dComIfG_Bgsp()->GetRoomId(mGndChk);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mGndChk);
    } else {
        roomNo = dComIfGp_roomControl_getStayNo();
    }

    tevStr.mRoomNo = roomNo;
    mStts.SetRoomId(roomNo);
    current.roomNo = roomNo;
}

/* 800E1CFC-800E1DA8       .text setKeepMatrix__13daBoomerang_cFv */
void daBoomerang_c::setKeepMatrix() {
    // Transform the boomerang to Link's hand.
    mDoMtx_stack_c::copy(daPy_getPlayerActorClass()->getLeftHandMatrix());
    mDoMtx_stack_c::transM(10.3f, 36.6f, 1.1f);
    mDoMtx_stack_c::XYZrotM(-0x39f4, -0x357, -0x2af3);
    MtxP mtx = mDoMtx_stack_c::get();
    mpModel->setBaseTRMtx(mtx);
    current.pos.set(mtx[0][3], mtx[1][3], mtx[2][3]);
}

/* 800E1DA8-800E1E6C       .text setAimPos__13daBoomerang_cFv */
void daBoomerang_c::setAimPos() {
    if (mIsReturning) {
        mTargetPos = daPy_getPlayerLinkActorClass()->getBoomerangCatchPos();
    } else {
        for (int i = mCurTargetIdx; i < mNumTargets; i++) {
            if (mTargetPtrs[i] != NULL) {
                mTargetPos = mTargetPtrs[i]->eyePos;
                return;
            }
            mCurTargetIdx++;
        }
    }
}

/* 800E1E6C-800E1F94       .text checkBgHit__13daBoomerang_cFP4cXyzP4cXyz */
void daBoomerang_c::checkBgHit(cXyz* pi_start, cXyz* pi_end) {
    mLinChk.Set(pi_start, pi_end, this);
    if (dComIfG_Bgsp()->LineCross(&mLinChk)) {
        current.pos.set(mLinChk.GetCross());
        g_dComIfG_gameInfo.play.getParticle()->setNormalP1(0xC, &current.pos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);
        mIsReturning = true;
        current.angle.y += 0x8000;
        shape_angle.y = current.angle.y;
        resetLockActor();
        u32 mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mLinChk);
        s8 reverb = dComIfGp_getReverb(current.roomNo);
        mDoAud_seStart(JA_SE_LK_W_WEP_HIT, &eyePos, mtrlSndId, reverb);
    }
}

/* 800E1F94-800E239C       .text procWait__13daBoomerang_cFv */
BOOL daBoomerang_c::procWait() {
    daPy_lk_c* pPlayer = daPy_getPlayerLinkActorClass();
    speedF = 0.0f;
    setKeepMatrix();

    if (mBlur.numTrailSegments > 0) {
        mBlur.numTrailSegments -= 5;
    }

    if (fpcM_GetParam(this) == 1) {
        speedF = 60.0f;
        mCps.ResetAtHit();
        mCps.OffAtNoTgHitInfSet();
        mIsReturning = false;
        field_0xF2D = true;
        field_0xF2E = false;
        mCurTargetIdx = 0;

        setAimPos();

        if (mCurTargetIdx == mNumTargets) {
            resetLockActor();

            s16 angleY = pPlayer->getBodyAngleY() + pPlayer->shape_angle.y;
            s16 angleX = pPlayer->getBodyAngleX();

            f32 flyMax = getFlyMax();

            mTargetPos.set(
                current.pos.x + flyMax * cM_ssin(angleY) * cM_scos(angleX),
                current.pos.y - flyMax * cM_ssin(angleX),
                current.pos.z + flyMax * cM_scos(angleY) * cM_scos(angleX)
            );
        }

        mModelRotY = 0;

        cXyz diff = mTargetPos - current.pos;

        s16 angle = cM_atan2s(-diff.y, diff.absXZ());
        current.angle.x = angle;
        if (mNumTargets == 0) {
            current.angle.y = cM_atan2s(diff.x, diff.z) + 0x3000;
            if (mThirdPerson) {
                mFreeFlyOut = false;
            } else {
                mFreeFlyOut = true;
            }
        } else {
            current.angle.y = cM_atan2s(diff.x, diff.z);
            mFreeFlyOut = false;
        }

        shape_angle.x = current.angle.x;
        shape_angle.y = current.angle.y;
        shape_angle.z = 0x2000;
        mModelRotZ = 0x2000;

        mCurrProcFunc = &daBoomerang_c::procMove;

        mCancelFlg = false;

        mBlur.initBlur(mpModel->getBaseTRMtx(), mModelRotY);

        cXyz bgHitPos(pPlayer->current.pos.x, pPlayer->current.pos.y + 60.0f, pPlayer->current.pos.z);
        checkBgHit(&bgHitPos, &current.pos);

        procMove();
    } else {
        if (dCam_getBody()->mCurMode != 0xB) {
            resetLockActor();
        } else {
            bool b = false;
            if ((pPlayer->mCurProc == daPy_lk_c::daPyProc_BOOMERANG_SUBJECT_e || pPlayer->mCurProc == daPy_lk_c::daPyProc_SHIP_BOOMERANG_e) &&
                pPlayer->mSightPacket.getDrawFlg())
            {
                b = true;
            }

            if (b) {
                camera_class* pCamera = g_dComIfG_gameInfo.play.getCamera(g_dComIfG_gameInfo.play.getPlayerCameraID(0));
                cXyz eyePos = *fopCamM_GetEye_p(pCamera);
                cXyz topPos = pPlayer->getLineTopPos();
                mCps.OnAtNoTgHitInfSet();
                mCps.cM3dGCps::Set(eyePos, topPos, 3.0f);

                mCps.CalcAtVec();
                mCps.SetAtHitCallback(&daBoomerang_rockLineCallback);

                dComIfG_Ccsp()->Set(&mCps);
            }
        }
    }

    return TRUE;
}

/* 800E239C-800E2AF4       .text procMove__13daBoomerang_cFv */
BOOL daBoomerang_c::procMove() {
    static cXyz at_offset; // Never used.

    if (mCatchAndDelete) {
        fopAcM_delete(this);
        return TRUE;
    }

    if (dComIfGp_event_getMode() == 0) {
        daPy_lk_c* pPlayer = daPy_getPlayerLinkActorClass();
        s16 s = mModelRotY;
        mModelRotY -= 0x1F00;
        if (s >= 0 && mModelRotY < 0) {
            mDoAud_seStart(JA_SE_LK_BOOM_FLY, &eyePos, 0, dComIfGp_getReverb(current.roomNo));
        }
        setAimPos();

        cXyz diff = mTargetPos - current.pos;
        f32 dist = diff.abs();
        cXyz norm;
        if (dist > 0.1f) {
            norm = diff / dist;
        } else {
            norm = diff;
        }

        s16 angle = cM_atan2s(norm.x, norm.z);
        s16 currentAngle = angle - current.angle.y;

        if (field_0xF2E) {
            field_0xF2E = false;
            if (s16(angle - current.angle.y) > 0) {
                current.angle.y = angle - 0x3000;
            } else {
                current.angle.y = angle + 0x3000;
            }
            currentAngle = angle - current.angle.y;
        }

        if (mIsReturning) {
            if (dist < speedF * 2.0f) {
                if (pPlayer->returnBoomerang()) {
                    fpcM_SetParam(this, 0);
                    mThirdPerson = false;
                    mCurrProcFunc = &daBoomerang_c::procWait;
                    mCps.SetAtHitCallback(NULL);
                } else {
                    mCatchAndDelete = true;
                }
            }
        } else {
            if (dist < speedF || mCps.ChkAtHit() && mCps.GetAtHitAc() == mTargetPtrs[mCurTargetIdx]) {
                // Boomerang hit its current target.
                field_0xF2E = true;
                mTargetPtrs[mCurTargetIdx] = NULL;
                mTargetIds[mCurTargetIdx] = fpcM_ERROR_PROCESS_ID_e;
                mCurTargetIdx++;
                mFreeFlyOut = false;
            }
        }

        if (!mIsReturning && (mCancelFlg || (!mFreeFlyOut && mNumTargets <= mCurTargetIdx) || mCps.ChkAtShieldHit())) {
            // Boomerang should return. It either was canceled, hit its last target, or hit a shield.
            field_0xF2E = true;
            mIsReturning = true;
            resetLockActor();
            mCancelFlg = false;
            mFreeFlyOut = false;
        }

        if (field_0xF2E) {
            current.angle.y = angle;
        } else {
            s16 newAngle;
            if (!mThirdPerson) {
                f32 a = 20.0f - dist * 2.0f / speedF;
                if (a < 0.0f) {
                    a = 0.0f;
                } else if (a > 18.0f) {
                    a = 20.0f + 40.0f * (a - 18.0f);
                }
                newAngle = a * 256.0f + 1024.0f;
            } else {
                newAngle = 0x4000;
            }

            if (currentAngle > newAngle) {
                currentAngle = newAngle;
            } else if (currentAngle < -newAngle) {
                currentAngle = -newAngle;
            }
            current.angle.y += currentAngle;
        }

        angle = cM_atan2s(-norm.y, norm.absXZ());
        current.angle.x = angle;

        current.pos.x += speedF * cM_scos(current.angle.x) * cM_ssin(current.angle.y);
        current.pos.y -= speedF * cM_ssin(current.angle.x);
        current.pos.z += speedF * cM_scos(current.angle.x) * cM_scos(current.angle.y);

        shape_angle.y = current.angle.y;
        shape_angle.x = current.angle.x;

        if (!mIsReturning) {
            checkBgHit(&old.pos, &current.pos);
        }

        currentAngle = -(currentAngle * 2);

        if (currentAngle > 0x100) {
            currentAngle = 0x2000;
        } else if (currentAngle < -0x100) {
            currentAngle = -0x2000;
        } else {
            currentAngle = mModelRotZ;
        }

        mModelRotZ = currentAngle;
        cLib_addCalcAngleS(&shape_angle.z, currentAngle, 0x10, 0x1000, 0x10);
    }

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mDoMtx_stack_c::YrotM(mModelRotY);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mCps.cM3dGCps::Set(old.pos, current.pos, 30.0f);
    mCps.CalcAtVec();

    if (dComIfGp_event_getMode() == 0) {
        mBlur.copyBlur(mDoMtx_stack_c::get(), mModelRotY);
        dComIfG_Ccsp()->Set(&mCps);
        dComIfG_Ccsp()->SetMass(&mCps, 1);
    } else {
        mBlur.copyBlur(mDoMtx_stack_c::get(), 0);
        mCps.ResetAtHit();
    }

    mInWater = daPy_lk_c::setItemWaterEffect(this, mInWater, TRUE);

    return TRUE;
}

/* 800E2AF4-800E2BD0       .text execute__13daBoomerang_cFv */
BOOL daBoomerang_c::execute() {
    for (int i = 0; i < mNumTargets; i++) {
        mTargetPtrs[i] = fopAcM_SearchByID(mTargetIds[i]);
    }

    if (mCurrProcFunc) {
        (this->*mCurrProcFunc)();
    }

    attention_info.position = current.pos;
    eyePos = current.pos;

    setRoomInfo();
    mSightPacket.play(mNumTargets);

    return TRUE;
}

/* 800E2BD0-800E2BF0       .text daBoomerang_Execute__FP13daBoomerang_c */
static BOOL daBoomerang_Execute(daBoomerang_c* i_this) {
    return ((daBoomerang_c*)i_this)->execute();
}

/* 800E2BF0-800E2BF8       .text daBoomerang_IsDelete__FP13daBoomerang_c */
static BOOL daBoomerang_IsDelete(daBoomerang_c*) {
    return TRUE;
}

/* 800E2BF8-800E2C00       .text daBoomerang_Delete__FP13daBoomerang_c */
static BOOL daBoomerang_Delete(daBoomerang_c*) {
    return TRUE;
}

/* 800E2C00-800E2CC8       .text createHeap__13daBoomerang_cFv */
BOOL daBoomerang_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Link", LINK_BDL_BOOMERANG);
    JUT_ASSERT(1546, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x37220202);
    if (mpModel == NULL)
        return FALSE;
    return TRUE;
}

/* 800E2CC8-800E2CE8       .text daBoomerang_createHeap__FP10fopAc_ac_c */
static BOOL daBoomerang_createHeap(fopAc_ac_c* i_this) {
    return static_cast<daBoomerang_c*>(i_this)->createHeap();
}

static dCcD_SrcCps l_at_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_BOOMERANG,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e | cCcD_AtSPrm_NoTgHitInfSet_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ dCcG_SE_UNK4,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_Unk1_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 3.0f,
    }},
};

/* 800E2CE8-800E2EF0       .text create__13daBoomerang_cFv */
cPhs_State daBoomerang_c::create() {
    fopAcM_SetupActor(this, daBoomerang_c);

    if (!fopAcM_entrySolidHeap(this, daBoomerang_createHeap, 0xD40)) {
        return cPhs_ERROR_e;
    }

    setKeepMatrix();
    cullMtx = mpModel->getBaseTRMtx();
    mCurrProcFunc = &daBoomerang_c::procWait;
    mStts.Init(0x3C, 0xFF, this);

    mCps.Set(l_at_cps_src);
    mCps.SetStts(&mStts);
    mCps.SetAtHitCallback(&daBoomerang_rockLineCallback);

    mLinChk.ClrSttsRoofOff();

    for (int i = 0; i < BOOM_TARGET_MAX; i++) {
        mTargetIds[i] = fpcM_ERROR_PROCESS_ID_e;
    }

    {
        ResTIMG* tmp_img = (ResTIMG*)dComIfG_getObjectRes("Link", LINK_BTI_BLUR);
        JUT_ASSERT(1629, tmp_img != NULL);
        mBlur.imageData = (u8*)tmp_img + tmp_img->imageOffset;
    }

    {
        ResTIMG* tmp_img = (ResTIMG*)dComIfG_getObjectRes("Link", LINK_BTI_ROCK_MARK);
        JUT_ASSERT(1637, tmp_img != NULL);
        mSightPacket.setTex((u8*)tmp_img + tmp_img->imageOffset);
        mSightPacket.setImage(tmp_img);
    }

    setRoomInfo();
    model = mpModel;

    return cPhs_COMPLEATE_e;
}

/* 800E2EF0-800E329C       .text __ct__13daBoomerang_cFv */
daBoomerang_c::daBoomerang_c() {
}

/* 800E33F0-800E3410       .text daBoomerang_Create__FP10fopAc_ac_c */
static cPhs_State daBoomerang_Create(fopAc_ac_c* i_this) {
    return ((daBoomerang_c*)i_this)->create();
}

static actor_method_class l_daBoomerang_Method = {
    (process_method_func)daBoomerang_Create,
    (process_method_func)daBoomerang_Delete,
    (process_method_func)daBoomerang_Execute,
    (process_method_func)daBoomerang_IsDelete,
    (process_method_func)daBoomerang_Draw,
};

actor_process_profile_definition g_profile_BOOMERANG = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BOOMERANG,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBoomerang_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BOOMERANG,
    /* Actor SubMtd */ &l_daBoomerang_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
