//
// Generated by dtk
// Translation Unit: d_a_obj_swhammer.cpp
//

#include "d/actor/d_a_obj_swhammer.h"
#include "d/res/res_mhmrsw.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_player_main.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep
#include "weak_data_1811.h" // IWYU pragma: keep

namespace daObjSwhammer {
    namespace {
        struct Attr_c {
            /* 0x00 */ float mVSpring;
            /* 0x04 */ float mIntVSpeedDecay;
            /* 0x08 */ float mExtVSpeedDecay;
            /* 0x0C */ float mVibMag0Mult;
            /* 0x10 */ float mVibSpring;
            /* 0x14 */ float mAngleSpeedDecay;
            /* 0x18 */ short mCrushDuration;
            /* 0x1C */ float mUncrushSpeed0;
            /* 0x20 */ float mUncrushSpring;
            /* 0x24 */ float mUncrushSpeedDecay;
        };

        static const Attr_c L_attr = {
            /* mVSpring           */ 0.8f,
            /* mIntVSpeedDecay    */ 0.55f,
            /* mExtVSpeedDecay    */ 0.55f,
            /* mVibMag0Mult       */ 1.0f,
            /* mVibSpring         */ 0.99f,
            /* mAngleSpeedDecay   */ 0.18f,
            /* mCrushDuration     */ 18,
            /* mUncrushSpeed0     */ 0.0f,
            /* mUncrushSpring     */ 0.8f,
            /* mUncrushSpeedDecay */ 0.45f
        };

        inline const Attr_c & attr() { return L_attr; }
    }
}

int daObjSwhammer::Act_c::M_damage;
short daObjSwhammer::Act_c::M_damage_dir;
Mtx daObjSwhammer::Act_c::M_tmp_mtx;

const char daObjSwhammer::Act_c::M_arcname[] = "MhmrSW";
const dCcD_SrcCyl daObjSwhammer::Act_c::M_cyl_src_co = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 100.0f,
        /* Height */ 112.5f,
    },
};
const dCcD_SrcCyl daObjSwhammer::Act_c::M_cyl_src_tg = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ ~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT),
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 50.0f,
        /* Height */ 112.5f,
    },
};
const GXColor color = {0xA0, 0xA0, 0x80, 0xFF};

/* 000000EC-00000260       .text __ct__Q213daObjSwhammer5Act_cFv */
daObjSwhammer::Act_c::Act_c() {
    mSmokeCb.setColor(color);
}

/* 000004B0-0000058C       .text CreateHeap__Q213daObjSwhammer5Act_cFv */
BOOL daObjSwhammer::Act_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData *>(dComIfG_getObjectRes(M_arcname, MHMRSW_BDL_MHMRSW));
    JUT_ASSERT(0x18b, modelData != NULL);
    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpModel) {
        modelData->getJointNodePointer(1)->setCallBack(jnodeCB);
        mpModel->setUserArea((u32) this);
    }
    return mpModel != NULL;
}

/* 0000058C-0000070C       .text Create__Q213daObjSwhammer5Act_cFv */
int daObjSwhammer::Act_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    init_mtx();
    fopAcM_setCullSizeSphere(this, 0.0f, 30.0f, 0.0f, 120.0f);

    mSttsCo.Init(0xFF, 0xFF, this);
    mCylCo.Set(M_cyl_src_co);
    mCylCo.SetStts(&mSttsCo);

    mSttsTg.Init(0xFF, 0xFF, this);
    mCylTg.Set(M_cyl_src_tg);
    mCylTg.SetStts(&mSttsTg);
    mCylTg.OnTgNoHitMark();

    mCrushTimer = 0;
    mCrushState = 0;
    mScaleYSpeed = 0.0f;
    mScaleY = 1.0f;
    mAngleZ = 0.0f;
    mAngleX = 0.0f;
    mAngleSpeedZ = 0.0f;
    mAngleSpeedX = 0.0f;
    mVSpeed = 0.0f;
    mTargetHFrac = 0.0f;

    if (is_switch()) {
        mCurHFrac = 0.0f;
        mTopPos = -60.0f;
        mode_lower_init();
    } else {
        mCurHFrac = 1.0f;
        mTopPos = 0.0f;
        mode_upper_init();
    }
    attention_info.distances[fopAc_Attn_TYPE_MISC_e] = 0x2D;
    attention_info.position.y = current.pos.y + mTopPos + 120.0f;
    eyePos.y = attention_info.position.y;
    return 1;
}

/* 0000070C-000007F8       .text _create__Q213daObjSwhammer5Act_cFv */
s32 daObjSwhammer::Act_c::_create() {
    fopAcM_SetupActor(this, Act_c);

    s32 phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(M_arcname, MHMRSW_DZB_MHMRSW, NULL, 0xa80);
        JUT_ASSERT(0x1e9, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 000007F8-00000828       .text Delete__Q213daObjSwhammer5Act_cFv */
BOOL daObjSwhammer::Act_c::Delete() {
    mSmokeCb.end();
    return TRUE;
}

/* 00000828-0000087C       .text _delete__Q213daObjSwhammer5Act_cFv */
bool daObjSwhammer::Act_c::_delete() {
    int ret = MoveBGDelete();
    dComIfG_resDelete(&mPhs, M_arcname);
    return ret;
}

/* 0000087C-000008E8       .text set_mtx__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000008E8-00000938       .text init_mtx__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 00000938-00000A58       .text set_damage__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::set_damage() {
    u8 attackState = daPy_getPlayerActorClass()->getCutType();
    M_damage = 0;
    M_damage_dir = 0;
    if (mCylTg.ChkTgHit()) {
        cCcD_Obj *hitObj = mCylTg.GetTgHitObj();
        fopAc_ac_c* hitActor = mCylTg.GetTgHitAc();
        if (hitObj->ChkAtType(AT_TYPE_SKULL_HAMMER) && fopAcM_GetProfName(hitActor) == PROC_PLAYER) {
            if (attackState == 0x12 || attackState == 0x13) {
                M_damage = 1;
            } else if (attackState == 0x11) {
                M_damage_dir = cM_atan2s(mCylTg.GetTgRVecP()->x, mCylTg.GetTgRVecP()->z);
                M_damage = 2;
            }
        }
        daObj::HitSeStart(&eyePos, current.roomNo, &mCylTg, 0x11);
        daObj::HitEff_hibana(this, &mCylTg);
        mCylTg.ClrTgHit();
    }
    mSttsTg.Move();
}

/* 00000A58-00000ABC       .text vib_start__Q213daObjSwhammer5Act_cFsf */
void daObjSwhammer::Act_c::vib_start(short dir, float mag) {
    mAngleSpeedZ = mag * attr().mVibMag0Mult * cM_scos(dir);
    mAngleSpeedX = mag * attr().mVibMag0Mult * cM_ssin(dir);
}

/* 00000ABC-00000B34       .text vib_proc__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::vib_proc() {
    float angleAccelX = -(mAngleX * attr().mVibSpring) - mAngleSpeedX * attr().mAngleSpeedDecay;
    float angleAccelZ = -(mAngleZ * attr().mVibSpring) - mAngleSpeedZ * attr().mAngleSpeedDecay;

    mAngleSpeedZ += angleAccelZ;
    mAngleSpeedX += angleAccelX;
    mAngleZ += mAngleSpeedZ;
    mAngleX += mAngleSpeedX;
}

/* 00000B34-00000B40       .text crush_start__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::crush_start() {
    mCrushState = 1;
}

/* 00000B40-00000BF0       .text crush_proc__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::crush_proc() {
    if (mCrushState == 1) {
        mScaleY = 0.2f;
        mCrushState = 2;
        mCrushTimer = attr().mCrushDuration;
        return;
    }
    if (mCrushState == 2) {
        if (--mCrushTimer > 0) {
            return;
        }
        mCrushState = 0;
        mScaleYSpeed = attr().mUncrushSpeed0;
        return;
    }
    mScaleYSpeed += -((mScaleY - 1.0f) * attr().mUncrushSpring) - mScaleYSpeed * attr().mUncrushSpeedDecay;
    mScaleY += mScaleYSpeed;
}

/* 00000BF0-00000DB8       .text eff_crush__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::eff_crush() {
    if (mMode == 0) {
        dComIfGp_particle_set(dPa_name::ID_SCENE_81B7, &current.pos);
        dComIfGp_particle_set(dPa_name::ID_SCENE_81B8, &current.pos);
    }
    static const cXyz particle_scale(1.5f, 1.5f, 1.0f);
    JPABaseEmitter* emitter = dComIfGp_particle_setToon(dPa_name::ID_COMMON_2027, &current.pos, NULL, NULL, 200, &mSmokeCb, -1, NULL, NULL, &particle_scale);
    if (emitter) {
        emitter->setRate(30.0f);
        emitter->setMaxFrame(1);
        emitter->setLifeTime(45);
        emitter->setAwayFromCenterSpeed(0.0f);
        emitter->setAwayFromAxisSpeed(38.0f);
        static const JGeometry::TVec3<f32> vec(0.0f, 15.0f, 0.0f);
        emitter->setEmitterTranslation(vec);
    }
}

/* 00000DB8-00000E74       .text calc_top_pos__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::calc_top_pos() {
    float diff = mCurHFrac - mTargetHFrac;
    float decay = mCurHFrac > 0.0f && mCurHFrac < 1.0f
        ? attr().mIntVSpeedDecay
        : attr().mExtVSpeedDecay;

    mVSpeed -= diff * attr().mVSpring;
    mVSpeed -= mVSpeed * decay;
    mCurHFrac += mVSpeed;
    mCurHFrac = cLib_maxLimit(mCurHFrac, 1.0f);
    mTopPos = (1.0f - mCurHFrac) * -60.0f;
}

/* 00000E74-00000F94       .text jnodeCB__Q213daObjSwhammer5Act_cFP7J3DNodei */
BOOL daObjSwhammer::Act_c::jnodeCB(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        daObjSwhammer::Act_c *i_this = (daObjSwhammer::Act_c*) model->getUserArea();
        J3DJoint* joint = static_cast<J3DJoint*>(node);
        s32 jntNo = joint->getJntNo();

        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
        mDoMtx_stack_c::transM(0.0f, (1.0f - i_this->mScaleY) * 20.0f, 0.0f);
        mDoMtx_stack_c::scaleM(1.0f, i_this->mScaleY, 1.0f);
        mDoMtx_stack_c::transM(0.0f, i_this->mTopPos, 0.0f);

        cXyz tmp(i_this->mAngleX, 1.0f, i_this->mAngleZ);
        Quaternion quat;
        daObj::quat_rotBaseY2(&quat, tmp);
        mDoMtx_stack_c::transM(0.0f, -20.0f, 0.0f);
        mDoMtx_stack_c::quatM(&quat);
        mDoMtx_stack_c::transM(0.0f, 20.0f, 0.0f);

        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    }
    return TRUE;
}

/* 00000F94-00001000       .text mode_upper_init__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::mode_upper_init() {
    mCylTg.SetH(112.5f);
    mCylCo.SetH(112.5f);
    mTargetHFrac = 1.0f;
    m5FC = false;
    cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
    mMode = 0;
}

/* 00001000-000010F4       .text mode_upper__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::mode_upper() {
    if (M_damage == 1) {
        m5FC = true;
        mode_u_l_init();
    } else if (is_switch()) {
        mode_u_l_init();
    } else if (M_damage == 2) {
        vib_start(M_damage_dir, 1.0f);
        fopAcM_seStart(this, JA_SE_OBJ_HAMMER_SW_SWING, 0);
    }
}

/* 000010F4-0000117C       .text mode_u_l_init__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::mode_u_l_init() {
    fopAcM_seStart(this, JA_SE_OBJ_HAMMER_SW_ON, 0);
    mTargetHFrac = 0.0f;
    mMode = 1;
}

/* 0000117C-0000121C       .text mode_u_l__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::mode_u_l() {
    if (mCurHFrac <= 0.0f) {
        on_switch();
        if (m5FC) {
            off_switch2();
        }
        mode_lower_init();
    }
}

/* 0000121C-0000128C       .text mode_lower_init__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::mode_lower_init() {
    mCylTg.SetH(52.5f);
    mCylCo.SetH(52.5f);
    mTargetHFrac = 0.0f;
    m5FC = false;
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
    mMode = 2;
}

/* 0000128C-00001330       .text mode_lower__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::mode_lower() {
    if (!is_switch()) {
        fopAcM_seStart(this, JA_SE_OBJ_HAMMER_SW_OFF, 0);
        mode_l_u_init();
    }
}

/* 00001330-00001348       .text mode_l_u_init__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::mode_l_u_init() {
    mTargetHFrac = 1.0f;
    mMode = 3;
}

/* 00001348-00001380       .text mode_l_u__Q213daObjSwhammer5Act_cFv */
void daObjSwhammer::Act_c::mode_l_u() {
    if (mCurHFrac >= 1.0f) {
        mode_upper_init();
    }
}

/* 00001380-00001504       .text Execute__Q213daObjSwhammer5Act_cFPPA3_A4_f */
BOOL daObjSwhammer::Act_c::Execute(Mtx** mtx) {
    set_damage();
    if (M_damage == 1) {
        crush_start();
        eff_crush();
    }
    typedef void (daObjSwhammer::Act_c::*procFunc)();
    static procFunc mode_proc[] = {
        &daObjSwhammer::Act_c::mode_upper,
        &daObjSwhammer::Act_c::mode_u_l,
        &daObjSwhammer::Act_c::mode_lower,
        &daObjSwhammer::Act_c::mode_l_u,
    };
    (this->*mode_proc[mMode])();
    calc_top_pos();
    vib_proc();
    crush_proc();
    set_mtx();
    *mtx = &M_tmp_mtx;
    mCylTg.SetC(current.pos);
    mCylCo.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCylTg);
    dComIfG_Ccsp()->Set(&mCylCo);
    attention_info.position.y = current.pos.y + mTopPos + 120.0f;
    eyePos.y = attention_info.position.y;
    return TRUE;
}

/* 00001504-00001564       .text Draw__Q213daObjSwhammer5Act_cFv */
BOOL daObjSwhammer::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return TRUE;
}

namespace daObjSwhammer {
namespace {
/* 00001564-00001584       .text Mthd_Create__Q213daObjSwhammer30@unnamed@d_a_obj_swhammer_cpp@FPv */
s32 Mthd_Create(void* i_this) {
    return static_cast<daObjSwhammer::Act_c*>(i_this)->_create();
}

/* 00001584-000015A8       .text Mthd_Delete__Q213daObjSwhammer30@unnamed@d_a_obj_swhammer_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return static_cast<daObjSwhammer::Act_c*>(i_this)->_delete();
}

/* 000015A8-000015C8       .text Mthd_Execute__Q213daObjSwhammer30@unnamed@d_a_obj_swhammer_cpp@FPv */
int Mthd_Execute(void* i_this) {
    return static_cast<daObjSwhammer::Act_c*>(i_this)->MoveBGExecute();
}

/* 000015C8-000015F4       .text Mthd_Draw__Q213daObjSwhammer30@unnamed@d_a_obj_swhammer_cpp@FPv */
void Mthd_Draw(void* i_this) {
    static_cast<daObjSwhammer::Act_c*>(i_this)->Draw();
}

/* 000015F4-00001620       .text Mthd_IsDelete__Q213daObjSwhammer30@unnamed@d_a_obj_swhammer_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return static_cast<daObjSwhammer::Act_c*>(i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjSwhammer

actor_process_profile_definition g_profile_Obj_Swhammer = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0002,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Swhammer,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjSwhammer::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x0082,
    /* Actor SubMtd */ &daObjSwhammer::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLSPHERE_CUSTOM_e,
};
