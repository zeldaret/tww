/**
 * d_a_npc_p1.cpp
 * NPC - Gonzo, Senza, & Nudge
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_p1.h"

#include "d/d_bg_s_func.h"
#include "d/d_camera.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "res/Object/P1.h"





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
        /* Radius */ 40.0f,
        /* Height */ 160.0f,
    }},
};

static msg_class* l_msg;
static fpc_ProcID l_msgId;
static daNpc_P1_HIO_c l_HIO;


/* 000000EC-00000264       .text __ct__14daNpc_P1_HIO_cFv */
daNpc_P1_HIO_c::daNpc_P1_HIO_c() {
    /* Nonmatching */
    children[0].unk14 = 50.0f;
    m94 = 7.0f;
    m98 = 16.0f;

}


/* 000002AC-000002BC       .text __ct__19daNpc_P1_childHIO_cFv */
daNpc_P1_childHIO_c::daNpc_P1_childHIO_c() {
    /* Nonmatching */
}

/* 000002BC-0000051C       .text setAnimFromMsg__10daNpc_P1_cFv */
void daNpc_P1_c::setAnimFromMsg() {
    /* Nonmatching */
}

/* 0000051C-00000AD0       .text setAnm__10daNpc_P1_cFif */
void daNpc_P1_c::setAnm(int, float) {
    /* Nonmatching */
}

/* 00000AD0-00000DEC       .text normalAction__10daNpc_P1_cFPv */
BOOL daNpc_P1_c::normalAction(void*) {
    /* Nonmatching */
}

/* 00000DEC-00000F40       .text confuseAction__10daNpc_P1_cFPv */
BOOL daNpc_P1_c::confuseAction(void*) {
    /* Nonmatching */
}

/* 00000F40-000013A4       .text talkAction__10daNpc_P1_cFPv */
BOOL daNpc_P1_c::talkAction(void*) {
    /* Nonmatching */
    if (m659 == 0) {
        if (m660 == 10 || m660 == 11) {
            return 0;
        }

        m664 = m660;

        //
        // Choose initial message
        //
        if (mType65B == 0) {
            if (m65C == 1) {
                if (dComIfGs_isEventBit(0x910)) {
                    m660 = 0xC95;

                } else {
                    dComIfGs_onEventBit(0x910);
                    m660 = 0xC94;
                }
            } else if (m65C == 3) {
                m660 = 0x100A;
            } else {
                if (!dComIfGs_isEventBit(0x880)) {
                    m660 = 0x1007;
                    dComIfGs_onEventBit(0x880);
                } else {
                    m660 = 0x1009;
                }
            }
        } else if (mType65B == 1) {
            if (m65C == 1) {
                m660 = 0xFA1;
            } else if (m65C == 3) {
                m660 = 0x100D;
            } else {
                if (!dComIfGs_isEventBit(0x840)) {
                    m660 = 0x100B;
                    dComIfGs_onEventBit(0x840);
                } else if (dComIfGs_getClearCount() == 0) {
                    m660 = 0x100C;
                } else {
                    m660 = 0x1034;
                }
            }

            if (m65C == 2) {
                m687 = 0;
            }
        } else {
            if (dComIfGs_isEventBit(0x808)) {
                                m660 = 0x1017;

            } else {
                if (!dComIfGs_isEventBit(0x820)) {
                    m660 = 0x1014;
                    dComIfGs_onEventBit(0x820);
                } else {
                    m660 = 0x1015;
                }
            }
        }

        m659++;
        l_msgId = 0xFFFFFFFF;
    }
    else if (m659 != -1) {
        if (l_msgId == 0xFFFFFFFF) {
            l_msgId = fopMsgM_messageSet(m660, &eyePos);
        }
        else {
            //
            // Enable talking animation
            //
            if (mType65B == 1) {
                if (m65C != 2 && m65C != 3) {
                    m686 = 1;
                }
            } else if (mType65B == 0) {
                if (m65C != 2) {
                    m686 = 1;
                }
            } else {
                m686 = 1;
            }

            setAnimFromMsg();

            if (m659 == 1) {
                l_msg = fopMsgM_SearchByID(l_msgId);

                if (l_msg != NULL) {
                    m659++;
                }
            }
            else if (l_msg->mStatus == 0xE) {
                if (getNextMsgNo(1) != 0xFFFF) {
                    l_msg->mStatus = 0x0F;
                    fopMsgM_messageSet(m660);

                } else {
                    l_msg->mStatus = 0x10;
                }
            }
            else if (l_msg->mStatus == 0x12) {
                if (m65C == 2) {
                    m687 = 1;
                }

                l_msg->mStatus = 0x13;
                ActionFunc cmp = m290;
                if(mPrevAction != cmp){
                    if(m290){
                        m659 = 0xFF;
                        (this->*m290)(NULL);   
                    }
                    mPrevAction = m290;
                    m290 = cmp;
                    m659 = 0;
                    (this->*m290)(NULL);
                }



            }
                dComIfGp_event_onEventFlag(0x8);
        }
    }

    return 1;
}

/* 000013A4-000017A0       .text p1c_speakAction__10daNpc_P1_cFPv */
BOOL daNpc_P1_c::p1c_speakAction(void*) {
    /* Nonmatching */
    if(m659 == 0){
        if(eventInfo.checkCommandTalk()){
            cXyz temp1 = (dComIfGp_getPlayer(0)->current.pos - home.pos);
            if(temp1.absXZ() < 200.0f){
                fopAcM_orderSpeakEvent(this);
                fopAcM_OnCondition(this,dEvtCnd_CANTALK_e);
            }
            return FALSE;
        }
        m660 = 0x1014;
        m664 = 0;
        m659 += 1;
        l_msg = NULL;
        l_msgId = -1;
    }else if(m659 != -1){
        if(l_msgId == -1){
            l_msgId = fopMsgM_messageSet(m660,&eyePos);
        }else{
            setAnimFromMsg();
            if(l_msg == NULL){
                l_msg = fopMsgM_SearchByID(l_msgId);
            }else if(l_msg->mStatus == 0xE){
                if(getNextMsgNo(1) != 0xFFFF){
                    l_msg->mStatus = 0xF;
                    fopMsgM_messageSet(m660);

                }else{
                    l_msg->mStatus = 0x10;
                }
            }else if(l_msg->mStatus == 0x12){
                setAnm(4,8.0f);
                cLib_addCalcPos2(&current.pos,home.pos,0.75f,5.0f);
                cXyz posdiff = current.pos - home.pos;
                f32 dist_xz = posdiff.absXZ();
                if( dist_xz < 1.0f){
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_0820);
                    m64C = 100.0f;
                    l_msg->mStatus = 0x13;
                    ActionFunc local_48 = &daNpc_P1_c::normalAction;
                    if(m290 == local_48){
                        if(m290 != NULL){
                            m659 = -1;
                            (this->*m290)(0);
                        }
                        mPrevAction = m290;
                        m290 = local_48;
                        m659 = 0;
                        (this->*m290)(NULL);
                    }
                    dComIfGp_event_onEventFlag(0x8);
                }
            }
        }
    }
    return TRUE;
}

/* 000017A0-00001C60       .text speakAction__10daNpc_P1_cFPv */
BOOL daNpc_P1_c::speakAction(void*) {
    /* Nonmatching */
    if(m659 == 0){
        if(m664 == 0xFAE){
            //TODO: This matches, but doesn't seem correct.
            dCamera_c* camera = reinterpret_cast<dCamera_c*>(dComIfGp_getCamera(0));
            camera->SkipSmoother();
        }
        if(!eventInfo.checkCommandTalk()){
            cXyz temp1 = (dComIfGp_getPlayer(0)->current.pos - home.pos);
            if(temp1.absXZ() < 400.0f){
                fopAcM_orderSpeakEvent(this);
                fopAcM_OnCondition(this,dEvtCnd_CANTALK_e);
            }
            return FALSE;
        }
        if(m664 == 0xFAE){
            m664 = m660;
            m660 = 0xFA5;
        }else if(dComIfGp_getStartStage()->getPoint() == 2){
            m664 = m660;
            m660 = 0xFAA;      
        }else{
            m664 = m660;
            m660 = 0xFA1;
        }
        m659 += 1;
        l_msgId = -1;
    }else if(m659 != -1){
        if(l_msgId == -1){
            l_msgId = fopMsgM_messageSet(m660,&eyePos);
        }else{
            m686 = 1;
            setAnimFromMsg();
            if(m659 == 1){
                if(m660 == 0xFA5){
                    dCamera_c* camera = (dCamera_c*)dComIfGp_getCamera(0);
                    camera->SkipSmoother();
                }
                l_msg = fopMsgM_SearchByID(l_msgId);
                if(l_msg != NULL){
                    m659 += 1;
                }
            }else if(l_msg->mStatus == 0xE){
                if(getNextMsgNo(1) != 0xFFFF){
                    l_msg->mStatus = 0xF;
                    fopMsgM_messageSet(m660);
                }else{
                    l_msg->mStatus = 0x10;
                }
            }else if(l_msg->mStatus == 0x12){
                l_msg->mStatus = 0x13;
                ActionFunc local_48 = &daNpc_P1_c::normalAction;
                if(m290 != local_48){
                    if(m290 != NULL){
                        m659 = -1;
                        (this->*m290)(0);
                    }
                    mPrevAction = m290;
                    m290 = local_48;
                    m659 = 0;
                    (this->*m290)(NULL);
                }
                if(m664 == 0xFA4){
                    dComIfGp_event_onEventFlag(dEvtCnd_CANTALK_e);
                    fopAcM_orderOtherEvent2(this,"sea_exp_cam",dEvtFlag_NOPARTNER_e);
                    fopAcM_OnCondition(this,dEvtCnd_UNK2_e);
                }
                local_48 = &daNpc_P1_c::explainAction;
                if(m290 == local_48){
                    if(m290 != NULL){
                        m659 = -1;
                        (this->*m290)(0);
                    }
                    mPrevAction = m290;
                    m290 = local_48;
                    m659 = 0;
                    (this->*m290)(NULL);
                }
            }else{
                s8 room = fopAcM_GetRoomNo(this);
                dComIfGp_setNextStage("Ocean",1,room);
            }
        }
    }
    return TRUE;
}

/* 00001C60-00001CD4       .text explainAction__10daNpc_P1_cFPv */
BOOL daNpc_P1_c::explainAction(void*) {
    /* Nonmatching */
    if(m659 == 0){
        m659 += 1;
    }else if(m659 == -1 && !eventInfo.checkCommandTalk()){
        fopAcM_orderSpeakEvent(this);
        fopAcM_OnCondition(this,dEvtCnd_CANTALK_e);
        return FALSE;
    }
    return TRUE;
}

/* 00001CD4-00001DE8       .text getNextMsgNo__10daNpc_P1_cFi */
BOOL daNpc_P1_c::getNextMsgNo(int i_param_1) {
    /* Nonmatching */
    u32 o_retval;


    switch (m660) {
    case 0xC94:
        o_retval = 0xC99;
        break;
    case 0xFA1:
    case 0xFA2:
    case 0xFA5:
    case 0xFA6:
    case 0xFA7:
    case 0xFAA:
    case 0xFAB:
    case 0x1015:
    case 0x1007:
        o_retval = m660 + 1;
        break;
    case 0x1009:
        o_retval = 0x102E;
        break;
    case 0x1016:
        o_retval = 0x1033;
        break;
    case 0xFAE:
        o_retval = 0xFA5;
        break;
    case 0xFA8:
    case 0xFAC:
        o_retval = 0xFA2;
        break;
    case 0xFA3:
        if (l_msg->mSelectNum == 0) {
            o_retval = 0xFA4;
        } else if (l_msg->mSelectNum == 1) {
            o_retval = 0xFB0;
        } else {
            o_retval = -1;
        }
        break;
    case 0xFA4:
    case 0xFA9:
    default:
        o_retval = -1;
        break;
    }
    if (i_param_1 == 1) {
        m664 = m660;
        m660 = o_retval;
    }
    return o_retval;
}

/* 00001DE8-00001E70       .text playTexPatternAnm__10daNpc_P1_cFv */
BOOL daNpc_P1_c::playTexPatternAnm() {
    /* Nonmatching */
    if(!cLib_calcTimer(&mBlinkTimer)){
        m2E0 += 1;
        s16 sVar1 = m2C8->getFrameMax();
        if(m2E0 >= sVar1){
            m2E0 -= sVar1;
            s16 rng = cM_rndF(100.0f);
            mBlinkTimer =  rng + 0x1E;
        }
    }
    return TRUE;
}

/* 00001E70-00002098       .text demo_end_init__10daNpc_P1_cFv */
void daNpc_P1_c::demo_end_init() {
    /* Nonmatching */
    if(m65C == 0){
        m668 = -1;
        ActionFunc local_48 = &daNpc_P1_c::confuseAction;
        bool compare = m290 == local_48; //TODO: unused comparison?
        if(m290 != NULL){
                m659 = -1;
                (this->*m290)(0);
        }
        mPrevAction = m290;
        m290 = local_48;
        m659 = 0;
        (this->*m290)(NULL);
        fopAc_ac_c* actor = fopAcM_SearchByName(fpcNm_Obj_Pirateship_e);
        if(actor){
            current.pos = actor->current.pos;
            current.pos.y += 700.0f;
            current.pos.x += cM_ssin(actor->current.angle.y) * 950.0f;
            current.pos.z += cM_scos(actor->current.angle.y) * 950.0f;
            current.pos.x += cM_scos(actor->current.angle.y) * 150.0f;
            current.pos.z -= cM_ssin(actor->current.angle.y) * 150.0f;
            s16 sVar2 = current.angle.y - 0x4000;
            actor->current.angle.y = sVar2;
            current.angle.y = sVar2;
        }
    }
    m687 = 0;
    m688 = 0;
    m670 = 0;
}

/* 00002098-000021E0       .text demo_move__10daNpc_P1_cFv */
BOOL daNpc_P1_c::demo_move() {
    /* Nonmatching */
    dDemo_actor_c* actor = dComIfGp_demo_getActor(this->demoActorID);
    if(!actor){
        if(m670 == 1){
            demo_end_init();
        }
        return FALSE;
    }else{
        m687 = 1;
        m688 = 1;
        m670 = 1;
        J3DAnmTexPattern* btp = actor->getP_BtpData("P1");
        if(btp){
            mBtp.init(mpModel->getModelData(),btp,1,2);
            m2E0 = 0;
        }
        if(m2D4 != 0){
            u32 uVar1 = m2D4 + 6;
            m2E0 += 1;
            if(m2E0 >= uVar1){
                m2E0 = uVar1;
            }
        }
#if VERSION != VERSION_DEMO
        dDemo_setDemoData(this,0x6A,mpMorf,"P1",NULL,NULL,dBgS_GetGndMtrlSndId_Func(current.pos,10.0f));
#endif
        return TRUE;
    }
}

/* 000021E0-00002244       .text event_move__10daNpc_P1_cFv */
BOOL daNpc_P1_c::event_move() {
    /* Nonmatching */
    if(mEventCut6B0.cutProc()){
        m741 = m710;
        if(m710 == 0){
            m710 = m741;
        }
        return TRUE;
    }else{
        return privateCut();
    }
}

/* 00002244-000022E8       .text evn_setAnm_init__10daNpc_P1_cFi */
BOOL daNpc_P1_c::evn_setAnm_init(int i_staff_id) {
    /* Nonmatching */
    int* idx = dComIfGp_evmng_getMyIntegerP(i_staff_id, "idx");

    if (idx != NULL) {
        setAnm(*idx, -1.0f);
    } else if (mType65B == 2) {
        setAnm(4, -1.0f);
    } else {
        setAnm(0, -1.0f);
    }

    return TRUE;
}

/* 000022E8-00002364       .text evn_talk_init__10daNpc_P1_cFi */
BOOL daNpc_P1_c::evn_talk_init(int i_staff_id) {
    /* Nonmatching */
    int* idx = dComIfGp_evmng_getMyIntegerP(i_staff_id, "idx");
    l_msgId = -1;
    l_msg = NULL;
    if(idx != NULL){
        m660 = *idx;

    }else{
        m660 = 0;
    }
    return TRUE;
}

/* 00002364-00002464       .text evn_talk__10daNpc_P1_cFv */
BOOL daNpc_P1_c::evn_talk() {
    /* Nonmatching */
  if (l_msgId == 0xffffffff) {
    l_msgId = fopMsgM_messageSet(m660,&eyePos);
  }
  else if (l_msg == NULL) {
    l_msg = fopMsgM_SearchByID(l_msgId);
  }
  else if (l_msg->mStatus == 0xe) {
    if (getNextMsgNo(true) != 0xFFFF) {
      l_msg->mStatus = 0xf;
      fopMsgM_messageSet(m660);
    }
    else {
      l_msg->mStatus = 0x10;
    }
  }
  else if (l_msg->mStatus == 0x12) {
    l_msg->mStatus = 0x13;
    l_msg = NULL;
    l_msgId = -1;

    return 1;
  }
  return 0;
}


/* 00002464-000027AC       .text minigameExplainCut__10daNpc_P1_cFv */
BOOL daNpc_P1_c::minigameExplainCut() {
    /* Nonmatching */
    static char* ActionNames[] = {"4013_msg"};
    int staffId = dComIfGp_evmng_getMyStaffId(mEventCut6B0.getActorName(), NULL);

    int actIdx = dComIfGp_evmng_getMyActIdx(staffId,ActionNames,2,1,0);

    if (staffId == -1) {
        m741 = 0;
        return 0;
    }
    if(m65A == 0){
            l_msgId = -1;
            dComIfGp_onCameraAttentionStatus(0,4);
            m664 = m660;
            m660 = 0xFAD;
            m65A++;
    }else if(m65A != -1){


            if (l_msgId == -1) {
                l_msgId = fopMsgM_messageSet(m660, &eyePos);

            }

    } else if (m65A == 1) {
            l_msg = fopMsgM_SearchByID(l_msgId);
            if (l_msg != NULL) {
                m65A++;
            }

    }else{
            if(l_msg->mStatus == 0xE){
                if (m660 == 0xFAD) {
                    l_msg->mStatus = 0x0F;

                    m664 = m660;
                    m660 = 0xFAE;
                    fopMsgM_messageSet(m660);
                } else {
                    m664 = m660;
                    m660 = -1;
                    l_msg->mStatus = 0x10;
                }
            }else if(l_msg->mStatus == 0x12){
                if (actIdx == 1) {
                    dComIfGp_evmng_cutEnd(staffId);
                }

                l_msg->mStatus = 0x13;
                dComIfGp_offCameraAttentionStatus(0,4);

            }






            else if (dComIfGp_checkMesgSendButton() && actIdx == 0) {
                dComIfGp_evmng_cutEnd(staffId);
            }
            if(checkAction(&daNpc_P1_c::explainAction)){
                if(dComIfGp_evmng_endCheck("sea_exp_cam")){
                    setAction(&daNpc_P1_c::speakAction,&m290,0);

                };
            }

                dComIfGp_event_onEventFlag(8);
                dCamera_c* camera = reinterpret_cast<dCamera_c*>(dComIfGp_getCamera(0));

                camera->SkipSmoother();

                fopAcM_orderSpeakEvent(this);
                eventInfo.onCondition(dEvtCnd_CANTALK_e);

        
    }

    return 1;
}

/* 000027AC-00002920       .text privateCut__10daNpc_P1_cFv */
BOOL daNpc_P1_c::privateCut() {
    /* Nonmatching */
    static char* cut_name_tbl[] = {"4013_mesg","4014_mesg","SETANM","HEADSWING","TALKMSG"};
    int staffIdx = dComIfGp_evmng_getMyStaffId(mEventCut6B0.getActorName());
    if(staffIdx == -1){
        return FALSE;
    }
    int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx,cut_name_tbl,5,true,0);
    if(actIdx == -1){
        dComIfGp_evmng_cutEnd(staffIdx);
    }else{
        int iVar4 = 0;
        if(dComIfGp_evmng_getIsAddvance(staffIdx)){
            switch(actIdx){
                case 2:
                    evn_setAnm_init(staffIdx);

                    break;
                case 3:
                    m71C.swing_vertical_init(2,0x1000,0x800,1);
                    break;
                case 4:
                    evn_talk_init(staffIdx);
            }
        }
        switch(actIdx){
            case 0:
            case 1:
                minigameExplainCut();
                break;

            case 4:
                iVar4 = evn_talk();
                setAnimFromMsg();
                break;
            default:
                iVar4 = 1;
                break;
        }
        if(iVar4 != 0){
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }
    return TRUE;

}

/* 00002920-00002A7C       .text nodeCallBack1__FP7J3DNodei */
static BOOL nodeCallBack1(J3DNode* i_node, int i_param_2) {
    /* Nonmatching */
    if(i_param_2 == J3DNodeCBCalcTiming_In){
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)i_node;
        daNpc_P1_c* i_this = (daNpc_P1_c*)model->getUserArea();
        s32 jntNo = joint->getJntNo();
        if(i_this){
            PSMTXCopy(model->getAnmMtx(jntNo),*calc_mtx);
            if(jntNo == i_this->m_jnt.getHeadJntNum()){
                cXyz local_28(REG10_F(0),REG10_F(1),REG10_F(2));
                cMtx_YrotM(*calc_mtx,-(i_this->m_jnt.getHead_x() + i_this->m71C.field_0x02));
                cMtx_ZrotM(*calc_mtx,-(i_this->m_jnt.getHead_y() + i_this->m71C.field_0x00));
                MtxPosition(&local_28,&i_this->eyePos);
            }
            if(jntNo == i_this->m_jnt.getBackboneJntNum()){
                mDoMtx_XrotM(*calc_mtx,i_this->m_jnt.getBackbone_y());
                mDoMtx_ZrotM(*calc_mtx,i_this->m_jnt.getBackbone_x());
            }

            model->setAnmMtx(jntNo,*calc_mtx);
            cMtx_copy(*calc_mtx,J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00002A7C-00002A9C       .text daNpc_P1_Draw__FP10daNpc_P1_c */
static BOOL daNpc_P1_Draw(daNpc_P1_c* i_this) {
    return ((daNpc_P1_c*)i_this)->_draw();
}

/* 00002A9C-00002ABC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    /* Nonmatching */
    return reinterpret_cast<daNpc_P1_c*>(i_this)->CreateHeap();
}

/* 00002ABC-00002B00       .text setAttentionPos__10daNpc_P1_cFP4cXyz */
BOOL daNpc_P1_c::setAttentionPos(cXyz* i_param_1) {
    /* Nonmatching */
    i_param_1->set(eyePos);
    i_param_1->y = i_param_1->y + l_HIO.children[mType65B].m10;
    return TRUE;
}

/* 00002B00-00003484       .text _create__10daNpc_P1_cFv */
cPhs_State daNpc_P1_c::_create() {
    /* Nonmatching */
}

/* 00003834-00003D6C       .text CreateHeap__10daNpc_P1_cFv */
BOOL daNpc_P1_c::CreateHeap() {
    /* Nonmatching */
    J3DModelData* model_data_p = static_cast<J3DModelData*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BDL_P1_e));
    // mDoExt_McaMorf* this_00;// = new mDoExt_McaMorf();
    // if(!this_00){
    //     J3DAnmTransformKey* anm_res_p = static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BCK_WAIT_e));
    //     this_00 = 
    // }
    mpMorf = new mDoExt_McaMorf(model_data_p,NULL,NULL,static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BCK_WAIT_e)),J3DFrameCtrl::EMode_LOOP,1.0f,0,-1,1,NULL,0x80000,0x11020002);;
    if (!mpMorf || !mpMorf->getModel()) {
#if VERSION > VERSION_DEMO
        //mpMorf = NULL;
#endif
        return FALSE;
    }
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);

    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    m_jnt.setHeadJntNum(model_data_p->getJointName()->getIndex("head"));
    JUT_ASSERT(DEMO_SELECT(0x639,0x639),m_jnt.getHeadJntNum() >= 0);
    m_jnt.setHeadJntNum(model_data_p->getJointName()->getIndex("backbone"));
    JUT_ASSERT(DEMO_SELECT(0x639,0x639),m_jnt.getBackboneJntNum() >= 0);
    m_handR_jnt_num = model_data_p->getJointName()->getIndex("handR");
    JUT_ASSERT(DEMO_SELECT(0x639,0x639),m_handR_jnt_num >= 0);
    J3DModelData* head_model_data_p;

    J3DAnmTexPattern* btp_p;
    if(mType65B == 0){
        head_model_data_p = static_cast<J3DModelData*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BDL_P1A_HEAD_e));
        btp_p = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BTP_MABA_A_e));
        m2C8 = btp_p;
    }else if(mType65B == 1){
        head_model_data_p = static_cast<J3DModelData*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BDL_P1B_HEAD_e));
        btp_p = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BTP_MABA_B_e));
        m2C8 = btp_p;
    }else{
        head_model_data_p = static_cast<J3DModelData*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BDL_P1C_HEAD_e));
        btp_p = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BTP_MABA_C_e));
        m2C8 = btp_p;
    }
    J3DAnmTexPattern* dummy_text_all_p = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BTP_P1A_DUMMY_TEX_ALL_e));
    mpModel = mDoExt_J3DModel__create(head_model_data_p,0x80000,0x10020002);
    if(m2C8 == NULL){
        return FALSE;
    }
    if(mBtp.init(head_model_data_p,dummy_text_all_p,TRUE,2)){
        return FALSE;
    }
    mBtp.init(head_model_data_p,m2C8,TRUE,2);
    if(mType65B == 1 && strcmp(dComIfGp_getStartStageName(), "sea") == 0 && 
    fopAcM_GetRoomNo(this) == dIsleRoom_OutsetIsland_e && dComIfGp_getStartStageLayer() == 0xA){
        mDoExt_J3DModel__create(static_cast<J3DModelData*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BDL_DORA_STICK_e)),0x80000,0x11000002);
    
    }
}

/* 00003D6C-00003DF8       .text _delete__10daNpc_P1_cFv */
BOOL daNpc_P1_c::_delete() {
    /* Nonmatching */
}

/* 00003DF8-00003E70       .text getKajiID__10daNpc_P1_cFv */
void daNpc_P1_c::getKajiID() {
    /* Nonmatching */
}

/* 00003E70-000043CC       .text kaji_anm__10daNpc_P1_cFv */
void daNpc_P1_c::kaji_anm() {
    /* Nonmatching */
}

/* 000043CC-0000458C       .text _execute__10daNpc_P1_cFv */
BOOL daNpc_P1_c::_execute() {
    /* Nonmatching */
}

/* 0000458C-00004814       .text _draw__10daNpc_P1_cFv */
BOOL daNpc_P1_c::_draw() {
    /* Nonmatching */
}

/* 00004814-00004BA0       .text lookBack__10daNpc_P1_cFv */
void daNpc_P1_c::lookBack() {
    /* Nonmatching */
}

/* 00004BA0-00004BC4       .text daNpc_P1_Execute__FP10daNpc_P1_c */
static BOOL daNpc_P1_Execute(daNpc_P1_c* i_this) {
    ((daNpc_P1_c*)i_this)->_execute();
    return TRUE;
}

/* 00004BC4-00004BCC       .text daNpc_P1_IsDelete__FP10daNpc_P1_c */
static BOOL daNpc_P1_IsDelete(daNpc_P1_c*) {
    return TRUE;
}

/* 00004BCC-00004BEC       .text daNpc_P1_Delete__FP10daNpc_P1_c */
static BOOL daNpc_P1_Delete(daNpc_P1_c* i_this) {
    return ((daNpc_P1_c*)i_this)->_delete();
}

/* 00004BEC-00004C0C       .text daNpc_P1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_P1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_P1_c*)i_this)->_create();
}

static actor_method_class l_daNpc_P1_Method = {
    (process_method_func)daNpc_P1_Create,
    (process_method_func)daNpc_P1_Delete,
    (process_method_func)daNpc_P1_Execute,
    (process_method_func)daNpc_P1_IsDelete,
    (process_method_func)daNpc_P1_Draw,
};

actor_process_profile_definition g_profile_NPC_P1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_P1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_P1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_P1_e,
    /* Actor SubMtd */ &l_daNpc_P1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
