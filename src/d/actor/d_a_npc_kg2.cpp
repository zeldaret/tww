/**
 * d_a_npc_kg2.cpp
 * NPC - Salvatore (Cannon Minigame)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kg2.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/d_lib.h"
#include "d/d_snap.h"
#include "res/Object/Kg.h"
#include "d/d_s_play.h"

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
        /* Height */ 80.0f,
    }},
};


class daNpc_Kg2_HIO_c : public JORReflexible {
public:
    daNpc_Kg2_HIO_c();
    virtual ~daNpc_Kg2_HIO_c() { }

    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x00 */ // vtable for daNpc_Kg2_HIO_C
    /* 0x04 */ s8 mNo;
    /* 0x05 */ // vtable for dNpc_HIO_c
    /* 0x08 */ dNpc_HIO_c mNpc;
    /* 0x30 */ u8 field_0x30;
};  // Size: 0x34

/* 000000EC-00000194       .text __ct__15daNpc_Kg2_HIO_cFv */
daNpc_Kg2_HIO_c::daNpc_Kg2_HIO_c() {
    mNpc.m04 = -20.0f;
    mNpc.mMaxHeadX = 0x9C4;
    mNpc.mMaxHeadY = 7000;
    mNpc.mMaxBackboneX = 2000;
    mNpc.mMaxBackboneY = 8000;
    mNpc.mMinHeadX = -0x9C4;
    mNpc.mMinHeadY = -7000;
    mNpc.mMinBackboneX = -2000;
    mNpc.mMinBackboneY = -8000;
    mNpc.mMaxTurnStep = 0x1000;
    mNpc.mMaxHeadTurnVel = 1000;
    mNpc.mAttnYOffset = 35.0f;
    mNpc.mMaxAttnAngleY = 0x4000;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 400.0f;
    field_0x30 = 0;
    mNo = -1;
    return;
}

static daNpc_Kg2_HIO_c l_HIO;

static const int l_bck_ix_tbl[] = {
    dRes_INDEX_KG_BCK_KG_WAIT01_e,
    dRes_INDEX_KG_BCK_KG_WAIT02_e,
    dRes_INDEX_KG_BCK_KG_TALK01_e,
    dRes_INDEX_KG_BCK_KG_KAMAE_e,
    dRes_INDEX_KG_BCK_KG_KWAIT_e,
    dRes_INDEX_KG_BCK_KG_CAPTAIN_e,
    dRes_INDEX_KG_BCK_KG_CAPTAIN02_e,
    dRes_INDEX_KG_BCK_KG_KIDS_e,
    dRes_INDEX_KG_BCK_KG_RADIO_e,
    dRes_INDEX_KG_BCK_KG_SASIKAE_e,
    dRes_INDEX_KG_BCK_KG_GONZO_e,
    dRes_INDEX_KG_BCK_KG_TETORA_e,
    dRes_INDEX_KG_BCK_KG_KAMAE_e,
    dRes_INDEX_KG_BCK_KG_KWAIT_e,
    dRes_INDEX_KG_BCK_KG_TETORA02_e,
};

static const int l_btp_ix_tbl[] = {
    dRes_INDEX_KG_BTP_KG_e,
    dRes_INDEX_KG_BTP_MOPEN_e,
    dRes_INDEX_KG_BTP_WARAI_e,
    dRes_INDEX_KG_BTP_RADIO_e,
    dRes_INDEX_KG_BTP_SLEEP_e,
};

/* 00000194-00000368       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    /* Nonmatching */
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Kg2_c* i_this = (daNpc_Kg2_c*)model->getUserArea();
        if (i_this) {
            J3DJoint* joint = (J3DJoint*)node;
            int jntNo = joint->getJntNo();
            MtxP mVar = model->getAnmMtx(jntNo);
            MTXCopy(mVar, mDoMtx_stack_c::get());
            if (jntNo == (i_this->m_jnt).getHeadJntNum()) {
                cXyz tmp(
                    REG10_F(0) + 24.0f,
                    REG10_F(1) + 5.0f,
                    REG10_F(2)
                );

                static cXyz l_offsetEyePos(24.0f, -16.0f, 0.0f);

                mDoMtx_stack_c::multVec(&tmp, i_this->getEyePos());
                mDoMtx_stack_c::XrotM((s16)i_this->m_jnt.getHead_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getHead_x());
                mDoMtx_stack_c::multVec(&l_offsetEyePos, i_this->getAttentionBasePos());
                mDoMtx_stack_c::multVec(&tmp, &i_this->attention_info.position);
                i_this->attention_info.position.y += l_HIO.mNpc.mAttnYOffset;
            } else if (jntNo == (i_this->m_jnt).getBackboneJntNum()) {
                mDoMtx_stack_c::XrotM((s16)i_this->m_jnt.getBackbone_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getBackbone_x());
            }
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 000003A4-0000048C       .text set_mtx__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::set_mtx() {
    J3DModel* model = mpMorf->getModel();

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    if (field_0x736) {
        mDoMtx_stack_c::copy(model->getAnmMtx(m_handL_num));
        mDoMtx_stack_c::transM(23.46f, -22.26f, -47.05f);
        mDoMtx_stack_c::XYZrotM(8011, -20224, 8011);
        field_0x6D4->setBaseTRMtx(mDoMtx_stack_c::get());
    }
    return;
}

/* 0000048C-000005A0       .text initTexPatternAnm__11daNpc_Kg2_cFb */
BOOL daNpc_Kg2_c::initTexPatternAnm(bool i_modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    m_btp = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("Kg", l_btp_ix_tbl[field_0x748]));
    JUT_ASSERT(0x12B, m_btp != 0);
    if (!mBtpAnm.init(modelData, m_btp, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        return FALSE;
    }
    field_0x704 = 0;
    field_0x706 = 0;
    return TRUE;
}

/* 000005A0-000006EC       .text playTexPatternAnm__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::playTexPatternAnm() {
    if (field_0x738 == 1 && field_0x748 == 0 && field_0x704 == 2) {
        field_0x704 = 0;
        field_0x748 = 4;
        initTexPatternAnm(true);
        return;
    }

    if (cLib_calcTimer(&field_0x706) == 0) {
        if (field_0x748 == 4) {
            if (field_0x704 == 0) {
                field_0x704 = 1;
                field_0x706 = cM_rndF(150.0f) + 150.0f;
            } else {
                field_0x704 = 0;
                field_0x706 = (s16)(cM_rndF(150.0f) + 150) << 1;
            }
        } else {
            if (field_0x704 >= m_btp->getFrameMax()) {
                field_0x704 -= m_btp->getFrameMax();
                field_0x706 = cM_rndF(100.0f) + 30.0f;
            } else {
                field_0x704 += 1;
            }
        }
    }
    return;
}

/* 000006EC-00000838       .text setAnm__11daNpc_Kg2_cFScf */
void daNpc_Kg2_c::setAnm(s8 param_1, f32 param_2) {
    static int a_play_mode_tbl[] = {
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_LOOP,
    };
    static f32 a_morf_frame_tbl[] = {
        8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f,
        8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f,
    };
    static f32 a_play_speed_tbl[] = {
        1.0f, 1.0f, 1.0f, 1.0f,  1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, -1.0f, 1.0f, 1.0f,
    };

    f32 fvar = param_2;
    if (fvar < 0.0f) {
        fvar = a_morf_frame_tbl[param_1];
    }

    if (param_1 != field_0x749 && field_0x749 != -1) {
        field_0x749 = param_1;
        dNpc_setAnm(
            mpMorf,
            a_play_mode_tbl[field_0x749],
            fvar,
            a_play_speed_tbl[field_0x749],
            l_bck_ix_tbl[field_0x749],
            -1,
            "Kg"
        );
        if (field_0x749 == 0xC) {
            mpMorf->setFrame(mpMorf->getEndFrame() - 1.0f);
            mpMorf->setPlaySpeed(-1.0f);
        }
    }

    if (field_0x749 == 2) {
        m_jnt.offHeadLock();
        m_jnt.onBackBoneLock();
    } else {
        m_jnt.onHeadLock();
        m_jnt.onBackBoneLock();
    }
    return;
}

/* 00000838-000009E8       .text subAnm__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::subAnm() {
    if (field_0x748 == 4) {
        fopAcM_seStart(this, 0x4114, 0);
    }

    if (field_0x749 == 3 || field_0x749 == 0xD) {
        if (mpMorf->checkFrame(1.0f)) {
            field_0x736 = 1;
            if (field_0x749 == 3) {
                field_0x737 = 3;
                return;
            } else {
                field_0x737 = 4;
                return;
            }
        }
    }
    if (field_0x749 == 9) {
        if (mpMorf->checkFrame(30.0f)) {
            field_0x736 = 1;
            field_0x737 = 2;
            return;
        }
    }
    if (field_0x749 == 0xC) {
        if (mpMorf->checkFrame(1.0f)) {
            field_0x736 = 0;
            setAnm(1, -1.0f);
            return;
        }
    }
    if (field_0x749 == 0xD) {
        if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            setAnm(4, -1.0f);
            return;
        }
    }
}

/* 000009E8-00000B3C       .text chkAttention__11daNpc_Kg2_cF4cXyzs */
BOOL daNpc_Kg2_c::chkAttention(cXyz param_1, s16 param_2) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 fVar_1 = l_HIO.mNpc.mMaxAttnDistXZ;
    int iVar_1 = l_HIO.mNpc.mMaxAttnAngleY;
    cXyz delta;
    delta.x = player->current.pos.x - param_1.x;
    delta.z = player->current.pos.z - param_1.z;

    f32 fVar_2 = std::sqrtf(delta.x*delta.x + delta.z*delta.z);
    s16 sVar = cM_atan2s(delta.x, delta.z);
    if (field_0x72C) {
        fVar_1 += 40.0f;
        iVar_1 += 1820;
    }
    sVar -= param_2;
    BOOL bVar = 0;
    if (iVar_1 > abs(sVar) && fVar_1 > fVar_2) {
        bVar = 1;
    }
    return bVar;
}

/* 00000B3C-00000BC0       .text eventOrder__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::eventOrder() {
    if (field_0x750 == 1 || field_0x750 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (field_0x750 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (field_0x750 == 3) {
        fopAcM_orderOtherEventId(this, mEventIdTable[mEventIdx], 0xFF, 0xFFFF, 0, 1);
    }
    return;
}

/* 00000BC0-00000CC4       .text checkOrder__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        setAction(&daNpc_Kg2_c::event_wait_action, NULL);
        field_0x750 = 0;
    } else if (eventInfo.checkCommandTalk()) {
        if (field_0x750 == 1 || field_0x750 == 2) {
            field_0x750 = 0;
            field_0x72D = 1;
        }
    }
    return;
}

/* 00000CC4-00000E38       .text getMsg__11daNpc_Kg2_cFv */
u32 daNpc_Kg2_c::getMsg() {
    int msgNo;
    if (field_0x74C) {
        u8 tmp = dComIfGs_getEventReg(dSv_event_flag_c::UNK_B703);
        if (field_0x74C == 0x3145) {
            if (field_0x735 == 1) {
                field_0x74C = 0x314B;
            } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2508)) {
                field_0x74C = 0x314C;
            }
        } else if (field_0x74C == 0x3150) {
            if (tmp) {
                field_0x74C = 0x3154;
            }
        } else if (field_0x74C == 0x3152) {
            if (tmp == 1) {
                field_0x74C = 0x3156;
            } else if (tmp >= 2) {
                field_0x74C = 0x3158;
            }
        }
        msgNo = field_0x74C;
        field_0x74C = 0;
    } else {
        if (field_0x738 == 1) {
            msgNo = 0x315B;
        } else {
            msgNo = dComIfGs_isEventBit(dSv_event_flag_c::UNK_2540);
            if (msgNo != 0 && dComIfGs_isEventBit(dSv_event_flag_c::UNK_2520) == 0) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_2520);
                msgNo = 0x3140;
            } else {
                if (field_0x734 == 0) {
                    field_0x734 = 1;
                    msgNo = 0x3139;
                } else {
                    msgNo = 0x313A;
                }
            }
        }
    }
    return msgNo;
}

/* 00000E38-00001028       .text next_msgStatus__11daNpc_Kg2_cFPUl */
u16 daNpc_Kg2_c::next_msgStatus(u32* pMsgNo) {
    u16 temp = 0xF;
    switch (*pMsgNo) {
        case 0x3140:
        case 0x3145:
        case 0x3146:
        case 0x3147:
        case 0x3148:
        case 0x314C:
        case 0x314E:
        case 0x3150:
        case 0x3152:
        case 0x3154:
        case 0x3156:
        case 0x3158:
            *pMsgNo += 1;
            break;
        case 0x314D:
            *pMsgNo = 0x3147;
            break;
        case 0x3139:
            if (dComIfGs_getEventReg(dSv_event_flag_c::UNK_B703) == 0) {
                *pMsgNo = 0x313E;
            } else if ((s32)dLib_getIplDaysFromSaveTime() < 4) {
                *pMsgNo = 0x313B;
            } else {
                if (dComIfGs_isTmpBit(dSv_event_flag_c::UNK_0102)) {
                    *pMsgNo = 0x313C;
                } else {
                    dComIfGs_onTmpBit(dSv_event_flag_c::UNK_0102);
                    *pMsgNo = 0x313D;
                }
            }
            break;
        case 0x3149:
            if (mpCurrMsg->mSelectNum == 0) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_2508);
                field_0x735 = 1;
                *pMsgNo = 0x314B;
            } else {
                *pMsgNo = 0x314A;
            }
            break;
        case 0x314A:
            *pMsgNo = 0x3148;
            break;
        case 0x313A:
        case 0x313B:
        case 0x313C:
        case 0x313D:
        case 0x313E:
            *pMsgNo = 0x313F;
            break;
        case 0x313F:
        case 0x314F:
            if (mpCurrMsg->mSelectNum == 0) {
                if (dComIfGs_getRupee() < 50) {
                    *pMsgNo = 0x3143;
                } else {
                    dComIfGp_setItemRupeeCount(-50);
                    dComIfGp_setAStatusForce(25);
                    *pMsgNo = 0x3144;
                }
            } else {
                *pMsgNo = 0x3142;
            }
            break;
        case 0x3141:
            if (field_0x734 == 0) {
                field_0x734 = 1;
                *pMsgNo = 0x3139;
            } else {
                *pMsgNo = 0x313A;
            }
            break;
        default:
            temp = 0x10;
            break;
    }
    return temp;
}

/* 00001028-000012EC       .text anmAtr__11daNpc_Kg2_cFUs */
void daNpc_Kg2_c::anmAtr(u16 i_msgStatus) {
    u8 temp = dComIfGp_getMesgAnimeAttrInfo();
    if (field_0x738 != 1) {
        switch (temp) {
            case 0:
                setAnm(0, -1.0f);
                field_0x748 = 0;
                initTexPatternAnm(true);
                break;
            case 1:
                setAnm(1, -1.0f);
                field_0x748 = 0;
                initTexPatternAnm(true);
                break;
            case 2:
                setAnm(2, -1.0f);
                field_0x748 = 1;
                initTexPatternAnm(true);
                break;
            case 3:
                setAnm(3, -1.0f);
                field_0x748 = 0;
                initTexPatternAnm(true);
                break;
            case 4:
                setAnm(5, -1.0f);
                field_0x748 = 1;
                initTexPatternAnm(true);
                break;
            case 5:
                setAnm(6, -1.0f);
                field_0x748 = 1;
                initTexPatternAnm(true);
                break;
            case 6:
                setAnm(7, -1.0f);
                field_0x748 = 2;
                initTexPatternAnm(true);
                break;
            case 7:
                setAnm(8, -1.0f);
                field_0x748 = 3;
                initTexPatternAnm(true);
                break;
            case 8:
                setAnm(9, -1.0f);
                field_0x748 = 0;
                initTexPatternAnm(true);
                break;
            case 9:
                setAnm(10, -1.0f);
                field_0x748 = 1;
                initTexPatternAnm(true);
                break;
            case 10:
                setAnm(11, -1.0f);
                field_0x748 = 2;
                initTexPatternAnm(true);
                break;
            case 11:
                setAnm(14, -1.0f);
                field_0x748 = 2;
                initTexPatternAnm(true);
        }

        if (field_0x749 == 3 && mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            setAnm(4, -1.0f);
            field_0x748 = 0;
            initTexPatternAnm(true);
        }

        dComIfGp_setMesgAnimeAttrInfo(0xff);
    }
    return;
}

/* 000012EC-00001308       .text setAttention__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::setAttention() {
    f32 fVar_2;
    f32 fVar_3;
    f32 fVar_1;

    fVar_1 = mAttPos.z;
    fVar_2 = mAttPos.y;
    fVar_3 = mAttPos.x;

    eyePos.x = fVar_3;
    eyePos.y = fVar_2;
    eyePos.z = fVar_1;
    return;
}

/* 00001308-00001448       .text lookBack__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::lookBack() {
    cXyz tmp;
    cXyz pos_1;
    pos_1.x = 0.0f;
    pos_1.y = 0.0f;
    pos_1.z = 0.0f;
    cXyz* pos_p = 0x0;
    s16 sVar = current.angle.y;

    switch (field_0x760) {
        case 2:
        case 1:
            if (field_0x760 == 2) {
                m_jnt.setTrn();
            }
            if (field_0x72C) {
                tmp = dNpc_playerEyePos(l_HIO.mNpc.m04);
                pos_p = &tmp;
                pos_1 = current.pos;
                pos_1.y = eyePos.y;
            }
            break;
    }

    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&field_0x720, l_HIO.mNpc.mMaxHeadTurnVel, 4, 0x800);
    } else {
        field_0x720 = 0;
    }

    m_jnt.lookAtTarget(
        &current.angle.y,
        pos_p,
        pos_1,
        sVar,
        field_0x720,
        true);
    return;
}

/* 00001448-00001468       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Kg2_c*>(i_this)->CreateHeap();
}

/* 00001468-0000180C       .text CreateHeap__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Kg", 5));
    JUT_ASSERT(0x391, modelData != 0);

    mDoExt_McaMorf* morfVar = new mDoExt_McaMorf(
        modelData,
        NULL,
        NULL,
        static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Kg", 26)),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        TRUE,
        NULL,
        0,
        0x11020203
    );
    mpMorf = morfVar;

    morfVar = mpMorf;
    if (morfVar == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    } else {
        m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
        JUT_ASSERT(0x3A1, m_jnt.getHeadJntNum() >= 0);

        m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone2"));
        JUT_ASSERT(0x3A6, m_jnt.getBackboneJntNum() >= 0);

        m_handL_num = modelData->getJointName()->getIndex("handL");
        JUT_ASSERT(0x3AA, m_handL_num >= 0);

        field_0x748 = 0;
        if (initTexPatternAnm(false) == FALSE) {
            return FALSE;
        } else {
            modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Kg", 6));
            field_0x6D4 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020002);
            if (field_0x6D4 == NULL) {
                return FALSE;
            } else {
                int tmp = field_0x6D8.init(
                    modelData,
                    static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("Kg", 10)),
                    TRUE,
                    2,
                    0.0f,
                    0,
                    -1,
                    false,
                    FALSE
                );
                if (tmp == 0) {
                    return FALSE;
                } else {
                    modelData = mpMorf->getModel()->getModelData();
                    modelData->getJointNodePointer(m_jnt.mHeadJntNum)->setCallBack(nodeCallBack);
                    modelData->getJointNodePointer(m_jnt.mBackboneJntNum)->setCallBack(nodeCallBack);
                    mpMorf->getModel()->setUserArea((uintptr_t)this);
                    mAcchCir.SetWall(30.0f, 0.0f);
                    mObjAcch.Set(
                        fopAcM_GetPosition_p(this),
                        fopAcM_GetOldPosition_p(this),
                        this,
                        1,
                        &mAcchCir,
                        fopAcM_GetSpeed_p(this),
                        NULL,
                        NULL
                    );
                }
            }
        }
    }
    return TRUE;
}

/* 0000180C-00001A9C       .text CreateInit__11daNpc_Kg2_cFv */
int daNpc_Kg2_c::CreateInit() {
    mActorAngle = current.angle;

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x6E;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x6E;

    gravity = -30.0f;
    setAction(&daNpc_Kg2_c::wait_action, NULL);

    mAttPos = current.pos;

    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);

    setCollision(60.0f, 150.0f);

    mEventCut.setActorInfo2("Kg2", this);
    mEventCut.setJntCtrlPtr(&m_jnt);

    field_0x734 = 0;
    field_0x735 = 0;
    field_0x736 = 0;
    field_0x737 = 0;
    field_0x74C = 0;

    m_jnt.mbHeadLock = true;
    m_jnt.mbBackBoneLock = true;

    field_0x750 = 0;
    mEventIdx = 4;

    mEventIdTable[0] = dComIfGp_evmng_getEventIdx("KG2_START_DEMO");
    mEventIdTable[1] = dComIfGp_evmng_getEventIdx("KG2_CLEAR_DEMO");
    mEventIdTable[2] = dComIfGp_evmng_getEventIdx("KG2_GETDEMO");
    mEventIdTable[3] = dComIfGp_evmng_getEventIdx("CANON_GAME");
    set_mtx();

    if (dComIfGs_getTime() >= 105.0f && dComIfGs_getTime() < 300.0f) {
        field_0x738 = 0;
        setAnm(1, -1.0f);
    } else {
        field_0x738 = 1;
        setAnm(13, 0.0f);
    }

    l_kg2_pointer = this;
    return 1;
}

/* 00001A9C-00001BDC       .text wait01__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::wait01() {
    if (dComIfGs_getTime() >= 105.0f && dComIfGs_getTime() < 300.0f) {
        if (field_0x738 == 1) {
            field_0x738 = 0;
            setAnm(12, -1.0f);
            field_0x748 = 0;
            initTexPatternAnm(true);
        }
    } else if (field_0x738 == 0) {
        field_0x738 = 1;
        setAnm(13, -1.0f);
        field_0x748 = 0;
        initTexPatternAnm(true);
    }

    if (field_0x72D) {
        field_0x760 = 2;
        return;
    }

    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    f32 delta = std::fabsf(current.pos.y - player->current.pos.y);
    if (field_0x72C != 0 && delta < 50.0f) {
        if (field_0x749 != 13 && field_0x749 != 12) {
            field_0x750 = 2;
        }
    }
    return;
}

/* 00001BDC-00001CA4       .text talk01__11daNpc_Kg2_cFv */
void daNpc_Kg2_c::talk01() {
    if (talk(1) == 0x12) {  // Maybe 0x12 = fopMsgStts_BOX_CLOSED_e ?
        field_0x760 = 1;
        dComIfGp_event_reset();
        field_0x72D = 0;
        if (mCurrMsgNo == 0x3144) {
            field_0x750 = 3;
            mEventIdx = 0;
        } else if (field_0x738 == 0) {
            setAnm(1, -1.0f);
            field_0x748 = 0;
            initTexPatternAnm(true);
        } else {
            setAnm(4, -1.0f);
        }
    }
    return;
}

/* 00001CA4-00001D88       .text evn_setAnm_init__11daNpc_Kg2_cFi */
u32 daNpc_Kg2_c::evn_setAnm_init(int param) {
    int* piVar_1 = dComIfGp_evmng_getMyIntegerP(param, "AnmNo");
    int* piVar_2 = dComIfGp_evmng_getMyIntegerP(param, "count");
    f32* pfVar = dComIfGp_evmng_getMyFloatP(param, "hokan");
    if (piVar_1) {
        f32 tmp = -1.0f;
        if (pfVar) {
            tmp = *pfVar;
        }

        setAnm(*piVar_1, tmp);

        if (piVar_2) {
            field_0x739 = *piVar_2;
        } else {
            field_0x739 = 0;
        }
    }
    return 1;
}

/* 00001D88-00001E4C       .text evn_setAnm__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::evn_setAnm() {
    if (field_0x749 == 0xC) {
        if (mpMorf->checkFrame(1.0f)) {
            field_0x739 -= 1;
        }
    } else {
        if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            field_0x739 -= 1;
        }
    }

    if (field_0x739 <= 0) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 00001E4C-00001F14       .text evn_jnt_lock_init__11daNpc_Kg2_cFi */
u32 daNpc_Kg2_c::evn_jnt_lock_init(int param) {
    int* piVar = dComIfGp_evmng_getMyIntegerP(param, "prm");
    int tmp = 0;
    if (piVar) {
        tmp = *piVar;
    }
    switch (tmp) {
        case 0:
            m_jnt.offHeadLock();
            m_jnt.offBackBoneLock();
            break;
        case 1:
            m_jnt.onHeadLock();
            m_jnt.offBackBoneLock();
            break;
        case 2:
            m_jnt.offHeadLock();
            m_jnt.onBackBoneLock();
            break;
        case 3:
            m_jnt.onHeadLock();
            m_jnt.onBackBoneLock();
            break;
    }
    return 1;
}

/* 00001F14-00001F88       .text evn_talk_init__11daNpc_Kg2_cFi */
u32 daNpc_Kg2_c::evn_talk_init(int param) {
    int* piVar = dComIfGp_evmng_getMyIntegerP(param, "msg_num");
    mCurrMsgBsPcId = -1;
    mpCurrMsg = NULL;
    if (piVar) {
        field_0x74C = *piVar;
    } else {
        field_0x74C = 0;
    }
    return 1;
}

/* 00001F88-00001FBC       .text evn_talk__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::evn_talk() {
    if (talk(1) == 0x12) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 00001FBC-00002070       .text evn_createItem_init__11daNpc_Kg2_cFi */
u32 daNpc_Kg2_c::evn_createItem_init(int param) {
    u8 iVar = dComIfGs_getEventReg(dSv_event_flag_c::UNK_B703);
    switch (iVar) {
        case 0:
        case 1:
            iVar = 7;
            break;
        case 2:
            iVar = 0xD7;
            break;
        case 3:
        default:
            iVar = 6;
            break;
    }

    fpc_ProcID tmp = fopAcM_createItemForPresentDemo(
        &current.pos,
        iVar,
        0,
        -1,
        fopAcM_GetRoomNo(this),
        NULL,
        NULL
    );
    if (tmp != fpcM_ERROR_PROCESS_ID_e) {
        dComIfGp_event_setItemPartnerId(tmp);
    }
    return 1;
}

/* 00002070-000021EC       .text privateCut__11daNpc_Kg2_cFv */
s32 daNpc_Kg2_c::privateCut() {
    static char* cut_name_tbl[] = {
        "SETANM",
        "JNTLOCK",
        "SHOWITEM",
        "KGTALK",
        "CREATEITEM",
    };

    int staffIdx = dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
    if (staffIdx == -1) {
        return 0;
    }

    int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), TRUE, 0);
    if (actIdx == -1) {
        dComIfGp_evmng_cutEnd(staffIdx);
    } else {
        if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
            switch (actIdx) {
                case 0:
                    evn_setAnm_init(staffIdx);
                    break;
                case 1:
                    evn_jnt_lock_init(staffIdx);
                    break;
                case 3:
                    evn_talk_init(staffIdx);
                    break;
                case 4:
                    evn_createItem_init(staffIdx);
                    break;
                case 2:
                    break;
            }
        }

        BOOL tmp;
        switch (actIdx) {
            case 0:
                tmp = evn_setAnm();
                break;
            case 2:
                tmp = TRUE;
                break;
            case 3:
                tmp = evn_talk();
                break;
            default:
                tmp = TRUE;
                break;
        }
        if (tmp) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }
    return 1;
}

/* 000021EC-00002250       .text processMove__11daNpc_Kg2_cFv */
u32 daNpc_Kg2_c::processMove() {
    (this->*mCurrActionFunc)(NULL);
    if (mEventCut.cutProc() || privateCut()) {
        return 1;
    }
    return 0;
}

/* 00002250-00002334       .text wait_action__11daNpc_Kg2_cFPv */
int daNpc_Kg2_c::wait_action(void*) {
    if (mActionStatus == 0) {
        field_0x760 = 1;
        mActionStatus += 1;
    } else if (mActionStatus != -1) {
        s16 local_1 = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        field_0x72C = chkAttention(current.pos, local_1);
        field_0x750 = 0;
        switch(field_0x760) {
            case 1:
                wait01();
                break;
            case 2:
                talk01();
                break;
        }
        lookBack();
        setAttention();
    }
    return 1;
}

/* 00002334-00002590       .text event_wait_action__11daNpc_Kg2_cFPv */
int daNpc_Kg2_c::event_wait_action(void*) {
    if (mActionStatus == 0) {
        field_0x760 = 1;
        mActionStatus += 1;
    } else if (mActionStatus != -1) {
        s16 local_1 = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        field_0x72C = chkAttention(current.pos, local_1);
        lookBack();
        setAttention();

        if (dComIfGp_evmng_endCheck(mEventIdTable[mEventIdx])) {
            if (mEventIdx == 0) {
                field_0x750 = 3;
                mEventIdx = 3;
            } else if (mEventIdx == 3) {
                if (canon_game_result == 1) {
                    field_0x750 = 3;
                    mEventIdx = 1;
                } else {
                    field_0x750 = 1;
                    field_0x74C = 0x314E;
                }
            } else if (mEventIdx == 1) {
                field_0x750 = 3;
                mEventIdx = 2;
                u8 local_2 = cLib_maxLimit(dComIfGs_getEventReg(dSv_event_flag_c::UNK_B703) + 1, 3);
                dComIfGs_setEventReg(dSv_event_flag_c::UNK_B703, local_2);
            } else if (mEventIdx == 2) {
                field_0x750 = 1;
                field_0x74C = 0x315A;
            } else {
                mEventIdx = 4;
            }

            dComIfGp_event_reset();
            setAction(&daNpc_Kg2_c::wait_action, NULL);
        }
    }
    return 1;
}

/* 00002590-000027BC       .text _create__11daNpc_Kg2_cFv */
cPhs_State daNpc_Kg2_c::_create() {
    fopAcM_ct(this, daNpc_Kg2_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhase, "Kg");
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CallbackCreateHeap, 0x2d00) == 0) {
            return cPhs_ERROR_e;
        } else {
            fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
            if (l_HIO.mNo < 0) {
                l_HIO.mNo = mDoHIO_createChild("海戦ゲーム親父２", &l_HIO);
            }

            if (CreateInit() == 0) {
                return cPhs_ERROR_e;
            }
        }
    }
    return phase_state;
}

/* 00002B6C-00002BFC       .text _delete__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::_delete() {
    dComIfG_resDelete(&mPhase, "Kg");
    if (this->heap) {
        if (mpMorf) {
            mpMorf->stopZelAnime();
        }
    }

    l_kg2_pointer = 0;

    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    return TRUE;
}

/* 00002BFC-00002D14       .text _execute__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::_execute() {
    m_jnt.setParam(
        l_HIO.mNpc.mMaxBackboneX,
        l_HIO.mNpc.mMaxBackboneY,
        l_HIO.mNpc.mMinBackboneX,
        l_HIO.mNpc.mMinBackboneY,
        l_HIO.mNpc.mMaxHeadX,
        l_HIO.mNpc.mMaxHeadY,
        l_HIO.mNpc.mMinHeadX,
        l_HIO.mNpc.mMinHeadY,
        l_HIO.mNpc.mMaxTurnStep
    );

    playTexPatternAnm();
    mpMorf->play(&eyePos, 0, 0);
    mpMorf->calc();
    checkOrder();
    processMove();
    eventOrder();
    subAnm();
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    set_mtx();
    setCollision(60.0f, 150.0f);
    return TRUE;
}

/* 00002D14-00002E74       .text _draw__11daNpc_Kg2_cFv */
BOOL daNpc_Kg2_c::_draw() {
    J3DModel* morf_model = mpMorf->getModel();
    J3DModelData* model_data = morf_model->getModelData();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morf_model, &tevStr);
    mBtpAnm.entry(model_data, field_0x704);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);

    if (field_0x736) {
        model_data = field_0x6D4->getModelData();
        g_env_light.setLightTevColorType(field_0x6D4, &tevStr);
        field_0x6D8.entry(model_data, field_0x737);
        mDoExt_modelUpdateDL(field_0x6D4);
        field_0x6D8.remove(model_data);
    }

    cXyz shadow_pos(
        current.pos.x,
        current.pos.y + 150.0f,
        current.pos.z
    );
    mShadowId = dComIfGd_setShadow(
        mShadowId,
        1,
        mpMorf->getModel(),
        &shadow_pos,
        800.0f,
        20.0f,
        current.pos.y,
        mObjAcch.GetGroundH(),
        mObjAcch.m_gnd,
        &tevStr,
        0,
        1.0f,
        dDlst_shadowControl_c::getSimpleTex()
    );

    dSnap_RegistFig(DSNAP_TYPE_NPC_KG2, this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00002E74-00002E94       .text daNpc_Kg2_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kg2_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_create();
}

/* 00002E94-00002EB4       .text daNpc_Kg2_Delete__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_Delete(daNpc_Kg2_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_delete();
}

/* 00002EB4-00002ED4       .text daNpc_Kg2_Execute__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_Execute(daNpc_Kg2_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_execute();
}

/* 00002ED4-00002EF4       .text daNpc_Kg2_Draw__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_Draw(daNpc_Kg2_c* i_this) {
    return ((daNpc_Kg2_c*)i_this)->_draw();
}

/* 00002EF4-00002EFC       .text daNpc_Kg2_IsDelete__FP11daNpc_Kg2_c */
static BOOL daNpc_Kg2_IsDelete(daNpc_Kg2_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Kg2_Method = {
    (process_method_func)daNpc_Kg2_Create,
    (process_method_func)daNpc_Kg2_Delete,
    (process_method_func)daNpc_Kg2_Execute,
    (process_method_func)daNpc_Kg2_IsDelete,
    (process_method_func)daNpc_Kg2_Draw,
};

actor_process_profile_definition g_profile_NPC_KG2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KG2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kg2_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KG2_e,
    /* Actor SubMtd */ &l_daNpc_Kg2_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_12_e,
};
