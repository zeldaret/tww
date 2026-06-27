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
    f32 m74;
    f32 m78;
    f32 m7C;
    f32 m80;
    f32 m84;
    f32 m88;
    f32 m8C;
    f32 m90;
    f32 m94;
    f32 m98;
    f32 m9C;
    f32 mA0;
    f32 mA4;
    f32 mA8;
    f32 mAC;
    f32 mB0;
    f32 mB4;
    f32 mB8;
    f32 mBC;
    f32 mC0;
    f32 mC4;
    f32 mC8;
    f32 mCC;
    f32 mD0;
    //SIZE: 0xD4 ?????
};

class daNpc_P2_HIO_c: mDoHIO_entry_c{
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
    m74 = 0.0f;
    m78 = 14.0f;
    m7C = 8.0f;
    m80 = 8.0f;
    m84 = 4.0f;
    m88 = 0;
    m8C = 4.0f;
    m90 = 8.0f;
    m94 = 6.0f;
    m98 = 6.0f;
    m9C = 2.0f;
    mA0 = 20.0f;
    mA4 = 20.0f;
    mA8 = 8.0f;
    mAC = 12.0f;
    mB0 = 8.0f;
    mB4 = 4.0f;
    mB8 = 8.0f;
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
                mDoMtx_stack_c::multVec(&l_offsetAttPos, &i_this->getAttentionBasePos());
                if(i_this->m714 == 0){
                    i_this->m714 += 1;
                }

            }else if(jointNo == 0x2){
                mDoMtx_stack_c::XrotM(*((s16*)(i_this)+0x169));
                mDoMtx_stack_c::ZrotM(*((s16*)(i_this)+0x168));
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
const u32 l_btp_ix_tbl[] = {36,37};
/* 0000068C-00000788       .text initTexPatternAnm__10daNpc_P2_cFb */
bool daNpc_P2_c::initTexPatternAnm(bool i_param_1) {
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
    /* Nonmatching */
}

/* 00000810-00000A90       .text setAnm__10daNpc_P2_cFv */
void daNpc_P2_c::setAnm() {
    /* Nonmatching */
}

/* 00000A90-00000AFC       .text setTexAnm__10daNpc_P2_cFv */
void daNpc_P2_c::setTexAnm() {
    /* Nonmatching */
}

/* 00000AFC-00000B90       .text setAttention__10daNpc_P2_cFv */
void daNpc_P2_c::setAttention() {
    /* Nonmatching */
}

/* 00000B90-00000CEC       .text chkAttention__10daNpc_P2_cFv */
bool daNpc_P2_c::chkAttention() {
    /* Nonmatching */
}

/* 00000CEC-000010E8       .text lookBack__10daNpc_P2_cFv */
void daNpc_P2_c::lookBack() {
    /* Nonmatching */
}

/* 000010E8-00001160       .text setMtx__10daNpc_P2_cFv */
void daNpc_P2_c::setMtx() {
    /* Nonmatching */
}

/* 00001160-00001204       .text setCollision__10daNpc_P2_cFv */
void daNpc_P2_c::setCollision() {
    /* Nonmatching */
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
u16 daNpc_P2_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00001534-000016CC       .text getMsg__10daNpc_P2_cFv */
u32 daNpc_P2_c::getMsg() {
    /* Nonmatching */
}

/* 000016CC-000016D8       .text talkInit__10daNpc_P2_cFv */
void daNpc_P2_c::talkInit() {
    /* Nonmatching */
    m809 = 0;
    return;
}

/* 000016D8-000017AC       .text anmAtr__10daNpc_P2_cFUs */
void daNpc_P2_c::anmAtr(unsigned short) {
    /* Nonmatching */
}

/* 000017AC-00001918       .text talk__10daNpc_P2_cFb */
u16 daNpc_P2_c::talk(bool) {
    /* Nonmatching */
}

/* 00001918-00001998       .text eventOrder__10daNpc_P2_cFv */
void daNpc_P2_c::eventOrder() {
    /* Nonmatching */
}

/* 00001998-00001A00       .text checkOrder__10daNpc_P2_cFv */
void daNpc_P2_c::checkOrder() {
    /* Nonmatching */
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
    if(dComIfGp_evmng_endCheck("PB2_GOAL_2")){
        m7D6 = 0xD;
        m7D5 = 0;
        m7C1 = 1;

        m73C = m7DC + mEventCut.getAttnPos(); 
        dComIfGp_event_onEventFlag(0x8);
    }else{
        m7D5 = 9;
    }
    return;
}

/* 00001C74-00001CFC       .text demo_bomb_get__10daNpc_P2_cFv */
void daNpc_P2_c::demo_bomb_get() {
    /* Nonmatching */
    if(dComIfGp_evmng_endCheck("PB2_BOMB_GET")){
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
    daPy_py_c* player = daPy_getPlayerActorClass();
    if((current.pos.y - player->current.pos.y - 300.f) > 0.0f){
        m7D6 = 0x9;
        return;
    }
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x0;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x0; 
    static cXyz aim_pos(0.0f,-450.0f,-2915.0f);
    static cXyz attn_pos(0.0f,-450.0f,-2715.0f);
    s16 sVar5 = cLib_targetAngleY(&current.pos,&aim_pos);
    m730 = attn_pos;
    f32 fVar8;
    if(std::fabsf(sVar5 - current.angle.y) < 5376.0f){
        m7D3 = 0x4;
        cLib_addCalc2(&current.pos.x,aim_pos.x,0.1,4.0);
        cLib_addCalc2(&current.pos.z,aim_pos.z,0.1,4.0);
        fVar8 = (aim_pos - current.pos).absXZ();
        if(fVar8 < 5376.0f){
            m7D3 = 0x1;
            m7D6 = 0x7;
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

/* 000021C4-000025B8       .text goal_talkpos_to_goalpos__10daNpc_P2_cFv */
void daNpc_P2_c::goal_talkpos_to_goalpos() {
    /* Nonmatching */
    m7C1 = 1;
    daPy_py_c* player = daPy_getPlayerActorClass();
    if(
        fopAcM_searchActorDistanceXZ(this,player) < l_HIO.children[m290].m70 && 
        (current.pos.y - player->current.pos.y - 300.f) > 0.0f
    ){
        m7D6 = 0x9;
        return;
    }
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x0;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x0; 
    static cXyz aim_pos(0.0f,-450.0f,-3130.0f);
    static cXyz attn_pos(0.0f,-450.0f,-3380.0f);
    static cXyz talk_attn_pos(0.0f,-450.0f,-2715.0f);
    

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
    daPy_py_c* player = daPy_getPlayerActorClass();
    if(
        fopAcM_searchActorDistanceXZ(this,player) < l_HIO.children[m290].m70 && 
        (current.pos.y - player->current.pos.y - 300.f) > 0.0f
    ){
        m7D6 = 0x9;
        return;
    }
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0x2;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0x2;   
    if(dLib_checkPlayerInCircle(l_HIO.children[m290].mGoalPosCircleCenter,l_HIO.children[m290].mGoalPosCircleRadius,l_HIO.children[m290].mGoalPosCircleHalfHeight) && !player->checkPlayerFly()){
        m7D6 = 0xC;
        daObjTimer::Act_c* timer = (daObjTimer::Act_c*)fopAcM_SearchByName(fpcNm_Obj_Timer_e);
        if(timer){
            timer->stopTimer();
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
        if(m725 == 0){
            m7D6 = 0x8;
            dComIfGp_event_onEventFlag(0x8);
            m7D5 = 0x5;
        }else{
            if(fopAcM_GetSpeedF(this) < 1.0f){
                m7D5 = 2;
            }
        }

        if(dLib_checkPlayerInCircle(l_HIO.children[m290].mDemoCircleCenter,l_HIO.children[m290].mDemoCircleRadius,l_HIO.children[m290].mDemoCircleHalfHeight) && !player->checkPlayerFly()){
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

    if (m725 == 0) {
        m7D5 = 2;
    } else {
        m7D3 = 1;
        m_jnt.offHeadLock();
        m_jnt.offBackBoneLock();
        m7D6 = 2;
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

    if (m725 == 0 || m7D3 != 1) {
        m7D5 = 2;
    } else {
        m7D6 = 2;
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
            if(dComIfGs_isEventBit(0x1A04)){
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
    if(m808){
        if(m290 == 2){
            m7D6 = 0x10;
        }else if(m290 == 0 && dComIfGs_isEventBit(0x808)){
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
bool daNpc_P2_c::_execute() {
    /* Nonmatching */
    // if(mLoaded == 0){
    //     m834 = current.pos;
    //     mRotTarget = current.angle;
    //     mLoaded = 1;
    // }



        //l_HIO.children[mSubType-1].hio_prm.mMaxTurnStep
        //m_jnt.setParam(0,0,0,0,0x2000,0x38E0,-0x2000,-0x38E0,0);

            // m_jnt.setParam(l_HIO.children[mSubType-1].hio_prm.mMaxBackboneX,l_HIO.children[mSubType-1].hio_prm.mMaxBackboneY,
            // l_HIO.children[mSubType-1].hio_prm.mMinBackboneX,l_HIO.children[mSubType-1].hio_prm.mMinBackboneY,
            // l_HIO.children[mSubType-1].hio_prm.mMaxHeadX,l_HIO.children[mSubType-1].hio_prm.mMaxHeadY,
            // l_HIO.children[mSubType-1].hio_prm.mMinHeadX,l_HIO.children[mSubType-1].hio_prm.mMinHeadY,l_HIO.children[mSubType-1].hio_prm.mMaxTurnStep);


    if(1 && demoActorID == 0){
        return TRUE;
    }

    // checkOrder();
    // if(!demo()){
    //     int iVar4 = -1;
    //     if(dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk() != false){
    //         iVar4 = isEventEntry();   
    //     }
    //     if(iVar4 >= 0){
    //         event_proc(iVar4);
    //     }else{
    //         (this->*mCurrActionFunc)(0);
    //     }
    //     lookBack();
    //     if(mStaff != 1){
    //         fopAcM_posMoveF(this,mStts.GetCCMoveP());
    //         mObjAcch.CrrPos(*dComIfG_Bgsp());
    //     }
    //     play_animation();
    // }else{
    //     m89E = 0;
    // }
    // eventOrder();
    // m846 = current.angle;
    // if(!m89F){
    //     shape_angle = current.angle;
    // }
    // tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    // tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    // setMtx(false);
    // set_cutGrass();
    // if(mStaff == 0){
    //     dComIfG_Ccsp()->SetMassAreaChk(&mCyl704,3,area_check);
    // }
    // if(m8A6 == 0){
    //     set_collision_sp();
    // }
    return TRUE;
}

/* 00003520-000035A4       .text draw_item__10daNpc_P2_cFP8J3DModelSc */
void daNpc_P2_c::draw_item(J3DModel*, signed char) {
    /* Nonmatching */
}

/* 000035A4-000035E8       .text drawDagger__10daNpc_P2_cFv */
void daNpc_P2_c::drawDagger() {
    /* Nonmatching */
    if(m80A == 0){
        draw_item(m2C0,0xE);
    }else{
        draw_item(m2BC,0xC);
    }
    return;
}

/* 000035E8-000036A4       .text drawHead__10daNpc_P2_cFv */
void daNpc_P2_c::drawHead() {
    /* Nonmatching */
}

/* 000036A4-000037A8       .text drawShadow__10daNpc_P2_cFv */
void daNpc_P2_c::drawShadow() {
    /* Nonmatching */
}

/* 000037A8-00003890       .text drawP2a__10daNpc_P2_cFv */
void daNpc_P2_c::drawP2a() {
    /* Nonmatching */
}

/* 00003890-00003948       .text drawP2b__10daNpc_P2_cFv */
void daNpc_P2_c::drawP2b() {
    /* Nonmatching */
}

/* 00003948-00003A64       .text drawP2c__10daNpc_P2_cFv */
void daNpc_P2_c::drawP2c() {
    /* Nonmatching */
}

/* 00003A64-00003AF0       .text _draw__10daNpc_P2_cFv */
bool daNpc_P2_c::_draw() {
    /* Nonmatching */
}

/* 00003AF0-00003B10       .text CreateHeap_CB__FP10fopAc_ac_c */
static BOOL CreateHeap_CB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00003B10-00003B58       .text getArg__10daNpc_P2_cFv */
void daNpc_P2_c::getArg() {
    /* Nonmatching */
}

/* 00003B58-00004034       .text _createHeap__10daNpc_P2_cFv */
void daNpc_P2_c::_createHeap() {
    /* Nonmatching */
}

/* 00004034-0000476C       .text createInit__10daNpc_P2_cFv */
void daNpc_P2_c::createInit() {
    /* Nonmatching */
}

/* 0000476C-0000492C       .text _create__10daNpc_P2_cFv */
cPhs_State daNpc_P2_c::_create() {
    /* Nonmatching */
    dBgS_Acch();
}

/* 00004CDC-00004D54       .text _delete__10daNpc_P2_cFv */
bool daNpc_P2_c::_delete() {
    /* Nonmatching */
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
}

/* 00005528-000055DC       .text cutTalkStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutTalkStart(int) {
    /* Nonmatching */
}

/* 000055DC-0000562C       .text cutTalkProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutTalkProc(int) {
    /* Nonmatching */
}

/* 0000562C-000056F4       .text cutRideSwitchStart__10daNpc_P2_cFi */
void daNpc_P2_c::cutRideSwitchStart(int) {
    /* Nonmatching */
}

/* 000056F4-0000589C       .text cutRideSwitchProc__10daNpc_P2_cFi */
void daNpc_P2_c::cutRideSwitchProc(int) {
    /* Nonmatching */
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
