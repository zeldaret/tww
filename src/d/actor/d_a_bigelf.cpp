/**
 * d_a_bigelf.cpp
 * NPC - Great Fairy
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bigelf.h"
#include "d/actor/d_a_ship.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_bigelf.h"

/* 00000078-0000016C       .text oct_delete__10daBigelf_cFv */
void daBigelf_c::oct_delete() {
    fopAc_ac_c* actOcto = fopAcM_SearchByID(this->mOctID);
    daShip_c* actShip = dComIfGp_getShipActor();
    if((this->mStateBits & 0b1000000) == 0b1000000){
        if(this->m3AC > 0){
            this->m3AC--;
            return;
        }

        if(actOcto != NULL){
            if(actShip != NULL){
                cXyz shipRelPos(0,0,1570), shipAbsPos;
                
                fpoAcM_absolutePos(actOcto, &shipRelPos, &shipAbsPos);
                shipAbsPos.y = actShip->current.pos.y;
                
                short shipAngle = cLib_targetAngleY(&this->current.pos, &shipAbsPos);
                shipAngle += 0x4000;
                
                actShip->initStartPos(&shipAbsPos, shipAngle);
            }
            fopAcM_delete(actOcto);
        }
        this->mStateBits &= ~(0b1000000);
    }
}

/* 0000016C-00000338       .text nodeCallBack__10daBigelf_cFP7J3DNode */
void daBigelf_c::nodeCallBack(J3DNode*) {
    /* Nonmatching */
}

/* 00000338-00000384       .text nodeCallBack_Bigelf__FP7J3DNodei */
static BOOL nodeCallBack_Bigelf(J3DNode*, int) {
    /* Nonmatching */
}

/* 00000384-00000438       .text lightInit__10daBigelf_cFP4cXyz */
void daBigelf_c::lightInit(cXyz*) {
    /* Nonmatching */
}

/* 00000438-00000470       .text lightEnd__10daBigelf_cFv */
void daBigelf_c::lightEnd() {
    /* Nonmatching */
}

/* 00000470-0000047C       .text lightProc__10daBigelf_cFv */
void daBigelf_c::lightProc() {
    /* Nonmatching */
}

/* 0000047C-00000488       .text darkInit__10daBigelf_cFv */
void daBigelf_c::darkInit() {
    this->bIsDark = 1;
}

/* 00000488-000004D0       .text darkEnd__10daBigelf_cFv */
void daBigelf_c::darkEnd() {
    this->bIsDark = 0;
    dKy_set_actcol_ratio(0.0f);
    dKy_set_bgcol_ratio(0.0f);
    dKy_set_vrboxcol_ratio(0.0f);
}

/* 000004D0-00000574       .text darkProc__10daBigelf_cFv */
void daBigelf_c::darkProc() {
    if(this->bIsDark){
        cLib_addCalc2(&this->m3A0,this->m3A4, 0.1f, 1.0f);
        dKy_set_actcol_ratio(this->m3A0 * 0.7f + 0.3f);
        float ratio = this->m3A0 * 0.6f + 0.4f;
        dKy_set_bgcol_ratio(ratio);
        dKy_set_vrboxcol_ratio(ratio);
    }
}

/* 00000574-00000588       .text demoInitFlDelete__10daBigelf_cFv */
void daBigelf_c::demoInitFlDelete() {
    /* Nonmatching */
}

/* 00000588-00000708       .text demoProcFlDelete__10daBigelf_cFv */
void daBigelf_c::demoProcFlDelete() {
    /* Nonmatching */
}

/* 00000708-000007E4       .text demoInitFlLink__10daBigelf_cFv */
void daBigelf_c::demoInitFlLink() {
    /* Nonmatching */
}

/* 000007E4-00000808       .text demoProcFlLink__10daBigelf_cFv */
void daBigelf_c::demoProcFlLink() {
    /* Nonmatching */
}

/* 00000808-000008F0       .text demoInitFlDmAf__10daBigelf_cFv */
void daBigelf_c::demoInitFlDmAf() {
    /* Nonmatching */
}

/* 000008F0-000009C0       .text demoProcFlDmAf__10daBigelf_cFv */
void daBigelf_c::demoProcFlDmAf() {
    /* Nonmatching */
}

/* 000009C0-00000A20       .text demoInitFlDmMd__10daBigelf_cFv */
void daBigelf_c::demoInitFlDmMd() {
    /* Nonmatching */
}

/* 00000A20-00000CEC       .text demoProcFlDmMd__10daBigelf_cFv */
void daBigelf_c::demoProcFlDmMd() {
    /* Nonmatching */
}

/* 00000CEC-00000CF0       .text demoInitFlDmBf__10daBigelf_cFv */
void daBigelf_c::demoInitFlDmBf() {
    /* Nonmatching */
}

/* 00000CF0-00000D7C       .text demoProcFlDmBf__10daBigelf_cFv */
void daBigelf_c::demoProcFlDmBf() {
    /* Nonmatching */
}

/* 00000D7C-00000D88       .text demoInitFlDemo__10daBigelf_cFv */
void daBigelf_c::demoInitFlDemo() {
    /* Nonmatching */
}

/* 00000D88-00000FB8       .text demoProcFlDemo__10daBigelf_cFv */
void daBigelf_c::demoProcFlDemo() {
    /* Nonmatching */
}

/* 00000FB8-0000115C       .text demoInitExit__10daBigelf_cFv */
void daBigelf_c::demoInitExit() {
    /* Nonmatching */
}

/* 0000115C-000012D4       .text demoProcExit__10daBigelf_cFv */
void daBigelf_c::demoProcExit() {
    /* Nonmatching */
}

/* 000012D4-000013C0       .text demoInitTalk__10daBigelf_cFv */
void daBigelf_c::demoInitTalk() {
    /* Nonmatching */
}

/* 000013C0-00001418       .text demoProcTalk__10daBigelf_cFv */
void daBigelf_c::demoProcTalk() {
    /* Nonmatching */
}

/* 00001418-0000163C       .text demoInitAppear__10daBigelf_cFv */
void daBigelf_c::demoInitAppear() {
    /* Nonmatching */
}

/* 0000163C-000017B4       .text demoProcAppear__10daBigelf_cFv */
void daBigelf_c::demoProcAppear() {
    /* Nonmatching */
}

/* 000017B4-00001848       .text demoInitFa1__10daBigelf_cFv */
void daBigelf_c::demoInitFa1() {
    /* Nonmatching */
}

/* 00001848-000018D4       .text demoProcFa1__10daBigelf_cFv */
void daBigelf_c::demoProcFa1() {
    /* Nonmatching */
}

/* 000018D4-00001948       .text demoInitWait__10daBigelf_cFv */
void daBigelf_c::demoInitWait() {
    /* Nonmatching */
}

/* 00001948-00001998       .text demoProcWait__10daBigelf_cFv */
void daBigelf_c::demoProcWait() {
    /* Nonmatching */
}

/* 00001998-00001A74       .text demoInitCom__10daBigelf_cFv */
void daBigelf_c::demoInitCom() {
    /* Nonmatching */
}

/* 00001A74-00001ACC       .text demoProcCom__10daBigelf_cFv */
void daBigelf_c::demoProcCom() {
    /* Nonmatching */
}

/* 00001ACC-00001B14       .text getNowEventAction__10daBigelf_cFv */
void daBigelf_c::getNowEventAction() {
    /* Nonmatching */
}

/* 00001B14-00001CCC       .text demoProc__10daBigelf_cFv */
void daBigelf_c::demoProc() {
    /* Nonmatching */
}

/* 00001CCC-00001CD8       .text getType__10daBigelf_cFv */
u8 daBigelf_c::getType() {
    /* Nonmatching */
}

/* 00001CD8-00001CE4       .text getSwbit__10daBigelf_cFv */
uint daBigelf_c::getSwbit() {
    /* Nonmatching */
}

/* 00001CE4-00001CF0       .text getSwbit2__10daBigelf_cFv */
void daBigelf_c::getSwbit2() {
    /* Nonmatching */
}

/* 00001CF0-00001D70       .text getEventFlag__10daBigelf_cFv */
void daBigelf_c::getEventFlag() {
    /* Nonmatching */
}

/* 00001D70-00001E20       .text makeFa1S__10daBigelf_cFv */
void daBigelf_c::makeFa1S() {
    /* Nonmatching */
}

/* 00001E20-00001EB4       .text makeFa1__10daBigelf_cFv */
void daBigelf_c::makeFa1() {
    /* Nonmatching */
}

/* 00001EB4-0000200C       .text setAnm__10daBigelf_cFSc */
void daBigelf_c::setAnm(signed char) {
    /* Nonmatching */
}

/* 0000200C-00002030       .text setAnmStatus__10daBigelf_cFv */
void daBigelf_c::setAnmStatus() {
    /* Nonmatching */
}

/* 00002030-000021A4       .text next_msgStatus__10daBigelf_cFPUl */
void daBigelf_c::next_msgStatus(unsigned long*) {
    /* Nonmatching */
}

/* 000021A4-000021D4       .text getMsg__10daBigelf_cFv */
void daBigelf_c::getMsg() {
    /* Nonmatching */
}

/* 000021D4-000021D8       .text msgPushButton__10daBigelf_cFv */
void daBigelf_c::msgPushButton() {
    /* Nonmatching */
}

/* 000021D8-000021DC       .text msgAnm__10daBigelf_cFUc */
void daBigelf_c::msgAnm(unsigned char) {
    /* Nonmatching */
}

/* 000021DC-000021F0       .text talkInit__10daBigelf_cFv */
void daBigelf_c::talkInit() {
    /* Nonmatching */
}

/* 000021F0-0000236C       .text talk__10daBigelf_cFv */
void daBigelf_c::talk() {
    /* Nonmatching */
}

/* 0000236C-00002534       .text init__10daBigelf_cFv */
BOOL daBigelf_c::init() {
    /* Nonmatching */
}

/* 00002534-000025A0       .text setAttention__10daBigelf_cFb */
void daBigelf_c::setAttention(bool) {
    /* Nonmatching */
}

/* 000025A0-000025F4       .text lookBack__10daBigelf_cFv */
void daBigelf_c::lookBack() {
    /* Nonmatching */
}

/* 000025F4-000026C0       .text hunt__10daBigelf_cFv */
void daBigelf_c::hunt() {
    /* Nonmatching */
}

/* 000026C0-00002730       .text oct_search__10daBigelf_cFv */
BOOL daBigelf_c::oct_search() {
    fopAc_ac_c* actOcto = fopAcM_searchFromName("Daiocta", 0, 0);
    if(actOcto != NULL){
        this->mOctID = fopAcM_GetID(actOcto);
        this->m3BD = 5;
        this->m3AC = 10;
    }

    return TRUE;
}

/* 00002730-000028E8       .text oct__10daBigelf_cFv */
BOOL daBigelf_c::oct() {
    fopAc_ac_c* actOcto = fopAcM_SearchByID(this->mOctID);
    if(actOcto != NULL){
        this->current.pos = actOcto->current.pos;
        this->current.pos.y = this->home.pos.y;
        this->attention_info.position = this->current.pos;
        this->eyePos = this->current.pos;
        this->current.angle.y = actOcto->shape_angle.y;

        cXyz p1(0,0,0), p2(-820, 0, 1340);
        s16 angleInc = cLib_targetAngleY(&p1, &p2);
        this->current.angle.y += angleInc;
        this->shape_angle.y = this->current.angle.y;
        this->mStateBits |= 0b100000;
    }
    else {
            this->mStateBits &= ~(0b100000);
    }

    if(dComIfGs_isSwitch(static_cast<u8>(this->getSwbit()), this->current.roomNo)){
        if(this->m3AC > 0){
            this->m3AC--;
        }
        else {
            fopAc_ac_c* actLink = dComIfGp_getLinkPlayer();
            this->m3BD = 1;
            this->mArrivalEvtID = dComIfGp_evmng_getEventIdx("BIGELF_ARRIVAL_2");
            fopAcM_orderChangeEventId(this, actLink, this->mArrivalEvtID, 0, 0xffff);
            this->m3AC = 30;
            this->mStateBits |= 0b1000000;
        }
    }

    return TRUE;
}

/* 000028E8-000029A0       .text ready0__10daBigelf_cFv */
void daBigelf_c::ready0() {
    /* Nonmatching */
}

/* 000029A0-00002A78       .text event0__10daBigelf_cFv */
void daBigelf_c::event0() {
    /* Nonmatching */
}

/* 00002A78-00002A80       .text dead__10daBigelf_cFv */
void daBigelf_c::dead() {
    /* Nonmatching */
}

/* 00002A80-00002C8C       .text wait_action__10daBigelf_cFPv */
void daBigelf_c::wait_action(void*) {
    /* Nonmatching */
}

/* 00002C8C-00002DB4       .text _draw__10daBigelf_cFv */
BOOL daBigelf_c::_draw() {
    J3DModel* bckModel = this->mpBckAnimator->getModel();
    J3DModelData* bckModelData = bckModel->getModelData();
    //J3DModel* flowerModel = this->mpFlowerModel;
    J3DModelData* flowerModelData = this->mpFlowerModel->getModelData();
    
    if((this->mStateBits & 0b10) == 0b10){
        return FALSE;
    }

    if((this->mStateBits & 0b10000) != 0b10000){
        dKy_getEnvlight().settingTevStruct(TEV_TYPE_ACTOR, fopAcM_GetPosition_p(this), &this->tevStr);
    }

    dKy_getEnvlight().setLightTevColorType(bckModel, &this->tevStr);
    dKy_getEnvlight().setLightTevColorType(this->mpFlowerModel, &this->tevStr);
    
    this->mBrkAnimator.entry(bckModelData);
    this->mBtkAnimator.entry(bckModelData);
    this->mpBckAnimator->entry();

    if((this->mStateBits & 0b1000) == 0b1000){
        mFlowerBrkAnimator.entry(flowerModelData);
        this->mpFlowerModel->setBaseTRMtx(bckModel->getAnmMtx(this->m_fl_jnt));
        mDoExt_modelUpdateDL(this->mpFlowerModel);
    }

    return TRUE;
}

/* 00002DB4-00002F5C       .text _execute__10daBigelf_cFv */
BOOL daBigelf_c::_execute() {
    this->m_jnt.setParam(0,0,0,0,4000,9000,-2000,-4000,0x1000);
    if((this->mStateBits & 0b10000) != 0b10000){
        this->m336 = this->mpBckAnimator->play(&this->eyePos, 0, 0);
        if(this->mpBckAnimator->getFrame() < this->m338 && this->m3BC != 3){
            this->m336 = 1;
        }
        this->m338 = this->mpBckAnimator->getFrame();
    }
    this->mStateBits &= ~(0b1000);

    (this->*mCurrentStateFunc)(NULL);

    this->shape_angle.y = this->current.angle.y;
    this->tevStr.mRoomNo = this->current.roomNo;
    
    J3DModel* bckModel = this->mpBckAnimator->getModel(); 
    mDoMtx_stack_c::transS(this->current.pos);
    mDoMtx_stack_c::YrotM(this->current.angle.y);
    bckModel->setBaseScale(this->scale);
    if((this->mStateBits & 0b10000) == 0b10000){
        mDoMtx_stack_c::transM(0, this->mHeightOffset, 0);
        mDoMtx_stack_c::scaleM(this->m3EC, this->m3F0, this->m3EC);
        mDoMtx_stack_c::transM(0, -this->mHeightOffset, 0);
    }

    bckModel->setBaseTRMtx(mDoMtx_stack_c::get());
    this->mpBckAnimator->calc();
    this->mBtkAnimator.play();

    return TRUE;
}

/* 00002F5C-00002FAC       .text _delete__10daBigelf_cFv */
BOOL daBigelf_c::_delete() {
    dComIfG_resDelete(&this->mPhaseProcReq, "bigelf");
    if(this->mpBckAnimator != NULL){
        this->mpBckAnimator->stopZelAnime();
    }

    return TRUE;
}

/* 00002FAC-00002FCC       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daBigelf_c*>(i_this)->CreateHeap();
}

/* 00002FCC-00003124       .text _create__10daBigelf_cFv */
cPhs_State daBigelf_c::_create() {

    fopAcM_SetupActor(this, daBigelf_c);
    cPhs_State ret = dComIfG_resLoad(&this->mPhaseProcReq, "bigelf");
    if(ret == cPhs_COMPLEATE_e){
        if(fopAcM_GetName(this) != PROC_BIGELF){
            return cPhs_ERROR_e;
        }

        this->m3F4 = 0;

        if(!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0xb7b0)){
            this->mpBckAnimator = NULL;
                return cPhs_ERROR_e;
            }
    
        fopAcM_SetMtx(this, this->mpBckAnimator->getModel()->getBaseTRMtx());

        if(init() == FALSE){
            this->mpBckAnimator = NULL;
            return cPhs_ERROR_e;
        }
    }

    return ret;
}

/* 00003224-00003808       .text CreateHeap__10daBigelf_cFv */
BOOL daBigelf_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("bigelf", BIGELF_BDL_DY));
    JUT_ASSERT(2004, modelData);

    this->mpBckAnimator = new mDoExt_McaMorf(
        modelData, 
        NULL, NULL,
        static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes("bigelf", BIGELF_BCK_WAIT01)),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x11000222);
    
    if(this->mpBckAnimator == NULL || this->mpBckAnimator->getModel() == 0)
        return FALSE;

    J3DAnmTevRegKey* pbrk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes("bigelf", BIGELF_BRK_DY_BODY));
    if(this->mBrkAnimator.init(modelData, pbrk, true, J3DFrameCtrl::EMode_NONE, 1, 0, -1, false, 0) == 0)
        return FALSE;

    J3DAnmTextureSRTKey* pbtk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes("bigelf", BIGELF_BTK_DY_BODY));
    if(this->mBtkAnimator.init(modelData, pbtk, true, J3DFrameCtrl::EMode_LOOP, 1, 0, -1, false, 0) == 0)
        return FALSE;

    J3DSkinDeform* pSkin = new J3DSkinDeform();
    if(pSkin == NULL)
        return FALSE;

    switch(this->mpBckAnimator->getModel()->setSkinDeform(pSkin, 1)){
        case 0:

            break;

        case 4:
            return FALSE;
        
        default:
            JUT_ASSERT(2065, 0);
    }

    J3DModel* bckModel = this->mpBckAnimator->getModel();
    mDoMtx_stack_c::transS(this->current.pos);
    mDoMtx_stack_c::YrotM(this->current.angle.y);
    bckModel->setBaseTRMtx(mDoMtx_stack_c::get());
    this->mpBckAnimator->calc();

    this->m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(2084, m_jnt.getHeadJntNum() >= 0);

    this->m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone"));
    JUT_ASSERT(2089, m_jnt.getBackboneJntNum() >= 0);

    this->m_fl_jnt = modelData->getJointName()->getIndex("handRB");
    JUT_ASSERT(2093, m_fl_jnt >= 0);

    for(u16 i_jnt = 0; i_jnt < modelData->getJointNum(); i_jnt++){
        if(i_jnt == this->m_jnt.mHeadJntNum || i_jnt == this->m_jnt.mBackboneJntNum || i_jnt == this->m_fl_jnt)
            this->mpBckAnimator->getModel()->getModelData()->getJointTree().getJointNodePointer(i_jnt)->setCallBack(nodeCallBack_Bigelf);
    }
    
    this->mpBckAnimator->getModel()->setUserArea((u32)this); // Unsafe casting because weird things here


    J3DModelData* flModelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("bigelf", BIGELF_BDL_DY_FL));
    JUT_ASSERT(2114, flModelData);

    this->mpFlowerModel = mDoExt_J3DModel__create(flModelData, 0x80000, 0x100000);
    if(this->mpFlowerModel == 0)
        return FALSE;

    pbrk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes("bigelf", BIGELF_BRK_DY_FL));
    if(this->mFlowerBrkAnimator.init(modelData, pbrk, true, J3DFrameCtrl::EMode_NONE, 1, 0, -1, false, 0) == 0)
        return FALSE;
 
    this->iBrkFrame = 0;
    switch(this->getType()){
        case 2:
        case 3:
            this->mBrkAnimator.setFrame(1);
            this->mFlowerBrkAnimator.setFrame(1);
            this->iBrkFrame = 1;
            break;
        case 4:
        case 5:
            this->mBrkAnimator.setFrame(2);
            this->mFlowerBrkAnimator.setFrame(2);
            this->iBrkFrame = 2;
            break;
        case 6:
            this->mBrkAnimator.setFrame(3);
            this->mFlowerBrkAnimator.setFrame(3);
            this->iBrkFrame = 3;
            break;
    }

    return TRUE;
}

/* 00003808-00003828       .text daBigelf_Create__FP10fopAc_ac_c */
static cPhs_State daBigelf_Create(fopAc_ac_c* i_this) {
    return ((daBigelf_c*)i_this)->_create();
}

/* 00003828-00003848       .text daBigelf_Delete__FP10daBigelf_c */
static BOOL daBigelf_Delete(daBigelf_c* i_this) {
    return ((daBigelf_c*)i_this)->_delete();
}

/* 00003848-00003868       .text daBigelf_Execute__FP10daBigelf_c */
static BOOL daBigelf_Execute(daBigelf_c* i_this) {
    return ((daBigelf_c*)i_this)->_execute();
}

/* 00003868-00003888       .text daBigelf_Draw__FP10daBigelf_c */
static BOOL daBigelf_Draw(daBigelf_c* i_this) {
    return ((daBigelf_c*)i_this)->_draw();
}

/* 00003888-00003890       .text daBigelf_IsDelete__FP10daBigelf_c */
static BOOL daBigelf_IsDelete(daBigelf_c*) {
    return TRUE;
}

static actor_method_class l_daBigelf_Method = {
    (process_method_func)daBigelf_Create,
    (process_method_func)daBigelf_Delete,
    (process_method_func)daBigelf_Execute,
    (process_method_func)daBigelf_IsDelete,
    (process_method_func)daBigelf_Draw,
};

actor_process_profile_definition g_profile_BIGELF = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BIGELF,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBigelf_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BIGELF,
    /* Actor SubMtd */ &l_daBigelf_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
