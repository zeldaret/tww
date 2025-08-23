/**
 * d_a_tbox.cpp
 * Treasure Chest / 宝箱 (Takarabako)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_tbox.h"
#include "d/res/res_dalways.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_particle.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_graphic.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"

#define FUNC_TYPE_NORMAL 0
#define FUNC_TYPE_SWITCH 1
#define FUNC_TYPE_ENEMIES 2
#define FUNC_TYPE_SWITCH_VISIBLE 3
#define FUNC_TYPE_SWITCH_TRANSPARENT 4
#define FUNC_TYPE_GRAVITY 5
#define FUNC_TYPE_TACT 6
#define FUNC_TYPE_EXTRA_SAVE_INFO 7
#define FUNC_TYPE_EXTRA_SAVE_INFO_SPAWN 8

extern dCcD_SrcCyl dNpc_cyl_src;

static daTbox_HIO_c l_HIO;

static daTbox_c::modelInfo l_modelInfo[] = {
    {
        DALWAYS_BDL_BOXA,
        DALWAYS_BCK_BOXOPENSHORTBOX,
        DALWAYS_BTK_BOXA,
        DALWAYS_BRK_BOXA,
        DALWAYS_DZB_BOXB_00,
        DALWAYS_DZB_BOXB_01,
    },
    {
        DALWAYS_BDL_BOXB,
        DALWAYS_BCK_BOXOPENBOX,
        DALWAYS_BTK_BOXB,
        DALWAYS_BRK_BOXB,
        DALWAYS_DZB_BOXB_00,
        DALWAYS_DZB_BOXB_01,
    },
    {
        DALWAYS_BDL_BOXC,
        DALWAYS_BCK_BOXOPENBOX,
        DALWAYS_BTK_BOXC,
        DALWAYS_BRK_BOXC,
        DALWAYS_DZB_BOXB_00,
        DALWAYS_DZB_BOXB_01,
    },
    {
        DALWAYS_BDL_BOXD,
        DALWAYS_BCK_BOXOPENBOX,
        -1,
        -1,
        DALWAYS_DZB_BOXD_00,
        DALWAYS_DZB_BOXD_01,
    }
};

/* 000000EC-00000124       .text __ct__12daTbox_HIO_cFv */
daTbox_HIO_c::daTbox_HIO_c() {
    mNo = -1;
    m06 = 0x82;
    m08 = 0xB4;
    m0A = 0x30;
    m0C = 0x1E;
}

/* 00000124-00000550       .text commonShapeSet__8daTbox_cFv */
cPhs_State daTbox_c::commonShapeSet() {
    modelInfo& mdlInfo = getModelInfo();

    // Load model
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Dalways", mdlInfo.modelId);
    JUT_ASSERT(0xA0, modelData != NULL);

    u32 modelFlags = 0x11000022;

    // Load open animation
    J3DAnmTransform* openAnm = (J3DAnmTransform*)dComIfG_getObjectRes("Dalways", mdlInfo.openBckId);
    if (mOpenAnm.init(modelData, openAnm, true, J3DFrameCtrl::EMode_NONE,  1.0f, 0, -1, false) == 0) {
        return cPhs_ERROR_e;
    }

    // Load texture anim, if requested
    if (mdlInfo.btkId > 0) {
        mpAppearTexAnm = new mDoExt_btkAnm();
        if (mpAppearTexAnm == NULL) {
            return cPhs_ERROR_e;
        }

        J3DAnmTextureSRTKey* appearTexData = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Dalways", mdlInfo.btkId);
        if (mpAppearTexAnm->init(modelData, appearTexData, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0) == 0) {
            return cPhs_ERROR_e;
        }

        modelFlags |= 0x1200;
    }

    // Load color anim, if requested
    if (mdlInfo.brkId > 0) {
        mpAppearRegAnm = new mDoExt_brkAnm();
        if (mpAppearRegAnm == NULL) {
            return cPhs_ERROR_e;
        }

        J3DAnmTevRegKey* appearRegData = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Dalways", mdlInfo.brkId);
        if (mpAppearRegAnm->init(modelData, appearRegData, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0) == 0) {
            return cPhs_ERROR_e;
        }

        modelFlags |= 0xF020000;
    }

    // Create model
    mpChestMdl = mDoExt_J3DModel__create(modelData, 0x80000, modelFlags);
    if (mpChestMdl == NULL) {
        return cPhs_ERROR_e;
    }

    // Set up Triforce platform for the type that spawns via Wind Waker song
    if (getFuncType() == FUNC_TYPE_TACT) {
        modelData = (J3DModelData*)dComIfG_getObjectRes("Dalways", DALWAYS_BDL_YTRIF00);
        JUT_ASSERT(0xE2, modelData);

        mpTactPlatformMdl = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000000);
        if (mpTactPlatformMdl == NULL) {
            return cPhs_ERROR_e;
        }

        J3DAnmTevRegKey* tactPlatformBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Dalways", DALWAYS_BRK_YTRIF00);
        if (mTactPlatformBrk.init(modelData, tactPlatformBrk, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0) == 0) {
            return cPhs_ERROR_e;
        }
    }

    mpChestMdl->setBaseScale(scale);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpChestMdl->setBaseTRMtx(mDoMtx_stack_c::get());

    if (getFuncType() == FUNC_TYPE_TACT) {
        mDoMtx_stack_c::transM(0.0f, 1.0f, 0.0f);
        mpTactPlatformMdl->setBaseTRMtx(mDoMtx_stack_c::get());
    }

    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);

    return cPhs_COMPLEATE_e;
}

/* 00000598-00000764       .text effectShapeSet__8daTbox_cFv */
cPhs_State daTbox_c::effectShapeSet() {
    J3DModelData* flashModelData = (J3DModelData*)dComIfG_getObjectRes("Dalways", DALWAYS_BDL_IT_TAKARA_FLASH);
    JUT_ASSERT(0x117, flashModelData != NULL);

    mpFlashMdl = mDoExt_J3DModel__create(flashModelData, 0x80000, 0x1000200);
    if (mpFlashMdl == NULL) {
        return cPhs_ERROR_e;
    }

    J3DAnmTransform* flashAnm = (J3DAnmTransform*)dComIfG_getObjectRes("Dalways", DALWAYS_BCK_IT_TAKARA_FLASH2);
    if (mFlashAnm.init(flashModelData, flashAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false) == 0) {
        return cPhs_ERROR_e;
    }

    J3DAnmTextureSRTKey* flashTexAnm = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Dalways", DALWAYS_BTK_IT_TAKARA_FLASH);
    if (mFlashTexAnm.init(flashModelData, flashTexAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0) == 0) {
        return cPhs_ERROR_e;
    }

    J3DAnmTevRegKey* flashRegAnm = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Dalways", DALWAYS_BRK_IT_TAKARA_FLASH);
    int regInit = mFlashRegAnm.init(flashModelData, flashRegAnm, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);

    if (regInit) {
        return cPhs_COMPLEATE_e;
    } else {
        return cPhs_ERROR_e;
    }
}

/* 00000764-00000928       .text envShapeSet__8daTbox_cFv */
cPhs_State daTbox_c::envShapeSet() {
    modelInfo& mdlInfo = getModelInfo();

    // Load model
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Dalways", mdlInfo.modelId);

    J3DTexture* mdlTex = modelData->getTexture();
    if (mdlTex == NULL) {
        return cPhs_ERROR_e;
    }

    JUTNameTab* texNameTable = modelData->getTextureName();
    if (texNameTable == NULL) {
        return cPhs_ERROR_e;
    }

    for (u16 i = 0; i < mdlTex->getNum(); i++) {
        const char* texName = texNameTable->getName(i);
        int cmpResult = strcmp(texName, "__dummy");

        if (cmpResult == 0) {
            mdlTex->setResTIMG(i, *mDoGph_gInf_c::getFrameBufferTimg());
        }
    }

    mDoExt_modelTexturePatch(modelData);

    return cPhs_COMPLEATE_e;
}

/* 00000928-00000BB0       .text bgCheckSet__8daTbox_cFv */
cPhs_State daTbox_c::bgCheckSet() {
    modelInfo& mdlInfo = getModelInfo();

    cBgD_t* bgd = (cBgD_t*)dComIfG_getObjectRes("Dalways", mdlInfo.closedColId);
    JUT_ASSERT(0x195, bgd != NULL);

    mpBgWClosed = new dBgW();
    if (mpBgWClosed == NULL) {
        return cPhs_ERROR_e;
    }

    if (mpBgWClosed->Set(bgd, cBgW::MOVE_BG_e, &mMtx) == true) {
        return cPhs_ERROR_e;
    }

    bgd = (cBgD_t*)dComIfG_getObjectRes("Dalways", mdlInfo.openColId);
    JUT_ASSERT(0x1A6, bgd != NULL);

    mpBgWOpen = new dBgW();
    if (mpBgWOpen == NULL) {
        return cPhs_ERROR_e;
    }

    if (mpBgWOpen->Set(bgd, cBgW::MOVE_BG_e, &mMtx) == true) {
        return cPhs_ERROR_e;
    }

    if (getFuncType() == FUNC_TYPE_SWITCH_VISIBLE) {
        bgd = (cBgD_t*)dComIfG_getObjectRes("Dalways", DALWAYS_DZB_KINB_00);
        JUT_ASSERT(0x1B9, bgd != NULL);

        mpBgWVines = new dBgW();
        if (mpBgWVines == NULL) {
            return cPhs_ERROR_e;
        }

        if (mpBgWVines->Set(bgd, cBgW::MOVE_BG_e, &mMtx) == true) {
            return cPhs_ERROR_e;
        }
    }

    mpBgWClosed->Move();
    mpBgWOpen->Move();

    if (mpBgWVines != NULL) {
        mpBgWVines->Move();
    }

    mpBgWCurrent = NULL;

    return cPhs_COMPLEATE_e;
}

/* 00000BB0-00000C14       .text searchRoomNo__8daTbox_cFv */
void daTbox_c::searchRoomNo() {
    if (mRoomNo == -1) {
        mRoomNo = home.angle.x & 0x3F;
    }

    if (flagCheck(daTboxFlg_UNK_02)) {
        clrDzb();
    }
    else if (mRoomNo != -1 && mpBgWCurrent == NULL) {
        setDzb();
    }
}

/* 00000C14-00000C98       .text lightReady__8daTbox_cFv */
void daTbox_c::lightReady() {
    mPLight.mPos.set(current.pos.x, current.pos.y + 55.0f, current.pos.z);
    mPLight.mColor.r = 0xFF;
    mPLight.mColor.g = 0xFF;
    mPLight.mColor.b = 0xFF;
    mPLight.mPower = 0.0f;
    mPLight.mFluctuation = 0.0f;

    mEfLight.mPos.set(current.pos.x, current.pos.y + 50.0f, current.pos.z);
    mEfLight.mColor.r = 0xFF;
    mEfLight.mColor.g = 0xFF;
    mEfLight.mColor.b = 0x64;
    mEfLight.mPower = 0.0f;
    mEfLight.mFluctuation = 0.0f;

    mAllColRatio = 0.0f;
}

/* 00000C98-00000CD8       .text checkEnv__8daTbox_cFv */
BOOL daTbox_c::checkEnv() {
    return l_modelInfo[getShapeType()].brkId <= 0 ? FALSE : TRUE;
}

/* 00000CD8-00000D48       .text checkOpen__8daTbox_cFv */
BOOL daTbox_c::checkOpen() {
    if (getFuncType() == FUNC_TYPE_EXTRA_SAVE_INFO || getFuncType() == FUNC_TYPE_EXTRA_SAVE_INFO_SPAWN) {
        int stageNo = dSv_save_c::STAGE_SEA2;
        u8 tBoxNo = getTboxNo();

        return dComIfGs_isStageTbox(stageNo, tBoxNo);
    }
    else {
        u8 tBoxNo = getTboxNo();
        return dComIfGs_isTbox(tBoxNo);
    }
}

/* 00000D48-00000D78       .text getModelInfo__8daTbox_cFv */
daTbox_c::modelInfo& daTbox_c::getModelInfo() {
    return l_modelInfo[getShapeType()];
}

/* 00000D78-00000DD0       .text clrDzb__8daTbox_cFv */
void daTbox_c::clrDzb() {
    if (mpBgWCurrent != NULL) {
        dComIfG_Bgsp()->Release(mpBgWCurrent);
        mpBgWCurrent = NULL;

        mColCyl.OffCoSetBit();
    }
}

/* 00000DD0-00000ECC       .text setDzb__8daTbox_cFv */
void daTbox_c::setDzb() {
    clrDzb();

    if (checkOpen()) {
        mpBgWCurrent = mpBgWOpen;
    }
    else {
        if (getFuncType() == FUNC_TYPE_SWITCH_VISIBLE && !dComIfGs_isSwitch(getSwNo(), mRoomNo)) {
            mpBgWCurrent = mpBgWVines;
        }
        else {
            mpBgWCurrent = mpBgWClosed;
        }
    }

    bool rt = dComIfG_Bgsp()->Regist(mpBgWCurrent, this);
    JUT_ASSERT(0x234, !rt);

    mpBgWCurrent->mRoomNo = mRoomNo;
    mColCyl.OnCoSetBit();
}

/* 00000ECC-00000F8C       .text surfaceProc__8daTbox_cFv */
void daTbox_c::surfaceProc() {
    if (mpBgWCurrent != NULL && flagCheck(daTboxFlg_APPEARING_e)) {
        if (mAppearingYOffset < -1.0f) {
            mAppearingYOffset += 1.0f;
        }
        else {
            flagOff(daTboxFlg_APPEARING_e);
            mAppearingYOffset = 0.0f;
        }

        mDoMtx_stack_c::transS(current.pos.x, current.pos.y + mAppearingYOffset, current.pos.z);
        mDoMtx_stack_c::YrotM(current.angle.y);
        mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);

        mpBgWCurrent->Move();
    }
}

/* 00000F8C-00000FC0       .text checkRoomDisp__8daTbox_cFi */
BOOL daTbox_c::checkRoomDisp(int i_roomNo) {
    if (dComIfGp_roomControl_checkStatusFlag(i_roomNo, 0x08)) {
        return FALSE;
    }

    return dComIfGp_roomControl_checkStatusFlag(i_roomNo, 0x10) ? TRUE : FALSE;
}

/* 00000FC0-00000FE4       .text getShapeType__8daTbox_cFv */
s32 daTbox_c::getShapeType() {
    s32 shapeType = (fopAcM_GetParam(this) >> 0x14) & 0x0F;
    return shapeType >= 4 ? 0 : shapeType;
}

/* 00000FE4-00000FF0       .text getFuncType__8daTbox_cFv */
s32 daTbox_c::getFuncType() {
    return fopAcM_GetParam(this) & 0x7F;
}

/* 00000FF0-0000108C       .text checkNormal__8daTbox_cFv */
BOOL daTbox_c::checkNormal() {
    s32 funcType = getFuncType();

    if (funcType == FUNC_TYPE_NORMAL || funcType == FUNC_TYPE_EXTRA_SAVE_INFO || funcType == FUNC_TYPE_SWITCH_VISIBLE || funcType == FUNC_TYPE_GRAVITY) {
        return TRUE;
    }

    if (mRoomNo == -1 || mRoomNo == 0x3F) {
        return FALSE;
    }

    s32 swNo = getSwNo();
    if (swNo >= 0xC0) {
        return FALSE;
    }

    if (dComIfGs_isSwitch(swNo, mRoomNo)) {
        return TRUE;
    }

    return FALSE;
}

/* 0000108C-000010AC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_actor) {
    return static_cast<daTbox_c*>(i_actor)->CreateHeap();
}

/* 000010AC-0000114C       .text CreateHeap__8daTbox_cFv */
BOOL daTbox_c::CreateHeap() {
    if (commonShapeSet() != cPhs_COMPLEATE_e) {
        return FALSE;
    }

    if (checkEnv() && envShapeSet() != cPhs_COMPLEATE_e) {
        return FALSE;
    }

    if (!checkOpen() && effectShapeSet() != cPhs_COMPLEATE_e) {
        return FALSE;
    }

    return bgCheckSet() != cPhs_COMPLEATE_e ? FALSE : TRUE;
}

/* 0000114C-00001560       .text CreateInit__8daTbox_cFv */
void daTbox_c::CreateInit() {
    s32 funcType = getFuncType();
    flagClr();

    mSmokeCB.onWindOff();
    mOpenAnm.setPlaySpeed(0.0f);

    if (checkOpen()) {
        J3DFrameCtrl* frameCtrl = mOpenAnm.getFrameCtrl();
        frameCtrl->setFrame(frameCtrl->getEnd());

        setAction(&daTbox_c::actionWait);

        if (checkEnv()) {
            mInvisibleScrollVal = 2.0f;

            frameCtrl = mpAppearRegAnm->getFrameCtrl();
            frameCtrl->setFrame(frameCtrl->getEnd());
        }
    }
    else {
        if (!checkEnv()) {
            setAction(&daTbox_c::actionOpenWait);
        }
        else {
            if (checkNormal()) {
                if (funcType == FUNC_TYPE_SWITCH_VISIBLE && !dComIfGs_isSwitch(getSwNo(), mRoomNo)) {
                    setAction(&daTbox_c::actionSwOnWait2);

                }
                else {
                    setAction(&daTbox_c::actionOpenWait);
                }

                mInvisibleScrollVal = 2.0f;

                J3DFrameCtrl* frameCtrl = mpAppearRegAnm->getFrameCtrl();
                frameCtrl->setFrame(frameCtrl->getEnd());
            }
            else {
                flagOn(daTboxFlg_UNK_04);

                switch (funcType) {
                    case FUNC_TYPE_ENEMIES:
                        setAction(&daTbox_c::actionGenocide);
                        mGenocideDelayTimer = 0x41;
                        flagOn(daTboxFlg_UNK_01 | daTboxFlg_UNK_02);
                        mAppearTimer = 0x78;
                        break;
                    case FUNC_TYPE_SWITCH:
                    case FUNC_TYPE_EXTRA_SAVE_INFO_SPAWN:
                        setAction(&daTbox_c::actionSwOnWait);
                        flagOn(daTboxFlg_UNK_01 | daTboxFlg_UNK_02);
                        mAppearTimer = 0x78;
                        break;
                    case FUNC_TYPE_TACT:
                        setAction(&daTbox_c::actionSwOnWait);
                        flagOn(daTboxFlg_UNK_01 | daTboxFlg_UNK_02);
                        mAppearTimer = l_HIO.m08;
                        break;
                    case FUNC_TYPE_SWITCH_TRANSPARENT:
                        setAction(&daTbox_c::actionSwOnWait);
                        flagOn(daTboxFlg_UNK_02);
                        mAppearTimer = 0x5A;

                        mpAppearRegAnm->setFrame(30.0f);
                        break;
                    default:
                        JUT_ASSERT(0x328, FALSE);
                        break;
                }

                mInvisibleScrollVal = -2.0f;
            }
        }
    }

    lightReady();
    mAllColRatio = 1.0f;

    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("宝箱", &l_HIO); // "Treasure Chest"
    }

    shape_angle.z = 0;
    shape_angle.x = 0;
    current.angle.z = 0;
    current.angle.x = 0;

    mColStatus.Init(0xFF, 0xFF, this);

    mColCyl.Set(dNpc_cyl_src);
    mColCyl.SetStts(&mColStatus);

    setCollision();
    mColCyl.OffCoSetBit();
    searchRoomNo();

    if (funcType == FUNC_TYPE_GRAVITY) {
        mAcchCir.SetWall(30.0f, 0.0f);
        mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this),  this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));

        gravity = -2.5f;
    }

    mTboxNo = getTboxNo();
}

/* 00001560-00001624       .text boxCheck__8daTbox_cFv */
s32 daTbox_c::boxCheck() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz playerChestDiff = player->current.pos - home.pos;

    if (playerChestDiff.abs2XZ() < SQUARE(100.0f)) {
        if (fopAcM_seenActorAngleY(this, dComIfGp_getPlayer(0)) < 0x2000 && fopAcM_seenActorAngleY(player, this) < 0x2000) {
            return TRUE;
        }
    }

    return FALSE;
}

/* 00001624-00001668       .text lightUpProc__8daTbox_cFv */
void daTbox_c::lightUpProc() {
    if (mPLight.mPower < 130.0f) {
        mPLight.mPower += 13.0f;
    }

    if (mEfLight.mPower < 120.0f) {
        mEfLight.mPower += 12.0f;
    }
}

/* 00001668-000016BC       .text lightDownProc__8daTbox_cFv */
void daTbox_c::lightDownProc() {
    if (mPLight.mPower > 5.2f) {
        mPLight.mPower -= 5.2f;
    }
    else {
        mPLight.mPower = 0.0f;
    }

    if (mEfLight.mPower > 4.8f) {
        mEfLight.mPower -= 4.8f;
    }
    else {
        mEfLight.mPower = 0.0f;
    }
}

/* 000016BC-0000172C       .text darkProc__8daTbox_cFv */
void daTbox_c::darkProc() {
    if (mOpenTimer > 0x96) {
        mAllColRatio = 1.0f;
    }
    else if (mOpenTimer > 0x78) {
        mAllColRatio = ((mOpenTimer - 0x78) / 30.0f) * 0.6f + 0.4f;
    }
}

/* 0000172C-000017CC       .text volmProc__8daTbox_cFv */
void daTbox_c::volmProc() {
    if (mOpenTimer == 0x24) {
        mSmokeEmitter->mGlobalPrmColor.a = 0xFF;
    }
    else if (mOpenTimer >= 0xB5) {
        dKy_plight_cut(&mPLight);
        dKy_efplight_cut(&mEfLight);

        mSmokeEmitter->mGlobalPrmColor.a = 0;

        mSmokeEmitter->becomeInvalidEmitter();
        mSmokeEmitter = NULL;
    }
    else if (mOpenTimer > 0x9C) {
        mSmokeEmitter->mGlobalPrmColor.a = (0xB5 - mOpenTimer) * 0x0A;
    }
}

/* 000017CC-00001890       .text demoProcOpen__8daTbox_cFv */
void daTbox_c::demoProcOpen() {
    if (mOpenTimer < 0x3E8) {
        mOpenTimer++;
    }

    if (mOpenTimer < 0x9C) {
        lightUpProc();
    }
    else {
        lightDownProc();
    }

    if (mOpenTimer == 0x24) {
        mOpenAnm.setPlaySpeed(1.0f);

        mFlashAnm.setPlaySpeed(1.0f);
        mFlashTexAnm.setPlaySpeed(1.0f);
        mFlashRegAnm.setPlaySpeed(1.0f);

        mAllColRatio = 0.4f;
        flagOn(daTboxFlg_UNK_08);
    }

    darkProc();

    if (mSmokeEmitter != NULL) {
        volmProc();
    }
}

/* 00001890-00001A40       .text demoInitAppear_Tact__8daTbox_cFv */
void daTbox_c::demoInitAppear_Tact() {
    csXyz angle;
    angle.x = current.angle.x;
    angle.y = current.angle.y;
    angle.z = current.angle.z;

    dComIfGp_particle_set(dPa_name::ID_SCENE_82F1, &current.pos, &angle);
    dComIfGp_particle_set(dPa_name::ID_SCENE_82F0, &current.pos, &angle);

    angle.y += 0x5555;
    dComIfGp_particle_set(dPa_name::ID_SCENE_82F0, &current.pos, &angle);

    angle.y += 0x5555;
    dComIfGp_particle_set(dPa_name::ID_SCENE_82F0, &current.pos, &angle);

    fopAcM_seStart(this, JA_SE_OBJ_TRIFORCE_BOX_IN, 0);
}

/* 00001A40-00001B38       .text demoInitAppear__8daTbox_cFv */
void daTbox_c::demoInitAppear() {
    fopAcM_seStart(this, JA_SE_OBJ_KOUBAKU_TBOX, 0);

    dComIfGp_particle_set(dPa_name::ID_COMMON_03EB, &current.pos);
    dComIfGp_particle_set(dPa_name::ID_COMMON_03EC, &current.pos);
}

/* 00001B38-00001CF4       .text demoProcAppear_Tact__8daTbox_cFv */
void daTbox_c::demoProcAppear_Tact() {
    if (mAppearTimer == l_HIO.m08 - l_HIO.m06) {
        flagOff(daTboxFlg_UNK_01);
        mInvisibleScrollVal = 2.0f;

        mpAppearRegAnm->setFrame(mpAppearRegAnm->getEndFrame());
        mpAppearRegAnm->play();
        flagOff(daTboxFlg_UNK_04);
    }

    mTactPlatformBrk.play();

    if (mAppearTimer != 0) {
        mAppearTimer--;

        if (mAppearTimer > l_HIO.m08 - l_HIO.m0A) {
            dKy_set_allcol_ratio((0.6f / l_HIO.m0A) * (mAppearTimer - (l_HIO.m08 - l_HIO.m0A)) + 0.4f);
        }
        else if (mAppearTimer < l_HIO.m0C) {
            dKy_set_allcol_ratio((0.6f / l_HIO.m0C) * (l_HIO.m0C - mAppearTimer) + 0.4f);
        }
        else {
            dKy_set_allcol_ratio(0.4f);
        }
    }
    else {
        dKy_set_allcol_ratio(1.0f);
        dComIfGp_evmng_cutEnd(mStaffId);
    }
}

/* 00001CF4-00001E4C       .text demoProcAppear__8daTbox_cFv */
void daTbox_c::demoProcAppear() {
    if (mAppearTimer <= 0x78 && mAppearTimer != 0) {
        cLib_chaseF(&mInvisibleScrollVal, 2.0f, 1.0f / 30.0f);
    }

    if (mAppearTimer == 0x3C) {
        mpAppearRegAnm->setFrame(150.0f);
    }

    if (mAppearTimer == 0x05) {
        JPABaseEmitter* emitter = dComIfGp_particle_setToon(dPa_name::ID_COMMON_2022, &current.pos, NULL, NULL, 0xB9, &mSmokeCB);

        if (emitter != NULL) {
            emitter->setRate(100.0f);
            emitter->setSpread(1.0f);
            emitter->setDirectionalSpeed(25.0f);
        }
    }

    if (mAppearTimer == 0x04 && mSmokeCB.getEmitter() != NULL) {
        mSmokeCB.end();
    }

    if (mAppearTimer != 0x00) {
        mAppearTimer--;
    }

    if (mpAppearRegAnm->play()) {
        dComIfGp_evmng_cutEnd(mStaffId);
        flagOff(daTboxFlg_UNK_04);
    }
}

/* 00001E4C-0000210C       .text demoProc__8daTbox_cFv */
s32 daTbox_c::demoProc() {
    static char* action_table[] = {
        "WAIT",
        "OPEN",
        "APPEAR",
        "OPEN_SHORT",
    };
    enum {
        ACT_WAIT,
        ACT_OPEN,
        ACT_APPEAR,
        ACT_OPEN_SHORT,
    };

    s32 actionIdx = dComIfGp_evmng_getMyActIdx(mStaffId, action_table, ARRAY_SIZE(action_table), FALSE, 0);
    bool bIsAdvance = dComIfGp_evmng_getIsAddvance(mStaffId);

    if (bIsAdvance) {
        mHasOpenAnmFinished = false;

        switch (actionIdx) {
            case ACT_OPEN:
                OpenInit();
                lightReady();
                mPLight.mPower = 0.0f;
                mEfLight.mPower = 0.0f;
                break;
            case ACT_APPEAR:
                flagOn(daTboxFlg_APPEARING_e);
                mAppearingYOffset = -130.0f;

                setDzb();

                if (getFuncType() == FUNC_TYPE_TACT) {
                    flagOff(daTboxFlg_UNK_02);
                    demoInitAppear_Tact();
                }
                else {
                    flagOff(daTboxFlg_UNK_01 | daTboxFlg_UNK_02);
                    demoInitAppear();
                }

                break;
            case ACT_OPEN_SHORT:
                OpenInit_com();
                break;
        }
    }

    switch (actionIdx) {
        case ACT_APPEAR:
            if (getFuncType() == FUNC_TYPE_TACT) {
                demoProcAppear_Tact();
            }
            else {
                demoProcAppear();
            }

            surfaceProc();
            break;
        case ACT_OPEN:
            if (mHasOpenAnmFinished) {
                dComIfGp_evmng_cutEnd(mStaffId);
            }
            else {
                if (mOpenAnm.play()) {
                    mHasOpenAnmFinished = true;
                    dComIfGp_evmng_cutEnd(mStaffId);
                    fopAcM_seStart(this, JA_SE_OBJ_TBOX_OPEN_S2, 0);
                }
            }
            break;
        case ACT_OPEN_SHORT:
            if (mHasOpenAnmFinished) {
                dComIfGp_evmng_cutEnd(mStaffId);
            }
            else {
                if (mOpenAnm.play()) {
                    mHasOpenAnmFinished = 1;
                    dComIfGp_evmng_cutEnd(mStaffId);
                    fopAcM_seStart(this, JA_SE_OBJ_TBOX_OPEN_S2, 0);
                }
            }
            break;
        default:
            dComIfGp_evmng_cutEnd(mStaffId);
            break;
    }

    if (flagCheck(daTboxFlg_OPENING_e)) {
        demoProcOpen();
    }

    if (flagCheck(daTboxFlg_UNK_08)) {
        dKy_set_allcol_ratio(mAllColRatio);
    }

    return 0;
}

/* 0000210C-00002250       .text OpenInit_com__8daTbox_cFv */
void daTbox_c::OpenInit_com() {
    mOpenAnm.setPlaySpeed(1.0f);

    if (getFuncType() == FUNC_TYPE_EXTRA_SAVE_INFO || getFuncType() == FUNC_TYPE_EXTRA_SAVE_INFO_SPAWN) {
        dComIfGs_onStageTbox(dSv_save_c::STAGE_SEA2, getTboxNo());
    }
    else {
        u8 tboxNo = getTboxNo();
        dComIfGs_onTbox(tboxNo);
    }

    s32 openSwNo = home.angle.z & 0xFF;
    if (openSwNo != 0xFF) {
        dComIfGs_onSwitch(openSwNo, mRoomNo);
    }

    setDzb();

    fopAcM_seStart(this, JA_SE_OBJ_TBOX_OPEN_S1, 0);
    fopAcM_seStart(this, JA_SE_OBJ_TBOX_UNLOCK, 0);
}

/* 00002250-00002444       .text OpenInit__8daTbox_cFv */
void daTbox_c::OpenInit() {
    OpenInit_com();

    mFlashAnm.setPlaySpeed(1.0f);
    mFlashTexAnm.setPlaySpeed(1.0f);
    mFlashRegAnm.setPlaySpeed(1.0f);

    mIsFlashPlaying = TRUE;
    mOpenTimer = 0;

    flagOn(daTboxFlg_OPENING_e);

    dComIfGp_particle_set(dPa_name::ID_COMMON_01F1, &current.pos, &current.angle);
    dComIfGp_particle_set(dPa_name::ID_COMMON_01F2, &current.pos, &current.angle);
    dComIfGp_particle_set(dPa_name::ID_COMMON_01F3, &current.pos, &current.angle);
    dComIfGp_particle_set(dPa_name::ID_COMMON_01F4, &current.pos, &current.angle);
    dComIfGp_particle_set(dPa_name::ID_COMMON_01F6, &current.pos, &current.angle);

    mSmokeEmitter = dComIfGp_particle_set(dPa_name::ID_COMMON_01F5, &current.pos, &current.angle);
    if (mSmokeEmitter != NULL) {
        mSmokeEmitter->mGlobalPrmColor.a = 0;
    }
}

/* 00002444-000024AC       .text setCollision__8daTbox_cFv */
void daTbox_c::setCollision() {
    mColCyl.SetC(current.pos);
    mColCyl.SetR(40.0f);
    mColCyl.SetH(110.f);

    dComIfG_Ccsp()->Set(&mColCyl);
}

/* 000024AC-000024B4       .text actionWait__8daTbox_cFv */
BOOL daTbox_c::actionWait() {
    return TRUE;
}

/* 000024B4-000025A4       .text actionDemo__8daTbox_cFv */
BOOL daTbox_c::actionDemo() {
    /* Fakematch - the temp variable for play is definitely not right. */
    s16 eventId = eventInfo.getEventId();
    dComIfG_play_c* play = &g_dComIfG_gameInfo.play;
    if (dComIfGp_evmng_endCheck(eventId)) {
    // if (dComIfGp_evmng_endCheck(eventInfo.getEventId())) {
        setAction(&daTbox_c::actionWait);

        // Fakematch:
        // When dComIfGp_event_reset is used here, the way gameInfo is loaded matches the demo
        // binary, but not the release binary. So the demo's debug map may be misleading here?
        // But daTbox_c::actionDemo in TP debug still calls dComIfGp_event_reset, so maybe not?
        // Also, putting a cast like (void) on dComIfGp_event_reset() slightly improves the
        // codegen, but it's still slightly wrong.
        // dComIfGp_event_reset();
        play->getEvent().reset();

        dKy_set_allcol_ratio(1.0f);
        flagOff(daTboxFlg_UNK_08 | daTboxFlg_OPENING_e);

        // The fakematch also might be related to dComIfGp_event_setItemPartner? Removing this
        // call fixes the load above.
        dComIfGp_event_setItemPartner(NULL);

        if (mSmokeEmitter != NULL) {
            dKy_plight_cut(&mPLight);
            dKy_efplight_cut(&mEfLight);

            mSmokeEmitter->becomeInvalidEmitter();
            mSmokeEmitter = NULL;
        }
    }
    else {
        demoProc();
    }

    return TRUE;
}

/* 000025A4-00002634       .text actionDemo2__8daTbox_cFv */
BOOL daTbox_c::actionDemo2() {
    if (dComIfGp_evmng_endCheck("DEFAULT_TREASURE_APPEAR")) {
        setAction(&daTbox_c::actionOpenWait);
        dComIfGp_event_reset();
    }
    else {
        demoProc();
    }

    return TRUE;
}

/* 00002634-000027C8       .text actionOpenWait__8daTbox_cFv */
BOOL daTbox_c::actionOpenWait() {
    if (eventInfo.checkCommandDoor()) {
        dComIfGp_event_onEventFlag(0x04);

        u8 itemNo = getItemNo();
        fpc_ProcID itemPID = fopAcM_createItemForTrBoxDemo(&current.pos, itemNo);

        if (itemPID != fpcM_ERROR_PROCESS_ID_e) {
            dComIfGp_event_setItemPartnerId(itemPID);
        }

        if (getShapeType() != 0) {
            mDoAud_subBgmStart(JA_BGM_OPEN_BOX);
            mAllColRatio = 0.4f;

            flagOn(daTboxFlg_UNK_08);
            dKy_set_allcol_ratio(mAllColRatio);

            lightReady();
            mPLight.mPower = 0.0f;
            mEfLight.mPower = 0.0f;

            dKy_plight_priority_set(&mPLight);
            dKy_efplight_set(&mEfLight);
        }

        setAction(&daTbox_c::actionDemo);

        mStaffId = dComIfGp_evmng_getMyStaffId("TREASURE");
        demoProc();
    }
    else {
        if (boxCheck()) {
            eventInfo.onCondition(dEvtCnd_CANDOOR_e);

            if (getShapeType() == 0) {
                eventInfo.setEventName("DEFAULT_TREASURE_A");
            }
            else {
                eventInfo.setEventName("DEFAULT_TREASURE");
            }
        }
    }

    return TRUE;
}

/* 000027C8-000028A0       .text actionSwOnWait__8daTbox_cFv */
BOOL daTbox_c::actionSwOnWait() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        setAction(&daTbox_c::actionDemo2);

        mStaffId = dComIfGp_evmng_getMyStaffId("TREASURE");
        demoProc();
    }
    else {
        if (dComIfGs_isSwitch(getSwNo(), mRoomNo)) {
            fopAcM_orderOtherEvent(this, "DEFAULT_TREASURE_APPEAR");
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
    }

    return TRUE;
}

/* 000028A0-00002914       .text actionSwOnWait2__8daTbox_cFv */
BOOL daTbox_c::actionSwOnWait2() {
    if (dComIfGs_isSwitch(getSwNo(), mRoomNo)) {
        setAction(&daTbox_c::actionOpenWait);
        setDzb();
    }

    return TRUE;
}

/* 00002914-00002A2C       .text actionGenocide__8daTbox_cFv */
BOOL daTbox_c::actionGenocide() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        setAction(&daTbox_c::actionDemo2);

        mStaffId = dComIfGp_evmng_getMyStaffId("TREASURE");
        demoProc();
    }
    else {
        if (mRoomNo != -1 && mRoomNo == dComIfGp_roomControl_getStayNo() && fopAcM_myRoomSearchEnemy(mRoomNo) == NULL) {
            if (mGenocideDelayTimer != 0) {
                mGenocideDelayTimer--;
            }
            else {
                fopAcM_orderOtherEvent(this, "DEFAULT_TREASURE_APPEAR");
                eventInfo.onCondition(dEvtCnd_UNK2_e);

                dComIfGs_onSwitch(getSwNo(), mRoomNo);
            }
        }
    }

    return TRUE;
}

/* 00002C10-00002FB0       .text draw__8daTbox_cFv */
BOOL daTbox_c::draw() {
    u8 tboxNo;

    if (mRoomNo != -1 && !checkRoomDisp(mRoomNo)) {
        return TRUE;
    }

    if (flagCheck(daTboxFlg_UNK_01) || (checkEnv() && flagCheck(daTboxFlg_UNK_04))) {
        tboxNo = mTboxNo;
    }
    else {
        tboxNo = 0xFF;
    }

    if (!checkOpen()) {
        dMap_drawPoint(5, current.pos.x, current.pos.y, current.pos.z, mRoomNo, -0x8000, tboxNo, gbaName, 0);
    }

    tevStr.mRoomNo = mRoomNo;
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);

    if (getFuncType() == FUNC_TYPE_TACT) {
        J3DModelData* platMdlData = mpTactPlatformMdl->getModelData();

        g_env_light.setLightTevColorType(mpTactPlatformMdl, &tevStr);
        mTactPlatformBrk.entry(platMdlData);
        mDoExt_modelUpdateDL(mpTactPlatformMdl);
    }

    if (flagCheck(daTboxFlg_UNK_01)) {
        return TRUE;
    }

    g_env_light.setLightTevColorType(mpChestMdl, &tevStr);

    J3DModelData* chestMdlData = mpChestMdl->getModelData();
    mOpenAnm.entry(chestMdlData);

    if (mpAppearTexAnm != NULL) {
        mpAppearTexAnm->entry(chestMdlData);
    }
    if (mpAppearRegAnm != NULL) {
        mpAppearRegAnm->entry(chestMdlData);
    }

    if (checkEnv() && flagCheck(daTboxFlg_UNK_04)) {
        float scrollOffset = mInvisibleScrollVal - -2.0f;
        s8 offsetAsU8 = scrollOffset;

        float interpVal = (scrollOffset - offsetAsU8) * 0.5f + 0.5f;

        for (u8 i = 0; i < chestMdlData->getMaterialNum(); i++) {
            J3DMaterial* mat = chestMdlData->getMaterialNodePointer(i);

            for (u8 j = 0; j < mat->getIndTexStageNum(); j++) {
                J3DIndTexMtx* texMtx = mat->getIndTexMtx(j);
                texMtx->setScaleExp(offsetAsU8);

                Mtx3P offsetMtx = texMtx->getOffsetMtx();
                offsetMtx[0][0] = interpVal;
                offsetMtx[1][1] = interpVal;
            }
        }

        if (flagCheck(daTboxFlg_UNK_04)) {
            dComIfGd_setListInvisisble();
            mDoExt_modelUpdateDL(mpChestMdl);
            dComIfGd_setList();
        }
        else {
            mDoExt_modelUpdateDL(mpChestMdl);
        }
    }
    else {
        mDoExt_modelUpdateDL(mpChestMdl);
    }

    if (mIsFlashPlaying != 0 && mOpenTimer >= 0x24) {
        J3DModelData* flashMdlData = mpFlashMdl->getModelData();

        mFlashAnm.entry(flashMdlData);
        mFlashRegAnm.entry(flashMdlData);
        mFlashTexAnm.entry(flashMdlData);

        dComIfGd_setListMaskOff();
        mDoExt_modelUpdateDL(mpFlashMdl);
        dComIfGd_setList();
    }

    return TRUE;
}

/* 00002A2C-00002BF0       .text execute__8daTbox_cFv */
BOOL daTbox_c::execute() {
    if (mRoomNo == -1 || checkRoomDisp(mRoomNo) != TRUE) {
        return TRUE;
    }

    action();

    if (mpAppearTexAnm != NULL) {
        mpAppearTexAnm->play();
    }

    if (mIsFlashPlaying) {
        mFlashAnm.play();
        mFlashTexAnm.play();

        if (mFlashRegAnm.play()) {
            mIsFlashPlaying = FALSE;
        }

        mpFlashMdl->setBaseScale(cXyz(10.0f / 7.0f, 1.0f, 1.0f));

        mDoMtx_stack_c::transS(current.pos.x, current.pos.y + 50.0f, current.pos.z);
        mDoMtx_stack_c::YrotM(current.angle.y + 0x7FFF);
        mpFlashMdl->setBaseTRMtx(mDoMtx_stack_c::get());
    }

    if (getFuncType() == FUNC_TYPE_GRAVITY) {
        fopAcM_posMoveF(this, NULL);
        mObjAcch.CrrPos(*dComIfG_Bgsp());

        attention_info.position = current.pos;

        mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
        mDoMtx_stack_c::YrotM(home.angle.y);

        mpChestMdl->setBaseTRMtx(mDoMtx_stack_c::get());
        mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);

        if (mpBgWCurrent != NULL) {
            mpBgWCurrent->Move();
        }
    }

    return TRUE;
}

/* 00002BF0-00002C10       .text daTbox_Draw__FP8daTbox_c */
static s32 daTbox_Draw(daTbox_c* i_tbox) {
    return i_tbox->draw();
}

/* 00002FB0-00002FD0       .text daTbox_Execute__FP8daTbox_c */
static s32 daTbox_Execute(daTbox_c* i_tbox) {
    return i_tbox->execute();
}

/* 00002FD0-00002FD8       .text daTbox_IsDelete__FP8daTbox_c */
static s32 daTbox_IsDelete(daTbox_c*) {
    return TRUE;
}

/* 00002FD8-00003070       .text daTbox_Delete__FP8daTbox_c */
static s32 daTbox_Delete(daTbox_c* i_tbox) {
    i_tbox->deleteProc();
    dComIfG_resDelete(i_tbox->getPhase(), "Dalways");

    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }

    return TRUE;
}

/* 00003070-0000315C       .text daTbox_Create__FP10fopAc_ac_c */
static cPhs_State daTbox_Create(fopAc_ac_c* i_actor) {
    static const u32 heapsize_tbl[] = {
        0x2E40,
        0x2D7C,
        0x2E40,
        0x2D80
    };

    static const u32 opensize_tbl[] = {
        0x14C0,
        0x14E0,
        0x14C0,
        0x14C0
    };

    daTbox_c* tbox = static_cast<daTbox_c*>(i_actor);

    fopAcM_SetupActor(tbox, daTbox_c);

    cPhs_State result = dComIfG_resLoad(tbox->getPhase(), "Dalways");

    if (result == cPhs_COMPLEATE_e) {
        tbox->mRoomNo = tbox->home.angle.x & 0x3F;

        u32 shapeType = tbox->getShapeType();
        u32 heapSize = heapsize_tbl[shapeType];

        if (!tbox->checkOpen()) {
            heapSize += opensize_tbl[shapeType];
        }

        u32 heapResult = fopAcM_entrySolidHeap(i_actor, CheckCreateHeap, heapSize);
        if (!heapResult) {
            return cPhs_ERROR_e;
        }
        else {
            tbox->CreateInit();
            tbox->attention_info.flags = fopAc_Attn_ACTION_TREASURE_e;
        }
    }

    return result;
}

static actor_method_class l_daTbox_Method = {
    (process_method_func)daTbox_Create,
    (process_method_func)daTbox_Delete,
    (process_method_func)daTbox_Execute,
    (process_method_func)daTbox_IsDelete,
    (process_method_func)daTbox_Draw,
};

actor_process_profile_definition g_profile_TBOX = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_TBOX,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daTbox_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_TBOX,
    /* Actor SubMtd */ &l_daTbox_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
