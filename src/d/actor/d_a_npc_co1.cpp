/**
 * d_a_npc_co1.cpp
 * NPC - Prince Komali (before Dragon Roost Cavern)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_co1.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Co.h"

class daNpc_Co1_HIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ s16 mMaxHeadX;
        /* 0x02 */ s16 mMaxHeadY;
        /* 0x04 */ s16 mMinHeadX;
        /* 0x06 */ s16 mMinHeadY;
        /* 0x08 */ s16 mMaxBackboneX;
        /* 0x0A */ s16 mMaxBackboneY;
        /* 0x0C */ s16 mMinBackboneX;
        /* 0x0E */ s16 mMinBackboneY;
        /* 0x10 */ s16 mMaxTurnStep;
        /* 0x12 */ s16 mMaxHeadTurnVel;
        /* 0x14 */ f32 mAttPosOffsetY;
        /* 0x18 */ u8 m18;
        /* 0x1A */ s16 mLightColorR;
        /* 0x1C */ s16 mLightColorG;
        /* 0x1E */ s16 mLightColorB;
        /* 0x20 */ f32 mLightPowerMax;
        /* 0x24 */ f32 mLightPowerMin;
        /* 0x28 */ s16 mGlowSpeed;
        /* 0x2A */ s16 mGlowColorMin;
    };  // Size: 0x2C

    daNpc_Co1_HIO_c();
    virtual ~daNpc_Co1_HIO_c() {}
    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int m8;
    /* 0x0C */ hio_prm_c mPrm;
};  // Size: 0x38

/* 000000EC-00000150       .text __ct__15daNpc_Co1_HIO_cFv */
daNpc_Co1_HIO_c::daNpc_Co1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        /* mMaxHeadX       */ 0x2000,
        /* mMaxHeadY       */ 0x2328,
        /* mMinHeadX       */ -0x2000,
        /* mMinHeadY       */ -0x2328,
        /* mMaxBackboneX   */ 0x0000,
        /* mMaxBackboneY   */ 0x0000,
        /* mMinBackboneX   */ 0x0000,
        /* mMinBackboneY   */ 0x0000,
        /* mMaxTurnStep    */ 0x0400,
        /* mMaxHeadTurnVel */ 0x0400,
        /* mAttPosOffsetY  */ 91.0f,
        /* m18             */ 0,
        /* mLightColorR    */ 0xFF,
        /* mLightColorG    */ 0x96,
        /* mLightColorB    */ 0x00,
        /* mLightPowerMax  */ 40.0f,
        /* mLightPowerMin  */ 20.0f,
        /* mGlowSpeed      */ 0x200,
        /* mGlowColorMin   */ 0x40,
    };
    memcpy(&mPrm, &a_prm_tbl, sizeof(hio_prm_c));
    mNo = -1;
    m8 = -1;
}

static daNpc_Co1_HIO_c l_HIO;

static char* l_evn_tbl[] = {
    "Prl_Flw",
    "Contact",
    "Red_Ltr",
};

/* 00000198-000001E4       .text nodeCallBack_Co1__FP7J3DNodei */
static BOOL nodeCallBack_Co1(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        if (j3dSys.getModel()->getUserArea() != 0) {
            ((daNpc_Co1_c*)j3dSys.getModel()->getUserArea())->nodeCo1Control(i_node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-00000334       .text nodeCo1Control__11daNpc_Co1_cFP7J3DNodeP8J3DModel */
void daNpc_Co1_c::nodeCo1Control(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(14.0f, 18.0f, 0.0f);

    s32 jnt_no = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    if (jnt_no == m_hed_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);
    }
    if (jnt_no == m_bbone_jnt_num) {
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    }
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000370-00000408       .text init_CO1_0__11daNpc_Co1_cFv */
bool daNpc_Co1_c::init_CO1_0() {
    bool ret = dComIfGs_isSymbol(1) == 0;
    if (ret) {
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
        set_action(&daNpc_Co1_c::wait_action1, NULL);
    }
    return ret;
}

/* 00000408-000005D8       .text createInit__11daNpc_Co1_cFv */
bool daNpc_Co1_c::createInit() {
    for (int i = 0; i < ARRAY_SSIZE(mEventIdTbl); i++) {
        mEventIdTbl[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i], 0xFF);
    }

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x46;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x45;
    gravity = -4.5f;
    mLookPos = current.pos;
    mbHeadOnly = true;

    mEventCut.setActorInfo2("Co1", this);
    mAnmNum = 11;

    bool init_result;
    switch (mType) {
    case 0:
        init_result = init_CO1_0();
        break;
    default:
        init_result = false;
        break;
    }

    if (init_result) {
        shape_angle = current.angle;
    } else {
        return false;
    }
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 000005D8-000008D4       .text setMtx__11daNpc_Co1_cFb */
void daNpc_Co1_c::setMtx(bool i_setEyePos) {
    if (!mbDemo) {
        plyTexPttrnAnm();
        mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);
        mpPrlMorf->setFrame(mpMorf->getFrame());
        if (mpMorf->getFrame() < mPrevMorfFrame) {
            mbMorfAnimStopped = true;
        }
        mPrevMorfFrame = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        switch (mAnmNum) {
        case 8:
            mbShowItem = mpMorf->getFrame() >= 15.0f;
            break;
        case 4:
            mbShowItem = true;
            break;
        default:
            mbShowItem = false;
            break;
        }
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();

    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_bbone_jnt_num));
    mpPrlMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpPrlMorf->calc();

    if (mbShowItem) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num));
        mpItemModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpItemModel->calc();
    }

    mDoMtx_stack_c::copy(mpPrlMorf->getModel()->getAnmMtx(m_prl_jnt_num));
    mPearlPos.x = mDoMtx_stack_c::get()[0][3];
    mPearlPos.y = mDoMtx_stack_c::get()[1][3];
    mPearlPos.z = mDoMtx_stack_c::get()[2][3];
    mLight.mPos = mPearlPos;
    mLight.mColor.r = l_HIO.mPrm.mLightColorR;
    mLight.mColor.g = l_HIO.mPrm.mLightColorG;
    mLight.mColor.b = l_HIO.mPrm.mLightColorB;
    mGlowPhase += l_HIO.mPrm.mGlowSpeed;
    mGlow = std::fabsf(cM_ssin(mGlowPhase));
    f32 range = cLib_minLimit<f32>(l_HIO.mPrm.mLightPowerMax - l_HIO.mPrm.mLightPowerMin, 0.0f);
    mLight.mPower = cLib_minLimit<f32>(l_HIO.mPrm.mLightPowerMin + range * mGlow, 0.001f);
    setAttention(i_setEyePos);
}

/* 000008D4-000008E8       .text anmNum_toResID__11daNpc_Co1_cFi */
int daNpc_Co1_c::anmNum_toResID(int i_anmNum) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_CO_BCK_CO_WAIT01_e,
        dRes_ID_CO_BCK_CO_WAIT02_e,
        dRes_ID_CO_BCK_CO_MIGAMAE_e,
        dRes_ID_CO_BCK_CO_OKIRU_e,
        dRes_ID_CO_BCK_CO_READ_e,
        dRes_ID_CO_BCK_CO_TALK01_e,
        dRes_ID_CO_BCK_CO_TALK02_e,
        dRes_ID_CO_BCK_CO_SWAIT01_e,
        dRes_ID_CO_BCK_CO_UKETORI_e,
        dRes_ID_CO_BCK_CO_OKIRU_e,
        dRes_ID_CO_BCK_CO_MIGAMAE_e,
    };
    return a_bck_resID_tbl[i_anmNum];
}

/* 000008E8-000008FC       .text anmNum_toResID_prl__11daNpc_Co1_cFi */
int daNpc_Co1_c::anmNum_toResID_prl(int i_anmNum) {
    static const int a_bck_resID_tbl[] = {
        dRes_ID_CO_BCK_COPEAL_WAIT01_e,
        dRes_ID_CO_BCK_COPEAL_WAIT02_e,
        dRes_ID_CO_BCK_COPEAL_MIGAMAE_e,
        dRes_ID_CO_BCK_COPEAL_OKIRU_e,
        dRes_ID_CO_BCK_COPEAL_READ_e,
        dRes_ID_CO_BCK_COPEAL_TALK01_e,
        dRes_ID_CO_BCK_COPEAL_TALK02_e,
        dRes_ID_CO_BCK_COPEAL_SWAIT01_e,
        dRes_ID_CO_BCK_COPEAL_UKETORI_e,
        dRes_ID_CO_BCK_COPEAL_OKIRU_e,
        dRes_ID_CO_BCK_COPEAL_MIGAMAE_e,
    };
    return a_bck_resID_tbl[i_anmNum];
}

/* 000008FC-00000910       .text btpNum_toResID__11daNpc_Co1_cFi */
int daNpc_Co1_c::btpNum_toResID(int i_btpNum) {
    static const int a_btp_resID_tbl[] = {
        dRes_ID_CO_BTP_FUAN_e,
        dRes_ID_CO_BTP_KIRI_e,
        dRes_ID_CO_BTP_NIKO_e,
        dRes_ID_CO_BTP_OKORI_e,
        dRes_ID_CO_BTP_NAGAME_e,
        dRes_ID_CO_BTP_OKIRU_e,
        dRes_ID_CO_BTP_MIGAMAE_e,
    };
    return a_btp_resID_tbl[i_btpNum];
}

/* 00000910-00000A20       .text setBtp__11daNpc_Co1_cFbi */
bool daNpc_Co1_c::setBtp(bool i_modify, int i_btpNum) {
    J3DModelData* model_data = mpMorf->getModel()->getModelData();
    m_hed_tex_pttrn = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Co", btpNum_toResID(i_btpNum));
    JUT_ASSERT(0x1CE, m_hed_tex_pttrn != NULL);

    bool ret = mBtpAnm.init(model_data, m_hed_tex_pttrn, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, 0) == 1;
    if (ret) {
        mBtpFrame = 0;
        mBlinkTimer = 0;
    }
    return ret;
}

/* 00000A20-00000B1C       .text setBtk__11daNpc_Co1_cFb */
bool daNpc_Co1_c::setBtk(bool i_modify) {
    J3DModelData* model_data = mpPrlMorf->getModel()->getModelData();
    m_prl_btk = (J3DAnmTextureSRTKey*)dComIfG_getObjectIDRes("Co", dRes_ID_CO_BTK_CO_PEAL_e);
    JUT_ASSERT(0x1EA, m_prl_btk != NULL);

    bool ret = mBtkAnm.init(model_data, m_prl_btk, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, 0) == 1;
    if (ret) {
        mBtkFrame = 0;
    }
    return ret;
}

/* 00000B1C-00000B44       .text iniTexPttrnAnm__11daNpc_Co1_cFb */
bool daNpc_Co1_c::iniTexPttrnAnm(bool i_modify) {
    return setBtp(i_modify, mBtpNum);
}

/* 00000B44-00000C34       .text plyTexPttrnAnm__11daNpc_Co1_cFv */
void daNpc_Co1_c::plyTexPttrnAnm() {
    mBtkFrame++;
    if (mBtkFrame >= m_prl_btk->getFrameMax()) {
        mBtkFrame = 0;
    }
    if (mBtpNum == 6 || mBtpNum == 5 || !cLib_calcTimer(&mBlinkTimer)) {
        mBtpFrame++;
        if (mBtpFrame >= m_hed_tex_pttrn->getFrameMax()) {
            if (mBtpNum == 6 || mBtpNum == 5) {
                mBtpFrame = m_hed_tex_pttrn->getFrameMax();
            } else {
                mBlinkTimer = 30.0f + cM_rndF(60.0f);
                mBtpFrame = 0;
            }
        }
    }
}

/* 00000C34-00000C70       .text setAnm_tex__11daNpc_Co1_cFSc */
void daNpc_Co1_c::setAnm_tex(s8 i_btpNum) {
    if (mBtpNum != i_btpNum) {
        mBtpNum = i_btpNum;
        iniTexPttrnAnm(true);
    }
}

/* 00000C70-00000D64       .text setAnm_anm__11daNpc_Co1_cFPQ211daNpc_Co1_c9anm_prm_c */
BOOL daNpc_Co1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (mAnmNum == i_anmPrmP->mAnmNum) {
        return TRUE;
    }
    mAnmNum = i_anmPrmP->mAnmNum;
    int res_id = anmNum_toResID(mAnmNum);
    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->mLoopMode, i_anmPrmP->mMorf, i_anmPrmP->mSpeed, res_id, -1, "Co");
    res_id = anmNum_toResID_prl(mAnmNum);
    dNpc_setAnmIDRes(mpPrlMorf, i_anmPrmP->mLoopMode, 0.0f, 0.0f, res_id, -1, "Co");
    mPrevMorfFrame = 0.0f;
    m809 = 0;
    mbMorfAnimStopped = 0;
    return TRUE;
}

/* 00000D64-00000DD0       .text setAnm_NUM__11daNpc_Co1_cFii */
void daNpc_Co1_c::setAnm_NUM(int i_anmNum, int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[12] = {
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 6, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {3, 5, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {4, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 3, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {7, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {8, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {9, 5, 8.0f, -1.0f, J3DFrameCtrl::EMode_NONE},
        {10, 6, 8.0f, -1.0f, J3DFrameCtrl::EMode_NONE},
        {7, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    if (i_setBtp) {
        setAnm_tex(a_anm_prm_tbl[i_anmNum].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* 00000DD0-00000E50       .text setAnm__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[8] = {
        {-1, -1, 0.0f, 0.0f, -1},
        {1, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, -1},
        {3, 5, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {7, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, -1},
        {4, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {10, 6, 8.0f, -1.0f, J3DFrameCtrl::EMode_NONE},
    };
    if (a_anm_prm_tbl[mStt].mBtpNum >= 0) {
        setAnm_tex(a_anm_prm_tbl[mStt].mBtpNum);
    }
    if (a_anm_prm_tbl[mStt].mAnmNum >= 0) {
        setAnm_anm(&a_anm_prm_tbl[mStt]);
    }
    return TRUE;
}

/* 00000E50-00000E54       .text chg_anmTag__11daNpc_Co1_cFv */
void daNpc_Co1_c::chg_anmTag() {}

/* 00000E54-00000E58       .text control_anmTag__11daNpc_Co1_cFv */
void daNpc_Co1_c::control_anmTag() {}

/* 00000E58-00000EF8       .text chg_anmAtr__11daNpc_Co1_cFUc */
void daNpc_Co1_c::chg_anmAtr(u8 i_atr) {
    if (i_atr >= 14 || i_atr == mAnmAtr) {
        return;
    }
    mLookMode = 1;
    switch (i_atr) {
    case 3:
    case 4:
    case 5:
    case 7:
    case 11:
        mLookMode = 0;
        break;
    case 13:
        set_target(1);
        break;
    }
    mAnmAtr = i_atr;
    setAnm_ATR(1);
}

/* 00000EF8-00000FF4       .text control_anmAtr__11daNpc_Co1_cFv */
void daNpc_Co1_c::control_anmAtr() {
    switch (mAnmAtr) {
    case 2:
        if (mbMorfAnimStopped) {
            setAnm_NUM(7, 1);
            mAnmAtr = 6;
        }
        break;
    case 3:
        if (mbMorfAnimStopped) {
            setAnm_NUM(4, 1);
            mAnmAtr = 10;
        }
        break;
    case 7:
        if (mbMorfAnimStopped) {
            setAnm_NUM(6, 1);
            mAnmAtr = 5;
        }
        break;
    case 8:
        if (mbMorfAnimStopped) {
            setAnm_NUM(7, 1);
            mAnmAtr = 6;
        }
        break;
    case 9:
        if (mbMorfAnimStopped) {
            setAnm_NUM(1, 1);
            mAnmAtr = 1;
        }
        break;
    case 13:
        break;
    }
}

/* 00000FF4-0000105C       .text setAnm_ATR__11daNpc_Co1_cFi */
void daNpc_Co1_c::setAnm_ATR(int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[14] = {
        {0, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {1, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {3, 5, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {8, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {5, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 3, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {7, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {2, 6, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {10, 6, 8.0f, -1.0f, J3DFrameCtrl::EMode_NONE},
        {9, 5, 8.0f, -1.0f, J3DFrameCtrl::EMode_NONE},
        {4, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 4, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {5, 0, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {6, 3, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };
    if (i_setBtp != 0) {
        setAnm_tex(a_anm_prm_tbl[mAnmAtr].mBtpNum);
    }
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 0000105C-00001120       .text anmAtr__11daNpc_Co1_cFUs */
void daNpc_Co1_c::anmAtr(u16 i_msgStatus) {
    u32 mesg_anime_tag;
    switch (i_msgStatus) {
    case fopMsgStts_MSG_TYPING_e:
        if (mMsgCount == 0) {
            mAnmAtr = 0xFF;
            chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
            mMsgCount++;
        }
        mesg_anime_tag = dComIfGp_getMesgAnimeTagInfo();
        dComIfGp_clearMesgAnimeTagInfo();
        if (mesg_anime_tag != 0xFF && mMesgAnimeTag != mesg_anime_tag) {
            mMesgAnimeTag = mesg_anime_tag;
            chg_anmTag();
        }
        break;
    case fopMsgStts_MSG_DISPLAYED_e:
        mMsgCount = 0;
        break;
    default:
        break;
    }
    control_anmTag();
    control_anmAtr();
}

/* 00001120-000011B8       .text eventOrder__11daNpc_Co1_cFv */
void daNpc_Co1_c::eventOrder() {
    s8 order = mOrder;
    if (order == 1 || order == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (mOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (order >= 3) {
        mEventIdx = order - 3;
        fopAcM_orderOtherEventId(this, mEventIdTbl[mEventIdx]);
    }
}

/* 000011B8-00001288       .text checkOrder__11daNpc_Co1_cFv */
void daNpc_Co1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(mEventIdTbl[mEventIdx])) {
            switch (mEventIdx) {
            case 0:
                break;
            case 1:
                fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
                break;
            case 2:
                mLookMode = 0;
                break;
            }
            mOrder = 0;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (mOrder == 1 || mOrder == 2) {
            mOrder = 0;
            mbTalkReq = true;
        }
    }
}

/* 00001288-000013A0       .text setCollision_SP___11daNpc_Co1_cFv */
void daNpc_Co1_c::setCollision_SP_() {
    if (mbTalkReq) {
        return;
    }

    cXyz pos;
    f32 radius;
    f32 height;
    if (mAnmNum == 1) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
        cXyz offset(0.0f, 0.0f, -20.0f);
        radius = 70.0f;
        height = 60.0f;
        mDoMtx_stack_c::multVec(&offset, &pos);
    } else {
        pos.set(current.pos.x, current.pos.y, current.pos.z);
        radius = 40.0f;
        height = 90.0f;
    }
    mCyl.SetC(pos);
    mCyl.SetR(radius);
    mCyl.SetH(height);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* 000013A0-000014B4       .text set_target__11daNpc_Co1_cFi */
void daNpc_Co1_c::set_target(int i_type) {
    switch (i_type) {
    case 0:
        mLookMode = 0;
        break;
    case 1: {
        cXyz pos = dNpc_playerEyePos(-20.0f);
        f32 dist = fopAcM_searchActorDistance(this, dComIfGp_getPlayer(0));
        s16 angle = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
        mDoMtx_stack_c::transS(current.pos.x, pos.y, current.pos.z);
        mDoMtx_YrotM(mDoMtx_stack_c::get(), angle -= 0x2000);
        pos.set(0.0f, 0.0f, dist);
        mDoMtx_stack_c::multVec(&pos, &mLookPos);
        mLookMode = 2;
        break;
    }
    }
}

/* 000014B4-0000154C       .text chk_talk__11daNpc_Co1_cFv */
bool daNpc_Co1_c::chk_talk() {
    bool ret = true;
    mItemNo = 0xFF;
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
        } else {
            ret = false;
        }
    }
    return ret;
}

/* 0000154C-0000158C       .text chk_partsNotMove__11daNpc_Co1_cFv */
bool daNpc_Co1_c::chk_partsNotMove() {
    return mJointHeadY == m_jnt.getHead_y() && mJointBackboneY == m_jnt.getBackbone_y() && mActorAngleY == current.angle.y;
}

/* 0000158C-0000172C       .text lookBack__11daNpc_Co1_cFv */
void daNpc_Co1_c::lookBack() {
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    mJointHeadY = m_jnt.getHead_y();
    mJointBackboneY = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f, 0.0f, 0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = mbHeadOnly;

    switch (mLookMode) {
    case 1:
        dstPos = dNpc_playerEyePos(-20.0f);
        dstPos_p = &dstPos;
        src_pos.x = current.pos.x;
        src_pos.y = current.pos.y;
        src_pos.z = current.pos.z;
        src_pos.y = eyePos.y;
        break;
    case 2:
        dstPos.set(mLookPos);
        dstPos_p = &dstPos;
        src_pos.x = current.pos.x;
        src_pos.y = current.pos.y;
        src_pos.z = current.pos.z;
        src_pos.y = eyePos.y;
        break;
    case 3:
        desiredYrot = mTargetAngleY;
        break;
    }
    cLib_addCalcAngleS2(&mLookAtMaxVel, l_HIO.mPrm.mMaxHeadTurnVel, 4, 0x800);
    if (!m_jnt.trnChk()) {
        mLookAtMaxVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos_p, src_pos, desiredYrot, mLookAtMaxVel, headOnlyFollow);
}

/* 0000172C-000017F4       .text next_msgStatus__11daNpc_Co1_cFPUl */
u16 daNpc_Co1_c::next_msgStatus(u32* o_msgNoP) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_msgNoP) {
    case 0x183E:
        *o_msgNoP = 0x183F;
        break;
    case 0x183F:
        *o_msgNoP = 0x1840;
        break;
    case 0x1841:
        *o_msgNoP = 0x1842;
        break;
    case 0x1842:
        *o_msgNoP = 0x1843;
        break;
    case 0x1843:
        *o_msgNoP = 0x1844;
        break;
    case 0x1844:
        *o_msgNoP = 0x1845;
        break;
    case 0x1845:
        *o_msgNoP = 0x1846;
        break;
    case 0x1846:
        *o_msgNoP = 0x1847;
        break;
    case 0x1847:
        *o_msgNoP = 0x1848;
        break;
    case 0x1849:
        *o_msgNoP = 0x184A;
        break;
    case 0x184A:
        *o_msgNoP = 0x184B;
        break;
    default:
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return ret;
}

/* 000017F4-00001888       .text getMsg_CO1_0__11daNpc_Co1_cFv */
u32 daNpc_Co1_c::getMsg_CO1_0() {
    if (mItemNo == 0x98) {
        return 0x183C;
    }
    if (mItemNo != 0xFF) {
        return 0x183B;
    }
    if (m80A) {
        return 0x183E;
    }
    if (dNpc_chkLetterPassed()) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0F04) ? 0x1849 : 0x1841;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0F08) ? 0x183A : 0x1839;
}

/* 00001888-000018C4       .text getMsg__11daNpc_Co1_cFv */
u32 daNpc_Co1_c::getMsg() {
    u32 msg = 0;
    switch (mType) {
    case 0:
        msg = getMsg_CO1_0();
        break;
    }
    return msg;
}

/* 000018C4-00001944       .text chkAttention__11daNpc_Co1_cFv */
bool daNpc_Co1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    }
    return this == attention.ActionTarget(0);
}

/* 00001944-00001A2C       .text setAttention__11daNpc_Co1_cFb */
void daNpc_Co1_c::setAttention(bool i_setEyePos) {
    if (mAnmNum == 1) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
        cXyz offset(0.0f, 60.0f, -50.0f);
        mDoMtx_stack_c::multVec(&offset, &attention_info.position);
    } else {
        attention_info.position.set(current.pos.x, current.pos.y + l_HIO.mPrm.mAttPosOffsetY, current.pos.z);
    }

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* 00001A2C-00001A48       .text charDecide__11daNpc_Co1_cFi */
bool daNpc_Co1_c::charDecide(int) {
    mHioType = 0;
    mType = -1;
    mType = 0;
    return true;
}

/* 00001A48-00001A84       .text eInit_MDR___11daNpc_Co1_cFv */
void daNpc_Co1_c::eInit_MDR_() {
    setAnm_NUM(10, 1);
    mLookMode = 0;
}

/* 00001A84-00001AAC       .text eInit_RED_LTR___11daNpc_Co1_cFv */
void daNpc_Co1_c::eInit_RED_LTR_() {
    setAnm_NUM(8, 1);
}

/* 00001AAC-00001B28       .text event_actionInit__11daNpc_Co1_cFi */
void daNpc_Co1_c::event_actionInit(int i_staffIdx) {
    int* act_no_p = dComIfGp_evmng_getMyIntegerP(i_staffIdx, "ActNo");
    if (act_no_p != NULL) {
        mActNo = *act_no_p;
        switch (mActNo) {
        case 0:
            eInit_MDR_();
            break;
        case 1:
            eInit_RED_LTR_();
            break;
        }
    }
}

/* 00001B28-00001B98       .text eMove_MDR___11daNpc_Co1_cFv */
bool daNpc_Co1_c::eMove_MDR_() {
    bool ret = (int)mpMorf->getFrame() == 0;
    if (ret) {
        setAnm_NUM(11, 1);
    }
    return ret;
}

/* 00001B98-00001C30       .text eMove_RED_LTR___11daNpc_Co1_cFv */
bool daNpc_Co1_c::eMove_RED_LTR_() {
    bool ret = false;
    if (mbMorfAnimStopped) {
        switch (mAnmNum) {
        case 8:
            setAnm_NUM(4, 1);
            break;
        case 4:
            mNextStt = 7;
            setStt(2);
            ret = true;
            break;
        default:
            setAnm_NUM(8, 1);
            break;
        }
    }
    return ret;
}

/* 00001C30-00001C88       .text event_action__11daNpc_Co1_cFv */
bool daNpc_Co1_c::event_action() {
    switch (mActNo) {
    case 0:
        return eMove_MDR_();
    case 1:
        return eMove_RED_LTR_();
    default:
        return true;
    }
}

/* 00001C88-00001D74       .text privateCut__11daNpc_Co1_cFi */
void daNpc_Co1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "ACTION",
    };

    if (i_staffIdx == -1) {
        return;
    }

    mActionIndex = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, ARRAY_SIZE(a_cut_tbl), TRUE, 0);
    if (mActionIndex == -1) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
    } else {
        if (dComIfGp_evmng_getIsAddvance(i_staffIdx)) {
            switch (mActionIndex) {
            case 0:
                event_actionInit(i_staffIdx);
                break;
            }
        }
        bool end_cut;
        switch (mActionIndex) {
        case 0:
            end_cut = event_action();
            break;
        default:
            end_cut = true;
            break;
        }
        if (end_cut) {
            dComIfGp_evmng_cutEnd(i_staffIdx);
        }
    }
}

/* 00001D74-00001D94       .text endEvent__11daNpc_Co1_cFv */
void daNpc_Co1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
}

/* 00001D94-00001DCC       .text isEventEntry__11daNpc_Co1_cFv */
int daNpc_Co1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(), NULL);
}

/* 00001DCC-00001EC4       .text event_proc__11daNpc_Co1_cFi */
void daNpc_Co1_c::event_proc(int i_staffIdx) {
    if (dComIfGp_evmng_endCheck(mEventIdTbl[mEventIdx])) {
        switch (mEventIdx) {
        case 0:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0F04);
            setStt(4);
            break;
        case 1:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_1810);
            break;
        case 2:
            mOrder = 1;
            break;
        }
        endEvent();
        return;
    }

    if (!mEventCut.cutProc()) {
        privateCut(i_staffIdx);
    }
    lookBack();
}

/* 00001EC4-00001F70       .text set_action__11daNpc_Co1_cFM11daNpc_Co1_cFPCvPvPv_iPv */
BOOL daNpc_Co1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
    if (mCurrProcFunc != i_newProcFunc) {
        if (mCurrProcFunc) {
            mActionState = 9;
            (this->*mCurrProcFunc)(i_argsP);
        }
        mCurrProcFunc = i_newProcFunc;
        mActionState = 0;
        (this->*mCurrProcFunc)(i_argsP);
    }
    return TRUE;
}

/* 00001F70-00001FD0       .text setStt__11daNpc_Co1_cFSc */
void daNpc_Co1_c::setStt(s8 i_stt) {
    mTalkTimer = 0;
    mStt = i_stt;
    switch (mStt) {
    case 2:
        mAnmAtr = 0xFF;
        mLookMode = 1;
        break;
    case 1:
        break;
    case 7:
        mLookMode = 0;
        break;
    }
    setAnm();
}

/* 00001FD0-0000205C       .text wait_1__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::wait_1() {
    if (mOrder == 1 || mOrder >= 3) {
        return TRUE;
    }

    if (mbTalkReq) {
        if (chk_talk()) {
            mNextStt = 4;
            setStt(3);
        }
        return TRUE;
    }

    mOrder = 2;
    return TRUE;
}

/* 0000205C-00002114       .text wait_2__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::wait_2() {
    if (mbTalkReq) {
        if (chk_talk()) {
            if (dNpc_chkLetterPassed()) {
                mNextStt = 7;
            } else {
                mNextStt = 4;
            }
            setStt(2);
        }
        return TRUE;
    }

    mOrder = 2;
    if (mbAttention) {
        mTalkTimer = 60;
    }
    if (cLib_calcTimer(&mTalkTimer) != 0) {
        mLookMode = 1;
    } else {
        mLookMode = 0;
    }
    return TRUE;
}

/* 00002114-00002150       .text wakeup__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::wakeup() {
    if (mbMorfAnimStopped) {
        mNextStt = 4;
        setStt(2);
    }
    return TRUE;
}

/* 00002150-00002348       .text talk_1__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::talk_1() {
    BOOL res = chk_partsNotMove();
    if (mOrder == 1 || mOrder >= 3) {
        return TRUE;
    }

    if (dNpc_chkLetterPassed() && !m80A && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0F04)) {
        if (mOrder != 3) {
            mItemNo = 0xFF;
            mbTalkReq = false;
            endEvent();
            mOrder = 3;
        }
        return TRUE;
    }

    fopNpc_npc_c::talk(1);
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
        case fopMsgStts_MSG_DESTROYED_e:
            switch (mCurrMsgNo) {
            case 0x1839:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0F08);
                break;
            case 0x1848:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0F04);
                break;
            case 0x1840:
                m80A = 0;
                break;
            }
            if (mItemNo == 0x98) {
                mOrder = 5;
                dComIfGp_evmng_CancelPresent();
                dComIfGs_setReserveItemEmpty();
                endEvent();
                m80A = 1;
            } else {
                setStt(mNextStt);
                if (mNextStt != 7) {
                    mbTalkReq = false;
                    endEvent();
                }
            }
            mItemNo = 0xFF;
            mTalkTimer = 60;
            break;
        case fopMsgStts_BOX_OPENING_e:
        case fopMsgStts_MSG_TYPING_e:
            if (mCurrMsgNo == 0x184B) {
                mLookMode = 0;
            }
            break;
        }
    }
    return res;
}

/* 00002348-000023BC       .text toru_1__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::toru_1() {
    if (mbTalkReq) {
        if (mItemNo == 0x98) {
            mItemNo = 0xFF;
            setAnm_NUM(8, 1);
        }
        if (mbMorfAnimStopped) {
            setStt(6);
        }
    }
    return FALSE;
}

/* 000023BC-000023F8       .text read_1__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::read_1() {
    if (mbMorfAnimStopped) {
        mNextStt = 7;
        setStt(2);
    }
    return FALSE;
}

/* 000023F8-00002454       .text modoru__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::modoru() {
    if ((int)mpMorf->getFrame() == 0) {
        setStt(4);
        mbTalkReq = false;
        endEvent();
    }
    return TRUE;
}

/* 00002454-000025D8       .text wait_action1__11daNpc_Co1_cFPv */
BOOL daNpc_Co1_c::wait_action1(void*) {
    switch (mActionState) {
    case 0:
        if (dNpc_chkLetterPassed()) {
            setStt(4);
        } else {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1810)) {
                mOrder = 4;
            }
            setStt(1);
        }
        mLight.mPos = current.pos;
        mLight.mPower = 0.0f;
        dKy_plight_set(&mLight);
        mActionState++;
        break;
    case 9:
        break;
    case 1:
    case 2:
    case 3:
        mbAttention = chkAttention();
        switch (mStt) {
        case 1:
            mbSetEyePos = wait_1();
            break;
        case 2:
            mbSetEyePos = talk_1();
            break;
        case 3:
            mbSetEyePos = wakeup();
            break;
        case 4:
            mbSetEyePos = wait_2();
            break;
        case 5:
            mbSetEyePos = toru_1();
            break;
        case 6:
            mbSetEyePos = read_1();
            break;
        case 7:
            mbSetEyePos = modoru();
            break;
        }
        lookBack();
        break;
    default:
        break;
    }
    return TRUE;
}

/* 000025D8-00002718       .text demo__11daNpc_Co1_cFv */
bool daNpc_Co1_c::demo() {
    if (demoActorID == 0) {
        if (mbDemo) {
            mbDemo = false;
        }
    } else {
        mbDemo = true;
        dDemo_actor_c* demo_actor_p = dComIfGp_demo_getActor(demoActorID);
        if (m_hed_tex_pttrn) {
            mBtpFrame++;
            if (mBtpFrame >= m_hed_tex_pttrn->getFrameMax()) {
                mBtpFrame = m_hed_tex_pttrn->getFrameMax();
            }
        }
        J3DAnmTexPattern* demo_btp_p = demo_actor_p->getP_BtpData("Co");
        if (demo_btp_p) {
            m_hed_tex_pttrn = demo_btp_p;
            if (mBtpAnm.init(mpMorf->getModel()->getModelData(), m_hed_tex_pttrn, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, FALSE)) {
                mBtpNum = 7;
                mBtpFrame = 0;
            }
        }
        dDemo_setDemoData(this, 0x6A, mpMorf, "Co");
    }
    return mbDemo;
}

/* 00002718-000027A8       .text shadowDraw__11daNpc_Co1_cFv */
void daNpc_Co1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f, current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex());
}

static void dummy() {
    const GXColor dummy1 = {0xFF, 0x00, 0x00, 0x80};
    const GXColor dummy2 = {0x00, 0x00, 0xFF, 0x80};
    const GXColor dummy3 = {0x00, 0xFF, 0x00, 0x80};
}

/* 000027A8-00002960       .text _draw__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::_draw() {
    J3DModel* model = mpMorf->getModel();
    J3DModelData* model_data = model->getModelData();
    J3DModel* prl_model = mpPrlMorf->getModel();
    J3DModelData* prl_model_data = prl_model->getModelData();

    if (mbHide || m811) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    dKy_tevstr_c* tevstr_p = &tevStr;
    u8 color_min = l_HIO.mPrm.mGlowColorMin;
    u8 color = (255 - color_min) * mGlow;
    tevstr_p->mLightObj.mInfo.mColor.r = color + color_min;
    g_env_light.setLightTevColorType(model, tevstr_p);

    mBtpAnm.entry(model_data, mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);

    g_env_light.setLightTevColorType(prl_model, &tevStr);
    mBtkAnm.entry(prl_model_data, mBtkFrame);
    mpPrlMorf->entryDL();
    mBtkAnm.remove(prl_model_data);

    if (mbShowItem) {
        g_env_light.setLightTevColorType(mpItemModel, &tevStr);
        mDoExt_modelEntryDL(mpItemModel);
    }

    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK8B, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00002960-00002B10       .text _execute__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::_execute() {
    if (!mbInitDone) {
        mHomePos = current.pos;
        mHomeAngle = current.angle;
        mbInitDone = true;
    }
    m_jnt.setParam(
        l_HIO.mPrm.mMaxBackboneX, l_HIO.mPrm.mMaxBackboneY, l_HIO.mPrm.mMinBackboneX, l_HIO.mPrm.mMinBackboneY,
        l_HIO.mPrm.mMaxHeadX, l_HIO.mPrm.mMaxHeadY, l_HIO.mPrm.mMinHeadX, l_HIO.mPrm.mMinHeadY,
        l_HIO.mPrm.mMaxTurnStep
    );
    if (mbHide && demoActorID == 0) {
        return TRUE;
    }
    mbNoMove = false;
    mbHide = false;
    checkOrder();
    if (!demo()) {
        int staff_id = -1;
        if (dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == false) {
            staff_id = isEventEntry();
        }
        if (staff_id >= 0) {
            event_proc(staff_id);
        } else {
            (this->*mCurrProcFunc)(NULL);
        }
        if (!mbNoMove) {
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
        }
        if (!m80F) {
            shape_angle = current.angle;
        }
    }
    eventOrder();
    setMtx(false);
    if (!mbDemo) {
        setCollision_SP_();
    }
    return TRUE;
}

/* 00002B10-00002B6C       .text _delete__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Co");
    dKy_plight_cut(&mLight);
    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00002B6C-00002B8C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Co1_c*)i_this)->CreateHeap();
}

daNpc_Co1_c::daNpc_Co1_c() {}

/* 00002B8C-00002CAC       .text _create__11daNpc_Co1_cFv */
cPhs_State daNpc_Co1_c::_create() {
    static int a_size_tbl[] = {
        0x272E0,
    };

    fopAcM_ct(this, daNpc_Co1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "Co");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }
    if (!charDecide(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[mHioType])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -40.0f, -20.0f, -100.0f, 40.0f, 100.0f, 60.0f);
    if (!createInit()) {
        return cPhs_ERROR_e;
    }
    return state;
}

/* 0000315C-000033AC       .text create_Anm__11daNpc_Co1_cFv */
J3DModelData* daNpc_Co1_c::create_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Co", dRes_ID_CO_BDL_CO_e);
    JUT_ASSERT(0x81F, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL, (J3DAnmTransform*)dComIfG_getObjectIDRes("Co", dRes_ID_CO_BCK_CO_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11020022
    );
    if (mpMorf == NULL) {
        return NULL;
    }
    if (mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return NULL;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x833, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x836, m_bbone_jnt_num >= 0);
    m_hnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("handR");
    JUT_ASSERT(0x839, m_hnd_R_jnt_num >= 0);

    return a_mdl_dat;
}

/* 000033AC-00003564       .text create_prl_Anm__11daNpc_Co1_cFv */
J3DModelData* daNpc_Co1_c::create_prl_Anm() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Co", dRes_ID_CO_BDL_CO_PEAL_e);
    JUT_ASSERT(0x848, a_mdl_dat != NULL);
    mpPrlMorf = new mDoExt_McaMorf(
        a_mdl_dat, NULL, NULL, (J3DAnmTransform*)dComIfG_getObjectIDRes("Co", dRes_ID_CO_BCK_COPEAL_WAIT01_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL, 0x80000, 0x15021222
    );
    if (mpPrlMorf == NULL) {
        return NULL;
    }
    if (mpPrlMorf->getModel() == NULL) {
        mpPrlMorf = NULL;
        return NULL;
    }

    m_prl_jnt_num = a_mdl_dat->getJointName()->getIndex("co_pearl");
    JUT_ASSERT(0x85C, m_prl_jnt_num >= 0);

    return a_mdl_dat;
}

/* 00003564-00003618       .text create_itm_Mdl__11daNpc_Co1_cFv */
bool daNpc_Co1_c::create_itm_Mdl() {
    mpItemModel = NULL;
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Co", dRes_ID_CO_BDL_CO_LETTER_e);
    JUT_ASSERT(0x86E, a_mdl_dat != NULL);
    mpItemModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000002);
    return true;
}

/* 00003618-000037C4       .text CreateHeap__11daNpc_Co1_cFv */
BOOL daNpc_Co1_c::CreateHeap() {
    J3DModelData* a_mdl_dat = create_Anm();
    if (!a_mdl_dat) {
        return FALSE;
    }
    mBtpNum = 6;
    if (!iniTexPttrnAnm(false)) {
        mpMorf = NULL;
        return FALSE;
    }
    if (create_prl_Anm() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }
    if (!setBtk(false)) {
        mpMorf = NULL;
        mpPrlMorf = NULL;
        return FALSE;
    }
    if (create_itm_Mdl()) {
        for (u16 i = 0; i < a_mdl_dat->getJointNum(); i++) {
            if (i == m_hed_jnt_num || i == m_bbone_jnt_num) {
                mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Co1);
            }
        }
        mpMorf->getModel()->setUserArea((uintptr_t)this);
        mAcchCir.SetWall(30.0f, 40.0f);
        mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
        return TRUE;
    }
    mpMorf = NULL;
    mpPrlMorf = NULL;
    return FALSE;
}

/* 000037C4-000037E4       .text daNpc_Co1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Co1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Co1_c*)i_this)->_create();
}

/* 000037E4-00003804       .text daNpc_Co1_Delete__FP11daNpc_Co1_c */
static BOOL daNpc_Co1_Delete(daNpc_Co1_c* i_this) {
    return ((daNpc_Co1_c*)i_this)->_delete();
}

/* 00003804-00003824       .text daNpc_Co1_Execute__FP11daNpc_Co1_c */
static BOOL daNpc_Co1_Execute(daNpc_Co1_c* i_this) {
    return ((daNpc_Co1_c*)i_this)->_execute();
}

/* 00003824-00003844       .text daNpc_Co1_Draw__FP11daNpc_Co1_c */
static BOOL daNpc_Co1_Draw(daNpc_Co1_c* i_this) {
    return ((daNpc_Co1_c*)i_this)->_draw();
}

/* 00003844-0000384C       .text daNpc_Co1_IsDelete__FP11daNpc_Co1_c */
static BOOL daNpc_Co1_IsDelete(daNpc_Co1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Co1_Method = {
    (process_method_func)daNpc_Co1_Create,
    (process_method_func)daNpc_Co1_Delete,
    (process_method_func)daNpc_Co1_Execute,
    (process_method_func)daNpc_Co1_IsDelete,
    (process_method_func)daNpc_Co1_Draw,
};

actor_process_profile_definition g_profile_NPC_CO1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_CO1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Co1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_CO1_e,
    /* Actor SubMtd */ &l_daNpc_Co1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
