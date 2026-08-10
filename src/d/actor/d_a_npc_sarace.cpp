/**
 * d_a_npc_sarace.cpp
 * NPC - Loot the Sailor (Boating Course)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_sarace.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "res/Object/Sarace.h"

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


/* 000000EC-00000198       .text __ct__18daNpc_Sarace_HIO_cFv */
daNpc_Sarace_HIO_c::daNpc_Sarace_HIO_c() {
    mNpc.m04 = -20.0;
    mNpc.mMaxHeadX = 4000;
    mNpc.mMaxHeadY = 6000;
    mNpc.mMaxBackboneX = 0;
    mNpc.mMaxBackboneY = 7000;
    mNpc.mMinHeadX = -2000;
    mNpc.mMinHeadY = -6000;
    mNpc.mMinBackboneX = -2000;
    mNpc.mMinBackboneY = -7000;
    mNpc.mMaxTurnStep = 1000;
    mNpc.mMaxHeadTurnVel = 0x640;
    mNpc.mAttnYOffset = 45.0;
    mNpc.mMaxAttnAngleY = 0x4000;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 400.0;
    m30 = 11.0;
    m34 = 8.0;
    mNo = -1;
}

static daNpc_Sarace_HIO_c l_HIO;

static const s32 l_bck_ix_tbl[] = {
    dRes_INDEX_SARACE_BCK_SA_WAIT01_e,
    dRes_INDEX_SARACE_BCK_SA_TALK01_e,
    dRes_INDEX_SARACE_BCK_SA_TALK02_e,
};
static const s32 l_head_bck_ix_tbl[] = {
    dRes_INDEX_SARACE_BCK_SA01HEAD_WAIT01_e,
    dRes_INDEX_SARACE_BCK_SA01HEAD_TALK01_e,
    dRes_INDEX_SARACE_BCK_SA01HEAD_TALK02_e,
};

static const u32 l_btp_ix_tbl[] = {
    dRes_INDEX_SARACE_BTP_SA01_MABA_e,
};


/* 00000198-00000328       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, s32 calcTiming) {
    if(calcTiming == J3DNodeCBCalcTiming_In){
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Sarace_c* i_this = (daNpc_Sarace_c*)model->getUserArea();
        if(i_this != NULL){
            s32 jntNo = joint->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            if(jntNo == i_this->m_jnt.getHeadJntNum()) {
                static cXyz l_offsetAttPos(0.0f, 0.0f, 0.0f);
                cXyz l_offsetEyePos(24.0f, 14.0f, 0.0f);
                mDoMtx_stack_c::multVec(&l_offsetAttPos, &i_this->mAttPos);
                mDoMtx_stack_c::XrotM(+i_this->m_jnt.getHead_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getHead_x());
                mDoMtx_stack_c::multVec(&l_offsetEyePos, &i_this->mEyePos);
            } else if(jntNo == i_this->m_jnt.getBackboneJntNum()) {
                mDoMtx_stack_c::XrotM(+i_this->m_jnt.getBackbone_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getBackbone_x());
            }
            cMtx_copy(mDoMtx_stack_c::get(),j3dSys.mCurrentMtx);
            model->setAnmMtx(jntNo,mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 00000364-00000478       .text initTexPatternAnm__14daNpc_Sarace_cFb */
BOOL daNpc_Sarace_c::initTexPatternAnm(bool i_param_1) {
    J3DModelData* modeldata = mpMorf->getModel()->getModelData();

    m_btp = (J3DAnmTexPattern*)dComIfG_getObjectRes("Sarace", l_btp_ix_tbl[mTexPatternNum]);
    JUT_ASSERT(0xF9, m_btp != NULL);

    if(mBtpAnm.init(modeldata, m_btp, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_param_1, FALSE) == FALSE) {
        return FALSE;
    }
    mBlinkFrame = 0;
    mBlinkTimer = 0;
    return TRUE;
}

/* 00000478-00000504       .text playTexPatternAnm__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::playTexPatternAnm() {
    if (cLib_calcTimer(&mBlinkTimer) == 0) {
        if (mBlinkFrame >= m_btp->getFrameMax()) {
            mBlinkFrame -= m_btp->getFrameMax();
            mBlinkTimer = cM_rndF(100.0f) + 30.0f;
        } else {
            mBlinkFrame++;
        }
    }
}

/* 00000504-0000060C       .text setAnm__14daNpc_Sarace_cFScf */
void daNpc_Sarace_c::setAnm(s8 bck_id, f32 morf) {
    static u32 a_play_mode_tbl[] = {
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP,
    };
    
    static f32 a_morf_frame_tbl[] = {
        8.0f, 8.0f, 8.0f
    };
    
    static f32 a_play_speed_tbl[] = {
        1.0f, 1.0f, 1.0f
    };
    

    if(morf < 0.0f) {
        morf = a_morf_frame_tbl[bck_id];
    }
    if(bck_id != mCurrentAnm && mCurrentAnm != -1) {

        mCurrentAnm = bck_id;
        dNpc_setAnm(
            mpMorf,
            a_play_mode_tbl[mCurrentAnm],
            morf,
            a_play_speed_tbl[mCurrentAnm],
            l_bck_ix_tbl[mCurrentAnm],
            0xFFFFFFFF,
            "Sarace"
        );
        dNpc_setAnm(
            mpHeadMorf,
            a_play_mode_tbl[mCurrentAnm],
            morf,
            a_play_speed_tbl[mCurrentAnm],
            l_head_bck_ix_tbl[mCurrentAnm],
            0xFFFFFFFF,
            "Sarace"
        );
    }
}

/* 0000060C-00000760       .text chkAttention__14daNpc_Sarace_cF4cXyzs */
bool daNpc_Sarace_c::chkAttention(cXyz i_pos, s16 i_angle) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    f32 maxAttnDistXZ = l_HIO.mNpc.mMaxAttnDistXZ;
    int maxAttnAngleY = l_HIO.mNpc.mMaxAttnAngleY;

    cXyz delta;
    delta.x = player->current.pos.x - i_pos.x;
    delta.z = player->current.pos.z - i_pos.z;
    f32 distXZ = std::sqrtf(delta.x*delta.x + delta.z*delta.z);
    s16 targetAngleY = cM_atan2s(delta.x, delta.z);
    if (mHasAttention) {
        maxAttnDistXZ += 40.0f;
        maxAttnAngleY += cAngle::d2s(10.0f);
    }
    targetAngleY -= i_angle;
    return maxAttnAngleY > abs(targetAngleY) && maxAttnDistXZ > distXZ;
}

/* 00000760-000007D8       .text eventOrder__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::eventOrder() {
    if(mEventState == 3) {
        fopAcM_orderOtherEvent2(
            this,
            "SARACE_EXPCAM",
            dEvtFlag_NOPARTNER_e
        );
    } else if (mEventState == 1 || mEventState == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(mEventState == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 000007D8-000008E8       .text checkOrder__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(mEventState == 3) {
            setAction(&daNpc_Sarace_c::event_endCheck_action, 0);
            mEventState = 0;
        }
    }
    else if (eventInfo.checkCommandTalk()) {
        if(mEventState == 1 || mEventState == 2) {
            mEventState = 0;
            m729 = 1;
        }
    }
}

/* 000008E8-00000A6C       .text next_msgStatus__14daNpc_Sarace_cFPUl */
u16 daNpc_Sarace_c::next_msgStatus(u32* i_msg_no) {
    u16 msg_status = fopMsgStts_MSG_CONTINUES_e;
    
    switch(*i_msg_no) {
        case 0xfa1:
        case 0xfa2:
        case 0xfa5:
        case 0xfa7:
        case 0xfb1:
        case 0xfb2:
        case 0xfb4:
        case 0xfb5:
        case 0xfb7:
            (*i_msg_no)++;
            break;
        case 0xfb8:
            *i_msg_no = 0xfb3;
            break;
        case 0xfb3:
            *i_msg_no = 0xfa3;
            break;
        case 0xfa3:
            if (mpCurrMsg->mSelectNum == 0) {
                *i_msg_no = 0xfa4;
            }
            else if (mpCurrMsg->mSelectNum == 1) {
                if ((u16)dComIfGs_getRupee() < 30) {
                    *i_msg_no = 0xfaf;
                }
                else {
                    
                    dComIfGp_setItemRupeeCount(-30);
                    dComIfGs_offEventBit(dSv_event_flag_c::UNK_2820);
                    *i_msg_no = 0xfb0;
                }
            }
            else {
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2808) == 0) {
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_2808);
                    *i_msg_no = 0xfad;
                }
                else {
                    *i_msg_no = 0xfae;
                }
            }
            break;
        case 0xfa8:
            if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2820)) {
                *i_msg_no = 0xfaa;
            }
            else {
                *i_msg_no = 0xfa9;
            }
            break;
        case 0xfaa:
            *i_msg_no = 0xfa9;
            break;
        case 0xfa9:
            *i_msg_no = 0xfa3;
            break;
        
        
        default:
            msg_status = 0x10;
            break;
    }
    return msg_status;
}

/* 00000A6C-00000B50       .text getMsg__14daNpc_Sarace_cFv */
u32 daNpc_Sarace_c::getMsg() {
    u32 msgNo;
    if(mMiniGameMessage != 0) {
        if(mMiniGameMessage == 0xFB4) {
            if(ship_race_result == 1) {
                mMiniGameMessage = 0xFB7; // Timeout
            } else if(ship_race_result == 3) {
                mMiniGameMessage = 0xFB1; // Drowned
            } else {
                dComIfGp_setMessageCountNumber(ship_race_rupee);
            }
        }
        msgNo = mMiniGameMessage;
        mMiniGameMessage = 0;
    } else {
        if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2810)) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_2810);
            msgNo = 0xFA1;
        }
        else {
            if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2840)) {
                msgNo = 0xFA1;
            } else {
                msgNo = 0xFA2;
            }
        }
    }
    return msgNo;
}

/* 00000B50-00000BEC       .text anmAtr__14daNpc_Sarace_cFUs */
void daNpc_Sarace_c::anmAtr(unsigned short) {
    switch(dComIfGp_getMesgAnimeAttrInfo()) {
        case 0:
            setAnm(
                dRes_ID_SARACE_BCK_SA01HEAD_TALK01_e,
                -1.0f
            );
            break;
        case 1:
            setAnm(
                dRes_ID_SARACE_BCK_SA01HEAD_WAIT01_e, 
                l_HIO.m30
            );
            break;
        case 2:
            setAnm(
                dRes_ID_SARACE_BCK_SA_TALK01_e,
                l_HIO.m34
            );
            break;
    }
    dComIfGp_setMesgAnimeAttrInfo(0xFF);
}

/* 00000BEC-00000E24       .text CreateInit__14daNpc_Sarace_cFv */
BOOL daNpc_Sarace_c::CreateInit() {
    m718 = current.angle;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    gravity = -30.0f;
    setAction(&daNpc_Sarace_c::wait_action, 0);
    mAttPos = current.pos;
    mEyePos = current.pos;
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(60.0f, 150.0f);
    m730 = 0;
    mEventCut.setActorInfo2("Sarace", this);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 173;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 173;
    set_mtx();
    mMiniGameMessage = 0;
    m6D8 = -1;
    m6DC = -1;
    setAnm(dRes_ID_SARACE_BCK_SA01HEAD_TALK01_e, -1.0);
    if(
        dComIfGp_getStartStagePoint() == 1
        && dComIfGp_getStartStageRoomNo() == 48
        && ship_race_result != 0
    ) {
        mEventState = 1;
        mMiniGameMessage = 0xFB4;
        fopAcM_orderSpeakEvent(this);
    }
    mpMorf->play(&mEyePos, 0, 0);
    mpMorf->calc();
    mpHeadMorf->play(NULL, 0, 0);
    mpHeadMorf->calc();
    return TRUE;
}

/* 00000E24-00000E68       .text setAttention__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::setAttention() {
    /* Nonmatching */
}

/* 00000E68-00000FF4       .text lookBack__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::lookBack() {
    /* Nonmatching */
}

/* 00000FF4-00001024       .text wait01__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::wait01() {
    /* Nonmatching */
}

/* 00001024-000014B8       .text talk01__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::talk01() {
    /* Nonmatching */
}

/* 000014B8-000014E0       .text dummy_action__14daNpc_Sarace_cFPv */
BOOL daNpc_Sarace_c::dummy_action(void* i_arg) {
    /* Nonmatching */
}

/* 000014E0-000015BC       .text wait_action__14daNpc_Sarace_cFPv */
BOOL daNpc_Sarace_c::wait_action(void* i_arg) {
    /* Nonmatching */
}

/* 000015BC-0000173C       .text event_endCheck_action__14daNpc_Sarace_cFPv */
BOOL daNpc_Sarace_c::event_endCheck_action(void* i_arg) {
    /* Nonmatching */
}

/* 0000173C-000017E0       .text set_mtx__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::set_mtx() {
    /* Nonmatching */
}

/* 000017E0-00001938       .text _draw__14daNpc_Sarace_cFv */
BOOL daNpc_Sarace_c::_draw() {
    /* Nonmatching */
}

/* 00001938-00001A68       .text _execute__14daNpc_Sarace_cFv */
BOOL daNpc_Sarace_c::_execute() {
    /* Nonmatching */
}

/* 00001A68-00001AE0       .text _delete__14daNpc_Sarace_cFv */
BOOL daNpc_Sarace_c::_delete() {
    /* Nonmatching */
}

/* 00001AE0-00001B00       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001B00-00001D1C       .text _create__14daNpc_Sarace_cFv */
cPhs_State daNpc_Sarace_c::_create() {
    /* Nonmatching */
}

/* 000020CC-00002498       .text CreateHeap__14daNpc_Sarace_cFv */
void daNpc_Sarace_c::CreateHeap() {
    /* Nonmatching */
}

/* 00002498-000024B8       .text daNpc_Sarace_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Sarace_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Sarace_c*)i_this)->_create();
}

/* 000024B8-000024D8       .text daNpc_Sarace_Delete__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_Delete(daNpc_Sarace_c* i_this) {
    return ((daNpc_Sarace_c*)i_this)->_delete();
}

/* 000024D8-000024F8       .text daNpc_Sarace_Execute__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_Execute(daNpc_Sarace_c* i_this) {
    return ((daNpc_Sarace_c*)i_this)->_execute();
}

/* 000024F8-00002518       .text daNpc_Sarace_Draw__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_Draw(daNpc_Sarace_c* i_this) {
    return ((daNpc_Sarace_c*)i_this)->_draw();
}

/* 00002518-00002520       .text daNpc_Sarace_IsDelete__FP14daNpc_Sarace_c */
static BOOL daNpc_Sarace_IsDelete(daNpc_Sarace_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Sarace_Method = {
    (process_method_func)daNpc_Sarace_Create,
    (process_method_func)daNpc_Sarace_Delete,
    (process_method_func)daNpc_Sarace_Execute,
    (process_method_func)daNpc_Sarace_IsDelete,
    (process_method_func)daNpc_Sarace_Draw,
};

actor_process_profile_definition g_profile_NPC_SARACE = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_SARACE_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Sarace_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_SARACE_e,
    /* Actor SubMtd */ &l_daNpc_Sarace_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_12_e,
};
