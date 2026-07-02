/**
 * d_a_obj_drift.cpp
 * Object - Floating tree platform
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "JSystem/JUtility/JUTAssert.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_a_obj.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_obj_drift.h"
#include "d/d_kankyo.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_iter.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"
#include "f_pc/f_pc_name.h"
#include "d/actor/d_a_player.h"
#include "res/Object/Kryu.h"

namespace daObjDrift {
namespace {
    struct Attr_c {
        /* 0x00 */ f32 field_0x00;
        /* 0x04 */ f32 field_0x04;
        /* 0x08 */ f32 field_0x08;
        /* 0x0C */ f32 field_0x0C;
        /* 0x10 */ f32 field_0x10;
        /* 0x14 */ s16 field_0x14;
        /* 0x16 */ s16 field_0x16; // unused
        /* 0x18 */ f32 field_0x18;
        /* 0x1C */ f32 field_0x1C;
        /* 0x20 */ f32 field_0x20;
        /* 0x24 */ f32 field_0x24;
        /* 0x28 */ f32 field_0x28;
        /* 0x2C */ s16 field_0x2C;
        /* 0x2E */ s16 field_0x2E;
        /* 0x30 */ f32 field_0x30;
        /* 0x34 */ f32 field_0x34;
        /* 0x38 */ s16 field_0x38; // unused
        /* 0x3A */ s16 field_0x3A; // unused
        /* 0x3C */ s16 field_0x3C;
    };

    const Attr_c L_attr = {
        /* field_0x00 */ 500.0f,
        /* field_0x04 */ 0.04,
        /* field_0x08 */ 0.01,
        /* field_0x0C */ 0.02,
        /* field_0x10 */ -20.0f,
        /* field_0x14 */ 0x190,
        /* field_0x16 */ 0,
        /* field_0x18 */ 0.3,
        /* field_0x1C */ 0.12,
        /* field_0x20 */ 0.8,
        /* field_0x24 */ 0.5,
        /* field_0x28 */ 0.07,
        /* field_0x2C */ 0x3E8,
        /* field_0x2E */ 0x457,
        /* field_0x30 */ 0.01,
        /* field_0x34 */ 0.5,
        /* field_0x38 */ 0x1E,
        /* field_0x3A */ 0x1E,
        /* field_0x3C */ 10,
    };
    inline static const Attr_c& attr() { return L_attr; }
}
}
const char daObjDrift::Act_c::M_arcname[] = "Kryu";
const dCcD_SrcCyl daObjDrift::Act_c::M_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_WIND,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 300.0f,
        /* Height */ 600.0f,
    }},
};

/* 000000EC-000001A0       .text CreateHeap__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::CreateHeap() {
    J3DModelData *model_data = (J3DModelData *)dComIfG_getObjectRes(M_arcname, 
        dRes_INDEX_KRYU_BDL_RYU_00_e);
    JUT_ASSERT(0x13a, model_data != NULL);
    mpModel = mDoExt_J3DModel__create(model_data, 0x80000, 0x11000022);
    return mpModel != NULL;
}

/* 000001A0-00000370       .text Create__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Create() {
    f32 waterHeight;
    cullMtx = mpModel->getBaseTRMtx();
    init_mtx();
    fopAcM_setCullSizeBox(this, -550.0f,-180.0f,-550.0f,550.0f,605.0f,550.0f);
    mStts.Init(0xff, 0xff, this);
    mCyl.Set(M_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.SetTgVec((cXyz&)cXyz::Zero);
    mCyl.OnTgNoHitMark();
    make_flower();
    mpBgW->SetRideCallback(rideCB);
    mode_wait_init();
    if (fopAcM_getWaterY(&home.pos, &waterHeight)) {
        eyePos.y = waterHeight;
    }
    field_0x47C = 0.0f;
    field_0x480 = 0.0f;
    field_0x484 = 0.0f;
    field_0x488 = 0.0f;
    field_0x48C = 0.0f;
    field_0x490 = 0.0f;
    field_0x494 = 0.0f;
    field_0x498 = cM_rndFX(32768.0);
    field_0x49A = cM_rndFX(32768.0);
    field_0x49C = cM_rndFX(32768.0);
    field_0x49E = 0;
    field_0x4A0 = 0;
    field_0x4A2 = 0;
    field_0x4A4 = cXyz::Zero;
    field_0x4B0 = 5.0f;
    field_0x4B4 = 5.0f;
    field_0x4B8 = 5.0f;
    field_0x4BC = current.pos;
    f32 t = field_0x4BC.y;
    field_0x4C8 = t;
    field_0x4CC = t;
    field_0x4D0 = 0.0f;
    field_0x4D4 = 0.0f;
    return 1;
}

/* 00000370-0000050C       .text Mthd_Create__Q210daObjDrift5Act_cFv */
cPhs_State daObjDrift::Act_c::Mthd_Create() {
    fopAcM_ct(this, daObjDrift::Act_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhase, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        type = prm_get_type(); 
        // Heap size differs in demo version
        #if VERSION > VERSION_DEMO
            phase_state = MoveBGCreate(M_arcname, 7, dBgS_MoveBGProc_TypicalRotY, 0x1b80);
        #else
            phase_state = MoveBGCreate(M_arcname, 7, dBgS_MoveBGProc_TypicalRotY, 0x8000);
        #endif
        JUT_ASSERT(0x19b, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e))
    }
    return phase_state;
}

/* 0000075C-000007EC       .text make_flower__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::make_flower() {
    static const s16 pf_name[2] = { fpcNm_JBO_e, fpcNm_BO_e };
    csXyz angle;

    cXyz pos [2];
    if (type >= 0 && type <= 1) {
        calc_flower_param(pos, &angle);
        s8 room_no = home.roomNo;
        mProcId = fopAcM_create(pf_name[type], 0, pos, 
            room_no, &angle, NULL, 0xff, NULL);
    } else {
        mProcId = 0xffffffff;
    }
}

/* 000007EC-00000890       .text calc_flower_param__Q210daObjDrift5Act_cFP4cXyzP5csXyz */
void daObjDrift::Act_c::calc_flower_param(cXyz* pos, csXyz* angle) {
    static cXyz offset_vec(-489.35f, 600.0f, 0.0f);

    PSMTXMultVec(field_0x444, &offset_vec, pos);
    mDoMtx_MtxToRot(field_0x444, angle);
}

/* 00000890-00000954       .text set_flower_current__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_flower_current() {
    fopAc_ac_c* proc;
    csXyz angle;
    cXyz pos;
    if (mProcId == 0xffffffff) {
        return;
    }
    fpc_ProcID id = mProcId;
    proc = static_cast<fopAc_ac_c*>(fopAcIt_Judge(fpcSch_JudgeByID, &id));
    if (proc != NULL) {
        calc_flower_param(&pos, &angle);
        proc->current.pos = pos;
        if (type == 0) {
            proc->shape_angle = angle;
        } else {
            proc->current.angle = angle;
        }
    }
}

/* 00000954-0000095C       .text Delete__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Delete() {
    return 1;
}

/* 0000095C-000009A8       .text Mthd_Delete__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Mthd_Delete() {
    BOOL result = MoveBGDelete();
    #if VERSION > VERSION_DEMO
        dComIfG_resDelete(&mPhase, M_arcname);
    #else
        dComIfG_deleteObjectRes(M_arcname);
    #endif
    return result;
}

/* 000009A8-000009C0       .text mode_wait_init__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_wait_init() {
    fopAcM_OnStatus(this, fopAcStts_NOCULLEXEC_e);
    field_0x478 = 0;
}

/* 000009C0-00000A80       .text mode_wait__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_wait() {
    f32 dist;
    if (mCyl.ChkTgHit() != 0) {
        mCyl.ClrTgHit();
        dist = fopAcM_searchActorDistanceXZ2(this, dComIfGp_getPlayer(0));
        if (dist > 302500.0f) {
            field_0x4A4 = *mCyl.GetTgRVecP();
            field_0x4A4.normalizeZP();
            mode_rot_init();
        }
    } else {
        mCyl.MoveCAtTg(current.pos);
        g_dComIfG_gameInfo.play.mCcS.Set(&mCyl);
    }
}

/* 00000A80-00000B38       .text mode_rot_init__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_rot_init() {
    fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
    field_0x4A0 = shape_angle.y + -(s16)0x8000;
    field_0x4A2 = 0;
    shape_angle.y = shape_angle.y + 10;
    field_0x4D8 = 0.0f;
    field_0x478 = 1;
    fopAcM_seStart(this, 0x6a1c, 0);
}

/* 00000B38-00000C3C       .text mode_rot__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_rot() {
    short tmp;
    tmp = field_0x4A0 - shape_angle.y;
    if (tmp <= 0) {
        shape_angle.y = field_0x4A0;
        field_0x4A4 = cXyz::Zero;
        mode_wait_init();
    } else {
        if (tmp < 0x2000) {
            cLib_chaseS(&field_0x4A2, 0x14, 10);
        } else {
            cLib_chaseS(&field_0x4A2, 400, 0x14);
        }
        shape_angle.y = shape_angle.y + field_0x4A2;
    }
    if (field_0x4D8 >= attr().field_0x3C) {
        field_0x4D8 = 0.0f;
        field_0x4D0 = 1.0f;
    } else {
        field_0x4D8 += 1.0f;
    }
}

/* 00000C3C-00000D18       .text set_mtx__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    Quaternion out;
    cXyz vec(field_0x494, 1.0, field_0x490);

    daObj::quat_rotBaseY2(&out, vec);
    mDoMtx_stack_c::quatM(&out);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    PSMTXCopy(mDoMtx_stack_c::get(), field_0x444);
    field_0x4CC = field_0x4C8;
    field_0x4C8 = field_0x4BC.y;
    field_0x4BC.x = mDoMtx_stack_c::now[0][3];
    field_0x4BC.y = mDoMtx_stack_c::now[1][3];
    field_0x4BC.z = mDoMtx_stack_c::now[2][3];
}

/* 00000D18-00000D54       .text init_mtx__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00000D54-00000EC4       .text rideCB__Q210daObjDrift5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjDrift::Act_c::rideCB(dBgW*, fopAc_ac_c* param_2, fopAc_ac_c* param_3) {
    cXyz diff;
    Mtx inv;
    f32 mag;
    cXyz sr_vec;

    Act_c* i_this = (Act_c *)param_2;
    daPy_py_c* player = (daPy_py_c *)param_3;
    if (fopAcM_GetProfName(player) != fpcNm_PLAYER_e) {
        return;
    }

    // Needed this for computation at the end, but it was expected to be calculated early
    f32 attr_field_0x00_inv = 1.0f / attr().field_0x00;
    i_this->field_0x47C = attr().field_0x10;

    diff = player->current.pos - i_this->current.pos;
    if (MTXInverse(i_this->field_0x444, inv) && !dComIfGp_checkPlayerStatus0(0,0x100)) {

        MTXMultVecSR(inv, &diff, &sr_vec);
        mag = sr_vec.abs2XZ();
        if (sr_vec.y < 400.0f) {
            if (mag < 129600.0f) {
                i_this->field_0x49E = 1;
            }
        } else {
            if (sr_vec.y < 550.0f && mag < 48400.0f) {
                i_this->field_0x49E = 1;
            }
        }
    } else {
        i_this->field_0x49E = 1;
    }
    if (!i_this->field_0x49E) {
        i_this->field_0x480 = diff.z * (attr_field_0x00_inv * attr().field_0x1C);
        i_this->field_0x484 = diff.x * (attr_field_0x00_inv * attr().field_0x1C);
    }
}

/* 00000EC4-00001104       .text set_current__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_current() {
    #if VERSION > VERSION_DEMO
        f32 fvar2;
        f32 fvar1;
    #else
        f32 fvar1;
        f32 fvar2;
    #endif
    f32 g = field_0x47C + home.pos.y;

    field_0x498 = field_0x498 + attr().field_0x14;
    gravity = (g - current.pos.y) * attr().field_0x0C +
        cM_ssin(field_0x498) * attr().field_0x18;
    daObj::posMoveF_stream(this, NULL, &cXyz::Zero, attr().field_0x04, attr().field_0x08);
    if (!field_0x49E) {
        fvar1 = 1.0f;
    } else {
        fvar1 = 0.2f;
    }
    if (field_0x478 == 1) {
        fvar2 = attr().field_0x24;
    } else {
        fvar2 = attr().field_0x20;
    }
    PSVECScale(&field_0x4A4, &field_0x4A4, 0.95f);
    field_0x49A += attr().field_0x2C;
    field_0x49C += attr().field_0x2E;
    f32 dz = field_0x490 - field_0x480;
    f32 dx = field_0x494 - field_0x484;
    f32 inc_z = field_0x4A4.z * attr().field_0x34 + (fvar1 * (cM_ssin(field_0x49A) * attr().field_0x30) - dz * fvar2);
    f32 inc_x = field_0x4A4.x * attr().field_0x34 + (fvar1 * (cM_ssin(field_0x49C) * attr().field_0x30) - dx * fvar2);
    field_0x488 += inc_z;
    field_0x48C += inc_x;

    field_0x488 *= attr().field_0x28;
    field_0x48C *= attr().field_0x28;
    field_0x490 += field_0x488;
    field_0x494 += field_0x48C;
    field_0x47C = 0.0f;
    field_0x480 = 0.0f;
    field_0x484 = 0.0f;
    field_0x49E = 0;
}

/* 00001104-000011D0       .text Execute__Q210daObjDrift5Act_cFPPA3_A4_f */
BOOL daObjDrift::Act_c::Execute(Mtx** o_param_1) {
    static void (daObjDrift::Act_c::*mode_proc[])() = {
    &daObjDrift::Act_c::mode_wait,
    &daObjDrift::Act_c::mode_rot,
    };
    (this->*mode_proc[field_0x478])();
    set_current();
    set_mtx();
    *o_param_1 = &field_0x444;
    set_flower_current();
    return 1;
}

/* 000011D0-00001270       .text Draw__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return 1;
}

namespace daObjDrift {
namespace {
/* 00001270-00001290       .text Mthd_Create__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->Mthd_Create();
}

/* 00001290-000012B0       .text Mthd_Delete__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->Mthd_Delete();
}

/* 000012B0-000012D0       .text Mthd_Execute__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->MoveBGExecute();
}

/* 000012D0-000012FC       .text Mthd_Draw__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->MoveBGDraw();
}

/* 000012FC-00001328       .text Mthd_IsDelete__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjDrift

actor_process_profile_definition g_profile_Obj_Drift = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0002,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Drift_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjDrift::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Drift_e,
    /* Actor SubMtd */ &daObjDrift::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
