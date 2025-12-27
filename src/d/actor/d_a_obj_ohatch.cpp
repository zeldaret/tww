/**
 * d_a_obj_ohatch.cpp
 * Object - Hatch door leading to the Nintendo Gallery
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ohatch.h"
#include "d/res/res_ohatch.h"
#include "d/d_procname.h"
#include "d/d_bg_w.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_hostIO.h"

namespace {
static const char l_arcname[] = "Ohatch";
}

#if VERSION == VERSION_DEMO
class daObjOhatch_HIO_c : public JORReflexible {
public:
    daObjOhatch_HIO_c();
    virtual ~daObjOhatch_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ u8 m38;
}; // size = 0x40

static daObjOhatch_HIO_c l_HIO;

daObjOhatch_HIO_c::daObjOhatch_HIO_c() {
    mNo = -1;
    m08 = -4096.0f;
    m0C = -16384.0f;
    m10 = 0.0f;
    m14 = -25.0f;
    m18 = 190.0f;
    m1C = 1.0f;
    m20 = 8192.0f;
    m24 = 131072.0f;
    m28 = 6.0f;
    m2C = -64.0f;
    m30 = 1024.0f;
    m34 = 8192.0f;
    m38 = 0;
}
#else
namespace L_HIO {
static const f32 m08 = -4096.0f;
static const f32 m0C = -16384.0f;
static const f32 m10 = 0.0f;
static const f32 m14 = -25.0f;
static const f32 m18 = 190.0f;
static const f32 m1C = 1.0f;
static const f32 m20 = 8192.0f;
static const f32 m24 = 131072.0f;
static const f32 m28 = 6.0f;
static const f32 m2C = -64.0f;
static const f32 m30 = 1024.0f;
static const f32 m34 = 8192.0f;
static const u8 m38 = 0;
} // namespace L_HIO
#endif

/* 00000078-0000018C       .text set_mtx__13daObjOhatch_cFv */
void daObjOhatch_c::set_mtx() {
    s16 tmp = m2D8 + (s32)(m2F0 * cM_ssin(m2F2));

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + m2E8, current.pos.z);
    mDoMtx_stack_c::XYZrotM(shape_angle);
    mDoMtx_stack_c::transM(0.0f, -HIO(m14), -HIO(m18));
    mDoMtx_stack_c::XrotM(tmp);
    mDoMtx_stack_c::transM(0.0f, HIO(m14), HIO(m18));
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 0000018C-0000027C       .text init_mtx__13daObjOhatch_cFv */
void daObjOhatch_c::init_mtx() {
    mModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::XYZrotM(shape_angle);
    mDoMtx_stack_c::push();
    mDoMtx_stack_c::transM(0.0f, 25.0f, -190.0f);
    mDoMtx_stack_c::XrotM(m2D8);
    mDoMtx_stack_c::transM(0.0f, -25.0f, 190.0f);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::pop();
    mDoMtx_stack_c::scaleM(scale);
    cMtx_copy(mDoMtx_stack_c::get(), m2A8);
}

/* 0000027C-000002A0       .text solidHeapCB__13daObjOhatch_cFP10fopAc_ac_c */
BOOL daObjOhatch_c::solidHeapCB(fopAc_ac_c* a_this) {
    return ((daObjOhatch_c*)a_this)->create_heap();
}

/* 000002A0-000003CC       .text create_heap__13daObjOhatch_cFv */
bool daObjOhatch_c::create_heap() {
    bool uVar5 = true;
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcname, OHATCH_BDL_OHATCH);
    if (modelData == NULL) {
        JUT_ASSERT(DEMO_SELECT(308, 311), FALSE);
        uVar5 = false;
    } else {
        mModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        mBgW1 = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, OHATCH_DZB_OH_CLS), cBgW::MOVE_BG_e, &m2A8);
        mBgW2 = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(l_arcname, OHATCH_DZB_OH_OPN), cBgW::MOVE_BG_e, &m2A8);
        if (mModel == NULL || mBgW1 == NULL || mBgW2 == NULL) {
            uVar5 = false;
        }
    }
    return uVar5;
}

/* 000003CC-00000548       .text _create__13daObjOhatch_cFv */
cPhs_State daObjOhatch_c::_create() {
    fopAcM_SetupActor(this, daObjOhatch_c);
    cPhs_State ret = dComIfG_resLoad(&mPhase, l_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0xB90)) {
            fopAcM_SetMtx(this, mModel->getBaseTRMtx());
            m29C = param_get_swSave();
            if (m29C != 0xff && fopAcM_isSwitch(this, m29C) == TRUE) {
                m2D8 = -0x4000;
                mActionFunc = &daObjOhatch_c::open_wait_act_proc;
                if (dComIfG_Bgsp()->Regist(mBgW2, this)) {
                    ret = cPhs_ERROR_e;
                }
            } else {
                mActionFunc = &daObjOhatch_c::close_wait_act_proc;
                if (dComIfG_Bgsp()->Regist(mBgW1, this)) {
                    ret = cPhs_ERROR_e;
                }
            }
            init_mtx();
        } else {
            ret = cPhs_ERROR_e;
        }
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("フィギュア屋の入口", &l_HIO);
    }
#endif
    return ret;
}

/* 00000548-00000628       .text _delete__13daObjOhatch_cFv */
bool daObjOhatch_c::_delete() {
    dComIfG_resDelete(&mPhase, l_arcname);
#if VERSION > VERSION_DEMO
    if (heap != NULL)
#endif
    {
        if (mBgW1 != NULL) {
            if (mBgW1->ChkUsed()) {
                dComIfG_Bgsp()->Release(mBgW1);
            }
#if VERSION > VERSION_DEMO
            mBgW1 = NULL;
#endif
        }

        if (mBgW2 != NULL) {
            if (mBgW2->ChkUsed()) {
                dComIfG_Bgsp()->Release(mBgW2);
            }
#if VERSION > VERSION_DEMO
            mBgW2 = NULL;
#endif
        }
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
#endif
    return true;
}

/* 00000628-00000810       .text close_wait_act_proc__13daObjOhatch_cFv */
void daObjOhatch_c::close_wait_act_proc() {
    if (m29C != 0xff && fopAcM_isSwitch(this, m29C) == TRUE) {
        if (dComIfGp_evmng_existence("FIGURE_HATCH_OPEN")) {
            s32 staffIdx = dComIfGp_evmng_getMyStaffId("Ohatch");
            if (staffIdx != -1) {
                if (strcmp(dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx), "OPEN") == 0) {
                    fopAcM_seStartCurrent(this, JA_SE_OBJ_FIG_HATCH_OPEN, 0);
                    if (mBgW1 != NULL && mBgW1->ChkUsed()) {
                        dComIfG_Bgsp()->Release(mBgW1);
                    }
                    if (mBgW2 != NULL && !mBgW2->ChkUsed()) {
                        dComIfG_Bgsp()->Regist(mBgW2, this);
                    }

                    dComIfGp_getVibration().StartShock(3, 1, cXyz(0.0f, 1.0f, 0.0f));
                    mActionFunc = &daObjOhatch_c::tremor_act_proc;
                }
            }
        }
    } else if (HIO(m38) == 1) {
        fopAcM_seStartCurrent(this, JA_SE_OBJ_FIG_HATCH_OPEN, 0);
        if (mBgW1 != NULL && mBgW1->ChkUsed()) {
            dComIfG_Bgsp()->Release(mBgW1);
        }
        if (mBgW2 != NULL && !mBgW2->ChkUsed()) {
            dComIfG_Bgsp()->Regist(mBgW2, this);
        }
        dComIfGp_getVibration().StartShock(3, 1, cXyz(0.0f, 1.0f, 0.0f));
        mActionFunc = &daObjOhatch_c::tremor_act_proc;
    }
}

/* 00000810-000008A4       .text tremor_act_proc__13daObjOhatch_cFv */
void daObjOhatch_c::tremor_act_proc() {
    m2EC += (s32)HIO(m20);
    if (m2EC > (s32)HIO(m24)) {
        m2E8 = 0.0f;
        mActionFunc = &daObjOhatch_c::open_act_proc;
    } else {
        f32 fVar1 = cM_ssin(m2EC);
        if (fVar1 < 0.0f) {
            fVar1 *= -1.0f;
        }
        m2E8 = fVar1 * HIO(m28);
    }
}

/* 000008A4-00000A00       .text open_act_proc__13daObjOhatch_cFv */
void daObjOhatch_c::open_act_proc() {
#if VERSION == VERSION_DEMO
    f32 uVar3 = (cM_ssin(m2D8 / HIO(m0C) * 32768.0f) + HIO(m1C)) / (HIO(m1C) + 1.0f);
    s32 uVar2 = HIO(m08) * uVar3;
#else
    f32 sin = m2D8 / HIO(m0C) * 32768.0f;
    s32 uVar2 = (cM_ssin(sin) + HIO(m1C)) / (HIO(m1C) + 1.0f) * HIO(m08);
#endif
    m2D8 += uVar2;

    if (m2D8 <= (s16)HIO(m0C)) {
        m2D8 = (s16)HIO(m0C);
        mDoAud_seStart(JA_SE_READ_RIDDLE_1);
        m2F0 = (s16)HIO(m30);
        dComIfGp_getVibration().StartShock(6, 1, cXyz(0.0f, 1.0f, 0.0f));
        mActionFunc = &daObjOhatch_c::vibrate_act_proc;
    }
}

/* 00000A00-00000A4C       .text vibrate_act_proc__13daObjOhatch_cFv */
void daObjOhatch_c::vibrate_act_proc() {
    m2F0 += (s32)HIO(m2C);
    if (m2F0 < 0) {
        mActionFunc = &daObjOhatch_c::open_wait_act_proc;
    } else {
        m2F2 += (s32)HIO(m34);
    }
}

/* 00000A4C-00000A50       .text open_wait_act_proc__13daObjOhatch_cFv */
void daObjOhatch_c::open_wait_act_proc() {
#if VERSION == VERSION_DEMO
    if ((m29C == 0xff || fopAcM_isSwitch(this, m29C) != TRUE) && HIO(m38) == 0) {
        m2D8 = 0;
        m2E8 = 0.0f;
        m2EC = 0;
        m2F2 = 0;
        m2F0 = 0;
        if (mBgW2 != NULL && mBgW2->ChkUsed()) {
            dComIfG_Bgsp()->Release(mBgW2);
        }

        if (mBgW1 != NULL && !mBgW1->ChkUsed()) {
            dComIfG_Bgsp()->Regist(mBgW1, this);
        }

        mActionFunc = &daObjOhatch_c::close_wait_act_proc;
    }
#endif
}

/* 00000A50-00000B04       .text _execute__13daObjOhatch_cFv */
bool daObjOhatch_c::_execute() {
    if (mBgW1 != NULL && mBgW1->ChkUsed()) {
        mBgW1->Move();
    }

    if (mBgW2 != NULL && mBgW2->ChkUsed()) {
        mBgW2->Move();
    }

    set_mtx();
    (this->*mActionFunc)();
    return true;
}

/* 00000B04-00000B64       .text _draw__13daObjOhatch_cFv */
bool daObjOhatch_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);
    mDoExt_modelUpdateDL(mModel);
    return true;
}

/* 00000B64-00000B84       .text daObjOhatch_Create__FP10fopAc_ac_c */
static cPhs_State daObjOhatch_Create(fopAc_ac_c* i_this) {
    return ((daObjOhatch_c*)i_this)->_create();
}

/* 00000B84-00000BA8       .text daObjOhatch_Delete__FP13daObjOhatch_c */
static BOOL daObjOhatch_Delete(daObjOhatch_c* i_this) {
    return ((daObjOhatch_c*)i_this)->_delete();
}

/* 00000BA8-00000BCC       .text daObjOhatch_Execute__FP13daObjOhatch_c */
static BOOL daObjOhatch_Execute(daObjOhatch_c* i_this) {
    return ((daObjOhatch_c*)i_this)->_execute();
}

/* 00000BCC-00000BF0       .text daObjOhatch_Draw__FP13daObjOhatch_c */
static BOOL daObjOhatch_Draw(daObjOhatch_c* i_this) {
    return ((daObjOhatch_c*)i_this)->_draw();
}

/* 00000BF0-00000BF8       .text daObjOhatch_IsDelete__FP13daObjOhatch_c */
static BOOL daObjOhatch_IsDelete(daObjOhatch_c*) {
    return TRUE;
}

static actor_method_class l_daObjOhatch_Method = {
    (process_method_func)daObjOhatch_Create,
    (process_method_func)daObjOhatch_Delete,
    (process_method_func)daObjOhatch_Execute,
    (process_method_func)daObjOhatch_IsDelete,
    (process_method_func)daObjOhatch_Draw,
};

actor_process_profile_definition g_profile_Obj_Ohatch = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Ohatch,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjOhatch_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Ohatch,
    /* Actor SubMtd */ &l_daObjOhatch_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_5_e,
};
