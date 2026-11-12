/**
 * d_a_obj_htetu1.cpp
 * Object - Tower of the Gods - Large yellow gate (blocks room containing Small Key)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_htetu1.h"
#include "d/d_bg_s_func.h"
#include "d/d_bg_s_wtr_chk.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Htetu1.h"

const u16 l_daObjHtetu1_splash_id_table[] = {
    dPa_name::ID_AK_SN_SIRENWATERGATE00,
    dPa_name::ID_AK_SN_SIRENWATERGATE01,
};

const char daObjHtetu1_c::M_arcname[] = "Htetu1";

/* 00000078-0000016C       .text create_s__19daObjHtetu1Splash_cFUsP4cXyzP5csXyzP12dKy_tevstr_c */
void daObjHtetu1Splash_c::create_s(u16 particleID, cXyz* pPos, csXyz* pAngle, dKy_tevstr_c* pTevStr) {
    mPos = *pPos;
    mAngle = *pAngle;
    dComIfGp_particle_set(particleID, &mPos, &mAngle, NULL, 255, &mSplashCb);
    if (mSplashCb.getEmitter() != NULL) {
        mSplashCb.getEmitter()->setGlobalPrmColor(pTevStr->mColorC0.r, pTevStr->mColorC0.g, pTevStr->mColorC0.b);
    }
    JPABaseEmitter* emitter = mSplashCb.getEmitter();
    if (emitter != NULL) {
        emitter->stopCreateParticle();
        mbIsActive = false;
    }
    mbIsActive = false;
    mTimer = -2;
}

/* 0000016C-0000018C       .text solidHeapCB__13daObjHtetu1_cFP10fopAc_ac_c */
BOOL daObjHtetu1_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjHtetu1_c*)i_this)->create_heap();
}

/* 0000018C-0000028C       .text create_heap__13daObjHtetu1_cFv */
BOOL daObjHtetu1_c::create_heap() {
    BOOL ret = TRUE;

    J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HTETU1_BDL_HTETU1_e);
    JUT_ASSERT(281, mdl_data != NULL);

    if (mdl_data == NULL) {
        ret = FALSE;
    } else {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);
        mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HTETU1_DZB_HTETU1_e), cBgW::MOVE_BG_e,
                            &mpModel->getBaseTRMtx());
        if (mpBgW == NULL) {
            ret = FALSE;
        }
    }
    return ret;
}

/* 0000028C-00000454       .text _create__13daObjHtetu1_cFv */
cPhs_State daObjHtetu1_c::_create() {
    fopAcM_ct(this, daObjHtetu1_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        ret = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0xae0)) {
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            mSwNo = fopAcM_GetParam(this) & 0xFF;
            mLowY = current.pos.y - 2300.0f;
            if (check_sw()) {
                current.pos.y = mLowY;
                mEvState = 2;
            }
            mQuakeTimer = -1;
            init_mtx();
            g_env_light.settingTevStruct(TEV_TYPE_BG1, &current.pos, &tevStr);

            for (int i = 0; i < 2; i++) {
                mSplash[i].create_s(l_daObjHtetu1_splash_id_table[i], &current.pos, &current.angle, &tevStr);
            }

            fopAcM_setCullSizeBox(this, -950.0f, -1000.0f, -100.0f, 950.0f, 1300.0f, 100.0f);
            dComIfG_Bgsp()->Regist(mpBgW, this);
            mEventIdx = dComIfGp_evmng_getEventIdx("htetu1_open");
            ret = cPhs_COMPLEATE_e;
        }
    }
    return ret;
}

/* 00000508-00000610       .text _delete__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_delete() {
    if (mQuakeTimer > 0) {
        dComIfGp_getVibration().StopQuake(-1);
        mQuakeTimer = -1;
    }

    for (int i = 0; i < 2; i++) {
        mSplash[i].delete_s();
    }

    if (heap != NULL && mpBgW != NULL && mpBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBgW);
        mpBgW = NULL;
    }

    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

/* 00000610-00000648       .text check_sw__13daObjHtetu1_cFv */
BOOL daObjHtetu1_c::check_sw() {
    return fopAcM_isSwitch(this, mSwNo);
}

/* 00000648-000006E4       .text init_mtx__13daObjHtetu1_cFv */
void daObjHtetu1_c::init_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mpModel->calc();
}

/* 000006E4-000007F8       .text unlock__13daObjHtetu1_cFv */
void daObjHtetu1_c::unlock() {
    cXyz shake = cXyz::BaseY;
    mPos -= mShake;
    s16 angle = mTimer * 0x859;
    s16 wave = mAmp * cM_ssin(angle);
    f32 mag = wave;
    shake *= std::fabsf(mag);
    mPos += shake;
    mShake = shake;
    cLib_addCalc(&mAmp, 0.0f, 0.13f, 50.0f, 1.0f);
}

/* 000007F8-0000098C       .text get_water_h__13daObjHtetu1_cFv */
f32 daObjHtetu1_c::get_water_h() {
    dBgS_WtrChk waterChk;
    cXyz chkPos = home.pos;
    f32 ret = current.pos.y;

    cXyz offVec;
    mDoMtx_stack_c::YrotS(current.angle.y);
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &offVec);
    offVec *= 400.0f;
    chkPos += offVec;
    if (dBgS_SplGrpChk_In_ObjGnd(chkPos, &waterChk, 1.0f) != false) {
        ret = waterChk.GetHeight();
    }
    return ret;
}

/* 00000AB8-00000BD4       .text splash_manager__13daObjHtetu1_cFv */
void daObjHtetu1_c::splash_manager() {
    f32 water_h = get_water_h();

    for (int i = 0; i < 2; i++) {
        mSplash[i].set_pos_y(water_h);
        s16 timer = mSplash[i].get_timer();
        if (timer == 0) {
            mSplash[i].stop_particle();
        } else if (timer > 0 || timer == -1) {
            if (1400.0f + current.pos.y > water_h) {
                mSplash[i].play_particle();
            } else {
                mSplash[i].stop_particle();
            }
            if (timer > 0) {
                mSplash[i].sub_timer();
            }
        }
    }
}

/* 00000BD4-00001024       .text _execute__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_execute() {
    switch (mEvState) {
    case 0:
        if (check_sw()) {
            if (!eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderOtherEventId(this, mEventIdx);
                eventInfo.onCondition(dEvtCnd_UNK2_e);
            } else {
                mAmp = 50.0f;
                mTimer = 70;
                mShake = cXyz::BaseY * mAmp;
                mDoAud_seStart(JA_SE_READ_RIDDLE_1);
                mMoveState = 1;
                mEvState = 1;
                dComIfGp_getVibration().StartShock(5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                for (int i = 0; i < 2; i++) {
                    mSplash[i].timer_play_particle(30);
                }
            }
        }
        break;
    case 1:
        if (dComIfGp_evmng_endCheck(mEventIdx)) {
            dComIfGp_event_reset();
            mEvState = 2;
        }
        break;
    }

    mPos = current.pos;

    switch (mMoveState) {
    case 1:
        unlock();
        if (mTimer != 0) {
            mTimer--;
            fopAcM_seStartCurrent(this, JA_SE_OBJ_ST_KOUSHI_MOVE, 0);
        } else {
            dComIfGp_getVibration().StartQuake(6, 3, cXyz(0.0f, 1.0f, 0.0f));
            mMoveState = 2;
            mQuakeTimer = 200;
            for (int i = 0; i < 2; i++) {
                mSplash[i].timer_play_particle(-1);
            }
        }
        break;
    case 2:
        mPos.y -= 5.0f;
        fopAcM_seStartCurrent(this, JA_SE_OBJ_ST_KOUSHI_MOVE, 0);
        if (mPos.y <= mLowY) {
            for (int i = 0; i < 2; i++) {
                mSplash[i].delete_s();
            }
            mPos.y = mLowY;
            mMoveState = 0;
        }
        break;
    }

    current.pos = mPos;
    init_mtx();
    splash_manager();

    if (mQuakeTimer == 0) {
        dComIfGp_getVibration().StopQuake(-1);
        mQuakeTimer = -1;
    } else if (mQuakeTimer > 0) {
        mQuakeTimer--;
    }

    if (heap != NULL && mpBgW != NULL && mpBgW->ChkUsed()) {
        mpBgW->Move();
    }
    return true;
}

/* 00001024-00001084       .text _draw__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return true;
}

namespace {
/* 0000107C-0000109C       .text Mthd_Create__28@unnamed@d_a_obj_htetu1_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_create();
}

/* 0000109C-000010C0       .text Mthd_Delete__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_delete();
}

/* 000010C0-000010E4       .text Mthd_Execute__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_execute();
}

/* 000010E4-00001108       .text Mthd_Draw__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_draw();
}

/* 00001108-00001110       .text Mthd_IsDelete__28@unnamed@d_a_obj_htetu1_cpp@FPv */
BOOL Mthd_IsDelete(void*) {
    return TRUE;
}

static actor_method_class Htetu1_Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

actor_process_profile_definition g_profile_Obj_Htetu1 = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Htetu1_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHtetu1_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Htetu1_e,
    /* Actor SubMtd */ &Htetu1_Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
