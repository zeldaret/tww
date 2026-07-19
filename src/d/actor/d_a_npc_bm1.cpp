/**
 * d_a_npc_bm1.cpp
 * NPC - Generic Ritos
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_bm1.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/d_letter.h"
#include "d/d_snap.h"
#include "res/Object/Bm.h"

class daNpc_Bm1_childHIO_c : public mDoHIO_entry_c{

public:
    daNpc_Bm1_childHIO_c();
    void genMessage(JORMContext* ctx){};
public:

    hio_prm_c hio_prm;
    u32 m50;
    //SIZE: 0x54
};

class daNpc_Bm1_HIO_c :public mDoHIO_entry_c{
public:
    daNpc_Bm1_HIO_c();
    virtual ~daNpc_Bm1_HIO_c(){};
    void genMessage(JORMContext* ctx);
public:

    s8 m4;
    s32 m8;
    daNpc_Bm1_childHIO_c children[10];
    /* Place member variables here */
};
    //SIZE: 0x354





static daNpc_Bm1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static s32 l_check_wrk = 0;
static char l_BCKName[0x1E];
static char l_BTPName[0x1E];




/* 000000EC-00000108       .text __ct__20daNpc_Bm1_childHIO_cFv */
daNpc_Bm1_childHIO_c::daNpc_Bm1_childHIO_c() {
    
}

/* 00000150-0000020C       .text __ct__15daNpc_Bm1_HIO_cFv */
daNpc_Bm1_HIO_c::daNpc_Bm1_HIO_c() {
    
    static hio_prm_c a_prm_tbl[] = {
        0x2000,0x0FA0,
        0xF63C,0xF060,
        0x0000,0x1B58,
        0xFC18,0xE4A8,
        0x0800,0x04B0,
        220.0f,
        0x0,0x0A,
        0x0400,0x0000,
        0,
        0,
        0,
        0,
        180.0f,
        0x0006,0x0400,
        0.5f,
        3.0f,
        0.1f,
        40.0f,
        870.0f,
        0x2000,0x2000,
        0xF8BB,0xE000,
        0x0000,0x1036,
        0x0000,0xEFCA,
        0x0479,0x0000,
        209.0f,
        0,0,
        0,0,
        0,
        0,
        0,
        0,
        0,
        0,0,
        0,
        0,
        0,
        0,
        0,
        0x2000,0x2000,
        0xF8BB,0xE000,
        0x0000,0x1036,
        0x0000,0xEFCA,
        0x0479,0x0000,
        209.0f,
        0,0,
        0,0,
        0,
        0,
        0,
        0,
        0,
        0,0,
        0,
        0,
        0,
        0,
        0,
        0x2000,0x2000,
        0xF000,0xE000,
        0x0000,0x1000,
        0x0000,0xF000,
        0x0578,0x0000,
        220.0f,
        0,0,
        0,0,
        0,
        0,
        0,
        0,
        0,
        0,0,
        0,
        0,
        0,
        0,
        0,
    0x2000,0x2000,
        0xF000,0xE000,
        0x0000,0x1000,
        0x0000,0xF000,
        0x0578,0x0000,
        220.0f,
        0,0,
        0,0,
        0,
        0,
        0,
        0,
        0,
        0,0,
        0,
        0,
        0,
        0,
        0,
    0x2000,0x2000,
        0xE5BA,0xE000,
        0x0000,0x1000,
        0x0000,0xF000,
        0x0508,0x0313,
        220.0f,
        0,0,
        0,0,
        0,
        0,
        0,
        0,
        0,
        0,0,
        0,
        0,
        0,
        0,
        0,
        0x2000,0x2000,
        0xF000,0xE000,
        0x0000,0x1000,
        0x0000,0xF000,
        0x03E8,0x0596,
        220.0f,
        0,0xA,
        0x0400,0x0000,
        20.0f,
        1.0f,
        20.0f,
        0.6f,
        180.0f,
        0x0006,0x0400,
        0.3f,
        4.0f,
        0.3f,
        40.0f,
        0x00000000,
        0x2000,0x2000,
        0xF000,0xE000,
        0x0000,0x2000,
        0x0000,0xE000,
        0x0640,0x0578,
        220.0f,
        0,0,0,
        0,0,0,0,0,0,0x0006,0x0400,
        0.3f,
        4.0f,
        0.3f,
        40.0f,
        0,
        0x2000,0x2000,
        0xF000,0xE000,
        0x0000,0x2000,
        0x0000,0xE000,
        0x0640,0x0578,
        220.0f,
        0,0,0,
        0,
        0,
        0,
        0,
        0,
        0,
        0x0006,0x0400,
        0.3f,
        4.0f,
        0.3f,
        40.0f,
        0,0x2000,0x2000,
        0xF000,0xE000,
        0x0000,0x1000,
        0x0000,0xF000,
        0x0640,0x04B0,
        220.0f,
        0,0xA,
        0x0400,0x0000,
        20.0f,
        1.0f,
        20.0f,
        0.3f,
        180.0f,
        0x0006,0x0400,
        0.5f,
        4.0f,
        0.3f,
        40.0f,
    };
    for(int i = 0; i < 10; i++){
        children[i].m50 = i;
        memcpy(&children[i].hio_prm,&a_prm_tbl[i],0x4C);
    }
    m4 = -1;
    m8 = -1;
}





/* 00000268-000002E0       .text searchActor_Zl__FPvPv */
static void* searchActor_Zl(void* i_param_1, void*) {
    
    if(l_check_wrk < 0x14 && fopAcM_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_ZL1_e){
        l_check_inf[l_check_wrk] =(fopAc_ac_c*)i_param_1;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 000002E0-00000358       .text searchActor_Gp__FPvPv */
static void* searchActor_Gp(void* i_param_1, void*) {
    
    if(l_check_wrk < 0x14 && fopAcM_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_GP1_e){
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_param_1;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 00000358-000003DC       .text searchActor_Bm_Skt__FPvPv */
static void* searchActor_Bm_Skt(void* i_param_1, void*) {
    
    if(l_check_wrk < 0x14 && fopAcM_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_BM2_e){
        if(reinterpret_cast<daNpc_Bm1_c*>(i_param_1)->IamSukketo()){
            l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_param_1;
            l_check_wrk += 1;
        }
    }
    return NULL;
}

/* 000003DC-00000460       .text searchActor_Bm_Kkt__FPvPv */
static void* searchActor_Bm_Kkt(void* i_param_1, void*) {
    
    if(l_check_wrk < 0x14 && fopAcM_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_BM2_e){
        if(reinterpret_cast<daNpc_Bm1_c*>(i_param_1)->IamKakkuto()){
            l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_param_1;
            l_check_wrk += 1;
        }
    }
    return NULL;
}

/* 00000460-000004AC       .text nodeCallBack_Wng__FP7J3DNodei */
static BOOL nodeCallBack_Wng(J3DNode* i_param_1, int i_param_2) {
    
    if(i_param_2 == 0){
        if(j3dSys.getModel()->getUserArea() != NULL){
            reinterpret_cast<daNpc_Bm1_c*>(j3dSys.getModel()->getUserArea())->nodeWngControl(i_param_1,j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000004AC-000005BC       .text nodeWngControl__11daNpc_Bm1_cFP7J3DNodeP8J3DModel */
void daNpc_Bm1_c::nodeWngControl(J3DNode* i_node, J3DModel* i_model) {
    
    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if(uVar1 == m_wngL1_jnt_num){
        cMtx_copy(mLeftArmMtx,j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1,mLeftArmMtx);
    }
    if(uVar1 == m_wngL3_jnt_num){
        mDoMtx_stack_c::multVecZero(&mWingLPos);

    }
    if(uVar1 == m_wngR1_jnt_num){
        cMtx_copy(mRightArmMtx,j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1,mRightArmMtx);   
    }
    if(uVar1 == m_wngR3_jnt_num){
        mDoMtx_stack_c::multVecZero(&mWingRPos);

    }
}

/* 000005BC-00000608       .text nodeCallBack_Arm__FP7J3DNodei */
static BOOL nodeCallBack_Arm(J3DNode* i_param_1, int i_param_2) {
    
    if(i_param_2 == 0){
        if(j3dSys.getModel()->getUserArea() != NULL){
            reinterpret_cast<daNpc_Bm1_c*>(j3dSys.getModel()->getUserArea())->nodeArmControl(i_param_1,j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000608-00000718       .text nodeArmControl__11daNpc_Bm1_cFP7J3DNodeP8J3DModel */
void daNpc_Bm1_c::nodeArmControl(J3DNode* i_node, J3DModel* i_model) {
    
    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if(uVar1 == m_armL1_jnt_num){
        cMtx_copy(mLeftArmMtx,j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1,mLeftArmMtx);
    }
    if(uVar1 == m_armL2_jnt_num){
        mDoMtx_stack_c::multVecZero(&mArmLPos);
    }
    if(uVar1 == m_armR1_jnt_num){
        cMtx_copy(mRightArmMtx,j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1,mRightArmMtx);   
    }
    if(uVar1 == m_armR2_jnt_num){
        mDoMtx_stack_c::multVecZero(&mArmRPos);
    }
}

/* 00000718-00000764       .text nodeCallBack_Bm1__FP7J3DNodei */
static BOOL nodeCallBack_Bm1(J3DNode* i_param_1, int i_param_2) {
    
    if(i_param_2 == 0){
        if(j3dSys.getModel()->getUserArea() != NULL){
            reinterpret_cast<daNpc_Bm1_c*>(j3dSys.getModel()->getUserArea())->nodeBm1Control(i_param_1,j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000764-00000900       .text nodeBm1Control__11daNpc_Bm1_cFP7J3DNodeP8J3DModel */
void daNpc_Bm1_c::nodeBm1Control(J3DNode* i_node, J3DModel* i_model) {
    
    static cXyz a_eye_pos_off(26.0f,26.0f,0.0f);
    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if(uVar1 == m_nec_jnt_num){
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());     
    }
    if(uVar1 == m_bbone_jnt_num){
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());  
        mDoMtx_stack_c::ZrotM(-m_jnt.getBackbone_x()); 
    } 
    if(uVar1 == m_arm_L_jnt_num){
        cMtx_copy(mDoMtx_stack_c::get(),mLeftArmMtx);
    }
    if(uVar1 == m_arm_R_jnt_num){
        cMtx_copy(mDoMtx_stack_c::get(),mRightArmMtx);
    }
    if(uVar1 == m_hed_jnt_num){
        mDoMtx_stack_c::multVec(&a_eye_pos_off,&mEyePos);  
    }
    cMtx_copy(mDoMtx_stack_c::get(),j3dSys.mCurrentMtx);
    i_model->setAnmMtx(uVar1,mDoMtx_stack_c::get());

}
char* l_evn_tbl[] = {
    "Get_Mo3_Ltr","Met_Ryu_Islnd","Get_Rupee","Skn_Islnd",
};
/* 0000093C-00000A9C       .text chk_appCnd__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::chk_appCnd() {
    switch (mSpawnCondition) {
        case 0:
            return TRUE;
        case 1:
            if(!dComIfGs_isSymbol(1)){
                return TRUE;
            }
            break;
        case 2:
            if(dComIfGs_isSymbol(1)){
                return !dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A80);
            }
            break;
        case 3:
            if(!dComIfGs_isSymbol(1)){
                return FALSE;
            }
            if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A80)){
                return dKy_daynight_check() == 0;
            }
            break;
        case 4:
            if(!dComIfGs_isSymbol(1)){
                return FALSE;
            }
            if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A80)){
                return dKy_daynight_check() == 1;
            }
            break;
    }
    return false;

}

/* 00000A9C-00000B38       .text init_PST_0__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_PST_0() {


    bool o_retval = false;
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)){
        set_action(&daNpc_Bm1_c::demo_action1,NULL);
        fopAcM_ClearStatusMap(this);
        mbInitPostman0 = true;
        o_retval = true;
    }
    return o_retval;
}

/* 00000B38-00000B84       .text init_PST_1__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_PST_1() {
    
    set_action(&daNpc_Bm1_c::wait_action1,NULL);
    return true;
}

/* 00000B84-00000C0C       .text init_PST_2__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_PST_2() {
    
    bool o_retval = false;
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1F40)){
        set_action(&daNpc_Bm1_c::wait_action3,NULL);
        o_retval = true;
    }
    return o_retval;
}

/* 00000C0C-00000CB8       .text init_PST_3__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_PST_3() {
    
    bool result;
    result = dComIfGs_isSymbol(1) == 0;
    if(result){
        result = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1102) != 0;
        if(result){
            set_action(&daNpc_Bm1_c::wait_action1,NULL);
        }
    }
    return result;
}

/* 00000CB8-00000D58       .text init_PST_4__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_PST_4() {

    bool result = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1E80) == 0;
    if(result){
        m888 = 1;
        gravity = 0.0f;
        set_action(&daNpc_Bm1_c::wait_action9,NULL);
        fopAcM_OnStatus(this,fopAcStts_UNK4000_e);
        return true;
    }
    return result;
}

/* 00000D58-00000DA4       .text init_BMB_0__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_BMB_0() {

    set_action(&daNpc_Bm1_c::wait_action6,NULL);
    return true;
}

/* 00000DA4-00000DC4       .text init_BMB_1__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_BMB_1() {
    
    init_BMB_0();
}

/* 00000DC4-00000E10       .text init_BMB_2__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_BMB_2() {

    set_action(&daNpc_Bm1_c::wait_action8,NULL);
    return true;
}

/* 00000E10-00000E5C       .text init_BMC_0__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_BMC_0() {

    set_action(&daNpc_Bm1_c::wait_action2,NULL);
    return true;
}

/* 00000E5C-00000F04       .text init_BMC_1__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_BMC_1() {

    bool result = false;
    if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1808)){
        result = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1220);
        if(result){
            set_action(&daNpc_Bm1_c::wait_action4,NULL);
        }
    }
    return result;

}

/* 00000F04-00000FB0       .text init_BMC_2__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_BMC_2() {

    bool result = false;
    if(!dComIfGs_isGetItemReserve(0x0F)){
        result = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1808);
        if(result){
            set_action(&daNpc_Bm1_c::wait_action5,NULL);
        }
    }
    return result;
}

/* 00000FB0-00001010       .text init_BMC_3__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_BMC_3() {

    if(mPathRun.getPath()){
    set_action(&daNpc_Bm1_c::wait_actionA,NULL);
    return true;
    }

    return false;
}

/* 00001010-00001030       .text init_BMD_0__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_BMD_0() {

    return init_BMC_3();
}

/* 00001030-00001084       .text init_BMD_1__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_BMD_1() {

    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_1620)){
        return false;
    }
    return init_BMC_0();
}

/* 00001084-000010DC       .text init_SKT_0__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_SKT_0() {

    fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);
    set_action(&daNpc_Bm1_c::wait_action7,NULL);
    return true;
}

/* 000010DC-000010FC       .text init_KKT_0__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_KKT_0() {

    return init_SKT_0();
}

/* 000010FC-00001404       .text createInit__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::createInit() {
    
    static u8 a_att_dis_TBL[11][2] = {0xA9,0xA9,0xA9,0xA9,
    0x6D,0x6D,0x6F,0x6D,0xA9,0xA9,0x80,0x80,0x80,0x80,0xA9,0xA9,0xA8,0xA8,0xA8,0xA8,0xAA,0xAA};
    if(chk_appCnd() == 0){
        return false;
    }
    for(int i = 0; i < 4; i++){
        m862[i] = dComIfGp_evmng_getEventIdx(l_evn_tbl[i]);
    }
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    attention_info.distances[1] = a_att_dis_TBL[mType][0];
    attention_info.distances[3] = a_att_dis_TBL[mType][1];
    gravity = -4.5;
    mAttentionPos = current.pos;
    s32 iVar5 = 0xFF;
    u32 param = fopAcM_GetParam(this);
    if(((param >> 16) & 0xFF) != 0xFF){
        mPathRun.setInf((param >> 16) & 0xFF,fopAcM_GetRoomNo(this),true);

        if(mPathRun.isPath()){
            fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);
            iVar5 = 0xF0;    
        }else{
            return false;
        }

    }
    static char* a_staff_tbl[0x10] = {"Bm1","Bm1","Bm1","Bm1","Bm1","Bm2","Bm2","Bm3","Bm3","Bm3","Bm4","Bm4","Bm4","Bm4","Bm5","Bm5"};
    mEventCut.setActorInfo2(a_staff_tbl[mSpecificType],this);
    mBckResIndex = 0x16;
    bool init_success;
    switch(mSpecificType){
        case Quill_0:
            init_success = init_PST_0();
            break;
        case Quill_1:
            init_success = init_PST_1();
            break;
        case Quill_2:
            init_success = init_PST_2();
            break;
        case Quill_3:
            init_success = init_PST_3();
            break;
        case Quill_4:
            init_success = init_PST_4();
            break;
        case Skett:
            init_success = init_SKT_0();
            break;
        case Akoot:
            init_success = init_KKT_0();
            break;
        case Basht:
            init_success = init_BMB_0();
            break;
        case Bisht:
            init_success = init_BMB_1();
            break;
        case Hoskit:
            init_success = init_BMB_2();
            break;
        case Ilari_0xA:
            init_success = init_BMC_0();
            break;
        case Ilari_0xB:
            init_success = init_BMC_1();
            break;
        case Ilari_0xC:
            init_success = init_BMC_2();
            break;
        case Pashli:
            init_success = init_BMC_3();
            break;
        case Namali:
            init_success = init_BMD_0();
            break;
        case Kogoli:
            init_success = init_BMD_1();
            break;
        default:
            init_success = false;
            break;
    }
    if(init_success){
    shape_angle = current.angle;
    }else{
        return false;
    }
    mStts.Init(iVar5,0xFF,this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);

    if(mbHasArms){
        mpArmMorf->setMorf(0.0f);

    }else{
        mpWingMorf->setMorf(0.0f);
    }
    mpHeadMorf->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 00001404-000017A8       .text setMtx__11daNpc_Bm1_cFb */
void daNpc_Bm1_c::setMtx(bool i_param_1) {
    
    if(mbInDemo == 0){
        int uVar5 = 0;
        plyTexPttrnAnm();
        if(mObjAcch.ChkGroundHit()){
            uVar5 = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
        }
        s8 reverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
        mbMorfAnimStopped = mpMorf->play(&eyePos,uVar5,reverb);
        if(mpMorf->getFrame() < mFrame){
            mbMorfAnimStopped = 1;
        }
        mFrame = mpMorf->getFrame();
        if(mbHasArms){
            mpArmMorf->play(&eyePos,0,0);
        }else{
            mpWingMorf->play(&eyePos,0,0);
        }
        mpHeadMorf->play(&eyePos,0,0);
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    if(!mbHasArms){
        mpWingMorf->calc();
    }else{
        mpArmMorf->calc();
    }
    mpHeadMorf->getModel()->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
    mpHeadMorf->calc();
    if(mpBinderModel){
        if(mBckResIndex == 4){
            mDoMtx_stack_c::copy(mpArmMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num));
            mDoMtx_stack_c::transM(13.5f,3.0f,-5.5f);
            mDoMtx_stack_c::XYZrotM(cM_deg2s(228),cM_deg2s(-114),cM_deg2s(-215));
            mpBinderModel->setBaseTRMtx(mDoMtx_stack_c::get());
        }else{
            mpBinderModel->setBaseTRMtx(mpArmMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num));
        }
        mpBinderModel->calc();
    }
    if(mpBagModel){
        mpBagModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_bbone_jnt_num));
        mpBagModel->calc();
    }
    if(mpKnifeModel){
        mpKnifeModel->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_bbone_jnt_num));
        mpKnifeModel->calc();
    }
    if(mbHasArms && mpStickModel){
        mpStickModel->setBaseTRMtx(mpArmMorf->getModel()->getAnmMtx(m_hnd_R_jnt_num));
        mpStickModel->calc();      
    }
    setPrtcl_Flyaway();
    setPrtcl_Land0();
    flwPrtcl_Hane0();
    flwPrtcl_Hane1();
    setAttention(i_param_1);
}

/* 000017A8-000017F8       .text anmNum_toResID__11daNpc_Bm1_cFi */
char* daNpc_Bm1_c::anmNum_toResID(int i_param_1) {
    
    static char* a_BCKName_TBL[0x16] = {"bm_dwait","bm_fly01","bm_lookup","bm_orooro","bm_wait01","bm_wait02","bm_talk01","bm_nadame","bm_gliding","bm_endurance","bm_flyaway","bm_flyaway2","bm_talk02","bm_landing","bm_walk","bm02_wait01","bm02_talk01","bm02_talk02","bm_talk03","bm_turn","bm_walk02","bm_check"};
    strcpy(l_BCKName,a_BCKName_TBL[i_param_1]);
    return strcat(l_BCKName,".bck");
}

/* 000017F8-00001848       .text headAnmNum_toResID__11daNpc_Bm1_cFi */
char* daNpc_Bm1_c::headAnmNum_toResID(int i_param_1) {
    
    static char* a_BCKName_TBL[0x16] = {"bmhead01_dwait","bmhead01_fly01","bmhead01_lookup","bmhead01_orooro","bmhead01_wait01","bmhead01_wait02","bmhead01_talk01","bmhead01_nadame","bmhead01_gliding","bmhead01_endurance","bmhead01_flyaway","bmhead01_flyaway2","bmhead01_talk02","bmhead01_landing","bmhead01_walk","bmhead01_wait01","bmhead01_wait01","bmhead01_wait01","bmhead01_talk03","bmhead01_turn","bmhead01_wait01","bmhead01_wait01"};
    strcpy(l_BCKName,a_BCKName_TBL[i_param_1]);
    return strcat(l_BCKName,".bck");
}

/* 00001848-00001898       .text wingAnmNum_toResID__11daNpc_Bm1_cFi */
char* daNpc_Bm1_c::wingAnmNum_toResID(int i_param_1) {
    
    static char* a_BCKName_TBL[0x16] = {"bmwing_dwait","bmwing_fly01","bmwing_lookup","bmwing_orooro","bmarm_wait01","bmarm_wait02","bmarm_talk01","bmarm_nadame","bmwing_gliding","bmwing_endurance","bmarm_flyaway","bmwing_flyaway2","bmarm_talk02","bmarm_landing","bmarm_walk","bmarm02_wait01","bmarm02_talk01","bmarm02_talk02","bmarm_talk03","bmarm_turn","bmarm_walk02","bmarm_check"};
    strcpy(l_BCKName,a_BCKName_TBL[i_param_1]);
    return strcat(l_BCKName,".bck");
}

/* 00001898-00001948       .text btpNum_toResID__11daNpc_Bm1_cFi */
char* daNpc_Bm1_c::btpNum_toResID(int i_param_1) {
    
    static char* a_BTPName_TBL[] = {"bmhead01"};
    static char* a_BTPName_TBL_2[] = {"bmhead01","bmhead01","bmhead01","bmhead01","bmhead01","bmhead02","bmhead02","bmhead07","bmhead07","bmhead05","bmhead03","bmhead04","bmhead04","bmhead09","bmhead06","bmhead04"};
    if(!strcmp(a_BTPName_TBL[i_param_1],"bmhead01")){
        strcpy(l_BTPName,a_BTPName_TBL_2[i_param_1]);
        return strcat(l_BTPName,".btp");
    }else{
        strcpy(l_BTPName,a_BTPName_TBL[i_param_1]);
        return strcat(l_BTPName,".btp");      
    }
}

/* 00001948-00001A4C       .text setBtp__11daNpc_Bm1_cFbi */
bool daNpc_Bm1_c::setBtp(bool i_param_1, int i_btp_num) {
    
    J3DModelData* model_data = mpHeadMorf->getModel()->getModelData();
    char* res_id = btpNum_toResID(i_btp_num);
    m_hed_tex_pttrn = reinterpret_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes(mArcName,res_id));
    JUT_ASSERT(0x529,m_hed_tex_pttrn != NULL);
    int iVar1 = mHeadBtpAnm.init(model_data,m_hed_tex_pttrn,1,2,1.0f,0,-1,i_param_1,0);
    bool o_retval = iVar1 == 1;
    if(o_retval){
        mBlinkFrame = 0;
        mBlinkTimer = 0;
    }
    return o_retval;
}

/* 00001A4C-00001A74       .text iniTexPttrnAnm__11daNpc_Bm1_cFb */
bool daNpc_Bm1_c::iniTexPttrnAnm(bool i_param_1) {
    return setBtp(i_param_1,m8F9);
}

/* 00001A74-00001B20       .text plyTexPttrnAnm__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::plyTexPttrnAnm() {
    
    if(m8F9 != 0 || !cLib_calcTimer(&mBlinkTimer)){
        mBlinkFrame += 1;
        if(mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()){
            if(m8F9 != 0){
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            }else{
                mBlinkTimer = cM_rndF(60.0f) + 30.0f;
                mBlinkFrame = 0;

            }
        }
    }
}

/* 00001B20-00001B5C       .text setAnm_tex__11daNpc_Bm1_cFSc */
void daNpc_Bm1_c::setAnm_tex(signed char i_param_1) {
    if(m8F9 != i_param_1){
        m8F9 = i_param_1;
        iniTexPttrnAnm(true);
    }
}

/* 00001B5C-00001CF4       .text setAnm_anm__11daNpc_Bm1_cFPQ211daNpc_Bm1_c9anm_prm_c */
BOOL daNpc_Bm1_c::setAnm_anm(daNpc_Bm1_c::anm_prm_c* i_anmPrmP) {

    if(mBckResIndex == i_anmPrmP->mBckResIndex){
        return 1;
    }
    mBckResIndex = i_anmPrmP->mBckResIndex;
    dNpc_setAnmFNDirect(mpMorf,i_anmPrmP->mLoopMode,i_anmPrmP->mMorf,i_anmPrmP->mSpeed,anmNum_toResID(mBckResIndex),NULL,mArcName);
    mbHasArms = i_anmPrmP->mbHasArms == 1;
    if(mbHasArms){
        dNpc_setAnmFNDirect(mpArmMorf,i_anmPrmP->mLoopMode,i_anmPrmP->mMorf,i_anmPrmP->mSpeed,wingAnmNum_toResID(mBckResIndex),NULL,mArcName);
    }else{
        dNpc_setAnmFNDirect(mpWingMorf,i_anmPrmP->mLoopMode,i_anmPrmP->mMorf,i_anmPrmP->mSpeed,wingAnmNum_toResID(mBckResIndex),NULL,mArcName);
 
    }
    dNpc_setAnmFNDirect(mpHeadMorf,i_anmPrmP->mLoopMode,i_anmPrmP->mMorf,i_anmPrmP->mSpeed,headAnmNum_toResID(mBckResIndex),NULL,mArcName);

    delPrtcl_Hane0();
    delPrtcl_Hane1();
    switch(mBckResIndex){
        case 2:
            setPrtcl_Hane1();
            break;
        case 3:
            setPrtcl_Hane0();
            break;
    }
    mFrame = 0;
    m87B = 0;
    mbMorfAnimStopped = 0;
    return TRUE;
}

/* 00001CF4-00001D60       .text setAnm_NUM__11daNpc_Bm1_cFii */
void daNpc_Bm1_c::setAnm_NUM(int i_param_1, int i_param_2) {
    
    static anm_prm_c a_anm_prm_tbl[0x17] = {
        { 0, 0,  0.0f, 1.0f, 2, 0 },
        { 1, 0,  8.0f, 1.0f, 2, 0 },
        { 2, 0,  8.0f, 1.0f, 0, 0 },
        { 3, 0,  6.0f, 1.8f, 2, 0 },
        { 4, 0,  8.0f, 1.0f, 2, 1 },
        { 5, 0,  8.0f, 1.0f, 2, 1 },
        { 6, 0,  8.0f, 1.0f, 2, 1 },
        { 7, 0,  8.0f, 1.0f, 2, 1 },
        { 8, 0,  8.0f, 1.0f, 2, 0 },
        { 9, 0,  8.0f, 1.0f, 2, 0 },
        {10, 0,  8.0f, 1.0f, 0, 1 },
        {11, 0,  0.0f, 1.0f, 0, 0 },
        {12, 0,  8.0f, 1.0f, 2, 1 },
        {13, 0,  8.0f, 1.0f, 0, 1 },
        {14, 0,  8.0f, 1.0f, 2, 1 },
        {15, 0, 12.0f, 1.0f, 2, 1 },
        {16, 0, 12.0f, 1.0f, 2, 1 },
        {17, 0, 12.0f, 1.0f, 2, 1 },
        {18, 0,  8.0f, 1.0f, 2, 1 },
        {19, 0,  8.0f, 1.0f, 0, 1 },
        {20, 0,  8.0f, 1.0f, 2, 1 },
        {21, 0,  8.0f, 1.0f, 2, 1 },
        { 6, 0, 20.0f, 1.0f, 2, 1 },
    };
    if(i_param_2 != 0){
        setAnm_tex(a_anm_prm_tbl[i_param_1].mResIndex);
    }
    setAnm_anm(&a_anm_prm_tbl[i_param_1]);
}

/* 00001D60-00001DE0       .text setAnm__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::setAnm() {
    
    static anm_prm_c a_anm_prm_tbl[] = {
        {-1, -1,  0.0f, 0.0f, -1, -1},
        { 0,  0,  0.0f, 1.0f,  2,  0},
        { 2,  0,  8.0f, 1.0f,  0,  0},
        { 3,  0,  6.0f, 1.8f,  2,  0},
        { 5,  0,  8.0f, 1.0f,  2,  1},
        {-1, -1,  0.0f, 0.0f, -1, -1},
        { 9,  0,  8.0f, 1.0f,  2,  0},
        {15,  0,  8.0f, 1.0f,  2,  1},
        {15,  0,  8.0f, 1.0f,  2,  1},
        {-1, -1,  0.0f, 0.0f, -1, -1},
        {10,  0,  8.0f, 1.0f,  0,  1},
        {-1, -1,  0.0f, 0.0f, -1, -1},
        { 4,  0,  8.0f, 1.0f,  2,  1},
        { 5,  0,  8.0f, 1.0f,  2,  1},
        { 4,  0,  8.0f, 1.0f,  2,  1},
        { 5,  0,  8.0f, 1.0f,  2,  1},
        {17,  0,  8.0f, 1.0f,  2,  1},
        {20,  0,  8.0f, 1.0f,  2,  1},
        {21,  0,  8.0f, 1.0f,  2,  1},
    };
    if(a_anm_prm_tbl[mStatus].mResIndex >= 0){
        setAnm_tex(a_anm_prm_tbl[mStatus].mResIndex);
    }
    if(a_anm_prm_tbl[mStatus].mBckResIndex >= 0){
        setAnm_anm(&a_anm_prm_tbl[mStatus]);
    }
    return true;
}

/* 00001DE0-00001E24       .text setPlaySpd__11daNpc_Bm1_cFf */
void daNpc_Bm1_c::setPlaySpd(float i_speed) {
    
    if(mbHasArms){
        mpArmMorf->setPlaySpeed(i_speed);
        mpHeadMorf->setPlaySpeed(i_speed);
        mpMorf->setPlaySpeed(i_speed);
        return;
    }else{
        mpWingMorf->setPlaySpeed(i_speed);
        mpHeadMorf->setPlaySpeed(i_speed);
        mpMorf->setPlaySpeed(i_speed);
    }
}

/* 00001E24-00001E28       .text chg_anmTag__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::chg_anmTag() {
    
}

/* 00001E28-00001E2C       .text control_anmTag__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::control_anmTag() {
    
}

/* 00001E2C-00001EFC       .text chg_anmAtr__11daNpc_Bm1_cFUc */
void daNpc_Bm1_c::chg_anmAtr(unsigned char i_param_1) {
    
    if(i_param_1 >= 0xF || i_param_1 == m8F7){
        return;
    }
    m8F7 = i_param_1;
    if(IamSukketo() || IamKakkuto()){
        switch(m8F7){
            case 9:
                mLookBackState = 1;
                m_jnt.setTrn();
                break;
            case 0xD:
                if(mPartnerProcID != -1){
                    fopAc_ac_c* actor = searchByID(mPartnerProcID);
                    mAttentionPos = actor->eyePos;
                    mLookBackState = 2;
                }
                break;
        }
    }
    setAnm_ATR(1);
}

/* 00001EFC-00001F68       .text control_anmAtr__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::control_anmAtr() {
    
    switch(m8F7){
        case 8:
            if(mbMorfAnimStopped != 0){
                if(++m87B >= 2){
                    m8F7 = 6;
                    setAnm_NUM(0x16,1);
                }
            }
            break;
        case 7:
        case 9:
            break;
    }
}

/* 00001F68-00001FD0       .text setAnm_ATR__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::setAnm_ATR(int i_param_1) {
    
    static anm_prm_c a_anm_prm_tbl[] = {
        { 4, 0,  8.0f, 1.0f, 2, 1 },
        { 1, 0,  8.0f, 1.0f, 2, 0 },
        { 0, 0,  6.0f, 1.0f, 2, 0 },
        { 2, 0,  8.0f, 1.0f, 0, 0 },
        { 3, 0,  8.0f, 1.8f, 2, 0 },
        { 5, 0, 12.0f, 1.0f, 2, 1 },
        { 6, 0,  8.0f, 1.0f, 2, 1 },
        { 7, 0,  8.0f, 1.0f, 2, 1 },
        { 7, 0,  5.0f, 1.0f, 2, 1 },
        {12, 0,  8.0f, 1.0f, 2, 1 },
        {15, 0, 12.0f, 1.0f, 2, 1 },
        {16, 0, 12.0f, 1.0f, 2, 1 },
        {17, 0, 12.0f, 1.0f, 2, 1 },
        { 6, 0,  8.0f, 1.0f, 2, 1 },
        {18, 0,  8.0f, 1.0f, 2, 1 },
    };
    if(i_param_1 != 0){
        setAnm_tex(a_anm_prm_tbl[m8F7].mResIndex);
    }
    setAnm_anm(&a_anm_prm_tbl[m8F7]);
}

/* 00001FD0-000020D8       .text anmAtr__11daNpc_Bm1_cFUs */
void daNpc_Bm1_c::anmAtr(unsigned short i_param_1) {
    dComIfG_MesgCamInfo_c* caminfo = dComIfGp_getMesgCameraInfo();
    if(mbManzai != 0 &&  this != caminfo->mActor[caminfo->mBasicID-1]){
        control_anmTag();
        control_anmAtr();
        return;
    }
    u32 uVar1;
    switch(i_param_1){
        case 0x6:
            if(m905 == 0){
                m8F7 = 0xFF;
                chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                m905 += 1;
            }   
            uVar1 = dComIfGp_getMesgAnimeTagInfo();
            dComIfGp_clearMesgAnimeTagInfo();
            if(uVar1 != 0xFF && m8F8 != uVar1){
                m8F8 = uVar1;
                chg_anmTag();
            }
            break;
        case 0xE:
            m905 = 0;
            break;
    }
    control_anmTag();
    control_anmAtr();

}

/* 000020D8-0000217C       .text eventOrder__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eventOrder() {
    s8 condition = m8FD;
    if(condition == 1 || condition == 2){
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(mSpecificType == Hoskit){
            eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
        }
        if(m8FD == 1){
            fopAcM_orderSpeakEvent(this);
        }
    }else if(condition >= 3){
        m86A = condition - 3;
        fopAcM_orderOtherEventId(this,m862[m86A]);
    }
}

/* 0000217C-00002234       .text checkOrder__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::checkOrder() {
    if(eventInfo.checkCommandDemoAccrpt()){
        if(dComIfGp_evmng_startCheck(m862[m86A])){
            switch(m86A){
                case 3:
                    fopAcM_OffStatus(this,fopAcStts_UNK4000_e);
                    break;
                case 2:
                    break;
            }
            m8FD = 0;
        }
    }else if(eventInfo.getCommand() == dEvtCmd_INTALK_e && (m8FD == 1 || m8FD == 2)){
        m8FD = 0;
        m895 = true;
    }
}

/* 00002234-00002304       .text chk_manzai__11daNpc_Bm1_cFv */
u8 daNpc_Bm1_c::chk_manzai() {
    u8 o_retval = 1;
    if(mPartnerProcID != -1){
        daNpc_Bm1_c* actor = static_cast<daNpc_Bm1_c*>(searchByID(mPartnerProcID));
        if(actor == NULL){
            return 0;
        }else{
            mbManzai = actor->getStt() == 9;
            if(mbManzai){
                dComIfGp_setMesgCameraInfoActor(this,actor,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
            }else{
                fopAcM_OnStatus(actor,fopAcStts_UNK4000_e);
                actor->set_manzai();
                o_retval = 0;
            }
        }
    }
    return o_retval;
}

/* 00002304-000023A0       .text chk_talk__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::chk_talk() {
    
    bool uVar3 = true;
    m87D = 0xFF;
    if(dComIfGp_event_chkTalkXY()){
            if(dComIfGp_evmng_ChkPresentEnd()){
                m87D = dComIfGp_event_getPreItemNo();

            }else{
                uVar3 = false;
            }

    }

    return uVar3;

}

/* 000023A0-000023E0       .text chk_partsNotMove__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::chk_partsNotMove() {
    return m85C == m_jnt.getHead_y() && m85E == m_jnt.getBackbone_y() && m860 == current.angle.y;
}

/* 000023E0-00002590       .text lookBack__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::lookBack() {
    
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz src_pos;
    s16 desiredYrot;
    m85C = m_jnt.getHead_y();
    m85E = m_jnt.getBackbone_y();
    m860 = current.angle.y;
    src_pos.x = current.pos.x;
    src_pos.y = current.pos.y;
    src_pos.z = current.pos.z;
    src_pos.y = eyePos.y;
    dstPos.set(0.0f,0.0f,0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = m896;

    switch(mLookBackState){
        case 1:
            dstPos = dNpc_playerEyePos(-20.0f);
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 2:
            dstPos = mAttentionPos;
            dstPos_p = &dstPos;
            src_pos.x = current.pos.x;
            src_pos.y = current.pos.y;
            src_pos.z = current.pos.z;
            src_pos.y = eyePos.y;
            break;
        case 3:
            desiredYrot = m876;
            break;
    }
    cLib_addCalcAngleS2(&mHeadLookAtMaxVel,l_HIO.children[mType-1].hio_prm.mCalcAngleTarget,4,0x800);
    if(!m_jnt.trnChk()){
        mHeadLookAtMaxVel = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y,dstPos_p,src_pos,desiredYrot,mHeadLookAtMaxVel,headOnlyFollow);
}

/* 00002590-00002A58       .text next_msgStatus__11daNpc_Bm1_cFPUl */
u16 daNpc_Bm1_c::next_msgStatus(unsigned long* i_msg_no) {
    
    u16 var_r0 = 0xF;
    switch (*i_msg_no) { 
    case 0x1771:
        *i_msg_no = 0x1772;
        break;
    case 0x1772:
        *i_msg_no = 0x1773;
        break;
    case 0x1773:
        *i_msg_no = 0x1774;
        break;
    case 0x1775:
        *i_msg_no = 0x1776;
        break;
    case 0x18A1:
        *i_msg_no = 0x18A2;
        break;
    case 0x5FE: 
        *i_msg_no = 0x5FF;
        break;
    case 0x601: 
        *i_msg_no = 0x602;
        break;
    case 0x602: 
        *i_msg_no = 0x603;
        break;
    case 0x603: 
        *i_msg_no = 0x604;
        break;
    case 0x604: 
        *i_msg_no = 0x605;
        break;
    case 0x186B:
        *i_msg_no = 0x186C;
        break;
    case 0x186C:
        *i_msg_no = 0x186D;
        break;
    case 0x186D:
        *i_msg_no = 0x186E;
        break;
    case 0x1873:
        *i_msg_no = 0x1874;
        break;
    case 0x1874:
        *i_msg_no = 0x1875;
        break;
    case 0x1875:
        *i_msg_no = 0x1876;
        break;
    case 0x187B:
        *i_msg_no = 0x187C;
        break;
    case 0x187C:
        *i_msg_no = 0x187D;
        break;
    case 0x187D:
        *i_msg_no = 0x187E;
        break;
    case 0x1883:
        *i_msg_no = 0x1884;
        break;
    case 0x1884:
        *i_msg_no = 0x1885;
        break;
    case 0x1885:
        *i_msg_no = 0x1886;
        break;
    case 0x186F:
        *i_msg_no = 0x1870;
        break;
    case 0x1870:
        *i_msg_no = 0x1871;
        break;
    case 0x1871:
        *i_msg_no = 0x1872;
        break;
    case 0x1877:
        *i_msg_no = 0x1878;
        break;
    case 0x1878:
        *i_msg_no = 0x1879;
        break;
    case 0x1879:
        *i_msg_no = 0x187A;
        break;
    case 0x187F:
        *i_msg_no = 0x1880;
        break;
    case 0x1880:
        *i_msg_no = 0x1881;
        break;
    case 0x1881:
        *i_msg_no = 0x1882;
        break;
    case 0x1887:
        *i_msg_no = 0x1888;
        break;
    case 0x1888:
        *i_msg_no = 0x1889;
        break;
    case 0x1889:
        *i_msg_no = 0x188A;
        break;
    case 0x18A6:
        *i_msg_no = 0x18A7;
        break;
    case 0x18BC:
        *i_msg_no = 0x18BD;
        break;
    case 0x1996:
        *i_msg_no = 0x1997;
        break;
    case 0x1998:
        *i_msg_no = 0x1999;
        break;
    case 0x199E:
        *i_msg_no = 0x199F;
        break;
    case 0x199F:
        if(dComIfGs_getBeastNum(2) >= 0x14){
            *i_msg_no = 0x19A1;
        }else{
            *i_msg_no = 0x19A0;
        }
        break;
    case 0x19A1:

        switch (mpCurrMsg->mSelectNum) { 
        case 0:
            *i_msg_no = 0x19A3;
            dComIfGp_setItemBeastNumCount(2,-0x14);
            break;
        case 1: 
            *i_msg_no = 0x19A2;
            break;
        }
        break;
    case 0x19A3:
        *i_msg_no = 0x19A4;
        break;
    case 0x1EF0:
        *i_msg_no = 0x1EF1;
        break;
    case 0x1EF1:
        *i_msg_no = 0x1EF2;
        break;
    case 0x1EF2:
        *i_msg_no = 0x1EF3;
        break;
    case 0x1EF3:
        *i_msg_no = 0x1EF4;
        break;
    case 0x1EF4:
        *i_msg_no = 0x1EF5;
        break;
    case 0x1EF5:
        switch (mpCurrMsg->mSelectNum) { 
        case 0:
            *i_msg_no = 0x1EF6;
            break;
        case 1: 
            *i_msg_no = 0x1EF8;
            break;
        }
        break;
    default:    
        var_r0 = 0x10;
        break;
    }
    return var_r0;
}

/* 00002A58-00002AC4       .text getBitMask__11daNpc_Bm1_cFv */
s8 daNpc_Bm1_c::getBitMask() {
    s8 o_retval = 0;
    switch(mSpecificType){
        case Basht:
            o_retval = 1;
            break;
        case Bisht:
            o_retval = 2;
            break;
        case Pashli:
            o_retval = 4;
            break;
        case Namali:
            o_retval = 8;
            break;
        case Kogoli:
            o_retval = 0x10;
            break;
    }
    return o_retval;
}

/* 00002AC4-00002B00       .text getMsg_PST_1__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_PST_1() {
    
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1401) ? 0xC93 : 0xC92;
}

/* 00002B00-00002B40       .text getMsg_PST_3__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_PST_3() {
    
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_2202) ? 0x18A3 : 0x18A1;
}

/* 00002B40-00002BE8       .text getMsg_SKT_0__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_SKT_0() {
    

    u32 o_retval;
    if(dComIfGs_isSymbol(1)){
        if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A80)){
            o_retval = 0x186B;
            return o_retval;
        }
        else if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1820)){
            o_retval = 0x1873;
            return o_retval;
        }
        else{
            return !dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) ? 0x187B : 0x1883;
        }
    }
    return 0;
}

/* 00002BE8-00002C90       .text getMsg_KKT_0__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_KKT_0() {
    
    u32 o_retval;
    if(dComIfGs_isSymbol(1)){
        if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A80)){
            o_retval = 0x186F;
            return o_retval;
        }
        else if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1820)){
            o_retval = 0x1877;
            return o_retval;
        }
        else{
            return !dComIfGs_isEventBit(dSv_event_flag_c::UNK_2E04) ? 0x187F : 0x1887;
        }
    }
    return 0;
}

/* 00002C90-00002DBC       .text getMsg_BMB_0__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMB_0() {
    
    s8 reg = dComIfGs_getEventReg(0xB8FF);
    s8 mask = getBitMask();
    u32 var_r29 = 0;
    if (reg&mask) {
        switch (mSpawnCondition) {
            case 1:
                var_r29 = 0x18A0;
                break;
            case 2:
                var_r29 = 0x18B1;
                break;
            case 3:
                var_r29 = 0x18B3;
                break;
            case 4:
                var_r29 = 0x18B5;
                break;
        }
    } else {
        switch (mSpawnCondition) {
            case 1:
                var_r29 = 0x189F;
                break;
            case 2:
                var_r29 = 0x18B0;
                break;
            case 3:
                var_r29 = 0x18B2;
                break;
            case 4:
                var_r29 = 0x18B4;
                break;
        }
    }
    if (var_r29) {
        u16 i_no = reg | mask;
        dComIfGs_setEventReg(0xB8FF, i_no);
    }
    return var_r29;
}

/* 00002DBC-00002EE8       .text getMsg_BMB_1__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMB_1() {
    
    s8 reg = dComIfGs_getEventReg(0xB8FF);
    s8 mask = getBitMask();
    u32 var_r29 = 0;
    if (reg&mask) {
        switch (mSpawnCondition) {
        case 1:
            var_r29 = 0x18A9;
            break;
        case 2:
            var_r29 = 0x18BF;
            break;
        case 3:
            var_r29 = 0x18C1;
            break;
        case 4:
            var_r29 = 0x18C3;
            break;
        }
    } else {
        switch (mSpawnCondition) {
        case 1:
            var_r29 = 0x18A8;
            break;
        case 2:
            var_r29 = 0x18BE;
            break;
        case 3:
            var_r29 = 0x18C0;
            break;
        case 4:
            var_r29 = 0x18C2;
            break;
        }
    }
    if (var_r29 != 0U) {
        u16 i_no = reg | mask;
        dComIfGs_setEventReg(0xB8FF, i_no);
    }
    return var_r29;
}

/* 00002EE8-00003010       .text getMsg_BMB_2__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMB_2() {
    
    if(m87C != 0){
        return 0x199C;
    }
    if(m87D == 0x47){
        if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_2180)){
            return 0x199D;
        }
        if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_2140)){
            return (dComIfGs_getBeastNum(2) >= 0x14) ? 0x19A1: 0x19A0;
        }
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_2140);
        return 0x199E;
    }
    else if(m87D != 0xFF){
        return 0x19A5;
    }
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_2180)){
        return 0x199B;
    }
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_2001)){
        return 0x199A;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_2120)? 0x1998 : 0x1996;


}

/* 00003010-00003058       .text getMsg_BMC_0__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMC_0() {

    switch(mSpawnCondition){
        case 1:
            return 0x18A6;
        case 2:
            return 0x18BA;
        case 3:
            return 0x18BC;
        case 4:
            break;
    }
    return 0;

}

/* 00003058-000030D0       .text getMsg_BMC_2__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMC_2() {
    
    if(m87C != 0){
        return 0x1EF7;
    }
    if(dComIfGs_isGetItemReserve(0xF)){
        return 0x1EF9;
    }
    return dComIfGs_isEventBit(dSv_event_flag_c::UNK_1908) ? 0x1EF2 : 0x1EF0;
}

/* 000030D0-000031FC       .text getMsg_BMC_3__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMC_3() {
    
    s8 reg = dComIfGs_getEventReg(0xB8FF);
    s8 mask = getBitMask();
    u32 var_r29 = 0;
    if (reg&mask) {
        switch (mSpawnCondition) {
        case 1:
            var_r29 = 0x18C5;
            break;
        case 2:
            var_r29 = 0x18C7;
            break;
        case 3:
            var_r29 = 0x18C9;
            break;
        case 4:
            var_r29 = 0x18CB;
            break;
        }
    } else {
        switch (mSpawnCondition) {
        case 1:
            var_r29 = 0x18C4;
            break;
        case 2:
            var_r29 = 0x18C6;
            break;
        case 3:
            var_r29 = 0x18C8;
            break;
        case 4:
            var_r29 = 0x18CA;
            break;
        }
    }
    if (var_r29 != 0U) {
        u16 i_no = reg | mask;
        dComIfGs_setEventReg(0xB8FF, i_no);
    }
    return var_r29;
}

/* 000031FC-00003328       .text getMsg_BMD_0__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMD_0() {
    
    s8 reg = dComIfGs_getEventReg(0xB8FF);
    s8 mask = getBitMask();
    u32 var_r29 = 0;
    if (reg&mask) {
        switch (mSpawnCondition) {
        case 1:
            var_r29 = 0x189E;
            break;
        case 2:
            var_r29 = 0x18AB;
            break;
        case 3:
            var_r29 = 0x18AD;
            break;
        case 4:
            var_r29 = 0x18AF;
            break;
        }
    } else {
        switch (mSpawnCondition) {
        case 1:
            var_r29 = 0x189D;
            break;
        case 2:
            var_r29 = 0x18AA;
            break;
        case 3:
            var_r29 = 0x18AC;
            break;
        case 4:
            var_r29 = 0x18AE;
            break;
        }
    }
    if (var_r29 != 0U) {
        u16 i_no = reg | mask;
        dComIfGs_setEventReg(0xB8FF, i_no);
    }
    return var_r29;
}

/* 00003328-00003470       .text getMsg_BMD_1__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMD_1() {
    
    s8 reg = dComIfGs_getEventReg(0xB8FF);
    s8 mask = getBitMask();
    u32 var_r29 = 0;
    if (reg&mask) {
        if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1820)){
            var_r29 = 0x18A5;
        }else{
            switch (mSpawnCondition) {
            case 1:
            case 2:
                var_r29 = 0x18A5;
                break;
            case 3:
                var_r29 = 0x18B7;
                break;
            case 4:
                var_r29 = 0x18B9;
                break;
            }
        }
    } else {
        if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1820) ){
            var_r29 = 0x18A4;
        }else{
            switch (mSpawnCondition) {
            case 1:
            case 2:
                var_r29 = 0x18A4;
                break;
            case 3:
                var_r29 = 0x18B6;
                break;
            case 4:
                var_r29 = 0x18B8;
                break;
            }
        }
    }
    if (var_r29 != 0U) {
        u16 i_no = reg | mask;
        dComIfGs_setEventReg(0xB8FF, i_no);
    }
    return var_r29;
}

/* 00003470-00003548       .text getMsg__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg() {

    u32 o_retval = 0;
    switch(this->mSpecificType) {
    case Quill_1:
        o_retval = getMsg_PST_1();
        break;
    case Quill_3:
        o_retval = getMsg_PST_3();
        break;
    case Skett:
        o_retval = getMsg_SKT_0();
        break;
    case Akoot:
        o_retval = getMsg_KKT_0();
        break;
    case Basht:
        o_retval = getMsg_BMB_0();
        break;
    case Bisht:
        o_retval = getMsg_BMB_1();
        break;
    case Hoskit:
        o_retval = getMsg_BMB_2();
        break;
    case Ilari_0xA:
        o_retval = getMsg_BMC_0();
        break;
    case Ilari_0xC:
        o_retval = getMsg_BMC_2();
        break;
    case Pashli:
        o_retval = getMsg_BMC_3();
        break;
    case Namali:
        o_retval = getMsg_BMD_0();
        break;
    case Kogoli:
        o_retval = getMsg_BMD_1();
    }
    return o_retval;
}

/* 00003548-000035C8       .text chkAttention__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::chkAttention() {
    
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }

}

/* 000035C8-00003630       .text setAttention__11daNpc_Bm1_cFb */
void daNpc_Bm1_c::setAttention(bool i_setEyePos) {
    
    f32 l_hio_offset = l_HIO.children[mType-1].hio_prm.mAttPosOffsetY;
    attention_info.position.set(
        current.pos.x,
        current.pos.y + l_hio_offset,
        current.pos.z
    );
    if (!mbSetEyePos && !i_setEyePos) {
        return;
    }

    eyePos.set(
        mEyePos.x,
        mEyePos.y,
        mEyePos.z
    );
}

/* 00003630-00003664       .text searchByID__11daNpc_Bm1_cFUi */
fopAc_ac_c* daNpc_Bm1_c::searchByID(fpc_ProcID i_procID) {
    
    fopAc_ac_c* o_actor = NULL;
    fopAcM_SearchByID(i_procID,&o_actor);
    return o_actor;
}

/* 00003664-00003714       .text partner_srch_sub__11daNpc_Bm1_cFPFPvPv_Pv */
bool daNpc_Bm1_c::partner_srch_sub(void* (*i_searchFunc)(void*, void*)) {
    
    bool o_retval = false;
    mPartnerProcID = -1;
    l_check_wrk = 0;
    for(int i = 0; i < 20; i++){
        l_check_inf[i] = 0;
    }
    fpcM_Search(i_searchFunc,this);
    if(l_check_wrk != 0){
        mPartnerProcID = fopAcM_GetID(l_check_inf[0]);     
        o_retval = true;
    }
    return o_retval;
}

/* 00003714-00003818       .text partner_srch__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::partner_srch() {
    
    bool found_partner = false;
    if(m904 == 1){
        switch(mSpecificType){
            case Quill_1:
                found_partner = partner_srch_sub(searchActor_Zl);
                break;
            case Skett:
                found_partner = partner_srch_sub(searchActor_Bm_Kkt);
                break;
            case Akoot:
                found_partner = partner_srch_sub(searchActor_Bm_Skt);
                break;
            case Ilari_0xB:
                if(partner_srch_sub(searchActor_Gp) ){
                    fopAc_ac_c* actor = searchByID(mPartnerProcID);
                    if(actor){
                        current.angle.y = cLib_targetAngleY(&current.pos,&actor->current.pos);
                    }
                    found_partner = true;
                    break;
                }
        }
        if(found_partner){
            m904 += 1;
        }
    }
}

/* 00003818-00003A24       .text bm_movPass__11daNpc_Bm1_cFb */
u32 daNpc_Bm1_c::bm_movPass(bool i_param_1) {
    
    cXyz cmpCoords;
    cXyz idxCoords;
    u8 point_idx;
    u32 o_retval = 0;
    f32 dist_xz;
    if(mPathRun.isPath() && (point_idx = mPathRun.getIdx(),dPath_ChkClose(mPathRun.getPath()))){
        if(mPathRun.chkPointPass(current.pos,mPathRun.getDir())){
            mPathRun.nextIdxAuto();
            o_retval = 1;
            if(i_param_1){
                goto block_18c;
            }
        }
        return o_retval;


    }

    dist_xz = (mTargetPos - current.pos).absXZ();
    if( dist_xz <= m858){
        o_retval = 1;
        if(mPathRun.isPath()){
            if(point_idx < mPathRun.maxPoint()-2){
                mPathRun.nextIdxAuto();
            }else{
                o_retval = 2;
            }

        }
        if(i_param_1 != 0){
            goto block_18c;
        }

    }
    return o_retval;
    
block_18c:
    u8 idx = mPathRun.getIdx();
    idxCoords = mPathRun.getPoint(idx);
    cmpCoords = mPathRun.getPoint(point_idx);
    m889 = cmpCoords.y <= idxCoords.y;

    return o_retval;
}

/* 00003A24-00003A68       .text bm_setFlyAnm__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_setFlyAnm() {
    
    if(m889){
        setAnm_NUM(9,1);
    }else{
        setAnm_NUM(8,1);
    }
}

/* 00003A68-00003BF0       .text bm_clcFlySpd__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_clcFlySpd() {
    
    s16 target;
    if(m8F4 == 2 || m8F4 == 5){
        target = cLib_targetAngleY(&current.pos,&mTargetPos);
        cLib_addCalcAngleS(&current.angle.y,target,l_HIO.children[mType-1].hio_prm.mFlyScale,l_HIO.children[mType-1].hio_prm.mFlyMaxStep,0);
    }
    switch(m8F4){

        case 3:
            speed.y -= mFlyAccelY;
            break;
        case 2:
        case 5:

            if(m889 != 0){
                if (mTargetPos.y > current.pos.y) {

                    speed.y = cLib_maxLimit(speed.y + mFlyAccelY,mFlySpeedY);
                } else {
                    speed.y = cLib_minLimit(speed.y - mFlyAccelY,0.0f);
                }
            }else if(mTargetPos.y > current.pos.y){
                speed.y = cLib_maxLimit(speed.y + mFlyAccelY,0.0f);
            }else{
                speed.y -= mFlyAccelY;
            }
            break;    
        case 0:
        case 1:
            break;
    }
    cLib_chaseF(&speedF,mTargetFlySpeed,mTargetFlyStep);

}

/* 00003BF0-00003C64       .text bm_clcMovSpd__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_clcMovSpd() {
    
    s16 target = cLib_targetAngleY(&current.pos,&mTargetPos);
    cLib_addCalcAngleS(&current.angle.y,target,l_HIO.children[mType-1].hio_prm.m34,l_HIO.children[mType-1].hio_prm.m36,0);
    cLib_chaseF(&speedF,mTargetFlySpeed,mTargetFlyStep);
}

/* 00003C64-00003ED4       .text bm_flyMove__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::bm_flyMove() {

    s32 temp_r3;

    if (m8F4 == 0) {
        return false;
    }
    if (m88A != 0) {
        m887 = 1;
        return true;
    }
    if (mPathRun.isPath()) {
        mTargetPos = mPathRun.getPoint(mPathRun.getIdx());
    }
    switch (m8F4) {
    case 1:    
        if ((s32) mBckResIndex != 0xA) {
            setAnm_NUM(0xA, 1);
        } else if (mbMorfAnimStopped != 0) {
            m8F4 = 2;
        }
        break;
    case 2:    
        if (mBckResIndex != 0xB) {
            setAnm_NUM(0xB, 1);
            speed.y = mTargetFlySpeed * 0.7f;
        } else if (mbMorfAnimStopped != 0) {
            m8F4 = 5;
            m88A = 1;
            bm_setFlyAnm();
        }
        goto case_5;
    case 3:    
        setAnm_NUM(9, 1);
        if (!mObjAcch.ChkGroundHit() != 0) {
            bm_clcFlySpd();
        } else {
            m8F4 = 4;
            speedF = 0.0f;
            speed.y = 0.0f;
            m88A = 1;
        }
        break;


    case 4:    
        if ((s32) mBckResIndex != 0xD) {
            setAnm_NUM(0xD, 1);
        } else if ((s8) mbMorfAnimStopped != 0) {
            gravity = -4.5f;
            setAnm_NUM(4, 1);
            m8F4 = 0;
            m88A = 1;
        }

        break;
    case 5:    
case_5:
        bm_clcFlySpd();
        temp_r3 = bm_movPass(1);
        switch (temp_r3) {
        case 1:
            if (m8F4 != 2) {
                bm_setFlyAnm();
                m8F4 = 5;
            }
            m88A = 1;
            break;
        case 2:
            m8F4 = 3;
            mTargetFlySpeed = 0.0f;
            m88A = 1;
            break;
        }
        break;
    }
    return TRUE;
}

/* 00003ED4-00003FA4       .text bm_nMove__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_nMove() {
    
    if(m88B){
        m887 = 1;
        return;
    }
    switch(mBckResIndex){
        case 0x14:
        case 0xE:
            bm_clcMovSpd();
            f32 speed = speedF * l_HIO.children[mType-1].hio_prm.m38;
            if(speed < 0.5f){
                speed = 0.5f;
            }
            setPlaySpd(speed);
            s32 iVar3 = bm_movPass(false);
            if(3 <= iVar3 || iVar3 < 1){ 
                return;
            }
            m88B = 1;
    }
}

/* 00003FA4-000040EC       .text setPrtcl_Flyaway__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Flyaway() {
    

    if (mBckResIndex == 0xB && mpMorf->checkFrame(10.0f)){
#if VERSION == VERSION_DEMO
            JGeometry::TVec3<f32> direction(-1.0f,1.0f,0.0f);
#endif
        delPrtcl_Flyaway();
        mpFlyawayEmitterL = dComIfGp_particle_set(
            dPa_name::ID_IT_SN_BM_HANEL_FLYAWAY00,
            &mWingLPos,
            &current.angle,
            NULL,
            -1,NULL,fopAcM_GetRoomNo(this),
            &tevStr.mColorK0,
            &tevStr.mColorK0
        );

        mpFlyawayEmitterR = dComIfGp_particle_set(
            dPa_name::ID_IT_SN_BM_HANEL_FLYAWAY00,
            &mWingRPos,
            &current.angle,
            NULL,-1,NULL,fopAcM_GetRoomNo(this),
            &tevStr.mColorK0,
            &tevStr.mColorK0
        );
#if VERSION > VERSION_DEMO
        if (mpFlyawayEmitterL != NULL) {
            mpFlyawayEmitterL->setStatus(0x40);
        }

        if (mpFlyawayEmitterR != NULL) {
            JGeometry::TVec3<f32> rot(-1.0f,1.0f,0.0f);
            mpFlyawayEmitterR->setStatus(0x40);
            mpFlyawayEmitterR->setDirection(rot);
        }
#else
        if(mpFlyawayEmitterR != NULL){
            mpFlyawayEmitterR->setDirection(direction);
        }
#endif
    }
}

/* 000040EC-00004160       .text delPrtcl_Flyaway__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Flyaway() {
    

    if(mpFlyawayEmitterL){
#if VERSION > VERSION_DEMO
        mpFlyawayEmitterL->clearStatus(0x40);
#endif
        mpFlyawayEmitterL->becomeInvalidEmitter();
        mpFlyawayEmitterL = NULL;
    }

    if(mpFlyawayEmitterR){
#if VERSION > VERSION_DEMO
        mpFlyawayEmitterR->clearStatus(0x40);
#endif
        mpFlyawayEmitterR->becomeInvalidEmitter();
        mpFlyawayEmitterR = NULL;
    }
}

/* 00004160-000042A8       .text setPrtcl_Land0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Land0() {
    
    if (mBckResIndex == 0xD && mpMorf->checkFrame(1.0f)){
#if VERSION == VERSION_DEMO
        JGeometry::TVec3<f32> direction(-1.0f,0.5f,0.0f);
#endif
        delPrtcl_Land0();
        mpLandEmitterL = dComIfGp_particle_set(
            dPa_name::ID_IT_SN_BM_HANEL_LAND00,
            &mArmLPos,
            &current.angle,
            NULL,
            0xFF,
            NULL,
            fopAcM_GetRoomNo(this),
            &tevStr.mColorK0,
            &tevStr.mColorK0
        );

        mpLandEmitterR = dComIfGp_particle_set(
            dPa_name::ID_IT_SN_BM_HANEL_LAND00,
            &mArmRPos,
            &current.angle,
            NULL,
            0xFF,
            NULL,
            fopAcM_GetRoomNo(this),
            &tevStr.mColorK0,
            &tevStr.mColorK0
        );

#if VERSION > VERSION_DEMO
        if (mpLandEmitterL != NULL) {
            mpLandEmitterL->setStatus(0x40);
        }

        if (mpLandEmitterR != NULL) {
            JGeometry::TVec3<f32> rot(-1.0f,0.5f,0.0f);
            mpLandEmitterR->setStatus(0x40);
            mpLandEmitterR->setDirection(rot);
        }
#else
        if(mpLandEmitterR != NULL){
            mpLandEmitterR->setDirection(direction);
        }
#endif
    }
}

/* 000042A8-0000431C       .text delPrtcl_Land0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Land0() {
    
    if(mpLandEmitterL){
#if VERSION > VERSION_DEMO
        mpLandEmitterL->clearStatus(0x40);
#endif
        mpLandEmitterL->becomeInvalidEmitter();
        mpLandEmitterL = NULL;
    }

    if(mpLandEmitterR){
#if VERSION > VERSION_DEMO
        mpLandEmitterR->clearStatus(0x40);
#endif
        mpLandEmitterR->becomeInvalidEmitter();
        mpLandEmitterR = NULL;
    }
}

/* 0000431C-000043E0       .text setPrtcl_Hane0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Hane0() {

    delPrtcl_Hane0();
    mpFeatherEmitterL = dComIfGp_particle_set(
        dPa_name::ID_IT_SN_TORIZOKU_HANE00,
        &current.pos,
        NULL,
        NULL,
        0xFF,
        NULL,
        fopAcM_GetRoomNo(this),
        NULL,
        NULL
    );

    mpFeatherEmitterR = dComIfGp_particle_set(
        dPa_name::ID_IT_SN_TORIZOKU_HANE00,
        &current.pos,
        NULL,
        NULL,
        0xFF,
        NULL,
        fopAcM_GetRoomNo(this),
        NULL,
        NULL
    );


}

/* 000043E0-00004470       .text flwPrtcl_Hane0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::flwPrtcl_Hane0() {

    if(mpFeatherEmitterL){
        mpFeatherEmitterL->setGlobalRTMatrix(mpWingMorf->getModel()->getAnmMtx(m_wngL3_jnt_num));
    }
    if(mpFeatherEmitterR){
        mpFeatherEmitterR->setGlobalRTMatrix(mpWingMorf->getModel()->getAnmMtx(m_wngR3_jnt_num));
    }
}

/* 00004470-000044C4       .text delPrtcl_Hane0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Hane0() {


    if(mpFeatherEmitterL){
        mpFeatherEmitterL->becomeInvalidEmitter();
        mpFeatherEmitterL = NULL;
    }
    
    if(mpFeatherEmitterR){
        mpFeatherEmitterR->becomeInvalidEmitter();
        mpFeatherEmitterR = NULL;
    }

}

/* 000044C4-000045B8       .text setPrtcl_Hane1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Hane1() {
    
    delPrtcl_Hane1();
    mpFeather1EmitterL = dComIfGp_particle_set(
        0x80DB,
        &current.pos,
        NULL,
        NULL,
        0xFF,
        NULL,
        fopAcM_GetRoomNo(this),
        NULL,
        NULL
    );
#if VERSION > VERSION_DEMO
    if(mpFeather1EmitterL){
        mpFeather1EmitterL->setStatus(0x40);
    }
#endif
    mpFeather1EmitterR = dComIfGp_particle_set(
        0x80DB,
        &current.pos,
        NULL,
        NULL,
        0xFF,
        NULL,
        fopAcM_GetRoomNo(this),
        NULL,
        NULL
    );
#if VERSION > VERSION_DEMO
    if(mpFeather1EmitterR){
        mpFeather1EmitterR->setStatus(0x40);
    }
#endif
}

/* 000045B8-00004648       .text flwPrtcl_Hane1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::flwPrtcl_Hane1() {
    
    if(mpFeather1EmitterL){
        mpFeather1EmitterL->setGlobalRTMatrix(mpWingMorf->getModel()->getAnmMtx(m_wngL3_jnt_num));
    }
    if(mpFeather1EmitterR){
        mpFeather1EmitterR->setGlobalRTMatrix(mpWingMorf->getModel()->getAnmMtx(m_wngR3_jnt_num));
    }
}

/* 00004648-000046BC       .text delPrtcl_Hane1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Hane1() {
    
    if(mpFeather1EmitterL){
#if VERSION > VERSION_DEMO
        mpFeather1EmitterL->clearStatus(0x40);
#endif
        mpFeather1EmitterL->becomeInvalidEmitter();
        mpFeather1EmitterL = NULL;
    }
    if(mpFeather1EmitterR){
#if VERSION > VERSION_DEMO
        mpFeather1EmitterR->clearStatus(0x40);
#endif
        mpFeather1EmitterR->becomeInvalidEmitter();
        mpFeather1EmitterR = NULL;
    }
}

/* 000046BC-000049B8       .text decideType__11daNpc_Bm1_cFii */
bool daNpc_Bm1_c::decideType(int i_type_param, int i_spawn_cond_param) {
    
    mSpawnCondition = 0;
    mType = t_Invalid;
    mSpecificType = Invalid;
    fpc_ProcID procName = fopAcM_GetName(this);
    switch(procName){
    case DEMO_SELECT(0x149,0x148):
        mType = 1;
        switch (i_type_param) {   
        case 0:
            mSpecificType = 0;
            break;
        case 1: 
            mSpecificType = 1;
            break;
        case 2:        
            mSpecificType = 2;
            break;
        case 3:
            mSpecificType = 3;
            break;
        case 4:
            mSpecificType = 4;
            break;
        default:
            return false;
        }
        break;
    case DEMO_SELECT(0x14A,0x149):
        switch (i_type_param) {
        case 0:
            mSpecificType = 6;
            mType = 3;
            break;
        case 1:
            mSpecificType = 5;
            mType = 2;
            break;
        default:
            return false;
        }
        break;
    case DEMO_SELECT(0x14B,0x14A):
        switch (i_type_param) {
        case 0:
            mSpecificType = 7;
            mType = 4;
            break;
        case 1:
            mSpecificType = 8;
            mType = 5;
            break;
        case 2:
            mSpecificType = 9;
            mType = 6;
            break;
        default: 
            return false;
        }
        break;
    case DEMO_SELECT(0x14C,0x14B):
        switch (i_type_param) { 
        case 0: 
            mSpecificType = 0xA;
            mType = 7;
            break;
        case 1: 
            mSpecificType = 0xB;
            mType = 7;
            break;
        case 2: 
            mSpecificType = 0xC;
            mType = 7;
            break;
        case 3: 
            mSpecificType = 0xD;
            mType = 8;
            break;
        default:
            return false;
        }
        break;
    case DEMO_SELECT(0x14D,0x14C):
        switch (i_type_param) {
        case 0: 
            mSpecificType = 0xE;
            mType = 9;
            break;
        case 1: 
            mSpecificType = 0xF;
            mType = 0xA;
            break;
        default:
            return false;
        }
        break;
    default:   
        return false;
    }

    switch (i_spawn_cond_param) {
    case 0: 
        mSpawnCondition = 1;
        break;
    case 1: 
        mSpawnCondition = 2;
        break;
    case 2: 
        mSpawnCondition = 3;
        break;
    case 3: 
        mSpawnCondition = 4;
        break;
    }
    switch(mSpecificType){
        case Quill_0:
            strcpy(mArcName, "Bm2");
            break;
        case Quill_1:
        case Quill_2:
        case Quill_3:
        case Quill_4:
        case Akoot:
        case Skett:
        case Basht:
        case Bisht:
        case Hoskit:
        case Ilari_0xA:
        case Ilari_0xB:
        case Ilari_0xC:
        case Pashli:
        case Namali:
        case Kogoli:
            strcpy(mArcName, "Bm");
            break;
        default:
            return false;
    }
    return true;
}

/* 000049B8-000049FC       .text eInit_setLocFlag__11daNpc_Bm1_cFPi */
void daNpc_Bm1_c::eInit_setLocFlag(int* i_param_1) {
    
    m896 = false;
    if(i_param_1 == NULL){
        return;
    }
    switch(*i_param_1){
        case 2:
            m_jnt.setTrn();
            return;
        case 1:
            m896 = true;
            return;        
    }
}

/* 000049FC-00004A34       .text eInit_setShapeAngleY__11daNpc_Bm1_cFPis */
void daNpc_Bm1_c::eInit_setShapeAngleY(int* i_setShapeAngle, short i_shapeAngle) {
    
    mbSetShapeAngle = false;
    if(i_setShapeAngle == NULL){
        return;
    }
    mbSetShapeAngle = *i_setShapeAngle == 1;
    if(!mbSetShapeAngle){
        return;
    }
    shape_angle.y = i_shapeAngle;
    return;
}

/* 00004A34-00004A50       .text eInit_setEvTimer__11daNpc_Bm1_cFPi */
void daNpc_Bm1_c::eInit_setEvTimer(int* i_param_1) {
    
    m86C = false;
    if(i_param_1 == NULL){
        return;
    }
    m86C = *i_param_1;
    return;
}

/* 00004A50-00004B30       .text eInit_calcRelativPos__11daNpc_Bm1_cFP4cXyzPi */

cXyz daNpc_Bm1_c::eInit_calcRelativPos(cXyz* i_param_2, int* arg2) {
    
    s16 sVar1;
    if(arg2){
        sVar1 = shape_angle.y + (s16)*arg2;
    }else{
        sVar1 = shape_angle.y;
    }
    cXyz local_1c;
    cXyz local_28;
    if(i_param_2){
        local_1c.set(
            i_param_2->x,
            i_param_2->y,
            i_param_2->z
        );

    }else{
        local_1c.set(0.0f,0.0f,0.0f);
    }
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(sVar1);
    mDoMtx_stack_c::multVec(&local_1c,&local_28);
    return local_28; 
}

/* 00004B30-00004D10       .text eInit_ATTENTION___11daNpc_Bm1_cFPiPiPiP4cXyzPiPiPi */
void daNpc_Bm1_c::eInit_ATTENTION_(int* i_prm_0_p, int* i_prm_1_p, int* i_prm_2_p, cXyz* i_offset_p, int* i_angle_p, int* i_index_p, int* i_timer_p) {
    
    u8 pointIndex;
    s16 unaff_r27;
    fopAc_ac_c* iVar1;
    if (!i_prm_0_p) {
        return;
    }
    switch(*i_prm_0_p) {
    case 0:
        break;
    case 1:
        mLookBackState = 1;
        unaff_r27 = cLib_targetAngleY(&current.pos,&dComIfGp_getLinkPlayer()->current.pos);
        break;
    case 2:
        if (!i_offset_p) {
        return;
        }
        mLookBackState = 2;
        unaff_r27 = cLib_targetAngleY(&current.pos,i_offset_p);
        break;
    case 3:
        mLookBackState = 2;
        mAttentionPos = eInit_calcRelativPos(i_offset_p,i_angle_p);
        unaff_r27 = cLib_targetAngleY(&current.pos,&mAttentionPos);
        break;
    case 4:
        if (i_angle_p == (int *)0x0) {
            return;
        }
        mLookBackState = 3;
        unaff_r27 = *i_angle_p;
        break;
    case 5:
        if (mPathRun.isPath() == 0) {
            return;
        }
        pointIndex = mPathRun.getIdx();
        if (i_index_p) {
        pointIndex = *i_index_p;
        }
        mAttentionPos = mPathRun.getPoint(pointIndex);
        mLookBackState = 2;
        break;
    case 6:
        iVar1 = searchByID(mPartnerProcID);
        if (iVar1 == NULL) {
            return;
        }
        mLookBackState = 2;
        mAttentionPos = iVar1->eyePos;
        unaff_r27 = cLib_targetAngleY(&current.pos,&mAttentionPos);
        break;
    default:
        mLookBackState = 0;
    }
    eInit_setLocFlag(i_prm_1_p);
    eInit_setShapeAngleY(i_prm_2_p,unaff_r27);
    eInit_setEvTimer(i_timer_p);
    return;
}

/* 00004D10-00004DC4       .text eInit_SET_PLYER_GOL___11daNpc_Bm1_cFPiP4cXyzPi */
void daNpc_Bm1_c::eInit_SET_PLYER_GOL_(int* i_prm_0_p, cXyz* i_offset_p, int* i_angle_p) {
    
    cXyz local_c;

    if(i_prm_0_p != NULL){
        switch(*i_prm_0_p){
            case 0:
                if(i_offset_p != NULL){
                    local_c.set(i_offset_p->x,i_offset_p->y,i_offset_p->z);
                    dComIfGp_evmng_setGoal(&local_c);
                }
                break;
            case 1:
                local_c = eInit_calcRelativPos(i_offset_p,i_angle_p);
                dComIfGp_evmng_setGoal(&local_c);
                break;
        }
    }
    return;
}

/* 00004DC4-00004DD4       .text eInit_prmFloat__11daNpc_Bm1_cFPff */
float daNpc_Bm1_c::eInit_prmFloat(float* param_1, float param_2) {
    
    if(param_1 == NULL){
        return param_2;
    }
    return *param_1;
}

/* 00004DD4-00004FB8       .text eInit_FLY___11daNpc_Bm1_cFPiPfPfPfPf */
void daNpc_Bm1_c::eInit_FLY_(int* i_prm_0_p, float* i_speed_p, float* i_spd_y_p, float* i_accel_p, float* i_acc_y_p) {
    
    int iVar1;
    
    if (i_prm_0_p == (int *)0x0) {
        return;
    }
    m858 = l_HIO.children[mType-1].hio_prm.m30;
    if (*i_prm_0_p != 2) {
        
        mTargetFlySpeed = eInit_prmFloat(i_speed_p,l_HIO.children[mType-1].hio_prm.m20);
        mFlySpeedY = eInit_prmFloat(i_spd_y_p,l_HIO.children[mType-1].hio_prm.m28);
        mTargetFlyStep = eInit_prmFloat(i_accel_p,l_HIO.children[mType-1].hio_prm.m24);
        mFlyAccelY = eInit_prmFloat(i_acc_y_p,l_HIO.children[mType-1].hio_prm.m2C);
    }
    mLookBackState = 0;
    m88A = 0;
    iVar1 = *i_prm_0_p;
    switch(*i_prm_0_p){
        case 1:
            m8F4 = 5;
            speedF = mTargetFlySpeed;
            speed.y = mFlySpeedY;
            gravity = 0.0;
            m889 = 1;
            bm_setFlyAnm();
            break;
        case 3:
            speedF = mTargetFlySpeed;
            break;
        case 4: 
            m8F4 = 3;
            mTargetFlySpeed = 0;
        case 5:
            speed.y = 0.0;
            speedF = mTargetFlySpeed;
            gravity = 0.0;
            break;
        default:
        m889 = 1;
        m8F4 = 1;
        speed.y = 0.0f;
        speedF = 0.0f;
        gravity = 0.0f;
        case 2:
            return;
    }

    return;
}

/* 00004FB8-00004FD8       .text eInit_DEL_ACTOR___11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eInit_DEL_ACTOR_() {
    
    fopAcM_delete(this);
}

/* 00004FD8-00005190       .text eInit_WLK___11daNpc_Bm1_cFPiPfPfP4cXyzPiPiPi */
void daNpc_Bm1_c::eInit_WLK_(int* arg0, float* arg1, float* arg2, cXyz* arg3, int* arg4, int* arg5, int* arg6) {
    
    s32 temp_r0;
    u8 var_r3;

    var_r3 = 0;
    if (arg0 != NULL) {
        temp_r0 = *arg0;
        switch (temp_r0) {
        case 0:
            if (arg3 != NULL) {
                mTargetPos.set(arg3->x,arg3->y,arg3->z);
                var_r3 = 1;
            }
            break;
        case 1:
            mTargetPos = eInit_calcRelativPos(arg3,arg4);
            var_r3 = 1;
            break;
        case 2:
            if (mPathRun.isPath() == 0) {
                return;
            }
            u8 pointIdx = mPathRun.getIdx();
            if (arg5 != NULL) {
                pointIdx = *arg5;
            }
            mTargetPos = mPathRun.getPoint(pointIdx);
            var_r3 = 1;

        }

        if (var_r3) {
            eInit_setEvTimer(arg6);
            mTargetFlySpeed = eInit_prmFloat(arg1,l_HIO.children[mType-1].hio_prm.m3C);
            mTargetFlyStep = eInit_prmFloat(arg2,l_HIO.children[mType-1].hio_prm.m40);
            m858 = l_HIO.children[mType-1].hio_prm.m44;
            mLookBackState = 0;
            setAnm_NUM(0xE, 1);
        }
    }
}

/* 00005190-0000519C       .text eInit_INI_EVN_1___11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eInit_INI_EVN_1_() {
    
    m888 = 0;
}

/* 0000519C-000051EC       .text eInit_SET_NXT_PTH_INF___11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eInit_SET_NXT_PTH_INF_() {

    if (mPathRun.getPath()) {
        dPath* path = mPathRun.nextPath(fopAcM_GetRoomNo(this));
        if ( path != NULL) {
            mPathRun.setInfDrct(path);
        }
    }
}

/* 000051EC-0000522C       .text eInit_SET_ANM___11daNpc_Bm1_cFPi */
void daNpc_Bm1_c::eInit_SET_ANM_(int* i_anmno_p) {

    if (i_anmno_p != NULL) {
        s32 temp_r4 = *i_anmno_p;
        if ((temp_r4 >= 0) && (temp_r4 <= 0x16)) {
            setAnm_NUM(temp_r4, 1);
        }
    }
}

/* 0000522C-00005368       .text eInit_MOV_PTH_POINT___11daNpc_Bm1_cFPiPiPiPi */
void daNpc_Bm1_c::eInit_MOV_PTH_POINT_(int* i_prm_0_p, int* i_anm_no_p, int* i_index_p, int* i_angle_p) {
    u8 idx;
    cXyz pathpos;
    if (mPathRun.isPath()) {
        idx = mPathRun.getIdx();
        if (i_index_p != NULL) {
            idx = *i_index_p;
            idx = cLib_maxLimit(idx, mPathRun.maxPoint());
            mPathRun.setIdx(idx);
        }
        current.pos = mPathRun.getPoint(idx);
        mPathRun.nextIdxAuto();
        pathpos = mPathRun.getPoint(mPathRun.getIdx());
        current.angle.y = cLib_targetAngleY(&current.pos,&pathpos);
        if (i_prm_0_p != NULL) {
            switch(*i_prm_0_p){
                case 1:
                    current.angle.y = cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos);
                    break;
            }

        }else if (i_angle_p != NULL) {
            current.angle.y = *i_angle_p;
        }
        eInit_SET_ANM_(i_anm_no_p);
    }
    
}

/* 00005368-00005650       .text event_actionInit__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::event_actionInit(int arg0) {

  cXyz *offset_p;
  int *act_no_p;
  int *prm_0_p;
  int *prm_1_p;
  int *prm_2_p;
  int *angle_p;
  int *index_p;
  int *timer_p;
  int *anmno_p;
  float *speed_p;
  float *accel_p;
  float *spd_y_p;
  float *acc_y_p;
            
  offset_p = dComIfGp_evmng_getMyXyzP(arg0,"Offst");
  act_no_p = dComIfGp_evmng_getMyIntegerP(arg0,"ActNo");
  prm_0_p = dComIfGp_evmng_getMyIntegerP(arg0,"prm_0");
  prm_1_p = dComIfGp_evmng_getMyIntegerP(arg0,"prm_1");
  prm_2_p = dComIfGp_evmng_getMyIntegerP(arg0,"prm_2");
  angle_p = dComIfGp_evmng_getMyIntegerP(arg0,"Angle");
  index_p = dComIfGp_evmng_getMyIntegerP(arg0,"Index");
  timer_p = dComIfGp_evmng_getMyIntegerP(arg0,"Timer");
  anmno_p = dComIfGp_evmng_getMyIntegerP(arg0,"AnmNo");
  speed_p = dComIfGp_evmng_getMyFloatP(arg0,"Speed");
  accel_p = dComIfGp_evmng_getMyFloatP(arg0,"Accel");
  spd_y_p = dComIfGp_evmng_getMyFloatP(arg0,"Spd_y");
  acc_y_p = dComIfGp_evmng_getMyFloatP(arg0,"Acc_y");

  if (act_no_p != NULL) {
    mActNo = *act_no_p;
    switch(mActNo) {
    case 4:
      eInit_DEL_ACTOR_();
      break;
    case 0x10:
      eInit_SET_NXT_PTH_INF_();
      break;
    case 0x14:
      eInit_INI_EVN_1_();
      break;
    case 0x15:
      eInit_MOV_PTH_POINT_(prm_0_p,anmno_p,index_p,angle_p);
      break;
    case 0x16:
    case 0x17:
      eInit_FLY_(prm_0_p,speed_p,spd_y_p,accel_p,acc_y_p);
      break;
    case 0x18:
      eInit_SET_PLYER_GOL_(prm_0_p,offset_p,angle_p);
      break;
    case 0x19:
      eInit_ATTENTION_(prm_0_p,prm_1_p,prm_2_p,offset_p,angle_p,index_p,timer_p);
      break;
    case 0x1a:
      eInit_SET_ANM_(anmno_p);
      break;
    case 0x1b:
      eInit_WLK_(prm_0_p,speed_p,accel_p,offset_p,angle_p,index_p,timer_p);
    }
  }
  return;
}

/* 00005650-0000569C       .text eMove_ATTENTION___11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::eMove_ATTENTION_() {
    if (m86C >= 0) {
        return cLib_calcTimer(&m86C) == 0;
    }
    else {
        return m_jnt.trnChk() == 0;
    }
}

/* 0000569C-000056A4       .text eMove_KMA_FLY___11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::eMove_KMA_FLY_() {
    return m88A;
}

/* 000056A4-000056C0       .text eMove_FLY___11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::eMove_FLY_() {
    
    m88A = 0;
    return m8F4 == 0;
}

/* 000056C0-00005734       .text eMove_WLK___11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::eMove_WLK_() {
    
    s16 timer = cLib_calcTimer(&m86C);
    bool is_terminate = timer == 0;
    if (is_terminate) {
        setAnm_NUM(4,1);
        mTargetFlySpeed = 0;
        speedF = mTargetFlySpeed;
    } 
    return is_terminate;   
}

/* 00005734-000057D0       .text event_action__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::event_action() {
    

    switch(mActNo) {
    case 4:
        return 1;
        break;
    case 0x10:
        return 1;
        break;
    case 0x14:
        return 1;
        break;
    case 0x15:
        return 1;
        break;
    case 0x16:
        return eMove_FLY_();
        break;
    case 0x17:
        return eMove_KMA_FLY_();
        break;
    case 0x18:
        return 1;
        break;
    case 0x19:
        return eMove_ATTENTION_();
        break;
    case 0x1a:
        return 1;
        break;
    case 0x1b:
        return eMove_WLK_();
    default:
        return 1;
        break;
    }

}

/* 000057D0-0000580C       .text cut_init_360_TRN__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::cut_init_360_TRN(int) {
    
    setAnm_NUM(0x13,1);
    mLookBackState = 0;
}

/* 0000580C-000058B8       .text cut_move_360_TRN__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::cut_move_360_TRN() {
    
    bool uVar1;
    
    if (mbMorfAnimStopped) {
        uVar1 = 0;
        current.angle.y += 0x10000 + -0x8000;
        setAnm_NUM(4,1);
        mpMorf->setMorf(0.0);
        if (mbHasArms) {
            mpArmMorf->setMorf(0.0f);
        }
        else {
            mpWingMorf->setMorf(0.0f);
        }
        mpHeadMorf->setMorf(0.0f);
        uVar1 = 1;
        return true;
    }
    return false;
}

/* 000058B8-000059E0       .text privateCut__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::privateCut(int arg0) {
    
    static char* a_cut_tbl[] = {"ACTION","360_TRN"};
    
    if (arg0 != -1) {
        m8F5 = dComIfGp_evmng_getMyActIdx(arg0,
                        a_cut_tbl,2,1,0);

        if (m8F5 == -1) {
        dComIfGp_evmng_cutEnd(arg0);
        }
        else {
            if (dComIfGp_evmng_getIsAddvance(arg0)) {
                switch(m8F5){
                    case 0:
                        event_actionInit(arg0);
                        break;
                    case 1:
                        cut_init_360_TRN(arg0);
                }

            }
            bool cVar3;
            switch(m8F5){
                case 0:
                    cVar3 = event_action();
                    break;
                case 1:
                    cVar3 = cut_move_360_TRN();
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

/* 000059E0-00005A00       .text endEvent__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::endEvent() {
    
    dComIfGp_event_reset();
    m8F7 = 0xFF;
}

/* 00005A00-00005A38       .text isEventEntry__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::isEventEntry() {
    
    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName(),NULL);
}

/* 00005A38-00005B60       .text event_proc__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::event_proc(int arg0) {
    
    short sVar1;
    if (dComIfGp_evmng_endCheck(m862[m86A])) {
        sVar1 = m86A;
        switch(m86A){
            case 0:
            m8FD = 1;
            m87C = 1;
            break;
            case 1:
            dComIfGs_onEventBit(0x1F40);
            fopAcM_delete(this);
            break;
            case 2:
            dLetter_send(0xAE03);
            dComIfGs_onEventBit(0x2180);
            break;
            case 3:
            dComIfGs_onEventBit(0x1E80);
            fopAcM_delete(this);
            break;

        }
        endEvent();
    }
    else {
        if (!mEventCut.cutProc()) {
            privateCut(arg0);
        }
        lookBack();
    }
}

/* 00005B60-00005C0C       .text set_action__11daNpc_Bm1_cFM11daNpc_Bm1_cFPCvPvPv_iPv */
BOOL daNpc_Bm1_c::set_action(int (daNpc_Bm1_c::*i_action)(void*), void* i_param_2) {
    
    if(mCurrActionFunc != i_action){
        if(mCurrActionFunc){
            m904 = 9;
            (this->*mCurrActionFunc)(i_param_2);
        }
        mCurrActionFunc = i_action;
        m904 = 0;
        (this->*mCurrActionFunc)(i_param_2);
    }
    return TRUE;

}

/* 00005C0C-00005E84       .text setStt__11daNpc_Bm1_cFSc */
void daNpc_Bm1_c::setStt(signed char i_param_1) {
    cXyz local_20;
    s8 previous_status = mStatus;
    m86E = 0;
    mStatus = i_param_1;
    switch(mStatus) {
    case 1:
        m870 = 0x50;
        break;
    case 3:
        m880 = 1;
        m870 = 0x5A;
        break;
    case 5:
        m8F7 = 0xff;
        mLookBackState = 1;
        m8FF = previous_status;
        m_jnt.setTrn();
        return;
    case 8:
        m870 = cM_rndF(180.0f) + 180.0f;
        break;
    case 9:
        m8F7 = 0xff;
        m8FF = previous_status;
        return;
    case 10:
        mLookBackState = 0;
        local_20.set(0.0f,9999.0f,100.0f);
        mTargetPos = eInit_calcRelativPos(&local_20,NULL);
        m870 = 0x5A;
        mTargetFlySpeed = 0;
        mTargetFlyStep = 0;
        mFlySpeedY = l_HIO.children[mType-1].hio_prm.m28;
        mFlyAccelY = l_HIO.children[mType-1].hio_prm.m2C;
        m858 = l_HIO.children[mType-1].hio_prm.m30;
        speedF = 0.0;
        speed.y = 0.0;
        gravity = 0.0;
        m889 = 1;
        m8F4 = 1;
        break;
    case 0xd:
        mLookBackState = 2;
        local_20.set(0.0f,1000.0f,100.0f);
        mAttentionPos = eInit_calcRelativPos(&local_20,NULL);
        break;
    case 0x10:
        m872 = (g_Counter.mCounter0 & 3) + 1;
        break;
    case 0x11:
        mTargetFlySpeed = l_HIO.children[mType-1].hio_prm.m3C;
        mTargetFlyStep = l_HIO.children[mType-1].hio_prm.m40;
        m858 = l_HIO.children[mType-1].hio_prm.m44;
        break;
    case 0x12:
        m870 = 0x3c;
        speedF = 0.0;
    }
    setAnm();
    return;

}

/* 00005E84-00005EE0       .text d_wait__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::d_wait() {
    
    if(m881 && m882){
        setStt(2);
        fopAcM_SetStatusMap(this,7);
    }
    return true;
    
}

/* 00005EE0-00005F14       .text lookup__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::lookup() {
    
    if(mbMorfAnimStopped){
        setStt(3);
    }
    return true;  
}

/* 00005F14-00005F64       .text orooro__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::orooro() {
    
    if(dComIfGs_isEventBit(dSv_event_flag_c::UNK_0001)){
        fopAcM_delete(this);
    }
    return true;
}

/* 00005F64-00006028       .text wait_1__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::wait_1() {
    s16 sVar1;
    if (m8FD == 1 || m8FD >= 3){
            return TRUE;
    }
    if (m895) {
        if (chk_talk()) {
            setStt(5);
            m896 = false;
        }
        return TRUE;   
    }
    m8FD = 2;
    mLookBackState = 0;
    m896 = true;
    if (mbAttention != 0) {
        m86E = 0x28;
    }
    sVar1 = cLib_calcTimer(&m86E);
    if (sVar1 != 0) {
        mLookBackState = 1;
    }
    return 1;
}

/* 00006028-0000622C       .text talk_1__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::talk_1() {
    
    u8 temp_r31 = chk_partsNotMove();
    if (mpCurrMsg != NULL) {
        mOldMsgStat = mpCurrMsg->mStatus;
    } else {
        mOldMsgStat = 0;
    }
    talk(1);
    if (mpCurrMsg != NULL) {
        switch (mpCurrMsg->mStatus) {
        case 0x6:
        case 2:
            break;
        case 0x13:
            switch (mCurrMsgNo) {
            case 0xC92:
                dComIfGs_onEventBit(0x1401);
                break;
            case 0x18A2:
                dComIfGs_onEventBit(0x2202);
                break;
            case 0x1997:
                dComIfGs_onEventBit(0x2120);
                break;
            case 0x19A2:
                dComIfGs_onEventBit(0x2001);
                break;
            case 0x19A4:
                m8FD = 5;
                break;
            case 0x1EF6:
                m8FD = 3;
                break;
            case 0x1EF8:
                dComIfGs_onEventBit(0x1908);
                break;
            case 0x1EF7:
                m87C = 0;
                break;
            }
            m87D = 0xFF;
            m895 = false;
            switch(mSpecificType){
                case Akoot:
                case Skett:
                    setStt(0xB); 
                    break;
                case Ilari_0xA:
                    setStt(0xA);
                    break;
                default:       
                    setStt(m8FF);
                    m86E = 0x28;
                    endEvent();     
            }

        }
    }
    return temp_r31;
}

/* 0000622C-000062C8       .text talk_2__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::talk_2() {
    
    if(mPartnerProcID == -1){
        return TRUE;
    }
    daNpc_Bm1_c* actor = static_cast<daNpc_Bm1_c*>(searchByID(mPartnerProcID));
    if(actor){
        bool somebool = actor->getStt() != 9;
        actor->clr_manzai();
        if(somebool){   
            fopAcM_OffStatus(actor,fopAcStts_UNK4000_e);
            setStt(m8FF);
            endEvent();
            clr_manzai();
        }
    }
  return TRUE;

}

/* 000062C8-00006344       .text manzai__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::manzai() {
    

    if (mPartnerProcID == -1) {
        return 1;
    }
    if (mbManzai != 0) {
        daNpc_Bm1_c* partner = (daNpc_Bm1_c*)(searchByID(mPartnerProcID));
        anmAtr(partner->get_oldMsgStat());
    } else {
        setStt(m8FF);
    }
    return 1;
}

/* 00006344-00006424       .text wait_4__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::wait_4() {
    
    cLib_addCalcAngleS(&current.angle.y,m818.y,4,0x800,0x80);
    if(m8FD == 1 || m8FD >= 3){
        return TRUE;
    }
    if(m895){
        if(chk_talk()){
            setStt(5);
            m896 = false;
        }
        return TRUE;
    }else{
        m8FD = 2;
        mLookBackState = 0;
        m896 = true;
        if(mbAttention){
            m86E = 0x28;
        }
    }
    if(cLib_calcTimer(&m86E)){
        mLookBackState = 1;
    }
    return TRUE;
    
}

/* 00006424-0000647C       .text flyawy__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::flyawy() {
    
    if (cLib_calcTimer(&m870) == 0) {
        endEvent();
       fopAcM_delete(this);
    }
    else {
        m88A = 0;
    }
    return 1;
}

/* 0000647C-000065B8       .text wait_5__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::wait_5() {
    
    if(m8FD == 0){
        f32 fVar2 = (dComIfGp_getLinkPlayer()->current.pos - current.pos).absXZ();
        f32 fVar1 = dComIfGp_getLinkPlayer()->current.pos.y - current.pos.y;
        if(fVar2 < l_HIO.children[mType-1].hio_prm.m48 && -40.0f < fVar1 && fVar1 < 300.0f){
            m8FD = 4;
        }
    }
    return TRUE;
}

BOOL daNpc_Bm1_c::wait_6(){} //unused

/* 000065B8-00006688       .text h_wait__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::h_wait() {

    if ((m8FD == 1) || (m8FD >= '\x03')) {
        return TRUE;
    }
    if(m895){
        if (chk_talk() != '\0') {
            setStt(5);
        }
        return TRUE;
    }
    m8FD = 2;
    if (mbAttention != 0) {
        m86E = 0x28;
    }
    if (cLib_calcTimer(&m86E)) {
        mLookBackState = 1;
        m896 = 0;
    }
    else {
        mLookBackState = 3;
        m876 = m818.y;
        m_jnt.setTrn();
    }
    return TRUE;
}

/* 00006688-0000677C       .text wait_7__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::wait_7() {
    


    if ((m8FD == 1) || (m8FD >= 3)) {
        return TRUE;
    }
    if (m895) {
        if (chk_talk()  && chk_manzai()) {
            setStt(5);
        }
        return TRUE;
    }else{
        if (mbManzai) {
            setStt(9);
            return TRUE;
        }
        else {
            m8FD = 2;
            if (mbAttention != 0) {
                m86E = 0x28;
            }
            if (cLib_calcTimer(&m86E)) {
                mLookBackState = 1;
            }
            else {
                mLookBackState = 3;
                m876 = m818.y;
                m_jnt.setTrn();

            }
        }
    }
    return 1;
}

/* 0000677C-000068A8       .text wait_3__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::wait_3() {
    
    cLib_addCalcAngleS(&current.angle.y,m818.y,4,0x800,0x80);
    if(m8FD == 1 || m8FD >= 3){
        return TRUE;
    }
    if(m895){
        if(chk_talk()){
            setStt(5);
            m896 = false;
        }
        return TRUE;
    }else{
        m8FD = 2;
        mLookBackState = 0;
        m896 = true;
        if(mbAttention){
            m86E = 0x28;
        }
    }
    if(cLib_calcTimer(&m86E)){
        mLookBackState = 1;
        m870 = cM_rndF(180.0f) + 180.0f;
        return TRUE;
    }
    if(!cLib_calcTimer(&m870)){
        setStt(0x10);
    }
    return TRUE;
}

/* 000068A8-0000692C       .text wait_8__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::wait_8() {

    m8FD = 2;
    if(mbMorfAnimStopped){
        if(!cLib_calcTimer(&m872)){
            setStt(0x8);
        }
        if(m895 && chk_talk()){
            setStt(0x8);
        }
    }
    return TRUE;
}

/* 0000692C-0000699C       .text wait_2__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::wait_2() {
    
    if(m8FD == 1 || m8FD >= 3){
        return TRUE;
    }
    if(dComIfGs_isEventBit(dSv_event_flag_c::ENDLESS_NIGHT)){
        m8FD = 6;
    }
    return TRUE;
}

/* 0000699C-00006A94       .text walk_1__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::walk_1() {
    
    char cVar1;
    u32 uVar2;
    cXyz local_18;
    
    if (m895) {
        setAnm_NUM(4,1);
        speedF = 0.0;
        if (chk_talk()) {
            setStt(5);
            m896 = false;
        }
        return TRUE;
    }else {
        mTargetPos = mPathRun.getPoint(mPathRun.getIdx());

        mLookBackState = 0;
        m896 = true;
        m8FD = 2;
        if (m88B) {
            if (m87E) {
                setStt(0x12);
            }
            m88B = 0;
        }
        m87E = mPathRun.pointArg(mPathRun.getIdx());    
    }
    return TRUE;
}

/* 00006A94-00006B74       .text CHKwai__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::CHKwai() {
    
  
    if (m895) {
        if (chk_talk()) {
            setStt(5);
            mLookBackState = 1;
            m896 = false;
            m_jnt.setTrn(); 
    
        }
        return TRUE;   
    }
    else {
        m8FD = 2;
        if (!cLib_calcTimer(&m870)) {
            setStt(0x11);
            return TRUE;
        }
        else {
        mLookBackState = 2;
        mAttentionPos = mPathRun.getPoint(mPathRun.getIdx());
        mAttentionPos.y = eyePos.y;
        m896 = false;
        m_jnt.setTrn();
        }
    }
    return 1;
}

/* 00006B74-00006C4C       .text demo_action1__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::demo_action1(void*) {
    switch(m904){
        case 0:
            setStt(1);
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus){
                case 1:
                    mbSetEyePos = d_wait();
                    break;
                case 2:
                    mbSetEyePos = lookup();
                    break;
                case 3:
                    mbSetEyePos = orooro();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00006C4C-00006D08       .text wait_action1__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action1(void* arg0) {
    
    switch(m904){
        case 0:
            setStt(4);
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus){
                case 4:
                    mbSetEyePos = wait_1();
                    break;
                case 5:
                    mbSetEyePos = talk_1();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00006D08-00006E28       .text wait_action2__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action2(void*) {
    
    switch(m904){
        case 0:
            setStt(0xC);
            if(mSpecificType == Kogoli && dComIfGs_isEventBit(dSv_event_flag_c::UNK_1820) && !dKy_daynight_check()){
                current.angle.y -= 0x6000;
                m818.y = current.angle.y;
            }
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus){
                case 0xC:
                    mbSetEyePos = wait_4();
                    break;
                case 5:
                    mbSetEyePos = talk_1();
                    break;

                case 0xA:
                    mbSetEyePos = flyawy();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;

}


/* 00006E28-00006EC4       .text wait_action3__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action3(void*) {
    
    switch(m904){
        case 0:
            setStt(0xD);
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus){
                case 0xD:
                    mbSetEyePos = wait_5();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00006EC4-00006F30       .text wait_action4__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action4(void*) {
    
    switch(m904){
        case 0:
            setAnm_NUM(4,1);
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
        case 9:
            break;
    }
    return TRUE;
}

/* 00006F30-00006FEC       .text wait_action5__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action5(void*) {
    
    switch(m904){
        case 0:
            setStt(0xE);
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus){
                case 0xE:
                    mbSetEyePos = wait_4();
                    break;
                case 0x5:
                    mbSetEyePos = talk_1();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00006FEC-000070B0       .text wait_action6__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action6(void*) {
    
    switch(m904){
        case 0:
            setStt(0x7);
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus){
                case 0x7:
                    mbSetEyePos = h_wait();
                    break;
                case 0x5:
                    mbSetEyePos = talk_1();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 000070B0-00007198       .text wait_action7__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action7(void*) {
    
    switch(m904){
        case 0:
            setStt(0xF);
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus){
                case 0xF:
                    mbSetEyePos = wait_7();
                    break;
                case 5:
                    mbSetEyePos = talk_1();
                    break;
                case 0xB:
                    mbSetEyePos = talk_2();
                    break;
                case 9:
                    mbSetEyePos = manzai();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 00007198-00007270       .text wait_action8__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action8(void*) {
        
    switch(m904){
        case 0:
            setStt(8);
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus){
                case 8:
                    mbSetEyePos = wait_3();
                    break;
                case 5:
                    mbSetEyePos = talk_1();
                    break;
                case 0x10:
                    mbSetEyePos = wait_8();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }

    return TRUE;
}

/* 00007270-0000730C       .text wait_action9__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action9(void*) {
    
    switch(m904){
        case 0:
            setStt(0x6);
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus){
                case 0x6:
                    mbSetEyePos = wait_2();
                    break;
            }
            lookBack();
            break;
        case 9:
            break;
    }
    return TRUE;
}

/* 0000730C-000073E4       .text wait_actionA__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_actionA(void*) {
    
    switch(m904){
        case 0:
            setStt(0x11);
            m904 += 1;
            break;
        case 1:
        case 2:
        case 3:
            mbAttention = chkAttention();
            switch(mStatus){
                case 0x11:
                    mbSetEyePos = walk_1();
                    break;
                case 0x12:
                    mbSetEyePos = CHKwai();
                    break;
                case 5:
                    mbSetEyePos = talk_1();
                    break;         
            }
            lookBack();
            break;
        case 9:
            break;
    }

    return TRUE;
}

/* 000073E4-00007514       .text demo__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::demo() {
    
    if(demoActorID == 0){
        if(mbInDemo != 0){
            mbInDemo = 0;
        }
    }else{
        mbInDemo = 1;
        dDemo_actor_c* demo_actor = dComIfGp_demo_getActor(demoActorID);
        if(m_hed_tex_pttrn){
            mBlinkFrame += 1;
            if (mBlinkFrame >= m_hed_tex_pttrn->getFrameMax()) {
                mBlinkFrame = m_hed_tex_pttrn->getFrameMax();
            }
        }
        J3DAnmTexPattern* demopattern = demo_actor->getP_BtpData(mArcName);
        if(demopattern){
            m_hed_tex_pttrn = demopattern;        
            if(mHeadBtpAnm.init(mpHeadMorf->getModel()->getModelData(),m_hed_tex_pttrn,1,2,1.0f,0,-1,true,FALSE)){
                m8F9 = 1;
                mBlinkFrame = 0;
            }
        }
        dDemo_setDemoData(this,0x6A, mpMorf,mArcName);
    }
    return mbInDemo;
}

/* 00007514-0000768C       .text shadowDraw__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::shadowDraw() {
    
    cXyz local_18(current.pos.x,current.pos.y + 150.0f, current.pos.z);

    mShadowID = dComIfGd_setShadow(mShadowID,1,mpMorf->getModel(),&local_18,800.0f,40.0f,current.pos.y,mObjAcch.GetGroundH(),
    mObjAcch.m_gnd,&tevStr,0,1.0,dDlst_shadowControl_c::getSimpleTex());
    if(mShadowID){
        if(mbHasArms){
            dComIfGd_addRealShadow(mShadowID,mpArmMorf->getModel());
        }else{
            dComIfGd_addRealShadow(mShadowID,mpWingMorf->getModel());

        }
        if(mpBinderModel){
            dComIfGd_addRealShadow(mShadowID,mpBinderModel);
        }
        if(mpBagModel){
            dComIfGd_addRealShadow(mShadowID,mpBagModel);
        }
        if(mpKnifeModel){
            dComIfGd_addRealShadow(mShadowID,mpKnifeModel);
        }
        if(mpStickModel){
            dComIfGd_addRealShadow(mShadowID,mpStickModel);
        }
        dComIfGd_addRealShadow(mShadowID,mpHeadMorf->getModel());

    }
}

static const u32 dummyColor[] = {
    0xFF000080,
    0x0000FF80,
    0x00FF0080,
};

/* 0000768C-00007AB4       .text _draw__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::_draw() {
    
    J3DModel* model = mpHeadMorf->getModel();
    J3DModelData* model_data = model->getModelData();
    J3DModel* morf_model = mpMorf->getModel();

    if ((mbInitPostman0) || (m888)) {
        return 1;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR,&current.pos,&tevStr);
    g_env_light.setLightTevColorType(morf_model,&tevStr);
    switch(mType){

        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            mpMorf->entryDL((J3DMaterialTable*)dComIfG_getObjectRes(mArcName,"bm02.bmt"));
            break;
        case 1:
        case 7:
        case 8:
        case 9:
        case 10:
        default:
            mpMorf->entryDL();
            break;
            
    }

    mHeadBtpAnm.entry(model_data,mBlinkFrame);
    mpHeadMorf->entryDL();
    mHeadBtpAnm.remove(model_data);
    g_env_light.setLightTevColorType(model,&tevStr);
    if(mbHasArms){
        g_env_light.setLightTevColorType(mpArmMorf->getModel(),&tevStr);

    
    switch(mType){
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
            {
            J3DMaterialTable* mattable = reinterpret_cast<J3DMaterialTable*>(dComIfG_getObjectRes(mArcName,"bmarm02.bmt"));
            mpArmMorf->entryDL(mattable);
            }
            break;
        case 1:
        case 7:
        case 8:
        case 9:
        case 10:
        default:
            mpArmMorf->entryDL();
            break;
    }

    }else{
        g_env_light.setLightTevColorType(mpWingMorf->getModel(),&tevStr);
        mpWingMorf->entryDL();
    }
    if(mpBinderModel){

        g_env_light.setLightTevColorType(mpBinderModel,&tevStr);
        mDoExt_modelEntryDL(mpBinderModel);

    }
    if(mpBagModel){
        g_env_light.setLightTevColorType(mpBagModel,&tevStr);
        mDoExt_modelEntryDL(mpBagModel);

    }
    if(mpKnifeModel){
        g_env_light.setLightTevColorType(mpKnifeModel,&tevStr);
        mDoExt_modelEntryDL(mpKnifeModel);

    }
    if(mpStickModel){
        g_env_light.setLightTevColorType(mpStickModel,&tevStr);
        mDoExt_modelEntryDL(mpStickModel);
    }
    shadowDraw();
    switch(mType){
        case 1:
            dSnap_RegistFig(0x8D,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
        case 2:
            dSnap_RegistFig(0x8E,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
        case 3:
            dSnap_RegistFig(0x8E,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
        case 4:
            dSnap_RegistFig(0x93,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
        case 5:
            dSnap_RegistFig(0x93,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
        case 6:
            dSnap_RegistFig(0x91,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
        case 7:
            dSnap_RegistFig(0x90,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
        case 8:
            dSnap_RegistFig(0x97,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
        case 9:
            dSnap_RegistFig(0x92,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
        case 0xA:
            dSnap_RegistFig(0x8F,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
    }

    if(l_HIO.children[mType-1].hio_prm.m18 != 0 && mSpecificType == Quill_2){

        cXyz somevec = current.pos;
        somevec.y = eyePos.y;

    }
    return 1;
}


/* 00007AB4-00007CAC       .text _execute__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::_execute() {
    
    if(!mbRanExecute){
        mInitialPos = current.pos;
        m818 = current.angle;
        mbRanExecute = true;
    }
    m_jnt.setParam(l_HIO.children[mType-1].hio_prm.mMaxBackboneX ,l_HIO.children[mType-1].hio_prm.mMaxBackboneY,
        l_HIO.children[mType-1].hio_prm.mMinBackboneX,l_HIO.children[mType-1].hio_prm.mMinBackboneY,
        l_HIO.children[mType-1].hio_prm.mMaxHeadX,l_HIO.children[mType-1].hio_prm.mMaxHeadY,
        l_HIO.children[mType-1].hio_prm.mMinHeadX,l_HIO.children[mType-1].hio_prm.mMinHeadY,
        l_HIO.children[mType-1].hio_prm.mMaxTurnStep);
    if(!m881 && mbInitPostman0 && demoActorID == 0){
        return TRUE;
    }
    m887 = 0;
    mbInitPostman0 = false;
    partner_srch();
    checkOrder();
    if(!demo()){
        s32 iVar1 = -1;
        if(dComIfGp_event_runCheck() && eventInfo.checkCommandTalk() == 0){
            iVar1 = isEventEntry();
        }
        if(iVar1 >= 0){
            event_proc(iVar1);
        }else{
            (this->*mCurrActionFunc)(NULL);
        }
        if(!bm_flyMove()){
            bm_nMove();
        }
        if(!m887){
            fopAcM_posMoveF(this,mStts.GetCCMoveP());
        }
        
        if(!mbSetShapeAngle){
            shape_angle = current.angle;
        }
    }
        eventOrder();
        setMtx(false);
        if(!mbInDemo){
            setCollision(50.0f,160.0f);
        }
        return TRUE;
}

/* 00007CAC-00007D50       .text _delete__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::_delete() {
    

#if VERSION == VERSION_DEMO
    if(m87F){
        dComIfG_resDelete(&mPhs,mArcName);
        mDoExt_McaMorf* this_00;
    }
    if(mpMorf){
        mpMorf->stopZelAnime();
    }
    {
#else
    dComIfG_resDelete(&mPhs,mArcName);
    mDoExt_McaMorf* this_00;
    if (heap != (JKRHeap *)0x0) {
        this_00 = mpMorf;
        if (this_00 != NULL) {
            mpMorf->stopZelAnime();
        }
#endif

        if (mpHeadMorf != NULL) {
            mpHeadMorf->stopZelAnime();
        }
        if (mpWingMorf != NULL) {
            mpWingMorf->stopZelAnime();
        }
        if (mpArmMorf != NULL) {
            mpArmMorf->stopZelAnime();
        }
    }
    delPrtcl_Flyaway();
    delPrtcl_Land0();
    delPrtcl_Hane0();
    delPrtcl_Hane1();
#if VERSION == VERSION_DEMO
l_HIO.removeHIO();
#endif
    return 1;
}

/* 00007D50-00007D70       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* this00) {
    
    static_cast<daNpc_Bm1_c*>(this00)->CreateHeap();
}

/* 00007D70-00007ED4       .text _create__11daNpc_Bm1_cFv */
cPhs_State daNpc_Bm1_c::_create() {
    
    fopAcM_ct_Retail(this, daNpc_Bm1_c);
    static u32 a_size_tbl[0xB] = {};
    u32 param = fopAcM_GetParam(this);
    u8 param2 = param;
    if(!decideType(param2 ,(param >> 8) & 0xFF)){
        return cPhs_ERROR_e;
    }
    cPhs_State state = dComIfG_resLoad(&mPhs,mArcName);
    m87F =  state == cPhs_COMPLEATE_e;
    if(!m87F){
        return state;
    }else{
#if VERSION == VERSION_DEMO
        l_HIO.entryHIO("リト族");
        fopAcM_ct(this,daNpc_Bm1_c);
#endif
        if(!fopAcM_entrySolidHeap(this,CheckCreateHeap,a_size_tbl[mType])){
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(this,mpMorf->getModel()->getBaseTRMtx());
        if(mSpecificType == Quill_0){
            fopAcM_setCullSizeBox(this,-250.0,-20.0,-200.0,250.0,500.0,200.0);
        }else{
            fopAcM_setCullSizeBox(this,-70.0,-20.0,-70.0,70.0,220.0,70.0);
        }
        if(!createInit()){
            return cPhs_ERROR_e;
        }
    }
    return state;



}

/* 000083E8-00008710       .text create_Anm__11daNpc_Bm1_cFv */
J3DModelData* daNpc_Bm1_c::create_Anm() {
    
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName,"bm.bdl");
    JUT_ASSERT(DEMO_SELECT(0x153E,0x1551),a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,(J3DAnmTransform*)dComIfG_getObjectRes(mArcName,"bm_dwait.bck"),J3DFrameCtrl::EMode_LOOP,1.0f,0,-1,1,NULL,0x80000,0x15021222);
    if(mpMorf == NULL ){
        return NULL;
    }else if(mpMorf->getModel() == NULL){
        mpMorf = NULL;
        return NULL;
    }

    m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
    JUT_ASSERT(DEMO_SELECT(0x1552,0x1565),m_hed_jnt_num >= 0);
    m_nec_jnt_num = a_mdl_dat->getJointName()->getIndex("neck");
    JUT_ASSERT(DEMO_SELECT(0x1555,0x1568),m_nec_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
    JUT_ASSERT(DEMO_SELECT(0x1558,0x156B),m_bbone_jnt_num >= 0);    
    m_arm_L_jnt_num = a_mdl_dat->getJointName()->getIndex("armL");
    JUT_ASSERT(DEMO_SELECT(0x155B,0x156E),m_arm_L_jnt_num >= 0);    
    m_arm_R_jnt_num = a_mdl_dat->getJointName()->getIndex("armR");
    JUT_ASSERT(DEMO_SELECT(0x155E,0x1571),m_arm_R_jnt_num >= 0); 
    return a_mdl_dat;  

}

/* 00008710-00008878       .text create_hed_Anm__11daNpc_Bm1_cFv */
J3DModelData* daNpc_Bm1_c::create_hed_Anm() {
    
    static char* a_headBDLName_TBL[] = {
        "bmhead01.bdl","bmhead01.bdl","bmhead01.bdl","bmhead01.bdl","bmhead01.bdl",
        "bmhead02.bdl","bmhead02.bdl",
        "bmhead07.bdl","bmhead07.bdl",
        "bmhead05.bdl",
        "bmhead04.bdl","bmhead04.bdl","bmhead04.bdl",
        "bmhead09.bdl",
        "bmhead06.bdl",
        "bmhead03.bdl",};
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName,a_headBDLName_TBL[mSpecificType]);
    JUT_ASSERT(DEMO_SELECT(0x1580,0x1593),a_mdl_dat != NULL);
    mpHeadMorf = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,(J3DAnmTransform*)dComIfG_getObjectRes(mArcName,"bmhead01_dwait.bck"),2,1.0,0,-1,1,NULL,0x80000,0x11020022);
    if(!mpHeadMorf){
        return NULL;
    }
    if(!mpHeadMorf->getModel()){
        mpHeadMorf = NULL;
        return NULL;
    }
    return a_mdl_dat;
}

/* 00008878-00008B44       .text create_wng_Anm__11daNpc_Bm1_cFv */
J3DModelData* daNpc_Bm1_c::create_wng_Anm() {
    
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName,"bmwing.bdl");
    JUT_ASSERT(DEMO_SELECT(0x159E,0x15B1),a_mdl_dat != NULL);
    mpWingMorf = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,(J3DAnmTransform*)dComIfG_getObjectRes(mArcName,"bmwing_dwait.bck"),2,1.0,0,-1,1,NULL,0x80000,0x15021222);
    if(!mpWingMorf){
        return NULL;
    }
    if(!mpWingMorf->getModel()){
        mpWingMorf = NULL;
        return NULL;
    }
    m_wngL1_jnt_num = a_mdl_dat->getJointName()->getIndex("wingLloc");
    JUT_ASSERT(DEMO_SELECT(0x15B2,0x15C5),m_wngL1_jnt_num >= 0);
    m_wngL3_jnt_num = a_mdl_dat->getJointName()->getIndex("wingL3");
    JUT_ASSERT(DEMO_SELECT(0x15B5,0x15C8),m_wngL3_jnt_num >= 0);
    m_wngR1_jnt_num = a_mdl_dat->getJointName()->getIndex("wingRloc");
    JUT_ASSERT(DEMO_SELECT(0x15B8,0x15CB),m_wngR1_jnt_num >= 0);
    m_wngR3_jnt_num = a_mdl_dat->getJointName()->getIndex("wingR3");
    JUT_ASSERT(DEMO_SELECT(0x15BB,0x15CE),m_wngR3_jnt_num >= 0);
    return a_mdl_dat;

}

/* 00008B44-00008E6C       .text create_arm_Anm__11daNpc_Bm1_cFv */
J3DModelData* daNpc_Bm1_c::create_arm_Anm() {
    
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName,"bmarm.bdl");
    JUT_ASSERT(DEMO_SELECT(0x15CA,0x15DD),a_mdl_dat != NULL);
    mpArmMorf = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,(J3DAnmTransform*)dComIfG_getObjectRes(mArcName,"bmarm_wait01.bck"),2,1.0,0,-1,1,NULL,0x80000,0x15021222);
    if(!mpArmMorf){
        return NULL;
    }
    if(!mpArmMorf->getModel()){
        mpArmMorf = NULL;
        return NULL;
    }
    m_armL1_jnt_num = a_mdl_dat->getJointName()->getIndex("armLloc");
    JUT_ASSERT(DEMO_SELECT(0x15DE,0x15F1),m_armL1_jnt_num >= 0);
    m_armR1_jnt_num = a_mdl_dat->getJointName()->getIndex("armRloc");
    JUT_ASSERT(DEMO_SELECT(0x15E1,0x15F4),m_armR1_jnt_num >= 0);
    m_armL2_jnt_num = a_mdl_dat->getJointName()->getIndex("armL2");
    JUT_ASSERT(DEMO_SELECT(0x15E4,0x15F7),m_armL2_jnt_num >= 0);
    m_armR2_jnt_num = a_mdl_dat->getJointName()->getIndex("armR2");
    JUT_ASSERT(DEMO_SELECT(0x15E7,0x15FA),m_armR2_jnt_num >= 0);
    m_hnd_R_jnt_num = a_mdl_dat->getJointName()->getIndex("handR");
    JUT_ASSERT(DEMO_SELECT(0x15EA,0x15FD),m_hnd_R_jnt_num >= 0);  
    return a_mdl_dat;
}

/* 00008E6C-00009174       .text create_itm_Mdl__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::create_itm_Mdl() {
    
    mpBinderModel = NULL;
    mpBagModel = NULL;
    mpKnifeModel = NULL;
    mpStickModel = NULL;
    if(mType == 8 || mType == 9){
        J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName,"bm_binder.bdl");
        JUT_ASSERT(DEMO_SELECT(0x1603,0x1616),a_mdl_dat != NULL);
        mpBinderModel = mDoExt_J3DModel__create(a_mdl_dat,0x80000,0x11000002);
        if(!mpBinderModel){
            return FALSE;
        }
    }
    if(mType == 1 || mType == 7 || mType == 8){
        J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName,"bm_bag.bdl");
        JUT_ASSERT(DEMO_SELECT(0x1612,0x1625),a_mdl_dat != NULL);
        mpBagModel = mDoExt_J3DModel__create(a_mdl_dat,0x80000,0x11000002);
        if(!mpBagModel){
            return FALSE;
        }
    }
    if(mType == 2 || mType == 3){
        J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName,"bm_knife.bdl");
        JUT_ASSERT(DEMO_SELECT(0x161F,0x1632),a_mdl_dat != NULL);
        mpKnifeModel = mDoExt_J3DModel__create(a_mdl_dat,0x80000,0x11000002);
        if(!mpKnifeModel){
            return FALSE;
        }
    }
    if(mType == 4 || mType == 5 || mType == 6){
        J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName,"bm_stick.bdl");
        JUT_ASSERT(DEMO_SELECT(0x162D,0x1640),a_mdl_dat != NULL);
        mpStickModel = mDoExt_J3DModel__create(a_mdl_dat,0x80000,0x11000002);
        if(!mpStickModel){
            return FALSE;
        }
    }
    return TRUE;
}

/* 00009174-0000946C       .text CreateHeap__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::CreateHeap() {
    
    J3DModelData* modeldat;
    J3DModelData* anm_model = create_Anm();
    if(!anm_model){
        return FALSE;
    }
    J3DModelData* head_modeldat = create_hed_Anm();
    if(!head_modeldat){
        mpMorf = NULL;
        return FALSE;
    }
    m8F9 = 0;
    if(!iniTexPttrnAnm(false)){
        mpMorf = NULL;
        mpHeadMorf = NULL;
        return FALSE;
    }
    modeldat = create_wng_Anm();
    if(!modeldat){
        mpMorf = NULL;
        mpHeadMorf = NULL;
        return FALSE;
    }
    J3DModelData* arm_anmdata = create_arm_Anm();
    if(arm_anmdata != NULL && create_itm_Mdl()){

        for(u16 i = 0; i < modeldat->getJointNum(); i++){
            if((i == m_wngL1_jnt_num) ||( i == m_wngL3_jnt_num) || (i == m_wngR1_jnt_num) || (i == m_wngR3_jnt_num)){
                mpWingMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Wng);
            }
        }
        mpWingMorf->getModel()->setUserArea((u32)this);
        for(u16 i = 0; i < arm_anmdata->getJointNum(); i++){
            if((i == m_armL1_jnt_num) ||( i == m_armL2_jnt_num) || (i == m_armR1_jnt_num) || (i == m_armR2_jnt_num)){
                mpArmMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Arm);
            }
        }
        mpArmMorf->getModel()->setUserArea((u32)this);
        for(u16 i = 0; i < anm_model->getJointNum(); i++){
            if((i == m_hed_jnt_num) ||( i == m_nec_jnt_num) || (i == m_bbone_jnt_num) || (i == m_arm_L_jnt_num) || i == m_arm_R_jnt_num){
                mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Bm1);
            }
        }
        mpMorf->getModel()->setUserArea((u32)this);
        mAcchCir.SetWall(30.0f,50.0f);
#if VERSION == VERSION_DEMO

        mObjAcch.Set(fopAcM_GetPosition_p(this),fopAcM_GetOldPosition_p(this),this,1,&mAcchCir,fopAcM_GetSpeed_p(this),NULL,NULL);

#else
        mObjAcch.Set(&current.pos,&old.pos,this,1,&mAcchCir,&speed);

#endif
        return TRUE;

    }else{
        mpMorf = NULL;
        mpHeadMorf = NULL;
        mpWingMorf = NULL;
        return FALSE;
    }
}

/* 0000946C-0000948C       .text daNpc_Bm1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Bm1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Bm1_c*)i_this)->_create();
}

/* 0000948C-000094AC       .text daNpc_Bm1_Delete__FP11daNpc_Bm1_c */
static BOOL daNpc_Bm1_Delete(daNpc_Bm1_c* i_this) {
    return ((daNpc_Bm1_c*)i_this)->_delete();
}

/* 000094AC-000094CC       .text daNpc_Bm1_Execute__FP11daNpc_Bm1_c */
static BOOL daNpc_Bm1_Execute(daNpc_Bm1_c* i_this) {
    return ((daNpc_Bm1_c*)i_this)->_execute();
}

/* 000094CC-000094EC       .text daNpc_Bm1_Draw__FP11daNpc_Bm1_c */
static BOOL daNpc_Bm1_Draw(daNpc_Bm1_c* i_this) {
    return ((daNpc_Bm1_c*)i_this)->_draw();
}

/* 000094EC-000094F4       .text daNpc_Bm1_IsDelete__FP11daNpc_Bm1_c */
static BOOL daNpc_Bm1_IsDelete(daNpc_Bm1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Bm1_Method = {
    (process_method_func)daNpc_Bm1_Create,
    (process_method_func)daNpc_Bm1_Delete,
    (process_method_func)daNpc_Bm1_Execute,
    (process_method_func)daNpc_Bm1_IsDelete,
    (process_method_func)daNpc_Bm1_Draw,
};

static BOOL daNpc_Bm1_ToFore(daNpc_Bm1_c*){}; //Unused
static BOOL daNpc_Bm1_ToBack(daNpc_Bm1_c*){}; //Unused

actor_process_profile_definition g_profile_NPC_BM1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BM1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bm1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BM1_e,
    /* Actor SubMtd */ &l_daNpc_Bm1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BM2 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BM2_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bm1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BM2_e,
    /* Actor SubMtd */ &l_daNpc_Bm1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BM3 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BM3_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bm1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BM3_e,
    /* Actor SubMtd */ &l_daNpc_Bm1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BM4 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BM4_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bm1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BM4_e,
    /* Actor SubMtd */ &l_daNpc_Bm1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_BM5 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_NPC_BM5_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Bm1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_NPC_BM5_e,
    /* Actor SubMtd */ &l_daNpc_Bm1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
