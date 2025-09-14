/**
 * d_a_npc_bmsw.cpp
 * NPC - Koboli (Rito mail sorter)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_bmsw.h"
#include "d/res/res_bmsw.h"
#include "d/d_shop.h"
#include "d/d_snap.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "SSystem/SComponent/c_angle.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_hostIO.h"

class daNpc_Bmsw_HIO_c : public JORReflexible {
public:
    daNpc_Bmsw_HIO_c();
    virtual ~daNpc_Bmsw_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x05[0x08 - 0x05];
    /* 0x08 */ dNpc_HIO_c mNpc;
    /* 0x30 */ s16 field_0x30;
    /* 0x32 */ s16 field_0x32;
    /* 0x34 */ s16 field_0x34;
    /* 0x36 */ s16 r_1;
    /* 0x38 */ s16 g_1;
    /* 0x3A */ s16 b_1;
    /* 0x3C */ s16 r_2;
    /* 0x3E */ s16 g_2;
    /* 0x40 */ s16 b_2;
    /* 0x42 */ u8 field_0x42[0x44 - 0x42];
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
};  // Size: 0x58

daNpc_Bmsw_HIO_c l_HIO;


static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
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

/* 000000EC-000001E4       .text __ct__16daNpc_Bmsw_HIO_cFv */
daNpc_Bmsw_HIO_c::daNpc_Bmsw_HIO_c() {
    mNpc.m04 = -20.0f;
    mNpc.mMaxHeadX = 0x1FFE;
    mNpc.mMaxHeadY = 3000;
    mNpc.mMaxBackboneX = 0;
    mNpc.mMaxBackboneY = 0x1C70;
    mNpc.mMinHeadX = -0x9C4;
    mNpc.mMinHeadY = -3000;
    mNpc.mMinBackboneX = 0;
    mNpc.mMinBackboneY = -0x1C70;
    mNpc.mMaxTurnStep = 0x1000;
    mNpc.mMaxHeadTurnVel = 0x800;
    mNpc.mAttnYOffset = 50.0f;
    mNpc.mMaxAttnAngleY = 0x2000;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 300.0f;

    field_0x30 = 0x1E;
    field_0x32 = 0xF;
    field_0x34 = 0x3C;
    r_1 = 192;
    g_1 = 174;
    b_1 = 192;
    r_2 = 192;
    g_2 = 174;
    b_2 = 192;
    field_0x44 = 40.0f;
    field_0x48 = 80.0f;
    field_0x4C = 50.0f;
    field_0x50 = 0.8f;
    field_0x54 = 0.75f;
    mNo = -1;
}


static const s32 l_bck_ix_tbl[] = {
    BMSW_BCK_BM_WAIT01, BMSW_BCK_BM_WAIT02, BMSW_BCK_BM_TALK01, BMSW_BCK_BM_TALK02,
    BMSW_BCK_BM_TALK03, BMSW_BCK_BM_SHIWAKE01, BMSW_BCK_BM_SHIWAKE02,
};
static const s32 l_arm_bck_ix_tbl[] = {
    BMSW_BCK_BMARM_WAIT01, BMSW_BCK_BMARM_WAIT02, BMSW_BCK_BMARM_TALK01, BMSW_BCK_BMARM_TALK02,
    BMSW_BCK_BMARM_TALK03, BMSW_BCK_BMARM_SHIWAKE01, BMSW_BCK_BMARM_SHIWAKE02,
};

static const u32 l_btp_ix_tbl[] = {BMSW_BTP_BMHEAD11, BMSW_BTP_BMHEAD11};


/* 000001E4-000003FC       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Bmsw_c* i_this = (daNpc_Bmsw_c*)model->getUserArea();

        if (i_this != NULL) {
            static cXyz a_att_pos_offst(0.0f, 0.0f, 0.0f);
            static cXyz a_eye_pos_offst(26.0f, 26.0f, 0.0f);

            u16 jointNo = joint->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jointNo));

            if (jointNo == i_this->m_neck_jnt_num) {
                mDoMtx_stack_c::XrotM(i_this->m_jnt.getHead_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getHead_x());
            } else if (jointNo == i_this->m_jnt.getHeadJntNum()) {
                mDoMtx_stack_c::multVec(&a_att_pos_offst, &i_this->getAttentionBasePos());
                mDoMtx_stack_c::multVec(&a_eye_pos_offst, &i_this->eyePos);
            } else if (jointNo == i_this->m_jnt.getBackboneJntNum()) {
                mDoMtx_stack_c::XrotM(i_this->m_jnt.getBackbone_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getBackbone_x());
            } else if (jointNo == i_this->m_body_ArmL) {
                cMtx_copy(mDoMtx_stack_c::get(), i_this->getArmLMtx());
            } else if (jointNo == i_this->m_body_ArmR) {
                cMtx_copy(mDoMtx_stack_c::get(), i_this->getArmRMtx());
            }

            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jointNo, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 00000438-00000550       .text nodeCallBackArm__FP7J3DNodei */
static BOOL nodeCallBackArm(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Bmsw_c* i_this = (daNpc_Bmsw_c*)model->getUserArea();

        if (i_this != NULL) {
            static cXyz a_eff_pos_offst(0.0f, 0.0f, 0.0f);
            u16 jointNo = joint->getJntNo();

            mDoMtx_stack_c::copy(model->getAnmMtx(jointNo));
            if (jointNo == i_this->m_ArmL) {
                cMtx_copy(i_this->getArmLMtx(), J3DSys::mCurrentMtx);
                model->setAnmMtx(jointNo, i_this->getArmLMtx());
            } else if (jointNo == i_this->m_ArmR) {
                cMtx_copy(i_this->getArmRMtx(), J3DSys::mCurrentMtx);
                model->setAnmMtx(jointNo, i_this->getArmRMtx());
            }
        }
    }
    return TRUE;
}

/* 00000550-000006F4       .text daNpc_Bmsw_getGameEndMsg__Fs */
static u32 daNpc_Bmsw_getGameEndMsg(short rupees) {
    u8 reg_val = dComIfGs_getEventReg(0xC203);
    u32 msgNo;
    switch (reg_val) {
        case 0:
            if (rupees == 0) {
                msgNo = 0x1A3A;
            } else if (rupees == 1) {
                msgNo = 0x1A3B;
            } else if (rupees < 10) {
                msgNo = 0x1A3C;
            } else {
                msgNo = 0x1A37;
            }
            break;
        case 1:
            if (rupees == 0) {
                msgNo = 0x1A4F;
            } else if (rupees == 1) {
                msgNo = 0x1A50;
            } else if (rupees < 20) {
                msgNo = 0x1A52;
            } else {
                msgNo = 0x1A4C;
            }
            break;
        case 2:
            if (rupees == 0) {
                msgNo = 0x1A5C;
            } else if (rupees == 1) {
                msgNo = 0x1A5D;
            } else if (rupees < 25) {
                msgNo = 0x1A60;
            } else {
                msgNo = 0x1A57;
            }
            break;
        case 3:
        default:
            if (dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701)) {
                if (rupees == 0) {
                    msgNo = 0x1A69;
                } else if (rupees == 1) {
                    msgNo = 0x1A6A;
                } else if (rupees <= dComIfGs_getEventReg(0x8AFF)) {
                    msgNo = 0x1A6B;
                } else {
                    dComIfGs_setEventReg(0x8AFF, rupees);
                    msgNo = 0x1A6D;
                }
            } else {
                msgNo = 0x1A62;
            }
            break;
    }
    return msgNo;
}

/* 000006F4-00000808       .text initTexPatternAnm__12daNpc_Bmsw_cFb */
BOOL daNpc_Bmsw_c::initTexPatternAnm(bool i_modify) {
    J3DModelData* modelData = field_0x6D4->getModelData();

    m_head_tex_pattern = (J3DAnmTexPattern*) dComIfG_getObjectIDRes("Bmsw", (u16)l_btp_ix_tbl[field_0x9D4]);
    JUT_ASSERT(385, m_head_tex_pattern != NULL);

    if (!field_0x7F8.init(modelData, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        return FALSE;
    }
    field_0x80C = 0;
    field_0x964 = 0;
    return TRUE;
}

/* 00000808-00000894       .text playTexPatternAnm__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::playTexPatternAnm() {
    if (cLib_calcTimer(&field_0x964) == 0) {
        if (field_0x80C >= m_head_tex_pattern->getFrameMax()) {
            field_0x80C -= m_head_tex_pattern->getFrameMax();
            field_0x964 = cM_rndF(100.0f) + 30.0f;
        } else {
            field_0x80C++;
        }
    }
}

/* 00000894-00000984       .text setAnm__12daNpc_Bmsw_cFSc */
void daNpc_Bmsw_c::setAnm(signed char idx) {
    static u32 a_play_mode_tbl[] = {
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
    };
    static f32 a_morf_frame_tbl[] = {8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f};
    static f32 a_play_speed_tbl[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

    if (idx != field_0x9D5) {
        field_0x9D5 = idx;

        dNpc_setAnmIDRes(mpMorf,
            a_play_mode_tbl[field_0x9DA],
            a_morf_frame_tbl[field_0x9DA],
            a_play_speed_tbl[field_0x9DA],
            l_bck_ix_tbl[field_0x9D5],
            -1,
            "Bmsw"
        );
        dNpc_setAnmIDRes(mpMorfHand,
            a_play_mode_tbl[field_0x9DA],
            a_morf_frame_tbl[field_0x9DA],
            a_play_speed_tbl[field_0x9DA],
            l_arm_bck_ix_tbl[field_0x9D5],
            -1,
            "Bmsw"
        );
    }
}

/* 00000984-00000AD8       .text chkAttention__12daNpc_Bmsw_cF4cXyzs */
bool daNpc_Bmsw_c::chkAttention(cXyz pos, short angle) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    f32 maxAttnDistXZ = l_HIO.mNpc.mMaxAttnDistXZ;
    int maxAttnAngleY = l_HIO.mNpc.mMaxAttnAngleY;

    cXyz delta;
    delta.x = player->current.pos.x - pos.x;
    delta.z = player->current.pos.z - pos.z;
    f32 distXZ = std::sqrtf(delta.x*delta.x + delta.z*delta.z);
    s16 targetAngleY = cM_atan2s(delta.x, delta.z);
    if (mHasAttention) {
        maxAttnDistXZ += 40.0f;
        maxAttnAngleY += cAngle::d2s(10.0f);
    }
    targetAngleY -= angle;
    return maxAttnAngleY > abs(targetAngleY) && maxAttnDistXZ > distXZ;
}

/* 00000AD8-00000B28       .text eventOrder__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::eventOrder() {
    if (field_0x9D7 == 1 || field_0x9D7 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (field_0x9D7 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00000B28-00000B68       .text checkOrder__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        return;
    }
    if (!eventInfo.checkCommandTalk()) {
        return;
    }
    if (field_0x9D7 != 1 && field_0x9D7 != 2) {
        return;
    }
    field_0x9D7 = 0;
    field_0x9B9 = 1;
}

/* 00000B68-00000EF8       .text next_msgStatus__12daNpc_Bmsw_cFPUl */
u16 daNpc_Bmsw_c::next_msgStatus(unsigned long* currMsgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;

    switch (*currMsgNo) {
        case 0x1A2D:
        case 0x1A31:
        case 0x1A32:
        case 0x1A35:
        case 0x1A37:
        case 0x1A41:
        case 0x1A42:
        case 0x1A47:
        case 0x1A4A:
        case 0x1A4C:
        case 0x1A50:
        case 0x1A55:
        case 0x1A57:
        case 0x1A59:
        case 0x1A5A:
        case 0x1A5D:
        case 0x1A67:
        case 0x1A6D:
        case 0x1A6E:
            (*currMsgNo)++;
            break;
        case 0x1A63:
        case 0x1A66:
            *currMsgNo = 0x1A64;
            break;
        case 0x1A6A:
        case 0x1A6B:
            *currMsgNo = 0x1A6C;
            break;
        case 0x1A52:
            if (dComIfGp_getMiniGameRupee() < 15) {
                *currMsgNo = 0x1A51;
            } else {
                *currMsgNo = 0x1A53;
            }
            break;
        case 0x1A60:
            if (dComIfGp_getMiniGameRupee() < 20) {
                *currMsgNo = 0x1A5E;
            } else {
                *currMsgNo = 0x1A61;
            }
            break;
        case 0x1A2E:
            if (mpCurrMsg->mSelectNum == 0) {
                dComIfGs_onEventBit(dSv_evtBit_c::UNK_1A01);
                *currMsgNo = 0x1A31;
            } else if (mpCurrMsg->mSelectNum == 1) {
                if (dComIfGs_isStageBossEnemy(dSv_save_c::STAGE_DRC)) {
                    *currMsgNo = 0x1A2F;
                } else {
                    *currMsgNo = 0x1A30;
                }
            }
            break;
        case 0x1A33:
            if (mpCurrMsg->mSelectNum == 0) {
                *currMsgNo = 0x1A35;
            } else if (mpCurrMsg->mSelectNum == 1) {
                *currMsgNo = 0x1A34;
            }
            break;
        case 0x1A34:
            if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_1A01)) {
                *currMsgNo = 0x1A32;
            } else {
                *currMsgNo = 0x1A42;
            }
            break;
        case 0x1A38:
            (*currMsgNo)++;
            dComIfGs_setEventReg(0xC203, 1);
            break;
        case 0x1A3D:
            if (mpCurrMsg->mSelectNum == 0) {
                dComIfGs_onEventBit(dSv_evtBit_c::UNK_1A01);
                *currMsgNo = 0x1A31;
            } else {
                *currMsgNo = 0x1A3E;
            }
            break;
        case 0x1A4D:
            dComIfGs_setEventReg(0xC203, 2);
            // fallthrough
        case 0x1A51:
        case 0x1A53:
            *currMsgNo = 0x1A4E;
            break;
        case 0x1A58:
            dComIfGs_setEventReg(0xC203, 3);
            (*currMsgNo)++;
            break;
        case 0x1A5E:
        case 0x1A61:
            *currMsgNo = 0x1A5F;
            break;
        case 0x1A3F:
            if (mpCurrMsg->mSelectNum == 0) {
                *currMsgNo = 0x1A41;
            } else {
                *currMsgNo = 0x1A40;
            }
            break;
        case 0x1A43:
            if (mpCurrMsg->mSelectNum == 0) {
                *currMsgNo = 0x1A35;
            } else {
                *currMsgNo = 0x1A34;
            }
            break;
        case 0x1A44:
            if (mpCurrMsg->mSelectNum == 0) {
                *currMsgNo = 0x1A46;
            } else {
                *currMsgNo = 0x1A45;
            }
            break;
        case 0x1A46:
            if (mpCurrMsg->mSelectNum == 0) {
                *currMsgNo = 0x1A4A;
            } else {
                *currMsgNo = 0x1A47;
            }
            break;
        case 0x1A48:
            if (mpCurrMsg->mSelectNum == 0) {
                *currMsgNo = 0x1A4A;
            } else {
                *currMsgNo = 0x1A49;
            }
            break;
        case 0x1A49:
            *currMsgNo = 0x1A47;
            break;
        case 0x1A54:
            if (mpCurrMsg->mSelectNum == 0) {
                *currMsgNo = 0x1A55;
            } else {
                *currMsgNo = 0x1A45;
            }
            break;
        case 0x1A64:
            if (mpCurrMsg->mSelectNum == 0) {
                *currMsgNo = 0x1A67;
            } else {
                *currMsgNo = 0x1A65;
            }
            break;
        default:
            ret = fopMsgStts_MSG_ENDS_e;
            break;
    }

    return ret;
}

/* 00000EF8-0000102C       .text getMsg__12daNpc_Bmsw_cFv */
u32 daNpc_Bmsw_c::getMsg() {
    u32 msg = field_0x9C0;

    if (field_0x9C0 != fpcM_ERROR_PROCESS_ID_e) {
        field_0x9C0 = fpcM_ERROR_PROCESS_ID_e;
    } else {
        if (dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701)) {
            if (!dComIfGs_isTmpBit(800)) {
                dComIfGs_onTmpBit(800);
                msg = 0x1A63;
            } else {
                msg = 0x1A66;
            }
        } else {
            if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_1A02)) {
                dComIfGs_onEventBit(dSv_evtBit_c::UNK_1A02);
                msg = 0x1A2D;
            } else {
                if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_1A01)) {
                    msg = 0x1A3D;
                } else {
                    u8 reg = dComIfGs_getEventReg(0xC203);
                    switch (reg) {
                        case 0:
                            msg = 0x1A3F;
                            break;
                        case 1:
                            msg = 0x1A44;
                            break;
                        case 2:
                            msg = 0x1A54;
                            break;
                        case 3:
                        default:
                            msg = 0x1A62;
                    }
                }
            }
        }
    }

    return msg;
}

/* 0000102C-000010C0       .text anmAtr__12daNpc_Bmsw_cFUs */
void daNpc_Bmsw_c::anmAtr(unsigned short mesgNo) {
    switch (dComIfGp_getMesgAnimeAttrInfo()) {
        case 5:
            setAnm(1);
            break;
        case 6:
            setAnm(2);
            break;
        case 9:
            setAnm(3);
            break;
        case 14:
            setAnm(4);
            break;
    }

    dComIfGp_clearMesgAnimeAttrInfo();
}

/* 000010C0-00001340       .text CreateInit__12daNpc_Bmsw_cFv */
BOOL daNpc_Bmsw_c::CreateInit() {
    field_0x97E = current.angle;

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAA;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xAA;

    gravity = -30.0f;
    setAction(&daNpc_Bmsw_c::wait_action, NULL);

    mAttPos = current.pos;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);

    setCollision(60.0f, 150.0f);

    field_0x9C4 = 0;
    mEventCut.setActorInfo2("Bmsw", this);
    field_0x962 = 0;
    field_0x963 = 0;
    field_0x9C0 = fpcM_ERROR_PROCESS_ID_e;
    field_0x988.setWaitParm(5, 2, 3, 2, 1.0, 0.9, 0, 0x2000);
    set_mtx();

    mpMorf->calc();
    mpMorfHand->calc();

    dKy_tevstr_init(&field_0x6E0, home.roomNo, 0xFF);
    if (dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701)) {
        field_0x9E0 = fopAcM_createChild(
            "Btsw",
            fopAcM_GetID(this),
            fopAcM_GetParam(this),
            &current.pos,
            fopAcM_GetRoomNo(this),
            &current.angle
        );
        *fopAcM_GetOldPosition_p(this) = cXyz(120.0f, 700.0f, 810.0f);
        current.pos = *fopAcM_GetOldPosition_p(this);
    } else {
        field_0x9E0 = fpcM_ERROR_PROCESS_ID_e;
    }

    return TRUE;
}

/* 00001340-00001508       .text set_mtx__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::set_mtx() {
    J3DModel* model = mpMorf->getModel();

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);

    model->setBaseTRMtx(mDoMtx_stack_c::get());
    field_0x6D4->setBaseTRMtx(model->getAnmMtx(m_jnt.getHeadJntNum()));
    field_0x6D8->setBaseTRMtx(model->getAnmMtx(m_jnt.getBackboneJntNum()));

    if (field_0x9D5 == 6 || field_0x9D5 == 5) {
        if ((field_0x9D5 == 5 && mpMorfHand->getFrame() < 18.0f) || (field_0x9D5 == 6 && mpMorfHand->getFrame() < 18.0f)) {
            mDoMtx_stack_c::copy(mpMorfHand->getModel()->getAnmMtx(m_handR));
            mDoMtx_stack_c::transM(24.77f, -3.73f, 22.69f);
            mDoMtx_stack_c::XYZrotM(0x45B4, -0x2BE7, 0xE6C);
        } else {
            mDoMtx_stack_c::copy(mpMorfHand->getModel()->getAnmMtx(m_handL));
            mDoMtx_stack_c::transM(26.18f, 8.72f, 18.55f);
            mDoMtx_stack_c::XYZrotM(0x5065, 0x28A0, -0x7F80);
        }
        field_0x6DC->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 00001508-00001534       .text setAttention__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::setAttention() {
    attention_info.position.set(mAttPos.x, mAttPos.y + l_HIO.mNpc.mAttnYOffset, mAttPos.z);
}

/* 00001534-000016EC       .text lookBack__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::lookBack() {
    cXyz vec2;
    cXyz vec(0.0f, 0.0f, 0.0f);

    cXyz* dstPos = NULL;
    s16 desired_y_rot = current.angle.y;

    switch (field_0x9DA) {
        case 1:
        case 2:
            if (mHasAttention) {
                vec2 = dNpc_playerEyePos(l_HIO.mNpc.m04);
                dstPos = &vec2;

                vec = current.pos;
                vec.y = eyePos.y;
            } else {
                if (dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701) && field_0x9E0 != fpcM_ERROR_PROCESS_ID_e) {
                    fopAc_ac_c* ac = fopAcM_SearchByID(field_0x9E0);
                    if (ac != NULL) {
                        vec2 = ac->eyePos;
                        dstPos = &vec2;

                        vec = current.pos;
                        vec.y = eyePos.y;
                    }
                }
            }
    }

    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&field_0x97A, l_HIO.mNpc.mMaxHeadTurnVel, 4, 0x800);
    } else {
        field_0x97A = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstPos, vec, desired_y_rot, field_0x97A, true);
}

/* 000016EC-0000184C       .text wait01__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::wait01() {
    if (field_0x9B9) {
        field_0x9DA = 2;
        m_jnt.offHeadLock();
        m_jnt.offBackBoneLock();
    } else {
        if (mHasAttention) {
            field_0x9D7 = 2;
        }

        if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701)) {
            if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
                if (--field_0x9D6 <= 0) {
                    if (field_0x9D5 == 5) {
                        field_0x9D6 = 1;
                        setAnm(6);
                    } else {
                        field_0x9D6 = cM_rndF(4.0f) + 2.0f;
                        setAnm(5);
                    }
                }
            }

            if (field_0x9D5 == 5 || field_0x9D5 == 6) {
                m_jnt.onHeadLock();
                m_jnt.onBackBoneLock();
            } else {
                m_jnt.offHeadLock();
                m_jnt.offBackBoneLock();
            }
        }
    }
}

/* 0000184C-00001A84       .text talk01__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::talk01() {
    u16 talk_res = talk(1);
    if (dComIfGp_checkMesgSendButton() == 1) {
        if (mCurrMsgNo == 0x1A32 || mCurrMsgNo == 0x1A42 || mCurrMsgNo == 0x1A47 || mCurrMsgNo == 0x1A4A
                || mCurrMsgNo == 0x1A55 || mCurrMsgNo == 0x1A67) {
            mSwCam.ActiveOn();
        } else if (mCurrMsgNo == 0x1A39 || mCurrMsgNo == 0x1A4E || mCurrMsgNo == 0x1A5F || mCurrMsgNo == 0x1A59 || mCurrMsgNo == 0x1A6F) {
            dComIfGp_setItemRupeeCount(field_0x960);
        }
    }

    if (talk_res == fopMsgStts_BOX_CLOSED_e) {
        field_0x9DA = 1;
        dComIfGp_event_reset();

        if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701)) {
            setAnm(0);
        } else {
            setAnm(1);
        }
        field_0x9D6 = 1;
        field_0x9B9 = 0;

        if (mCurrMsgNo == 0x1A36 || mCurrMsgNo == 0x1A4B || mCurrMsgNo == 0x1A56 || mCurrMsgNo == 0x1A68) {
            setAction(&daNpc_Bmsw_c::shiwake_game_action, NULL);
        }
    }
}

/* 00001A84-00001BA4       .text wait_action__12daNpc_Bmsw_cFPv */
BOOL daNpc_Bmsw_c::wait_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        field_0x9DA = 1;
        field_0x9D6 = 1;
        if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701)) {
            setAnm(FALSE);
        } else {
            setAnm(TRUE);
        }
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        s16 angle = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        mHasAttention = chkAttention(current.pos, angle);
        field_0x9D7 = 0;

        switch (field_0x9DA) {
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
    return TRUE;
}

/* 00001BA4-00001C70       .text checkNextMailThrowOK__12daNpc_Bmsw_cFv */
BOOL daNpc_Bmsw_c::checkNextMailThrowOK() {
    u8 mailIdx = field_0x93C;
    if (mailIdx < 2) {
        mailIdx++;
    } else {
        mailIdx = 0;
    }
    u8 ret = 1;

    if (field_0x930[mailIdx]->CheckProc(&SwMail_c::Dummy) == FALSE) {
        if (field_0x930[mailIdx]->CheckProc(&SwMail_c::End) == FALSE) {
            ret = 0;
        }
    }
    return ret;
}

/* 00001C70-00001DA4       .text setGameGetRupee__12daNpc_Bmsw_cFs */
void daNpc_Bmsw_c::setGameGetRupee(short rupees) {
    u8 reg_val = dComIfGs_getEventReg(0xC203);
    switch (reg_val) {
        case 0:
            if (rupees < 10) {
                field_0x960 = 0;
            } else {
                // Does not match with `rupees / 2`, maybe hand-optimized?
                field_0x960 = rupees >> 1;
            }
            break;
        case 1:
            if (rupees < 15) {
                field_0x960 = 0;
            } else if (rupees < 20) {
                field_0x960 = rupees >> 1;
            } else {
                field_0x960 = rupees;
            }
            break;
        case 2:
            if (rupees < 20) {
                field_0x960 = 0;
            } else if (rupees < 25) {
                field_0x960 = rupees;
            } else {
                field_0x960 = rupees * 3;
            }
            break;
        case 3:
        default:
            if (dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701)) {
                field_0x960 = rupees;
            } else {
                field_0x960 = rupees * 3;
            }
            break;
    }

    dComIfGp_setMessageCountNumber(field_0x960);
}

/* 00001DA4-00001E88       .text TimerCountDown__12daNpc_Bmsw_cFv */
void daNpc_Bmsw_c::TimerCountDown() {
    if (field_0x9B4 > dComIfG_getTimerRestTimeMs()) {
        if (field_0x9B4 <= 10000) {
            mDoAud_seStart(JA_SE_MINIGAME_TIMER_30);
            field_0x9B4 -= 1000;
        } else {
            mDoAud_seStart(JA_SE_MINIGAME_TIMER_10);
            field_0x9B4 -= 10000;
        }
    }
}

/* 00001E88-00002950       .text shiwake_game_action__12daNpc_Bmsw_cFPv */
BOOL daNpc_Bmsw_c::shiwake_game_action(void*) {
    static cXyz aim_pos_data[2][3] = {
        cXyz(-40.0f, 772.0f, 1035.0f),
        cXyz(-139.0f, 772.0f, 1035.0f),
        cXyz(-240.0f, 772.0f, 1035.0f),
        cXyz(-40.0f, 855.0f, 1035.0f),
        cXyz(-139.0f, 855.0f, 1035.0f),
        cXyz(-240.0f, 855.0f, 1035.0f)
    };
    static cXyz cursor_pos_data[2][3] = {
        cXyz(-52.0f, 804.0f, 996.0f),
        cXyz(-140.0f, 804.0f, 996.0f),
        cXyz(-227.0f, 804.0f, 996.0f),
        cXyz(-52.0f, 889.0f, 996.0f),
        cXyz(-140.0f, 889.0f, 996.0f),
        cXyz(-227.0f, 889.0f, 996.0f)
    };

    if (mActionStatus == ACTION_STARTING) {
        field_0x9DA = 3;
        field_0x9B0 = 0;
        field_0x9B1 = 0;

        if (!eventInfo.checkCommandDemoAccrpt()) {
            if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701)) {
                field_0x9D8 = dComIfGp_evmng_getEventIdx("SHIWAKEGAME");
            } else {
                field_0x9D8 = dComIfGp_evmng_getEventIdx("SHIWAKEGAME2");
            }

            fopAcM_orderOtherEventId(this, field_0x9D8);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
            return FALSE;
        }

        if (!field_0x962) {
            dTimer_createTimer(6, l_HIO.field_0x30, 3, 4, 221.0f, l_HIO.field_0x48, 32.0f, l_HIO.field_0x4C);
            field_0x962 = 1;

            dComIfGp_setMiniGameRupee(0);
            dComIfGp_startMiniGame(7);
        }

        if (dComIfG_getTimerPtr() == NULL) {
            return FALSE;
        }
        // Possibly wrong inline for dComIfG_TimerStart here.
        dComIfG_TimerStart(6, l_HIO.field_0x32);

        field_0x963 = 1;
        field_0x930[0]->init();
        field_0x930[0]->AppearInit();
        field_0x930[1]->init();
        field_0x930[1]->DummyInit();
        field_0x930[2]->init();
        field_0x930[2]->DummyInit();
        field_0x93C = 0;
        mActionStatus++;

        mpShopCursor->setPos(cursor_pos_data[field_0x9B1][1 + field_0x9B0]);
        mpShopCursor->show();
        field_0x9B4 = 20000;
    } else if (mActionStatus == ACTION_ENDING) {
        field_0x962 = 0;
        field_0x963 = 0;
    } else {
        if (dComIfG_getTimerRestTimeMs() > 0) {
            TimerCountDown();

            field_0x988.checkTrigger();
            if (field_0x9B0 > -1 && field_0x988.checkLeftTrigger()) {
                mDoAud_seStart(JA_SE_LETTER_GAME_CURSOR);
                field_0x9B0--;
            } else if (field_0x9B0 < 1 && field_0x988.checkRightTrigger()) {
                mDoAud_seStart(JA_SE_LETTER_GAME_CURSOR);
                field_0x9B0++;
            }

            if (field_0x9B1 < 1 && field_0x988.checkUpTrigger()) {
                mDoAud_seStart(JA_SE_LETTER_GAME_CURSOR);
                field_0x9B1++;
            } else if (field_0x9B1 > 0 && field_0x988.checkDownTrigger()) {
                mDoAud_seStart(JA_SE_LETTER_GAME_CURSOR);
                field_0x9B1--;
            }

            if (field_0x930[field_0x93C]->CheckProc(&SwMail_c::Wait)
                        && dComIfG_getTimerPtr()->getStatus() != 1 && CPad_CHECK_TRIG_A(0)
                        && checkNextMailThrowOK()) {

                s32 row = field_0x9B0 + 1;
                u8 col = field_0x9B1;
                u8 idx = row + (1 - col) * 3;

                cXyz& aim_pos = aim_pos_data[field_0x9B1][row];
                field_0x930[field_0x93C]->ThrowInit(
                    aim_pos,
                    idx
                );

                if (field_0x93C < 2) {
                    field_0x93C++;
                } else {
                    field_0x93C = 0;
                }

                mDoAud_seStart(JA_SE_LETTER_GAME_OK);
                field_0x930[field_0x93C]->AppearInit();
            }

            mSwCam.setAimIdx(field_0x9B0, field_0x9B1);

            mpShopCursor->setPos(cursor_pos_data[field_0x9B1][1 + field_0x9B0]);
            mpShopCursor->setScale(0.65f, 0.9f, 0.5f, 27.0f, 20.0f);
            mpShopCursor->anm_play();
        } else {
            if (mActionStatus == ACTION_ONGOING) {
                mDoAud_seStart(JA_SE_LETTER_GAME_TIMER_0);

                dComIfG_getTimerPtr()->end(l_HIO.field_0x34);

                mpShopCursor->hide();
                mActionStatus++;
            } else if (mActionStatus == ACTION_UNK_2) {
                if (dComIfG_getTimerPtr()->deleteCheck()) {
                    dComIfG_getTimerPtr()->deleteRequest();
                    mActionStatus++;
                }
            } else if (dComIfG_getTimerPtr() == NULL) {
                s32 staff_id = dComIfGp_evmng_getMyStaffId("Bmsw");
                dComIfGp_evmng_cutEnd(staff_id);

                if (dComIfGp_evmng_endCheck(field_0x9D8)) {
                    dComIfGp_event_onEventFlag(8);
                    s16 rupees = dComIfGp_getMiniGameRupee();
                    fpc_ProcID msg = daNpc_Bmsw_getGameEndMsg(rupees);
                    field_0x9C0 = msg;

                    setGameGetRupee(rupees);
                    field_0x9D7 = 1;

                    setAction(&daNpc_Bmsw_c::wait_action, NULL);

                    mSwCam.ActiveOff();
                    if (dComIfGp_getMiniGameType() == 7) {
                        dComIfGp_endMiniGame(7);
                    }
                }
            }
        }
        field_0x930[0]->move();
        field_0x930[1]->move();
        field_0x930[2]->move();
    }

    return TRUE;
}

/* 00002950-00002B24       .text _draw__12daNpc_Bmsw_cFv */
BOOL daNpc_Bmsw_c::_draw() {
    GXColor unused[] = {
        {0xFF, 0x00, 0x00, 0x80},
        {0x00, 0x00, 0xFF, 0x80},
    }; // Unused colors, needed for the .rodata section to match.

    J3DModel* model = mpMorf->getModel();
    J3DModelData* unkModelData = field_0x6D4->getModelData();
    J3DModel* handModel = mpMorfHand->getModel();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);
    g_env_light.setLightTevColorType(field_0x6D4, &tevStr);
    g_env_light.setLightTevColorType(field_0x6D8, &tevStr);
    g_env_light.setLightTevColorType(handModel, &tevStr);

    field_0x7F8.entry(unkModelData, field_0x80C);
    mpMorf->entryDL();
    mpMorfHand->entryDL();
    mDoExt_modelUpdateDL(field_0x6D4);
    mDoExt_modelUpdateDL(field_0x6D8);

    if (field_0x9D5 == 5 || field_0x9D5 == 6) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &field_0x6E0);

        field_0x6E0.mColorK0.r = l_HIO.r_1;
        field_0x6E0.mColorK0.g = l_HIO.g_1;
        field_0x6E0.mColorK0.b = l_HIO.b_1;
        field_0x6E0.mColorC0.r = l_HIO.r_2;
        field_0x6E0.mColorC0.g = l_HIO.g_2;
        field_0x6E0.mColorC0.b = l_HIO.b_2;

        g_env_light.setLightTevColorType(field_0x6DC, &field_0x6E0);
        mDoExt_modelUpdateDL(field_0x6DC);
    }

    field_0x7F8.remove(unkModelData);
    if (field_0x963 != 0) {
        for (s32 i = 0; i < 3; i++) {
            field_0x930[i]->draw(&tevStr);
        }
    }

    mpShopCursor->draw();
    dSnap_RegistFig(DSNAP_TYPE_BMSW, this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00002B24-00002CA4       .text _execute__12daNpc_Bmsw_cFv */
BOOL daNpc_Bmsw_c::_execute() {
    m_jnt.setParam(
        l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY,
        l_HIO.mNpc.mMinBackboneX, l_HIO.mNpc.mMinBackboneY,
        l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY,
        l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY,
        l_HIO.mNpc.mMaxTurnStep);
    field_0x988.setWaitParm(5, 2, 3, 2, l_HIO.field_0x50, l_HIO.field_0x54, 0, 0x2000);

    playTexPatternAnm();

    mpMorf->play(&eyePos, 0, 0);
    mpMorf->calc();
    mpMorfHand->play(NULL, 0, 0);
    mpMorfHand->calc();

    checkOrder();

    if (!mEventCut.cutProc()) {
        (this->*mCurrActionFunc)(NULL);
    }
    mSwCam.Move();
    eventOrder();

    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mObjAcch.CrrPos(*dComIfG_Bgsp());

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    set_mtx();
    setCollision(60.0f, 150.0f);
    return TRUE;
}

/* 00002CA4-00002D40       .text _delete__12daNpc_Bmsw_cFv */
BOOL daNpc_Bmsw_c::_delete() {
    dComIfG_resDelete(&mPhs, "Bmsw");

    if (heap != NULL && mpMorf != NULL) {
        mpMorf->stopZelAnime();
    }

    mSwMail0.SeDelete();
    mSwMail1.SeDelete();
    mSwMail2.SeDelete();
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    return TRUE;
}

/* 00002D40-00002D60       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Bmsw_c*)i_this)->CreateHeap();
}

/* 00002D60-00002ECC       .text _create__12daNpc_Bmsw_cFv */
cPhs_State daNpc_Bmsw_c::_create() {
    fopAcM_SetupActor(this, daNpc_Bmsw_c);

    u8 reg_val = dComIfGs_getEventReg(0xC203);
    if (reg_val >= 3 && !dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701)) {
        fopAcM_create(
            "Btsw",
            fopAcM_GetParam(this),
            fopAcM_GetPosition_p(this),
            fopAcM_GetRoomNo(this),
            fopAcM_GetAngle_p(this)
        );
        return cPhs_ERROR_e;
    }

    cPhs_State res = dComIfG_resLoad(&mPhs, "Bmsw");
    if (res == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CallbackCreateHeap, 0xCDA0)) {
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        if (l_HIO.mNo < 0) {
            l_HIO.mNo = mDoHIO_createChild("リト族（仕分けゲーム）", &l_HIO);
        }

        if (!CreateInit()) {
            return cPhs_ERROR_e;
        }
    }
    return res;
}

/* 00003524-00003CB0       .text CreateHeap__12daNpc_Bmsw_cFv */
BOOL daNpc_Bmsw_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*) dComIfG_getObjectIDRes("Bmsw", BMSW_BDL_BM);
    JUT_ASSERT(1499, modelData != NULL);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL,
        NULL,
        (J3DAnmTransform*) dComIfG_getObjectIDRes("Bmsw", BMSW_BCK_BM_TALK01),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        TRUE,
        NULL,
        0,
        0x11020203
    );
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(1513, m_jnt.getHeadJntNum() >= 0);
    m_neck_jnt_num = modelData->getJointName()->getIndex("neck");
    JUT_ASSERT(1515, m_neck_jnt_num >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    m_body_ArmL = modelData->getJointName()->getIndex("armL");
    m_body_ArmR = modelData->getJointName()->getIndex("armR");
    JUT_ASSERT(1519, m_body_ArmL >= 0 || m_body_ArmR >= 0);

    J3DModelData* headModelData = (J3DModelData*) dComIfG_getObjectIDRes("Bmsw", BMSW_BDL_BMHEAD11);
    field_0x6D4 = mDoExt_J3DModel__create(headModelData, 0x80000,0x11020022);
    if (field_0x6D4 == NULL) {
        return FALSE;
    }

    J3DModelData* armModelData = (J3DModelData*) dComIfG_getObjectIDRes("Bmsw", BMSW_BDL_BMARM);
    mpMorfHand = new mDoExt_McaMorf(
        armModelData,
        NULL,
        NULL,
        (J3DAnmTransform*) dComIfG_getObjectIDRes("Bmsw", BMSW_BCK_BMARM_TALK01),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        TRUE,
        NULL,
        0,
        0x11020203
    );
    if (mpMorfHand == NULL || mpMorfHand->getModel() == NULL) {
        return FALSE;
    }

    m_ArmL = armModelData->getJointName()->getIndex("armLloc");
    m_ArmR = armModelData->getJointName()->getIndex("armRloc");
    m_handL = armModelData->getJointName()->getIndex("handL");
    m_handR = armModelData->getJointName()->getIndex("handR");
    JUT_ASSERT(1555, m_ArmL >= 0 || m_ArmR >= 0);
    JUT_ASSERT(1556, m_handL >= 0 || m_handR >= 0);

    J3DModelData* bagModelData = (J3DModelData*) dComIfG_getObjectIDRes("Bmsw", BMSW_BDL_BM_BAG);
    field_0x6D8 = mDoExt_J3DModel__create(bagModelData, 0, 0x11020203);
    if (field_0x6D8 == NULL) {
        return FALSE;
    }

    J3DModelData* letterModelData = (J3DModelData*) dComIfG_getObjectIDRes("Bmsw", BMSW_BDL_BM_LETTER);
    field_0x6DC = mDoExt_J3DModel__create(letterModelData, 0,0x11020203);
    if (field_0x6DC == NULL) {
        return FALSE;
    }

    field_0x9D4 = 0;
    if (!initTexPatternAnm(false)) {
        return FALSE;
    }

    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        if (i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum() ||
                i == m_neck_jnt_num || i == m_body_ArmL || i == m_body_ArmR) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
        }
    }
    for (u16 i = 0; i < armModelData->getJointNum(); i++) {
        if (i == m_ArmR || i == m_ArmL) {
            armModelData->getJointNodePointer(i)->setCallBack(nodeCallBackArm);
        }
    }
    mpMorf->getModel()->setUserArea((u32) this);
    mpMorfHand->getModel()->setUserArea((u32) this);

    field_0x930[0] = &mSwMail0;
    field_0x930[1] = &mSwMail1;
    field_0x930[2] = &mSwMail2;
    field_0x93C = 0;

    cXyz* eyeP = mSwCam.getEyeP();
    cXyz* cameraCenter = mSwCam.getCenterP();
    if (field_0x930[0]->MailCreateInit(eyeP, cameraCenter) == FALSE) {
        return FALSE;
    }
    if (field_0x930[1]->MailCreateInit(eyeP, cameraCenter) == FALSE) {
        return FALSE;
    }
    if (field_0x930[2]->MailCreateInit(eyeP, cameraCenter) == FALSE) {
        return FALSE;
    }

    J3DAnmTevRegKey* tevRegKey = (J3DAnmTevRegKey*) dComIfG_getObjectIDRes("Bmsw", BMSW_BRK_SHOP_CURSOR01);
    J3DModelData* cursorModelData = (J3DModelData*) dComIfG_getObjectIDRes("Bmsw", BMSW_BMD_SHOP_CURSOR01);

    mpShopCursor = ShopCursor_create(cursorModelData, tevRegKey, 0.65f);
    if (mpShopCursor == NULL) {
        return FALSE;
    }
    mpShopCursor->m54 = 0;

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

    return TRUE;
}

/* 00003CB0-00003DBC       .text MailCreateInit__8SwMail_cFP4cXyzP4cXyz */
BOOL SwMail_c::MailCreateInit(cXyz* param_1, cXyz* param_2) {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectIDRes("Bmsw", BMSW_BDL_QMAIL));
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020002);
    if (mpModel == NULL) {
        return FALSE;
    }

    J3DAnmTexPattern* texPattern = (J3DAnmTexPattern*) dComIfG_getObjectIDRes("Bmsw", BMSW_BTP_QMAIL);
    if (!field_0x10.init(modelData, texPattern, TRUE, J3DFrameCtrl::EMode_LOOP, 0.0f, 0, -1, false, FALSE)) {
        return FALSE;
    }

    field_0x58 = param_1;
    field_0x5C = param_2;
    field_0x54 = 0;
    init();
    DummyInit();

    return TRUE;
}

/* 00003DBC-00003FE8       .text getNextNo__8SwMail_cFUc */
u8 SwMail_c::getNextNo(unsigned char previous_no) {
    f32 random = cM_rndF(10.0f);
    f32 fVar4 = 2.5f - (m_same_count * 1.25f);

    s32 box_y = previous_no % 3;
    s32 box_x = previous_no / 3;

    if (random < fVar4) {
        m_same_count++;
    } else {
        f32 new_threshold = fVar4 + 2.5f;
        if (random < new_threshold) {
            if (cM_rndF(1.0f) > 0.5f) {
                if (box_y == 0 || box_y == 2) {
                    box_y = 1;
                } else if (cM_rndF(1.0f) > 0.5f) {
                    box_y = 0;
                } else {
                    box_y = 2;
                }
            } else {
                box_x = box_x == 0;
            }

            m_same_count = 0;
        } else if (random >= new_threshold) {
            fVar4 = cM_rndF(1.0f);
            if (fVar4 < 0.3333f) {
                if (box_y == 0 || box_y == 2) {
                    box_y = 1;
                } else {
                    if (cM_rndF(1.0f) > 0.5f) {
                        box_y = 0;
                    } else {
                        box_y = 2;
                    }
                }
                box_x = box_x == 0;
            } else if (fVar4 < 0.6666f) {
                if (box_y == 0) {
                    box_y = 2;
                } else if (box_y == 2) {
                    box_y = 0;
                } else {
                    if (cM_rndF(1.0f) > 0.5f) {
                        box_y = 0;
                    } else {
                        box_y = 2;
                    }
                }
            } else {
                if (box_y == 0) {
                    box_y = 2;
                } else if (box_y == 2) {
                    box_y = 0;
                } else {
                    if (cM_rndF(1.0f) > 0.5f) {
                        box_y = 0;
                    } else {
                        box_y = 2;
                    }
                }
                box_x = box_x == 0;
            }
            m_same_count = 0;
        }
    }

    u8 res = box_y + (box_x * 3);
    m_no_buff = res;
    return res;
}

/* 00003FE8-00004074       .text init__8SwMail_cFv */
void SwMail_c::init() {
    field_0x54 = 0;
    field_0x56 = 0;
    field_0x30 = cXyz::Zero;
    field_0x3C = cXyz::Zero;
    field_0x55 = 0;

    field_0x24.set(
        field_0x5C->x,
        field_0x5C->y - 200.0f,
        field_0x5C->z
    );
    set_mtx();
}

/* 00004074-000040F8       .text set_mtx__8SwMail_cFv */
void SwMail_c::set_mtx() {
    mDoMtx_stack_c::transS(
        field_0x24.x + field_0x3C.x,
        field_0x24.y + field_0x3C.y,
        field_0x24.z + field_0x3C.z
    );
    mDoMtx_stack_c::ZXYrotM(field_0x48);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000040F8-00004184       .text set_mtx_throw__8SwMail_cFv */
void SwMail_c::set_mtx_throw() {
    mDoMtx_stack_c::transS(
        field_0x24.x + field_0x3C.x,
        field_0x24.y + field_0x3C.y,
        field_0x24.z + field_0x3C.z
    );
    mDoMtx_stack_c::XrotM(field_0x48.x);
    mDoMtx_stack_c::YrotM(field_0x48.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00004184-0000425C       .text DummyInit__8SwMail_cFv */
void SwMail_c::DummyInit() {
    cLib_targetAngleY(field_0x58, field_0x5C);
    field_0x48.set(0, -0x4000, 0);
    field_0x24.set(field_0x5C->x - 150.0f, field_0x5C->y - 200.0f, field_0x5C->z);

    field_0x54 = getNextNo(field_0x54);
    field_0x4E.set(0, -0x4000, -0x4000);

    field_0x3C = cXyz::Zero;
    SetProc(&SwMail_c::Dummy);
}

/* 0000425C-0000427C       .text Dummy__8SwMail_cFv */
void SwMail_c::Dummy() {
    set_mtx();
}

/* 0000427C-0000438C       .text AppearInit__8SwMail_cFv */
void SwMail_c::AppearInit() {
    cLib_targetAngleY(field_0x58, field_0x5C);
    field_0x48.set(0, -0x4000, 0);
    field_0x24.set(field_0x5C->x, field_0x5C->y - 200.0f, field_0x5C->z);

    field_0x54 = getNextNo(field_0x54);
    field_0x4E.set(0, -0x4000, -0x4000);

    field_0x3C = cXyz::Zero;
    field_0x56 = 0;
    mDoAud_seStart(JA_SE_LETTER_GAME_NEW);
    SetProc(&SwMail_c::Appear);
}

/* 0000438C-000044E8       .text Appear__8SwMail_cFv */
void SwMail_c::Appear() {
    s16 new_y = cLib_targetAngleY(field_0x58, field_0x5C);

    cXyz diff = *field_0x58 - *field_0x5C;
    if (!diff.normalizeRS()) {
        diff.set(0.0f, 0.0f, 1.0f);
    }

    cXyz vec = *field_0x5C;
    diff = diff * 120.0f;
    vec += diff;

    vec.y -= 40.0f;
    field_0x48.x = field_0x4E.x;
    field_0x48.y = field_0x4E.y + new_y;
    cLib_addCalcAngleS2(&field_0x48.z, field_0x4E.z, 4, 0x1000);

    if (std::abs(cLib_addCalcPos(&field_0x24, vec, 0.25f, 30.0f, 2.5f)) < 2.5f) {
        WaitInit();
    }
    set_mtx();
}

/* 000044E8-0000450C       .text WaitInit__8SwMail_cFv */
void SwMail_c::WaitInit() {
    SetProc(&SwMail_c::Wait);
}

/* 0000450C-00004628       .text Wait__8SwMail_cFv */
void SwMail_c::Wait() {
    s16 new_y = cLib_targetAngleY(field_0x58, field_0x5C);

    cXyz diff = *field_0x58 - *field_0x5C;
    if (!diff.normalizeRS()) {
        diff.set(0.0f, 0.0f, 1.0f);
    }

    field_0x24 = *field_0x5C;
    diff = diff * 120.0f;
    field_0x24 += diff;

    field_0x24.y -= 40.0f;
    field_0x48.set(field_0x4E.x, field_0x4E.y + new_y, field_0x4E.z);
    set_mtx();
}

/* 00004628-00004670       .text ThrowInit__8SwMail_cF4cXyzUc */
void SwMail_c::ThrowInit(cXyz param_1, unsigned char param_2) {
    field_0x30 = param_1;
    field_0x56 = 0;
    field_0x55 = param_2;

    SetProc(&SwMail_c::Throw);
}

/* 00004670-00004954       .text Throw__8SwMail_cFv */
void SwMail_c::Throw() {
    if (field_0x56 == 0) {
        s16 x_angle = cLib_targetAngleX(&field_0x30, field_0x5C);
        s16 y_angle = cLib_targetAngleY(field_0x58, field_0x5C);

        cXyz multVec;
        cXyz vec(-40.0f, -50.0f, 0.0f);
        mDoMtx_stack_c::ZXYrotS(x_angle, y_angle, 0);
        mDoMtx_stack_c::multVec(&vec, &multVec);
        multVec += *field_0x5C;

        if (cLib_addCalcPos(&field_0x24, multVec, 0.5f, 30.0f, 2.0f) < 1.0f) {
            field_0x48.y = 0;
            field_0x4E.x = 0;
            mDoAud_seStart(JA_SE_LK_SW_KAZEKIRI_S);
            field_0x56++;
        }

        set_mtx();
    } else {
        s16 x_angle = cLib_targetAngleX(&field_0x30, field_0x5C);
        field_0x48.x = -x_angle;
        s16 new_y = (field_0x54 * 0x80) + 0x1000;
        field_0x48.y += new_y;
        field_0x48.z = 0;

        f32 pos_step = cLib_addCalcPos(&field_0x24, field_0x30, 0.5f, l_HIO.field_0x44, 1.0f);

        field_0x4E.x += 4000;
        field_0x3C.y = (1.0f - cM_scos(field_0x4E.x)) * 20.0f;

        if (pos_step < 1.0f) {
            mDoAud_seStart(JA_SE_LETTER_IN_BOX, &field_0x24);
            if (field_0x55 == field_0x54) {
                dComIfGp_plusMiniGameRupee(1);
                mDoAud_seStart(JA_SE_MINIGAME_RIGHT);
            } else {
                dComIfGp_getVibration().StartShock(3, 0x9, cXyz(0.0f, 1.0f, 0.0f));
                mDoAud_seStart(JA_SE_MINIGAME_WRONG);
            }

            EndInit();
        }

        set_mtx_throw();
    }
}

/* 00004954-000049A0       .text EndInit__8SwMail_cFv */
void SwMail_c::EndInit() {
    field_0x30 = cXyz::Zero;
    field_0x30.z = -10.0f;
    SetProc(&SwMail_c::End);
}

/* 000049A0-00004B34       .text End__8SwMail_cFv */
void SwMail_c::End() {
    if (field_0x55 == field_0x54) {
        cLib_addCalcAngleS2(&field_0x48.y, 0, 4, 0x1000);
        cXyz target = cXyz::Zero;
        cLib_addCalcPos2(&field_0x3C, target, 0.25f, 5.0f);
    } else {
        cLib_addCalcAngleS2(&field_0x48.y, -0x8000, 4, 0x1000);
        cXyz target = cXyz::Zero;
        cLib_addCalcPos2(&field_0x3C, target, 0.25f, 5.0f);

        if (field_0x24.z < 995.0f) {
            s16 target;
            if (field_0x24.y > 720.0f) {
                target = -0x4000;
                field_0x30.y -= 3.0f;
            } else {
                target = 0;
                field_0x30.y *= 0.6f;
                field_0x30.x *= 0.9f;
                field_0x30.z *= 0.9f;
            }

            if (field_0x24.y <= 700.0f) {
                field_0x30.y = 0.0f;
                field_0x24.y = 700.0f;
            }

            cLib_addCalcAngleS2(&field_0x48.x, target, 2, 0x800);
        }
        field_0x30 *= 0.9f;
        field_0x24 += field_0x30;
    }
    set_mtx_throw();
}

/* 00004B34-00004B68       .text SeDelete__8SwMail_cFv */
void SwMail_c::SeDelete() {
    mDoAud_seDeleteObject((Vec*) &field_0x24);
}

/* 00004B68-00004B90       .text move__8SwMail_cFv */
void SwMail_c::move() {
    (this->*mFunc)();
}

/* 00004B90-00004C04       .text draw__8SwMail_cFP12dKy_tevstr_c */
void SwMail_c::draw(dKy_tevstr_c* tevStr) {
    J3DModelData* modelData = mpModel->getModelData();
    field_0x10.entry(modelData, field_0x54);
    g_env_light.setLightTevColorType(mpModel, tevStr);
    mDoExt_modelUpdateDL(mpModel);
    field_0x10.remove(modelData);
}

/* 00004C04-00004D0C       .text Move__7SwCam_cFv */
void SwCam_c::Move() {
    if (field_0x1E != 0) {
        camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
        
        cXyz center = camera_center_data[field_0x1D][field_0x1C + 1];
        cLib_addCalcPos(&field_0x00, center, 0.25f, 10.0f, 1.0f);

        camera->mCamera.Stay();
        camera->mCamera.Set(*getEyeP(), *getCenterP(), field_0x18, 0);
    }
}

/* 00004D0C-00004D2C       .text daNpc_Bmsw_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Bmsw_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Bmsw_c*)i_this)->_create();
}

/* 00004D2C-00004D4C       .text daNpc_Bmsw_Delete__FP12daNpc_Bmsw_c */
static BOOL daNpc_Bmsw_Delete(daNpc_Bmsw_c* i_this) {
    return ((daNpc_Bmsw_c*)i_this)->_delete();
}

/* 00004D4C-00004D6C       .text daNpc_Bmsw_Execute__FP12daNpc_Bmsw_c */
static BOOL daNpc_Bmsw_Execute(daNpc_Bmsw_c* i_this) {
    return ((daNpc_Bmsw_c*)i_this)->_execute();
}

/* 00004D6C-00004D8C       .text daNpc_Bmsw_Draw__FP12daNpc_Bmsw_c */
static BOOL daNpc_Bmsw_Draw(daNpc_Bmsw_c* i_this) {
    return ((daNpc_Bmsw_c*)i_this)->_draw();
}

/* 00004D8C-00004D94       .text daNpc_Bmsw_IsDelete__FP12daNpc_Bmsw_c */
static BOOL daNpc_Bmsw_IsDelete(daNpc_Bmsw_c*) {
    return TRUE;
}

u8 SwMail_c::m_no_buff;
u8 SwMail_c::m_same_count;

cXyz SwCam_c::camera_center_data[2][3] = {
    cXyz(-104.0f, 805.0f, 875.0f),
    cXyz(-139.0f, 805.0f, 882.0f),
    cXyz(-173.0f, 805.0f, 875.0f),
    cXyz(-104.0f, 825.0f, 868.0f),
    cXyz(-139.0f, 825.0f, 875.0f),
    cXyz(-173.0f, 825.0f, 868.0f),
};
cXyz SwCam_c::camera_eye(-139.0f, 815.0f, 662.0f);

static actor_method_class l_daNpc_Bmsw_Method = {
    (process_method_func)daNpc_Bmsw_Create,
    (process_method_func)daNpc_Bmsw_Delete,
    (process_method_func)daNpc_Bmsw_Execute,
    (process_method_func)daNpc_Bmsw_IsDelete,
    (process_method_func)daNpc_Bmsw_Draw,
};

actor_process_profile_definition g_profile_NPC_BMSW = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_BMSW,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bmsw_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_BMSW,
    /* Actor SubMtd */ &l_daNpc_Bmsw_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
