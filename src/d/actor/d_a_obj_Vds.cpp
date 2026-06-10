/**
 * d_a_obj_Vds.cpp
 * Object - Earth Temple - Face statue (lights up when eyes are hit with Mirror Shield)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Vds.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_a_obj.h"
#include "d/res/res_vds.h"

const char daObjVds::Act_c::M_arcname[4] = "Vds";

/* 00000078-00000134       .text SetLoopJointAnimation__Q28daObjVds5Act_cFP18J3DAnmTransformKeyP18J3DAnmTransformKeyff */
BOOL daObjVds::Act_c::SetLoopJointAnimation(J3DAnmTransformKey* i_bckAnm0, J3DAnmTransformKey* i_bckAnm1, float speed, float morf) {
    this->M_anm0->setAnm(i_bckAnm0, J3DFrameCtrl::EMode_LOOP, morf, speed, 0, -1, NULL);
    this->M_anm1->setAnm(i_bckAnm1, J3DFrameCtrl::EMode_LOOP, morf, speed, 0, -1, NULL);
    this->m318 = 1;
    
    return TRUE;
}

/* 00000134-00000188       .text PlayLoopJointAnimation__Q28daObjVds5Act_cFv */
BOOL daObjVds::Act_c::PlayLoopJointAnimation() {
    this->M_anm0->play(NULL, 0, 0);
    this->M_anm1->play(NULL, 0, 0);
    return TRUE;
}

/* 00000188-000001E8       .text set_first_process__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::set_first_process() {
    process_init(is_switch());
}

/* 000001E8-00000214       .text ds_search_switchCB__8daObjVdsFPvPv */
static void* daObjVds::ds_search_switchCB(void* i_act, void* i_VdsAct) {
    daObjVds::Act_c* pVdsAct = static_cast<daObjVds::Act_c*>(i_VdsAct);
    fopAc_ac_c* pAct = static_cast<fopAc_ac_c*>(i_act);
    return pVdsAct->search_switchCB(pAct);
}

/* 00000214-000002B0       .text search_switchCB__Q28daObjVds5Act_cFP10fopAc_ac_c */
void* daObjVds::Act_c::search_switchCB(fopAc_ac_c* i_act) {
    if(fopAc_IsActor(i_act) && fopAcM_GetName(i_act) == PROC_Obj_Swlight){
        for(int i = 0; i < 2; i++){
            if(this->m324[i] == -1){
                this->m324[i] = fopAcM_GetID(i_act);
                break;
            }
        }
    }

    return NULL;
}

/* 000002EC-000003C8       .text process_off_init__Q28daObjVds5Act_cFv */
BOOL daObjVds::Act_c::process_off_init() {

    if(
        this->mBrkAnm0.init(
            this->M_anm0->getModel()->getModelData(),
            this->M_brk_data0,
            true,
            J3DFrameCtrl::EMode_NONE,
            1, 0, -1, true, 0)
    ){
        this->mBrkAnm0.setPlaySpeed(0);
        if(
            this->mBrkAnm1.init(
                this->M_anm1->getModel()->getModelData(),
                this->M_brk_data1,
                true,
                J3DFrameCtrl::EMode_NONE,
                1, 0, -1, true, 0
            )
        ){
            this->mBrkAnm1.setPlaySpeed(0);
            return TRUE;
        }
    }

    return FALSE;
}

/* 000003C8-00000474       .text process_off_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_off_main() {
    for(int i = 0; i < 2; i++){
        fopAc_ac_c* actor = fopAcM_SearchByID(this->m324[i]);
        this->m32C[i] = actor[5].eyePos.x;
    }

    if(is_switch()){
        process_init(TRUE);
    }
}

/* 00000474-000004F0       .text process_on_init__Q28daObjVds5Act_cFv */
BOOL daObjVds::Act_c::process_on_init() {
    if(SetLoopJointAnimation(this->M_bck_data0, this->M_bck_data1, 1, 0)){
        for(int i = 0; i < 2; i++){
            this->m32C[i] = 1;
        }

        return TRUE;
    }
    else
        return FALSE;
}

/* 000004F0-000004F4       .text process_on_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_on_main() {
    return;
}

/* 000004F4-000005C0       .text process_init__Q28daObjVds5Act_cFi */
BOOL daObjVds::Act_c::process_init(int i_side) {
    static procInitFun_t init_table[2] = {};
    static s8 init;

    if(!init){
        init_table[0] = &daObjVds::Act_c::process_off_init;
        init_table[1] = &daObjVds::Act_c::process_on_init;
        init = 1;
    }

    if(0 <= i_side && i_side < 2 && (this->*init_table[i_side])() != FALSE){
        this->m31C = i_side;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/* 000005C0-0000065C       .text process_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_main() {
    static procMainFun_t main_table[2] = {};
    static s8 init;

    if(init == 0){
        main_table[0] = &daObjVds::Act_c::process_off_main;
        main_table[1] = &daObjVds::Act_c::process_on_main;
        init = 1;
    }

    if(0 <= this->m31C && this->m31C < 2){
        (this->*main_table[this->m31C])();
    }
}

/* 0000065C-000007EC       .text process_common__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_common() {
    switch(m320){
        case 0:
            for(int i = 0; i < 2; i++){
                this->m324[i] = -1;
            }

            fopAcIt_Judge(ds_search_switchCB, this);
            if(this->m324[0] != -1 && this->m324[1] != -1){
                fopAc_ac_c *actor0 = fopAcM_SearchByID(this->m324[0]), *actor1 = fopAcM_SearchByID(this->m324[1]);
                if(actor0 != NULL && actor1 != NULL){
                    s16 angle_diff = actor0->shape_angle.y - this->shape_angle.y;
                    if(angle_diff >= 0){
                        fpc_ProcID swap = this->m324[0];
                        this->m324[0] = this->m324[1];
                        this->m324[1] = swap;
                    }
                    this->m320 = 1;
                }
            }
            break;
        
        case 1:
            fopAc_ac_c *actor0 = fopAcM_SearchByID(this->m324[0]), *actor1 = fopAcM_SearchByID(this->m324[1]);
            if(actor0 != NULL && actor1 != NULL){
                create_point_light(0, fopAcM_GetPosition_p(actor0));
                create_point_light(1, fopAcM_GetPosition_p(actor1));
                this->m320 = 2;
            }
            break;
        
        case 2:
            execute_point_light();
            break;
    }
}

/* 000007EC-0000087C       .text create_point_light__Q28daObjVds5Act_cFiP4cXyz */
void daObjVds::Act_c::create_point_light(int i_side, cXyz* i_actorPos){
    VDS_SIDE side = static_cast<VDS_SIDE>(i_side & 1);

    this->m33C[side].mPos.set(*i_actorPos);
    this->m37C[side].set(*i_actorPos);
    
    this->m33C[side].mColor.r = 0x400;
    this->m33C[side].mColor.g = 0x400;
    this->m33C[side].mColor.b = 0x400;
    this->m33C[side].mPower = 0;
    this->m33C[side].mFluctuation = 0;
    dKy_plight_set(&this->m33C[side]);
}

/* 0000087C-00000900       .text execute_point_light__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::execute_point_light() {
    cXyz newPos;
    for(int i = 0; i < 2; i++){
        this->m33C[i].mPower = this->m32C[i] * 2200.f;
        newPos.set(this->m37C[i].x, this->m37C[i].y, this->m37C[i].z);
        this->m33C[i].mPos.set(newPos);
        this->m33C[i].mColor.r = 0x400;
        this->m33C[i].mColor.g = 0x400;
        this->m33C[i].mColor.b = 0x400;
    }
}

/* 00000900-00000954       .text delete_point_light__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::delete_point_light() {
    for(int i = 0; i < 2; i++){
        dKy_plight_cut(&this->m33C[i]);
    }
}

/* 00000954-00000968       .text Event_init__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::Event_init() {
    this->mEventIdx = -1;
    this->m336 = 0;
}

/* 00000968-00000A28       .text Event_exe__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::Event_exe() {
    switch(this->m336){
        case 1:
            if(this->eventInfo.checkCommandDemoAccrpt()){
                this->m336 = 2;
            }
            else {
                fopAcM_orderOtherEventId(this, this->mEventIdx);
                this->eventInfo.onCondition(dEvtCnd_UNK2_e);
            }
            break;
        case 2:
            if(dComIfGp_evmng_endCheck(this->mEventIdx)){
                dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
                Event_init();
            }
    }
}

/* 00000A28-00000A4C       .text solidHeapCB__Q28daObjVds5Act_cFP10fopAc_ac_c */
BOOL daObjVds::Act_c::solidHeapCB(fopAc_ac_c* i_actor) {
    return static_cast<daObjVds::Act_c*>(i_actor)->create_heap();
}

/* 00000A4C-00001020       .text create_heap__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::create_heap() {
    J3DModelData* mdl_data0 = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, VDS_BDL_VDSWT0));
    JUT_ASSERT(848, mdl_data0 != NULL);

    this->M_bck_data0 = static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes(M_arcname, VDS_BCK_VDSWT0));
    JUT_ASSERT(852, M_bck_data0 != NULL);

    if(mdl_data0 != NULL && M_bck_data0 != NULL)
        this->M_anm0 = new mDoExt_McaMorf(mdl_data0,
            NULL, NULL,
            M_bck_data0,
            J3DFrameCtrl::EMode_NONE,
            1, 0, -1, 1, NULL, 0, 0x11020203);

    JUT_ASSERT(865, M_anm0 != NULL);


    J3DModelData* mdl_data1 = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, VDS_BDL_VDSWT1));
    JUT_ASSERT(869, mdl_data1 != NULL);

    this->M_bck_data1 = static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes(M_arcname, VDS_BCK_VDSWT1));
    JUT_ASSERT(873, M_bck_data1 != NULL);

    if(mdl_data1 != NULL && M_bck_data1 != NULL)
            this->M_anm1 = new mDoExt_McaMorf(mdl_data1,
                NULL, NULL, 
                M_bck_data1,
                J3DFrameCtrl::EMode_NONE,
                1, 0, -1, 1, NULL, 0, 0x11020203);
    
    JUT_ASSERT(886, M_anm1 != NULL);

    this->M_brk_data0 = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname, VDS_BRK_VDSWT0));
    JUT_ASSERT(891, M_bck_data0 != NULL);
    BOOL brkAnm0_init = this->mBrkAnm0.init(mdl_data0,
        M_brk_data0,
        true, J3DFrameCtrl::EMode_NONE,
        1, 0, -1, false, 0);

    this->M_brk_data1 = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname, VDS_BRK_VDSWT1));
    JUT_ASSERT(904, M_brk_data1 != NULL);
    BOOL brkAnm1_init = this->mBrkAnm1.init(mdl_data1,
        M_brk_data1,
        true, J3DFrameCtrl::EMode_NONE,
        1, 0, -1, false, 0);
    
    set_mtx();

    cBgD_t* bgw_data = static_cast<cBgD_t*>(dComIfG_getObjectRes(M_arcname, VDS_DZB_VDSWT));
    JUT_ASSERT(926, bgw_data != NULL);
    
    if(bgw_data != NULL){
        this->m314 = new dBgW();
        if(this->m314 != NULL)
            this->m314->Set(bgw_data, 1, &this->m29C);
    }

    return (
        this->M_bck_data0 != NULL &&
        this->M_anm0 != NULL &&
        this->M_anm0->getModel() != NULL && 
        this->M_bck_data1 != NULL && 
        this->M_anm1 != NULL &&
        this->M_anm1->getModel() != NULL &&
        this->m314 != NULL && 
        this->M_brk_data0 != NULL &&
        this->M_brk_data1 != NULL &&
        brkAnm0_init && brkAnm1_init
    );
}

/* 00001020-000011EC       .text _create__Q28daObjVds5Act_cFv */
cPhs_State daObjVds::Act_c::_create() {
    fopAcM_SetupActor(this, daObjVds::Act_c);

    cPhs_State ret = dComIfG_resLoad(&this->mPhs, M_arcname);
    if(ret == cPhs_COMPLEATE_e){
        if(fopAcM_entrySolidHeap(this, solidHeapCB, 0)){
            set_first_process();
            fopAcM_SetMtx(this, this->M_anm0->getModel()->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -2000, -2000, -2000, 2000, 2000, 2000);
            dComIfG_Bgsp()->Regist(this->m314, this);
            this->m314->SetCrrFunc(NULL);
            Event_init();
            this->m338 = dComIfGp_evmng_getEventIdx("Vds");
            for(int i = 0; i < 2; i++){
                this->m324[i] = -1;
            }
        }
    }
    else {
        ret = cPhs_ERROR_e;
    }

    return ret;
}

/* 000012D4-00001368       .text _delete__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_delete() {
    if(this->heap != NULL && this->m314 != NULL){
        int bgwId = this->m314->GetId();
        
        bool doRelease;
        if(0 <= bgwId && bgwId < 256)
            doRelease = true;
        else
            doRelease = false;
        
        if(doRelease)
            dComIfG_Bgsp()->Release(this->m314);
    }
    delete_point_light();
    dComIfG_resDelete(&this->mPhs, M_arcname);

    return true;
}

/* 00001368-00001420       .text set_mtx__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::set_mtx() {
    this->M_anm0->getModel()->setBaseScale(this->scale);
    mDoMtx_stack_c::transS(this->current.pos);
    mDoMtx_stack_c::ZXYrotM(this->shape_angle);
    this->M_anm0->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
    this->M_anm1->getModel()->setBaseTRMtx(mDoMtx_stack_c::now);
    MTXCopy(mDoMtx_stack_c::now, this->m29C);
}

/* 00001420-000014EC       .text _execute__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_execute() {
    Event_exe();
    PlayLoopJointAnimation();

    this->mBrkAnm0.setFrame(this->m32C[0] * (this->M_brk_data0->getFrameMax() - 1));
    this->mBrkAnm1.setFrame(this->m32C[1] * (this->M_brk_data1->getFrameMax() - 1));
    
    process_common();
    process_main();
    set_mtx();
    
    if(this->m314 != NULL)
        this->m314->Move();
    
    return true;
}

/* 000014EC-000015A8       .text _draw__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_draw() {
    dKy_getEnvlight().settingTevStruct(TEV_TYPE_BG0, &this->current.pos, &this->tevStr);
    dKy_getEnvlight().setLightTevColorType(this->M_anm0->getModel(), &this->tevStr);
    dKy_getEnvlight().setLightTevColorType(this->M_anm1->getModel(), &this->tevStr);

    J3DModelData* modelData = this->M_anm0->getModel()->getModelData();
    this->mBrkAnm0.entry(modelData, this->mBrkAnm0.getFrame());
    modelData = this->M_anm1->getModel()->getModelData();
    this->mBrkAnm1.entry(modelData, this->mBrkAnm1.getFrame());
    this->M_anm0->updateDL();
    this->M_anm1->updateDL();

    return true;
}

namespace daObjVds {
namespace {
/* 000015A8-000015C8       .text Mthd_Create__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_create();
}

/* 000015C8-000015EC       .text Mthd_Delete__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_delete();
}

/* 000015EC-00001610       .text Mthd_Execute__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_execute();
}

/* 00001610-00001634       .text Mthd_Draw__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjVds::Act_c*)i_this)->_draw();
}

/* 00001634-0000163C       .text Mthd_IsDelete__Q28daObjVds25@unnamed@d_a_obj_Vds_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjVds

actor_process_profile_definition g_profile_Obj_Vds = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Vds_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjVds::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Vds_e,
    /* Actor SubMtd */ &daObjVds::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
