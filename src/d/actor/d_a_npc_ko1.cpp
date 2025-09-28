/**
 * d_a_npc_ko1.cpp
 * NPC - Joel & Zill (Outset Island)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_ko1.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_snap.h"
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
    static hio_prm_child_c a_prm_tbl[2] = {
    {
	0x2000,0x1F40,0xE0C0,0xE0C0,
	0x0000,0x1F40,0x0000,0xE0C0,
	0x07D0,0x0640,90.0f,0,
    0x4,0x0800,0x0000,
    0.9f,1.0f,
	0.5f,21.0f,
	0.1f,10.0f,
	0.3f,40.0f,
	80.0f,200.0f,
	300.0f,150.0f,
	1100.0f,1500.0f},{
	0x2000,0x1F40,
	0xE0C0,0xE0C0,
	0x0000,0x1F40,
	0x0000,0xE0C0,
	0x07D0,0x0640,
	90.0f,
	0,0x6,
	0x0800,0x0000,
    0.3,6.0,
    0.4,21.0,
    0.1,12.0,
    1.5,100.0,
    0.0,350.0,
    500.0,150.0,
    0.0,0.0
        }
    };

    for(int i = 0; i < 2; i++){
        children[i].field5C = i;
        memcpy(&children[i].hio_prm,&a_prm_tbl[i],0x58);

    }
    mNo = -1;
    field8 = -1;
}

/* 00000268-000002E0       .text searchActor_Ko_Hna__FPvPv */
void* searchActor_Ko_Hna(void* i_hna, void* i_ko1) {

    ko_hna_class* hna_act = (ko_hna_class*)(i_hna);

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
void* searchActor_Ko_Bou(void* i_bou, void*) {

    ko_bou_class* bou_act = (ko_bou_class*)(i_bou);

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
void* searchActor_Ob(void* i_ob, void*) {

    ko_bou_class* ob_act = (ko_bou_class*)(i_ob);

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
    if(uVar1 == m_hed_2_jnt_num){
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
    if(uVar1 == m_bln_loc_jnt_num){
        cMtx_copy(field_0x6D4,j3dSys.mCurrentMtx);
        i_model->setAnmMtx(uVar1,field_0x6D4);
    }
}

/* 00000554-000005A0       .text nodeCallBack_Ko1__FP7J3DNodei */
static BOOL nodeCallBack_Ko1(J3DNode* i_node, int i_param2) {

    if(i_param2 == 0){
        J3DModel* model = j3dSys.getModel();
        if(model->getUserArea() != NULL){
            ((daNpc_Ko1_c*)model->getUserArea())->nodeKo1Control(i_node,model);
        }
    }
    return TRUE;
}

/* 000005A0-000006E8       .text nodeKo1Control__11daNpc_Ko1_cFP7J3DNodeP8J3DModel */
void daNpc_Ko1_c::nodeKo1Control(J3DNode* i_node, J3DModel* i_model) {

    static cXyz a_eye_pos_off(18.0f,20.0f,0.0f);
    s32 uVar1 = ((J3DJoint*)i_node)->getJntNo();
    mDoMtx_stack_c::copy(i_model->getAnmMtx(uVar1));
    if(uVar1 == m_hed_jnt_num){
        mDoMtx_stack_c::XrotM(m_jnt.getHead_y());
        mDoMtx_stack_c::ZrotM(-m_jnt.getHead_x());     
        mDoMtx_stack_c::multVec(&a_eye_pos_off,&field_0x7DC);  
    }
    if(uVar1 == m_bbone_jnt_num){
        mDoMtx_stack_c::XrotM(m_jnt.getBackbone_y());  
        mDoMtx_stack_c::YrotM(m_jnt.getBackbone_x()); 
    } 
    cMtx_copy(mDoMtx_stack_c::get(),j3dSys.mCurrentMtx);
    i_model->setAnmMtx(uVar1,mDoMtx_stack_c::get());

}

/* 00000724-000007CC       .text init_HNA_0__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_HNA_0() {

    if(dComIfGs_isEventBit(0x2A80) && !dComIfGs_isEventBit(0xE20)){
        mBlnAnm = 0;
        set_action(&daNpc_Ko1_c::hana_action1,NULL);
        return true;     
    }
    return false;

}

/* 000007CC-00000860       .text init_HNA_1__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_HNA_1() {

    if(dComIfGs_isEventBit(0xE20)){
        mBlnAnm = 0;
        fopAcM_OffStatus(this,fopAcStts_NOCULLEXEC_e);
        set_action(&daNpc_Ko1_c::hana_action2,NULL);
        return TRUE;     
    }
    return FALSE;
}

/* 00000860-000008E8       .text init_HNA_2__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::init_HNA_2() {

    if(!dComIfGs_isEventBit(0x2A80)){
        mBlnAnm = 0;
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
            mBlnAnm = 0;
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
bool daNpc_Ko1_c::createInit() {

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
        if(mBlnAnm != NULL && field_0x865 < 2){
            mBlnAnm->setFrame(mpMorf->getFrame());
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
    field_0x710->getModel()->setBaseTRMtx(mpMorf->getModel()->getAnmMtx(m_hed_jnt_num));
    field_0x710->calc();
    if(mBlnAnm != NULL){
        mBlnAnm->calc();
    }
    if(field_0x708 != NULL){
        field_0x708->setBaseTRMtx(mpMorf->mpModel->getAnmMtx(m_armR2_jnt_num));
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
    if(mBtpAnm.init(model_data,m_hed_tex_pttrn,1,2,1.0f,0,-1,i_param_1,0)){
        mBtpFrame = 0;
        field_0x72E = NULL;
        return true;
    }
    return false;

}

/* 000013AC-000013D4       .text iniTexPttrnAnm__11daNpc_Ko1_cFb */
bool daNpc_Ko1_c::iniTexPttrnAnm(bool i_param_1) {

    setBtp(i_param_1,field_0x89E);
}

/* 000013D4-00001480       .text plyTexPttrnAnm__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::plyTexPttrnAnm() {

    if ((field_0x89E != 0 || (cLib_calcTimer(&field_0x72E) == 0))){
        mBtpFrame += 1;    
        if(mBtpFrame >= m_hed_tex_pttrn->getFrameMax()){
            if(field_0x89E != 0){
                mBtpFrame = m_hed_tex_pttrn->getFrameMax();
            }else{
                field_0x72E = cM_rndF(60.0f) + 30.0f;
                mBtpFrame = 0;
            }

        }
    }
    return;
}

/* 00001480-000014BC       .text setAnm_tex__11daNpc_Ko1_cFSc */
void daNpc_Ko1_c::setAnm_tex(signed char i_param_1) {

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
    dNpc_setAnmIDRes(mBlnAnm,i_anm_prm->fieldC,i_anm_prm->field4,i_anm_prm->field8,anim_res_id,-1,"Ko");
    field_0x828 = field_0x85F = field_0x85E = 0;
    return 1;
}

/* 00001674-000016A4       .text set_balloonAnm_NUM__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::set_balloonAnm_NUM(int param_1) {

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
void daNpc_Ko1_c::anmAtr(unsigned short i_param_1) {
    /* Nonmatching */
    u8 uVar1 = dComIfGp_getPlayerInfoBufferStageNo();
    dComIfG_MesgCamInfo_c* cam_info = dComIfGp_getMesgCameraInfo();
    if(field_0x6bc[0] == 2 && (fopAc_ac_c*)this != cam_info->mActor[cam_info->mBasicID-1]){
        control_anmTag();
        control_anmAtr();
    }else{
        switch(i_param_1){
            case 6:
            if(field_0x8A9 == 0){
                field_0x89C = 0xFF;
                chg_anmAtr(dComIfGp_getMesgAnimeAttrInfo());
                field_0x8A9 += 1;
            }
            uVar1 = dComIfGp_getMesgAnimeTagInfo();
            dComIfGp_clearMesgAnimeTagInfo();
            if(uVar1 != 0xFF && field_0x89D != uVar1){
                field_0x89D = uVar1;
                chg_anmTag();
            }
            break; 
            case 0xE:
                field_0x8A9 = 0;
                break;

        }
        control_anmTag();
        control_anmAtr();
    }
    return;
}

/* 00001A9C-00001AEC       .text eventOrder__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::eventOrder() {

    if(field_0x8A2 == 1 || field_0x8A2 == 2){
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if(field_0x8A2 == 1){
            fopAcM_orderSpeakEvent(this);
        }
    }
}

/* 00001AEC-00001B2C       .text checkOrder__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::checkOrder() {

    if(eventInfo.mCommand == dEvtCmd_INDEMO_e){
        return;
    }
    if(eventInfo.mCommand != dEvtCmd_INTALK_e){
        return;
    }
    if(field_0x8A2 != 1 && field_0x8A2 != 2){
        return;
    }
    field_0x8A2 = 0;
    field_0x875 = 1;
}

/* 00001B2C-00001BCC       .text chk_talk__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::chk_talk() {
    bool o_retval = FALSE;
    if(dComIfGp_event_chkTalkXY()){
        if(dComIfGp_evmng_ChkPresentEnd()){
            field_0x863 = dComIfGp_event_getPreItemNo();
            o_retval = TRUE;
        }
    }else{
        field_0x863 = 0xFF;
        o_retval = TRUE;
    }
    return o_retval;
}

/* 00001BCC-00001E0C       .text chk_manzai_1__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::chk_manzai_1() {

    u32 uVar7 = 0;
    fpc_ProcID fVar2;
    fopAc_ac_c* a_actor;
    for(int i = 0; i < field_0x7BC; i++){
        a_actor = (fopAc_ac_c*)searchByID(field_0x7B4[i]);
        JUT_ASSERT(1410,0 != a_actor);
        if(*((u8*)a_actor+0x6BC) == 2){
            uVar7 += 1;
        }else{
            fopAcM_OnStatus(a_actor,fopAcStts_UNK4000_e);
            if(this != NULL){
                fVar2 = base.mBsPcId;

            }else{
                fVar2 = 0xFFFFFFFF;
            }
            *((u32*)a_actor+0x1AD) = fVar2;
            *((u8*)a_actor+0x6BC) = 1;
        }
    }
    bool o_retval =  uVar7 == field_0x7BC;
    if(o_retval){
        fopAc_ac_c* uVar5 = searchByID(field_0x7B4[0]);
        s8 cVar1 = field_0x8A7;
        switch(cVar1){
            case 1:
                dComIfGp_setMesgCameraInfoActor(uVar5,this,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
                break;
            case 3:
                dComIfGp_setMesgCameraInfoActor(uVar5,searchByID(field_0x7B4[1]),this,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
                break;



            case 6:
                dComIfGp_setMesgCameraInfoActor(this,uVar5,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
                break;

            case 7:
                dComIfGp_setMesgCameraInfoActor(this,searchByID(field_0x7B4[1]),uVar5,NULL,NULL,NULL,NULL,NULL,NULL,NULL);
                break;
        }
        field_0x6bc[0] = 2;
    }
    return o_retval;
}

/* 00001E0C-00001E4C       .text chk_partsNotMove__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::chk_partsNotMove() {

    bool o_retval = false;
    if(field_0x840 == m_jnt.getHead_y() &&
        field_0x842 == m_jnt.getBackbone_y() &&
        field_0x844 == current.angle.y){
            o_retval = true;
    }
    return o_retval;
}

/* 00001E4C-00001FFC       .text lookBack__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::lookBack() {

    field_0x840 = m_jnt.getHead_y();
    field_0x842 = m_jnt.getBackbone_y();
    field_0x844 = current.angle.y;
    cXyz local_24;
    cXyz local_30 = current.pos;
    local_30.y = eyePos.y;
    local_24.set(0.0f,0.0f,0.0f);
    cXyz* dstPos = NULL;
    s16 desiredYRot = current.angle.y;
    bool headOnlyFollow = field_0x876;

    switch(field_0x8A5){
        case 1:
            local_24 = dNpc_playerEyePos(-20.0f);
            dstPos = &local_24;
            local_30.x = current.pos.x;
            local_30.y = current.pos.y;
            local_30.z = current.pos.z;
            local_30.y = eyePos.y;
            // local_30.set(current.pos.x,eyePos.y,current.pos.z);
            break;

        case 2:
            local_24 = field_0x7E8;
            dstPos = &local_24;
            local_30 = current.pos;
            local_30.y = eyePos.y;
            break;
        case 3:
            desiredYRot = field_0x858;
    }
    cLib_addCalcAngleS2(&field_0x856,l_HIO.children[field_0x8A6].hio_prm.field16,4,0x800);
    if(!m_jnt.mbTrn){
        field_0x856 = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y,dstPos,local_30,desiredYRot,field_0x856,headOnlyFollow);
}

/* 00001FFC-00002204       .text next_msgStatus__11daNpc_Ko1_cFPUl */
u16 daNpc_Ko1_c::next_msgStatus(unsigned long* i_param_1) {

    u16 var_r31 = 0xF;
    u32 temp_r3 = *i_param_1;
    switch (temp_r3) {
    case 0xAF4:
        *i_param_1 = 0xB57;
        break;
    case 0xAF5:
        *i_param_1 = 0xB58;
        break;
    case 0xB59:
        *i_param_1 = 0xB5A;
        break;
    case 0xB5A:
        *i_param_1 = 0xB5B;
        break;
    case 0xB5B:
        *i_param_1 = 0xB5C;
        break;
    case 0xB5C:
        *i_param_1 = 0xB5D;
        break;
    case 0xB5D:
        *i_param_1 = 0xB64;
        break;
    case 0xB5E:
        *i_param_1 = 0xB5F;
        break;
    case 0xB5F:
        *i_param_1 = 0xB60;
        break;
    case 0xB60:
        *i_param_1 = 0xB61;
        break;
    case 0xB61:
        *i_param_1 = 0xB65;
        break;
    case 0xAF6:
        *i_param_1 = 0xAF7;
        break;
    case 0xAF7:
        *i_param_1 = 0xAF8;
        break;
    case 0xAF8:
        *i_param_1 = 0xAF9;
        break;
    case 0xAF9:
        *i_param_1 = 0xAFA;
        break;
    case 0xAFA:
        *i_param_1 = 0xAFB;
        break;
    case 0xAFB:
        if(bitCount(dComIfGs_getEventReg(0xBFFF))){
            *i_param_1 = 0xAFC;
        } else {
            *i_param_1 = 0xAFD;
        }
        break;
    case 0xAFC:
    case 0xAFD:
        *i_param_1 = 0xAFE;
        break;
    case 0xAFE:
        *i_param_1 = 0xAFF;
        break;
    case 0xB00:
    case 0xB07:
        *i_param_1 = 0xB01;
        break;
    case 0xB01:
        *i_param_1 = 0xB02;
        break;
    case 0xB02:
        *i_param_1 = 0xB03;
        break;
    case 0xB03:
        *i_param_1 = 0xB04;
        break;
    case 0xB04:
        *i_param_1 = 0xB05;
        break;
    case 0xB05:
        *i_param_1 = 0xB06;
        break;
    case 0xB08:
        *i_param_1 = 0xB09;
        break;
    case 0xB09:
        *i_param_1 = 0xB0A;
        break;
    case 0xB0A:
        *i_param_1 = 0xB0B;
        break;
    case 0xB0B:
        *i_param_1 = 0xB0C;
        break;
    case 0xB0C:
        *i_param_1 = 0xB0D;
        break;
    default:
        var_r31 = 0x10;
        break;
    }
    return var_r31;
}


/* 00002204-00002240       .text getMsg_HNA_0__11daNpc_Ko1_cFv */
s32 daNpc_Ko1_c::getMsg_HNA_0() {

    return (dComIfGs_isEventBit(0x220))?0xB56:0xB55;
}

/* 00002240-0000227C       .text getMsg_HNA_1__11daNpc_Ko1_cFv */
s32 daNpc_Ko1_c::getMsg_HNA_1() {

    return (dComIfGs_isEventBit(0x240))?0xAF5:0xAF4;
}

/* 0000227C-000022B8       .text getMsg_HNA_2__11daNpc_Ko1_cFv */
s32 daNpc_Ko1_c::getMsg_HNA_2() {

    return (dComIfGs_isEventBit(0x3101))?0xB63:0xB62;
}

/* 000022B8-00002318       .text getMsg_HNA_3__11daNpc_Ko1_cFv */
s32 daNpc_Ko1_c::getMsg_HNA_3() {

    if(dComIfGs_isEventBit(0x2C04)){
        if(field_0x86D != 0){
            return 0xB5E;
        }else{
            return 0xB5A;
        }
    }
    return 0xB59;
}

/* 00002318-0000237C       .text getMsg_BOU_0__11daNpc_Ko1_cFv */
s32 daNpc_Ko1_c::getMsg_BOU_0() {

    if(dComIfGs_isEventBit(0x104)){
        return 0xAF3;
    }
    return (dComIfGs_isEventBit(0x210))?0xAF2:0xAF1;

}

/* 0000237C-000023B8       .text getMsg_BOU_1__11daNpc_Ko1_cFv */
s32 daNpc_Ko1_c::getMsg_BOU_1() {

    return (dComIfGs_isEventBit(0x208))?0xAF5:0xAF4;
}

/* 000023B8-000023E8       .text bitCount__11daNpc_Ko1_cFUc */
s8 daNpc_Ko1_c::bitCount(unsigned char i_param_1) {

    u8 param = i_param_1;
    s8 count = 0;
    for (int i = 0; i < 8; ++i) {
        if (param & 1)
            count++;
        param = param >> 1;
    }
    return count;

}

/* 000023E8-0000248C       .text getMsg_BOU_2__11daNpc_Ko1_cFv */
s32 daNpc_Ko1_c::getMsg_BOU_2() {
    /* Nonmatching */
//   int iVar1;
//   undefined4 uVar2;
//   ushort uVar3;
//   char cVar4;
    if(dComIfGs_isEventBit(0x3801)){
        if(dComIfGs_isEventBit(0x3340)){
            return 0xB08;
        }else{
            if(bitCount(dComIfGs_getEventReg(0xBFFF)) >= 2){
                return 0xB07;
            }
            return 0xB00;
        }   
    }else{
        return 0xAF6;
    }

}

/* 0000248C-00002528       .text getMsg__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::getMsg() {


    u32 uVar1 = 0;
    switch(field_0x8A7) {
    case 0:
        uVar1 = getMsg_HNA_0();
        break;
    case 1:
        uVar1 = getMsg_HNA_1();
        break;
    case 2:
        uVar1 = getMsg_HNA_2();
        break;
    case 3:
        uVar1 = getMsg_HNA_3();
        break;
    case 5:
        uVar1 = getMsg_BOU_0();
        break;
    case 6:
        uVar1 = getMsg_BOU_1();
        break;
    case 7:
        uVar1 = getMsg_BOU_2();
        break;
    case 8:
        break;
    }
  return uVar1;
}

/* 00002528-000025A8       .text chkAttention__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::chkAttention() {
    dAttention_c& attn = dComIfGp_getAttention();
    if((attn.LockonTruth())){
        return this == attn.LockonTarget(0);
    }else{
        return this == attn.ActionTarget(0);
    }

}

/* 000025A8-00002610       .text setAttention__11daNpc_Ko1_cFb */
void daNpc_Ko1_c::setAttention(bool i_param_1) {

    attention_info.position.set(current.pos.x,current.pos.y + l_HIO.children[field_0x8A6].hio_prm.field18,current.pos.z);
    if(field_0x870 == 0 && !i_param_1){
        return;
    }
    eyePos.set(field_0x7DC.x,field_0x7DC.y,field_0x7DC.z);
}

/* 00002610-00002644       .text searchByID__11daNpc_Ko1_cFUi */
fopAc_ac_c* daNpc_Ko1_c::searchByID(fpc_ProcID i_procID) {
    /* Nonmatching */
    fopAc_ac_c* actor = NULL;
    fopAcM_SearchByID(i_procID, &actor);
    return actor;
}

/* 00002644-000026DC       .text partner_srch_sub__11daNpc_Ko1_cFPFPvPv_Pv */
fpc_ProcID daNpc_Ko1_c::partner_srch_sub(void* (*i_param_1)(void*, void*)) {

    fpc_ProcID partnerProcID = -1;
    l_check_wrk = 0;

    for(int i = 0; i != 0x14; i++){
        l_check_inf[i] = 0x0000;
    }
    fpcEx_Search(*i_param_1, this);
    if(l_check_wrk != 0){
        partnerProcID = fopAcM_GetID(l_check_inf[0]);

    }
    return partnerProcID;
}

/* 000026DC-000027CC       .text partner_srch__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::partner_srch() {

    if(field_0x8A8 == 1){
        switch(field_0x8A7) {
            case 1:
                field_0x7B4[0] = partner_srch_sub(searchActor_Ko_Bou);
                field_0x7BC = 1;
                return;
            case 3:
                field_0x7B4[0] = partner_srch_sub(searchActor_Ko_Bou);
                field_0x7B4[1] = partner_srch_sub(searchActor_Ob);
                field_0x7BC = 2;
                return;
            case 6:
                field_0x7B4[0] = partner_srch_sub(searchActor_Ko_Hna);
                field_0x7BC = 1;
                return;
            case 7:
                field_0x7B4[0] = partner_srch_sub(searchActor_Ko_Hna);
                field_0x7B4[1] = partner_srch_sub(searchActor_Ob);
                field_0x7BC = 2;
                break;
            case 8:
                //field_0x8A8 = 1;
                break;
        }
    }else{

    }

}

/* 000027CC-00002900       .text check_landOn__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::check_landOn() {
    /* Nonmatching */
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    cXyz local_1c(-198160.0f,150.0f,319690.0f);
    f32 fVar3 = (player->current.pos-local_1c).absXZ();
    if(player->current.pos.y == local_1c.y && fVar3 < 280.0f && player->getAutoJumpLand()){
        dComIfGs_onEventBit(0x104);
        return true;
    }
    return false;
}

/* 00002900-0000299C       .text ko_setPthPos__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_setPthPos() {
    /* Nonmatching */
    if(mPathRun.isPath()){
        current.pos = mPathRun.getPoint(mPathRun.getIdx());
        mPathRun.nextIdxAuto();
        cXyz nextpoint = mPathRun.getPoint(mPathRun.getIdx());
        current.angle.y = cLib_targetAngleY(&current.pos,&nextpoint); 
    }
}

/* 0000299C-00002AA4       .text set_tgtPos__11daNpc_Ko1_cF4cXyz */
cXyz daNpc_Ko1_c::set_tgtPos(cXyz i_param_1) {
    /* Nonmatching */
    cXyz local_1c(0.0f,0.0f,0.0f);
    cXyz local_28;
    mDoMtx_stack_c::transS(i_param_1);
    mDoMtx_stack_c::YrotM(dComIfGp_getLinkPlayer()->current.angle.y);
    local_1c.x = cM_ssin(field_0x85A) * 80.0f;
    local_1c.z = cM_scos(field_0x85A) * 40.0f;
    field_0x85A += 0x400;
    mDoMtx_stack_c::multVec(&local_1c,&local_28);
    return local_28;
}

/* 00002AA4-00002C14       .text ko_movPass__11daNpc_Ko1_cFv */
u32 daNpc_Ko1_c::ko_movPass() {
    /* Nonmatching */
    u32 uVar3 = 0;
    if(mPathRun.isPath() && dPath_ChkClose(mPathRun.getPath())){
        if(mPathRun.chkPointPass(current.pos,mPathRun.getDir())){
            mPathRun.nextIdxAuto();
            uVar3 = 1;
        }
        return uVar3;

    }
    f32 fVar5 = (field_0x7F4 - current.pos).absXZ();
    if(fVar5 <= field_0x83C){
            uVar3 = 1;
        if(mPathRun.isPath() && mPathRun.nextIdxAuto() == 0){
            uVar3 = 2;
        }
    }
    return uVar3;
}

/* 00002C14-00002D50       .text ko_clcMovSpd__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_clcMovSpd() {
    /* Nonmatching */
    f32 fVar5 = (field_0x7F4-current.pos).abs2XZ();
    s16 local_38 = cLib_targetAngleY(&current.pos,&field_0x7F4);
    if(routeCheck(fVar5,&local_38) != 0){
        char cVar1 = field_0x8A3;
        if(cVar1 == 4 || cVar1 == 0xB ||cVar1 == 0x18){
            if(!cLib_calcTimer(&field_0x850)){
                field_0x864 ^= 1;
                field_0x850 = cLib_getRndValue(8,0x14);
            }
            s16 sVar3;
            if(field_0x864 != 0){
                sVar3 = -0x2000;
            }else{
                sVar3 = 0x2000;
            }
            local_38 += sVar3;
        }
        cLib_chaseAngleS(&current.angle.y,local_38,l_HIO.children[field_0x8A6].hio_prm.field20);
        cLib_chaseF(&speedF,field_0x82C,field_0x834);
    }

}

/* 00002D50-00002E3C       .text ko_clcSwmSpd__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_clcSwmSpd() {

    f32 fVar5 = (field_0x7F4-current.pos).abs2XZ();
    s16 local_38 = cLib_targetAngleY(&current.pos,&field_0x7F4);
    if(routeCheck(fVar5,&local_38) != 0){
        cLib_chaseAngleS(&current.angle.y,local_38,l_HIO.children[field_0x8A6].hio_prm.field20);
        cLib_chaseF(&speed.y,field_0x830,1.6f);
        cLib_chaseF(&speedF,0.0f,0.4f);
    }
}

/* 00002E3C-00003028       .text ko_nMove__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::ko_nMove() {

    f32 fVar2, fVar3;
    switch(field_0x898){
        case 1:
        case 2:
            ko_clcMovSpd();          

            if(field_0x898 == 1){
                fVar3 = speedF*l_HIO.children[field_0x8A6].hio_prm.field24;
                fVar3 = cLib_maxLimit(fVar3, l_HIO.children[field_0x8A6].hio_prm.field28*l_HIO.children[field_0x8A6].hio_prm.field24);

            }else{
                fVar3 = speedF*l_HIO.children[field_0x8A6].hio_prm.field34;
                fVar3 = cLib_maxLimit(fVar3,l_HIO.children[field_0x8A6].hio_prm.field38*l_HIO.children[field_0x8A6].hio_prm.field34);
            }
            if(fVar3 < 0.5f){
                fVar3 = 0.5f;
            }
            setPlaySpd(fVar3);
            switch(ko_movPass()){
                case 1:
                    field_0x86B = 1;
                    break;
                case 2:
                    field_0x86B = 1;
                    field_0x898 = 0;
                    break;
            }
            break;
        case 3:
            ko_clcSwmSpd();
            switch(ko_movPass()){
                case 1:
                    field_0x86B = 1;
                    break;
                case 2:
                    field_0x86B = 1;
                    field_0x898 = 0;
                    break;
            }
            break;
        case 4:
            cLib_chaseF(&speedF,0.1f,field_0x834);
            if(field_0x86C == 0 && mObjAcch.ChkGroundHit()){
                speed.y = 0.0f;
                speedF = 0.0f;
                gravity = -4.5f;
                field_0x898 = field_0x899;
                field_0x86B = 1;
            }
            break;
            
    }
    if(field_0x86B){
        field_0x869 = 1;
    }
    return;

}

/* 00003028-000030E8       .text chk_routeAngle__11daNpc_Ko1_cFR4cXyzPs */
void daNpc_Ko1_c::chk_routeAngle(cXyz& i_param_1, short* i_param_2) {

    cXyz local_28 = field_0x818.outprod(i_param_1);
    s16 iVar1 = cM_atan2s(local_28.x,local_28.z);
    if (((field_0x818.y >= 0.999f) && (cLib_distanceAngleS(iVar1, *i_param_2) > 0x4000)) || ((local_28.y * (field_0x7F4.y - current.pos.y)) < 0.0f)) {
        iVar1 += 0x8000;
    }
    *i_param_2 = iVar1;
}

/* 000030E8-0000334C       .text routeWallCheck__11daNpc_Ko1_cFR4cXyzR4cXyzPs */
void daNpc_Ko1_c::routeWallCheck(cXyz& i_param_1, cXyz& i_param_2, short* i_param_3) {

    dBgS_LinChk chnk;
    chnk.Set(&i_param_1,&i_param_2,NULL);
    if(dComIfG_Bgsp()->LineCross(&chnk)){
        cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(chnk);
        if(pla){
            chk_routeAngle(*(cXyz*)pla,i_param_3);
        }
    }
}

/* 00003784-00003A04       .text chk_ForwardGroundY__11daNpc_Ko1_cFs */
f32 daNpc_Ko1_c::chk_ForwardGroundY(short i_param_1) {

    cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(mAcchCir.GetBgIndex(),mAcchCir.GetPolyIndex());
    if(pla != NULL){
        if(cLib_distanceAngleS(i_param_1,cM_atan2s(pla->mNormal.x,pla->mNormal.z)) > 0x4000){
            dBgS_GndChk gndchk;
            gndchk.OffWall();
            cXyz position(current.pos.x+cM_ssin(i_param_1) * 80.0f,current.pos.y + 80.0f,current.pos.z+cM_scos(i_param_1) * 80.0f);
            gndchk.SetPos(&position);
            return dComIfG_Bgsp()->GroundCross(&gndchk);
        }
    }
    return -1e07;
}

/* 00003B9C-00003C54       .text chk_wallJump__11daNpc_Ko1_cFs */
f32 daNpc_Ko1_c::chk_wallJump(short i_param_1) {

    f32 check = chk_ForwardGroundY(i_param_1);
    if(0.0f < check && check < 100.0f){
        return std::sqrtf(check)*3.2f;

    }else{
        return -1.0f;
    }
}

/* 00003C54-00003D34       .text routeCheck__11daNpc_Ko1_cFfPs */
s32 daNpc_Ko1_c::routeCheck(float i_param_1, short* i_param_2) {
    /* Nonmatching */
    if(field_0x898 != 3 && mObjAcch.ChkWallHit()){
        chk_wallJump(*i_param_2);
    }
    cXyz local_1c(current.pos.x,current.pos.y + 80.0f, current.pos.z);
    cXyz local_28(current.pos.x+80.0f*cM_ssin(*i_param_2),local_1c.y,current.pos.z+80.0f*cM_scos(*i_param_2));
    routeWallCheck(local_1c,local_28,i_param_2);
    return 1;
}

/* 00003D34-00003DE8       .text chk_start_swim__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::chk_start_swim() {

    bool uVar1 = false;
    if(mObjAcch.ChkWaterIn()){
        uVar1 = mObjAcch.m_wtr.GetHeight() - mObjAcch.m_ground_h > 62.0f; 
        if( uVar1 ){
            if(field_0x8A3 != 7){
            setPrtcl_Hamon(1.0f,0.0f);
            }
        }else if(field_0x8A3 == 7){
                setPrtcl_Hamon(0.5f,1.0f);
        }
    }else{
        field_0x878.end();
        field_0x88C = 0;
    }
    return uVar1;
}

/* 00003DE8-00003E64       .text get_crsActorID__11daNpc_Ko1_cFv */
fpc_ProcID daNpc_Ko1_c::get_crsActorID() {

    fopAc_ac_c* var_r3;
    if(mCyl.ChkCoHit()){
        cCcD_Obj* temp_r3 = mCyl.GetCoHitObj();
        if(temp_r3){
            if(temp_r3->GetStts() == NULL){
                var_r3 = NULL;
            }else{
                var_r3 = temp_r3->GetStts()->GetActor();
            }
            if(var_r3 != NULL){
                return var_r3->base.mBsPcId;
            }
            return -1;
        }
    }
    return -1;
}

/* 00003E64-00003F50       .text chk_areaIn__11daNpc_Ko1_cFf4cXyz */
bool daNpc_Ko1_c::chk_areaIn(float i_param_1, cXyz i_param_2) {

    return (dComIfGp_getLinkPlayer()->current.pos-i_param_2).absXZ() < i_param_1;

}

/* 00003F50-00003FF0       .text setPrtcl_Hamon__11daNpc_Ko1_cFff */
void daNpc_Ko1_c::setPrtcl_Hamon(float i_param_1, float i_param_2) {
    /* Nonmatching */
    cXyz scale;
    scale.setall(i_param_1);
    field_0x878.end();
    field_0x88C = dComIfGp_particle_setShipTail(0x33,&current.pos,NULL,&scale,0xFF,&field_0x878);
    if(field_0x88C != NULL){
        field_0x878.setRate(i_param_2);
    }
}

/* 00003FF0-000040F8       .text setPrtcl_HanaPachi__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::setPrtcl_HanaPachi() {
    /* Nonmatching */
    cXyz local_18;
    mDoMtx_stack_c::copy(mBlnAnm->getModel()->getAnmMtx(m_bln_jnt_num));
    mDoMtx_stack_c::multVecZero(&local_18);

    field_0x890 = dComIfGp_particle_set(0x830C,&local_18,&current.angle,NULL,0xFF,NULL,fopAcM_GetRoomNo(this));
    field_0x894 = dComIfGp_particle_set(0x8313,&local_18,&current.angle,NULL,0xFF,NULL,fopAcM_GetRoomNo(this));

}

/* 000040F8-0000420C       .text charDecide__11daNpc_Ko1_cFi */
bool daNpc_Ko1_c::charDecide(int i_param_1) {

    s16 temp_r0;
    field_0x8A6 = -1;
    field_0x8A7 = -1;
    temp_r0 = base.mProcName;
    switch (temp_r0) {                              /* irregular */
    case 0x141:
        field_0x8A6 = 0;
        switch (i_param_1) {                             /* switch 1; irregular */
        case 0:                                     /* switch 1 */
            field_0x8A7 = 0;
            break;
        case 1:                                     /* switch 1 */
            field_0x8A7 = 1;
            break;
        case 2:                                     /* switch 1 */
            field_0x8A7 = 2;
            break;
        case 3:                                     /* switch 1 */
            field_0x8A7 = 3;
            break;
        case 4:                                     /* switch 1 */
            field_0x8A7 = 4;
            break;
        default:                                    /* switch 1 */
            return 0;
        }
        break;
    case 0x142:
        field_0x8A6 = 1;
        switch (i_param_1) {                             /* switch 2; irregular */
        case 0:                                     /* switch 2 */
            field_0x8A7 = 5;
            break;
        case 1:                                     /* switch 2 */
            field_0x8A7 = 6;
            break;
        case 2:                                     /* switch 2 */
            field_0x8A7 = 7;
            break;
        case 3:                                     /* switch 2 */
            field_0x8A7 = 8;
            break;
        default:   
            return 0;                                 /* switch 2 */
            break;
        }
        break;
    default:
        return 0;
    }
    return 1;

}

/* 0000420C-00004264       .text event_actionInit__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::event_actionInit(int i_param_1) {

    int* act_no = dComIfGp_evmng_getMyIntegerP(i_param_1,"ActNo");
    if(act_no){
        field_0x89B = *act_no; 
    }
}

/* 00004264-00004274       .text event_action__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::event_action() {

    switch(field_0x89B){
        case 0:
        default:
            return 1;
    }



}

/* 00004274-00004360       .text privateCut__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::privateCut(int i_param_1) {

    bool cVar3;
    static char* a_cut_tbl[1] = {"ACTION"};
    if(i_param_1 != -1){
        field_0x89A = dComIfGp_evmng_getMyActIdx(i_param_1,a_cut_tbl,1,1,0);
        if(field_0x89A == -1){
            dComIfGp_evmng_cutEnd(i_param_1);
        }else{
            if(dComIfGp_evmng_getIsAddvance(i_param_1)){
                switch(field_0x89A){
                    case 0:
                        event_actionInit(i_param_1);
                        break;
                }
            }
            switch(field_0x89A){
                case 0:
                    cVar3 = event_action();
                    break;
                default:
                    cVar3 = 1;
                    break;
            }

            if(cVar3 != 0){
                dComIfGp_evmng_cutEnd(i_param_1);
            }
        }
    }
}

/* 00004360-00004384       .text endEvent__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::endEvent() {

    dComIfGp_event_onEventFlag(8);
    field_0x89C = 0xFF;
    field_0x89D = 0xFF;
}

/* 00004384-000043BC       .text isEventEntry__11daNpc_Ko1_cFv */
int daNpc_Ko1_c::isEventEntry() {

    return dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
}

/* 000043BC-00004414       .text event_proc__11daNpc_Ko1_cFi */
void daNpc_Ko1_c::event_proc(int i_param_1) {

    if(!mEventCut.cutProc()){
        privateCut(i_param_1);
    }
    lookBack();
}

/* 00004414-000044C0       .text set_action__11daNpc_Ko1_cFM11daNpc_Ko1_cFPCvPvPv_iPv */
s32 daNpc_Ko1_c::set_action(ActionFunc i_param_1, void* i_param_2) {

    if(field_0x730 != i_param_1){
        if(field_0x730 != NULL){
            field_0x8A8 = 9;
            (this->*field_0x730)(i_param_2);
        }
        field_0x730 = i_param_1;
        field_0x8A8 = 0;
        (this->*field_0x730)(i_param_2);    
    }
    return 1;
}

/* 000044C0-000044E8       .text clrSpd__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::clrSpd() {

    field_0x82C = 0;
    field_0x834 = 0;
    speed.y = 0.0f;
    speedF = 0.0f;
    gravity = -4.5f;
    /* Nonmatching */
}

/* 000044E8-00004B18       .text setStt__11daNpc_Ko1_cFSc */
void daNpc_Ko1_c::setStt(signed char i_param_1) {

    fopAc_ac_c* a_partner = searchByID(field_0x7B4[0]);
    dPath* temp_r4_2;
    s8 temp_r30 = field_0x8A3;
    field_0x84E = 0;
    field_0x8A3 = i_param_1;
    switch(field_0x8A3){
        case 1:
        case 2:
        case 12:
        case 22:
        case 29:
            switch(field_0x8A3){
                case 1:
                    field_0x852 = 90.0f + cM_rndF(90.0f);
                    break;
                case 2:
                    field_0x854 = (g_Counter.mCounter0 & 3) + 1;
                    break;
            }
            if (temp_r30 != 3) {
                field_0x8A5 = 3;
                field_0x858 = field_0x7D0.y;
                m_jnt.mbTrn = true;
                field_0x876 = 0;
            }
            field_0x8A2 = 0;
            field_0x898 = 0;
            clrSpd();
            break;    
        case 3:
            field_0x8A5 = 1;
            m_jnt.mbTrn = 1;
            field_0x876 = 0;
            field_0x8A2 = 0;
            field_0x898 = 0;
            clrSpd();
            field_0x89C = 0xFF;
            field_0x89D = 0xFF;
            field_0x8A4 = temp_r30;                        
            break;
        case 4:
        case 11:
            switch(field_0x8A3){
                case 4:
                    field_0x852 = 180.0f + cM_rndF(180.0f);
                    break;
                case 11:
                    if(field_0x744 != NULL){
                        mPathRun.setInfDrct((dPath*)field_0x744);
                        mPathRun.setNearPathIndx(&current.pos,0.0f);
                        field_0x744 = 0;
                    }
            }
    
            field_0x7F4 = mPathRun.getPoint(mPathRun.getIdx());
            field_0x8A5 = 0;
    
            field_0x876 = 1;
            field_0x8A2 = 0;
            field_0x898 = 1;
            field_0x86B = 0;
            goto label_420;
        case 5:
            field_0x8A5 = 0;
            field_0x876 = 0;
            field_0x8A2 = 0;
            field_0x898 = 0;
            clrSpd();
            break;
        case 6:
        case 13:
        case 23:
            switch(field_0x8A3){
                case 6:
                    if(mPathRun.isPath()){
                        field_0x744 = mPathRun.getPath();
                        mPathRun.setInfDrct(0);
                    }
            } 
    
            field_0x7F4 = dComIfGp_getLinkPlayer()->current.pos;
            field_0x8A5 = 1;
            field_0x876 = 1;
            field_0x8A2 = 0;
            field_0x898 = 2;
            field_0x86B = 0;
            goto label_514;
        case 7:
            if(mPathRun.isPath()){
                field_0x744 = mPathRun.getPath();
                mPathRun.setInfDrct(0);
            }
            field_0x7F4 = dComIfGp_getLinkPlayer()->current.pos;
            field_0x8A5 = 1;
            field_0x876 = 1;
            goto label_320;
        case 8:
            temp_r4_2 = (dPath*)field_0x744;
            if(temp_r4_2 != NULL){
                mPathRun.setInfDrct(temp_r4_2);
                mPathRun.setNearPathIndx(&current.pos,0.0);
                field_0x744 = NULL;
            }
            field_0x7F4 = mPathRun.getPoint(mPathRun.getIdx());
            field_0x8A5 = 0;
            field_0x876 = 1;
        label_320:
            field_0x8A2 = 0;
            field_0x898 = 3;
            field_0x86B = 0;
            field_0x830 = -4.0f;
            speed.y = field_0x830;
            speedF = 0.0f;
            field_0x834 = 0.0f;
            field_0x82C = 0.0f;
            fopAcM_SetGravity(this,0.0f);
            field_0x83C = l_HIO.children[field_0x8A6].hio_prm.field44;
            break;
        case 9:
        case 16:
        case 18:
        case 25:
            field_0x8A5 = 0;
            field_0x876 = 0;
            field_0x8A2 = 0;
            field_0x899 = field_0x898;            
            field_0x898 = 4;
            field_0x86C = 1;
            speed.y = 10.0f;
            speedF = -3.0f;
            gravity = -1.6f;
            field_0x834 = 0.1f;
            break;
        case 10:
        case 14:
        case 26:
            field_0x8A5 = 1;
            field_0x876 = 0;
            field_0x8A2 = 0;         
            field_0x898 = 0;
            clrSpd();
            break;
        case 15:
        case 24:
            field_0x7F4 = field_0x7C4;
            field_0x8A5 = 0;
            field_0x876 = 1;
            field_0x8A2 = 0;         
            field_0x898 = 1;
            field_0x86B = 0;
        label_420:
            fopAcM_SetGravity(this,-4.5f);
            field_0x82C =  l_HIO.children[field_0x8A6].hio_prm.field28;
            field_0x834 = l_HIO.children[field_0x8A6].hio_prm.field2C;
            field_0x83C = l_HIO.children[field_0x8A6].hio_prm.field30;
            break;
        case 17:
            JUT_ASSERT(2675,a_partner != NULL);
            field_0x7F4 = a_partner->current.pos;
            field_0x8A5 = 2;
            field_0x7E8 = field_0x7F4;
            field_0x7E8.y = a_partner->eyePos.y;
            field_0x876 = 1;
            field_0x8A2 = 0;         
            field_0x898 = 2;
            field_0x86B = 0;
        label_514:
            fopAcM_SetGravity(this,-4.5f);
            field_0x82C =  l_HIO.children[field_0x8A6].hio_prm.field38;
            field_0x834 = l_HIO.children[field_0x8A6].hio_prm.field3C;
            field_0x83C = l_HIO.children[field_0x8A6].hio_prm.field40;
            break;
        case 19:
            if (a_partner != NULL) {
                field_0x8A5 = 2;
                field_0x7E8 = a_partner->current.pos;
                field_0x7E8.y = a_partner->eyePos.y;
            } else {
                field_0x8A5 = 0;
            }
            field_0x876 = 0;
            field_0x8A2 = 0;         
            field_0x898 = 0; 
            clrSpd();
            break;
        case 20:
            field_0x89C =  0xFF;
            field_0x89D =  0xFF;
            field_0x8A4 = temp_r30;
            break;
        case 27:
        case 28:
            field_0x852 = 180.0f + cM_rndF(180.0f);
            field_0x854 = cLib_getRndValue(3,10);
            field_0x865 = 0;
            break;
    }
    setAnm();
}

/* 00004B18-00004C70       .text wait_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_1() {

    if(field_0x875){
        if(chk_talk()){
            setStt(3);
        };
        return 1;
    }
    field_0x8A2 = 2;
    field_0x8A5 = 3;
    field_0x858 = field_0x7D0.y;
    if ((s32) field_0x89F == 6) {
        if ((s8) field_0x860 != 0) {
            cLib_calcTimer(&field_0x854);
        }
        if ((field_0x854 == 0) || (field_0x874 != 0)) {
            field_0x854 = (g_Counter.mCounter0 & 3) + 1;
            field_0x852 = (s16) (90.0f + cM_rndF(90.0f));
            setAnm_NUM(0, 1);
        }
        return 1;
    }
    if ((u8) field_0x874 != 0) {
        field_0x84E = 0x3C;
    }
    if (cLib_calcTimer(&field_0x84E) != 0) {
        field_0x8A5 = 1;
        return 1;
    }
    if (cLib_calcTimer(&field_0x852) == 0) {
        setAnm_NUM(6, 1);
    }
    m_jnt.mbTrn = true;
    return 1;
}

/* 00004C70-00004CE8       .text wait_2__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_2() {

    if(field_0x860){
        cLib_calcTimer(&field_0x854);
        if(!field_0x854 || field_0x874 || field_0x875 ){
            setStt(1);
            return 1;
        };
    }
    return 1;
}

/* 00004CE8-00004D1C       .text wait_3__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_3() {
    /* Nonmatching */
    if (field_0x860 != 0) {
        setStt(4);
    }
    return 1;
}

/* 00004D1C-00004E64       .text wait_4__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_4() {

    if (field_0x875) {
        if (chk_talk()) {
            setStt(3);
        }
        return 1;
    }
    if (chk_start_swim()) {
        setStt(7);
        return 1;
    }

    if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field50,current.pos) == 0) {

        if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field58, field_0x80C) == 0) {
            setStt(0xB);
            return 1;
        }
        setStt(6);
        return 1;
    }
    field_0x8A2 = 2;
    return 1;
}

/* 00004E64-00004F30       .text wait_5__11daNpc_Ko1_cFSc */
BOOL daNpc_Ko1_c::wait_5(signed char i_param_1) {

    if (field_0x6bc[0] == 1) {
        field_0x6bc[0] = 2;
        setStt(0x14);
        field_0x8A5 = 1;
        field_0x876 = 0;
        field_0x8A2 = 0;
        field_0x898 = 0;
        clrSpd();
        return 1;
    }

    if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field48, field_0x80C)) {
        setStt(i_param_1);
    }
    return 1;
}

/* 00004F30-00005088       .text wait_6__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_6() {

    if (field_0x875) {
        if (chk_talk()) {
            if(chk_manzai_1()){
                setStt(3);
            }
        }
        return 1;
    }
    if (field_0x6bc[0] == 1) {
        field_0x6bc[0] = 2;
        setStt(0x14);
        return 1;
    }

    if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field50,current.pos) == 0) {

        if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field4C, field_0x80C) == 0) {
            setStt(0xF);
            return 1;
        }
        setStt(0xD);
        return 1;
    }
    field_0x8A2 = 2;
    return 1;
}

/* 00005088-000052D4       .text wait_7__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_7() {
    /* Nonmatching */

    fopAc_ac_c* a_partner = searchByID(field_0x7B4[0]);
    JUT_ASSERT(2923,a_partner != NULL);
    if (field_0x875) {
        if (chk_talk()) {
            if(chk_manzai_1()){
                setStt(3);
            }
        }
        return 1;
    }
    if (field_0x6bc[0] == 1) {
        field_0x6bc[0] = 2;
        setStt(0x14);
        field_0x8A5 = 1;
        field_0x876 = 0; 
        field_0x8A2 = 0;
        field_0x898 = 0;  
        clrSpd(); 
        return 1;
    }
    if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field50,current.pos) ) {
        field_0x8A5 = 1;
    }else{
        field_0x8A5 = 2;
        field_0x7E8 = a_partner->current.pos;
        field_0x7E8.y = a_partner->eyePos.y;
    }
    if((a_partner->current.pos - current.pos).absXZ() < l_HIO.children[field_0x8A6].hio_prm.field50){
        field_0x8A2 = 2;
    }else{
        setStt(17);
    }
    return 1;
}

/* 000052D4-000053F8       .text wait_9__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_9() {

    if (field_0x875) {
        if (chk_talk()) {
            setStt(3);
        }
        return 1;
    }
    if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field50,current.pos) == 0) {

        if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field4C, field_0x80C) == 0) {
            setStt(0x18);
            return 1;
        }
        setStt(0x17);
        return 1;
    }else{
        field_0x8A2 = 2;
        return 1;
    }
}

/* 000053F8-00005524       .text wait_a__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::wait_a() {

    fopAc_ac_c* a_partner = searchByID(field_0x7B4[0]);
    JUT_ASSERT(3011,a_partner != NULL);
    if(field_0x875){
        if(chk_talk() && chk_manzai_1()){
            setStt(3);
        }
        return 1;
    }else{
        if(field_0x6bc[0] == 1){
            field_0x6bc[0] = 2;
            setStt(0x14);
            return 1;
        }else{
            field_0x8A2 = 2;
            if(field_0x874){
                field_0x84E = 0x3C;
            }
            if(cLib_calcTimer(&field_0x84E)){
                field_0x8A5 = 1;

            }else{
                field_0x8A5 = 3;
                field_0x858 = field_0x7D0.y;
                m_jnt.mbTrn = true;
            }
        }
    }
    return 1;
}

/* 00005524-000055F8       .text walk_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::walk_1() {

    field_0x86B = 0;
    field_0x7F4 = mPathRun.getPoint(mPathRun.getIdx());
    if(chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field54,field_0x80C)){
        setStt(6);
        return 1;
    }else{
        if(!cLib_calcTimer(&field_0x852)){
            setStt(5);
        }
    }
    return 1;
}

/* 000055F8-000056D4       .text walk_2__11daNpc_Ko1_cFScSc */
BOOL daNpc_Ko1_c::walk_2(signed char i_param_1, signed char i_param_2) {

    if (field_0x86B != 0) {
        setStt(i_param_1);
        return 1;
    }
    if (field_0x6bc[0] == 1) {
        setStt(0xE);
        return 1;
    }
    if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field48,field_0x80C)) {
        setStt(i_param_2);
        return 1;
    }
    field_0x7F4 = field_0x7C4;
    return 1;

}

/* 000056D4-000057B8       .text walk_3__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::walk_3() {

    if (field_0x86B != 0) {
        setStt(4);
        return 1;
    }

    if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field54,field_0x80C)) {
        setStt(6);
        return 1;
    }else{
        field_0x7F4 = mPathRun.getPoint(mPathRun.getIdx());
        if(chk_start_swim()){
            setStt(8);
        }
    }
    return 1;
}

/* 000057B8-000058EC       .text swim_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::swim_1() {
    /* Nonmatching */
    f32 temp_f1 = mObjAcch.m_wtr.GetHeight() - current.pos.y;
    if (temp_f1 < 49.0f) {
        field_0x830 = -4.0f;
        if ((u8) field_0x86B == 0) {
            speedF = 8.0f;
        }
    } else if (temp_f1 > 58.0f) {
        field_0x830 = 4.0f;
    }
    if (!chk_start_swim()) {
        setStt(6);
        return 1;
    }

    if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field58, field_0x80C) == 0){
        setStt(8);
        return 1;
    }
    field_0x86B = 0;
    field_0x7F4 = dComIfGp_getLinkPlayer()->current.pos;
    return 1;
}

/* 000058EC-00005A1C       .text swim_2__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::swim_2() {
    /* Nonmatching */
    f32 temp_f1 = mObjAcch.m_wtr.GetHeight() - current.pos.y;
    if (temp_f1 < 49.0f) {
        field_0x830 = -4.0f;
        if ((u8) field_0x86B == 0) {
            speedF = 8.0f;
        }
    } else if (temp_f1 > 58.0f) {
        field_0x830 = 4.0f;
    }
    if (!chk_start_swim()) {
        setStt(0xB);
        return 1;
    }

    if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field54, field_0x80C)){
        setStt(7);
        return 1;
    }
    field_0x86B = 0;
    field_0x7F4 = mPathRun.getPoint(mPathRun.getIdx());
    return 1;
}

/* 00005A1C-00005B64       .text attk_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::attk_1() {
    
    field_0x86B = 0;
    fpc_ProcID uVar1 = get_crsActorID();
    field_0x7C0 = uVar1;
    fopAc_ac_c* actor;
    if ((field_0x7C0 != 0xffffffff) && (actor = searchByID(field_0x7C0), actor) && actor->base.mProcName == 0xA9){
            setStt(9);
            return 1;
    }
    else {
        if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field58,field_0x80C) == 0) {
            setStt(11);
            return 1;
        }
        else {

            field_0x7F4 = set_tgtPos(dComIfGp_getLinkPlayer()->current.pos);

            if (chk_start_swim()) {
                setStt(7);
            }
        }
    }
    return 1;
}

/* 00005B64-00005C94       .text attk_2__11daNpc_Ko1_cFScSc */
BOOL daNpc_Ko1_c::attk_2(signed char i_param_1, signed char i_param_2) {

    field_0x86B = 0;
    if(field_0x6bc[0] == 1){
        setStt(0xE);
        return true;
    }
    fpc_ProcID uVar1 = get_crsActorID();
    field_0x7C0 = uVar1;
    fopAc_ac_c* actor;
    if ((field_0x7C0 != 0xffffffff) && (actor = searchByID(field_0x7C0), actor) && actor->base.mProcName == 0xA9){
            setStt(i_param_1);
            return 1;
    }
    else {
        if (chk_areaIn(l_HIO.children[field_0x8A6].hio_prm.field4C,field_0x80C) == 0) {
            setStt(i_param_2);
            return 1;
        }
        else {
            field_0x7F4 = dComIfGp_getLinkPlayer()->current.pos;
        }
    }
    return 1;
}

/* 00005C94-00005DEC       .text attk_3__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::attk_3() {
    /* Nonmatching */

    fopAc_ac_c* a_partner = searchByID(field_0x7B4[0]);
    JUT_ASSERT(3282,a_partner != NULL);
    field_0x86B = 0;
    if(field_0x6bc[0] == 1){
        setStt(0x13);
        return true;
    }
    fpc_ProcID uVar1 = get_crsActorID();
    field_0x7C0 = uVar1;
    fopAc_ac_c* actor;
    if ((field_0x7C0 != 0xffffffff) && (actor = searchByID(field_0x7C0), actor) && (actor->base.mProcName == 0x142 || actor->base.mProcName == 0xA9)){
        setStt(0x12);
        return 1;
    }
    else {
        field_0x7F4 = set_tgtPos(a_partner->current.pos);
        field_0x7E8 = field_0x7F4;
        field_0x7E8.y = a_partner->eyePos.y;
        return 1;
    }
    return 1;
}

/* 00005DEC-00005E1C       .text down_1__11daNpc_Ko1_cFSc */
BOOL daNpc_Ko1_c::down_1(signed char i_param_1) {

    if(field_0x86B){
        setStt(i_param_1);
    }
    return true;
}

/* 00005E1C-0000609C       .text talk_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::talk_1() {

    BOOL uVar6 = chk_partsNotMove();
    if(mpCurrMsg != NULL){
        field_0x6b8 = mpCurrMsg->mStatus;
    }else{
        field_0x6b8 = 0;
    }
    if(field_0x6bc[0] == 2 && mCurrMsgBsPcId == -1){
        mCurrMsgNo = getMsg();
        mCurrMsgBsPcId = fopMsgM_messageSet(mCurrMsgNo,dComIfGp_getMesgCameraInfo()->mActor[0]);
        mpCurrMsg = NULL;
    }else{
        field_0x848 = 0xFFFFFFFF;
        talk(1);
    }

    if(mpCurrMsg != NULL){
        switch(mpCurrMsg->mStatus){
            case 2:
            case 6:
                break;
            case 19:
                switch(mCurrMsgNo){
                    case 0xAF1:                         /* switch 1 */
                        dComIfGs_onEventBit(0x210U);
                        break;
                    case 0xAFF:                         /* switch 1 */
                        dComIfGs_onEventBit(0x3801U);
                        break;
                    case 0xB06:                         /* switch 1 */
                        dComIfGs_onEventBit(0x3340U);
                        break;
                    case 0xB55:                         /* switch 1 */
                        dComIfGs_onEventBit(0x220U);
                        break;
                    case 0xB57:                         /* switch 1 */

                        dComIfGs_onEventBit(0x208U);
                        dComIfGs_onEventBit(0x240U);
                        break;
                    case 0xB62:                         /* switch 1 */
                        dComIfGs_onEventBit(0x3101U);
                        break;
                    case 0xB64:                         /* switch 1 */
                        dComIfGs_onEventBit(0x2C04U);
                        field_0x86D = 1;
                        break;
                }
                field_0x863 = 0xFF;
                field_0x875 = 0;
                switch(field_0x8A7){

                    case 1:
                    case 3:
                    case 6:  
                    case 7:           
                        setStt(0x15);
                        break;
                    default:
                        setStt(field_0x8A4);
                        field_0x84E = 0x3C;
                        endEvent();
                        break;

                }
            break;
        }
    }
    return uVar6;
    
}

/* 0000609C-00006184       .text talk_2__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::talk_2() {

    s32 uVar4 = 0;
    for(int i = 0; i < field_0x7BC; i++){
        fopNpc_npc_c* a_actor = (fopNpc_npc_c*)searchByID(field_0x7B4[i]);
        JUT_ASSERT(3417,NULL != a_actor);
        if(a_actor->field_0x6bc[0] != 0){
            a_actor->field_0x6bc[0] = 3;
        }else{
            uVar4 += 1;
        }
    }
    if(uVar4 == field_0x7BC){
        field_0x6bc[0] = 0;
        setStt(field_0x8A4);
        endEvent();
    }
    return 1;

}

/* 00006184-000062B4       .text manzai__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::manzai() {

    dComIfG_MesgCamInfo_c* temp_r30 = dComIfGp_getMesgCameraInfo();
    fopNpc_npc_c* temp_r4;
    switch(field_0x6bc[0]){
        case 2:
            temp_r4 = (fopNpc_npc_c*)searchByID(field_0x6b4);
            if(this != temp_r30->mActor[temp_r30->mBasicID-1]){

                if(field_0x89C != 0xFF){
                    if(field_0x8A7 == 1|| field_0x8A7 == 6){
                        field_0x8A5 = 1;
                        m_jnt.mbTrn = true;
                    }else{
                                field_0x8A5 = 3;
                                field_0x858 = field_0x7D0.y;
                                m_jnt.mbTrn = true;
                                field_0x8A3 = field_0x8A4;
                                setAnm();
                                field_0x8A3 = 0x14;            
                    }                
                    field_0x89C = 0xFF;
                }
            }else{
                field_0x848 = temp_r4->mCurrMsgNo;
                anmAtr(temp_r4->field_0x6b8);
            }

            break;
        case 3:
            fopAcM_OffStatus(this,0x4000);
            setStt(field_0x8A4);
            field_0x6bc[0] = 0;
            break;
    }
    return 1;
}

/* 000062B4-00006358       .text neru_1__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::neru_1() {

    u32 neruarray[] = {7,8};
    if(!cLib_calcTimer(&field_0x852)){
        field_0x865 ^= 1;
        setAnm_NUM(neruarray[field_0x865],1);
        field_0x852 = 180.0f + cM_rndF(180.0f);
    }
    return 1;
}

/* 00006358-00006524       .text neru_2__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::neru_2() {

    u32 neruarray[] = {9,12,10};
    switch(field_0x865){
        case 0:
            if(!cLib_calcTimer(&field_0x852)){
                if(!cLib_calcTimer(&field_0x854)){
                    field_0x865 = 1;
                    setAnm_NUM(neruarray[field_0x865],1);
                    set_balloonAnm_NUM(1);
                    field_0x854 = cLib_getRndValue(3,10);
                }
                field_0x852 = 180.0f + cM_rndF(180.0f);
            }
            break;
        case 1:
            if(field_0x860){
                field_0x865 = 2;
                setAnm_NUM(neruarray[field_0x865],1);
            }else if(mpMorf->checkFrame(2)){
                setPrtcl_HanaPachi();
                fopAcM_seStart(this,0x592C,0);
            }
            break;
        case 2:
            if(field_0x860){
                field_0x865 = 0;
                setAnm_NUM(neruarray[field_0x865],1);
                set_balloonAnm_NUM(0);
            }
            break;
    }
    return 1;

}

/* 00006524-00006668       .text hana_action1__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::hana_action1(void* i_param_1) {
    /* Nonmatching */

    BOOL uVar2;

    switch(field_0x8A8){

        case 9:
            break;
        case 0:
            ko_setPthPos();
            setStt(4);
            field_0x8A8 += 1;
            break;
        case 1:
        case 2:
        case 3:

        field_0x874 = chkAttention();
        switch(this->field_0x8A3) {
        case 4:
        uVar2 = walk_1();
        field_0x870 = uVar2;
        break;
        case 11:
        uVar2 = walk_3();
        field_0x870 = uVar2;
        break;
        case 5:
        uVar2 = wait_3();
        field_0x870 = uVar2;
        break;
        case 10:
        uVar2 = wait_4();
        field_0x870 = uVar2;
        break;
        case 6:
        uVar2 = attk_1();
        field_0x870 = uVar2;
        break;
        case 7:
        uVar2 = swim_1();
        field_0x870 = uVar2;
        break;
        case 8:
        uVar2 = swim_2();
        field_0x870 = uVar2;
        break;
        case 9:
        uVar2 = down_1(10);
        field_0x870 = uVar2;
        break;
        case 3:
        uVar2 = talk_1();
        field_0x870 = uVar2;
        break;
        }
        lookBack();
        break;
    }

    return 1;
}

/* 00006668-00006774       .text hana_action2__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::hana_action2(void*) {
    /* Nonmatching */
    s32 uVar2;
    switch(field_0x8A8){

        case 9:
            break;
        case 0:
            setStt(0x13);
            field_0x8A8 += 1;
            break;
        case 1:
        case 2:
        case 3:
        bool uVar3 = chkAttention();
        this->field_0x874 = uVar3;
        switch(field_0x8A3) {

            case 19:
                uVar2 = wait_7();
                field_0x870 = uVar2;
                break;
            case 17:
                uVar2 = attk_3();
                field_0x870 = uVar2;
                break;
            case 18:
                uVar2 = down_1('\x13');
                field_0x870 = uVar2;
                break;
            case 3:
                uVar2 = talk_1();
                field_0x870 = uVar2;
                break;
            case 21:
                uVar2 = talk_2();
                field_0x870 = uVar2;
                break;
            case 20:
                uVar2 = manzai();
                field_0x870 = uVar2;
            }
            lookBack();
            

    }
 return 1;
}

/* 00006774-00006894       .text hana_action3__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::hana_action3(void*) {
    BOOL uVar2;

    switch(field_0x8A8){

        case 9:
            break;
        case 0:
            setStt(0x16);
            field_0x8A8 += 1;
            break;
        case 1:
        case 2:
        case 3:
            bool uVar3 = chkAttention();
            this->field_0x874 = uVar3;
            switch(field_0x8A3) {
            case 22:
            uVar2 = wait_5('\x17');
            field_0x870 = uVar2;
            break;
            case 23:
            uVar2 = attk_2('\x19','\x18');
            field_0x870 = uVar2;
            break;
            case 24:
            uVar2 = walk_2('\x16','\x17');
            field_0x870 = uVar2;
            break;
            case 26:
            uVar2 = wait_9();
            field_0x870 = uVar2;
            break;
            case 25:
            uVar2 = down_1('\x1a');
            field_0x870 = uVar2;
            break;
            case 3:
            uVar2 = talk_1();
            field_0x870 = uVar2;
            }
            lookBack();
    }
    return 1;
}

/* 00006894-00006988       .text hana_action4__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::hana_action4(void*) {

    BOOL uVar2;
    switch(field_0x8A8){

        case 9:
            break;
        case 0:
            setStt(0x1D);
            field_0x8A8 += 1;
            break;
        case 1:
        case 2:
        case 3:
            bool uVar3 = chkAttention();
            this->field_0x874 = uVar3;
            switch(field_0x8A3) {
            case 29:
            uVar2 = wait_a();
            field_0x870 = uVar2;
            break;
            case 3:
            uVar2 = talk_1();
            field_0x870 = uVar2;
            break;
            case 21:
            uVar2 = talk_2();
            field_0x870 = uVar2;
            break;
            case 20:
            uVar2 = manzai();
            field_0x870 = uVar2;
            break;
            }
            lookBack();
            break;
    }
    return 1;

}

/* 00006988-00006A24       .text hana_action5__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::hana_action5(void*) {

    s8 temp_r0 = field_0x8A8;
    switch (temp_r0){
    case 9:
        break;
    case 0:
        setStt(0x1C);
        field_0x8A8 += 1;
        break;
    case 1:
    case 2:
    case 3:
        field_0x874 = chkAttention();
        switch(field_0x8A3){
            case 0x1C:
                field_0x870 = neru_2();
                break;
            default:

                break;
        }
        lookBack();
        break;
    }
    return 1;
}

/* 00006A24-00006B24       .text wait_action1__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::wait_action1(void*) {
    /* Nonmatching */
    s8 temp_r0 = field_0x8A8;
    switch (temp_r0){
    case 9:
        break;
    case 0:
        setStt(1);
        field_0x8A8 += 1;
        break;
    case 1:
    case 2:
    case 3:
        if(!dComIfGs_isEventBit(0x104)){
            check_landOn();
        }
        field_0x874 = chkAttention();
        switch(field_0x8A3){
            case 1:
                field_0x870 = wait_1();
                break;
            case 2:
                field_0x870 = wait_2();
                break;
            case 3:
                field_0x870 = talk_1();
                break;
        }
        lookBack();
        break;
    }
    return 1;
}

/* 00006B24-00006C64       .text wait_action2__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::wait_action2(void*) {

    s8 temp_r0 = field_0x8A8;
    switch (temp_r0){
    case 9:
        break;
    case 0:
        setStt(0xC);
        field_0x8A8 += 1;
        break;
    case 1:
    case 2:
    case 3:
        field_0x874 = chkAttention();
        switch(field_0x8A3){

            case 12:
                field_0x870 = wait_5(13);
                break;
            case 13:
                field_0x870 = attk_2(16,15);
                break;        
            case 15:
                field_0x870 = walk_2(12,13);
                break;    
            case 14:
                field_0x870 = wait_6();
                break;

            case 16:
                field_0x870 = down_1(14);
                break;
            case 3:
                field_0x870 = talk_1();
                break;
            case 21:
                field_0x870 = talk_2();
                break;
            case 20:
                field_0x870 = manzai();
                break;
        }
        lookBack();
        break;
    }
    return 1;
}

/* 00006C64-00006D58       .text wait_action3__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::wait_action3(void*) {

    s8 temp_r0 = field_0x8A8;
    switch (temp_r0){
    case 9:
        break;
    case 0:
        setStt(0x1D);
        field_0x8A8 += 1;
        break;
    case 1:
    case 2:
    case 3:
        field_0x874 = chkAttention();
        switch(field_0x8A3){

            case 29:
                field_0x870 = wait_a();
                break;
            case 3:
                field_0x870 = talk_1();
                break;
            case 21:
                field_0x870 = talk_2();
                break;
            case 20:
                field_0x870 = manzai();
                break;
        }
        lookBack();
        break;
    }
    return 1;
}

/* 00006D58-00006DF4       .text wait_action4__11daNpc_Ko1_cFPv */
int daNpc_Ko1_c::wait_action4(void*) {

    s8 temp_r0 = field_0x8A8;
    switch (temp_r0){
    case 9:
        break;
    case 0:
        setStt(0x1B);
        field_0x8A8 += 1;
        break;
    case 1:
    case 2:
    case 3:
        field_0x874 = chkAttention();
        switch(field_0x8A3){
            case 27:
                field_0x870 = neru_1();
                break;
        }
        lookBack();
        break;
    }
    return 1;
}

/* 00006DF4-00006F34       .text demo__11daNpc_Ko1_cFv */
u8 daNpc_Ko1_c::demo() {
    /* Nonmatching */
    s16 cmp;
    if(demoActorID == 0){
        if(field_0x877 != 0){
            field_0x877 = 0;
        }
    }else{
        field_0x877 = 1;
        dDemo_actor_c* a_actor = dComIfGp_demo_getActor(demoActorID);
        if(m_hed_tex_pttrn != NULL){

            mBtpFrame += 1;
            if (mBtpFrame >= m_hed_tex_pttrn->getFrameMax()) {
                mBtpFrame = m_hed_tex_pttrn->getFrameMax();
            }
        }
        J3DAnmTexPattern* pJVar2 = (J3DAnmTexPattern*)a_actor->getP_BtpData("Ko");
        if(pJVar2 != NULL){
            m_hed_tex_pttrn = pJVar2; 
            if(mBtpAnm.init(field_0x710->getModel()->getModelData(),m_hed_tex_pttrn,1,2,1.0,0,-1,true,0)){
                field_0x89E = 4;
                mBtpFrame = 0;
            }
        }
        dDemo_setDemoData(this,0x6A,mpMorf,"Ko");
    }
    return field_0x877;
}

/* 00006F34-00007008       .text shadowDraw__11daNpc_Ko1_cFv */
void daNpc_Ko1_c::shadowDraw() {
    /* Nonmatching */
    cXyz local_18(current.pos.x,current.pos.y + 150.0f, current.pos.z);
    GXTexObj* tex = dDlst_shadowControl_c::getSimpleTex();
    mShadowID = dComIfGd_setShadow(mShadowID,1,mpMorf->getModel(),&local_18,800.0f,40.0f,current.pos.y,mObjAcch.GetGroundH(),
    mObjAcch.m_gnd,&tevStr,0,1.0,tex);
    if(mShadowID != 0){
        if(field_0x708 != NULL){
            dComIfGd_addRealShadow(mShadowID,field_0x708);
        }
        dComIfGd_addRealShadow(mShadowID,field_0x710->getModel());
    }
}
const GXColor unused_red     = {0xFF,0x00,0x00,0x80};
const GXColor unused_blue    = {0x00,0x00,0xFF,0x80};
const GXColor unused_green   = {0x00,0xFF,0x00,0x80};
const GXColor unused_red_2   = {0xFF,0x00,0x00,0x80};
const GXColor unused_green_2 = {0x00,0xFF,0x00,0x80};
const GXColor unused_red_3   = {0xFF,0x00,0x00,0x80};
const GXColor unused_green_3 = {0x00,0xFF,0x00,0x80};
const GXColor unused_yellow  = {0xFF,0xFF,0x00,0x80};

/* 00007008-0000728C       .text _draw__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::_draw() {
    /* Nonmatching */

    J3DModel* model = field_0x710->getModel();
    J3DModelData* model_data = model->getModelData();
    J3DModel* morf_model = mpMorf->getModel();

    if ((field_0x867) || (field_0x86A)) {
        return 1;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR,&current.pos,&tevStr);
    g_env_light.setLightTevColorType(morf_model,&tevStr);
    switch(field_0x8A6){
        case 0:
            mpMorf->entryDL();
            break;
        case 1:
            mpMorf->entryDL((J3DMaterialTable*)dComIfG_getObjectIDRes("Ko",KO_BMT_KO02));
            break;
    }

    mBtpAnm.entry(model_data,mBtpFrame);
    field_0x710->entryDL();
    mBtpAnm.remove(model_data);
    g_env_light.setLightTevColorType(model,&tevStr);

    if(mBlnAnm){
        mBlnAnm->entryDL();
        g_env_light.setLightTevColorType(mBlnAnm->getModel(),&tevStr);
    }
    if(field_0x708){
        g_env_light.setLightTevColorType(field_0x708,&tevStr);
        mDoExt_modelEntryDL(field_0x708);
    }
    shadowDraw();
    switch(field_0x8A6){
        case 0:
            dSnap_RegistFig(0x52,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;
        case 1:
            dSnap_RegistFig(0x51,(fopAc_ac_c *)this,1.0,1.0,1.0);
            break;

    }
    if(l_HIO.children[field_0x8A6].hio_prm.field1C){
        cXyz somevec = field_0x7F4;
        somevec.y = eyePos.y;
        if(field_0x8A7){
            somevec = field_0x80C;
            somevec.y = eyePos.y;
        }else{
            somevec = field_0x80C;
            somevec.y = eyePos.y;
        }
        somevec = current.pos;
        somevec.y = eyePos.y;

    }
    return 1;
}

/* 0000728C-0000756C       .text _execute__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::_execute() {
    /* Nonmatching */
    if(field_0x86E == 0){
        field_0x7C4 = current.pos;
        field_0x7D0 = current.angle;
        field_0x86E = 1;
    }

    m_jnt.setParam(

        l_HIO.children[field_0x8A6].hio_prm.mMaxBackboneX,l_HIO.children[field_0x8A6].hio_prm.mMaxBackboneY,
        l_HIO.children[field_0x8A6].hio_prm.mMinBackboneX,l_HIO.children[field_0x8A6].hio_prm.mMinBackboneY,
        l_HIO.children[field_0x8A6].hio_prm.mMaxHeadX,l_HIO.children[field_0x8A6].hio_prm.mMaxHeadY,
        l_HIO.children[field_0x8A6].hio_prm.mMinHeadX,l_HIO.children[field_0x8A6].hio_prm.mMinHeadY,
        l_HIO.children[field_0x8A6].hio_prm.mMaxTurnStep
    );

    if(field_0x867 && demoActorID == 0){
        return TRUE;
    }
    field_0x869 = 0;
    field_0x867 = 0;
    partner_srch();
    checkOrder();
    if(!demo()){
        int iVar4 = -1;
        if(dComIfGp_event_runCheck() && !eventInfo.checkCommandTalk()){
            iVar4 = isEventEntry();   
        }
        if(iVar4 >= 0){
            event_proc(iVar4);
        }else{
            (this->*field_0x730)(0);
        }
        if(field_0x869 == 0){
            ko_nMove();
            fopAcM_posMoveF(this,mStts.GetCCMoveP());
        }
        cM3dGPla* pla = dComIfG_Bgsp()->GetTriPla(mObjAcch.m_gnd);
        if(pla != NULL){
            field_0x818 = pla->mNormal;
        }
        if(field_0x868 == 0){
            field_0x7D6 = current.angle;
            shape_angle = field_0x7D6;
        }
        if((current.pos-field_0x80C).absXZ() > 3000.0f){
            fopAcM_delete(this);
            return 1;
        }
    }
    eventOrder();
    setMtx(false);
    if(field_0x877 == 0){
        setCollision(30.0f,80.0f);
    }
    return TRUE;
}

/* 0000756C-000075F0       .text _delete__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::_delete() {
    /* Nonmatching */
    mDoExt_McaMorf *this_00;
    dComIfG_resDelete(&field_0x6C4,"Ko");
    if (heap != (JKRHeap *)0x0) {
        this_00 = mpMorf;
        if (this_00 != NULL) {
            mpMorf->stopZelAnime();
        }
        if (field_0x710 != NULL) {
            field_0x710->stopZelAnime();
        }
        if (mBlnAnm != NULL) {
            mBlnAnm->stopZelAnime();
        }
    }
    field_0x878.end();
    return 1;
}

/* 000075F0-00007610       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_actor) {
    /* Nonmatching */
    return ((daNpc_Ko1_c*)i_actor)->CreateHeap();
}


/* 00007610-00007730       .text _create__11daNpc_Ko1_cFv */
cPhs_State daNpc_Ko1_c::_create() {
    /* Nonmatching */
    static u32 a_size_tbl[] = {0x272E0,0x272E0};
    fopAcM_SetupActor(this,daNpc_Ko1_c);


    s32 resLoadResult = dComIfG_resLoad(&field_0x6C4,"Ko");
    

    if (resLoadResult != cPhs_COMPLEATE_e){
        return resLoadResult;
    }

   
    if(!charDecide(fopAcM_GetParam(this) & 0xFF)){
        return cPhs_ERROR_e;
    }  


    if (!fopAcM_entrySolidHeap(this,CheckCreateHeap,a_size_tbl[field_0x8A6])) {
        return cPhs_ERROR_e;
    }
    fopAcM_SetMtx(this,mpMorf->mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this,-50.0,-20.0,-50.0,50.0,120.0,50.0);
    if (!createInit()) {
        return cPhs_ERROR_e;
    }

    return resLoadResult;
}

/* 00007C2C-00007E9C       .text create_Anm__11daNpc_Ko1_cFv */
J3DModelData* daNpc_Ko1_c::create_Anm() {
    /* Nonmatching */

    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ko",KO_BDL_KO);
    a_mdl_dat->getJointName();
    JUT_ASSERT(4262, a_mdl_dat != NULL);

    mpMorf = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,(J3DAnmTransform*)dComIfG_getObjectIDRes("Ko",0x16),2,1.0,0,-1,1,NULL,0x80000,0x15021222);

    if(mpMorf == NULL){
        a_mdl_dat = NULL;
        return a_mdl_dat;
    }else if(mpMorf->mpModel == NULL){
        mpMorf = NULL;
        a_mdl_dat = NULL;
        return a_mdl_dat;
    }else{
        m_hed_jnt_num = a_mdl_dat->getJointName()->getIndex("head");
        JUT_ASSERT(4282,m_hed_jnt_num >= 0);
        m_bbone_jnt_num = a_mdl_dat->getJointName()->getIndex("backbone");
        JUT_ASSERT(4285,m_bbone_jnt_num >= 0);
        m_armR2_jnt_num = a_mdl_dat->getJointName()->getIndex("armR2");
        JUT_ASSERT(4288,m_armR2_jnt_num >= 0);
    }
    return a_mdl_dat;
}



/* 00007E9C-00008090       .text create_hed_Anm__11daNpc_Ko1_cFv */
J3DModelData* daNpc_Ko1_c::create_hed_Anm() {
    /* Nonmatching */
    static u32 a_hed_bdl_resID_tbl[] = {0x1C,0x1D};
    static u32 a_hed_bck_resID_tbl[] = {0x0A,0x25};
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ko",(int)a_hed_bdl_resID_tbl[field_0x8A6]);
    JUT_ASSERT(4312,a_mdl_dat != 0);
    field_0x710 = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,(J3DAnmTransform*)dComIfG_getObjectIDRes("Ko",(int)a_hed_bck_resID_tbl[field_0x8A6]),2,1.0,0,-1,1,NULL,0x80000,0x11020022);
    if(field_0x710 == NULL){
        a_mdl_dat = NULL;
        return a_mdl_dat;
    }else if(field_0x710->mpModel == NULL){
        field_0x710 = NULL;
        a_mdl_dat = NULL;
        return a_mdl_dat;
    }else{
        if(field_0x8A6 == 0){
        m_hed_2_jnt_num = a_mdl_dat->getJointName()->getIndex("head2");
        JUT_ASSERT(4333,m_hed_2_jnt_num >= 0);
        }
        return a_mdl_dat;
        

    }
}

/* 00008090-000082A4       .text create_bln_Anm__11daNpc_Ko1_cFv */
J3DModelData* daNpc_Ko1_c::create_bln_Anm() {
    /* Nonmatching */
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ko",KO_BDL_KO_BALLOON);
    JUT_ASSERT(4349,a_mdl_dat != 0);
    mBlnAnm = new mDoExt_McaMorf(a_mdl_dat,NULL,NULL,(J3DAnmTransform*)dComIfG_getObjectIDRes("Ko",1),2,1.0,0,-1,1,NULL,0x80000,0x11000022);
    if(mBlnAnm == NULL){
        a_mdl_dat = NULL;
        return a_mdl_dat;
    }else if(mBlnAnm->mpModel == NULL){
        mBlnAnm = NULL;
        a_mdl_dat = NULL;
        return a_mdl_dat;
    }else{

        m_bln_loc_jnt_num = a_mdl_dat->getJointName()->getIndex("balloon_loc");
        JUT_ASSERT(4369,m_bln_loc_jnt_num >= 0);

        m_bln_jnt_num = a_mdl_dat->getJointName()->getIndex("ko_balloon");
        JUT_ASSERT(4372,m_bln_jnt_num >= 0);
        }
        return a_mdl_dat;

}

/* 000082A4-00008380       .text create_itm_Mdl__11daNpc_Ko1_cFv */
bool daNpc_Ko1_c::create_itm_Mdl() {

    if(field_0x8A6 != 1){
        return 1;
    }
    J3DModelData* a_mdl_dat = (J3DModelData*)dComIfG_getObjectIDRes("Ko",KO_BDL_KOEDA);
    JUT_ASSERT(4390,a_mdl_dat != 0);
    field_0x708 = mDoExt_J3DModel__create(a_mdl_dat,0x80000,0x11000022);
    if(field_0x708 == NULL){
        return false;
    }
    return true;
}

/* 00008380-00008604       .text CreateHeap__11daNpc_Ko1_cFv */
BOOL daNpc_Ko1_c::CreateHeap() {
    /* Nonmatching */
    J3DModelData* anm = create_Anm();
    if(anm == NULL){
        return FALSE;
    }
    J3DModelData* hed_anm = create_hed_Anm();
    if(hed_anm == NULL){
        mpMorf = NULL;
        return FALSE;
    }
    u8 local_20[] = {0,0};
    field_0x89E = local_20[field_0x8A6];
    if(!iniTexPttrnAnm(false)){
        mpMorf = NULL;
        field_0x710 = NULL;
        return FALSE;
    }
    if(field_0x8A6 == NULL && !create_bln_Anm()){
        mpMorf = NULL;
        field_0x710 = NULL;
        return FALSE;
    }
    if(create_itm_Mdl()){


        if(field_0x8A6 == NULL){
            for(u16 i = 0; i < hed_anm->getJointNum(); i++){
                if(i == m_bln_loc_jnt_num){
                    mBlnAnm->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Bln);
                }
            }
            mBlnAnm->getModel()->setUserArea((u32)this);
            for(u16 i = 0; i < hed_anm->getJointNum(); i++){
                if(i == m_hed_2_jnt_num){
                    field_0x710->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Hed);

                }
            }
            field_0x710->getModel()->setUserArea((u32)this);
        }
            for(u16 i = 0; i < anm->getJointNum(); i++){
                if(i == m_hed_jnt_num || i == m_bbone_jnt_num){
                    mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack_Ko1);
                }              
            }
            mpMorf->getModel()->setUserArea((u32)this);
            mAcchCir.SetWall(30.0f,30.0f);
            mObjAcch.Set(&current.pos,&old.pos,this,1,&mAcchCir,&speed,NULL,NULL);
            return TRUE;
    }
        mpMorf = NULL;
        field_0x710 = NULL;
        mBlnAnm = NULL;
        return FALSE;

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
