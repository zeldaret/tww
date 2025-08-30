/**
 * d_a_obj_figure.cpp
 * Object - Nintendo Gallery figurines + stand
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_figure.h"
#include "d/res/res_figure.h"
#include "d/res/res_figure2.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/d_com_lib_game.h"
#include "d/d_snap.h"
#include "d/d_camera.h"
#include "d/d_a_obj.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/actor/d_a_player_main.h"
#include "m_Do/m_Do_controller_pad.h"

#define TOTAL_FIGURE_COUNT 0x86

static const char* l_arcname_tbl[] = {
    "Figure",
    "Figure2",
    "Figure1",
    "Figure0",
    "Figure6",
    "Figure5",
    "Figure3",
    "Figure4",
#if VERSION > VERSION_DEMO
    "Figure2a",
    "Figure2b",
    "Figure6a",
    "Figure6b",
    "Figure6c",
#endif
};

static u16 l_figure_comp[] = {
    0x95FF,
    0x94FF,
    0x93FF,
    0x92FF,
    0x91FF,
    0x90FF,
    0x8FFF,
    0x8EFF,
    0x8DFF,
    0x8CFF,
    0xB1FF,
    0x9CFF,
    0x84FF,
    0x83FF,
    0x82FF,
    0x81FF,
    0x80FF,
};

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
        /* Height */ 150.0f,
    }},
};

struct FigureData {
    /* 0x00 */ int mBmdId;
    /* 0x04 */ int mModelAttr;
#if VERSION > VERSION_DEMO
    /* 0x08 */ int mRoomId;
#endif
}; // Size: 0x0C

#if VERSION == VERSION_DEMO
#define FIGUREDAT(bmdId, dlistFlags, roomId)                                                       \
    {                                                                                              \
        bmdId, dlistFlags                                                                          \
    }
#else
#define FIGUREDAT(bmdId, dlistFlags, roomId)                                                       \
    {                                                                                              \
        bmdId, dlistFlags, roomId                                                                  \
    }
#endif

static const FigureData l_figure_dat_tbl[TOTAL_FIGURE_COUNT] = {
    FIGUREDAT(0x00, 0x37441422, -1),
    FIGUREDAT(0x01, 0x37441422, -1),
    FIGUREDAT(0x02, 0x37441422, -1),
    FIGUREDAT(0x03, 0x37441422, -1),
    FIGUREDAT(0x0A, 0x37441422, -1),
    FIGUREDAT(0x04, 0x37441422, -1),
    FIGUREDAT(0x05, 0x37441422, -1),
    FIGUREDAT(0x06, 0x37441422, -1),
    FIGUREDAT(0x07, 0x37441422, -1),
    FIGUREDAT(0x08, 0x37441422, -1),
    FIGUREDAT(0x09, 0x11001222, -1),
    FIGUREDAT(0x0B, 0x37441422, -1),
    FIGUREDAT(0x0C, 0x37441422, -1),
    FIGUREDAT(0x0D, 0x37441422, -1),
    FIGUREDAT(0x00, 0x37441422, -1),
    FIGUREDAT(0x01, 0x37441422, -1),
    FIGUREDAT(0x02, 0x37441422, -1),
    FIGUREDAT(0x04, 0x37441422, -1),
    FIGUREDAT(0x05, 0x37441422, -1),
    FIGUREDAT(0x07, 0x37441422, -1),
    FIGUREDAT(0x08, 0x37441422, -1),
    FIGUREDAT(0x09, 0x37441422, -1),
    FIGUREDAT(0x0A, 0x37441422, -1),
    FIGUREDAT(0x0B, 0x37441422, -1),
    FIGUREDAT(0x0C, 0x37441422, -1),
    FIGUREDAT(0x0D, 0x37441422, -1),
    FIGUREDAT(0x0E, 0x37441422, -1),
    FIGUREDAT(0x0F, 0x37441422, -1),
    FIGUREDAT(0x10, 0x37441422, -1),
    FIGUREDAT(0x11, 0x37441422, -1),
    FIGUREDAT(0x12, 0x37441422, -1),
    FIGUREDAT(0x13, 0x37441422, -1),
    FIGUREDAT(0x14, 0x37441422, -1),
    FIGUREDAT(0x15, 0x37441422, -1),
    FIGUREDAT(0x16, 0x37441422, -1),
    FIGUREDAT(0x17, 0x37441422, -1),
    FIGUREDAT(0x18, 0x37441422, -1),
    FIGUREDAT(0x19, 0x37441422, -1),
    FIGUREDAT(0x1A, 0x37441422, -1),
    FIGUREDAT(0x1B, 0x37441422, -1),
    FIGUREDAT(0x1C, 0x37441422, -1),
#if VERSION > VERSION_DEMO
    FIGUREDAT(0x00, 0x37441422, 8),
#endif
    FIGUREDAT(0x01, 0x37441422, 8),
    FIGUREDAT(0x02, 0x37441422, 8),
    FIGUREDAT(0x03, 0x37441422, 8),
    FIGUREDAT(0x04, 0x37441422, 8),
    FIGUREDAT(0x05, 0x37441422, 8),
    FIGUREDAT(0x06, 0x37441422, 8),
    FIGUREDAT(0x07, 0x37441422, 8),
    FIGUREDAT(0x08, 0x37441422, 8),
    FIGUREDAT(0x09, 0x37441422, 8),
    FIGUREDAT(0x0A, 0x37441422, 8),
    FIGUREDAT(0x0B, 0x37441422, 8),
    FIGUREDAT(0x0C, 0x37441422, 8),
#if VERSION == VERSION_DEMO
    FIGUREDAT(0x17, 0x37441422, -1),
#endif
    FIGUREDAT(0x0D, 0x37441422, 8),
    FIGUREDAT(0x0E, 0x37441422, 8),
#if VERSION == VERSION_DEMO
    FIGUREDAT(0x18, 0x37441422, 8),
    FIGUREDAT(0x0F, 0x37441422, 8),
    FIGUREDAT(0x10, 0x37441422, 8),
    FIGUREDAT(0x11, 0x37441422, 8),
    FIGUREDAT(0x12, 0x37441422, 8),
    FIGUREDAT(0x19, 0x37441422, 9),
    FIGUREDAT(0x13, 0x37441422, 9),
    FIGUREDAT(0x14, 0x37441422, 9),
    FIGUREDAT(0x16, 0x37441422, 9),
#else
    FIGUREDAT(0x0F, 0x37441422, 8),
    FIGUREDAT(0x10, 0x37441422, 8),
    FIGUREDAT(0x11, 0x37441422, 8),
    FIGUREDAT(0x12, 0x37441422, 8),
    FIGUREDAT(0x13, 0x37441422, 8),
    FIGUREDAT(0x06, 0x37441422, 9),
    FIGUREDAT(0x01, 0x37441422, 9),
    FIGUREDAT(0x02, 0x37441422, 9),
    FIGUREDAT(0x05, 0x37441422, 9),
#endif
    FIGUREDAT(0x00, 0x11001222, -1),
    FIGUREDAT(0x01, 0x37441422, -1),
    FIGUREDAT(0x02, 0x37441422, -1),
    FIGUREDAT(0x03, 0x37441422, -1),
    FIGUREDAT(0x04, 0x37441422, -1),
    FIGUREDAT(0x05, 0x37441422, -1),
    FIGUREDAT(0x06, 0x37441422, -1),
    FIGUREDAT(0x07, 0x37441422, -1),
    FIGUREDAT(0x08, 0x37441422, -1),
    FIGUREDAT(0x09, 0x37441422, -1),
    FIGUREDAT(0x0A, 0x37441422, -1),
    FIGUREDAT(0x0B, 0x37441422, -1),
    FIGUREDAT(0x0C, 0x37441422, -1),
    FIGUREDAT(0x0D, 0x37441422, -1),
    FIGUREDAT(0x0E, 0x37441422, -1),
    FIGUREDAT(0x0F, 0x37441422, -1),
    FIGUREDAT(0x10, 0x37441422, -1),
    FIGUREDAT(0x11, 0x11001222, -1),
    FIGUREDAT(0x00, 0x37441422, -1),
    FIGUREDAT(0x05, 0x37441422, -1),
    FIGUREDAT(0x06, 0x37441422, -1),
    FIGUREDAT(0x07, 0x37441422, -1),
    FIGUREDAT(0x08, 0x37441422, -1),
    FIGUREDAT(0x09, 0x37441422, -1),
    FIGUREDAT(0x0A, 0x37441422, -1),
    FIGUREDAT(0x0B, 0x37441422, -1),
    FIGUREDAT(0x0C, 0x37441422, -1),
    FIGUREDAT(0x0D, 0x37441422, -1),
    FIGUREDAT(0x01, 0x37441422, -1),
    FIGUREDAT(0x02, 0x37441422, -1),
    FIGUREDAT(0x03, 0x37441422, -1),
    FIGUREDAT(0x04, 0x37441422, -1),
    FIGUREDAT(0x00, 0x37441422, -1),
    FIGUREDAT(0x01, 0x37441422, -1),
    FIGUREDAT(0x02, 0x37441422, -1),
    FIGUREDAT(0x03, 0x37441422, -1),
    FIGUREDAT(0x04, 0x37441422, -1),
    FIGUREDAT(0x05, 0x37441422, -1),
    FIGUREDAT(0x06, 0x37441422, -1),
    FIGUREDAT(0x07, 0x37441422, -1),
    FIGUREDAT(0x08, 0x37441422, -1),
    FIGUREDAT(0x09, 0x37441422, -1),
    FIGUREDAT(0x12, 0x37441422, -1),
    FIGUREDAT(0x0A, 0x11001222, -1),
    FIGUREDAT(0x0B, 0x11001222, -1),
    FIGUREDAT(0x0C, 0x11001222, -1),
    FIGUREDAT(0x0D, 0x37441422, -1),
    FIGUREDAT(0x0E, 0x37441422, -1),
    FIGUREDAT(0x0F, 0x37441422, -1),
    FIGUREDAT(0x10, 0x37441422, -1),
    FIGUREDAT(0x11, 0x37441422, -1),
    FIGUREDAT(0x00, 0x37441422, 0xA),
#if VERSION == VERSION_DEMO
    FIGUREDAT(0x10, 0x37441422, 0xA),
#else
    FIGUREDAT(0x01, 0x37441422, 0xA),
#endif
    FIGUREDAT(0x02, 0x11001222, 0xA),
    FIGUREDAT(0x03, 0x11001222, 0xA),
    FIGUREDAT(0x04, 0x11001222, 0xA),
    FIGUREDAT(0x05, 0x37441422, 0xA),
    FIGUREDAT(0x06, 0x37441422, 0xA),
    FIGUREDAT(0x07, 0x37441422, 0xA),
#if VERSION == VERSION_DEMO
    FIGUREDAT(0x08, 0x37441422, 0xB),
    FIGUREDAT(0x09, 0x11001222, 0xB),
    FIGUREDAT(0x01, 0x11001222, 0xB),
    FIGUREDAT(0x0A, 0x37441422, 0xB),
    FIGUREDAT(0x0B, 0x37441422, 0xB),
    FIGUREDAT(0x0C, 0x11001222, 0xC),
    FIGUREDAT(0x0D, 0x37441422, 0xC),
    FIGUREDAT(0x0E, 0x11001222, 0xC),
    FIGUREDAT(0x11, 0x11001222, 0xC),
    FIGUREDAT(0x0F, 0x37441422, 0xC),
#else
    FIGUREDAT(0x00, 0x37441422, 0xB),
    FIGUREDAT(0x01, 0x11001222, 0xB),
    FIGUREDAT(0x02, 0x11001222, 0xB),
    FIGUREDAT(0x03, 0x37441422, 0xB),
    FIGUREDAT(0x04, 0x37441422, 0xB),
    FIGUREDAT(0x00, 0x11001222, 0xC),
    FIGUREDAT(0x01, 0x37441422, 0xC),
    FIGUREDAT(0x02, 0x11001222, 0xC),
    FIGUREDAT(0x03, 0x11001222, 0xC),
    FIGUREDAT(0x04, 0x37441422, 0xC),
#endif
};

struct FigureCheckTbl {
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ s16 field_0x28;
    /* 0x2A */ s16 field_0x2A;
    /* 0x2C */ s16 field_0x2C;
    /* 0x2E */ s16 field_0x2E;
    /* 0x30 */ s16 field_0x30;
    /* 0x32 */ s16 field_0x32;
}; // Size: 0x34

static const FigureCheckTbl l_figure_check_tbl[] = {
    {
        200.0f,
        5.0f,
        118.0f,
        80.0f,
        150.0f,
        30.0f,
        50.0f,
        2.0f,
        20.0f,
        60.0f,
        0x0000,
        0x0200,
        0x0200,
        0xE3E0,
        0x0FA0,
        0x0000,
    },
    {
        200.0f,
        5.0f,
        118.0f,
        80.0f,
        150.0f,
        30.0f,
        50.0f,
        2.0f,
        20.0f,
        60.0f,
        0x0000,
        0x0200,
        0x0200,
        0xE3E0,
        0x0FA0,
        0x0000,
    },
    {
        200.0f,
        5.0f,
        150.0f,
        80.0f,
        200.0f,
        30.0f,
        50.0f,
        2.0f,
        20.0f,
        60.0f,
        0x0000,
        0x0200,
        0x0200,
        0xE3E0,
        0x0FA0,
        0x0000,
    },
    {
        200.0f,
        5.0f,
        150.0f,
        80.0f,
        200.0f,
        30.0f,
        50.0f,
        2.0f,
        20.0f,
        60.0f,
        0x0000,
        0x0200,
        0x0200,
        0xE3E0,
        0x0FA0,
        0x0000,
    },
};

/* 000000EC-0000032C       .text __ct__13daObjFigure_cFv */
daObjFigure_c::daObjFigure_c() {
    mFigureNo = getPrmFigureNo();
    if(mFigureNo == 0xFF) {
        mFigureNo = 0;
    }
    if(mFigureNo >= TOTAL_FIGURE_COUNT) {
        mFigureNo = 0;
    }

    m734 = current.angle.y;
    mbDisplay = isFigureGet(mFigureNo);
    m732 = 0;
    m734 = 0;
    m736 = current.angle.y;
    m73C = 0;
}

/* 00000588-000005A8       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daObjFigure_c*>(i_this)->createHeap();
}

/* 000005A8-00000624       .text phase_1__FP13daObjFigure_c */
static cPhs_State phase_1(daObjFigure_c* i_this) {
    fopAcM_SetupActor(i_this, daObjFigure_c)
    i_this->setResFlag(0x1);

    cPhs_State status = dComIfG_resLoad(i_this->getPhase1P(), "Figure");
    if(status != cPhs_ERROR_e && status == cPhs_COMPLEATE_e) {
        return cPhs_NEXT_e;
    }

    return status;
}

/* 00000624-000006F0       .text phase_2__FP13daObjFigure_c */
static cPhs_State phase_2(daObjFigure_c* i_this) {
    i_this->setResFlag(0x2);
    u8 figureNo = i_this->getFigureNo();
    int id = dSnap_GetFigRoomId(figureNo);
#if VERSION > VERSION_DEMO
    if(l_figure_dat_tbl[figureNo].mRoomId >= 0) {
        id = l_figure_dat_tbl[figureNo].mRoomId;
    }
#endif

    cPhs_State status = dComIfG_resLoad(i_this->getPhase2P(), l_arcname_tbl[id]);

    if(status == cPhs_COMPLEATE_e) {
#if VERSION == VERSION_DEMO
        if(fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0))
#else
        if(fopAcM_entrySolidHeap(i_this, CheckCreateHeap, figureNo == 0x40 ? 0x25000 : 0xCD90))
#endif
        {
            return i_this->createInit();
        }
        else {
            return cPhs_ERROR_e;
        }
    }

    return status;
}

/* 000006F0-00000720       .text _create__13daObjFigure_cFv */
cPhs_State daObjFigure_c::_create() {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler)&phase_1,
        (cPhs__Handler)&phase_2,
        NULL,
    };

    return dComLbG_PhaseHandler(&mPhsLoad, l_method, this);
}

/* 00000720-00000A90       .text createHeap__13daObjFigure_cFv */
BOOL daObjFigure_c::createHeap() {
    int roomId = dSnap_GetFigRoomId(getFigureNo());
#if VERSION > VERSION_DEMO
    if(l_figure_dat_tbl[getFigureNo()].mRoomId >= 0) {
        roomId = l_figure_dat_tbl[getFigureNo()].mRoomId;
    }
#endif

    J3DModelData* pModelData;
    const char* arcname = l_arcname_tbl[roomId];
    pModelData = (J3DModelData*)(dComIfG_getObjectIDRes(arcname, getFigureBmd(mFigureNo)));
    if(pModelData == NULL) {
        return false;
    }

    mpModel = mDoExt_J3DModel__create(pModelData, 0x80000, l_figure_dat_tbl[mFigureNo].mModelAttr);
    if(mpModel == NULL) {
        return false;
    }

    if(mFigureNo == 0x3D) {
        J3DAnmTevRegKey* pBrkData = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectIDRes(arcname, FIGURE2_BDL_VF_047));
        if(pBrkData == NULL) {
            return false;
        }

        mpBrkAnm = new mDoExt_brkAnm;
        if(mpBrkAnm == NULL) {
            return false;
        }

        if(!mpBrkAnm->init(pModelData, pBrkData, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0)) {
            return false;
        }
    }
    J3DModelData* pPedestalData;
    if(mFigureNo == 0x40) {
        pPedestalData = (J3DModelData*)dComIfG_getObjectIDRes(arcname, FIGURE2_BDL_VF_044);
        mpMorf = new mDoExt_McaMorf(
            pPedestalData,
            NULL, NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectIDRes(arcname, FIGURE2_BCK_VF_064L),
            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
            NULL,
            0x80000,
#if VERSION == VERSION_DEMO
            0x11000022
#else
            0x11001222
#endif
        );

        if(mpMorf == NULL || mpMorf->getModel() == NULL) {
            return false;
        }

#if VERSION > VERSION_DEMO
        J3DSkinDeform* pDeform = new J3DSkinDeform;
        if(pDeform == NULL) {
            return false;
        }

        if(mpMorf->getModel()->setSkinDeform(pDeform, 1) != J3DErrType_Success) {
            return false;
        }
#endif
    }

    pPedestalData = static_cast<J3DModelData*>(dComIfG_getObjectIDRes("Figure", FIGURE_BDL_VF_BS));
    if(pPedestalData == NULL) {
        return false;
    }

    mpPedestalModel = mDoExt_J3DModel__create(pPedestalData, 0x80000, 0x11020022);
    if(mpPedestalModel == NULL) {
        return false;
    }

    mpPedestalBtp = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectIDRes("Figure", FIGURE_BTP_VF_BS));
    if(mpPedestalBtp == NULL) {
        return false;
    }

    if(!mBtpAnm1.init(pPedestalData, mpPedestalBtp, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE)) {
        return false;
    }

    return true;
}

/* 00000A90-00000BF4       .text createInit__13daObjFigure_cFv */
cPhs_State daObjFigure_c::createInit() {
    mStts.Init(0xFF, 0xFF, this);
    mCyl1.Set(l_cyl_src);
    mCyl1.SetStts(&mStts);
    mCyl2.Set(l_cyl_src);
    mCyl2.SetStts(&mStts);
    mCyl2.SetCoSPrm(0x129);
    mCyl2.SetR(200.0f);
    mCyl2.SetH(100.0f);
    fopAcM_SetMtx(this, mpPedestalModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -50.0f, 0.0f, -50.0f, 50.0f, 200.0f, 50.0f);
    mFigureCheckEvtIdx = dComIfGp_evmng_getEventIdx("FIGURE_CHECK");
    mEventCut.setActorInfo("Figure", this);
    eventInfo.setEventId(mFigureCheckEvtIdx);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA8;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA8;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_TALKFLAG_CHECK_e;
    shape_angle = current.angle;
    dKy_tevstr_init(&mTevStrBG2, fopAcM_GetHomeRoomNo(this), 0xFF);
    cMtx_copy(cMtx_getIdentity(), mMtx);
    setMtx();

    return cPhs_COMPLEATE_e;
}

#if VERSION == VERSION_DEMO
BOOL daObjFigure_c::_delete() {
    if (mLoadFlags & 1) {
        dComIfG_resDeleteDemo(getPhase1P(), "Figure");
    }

    if (mLoadFlags & 2) {
        int id = dSnap_GetFigRoomId(getFigureNo());
        dComIfG_resDeleteDemo(getPhase2P(), l_arcname_tbl[id]);
    }

    return true;
}
#else
/* 00000BF4-00000C78       .text _delete__13daObjFigure_cFv */
BOOL daObjFigure_c::_delete() {
    dComIfG_resDeleteDemo(getPhase1P(), "Figure");

    int id = dSnap_GetFigRoomId(getFigureNo());
    if(l_figure_dat_tbl[getFigureNo()].mRoomId >= 0) {
        id = l_figure_dat_tbl[getFigureNo()].mRoomId;
    }

    dComIfG_resDelete(getPhase2P(), l_arcname_tbl[id]);

    return true;
}
#endif

void linkDraw(mDoExt_McaMorf*);

/* 00000C78-00000DE8       .text _draw__13daObjFigure_cFv */
BOOL daObjFigure_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG2, &current.pos, &mTevStrBG2);
    g_env_light.setLightTevColorType(mpModel, &mTevStrBG2);
#if VERSION == VERSION_DEMO
    if(mpMorf) {
        g_env_light.setLightTevColorType(mpMorf->getModel(), &mTevStrBG2);
    }
#endif
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpPedestalModel, &tevStr);

    J3DModelData* pModelData = mpPedestalModel->getModelData();
    if(mbDisplay) {
        if(mpBrkAnm) {
            J3DModelData* pModelData2 = mpModel->getModelData();
            mpBrkAnm->entry(pModelData2, mpBrkAnm->getFrame());
        }

        mBtpAnm1.entry(pModelData, 1);
        mDoExt_modelUpdateDL(mpPedestalModel);
        mDoExt_modelUpdateDL(mpModel);
        mBtpAnm1.remove(pModelData);

        if(mpBrkAnm) {
            mpBrkAnm->remove(mpModel->getModelData());
        }

        if(mpMorf) {
#if VERSION > VERSION_DEMO
            g_env_light.setLightTevColorType(mpMorf->getModel(), &mTevStrBG2);
#endif
            linkDraw(mpMorf);
        }
    }
    else {
        if(mFigureNo != 0x40 && mFigureNo != 0x32) {
            mBtpAnm1.entry(pModelData, 0);
            mDoExt_modelUpdateDL(mpPedestalModel);
            mBtpAnm1.remove(pModelData);
        }
    }

    return true;
}

typedef void(daObjFigure_c::*ProcFunc_t)();
static const ProcFunc_t moveProc[] = {
    &daObjFigure_c::executeNormal,
};

/* 00000DE8-00000F10       .text _execute__13daObjFigure_cFv */
BOOL daObjFigure_c::_execute() {
    if(!dComIfGp_event_runCheck()) {
        (this->*moveProc[m73C])();
    }
    else {
        eventMove();
    }

    if(mbDisplay || (getFigureNo() != 0x40 && getFigureNo() != 0x32)) {
        mCyl1.SetC(current.pos);
        mCyl2.SetC(current.pos);
        dComIfG_Ccsp()->Set(&mCyl1);
        dComIfG_Ccsp()->Set(&mCyl2);
    }

    attention_info.position.set(current.pos.x, current.pos.y + 200.0f, current.pos.z);
    eyePos.set(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    if(mpBrkAnm) {
        mpBrkAnm->play();
    }

    setMtx();

    return true;
}

/* 00000F10-00000FD4       .text executeNormal__13daObjFigure_cFv */
void daObjFigure_c::executeNormal() {
    if(mbDisplay) {
        fopAc_ac_c* pLink = dComIfGp_getLinkPlayer();

        f32 f31 = 150.0f;
        int r31 = 13000;
        f32 temp1;
        s16 temp2;
        dNpc_calc_DisXZ_AngY(current.pos, pLink->current.pos, &temp1, &temp2);
        temp2 -= current.angle.y;

        if(f31 > temp1 && r31 > abs(temp2)) {
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
        }
    }
}

/* 00000FD4-00001060       .text eventMove__13daObjFigure_cFv */
void daObjFigure_c::eventMove() {
    if(dComIfGp_evmng_endCheck(mFigureCheckEvtIdx)) {
        dComIfGp_event_reset();
    }
    else {
        bool attn = mEventCut.getAttnFlag();
        if (mEventCut.cutProc()) {
            if (!mEventCut.getAttnFlag()) {
                mEventCut.setAttnFlag(attn);
            }
        } else {
            privateCut();
        }
    }
}

/* 00001060-0000119C       .text privateCut__13daObjFigure_cFv */
void daObjFigure_c::privateCut() {
    static char* cut_name_tbl[] = {
        "MES_SET",
        "ON_PLR",
        "OFF_PLR",
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId("Figure");
    if(staffIdx != -1) {
        m741 = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
        if(m741 == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
        else {
            if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch(m741) {
                    case 0:
                        eventMesSetInit(staffIdx);
                        break;
                    case 1:
                        eventOnPlrInit();
                        break;
                    case 2:
                        eventOffPlrInit();
                        break;
                }
            }

            bool end;
            switch(m741) {
                case 0:
                    end = eventMesSet();
                    break;
                default:
                    end = true;
                    break;
            }

            if(end) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }
        }
    }
}

/* 0000119C-00001294       .text eventMesSetInit__13daObjFigure_cFi */
void daObjFigure_c::eventMesSetInit(int staffIdx) {
    int* pMsgNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    if(pMsgNo) {
        m72C = NULL;
        switch(*pMsgNo) {
            case 0:
                setMessage(getMsg());
                break;
            case 1:
                break;
            default:
                setMessage(*pMsgNo);
                break;
        }

        if(m72C) {
            setMessage(*m72C);
        }
    }
    else {
        m72C++;
        setMessage(*m72C);
    }

    m724 = l_figure_check_tbl[0].field_0x18;
    m728 = l_figure_check_tbl[0].field_0x08;
    m738 = 0;
    m73F = 0;
    m73A = 10;
}

/* 00001294-00001600       .text eventMesSet__13daObjFigure_cFv */
bool daObjFigure_c::eventMesSet() {
    switch(m73F) {
        case 0: {
            if(m73A != 0) {
                m73A--;
            }
            else {
                dComIfGp_setDoStatusForce(dActStts_INFO_e);
                dComIfGp_setAStatusForce(dActStts_CANCEL_e);
                if(g_mDoCPd_cpadInfo[0].mMainStickPosX || g_mDoCPd_cpadInfo[0].mMainStickPosY || g_mDoCPd_cpadInfo[0].mCStickPosY) {
                    m738 = l_figure_check_tbl[0].field_0x32;
                    m734 += (s16)(g_mDoCPd_cpadInfo[0].mMainStickPosX * l_figure_check_tbl[0].field_0x2C);
                    m728 += (s16)(g_mDoCPd_cpadInfo[0].mMainStickPosY * l_figure_check_tbl[0].field_0x04);

                    if(m728 < l_figure_check_tbl[0].field_0x0C) {
                        m728 = l_figure_check_tbl[0].field_0x0C;
                    }
                    else if(m728 > l_figure_check_tbl[0].field_0x10) {
                        m728 = l_figure_check_tbl[0].field_0x10;
                    }

                    m724 -= g_mDoCPd_cpadInfo[0].mCStickPosY * l_figure_check_tbl[0].field_0x1C;
                    if(m724 < l_figure_check_tbl[0].field_0x20) {
                        m724 = l_figure_check_tbl[0].field_0x20;
                    }
                    else if(m724 > l_figure_check_tbl[0].field_0x24) {
                        m724 = l_figure_check_tbl[0].field_0x24;
                    }
                }
                else {
                    if(m738 != 0) {
                        m738--;
                    }
                    else {
                        m736 += l_figure_check_tbl[0].field_0x28;
                    }
                }

                dComIfGp_setDoStatusForce(dActStts_INFO_e);
                dComIfGp_setAStatusForce(dActStts_CANCEL_e);
                if(CPad_CHECK_TRIG_B(0)) {
                    m732 = 0;
                    m734 = 0;
                    m736 = current.angle.y;

                    return true;
                }

                if(CPad_CHECK_TRIG_A(0)) {
                    m73F = 1;
                }
            }

            f32 temp = m728 + l_figure_check_tbl[0].field_0x14;
            m70C.set(0.0f, temp, 0.0f);
            temp = m728 + l_figure_check_tbl[0].field_0x14;
            m718.x = 0.0f;
            m718.y = temp;
            m718.z = l_figure_check_tbl[0].field_0x00;
            mDoMtx_stack_c::YrotS(current.angle.y + m734);
            mDoMtx_stack_c::multVec(&m718, &m718);
            m70C += current.pos;
            m718 += current.pos;
            dCam_getBody()->Set(m70C, m718, m724, 0);

            break;
        }
        case 1:
            talk(0);
            if(m694 != fpcM_ERROR_PROCESS_ID_e) {
                m73F = 2;
            }

            break;
        case 2:
            if(talk(0) == fopMsgStts_BOX_CLOSED_e) {
                m73F = 0;
            }

            break;
    }

    return false;
}

/* 00001600-00001658       .text eventOnPlrInit__13daObjFigure_cFv */
void daObjFigure_c::eventOnPlrInit() {
    ((daPy_lk_c*)dComIfGp_getLinkPlayer())->offPlayerNoDraw();
    dCam_getBody()->Reset();
    dCam_getBody()->Start();
    dComIfGs_offTmpBit(0x408);
}

/* 00001658-000016A8       .text eventOffPlrInit__13daObjFigure_cFv */
void daObjFigure_c::eventOffPlrInit() {
    ((daPy_lk_c*)dComIfGp_getLinkPlayer())->onPlayerNoDraw();
    dCam_getBody()->Stop();
    dComIfGs_onTmpBit(0x408);
}

/* 000016A8-00001788       .text talk__13daObjFigure_cFi */
u16 daObjFigure_c::talk(int param_1) {
    u16 msgStatus = 0xFF;

    if(m694 == fpcM_ERROR_PROCESS_ID_e) {
        if(param_1 == 1) {
            m69C = getMsg();
        }
        
        m694 = fopMsgM_messageSet(m69C, this);
        mpCurrMsg = NULL;
    }
    else {
        if(mpCurrMsg) {
            msgStatus = mpCurrMsg->mStatus;

            if (msgStatus == fopMsgStts_MSG_DISPLAYED_e) {
                mpCurrMsg->mStatus = next_msgStatus(&m69C);
                if(mpCurrMsg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_messageSet(m69C);
                }
            }
            else if (msgStatus == fopMsgStts_BOX_CLOSED_e) {
                mpCurrMsg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                m694 = fpcM_ERROR_PROCESS_ID_e;
            }
        }
        else {
            mpCurrMsg = fopMsgM_SearchByID(m694);
        }
    }

    return msgStatus;
}

/* 00001788-000017D8       .text next_msgStatus__13daObjFigure_cFPUl */
u16 daObjFigure_c::next_msgStatus(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;

    if(m72C) {
        m72C++;
        switch(*m72C) {
            case 0:
                m72C = NULL;
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
            default:
                *pMsgNo = *m72C;
                break;
        }
    }
    else {
        msgStatus = fopMsgStts_MSG_ENDS_e;
    }

    return msgStatus;
}

/* 000017D8-000017EC       .text getMsg__13daObjFigure_cFv */
u32 daObjFigure_c::getMsg() {
    m72C = NULL;

    return 0x37DD + getFigureNo();
}

/* 000017EC-000017FC       .text setMessage__13daObjFigure_cFUl */
void daObjFigure_c::setMessage(u32 msgNo) {
    m694 = fpcM_ERROR_PROCESS_ID_e;
    m69C = msgNo;
}

/* 000017FC-00001828       .text getPrmFigureNo__13daObjFigure_cFv */
u8 daObjFigure_c::getPrmFigureNo() {
    return daObj::PrmAbstract<Prm_e>(this, PRM_FIGURE_NO_W, PRM_FIGURE_NO_S);
}

/* 00001828-00001954       .text setMtx__13daObjFigure_cFv */
void daObjFigure_c::setMtx() {
    mpPedestalModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpPedestalModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cXyz scale(1.0f, 1.0f, 1.0f);
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + 100.0f, current.pos.z);
    mDoMtx_stack_c::YrotM(m736);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

    if(mpMorf) {
        mpMorf->getModel()->setBaseScale(scale);
        mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    }

}

/* 00001954-000019DC       .text isFigureGet__13daObjFigure_cFUc */
u8 daObjFigure_c::isFigureGet(u8 figureNo) {
    if(figureNo / 8 < 0x11) {
        int r31 = (figureNo % 8);
        u8 reg = dComIfGs_getEventReg(l_figure_comp[figureNo / 8]);
        u32 ret = reg & (1 << r31);
        return ret;
    }

    return false;
}

/* 000019DC-00001A80       .text getFigureBmd__13daObjFigure_cFUc */
int daObjFigure_c::getFigureBmd(u8 figureNo) {
    u32 bmd = l_figure_dat_tbl[figureNo].mBmdId;
    switch(figureNo) {
        case 0x10:
            if(dComIfGs_isEventBit(0x2D01)) {
                bmd = 3;
            }

            break;
        case 0x12:
            if(dComIfGs_isEventBit(0x2D01)) {
                bmd = 6;
            }

            break;
        default:
            break;
    }
    
    return bmd;
}

/* 00001A80-00001AA0       .text daSampleCreate__FPv */
static cPhs_State daSampleCreate(void* i_this) {
    return static_cast<daObjFigure_c*>(i_this)->_create();
}

/* 00001AA0-00001AC0       .text daSampleDelete__FPv */
static BOOL daSampleDelete(void* i_this) {
    return static_cast<daObjFigure_c*>(i_this)->_delete();
}

/* 00001AC0-00001AE0       .text daSampleExecute__FPv */
static BOOL daSampleExecute(void* i_this) {
    return static_cast<daObjFigure_c*>(i_this)->_execute();
}

/* 00001AE0-00001B00       .text daSampleDraw__FPv */
static BOOL daSampleDraw(void* i_this) {
    return static_cast<daObjFigure_c*>(i_this)->_draw();
}

/* 00001B00-00001B08       .text daSampleIsDelete__FPv */
static BOOL daSampleIsDelete(void*) {
    return true;
}

/* 00001B08-00002148       .text linkDraw__FP14mDoExt_McaMorf */
void linkDraw(mDoExt_McaMorf* pMorf) {
    pMorf->calc();
#if VERSION > VERSION_DEMO
    J3DModel* model = pMorf->getModel();
    J3DModelData* modelData = model->getModelData();
    j3dSys.setModel(model);
    j3dSys.setTexture(modelData->getTexture());
    model->unlock();
#endif

    static mDoExt_offCupOnAupPacket l_offCupOnAupPacket1;
    static mDoExt_offCupOnAupPacket l_offCupOnAupPacket2;
    static mDoExt_onCupOffAupPacket l_onCupOffAupPacket1;
    static mDoExt_onCupOffAupPacket l_onCupOffAupPacket2;

    J3DShape* ZOffBlendShape[4];
    J3DShape* ZOffNoneShape[4];
    J3DShape* ZOnShape[4];

#if VERSION == VERSION_DEMO
    J3DModel* model = pMorf->getModel();
    J3DModelData* modelData = model->getModelData();
#endif

    J3DJoint* link_root_joint = modelData->getJointNodePointer(0x00); // link_root joint
    J3DJoint* cl_eye_joint = modelData->getJointNodePointer(0x13);    // cl_eye joint
    J3DJoint* cl_mayu_joint = modelData->getJointNodePointer(0x15);   // cl_mayu joint

    J3DMaterial* mtl;
    mtl = modelData->getJointNodePointer(0x13)->getMesh(); // cl_eye joint
    int zoff_blend_cnt = 0;
    int zoff_none_cnt = 0;
    int zon_cnt = 0;
    int i;
    for (i = 0; i < 2; i++) {
        while (mtl) {
            mtl->setMaterialMode(1);
            if (mtl->getZMode()->getCompareEnable() == 0) {
                if ((u8)mtl->getBlend()->getType() == GX_BM_BLEND) {
                    ZOffBlendShape[zoff_blend_cnt++] = mtl->getShape();
                    JUT_ASSERT(DEMO_SELECT(1713, 1767), zoff_blend_cnt <= 4);
                } else {
                    ZOffNoneShape[zoff_none_cnt++] = mtl->getShape();
                    JUT_ASSERT(DEMO_SELECT(1717, 1770), zoff_none_cnt <= 4);
                }
            } else {
                ZOnShape[zon_cnt++] = mtl->getShape();
                JUT_ASSERT(DEMO_SELECT(1722, 1774), zon_cnt <= 4);
            }
            mtl = mtl->getNext();
        }
        mtl = modelData->getJointNodePointer(0x15)->getMesh(); // cl_mayu joint
    }

    dComIfGd_setListP0();
    l_onCupOffAupPacket2.entryOpa();

    for (i = 0; i < 4; i++) {
        ZOffBlendShape[i]->hide();
        ZOnShape[i]->hide();
        ZOffNoneShape[i]->show();
    }

    cl_eye_joint->entryIn();
    cl_mayu_joint->entryIn();
    l_offCupOnAupPacket2.entryOpa();

    for (i = 0; i < 4; i++) {
        ZOffBlendShape[i]->show();
        ZOffNoneShape[i]->hide();
    }

    cl_eye_joint->entryIn();
    cl_mayu_joint->entryIn();

    mtl = link_root_joint->getMesh();
    for (i = 0; mtl != NULL; i++, mtl = mtl->getNext()) {
        if (i != 2 && i != 5) {
            mtl->getShape()->hide();
        }
    }

    link_root_joint->entryIn();

#if VERSION > VERSION_DEMO
    for (i = 0, mtl = link_root_joint->getMesh(); mtl != NULL; i++, mtl = mtl->getNext()) {
        if (i != 2 && i != 5) {
            mtl->getShape()->show();
        } else {
            mtl->getShape()->hide();
        }
    }
#endif

    l_onCupOffAupPacket1.entryOpa();

    for (i = 0; i < 4; i++) {
        ZOffBlendShape[i]->hide();
        ZOnShape[i]->show();
        ZOffNoneShape[i]->hide();
    }

    cl_eye_joint->entryIn();
    cl_mayu_joint->entryIn();

    l_offCupOnAupPacket1.entryOpa();

    for (i = 0; i < 4; i++) {
        ZOnShape[i]->hide();
    }

#if VERSION == VERSION_DEMO
    pMorf->entryDL();
#else
    dComIfGd_setList();
    mDoExt_modelEntryDL(pMorf->getModel());
#endif

    for (mtl = link_root_joint->getMesh(); mtl != NULL; mtl = mtl->getNext()) {
        mtl->getShape()->show();
    }

    modelData->getJointNodePointer(0x14)->getMesh()->getShape()->show(); // cl_hana joint
    modelData->getJointNodePointer(0x29)->getMesh()->getShape()->show(); // cl_back joint

#if VERSION == VERSION_DEMO
    dComIfGd_setList();
#endif
}

static actor_method_class daSampleMethodTable = {
    (process_method_func)daSampleCreate,
    (process_method_func)daSampleDelete,
    (process_method_func)daSampleExecute,
    (process_method_func)daSampleIsDelete,
    (process_method_func)daSampleDraw,
};

actor_process_profile_definition g_profile_OBJ_FIGURE = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_FIGURE,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjFigure_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_FIGURE,
    /* Actor SubMtd */ &daSampleMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
