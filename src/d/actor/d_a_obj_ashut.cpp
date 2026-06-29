/**
 * d_a_obj_ashut.cpp
 * Object - Metal bars (Pirate Ship rope minigame)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ashut.h"
#include "res/Object/Ashut.h"

namespace daObjAshut {
namespace {
const Attr_c L_attr = {
    250.0f,
    -2.5f,
    0.05f,
    5,
    -0.5f,
    7.0f,
    0.8f,
    0.1f,
    0.4f,
    { 14, 4, 5 },
    -0.6f,
    -4.0f,
};

inline static const Attr_c& attr() { return L_attr; }
}
}

const char daObjAshut::Act_c::M_arcname[] = "Ashut";
Mtx daObjAshut::Act_c::M_tmp_mtx;

static const f32 l_anti_crush_safe_area_y = 100.0f;
static const f32 l_anti_crush_safe_area_z = 55.0f;
static const f32 l_anti_crush_safe_area_x = 105.0f;

static const f32 l_bgw_release_height = 150.0f;

/* 00000078-0000012C       .text CreateHeap__Q210daObjAshut5Act_cFv */
BOOL daObjAshut::Act_c::CreateHeap() {
    J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_ASHUT_BDL_ASHUT_e);
    JUT_ASSERT(0xf9, mdl_data != NULL);
    mpModel = mDoExt_J3DModel__create(mdl_data, 0x80000, 0x11000022);
    return mpModel != NULL;
}

/* 0000012C-00000224       .text Create__Q210daObjAshut5Act_cFv */
BOOL daObjAshut::Act_c::Create() {
    mpBgW->SetPriority((cBgW::PRIORITY)1);
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    init_mtx();
    fopAcM_setCullSizeBox(this, -80.0f, -5.0f, -30.0f, 80.0f, 250.0f, 30.0f);
    mIsEventReady = false;
    mEventId = dComIfGp_evmng_getEventIdx(NULL, prm_get_evId());
    mNextMode = Mode_Initial;

    if(is_switch()) {
        mode_upper_init();
    } else {
        mode_lower_init();
    }
    return TRUE;
}

/* 00000224-00000388       .text Mthd_Create__Q210daObjAshut5Act_cFv */
cPhs_State daObjAshut::Act_c::Mthd_Create() {
    fopAcM_ct(this, daObjAshut::Act_c);
    cPhs_State phase_state = (cPhs_State)dComIfG_resLoad(&mPhase, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = (cPhs_State)MoveBGCreate(M_arcname, 7, NULL, DEMO_SELECT(0x8000, 0x760));
        JUT_ASSERT(312, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
        
        // If switch is active on load, ensure collision is disabled so player can pass
        if (is_switch()) {
            if (mpBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgW);
            }
        }
    }
    return phase_state;
}

/* 00000388-00000390       .text Delete__Q210daObjAshut5Act_cFv */
BOOL daObjAshut::Act_c::Delete() {
    return TRUE;
}

/* 00000390-000003DC       .text Mthd_Delete__Q210daObjAshut5Act_cFv */
BOOL daObjAshut::Act_c::Mthd_Delete() {
    BOOL result = MoveBGDelete();
    dComIfG_resDeleteDemo(&mPhase, M_arcname);
    return result;
}

/* 000003DC-0000046C       .text set_mtx__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
    mDoMtx_stack_c::get()[1][3] += mCurrentY;
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 0000046C-000004A8       .text init_mtx__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 000004A8-000005A4       .text chk_safe_area__Q210daObjAshut5Act_cCFv */
bool daObjAshut::Act_c::chk_safe_area() const {
    // Prevents the metal bars from closing and crushing Link if he is standing directly underneath

    s16 inv_angle = -shape_angle.y;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz diff = player->current.pos - current.pos;
    cXyz local_pos;
    
    mDoMtx_stack_c::YrotS(inv_angle);
    mDoMtx_stack_c::multVecSR(&diff, &local_pos);
    
    return (
        std::fabsf(local_pos.y) < l_anti_crush_safe_area_y
        && std::fabsf(local_pos.z) < l_anti_crush_safe_area_z
        && std::fabsf(local_pos.x) < l_anti_crush_safe_area_x
    );
}

/* 000005A4-000005BC       .text mode_upper_init__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_upper_init() {
    mMode = Mode_U;
    mCurrentY = attr().open_max_y;
}

/* 000005BC-0000066C       .text mode_upper__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_upper() {
    if (is_switch()) {
        return; // Stay open
    }
    if (chk_safe_area()) {
        return; // Stay open: player is underneath
    }
    
    // Metal bars gonna fall. Re-enable collision
    if (!mpBgW->ChkUsed()) {
        dComIfG_Bgsp()->Regist(mpBgW, this);
    }
    mode_demoreq_init(Mode_U_L);
}

/* 0000066C-00000700       .text mode_u_l_init__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_u_l_init() {
    mMode = Mode_U_L;
    mSpeedY = 0.0f;
    mBounceCount = attr().close_bounce_count;
    fopAcM_seStart(this, JA_SE_OBJ_P_SHIP_SHTR_CL, 0);
}

/* 00000700-000007C0       .text mode_u_l__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_u_l() {
    mSpeedY += attr().close_accel;
    mSpeedY *= (1.0f - attr().close_damping);
    mCurrentY += mSpeedY;
    
    if (mCurrentY <= 0.0f) {
        if (mBounceCount == 0) {
            mode_lower_init();
        } else {
            mBounceCount--;
            mCurrentY *= attr().close_bounce_factor;
            mSpeedY *= attr().close_bounce_factor;
            if (mSpeedY > attr().max_close_bounce_vel) {
                mSpeedY = attr().max_close_bounce_vel;
            }
        }
    }
}

/* 000007C0-000007D8       .text mode_lower_init__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_lower_init() {
    mMode = Mode_L;
    mCurrentY = 0.0f;
}

/* 000007D8-00000838       .text mode_lower__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_lower() {
    if (is_switch()) {
        mode_demoreq_init(Mode_L_U);
    }
}

/* 00000838-000008D4       .text mode_l_u_init__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_l_u_init() {
    mMode = Mode_L_U;
    mSpeedY = 0.0f;
    mBounceCount = attr().open_timer_params[2];
    mDelayTimer = attr().open_timer_params[0];
    fopAcM_seStart(this, JA_SE_OBJ_P_SHIP_SHTR_OP, 0);
}

/* 000008D4-00000A50       .text mode_l_u__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_l_u() {
    if (mDelayTimer > 0) {
        mDelayTimer--;
    }
    
    mSpeedY += attr().open_accel;
    
    if (mDelayTimer > 0 && mDelayTimer < attr().open_timer_params[1]) {
        mSpeedY *= (1.0f - attr().open_heavy_damping);
    } else {
        mSpeedY *= (1.0f - attr().open_damping);
    }
    mCurrentY += mSpeedY;
     
    if (mCurrentY > l_bgw_release_height) {
        // Disable the collision so the player can pass
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
        }
    }

    if (mCurrentY >= attr().open_max_y) {
        if (mBounceCount == 0) {
            mode_upper_init();
        } else {
            mBounceCount--;
            f32 diff = mCurrentY - attr().open_max_y;
            mCurrentY = attr().open_max_y + (diff * attr().open_bounce_factor);
            mSpeedY *= attr().open_bounce_factor;

            if (mSpeedY < attr().max_open_bounce_vel) {
                mSpeedY = attr().max_open_bounce_vel;
            }
        }
    }
}

/* 00000A50-00000B0C       .text mode_demoreq_init__Q210daObjAshut5Act_cFQ310daObjAshut5Act_c6Mode_e */
void daObjAshut::Act_c::mode_demoreq_init(daObjAshut::Act_c::Mode_e i_demo_next) {
    JUT_ASSERT(DEMO_SELECT(544, 546), (i_demo_next == Mode_U_L) || (i_demo_next == Mode_L_U));
    
    if (mIsEventReady) {
        if (i_demo_next == Mode_U_L) {
            mode_u_l_init();
        } else {
            mode_l_u_init();
        }
    } else {
        mMode = Mode_DemoReq;
        mNextMode = i_demo_next;
    }
}

/* 00000B0C-00000BE4       .text mode_demoreq__Q210daObjAshut5Act_cFv */
void daObjAshut::Act_c::mode_demoreq() {
    bool is_demo_ready = false;
    if (dComIfGp_evmng_existence(mEventId)) {
        if (eventInfo.checkCommandDemoAccrpt()) {
            is_demo_ready = true;
            mIsEventReady = true;
        } else {
            fopAcM_orderOtherEventId(this, mEventId, prm_get_evId(), 0xFFFF, 0, 1);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
    } else {
        is_demo_ready = true;
    }
    
    if (is_demo_ready) {
        if (mNextMode == Mode_U_L) {
            mode_u_l_init();
        } else {
            mode_l_u_init();
        }
    }
}

/* 00000BE4-00000D0C       .text Execute__Q210daObjAshut5Act_cFPPA3_A4_f */
BOOL daObjAshut::Act_c::Execute(Mtx** pMtx) {
    typedef void(Act_c::*ModeProcFunc)();
    static const ModeProcFunc mode_proc[] = {
        &Act_c::mode_upper,
        &Act_c::mode_u_l,
        &Act_c::mode_lower,
        &Act_c::mode_l_u,
        &Act_c::mode_demoreq
    };
    
    (this->*mode_proc[mMode])();

    f32 eyeZ = current.pos.z;
    f32 eyeY = current.pos.y + mCurrentY;

    eyePos.set(current.pos.x, eyeY, eyeZ);
    
    set_mtx();
    *pMtx = &M_tmp_mtx;
    return TRUE;
}

/* 00000D0C-00000D6C       .text Draw__Q210daObjAshut5Act_cFv */
BOOL daObjAshut::Act_c::Draw() {
    g_env_light.settingTevStruct(1, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return TRUE;
}

namespace daObjAshut {
namespace {
/* 00000D6C-00000D8C       .text Mthd_Create__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjAshut::Act_c*)i_this)->Mthd_Create();
}

/* 00000D8C-00000DAC       .text Mthd_Delete__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjAshut::Act_c*)i_this)->Mthd_Delete();
}

/* 00000DAC-00000DCC       .text Mthd_Execute__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjAshut::Act_c*)i_this)->MoveBGExecute();
}

/* 00000DCC-00000DF8       .text Mthd_Draw__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return
        static_cast<dBgS_MoveBgActor*> /* casting as dBgS_MoveBgActor* solves weak func order*/
        (i_this)->Draw();
}

/* 00000DF8-00000E24       .text Mthd_IsDelete__Q210daObjAshut27@unnamed@d_a_obj_ashut_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjAshut::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjAshut

actor_process_profile_definition g_profile_Obj_Ashut = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Ashut_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjAshut::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Ashut_e,
    /* Actor SubMtd */ &daObjAshut::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
