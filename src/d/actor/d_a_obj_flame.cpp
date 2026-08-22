//
// d_a_obj_flame.cpp
// Object - Flame jet (Yfire_00)
//

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_flame.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_stage.h"
#include "d/d_particle_name.h"
#include "d/actor/d_a_ykgr.h"
#include "d/actor/d_a_obj_magmarock.h"
#include "d/actor/d_a_mflft.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_actor_iter.h"
#include "m_Do/m_Do_ext.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_math.h"
#include "res/Object/Yfire_00.h"

namespace daObjFlame {

const AttrBase_c Act_c::M_attr_base = {
    6,
    400,
    400,
    200,
    -100,
    1000,
    100,
    270,
    0,
};

const dCcD_SrcCps Act_c::M_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_FIRE,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 30.0f,
    }},
};

const AttrScl_c Act_c::M_attr_scl[4] = {
    {
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        dRes_INDEX_YFIRE_00_BMD_YFIRE_00_e,
        dRes_INDEX_YFIRE_00_BTK_YFIRE_00_e,
        dRes_INDEX_YFIRE_00_BRK_YFIRE_00_e,
        0x52E0,
        1.0f,
        1.0f,
        dPa_name::ID_AK_SN_O_FIRESHAFTFOOT,
        true,
        true,
        {},
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        1.0f,
        -150,
        -1,
        -150,
        150,
        1500,
        150,
        0.7f,
    },
    {
        4.3333335f,
        3.3333334f,
        1.0f,
        0.815f,
        dRes_INDEX_YFIRE_00_BMD_YFIRB_00_e,
        dRes_INDEX_YFIRE_00_BTK_YFIRB_00_e,
        -1,
        0x62A0,
        1.0f,
        0.5f,
        dPa_name::ID_AK_SN_FIRESHAFTFOOTBIG,
        false,
        false,
        {},
        4.3333335f,
        2.7166667f,
        4.3333335f,
        2.7166667f,
        0.8666667f,
        0.54333335f,
        -700,
        -1,
        -700,
        700,
        7500,
        700,
        0.0f,
    },
    {
        7.5f,
        7.5f,
        1.0f,
        1.0f,
        dRes_INDEX_YFIRE_00_BMD_YFIRB_00_e,
        dRes_INDEX_YFIRE_00_BTK_YFIRB_00_e,
        -1,
        0x6760,
        1.0f,
        0.5f,
        dPa_name::ID_AK_SN_FIRESHAFTFOOTBIG,
        false,
        false,
        {},
        7.5f,
        7.5f,
        7.5f,
        7.5f,
        1.0f,
        1.0f,
        -150,
        -1,
        -150,
        150,
        1500,
        150,
        0.0f,
    },
    {
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        dRes_INDEX_YFIRE_00_BMD_YFIRE_00_e,
        dRes_INDEX_YFIRE_00_BTK_YFIRE_00_e,
        dRes_INDEX_YFIRE_00_BRK_YFIRE_00_e,
        0x52E0,
        1.0f,
        1.0f,
        dPa_name::ID_AK_SN_O_FIRESHAFTFOOT,
        false,
        true,
        {},
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        0.5f,
        -75,
        -1,
        -75,
        75,
        750,
        75,
        0.7f,
    },
};

char Act_c::M_arcname[] = "Yfire_00";

/* 00000078-00000110       .text set_switch__Q210daObjFlame5Act_cFv */
void Act_c::set_switch() {
    if (mType == 1) {
        if (mModeProc == MODE_L_U_e || mModeProc == MODE_U_e) {
            fopAcM_onSwitch(this, prm_get_swSave());
        } else {
            fopAcM_offSwitch(this, prm_get_swSave());
        }
    }
}

/* 00000110-00000134       .text solidHeapCB__Q210daObjFlame5Act_cFP10fopAc_ac_c */
BOOL Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

/* 00000134-00000414       .text create_heap__Q210daObjFlame5Act_cFv */
bool Act_c::create_heap() {
    bool success = false;
#if VERSION == VERSION_DEMO
    int model_res = attr_scl().mModelRes;
    J3DModelData* mdl_data = (J3DModelData*)dRes_control_c::getRes(
        M_arcname, model_res, &g_dComIfG_gameInfo.mResControl.mObjectInfo[0], 0x40
    );
#else
    J3DModelData* mdl_data = (J3DModelData*)dRes_control_c::getRes(
        M_arcname, attr_scl().mModelRes, &g_dComIfG_gameInfo.mResControl.mObjectInfo[0], 0x40
    );
#endif
    JUT_ASSERT(DEMO_SELECT(498, 499), mdl_data != 0);
    mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);

#if VERSION == VERSION_DEMO
    int btk_res = attr_scl().mBtkRes;
    J3DAnmTextureSRTKey* btk = (J3DAnmTextureSRTKey*)dRes_control_c::getRes(
        M_arcname, btk_res, &g_dComIfG_gameInfo.mResControl.mObjectInfo[0], 0x40
    );
#else
    J3DAnmTextureSRTKey* btk = (J3DAnmTextureSRTKey*)dRes_control_c::getRes(
        M_arcname, attr_scl().mBtkRes, &g_dComIfG_gameInfo.mResControl.mObjectInfo[0], 0x40
    );
#endif
    mpBtkAnm = new mDoExt_btkAnm();
    int btk_ok = 0;
    JUT_ASSERT(DEMO_SELECT(507, 508), btk != 0);

    if (mpBtkAnm != NULL) {
        btk_ok = mpBtkAnm->init(mdl_data, btk, TRUE, J3DFrameCtrl::EMode_LOOP, attr_scl().mAnmSpeed);
    }

    int brk_ok = 0;
    int brk_res = attr_scl().mBrkRes;
    if (brk_res >= 0) {
        J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dRes_control_c::getRes(
            M_arcname, brk_res, &g_dComIfG_gameInfo.mResControl.mObjectInfo[0], 0x40
        );
        mpBrkAnm = new mDoExt_brkAnm();
        JUT_ASSERT(DEMO_SELECT(529, 530), brk != 0);
        if (mpBrkAnm != NULL) {
            brk_ok = mpBrkAnm->init(mdl_data, brk, TRUE, J3DFrameCtrl::EMode_LOOP, attr_scl().mAnmSpeed);
        }
    } else {
        brk_ok = 1;
    }

    if (mpModel != NULL && btk_ok != 0 && brk_ok != 0) {
        success = true;
    }
    return success;
}

/* 0000045C-000007D8       .text create_mode_init__Q210daObjFlame5Act_cFv */
void Act_c::create_mode_init() {
    u8 sch = prm_get_sch();
    u8 sch_bit = dKy_get_schbit();

    if (sch != 0 && sch_bit != 0) {
        int sch_timer = dKy_get_schbit_timer();
#if VERSION == VERSION_DEMO
        int sch_sec = dStage_stagInfo_GetSchSec(dComIfGp_getStageStagInfo()) * 30;
        int bits;
        int idx;
        int mask;
        bits = sch >= sch_bit ? sch : sch << 8;
        idx = 0;
#else
        u32 bits;
        u32 shifted_sch;
        int sch_sec = dStage_stagInfo_GetSchSec(dComIfGp_getStageStagInfo()) * 30;

        if (sch >= sch_bit) {
            bits = sch;
        } else {
            shifted_sch = sch << 8;
            bits = shifted_sch;
        }
        int idx = 0;
#endif

#if VERSION == VERSION_DEMO
        mask = sch_bit;
#else
        u32 mask = sch_bit;
#endif
        while (!(bits & mask)) {
            mask <<= 1;
            idx++;
        }

#if VERSION == VERSION_DEMO
        int phase_timer = sch_timer + sch_sec * idx;
        f32 phase = (f32)phase_timer * attr_scl().mPhaseScale;
#else
        f32 phase = (f32)(sch_timer + sch_sec * idx) * attr_scl().mPhaseScale;
#endif
        if (mType != 1) {
            phase -= 127.0f;
        }

        if (phase < 0.0f) {
            mModeProc = MODE_WAIT2_e;
            mTimer = 127.0f + phase;
            mHeight = 0.0f;
        } else if (phase < 23.0f) {
            mModeProc = MODE_L_BEFORE_e;
            mTimer = 23.0f - phase;
            mHeight = 0.0f;
        } else if (phase < 45.0f) {
            mModeProc = MODE_L_U_e;
            mTimer = 45.0f - phase;
            mHeight = 0.045454547f * (22.0f - mTimer);
        } else if (phase < 135.0f) {
            mModeProc = MODE_U_e;
            mTimer = 135.0f - phase;
            mHeight = 1.0f;
        } else if (phase < 160.0f) {
            mModeProc = MODE_U_L_e;
            mTimer = 160.0f - phase;
            mHeight = mTimer * 0.04f;
        } else if (phase < 180.0f) {
            mModeProc = MODE_L_AFTER_e;
            mTimer = 180.0f - phase;
            mHeight = 0.0f;
        } else {
            mModeProc = MODE_WAIT_e;
            mTimer = 0.0f;
            mHeight = 0.0f;
        }

        f32 anm_phase = phase * 0.0055555557f;
        if (mModeProc != MODE_WAIT_e && mModeProc != MODE_WAIT2_e) {
            if (mpBtkAnm != NULL) {
                mpBtkAnm->setFrame(1.0f + anm_phase * mpBtkAnm->getEndFrame());
            }
            if (mpBrkAnm != NULL) {
                mpBrkAnm->setFrame(1.0f + anm_phase * mpBrkAnm->getEndFrame());
            }
        }

        if (mModeProc != MODE_WAIT_e) {
            if (mModeProc == MODE_WAIT2_e || mModeProc == MODE_L_BEFORE_e ||
                mModeProc == MODE_L_U_e || mModeProc == MODE_U_e)
            {
                mEm0State = 1;
            }
            if (mModeProc == MODE_WAIT2_e || mModeProc == MODE_L_BEFORE_e ||
                mModeProc == MODE_L_U_e || mModeProc == MODE_U_e || mModeProc == MODE_U_L_e)
            {
                mEm1State = 1;
                mEm2State = 1;
            }
            if (attr_scl().mEmSimple == 0) {
                em_manual_set();
            }
            mEmPosOn = 1;
        }
    } else {
        mModeProc = MODE_WAIT_e;
        if (sch != 0) {
            mTimer = 0.0f;
        } else {
            mTimer = 120.0f;
        }
        mHeight = 0.0f;
    }
}

/* 000007D8-00000930       .text set_mtx__Q210daObjFlame5Act_cFv */
void Act_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_stack_c::YrotM(mRotY);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

    fopAcM_setCullSizeBox(this, attr_scl().mCullMinX, attr_scl().mCullMinY, attr_scl().mCullMinZ,
                          attr_scl().mCullMaxX, mHeight * attr_scl().mCullMaxY, attr_scl().mCullMaxZ);
}

/* 00000930-00000950       .text init_mtx__Q210daObjFlame5Act_cFv */
void Act_c::init_mtx() {
    set_mtx();
}

/* 00000950-00000B3C       .text em_position__Q210daObjFlame5Act_cFv */
void Act_c::em_position() {
    if (mEmPosOn != 0) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle);

        if (attr_scl().mEmSimple == 0) {
            if (mpEmitter0 != NULL) {
                mDoMtx_stack_c::push();
                mDoMtx_stack_c::transM(0.0f, 1500.0f * mHeight * attr_scl().mScaleY * mExtraScaleY +
                                                 -300.0f * attr_scl().mScaleY * mExtraScaleY,
                                       0.0f);
                mpEmitter0->setGlobalRTMatrix(mDoMtx_stack_c::get());
                mDoMtx_stack_c::pop();
            }
            if (mpEmitter1 != NULL) {
                mpEmitter1->setGlobalRTMatrix(mDoMtx_stack_c::get());
            }
        }

        mDoMtx_stack_c::transM(0.0f, 1500.0f * mHeight * attr_scl().mHeightScale * mSpread, 0.0f);
        PSMTXMultVec(mDoMtx_stack_c::get(), &cXyz::Zero, &eyePos);

        mCpsOn = (1500.0f * mHeight - 300.0f) > 0.0f;
        if (mCpsOn) {
            mDoMtx_stack_c::transM(0.0f, mSpread * (-300.0f * attr_scl().mHeightScale), 0.0f);
            PSMTXMultVec(mDoMtx_stack_c::get(), &cXyz::Zero, &mCpsP1);
        }
    }
}

/* 00000B3C-00000CAC       .text em_simple_set__Q210daObjFlame5Act_cFv */
void Act_c::em_simple_set() {
#if VERSION == VERSION_DEMO
    bool once_done = false;
    if (attr_scl().mEmOnce != 0 && mEmOnceDone != 0) {
        once_done = true;
    }
    bool emit = !once_done;
#else
    bool emit = false;
    if (attr_scl().mEmOnce == 0 || mEmOnceDone == 0) {
        emit = true;
    }
#endif

    if (mEm0State == 1 && emit) {
        cXyz pos(eyePos.x, eyePos.y + mExtraScaleY * (-300.0f * attr_scl().mHeightScale), eyePos.z);
        dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_FIRESHAFTHEAD | 0x10000, &pos);
    }
    if (mEm1State == 1) {
        dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_FIRESHAFTBODY | 0x10000, &eyePos);
    }
    if (mEm2State == 1 && emit) {
        dComIfGp_particle_setSimple((u16)attr_scl().mEm2Id, &home.pos);
    }
}

/* 00000CAC-00000CEC       .text em_simple_inv__Q210daObjFlame5Act_cFv */
void Act_c::em_simple_inv() {
    if (mEm0State == 3) {
        mpEmitter0 = NULL;
    }
    if (mEm1State == 3) {
        mpEmitter1 = NULL;
    }
    if (mEm2State == 3) {
        mpEmitter2 = NULL;
    }
}

/* 00000CEC-00000F04       .text em_manual_set__Q210daObjFlame5Act_cFv */
void Act_c::em_manual_set() {
#if VERSION == VERSION_DEMO
    bool once_done = false;
    int type = mType;
    const AttrScl_c& attr = M_attr_scl[type];
#else
    bool emit = false;
    const AttrScl_c& attr = M_attr_scl[mType];
#endif
#if VERSION == VERSION_DEMO
    if (attr.mEmOnce != 0 && mEmOnceDone != 0) {
        once_done = true;
    }
    bool emit = !once_done;
#else
    if (attr.mEmOnce == 0 || mEmOnceDone == 0) {
        emit = true;
    }
#endif

    if (mEm0State == 1 && emit &&
#if VERSION == VERSION_DEMO
        type != 1
#else
        mType != 1
#endif
    ) {
        cXyz scale(attr.mEm0ScaleXZ, mExtraScaleY * attr.mEm0ScaleY, attr.mEm0ScaleXZ);
        mpEmitter0 = dComIfGp_particle_set(dPa_name::ID_AK_SN_O_FIRESHAFTHEAD | 0x10000, &home.pos,
                                           &home.angle, &scale);
        mEm0State = 2;
    }
    if (mEm1State == 1) {
        cXyz scale(attr_scl().mEm1ScaleXZ, mExtraScaleY * attr_scl().mEm1ScaleY, attr_scl().mEm1ScaleXZ);
        mpEmitter1 = dComIfGp_particle_set(dPa_name::ID_AK_SN_O_FIRESHAFTBODY | 0x10000, &home.pos,
                                           &home.angle, &scale);
        mEm1State = 2;
    }
    if (mEm2State == 1 && emit) {
        cXyz scale(attr_scl().mEm2Scale, attr_scl().mEm2Scale, attr_scl().mEm2Scale);
        mpEmitter2 = dComIfGp_particle_set((u16)attr_scl().mEm2Id, &home.pos, &home.angle,
                                           &scale);
        mEm2State = 2;
    }
}

/* 00000F04-00001010       .text em_manual_inv__Q210daObjFlame5Act_cFv */
void Act_c::em_manual_inv() {
    bool once_done = attr_scl().mEmOnce != 0 && mEmOnceDone != 0;

    if (mEm0State == 2 && once_done) {
        mEm0State = 3;
    }
    if (mEm2State == 2 && once_done) {
        mEm2State = 3;
    }

    if (mEm0State == 3) {
        if (mpEmitter0 != NULL) {
            mpEmitter0->becomeInvalidEmitter();
            mpEmitter0 = NULL;
        }
    }
    if (mEm1State == 3) {
        if (mpEmitter1 != NULL) {
            mpEmitter1->becomeInvalidEmitter();
            mpEmitter1 = NULL;
        }
    }
    if (mEm2State == 3) {
        if (mpEmitter2 != NULL) {
            mpEmitter2->becomeInvalidEmitter();
            mpEmitter2 = NULL;
        }
    }
}

/* 00001010-00001070       .text ki_init__Q210daObjFlame5Act_cFv */
void Act_c::ki_init() {
    int num = prm_get_kiNum() + 1;
    if ((num == 32 ? 0 : num) > 0) {
        mKiIntervalTmr = 0;
        mKiCount = 0;
        mKiActive = 1;
    }
}

/* 00001070-00001194       .text ki_make__Q210daObjFlame5Act_cFv */
void Act_c::ki_make() {
    if (mKiActive != 0) {
        if (mKiCycleTmr <= 0) {
            int num = prm_get_kiNum() + 1;
            if (mKiCount < (num == 32 ? 0 : num)) {
                if (--mKiIntervalTmr <= 0) {
                    mKiIntervalTmr = M_attr_base.mKiInterval - 1;
                    mKiCount++;
                    csXyz angle(0, (s16)cM_rndFX(32768.0f), 0);
                    fopAcM_create(fpcNm_KI_e, 0xFFFF8002, &current.pos, fopAcM_GetRoomNo(this),
                                  &angle, NULL, -1, NULL);
                }
            } else {
                mKiActive = 0;
                mKiCycleTmr = prm_get_kiCycle();
            }
        } else {
            mKiActive = 0;
            mKiCycleTmr--;
        }
    }
}

/* 00001194-000011E4       .text eff_hase__Q210daObjFlame5Act_cFv */
void Act_c::eff_hase() {
    dComIfGp_particle_setSimple(dPa_name::ID_AK_SP_O_FIREHOLEKAGEROU | 0x10000, &home.pos);
}

/* 000011E4-00001254       .text se_fireblast_omen__Q210daObjFlame5Act_cFv */
void Act_c::se_fireblast_omen() {
    JAIZelBasic::zel_basic->seStart(0x704E, &current.pos, 0,
                                    dComIfGp_getReverb(fopAcM_GetRoomNo(this)), 1.0f, 1.0f, -1.0f,
                                    -1.0f, 0);
}

/* 00001254-00001610       .text liftup_magmarock__Q210daObjFlame5Act_cFPvPv */
void* Act_c::liftup_magmarock(void* i_actor, void* i_this) {
    Act_c* flame = (Act_c*)i_this;
    fopAc_ac_c* actor = (fopAc_ac_c*)i_actor;

    if (fopAc_IsActor(actor) && fpcM_GetName(actor) == fpcNm_Obj_Magmarock_e &&
        !fpcM_IsCreating(fopAcM_GetID(actor)))
    {
        f32 size_scale = 145.0f * flame->attr_scl().mSizeScale;
        f32 near_y = size_scale + M_attr_base.mLiftupYOfs;

        bool eye_below = flame->eyePos.y < flame->current.pos.y;
        f32 sel_lo;
        if (eye_below) {
            sel_lo = flame->eyePos.y;
        } else {
            sel_lo = flame->current.pos.y;
        }
        f32 y_lo = sel_lo + M_attr_base.mLiftupYMin;
        f32 sel_hi;
        if (eye_below) {
            sel_hi = flame->current.pos.y;
        } else {
            sel_hi = flame->eyePos.y;
        }
        f32 y_hi = sel_hi + M_attr_base.mLiftupYMax;

        cXyz pos;
        cXyz flame_xz;
        cXyz actor_xz;
        actor_xz.set(actor->current.pos.x, 0.0f, actor->current.pos.z);
        flame_xz.set(flame->eyePos.x, 0.0f, flame->eyePos.z);
        f32 dist = std::sqrtf(actor_xz.getSquareDistance(flame_xz));

        if (dist < near_y && actor->current.pos.y > y_lo && actor->current.pos.y < y_hi) {
            daObjMagmarock::Act_c* magmarock = (daObjMagmarock::Act_c*)actor;
            if (flame->mType != 1) {
                f32 lift_base;
                f32 lift_peak;
                if (flame->mHeight < 0.1f) {
                    lift_base = M_attr_base.mLiftupBase;
                    lift_peak = flame->mHeight * (10.0f * M_attr_base.mLiftupPeak);
                } else if (flame->mHeight > 0.9f) {
                    lift_base = (1.0f - flame->mHeight) * (10.0f * M_attr_base.mLiftupBase);
                    lift_peak = (1.0f - flame->mHeight) * (10.0f * M_attr_base.mLiftupPeak);
                } else {
                    lift_base = M_attr_base.mLiftupBase;
                    lift_peak = M_attr_base.mLiftupPeak;
                }

                f32 scale = flame->mSpread * flame->attr_scl().mHeightScale;
                lift_base *= scale;
                lift_peak *= scale;

                pos.set(flame->eyePos.x, lift_peak + (flame->eyePos.y + lift_base), flame->eyePos.z);
                if (flame->mModeProc == MODE_WAIT2_e || flame->mModeProc == MODE_L_BEFORE_e) {
                    magmarock->BeforeLiftRequest(pos);
                } else {
                    magmarock->LiftUpRequest(pos);
                }
                flame->mEmOnceDone = 1;
            }
        }
    }
    return NULL;
}

/* 00001610-00001884       .text liftup_mflft__Q210daObjFlame5Act_cFPvPv */
void* Act_c::liftup_mflft(void* i_actor, void* i_this) {
    Act_c* flame = (Act_c*)i_this;
    fopAc_ac_c* actor = (fopAc_ac_c*)i_actor;

    if (fopAc_IsActor(actor) && fpcM_GetName(actor) == fpcNm_MFLFT_e) {
        mflft_class* mflft = (mflft_class*)actor;
        f32 target_spread;
        f32 target_scale_y;
        f32 y_max;
        if (mflft->m29A == 0) {
            target_spread = 1.0f;
            target_scale_y = 1.0004418f;
            y_max = 5000.0f;
        } else {
            target_spread = 1.0f;
            target_scale_y = 1.0f;
            y_max = 5000.0f;
        }

        f32 lift_base;
        f32 lift_peak;
        if (flame->mHeight < 0.1f) {
            lift_base = M_attr_base.mLiftupBase;
            lift_peak = flame->mHeight * (10.0f * M_attr_base.mLiftupPeak);
        } else if (flame->mHeight > 0.9f) {
            lift_base = (1.0f - flame->mHeight) * (10.0f * M_attr_base.mLiftupBase);
            lift_peak = (1.0f - flame->mHeight) * (10.0f * M_attr_base.mLiftupPeak);
        } else {
            lift_base = M_attr_base.mLiftupBase;
            lift_peak = M_attr_base.mLiftupPeak;
        }

        f32 scale = flame->mSpread * flame->attr_scl().mHeightScale;
        lift_base *= scale;
        lift_peak *= scale;

        cXyz pos(flame->eyePos.x, lift_peak + (flame->eyePos.y + lift_base), flame->eyePos.z);
        f32 limit_y = flame->current.pos.y + y_max;
        if (pos.y > limit_y) {
            pos.y = limit_y;
        }

        if (flame->mModeProc != MODE_WAIT2_e && flame->mModeProc != MODE_L_BEFORE_e) {
            mflft->setLiftUp(pos);
        }

        flame->mEmOnceDone = 1;
        cLib_addCalc(&flame->mSpread, target_spread, 0.3f, 0.1f, 0.01f);
        cLib_addCalc(&flame->mExtraScaleY, target_scale_y, 0.3f, 0.1f, 0.01f);
    }
    return NULL;
}

/* 00001884-00001988       .text mode_wait__Q210daObjFlame5Act_cFv */
void Act_c::mode_wait() {
    u8 sch = prm_get_sch();
    bool trigger = false;
    if (sch != 0) {
        if ((sch & dKy_get_schbit()) != 0 && dKy_get_schbit_timer() == 0) {
            trigger = true;
        }
    } else {
        if (mTimer <= 0.0f) {
            trigger = true;
        }
    }

    if (trigger) {
        if (mType == 1) {
            mpBtkAnm->setFrame(0.0f);
            if (mpBrkAnm != NULL) {
                mpBrkAnm->setFrame(0.0f);
            }
            mModeProc = MODE_L_BEFORE_e;
            mTimer = 23.0f;
            ki_init();
        } else {
            mModeProc = MODE_WAIT2_e;
            mTimer = 127.0f;
        }
        mEm0State = 1;
        mEm1State = 1;
        mEm2State = 1;
        mEmPosOn = 1;
    }
}

/* 00001988-00001A08       .text mode_wait2__Q210daObjFlame5Act_cFv */
void Act_c::mode_wait2() {
    se_fireblast_omen();
    if (mTimer <= 0.0f) {
        mpBtkAnm->setFrame(0.0f);
        if (mpBrkAnm != NULL) {
            mpBrkAnm->setFrame(0.0f);
        }
        mModeProc = MODE_L_BEFORE_e;
        mTimer = 23.0f;
        ki_init();
    }
}

/* 00001A08-00001A98       .text mode_l_before__Q210daObjFlame5Act_cFv */
void Act_c::mode_l_before() {
    mEmPosOn = 0;
    if (mTimer <= 0.0f) {
        mModeProc = MODE_L_U_e;
        mTimer = 22.0f;
#if VERSION == VERSION_DEMO
        s8 reverb = mReverb;
        JAIZelBasic::zel_basic->seStart(0x380D, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
#else
        JAIZelBasic::zel_basic->seStart(0x380D, &eyePos, 0, mReverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
#endif
    } else {
        se_fireblast_omen();
    }
}

/* 00001A98-00001AE8       .text mode_l_u__Q210daObjFlame5Act_cFv */
void Act_c::mode_l_u() {
    mHeight = 0.045454547f * (22.0f - mTimer);
    mEmPosOn = 1;
    if (mTimer <= 0.0f) {
        mModeProc = MODE_U_e;
        mTimer = 90.0f;
    }
}

/* 00001AE8-00001B20       .text mode_u__Q210daObjFlame5Act_cFv */
void Act_c::mode_u() {
    if (mTimer <= 0.0f) {
        mModeProc = MODE_U_L_e;
        mTimer = 25.0f;
        mEm0State = 3;
    }
}

/* 00001B20-00001B74       .text mode_u_l__Q210daObjFlame5Act_cFv */
void Act_c::mode_u_l() {
    mHeight = mTimer * 0.04f;
    mEmPosOn = 1;
    if (mTimer <= 0.0f) {
        mModeProc = MODE_L_AFTER_e;
        mTimer = 20.0f;
        mEm1State = 3;
        mEm2State = 3;
    }
}

/* 00001B74-00001BEC       .text mode_l_after__Q210daObjFlame5Act_cFv */
void Act_c::mode_l_after() {
    if (mTimer <= 0.0f) {
        mModeProc = MODE_WAIT_e;
        if (prm_get_sch() != 0) {
            mTimer = 0.0f;
        } else {
            mTimer = 120.0f;
        }
    }
}

/* 00001BEC-00001EAC       .text mode_proc_call__Q210daObjFlame5Act_cFv */
void Act_c::mode_proc_call() {
    static void (Act_c::*mode_proc[])() = {
        &Act_c::mode_wait,
        &Act_c::mode_wait2,
        &Act_c::mode_l_before,
        &Act_c::mode_l_u,
        &Act_c::mode_u,
        &Act_c::mode_u_l,
        &Act_c::mode_l_after,
    };

    if (mTimer >= -0.1f) {
        if (mModeProc == MODE_WAIT_e || mModeProc == MODE_WAIT2_e) {
            mTimer -= 1.0f;
        } else {
            mTimer -= attr_scl().mPhaseScale;
        }
    }

    (this->*mode_proc[mModeProc])();

    if (attr_scl().mEmSimple != 0) {
        em_position();
        em_simple_set();
        em_simple_inv();
    } else {
        em_manual_set();
        em_manual_inv();
        em_position();
    }

    if (mModeProc != MODE_WAIT_e && mModeProc != MODE_WAIT2_e) {
        mpBtkAnm->play();
        if (mpBrkAnm != NULL) {
            mpBrkAnm->play();
        }
#if VERSION == VERSION_DEMO
        s8 reverb = mReverb;
        JAIZelBasic::zel_basic->seStart(0x7009, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
#else
        JAIZelBasic::zel_basic->seStart(0x7009, &eyePos, 0, mReverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
#endif
    }

    if (mCpsOn) {
        bool cps_ok;
        if (mModeProc == MODE_U_L_e) {
            cps_ok = mHeight > attr_scl().mCpsOnHeight;
        } else {
            cps_ok = true;
        }
        if (cps_ok) {
            mCps.SetStartEnd(mCpsP0, mCpsP1);
            mCps.SetR(mCpsRad);
            dComIfG_Ccsp()->Set(&mCps);
        }
    }
}

}  // namespace daObjFlame

/* 00001EAC-00001ECC       .text Create__Q210daObjFlame6MethodFPv */
cPhs_State daObjFlame::Method::Create(void* i_this) {
    return ((Act_c*)i_this)->_create();
}

namespace daObjFlame {

/* 00001ECC-00002200       .text _create__Q210daObjFlame5Act_cFv */
inline cPhs_State Act_c::_create() {
    fopAcM_ct(this, Act_c);

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);
    if (phase_state == cPhs_COMPLEATE_e) {
        mType = prm_get_type();

        if (fopAcM_entrySolidHeap(this, &Act_c::solidHeapCB, attr_scl().mHeapSize)) {
            mOrigScale = scale;

            if (mType == 1) {
                mSpread = 1.0f;
                mExtraScaleY = 1.0004418f;
            } else {
                mSpread = 1.0f;
                mExtraScaleY = 1.0f;
            }

            scale.x = scale.x * attr_scl().mScaleXZ;
            scale.y *= mExtraScaleY * attr_scl().mScaleY;
            scale.z = scale.z * attr_scl().mScaleXZ;

            mEm0State = 0;
            mEm1State = 0;
            mEm2State = 0;
            create_mode_init();
            set_switch();

            cullMtx = mpModel->getBaseTRMtx();
            init_mtx();

            mStts.Init(100, 0xFF, this);
            mCps.Set(M_cps_src);
            mCps.SetStts(&mStts);

            mCpsP0 = current.pos;
            mCpsP1 = current.pos;
            mCpsRad = 145.0f * attr_scl().mSizeScale;
            mCpsOn = false;
            em_position();

#if VERSION == VERSION_DEMO
            mReverb = dComIfGp_getReverb(home.roomNo);
#else
            mReverb = dComIfGp_getReverb(fopAcM_GetHomeRoomNo(this));
#endif
            mEmOnceDone = 0;

            mKiCycleTmr = (int)cM_rndF((f32)(prm_get_kiCycle() + 1));
            if (mModeProc != MODE_WAIT_e && mKiCycleTmr == 0) {
                mKiCycleTmr = 1;
            }
        } else {
            phase_state = cPhs_ERROR_e;
        }
    }
    return phase_state;
}

/* 00002484-000024B4       .text Delete__Q210daObjFlame6MethodFPv */
inline bool Act_c::_delete() {
#if VERSION == VERSION_DEMO
    dRes_control_c::deleteRes(M_arcname, &g_dComIfG_gameInfo.mResControl.mObjectInfo[0], 0x40);
#else
    dComIfG_resDelete(&mPhs, M_arcname);
#endif
    return true;
}

BOOL Method::Delete(void* i_this) {
    return ((Act_c*)i_this)->_delete();
}

/* 000024B4-00002638       .text Execute__Q210daObjFlame6MethodFPv */
inline bool Act_c::_execute() {
    scale.x = mOrigScale.x * attr_scl().mScaleXZ;
    scale.y = mOrigScale.y * attr_scl().mScaleY * mExtraScaleY;
    scale.z = mOrigScale.z * attr_scl().mScaleXZ;

    mode_proc_call();
    ki_make();

    if (prm_get_haze() == 0) {
        eff_hase();
    }

    if (mType == 1) {
        mRotY += M_attr_base.mRotSpdA;
        if (mHeight > 0.01f) {
            daYkgr_c::m_aim_rate = 1.0f;
        }
    } else {
        mRotY += M_attr_base.mRotSpdB;
    }

    mEmOnceDone = 0;
    if (mModeProc == MODE_WAIT2_e || mModeProc == MODE_L_BEFORE_e ||
        mModeProc == MODE_L_U_e || mModeProc == MODE_U_e)
    {
        fopAcIt_Judge((fopAcIt_JudgeFunc)liftup_magmarock, this);
        if (mType == 1) {
            fopAcIt_Judge((fopAcIt_JudgeFunc)liftup_mflft, this);
        }
    }

    set_switch();
    set_mtx();
    return true;
}

BOOL Method::Execute(void* i_this) {
    return ((Act_c*)i_this)->_execute();
}

/* 00002638-00002710       .text Draw__Q210daObjFlame6MethodFPv */
inline bool Act_c::_draw() {
    g_env_light.settingTevStruct(0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    mpBtkAnm->entry(mpModel->getModelData());
    if (mpBrkAnm != NULL) {
        mpBrkAnm->entry(mpModel->getModelData());
    }

    J3DDrawBuffer* draw_buffer = dComIfGd_getListFilter();
    j3dSys.setDrawBuffer(draw_buffer, 0);
    j3dSys.setDrawBuffer(draw_buffer, 1);
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return true;
}

BOOL Method::Draw(void* i_this) {
    return ((Act_c*)i_this)->_draw();
}

/* 00002710-000027B0       .text IsDelete__Q210daObjFlame6MethodFPv */
BOOL Method::IsDelete(void* i_this) {
    Act_c* flame = (Act_c*)i_this;
    if (flame->attr_scl().mEmSimple == 0) {
        if (flame->mpEmitter0 != NULL) {
            flame->mpEmitter0->becomeInvalidEmitter();
            flame->mpEmitter0 = NULL;
        }
        if (flame->mpEmitter1 != NULL) {
            flame->mpEmitter1->becomeInvalidEmitter();
            flame->mpEmitter1 = NULL;
        }
        if (flame->mpEmitter2 != NULL) {
            flame->mpEmitter2->becomeInvalidEmitter();
            flame->mpEmitter2 = NULL;
        }
    }
    return TRUE;
}

actor_method_class Method::Table = {
    (process_method_func)daObjFlame::Method::Create,
    (process_method_func)daObjFlame::Method::Delete,
    (process_method_func)daObjFlame::Method::Execute,
    (process_method_func)daObjFlame::Method::IsDelete,
    (process_method_func)daObjFlame::Method::Draw,
};

}  // namespace daObjFlame

actor_process_profile_definition g_profile_Obj_Flame = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Flame_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjFlame::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Flame_e,
    /* Actor SubMtd */ &daObjFlame::Method::Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
