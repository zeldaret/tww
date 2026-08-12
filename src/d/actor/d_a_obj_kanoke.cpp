/**
 * d_a_obj_kanoke.cpp
 * Object - Earth Temple - Coffin
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_kanoke.h"
#include "assets/GZLE01/res/Object/Mkanoke.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_particle_name.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_mtx.h"

static dCcD_SrcCps l_cps_src_body = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 50.0f, -100.0f},
        /* End    */ {0.0f, 50.0f, 100.0f},
        /* Radius */ 100.0f,
    }},
};


static dCcD_SrcCps l_cps_src_huta = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
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
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 50.0f, -100.0f},
        /* End    */ {0.0f, 50.0f, 100.0f},
        /* Radius */ 25.0f,
    }},
};

static cXyz daObjKanoke_Yoko_pfs = cXyz(100.0f, 0.0f, 0.0f);
static cXyz daObjKanoke_Tate_pfs[][2] = {
    {cXyz(50.0f, 0.0f, -175.0f), cXyz(50.0f, 0.0f, 175.0f)},
    {cXyz(0.0f, 0.0f, -175.0f), cXyz(0.0f, 0.0f, 175.0f)},
    {cXyz(-50.0f, 0.0f, -175.0f), cXyz(-50.0f, 0.0f, 175.0f)},
};

static daObjKanoke_c::MoveProc moveProc[] = {
    &daObjKanoke_c::executeNormal,
    &daObjKanoke_c::executeYureYoko,
    &daObjKanoke_c::executeOpenYoko,
    &daObjKanoke_c::executeEffectYoko,
    &daObjKanoke_c::executeYureTate,
    &daObjKanoke_c::executeOpenTate,
    &daObjKanoke_c::executeEffectTate,
    &daObjKanoke_c::executeWait,
};

/* 000000EC-000002F4       .text __ct__13daObjKanoke_cFv */
daObjKanoke_c::daObjKanoke_c() {
    mType = getPrmType();
    mSearchRange = getPrmSearch();
    mSwitchNo = getPrmSwNo();
    mSwitchNo2 = getPrmSwNo2();

    if (mType == 0) {
        mLidOffset.set(0.0f, 0.0f, 0.0f);
    } else {
        current.pos.y = home.pos.y + 200.0f;
        shape_angle.x = 0x4000;
        mLidOffset.set(0.0f, 35.0f, 200.0f);
    }
    mPivotOffset.set(0.0f, 75.0f, 0.0f);
    mLidRotX = 0;
    mBodyRotY = 0;
    mLidRotZ = 0;
    mRotStep = 0;
    for (int i = 0; i < 2; i++) {
        mpEmitters[i] = NULL;
    }
    mSmokeCallback.setRateOff(0);
    mState = 0;
    mFlags = 0;
    mLightTimer = 0;
    setMtxHontai();
    mDoMtx_copy(mDoMtx_stack_c::get(), mBodyMtx);
    setMtxHuta(&current.pos);
    mDoMtx_copy(mDoMtx_stack_c::get(), mLidMtx);
}

/* 00000644-00000664       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_actor) {
    return ((daObjKanoke_c*)i_actor)->createHeap();
}

/* 00000664-00000700       .text _create__13daObjKanoke_cFv */
cPhs_State daObjKanoke_c::_create() {
    fopAcM_ct(this, daObjKanoke_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, "Mkanoke");
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x2400)) {
            phase_state = createInit();
        } else {
#if VERSION > VERSION_DEMO
            mpLidBgW = NULL;
            mpBodyBgW = NULL;
#endif
            phase_state = cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 00000700-000008BC       .text createHeap__13daObjKanoke_cFv */
BOOL daObjKanoke_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(
        "Mkanoke", dRes_INDEX_MKANOKE_BDL_MOKE1_e);
    if (modelData == NULL) {
        return FALSE;
    }
    mpBodyModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpBodyModel == NULL) {
        return FALSE;
    }

    mpBodyBgW = new dBgW();
    if (mpBodyBgW == NULL) {
        return FALSE;
    }
    cBgD_t* bodyDzb = (cBgD_t*)dComIfG_getObjectRes(
        "Mkanoke", dRes_INDEX_MKANOKE_DZB_MOKE1_e);
    if (mpBodyBgW->Set(bodyDzb, dBgW::MOVE_BG_e, &mBodyMtx) == true) {
        return FALSE;
    }

    modelData = (J3DModelData*)dComIfG_getObjectRes(
        "Mkanoke", dRes_INDEX_MKANOKE_BDL_MOKE2_e);
    if (modelData == NULL) {
        return FALSE;
    }
    mpLidModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpLidModel == NULL) {
        return FALSE;
    }

    mpLidBgW = new dBgW();
    if (mpLidBgW == NULL) {
        return FALSE;
    }
    cBgD_t* lidDzb = (cBgD_t*)dComIfG_getObjectRes(
        "Mkanoke", dRes_INDEX_MKANOKE_DZB_MOKE2_e);
    BOOL result = mpLidBgW->Set(lidDzb, dBgW::MOVE_BG_e, &mLidMtx);
    if (result == TRUE) {
        return FALSE;
    }
    return TRUE;
}

/* 000008BC-00000B28       .text createInit__13daObjKanoke_cFv */
cPhs_State daObjKanoke_c::createInit() {
    if (dComIfG_Bgsp()->Regist(mpBodyBgW, this)) {
        return cPhs_ERROR_e;
    }

    if (mSwitchNo != 0xFF) {
        if (dComIfGs_isSwitch(mSwitchNo, fopAcM_GetHomeRoomNo(this))) {
            mState = 7;
            if (mType == 0) {
                if (dComIfG_Bgsp()->Regist(mpLidBgW, this)) {
                    return cPhs_ERROR_e;
                }
                mPivotOffset.set(148.0f, 75.0f, 0.0f);
                mLidOffset.set(-48.0f, 0.0f, 0.0f);
                mLidRotZ = -0x15E0;
            } else {
                mFlags |= 2;
            }
        } else if (dComIfG_Bgsp()->Regist(mpLidBgW, this)) {
            return cPhs_ERROR_e;
        }
    } else if (dComIfG_Bgsp()->Regist(mpLidBgW, this)) {
        return cPhs_ERROR_e;
    }

    mStts.Init(0xFF, 0xFF, this);
    mBodyCps.Set(l_cps_src_body);
    mBodyCps.SetStts(&mStts);
    mBodyCps.SetStartEnd(current.pos, current.pos);
    for (int i = 0; i < 3; i++) {
        mLidCps[i].Set(l_cps_src_huta);
        mLidCps[i].SetStts(&mStts);
        mLidCps[i].SetStartEnd(current.pos, current.pos);
    }

    fopAcM_SetMtx(this, mpBodyModel->getBaseTRMtx());
    setMtx();
    if (mType == 0) {
        fopAcM_setCullSizeBox(this, -110.0f, 0.0f, -210.0f, 310.0f, 120.0f, 210.0f);
    } else {
        fopAcM_setCullSizeBox(this, -110.0f, 0.0f, -210.0f, 110.0f, 520.0f, 210.0f);
    }
    return cPhs_COMPLEATE_e;
}

/* 00000B28-00000C0C       .text _delete__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_delete() {
#if VERSION > VERSION_DEMO
    if (heap != NULL) {
        if (mpBodyBgW != NULL && mpBodyBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBodyBgW);
        }
        if (mpLidBgW != NULL && mpLidBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpLidBgW);
        }
    }
#else
    if (mpBodyBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBodyBgW);
    }
    if (mpLidBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpLidBgW);
    }
    for (int i = 0; i < 2; i++) {
        // The demo build retains an empty emitter loop.
    }
#endif
    mSmokeCallback.remove();
    dComIfG_resDeleteDemo(&mPhs, "Mkanoke");
    return TRUE;
}

/* 00000C0C-00000CE0       .text _draw__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpBodyModel, &tevStr);
    g_env_light.setLightTevColorType(mpLidModel, &tevStr);
    dComIfGd_setListBG();
    if (!(mFlags & 1)) {
        mDoExt_modelUpdateDL(mpBodyModel);
    }
    if (!(mFlags & 2)) {
        mDoExt_modelUpdateDL(mpLidModel);
    }
    dComIfGd_setList();
    return TRUE;
}

/* 00000CE0-00000E7C       .text _execute__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_execute() {
    cXyz bodyStart(0.0f, 0.0f, -100.0f);
    cXyz bodyEnd(0.0f, 0.0f, 100.0f);
    mDoMtx_stack_c::YrotS(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::multVec(&bodyStart, &bodyStart);
    mDoMtx_stack_c::multVec(&bodyEnd, &bodyEnd);
    bodyStart += current.pos;
    bodyEnd += current.pos;
    mBodyCps.SetStartEnd(bodyStart, bodyEnd);
    mBodyCps.SetR(140.0f);
    dComIfG_Ccsp()->Set(&mBodyCps);

    (this->*moveProc[mState])();
    setMtx();
    if (mpBodyBgW->ChkUsed()) {
        mpBodyBgW->Move();
    }
    if (mpLidBgW->ChkUsed()) {
        mpLidBgW->Move();
    }
    return TRUE;
}

/* 00000E7C-0000122C       .text executeNormal__13daObjKanoke_cFv */
void daObjKanoke_c::executeNormal() {
    bool open = false;
    if (mSwitchNo != 0xFF && dComIfGs_isSwitch(mSwitchNo, fopAcM_GetHomeRoomNo(this))) {
        open = true;
    } else if (dComIfGp_getDetect().chk_light(&current.pos) || mBodyCps.ChkTgHit()) {
        mLightTimer++;
        if (mLightTimer > 20) {
            mBodyCps.SetTgType(0);
            open = true;
        }
    } else {
        mLightTimer = 0;
        if (mSearchRange != 0) {
            fopAc_ac_c* player = dComIfGp_getPlayer(0);
            cXyz delta = home.pos - player->current.pos;
            if (delta.abs() < 100.0f * mSearchRange) {
                open = true;
            }
        }
    }

    if (open) {
        mBodyCps.ClrTgHit();
        if (mSwitchNo != 0xFF) {
            dComIfGs_onSwitch(mSwitchNo, fopAcM_GetHomeRoomNo(this));
        }
        mRotStep = 0;
        if (getPrmYure()) {
            mTimer = 0;
            if (mType == 0) {
                mDoAud_seStart(JA_SE_OBJ_KANOKE_Y_GATA, &current.pos, 0,
                               dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                mState = 1;
                mLidRotZ = 0;
                mMoveSpeed = 0x100;
            } else {
                mDoAud_seStart(JA_SE_OBJ_KANOKE_T_GATA, &current.pos, 0,
                               dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                mState = 4;
                mBodyRotY = 0;
                mMoveSpeed = 0x400;
            }
        } else if (mType == 0) {
            mDoAud_seStart(JA_SE_OBJ_KANOKE_Y_OPEN, &current.pos, 0,
                           dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            mState = 2;
            mLidRotZ = 0;
        } else {
            mDoAud_seStart(JA_SE_OBJ_KANOKE_T_OPEN, &current.pos, 0,
                           dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            mState = 5;
            if (mpLidBgW->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpLidBgW);
            }
            mLidRotX = 0;
        }
    }
}

/* 0000122C-00001358       .text executeYureYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeYureYoko() {
    mTimer += 0x2000;
    mMoveSpeed -= 8;
    mLidRotZ = mMoveSpeed * cM_ssin(mTimer);
    if (mLidRotZ < 0) {
        mLidOffset.x = 100.0f;
    } else {
        mLidOffset.x = -100.0f;
    }
    if (mMoveSpeed <= 0) {
        mDoAud_seStart(JA_SE_OBJ_KANOKE_Y_OPEN, &current.pos, 0,
                       dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        mState = 2;
        mLidRotZ = 0;
        mLidOffset.x = 0.0f;
    }
}

/* 00001358-00001544       .text executeOpenYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeOpenYoko() {
#if VERSION == VERSION_DEMO
    f32 maxOffset = 100.0f;
    s16 maxRotation = -0x15E0;
#endif
    mPivotOffset.x += 4.0f;
#if VERSION == VERSION_DEMO
    mLidOffset.x = maxOffset - mPivotOffset.x;
    if (mPivotOffset.x > maxOffset) {
#else
    mLidOffset.x = 100.0f - mPivotOffset.x;
    if (mPivotOffset.x > 100.0f) {
#endif
        mLidRotZ += mRotStep;
        mRotStep -= 100;
#if VERSION == VERSION_DEMO
        if (mLidRotZ <= maxRotation) {
            mLidRotZ = maxRotation;
#else
        if (mLidRotZ <= -0x15E0) {
            mLidRotZ = -0x15E0;
#endif
            mState = 3;

            mDoMtx_stack_c::YrotS(shape_angle.y);
            mDoMtx_stack_c::transM(100.0f, 75.0f, 0.0f);
            mDoMtx_stack_c::ZrotM(mLidRotZ);
            mDoMtx_stack_c::transM(-100.0f, -75.0f, 0.0f);
            Mtx mtx;
            mDoMtx_copy(mDoMtx_stack_c::get(), mtx);

            mEffectAngle.set(0, shape_angle.y, 0);
            mEffectScale = 180.0f;
            cXyz effectPos = mPivotOffset + daObjKanoke_Yoko_pfs;
            mDoMtx_multVec(mtx, &effectPos, &effectPos);
            mEffectPos = effectPos + current.pos;
#if VERSION > VERSION_DEMO
            if (mSmokeCallback.getEmitter() == NULL)
#endif
            {
                dComIfGp_particle_setToon(dPa_name::ID_IT_ST_KANOKE_SMOKE01, &mEffectPos,
                                           &mEffectAngle, NULL, (u8)mEffectScale,
                                           &mSmokeCallback);
            }
            if (mSmokeCallback.getEmitter() != NULL) {
                mSmokeCallback.getEmitter()->becomeImmortalEmitter();
            }
            mTimer = 60;
        }
    }
}

/* 00001544-000015F8       .text executeEffectYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeEffectYoko() {
    mTimer--;
    if (mTimer != 0) {
        if (mTimer <= 50) {
            mEffectScale -= 3.6f;
            if (mEffectScale < 0.0f) {
                mEffectScale = 0.0f;
            }
            if (mSmokeCallback.getEmitter() != NULL) {
                mSmokeCallback.getEmitter()->setGlobalAlpha((u8)mEffectScale);
            }
        }
    } else {
        mSmokeCallback.remove();
        mState = 7;
    }
}

/* 000015F8-00001764       .text executeYureTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeYureTate() {
    mTimer += 0x2000;
    mMoveSpeed -= 0x20;
    mBodyRotY = mMoveSpeed * cM_ssin(mTimer);
    if (mBodyRotY < 0) {
        mLidOffset.x = 100.0f;
    } else {
        mLidOffset.x = -100.0f;
    }
    if (mMoveSpeed <= 0) {
        mDoAud_seStart(JA_SE_OBJ_KANOKE_T_OPEN, &current.pos, 0,
                       dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        mState = 5;
        if (mpLidBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpLidBgW);
        }
        mLidRotX = 0;
        mBodyRotY = 0;
        mLidOffset.x = 0.0f;
    }
}

/* 00001764-00001A6C       .text executeOpenTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeOpenTate() {
    mLidRotX += mRotStep;
    mRotStep += 100;
    if (mLidRotX >= 0x4000) {
        dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        mLidRotX = 0x4000;
        mState = 6;
        mFlags |= 2;
        mEffectPos.x = mLidMtx[0][3];
        mEffectPos.y = mLidMtx[1][3];
        mEffectPos.z = mLidMtx[2][3];
        mEffectAngle.set(0, shape_angle.y, 0);
        mpEmitters[0] = dComIfGp_particle_set(
            dPa_name::ID_IT_SN_KANOKE_ROCK00, &mEffectPos, &mEffectAngle, NULL, 0xFF, NULL,
            -1, &tevStr.mColorK0, &tevStr.mColorK0);
        mEffectScale = 180.0f;
#if VERSION > VERSION_DEMO
        if (mSmokeCallback.getEmitter() == NULL)
#endif
        {
            dComIfGp_particle_setToon(dPa_name::ID_IT_ST_KANOKE_SMOKE00, &mEffectPos,
                                       &mEffectAngle, NULL, (u8)mEffectScale,
                                       &mSmokeCallback);
        }
        if (mSmokeCallback.getEmitter() != NULL) {
            mSmokeCallback.getEmitter()->becomeImmortalEmitter();
        }
        mTimer = 60;
    } else {
        mDoMtx_stack_c::YrotS(shape_angle.y);
        mDoMtx_stack_c::XrotM(shape_angle.x);
        mDoMtx_stack_c::transM(0.0f, 110.0f, 200.0f);
        mDoMtx_stack_c::XrotM(mLidRotX);
        mDoMtx_stack_c::transM(0.0f, -110.0f, -200.0f);
        for (int i = 0; i < 3; i++) {
            cXyz start = daObjKanoke_Tate_pfs[i][0] + mPivotOffset;
            cXyz end = daObjKanoke_Tate_pfs[i][1] + mPivotOffset;
            mDoMtx_stack_c::multVec(&start, &start);
            mDoMtx_stack_c::multVec(&end, &end);
            start += current.pos;
            end += current.pos;
            mLidCps[i].SetStartEnd(start, end);
            dComIfG_Ccsp()->Set(&mLidCps[i]);
        }
    }
}

/* 00001A6C-00001B24       .text executeEffectTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeEffectTate() {
    mTimer--;
    if (mTimer != 0) {
        if (mSmokeCallback.getEmitter() != NULL && mTimer <= 50) {
            mEffectScale -= 3.6f;
            if (mEffectScale < 0.0f) {
                mEffectScale = 0.0f;
            }
            mSmokeCallback.getEmitter()->setGlobalAlpha((u8)mEffectScale);
        }
    } else {
        mSmokeCallback.remove();
        mState = 7;
    }
}

/* 00001B24-00001B28       .text executeWait__13daObjKanoke_cFv */
void daObjKanoke_c::executeWait() {
}

/* 00001B28-00001B54       .text getPrmType__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmType() {
    return daObj::PrmAbstract<Prm_e>(this, PRM_TYPE_W, PRM_TYPE_S);
}

/* 00001B54-00001B80       .text getPrmSearch__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSearch() {
    return daObj::PrmAbstract<Prm_e>(this, PRM_SEARCH_W, PRM_SEARCH_S);
}

/* 00001B80-00001BAC       .text getPrmYure__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmYure() {
    return daObj::PrmAbstract<Prm_e>(this, PRM_YURE_W, PRM_YURE_S);
}

/* 00001BAC-00001BD8       .text getPrmSwNo__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSwNo() {
    return daObj::PrmAbstract<Prm_e>(this, PRM_SWNO_W, PRM_SWNO_S);
}

/* 00001BD8-00001C04       .text getPrmSwNo2__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSwNo2() {
    return daObj::PrmAbstract<Prm_e>(this, PRM_SWNO2_W, PRM_SWNO2_S);
}

/* 00001C04-00001C9C       .text setMtx__13daObjKanoke_cFv */
void daObjKanoke_c::setMtx() {
    if (!(mFlags & 1)) {
        setMtxHontai();
        mpBodyModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mDoMtx_copy(mDoMtx_stack_c::get(), mBodyMtx);
    }
    if (!(mFlags & 2)) {
        setMtxHuta(&current.pos);
        mpLidModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mDoMtx_copy(mDoMtx_stack_c::get(), mLidMtx);
    }
}

/* 00001C9C-00001D38       .text setMtxHontai__13daObjKanoke_cFv */
void daObjKanoke_c::setMtxHontai() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::transM(mLidOffset);
    mDoMtx_stack_c::YrotM(mBodyRotY);
    mDoMtx_stack_c::transM(-mLidOffset.x, -mLidOffset.y, -mLidOffset.z);
}

/* 00001D38-00001E4C       .text setMtxHuta__13daObjKanoke_cFP4cXyz */
void daObjKanoke_c::setMtxHuta(cXyz* i_pos) {
    cXyz pivot;
    mDoMtx_stack_c::YrotS(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::multVec(&mPivotOffset, &pivot);
    mDoMtx_stack_c::transS(i_pos->x + pivot.x, i_pos->y + pivot.y, i_pos->z + pivot.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::transM(mLidOffset);
    mDoMtx_stack_c::XrotM(mLidRotX);
    mDoMtx_stack_c::YrotM(mBodyRotY);
    mDoMtx_stack_c::ZrotM(mLidRotZ);
    mDoMtx_stack_c::transM(-mLidOffset.x, -mLidOffset.y, -mLidOffset.z);
}

/* 00001E4C-00001E6C       .text daObjKanokeCreate__FPv */
static cPhs_State daObjKanokeCreate(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_create();
}

/* 00001E6C-00001E8C       .text daObjKanokeDelete__FPv */
static BOOL daObjKanokeDelete(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_delete();
}

/* 00001E8C-00001EAC       .text daObjKanokeExecute__FPv */
static BOOL daObjKanokeExecute(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_execute();
}

/* 00001EAC-00001ECC       .text daObjKanokeDraw__FPv */
static BOOL daObjKanokeDraw(void* i_this) {
    return ((daObjKanoke_c*)i_this)->_draw();
}

/* 00001ECC-00001ED4       .text daObjKanokeIsDelete__FPv */
static BOOL daObjKanokeIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObjKanokeMethodTable = {
    (process_method_func)daObjKanokeCreate,
    (process_method_func)daObjKanokeDelete,
    (process_method_func)daObjKanokeExecute,
    (process_method_func)daObjKanokeIsDelete,
    (process_method_func)daObjKanokeDraw,
};

actor_process_profile_definition g_profile_Obj_Kanoke = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Kanoke_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjKanoke_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Kanoke_e,
    /* Actor SubMtd */ &daObjKanokeMethodTable,
    /* Status       */ 0x04 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
