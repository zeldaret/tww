/**
 * d_a_obj_YLzou.cpp
 * Object - Hyrule Castle - Link statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_YLzou.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_bg_w.h"
#include "d/res/res_ylzou.h"

namespace {
const char l_arcname[] = "YLzou";
const char l_move_ylzou_demo_name[] = "move_YLzou";
const char l_go_up_stairs_demo_name[] = "go_up_stairs";
const char l_go_up_stairs_demo2_name[] = "go_up_stairs2";
const char* l_demo_name[] = {
    NULL,
    l_move_ylzou_demo_name,
    l_go_up_stairs_demo_name,
    l_go_up_stairs_demo2_name,
};
} // namespace

/* 000000EC-000002B8       .text set_start_type__12daObjYLzou_cFv */
void daObjYLzou_c::set_start_type() {
    int type = 0;
    int demoIdx = 0;
    u8 onFlag = 0;
    int mode;

    if (!dComIfGs_isEventBit(0x2d04)) {
        if (m2e0 != 0xff && !dComIfGs_isSwitch(m2e0, fopAcM_GetHomeRoomNo(this))) {
            mode = 0;
            demoIdx = 1;
        } else {
            mode = 6;
            onFlag = 1;
        }
    } else if (!dComIfGs_isEventBit(0x3a04)) {
        mode = 6;
        onFlag = 1;
    } else if (!dComIfGs_isEventBit(0x3804)) {
        if (dComIfGs_isEventBit(0x3820) == 1) {
            mode = 7;
            demoIdx = 2;
        } else {
            mode = 0xb;
        }
    } else if (!dComIfGs_isEventBit(0x2d02)) {
        mode = 6;
        onFlag = 1;
    } else if (dComIfGs_getTriforceNum() < 8) {
        if (dComIfGs_isEventBit(0x3820) == 1) {
            mode = 7;
            demoIdx = 2;
        } else {
            mode = 0xb;
        }
    } else {
        type = 1;
        if (!dComIfGs_isEventBit(0x2c01)) {
            mode = 0xc;
        } else if (!dComIfGs_isEventBit(0x3980)) {
            mode = 0xd;
            demoIdx = 3;
        } else {
            mode = 0xc;
        }
    }

    mActionIdx = mode;
    mType = type;
    m2ec = demoIdx;
    if (onFlag == 0) {
        dComIfGs_offEventBit(0x3820);
    } else {
        dComIfGs_onEventBit(0x3820);
    }
}

/* 000002B8-00000374       .text set_mtx__12daObjYLzou_cFv */
void daObjYLzou_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + m35c * cM_ssin(m358), current.pos.z);
    mDoMtx_stack_c::XYZrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
    cMtx_copy(mDoMtx_stack_c::get(), mMtx);
}

/* 00000374-000003B0       .text init_mtx__12daObjYLzou_cFv */
void daObjYLzou_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 000003B0-000003D4       .text solidHeapCB__12daObjYLzou_cFP10fopAc_ac_c */
BOOL daObjYLzou_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjYLzou_c*)i_this)->create_heap();
}

/* 000003D4-000004F4       .text create_heap__12daObjYLzou_cFv */
bool daObjYLzou_c::create_heap() {
    static u32 bdl_table[] = { YLZOU_BDL_YLZOU, YLZOU_BDL_YLZOU2 };
    static u32 dzb_table[] = { YLZOU_DZB_YLZOU, YLZOU_DZB_YLZOU2 };

    bool ok = true;
    J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(l_arcname, bdl_table[mType]));
    if (mdl_data == NULL) {
        JUT_ASSERT(408, 0);
        ok = false;
    } else {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000022);
        Mtx* baseMtx = &mpModel->getBaseTRMtx();
        cBgD_t* dzb = static_cast<cBgD_t*>(dComIfG_getObjectRes(l_arcname, dzb_table[mType]));
        mBgW = dBgW_NewSet(dzb, 1, baseMtx);
        if (mpModel == NULL || mBgW == NULL) {
            ok = false;
        }
    }
    return ok;
}

/* 000004F4-00000668       .text eff_set_slip_smoke_pos__12daObjYLzou_cFv */
void daObjYLzou_c::eff_set_slip_smoke_pos() {
    static cXyz base_pos[ARRAY_SIZE(mSmoke)] = {
        cXyz(-240.0f, 0.0f, -240.0f),
        cXyz(240.0f, 0.0f, -240.0f)
    };

    mDoMtx_stack_c::transS(current.pos.x, -1550.0f + current.pos.y, -1200.0f + current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);

    for (int i = 0; i < (int)ARRAY_SIZE(mSmoke); i++) {
        mDoMtx_stack_c::push();
        mDoMtx_stack_c::transM(base_pos[i].x, base_pos[i].y, base_pos[i].z);
        mSmoke[i].field_0x20.x = mDoMtx_stack_c::get()[0][3];
        mSmoke[i].field_0x20.y = mDoMtx_stack_c::get()[1][3];
        mSmoke[i].field_0x20.z = mDoMtx_stack_c::get()[2][3];
        mSmoke[i].field_0x2C.set(0, current.angle.y, 0);
        mDoMtx_stack_c::pop();
    }
}

/* 000006A4-000007AC       .text eff_smoke_slip_start__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_slip_start() {
    static cXyz scl(2.0f, 2.0f, 2.0f);

    eff_set_slip_smoke_pos();

    for (int i = 0; i < (int)ARRAY_SIZE(mSmoke); i++) {
        JPABaseEmitter* emitter = dComIfGp_particle_setToon(
            dPa_name::ID_AK_JT_ELEMENTSMOKE00, &mSmoke[i].field_0x20, &mSmoke[i].field_0x2C,
            &scl, 0xB9, &mSmoke[i], fopAcM_GetRoomNo(this)
        );
        if (emitter) {
            emitter->setRate(2.0f);
            emitter->setDirectionalSpeed(15.0f);
            emitter->setSpread(0.15f);
            emitter->setLifeTime(30);
        }
    }
}

/* 000007AC-0000080C       .text eff_smoke_slip_end__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_slip_end() {
    for (int i = 0; i < (int)ARRAY_SIZE(mSmoke); i++) {
        mSmoke[i].remove();
    }
}

/* 0000080C-0000086C       .text eff_smoke_slip_remove__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_slip_remove() {
    for (int i = 0; i < (int)ARRAY_SIZE(mSmoke); i++) {
        mSmoke[i].remove();
    }
}

/* 0000086C-000008D0       .text eff_smoke_proc__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_proc() {
    if (m360 != m361) {
        if (m361 == 1) {
            eff_smoke_slip_start();
        } else {
            eff_smoke_slip_end();
        }
        m360 = m361;
    } else if (m360 == 1) {
        eff_set_slip_smoke_pos();
    }
}

/* 000008D0-000009A4       .text vib_proc__12daObjYLzou_cFv */
void daObjYLzou_c::vib_proc() {
    if (m364 != m368) {
        m364 = m368;
    }
    switch (m364) {
    case 1:
        m358 += 0x4000;
        m35c += 0.05f;
        if (m35c > 0.8f) {
            m35c = 0.8f;
        }
        break;
    case 2:
        m358 += 0x4000;
        m35c -= 0.05f;
        if (m35c < 0.4f) {
            m35c = 0.4f;
        }
        break;
    default:
        m358 += 0x4000;
        m35c -= 0.1f;
        if (m35c < 0.0f) {
            m35c = 0.0f;
        }
        break;
    }
}

/* 000009A4-00000AE0       .text _create__12daObjYLzou_cFv */
cPhs_State daObjYLzou_c::_create() {
    static u32 solidHeapSize_table[] = { 0x5840, 0x49E0 };

    fopAcM_SetupActor(this, daObjYLzou_c);

    if (fpcM_IsFirstCreating(this)) {
        m2e0 = prm_get_swSave();
        set_start_type();
    }

    cPhs_State phase = dComIfG_resLoad(&mPhase, l_arcname);
    if (phase == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, solidHeapSize_table[mType])) {
            if (dComIfG_Bgsp()->Regist(mBgW, this)) {
                phase = cPhs_ERROR_e;
            } else {
                fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
                setup_action(mActionIdx);
                init_mtx();
            }
        } else {
            phase = cPhs_ERROR_e;
        }
    }
    return phase;
}

/* 00000AE0-00000B7C       .text _delete__12daObjYLzou_cFv */
bool daObjYLzou_c::_delete() {
    dComIfG_resDelete(&mPhase, l_arcname);
    eff_smoke_slip_remove();
    if (heap != NULL && mBgW != NULL) {
        if (mBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mBgW);
        }
        mBgW = NULL;
    }
    return true;
}

/* 00000B7C-00000BD8       .text move_ylzou_demo_start_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_start_wait_act_proc() {
    if (m2e0 != 0xff && dComIfGs_isSwitch(m2e0, fopAcM_GetHomeRoomNo(this)) == 1) {
        setup_action(1);
    }
}

/* 00000BD8-00000C70       .text demo_regist_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_regist_wait_act_proc() {
    if (m2e4 != -1) {
        if (eventInfo.getCommand() == 2) {
            setup_action(mActionIdx + 1);
        } else {
            fopAcM_orderOtherEventId(this, m2e4);
        }
    } else {
        m2e4 = dComIfGp_evmng_getEventIdx(l_demo_name[m2ec], 0xff);
    }
}

/* 00000C70-00000D18       .text demo_vib_start_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_vib_start_wait_act_proc() {
    if (dComIfGp_getPEvtManager()->getEventData(m2e4) != NULL) {
        int staffId = dComIfGp_getPEvtManager()->getMyStaffId("YLzou", NULL, 0);
        if (staffId != -1) {
            if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffId), "Vibrate") == 0) {
                setup_action(mActionIdx + 1);
            }
        }
    }
}

/* 00000D18-00000E08       .text demo_vib_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_vib_act_proc() {
    if (dComIfGp_getPEvtManager()->getEventData(m2e4) != NULL) {
        int staffId = dComIfGp_getPEvtManager()->getMyStaffId("YLzou", NULL, 0);
        if (staffId != -1) {
            if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffId), "Move") == 0) {
                setup_action(mActionIdx + 1);
            }
        }
    }
    mDoAud_seStart(0x6225, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
}

/* 00000E08-00000F0C       .text move_ylzou_demo_move_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_move_act_proc() {
    if (current.pos.z < -170.0f + home.pos.z) {
        mDoAud_seStart(0x6A27, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        setup_action(5);
    } else {
        speedF += 0.1f;
        if (speedF > 6.0f) {
            speedF = 6.0f;
        }
        mDoAud_seStart(0x6226, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }
}

/* 00000F0C-00001008       .text go_up_stairs_demo_move_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::go_up_stairs_demo_move_act_proc() {
    if (current.pos.z > home.pos.z) {
        mDoAud_seStart(0x6A27, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        setup_action(0xA);
    } else {
        speedF += 0.1f;
        if (speedF > 6.0f) {
            speedF = 6.0f;
        }
        mDoAud_seStart(0x6226, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }
}

/* 00001008-000010A8       .text demo_end_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_end_wait_act_proc() {
    static int next_act_idx[] = { -1, 6, 11, 12 };

    if (dComIfGp_evmng_endCheck(m2e4)) {
        dComIfGp_event_onEventFlag(8);
        if (mActionIdx == 0xE) {
            dComIfGs_onEventBit(0x3980);
        }
        fopAcM_OffStatus(this, 0x4000);
        setup_action(next_act_idx[m2ec]);
    }
}

/* 000010A8-000010AC       .text wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::wait_act_proc() {
}

/* 000010AC-000010D8       .text move_ylzou_demo_start_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_start_wait_act_init_proc() {
    m2e4 = -1;
    home.pos.set(0.0f, 0.0f, 0.0f);
    current.pos.set(0.0f, 0.0f, 0.0f);
}

/* 000010D8-00001174       .text demo_regist_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_regist_wait_act_init_proc() {
    if (m2ec != 1) {
        dComIfGp_evmng_cancelStartDemo();
        fopAcM_OnStatus(this, 0x4000);
    }
    m2e4 = dComIfGp_evmng_getEventIdx(l_demo_name[m2ec], 0xff);
    fopAcM_orderOtherEventId(this, m2e4);
}

/* 00001174-000011A4       .text move_ylzou_demo_vib_start_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_vib_start_wait_act_init_proc() {
    dComIfGs_onEventBit(0x3820);
}

/* 000011A4-0000120C       .text move_ylzou_demo_vib_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_vib_act_init_proc() {
    dComIfGp_getVibration().StartQuake(6, 1, cXyz(0.0f, 1.0f, 0.0f));
    m368 = 1;
}

/* 0000120C-00001228       .text move_ylzou_demo_move_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_move_act_init_proc() {
    m361 = 1;
    m368 = 2;
    current.angle.y = -0x8000;
}

/* 00001228-000012C8       .text demo_end_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_end_wait_act_init_proc() {
    speedF = 0.0f;
    m361 = 0;
    if (m2ec != 3) {
        dComIfGp_getVibration().StopQuake(-1);
        dComIfGp_getVibration().StartShock(8, 1, cXyz(0.0f, 1.0f, 0.0f));
    }
    m368 = 0;
}

/* 000012C8-000012F4       .text open_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::open_wait_act_init_proc() {
    home.pos.set(0.0f, 0.0f, -170.0f);
    current.pos.set(0.0f, 0.0f, -170.0f);
}

/* 000012F4-00001318       .text close_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::close_wait_act_init_proc() {
    home.pos.set(0.0f, 0.0f, 0.0f);
    current.pos.set(0.0f, 0.0f, 0.0f);
}

/* 00001318-000013A4       .text go_up_stairs_demo_move_start_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::go_up_stairs_demo_move_start_wait_act_init_proc() {
    current.angle.y = 0;
    home.pos.set(0.0f, 0.0f, 0.0f);
    current.pos.set(0.0f, 0.0f, -170.0f);
    dComIfGp_getVibration().StartQuake(6, 1, cXyz(0.0f, 1.0f, 0.0f));
    m368 = 1;
}

/* 000013A4-000013B8       .text go_up_stairs_demo_move_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::go_up_stairs_demo_move_act_init_proc() {
    m361 = 1;
    m368 = 2;
}

/* 000013B8-00001740       .text setup_action__12daObjYLzou_cFi */
void daObjYLzou_c::setup_action(int action) {
    static ActionFunc init_proc_tbl[] = {
        &daObjYLzou_c::move_ylzou_demo_start_wait_act_init_proc,
        &daObjYLzou_c::demo_regist_wait_act_init_proc,
        &daObjYLzou_c::move_ylzou_demo_vib_start_wait_act_init_proc,
        &daObjYLzou_c::move_ylzou_demo_vib_act_init_proc,
        &daObjYLzou_c::move_ylzou_demo_move_act_init_proc,
        &daObjYLzou_c::demo_end_wait_act_init_proc,
        &daObjYLzou_c::open_wait_act_init_proc,
        &daObjYLzou_c::demo_regist_wait_act_init_proc,
        &daObjYLzou_c::go_up_stairs_demo_move_start_wait_act_init_proc,
        &daObjYLzou_c::go_up_stairs_demo_move_act_init_proc,
        &daObjYLzou_c::demo_end_wait_act_init_proc,
        &daObjYLzou_c::close_wait_act_init_proc,
        &daObjYLzou_c::close_wait_act_init_proc,
        &daObjYLzou_c::demo_regist_wait_act_init_proc,
        &daObjYLzou_c::demo_end_wait_act_init_proc,
    };
    static ActionFunc proc_tbl[] = {
        &daObjYLzou_c::move_ylzou_demo_start_wait_act_proc,
        &daObjYLzou_c::demo_regist_wait_act_proc,
        &daObjYLzou_c::demo_vib_start_wait_act_proc,
        &daObjYLzou_c::demo_vib_act_proc,
        &daObjYLzou_c::move_ylzou_demo_move_act_proc,
        &daObjYLzou_c::demo_end_wait_act_proc,
        &daObjYLzou_c::wait_act_proc,
        &daObjYLzou_c::demo_regist_wait_act_proc,
        &daObjYLzou_c::demo_vib_act_proc,
        &daObjYLzou_c::go_up_stairs_demo_move_act_proc,
        &daObjYLzou_c::demo_end_wait_act_proc,
        &daObjYLzou_c::wait_act_proc,
        &daObjYLzou_c::wait_act_proc,
        &daObjYLzou_c::demo_regist_wait_act_proc,
        &daObjYLzou_c::demo_end_wait_act_proc,
    };

    (this->*init_proc_tbl[action])();
    mActProc = proc_tbl[action];
    mActionIdx = action;
}

/* 00001740-000017D4       .text _execute__12daObjYLzou_cFv */
bool daObjYLzou_c::_execute() {
    fopAcM_posMoveF(this, NULL);
    set_mtx();
    if (mBgW != NULL && mBgW->ChkUsed()) {
        mBgW->Move();
    }
    (this->*mActProc)();
    eff_smoke_proc();
    vib_proc();
    return true;
}

/* 000017D4-00001834       .text _draw__12daObjYLzou_cFv */
bool daObjYLzou_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return true;
}

/* 00001834-00001854       .text daObjYLzou_Create__FP10fopAc_ac_c */
static cPhs_State daObjYLzou_Create(fopAc_ac_c* i_this) {
    return ((daObjYLzou_c*)i_this)->_create();
}

/* 00001854-00001878       .text daObjYLzou_Delete__FP12daObjYLzou_c */
static BOOL daObjYLzou_Delete(daObjYLzou_c* i_this) {
    return ((daObjYLzou_c*)i_this)->_delete();
}

/* 00001878-0000189C       .text daObjYLzou_Execute__FP12daObjYLzou_c */
static BOOL daObjYLzou_Execute(daObjYLzou_c* i_this) {
    return ((daObjYLzou_c*)i_this)->_execute();
}

/* 0000189C-000018C0       .text daObjYLzou_Draw__FP12daObjYLzou_c */
static BOOL daObjYLzou_Draw(daObjYLzou_c* i_this) {
    return ((daObjYLzou_c*)i_this)->_draw();
}

/* 000018C0-000018C8       .text daObjYLzou_IsDelete__FP12daObjYLzou_c */
static BOOL daObjYLzou_IsDelete(daObjYLzou_c*) {
    return TRUE;
}

static actor_method_class l_daObjYLzou_Method = {
    (process_method_func)daObjYLzou_Create,
    (process_method_func)daObjYLzou_Delete,
    (process_method_func)daObjYLzou_Execute,
    (process_method_func)daObjYLzou_IsDelete,
    (process_method_func)daObjYLzou_Draw,
};

actor_process_profile_definition g_profile_Obj_YLzou = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_YLzou,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjYLzou_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_YLzou,
    /* Actor SubMtd */ &l_daObjYLzou_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
