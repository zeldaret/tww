/**
 * d_a_npc_kf1.cpp
 * NPC - Mila's Father (rich)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kf1.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_tsubo.h"
#include "d/d_a_obj.h"
#include "d/d_snap.h"

class daNpc_Kf1_HIO_c : public mDoHIO_entry_c{
    struct hio_prm_c{
        s16 m0;
        s16 m2;
        s16 m4;
        s16 m6;
        s16 m8;
        s16 mA;
        s16 mC;
        s16 mE;
        s16 m10;
        s16 m12;
        f32 m14;
        s16 m18;
        s16 m1A;
        s16 m1C;
        s16 m1E;
        f32 m20;
        f32 m24;
        f32 m28;
        f32 m2C;
    }; //Size: 0x30
public:
    daNpc_Kf1_HIO_c();
    virtual ~daNpc_Kf1_HIO_c(){};
public:
    /* 0x0 */ s8 m0;
    /* 0x4 */ s32 m4;
    /* 0x8 */ hio_prm_c m8;

};


/* 000000EC-00000150       .text __ct__15daNpc_Kf1_HIO_cFv */
daNpc_Kf1_HIO_c::daNpc_Kf1_HIO_c() {

    static daNpc_Kf1_HIO_c::hio_prm_c a_prm_tbl = {
        0x2000,
        0x07D0,
        0xFC18,
        0xF830,
        0x0000,
        0x1388,
        0xF060,
        0xEC78,
        0x05DC,
        0x04B0,
        200.0f,
        0x0000,
        0x000A,
        0x0400,
        0x0000,
        0.5f,
        2.0f,
        0.20f,
        8.0f,
    };
    memcpy(&m8,&a_prm_tbl,0x30);
    m0 = -1;
    m4 = -1;
}

static daNpc_Kf1_HIO_c l_HIO;
static char* l_evn_tbl[3] = {"angry","rupee_age","bensyou"};
/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode* i_node, int i_param2) {

    if(!i_param2){
        if(j3dSys.getModel()->getUserArea()){
            reinterpret_cast<daNpc_Kf1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_Head(i_node,j3dSys.getModel());
        }
    }   
    return TRUE;
}
static fopAc_ac_c* l_check_inf[0x14];
static s32 l_check_wrk;
/* 000001E4-000002D8       .text _nodeCB_Head__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_pModel) {

    static cXyz a_eye_pos_off(30.0f,30.0f,0.0f);
    int jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_multVecZero(mDoMtx_stack_c::get(),&m754);
    mDoMtx_stack_c::multVec(&a_eye_pos_off,&m730);
    mDoMtx_copy(mDoMtx_stack_c::get(),J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx,mDoMtx_stack_c::get());
}

/* 00000314-00000360       .text nodeCB_Neck__FP7J3DNodei */
static BOOL nodeCB_Neck(J3DNode* i_node, int i_param2) {

    if(!i_param2){
        if(j3dSys.getModel()->getUserArea()){
            reinterpret_cast<daNpc_Kf1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_Neck(i_node,j3dSys.getModel());
        }
    }   
    return TRUE;
}

/* 00000360-00000400       .text _nodeCB_Neck__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Neck(J3DNode* i_node, J3DModel* i_pModel) {

    int jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    mDoMtx_copy(mDoMtx_stack_c::get(),J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx,mDoMtx_stack_c::get());
}

/* 00000400-0000044C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode* i_node, int i_param2) {

    if(!i_param2){
        if(j3dSys.getModel()->getUserArea()){
            reinterpret_cast<daNpc_Kf1_c*>(j3dSys.getModel()->getUserArea())->_nodeCB_BackBone(i_node,j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 0000044C-000004EC       .text _nodeCB_BackBone__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_pModel) {

    int jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    mDoMtx_copy(mDoMtx_stack_c::get(),J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx,mDoMtx_stack_c::get());
}

/* 000004EC-0000050C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {

    return ((daNpc_Kf1_c*)i_this)->CreateHeap();
}


/* 0000050C-0000059C       .text searchActor_Tsubo__FPvPv */
void* searchActor_Tsubo(void* i_actorP, void*) {

    if (
        l_check_wrk < ARRAY_SSIZE(l_check_inf) && 
        fopAc_IsActor(i_actorP) && 
        fpcM_GetName(i_actorP) == fpcNm_TSUBO_e &&
        daObj::PrmAbstract((fopAc_ac_c*)i_actorP,4,0x18) == 0xE
    ) {
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_actorP;
        l_check_wrk++;
    }
    return NULL;
}

/* 0000059C-0000061C       .text init_KF1_0__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::init_KF1_0() {

    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)){
        set_action(&daNpc_Kf1_c::wait_action1,NULL);
        return TRUE;
    }
    return FALSE;
}


/* 0000061C-0000083C       .text createInit__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::createInit() {

    for(int i = 0; i < 3; i++){
        m780[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }
    mEventCut.setActorInfo2("Kf1",this);
    m79F = fopAcM_GetParamBit(fopAcM_GetParam(this),8,8);
    s32 iVar6 = 0xFF;
    s32 param = fopAcM_GetParam(this);
    if(fopAcM_GetParamBit(param,0x10,8) != 0xFF){
        mPathRun.setInf(fopAcM_GetParamBit(param,0x10,8),fopAcM_GetRoomNo(this),true);
        if(mPathRun.getPath()){
            fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);
            iVar6 = 0xD9;
            set_pthPoint(0);
        }else{
            return FALSE;
        }
    }
    if(mPathRun.isPath() == 0){
        return FALSE;

    }
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    switch(m7FC){
        case 0:
            break;
    }

    attention_info.distances[1] = 0xAB;
    attention_info.distances[3] = 0xAB;
    gravity = -4.5f;
    m7F6 = 0xA;
    bool cVar4;
    switch(m7FC){
        case 0:
            cVar4 = init_KF1_0();
            break;
        default:
            cVar4 = 0;
            break;
    }

    if(cVar4 == 0){
        return FALSE;
    }
    m722 = current.angle;
    shape_angle = m722;
    mStts.Init(iVar6,0xFF,this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mObjAcch.CrrPos(*dComIfG_Bgsp());
    play_animation();
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mpMorf->setMorf(0.0f);
    setMtx(true);
    return TRUE;
}

/* 0000083C-000008E4       .text play_animation__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::play_animation() {

    u32 uVar3 = 0;
    play_btp_anm();
    if(mObjAcch.ChkGroundHit()){
        uVar3 = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    }
    m79C = mpMorf->play(&eyePos,uVar3,dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    if(mpMorf->getFrame() < m76C){
        m79C = 1;
    }
    m76C = mpMorf->getFrame();
}

/* 000008E4-00000A20       .text setMtx__11daNpc_Kf1_cFb */
void daNpc_Kf1_c::setMtx(bool i_param1) {

    J3DModel* model = mpMorf->getModel();
    model->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(m722);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    if(m6D0){
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
        mDoMtx_stack_c::transM(33.87f,3.26f,0.0f);
        mDoMtx_stack_c::XYZrotM(-0x4000,-0x4000,0);
        m6D0->setBaseTRMtx(mDoMtx_stack_c::get());
        m6D0->calc();
    }
    setAttention(i_param1);
}

/* 00000A20-00000A34       .text bckResID__11daNpc_Kf1_cFi */
s32 daNpc_Kf1_c::bckResID(int i_idx) {

    static const u32 a_resID_tbl[0xA] = {0xA,0xC,0x6,0x7,0x8,0x9,0x5,0x3,0x4,0xB};
    return a_resID_tbl[i_idx];
}

/* 00000A34-00000A48       .text btpResID__11daNpc_Kf1_cFi */
s32 daNpc_Kf1_c::btpResID(int i_idx) {

    static const u32 a_resID_tbl[0x2] = {0x2,0xD};
    return a_resID_tbl[i_idx];
}

/* 00000A48-00000B4C       .text setBtp__11daNpc_Kf1_cFScb */
bool daNpc_Kf1_c::setBtp(signed char i_param1, bool i_param2) {

    J3DModel* a_model = mpMorf->getModel();
    if(i_param1 < 0){
        return FALSE;
    }

    u32 uVar4 = btpResID(i_param1);
    J3DAnmTexPattern* a_btp = (J3DAnmTexPattern*)dComIfG_getObjectIDRes(mArcName,(int)uVar4);
    JUT_ASSERT(DEMO_SELECT(0x20A,0x20A),a_btp != NULL);
    m7F5 = i_param1;
    m6F0 = 0;
    m6F2 = 0;
    return m6DC.init(a_model->getModelData(),a_btp,1,0,1.0f,0,-1,i_param2,0) ? true : false;
}

/* 00000B4C-00000B6C       .text init_texPttrnAnm__11daNpc_Kf1_cFScb */
bool daNpc_Kf1_c::init_texPttrnAnm(signed char i_param1, bool i_param2) {

    return setBtp(i_param1,i_param2);
}

/* 00000B6C-00000C08       .text play_btp_anm__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::play_btp_anm() {

    u8 uVar1 = m6DC.getBtpAnm()->getFrameMax();
    if(m7F5 != 0 || !cLib_calcTimer(&m6F2)){
        m6F0 += 1;
        if(m6F0 >= uVar1){
            if(m7F5 != 0){
                m6F0 = uVar1;

            }else{
                m6F2 = cLib_getRndValue(0x3C,0x5A);
                m6F0 = 0;
            }
        }
    }
}

/* 00000C08-00000CA4       .text setAnm_anm__11daNpc_Kf1_cFPQ211daNpc_Kf1_c9anm_prm_c */
void daNpc_Kf1_c::setAnm_anm(daNpc_Kf1_c::anm_prm_c* i_param_1) {

    if(i_param_1->m0 < 0 || m7F6 == i_param_1->m0){
        return;
    }
    u32 uVar2 = bckResID(i_param_1->m0);
    dNpc_setAnmIDRes(mpMorf,i_param_1->mC,i_param_1->m4,i_param_1->m8,uVar2,-1,mArcName);
    m7F6 = i_param_1->m0;
    m79C = 0;
    m79D = 0;
    m76C = 0; 
        
    
}

/* 00000CA4-00000D14       .text setAnm_NUM__11daNpc_Kf1_cFii */
void daNpc_Kf1_c::setAnm_NUM(int i_param1, int i_param2) {

    static anm_prm_c a_anm_prm_tbl[0xA] = {
        0,0,15.0,1.0,2,
        1,1,8.0,1.0,2,
        2,0,8.0,1.0,2,
        3,0,8.0,1.0,2,
        4,0,8.0,1.0,2,
        5,0,8.0,1.0,2,
        6,0,8.0,1.0,2,
        7,0,8.0,1.0,0,
        8,0,8.0,1.0,0,
        9,1,8.0,1.0,2,
    };
    if(i_param2 != 0){
        init_texPttrnAnm(a_anm_prm_tbl[i_param1].m1,true);
    }
    setAnm_anm(&a_anm_prm_tbl[i_param1]);
}

/* 00000D14-00000D80       .text setAnm__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::setAnm() {

    static anm_prm_c a_anm_prm_tbl[0x4] = {
        -1,-1,0,0,-1,
        -1,-1,0,0,-1,
        -1,-1,0,0,-1,
        1,1,8.0f,1.0,2,
    };

        init_texPttrnAnm(a_anm_prm_tbl[m7F8].m1,true);
    
    setAnm_anm(&a_anm_prm_tbl[m7F8]);
}

/* 00000D80-00000D84       .text chngAnmTag__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::chngAnmTag() {

}

/* 00000D84-00000D88       .text ctrlAnmTag__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::ctrlAnmTag() {

}

/* 00000D88-00000DEC       .text chngAnmAtr__11daNpc_Kf1_cFUc */
void daNpc_Kf1_c::chngAnmAtr(unsigned char i_param1) {

    switch(mCurrMsgNo){
        case 0x1C2E:
            dComIfGp_event_offHindFlag(0x80);
            break;
    }

    if(i_param1 == m7F3 || i_param1 > 0xB){
        return;
    }
    m7F3 = i_param1;
    setAnm_ATR();
}

/* 00000DEC-00000E60       .text ctrlAnmAtr__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::ctrlAnmAtr() {

        switch (m7F3) {
            break;
        case 7:
        case 9:
            if (m79C) {
                setAnm_NUM(0, 1);
                m7F3 = 0;
            }
            break;
        case 10:
            return;
        case 5:
        case 6:
            break;
        }
}

/* 00000E60-00000EC4       .text setAnm_ATR__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::setAnm_ATR() {

    static anm_prm_c a_anm_prm_tbl[0xB] = {
        0,0,15.0f,1.0f,2,
        1,1,8.0f,1.0f,2,
        2,0,8.0f,1.0f,2,
        3,0,8.0f,1.0f,2,
        4,0,8.0f,1.0f,2,
        5,0,8.0f,1.0f,2,
        6,0,8.0f,1.0f,2,
        7,0,8.0f,1.0f,0,
        8,0,8.0f,1.0f,0,
        3,0,8.0f,1.0f,2,
        9,1,8.0f,1.0f,2,
    };
    init_texPttrnAnm(a_anm_prm_tbl[m7F3].m1,true);
    setAnm_anm(&a_anm_prm_tbl[m7F3]);
}

/* 00000EC4-00000F80       .text anmAtr__11daNpc_Kf1_cFUs */
void daNpc_Kf1_c::anmAtr(unsigned short i_param_1) {

    u8 taginfo;
    switch(i_param_1){

        case 0x6:
            if(m7FE == 0){
                chngAnmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m7FE += 1;
            }
            taginfo = dComIfGp_getMesgAnimeTagInfo();
            if(taginfo != 0xFF && taginfo != m7F4){
                dComIfGp_setMesgAnimeTagInfo(0xFF);
                m7F4 = taginfo;
                chngAnmTag();
            }
            break;
        case 0xE:
            m7FE = 0;
            break;
    }
    ctrlAnmAtr();
    ctrlAnmTag();

}

/* 00000F80-000010F4       .text next_msgStatus__11daNpc_Kf1_cFPUl */
u16 daNpc_Kf1_c::next_msgStatus(unsigned long* i_param1) {

    u16 uVar2 = 0xF;
    switch(*i_param1){


        case 0x1C23:
            switch(mpCurrMsg->mSelectNum){
                case 0:
                    *i_param1 = 0x1C24;
                    break;
                case 1:
                    *i_param1 = 0x1C25;
                    break;
            }
            break;




        case 0x1C28:
            switch(mpCurrMsg->mSelectNum){
                case 0:
                    *i_param1 = 0x1C2A;
                    break;
                case 1:
                    *i_param1 = 0x1C29;
                    break;
            }
            break;
        case 0x1C24:
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B02);
            uVar2 = 0x10;
            break;
        case 0x1C2B:
            m7A0 = 1;
            uVar2 = 0x10;
            break;
        case 0x1C21:
            *i_param1 = 0x1C22;
            break;
        case 0x1C22:
            *i_param1 = 0x1C34;
            break;
        case 0x1C34:
            *i_param1 = 0x1C23;
            break;
        case 0x1C27:
            *i_param1 = 0x1C28;
            break;
        case 0x1C2A:
            *i_param1 = 0x1C2B;
            break;
        case 0x1C30:
            *i_param1 = 0x1C31;
            break;
        case 0x1C2D:
            *i_param1 = 0x1C2E;
            break;
        case 0x1C33:
            *i_param1 = (m7F0 >= m7EE*10) ? 0x1C2F : 0x1C30;
            break;

        case 0x1C36:
            *i_param1 = 0x1C37;
            break;
        default:
            uVar2 = 0x10;
            break;
    }
    return uVar2;
}

/* 000010F4-000011DC       .text getMsg_KF1_0__11daNpc_Kf1_cFv */
s32 daNpc_Kf1_c::getMsg_KF1_0() {

    if(m7A1 != 0){
        return 0x1C38;
    }
    if(dComIfGs_isEventBit(dSv_event_flag_c::ENDLESS_NIGHT)){
        if(!dComIfGs_isSymbol(0)){
            return 0x1C3B;
        }
    }
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B02)){
        u8 uVar3 = dComIfGs_getEventReg(dSv_event_flag_c::UNK_BCFF);
        if(dKy_daynight_check() == 1 || !dComIfGs_isEventBit(dSv_event_flag_c::UNK_2780) || (uVar3 & 1) != 0){
            return 0x1C26;
        }
        return 0x1C27;
    }
    return 0x1C21;
}

/* 000011DC-00001218       .text getMsg__11daNpc_Kf1_cFv */
u32 daNpc_Kf1_c::getMsg() {

    u32 o_retval = 0;
    switch(m7FC){
        case 0:
            o_retval =  getMsg_KF1_0();
            break;
    }
    return o_retval;
}

/* 00001218-000012A4       .text eventOrder__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::eventOrder() {

    if(m7F7 == 1 || m7F7 == 2){
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(m7F7 == 1){
            fopAcM_orderSpeakEvent(this);
        }
    }else if(m7F7 >= 3){
        m786 = m7F7 - 3;
        fopAcM_orderOtherEventId(this,m780[m786]);
    }
}

/* 000012A4-00001380       .text checkOrder__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::checkOrder() {

    if(eventInfo.checkCommandDemoAccrpt()){
        if(dComIfGp_evmng_startCheck(m780[m786]) && m7F7 >= 3){
            daPy_py_c* player;
            switch(m786){
                case 0:
                    player = (daPy_py_c*)dComIfGp_getPlayer(0);
                    player->changeDemoMoveAngle(player->current.angle.y);
                    break;
                case 1:
                case 2:
                default:
                    break;
            }
            m7F7 = 0;
            m7F3 = -1;
            m7F4 = -1;
        }
    }else if(eventInfo.checkCommandTalk() && (m7F7 == 1 || m7F7 == 2)){
        m7F7 = 0;
        m7AC = 1;
    }
}

/* 00001380-00001418       .text chk_talk__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::chk_talk() {

    if(dComIfGp_event_chkTalkXY()){
        if(dComIfGp_evmng_ChkPresentEnd()){
            m79E = dComIfGp_event_getPreItemNo();
            return TRUE;
        }else{
            return FALSE;
        }
    }else{
        m79E = -1;
        return TRUE;
    }
}

/* 00001418-0000146C       .text searchByID__11daNpc_Kf1_cFUiPi */
fopAc_ac_c* daNpc_Kf1_c::searchByID(fpc_ProcID i_procId, int* i_param2) {

    fopAc_ac_c* actor = NULL;
    *i_param2 = 0;
    if(!fopAcM_SearchByID(i_procId,&actor)){
        *i_param2 = 1;
    }
    return actor;
}

/* 0000146C-0000156C       .text srch_Tsubo__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::srch_Tsubo() {

    s32 uVar2 = 0;
    if(m7FD != 1){
        return 0;
    }
    m700 = -1;
    l_check_wrk = 0;
    for(s32 i = 0; i <= 0x13; i++){
        l_check_inf[i] = NULL;
    }
    fpcEx_Search(searchActor_Tsubo,this);
    if(l_check_wrk >= 8){
        m7EC = 0;
        for(s32 i = 0; i <= 7; i++){
            m7BC[i] = fopAcM_GetID(l_check_inf[i]);
            m7EC += 1;
        }
        uVar2 = 1;
        m7FD += 1;
    }
    return uVar2;

}

/* 0000156C-000017F4       .text create_rupee__11daNpc_Kf1_cF4cXyzi */
void daNpc_Kf1_c::create_rupee(cXyz i_param1, int i_param2) {

    cXyz local(0.2f,0.2f,0.2f);
    csXyz local_c8(0.0f,0.0f,0.0f);
    int iVar8;
    s32 iVar7 = g_Counter.mCounter0;
    for(iVar8 = 0; iVar8 < i_param2; iVar8++,iVar7++){
        f32 local_c0[3] = {-30.0f,0.0f,30.0f};
        s32 iVar2 = local_c0[iVar7 % 3] + (cM_rndF(30.0f) - 15.0f);
        iVar2 = (s16)iVar2 * 182.0389f;
        local_c8.y = current.angle.y + iVar2;
        fopAc_ac_c* a_actor_p = fopAcM_createItemForKP2(&i_param1,dItemNo_RED_RUPEE_e,fopAcM_GetRoomNo(this),NULL,NULL,cM_rndFX(2.0f)+13.0f,cM_rndFX(4.0f)+31.0f,-2.0f,1);
        JUT_ASSERT(0x412,a_actor_p != NULL);
        if(a_actor_p){
            fopAcM_OnStatus(a_actor_p, fopAcStts_UNK4000_e);
            fopAcM_OffStatus(a_actor_p, fopAcStts_NOCULLEXEC_e);
            a_actor_p->scale = local;
            a_actor_p->shape_angle = local_c8;
            a_actor_p->current.angle = a_actor_p->shape_angle;
            m7B0[iVar8] = fopAcM_GetID(a_actor_p);
        }
    }
}

/* 000017F4-00001A0C       .text ready_kutaniCamera__11daNpc_Kf1_cFii */
void daNpc_Kf1_c::ready_kutaniCamera(int i_param1, int i_param2) {

    int i_flg;
    cXyz local_20;
    cXyz local_2c;

    fopAc_ac_c* a_actor = searchByID(m7E8,&i_flg);
    if( a_actor && i_flg == 0){
        fopAcM_delete(a_actor);
    }
    if(i_param2 != 0){
        local_20.x = 0.1f;
        local_20.y = 0.1f;
        local_20.z = 0.1f;
        csXyz local_34(0,0,0);
        a_actor = searchByID(m7DC[i_param1],&i_flg);
        JUT_ASSERT(0x432,NULL != a_actor && 0 == i_flg);
        dComIfGp_event_setItemPartner(a_actor);
        local_34.y = a_actor->current.angle.y;
        local_2c = a_actor->current.pos;
        local_2c.y = local_2c.y + 180.0f;
        a_actor = fopAcM_createItemForKP2(&local_2c,4,fopAcM_GetRoomNo(this),NULL,NULL,0.0f,0.0f,-4.0f,1);
        JUT_ASSERT(0x43E,NULL != a_actor);
        fopAcM_OnStatus(a_actor, fopAcStts_UNK4000_e);
        fopAcM_OffStatus(a_actor, fopAcStts_NOCULLEXEC_e);
        a_actor->scale = local_20;
        a_actor->current.angle = local_34;
        m7E8 = fopAcM_GetID(a_actor);
    }
}

/* 00001A0C-00001BD0       .text lookBack__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::lookBack() {

    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    m776 = m_jnt.getHead_y();
    m778 = m_jnt.getBackbone_y();
    m774 = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f, 0.0f, 0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = m7AD;

    switch (mLookBackState) {
        case 1:
            m73C = dNpc_playerEyePos(-20.0f);
            dstPos = m73C;
            dstPos_p = &dstPos;
            break;
        case 2:
            dstPos = m73C;
            dstPos_p = &dstPos;
            break;
        case 3:
            desiredYrot = m79A;
            break;
        case 4:
            int local_48;
            fopAc_ac_c* iVar3 = searchByID(m704,&local_48);
            if(iVar3 && local_48 == 0){
                m73C = iVar3->current.pos;
                m73C.y = iVar3->eyePos.y;
                dstPos = m73C;
                dstPos_p = &dstPos;
            }
            break;
    }
    m_jnt.lookAtTarget_2(&current.angle.y, dstPos_p, src_pos, desiredYrot, l_HIO.m8.m12, headOnlyFollow);

}

/* 00001BD0-00001C50       .text chkAttention__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::chkAttention() {

    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }
}

/* 00001C50-00001CA8       .text setAttention__11daNpc_Kf1_cFb */
void daNpc_Kf1_c::setAttention(bool i_setEyePos) {

    attention_info.position.set(current.pos.x, current.pos.y + l_HIO.m8.m14, current.pos.z);
    if (!m77C && !i_setEyePos) {
        return;
    }
    eyePos.set(m730.x, m730.y, m730.z);
}

/* 00001CA8-00001D30       .text decideType__11daNpc_Kf1_cFi */
bool daNpc_Kf1_c::decideType(int) {

    bool o_retval;
    if(m7FB > 0){
        return true;
    }
    m7FB = 1;
    m7FC = 0;
    strcpy(mArcName,"Kf");
    o_retval = FALSE;
    if(m7FB != -1 && m7FC != -1){
        o_retval = TRUE;
    }
    return o_retval;
    
}

/* 00001D30-00001E04       .text cut_init_ANGRY_START__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_ANGRY_START(int i_param1) {

    Vec* pos_p = dComIfGp_evmng_getMyVec3dP(i_param1,"Pos");
    if(pos_p){
        current.pos.set(pos_p->x,pos_p->y,pos_p->z);
        mObjAcch.SetOld();
    }
    m73C.set(0.0f,eyePos.y,0.0f);
    mLookBackState = 2;
    current.angle.y = cLib_targetAngleY(&current.pos,&m73C);
    speedF = 0.0f;
    setAnm_NUM(0,1);
}

/* 00001E04-00001E0C       .text cut_move_ANGRY_START__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_ANGRY_START() {

    return true;
}

/* 00001E0C-00001E5C       .text cut_init_BENSYOU_START__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_BENSYOU_START(int i_param1) {

    cut_init_ANGRY_START(i_param1);
    cXyz goal(0.0f,0.0f,700.0f);
    dComIfGp_evmng_setGoal(&goal);
}

/* 00001E5C-00001E64       .text cut_move_BENSYOU_START__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_BENSYOU_START() {

    return true;
}

/* 00001E64-00001EB4       .text cut_init_TSUBO_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_CNT(int) {

    m7EE = m7EC - chk_tsubo();
    m_jnt.setBackBone_x(0);
    m_jnt.setBackBone_y(0);
    m_jnt.setHead_x(0);
    m_jnt.setHead_y(0);
    mLookBackState = 0;
}

/* 00001EB4-00001EBC       .text cut_move_TSUBO_CNT__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_TSUBO_CNT() {

    return true;
}

/* 00001EBC-00001EE8       .text cut_init_BENSYOU__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_BENSYOU(int) {

    m7F0 = dComIfGs_getRupee();
    dComIfGp_setItemRupeeCount(-(m7EE*10));
}

/* 00001EE8-00001EF0       .text cut_move_BENSYOU__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_BENSYOU() {

    return true;
}

/* 00001EF0-00001FE4       .text cut_init_GET_OUT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_GET_OUT(int i_param1) {

    int* puVar2 = dComIfGp_evmng_getMyIntegerP(i_param1,"Timer");
    m78C = 0;
    if(puVar2){
        m78C = *puVar2;
    }
    ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMoveAngle(0);
    ((daPy_py_c*)dComIfGp_getPlayer(0))->changeOriginalDemo();
    if(m7F0 >= m7EE * 10){
        cXyz local_18(0.0f,0.0f,999.0f);
        cLib_targetAngleY(&((daPy_py_c*)dComIfGp_getPlayer(0))->current.pos,&local_18);
        ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMode(3);
    }else{
        ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoParam0(1);   
        ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMode(9);
    }
}

/* 00001FE4-00002044       .text cut_move_GET_OUT__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_GET_OUT() {

    if(!cLib_calcTimer(&m78C)){
        dComIfGp_setNextStage("sea",3,0xB);
    }
    return false;
}

/* 00002044-0000205C       .text cut_init_DSP_RUPEE_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_DSP_RUPEE_CNT(int) {

    dComIfGp_event_offHindFlag(0x80);
}

/* 0000205C-00002064       .text cut_move_DSP_RUPEE_CNT__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_DSP_RUPEE_CNT() {

    return true;
}

/* 00002064-000020AC       .text cut_init_PLYER_TRN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_TRN(int) {

    ((daPy_py_c*)dComIfGp_getPlayer(0))->changeDemoMoveAngle(
        cLib_targetAngleY(&dComIfGp_getPlayer(0)->current.pos,&current.pos)
    );
}

/* 000020AC-000020B4       .text cut_move_PLYER_TRN__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_PLYER_TRN() {

    return true;
}

/* 000020B4-000020B8       .text cut_init_RUPEE_CNT_END__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_CNT_END(int) {


}

/* 000020B8-000020EC       .text cut_move_RUPEE_CNT_END__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_RUPEE_CNT_END() {

    //TODO: One/both of these inlines likely return u16, making these casts unneeded.
    if((u16)dComIfGs_getRupee() == (u16)dComIfGp_getItemNowRupee()){
        dComIfGp_event_onHindFlag(0x80);
        return true;
    };
    return false;
}

/* 000020EC-00002168       .text cut_init_START_AGE__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_START_AGE(int) {

    m73C.set(0.0f,eyePos.y,0.0f);
    shape_angle.y = cLib_targetAngleY(&current.pos,&m73C);
    m7A8 = 1;
    mLookBackState = 3;
    m79A = shape_angle.y;
    m_jnt.setTrn();
    setAnm_NUM(0,1);
}

/* 00002168-00002178       .text cut_move_START_AGE__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_START_AGE() {

    return !m_jnt.trnChk();
}

/* 00002178-00002284       .text cut_init_PLYER_MOV__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_MOV(int) {
    s16 sVar3 = cLib_targetAngleY(&current.pos,&dComIfGp_getPlayer(0)->current.pos);
    sVar3 = sVar3 - current.angle.y;
    s32 iVar2 = abs(sVar3);
    cXyz cStack_1c;
    cXyz local_28;
    if(iVar2 > 0x2000){
        dComIfGp_evmng_setGoal(&dComIfGp_getPlayer(0)->current.pos);
    }else{
        local_28.set(0.0f,0.0f,0.0f);
        // sVar1 = -0x2800;
        // if(sVar3 > 0){
        //     sVar1 = 0x2800;
        // }
        sVar3 = sVar3 > 0 ? 0x2800 : -0x2800;
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(current.angle.y + sVar3);
        local_28.z = 150.0f;

        mDoMtx_stack_c::multVec(&local_28,&cStack_1c);
        dComIfGp_evmng_setGoal(&cStack_1c);
    }


}

/* 00002284-0000228C       .text cut_move_PLYER_MOV__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_PLYER_MOV() {

    return true;
}

/* 0000228C-000023E8       .text cut_init_RUPEE_SET__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_SET(int) {

    daTsubo::Act_c* a_tsubo_actor;
    if(m7EC == 8){
        u8 local54[8] = {0,0,0,0,0,0,0,0};
        int iVar1;
        for(int i = 0; i < 3; i++){
            do{
                iVar1 = cM_rndF(32.0f) / 4.f;
            }while(local54[iVar1] != 0);
            u32 local_58 = m7BC[iVar1];
            a_tsubo_actor = (daTsubo::Act_c*)fopAcM_SearchByID(local_58);
            JUT_ASSERT(0x5C3, NULL != a_tsubo_actor);
            const int item_no = dItemNo_RED_RUPEE_e;
            a_tsubo_actor->prm_set_itemNo(item_no);
            dComIfGp_event_setItemPartner(a_tsubo_actor);
            m7DC[i] = m7BC[iVar1];
            local54[iVar1] = 1;
        }
    }
    setAnm_NUM(8,1);
}

/* 000023E8-0000260C       .text cut_move_RUPEE_SET__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_RUPEE_SET() {

    fopAc_ac_c* actor;
    int iVar1;
    int iVar5 = 0;
    int i;
    if(m79C == 0){
        if(mpMorf->checkFrame(68.0f) != 0){
            cXyz local_1c(0.0f,40.0f,40.0f);
            mDoAud_seStart(0x69E9,NULL,0,dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            mDoMtx_stack_c::transS(current.pos);
            mDoMtx_stack_c::YrotM(current.angle.y);
            cXyz local_34;
            mDoMtx_stack_c::multVec(&local_1c,&local_34);
            create_rupee(local_34,3);
        }else{
            if(68.0f < mpMorf->getFrame()){

                for(i = 0; i < 3; i++){
                    actor = searchByID(m7B0[i],&iVar1);
                    if(actor && !iVar1){
                        eyePos = actor->current.pos;
                    }
                }
                m77C = 0;
            }
        }
        return false;
    }else{
        for( i = 0; i < 3; i++){
            actor = searchByID(m7B0[i],&iVar1);
            if(actor){
                fopAcM_delete(actor);
                iVar5 += 1;
            }else{
                if(iVar1){
                    iVar5 += 1;
                }
            }
        }
        if(iVar5 == i){
            ready_kutaniCamera(0,1);
            m77C = 1;
            setAnm_NUM(0,1);
            return true;
        }
        return false;
    }
}

/* 0000260C-000026B4       .text cut_init_TSUBO_ATN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_ATN(int i_param1) {

    int* timer_p = dComIfGp_evmng_getMyIntegerP(i_param1,"Timer");
    int* count_p = dComIfGp_evmng_getMyIntegerP(i_param1,"Count");
    m78C = 0;
    if(timer_p){
        m78C = *timer_p;
    }
    m78E = 0;
    if(count_p){
        m78E = *count_p;
    }
}

/* 000026B4-00002794       .text cut_move_TSUBO_ATN__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_TSUBO_ATN() {

    if(!cLib_calcTimer(&m78C)){
        if(m78E >= 0 && m78E <= 3){
            switch(m78E){
                case 0:
                case 1:
                case 2:
                    ready_kutaniCamera(m78E,1);
                    break;
                case 3:
                default:    
                    ready_kutaniCamera(0,0);
                    break;
            }
        }
        return true;
    }
    if(m78C == 0x14){
        mDoAud_seStart(0x6981,NULL,0,dComIfGp_getReverb(fopAcM_GetRoomNo(this)));

    }
    return false;
}

/* 00002794-000028F4       .text cut_init_TLK_MSG__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TLK_MSG(int param_1) {

    int* msgnum_p = dComIfGp_evmng_getMyIntegerP(param_1,"MsgNum");
    int* endmsg_p = dComIfGp_evmng_getMyIntegerP(param_1,"EndMsg");
    m7F3 = -1;
    m7F4 = -1;
    m7FE = 0;
    mCurrMsgNo = 0;
    mEndMsgNo = -1;
    if(endmsg_p){
        mEndMsgNo = *endmsg_p;
    }
    if(msgnum_p){
        mCurrMsgNo = *msgnum_p;
        switch(mCurrMsgNo){
            case 0x1C2D:
                dComIfGp_setMessageCountNumber(m7EE*10);
                break;
            case 0x1C2F:
            case 0x1C30:
                mCurrMsgNo = (m7F0 >= m7EE*10) ? 0x1C2F : 0x1C30;
                break;
            case 0x1C39:
                dComIfGp_getVibration().StartShock(5,-0x21,cXyz(0.0f,1.0f,0.0f));
        }
    }
    mCurrMsgBsPcId = -1;
}

/* 000028F4-00002954       .text cut_init_CONTNUE_TLK__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_CONTNUE_TLK(int i_param1) {

    int* endmsg_p = dComIfGp_evmng_getMyIntegerP(i_param1,"EndMsg");
    mEndMsgNo = -1;
    if(endmsg_p){
        mEndMsgNo = *endmsg_p;
    }
}

/* 00002954-000029D8       .text cut_move_TLK_MSG__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::cut_move_TLK_MSG() {

    u16 talk_val = talk(0);
    if(talk_val == 0x12){
        m7F3 = -1;
        m7F4 = -1;
        m7FE = 0;
        return true;
    }else if(talk_val == 0x2 || talk_val == 0x6){
        return mCurrMsgNo == mEndMsgNo;
    }else{
        return false;
    }
}

/* 000029D8-00002C60       .text privateCut__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::privateCut(int arg0) {

    static char* a_cut_tbl[] = {
        "ANGRY_START", "BENSYOU_START",
        "TSUBO_CNT","BENSYOU",
        "GET_OUT","DSP_RUPEE_CNT",
        "PLYER_TRN","RUPEE_CNT_END",
        "START_AGE","PLYER_MOV",
        "RUPEE_SET","TSUBO_ATN",
        "TLK_MSG","CONTNUE_TLK"
    };

    if (arg0 != -1) {
        m7F2 = dComIfGp_evmng_getMyActIdx(arg0, a_cut_tbl, ARRAY_SIZE(a_cut_tbl), 1, 0);
        if (m7F2 == -1) {
            dComIfGp_evmng_cutEnd(arg0);
        } else {
            if (dComIfGp_evmng_getIsAddvance(arg0)) {
                switch (m7F2) {
                    case 0:
                        cut_init_ANGRY_START(arg0);
                        break;
                    case 1:
                        cut_init_BENSYOU_START(arg0);
                        break;
                    case 2:
                        cut_init_TSUBO_CNT(arg0);
                        break;
                    case 3:
                        cut_init_BENSYOU(arg0);
                        break;
                    case 4:
                        cut_init_GET_OUT(arg0);
                        break;
                    case 5:
                        cut_init_DSP_RUPEE_CNT(arg0);
                        break;
                    case 6:
                        cut_init_PLYER_TRN(arg0);
                        break;
                    case 7:
                        cut_init_RUPEE_CNT_END(arg0);
                        break;
                    case 8:
                        cut_init_START_AGE(arg0);
                        break;
                    case 9:
                        cut_init_PLYER_MOV(arg0);
                        break;
                    case 10:
                        cut_init_RUPEE_SET(arg0);
                        break;
                    case 0xb:
                        cut_init_TSUBO_ATN(arg0);
                        break;
                    case 0xc:
                        cut_init_TLK_MSG(arg0);
                        break;
                    case 0xd:
                        cut_init_CONTNUE_TLK(arg0);
                        break;
                }
            }
            bool cVar3;
            switch (m7F2) {
                case 0:
                    cVar3 = cut_move_ANGRY_START();
                    break;
                case 1:
                    cVar3 = cut_move_BENSYOU_START();
                    break;
                case 2:
                    cVar3 = cut_move_TSUBO_CNT();
                    break;
                case 3:
                    cVar3 = cut_move_BENSYOU();
                    break;
                case 4:
                    cVar3 = cut_move_GET_OUT();
                    break;
                case 5:
                    cVar3 = cut_move_DSP_RUPEE_CNT();
                    break;
                case 6:
                    cVar3 = cut_move_PLYER_TRN();
                    break;
                case 7:
                    cVar3 = cut_move_RUPEE_CNT_END();
                    break;
                case 8:
                    cVar3 = cut_move_START_AGE();
                    break;
                case 9:
                    cVar3 = cut_move_PLYER_MOV();
                    break;
                case 10:
                    cVar3 = cut_move_RUPEE_SET();
                    break;
                case 0xb:
                    cVar3 = cut_move_TSUBO_ATN();
                    break;
                case 0xc:
                    cVar3 = cut_move_TLK_MSG();
                    break;
                case 0xd:
                    cVar3 = cut_move_TLK_MSG();
                    break;
                default:
                    cVar3 = 1;
                    break;
            }

            if (cVar3) {
                dComIfGp_evmng_cutEnd(arg0);
            }
        }
    }
}

/* 00002C60-00002C84       .text endEvent__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::endEvent() {

    dComIfGp_event_reset();
    m7F3 = -1;
    m7F4 = -1;
}

/* 00002C84-00002CBC       .text isEventEntry__11daNpc_Kf1_cFv */
s32 daNpc_Kf1_c::isEventEntry() {

    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 00002CBC-00002E14       .text event_proc__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::event_proc(int param_1) {

    if(dComIfGp_evmng_endCheck(m780[m786])){
        switch(m786){
            default:
            case 2:
                break;
            case 0:
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_2780);
                m7EC = chk_tsubo();
                break;
            case 1:
                u8 temp = dComIfGs_getEventReg(0xBCFF);
                temp |= 1;
                dComIfGs_setEventReg(0xBCFF, temp);                
                m7A8 = 0;
                setStt(1);
                setAnm_NUM(0,1);
                m792 = cLib_getRndValue(0x1E,0x3C);
                m790 = cLib_getRndValue(0xF, 0x1E);
                m7A1 = 1;
                break;
        }
        m792 = cLib_getRndValue(0x1E,0x3C);
        endEvent();  
    }else{
        if(!mEventCut.cutProc()){
            privateCut(param_1);
        }
    }
}

/* 00002E14-00002EC0       .text set_action__11daNpc_Kf1_cFM11daNpc_Kf1_cFPCvPvPv_iPv */
BOOL daNpc_Kf1_c::set_action(ActionFunc i_action, void* i_param_2) {

    if (mCurrentAction != i_action) {
        if (mCurrentAction) {
            m7FD = 9;
            (this->*mCurrentAction)(i_param_2);
        }
        mCurrentAction = i_action;
        m7FD = 0;
        (this->*mCurrentAction)(i_param_2);
    }
    return TRUE;

}

/* 00002EC0-00002F88       .text setStt__11daNpc_Kf1_cFSc */
void daNpc_Kf1_c::setStt(signed char i_param1) {

    u8 uVar1 = m7F8;
    m7F8 = i_param1;
    switch(m7F8){
        case 0:
            break;
        case 1:
            m7F7 = 0;
            m794 = cLib_getRndValue(0x3C,0x5A);
            speedF = 0.0f;
            break;
        case 2:
            m7F7 = 0;
            m7F3 = -1;
            m7F4 = -1;
            m7FE = 0;
            m7F9 = uVar1;
            break;
        case 3:
            m7F7 = 0;
            m794 = cLib_getRndValue(0x5A,0x5A);
    }
    setAnm();
}

/* 00002F88-00003030       .text set_pthPoint__11daNpc_Kf1_cFUc */
void daNpc_Kf1_c::set_pthPoint(unsigned char i_pointIndex) {


    if(mPathRun.isPath() != 0){
        mPathRun.setIdx(i_pointIndex);
        current.pos = mPathRun.getPoint(mPathRun.getIdx());
        if(mPathRun.nextIdx()){
            cXyz runpoint = mPathRun.getPoint(mPathRun.getIdx());
            current.angle.y = cLib_targetAngleY(&current.pos,&runpoint);
        }
    }
}

/* 00003030-000030A8       .text chk_tsubo__11daNpc_Kf1_cFv */
s16 daNpc_Kf1_c::chk_tsubo() {

    int local_18;
    s16 o_retval = 0;
    for(int i = 0; i < 8; i++){
        searchByID(m7BC[i],&local_18);
        if(local_18 == 0){
            o_retval += 1;
        }
    }
    return o_retval;
}

/* 000030A8-0000317C       .text orderTsuboEvent__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::orderTsuboEvent() {

    if(m7AC != 0){
        return FALSE;
    }
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2780)){
        if(m7EC > chk_tsubo()){
            m7F7 = 3;
            return TRUE;
        }
    }else if(m79F != 0xFF && dComIfGs_isSwitch(m79F,fopAcM_GetRoomNo(this))){
        if(m7EC > chk_tsubo()){
            m7F7 = 5;
            return TRUE;
        }
    }
    return FALSE;
}

/* 0000317C-0000327C       .text wait_1__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::wait_1() {

    if(m7AC != 0){
        if(chk_talk()){
            setStt(2);
            mLookBackState = 1;
            m7AD = 0;
            m_jnt.setTrn();
        }
        return TRUE;
    
    }
    if(m7F7 < 3){
        m7F7 = 2;
    }
    m7AD = 1;
    if(m7F6 == 9){
        m792 = 0;
    }
    if(!cLib_calcTimer(&m792)){
        if(m7F6 != 9){
            setAnm_NUM(9,1);
            m794 = 0;
        }
        if(!cLib_calcTimer(&m794)){
            setStt(3);
            return TRUE;
        }
    }
    mLookBackState = 0;
    return TRUE;
}

/* 0000327C-000034C4       .text walk_1__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::walk_1() {

    if(mPathRun.isPath() == 0){
        return TRUE;
    }
    if(dPath_ChkClose(mPathRun.getPath())){ 
        if(mPathRun.chkPointPass(current.pos,mPathRun.getDir())){
            mPathRun.nextIdxAuto();
        }
    }else{
        return TRUE;
    }
    cXyz local_30 = mPathRun.getPoint(mPathRun.getIdx());
    
    s16 sVar4 = cLib_targetAngleY(&current.pos,&local_30);
    cLib_addCalcAngleS(&current.angle.y,sVar4,l_HIO.m8.m1A,l_HIO.m8.m1C,0x80);
    f32 target = l_HIO.m8.m24;
    if(!cLib_calcTimer(&m794) || m7AC != 0){
        target = 0.0f;
    }
    cLib_chaseF(&speedF,target,l_HIO.m8.m28);
    f32 fVar2 = speedF * l_HIO.m8.m20;
    fVar2 = cLib_minLimit(fVar2,0.5f);
    mpMorf->setPlaySpeed(fVar2);
    if((int)target == 0 && (s32)speedF == 0){
        if(m7AC != 0){
            if(chk_talk()){
                setStt(1);
                setAnm_NUM(9,1);
                mLookBackState = 1;
                m7AD = 0;
                m_jnt.setTrn();
            }
            return TRUE;
        }
        setStt(1);
        setAnm_NUM(9,1);
        return TRUE;
    }else{
        if(m7F7 < 3){
            m7F7 = 2;
        }
        mLookBackState = 0;
        m7AD = 1;
    }
    return TRUE;
}

/* 000034C4-000035CC       .text talk_1__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::talk_1() {

    u8 uVar1 = 0;
    talk(1);
    if(!mpCurrMsg){
        return TRUE;
    }
    switch(mpCurrMsg->mStatus){
        case 6:
        case 2:
            break;
        case 0x13:

            switch(mCurrMsgNo){
                case 0x1C2B:
                    uVar1 = 1;

                default:
                    m79E = -1;
                    m7AC = 0;
                    setStt(m7F9);
                    setAnm_NUM(0,1);
                    m792 = cLib_getRndValue(0x1E,0x3C);
                    m790 = cLib_getRndValue(0xF,0x1E);
                    if(uVar1 != 0){
                        m7F7 = 4;
                        
                    }
                    endEvent();
            }
            break;
    }
    return (m7F6 != 4);


}

/* 000035CC-000036B4       .text wait_action1__11daNpc_Kf1_cFPv */
int daNpc_Kf1_c::wait_action1(void*) {

    switch(m7FD){
        case 0:
            setStt(3);
            m7FD += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(m7F8){
                case 1:
                    m77C = wait_1();
                    break;
                case 2:
                    m77C = talk_1();
                    break;
                case 3:
                    m77C = walk_1();
                    break;
            }
            if(m7FD > 1){
                orderTsuboEvent();
            }
        default:
        case 9:
            break;
    }
    return TRUE;
}

/* 000036B4-000037F4       .text demo__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::demo() {

    if(demoActorID == 0){
        if(m7AE){
            m7AE = 0;
        }
    }else{
        if(m7AE == 0){
            m7AE = 1;
            m7A8 = 0;
            m_jnt.setHead_y(0);
            m_jnt.setHead_x(0);
            m_jnt.setBackBone_y(0);
            m_jnt.setBackBone_x(0);
        }
        dDemo_actor_c* this_00 = dComIfGp_demo_getActor(demoActorID);
        if(m6DC.getBtpAnm()){
            u8 uVar1 = m6DC.getBtpAnm()->getFrameMax();
            m6F0 += 1;
            if(m6F0 >= uVar1){
                m6F0 = uVar1;
            }
        }
        J3DAnmTexPattern* btp_dat = this_00->getP_BtpData(mArcName);
        if(btp_dat){
            m6DC.init(mpMorf->getModel()->getModelData(),btp_dat,1,0,1.0f,0,-1,true,FALSE);
            m7F5 = 2;
            m6F0 = 0;
        }
        dDemo_setDemoData(this,0x6A,mpMorf,mArcName);
    }
    return m7AE;
}

/* 000037F4-00003884       .text shadowDraw__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::shadowDraw() {

    cXyz local_18(current.pos.x, current.pos.y + 150.0f, current.pos.z);

    mShadowId = dComIfGd_setShadow(
        mShadowId,
        1,
        mpMorf->getModel(),
        &local_18,
        800.0f,
        40.0f,
        current.pos.y,
        mObjAcch.GetGroundH(),
        mObjAcch.m_gnd,
        &tevStr,
        0,
        1.0,
        dDlst_shadowControl_c::getSimpleTex()
    );
}


const GXColor unused_1 = {0xFF,0x00,0x00,0x80};
const GXColor unused_2 = {0x00,0x00,0xFF,0x80};
const GXColor unused_3 = {0xFF,0xFF,0x00,0x80};

/* 00003884-0000397C       .text _draw__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_draw() {

    J3DModel* a_model = mpMorf->getModel();
    J3DModelData* a_mdl_data = a_model->getModelData();
    if(m7A7 != 0 || m7A9 != 0){
        return TRUE;
    }
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR,&current.pos,&tevStr);
    g_env_light.setLightTevColorType(a_model,&tevStr);
    m6DC.entry(a_mdl_data,m6F0);
    mpMorf->entryDL();
    a_mdl_data->getMaterialTable().removeTexNoAnimator(m6DC.getBtpAnm());
    if(m6D0){
        g_env_light.setLightTevColorType(m6D0,&tevStr); 
        mDoExt_modelEntryDL(m6D0); 
    }
    shadowDraw();
    dSnap_RegistFig(DSNAP_TYPE_NPC_KF1,this,1.0f,1.0f,1.0f);
    return TRUE;

}

/* 0000397C-00003BC4       .text _execute__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_execute() {

    if(m7AA == 0){
       m710 = current.pos;
       m71C = current.angle; 
        m7AA = 1;
    }
    
    m_jnt.setParam(l_HIO.m8.m8,l_HIO.m8.mA,
        l_HIO.m8.mC,l_HIO.m8.mE,
        l_HIO.m8.m0,l_HIO.m8.m2,
        l_HIO.m8.m4,l_HIO.m8.m6,
        l_HIO.m8.m10);
    if(m7A7 != 0 && demoActorID == 0){
        return TRUE;
    }
    srch_Tsubo();
    checkOrder();
    if(!demo()){
        s32 iVar3 = -1;
        if(dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == 0){
            iVar3 = isEventEntry();
        }
        if(iVar3 >= 0 || m7A5 != 0){
            event_proc(iVar3);

        }else{
            (this->*mCurrentAction)(0);
        }
        lookBack();
        fopAcM_posMoveF(this,mStts.GetCCMoveP());
        m7A3 = mObjAcch.ChkGroundHit() ? 1 : 0;
        m7A4 = mObjAcch.ChkWaterIn() ? 1 : 0;
        mObjAcch.CrrPos(*dComIfG_Bgsp());
        play_animation();
    }else{
        m7A7 = 0;
    }
    eventOrder();
    m722 = current.angle;
    if(m7A8 == 0){
        shape_angle = current.angle;
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    setMtx(false);
    if(!m7AE){
        setCollision(90.0f,200.0f);
    }
    return TRUE;
    
    
}

/* 00003BC4-00003C18       .text _delete__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_delete() {

    if(DEMO_SELECT(m7A6 != 0,TRUE)){
#if VERSION == VERSION_DEMO
        l_HIO.removeHIO();
#endif
        dComIfG_resDelete(&mPhs,mArcName);
        if(DEMO_SELECT(mpMorf, heap && mpMorf)){
            mpMorf->stopZelAnime();
        }
    }
    return TRUE;
}

/* 00003C18-00003E64       .text _create__11daNpc_Kf1_cFv */
cPhs_State daNpc_Kf1_c::_create() {

    fopAcM_ct_Retail(this,daNpc_Kf1_c);
    static u32 a_siz_tbl[] = {
        0,
        0,
    };

    if (!decideType(fopAcM_GetParam(this) & 0xFF)) {
        return cPhs_ERROR_e;
    }

    cPhs_State state = dComIfG_resLoad(&mPhs, mArcName);
    m7A6 = state == cPhs_COMPLEATE_e;
    if(!m7A6){
        return state;
    }
#if VERSION == VERSION_DEMO
    l_HIO.entryHIO("金持ちム－ルの父"); //Wealthy Mila's Father

#endif
    fopAcM_ct_Demo(this,daNpc_Kf1_c);
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_siz_tbl[m7FB])) {
        m7A6 = DEMO_SELECT(0,m7A6);
        return cPhs_ERROR_e;
    }
    cullMtx = mpMorf->getModel()->getBaseTRMtx();
    fopAcM_setCullSizeBox(this,-90.0f,-20.0f,-80.0f,90.0f,200.0f,80.0f);
    if(createInit() != 0){
        return state;
    }
    return cPhs_ERROR_e;


}

/* 00004130-0000442C       .text bodyCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::bodyCreateHeap() {

    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName,1);
    JUT_ASSERT(DEMO_SELECT(0x97B,0x97F),a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,NULL,-1,1.0f,0,-1,1,NULL,0x80000,0x11020022);
    if(!mpMorf){
        return FALSE;
    }
    if(!mpMorf->getModel()){
        mpMorf = NULL;
        return FALSE;
    }
    if(!init_texPttrnAnm(0,false)){
        mpMorf = NULL;
        return FALSE;
    }
    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    
    JUT_ASSERT(DEMO_SELECT(0x98F,0x993),m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(DEMO_SELECT(0x991,0x995),m_bbone_jnt_num >= 0);
    m_nck_jnt_num = a_mdl_dat->getJointName()->getIndex("neck");
    JUT_ASSERT(DEMO_SELECT(0x993,0x997),m_nck_jnt_num >= 0);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_nck_jnt_num)->setCallBack(nodeCB_Neck);
    mpMorf->getModel()->setUserArea((u32)this);
    return TRUE;
}

/* 0000442C-000044EC       .text itemCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::itemCreateHeap() {

    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName,0);
    JUT_ASSERT(DEMO_SELECT(0x9A8,0x9AC),a_mdl_dat != NULL);
    m6D0 = mDoExt_J3DModel__create(a_mdl_dat,0x80000,0x11000022);
    if(!m6D0){
        return FALSE;
    }
    return TRUE;
}

/* 000044EC-00004590       .text CreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::CreateHeap() {

    if(!bodyCreateHeap()){
        return FALSE;
    }
    if(!itemCreateHeap()){
        mpMorf = NULL;
        return FALSE;
    }
    mAcchCir.SetWall(30.0f,90.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
    return TRUE;
}

/* 00004590-000045B0       .text daNpc_Kf1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kf1_Create(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Kf1_c*>(i_this)->_create();
}

/* 000045B0-000045D0       .text daNpc_Kf1_Delete__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Delete(daNpc_Kf1_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_delete();
}

/* 000045D0-000045F0       .text daNpc_Kf1_Execute__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Execute(daNpc_Kf1_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_execute();
}

/* 000045F0-00004610       .text daNpc_Kf1_Draw__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_Draw(daNpc_Kf1_c* i_this) {
    return ((daNpc_Kf1_c*)i_this)->_draw();
}

/* 00004610-00004618       .text daNpc_Kf1_IsDelete__FP11daNpc_Kf1_c */
static BOOL daNpc_Kf1_IsDelete(daNpc_Kf1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Kf1_Method = {
    (process_method_func)daNpc_Kf1_Create,
    (process_method_func)daNpc_Kf1_Delete,
    (process_method_func)daNpc_Kf1_Execute,
    (process_method_func)daNpc_Kf1_IsDelete,
    (process_method_func)daNpc_Kf1_Draw,
};

actor_process_profile_definition g_profile_NPC_KF1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_KF1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Kf1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_KF1_e,
    /* Actor SubMtd */ &l_daNpc_Kf1_Method,
    /* Status       */ 0x08 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
