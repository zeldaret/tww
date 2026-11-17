/**
 * d_a_obj_magmarock.cpp
 * Object - Magma rock (Dragon Roost Cavern)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_magmarock.h"
#include "d/d_bg_w.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_magma.h"
#include "d/d_s_play.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_lib.h"
#include "res/Object/Kyjim.h"

const char daObjMagmarock::Act_c::M_arcname[] = "Kyjim";
GXColor daObjMagmarock::Act_c::default_color = {0xFF, 0xFF, 0xFF, 0xFF};

static inline void mr_color_add(dKy_tevstr_c* tevstr, f32 ratio) {
    tevstr->mColorC0.r = (u8)(tevstr->mColorC0.r + (int)(ratio * (f32)(0xFF - tevstr->mColorC0.r)));
    tevstr->mColorC0.g = (u8)(tevstr->mColorC0.g + (int)(ratio * (f32)(0xFF - tevstr->mColorC0.g)));
    tevstr->mColorC0.b = (u8)(tevstr->mColorC0.b + (int)(ratio * (f32)(0xFF - tevstr->mColorC0.b)));
    tevstr->mColorK0.r = (u8)(tevstr->mColorK0.r + (int)(ratio * (f32)(0xFF - tevstr->mColorK0.r)));
    tevstr->mColorK0.g = (u8)(tevstr->mColorK0.g + (int)(ratio * (f32)(0xFF - tevstr->mColorK0.g)));
    tevstr->mColorK0.b = (u8)(tevstr->mColorK0.b + (int)(ratio * (f32)(0xFF - tevstr->mColorK0.b)));
}

/* 00000078-00000128       .text set_mtx__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    Quaternion quat;
    PSQUATMultiply(&mQuat, &mGroundQuat, &quat);
    mDoMtx_stack_c::quatM(&quat);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), mMtx);
}

/* 00000128-00000258       .text demo_move__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::demo_move() {
    if (dComIfGs_isEventBit(0x380) || mStayType != 0) {
        return;
    }
    if (mDemoState == 0) {
        if (eventInfo.checkCommandDemoAccrpt()) {
            mDemoState++;
        } else {
            fopAcM_orderOtherEvent2(this, "magma_cam", dEvtFlag_NOPARTNER_e, 0xFFFF);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
    } else if (mDemoState == 1) {
        int staffIdx = dComIfGp_evmng_getMyStaffId("Magrock");
        if (dComIfGp_evmng_endCheck("magma_cam")) {
            dComIfGp_event_reset();
            mDemoState++;
            dComIfGs_onEventBit(0x380);
        } else {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }
}

/* 00000258-00000410       .text ControlEffect__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::ControlEffect() {
    if (mLiftUp) {
        if (mBeforeLift) {
            if (mpEmitter2 == NULL) {
                mpEmitter2 = dComIfGp_particle_set(0x8104, &current.pos);
            } else {
                mpEmitter2->setGlobalTranslation(current.pos.x, current.pos.y, current.pos.z);
            }
        } else {
            if (mpEmitter2 != NULL) {
                mpEmitter2->becomeInvalidEmitter();
                mpEmitter2 = NULL;
            }
            if (mpEmitter3 == NULL) {
                dComIfGp_getVibration().StartShock(4, 1, cXyz(0.0f, 1.0f, 0.0f));
                mpEmitter3 = dComIfGp_particle_setToon(0x8105, &current.pos);
            } else {
                mpEmitter3->setGlobalTranslation(current.pos.x, current.pos.y, current.pos.z);
            }
        }
    } else {
        if (mpEmitter3 != NULL) {
            mpEmitter3->becomeInvalidEmitter();
            mpEmitter3 = NULL;
        }
    }
}

/* 0000044C-00000560       .text play_anim__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::play_anim() {
    if (mCount > 375 && mBrkFrame > 0.0f) {
        mBrkFrame -= 1.0f;
    } else if (mCount < 15 || mCount > 60) {
        if (mBrkFrame < M_brk->getFrameMax()) {
            mBrkFrame += 1.0f;
        }
    }
    if (mCount < 60 && mBckFrame < M_bck->getFrameMax()) {
        mBckFrame += 1.0f;
    } else if (mCount > 375 && mBckFrame > 0.0f) {
        mBckFrame -= 1.0f;
    }
}

/* 00000560-0000058C       .text appear_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::appear_proc_init() {
    mTimer = 30;
    setProcess(&Act_c::appear_proc);
}

/* 0000058C-000005EC       .text appear_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::appear_proc() {
    if (mTimer == 10) {
        dComIfG_Bgsp()->Regist(mpBgW, this);
    }
    if (mTimer == 0) {
        wait_proc_init();
    }
}

/* 000005EC-00000618       .text wait_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::wait_proc_init() {
    mTimer = 300;
    setProcess(&Act_c::wait_proc);
}

/* 00000618-00000644       .text wait_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::wait_proc() {
    if (mTimer == 0) {
        quake_proc_init();
    }
}

/* 00000644-000006E0       .text stay_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::stay_proc_init() {
    u8 delay = fopAcM_GetParam(this);
    if (delay == 0xFF) {
        delay = 0;
    }
    mBrkFrame = 30.0f;
    mBckFrame = 30.0f;
    mTimer = delay * 15 + 30;
    mCount = 330;
    dComIfG_Bgsp()->Regist(mpBgW, this);
    setProcess(&Act_c::stay_proc);
}

/* 000006E0-00000720       .text stay_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::stay_proc() {
    if (mRideOn) {
        if (mTimer-- == 0) {
            quake_proc_init();
        }
    }
}

/* 00000720-000007B8       .text quake_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::quake_proc_init() {
    mDoAud_seStart(0x380F, &eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    mTimer = 45;
    setProcess(&Act_c::quake_proc);
}

/* 000007B8-0000084C       .text quake_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::quake_proc() {
    mWaveAngle += mWaveSpeed;
    cLib_addCalcAngleS2(&mWaveSpeed, 0x1000, 2, 0x100);
    cLib_addCalc2(&mTilt, 750.0f + REG10_F(10), 0.25f, 50.0f);
    if (mTimer == 0) {
        vanish_proc_init();
    }
}

/* 0000084C-00000878       .text vanish_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::vanish_proc_init() {
    mTimer = 90;
    setProcess(&Act_c::vanish_proc);
}

/* 00000878-000008F8       .text vanish_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::vanish_proc() {
    mWaveAngle += mWaveSpeed;
    cLib_addCalcAngleS2(&mWaveSpeed, 0, 4, 0x40);
    if (mTimer == 80) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
    if (mTimer < 0) {
        fopAcM_delete(this);
    }
}

/* 000008F8-00000AEC       .text ride_call_back__14daObjMagmarockFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjMagmarock::ride_call_back(dBgW*, fopAc_ac_c* i_ac, fopAc_ac_c* i_rider) {
    Act_c* i_this = (Act_c*)i_ac;
    cXyz vec = i_rider->current.pos - i_this->current.pos;
    cXyz up(0.0f, 1.0f, 0.0f);
    vec = vec.outprod(up);
    f32 len = std::sqrtf(vec.abs2());
    if (vec.normalizeRS()) {
        cLib_addCalcAngleS2(&i_this->mRideAngle, -len * (2.0f + 4.0f * (0.001f * (i_this->current.pos.y - i_this->home.pos.y))), 8, 0x200);
        i_this->mRideFlag = 1;
        i_this->mRideOn = 1;
        f32 sin = cM_ssin(i_this->mRideAngle);
        i_this->mRideQuat.x = vec.x * sin;
        i_this->mRideQuat.y = vec.y * sin;
        i_this->mRideQuat.z = vec.z * sin;
        i_this->mRideQuat.w = cM_scos(i_this->mRideAngle);
    }
}

/* 00000AEC-00000B0C       .text CheckCreateHeap__14daObjMagmarockFP10fopAc_ac_c */
BOOL daObjMagmarock::CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->CreateHeap();
}

/* 00000B0C-00000DA0       .text CreateHeap__Q214daObjMagmarock5Act_cFv */
BOOL daObjMagmarock::Act_c::CreateHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, dRes_INDEX_KYJIM_BDL_KYJIM_00_e));
    JUT_ASSERT(333, modelData != 0);
    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);

    M_brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_KYJIM_BRK_KYJIM_00_e);
    M_bck = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_KYJIM_BCK_KYJIM_00_e);
    JUT_ASSERT(341, M_brk != 0);
    JUT_ASSERT(342, M_bck != 0);

    BOOL brk_ret = mBrk.init(modelData, M_brk, FALSE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    BOOL bck_ret = mBck.init(modelData, M_bck, FALSE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale);
    cMtx_copy(mDoMtx_stack_c::get(), mMtx);

    mpBgW = dBgW_NewSet((cBgD_t*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_KYJIM_DZB_KYJIM_00_e), cBgW::MOVE_BG_e, &mMtx);
    mpBgW->SetCrrFunc(dBgS_MoveBGProc_Typical);
    if (mpBgW == NULL) {
        return FALSE;
    }
    return mpModel != NULL && brk_ret && bck_ret;
}

/* 00000DA0-000013B4       .text CreateInit__Q214daObjMagmarock5Act_cFv */
BOOL daObjMagmarock::Act_c::CreateInit() {
    scale.setall(1.0f);
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -200.0f, -30.0f, -200.0f, 200.0f, 30.0f, 200.0f);
    cMtx_copy(mpModel->getBaseTRMtx(), mMtx);
    mTilt = 0.0f;
    mRideAngle = 0;
    field_0x29a = 0;
    field_0x450 = 0;
    mTimer = 30;
    mCount = 0;
    mBrkFrame = 0.0f;
    mWaveAngle = 0;
    mWaveSpeed = 0;
    mDemoState = 0;
    mRideOn = 0;
    speed.setall(0.0f);
    home.pos = current.pos;
    home.pos.y += 15.0f;
    gravity = -2.5f;
    mGroundQuat = ZeroQuat;
    mRideQuat = mGroundQuat;
    mQuat = mRideQuat;
    set_mtx();
    mpBgW->SetRideCallback(ride_call_back);
    mStayType = fopAcM_GetParam(this) >> 24;
    if (mStayType != 0) {
        stay_proc_init();
    } else {
        appear_proc_init();
        if (mpEmitter0 == NULL) {
            mDoAud_seStart(0x380E, &eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            dComIfGp_getVibration().StartShock(4, 1, cXyz(0.0f, 1.0f, 0.0f));
            mTevStr = tevStr;
            g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &mTevStr);
            mr_color_add(&mTevStr, 0.12f);
            mpEmitter0 = dComIfGp_particle_setToon(0x8072, &current.pos, NULL, NULL, 153.0f + 102.0f * REG10_F(25));
            mpEmitter1 = dComIfGp_particle_setToon(0x8073, &current.pos, NULL, NULL, 153.0f + 102.0f * REG10_F(26));
            if (mpEmitter0 != NULL) {
                mpEmitter0->setGlobalPrmColor(default_color.r, default_color.g, default_color.b);
                mpEmitter0->setGlobalEnvColor(default_color.r, default_color.g, default_color.b);
            }
            if (mpEmitter1 != NULL) {
                mpEmitter1->setGlobalPrmColor(default_color.r, default_color.g, default_color.b);
                mpEmitter1->setGlobalEnvColor(default_color.r, default_color.g, default_color.b);
            }
        }
    }
    return TRUE;
}

/* 000013B4-00001560       .text LiftUpRequest__Q214daObjMagmarock5Act_cFR4cXyz */
BOOL daObjMagmarock::Act_c::LiftUpRequest(cXyz& pos) {
    mLiftPos = pos;
    if (!checkProcess(&Act_c::wait_proc)) {
        if (checkProcess(&Act_c::appear_proc)) {
            cXyz dir = current.pos - mLiftPos;
            dir.y = 0.0f;
            if (!dir.normalizeRS()) {
                dir.set(0.0f, 0.0f, 1.0f);
            }
            dir *= 10.0f;
            current.pos += dir;
        }
        return FALSE;
    }
    cLib_addCalcPos2(&current.pos, pos, 0.05f, 5.0f);
    cLib_addCalc2(&mTilt, 750.0f, 0.5f, 40.0f);
    cLib_addCalcAngleS2(&mWaveSpeed, 0x1200, 4, 0x100);
    mWaveAngle += mWaveSpeed;
    cLib_addCalc2(&current.pos.y, pos.y, 0.25f, 150.0f);
    mLiftUp = 1;
    return TRUE;
}

/* 00001560-0000167C       .text BeforeLiftRequest__Q214daObjMagmarock5Act_cFR4cXyz */
BOOL daObjMagmarock::Act_c::BeforeLiftRequest(cXyz& pos) {
    mLiftPos = pos;
    if (mLiftPos.y < 25.0f + home.pos.y) {
        mLiftPos.y = 25.0f + home.pos.y;
    }
    if (!checkProcess(&Act_c::wait_proc)) {
        return FALSE;
    }
    cLib_addCalcPos2(&current.pos, mLiftPos, 0.05f, 5.0f);
    cLib_addCalc2(&mTilt, 500.0f, 0.25f, 20.0f);
    cLib_addCalcAngleS2(&mWaveSpeed, 0xA00, 8, 0x100);
    mWaveAngle += mWaveSpeed;
    cLib_addCalc2(&current.pos.y, mLiftPos.y, 0.25f, 150.0f);
    mLiftUp = 1;
    mBeforeLift = 1;
    return TRUE;
}

/* 0000167C-000017DC       .text calc_ground_quat__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::calc_ground_quat() {
    f32 y;
    if (dComIfGp_getMagma() != NULL) {
        y = dComIfGp_getMagma()->checkYpos(current.pos);
    } else {
        y = current.pos.y - 10.0f;
    }
    if (y > -99999992.0f) {
        home.pos.y = 15.0f + (10.0f + y);
    }
    home.pos.x = current.pos.x;
    home.pos.z = current.pos.z;
    mGroundPos[0].set(0.0f, 0.0f, 120.0f);
    mGroundPos[1].set(103.9f, 0.0f, -60.0f);
    mGroundPos[2].set(-103.9f, 0.0f, -60.0f);
    for (int i = 0; i < 3; i++) {
        mGroundPos[i] += home.pos;
        if (dComIfGp_getMagma() != NULL) {
            y = dComIfGp_getMagma()->checkYpos(mGroundPos[i]);
        } else {
            y = current.pos.y - 10.0f;
        }
        if (y > -99999992.0f) {
            mGroundPos[i].y = 15.0f + y;
        }
    }
    dLib_calc_QuatFromTriangle(&mGroundQuat, 0.25f, &mGroundPos[0], &mGroundPos[1], &mGroundPos[2]);
}

inline cPhs_State daObjMagmarock::Act_c::_create() {
    fopAcM_ct(this, Act_c);

    cPhs_State ret = dComIfG_resLoad(&mPhase, M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        if (dComIfGp_getMagma() == NULL) {
            ret = cPhs_INIT_e;
        } else if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x5D40)) {
            ret = cPhs_ERROR_e;
        } else {
            CreateInit();
        }
    }
    return ret;
}

inline bool daObjMagmarock::Act_c::_delete() {
    dComIfG_resDelete(&mPhase, M_arcname);
    if (heap != NULL && mpBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
    return true;
}

inline bool daObjMagmarock::Act_c::_execute() {
    calc_ground_quat();
    if (mLiftUp == 0) {
        if (!checkProcess(&Act_c::quake_proc) && !checkProcess(&Act_c::vanish_proc)) {
            cLib_addCalc2(&mTilt, 0.0f, 0.2f, 20.0f);
            cLib_addCalcAngleS2(&mWaveSpeed, 0, 4, 0x100);
        }
        current.pos.y += speed.y;
        speed.y += gravity;
    } else {
        speed.y = 0.0f;
    }
    if (current.pos.y < 100.0f + home.pos.y) {
        if (old.pos.y >= 100.0f + home.pos.y) {
            dComIfGp_getVibration().StartShock(4, 1, cXyz(0.0f, 1.0f, 0.0f));
        }
        if (current.pos.y < home.pos.y) {
            f32 min = home.pos.y - 30.0f;
            if (current.pos.y < min) {
                current.pos.y = min;
            }
            speed.y -= (0.4f + REG10_F(26)) * (current.pos.y - home.pos.y);
        }
        speed.y *= 0.65f - REG10_F(25);
    }
    if (mLiftUp == 0 && !checkProcess(&Act_c::stay_proc)) {
        mTimer--;
        mCount++;
    }
    set_mtx();
    demo_move();
    ControlEffect();
    mLiftUp = 0;
    mBeforeLift = 0;
    (this->*mProc)();
    play_anim();
    shape_angle.x = mTilt * cM_scos(mWaveAngle);
    shape_angle.z = mTilt * cM_ssin(mWaveAngle);
    if (mRideFlag == 0) {
        mRideQuat = ZeroQuat;
    }
    Quaternion quat;
    C_QUATSlerp(&mQuat, &mRideQuat, &quat, 0.25f);
    mQuat = quat;
    mRideFlag = 0;
    if (mpBgW->ChkUsed()) {
        mpBgW->mIgnorePlaneType |= 4;
        mpBgW->Move();
    }
    return false;
}

inline bool daObjMagmarock::Act_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &mTevStr);
    mr_color_add(&mTevStr, 0.12f);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mBrk.entry(mpModel->getModelData(), (s16)mBrkFrame);
    mBck.entry(mpModel->getModelData(), (s16)mBckFrame);
    mDoExt_modelUpdateDL(mpModel);
    return true;
}

namespace daObjMagmarock {
namespace Method {
/* 000017DC-0000198C       .text Create__Q214daObjMagmarock6MethodFPv */
cPhs_State Create(void* i_this) {
    return ((Act_c*)i_this)->_create();
}

/* 00001A90-00001B14       .text Delete__Q214daObjMagmarock6MethodFPv */
BOOL Delete(void* i_this) {
    return ((Act_c*)i_this)->_delete();
}

/* 00001B14-00001B38       .text Execute__Q214daObjMagmarock6MethodFPv */
BOOL Execute(void* i_this) {
    return ((Act_c*)i_this)->_execute();
}

/* 00001EC0-00002128       .text Draw__Q214daObjMagmarock6MethodFPv */
BOOL Draw(void* i_this) {
    return ((Act_c*)i_this)->_draw();
}

/* 00002128-00002130       .text IsDelete__Q214daObjMagmarock6MethodFPv */
BOOL IsDelete(void*) {
    return TRUE;
}
}; // namespace Method
}; // namespace daObjMagmarock

actor_method_class daObjMagmarock::Method::Table = {
    (process_method_func)daObjMagmarock::Method::Create,
    (process_method_func)daObjMagmarock::Method::Delete,
    (process_method_func)daObjMagmarock::Method::Execute,
    (process_method_func)daObjMagmarock::Method::IsDelete,
    (process_method_func)daObjMagmarock::Method::Draw,
};

actor_process_profile_definition g_profile_Obj_Magmarock = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0003,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Magmarock_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjMagmarock::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Magmarock_e,
    /* Actor SubMtd */ &daObjMagmarock::Method::Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
