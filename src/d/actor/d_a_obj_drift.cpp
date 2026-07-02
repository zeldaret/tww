/**
 * d_a_obj_drift.cpp
 * Object - Floating tree platform
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_drift.h"
#include "d/actor/d_a_player.h"
#include "d/d_a_obj.h"
#include "d/d_kankyo.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_bg_s_movebg_actor.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "JAZelAudio/JAZelAudio_SE.h"
#include "JSystem/J3DGraphAnimator/J3DModel.h"
#include "JSystem/J3DGraphBase/J3DSys.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "SSystem/SComponent/c_cc_d.h"
#include "SSystem/SComponent/c_phase.h"
#include "SSystem/SComponent/c_math.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/mtx/mtxvec.h"
#include "dolphin/mtx/vec.h"
#include "dolphin/os/OS.h"
#include "dolphin/types.h"
#include "f_op/f_op_actor_iter.h"
 #include "f_op/f_op_actor_mng.h"
#include "f_pc/f_pc_base.h"
#include "f_pc/f_pc_manager.h"
#include "f_pc/f_pc_name.h"
#include "f_pc/f_pc_searcher.h"
#include "m_Do/m_Do_mtx.h"
 #include "res/Object/Kryu.h"
 
namespace daObjDrift {
    namespace {
        struct Attr_c {
            /* 0x00 */ f32 mWaveHeight;
            /* 0x04 */ f32 mWaveSpeed;
            /* 0x08 */ f32 mWavePhase;
            /* 0x0C */ f32 mWaveAmplitude;
            /* 0x10 */ f32 mStateYBase;
            /* 0x14 */ s16 mRotSpeedXInit;
            /* 0x16 */ s16 mRotSpeedXPad;
            /* 0x18 */ f32 mWaveSinScale;
            /* 0x1C */ f32 mField1C;
            /* 0x20 */ f32 mRotAccelWait;
            /* 0x24 */ f32 mRotAccelRot;
            /* 0x28 */ f32 mPosMoveDamp;
            /* 0x2C */ s16 mRotSpeedYInit;
            /* 0x2E */ s16 mRotSpeedZInit;
            /* 0x30 */ f32 mRotSinScale;
            /* 0x34 */ f32 mStateScale;
            /* 0x38 */ s16 mRotSpeedXAdd;
            /* 0x3A */ s16 mRotSpeedYAdd;
            /* 0x3C */ s16 mRotTimerMax;
            /* 0x3E */ s16 mField3E;
        };

        static const Attr_c L_attr = {
            /* mWaveHeight     */ 500.0f,
            /* mWaveSpeed      */ 0.04f,
            /* mWavePhase      */ 0.01f,
            /* mWaveAmplitude  */ 0.02f,
            /* mStateYBase     */ -20.0f,
            /* mRotSpeedXInit  */ 400,
            /* mRotSpeedXPad   */ 0,
            /* mWaveSinScale   */ 0.3f,
            /* mField1C        */ 0.12f,
            /* mRotAccelMode1  */ 0.8f,
            /* mRotAccelMode0  */ 0.5f,
            /* mPosMoveDamp    */ 0.07f,
            /* mRotSpeedYInit  */ 1000,
            /* mRotSpeedZInit  */ 1111,
            /* mRotSinScale    */ 0.01f,
            /* mStateScale     */ 0.5f,
            /* mRotSpeedXAdd   */ 30,
            /* mRotSpeedYAdd   */ 30,
            /* mRotTimerMax    */ 10,
            /* mField3E        */ 0,
        };
    } // namespace
} // namespace daObjDrift

const char daObjDrift::Act_c::M_arcname[] = "Kryu"; /* 0x40 */

const dCcD_SrcCyl daObjDrift::Act_c::M_cyl_src = { /* 0x48 */
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_WIND,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
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
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 300.0f,
        /* Height */ 600.0f,
    }},
};

namespace daObjDrift {
    namespace {
        /* 0x8C */ static const f32 l_cullMinX = -550.0f;
        /* 0x90 */ static const f32 l_cullMinY = -180.0f;
        /* 0x94 */ static const f32 l_cullMaxX = 550.0f;
        /* 0x98 */ static const f32 l_cullMaxY = 605.0f;
        /* 0x9C */ static const f32 l_zero = 0.0f;
        /* 0xA0 */ static const f32 l_rndFX = 32768.0f;
        /* 0xA4 */ static const f32 l_scale = 5.0f;
        // /* 0xA8 */ static const s16 pf_name[2] = {0xD6, 0xD7};
        /* 0xAC */ static const f32 l_flowerOffsetX = -489.35f;
        /* 0xB0 */ static const f32 l_flowerOffsetY = 600.0f;
        /* 0xB4 */ static const f32 l_targetDistSq = 302500.0f;
        /* 0xB8 */ static const f32 l_rotTimerInc = 1.0f;
        /* 0xBC */ static const f32 l_seReverb = -1.0f;
        // /* 0xC0 */ static const f32 l_rotTimerLimit = 176.0f;
        // /* 0xC4 */ static const u32 l_rotTimerConvHi = 0x80000000;
        /* 0xC8 */ static const f32 l_rideYMax = 400.0f;
        /* 0xCC */ static const f32 l_rideDistSqLow = 129600.0f;
        /* 0xD0 */ static const f32 l_rideDistSqHigh = 48400.0f;
        /* 0xD4 */ static const f32 l_rotFactorRide = 0.2f;
        /* 0xD8 */ static const f32 l_targetPosScale = 0.95f;
    }
} // namespace daObjDrift

/* 000000EC-000001A0       .text CreateHeap__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_KRYU_BDL_RYU_00_e);
    JUT_ASSERT(0x13A, model_data != NULL);
    mModel = mDoExt_J3DModel__create(model_data, 0x80000, 0x11000022);
    return mModel != NULL;
}

/* 000001A0-00000370       .text Create__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Create() {
    f32 L_waterY[2];
    cullMtx = mModel->getBaseTRMtx();
    init_mtx();
    fopAc_ac_c* actor = this;
    f32 cullMinX = l_cullMinX;
    f32 cullMinY = l_cullMinY;
    f32 cullMaxX = l_cullMaxX;
    f32 cullMaxY = l_cullMaxY;
    fopAcM_setCullSizeBox(actor, cullMinX, cullMinY, cullMinX, cullMaxX, cullMaxY, cullMaxX);
    mStts.Init(0xFF, 0xFF, this);
    mCyl.Set(M_cyl_src);
    mCyl.SetStts(&mStts);
    mCyl.SetTgVec((cXyz&)cXyz::Zero);
    mCyl.OnTgNoHitMark();

    make_flower();
    mpBgW->SetRideCallback(rideCB);
    mode_wait_init();
    if (fopAcM_getWaterY(&home.pos, L_waterY)) {
        eyePos.y = L_waterY[0];
    }

    f32 zero = l_zero;
    mState[0] = zero;
    mState[1] = zero;
    mState[2] = zero;
    mState[3] = zero;
    mState[4] = zero;
    mState[5] = zero;
    mState[6] = zero;

    mRotSpeedX = cM_rndFX(l_rndFX);
    mRotSpeedY = cM_rndFX(l_rndFX);
    mRotSpeedZ = cM_rndFX(l_rndFX);
    mRideFlag = FALSE;

    mTargetAngleY = 0;
    mAngleChaseY = 0;

    mTargetPos.set((cXyz&)cXyz::Zero);
    mScaleModifier.set(l_scale, l_scale, l_scale);
    mHomePosCopy.x = current.pos.x;
    mHomePosCopy.y = current.pos.y;
    mHomePosCopy.z = current.pos.z;
    f32 prevY = mHomePosCopy.y;
    mPrevMtxTransY = prevY;
    mPrevPrevMtxTransY = prevY;

    f32 endZero = l_zero;
    field_0x4D0 = endZero;
    field_0x4D4 = endZero;

    return TRUE;
}

/* 00000370-0000050C       .text Mthd_Create__Q210daObjDrift5Act_cFv */
cPhs_State daObjDrift::Act_c::Mthd_Create() {
    fopAcM_ct(this, Act_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhase, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        mType = daObj::PrmAbstract(this, PRM_STATE_W, PRM_STATE_S);
        phase_state = MoveBGCreate(
            M_arcname,
            dRes_INDEX_KRYU_DZB_RYU_00_e,
            dBgS_MoveBGProc_TypicalRotY,
            0x1B80);
        JUT_ASSERT(0x19B, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 0000075C-000007EC       .text make_flower__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::make_flower() {
    if (mType >= 0 && mType <= 1) {
        cXyz pos;
        csXyz angle;
        calc_flower_param(&pos, &angle);
        static const s16 pf_name[2] = {0xD6, 0xD7};
        mFlowerPid = fopAcM_create(
            pf_name[mType],
            0,
            &pos,
            fopAcM_GetHomeRoomNo(this),
            &angle,
            NULL,
            -1,
            NULL);
    } else {
        mFlowerPid = fpcM_ERROR_PROCESS_ID_e;
    }
}

/* 000007EC-00000890       .text calc_flower_param__Q210daObjDrift5Act_cFP4cXyzP5csXyz */
void daObjDrift::Act_c::calc_flower_param(cXyz* i_pos, csXyz* i_angle) {
    static cXyz offset_vec(l_flowerOffsetX, l_flowerOffsetY, l_zero);

    PSMTXMultVec(mMtx, &offset_vec, i_pos);
    mDoMtx_MtxToRot(mMtx, i_angle);
}

/* 00000890-00000954       .text set_flower_current__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_flower_current() {
    fpc_ProcID pid = mFlowerPid;
    if (pid == fpcM_ERROR_PROCESS_ID_e) {
        return;
    }

    fopAc_ac_c* flower = fopAcM_SearchByID(pid);
    if (flower != NULL) {
        cXyz pos;
        csXyz angle;
        calc_flower_param(&pos, &angle);
        flower->current.pos = pos;
        if (mType == 0) {
            flower->shape_angle.x = angle.x;
            flower->shape_angle.y = angle.y;
            flower->shape_angle.z = angle.z;
        } else {
            flower->current.angle.x = angle.x;
            flower->current.angle.y = angle.y;
            flower->current.angle.z = angle.z;
        }
    }
}

/* 00000954-0000095C       .text Delete__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Delete() {
    return TRUE;
}

/* 0000095C-000009A8       .text Mthd_Delete__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Mthd_Delete() {
    BOOL ret = MoveBGDelete();
    dComIfG_resDeleteDemo(&mPhase, M_arcname);
    return ret;
}

/* 000009A8-000009C0       .text mode_wait_init__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_wait_init() {
    actor_status = actor_status | fopAcStts_NOCULLEXEC_e;
    mMode = MODE_WAIT;
}

/* 000009C0-00000A80       .text mode_wait__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_wait() {
    if (mCyl.ChkTgHit()) {
        mCyl.ClrTgHit();
        f32 dist = fopAcM_searchPlayerDistanceXZ2(this);
        if (dist > l_targetDistSq) {
            cXyz* l_tgrVec = mCyl.GetTgRVecP();
            mTargetPos.x = l_tgrVec->x;
            mTargetPos.y = l_tgrVec->y;
            mTargetPos.z = l_tgrVec->z;
            mTargetPos.normalizeZP();
            mode_rot_init();
        }
    } else {
        mCyl.MoveCAtTg(current.pos);
        dComIfG_Ccsp()->Set(&mCyl);
    }
}

/* 00000A80-00000B38       .text mode_rot_init__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_rot_init() {
    fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
    mTargetAngleY = shape_angle.y + 0x8000;
    mAngleChaseY = 0;
    shape_angle.y += 10;
    mRotTimer = l_zero;
    mMode = MODE_ROT;

    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::zel_basic->seStart(
        JA_SE_OBJ_RYUBOKU_MOVE,
        &eyePos,
        0,
        reverb,
        l_rotTimerInc,
        l_rotTimerInc,
        l_seReverb,
        l_seReverb,
        0
    );
}

/* 00000B38-00000C3C       .text mode_rot__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_rot() {
    s16 yDiff = mTargetAngleY - shape_angle.y;
    if (yDiff <= 0) {
        shape_angle.y = mTargetAngleY;
        mTargetPos.set(cXyz::Zero);
        mode_wait_init();
    } else {
        if (yDiff < 0x2000) {
            cLib_chaseS(&mAngleChaseY, 0x14, 0xA);
        } else {
            cLib_chaseS(&mAngleChaseY, 0x190, 0x14);
        }
        shape_angle.y = shape_angle.y + mAngleChaseY;
    }

    if (mRotTimer >= L_attr.mRotTimerMax) {
        mRotTimer = 0.0f;
        field_0x4D0 = 1.0f;
    } else {
        mRotTimer += 1.0f;
    }
}

/* 00000C3C-00000D18       .text set_mtx__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    f32 axisZ = mState[5];
    f32 axisY = 1.0f;
    f32 axisX = mState[6];
    Quaternion quat;
    cXyz axis(axisX, axisY, axisZ);
    daObj::quat_rotBaseY2(&quat, axis);
    mDoMtx_stack_c::quatM(&quat);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), mMtx);
    mPrevPrevMtxTransY = mPrevMtxTransY;
    mPrevMtxTransY = mHomePosCopy.y;
    mHomePosCopy.x = mDoMtx_stack_c::get()[0][3];
    mHomePosCopy.y = mDoMtx_stack_c::get()[1][3];
    mHomePosCopy.z = mDoMtx_stack_c::get()[2][3];
}

/* 00000D18-00000D54       .text init_mtx__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::init_mtx() {
    J3DModel* l_model = mModel;
    l_model->setBaseScale(scale);
    set_mtx();
}

/* 00000D54-00000EC4       .text rideCB__Q210daObjDrift5Act_cFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjDrift::Act_c::rideCB(dBgW*, fopAc_ac_c* i_this, fopAc_ac_c* i_ride) {
    Act_c* drift = (Act_c*)i_this;
    daPy_py_c* player = (daPy_py_c*)i_ride;
    if (fopAcM_GetProfName(player) != fpcNm_PLAYER_e) {
        return;
    }
    f32 ratio = 1.0f / L_attr.mWaveHeight;
    drift->mState[0] = L_attr.mStateYBase;
    cXyz delta;
    cXyz localDelta;
    Mtx invMtx;
    delta = player->current.pos - drift->current.pos;
    if (PSMTXInverse(drift->mMtx, invMtx) &&
        !cLib_checkBit<u32>(*(u32*)((u8*)&g_dComIfG_gameInfo + 0x5CC8), 0x100)) {
        PSMTXMultVecSR(invMtx, &delta, &localDelta);
        f32 sqMag = localDelta.abs2XZ();
        if (localDelta.y < l_rideYMax) {
            if (sqMag < l_rideDistSqLow) {
                drift->mRideFlag = TRUE;
            }
        } else if (localDelta.y < l_cullMaxX) {
            if (sqMag < l_rideDistSqHigh) {
                drift->mRideFlag = TRUE;
            }
        }
    } else {
        drift->mRideFlag = TRUE;
    }
    if (drift->mRideFlag == FALSE) {
        drift->mState[1] = delta.z * (ratio * L_attr.mField1C);
        drift->mState[2] = delta.x * (ratio * L_attr.mField1C);
    }
}

/* 00000EC4-00001104       .text set_current__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_current() {
    f32 y = mState[0] + home.pos.y;
    mRotSpeedX += L_attr.mRotSpeedXInit;
    f32 yDelta = y - current.pos.y;
    f32 sinVal = JMASSin(mRotSpeedX);
    gravity = yDelta * L_attr.mWaveAmplitude
            + sinVal * L_attr.mWaveSinScale;
    daObj::posMoveF_stream(this, NULL, &cXyz::Zero, L_attr.mWaveSpeed, L_attr.mWavePhase);
    f32 chaseFactor;
    f32 rotFactor;
    if (mRideFlag != 0) {
        rotFactor = l_rotFactorRide;
    } else {
        rotFactor = l_rotTimerInc;
    }
    if (mMode == MODE_ROT) {
        chaseFactor = L_attr.mRotAccelRot;
    } else {
        chaseFactor = L_attr.mRotAccelWait;
    }
    PSVECScale(&mTargetPos, &mTargetPos, l_targetPosScale);
    mRotSpeedY += L_attr.mRotSpeedYInit;
    mRotSpeedZ += L_attr.mRotSpeedZInit;
    f32 sinY = JMASSin(mRotSpeedY);
    f32 sinZ = JMASSin(mRotSpeedZ);
    f32 diffZ = mState[5] - mState[1];
    f32 diffX = mState[6] - mState[2];
    f32 f8 = mTargetPos.x * L_attr.mStateScale
           + (rotFactor * (sinZ * L_attr.mRotSinScale)
           - diffX * chaseFactor);
    mState[3] += mTargetPos.z * L_attr.mStateScale
               + (rotFactor * (sinY * L_attr.mRotSinScale)
               - diffZ * chaseFactor);
    mState[4] += f8;
    mState[3] *= L_attr.mPosMoveDamp;
    mState[4] *= L_attr.mPosMoveDamp;
    mState[5] += mState[3];
    mState[6] += mState[4];
    mState[0] = l_zero;
    mState[1] = l_zero;
    mState[2] = l_zero;
    mRideFlag = FALSE;
}

/* 00001104-000011D0       .text Execute__Q210daObjDrift5Act_cFPPA3_A4_f */
BOOL daObjDrift::Act_c::Execute(Mtx** vMtx) {
    typedef void (Act_c::*ModeProcFunc)();
    static ModeProcFunc mode_proc[] = {
        &Act_c::mode_wait,
        &Act_c::mode_rot,
    };
    (this->*mode_proc[mMode])();

    set_current();
    set_mtx();
    *vMtx = &mMtx;
    set_flower_current();
    return TRUE;
}

/* 000011D0-00001270       .text Draw__Q210daObjDrift5Act_cFv */
BOOL daObjDrift::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mModel, &tevStr);
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mModel);
    dComIfGd_setList();
    return TRUE;
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
    return ((daObjDrift::Act_c*)i_this)->Draw();
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
