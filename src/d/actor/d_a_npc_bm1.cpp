/**
 * d_a_npc_bm1.cpp
 * NPC - Generic Ritos
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_bm1.h"
#include "d/d_bg_s_func.h"
#include "res/Object/Bm.h"

static daNpc_Bm1_HIO_c l_HIO;
static fopAc_ac_c* l_check_inf[20];
static s32 l_check_wrk = 0;
static char l_BCKName[0x1E];
static char l_BTPName[0x1E];


    char* l_evn_tbl[] = {
        "Get_Mo3_Ltr","Met_Ryu_Islnd","Get_Rupee","Skn_Islnd",
    };
    char* stringbaseone[] = {"Bm1","Bm2","Bm3","Bm4"};
    // char* last = "B5";
/* 000000EC-00000108       .text __ct__20daNpc_Bm1_childHIO_cFv */
daNpc_Bm1_childHIO_c::daNpc_Bm1_childHIO_c() {
    /* Nonmatching */
}

/* 00000150-0000020C       .text __ct__15daNpc_Bm1_HIO_cFv */
daNpc_Bm1_HIO_c::daNpc_Bm1_HIO_c() {
    /* Nonmatching */
    static hio_prm_c a_prm_tbl[] = {
        0x20000FA0,
        0xF63CF060,
        0x00001B58,
        0xFC18E4A8,
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
        0x20002000,
        0xF8BBE000,
        0x00001036,
        0x0000EFCA,
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
        0x20002000,
        0xF8BBE000,
        0x00001036,
        0x0000EFCA,
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
        0x20002000,
        0xF000E000,
        0x00001000,
        0x0000F000,
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
    0x20002000,
        0xF000E000,
        0x00001000,
        0x0000F000,
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
    0x20002000,
        0xE5BAE000,
        0x00001000,
        0x0000F000,
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
        0x20002000,
        0xF000E000,
        0x00001000,
        0x0000F000,
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
        0x20002000,
        0xF000E000,
        0x00002000,
        0x0000E000,
        0x0640,0x0578,
        220.0f,
        0,0,0,
        0,0,0,0,0,0,0x0006,0x0400,
        0.3f,
        4.0f,
        0.3f,
        40.0f,
        0,
        0x20002000,
        0xF000E000,
        0x00002000,
        0x0000E000,
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
        0,0x20002000,
        0xF000E000,
        0x00001000,
        0x0000F000,
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
void* searchActor_Zl(void* i_param_1, void*) {
    /* Nonmatching */
    if(l_check_wrk < 0x14 && fopAc_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_ZL1_e){
        l_check_inf[l_check_wrk] =(fopAc_ac_c*)i_param_1;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 000002E0-00000358       .text searchActor_Gp__FPvPv */
void* searchActor_Gp(void* i_param_1, void*) {
    /* Nonmatching */
    if(l_check_wrk < 0x14 && fopAc_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_GP1_e){
        l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_param_1;
        l_check_wrk += 1;
    }
    return NULL;
}

/* 00000358-000003DC       .text searchActor_Bm_Skt__FPvPv */
void* searchActor_Bm_Skt(void* i_param_1, void*) {
    /* Nonmatching */
    if(l_check_wrk < 0x14 && fopAc_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_BM2_e){
        if(reinterpret_cast<daNpc_Bm1_c*>(i_param_1)->mSpecificType == Skett){
            l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_param_1;
            l_check_wrk += 1;
        }
    }
    return NULL;
}

/* 000003DC-00000460       .text searchActor_Bm_Kkt__FPvPv */
void* searchActor_Bm_Kkt(void* i_param_1, void*) {
    /* Nonmatching */
    if(l_check_wrk < 0x14 && fopAc_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_BM2_e){
        if(reinterpret_cast<daNpc_Bm1_c*>(i_param_1)->mSpecificType == Akoot){
            l_check_inf[l_check_wrk] = (fopAc_ac_c*)i_param_1;
            l_check_wrk += 1;
        }
    }
    return NULL;
}

/* 00000460-000004AC       .text nodeCallBack_Wng__FP7J3DNodei */
static BOOL nodeCallBack_Wng(J3DNode* i_param_1, int i_param_2) {
    /* Nonmatching */
    if(i_param_2 == 0){
        if(j3dSys.getModel()->getUserArea() != NULL){
            reinterpret_cast<daNpc_Bm1_c*>(j3dSys.getModel()->getUserArea())->nodeWngControl(i_param_1,j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 000004AC-000005BC       .text nodeWngControl__11daNpc_Bm1_cFP7J3DNodeP8J3DModel */
void daNpc_Bm1_c::nodeWngControl(J3DNode*, J3DModel*) {
    /* Nonmatching */
}

/* 000005BC-00000608       .text nodeCallBack_Arm__FP7J3DNodei */
static BOOL nodeCallBack_Arm(J3DNode* i_param_1, int i_param_2) {
    /* Nonmatching */
    if(i_param_2 == 0){
        if(j3dSys.getModel()->getUserArea() != NULL){
            reinterpret_cast<daNpc_Bm1_c*>(j3dSys.getModel()->getUserArea())->nodeWngControl(i_param_1,j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000608-00000718       .text nodeArmControl__11daNpc_Bm1_cFP7J3DNodeP8J3DModel */
void daNpc_Bm1_c::nodeArmControl(J3DNode*, J3DModel*) {
    /* Nonmatching */
}

/* 00000718-00000764       .text nodeCallBack_Bm1__FP7J3DNodei */
static BOOL nodeCallBack_Bm1(J3DNode* i_param_1, int i_param_2) {
    /* Nonmatching */
    if(i_param_2 == 0){
        if(j3dSys.getModel()->getUserArea() != NULL){
            reinterpret_cast<daNpc_Bm1_c*>(j3dSys.getModel()->getUserArea())->nodeWngControl(i_param_1,j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000764-00000900       .text nodeBm1Control__11daNpc_Bm1_cFP7J3DNodeP8J3DModel */
void daNpc_Bm1_c::nodeBm1Control(J3DNode*, J3DModel*) {
    /* Nonmatching */

}

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
                return !dComIfGs_isEventBit(0x1A80);
            }
            break;
        case 3:
            if(!dComIfGs_isSymbol(1)){
                return FALSE;
            }
            if(dComIfGs_isEventBit(0x1A80)){
                return dKy_daynight_check() == 0;
            }
            break;
        case 4:
            if(!dComIfGs_isSymbol(1)){
                return FALSE;
            }
            if(dComIfGs_isEventBit(0x1A80)){
                return dKy_daynight_check() == 1;
            }
            break;
    }
    return false;

}

/* 00000A9C-00000B38       .text init_PST_0__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_PST_0() {


    bool o_retval = false;
    if(!dComIfGs_isEventBit(1)){
        set_action(&daNpc_Bm1_c::demo_action1,NULL);
        fopAcM_OffStatus(this,0x3F);
        m884 = 1;
        o_retval = true;
    }
    return o_retval;
}

/* 00000B38-00000B84       .text init_PST_1__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_PST_1() {
    /* Nonmatching */
    set_action(&daNpc_Bm1_c::wait_action1,NULL);
    return true;
}

/* 00000B84-00000C0C       .text init_PST_2__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_PST_2() {
    /* Nonmatching */
    bool o_retval = false;
    if(!dComIfGs_isEventBit(0x1F40)){
        set_action(&daNpc_Bm1_c::wait_action3,NULL);
        o_retval = true;
    }
    return o_retval;
}

/* 00000C0C-00000CB8       .text init_PST_3__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_PST_3() {
    /* Nonmatching */
    bool result;
    result = dComIfGs_isSymbol(1) == 0;
    if(result){
        result = dComIfGs_isEventBit(0x1102) != 0;
        if(result){
            set_action(&daNpc_Bm1_c::wait_action1,NULL);
        }
    }
    return result;
}

/* 00000CB8-00000D58       .text init_PST_4__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::init_PST_4() {

    bool result = dComIfGs_isEventBit(0x1E80) == 0;
    if(result){
        m888 = 1;
        gravity = 0.0f;
        set_action(&daNpc_Bm1_c::wait_action9,NULL);
        fopAcM_OnStatus(this,0x4000);
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
    /* Nonmatching */
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
    if(!dComIfGs_isEventBit(0x1808)){
        result = dComIfGs_isEventBit(0x1220);
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
        result = dComIfGs_isEventBit(0x1808);
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

    if(dComIfGs_isEventBit(0x1620)){
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
    /* Nonmatching */
    static u8 a_att_dis_TBL[10][2];
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
    m82C = current.pos;
    s32 iVar5 = 0xFF;
    u32 param = fopAcM_GetParam(this);
    if(fopAcM_GetParamBit(param,16,8) != 0xFF){
        mPathRun.setInf(fopAcM_GetParamBit(param,16,8),fopAcM_GetRoomNo(this),true);

        if(mPathRun.getPath()){
            fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);
            iVar5 = 0xF0;    
        }else{
            return false;
        }

    }
    static char* a_staff_tbl[] = {""};
    m79C.setActorInfo2(a_staff_tbl[mSpecificType],this);
    m8FA = 0x16;
    bool cVar4;
    switch(mSpecificType){
        case Quill_0:
            cVar4 = init_PST_0();
            break;
        case Quill_1:
            cVar4 = init_PST_1();
            break;
        case Quill_2:
            cVar4 = init_PST_2();
            break;
        case Quill_3:
            cVar4 = init_PST_3();
            break;
        case Quill_4:
            cVar4 = init_PST_4();
            break;
        case Akoot:
            cVar4 = init_KKT_0();
            break;
        case Skett:
            cVar4 = init_SKT_0();
            break;
        case Basht:
            cVar4 = init_BMB_0();
            break;
        case Bisht:
            cVar4 = init_BMB_1();
            break;
        case Hoskit:
            cVar4 = init_BMB_2();
            break;
        case Ilari_0xA:
            cVar4 = init_BMC_0();
            break;
        case Ilari_0xB:
            cVar4 = init_BMC_1();
            break;
        case Ilari_0xC:
            cVar4 = init_BMC_2();
            break;
        case Pashli:
            cVar4 = init_BMC_3();
            break;
        case Namali:
            cVar4 = init_BMD_0();
            break;
        case Kogoli:
            cVar4 = init_BMD_1();
            break;
        default:
            cVar4 = '\0';
            break;
    }
    if(cVar4 != 0){
    shape_angle = current.angle;
    }else{
        return false;
    }
    mStts.Init(iVar5,0xFF,this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);

    if(m885){
        m71C->setMorf(0.0f);

    }else{
        m710->setMorf(0.0f);
    }
    m6EC->setMorf(0.0f);
    setMtx(true);
    return true;
}

/* 00001404-000017A8       .text setMtx__11daNpc_Bm1_cFb */
void daNpc_Bm1_c::setMtx(bool i_param_1) {
    /* Nonmatching */
    if(m897 == 0){
        int uVar5 = 0;
        plyTexPttrnAnm();
        if(mObjAcch.ChkGroundHit()){
            uVar5 = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
        }
        s8 reverb = dComIfGp_getReverb(fopAcM_GetRoomNo(this));
        m87A = mpMorf->play(&eyePos,uVar5,reverb);
        if(mpMorf->getFrame() < m844){
            m87A = 1;
        }
        m844 = mpMorf->getFrame();
        if(m885){
            m71C->play(&eyePos,0,0);
        }else{
            m710->play(&eyePos,0,0);
        }
        m6EC->play(&eyePos,0,0);
        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    if(!m885){
        m710->calc();
    }else{
        m71C->calc();
    }
    m6EC->getModel()->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
    m6EC->calc();
    if(m6D8){
        if(m8FA == 4){
            mDoMtx_stack_c::copy(m71C->getModel()->getAnmMtx(m_UNK_jnt_num));
            mDoMtx_stack_c::transM(13.5f,3.0f,-5.5f);
            mDoMtx_stack_c::XYZrotM(cM_deg2s(-132.001),cM_deg2s(-114),cM_deg2s(145.005));
            m6D8->setBaseTRMtx(mDoMtx_stack_c::get());
        }else{
            m6D8->setBaseTRMtx(m71C->getModel()->getAnmMtx(m_UNK_jnt_num));
        }
        m6D8->calc();
    }
    if(m6DC){
        m6DC->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_bbone_jnt_num));
        m6DC->calc();
    }
    if(m6E0){
        m6E0->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_bbone_jnt_num));
        m6E0->calc();
    }
    if(m885 && m6E4){
        m6E4->setBaseTRMtx(m71C->getModel()->getAnmMtx(m_UNK_jnt_num));
        m6E4->calc();      
    }
    setPrtcl_Flyaway();
    setPrtcl_Land0();
    setPrtcl_Hane0();
    setPrtcl_Hane1();
    setAttention(i_param_1);
}

/* 000017A8-000017F8       .text anmNum_toResID__11daNpc_Bm1_cFi */
char* daNpc_Bm1_c::anmNum_toResID(int i_param_1) {
    /* Nonmatching */
    static char* a_BCKName_TBL[0x16] = {"m5\0bm_dwait","bm_fly01","bm_lookup","bm_orooro","bm_wait01","bm_wait02","bm_talk01","bm_nadame","bm_gliding","bm_endurance","bm_flyaway","bm_flyaway2","bm_talk02","bm_landing","bm_walk","bm02_wait01","bm02_talk01","bm02_talk02","bm_talk03","bm_turn","bm_walk02","bm_check"};
    strcpy(l_BCKName,a_BCKName_TBL[i_param_1]);
    return strcat(l_BCKName,".bck");
}

/* 000017F8-00001848       .text headAnmNum_toResID__11daNpc_Bm1_cFi */
char* daNpc_Bm1_c::headAnmNum_toResID(int i_param_1) {
    /* Nonmatching */
    static char* a_BCKName_TBL[0x16] = {"bmhead01_dwait","bmhead01_fly01","bmhead01_lookup","bmhead01_orooro","bmhead01_wait01","bmhead01_wait02","bmhead01_talk01","bmhead01_nadame","bmhead01_gliding","bmhead01_endurance","bmhead01_flyaway","bmhead01_flyaway2","bmhead01_talk02","bmhead01_landing","bmhead01_walk","bmhead01_wait01","bmhead01_wait01","bmhead01_wait01","bmhead01_talk03","bmhead01_turn","bmhead01_wait01","bmhead01_wait01"};
    strcpy(l_BCKName,a_BCKName_TBL[i_param_1]);
    return strcat(l_BCKName,".bck");
}

/* 00001848-00001898       .text wingAnmNum_toResID__11daNpc_Bm1_cFi */
char* daNpc_Bm1_c::wingAnmNum_toResID(int i_param_1) {
    /* Nonmatching */
    static char* a_BCKName_TBL[0x16] = {"bmwing_dwait","bmwing_fly01","bmwing_lookup","bmwing_orooro","bmarm_wait01","bmarm_wait02","bmarm_talk01","bmarm_nadame","bmwing_gliding","bmwing_endurance","bmarm_flyaway","bmwing_flyaway2","bmarm_talk02","bmarm_landing","bmarm_walk","bmarm02_wait01","bmarm02_talk01","bmarm02_talk02","bmarm_talk03","bmarm_turn","bmarm_walk02","bmarm_check"};
    strcpy(l_BCKName,a_BCKName_TBL[i_param_1]);
    return strcat(l_BCKName,".bck");
}

/* 00001898-00001948       .text btpNum_toResID__11daNpc_Bm1_cFi */
char* daNpc_Bm1_c::btpNum_toResID(int i_param_1) {
    /* Nonmatching */
    static char* a_BTPName_TBL[] = {"bmhead01"};
    static char* a_BTPName_TBL_2[] = {"bmhead01","bmhead01","bmhead01","bmhead01","bmhead01","bmhead02","bmhead07","bmhead07","bmhead05","bmhead03","bmhead04","bmhead04","bmhead09","bmhead06","bmhead04"};
    if(!strcmp(a_BTPName_TBL[i_param_1],"bmhead01")){
        strcpy(l_BTPName,a_BTPName_TBL_2[i_param_1]);
        return strcat(l_BTPName,".btp");
    }else{
        strcpy(l_BTPName,a_BTPName_TBL[i_param_1]);
        return strcat(l_BTPName,".btp");      
    }
}

/* 00001948-00001A4C       .text setBtp__11daNpc_Bm1_cFbi */
bool daNpc_Bm1_c::setBtp(bool i_param_1, int i_param_2) {
    /* Nonmatching */
    J3DModelData* model_data = m6EC->getModel()->getModelData();
    char* res_id = btpNum_toResID(i_param_2);
    m_hed_tex_pttrn = reinterpret_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes(mArcName,res_id));
    JUT_ASSERT(DEMO_SELECT(0x529,0x529),m_hed_tex_pttrn != NULL);
    int iVar1 = m6F4.init(model_data,m_hed_tex_pttrn,1,2,1.0f,0,-1,i_param_1,0);
    bool o_retval = iVar1 == 1;
    if(o_retval){
        m708 = 0;
        m70A = 0;
    }
    return o_retval;
}

/* 00001A4C-00001A74       .text iniTexPttrnAnm__11daNpc_Bm1_cFb */
void daNpc_Bm1_c::iniTexPttrnAnm(bool i_param_1) {
    setBtp(i_param_1,m8F9);
}

/* 00001A74-00001B20       .text plyTexPttrnAnm__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::plyTexPttrnAnm() {
    /* Nonmatching */
    if(m8F9 || !cLib_calcTimer(&m70A)){
        m708 += 1;
        if(m708 >= m_hed_tex_pttrn->getFrameMax()){
            if(m8F9 != 0){
                m708 = m_hed_tex_pttrn->getFrameMax();
            }else{
                m70A = cM_rndF(60.0f) + 30.0f;
                m708 = 0;

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
BOOL daNpc_Bm1_c::setAnm_anm(daNpc_Bm1_c::anm_prm_c* i_param_1) {

    if(m8FA == i_param_1->m0){
        return 1;
    }
    m8FA = i_param_1->m0;
    dNpc_setAnmFNDirect(mpMorf,i_param_1->mC,i_param_1->m4,i_param_1->m8,anmNum_toResID(m8FA),NULL,mArcName);
    m885 = i_param_1->m10 == 1;
    if(m885){
        dNpc_setAnmFNDirect(m71C,i_param_1->mC,i_param_1->m4,i_param_1->m8,wingAnmNum_toResID(m8FA),NULL,mArcName);

    }else{
        dNpc_setAnmFNDirect(m710,i_param_1->mC,i_param_1->m4,i_param_1->m8,wingAnmNum_toResID(m8FA),NULL,mArcName);
 
    }
    dNpc_setAnmFNDirect(m6EC,i_param_1->mC,i_param_1->m4,i_param_1->m8,wingAnmNum_toResID(m8FA),NULL,mArcName);

    delPrtcl_Hane0();
    delPrtcl_Hane1();
    switch(m8FA){
        case 2:
            setPrtcl_Hane1();
            break;
        case 3:
            setPrtcl_Hane0();
            break;
    }
    m844 = 0;
    m87B = 0;
    m87A = 0;
    return TRUE;
}

/* 00001CF4-00001D60       .text setAnm_NUM__11daNpc_Bm1_cFii */
void daNpc_Bm1_c::setAnm_NUM(int i_param_1, int i_param_2) {
    /* Nonmatching */
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
        setAnm_tex(a_anm_prm_tbl[i_param_1].m1);
    }
    setAnm_anm(&a_anm_prm_tbl[i_param_1]);
}

/* 00001D60-00001DE0       .text setAnm__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::setAnm() {
    /* Nonmatching */
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
    if(a_anm_prm_tbl[m8FE].m1 >= 0){
        setAnm_tex(a_anm_prm_tbl[m8FE].m1);
    }
    if(a_anm_prm_tbl[m8FE].m0 >= 0){
        setAnm_anm(&a_anm_prm_tbl[m8FE]);
    }
    return true;
}

/* 00001DE0-00001E24       .text setPlaySpd__11daNpc_Bm1_cFf */
void daNpc_Bm1_c::setPlaySpd(float i_speed) {
    /* Nonmatching */
    if(m885){
        m71C->setPlaySpeed(i_speed);
        m6EC->setPlaySpeed(i_speed);
        mpMorf->setPlaySpeed(i_speed);
        return;
    }else{
        m710->setPlaySpeed(i_speed);
        m6EC->setPlaySpeed(i_speed);
        mpMorf->setPlaySpeed(i_speed);
    }
}

/* 00001E24-00001E28       .text chg_anmTag__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::chg_anmTag() {
    /* Nonmatching */
}

/* 00001E28-00001E2C       .text control_anmTag__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::control_anmTag() {
    /* Nonmatching */
}

/* 00001E2C-00001EFC       .text chg_anmAtr__11daNpc_Bm1_cFUc */
void daNpc_Bm1_c::chg_anmAtr(unsigned char i_param_1) {
    /* Nonmatching */
    if(i_param_1 >= 0xF || i_param_1 == m8F7){
        return;
    }
    m8F7 = i_param_1;
    if(mSpecificType == Skett || mSpecificType == Akoot){
        switch(m8F7){
            case 9:
                m900 = 1;
                m_jnt.setTrn();
                break;
            case 0xD:
                if(m808 != -1){
                    fopAc_ac_c* actor = searchByID(m808);
                    m82C = actor->eyePos;
                    m900 = 2;
                }
                break;
        }
    }
    setAnm_ATR(1);
}

/* 00001EFC-00001F68       .text control_anmAtr__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::control_anmAtr() {
    /* Nonmatching */
    switch(m8F7){
        case 8:
            if(m87A != 0){
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
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[] = {0};
    if(i_param_1 != 0){
        setAnm_tex(a_anm_prm_tbl[m8F7].m1);
    }
    setAnm_anm(&a_anm_prm_tbl[m8F7]);
}

/* 00001FD0-000020D8       .text anmAtr__11daNpc_Bm1_cFUs */
void daNpc_Bm1_c::anmAtr(unsigned short i_param_1) {
    dComIfG_MesgCamInfo_c* caminfo = dComIfGp_getMesgCameraInfo();
    if(m883 != 0 &&  this != caminfo->mActor[caminfo->mBasicID-1]){
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
            dComIfGp_setMesgAnimeTagInfo(0xFF);
            if(uVar1 != 0xFF && m8F8 != uVar1){
                m8F8 = uVar1;
                chg_anmTag();
            }
            break;
        case 0xE:
            m905 = 0;
            break;
    }
    control_anmAtr();
    control_anmTag();

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
                    fopAcM_OffStatus(this,0x4000);
                    break;
                case 2:
                    break;
            }
            m8FD = 0;
        }
    }else if(eventInfo.checkCommandTalk() && (m8FD == 1 || m8FD == 2)){
        m8FD = 0;
        m895 = 1;
    }
}

/* 00002234-00002304       .text chk_manzai__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::chk_manzai() {
    BOOL o_retval = true;
    if(m808 != -1){
        daNpc_Bm1_c* actor = static_cast<daNpc_Bm1_c*>(searchByID(m808));
        if(actor == NULL){
            // o_retval = false;
            return false;
        }else{
            m883 = actor->m8FE == 9;
            if(m883){
                dComIfGp_setMesgCameraInfoActor(this,actor,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
            }else{
                fopAcM_OnStatus(actor,fopAcStts_UNK4000_e);
                actor->m883 = 1;
                o_retval = false;
            }
        }
    }
    return o_retval;
}

/* 00002304-000023A0       .text chk_talk__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::chk_talk() {
    /* Nonmatching */
    u32 uVar3 = TRUE;
    m87D = 0xFF;
    if(dComIfGp_event_chkTalkXY()){
        // if(bVar1){
            if(dComIfGp_evmng_ChkPresentEnd()){
                m87D = dComIfGp_event_getPreItemNo();

            }else{
                uVar3 = FALSE;
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
    /* Nonmatching */
    cXyz dstPos;
    cXyz* dstPos_p;
    cXyz local_2c;
    s16 desiredYrot;
    m85C = m_jnt.getHead_y();
    m85E = m_jnt.getBackbone_y();
    m860 = current.angle.y;
    // local_2c.set(current.pos);
    local_2c.x = current.pos.x;
    local_2c.y = current.pos.y;
    local_2c.z = current.pos.z;
    local_2c.y = eyePos.y;
    dstPos.setall(0.0f);
    dstPos_p = NULL;
    desiredYrot = current.angle.y;
    bool headOnlyFollow = m896;

    switch(m900){
        case 1:
            dstPos = dNpc_playerEyePos(-20.0f);
            dstPos_p = &dstPos;
            local_2c.x = current.pos.x;
            local_2c.y = current.pos.y;
            local_2c.z = current.pos.z;
            local_2c.y = eyePos.y;
            break;
        case 2:
            dstPos = m82C;
            dstPos_p = &dstPos;
            local_2c.x = current.pos.x;
            local_2c.y = current.pos.y;
            local_2c.z = current.pos.z;
            local_2c.y = eyePos.y;
            break;
        case 3:
            desiredYrot = m876;
            break;
    }
    cLib_addCalcAngleS2(&m874,l_HIO.children[mType-1].hio_prm.m12,4,0x800);
    if(!m_jnt.trnChk()){
        m874 = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y,dstPos_p,local_2c,desiredYrot,m874,headOnlyFollow);
}

/* 00002590-00002A58       .text next_msgStatus__11daNpc_Bm1_cFPUl */
u16 daNpc_Bm1_c::next_msgStatus(unsigned long* i_msg_no) {
    /* Nonmatching */
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
        case 7:
            o_retval = 1;
            break;
        case 8:
            o_retval = 2;
            break;
        case 13:
            o_retval = 4;
            break;
        case 14:
            o_retval = 8;
            break;
        case 15:
            o_retval = 0x10;
            break;
    }
    return o_retval;
}

/* 00002AC4-00002B00       .text getMsg_PST_1__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_PST_1() {
    /* Nonmatching */
    return dComIfGs_isEventBit(0x1401) ? 0xC93 : 0xC92;
}

/* 00002B00-00002B40       .text getMsg_PST_3__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_PST_3() {
    /* Nonmatching */
    return dComIfGs_isEventBit(0x2202) ? 0x18A3 : 0x18A1;
}

/* 00002B40-00002BE8       .text getMsg_SKT_0__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_SKT_0() {
    /* Nonmatching */

    u32 o_retval;
    int compare = dComIfGs_isSymbol(1);
    if(compare){
        compare = dComIfGs_isEventBit(0x1A80);
        if(!compare){
            o_retval = 0x186B;
            return o_retval;
        }
        else if(!dComIfGs_isEventBit(0x1820)){
            o_retval = 0x1873;
            return o_retval;
        }
        else{
            compare = (!dComIfGs_isEventBit(0x2E04));
            if(compare){
                o_retval = 0x187B;
                return o_retval;
            }else{
                o_retval = 0x1883;
                return o_retval;
            }
        }
    }
    return 0;
}

/* 00002BE8-00002C90       .text getMsg_KKT_0__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_KKT_0() {
    /* Nonmatching */
    u32 o_retval;
    int compare = dComIfGs_isSymbol(1);
    if(compare){
        compare = dComIfGs_isEventBit(0x1A80);
        if(!compare){
            o_retval = 0x186F;
            return o_retval;
        }
        else if(!dComIfGs_isEventBit(0x1820)){
            o_retval = 0x1877;
            return o_retval;
        }
        else{
            compare = (!dComIfGs_isEventBit(0x2E04));
            if(compare){
                o_retval = 0x187F;
                return o_retval;
            }else{
                o_retval = 0x1887;
                return o_retval;
            }
        }
    }
    return 0;
}

/* 00002C90-00002DBC       .text getMsg_BMB_0__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMB_0() {
    /* Nonmatching */
    s8 reg = dComIfGs_getEventReg(0xB8FF);
    s8 mask = getBitMask();
    u32 var_r29 = 0;
    if (reg&mask) {
        switch (mSpawnCondition) {
        case 1:
            var_r29 = 0x18A0U;
            break;
        case 2:
            var_r29 = 0x18B1U;
            break;
        case 3:
            var_r29 = 0x18B3U;
            break;
        case 4:
            var_r29 = 0x18B5U;
            break;
        }
    } else {
        switch (mSpawnCondition) {
        case 1:
            var_r29 = 0x189FU;
            break;
        case 2:
            var_r29 = 0x18B0U;
            break;
        case 3:
            var_r29 = 0x18B2U;
            break;
        case 4:
            var_r29 = 0x18B4U;
            break;
        }
    }
    if (var_r29 != 0U) {
        dComIfGs_setEventReg(0xB8FFU, reg|mask);
    }
    return var_r29;
}

/* 00002DBC-00002EE8       .text getMsg_BMB_1__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMB_1() {
    /* Nonmatching */
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
        dComIfGs_setEventReg(0xB8FFU, reg|mask);
    }
    return var_r29;
}

/* 00002EE8-00003010       .text getMsg_BMB_2__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMB_2() {
    /* Nonmatching */
    if(m87C != 0){
        return 0x199C;
    }
    if(m87D == 0x47){
        if(dComIfGs_isEventBit(0x2180)){
            return 0x199D;
        }
        if(dComIfGs_isEventBit(0x2140)){
            return (dComIfGs_getBeastNum(2) >= 0x14) ? 0x19A1: 0x19A0;
        }
        dComIfGs_onEventBit(0x2140);
        return 0x199E;
    }
    else if(m87D != 0xFF){
        return 0x19A5;
    }
    if(dComIfGs_isEventBit(0x2180)){
        return 0x199B;
    }
    if(dComIfGs_isEventBit(0x2001)){
        return 0x199A;
    }
    return dComIfGs_isEventBit(0x2120)? 0x1998 : 0x1996;


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
    /* Nonmatching */
    if(m87C != 0){
        return 0x1EF7;
    }
    if(dComIfGs_isGetItemReserve(0xF)){
        return 0x1EF9;
    }
    return dComIfGs_isEventBit(0x1908) ? 0x1EF2 : 0x1EF0;
}

/* 000030D0-000031FC       .text getMsg_BMC_3__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMC_3() {
    /* Nonmatching */
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
        dComIfGs_setEventReg(0xB8FF, reg|mask);
    }
    return var_r29;
}

/* 000031FC-00003328       .text getMsg_BMD_0__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMD_0() {
    /* Nonmatching */
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
        dComIfGs_setEventReg(0xB8FF, reg|mask);
    }
    return var_r29;
}

/* 00003328-00003470       .text getMsg_BMD_1__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg_BMD_1() {
    /* Nonmatching */
    s8 reg = dComIfGs_getEventReg(0xB8FF);
    s8 mask = getBitMask();
    u32 var_r29 = 0;
    if (reg&mask) {
        if(!dComIfGs_isEventBit(0x1820)){
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
        if(!dComIfGs_isEventBit(0x1820) ){
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
        dComIfGs_setEventReg(0xB8FF, reg|mask);
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
    case Akoot:
        o_retval = getMsg_KKT_0();
        break;
    case Skett:
        o_retval = getMsg_SKT_0();
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
    /* Nonmatching */
    dAttention_c& attention = dComIfGp_getAttention();
    if (attention.LockonTruth()) {
        return this == attention.LockonTarget(0);
    } else {
        return this == attention.ActionTarget(0);
    }

}

/* 000035C8-00003630       .text setAttention__11daNpc_Bm1_cFb */
void daNpc_Bm1_c::setAttention(bool i_setEyePos) {
    /* Nonmatching */
    attention_info.position.set(
        current.pos.x,
        current.pos.y + l_HIO.children[mType-1].hio_prm.mAttPosOffsetY,
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
    /* Nonmatching */
    fopAc_ac_c* o_actor = NULL;
    fopAcM_SearchByID(i_procID,&o_actor);
    return o_actor;
}

/* 00003664-00003714       .text partner_srch_sub__11daNpc_Bm1_cFPFPvPv_Pv */
bool daNpc_Bm1_c::partner_srch_sub(void* (*i_searchFunc)(void*, void*)) {
    /* Nonmatching */
    bool o_retval = false;
    m808 = -1;
    l_check_wrk = 0;
    for(int i = 0; i < 20; i++){
        l_check_inf[i] = 0;
    }
    fpcM_Search(i_searchFunc,this);
    if(l_check_wrk != 0){
        m808 = fopAcM_GetID(l_check_inf[0]);     
        o_retval = true;
    }
    return o_retval;
}

/* 00003714-00003818       .text partner_srch__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::partner_srch() {
    /* Nonmatching */
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
                    fopAc_ac_c* actor = searchByID(m808);
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
    /* Nonmatching */
    cXyz cmpCoords;
    cXyz idxCoords;

    s32 point_idx;
    u32 o_retval = 0;
    if(mPathRun.isPath() && (point_idx = mPathRun.getIdx(),dPath_ChkClose(mPathRun.getPath()))){
        if(mPathRun.chkPointPass(current.pos,mPathRun.getDir())){
            mPathRun.nextIdxAuto();
            o_retval = 1;
        }
        if(i_param_1){
            return o_retval;
        }


    }
    // if(mPathRun.isPath()){
    //     point_idx = mPathRun.getIdx();
    //     if(dPath_ChkClose(mPathRun.getPath())){


    //         // if(mPathRun.chkPointPass(current.pos,mPathRun.getDir())){
    //         //     mPathRun.nextIdxAuto();
    //         //     o_retval = 1;
    //         // }
    //         if(mPathRun.chkPointPass(current.pos, mPathRun.getDir())) {
    //             mPathRun.nextIdxAuto();
    //             o_retval = true;
    //         }
    //         if(!i_param_1){
    //             return o_retval;
    //         }

    //     }
    // }

    if((m838 - current.pos).absXZ() <= m858){
        o_retval = 1;
        if(mPathRun.isPath()){
            if(point_idx < mPathRun.maxPoint()-2){
                mPathRun.nextIdxAuto();
            }else{
                o_retval =2 ;
            }
        }
        if(!i_param_1){
            return o_retval;
        }
    }

    u8 idx = mPathRun.getIdx();
    idxCoords = mPathRun.getPoint(idx);
    cmpCoords = mPathRun.getPoint(point_idx);
    m889 = cmpCoords.y <= idxCoords.y;

    return o_retval;
}

/* 00003A24-00003A68       .text bm_setFlyAnm__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_setFlyAnm() {
    /* Nonmatching */
    if(m889){
        setAnm_NUM(9,1);
    }else{
        setAnm_NUM(8,1);
    }
}

/* 00003A68-00003BF0       .text bm_clcFlySpd__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_clcFlySpd() {
    /* Nonmatching */
    s16 target;
    if(m8F4 == 2 || m8F4 == 5){
        target = cLib_targetAngleY(&current.pos,&m838);
        cLib_addCalcAngleS(&current.angle.y,target,l_HIO.children[mType-1].hio_prm.m1A,l_HIO.children[mType-1].hio_prm.m1C,0);
    }
    switch(m8F4){

        case 3:
            speed.y -= m854;
            break;
        case 2:
        case 5:

            if(m889 != 0){
                if (m838.y > current.pos.y) {

                    speed.y = cLib_maxLimit(speed.y + m854,m84C);
                } else {
                    speed.y = cLib_minLimit(speed.y - m854,0.0f);
                }
            }else if(m838.y > current.pos.y){
                speed.y = cLib_maxLimit(speed.y + m854,0.0f);
            }else{
                speed.y -= m854;
            }
            break;    
        case 0:
        case 1:
            break;
    }
    cLib_chaseF(&speedF,m848,m850);

}

/* 00003BF0-00003C64       .text bm_clcMovSpd__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_clcMovSpd() {
    /* Nonmatching */
    s16 target = cLib_targetAngleY(&current.pos,&m838);
    cLib_addCalcAngleS(&current.angle.y,target,l_HIO.children[mType-1].hio_prm.m34,l_HIO.children[mType-1].hio_prm.m36,0);
    cLib_chaseF(&speedF,m848,m850);
}

/* 00003C64-00003ED4       .text bm_flyMove__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::bm_flyMove() {

    s32 temp_r3;

    if (m8F4 == 0) {
        return 0U;
    }
    if (m88A != 0) {
        m887 = 1;
        return 1U;
    }
    if (mPathRun.isPath()) {
        m838 = mPathRun.getPoint(mPathRun.getIdx());
    }
    switch (m8F4) {                         /* switch 1; irregular */
    case 1:                                         /* switch 1 */
        if ((s32) m8FA != 0xA) {
            setAnm_NUM(0xA, 1);
        } else if (m87A != 0) {
            m8F4 = 2;
        }
        break;
    case 2:                                         /* switch 1 */
        if (m8FA != 0xB) {
            setAnm_NUM(0xB, 1);
            speed.y = m848 * 0.7f;
        } else if (m87A != 0) {
            m8F4 = 5;
            m88A = 1;
            bm_setFlyAnm();
        }
        goto case_5;
    case 3:                                         /* switch 1 */
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


    case 4:                                         /* switch 1 */
        if ((s32) m8FA != 0xD) {
            setAnm_NUM(0xD, 1);
        } else if ((s8) m87A != 0) {
            gravity = -4.5f;
            setAnm_NUM(4, 1);
            m8F4 = 0;
            m88A = 1;
        }

        break;
    case 5:                                         /* switch 1 */
case_5:
        bm_clcFlySpd();
        temp_r3 = bm_movPass(1);
        switch (temp_r3) {                          /* switch 2; irregular */
        case 1:                                     /* switch 2 */
            if (m8F4 != 2) {
                bm_setFlyAnm();
                m8F4 = 5;
            }
            m88A = 1;
            break;
        case 2:                                     /* switch 2 */
            m8F4 = 3;
            m848 = 0.0f;
            m88A = 1;
            break;
        }
        break;
    }
    return TRUE;
}

/* 00003ED4-00003FA4       .text bm_nMove__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_nMove() {
    /* Nonmatching */
    if(m88B){
        m887 = 1;
        return;
    }
    switch(m8FA){
        case 0x14:
        case 0xE:
            bm_clcMovSpd();
            f32 speed = speedF * l_HIO.children[mType-1].hio_prm.m38;
            //speed *= ;
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
    /* Nonmatching */
    if (m8FA == 0xB && mpMorf->checkFrame(10.0f)){

        delPrtcl_Flyaway();
        m8D4 = dComIfGp_particle_set(
            0x8275,
            &m898,
            &current.angle,
            NULL,
            -1,NULL,fopAcM_GetRoomNo(this),
            &tevStr.mColorK0,
            &tevStr.mColorK0
        );

        m8D8 = dComIfGp_particle_set(
            0x8275,
            &m8A4,
            &current.angle,
            NULL,-1,NULL,fopAcM_GetRoomNo(this),
            &tevStr.mColorK0,
            &tevStr.mColorK0
        );

        if (m8D4 != NULL) {
            m8D4->setStatus(0x40);
        }

        if (m8D8 != NULL) {
            JGeometry::TVec3<f32> rot(-1.0f,1.0f,0.0f);
            m8D8->setStatus(0x40);
            m8D8->setDirection(rot);
        }
    }
}

/* 000040EC-00004160       .text delPrtcl_Flyaway__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Flyaway() {
    /* Nonmatching */
    JPABaseEmitter* emitter;
    if(m8D4){
#if VERSION > VERSION_DEMO
        m8D4->clearStatus(0x40);
#endif
        emitter = m8D4;
        emitter->setMaxFrame(-1);
        emitter->setStatus(1);
        m8D4 = NULL;
    }

    if(m8D8){
#if VERSION > VERSION_DEMO
        m8D8->clearStatus(0x40);
#endif
        emitter = m8D8;
        emitter->setMaxFrame(-1);
        emitter->setStatus(1);
        m8D8 = NULL; 
    }
}

/* 00004160-000042A8       .text setPrtcl_Land0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Land0() {
    /* Nonmatching */
    if (m8FA == 0xD && mpMorf->checkFrame(1.0f)){

        delPrtcl_Land0();
        m8DC = dComIfGp_particle_set(
            0x8276,
            &m8B0,
            &current.angle,
            NULL,
            0xFF,
            NULL,
            fopAcM_GetRoomNo(this),
            &tevStr.mColorK0,
            &tevStr.mColorK0
        );

        m8E0 = dComIfGp_particle_set(
            0x8276,
            &m8BC,
            &current.angle,
            NULL,
            0xFF,
            NULL,
            fopAcM_GetRoomNo(this),
            &tevStr.mColorK0,
            &tevStr.mColorK0
        );

        if (m8DC != NULL) {

            m8DC->setStatus(0x40);
        }

        if (m8E0 != NULL) {
            JGeometry::TVec3<f32> rot(-1.0f,0.5f,0.0f);
            m8E0->setStatus(0x40);
            m8E0->setDirection(rot);


        }
    }
}

/* 000042A8-0000431C       .text delPrtcl_Land0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Land0() {
    /* Nonmatching */
    JPABaseEmitter* emitter;
    if(m8DC){
#if VERSION > VERSION_DEMO
        m8DC->clearStatus(0x40);
#endif
        emitter = m8DC;
        emitter->setMaxFrame(-1);
        emitter->setStatus(1);
        m8DC = NULL;
    }

    if(m8E0){
#if VERSION > VERSION_DEMO
        m8E0->clearStatus(0x40);
#endif
        emitter = m8E0;
        emitter->setMaxFrame(-1);
        emitter->setStatus(1);
        m8E0 = NULL; 
    }
}

/* 0000431C-000043E0       .text setPrtcl_Hane0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Hane0() {

    delPrtcl_Hane0();
    m8E4 = dComIfGp_particle_set(
        0x80D6,
        &current.pos,
        NULL,
        NULL,
        0xFF,
        NULL,
        fopAcM_GetRoomNo(this),
        NULL,
        NULL
    );

    m8E8 = dComIfGp_particle_set(
        0x80D6,
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

    if(m8E4){
        m8E4->setGlobalRTMatrix(m710->getModel()->getAnmMtx(m716));
    }
    if(m8E8){
        m8E8->setGlobalRTMatrix(m710->getModel()->getAnmMtx(m717));
    }
}

/* 00004470-000044C4       .text delPrtcl_Hane0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Hane0() {

    JPABaseEmitter* emitter;
    if(m8E4){
        emitter = m8E4;
        emitter->setMaxFrame(-1);
        emitter->setStatus(1);
        m8E4 = NULL;
    }
    if(m8E8){
        emitter = m8E8;
        emitter->setMaxFrame(-1);
        emitter->setStatus(1);
        m8E8 = NULL;
    }

}

/* 000044C4-000045B8       .text setPrtcl_Hane1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Hane1() {
    /* Nonmatching */
    delPrtcl_Hane1();
    m8EC = dComIfGp_particle_set(
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
    if(m8EC){
        m8EC->setStatus(0x40);
    }
    m8F0 = dComIfGp_particle_set(
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
    if(m8F0){
        m8F0->setStatus(0x40);
    }
}

/* 000045B8-00004648       .text flwPrtcl_Hane1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::flwPrtcl_Hane1() {
    /* Nonmatching */
    if(m8EC){
        m8EC->setGlobalRTMatrix(m710->getModel()->getAnmMtx(m716));
    }
    if(m8F0){
        m8F0->setGlobalRTMatrix(m710->getModel()->getAnmMtx(m717));
    }
}

/* 00004648-000046BC       .text delPrtcl_Hane1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Hane1() {
    /* Nonmatching */
    JPABaseEmitter* emitter;
    if(m8EC){
#if VERSION > VERSION_DEMO
        m8EC->clearStatus(0x40);
#endif
        emitter = m8EC;
        emitter->setMaxFrame(-1);
        emitter->setStatus(1);
        m8EC = NULL;
    }
    if(m8F0){
#if VERSION > VERSION_DEMO
        m8F0->clearStatus(0x40);
#endif
        emitter = m8F0;
        emitter->setMaxFrame(-1);
        emitter->setStatus(1);
        m8F0 = NULL;
    }
}

/* 000046BC-000049B8       .text decideType__11daNpc_Bm1_cFii */
bool daNpc_Bm1_c::decideType(int i_type_param, int i_spawn_cond_param) {
    /* Nonmatching */
    mSpawnCondition = 0;
    mType = t_Invalid;
    mSpecificType = Invalid;
    fpc_ProcID procName = fopAcM_GetName(this);
    switch(procName){
    case 0x148:
        mType = 1;
        switch (i_type_param) {   
        case 0:
            mSpecificType = 0;
            break;
        case 1:                                     /* switch 2 */
            mSpecificType = 1;
            break;
        case 2:        
            mSpecificType = 2;
            break;
        case 3:                                     /* switch 2 */
            mSpecificType = 3;
            break;
        case 4:                                     /* switch 2 */
            mSpecificType = 4;
            break;
        default:
            return false;
        }
        break;
    case 0x149:                                     /* switch 1 */
        switch (i_type_param) {                             /* switch 3; irregular */
        case 0:                                     /* switch 3 */
            mSpecificType = 6;
            mType = 3;
            break;
        case 1:                                     /* switch 3 */
            mSpecificType = 5;
            mType = 2;
            break;
        default:                                    /* switch 3 */
            return 0U;
        }
        break;
    case 0x14A:                                     /* switch 1 */
        switch (i_type_param) {                             /* switch 4; irregular */
        case 0:                                     /* switch 4 */
            mSpecificType = 7;
            mType = 4;
            break;
        case 1:                                     /* switch 4 */
            mSpecificType = 8;
            mType = 5;
            break;
        case 2:                                     /* switch 4 */
            mSpecificType = 9;
            mType = 6;
            break;
        default:                                    /* switch 4 */
            return 0U;
        }
        break;
    case 0x14B:                                     /* switch 1 */
        switch (i_type_param) {                             /* switch 5; irregular */
        case 0:                                     /* switch 5 */
            mSpecificType = 0xA;
            mType = 7;
            break;
        case 1:                                     /* switch 5 */
            mSpecificType = 0xB;
            mType = 7;
            break;
        case 2:                                     /* switch 5 */
            mSpecificType = 0xC;
            mType = 7;
            break;
        case 3:                                     /* switch 5 */
            mSpecificType = 0xD;
            mType = 8;
            break;
        default:                                    /* switch 5 */
            return 0U;
        }
        break;
    case 0x14C:                                     /* switch 1 */
        switch (i_type_param) {                             /* switch 6; irregular */
        case 0:                                     /* switch 6 */
            mSpecificType = 0xE;
            mType = 9;
            break;
        case 1:                                     /* switch 6 */
            mSpecificType = 0xF;
            mType = 0xA;
            break;
        default:                                    /* switch 6 */
            return 0U;
        }
        break;
    default:                                        /* switch 1 */
        return 0U;
    }

    switch (i_spawn_cond_param) {                         /* switch 7; irregular */
    case 0:                                 /* switch 7 */
        mSpawnCondition = 1;
        break;
    case 1:                                 /* switch 7 */
        mSpawnCondition = 2;
        break;
    case 2:                                 /* switch 7 */
        mSpawnCondition = 3;
        break;
    case 3:                                 /* switch 7 */
        mSpawnCondition = 4;
        break;
    }
    switch(mSpecificType){
        case 0:
            strcpy(mArcName, "Bm2");
            break;
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 0xA:
        case 0xB:
        case 0xC:
        case 0xD:
        case 0xE:
        case 0xF:
            strcpy(mArcName, "Bm");
            break;
        default:
            return false;
    }
    return true;
}

/* 000049B8-000049FC       .text eInit_setLocFlag__11daNpc_Bm1_cFPi */
void daNpc_Bm1_c::eInit_setLocFlag(int* i_param_1) {
    /* Nonmatching */
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
void daNpc_Bm1_c::eInit_setShapeAngleY(int* i_param_1, short i_param_2) {
    /* Nonmatching */
    m886 = false;
    if(i_param_1 == NULL){
        return;
    }
    m886 = *i_param_1 == 1;
    if(!m886){
        return;
    }
    shape_angle.y = i_param_2;
    return;
}

/* 00004A34-00004A50       .text eInit_setEvTimer__11daNpc_Bm1_cFPi */
void daNpc_Bm1_c::eInit_setEvTimer(int* i_param_1) {
    /* Nonmatching */
    m86C = false;
    if(i_param_1 == NULL){
        return;
    }
    m86C = *i_param_1;
    return;
}

/* 00004A50-00004B30       .text eInit_calcRelativPos__11daNpc_Bm1_cFP4cXyzPi */

cXyz daNpc_Bm1_c::eInit_calcRelativPos(cXyz* i_param_2, int* arg2) {
    /* Nonmatching */
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
        local_1c.setall(0.0f);
    }
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(sVar1);
    mDoMtx_stack_c::multVec(&local_1c,&local_28);
    return local_28; 
}

/* 00004B30-00004D10       .text eInit_ATTENTION___11daNpc_Bm1_cFPiPiPiP4cXyzPiPiPi */
void daNpc_Bm1_c::eInit_ATTENTION_(int*, int*, int*, cXyz*, int*, int*, int*) {
    /* Nonmatching */
}

/* 00004D10-00004DC4       .text eInit_SET_PLYER_GOL___11daNpc_Bm1_cFPiP4cXyzPi */
void daNpc_Bm1_c::eInit_SET_PLYER_GOL_(int*, cXyz*, int*) {
    /* Nonmatching */
}

/* 00004DC4-00004DD4       .text eInit_prmFloat__11daNpc_Bm1_cFPff */
void daNpc_Bm1_c::eInit_prmFloat(float*, float) {
    /* Nonmatching */
}

/* 00004DD4-00004FB8       .text eInit_FLY___11daNpc_Bm1_cFPiPfPfPfPf */
void daNpc_Bm1_c::eInit_FLY_(int*, float*, float*, float*, float*) {
    /* Nonmatching */
}

/* 00004FB8-00004FD8       .text eInit_DEL_ACTOR___11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eInit_DEL_ACTOR_() {
    /* Nonmatching */
}

/* 00004FD8-00005190       .text eInit_WLK___11daNpc_Bm1_cFPiPfPfP4cXyzPiPiPi */
void daNpc_Bm1_c::eInit_WLK_(int*, float*, float*, cXyz*, int*, int*, int*) {
    /* Nonmatching */
}

/* 00005190-0000519C       .text eInit_INI_EVN_1___11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eInit_INI_EVN_1_() {
    /* Nonmatching */
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
void daNpc_Bm1_c::eInit_SET_ANM_(int* arg0) {

    if (arg0 != NULL) {
        s32 temp_r4 = *arg0;
        if ((temp_r4 >= 0) && (temp_r4 <= 0x16)) {
            setAnm_NUM(temp_r4, 1);
        }
    }
}

/* 0000522C-00005368       .text eInit_MOV_PTH_POINT___11daNpc_Bm1_cFPiPiPiPi */
void daNpc_Bm1_c::eInit_MOV_PTH_POINT_(int* arg0, int* arg1, int* arg2, int* arg3) {
    /* Nonmatching - Regswap*/
    u8 idx;
    cXyz pathpos;
    if (mPathRun.isPath()) {
        idx = mPathRun.getIdx();
        if (arg2 != NULL) {
            idx = *arg2;
            idx = cLib_maxLimit(idx, mPathRun.maxPoint());

            mPathRun.setIdx(idx);
        }
        current.pos = mPathRun.getPoint(idx);
        mPathRun.nextIdxAuto();
        pathpos = mPathRun.getPoint(mPathRun.getIdx());
        current.angle.y = cLib_targetAngleY(&current.pos,&pathpos);
        if (arg0) {
            switch(*arg0){
                case 1:
                    current.angle.y = cLib_targetAngleY(&current.pos, &dComIfGp_getLinkPlayer()->current.pos);
                    break;
            }

        }else if (arg3 != NULL) {
            current.angle.y = *arg3;
        }
        eInit_SET_ANM_(arg1);
    }
    
}

/* 00005368-00005650       .text event_actionInit__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::event_actionInit(int arg0) {

  cXyz *pcVar1;
  int *puVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  int *piVar7;
  int *piVar8;
  int *piVar9;
  float *pfVar10;
  float *pfVar11;
  float *pfVar12;
  float *pfVar13;
            
  pcVar1 = dComIfGp_evmng_getMyXyzP(arg0,"Offst");
  puVar2 = dComIfGp_evmng_getMyIntegerP(arg0,"ActNo");
  piVar3 = dComIfGp_evmng_getMyIntegerP(arg0,"prm_0");
  piVar4 = dComIfGp_evmng_getMyIntegerP(arg0,"prm_1");
  piVar5 = dComIfGp_evmng_getMyIntegerP(arg0,"prm_2");
  piVar6 = dComIfGp_evmng_getMyIntegerP(arg0,"Angle");
  piVar7 = dComIfGp_evmng_getMyIntegerP(arg0,"Index");
  piVar8 = dComIfGp_evmng_getMyIntegerP(arg0,"Timer");
  piVar9 = dComIfGp_evmng_getMyIntegerP(arg0,"AnmNo");
  pfVar10 = dComIfGp_evmng_getMyFloatP(arg0,"Speed");
  pfVar11 = dComIfGp_evmng_getMyFloatP(arg0,"Accel");
  pfVar12 = dComIfGp_evmng_getMyFloatP(arg0,"Spd_y");
  pfVar13 = dComIfGp_evmng_getMyFloatP(arg0,"Acc_y");

  if (puVar2 != NULL) {
    m8F6 = *puVar2;
    switch(m8F6) {
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
      eInit_MOV_PTH_POINT_(piVar3,piVar9,piVar7,piVar6);
      break;
    case 0x16:
    case 0x17:
      eInit_FLY_(piVar3,pfVar10,pfVar12,pfVar11,pfVar13);
      break;
    case 0x18:
      eInit_SET_PLYER_GOL_(piVar3,pcVar1,piVar6);
      break;
    case 0x19:
      eInit_ATTENTION_(piVar3,piVar4,piVar5,pcVar1,piVar6,piVar7,piVar8);
      break;
    case 0x1a:
      eInit_SET_ANM_(piVar9);
      break;
    case 0x1b:
      eInit_WLK_(piVar3,pfVar10,pfVar11,pcVar1,piVar6,piVar7,piVar8);
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
    /* Nonmatching */
    m88A = 0;
    return m8F4 == 0;
}

/* 000056C0-00005734       .text eMove_WLK___11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::eMove_WLK_() {
    /* Nonmatching */
    s16 timer = cLib_calcTimer(&m86C);
    bool is_terminate = timer == 0;
    if (is_terminate) {
        setAnm_NUM(4,1);
        m848 = 0;
        speedF = m848;
    } 
    return is_terminate;   
}

/* 00005734-000057D0       .text event_action__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::event_action() {
    /* Nonmatching */

    switch(m8F6) {
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
    /* Nonmatching */
    setAnm_NUM(0x13,1);
    m900 = 0;
}

/* 0000580C-000058B8       .text cut_move_360_TRN__11daNpc_Bm1_cFv */
bool daNpc_Bm1_c::cut_move_360_TRN() {
    /* Nonmatching */
    bool uVar1;
    
    if (m87A) {
        uVar1 = 0;
        current.angle.y += 0x10000 + -0x8000;
        setAnm_NUM(4,1);
        mpMorf->setMorf(0.0);
        if (m885) {
            m71C->setMorf(0.0f);
        }
        else {
            m710->setMorf(0.0f);
        }
        m6EC->setMorf(0.0f);
        uVar1 = 1;
        return true;
    }
    return false;
}

/* 000058B8-000059E0       .text privateCut__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::privateCut(int arg0) {
    /* Nonmatching */
    static char* a_cut_tbl[] = {"ACTION","idk"};
    u32 uVar1;
    bool bVar2;
    char cVar3;
    
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
    /* Nonmatching */
    dComIfGp_event_onEventFlag(0x8);
    m8F7 = 0xFF;
}

/* 00005A00-00005A38       .text isEventEntry__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::isEventEntry() {
    /* Nonmatching */
    return dComIfGp_evmng_getMyStaffId(m79C.getActorName(),NULL);
}

/* 00005A38-00005B60       .text event_proc__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::event_proc(int) {
    /* Nonmatching */
}

/* 00005B60-00005C0C       .text set_action__11daNpc_Bm1_cFM11daNpc_Bm1_cFPCvPvPv_iPv */
void daNpc_Bm1_c::set_action(int (daNpc_Bm1_c::*)(void*), void*) {
    /* Nonmatching */
}

/* 00005C0C-00005E84       .text setStt__11daNpc_Bm1_cFSc */
void daNpc_Bm1_c::setStt(signed char) {
    /* Nonmatching */
}

/* 00005E84-00005EE0       .text d_wait__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::d_wait() {
    /* Nonmatching */
}

/* 00005EE0-00005F14       .text lookup__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::lookup() {
    /* Nonmatching */
}

/* 00005F14-00005F64       .text orooro__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::orooro() {
    /* Nonmatching */
}

/* 00005F64-00006028       .text wait_1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::wait_1() {
    /* Nonmatching */
}

/* 00006028-0000622C       .text talk_1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::talk_1() {
    /* Nonmatching */
}

/* 0000622C-000062C8       .text talk_2__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::talk_2() {
    /* Nonmatching */
}

/* 000062C8-00006344       .text manzai__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::manzai() {
    /* Nonmatching */
}

/* 00006344-00006424       .text wait_4__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::wait_4() {
    /* Nonmatching */
}

/* 00006424-0000647C       .text flyawy__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::flyawy() {
    /* Nonmatching */
}

/* 0000647C-000065B8       .text wait_5__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::wait_5() {
    /* Nonmatching */
}

/* 000065B8-00006688       .text h_wait__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::h_wait() {
    /* Nonmatching */
}

/* 00006688-0000677C       .text wait_7__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::wait_7() {
    /* Nonmatching */
}

/* 0000677C-000068A8       .text wait_3__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::wait_3() {
    /* Nonmatching */
}

/* 000068A8-0000692C       .text wait_8__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::wait_8() {
    /* Nonmatching */
}

/* 0000692C-0000699C       .text wait_2__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::wait_2() {
    /* Nonmatching */
}

/* 0000699C-00006A94       .text walk_1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::walk_1() {
    /* Nonmatching */
}

/* 00006A94-00006B74       .text CHKwai__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::CHKwai() {
    /* Nonmatching */
}

/* 00006B74-00006C4C       .text demo_action1__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::demo_action1(void*) {
    /* Nonmatching */
}

/* 00006C4C-00006D08       .text wait_action1__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 00006D08-00006E28       .text wait_action2__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action2(void*) {
    /* Nonmatching */
}

/* 00006E28-00006EC4       .text wait_action3__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action3(void*) {
    /* Nonmatching */
}

/* 00006EC4-00006F30       .text wait_action4__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action4(void*) {
    /* Nonmatching */
}

/* 00006F30-00006FEC       .text wait_action5__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action5(void*) {
    /* Nonmatching */
}

/* 00006FEC-000070B0       .text wait_action6__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action6(void*) {
    /* Nonmatching */
}

/* 000070B0-00007198       .text wait_action7__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action7(void*) {
    /* Nonmatching */
}

/* 00007198-00007270       .text wait_action8__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action8(void*) {
    /* Nonmatching */
}

/* 00007270-0000730C       .text wait_action9__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_action9(void*) {
    /* Nonmatching */
}

/* 0000730C-000073E4       .text wait_actionA__11daNpc_Bm1_cFPv */
BOOL daNpc_Bm1_c::wait_actionA(void*) {
    /* Nonmatching */
}

/* 000073E4-00007514       .text demo__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::demo() {
    /* Nonmatching */
}

/* 00007514-0000768C       .text shadowDraw__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::shadowDraw() {
    /* Nonmatching */
}

/* 0000768C-00007AB4       .text _draw__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::_draw() {
    /* Nonmatching */
}

/* 00007AB4-00007CAC       .text _execute__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::_execute() {
    /* Nonmatching */
}

/* 00007CAC-00007D50       .text _delete__11daNpc_Bm1_cFv */
BOOL daNpc_Bm1_c::_delete() {
    /* Nonmatching */
}

/* 00007D50-00007D70       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00007D70-00007ED4       .text _create__11daNpc_Bm1_cFv */
cPhs_State daNpc_Bm1_c::_create() {
    /* Nonmatching */
    // fopAcM_ct_Retail(this, daNpc_Bm1_c);
    static u32 a_size_tbl[0xB] = {};
    if(actor_condition == cPhs_COMPLEATE_e){
        return cPhs_COMPLEATE_e;
    }
    if(!decideType(fopAcM_GetParam(this),fopAcM_GetParamBit(fopAcM_GetParam(this),8,8))){
        return cPhs_ERROR_e;
    }
    cPhs_State state = dComIfG_resLoad(&mPhs,mArcName);
    m87F =  state == cPhs_COMPLEATE_e;
    if(!m87F){
        return state;
    }else{
        if(!fopAcM_entrySolidHeap(this,CheckCreateHeap,a_size_tbl[mType])){
            return cPhs_ERROR_e;
        }
        cullMtx = mpMorf->getModel()->getBaseTRMtx();
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
    /* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectRes(mArcName,"bm.bdl");
    JUT_ASSERT(DEMO_SELECT(0x1551,0x1551),a_mdl_dat != NULL);
    mpMorf = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,(J3DAnmTransform*)dComIfG_getObjectRes(mArcName,"bm_dwait.bck"),J3DFrameCtrl::EMode_LOOP,1.0f,0,-1,1,NULL,0x80000,0x15021222);
    if(mpMorf == NULL ){
        return NULL;
    }else if(mpMorf->getModel() == NULL){
        mpMorf = NULL;
        return NULL;
    }

    m_hed_jnt_num = a_mdl_dat->getTextureName()->getIndex("head");
    JUT_ASSERT(DEMO_SELECT(0x1565,0x1565),m_hed_jnt_num >= 0);
    m_nec_jnt_num = a_mdl_dat->getTextureName()->getIndex("neck");
    JUT_ASSERT(DEMO_SELECT(0x1565,0x1568),m_nec_jnt_num >= 0);
    m_bbone_jnt_num = a_mdl_dat->getTextureName()->getIndex("backbone");
    JUT_ASSERT(DEMO_SELECT(0x1565,0x156B),m_bbone_jnt_num >= 0);    
    m_arm_L_jnt_num = a_mdl_dat->getTextureName()->getIndex("armL");
    JUT_ASSERT(DEMO_SELECT(0x1565,0x156E),m_arm_L_jnt_num >= 0);    
    m_arm_R_jnt_num = a_mdl_dat->getTextureName()->getIndex("armR");
    JUT_ASSERT(DEMO_SELECT(0x1565,0x1571),m_arm_R_jnt_num >= 0); 
    return a_mdl_dat;  

}

/* 00008710-00008878       .text create_hed_Anm__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::create_hed_Anm() {
    /* Nonmatching */
}

/* 00008878-00008B44       .text create_wng_Anm__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::create_wng_Anm() {
    /* Nonmatching */
}

/* 00008B44-00008E6C       .text create_arm_Anm__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::create_arm_Anm() {
    /* Nonmatching */
}

/* 00008E6C-00009174       .text create_itm_Mdl__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::create_itm_Mdl() {
    /* Nonmatching */
}

/* 00009174-0000946C       .text CreateHeap__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::CreateHeap() {
    /* Nonmatching */
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
