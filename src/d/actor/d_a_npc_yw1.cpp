/**
 * d_a_npc_yw1.cpp
 * NPC - Sue-Belle
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_yw1.h"
#include "d/actor/d_a_npc_bm1.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_wether.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_hostIO.h"
#include "m_Do/m_Do_lib.h"
#include "res/Object/Yw.h"

class daNpc_Yw1_childHIO_c : public mDoHIO_entry_c {
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
        /* 0x1C */ f32 mAreaDist;
        /* 0x20 */ s16 mWalkTurnScale;
        /* 0x22 */ s16 mWalkTurnMaxStep;
        /* 0x24 */ f32 mWalkAnmRate;
        /* 0x28 */ f32 mWalkSpeed;
        /* 0x2C */ f32 mWalkAccel;
    };  // Size: 0x30

    daNpc_Yw1_childHIO_c();
    void genMessage(JORMContext* ctx) { UNUSED(ctx); };

public:
    /* 0x04 */ hio_prm_c hio_prm;
    /* 0x34 */ u32 m34;
};  // Size: 0x38

class daNpc_Yw1_HIO_c : public mDoHIO_entry_c {
public:
    daNpc_Yw1_HIO_c();
    virtual ~daNpc_Yw1_HIO_c() {}
    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 m4;
    /* 0x08 */ s32 m8;
    /* 0x0C */ daNpc_Yw1_childHIO_c children[1];
};  // Size: 0x44

static daNpc_Yw1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static int l_check_wrk;

/* 000000EC-00000108       .text __ct__20daNpc_Yw1_childHIO_cFv */
daNpc_Yw1_childHIO_c::daNpc_Yw1_childHIO_c() {
}

/* 00000150-000001DC       .text __ct__15daNpc_Yw1_HIO_cFv */
daNpc_Yw1_HIO_c::daNpc_Yw1_HIO_c() {
    static daNpc_Yw1_childHIO_c::hio_prm_c a_prm_tbl[] = {
        {
            /* mMaxHeadX        */ 0x2000,
            /* mMaxHeadY        */ 0x1E78,
            /* mMinHeadX        */ -0x2000,
            /* mMinHeadY        */ -0x1E78,
            /* mMaxBackBoneX    */ 0x0000,
            /* mMaxBackBoneY    */ 0x20D0,
            /* mMinBackBoneX    */ 0x0000,
            /* mMinBackBoneY    */ -0x20D0,
            /* mMaxTurnStep     */ 0x0640,
            /* mMaxHeadTurnVel  */ 0x04B0,
            /* mAttPosOffsetY   */ 170.0f,
            /* m18              */ 0,
            /* mAreaDist        */ 300.0f,
            /* mWalkTurnScale   */ 6,
            /* mWalkTurnMaxStep */ 0x400,
            /* mWalkAnmRate     */ 0.95f,
            /* mWalkSpeed       */ 1.2f,
            /* mWalkAccel       */ 0.5f,
        },
    };
    for (int i = 0; i < 1; i++) {
        children[i].m34 = i;
        memcpy(&children[i].hio_prm, &a_prm_tbl[i], sizeof(daNpc_Yw1_childHIO_c::hio_prm_c));
    }
    m4 = -1;
    m8 = -1;
}

/* 00000238-00000284       .text nodeCB_Hair__FP7J3DNodei */
static BOOL nodeCB_Hair(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Yw1_c* actor_p = (daNpc_Yw1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Hair(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 00000284-00000414       .text _nodeCB_Hair__11daNpc_Yw1_cFP7J3DNodeP8J3DModel */
void daNpc_Yw1_c::_nodeCB_Hair(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(18.0f, 20.0f, 0.0f);

    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    if (m_hair1 == jnt_no) {
        mDoMtx_stack_c::YrotM(mHair1RotY);
        mDoMtx_stack_c::ZrotM(mHair1RotZ + mHairRotX + mHair1Wind);
    } else if (m_hair2 == jnt_no) {
        mDoMtx_stack_c::YrotM(mHair2RotY);
        mDoMtx_stack_c::ZrotM(mHair2RotZ + mHair2Wind);
    } else if (m_hair3 == jnt_no) {
        mDoMtx_stack_c::YrotM(mHair3RotY);
        mDoMtx_stack_c::ZrotM(mHair3RotZ + mHair3Wind);
    }

    mDoMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 00000450-0000049C       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Yw1_c* actor_p = (daNpc_Yw1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_Head(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 0000049C-000005BC       .text _nodeCB_Head__11daNpc_Yw1_cFP7J3DNodeP8J3DModel */
void daNpc_Yw1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_model) {
    static cXyz a_eye_pos_off(18.0f, 20.0f, 0.0f);

    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    mHeadPos.x = mDoMtx_stack_c::get()[0][3];
    mHeadPos.y = mDoMtx_stack_c::get()[1][3];
    mHeadPos.z = mDoMtx_stack_c::get()[2][3];

    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &mTransformedEyePos);

    mDoMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 000005BC-00000608       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In && j3dSys.getModel()->getUserArea() != 0) {
        daNpc_Yw1_c* actor_p = (daNpc_Yw1_c*)j3dSys.getModel()->getUserArea();
        actor_p->_nodeCB_BackBone(i_node, j3dSys.getModel());
    }
    return TRUE;
}

/* 00000608-000006A8       .text _nodeCB_BackBone__11daNpc_Yw1_cFP7J3DNodeP8J3DModel */
void daNpc_Yw1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());

    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 000006A8-000006C8       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Yw1_c*)i_this)->CreateHeap();
}

/* 000006C8-00000740       .text searchActor_Bm1__FPvPv */
static void* searchActor_Bm1(void* i_actor, void*) {
    if (l_check_wrk < ARRAY_SSIZE(l_check_inf) && fopAc_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_NPC_BM1_e) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actor;
        l_check_wrk++;
    }
    return NULL;
}

/* 00000740-00000844       .text init_YW1_0__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::init_YW1_0() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && !dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)) {
        if (!mPath.isPath()) {
            return false;
        }
        mbCarry = true;
        mTsuboID = fopAcM_create(fpcNm_TSUBO_e, 0x7F063F, &current.pos, fopAcM_GetRoomNo(this), NULL, NULL, -1, NULL);
        set_action(&daNpc_Yw1_c::wait_action1, NULL);
        set_pthPoint(0);
        return mTsuboID != fpcM_ERROR_PROCESS_ID_e;
    }
    return false;
}

/* 00000844-000008F8       .text init_YW1_1__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::init_YW1_1() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)) {
            fopAcM_ClearStatusMap(this);
        }
        set_action(&daNpc_Yw1_c::wait_action2, NULL);
        mbHide = true;
        return true;
    }
    return false;
}

/* 000008F8-000009A4       .text init_YW1_2__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::init_YW1_2() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && (dKy_daynight_check() == 1 || !dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED))) {
        set_action(&daNpc_Yw1_c::wait_action2, NULL);
        return true;
    }
    return false;
}

/* 000009A4-00000AB4       .text init_YW1_3__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::init_YW1_3() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520) && dKy_daynight_check() == 0) {
        if (!mPath.isPath()) {
            return false;
        }
        if (dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED)) {
            mbCarry = true;
            mTsuboID = fopAcM_create(fpcNm_TSUBO_e, 0x7F063F, &current.pos, fopAcM_GetRoomNo(this), NULL, NULL, -1, NULL);
            set_action(&daNpc_Yw1_c::wait_action1, NULL);
            set_pthPoint(0);
            return mTsuboID != fpcM_ERROR_PROCESS_ID_e;
        }
    }
    return false;
}

/* 00000AB4-00000C9C       .text createInit__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::createInit() {
    mEventCut.setActorInfo2("Yw1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAB;

    int weight = 0xFF;
    u8 path_no = (fopAcM_GetParam(this) >> 16) & 0xFF;
    if (path_no != 0xFF) {
        mPath.setInf(path_no, fopAcM_GetRoomNo(this), true);
        if (mPath.isPath()) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            weight = 0xF0;
        } else {
            return false;
        }
    }

    mBckNum = BCKNUM_NULL_e;

    bool init_result;
    switch (mType) {
    case 0:
        init_result = init_YW1_0();
        break;
    case 1:
        init_result = init_YW1_1();
        break;
    case 2:
        init_result = init_YW1_2();
        break;
    case 3:
        init_result = init_YW1_3();
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

    mStts.Init(weight, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);

    play_animation();
    mObjAcch.CrrPos(*dComIfG_Bgsp());

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(true);

    return true;
}

/* 00000C9C-00000D44       .text play_animation__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::play_animation() {
    u32 snd_id = 0;

    play_texPttrnAnm();

    if (mObjAcch.ChkGroundHit()) {
        snd_id = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }

    mbMorfAnimStopped = mpMorf->play(&eyePos, snd_id, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));

    if (mpMorf->getFrame() < mPrevMorfFrame) {
        mbMorfAnimStopped = true;
    }

    mPrevMorfFrame = mpMorf->getFrame();
}

static cXyz l_hed_front(0.0f, 1.0f, 0.0f);

/* 00000D44-00000E4C       .text upLift__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::upLift() {
    int not_found;
    fopAc_ac_c* tsubo_p = searchByID(mTsuboID, &not_found);
    mbTsuboBroken = not_found == 1;
    if (tsubo_p) {
        if (!fopAcM_checkCarryNow(tsubo_p)) {
            fopAcM_setCarryNow(tsubo_p, FALSE);
        }
        cXyz front;
        cXyz offset(34.0f, -4.0f, 0.0f);
        mDoMtx_multVecSR(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num), &l_hed_front, &front);
        tsubo_p->shape_angle.y = cM_atan2s(front.x, front.z);
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        mDoMtx_stack_c::multVec(&offset, &tsubo_p->current.pos);
    }
    return mbTsuboBroken;
}

/* 00000E4C-00000F48       .text setMtx__11daNpc_Yw1_cFb */
void daNpc_Yw1_c::setMtx(bool i_setEyePos) {
    mpMorf->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(mAngle);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());

    mpMorf->calc();

    setHairAngle();

    mpHeadModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
    mpHeadModel->calc();

    upLift();
    setAttention(i_setEyePos);
}

/* 00000F48-00000F5C       .text bckResID__11daNpc_Yw1_cFi */
int daNpc_Yw1_c::bckResID(int i_bckNum) {
    static const int a_res_id_tbl[] = {
        dRes_ID_YW_BCK_WAIT01_e,
        dRes_ID_YW_BCK_YW_TWAIT_e,
        dRes_ID_YW_BCK_YW_TWALK_e,
        dRes_ID_YW_BCK_YW_TTALK_e,
        dRes_ID_YW_BCK_YW_TALK01_e,
        dRes_ID_YW_BCK_YW_WAIT02_e,
        dRes_ID_YW_BCK_YW_TALK02_e,
    };
    return a_res_id_tbl[i_bckNum];
}

/* 00000F5C-00000F70       .text btpResID__11daNpc_Yw1_cFi */
int daNpc_Yw1_c::btpResID(int i_btpNum) {
    static const int a_res_id_tbl[] = {
        dRes_ID_YW_BTP_YWHEAD01_e,
    };
    return a_res_id_tbl[i_btpNum];
}

/* 00000F70-00001078       .text init_texPttrnAnm__11daNpc_Yw1_cFScb */
bool daNpc_Yw1_c::init_texPttrnAnm(s8 i_btpNum, bool i_bModify) {
    J3DModel* head_model_p = mpHeadModel;

    if (i_btpNum < 0) {
        return false;
    }

    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Yw", btpResID(i_btpNum));
    JUT_ASSERT(0x28A, a_btp != NULL);
    mBtpNum = i_btpNum;
    mBtpFrame = 0;
    mBlinkTimer = 0;

    return mBtpAnm.init(head_model_p->getModelData(), a_btp, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, i_bModify, 0) != 0;
}

/* 00001078-00001108       .text play_texPttrnAnm__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::play_texPttrnAnm() {
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

/* 00001108-000011AC       .text setAnm_anm__11daNpc_Yw1_cFPQ211daNpc_Yw1_c9anm_prm_c */
void daNpc_Yw1_c::setAnm_anm(anm_prm_c* i_anmPrmP) {
    if (i_anmPrmP->bckNum < 0 || mBckNum == i_anmPrmP->bckNum) {
        return;
    }

    dNpc_setAnmIDRes(mpMorf, i_anmPrmP->loopMode, i_anmPrmP->morf, i_anmPrmP->speed, bckResID(i_anmPrmP->bckNum), -1, "Yw");
    mBckNum = i_anmPrmP->bckNum;
    mbMorfAnimStopped = false;
    m771 = 0;
    mPrevMorfFrame = 0.0f;
}

/* 000011AC-0000121C       .text setAnm_NUM__11daNpc_Yw1_cFii */
void daNpc_Yw1_c::setAnm_NUM(int i_anmNum, int i_setBtp) {
    static anm_prm_c a_anm_prm_tbl[7] = {
        {BCKNUM_WAIT01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TWAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TWALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TTALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    if (i_setBtp) {
        init_texPttrnAnm(a_anm_prm_tbl[i_anmNum].btpNum, true);
    }
    setAnm_anm(&a_anm_prm_tbl[i_anmNum]);
}

/* 0000121C-00001288       .text setAnm__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[7] = {
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_WAIT02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {-1, -1, 0.0f, 0.0f, J3DFrameCtrl::EMode_NULL},
        {BCKNUM_TWALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TWALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mStt].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mStt]);
}

/* 00001288-0000128C       .text chngAnmTag__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::chngAnmTag() {
}

/* 0000128C-00001290       .text ctrlAnmTag__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::ctrlAnmTag() {
}

/* 00001290-000012D0       .text chngAnmAtr__11daNpc_Yw1_cFUc */
void daNpc_Yw1_c::chngAnmAtr(u8 i_atr) {
    if (i_atr == mAnmAtr || i_atr > 7) {
        return;
    }
    mAnmAtr = i_atr;
    setAnm_ATR();
}

/* 000012D0-000012D4       .text ctrlAnmAtr__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::ctrlAnmAtr() {
}

/* 000012D4-00001338       .text setAnm_ATR__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::setAnm_ATR() {
    static anm_prm_c a_anm_prm_tbl[7] = {
        {BCKNUM_WAIT01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TWAIT_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TWALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TTALK_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK01_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_WAIT02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
        {BCKNUM_TALK02_e, BTPNUM_HEAD_e, 8.0f, 1.0f, J3DFrameCtrl::EMode_LOOP},
    };

    init_texPttrnAnm(a_anm_prm_tbl[mAnmAtr].btpNum, true);
    setAnm_anm(&a_anm_prm_tbl[mAnmAtr]);
}

/* 00001338-000013F4       .text anmAtr__11daNpc_Yw1_cFUs */
void daNpc_Yw1_c::anmAtr(u16 i_msgStatus) {
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

/* 000013F4-0000148C       .text next_msgStatus__11daNpc_Yw1_cFPUl */
u16 daNpc_Yw1_c::next_msgStatus(u32* o_msgNoP) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    switch (*o_msgNoP) {
    case 0x8A3:
        if (!dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED)) {
            *o_msgNoP = 0x8A4;
        } else if (dKy_daynight_check() == 0) {
            *o_msgNoP = 0x8A6;
        } else {
            *o_msgNoP = 0x8A5;
        }
        break;
    default:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return msg_status;
}

/* 0000148C-00001588       .text getMsg_YW1_0__11daNpc_Yw1_cFv */
u32 daNpc_Yw1_c::getMsg_YW1_0() {
    if (mbPaid) {
        return 0x8A0;
    }
    if (mbTsuboBroken) {
        return 0x89F;
    }
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0140) ? 0x89C : 0x89B;
    }
    if (mPath.isPath() && mbPathEnd == 1) {
        return mPath.getDir() == 1 ? 0x8A2 : 0x8A1;
    }
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0180)) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_2A80) ? 0x8AA : 0x899;
    }
    return 0x89A;
}

/* 00001588-00001600       .text getMsg_YW1_1__11daNpc_Yw1_cFv */
u32 daNpc_Yw1_c::getMsg_YW1_1() {
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0E20)) {
        return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0120) ? 0x89E : 0x89D;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_0140) ? 0x89C : 0x89B;
}

/* 00001600-00001678       .text getMsg_YW1_2__11daNpc_Yw1_cFv */
u32 daNpc_Yw1_c::getMsg_YW1_2() {
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A40)) {
        return 0x8A3;
    }
    if (!dComIfGs_isEventBit(dSv_event_flag_c::GRANDMA_HEALED)) {
        return 0x8A7;
    }
    return dKy_daynight_check() == 0 ? 0x8A9 : 0x8A8;
}

/* 00001678-000016F0       .text getMsg_YW1_3__11daNpc_Yw1_cFv */
u32 daNpc_Yw1_c::getMsg_YW1_3() {
    if (mbPaid) {
        return 0x8A0;
    }
    if (mbTsuboBroken) {
        return 0x89F;
    }
    if (mPath.isPath() && mbPathEnd == 1) {
        return mPath.getDir() == 1 ? 0x8A2 : 0x8A1;
    }
    return getMsg_YW1_2();
}

/* 000016F0-00001770       .text getMsg__11daNpc_Yw1_cFv */
u32 daNpc_Yw1_c::getMsg() {
    u32 result = 0;
    switch (mType) {
    case 0:
        result = getMsg_YW1_0();
        break;
    case 1:
        result = getMsg_YW1_1();
        break;
    case 2:
        result = getMsg_YW1_2();
        break;
    case 3:
        result = getMsg_YW1_3();
        break;
    }
    return result;
}

/* 00001770-000017C0       .text eventOrder__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::eventOrder() {
    if (mOrder == 1 || mOrder == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mOrder == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 000017C0-00001800       .text checkOrder__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
    } else if (eventInfo.checkCommandTalk()) {
        if (mOrder == 1 || mOrder == 2) {
            mOrder = 0;
            mbTalkReq = true;
        }
    }
}

/* 00001800-00001898       .text chk_talk__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::chk_talk() {
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

/* 00001898-000018D8       .text chk_parts_notMov__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::chk_parts_notMov() {
    bool ret = false;
    if (mJointHeadY == m_jnt.getHead_y() && mJointBackboneY == m_jnt.getBackbone_y() && mActorAngleY == current.angle.y) {
        ret = true;
    }
    return ret;
}

/* 000018D8-00001938       .text searchByID__11daNpc_Yw1_cFUiPi */
fopAc_ac_c* daNpc_Yw1_c::searchByID(fpc_ProcID i_PID, int* o_notFound) {
    fopAc_ac_c* actor_p = NULL;
    if (o_notFound) {
        *o_notFound = 0;
    }
    if (!fopAcM_SearchByID(i_PID, &actor_p) && o_notFound) {
        *o_notFound = 1;
    }
    return actor_p;
}

/* 00001938-000019E8       .text partner_search_sub__11daNpc_Yw1_cFPFPvPv_Pv */
bool daNpc_Yw1_c::partner_search_sub(void* (*i_searchFunc)(void*, void*)) {
    bool ret = false;

    mPartnerID = fpcM_ERROR_PROCESS_ID_e;
    l_check_wrk = 0;
    for (int i = 0; i < ARRAY_SSIZE(l_check_inf); i++) {
        l_check_inf[i] = NULL;
    }

    fpcM_Search(i_searchFunc, this);

    if (l_check_wrk != 0) {
        mPartnerID = fopAcM_GetID(l_check_inf[0]);
        ret = true;
    }
    return ret;
}

/* 000019E8-00001A54       .text partner_search__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::partner_search() {
    if (mActionState == 1) {
        bool found;
        switch (mType) {
        case 0:
            found = partner_search_sub(searchActor_Bm1);
            break;
        default:
            found = true;
            break;
        }
        if (found) {
            mActionState++;
        }
    }
}

// Stripped function, only its constant remains in .rodata
static f32 dummy_deg2s(f32 i_deg) {
    return i_deg * (32767.0f / 180.0f);
}

/* 00001A54-00001C2C       .text lookBack__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::lookBack() {
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
    bool head_only = mbHeadOnly;

    switch (mLookMode) {
    case 1:
        player_eye_pos = dNpc_playerEyePos(-20.0f);
        player_eye_pos_p = &player_eye_pos;
        break;
    case 2:
        player_eye_pos = mLookPos;
        player_eye_pos_p = &player_eye_pos;
        break;
    case 3:
        target_y = mTargetAngleY;
        break;
    case 4: {
        fopAc_ac_c* actor_p = searchByID(mLookID, NULL);
        if (actor_p) {
            mLookPos = actor_p->current.pos;
            mLookPos.y = actor_p->eyePos.y;
            player_eye_pos = mLookPos;
            player_eye_pos_p = &player_eye_pos;
        }
        break;
    }
    }

    cLib_addCalcAngleS2(&mHeadTurnVel, l_HIO.children[mHioType].hio_prm.mMaxHeadTurnVel, 4, 0x800);
    if (!m_jnt.trnChk()) {
        mHeadTurnVel = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, player_eye_pos_p, current_pos, target_y, mHeadTurnVel, head_only);
}

/* 00001C2C-00001CAC       .text chkAttention__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* 00001CAC-00001D28       .text setAttention__11daNpc_Yw1_cFb */
void daNpc_Yw1_c::setAttention(bool i_setEyePos) {
    f32 offset_y = l_HIO.children[mHioType].hio_prm.mAttPosOffsetY;
    cXyz pos = current.pos;
    attention_info.position.set(pos.x, pos.y + offset_y, pos.z);

    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(mTransformedEyePos.x, mTransformedEyePos.y, mTransformedEyePos.z);
}

/* 00001D28-00001DC4       .text decideType__11daNpc_Yw1_cFi */
bool daNpc_Yw1_c::decideType(int i_type) {
    mHioType = 0;
    mType = -1;

    switch (i_type) {
    case 0:
        mType = 0;
        break;
    case 1:
        mType = 1;
        break;
    case 2:
        mType = 2;
        break;
    case 3:
        mType = 3;
        break;
    default:
        return false;
    }

    return mHioType != -1 && mType != -1;
}

/* 00001DC4-00001E64       .text privateCut__11daNpc_Yw1_cFi */
void daNpc_Yw1_c::privateCut(int i_staffIdx) {
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

/* 00001E64-00001E88       .text endEvent__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::endEvent() {
    dComIfGp_event_reset();
    mAnmAtr = 0xFF;
    mMesgAnimeTag = 0xFF;
}

/* 00001E88-00001EC0       .text isEventEntry__11daNpc_Yw1_cFv */
int daNpc_Yw1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 00001EC0-00001F18       .text event_proc__11daNpc_Yw1_cFi */
void daNpc_Yw1_c::event_proc(int i_staffIdx) {
    if (!mEventCut.cutProc()) {
        privateCut(i_staffIdx);
    }
    lookBack();
}

/* 00001F18-00001FC4       .text set_action__11daNpc_Yw1_cFM11daNpc_Yw1_cFPCvPvPv_iPv */
BOOL daNpc_Yw1_c::set_action(ProcFunc i_newProcFunc, void* i_argsP) {
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

/* 00001FC4-0000205C       .text setStt__11daNpc_Yw1_cFSc */
void daNpc_Yw1_c::setStt(s8 i_stt) {
    u8 prev_stt = mStt;
    mStt = i_stt;
    switch (mStt) {
    case 2:
        mAnmAtr = 0xFF;
        mMesgAnimeTag = 0xFF;
        mMsgCount = 0;
        mPrevStt = prev_stt;
        break;
    case 3:
    case 5:
        mbHeadOnly = true;
        break;
    case 4:
    case 6:
        break;
    }
    setAnm();
    chngTsuboAnm();
}

/* 0000205C-0000212C       .text chngTsuboAnm__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::chngTsuboAnm() {
    if (mbCarry) {
        if (!mbTsuboBroken) {
            switch (mBckNum) {
            case BCKNUM_TALK01_e:
                setAnm_NUM(3, 1);
                break;
            case BCKNUM_WAIT02_e:
                setAnm_NUM(1, 1);
                break;
            }
        } else {
            switch (mBckNum) {
            case BCKNUM_TWAIT_e:
                setAnm_NUM(5, 1);
                break;
            case BCKNUM_TTALK_e:
                setAnm_NUM(4, 1);
                break;
            case BCKNUM_TWALK_e:
                break;
            }
            mbCarry = false;
        }
    }
}

/* 0000212C-000022B8       .text chk_areaIN__11daNpc_Yw1_cFffs4cXyz */
bool daNpc_Yw1_c::chk_areaIN(f32 i_dist, f32 i_height, s16 i_angle, cXyz i_pos) {
    f32 dist = (dComIfGp_getLinkPlayer()->current.pos - i_pos).absXZ();
    f32 dy = dComIfGp_getLinkPlayer()->current.pos.y - i_pos.y;
    int target = cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos);
    s16 angle = target - current.angle.y;
    if (dist < i_dist && std::fabsf(dy) < i_height && abs(angle) < i_angle) {
        return true;
    }
    return false;
}

/* 000022B8-00002360       .text set_pthPoint__11daNpc_Yw1_cFUc */
void daNpc_Yw1_c::set_pthPoint(u8 i_idx) {
    if (mPath.isPath()) {
        mPath.setIdx(i_idx);
        current.pos = mPath.getPoint(mPath.getIdx());
        if (mPath.nextIdx()) {
            cXyz next = mPath.getPoint(mPath.getIdx());
            current.angle.y = cLib_targetAngleY(&current.pos, &next);
        }
    }
}

static const Vec l_eye_offset = {15.0f, 10.0f, 0.0f};
static const Vec l_head_center_offset = {15.0f, 0.0f, 0.0f};
static const Vec l_neck_front = {0.0f, 1.0f, 0.0f};
static const Vec l_neck_top = {1.0f, 0.0f, 0.0f};

/* 00002360-00002D94       .text setHairAngle__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::setHairAngle() {
    cXyz neck_front;
    cXyz neck_top;
    cXyz head_center;
    cXyz eye;
    cXyz dir;
    cXyz head_pos;
    cXyz move;
    cXyz wind_vec;
    f32 wind_pow;

    MtxP head_mtx = mpMorf->getModel()->getAnmMtx(m_hed_jnt_num);
    mDoMtx_multVec(head_mtx, &l_head_center_offset, &head_center);
    mDoMtx_multVec(head_mtx, &l_eye_offset, &eye);
    dir = eye - head_center;
    s16 head_angle = cM_atan2s(dir.x, dir.z);
    f32 sin = cM_ssin(head_angle);
    f32 cos = cM_scos(head_angle);

    head_mtx = mpMorf->getModel()->getAnmMtx(m_hed_jnt_num);
    head_pos.x = head_mtx[0][3];
    head_pos.y = head_mtx[1][3];
    head_pos.z = head_mtx[2][3];

    dKyw_get_AllWind_vec(&head_pos, &wind_vec, &wind_pow);
    f32 wind = wind_pow * wind_pow;

    mDoMtx_multVecSR(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num), &l_neck_front, &neck_front);
    mDoMtx_multVecSR(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num), &l_neck_top, &neck_top);

    s16 prev_rot_x = mHairRotX;
    s16 prev_rot_y = mHairRotY;
    if (neck_top.y < 0.0f) {
        mHairRotX = cM_atan2s(neck_front.y, -neck_front.absXZ());
        mHairRotY = cM_atan2s(neck_front.x, neck_front.z) + 0x8000;
    } else {
        mHairRotX = cM_atan2s(neck_front.y, neck_front.absXZ());
        mHairRotY = cM_atan2s(neck_front.x, neck_front.z);
    }
    if (std::fabsf(neck_front.y) > 0.7f) {
        mHairRotY = prev_rot_y;
    }

    s16 d_rot_x = (s16)(mHairRotX - prev_rot_x) / 2;
    s16 d_rot_y = (s16)(mHairRotY - prev_rot_y) / 2;
    if (d_rot_x > 0x200) {
        d_rot_x = 0x200;
    } else if (d_rot_x < -0x200) {
        d_rot_x = -0x200;
    }
    if (d_rot_y > 0x800) {
        d_rot_y = 0x800;
    } else if (d_rot_y < -0x800) {
        d_rot_y = -0x800;
    }

    move.x = mPrevHeadPos.x - head_pos.x;
    move.y = (mPrevHeadPos.y - head_pos.y) - 7.5f;
    move.z = mPrevHeadPos.z - head_pos.z;
    move += wind_vec * wind;
    if (std::fabsf(move.x) < 0.01f) {
        move.x = 0.0f;
    }
    if (std::fabsf(move.z) < 0.01f) {
        move.z = 0.0f;
    }

    s16 d_z;
    s16 d_y;
    s16 prev_z = mHair1RotZ;
    s16 prev_y = mHair1RotY;
    f32 fwd = move.z * cos + move.x * sin;
    s16 target = cM_atan2s(-fwd, -move.y);
    if (mHair1RotZ < 0) {
        target = 0;
    } else if (target < 0 && target > -0x7800) {
        target = 0;
    } else if (target > 0x7800 || target <= -0x7800) {
        target = 0x7800;
    }
    cLib_addCalcAngleS2(&mHair1RotZ, target, 5, 0x400);
    mHair1RotZ = mHair1VelZ + d_rot_x + mHair1RotZ;

    target = cM_atan2s(-(move.x * cos - move.z * sin), std::sqrtf(fwd * fwd + move.y * move.y));
    if (target > 0x3800) {
        target = 0x3800;
    } else if (target < -0x3800) {
        target = -0x3800;
    }
    cLib_addCalcAngleS2(&mHair1RotY, target, 5, 0x400);
    mHair1RotY += mHair1VelY - d_rot_y;
    mHair1VelZ = 0.2f * (s16)(mHair1RotZ - prev_z);
    mHair1VelY = 0.2f * (s16)(mHair1RotY - prev_y);

    d_z = mHair1RotZ - prev_z;
    d_y = mHair1RotY - prev_y;
    mHair2RotZ -= d_z;
    mHair2RotY -= d_y;
    prev_z = mHair2RotZ;
    prev_y = mHair2RotY;
    cLib_addCalcAngleS2(&mHair2RotZ, 0, 5, 0x400);
    cLib_addCalcAngleS2(&mHair2RotY, 0, 5, 0x400);
    mHair2RotZ = mHair2VelZ + d_rot_x + mHair2RotZ;
    mHair2RotY += mHair2VelY - d_rot_y;
    mHair2VelZ = 0.2f * (s16)(mHair2RotZ - prev_z);
    mHair2VelY = 0.2f * (s16)(mHair2RotY - prev_y);

    target = mHair2RotZ - prev_z;
    d_z = mHair2RotY - prev_y;
    mHair3RotZ -= target;
    mHair3RotY -= d_z;
    prev_z = mHair3RotZ;
    prev_y = mHair3RotY;
    cLib_addCalcAngleS2(&mHair3RotZ, 0, 5, 0x400);
    cLib_addCalcAngleS2(&mHair3RotY, 0, 5, 0x400);
    mHair3RotZ = mHair3VelZ + d_rot_x + mHair3RotZ;
    mHair3RotY += mHair3VelY - d_rot_y;
    mHair3VelZ = 0.2f * (s16)(mHair3RotZ - prev_z);
    mHair3VelY = 0.2f * (s16)(mHair3RotY - prev_y);

    f32 pow = (wind + 0.65f * mPrevHeadPos.abs(head_pos)) / 4.0f;
    if (pow > 1.0f) {
        pow = 1.0f;
    }
    s16 step = 1500.0f + 4096.0f * pow;
    mWindPhase += step;
    mHair1Wind = 2280.0f * pow * cM_scos(mWindPhase);
    mHair2Wind = 3908.0f * pow * cM_scos(mWindPhase - 3.0f * step);
    mHair3Wind = 7568.0f * pow * cM_scos(mWindPhase - 6.0f * step);

    mPrevHeadPos = head_pos;
}

/* 00002D94-00002DEC       .text chk_brkTsubo__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::chk_brkTsubo() {
    if (mbTsuboBroken) {
        setStt(4);
        speedF = 0.0f;
        mLookMode = 0;
        mbHeadOnly = false;
    }
    return mbTsuboBroken;
}

/* 00002DEC-00002E28       .text chk_bm1Odoroki__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::chk_bm1Odoroki() {
    daNpc_Bm1_c* bm1_p = (daNpc_Bm1_c*)searchByID(mPartnerID, NULL);
    if (bm1_p) {
        return bm1_p->getOdoroki();
    }
    return false;
}

/* 00002E28-00002F90       .text wait_1__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::wait_1() {
    if (chk_brkTsubo()) {
        return TRUE;
    }

    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
            mLookMode = 1;
            mbHeadOnly = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }

    if (chk_bm1Odoroki()) {
        mLookMode = 4;
        mLookID = mPartnerID;
        return TRUE;
    }

    mOrder = 2;
    chngTsuboAnm();

    if (chk_areaIN(100.0f + l_HIO.children[mHioType].hio_prm.mAreaDist, 100.0f, 0x4400, current.pos) == false) {
        if (cLib_calcTimer(&mLookTimer) == 0) {
            setStt(3);
            mLookMode = 0;
            mbHeadOnly = true;
            return TRUE;
        }
    } else {
        mLookTimer = cLib_getRndValue(10, 20);
    }

    mLookMode = 1;
    return TRUE;
}

/* 00002F90-0000309C       .text wait_2__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::wait_2() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
            mLookMode = 1;
            mbHeadOnly = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }

    if (chk_bm1Odoroki()) {
        mLookMode = 4;
        mLookID = mPartnerID;
        mbHeadOnly = false;
        m_jnt.setTrn();
        return TRUE;
    }

    mOrder = 2;
    mbHeadOnly = true;
    cLib_addCalcAngleS(&current.angle.y, mHomeAngle.y, 4, 0x800, 0x80);
    if (mbAttention) {
        mLookTimer = cLib_getRndValue(10, 20);
    }
    if (cLib_calcTimer(&mLookTimer) != 0) {
        mLookMode = 1;
        return TRUE;
    }
    mLookMode = 0;
    return TRUE;
}

/* 0000309C-00003174       .text wait_3__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::wait_3() {
    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
            mLookMode = 1;
            mbHeadOnly = false;
            m_jnt.setTrn();
        }
        return TRUE;
    }

    mOrder = 2;
    mbHeadOnly = true;
    cLib_addCalcAngleS(&current.angle.y, mHomeAngle.y, 4, 0x800, 0x80);
    if (mbAttention) {
        mLookTimer = cLib_getRndValue(10, 20);
    }
    if (cLib_calcTimer(&mLookTimer) != 0) {
        mLookMode = 1;
        return TRUE;
    }
    mLookMode = 0;
    return TRUE;
}

/* 00003174-0000347C       .text walk_1__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::walk_1() {
    if (chk_brkTsubo()) {
        return TRUE;
    }

    if (!mbPathEnd) {
        if (mPath.chkPointPass(current.pos, mPath.getDir())) {
            mbPathEnd = !mPath.nextIdx();
        }
    }

    f32 target_speed;
    if (!mbPathEnd && chk_areaIN(l_HIO.children[mHioType].hio_prm.mAreaDist, 100.0f, 0x4000, current.pos) == false && !mbTalkReq && !chk_bm1Odoroki()) {
        cXyz point = mPath.getPoint(mPath.getIdx());
        int target = cLib_targetAngleY(&current.pos, &point);
        cLib_addCalcAngleS(&current.angle.y, target, l_HIO.children[mHioType].hio_prm.mWalkTurnScale, l_HIO.children[mHioType].hio_prm.mWalkTurnMaxStep, 0);
        target_speed = l_HIO.children[mHioType].hio_prm.mWalkSpeed;
    } else {
        target_speed = 0.0f;
    }

    cLib_chaseF(&speedF, target_speed, l_HIO.children[mHioType].hio_prm.mWalkAccel);

    f32 rate = speedF * l_HIO.children[mHioType].hio_prm.mWalkAnmRate;
    f32 anm_speed = rate < 0.5f ? 0.5f : rate;
    mpMorf->setPlaySpeed(anm_speed);

    if ((int)target_speed == 0 && (int)speedF == 0) {
        speedF = 0.0f;
        if (mbTalkReq) {
            if (chk_talk()) {
                setStt(2);
                mLookMode = 1;
                mbHeadOnly = false;
                m_jnt.setTrn();
            }
            return TRUE;
        }
        if (mbPathEnd) {
            setStt(5);
            mLookMode = 0;
            return TRUE;
        }
        setStt(1);
        mLookMode = 1;
        mbHeadOnly = false;
        m_jnt.setTrn();
        return TRUE;
    }

    mOrder = 2;
    mLookMode = 0;
    return TRUE;
}

/* 0000347C-00003594       .text turn_1__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::turn_1() {
    if (chk_brkTsubo()) {
        return TRUE;
    }

    if (mbTalkReq) {
        if (chk_talk()) {
            setStt(2);
        }
        return TRUE;
    }

    mOrder = 2;
    cXyz point = mPath.getPoint(mPath.getIdx());
    int target = cLib_targetAngleY(&current.pos, &point);
    cLib_chaseAngleS(&current.angle.y, target, l_HIO.children[mHioType].hio_prm.mWalkTurnMaxStep);
    if (current.angle.y == target) {
        setStt(3);
        mLookMode = 0;
        mPath.turnDir();
        mbPathEnd = 0;
        return TRUE;
    }
    return TRUE;
}

/* 00003594-000036F0       .text talk_1__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::talk_1() {
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
        case 0x899:
        case 0x8AA:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0180);
            break;
        case 0x89B:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0140);
            break;
        case 0x89D:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0120);
            break;
        case 0x89F:
            dComIfGp_setItemRupeeCount(-10);
            mbPaid = true;
            break;
        case 0x8A4:
        case 0x8A5:
        case 0x8A6:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3A40);
            break;
        }
        mItemNo = 0xFF;
        mbTalkReq = false;
        setStt(mPrevStt);
        mLookTimer = cLib_getRndValue(10, 20);
        endEvent();
        break;
    }
    return res;
}

/* 000036F0-00003848       .text wait_action1__11daNpc_Yw1_cFPv */
BOOL daNpc_Yw1_c::wait_action1(void*) {
    switch (mActionState) {
    case 0:
        setStt(3);
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
        case 4:
            mbSetEyePos = wait_2();
            break;
        case 3:
            mbSetEyePos = walk_1();
            break;
        case 5:
            mbSetEyePos = turn_1();
            break;
        case 2:
            mbSetEyePos = talk_1();
            break;
        }
        lookBack();
        break;
    default:
        break;
    }

    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001) && mType == 0) {
        int not_found;
        fopAc_ac_c* tsubo_p = searchByID(mTsuboID, &not_found);
        if (not_found == 0 && tsubo_p) {
            fopAcM_delete(tsubo_p);
        }
        fopAcM_delete(this);
    }
    return TRUE;
}

/* 00003848-00003904       .text wait_action2__11daNpc_Yw1_cFPv */
BOOL daNpc_Yw1_c::wait_action2(void*) {
    switch (mActionState) {
    case 0:
        setStt(6);
        mActionState++;
        break;
    case 9:
        break;
    case 1:
    case 2:
    case 3:
        mbAttention = chkAttention();
        switch (mStt) {
        case 6:
            mbSetEyePos = wait_3();
            break;
        case 2:
            mbSetEyePos = talk_1();
            break;
        }
        lookBack();
        break;
    default:
        break;
    }
    return TRUE;
}

/* 00003904-00003A50       .text demo__11daNpc_Yw1_cFv */
bool daNpc_Yw1_c::demo() {
    if (demoActorID == 0) {
        if (mbDemo) {
            mbDemo = false;
        }
    } else {
        if (!mbDemo) {
            mbDemo = true;
            m778 = false;
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

        J3DAnmTexPattern* demo_btp_p = demo_actor_p->getP_BtpData("Yw");
        if (demo_btp_p) {
            mBtpAnm.init(mpHeadModel->getModelData(), demo_btp_p, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            mBtpNum = BTPNUM_NULL_e;
            mBtpFrame = 0;
        }

        dDemo_setDemoData(this, 106, mpMorf, "Yw", 0, NULL, 0, 0);
    }

    return mbDemo;
}

/* 00003A50-00003B4C       .text shadowDraw__11daNpc_Yw1_cFv */
void daNpc_Yw1_c::shadowDraw() {
    int not_found;
    fopAc_ac_c* tsubo_p = searchByID(mTsuboID, &not_found);
    cXyz pos(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(mShadowID, 1, mpMorf->getModel(), &pos, 800.0f, 40.0f, current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr);

    if (mShadowID != 0) {
        if (not_found == 0 && tsubo_p && tsubo_p->model) {
            dComIfGd_addRealShadow(mShadowID, tsubo_p->model);
        }
        dComIfGd_addRealShadow(mShadowID, mpHeadModel);
    }
}

static void dummy() {
    const GXColor dummy1 = {0xFF, 0x00, 0x00, 0x80};
    const GXColor dummy2 = {0x00, 0x00, 0xFF, 0x80};
    const GXColor dummy3 = {0xFF, 0xFF, 0x00, 0x80};
}

/* 00003B4C-00003C84       .text _draw__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::_draw() {
    J3DModel* head_model_p = mpHeadModel;
    J3DModelData* head_model_info_p = head_model_p->getModelData();
    J3DModel* morf_model_p = mpMorf->getModel();

    if (mbHide || m779 != 0) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model_p, &tevStr);
    g_env_light.setLightTevColorType(head_model_p, &tevStr);

    mpMorf->entryDL();

    mBtpAnm.entry(head_model_info_p, mBtpFrame);
    mDoExt_modelEntryDL(head_model_p);
    mBtpAnm.remove(head_model_info_p);

    shadowDraw();

    dSnap_RegistFig(DSNAP_TYPE_UNK4B, this, 1.0f, 1.0f, 1.0f);

    // Does nothing
    if (l_HIO.children[mHioType].hio_prm.m18) {
        cXyz dummy = current.pos;
        dummy.y = eyePos.y;
    }

    return TRUE;
}

/* 00003C84-00003EDC       .text _execute__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::_execute() {
    if (!mbInitDone) {
        mHomePos = current.pos;
        mHomeAngle = current.angle;
        mbInitDone = true;
    }

    m_jnt.setParam(
        l_HIO.children[mHioType].hio_prm.mMaxBackBoneX,
        l_HIO.children[mHioType].hio_prm.mMaxBackBoneY,
        l_HIO.children[mHioType].hio_prm.mMinBackBoneX,
        l_HIO.children[mHioType].hio_prm.mMinBackBoneY,
        l_HIO.children[mHioType].hio_prm.mMaxHeadX,
        l_HIO.children[mHioType].hio_prm.mMaxHeadY,
        l_HIO.children[mHioType].hio_prm.mMinHeadX,
        l_HIO.children[mHioType].hio_prm.mMinHeadY,
        l_HIO.children[mHioType].hio_prm.mMaxTurnStep
    );

    if (mbHide && demoActorID == 0) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)) {
            if (mType == 1) {
                fopAcM_SetStatusMap(this, 8);
            }
            mbHide = false;
        } else {
            return TRUE;
        }
    }

    partner_search();
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

        fopAcM_posMoveF(this, mStts.GetCCMoveP());
        play_animation();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }

    eventOrder();
    mAngle = current.angle;
    if (!m778) {
        shape_angle = current.angle;
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);
    setCollision(30.0f, 150.0f);

    return TRUE;
}

/* 00003EDC-00003F38       .text _delete__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::_delete() {
    dComIfG_resDelete(&mPhs, "Yw");
    if (heap && mpMorf) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

daNpc_Yw1_c::daNpc_Yw1_c() {}

/* 00003F38-0000417C       .text _create__11daNpc_Yw1_cFv */
cPhs_State daNpc_Yw1_c::_create() {
    static int a_siz_tbl[] = {
        0,
    };

    fopAcM_ct(this, daNpc_Yw1_c);

    cPhs_State state = dComIfG_resLoad(&mPhs, "Yw");
    if (state != cPhs_COMPLEATE_e) {
        return state;
    }

    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[mHioType])) {
        return cPhs_ERROR_e;
    }

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -40.0f, -20.0f, -40.0f, 40.0f, 210.0f, 40.0f);

    if (!createInit()) {
        return cPhs_ERROR_e;
    }

    return state;
}

/* 00004448-0000469C       .text bodyCreateHeap__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Yw", dRes_ID_YW_BDL_YW_e);
    JUT_ASSERT(0x96F, a_mdl_dat != NULL);

    mpMorf = new mDoExt_McaMorf(a_mdl_dat, NULL, NULL, NULL, J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11020022);

    if (!mpMorf) {
        return FALSE;
    } else if (!mpMorf->getModel()) {
        mpMorf = NULL;
        return FALSE;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x97D, m_hed_jnt_num >= 0);

    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x97F, m_bbone_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->setUserArea((uintptr_t)this);

    return TRUE;
}

/* 0000469C-00004930       .text headCreateHeap__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::headCreateHeap() {
    static int a_hed_bdl_resID_tbl[] = {
        dRes_ID_YW_BDL_YWHEAD01_e,
    };
    static s8 a_tex_pttrn_num_tbl[] = {
        0,
    };

    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Yw", a_hed_bdl_resID_tbl[mHioType]);
    JUT_ASSERT(0x99C, a_mdl_dat != NULL);

    mpHeadModel = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x15020022);
    if (!mpHeadModel) {
        return FALSE;
    }

    if (!init_texPttrnAnm(a_tex_pttrn_num_tbl[mHioType], false)) {
        return FALSE;
    }

    m_hair1 = a_mdl_dat->getJointName()->getIndex("hair1");
    JUT_ASSERT(0x9AD, m_hair1 >= 0);

    m_hair2 = a_mdl_dat->getJointName()->getIndex("hair2");
    JUT_ASSERT(0x9AF, m_hair2 >= 0);

    m_hair3 = a_mdl_dat->getJointName()->getIndex("hair3");
    JUT_ASSERT(0x9B1, m_hair3 >= 0);

    mpHeadModel->getModelData()->getJointNodePointer(m_hair1)->setCallBack(nodeCB_Hair);
    mpHeadModel->getModelData()->getJointNodePointer(m_hair2)->setCallBack(nodeCB_Hair);
    mpHeadModel->getModelData()->getJointNodePointer(m_hair3)->setCallBack(nodeCB_Hair);
    mpHeadModel->setUserArea((uintptr_t)this);

    return TRUE;
}

/* 00004930-000049D0       .text CreateHeap__11daNpc_Yw1_cFv */
BOOL daNpc_Yw1_c::CreateHeap() {
    if (!bodyCreateHeap()) {
        return FALSE;
    }

    if (!headCreateHeap()) {
        mpMorf = NULL;
        return FALSE;
    }

    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);

    return TRUE;
}

/* 000049D0-000049F0       .text daNpc_Yw1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Yw1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Yw1_c*)i_this)->_create();
}

/* 000049F0-00004A10       .text daNpc_Yw1_Delete__FP11daNpc_Yw1_c */
static BOOL daNpc_Yw1_Delete(daNpc_Yw1_c* i_this) {
    return ((daNpc_Yw1_c*)i_this)->_delete();
}

/* 00004A10-00004A30       .text daNpc_Yw1_Execute__FP11daNpc_Yw1_c */
static BOOL daNpc_Yw1_Execute(daNpc_Yw1_c* i_this) {
    return ((daNpc_Yw1_c*)i_this)->_execute();
}

/* 00004A30-00004A50       .text daNpc_Yw1_Draw__FP11daNpc_Yw1_c */
static BOOL daNpc_Yw1_Draw(daNpc_Yw1_c* i_this) {
    return ((daNpc_Yw1_c*)i_this)->_draw();
}

/* 00004A50-00004A58       .text daNpc_Yw1_IsDelete__FP11daNpc_Yw1_c */
static BOOL daNpc_Yw1_IsDelete(daNpc_Yw1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Yw1_Method = {
    (process_method_func)daNpc_Yw1_Create,
    (process_method_func)daNpc_Yw1_Delete,
    (process_method_func)daNpc_Yw1_Execute,
    (process_method_func)daNpc_Yw1_IsDelete,
    (process_method_func)daNpc_Yw1_Draw,
};

actor_process_profile_definition g_profile_NPC_YW1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_YW1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Yw1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_YW1_e,
    /* Actor SubMtd */ &l_daNpc_Yw1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
