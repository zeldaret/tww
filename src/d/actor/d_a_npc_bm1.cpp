/**
 * d_a_npc_bm1.cpp
 * NPC - Generic Ritos
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_bm1.h"
#include "d/d_bg_s_func.h"
#include "res/Object/Bm.h"

static daNpc_Bm1_HIO_c l_HIO;
static void* l_check_inf[0x14];
static s32 l_check_wrk = 0;
static char l_BCKName[0x1E];
static char l_BTPName[0x1E];
struct hio_prm{
    s32 m0;
    s32 m4;
    s32 m8;
    s32 mC;
    s32 m10;
    f32 m14;
    s32 m18;
    s32 m1C;
    f32 m20;
    f32 m24;
    f32 m28;
    f32 m2C;
    f32 m30;
    s32 m34;
    f32 m38;
    f32 m3C;
    f32 m40;
    f32 m44;
    f32 m48;
};

    char* l_evn_tbl[] = {
        "Get_Mo3_Ltr","Met_Ryu_Islnd","Get_Rupee","Skn_Islnd",
    };
/* 000000EC-00000108       .text __ct__20daNpc_Bm1_childHIO_cFv */
daNpc_Bm1_childHIO_c::daNpc_Bm1_childHIO_c() {
    /* Nonmatching */
}

/* 00000150-0000020C       .text __ct__15daNpc_Bm1_HIO_cFv */
daNpc_Bm1_HIO_c::daNpc_Bm1_HIO_c() {
    /* Nonmatching */
    static hio_prm a_prm_tbl[] = {
        0x20000FA0,
        0xF63CF060,
        0x00001B58,
        0xFC18E4A8,
        0x080004B0,
        220.0f,
        0xA,
        0x04000000,
        0,
        0,
        0,
        0,
        180.0f,
        0x00060400,
        0.5f,
        3.0f,
        0.1f,
        40.0f,
        870.0f,
        0x20002000,
        0xF8BBE000,
        0x00001036,
        0x0000EFCA,
        0x04790000,
        209.0f,
        0.0f,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0x20002000,
        0xF8BBE000,
        0x00001036,
        0x0000EFCA,
        0x04790000,
        209.0f,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0x20002000,
        0xF000E000,
        0x00001000,
        0x0000F000,
        0x05780000,
        220.0f,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    0x20002000,
        0xF000E000,
        0x00001000,
        0x0000F000,
        0x05780000,
        220.0f,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
    0x20002000,
        0xE5BAE000,
        0x00001000,
        0x0000F000,
        0x05080313,
        220.0f,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0x20002000,
        0xF000E000,
        0x00001000,
        0x0000F000,
        0x03E80596,
        220.0f,
        0xA,
        0x04000000,
        20.0f,
        1.0f,
        20.0f,
        0.6f,
        180.0f,
        0x00060400,
        0.3f,
        4.0f,
        0.3f,
        40.0f,
        0x00000000,
        0x20002000,
        0xF000E000,
        0x00002000,
        0x0000E000,
        0x06400578,
        220.0f,
        0,
        0,0,0,0,0,0,0x00060400,
        0.3f,
        4.0f,
        0.3f,
        40.0f,
        0,
        0x20002000,
        0xF000E000,
        0x00002000,
        0x0000E000,
        0x06400578,
        220.0f,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0x00060400,
        0.3f,
        4.0f,
        0.3f,
        40.0f,
        0,0x20002000,
        0xF000E000,
        0x00001000,
        0x0000F000,
        0x0064004B0,
        220.0f,
        0xA,
        0x04000000,
        20.0f,
        1.0f,
        20.0f,
        0.3f,
        180.0f,
        0x00060400,
        0.5f,
        4.0f,
        0.3f,
        40.0f,
    };
    for(int i = 0; i < 10; i++){
        children[i].m50 = i;
        memcpy(&children[i].anm_prm,&a_prm_tbl[i],0x4C);
    }
    m4 = -1;
    m8 = -1;
}





/* 00000268-000002E0       .text searchActor_Zl__FPvPv */
BOOL searchActor_Zl(void* i_param_1, void*) {
    /* Nonmatching */
    if(l_check_wrk < 0x14 && fopAc_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_ZL1_e){
        l_check_inf[l_check_wrk] = i_param_1;
        l_check_wrk += 1;
    }
    return 0;
}

/* 000002E0-00000358       .text searchActor_Gp__FPvPv */
BOOL searchActor_Gp(void* i_param_1, void*) {
    /* Nonmatching */
    if(l_check_wrk < 0x14 && fopAc_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_GP1_e){
        l_check_inf[l_check_wrk] = i_param_1;
        l_check_wrk += 1;
    }
    return 0;
}

/* 00000358-000003DC       .text searchActor_Bm_Skt__FPvPv */
BOOL searchActor_Bm_Skt(void* i_param_1, void*) {
    /* Nonmatching */
    if(l_check_wrk < 0x14 && fopAc_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_BM2_e){
        if(reinterpret_cast<daNpc_Bm1_c*>(i_param_1)->mSpecificType == Skett){
            l_check_inf[l_check_wrk] = i_param_1;
            l_check_wrk += 1;
        }
    }
    return 0;
}

/* 000003DC-00000460       .text searchActor_Bm_Kkt__FPvPv */
BOOL searchActor_Bm_Kkt(void* i_param_1, void*) {
    /* Nonmatching */
    if(l_check_wrk < 0x14 && fopAc_IsActor(i_param_1) && fopAcM_GetName(i_param_1) == fpcNm_NPC_BM2_e){
        if(reinterpret_cast<daNpc_Bm1_c*>(i_param_1)->mSpecificType == Akoot){
            l_check_inf[l_check_wrk] = i_param_1;
            l_check_wrk += 1;
        }
    }
    return 0;
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
        m888[0] = 1;
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

    if(m794.getPath()){
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
        m794.setInf(fopAcM_GetParamBit(param,16,8),fopAcM_GetRoomNo(this),true);

        if(m794.getPath()){
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
// char* stringbasefiller[] = {"Bm1","Bm2","Bm3","Bm4","Bm5"};
/* 000017A8-000017F8       .text anmNum_toResID__11daNpc_Bm1_cFi */
char* daNpc_Bm1_c::anmNum_toResID(int i_param_1) {
    /* Nonmatching */
    static char* a_BCKName_TBL[0x16] = {"bm_dwait","bm_fly01","bm_lookup","bm_orooro","bm_wait01","bm_wait02","bm_talk01","bm_nadame","bm_gliding","bm_endurance","bm_flyaway","bm_flyaway2","bm_talk02","bm_landing","bm_walk","bm02_wait01","bm02_talk01","bm02_talk02","bm_talk03","bm_turn","bm_walk02","bm_check"};
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
void daNpc_Bm1_c::chg_anmAtr(unsigned char) {
    /* Nonmatching */
}

/* 00001EFC-00001F68       .text control_anmAtr__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::control_anmAtr() {
    /* Nonmatching */
}

/* 00001F68-00001FD0       .text setAnm_ATR__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::setAnm_ATR(int) {
    /* Nonmatching */
}

/* 00001FD0-000020D8       .text anmAtr__11daNpc_Bm1_cFUs */
void daNpc_Bm1_c::anmAtr(unsigned short) {
    /* Nonmatching */
}

/* 000020D8-0000217C       .text eventOrder__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eventOrder() {
    /* Nonmatching */
}

/* 0000217C-00002234       .text checkOrder__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::checkOrder() {
    /* Nonmatching */
}

/* 00002234-00002304       .text chk_manzai__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::chk_manzai() {
    /* Nonmatching */
}

/* 00002304-000023A0       .text chk_talk__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::chk_talk() {
    /* Nonmatching */
}

/* 000023A0-000023E0       .text chk_partsNotMove__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::chk_partsNotMove() {
    /* Nonmatching */
}

/* 000023E0-00002590       .text lookBack__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::lookBack() {
    /* Nonmatching */
}

/* 00002590-00002A58       .text next_msgStatus__11daNpc_Bm1_cFPUl */
u16 daNpc_Bm1_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 00002A58-00002AC4       .text getBitMask__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getBitMask() {
    /* Nonmatching */
}

/* 00002AC4-00002B00       .text getMsg_PST_1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_PST_1() {
    /* Nonmatching */
}

/* 00002B00-00002B40       .text getMsg_PST_3__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_PST_3() {
    /* Nonmatching */
}

/* 00002B40-00002BE8       .text getMsg_SKT_0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_SKT_0() {
    /* Nonmatching */
}

/* 00002BE8-00002C90       .text getMsg_KKT_0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_KKT_0() {
    /* Nonmatching */
}

/* 00002C90-00002DBC       .text getMsg_BMB_0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_BMB_0() {
    /* Nonmatching */
}

/* 00002DBC-00002EE8       .text getMsg_BMB_1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_BMB_1() {
    /* Nonmatching */
}

/* 00002EE8-00003010       .text getMsg_BMB_2__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_BMB_2() {
    /* Nonmatching */
}

/* 00003010-00003058       .text getMsg_BMC_0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_BMC_0() {
    /* Nonmatching */
}

/* 00003058-000030D0       .text getMsg_BMC_2__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_BMC_2() {
    /* Nonmatching */
}

/* 000030D0-000031FC       .text getMsg_BMC_3__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_BMC_3() {
    /* Nonmatching */
}

/* 000031FC-00003328       .text getMsg_BMD_0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_BMD_0() {
    /* Nonmatching */
}

/* 00003328-00003470       .text getMsg_BMD_1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::getMsg_BMD_1() {
    /* Nonmatching */
}

/* 00003470-00003548       .text getMsg__11daNpc_Bm1_cFv */
u32 daNpc_Bm1_c::getMsg() {
    /* Nonmatching */
}

/* 00003548-000035C8       .text chkAttention__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::chkAttention() {
    /* Nonmatching */
}

/* 000035C8-00003630       .text setAttention__11daNpc_Bm1_cFb */
void daNpc_Bm1_c::setAttention(bool) {
    /* Nonmatching */
}

/* 00003630-00003664       .text searchByID__11daNpc_Bm1_cFUi */
void daNpc_Bm1_c::searchByID(fpc_ProcID) {
    /* Nonmatching */
}

/* 00003664-00003714       .text partner_srch_sub__11daNpc_Bm1_cFPFPvPv_Pv */
void daNpc_Bm1_c::partner_srch_sub(void* (*)(void*, void*)) {
    /* Nonmatching */
}

/* 00003714-00003818       .text partner_srch__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::partner_srch() {
    /* Nonmatching */
}

/* 00003818-00003A24       .text bm_movPass__11daNpc_Bm1_cFb */
void daNpc_Bm1_c::bm_movPass(bool) {
    /* Nonmatching */
}

/* 00003A24-00003A68       .text bm_setFlyAnm__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_setFlyAnm() {
    /* Nonmatching */
}

/* 00003A68-00003BF0       .text bm_clcFlySpd__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_clcFlySpd() {
    /* Nonmatching */
}

/* 00003BF0-00003C64       .text bm_clcMovSpd__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_clcMovSpd() {
    /* Nonmatching */
}

/* 00003C64-00003ED4       .text bm_flyMove__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_flyMove() {
    /* Nonmatching */
}

/* 00003ED4-00003FA4       .text bm_nMove__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::bm_nMove() {
    /* Nonmatching */
}

/* 00003FA4-000040EC       .text setPrtcl_Flyaway__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Flyaway() {
    /* Nonmatching */
}

/* 000040EC-00004160       .text delPrtcl_Flyaway__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Flyaway() {
    /* Nonmatching */
}

/* 00004160-000042A8       .text setPrtcl_Land0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Land0() {
    /* Nonmatching */
}

/* 000042A8-0000431C       .text delPrtcl_Land0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Land0() {
    /* Nonmatching */
}

/* 0000431C-000043E0       .text setPrtcl_Hane0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Hane0() {
    /* Nonmatching */
}

/* 000043E0-00004470       .text flwPrtcl_Hane0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::flwPrtcl_Hane0() {
    /* Nonmatching */
}

/* 00004470-000044C4       .text delPrtcl_Hane0__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Hane0() {
    /* Nonmatching */
}

/* 000044C4-000045B8       .text setPrtcl_Hane1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::setPrtcl_Hane1() {
    /* Nonmatching */
}

/* 000045B8-00004648       .text flwPrtcl_Hane1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::flwPrtcl_Hane1() {
    /* Nonmatching */
}

/* 00004648-000046BC       .text delPrtcl_Hane1__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::delPrtcl_Hane1() {
    /* Nonmatching */
}

/* 000046BC-000049B8       .text decideType__11daNpc_Bm1_cFii */
bool daNpc_Bm1_c::decideType(int, int) {
    /* Nonmatching */
}

/* 000049B8-000049FC       .text eInit_setLocFlag__11daNpc_Bm1_cFPi */
void daNpc_Bm1_c::eInit_setLocFlag(int*) {
    /* Nonmatching */
}

/* 000049FC-00004A34       .text eInit_setShapeAngleY__11daNpc_Bm1_cFPis */
void daNpc_Bm1_c::eInit_setShapeAngleY(int*, short) {
    /* Nonmatching */
}

/* 00004A34-00004A50       .text eInit_setEvTimer__11daNpc_Bm1_cFPi */
void daNpc_Bm1_c::eInit_setEvTimer(int*) {
    /* Nonmatching */
}

/* 00004A50-00004B30       .text eInit_calcRelativPos__11daNpc_Bm1_cFP4cXyzPi */
void daNpc_Bm1_c::eInit_calcRelativPos(cXyz*, int*) {
    /* Nonmatching */
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
}

/* 0000519C-000051EC       .text eInit_SET_NXT_PTH_INF___11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eInit_SET_NXT_PTH_INF_() {
    /* Nonmatching */
}

/* 000051EC-0000522C       .text eInit_SET_ANM___11daNpc_Bm1_cFPi */
void daNpc_Bm1_c::eInit_SET_ANM_(int*) {
    /* Nonmatching */
}

/* 0000522C-00005368       .text eInit_MOV_PTH_POINT___11daNpc_Bm1_cFPiPiPiPi */
void daNpc_Bm1_c::eInit_MOV_PTH_POINT_(int*, int*, int*, int*) {
    /* Nonmatching */
}

/* 00005368-00005650       .text event_actionInit__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::event_actionInit(int) {
    /* Nonmatching */
}

/* 00005650-0000569C       .text eMove_ATTENTION___11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eMove_ATTENTION_() {
    /* Nonmatching */
}

/* 0000569C-000056A4       .text eMove_KMA_FLY___11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eMove_KMA_FLY_() {
    /* Nonmatching */
}

/* 000056A4-000056C0       .text eMove_FLY___11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eMove_FLY_() {
    /* Nonmatching */
}

/* 000056C0-00005734       .text eMove_WLK___11daNpc_Bm1_cFv */
void daNpc_Bm1_c::eMove_WLK_() {
    /* Nonmatching */
}

/* 00005734-000057D0       .text event_action__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::event_action() {
    /* Nonmatching */
}

/* 000057D0-0000580C       .text cut_init_360_TRN__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::cut_init_360_TRN(int) {
    /* Nonmatching */
}

/* 0000580C-000058B8       .text cut_move_360_TRN__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::cut_move_360_TRN() {
    /* Nonmatching */
}

/* 000058B8-000059E0       .text privateCut__11daNpc_Bm1_cFi */
void daNpc_Bm1_c::privateCut(int) {
    /* Nonmatching */
}

/* 000059E0-00005A00       .text endEvent__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::endEvent() {
    /* Nonmatching */
}

/* 00005A00-00005A38       .text isEventEntry__11daNpc_Bm1_cFv */
void daNpc_Bm1_c::isEventEntry() {
    /* Nonmatching */
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
