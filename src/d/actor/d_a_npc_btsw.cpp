/**
 * d_a_npc_btsw.cpp
 * NPC - Baito
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_btsw.h"
#include "d/d_letter.h"
#include "d/d_snap.h"
#include "d/res/res_btsw.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

class daNpc_Btsw_HIO_c : public JORReflexible {
public:
    daNpc_Btsw_HIO_c();
    virtual ~daNpc_Btsw_HIO_c() {}

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
    /* 0x58 */ u8 field_0x58;
    /* 0x59 */ u8 field_0x59[0x5C - 0x59];
    /* 0x5C */ f32 field_0x5C;
};  // Size: 0x60

daNpc_Btsw_HIO_c l_HIO;

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


/* 000000EC-000001E8       .text __ct__16daNpc_Btsw_HIO_cFv */
daNpc_Btsw_HIO_c::daNpc_Btsw_HIO_c() {
    mNpc.m04 = 0.0f;
    mNpc.mMaxHeadX = 8000;
    mNpc.mMaxHeadY = 2000;
    mNpc.mMaxBackboneX = 0;
    mNpc.mMaxBackboneY = 8000;
    mNpc.mMinHeadX = -3000;
    mNpc.mMinHeadY = -2000;
    mNpc.mMinBackboneX = 0;
    mNpc.mMinBackboneY = -8000;
    mNpc.mMaxTurnStep = 2000;
    mNpc.mMaxHeadTurnVel = 0x640;
    mNpc.mAttnYOffset = 40.0f;
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
    field_0x58 = 0;
    field_0x5C = 10.0f;
    mNo = -1;
}

static const s32 l_bck_ix_tbl[] = {
    BTSW_BCK_BN_WAIT01, BTSW_BCK_BN_WAIT02, BTSW_BCK_BN_TALK01, BTSW_BCK_BN_TALK02,
    BTSW_BCK_BN_ONEGAI, BTSW_BCK_BN_SUGOI, BTSW_BCK_BN_SUGOI, BTSW_BCK_BN_WALK,
    BTSW_BCK_BN_KASIGE, BTSW_BCK_BN_SIWAKE01, BTSW_BCK_BN_SIWAKE02
};
static const u32 l_btp_ix_tbl[] = {BTSW_INDEX_BCK_BN_TALK02};

/* 000001E8-000003F4       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Btsw_c* i_this = (daNpc_Btsw_c*)model->getUserArea();

        if (i_this != NULL) {
            static cXyz a_att_pos_offst(0.0f, 0.0f, 0.0f);
            static cXyz a_eye_pos_offst(10.0f, 20.0f, 0.0f);

            u16 jointNo = joint->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jointNo));

            if (jointNo == i_this->m_jnt.getHeadJntNum()) {
                mDoMtx_stack_c::multVec(&a_att_pos_offst, &i_this->getAttentionBasePos());

                Mtx mtx;
                cMtx_copy(mDoMtx_stack_c::get(), mtx);

                cXyz vec(mtx[0][3], mtx[1][3], mtx[2][3]);
                mtx[0][3] = mtx[1][3] = mtx[2][3] = 0.0f;

                mDoMtx_stack_c::transS(vec);

                mDoMtx_stack_c::YrotM((u32)i_this->m_jnt.getHead_y());
                mDoMtx_stack_c::XrotM((u32)i_this->m_jnt.getHead_x());

                mDoMtx_stack_c::concat(mtx);
                mDoMtx_stack_c::multVec(&a_eye_pos_offst, &i_this->eyePos);
            } else if (jointNo == i_this->m_jnt.getBackboneJntNum()) {
                mDoMtx_stack_c::XrotM(i_this->m_jnt.getBackbone_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getBackbone_x());
            }

            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jointNo, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 00000430-0000046C       .text daNpc_Btsw_getGameEndMsg__Fs */
u32 daNpc_Btsw_getGameEndMsg(short rupees) {
    u32 msgNo;
    if (rupees == 0) {
        msgNo = 0x1A9D;
    } else if (rupees == 1) {
        msgNo = 0x1A9E;
    } else if (rupees < 25) {
        msgNo = 0x1A9F;
    } else {
        msgNo = 0x1A98;
    }
    return msgNo;
}

/* 0000046C-00000584       .text initTexPatternAnm__12daNpc_Btsw_cFb */
BOOL daNpc_Btsw_c::initTexPatternAnm(bool i_modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();

    m_head_tex_pattern = (J3DAnmTexPattern*) dComIfG_getObjectIDRes("Btsw", (u16)l_btp_ix_tbl[field_0x9C4]);
    JUT_ASSERT(332, m_head_tex_pattern != NULL);

    if (!field_0x7E8.init(modelData, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        return FALSE;
    }
    field_0x7FC = 0;
    field_0x954 = 0;
    return TRUE;
}

/* 00000584-00000610       .text playTexPatternAnm__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::playTexPatternAnm() {
    if (cLib_calcTimer(&field_0x954) == 0) {
        if (field_0x7FC >= m_head_tex_pattern->getFrameMax()) {
            field_0x7FC -= m_head_tex_pattern->getFrameMax();
            field_0x954 = cM_rndF(100.0f) + 30.0f;
        } else {
            field_0x7FC++;
        }
    }
}

/* 00000610-00000708       .text setAnm__12daNpc_Btsw_cFSc */
void daNpc_Btsw_c::setAnm(signed char idx) {
    static u32 a_play_mode_tbl[] = {
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_NONE, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_NONE, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_NONE,
    };
    static f32 a_morf_frame_tbl[] = {
        8.0f, 8.0f, 8.0f, 8.0f, 8.0f, 8.0f,
        8.0f, 8.0f, 8.0f, 8.0f, 8.0f
    };
    static f32 a_play_speed_tbl[] = {
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f
    };

    f32 morf = a_morf_frame_tbl[idx];
    if (field_0x9C5 == 6 || field_0x9C5 == 5) {
        morf = l_HIO.field_0x5C;
    }

    if (idx != field_0x9C5) {
        field_0x9C5 = idx;

        dNpc_setAnmIDRes(mpMorf,
            a_play_mode_tbl[field_0x9C5],
            morf,
            a_play_speed_tbl[field_0x9C5],
            l_bck_ix_tbl[field_0x9C5],
            -1,
            "Btsw"
        );
        if (field_0x9C5 == 9 || field_0x9C5 == 10 || field_0x9C5 == 6 || field_0x9C5 == 5) {
            m_jnt.onHeadLock();
            m_jnt.onBackBoneLock();
        } else {
            m_jnt.offHeadLock();
            m_jnt.offBackBoneLock();
        }
    }
}

/* 00000708-0000085C       .text chkAttention__12daNpc_Btsw_cF4cXyzs */
bool daNpc_Btsw_c::chkAttention(cXyz pos, short angle) {
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

/* 0000085C-00000908       .text eventOrder__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::eventOrder() {
    if (field_0x9C7 == 3) {
        fopAcM_orderOtherEvent2(this, "GETMOTHERLETTER", dEvtFlag_NOPARTNER_e);
    } else if (field_0x9C7 == 4) {
        fopAcM_orderOtherEventId(this, field_0x9C8);
    } else if (field_0x9C7 == 1 || field_0x9C7 == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        if (field_0x9C7 == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00000908-00000AC4       .text checkOrder__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::checkOrder() {
    if (eventInfo.checkCommandDemoAccrpt()) {
        if (field_0x9C7 == 3) {
            field_0x9C7 = 0;
            setAction(&daNpc_Btsw_c::getdemo_action, NULL);
        } else if (field_0x9C7 == 4) {
            field_0x9C7 = 0;
            setAction(&daNpc_Btsw_c::dummy_event_action, NULL);
        }
        return;
    }
    if (!eventInfo.checkCommandTalk()) {
        return;
    }
    if (field_0x9C7 != 1 && field_0x9C7 != 2) {
        return;
    }
    field_0x9C7 = 0;
    field_0x9A9 = 1;
}

/* 00000AC4-00000CBC       .text next_msgStatus__12daNpc_Btsw_cFPUl */
u16 daNpc_Btsw_c::next_msgStatus(unsigned long* currMsgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;

    switch (*currMsgNo) {
        case 0x1A91:
        case 0x1A92:
        case 0x1A94:
        case 0x1A95:
        case 0x1A96:
        case 0x1A98:
        case 0x1A99:
        case 0x1A9A:
        case 0x1AA7:
        case 0x1AAD:
            (*currMsgNo)++;
            break;
        case 0x1AB5:
            *currMsgNo = 0x1A93;
            break;
        case 0x1A93:
            if (mpCurrMsg->mSelectNum == 0) {
                dComIfGs_onEventBit(dSv_evtBit_c::UNK_2702);
                *currMsgNo = 0x1A94;
            } else {
                *currMsgNo = 0x1AA0;
            }
            break;
        case 0x1AA1:
            if (mpCurrMsg->mSelectNum == 0) {
                dComIfGs_onEventBit(dSv_evtBit_c::UNK_2702);
                *currMsgNo = 0x1A94;
            } else {
                *currMsgNo = 0x1AA2;
            }
            break;
        case 0x1AA8:
            if (mpCurrMsg->mSelectNum == 0) {
                *currMsgNo = 0x1AA9;
            } else {
                *currMsgNo = 0x1AAA;
            }
            break;
        case 0x1AA4:
        case 0x1AA5:
        case 0x1AA6:
            if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_2701)) {
                *currMsgNo = 0x1AA7;
            } else if (dLetter_isNoSend(0xAC03)) {
                *currMsgNo = 0x1AAB;
            } else if (!dComIfGs_isSymbol(1)) {
                *currMsgNo = 0x1AB4;
            } else if (!dLetter_isRead(0xAC03)) {
                *currMsgNo = 0x1AAD;
            } else if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_3104)) {
                *currMsgNo = 0x1AAC;
                dComIfGs_onEventBit(dSv_evtBit_c::UNK_3104);
            } else {
                *currMsgNo = 0x1AB3;
            }
            break;
        case 0x1AA9:
            *currMsgNo = 0x1A97;
            break;
        default:
            ret = fopMsgStts_MSG_ENDS_e;
            break;
    }

    return ret;
}

/* 00000CBC-00000DF0       .text getMsg__12daNpc_Btsw_cFv */
u32 daNpc_Btsw_c::getMsg() {
    u32 msg;

    fpc_ProcID previous = field_0x9B0;
    if (previous != fpcM_ERROR_PROCESS_ID_e) {
        msg = previous;
        field_0x9B0 = fpcM_ERROR_PROCESS_ID_e;
    } else {
        if (dComIfGp_event_chkTalkXY()) {
            msg = 0x1AA3;
        } else {
            if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_2704)) {
                dComIfGs_onEventBit(dSv_evtBit_c::UNK_2704);
                if (dComIfGs_getClearCount() == 0) {
                    msg = 0x1A91;
                } else {
                    msg = 0x1AB5;
                }
            } else if (!dComIfGs_isEventBit(dSv_evtBit_c::UNK_2702)) {
                msg = 0x1AA1;
            } else {
                if (dComIfGs_getEventReg(0xAB03) < 3) {
                    msg = 0x1AA5;
                } else {
                    msg = 0x1AA4;
                }
            }
            dComIfGs_setEventReg(0xAB03, 0);
        }
    }

    return msg;
}

/* 00000DF0-00000F0C       .text anmAtr__12daNpc_Btsw_cFUs */
void daNpc_Btsw_c::anmAtr(unsigned short mesgNo) {
    switch (dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnm(0);
            break;
        case 1:
            setAnm(1);
            break;
        case 2:
            setAnm(2);
            break;
        case 3:
            setAnm(3);
            break;
        case 4:
            setAnm(4);
            break;
        case 5:
            setAnm(5);
            break;
        case 6:
            setAnm(6);
            break;
    }

    if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f) && (field_0x9C5 == 4 || field_0x9C5 == 6)) {
        setAnm(1);
    }

    dComIfGp_clearMesgAnimeAttrInfo();
}

/* 00000F0C-00000F30       .text daNpc_Btsw_XyCheckCB__FPvi */
static s16 daNpc_Btsw_XyCheckCB(void*, int idx) {
    if (dComIfGp_getSelectItem(idx) == dItem_NOTE_TO_MOM_e) {
        return TRUE;
    }
    return FALSE;
}

/* 00000F30-00001110       .text CreateInit__12daNpc_Btsw_cFv */
BOOL daNpc_Btsw_c::CreateInit() {
    field_0x96E = current.angle;

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;

    gravity = -30.0f;
    setAction(&daNpc_Btsw_c::wait_action, NULL);

    mAttPos = current.pos;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);

    setCollision(60.0f, 150.0f);
    field_0x9B4 = 0;
    eventInfo.setXyCheckCB(daNpc_Btsw_XyCheckCB);
    mEventCut.setActorInfo2("Btsw", this);

    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x6F;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x6F;
    field_0x9C8 = -1;
    field_0x952 = 0;
    field_0x953 = 0;
    field_0x9B0 = fpcM_ERROR_PROCESS_ID_e;

    field_0x978.setWaitParm(5, 2, 3, 2, 1.0f, 0.9f, 0, 0x2000);
    set_mtx();
    mpMorf->calc();
    dKy_tevstr_init(&field_0x6D4, home.roomNo, 0xFF);

    return TRUE;
}

/* 00001110-00001324       .text set_mtx__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::set_mtx() {
    J3DModel* model = mpMorf->getModel();

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());


    if (field_0x9C5 == 10 || field_0x9C5 == 9) {
        cXyz vec;
        csXyz angle;

        if (mpMorf->getFrame() < 19.0f) {
            if (field_0x9C5 == 9) {
                vec.set(28.68f, 4.68f, -8.45f);
                angle.set(-0x43A2, 0x9CA, -0x233);
            } else {
                vec.set(28.68f, -0.43f, -8.19f);
                angle.set(-0x43A2, 0x9CA, -0x2CB);
            }
            mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_handR));
        } else {
            if (field_0x9C5 == 9) {
                vec.set(23.61f, -5.08f, -7.22f);
                angle.set(-0x49FC, -0x458, -0x568F);
            } else {
                vec.set(24.9f, 0.62f, -7.51f);
                angle.set(-0x4C7F, -0x7A, -0x491D);
            }
            mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_handL));
        }

        mDoMtx_stack_c::transM(vec);
        mDoMtx_stack_c::XYZrotM(angle);
        field_0x6D0->setBaseTRMtx(mDoMtx_stack_c::get());
    }
}

/* 00001324-00001350       .text setAttention__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::setAttention() {
    attention_info.position.set(mAttPos.x, mAttPos.y + l_HIO.mNpc.mAttnYOffset, mAttPos.z);
}

/* 00001350-00001490       .text lookBack__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::lookBack() {
    cXyz vec2;
    cXyz vec(0.0f, 0.0f, 0.0f);

    cXyz* dstPos = NULL;
    s16 desired_y_rot = current.angle.y;

    switch (field_0x9CA) {
        case 1:
        case 2:
            if (field_0x9CA == 2) {
                m_jnt.setTrn();
            }
            if (mHasAttention) {
                vec2 = dNpc_playerEyePos(l_HIO.mNpc.m04);
                dstPos = &vec2;

                vec = current.pos;
                vec.y = eyePos.y;
            }
    }

    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&field_0x96A, l_HIO.mNpc.mMaxHeadTurnVel, 4, 0x800);
    } else {
        field_0x96A = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstPos, vec, desired_y_rot, field_0x96A, true);
}

/* 00001490-00001594       .text wait01__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::wait01() {
    if (field_0x9A9) {
        field_0x9CA = 2;
    } else {
        if (mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            if (--field_0x9C6 <= 0) {
                if (field_0x9C5 == 9) {
                    field_0x9C6 = 1;
                    setAnm(10);
                } else {
                    field_0x9C6 = cM_rndF(4.0f) + 2.0f;
                    setAnm(9);
                }
            }
        }

        if (mHasAttention) {
            field_0x9C7 = 2;
        }
    }
}

/* 00001594-00001798       .text talk01__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::talk01() {
    if (mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e
        && dComIfGp_event_chkTalkXY()
        && !dComIfGp_evmng_ChkPresentEnd())
    {
        return;
    }

    u16 talk_res = talk(1);

    if (dComIfGp_checkMesgSendButton() == 1 && (mCurrMsgNo == 0x1A96 || mCurrMsgNo == 0x1AA9)) {
        mSwCam.ActiveOn();
    }

    if (talk_res == fopMsgStts_BOX_CLOSED_e) {
        field_0x9CA = 1;
        dComIfGp_event_reset();

        setAnm(1);
        field_0x9C6 = 1;
        field_0x9A9 = 0;

        if (mCurrMsgNo == 0x1A97) {
            setAction(&daNpc_Btsw_c::shiwake_game_action, NULL);
        } else if (mCurrMsgNo == 0x1A9B) {
            field_0x9C7 = 3;
        }
    }
}

/* 00001798-00001888       .text wait_action__12daNpc_Btsw_cFPv */
BOOL daNpc_Btsw_c::wait_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        field_0x9CA = 1;
        field_0x9C6 = 1;
        setAnm(TRUE);
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        s16 angle = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        mHasAttention = chkAttention(current.pos, angle);
        field_0x9C7 = 0;

        switch (field_0x9CA) {
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

/* 00001888-00001A40       .text dummy_event_action__12daNpc_Btsw_cFPv */
BOOL daNpc_Btsw_c::dummy_event_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        field_0x9CA = 2;
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING) {
        int staffIdx = dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
        if (!mEventCut.cutProc()) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }

        s16 angle = current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y();
        mHasAttention = chkAttention(current.pos, angle);

        if (dComIfGp_evmng_endCheck(field_0x9C8)) {
            field_0x9C8 = -1;
            field_0x9C7 = 3;
            dComIfGp_event_onEventFlag(8);

            setAction(&daNpc_Btsw_c::wait_action, NULL);
        }

        lookBack();
        setAttention();
    }

    return TRUE;
}

/* 00001A40-00001B0C       .text checkNextMailThrowOK__12daNpc_Btsw_cFv */
BOOL daNpc_Btsw_c::checkNextMailThrowOK() {
    u8 mailIdx = field_0x92C;
    if (mailIdx < 2) {
        mailIdx++;
    } else {
        mailIdx = 0;
    }
    u8 ret = 1;

    if (field_0x920[mailIdx]->CheckProc(&SwMail2_c::Dummy) == FALSE) {
        if (field_0x920[mailIdx]->CheckProc(&SwMail2_c::End) == FALSE) {
            ret = 0;
        }
    }
    return ret;
}

/* 00001B0C-00001BF0       .text TimerCountDown__12daNpc_Btsw_cFv */
void daNpc_Btsw_c::TimerCountDown() {
    if (field_0x9A4 > dComIfG_getTimerRestTimeMs()) {
        if (field_0x9A4 <= 10000) {
            mDoAud_seStart(JA_SE_MINIGAME_TIMER_30);
            field_0x9A4 -= 1000;
        } else {
            mDoAud_seStart(JA_SE_MINIGAME_TIMER_10);
            field_0x9A4 -= 10000;
        }
    }
}

/* 00001BF0-000026EC       .text shiwake_game_action__12daNpc_Btsw_cFPv */
BOOL daNpc_Btsw_c::shiwake_game_action(void*) {
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
        field_0x9CA = 3;
        field_0x9A0 = 0;
        field_0x9A1 = 0;

        if (!eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderOtherEvent2(this, "SHIWAKEGAME", dEvtFlag_NOPARTNER_e);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
            return FALSE;
        }

        if (!field_0x952) {
            dTimer_createTimer(6, l_HIO.field_0x30, 3, 4, 221.0f, l_HIO.field_0x48, 32.0f, l_HIO.field_0x4C);
            field_0x952 = 1;

            dComIfGp_setMiniGameRupee(0);
            dComIfGp_startMiniGame(7);
        }

        if (dComIfG_getTimerPtr() == NULL) {
            return FALSE;
        }
        dComIfG_TimerStart(6, l_HIO.field_0x32);

        field_0x953 = 1;
        field_0x920[0]->init();
        field_0x920[0]->AppearInit();
        field_0x920[1]->init();
        field_0x920[1]->DummyInit();
        field_0x920[2]->init();
        field_0x920[2]->DummyInit();
        field_0x92C = 0;
        mActionStatus++;

        mpShopCursor->setPos(cursor_pos_data[field_0x9A1][1 + field_0x9A0]);
        mpShopCursor->show();
        field_0x9A4 = 20000;
    } else if (mActionStatus == ACTION_ENDING) {
        field_0x952 = 0;
        field_0x953 = 0;
    } else {
        if (dComIfG_getTimerRestTimeMs() > 0) {
            TimerCountDown();

            field_0x978.checkTrigger();
            if (field_0x9A0 > -1 && field_0x978.checkLeftTrigger()) {
                mDoAud_seStart(JA_SE_LETTER_GAME_CURSOR);
                field_0x9A0--;
            } else if (field_0x9A0 < 1 && field_0x978.checkRightTrigger()) {
                mDoAud_seStart(JA_SE_LETTER_GAME_CURSOR);
                field_0x9A0++;
            }

            if (field_0x9A1 < 1 && field_0x978.checkUpTrigger()) {
                mDoAud_seStart(JA_SE_LETTER_GAME_CURSOR);
                field_0x9A1++;
            } else if (field_0x9A1 > 0 && field_0x978.checkDownTrigger()) {
                mDoAud_seStart(JA_SE_LETTER_GAME_CURSOR);
                field_0x9A1--;
            }

            if (field_0x920[field_0x92C]->CheckProc(&SwMail2_c::Wait)
                        && dComIfG_getTimerPtr()->getStatus() != 1 && CPad_CHECK_TRIG_A(0)
                        && checkNextMailThrowOK()) {

                s32 row = field_0x9A0 + 1;
                u8 col = field_0x9A1;
                u8 idx = row + (1 - col) * 3;

                cXyz& aim_pos = aim_pos_data[field_0x9A1][row];
                field_0x920[field_0x92C]->ThrowInit(
                    aim_pos,
                    idx
                );

                if (field_0x92C < 2) {
                    field_0x92C++;
                } else {
                    field_0x92C = 0;
                }

                mDoAud_seStart(JA_SE_LETTER_GAME_OK);
                field_0x920[field_0x92C]->AppearInit();
            }

            mSwCam.setAimIdx(field_0x9A0, field_0x9A1);

            mpShopCursor->setPos(cursor_pos_data[field_0x9A1][1 + field_0x9A0]);
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
                s32 staff_id = dComIfGp_evmng_getMyStaffId("Btsw");
                dComIfGp_evmng_cutEnd(staff_id);
                dComIfGp_event_onEventFlag(8);

                s16 rupees = dComIfGp_getMiniGameRupee();
                field_0x9B0 = daNpc_Btsw_getGameEndMsg(rupees);

                if (rupees < 25) {
                    field_0x9C7 = 1;
                    setAction(&daNpc_Btsw_c::wait_action, NULL);
                    field_0x9C8 = -1;
                } else {
                    field_0x9C7 = 4;
                    field_0x9C8 = dComIfGp_evmng_getEventIdx("BTSW_TALK_SUGOI");
                    setAction(&daNpc_Btsw_c::dummy_event_action, NULL);
                }

                mSwCam.ActiveOff();
                if (dComIfGp_getMiniGameType() == 7) {
                    dComIfGp_endMiniGame(7);
                }
            }
        }
        field_0x920[0]->move();
        field_0x920[1]->move();
        field_0x920[2]->move();
    }

    return TRUE;
}

/* 000026EC-00002844       .text getdemo_action__12daNpc_Btsw_cFPv */
BOOL daNpc_Btsw_c::getdemo_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        mActionStatus++;
    } else if (mActionStatus != ACTION_ENDING && dComIfGp_evmng_endCheck("GETMOTHERLETTER")) {
        dComIfGp_event_onEventFlag(8);

        field_0x9C7 = 1;
        field_0x9B0 = 0x1A9C;

        dComIfGs_onEventBit(dSv_evtBit_c::UNK_2701);
        dComIfGs_setEventReg(0x8AFF, 25);

        setAction(&daNpc_Btsw_c::wait_action, NULL);
    }

    return TRUE;
}

/* 00002844-000029A0       .text _draw__12daNpc_Btsw_cFv */
BOOL daNpc_Btsw_c::_draw() {
    GXColor unused[] = {
        {0xFF, 0x00, 0x00, 0x80},
        {0x00, 0x00, 0xFF, 0x80},
    }; // Unused colors, needed for the .rodata section to match.

    J3DModel* model = mpMorf->getModel();
    J3DModelData* modelData = model->getModelData();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(model, &tevStr);

    field_0x7E8.entry(modelData, field_0x7FC);
    mpMorf->entryDL();

    if (field_0x9C5 == 10 || field_0x9C5 == 9) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &field_0x6D4);

        field_0x6D4.mColorK0.r = 0xC0;
        field_0x6D4.mColorK0.g = 0xAE;
        field_0x6D4.mColorK0.b = 0xC0;
        field_0x6D4.mColorC0.r = 0xC0;
        field_0x6D4.mColorC0.g = 0xAE;
        field_0x6D4.mColorC0.b = 0xC0;

        g_env_light.setLightTevColorType(field_0x6D0, &field_0x6D4);
        mDoExt_modelUpdateDL(field_0x6D0);
    }

    field_0x7E8.remove(modelData);
    if (field_0x953 != 0) {
        for (s32 i = 0; i < 3; i++) {
            field_0x920[i]->draw(&tevStr);
        }
    }

    mpShopCursor->draw();
    dSnap_RegistFig(DSNAP_TYPE_BTSW, this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 000029A0-00002AF4       .text _execute__12daNpc_Btsw_cFv */
BOOL daNpc_Btsw_c::_execute() {
    m_jnt.setParam(
        l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY,
        l_HIO.mNpc.mMinBackboneX, l_HIO.mNpc.mMinBackboneY,
        l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY,
        l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY,
        l_HIO.mNpc.mMaxTurnStep);
    field_0x978.setWaitParm(5, 2, 3, 2, l_HIO.field_0x50, l_HIO.field_0x54, 0, 0x2000);

    playTexPatternAnm();
    mpMorf->play(&eyePos, 0, 0);
    mpMorf->calc();
    checkOrder();
    (this->*mCurrActionFunc)(NULL);
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

/* 00002AF4-00002B90       .text _delete__12daNpc_Btsw_cFv */
BOOL daNpc_Btsw_c::_delete() {
    dComIfG_resDelete(&mPhs, "Btsw");

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

/* 00002B90-00002BB0       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Btsw_c*)i_this)->CreateHeap();
}

/* 00002BB0-00002CAC       .text _create__12daNpc_Btsw_cFv */
cPhs_State daNpc_Btsw_c::_create() {
    fopAcM_SetupActor(this, daNpc_Btsw_c);

    cPhs_State res = dComIfG_resLoad(&mPhs, "Btsw");
    if (res == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CallbackCreateHeap, 0xCDA0)) {
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
        if (l_HIO.mNo < 0) {
            l_HIO.mNo = mDoHIO_createChild("仕分けバイト君", &l_HIO);
        }

        if (!CreateInit()) {
            return cPhs_ERROR_e;
        }
    }
    return res;
}

/* 00003304-0000372C       .text CreateHeap__12daNpc_Btsw_cFv */
BOOL daNpc_Btsw_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectIDRes("Btsw", BTSW_BDL_BN));
    JUT_ASSERT(1424, modelData != NULL);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL,
        NULL,
        (J3DAnmTransform*) dComIfG_getObjectIDRes("Btsw", BTSW_BCK_BN_WAIT02),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        TRUE,
        NULL,
        0x80000,
        0x15020022
    );
    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(1440, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(1442, m_jnt.getBackboneJntNum() >= 0);

    m_handL = modelData->getJointName()->getIndex("handL");
    m_handR = modelData->getJointName()->getIndex("handR");

    J3DModelData* letterModelData = (J3DModelData*) dComIfG_getObjectIDRes("Btsw", BTSW_BDL_BM_LETTER);
    field_0x6D0 = mDoExt_J3DModel__create(letterModelData, 0,0x11020203);
    if (field_0x6D0 == NULL) {
        return FALSE;
    }

    field_0x9C4 = 0;
    if (!initTexPatternAnm(false)) {
        return FALSE;
    }

    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        if (i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum()) {
            mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
        }
    }

    mpMorf->getModel()->setUserArea((u32) this);

    field_0x920[0] = &mSwMail0;
    field_0x920[1] = &mSwMail1;
    field_0x920[2] = &mSwMail2;
    field_0x92C = 0;

    cXyz* eyeP = mSwCam.getEyeP();
    cXyz* cameraCenter = mSwCam.getCenterP();
    if (field_0x920[0]->MailCreateInit(eyeP, cameraCenter) == FALSE) {
        return FALSE;
    }
    if (field_0x920[1]->MailCreateInit(eyeP, cameraCenter) == FALSE) {
        return FALSE;
    }
    if (field_0x920[2]->MailCreateInit(eyeP, cameraCenter) == FALSE) {
        return FALSE;
    }

    J3DAnmTevRegKey* tevRegKey = (J3DAnmTevRegKey*) dComIfG_getObjectIDRes("Btsw", BTSW_BRK_SHOP_CURSOR01);
    J3DModelData* cursorModelData = (J3DModelData*) dComIfG_getObjectIDRes("Btsw", BTSW_BMD_SHOP_CURSOR01);

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

/* 0000372C-00003838       .text MailCreateInit__9SwMail2_cFP4cXyzP4cXyz */
BOOL SwMail2_c::MailCreateInit(cXyz* param_1, cXyz* param_2) {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectIDRes("Btsw", BTSW_BDL_QMAIL));
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11020002);
    if (mpModel == NULL) {
        return FALSE;
    }

    J3DAnmTexPattern* texPattern = (J3DAnmTexPattern*) dComIfG_getObjectIDRes("Btsw", BTSW_BTP_QMAIL);
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

/* 00003838-00003A64       .text getNextNo__9SwMail2_cFUc */
u8 SwMail2_c::getNextNo(unsigned char previous_no) {
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

/* 00003A64-00003AF0       .text init__9SwMail2_cFv */
void SwMail2_c::init() {
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

/* 00003AF0-00003B74       .text set_mtx__9SwMail2_cFv */
void SwMail2_c::set_mtx() {
    mDoMtx_stack_c::transS(
        field_0x24.x + field_0x3C.x,
        field_0x24.y + field_0x3C.y,
        field_0x24.z + field_0x3C.z
    );
    mDoMtx_stack_c::ZXYrotM(field_0x48);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00003B74-00003C00       .text set_mtx_throw__9SwMail2_cFv */
void SwMail2_c::set_mtx_throw() {
    mDoMtx_stack_c::transS(
        field_0x24.x + field_0x3C.x,
        field_0x24.y + field_0x3C.y,
        field_0x24.z + field_0x3C.z
    );
    mDoMtx_stack_c::XrotM(field_0x48.x);
    mDoMtx_stack_c::YrotM(field_0x48.y);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00003C00-00003CD8       .text DummyInit__9SwMail2_cFv */
void SwMail2_c::DummyInit() {
    cLib_targetAngleY(field_0x58, field_0x5C);
    field_0x48.set(0, -0x4000, 0);
    field_0x24.set(field_0x5C->x - 150.0f, field_0x5C->y - 200.0f, field_0x5C->z);

    field_0x54 = getNextNo(field_0x54);
    field_0x4E.set(0, -0x4000, -0x4000);

    field_0x3C = cXyz::Zero;
    SetProc(&SwMail2_c::Dummy);
}

/* 00003CD8-00003CF8       .text Dummy__9SwMail2_cFv */
void SwMail2_c::Dummy() {
    set_mtx();
}

/* 00003CF8-00003E08       .text AppearInit__9SwMail2_cFv */
void SwMail2_c::AppearInit() {
    cLib_targetAngleY(field_0x58, field_0x5C);
    field_0x48.set(0, -0x4000, 0);
    field_0x24.set(field_0x5C->x, field_0x5C->y - 200.0f, field_0x5C->z);

    field_0x54 = getNextNo(field_0x54);
    field_0x4E.set(0, -0x4000, -0x4000);

    field_0x3C = cXyz::Zero;
    field_0x56 = 0;
    mDoAud_seStart(JA_SE_LETTER_GAME_NEW);
    SetProc(&SwMail2_c::Appear);
}

/* 00003E08-00003F64       .text Appear__9SwMail2_cFv */
void SwMail2_c::Appear() {
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

/* 00003F64-00003F88       .text WaitInit__9SwMail2_cFv */
void SwMail2_c::WaitInit() {
    SetProc(&SwMail2_c::Wait);
}

/* 00003F88-000040A4       .text Wait__9SwMail2_cFv */
void SwMail2_c::Wait() {
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

/* 000040A4-000040EC       .text ThrowInit__9SwMail2_cF4cXyzUc */
void SwMail2_c::ThrowInit(cXyz param_1, unsigned char param_2) {
    field_0x30 = param_1;
    field_0x56 = 0;
    field_0x55 = param_2;

    SetProc(&SwMail2_c::Throw);
}

/* 000040EC-000043D0       .text Throw__9SwMail2_cFv */
void SwMail2_c::Throw() {
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

/* 000043D0-0000441C       .text EndInit__9SwMail2_cFv */
void SwMail2_c::EndInit() {
    field_0x30 = cXyz::Zero;
    field_0x30.z = -10.0f;
    SetProc(&SwMail2_c::End);
}

/* 0000441C-000045B0       .text End__9SwMail2_cFv */
void SwMail2_c::End() {
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

/* 000045B0-000045E4       .text SeDelete__9SwMail2_cFv */
void SwMail2_c::SeDelete() {
    mDoAud_seDeleteObject((Vec*) &field_0x24);
}

/* 000045E4-0000460C       .text move__9SwMail2_cFv */
void SwMail2_c::move() {
    (this->*mFunc)();
}

/* 0000460C-00004680       .text draw__9SwMail2_cFP12dKy_tevstr_c */
void SwMail2_c::draw(dKy_tevstr_c* tevStr) {
    J3DModelData* modelData = mpModel->getModelData();
    field_0x10.entry(modelData, field_0x54);
    g_env_light.setLightTevColorType(mpModel, tevStr);
    mDoExt_modelUpdateDL(mpModel);
    field_0x10.remove(modelData);
}

/* 00004680-00004788       .text Move__8SwCam2_cFv */
void SwCam2_c::Move() {
    if (field_0x1E != 0) {
        camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));

        cXyz center = camera_center_data[field_0x1D][field_0x1C + 1];
        cLib_addCalcPos(&field_0x00, center, 0.25f, 10.0f, 1.0f);

        camera->mCamera.Stay();
        camera->mCamera.Set(*getEyeP(), *getCenterP(), field_0x18, 0);
    }
}

/* 00004788-000047A8       .text daNpc_Btsw_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Btsw_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Btsw_c*)i_this)->_create();
}

/* 000047A8-000047C8       .text daNpc_Btsw_Delete__FP12daNpc_Btsw_c */
static BOOL daNpc_Btsw_Delete(daNpc_Btsw_c* i_this) {
    return ((daNpc_Btsw_c*)i_this)->_delete();
}

/* 000047C8-000047E8       .text daNpc_Btsw_Execute__FP12daNpc_Btsw_c */
static BOOL daNpc_Btsw_Execute(daNpc_Btsw_c* i_this) {
    return ((daNpc_Btsw_c*)i_this)->_execute();
}

/* 000047E8-00004808       .text daNpc_Btsw_Draw__FP12daNpc_Btsw_c */
static BOOL daNpc_Btsw_Draw(daNpc_Btsw_c* i_this) {
    return ((daNpc_Btsw_c*)i_this)->_draw();
}

/* 00004808-00004810       .text daNpc_Btsw_IsDelete__FP12daNpc_Btsw_c */
static BOOL daNpc_Btsw_IsDelete(daNpc_Btsw_c*) {
    return TRUE;
}

u8 SwMail2_c::m_no_buff;
u8 SwMail2_c::m_same_count;

cXyz SwCam2_c::camera_center_data[2][3] = {
    cXyz(-104.0f, 805.0f, 875.0f),
    cXyz(-139.0f, 805.0f, 882.0f),
    cXyz(-173.0f, 805.0f, 875.0f),
    cXyz(-104.0f, 825.0f, 868.0f),
    cXyz(-139.0f, 825.0f, 875.0f),
    cXyz(-173.0f, 825.0f, 868.0f),
};
cXyz SwCam2_c::camera_eye(-139.0f, 815.0f, 662.0f);

static actor_method_class l_daNpc_Btsw_Method = {
    (process_method_func)daNpc_Btsw_Create,
    (process_method_func)daNpc_Btsw_Delete,
    (process_method_func)daNpc_Btsw_Execute,
    (process_method_func)daNpc_Btsw_IsDelete,
    (process_method_func)daNpc_Btsw_Draw,
};

actor_process_profile_definition g_profile_NPC_BTSW = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_BTSW,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Btsw_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_BTSW,
    /* Actor SubMtd */ &l_daNpc_Btsw_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
