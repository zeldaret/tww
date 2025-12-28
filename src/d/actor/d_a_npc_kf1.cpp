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
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "d/actor/d_a_player.h"
#include "f_op/f_op_actor_mng.h"

#include "d/actor/d_a_tsubo.h"
#include "d/d_priority.h"
#include <string.h>


static daNpc_Kf1_HIO_c l_HIO;

static u8 a_prm_tbl[0x30];

/* 000000EC-00000150       .text __ct__15daNpc_Kf1_HIO_cFv */
daNpc_Kf1_HIO_c::daNpc_Kf1_HIO_c() {
    memcpy(data, a_prm_tbl, 0x30);
    b = a = -1;

    /* Nonmatching */
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

cXyz a_eye_pos_off;
u8 init;

/* 000001E4-000002D8       .text _nodeCB_Head__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Head(J3DNode* node, J3DModel* model) {
    if (init == 0) {
        a_eye_pos_off = cXyz(30.0f, 30.0f, 0.0f);
        init = 1;
    }

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
        set_action(&daNpc_Kf1_c::wait_action1, NULL);
        return TRUE;
    }
    return FALSE;
}

dCcD_SrcCyl dNpc_cyl_src;

/* 0000061C-0000083C       .text createInit__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::createInit() {
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
        }
        else {
            return FALSE;
        }
    }
    if (this->pathRun.mPath == NULL) {
        status = FALSE;
    } else {
        this->attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
        this->attention_info.distances[1] = 0xab;
        this->attention_info.distances[3] = 0xab;
        this->gravity = -4.5f;
        this->mAnmId = 10;

        BOOL init;
        if (field_0x7FC != 0) {
            init = FALSE;
        } else {
            init = this->init_KF1_0();
        }
        if (init == FALSE) {
            status = FALSE;
        } else {
            mAngle = current.angle;
            shape_angle = mAngle;
            mStts.Init(weight, 0xff, this);
            mCyl.SetStts(&mStts);
            mCyl.Set(dNpc_cyl_src);
            mObjAcch.CrrPos(*dComIfG_Bgsp());
            play_animation();
            this->tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
            tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
            mpMorf->setMorf(0.0f);
            setMtx(true);

            status = TRUE;
        }
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
    mpMorf->getModel()->setBaseScale(scale);
    MTXTrans(mDoMtx_stack_c::now, current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_ZXYrotM(mDoMtx_stack_c::now, mAngle.x, mAngle.y, mAngle.z);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
    mpMorf->calc();
    if (mModel != NULL) {
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        //MTXCopy(mpMorf->getModel()->mpNodeMtx[m_hed_jnt_num], mDoMtx_stack_c::now);
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
BOOL daNpc_Kf1_c::setBtp(signed char btpId, bool i_modify) {
    /* Nonmatching */
    J3DModel* model = mpMorf->getModel();
    if (btpId < 0) {
        return FALSE;
    }
    J3DAnmTexPattern *a_btp = (J3DAnmTexPattern*) dComIfG_getObjectIDRes(field_0x6d4, (int)btpResID(btpId));
    JUT_ASSERT(0x20a, a_btp != NULL);

    field_0x7F5 = btpId;
    field_0x6F0 = 0;
    field_0x6F2 = 0;
    return mBtpAnm.init(model->getModelData(), a_btp, TRUE, 0, 1.0f, 0, -1, i_modify, FALSE);
}

/* 00000B4C-00000B6C       .text init_texPttrnAnm__11daNpc_Kf1_cFScb */
BOOL daNpc_Kf1_c::init_texPttrnAnm(signed char btpId, bool i_modify) {
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
                     bckResID(i_anmPrm->anmId), -1, field_0x6d4);
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
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7F9].flag, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7F9]);
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
    init_texPttrnAnm(a_anm_prm_tbl[field_0x7F5].flag, true);
    setAnm_anm(&a_anm_prm_tbl[field_0x7F5]);
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
    case 0x1c33:
        // TODO cryptic add with carry that I don't know how to spell
        u32 temp_r3_3 = this->field_0x7EE * 0xA;
        u32 temp_r3_4 = (this->field_0x7F0 - temp_r3_3) + (temp_r3_3 ^ 0x80000000);
        *param = (temp_r3_4 - temp_r3_4) + 0x1C30;
        // *param = 0x1c30;
        break;
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
    if (field_0x7F9 == 1 || field_0x7F9 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (field_0x7F9 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
    else if (field_0x7F9 >= 3) {
        field_0x780[3] = field_0x7F9 - 3;
        fopAcM_orderOtherEventId(this, field_0x780[field_0x780[3]]);
    }
}

/* 000012A4-00001380       .text checkOrder__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::checkOrder() {
    /* Nonmatching */
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (dComIfGp_evmng_startCheck(field_0x780[field_0x780[3]]) && field_0x7F9 >= 3) {
            // TODO missing blt statement in asm around here
            switch(field_0x780[3]) {
                case 0:
                static_cast<daPy_py_c*>(dComIfGp_getPlayer(0))
                    ->changeDemoMoveAngle(dComIfGp_getPlayer(0)->current.angle.y);
                break;
            }
            field_0x7F9 = 0;
            field_0x7F4 = 0xff;
            field_0x7F5 = 0xff;
        }
    } else if (eventInfo.checkCommandTalk()) {
        switch (field_0x7F9) {
            case 0: case 1:
                field_0x7F9 = 0;
                field_0x7AC = 1;
                break;
        }
    }
}

/* 00001380-00001418       .text chk_talk__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::chk_talk() {
    if (dComIfGp_event_chkTalkXY()) {
        if (dComIfGp_evmng_ChkPresentEnd()) {
            field_0x79E = dComIfGp_event_getPreItemNo();
            return TRUE;
        }
        else {
            return FALSE;
        }
    }
    else {
        field_0x79E = 0xff;
        return TRUE;
    }
}

/* 00001418-0000146C       .text searchByID__11daNpc_Kf1_cFUiPi */
fopAc_ac_c *daNpc_Kf1_c::searchByID(fpc_ProcID i_procId, int* o_par1) {
    fopAc_ac_c *ret = NULL;
    *o_par1 = 0;
    s32 id = fopAcM_SearchByID(i_procId, &ret);
    if (id == 0) {
        *o_par1 = 1;
    }
    return ret;
}

/* 0000146C-0000156C       .text srch_Tsubo__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::srch_Tsubo() {
    /* Nonmatching */

    int i = 0;
    BOOL ret = FALSE;
    int j = 0;
    switch (field_0x7FD) {
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
            ret = TRUE;
            field_0x7FD++;
            break;
        }
    default:
        ret = FALSE;
        break;
    }
    return ret;
}

/* 0000156C-000017F4       .text create_rupee__11daNpc_Kf1_cF4cXyzi */
void daNpc_Kf1_c::create_rupee(cXyz vec, int count) {
    /* Nonmatching */
    cXyz scale(0.2, 0.2, 0.2);
    csXyz shape_angle(0, 0, 0);

    u32 cnt = g_Counter.mCounter0;
    for (int i = 0; i < count; ++i) {
        f32 nums[] = {-30.0, 0.0, 30.0};
        s16 j = ((s16)(nums[cnt % 3] + cM_rndF(30.0) - 15.0) ^ 0x8000) * *(float*)((u32*)0x433609F5);
        // j = j ^ 0x80000000;
        // mysterious constant 0x433609F5 (182.0389f) here.
        // a similar constant 182.0445f appears in Degree_To_Sangle but this is what ghidra says
        // j = (int)(j * *(float*)((u32*)0x433609F5));
        shape_angle.y = this->current.angle.y + (s16)j;
        s8 roomNo = current.roomNo;
        f32 speed = cM_rndFX(4.0) + 13.0;
        f32 yvelocity = cM_rndFX(2.0) + 31.0;
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
            fpc_ProcID id;
            if (a_actor_p == NULL) {
                id = fopAcM_GetID(a_actor_p);
            } else {
                id = -1;
            }
            this->field_0x7BC[i] = id;
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
    strcpy(this->field_0x6d4, "Kf");
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
    /* Nonmatching */
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
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 00001EE8-00001EF0       .text cut_move_BENSYOU__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_BENSYOU() {
    /* Nonmatching */
    return 1;
}

/* 00001EF0-00001FE4       .text cut_init_GET_OUT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_GET_OUT(int) {
    /* Nonmatching */
}

/* 00001FE4-00002044       .text cut_move_GET_OUT__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_GET_OUT() {
    /* Nonmatching */
}

/* 00002044-0000205C       .text cut_init_DSP_RUPEE_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_DSP_RUPEE_CNT(int) {
    /* Nonmatching */
}

/* 0000205C-00002064       .text cut_move_DSP_RUPEE_CNT__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_DSP_RUPEE_CNT() {
    /* Nonmatching */
    return 1;
}

/* 00002064-000020AC       .text cut_init_PLYER_TRN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_TRN(int) {
    /* Nonmatching */
}

/* 000020AC-000020B4       .text cut_move_PLYER_TRN__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_PLYER_TRN() {
    /* Nonmatching */
    return 1;
}

/* 000020B4-000020B8       .text cut_init_RUPEE_CNT_END__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_CNT_END(int) {
    /* Nonmatching */
}

/* 000020B8-000020EC       .text cut_move_RUPEE_CNT_END__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_RUPEE_CNT_END() {
    /* Nonmatching */
}

/* 000020EC-00002168       .text cut_init_START_AGE__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_START_AGE(int) {
    /* Nonmatching */
}

/* 00002168-00002178       .text cut_move_START_AGE__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_START_AGE() {
    /* Nonmatching */
}

/* 00002178-00002284       .text cut_init_PLYER_MOV__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_MOV(int) {
    /* Nonmatching */
}

/* 00002284-0000228C       .text cut_move_PLYER_MOV__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_PLYER_MOV() {
    /* Nonmatching */
    return 1;
}

/* 0000228C-000023E8       .text cut_init_RUPEE_SET__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_SET(int) {
    /* Nonmatching */
}

/* 000023E8-0000260C       .text cut_move_RUPEE_SET__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_RUPEE_SET() {
    /* Nonmatching */
}

/* 0000260C-000026B4       .text cut_init_TSUBO_ATN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_ATN(int) {
    /* Nonmatching */
}

/* 000026B4-00002794       .text cut_move_TSUBO_ATN__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_TSUBO_ATN() {
    /* Nonmatching */
}

/* 00002794-000028F4       .text cut_init_TLK_MSG__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TLK_MSG(int) {
    /* Nonmatching */
}

/* 000028F4-00002954       .text cut_init_CONTNUE_TLK__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_CONTNUE_TLK(int) {
    /* Nonmatching */
}

/* 00002954-000029D8       .text cut_move_TLK_MSG__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_TLK_MSG() {
    /* Nonmatching */
}

/* 000029D8-00002C60       .text privateCut__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::privateCut(int) {
    /* Nonmatching */
}

/* 00002C60-00002C84       .text endEvent__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::endEvent() {
    /* Nonmatching */
}

/* 00002C84-00002CBC       .text isEventEntry__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::isEventEntry() {
    /* Nonmatching */
}

/* 00002CBC-00002E14       .text event_proc__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::event_proc(int) {
    /* Nonmatching */
}

/* 00002E14-00002EC0       .text set_action__11daNpc_Kf1_cFM11daNpc_Kf1_cFPCvPvPv_iPv */
void daNpc_Kf1_c::set_action(int (daNpc_Kf1_c::*)(void*), void*) {
    /* Nonmatching */
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

/* 000037F4-00003884       .text shadowDraw__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::shadowDraw() {
    /* Nonmatching */
}

/* 00003884-0000397C       .text _draw__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_draw() {
    /* Nonmatching */
}

/* 0000397C-00003BC4       .text _execute__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_execute() {
    /* Nonmatching */
}

/* 00003BC4-00003C18       .text _delete__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_delete() {
    /* Nonmatching */
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
    s32 ret = dComIfG_resLoad(&this->mPhs, field_0x6d4) ;
    field_0x7A6 = ret == cPhs_COMPLEATE_e;
    if (field_0x7A6) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[this->field_0x7FB])) {
            ret = cPhs_ERROR_e;
        }
        else {
            fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
            fopAcM_setCullSizeBox(this,-90.0f,-20.0f,-80.0f,90.0f,200.0f,80.0f);
            if (!createInit()) {
                return  cPhs_ERROR_e;
            }
        }
    }
    return ret;
}

/* 00004130-0000442C       .text bodyCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::bodyCreateHeap() {
    /* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*) dComIfG_getObjectIDRes(field_0x6d4, 1);
    JUT_ASSERT(0x97f, a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(a_mdl_dat, NULL, NULL, NULL, /* ~J3DFrameCtrl::LOOP_ONCE_e */NULL, 1.0f, 0, -1, 1, NULL, 0x80000, 0x11000022);
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        mpMorf = NULL;
        return FALSE;
    }

    if (!init_texPttrnAnm(0, false)) {
        mpMorf = NULL;
        return FALSE;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(0x993, m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(0x995, m_bbone_jnt_num >= 0);
    m_nck_jnt_num = a_mdl_dat->getJointName()->getIndex("neck");
    JUT_ASSERT(0x997, m_nck_jnt_num >= 0);

    mpMorf->getModel()->getModelData()->getJointTree().getJointNodePointer(m_hed_jnt_num)
        ->mCallBack = nodeCB_Head;
    mpMorf->getModel()->getModelData()->getJointTree().getJointNodePointer(m_bbone_jnt_num)
        ->mCallBack = nodeCB_BackBone;
    mpMorf->getModel()->getModelData()->getJointTree().getJointNodePointer(m_nck_jnt_num)
        ->mCallBack = nodeCB_Neck;
    //mpMorf->getModel()->setUserArea(u32 area)
    return TRUE;
}

/* 0000442C-000044EC       .text itemCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::itemCreateHeap() {
    /* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*) dComIfG_getObjectIDRes(field_0x6d4, 0);
    JUT_ASSERT(0x9ac, a_mdl_dat != NULL);

    // TODO enums?
    J3DModel* model = mDoExt_J3DModel__create(a_mdl_dat, 0x80000, 0x11000022);
    this->mModel = model;
    return mModel != NULL;
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
