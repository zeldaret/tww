/**
 * d_a_npc_p2.cpp
 * NPC - Zuko, Niko, & Mako
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_p2.h"
#include "d/actor/d_a_obj_timer.h"
#include "d/actor/d_a_player.h"
#include "d/d_lib.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "m_Do/m_Do_ext.h"


const u32 daNpc_P2_c::m_heapsize[] = {
    0x3EE0, 
    0x37E0, 
    0x4280

};
const char daNpc_P2_c::m_arc_name[] = "P2";


class daNpc_P2_childHIO_c{
public:
    daNpc_P2_childHIO_c();
    virtual ~daNpc_P2_childHIO_c(){};
public:
    dNpc_HIO_c base;
    u8 m2C;
    cXyz mGoalPosCircleCenter;
    cXyz m3C;
    cXyz mDemoCircleCenter;
    f32 mDemoCircleRadius;
    f32 mDemoCircleHalfHeight;
    f32 mGoalPosCircleRadius;
    f32 m60;
    f32 mGoalPosCircleHalfHeight;
    f32 m68;
    u8 m6C;
    f32 m70;
    f32 m74[0x12];
    f32 mBC;
    f32 mC0;
    f32 mC4;
    f32 mC8;
    f32 mCC;
    f32 mD0;
    //SIZE: 0xD4 ?????
};

class daNpc_P2_HIO_c: public mDoHIO_entry_c{
public:
    daNpc_P2_HIO_c();
    virtual ~daNpc_P2_HIO_c(){};
public:
    daNpc_P2_childHIO_c children[3];
    f32 m280;
    f32 m284;

};



/* 000000EC-0000020C       .text __ct__19daNpc_P2_childHIO_cFv */
daNpc_P2_childHIO_c::daNpc_P2_childHIO_c() {
    /* Nonmatching */
    m2C = 0;
    mDemoCircleCenter.x = 5.0f;
    mDemoCircleCenter.y = -545.0f;
    mDemoCircleCenter.z = 30.0f;
    mDemoCircleRadius = 80.0f;
    mDemoCircleHalfHeight = 180.0f;
    mGoalPosCircleCenter.x = 0.0f;
    mGoalPosCircleCenter.y = -550.0f;
    mGoalPosCircleCenter.z = -3020.0f;
    m3C.x = 0.0f;
    m3C.y = -550.0f;
    m3C.z = -3400.0f;
    mGoalPosCircleRadius = 200.0f;
    m60 = 300.0f;
    mGoalPosCircleHalfHeight = 30.0f;
    m68 = 300.0f;
    m6C = 0;
    m70 = 5000.0f;
    m74[0] = 0.0f;
    m74[1] = 14.0f;
    m74[2] = 8.0f;
    m74[3] = 8.0f;
    m74[4] = 4.0f;
    m74[5] = 0;
    m74[6] = 4.0f;
    m74[7] = 8.0f;
    m74[8] = 6.0f;
    m74[9] = 6.0f;
    m74[10] = 2.0f;
    m74[11] = 20.0f;
    m74[12] = 20.0f;
    m74[13] = 8.0f;
    m74[14] = 12.0f;
    m74[15] = 8.0f;
    m74[16] = 4.0f;
    m74[17] = 8.0f;
    mBC = 8.0f;
    mC0 = 8.0f;
    mC4 = 8.0f;
    mC8 = 8.0f;
    mCC = 15.0f;
    mD0 = 8.0f;
};

/* 00000248-000003E8       .text __ct__14daNpc_P2_HIO_cFv */
daNpc_P2_HIO_c::daNpc_P2_HIO_c() {
    //children[0].m28 = -20.0f;
    children[0].base.m04 = -20.0f;
    children[0].base.mMaxHeadX = 0x834;
    children[0].base.mMaxHeadY = 0x28A0;
    children[0].base.mMaxBackboneX = 0x0;
    children[0].base.mMaxBackboneY = 0x1130;
    children[0].base.mMinHeadX = -0x1ffe;
    children[0].base.mMinHeadY = -0x28a0;
    children[0].base.mMinBackboneX = 0;
    children[0].base.mMinBackboneY = -0x1130;
    children[0].base.mMaxTurnStep = 600;
    children[0].base.mMaxHeadTurnVel = 0;
    children[0].base.mAttnYOffset = 50.0;
    children[0].base.mMaxAttnAngleY = 0x4000;
    children[0].base.m22 = 0.0f;
    children[0].base.mMaxAttnDistXZ = 200.0;
    children[1].base.m04 = -26.0f;
    children[1].base.mMaxHeadX = 0x1FFE;
    children[1].base.mMaxHeadY = 0x4268;
    children[1].base.mMaxBackboneX = 0x0;
    children[1].base.mMaxBackboneY = 0xFA0;
    children[1].base.mMinHeadX = -0x1ffe;
    children[1].base.mMinHeadY = 0xC568;
    children[1].base.mMinBackboneX = 0;
    children[1].base.mMinBackboneY = 0XF060;
    children[1].base.mMaxTurnStep = 0X1000;
    children[1].base.mMaxHeadTurnVel = 0X800;
    children[1].base.mAttnYOffset = 50.0;
    children[1].base.mMaxAttnAngleY = 0x4000;
    children[1].base.m22 = 0;
    children[1].base.mMaxAttnDistXZ = 200.0;
    children[2].base.m04 = -20.0f;
    children[2].base.mMaxHeadX = 0x1FFE;
    children[2].base.mMaxHeadY = 0x2134;
    children[2].base.mMaxBackboneX = 0x0;
    children[2].base.mMaxBackboneY = 0x8E8;
    children[2].base.mMinHeadX = -0x1ffe;
    children[2].base.mMinHeadY = -0x2134;
    children[2].base.mMinBackboneX = 0;
    children[2].base.mMinBackboneY = -0x8e8;
    children[2].base.mMaxTurnStep = 0X960;
    children[2].base.mMaxHeadTurnVel = 0X7D0;
    children[2].base.mAttnYOffset = 50.0;
    children[2].base.mMaxAttnAngleY = 0x4000;
    children[2].base.m22 = 0;
    children[2].base.mMaxAttnDistXZ = 200.0;
    m280 = 3.0;
    m284 = 0.9;
};

daNpc_P2_HIO_c l_HIO;
static const u32 l_btp_ix_tbl[] = {0x36,0x37};
const u32 l_bmt_ix_tbl[] = {-1,0x32,0x33};
/* 00000490-0000068C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    /* Nonmatching */
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daNpc_P2_c* i_this = (daNpc_P2_c*)model->getUserArea();
        if(i_this != 0){
            s32 jointNo = ((J3DJoint*)node)->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jointNo));
            if (jointNo == 0x4) {

                static cXyz l_offsetAttPos(0.0f, 0.0f, 0.0f);
                static cXyz l_offsetEyePos(20.0f, 10.0f, 0.0f);
                cXyz* dest = &i_this->m704;
                mDoMtx_stack_c::multVec(&l_offsetAttPos,dest);
                mDoMtx_stack_c::XrotM(i_this->m_jnt.getHead_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getHead_x());
                mDoMtx_stack_c::multVec(&l_offsetEyePos, &i_this->getAttentionBasePos());
                if(i_this->m710 != 0xFF){
                    i_this->m710 += 1;
                }

            }else if(jointNo == 0x2){
                mDoMtx_stack_c::XrotM(i_this->m_jnt.getBackbone_y());
                mDoMtx_stack_c::ZrotM(i_this->m_jnt.getBackbone_x());
                mDoMtx_stack_c::ZrotM(REG12_S(0));
                mDoMtx_stack_c::XrotM(REG12_S(1));
                mDoMtx_stack_c::YrotM(REG12_S(2));
            }
                cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
                model->setAnmMtx(jointNo, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 0000068C-00000788       .text initTexPatternAnm__10daNpc_P2_cFb */
BOOL daNpc_P2_c::initTexPatternAnm(bool i_param_1) {
    /* Nonmatching */
    J3DModelData* model_data = m2B8->getModelData();
    J3DAnmTexPattern* head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes(m_arc_name,l_btp_ix_tbl[m7D0]);
    JUT_ASSERT(DEMO_SELECT(0x185,0x185),head_tex_pattern != 0);
    int iVar3 = mBtpAnm.init(model_data,head_tex_pattern,1,2,1.0,0,-1,i_param_1,0);
    if(!iVar3){

        return FALSE;
    }
    m378 = 0;
    m37A = 0;
    return TRUE;

}

/* 00000788-00000810       .text playTexPatternAnm__10daNpc_P2_cFv */
void daNpc_P2_c::playTexPatternAnm() {
    if(!cLib_calcTimer(&m37A)){
        s16 frame_max = mBtpAnm.getBtpAnm()->getFrameMax();
        if(m378 >= frame_max){
            m378 -= frame_max;
            m37A = cM_rndF(100.0f) + 30.0f;
        }else{
            m378 += 1;
        }
    }
}

/* 00000810-00000A90       .text setAnm__10daNpc_P2_cFv */
void daNpc_P2_c::setAnm() {
    /* Nonmatching */
    static s8 a_anm_num_tbl[3][0x18] = {-1,0x18,-1,-1,1,2,-1,-1,3,4,4,5,6,0x1A,-1,-1,-1,
    -1,-1,-1,-1,-1,0x19,0x1B,0xFF,7,8,9,1,2,0x12,0x13,
3,4,4,5,6,0xC,0xB,0xA,0xD,0xE,0xF,0x10,0x11,-1,-1,-1,
-1,0x14,-1,-1,1,2,-1,-1,3,4,4,5,6,0x16,0x17,-1,
-1,-1,-1,-1,-1,0x15,-1,-1};
    static u32 a_play_mode_tbl[] = {
        J3DFrameCtrl::EMode_NULL, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_NONE, J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_NONE, J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_NONE, J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_NONE, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_LOOP,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_NONE, J3DFrameCtrl::EMode_NONE,
        J3DFrameCtrl::EMode_LOOP, J3DFrameCtrl::EMode_NONE,
    };
    static f32 a_morf_frame_tbl[0x18] = {0.0f,14.0f,8.0f,8.0f,
        4.0f,0.0f,4.0f,8.0f,6.0f,6.0f,2.0f,20.0f,
    20.0f,8.0f,12.0f,8.0f,4.0f,8.0f,8.0f,8.0f,
8.0f,8.0f,15.0f,8.0f};
    static f32 a_play_speed_tbl[] = {0.0f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
    1.0f,0.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,
    1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,1.0f,};

    static const u32 a_anm_bck_tbl[] = {
        0x1D,0x1E,0x1C,7,
    8,0x1A,0x1B,0xF,
    0x18,0x19,0x13,0x14,
    0x15,0x16,0x10,0x17,
    0x11,0xE,0xD,0x12,
    0xB,0xC,0x9,0xA,
    0x22,0x20,0x21,0x1F};
    for(int i = 0; i < 0x18; i++){
        a_morf_frame_tbl[i] = l_HIO.children[m290].m74[i];
    }
    f32 speed;

        if(m7D4 != m7D3){
            s8 anm_num = a_anm_num_tbl[m290][m7D3];
            if(anm_num != -1){
                m7D2 = anm_num;
                m374 = 0;

            
            speed = a_play_speed_tbl[m7D3];

            if(mEventCut.getMoveSpeed() != 0){
                switch(mEventCut.getNowCut()){

                    case 2:
                    case 4:
                        speed = mEventCut.getMoveSpeed() * 0.25f;
                    default:
                        break;
                }
            }

        dNpc_setAnm(mpMorf,a_play_mode_tbl[m7D3],
            a_morf_frame_tbl[m7D3],
            speed,

            a_anm_bck_tbl[m7D2],
            -1,
            m_arc_name);
        
        }   
    }



    if(mpMorf->getFrame() == 1.0f){
        switch(m7D2){
            case 0x12:
                fopAcM_monsSeStart(this,JA_SE_CV_NK_BEF_JUMP,0);
                break;
        }

        
    }
        m7D4 = m7D3;
        if(mpMorf->isStop() && m7D3 == 0x13){
            m7D3 = 3;
        }
        if(m7D3 == 0x7 && mpMorf->isStop()){
            m7D3 = 1;

        }
        if(m290 == 0){
            if(mpMorf->isStop() && m7D3 == 0x17){
                m7D3 = 0xD;
            }
        }

    return;



}

/* 00000A90-00000AFC       .text setTexAnm__10daNpc_P2_cFv */
void daNpc_P2_c::setTexAnm() {
    /* Nonmatching */
    static s8 a_tex_pattern_num_tbl[2][0x17] = {
        {0xFF},
        {0xFF,0x01}

    };
    
    if ( !(m7D0 == a_tex_pattern_num_tbl[m290][m7D1] ||  a_tex_pattern_num_tbl[m290][m7D1] == -1 || m290 == 2)) {
        m7D0 = a_tex_pattern_num_tbl[m290][m7D1];
        initTexPatternAnm(true);
    }
    return;
}

static char* action_table[] ={
    "TALK",
    "RIDE_SWITCH",
    "RUN_WAIT",
    "JUMP_TO_LIFT",
    "LIFT_TO_ROPE",
    "ROPE_TALK",
    "ROPE_TO_LIFT",
    "JUMP_TO_GOAL",
    "SET_ANM",
    "JUMP",
    "SW_ON",
    "SW_OFF",
    "SURPRISE",
    "OMAMORI_INIT",
    "OMAMORI_END"
};
static char* p2bEarlyRemoveLater[] = {"P2b","MsgNum","Attention","Speed_y","Gravity","Timer","Speed","Pos","Name","KYORO","THINK","NOD","WAIT01"};
/* 00000AFC-00000B90       .text setAttention__10daNpc_P2_cFv */
void daNpc_P2_c::setAttention() {
    /* Nonmatching */
    bool is_morf = mpMorf->isMorf();
    if(  m750 == 0 || is_morf){
            f32 fVar1,fVar2;
            fVar2 = m6F8.z;
            fVar1 = m6F8.y;
            eyePos.set(m6F8.x,fVar1,fVar2);
            attention_info.position.set(m704.x,m704.y + l_HIO.children[m290].base.mAttnYOffset,m704.z);

    }

    m750 = 0;
    return;
}

/* 00000B90-00000CEC       .text chkAttention__10daNpc_P2_cFv */
bool daNpc_P2_c::chkAttention() {
    /* Nonmatching */

    f32 dist_xz = fopAcM_searchPlayerDistanceXZ(this);
    s16 sVar1 = l_HIO.children[m290].base.mMaxAttnAngleY;
    s16 iVar5 = (current.angle.y + m_jnt.getHead_y() + m_jnt.getBackbone_y());

    if((m290 == 1) && (m7C1 != 0  ||  (m7D6 == 0x15)) && (dist_xz < l_HIO.children[m290].base.mMaxAttnDistXZ)){
        return true;
    }
    if(sVar1 > abs(iVar5) && dist_xz < l_HIO.children[m290].base.mMaxAttnDistXZ && dComIfGp_event_runCheck()){
        return true;
    }

    dAttention_c& attention = dComIfGp_getAttention();
    if(attention.LockonTruth()) {
        return this == attention.LockonTarget(0);

    }
    return this == attention.ActionTarget(0);


}

/* 00000CEC-000010E8       .text lookBack__10daNpc_P2_cFv */
void daNpc_P2_c::lookBack() {
    cXyz local_30;
    cXyz lookTarget(0.0f,0.0f,0.0f);
    cXyz* dstPos = NULL;
    s16 desiredAngle = current.angle.y;
    bool headOnly = mEventCut.getAttnNoTurnFlag();


    if (m72C || mEventCut.getAttnFlag()) {
        m_jnt.setTrn();
        local_30 = mEventCut.getAttnPos() + m7DC;
        dstPos = &local_30;
        lookTarget = current.pos;
        lookTarget.y = eyePos.y;


    } else {
        if (m7D6 == 0xE) {
            m_jnt.setTrn();
        }

        switch (m7D6) {
        case 9:
        case 10:
            m_jnt.setTrn();
            local_30 = m730;
            dstPos = &local_30;
            lookTarget = current.pos;
            lookTarget.y = eyePos.y;
            break;
        case 2:
            m_jnt.setTrn();
            local_30 = dNpc_playerEyePos(l_HIO.children[m290].base.m04);
            dstPos = &local_30;
            lookTarget = current.pos;
            lookTarget.y = eyePos.y;
            break;
        default:
            if (m724) {
                local_30 = dNpc_playerEyePos(l_HIO.children[m290].base.m04);
                dstPos = &local_30;
                lookTarget = current.pos;
                lookTarget.y = eyePos.y;
            }
            break;
        }
    }

    if (m290 == 0) {
        if (m7D3 == 0x17) {
            fopAc_ac_c* actor = fopAcM_SearchByName(fpcNm_NPC_ZL1_e);

            if (actor) {

                cLib_addCalcAngleS2(
                    &current.angle.y,
                    fopAcM_searchActorAngleY(this, actor),
                    4, 0x800);
                lookTarget = current.pos;
                lookTarget.y = eyePos.y;
                m_jnt.onHeadLock();
                m_jnt.onBackBoneLock();
                m_jnt.lookAtTarget(
                    &current.angle.y,
                    &actor->current.pos,
                    lookTarget,
                    desiredAngle,
                    m6F2,
                    false);
                return;
            }
        } else if (m7D3 == 0x16) {
            headOnly = false;
            m_jnt.clrTrn();
            m_jnt.onHeadLock();
            m_jnt.onBackBoneLock();
        } else {
            m_jnt.offHeadLock();
            m_jnt.offBackBoneLock();
        }
    }

    if (m7D6 == 0x10) {
        headOnly = false;
        m_jnt.clrTrn();
    }

    if (m290 == 1 &&
        m7D6 == 0xD &&
        m291 == 1) {

        m_jnt.setTrn();
        local_30 = m73C;
        dstPos = &local_30;

        lookTarget = current.pos;
        lookTarget.y = eyePos.y;
    }

    if (m_jnt.trnChk()) {
        cLib_addCalcAngleS2(
            &m6F2,
            l_HIO.children[m290].base.mMaxHeadTurnVel,
            4,
            0x800);

    } else {
        m6F2 = 0;
    }
    m_jnt.lookAtTarget(
        &current.angle.y,
        dstPos,
        lookTarget,
        desiredAngle,
        m6F2,
        headOnly);

}

/* 000010E8-00001160       .text setMtx__10daNpc_P2_cFv */
void daNpc_P2_c::setMtx() {

    J3DModel* model = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(current.angle);
    model->setBaseTRMtx(mDoMtx_stack_c::get());

}

/* 00001160-00001204       .text setCollision__10daNpc_P2_cFv */
void daNpc_P2_c::setCollision() {
    /* Nonmatching */
    if(m7C1 != 0){
        m5BC.SetC(current.pos);
        m5BC.SetR(90.0f);
        m5BC.SetH(120.0f);
    }else{
        m5BC.SetC(current.pos);
        m5BC.SetR(30.0f);
        m5BC.SetH(120.0f);
    }
    dComIfG_Ccsp()->Set(&m5BC);
}

/* 00001204-00001338       .text smoke_set__10daNpc_P2_cFv */
void daNpc_P2_c::smoke_set() {
    /* Nonmatching */
    static JGeometry::TVec3<f32> smoke_scale(1.25f,1.25f,1.25f);
    JPABaseEmitter* p_smoke_emitter = (JPABaseEmitter*)m754.getEmitter();
    if(m754.getEmitter() == NULL){
        p_smoke_emitter = dComIfGp_particle_setToon(0x2022,&mSmokePos,&mSmokeAngle,NULL,0xB9,&m754,fopAcM_GetRoomNo((fopAc_ac_c*)this));
    }
    p_smoke_emitter = (JPABaseEmitter*)m754.getEmitter();
    if(p_smoke_emitter != NULL){
        p_smoke_emitter->setRate(2.0f);
        m754.getEmitter()->setSpread(0.25f);
        m754.getEmitter()->setAwayFromCenterSpeed(0.0f);
        m754.getEmitter()->setAwayFromAxisSpeed(5.0f);
        m754.getEmitter()->setDirectionalSpeed(20.0f);
        m754.getEmitter()->setGlobalScale(smoke_scale);
    }
}

/* 00001338-00001534       .text next_msgStatus__10daNpc_P2_cFPUl */
u16 daNpc_P2_c::next_msgStatus(unsigned long* pMsgNo) {
    /* Nonmatching */
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;
    switch (*pMsgNo) {                        /* irregular */
    case 0x1011:
        *pMsgNo = 0x102F;
        break;
    case 0x102F:
        *pMsgNo = 0x1030;
        break;
    case 0x1012:
        *pMsgNo = 0x1031;
        break;
    case 0x1031:
        *pMsgNo = 0x1032;
        break;
    case 0xC96:
        *pMsgNo = 0xC98;
        break;
    case 0x1018:
        *pMsgNo = 0x1019;
        break;
    case 0x1020:
        *pMsgNo = 0x1021;
        break;
    case 0x1022:
        *pMsgNo = 0x102C;
        break;
    case 0x1023:
        *pMsgNo = 0x1024;
        break;
    case 0x1025:
        *pMsgNo = 0x1026;
        break;
    case 0x1026:
        *pMsgNo = 0x1027;
        break;
    case 0x1027:
        *pMsgNo = 0x102D;
        break;
    case 0x1B20:
        *pMsgNo = 0x1B21;
        break;
    case 0x1B21:
        *pMsgNo = 0x1B22;
        break;
    case 0x1B22:
        *pMsgNo = 0x1B23;
        break;
    case 0x1B23:
        *pMsgNo = 0x1B24;
        break;
    case 0x1B28:
        *pMsgNo = 0x1B29;
        break;
    case 0x1B29:
        *pMsgNo = 0x1B2A;
        break;
    case 0x1B2A:
        *pMsgNo = 0x1B2B;
        break;
    case 0x1B2B:
        *pMsgNo = 0x1B2C;
        break;
    case 0x1B2C:
        *pMsgNo = 0x1B2D;
        break;
    case 0x1B2D:
        *pMsgNo = 0x1B2E;
        break;
    default:
        msgStatus = fopMsgStts_MSG_ENDS_e;
        break;
    }
    return msgStatus;
}

/* 00001534-000016CC       .text getMsg__10daNpc_P2_cFv */
u32 daNpc_P2_c::getMsg() {

    u32 o_retval = 0;
    switch(m290){
        case 0:
            if(dComIfGs_isEventBit(0x808) == 0){
                o_retval = dLib_setFirstMsg(0x702,0x100e,0x100f);

            }else{
                o_retval = 0x1010;
            }
            break;
        case 1:
            if(m291 == 1){
                if(dComIfGs_isEventBit(0xF02) != 0){
                    o_retval = dLib_setFirstMsg(0x1502,0x1B35,0x1B36);

                }else{
                    o_retval = 0x1028;
                }
            }else{
                if(!dComIfGs_isEventBit(0x720)){
                    o_retval = dLib_setFirstMsg(0x940,0xC96,0xC97);
                }else{
                    if(!dComIfGs_isEventBit(0x808)){
                        if(dComIfGs_isEventBit(0x710)){
                            o_retval = 0x1028;
                        }
                    }else{
                        o_retval = dLib_setFirstMsg(0x704,0x1029,0x102A);
                    }
                }
            }
            break;
        case 2:
            if(dComIfGs_isEventBit(0x808) == 0){
                o_retval = dLib_setFirstMsg(0x701,0x1011,0x1012);
            }else{
                o_retval = 0x1013;
            }
            break;
    }
    return o_retval;
}

/* 000016CC-000016D8       .text talkInit__10daNpc_P2_cFv */
void daNpc_P2_c::talkInit() {
    /* Nonmatching */
    m809 = 0;
    return;
}

/* 000016D8-000017AC       .text anmAtr__10daNpc_P2_cFUs */
void daNpc_P2_c::anmAtr(unsigned short i_param_1) {
    /* Nonmatching */

    static const s8 anm_atr[] = {
        0x1,0x2,0x3,0xF,0xE,0xD,0x10,0x11,
        0x12,0x13,0x14,0x1,0x2,0xD,0xE,0x1,
        0x16,0xD,0x17,0x7,0x6
    };

    if (i_param_1 == 6) {
        u8 mesgAnime = dComIfGp_getMesgAnimeAttrInfo();
        if (mesgAnime < 0x15) {
            if (m290 == 0 && m7D3 == 0xD && anm_atr[mesgAnime] == 0x17) {
                return;
            }
            if (m290 == 1 && anm_atr[mesgAnime] == 0x7) {
                if (m751 != 0) {
                    return;
                }
                m751 = 1;
                m7D3 = anm_atr[mesgAnime];
                return;
            }
            if (m7D3 != anm_atr[mesgAnime]) {
                m7D3 = anm_atr[mesgAnime];
            }
            return;
        }
        m7D3 = 1;
        return;
    }
    if (i_param_1 == 0x10) {
        m7D3 = 1;
        return;
    }

}

static u32 l_msgId;
static msg_class* l_msg;
/* 000017AC-00001918       .text talk__10daNpc_P2_cFb */
u16 daNpc_P2_c::talk(bool i_param_1) {
    /* Nonmatching */
    u16 mode = 0xFF;
    s8 temp01 = m809;
    if(m809 == 0){
        l_msgId = -1;

        if (!i_param_1) {
            m728 = getMsg();
        }

        m809 = 1;
    }else if(m809 == -1){
        mode = 0x12;
        anmAtr(0x12);  
    }else if(l_msgId == -1){
        l_msgId = fopMsgM_messageSet(m728, this);

    }else{

        switch (temp01) {
            case 1:
                l_msg = fopMsgM_SearchByID(l_msgId);

                if (l_msg != NULL) {
                    m809 = 2;
                }
                break;
            case 2:
                mode = l_msg->mStatus;

                if (mode == 0xE) {
                    l_msg->mStatus = next_msgStatus(&m728);

                    if (l_msg->mStatus == 0xF) {
                        fopMsgM_messageSet(m728);
                    }
                }
                else if (mode == 0x12) {
                    l_msg->mStatus = 0x13;
                    m809 = -1;
                    m751 = 0;
                }

                anmAtr(mode);
                break;


        }
    }

    return mode;
}

/* 00001918-00001998       .text eventOrder__10daNpc_P2_cFv */
void daNpc_P2_c::eventOrder() {
    static char* a_demo_name_tbl[0x8] = {
        "P2B_INTRO",
        "P2B_TO_GOAL",
        "P2B_GOAL_WAIT_TALK",
        "P2B_GOAL",
        "P2B_ARRIVE_MAJYU",
        "P2B_INTRO_2",
        "P2B_GOAL_2",
        "P2B_BOMB_GET"
    };

    if ((m7D5 == 1) || (m7D5 == 2)) {
        eventInfo.onCondition(dEvtCmd_INTALK_e);
        if (m7D5 == 1) {
            fopAcM_orderSpeakEvent((fopAc_ac_c *) this);
        }
    } else if (m7D5 >= 3) {
        fopAcM_orderOtherEvent2((fopAc_ac_c *) this, a_demo_name_tbl[m7D5-3], 1, 0xFFFF);
    }
}

/* 00001998-00001A00       .text checkOrder__10daNpc_P2_cFv */
void daNpc_P2_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()){
        m7D5 = 0;
    }else if(eventInfo.checkCommandTalk() && (m7D5 == 1 || m7D5 == 2)){
        m7D5 = 0;
        m725 = 1;
        talkInit();
    }
    return;

}

/* 00001A00-00001A7C       .text demo_wait_2__10daNpc_P2_cFv */
void daNpc_P2_c::demo_wait_2() {
    /* Nonmatching */
    //l_HIO.children[0]
    daNpc_P2_childHIO_c* hio_child = &l_HIO.children[m290];
    if(dLib_checkPlayerInCircle(l_HIO.children[m290].mDemoCircleCenter,l_HIO.children[m290].mDemoCircleRadius,l_HIO.children[m290].mDemoCircleHalfHeight)){
        m7D5 = 0x8;
        m7D6 = 0x13;
    }
    return;
}

/* 00001A7C-00001B00       .text demo_intro_2__10daNpc_P2_cFv */
void daNpc_P2_c::demo_intro_2() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck("P2B_INTRO_2")){
        dComIfGs_onEventBit(0x1A04);
        m7D6 = 0x14;
        m7D5 = 0x0;
        dComIfGp_event_onEventFlag(0x8);
    }
}

/* 00001B00-00001BBC       .text goal_wait_2__10daNpc_P2_cFv */
void daNpc_P2_c::goal_wait_2() {
    /* Nonmatching */

    BOOL switch_bool = fopAcM_isSwitch(this,m292);
    if(switch_bool){
        if(dLib_checkPlayerInCircle(l_HIO.children[m290].m3C,l_HIO.children[m290].m60,l_HIO.children[m290].m68)){
            m7D6 = 0x15;
            
            daObjTimer::Act_c* timer = (daObjTimer::Act_c*)fopAcM_SearchByName(fpcNm_Obj_Timer_e);
            if(timer){
                timer->stopTimer();
            }
        }
    }
}

/* 00001BBC-00001C74       .text demo_goal_2__10daNpc_P2_cFv */
void daNpc_P2_c::demo_goal_2() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck("P2B_GOAL_2")){
        m7D6 = 0xD;
        m7D5 = 0;
        m7C1 = 1;

        m73C =  mEventCut.getAttnPos() + m7DC; 
        dComIfGp_event_onEventFlag(0x8);
    }else{
        m7D5 = 9;
    }
    return;
}

/* 00001C74-00001CFC       .text demo_bomb_get__10daNpc_P2_cFv */
void daNpc_P2_c::demo_bomb_get() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck("P2B_BOMB_GET")){
        dComIfGs_onEventBit(0xF02);
        m7D6 = 1;
        m7D5 = 0;
        m7C1 = 0;
        dComIfGp_event_onEventFlag(0x8);
    }
    return;
}

/* 00001CFC-00001D78       .text demo_wait__10daNpc_P2_cFv */
void daNpc_P2_c::demo_wait() {
    /* Nonmatching */
    if(dLib_checkPlayerInCircle(l_HIO.children[m290].mDemoCircleCenter,l_HIO.children[m290].mDemoCircleRadius,l_HIO.children[m290].mDemoCircleHalfHeight)){
        m7D5 = 0x3;
        m7D6 = 0x4;

        }
        // daObjTimer::Act_c* timer = (daObjTimer::Act_c*)fopAcM_SearchByName(fpcNm_Obj_Timer_e);
        // if(timer){
        //     timer->stopTimer();
        // }
    
    return;
}

/* 00001D78-00001DE8       .text demo_intro__10daNpc_P2_cFv */
void daNpc_P2_c::demo_intro() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck("P2B_INTRO")){
        m7D6 = 0x5;
        m7D5 = 0x0;
        dComIfGp_event_onEventFlag(0x8);
    }
    return;    
}

/* 00001DE8-00001E4C       .text demo_lift__10daNpc_P2_cFv */
void daNpc_P2_c::demo_lift() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck("Hlift_up")){
        m7D6 = 0x6;
        m7D5 = 0x4;
        m804 = 0;
    }
    return;
}

/* 00001E4C-00001EC8       .text demo_jump__10daNpc_P2_cFv */
void daNpc_P2_c::demo_jump() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck("P2B_TO_GOAL")){
        dComIfGs_onEventBit(0x720);
        m7D6 = 9;
        dComIfGp_event_onEventFlag(0x8);
    }
    return;
}

/* 00001EC8-000021C4       .text goal_goalpos_to_talkpos__10daNpc_P2_cFv */
void daNpc_P2_c::goal_goalpos_to_talkpos() {
    /* Nonmatching */
    m7C1 = 1;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if((current.pos.y - player->current.pos.y - 300.f) < 0.0f){
        m7D6 = 0xA;
        return;
    }
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x0;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x0; 

    static cXyz aim_pos = cXyz(0.0f,-450.0f,-2915.0f);
    static cXyz attn_pos = cXyz(0.0f,-450.0f,-2715.0f);

    s16 sVar5 = cLib_targetAngleY(&current.pos,&aim_pos);
    m730 = attn_pos;
    f32 fVar8;
    if(std::fabsf(sVar5 - current.angle.y) < 5376.0f){
        m7D3 = 0x4;
        cLib_addCalc2(&current.pos.x,aim_pos.x,0.1,4.0);
        cLib_addCalc2(&current.pos.z,aim_pos.z,0.1,4.0);
    }     
    fVar8 = (aim_pos - current.pos).absXZ();



    if(fVar8 < 5.0f){
        m7D3 = 0x1;
        m7D6 = 0x7;
    }

    if(dLib_checkPlayerInCircle(l_HIO.children[m290].mGoalPosCircleCenter,l_HIO.children[m290].mGoalPosCircleRadius,l_HIO.children[m290].mGoalPosCircleHalfHeight) && !player->checkPlayerFly()){
        m7D6 = 0xC;
        daObjTimer::Act_c* timer = (daObjTimer::Act_c*)fopAcM_SearchByName(fpcNm_Obj_Timer_e);
        if(timer){
            timer->stopTimer();
        }
    }
    
}

/* 000021C4-000025B8       .text goal_talkpos_to_goalpos__10daNpc_P2_cFv */
void daNpc_P2_c::goal_talkpos_to_goalpos() {
    /* Nonmatching */
    m7C1 = 1;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if(
        fopAcM_searchPlayerDistanceXZ(this) < l_HIO.children[m290].m70 && 
        (current.pos.y - player->current.pos.y - 300.f) > 0.0f
    ){
        m7D6 = 0x9;
        return;
    }
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x0;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x0; 
    static cXyz aim_pos = cXyz(0.0f,-450.0f,-3130.0f);
    static cXyz attn_pos = cXyz(0.0f,-450.0f,-3380.0f);
    static cXyz talk_attn_pos = cXyz(0.0f,-450.0f,-2715.0f);
    

    f32 fVar8 = (aim_pos - current.pos).absXZ();
    if( fVar8 < 5.0f){
        m730 = talk_attn_pos;
    }else{
        m730 = attn_pos;
    }
//cLib_targetAngleY(&current.pos,&m730)
    s16 sVar5 = cLib_targetAngleY(&current.pos,&m730);
    if( fVar8 < 5.0f){
        //f32 diff = fabs(sVar5-current.angle.y);
        if(std::fabsf(sVar5-current.angle.y) < 5376.0f){
            m7D3 = 0x1;
            m7D6 = 0xB;
        }
    }else{

        if(std::fabsf(sVar5 - current.angle.y) < 5376.0f){
            m7D3 = 4;
            cLib_addCalc2(&current.pos.x,aim_pos.x,0.1,4.0);
            cLib_addCalc2(&current.pos.z,aim_pos.z,0.1,4.0);
        }
    }
    if(dLib_checkPlayerInCircle(l_HIO.children[m290].mGoalPosCircleCenter,l_HIO.children[m290].mGoalPosCircleRadius,l_HIO.children[m290].mGoalPosCircleHalfHeight) && !player->checkPlayerFly()){
        m7D6 = 0xC;
        daObjTimer::Act_c* timer = (daObjTimer::Act_c*)fopAcM_SearchByName(fpcNm_Obj_Timer_e);
        if(timer){
            timer->stopTimer();
        }
    }
}

/* 000025B8-000026F4       .text goal_goalpos_wait__10daNpc_P2_cFv */
void daNpc_P2_c::goal_goalpos_wait() {
    /* Nonmatching */

    m7C1 = 1;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    if(
        fopAcM_searchPlayerDistanceXZ(this) < l_HIO.children[m290].m70 && 
        (current.pos.y - player->current.pos.y - 300.f) > 0.0f
    ){
        m7D6 = 0x9;
        return;
    }
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x2;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x2;   
    if(dLib_checkPlayerInCircle(l_HIO.children[m290].mGoalPosCircleCenter,l_HIO.children[m290].mGoalPosCircleRadius,l_HIO.children[m290].mGoalPosCircleHalfHeight)){
        if(!player->checkPlayerFly()){
            m7D6 = 0xC;
            daObjTimer::Act_c* timer = (daObjTimer::Act_c*)fopAcM_SearchByName(fpcNm_Obj_Timer_e);
            if(timer){
                timer->stopTimer();
            }
        }  
    }
 
}

/* 000026F4-00002864       .text goal_talkpos_wait__10daNpc_P2_cFv */
void daNpc_P2_c::goal_talkpos_wait() {
    /* Nonmatching */
    m7C1 = 1;
    daPy_py_c* player = daPy_getPlayerActorClass();
    if((current.pos.y - player->current.pos.y - 300.f) < 0.0f){
        m7D6 = 0xA;
        return;
    }
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x22;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x22;
    if(m74A == 0){
        m7D5 = 1;
        m74A = 1;
    }else{
        if(m725 != 0){
            m7D6 = 0x8;
            dComIfGp_event_onEventFlag(0x8);
            m7D5 = 0x5;
        }else{
            if(fopAcM_GetSpeedF(player) < 1.0f){
                m7D5 = 2;
            }
        }

        if(dLib_checkPlayerInCircle(l_HIO.children[m290].mGoalPosCircleCenter,l_HIO.children[m290].mGoalPosCircleRadius,l_HIO.children[m290].mGoalPosCircleHalfHeight) && !player->checkPlayerFly()){
            m7D6 = 0xC;
            daObjTimer::Act_c* timer = (daObjTimer::Act_c*)fopAcM_SearchByName(fpcNm_Obj_Timer_e);
            if(timer){
                timer->stopTimer();
            }
        }
    }

    return;
}

/* 00002864-00002908       .text demo_goal__10daNpc_P2_cFv */
void daNpc_P2_c::demo_goal() {
    /* Nonmatching */
    m7C1 = 0;
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    if(dComIfGp_evmng_endCheck("P2B_GOAL")){
        dComIfGs_onEventBit(0x710);
        m7D6 = 0xD;
        m7D5 = 0;
        dComIfGp_event_onEventFlag(0x8);
    }else{
        m7D5 = 0x6;
    }
    return;
}

/* 00002908-00002978       .text goal_talkpos_talk__10daNpc_P2_cFv */
void daNpc_P2_c::goal_talkpos_talk() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck("P2B_GOAL_WAIT_TALK")){
        m7D6 = 0x7;
        dComIfGp_event_onEventFlag(0x8);
        m725 = 0;
    }
    return;
}

/* 00002978-00002A20       .text treasure_wait__10daNpc_P2_cFv */
void daNpc_P2_c::treasure_wait() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck("DEFAULT_TREASURE")){
        if(m291 == 0){
            m7D6 = 0xF;
            m7D5 = 0x7;
        }else if(m291 == 1){
            m7D6 = 0x16;
            m7D5 = 0xA;
        }
    }else if(m725 != 0){
        m7D6 = 0xE;
    }else{
        m7D5 = 0x2;
    }
    return;
}

/* 00002A20-00002A88       .text treasure_wait_talk__10daNpc_P2_cFv */
void daNpc_P2_c::treasure_wait_talk() {
    /* Nonmatching */
    m750 = 1;
    if(talk(false) == 0x12){
        m7D6 = 0xD;
        m725 = 0;
        dComIfGp_event_onEventFlag(0x8);
    }
    return;
}

/* 00002A88-00002B18       .text demo_arrive__10daNpc_P2_cFv */
void daNpc_P2_c::demo_arrive() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck("P2B_ARRIVE_MAJYU")){
        dKy_instant_timechg(300);
        dComIfGs_onEventBit(0x808);
        m7D6 = 1;
        m7D5 = 0;
        dComIfGp_event_onEventFlag(0x8);
    }
    return;
}

/* 00002B18-00002B3C       .text wait01__10daNpc_P2_cFv */
void daNpc_P2_c::wait01() {
    /* Nonmatching */
    if(m725 != 0){
        m7D6 = 2;
        return;
    }
    m7D5 = 2;
    return;

}

/* 00002B3C-00002BE8       .text zukotelescope__10daNpc_P2_cFv */
void daNpc_P2_c::zukotelescope() {
    /* Nonmatching */
    m7D3 = 0x16;
    if (parentActorID != -1) {
        fopAc_ac_c* actor = fopAcM_SearchByID(parentActorID);

        cLib_addCalcAngleS2(
            &current.angle.y,
            m748 + actor->current.angle.y,
            4, 0x800);
    }

    if (m725 != 0) {
        m7D3 = 1;
        m_jnt.offHeadLock();
        m_jnt.offBackBoneLock();
        m7D6 = 2;

    } else {
        m7D5 = 2;
    }
}

/* 00002BE8-00002D78       .text moccowait__10daNpc_P2_cFv */
void daNpc_P2_c::moccowait() {
    /* Nonmatching */

    if(parentActorID != -1){
        cLib_addCalcAngleS2(
            &current.angle.y,
            m748 + fopAcM_SearchByID(parentActorID)->current.angle.y,
            4, 0x800);
    }

    if (m7D3 == 0x15) {
        mpMorf2->setFrame(mpMorf->getFrame());
    } else {
        mpMorf2->setFrame(0.0f);
    }

    if (m7D3 == 1 && cLib_calcTimer(&m74C) == 0) {
        m7D3 = 0x15;
        m74C = (s16)(cM_rndF(100.0f) + 200.0f);
    }

    if (m7D3 == 0x15) {

        if (mpMorf->isStop()) {
            m7D3 = 1;
        }
    }

    if (m725 != 0 && m7D3 == 1) {
        m7D6 = 2;
    } else {
        m7D5 = 2;
    }
}

/* 00002D78-00002E38       .text talk01__10daNpc_P2_cFv */
void daNpc_P2_c::talk01() {
    /* Nonmatching */
    if (talk(false) == 0x12) {
        if (m290 == 2) {
            m7D3 = 1;
            m7D6 = 0x10;
        }
        else if ((m290 == 0) && !dComIfGs_isEventBit(0x808)) {
            m7D6 = 0x11;
            m_jnt.onHeadLock();
            m_jnt.onBackBoneLock();
        }
        else {
            m7D3 = 1;
            m7D6 = 1;
        }

        dComIfGp_event_onEventFlag(8);
        m725 = 0;
    }


}

/* 00002E38-00003030       .text intro_action__10daNpc_P2_cFPv */
BOOL daNpc_P2_c::intro_action(void*) {
    /* Nonmatching */
    if(m808 == 0){
        if(m291 == 0){
            if(!dComIfGs_isEventBit(0x720)){
                m7D6 = 3;
            }else{
                m7D6 = 10;
            }
        }else{
            if(!dComIfGs_isEventBit(0x1A04)){
                m7D6 = 0x12;
            }else{
                m7D6 = 0x14;
            }
        }
        m808 += 1;
    }else if(m808 != -1){
        m724 = chkAttention();
        m7D5 = 0;
        switch(m7D6){
            case 1:
            wait01();
            break;
            case 2:
            talk01();
            break;
            case 3:
            demo_wait();
            break;
            case 4:
            demo_intro();
            break;
            case 5:
            demo_lift();
            break;
            case 6:
            demo_jump();
            break;
            case 7:
            goal_talkpos_wait();
            break;
            case 8:
            goal_talkpos_talk();
            break;
            case 9:
            goal_goalpos_to_talkpos();
            break;
            case 10:
            goal_talkpos_to_goalpos();
            break;
            case 0xb:
            goal_goalpos_wait();
            break;
            case 0xc:
            demo_goal();
            break;
            case 0xd:
            treasure_wait();
            break;
            case 0xe:
            treasure_wait_talk();
            break;
            case 0xf:
            demo_arrive();
            break;
            case 0x12:
            demo_wait_2();
            break;
            case 0x13:
            demo_intro_2();
            break;
            case 0x14:
            goal_wait_2();
            break;
            case 0x15:
            demo_goal_2();
            break;
            case 0x16:
            demo_bomb_get();
            break;
        }
        lookBack();
        setAttention();
    }
    return TRUE;
}

/* 00003030-00003158       .text wait_action__10daNpc_P2_cFPv */
BOOL daNpc_P2_c::wait_action(void*) {
    /* Nonmatching */
    if(!m808){
        if(m290 == 2){
            m7D6 = 0x10;
        }else if(m290 == 0 && !dComIfGs_isEventBit(0x808)){
            m7D6 = 0x11;
        }else{
            m7D6 = 1;
        }
        m808 += 1;
    }else if(m808 != -1){
        m724 = chkAttention();
        m7D5 = 0;
        switch(m7D6){
            case 1:
                wait01();
                break;
            case 0x10:
                moccowait();
                break;
            case 0x11:
                zukotelescope();
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

/* 00003158-00003520       .text _execute__10daNpc_P2_cFv */

enum P2_ACT_IDX{
    MONE = -1,
    ZERO = 0,
    ONE = 1,
    TWO = 2,
    THREE = 3,
    FOUR = 4,
    FIVE = 5,

};
bool daNpc_P2_c::_execute() {
    /* Nonmatching */

    m_jnt.setParam(
        l_HIO.children[m290].base.mMaxBackboneX,
        l_HIO.children[m290].base.mMaxBackboneY,
        l_HIO.children[m290].base.mMinBackboneX,
        l_HIO.children[m290].base.mMinBackboneY,
        l_HIO.children[m290].base.mMaxHeadX,
        l_HIO.children[m290].base.mMaxHeadY,
        l_HIO.children[m290].base.mMinHeadX,
        l_HIO.children[m290].base.mMinHeadY,
        l_HIO.children[m290].base.mMaxTurnStep       
    );

    if (m290 != 2) {
        playTexPatternAnm();
    }

    m370 = mpMorf->play(
        &eyePos,
        mAcch.ChkGroundHit() ? dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd) : 0,
        dComIfGp_getReverb(fopAcM_GetRoomNo(this)));

    if (mpMorf->getFrame() < m374) {
        m370 = true;
    }

    m374 = mpMorf->getFrame();

    checkOrder();

    (this->*mActionFunc)(NULL);

    if (dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()) {

        if (!mEventCut.cutProc()) {
            mEventCut.setAttnFlag(false);
            cutProc();
        } else {
            m72C = 0;
            if(mEventCut.getNowCut() != -1){
                switch (mEventCut.getNowCut()) {
                case 2:
                case 4:
                    if (mEventCut.getMoveSpeed() == 0.0f) {
                        m7D3 = 1;
                    } else if (mEventCut.getMoveSpeed() > 10.0f) {
                        m7D3 = 5;

                    } else {
                        m7D3 = 4;
                        break;
                    }
                    break;
                default:
                    m7D3 = 1;
                    break;
                }
            }else{
                m7D3 = 1;
            }

        }
    }

    if (!dComIfGp_event_runCheck()) {
        mEventCut.setAttnNoTurnFlag(false);
        mEventCut.setAttnFlag(false);

        m72C = 0;
    }

    eventOrder();

    setAnm();
    setTexAnm();

    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mAcch.CrrPos(*dComIfG_Bgsp());
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);

    setMtx();

    mpMorf->calc();

    if (m7C0) {
        J3DModel* model = mpMorf->getModel();
        himo3_class* himo3 = m7BC;

        dLib_getPosFromMtx(model->getAnmMtx(0xC),&m78C);

        himo3->setActorHang(m78C, shape_angle.y);
    }

    setCollision();
    if(m7D3 == 4){
        //f32 fVar1,fVar9;
        f32 fVar1 = (current.pos-old.pos).abs()/(REG12_F(6)+10.0f);
        // fVar1 = 0.0f;
        //f32 fVar1 = cLib_minMaxLimit(fVar9,0.0f,1.0f);
        //f32 fVar1 = (fVar9 <= 0.0f) ? fVar9 :( (fVar9 >= 1.0f) ? 1.0f : 0.0f);
        //f32 fVar1;

        if(fVar1 <= 0.0f){
            fVar1 = 0.0f;
        }else if(fVar1 >= 1.0f){
            fVar1 = 1.0f;
        }

        fVar1 *= l_HIO.m280;
        fVar1 = cLib_minLimit(fVar1, l_HIO.m284);

        mpMorf->setPlaySpeed(fVar1);
    }


    return 1;
}


/* 00003520-000035A4       .text draw_item__10daNpc_P2_cFP8J3DModelSc */
void daNpc_P2_c::draw_item(J3DModel* i_model_p, signed char i_param_2) {
    g_env_light.setLightTevColorType(i_model_p,&tevStr);
    mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(i_param_2));
    i_model_p->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoExt_modelUpdateDL(i_model_p);
}

/* 000035A4-000035E8       .text drawDagger__10daNpc_P2_cFv */
void daNpc_P2_c::drawDagger() {

    if(m80A != 0){
        draw_item(m2BC,0xC);
    }else{
        draw_item(m2C0,0xE);
    }
    return;
}

/* 000035E8-000036A4       .text drawHead__10daNpc_P2_cFv */
void daNpc_P2_c::drawHead() {
    /* Nonmatching */
    g_env_light.setLightTevColorType(m2B8,&tevStr);
    if(m290 != 2){
        mBtpAnm.entry(m2B8->getModelData(),m378);
        m2B8->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(4));
        mDoExt_modelUpdateDL(m2B8);
        mBtpAnm.remove(m2B8->getModelData());

    }else{
        m2B8->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(4));
        mDoExt_modelUpdateDL(m2B8);
    }

}

/* 000036A4-000037A8       .text drawShadow__10daNpc_P2_cFv */
void daNpc_P2_c::drawShadow() {
    /* Nonmatching */
    cXyz local_18(current.pos.x,current.pos.y + 150.0f + REG8_F(18),current.pos.z);
    mShadowId = dComIfGd_setShadow(mShadowId,1,mpMorf->getModel(),&local_18,REG8_F(19)+800.0f,20.0f,current.pos.y,mAcch.GetGroundH(),mAcch.m_gnd,&tevStr);
    if(mShadowId != 0){
        dComIfGd_addRealShadow(mShadowId,m2B8);
        if(m80A){
            dComIfGd_addRealShadow(mShadowId,m2BC);
        }else{
            dComIfGd_addRealShadow(mShadowId,m2C0);
        }
    }
}

/* 000037A8-00003890       .text drawP2a__10daNpc_P2_cFv */
void daNpc_P2_c::drawP2a() {
    g_env_light.setLightTevColorType(mpMorf->getModel(),&tevStr);
    mpMorf->entryDL();
    drawDagger();
    drawHead();
    if(!dComIfGs_isEventBit(0x808)){
        draw_item(m2C4,0xC);
    }
    drawShadow();
    if(!dComIfGs_isEventBit(0x808) && mShadowId != 0){
        dComIfGd_addRealShadow(mShadowId,m2C4);
    }
    dSnap_RegistFig(0x76,this,1.0f,1.0f,1.0f);
    return;
}


/* 00003890-00003948       .text drawP2b__10daNpc_P2_cFv */
void daNpc_P2_c::drawP2b() {
    g_env_light.setLightTevColorType(mpMorf->getModel(),&tevStr);
    mpMorf->entryDL((J3DMaterialTable*)dComIfG_getObjectRes(m_arc_name,l_bmt_ix_tbl[m290]));
    drawDagger();
    drawHead();
    drawShadow();
    dSnap_RegistFig(0x77,this,1.0f,1.0f,1.0f);
    return;
}

/* 00003948-00003A64       .text drawP2c__10daNpc_P2_cFv */
void daNpc_P2_c::drawP2c() {
    g_env_light.setLightTevColorType(mpMorf->getModel(),&tevStr);
    mpMorf->entryDL((J3DMaterialTable*)dComIfG_getObjectRes(m_arc_name,l_bmt_ix_tbl[m290]));
    drawDagger();
    drawHead();
    g_env_light.setLightTevColorType(mpMorf2->getModel(),&tevStr);
    mpMorf2->getModel()->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(2));
    mpMorf2->updateDL();
    drawShadow();
    if(mShadowId != 0){
        dComIfGd_addRealShadow(mShadowId,mpMorf2->getModel());
    }
    dSnap_RegistFig(0x78,this,1.0f,1.0f,1.0f);
}

/* 00003A64-00003AF0       .text _draw__10daNpc_P2_cFv */
bool daNpc_P2_c::_draw() {
    g_env_light.settingTevStruct(0,&current.pos,&tevStr);
    switch(m290){
        case 0:
            drawP2a();
            break;
        case 1:
            drawP2b();
            break;
        case 2:
            drawP2c();
            break;
    }
    return true;
}

/* 00003AF0-00003B10       .text CreateHeap_CB__FP10fopAc_ac_c */
static BOOL CreateHeap_CB(fopAc_ac_c* i_this) {
    return ((daNpc_P2_c*)i_this)->_createHeap();
}

/* 00003B10-00003B58       .text getArg__10daNpc_P2_cFv */
void daNpc_P2_c::getArg() {
    u32 params = fopAcM_GetParam(this);
    m290 = fopAcM_GetParamBit(params,0,2);
    m291 = fopAcM_GetParamBit(params, 2, 8);
    m292 = fopAcM_GetParamBit(params,10,8);
    if(m290 == 3){
        m290 = 0;
    }
    if(m291 != 0xFF){
        return;
    }
    m291 = 0;
    return;

}

/* 00003B58-00004034       .text _createHeap__10daNpc_P2_cFv */
BOOL daNpc_P2_c::_createHeap() {
    static const u32 head_bdl_tbl[3] = {0x2D,0x2E,0x2F};
    static const u8 head_tex_tbl[2] = {0,1};
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name,0x26);
    JUT_ASSERT(DEMO_SELECT(0x9F2,0x9F1),modelData != 0);
    mpMorf = new mDoExt_McaMorf(modelData,NULL,NULL,NULL,-1,1.0f,0,-1,1,NULL,0x80000,0x15021222);
    if(mpMorf == NULL ||mpMorf->getModel() == NULL){
#if VERSION > VERSION_DEMO
        mpMorf = NULL;
#endif
        return FALSE;
    }else{
        J3DModelData* headModelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name,head_bdl_tbl[m290]);
        JUT_ASSERT(DEMO_SELECT(0xA08,0xA0A),headModelData != 0);
        if(m290 != 2){
            m2B8 = mDoExt_J3DModel__create(headModelData,0x80000,0x11020022);
            if(m2B8 == NULL){
                return FALSE;
            }
            m7D0 = head_tex_tbl[m290];
            if(initTexPatternAnm(false) == 0){
                return FALSE;
            }
        }else{
            m2B8 = mDoExt_J3DModel__create(headModelData,0,0x11020203);
            if(m2B8 == NULL){
                return FALSE;
            }
        }
        J3DModelData* daggerModelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name,0x2A);
        JUT_ASSERT(DEMO_SELECT(0xA25,0xA27), daggerModelData != 0);
        m2BC = mDoExt_J3DModel__create(daggerModelData,0,0x11020203);
        if(m2BC == NULL){
            return FALSE;
        }
        modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name,0x27);
        JUT_ASSERT(DEMO_SELECT(0xA2C,0xA2E), daggerModelData != 0);      
        m2C0 = mDoExt_J3DModel__create(modelData,0,0x11020203);
        if(m2C0 == NULL){
            return FALSE;
        }
        if(m290 == 2){
            J3DModelData* bookModelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name,0x29);
            JUT_ASSERT(DEMO_SELECT(0xA34,0xA36), bookModelData != 0);
            mpMorf2 = new mDoExt_McaMorf(bookModelData,NULL,NULL,
                (J3DAnmTransform*)dComIfG_getObjectRes(m_arc_name,0x23),
                0,1.0f,0,-1,1,NULL,0,0x11020203);
            if(mpMorf2 == NULL ||mpMorf2->getModel() == NULL){
                return FALSE;
            }
        }
        if(m290 == 0){
            J3DModelData* telescopeModelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name,0x28);
            JUT_ASSERT(DEMO_SELECT(0xA47,0xA49), telescopeModelData != 0);
            m2C4 = mDoExt_J3DModel__create(telescopeModelData,0,0x11020203);
            if(m2C4 == NULL){
                return FALSE;
            }
        }
        mpMorf->getModel()->setUserArea((u32)this);
        J3DJointTree& tree = modelData->getJointTree();
        for (u16 i = 0; i < tree.getJointNum(); i += 1) {
            if ((i == 4) || (i == 2)) {
                mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
            }
        }
        return TRUE;
    }
}

// daNpc_P2_c::ActionFunc* introaction;
// daNpc_P2_c::ActionFunc waitaction;
/* 00004034-0000476C       .text createInit__10daNpc_P2_cFv */
void daNpc_P2_c::createInit() {
    /* Nonmatching */
    static char* actor_name_table[] = {"P2a","P2b","P2c"};
    if (m290 == 1 && !strcmp(dComIfGp_getStartStageName(), "Asoko")) {

        fopAcM_OnStatus(this,0x4000);
    }

    mpMorf->calc();
    cullMtx = mpMorf->getModel()->getBaseTRMtx();
    mAcchCir.SetWall(30.0f, 0.0f);
    mAcch.Set(
        &current.pos,
        &old.pos,
        this,
        1,
        &mAcchCir,
        &speed,
        &current.angle,
        &shape_angle);

    attention_info.distances[1] = 0xA9;
    attention_info.distances[3] = 0xA9;

    //
    // Adjust spawn position depending on subtype/event progress.
    //
    if(m290 == 1){
        if (m291 == 0) {

                if (!dComIfGs_isEventBit(0x808) &&
                    dComIfGs_isEventBit(0x720)) {

                    // int idx = m290;
                    current.pos = l_HIO.children[m290].mGoalPosCircleCenter;

                }

        }else if(m291 == 1){

                if (!dComIfGs_isEventBit(0xF02) &&
                    dComIfGs_isEventBit(0x1A04)) {

                    current.pos = l_HIO.children[m290].m3C;
                }
        
        }
    }
    




    
    m6EC = current.angle;

    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    gravity = -9.0f;

    mEventCut.setActorInfo(actor_name_table[m290], this);
    if (m290 == 1) {
        //if(dComIfGs_isEventBit(0x808)){
        //
        // Initial action selection.
        //
    //         if (m290 == 1) {
            if (!strcmp(dComIfGp_getStartStageName(), "Asoko")) {
                if(m291 == 0){

                    if(!dComIfGs_isEventBit(0x808)){
                        ActionFunc action = &daNpc_P2_c::intro_action;
                        if(mActionFunc != action){
                            if(mActionFunc){
                                m808 = -1;
                                (this->*mActionFunc)(NULL);
                            }
                            mActionFunc = action;
                            m808 = 0;
                            (this->*mActionFunc)(NULL);
                        }
                    }else{
                        ActionFunc action = &daNpc_P2_c::wait_action;
                        if(mActionFunc != action){
                            if(mActionFunc){
                                m808 = -1;
                                (this->*mActionFunc)(NULL);
                            }
                            mActionFunc = action;
                            m808 = 0;
                            (this->*mActionFunc)(NULL);
                        }                        

                    }



                }else if(m291 == 1){
                    if(!dComIfGs_isEventBit(0xF02)){
                        ActionFunc action = &daNpc_P2_c::intro_action;
                        if(mActionFunc != action){
                            if(mActionFunc){
                                m808 = -1;
                                (this->*mActionFunc)(NULL);
                            }
                            mActionFunc = action;
                            m808 = 0;
                            (this->*mActionFunc)(NULL);
                        }
                    }else{
                        ActionFunc action = &daNpc_P2_c::wait_action;
                        if(mActionFunc != action){
                            if(mActionFunc){
                                m808 = -1;
                                (this->*mActionFunc)(NULL);
                            }
                            mActionFunc = action;
                            m808 = 0;
                            (this->*mActionFunc)(NULL);
                        }                         
                    }  
                }
            }else{
                ActionFunc action = &daNpc_P2_c::wait_action;
                if(mActionFunc != action){
                    if(mActionFunc){
                        m808 = -1;
                        (this->*mActionFunc)(NULL);
                    }
                    mActionFunc = action;
                    m808 = 0;
                    (this->*mActionFunc)(NULL);
                }               
            }
        }else{
            ActionFunc action = &daNpc_P2_c::wait_action;
            if(mActionFunc != action){
                if(mActionFunc){
                    m808 = -1;
                    (this->*mActionFunc)(NULL);
                }
                mActionFunc = action;
                m808 = 0;
                (this->*mActionFunc)(NULL);
            }          
        }

 
    m704 = current.pos;
    m6F8 = current.pos;

    mStts.Init(0xFF, 0xFF, this);

    m5BC.Set(dNpc_cyl_src);
    m5BC.SetStts(&mStts);

    m7D1 = 1;
    m7D3 = 1;
    m7D4 = 0;

    setTexAnm();
    setAnm();


    if (parentActorID != -1) {
        fopAc_ac_c* actor = (fopAc_ac_c*)fopAcM_SearchByID(parentActorID);
        if(actor && fopAc_IsActor(actor) && actor->base.base.mProcName == 0x3B){
            if(m290 == 0 && !dComIfGs_isEventBit(0x808)){
                m748 = home.angle.y - actor->home.angle.y;
                m_jnt.onHeadLock();
                m_jnt.onBackBoneLock();
            }else if(m290 == 2){
                m748 = home.angle.y - actor->home.angle.y;
            }
        }
    }



    m74C = (s16)(cM_rndF(100.0f) + 200.0f);

    m7DC.setall(0.0f);

}

/* 0000476C-0000492C       .text _create__10daNpc_P2_cFv */
cPhs_State daNpc_P2_c::_create() {
    /* Nonmatching */
    fopAcM_ct_Retail(this, daNpc_P2_c);
    cPhs_State state = dComIfG_resLoad(&mPhs, m_arc_name);


    if (state == cPhs_COMPLEATE_e) {
        getArg();
        if(!fopAcM_entrySolidHeap(this,CreateHeap_CB,m_heapsize[m290])){
            return cPhs_ERROR_e;
        }else{
            createInit();
        }

    }
    return state;
}

/* 00004CDC-00004D54       .text _delete__10daNpc_P2_cFv */
bool daNpc_P2_c::_delete() {
    /* Nonmatching */
    dComIfG_resDelete(&this->mPhs,m_arc_name);
    m754.remove();

#if VERSION == VERSION_DEMO
    if(mpMorf){
        mpMorf->stopZelAnime();
    }
    if(mpMorf2){
        mpMorf2->stopZelAnime();
    }
#else
    mDoAud_seDeleteObject(&m7B0);
    if(heap){
        mpMorf->stopZelAnime();
    }
#endif
    return true;
}

/* 00004D54-00004D74       .text daNpc_P2Create__FPv */
static cPhs_State daNpc_P2Create(void* i_this) {
    return ((daNpc_P2_c*)i_this)->_create();
}

/* 00004D74-00004D98       .text daNpc_P2Delete__FPv */
static BOOL daNpc_P2Delete(void* i_this) {
    return ((daNpc_P2_c*)i_this)->_delete();
}

/* 00004D98-00004DBC       .text daNpc_P2Execute__FPv */
static BOOL daNpc_P2Execute(void* i_this) {
    return ((daNpc_P2_c*)i_this)->_execute();
}

/* 00004DBC-00004DE0       .text daNpc_P2Draw__FPv */
static BOOL daNpc_P2Draw(void* i_this) {
    return ((daNpc_P2_c*)i_this)->_draw();
}

/* 00004DE0-00004DE8       .text daNpc_P2IsDelete__FPv */
static BOOL daNpc_P2IsDelete(void*) {
    return TRUE;
}

/* 00005238-00005528       .text cutProc__10daNpc_P2_cFv */
void daNpc_P2_c::cutProc() {
    /* Nonmatching */

  int iVar1;
  int staffIdx = dComIfGp_evmng_getMyStaffId("P2b");
  if (staffIdx == -1) {
    m7D7 = 0;
  }
  else {
    iVar1 = dComIfGp_evmng_getMyActIdx(staffIdx,action_table,0xF,1,0);
    if ( iVar1 == -1) {
      m7D7 = 0;
      dComIfGp_evmng_cutEnd(staffIdx);
    }
    else {
      m7D7 = 1;
      if (dComIfGp_evmng_getIsAddvance(staffIdx)) {
        m72C = 0;
        switch(iVar1) {
        case 0:
          cutTalkStart(staffIdx);
          break;
        case 1:
          cutRideSwitchStart(staffIdx);
          break;
        case 2:
          cutRunWaitStart(staffIdx);
          break;
        case 3:
          cutJumpToLiftStart(staffIdx);
          break;
        case 4:
          cutLiftToRopeStart(staffIdx);
          break;
        case 5:
          cutRopeTalkStart(staffIdx);
          break;
        case 6:
          cutRopeToLiftStart(staffIdx);
          break;
        case 7:
          cutJumpToGoalStart(staffIdx);
          break;
        case 8:
          cutSetAnmStart(staffIdx);
          break;
        case 9:
          cutJumpStart(staffIdx);
          break;
        case 10:
          cutSwOnStart(staffIdx);
          break;
        case 0xb:
          cutSwOffStart(staffIdx);
          break;
        case 0xc:
          cutSurpriseStart(staffIdx);
          break;
        case 0xd:
          cutOmamoriInitStart(staffIdx);
          break;
        case 0xe:
          cutOmamoriEndStart(staffIdx);
        }
      }
      switch(iVar1) {
      case 0:
        cutTalkProc(staffIdx);
        break;
      case 1:
        cutRideSwitchProc(staffIdx);
        break;
      case 2:
        cutRunWaitProc(staffIdx);
        break;
      case 3:
        cutJumpToLiftProc(staffIdx);
        break;
      case 4:
        cutLiftToRopeProc(staffIdx);
        break;
      case 5:
        cutRopeTalkProc(staffIdx);
        break;
      case 6:
        cutRopeToLiftProc(staffIdx);
        break;
      case 7:
        cutJumpToGoalProc(staffIdx);
        break;
      case 8:
        cutSetAnmProc(staffIdx);
        break;
      case 9:
        cutJumpProc(staffIdx);
        break;
      case 10:
        cutSwOnProc(staffIdx);
        break;
      case 0xb:
        cutSwOffProc(staffIdx);
        break;
      case 0xc:
        cutSurpriseProc(staffIdx);
        break;
      case 0xd:
        cutOmamoriInitProc(staffIdx);
        break;
      case 0xe:
        cutOmamoriEndProc(staffIdx);
      }
    }
  }
  return;

}

/* 00005528-000055DC       .text cutTalkStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutTalkStart(int i_param_1) {
    /* Nonmatching */
    int* puVar1 = dComIfGp_evmng_getMyIntegerP(i_param_1,"MsgNum");
    if(puVar1 == NULL){
        m728 = 0;
    }else{
        m728 = *puVar1;
    }
    int* puVar2 = dComIfGp_evmng_getMyIntegerP(i_param_1,"Attention");
    if(puVar2 == NULL){
        m72C = 0;
    }else{
        m72C = 1;
    }
    talkInit();
    return;
}

/* 000055DC-0000562C       .text cutTalkProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutTalkProc(int i_param_1) {
    /* Nonmatching */
    if(talk(true) == 0x12){
        dComIfGp_evmng_cutEnd(i_param_1);
    }
    return;
}

/* 0000562C-000056F4       .text cutRideSwitchStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutRideSwitchStart(int i_param_1) {
    /* Nonmatching */
    f32* pfVar1 = dComIfGp_evmng_getMyFloatP(i_param_1,"Speed_y");
    f32* pfVar2 = dComIfGp_evmng_getMyFloatP(i_param_1,"Gravity");

    if(pfVar1 == NULL){
        speed.y = 16.0f;
    }else{
        speed.y = *pfVar1;
    }
    if(pfVar2 == NULL){
        gravity = -2.0f;
    }else{
        gravity = *pfVar2;
    }
    m72C = 1;
    m7D3 = 9;
    return;
}

/* 000056F4-0000589C       .text cutRideSwitchProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutRideSwitchProc(int i_param_1) {
    /* Nonmatching */
    //fopAcM_searchPlayerAngleY(fopAcM_SearchByName(m_arc_name));


}

/* 0000589C-00005914       .text cutRunWaitStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutRunWaitStart(int) {
    /* Nonmatching */
}

/* 00005914-000059B0       .text cutRunWaitProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutRunWaitProc(int) {
    /* Nonmatching */
}

/* 000059B0-00005BD0       .text searchNearLift__10daNpc_P2_cFPvPv */
void daNpc_P2_c::searchNearLift(void*, void*) {
    /* Nonmatching */
}

/* 00005BD0-00005CD4       .text cutJumpToLiftStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutJumpToLiftStart(int) {
    /* Nonmatching */
}

/* 00005CD4-00006064       .text cutJumpToLiftProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutJumpToLiftProc(int) {
    /* Nonmatching */
}

/* 00006064-00006284       .text searchNearRope__10daNpc_P2_cFPvPv */
void daNpc_P2_c::searchNearRope(void*, void*) {
    /* Nonmatching */
}

/* 00006284-00006388       .text cutLiftToRopeStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutLiftToRopeStart(int) {
    /* Nonmatching */
}

/* 00006388-000065B8       .text cutLiftToRopeProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutLiftToRopeProc(int) {
    /* Nonmatching */
}

/* 000065B8-00006B08       .text cutRopeTalkStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutRopeTalkStart(int) {
    /* Nonmatching */
}

/* 00006B08-00007314       .text cutRopeTalkProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutRopeTalkProc(int) {
    /* Nonmatching */
}

/* 00007314-0000743C       .text cutRopeToLiftStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutRopeToLiftStart(int) {
    /* Nonmatching */
}

/* 0000743C-00007694       .text cutRopeToLiftProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutRopeToLiftProc(int) {
    /* Nonmatching */
}

/* 00007694-00007808       .text cutJumpToGoalStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutJumpToGoalStart(int) {
    /* Nonmatching */
}

/* 00007808-00007B3C       .text cutJumpToGoalProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutJumpToGoalProc(int) {
    /* Nonmatching */
}

/* 00007B3C-00007D08       .text cutJumpStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutJumpStart(int) {
    /* Nonmatching */
}

/* 00007D08-00007F70       .text cutJumpProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutJumpProc(int) {
    /* Nonmatching */
}

/* 00007F70-000080B4       .text cutSetAnmStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutSetAnmStart(int) {
    /* Nonmatching */
}

/* 000080B4-00008114       .text cutSetAnmProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutSetAnmProc(int) {
    /* Nonmatching */
}

/* 00008114-00008154       .text cutSwOnStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutSwOnStart(int) {
    /* Nonmatching */
}

/* 00008154-000081B4       .text cutSwOnProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutSwOnProc(int) {
    /* Nonmatching */
}

/* 000081B4-000081F4       .text cutSwOffStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutSwOffStart(int) {
    /* Nonmatching */
}

/* 000081F4-00008254       .text cutSwOffProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutSwOffProc(int) {
    /* Nonmatching */
}

/* 00008254-000082CC       .text cutSurpriseStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutSurpriseStart(int) {
    /* Nonmatching */
}

/* 000082CC-000082F8       .text cutSurpriseProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutSurpriseProc(int) {
    /* Nonmatching */
}

/* 000082F8-00008350       .text cutOmamoriInitStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutOmamoriInitStart(int) {
    /* Nonmatching */
}

/* 00008350-0000837C       .text cutOmamoriInitProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutOmamoriInitProc(int) {
    /* Nonmatching */
}

/* 0000837C-000083D4       .text cutOmamoriEndStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutOmamoriEndStart(int) {
    /* Nonmatching */
}

/* 000083D4-00008400       .text cutOmamoriEndProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutOmamoriEndProc(int) {
    /* Nonmatching */
}

static actor_method_class daNpc_P2MethodTable = {
    (process_method_func)daNpc_P2Create,
    (process_method_func)daNpc_P2Delete,
    (process_method_func)daNpc_P2Execute,
    (process_method_func)daNpc_P2IsDelete,
    (process_method_func)daNpc_P2Draw,
};

actor_process_profile_definition g_profile_NPC_P2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_P2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_P2_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_P2_e,
    /* Actor SubMtd */ &daNpc_P2MethodTable,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_FREEZE_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
