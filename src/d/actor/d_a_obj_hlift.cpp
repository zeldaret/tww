/**
 * d_a_obj_hlift.cpp
 * Object - Wooden platforms (Pirate ship rope minigame 1)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_hlift.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_hlift.h"

namespace daObjHlift {

namespace {
    int L_time_lag_num;
    static const Attr_c L_attr = { 30.0f, 50.0f, 10.0f, 2.0f, 0.3f, 1.2f, 250.0f, 10, 16384, 2.5f, 0x00, 0x02, 0x0a, 0x08, 0x07, 0x00, 0x00, 0x00 };
}
Mtx Act_c::M_tmp_mtx;
u8 Act_c::M_lift_move_flag;
int Act_c::M_control_id = -1;
const char Act_c::M_arcname[] = "Hlift";
const char Act_c::M_evname[] = "Hlift_up";
const s16 Act_c::M_up_dist[] = { 125, 250, 375, 500, 625, 750, 875, 1000 };
const Act_c::size_data Act_c::M_data_size[2] = {
    { HLIFT_BDL_HLIFT, HLIFT_DZB_HLIFT, VERSION_SELECT(32768, 5888, 5888, 5888) },
    { HLIFT_BDL_HLIFTB, HLIFT_DZB_HLIFTB, VERSION_SELECT(32768, 5888, 5888, 5888) }
};

}

/* 00000078-000001BC       .text CreateHeap__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, M_data_size[field_0x2DC].field_0x00);
    JUT_ASSERT(288, model_data != NULL);
    mModel1 = mDoExt_J3DModel__create(model_data, 0x80000, 0x11000022);
    J3DModelData* model_data_c = (J3DModelData*)dComIfG_getObjectRes(M_arcname, HLIFT_BDL_HLIFTC);
    JUT_ASSERT(298, model_data_c != NULL);
    mModel2 = mDoExt_J3DModel__create(model_data_c, 0x80000, 0x11000022);
    return mModel1 != NULL && mModel2 != NULL;
}

/* 000001BC-000002D0       .text Create__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::Create() {
    field_0x2EC = 0.0f;
    int switchIndex = prm_get_swSave();
    if (fopAcM_isSwitch(const_cast<Act_c*>(this), switchIndex)) {
        mode_upper_init();
    } else {
        mode_lower_init();
    }
    field_0x2E4 = Mode_UNK;
    field_0x2F6 = 0;
    mEventId = dComIfGp_evmng_getEventIdx(M_evname, prm_get_evId());
    cullMtx = mModel1->getBaseTRMtx();
    init_mtx();
    fopAcM_setCullSizeBox(
        this,
        -151.0f,
        -1005.0f,
        -151.0f,
        151.0f,
        1.0f,
        151.0f
    );
    if (M_control_id == 0xffffffff) {
        M_control_id = base.base.mBsPcId;
    }
    return TRUE;
}

/* 000002D0-00000408       .text Mthd_Create__Q210daObjHlift5Act_cFv */
cPhs_State daObjHlift::Act_c::Mthd_Create() {
    fopAcM_ct(this, daObjHlift::Act_c);
    cPhs_State phase_state = dComIfG_resLoad(&mPhase, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        field_0x2D8 = prm_get_dist();
        field_0x2DC = prm_get_size();
        phase_state = MoveBGCreate(
            M_arcname,
            M_data_size[field_0x2DC].field_0x01,
            dBgS_MoveBGProc_TypicalRotY,
            *(int*)&M_data_size[field_0x2DC].field_0x02
        );
        JUT_ASSERT(366, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 00000408-00000430       .text Delete__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::Delete() {
    if (M_control_id == base.base.mBsPcId) {
        M_control_id = -1;
    }
    return TRUE;
}

/* 00000430-0000047C       .text Mthd_Delete__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::Mthd_Delete() {
    u32 result = MoveBGDelete();
    dComIfG_resDeleteDemo(&mPhase, M_arcname);
    return result;
}

/* 0000047C-00000490       .text mode_lower_init__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_lower_init() {
    current.pos.y = home.pos.y;
    field_0x2E0 = 0;
}

/* 00000490-000004F0       .text mode_lower__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_lower() {
    int switchIndex = prm_get_swSave();
    if (fopAcM_isSwitch(const_cast<Act_c*>(this), switchIndex)) {
        mode_demoreq_init(Mode_L_U);
    }
}

/* 000004F0-000005B8       .text mode_l_u_init__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_l_u_init() {
    vib_set();
    field_0x2F0 = 0.0f;
    field_0x2E0 = 1;
    fopAcM_seStart(this, JA_SE_OBJ_PRT_LIFT_UD, 0);
    field_0x2F4 = L_attr.field_0x24[L_time_lag_num];
    L_time_lag_num++;
    L_time_lag_num %= 5;
}

/* 000005B8-00000724       .text mode_l_u__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_l_u() {
    /* Nonmatching */
    if (field_0x2F4 > 0) {
        field_0x2F4--;
    } else {
        float fVar1 = current.pos.y - home.pos.y;
        if (fVar1 < L_attr.field_0x04) {
            cLib_chaseF(&field_0x2F0, L_attr.field_0x08, L_attr.field_0x10);
        } else {
            if (M_up_dist[field_0x2D8] - L_attr.field_0x04 > fVar1) {
                field_0x2F0 = L_attr.field_0x08;
            } else {
                cLib_chaseF(&field_0x2F0, L_attr.field_0x0C, L_attr.field_0x14);
            }
        }
        int iVar2 = cLib_chaseF(&current.pos.y, home.pos.y + M_up_dist[field_0x2D8], field_0x2F0);
        if (iVar2 != 0) {
            vib_set();
            fopAcM_seStart(this, JA_SE_OBJ_PRT_LIFT_STOP, 0);
            mode_upper_init();
        }
    }
}

/* 00000724-00000778       .text mode_upper_init__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_upper_init() {
    current.pos.y = home.pos.y + M_up_dist[field_0x2D8];
    field_0x2E0 = 2;
}

/* 00000778-000007D8       .text mode_upper__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_upper() {
    int switchIndex = prm_get_swSave();
    if (!fopAcM_isSwitch(const_cast<Act_c*>(this), switchIndex)) {
        mode_demoreq_init(Mode_U_L);
    }
}

/* 000007D8-000008A0       .text mode_u_l_init__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_u_l_init() {
    vib_set();
    field_0x2F0 = 0.0f;
    fopAcM_seStart(this, JA_SE_OBJ_PRT_LIFT_UD, 0);
    field_0x2F4 = L_attr.field_0x24[L_time_lag_num];
    L_time_lag_num++;
    L_time_lag_num %= 5;
    field_0x2E0 = 3;
}

/* 000008A0-000009DC       .text mode_u_l__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_u_l() {
    /* Nonmatching */
    if (field_0x2F4 > 0) {
        field_0x2F4--;
    } else {
        float fVar1 = current.pos.y - home.pos.y;
        if (fVar1 < L_attr.field_0x04) {
            cLib_chaseF(&field_0x2F0, L_attr.field_0x0C, L_attr.field_0x14);
        } else {
            if (M_up_dist[field_0x2D8] - L_attr.field_0x04 > fVar1) {
                field_0x2F0 = L_attr.field_0x08;
            } else {
                cLib_chaseF(&field_0x2F0, L_attr.field_0x08, L_attr.field_0x10);
            }
        }
        int iVar2 = cLib_chaseF(&current.pos.y, home.pos.y, field_0x2F0);
        if (iVar2 != 0) {
            vib_set();
            fopAcM_seStart(this, JA_SE_OBJ_PRT_LIFT_STOP, 0);
            mode_lower_init();
        }
    }
}

/* 000009DC-00000AB0       .text mode_demoreq_init__Q210daObjHlift5Act_cFQ310daObjHlift5Act_c6Mode_e */
void daObjHlift::Act_c::mode_demoreq_init(daObjHlift::Act_c::Mode_e next) {
    JUT_ASSERT(575, (next == Mode_U_L) || (next == Mode_L_U));
    field_0x2E4 = next;
    field_0x2F6 = 0;
    fopAcM_orderOtherEventId(this, mEventId, prm_get_evId());
    eventInfo.onCondition(dEvtCnd_UNK2_e);
    field_0x2E0 = 4;
}

/* 00000AB0-00000B28       .text mode_demoreq__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::mode_demoreq() {
    if (dComIfGp_evmng_existence(mEventId) && eventInfo.checkCommandDemoAccrpt()) {
        field_0x2F6 = 1;
    }
    if (field_0x2E4 == 3) {
        mode_u_l_init();
    } else {
        mode_l_u_init();
    }
}

/* 00000B28-00000BE8       .text set_mtx__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::set_mtx() {
    float fVar1 = current.pos.y + field_0x2EC;
    mDoMtx_stack_c::transS(current.pos.x, fVar1 + L_attr.field_0x00, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mModel1->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
    mDoMtx_stack_c::transS(home.pos);
    mModel2->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000BE8-00000C40       .text init_mtx__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::init_mtx() {
    mModel1->setBaseScale(scale);
    mModel2->setBaseScale(scale);
    set_mtx();
}

/* 00000C40-00000C8C       .text rot_set__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::rot_set() {
    float fVar1 = current.pos.y - home.pos.y;
    float fVar2 = (65536.0f/L_attr.field_0x18);
    shape_angle.y = -(s16)(int)(fVar1 * fVar2);
}

/* 00000C8C-00000CA8       .text vib_set__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::vib_set() {
    field_0x2E8 = L_attr.field_0x1C;
    field_0x2EA = 16384;
}

/* 00000CA8-00000D70       .text vib_proc__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::vib_proc() {
    if (field_0x2E8 > 0) {
        float fVar1 = (L_attr.field_0x1C - field_0x2E8);
        field_0x2EC = (L_attr.field_0x20 * (0.5f + fVar1 * (0.5f / L_attr.field_0x1C))) * cM_ssin(field_0x2EA);
        field_0x2EA += L_attr.field_0x1E;
        field_0x2E8--;
    } else {
        field_0x2EC = 0.0f;
    }
}

/* 00000D70-00000DE8       .text chk_demo_end__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::chk_demo_end() {
    /* Nonmatching */
    if (field_0x2F6 != 0 && dComIfGp_evmng_endCheck(mEventId)) {
        dComIfGp_event_reset();
        field_0x2F6 = 0;
    }
    return field_0x2F6 == 0;
}

/* 00000DE8-00000E74       .text se_whole__Q210daObjHlift5Act_cFv */
void daObjHlift::Act_c::se_whole() {
    if (M_control_id == base.base.mBsPcId && M_lift_move_flag != 0) {
        mDoAud_seStart(JA_SE_OBJ_PRT_LIFT_WORK);
        M_lift_move_flag = 0;
    }
}

/* 00000E74-00000FD4       .text Execute__Q210daObjHlift5Act_cFPPA3_A4_f */
BOOL daObjHlift::Act_c::Execute(Mtx** param_1) {
    /* Nonmatching */
    typedef void (daObjHlift::Act_c::*procFunc)();
    static procFunc mode_proc[] = {
        &daObjHlift::Act_c::mode_lower,
        &daObjHlift::Act_c::mode_l_u,
        &daObjHlift::Act_c::mode_upper,
        &daObjHlift::Act_c::mode_u_l,
        &daObjHlift::Act_c::mode_demoreq
    };
    chk_demo_end();

    (this->*mode_proc[field_0x2E0])();

    if (field_0x2E0 == 1 || field_0x2E0 == 3 || field_0x2E0 == 4) {
        M_lift_move_flag = 1;
    }
    rot_set();
    vib_proc();
    se_whole();
    eyePos = current.pos;
    set_mtx();
    *param_1 = &M_tmp_mtx;
    return TRUE;
}

/* 00000FD4-00001090       .text Draw__Q210daObjHlift5Act_cFv */
BOOL daObjHlift::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel1, &tevStr);
    g_env_light.setLightTevColorType(mModel2, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mModel1);
    mDoExt_modelUpdateDL(mModel2);
    dComIfGd_setList();
    return TRUE;
}

namespace daObjHlift {
namespace {
/* 00001090-000010B0       .text Mthd_Create__Q210daObjHlift27@unnamed@d_a_obj_hlift_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjHlift::Act_c*)i_this)->Mthd_Create();
}

/* 000010B0-000010D0       .text Mthd_Delete__Q210daObjHlift27@unnamed@d_a_obj_hlift_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjHlift::Act_c*)i_this)->Mthd_Delete();
}

/* 000010D0-000010F0       .text Mthd_Execute__Q210daObjHlift27@unnamed@d_a_obj_hlift_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjHlift::Act_c*)i_this)->MoveBGExecute();
}

/* 000010F0-0000111C       .text Mthd_Draw__Q210daObjHlift27@unnamed@d_a_obj_hlift_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjHlift::Act_c*)i_this)->MoveBGDraw();
}

/* 0000111C-00001148       .text Mthd_IsDelete__Q210daObjHlift27@unnamed@d_a_obj_hlift_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjHlift::Act_c*)i_this)->MoveBGIsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjHlift

actor_process_profile_definition g_profile_Obj_Hlift = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Hlift,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHlift::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Hlift,
    /* Actor SubMtd */ &daObjHlift::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
