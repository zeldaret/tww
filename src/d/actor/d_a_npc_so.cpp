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
#include "d/d_item_data.h"
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
#include "JSystem/JUtility/JUTAssert.h"

const u32 daNpc_So_c::m_heapsize = 0x1C00;
const char daNpc_So_c::m_arc_name[] = "So";

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

static Vec cyl_offset_B[] = {
    {15.0f, 0.0f, 0.0f},
    {-15.0f, 0.0f, 0.0f},
};

static __jnt_hit_data_c search_data[] = {
    {0, 4, 2.0f, &cyl_offset_B[0]},
    {0, 8, 2.0f, &cyl_offset_B[0]},
};

/* 000000EC-000002A4       .text __ct__14daNpc_So_HIO_cFv */
daNpc_So_HIO_c::daNpc_So_HIO_c() {
    field_0x2c[0] = 0;
    field_0x2c[1] = 0;
    field_0x2c[2] = 0;
    field_0x2c[3] = 0;
    field_0x2c[4] = 0;
    field_0x2c[5] = 0;

    m0034 = 3.0f;
    m0038 = 0.9f;
    m003C = 100.0f;
    m0040 = 2000.0f;
    m0054 = 20000.0f;
    m005C = 30.0f;
    m0044 = 0.7f;
    m0048 = 2000.0f;
    m004C = 2.0f;
    m0050 = 150.0f;
    m0064 = 8000;
    m0066 = 4000;
    m0068 = -8000;
    m006A = -4000;
    m006C = 10.0f;

    mNpcHIO.m04 = -33.0f;
    mNpcHIO.mMaxHeadX = 0x1FFE;
    mNpcHIO.mMaxHeadY = 0x1000;
    mNpcHIO.mMaxBackboneX = 0x1000;
    mNpcHIO.mMaxBackboneY = 0x2000;
    mNpcHIO.mMinHeadX = -0xBB8;
    mNpcHIO.mMinHeadY = -0x1000;
    mNpcHIO.mMinBackboneX = -0x1000;
    mNpcHIO.mMinBackboneY = -0x2000;
    mNpcHIO.mMaxTurnStep = 0x250;
    mNpcHIO.mMaxHeadTurnVel = 0x150;
    mNpcHIO.mAttnYOffset = 50.0f;
    mNpcHIO.mMaxAttnAngleY = 0x7FFF;
    mNpcHIO.m22 = 0;
    mNpcHIO.mMaxAttnDistXZ = 400.0f;

    m0058 = 250.0f;
    m0060 = 700.0f;
    m0070 = 600.0f;
    m0074 = 300.0f;
    m0078 = 100.0f;
    m007C = 5;
    m0080 = -1.4f;
    m0084 = 18.0f;
    m0088 = 120.0f;
    m008C = 300.0f;
    m0090 = 15.0f;
    m0094 = 0;
}

static daNpc_So_HIO_c l_HIO;

/* 000002A4-000002D0       .text searchEsa_CB__FPvPv */
void searchEsa_CB(void* i_actor, void* i_data) {
    ((daNpc_So_c*)i_data)->_searchEsa((fopAc_ac_c*)i_actor);
}

/* 000002D0-000002F8       .text _searchEsa__10daNpc_So_cFP10fopAc_ac_c */
fopAc_ac_c* daNpc_So_c::_searchEsa(fopAc_ac_c* i_actor) {
    if (fopAcM_GetName(i_actor) == PROC_ESA &&
        *(u8*)((u32)i_actor + 0x298) == 0) {
        return i_actor;
    }
    return NULL;
}

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

    mDoMtx_stack_c::copy(i_model->getAnmMtx(jnt_no));

    if (jnt_no == m_jnt.getHeadJntNum()) {
        cXyz zero(0.0f, 0.0f, 0.0f);
        cXyz eyeOffset(24.0f, -16.0f, 0.0f);
        mDoMtx_stack_c::multVec(&zero, &mB60);
        mDoMtx_YrotM(mDoMtx_stack_c::now, m_jnt.getHead_y());
        mDoMtx_ZrotM(mDoMtx_stack_c::now, m_jnt.getHead_x());
        mDoMtx_stack_c::multVec(&eyeOffset, &mB54);
    } else if (jnt_no == m_jnt.getBackboneJntNum()) {
        mDoMtx_XrotM(mDoMtx_stack_c::now, m_jnt.getBackbone_y());
        mDoMtx_ZrotM(mDoMtx_stack_c::now, m_jnt.getBackbone_x());
    }

    mDoMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_model->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
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
    mBDC = dComIfGp_evmng_getEventIdx("SO_ESA_XY");
    return mBDC;
}

/* 000006EC-0000070C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daNpc_So_c*)i_this)->_createHeap();
}

/* 00000800-00000B14       .text _createHeap__10daNpc_So_cFv */
int daNpc_So_c::_createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, SO_BDL_SO);
    JUT_ASSERT(0x1fd, modelData != 0);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        NULL,
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x80000, 0x11020022
    );

    if (!mpMorf || !mpMorf->getModel()) {
        return FALSE;
    }

    mpMorf->getModel()->setUserArea((u32)this);

    J3DAnmTexPattern* btp = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arc_name, SO_BTP_SO);
    JUT_ASSERT(0x210, btp != 0);

    if (!mBtpAnm.init(modelData, btp, TRUE, 0, 1.0f, 0, -1, false, FALSE)) {
        return FALSE;
    }

    m_jnt.setHeadJntNum(0xb);
    JUT_ASSERT(0x215, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(0x1);
    JUT_ASSERT(0x217, m_jnt.getBackboneJntNum() >= 0);

    modelData->getJointNodePointer(0xb)->setCallBack(nodeControl_CB);
    modelData->getJointNodePointer(1)->setCallBack(nodeControl_CB);

    modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, SO_BDL_SO_FUDE);
    JUT_ASSERT(0x221, modelData != 0);
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (!mpModel) {
        return FALSE;
    }

    return jntHitCreateHeap();
}

/* 00000B14-00000B78 000A20 0064+00 1/1 0/0 0/0 .text            jntHitCreateHeap__10daNpc_So_cFv */
bool daNpc_So_c::jntHitCreateHeap() {
    mpJntHit2 = JntHit_create(mpMorf->getModel(), search_data, 2);
    if (mpJntHit2 == NULL) {
        return false;
    }
    jntHit = mpJntHit2;
    return true;
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
            1.0f, 1.0f,
            -1.0f, -1.0f, 0
        );
    }

    fopAcM_monsSeStart(this, JA_SE_CV_SO_DAMAGE, 0);

    dComIfGp_particle_set(0x10, hitPos);

    f32 scaleVal = 2.0f;
    cXyz scaleVec(scaleVal, scaleVal, scaleVal);
    dComIfGp_particle_set(0x0F, hitPos, &player->shape_angle, &scaleVec);

    mDoAud_zelAudio_c::getInterface()->seStart(
        JA_SE_LK_LAST_HIT, &eyePos, 0,
        dComIfGp_getReverb(fopAcM_GetRoomNo(this)),
        1.0f, 1.0f,
        -1.0f, -1.0f, 0
    );

    return TRUE;
}

/* 00000C8C-00000CB0       .text offsetZero__10daNpc_So_cFv */
void daNpc_So_c::offsetZero() {
    mB40 = 0.1f;
    mB3C = 20.0f;
    mB38 = -1.0f;
}

/* 00000CB0-00000CD4       .text offsetDive__10daNpc_So_cFv */
void daNpc_So_c::offsetDive() {
    mB40 = 0.3f;
    mB3C = 10.0f;
    mB38 = -150.0f;
}

/* 00000CD4-00000CF8       .text offsetSwim__10daNpc_So_cFv */
void daNpc_So_c::offsetSwim() {
    mB40 = 0.3f;
    mB3C = 10.0f;
    mB38 = -40.0f;
}

/* 00000CF8-00000D1C       .text offsetAppear__10daNpc_So_cFv */
void daNpc_So_c::offsetAppear() {
    mB40 = 0.4f;
    mB3C = 22.0f;
    mB38 = 110.0f;
}

/* 00000D1C-00000E40       .text getMsg__10daNpc_So_cFv */
u32 daNpc_So_c::getMsg() {
    u32 msgNo;

    if (mB0C != 0) {
        if (l_HIO.field_0x2c[2] != 0 || mB7C >= 10) {
            if (mBD9 != 0) {
                msgNo = 0x32E2;
            } else {
                msgNo = 0x32DD;
            }
        } else {
            if (mB7C == 0) {
                msgNo = 0x32E1;
            } else if (mB7C == 1) {
                msgNo = 0x32E0;
            } else {
                dComIfGp_setMessageCountNumber((u16)mB7C);
                msgNo = 0x32DF;
            }
        }
    } else {
        if (!dComIfGs_isEventBit(0x901) &&
            strcmp(dComIfGp_getStartStageName(), "sea") == 0 &&
            current.roomNo == 0xd)
        {
            if (mBD8 != 0) {
                msgNo = (u32)(s32)m06D0;
            } else {
                msgNo = 0x32CA;
            }
        } else {
            if (mBD8 != 0) {
                msgNo = (u32)(s32)m06D0;
            } else {
                msgNo = 0x32D0;
            }
        }
    }

    return msgNo;
}

/* 00000E40-00001214       .text next_msgStatus__10daNpc_So_cFPUl */
u16 daNpc_So_c::next_msgStatus(unsigned long* pMsgNo) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;

    if (*pMsgNo == (u32)(s32)m06D0) {
        if (mBD8 == 0) {
            if (!dComIfGs_isEventBit(0x901) &&
                strcmp(dComIfGp_getStartStageName(), "sea") == 0 &&
                current.roomNo == 0xd)
            {
                *pMsgNo = 0x32CE;
            } else {
                *pMsgNo = 0x32D2;
            }
        } else {
            *pMsgNo = 0x32D6;
        }
        return fopMsgStts_MSG_CONTINUES_e;
    }

    switch (*pMsgNo) {
    case 0x32CA:
        *pMsgNo = 0x32CB;
        break;
    case 0x32CB:
        *pMsgNo = 0x32CC;
        break;
    case 0x32CC:
        *pMsgNo = 0x32CD;
        break;
    case 0x32CD:
    case 0x32D1:
        msg_status = fopMsgStts_MSG_ENDS_e;
        modeProc(PROC_INIT_e, MODE_EVENT_ESA_e);
        break;
    case 0x32CE:
        msg_status = fopMsgStts_MSG_ENDS_e;
        modeProc(PROC_INIT_e, MODE_EVENT_FIRST_END_e);
        break;
    case 0x32D0:
        if (g_dComIfG_gameInfo.save.getPlayer().getMap().isSaveArriveGrid(current.roomNo - 1) ||
            g_dComIfG_gameInfo.save.getPlayer().getPlayerStatusB().field_0x17 != 0)
        {
            *pMsgNo = 0x32D4;
        } else {
            *pMsgNo = 0x32D1;
        }
        break;
    case 0x32D2:
        *pMsgNo = 0x32D3;
        break;
    case 0x32D4:
        *pMsgNo = (u32)(s32)m06D0;
        break;
    case 0x32D6:
        fopAcIt_Judge((fopAcIt_JudgeFunc)searchEsa_CB, this);
        if (g_dComIfG_gameInfo.save.getPlayer().getPlayerReturnPlace().getName()[0] != 0 || mBAE != 0) {
            if (g_dComIfG_gameInfo.save.getPlayer().getItem().getItem(dInvSlot_BOW_e) != 0xFF &&
                dComIfG_getTimerPtr() == NULL)
            {
                if (!dComIfGs_isEventBit(0x3A10)) {
                    *pMsgNo = 0x32D8;
                } else {
                    *pMsgNo = 0x32DC;
                }
            } else {
                *pMsgNo = 0x32D7;
            }
        } else {
            *pMsgNo = 0x32D7;
        }
        break;
    case 0x32D8:
        if (mpCurrMsg->mSelectNum == 0) {
            *pMsgNo = 0x32DA;
        } else {
            *pMsgNo = 0x32D9;
        }
        break;
    case 0x32D9:
        *pMsgNo = 0x32D7;
        break;
    case 0x32DA:
        *pMsgNo = 0x32DB;
        break;
    case 0x32DB:
        msg_status = fopMsgStts_MSG_ENDS_e;
        modeProc(PROC_INIT_e, MODE_EVENT_BOW_e);
        break;
    case 0x32DC:
        if (mpCurrMsg->mSelectNum == 0) {
            *pMsgNo = 0x32DB;
        } else {
            *pMsgNo = 0x32D9;
        }
        break;
    case 0x32DD:
        *pMsgNo = 0x32DE;
        break;
    case 0x32DE:
        msg_status = fopMsgStts_MSG_ENDS_e;
        modeProc(PROC_INIT_e, MODE_GET_RUPEE_e);
        break;
    case 0x32DF:
    case 0x32E0:
        dComIfGp_setItemRupeeCount(mB7C * 10);
        *pMsgNo = 0x32E2;
        break;
    case 0x32E1:
        *pMsgNo = 0x32E2;
        break;
    case 0x0633:
        if (dComIfGs_getTriforceNum() == 8) {
            *pMsgNo = 0x0635;
        } else {
            *pMsgNo = 0x0634;
        }
        break;
    default:
        msg_status = fopMsgStts_MSG_ENDS_e;
        break;
    }

    return msg_status;
}

/* 00001214-000013A0       .text lookBack__10daNpc_So_cFv */
void daNpc_So_c::lookBack() {
    if (dComIfGp_event_getMode() != 0) {
        if (mEventCut.getAttnFlag()) {
            if (m06D3 == 4) {
                m_jnt.clrTrn();
            } else {
                m_jnt.setTrn();
                mLookTarget = mEventCut.getAttnPos();
            }
        } else {
            mLookTarget = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
        }
    } else {
        m_jnt.clrTrn();
        mLookTarget = dNpc_playerEyePos(l_HIO.mNpcHIO.m04);
    }

    if (m_jnt.trnChk()) {
        s16 target = l_HIO.mNpcHIO.mMaxHeadTurnVel;
        if (mEventCut.getTurnSpeed() != 0) {
            target = mEventCut.getTurnSpeed();
        }
        cLib_addCalcAngleS2(&mLookAngleVel, target, 4, 0x800);
    } else {
        mLookAngleVel = 0;
    }

    cXyz srcPos = mB54;
    srcPos.y += 200.0f;
    m_jnt.lookAtTarget(
        &shape_angle.y, &mLookTarget,
        srcPos, shape_angle.y,
        mLookAngleVel, mBDA
    );
}

/* 000013A0-00001430       .text setAttention__10daNpc_So_cFv */
void daNpc_So_c::setAttention() {
    attention_info.position = mB60;
    attention_info.position.y += l_HIO.mNpcHIO.mAttnYOffset;

    f32 waterY = dLib_getWaterY(attention_info.position, mAcch);
    if (attention_info.position.y <= waterY) {
        attention_info.position.y = waterY;
    }

    eyePos = mB54;
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

    if (i_anmIdx != 6) {
        m06D3 = i_anmIdx;
    }

    if (mpMorf->getFrame() >= mpMorf->getEndFrame() - 1.0f) {
        f32 rnd = cM_rndF(100.0f);
        if (rnd < l_HIO.m005C) {
            if (m06D3 == 5) {
                m06D3 = 3;
            } else if (m06D3 == 3) {
                m06D3 = 5;
            }
        }
    }

    dLib_bcks_setAnm(m_arc_name, mpMorf, &m06D2, &m06D3, &m06D4, a_anm_bcks_tbl, a_anm_prm_tbl, i_morf);
}

/* 00001524-00001644       .text setAnmSwimSpeed__10daNpc_So_cFv */
void daNpc_So_c::setAnmSwimSpeed() {
    if (m06D3 == 2) {
        f32 mag = (current.pos - old.pos).abs();
        f32 ratio = mag / 10.0f;

        if (ratio <= 0.0f) {
            ratio = 0.0f;
        } else if (ratio >= 1.0f) {
            ratio = 1.0f;
        }

        ratio *= l_HIO.m0034;
        if (ratio < l_HIO.m0038) {
            ratio = l_HIO.m0038;
        }

        mpMorf->setPlaySpeed(ratio);
    }
}

/* 00001644-000016E8       .text setMtx__10daNpc_So_cFv */
void daNpc_So_c::setMtx() {
    J3DModel* model = mpMorf->getModel();
    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mDoMtx_stack_c::transM(0.0f, mB34, 0.0f);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
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
    m0AFC = mB08 * (5.0f + cM_rndF(5.0f));
    speedF = m0AFC;
    speed.y = 30.0f * mB08 + 4.0f * speedF;
    if (speed.y > l_HIO.m0050) {
        speed.y = l_HIO.m0050;
    }
    mB00 = speed.y;
    shape_angle.x = l_HIO.m0068;
    setAnm(4, false);
    m_jnt.mbBackBoneLock = 1;
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_SO_JUMP_L, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

/* 00001880-000019F0       .text modeJump__10daNpc_So_cFv */
void daNpc_So_c::modeJump() {
    f32 waterY = dLib_getWaterY(current.pos, mAcch);

    if (current.pos.y < waterY) {
        s8 reverb = dComIfGp_getReverb(current.roomNo);
        JAIZelBasic::zel_basic->seStart(JA_SE_CM_SO_LANDING_L, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);

        fopKyM_createWpillar(&current.pos, 1.4f * scale.x, 1.4f, 0);

        f32 dist = (m0A80 - current.pos).absXZ();
        if (dist > m0A7C) {
            current.pos.x = m0A80.x;
            current.pos.y = m0A80.y;
            current.pos.z = m0A80.z;
        }

        modeProc(PROC_INIT_e, MODE_SWIM_e);
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
    mBDB = 0;

    f32 distPlayerXZ = (dComIfGp_getPlayer(0)->current.pos - m0A80).absXZ();

    daShip_c* ship = dComIfGp_getShipActor();

    if (ship != NULL) {
        cLib_addCalc2(&mB28, 200.0f, 0.1f, 10.0f);
        mB2C = 50.0f;
        mB32 = 0x150;

        mB10 = m0A80;
        mB10.y = dLib_getWaterY(mB10, mAcch);

        dLib_setCirclePath((dLib_circle_path_c*)&mB10);

        mB1C.y = dLib_getWaterY(mB1C, mAcch);
        mB1C.y += mB34;

        f32 distToTarget = (current.pos - mB1C).absXZ();

        if (distToTarget > 150.0f || ship->speedF > 10.0f) {
            m0AFC = 12.0f;
            s16 target = cLib_targetAngleY(&current.pos, &mB1C);
            cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x400);
            field_0xB04 = 0.0f;
        } else {
            cLib_addCalc2(&field_0xB04, 1.0f, 0.01f, 0.05f);
            cXyz dir = mB1C - current.pos;
            cXyz dirCopy = dir;
            cXyz scaled = dirCopy * field_0xB04;
            cXyz newPos = current.pos + scaled;
            current.pos.x = newPos.x;
            current.pos.y = newPos.y;
            current.pos.z = newPos.z;
            cLib_addCalcAngleS2(&shape_angle.y, (s16)(mB30 - 0x8000), 4, 0x400);
        }

        if (distPlayerXZ < m0A7C && dComIfGp_checkPlayerStatus0(0, 0x10000)) {
            modeProc(PROC_INIT_e, MODE_NEAR_SWIM_e);
        } else {
            if (cLib_calcTimer(&m0A90) == 0) {
                modeProc(PROC_INIT_e, MODE_JUMP_e);
            }
        }
    }
}

/* 00001DB8-00001DFC       .text modeNearSwimInit__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwimInit() {
    setAnm(2, false);
    offsetDive();
    m_jnt.mbBackBoneLock = 1;
}

/* 00001DFC-00002144       .text modeNearSwim__10daNpc_So_cFv */
void daNpc_So_c::modeNearSwim() {
    dCamera_c* cam = dCam_getBody();
    cam->SetTypeForce("BoatBattle", (fopAc_ac_c*)NULL);

    mB70 = 2;

    daShip_c* ship = dComIfGp_getShipActor();
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    if (ship != NULL) {
        f32 distPlayerXZ = (player->current.pos - m0A80).absXZ();

        cLib_addCalc2(&mB28, 400.0f, 0.1f, 10.0f);
        mB2C = 50.0f;
        mB32 = 0x100;

        mB10.x = player->current.pos.x;
        mB10.y = player->current.pos.y;
        mB10.z = player->current.pos.z;
        mB10.y = dLib_getWaterY(mB10, mAcch);

        dLib_setCirclePath((dLib_circle_path_c*)&mB10);

        mB1C.y = dLib_getWaterY(mB1C, mAcch);
        mB1C.y += mB34;

        f32 distToTarget = (current.pos - mB1C).absXZ();

        if (distToTarget > 150.0f || ship->speedF > 10.0f) {
            m0AFC = 12.0f;
            s16 target = cLib_targetAngleY(&current.pos, &mB1C);
            cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x400);
            field_0xB04 = 0.0f;
            current.pos.y += mB34;
        } else {
            cLib_addCalc2(&field_0xB04, 1.0f, 0.01f, 0.05f);
            cXyz dir = mB1C - current.pos;
            cXyz dirCopy = dir;
            cXyz scaled = dirCopy * field_0xB04;
            cXyz newPos = current.pos + scaled;
            current.pos.x = newPos.x;
            current.pos.y = newPos.y;
            current.pos.z = newPos.z;
            cLib_addCalcAngleS2(&shape_angle.y, (s16)(mB30 - 0x8000), 4, 0x400);
            current.pos.y += mB34;
        }

        if (distPlayerXZ >= m0A7C) {
            modeProc(PROC_INIT_e, MODE_SWIM_e);
        }
    }
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
    daShip_c* ship = dComIfGp_getShipActor();
    if (ship != NULL) {
        current.pos = ship->current.pos;

        f32 distXZ = (ship->current.pos - mAAC).absXZ();

        if (distXZ >= l_HIO.m0054 && dComIfGs_checkGetItem(NORMAL_SAIL)) {
            if (dComIfGs_isStageBossEnemy(3) && dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                modeProc(PROC_INIT_e, MODE_EVENT_FIRST_e);
            }
        }
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
    JAIZelBasic::zel_basic->seStart(
        JA_SE_CM_SO_DIVE, &eyePos, 0, reverb,
        1.0f, 1.0f, -1.0f, -1.0f, 0
    );

    fopKyM_createWpillar(&current.pos, 1.2f * scale.x, 1.4f, 0);

    m_jnt.mbBackBoneLock = 0;
}

/* 0000296C-00002A90       .text modeDisappear__10daNpc_So_cFv */
void daNpc_So_c::modeDisappear() {
    if (std::abs(mB34 - mB38) < 10.0f) {
        int oldTag = m0A79;
        fopAc_ac_c* found;
        do {
            do {
                m0A79 = cM_rndF(4.9f);
            } while (m0A79 == oldTag);
            found = (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)searchTagSo_CB, this);
        } while (found == NULL);

        current.pos.x = found->current.pos.x;
        current.pos.y = found->current.pos.y;
        current.pos.z = found->current.pos.z;

        mB74 = 0;
        mB78 = 0;
        mB7C = 0;
        mB80 = 0;
        mB84 = 0;
        mB88 = 0.0f;
        mB8C = 0.0f;
        mB90.x = 0.0f;
        mB90.y = 0.0f;
        mB90.z = 0.0f;
        mB9C = 0;
        mBA0.x = 0.0f;
        mBA0.y = 0.0f;
        mBA0.z = 0.0f;
        mBAC = 0;
        mB0C = 0;
        mBD9 = 0;
        mBD8 = 0;
        mBDB = 1;
        modeProc(PROC_INIT_e, MODE_HIDE_e);
        gravity = -2.5f;
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
        { &daNpc_So_c::modeWaitInit, &daNpc_So_c::modeWait, "WAIT" },
        { &daNpc_So_c::modeHideInit, &daNpc_So_c::modeHide, "HIDE" },
        { &daNpc_So_c::modeJumpInit, &daNpc_So_c::modeJump, "JUMP" },
        { &daNpc_So_c::modeSwimInit, &daNpc_So_c::modeSwim, "SWIM" },
        { &daNpc_So_c::modeNearSwimInit, &daNpc_So_c::modeNearSwim, "NEAR_SWIM" },
        { &daNpc_So_c::modeEventFirstWaitInit, &daNpc_So_c::modeEventFirstWait, "EVENT_FIRST_WAIT" },
        { &daNpc_So_c::modeEventFirstInit, &daNpc_So_c::modeEventFirst, "EVENT_FIRST" },
        { &daNpc_So_c::modeEventFirstEndInit, &daNpc_So_c::modeEventFirstEnd, "EVENT_FIRST_END" },
        { &daNpc_So_c::modeEventEsaInit, &daNpc_So_c::modeEventEsa, "EVENT_ESA" },
        { &daNpc_So_c::modeEventMapopenInit, &daNpc_So_c::modeEventMapopen, "EVENT_MAPOPEN" },
        { &daNpc_So_c::modeEventBowInit, &daNpc_So_c::modeEventBow, "EVENT_BOW" },
        { &daNpc_So_c::modeTalkInit, &daNpc_So_c::modeTalk, "TALK" },
        { &daNpc_So_c::modeDisappearInit, &daNpc_So_c::modeDisappear, "DISAPPEAR" },
        { &daNpc_So_c::modeDebugInit, &daNpc_So_c::modeDebug, "DEBUG" },
        { &daNpc_So_c::modeGetRupeeInit, &daNpc_So_c::modeGetRupee, "GETRUPEE" },
        { &daNpc_So_c::modeEventTriForceInit, &daNpc_So_c::modeEventTriForce, "EVENT_TRIFORCE" },
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
    static char* event_names[] = {
        "SO_1ST_MEET",
        "SO_1ST_MEET_END",
        "SO_MAPOPEN",
        "SO_BOW",
        "SO_GET_RUPEE",
        "SO_TRIFORCE_CHECK",
    };

    u8 ev = mB70;
    if (ev == 1 || ev == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (mB70 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (ev == 5 || ev == 4 || ev == 6) {
        fopAcM_orderChangeEvent(this, event_names[ev - 3], 0, 0xFFFF);
    } else if (ev == 7) {
        if (REG12_S(9) == 0) {
            fopAcM_orderChangeEvent(this, event_names[ev - 3], 0, 0xFFFF);
            eventInfo.onCondition(dEvtCnd_CANGETITEM_e);
        } else {
            fopAcM_orderOtherEvent2(this, event_names[ev - 3], 1, 0xFFFF);
        }
    } else if (ev >= 3) {
        fopAcM_orderOtherEvent2(this, event_names[ev - 3], 1, 0xFFFF);
    }
}

/* 00003264-0000330C       .text checkOrder__10daNpc_So_cFv */
void daNpc_So_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        mB70 = 0;
    } else if (eventInfo.checkCommandTalk()) {
        if (mB70 == 1 || mB70 == 2) {
            bool hasTalkBtn = false;
            if (dComIfGp_event_getTalkXYBtn() == 1 ||
                dComIfGp_event_getTalkXYBtn() == 2 ||
                dComIfGp_event_getTalkXYBtn() == 3)
            {
                hasTalkBtn = true;
            }
            if (hasTalkBtn) {
                modeProc(PROC_INIT_e, MODE_EVENT_ESA_e);
            }
            mB70 = 0;
        }
    }
}

/* 0000330C-000033F4       .text setScale__10daNpc_So_cFv */
void daNpc_So_c::setScale() {
    f32 dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));

    if (dist > l_HIO.m0048) {
        mB08 = 1.0f + (dist - l_HIO.m0048) / ((3000.0f - l_HIO.m0048) / l_HIO.m004C);
        if (mB08 > l_HIO.m004C) {
            mB08 = l_HIO.m004C;
        }
    } else {
        mB08 = l_HIO.m0044;
    }

    if (mCurMode == MODE_EVENT_TRIFORCE_e) {
        mB08 = 1.0f;
        scale.x = mB08;
        scale.y = mB08;
        scale.z = mB08;
    }

    cXyz targetScale(mB08, mB08, mB08);
    cLib_addCalcPos2(&scale, targetScale, 0.1f, 0.01f);
}

/* 000033F4-00003844       .text _execute__10daNpc_So_cFv */
bool daNpc_So_c::_execute() {
    f32 hi = 100.0f * scale.x;
    f32 lo = -100.0f * scale.x;
    fopAcM_setCullSizeBox(this, lo, lo, lo, hi, hi, hi);

    if (dComIfGp_event_getMode() == 0 && mAcch.ChkGroundHit()) {
        current.pos.y = 0.0f;
        speedF = 0.0f;
        m0AFC = 0.0f;
        speed.y = 0.0f;
        m0AFC = 0.0f;
        modeProc(PROC_INIT_e, MODE_HIDE_e);
        return true;
    }

    m_jnt.setParam(
        l_HIO.mNpcHIO.mMaxBackboneX,
        l_HIO.mNpcHIO.mMaxBackboneY,
        l_HIO.mNpcHIO.mMinBackboneX,
        l_HIO.mNpcHIO.mMinBackboneY,
        l_HIO.mNpcHIO.mMaxHeadX,
        l_HIO.mNpcHIO.mMaxHeadY,
        l_HIO.mNpcHIO.mMinHeadX,
        l_HIO.mNpcHIO.mMinHeadY,
        l_HIO.mNpcHIO.mMaxTurnStep
    );

    current.angle.y = shape_angle.y;

    if (mCurMode == MODE_HIDE_e) {
        if (0.0f == m0A7C) {
            fopAcIt_Judge((fopAcIt_JudgeFunc)searchTagSo_CB, this);
        } else {
            modeProc(PROC_INIT_e, MODE_SWIM_e);
        }
    } else if (0.0f == m0A7C) {
        fopAcIt_Judge((fopAcIt_JudgeFunc)searchTagSo_CB, this);
    }

    if (cLib_calcTimer(&m868) == 0) {
        m86C++;
        if (m86C > mBtpAnm.getFrameCtrl()->getEnd()) {
            m868 = (int)(s16)(int)(100.0f + cM_rndF(100.0f));
            m86C = 0;
        }
    }

    setScale();
    setAttention();
    cLib_addCalc2(&speedF, m0AFC, 0.3f, 4.0f);
    cLib_addCalc2(&mB34, mB38, mB40, mB3C);
    lookBack();
    checkOrder();
    modeProc(PROC_EXEC_e, 0x10);
    eventOrder();

    s16 target = 0;
    f32 waterY = dLib_getWaterY(current.pos, mAcch);
    if (current.pos.y < waterY) {
        current.pos.y = dLib_getWaterY(current.pos, mAcch);
        if (mB34 > 0.0f && mRipple.mpBaseEmitter == NULL) {
            static cXyz ripple_scale(0.8f, 0.8f, 0.8f);
            dComIfGp_particle_setShipTail(0x33, &current.pos, NULL, &ripple_scale, 0xFF, &mRipple);
            if (mRipple.mpBaseEmitter != NULL) {
                mRipple.mRate = 0.0f;
            }
        }
    } else {
        f32 sy = speed.y;
        f32 thresh = mB00 * 0.25f;
        if (sy < -thresh) {
            target = l_HIO.m0066;
            if (sy < -(mB00 * 0.5f)) {
                target = l_HIO.m0064;
            }
        } else if (sy > thresh) {
            target = l_HIO.m006A;
            if (sy > mB00 * 0.5f) {
                target = l_HIO.m0068;
            }
        } else {
            target = 0;
        }
        mRipple.end();
    }

    cLib_addCalcAngleS2(&shape_angle.x, target, 4, 0x800);

    if (mCurMode != MODE_HIDE_e && mCurMode != MODE_EVENT_FIRST_WAIT_e &&
        mBDB == 0 && cLib_calcTimer(&mBE0) == 0) {
        fopAcM_posMoveF(this, NULL);
        mAcch.CrrPos(*dComIfG_Bgsp());
    }

    mpMorf->play(NULL, 0, 0);
    mpMorf->calc();
    setMtx();
    setAnm(6, false);
    setAnmSwimSpeed();
    current.angle.y = shape_angle.y;

    return false;
}

/* 00003844-000038E0       .text debugDraw__10daNpc_So_cFv */
void daNpc_So_c::debugDraw() {
    cXyz pos1 = m0A80;
    pos1.y += 20.0f;

    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz pos2 = player->current.pos;
    pos2.y += 20.0f;

    cXyz pos3 = current.pos;
    pos3.y += 20.0f;

    cXyz pos4 = mAAC;
    pos4.y += 20.0f;
}

/* 000038E0-00003954       .text hudeDraw__10daNpc_So_cFv */
void daNpc_So_c::hudeDraw() {
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(11));
    mDoMtx_copy(mDoMtx_stack_c::get(), mpModel->getBaseTRMtx());
    mDoExt_modelUpdateDL(mpModel);
}

/* 00003954-00003B00       .text _draw__10daNpc_So_cFv */
bool daNpc_So_c::_draw() {
    if (l_HIO.mNpcHIO.m22 != 0) {
        debugDraw();
    }
    if (mCurMode != MODE_EVENT_FIRST_WAIT_e) {
        if (l_HIO.field_0x2c[5] == 0) {
            J3DModel* model_p = mpMorf->getModel();
            J3DModelData* model_data_p = model_p->getModelData();

            g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
            g_env_light.setLightTevColorType(model_p, &tevStr);

            mBtpAnm.entry(model_data_p, m86C);
            mpMorf->entryDL();
            mBtpAnm.remove(model_data_p);

            if (mEquipNecklace != 0 || l_HIO.field_0x2c[0] != 0) {
                hudeDraw();
            }
        }

        cXyz snap_pos(current.pos.x, current.pos.y + mB34, current.pos.z);
        dSnap_RegistFig(DSNAP_TYPE_UNK7D, this, snap_pos, shape_angle.y, 1.0f, 1.0f, 1.0f);

        cXyz shadow_pos(current.pos.x, 120.0f + current.pos.y, current.pos.z);
        mShadowId = dComIfGd_setShadow(
            mShadowId, 0, mpMorf->getModel(),
            &shadow_pos, 800.0f, 20.0f,
            current.pos.y + mB34, mAcch.GetGroundH(),
            mAcch.m_gnd, &tevStr, 0, 1.0f,
            dDlst_shadowControl_c::getSimpleTex()
        );
    }
    return true;
}

/* 00003B00-00003DF8       .text createInit__10daNpc_So_cFv */
void daNpc_So_c::createInit() {
    mBDA = 0;

    fopNpc_npc_c::mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&(this->fopNpc_npc_c::mStts));

    mStts.Init(0xFF, 0xFF, this);
    mSph.Set(m_sph_src);
    mSph.SetStts(&mStts);

    current.pos.y -= 15.0f;
    setMtx();
    mpMorf->calc();

    mAAC = current.pos;

    offsetZero();
    setAnm(1, false);

    m0A79 = (u8)(int)cM_rndF(5.0f);

    if (!dComIfGs_isEventBit(0x901) &&
        strcmp(dComIfGp_getStartStageName(), "sea") == 0 &&
        current.roomNo == 0xd &&
        dComIfGs_isStageBossEnemy(3))
    {
        modeProc(PROC_INIT_e, MODE_EVENT_FIRST_WAIT_e);
    }
    else if (strcmp(dComIfGp_getStartStageName(), "sea") == 0 &&
             current.roomNo == 0x4 &&
             dComIfGs_isStageBossEnemy(7) &&
             dComIfGs_isCollect(0, 3) &&
             !dComIfGs_isEventBit(0x3A20))
    {
        modeProc(PROC_INIT_e, MODE_EVENT_TRIFORCE_e);
    }
    else {
        attention_info.flags = 0x200000A;
        modeProc(PROC_INIT_e, MODE_HIDE_e);
    }

    mBE0 = 0x1E;
    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
    mAcch.SetWallNone();
    mAcch.SetRoofNone();

    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());

    f32 hi = 100.0f * scale.x;
    f32 lo = -100.0f * scale.x;
    fopAcM_setCullSizeBox(this, lo, lo, lo, hi, hi, hi);

    maxFallSpeed = 10.0f;
    gravity = -2.5f;

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x22;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x22;

    eventInfo.setXyCheckCB(daNpc_So_XyCheckCB);
    eventInfo.setXyEventCB(daNpc_So_XyEventCB);

    mEventCut.setActorInfo2("NpcSo", this);
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
        getArg();

        if (strcmp(dComIfGp_getStartStageName(), "sea") == 0 &&
            current.roomNo == 0x1a &&
            !dComIfGs_isEventBit(0x1E40))
        {
            return cPhs_ERROR_e;
        }

        if (!dComIfGs_isStageBossEnemy(3)) {
            return cPhs_ERROR_e;
        }

        if (!fopAcM_entrySolidHeap(this, createHeap_CB, 0x1c00)) {
            return cPhs_ERROR_e;
        }
        createInit();
    }
    return state;
}

/* 000046E4-00004754       .text _delete__10daNpc_So_cFv */
bool daNpc_So_c::_delete() {
    if (g_dComIfG_gameInfo.play.mMiniGameType == 8) {
        g_dComIfG_gameInfo.play.mMiniGameType = 0;
        g_dComIfG_gameInfo.play.mMinigameFlags ^= 0x80;
        g_dComIfG_gameInfo.play.mMinigameResult = 0;
    }
    dComIfG_resDelete(&mPhs, m_arc_name);
    mRipple.end();
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

#include "d/actor/d_a_npc_so_cut.inc"
