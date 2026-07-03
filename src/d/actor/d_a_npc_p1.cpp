/**
 * d_a_npc_p1.cpp
 * NPC - Gonzo, Senza, & Nudge
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_p1.h"

#include "d/actor/d_a_kaji.h"
#include "d/actor/d_a_obj_pirateship.h"
#include "d/d_bg_s_func.h"
#include "d/d_camera.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "res/Object/P1.h"


class daNpc_P1_childHIO_c{
public:
    daNpc_P1_childHIO_c();
    virtual ~daNpc_P1_childHIO_c(){};

public:
    /* Place member variables here */
    /* 0x04 */ s8 unk4;                             /* inferred */
               f32 mAttnYPosOffset;
               s16 mC;
               s16 mE;
               s16 m10;
               s16 m12;
    /* 0x14 */ s16 m14;                           /* inferred */
               s16 m16;
    /* 0x18 */ s16 m18;                           /* inferred */
    /* 0x1A */ s16 m1A;                           /* inferred */
    /* 0x1C */ s16 m1C;                           /* inferred */
    /* 0x1E */ s16 m1E;                           /* inferred */
    /* 0x20 */ s8 m20;                           /* inferred */
    /* 0x22 */ s16 m22;                           /* inferred */
               f32 m24;
               f32 mMorf;
               f32 m2C;

    //SIZE = 0x30
};



class daNpc_P1_HIO_c{
public:
    daNpc_P1_HIO_c();
    virtual ~daNpc_P1_HIO_c(){};
public:
    s8 m4;
    s32 m8;
    daNpc_P1_childHIO_c children[3];
};


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

static daNpc_P1_HIO_c l_HIO;
static msg_class* l_msg;
static fpc_ProcID l_msgId;

/* 000000EC-00000264       .text __ct__14daNpc_P1_HIO_cFv */
daNpc_P1_HIO_c::daNpc_P1_HIO_c() {

    children[0].mAttnYPosOffset = 50.0f;
    children[0].mC = 0x9C4;
    children[0].mE = 0xF63C;
    children[0].m10 = 2000;
    children[0].m12 = 0xF830;
    children[0].m14 = 5000;
    children[0].m16 = 0xEC78;
    children[0].m18 = 8000;
    children[0].m1A = 0xE0C0;
    children[0].m1C = 1000;
    children[0].m1E = 0x708;
    children[0].m20 = 0;
    children[0].m24 = 300.0f;
    children[0].mMorf = 8.0f;
    children[0].m2C = 8.0f;
    children[1].mAttnYPosOffset = 45.0f;
    children[1].mC = 0x9C4;
    children[1].mE = 0xF63C;
    children[1].m10 = 2000;
    children[1].m12 = 0xF830;
    children[1].m14 = 10000;
    children[1].m16 = 0xD8F0;
    children[1].m18 = 8000;
    children[1].m1A = 0xE0C0;
    children[1].m1C = 1000;
    children[1].m1E = 0x708;
    children[1].m20 = 0;
    children[1].m24 = 250.0f;
    children[1].mMorf = 8.0f;
    children[1].m2C = 8.0f;
    children[2].mAttnYPosOffset = 45.0f;
    children[2].mC = 0x9C4;
    children[2].mE = 0xF63C;
    children[2].m10 = 2000;
    children[2].m12 = 0xF830;
    children[2].m14 = 5000;
    children[2].m16 = 0xEC78;
    children[2].m18 = 8000;
    children[2].m1A = 0xE0C0;
    children[2].m1C = 1000;
    children[2].m1E = 0x708;
    children[2].m20 = 0;
    children[2].m24 = 250.0f;
    children[2].mMorf = 7.0f;
    children[2].m2C = 16.0f;
    m4 = -1;
    m8 = -1;

}


/* 000002AC-000002BC       .text __ct__19daNpc_P1_childHIO_cFv */
daNpc_P1_childHIO_c::daNpc_P1_childHIO_c() {
    /* Nonmatching */
}

/* 000002BC-0000051C       .text setAnimFromMsg__10daNpc_P1_cFv */
void daNpc_P1_c::setAnimFromMsg() {
    /* Nonmatching */


    if ((m668 == 10 || m668 == 11) && !mpMorf->checkFrame(
        mpMorf->getEndFrame() - 1.0f
    )) {
        return;
    }

    if (m668 == 8 && mpMorf->checkFrame(
        mpMorf->getEndFrame() - 1.0f
    )) {
        if (--m66C <= 0) {
            setAnm(4, 15.0f);
        }
    } else if (m668 == 12 && mpMorf->checkFrame(
        mpMorf->getEndFrame() - 1.0f
    )) {
        if (--m66C <= 0) {
            setAnm(9, 8.0f);
        }
    }
    int iVar1;
  switch(dComIfGp_getMesgAnimeAttrInfo()) {
  case 0:
    if (mType65B != 2) {
      iVar1 = 0;
    }
    else {
      iVar1 = 4;
    }
    break;
  case 1:
    iVar1 = 1;
    break;
  case 2:
    iVar1 = 2;
    break;
  case 3:
    iVar1 = 3;
    break;
  case 4:
    if (mType65B != 2) {
      iVar1 = 9;
    }
    else {
      iVar1 = 4;
    }
    break;
  case 5:
    iVar1 = 10;
    break;
  case 6:
    iVar1 = 0xb;
    break;
  case 7:
    iVar1 = 0xc;
    m66C = 4;
    break;
  case 8:
    iVar1 = 0xd;
    break;
  case 9:
    iVar1 = 0xe;
    break;
  case 10:
    iVar1 = 0xf;
    break;
  case 0xb:
    iVar1 = 0x10;
    break;
  case 0xc:
    iVar1 = 4;
    break;
  case 0xd:
    iVar1 = 5;
    break;
  case 0xe:
    iVar1 = 6;
    break;
  case 0xf:
    iVar1 = 7;
    break;
  case 0x10:
    iVar1 = 8;
    m66C= 6;
    break;
  default:
    return;
  }
  dComIfGp_setMesgAnimeAttrInfo(0xFF);
  setAnm(iVar1,-1.0);

  return;
}

/* 0000051C-00000AD0       .text setAnm__10daNpc_P1_cFif */
BOOL daNpc_P1_c::setAnm(int i_anm, f32 i_morf) {
    /* Nonmatching */
    if (m668 == i_anm) {
        return false;
    }

    m668 = i_anm;

    if (i_morf < 0.0f) {
        i_morf = l_HIO.children[mType65B].mMorf;
    }

    J3DAnmTransform* anm = NULL;
    int attr = J3DFrameCtrl::EMode_LOOP;

    switch (i_anm) {
    case 0:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_WAIT_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 1:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_TALK_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 2:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_TALK02_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 3:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_TALK03_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 9:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_WAIT02_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 10:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_OMOKJ_e);
        attr = J3DFrameCtrl::EMode_NONE;
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 11:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_TORIKJ_e);
        attr = J3DFrameCtrl::EMode_NONE;
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 12:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_ANGRY_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 13:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_TALK04_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 14:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_CHECK01_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 15:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_CHECK02_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;


    case 16:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_LOOK_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;


    case 4:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_C_WAIT_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 5:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_C_TALK01_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 6:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_C_TALK02_e);
        attr = J3DFrameCtrl::EMode_NONE;
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);

        break;

    case 7:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_C_STOP_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;

    case 8:
        anm = (J3DAnmTransform*)dComIfG_getObjectRes("P1", dRes_INDEX_P1_BCK_C_TALK01_e);
        mpMorf->setAnm(anm, attr, i_morf, 1.0f, 0.0f, -1.0f, NULL);
        break;
    }
    return TRUE;
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
                m_jnt.onBackBoneLock();
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
                    m_jnt.onBackBoneLock();
                }
            } else if (mType65B == 0) {
                if (m65C != 2) {
                    m_jnt.onBackBoneLock();
                }
            } else {
                m_jnt.onBackBoneLock();
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
                    m_jnt.onBackBoneLock();
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
                    mCyl.SetR(100.0f);
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
            m_jnt.setTrn();
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
    
    if(!cLib_calcTimer(&mBlinkTimer)){
        m2E0 += 1;
        if(m2E0 >= mpTexture->getFrameMax()){
            m2E0 -= mpTexture->getFrameMax();
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
        m_jnt.offHeadLock();
        m_jnt.offBackBoneLock();
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
        m_jnt.onHeadLock();
        m_jnt.onBackBoneLock();
        m670 = 1;
        J3DAnmTexPattern* btp = actor->getP_BtpData("P1");
        if(btp){
            mBtp.init(mpHeadModel->getModelData(),btp,1,2,1.0f,0,-1,true,FALSE);
            m2E0 = 0;
        }
        if(mBtp.getBtpAnm()){
            u8 uVar1 = mBtp.getBtpAnm()->getFrameMax();
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
        m741 = mEventCut6B0.getAttnFlag();
        if(mEventCut6B0.getAttnFlag() == 0){
            mEventCut6B0.setAttnFlag(m741);
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
    static char* cut_name_tbl[] = {"4013_msg","4014_msg","SETANM","HEADSWING","TALKMSG"};
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
                cMtx_YrotM(*calc_mtx,-( i_this->m71C.field_0x02 + i_this->m_jnt.getHead_y()));
                cMtx_ZrotM(*calc_mtx,-( i_this->m71C.field_0x00 + i_this->m_jnt.getHead_x()));
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
    i_param_1->set(eyePos);
    i_param_1->y = i_param_1->y + l_HIO.children[mType65B].mAttnYPosOffset;
    return TRUE;
}

/* 00002B00-00003484       .text _create__10daNpc_P1_cFv */
cPhs_State daNpc_P1_c::_create() {
    /* Nonmatching */
    fopAcM_SetupActor(this, daNpc_P1_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, "P1");
    if (state == cPhs_COMPLEATE_e) {
        
    }
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
    JUT_ASSERT(DEMO_SELECT(0x634,0x639),m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(model_data_p->getJointName()->getIndex("backbone"));
    JUT_ASSERT(DEMO_SELECT(0x639,0x63E),m_jnt.getBackboneJntNum() >= 0);
    m_handR_jnt_num = model_data_p->getJointName()->getIndex("handR");
    JUT_ASSERT(DEMO_SELECT(0x63C,0x641),m_handR_jnt_num >= 0);
    
    J3DModelData* head_model_data_p;
    if(mType65B == 0){
        head_model_data_p = static_cast<J3DModelData*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BDL_P1A_HEAD_e));
        mpTexture = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BTP_MABA_A_e));
    }else if(mType65B == 1){
        head_model_data_p = static_cast<J3DModelData*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BDL_P1B_HEAD_e));
        mpTexture = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BTP_MABA_B_e));
    }else{
        head_model_data_p = static_cast<J3DModelData*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BDL_P1C_HEAD_e));
        mpTexture = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BTP_MABA_C_e));
    }
    J3DAnmTexPattern* dummy_text_all_p = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BTP_P1A_DUMMY_TEX_ALL_e));
    mpHeadModel = mDoExt_J3DModel__create(head_model_data_p,0x80000,0x11020002);
    if(mpTexture == NULL){
        return FALSE;
    }
#if VERSION == VERSION_DEMO
    mBtp.init(head_model_data_p,dummy_text_all_p,TRUE,2);
#else
    if(!mBtp.init(head_model_data_p,dummy_text_all_p,TRUE,2)){
        return FALSE;
    }
#endif

    mBtp.init(head_model_data_p,mpTexture,TRUE,2,1.0f,0,-1,true,FALSE);
    if(mType65B == 1 && strcmp(dComIfGp_getStartStageName(), "sea") == 0 && 
    fopAcM_GetRoomNo(this) == dIsleRoom_OutsetIsland_e && dComIfGp_getStartStageLayer() == 0xA){
        mpDoraModel = mDoExt_J3DModel__create(static_cast<J3DModelData*>(dComIfG_getObjectRes("P1",dRes_INDEX_P1_BDL_DORA_STICK_e)),0x80000,0x11000002);
        if(mpDoraModel == NULL){
            return FALSE;
        }
    }else{
        mpDoraModel = NULL;
    }
        J3DJointTree& tree = model_data_p->getJointTree(); 
    for (u16 i = 0; i < tree.getJointNum(); i += 1) {
        if ((i == m_jnt.getHeadJntNum()) || (i == m_jnt.getBackboneJntNum())) {
            model_data_p->getJointNodePointer(i)->setCallBack(nodeCallBack1);
        }
    }
    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f,0.0f);
    mAcch.Set(
        fopAcM_GetPosition_p(this),
        fopAcM_GetOldPosition_p(this),
        this,
        1,
        &mAcchCir,
        fopAcM_GetSpeed_p(this),
        fopAcM_GetAngle_p(this),
        fopAcM_GetShapeAngle_p(this));   
    if(mType65B == 1){
        if(m65C  == 3){
            mAcch.SetWallNone();

        }
    } 

            return TRUE;
}

/* 00003D6C-00003DF8       .text _delete__10daNpc_P1_cFv */
BOOL daNpc_P1_c::_delete() {
    /* Nonmatching */


    dComIfG_resDeleteDemo(&mPhs, "P1");
    if (DEMO_SELECT(true, heap) && mpMorf) {
        mpMorf->stopZelAnime();
    }


    if(l_HIO.m8 >= 0){
        l_HIO.m8 -= 1;
        if(l_HIO.m8 < 0){
            mDoHIO_deleteChild(l_HIO.m4);
        }
    }
    return TRUE;
}

/* 00003DF8-00003E70       .text getKajiID__10daNpc_P1_cFv */
fpc_ProcID daNpc_P1_c::getKajiID() {
    /* Nonmatching */
    fpc_ProcID pnVar2 = 0xFFFFFFFF;
    fpc_ProcID id = parentActorID;
    if(id != -1){
        daObjPirateship::Act_c* actor = (daObjPirateship::Act_c*)fopAcM_SearchByID(id);
        if(fopAc_IsActor(actor) && fopAcM_GetName(actor) == fpcNm_Obj_Pirateship_e){
            pnVar2 = actor->m300;
        }
    }
    return pnVar2;
}

/* 00003E70-000043CC       .text kaji_anm__10daNpc_P1_cFv */
BOOL daNpc_P1_c::kaji_anm() {
    /* Nonmatching */
    if(m671 != 0){
        if(m668 == 0xA || m668 == 0xB){
            if(mpMorf->checkFrame(mpMorf->getEndFrame()-1.0f)){
                setAnm(9,-1.0f);
                m678 = 0x12C;
            }else if(mpMorf->checkFrame(30.0f)){
                fopAcM_seStart(this,JA_SE_OBJ_PIRATE_WHEEL,0);
            }
        
        }else{
            if(--m678 < 0){
                if(mpMorf->checkFrame(mpMorf->getEndFrame()-1.0f)){
                    if(!checkAction(&daNpc_P1_c::talkAction)){
                        if(cM_rndF(1.0f) > 0.5f){
                            setAnm(0xA,-1.0f);

                        }else{
                            setAnm(0xB,-1.0f);
                        }
                    }
                }
            }
        }
    }
    if(m674 != 0xFFFF){
        daKaji_c* actor = (daKaji_c*)fopAcM_SearchByID(m674);
        if(fopAc_IsActor(actor) && fopAcM_GetName(actor) == fpcNm_Kaji_e){
            f32 fVar5 = mpMorf->getStartFrame();
            J3DAnmTransform* pAnimRes;
            void* pSoundAnimRes;
            f32 frame = mpMorf->getFrame();
            switch(m668 - 9){
                case 0:
                    pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Kaji",0xE);
                    pSoundAnimRes = dComIfG_getObjectRes("Kaji",8);
                    break;
                case 1:
                    pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Kaji",0xC);
                    pSoundAnimRes = dComIfG_getObjectRes("Kaji",6);
                    break;
                case 2:
                    pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Kaji",0xD);
                    pSoundAnimRes = dComIfG_getObjectRes("Kaji",7);
                    break;      
                case 3:
                    pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Kaji",0xB);
                    pSoundAnimRes = dComIfG_getObjectRes("Kaji",5);
                    break;

            }
            actor->mpMorf->setAnm(pAnimRes,J3DFrameCtrl::EMode_LOOP,0.0,1.0,0.0,-1.0,pSoundAnimRes);
            if(frame >= 0.0f){
                actor->mpMorf->setFrame(frame);
            }
        }
        return TRUE;
    }else{
        // return TRUE;    

        if(mType65B == 1 && m65C == 2){
            if(!checkAction(&daNpc_P1_c::talkAction)){
                if(m668 == 0xE){
                    if(mpMorf->checkFrame(mpMorf->getEndFrame()-1.0f)){
                        if(--m66C <= 0){
                            setAnm(0xF,-1.0f);
                            if(cM_rndF(1.0f) > 0.05f){
                                m66C = 1;

                            }else{
                                m66C = 2;
                            }


                        }

                    }
                }else {
                    if(m668 == 0xF){
                        if(mpMorf->checkFrame(mpMorf->getEndFrame()-1.0f)){
                            if(--m66C <= 0){
                                setAnm(0xE,-1.0f);
                                m66C = 4;
                            }
                        }
                    }
                }
            }
        }
    }
    return FALSE;

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
