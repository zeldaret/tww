//
// Generated by dtk
// Translation Unit: d_a_tbox.cpp
//

#include "JSystem/JKernel/JKRHeap.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "d/d_bg_s_acch.h"
#include "d/d_bg_w.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_particle.h"
#include "d/d_procname.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_graphic.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_do/m_Do_mtx.h"
#include "dolphin/types.h"


#define DEMO_PROC_WAIT 0
#define DEMO_PROC_OPEN 1
#define DEMO_PROC_APPEAR 2
#define DEMO_PROC_OPEN_SHORT 3

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

// Needed for the .data section to match.
static f32 dummy1[3] = {1.0f, 1.0f, 1.0f};
static f32 dummy2[3] = {1.0f, 1.0f, 1.0f};
static u8 dummy3[4] = {0x02, 0x00, 0x02, 0x01};
static f64 dummy4[2] = {3.0, 0.5};

class daTbox_HIO_c {
public:
    daTbox_HIO_c();
    virtual ~daTbox_HIO_c();

    /* 0x0004 */ s8 mHioId;
    /* 0x0006 */ s16 m0006;
    /* 0x0008 */ s16 m0008;
    /* 0x000A */ s16 m000A;
    /* 0x000C */ s16 m000C;
};

static daTbox_HIO_c l_HIO;

struct modelInfo {
    s16 modelId;
    s16 openBckId;
    s16 btkId;
    s16 brkId;
    s16 closedColId;
    s16 openColId;
};

static modelInfo l_modelInfo[] = {
    { 0x000E, 0x0009, 0x0022, 0x001B, 0x002A, 0x002B },
    { 0x000F, 0x0008, 0x0023, 0x001C, 0x002A, 0x002B },
    { 0x0010, 0x0008, 0x0024, 0x001D, 0x002A, 0x002B },
    { 0x0014, 0x0008, 0xFFFF, 0xFFFF, 0x002C, 0x002D }
};

class daTbox_c : public fopAc_ac_c {
public:
    daTbox_c();

    s32 commonShapeSet();
    s32 effectShapeSet();
    s32 envShapeSet();
    s32 bgCheckSet();

    void searchRoomNo();
    void lightReady();
    
    BOOL checkEnv();
    BOOL checkOpen();

    modelInfo& getModelInfo();
    
    void clrDzb();
    void setDzb();

    void surfaceProc();
    BOOL checkRoomDisp(int);
    u32 getShapeType();
    s32 getFuncType();
    BOOL checkNormal();
    
    s32 CreateHeap();
    s32 CreateInit();

    void boxCheck();
    void lightUpProc();
    void lightDownProc();
    void darkProc();
    void volmProc();

    void demoProcOpen();

    void demoInitAppear_Tact();
    void demoInitAppear();

    void demoProcAppear_Tact();
    void demoProcAppear();

    s32 demoProc();

    void OpenInit_com();
    void OpenInit();

    void setCollision();

    bool actionWait();
    bool actionDemo();
    bool actionDemo2();
    bool actionOpenWait();
    bool actionSwOnWait();
    bool actionSwOnWait2();
    bool actionGenocide();

    s32 execute();
    s32 draw();

    /* 0x0290 */ s32 mRoomNo;
    /* 0x0294 */ request_of_phase_process_class mPhs;

    /* 0x029C */ J3DModel* mChestMdl;
    /* 0x02A0 */ mDoExt_bckAnm mOpenAnm;
    /* 0x02B0 */ mDoExt_btkAnm* mpAppearTexAnm;
    /* 0x02B4 */ mDoExt_brkAnm* mpAppearRegAnm;

    /* 0x02B8 */ dBgW* mpBgWClosed;
    /* 0x02BC */ dBgW* mpBgWOpen;
    /* 0x02C0 */ dBgW* mpBgWVines;

    /* 0x02C4 */ dBgW* mpBgWCurrent;

    /* 0x02C8 */ J3DModel* mpFlashMdl;
    /* 0x02CC */ mDoExt_bckAnm mFlashAnm;
    /* 0x02DC */ mDoExt_btkAnm mFlashTexAnm;
    /* 0x02F0 */ mDoExt_brkAnm mFlashRegAnm;
    
    /* 0x0308 */ u32 m0308;

    /* 0x030C */ mDoExt_brkAnm mBrkAnm3;

    /* 0x0324 */ J3DModel* mTactPlatformMdl;
    /* 0x0328 */ mDoExt_brkAnm mTactPlatformBrk;

    typedef bool (daTbox_c::*actionFunc)();
    /* 0x0340 */ actionFunc mActionFunc;

    /* 0x034C */ float m034C;

    /* 0x0350 */ u32 mStaffId;

    /* 0x0354 */ Mtx mMtx;

    /* 0x0384 */ LIGHT_INFLUENCE mPLight;
    /* 0x03A4 */ LIGHT_INFLUENCE mEfLight;

    /* 0x03C4 */ dPa_smokeEcallBack mSmokeCB;
    /* 0x03E4 */ JPABaseEmitter* mSmokeEmitter;

    /* 0x03E8 */ float mAllColRatio;
    /* 0x03EC */ float m03EC;

    /* 0x03F0 */ u16 mFlags;
    /* 0x03F2 */ s16 m03F2;

    /* 0x03F4 */ u8 m03F4;
    /* 0x03F5 */ u8 m03F5;
    /* 0x03F6 */ u16 m03F6;

    /* 0x03F8 */ u8 m03F8;

    /* 0x03FC */ dBgS_ObjAcch mObjAcch;
    /* 0x05C0 */ dBgS_AcchCir mAcchCir;
    /* 0x0600 */ dCcD_Stts mColStatus;
    /* 0x063C */ dCcD_Cyl mColCyl;

    /* 0x076C */ u8 mOpenedSwitch;

    void flagOn(u16 flag) { mFlags |= flag; }
    void flagOff(u16 flag) { mFlags &= ~flag; }
    void flagClr() { mFlags = 0; }
    BOOL flagCheck(u16 flag) { return mFlags & flag; }

    u8 getTboxNo() { return fopAcM_GetParam(this) >> 0x07 & 0x1F; }
    s32 getSwNo() { return fopAcM_GetParam(this) >> 0x0C & 0xFF; }
};

/* 000000EC-00000124       .text __ct__12daTbox_HIO_cFv */
daTbox_HIO_c::daTbox_HIO_c() {
    mHioId = -1;
    m0006 = 0x82;
    m0008 = 0xB4;
    m000A = 0x30;
    m000C = 0x1E;
}

/* 00000124-00000550       .text commonShapeSet__8daTbox_cFv */
s32 daTbox_c::commonShapeSet() {
    modelInfo& mdlInfo = getModelInfo();

    // Load model
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Dalways", mdlInfo.modelId);
    JUT_ASSERT(0xA0, modelData != 0);

    u32 modelFlags = 0x11000022;

    // Load open animation
    J3DAnmTransform* openAnm = (J3DAnmTransform*)dComIfG_getObjectRes("Dalways", mdlInfo.openBckId);
    if (mOpenAnm.init(modelData, openAnm, true, 0,  1.0f, 0, -1, false) == 0) {
        return cPhs_ERROR_e;
    }

    // Load texture anim, if requested
    if (mdlInfo.btkId > 0) {
        mpAppearTexAnm = new mDoExt_btkAnm();
        if (mpAppearTexAnm == NULL) {
            return cPhs_ERROR_e;
        }

        J3DAnmTextureSRTKey* appearTexData = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Dalways", mdlInfo.btkId);
        if (mpAppearTexAnm->init(modelData, appearTexData, true, 2, 1.0f, 0, -1, false, 0) == 0) {
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
        if (mpAppearRegAnm->init(modelData, appearRegData, true, 0, 1.0f, 0, -1, false, 0) == 0) {
            return cPhs_ERROR_e;
        }

        modelFlags |= 0xF020000;
    }

    // Create model
    mChestMdl = mDoExt_J3DModel__create(modelData, 0x80000, modelFlags);
    if (mChestMdl == NULL) {
        return cPhs_ERROR_e;
    }

    // Set up Triforce platform for the type that spawns via Wind Waker song
    if (getFuncType() == FUNC_TYPE_TACT) {
        modelData = (J3DModelData*)dComIfG_getObjectRes("Dalways", 0x17);
        JUT_ASSERT(0xE2, modelData);

        mTactPlatformMdl = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000000);
        if (mTactPlatformMdl == NULL) {
            return cPhs_ERROR_e;
        }

        J3DAnmTevRegKey* tactPlatformBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Dalways", 0x1F);
        if (mTactPlatformBrk.init(modelData, tactPlatformBrk, true, 0, 1.0f, 0, -1, false, 0) == 0) {
            return cPhs_ERROR_e;
        }
    }

    mChestMdl->setBaseScale(mScale);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mChestMdl->setBaseTRMtx(mDoMtx_stack_c::get());

    if (getFuncType() == FUNC_TYPE_TACT) {
        mDoMtx_stack_c::transM(0.0f, 1.0f, 0.0f);
        mTactPlatformMdl->setBaseTRMtx(mDoMtx_stack_c::get());
    }

    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);

    return cPhs_COMPLEATE_e;
}

/* 00000598-00000764       .text effectShapeSet__8daTbox_cFv */
s32 daTbox_c::effectShapeSet() {
    J3DModelData* flashModelData = (J3DModelData*)dComIfG_getObjectRes("Dalways", 0x16);
    JUT_ASSERT(0x117, flashModelData != 0);
    
    mpFlashMdl = mDoExt_J3DModel__create(flashModelData, 0x80000, 0x1000200);
    if (mpFlashMdl == NULL) {
        return cPhs_ERROR_e;
    }

    J3DAnmTransform* flashAnm = (J3DAnmTransform*)dComIfG_getObjectRes("Dalways", 0x0B);
    if (mFlashAnm.init(flashModelData, flashAnm, true, 0, 1.0f, 0, -1, false) == 0) {
        return cPhs_ERROR_e;
    }

    J3DAnmTextureSRTKey* flashTexAnm = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Dalways", 0x25);
    if (mFlashTexAnm.init(flashModelData, flashTexAnm, true, 0, 1.0f, 0, -1, false, 0) == 0) {
        return cPhs_ERROR_e;
    }

    J3DAnmTevRegKey* flashRegAnm = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Dalways", 0x1E);
    int regInit = mFlashRegAnm.init(flashModelData, flashRegAnm, true, 0, 1.0f, 0, -1, false, 0);

    // Using cPhs_COMPLEATE_e and cPhs_ERROR_e break the match here.
    return regInit != 0 ? 4 : 5;
}

/* 00000764-00000928       .text envShapeSet__8daTbox_cFv */
s32 daTbox_c::envShapeSet() {
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
s32 daTbox_c::bgCheckSet() {
    modelInfo& mdlInfo = getModelInfo();

    cBgD_t* bgd = (cBgD_t*)dComIfG_getObjectRes("Dalways", mdlInfo.closedColId);
    JUT_ASSERT(0x195, bgd != 0);

    mpBgWClosed = new dBgW();
    if (mpBgWClosed == NULL) {
        return cPhs_ERROR_e;
    }

    if (mpBgWClosed->Set(bgd, 1, &mMtx) == 1) {
        return cPhs_ERROR_e;
    }

    bgd = (cBgD_t*)dComIfG_getObjectRes("Dalways", mdlInfo.openColId);
    JUT_ASSERT(0x1A6, bgd != 0);

    mpBgWOpen = new dBgW();
    if (mpBgWOpen == NULL) {
        return cPhs_ERROR_e;
    }

    if (mpBgWOpen->Set(bgd, 1, &mMtx) == 1) {
        return cPhs_ERROR_e;
    }

    if (getFuncType() == FUNC_TYPE_SWITCH_VISIBLE) {
        bgd = (cBgD_t*)dComIfG_getObjectRes("Dalways", 0x2E);
        JUT_ASSERT(0x1B9, bgd != 0);

        mpBgWVines = new dBgW();
        if (mpBgWVines == NULL) {
            return cPhs_ERROR_e;
        }

        if (mpBgWVines->Set(bgd, 1, &mMtx) == 1) {
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
        mRoomNo = orig.angle.x & 0x3F;
    }

    if (flagCheck(0x02)) {
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
        int stageNo = 1;
        u8 tBoxNo = getTboxNo();

        return dComIfGs_isStageTbox(stageNo, tBoxNo);
    }
    else {
        u8 tBoxNo = getTboxNo();
        return dComIfGs_isTbox(tBoxNo);
    }
}

/* 00000D48-00000D78       .text getModelInfo__8daTbox_cFv */
modelInfo& daTbox_c::getModelInfo() {
    return l_modelInfo[getShapeType()];
}

/* 00000D78-00000DD0       .text clrDzb__8daTbox_cFv */
void daTbox_c::clrDzb() {
    if (mpBgWCurrent != NULL) {
        g_dComIfG_gameInfo.play.mBgS.Release(mpBgWCurrent);
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

    bool rt = g_dComIfG_gameInfo.play.mBgS.Regist(mpBgWCurrent, this);
    JUT_ASSERT(0x234, !rt);

    mpBgWCurrent->mRoomNo = mRoomNo;
    mColCyl.OnCoSetBit();
}

/* 00000ECC-00000F8C       .text surfaceProc__8daTbox_cFv */
void daTbox_c::surfaceProc() {
    if (mpBgWCurrent != NULL && flagCheck(0x20)) {
        if (m03EC < -1.0f) {
            m03EC += 1.0f;
        }
        else {
            flagOff(0x20);
            m03EC = 0.0f;
        }

        mDoMtx_stack_c::transS(current.pos.x, current.pos.y + m03EC, current.pos.z);
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
u32 daTbox_c::getShapeType() {
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

    return dComIfGs_isSwitch(swNo, mRoomNo) ? TRUE : FALSE;
}

/* 0000108C-000010AC       .text CheckCreateHeap__FP10fopAc_ac_c */
s32 CheckCreateHeap(fopAc_ac_c* i_actor) {
    return static_cast<daTbox_c*>(i_actor)->CreateHeap();
}

/* 000010AC-0000114C       .text CreateHeap__8daTbox_cFv */
s32 daTbox_c::CreateHeap() {
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
s32 daTbox_c::CreateInit() {
    s32 funcType = getFuncType();
    flagClr();

    mSmokeCB.field_0x15 = 1;
    mOpenAnm.setPlaySpeed(0.0f);

    if (checkOpen()) {
        J3DFrameCtrl* frameCtrl = mOpenAnm.getFrameCtrl();
        frameCtrl->setFrame(frameCtrl->getEnd());

        mActionFunc = actionWait;

        if (checkEnv()) {
            m034C = 2.0;

            frameCtrl = mpAppearRegAnm->getFrameCtrl();
            frameCtrl->setFrame(frameCtrl->getEnd());
        }
    }
    else {
        if (!checkEnv()) {
            mActionFunc = actionOpenWait;
        }
        else {
            if (checkNormal()) {
                if (funcType == FUNC_TYPE_SWITCH_VISIBLE && !dComIfGs_isSwitch(getSwNo(), mRoomNo)) {
                    mActionFunc = actionOpenWait;
                }
                else {
                    mActionFunc = actionSwOnWait2;
                }

                m034C = 2.0f;

                J3DFrameCtrl* frameCtrl = mpAppearRegAnm->getFrameCtrl();
                frameCtrl->setFrame(frameCtrl->getEnd());
            }
            else {
                 flagOn(0x04);

                switch (funcType) {
                    case FUNC_TYPE_SWITCH:
                    case FUNC_TYPE_EXTRA_SAVE_INFO_SPAWN:
                        mActionFunc = actionSwOnWait;
                        m03F8 = 0x41;
                        flagOn(0x03);
                        m03F6 = 0x78;
                        break;
                    case FUNC_TYPE_ENEMIES:
                        mActionFunc = actionGenocide;
                        flagOn(0x03);
                        m03F6 = 0x78;
                        break;
                    case FUNC_TYPE_TACT:
                        mActionFunc = actionSwOnWait;
                        flagOn(0x03);
                        m03F6 = l_HIO.m0008;
                        break;
                    case FUNC_TYPE_SWITCH_TRANSPARENT:
                        mActionFunc = actionSwOnWait;
                        flagOn(0x02);
                        m03F6 = 0x5A;

                        mpAppearRegAnm->setFrame(30.0f);
                        break;
                    default:
                        JUT_ASSERT(0x328, 0);
                        break;
                }

                m034C = -2.0f;
            }
        }
    }

    lightReady();
    mAllColRatio = 1.0f;

    if (l_HIO.mHioId < 0) {
        l_HIO.mHioId = mDoHIO_root.mDoHIO_createChild("宝箱", (JORReflexible*)(&l_HIO));
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
        mObjAcch.Set(getPositionP(), &next.pos, this, 1, &mAcchCir, &speed, NULL, NULL);

        mGravity = -2.5f;
    }

    mOpenedSwitch = getTboxNo();
}

/* 00001560-00001624       .text boxCheck__8daTbox_cFv */
void daTbox_c::boxCheck() {
    /* Nonmatching */
}

/* 00001624-00001668       .text lightUpProc__8daTbox_cFv */
void daTbox_c::lightUpProc() {
    /* Nonmatching */
}

/* 00001668-000016BC       .text lightDownProc__8daTbox_cFv */
void daTbox_c::lightDownProc() {
    /* Nonmatching */
}

/* 000016BC-0000172C       .text darkProc__8daTbox_cFv */
void daTbox_c::darkProc() {
    /* Nonmatching */
}

/* 0000172C-000017CC       .text volmProc__8daTbox_cFv */
void daTbox_c::volmProc() {
    /* Nonmatching */
}

/* 000017CC-00001890       .text demoProcOpen__8daTbox_cFv */
void daTbox_c::demoProcOpen() {
    /* Nonmatching */
}

/* 00001890-00001A40       .text demoInitAppear_Tact__8daTbox_cFv */
void daTbox_c::demoInitAppear_Tact() {
    /* Nonmatching */
}

/* 00001A40-00001B38       .text demoInitAppear__8daTbox_cFv */
void daTbox_c::demoInitAppear() {
    /* Nonmatching */
}

/* 00001B38-00001CF4       .text demoProcAppear_Tact__8daTbox_cFv */
void daTbox_c::demoProcAppear_Tact() {
    /* Nonmatching */
}

/* 00001CF4-00001E4C       .text demoProcAppear__8daTbox_cFv */
void daTbox_c::demoProcAppear() {
    /* Nonmatching */
}

/* 00001E4C-0000210C       .text demoProc__8daTbox_cFv */
s32 daTbox_c::demoProc() {
    static char* action_table[] = {
        "WAIT",
        "OPEN",
        "APPEAR",
        "OPEN_SHORT"
    };

    s32 actionIdx = dComIfGp_evmng_getMyActIdx(mStaffId, action_table, 4, 0, 0);
    bool bIsAdvance = dComIfGp_evmng_getIsAddvance(mStaffId);

    if (bIsAdvance) {
        m03F4 = 0;

        switch (actionIdx) {
            case DEMO_PROC_OPEN:
                OpenInit();
                lightReady();
                mPLight.mPower = 0.0f;
                mEfLight.mPower = 0.0f;
                break;
            case DEMO_PROC_APPEAR:
                flagOn(0x20);
                m03EC = -130.0f;
                
                setDzb();

                if (getFuncType() == FUNC_TYPE_TACT) {
                    flagOff(0x02);
                    demoInitAppear_Tact();
                }
                else {
                    flagOff(0x03);
                    demoInitAppear();
                }

                break;
            case DEMO_PROC_OPEN_SHORT:
                OpenInit_com();
                break;
        }
    }

    switch (actionIdx) {
        case DEMO_PROC_APPEAR:
            if (getFuncType() == FUNC_TYPE_TACT) {
                demoProcAppear_Tact();
            }
            else {
                demoProcAppear();
            }

            surfaceProc();
            break;
        case DEMO_PROC_OPEN:
            if (m03F4 != 0) {
                dComIfGp_evmng_cutEnd(mStaffId);
            }
            else {
                if (mOpenAnm.play() != 0) {
                    m03F4 = 1;
                    dComIfGp_evmng_cutEnd(mStaffId);
                    fopAcM_seStart(this, JA_SE_OBJ_TBOX_OPEN_S2, 0);
                }
            }
            break;
        case DEMO_PROC_OPEN_SHORT:
            if (m03F4 != 0) {
                dComIfGp_evmng_cutEnd(mStaffId);
            }
            else {
                if (mOpenAnm.play() != 0) {
                    m03F4 = 1;
                    dComIfGp_evmng_cutEnd(mStaffId);
                    fopAcM_seStart(this, JA_SE_OBJ_TBOX_OPEN_S2, 0);
                }
            }
            break;
        default:
            dComIfGp_evmng_cutEnd(mStaffId);
            break;
    }

    if (flagCheck(0x10)) {
        demoProcOpen();
    }

    if (flagCheck(0x08)) {
        dKy_set_allcol_ratio(mAllColRatio);
    }

    return 0;
}

/* 0000210C-00002250       .text OpenInit_com__8daTbox_cFv */
void daTbox_c::OpenInit_com() {
    /* Nonmatching */
}

/* 00002250-00002444       .text OpenInit__8daTbox_cFv */
void daTbox_c::OpenInit() {
    /* Nonmatching */
}

/* 00002444-000024AC       .text setCollision__8daTbox_cFv */
void daTbox_c::setCollision() {
    /* Nonmatching */
}

/* 000024AC-000024B4       .text actionWait__8daTbox_cFv */
bool daTbox_c::actionWait() {
    return true;
}

/* 000024B4-000025A4       .text actionDemo__8daTbox_cFv */
bool daTbox_c::actionDemo() {
    /* Nonmatching */
}

/* 000025A4-00002634       .text actionDemo2__8daTbox_cFv */
bool daTbox_c::actionDemo2() {
    /* Nonmatching */
}

/* 00002634-000027C8       .text actionOpenWait__8daTbox_cFv */
bool daTbox_c::actionOpenWait() {
    /* Nonmatching */
}

/* 000027C8-000028A0       .text actionSwOnWait__8daTbox_cFv */
bool daTbox_c::actionSwOnWait() {
    /* Nonmatching */
}

/* 000028A0-00002914       .text actionSwOnWait2__8daTbox_cFv */
bool daTbox_c::actionSwOnWait2() {
    /* Nonmatching */
}

/* 00002914-00002A2C       .text actionGenocide__8daTbox_cFv */
bool daTbox_c::actionGenocide() {
    /* Nonmatching */
}

/* 00002A2C-00002BF0       .text execute__8daTbox_cFv */
s32 daTbox_c::execute() {
    /* Nonmatching */
}

/* 00002BF0-00002C10       .text daTbox_Draw__FP8daTbox_c */
s32 daTbox_Draw(daTbox_c* i_tbox) {
    return i_tbox->draw();
}

/* 00002C10-00002FB0       .text draw__8daTbox_cFv */
s32 daTbox_c::draw() {
    /* Nonmatching */
}

/* 00002FB0-00002FD0       .text daTbox_Execute__FP8daTbox_c */
s32 daTbox_Execute(daTbox_c* i_tbox) {
    return i_tbox->execute();
}

/* 00002FD0-00002FD8       .text daTbox_IsDelete__FP8daTbox_c */
s32 daTbox_IsDelete(daTbox_c*) {
    return TRUE;
}

/* 00002FD8-00003070       .text daTbox_Delete__FP8daTbox_c */
s32 daTbox_Delete(daTbox_c* i_tbox) {
    if (i_tbox->mpBgWCurrent != NULL) {
        g_dComIfG_gameInfo.play.mBgS.Release(i_tbox->mpBgWCurrent);
    }

    i_tbox->mSmokeCB.end();
    dComIfG_resDelete(&i_tbox->mPhs, "Dalways");

    if (l_HIO.mHioId >= 0) {
        mDoHIO_root.mDoHIO_deleteChild(l_HIO.mHioId);
        l_HIO.mHioId = -1;
    }

    return TRUE;
}

/* 00003070-0000315C       .text daTbox_Create__FP10fopAc_ac_c */
s32 daTbox_Create(fopAc_ac_c* i_actor) {
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
    s32 result;

    fopAcM_SetupActor(tbox, daTbox_c);

    result = dComIfG_resLoad(&tbox->mPhs, "Dalways");

    if (result == cPhs_COMPLEATE_e) {
        tbox->mRoomNo = tbox->orig.angle.x & 0x3F;
        
        u32 shapeType = tbox->getShapeType();
        u32 heapSize = heapsize_tbl[shapeType];

        if (tbox->checkOpen() == FALSE) {
            heapSize += opensize_tbl[shapeType];
        }

        u32 heapResult = fopAcM_entrySolidHeap(i_actor, (heapCallbackFunc)CheckCreateHeap, heapSize);
        if (heapResult == FALSE) {
            return cPhs_ERROR_e;
        }
        else {
            tbox->CreateInit();
            tbox->mAttentionInfo.mFlags = fopAc_Attn_ACTION_TREASURE_e;
        }
    }

    return result;
}

/* 0000315C-000032F0       .text __ct__8daTbox_cFv */
daTbox_c::daTbox_c() {

}

/* 000039E4-00003A2C       .text __dt__12daTbox_HIO_cFv */
daTbox_HIO_c::~daTbox_HIO_c() {

}

static actor_method_class l_daTbox_Method = {
    (process_method_func)daTbox_Create,
    (process_method_func)daTbox_Delete,
    (process_method_func)daTbox_Execute,
    (process_method_func)daTbox_IsDelete,
    (process_method_func)daTbox_Draw,
};

actor_process_profile_definition g_profile_TBOX = {
    fpcLy_CURRENT_e,
    7,
    fpcPi_CURRENT_e,
    PROC_TBOX,
    &g_fpcLf_Method.mBase,
    sizeof(daTbox_c),
    0,
    0,
    &g_fopAc_Method.base,
    0x0113,
    &l_daTbox_Method,
    fopAcStts_UNK40000_e | fopAcStts_UNK4000_e,
    fopAc_ACTOR_e,
    fopAc_CULLBOX_CUSTOM_e,
};
