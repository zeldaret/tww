/**
 * d_a_obj_mshokki.cpp
 * Object - Dishes and cutlery inside Forsaken Fortress
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_mshokki.h"
#include "d/res/res_mshokki.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_kankyo.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_hostIO.h"

#if VERSION == VERSION_DEMO
class daObjMshokki_HIO_c : public JORReflexible {
public:
    daObjMshokki_HIO_c();
    virtual ~daObjMshokki_HIO_c() {}

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
    /* 0x38 */ f32 m38;
    /* 0x3C */ f32 m3C;
    /* 0x40 */ s8 m40;
}; // size = 0x44

static daObjMshokki_HIO_c l_HIO;
#else
namespace L_HIO {
static const f32 m08 = 20.0f;
static const f32 m0C = 20.0f;
static const f32 m10 = 128.0f;
static const f32 m14 = 3072.0f;
static const f32 m18 = 4096.0f;
static const f32 m1C = 6.0f;
static const f32 m20 = 11.0f;
static const f32 m24 = 4096.0f;
static const f32 m28 = 1.0f;
static const f32 m2C = 24.0f;
static const f32 m30 = 0.0f;
static const f32 m34 = 0.5f;
static const f32 m38 = 0.8f;
static const f32 m3C = 0.1f;
} // namespace L_HIO
#endif

namespace {
static const char l_arcname[] = "Mshokki";
static const dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 35.0f,
        /* Height */ 50.0f,
    }},
};

struct LData {
    /* 0x00 */ f32 m00;
    /* 0x04 */ f32 radius;
    /* 0x08 */ f32 height;
    /* 0x0C */ f32 m0C;
}; // size = 0x10

static const LData l_data[] = {
    {20.0f, 15.0f, 40.0f, 6144.0f},
    {7.5f, 30.0f, 15.0f, 2048.0f},
    {15.0f, 15.0f, 30.0f, 8192.0f},
};
} // namespace

#if VERSION == VERSION_DEMO
daObjMshokki_HIO_c::daObjMshokki_HIO_c() {
    mNo = -1;
    m08 = 20.0f;
    m0C = 20.0f;
    m10 = 128.0f;
    m14 = 3072.0f;
    m18 = 4096.0f;
    m1C = 6.0f;
    m20 = 11.0f;
    m24 = 4096.0f;
    m28 = 1.0f;
    m2C = 24.0f;
    m30 = 0.0f;
    m34 = 0.5f;
    m38 = 0.8f;
    m3C = 0.1f;
    m40 = 0;
}
#endif

/* 00000078-00000108       .text set_mtx__14daObjMshokki_cFv */
void daObjMshokki_c::set_mtx() {
    mModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000108-0000012C       .text solidHeapCB__14daObjMshokki_cFP10fopAc_ac_c */
BOOL daObjMshokki_c::solidHeapCB(fopAc_ac_c* a_this) {
    return ((daObjMshokki_c*)a_this)->create_heap();
}

/* 0000012C-000001FC       .text create_heap__14daObjMshokki_cFv */
bool daObjMshokki_c::create_heap() {
    static s32 bdl_idx[] = {MSHOKKI_BDL_POT, MSHOKKI_BDL_OSARA, MSHOKKI_BDL_KOPPU};

    bool uVar3 = true;
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(l_arcname, bdl_idx[m60C]);
    if (modelData == NULL) {
        JUT_ASSERT(DEMO_SELECT(352, 356), FALSE);
        uVar3 = false;
    } else {
        mModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
        if (mModel == NULL) {
            uVar3 = false;
        }
    }
    return uVar3;
}

/* 000001FC-0000032C       .text checkCollision__14daObjMshokki_cFv */
bool daObjMshokki_c::checkCollision() {
    bool uVar4 = false;
    if (mCyl.ChkTgHit()) {
        cCcD_Obj* pcVar3 = mCyl.GetTgHitObj();
        if (pcVar3 != NULL) {
            if (pcVar3->ChkAtType(AT_TYPE_WIND)) {
                speedF = mCyl.GetTgRVecP()->absXZ() * HIO(m34);
                current.angle.y = cM_atan2s(mCyl.GetTgRVecP()->x, mCyl.GetTgRVecP()->z);
            } else {
                break_proc();
                uVar4 = true;
            }
        }
        mCyl.ClrTgHit();
    }
    return uVar4;
}

/* 0000032C-000004E4       .text co_hitCallback__14daObjMshokki_cFP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daObjMshokki_c::co_hitCallback(fopAc_ac_c* a_this, dCcD_GObjInf*, fopAc_ac_c* other_actor, dCcD_GObjInf*) {
    daObjMshokki_c* i_this = (daObjMshokki_c*)a_this;
    f32 fVar1;
    s16 sVar3 = cM_atan2s(i_this->current.pos.x - other_actor->current.pos.x, i_this->current.pos.z - other_actor->current.pos.z);
#if VERSION == VERSION_DEMO
    if (other_actor == dComIfGp_getPlayer(0) && abs(other_actor->current.angle.y - sVar3) < (s16)HIO(m24) && other_actor->speedF >= HIO(m1C) + HIO(m20) &&
        abs(i_this->m618 - i_this->m614) > 2)
#else
    if (other_actor == dComIfGp_getPlayer(0) && abs(other_actor->current.angle.y - sVar3) < HIO(m24) && other_actor->speedF >= HIO(m1C) + HIO(m20) &&
        abs(i_this->m618 - i_this->m614) > 2)
#endif
    {
        fVar1 = (other_actor->speedF - (HIO(m1C) + HIO(m20))) / HIO(m28);
        if (fVar1 > 1.0f) {
            fVar1 = 1.0f;
        }
        s32 cos = fVar1 * 6144.0f;
        i_this->speedF = other_actor->speedF * cM_scos(cos);
        i_this->speed.y = HIO(m30) * fVar1 + HIO(m2C);
        i_this->current.angle.y = sVar3;
        i_this->shape_angle.y = sVar3;
        i_this->mCyl.SetCoHitCallback(NULL);
        i_this->m618 = i_this->m614;
    } else if (other_actor->speedF >= HIO(m1C)) {
        fVar1 = (other_actor->speedF - HIO(m1C)) / HIO(m20);
        if (fVar1 > 1.0f) {
            fVar1 = 1.0f;
        }
        s16 angle_x = l_data[i_this->m60C].m0C * fVar1;
        s16 angle_y = other_actor->current.angle.y;
        i_this->shape_angle.x = angle_x;
        i_this->shape_angle.y = angle_y;
#if VERSION == VERSION_DEMO
        i_this->m61C = angle_y + HIO(m18) * 2.0f;
#else
        i_this->m61C = angle_y + (s16)(HIO(m18) * 2.0f);
#endif
    }
}

/* 000004E4-00000610       .text break_proc__14daObjMshokki_cFv */
void daObjMshokki_c::break_proc() {
    static u16 particle_id[] = {dPa_name::ID_COMMON_0441, dPa_name::ID_COMMON_043F, dPa_name::ID_COMMON_0440};

    dComIfGp_particle_set(particle_id[m60C], &current.pos, &shape_angle, NULL, 0xff, NULL, -1, &tevStr.mColorK0);
    fopAcM_seStartCurrent(this, JA_SE_OBJ_COL_SWC_CHNS, dComIfG_Bgsp()->GetMtrlSndId(mAcch.m_gnd));

    dKy_Sound_set(current.pos, 150, fopAcM_GetID(this), 5);
    fopAcM_delete(this);
}

/* 00000610-00000740       .text set_se__14daObjMshokki_cFv */
void daObjMshokki_c::set_se() {
    static s32 se_flag[] = {JA_SE_OBJ_CUP_SWING, JA_SE_OBJ_DISH_SWING, JA_SE_OBJ_CUP_SWING};

    s16 tmp = shape_angle.y - m61C;
#if VERSION == VERSION_DEMO
    if (abs(tmp) < HIO(m18)) {
#else
    if (abs(tmp) < (s32)HIO(m18)) {
#endif
        s16 uVar4 = (shape_angle.x / l_data[m60C].m0C) * 16384.0f;
        if (uVar4 > 0x4000) {
            uVar4 = 0x4000;
        }
        fopAcM_seStartCurrent(this, se_flag[m60C], cM_ssin(uVar4) * 100.0f);
    }
}

/* 00000740-00000A1C       .text _create__14daObjMshokki_cFv */
cPhs_State daObjMshokki_c::_create() {
    fopAcM_SetupActor(this, daObjMshokki_c);

    if (fopAcM_IsFirstCreating(this)) {
        m60C = param_get_arg();
        if (m60C < 0 || m60C >= 3) {
            JUT_ASSERT(DEMO_SELECT(644, 648), FALSE);
            m60C = 0;
        }
    }

    cPhs_State ret = dComIfG_resLoad(&mPhase, l_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0x4C0)) {
            fopAcM_SetMtx(this, mModel->getBaseTRMtx());
            set_mtx();
            mAcchCir.SetWall(50.0f, 35.0f);
            mAcch.Set(
                fopAcM_GetPosition_p(this),
                fopAcM_GetOldPosition_p(this),
                this,
                1,
                &mAcchCir,
                fopAcM_GetSpeed_p(this),
                fopAcM_GetAngle_p(this),
                fopAcM_GetShapeAngle_p(this)
            );
            mAcch.ClrWaterNone();
            mAcch.ClrRoofNone();
            mAcch.SetRoofCrrHeight(50.0f);
            mAcch.CrrPos(*dComIfG_Bgsp());
            mAcch.ClrGroundLanding();
            mStts.Init(100, 0xff, this);
            mCyl.Set(l_cyl_src);
            mCyl.SetStts(&mStts);
            mCyl.StartCTg(current.pos);
            mCyl.SetR(l_data[m60C].radius);
            mCyl.SetH(l_data[m60C].height);
            mCyl.SetCoHitCallback(co_hitCallback);
            fopAcM_SetGravity(this, -6.0f);
        } else {
            ret = cPhs_ERROR_e;
        }
    }

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("魔獣島内部の食器", &l_HIO);
    }
#endif
    return ret;
}

/* 00000C44-00000C74       .text _delete__14daObjMshokki_cFv */
bool daObjMshokki_c::_delete() {
    dComIfG_resDelete(&mPhase, l_arcname);

#if VERSION == VERSION_DEMO
    if (l_HIO.mNo >= 0) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
#endif
    return true;
}

/* 00000C74-00000E24       .text _execute__14daObjMshokki_cFv */
bool daObjMshokki_c::_execute() {
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mAcch.CrrPos(*dComIfG_Bgsp());

    speedF *= HIO(m38);
    if (speedF < HIO(m3C)) {
        speedF = 0.0f;
    }

    if (mAcch.ChkGroundHit()) {
        if (abs(shape_angle.x) > (s32)HIO(m10)) {
            shape_angle.x += -(s16)HIO(m10);
            shape_angle.y += (s16)HIO(m18);
            set_se();
        } else {
            shape_angle.x = 0;
        }
    } else {
        shape_angle.x += -(s32)HIO(m14);
    }

#if VERSION == VERSION_DEMO
    mCyl.SetR(l_HIO.m0C);
    mCyl.SetH(l_HIO.m08);
#endif

    if (m612 == 1 && mAcch.ChkGroundLanding()) {
        break_proc();
    } else {
        if (mAcch.ChkGroundHit() && !mAcch.ChkGroundLanding()) {
            m612 = 1;
        }

        mStts.Move();
        if (!checkCollision()) {
            set_mtx();
            mCyl.MoveCTg(current.pos);
            mStts.SetRoomId(current.roomNo);
            dComIfG_Ccsp()->Set(&mCyl);
            attention_info.position.x = current.pos.x;
            attention_info.position.y = current.pos.y + l_data[m60C].m00;
            attention_info.position.z = current.pos.z;
            eyePos = attention_info.position;
        }
    }
    m614++;
    return true;
}

/* 00000E24-00000E84       .text _draw__14daObjMshokki_cFv */
bool daObjMshokki_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);
    mDoExt_modelUpdateDL(mModel);
    return true;
}

/* 00000E84-00000EA4       .text daObjMshokki_Create__FP10fopAc_ac_c */
static cPhs_State daObjMshokki_Create(fopAc_ac_c* i_this) {
    return ((daObjMshokki_c*)i_this)->_create();
}

/* 00000EA4-00000EC8       .text daObjMshokki_Delete__FP14daObjMshokki_c */
static BOOL daObjMshokki_Delete(daObjMshokki_c* i_this) {
    return ((daObjMshokki_c*)i_this)->_delete();
}

/* 00000EC8-00000EEC       .text daObjMshokki_Execute__FP14daObjMshokki_c */
static BOOL daObjMshokki_Execute(daObjMshokki_c* i_this) {
    return ((daObjMshokki_c*)i_this)->_execute();
}

/* 00000EEC-00000F10       .text daObjMshokki_Draw__FP14daObjMshokki_c */
static BOOL daObjMshokki_Draw(daObjMshokki_c* i_this) {
    return ((daObjMshokki_c*)i_this)->_draw();
}

/* 00000F10-00000F18       .text daObjMshokki_IsDelete__FP14daObjMshokki_c */
static BOOL daObjMshokki_IsDelete(daObjMshokki_c*) {
    return TRUE;
}

static actor_method_class l_daObjMshokki_Method = {
    (process_method_func)daObjMshokki_Create,
    (process_method_func)daObjMshokki_Delete,
    (process_method_func)daObjMshokki_Execute,
    (process_method_func)daObjMshokki_IsDelete,
    (process_method_func)daObjMshokki_Draw,
};

actor_process_profile_definition g_profile_Obj_Mshokki = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Mshokki,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjMshokki_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Mshokki,
    /* Actor SubMtd */ &l_daObjMshokki_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
