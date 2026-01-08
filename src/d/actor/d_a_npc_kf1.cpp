/**
 * d_a_npc_kf1.cpp
 * NPC - Mila's Father (rich)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kf1.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "SSystem/SComponent/c_counter.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_sxyz.h"
#include "d/d_com_inf_game.h"
#include "d/d_item_data.h"
#include "d/d_npc.h"
#include "d/d_procname.h"
#include "d/d_snap.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/mtx/mtxvec.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/actor/d_a_player.h"
#include "f_op/f_op_actor_mng.h"

#include "d/actor/d_a_tsubo.h"
#include "d/d_priority.h"
#include "f_pc/f_pc_base.h"
#include "f_pc/f_pc_manager.h"
#include "m_Do/m_Do_audio.h"
#include <string.h>

static daNpc_Kf1_HIO_c l_HIO;
static u8 a_prm_tbl[0x30] = {0x20, 0x00, 0x07, 0xd0, 0xfc, 0x18, 0xf8, 0x30, 0x00, 0x00, 0x13, 0x88, 0xf0, 0x60, 0xec, 0x78,
                                 0x05, 0xdc, 0x04, 0xb0, 0x43, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0a, 0x04, 0x00, 0x00, 0x00,
                                 0x3f, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x3e, 0x4c, 0xcc, 0xcd, 0x41, 0x00, 0x00, 0x00};

/* 000000EC-00000150       .text __ct__15daNpc_Kf1_HIO_cFv */
daNpc_Kf1_HIO_c::daNpc_Kf1_HIO_c() {
        memcpy((char*)this + 0xC, a_prm_tbl, 0x30);
    b = a = -1;
}

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* node, int idx) {
    /* Nonmatching */
    if (idx == 0) {
        void* userData = (void*)j3dSys.getModel()->getUserArea();
        if (userData != NULL) {
           ((daNpc_Kf1_c*)userData)->_nodeCB_Head(node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000001E4-000002D8       .text _nodeCB_Head__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Head(J3DNode* node, J3DModel* model) {
    static cXyz a_eye_pos_off(30.0f, 30.0f, 0.0f);

    u16 joint_number = static_cast<J3DJoint*>(node)->getJntNo();
    MTXCopy(model->getAnmMtx(joint_number), mDoMtx_stack_c::now);
    mDoMtx_stack_c::multVecZero(&this->mMtx);
    mDoMtx_stack_c::multVec(&a_eye_pos_off, &this->head_anm_vec);
    MTXCopy(mDoMtx_stack_c::now, j3dSys.mCurrentMtx);
    model->setAnmMtx(joint_number, mDoMtx_stack_c::now);
    /* Nonmatching */
}

/* 00000314-00000360       .text nodeCB_Neck__FP7J3DNodei */
static BOOL nodeCB_Neck(J3DNode* node, int idx) {
     if (idx == 0) {
        void* userData = (void*)j3dSys.getModel()->getUserArea();
        if (userData != NULL) {
           ((daNpc_Kf1_c*)userData)->_nodeCB_Neck(node, j3dSys.getModel());
        }
    }
    return TRUE;
   /* Nonmatching */
}

/* 00000360-00000400       .text _nodeCB_Neck__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Neck(J3DNode* node, J3DModel* model) {
    u16 joint_number = static_cast<J3DJoint*>(node)->getJntNo();
    MTXCopy(model->getAnmMtx(joint_number), mDoMtx_stack_c::now);
    mDoMtx_stack_c::XrotM(this->m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-this->m_jnt.getHead_x());

    MTXCopy(mDoMtx_stack_c::now, j3dSys.mCurrentMtx);
    model->setAnmMtx(joint_number, mDoMtx_stack_c::now);
}

/* 00000400-0000044C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* node, int idx) {
    /* Nonmatching */
    if (idx == 0) {
        void* userData = (void*)j3dSys.getModel()->getUserArea();
        if (userData != NULL) {
           ((daNpc_Kf1_c*)userData)->_nodeCB_BackBone(node, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000044C-000004EC       .text _nodeCB_BackBone__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_BackBone(J3DNode* node, J3DModel* model) {
    u16 joint_number = static_cast<J3DJoint*>(node)->getJntNo();
    MTXCopy(model->getAnmMtx(joint_number), mDoMtx_stack_c::now);
    mDoMtx_stack_c::XrotM(this->m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-this->m_jnt.getBackbone_x());

    MTXCopy(mDoMtx_stack_c::now, j3dSys.mCurrentMtx);
    model->setAnmMtx(joint_number, mDoMtx_stack_c::now);
}

/* 000004EC-0000050C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Kf1_c*>(i_this)->CreateHeap();
    /* Nonmatching */
}

#define L_CHECK_SZ 20
s32 l_check_wrk;
fopAc_ac_c* l_check_inf[L_CHECK_SZ];

/* 0000050C-0000059C       .text searchActor_Tsubo__FPvPv */
void* searchActor_Tsubo(void* i_act, void* arg2) {
    // TODO enums
    fopAc_ac_c *act = static_cast<fopAc_ac_c*>(i_act);
    if (l_check_wrk < L_CHECK_SZ && fopAc_IsActor(i_act) && act->base.base.mProcName == PROC_TSUBO && daObj::PrmAbstract<daTsubo::Act_c::Prm_e>(act, daTsubo::Act_c::PRM_TYPE_W, daTsubo::Act_c::PRM_TYPE_S) == 0xe) {
        l_check_inf[l_check_wrk] = act;
        l_check_wrk++;
    }
    return FALSE;
}

char* l_evn_tbl[] = {
    "angry", "rupee_age", "bensyou"
};

/* 0000059C-0000061C       .text init_KF1_0__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::init_KF1_0() {
    if (!dComIfGs_isEventBit(0x2d01)) {
        this->set_action(&daNpc_Kf1_c::wait_action1, NULL);
        return TRUE;
    }
    return FALSE;
}

dCcD_SrcCyl dNpc_cyl_src;

/* 0000061C-0000083C       .text createInit__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::createInit() {
    /* Nonmatching */
    for (int i = 0; i < 3; ++i) {
        field_0x780[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i], 0xFF);
    }
    mEventCut.setActorInfo2("Kf1", this);
    this->field_0x79F = base.base.mParameters >> 8;
    u8 weight = 0xFF;
    u8 params = base.base.mParameters >> 0x10;
    BOOL status = FALSE;
    if (params != 0xff) {
        pathRun.setInf(params, current.roomNo, true);
        if (pathRun.mPath != NULL) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            weight = 0xD9;
            set_pthPoint(0);
        } else {
            return FALSE;
        }
    }
    if (this->pathRun.mPath == NULL) {
        return FALSE;
    }
    this->attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    this->attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xab;
    this->attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xab;
    this->gravity = -4.5f;
    this->mAnmId = 10;

    BOOL init;
    BOOL cond = this->field_0x7FC == FALSE;
    // BOOL init = (this->field_0x7FC == 0) ? this->init_KF1_0() : FALSE;
    if (cond) {
        init = FALSE;
    } else {
        init = this->init_KF1_0();
    }
    if (init) {
        this->mAngle = current.angle;
        shape_angle = mAngle;
        this->mStts.Init(weight, 0xff, this);
        this->mCyl.SetStts(&mStts);
        this->mCyl.Set(dNpc_cyl_src);
        this->mObjAcch.CrrPos(*dComIfG_Bgsp());
        this->play_animation();
        this->tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
        this->tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
        this->mpMorf->setMorf(0.0f);
        this->setMtx(true);

        return true;
    } else {
        return false;
    }

    return status;
}

/* 0000083C-000008E4       .text play_animation__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::play_animation() {

    int mtrlSndId = 0;
    play_btp_anm();
    if (mObjAcch.ChkGroundHit()) {
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    field_0x79C = mpMorf->play(&eyePos, mtrlSndId, reverb);
    if (mpMorf->getFrame() < mAnimTimer) {
        field_0x79C = 1;
    }
    mAnimTimer = mpMorf->getFrame();
}

/* 000008E4-00000A20       .text setMtx__11daNpc_Kf1_cFb */
void daNpc_Kf1_c::setMtx(bool arg) {
    this->mpMorf->getModel()->setBaseScale(this->scale);
    MTXTrans(mDoMtx_stack_c::now, current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_ZXYrotM(mDoMtx_stack_c::now, mAngle.x, mAngle.y, mAngle.z);
    this->mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
    this->mpMorf->calc();
    if (mModel != NULL) {
        // mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        MTXCopy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num), mDoMtx_stack_c::now);
        mDoMtx_stack_c::transM(33.87f, 3.26f, 0.0f);
        mDoMtx_XYZrotM(mDoMtx_stack_c::now, -0x4000, -0x4000, 0);
        mModel->setBaseTRMtx(mDoMtx_stack_c::now);
        mModel->calc();
    }
    setAttention(arg);
}

/* 00000A20-00000A34       .text bckResID__11daNpc_Kf1_cFi */
s32 daNpc_Kf1_c::bckResID(int id) {
    static const s32 a_resID_tbl[10] = {
        0xA, 0xC, 0x6, 0x7, 0x8, 0x9, 0x5, 0x3, 0x4, 0xB
    };
    return a_resID_tbl[id];
    /* Nonmatching */
}


/* 00000A34-00000A48       .text btpResID__11daNpc_Kf1_cFi */
s32 daNpc_Kf1_c::btpResID(int idx) {
    static const s32 a_resID_tbl[2] = {
        0x02, 0x0d
    };
    /* Nonmatching */
    return a_resID_tbl[idx];
}

/* 00000A48-00000B4C       .text setBtp__11daNpc_Kf1_cFScb */
bool daNpc_Kf1_c::setBtp(signed char btpId, bool i_modify) {
    /* Nonmatching */
    J3DModel* model = mpMorf->getModel();
    if (btpId < 0) {
        return FALSE;
    }
    J3DAnmTexPattern *a_btp = (J3DAnmTexPattern*) dComIfG_getObjectIDRes(field_0x6D4, (int)btpResID(btpId));
    JUT_ASSERT(0x20a, a_btp != NULL);

    field_0x7F5 = btpId;
    field_0x6F0 = 0;
    field_0x6F2 = 0;
    return 0 != mBtpAnm.init(model->getModelData(), a_btp, TRUE, 0, 1.0f, 0, -1, i_modify, FALSE);
}

/* 00000B4C-00000B6C       .text init_texPttrnAnm__11daNpc_Kf1_cFScb */
bool daNpc_Kf1_c::init_texPttrnAnm(signed char btpId, bool i_modify) {
    setBtp(btpId, i_modify);
}

/* 00000B6C-00000C08       .text play_btp_anm__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::play_btp_anm() {
    u8 dur = mBtpAnm.getBtpAnm()->getFrameMax();
    if (field_0x7F5 != 0 || cLib_calcTimer(&field_0x6F2) == 0) {
        field_0x6F0++;
        if (field_0x6F0 >= dur) {
            if (field_0x7F5 != 0) {
                field_0x6F0 = dur;
            }
            else {
                field_0x6F2 = cLib_getRndValue(60, 90);
                field_0x6F0 = 0;
            }
        }
    }
}

/* 00000C08-00000CA4       .text setAnm_anm__11daNpc_Kf1_cFPQ211daNpc_Kf1_c9anm_prm_c */
void daNpc_Kf1_c::setAnm_anm(daNpc_Kf1_c::anm_prm_c* i_anmPrm) {
    if (i_anmPrm->anmId < 0 || mAnmId == i_anmPrm->anmId) {
        return;
    }
    dNpc_setAnmIDRes(mpMorf, i_anmPrm->loopMode, i_anmPrm->morf, i_anmPrm->animSpeed,
                     bckResID(i_anmPrm->anmId), -1, field_0x6D4);
    mAnmId = i_anmPrm->anmId;
    field_0x79C = 0;
    field_0x79D = 0;
    mAnimTimer = 0.0f;
    /* Nonmatching */
}
static u32 foo = 9;

/* 00000CA4-00000D14       .text setAnm_NUM__11daNpc_Kf1_cFii */
void daNpc_Kf1_c::setAnm_NUM(int i_1, int i_2) {
    static anm_prm_c a_anm_prm_tbl[] = {
        {0, 0, 15.0f, 1.0f, 2},
        {1, 1, 8.0f, 1.0f, 2},
        {2, 0, 8.0f, 1.0f, 2},
        {3, 0, 8.0f, 1.0f, 2},
        {4, 0, 8.0f, 1.0f, 2},
        {5, 0, 8.0f, 1.0f, 2},
        {6, 0, 8.0f, 1.0f, 2},
        {7, 0, 8.0f, 1.0f, 0},
        {8, 0, 8.0f, 1.0f, 0},
        // TODO address 0x1 has value 0x01
        {9, 1, 8.0f, 1.0f, 2},
    };
    if (i_2 != 0) {
        init_texPttrnAnm(a_anm_prm_tbl[i_1].flag, true);
    }
    setAnm_anm(&a_anm_prm_tbl[i_1]);
    /* Nonmatching */
}

/* 00000D14-00000D80       .text setAnm__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[] = {
        {0xff, 0xff, 0.0f, 0.0f, 0xffffffff},
        {0xff, 0xff, 0.0f, 0.0f, 0xffffffff},
        {0xff, 0xff, 0.0f, 0.0f, 0xffffffff},

    {1, 1, 8.0f, 1.0f, 2}};
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7F8].flag, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7F8]);
    /* Nonmatching */
}

/* 00000D80-00000D84       .text chngAnmTag__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::chngAnmTag() {
}

/* 00000D84-00000D88       .text ctrlAnmTag__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::ctrlAnmTag() {
}

/* 00000D88-00000DEC       .text chngAnmAtr__11daNpc_Kf1_cFUc */
void daNpc_Kf1_c::chngAnmAtr(unsigned char c) {
    switch (mCurrMsgNo) {
        case 0x1c2e:
            dComIfGp_event_offHindFlag(0x80);
    }
    if (c == field_0x7F5 || c > 0xb) {
        return;
    }
    field_0x7F5 = c;
    setAnm_ATR();
}

/* 00000DEC-00000E60       .text ctrlAnmAtr__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::ctrlAnmAtr() {
    switch (field_0x7F5) {
    case 7:
    case 9:
        if (field_0x79C != 0) {
            setAnm_NUM(0, 1);
            field_0x7F5 = 0;
        }
    }
    /* Nonmatching */
}

/* 00000E60-00000EC4       .text setAnm_ATR__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::setAnm_ATR() {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[] = {
    {0,0,15.0f, 1.0f, 2},
    {1, 1, 8.0f, 1.0f, 2},
    {2, 0, 8.0f, 1.0f, 2},
    {3, 0, 8.0f, 1.0f, 2},
    {4, 0, 8.0f, 1.0f, 2},
    {5, 0, 8.0f, 1.0f, 2},
    {6, 0, 8.0f, 1.0f, 2},
    {7, 0, 8.0f, 1.0f, 0},
    {8, 0, 8.0f, 1.0f, 0},
    {3, 0, 8.0f, 1.0f, 2},
    {9, 1, 8.0f, 1.0f, 2},
};
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7F3].flag, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7F3]);
}

/* 00000EC4-00000F80       .text anmAtr__11daNpc_Kf1_cFUs */
void daNpc_Kf1_c::anmAtr(unsigned short param) {
    switch (param) {
        case 0x6: {
            if (field_0x7FE == 0) {
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                field_0x7FE++;
            }
            u8 prev = dComIfGp_getMesgAnimeTagInfo();
            if (prev != 0xff && prev != field_0x7F5) {
                dComIfGp_clearMesgAnimeTagInfo();
                field_0x7F5 = prev;
                chngAnmTag();
            }
            break;
        }
        case 0xe:
            field_0x7FE = 0;
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000F80-000010F4       .text next_msgStatus__11daNpc_Kf1_cFPUl */
u16 daNpc_Kf1_c::next_msgStatus(unsigned long* param) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    /* Nonmatching */
    switch (*param) {
    case 0x1c23:
        switch (mpCurrMsg->mSelectNum) {
            case 0:
                *param = 0x1c24;
                break;
            case 1:
                *param = 0x1c25;
                break;
        }
        break;
        // *param = mpCurrMsg->mSelectNum == 1 ? 0x1c25 : 0x1c24;
        // break;
    case 0x1c28:
        switch (mpCurrMsg->mSelectNum) {
        case 0:
            *param = 0x1c2A;
            break;
        case 1:
            *param = 0x1c29;
            break;
        }
        break;
    case 0x1c24:
        dComIfGs_onEventBit(0xb02);
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x1c2b:
        field_0x7A0 = 1;
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x1c21:
        *param = 0x1c22;
        break;
    case 0x1c22:
        *param = 0x1c34;
        break;
    case 0x1c34:
        *param = 0x1c23;
        break;
    case 0x1c27:
        *param = 0x1c28;
        break;
    case 0x1c2a:
        *param = 0x1c2b;
        break;
    case 0x1c30:
        *param = 0x1c31;
        break;
    case 0x1c2d:
        *param = 0x1c2e;
        break;
    case 0x1c33: {
        int temp = field_0x7F0 >= field_0x7EE * 10 ? -1 : 0;
        *param = 0x1C30 + temp;
        break;
    }
    case 0x1c36:
        *param = 0x1c37;
        break;

    default:
        ret = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return ret;
}

/* 000010F4-000011DC       .text getMsg_KF1_0__11daNpc_Kf1_cFv */
u32 daNpc_Kf1_c::getMsg_KF1_0() {
    if (field_0x7A1 != 0) {
        return 0x1c38;
    }
    if (dComIfGs_isEventBit(0xa02) && !dComIfGs_isSymbol(0)) {
        return 0x1c3b;
    }
    if (dComIfGs_isEventBit(0xb02)){
        u8 eventReg = dComIfGs_getEventReg(0xbcff);
        if (dKy_daynight_check() == 1 || !dComIfGs_isEventBit(0x2780) || (eventReg & 1) != 0) {
            return 0x1c26;
        }
        return 0x1c27;
    }
    return 0x1c21;
}

/* 000011DC-00001218       .text getMsg__11daNpc_Kf1_cFv */
u32 daNpc_Kf1_c::getMsg() {
    u32 ret = 0;

    switch (field_0x7FC) {
        case 0:
            ret = getMsg_KF1_0();
            break;
    }
    return ret;
}

/* 00001218-000012A4       .text eventOrder__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::eventOrder() {
    if (field_0x7F7 == 1 || field_0x7F7 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (field_0x7F7 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (field_0x7F7 >= 3) {
        field_0x780[3] = field_0x7F7 - 3;
        fopAcM_orderOtherEventId(this, field_0x780[field_0x780[3]]);
    }
}

/* 000012A4-00001380       .text checkOrder__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::checkOrder() {
    /* Nonmatching */
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(field_0x780[field_0x780[3]]) && field_0x7F7 >= 3) {
            // TODO missing blt statement in asm around here
            switch (field_0x780[3]) {
            default:
                break;
            case 0:
                static_cast<daPy_py_c*>((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMoveAngle(dComIfGp_getPlayer(0)->current.angle.y);
                break;
            }
            field_0x7F7 = 0;
            field_0x7F3 = 0xff;
            field_0x7F4 = 0xff;
        }
    } else if (eventInfo.getCommand() == dEvtCmd_INTALK_e && (field_0x7F7 == 1 || field_0x7F7 == 2)) {
        field_0x7F7 = 0;
        field_0x7AC = 1;
        // switch (field_0x7F7) {
        // case 1:
        // case 2:
        //     field_0x7F7 = 0;
        //     field_0x7AC = 1;
        // }
    }
}

/* 00001380-00001418       .text chk_talk__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::chk_talk() {
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            field_0x79E = dComIfGp_event_getPreItemNo();
            return TRUE;
        } else {
            return FALSE;
        }
    } else {
        field_0x79E = 0xff;
        return TRUE;
    }
}

/* 00001418-0000146C       .text searchByID__11daNpc_Kf1_cFUiPi */
fopAc_ac_c* daNpc_Kf1_c::searchByID(fpc_ProcID i_procId, int* o_par1) {
    fopAc_ac_c* ret = NULL;
    *o_par1 = 0;
    BOOL found = fopAcM_SearchByID(i_procId, &ret);
    if (found == FALSE) {
        *o_par1 = 1;
    }
    return ret;
}

/* 0000146C-0000156C       .text srch_Tsubo__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::srch_Tsubo() {
    /* Nonmatching */

    bool ret = false;
    int i = 0;
    int j = 0;
    switch (field_0x7FD) {
    default:
        return false;
        break;
    case 1:
        field_0x700 = -1;
        l_check_wrk = 0;
        for (i = 0, j = L_CHECK_SZ; j != 0; ++i, --j) {
            l_check_inf[i] = 0;
        }
        fpcM_Search(searchActor_Tsubo, this);
        if (l_check_wrk >= 8) {
            field_0x7EC = 0;
            for (i = 0, j = 8; j != 0; ++i, --j) {
                field_0x7BC[i] = fopAcM_GetID(l_check_inf[i]);
                field_0x7EC++;
            }
            ret = true;
            field_0x7FD++;
        }
        break;
    }
    return ret;
}

/* 0000156C-000017F4       .text create_rupee__11daNpc_Kf1_cF4cXyzi */
void daNpc_Kf1_c::create_rupee(cXyz vec, int count) {
    /* Nonmatching */
    cXyz scale(0.2f, 0.2f, 0.2f);
    csXyz shape_angle(0, 0, 0);

    int i;
    int cnt = g_Counter.mCounter0;
    int idx = 0;
    for (i = 0; i < count; ++i) {
        f32 nums[] = {-30.0f, 0.0f, 30.0f};

        // mysterious constant 0x433609F5 (182.0389f) here.
        // a similar constant 182.0445f appears in Degree_To_Sangle but this is what ghidra says
        s16 rand_angle = nums[cnt % 3] + (cM_rndF(30.0f) - 15.0f);
        rand_angle = 182.0389f * rand_angle;
        shape_angle.y = this->current.angle.y + rand_angle;
        s8 roomNo = current.roomNo;
        f32 yvelocity = cM_rndFX(4.0f) + 31.0f;
        f32 speed = cM_rndFX(2.0f) +  13.0f;
        f32 gravity = -2.0;
        // cXyz pos(speed, yvelocity, gravity);
        fopAc_ac_c* a_actor_p = fopAcM_createItemForKP2(&vec, dItem_RED_RUPEE_e, roomNo, NULL, NULL, speed, yvelocity, gravity, 1);

        JUT_ASSERT(0x412, a_actor_p != NULL);

        if (a_actor_p != NULL) {
            // TODO enum
            fopAcM_OnStatus(a_actor_p, 0x4000);
            fopAcM_OffStatus(a_actor_p, 0x80);
            a_actor_p->scale = scale;
            a_actor_p->shape_angle = shape_angle;
            a_actor_p->current.angle = a_actor_p->shape_angle;
            // fpc_ProcID id = 
            // if (a_actor_p != NULL) {
            //     id = fopAcM_GetID(a_actor_p);
            // } else {
            //     id = -1;
            // }
            this->field_0x7B0[i] = fopAcM_GetID(a_actor_p);
        }

        cnt++;
    }
}

/* 000017F4-00001A0C       .text ready_kutaniCamera__11daNpc_Kf1_cFii */
void daNpc_Kf1_c::ready_kutaniCamera(int arg1, int arg2) {
    int i_flg;
    fopAc_ac_c* a_actor = searchByID(this->field_0x7BC[11], &i_flg);
    if (a_actor != NULL && i_flg == 0) {
        fopAcM_delete(a_actor);
    }
    if (arg2 != 0) {
        cXyz scale(0.1, 0.1, 0.1);
        csXyz angle(0, 0, 0);

        fopAc_ac_c* a_actor = this->searchByID(this->field_0x7BC[arg1 + 8], &i_flg);
        // BOOL i_flg = a_actor != NULL && id == 0;
        JUT_ASSERT(0x432, NULL != a_actor && 0 == i_flg);

        dComIfGp_event_setItemPartner(a_actor);

        // cXyz pos(0,0,-4.0);
        // csXyz angle = this->current.angle;
        angle.y = this->current.angle.y;
        cXyz pos = this->current.pos;
        pos.y = pos.y + 180.0f;

        a_actor = fopAcM_createItemForKP2(&pos, dItem_RED_RUPEE_e, this->current.roomNo, NULL, NULL, 0.0, 0.0, -4.0, 1);
        JUT_ASSERT(0x43e, NULL != a_actor);

        fopAcM_OnStatus(a_actor, 0x4000);
        fopAcM_OffStatus(a_actor, 0x80);

        a_actor->scale = scale;
        a_actor->current.angle = angle;

        this->field_0x7BC[11] = fopAcM_GetID(a_actor);
    }
    /* Nonmatching */
}

/* 00001A0C-00001BD0       .text lookBack__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::lookBack() {
    this->field_0x776 = this->m_jnt.getHead_y();
    this->field_0x778 = this->m_jnt.getBackbone_y();
    this->field_0x774 = this->current.angle.y;

    cXyz zeros;
    cXyz pos;

    pos = this->current.pos;
    pos.y = this->eyePos.y;
    zeros.x = 0.0;
    zeros.y = 0.0;
    zeros.z = 0.0;

    cXyz* vec_ptr = NULL;
    int id;
    s16 targetY = this->current.angle.y;
    fopAc_ac_c* a_actor;
    bool b = this->field_0x7AD;
    switch (this->field_0x7FA) {
    case 1:
        this->field_0x73C = dNpc_playerEyePos(20.0);
        zeros = this->field_0x73C;
        vec_ptr = &zeros;
        break;
    case 2:
        zeros = this->field_0x73C;
        vec_ptr = &zeros;
        break;
    case 3:
        targetY = this->field_0x79A;
        break;
    case 4:
        a_actor = this->searchByID(this->field_0x704, &id);
        if (a_actor != NULL && id == 0) {
            this->field_0x73C = a_actor->current.pos;
            this->field_0x73C.y = a_actor->eyePos.y;
            zeros = this->field_0x73C;
            vec_ptr = &zeros;
        };
        break;
    }

    this->m_jnt.lookAtTarget_2(&this->current.angle.y, vec_ptr, pos, targetY, l_HIO.field_0x1e, b);
}

/* 00001BD0-00001C50       .text chkAttention__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::chkAttention() {
    if (dComIfGp_getAttention().LockonTruth()) {
        return this == dComIfGp_getAttention().LockonTarget(0);
    }
    return this == dComIfGp_getAttention().ActionTarget(0);
}

/* 00001C50-00001CA8       .text setAttention__11daNpc_Kf1_cFb */
void daNpc_Kf1_c::setAttention(bool arg) {
    f32 zpos = this->current.pos.z;
    f32 ypos = this->current.pos.y + l_HIO.yoffset;
    this->attention_info.position.x = this->current.pos.x;
    this->attention_info.position.y = ypos;
    this->attention_info.position.z = zpos;

    if (this->field_0x77C == 0 && !arg) {
        return;
    }
    zpos = this->head_anm_vec.z;
    ypos = this->head_anm_vec.y;

    this->eyePos.x = this->head_anm_vec.x;
    this->eyePos.y = ypos;
    this->eyePos.z = zpos;

    /* Nonmatching */ // (FIXME regalloc crap)
}

/* 00001CA8-00001D30       .text decideType__11daNpc_Kf1_cFi */
bool daNpc_Kf1_c::decideType(int arg) {
    bool ret;
    if (this->field_0x7FB > 0) {
        return TRUE;
    }
    this->field_0x7FB = 1;
    this->field_0x7FC = 0;
    strcpy(this->field_0x6D4, "Kf");
    ret = FALSE;
    if (this->field_0x7FB != -1 && this->field_0x7FC != -1) {
        ret = TRUE;
    }
    return ret;
}

/* 00001D30-00001E04       .text cut_init_ANGRY_START__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_ANGRY_START(int staffIdx) {
    cXyz* subst = dComIfGp_evmng_getMyXyzP(staffIdx, "Pos");

    if (subst != NULL) {
        // TODO regalloc
        this->current.pos.x = subst->x;
        this->current.pos.z = subst->z;
        this->current.pos.y = subst->y;
        this->mObjAcch.SetOld();
    }

    this->field_0x73C.x = 0.0;
    this->field_0x73C.y = this->eyePos.y;
    this->field_0x73C.z = 0.0;
    this->field_0x7FA = 2;

    this->current.angle.y = cLib_targetAngleY(&this->current.pos, &this->field_0x73C);
    this->speedF = 0.0;
    setAnm_NUM(0, 1);
    /* Nonmatching */
}

/* 00001E04-00001E0C       .text cut_move_ANGRY_START__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_ANGRY_START() {
    return 1;
}

/* 00001E0C-00001E5C       .text cut_init_BENSYOU_START__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_BENSYOU_START(int staffIdx) {
    this->cut_init_ANGRY_START(staffIdx);
    cXyz target_pos(0.0f, 0.0f, 700.0f);
    dComIfGp_evmng_setGoal(&target_pos);
}

/* 00001E5C-00001E64       .text cut_move_BENSYOU_START__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_BENSYOU_START() {
    return 1;
}

/* 00001E64-00001EB4       .text cut_init_TSUBO_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_CNT(int) {
    s16 res = this->chk_tsubo();
    this->field_0x7EE = this->field_0x7EC - res;

    this->m_jnt.setBackBone_x(0);
    this->m_jnt.setBackBone_y(0);
    this->m_jnt.setHead_x(0);
    this->m_jnt.setHead_y(0);

    this->field_0x7FA = 0;
    return;
}

/* 00001EB4-00001EBC       .text cut_move_TSUBO_CNT__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_TSUBO_CNT() {
    return 1;
}

/* 00001EBC-00001EE8       .text cut_init_BENSYOU__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_BENSYOU(int) {
    this->field_0x7F0 = dComIfGs_getRupee();

    dComIfGp_setItemRupeeCount(-(this->field_0x7EE * 10));
}

/* 00001EE8-00001EF0       .text cut_move_BENSYOU__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_BENSYOU() {
    /* Nonmatching */
    return 1;
}

/* 00001EF0-00001FE4       .text cut_init_GET_OUT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_GET_OUT(int staffIdx) {
    /* Nonmatching */
    int* ev = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");
    this->field_0x78C = 0;
    if (ev != NULL) {
        this->field_0x78C = *ev;
    }

    ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMoveAngle(0);
    // daPy_lk_c* player = (daPy_lk_c*)dComIfGp_getLinkPlayer();
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    player->changeDemoType(3);
    player->changeDemoParam0(0);
    if (!(this->field_0x7F0 < this->field_0x7EE * 10)) {
        cXyz angle(0.0f, 0.0f, 999.0f);

        cLib_targetAngleY(&daPy_getPlayerActorClass()->current.pos, &angle);
        ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMode(daPy_demo_c::DEMO_N_DASH_e);
    } else {

        ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoParam0(1);
        ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMode(daPy_demo_c::DEMO_LDAM_e);
    }
}

/* 00001FE4-00002044       .text cut_move_GET_OUT__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_GET_OUT() {
    s16 timer = cLib_calcTimer(&this->field_0x78C);
    if (timer == 0) {
        dComIfGp_setNextStage("sea", 3, 0xb);
    }

    return 0;
}

/* 00002044-0000205C       .text cut_init_DSP_RUPEE_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_DSP_RUPEE_CNT(int) {
    dComIfGp_event_offHindFlag(0x80);
}

/* 0000205C-00002064       .text cut_move_DSP_RUPEE_CNT__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_DSP_RUPEE_CNT() {
    return 1;
}

/* 00002064-000020AC       .text cut_init_PLYER_TRN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_TRN(int) {
    s16 angle = cLib_targetAngleY(&daPy_getPlayerActorClass()->current.pos, &this->current.pos);
    daPy_getPlayerActorClass()->changeDemoMoveAngle(angle);
}

/* 000020AC-000020B4       .text cut_move_PLYER_TRN__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_PLYER_TRN() {
    /* Nonmatching */
    return 1;
}

/* 000020B4-000020B8       .text cut_init_RUPEE_CNT_END__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_CNT_END(int) {
}

/* 000020B8-000020EC       .text cut_move_RUPEE_CNT_END__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_RUPEE_CNT_END() {
    if (dComIfGs_getRupee() == dComIfGp_getItemNowRupee()) {
        dComIfGp_event_onHindFlag(0x80);
        return TRUE;
    }
    return FALSE;
    /* Nonmatching */
}

/* 000020EC-00002168       .text cut_init_START_AGE__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_START_AGE(int) {
    f32 ycoord = this->eyePos.y;
    this->field_0x73C.x = 0.0;
    this->field_0x73C.y = ycoord;
    this->field_0x73C.z = 0.0;

    this->shape_angle.y = cLib_targetAngleY(&this->current.pos, &this->field_0x73C);

    this->field_0x7A8 = 1;
    this->field_0x7FA = 3;
    this->field_0x79A = this->shape_angle.y;
    this->m_jnt.setTrn();
    this->setAnm_NUM(0, 1);
}

/* 00002168-00002178       .text cut_move_START_AGE__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_START_AGE() {
    return !this->m_jnt.trnChk();
}

/* 00002178-00002284       .text cut_init_PLYER_MOV__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_MOV(int) {
    cXyz dst;

    s16 angle = cLib_targetAngleY(&this->current.pos, &dComIfGp_getPlayer(0)->current.pos) - this->current.angle.y;
    int angle_abs = abs(angle);
    if (angle_abs > 0x2000) {
        dComIfGp_evmng_setGoal(&dComIfGp_getPlayer(0)->current.pos);
    } else {
        cXyz vec(0.0, 0.0, 0.0);
        angle = (angle > 0) ? 0x2800 : -0x2800;
        // if (angle > 0) {
        //     angle_offset = 0x2800;
        // } else {
        //     angle_offset = -0x2800;
        // }
        MTXTrans(mDoMtx_stack_c::now, current.pos.x, current.pos.y, current.pos.z);

        cMtx_YrotM(mDoMtx_stack_c::now, this->current.angle.y + angle);
        vec.z = 150.0f;
        PSMTXMultVec(mDoMtx_stack_c::now, &vec, &dst);

        dComIfGp_evmng_setGoal(&dst);
    }

    /* Nonmatching */
}

/* 00002284-0000228C       .text cut_move_PLYER_MOV__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_PLYER_MOV() {
    return 1;
}

/* 0000228C-000023E8       .text cut_init_RUPEE_SET__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_SET(int) {
    if (this->field_0x7EC == 8) {
        // NOTE is this really char?
        // TODO regalloc
        char l54[8] = {0};
        for (int i = 0; i < 3; ++i) {
            int j;
            do {
                j = cM_rndF(32.0f) * 0.25f;
                // l48 = j;
            } while (l54[j] != 0);

            fopAc_ac_c* a_tsubo_actor = fopAcM_SearchByID(this->field_0x7BC[j]);
            JUT_ASSERT(0x5c3, NULL != a_tsubo_actor);
            fpcM_SetParam(a_tsubo_actor, (fpcM_GetParam(a_tsubo_actor) & 0xffffffc0) | 4);
            dComIfGp_event_setItemPartner(a_tsubo_actor);
            this->field_0x7BC[i + 8] = this->field_0x7BC[j];
            l54[j] = 1;
        }
    }
    this->setAnm_NUM(8, 1);
    /* Nonmatching */
}

/* 000023E8-0000260C       .text cut_move_RUPEE_SET__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_RUPEE_SET() {
    /* Nonmatching */
    int count = 0;
    if (this->field_0x79C == 0) {

        if (this->mpMorf->checkFrame(68.0f)) {
            cXyz vec(0.0f, 40.0f, 40.0f);
            cXyz dst;
            s8 reverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
            mDoAud_seStart(0x69e9, NULL, 0, reverb);

            MTXTrans(mDoMtx_stack_c::now, current.pos.x, current.pos.y, current.pos.z);

            cMtx_YrotM(mDoMtx_stack_c::now, this->current.angle.y);
            PSMTXMultVec(mDoMtx_stack_c::now, &vec, &dst);

            this->create_rupee(dst, 3);
        } else /* waiting for frame 68 */ {
            if (this->mpMorf->getFrame() < 68.0f) {
                for (int i = 0; i < 3; ++i) {
                    int id;
                    fopAc_ac_c* actor = this->searchByID(this->field_0x7B0[i], &id);
                    if (actor != NULL && id == 0) {
                        this->eyePos = actor->current.pos;
                    }
                }
                this->field_0x77C = 0;
            }
        }
        return FALSE;
    } else /* this->field_0x79C != 0 */ {
        int i;
        for (i = 0; i < 3; ++i) {
            int id;
            fopAc_ac_c* actor = this->searchByID(this->field_0x7B0[i], &id);
            if (actor != NULL) {
                fopAcM_delete(actor);
                ++count;
            } else {
                if (id != 0) {
                    ++count;
                }
            }
        }
        if (i == count) {
            this->ready_kutaniCamera(0, 1);
            this->field_0x77C = 1;
            this->setAnm_NUM(0, 1);
            return TRUE;
        } else {
            return FALSE;
        }
    }
}

/* 0000260C-000026B4       .text cut_init_TSUBO_ATN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_ATN(int staffIdx) {
    int* timer = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");
    int* count = dComIfGp_evmng_getMyIntegerP(staffIdx, "Count");

    this->field_0x78C = 0;
    if (timer != NULL) {
        this->field_0x78C = *timer;
    }
    this->field_0x78E = 0;
    if (count != NULL) {
        this->field_0x78E = *count;
    }
}

/* 000026B4-00002794       .text cut_move_TSUBO_ATN__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_TSUBO_ATN() {
    if (!cLib_calcTimer(&this->field_0x78C)) {
        s16 state = this->field_0x78E;
        if (state == 3) {
            switch (state) {
            case 0:
            case 1:
            case 2:
                this->ready_kutaniCamera(state, 1);
                break;
            case 3:
                this->ready_kutaniCamera(0, 0);
                break;
            }
        }
        
        return true;
    } else {

        if (this->field_0x78C == 0x14) {
            s8 reverb = dComIfGp_getReverb(this->current.roomNo);
            mDoAud_seStart(0x6981, NULL, 0, reverb);
        }
        return false;
    }

    /* Nonmatching */
}

/* 00002794-000028F4       .text cut_init_TLK_MSG__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TLK_MSG(int staffIdx) {
    int* msg_num = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNum");
    int* end_msg = dComIfGp_evmng_getMyIntegerP(staffIdx, "EndMsg");

    this->field_0x7F3 = 0xff;
    this->field_0x7F4 = 0xff;
    this->field_0x7FE = 0;
    this->mCurrMsgNo = 0;
    this->mEndMsgNo = -1;
    if (end_msg != NULL) {
        this->mEndMsgNo = *end_msg;
    }
    if (msg_num != NULL) {
        this->mCurrMsgNo = *msg_num;
        switch (this->mCurrMsgNo) {
        case 0x1c2e:
            break;
        case 0x1c2d:
            dComIfGp_setMessageCountNumber(this->field_0x7EE * 10);
            break;
        default:
            this->mCurrMsgNo = 0x1C30 + (field_0x7F0 >= field_0x7EE * 10 ? -1 : 0);
            break;
        case 0x1c39:
            dComIfGp_getVibration().StartShock(5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            break;
        }
    }
    this->mCurrMsgBsPcId = -1;
    /* Nonmatching */
}

/* 000028F4-00002954       .text cut_init_CONTNUE_TLK__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_CONTNUE_TLK(int staffIdx) {
    int* endMsg = dComIfGp_evmng_getMyIntegerP(staffIdx, "EndMsg");

    this->mEndMsgNo = -1;
    if (endMsg != NULL) {
        this->mEndMsgNo = *endMsg;
    }
}

/* 00002954-000029D8       .text cut_move_TLK_MSG__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_TLK_MSG() {
    u16 res = this->talk(0);
    if (res == 0x12) {
        this->field_0x7F3 = 0xff;
        this->field_0x7F4 = 0xff;
        this->field_0x7FE = 0;
        return true;
    } else if (res == 2 || res == 6) {
        return this->mCurrMsgNo == this->mEndMsgNo;
    } else {
        return false;
    }
}

static char* a_cut_tbl[14] = {
    "ANGRY_START",
    "BENSYOU_START",
    "TSUBO_CNT",
    "BENSYOU",
    "GET_OUT",
    "DSP_RUPEE_CNT",
    "PLYER_TRN",
    "RUPEE_CNT_END",
    "START_AGE",
    "PLYER_MOV",
    "RUPEE_SET",
    "TSUBO_ATN",
    "TLK_MSG",
    "CONTNUE_TLK"
};

/* 000029D8-00002C60       .text privateCut__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::privateCut(int staffIdx) {
    if (staffIdx == -1) return;

    this->field_0x7F2 = dComIfGp_evmng_getMyActIdx(staffIdx, a_cut_tbl, sizeof(a_cut_tbl) / sizeof(char*), TRUE, 0);
    if (this->field_0x7F2 == -1) {
        dComIfGp_evmng_cutEnd(staffIdx);
        return;
    }

    if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
        switch (this->field_0x7F2) {
        case 0:
            this->cut_init_ANGRY_START(staffIdx);
            break;
        case 1:
            this->cut_init_BENSYOU_START(staffIdx);
            break;
        case 2:
            this->cut_init_TSUBO_CNT(staffIdx);
            break;
        case 3:
            this->cut_init_BENSYOU(staffIdx);
            break;
        case 4:
            this->cut_init_GET_OUT(staffIdx);
            break;
        case 5:
            this->cut_init_DSP_RUPEE_CNT(staffIdx);
            break;
        case 6:
            this->cut_init_PLYER_TRN(staffIdx);
            break;
        case 7:
            this->cut_init_RUPEE_CNT_END(staffIdx);
            break;
        case 8:
            this->cut_init_START_AGE(staffIdx);
            break;
        case 9:
            this->cut_init_PLYER_MOV(staffIdx);
            break;
        case 10:
            this->cut_init_RUPEE_SET(staffIdx);
            break;
        case 0xb:
            this->cut_init_TSUBO_ATN(staffIdx);
            break;
        case 0xc:
            this->cut_init_TLK_MSG(staffIdx);
            break;
        case 0xd:
            this->cut_init_CONTNUE_TLK(staffIdx);
        }
    }
    bool res;
    switch (this->field_0x7F2) {
    case 0:
        res = this->cut_move_ANGRY_START();
        break;
    case 1:
        res = this->cut_move_BENSYOU_START();
        break;
    case 2:
        res = this->cut_move_TSUBO_CNT();
        break;
    case 3:
        res = this->cut_move_BENSYOU();
        break;
    case 4:
        res = this->cut_move_GET_OUT();
        break;
    case 5:
        res = this->cut_move_DSP_RUPEE_CNT();
        break;
    case 6:
        res = this->cut_move_PLYER_TRN();
        break;
    case 7:
        res = this->cut_move_RUPEE_CNT_END();
        break;
    case 8:
        res = this->cut_move_START_AGE();
        break;
    case 9:
        res = this->cut_move_PLYER_MOV();
        break;
    case 10:
        res = this->cut_move_RUPEE_SET();
        break;
    case 0xb:
        res = this->cut_move_TSUBO_ATN();
        break;
    case 0xc:
        res = this->cut_move_TLK_MSG();
        break;
    case 0xd:
        res = this->cut_move_TLK_MSG();
        break;
    default:
        res = TRUE;
        break;
    } /* Nonmatching */

    if (res) {
        dComIfGp_evmng_cutEnd(staffIdx);
    }
}

/* 00002C60-00002C84       .text endEvent__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::endEvent() {
    dComIfGp_event_reset();
    this->field_0x7F3 = 0xff;
    this->field_0x7F4 = 0xff;
}

/* 00002C84-00002CBC       .text isEventEntry__11daNpc_Kf1_cFv */
int daNpc_Kf1_c::isEventEntry() {
    return dComIfGp_evmng_getMyStaffId(this->mEventCut.getActorName());
}

/* 00002CBC-00002E14       .text event_proc__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::event_proc(int staffIdx) {
    if (dComIfGp_evmng_endCheck(this->field_0x780[this->field_0x780[3]])) {
        switch (this->field_0x780[3]) {
        case 0:
            dComIfGs_onEventBit(0x2780);
            this->field_0x7EC = this->chk_tsubo();
            break;
        case 1: {
            u8 event_reg = dComIfGs_getEventReg(0xbcff) | 1;
            dComIfGs_setEventReg(0xbcff, event_reg);
            this->field_0x7A8 = 0;
            this->setStt(1);
            this->setAnm_NUM(0, 1);
            this->field_0x792 = cLib_getRndValue(30, 60);
            this->field_0x790 = cLib_getRndValue(15, 30);
            this->field_0x7A1 = 1;
            break;
        }
        default:
            break;
        }

        this->field_0x792 = cLib_getRndValue(30, 60);
        this->endEvent();

    } else {
        if (!this->mEventCut.cutProc()) {
            this->privateCut(staffIdx);
        }
    }
    /* Nonmatching */
}

/* 00002E14-00002EC0       .text set_action__11daNpc_Kf1_cFM11daNpc_Kf1_cFPCvPvPv_iPv */
bool daNpc_Kf1_c::set_action(int (daNpc_Kf1_c::*action)(void*), void* param) {
    if (this->field_0x6F4 != action) {
        if (this->field_0x6F4) {
            this->field_0x7FD = 9;
            (this->*field_0x6F4)(param);
        }
        this->field_0x6F4 = action;

        this->field_0x7FD = 0;
        (this->*field_0x6F4)(param);
    }
    return true;
}

/* 00002EC0-00002F88       .text setStt__11daNpc_Kf1_cFSc */
void daNpc_Kf1_c::setStt(signed char stt) {
    u8 prev = field_0x7F8;
    field_0x7F8 = stt;
    switch (field_0x7F8) {
        case 0: break;
        case 1:
            field_0x7F7 = 0;
            field_0x794 = cLib_getRndValue(60, 90);
            speedF = 0.0f;
            break;
        case 2:
            field_0x7F7 = 0;
            field_0x7F3 = 0xff;
            field_0x7F4 = 0xff;
            field_0x7FE = 0;
            field_0x7F9 = prev;
            break;
        case 3:
            field_0x7F7 = 0;
            field_0x794 = cLib_getRndValue(90, 90);
            break;
    }
    setAnm();
    /* Nonmatching */
}

void daNpc_Kf1_c::set_pthPoint(unsigned char param) {
    if (this->pathRun.mPath != NULL) {
        this->pathRun.mCurrPointIndex = param;
        
        this->current.pos = this->pathRun.getPoint(this->pathRun.mCurrPointIndex);
        if (this->pathRun.nextIdx()) {
            cXyz nextPoint = this->pathRun.getPoint(this->pathRun.mCurrPointIndex);
            this->current.angle.y = cLib_targetAngleY(&this->current.pos, &nextPoint);
            
        }
    }
}

/* .text:0x2F44 | 0x3030 | size: 0x78 */
s16 daNpc_Kf1_c::chk_tsubo() {
    int id;
    s16 count = 0;
    for (int i = 0; i < 8; ++i) {
        searchByID(this->field_0x7BC[i], &id);
        if (id == 0) {
            count++;
        }
    }
    return count;
    /* Nonmatching */
}

/* 000037F4-00003884       .text shadowDraw__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::shadowDraw() {
    cXyz pos;

    pos.set(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    f32 prev_y = this->current.pos.y;
    // pos.z = this->current.pos.z;
    // f32 offset = 150.0f;
    // pos.y = this->current.pos.y + current.pos.y;
    // pos.x = this->current.pos.x;
    
    this->field_0x6D8 = dComIfGd_setShadow(
        this->field_0x6D8,
        1,
        this->mpMorf->getModel(),
        &pos,
        800.0f,
        40.0f,
        prev_y,
        this->mObjAcch.m_ground_h,
        this->mObjAcch.m_gnd,
        &this->tevStr
    );

    /* Nonmatching */
}

/* 00003884-0000397C       .text _draw__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_draw() {
    J3DModel* model = this->mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();

    if (this->field_0x7A7 || this->field_0x7A9) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &this->current.pos, &this->tevStr);
    g_env_light.setLightTevColorType(model, &this->tevStr);
    this->mBtpAnm.entry(modelData, this->field_0x6F0);
    this->mpMorf->entryDL();
    modelData->getMaterialTable().removeTexNoAnimator(this->mBtpAnm.getBtpAnm());

    if (this->mModel != NULL) {
        g_env_light.setLightTevColorType(this->mModel, &this->tevStr);
        mDoExt_modelEntryDL(this->mModel);
    }
    this->shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_UNK59, this, 1.0, 1.0, 1.0);

    return TRUE;
}

/* 0000397C-00003BC4       .text _execute__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_execute() {
    if (this->field_0x7AA == 0) {
        this->field_0x710 = this->current.pos;
        this->field_0x71C = this->current.angle;
        this->field_0x7AA = 1;
    }

    this->m_jnt.setParam(
        l_HIO.max_backbone_x,
        l_HIO.max_backbone_y,
        l_HIO.min_backbone_x,
        l_HIO.min_backbone_y,
        l_HIO.max_head_x,
        l_HIO.max_head_y,
        l_HIO.min_head_x,
        l_HIO.min_head_y,
        l_HIO.max_turn_step
    );

    if (this->field_0x7A7 && this->demoActorID == 0) {
        return TRUE;
    } else {
        this->srch_Tsubo();
        this->checkOrder();
        if (!this->demo()) {
            int event_entry = -1;
            dBgS* bgs = dComIfG_Bgsp();
            if (dComIfGp_event_getMode() != 0 && !this->eventInfo.checkCommandTalk()) {
                event_entry = this->isEventEntry();
            }
            if (event_entry >= 0 || this->field_0x7A5) {
                this->event_proc(event_entry);
            } else {
                (this->*field_0x6F4)(NULL);
            }
            this->lookBack();
            fopAcM_posMoveF(this, this->mStts.GetCCMoveP());
            this->field_0x7A3 = this->mObjAcch.ChkGroundHit();
            this->field_0x7A4 = this->mObjAcch.ChkWaterIn();
            this->mObjAcch.CrrPos(*bgs);
            this->play_animation();
        } else {
            this->field_0x7A7 = 0;
        }
        this->eventOrder();
        this->mAngle = this->current.angle;
        if (!this->field_0x7A8) {
            this->shape_angle = this->current.angle;
        }
        this->tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(this->mObjAcch.m_gnd);
        this->tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(this->mObjAcch.m_gnd);

        this->setMtx(false);

        if (!this->field_0x7AE) {
            this->setCollision(90.0f, 200.0f);
        }
        return TRUE;
    }
}

/* 00003BC4-00003C18       .text _delete__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_delete() {
    dComIfG_resDelete(&this->mPhs, this->field_0x6D4);
    if (this->heap != NULL && this->mpMorf != NULL) {
        this->mpMorf->stopZelAnime();
    }
    return TRUE;
}


static u32 a_siz_tbl[] = {
    0, 0
};
/* 00003C18-00003E64       .text _create__11daNpc_Kf1_cFv */
cPhs_State daNpc_Kf1_c::_create() {
    /* Nonmatching */
    fopAcM_SetupActor(this, daNpc_Kf1_c);
    if (!decideType(base.base.mParameters & 0xff)) {
        return cPhs_ERROR_e;
    }
    s32 ret = dComIfG_resLoad(&this->mPhs, field_0x6D4);
    this->field_0x7A6 = ret == cPhs_COMPLEATE_e;
    if (!field_0x7A6) {
        return ret;
    }
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[this->field_0x7FB])) {
        return cPhs_ERROR_e;
    } else {
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -90.0f, -20.0f, -80.0f, 90.0f, 200.0f, 80.0f);
        if (createInit()) {
            return ret;
        }
        else {
            return cPhs_ERROR_e;
        }
    }

    return ret;
}

/* 00004130-0000442C       .text bodyCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::bodyCreateHeap() {
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(field_0x6D4, 1);
    JUT_ASSERT(0x97f, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(a_mdl_dat,
                                NULL,
                                NULL,
                                NULL,
                                J3DFrameCtrl::EMode_NULL,
                                1.0f,
                                0,
                                -1,
                                1,
                                NULL,
                                0x80000,
                                0x11020022);
    if (mpMorf == NULL) {
        return FALSE;
    }
    if (mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }

    if (!init_texPttrnAnm(0, false)) {
        mpMorf = NULL;
        return false;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x993, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x995, m_bbone_jnt_num >= 0);
    m_nck_jnt_num = a_mdl_dat->getJointName()->getIndex("neck");
    JUT_ASSERT(0x997, m_nck_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointTree().getJointNodePointer(m_hed_jnt_num)->mCallBack = nodeCB_Head;
    mpMorf->getModel()->getModelData()->getJointTree().getJointNodePointer(m_bbone_jnt_num)->mCallBack = nodeCB_BackBone;
    mpMorf->getModel()->getModelData()->getJointTree().getJointNodePointer(m_nck_jnt_num)->mCallBack = nodeCB_Neck;
    mpMorf->getModel()->setUserArea(reinterpret_cast<u32>(this));
    return TRUE;
}

/* 0000442C-000044EC       .text itemCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::itemCreateHeap() {
    /* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*) dComIfG_getObjectIDRes(field_0x6D4, 0);
    JUT_ASSERT(0x9ac, a_mdl_dat != NULL);

    // TODO enums?
    J3DModel* model = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    this->mModel = model;
    if (this->mModel == NULL) {
        return false;
    }
    else {
        return true;
    }
}

/* 000044EC-00004590       .text CreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::CreateHeap() {
    if (!bodyCreateHeap()) {
        return FALSE;
    }
    if (!itemCreateHeap()) {
        this->mpMorf = NULL;
        return FALSE;
    }
    else {
        // TODO nonmatching on account of storage of these?
        mAcchCir.SetWall(30.0f, 90.0f);
        mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir,
                     fopAcM_GetSpeed_p(this));
    }
    return TRUE;
    /* Nonmatching */
}

/* 00004590-000045B0       .text daNpc_Kf1_Create__FP10fopAc_ac_c */
static s32 daNpc_Kf1_Create(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Kf1_c*>(i_this)->_create();
    /* Nonmatching */
}

/* 000045B0-000045D0       .text daNpc_Kf1_Delete__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Delete(daNpc_Kf1_c* i_this) {
    return static_cast<daNpc_Kf1_c*>(i_this)->_delete();
}

/* 000045D0-000045F0       .text daNpc_Kf1_Execute__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Execute(daNpc_Kf1_c* i_this) {
    return static_cast<daNpc_Kf1_c*>(i_this)->_execute();
}

/* 000045F0-00004610       .text daNpc_Kf1_Draw__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Draw(daNpc_Kf1_c* i_this) {
    return static_cast<daNpc_Kf1_c*>(i_this)->_draw();
}

/* 00004610-00004618       .text daNpc_Kf1_IsDelete__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_IsDelete(daNpc_Kf1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Kf1_Method = {
    (process_method_func)daNpc_Kf1_Create,
    (process_method_func)daNpc_Kf1_Delete,
    (process_method_func)daNpc_Kf1_Execute,
    (process_method_func)daNpc_Kf1_IsDelete,
    (process_method_func)daNpc_Kf1_Draw,
};

actor_process_profile_definition g_profile_NPC_KF1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_KF1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kf1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_KF1,
    /* Actor SubMtd */ &l_daNpc_Kf1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
