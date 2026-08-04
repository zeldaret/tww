/**
 * d_a_npc_kf1.cpp
 * NPC - Mila's Father (rich)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_kf1.h"
#include "d/actor/d_a_player.h"
#include "d/d_a_obj.h"
#include "d/d_snap.h"

/* 000000EC-00000150       .text __ct__15daNpc_Kf1_HIO_cFv */
daNpc_Kf1_HIO_c::daNpc_Kf1_HIO_c() {
    /* Nonmatching */
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
        0x4348,
        0x0000,
        0x0000,
        0x000A,
        0x0400,
        0x0000,
        0.5f,
        2.0f,
        0.20f,
        8.0f,
    };
    memcpy(m8,&a_prm_tbl,0x30);
    m0 = -1;
    m4 = -1;
}

static daNpc_Kf1_HIO_c l_HIO;

/* 00000198-000001E4       .text nodeCB_Head__FP7J3DNodei */
static BOOL nodeCB_Head(J3DNode*, int) {
    /* Nonmatching */
}

/* 000001E4-000002D8       .text _nodeCB_Head__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Head(J3DNode* i_node, J3DModel* i_pModel) {
    /* Nonmatching */
    static cXyz a_eye_pos_off(30.0f,30.0f,0.0f);
    int jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_multVecZero(mDoMtx_stack_c::get(),&m754);
    mDoMtx_stack_c::multVec(&a_eye_pos_off,&m730);
    mDoMtx_copy(mDoMtx_stack_c::get(),J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx,mDoMtx_stack_c::get());
}

/* 00000314-00000360       .text nodeCB_Neck__FP7J3DNodei */
static BOOL nodeCB_Neck(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000360-00000400       .text _nodeCB_Neck__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_Neck(J3DNode* i_node, J3DModel* i_pModel) {
    /* Nonmatching */
    int jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());
    mDoMtx_copy(mDoMtx_stack_c::get(),J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx,mDoMtx_stack_c::get());
}

/* 00000400-0000044C       .text nodeCB_BackBone__FP7J3DNodei */
static BOOL nodeCB_BackBone(J3DNode*, int) {
    /* Nonmatching */
}

/* 0000044C-000004EC       .text _nodeCB_BackBone__11daNpc_Kf1_cFP7J3DNodeP8J3DModel */
void daNpc_Kf1_c::_nodeCB_BackBone(J3DNode* i_node, J3DModel* i_pModel) {
    /* Nonmatching */
    int jointIdx = ((J3DJoint*)(i_node))->getJntNo();
    mDoMtx_stack_c::copy(i_pModel->getAnmMtx(jointIdx));
    mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());
    mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x());
    mDoMtx_copy(mDoMtx_stack_c::get(),J3DSys::mCurrentMtx);
    i_pModel->setAnmMtx(jointIdx,mDoMtx_stack_c::get());
}

/* 000004EC-0000050C       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    /* Nonmatching */
    return ((daNpc_Kf1_c*)i_this)->CreateHeap();
}

static fopAc_ac_c* l_check_inf[0x14];
static s32 l_check_wrk;
/* 0000050C-0000059C       .text searchActor_Tsubo__FPvPv */
void* searchActor_Tsubo(void* i_actorP, void*) {
    /* Nonmatching */
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
    /* Nonmatching */
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D01)){
        set_action(&daNpc_Kf1_c::wait_action1,NULL);
        return TRUE;
    }
    return FALSE;
}

static char* l_evn_tbl[3];
/* 0000061C-0000083C       .text createInit__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::createInit() {
    /* Nonmatching */
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
    if(!mPathRun.getPath()){
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
    /* Nonmatching */
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
    /* Nonmatching */
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
    /* Nonmatching */
    static const u32 a_resID_tbl[0xA] = {0xA,0xC,0x6,0x7,0x8,0x9,0x5,0x3,0x4,0xB};
    return a_resID_tbl[i_idx];
}

/* 00000A34-00000A48       .text btpResID__11daNpc_Kf1_cFi */
s32 daNpc_Kf1_c::btpResID(int i_idx) {
    /* Nonmatching */
    static const u32 a_resID_tbl[0x2] = {0x2,0xD};
    return a_resID_tbl[i_idx];
}

/* 00000A48-00000B4C       .text setBtp__11daNpc_Kf1_cFScb */
BOOL daNpc_Kf1_c::setBtp(signed char i_param1, bool i_param2) {
    /* Nonmatching */
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
    return m6DC.init(a_model->getModelData(),a_btp,1,0,1.0f,0,-1,i_param2,0) ? TRUE : FALSE;
}

/* 00000B4C-00000B6C       .text init_texPttrnAnm__11daNpc_Kf1_cFScb */
bool daNpc_Kf1_c::init_texPttrnAnm(signed char i_param1, bool i_param2) {
    /* Nonmatching */
    return setBtp(i_param1,i_param2);
}

/* 00000B6C-00000C08       .text play_btp_anm__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::play_btp_anm() {
    /* Nonmatching */
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
    /* Nonmatching */
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
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[0xA];
    if(i_param2 != 0){
        init_texPttrnAnm(a_anm_prm_tbl[i_param1].m1,true);
    }
    setAnm_anm(&a_anm_prm_tbl[i_param1]);
}

/* 00000D14-00000D80       .text setAnm__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::setAnm() {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[0x4];

        init_texPttrnAnm(a_anm_prm_tbl[m7F8].m1,true);
    
    setAnm_anm(&a_anm_prm_tbl[m7F8]);
}

/* 00000D80-00000D84       .text chngAnmTag__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::chngAnmTag() {
    /* Nonmatching */
}

/* 00000D84-00000D88       .text ctrlAnmTag__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::ctrlAnmTag() {
    /* Nonmatching */
}

/* 00000D88-00000DEC       .text chngAnmAtr__11daNpc_Kf1_cFUc */
void daNpc_Kf1_c::chngAnmAtr(unsigned char i_param1) {
    /* Nonmatching */
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
    /* Nonmatching */
    switch(m7F3){
        case 0x7:
            if(m79C){
                setAnm_NUM(0,1);
                m7F3 = 0;
            }
        case 0x8:
            break;
        case 0x9:
        case 0xA:
            return;
    }
}

/* 00000E60-00000EC4       .text setAnm_ATR__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::setAnm_ATR() {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[2];
    init_texPttrnAnm(a_anm_prm_tbl[m7F3].m1,true);
    setAnm_anm(&a_anm_prm_tbl[m7F3]);
}

/* 00000EC4-00000F80       .text anmAtr__11daNpc_Kf1_cFUs */
void daNpc_Kf1_c::anmAtr(unsigned short i_param_1) {
    /* Nonmatching */
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
    /* Nonmatching */
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
    /* Nonmatching */
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
    /* Nonmatching */
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
    /* Nonmatching */
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
    /* Nonmatching */
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
BOOL daNpc_Kf1_c::chk_talk() {
    /* Nonmatching */
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
    /* Nonmatching */
    fopAc_ac_c* actor = NULL;
    *i_param2 = 0;
    if(!fopAcM_SearchByID(i_procId,&actor)){
        *i_param2 = 1;
    }
    return actor;
}

/* 0000146C-0000156C       .text srch_Tsubo__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::srch_Tsubo() {
    /* Nonmatching */
}

/* 0000156C-000017F4       .text create_rupee__11daNpc_Kf1_cF4cXyzi */
void daNpc_Kf1_c::create_rupee(cXyz, int) {
    /* Nonmatching */
}

/* 000017F4-00001A0C       .text ready_kutaniCamera__11daNpc_Kf1_cFii */
void daNpc_Kf1_c::ready_kutaniCamera(int, int) {
    /* Nonmatching */
}

/* 00001A0C-00001BD0       .text lookBack__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::lookBack() {
    /* Nonmatching */
}

/* 00001BD0-00001C50       .text chkAttention__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::chkAttention() {
    /* Nonmatching */
}

/* 00001C50-00001CA8       .text setAttention__11daNpc_Kf1_cFb */
void daNpc_Kf1_c::setAttention(bool) {
    /* Nonmatching */
}

/* 00001CA8-00001D30       .text decideType__11daNpc_Kf1_cFi */
bool daNpc_Kf1_c::decideType(int) {
    /* Nonmatching */
}

/* 00001D30-00001E04       .text cut_init_ANGRY_START__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_ANGRY_START(int) {
    /* Nonmatching */
}

/* 00001E04-00001E0C       .text cut_move_ANGRY_START__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_ANGRY_START() {
    /* Nonmatching */
}

/* 00001E0C-00001E5C       .text cut_init_BENSYOU_START__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_BENSYOU_START(int) {
    /* Nonmatching */
}

/* 00001E5C-00001E64       .text cut_move_BENSYOU_START__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_BENSYOU_START() {
    /* Nonmatching */
}

/* 00001E64-00001EB4       .text cut_init_TSUBO_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_CNT(int) {
    /* Nonmatching */
}

/* 00001EB4-00001EBC       .text cut_move_TSUBO_CNT__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_TSUBO_CNT() {
    /* Nonmatching */
}

/* 00001EBC-00001EE8       .text cut_init_BENSYOU__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_BENSYOU(int) {
    /* Nonmatching */
}

/* 00001EE8-00001EF0       .text cut_move_BENSYOU__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_BENSYOU() {
    /* Nonmatching */
}

/* 00001EF0-00001FE4       .text cut_init_GET_OUT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_GET_OUT(int) {
    /* Nonmatching */
}

/* 00001FE4-00002044       .text cut_move_GET_OUT__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_GET_OUT() {
    /* Nonmatching */
}

/* 00002044-0000205C       .text cut_init_DSP_RUPEE_CNT__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_DSP_RUPEE_CNT(int) {
    /* Nonmatching */
}

/* 0000205C-00002064       .text cut_move_DSP_RUPEE_CNT__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_DSP_RUPEE_CNT() {
    /* Nonmatching */
}

/* 00002064-000020AC       .text cut_init_PLYER_TRN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_TRN(int) {
    /* Nonmatching */
}

/* 000020AC-000020B4       .text cut_move_PLYER_TRN__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_PLYER_TRN() {
    /* Nonmatching */
}

/* 000020B4-000020B8       .text cut_init_RUPEE_CNT_END__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_CNT_END(int) {
    /* Nonmatching */
}

/* 000020B8-000020EC       .text cut_move_RUPEE_CNT_END__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_RUPEE_CNT_END() {
    /* Nonmatching */
}

/* 000020EC-00002168       .text cut_init_START_AGE__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_START_AGE(int) {
    /* Nonmatching */
}

/* 00002168-00002178       .text cut_move_START_AGE__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_START_AGE() {
    /* Nonmatching */
}

/* 00002178-00002284       .text cut_init_PLYER_MOV__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_PLYER_MOV(int) {
    /* Nonmatching */
}

/* 00002284-0000228C       .text cut_move_PLYER_MOV__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_PLYER_MOV() {
    /* Nonmatching */
}

/* 0000228C-000023E8       .text cut_init_RUPEE_SET__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_RUPEE_SET(int) {
    /* Nonmatching */
}

/* 000023E8-0000260C       .text cut_move_RUPEE_SET__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_RUPEE_SET() {
    /* Nonmatching */
}

/* 0000260C-000026B4       .text cut_init_TSUBO_ATN__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TSUBO_ATN(int) {
    /* Nonmatching */
}

/* 000026B4-00002794       .text cut_move_TSUBO_ATN__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_TSUBO_ATN() {
    /* Nonmatching */
}

/* 00002794-000028F4       .text cut_init_TLK_MSG__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_TLK_MSG(int) {
    /* Nonmatching */
}

/* 000028F4-00002954       .text cut_init_CONTNUE_TLK__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::cut_init_CONTNUE_TLK(int) {
    /* Nonmatching */
}

/* 00002954-000029D8       .text cut_move_TLK_MSG__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::cut_move_TLK_MSG() {
    /* Nonmatching */
}

/* 000029D8-00002C60       .text privateCut__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::privateCut(int) {
    /* Nonmatching */
}

/* 00002C60-00002C84       .text endEvent__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::endEvent() {
    /* Nonmatching */
}

/* 00002C84-00002CBC       .text isEventEntry__11daNpc_Kf1_cFv */
s32 daNpc_Kf1_c::isEventEntry() {
    /* Nonmatching */
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 00002CBC-00002E14       .text event_proc__11daNpc_Kf1_cFi */
void daNpc_Kf1_c::event_proc(int) {
    /* Nonmatching */
}

/* 00002E14-00002EC0       .text set_action__11daNpc_Kf1_cFM11daNpc_Kf1_cFPCvPvPv_iPv */
void daNpc_Kf1_c::set_action(int (daNpc_Kf1_c::*)(void*), void*) {
    /* Nonmatching */
}

/* 00002EC0-00002F88       .text setStt__11daNpc_Kf1_cFSc */
void daNpc_Kf1_c::setStt(signed char) {
    /* Nonmatching */
}

/* 00002F88-00003030       .text set_pthPoint__11daNpc_Kf1_cFUc */
void daNpc_Kf1_c::set_pthPoint(unsigned char) {
    /* Nonmatching */
}

/* 00003030-000030A8       .text chk_tsubo__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::chk_tsubo() {
    /* Nonmatching */
}

/* 000030A8-0000317C       .text orderTsuboEvent__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::orderTsuboEvent() {
    /* Nonmatching */
}

/* 0000317C-0000327C       .text wait_1__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::wait_1() {
    /* Nonmatching */
}

/* 0000327C-000034C4       .text walk_1__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::walk_1() {
    /* Nonmatching */
}

/* 000034C4-000035CC       .text talk_1__11daNpc_Kf1_cFv */
void daNpc_Kf1_c::talk_1() {
    /* Nonmatching */
}

/* 000035CC-000036B4       .text wait_action1__11daNpc_Kf1_cFPv */
int daNpc_Kf1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 000036B4-000037F4       .text demo__11daNpc_Kf1_cFv */
bool daNpc_Kf1_c::demo() {
    /* Nonmatching */
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
    /* Nonmatching */
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

/* 00003884-0000397C       .text _draw__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::_draw() {
    /* Nonmatching */
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
    /* Nonmatching */
    if(m7AA == 0){
       m710 = current.pos;
       m71C = current.angle; 
        m7AA = 1;
    }
    
    m_jnt.setParam(l_HIO.m8[0].m8,l_HIO.m8[0].mA,
        l_HIO.m8[0].mC,l_HIO.m8[0].mE,
        l_HIO.m8[0].m0,l_HIO.m8[0].m2,
        l_HIO.m8[0].m4,l_HIO.m8[0].m6,
        l_HIO.m8[0].m10);
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
    /* Nonmatching */
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
    /* Nonmatching */
    fopAcM_ct_Retail(this,daNpc_Kf1_c);
    static u32 a_size_tbl[] = {
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
    if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, a_size_tbl[m7FB])) {
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
    /* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName,0);
    JUT_ASSERT(DEMO_SELECT(0x9AC,0x9AC),a_mdl_dat);
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
    
    JUT_ASSERT(DEMO_SELECT(0x993,0x993),m_hed_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(DEMO_SELECT(0x995,0x995),m_bbone_jnt_num >= 0);
    m_nck_jnt_num = a_mdl_dat->getJointName()->getIndex("neck");
    JUT_ASSERT(DEMO_SELECT(0x997,0x997),m_nck_jnt_num >= 0);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_hed_jnt_num)->setCallBack(nodeCB_Head);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_bbone_jnt_num)->setCallBack(nodeCB_BackBone);
    mpMorf->getModel()->getModelData()->getJointNodePointer(m_nck_jnt_num)->setCallBack(nodeCB_Neck);
    mpMorf->getModel()->setUserArea((u32)this);
    return TRUE;
}

/* 0000442C-000044EC       .text itemCreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::itemCreateHeap() {
    /* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes(mArcName,0);
    JUT_ASSERT(DEMO_SELECT(0x9AC,0x9AC),a_mdl_dat);
    m6D0 = mDoExt_J3DModel__create(a_mdl_dat,0x80000,0x11000022);
    if(!m6D0){
        return FALSE;
    }
    return TRUE;
}

/* 000044EC-00004590       .text CreateHeap__11daNpc_Kf1_cFv */
BOOL daNpc_Kf1_c::CreateHeap() {
    /* Nonmatching */
    if(!bodyCreateHeap()){
        return FALSE;
    }
    if(!itemCreateHeap()){
        mpMorf = NULL;
        return FALSE;
    }
    mAcchCir.SetWall(30.0f,90.0f);
    mObjAcch.Set(&current.pos,&old.pos,this,1,&mAcchCir,&speed);
    return TRUE;
}

/* 00004590-000045B0       .text daNpc_Kf1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Kf1_Create(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Kf1_c*>(i_this)->CreateHeap();
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
