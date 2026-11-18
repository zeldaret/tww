/**
 * d_a_obj_kanoke.cpp
 * Object - Earth Temple - Coffin
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_kanoke.h"
#include "d/d_cc_d.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_ext.h"
#include "JSystem/JParticle/JPAEmitter.h"


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

static cXyz daObjKanoke_Yoko_pfs[] = {
    cXyz(100.0f, 0.0f, 0.0f),
};

static cXyz daObjKanoke_Tate_pfs[3][2] = {
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
    mSearch = getPrmSearch();
    mSwNo = getPrmSwNo();
    mSwNo2 = getPrmSwNo2();
    if (mType == 0) {
        mPivot.x = 0.0f;
        mPivot.y = 0.0f;
        mPivot.z = 0.0f;
    } else {
        current.pos.y = 200.0f + home.pos.y;
        shape_angle.x = 0x4000;
        mPivot.x = 0.0f;
        mPivot.y = 35.0f;
        mPivot.z = 200.0f;
    }
    mHutaOffset.x = 0.0f;
    mHutaOffset.y = 75.0f;
    mHutaOffset.z = 0.0f;
    mAngleX = 0;
    mAngleY = 0;
    mAngleZ = 0;
    mSpeed = 0;
    for (int i = 0; i < 2; i++) {
        mpEmitter[i] = NULL;
    }
    mSmoke.setRateOff(0);
    mMode = 0;
    mHideFlag = 0;
    mLightCount = 0;
    setMtxHontai();
    cMtx_copy(mDoMtx_stack_c::get(), mMtxBody);
    setMtxHuta(&current.pos);
    cMtx_copy(mDoMtx_stack_c::get(), mMtxHuta);
}

/* 00000644-00000664       .text CheckCreateHeap__FP10fopAc_ac_c */
static bool CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daObjKanoke_c*)i_this)->createHeap();
}

/* 00000664-00000700       .text _create__13daObjKanoke_cFv */
cPhs_State daObjKanoke_c::_create() {
    fopAcM_ct(this, daObjKanoke_c);
    cPhs_State ret = dComIfG_resLoad(&mPhase, "Mkanoke");
    if (ret == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, (heapCallbackFunc)CheckCreateHeap, 0x2400)) {
            return createInit();
        }
        mpBgWHuta = NULL;
        mpBgWBody = NULL;
        ret = cPhs_ERROR_e;
    }
    return ret;
}

/* 00000700-000008BC       .text createHeap__13daObjKanoke_cFv */
bool daObjKanoke_c::createHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Mkanoke", 4);
    if (modelData == NULL) {
        return false;
    }
    mpModelBody = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpModelBody == NULL) {
        return false;
    }
    mpBgWBody = new dBgW();
    if (mpBgWBody == NULL) {
        return false;
    }
    if (mpBgWBody->Set((cBgD_t*)dComIfG_getObjectRes("Mkanoke", 8), cBgW::MOVE_BG_e, &mMtxBody) == true) {
        return false;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Mkanoke", 5);
    if (modelData == NULL) {
        return false;
    }
    mpModelHuta = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpModelHuta == NULL) {
        return false;
    }
    mpBgWHuta = new dBgW();
    if (mpBgWHuta == NULL) {
        return false;
    }
    return mpBgWHuta->Set((cBgD_t*)dComIfG_getObjectRes("Mkanoke", 9), cBgW::MOVE_BG_e, &mMtxHuta) != true;
}

/* 000008BC-00000B28       .text createInit__13daObjKanoke_cFv */
cPhs_State daObjKanoke_c::createInit() {
    if (dComIfG_Bgsp()->Regist(mpBgWBody, this)) {
        return cPhs_ERROR_e;
    }
    if (mSwNo != 0xFF) {
        if (fopAcM_isSwitch(this, mSwNo)) {
            mMode = 7;
            if (mType == 0) {
                if (dComIfG_Bgsp()->Regist(mpBgWHuta, this)) {
                    return cPhs_ERROR_e;
                }
                mHutaOffset.x = 148.0f;
                mHutaOffset.y = 75.0f;
                mHutaOffset.z = 0.0f;
                mPivot.x = -48.0f;
                mPivot.y = 0.0f;
                mPivot.z = 0.0f;
                mAngleZ = -0x15E0;
            } else {
                mHideFlag |= 2;
            }
        } else if (dComIfG_Bgsp()->Regist(mpBgWHuta, this)) {
            return cPhs_ERROR_e;
        }
    } else if (dComIfG_Bgsp()->Regist(mpBgWHuta, this)) {
        return cPhs_ERROR_e;
    }
    mStts.Init(0xFF, 0xFF, this);
    mCpsBody.Set(l_cps_src_body);
    mCpsBody.SetStts(&mStts);
    mCpsBody.SetStartEnd(current.pos, current.pos);
    for (int i = 0; i < 3; i++) {
        mCpsHuta[i].Set(l_cps_src_huta);
        mCpsHuta[i].SetStts(&mStts);
        mCpsHuta[i].SetStartEnd(current.pos, current.pos);
    }
    fopAcM_SetMtx(this, mpModelBody->getBaseTRMtx());
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
    if (heap != NULL) {
        if (mpBgWBody != NULL && mpBgWBody->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgWBody);
        }
        if (mpBgWHuta != NULL && mpBgWHuta->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgWHuta);
        }
    }
    mSmoke.remove();
    dComIfG_resDelete(&mPhase, "Mkanoke");
    return TRUE;
}

/* 00000C0C-00000CE0       .text _draw__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModelBody, &tevStr);
    g_env_light.setLightTevColorType(mpModelHuta, &tevStr);
    dComIfGd_setListBG();
    if (!(mHideFlag & 1)) {
        mDoExt_modelUpdateDL(mpModelBody);
    }
    if (!(mHideFlag & 2)) {
        mDoExt_modelUpdateDL(mpModelHuta);
    }
    dComIfGd_setList();
    return TRUE;
}

/* 00000CE0-00000E7C       .text _execute__13daObjKanoke_cFv */
BOOL daObjKanoke_c::_execute() {
    cXyz start(0.0f, 0.0f, -100.0f);
    cXyz end(0.0f, 0.0f, 100.0f);
    mDoMtx_stack_c::YrotS(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::multVec(&start, &start);
    mDoMtx_stack_c::multVec(&end, &end);
    start += current.pos;
    end += current.pos;
    mCpsBody.SetStartEnd(start, end);
    mCpsBody.SetR(140.0f);
    dComIfG_Ccsp()->Set(&mCpsBody);
    (this->*moveProc[mMode])();
    setMtx();
    if (mpBgWBody->ChkUsed()) {
        mpBgWBody->Move();
    }
    if (mpBgWHuta->ChkUsed()) {
        mpBgWHuta->Move();
    }
    return TRUE;
}

/* 00000E7C-0000122C       .text executeNormal__13daObjKanoke_cFv */
void daObjKanoke_c::executeNormal() {
    bool open = false;
    if (mSwNo != 0xFF && fopAcM_isSwitch(this, mSwNo)) {
        open = true;
    } else if (dComIfGp_getDetect().chk_light(&current.pos) || mCpsBody.ChkTgHit()) {
        mLightCount++;
        if (mLightCount > 20) {
            mCpsBody.SetTgType(0);
            open = true;
        }
    } else {
        mLightCount = 0;
        if (mSearch != 0) {
            fopAc_ac_c* player = dComIfGp_getPlayer(0);
            cXyz diff = home.pos - player->current.pos;
            if (diff.abs() < 100.0f * mSearch) {
                open = true;
            }
        }
    }
    if (open) {
        mCpsBody.ClrTgHit();
        if (mSwNo != 0xFF) {
            fopAcM_onSwitch(this, mSwNo);
        }
        mSpeed = 0;
        if (getPrmYure()) {
            mTimer = 0;
            if (mType == 0) {
                mDoAud_seStart(0x695B, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                mMode = 1;
                mAngleZ = 0;
                mAmp = 0x100;
            } else {
                mDoAud_seStart(0x6959, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                mMode = 4;
                mAngleY = 0;
                mAmp = 0x400;
            }
        } else if (mType == 0) {
            mDoAud_seStart(0x695C, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            mMode = 2;
            mAngleZ = 0;
        } else {
            mDoAud_seStart(0x695A, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            mMode = 5;
            if (mpBgWHuta->ChkUsed()) {
                dComIfG_Bgsp()->Release(mpBgWHuta);
            }
            mAngleX = 0;
        }
    }
}

/* 0000122C-00001358       .text executeYureYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeYureYoko() {
    mTimer += 0x2000;
    mAmp -= 8;
    mAngleZ = mAmp * cM_ssin(mTimer);
    if (mAngleZ < 0) {
        mPivot.x = 100.0f;
    } else {
        mPivot.x = -100.0f;
    }
    if (mAmp <= 0) {
        mDoAud_seStart(0x695C, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        mMode = 2;
        mAngleZ = 0;
        mPivot.x = 0.0f;
    }
}

/* 00001358-00001544       .text executeOpenYoko__13daObjKanoke_cFv */
void daObjKanoke_c::executeOpenYoko() {
    mHutaOffset.x += 4.0f;
    mPivot.x = 100.0f - mHutaOffset.x;
    if (mHutaOffset.x > 100.0f) {
        mAngleZ += mSpeed;
        mSpeed -= 100;
        if (mAngleZ <= -0x15E0) {
            mAngleZ = -0x15E0;
            mMode = 3;
            mDoMtx_stack_c::YrotS(shape_angle.y);
            mDoMtx_stack_c::transM(100.0f, 75.0f, 0.0f);
            mDoMtx_stack_c::ZrotM(mAngleZ);
            mDoMtx_stack_c::transM(-100.0f, -75.0f, 0.0f);
            Mtx mtx;
            cMtx_copy(mDoMtx_stack_c::get(), mtx);
            mEffAngle.set(0, shape_angle.y, 0);
            mAlpha = 180.0f;
            cXyz pos = mHutaOffset + daObjKanoke_Yoko_pfs[0];
            MTXMultVec(mtx, &pos, &pos);
            mEffPos = pos + current.pos;
            if (mSmoke.getEmitter() == NULL) {
                dComIfGp_particle_setToon(0xA181, &mEffPos, &mEffAngle, NULL, mAlpha, &mSmoke);
            }
            if (mSmoke.getEmitter() != NULL) {
                mSmoke.getEmitter()->becomeImmortalEmitter();
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
            mAlpha -= 3.6f;
            if (mAlpha < 0.0f) {
                mAlpha = 0.0f;
            }
            if (mSmoke.getEmitter() != NULL) {
                mSmoke.getEmitter()->setGlobalAlpha(mAlpha);
            }
        }
    } else {
        mSmoke.remove();
        mMode = 7;
    }
}

/* 000015F8-00001764       .text executeYureTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeYureTate() {
    mTimer += 0x2000;
    mAmp -= 0x20;
    mAngleY = mAmp * cM_ssin(mTimer);
    if (mAngleY < 0) {
        mPivot.x = 100.0f;
    } else {
        mPivot.x = -100.0f;
    }
    if (mAmp <= 0) {
        mDoAud_seStart(0x695A, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        mMode = 5;
        if (mpBgWHuta->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgWHuta);
        }
        mAngleX = 0;
        mAngleY = 0;
        mPivot.x = 0.0f;
    }
}

/* 00001764-00001A6C       .text executeOpenTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeOpenTate() {
    mAngleX += mSpeed;
    mSpeed += 100;
    if (mAngleX >= 0x4000) {
        dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        mAngleX = 0x4000;
        mMode = 6;
        mHideFlag |= 2;
        mEffPos.x = mMtxHuta[0][3];
        mEffPos.y = mMtxHuta[1][3];
        mEffPos.z = mMtxHuta[2][3];
        mEffAngle.set(0, shape_angle.y, 0);
        mpEmitter[0] = dComIfGp_particle_set(0x817F, &mEffPos, &mEffAngle, NULL, 0xFF, NULL, -1, &tevStr.mColorK0, &tevStr.mColorK0);
        mAlpha = 180.0f;
        if (mSmoke.getEmitter() == NULL) {
            dComIfGp_particle_setToon(0xA180, &mEffPos, &mEffAngle, NULL, mAlpha, &mSmoke);
        }
        if (mSmoke.getEmitter() != NULL) {
            mSmoke.getEmitter()->becomeImmortalEmitter();
        }
        mTimer = 60;
        return;
    }
    mDoMtx_stack_c::YrotS(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::transM(0.0f, 110.0f, 200.0f);
    mDoMtx_stack_c::XrotM(mAngleX);
    mDoMtx_stack_c::transM(0.0f, -110.0f, -200.0f);
    for (int i = 0; i < 3; i++) {
        cXyz start = daObjKanoke_Tate_pfs[i][0] + mHutaOffset;
        cXyz end = daObjKanoke_Tate_pfs[i][1] + mHutaOffset;
        mDoMtx_stack_c::multVec(&start, &start);
        mDoMtx_stack_c::multVec(&end, &end);
        start += current.pos;
        end += current.pos;
        mCpsHuta[i].SetStartEnd(start, end);
        dComIfG_Ccsp()->Set(&mCpsHuta[i]);
    }
}

/* 00001A6C-00001B24       .text executeEffectTate__13daObjKanoke_cFv */
void daObjKanoke_c::executeEffectTate() {
    mTimer--;
    if (mTimer != 0) {
        if (mSmoke.getEmitter() != NULL && mTimer <= 50) {
            mAlpha -= 3.6f;
            if (mAlpha < 0.0f) {
                mAlpha = 0.0f;
            }
            mSmoke.getEmitter()->setGlobalAlpha(mAlpha);
        }
    } else {
        mSmoke.remove();
        mMode = 7;
    }
}

/* 00001B24-00001B28       .text executeWait__13daObjKanoke_cFv */
void daObjKanoke_c::executeWait() {
}

/* 00001B28-00001B54       .text getPrmType__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmType() {
    return daObj::PrmAbstract(this, PRM_TYPE_W, PRM_TYPE_S);
}

/* 00001B54-00001B80       .text getPrmSearch__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSearch() {
    return daObj::PrmAbstract(this, PRM_SEARCH_W, PRM_SEARCH_S);
}

/* 00001B80-00001BAC       .text getPrmYure__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmYure() {
    return daObj::PrmAbstract(this, PRM_YURE_W, PRM_YURE_S);
}

/* 00001BAC-00001BD8       .text getPrmSwNo__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSwNo() {
    return daObj::PrmAbstract(this, PRM_SWNO_W, PRM_SWNO_S);
}

/* 00001BD8-00001C04       .text getPrmSwNo2__13daObjKanoke_cFv */
u8 daObjKanoke_c::getPrmSwNo2() {
    return daObj::PrmAbstract(this, PRM_SWNO2_W, PRM_SWNO2_S);
}

/* 00001C04-00001C9C       .text setMtx__13daObjKanoke_cFv */
void daObjKanoke_c::setMtx() {
    if (!(mHideFlag & 1)) {
        setMtxHontai();
        mpModelBody->setBaseTRMtx(mDoMtx_stack_c::get());
        cMtx_copy(mDoMtx_stack_c::get(), mMtxBody);
    }
    if (!(mHideFlag & 2)) {
        setMtxHuta(&current.pos);
        mpModelHuta->setBaseTRMtx(mDoMtx_stack_c::get());
        cMtx_copy(mDoMtx_stack_c::get(), mMtxHuta);
    }
}

/* 00001C9C-00001D38       .text setMtxHontai__13daObjKanoke_cFv */
void daObjKanoke_c::setMtxHontai() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::transM(mPivot.x, mPivot.y, mPivot.z);
    mDoMtx_stack_c::YrotM(mAngleY);
    mDoMtx_stack_c::transM(-mPivot.x, -mPivot.y, -mPivot.z);
}

/* 00001D38-00001E4C       .text setMtxHuta__13daObjKanoke_cFP4cXyz */
void daObjKanoke_c::setMtxHuta(cXyz* pos) {
    cXyz offset;
    mDoMtx_stack_c::YrotS(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::multVec(&mHutaOffset, &offset);
    mDoMtx_stack_c::transS(pos->x + offset.x, pos->y + offset.y, pos->z + offset.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::XrotM(shape_angle.x);
    mDoMtx_stack_c::transM(mPivot.x, mPivot.y, mPivot.z);
    mDoMtx_stack_c::XrotM(mAngleX);
    mDoMtx_stack_c::YrotM(mAngleY);
    mDoMtx_stack_c::ZrotM(mAngleZ);
    mDoMtx_stack_c::transM(-mPivot.x, -mPivot.y, -mPivot.z);
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
