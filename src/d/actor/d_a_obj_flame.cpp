/**
 * d_a_obj_flame.cpp
 * Object - Flame pillar
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_flame.h"
#include "d/actor/d_a_obj_magmarock.h"
#include "d/actor/d_a_mflft.h"
#include "d/actor/d_a_ykgr.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_stage.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_actor_iter.h"
#include "m_Do/m_Do_mtx.h"
#include "m_Do/m_Do_audio.h"
#include "JSystem/JParticle/JPAEmitter.h"

const daObjFlame::AttrBase_c daObjFlame::Act_c::M_attr_base = {
    /* mKiInterval */ 6,
    /* mRotSpd1    */ 400,
    /* mRotSpd0    */ 400,
    /* mLiftR      */ 200,
    /* mLiftYMin   */ -100,
    /* mLiftYMax   */ 1000,
    /* mLiftOfs0   */ 100,
    /* mLiftOfs1   */ 270,
};

const dCcD_SrcCps daObjFlame::Act_c::M_cps_src = {
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
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
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

const daObjFlame::AttrScl_c daObjFlame::Act_c::M_attr_scl[] = {
    {
        1.0f, 1.0f, 1.0f, 1.0f,
        6, 13, 9, 0x52E0,
        1.0f, 1.0f, 0x805C, 1, 1,
        1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
        -150, -1, -150, 150, 1500, 150,
        0.7f,
    },
    {
        4.3333335f, 3.3333335f, 1.0f, 0.815f,
        5, 12, -1, 0x62A0,
        1.0f, 0.5f, 0x808A, 0, 0,
        4.3333335f, 2.7166667f, 4.3333335f, 2.7166667f, 0.8666667f, 0.54333335f,
        -700, -1, -700, 700, 7500, 700,
        0.0f,
    },
    {
        7.5f, 7.5f, 1.0f, 1.0f,
        5, 12, -1, 0x6760,
        1.0f, 0.5f, 0x808A, 0, 0,
        7.5f, 7.5f, 7.5f, 7.5f, 1.0f, 1.0f,
        -150, -1, -150, 150, 1500, 150,
        0.0f,
    },
    {
        0.5f, 0.5f, 0.5f, 0.5f,
        6, 13, 9, 0x52E0,
        1.0f, 1.0f, 0x805C, 0, 1,
        0.5f, 0.5f, 0.5f, 0.5f, 0.5f, 0.5f,
        -75, -1, -75, 75, 750, 75,
        0.7f,
    },
};

char daObjFlame::Act_c::M_arcname[] = "Yfire_00";

/* 00000078-00000110       .text set_switch__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::set_switch() {
    if (mType == 1) {
        if (mModeProc == 3 || mModeProc == 4) {
            fopAcM_onSwitch(this, prm_get_swSave());
        } else {
            fopAcM_offSwitch(this, prm_get_swSave());
        }
    }
}

/* 00000110-00000134       .text solidHeapCB__Q210daObjFlame5Act_cFP10fopAc_ac_c */
BOOL daObjFlame::Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

/* 00000134-00000414       .text create_heap__Q210daObjFlame5Act_cFv */
bool daObjFlame::Act_c::create_heap() {
    bool ret = false;
    J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, attr_scl().mMdlIdx);
    JUT_ASSERT(0x1F3, mdl_data != 0);
    mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11020203);

    J3DAnmTextureSRTKey* btk = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes(M_arcname, attr_scl().mBtkIdx);
    mpBtkAnm = new mDoExt_btkAnm();
    BOOL btk_ret = FALSE;
    JUT_ASSERT(0x1FC, btk != 0);
    if (mpBtkAnm != NULL) {
        btk_ret = mpBtkAnm->init(mdl_data, btk, TRUE, J3DFrameCtrl::EMode_LOOP, attr_scl().mAnmRate, 0, -1, false, 0);
    }

    int brk_ret = 0;
    if (attr_scl().mBrkIdx >= 0) {
        J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, attr_scl().mBrkIdx);
        mpBrkAnm = new mDoExt_brkAnm();
        JUT_ASSERT(0x212, brk != 0);
        if (mpBrkAnm != NULL) {
            brk_ret = mpBrkAnm->init(mdl_data, brk, TRUE, J3DFrameCtrl::EMode_LOOP, attr_scl().mAnmRate, 0, -1, false, 0);
        }
    } else {
        brk_ret = 1;
    }

    if (mpModel != NULL && btk_ret && brk_ret) {
        ret = true;
    }
    return ret;
}

/* 0000045C-000007D8       .text create_mode_init__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::create_mode_init() {
    u8 sch = prm_get_sch();
    u8 schbit = dKy_get_schbit();
    if (sch != 0 && schbit != 0) {
        int timer = dKy_get_schbit_timer();
        int interval = dStage_stagInfo_GetSchSec(dComIfGp_getStageStagInfo()) * 30;
        u32 bits = sch >= schbit ? sch : sch << 8;
        int n = 0;
        int bit = schbit;
        while (!(bits & bit)) {
            bit <<= 1;
            n++;
        }
        f32 time = (timer + interval * n) * attr_scl().mTimerRate;
        if (mType != 1) {
            time -= 127.0f;
        }
        if (time < 0.0f) {
            mModeProc = 1;
            mTimer = 127.0f + time;
            mHeight = 0.0f;
        } else if (time < 23.0f) {
            mModeProc = 2;
            mTimer = 23.0f - time;
            mHeight = 0.0f;
        } else if (time < 45.0f) {
            mModeProc = 3;
            mTimer = 45.0f - time;
            mHeight = (1.0f / 22.0f) * (22.0f - mTimer);
        } else if (time < 135.0f) {
            mModeProc = 4;
            mTimer = 135.0f - time;
            mHeight = 1.0f;
        } else if (time < 160.0f) {
            mModeProc = 5;
            mTimer = 160.0f - time;
            mHeight = (1.0f / 25.0f) * mTimer;
        } else if (time < 180.0f) {
            mModeProc = 6;
            mTimer = 180.0f - time;
            mHeight = 0.0f;
        } else {
            mModeProc = 0;
            mTimer = 0.0f;
            mHeight = 0.0f;
        }
        f32 rate = (1.0f / 180.0f) * time;
        if (mModeProc != 0 && mModeProc != 1) {
            if (mpBtkAnm != NULL) {
                mpBtkAnm->setFrame(1.0f + rate * mpBtkAnm->getEndFrame());
            }
            if (mpBrkAnm != NULL) {
                mpBrkAnm->setFrame(1.0f + rate * mpBrkAnm->getEndFrame());
            }
        }
        if (mModeProc != 0) {
            if (mModeProc == 1 || mModeProc == 2 || mModeProc == 3 || mModeProc == 4) {
                mEm0State = 1;
            }
            if (mModeProc == 1 || mModeProc == 2 || mModeProc == 3 || mModeProc == 4 || mModeProc == 5) {
                mEm1State = 1;
                mEm2State = 1;
            }
            if (!attr_scl().mSimpleEmitter) {
                em_manual_set();
            }
            m457 = 1;
        }
    } else {
        mModeProc = 0;
        if (sch != 0) {
            mTimer = 0.0f;
        } else {
            mTimer = 120.0f;
        }
        mHeight = 0.0f;
    }
}

/* 000007D8-00000930       .text set_mtx__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::set_mtx() {
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_stack_c::YrotM(mRotY);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    const AttrScl_c& attr = attr_scl();
    fopAcM_setCullSizeBox(this, attr.mCullMinX, attr.mCullMinY, attr.mCullMinZ, attr.mCullMaxX, mHeight * attr.mCullMaxY, attr.mCullMaxZ);
}

/* 00000930-00000950       .text init_mtx__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::init_mtx() {
    set_mtx();
}

/* 00000950-00000B3C       .text em_position__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::em_position() {
    if (m457) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle);
        if (!attr_scl().mSimpleEmitter) {
            if (mpEmitter0 != NULL) {
                mDoMtx_stack_c::push();
                mDoMtx_stack_c::transM(0.0f, mExtraScaleY * (1500.0f * mHeight * attr_scl().mScaleY) + mExtraScaleY * (-300.0f * attr_scl().mScaleY), 0.0f);
                mpEmitter0->setGlobalRTMatrix(mDoMtx_stack_c::get());
                mDoMtx_stack_c::pop();
            }
            if (mpEmitter1 != NULL) {
                mpEmitter1->setGlobalRTMatrix(mDoMtx_stack_c::get());
            }
        }
        mDoMtx_stack_c::transM(0.0f, m46C * (1500.0f * mHeight * attr_scl().mHeightScale), 0.0f);
        mDoMtx_stack_c::multVec(&cXyz::Zero, &eyePos);
        m434 = (1500.0f * mHeight - 300.0f) > 0.0f;
        if (m434) {
            mDoMtx_stack_c::transM(0.0f, m46C * (-300.0f * attr_scl().mHeightScale), 0.0f);
            mDoMtx_stack_c::multVec(&cXyz::Zero, &mCpsP1);
        }
    }
}

/* 00000B3C-00000CAC       .text em_simple_set__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::em_simple_set() {
    bool set = false;
    const AttrScl_c& attr = attr_scl();
    if (!attr.mChkLift || !m459) {
        set = true;
    }
    if ((int)mEm0State == 1 && set) {
        cXyz pos(eyePos.x, eyePos.y + mExtraScaleY * (-300.0f * attr.mHeightScale), eyePos.z);
        dComIfGp_particle_setSimple(0x805A, &pos);
    }
    if ((int)mEm1State == 1) {
        dComIfGp_particle_setSimple(0x805B, &eyePos);
    }
    if ((int)mEm2State == 1 && set) {
        dComIfGp_particle_setSimple(attr_scl().mEmitterId, &home.pos);
    }
}

/* 00000CAC-00000CEC       .text em_simple_inv__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::em_simple_inv() {
    if ((int)mEm0State == 3) {
        mpEmitter0 = NULL;
    }
    if ((int)mEm1State == 3) {
        mpEmitter1 = NULL;
    }
    if ((int)mEm2State == 3) {
        mpEmitter2 = NULL;
    }
}

/* 00000CEC-00000F04       .text em_manual_set__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::em_manual_set() {
    bool set = false;
    const AttrScl_c& attr = attr_scl();
    if (!attr.mChkLift || !m459) {
        set = true;
    }
    if ((int)mEm0State == 1 && set && mType != 1) {
        cXyz scl(attr.mEm0ScaleXZ, mExtraScaleY * attr.mEm0ScaleY, attr.mEm0ScaleXZ);
        mpEmitter0 = dComIfGp_particle_set(0x805A, &home.pos, &home.angle, &scl);
        mEm0State = 2;
    }
    if ((int)mEm1State == 1) {
        const AttrScl_c& attr2 = attr_scl();
        cXyz scl(attr2.mEm1ScaleXZ, mExtraScaleY * attr2.mEm1ScaleY, attr2.mEm1ScaleXZ);
        mpEmitter1 = dComIfGp_particle_set(0x805B, &home.pos, &home.angle, &scl);
        mEm1State = 2;
    }
    if ((int)mEm2State == 1 && set) {
        f32 s = attr_scl().mEm2Scale;
        cXyz scl(s, s, s);
        mpEmitter2 = dComIfGp_particle_set(attr_scl().mEmitterId, &home.pos, &home.angle, &scl);
        mEm2State = 2;
    }
}

/* 00000F04-00001010       .text em_manual_inv__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::em_manual_inv() {
    bool inv = false;
    if (attr_scl().mChkLift && m459) {
        inv = true;
    }
    if ((int)mEm0State == 2 && inv) {
        mEm0State = 3;
    }
    if ((int)mEm2State == 2 && inv) {
        mEm2State = 3;
    }
    if ((int)mEm0State == 3) {
        if (mpEmitter0 != NULL) {
            mpEmitter0->becomeInvalidEmitter();
            mpEmitter0 = NULL;
        }
    }
    if ((int)mEm1State == 3) {
        if (mpEmitter1 != NULL) {
            mpEmitter1->becomeInvalidEmitter();
            mpEmitter1 = NULL;
        }
    }
    if ((int)mEm2State == 3) {
        if (mpEmitter2 != NULL) {
            mpEmitter2->becomeInvalidEmitter();
            mpEmitter2 = NULL;
        }
    }
}

/* 00001010-00001070       .text ki_init__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::ki_init() {
    if (prm_get_kiNum() > 0) {
        m460 = 0;
        m464 = 0;
        m45A = 1;
    }
}

/* 00001070-00001194       .text ki_make__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::ki_make() {
    if (m45A) {
        if (m45C <= 0) {
            if (m464 < prm_get_kiNum()) {
                if (--m460 <= 0) {
                    m460 = attr_base().mKiInterval - 1;
                    m464++;
                    csXyz angle(0, cM_rndFX(32768.0f), 0);
                    fopAcM_create(fpcNm_KI_e, 0xFFFF8002, &current.pos, current.roomNo, &angle);
                }
            } else {
                m45A = 0;
                m45C = prm_get_kiCycle();
            }
        } else {
            m45A = 0;
            m45C--;
        }
    }
}

/* 00001194-000011E4       .text eff_hase__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::eff_hase() {
    dComIfGp_particle_setSimple(0xC06B, &home.pos);
}

/* 000011E4-00001254       .text se_fireblast_omen__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::se_fireblast_omen() {
    mDoAud_seStart(0x704E, &current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
}

/* 00001254-00001610       .text liftup_magmarock__Q210daObjFlame5Act_cFPvPv */
void* daObjFlame::Act_c::liftup_magmarock(void* i_actor, void* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)i_actor;
    Act_c* flame = (Act_c*)i_this;
    if (fopAc_IsActor(actor) && fopAcM_GetName(actor) == fpcNm_Obj_Magmarock_e && !fpcM_IsCreating(fopAcM_GetID(actor))) {
        f32 radius = 145.0f * flame->attr_scl().mCpsScale + attr_base().mLiftR;
        bool lt = flame->eyePos.y < flame->current.pos.y;
        f32 lo = (lt ? flame->eyePos.y : flame->current.pos.y) + attr_base().mLiftYMin;
        f32 hi = (lt ? flame->current.pos.y : flame->eyePos.y) + attr_base().mLiftYMax;
        if (actor->current.pos.absXZ(flame->eyePos) < radius) {
            if (actor->current.pos.y > lo && actor->current.pos.y < hi) {
                daObjMagmarock::Act_c* rock = (daObjMagmarock::Act_c*)actor;
                if (flame->mType != 1) {
                    f32 ofs1, ofs0;
                    f32 height = flame->mHeight;
                    if (height < 0.1f) {
                        ofs0 = attr_base().mLiftOfs0;
                        ofs1 = height * (10.0f * attr_base().mLiftOfs1);
                    } else if (height > 0.9f) {
                        f32 t = 1.0f - height;
                        ofs0 = t * (10.0f * attr_base().mLiftOfs0);
                        ofs1 = t * (10.0f * attr_base().mLiftOfs1);
                    } else {
                        ofs0 = attr_base().mLiftOfs0;
                        ofs1 = attr_base().mLiftOfs1;
                    }
                    f32 s = flame->m46C * flame->attr_scl().mHeightScale;
                    ofs0 *= s;
                    ofs1 *= s;
                    cXyz pos(flame->eyePos.x, ofs1 + (flame->eyePos.y + ofs0), flame->eyePos.z);
                    if (flame->mModeProc == 1 || flame->mModeProc == 2) {
                        rock->BeforeLiftRequest(pos);
                    } else {
                        rock->LiftUpRequest(pos);
                    }
                    flame->m459 = 1;
                }
            }
        }
    }
    return NULL;
}

/* 00001610-00001884       .text liftup_mflft__Q210daObjFlame5Act_cFPvPv */
void* daObjFlame::Act_c::liftup_mflft(void* i_actor, void* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)i_actor;
    Act_c* flame = (Act_c*)i_this;
    if (fopAc_IsActor(actor) && fopAcM_GetName(actor) == fpcNm_MFLFT_e) {
        mflft_class* lift = (mflft_class*)actor;
        f32 target46C;
        f32 target;
        f32 limitOfs;
        if (lift->m29A == 0) {
            target46C = 1.0f;
            target = 1.00044f;
            limitOfs = 5000.0f;
        } else {
            target46C = 1.0f;
            target = 1.0f;
            limitOfs = 5000.0f;
        }
        f32 ofs1, ofs0;
        f32 height = flame->mHeight;
        if (height < 0.1f) {
            ofs0 = attr_base().mLiftOfs0;
            ofs1 = height * (10.0f * attr_base().mLiftOfs1);
        } else if (height > 0.9f) {
            f32 t = 1.0f - height;
            ofs0 = t * (10.0f * attr_base().mLiftOfs0);
            ofs1 = t * (10.0f * attr_base().mLiftOfs1);
        } else {
            ofs0 = attr_base().mLiftOfs0;
            ofs1 = attr_base().mLiftOfs1;
        }
        f32 s = flame->m46C * flame->attr_scl().mHeightScale;
        cXyz pos(flame->eyePos.x, flame->eyePos.y + ofs0 * s + ofs1 * s, flame->eyePos.z);
        f32 limit = flame->current.pos.y + limitOfs;
        if (pos.y > limit) {
            pos.y = limit;
        }
        if (flame->mModeProc != 1 && flame->mModeProc != 2) {
            lift->setLiftUp(pos);
        }
        flame->m459 = 1;
        cLib_addCalc(&flame->m46C, target46C, 0.3f, 0.1f, 0.01f);
        cLib_addCalc(&flame->mExtraScaleY, target, 0.3f, 0.1f, 0.01f);
    }
    return NULL;
}

/* 00001884-00001988       .text mode_wait__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_wait() {
    u8 sch = prm_get_sch();
    bool start = false;
    if (sch != 0) {
        if ((sch & dKy_get_schbit()) && dKy_get_schbit_timer() == 0) {
            start = true;
        }
    } else if (mTimer <= 0.0f) {
        start = true;
    }
    if (start) {
        if (mType == 1) {
            mpBtkAnm->setFrame(0.0f);
            if (mpBrkAnm != NULL) {
                mpBrkAnm->setFrame(0.0f);
            }
            mModeProc = 2;
            mTimer = 23.0f;
            ki_init();
        } else {
            mModeProc = 1;
            mTimer = 127.0f;
        }
        mEm0State = 1;
        mEm1State = 1;
        mEm2State = 1;
        m457 = 1;
    }
}

/* 00001988-00001A08       .text mode_wait2__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_wait2() {
    se_fireblast_omen();
    if (mTimer <= 0.0f) {
        mpBtkAnm->setFrame(0.0f);
        if (mpBrkAnm != NULL) {
            mpBrkAnm->setFrame(0.0f);
        }
        mModeProc = 2;
        mTimer = 23.0f;
        ki_init();
    }
}

/* 00001A08-00001A98       .text mode_l_before__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_l_before() {
    m457 = 0;
    if (mTimer <= 0.0f) {
        mModeProc = 3;
        mTimer = 22.0f;
        mDoAud_seStart(0x380D, &eyePos, 0, m458);
    } else {
        se_fireblast_omen();
    }
}

/* 00001A98-00001AE8       .text mode_l_u__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_l_u() {
    mHeight = (1.0f / 22.0f) * (22.0f - mTimer);
    m457 = 1;
    if (mTimer <= 0.0f) {
        mModeProc = 4;
        mTimer = 90.0f;
    }
}

/* 00001AE8-00001B20       .text mode_u__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_u() {
    if (mTimer <= 0.0f) {
        mModeProc = 5;
        mTimer = 25.0f;
        mEm0State = 3;
    }
}

/* 00001B20-00001B74       .text mode_u_l__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_u_l() {
    mHeight = (1.0f / 25.0f) * mTimer;
    m457 = 1;
    if (mTimer <= 0.0f) {
        mModeProc = 6;
        mTimer = 20.0f;
        mEm1State = 3;
        mEm2State = 3;
    }
}

/* 00001B74-00001BEC       .text mode_l_after__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_l_after() {
    if (mTimer <= 0.0f) {
        mModeProc = 0;
        if (prm_get_sch() != 0) {
            mTimer = 0.0f;
        } else {
            mTimer = 120.0f;
        }
    }
}

/* 00001BEC-00001EAC       .text mode_proc_call__Q210daObjFlame5Act_cFv */
void daObjFlame::Act_c::mode_proc_call() {
    static ModeFunc mode_proc[] = {
        &Act_c::mode_wait,
        &Act_c::mode_wait2,
        &Act_c::mode_l_before,
        &Act_c::mode_l_u,
        &Act_c::mode_u,
        &Act_c::mode_u_l,
        &Act_c::mode_l_after,
    };

    if (mTimer >= -0.1f) {
        if (mModeProc == 0 || mModeProc == 1) {
            mTimer -= 1.0f;
        } else {
            mTimer -= attr_scl().mTimerRate;
        }
    }
    (this->*mode_proc[mModeProc])();
    if (attr_scl().mSimpleEmitter) {
        em_position();
        em_simple_set();
        em_simple_inv();
    } else {
        em_manual_set();
        em_manual_inv();
        em_position();
    }
    if (mModeProc != 0 && mModeProc != 1) {
        mpBtkAnm->play();
        if (mpBrkAnm != NULL) {
            mpBrkAnm->play();
        }
        mDoAud_seStart(0x7009, &eyePos, 0, m458);
    }
    if (m434) {
        bool set;
        if (mModeProc == 5) {
            set = mHeight > attr_scl().mCpsMinHeight;
        } else {
            set = true;
        }
        if (set) {
            mCps.SetStartEnd(mCpsP0, mCpsP1);
            mCps.SetR(mCpsRad);
            dComIfG_Ccsp()->Set(&mCps);
        }
    }
}

namespace daObjFlame {
namespace Method {
/* 00001EAC-00001ECC       .text Create__Q210daObjFlame6MethodFPv */
cPhs_State Create(void* i_this) {
    return ((Act_c*)i_this)->_create();
}
}  // namespace Method
}  // namespace daObjFlame

/* 00001ECC-00002200       .text _create__Q210daObjFlame5Act_cFv */
cPhs_State daObjFlame::Act_c::_create() {
    fopAcM_ct(this, Act_c);
    cPhs_State ret = dComIfG_resLoad(&mPhs, M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        mType = prm_get_scl();
        if (fopAcM_entrySolidHeap(this, solidHeapCB, attr_scl().mHeapSize)) {
            mOrigScale = scale;
            if (mType == 1) {
                m46C = 1.0f;
                mExtraScaleY = 1.00044f;
            } else {
                m46C = 1.0f;
                mExtraScaleY = 1.0f;
            }
            scale.x *= attr_scl().mScaleXZ;
            scale.y *= mExtraScaleY * attr_scl().mScaleY;
            scale.z *= attr_scl().mScaleXZ;
            mEm0State = 0;
            mEm1State = 0;
            mEm2State = 0;
            create_mode_init();
            set_switch();
            fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
            init_mtx();
            mStts.Init(100, 0xFF, this);
            mCps.Set(M_cps_src);
            mCps.SetStts(&mStts);
            mCpsP0 = current.pos;
            mCpsP1 = current.pos;
            mCpsRad = 145.0f * attr_scl().mCpsScale;
            m434 = 0;
            em_position();
            m458 = dComIfGp_getReverb(home.roomNo);
            m459 = 0;
            m45C = cM_rndF(prm_get_kiCycle() + 1);
            if (mModeProc != 0 && m45C == 0) {
                m45C = 1;
            }
        } else {
            ret = cPhs_ERROR_e;
        }
    }
    return ret;
}

inline bool daObjFlame::Act_c::_execute() {
    scale.x = mOrigScale.x * attr_scl().mScaleXZ;
    scale.y = mExtraScaleY * (mOrigScale.y * attr_scl().mScaleY);
    scale.z = mOrigScale.z * attr_scl().mScaleXZ;
    mode_proc_call();
    ki_make();
    if (prm_get_haze() == 0) {
        eff_hase();
    }
    if (mType == 1) {
        mRotY += attr_base().mRotSpd1;
        if (mHeight > 0.01f) {
            daYkgr_c::m_aim_rate = 1.0f;
        }
    } else {
        mRotY += attr_base().mRotSpd0;
    }
    m459 = 0;
    if (mModeProc == 1 || mModeProc == 2 || mModeProc == 3 || mModeProc == 4) {
        fopAcIt_Judge(liftup_magmarock, this);
        if (mType == 1) {
            fopAcIt_Judge(liftup_mflft, this);
        }
    }
    set_switch();
    set_mtx();
    return true;
}

inline bool daObjFlame::Act_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mpBtkAnm->entry(mpModel->getModelData());
    if (mpBrkAnm != NULL) {
        mpBrkAnm->entry(mpModel->getModelData());
    }
    dComIfGd_setListFilter();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return true;
}

inline bool daObjFlame::Act_c::_delete() {
    dComIfG_resDelete(&mPhs, M_arcname);
    return true;
}

namespace daObjFlame {
namespace Method {
/* 00002484-000024B4       .text Delete__Q210daObjFlame6MethodFPv */
BOOL Delete(void* i_this) {
    return ((Act_c*)i_this)->_delete();
}

/* 000024B4-00002638       .text Execute__Q210daObjFlame6MethodFPv */
BOOL Execute(void* i_this) {
    return ((Act_c*)i_this)->_execute();
}

/* 00002638-00002710       .text Draw__Q210daObjFlame6MethodFPv */
BOOL Draw(void* i_this) {
    return ((Act_c*)i_this)->_draw();
}

/* 00002710-000027B0       .text IsDelete__Q210daObjFlame6MethodFPv */
BOOL IsDelete(void* i_this) {
    Act_c* a_this = (Act_c*)i_this;
    if (!a_this->attr_scl().mSimpleEmitter) {
        if (a_this->mpEmitter0 != NULL) {
            a_this->mpEmitter0->becomeInvalidEmitter();
            a_this->mpEmitter0 = NULL;
        }
        if (a_this->mpEmitter1 != NULL) {
            a_this->mpEmitter1->becomeInvalidEmitter();
            a_this->mpEmitter1 = NULL;
        }
        if (a_this->mpEmitter2 != NULL) {
            a_this->mpEmitter2->becomeInvalidEmitter();
            a_this->mpEmitter2 = NULL;
        }
    }
    return TRUE;
}

}  // namespace Method
}  // namespace daObjFlame

actor_method_class daObjFlame::Method::Table = {
    (process_method_func)daObjFlame::Method::Create,
    (process_method_func)daObjFlame::Method::Delete,
    (process_method_func)daObjFlame::Method::Execute,
    (process_method_func)daObjFlame::Method::IsDelete,
    (process_method_func)daObjFlame::Method::Draw,
};

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

