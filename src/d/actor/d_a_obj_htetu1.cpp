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
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_lib.h"

const u16 l_daObjHtetu1_splash_id_table[2] = {0x82BA, 0x82BB};
const char daObjHtetu1_c::M_arcname[7] = "Htetu1";

/* 00000078-00000178       .text create_s__19daObjHtetu1Splash_cFUsP4cXyzP5csXyzP12dKy_tevstr_c */
void daObjHtetu1Splash_c::create_s(unsigned short particleID, cXyz* pPos, csXyz* pAngle, dKy_tevstr_c* pTevStr) {
    mPos = *pPos;
    mAngle = *pAngle;
    dComIfGp_particle_set(particleID, &mPos, &mAngle, NULL, 0xFF, &mSplashCb);
    JPABaseEmitter* emitter = mSplashCb.getEmitter();
    if (emitter != NULL) {
        emitter->setGlobalPrmColor(pTevStr->mColorC0.r, pTevStr->mColorC0.g, pTevStr->mColorC0.b);
    }
    stop_particle();
    mbIsActive = false;
    mTimer = -2;
}

/* 00000178-00000198       .text solidHeapCB__13daObjHtetu1_cFP10fopAc_ac_c */
BOOL daObjHtetu1_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjHtetu1_c*)i_this)->create_heap();
}

/* 00000198-00000298       .text create_heap__13daObjHtetu1_cFv */
BOOL daObjHtetu1_c::create_heap() {
    BOOL ret = TRUE;
    J3DModelData* mdl_data = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, 4));
    JUT_ASSERT(281, mdl_data != 0);
    if (mdl_data == NULL) {
        ret = FALSE;
    } else {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);
        mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(M_arcname, 7), cBgW::MOVE_BG_e, &mpModel->getBaseTRMtx());
        if (mpBgW == NULL) {
            ret = FALSE;
        }
    }
    return ret;
}

/* 00000298-00000460       .text _create__13daObjHtetu1_cFv */
cPhs_State daObjHtetu1_c::_create() {
    fopAcM_ct(this, daObjHtetu1_c);

    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        ret = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0xAE0)) {
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            mSwNo = fopAcM_GetParam(this) & 0xFF;
            mOpenY = current.pos.y - 2300.0f;
            if (check_sw()) {
                current.pos.y = mOpenY;
                mEventState = 2;
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
inline BOOL daObjHtetu1_c::check_sw() {
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
    cXyz offset = cXyz::BaseY;
    mPos -= mShakeVec;
    f32 amp = mShakeAmp;
    s16 ang = mShakeTimer * 0x859;
    offset *= std::fabsf((s16)(amp * cM_ssin(ang)));
    mPos += offset;
    mShakeVec = offset;
    cLib_addCalc(&mShakeAmp, 0.0f, 0.13f, 50.0f, 1.0f);
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
    if (dBgS_SplGrpChk_In_ObjGnd(chkPos, &waterChk, 1.0f)) {
        ret = waterChk.GetHeight();
    }
    return ret;
}

/* 00000AB0-00000BCC       .text splash_manager__13daObjHtetu1_cFv */
void daObjHtetu1_c::splash_manager() {
    f32 water_h = get_water_h();
    for (int i = 0; i < 2; i++) {
        mSplash[i].set_pos_y(water_h);
        s16 timer = mSplash[i].get_timer();
        if (timer == 0) {
            if (!mSplash[i].chk_stop()) {
                mSplash[i].stop_particle();
            }
        } else if (timer > 0 || timer == -1) {
            if (current.pos.y + 1400.0f > water_h) {
                if (mSplash[i].chk_stop()) {
                    mSplash[i].play_particle();
                }
            } else {
                if (!mSplash[i].chk_stop()) {
                    mSplash[i].stop_particle();
                }
            }
            if (timer > 0) {
                mSplash[i].sub_timer();
            }
        }
    }
}

/* 00000BCC-0000101C       .text _execute__13daObjHtetu1_cFv */
bool daObjHtetu1_c::_execute() {
    int i;
    switch (mEventState) {
    case 0:
        if (check_sw()) {
            if (!eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderOtherEventId(this, mEventIdx, 0xFF, 0xFFFF, 0, 1);
                eventInfo.onCondition(dEvtCnd_UNK2_e);
            } else {
                mShakeAmp = 50.0f;
                mShakeTimer = 70;
                mShakeVec = cXyz::BaseY * 50.0f;
                mDoAud_seStart(0x806, NULL, 0, 0);
                mMoveState = 1;
                mEventState = 1;
                dComIfGp_getVibration().StartShock(5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                for (i = 0; i < 2; i++) {
                    mSplash[i].timer_play_particle(30);
                }
            }
        }
        break;
    case 1:
        if (dComIfGp_evmng_endCheck(mEventIdx)) {
            dComIfGp_event_reset();
            mEventState = 2;
        }
        break;
    case 2:
        break;
    }

    mPos = current.pos;

    switch (mMoveState) {
    case 0:
        break;
    case 1:
        unlock();
        if (mShakeTimer != 0) {
            mShakeTimer--;
            mDoAud_seStart(0x107B, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        } else {
            dComIfGp_getVibration().StartQuake(6, 3, cXyz(0.0f, 1.0f, 0.0f));
            mMoveState = 2;
            mQuakeTimer = 200;
            for (i = 0; i < 2; i++) {
                mSplash[i].timer_play_particle(-1);
            }
        }
        break;
    case 2:
        mPos.y -= 5.0f;
        mDoAud_seStart(0x107B, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        if (mPos.y <= mOpenY) {
            for (i = 0; i < 2; i++) {
                mSplash[i].delete_s();
            }
            mPos.y = mOpenY;
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

/* 0000101C-0000107C       .text _draw__13daObjHtetu1_cFv */
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
