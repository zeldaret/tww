/**
 * d_a_obj_swheavy.cpp
 * Object - Wind Temple - Iron Boots switch
 */

#include "d/actor/d_a_obj_swheavy.h"
#include "d/res/res_hhbot.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/actor/d_a_player.h"

#include "weak_data_1811.h" // IWYU pragma: keep

const char daObjSwheavy::Act_c::M_arcname[] = "Hhbot";
const daObjSwheavy::Attr_c daObjSwheavy::Act_c::M_attr[] = {
    {
        /* m00            */ {},
        /* mFlags         */ 0,
        /* mVSpring       */ 0.0f,
        /* mVSpeedDecay   */ 0.0f,
        /* mPushVSpeed0   */ 0.0f,
        /* m14            */ 0,
        /* mMiniPushDelay */ 0,
        /* mPushDelay     */ 0,
    },
    {
        /* m00            */ {},
        /* mFlags         */ 0,
        /* mVSpring       */ 0.0f,
        /* mVSpeedDecay   */ 0.0f,
        /* mPushVSpeed0   */ 0.0f,
        /* m14            */ 0,
        /* mMiniPushDelay */ 0,
        /* mPushDelay     */ 0,
    },
    {
        /* m00            */ {0,0,0x80,0},
        /* mFlags         */ FLAG_IS_TOGGLE | FLAG_REQ_HEAVY,
        /* mVSpring       */ 0.93f,
        /* mVSpeedDecay   */ 0.42f,
        /* mPushVSpeed0   */ 0.0f,
        /* m14            */ 4,
        /* mMiniPushDelay */ 4,
        /* mPushDelay     */ 15,
    },
    {
        /* m00            */ {0,0,0x80,0},
        /* mFlags         */ FLAG_OBEY_SAVE | FLAG_STAY_PRESSED | FLAG_REQ_HEAVY,
        /* mVSpring       */ 0.93f,
        /* mVSpeedDecay   */ 0.42f,
        /* mPushVSpeed0   */ 0.0f,
        /* m14            */ 4,
        /* mMiniPushDelay */ 4,
        /* mPushDelay     */ 15,
    },
};

/* 00000078-0000009C       .text solidHeapCB__Q212daObjSwheavy5Act_cFP10fopAc_ac_c */
BOOL daObjSwheavy::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return static_cast<daObjSwheavy::Act_c*>(i_this)->create_heap();
}

/* 0000009C-0000032C       .text create_heap__Q212daObjSwheavy5Act_cFv */
u8 daObjSwheavy::Act_c::create_heap() {
    J3DModelData* mdl_1_data = (J3DModelData*) dComIfG_getObjectRes(M_arcname, HHBOT_BDL_HHBOT1);
    JUT_ASSERT(0x116, mdl_1_data != NULL);
    mpModel1 = mDoExt_J3DModel__create(mdl_1_data, 0x80000, 0x11000022);

    J3DModelData* mdl_2_data = (J3DModelData*) dComIfG_getObjectRes(M_arcname, HHBOT_BDL_HHBOT2);
    JUT_ASSERT(0x11F, mdl_2_data != NULL);
    mpModel2 = mDoExt_J3DModel__create(mdl_2_data, 0x80000, 0x11000022);

    bool b1 = false;
    mpBgW1 = new dBgW();
    if (mpBgW1 != NULL) {
        cBgD_t* bgw_1_data = (cBgD_t*) dComIfG_getObjectRes(M_arcname, HHBOT_DZB_HHBOT1);
        JUT_ASSERT(0x137, bgw_1_data != NULL);
        if (!mpBgW1->Set(bgw_1_data, dBgW::MOVE_BG_e, &mMtx1)) {
            b1 = true;
        }
    }

    bool b2 = false;
    mpBgW2 = new dBgW();
    if (mpBgW2 != NULL) {
        cBgD_t* bgw_2_data = (cBgD_t*) dComIfG_getObjectRes(M_arcname, HHBOT_DZB_HHBOT2);
        JUT_ASSERT(0x146, bgw_2_data != NULL);
        if (!mpBgW2->Set(bgw_2_data, dBgW::MOVE_BG_e, &mMtx2)) {
            b2 = true;
        }
    }

    bool success = false;
    if (mpModel1 && mpModel2 && b1 && b2) {
        success = true;
    }

    if (!success) {
        mpBgW1 = NULL;
        mpBgW2 = NULL;
    }
    // Fakematch? This function should probably have return type bool, but the codegen towards the
    // end here doesn't work unless the return type is u8.
    return success;
}

/* 0000032C-00000628       .text _create__Q212daObjSwheavy5Act_cFv */
cPhs_State daObjSwheavy::Act_c::_create() {
    fopAcM_SetupActor(this, daObjSwheavy::Act_c);
    
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        mType = prm_get_type();
        bool up = cLib_checkBit<u32>(attr().mFlags, FLAG_IS_TOGGLE) || !is_switch();
        scale.z *= 1.5f;
        scale.x *= 1.5f;
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle);
        mDoMtx_stack_c::scaleM(scale);
        mDoMtx_copy(mDoMtx_stack_c::get(), mMtx1);
        if (!up) {
            mDoMtx_stack_c::get()[1][3] += -35.5f;
        }
        mDoMtx_copy(mDoMtx_stack_c::get(), mMtx2);
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x2000)) {
            dComIfG_Bgsp()->Regist(mpBgW1, this);
            mpBgW1->SetCrrFunc(NULL);
            dComIfG_Bgsp()->Regist(mpBgW2, this);
            mpBgW2->SetCrrFunc(NULL);
            mpBgW2->SetRideCallback(rideCB);
            fopAcM_SetMtx(this, mpModel1->getBaseTRMtx());
            init_mtx();
            fopAcM_setCullSizeBox(this, -97.5f, -2.0f, -97.5f, 97.5f, 55.0f, 97.5f);
            mRiding = false;
            mPrevRiding = false;
            mMiniPushTimer = 0;
            mMiniPushFlg = false;
            mHeavyRiding = false;
            mPrevHeavyRiding = false;
            mPushTimer = 0;
            mPushFlg = false;
            mVSpeed = 0.0f;
            m330 = 0;
            m334 = 0.0f;
            if (cLib_checkBit<u32>(attr().mFlags, FLAG_IS_TOGGLE) || !is_switch()) {
                mTargetHFrac = 1.0f;
                mCurHFrac = 1.0f;
                m328 = 0.0f;
                m32C = 1.0f;
                m338 = 1.0f;
                mTopPos = 0.0f;
                mode_upper_init();
            } else {
                mTargetHFrac = 0.0f;
                mCurHFrac = 0.0f;
                m328 = -35.5f;
                m32C = 0.0f;
                m338 = 0.0f;
                mTopPos = -35.5f;
                mode_lower_init();
            }
        } else {
            phase_state = cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 00000628-000006EC       .text _delete__Q212daObjSwheavy5Act_cFv */
bool daObjSwheavy::Act_c::_delete() {
    if (mpBgW1) {
        if (mpBgW1->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW1);
        }
    }
    if (mpBgW2) {
        if (mpBgW2->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW2);
        }
    }
    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

/* 000006EC-000007F8       .text set_mtx__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel1->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::get()[1][3] += m328;
    mpModel2->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_stack_c::scaleM(scale);
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx1);
    mDoMtx_stack_c::get()[1][3] += mTopPos;
    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx2);
}

/* 000007F8-00000850       .text init_mtx__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::init_mtx() {
    mpModel1->setBaseScale(scale);
    mpModel2->setBaseScale(scale);
    set_mtx();
}

/* 00000850-00000884       .text rideCB__Q212daObjSwheavy5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjSwheavy::Act_c::rideCB(dBgW* bgw, fopAc_ac_c* i_ac, fopAc_ac_c* i_pt) {
    daObjSwheavy::Act_c *i_this = (daObjSwheavy::Act_c*)i_ac;
    if (fopAcM_CheckStatus(i_pt, fopAcStts_FREEZE_e)) {
        i_this->mRiding = true;

        if (fopAcM_GetProfName(i_pt) == PROC_PLAYER && ((daPy_py_c*)i_pt)->checkEquipHeavyBoots()) {
            i_this->mHeavyRiding = true;
        }
    }
}

/* 00000884-00000998       .text calc_top_pos__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::calc_top_pos() {
    float decay = attr().mVSpeedDecay;
    mVSpeed -= (mCurHFrac - mTargetHFrac) * attr().mVSpring;
    mVSpeed -= mVSpeed * decay;
    mCurHFrac += mVSpeed;
    m328 = (1.0f - mCurHFrac) * -35.5f;
    m328 = cLib_minMaxLimit(m328, -36.5f, 1.0f);

    if (m330 > 0) {
        if (--m330 == 0) {
            m32C = m334;
        }
    }
    if (mMode == 0) {
        m338 = mCurHFrac;
    } else {
        m338 = m32C;
    }
    mTopPos = (1.0f - m338) * -35.5f;
    if (mTopPos < m328) {
        mTopPos = m328;
    }
}

/* 00000998-000009A4       .text top_bg_aim_req__Q212daObjSwheavy5Act_cFfs */
void daObjSwheavy::Act_c::top_bg_aim_req(float param_1, short param_2) {
    m334 = param_1;
    m330 = param_2;
}

/* 000009A4-00000AF8       .text set_push_flag__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::set_push_flag() {
    if (mMiniPushFlg) {
        if (mRiding) {
            mMiniPushTimer = attr().mMiniPushDelay;
        } else {
            if (--mMiniPushTimer <= 0) {
                mMiniPushFlg = false;
            }
        }
    } else {
        if (mRiding) {
            if (++mMiniPushTimer >= attr().mMiniPushDelay) {
                mMiniPushFlg = true;
            }
        } else {
            mMiniPushTimer = 0;
        }
    }

    if (mPushFlg) {
        if (mHeavyRiding) {
            mPushTimer = attr().mPushDelay;
        } else {
            if (--mPushTimer <= 0) {
                mPushFlg = false;
            }
        }
    } else {
        if (mHeavyRiding) {
            if (++mPushTimer >= attr().mPushDelay) {
                mPushFlg = true;
            }
        } else {
            mPushTimer = 0;
        }
    }    
}

/* 00000AF8-00000B14       .text mode_upper_init__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::mode_upper_init() {
    mMode = 0;
    mTargetHFrac = 1.0f;
    mChangingState = false;
}

/* 00000B14-00000C30       .text mode_upper__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::mode_upper() {
    bool pressing = false;
    float height = 1.0f;
    if (mMiniPushFlg) {
        if (cLib_checkBit<u32>(attr().mFlags, FLAG_REQ_HEAVY)) {
            if (mPushFlg) {
                pressing = true;
            } else {
                height = 0.9f;
            }
        } else {
            pressing = true;
        }
    }

    if (pressing || (cLib_checkBit<u32>(attr().mFlags, FLAG_OBEY_SAVE) && is_switch())) {
        if (pressing) {
            mChangingState = true;
        }
        mode_u_l_init();
    } else {
        mTargetHFrac = height;
        top_bg_aim_req(height, 1);
    }
}

/* 00000C30-00000C90       .text mode_u_l_init__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::mode_u_l_init() {
    mMode = 1;
    mTargetHFrac = 0.0f;
    mVSpeed = attr().mPushVSpeed0;
    top_bg_aim_req(0.0f, attr().m14);
}

/* 00000C90-00000D98       .text mode_u_l__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::mode_u_l() {
    if (mCurHFrac <= 0.0f) {
        if (mChangingState) {
            if (cLib_checkBit<u32>(attr().mFlags, FLAG_IS_TOGGLE)) {
                rev_switch();
            } else {
                on_switch();
            }
        }
        fopAcM_seStart(this, JA_SE_OBJ_FOOT_SW_ON, 0);
        mode_lower_init();
    }
}

/* 00000D98-00000DB8       .text mode_lower_init__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::mode_lower_init() {
    mMode = 2;
    mTargetHFrac = 0.0f;
    mChangingState = false;
}

/* 00000DB8-00000F0C       .text mode_lower__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::mode_lower() {
    bool pressing = false;
    if (mMiniPushFlg) {
        if (cLib_checkBit<u32>(attr().mFlags, FLAG_REQ_HEAVY)) {
            if (mPushFlg) {
                pressing = true;
            }
        } else {
            pressing = true;
        }
    }

    bool pop_back_up = !cLib_checkBit<u32>(attr().mFlags, FLAG_STAY_PRESSED) &&
        !pressing;
    bool match_state_up = cLib_checkBit<u32>(attr().mFlags, FLAG_OBEY_SAVE) &&
        !is_switch() &&
        !pressing;

    if (pop_back_up || match_state_up) {
        bool is_toggle = cLib_checkBit<u32>(attr().mFlags, FLAG_IS_TOGGLE);
        if (pop_back_up && !is_toggle && !pressing) {
            mChangingState = true;
        }
        mode_l_u_init();
    }
}

/* 00000F0C-00000F44       .text mode_l_u_init__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::mode_l_u_init() {
    mMode = 3;
    mTargetHFrac = 1.0f;
    top_bg_aim_req(1.0f, 1);
}

/* 00000F44-00000FBC       .text mode_l_u__Q212daObjSwheavy5Act_cFv */
void daObjSwheavy::Act_c::mode_l_u() {
    if (mCurHFrac >= 1.0f) {
        if (mChangingState) {
            off_switch();
        }
        mode_upper_init();
    }
}

/* 00000FBC-00001104       .text _execute__Q212daObjSwheavy5Act_cFv */
bool daObjSwheavy::Act_c::_execute() {
    typedef void (daObjSwheavy::Act_c::*procFunc)();
    static procFunc mode_proc[] = {
        &daObjSwheavy::Act_c::mode_upper,
        &daObjSwheavy::Act_c::mode_u_l,
        &daObjSwheavy::Act_c::mode_lower,
        &daObjSwheavy::Act_c::mode_l_u,
    };
    set_push_flag();
    (this->*mode_proc[mMode])();
    calc_top_pos();
    mPrevRiding = mRiding;
    mPrevHeavyRiding = mHeavyRiding;
    mRiding = false;
    mHeavyRiding = false;
    set_mtx();
    mpBgW1->Move();
    mpBgW2->Move();
    eyePos.x = current.pos.x;
    eyePos.y = current.pos.y + m328 - -35.5f;
    eyePos.z = current.pos.z;
    return true;
}

/* 00001104-000011C0       .text _draw__Q212daObjSwheavy5Act_cFv */
bool daObjSwheavy::Act_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel1, &tevStr);
    g_env_light.setLightTevColorType(mpModel2, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel1);
    mDoExt_modelUpdateDL(mpModel2);
    dComIfGd_setList();
    return true;
}

namespace daObjSwheavy {
namespace {
/* 000011C0-000011E0       .text Mthd_Create__Q212daObjSwheavy29@unnamed@d_a_obj_swheavy_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return static_cast<Act_c*>(i_this)->_create();
}

/* 000011E0-00001204       .text Mthd_Delete__Q212daObjSwheavy29@unnamed@d_a_obj_swheavy_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return static_cast<Act_c*>(i_this)->_delete();
}

/* 00001204-00001228       .text Mthd_Execute__Q212daObjSwheavy29@unnamed@d_a_obj_swheavy_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return static_cast<Act_c*>(i_this)->_execute();
}

/* 00001228-0000124C       .text Mthd_Draw__Q212daObjSwheavy29@unnamed@d_a_obj_swheavy_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return static_cast<Act_c*>(i_this)->_draw();
}

/* 0000124C-00001254       .text Mthd_IsDelete__Q212daObjSwheavy29@unnamed@d_a_obj_swheavy_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
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
}; // namespace daObjSwheavy

actor_process_profile_definition g_profile_Obj_Swheavy = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Swheavy,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjSwheavy::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Swheavy,
    /* Actor SubMtd */ &daObjSwheavy::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
