/**
 * d_a_obj_shelf.cpp
 * Object - Wooden shelf
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_shelf.h"
#include "d/res/res_otana.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_npc_ba1.h"
#include "m_Do/m_Do_mtx.h"

Mtx daObjShelf::Act_c::M_tmp_mtx;

namespace daObjShelf {
    namespace {
        struct Attr_c {
            /* 0x00 */ short mVibDuration;
            /* 0x02 */ short mVibYSpeed;
            /* 0x04 */ float mVibYMagnitude;
            /* 0x08 */ short mVibXSpeed;
            /* 0x0a */ short mVibZSpeed;
            /* 0x0c */ float mVibXMagnitude;
            /* 0x10 */ float mVibZMagnitude;
            /* 0x14 */ float mRotAccel;
            /* 0x18 */ float mRotDecay;
            /* 0x1c */ float mBounceFactor;
            /* 0x20 */ u8 mBounceNum;
            /* 0x21 */ u8 mRotWaitDuration;
            /* 0x24 */ float mInitSpeed2;
            /* 0x28 */ float mInitSpeed3;
        };

        static const Attr_c L_attr = {
            /* mVibDuration     */ 4,
            /* mVibYSpeed       */ 30000,
            /* mVibYMagnitude   */ 4.0f,
            /* mVibXSpeed       */ 30500,
            /* mVibZSpeed       */ 29000,
            /* mVibXMagnitude   */ 200.0f,
            /* mVibZMagnitude   */ 200.0f,
            /* mRotAccel        */ 600.0f,
            /* mRotDecay        */ 0.02f,
            /* mBounceFactor    */ 0.5f,
            /* mBounceNum       */ 5,
            /* mRotWaitDuration */ 0,
            /* mInitSpeed2      */ -3500.0f,
            /* mInitSpeed3      */ -2500.0f,
        };

        inline const Attr_c & attr() { return L_attr; }
    }
}

const char daObjShelf::Act_c::M_arcname[] = "Otana";

/* 00000078-0000012C       .text CreateHeap__Q210daObjShelf5Act_cFv */
int daObjShelf::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData *)dComIfG_getObjectRes(M_arcname, OTANA_BDL_OTANA);
    JUT_ASSERT(0x12c, model_data != NULL);
    mpModel = mDoExt_J3DModel__create(model_data, 0x80000, 0x11000022);
    return mpModel != NULL;
}

/* 0000012C-000001A0       .text Create__Q210daObjShelf5Act_cFv */
BOOL daObjShelf::Act_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    init_mtx();
    fopAcM_setCullSizeBox(this, -110.0f, -55.0f, -1.0f, 110.0f, 20.0f, 110.0f);
    mode_wait_init();
    return TRUE;
}

/* 000001A0-0000029C       .text Mthd_Create__Q210daObjShelf5Act_cFv */
cPhs_State daObjShelf::Act_c::Mthd_Create() {
    fopAcM_SetupActor(this, Act_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(M_arcname, OTANA_DZB_OTANA, dBgS_MoveBGProc_Trans, 0xb00);
        JUT_ASSERT(0x15b, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 0000029C-000002A4       .text Delete__Q210daObjShelf5Act_cFv */
BOOL daObjShelf::Act_c::Delete() {
    return TRUE;
}

/* 000002A4-000002F0       .text Mthd_Delete__Q210daObjShelf5Act_cFv */
BOOL daObjShelf::Act_c::Mthd_Delete() {
    BOOL ret = MoveBGDelete();
    dComIfG_resDelete(&mPhs, M_arcname);
    return ret;
}

/* 000002F0-00000334       .text hold_event__Q210daObjShelf5Act_cCFv */
void daObjShelf::Act_c::hold_event() const {
    fopAc_ac_c* npc;
    if (fopAcM_SearchByName(PROC_NPC_BA1, &npc) && npc) {
        ((daNpc_Ba1_c *) npc)->holdEventOn();
    }
}

/* 00000334-00000340       .text mode_wait_init__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::mode_wait_init() {
    mMode = 0;
}

/* 00000340-000003FC       .text mode_wait__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::mode_wait() {
    bool quake = dComIfGp_getDetect().chk_quake(&current.pos);
    bool event = false;
    if (quake && prm_get_groundma() && !dComIfGs_isEventBit(0x1)) {
        hold_event();
        quake = false;
        event = true;
    }

    if (quake) {
        mode_vib_init();
    } else if (event) {
        mode_rot_init3();
    }
}

/* 000003FC-00000424       .text mode_vib_init__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::mode_vib_init() {
    mTimer = attr().mVibDuration;
    mVibY = 0;
    mVibX = 0;
    mVibZ = 0;
    mMode = 1;
}

/* 00000424-00000564       .text mode_vib__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::mode_vib() {
    if (--mTimer <= 0) {
        current.pos.y = home.pos.y;
        shape_angle.x = home.angle.x;
        shape_angle.z = home.angle.z;
        mode_rot_init();
    } else {
        mVibY += attr().mVibYSpeed;
        current.pos.y = home.pos.y + cM_ssin(mVibY) * attr().mVibYMagnitude;
        mVibX += attr().mVibXSpeed;
        mVibZ += attr().mVibZSpeed;
        shape_angle.x = home.angle.x + (short)(cM_ssin(mVibX) * attr().mVibXMagnitude);
        shape_angle.z = home.angle.z + (short)(cM_ssin(mVibZ) * attr().mVibZMagnitude);
    }
}

/* 00000564-000005A8       .text mode_rot_init__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::mode_rot_init() {
    mCurBounce = attr().mBounceNum + 1;
    mRotSpeed = 0.0f;
    mTimer = attr().mRotWaitDuration;
    mTargetAngle = 0x4000;
    m2e7 = false;
    mMode = 2;
}

/* 000005A8-000005E4       .text mode_rot_init2__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::mode_rot_init2() {
    mCurBounce = attr().mBounceNum + 1;
    mRotSpeed = attr().mInitSpeed2;
    mTimer = 0;
    mTargetAngle = 0x4000;
    m2e7 = false;
    mMode = 2;
}

/* 000005E4-00000620       .text mode_rot_init3__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::mode_rot_init3() {
    mCurBounce = attr().mBounceNum + 1;
    mRotSpeed = attr().mInitSpeed3;
    mTimer = 0;
    mTargetAngle = 0;
    m2e7 = true;
    mMode = 2;
}

/* 00000620-000007AC       .text mode_rot__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::mode_rot() {
    if (mTimer > 0) {
        mTimer--;
        return;
    }
    mRotSpeed += attr().mRotAccel;
    mRotSpeed -= mRotSpeed * attr().mRotDecay;
    shape_angle.x += (short)(int)mRotSpeed;
    if (shape_angle.x > mTargetAngle) {
        if (--mCurBounce <= 0) {
            shape_angle.x = mTargetAngle;
            if (m2e7) {
                mode_wait_init();
            } else {
                mode_fell_init();
            }
        } else {
            // Bounce
            shape_angle.x = mTargetAngle - (int)((short)(int)(shape_angle.x - mTargetAngle) * attr().mBounceFactor);
            mRotSpeed = mRotSpeed * -attr().mBounceFactor;
            if (mCurBounce == attr().mBounceNum) {
                fopAcM_seStart(this, JA_SE_OBJ_RACK_BREAK, 0);
            }
        }
    }
}

/* 000007AC-000007B8       .text mode_fell_init__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::mode_fell_init() {
    mMode = 3;
}

/* 000007B8-00000804       .text mode_fell__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::mode_fell() {
    if (dComIfGp_getDetect().chk_quake(&current.pos)) {
        mode_rot_init2();
    }
}

/* 00000804-00000884       .text set_mtx__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 00000884-000008C0       .text init_mtx__Q210daObjShelf5Act_cFv */
void daObjShelf::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 000008C0-000009B0       .text Execute__Q210daObjShelf5Act_cFPPA3_A4_f */
BOOL daObjShelf::Act_c::Execute(Mtx** matrix) {
    typedef void (daObjShelf::Act_c::*procFunc)();
    static procFunc mode_proc[] = {
        &daObjShelf::Act_c::mode_wait,
        &daObjShelf::Act_c::mode_vib,
        &daObjShelf::Act_c::mode_rot,
        &daObjShelf::Act_c::mode_fell,
    };
    (this->*mode_proc[mMode])();

    set_mtx();

    *matrix = &M_tmp_mtx;
    return TRUE;
}

/* 000009B0-00000A50       .text Draw__Q210daObjShelf5Act_cFv */
BOOL daObjShelf::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    dComIfG_Bgsp();
    return TRUE;
}

namespace daObjShelf {
namespace {
/* 00000A50-00000A70       .text Mthd_Create__Q210daObjShelf27@unnamed@d_a_obj_shelf_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return static_cast<Act_c*>(i_this)->Mthd_Create();
}

/* 00000A70-00000A90       .text Mthd_Delete__Q210daObjShelf27@unnamed@d_a_obj_shelf_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return static_cast<Act_c*>(i_this)->Mthd_Delete();
}

/* 00000A90-00000AB0       .text Mthd_Execute__Q210daObjShelf27@unnamed@d_a_obj_shelf_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return static_cast<Act_c*>(i_this)->MoveBGExecute();
}

/* 00000AB0-00000ADC       .text Mthd_Draw__Q210daObjShelf27@unnamed@d_a_obj_shelf_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return static_cast<Act_c*>(i_this)->MoveBGDraw();
}

/* 00000ADC-00000B08       .text Mthd_IsDelete__Q210daObjShelf27@unnamed@d_a_obj_shelf_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
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
}; // namespace daObjShelf

actor_process_profile_definition g_profile_Obj_Shelf = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Shelf,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjShelf::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Shelf,
    /* Actor SubMtd */ &daObjShelf::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
