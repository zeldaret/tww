/**
 * d_a_obj_htetu1.cpp
 * Object - Tower of the Gods - Large yellow gate (blocks room containing Small Key)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_htetu1.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_mtx.h"
#include "JSystem/JMath/JMATrigonometric.h"
#include "d/d_bg_s_func.h"

static const u16 l_daObjHtetu1_splash_id_table[] = {
    0x82BA, 0x82BB
};

const char daObjHtetu1_c::M_arcname[] = "Htetu1";

extern "C" void set__13dPa_control_cFUcUsPC4cXyzPC5csXyzPC4cXyzUcP18dPa_levelEcallBackScPC8_GXColorPC8_GXColorPC4cXyz(
    u8, u16, const cXyz*, const csXyz*, const cXyz*, u8, dPa_levelEcallBack*, s8, const GXColor*, const GXColor*, const cXyz*
);

void daObjHtetu1Splash_c::create_s(u16 id, cXyz* pos, csXyz* angle, dKy_tevstr_c* tevStr) {
    mPos = *pos;
    mRot = *angle;
    dComIfGp_particle_set(id, &mPos, &mRot, NULL, 0xFF, this, -1, NULL, NULL, NULL);
    s16 g, b, r;
    JPABaseEmitter* emitter = mpEmitter;
    if (emitter != NULL) {
        b = tevStr->mColorC0.b;
        g = tevStr->mColorC0.g;
        r = tevStr->mColorC0.r;
        emitter->mGlobalPrmColor.r = r;
        emitter->mGlobalPrmColor.g = g;
        emitter->mGlobalPrmColor.b = b;
    }
    if (mpEmitter != NULL) {
        mpEmitter->setStatus(JPAEmtrStts_StopEmit);
        mState = 0;
    }
    mState = 0;
    mTimer = -2;
}

BOOL daObjHtetu1_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((daObjHtetu1_c*)i_this)->create_heap();
}

BOOL daObjHtetu1_c::create_heap() {
    register J3DModelData* modelData;
    register BOOL status = TRUE;
    
    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, 4));
    JUT_ASSERT(281, modelData !=0);
    if (modelData == NULL) {
        status = FALSE;
    } else {
        mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        float (*mtx)[3][4] = &mpModel->getBaseTRMtx();
        cBgD_t* bgd = static_cast<cBgD_t*>(dComIfG_getObjectRes(M_arcname, 7));
        mpBgW = dBgW_NewSet(bgd, 1, mtx);
        if (mpBgW == NULL) {
            status = FALSE;
        }
    }
    
    return status;
}
cPhs_State daObjHtetu1_c::_create() {
    fopAcM_SetupActor(this, daObjHtetu1_c);
    
    cPhs_State state = (cPhs_State)dComIfG_resLoad(&mPhase, M_arcname);
    if (state == cPhs_COMPLEATE_e) {
        state = cPhs_ERROR_e;
        if (fopAcM_entrySolidHeap(this, solidHeapCB, 0xAE0)) {
            cullMtx = mpModel->getBaseTRMtx();
            mSw = (u8)fopAcM_GetParam(this);
            mBaseY = current.pos.y - 2300.0f;
            
            if (check_sw()) {
                current.pos.y = mBaseY;
                mMode = 2;
            }
            
            mQuakeTimer = -1;
            init_mtx();
            
            g_env_light.settingTevStruct(2, &current.pos, &tevStr);
            
            for (int i = 0; i < 2; i++) {
                mSplash[i].create_s(l_daObjHtetu1_splash_id_table[i], &current.pos, &current.angle, &tevStr);
            }
            
            fopAcM_setCullSizeBox(this, -950.0f, -1000.0f, -100.0f, 950.0f, 1300.0f, 100.0f);
            
            dComIfG_Bgsp()->Regist(mpBgW, this);
            
            mEventIdx = dComIfGp_evmng_getEventIdx("htetu1_open", 0xFF);
            
            state = cPhs_COMPLEATE_e;
        }
    }
    
    return state;
}


bool daObjHtetu1_c::_delete() {
    if (mQuakeTimer > 0) {
        dComIfGp_getVibration().StopQuake(-1);
        mQuakeTimer = -1;
    }
    
    for (int i = 0; i < 2; i++) {
        if (mSplash[i].getEmitter() != NULL) {
            mSplash[i].end();
            mSplash[i].mState = 0;
        }
    }
    
    if (heap != NULL && mpBgW != NULL && mpBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBgW);
        mpBgW = NULL;
    }
    
    dComIfG_resDelete(&mPhase, M_arcname);
    return true;
}

BOOL daObjHtetu1_c::check_sw() {
    return fopAcM_isSwitch(this, mSw);
}

void daObjHtetu1_c::init_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    MtxP stack_mtx = mDoMtx_stack_c::get();
    J3DModel* model = mpModel;
    MTXCopy(stack_mtx, model->getBaseTRMtx());
    mpModel->calc();
}

void daObjHtetu1_c::unlock() {
    cXyz sp8 = cXyz::BaseY;
    PSVECSubtract(&mTargetPos, &mGatePos, &mTargetPos);
    f32 scale = mSpeedY;
    scale = (f32)(s16)(scale * cM_ssin(mMoveTimer * 0x859));
    scale = std::fabsf(scale);
    PSVECScale(&sp8, &sp8, scale);
    PSVECAdd(&mTargetPos, &sp8, &mTargetPos);
    
    mGatePos = sp8;
    
    cLib_addCalc(&mSpeedY, 0.0f, 0.13f, 50.0f, 1.0f);
}

f32 daObjHtetu1_c::get_water_h() {
    dBgS_WtrChk wtrChk;
    cXyz pos;
    pos.x = home.pos.x;
    pos.y = home.pos.y;
    pos.z = home.pos.z;
    
    f32 water_h = current.pos.y;
    
    mDoMtx_stack_c::YrotS(current.angle.y);
    cXyz offset;
    mDoMtx_stack_c::multVec(&cXyz::BaseZ, &offset);
    offset *= 400.0f;
    pos += offset;
    
    if (dBgS_SplGrpChk_In_ObjGnd(pos, &wtrChk, 1.0f)) {
        water_h = wtrChk.GetHeight();
    }
    return water_h;
}

void daObjHtetu1_c::splash_manager() {
    f32 water_h = get_water_h();
    s16 timer;
    for (int i = 0; i < 2; i++) {
        mSplash[i].set_pos_y(water_h);
        timer = mSplash[i].get_timer();
        if (timer == 0) {
            if (mSplash[i].mState != 0) {
                if (mSplash[i].getEmitter() != NULL) {
                    mSplash[i].getEmitter()->setStatus(JPAEmtrStts_StopEmit);
                    mSplash[i].mState = 0;
                }
            }
        } else if (timer > 0 || timer == -1) {
            if (current.pos.y + 1400.0f > water_h) {
                if (mSplash[i].mState == 0) {
                    if (mSplash[i].getEmitter() != NULL) {
                        mSplash[i].getEmitter()->clearStatus(JPAEmtrStts_StopEmit);
                        mSplash[i].mState = 1;
                    }
                }
            } else {
                if (mSplash[i].mState != 0) {
                    if (mSplash[i].getEmitter() != NULL) {
                        mSplash[i].getEmitter()->setStatus(JPAEmtrStts_StopEmit);
                        mSplash[i].mState = 0;
                    }
                }
            }
            if (timer > 0) {
                mSplash[i].mTimer--;
            }
        }
    }
}

bool daObjHtetu1_c::_execute() {
    int i;
    int state;
    switch (mMode) {
    case 2:
        break;
    case 0:
        if (fopAcM_isSwitch(this, mSw)) {
            if (eventInfo.checkCommandDemoAccrpt() == FALSE) {
                fopAcM_orderOtherEventId(this, mEventIdx, 0xFF, 0xFFFF, 0, 1);
                eventInfo.onCondition(2);
            } else {
                mSpeedY = 50.0f;
                mMoveTimer = 70;
                mGatePos = cXyz::BaseY * 50.0f;
                mDoAud_seStart(0x806, NULL, 0, 0);
                mState = 1;
                mMode = 1;
                dComIfGp_getVibration().StartShock(5, -33, cXyz(0.0f, 1.0f, 0.0f));
                for (i = 0; i < 2; i++) {
                    if (mSplash[i].getEmitter() != NULL) {
                        mSplash[i].getEmitter()->clearStatus(JPAEmtrStts_StopEmit);
                        mSplash[i].mState = 1;
                        mSplash[i].mTimer = 30;
                    }
                }
            }
        }
        break;
    case 1:
        if (dComIfGp_evmng_endCheck(mEventIdx)) {
            g_dComIfG_gameInfo.play.getEvent()->onEventFlag(8);
            mMode = 2;
        }
        break;
    }
    
    mTargetPos = current.pos;
    
    switch (mState) {
    case 0:
        break;
    case 1:
        unlock();
        if (mMoveTimer != 0) {
            mMoveTimer--;
            mDoAud_seStart(0x107b, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        } else {
            dComIfGp_getVibration().StartQuake(6, 3, cXyz(0.0f, 1.0f, 0.0f));
            mState = 2;
            mQuakeTimer = 200;
            for (i = 0; i < 2; i++) {
                if (mSplash[i].getEmitter() != NULL) {
                    mSplash[i].getEmitter()->clearStatus(JPAEmtrStts_StopEmit);
                    mSplash[i].mState = 1;
                    mSplash[i].mTimer = -1;
                }
            }
        }
        break;
    case 2:
        mTargetPos.y -= 5.0f;
        mDoAud_seStart(0x107b, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        if (mTargetPos.y <= mBaseY) {
            i = 0;
            state = i;
            do {
                if (mSplash[i].getEmitter() != NULL) {
                    mSplash[i].end();
                    mSplash[i].mState = state;
                }
                i++;
            } while (i < 2);
            mTargetPos.y = mBaseY;
            mState = 0;
        }
        break;
    }
    
    current.pos = mTargetPos;
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

bool daObjHtetu1_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mDoExt_modelUpdateDL(mpModel);
    return true;
}

namespace {
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_create();
}

BOOL Mthd_Delete(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_delete();
}

BOOL Mthd_Execute(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_execute();
}

BOOL Mthd_Draw(void* i_this) {
    return ((daObjHtetu1_c*)i_this)->_draw();
}

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
