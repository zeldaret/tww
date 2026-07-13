/**
 * d_a_obj_YLzou.cpp
 * Object - Hyrule Castle - Link statue
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_YLzou.h"
#include "res/Object/YLzou.h"

typedef enum {
    ENUM_ONE_UNK_0000 = 0x0000,
    ENUM_ONE_UNK_0006 = 0x0006,
    ENUM_ONE_UNK_0007 = 0x0007,
    ENUM_ONE_UNK_000B = 0x000B,
    ENUM_ONE_UNK_000C = 0x000C,
    ENUM_ONE_UNK_000D = 0x000D
} UNK_YLZOU_ENUM_ONE;

typedef enum { ENUM_TWO_UNK_0000 = 0x0000, ENUM_TWO_UNK_0001 = 0x0001, ENUM_TWO_UNK_0002 = 0x0002, ENUM_TWO_UNK_0003 = 0x0003 } UNK_YLZOU_ENUM_TWO;

namespace {
static const char l_arcname[] = "YLzou";
static const char l_move_ylzou_demo_name[] = "move_YLzou";
static const char l_go_up_stairs_demo_name[] = "go_up_stairs";
static const char l_go_up_stairs_demo2_name[] = "go_up_stairs2";
static char* l_demo_name[4] = {NULL, (char*)l_move_ylzou_demo_name, (char*)l_go_up_stairs_demo_name, (char*)l_go_up_stairs_demo2_name};
} // namespace

/* 000000EC-000002B8       .text set_start_type__12daObjYLzou_cFv */
void daObjYLzou_c::set_start_type() {
    UNK_YLZOU_ENUM_ONE unk_ylzou_enum_one;
    BOOL triforce_complete;
    UNK_YLZOU_ENUM_TWO unk_ylzou_enum_two;
    bool event_bit_3820;

    triforce_complete = FALSE;
    unk_ylzou_enum_two = ENUM_TWO_UNK_0000;
    event_bit_3820 = false;
    if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D04) == FALSE) {
        if (field_0x2E0 != 0xFF && !fopAcM_isSwitch(this, field_0x2E0)) {
            unk_ylzou_enum_one = ENUM_ONE_UNK_0000;
            unk_ylzou_enum_two = ENUM_TWO_UNK_0001;
        } else {
            unk_ylzou_enum_one = ENUM_ONE_UNK_0006;
            event_bit_3820 = true;
        }
    } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3A04) == FALSE) {
        unk_ylzou_enum_one = ENUM_ONE_UNK_0006;
        event_bit_3820 = true;
    } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3804) == FALSE) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3820) == TRUE) {
            unk_ylzou_enum_one = ENUM_ONE_UNK_0007;
            unk_ylzou_enum_two = ENUM_TWO_UNK_0002;
        } else {
            unk_ylzou_enum_one = ENUM_ONE_UNK_000B;
        }
    } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2D02) == FALSE) {
        unk_ylzou_enum_one = ENUM_ONE_UNK_0006;
        event_bit_3820 = true;
    } else if (dComIfGs_getTriforceNum() < 8) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3820) == TRUE) {
            unk_ylzou_enum_one = ENUM_ONE_UNK_0007;
            unk_ylzou_enum_two = ENUM_TWO_UNK_0002;
        } else {
            unk_ylzou_enum_one = ENUM_ONE_UNK_000B;
        }
    } else {
        triforce_complete = TRUE;
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_2C01) == FALSE) {
            unk_ylzou_enum_one = ENUM_ONE_UNK_000C;
        } else if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_3980) == FALSE) {
            unk_ylzou_enum_one = ENUM_ONE_UNK_000D;
            unk_ylzou_enum_two = ENUM_TWO_UNK_0003;
        } else {
            unk_ylzou_enum_one = ENUM_ONE_UNK_000C;
        }
    }

    field_0x2DC = unk_ylzou_enum_one;
    field_0x2E8 = triforce_complete;
    field_0x2EC = unk_ylzou_enum_two;
    if (!event_bit_3820) {
        dComIfGs_offEventBit(dSv_event_flag_c::UNK_3820);
    } else {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_3820);
    }
}

/* 000002B8-00000374       .text set_mtx__12daObjYLzou_cFv */
void daObjYLzou_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + field_0x35C * cM_ssin(field_0x358), current.pos.z);
    mDoMtx_stack_c::XYZrotM(shape_angle);
    field_0x298->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::scaleM(scale);
    MTXCopy(mDoMtx_stack_c::get(), field_0x2A0);
}

/* 00000374-000003B0       .text init_mtx__12daObjYLzou_cFv */
void daObjYLzou_c::init_mtx() {
    field_0x298->setBaseScale(scale);
    set_mtx();
}

/* 000003B0-000003D4       .text solidHeapCB__12daObjYLzou_cFP10fopAc_ac_c */
BOOL daObjYLzou_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjYLzou_c*)i_this)->create_heap();
}

/* 000003D4-000004F4       .text create_heap__12daObjYLzou_cFv */
bool daObjYLzou_c::create_heap() {
    /* Nonmatching */
    J3DModelData* model_data;
    J3DModel* model;
    dBgW* bgw;
    bool res;

    static s32 bdl_table[] = {dRes_INDEX_YLZOU_BDL_YLZOU_e, dRes_INDEX_YLZOU_BDL_YLZOU2_e};

    static s32 dzb_table[] = {dRes_INDEX_YLZOU_DZB_YLZOU_e, dRes_INDEX_YLZOU_DZB_YLZOU2_e};

    res = true;
    model_data = (J3DModelData*)dComIfG_getObjectRes(l_arcname, bdl_table[field_0x2E8]);

    if (model_data == NULL) {
        JUT_ASSERT(0x198, FALSE);
        res = false;
    } else {
        model = mDoExt_J3DModel__create(model_data, 0x80000, 0x11000022);
        field_0x298 = model;
        model = field_0x298;
        bgw = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, dzb_table[field_0x2E8]), cBgW::MOVE_BG_e, &model->getBaseTRMtx());
        field_0x29C = bgw;
        if (field_0x298 == NULL || field_0x29C == NULL) {
            res = false;
        }
    }

    return res;
}

/* 000004F4-00000668       .text eff_set_slip_smoke_pos__12daObjYLzou_cFv */
void daObjYLzou_c::eff_set_slip_smoke_pos() {
    /* Nonmatching */
    static cXyz positions[2] = {cXyz(0xC3700000, 0.0f, 0xC3700000), cXyz(0x43700000, 0.0f, 0xC3700000)};

    f32 new_y = current.pos.y + -1550;
    f32 new_z = current.pos.z + -1200;
    mDoMtx_stack_c::transS(current.pos.x, new_y, new_z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); ++i) {
        mDoMtx_stack_c::push();
        mDoMtx_stack_c::transM(positions[i]);
        mDoMtx_multVecZero(mDoMtx_stack_c::get(), &mSmokeCbs[i].field_0x20);
        mSmokeCbs[i].field_0x2C.set(0, current.angle.y, 0);
        mDoMtx_stack_c::pop();
    }
}

/* 000006A4-000007AC       .text eff_smoke_slip_start__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_slip_start() {
    /* Nonmatching */
    static cXyz scl(0x40000000, 0x40000000, 0x40000000);

    eff_set_slip_smoke_pos();
    for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); ++i) {
        JPABaseEmitter* emitter = dComIfGp_particle_setToon(
            dPa_name::ID_AK_JT_ELEMENTSMOKE00,
            &mSmokeCbs[i].field_0x20,
            &mSmokeCbs[i].field_0x2C,
            &scl,
            0xb9,
            &mSmokeCbs[i],
            fopAcM_GetRoomNo(this),
            NULL,
            NULL,
            NULL
        );
        if (emitter != NULL) {
            emitter->setRate(2.0);
            emitter->setDirectionalSpeed(15.0);
            emitter->setSpread(0.15);
            emitter->setLifeTime(0x1e);
        }
    }
}

/* 000007AC-0000080C       .text eff_smoke_slip_end__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_slip_end() {
    for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); ++i) {
        mSmokeCbs[i].remove();
    }
}

/* 0000080C-0000086C       .text eff_smoke_slip_remove__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_slip_remove() {
    for (int i = 0; i < (int)ARRAY_SIZE(mSmokeCbs); ++i) {
        mSmokeCbs[i].remove();
    }
}

/* 0000086C-000008D0       .text eff_smoke_proc__12daObjYLzou_cFv */
void daObjYLzou_c::eff_smoke_proc() {
    if (field_0x360 != field_0x361) {
        if (field_0x361 == 1) {
            eff_smoke_slip_start();
        } else {
            eff_smoke_slip_end();
        }
        field_0x360 = field_0x361;
    } else {
        if (field_0x360 == 1) {
            eff_set_slip_smoke_pos();
        }
    }
}

/* 000008D0-000009A4       .text vib_proc__12daObjYLzou_cFv */
void daObjYLzou_c::vib_proc() {
    /* Nonmatching */

    if (field_0x364 != field_0x368) {
        field_0x364 = field_0x368;
    }

    switch (field_0x364) {
        case 1:
            field_0x358 += 0x4000;
            field_0x35C += 0.05f;
            if (field_0x35C > 0.8f) {
                field_0x35C = 0.8f;
            }
            break;
        case 2:
            field_0x358 += 0x4000;
            field_0x35C -= 0.05f;
            if (field_0x35C < 0.4f) {
                field_0x35C = 0.4f;
            }
            break;
        default:
            field_0x358 += 0x4000;
            field_0x35C -= 0.1f;
            if (field_0x35C < 0.0f) {
                field_0x35C = 0.0f;
            }
            break;
    }
}

/* 000009A4-00000AE0       .text _create__12daObjYLzou_cFv */
cPhs_State daObjYLzou_c::_create() {
    static u32 solidHeapSize_table[] = {0x5840, 0x49e0};

    cPhs_State cphs_state;

    fopAcM_ct(this, daObjYLzou_c);
    if (fpcM_IsFirstCreating(this)) {
        field_0x2E0 = param_get_swSave();
        set_start_type();
    }
    cphs_state = dComIfG_resLoad(&field_0x290, l_arcname);
    if (cphs_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, solidHeapSize_table[field_0x2E8])) {
            if (dComIfG_Bgsp()->Regist(field_0x29C, this)) {
                cphs_state = cPhs_ERROR_e;
            } else {
                fopAcM_SetMtx(this, field_0x298->getBaseTRMtx());
                setup_action(field_0x2DC);
                init_mtx();
            }
        } else {
            cphs_state = cPhs_ERROR_e;
        }
    }
    return cphs_state;
}

/* 00000AE0-00000B7C       .text _delete__12daObjYLzou_cFv */
bool daObjYLzou_c::_delete() {
    /* Nonmatching */
}

/* 00000B7C-00000BD8       .text move_ylzou_demo_start_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_start_wait_act_proc() {
    if (field_0x2E0 != 0xFF) {
        // == TRUE required for 100% match
        if (fopAcM_isSwitch(this, field_0x2E0) == TRUE) {
            setup_action(1);
        }
    }
}

/* 00000BD8-00000C70       .text demo_regist_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_regist_wait_act_proc() {
    if (field_0x2E4 != -1) {
        if (eventInfo.checkCommandDemoAccrpt()) {
            setup_action(field_0x2DC + 1);
            return;
        }
        fopAcM_orderOtherEventId(this, field_0x2E4);
        return;
    }
    field_0x2E4 = dComIfGp_evmng_getEventIdx(l_demo_name[field_0x2EC]);
}

/* 00000C70-00000D18       .text demo_vib_start_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_vib_start_wait_act_proc() {
    if (dComIfGp_evmng_existence(field_0x2E4)) {
        int staff_idx = dComIfGp_evmng_getMyStaffId("YLzou", NULL, 0);
        if (staff_idx != -1) {
            if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staff_idx), "Vibrate") == 0) {
                setup_action(field_0x2DC + 1);
            }
        }
    }
}

/* 00000D18-00000E08       .text demo_vib_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_vib_act_proc() {
    /* Nonmatching */
    dEvDtEvent_c* event_data = dComIfGp_getPEvtManager()->getEventData(field_0x2E4);
    if (event_data != NULL) {
        int staff_idx = dComIfGp_evmng_getMyStaffId("YLzou", NULL, 0);
        if (staff_idx != -1) {
            if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staff_idx), "Move") == 0) {
                setup_action(field_0x2DC + 1);
            }
        }
    }
    fopAcM_seStartCurrent(this, JA_SE_OBJ_H_STATUE_VIB, 0);
}

/* 00000E08-00000F0C       .text move_ylzou_demo_move_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_move_act_proc() {
    /* Nonmatching */
    if (current.pos.z < home.pos.z + -680) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_H_STATUE_STOP, 0);
        setup_action(5);
    } else {
        speedF += 0.1f;
        if (speedF > 6) {
            speedF = 6;
        }
        fopAcM_seStartCurrent(this, JA_SE_OBJ_H_STATUE_MOVE, 0);
    }
}

/* 00000F0C-00001008       .text go_up_stairs_demo_move_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::go_up_stairs_demo_move_act_proc() {
    /* Nonmatching */
    if (current.pos.z > home.pos.z) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_H_STATUE_STOP, 0);
        setup_action(10);
    } else {
        speedF += 0.1f;
        if (speedF > 6) {
            speedF = 6;
        }

        fopAcM_seStartCurrent(this, JA_SE_OBJ_H_STATUE_MOVE, 0);
    }
}

/* 00001008-000010A8       .text demo_end_wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_end_wait_act_proc() {
    /* Nonmatching */
    static int next_act_idx[4] = {-1, 6, 11, 12};

    if (dComIfGp_evmng_endCheck(field_0x2E4)) {
        dComIfGp_event_reset();
        if (field_0x2DC == 0xE) {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_3980);
        }
        fopAcM_OffStatus(this, fopAcStts_UNK4000_e);
        setup_action(next_act_idx[field_0x2EC]);
    }
}

/* 000010A8-000010AC       .text wait_act_proc__12daObjYLzou_cFv */
void daObjYLzou_c::wait_act_proc() {
    return;
}

/* 000010AC-000010D8       .text move_ylzou_demo_start_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_start_wait_act_init_proc() {
    /* Nonmatching */
    field_0x2E4 = -1;
    home.pos.x = 0.0;
    home.pos.y = 0.0;
    home.pos.z = 0.0;
    current.pos.x = 0.0;
    current.pos.y = 0.0;
    current.pos.z = 0.0;
}

/* 000010D8-00001174       .text demo_regist_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_regist_wait_act_init_proc() {
    if (field_0x2EC != 1) {
        dComIfGp_evmng_cancelStartDemo();
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
    }

    field_0x2E4 = dComIfGp_evmng_getEventIdx(l_demo_name[field_0x2EC]);
    fopAcM_orderOtherEventId(this, field_0x2E4, 0xFF, 0xFFFF, 0, 1);
}

/* 00001174-000011A4       .text move_ylzou_demo_vib_start_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_vib_start_wait_act_init_proc() {
    dComIfGs_onEventBit(dSv_event_flag_c::UNK_3820);
}

/* 000011A4-0000120C       .text move_ylzou_demo_vib_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_vib_act_init_proc() {
    /* Nonmatching */
    dComIfGp_getVibration().StartQuake(6, 1, cXyz(0, 1, 0));
    field_0x368 = 1;
    return;
}

/* 0000120C-00001228       .text move_ylzou_demo_move_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::move_ylzou_demo_move_act_init_proc() {
    field_0x361 = 1;
    field_0x368 = 2;
    current.angle.y = SHRT_MIN;
}

/* 00001228-000012C8       .text demo_end_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::demo_end_wait_act_init_proc() {
    /* Nonmatching */
    speedF = 0.0;
    field_0x361 = 0;
    if (field_0x2EC != 3) {
        dComIfGp_getVibration().StopQuake(-1);
        dComIfGp_getVibration().StartShock(8, 1, cXyz(0, 1, 0));
    }
    field_0x368 = 0;
}

/* 000012C8-000012F4       .text open_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::open_wait_act_init_proc() {
    /* Nonmatching */
    home.pos.x = 0.0;
    home.pos.y = 0.0;
    home.pos.z = -680.0;
    current.pos.x = 0.0;
    current.pos.y = 0.0;
    current.pos.z = -680.0;
}

/* 000012F4-00001318       .text close_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::close_wait_act_init_proc() {
    /* Nonmatching */
    home.pos.x = 0.0;
    home.pos.y = 0.0;
    home.pos.z = 0.0;
    current.pos.x = 0.0;
    current.pos.y = 0.0;
    current.pos.z = 0.0;
}

/* 00001318-000013A4       .text go_up_stairs_demo_move_start_wait_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::go_up_stairs_demo_move_start_wait_act_init_proc() {
    /* Nonmatching */
    current.angle.y = 0;
    home.pos.set(0, 0, 0);
    current.pos.set(0, 0, -680);

    dComIfGp_getVibration().StartQuake(6, 1, cXyz(0, 1, 0));
    field_0x368 = 1;
    return;
}

/* 000013A4-000013B8       .text go_up_stairs_demo_move_act_init_proc__12daObjYLzou_cFv */
void daObjYLzou_c::go_up_stairs_demo_move_act_init_proc() {
    field_0x361 = 1;
    field_0x368 = 2;
}

/* 000013B8-00001740       .text setup_action__12daObjYLzou_cFi */
void daObjYLzou_c::setup_action(int) {
    /* Nonmatching */
}

/* 00001740-000017D4       .text _execute__12daObjYLzou_cFv */
bool daObjYLzou_c::_execute() {
    fopAcM_posMoveF(this, NULL);
    set_mtx();
    if (field_0x29C != NULL) {
        int id = field_0x29C->GetId();
        bool to_move;
        if ((id >= 0) && (id < 0x100)) {
            to_move = true;
        } else {
            to_move = false;
        }

        if (to_move) {
            field_0x29C->Move();
        }
    }
    (this->*field_0x2D0)();
    eff_smoke_proc();
    vib_proc();
    return true;
}

/* 000017D4-00001834       .text _draw__12daObjYLzou_cFv */
bool daObjYLzou_c::_draw() {
    /* Nonmatching */
    g_env_light.settingTevStruct(TEV_TYPE_BG0_PLIGHT, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(field_0x298, &tevStr);
    mDoExt_modelUpdateDL(field_0x298);
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
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_YLzou_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjYLzou_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_YLzou_e,
    /* Actor SubMtd */ &l_daObjYLzou_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
