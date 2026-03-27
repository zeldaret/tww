/**
 * d_a_bigelf.cpp
 * NPC - Great Fairy
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bigelf.h"
#include "d/actor/d_a_npc_fa1.h"
#include "d/actor/d_a_ship.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_bigelf.h"

fpc_ProcID l_msgId;
msg_class* l_msg;

const u32 l_bck_ix_tbl[4] = {8,6,7,6};
const u16 pa_name_flower[] = {dPa_name::ID_SCENE_834F, dPa_name::ID_SCENE_8351, dPa_name::ID_SCENE_8353, dPa_name::ID_SCENE_8355};
const u16 pa_name_flower2[] = {dPa_name::ID_SCENE_8350, dPa_name::ID_SCENE_8352, dPa_name::ID_SCENE_8354, dPa_name::ID_SCENE_8356};

/* 00000078-0000016C       .text oct_delete__10daBigelf_cFv */
void daBigelf_c::oct_delete() {
    fopAc_ac_c* actOcto = fopAcM_SearchByID(this->mOctID);
    daShip_c* actShip = dComIfGp_getShipActor();
    if(chkFlag(BIGELF_STATE_UNK6)){
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
        this->clrFlag(BIGELF_STATE_UNK6);
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
void daBigelf_c::lightInit(cXyz* pPos) {
    this->mLightInfluence.mPos = *pPos;
    this->mLightInfluencePos = this->mLightInfluence.mPos;

    if(!this->mIsLightShining){
        this->mIsLightShining = true;
        
        this->mLightInfluence.mColor.r = 255;
        this->mLightInfluence.mColor.g = 255;
        this->mLightInfluence.mColor.b = 255;
        
        this->mLightInfluence.mPower = 0;
        this->mLightInfluence.mFluctuation = 0;
        this->mLightInfluencePos = this->mLightInfluence.mPos;
        
        this->mLightInfluenceColor.r = 255;
        this->mLightInfluenceColor.g = 255;
        this->mLightInfluenceColor.b = 255;

        this->mLightInfluencePower = 0;
        this->mLightInfluenceFluctuation = 0;
        dKy_plight_priority_set(&this->mLightInfluence);
    }
}

/* 00000438-00000470       .text lightEnd__10daBigelf_cFv */
void daBigelf_c::lightEnd() {
    if(this->mIsLightShining){
        this->mIsLightShining = false;
        dKy_plight_cut(&this->mLightInfluence);
    }
}

/* 00000470-0000047C       .text lightProc__10daBigelf_cFv */
void daBigelf_c::lightProc() {
    if(this->mIsLightShining){
        return;
    }
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
    this->m3C0 = 0;
    this->m3DC = -1;
}

/* 00000588-00000708       .text demoProcFlDelete__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlDelete() {
    this->m3C0++;
    if(this->m3C0 == 27){
        fopAc_ac_c* link_actor = dComIfGp_getLinkPlayer();
        dComIfGp_particle_set(pa_name_flower2[this->iBrkFrame], &link_actor->current.pos);
        this->m3A4 = 1.0f;
    }
    if(this->m3C0 >= 27){
        if(this->m3E4 != NULL) {
            if(this->m3DC > 10){
                this->m3DC -= 10;
                this->m3E4->setGlobalAlpha(this->m3DC);
            }
            else {
                this->m3DC = 0;
                this->m3E4->setGlobalAlpha(0);
                this->m3E4->becomeInvalidEmitter();
                this->m3E4 = NULL;
            }
        }
        else {
            this->lightEnd();
            dComIfGp_evmng_cutEnd(this->mStaffId);
            if(this->chkFlag(BIGELF_STATE_UNK0)){
                this->clrFlag(BIGELF_STATE_UNK0);
                if(this->getType() == 6){
                    dComIfGp_setItemMaxMagicCount(32);
                    dComIfGp_setItemMagicCount(32);
                }
            }
        }
    }
    return TRUE;
}

/* 00000708-000007E4       .text demoInitFlLink__10daBigelf_cFv */
void daBigelf_c::demoInitFlLink() {
    fopAc_ac_c* link_actor = dComIfGp_getLinkPlayer();
    cXyz relPos, absPos;
    relPos.set(0, 300, 400);
    fpoAcM_absolutePos(link_actor, &relPos, &absPos);
    this->m3E4 = dComIfGp_particle_set(pa_name_flower[this->iBrkFrame], &absPos, &this->shape_angle);
    this->lightInit(&absPos);
    this->mLightInfluence.mPower = 1000;
    this->demoInitWait();
}

/* 000007E4-00000808       .text demoProcFlLink__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlLink() {
    this->demoProcWait();
    return TRUE;
}

/* 00000808-000008F0       .text demoInitFlDmAf__10daBigelf_cFv */
void daBigelf_c::demoInitFlDmAf() {
    cXyz particle_pos = this->m3D0;
    particle_pos.y += 20.0f;
    this->m3E0 = dComIfGp_particle_set(pa_name_flower[this->iBrkFrame], &particle_pos, &this->shape_angle);
    mDoAud_seStart(JA_SE_OBJ_DY_HANAFUBUKI);

}

/* 000008F0-000009C0       .text demoProcFlDmAf__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlDmAf() {
    if(this->m336 != 0 || !this->chkFlag(BIGELF_STATE_UNK0)){
        dComIfGp_evmng_cutEnd(this->mStaffId);
        this->clrFlag(BIGELF_STATE_UNK0);
        if(this->m3E0 != NULL){
            this->m3E0->becomeInvalidEmitter();
            this->m3E0 = NULL;
        }
        return TRUE;
    }
    else {
        float time = this->mpBckAnimator->getFrame();
        if(time >= 116 && time <= 173) this->setFlag(BIGELF_STATE_UNK3);
        return TRUE;
    }
}

/* 000009C0-00000A20       .text demoInitFlDmMd__10daBigelf_cFv */
void daBigelf_c::demoInitFlDmMd() {
    this->darkInit();
    this->m3A0 = this->m3A4 = 1.0f;
    this->clrFlag(BIGELF_STATE_UNK7);
    this->setFlag(BIGELF_STATE_UNK9);
    this->setFlag(BIGELF_STATE_UNK10);
}

/* 00000A20-00000CEC       .text demoProcFlDmMd__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlDmMd() {
    f32 time = this->mpBckAnimator->getFrame();
    if(!chkFlag(BIGELF_STATE_UNK0)){
        dComIfGp_evmng_cutEnd(this->mStaffId);
        return TRUE;
    }

    if(time < 16){}
    else {
        if(time < 116){
            this->m3A4 = (116 - time) * 0.01f;
        }
        else {
            this->m3A4 = 0;
        }
    }

    if(!chkFlag(BIGELF_STATE_UNK7) && time >= 116){
        this->setFlag(BIGELF_STATE_UNK7);
        cXyz lightPos = this->m3D0;
        lightPos.x += JMASSin(this->shape_angle.y) * 60;
        lightPos.z += JMASCos(this->shape_angle.y) * 60;
        this->lightInit(&lightPos);
        this->mLightInfluence.mPower = 850.0f;
        fopAcM_seStart(this, JA_SE_OBJ_DY_FLOWER, 0);
    }

    if(this->chkFlag(BIGELF_STATE_UNK9) && time >= 126){
        this->clrFlag(BIGELF_STATE_UNK9);
        fopAcM_seStart(this, JA_SE_CV_DY_BREATH_IN, 0);
    }

    if(this->chkFlag(BIGELF_STATE_UNK10) && time >= 154){
        this->clrFlag(BIGELF_STATE_UNK10);
        fopAcM_seStart(this, JA_SE_CV_DY_BREATH_OUT, 0);
    }

    if(time >= 166){
        dComIfGp_evmng_cutEnd(this->mStaffId);
        this->clrFlag(BIGELF_STATE_UNK0);
    }

    if(time >= 116 && time <= 173){
        this->setFlag(BIGELF_STATE_UNK3);
    }

    return TRUE;
}

/* 00000CEC-00000CF0       .text demoInitFlDmBf__10daBigelf_cFv */
void daBigelf_c::demoInitFlDmBf() {
    return;
}

/* 00000CF0-00000D7C       .text demoProcFlDmBf__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlDmBf() {
    if(!this->chkFlag(BIGELF_STATE_UNK0)){
        dComIfGp_evmng_cutEnd(this->mStaffId);
        return TRUE;
    }
    else if(this->m336 != 0){
        this->setAnm(2);
        dComIfGp_evmng_cutEnd(this->mStaffId);
        this->clrFlag(BIGELF_STATE_UNK0);
    }

    return TRUE;
}

/* 00000D7C-00000D88       .text demoInitFlDemo__10daBigelf_cFv */
void daBigelf_c::demoInitFlDemo() {
    this->m3DC = 0;
}

/* 00000D88-00000FB8       .text demoProcFlDemo__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFlDemo() {
    if(this->m336 != 0){
        if(this->chkFlag(BIGELF_STATE_UNK0)){
            switch(this->m3BC){
                case 0:
                    this->setAnm(2);
                    break;
                case 2:
                    this->clrFlag(BIGELF_STATE_UNK0);
                    dComIfGp_evmng_cutEnd(this->mStaffId);
                    break;
            }
        }
        else {
            dComIfGp_evmng_cutEnd(this->mStaffId);
        }
    }

    if(this->m3BC == 2){
        float time = this->mpBckAnimator->getFrame();
        if(time >= 116.f && time <= 173.f)
            this->setFlag(BIGELF_STATE_UNK3);
        
        cXyz particle_pos;
        switch(this->m3DC){
            case 0:
                particle_pos = this->m3D0;
                particle_pos.y += 20.f;
                if(time >= 167.f){
                    this->m3DC++;
                    this->m3E0 = dComIfGp_particle_set(pa_name_flower[this->iBrkFrame], &particle_pos, &this->shape_angle);
                    mDoAud_seStart(JA_SE_OBJ_DY_HANAFUBUKI);
                }
            break;
            
            case 1:
                if(!this->chkFlag(BIGELF_STATE_UNK0) && this->m3E0 != NULL){
                    this->m3DC++;
                    this->m3E0->becomeInvalidEmitter();
                    this->m3E0 = NULL;
                }
                break;
        }
    }

    return TRUE;
}

/* 00000FB8-0000115C       .text demoInitExit__10daBigelf_cFv */
void daBigelf_c::demoInitExit() {
    if(this->m3CC != NULL){
        this->m3CC->becomeInvalidEmitter();
        this->m3CC = NULL;
    }

    this->setFlag(BIGELF_STATE_UNK4);
    this->m3C0 = 0;
    this->mHeightOffset = 250.f;
    this->m3EC = 1.f;
    this->m3F0 = 1.f;

    cXyz pos, scale;
    scale.set(1,1,1);
    pos = current.pos;
    pos.y += this->mHeightOffset;
    dComIfGp_particle_set(dPa_name::ID_COMMON_LIGHT_EXPLOSION, &pos, NULL, &scale);
    this->tevStr.mFogColor.b = 0xFF;
    this->tevStr.mFogColor.g = 0xFF;
    this->tevStr.mFogColor.r = 0xFF;
    this->tevStr.mFogStartZ = 0;
    this->tevStr.mFogEndZ = 2000.f;
    
    fopAcM_seStart(this, JA_SE_CM_DY_GO_AWAY, 0);
    fopAcM_seStart(this, JA_SE_CV_DY_GO_AWAY, 0);
    this->darkEnd();
}

/* 0000115C-000012D4       .text demoProcExit__10daBigelf_cFv */
BOOL daBigelf_c::demoProcExit() {
    this->m3C0++;
    cLib_addCalc2(&this->tevStr.mFogEndZ, 10, 1, 80);
    if(this->m3C0 < 70){
        cLib_addCalc0(&this->m3EC, 0.1, 0.01);
        cLib_addCalc0(&this->m3F0, 0.1, 0.01);
        return TRUE;
    }

    if(this->m3C0 == 70){
        fopAcM_seStart(this, JA_SE_CM_L_ARROW_PASS_AWAY, 0);
        if(this->getType() == 6)
            mDoAud_bgmStop(45);
    }

    cLib_addCalc2(&this->m3F0, 5, 0.1, 1);
    cLib_addCalc0(&this->m3EC, 0.1, 0.05);
    if(this->m3C0 >= 90){
        dComIfGp_evmng_cutEnd(this->mStaffId);
        this->setFlag(BIGELF_STATE_UNK1);
        this->clrFlag(BIGELF_STATE_UNK4);
        if(this->getType() != 6)
            this->makeFa1S();
    }

    return TRUE;
}

/* 000012D4-000013C0       .text demoInitTalk__10daBigelf_cFv */
void daBigelf_c::demoInitTalk() {
    this->talkInit();
    int* a_intP = dComIfGp_evmng_getMyIntegerP(this->mStaffId, "MsgNo");
    JUT_ASSERT(0x325, a_intP);
    this->mCurrentMessageId = *a_intP;
    if(this->mCurrentMessageId == 0x2EEA){
        dComIfGp_setItemLifeCount(dComIfGs_getMaxLife());
        dComIfGp_setItemMagicCount(dComIfGs_getMaxMagic());
    }

}

/* 000013C0-00001418       .text demoProcTalk__10daBigelf_cFv */
BOOL daBigelf_c::demoProcTalk() {
    u16 talk_status = this->talk();
    if(talk_status == fopMsgStts_BOX_CLOSED_e || talk_status == 0xFE){ // What is 0xFE ?
        dComIfGp_evmng_cutEnd(this->mStaffId);
    }

    return TRUE;
}

/* 00001418-0000163C       .text demoInitAppear__10daBigelf_cFv */
void daBigelf_c::demoInitAppear() {
    static u16 p_name0[] = {dPa_name::ID_SCENE_8347, dPa_name::ID_SCENE_8349, dPa_name::ID_SCENE_834B, dPa_name::ID_SCENE_834D};
    static u16 p_name1[] = {dPa_name::ID_SCENE_8348, dPa_name::ID_SCENE_834A, dPa_name::ID_SCENE_834C, dPa_name::ID_SCENE_834E};

    fopAc_ac_c* pFairyActor = fopAcM_SearchByID(this->mFairyActorID);
    if(pFairyActor != NULL){
        dComIfGp_event_setTalkPartner(this);
        fopAcM_delete(pFairyActor);
    }

    cXyz particlePos;
    particlePos = this->current.pos;
    particlePos.y += 70.f;

    dComIfGp_getVibration().StartShock(5, -33, cXyz(0,1,0));
    dComIfGp_particle_set(p_name0[this->iBrkFrame], &particlePos, NULL, &this->scale);
    dComIfGp_particle_set(p_name1[this->iBrkFrame], &particlePos, NULL, &this->scale);

    if(this->getType() == 6)
        this->iAttCnt = 15;
    this->m3DC = 15;
    this->mBlend = 0.5;
    
    if(this->getType() == 6){
        fopAcM_seStart(this, JA_SE_CM_DY_ENTER_DO, 0);
        mDoAud_bgmStart(0x80000053);
    }

    this->setFlag(BIGELF_STATE_UNK8);
}

/* 0000163C-000017B4       .text demoProcAppear__10daBigelf_cFv */
BOOL daBigelf_c::demoProcAppear() {
    if(this->m3DC != 0){
        this->m3DC--;
        if(this->m3DC == 0){
            this->clrFlag(BIGELF_STATE_UNK1);
            this->setAnm(1);
            if(this->m3CC == NULL)
                this->m3CC = dComIfGp_particle_set(dPa_name::ID_SCENE_8346, &this->current.pos);
        }

        return TRUE;
    }
    
    if (this->chkFlag(BIGELF_STATE_UNK8) && this->mpBckAnimator->getFrame() >= 87.f){
        this->clrFlag(BIGELF_STATE_UNK8);
        fopAcM_seStart(this, JA_SE_CV_DY_ENTER, 0);
    }

    if(this->m336 != 0){
        this->setAnm(0);
        dComIfGp_evmng_cutEnd(this->mStaffId);
    }

    this->scale.set(this->scale.x, this->scale.x, this->scale.x);

    return TRUE;
}

/* 000017B4-00001848       .text demoInitFa1__10daBigelf_cFv */
void daBigelf_c::demoInitFa1() {
    daNpc_Fa1_c* paFairy = static_cast<daNpc_Fa1_c*>(fopAcM_SearchByID(this->mFairyActorID));
    if(paFairy != NULL){
        paFairy->init_bigelf_change();
        fopAcM_seStart(this, JA_SE_CM_DY_ENTER, 0);
    }
}

/* 00001848-000018D4       .text demoProcFa1__10daBigelf_cFv */
BOOL daBigelf_c::demoProcFa1() {
    fopAc_ac_c* paFairy = fopAcM_SearchByID(this->mFairyActorID);
    if(paFairy != NULL)
        cLib_addCalc2(&paFairy->current.pos.y, this->current.pos.y + 70.f, 0.2f, 100.f);

    dComIfGp_evmng_cutEnd(this->mStaffId);

    return TRUE;
}

/* 000018D4-00001948       .text demoInitWait__10daBigelf_cFv */
void daBigelf_c::demoInitWait() {
    int* pTimer = dComIfGp_evmng_getMyIntegerP(this->mStaffId, "Timer");
    if(pTimer != NULL)
        this->m3C0 = *pTimer;
    else 
        this->m3C0 = 0;

    this->setAnm(0);
}

/* 00001948-00001998       .text demoProcWait__10daBigelf_cFv */
BOOL daBigelf_c::demoProcWait() {
    if(this->m3C0 > 0)
        this->m3C0--;
    else 
        dComIfGp_evmng_cutEnd(this->mStaffId);

    return FALSE;
}

/* 00001998-00001A74       .text demoInitCom__10daBigelf_cFv */
void daBigelf_c::demoInitCom() {
    this->setFlag(BIGELF_STATE_UNK0);

    if(dComIfGp_evmng_getMyIntegerP(this->mStaffId, "Ship") != NULL){

        daShip_c* pShip = dComIfGp_getShipActor();
        cXyz absShipPos, relShipPos;

        if(pShip != NULL){       
            relShipPos.set(0,0,800);
            fpoAcM_absolutePos(this, &relShipPos, &absShipPos);
            absShipPos.y = pShip->current.pos.y;
            s16 shipAngle = cLib_targetAngleY(&this->current.pos, &absShipPos);
            shipAngle += 0x4000;
            pShip->initStartPos(&absShipPos, shipAngle);
        }
        this->setFlag(BIGELF_STATE_UNK5);
    }
}

/* 00001A74-00001ACC       .text demoProcCom__10daBigelf_cFv */
void daBigelf_c::demoProcCom() {
    if(this->getType() != 6)
        dKy_custom_colset(4, 0, this->mBlend);

    this->lightProc();
    this->darkProc();
}

/* 00001ACC-00001B14       .text getNowEventAction__10daBigelf_cFv */
int daBigelf_c::getNowEventAction() {
    static char* action_table [11] = {"WAIT", "FA1", "APPEAR", "TALK", "EXIT", "FL_DEMO", "FL_LINK", "FL_DELETE", "FL_DM_BF", "FL_DM_MD", "FL_DM_AF"};
    return dComIfGp_evmng_getMyActIdx(this->mStaffId, action_table, ARRAY_SSIZE(action_table), FALSE, 1);
}

/* 00001B14-00001CCC       .text demoProc__10daBigelf_cFv */
void daBigelf_c::demoProc() {
    int iEvent = this->getNowEventAction();

    if(dComIfGp_evmng_getIsAddvance(this->mStaffId)){
        demoInitCom();
        switch(iEvent) {
            case 0:
                demoInitWait();
                break;
            case 1:
                demoInitFa1();
                break;
            case 2:
                demoInitAppear();
                break;
            case 3:
                demoInitTalk();
                break;
            case 4:
                demoInitExit();
                break;
            case 5:
                demoInitFlDemo();
                break;
            case 6:
                demoInitFlLink();
                break;
            case 7:
                demoInitFlDelete();
                break;
            case 8:
                demoInitFlDmBf();
                break;
            case 9:
                demoInitFlDmMd();
                break;
            case 10:
                demoInitFlDmAf();
                break;
            }
    }
    switch(iEvent){
    case 0:
        demoProcWait();
        break;
    case 1:
        demoProcFa1();
        break;
    case 2:
        demoProcAppear();
        break;
    case 3:
        demoProcTalk();
        break;
    case 4:
        demoProcExit();
        break;
    case 5:
        demoProcFlDemo();
        break;
    case 6:
        demoProcFlLink();
        break;
    case 7:
        demoProcFlDelete();
        break;
    case 8:
        demoProcFlDmBf();
        break;
    case 9:
        demoProcFlDmMd();
        break;
    case 10:
        demoProcFlDmAf();
        break;
    default:
        dComIfGp_evmng_cutEnd(this->mStaffId);
        break;
    }

    demoProcCom();
}

/* 00001CCC-00001CD8       .text getType__10daBigelf_cFv */
u8 daBigelf_c::getType() {
    return fopAcM_GetParam(this);
}

/* 00001CD8-00001CE4       .text getSwbit__10daBigelf_cFv */
u8 daBigelf_c::getSwbit() {
    return fopAcM_GetParam(this) >> 0x8;
}

/* 00001CE4-00001CF0       .text getSwbit2__10daBigelf_cFv */
u8 daBigelf_c::getSwbit2() {
    return fopAcM_GetParam(this) >> 0x10;
}

/* 00001CF0-00001D70       .text getEventFlag__10daBigelf_cFv */
u16 daBigelf_c::getEventFlag() {
    // Type to event (dSv_event_flag_c)
    switch(this->getType()){
        case 0:
            return dSv_event_flag_c::UNK_3020;
        case 1:
            return dSv_event_flag_c::UNK_3010;
        case 2:
            return dSv_event_flag_c::UNK_3008;
        case 3:
            return dSv_event_flag_c::UNK_3004;
        case 4:
            return dSv_event_flag_c::UNK_3002;
        case 5:
            return dSv_event_flag_c::UNK_3001;
        case 6:
            return dSv_event_flag_c::UNK_3180;
        default:
            return 0;
    }
}

/* 00001D70-00001E20       .text makeFa1S__10daBigelf_cFv */
void daBigelf_c::makeFa1S() {
    cXyz pos = this->current.pos;
    csXyz angle;
    angle.x = this->current.angle.x;
    angle.y = this->current.angle.y;
    angle.z = this->current.angle.z;
    pos.y += this->mHeightOffset;
    for(int i = 0; i < 10; i++, angle.y += 10000){
        fopAcM_create(PROC_NPC_FA1, 4, &pos, fopAcM_GetRoomNo(this), &angle);
    }

}

/* 00001E20-00001EB4       .text makeFa1__10daBigelf_cFv */
void daBigelf_c::makeFa1() {
    cXyz pos = this->current.pos;
    csXyz angle;
    angle.x = this->current.angle.x;
    angle.y = this->current.angle.y;
    angle.z = this->current.angle.z;
    pos.y += 100.0f;
    this->mFairyActorID = fopAcM_create(PROC_NPC_FA1, 6, &pos, fopAcM_GetRoomNo(this), &angle);
}

/* 00001EB4-0000200C       .text setAnm__10daBigelf_cFSc */
void daBigelf_c::setAnm(s8 anmIdx) {
    float morf = 8.0f;
    int loopMode = -1;
    float speed = 1.0f, startFrame = 0.0f;
    float duration = -1.0f;

    switch(anmIdx){
        case 1:
        case 2:
            morf = 0.0f;
            break;
        case 3:
            loopMode = 3;
            startFrame = 0.0f;
            speed = duration;
            duration = 100.0f;
            break;
    }

    switch(this->m3BC){
        case 1:
            morf = 0.0f;
    }
    
    if(anmIdx != this->m3BC && anmIdx != -1){
        this->m3BC = anmIdx;
        this->m338 = 0;
        this->m336 = 0;
        J3DAnmTransform* pAnimRes = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("bigelf", l_bck_ix_tbl[this->m3BC]));
        this->mpBckAnimator->setAnm(pAnimRes, loopMode, morf, speed, startFrame, duration, NULL);
    }
}

/* 0000200C-00002030       .text setAnmStatus__10daBigelf_cFv */
void daBigelf_c::setAnmStatus() {
    this->setAnm(0);
}

/* 00002030-000021A4       .text next_msgStatus__10daBigelf_cFPUl */
fopMsg_MessageStatus_e daBigelf_c::next_msgStatus(u32* pMsgIdx) {
    fopMsg_MessageStatus_e ret = fopMsgStts_MSG_CONTINUES_e;
    switch(*pMsgIdx){
        case 0x2EE8:
            (*pMsgIdx)++;
            switch(getType()){
                case 0:
                case 1:
                    if(dComIfGs_getWalletSize() == 0){
                        this->mGivenItem = dItem_MAX_RUPEE_UP1_e;
                    }
                    else {
                        this->mGivenItem = dItem_MAX_RUPEE_UP2_e;
                    }
                    break;
                case 2:
                case 3:
                    if(dComIfGs_getBombMax() <= 30){
                        this->mGivenItem = dItem_MAX_BOMB_UP1_e;
                    }
                    else {
                        this->mGivenItem = dItem_MAX_BOMB_UP2_e;
                    }
                    break;
                case 4:
                case 5:
                    if(dComIfGs_getArrowMax() <= 30){
                        this->mGivenItem = dItem_MAX_ARROW_UP1_e;
                    }
                    else {
                        this->mGivenItem = dItem_MAX_ARROW_UP2_e;
                    }
                    break;
                default:
                    this->mGivenItem = dItem_RED_RUPEE_e;
                    break;
            }
            dComIfGp_event_setGtItm(this->mGivenItem);
            break;
        
        case 0x2EEB:
        case 0x2EEC:
            (*pMsgIdx)++;
            break;
        
        case 0x2EEF:
        case 0x2EF0:
            (*pMsgIdx)++;
            break;
        
        case 0x2EF1:
            *pMsgIdx = 0x2EEE;
            break;
        
        default:
            ret = fopMsgStts_MSG_ENDS_e;
            break;
    }

    return ret;
}

/* 000021A4-000021D4       .text getMsg__10daBigelf_cFv */
int daBigelf_c::getMsg() {
    if(this->mCurrentMessageId == 0x2eee && dComIfGs_getItem(dInvSlot_BOW_e) == dItem_BOW_e){
        this->mCurrentMessageId = 0x2eef;
    }

    return this->mCurrentMessageId;
}

/* 000021D4-000021D8       .text msgPushButton__10daBigelf_cFv */
void daBigelf_c::msgPushButton() {
    return;
}

/* 000021D8-000021DC       .text msgAnm__10daBigelf_cFUc */
void daBigelf_c::msgAnm(unsigned char) {
    return;
}

/* 000021DC-000021F0       .text talkInit__10daBigelf_cFv */
void daBigelf_c::talkInit() {
    this->m3F7 = 0;
    this->m344 = -1;
}

/* 000021F0-0000236C       .text talk__10daBigelf_cFv */
u16 daBigelf_c::talk() {
    u16 ret = 0xff;

    if(this->m3F7 == 0){
        l_msgId = -1;
        this->mMsgIdx = getMsg();
        this->m3F7 = 1;
    }
    else if(this->m3F7 != -1){
        if(l_msgId == -1){
            l_msgId = fopMsgM_messageSet(this->mMsgIdx, this);
        }
        else {
            if(!chkFlag(BIGELF_STATE_UNK2)){
                this->msgAnm(dComIfGp_getMesgAnimeAttrInfo());
            }
            
            switch(this->m3F7){
                case 1:
                    l_msg = fopMsgM_SearchByID(l_msgId);
                    if(l_msg != NULL)
                        this->m3F7 = 2;
                    break;
                
                case 2:
                    ret = l_msg->mStatus;
                    if(ret == fopMsgStts_MSG_DISPLAYED_e){
                            this->msgPushButton();
                            l_msg->mStatus = this->next_msgStatus(&this->mMsgIdx);
                            if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e)
                                fopMsgM_messageSet(this->mMsgIdx);
                    }
                    else if(ret == fopMsgStts_BOX_CLOSED_e){
                        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                        this->m3F7 = -1;
                    }
                    break;
            }
        }
    }

    return ret;
}

/* 0000236C-00002534       .text init__10daBigelf_cFv */
BOOL daBigelf_c::init() {
    switch(this->m3F4){
        case 0:
        ActionFunc pActWait = &daBigelf_c::wait_action;
        if(this->mCurrentStateFunc != pActWait){
            if(this->mCurrentStateFunc != NULL){
                this->m3F6 = -1;
                (this->*mCurrentStateFunc)(NULL);
            }
            this->mCurrentStateFunc = pActWait;
            this->m3F6 = 0;
            (this->*mCurrentStateFunc)(NULL);
        }
    }

    this->current.pos.y = this->home.pos.y + 30;
    this->mCurrentPos = this->current.pos;
    this->mCurrentPos.y += 100.0f;
    this->eyePos = this->mUnkPos = this->mCurrentPos;
    this->attention_info.position.set(this->mCurrentPos.x, this->mCurrentPos.y + 50, this->mCurrentPos.z);
    this->mFairyActorID = -1;
    
    if(getType() != 6){
        if(dComIfGs_isEventBit(getEventFlag()))
            makeFa1S();
        else
            makeFa1();
    }
    this->setFlag(BIGELF_STATE_UNK1);
    return TRUE;
}

/* 00002534-000025A0       .text setAttention__10daBigelf_cFb */
void daBigelf_c::setAttention(bool active) {
    if(this->iAttCnt > 0){
        this->iAttCnt--;
        return;
    }

    if(!active && this->m337 >= 2){
        return;
    }
    
    this->eyePos.set(this->mUnkPos.x, this->mUnkPos.y, this->mUnkPos.z);
    this->attention_info.position.set(this->mCurrentPos.x, this->mCurrentPos.y + 50, this->mCurrentPos.z);
}

/* 000025A0-000025F4       .text lookBack__10daBigelf_cFv */
void daBigelf_c::lookBack() {
    fopAc_ac_c* pLink = dComIfGp_getLinkPlayer();
    if(!chkFlag(BIGELF_STATE_UNK5)){
        this->current.angle.y = fopAcM_searchActorAngleY(this, pLink);
        this->shape_angle.y = this->current.angle.y;
    }
}

/* 000025F4-000026C0       .text hunt__10daBigelf_cFv */
bool daBigelf_c::hunt() {
    fopAc_ac_c* pAcFairy = fopAcM_SearchByID(this->mFairyActorID);
    fopAc_ac_c* pLink = dComIfGp_getLinkPlayer();
    if(pAcFairy == NULL){
        this->m3BD = 3;
        return false;
    }
    else {
        if(fopAcM_searchActorDistanceXZ(this, pLink) < 900.0f){
            this->m3BD = 1;
            this->mArrivalEvtID = dComIfGp_evmng_getEventIdx("BIGELF_ARRIVAL");
            fopAcM_orderOtherEventId(this, this->mArrivalEvtID);
        }
        return true;
    }
}

/* 000026C0-00002730       .text oct_search__10daBigelf_cFv */
bool daBigelf_c::oct_search() {
    fopAc_ac_c* actOcto = fopAcM_searchFromName("Daiocta", 0, 0);
    if(actOcto != NULL){
        this->mOctID = fopAcM_GetID(actOcto);
        this->m3BD = 5;
        this->m3AC = 10;
    }

    return true;
}

/* 00002730-000028E8       .text oct__10daBigelf_cFv */
bool daBigelf_c::oct() {
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
        this->setFlag(BIGELF_STATE_UNK5);
    }
    else {
            this->clrFlag(BIGELF_STATE_UNK5);
    }

    if(dComIfGs_isSwitch(getSwbit(), fopAcM_GetRoomNo(this))){
        if(this->m3AC > 0){
            this->m3AC--;
        }
        else {
            fopAc_ac_c* actLink = dComIfGp_getLinkPlayer();
            this->m3BD = 1;
            this->mArrivalEvtID = dComIfGp_evmng_getEventIdx("BIGELF_ARRIVAL_2");
            fopAcM_orderChangeEventId(this, actLink, this->mArrivalEvtID, 0, 0xffff);
            this->m3AC = 30;
            this->setFlag(BIGELF_STATE_UNK6);
        }
    }

    return true;
}

/* 000028E8-000029A0       .text ready0__10daBigelf_cFv */
bool daBigelf_c::ready0() {
    fopAcM_SearchByID(this->mFairyActorID);
    if(this->eventInfo.checkCommandDemoAccrpt()){
        this->m3BD = 2;
        this->mStaffId = dComIfGp_evmng_getMyStaffId("BigElf");
        this->mBlend = 1.0f;
        demoProc();
    }
    else {
        fopAcM_orderOtherEventId(this, this->mArrivalEvtID);
    }

    return true;
}

/* 000029A0-00002A78       .text event0__10daBigelf_cFv */
bool daBigelf_c::event0() {
    if(dComIfGp_evmng_endCheck(this->mArrivalEvtID)){
        dComIfGs_onEventBit(getEventFlag());
        this->m3BD = 3;
        dComIfGp_event_onEventFlag(8);
        if(getType() == 6 && getSwbit2() != 0xff){
            dComIfGs_onSwitch(getSwbit2(), fopAcM_GetRoomNo(this));
        }
    }
    else {
        demoProc();
    }

    return true;
}

/* 00002A78-00002A80       .text dead__10daBigelf_cFv */
bool daBigelf_c::dead() {
    return true;
}

/* 00002A80-00002C8C       .text wait_action__10daBigelf_cFPv */
BOOL daBigelf_c::wait_action(void*) {
    if(this->m3F6 == 0){
        if(dComIfGs_isEventBit(getEventFlag())){
            this->m3BD = 3;
        }
        else {
            if(getType() == 6){
                if(dComIfGs_isSwitch(getSwbit(), fopAcM_GetRoomNo(this))){
                    if(getSwbit2() != 0xff){
                        dComIfGs_onSwitch(getSwbit2(), fopAcM_GetRoomNo(this));
                    }
                    this->m3BD = 3;
                }
                else {
                    this->m3BD = 4;
                }
            }
            else {
                this->m3BD = 0;
            }
        }
        this->setAnmStatus();
        this->m3F6++;
    }
    else if(this->m3F6 != -1) {
        bool bAttention;
        switch(this->m3BD){
            case 0:
                bAttention = hunt();
                break;
            case 1:
                bAttention = ready0();
                break;
            case 2:
                bAttention = event0();
                break;
            case 3:
                bAttention = dead();
                break;
            case 4:
                bAttention = oct_search();
                break;
            case 5:
                bAttention = oct();
                break;
            default:
                bAttention = false;
        }
        this->lookBack();
        this->setAttention(bAttention);
        if(this->chkFlag(BIGELF_STATE_UNK1)){
            this->attention_info.position = this->current.pos;
            this->eyePos = this->current.pos;
        }
        this->oct_delete();
    }

    return TRUE;
}

/* 00002C8C-00002DB4       .text _draw__10daBigelf_cFv */
BOOL daBigelf_c::_draw() {
    J3DModel* bckModel = this->mpBckAnimator->getModel();
    J3DModelData* bckModelData = bckModel->getModelData();
    //J3DModel* flowerModel = this->mpFlowerModel;
    J3DModelData* flowerModelData = this->mpFlowerModel->getModelData();
    
    if(this->chkFlag(BIGELF_STATE_UNK1)){
        return FALSE;
    }

    if(this->chkFlag(BIGELF_STATE_UNK4)){
        dKy_getEnvlight().settingTevStruct(TEV_TYPE_ACTOR, fopAcM_GetPosition_p(this), &this->tevStr);
    }

    dKy_getEnvlight().setLightTevColorType(bckModel, &this->tevStr);
    dKy_getEnvlight().setLightTevColorType(this->mpFlowerModel, &this->tevStr);
    
    this->mBrkAnimator.entry(bckModelData);
    this->mBtkAnimator.entry(bckModelData);
    this->mpBckAnimator->entry();

    if(this->chkFlag(BIGELF_STATE_UNK3)){
        mFlowerBrkAnimator.entry(flowerModelData);
        this->mpFlowerModel->setBaseTRMtx(bckModel->getAnmMtx(this->m_fl_jnt));
        mDoExt_modelUpdateDL(this->mpFlowerModel);
    }

    return TRUE;
}

/* 00002DB4-00002F5C       .text _execute__10daBigelf_cFv */
BOOL daBigelf_c::_execute() {
    this->m_jnt.setParam(0,0,0,0,4000,9000,-2000,-4000,0x1000);
    if(!this->chkFlag(BIGELF_STATE_UNK4)){
        this->m336 = this->mpBckAnimator->play(&this->eyePos, 0, 0);
        if(this->mpBckAnimator->getFrame() < this->m338 && this->m3BC != 3){
            this->m336 = 1;
        }
        this->m338 = this->mpBckAnimator->getFrame();
    }
    this->clrFlag(BIGELF_STATE_UNK3);

    (this->*mCurrentStateFunc)(NULL);

    this->shape_angle.y = this->current.angle.y;
    this->tevStr.mRoomNo = this->current.roomNo;
    
    J3DModel* bckModel = this->mpBckAnimator->getModel(); 
    mDoMtx_stack_c::transS(this->current.pos);
    mDoMtx_stack_c::YrotM(this->current.angle.y);
    bckModel->setBaseScale(this->scale);
    if(this->chkFlag(BIGELF_STATE_UNK4)){
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
