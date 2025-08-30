/**
 * d_a_obj_ladder.cpp
 * Object - Drop-down ladder
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ladder.h"
#include "d/res/res_mhsg.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"

Mtx daObjLadder::Act_c::M_tmp_mtx;

namespace daObjLadder {
    namespace {
        struct Attr_c {
            /* 0x00 */ f32 field_0x00;
            /* 0x04 */ f32 field_0x04;
            /* 0x08 */ f32 field_0x08;
            /* 0x0C */ f32 field_0x0C;
            /* 0x10 */ u8 field_0x10;
            /* 0x11 */ u8 field_0x11;
            /* 0x12 */ u8 field_0x12;
            /* 0x13 */ u8 field_0x13;
            /* 0x14 */ u8 field_0x14;
            /* 0x16 */ s16 field_0x16;
            /* 0x18 */ s16 field_0x18;
            /* 0x1A */ s16 mVibDuration;
            /* 0x1C */ f32 field_0x1C;
            /* 0x20 */ f32 field_0x20;
        };

        static const Attr_c L_attr = { // TODO: Figure out what these are
            -3.0f, 0.005f, 0.0005f, 0.5f,
            3, 75, 50, 45, 40,
            20000, 0x3CC3, 0x000F,
            2.0f, 1.0f,
        };

        inline const Attr_c & attr() { return L_attr; }

        struct AttrType {
            s16 modelId;
            s16 dzbId;
            f32 field_0x04;
        };

        static AttrType L_attr_type[] = {
            {MHSG_BDL_MHSG6, MHSG_DZB_MHSG6, 600.0f},
            {MHSG_BDL_MHSG9, MHSG_DZB_MHSG9, 900.0f},
            {MHSG_BDL_MHSG12, MHSG_DZB_MHSG12, 1200.0f},
            {MHSG_BDL_MHSG15, MHSG_DZB_MHSG15, 1500.0f},
            {MHSG_BDL_MHSG4H, MHSG_DZB_MHSG4H, 450.0f},
        };

        inline const AttrType& attr_type(Type_e type) { return L_attr_type[type]; }
    }
}

const char daObjLadder::Act_c::M_arcname[] = "Mhsg";

/* 00000078-0000013C       .text CreateHeap__Q211daObjLadder5Act_cFv */
BOOL daObjLadder::Act_c::CreateHeap() {
    J3DModelData* model_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, attr_type(mType).modelId));
    JUT_ASSERT(0x17E, model_data != NULL);

    mpModel = mDoExt_J3DModel__create(model_data, 0x80000U, 0x11000022U);

    return mpModel != NULL;
}

/* 0000013C-000002F0       .text Create__Q211daObjLadder5Act_cFv */
BOOL daObjLadder::Act_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    init_mtx();

    fopAcM_setCullSizeBox(this, -55.0f, -1.0f, -10.0f, 55.0f, attr_type(mType).field_0x04 + 41.0f, 10.0f);

    cXyz pos;
    mDoMtx_stack_c::push();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::transM(0.0f, 10.0f, 5.0f);
    mDoMtx_stack_c::multVec(&cXyz::Zero, &pos);
    mDoMtx_stack_c::pop();

    mGndChk.SetPos(&pos);
    mGndChk.SetActorPid(base.mBsPcId);
    mGndY = dComIfG_Bgsp()->GroundCross(&mGndChk);
    unk346 = 0;

    mEventIdx = dComIfGp_evmng_getEventIdx(NULL, prm_get_evId());

    if (prm_get_swSave() == 0xFF || fopAcM_isSwitch(this, prm_get_swSave())) {
        current.pos.y = mGndY;
        set_mtx();
        mode_fell_init();
    } else {
        mode_wait_init();
    }

    return TRUE;
}

/* 000002F0-000004F8       .text Mthd_Create__Q211daObjLadder5Act_cFv */
cPhs_State daObjLadder::Act_c::Mthd_Create() {
    fopAcM_SetupActor(this, Act_c);
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);

    if (phase_state == cPhs_COMPLEATE_e) {
        mType = prm_get_type();
        phase_state = MoveBGCreate(
            M_arcname, attr_type(mType).dzbId, dBgS_MoveBGProc_Trans,
            DEMO_SELECT(0x1700, 0x900)
        );

        JUT_ASSERT(0x1DE, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }

    return phase_state;
}

/* 000009B8-000009C0       .text Delete__Q211daObjLadder5Act_cFv */
BOOL daObjLadder::Act_c::Delete() {
    return TRUE;
}

/* 000009C0-00000A0C       .text Mthd_Delete__Q211daObjLadder5Act_cFv */
BOOL daObjLadder::Act_c::Mthd_Delete() {
    BOOL res = MoveBGDelete();

    dComIfG_resDeleteDemo(&mPhs, M_arcname);

    return res;
}

/* 00000A0C-00000A78       .text demo_end_reset__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::demo_end_reset() {
    if (unk346 && dComIfGp_evmng_endCheck(mEventIdx)) {
        dComIfGp_event_reset();
        unk346 = 0;
    }
}

/* 00000A78-00000A84       .text mode_wait_init__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::mode_wait_init() {
    mMode = Mode_WAIT_e;
}

/* 00000A84-00000AE0       .text mode_wait__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::mode_wait() {
    if (fopAcM_isSwitch(this, prm_get_swSave())) {
        mode_demoreq_init();
    }
}

/* 00000AE0-00000AF4       .text mode_demoreq_init__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::mode_demoreq_init() {
    mMode = Mode_DEMOREQ_e;
    unk346 = 0;
}

/* 00000AF4-00000BB4       .text mode_demoreq__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::mode_demoreq() {
    bool ret = false;
    if (dComIfGp_evmng_existence(mEventIdx)) {
        if (eventInfo.checkCommandDemoAccrpt()) {
            ret = true;
            unk346 = 1;
        } else {
            fopAcM_orderOtherEventId(this, mEventIdx, prm_get_evId());
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
    } else {
        ret = true;
    }

    if (ret) {
        mode_vib_init();
    }
}

/* 00000BB4-00000BDC       .text mode_vib_init__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::mode_vib_init() {
    mVibTimer = attr().mVibDuration;
    unk338 = 0;
    unk33A = 0;
    mMode = Mode_VIB_e;
}

/* 00000BDC-00000C98       .text mode_vib__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::mode_vib() {
    unk338 += attr().field_0x16;
    unk33A += attr().field_0x18;

    mVibXOffset = cM_scos(unk338) * attr().field_0x1C;
    mVibYOffset = cM_scos(unk33A) * attr().field_0x20;

    if (--mVibTimer <= 0) {
        mode_drop_init();
    }
}

/* 00000C98-00000CDC       .text mode_drop_init__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::mode_drop_init() {
    gravity = -5.0f;
    speed.set(cXyz::Zero);
    unk2DE = attr().field_0x10;
    mMode = Mode_DROP_e;
}

/* 00000CDC-00000EA8       .text mode_drop__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::mode_drop() {
    daObj::posMoveF_stream(this, NULL, &cXyz::Zero, attr().field_0x04, attr().field_0x08);

    if (current.pos.y < mGndY) {
        if (unk2DE == attr().field_0x10) {
            fopAcM_seStart(this, JA_SE_OBJ_LADDER_FALL_1, dComIfG_Bgsp()->GetMtrlSndId(mGndChk));

            dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        } else {
            s32 tmp = attr().field_0x10 - unk2DE;
            s32 param_2;

            if (tmp == 1) {
                param_2 = attr().field_0x11;
            } else if (tmp == 2) {
                param_2 = attr().field_0x12;
            } else if (tmp == 3) {
                param_2 = attr().field_0x13;
            } else {
                param_2 = attr().field_0x14;
            }

            fopAcM_seStart(this, JA_SE_OBJ_LADDER_FALL_2, param_2);
        }

        if (unk2DE >= 0) {
            unk2DE--;

            f32 temp = current.pos.y - mGndY;
            current.pos.y = mGndY - temp * 0.5f;
            speed.y *= -0.5f;
        } else {
            current.pos.y = mGndY;
            mode_fell_init();
        }
    }
}

/* 00000EA8-00000EB4       .text mode_fell_init__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::mode_fell_init() {
    mMode = Mode_FELL_e;
}

/* 00000EB4-00000EB8       .text mode_fell__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::mode_fell() {}

/* 00000EB8-00000F4C       .text set_mtx__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);

    mDoMtx_stack_c::transM(mVibXOffset, mVibYOffset, 0.0f);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000F4C-00000F88       .text init_mtx__Q211daObjLadder5Act_cFv */
void daObjLadder::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00000F88-000010A0       .text Execute__Q211daObjLadder5Act_cFPPA3_A4_f */
BOOL daObjLadder::Act_c::Execute(Mtx** ppMtx) {
    typedef void (Act_c::*ModeFunc)();
    static const ModeFunc mode_proc[] = {
        &Act_c::mode_wait,
        &Act_c::mode_demoreq,
        &Act_c::mode_vib,
        &Act_c::mode_drop,
        &Act_c::mode_fell,
    };

    demo_end_reset();
    (this->*mode_proc[mMode])();
    eyePos.y = current.pos.y;
    set_mtx();
    *ppMtx = &M_tmp_mtx;

    return TRUE;
}

/* 000010A0-00001140       .text Draw__Q211daObjLadder5Act_cFv */
BOOL daObjLadder::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();

    return TRUE;
}

namespace daObjLadder {
namespace {
/* 00001140-00001160       .text Mthd_Create__Q211daObjLadder28@unnamed@d_a_obj_ladder_cpp@FPv */
static cPhs_State Mthd_Create(void* i_this) {
    return static_cast<Act_c*>(i_this)->Mthd_Create();
}

/* 00001160-00001180       .text Mthd_Delete__Q211daObjLadder28@unnamed@d_a_obj_ladder_cpp@FPv */
static BOOL Mthd_Delete(void* i_this) {
    return static_cast<Act_c*>(i_this)->Mthd_Delete();
}

/* 00001180-000011A0       .text Mthd_Execute__Q211daObjLadder28@unnamed@d_a_obj_ladder_cpp@FPv */
static BOOL Mthd_Execute(void* i_this) {
    return static_cast<Act_c*>(i_this)->MoveBGExecute();
}

/* 000011A0-000011CC       .text Mthd_Draw__Q211daObjLadder28@unnamed@d_a_obj_ladder_cpp@FPv */
static BOOL Mthd_Draw(void* i_this) {
    return static_cast<Act_c*>(i_this)->MoveBGDraw();
}

/* 000011CC-000011F8       .text Mthd_IsDelete__Q211daObjLadder28@unnamed@d_a_obj_ladder_cpp@FPv */
static BOOL Mthd_IsDelete(void* i_this) {
    return static_cast<Act_c*>(i_this)->MoveBGIsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjLadder

actor_process_profile_definition g_profile_Obj_Ladder = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ladder,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjLadder::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Ladder,
    /* Actor SubMtd */ &daObjLadder::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
