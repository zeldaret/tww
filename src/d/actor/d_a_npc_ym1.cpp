/**
 * d_a_npc_ym1.cpp
 * NPC - Mesa & Abe
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ym1.h"
#include "d/d_cc_mass_s.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "res/Object/Ym.h"

class daNpc_Ym1_childHIO_c : public mDoHIO_entry_c {
public:
    struct hio_prm_c {
        /* 0x00 */ s16 mMaxHeadX;
        /* 0x02 */ s16 mMaxHeadY;
        /* 0x04 */ s16 mMinHeadX;
        /* 0x06 */ s16 mMinHeadY;
        /* 0x08 */ s16 mMaxBackBoneX;
        /* 0x0A */ s16 mMaxBackBoneY;
        /* 0x0C */ s16 mMinBackBoneX;
        /* 0x0E */ s16 mMinBackBoneY;
        /* 0x10 */ s16 mMaxTurnStep;
        /* 0x12 */ s16 mMaxHeadTurnVel;
        /* 0x14 */ f32 mAttPosOffsetY;
        /* 0x18 */ u8 m18;
        /* 0x1C */ f32 mKariDist;
        /* 0x20 */ f32 mKtalkMorf;
    };  // Size: 0x24

    daNpc_Ym1_childHIO_c();
    void genMessage(JORMContext* ctx) { UNUSED(ctx); };

public:
    /* 0x04 */ hio_prm_c hio_prm;
    /* 0x28 */ u32 m28;
};  // Size: 0x2C

class daNpc_Ym1_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_Ym1_HIO_c();
    virtual ~daNpc_Ym1_HIO_c() {}
    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 m4;
    /* 0x08 */ s32 m8;
    /* 0x0C */ daNpc_Ym1_childHIO_c children[2];
};  // Size: 0x64

static daNpc_Ym1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* .text __ct__20daNpc_Ym1_childHIO_cFv */
daNpc_Ym1_childHIO_c::daNpc_Ym1_childHIO_c() {
}

/* .text __ct__15daNpc_Ym1_HIO_cFv */
daNpc_Ym1_HIO_c::daNpc_Ym1_HIO_c() {
    static daNpc_Ym1_childHIO_c::hio_prm_c a_prm_tbl[] = {
        {
            /* mMaxHeadX       */ 0x2000,
            /* mMaxHeadY       */ 0x1F40,
            /* mMinHeadX       */ -0x2000,
            /* mMinHeadY       */ -0x1F40,
            /* mMaxBackBoneX   */ 0x0000,
            /* mMaxBackBoneY   */ 0x1C70,
            /* mMinBackBoneX   */ 0x0000,
            /* mMinBackBoneY   */ -0x1C70,
            /* mMaxTurnStep    */ 0x0640,
            /* mMaxHeadTurnVel */ 0x04B0,
            /* mAttPosOffsetY  */ 190.0f,
            /* m18             */ 0,
            /* mKariDist       */ 400.0f,
            /* mKtalkMorf      */ 14.0f,
        },
        {
            /* mMaxHeadX       */ 0x2000,
            /* mMaxHeadY       */ 0x1F40,
            /* mMinHeadX       */ -0x2000,
            /* mMinHeadY       */ -0x1F40,
            /* mMaxBackBoneX   */ 0x0000,
            /* mMaxBackBoneY   */ 0x1B58,
            /* mMinBackBoneX   */ 0x0000,
            /* mMinBackBoneY   */ -0x1B58,
            /* mMaxTurnStep    */ 0x0640,
            /* mMaxHeadTurnVel */ 0x04B0,
            /* mAttPosOffsetY  */ 190.0f,
            /* m18             */ 0,
            /* mKariDist       */ 0.0f,
            /* mKtalkMorf      */ 0.0f,
        },
    };
    for (int i = 0; i < 2; i++) {
        children[i].m28 = i;
        memcpy(&children[i].hio_prm, &a_prm_tbl[i], sizeof(daNpc_Ym1_childHIO_c::hio_prm_c));
    }
    m4 = -1;
    m8 = -1;
}

/* .text area_check */
static void area_check(fopAc_ac_c* i_this, cXyz*, u32 i_flag) {
    if (i_flag == 0) {
        ((daNpc_Ym1_c*)i_this)->setKariFlg();
    }
}

/* .text setKariFlg */
void daNpc_Ym1_c::setKariFlg() {
    mbKari = true;
}

/* .text nodeCB_Head */
static BOOL nodeCB_Head(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ym1_c* actor_p = (daNpc_Ym1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Head(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* .text _nodeCB_Head */
void daNpc_Ym1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(26.0f, -25.0f, 0.0f);

    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    mHeadPos.x = mDoMtx_stack_c::get()[0][3];
    mHeadPos.y = mDoMtx_stack_c::get()[1][3];
    mHeadPos.z = mDoMtx_stack_c::get()[2][3];

    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(m_jnt.getHead_x());
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);

    mDoMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* .text nodeCB_BackBone */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Ym1_c* actor_p = (daNpc_Ym1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_BackBone(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* .text _nodeCB_BackBone */
void daNpc_Ym1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(m_jnt.getBackbone_x());

    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* .text CheckCreateHeap */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Ym1_c*)i_this)->CreateHeap();
}

/* .text init_YM1_0 */
bool daNpc_Ym1_c::init_YM1_0() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
        set_action(&daNpc_Ym1_c::wait_action1, NULL);
        return true;
    }
    return false;
}

/* .text init_YM1_1 */
bool daNpc_Ym1_c::init_YM1_1() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
        set_action(&daNpc_Ym1_c::wait_action4, NULL);
        return true;
    }
    return false;
}

/* .text init_YM2_0 */
bool daNpc_Ym1_c::init_YM2_0() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20)) {
        set_action(&daNpc_Ym1_c::wait_action3, NULL);
        return true;
    }
    return false;
}

/* .text init_YM2_1 */
bool daNpc_Ym1_c::init_YM2_1() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20)) {
        set_action(&daNpc_Ym1_c::wait_action2, NULL);
        return true;
    }
    return false;
}

/* .text init_YM2_2 */
bool daNpc_Ym1_c::init_YM2_2() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && dKy_daynight_check() == 0) {
        set_action(&daNpc_Ym1_c::wait_action2, NULL);
        return true;
    }
    return false;
}

/* .text init_YM2_3 */
bool daNpc_Ym1_c::init_YM2_3() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && dKy_daynight_check() == 1) {
        set_action(&daNpc_Ym1_c::wait_action2, NULL);
        return true;
    }
    return false;
}

/* .text init_YMx_error */
bool daNpc_Ym1_c::init_YMx_error() {
    set_action(&daNpc_Ym1_c::demo_action1, NULL);
    return true;
}

/* .text createInit */
bool daNpc_Ym1_c::createInit() {
    static u8 a_att_dis_TBL[][2] = {
        {0x00, 0x00},
        {0xAA, 0xAA},
        {0xAA, 0xAA},
    };
    static char* a_staff_tbl[] = {
        "Ym1",
        "Ym1",
        "Ym2",
        "Ym2",
        "Ym2",
        "Ym2",
        "Ym1",
        "Ym2",
    };

    mEventCut.setActorInfo2(a_staff_tbl[mType], this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = a_att_dis_TBL[mHioType][0];
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = a_att_dis_TBL[mHioType][1];
    mBckNum = BCKNUM_NULL_e;

    bool init_result;
    switch (mType) {
    case 0:
        init_result = init_YM1_0();
        break;
    case 1:
        init_result = init_YM1_1();
        break;
    case 2:
        init_result = init_YM2_0();
        break;
    case 3:
        init_result = init_YM2_1();
        break;
    case 4:
        init_result = init_YM2_2();
        break;
    case 5:
        init_result = init_YM2_3();
        break;
    case 6:
    case 7:
        init_result = init_YMx_error();
        break;
    default:
        init_result = false;
        break;
    }

    if (!init_result) {
        return false;
    }

    mAngle = current.angle;
    shape_angle = mAngle;
    gravity = -4.5f;

    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);

    if (mType == 0) {
        cXyz offset(0.0f, 0.0f, 80.0f);
        cXyz pos;
        mAreaCyl.SetStts(&mStts);
        mAreaCyl.Set(dNpc_cyl_src);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
        mDoMtx_stack_c::multVec(&offset, &pos);
        mAreaCyl.SetC(pos);
        mAreaCyl.SetR(50.0f);
        mAreaCyl.SetH(30.0f);
        dComIfG_Ccsp()->SetMass(&mAreaCyl, 3);
    }

    play_animation();
    if (mType != 1) {
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(true);

    return true;
}

/* .text play_animation */
void daNpc_Ym1_c::play_animation() {
    play_texPttrnAnm();

    mbMorfAnimStopped = mpMorf->play(&eyePos, 0, 0);

    if (mpMorf->getFrame() < mPrevMorfFrame) {
        mbMorfAnimStopped = true;
    }

    mPrevMorfFrame = mpMorf->getFrame();
}

/* .text setMtx */
void daNpc_Ym1_c::setMtx(bool i_setEyePos) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());

    mpMorf->calc();

    mpHeadModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
    mpHeadModel->calc();

    if (mpItemModel) {
        mpItemModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num));
        mpItemModel->calc();
    }
    setAttention(i_setEyePos);
}

/* .text bckResID */
int daNpc_Ym1_c::bckResID(int i_bckNum) {
    static const int a_res_id_tbl[] = {
        dRes_ID_YM_BCK_WAIT01_e,
        dRes_ID_YM_BCK_YM_KARI01_e,
        dRes_ID_YM_BCK_YM_KARI2WAIT_e,
        dRes_ID_YM_BCK_YM_KWAIT_e,
        dRes_ID_YM_BCK_YM_KTALK_e,
        dRes_ID_YM_BCK_YM_NBTWAIT_e,
        dRes_ID_YM_BCK_YM_NBTLOOK_e,
        dRes_ID_YM_BCK_YM_NBTTALK_e,
        dRes_ID_YM_BCK_YM_KTALK02_e,
        dRes_ID_YM_BCK_YM_WAIT02_e,
        dRes_ID_YM_BCK_YM_SIT_e,
        dRes_ID_YM_BCK_YM_SITTALK_e,
        dRes_ID_YM_BCK_YM_TALK01_e,
    };
    return a_res_id_tbl[i_bckNum];
}

/* .text btpResID */
int daNpc_Ym1_c::btpResID(int i_btpNum) {
    static const int a_res_id_tbl[] = {
        dRes_ID_YM_BTP_YMHEAD01_e,
    };
    int res_id = a_res_id_tbl[i_btpNum];
    if (res_id == dRes_ID_YM_BTP_YMHEAD01_e) {
        switch (mHioType) {
        case 1:
            return dRes_ID_YM_BTP_YMHEAD01_e;
        case 2:
            return dRes_ID_YM_BTP_YMHEAD02_e;
        }
    }
    return res_id;
}

/* .text init_texPttrnAnm */
bool daNpc_Ym1_c::init_texPttrnAnm(s8 i_btpNum, bool i_bModify) {
    J3DModel* head_model_p = mpHeadModel;

    if (i_btpNum < 0) {
        return false;
    }

    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(mArcName, btpResID(i_btpNum));
    JUT_ASSERT(0x270, a_btp != NULL);
    mBtpNum = i_btpNum;
    mBtpFrame = 0;
    mBlinkTimer = 0;

    return mBtpAnm.init(head_model_p->getModelData(), a_btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, i_bModify, 0) != 0;
}

/* .text play_texPttrnAnm */
void daNpc_Ym1_c::play_texPttrnAnm() {
    if (mBtpNum != BTPNUM_HEAD_e || cLib_calcTimer(&mBlinkTimer) == 0) {
        mBtpFrame++;
        if (mBtpFrame >= mBtpAnm.getBtpAnm()->getFrameMax()) {
            if (mBtpNum != BTPNUM_HEAD_e) {
                mBtpFrame = mBtpAnm.getBtpAnm()->getFrameMax();
            } else {
                mBlinkTimer = cLib_getRndValue(60, 90);
                mBtpFrame = 0;
            }
        }
    }
}

/* .text setAnm_anm */
void daNpc_Ym1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (i_anmPrmP->bckNum < 0 || mBckNum == i_anmPrmP->bckNum) {
        return;
    }

    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, bckResID(i_anmPrmP->bckNum), -1, mArcName);
    mBckNum = i_anmPrmP->bckNum;
    mbMorfAnimStopped = false;
    m899 = 0;
    mPrevMorfFrame = 0.0f;
    if (mBckNum == BCKNUM_KTALK02_e) {
        mpMorf->setMorf(l_HIO.children[mHioType - 1].hio_prm.mKtalkMorf);
    }
}

/* .text setAnm_NUM */
void daNpc_Ym1_c::setAnm_NUM(int i_anmNum, int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[13] = {
        {BCKNUM_WAIT01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KARI01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KARI2WAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_KWAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KTALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_NBTWAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_NBTLOOK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_NBTTALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KTALK02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_SIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_SITTALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    if (i_setBtp) {
        init_texPttrnAnm(a_anm_prm_tbl[i_anmNum].btpNum, true);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* .text setAnm */
void daNpc_Ym1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[12] = {
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_KARI01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KWAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KWAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KWAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_NBTWAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_WAIT01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_WAIT02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_SIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mStt].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mStt]);
}

/* .text chngAnmTag */
void daNpc_Ym1_c::chngAnmTag() {
}

/* .text ctrlAnmTag */
void daNpc_Ym1_c::ctrlAnmTag() {
}

/* .text chngAnmAtr */
void daNpc_Ym1_c::chngAnmAtr(u8 i_atr) {
    if (i_atr == mAnmAtr || i_atr > 13) {
        return;
    }
    mAnmAtr = i_atr;
    setAnm_ATR();
}

/* .text ctrlAnmAtr */
void daNpc_Ym1_c::ctrlAnmAtr() {
}

/* .text setAnm_ATR */
void daNpc_Ym1_c::setAnm_ATR() {
    static anm_prm_c a_anm_prm_tbl[13] = {
        {BCKNUM_WAIT01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KARI01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KARI2WAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_KWAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KTALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_NBTWAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_NBTLOOK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_NONE},
        {BCKNUM_NBTTALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_KTALK02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_SIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_SITTALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mAnmAtr].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* .text anmAtr */
void daNpc_Ym1_c::anmAtr(u16 i_msgStatus) {
    u8 mesg_anime_tag;
    switch (i_msgStatus) {
    case fopMsgStts_MSG_TYPING_e:
        if (mMsgCount == 0) {
            chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
            mMsgCount++;
        }
        mesg_anime_tag = dComIfGp_getMesgAnimeTagInfo();
        if (mesg_anime_tag != 0xFF && mesg_anime_tag != mMesgAnimeTag) {
            dComIfGp_setMesgAnimeTagInfo(0xFF);
            mMesgAnimeTag = mesg_anime_tag;
            chngAnmTag();
        }
        break;
    case fopMsgStts_MSG_DISPLAYED_e:
        mMsgCount = 0;
        break;
    default:
        break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* .text next_msgStatus */
u16 daNpc_Ym1_c::next_msgStatus(u32* o_msgNoP) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_msgNoP) {
    case 0x8FD:
        *o_msgNoP = 0x8FE;
        break;
    case 0x8FF:
        *o_msgNoP = 0x900;
        break;
    case 0x901:
        *o_msgNoP = 0x902;
        break;
    case 0x90A:
        *o_msgNoP = 0x90B;
        break;
    case 0x904:
        *o_msgNoP = 0x905;
        break;
    case 0x905:
        *o_msgNoP = 0x906;
        break;
    case 0x907:
        *o_msgNoP = 0x908;
        break;
    case 0x908:
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3004)) {
            msg_status = fopMsgStts_MSG_ENDS_e;
        } else {
            *o_msgNoP = 0x909;
        }
        break;
    case 0xA2F:
        if (dKy_daynight_check() == 1) {
            *o_msgNoP = 0xA30;
        } else if (dComIfGs_getEventReg(dSv_event_flag_c::UNK_BFFF)) {
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3402)) {
                *o_msgNoP = 0xA31;
            } else {
                *o_msgNoP = 0xA33;
            }
        } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3402)) {
            *o_msgNoP = 0xA37;
        } else {
            *o_msgNoP = 0xA35;
        }
        break;
    case 0xA31:
        *o_msgNoP = 0xA32;
        break;
    case 0xA33:
        *o_msgNoP = 0xA34;
        break;
    case 0xA35:
        *o_msgNoP = 0xA36;
        break;
    case 0xA37:
        *o_msgNoP = 0xA38;
        break;
    case 0xA3B:
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3402)) {
            *o_msgNoP = 0xA3C;
        } else {
            *o_msgNoP = 0xA3D;
        }
        break;
    case 0xA3E:
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3402)) {
            *o_msgNoP = 0xA40;
        } else {
            *o_msgNoP = 0xA3F;
        }
        break;
    case 0xA41:
        *o_msgNoP = 0xA42;
        break;
    case 0x906:
    default:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return msg_status;
}

/* .text getMsg_YM1_0 */
u32 daNpc_Ym1_c::getMsg_YM1_0() {
    if (dComIfGs_getpCollect()->checkCollect(0)) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0010) ? 0x903 : 0x901;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0020)) {
        return 0x8FF;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80) ? 0x8FD : 0x90A;
}

/* .text getMsg_YM1_1 */
u32 daNpc_Ym1_c::getMsg_YM1_1() {
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_2904) ? 0x907 : 0x904;
}

/* .text getMsg_YM2_0 */
u32 daNpc_Ym1_c::getMsg_YM2_0() {
    if (chk_BlackPig()) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0008) ? 0xA2C : 0xA2B;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0080) ? 0xA2A : 0xA29;
}

/* .text getMsg_YM2_1 */
u32 daNpc_Ym1_c::getMsg_YM2_1() {
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B01) ? 0xA2E : 0xA2D;
}

/* .text getMsg_YM2_2 */
u32 daNpc_Ym1_c::getMsg_YM2_2() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3140)) {
        return 0xA2F;
    }
    if (dKy_daynight_check() == 1) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_3402) ? 0xA3A : 0xA39;
    }
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3580)) {
        return 0xA3B;
    }
    return !dComIfGs_isEventBit(dSv_event_flag_c::UNK_3540) ? 0xA3E : 0xA41;
}

/* .text getMsg_YM2_3 */
u32 daNpc_Ym1_c::getMsg_YM2_3() {
    return getMsg_YM2_2();
}

/* .text getMsg */
u32 daNpc_Ym1_c::getMsg() {
    u32 result = 0;
    switch (mType) {
    case 0:
        result = getMsg_YM1_0();
        break;
    case 1:
        result = getMsg_YM1_1();
        break;
    case 2:
        result = getMsg_YM2_0();
        break;
    case 3:
        result = getMsg_YM2_1();
        break;
    case 4:
        result = getMsg_YM2_2();
        break;
    case 5:
        result = getMsg_YM2_3();
        break;
    }
    return result;
}

/* .text eventOrder */
void daNpc_Ym1_c::eventOrder() {
    if (mOrder == 1 || mOrder == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* .text checkOrder */
void daNpc_Ym1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
    } else if (eventInfo.checkCommandTalk()) {
        if (mOrder == 1 || mOrder == 2) {
            mOrder = 0;
            mbTalkReq = true;
        }
    }
}

/* .text set_collision_sp */
void daNpc_Ym1_c::set_collision_sp() {
    if (mbTalkReq) {
        return;
    }

    cXyz pos;
    cXyz offset;
    f32 height;
    f32 radius;
    switch (mBckNum) {
    case BCKNUM_KARI01_e:
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
        offset.set(0.0f, 0.0f, 20.0f);
        radius = 60.0f;
        height = 140.0f;
        mDoMtx_stack_c::multVec(&offset, &pos);
        break;
    case BCKNUM_NBTWAIT_e:
    case BCKNUM_NBTLOOK_e:
    case BCKNUM_NBTTALK_e:
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y);
        offset.set(0.0f, 0.0f, 60.0f);
        radius = 80.0f;
        height = 150.0f;
        mDoMtx_stack_c::multVec(&offset, &pos);
        break;
    default:
        pos.set(current.pos.x, current.pos.y, current.pos.z);
        radius = 60.0f;
        height = 180.0f;
        break;
    }

    mCyl.SetC(pos);
    mCyl.SetR(radius);
    mCyl.SetH(height);
    dComIfG_Ccsp()->Set(&mCyl);
}

/* .text set_cutGrass */
void daNpc_Ym1_c::set_cutGrass() {
    if (!mbDemo && mBckNum == BCKNUM_KARI01_e && mpMorf->checkFrame(34.0f)) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hnd_L_jnt_num));
        cXyz pos;
        pos.x = mDoMtx_stack_c::get()[0][3];
        pos.y = mDoMtx_stack_c::get()[1][3];
        pos.z = mDoMtx_stack_c::get()[2][3];
        dComIfGp_particle_setSimple(dPa_name::ID_IT_JN_O_KUSA_KEN, &pos);
        mDoAud_seStart(JA_SE_CM_CUT_GRASS, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }
}

/* .text chk_BlackPig */
bool daNpc_Ym1_c::chk_BlackPig() {
    return (dComIfGs_getEventReg(dSv_event_flag_c::UNK_BFFF) >> 2) & 1;
}

/* .text chk_nbt_attn */
bool daNpc_Ym1_c::chk_nbt_attn() {
    bool ret = false;
    if (mBckNum == BCKNUM_NBTWAIT_e || mBckNum == BCKNUM_NBTLOOK_e || mBckNum == BCKNUM_NBTTALK_e) {
        ret = true;
    }
    return ret;
}

/* .text chk_talk */
bool daNpc_Ym1_c::chk_talk() {
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            mItemNo = dComIfGp_event_getPreItemNo();
            return true;
        }
        return false;
    }

    mItemNo = 0xFF;
    return true;
}

/* .text chk_parts_notMov */
bool daNpc_Ym1_c::chk_parts_notMov() {
    bool ret = false;
    if (mJointHeadY == m_jnt.getHead_y() && mJointBackboneY == m_jnt.getBackbone_y() && mActorAngleY == current.angle.y) {
        ret = true;
    }
    return ret;
}

/* .text lookBack */
void daNpc_Ym1_c::lookBack() {
    cXyz player_eye_pos;
    cXyz current_pos;

    mJointHeadY = m_jnt.getHead_y();
    mJointBackboneY = m_jnt.getBackbone_y();
    mActorAngleY = current.angle.y;

    current_pos = current.pos;
    current_pos.y = eyePos.y;

    player_eye_pos.set(0.0f, 0.0f, 0.0f);

    cXyz* player_eye_pos_p = NULL;
    s16 target_y = current.angle.y;
    bool head_only = m8A4;

    switch (mLookMode) {
    case 1:
        mPlayerEyePos = dNpc_playerEyePos(-20.0f);
        player_eye_pos = mPlayerEyePos;
        player_eye_pos_p = &player_eye_pos;
        break;
    case 2:
        player_eye_pos = mPlayerEyePos;
        player_eye_pos_p = &player_eye_pos;
        break;
    case 3:
        target_y = mTargetAngleY;
        break;
    }

    m_jnt.lookAtTarget_2(&current.angle.y, player_eye_pos_p, current_pos, target_y, l_HIO.children[mHioType - 1].hio_prm.mMaxHeadTurnVel, head_only);
}

/* .text chkAttention */
bool daNpc_Ym1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* .text setAttention */
void daNpc_Ym1_c::setAttention(bool i_setEyePos) {
    f32 offset_y = l_HIO.children[mHioType - 1].hio_prm.mAttPosOffsetY;
    cXyz pos = current.pos;
    if (chk_nbt_attn()) {
        if (mBckNum == BCKNUM_NBTLOOK_e) {
            offset_y = mHeadPos.y - 210.0f;
        } else {
            offset_y = 116.0f;
        }
        pos = mNbtPos;
    }
    attention_info.position.set(pos.x, pos.y + offset_y, pos.z);

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* .text decideType */
bool daNpc_Ym1_c::decideType(int i_type) {
    if (mHioType > 0) {
        return true;
    }

    mHioType = -1;
    mType = -1;

    switch (fopAcM_GetName(this)) {
    case fpcNm_NPC_YM1_e:
        mHioType = 1;
        switch (i_type) {
        case 0:
            mType = 0;
            break;
        case 1:
            mType = 1;
            break;
        }
        break;
    case fpcNm_NPC_YM2_e:
        mHioType = 2;
        switch (i_type) {
        case 0:
            mType = 2;
            break;
        case 1:
            mType = 3;
            break;
        case 2:
            mType = 4;
            break;
        case 3:
            mType = 5;
            break;
        }
        break;
    }

    strcpy(mArcName, "Ym");
    return mHioType != -1 && mType != -1;
}

/* .text privateCut */
void daNpc_Ym1_c::privateCut(int i_staffIdx) {
    static char* a_cut_tbl[] = {
        "DUMMY",
    };

    if (i_staffIdx == -1) {
        return;
    }

    mActionIndex = dComIfGp_evmng_getMyActIdx(i_staffIdx, a_cut_tbl, ARRAY_SSIZE(a_cut_tbl), TRUE, 0);

    if (mActionIndex == -1) {
        dComIfGp_evmng_cutEnd(i_staffIdx);
        return;
    }

    dComIfGp_evmng_getIsAddvance(i_staffIdx);
    dComIfGp_evmng_cutEnd(i_staffIdx);
}

/* .text endEvent */
void daNpc_Ym1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
    mMesgAnimeTag = 0xFF;
}

/* .text isEventEntry */
int daNpc_Ym1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* .text event_proc */
void daNpc_Ym1_c::event_proc(int i_staffIdx) {
    if (!mEventCut.cutProc()) {
        privateCut(i_staffIdx);
    }
}

/* .text set_action */
BOOL daNpc_Ym1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
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

/* .text setStt */
void daNpc_Ym1_c::setStt(s8 i_stt) {
    u8 prev_stt = mStt;
    mStt = i_stt;
    switch (mStt) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 8:
    case 10:
    case 11:
        mOrder = 0;
        break;
    case 5:
    case 7:
    case 9:
        mOrder = 0;
        mAnmAtr = 0xFF;
        mMesgAnimeTag = 0xFF;
        mMsgCount = 0;
        mPrevStt = prev_stt;
        break;
    case 6:
        mOrder = 0;
        mTimer = cLib_getRndValue(90, 180);
        break;
    }
    setAnm();
}

/* .text chk_areaIN */
bool daNpc_Ym1_c::chk_areaIN(f32 i_dist, cXyz i_pos) {
    f32 dist = (dComIfGp_getLinkPlayer()->current.pos - i_pos).absXZ();
    f32 dy = dComIfGp_getLinkPlayer()->current.pos.y - i_pos.y;
    if (dist < i_dist && std::fabsf(dy) < 300.0f) {
        return true;
    }
    return false;
}

/* .text kari_1 */
BOOL daNpc_Ym1_c::kari_1() {
    f32 dist = (dComIfGp_getLinkPlayer()->current.pos - current.pos).absXZ();

    if (cLib_calcTimer(&mTimer) != 0) {
        return TRUE;
    }

    if (chk_areaIN(l_HIO.children[mHioType - 1].hio_prm.mKariDist, current.pos) || !mbPrevKari) {
        setStt(2);
        mLookMode = 0;
        m8A4 = true;
        setAnm_NUM(2, 1);
    }
    return TRUE;
}

/* .text wait_1 */
BOOL daNpc_Ym1_c::wait_1() {
    if (mBckNum == BCKNUM_KARI2WAIT_e) {
        if (mbMorfAnimStopped) {
            setAnm_NUM(3, 1);
            mLookMode = 0;
            m8A4 = true;
            mLookTimer = cLib_getRndValue(15, 30);
        }
        return TRUE;
    }

    if (mbTurnHome) {
        cLib_addCalcAngleS(&current.angle.y, mHomeAngle.y, 4, l_HIO.children[mHioType - 1].hio_prm.mMaxHeadTurnVel, 0x80);
    }

    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(5);
            mLookMode = 1;
            m8A4 = false;
            mbTurnHome = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }

    mOrder = 2;
    mLookMode = 1;
    m8A4 = true;
    if (mbAttention) {
        mLookTimer = cLib_getRndValue(15, 30);
    }

    if (chk_areaIN(50.0f + l_HIO.children[mHioType - 1].hio_prm.mKariDist, current.pos) == false) {
        if (cLib_calcTimer(&mLookTimer) == 0) {
            setStt(3);
            mLookMode = 0;
            m8A4 = true;
        }
        return TRUE;
    }
    return TRUE;
}

/* .text wait_2 */
BOOL daNpc_Ym1_c::wait_2() {
    s16 diff = 0;
    if (mbTurnHome) {
        cLib_addCalcAngleS(&current.angle.y, mHomeAngle.y, 4, l_HIO.children[mHioType - 1].hio_prm.mMaxHeadTurnVel, 0x80);
        diff = mHomeAngle.y - current.angle.y;
    }

    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(5);
            mLookMode = 1;
            m8A4 = false;
            mbTurnHome = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }

    mOrder = 2;
    mLookMode = 0;
    m8A4 = true;
    if (diff == 0) {
        f32 dist_y = mHioType == 1 ? 120.0f : 92.0f;
        f32 dist_xz = mHioType == 1 ? 250.0f : 200.0f;
        if (mbAttention) {
            mLookTimer = cLib_getRndValue(15, 30);
        }
        if (cLib_calcTimer(&mLookTimer) != 0) {
            mLookMode = 1;
        }
        if (dNpc_chkAttn(this, dComIfGp_getLinkPlayer()->current.pos, dist_xz, 50.0f, dist_y, mLookMode == 1)) {
            return TRUE;
        }
        mLookMode = 0;
        mbTurnHome = true;
    }
    return TRUE;
}

/* .text talk_1 */
BOOL daNpc_Ym1_c::talk_1() {
    BOOL res = chk_parts_notMov();
    fopNpc_npc_c::talk(1);
    if (mpCurrMsg == NULL) {
        return res;
    }
    switch (mpCurrMsg->mStatus) {
    case fopMsgStts_BOX_OPENING_e:
    case fopMsgStts_MSG_TYPING_e:
        break;
    case fopMsgStts_MSG_DESTROYED_e:
        switch (mCurrMsgNo) {
        case 0x902:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0010);
            break;
        case 0x906:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2904);
            break;
        case 0xA29:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0080);
            break;
        case 0xA2B:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0008);
            break;
        case 0xA2D:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B01);
            break;
        case 0xA40:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3540);
            break;
        case 0x8FE:
        case 0x90B:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0020);
            break;
        case 0xA30:
        case 0xA32:
        case 0xA34:
        case 0xA36:
        case 0xA38:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3140);
            break;
        case 0xA3C:
        case 0xA3D:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3580);
            break;
        case 0xA37:
        case 0xA39:
        case 0xA3A:
        case 0xA3B:
            break;
        }
        mItemNo = 0xFF;
        mbTalkReq = false;
        setStt(mPrevStt);
        mLookTimer = cLib_getRndValue(15, 30);
        endEvent();
        break;
    }
    return res;
}

/* .text turn_1 */
BOOL daNpc_Ym1_c::turn_1() {
    cLib_addCalcAngleS(&current.angle.y, mHomeAngle.y, 4, l_HIO.children[mHioType - 1].hio_prm.mMaxHeadTurnVel, 0x80);
    if ((s16)(mHomeAngle.y - current.angle.y) == 0) {
        if (mbPrevKari) {
            setStt(1);
            mpMorf->setMorf(10.0f);
            mLookMode = 0;
            m8A4 = true;
            mTimer = cLib_getRndValue(30, 60);
        } else {
            setStt(4);
            mLookMode = 0;
            m8A4 = true;
        }
    }
    return TRUE;
}

/* .text NBTwai */
BOOL daNpc_Ym1_c::NBTwai() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(7);
            mLookMode = 0;
            m8A4 = true;
        }
        return TRUE;
    }

    mOrder = 2;
    mLookMode = 0;
    m8A4 = true;

    if (chk_BlackPig()) {
        setStt(8);
        mLookMode = 0;
        m8A4 = true;
        mbTurnHome = true;
        return TRUE;
    }

    if (mBckNum == BCKNUM_NBTLOOK_e) {
        if (mbMorfAnimStopped || mbAttention) {
            setAnm_NUM(5, 1);
            mTimer = cLib_getRndValue(90, 180);
        }
        return TRUE;
    }

    if (mbAttention) {
        mLookTimer = cLib_getRndValue(15, 30);
    }
    if (cLib_calcTimer(&mLookTimer) != 0) {
        mLookMode = 1;
        return TRUE;
    }
    if (cLib_calcTimer(&mTimer) == 0) {
        setAnm_NUM(6, 1);
    }
    return TRUE;
}

/* .text SITwai */
BOOL daNpc_Ym1_c::SITwai() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(5);
            mLookMode = 1;
            m8A4 = true;
        }
        return TRUE;
    }

    mOrder = 2;
    mLookMode = 0;
    m8A4 = true;
    if (mbAttention) {
        mLookTimer = cLib_getRndValue(15, 30);
    }
    if (cLib_calcTimer(&mLookTimer) != 0) {
        mLookMode = 1;
    }
    if (dNpc_chkAttn(this, dComIfGp_getLinkPlayer()->current.pos, 250.0f, 50.0f, 120.0f, mLookMode == 1)) {
        return TRUE;
    }
    mLookMode = 0;
    return TRUE;
}

/* .text wait_action1 */
BOOL daNpc_Ym1_c::wait_action1(void*) {
    switch (mActionState) {
    case 0:
        setStt(1);
        mbTurnHome = true;
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
            mbSetEyePos = kari_1();
            break;
        case 2:
            mbSetEyePos = wait_1();
            break;
        case 4:
            mbSetEyePos = wait_2();
            break;
        case 3:
            mbSetEyePos = turn_1();
            break;
        case 5:
            mbSetEyePos = talk_1();
            break;
        }
        break;
    default:
        break;
    }
    return TRUE;
}

/* .text wait_action2 */
BOOL daNpc_Ym1_c::wait_action2(void*) {
    switch (mActionState) {
    case 0:
        if (mType == 5) {
            setStt(10);
            mbTurnHome = true;
            mActionState++;
        } else {
            setStt(8);
            mbTurnHome = true;
            mActionState++;
        }
        break;
    case 9:
        break;
    case 1:
    case 2:
    case 3:
        mbAttention = chkAttention();
        switch (mStt) {
        case 8:
            mbSetEyePos = wait_2();
            break;
        case 10:
            mbSetEyePos = wait_2();
            break;
        case 5:
            mbSetEyePos = talk_1();
            break;
        }
        break;
    default:
        break;
    }
    return TRUE;
}

/* .text wait_action3 */
BOOL daNpc_Ym1_c::wait_action3(void*) {
    cXyz offset(0.0f, 0.0f, 110.0f);
    switch (mActionState) {
    case 0:
        if (chk_BlackPig()) {
            setStt(8);
            mbTurnHome = true;
            mActionState++;
        } else {
            setStt(6);
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(mAngle.y);
            mDoMtx_stack_c::multVec(&offset, &mNbtPos);
            mActionState++;
        }
        break;
    case 9:
        break;
    case 1:
    case 2:
    case 3:
        mbAttention = chkAttention();
        switch (mStt) {
        case 6:
            mbSetEyePos = NBTwai();
            break;
        case 7:
            mbSetEyePos = talk_1();
            break;
        case 8:
            mbSetEyePos = wait_2();
            break;
        case 5:
            mbSetEyePos = talk_1();
            break;
        }
        break;
    default:
        break;
    }
    return TRUE;
}

/* .text wait_action4 */
BOOL daNpc_Ym1_c::wait_action4(void*) {
    switch (mActionState) {
    case 0:
        setStt(11);
        mActionState++;
        break;
    case 9:
        break;
    case 1:
    case 2:
    case 3:
        mbAttention = chkAttention();
        switch (mStt) {
        case 11:
            mbSetEyePos = SITwai();
            break;
        case 5:
            mbSetEyePos = talk_1();
            break;
        }
        break;
    default:
        break;
    }
    return TRUE;
}

/* .text demo_action1 */
BOOL daNpc_Ym1_c::demo_action1(void*) {
    switch (mActionState) {
    case 0:
        mActionState++;
        break;
    case 9:
        break;
    case 1:
    case 2:
    case 3:
        mbAttention = chkAttention();
        break;
    default:
        break;
    }
    return TRUE;
}

/* .text demo */
bool daNpc_Ym1_c::demo() {
    if (demoActorID == 0) {
        if (mbDemo) {
            mbDemo = false;
        }
    } else {
        if (!mbDemo) {
            mbDemo = true;
            m89F = false;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);
        }

        dDemo_actor_c* demo_actor_p = dComIfGp_demo_getActor(demoActorID);
        if (mBtpAnm.getBtpAnm() != NULL) {
            mBtpFrame++;
            if (mBtpFrame >= mBtpAnm.getBtpAnm()->getFrameMax()) {
                mBtpFrame = mBtpAnm.getBtpAnm()->getFrameMax();
            }
        }

        J3DAnmTexPattern* demo_btp_p = demo_actor_p->getP_BtpData(mArcName);
        if (demo_btp_p) {
            mBtpAnm.init(mpHeadModel->getModelData(), demo_btp_p, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            mBtpNum = BTPNUM_NULL_e;
            mBtpFrame = 0;
        }

        dDemo_setDemoData(this, 106, mpMorf, mArcName, 0, NULL, 0, 0);
    }

    return mbDemo;
}

/* .text shadowDraw */
void daNpc_Ym1_c::shadowDraw() {
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f, current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr);

    if (mShadowID != 0) {
        if (mpItemModel) {
            dComIfGd_addRealShadow(mShadowID, mpItemModel);
        }
        dComIfGd_addRealShadow(mShadowID, mpHeadModel);
    }
}

static void dummy() {
    const GXColor dummy1 = {0xFF, 0x00, 0x00, 0x80};
    const GXColor dummy2 = {0x00, 0x00, 0xFF, 0x80};
    const GXColor dummy3 = {0xFF, 0xFF, 0x00, 0x80};
}

/* .text _draw */
BOOL daNpc_Ym1_c::_draw() {
    J3DModel* head_model_p = mpHeadModel;
    J3DModelData* head_model_info_p = head_model_p->getModelData();
    J3DModel* morf_model_p = mpMorf->getModel();

    if (m89E || m8A0 != 0) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model_p, &tevStr);
    g_env_light.setLightTevColorType(head_model_p, &tevStr);

    switch (mHioType) {
    case 1:
        mpMorf->entryDL();
        break;
    case 2:
        mpMorf->entryDL((J3DMaterialTable*)dComIfG_getObjectIDRes(mArcName, dRes_ID_YM_BMT_YM2_e));
        break;
    }

    mBtpAnm.entry(head_model_info_p, mBtpFrame);
    mDoExt_modelEntryDL(head_model_p);
    mBtpAnm.remove(head_model_info_p);

    if (mpItemModel) {
        g_env_light.setLightTevColorType(mpItemModel, &tevStr);
        mDoExt_modelEntryDL(mpItemModel);
    }

    shadowDraw();

    switch (mHioType) {
    case 1:
        dSnap_RegistFig(DSNAP_TYPE_UNK50, this, 1.0f, 1.0f, 1.0f);
        break;
    case 2:
        dSnap_RegistFig(DSNAP_TYPE_UNK4E, this, eyePos, shape_angle.y, 1.0f, 1.0f, 1.0f);
        break;
    }

    // Does nothing
    if (l_HIO.children[mHioType - 1].hio_prm.m18) {
        cXyz dummy = current.pos;
        dummy.y = eyePos.y;
    }

    mbPrevKari = mbKari;
    mbKari = false;

    return TRUE;
}

/* .text _execute */
BOOL daNpc_Ym1_c::_execute() {
    if (!mbInitDone) {
        mHomePos = current.pos;
        mHomeAngle = current.angle;
        mbInitDone = true;
    }

    if (chk_nbt_attn()) {
        m_jnt.setParam(0, 0, 0, 0, 0x2000, 0x38E0, -0x2000, -0x38E0, l_HIO.children[mHioType - 1].hio_prm.mMaxTurnStep);
    } else {
        m_jnt.setParam(
            l_HIO.children[mHioType - 1].hio_prm.mMaxBackBoneX,
            l_HIO.children[mHioType - 1].hio_prm.mMaxBackBoneY,
            l_HIO.children[mHioType - 1].hio_prm.mMinBackBoneX,
            l_HIO.children[mHioType - 1].hio_prm.mMinBackBoneY,
            l_HIO.children[mHioType - 1].hio_prm.mMaxHeadX,
            l_HIO.children[mHioType - 1].hio_prm.mMaxHeadY,
            l_HIO.children[mHioType - 1].hio_prm.mMinHeadX,
            l_HIO.children[mHioType - 1].hio_prm.mMinHeadY,
            l_HIO.children[mHioType - 1].hio_prm.mMaxTurnStep
        );
    }

    if (m89E && demoActorID == 0) {
        return TRUE;
    }

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

        lookBack();
        if (mType != 1) {
            fopAcM_posMoveF(this, mStts.GetCCMoveP());
            mObjAcch.CrrPos(*dComIfG_Bgsp());
        }
        play_animation();
    } else {
        m89E = false;
    }

    eventOrder();
    mAngle = current.angle;
    if (!m89F) {
        shape_angle = current.angle;
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);
    set_cutGrass();

    if (mType == 0) {
        dComIfG_Ccsp()->SetMassAreaChk(&mAreaCyl, 3, area_check);
    }

    if (!mbDemo) {
        set_collision_sp();
    }

    return TRUE;
}

/* .text _delete */
BOOL daNpc_Ym1_c::_delete() {
    dComIfG_resDelete(&mPhs, mArcName);
    if (heap && mpMorf) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* .text _create */
cPhs_State daNpc_Ym1_c::_create() {
    static int a_siz_tbl[] = {
        0,
        0,
        0,
    };

    fopAcM_ct(this, daNpc_Ym1_c);

    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    cPhs_State state = dComIfG_resLoad(&mPhs, mArcName);
    mbResLoadIsComplete = state == cPhs_COMPLEATE_e;
    if (!mbResLoadIsComplete) {
        return state;
    }

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[mHioType])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -80.0f, -20.0f, -40.0f, 80.0f, 180.0f, 130.0f);

    if (!createInit()) {
        return cPhs_ERROR_e;
    }

    return state;
}

daNpc_Ym1_c::daNpc_Ym1_c() {}

/* .text bodyCreateHeap */
BOOL daNpc_Ym1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_YM_BDL_YM_e);
    JUT_ASSERT(0x971, a_mdl_dat != NULL);

    mpMorf = new mDoExt_McaMorf(a_mdl_dat, NULL, NULL, NULL, J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL, 0x80000, 0x15021222);

    if (!mpMorf) {
        return FALSE;
    } else if (!mpMorf->getModel()) {
        mpMorf = NULL;
        return FALSE;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x97F, m_hed_jnt_num >= 0);

    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x981, m_bbone_jnt_num >= 0);

    m_hnd_L_jnt_num = a_mdl_dat->getJointName()->getIndex("handL");
    JUT_ASSERT(0x983, m_hnd_L_jnt_num >= 0);

    m_hnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("handR");
    JUT_ASSERT(0x985, m_hnd_R_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((uintptr_t)this);

    return TRUE;
}

/* .text headCreateHeap */
BOOL daNpc_Ym1_c::headCreateHeap() {
    static int a_hed_bdl_resID_tbl[] = {
        0,
        dRes_ID_YM_BDL_YMHEAD01_e,
        dRes_ID_YM_BDL_YMHEAD02_e,
    };
    static s8 a_tex_pttrn_num_tbl[] = {
        0,
        0,
        0,
    };

    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, a_hed_bdl_resID_tbl[mHioType]);
    JUT_ASSERT(0x9A4, a_mdl_dat != NULL);

    mpHeadModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x15020022);
    if (!mpHeadModel) {
        return FALSE;
    }

    return init_texPttrnAnm(a_tex_pttrn_num_tbl[mHioType], false) != false ? TRUE : FALSE;
}

/* .text itemCreateHeap */
BOOL daNpc_Ym1_c::itemCreateHeap() {
    if (mType == 0) {
        J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName, dRes_ID_YM_BDL_YMKAMA_e);
        JUT_ASSERT(0x9C6, a_mdl_dat != NULL);

        mpItemModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
        if (!mpItemModel) {
            return FALSE;
        }
    } else {
        mpItemModel = NULL;
    }

    return TRUE;
}

/* .text CreateHeap */
BOOL daNpc_Ym1_c::CreateHeap() {
    if (!bodyCreateHeap()) {
        return FALSE;
    }

    if (!headCreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }

    if (!itemCreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }

    mAcchCir.SetWall(30.0f, 60.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);

    return TRUE;
}

/* 000046D8-000046F8       .text daNpc_Ym1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ym1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ym1_c*)i_this)->_create();
}

/* 000046F8-00004718       .text daNpc_Ym1_Delete__FP11daNpc_Ym1_c */
static BOOL daNpc_Ym1_Delete(daNpc_Ym1_c* i_this) {
    return ((daNpc_Ym1_c*)i_this)->_delete();
}

/* 00004718-00004738       .text daNpc_Ym1_Execute__FP11daNpc_Ym1_c */
static BOOL daNpc_Ym1_Execute(daNpc_Ym1_c* i_this) {
    return ((daNpc_Ym1_c*)i_this)->_execute();
}

/* 00004738-00004758       .text daNpc_Ym1_Draw__FP11daNpc_Ym1_c */
static BOOL daNpc_Ym1_Draw(daNpc_Ym1_c* i_this) {
    return ((daNpc_Ym1_c*)i_this)->_draw();
}

/* 00004758-00004760       .text daNpc_Ym1_IsDelete__FP11daNpc_Ym1_c */
static BOOL daNpc_Ym1_IsDelete(daNpc_Ym1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ym1_Method = {
    (process_method_func)daNpc_Ym1_Create,
    (process_method_func)daNpc_Ym1_Delete,
    (process_method_func)daNpc_Ym1_Execute,
    (process_method_func)daNpc_Ym1_IsDelete,
    (process_method_func)daNpc_Ym1_Draw,
};

actor_process_profile_definition g_profile_NPC_YM1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_YM1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ym1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_YM1_e,
    /* Actor SubMtd */ &l_daNpc_Ym1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_YM2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_YM2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ym1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_YM2_e,
    /* Actor SubMtd */ &l_daNpc_Ym1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
