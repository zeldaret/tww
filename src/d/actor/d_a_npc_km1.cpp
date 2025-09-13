/**
 * d_a_npc_km1.cpp
 * NPC - Mila (rich)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_km1.h"
#include "d/d_com_inf_game.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_km.h"

class daNpc_Km1_HIO_c : public JORReflexible{
public:
    struct hio_prm_c {
        s16 field_0;
        s16 field_2;
        s16 field_4;
        s16 field_6;
        s16 field_8;
        s16 field_A;
        s16 field_C;
        s16 field_E;
        s16 field_10;
        s16 field_12;
        f32 mAttentionArrowYOffset;
        f32 field_18;
    };  // Size: 0x1C

    daNpc_Km1_HIO_c();
    virtual ~daNpc_Km1_HIO_c() {};

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ s8 field_0x5;
    /* 0x06 */ s8 field_0x6;
    /* 0x07 */ s8 field_0x7;
    /* 0x08 */ int field_0x8;
    /* 0x0C */ hio_prm_c mPrmTbl;
};

static daNpc_Km1_HIO_c l_HIO;

/* 000000EC-00000144       .text __ct__15daNpc_Km1_HIO_cFv */
daNpc_Km1_HIO_c::daNpc_Km1_HIO_c() {
    static hio_prm_c a_prm_tbl = {
        0x1FFE,
        0x38E0,
        0xE002,
        0xC720,
        0x0000,
        0x0000,
        0x0000,
        0x0000,
        0x0800,
        0x0800,
        150.0f,
        0.0f
    };
    memcpy(&mPrmTbl,&a_prm_tbl,sizeof(hio_prm_c));
    mNo = -1;
    field_0x8 = -1;
}

/* 00000144-000002F0       .text nodeCallBack_Km__FP7J3DNodei */
static BOOL nodeCallBack_Km(J3DNode* i_node, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_Km1_c* km1Actor = (daNpc_Km1_c *)(model->getUserArea());
        if (km1Actor) {
            static cXyz a_att_pos_offst(0.0f,0.0f,0.0f);
            static cXyz a_eye_pos_offst(20.0f,20.0f,0.0f);
            u16 jointIdx = ((J3DJoint*)(i_node))->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jointIdx));
            if(jointIdx == km1Actor->getHeadJntNum()){
                MTXMultVec(mDoMtx_stack_c::get(),&a_att_pos_offst,km1Actor->getAttPos());
                mDoMtx_stack_c::XrotM(km1Actor->getHead_y());
                mDoMtx_stack_c::ZrotM(km1Actor->getHead_x()); 
                MTXMultVec(mDoMtx_stack_c::get(),&a_eye_pos_offst,km1Actor->getEyePos());
            }else if(jointIdx == km1Actor->getBackboneJntNum()){
                mDoMtx_stack_c::XrotM(km1Actor->getBackbone_y());
                mDoMtx_stack_c::ZrotM(km1Actor->getBackbone_x());  
            }
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jointIdx, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
 }


extern dCcD_SrcCyl dNpc_cyl_src;
/* 0000032C-0000043C       .text createInit__11daNpc_Km1_cFv */
bool daNpc_Km1_c::createInit() {
    mEventCut.setActorInfo2("Km1", this);
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xAB;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    gravity = -4.0f;
    field_0x798 = current.pos;
    set_action(&daNpc_Km1_c::wait_action1,NULL);
    shape_angle = current.angle;
    mStts.Init(0xFF,0xFF,this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    field_0x7BC = 1;
    setMtx();
    return true;

}

/* 0000043C-0000054C       .text setMtx__11daNpc_Km1_cFv */
void daNpc_Km1_c::setMtx() {
    if (field_0x7C7 == 0) {
        playTexPatternAnm();
        field_0x7B4 = mpMorf->play(&eyePos,0,0);
        if (mpMorf->getFrame() < field_0x7A4) {
            field_0x7B4 = 1;
        }
        field_0x7A4 = mpMorf->getFrame();
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    setAttention();
}


/* 0000054C-00000654       .text anmResID__11daNpc_Km1_cFiPiPi */
bool daNpc_Km1_c::anmResID(int i_num, int* o_bck_num, int* o_bas_num) {
    static const int a_anm_idx_tbl[1][2] = {KM_BCK_KM_WAIT01,KM_BAS_KM_WAIT01};
    JUT_ASSERT(0x11A,0 <= i_num && i_num < ANM_END);
    JUT_ASSERT(0x11B,o_bck_num && o_bas_num);
    *o_bck_num = a_anm_idx_tbl[i_num][0];
    *o_bas_num = a_anm_idx_tbl[i_num][1];
    return true;
}



/* 00000654-000006F0       .text BtpNum2ResID__11daNpc_Km1_cFiPi */
void daNpc_Km1_c::BtpNum2ResID(int i_num, int* o_btp_num){
    static const int a_btp_arc_ix_tbl[1] = {KM_BTP_MABA};
    JUT_ASSERT(0x130,0 <= i_num && i_num < TEXPATTERN_END);
    *o_btp_num = a_btp_arc_ix_tbl[i_num];
}

/* 000006F0-00000734       .text setAnm_tex__11daNpc_Km1_cFSc */
void daNpc_Km1_c::setAnm_tex(signed char i_param_1) {
    if(i_param_1 >= 0 && i_param_1 != field_0x7CD){
        field_0x7CD = i_param_1;
        initTexPatternAnm(true);
    }
}

/* 00000734-00000850       .text init_btp__11daNpc_Km1_cFbi */
bool daNpc_Km1_c::init_btp(bool param_1, int param_2) {
    int btp_num;
    int iVar3;
    J3DModelData *pJVar4;

    pJVar4 = mpMorf->getModel()->getModelData();
    if (param_2 >= 0) {
        BtpNum2ResID(param_2,&btp_num);
        J3DAnmTexPattern* pVVar1 = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Km",btp_num);
        m_head_tex_pattern = pVVar1;
        JUT_ASSERT(0x151,m_head_tex_pattern != NULL);
        iVar3 = mBtpAnm.init(pJVar4,m_head_tex_pattern,TRUE,J3DFrameCtrl::EMode_LOOP,1.0f,0,-1,param_1,FALSE);

        if (iVar3 == 0) {
            return false;
        }
        mBtpFrame = 0;
        field_0x6F2 = 0;
    }
    return true;
}

/* 00000850-00000894       .text initTexPatternAnm__11daNpc_Km1_cFb */
bool daNpc_Km1_c::initTexPatternAnm(bool param_1) {
    
    bool var_31 = false;
    if(init_btp(param_1,field_0x7CD)){
        var_31 = true;
    }
    return var_31;

}

/* 00000894-00000958       .text playTexPatternAnm__11daNpc_Km1_cFv */
void daNpc_Km1_c::playTexPatternAnm() {
    //TODO: Rewrite this conditional logic
    bool var_r4 = true;
    if(field_0x7CD == 0){
        var_r4 = !cLib_calcTimer(&field_0x6F2);
    }
    if(!var_r4){
        return;
    }

    if((mBtpFrame += 1) < m_head_tex_pattern->getFrameMax()){
        return;
    }

    if(field_0x7CD){
        mBtpFrame = m_head_tex_pattern->getFrameMax();
        return;

    }else{
        mBtpFrame = 0;
        field_0x6F2 = cM_rndF(60.0) + 30.0f;
    }
    return;
}

/* 00000958-00000A24       .text setAnm_anm__11daNpc_Km1_cFPQ211daNpc_Km1_c9anm_prm_c */
s32 daNpc_Km1_c::setAnm_anm(daNpc_Km1_c::anm_prm_c* i_anm_ptr) {
    u32 uVar2 = 0;
    int local_18;
    int local_14;
    

    if (i_anm_ptr->field_0x0 >= 0 && field_0x7CE != i_anm_ptr->field_0x0) {
        field_0x7CE = i_anm_ptr->field_0x0;
        if (mpMorf != NULL) {
            anmResID(field_0x7CE,&local_18,&local_14);
            if (local_18 >= 0) {
                dNpc_setAnmIDRes(mpMorf,i_anm_ptr->field_0xC,i_anm_ptr->field_0x4,i_anm_ptr->field_0x8,local_18,local_14,"Km");
            }
            uVar2 = 1;
        }
        field_0x7A4 = 0;
        field_0x7B5 = 0;
        field_0x7B4 = 0;
    }
    return uVar2;
}

/* 00000A24-00000A8C       .text setAnm__11daNpc_Km1_cFv */
void daNpc_Km1_c::setAnm() {
    static daNpc_Km1_c::anm_prm_c a_anm_prm_tbl[3] = {
        {-1,-1,0.0f,0.0f,-1},
        {ANM_WAIT,0,8.0f,1.0f,J3DFrameCtrl::EMode_LOOP},
        {-1,-1,0.0f,0.0f,-1}
    };
    setAnm_tex(a_anm_prm_tbl[field_0x7D0].field_0x1);
    setAnm_anm(&a_anm_prm_tbl[field_0x7D0]);
}

/* 00000A8C-00000A98       .text chngAnmTag__11daNpc_Km1_cFv */
void daNpc_Km1_c::chngAnmTag() {
    switch(field_0x7CC){
        case 0:
            break;
    }
}

/* 00000A98-00000AA4       .text ctrlAnmTag__11daNpc_Km1_cFv */
void daNpc_Km1_c::ctrlAnmTag() {
    switch(field_0x7CB){
        case 0:
            break;
    }
}

/* 00000AA4-00000AE4       .text chngAnmAtr__11daNpc_Km1_cFUc */
void daNpc_Km1_c::chngAnmAtr(unsigned char param_1) {
    if(param_1 < 1 && param_1 != field_0x7CB){
        field_0x7CB = param_1;
        setAnm_ATR(1);
    }
}

/* 00000AE4-00000AE8       .text ctrlAnmAtr__11daNpc_Km1_cFv */
void daNpc_Km1_c::ctrlAnmAtr() {
}

/* 00000AE8-00000B50       .text setAnm_ATR__11daNpc_Km1_cFi */
void daNpc_Km1_c::setAnm_ATR(int param_1) {
    static daNpc_Km1_c::anm_prm_c a_anm_prm_tbl[1] = {
        {ANM_WAIT,0x00,8.0f,1.0f,J3DFrameCtrl::EMode_LOOP}
    };
    if(param_1 != 0){
        setAnm_tex(a_anm_prm_tbl[field_0x7CB].field_0x1);
    }
    setAnm_anm((&a_anm_prm_tbl[field_0x7CB]));

}

/* 00000B50-00000C0C       .text anmAtr__11daNpc_Km1_cFUs */
void daNpc_Km1_c::anmAtr(unsigned short param_1) {
    if(param_1 == 6){
        if(field_0x7D6 == 0){
            field_0x7CC = 0xFF;
            chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
            field_0x7D6 += 1;
        }
        u8 uVar1 = dComIfGp_getMesgAnimeTagInfo();
        if(uVar1 != 0xFF && uVar1 != field_0x7CC){
            dComIfGp_clearMesgAnimeTagInfo();
            field_0x7CC = uVar1;
            chngAnmTag();
        }
    }else if(param_1 == 0xE){
        field_0x7D6 = 0;
    }
    ctrlAnmAtr();
    ctrlAnmTag();
}

/* 00000C0C-00000C64       .text setStt__11daNpc_Km1_cFSc */
void daNpc_Km1_c::setStt(signed char param_1) {
    s8 uVar1 = field_0x7D0;
    field_0x7D0 = param_1;
    switch((s8)field_0x7D0) {
        case 2:
            field_0x7D2 = 1;
            field_0x7CB = 0xFF;
            field_0x7D1 = uVar1;
            break;
        default:
        case 1:
            setAnm();
            break;
    }
}

/* 00000C64-00000C6C       .text next_msgStatus__11daNpc_Km1_cFPUl */
u16 daNpc_Km1_c::next_msgStatus(unsigned long*) {
    return fopMsgStts_MSG_ENDS_e;
}

/* 00000C6C-00000C74       .text getMsg__11daNpc_Km1_cFv */
u32 daNpc_Km1_c::getMsg() {
    return 0;
}

/* 00000C74-00000CC4       .text eventOrder__11daNpc_Km1_cFv */
void daNpc_Km1_c::eventOrder() {
    if (((field_0x7CF == 1) || (field_0x7CF == 2))){
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(field_0x7CF == 1){
            fopAcM_orderSpeakEvent(this);
        }
    }
}


/* 00000CC4-00000D04       .text checkOrder__11daNpc_Km1_cFv */
void daNpc_Km1_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()){
        return;
    }
    if(!eventInfo.checkCommandTalk()){
        return;
    }
    if(field_0x7CF != 1 && field_0x7CF != 2){
        return;
    }
    field_0x7CF = 0;
    field_0x7C5 = 1;
    return;
}

/* 00000D04-00000E94       .text lookBack__11daNpc_Km1_cFv */
void daNpc_Km1_c::lookBack() {
    cXyz vec1;
    cXyz vec2 = current.pos;
    vec2.y = eyePos.y;
    
    vec1.setall(0.0);

    cXyz* dstPos = NULL;
    s16 targetY = current.angle.y;
    bool headOnlyFollow = mHeadOnlyFollow;
    s8 state = field_0x7D2;

    switch(state){
        case 0:
            break;
        case 1:
            vec1 = dNpc_playerEyePos(-20.0);
            dstPos = &vec1;
            vec2 = current.pos;
            vec2.y = eyePos.y;
            break;
        case 2:
            vec1 = field_0x798;
            dstPos = &vec1;
            vec2 = current.pos;
            vec2.y = eyePos.y;
            break;
        case 3:
            targetY = field_0x7B2;
            break;
    }
    if(m_jnt.trnChk() != 0){
        cLib_addCalcAngleS2(&field_0x7B0,l_HIO.mPrmTbl.field_12,4,0x800);
    }else{
        field_0x7B0 = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y,dstPos,vec2,targetY,field_0x7B0,headOnlyFollow);
}

/* 00000E94-00000F14       .text chkAttention__11daNpc_Km1_cFv */
bool daNpc_Km1_c::chkAttention() {
    dAttention_c& attention = dComIfGp_getAttention();
    if(attention.LockonTruth() != 0){
        return this == attention.LockonTarget(0);
    }else{
        return this == attention.ActionTarget(0);
    }
}

/* 00000F14-00000F78       .text setAttention__11daNpc_Km1_cFv */
void daNpc_Km1_c::setAttention() {
    f32 f1 = current.pos.z; 
    f32 f2 = current.pos.y + l_HIO.mPrmTbl.mAttentionArrowYOffset;   

    attention_info.position.set(current.pos.x,f2,f1);
    if(!field_0x7BC && !field_0x7C0){return;}
    f2 = getEyePos()->z;
    f1 = getEyePos()->y;
    eyePos.set(getEyePos()->x,f1,f2);
    field_0x7BC = 0;
}

/* 00000F78-00000FA4       .text decideType__11daNpc_Km1_cFi */
bool daNpc_Km1_c::decideType(int param_1) {
    field_0x7D3 = 0xFF;
    switch(fopAcM_GetName(this)){
        case PROC_NPC_KM1:
            field_0x7D3 = 0;
            field_0x7D4 = 0;  
            break;
    }

    return true;
}

/* 00000FA4-0000102C       .text event_actionInit__11daNpc_Km1_cFi */
void daNpc_Km1_c::event_actionInit(int param_1) {
    int* puVar1 = dComIfGp_evmng_getMyIntegerP(param_1,"ActNo");
    dComIfGp_evmng_getMyIntegerP(param_1,"Timer");
    if(puVar1 != NULL){
        field_0x7CA = *puVar1;
    }
}

/* 0000102C-0000103C       .text event_action__11daNpc_Km1_cFv */
bool daNpc_Km1_c::event_action() {
    switch(field_0x7CA){
        case 0:
            break;
    }
    return true;
}

/* 0000103C-00001144       .text privateCut__11daNpc_Km1_cFv */
void daNpc_Km1_c::privateCut() {
    static char* cut_name_tbl[] = {"ACTION"};

    int staffIdx = dComIfGp_evmng_getMyStaffId("Km1",NULL,0);
    if(staffIdx != -1){
        int uVar1 = dComIfGp_evmng_getMyActIdx(staffIdx,cut_name_tbl,1,1,0);
        field_0x7C9 = uVar1;
        if(field_0x7C9 == -1){
            dComIfGp_evmng_cutEnd(staffIdx);
            return;
        }
        if(dComIfGp_evmng_getIsAddvance(staffIdx)){
            switch(field_0x7C9){
                case 0:
                    event_actionInit(staffIdx);
            }
        }
        bool bVar1;
        switch(field_0x7C9){
            case 0:
                bVar1 = event_action();
                break;
            default:
                bVar1 = 1;
                break;    
        }

        if(bVar1){
            dComIfGp_evmng_cutEnd(staffIdx);
        }

    }
}

/* 00001144-00001164       .text endEvent__11daNpc_Km1_cFv */
void daNpc_Km1_c::endEvent() {
    dComIfGp_event_onEventFlag(8);
    field_0x7CB = 0xFF;

}

/* 00001164-000011C4       .text event_proc__11daNpc_Km1_cFv */
void daNpc_Km1_c::event_proc() {
    if(!mEventCut.cutProc()){
        privateCut();
    }
    lookBack();
    shape_angle = current.angle;
}

/* 000011C4-00001270       .text set_action__11daNpc_Km1_cFM11daNpc_Km1_cFPCvPvPv_iPv */
bool daNpc_Km1_c::set_action(ActionFunc i_action, void* param_2) {
    if(field_0x6F4 != i_action){
        if(field_0x6F4 != 0){
            field_0x7D5 = 0xFF;
            (this->*field_0x6F4)(param_2);
        }
        field_0x6F4 = i_action;
        field_0x7D5 = 0;
        (this->*field_0x6F4)(param_2);
    }
    return true;
}

/* 00001270-00001368       .text wait01__11daNpc_Km1_cFv */
BOOL daNpc_Km1_c::wait01() {
    if(field_0x7C5 != 0){
        bool set_stt = true;
        field_0x7B7 = 0xFF;
        if(dComIfGp_event_chkTalkXY()){
            if(dComIfGp_evmng_ChkPresentEnd() != 0){
                field_0x7B7 = dComIfGp_event_getPreItemNo();
            }else{
                set_stt = false;
            }
        }
        if(set_stt){
            setStt(2);
        }
    }else{
        field_0x7CF = 2;
        if(field_0x7C4){
            field_0x7D2 = 1;
        }else{
            field_0x7D2 = 3;
            field_0x7B2 = field_0x76C.y;
            m_jnt.setTrn();
        }
    }
    return TRUE;
}

/* 00001368-000013F8       .text talk01__11daNpc_Km1_cFv */
BOOL daNpc_Km1_c::talk01() {
    talk(1);
    if(mpCurrMsg != NULL){
        switch(mpCurrMsg->mStatus){
            case 6:
            case 2:
                break;
            case 19:
                field_0x7B7 = 0xFF;
                setStt((field_0x7D1));
                field_0x7C8 = 0;
                field_0x7C5 = 0;
                endEvent();
                break;
        }
    }
    return TRUE;
}

/* 000013F8-000014AC       .text wait_action1__11daNpc_Km1_cFPv */
int daNpc_Km1_c::wait_action1(void*) {
    if(field_0x7D5 == 0){
        setStt(1);
        field_0x7D5 += 1;
    }else if( field_0x7D5 != -1){

        field_0x7C4 = chkAttention();
        switch(field_0x7D0){
            case 2:
                field_0x7C0 = talk01();
                break;
            case 1:
                field_0x7C0 = wait01();
                break;
            default:
                field_0x7C0 = 0;
                break;
        }
        lookBack();
    }
    return 1;
}

/* 000014AC-00001548       .text demo__11daNpc_Km1_cFv */
u8 daNpc_Km1_c::demo() {
    if(demoActorID == 0){
        if(field_0x7C7 != 0){
            field_0x7C7 = 0;
        }
    }else{
        field_0x7C7 = 1;
        dComIfGp_demo_getActor(demoActorID);
        dDemo_setDemoData(
            this,
            dDemo_actor_c::ENABLE_TRANS_e | dDemo_actor_c::ENABLE_ROTATE_e | dDemo_actor_c::ENABLE_ANM_e | dDemo_actor_c::ENABLE_ANM_FRAME_e,
            mpMorf,
            "Km"
        );
    }
    return field_0x7C7;
}

/* 00001548-000016AC       .text _draw__11daNpc_Km1_cFv */
BOOL daNpc_Km1_c::_draw() {
    J3DModel *model = mpMorf->getModel();
    J3DModelData *model_data = model->getModelData();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR,&current.pos,&tevStr);
    g_env_light.setLightTevColorType(model,&tevStr);
    mBtpAnm.entry(model_data,mBtpFrame);
    mpMorf->entryDL();
    mBtpAnm.remove(model_data);
    dNpc_setShadowModel(field_0x6D4,model_data,model);

    cXyz pos(current.pos.x,current.pos.y+150.0f,current.pos.z);
    mShadowId = dComIfGd_setRealShadow(mShadowId,1,field_0x6D4,&pos,800.0f,current.pos.y-mObjAcch.GetGroundH(),NULL);
    if(mShadowId == 0){
        dComIfGd_setSimpleShadow(
            &current.pos,
            mObjAcch.GetGroundH(),
            40.0f,
            dComIfG_Bgsp()->GetTriPla(mObjAcch.m_gnd)->GetNP()
        );
    }
    dSnap_RegistFig(DSNAP_TYPE_KM1,this,1.0f,1.0f,1.0f);

    // Color literals for debug drawing. Unused in non-debug builds.
    (GXColor){0xFF,0x00, 0x00, 0x80};
    (GXColor){0x00,0x00, 0xFF, 0x80};

    return true;
}

/* 000016AC-00001808       .text _execute__11daNpc_Km1_cFv */
BOOL daNpc_Km1_c::_execute() {
    if(field_0x7B8 == 0){
        field_0x774 = current.pos;
        field_0x76C = current.angle;
        field_0x7B8 = 1;
    }
    m_jnt.setParam(l_HIO.mPrmTbl.field_8,
    l_HIO.mPrmTbl.field_A,l_HIO.mPrmTbl.field_C,
    l_HIO.mPrmTbl.field_E,l_HIO.mPrmTbl.field_0,
    l_HIO.mPrmTbl.field_2,l_HIO.mPrmTbl.field_4,
    l_HIO.mPrmTbl.field_6,l_HIO.mPrmTbl.field_10);
    checkOrder();
    if(demo() == 0){
        if (dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()){
            event_proc();  
        }else{
            (this->*field_0x6F4)(NULL);
            shape_angle = current.angle;
        }
    }
    eventOrder();
    if(field_0x7C7 == 0){
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    setMtx();
    setCollision(60.0f,150.0f);
    return true;
}

/* 00001808-0000188C       .text _delete__11daNpc_Km1_cFv */
BOOL daNpc_Km1_c::_delete() {
    fopAcM_GetID(this);
    dComIfG_resDeleteDemo(&field_0x6C4,"Km");

    if(mpMorf != NULL){
        mpMorf->stopZelAnime();
    }
    if(l_HIO.field_0x8 >= 0){
        l_HIO.field_0x8 += -1;
        if(l_HIO.field_0x8 < 0){
            mDoHIO_deleteChild(l_HIO.mNo);
        }
    }
    return true;
    
}

/* 0000188C-000018AC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* actor) {
    return ((daNpc_Km1_c*)actor)->CreateHeap();
}

/* 000018AC-00001A1C       .text _create__11daNpc_Km1_cFv */
cPhs_State daNpc_Km1_c::_create() {
    static int a_heap_size_tbl[] = {
        0x272E0
    };

#if VERSION > VERSION_DEMO
    fopAcM_SetupActor(this, daNpc_Km1_c);
#endif

    if (!decideType(fopAcM_GetParam(this) & 0xFF )) {
        return cPhs_ERROR_e;
    }

    cPhs_State resLoadResult = dComIfG_resLoad(&field_0x6C4,"Km");

    
    if(resLoadResult != cPhs_COMPLEATE_e){
        return resLoadResult;
    }
    if(l_HIO.field_0x8 < 0){
        l_HIO.mNo = mDoHIO_createChild("金持ちム−ル",&l_HIO);
    }
    l_HIO.field_0x8 += 1;

#if VERSION == VERSION_DEMO
    fopAcM_SetupActor(this, daNpc_Km1_c);
#endif

    if(fopAcM_entrySolidHeap(this,CheckCreateHeap,a_heap_size_tbl[field_0x7D3])){
        fopAcM_SetMtx(this,mpMorf->mpModel->getBaseTRMtx());
        fopAcM_setCullSizeBox(this,-60.0f,-20.0f,-80.0f,60.0f,160.0f,60.0f);
    }else{
        return cPhs_ERROR_e;
    }
    if (createInit() == 0) {
        resLoadResult = cPhs_ERROR_e;
    }
    return resLoadResult; 
    
}

/* 00001E4C-00002158       .text CreateHeap__11daNpc_Km1_cFv */
BOOL daNpc_Km1_c::CreateHeap() {
    static u8 a_tex_pattern_num_tbl[1] = {TEXPATTERN_MABA};
    J3DModelData *a_mdl_data;

 
    a_mdl_data = (J3DModelData*)dComIfG_getObjectIDRes("Km",KM_BDL_KM);
    JUT_ASSERT(DEMO_SELECT(1316, 1325) ,a_mdl_data != NULL);
    mpMorf = new mDoExt_McaMorf(
        a_mdl_data,
        NULL, NULL,
        (J3DAnmTransform*)dComIfG_getObjectIDRes("Km", KM_BCK_KM_WAIT01),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1, NULL,
        0x80000, 0x11020002
    );
    if (mpMorf){
        if(mpMorf->getModel()) {
            m_head_jnt_num = a_mdl_data->getJointName()->getIndex("head");
            JUT_ASSERT(DEMO_SELECT(1335, 1344), m_head_jnt_num >= 0);
            m_backbone_jnt_num = a_mdl_data->getJointName()->getIndex("backbone");
            JUT_ASSERT(DEMO_SELECT(1337, 1346), m_backbone_jnt_num >= 0);
            field_0x7CD = a_tex_pattern_num_tbl[field_0x7D3];
            if (initTexPatternAnm(false) != 0) {
                field_0x6D4 = mDoExt_J3DModel__create(a_mdl_data,0x20000,0x11020203);
                if (field_0x6D4 != 0) {
                    for (u16 i = 0; i < a_mdl_data->getJointNum(); i += 1) {
                        if ((i == m_head_jnt_num) || (i == m_backbone_jnt_num)) {
                            mpMorf->mpModel->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Km);
                        }
                    }
                    mpMorf->getModel()->setUserArea((u32)this);
                    mAcchCir.SetWall(30.0f,60.0f);
                    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
                    return TRUE;
                }
            }
        }
        mpMorf = NULL;
    }
    return FALSE;
}

/* 00002158-00002178       .text daNpc_Km1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Km1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Km1_c*)i_this)->_create();
}

/* 00002178-00002198       .text daNpc_Km1_Delete__FP11daNpc_Km1_c */
static BOOL daNpc_Km1_Delete(daNpc_Km1_c* i_this) {
    return ((daNpc_Km1_c*)i_this)->_delete();
}

/* 00002198-000021B8       .text daNpc_Km1_Execute__FP11daNpc_Km1_c */
static BOOL daNpc_Km1_Execute(daNpc_Km1_c* i_this) {
    return ((daNpc_Km1_c*)i_this)->_execute();
}

/* 000021B8-000021D8       .text daNpc_Km1_Draw__FP11daNpc_Km1_c */
static BOOL daNpc_Km1_Draw(daNpc_Km1_c* i_this) {
    return ((daNpc_Km1_c*)i_this)->_draw();
}

/* 000021D8-000021E0       .text daNpc_Km1_IsDelete__FP11daNpc_Km1_c */
static BOOL daNpc_Km1_IsDelete(daNpc_Km1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Km1_Method = {
    (process_method_func)daNpc_Km1_Create,
    (process_method_func)daNpc_Km1_Delete,
    (process_method_func)daNpc_Km1_Execute,
    (process_method_func)daNpc_Km1_IsDelete,
    (process_method_func)daNpc_Km1_Draw,
};

actor_process_profile_definition g_profile_NPC_KM1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_KM1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Km1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_KM1,
    /* Actor SubMtd */ &l_daNpc_Km1_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
