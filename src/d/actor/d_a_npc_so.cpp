/**
 * d_a_npc_so.cpp
 * NPC - Fishman (blue fish)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_so.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_ship.h"
#include "d/d_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/d_lib.h"
#include "f_op/f_op_kankyo_mng.h"
#include "f_op/f_op_camera.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_audio.h"
#include "d/res/res_so.h"
#include "d/d_kankyo.h"
#include "d/d_snap.h"

char* daNpc_So_c::m_arc_name = "So";

static cXyz cyl_offset_B[] = {
    cXyz(15.0f, 0.0f, 0.0f),
    cXyz(-15.0f, 0.0f, 0.0f),
};

static __jnt_hit_data_c search_data[] = {
    {0, 4, 2.0f, &cyl_offset_B[0]},
    {0, 8, 2.0f, &cyl_offset_B[0]},
};

/* 000003EC-00000438 0002F8 004C+00 1/1 0/0 0/0 .text            nodeControl_CB__FP7J3DNodei */
static int nodeControl_CB(J3DNode* i_node, int i_param) {
    if (i_param == 0) {
        J3DModel* model = j3dSys.getModel();
        daNpc_So_c* a_this = (daNpc_So_c*)model->getUserArea();
        if (a_this != NULL) {
            a_this->_nodeControl(i_node, model);
        }
    }
    return 1;
}

/* 00000438-00000568       .text _nodeControl__10daNpc_So_cFP7J3DNodeP8J3DModel */
void daNpc_So_c::_nodeControl(J3DNode* i_node, J3DModel* i_model) {
    J3DJoint* jnt_p = (J3DJoint*)i_node;
    s32 jnt_no = jnt_p->getJntNo();

    if (jnt_no == m_jnt.getHeadJntNum()) {
        mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());

        cXyz eyeOffset(m_heapsize.m0080, m_heapsize.m0084, 0.0f);
        cXyz transformedEyePos;
        mDoMtx_stack_c::multVec(&eyeOffset, &transformedEyePos);

        mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
        i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
    } else if (jnt_no == m_jnt.getBackboneJntNum()) {
        mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());

        mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
        i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
    }
}

/* 00000B14-00000B78 000A20 0064+00 1/1 0/0 0/0 .text            jntHitCreateHeap__10daNpc_So_cFv */
bool daNpc_So_c::jntHitCreateHeap() {
    mpJntHit2 = JntHit_create(mpMorf->getModel(), search_data, 2);
    if (mpJntHit2 != NULL) {
        jntHit = mpJntHit2;
    }
    return mpJntHit2 != NULL;
}

/* 00000800-00000B14       .text _createHeap__10daNpc_So_cFv */
int daNpc_So_c::_createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, SO_BDL_SO);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes(m_arc_name, SO_BCK_SO_WAIT01),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0, 0x11020203
    );

    if (!mpMorf || !mpMorf->getModel()) {
        mpMorf = NULL;
        return FALSE;
    }

    mpModel = mDoExt_J3DModel__create(
        (J3DModelData*)dComIfG_getObjectRes(m_arc_name, SO_BDL_SO_FUDE),
        0x80000, 0x11020203
    );

    mBtpAnm.init(
        modelData,
        (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arc_name, SO_BTP_SO),
        TRUE, J3DFrameCtrl::EMode_LOOP,
        1.0f, 0, -1, false, FALSE
    );

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));

    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        if (i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum()) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeControl_CB);
        }
    }

    mpMorf->getModel()->setUserArea((u32)this);

    if (!jntHitCreateHeap()) {
        return FALSE;
    }

    return TRUE;
}

/* 000000EC-000002A4       .text __ct__14daNpc_So_HIO_cFv */
daNpc_So_HIO_c::daNpc_So_HIO_c() {
    mNpcHIO.m04 = -20.0f;
    mNpcHIO.mMaxHeadX = 0x400;
    mNpcHIO.mMaxHeadY = 0x400;
    mNpcHIO.mMaxBackboneX = 0x1000;
    mNpcHIO.mMaxBackboneY = 0x1500;
    mNpcHIO.mMinHeadX = -0x400;
    mNpcHIO.mMinHeadY = -0x400;
    mNpcHIO.mMinBackboneX = -0x1000;
    mNpcHIO.mMinBackboneY = -0x1500;
    mNpcHIO.mMaxTurnStep = 0x1000;
    mNpcHIO.mMaxHeadTurnVel = 0x800;
    mNpcHIO.mAttnYOffset = 70.0f;
    mNpcHIO.mMaxAttnAngleY = 0x4000;
    mNpcHIO.m22 = 0;
    mNpcHIO.mMaxAttnDistXZ = 350.0f;

    m0034 = 600.0f;
    m0038 = 200.0f;
    m003C = 300.0f;
    m0040 = 600.0f;
    m0044 = 5.0f;
    m0048 = 6.0f;
    m004C = 3.0f;
    m0050 = 0.5f;
    m0054 = 50.0f;
    m0058 = 0.0f;
    m005C = 0.0f;
    m0060 = 100.0f;
    m0064 = 0x800;
    m0066 = 0x400;
    m0068 = 0;
    m006A = 0;
    m006C = -40.0f;
    m0070 = 0.0f;
    m0074 = 0.0f;
    m0078 = 0.0f;
    m007C = 0;
    m0080 = 20.0f;
    m0084 = 15.0f;
    m0088 = 150.0f;
    m008C = 50.0f;
    m0090 = 0.0f;
    m0094 = 0.0f;
    m00C4 = 15.0f;
    m00C8 = 0.0f;
    m00CC = 0.0f;
    m00D0 = 0.0f;
    m00D4 = 1.0f;
    m00D8 = 0.1f;
    m00DC = 0.01f;
    m00E0 = 0.001f;
    m00E4 = 0.1f;
    m00E8 = 0.5f;
    m00EC = 0.5f;
    m00F0 = 1.0f;
    m00F4 = 0.01f;
    m00F8 = 0.0f;
    m00FC = 0.0f;
    m0100 = 0.5f;
    m0104 = 1.0f;
    m0108 = 0.01f;
    m010C = 0.5f;
    m0110 = 1.0f;
    m0114 = 0.01f;
    m0118 = 7.0f;
    m011C = -7.0f;
    m0120 = 0x4E20;
    m0122 = 0;
    m0124 = 0;
    m0126 = 0;
    m0128 = 0;
    m012A = 0;
    m012C = 0.0f;
    m0130 = -40.0f;
    m0134 = -80.0f;
    m0138 = -50.0f;
    m013C = 40.0f;
    m0140 = 0.0f;
    m0144 = 0.0f;
}

daNpc_So_HIO_c daNpc_So_c::m_heapsize;

/* 000002A4-000002D0       .text searchEsa_CB__FPvPv */
void searchEsa_CB(void* i_actor, void* i_data) {
    ((daNpc_So_c*)i_data)->_searchEsa((fopAc_ac_c*)i_actor);
}

/* 000002D0-000002F8       .text _searchEsa__10daNpc_So_cFP10fopAc_ac_c */
void daNpc_So_c::_searchEsa(fopAc_ac_c* i_actor) {
    if (fopAcM_GetProfName(i_actor) == PROC_OBJ_SEARCH) {
        if (*(u8*)((u32)i_actor + 0x298) == 0) {
            // Return i_actor (found)
            return;
        }
    }
    // Return NULL (not found) - handled by fopAcIt_Judge
}


/* 000004B0-000004DC       .text searchTagSo_CB__FPvPv */
void searchTagSo_CB(void* i_actor, void* i_data) {
    ((daNpc_So_c*)i_data)->_searchTagSo((fopAc_ac_c*)i_actor);
}

/* 000004DC-0000054C       .text _searchTagSo__10daNpc_So_cFP10fopAc_ac_c */
fopAc_ac_c* daNpc_So_c::_searchTagSo(fopAc_ac_c* i_actor) {
    if (fopAcM_GetName(i_actor) == PROC_TAG_SO) {
        if (m0A79 == *(u8*)((u32)i_actor + 0x290) &&
            *(u8*)((u32)i_actor + 0x298) != 1) {
            m0A7C = *(f32*)((u32)i_actor + 0x294);
            m0A80.x = i_actor->current.pos.x;
            m0A80.y = i_actor->current.pos.y;
            m0A80.z = i_actor->current.pos.z;
            current.pos.x = m0A80.x;
            current.pos.y = m0A80.y;
            current.pos.z = m0A80.z;
            return i_actor;
        }
    }
    return NULL;
}

/* 0000054C-00000578       .text searchMinigameTagSo_CB__FPvPv */
void searchMinigameTagSo_CB(void* i_actor, void* i_data) {
    ((daNpc_So_c*)i_data)->_searchMinigameTagSo((fopAc_ac_c*)i_actor);
}

/* 00000578-000005C8       .text _searchMinigameTagSo__10daNpc_So_cFP10fopAc_ac_c */
fopAc_ac_c* daNpc_So_c::_searchMinigameTagSo(fopAc_ac_c* i_actor) {
    if (fopAcM_GetName(i_actor) == PROC_TAG_SO) {
        if (*(u8*)((u32)i_actor + 0x298) == 1) {
            mB90.x = i_actor->current.pos.x;
            mB90.y = i_actor->current.pos.y;
            mB90.z = i_actor->current.pos.z;
            mB9C = i_actor->shape_angle.y;
            *(u8*)((u32)this + 0xBAE) = 1;
            return i_actor;
        }
    }
    return NULL;
}

/* 000005C8-000005E8       .text daNpc_So_XyCheckCB__FPvi */
static s16 daNpc_So_XyCheckCB(void* i_this, int i_param) {
    return ((daNpc_So_c*)i_this)->XyCheckCB(i_param);
}

/* 000005E8-00000680       .text XyCheckCB__10daNpc_So_cFi */
s16 daNpc_So_c::XyCheckCB(int i_param) {
    void* esa = fopAcIt_Judge((fopAcIt_JudgeFunc)searchEsa_CB, this);
    if (esa != NULL) {
        return 0;
    }
    if (m06D3 != 2) {
        return 0;
    }
    if (dComIfGp_checkPlayerStatus0(0, 0x10000)) {
        if (*(u8*)((u32)&g_dComIfG_gameInfo + 0x5BD3 + i_param) == 0x82) {
            return 1;
        }
    }
    return 0;
}

/* 00000680-000006A0       .text daNpc_So_XyEventCB__FPvi */
static s16 daNpc_So_XyEventCB(void* i_this, int i_param) {
    return ((daNpc_So_c*)i_this)->XyEventCB(i_param);
}

/* 000006A0-000006EC       .text XyEventCB__10daNpc_So_cFi */
s16 daNpc_So_c::XyEventCB(int i_param) {
    mBDC = dComIfGp_getPEvtManager()->getEventIdx("SO_ESA_XY", 0xFF);
    return mBDC;
}

/* 000006EC-0000070C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daNpc_So_c*)i_this)->_createHeap();
}


/* 00000A84-00000C8C       .text checkTgHit__10daNpc_So_cFv */
BOOL daNpc_So_c::checkTgHit() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    mStts.Move();

    if (cLib_calcTimer(&m06D8) != 0) {
        return FALSE;
    }

    if (!mSph.ChkTgHit()) {
        return FALSE;
    }

    cXyz* hitPos = mSph.GetTgHitPosP();
    cCcD_Obj* hitObj = mSph.GetTgHitObj();

    m06D8 = l_HIO.m007C;

    if (hitObj == NULL) {
        return FALSE;
    }

    if (hitObj->GetAtType() == AT_TYPE_NORMAL_ARROW) {
        mDoAud_zelAudio_c::getInterface()->seStart(
            JA_SE_LK_ARROW_HIT, &eyePos, 0x20,
            dComIfGp_getReverb(fopAcM_GetRoomNo(this)),
            m_heapsize.m00A8, m_heapsize.m00A8,
            m_heapsize.m00C8, m_heapsize.m00C8, 0
        );
    }

    fopAcM_monsSeStart(this, JA_SE_CV_SO_DAMAGE, 0);

    dComIfGp_particle_set(0x10, hitPos);

    f32 scaleVal = *(f32*)((u8*)&m_heapsize + 0x64);
    cXyz scaleVec(scaleVal, scaleVal, scaleVal);
    dComIfGp_particle_set(0x0F, hitPos, &player->shape_angle, &scaleVec);

    mDoAud_zelAudio_c::getInterface()->seStart(
        JA_SE_LK_LAST_HIT, &eyePos, 0,
        dComIfGp_getReverb(fopAcM_GetRoomNo(this)),
        m_heapsize.m00A8, m_heapsize.m00A8,
        m_heapsize.m00C8, m_heapsize.m00C8, 0
    );

    return TRUE;
}

/* 00000C8C-00000CB0       .text offsetZero__10daNpc_So_cFv */
void daNpc_So_c::offsetZero() {
    mB40 = m_heapsize.m00FC;
    mB3C = m_heapsize.m00F8;
    mB38 = m_heapsize.m00C8;
}

/* 00000CB0-00000CD4       .text offsetDive__10daNpc_So_cFv */
void daNpc_So_c::offsetDive() {
    mB40 = m_heapsize.m0130;
    mB3C = m_heapsize.m006C;
    mB38 = m_heapsize.m0134;
}

/* 00000CD4-00000CF8       .text offsetSwim__10daNpc_So_cFv */
void daNpc_So_c::offsetSwim() {
    mB40 = m_heapsize.m0130;
    mB3C = m_heapsize.m006C;
    mB38 = m_heapsize.m0138;
}

/* 00000CF8-00000D1C       .text offsetAppear__10daNpc_So_cFv */
void daNpc_So_c::offsetAppear() {
    mB40 = m_heapsize.m013C;
    mB3C = m_heapsize.m0140;
    mB38 = m_heapsize.m0144;
}

/* 00000D1C-00000E40       .text getMsg__10daNpc_So_cFv */
u32 daNpc_So_c::getMsg() {
    u32 msgNo;

    if (mBD9 != 0) {
        mBD9 = 0;
        return 0x339B;
    }

    if (mBD8 != 0) {
        mBD8 = 0;
        return 0x3395;
    }

    if (!dComIfGs_isEventBit(0x2C01)) {
        msgNo = 0x3381 + m06D0 - 1;
    } else if (m06D3 == 2) {
        msgNo = 0x33A5;
    } else {
        msgNo = 0x3395;
    }

    return msgNo;
}

/* 00000E40-00001214       .text next_msgStatus__10daNpc_So_cFPUl */
u16 daNpc_So_c::next_msgStatus(unsigned long* pMsgNo) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;

    switch (*pMsgNo) {
    case 0x3381: case 0x3382: case 0x3383: case 0x3384:
    case 0x3385: case 0x3386: case 0x3387: case 0x3388:
    case 0x3389: case 0x338A: case 0x338B: case 0x338C:
    case 0x338D: case 0x338E: case 0x338F: case 0x3390:
    case 0x3391: case 0x3392: case 0x3393:
        dComIfGs_onEventBit(0x2C01);
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x3395:
        *pMsgNo = 0x3396;
        break;
    case 0x3396:
        if (mpCurrMsg->mSelectNum == 0) {
            *pMsgNo = 0x3397;
        } else {
            *pMsgNo = 0x339A;
        }
        break;
    case 0x3397:
        *pMsgNo = 0x3398;
        break;
    case 0x3398:
        mB70 = 5;
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x3399:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x339A:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x339B:
        *pMsgNo = 0x339C;
        break;
    case 0x339C:
        if (mpCurrMsg->mSelectNum == 0) {
            *pMsgNo = 0x339D;
        } else {
            *pMsgNo = 0x339F;
        }
        break;
    case 0x339D:
        *pMsgNo = 0x339E;
        break;
    case 0x339E:
        mB70 = 6;
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x339F:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x33A0:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x33A1:
        *pMsgNo = 0x33A2;
        break;
    case 0x33A2:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x33A3:
        *pMsgNo = 0x33A4;
        break;
    case 0x33A4:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    case 0x33A5:
        *pMsgNo = 0x33A6;
        break;
    case 0x33A6:
        if (mpCurrMsg->mSelectNum == 0) {
            m06D3 = 1;
            msg_status = fopMsgStts_MSG_ENDS_e;
        } else {
            *pMsgNo = 0x33A7;
        }
        break;
    case 0x33A7:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    default:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    }

    return msg_status;
}

/* 00001214-000013A0       .text lookBack__10daNpc_So_cFv */
void daNpc_So_c::lookBack() {
    cXyz player_eye_pos;
    cXyz* vec_p = NULL;
    s16 target_y = shape_angle.y;
    bool temp = true;

    if (mEventCut.getAttnFlag()) {
        player_eye_pos = dNpc_playerEyePos(m_heapsize.mNpcHIO.m04);
        vec_p = &player_eye_pos;
    }

    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&mB30, m_heapsize.mNpcHIO.mMaxHeadTurnVel, 4, 0x800);
    } else {
        mB30 = 0;
    }

    m_jnt.lookAtTarget(
        &shape_angle.y, vec_p,
        eyePos, target_y,
        mB30, temp
    );
}

/* 000013A0-00001430       .text setAttention__10daNpc_So_cFv */
void daNpc_So_c::setAttention() {
    f32 sinY = cM_ssin(shape_angle.y);
    f32 cosY = cM_scos(shape_angle.y);

    attention_info.position.set(
        current.pos.x + mB08 * sinY,
        current.pos.y + m_heapsize.mNpcHIO.mAttnYOffset + mB00,
        current.pos.z + mB08 * cosY
    );
    eyePos.set(
        current.pos.x + mB08 * sinY,
        current.pos.y + m_heapsize.mNpcHIO.mAttnYOffset + mB00,
        current.pos.z + mB08 * cosY
    );
}

/* 00001430-00001524       .text setAnm__10daNpc_So_cFScb */
void daNpc_So_c::setAnm(signed char i_anmIdx, bool i_morf) {
    static const int a_anm_bcks_tbl[] = {
        SO_BCK_SO_WAIT01,  // 0
        SO_BCK_SO_WAIT01,  // 1: wait
        SO_BCK_SO_SWIM01,  // 2: swim
        SO_BCK_SO_TALK01,  // 3: talk
        SO_BCK_SO_JUMP,    // 4: jump
    };

    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        { 0, -1, 0, 8.0f, 1.0f, 2 },
        { 1, -1, 0, 8.0f, 1.0f, 2 },
        { 2, -1, 0, 8.0f, 1.0f, 2 },
        { 3, -1, 0, 8.0f, 1.0f, 2 },
        { 4, -1, 0, 8.0f, 1.0f, 0 },
    };

    m06D3 = i_anmIdx;
    dLib_bcks_setAnm(m_arc_name, mpMorf, &m06D2, &m06D3, &mB0C, a_anm_bcks_tbl, a_anm_prm_tbl, i_morf);
}

/* 00001524-00001644       .text setAnmSwimSpeed__10daNpc_So_cFv */
void daNpc_So_c::setAnmSwimSpeed() {
    f32 speed_val = m0AFC;
    if (speed_val < 0.0f) {
        speed_val = -speed_val;
    }
    f32 playSpeed = m_heapsize.m0050 + speed_val * m_heapsize.m0058;
    if (playSpeed > m_heapsize.m005C) {
        playSpeed = m_heapsize.m005C;
    }
    mpMorf->setPlaySpeed(playSpeed);

    speedF = m0AFC;
    current.pos.y = dLib_getWaterY(current.pos, mAcch);

    cLib_addCalcAngleS2(&shape_angle.x, m_heapsize.m0066, 4, m_heapsize.m0064);
}

/* 00001644-000016E8       .text setMtx__10daNpc_So_cFv */
void daNpc_So_c::setMtx() {
    f32 sinY = cM_ssin(shape_angle.y);
    f32 cosY = cM_scos(shape_angle.y);

    J3DModel* model = mpMorf->getModel();
    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(
        current.pos.x + mB08 * sinY,
        current.pos.y + mB34 + mB00,
        current.pos.z + mB08 * cosY
    );
    mDoMtx_stack_c::YrotM(shape_angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
}

/* 000016E8-00001718       .text modeWaitInit__10daNpc_So_cFv */
void daNpc_So_c::modeWaitInit() {
    speedF = 0.0f;
    m0AFC = 0.0f;
    offsetAppear();
}

/* 00001718-0000171C       .text modeWait__10daNpc_So_cFv */
void daNpc_So_c::modeWait() {
}

/* 0000171C-0000175C       .text modeHideInit__10daNpc_So_cFv */
void daNpc_So_c::modeHideInit() {
    mBDB = 1;
    offsetDive();
    m0A7C = 0.0f;
}

/* 0000175C-00001778       .text modeHide__10daNpc_So_cFv */
void daNpc_So_c::modeHide() {
    current.pos = m0A80;
}

/* 00001778-00001880       .text modeJumpInit__10daNpc_So_cFv */
void daNpc_So_c::modeJumpInit() {
    current.pos.y = dLib_getWaterY(current.pos, mAcch);
    maxFallSpeed = m_heapsize.m0080;
    speed.y = m_heapsize.m0084;
    mB00 = speed.y;
    gravity = m_heapsize.m0104;
    m0AFC = 0.0f;
    speedF = m0AFC;
    setAnm(4, false);
    offsetSwim();
    fopAcM_seStart(this, JA_SE_CM_SO_JUMP_L, 0);
}

/* 00001880-000019F0       .text modeJump__10daNpc_So_cFv */
void daNpc_So_c::modeJump() {
    f32 waterY = dLib_getWaterY(current.pos, mAcch);

    if (current.pos.y <= waterY) {
        current.pos.y = waterY;
        speed.y = 0.0f;
        gravity = 0.0f;
        m0AFC = 0.0f;
        speedF = 0.0f;
        mB00 = 0.0f;

        fopAcM_seStart(this, JA_SE_CM_SO_LANDING_L, 0);
        fopKyM_createWpillar(&current.pos, m_heapsize.m00D0 * scale.x, m_heapsize.m00CC, 0);

        setAnm(1, false);
        offsetAppear();
        attention_info.flags = 0x200000A;
        mB70 = 1;
        modeProc(PROC_INIT_e, MODE_TALK_e);
    }
}

/* 000019F0-00001A6C       .text modeSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeSwimInit() {
    attention_info.flags = 0x200000A;
    m0A90 = (int)(30.0f + cM_rndF(90.0f));
    setAnm(2, false);
    m_jnt.mbBackBoneLock = 1;
    offsetDive();
}

/* 00001A6C-00001DB8       .text modeSwim__10daNpc_So_cFv */
void daNpc_So_c::modeSwim() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 distXZ = fopAcM_searchActorDistanceXZ(this, player);

    if (distXZ < m_heapsize.m0034 + m_heapsize.m0038) {
        modeProc(PROC_INIT_e, MODE_NEAR_SWIM_e);
        return;
    }

    if (cLib_calcTimer(&m0A90) == 0) {
        modeProc(PROC_INIT_e, MODE_DISAPPEAR_e);
        return;
    }

    cXyz target = m0A80;
    f32 radius = m0A7C;
    if (radius > 0.0f) {
        s16 angle = cM_rndF(65536.0f);
        f32 r = cM_rndF(radius);
        target.x += r * cM_ssin(angle);
        target.z += r * cM_scos(angle);
    }

    cXyz diff = target - current.pos;
    diff.y = 0.0f;
    f32 dist = diff.abs();

    if (dist > m_heapsize.m0054) {
        s16 targetAngle = cLib_targetAngleY(&current.pos, &target);
        cLib_addCalcAngleS2(&shape_angle.y, targetAngle, 8, m_heapsize.m0064);
        cLib_addCalc2(&m0AFC, m_heapsize.m0048, m_heapsize.m00E4, m_heapsize.m00E8);
    } else {
        cLib_addCalc2(&m0AFC, 0.0f, 0.2f, 1.0f);
    }

    setAnmSwimSpeed();
}

/* 00001DB8-00001DFC       .text modeNearSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwimInit() {
    setAnm(2, false);
    offsetDive();
    m_jnt.mbBackBoneLock = 1;
}

/* 00001DFC-00002144       .text modeNearSwim__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwim() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 distXZ = fopAcM_searchActorDistanceXZ(this, player);

    if (distXZ > m_heapsize.m0034 + m_heapsize.m003C) {
        modeProc(PROC_INIT_e, MODE_SWIM_e);
        return;
    }

    daShip_c* ship = dComIfGp_getShipActor();
    cXyz targetPos;
    if (ship != NULL) {
        s16 shipAngle = ship->shape_angle.y + 0x4000;
        targetPos.x = ship->current.pos.x + -m_heapsize.m0088 * cM_ssin(shipAngle);
        targetPos.y = ship->current.pos.y;
        targetPos.z = ship->current.pos.z + -m_heapsize.m0088 * cM_scos(shipAngle);
    } else {
        targetPos = player->current.pos;
    }

    cXyz diff = targetPos - current.pos;
    diff.y = 0.0f;
    f32 dist = diff.abs();

    s16 targetAngle = cLib_targetAngleY(&current.pos, &targetPos);
    cLib_addCalcAngleS2(&shape_angle.y, targetAngle, 8, m_heapsize.m0064);

    if (dist > m_heapsize.m0054) {
        cLib_addCalc2(&m0AFC, m_heapsize.m0048, m_heapsize.m00E4, m_heapsize.m00E8);
    } else {
        cLib_addCalc2(&m0AFC, 0.0f, 0.2f, 1.0f);
        if (dist < m_heapsize.m0060) {
            m0AFC = 0.0f;
            speedF = 0.0f;
            if (!dComIfGs_isEventBit(0x901)) {
                modeProc(PROC_INIT_e, MODE_EVENT_FIRST_WAIT_e);
            } else {
                modeProc(PROC_INIT_e, MODE_JUMP_e);
            }
            return;
        }
    }

    setAnmSwimSpeed();
}

/* 00002144-0000217C       .text modeEventFirstWaitInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstWaitInit() {
    m0A90 = 150;
    m0AFC = 0.0f;
    speedF = 0.0f;
    offsetDive();
}

/* 0000217C-000022D0       .text modeEventFirstWait__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstWait() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 distXZ = fopAcM_searchActorDistanceXZ(this, player);
    s16 angY = cLib_targetAngleY(&current.pos, &player->current.pos);

    if (distXZ > m_heapsize.m0034 + m_heapsize.m003C) {
        modeProc(PROC_INIT_e, MODE_SWIM_e);
        return;
    }

    cLib_addCalcAngleS2(&shape_angle.y, angY, 8, m_heapsize.m0064);
    current.pos.y = dLib_getWaterY(current.pos, mAcch);

    if (cLib_calcTimer(&m0A90) == 0) {
        modeProc(PROC_INIT_e, MODE_JUMP_e);
    }
}

/* 000022D0-00002314       .text modeEventFirstInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstInit() {
    offsetSwim();
    m0AFC = 0.0f;
    speedF = 0.0f;
    m_jnt.mbBackBoneLock = 0;
}

/* 00002314-000023C8       .text modeEventFirst__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirst() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        dComIfG_inf_c* pInfo = &g_dComIfG_gameInfo;
        if (pInfo->play.getEvtManager().endCheckOld("SO_1ST_MEET")) {
            ((u16*)pInfo)[0x52C0 / 2] |= 0x8;
            mB70 = 1;
            modeProc(PROC_INIT_e, MODE_TALK_e);
            attention_info.flags = 0x200000A;
        }
    } else {
        mB70 = 3;
    }
}

/* 000023C8-0000240C       .text modeEventFirstEndInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstEndInit() {
    offsetAppear();
    m0AFC = 0.0f;
    speedF = 0.0f;
    m_jnt.mbBackBoneLock = 0;
}

/* 0000240C-000024C0       .text modeEventFirstEnd__10daNpc_So_cFv */
void daNpc_So_c::modeEventFirstEnd() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        dComIfG_inf_c* pInfo = &g_dComIfG_gameInfo;
        if (pInfo->play.getEvtManager().endCheckOld("SO_1ST_MEET_END")) {
            ((u16*)pInfo)[0x52C0 / 2] |= 0x8;
            modeProc(PROC_INIT_e, MODE_DISAPPEAR_e);
        }
    } else {
        if (talk(1) == 0x12) {
            mB70 = 4;
        }
    }
}

/* 000024C0-00002504       .text modeEventEsaInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventEsaInit() {
    offsetSwim();
    m0AFC = 0.0f;
    speedF = 0.0f;
    m_jnt.mbBackBoneLock = 0;
}

/* 00002504-00002594       .text modeEventEsa__10daNpc_So_cFv */
void daNpc_So_c::modeEventEsa() {
    if (!mEventCut.cutProc()) {
        cutProc();
    }

    dComIfG_inf_c* pInfo = &g_dComIfG_gameInfo;
    if (pInfo->play.getEvtManager().endCheck(mBDC)) {
        ((u16*)pInfo)[0x52C0 / 2] |= 0x8;
        mBDC = -1;
        mB70 = 1;
        modeProc(PROC_INIT_e, MODE_TALK_e);
    }
}

/* 00002594-000025B0       .text modeEventMapopenInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventMapopenInit() {
    m0AFC = 0.0f;
    speedF = 0.0f;
    m_jnt.mbBackBoneLock = 0;
}

/* 000025B0-00002670       .text modeEventMapopen__10daNpc_So_cFv */
void daNpc_So_c::modeEventMapopen() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        dComIfG_inf_c* pInfo = &g_dComIfG_gameInfo;
        if (pInfo->play.getEvtManager().endCheckOld("SO_MAPOPEN")) {
            ((u16*)pInfo)[0x52C0 / 2] |= 0x8;
            mB70 = 1;
            mBD8 = 1;
            modeProc(PROC_INIT_e, MODE_TALK_e);
        }
    } else {
        if (talk(1) == 0x12) {
            mB70 = 5;
        }
    }
}

/* 00002670-000026B4       .text modeEventBowInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventBowInit() {
    offsetSwim();
    m0AFC = 0.0f;
    speedF = 0.0f;
    m_jnt.mbBackBoneLock = 0;
}

/* 000026B4-000027F8       .text modeEventBow__10daNpc_So_cFv */
void daNpc_So_c::modeEventBow() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        dComIfG_inf_c* pInfo = &g_dComIfG_gameInfo;
        if (pInfo->play.getEvtManager().endCheckOld("SO_BOW")) {
            mB0C = 1;
            ((u16*)pInfo)[0x52C0 / 2] |= 0x8;
            mBDB = 0;
            dComIfGs_onEventBit(0x3A10);

            int camID = dComIfGp_getPlayerCameraID(0);
            camera_class* cam = (camera_class*)dComIfGp_getCamera(camID);
            cam->mCamera.Reset(mBCC, mBC0);
            cam->mCamera.Start();

            mB70 = 1;
            modeProc(PROC_INIT_e, MODE_TALK_e);
        }
    } else {
        if (talk(1) == 0x12) {
            mB70 = 6;
        }
    }
}

/* 000027F8-0000283C       .text modeTalkInit__10daNpc_So_cFv */
void daNpc_So_c::modeTalkInit() {
    offsetAppear();
    setAnm(3, false);
    m_jnt.mbBackBoneLock = 0;
}

/* 0000283C-0000289C       .text modeTalk__10daNpc_So_cFv */
void daNpc_So_c::modeTalk() {
    if (talk(1) == 0x12) {
        ((u16*)&g_dComIfG_gameInfo)[0x52C0 / 2] |= 0x8;
        modeProc(PROC_INIT_e, MODE_DISAPPEAR_e);
    }
}

/* 0000289C-0000296C       .text modeDisappearInit__10daNpc_So_cFv */
void daNpc_So_c::modeDisappearInit() {
    if (!dComIfGs_isEventBit(0x901)) {
        dComIfGs_onEventBit(0x901);
    }

    offsetDive();

    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::getInterface()->seStart(
        0x593B, &eyePos, 0, reverb,
        m_heapsize.m00A8, m_heapsize.m00A8,
        m_heapsize.m00C8, m_heapsize.m00C8, 0
    );

    fopKyM_createWpillar(&current.pos, m_heapsize.m00D0 * scale.x, m_heapsize.m00CC, 0);

    m_jnt.mbBackBoneLock = 0;
}

/* 0000296C-00002A90       .text modeDisappear__10daNpc_So_cFv */
void daNpc_So_c::modeDisappear() {
    cLib_addCalc2(&m0AFC, 0.0f, 0.2f, 1.0f);
    speedF = m0AFC;
    current.pos.y = dLib_getWaterY(current.pos, mAcch);

    if (std::abs(mB34 - mB38) < 10.0f) {
        m0AFC = 0.0f;
        speedF = 0.0f;
        gravity = 0.0f;
        speed.y = 0.0f;
        attention_info.flags = 0;
        modeProc(PROC_INIT_e, MODE_HIDE_e);
    }
}

/* 00002A90-00002B60       .text modeDebugInit__10daNpc_So_cFv */
void daNpc_So_c::modeDebugInit() {
    speedF = 0.0f;
    m0AFC = 0.0f;
    setAnm(1, false);

    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz pos = player->current.pos;

    s16 angle = player->shape_angle.y;
    pos.x += 100.0f * cM_scos(angle);
    pos.z += 100.0f * cM_ssin(angle);

    current.pos = pos;
    offsetAppear();
}

/* 00002B60-00002B64       .text modeDebug__10daNpc_So_cFv */
void daNpc_So_c::modeDebug() {
}

/* 00002B64-00002B68       .text modeGetRupeeInit__10daNpc_So_cFv */
void daNpc_So_c::modeGetRupeeInit() {
}

/* 00002B68-00002C6C       .text modeGetRupee__10daNpc_So_cFv */
void daNpc_So_c::modeGetRupee() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        dComIfG_inf_c* pInfo = &g_dComIfG_gameInfo;
        if (pInfo->play.getEvtManager().endCheckOld("SO_GET_RUPEE")) {
            ((u16*)pInfo)[0x52C0 / 2] |= 0x8;
            mB70 = 1;
            mBD9 = 1;
            modeProc(PROC_INIT_e, MODE_TALK_e);
        }
    } else {
        if (talk(1) == 0x12) {
            if (REG12_S(9) != 0) {
                ((u16*)&g_dComIfG_gameInfo)[0x52C0 / 2] |= 0x8;
            }
            fopAc_ac_c* ship = (fopAc_ac_c*)((u32*)&g_dComIfG_gameInfo)[0x5B44 / 4];
            ((u16*)((u8*)ship + 0x304))[0] = 2;
            ((u32*)((u8*)ship + 0x314))[0] = 1;
            mB70 = 7;
        }
    }
}

/* 00002C6C-00002CC0       .text modeEventTriForceInit__10daNpc_So_cFv */
void daNpc_So_c::modeEventTriForceInit() {
    m0AFC = 0.0f;
    speedF = 0.0f;
    m_jnt.mbBackBoneLock = 0;
    offsetAppear();
    setAnm(1, false);
}

/* 00002CC0-00002D80       .text modeEventTriForce__10daNpc_So_cFv */
void daNpc_So_c::modeEventTriForce() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (!mEventCut.cutProc()) {
            cutProc();
        }

        dComIfG_inf_c* pInfo = &g_dComIfG_gameInfo;
        if (pInfo->play.getEvtManager().endCheckOld("SO_TRIFORCE_CHECK")) {
            attention_info.flags = 0x200000A;
            ((u16*)pInfo)[0x52C0 / 2] |= 0x8;
            modeProc(PROC_INIT_e, MODE_DISAPPEAR_e);
            dComIfGs_onEventBit(0x3A20);
        }
    } else {
        mB70 = 8;
    }
}

/* 00002D80-00003110       .text modeProc__10daNpc_So_cFQ210daNpc_So_c6Proc_ei */
void daNpc_So_c::modeProc(daNpc_So_c::Proc_e proc, int newMode) {
    typedef void (daNpc_So_c::*mode_func_t)(void);
    struct mode_entry_t {
        mode_func_t init;
        mode_func_t run;
        const char* name;
    };

    static mode_entry_t mode_tbl[] = {
        { &daNpc_So_c::modeWaitInit, &daNpc_So_c::modeWait, NULL },
        { &daNpc_So_c::modeHideInit, &daNpc_So_c::modeHide, NULL },
        { &daNpc_So_c::modeJumpInit, &daNpc_So_c::modeJump, NULL },
        { &daNpc_So_c::modeSwimInit, &daNpc_So_c::modeSwim, NULL },
        { &daNpc_So_c::modeNearSwimInit, &daNpc_So_c::modeNearSwim, NULL },
        { &daNpc_So_c::modeEventFirstWaitInit, &daNpc_So_c::modeEventFirstWait, NULL },
        { &daNpc_So_c::modeEventFirstInit, &daNpc_So_c::modeEventFirst, NULL },
        { &daNpc_So_c::modeEventFirstEndInit, &daNpc_So_c::modeEventFirstEnd, NULL },
        { &daNpc_So_c::modeEventEsaInit, &daNpc_So_c::modeEventEsa, NULL },
        { &daNpc_So_c::modeEventMapopenInit, &daNpc_So_c::modeEventMapopen, NULL },
        { &daNpc_So_c::modeEventBowInit, &daNpc_So_c::modeEventBow, NULL },
        { &daNpc_So_c::modeTalkInit, &daNpc_So_c::modeTalk, NULL },
        { &daNpc_So_c::modeDisappearInit, &daNpc_So_c::modeDisappear, NULL },
        { &daNpc_So_c::modeDebugInit, &daNpc_So_c::modeDebug, NULL },
        { &daNpc_So_c::modeGetRupeeInit, &daNpc_So_c::modeGetRupee, NULL },
        { &daNpc_So_c::modeEventTriForceInit, &daNpc_So_c::modeEventTriForce, NULL },
    };

    if (proc == PROC_INIT_e) {
        mCurMode = newMode;
        (this->*mode_tbl[mCurMode].init)();
    } else if (proc == PROC_EXEC_e) {
        (this->*mode_tbl[mCurMode].run)();
    }
}

/* 00003110-00003264       .text eventOrder__10daNpc_So_cFv */
void daNpc_So_c::eventOrder() {
    if (mB70 == 1 || mB70 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mB70 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mB70 == 3) {
        fopAcM_orderOtherEvent2(this, "SO_1ST_MEET", 0);
    } else if (mB70 == 4) {
        fopAcM_orderOtherEvent2(this, "SO_1ST_MEET_END", 0);
    } else if (mB70 == 5) {
        fopAcM_orderOtherEvent2(this, "SO_MAPOPEN", 0);
    } else if (mB70 == 6) {
        fopAcM_orderOtherEvent2(this, "SO_BOW", 0);
    } else if (mB70 == 7) {
        fopAcM_orderOtherEvent2(this, "SO_GET_RUPEE", 0);
    } else if (mB70 == 8) {
        fopAcM_orderOtherEvent2(this, "SO_TRIFORCE_CHECK", 0);
    }
}

/* 00003264-0000330C       .text checkOrder__10daNpc_So_cFv */
void daNpc_So_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (mB70 >= 3) {
            modeProc(PROC_INIT_e, MODE_EVENT_FIRST_e + (mB70 - 3));
            mB70 = 0;
        }
    } else if (eventInfo.checkCommandTalk()) {
        if (mB70 == 1 || mB70 == 2) {
            mB70 = 0;
            modeProc(PROC_INIT_e, MODE_TALK_e);
        }
    }
}

/* 0000330C-000033F4       .text setScale__10daNpc_So_cFv */
void daNpc_So_c::setScale() {
    f32 targetScale = m_heapsize.m00D4;
    cLib_addCalc2(&scale.x, targetScale, m_heapsize.m00D8, m_heapsize.m00DC);
    scale.z = scale.x;
    scale.y = scale.x;
}

/* 000033F4-00003844       .text _execute__10daNpc_So_cFv */
bool daNpc_So_c::_execute() {
    m_jnt.setParam(
        m_heapsize.mNpcHIO.mMaxBackboneX,
        m_heapsize.mNpcHIO.mMaxBackboneY,
        m_heapsize.mNpcHIO.mMinBackboneX,
        m_heapsize.mNpcHIO.mMinBackboneY,
        m_heapsize.mNpcHIO.mMaxHeadX,
        m_heapsize.mNpcHIO.mMaxHeadY,
        m_heapsize.mNpcHIO.mMinHeadX,
        m_heapsize.mNpcHIO.mMinHeadY,
        m_heapsize.mNpcHIO.mMaxTurnStep
    );

    if (REG12_S(0) != 0) {
        modeProcInit(REG12_S(0) - 1);
        REG12_S(0) = 0;
    }

    if (REG12_S(1) != 0) {
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        current.pos = player->current.pos;
        current.pos.x += 200.0f * cM_ssin(player->shape_angle.y);
        current.pos.z += 200.0f * cM_scos(player->shape_angle.y);
        current.pos.y = dLib_getWaterY(current.pos, mAcch);
        REG12_S(1) = 0;
    }

    if (mBDA != 0) {
        if (mB84 != 0) {
            mB84 = 0;
            mB7C++;
        }
    }

    checkOrder();
    modeProc(PROC_EXEC_e, mCurMode);
    lookBack();

    s8 roomNo = fopAcM_GetRoomNo(this);
    mpMorf->play(NULL, 0, dComIfGp_getReverb(roomNo));
    mBtpAnm.play();
    mpMorf->calc();

    checkTgHit();

    hudeDraw();
    setScale();

    fopAcM_posMoveF(this, mStts.GetCCMoveP());

    mAcch.CrrPos(*dComIfG_Bgsp());

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);

    setAttention();
    setMtx();

    if (mpModel != NULL) {
        J3DModel* model = mpMorf->getModel();
        MtxP jointMtx = model->getAnmMtx(0);
        mDoMtx_stack_c::copy(jointMtx);
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, 0);
        mDoMtx_stack_c::transM(0.0f, 0.0f, 0.0f);
        mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpModel->calc();
    }

    // JntHit_set(mpJntHit2, &m_heapsize.mJntHitHIO); // Not called in original binary

    mStts.Move();

    f32 sinY = cM_ssin(shape_angle.y);
    f32 cosY = cM_scos(shape_angle.y);
    cXyz sphPos(
        current.pos.x + mB08 * sinY,
        current.pos.y + mB00,
        current.pos.z + mB08 * cosY
    );
    mSph.SetC(sphPos);
    mSph.SetR(m_heapsize.m0054);
    dComIfG_Ccsp()->Set(&mSph);

    eventOrder();

    return true;
}

/* 00003844-000038E0       .text debugDraw__10daNpc_So_cFv */
void daNpc_So_c::debugDraw() {
}

/* 000038E0-00003954       .text hudeDraw__10daNpc_So_cFv */
void daNpc_So_c::hudeDraw() {
    cLib_addCalc2(&mB34, mB38, m_heapsize.m00EC, m_heapsize.m00F0);
    cLib_addCalc2(&mB00, mB3C, m_heapsize.m0100, m_heapsize.m0104);
    cLib_addCalc2(&mB08, mB40, m_heapsize.m010C, m_heapsize.m0110);
}

/* 00003954-00003B00       .text _draw__10daNpc_So_cFv */
bool daNpc_So_c::_draw() {
    if (mBDB != 0) {
        return true;
    }

    J3DModel* model_p = mpMorf->getModel();
    J3DModelData* model_data_p = model_p->getModelData();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model_p, &tevStr);

    mBtpAnm.entry(model_data_p);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data_p);

    if (mpModel != NULL && mEquipNecklace != 0) {
        g_env_light.setLightTevColorType(mpModel, &tevStr);
        mDoExt_modelUpdateDL(mpModel);
    }

    cXyz shadow_pos(
        current.pos.x,
        current.pos.y + 120.0f,
        current.pos.z
    );

    f32 ground_y = mAcch.GetGroundH();
    m06D8 = dComIfGd_setShadow(
        m06D8, 1, model_p,
        &shadow_pos, 800.0f, 20.0f,
        current.pos.y, ground_y,
        mAcch.m_gnd, &tevStr
    );

    dSnap_RegistFig(DSNAP_TYPE_UNK53, this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);

    debugDraw();

    return true;
}

/* 00003B00-00003DF8       .text createInit__10daNpc_So_cFv */
void daNpc_So_c::createInit() {
    getArg();

    fopAcIt_Judge((fopAcIt_JudgeFunc)searchTagSo_CB, this);

    mEventCut.setActorInfo2("So", this);
    mEventCut.setJntCtrlPtr(&m_jnt);

    attention_info.flags = 0x200000A;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;

    eventInfo.setXyCheckCB(daNpc_So_XyCheckCB);
    eventInfo.setXyEventCB(daNpc_So_XyEventCB);

    gravity = 0.0f;
    maxFallSpeed = 0.0f;
    mB0C = 0;
    mB70 = 0;
    mBD8 = 0;
    mBD9 = 0;
    mBDA = 0;
    mBDB = 0;
    m06D2 = 0;
    m06D3 = 0;
    m0AFC = 0.0f;
    mB00 = 0.0f;
    field_0xB04 = 0.0f;
    mB08 = 0.0f;
    mB34 = 0.0f;
    mB38 = 0.0f;
    mB3C = 0.0f;
    mB40 = 0.0f;
    mB84 = 0;
    mB74 = 0;
    mB78 = 0;
    mB7C = 0;
    mB80 = 0;
    mStaffId = -1;
    mEquipNecklace = 0;
    m0A79 = (u8)(fopAcM_GetParam(this) >> 8);
    m0BDE = 0;
    mBDC = -1;

    shape_angle = current.angle;

    mStts.Init(0xFF, 0xFF, this);
    mSph.SetStts(&mStts);
    mSph.Set(m_sph_src);

    mAcchCir.SetWall(30.0f, 40.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));

    current.pos.y = dLib_getWaterY(current.pos, mAcch);

    m_jnt.setParam(
        m_heapsize.mNpcHIO.mMaxBackboneX,
        m_heapsize.mNpcHIO.mMaxBackboneY,
        m_heapsize.mNpcHIO.mMinBackboneX,
        m_heapsize.mNpcHIO.mMinBackboneY,
        m_heapsize.mNpcHIO.mMaxHeadX,
        m_heapsize.mNpcHIO.mMaxHeadY,
        m_heapsize.mNpcHIO.mMinHeadX,
        m_heapsize.mNpcHIO.mMinHeadY,
        m_heapsize.mNpcHIO.mMaxTurnStep
    );

    if (!dComIfGs_isEventBit(0x901)) {
        modeProc(PROC_INIT_e, MODE_SWIM_e);
    } else {
        modeProc(PROC_INIT_e, MODE_HIDE_e);
    }

    setMtx();

    fopAcM_setCullSizeBox(this, -100.0f, -100.0f, -100.0f, 100.0f, 200.0f, 100.0f);
}

/* 00003DF8-00003E24       .text getArg__10daNpc_So_cFv */
void daNpc_So_c::getArg() {
    m06D0 = home.angle.x;
    if (m06D0 == 0xFFFF || m06D0 == 0) {
        m06D0 = 1;
    }
}

/* 00003E24-00003F38       .text _create__10daNpc_So_cFv */
cPhs_State daNpc_So_c::_create() {
    fopAcM_SetupActor(this, daNpc_So_c);

    cPhs_State state = dComIfG_resLoad(&mPhs, m_arc_name);
    if (state == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, createHeap_CB, 0)) {
            return cPhs_ERROR_e;
        }
        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(this, -100.0f, -50.0f, -100.0f, 100.0f, 100.0f, 100.0f);
        createInit();
    }
    return state;
}

/* 000046E4-00004754       .text _delete__10daNpc_So_cFv */
bool daNpc_So_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);
    return true;
}

/* 00004754-00004774       .text daNpc_SoCreate__FPv */
static cPhs_State daNpc_SoCreate(void* i_this) {
    return ((daNpc_So_c*)i_this)->_create();
}

/* 00004774-00004798       .text daNpc_SoDelete__FPv */
static BOOL daNpc_SoDelete(void* i_this) {
    return ((daNpc_So_c*)i_this)->_delete();
}

/* 00004798-000047BC       .text daNpc_SoExecute__FPv */
static BOOL daNpc_SoExecute(void* i_this) {
    return ((daNpc_So_c*)i_this)->_execute();
}

/* 000047BC-000047E0       .text daNpc_SoDraw__FPv */
static BOOL daNpc_SoDraw(void* i_this) {
    return ((daNpc_So_c*)i_this)->_draw();
}

/* 000047E0-000047E8       .text daNpc_SoIsDelete__FPv */
static BOOL daNpc_SoIsDelete(void*) {
    return TRUE;
}

#include "d/actor/d_a_npc_so_cut.inc"
#include "d/d_cc_d.h"

const dCcD_SrcSph daNpc_So_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_UNK8 & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_NoCrr_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
    }},
};


static actor_method_class daNpc_SoMethodTable = {
    (process_method_func)daNpc_SoCreate,
    (process_method_func)daNpc_SoDelete,
    (process_method_func)daNpc_SoExecute,
    (process_method_func)daNpc_SoIsDelete,
    (process_method_func)daNpc_SoDraw,
};

actor_process_profile_definition g_profile_NPC_SO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_SO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_So_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_SO,
    /* Actor SubMtd */ &daNpc_SoMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
