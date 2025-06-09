/**
 * d_a_npc_ko1.cpp
 * NPC - Joel & Zill (Outset Island)
 */

#include "d/actor/d_a_npc_ko1.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "d/res/res_ko.h"
#include "weak_bss_936_to_1036.h"


daNpc_Ko1_HIO_c l_HIO;

#define L_CHECK_SZ 20
fopAc_ac_c* l_check_inf[L_CHECK_SZ];
s32 l_check_wrk;


/* 000000EC-00000108       .text __ct__20daNpc_Ko1_childHIO_cFv */
daNpc_Ko1_childHIO_c::daNpc_Ko1_childHIO_c() {
    /* Nonmatching */
}

/* 00000150-0000020C       .text __ct__15daNpc_Ko1_HIO_cFv */
daNpc_Ko1_HIO_c::daNpc_Ko1_HIO_c() {
    /* Nonmatching */
    static hio_prm_c a_prm_tbl = {
        {20,0,}
    };
    // genMessage(NULL);
    for(int i = 0; i < 2; i++){
        children[i].field5C = 0;
        memcpy(&children[i].pad04,&a_prm_tbl.childtable[i],0x58);
        //children[0] = a_prm_tbl
    }
    mNo = -1;
    field8 = -1;
}

/* 00000268-000002E0       .text searchActor_Ko_Hna__FPvPv */
fopAc_ac_c* searchActor_Ko_Hna(void* i_hna, void* i_ko1) {

    ko_hna_class* hna_act = (ko_hna_class*)(i_hna);
    //daNpc_Ko1_c* ko1_act = (daNpc_Ko1_c*)(i_ko1);
    if (
        l_check_wrk < L_CHECK_SZ  && fopAc_IsActor(hna_act) && 
        fopAcM_GetName(hna_act) == PROC_NPC_KO1

    ){
        l_check_inf[l_check_wrk] = hna_act;
        l_check_wrk++;
    }
    return NULL;
}

/* 000002E0-00000358       .text searchActor_Ko_Bou__FPvPv */
fopAc_ac_c* searchActor_Ko_Bou(void* i_bou, void*) {

    ko_bou_class* bou_act = (ko_bou_class*)(i_bou);
    //daNpc_Ko1_c* ko1_act = (daNpc_Ko1_c*)(i_ko1);
    if (
        l_check_wrk < L_CHECK_SZ  && fopAc_IsActor(bou_act) && 
        fopAcM_GetName(bou_act) == PROC_NPC_KO2

    ){
        l_check_inf[l_check_wrk] = bou_act;
        l_check_wrk++;
    }
    return NULL;

}

/* 00000358-000003D0       .text searchActor_Ob__FPvPv */
fopAc_ac_c* searchActor_Ob(void* i_ob, void*) {

    ko_bou_class* ob_act = (ko_bou_class*)(i_ob);
    //daNpc_Ko1_c* ko1_act = (daNpc_Ko1_c*)(i_ko1);
    if (
        l_check_wrk < L_CHECK_SZ  && fopAc_IsActor(ob_act) && 
        fopAcM_GetName(ob_act) == PROC_NPC_OB1

    ){
        l_check_inf[l_check_wrk] = ob_act;
        l_check_wrk++;
    }
    return NULL;
}

/* 000003D0-0000041C       .text nodeCallBack_Hed__FP7J3DNodei */
static BOOL nodeCallBack_Hed(J3DNode* i_node, int i_param2) {

    if(i_param2 == 0){
        J3DModel* model = j3dSys.getModel();
        if(model->getUserArea() != NULL){
            ((daNpc_Ko1_c*)model->getUserArea())->nodeHedControl(i_node,model);
        }
    }
    return TRUE;

}

/* 0000041C-00000488       .text nodeHedControl__11daNpc_Ko1_cFP7J3DNodeP8J3DModel */
void daNpc_Ko1_c::nodeHedControl(J3DNode* i_node, J3DModel* i_model) {

    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if(uVar1 == field_0x6CF){
        cMtx_copy(mDoMtx_stack_c::get(),field_0x6D4);
    }


}

/* 00000488-000004D4       .text nodeCallBack_Bln__FP7J3DNodei */
static BOOL nodeCallBack_Bln(J3DNode* i_node, int i_param2) {

    if(i_param2 == 0){
        J3DModel* model = j3dSys.getModel();
        if(model->getUserArea() != NULL){
            ((daNpc_Ko1_c*)model->getUserArea())->nodeBlnControl(i_node,model);
        }
    }
    return TRUE;
}

/* 000004D4-00000554       .text nodeBlnControl__11daNpc_Ko1_cFP7J3DNodeP8J3DModel */
void daNpc_Ko1_c::nodeBlnControl(J3DNode* i_node, J3DModel* i_model) {

    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if(uVar1 == field_0x6D0){
        cMtx_copy(field_0x6D4,j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1,field_0x6D4);
    }
}

/* 00000554-000005A0       .text nodeCallBack_Ko1__FP7J3DNodei */
static BOOL nodeCallBack_Ko1(J3DNode* i_node, int i_param2) {

    if(i_param2 == 0){
        J3DModel* model = j3dSys.getModel();
        if(model->getUserArea() != NULL){
            ((daNpc_Ko1_c*)model->getUserArea())->nodeBlnControl(i_node,model);
        }
    }
    return TRUE;
}

/* 000005A0-000006E8       .text nodeKo1Control__11daNpc_Ko1_cFP7J3DNodeP8J3DModel */
void daNpc_Ko1_c::nodeKo1Control(J3DNode* i_node, J3DModel* i_model) {

    static cXyz a_eye_pos_off(18.0f,20.0f,0.0f);
    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if(uVar1 == field_0x6CC){
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());     
        mDoMtx_stack_c::multVec(&a_eye_pos_off,&field_0x7DC);  
    }
    if(uVar1 == field_0x6CD){
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());  
        mDoMtx_stack_c::YrotM(m_jnt.getBackbone_x()); 
    } 
    cMtx_copy(mDoMtx_stack_c::get(),j3dSys.mCurrentMtx);
    i_model->setAnmMtx(uVar1,mDoMtx_stack_c::get());

}

/* 00000724-000007CC       .text init_HNA_0__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_HNA_0() {

    if(dComIfGs_isEventBit(0x2A80) && !dComIfGs_isEventBit(0xE20)){
        field_0x704 = 0;
        set_action(&daNpc_Ko1_c::hana_action1,NULL);
        return true;     
    }
    return false;

}

/* 000007CC-00000860       .text init_HNA_1__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_HNA_1() {

    if(dComIfGs_isEventBit(0xE20)){
        field_0x704 = 0;
        fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);
        set_action(&daNpc_Ko1_c::hana_action2,NULL);
        return TRUE;     
    }
    return FALSE;
}

/* 00000860-000008E8       .text init_HNA_2__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_HNA_2() {

    if(!dComIfGs_isEventBit(0x2A80)){
        field_0x704 = 0;
        set_action(&daNpc_Ko1_c::hana_action3,NULL);
        return TRUE;     
    }
    return FALSE;
}

/* 000008E8-00000994       .text init_HNA_3__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_HNA_3() {

    if(dComIfGs_isEventBit(0x520)){
        if(dKy_daynight_check() == 0){
            fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);
            fopAcM_OnStatus(this,fopAcStts_UNK4000_e);
            field_0x704 = 0;
            set_action(&daNpc_Ko1_c::hana_action4,NULL);
            return TRUE;     
        }
    }
    return FALSE;
}

/* 00000994-00000A20       .text init_HNA_4__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_HNA_4() {

    if(dComIfGs_isEventBit(0x520)){
        if(dKy_daynight_check() == 1){
            set_action(&daNpc_Ko1_c::hana_action5,NULL);
            return TRUE;     
        }
    }
    return FALSE;

}

/* 00000A20-00000AAC       .text init_BOU_0__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_BOU_0() {

    if(!dComIfGs_isEventBit(0xE20)){
        set_action(&daNpc_Ko1_c::wait_action1,NULL);
        fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);
        return TRUE;     
    }

    return FALSE;
}

/* 00000AAC-00000B38       .text init_BOU_1__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_BOU_1() {

    if(dComIfGs_isEventBit(0xE20)){
        set_action(&daNpc_Ko1_c::wait_action2,NULL);
        fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);

        return TRUE;     
    }
    return FALSE;
}

/* 00000B38-00000BE4       .text init_BOU_2__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_BOU_2() {

    if(dComIfGs_isEventBit(0x520)){
        if(dKy_daynight_check() == 0){
            fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);
            fopAcM_OnStatus(this,fopAcStts_UNK4000_e);

            set_action(&daNpc_Ko1_c::wait_action3,NULL);
            field_0x708 = 0;
            return TRUE;     
        }
    }
    return FALSE;
}

/* 00000BE4-00000C78       .text init_BOU_3__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_BOU_3() {

    if(dComIfGs_isEventBit(0x520)){
        if(dKy_daynight_check() == 1){

            set_action(&daNpc_Ko1_c::wait_action4,NULL);
            field_0x708 = 0;
            return TRUE;     
        }
    }
    return FALSE;
}
char* a_staff_tbl[] = {"Ko1","Ko1","Ko1","Ko1","Ko1",
    "Ko2","Ko2","Ko2","Ko2",};
extern dCcD_SrcCyl dNpc_cyl_src;
/* 00000C78-00000F14       .text createInit__11daNpc_Ko1_cFv */
s8 daNpc_Ko1_c::createInit() {
    /* Nonmatching */

    bool cVar2;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    switch(field_0x8A6){
        case 0:
            attention_info.distances[1] = 0xA9;
            attention_info.distances[3] = 0xA9; 
            break;
        case 1:
            attention_info.distances[1] = 0xA7;
            attention_info.distances[3] = 0xA9;     
            break;

    }
    gravity = -4.5f;
    field_0x7D0 = current.angle;
    field_0x7C4 = current.pos;
    field_0x80C = field_0x7C4;
    field_0x7E8 = field_0x80C;
    int iVar3 = 0xFF;
    if(fopAcM_GetParamBit(fopAcM_GetParam(this),0x10,0x8) != 0xFF){ //TODO: fopAcM_GetParamBit not in debug maps
        mPathRun.setInf(fopAcM_GetParam(this) >> 0x10,fopAcM_GetRoomNo(this),true);
        if(!mPathRun.isPath()){
            return 0;
        }
        fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);
        iVar3 = 0xF0;
    }
    mEventCut.setActorInfo2(a_staff_tbl[field_0x8A7],this);
    field_0x89F = 0xE;
    switch(field_0x8A7){
        case 0:
            cVar2 = init_HNA_0();
            break;
        case 1:
            cVar2 = init_HNA_1();
            iVar3 = 0xF0;
            break;        
        case 2:
            cVar2 = init_HNA_2();
            iVar3 = 0xF0;
            break;
        case 3:
            cVar2 = init_HNA_3();

            break;
        case 4:
            cVar2 = init_HNA_4();
            break;
        case 5:
            cVar2 = init_BOU_0();
            break;
        case 6:
            cVar2 = init_BOU_1();
            iVar3 = 0xF0;
            break;
        case 7:
            cVar2 = init_BOU_2();
            break;
        case 8:
            cVar2 = init_BOU_3();
            break;
        default:
            cVar2 = 0;
    }
    
    switch(cVar2){
        default:
            field_0x7D6 = current.angle;
            shape_angle = field_0x7D6;
            break;
        case 0:
            return 0;
            break;
    }
    mStts.Init(iVar3,0xFF,this);
    mCyl.SetStts(&mStts);
    mCyl.Set(dNpc_cyl_src);
    mpMorf->setMorf(0.0f);
    field_0x710->setMorf(0.0f);
    setMtx(true);
    return 1;



}

/* 00000F14-000011C4       .text setMtx__11daNpc_Ko1_cFb */
void daNpc_Ko1_c::setMtx(bool param_1) {
    /* Nonmatching */
    if(field_0x877 == 0){
        int uVar6 = 0;
        plyTexPttrnAnm();
        if(mObjAcch.ChkGroundHit()){
            uVar6 = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
        }
        field_0x860 = mpMorf->play(&eyePos,uVar6,dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    
        if(mpMorf->getFrame() < field_0x824){
            field_0x860 = 1;
        }
        field_0x824 = mpMorf->getFrame();
        if(field_0x89F == 4 && mpMorf->mFrameCtrl.checkPass(10.0f) != 0){
            fopAcM_seStart(this,JA_SE_CM_GAKI_HANASUSURI,0);
        }
        field_0x710->play(&eyePos,0,0);
        if(field_0x704 != NULL && field_0x865 < 2){
            field_0x704->setFrame(mpMorf->getFrame());
        }
        field_0x86C = mObjAcch.ChkGroundHit();

        mObjAcch.CrrPos(*dComIfG_Bgsp());
    }
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(field_0x7D6.y);
    mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    mpMorf->calc();
    field_0x710->getModel()->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(field_0x6CC));
    field_0x710->calc();
    if(field_0x704 != NULL){
        field_0x704->calc();
    }
    if(field_0x708 != NULL){
        field_0x708->setBaseTRMtx(mpMorf->mpModel->getAnmMtx(field_0x6CE));
        field_0x708->calc();
    }

    setAttention(param_1);
    return;

}

/* 000011C4-000011D8       .text anmNum_toResID__11daNpc_Ko1_cFi */
s32 daNpc_Ko1_c::anmNum_toResID(int i_anmNum) {

    static const KO_RES_FILE_ID a_bck_resID_tbl[0xE] = {
        KO_BCK_KO_WAIT01,          // 0x16
        KO_BCK_KO_RUN01,           // 0xF
        KO_BCK_KO_WALK01,          // 0x18
        KO_BCK_KO_TALK01,          // 0x15
        KO_BCK_KO_SUSURI,          // 0x14
        KO_BCK_KO_BUTUKARI,        // 0xD
        KO_BCK_KO_WAIT02,          // 0x17
        KO_BCK_KO_SLEEP01,         // 0x10
        KO_BCK_KO_SLEEP02,         // 0x11
        KO_BCK_KO_SLEEP03,         // 0x12
        KO_BCK_KO_SLEEP04,        // 0x13
        KO_BCK_KO_OISI,           // 0xE
        KO_BCK_KO_BANG,           // 0xC
        KO_BCK_KO_OHOHO           // 0x26
    };
    return a_bck_resID_tbl[i_anmNum];
}

/* 000011D8-00001200       .text headAnmNum_toResID__11daNpc_Ko1_cFi */
s32 daNpc_Ko1_c::headAnmNum_toResID(int i_headAnmNum) {

    static const KO_RES_FILE_ID a_bck_resID_tbl[0xE] = {
        KO_BCK_KOHEAD01_WAIT01,      // 0xA
        KO_BCK_KOHEAD01_RUN01,       // 0x5
        KO_BCK_KOHEAD01_WALK01,      // 0xB
        KO_BCK_KOHEAD01_TALK01,      // 0x9
        KO_BCK_KOHEAD01_SUSURI,      // 0x8
        KO_BCK_KOHEAD01_BUTUKARI,    // 0x3
        KO_BCK_KOHEAD01_WAIT01,      // 0xA
        KO_BCK_KOHEAD01_WAIT01,      // 0xA
        KO_BCK_KOHEAD01_WAIT01,      // 0xA
        KO_BCK_KOHEAD01_SLEEP03,     // 0x6
        KO_BCK_KOHEAD01_SLEEP04,    // 0x7
        KO_BCK_KOHEAD01_OISI,       // 0x4
        KO_BCK_KOHEAD01_BANG,       // 0x2
        KO_BCK_KOHEAD01_WAIT01      // 0xA
    };
    if(field_0x8A6 == 1){
        return KO_BCK_KOHEAD02_WAIT01;
    }

    return a_bck_resID_tbl[i_headAnmNum];
}

/* 00001200-00001214       .text balloon_anmNum_toResID__11daNpc_Ko1_cFi */
s32 daNpc_Ko1_c::balloon_anmNum_toResID(int i_balloon_anmNum) {

    static const KO_RES_FILE_ID a_bck_resID_tbl[0xE] = {
        KO_BCK_BALLOON_SLEEP04,      // 0x1
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
        KO_BCK_BALLOON_BANG,         // 0x0
    };
    return a_bck_resID_tbl[i_balloon_anmNum];

}

/* 00001214-0000129C       .text btpNum_toResID__11daNpc_Ko1_cFi */
s32 daNpc_Ko1_c::btpNum_toResID(int i_btpNum) {

    static const KO_RES_FILE_ID a_btp_resID_tbl[0x4] = {
        KO_BTP_KOHEAD01,              // 0x1F
        KO_BTP_KOHEAD01_SUSURI,       // 0x22
        KO_BTP_KOHEAD01_SLEEP,        // 0x20
        KO_BTP_KOHEAD01_SLEEP04,      // 0x21
    };
    u32 res_id = a_btp_resID_tbl[i_btpNum]; 
    switch(res_id){
        case KO_BTP_KOHEAD01:   //0x1F
            switch(field_0x8A6){
                case 0:
                    return KO_BTP_KOHEAD01;
                case 1:
                    return KO_BTP_KOHEAD02;
            }   
            break;
        case KO_BTP_KOHEAD01_SLEEP: //0x20
            switch(field_0x8A6){
                case 0:
                    return KO_BTP_KOHEAD01_SLEEP;
                case 1:
                    return KO_BTP_KOHEAD02_SLEEP;
            }
            break;
        default:
            return res_id;
    }

}

/* 0000129C-000013AC       .text setBtp__11daNpc_Ko1_cFbi */
bool daNpc_Ko1_c::setBtp(bool i_param_1, int i_btpNum) {

    J3DModelData* model_data = field_0x710->getModel()->getModelData();
    int res_id = btpNum_toResID(i_btpNum);
    m_hed_tex_pttrn = (J3DAnmTexPattern*)dComIfG_getObjectIDRes("Ko",res_id);
    JUT_ASSERT(VERSION_SELECT(0x3AA,0x3AA,0x3AA,0x3AA),m_hed_tex_pttrn != 0);
    if(field_0x718.init(model_data,m_hed_tex_pttrn,1,2,1.0f,0,-1,i_param_1,0)){
        field_0x72C = 0;
        field_0x72E = NULL;
        return true;
    }
    return false;

}

/* 000013AC-000013D4       .text iniTexPttrnAnm__11daNpc_Ko1_cFb */
void daNpc_Ko1_c::iniTexPttrnAnm(bool i_param_1) {

    setBtp(i_param_1,field_0x89E);
}

/* 000013D4-00001480       .text plyTexPttrnAnm__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::plyTexPttrnAnm() {

    if ((field_0x89E != 0 || (cLib_calcTimer(&field_0x72E) == 0))){
        field_0x72C += 1;    
        //temp_r4 = 
        if(field_0x72C >= m_hed_tex_pttrn->getFrameMax()){
            if(field_0x89E != 0){
                field_0x72C = m_hed_tex_pttrn->getFrameMax();
            }else{
                f32 fVar2 = cM_rndF(60.0f);
                field_0x72E = fVar2 + 30.0f;
                field_0x72C = 0;
            }

        }
    }
    return;
}

/* 00001480-000014BC       .text setAnm_tex__11daNpc_Ko1_cFSc */
void daNpc_Ko1_c::setAnm_tex(signed char i_param_1) {
    /* Nonmatching */
    if(field_0x89E != i_param_1){
        field_0x89E = i_param_1;
        iniTexPttrnAnm(true);
    }
    return;
}

/* 000014BC-000015B4       .text setAnm_anm__11daNpc_Ko1_cFPQ211daNpc_Ko1_c9anm_prm_c */
s32 daNpc_Ko1_c::setAnm_anm(daNpc_Ko1_c::anm_prm_c* i_anm_prm) {

    if(field_0x89F == i_anm_prm->field0){
        return 1;
    }
    field_0x89F = i_anm_prm->field0;
    int anm_res_id = anmNum_toResID(field_0x89F);
    dNpc_setAnmIDRes(mpMorf,i_anm_prm->fieldC,i_anm_prm->field4,i_anm_prm->field8,anm_res_id,-1,"Ko");
    int anm_res_id_2 = headAnmNum_toResID(field_0x89F);
    dNpc_setAnmIDRes(field_0x710,i_anm_prm->fieldC,i_anm_prm->field4,i_anm_prm->field8,anm_res_id_2,-1,"Ko");
    field_0x824 = field_0x861 = field_0x860 = 0;
    
    return 1;
}

/* 000015B4-00001674       .text set_balloonAnm_anm__11daNpc_Ko1_cFPQ211daNpc_Ko1_c9anm_prm_c */
s32 daNpc_Ko1_c::set_balloonAnm_anm(daNpc_Ko1_c::anm_prm_c* i_anm_prm) {

    int anim_res_id;
    if(field_0x8A1 == i_anm_prm->field0){
        return 1;
    }
    field_0x8A1 = i_anm_prm->field0;
    anim_res_id = balloon_anmNum_toResID(field_0x8A1);
    dNpc_setAnmIDRes(field_0x704,i_anm_prm->fieldC,i_anm_prm->field4,i_anm_prm->field8,anim_res_id,-1,"Ko");
    field_0x828 = field_0x85F = field_0x85E = 0;
    return 1;
}

/* 00001674-000016A4       .text set_balloonAnm_NUM__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::set_balloonAnm_NUM(int param_1) {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[2] = {
        { 0x00, 0xFF,  0.0f, 0.0f, 2, 0 },
        { 0x01, 0xFF,  0.0f, 0.0f, 0, 0 },

    };
    set_balloonAnm_anm(&a_anm_prm_tbl[param_1]);
}

/* 000016A4-00001710       .text setAnm_NUM__11daNpc_Ko1_cFii */
void daNpc_Ko1_c::setAnm_NUM(int i_param_1, int i_param_2) {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[14] = {
        { 0x00, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x01, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x02, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x03, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x04, 0x01,  8.0f, 1.0f, 2, 0 },
        { 0x05, 0x00,  8.0f, 1.0f, 0, 0 },
        { 0x06, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x07, 0x02,  8.0f, 1.0f, 2, 0 },
        { 0x08, 0x02,  8.0f, 1.0f, 2, 0 },
        { 0x09, 0x02,  8.0f, 1.0f, 2, 0 },
        { 0x0A, 0x03,  8.0f, 1.0f, 2, 0 },
        { 0x0B, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x0C, 0x02,  8.0f, 1.0f, 0, 0 },
        { 0x0D, 0x00,  8.0f, 1.0f, 2, 0 },
    };
    if(i_param_2 != 0){
        setAnm_tex(a_anm_prm_tbl[i_param_1].field1);
    }
    setAnm_anm(&a_anm_prm_tbl[i_param_1]);
}

/* 00001710-00001790       .text setAnm__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::setAnm() {
    static anm_prm_c a_anm_prm_tbl[0x1E] = {
    { 0xFF, 0xFF,  0.0f, 0.0f, -1, 0 },
    { 0x0, 0x0,  8.0f, 1.0f, 2, 0 },
    
    { 0x06, 0x00,  8.0f, 1.0f, 2, 0 },
    { -1, -1,  0.0f, 0.0f, -1, 0 },
    { 0x02, 0x0,  8.0f, 1.0f, 2, 0 },
    { 0x04, 0x01,  8.0f, 1.0f, 2, 0 },
    { 0x01, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x02, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x02, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x05, 0x00,  8.0f, 1.0f, 0, 0 },
    { 0x00, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x02, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x00, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x01, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x00, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x02, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x05, 0x00,  8.0f, 1.0f, 0, 0 },
    { 0x01, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x05, 0x00,  8.0f, 1.0f, 0, 0 },
    { 0x00, 0x00,  8.0f, 1.0f, 2, 0 },
    { -1, -1,  0.0f, 0.0f, -1, 0 },
    { -1, -1,  0.0f, 0.0f, -1, 0 },
    { 0x00, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x01, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x02, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x05, 0x00,  8.0f, 1.0f, 0, 0 },
    { 0x00, 0x00,  8.0f, 1.0f, 2, 0 },
    { 0x07, 0x02,  8.0f, 1.0f, 2, 0 },
    { 0x09, 0x02,  8.0f, 1.0f, 2, 0 },
    { 0x00, 0x00,  8.0f, 1.0f, 2, 0 },
    };
    if(a_anm_prm_tbl[field_0x8A3].field1 >= 0){
        setAnm_tex(a_anm_prm_tbl[field_0x8A3].field1);
    }
    if(a_anm_prm_tbl[field_0x8A3].field0 >= 0){
        setAnm_anm(&a_anm_prm_tbl[field_0x8A3]);

    }
    return true;

}

/* 00001790-000017A4       .text setPlaySpd__11daNpc_Ko1_cFf */
void daNpc_Ko1_c::setPlaySpd(float i_param_1) {

    field_0x710->setPlaySpeed(i_param_1);
    mpMorf->setPlaySpeed(i_param_1);
}

/* 000017A4-000017DC       .text chg_anmTag__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::chg_anmTag() {

    switch(field_0x89D){
        default:
            break;
        case 0xA:
            setAnm_NUM(4,1);
            break;
    }

}

/* 000017DC-00001824       .text control_anmTag__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::control_anmTag() {

    switch(field_0x89D){
        default:
            break;
        case 0xA:
            if(field_0x860){
                field_0x89D = 0xFF;
                setAnm_ATR(0x1);
            }
            break;
    }
}

/* 00001824-000018D8       .text chg_anmAtr__11daNpc_Ko1_cFUc */
void daNpc_Ko1_c::chg_anmAtr(unsigned char i_param_1) {
    /* Nonmatching */

    if(field_0x848 != -1){
        switch(field_0x848){

            case 0xB0A:
            case 0xB03:
            case 0xB65:
            case 0xB64:
                field_0x8A5 = 1;
                field_0x876 = 0;
                m_jnt.mbTrn = 1;
                break;


        }
    }
    if(i_param_1 >= 0xD || i_param_1 == field_0x89C){
        return;
    }
    field_0x89C = i_param_1;
    if(field_0x89C == 0xB){
        field_0x8A5 = 1;
        field_0x876 = 0;
        m_jnt.mbTrn = true;
    }
    setAnm_ATR(1);



}

/* 000018D8-0000192C       .text control_anmAtr__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::control_anmAtr() {

    switch(field_0x89C){
        case 0xB:
            if(field_0x860 != 0){
                field_0x89C = 0;
                setAnm_NUM(0,1);
            }
            break;
        case 0xC:
        case 0xA:
        default:
            break;
    }
}

/* 0000192C-00001994       .text setAnm_ATR__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::setAnm_ATR(int i_param_1) {
    /* Nonmatching */
    static anm_prm_c a_anm_prm_tbl[13] = {
        { 0x00, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x01, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x02, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x03, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x04, 0x01,  8.0f, 1.0f, 2, 0 },
        { 0x05, 0x00,  8.0f, 1.0f, 0, 0 },
        { 0x06, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x07, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x08, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x09, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x0A, 0x03,  8.0f, 1.0f, 2, 0 },
        { 0x0B, 0x00,  8.0f, 1.0f, 2, 0 },
        { 0x0D, 0x00,  8.0f, 1.0f, 2, 0 },
    };

    if(i_param_1 != 0){
        setAnm_tex(a_anm_prm_tbl[field_0x89C].field1);
    }
    setAnm_anm(&a_anm_prm_tbl[field_0x89C]);
}

/* 00001994-00001A9C       .text anmAtr__11daNpc_Ko1_cFUs */
void daNpc_Ko1_c::anmAtr(unsigned short) {
    /* Nonmatching */
}

/* 00001A9C-00001AEC       .text eventOrder__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::eventOrder() {
    /* Nonmatching */
}

/* 00001AEC-00001B2C       .text checkOrder__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::checkOrder() {
    /* Nonmatching */
}

/* 00001B2C-00001BCC       .text chk_talk__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::chk_talk() {
    /* Nonmatching */
}

/* 00001BCC-00001E0C       .text chk_manzai_1__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::chk_manzai_1() {
    /* Nonmatching */
}

/* 00001E0C-00001E4C       .text chk_partsNotMove__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::chk_partsNotMove() {
    /* Nonmatching */
}

/* 00001E4C-00001FFC       .text lookBack__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::lookBack() {
    /* Nonmatching */
}

/* 00001FFC-00002204       .text next_msgStatus__11daNpc_Ko1_cFPUl */
u16 daNpc_Ko1_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
    return fopMsgStts_MSG_ENDS_e;
}

/* 00002204-00002240       .text getMsg_HNA_0__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::getMsg_HNA_0() {
    /* Nonmatching */
}

/* 00002240-0000227C       .text getMsg_HNA_1__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::getMsg_HNA_1() {
    /* Nonmatching */
}

/* 0000227C-000022B8       .text getMsg_HNA_2__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::getMsg_HNA_2() {
    /* Nonmatching */
}

/* 000022B8-00002318       .text getMsg_HNA_3__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::getMsg_HNA_3() {
    /* Nonmatching */
}

/* 00002318-0000237C       .text getMsg_BOU_0__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::getMsg_BOU_0() {
    /* Nonmatching */
}

/* 0000237C-000023B8       .text getMsg_BOU_1__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::getMsg_BOU_1() {
    /* Nonmatching */
}

/* 000023B8-000023E8       .text bitCount__11daNpc_Ko1_cFUc */
void daNpc_Ko1_c::bitCount(unsigned char) {
    /* Nonmatching */
}

/* 000023E8-0000248C       .text getMsg_BOU_2__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::getMsg_BOU_2() {
    /* Nonmatching */
}

/* 0000248C-00002528       .text getMsg__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::getMsg() {
    /* Nonmatching */
}

/* 00002528-000025A8       .text chkAttention__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::chkAttention() {
    /* Nonmatching */
}

/* 000025A8-00002610       .text setAttention__11daNpc_Ko1_cFb */
void daNpc_Ko1_c::setAttention(bool) {
    /* Nonmatching */
}

/* 00002610-00002644       .text searchByID__11daNpc_Ko1_cFUi */
void daNpc_Ko1_c::searchByID(fpc_ProcID) {
    /* Nonmatching */
}

/* 00002644-000026DC       .text partner_srch_sub__11daNpc_Ko1_cFPFPvPv_Pv */
void daNpc_Ko1_c::partner_srch_sub(void* (*)(void*, void*)) {
    /* Nonmatching */
}

/* 000026DC-000027CC       .text partner_srch__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::partner_srch() {
    /* Nonmatching */
}

/* 000027CC-00002900       .text check_landOn__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::check_landOn() {
    /* Nonmatching */
}

/* 00002900-0000299C       .text ko_setPthPos__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_setPthPos() {
    /* Nonmatching */
}

/* 0000299C-00002AA4       .text set_tgtPos__11daNpc_Ko1_cF4cXyz */
void daNpc_Ko1_c::set_tgtPos(cXyz) {
    /* Nonmatching */
}

/* 00002AA4-00002C14       .text ko_movPass__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_movPass() {
    /* Nonmatching */
}

/* 00002C14-00002D50       .text ko_clcMovSpd__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_clcMovSpd() {
    /* Nonmatching */
}

/* 00002D50-00002E3C       .text ko_clcSwmSpd__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_clcSwmSpd() {
    /* Nonmatching */
}

/* 00002E3C-00003028       .text ko_nMove__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_nMove() {
    /* Nonmatching */
}

/* 00003028-000030E8       .text chk_routeAngle__11daNpc_Ko1_cFR4cXyzPs */
void daNpc_Ko1_c::chk_routeAngle(cXyz&, short*) {
    /* Nonmatching */
}

/* 000030E8-0000334C       .text routeWallCheck__11daNpc_Ko1_cFR4cXyzR4cXyzPs */
void daNpc_Ko1_c::routeWallCheck(cXyz&, cXyz&, short*) {
    /* Nonmatching */
}

/* 00003784-00003A04       .text chk_ForwardGroundY__11daNpc_Ko1_cFs */
void daNpc_Ko1_c::chk_ForwardGroundY(short) {
    /* Nonmatching */
}

/* 00003B9C-00003C54       .text chk_wallJump__11daNpc_Ko1_cFs */
void daNpc_Ko1_c::chk_wallJump(short) {
    /* Nonmatching */
}

/* 00003C54-00003D34       .text routeCheck__11daNpc_Ko1_cFfPs */
void daNpc_Ko1_c::routeCheck(float, short*) {
    /* Nonmatching */
}

/* 00003D34-00003DE8       .text chk_start_swim__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::chk_start_swim() {
    /* Nonmatching */
}

/* 00003DE8-00003E64       .text get_crsActorID__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::get_crsActorID() {
    /* Nonmatching */
}

/* 00003E64-00003F50       .text chk_areaIn__11daNpc_Ko1_cFf4cXyz */
void daNpc_Ko1_c::chk_areaIn(float, cXyz) {
    /* Nonmatching */
}

/* 00003F50-00003FF0       .text setPrtcl_Hamon__11daNpc_Ko1_cFff */
void daNpc_Ko1_c::setPrtcl_Hamon(float, float) {
    /* Nonmatching */
}

/* 00003FF0-000040F8       .text setPrtcl_HanaPachi__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::setPrtcl_HanaPachi() {
    /* Nonmatching */
}

/* 000040F8-0000420C       .text charDecide__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::charDecide(int) {
    /* Nonmatching */
}

/* 0000420C-00004264       .text event_actionInit__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::event_actionInit(int) {
    /* Nonmatching */
}

/* 00004264-00004274       .text event_action__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::event_action() {
    /* Nonmatching */
}

/* 00004274-00004360       .text privateCut__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::privateCut(int) {
    /* Nonmatching */
}

/* 00004360-00004384       .text endEvent__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::endEvent() {
    /* Nonmatching */
}

/* 00004384-000043BC       .text isEventEntry__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::isEventEntry() {
    /* Nonmatching */
}

/* 000043BC-00004414       .text event_proc__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::event_proc(int) {
    /* Nonmatching */
}

/* 00004414-000044C0       .text set_action__11daNpc_Ko1_cFM11daNpc_Ko1_cFPCvPvPv_iPv */
void daNpc_Ko1_c::set_action(int (daNpc_Ko1_c::*)(void*), void*) {
    /* Nonmatching */
}

/* 000044C0-000044E8       .text clrSpd__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::clrSpd() {
    /* Nonmatching */
}

/* 000044E8-00004B18       .text setStt__11daNpc_Ko1_cFSc */
void daNpc_Ko1_c::setStt(signed char) {
    /* Nonmatching */
}

/* 00004B18-00004C70       .text wait_1__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::wait_1() {
    /* Nonmatching */
}

/* 00004C70-00004CE8       .text wait_2__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::wait_2() {
    /* Nonmatching */
}

/* 00004CE8-00004D1C       .text wait_3__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::wait_3() {
    /* Nonmatching */
}

/* 00004D1C-00004E64       .text wait_4__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::wait_4() {
    /* Nonmatching */
}

/* 00004E64-00004F30       .text wait_5__11daNpc_Ko1_cFSc */
void daNpc_Ko1_c::wait_5(signed char) {
    /* Nonmatching */
}

/* 00004F30-00005088       .text wait_6__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::wait_6() {
    /* Nonmatching */
}

/* 00005088-000052D4       .text wait_7__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::wait_7() {
    /* Nonmatching */
}

/* 000052D4-000053F8       .text wait_9__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::wait_9() {
    /* Nonmatching */
}

/* 000053F8-00005524       .text wait_a__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::wait_a() {
    /* Nonmatching */
}

/* 00005524-000055F8       .text walk_1__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::walk_1() {
    /* Nonmatching */
}

/* 000055F8-000056D4       .text walk_2__11daNpc_Ko1_cFScSc */
void daNpc_Ko1_c::walk_2(signed char, signed char) {
    /* Nonmatching */
}

/* 000056D4-000057B8       .text walk_3__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::walk_3() {
    /* Nonmatching */
}

/* 000057B8-000058EC       .text swim_1__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::swim_1() {
    /* Nonmatching */
}

/* 000058EC-00005A1C       .text swim_2__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::swim_2() {
    /* Nonmatching */
}

/* 00005A1C-00005B64       .text attk_1__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::attk_1() {
    /* Nonmatching */
}

/* 00005B64-00005C94       .text attk_2__11daNpc_Ko1_cFScSc */
void daNpc_Ko1_c::attk_2(signed char, signed char) {
    /* Nonmatching */
}

/* 00005C94-00005DEC       .text attk_3__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::attk_3() {
    /* Nonmatching */
}

/* 00005DEC-00005E1C       .text down_1__11daNpc_Ko1_cFSc */
void daNpc_Ko1_c::down_1(signed char) {
    /* Nonmatching */
}

/* 00005E1C-0000609C       .text talk_1__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::talk_1() {
    /* Nonmatching */
}

/* 0000609C-00006184       .text talk_2__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::talk_2() {
    /* Nonmatching */
}

/* 00006184-000062B4       .text manzai__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::manzai() {
    /* Nonmatching */
}

/* 000062B4-00006358       .text neru_1__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::neru_1() {
    /* Nonmatching */
}

/* 00006358-00006524       .text neru_2__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::neru_2() {
    /* Nonmatching */
}

/* 00006524-00006668       .text hana_action1__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::hana_action1(void*) {
    /* Nonmatching */
}

/* 00006668-00006774       .text hana_action2__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::hana_action2(void*) {
    /* Nonmatching */
}

/* 00006774-00006894       .text hana_action3__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::hana_action3(void*) {
    /* Nonmatching */
}

/* 00006894-00006988       .text hana_action4__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::hana_action4(void*) {
    /* Nonmatching */
}

/* 00006988-00006A24       .text hana_action5__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::hana_action5(void*) {
    /* Nonmatching */
}

/* 00006A24-00006B24       .text wait_action1__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::wait_action1(void*) {
    /* Nonmatching */
}

/* 00006B24-00006C64       .text wait_action2__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::wait_action2(void*) {
    /* Nonmatching */
}

/* 00006C64-00006D58       .text wait_action3__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::wait_action3(void*) {
    /* Nonmatching */
}

/* 00006D58-00006DF4       .text wait_action4__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::wait_action4(void*) {
    /* Nonmatching */
}

/* 00006DF4-00006F34       .text demo__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::demo() {
    /* Nonmatching */
}

/* 00006F34-00007008       .text shadowDraw__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::shadowDraw() {
    /* Nonmatching */
}

/* 00007008-0000728C       .text _draw__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::_draw() {
    /* Nonmatching */
}

/* 0000728C-0000756C       .text _execute__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::_execute() {
    /* Nonmatching */
}

/* 0000756C-000075F0       .text _delete__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::_delete() {
    /* Nonmatching */
}

/* 000075F0-00007610       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00007610-00007730       .text _create__11daNpc_Ko1_cFv */
cPhs_State daNpc_Ko1_c::_create() {
    /* Nonmatching */
}

/* 00007C2C-00007E9C       .text create_Anm__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::create_Anm() {
    /* Nonmatching */
}

/* 00007E9C-00008090       .text create_hed_Anm__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::create_hed_Anm() {
    /* Nonmatching */
}

/* 00008090-000082A4       .text create_bln_Anm__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::create_bln_Anm() {
    /* Nonmatching */
}

/* 000082A4-00008380       .text create_itm_Mdl__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::create_itm_Mdl() {
    /* Nonmatching */
}

/* 00008380-00008604       .text CreateHeap__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::CreateHeap() {
    /* Nonmatching */
}

/* 00008604-00008624       .text daNpc_Ko1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ko1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Ko1_c*)i_this)->_create();
}

/* 00008624-00008644       .text daNpc_Ko1_Delete__FP11daNpc_Ko1_c */
static BOOL daNpc_Ko1_Delete(daNpc_Ko1_c* i_this) {
    return ((daNpc_Ko1_c*)i_this)->_delete();
}

/* 00008644-00008664       .text daNpc_Ko1_Execute__FP11daNpc_Ko1_c */
static BOOL daNpc_Ko1_Execute(daNpc_Ko1_c* i_this) {
    return ((daNpc_Ko1_c*)i_this)->_execute();
}

/* 00008664-00008684       .text daNpc_Ko1_Draw__FP11daNpc_Ko1_c */
static BOOL daNpc_Ko1_Draw(daNpc_Ko1_c* i_this) {
    return ((daNpc_Ko1_c*)i_this)->_draw();
}

/* 00008684-0000868C       .text daNpc_Ko1_IsDelete__FP11daNpc_Ko1_c */
static BOOL daNpc_Ko1_IsDelete(daNpc_Ko1_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Ko1_Method = {
    (process_method_func)daNpc_Ko1_Create,
    (process_method_func)daNpc_Ko1_Delete,
    (process_method_func)daNpc_Ko1_Execute,
    (process_method_func)daNpc_Ko1_IsDelete,
    (process_method_func)daNpc_Ko1_Draw,
};

actor_process_profile_definition g_profile_NPC_KO1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_KO1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ko1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_KO1,
    /* Actor SubMtd */ &l_daNpc_Ko1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};

actor_process_profile_definition g_profile_NPC_KO2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_KO2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ko1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_KO2,
    /* Actor SubMtd */ &l_daNpc_Ko1_Method,
    /* Status       */ 0x07 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_NPC_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
