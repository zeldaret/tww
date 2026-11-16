/**
 * d_a_obj_Vds.cpp
 * Object - Earth Temple - Face statue (lights up when eyes are hit with Mirror Shield)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_Vds.h"
#include "d/actor/d_a_obj_swlight.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Vds.h"

namespace daObjVds {
namespace {
struct Attr_c {
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ s16 mLightR;
    /* 0x0E */ s16 mLightG;
    /* 0x10 */ s16 mLightB;
    /* 0x14 */ f32 mLightPower;
    /* 0x18 */ u8 field_0x18[0x28 - 0x18];
}; // Size: 0x28

static const Attr_c L_attr = {
    222.5f, 598.73f, 178.9f, 0x400, 0x400, 0x400, 2200.0f, {},
};

inline const Attr_c& attr() { return L_attr; }
} // namespace
} // namespace daObjVds

/* 00000078-00000134       .text SetLoopJointAnimation__Q28daObjVds5Act_cFP18J3DAnmTransformKeyP18J3DAnmTransformKeyff */
BOOL daObjVds::Act_c::SetLoopJointAnimation(J3DAnmTransformKey* bck0, J3DAnmTransformKey* bck1, float rate, float morf) {
    M_anm0->setAnm(bck0, J3DFrameCtrl::EMode_LOOP, morf, rate, 0.0f, -1.0f, NULL);
    M_anm1->setAnm(bck1, J3DFrameCtrl::EMode_LOOP, morf, rate, 0.0f, -1.0f, NULL);
    mAnmPlaying = 1;
    return TRUE;
}

/* 00000134-00000188       .text PlayLoopJointAnimation__Q28daObjVds5Act_cFv */
BOOL daObjVds::Act_c::PlayLoopJointAnimation() {
    M_anm0->play(NULL, 0, 0);
    M_anm1->play(NULL, 0, 0);
    return TRUE;
}

/* 00000188-000001E8       .text set_first_process__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::set_first_process() {
    process_init(is_switch() ? TRUE : FALSE);
}

/* 000001E8-00000214       .text ds_search_switchCB__8daObjVdsFPvPv */
void* daObjVds::ds_search_switchCB(void* i_ac, void* i_this) {
    return ((Act_c*)i_this)->search_switchCB((fopAc_ac_c*)i_ac);
}

/* 00000214-000002B0       .text search_switchCB__Q28daObjVds5Act_cFP10fopAc_ac_c */
void* daObjVds::Act_c::search_switchCB(fopAc_ac_c* i_ac) {
    if (fopAc_IsActor(i_ac) && fopAcM_GetName(i_ac) == fpcNm_Obj_Swlight_e) {
        for (int i = 0; i < 2; i++) {
            if (mSwitchID[i] == fpcM_ERROR_PROCESS_ID_e) {
                mSwitchID[i] = fopAcM_GetID(i_ac);
                break;
            }
        }
    }
    return NULL;
}

static void dummy_vds(cXyz* p, s16* a) {
    static s16 angle_data[] = {0, 0};
    *a = angle_data[0];
    cXyz tmp(-222.5f, 598.73f, 178.9f);
    tmp.x += 222.5f;
    *p = tmp;
}

/* 000002EC-000003C8       .text process_off_init__Q28daObjVds5Act_cFv */
BOOL daObjVds::Act_c::process_off_init() {
    if (mBrk0.init(M_anm0->getModel()->getModelData(), M_brk_data0, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0)) {
        mBrk0.setPlaySpeed(0.0f);
        if (mBrk1.init(M_anm1->getModel()->getModelData(), M_brk_data1, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0)) {
            mBrk1.setPlaySpeed(0.0f);
            return TRUE;
        }
    }
    return FALSE;
}

/* 000003C8-00000474       .text process_off_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_off_main() {
    for (int i = 0; i < 2; i++) {
        mRatio[i] = ((daObjSwlight::Act_c*)fopAcM_SearchByID(mSwitchID[i]))->mF30;
    }
    if (is_switch()) {
        process_init(1);
    }
}

/* 00000474-000004F0       .text process_on_init__Q28daObjVds5Act_cFv */
BOOL daObjVds::Act_c::process_on_init() {
    if (SetLoopJointAnimation(M_bck_data0, M_bck_data1, 1.0f, 0.0f)) {
        for (int i = 0; i < 2; i++) {
            mRatio[i] = 1.0f;
        }
        return TRUE;
    }
    return FALSE;
}

/* 000004F0-000004F4       .text process_on_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_on_main() {
}

/* 000004F4-000005C0       .text process_init__Q28daObjVds5Act_cFi */
BOOL daObjVds::Act_c::process_init(int mode) {
    typedef BOOL (daObjVds::Act_c::*initProc)();
    static initProc init_table[] = {
        &daObjVds::Act_c::process_off_init,
        &daObjVds::Act_c::process_on_init,
    };

    if (mode >= 0 && mode < 2 && (this->*init_table[mode])()) {
        mMode = mode;
        return TRUE;
    }
    return FALSE;
}

/* 000005C0-0000065C       .text process_main__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_main() {
    typedef void (daObjVds::Act_c::*mainProc)();
    static mainProc main_table[] = {
        &daObjVds::Act_c::process_off_main,
        &daObjVds::Act_c::process_on_main,
    };

    if (mMode >= 0 && mMode < 2) {
        (this->*main_table[mMode])();
    }
}

/* 0000065C-00000800       .text process_common__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::process_common() {
    switch (mCommonState) {
    case 0: {
        for (int i = 0; i < 2; i++) {
            mSwitchID[i] = fpcM_ERROR_PROCESS_ID_e;
        }
        fopAcIt_Judge((fopAcIt_JudgeFunc)ds_search_switchCB, this);
        if (mSwitchID[0] != fpcM_ERROR_PROCESS_ID_e && mSwitchID[1] != fpcM_ERROR_PROCESS_ID_e) {
            fopAc_ac_c* sw0 = fopAcM_SearchByID(mSwitchID[0]);
            fopAc_ac_c* sw1 = fopAcM_SearchByID(mSwitchID[1]);
            if (sw0 != NULL && sw1 != NULL) {
                if ((s16)(sw0->shape_angle.y - shape_angle.y) >= 0) {
                    fpc_ProcID tmp = mSwitchID[0];
                    mSwitchID[0] = mSwitchID[1];
                    mSwitchID[1] = tmp;
                }
                mCommonState = 1;
            }
        }
        break;
    }
    case 1: {
        fopAc_ac_c* sw0 = fopAcM_SearchByID(mSwitchID[0]);
        fopAc_ac_c* sw1 = fopAcM_SearchByID(mSwitchID[1]);
        if (sw0 != NULL && sw1 != NULL) {
            create_point_light(0, &sw0->current.pos);
            create_point_light(1, &sw1->current.pos);
            mCommonState = 2;
        }
        break;
    }
    case 2:
        execute_point_light();
        break;
    }
}

/* 00000800-00000870       .text create_point_light__Q28daObjVds5Act_cFiP4cXyz */
void daObjVds::Act_c::create_point_light(int idx, cXyz* pos) {
    int no = idx & 1;
    mLight[no].mPos = *pos;
    mLightPos[no] = *pos;
    mLight[no].mColor.r = 0x400;
    mLight[no].mColor.g = 0x400;
    mLight[no].mColor.b = 0x400;
    mLight[no].mPower = 0.0f;
    mLight[no].mFluctuation = 0.0f;
    dKy_plight_set(&mLight[no]);
}

/* 00000870-000008F8       .text execute_point_light__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::execute_point_light() {
    for (int i = 0; i < 2; i++) {
        mLight[i].mPower = 2200.0f * mRatio[i];
        cXyz pos(mLightPos[i].x, mLightPos[i].y, mLightPos[i].z);
        mLight[i].mPos = pos;
        mLight[i].mColor.r = 0x400;
        mLight[i].mColor.g = 0x400;
        mLight[i].mColor.b = 0x400;
    }
}

/* 000008F8-00000948       .text delete_point_light__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::delete_point_light() {
    for (int i = 0; i < 2; i++) {
        dKy_plight_cut(&mLight[i]);
    }
}

/* 00000948-0000095C       .text Event_init__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::Event_init() {
    mEventId = -1;
    mEventState = 0;
}

/* 0000095C-00000A28       .text Event_exe__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::Event_exe() {
    switch (mEventState) {
    case 1:
        if (eventInfo.checkCommandDemoAccrpt()) {
            mEventState = 2;
        } else {
            fopAcM_orderOtherEventId(this, mEventId, 0xFF, 0xFFFF, 0, 1);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
        break;
    case 2:
        if (dComIfGp_evmng_endCheck(mEventId)) {
            dComIfGp_event_reset();
            Event_init();
        }
        break;
    }
}

/* 00000A28-00000A4C       .text solidHeapCB__Q28daObjVds5Act_cFP10fopAc_ac_c */
BOOL daObjVds::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

const char daObjVds::Act_c::M_arcname[] = "Vds";

/* 00000A4C-0000101C       .text create_heap__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::create_heap() {
    J3DModelData* mdl_data0 = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BDL_VDSWT0_e);
    JUT_ASSERT(848, mdl_data0 != 0);

    M_bck_data0 = (J3DAnmTransformKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BCK_VDSWT0_e);
    JUT_ASSERT(852, M_bck_data0 != 0);

    if (mdl_data0 != NULL && M_bck_data0 != NULL) {
        M_anm0 = new mDoExt_McaMorf(mdl_data0, NULL, NULL, M_bck_data0, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 1, NULL, 0, 0x11020203);
    }
    JUT_ASSERT(865, M_anm0 != 0);

    J3DModelData* mdl_data1 = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BDL_VDSWT1_e);
    JUT_ASSERT(869, mdl_data1 != 0);

    M_bck_data1 = (J3DAnmTransformKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BCK_VDSWT1_e);
    JUT_ASSERT(873, M_bck_data1 != 0);

    if (mdl_data1 != NULL && M_bck_data1 != NULL) {
        M_anm1 = new mDoExt_McaMorf(mdl_data1, NULL, NULL, M_bck_data1, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, 1, NULL, 0, 0x11020203);
    }
    JUT_ASSERT(886, M_anm1 != 0);

    M_brk_data0 = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BRK_VDSWT0_e);
    JUT_ASSERT(891, M_brk_data0 != 0);
    int brk_ret0 = mBrk0.init(mdl_data0, M_brk_data0, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);

    M_brk_data1 = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_BRK_VDSWT1_e);
    JUT_ASSERT(904, M_brk_data1 != 0);
    int brk_ret1 = mBrk1.init(mdl_data1, M_brk_data1, TRUE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);

    set_mtx();

    cBgD_t* bgw_data = (cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_VDS_DZB_VDSWT_e);
    JUT_ASSERT(926, bgw_data != 0);
    if (bgw_data != NULL) {
        mpBgW = new dBgW();
        if (mpBgW != NULL) {
            mpBgW->Set(bgw_data, cBgW::MOVE_BG_e, &mMtx);
        }
    }

    return M_bck_data0 != NULL && M_anm0 != NULL && M_anm0->getModel() != NULL &&
           M_bck_data1 != NULL && M_anm1 != NULL && M_anm1->getModel() != NULL &&
           mpBgW != NULL && M_brk_data0 != NULL && M_brk_data1 != NULL && brk_ret0 && brk_ret1;
}

/* 0000101C-000011EC       .text _create__Q28daObjVds5Act_cFv */
cPhs_State daObjVds::Act_c::_create() {
    fopAcM_ct(this, daObjVds::Act_c);

    cPhs_State ret = dComIfG_resLoad(&mPhase, M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0)) {
            set_first_process();
            fopAcM_SetMtx(this, M_anm0->getModel()->getBaseTRMtx());
            fopAcM_setCullSizeBox(this, -2000.0f, -2000.0f, -2000.0f, 2000.0f, 2000.0f, 2000.0f);
            dComIfG_Bgsp()->Regist(mpBgW, this);
            mpBgW->SetCrrFunc(NULL);
            Event_init();
            mEventIdx = dComIfGp_evmng_getEventIdx("Vds");
            for (int i = 0; i < 2; i++) {
                mSwitchID[i] = fpcM_ERROR_PROCESS_ID_e;
            }
        } else {
            ret = cPhs_ERROR_e;
        }
    }
    return ret;
}

/* 000012C8-00001358       .text _delete__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_delete() {
    if (heap != NULL && mpBgW != NULL && mpBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
    delete_point_light();
    dComIfG_resDelete(&mPhase, M_arcname);
    return true;
}

/* 00001358-00001410       .text set_mtx__Q28daObjVds5Act_cFv */
void daObjVds::Act_c::set_mtx() {
    M_anm0->getModel()->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    M_anm0->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    M_anm1->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), mMtx);
}

/* 00001410-000014EC       .text _execute__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_execute() {
    Event_exe();
    PlayLoopJointAnimation();
    mBrk0.setFrame(mRatio[0] * (M_brk_data0->getFrameMax() - 1));
    mBrk1.setFrame(mRatio[1] * (M_brk_data1->getFrameMax() - 1));
    process_common();
    process_main();
    set_mtx();
    if (mpBgW != NULL) {
        mpBgW->Move();
    }
    return true;
}

static void dummy_color(GXColor* c) {
    GXColor color = {0xFF, 0x00, 0x00, 0x80};
    *c = color;
}

/* 000014EC-000015A8       .text _draw__Q28daObjVds5Act_cFv */
bool daObjVds::Act_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(M_anm0->getModel(), &tevStr);
    g_env_light.setLightTevColorType(M_anm1->getModel(), &tevStr);
    mBrk0.entry(M_anm0->getModel()->getModelData());
    mBrk1.entry(M_anm1->getModel()->getModelData());
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
