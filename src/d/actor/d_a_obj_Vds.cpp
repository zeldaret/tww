/**
 * d_a_obj_Vds.cpp
 * Object - Earth Temple - Face statue (lights up when eyes are hit with Mirror Shield)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Vds.h"
#include "res/Object/Vds.h"
#include "d/actor/d_a_obj_swlight.h"

namespace daObjVds {
    namespace {
        struct Attr_c { // Corresponds to unused data, so i tried to infer what i could
                f32 m00;
                f32 m04;
                f32 m08;
                s16 m0C;
                s16 m0E;
                s16 m10;
                f32 m14;
                u8  m18[16];
            }; // Size : 0x28

        static const Attr_c L_attr = {
            222.5f, 598.73f, 178.9f,
            0x400, 0x400, 0x400,
            2200.f,
            {NULL}
        };
    };
};

#if VERSION == VERSION_DEMO
static f32 lbl_365_data_1C[5] = { 0, 2.125, 0, 1.75, 0}; // Unused
#endif


/* 00000078-00000134       .text SetLoopJointAnimation__Q28daObjVds5Act_cFP18J3DAnmTransformKeyP18J3DAnmTransformKeyff */
BOOL daObjVds::Act_c::SetLoopJointAnimation(J3DAnmTransformKey* i_bckAnm0, J3DAnmTransformKey* i_bckAnm1, float i_playSpeed, float i_morf) {
    static s16 angle_data[2] = {}; // Unused, so i defined it here
    M_anm0->setAnm(i_bckAnm0, J3DFrameCtrl::EMode_LOOP, i_morf, i_playSpeed, 0, -1, NULL);
    M_anm1->setAnm(i_bckAnm1, J3DFrameCtrl::EMode_LOOP, i_morf, i_playSpeed, 0, -1, NULL);
    m318 = 1;
    
    return TRUE;
}

/* 00000134-00000188       .text PlayLoopJointAnimation__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::PlayLoopJointAnimation() {
    const f32 unused[4] = {
        -222.5f,
        598.73f,
        178.9f,
        222.5f
    }; // Unused data
    
    M_anm0->play(NULL, 0, 0);
    M_anm1->play(NULL, 0, 0);
    return TRUE;
}


/* 00000188-000001E8       .text set_first_process__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::set_first_process() {
    BOOL side = is_switch() ? TRUE : FALSE;
    process_init(side);
}

/* 000001E8-00000214       .text ds_search_switchCB__8daObjVdsFPvPv */
static void* daObjVds::ds_search_switchCB(void* i_actor, void* i_this) {
    daObjVds::Act_c* pVdsAct = static_cast<daObjVds::Act_c*>(i_this);
    fopAc_ac_c* pAct = static_cast<fopAc_ac_c*>(i_actor);
    return pVdsAct->search_switchCB(pAct);
}

/* 00000214-000002B0       .text search_switchCB__Q28daObjVds5Act_cFP10fopAc_ac_c */
void* daObjVds::Act_c::search_switchCB(fopAc_ac_c* i_actor) {
    if(fopAc_IsActor(i_actor) && fopAcM_GetName(i_actor) == fpcNm_Obj_Swlight_e){
        cXyz unused;
        for(int i = 0; i < 2; i++){
            if(mEyeID[i] == -1){
                mEyeID[i] = fopAcM_GetID(i_actor);
                break;
            }
        }
    }

    return NULL;
}

/* 000002EC-000003C8       .text process_off_init__Q28daObjVds5Act_cFv */
BOOL daObjVds::Act_c::process_off_init() {
    if(
        mBrkAnm0.init(
            M_anm0->getModel()->getModelData(),
            M_brk_data0,
            true,
            J3DFrameCtrl::EMode_NONE,
            1, 0, -1, true, 0)
    ){
        mBrkAnm0.setPlaySpeed(0);
        if(
            mBrkAnm1.init(
                M_anm1->getModel()->getModelData(),
                M_brk_data1,
                true,
                J3DFrameCtrl::EMode_NONE,
                1, 0, -1, true, 0
            )
        ){
            mBrkAnm1.setPlaySpeed(0);
            return TRUE;
        }
    }

    return FALSE;
}

/* 000003C8-00000474       .text process_off_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_off_main() {
    for(int i = 0; i < 2; i++){
        daObjSwlight::Act_c* eye_actor = static_cast<daObjSwlight::Act_c*>(fopAcM_SearchByID(mEyeID[i]));
        mEyePower[i] = eye_actor->get_power();
    }

    if(is_switch()){
        process_init(1);
    }
}

/* 00000474-000004F0       .text process_on_init__Q28daObjVds5Act_cFv */
BOOL daObjVds::Act_c::process_on_init() {
    if(SetLoopJointAnimation(M_bck_data0, M_bck_data1, 1, 0)){
        for(int i = 0; i < 2; i++){
            mEyePower[i] = 1;
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
    static procInitFun_t init_table[2] = {
        &daObjVds::Act_c::process_off_init,
        &daObjVds::Act_c::process_on_init
    };

    if(0 <= i_side && i_side < 2 && (this->*init_table[i_side])() != FALSE){
        mSide = i_side;
        return TRUE;
    }
    else {
        return FALSE;
    }
}

/* 000005C0-0000065C       .text process_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_main() {
    static procMainFun_t main_table[2] = {
        &daObjVds::Act_c::process_off_main,
        &daObjVds::Act_c::process_on_main
    };

    if(0 <= mSide && mSide < 2){
        (this->*main_table[mSide])();
    }
}

/* 0000065C-000007EC       .text process_common__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_common() {
    // Regalloc issue in demo
    fopAc_ac_c* actor_eye[2];
    switch(m320){
        case 0:
            for(int i = 0; i < 2; i++){
                mEyeID[i] = -1;
            }

            fopAcM_Search(ds_search_switchCB, this);
            if(mEyeID[0] != -1 && mEyeID[1] != -1){
                actor_eye[0] = fopAcM_SearchByID(mEyeID[0]);
                actor_eye[1] = fopAcM_SearchByID(mEyeID[1]);
                if(actor_eye[0] != NULL && actor_eye[1] != NULL){
                    s16 angle_diff = actor_eye[0]->shape_angle.y - this->shape_angle.y;
                    if(angle_diff >= 0){
                        fpc_ProcID swap = mEyeID[0];
                        mEyeID[0] = mEyeID[1];
                        mEyeID[1] = swap;
                    }
                    m320 = 1;
                }
            }
            break;
        
        case 1:
            actor_eye[0] = fopAcM_SearchByID(mEyeID[0]);
            actor_eye[1] = fopAcM_SearchByID(mEyeID[1]);
            if(actor_eye[0] != NULL && actor_eye[1] != NULL){
                create_point_light(0, &actor_eye[0]->current.pos);
                create_point_light(1, &actor_eye[1]->current.pos);
                m320 = 2;
            }
            break;
        
        case 2:
            execute_point_light();
            break;
    }
}

/* 000007EC-0000087C       .text create_point_light__Q28daObjVds5Act_cFiP4cXyz */
void daObjVds::Act_c::create_point_light(int i_side, cXyz* i_actorPos){
    int side = i_side & 1;

    mEyeLightInfluence[side].mPos = *i_actorPos;
    m37C[side] = *i_actorPos;
    
    mEyeLightInfluence[side].mColor.r = 0x400;
    mEyeLightInfluence[side].mColor.g = 0x400;
    mEyeLightInfluence[side].mColor.b = 0x400;
    mEyeLightInfluence[side].mPower = 0;
    mEyeLightInfluence[side].mFluctuation = 0;
    dKy_plight_set(&mEyeLightInfluence[side]);
}

/* 0000087C-00000900       .text execute_point_light__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::execute_point_light() {
    for(int i = 0; i < 2; i++){
        mEyeLightInfluence[i].mPower = mEyePower[i] * 2200.f;
        
        cXyz newPos(m37C[i].x, m37C[i].y, m37C[i].z);
        mEyeLightInfluence[i].mPos.set(newPos);
        
        mEyeLightInfluence[i].mColor.r = 0x400;
        mEyeLightInfluence[i].mColor.g = 0x400;
        mEyeLightInfluence[i].mColor.b = 0x400;
    }
}

/* 00000900-00000954       .text delete_point_light__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::delete_point_light() {
    for(int i = 0; i < 2; i++){
        dKy_plight_cut(&mEyeLightInfluence[i]);
    }
}

/* 00000954-00000968       .text Event_init__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::Event_init() {
    mEventIdx = -1;
    m336 = 0;
}

/* 00000968-00000A28       .text Event_exe__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::Event_exe() {
    switch(m336){
        case 1:
            if(eventInfo.checkCommandDemoAccrpt()){
                m336 = 2;
            }
            else {
                fopAcM_orderOtherEventId(this, mEventIdx);
                eventInfo.onCondition(dEvtCnd_UNK2_e);
            }
            break;
        case 2:
            if(dComIfGp_evmng_endCheck(mEventIdx)){
                dComIfGp_event_onEventFlag(dSv_event_flag_c::UNK_0008);
                Event_init();
            }
    }
}

/* 00000A28-00000A4C       .text solidHeapCB__Q28daObjVds5Act_cFP10fopAc_ac_c */
BOOL daObjVds::Act_c::solidHeapCB(fopAc_ac_c* i_actor) {
    return static_cast<daObjVds::Act_c*>(i_actor)->create_heap();
}

const char daObjVds::Act_c::M_arcname[4] = "Vds";

/* 00000A4C-00001020       .text create_heap__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::create_heap() {
    J3DModelData* mdl_data0 = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BDL_VDSWT0_e));
    JUT_ASSERT(848, mdl_data0 != NULL);

    M_bck_data0 = static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BCK_VDSWT0_e));
    JUT_ASSERT(852, M_bck_data0 != NULL);

#if VERSION != VERSION_DEMO
    if(mdl_data0 != NULL && M_bck_data0 != NULL)
#endif
        M_anm0 = new mDoExt_McaMorf(mdl_data0,
            NULL, NULL,
            M_bck_data0,
            J3DFrameCtrl::EMode_NONE,
            1, 0, -1, 1, NULL, 0, 0x11020203);

    JUT_ASSERT((VERSION == VERSION_DEMO) ? 863 : 865, M_anm0 != NULL);


    J3DModelData* mdl_data1 = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BDL_VDSWT1_e));
    JUT_ASSERT((VERSION == VERSION_DEMO) ? 867 : 869, mdl_data1 != NULL);

    M_bck_data1 = static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BCK_VDSWT1_e));
    JUT_ASSERT((VERSION == VERSION_DEMO) ? 871 : 873, M_bck_data1 != NULL);

#if VERSION != VERSION_DEMO
    if(mdl_data1 != NULL && M_bck_data1 != NULL)
#endif
            M_anm1 = new mDoExt_McaMorf(mdl_data1,
                NULL, NULL, 
                M_bck_data1,
                J3DFrameCtrl::EMode_NONE,
                1, 0, -1, 1, NULL, 0, 0x11020203);
    
    JUT_ASSERT((VERSION == VERSION_DEMO) ? 882 : 886, M_anm1 != NULL);

    M_brk_data0 = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BRK_VDSWT0_e));
    JUT_ASSERT((VERSION == VERSION_DEMO) ? 887 : 891, M_brk_data0 != NULL);
    BOOL mBrkAnm0_init = mBrkAnm0.init(mdl_data0,
        M_brk_data0,
        true, J3DFrameCtrl::EMode_NONE,
        1, 0, -1, false, 0);

    M_brk_data1 = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BRK_VDSWT1_e));
    JUT_ASSERT((VERSION == VERSION_DEMO) ? 900 : 904, M_brk_data1 != NULL);
    BOOL mBrkAnm1_init = mBrkAnm1.init(mdl_data1,
        M_brk_data1,
        true, J3DFrameCtrl::EMode_NONE,
        1, 0, -1, false, 0);
    
    set_mtx();

    cBgD_t* bgw_data = static_cast<cBgD_t*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_DZB_VDSWT_e));
    JUT_ASSERT((VERSION == VERSION_DEMO) ? 922 : 926, bgw_data != NULL);
    
    if(VERSION == VERSION_DEMO || bgw_data != NULL){
        mpBgW = new dBgW();
        if(mpBgW != NULL)
            mpBgW->Set(bgw_data, 1, &m29C);
    }

    return (
        M_bck_data0 != NULL &&
        M_anm0 != NULL &&
        M_anm0->getModel() != NULL && 
        M_bck_data1 != NULL && 
        M_anm1 != NULL &&
        M_anm1->getModel() != NULL &&
        mpBgW != NULL && 
        M_brk_data0 != NULL &&
        M_brk_data1 != NULL 
    #if VERSION != VERSION_DEMO
        && mBrkAnm0_init && mBrkAnm1_init
    #endif
    );
}

/* 00001020-000011EC       .text _create__Q28daObjVds5Act_cFv */
cPhs_State daObjVds::Act_c::_create() {
    fopAcM_SetupActor(this, daObjVds::Act_c);

    cPhs_State state = dComIfG_resLoad(&mPhs, M_arcname);
    if(state == cPhs_COMPLEATE_e){
        if(fopAcM_entrySolidHeap(this, solidHeapCB, 0)){
            set_first_process();
            fopAcM_SetMtx(this, M_anm0->getModel()->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -2000, -2000, -2000, 2000, 2000, 2000);
            dComIfG_Bgsp()->Regist(mpBgW, this);
            mpBgW->SetCrrFunc(NULL);
            Event_init();
            m338 = dComIfGp_evmng_getEventIdx("Vds");
            for(int i = 0; i < 2; i++){
                mEyeID[i] = -1;
            }
        }
        else {
            state = cPhs_ERROR_e;
        }
    }

    return state;
}

/* 000012D4-00001368       .text _delete__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_delete() {
    if(DEMO_SELECT(mpBgW != NULL, heap != NULL && mpBgW != NULL)) {
        int bgwId = mpBgW->GetId();
        
        bool doRelease;
        if(0 <= bgwId && bgwId < 256)
            doRelease = true;
        else
            doRelease = false;
        
        if(doRelease)
            dComIfG_Bgsp()->Release(mpBgW);
    }
    delete_point_light();
    dComIfG_resDelete(&mPhs, M_arcname);

    return true;
}

/* 00001368-00001420       .text set_mtx__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::set_mtx() {
    M_anm0->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    M_anm0->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    M_anm1->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::now, m29C);
}

/* 00001420-000014EC       .text _execute__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_execute() {
    Event_exe();
    PlayLoopJointAnimation();

    mBrkAnm0.setFrame(mEyePower[0] * (M_brk_data0->getFrameMax() - 1));
    mBrkAnm1.setFrame(mEyePower[1] * (M_brk_data1->getFrameMax() - 1));
    
    process_common();
    process_main();
    set_mtx();
    
    if(mpBgW != NULL)
        mpBgW->Move();
    
    return true;
}

/* 000014EC-000015A8       .text _draw__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_draw() {
    const u8 unused[4] = {
        0xFF,
        0,
        0,
        0x80
    }; // Unused variable

    dKy_getEnvlight().settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    dKy_getEnvlight().setLightTevColorType(M_anm0->getModel(), &tevStr);
    dKy_getEnvlight().setLightTevColorType(M_anm1->getModel(), &tevStr);

    J3DModelData* modelData = M_anm0->getModel()->getModelData();
    mBrkAnm0.entry(modelData, mBrkAnm0.getFrame());
    modelData = M_anm1->getModel()->getModelData();
    mBrkAnm1.entry(modelData, mBrkAnm1.getFrame());
    M_anm0->updateDL();
    M_anm1->updateDL();

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
