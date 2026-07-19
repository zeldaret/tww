/**
 * d_a_obj_drift.cpp
 * Object - Floating tree platform
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_drift.h"
#include "d/actor/d_a_player.h"
#include "res/Object/Kryu.h"
 
namespace daObjDrift {
    namespace {
        struct Attr_c {
            /* 0x00 */ f32 mWaveHeight;
            /* 0x04 */ f32 mWaveSpeed;
            /* 0x08 */ f32 mWavePhase;
            /* 0x0C */ f32 mWaveAmplitude;
            /* 0x10 */ f32 mRideYOff;
            /* 0x14 */ s16 mWavePhaseXStep;
            /* 0x16 */ s16 field_0x16;
            /* 0x18 */ f32 mWaveSinScale;
            /* 0x1C */ f32 field_0x1C;
            /* 0x20 */ f32 mTiltChaseWait;
            /* 0x24 */ f32 mTiltChaseRot;
            /* 0x28 */ f32 mPosMoveDamp;
            /* 0x2C */ s16 mWavePhaseYStep;
            /* 0x2E */ s16 mWavePhaseZStep;
            /* 0x30 */ f32 mTiltSinScale;
            /* 0x34 */ f32 field_0x34;
            /* 0x38 */ s16 field_0x38;
            /* 0x3A */ s16 field_0x3A;
            /* 0x3C */ s16 mRotTimerMax;
            /* 0x3E */ s16 field_0x3E;
        };

        static const Attr_c L_attr = {
            /* mWaveHeight     */ 500.0f,
            /* mWaveSpeed      */ 0.04f,
            /* mWavePhase      */ 0.01f,
            /* mWaveAmplitude  */ 0.02f,
            /* mRideYOff       */ -20.0f,
            /* mWavePhaseXStep  */ 400,
            /* field_0x16      */ 0,
            /* mWaveSinScale   */ 0.3f,
            /* field_0x1C      */ 0.12f,
            /* mTiltChaseWait  */ 0.8f,
            /* mTiltChaseRot   */ 0.5f,
            /* mPosMoveDamp    */ 0.07f,
            /* mWavePhaseYStep */ 1000,
            /* mWavePhaseZStep */ 1111,
            /* mTiltSinScale    */ 0.01f,
            /* field_0x34      */ 0.5f,
            /* field_0x38      */ 30,
            /* field_0x3A      */ 30,
            /* mRotTimerMax    */ 10,
            /* field_0x3E      */ 0,
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
#if VERSION == VERSION_DEMO
    fopAcM_setCullSizeBox(actor, -550.0f, -180.0f, -550.0f, 550.0f, 605.0f, 550.0f);
#else
    f32 cullMinX = -550.0f;
    f32 cullMinY = -180.0f;
    f32 cullMaxX = 550.0f;
    f32 cullMaxY = 605.0f;
    fopAcM_setCullSizeBox(actor, cullMinX, cullMinY, cullMinX, cullMaxX, cullMaxY, cullMaxX);
#endif
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

    mRideYOff = 0.0f;
    mTiltTargetZ = 0.0f;
    mTiltTargetX = 0.0f;
    mTiltVelZ = 0.0f;
    mTiltVelX = 0.0f;
    mTiltZ = 0.0f;
    mTiltX = 0.0f;

    mWavePhaseX = cM_rndFX(32768.0f);
    mWavePhaseY = cM_rndFX(32768.0f);
    mWavePhaseZ = cM_rndFX(32768.0f);
    mRideFlag = FALSE;

    mTargetAngleY = 0;
    mAngleChaseY = 0;

    mHitDir.set((cXyz&)cXyz::Zero);
    field_0x4B0.set(5.0f, 5.0f, 5.0f);
    mPrevPos.set(current.pos);
    f32 prevY = mPrevPos.y;
    field_0x4C8 = prevY;
    field_0x4CC = prevY;

    // f32 endZero = 0.0f;
    field_0x4D0 = 0.0f;
    field_0x4D4 = 0.0f;

    return TRUE;
}

/* 00000370-0000050C       .text Mthd_Create__Q210daObjDrift5Act_cFv */
cPhs_State daObjDrift::Act_c::Mthd_Create() {
    fopAcM_ct(this, Act_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhase, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        mType = prm_get_type();

        phase_state = MoveBGCreate(
            M_arcname,
            dRes_INDEX_KRYU_DZB_RYU_00_e,
            dBgS_MoveBGProc_TypicalRotY,
            DEMO_SELECT(0x8000, 0x1B80)
        );
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
#if VERSION == VERSION_DEMO
        static const s16 pf_name[2] = {0xD7, 0xD8};
#else
        static const s16 pf_name[2] = {0xD6, 0xD7};
#endif
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
    static cXyz offset_vec(-489.35f, 600.0f, 0.0f);

    PSMTXMultVec(mMtx, &offset_vec, i_pos);
    mDoMtx_MtxToRot(mMtx, i_angle);
}

/* 00000890-00000954       .text set_flower_current__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_flower_current() {
    if (mFlowerPid == fpcM_ERROR_PROCESS_ID_e) {
        return;
    }

    fopAc_ac_c* flower = fopAcM_SearchByID(mFlowerPid);
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
    s32 ret = MoveBGDelete();
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
        if (fopAcM_searchPlayerDistanceXZ2(this) > 302500.0f) {
            cXyz* l_tgrVec = mCyl.GetTgRVecP();
            mHitDir.set(*l_tgrVec);
            mHitDir.normalizeZP();
            mode_rot_init();
        }
    } else {
        mCyl.MoveCAtTg(*&current.pos);
        dComIfG_Ccsp()->Set(&mCyl);
    }
}

/* 00000A80-00000B38       .text mode_rot_init__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_rot_init() {
    fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
    mTargetAngleY = shape_angle.y + 0x8000;
    mAngleChaseY = 0;
    shape_angle.y += 10;
    mRotTimer = 0.0f;
    mMode = MODE_ROT;
#if VERSION == VERSION_DEMO
    s8 roomNo = current.roomNo;
    s8 reverb = dComIfGp_getReverb(roomNo);
#else
    s8 reverb = dComIfGp_getReverb(current.roomNo);
#endif
    JAIZelBasic::zel_basic->seStart(
        JA_SE_OBJ_RYUBOKU_MOVE,
        &eyePos,
        0,
        reverb,
        1.0f,
        1.0f,
        -1.0f,
        -1.0f,
        0
    );
}

/* 00000B38-00000C3C       .text mode_rot__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::mode_rot() {
    s16 yDiff = mTargetAngleY - shape_angle.y;
    if (yDiff <= 0) {
        shape_angle.y = mTargetAngleY;
        mHitDir.set(cXyz::Zero);
        mode_wait_init();
    } else {
        if (yDiff < 0x2000) {
            cLib_chaseS(&mAngleChaseY, 0x14, 0xA);
        } else {
            cLib_chaseS(&mAngleChaseY, 0x190, 0x14);
        }
        shape_angle.y += mAngleChaseY;
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
    mDoMtx_stack_c::transS(current.pos);
#if VERSION == VERSION_DEMO
    Quaternion quat;
    cXyz axis(mTiltX, 1.0f, mTiltZ);
#else
    f32 axisZ = mTiltZ;
    f32 axisY = 1.0f;
    f32 axisX = mTiltX;
    Quaternion quat;
    cXyz axis(axisX, axisY, axisZ);
#endif
    daObj::quat_rotBaseY2(&quat, axis);
    mDoMtx_stack_c::quatM(&quat);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), mMtx);
    field_0x4CC = field_0x4C8;
    field_0x4C8 = mPrevPos.y;
    mPrevPos.x = mDoMtx_stack_c::get()[0][3];
    mPrevPos.y = mDoMtx_stack_c::get()[1][3];
    mPrevPos.z = mDoMtx_stack_c::get()[2][3];
}

/* 00000D18-00000D54       .text init_mtx__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::init_mtx() {
    mModel->setBaseScale(scale);
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
    drift->mRideYOff = L_attr.mRideYOff;
    
    cXyz delta;
    cXyz localDelta;
    Mtx invMtx;
    delta = player->current.pos - drift->current.pos;
    if (PSMTXInverse(drift->mMtx, invMtx) &&
        !dComIfGp_checkPlayerStatus0(0, daPyStts0_HANG_e)) {
        PSMTXMultVecSR(invMtx, &delta, &localDelta);
        f32 sqMag = localDelta.abs2XZ();
        if (localDelta.y < 400.0f) {
            if (sqMag < 129600.0f) {
                drift->mRideFlag = TRUE;
            }
        } else if (localDelta.y < 550.0f) {
            if (sqMag < 48400.0f) {
                drift->mRideFlag = TRUE;
            }
        }
    } else {
        drift->mRideFlag = TRUE;
    }
    if (drift->mRideFlag == FALSE) {
        drift->mTiltTargetZ = delta.z * (ratio * L_attr.field_0x1C);
        drift->mTiltTargetX = delta.x * (ratio * L_attr.field_0x1C);
    }
}

/* 00000EC4-00001104       .text set_current__Q210daObjDrift5Act_cFv */
void daObjDrift::Act_c::set_current() {
    f32 y = mRideYOff + home.pos.y;
    mWavePhaseX += L_attr.mWavePhaseXStep;
#if VERSION == VERSION_DEMO
    f32 sinVal = JMASSin(mWavePhaseX);
    f32 yDelta = y - current.pos.y;
#else
    f32 yDelta = y - current.pos.y;
    f32 sinVal = JMASSin(mWavePhaseX);
#endif
    gravity = yDelta * L_attr.mWaveAmplitude
            + sinVal * L_attr.mWaveSinScale;
    daObj::posMoveF_stream(this, NULL, &cXyz::Zero, L_attr.mWaveSpeed, L_attr.mWavePhase);
#if VERSION == VERSION_DEMO
    f32 rotFactor;
    f32 chaseFactor;
#else
    f32 chaseFactor;
    f32 rotFactor;
#endif
    if (mRideFlag != 0) {
        rotFactor = 0.2f;
    } else {
        rotFactor = 1.0f;
    }
    if (mMode == MODE_ROT) {
        chaseFactor = L_attr.mTiltChaseRot;
    } else {
        chaseFactor = L_attr.mTiltChaseWait;
    }
#if VERSION == VERSION_DEMO
    PSVECScale(&mHitDir, &mHitDir, 0.95f);
    mWavePhaseY += L_attr.mWavePhaseYStep;
    mWavePhaseZ += L_attr.mWavePhaseZStep;
    f32 diffZ = mTiltZ - mTiltTargetZ;
    f32 diffX = mTiltX - mTiltTargetX;
    f32 sinY = JMASSin(mWavePhaseY);
    f32 z_val = mHitDir.z * L_attr.field_0x34
            + (rotFactor * (sinY * L_attr.mTiltSinScale)
            - diffZ * chaseFactor);
    f32 sinZ = JMASSin(mWavePhaseZ);
    f32 x_val = mHitDir.x * L_attr.field_0x34
        + (rotFactor * (sinZ * L_attr.mTiltSinScale)
        - diffX * chaseFactor);
    mTiltVelZ += z_val;
    mTiltVelX += x_val;
#else
    PSVECScale(&mHitDir, &mHitDir, 0.95f);
    mWavePhaseY += L_attr.mWavePhaseYStep;
    mWavePhaseZ += L_attr.mWavePhaseZStep;
    f32 sinY = JMASSin(mWavePhaseY);
    f32 sinZ = JMASSin(mWavePhaseZ);
    f32 diffZ = mTiltZ - mTiltTargetZ;
    f32 diffX = mTiltX - mTiltTargetX;
    f32 x_val = mHitDir.x * L_attr.field_0x34
        + (rotFactor * (sinZ * L_attr.mTiltSinScale)
        - diffX * chaseFactor);
    mTiltVelZ += mHitDir.z * L_attr.field_0x34
            + (rotFactor * (sinY * L_attr.mTiltSinScale)
            - diffZ * chaseFactor);
    mTiltVelX += x_val;
#endif
    mTiltVelZ *= L_attr.mPosMoveDamp;
    mTiltVelX *= L_attr.mPosMoveDamp;
    mTiltZ += mTiltVelZ;
    mTiltX += mTiltVelX;
    mRideYOff = 0.0f;
    mTiltTargetZ = 0.0f;
    mTiltTargetX = 0.0f;
    mRideFlag = FALSE;
}

/* 00001104-000011D0       .text Execute__Q210daObjDrift5Act_cFPPA3_A4_f */
BOOL daObjDrift::Act_c::Execute(Mtx** mtx) {
    typedef void (daObjDrift::Act_c::*procFunc)();
    static procFunc mode_proc[] = {
        &daObjDrift::Act_c::mode_wait,
        &daObjDrift::Act_c::mode_rot,
    };
    (this->*mode_proc[mMode])();

    set_current();
    set_mtx();
    *mtx = &mMtx;
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
    return ((daObjDrift::Act_c*)i_this)->MoveBGDraw();
}

/* 000012FC-00001328       .text Mthd_IsDelete__Q210daObjDrift27@unnamed@d_a_obj_drift_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjDrift::Act_c*)i_this)->MoveBGIsDelete();
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
