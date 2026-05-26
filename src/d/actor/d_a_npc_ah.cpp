/**
 * d_a_npc_ah.cpp
 * NPC - Old Man Ho Ho
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ah.h"
#include "d/d_a_obj.h"
#include "d/d_com_lib_game.h"
#include "d/d_snap.h"
#include "d/res/res_ah.h"

const char daNpcAh_c::m_arcname[] = "Ah"; 

static const int l_bmd_ix_tbl[] = {
    AH_BDL_AH
};

static const int l_bck_ix_tbl[] = {
    AH_BCK_AH_WAIT01,
    AH_BCK_AH_WAIT02
};

static const int l_btp_ix_tbl[] = {
    AH_BTP_MABA,
    AH_BTP_HOU
};

static char* l_npc_staff_id[] = {
    "Ah"
};

static const char* l_arcname_tbl[] = {"Ah"};

static sAhAnmDat l_npc_anm_wait = {
    0x00,
    0x08,
    0xff
};

static sAhAnmDat l_npc_anm_wait2 = {
    0x01,
    0x08,
    0xff
};

static NpcDatStruct l_npc_dat = {
    0x1000, 0x2000, 0x0000, 0x1000,
    0xF000, 0xE000, 0x0000, 0xF000,
    0X0800, 0x0000, 0.0f  , 0.0f  ,
    190.0f, -20.0f, 150.0f, 200.0f,
    0.0f  , 0x7FFF, 0x0800, 0x0190,
    0x0000, 60.0f , 0.5f  , 3.0f  ,
    0x0006, 0x0400, 0x003C, 0x005A,
    0x00C8, 0x012C, 0x001E, 0x00, 0x00
};

static u32 l_msg_ah_0[] = {
    0x36B1,
    0x0000
};
static u32 l_msg_ah_1[] = {
    0x36B2,
    0x0000
};
static u32 l_msg_ah_2[] = {
    0x36B3,
    0x0000
};
static u32 l_msg_ah_3[] = {
    0x36B4,
    0x0000
};
static u32 l_msg_ah_4[] = {
    0x36B5,
    0x0000
};
static u32 l_msg_ah_5[] = {
    0x36B6,
    0x0000
};
static u32 l_msg_ah_6[] = {
    0x36B7,
    0x0000
};
static u32 l_msg_ah_7[] = {
    0x36B8,
    0x0000
};
static u32 l_msg_ah_8[] = {
    0x36B9,
    0x0000
};
static u32 l_msg_ah_9[] = {
    0x36BA,
    0x0000
};

static u32 *l_msg_ah_tbl[] = {
    l_msg_ah_0,
    l_msg_ah_1,
    l_msg_ah_2,
    l_msg_ah_3,
    l_msg_ah_4,
    l_msg_ah_5,
    l_msg_ah_6,
    l_msg_ah_7,
    l_msg_ah_8,
    l_msg_ah_9,

};

/* 00000078-00000210       .text __ct__9daNpcAh_cFv */
daNpcAh_c::daNpcAh_c() {
    setResFlag(0);
    mMoveState = 0;
    field_0x718 = 0.0f;
    field_0x72C = 0;
    field_0x71C = -1.0f;
    field_0x74E = 0;
    mHeadOnlyFollow = true;
    field_0x732 = home.angle.y;
    mBckIdx = 0;
    field_0x736 = 0;
}

/* 000005C0-000006DC       .text da_Npc_Ah_nodeCallBack__FP7J3DNodei */
static BOOL da_Npc_Ah_nodeCallBack(J3DNode* node, int calcTiming) {
    if(calcTiming == J3DNodeCBCalcTiming_In){
        J3DModel* model = j3dSys.getModel();
        daNpcAh_c* i_this = (daNpcAh_c*)model->getUserArea();
        J3DJoint* joint = (J3DJoint*)node;
        
        u16 jointNo = joint->getJntNo();
        MTXCopy(model->getAnmMtx(jointNo), *calc_mtx);

        if(jointNo == i_this->m_jnt.getHeadJntNum()){
            mDoMtx_XrotM(*calc_mtx, i_this->m_jnt.getHead_y());
            cMtx_ZrotM(*calc_mtx, -i_this->m_jnt.getHead_x());
        }
        else if(jointNo == i_this->m_jnt.getBackboneJntNum()){
            mDoMtx_XrotM(*calc_mtx, i_this->m_jnt.getBackbone_y());
            cMtx_ZrotM(*calc_mtx, -i_this->m_jnt.getBackbone_x());
        }
#if VERSION > VERSION_DEMO
        MTXCopy(*calc_mtx, model->getAnmMtx(jointNo));
#else
        Mtx* src = calc_mtx;
        MTXCopy(*src, model->getAnmMtx(jointNo));
#endif
        MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 000006DC-000006FC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpcAh_c*)i_this)->createHeap();
}

/* 000006FC-00000828       .text phase_1__FP9daNpcAh_c */
static cPhs_State phase_1(daNpcAh_c* i_this) {
    fopAcM_ct(i_this, daNpcAh_c);
    u8 prmArg = i_this->getPrmArg0();
    switch (prmArg) {
        case 2:
            if(fopAcM_isSwitch(i_this, 0x6c)){
                return cPhs_STOP_e;
            }
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)){
                return cPhs_STOP_e;
            }
            break;
        case 5:
            if(fopAcM_isSwitch(i_this, 0x10)){
                return cPhs_STOP_e;
            }
            break;
        case 9:
            if(fopAcM_isSwitch(i_this, i_this->getSwBit())){
                return cPhs_STOP_e;
            }
            break;
    }
    i_this->setResFlag(1);
    return cPhs_NEXT_e;
}

/* 00000828-000008D8       .text phase_2__FP9daNpcAh_c */
static cPhs_State phase_2(daNpcAh_c* i_this) {
    cPhs_State state = dComIfG_resLoad(i_this->getPhaseP(), l_arcname_tbl[0]);
    if(state == cPhs_COMPLEATE_e){
        i_this->getPrmArg0();
        if(fopAcM_entrySolidHeap(i_this, CheckCreateHeap, 0x2F00)){
            state = i_this->createInit();
        }
        else {            
            i_this->getPrmArg0();
#if VERSION > VERSION_DEMO
            i_this->mpMorf = NULL;
#endif
            return cPhs_ERROR_e;
        }
        
    }
    if(state == cPhs_ERROR_e){
        i_this->getPrmArg0();
    }
    return state;

}

/* 000008D8-00000908       .text _create__9daNpcAh_cFv */
cPhs_State daNpcAh_c::_create() {
    static cPhs__Handler l_method[] = {
        (cPhs__Handler) &phase_1,
        (cPhs__Handler) &phase_2,
        NULL
    };
    return dComLbG_PhaseHandler(&mPhsMethod, l_method, this);
}

/* 00000908-00000BA4       .text createHeap__9daNpcAh_cFv */
BOOL daNpcAh_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*) dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bmd_ix_tbl[0]); 
    mpMorf = new mDoExt_McaMorf(
        modelData, 
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bck_ix_tbl[mBckIdx]),
        J3DFrameCtrl::EMode_LOOP, 
        1.0f, 
        0, 
        -1, 
        1, 
        NULL, 
        0x80000, 
        0x11020022
    );
#if VERSION > VERSION_DEMO
    if(mpMorf == NULL || mpMorf->getModel() == NULL) return FALSE;
#endif
    m_jnt.setHeadJntNum(modelData->getJointTree().getJointName()->getIndex("head"));
    JUT_ASSERT(DEMO_SELECT(0x2B4, 0x2B8), m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(modelData->getJointTree().getJointName()->getIndex("backbone"));
    JUT_ASSERT(DEMO_SELECT(0x2B8, 0x2BC), m_jnt.getBackboneJntNum() >= 0);

    if(initTexPatternAnm(false) == FALSE) return FALSE;

    for(u16 jntIdx = 0; jntIdx < modelData->getJointNum(); jntIdx++){
        if(jntIdx == m_jnt.getHeadJntNum() || jntIdx == m_jnt.getBackboneJntNum()){
            modelData->getJointTree().getJointNodePointer(jntIdx)->setCallBack(da_Npc_Ah_nodeCallBack);
        }
    }   
    mpMorf->getModel()->setUserArea((u32)this);
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), fopAcM_GetAngle_p(this), fopAcM_GetShapeAngle_p(this));
    return TRUE;
}

/* 00000BA4-00000D60       .text createInit__9daNpcAh_cFv */
cPhs_State daNpcAh_c::createInit() {
    getPrmArg0();
#if VERSION == VERSION_DEMO
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(&mCyl, current.pos, l_npc_dat.field_0x38, 150.0f);
#endif
    gravity = -9.0f;
    setAnmTbl(&l_npc_anm_wait);
    mEventCut.setActorInfo2(l_npc_staff_id[0], this);
#if VERSION == VERSION_DEMO
    setMtx();
#endif
    mLookAtMaxVel = 0;
    field_0x742 = 0;
    field_0x743 = 0;
    field_0x751 = 0;
    fopAcM_SetMtx(this, mpMorf->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -70.0f,0.0f,-70.0f,70.0f,200.0f,70.0f);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e]=0xA7;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e]=0xA9;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_UNK1000000_e;;
    m_jnt.setParam( l_npc_dat.mMax_backbone_x, l_npc_dat.mMax_backbone_y,
                    l_npc_dat.mMin_backbone_x, l_npc_dat.mMin_backbone_y,
                    l_npc_dat.mMax_head_x, l_npc_dat.mMax_head_y,
                    l_npc_dat.mMin_head_x, l_npc_dat.mMin_head_y,
                    l_npc_dat.mMax_turn_step);
    field_0x74F = l_npc_dat.field_0x52;
    field_0x750 = l_npc_dat.field_0x53;
    field_0x720 = l_npc_dat.field_0x28;
    field_0x730 = l_npc_dat.field_0x30;
    mObjAcch.CrrPos(*dComIfG_Bgsp());
#if VERSION > VERSION_DEMO
    setMtx();
    mpMorf->getModel()->calc();
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    setCollision(&mCyl, current.pos, l_npc_dat.field_0x38, 150.0f);
#endif
    return cPhs_COMPLEATE_e;
}

/* 00000D60-00000DCC       .text _delete__9daNpcAh_cFv */
bool daNpcAh_c::_delete() {
    getPrmArg0();
    if(field_0x747 != 0){
        dComIfG_resDeleteDemo(&mPhs, l_arcname_tbl[0]);
    }
#if VERSION > VERSION_DEMO
    if(heap != NULL && mpMorf != NULL){
#else
    if(mpMorf != NULL){
#endif
        mpMorf->stopZelAnime();
    }
    return true;
}

/* 00000DCC-00000EDC       .text _draw__9daNpcAh_cFv */
bool daNpcAh_c::_draw() {
    J3DModel* morfModel = mpMorf->getModel();
    J3DModelData* morfModelData = morfModel->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(morfModel, &tevStr);
    mBtpAnm.entry(morfModelData, mBtpFrame);
    mpMorf->updateDL();
    mBtpAnm.remove(morfModelData);

    cXyz shadowPos;
    shadowPos.set(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    mShadowId = dComIfGd_setShadow(mShadowId, 
                                     1, 
                                     mpMorf->getModel(), 
                                     &shadowPos, 800.0f, 20.0f, 
                                     current.pos.y, 
                                     mObjAcch.GetGroundH(),
                                     mObjAcch.m_gnd, 
                                     &tevStr);
    dSnap_RegistFig(DSNAP_TYPE_UNK7F, this, 1.0f, 1.0f, 1.0f);
    return true;
}

typedef BOOL(daNpcAh_c::*ExecuteInit_t)();
static ExecuteInit_t l_execute_init[] = {
    &daNpcAh_c::executeWaitInit,
    &daNpcAh_c::executeTalkInit
};


typedef void(daNpcAh_c::*MoveProc_t)();
static MoveProc_t moveProc[]={
    &daNpcAh_c::executeWait,
    &daNpcAh_c::executeTalk,
};

/* 00000EDC-00001134       .text _execute__9daNpcAh_cFv */
bool daNpcAh_c::_execute() {
    switch (getPrmArg0()) {
        case 2:
            if(fopAcM_isSwitch(this, 0x6c)) fopAcM_delete(this);
            break;
        case 5:
            if(fopAcM_isSwitch(this, 0x10)) fopAcM_delete(this);
            break;
        case 9:
            if(fopAcM_isSwitch(this, getSwBit() & 0xff)) fopAcM_delete(this);
            break;
    }
    chkAttention();
    checkOrder();
    if(!dComIfGp_event_runCheck() || eventInfo.checkCommandTalk()){
        (this->*moveProc[mMoveState])();
    }
    else eventMove();

    eventOrder();
    playTexPatternAnm();
    playAnm();
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    setCollision(&mCyl, current.pos, l_npc_dat.field_0x38, 150.0f);

    cXyz attnInfoPos;
    attnInfoPos.set(l_npc_dat.field_0x18, l_npc_dat.field_0x1C, l_npc_dat.field_0x20);
    cMtx_YrotS(mDoMtx_stack_c::get(), current.angle.y);
    cMtx_multVec(mDoMtx_stack_c::get(), &attnInfoPos, &attnInfoPos);
    attnInfoPos += current.pos;
    attention_info.position.set(attnInfoPos);
    eyePos.set(current.pos.x, current.pos.y + l_npc_dat.field_0x24, current.pos.z);
    lookBack();
    setMtx();
    return false;
}

/* 00001134-000011A4       .text executeCommon__9daNpcAh_cFv */
u8 daNpcAh_c::executeCommon() {
    if(field_0x743 != 0) field_0x744 = 1;
    else field_0x744 = 0;

    if(field_0x742 == 1 && mMoveState != 1) executeSetMode(1);
    return field_0x742;
}


/* 000011A4-000011F8       .text executeSetMode__9daNpcAh_cFUc */
void daNpcAh_c::executeSetMode(u8 proc) {
    field_0x718 = 0.0f;
    mMoveState = (this->*l_execute_init[proc])();
}

/* 000011F8-00001278       .text executeWaitInit__9daNpcAh_cFv */
BOOL daNpcAh_c::executeWaitInit() {
    speedF = 0.0f;
    setAnmTbl(&l_npc_anm_wait);
    m_jnt.setParam(l_npc_dat.mMax_backbone_x, l_npc_dat.mMax_backbone_y, 
                   l_npc_dat.mMin_backbone_x, l_npc_dat.mMin_backbone_y,
                   l_npc_dat.mMax_head_x, l_npc_dat.mMax_head_y,
                   l_npc_dat.mMin_head_x, l_npc_dat.mMin_head_y, 
                   l_npc_dat.mMax_turn_step);
    return FALSE;
}

/* 00001278-00001298       .text executeWait__9daNpcAh_cFv */
void daNpcAh_c::executeWait() {
    executeCommon();
}

/* 00001298-000012A0       .text executeTalkInit__9daNpcAh_cFv */
BOOL daNpcAh_c::executeTalkInit() {
    return TRUE;
}

/* 000012A0-00001318       .text executeTalk__9daNpcAh_cFv */
void daNpcAh_c::executeTalk() {
    executeCommon();
    if(talk2(1) == fopMsgStts_BOX_CLOSED_e){
        field_0x742 = 0;
        executeSetMode(0);
        dComIfGp_event_reset();
    }
    else{
        setAnmFromMsgTag();
    }
}

/* 00001318-0000136C       .text checkOrder__9daNpcAh_cFv */
void daNpcAh_c::checkOrder() {
    if(!eventInfo.checkCommandDemoAccrpt() && eventInfo.checkCommandTalk() && (field_0x744 == 2 || field_0x744 == 1)){
        field_0x742 = 1;
        executeSetMode(1);
    }
}

/* 0000136C-000013B8       .text eventOrder__9daNpcAh_cFv */
void daNpcAh_c::eventOrder() {
    if((field_0x744 == 2 || field_0x744 == 1) && (eventInfo.onCondition(dEvtCnd_CANTALK_e), field_0x744 == 2)){
        fopAcM_orderSpeakEvent(this);
    }
}

/* 000013B8-0000142C       .text eventMove__9daNpcAh_cFv */
void daNpcAh_c::eventMove() {
    if(!chkEndEvent()){
        bool attnFlag = mEventCut.getAttnFlag();
        if(mEventCut.cutProc()){
            if(!mEventCut.getAttnFlag()){
                mEventCut.setAttnFlag(attnFlag);
            }
        }
        else{
            privateCut();
            setAnmFromMsgTag();
        }
    }
}

/* 0000142C-00001554       .text privateCut__9daNpcAh_cFv */
void daNpcAh_c::privateCut() {
    static char* cut_name_tbl[] = {
        "MES_SET",
        "GET_ITEM",
    };
    int staff_idx = dComIfGp_evmng_getMyStaffId(*l_npc_staff_id);
    if(staff_idx != -1){
        mActIdx = dComIfGp_evmng_getMyActIdx(staff_idx, cut_name_tbl, 2, 1, 0);
        if(mActIdx == -1){
            dComIfGp_evmng_cutEnd(staff_idx);
        }
        else{
            if(dComIfGp_evmng_getIsAddvance(staff_idx)){
                switch (mActIdx) {
                    case 0:
                        eventMesSetInit(staff_idx);
                        break;
                    case 1:
                        eventGetItemInit();
                        break;
                }
            }
            bool end;
            switch(mActIdx){
                case 0:
                    end = eventMesSet();
                    break;
                default:
                    end = TRUE;
                    break;
            }
            if(end){
                dComIfGp_evmng_cutEnd(staff_idx);
            }
        }
    }
}

/* 00001554-0000162C       .text eventMesSetInit__9daNpcAh_cFi */
void daNpcAh_c::eventMesSetInit(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    if(pData != NULL){
        mpMsgNo = NULL;
        int msg = *pData;
        switch(msg){
            case 1:
                break;
            case 0:
                msg = getMsg();
                setMessage(msg);
                break;
            default:
                setMessage(msg);
        }
        if(mpMsgNo != NULL){
            setMessage(*mpMsgNo);
        }
    }else{
        mpMsgNo++;
        setMessage(*mpMsgNo);
    }
}

/* 0000162C-000016C0       .text eventMesSet__9daNpcAh_cFv */
bool daNpcAh_c::eventMesSet() {
    u16 talkVal = talk2(0);
    if(talkVal == fopMsgStts_BOX_CLOSED_e){
        if((field_0x748 & 1) != 0){
            field_0x748 &= ~0x1;
            mItemNo = 7;
            field_0x744 = 3;
            
        }else{
            if((field_0x748 & 2) != 0){
                field_0x748 &= ~0x2;
                mItemNo = 5;
                field_0x744 = 3;
            }
        }
    }
    return talkVal == fopMsgStts_BOX_CLOSED_e;
}

/* 000016C0-00001718       .text eventGetItemInit__9daNpcAh_cFv */
void daNpcAh_c::eventGetItemInit() {
    fpc_ProcID procItem = fopAcM_createItemForPresentDemo(&current.pos, mItemNo);
    if(procItem != fpcM_ERROR_PROCESS_ID_e){
        dComIfGp_event_setItemPartnerId(procItem);
    }
}

/* 00001718-00001860       .text talk2__9daNpcAh_cFi */
u16 daNpcAh_c::talk2(int i_param) {
    u16 ret = 0xff;
    if(mCurrMsgBsPcId == fpcM_ERROR_PROCESS_ID_e){
        if(i_param == 1) mCurrMsgNo = getMsg();
        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo, this);
        mpCurrMsg = NULL;
        field_0x734 = -1;
    }
    else{
        if(mpCurrMsg != NULL) {
            ret = mpCurrMsg->mStatus;
            switch(ret){
                case fopMsgStts_MSG_DISPLAYED_e:
                    mpCurrMsg->mStatus = next_msgStatus(&mCurrMsgNo);
                    if(mpCurrMsg->mStatus == fopMsgStts_MSG_CONTINUES_e) fopMsgM_messageSet(mCurrMsgNo);
                    break;
                case fopMsgStts_MSG_TYPING_e:
                    if(field_0x734 == fopMsgStts_MSG_CONTINUES_e) chkMsg();
                    break;
                case fopMsgStts_BOX_CLOSED_e:
                    mpCurrMsg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                    mCurrMsgBsPcId = -1;
                    break;
            }
            field_0x734 = ret;
            anmAtr(ret);
        }
        else{
            mpCurrMsg = fopMsgM_SearchByID(mCurrMsgBsPcId);
        }
    }
    return ret;
}

/* 00001860-000018B0       .text next_msgStatus__9daNpcAh_cFPUl */
u16 daNpcAh_c::next_msgStatus(u32* pMsgNo) {
    u16 ret = fopMsgStts_MSG_CONTINUES_e;
    if(mpMsgNo != NULL){
        mpMsgNo++;
        switch (*mpMsgNo) {
            case 0:
                mpMsgNo = 0;
                ret = fopNpc_npc_c::next_msgStatus(pMsgNo);
                break;
            default:
                *pMsgNo = *mpMsgNo;
                break;
                
        }
    }
    else {
        ret = fopNpc_npc_c::next_msgStatus(pMsgNo);;
    }
    return ret;
}

/* 000018B0-00001958       .text getMsg__9daNpcAh_cFv */
u32 daNpcAh_c::getMsg() {
    u32 ret = 0;
    mpMsgNo = 0;
    if(!g_dComIfG_gameInfo.play.getEvent()->chkPhoto()){
        if(!dComIfGp_event_chkTalkXY()) {
            u8 index = getPrmArg0();
            mpMsgNo = l_msg_ah_tbl[index];
        }
    }
    if(mpMsgNo != 0) ret = *mpMsgNo;
    return ret;
}

/* 00001958-0000195C       .text chkMsg__9daNpcAh_cFv */
void daNpcAh_c::chkMsg() {
    return;
}

/* 0000195C-00001964       .text setMessage__9daNpcAh_cFUl */
void daNpcAh_c::setMessage(unsigned long msgNo) {
    mCurrMsgNo = msgNo;
}

/* 00001964-000019D0       .text setAnmFromMsgTag__9daNpcAh_cFv */
void daNpcAh_c::setAnmFromMsgTag() {
    switch(dComIfGp_getMesgAnimeAttrInfo()){
        case 0:
            setAnmTbl(&l_npc_anm_wait);
            break;
        case 1:
            setAnmTbl(&l_npc_anm_wait2);
            break;
    }
    dComIfGp_setMesgAnimeAttrInfo(0xff);
}

/* 000019D0-00001A08       .text getPrmArg0__9daNpcAh_cFv */
u8 daNpcAh_c::getPrmArg0() {
    u8 ret = daObj::PrmAbstract(this, PRM_SWSAVE_S, PRM_SWSAVE_W);
    if(ret >= 0xa) ret = 0;
    return ret;
}

/* 00001A08-00001A34       .text getSwBit__9daNpcAh_cFv */
u8 daNpcAh_c::getSwBit() {
    return daObj::PrmAbstract(this, PRM_SWSAVE2_S, PRM_SWSAVE2_W);
}

/* 00001A34-00001ABC       .text setMtx__9daNpcAh_cFv */
void daNpcAh_c::setMtx() {
    J3DModel* mcaMorf = mpMorf->getModel();
    mcaMorf->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    cMtx_YrotM(mDoMtx_stack_c::get(), current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00001ABC-00001DBC       .text chkAttention__9daNpcAh_cFv */
void daNpcAh_c::chkAttention() {
    field_0x751 = 0;
    f32 distXZ;
    s16 angle;
    if(mEventCut.getAttnFlag()){
        mEyePos.set(mEventCut.getAttnPos());
        field_0x74E = 1;
        if(field_0x74F != 0){
            mHeadOnlyFollow = false;
            m_jnt.setTrn();
        }
        else{
            mHeadOnlyFollow = true;
        }
        if(field_0x743 == 0){
            field_0x743 = 1;
        }
    }
    else{
        fopAc_ac_c* player = dComIfGp_getPlayer(0);
        f32 temp720 = field_0x720;
        s32 temp730 = field_0x730;
        dNpc_calc_DisXZ_AngY(current.pos, player->current.pos, &distXZ, &angle);
        if(field_0x743 != 0){
            temp720 += 40.0f;
            temp730 += 0x71C;
        }
        angle -= shape_angle.y;
        if(temp720 > distXZ && temp730 > abs(angle))
        {
            mEyePos.set(dNpc_playerEyePos(l_npc_dat.field_0x14));
            field_0x74E = 1;
            if(field_0x74F != 0) mHeadOnlyFollow = false;
            else mHeadOnlyFollow = true;
            if(field_0x750 == 0){
                mTargetYRot = field_0x732;
                mHeadOnlyFollow = false;
                field_0x74E = 2;
                m_jnt.setTrn();
            }
            if(field_0x743 == 0) field_0x743 = 1;
        }
        else{
            if(field_0x743 == 1){
                field_0x743 = 0;
                field_0x72E = l_npc_dat.field_0x50;
            }
            if(l_npc_dat.field_0x2C > distXZ){
                mEyePos.set(dNpc_playerEyePos(l_npc_dat.field_0x14));
                field_0x74E = 1;
                if(field_0x74F != 0) mHeadOnlyFollow = false;
                else mHeadOnlyFollow = true;
                if(field_0x750 == 0){
                    mTargetYRot = field_0x732;
                    mHeadOnlyFollow = false;
                    field_0x74E = 2;
                    m_jnt.setTrn();
                }
                field_0x751 = 1;
            }
            else{
                field_0x74E = 0;
                if(!mPathRun.isPath()){
                    if(field_0x72E != 0){
                        field_0x72E--;
                    }
                    else{
                        mTargetYRot = field_0x732;
                        mHeadOnlyFollow = false;
                        field_0x74E = 2;
                        m_jnt.setTrn();
                    }
                }
            }
        }
    }
    mTargetAngle = l_npc_dat.field_0x32;
}

/* 00001DBC-00001F08       .text lookBack__9daNpcAh_cFv */
void daNpcAh_c::lookBack() {
    s16 target = mTargetAngle;
    s16 desiredYRot = current.angle.y;
    cXyz* dstPos = NULL;
    cXyz newDes;
    cXyz eyePosFollow = eyePos;
    bool headOnlyFollow = mHeadOnlyFollow;

    switch(field_0x74E){
        case 0x1:
            newDes.set(mEyePos);
            dstPos = &newDes;
            break;
        case 0x2:
            desiredYRot = mTargetYRot;
            break;
        case 0:
        default:
            break;
    }

    if(field_0x742 != 0 && field_0x74F != 0){
        headOnlyFollow = false;
        m_jnt.setTrn();
    }
    if(m_jnt.trnChk() != false) {
        if(mEventCut.getTurnSpeed() != 0) target = mEventCut.getTurnSpeed();
        cLib_addCalcAngleS2(&mLookAtMaxVel, target, 4, 0x800);
    }
    else{
        mLookAtMaxVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos, eyePosFollow, desiredYRot, mLookAtMaxVel, headOnlyFollow);
    shape_angle = current.angle;
}

/* 00001F08-00002014       .text initTexPatternAnm__9daNpcAh_cFb */
BOOL daNpcAh_c::initTexPatternAnm(bool modify) {
    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_btp_ix_tbl[0]);
    JUT_ASSERT(DEMO_SELECT(0x65C, 0x66B), m_head_tex_pattern != NULL);
    BOOL ret = mBtpAnm.init(modelData, m_head_tex_pattern, 1, 2, 1.0, 0, -1, modify, FALSE);
    if(ret == FALSE)
        return FALSE;
    else{
        mBtpFrame = 0;
        mTimer = 0;
        return TRUE;
    }
}

/* 00002014-00002080       .text playTexPatternAnm__9daNpcAh_cFv */
void daNpcAh_c::playTexPatternAnm() {
    if(!cLib_calcTimer(&mTimer)){
        if(mBtpFrame >= m_head_tex_pattern->getFrameMax()){
            mBtpFrame -= m_head_tex_pattern->getFrameMax();
            mTimer = 0x78;
        }
        else{
            mBtpFrame++;
        }
    }
}

/* 00002080-00002148       .text playAnm__9daNpcAh_cFv */
void daNpcAh_c::playAnm() {
    field_0x74A &= ~1;
    if(mpMorf->play(NULL, 0, 0)){
        if(mpAnmDat != NULL){
            if(field_0x74B> 0){
                field_0x74B += -1;
                if(field_0x74B == 0){
                    mpAnmDat++;
                    if(setAnmTbl(mpAnmDat)){
                        field_0x74A |= 1; 
                    }
                }
                else{
                    setAnm(mpAnmDat->mBckIdx, J3DFrameCtrl::EMode_NONE, 0.0f);
                }
            }
        }
    }
}

/* 00002148-00002218       .text setAnm__9daNpcAh_cFUcif */
void daNpcAh_c::setAnm(unsigned char bck_ix, int loopMode, float morf) {
    f32 tempMorf = field_0x71C;
    if(tempMorf>=0.0f){
        morf = tempMorf;
        field_0x71C = -1;
    }
    mpMorf->setAnm( (J3DAnmTransform*)dComIfG_getObjectIDRes(l_arcname_tbl[0], l_bck_ix_tbl[bck_ix]),
                    loopMode, morf, 1.0, 0.0, -1.0, NULL);
    mBckIdx = bck_ix;
}

/* 00002218-000022B8       .text setAnmTbl__9daNpcAh_cFP9sAhAnmDat */
bool daNpcAh_c::setAnmTbl(sAhAnmDat* i_anmDat) {
    if(i_anmDat->mBckIdx == 0xFF){
        mpAnmDat = NULL;
        return TRUE;
    }else{
        mpAnmDat = i_anmDat;
        field_0x74B = mpAnmDat->field_0x02;
        int loopMode = J3DFrameCtrl::EMode_LOOP;
        if(field_0x74B > 0) loopMode = J3DFrameCtrl::EMode_NONE;
        if(mBckIdx != mpAnmDat->mBckIdx || loopMode == J3DFrameCtrl::EMode_NONE){
            setAnm(mpAnmDat->mBckIdx, loopMode, mpAnmDat->mMorf);
        }
        return FALSE;
    }
}

/* 000022B8-00002330       .text setCollision__9daNpcAh_cFP8dCcD_Cyl4cXyzff */
void daNpcAh_c::setCollision(dCcD_Cyl* cyl, cXyz center, float radius, float height) {
    cyl->SetC(center);
    cyl->SetR(radius);
    cyl->SetH(height);
    dComIfG_Ccsp()->Set(cyl);
}

/* 00002330-00002338       .text chkEndEvent__9daNpcAh_cFv */
BOOL daNpcAh_c::chkEndEvent() {
    return FALSE;
}

/* 00002338-00002358       .text daNpc_AhCreate__FPv */
static cPhs_State daNpc_AhCreate(void* i_this) {
    return ((daNpcAh_c*)i_this)->_create();
}

/* 00002358-0000237C       .text daNpc_AhDelete__FPv */
static BOOL daNpc_AhDelete(void* i_this) {
    return ((daNpcAh_c*)i_this)->_delete();
}

/* 0000237C-000023A0       .text daNpc_AhExecute__FPv */
static BOOL daNpc_AhExecute(void* i_this) {
    return ((daNpcAh_c*)i_this)->_execute();
}

/* 000023A0-000023C4       .text daNpc_AhDraw__FPv */
static BOOL daNpc_AhDraw(void* i_this) {
    return ((daNpcAh_c*)i_this)->_draw();
}

/* 000023C4-000023CC       .text daNpc_AhIsDelete__FPv */
static BOOL daNpc_AhIsDelete(void*) {
    return TRUE;
}

static actor_method_class daNpc_AhMethodTable = {
    (process_method_func)daNpc_AhCreate,
    (process_method_func)daNpc_AhDelete,
    (process_method_func)daNpc_AhExecute,
    (process_method_func)daNpc_AhIsDelete,
    (process_method_func)daNpc_AhDraw,
};

actor_process_profile_definition g_profile_NPC_AH = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ fpcNm_NPC_AH_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpcAh_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_AH,
    /* Actor SubMtd */ &daNpc_AhMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
