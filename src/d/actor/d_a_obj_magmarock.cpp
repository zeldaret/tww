/**
 * d_a_obj_magmarock.cpp
 * Object - Dragon Roost Cavern - Lava slab
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_magmarock.h"
#include "JSystem/J3DGraphAnimator/J3DAnimation.h"
#include "JSystem/JMath/JMATrigonometric.h"
#include "JSystem/JParticle/JPAEmitter.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "SSystem/SComponent/c_bg_s.h"
#include "SSystem/SComponent/c_bg_w.h"
#include "SSystem/SComponent/c_lib.h"
#include "SSystem/SComponent/c_phase.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "d/d_lib.h"
#include "d/d_s_play.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/mtx/mtx.h"
#include "dolphin/mtx/quat.h"
#include "f_op/f_op_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "global.h"
#include "m_Do/m_Do_audio.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_bg_s_movebg_actor.h"
#include "m_Do/m_Do_mtx.h"

const char daObjMagmarock::Act_c::M_arcname[] = "Kyjim";

/* 00000078-00000128       .text set_mtx__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::set_mtx() {
    Quaternion temp;
    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mDoMtx_quatMultiply(&m2b0, &m2d0, &temp);
    mDoMtx_stack_c::quatM(&temp);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::now);
    mDoMtx_copy(mDoMtx_stack_c::now, mtx);
}

/* 00000128-00000258       .text demo_move__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::demo_move() {
    if (dComIfGs_isEventBit(0x380) || m29f != NULL) {
        return;
    }
    if (m45a == 0) {
        if (eventInfo.getCommand() == dEvtCmd_INDEMO_e) {
            m45a += 1;
        } else {
            fopAcM_orderOtherEvent2(this, "magma_cam", 1);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
    } else if (m45a == 1) {
        int id = dComIfGp_evmng_getMyStaffId("Magrock", NULL, 0);
        if (dComIfGp_evmng_endCheck("magma_cam")) {
            dComIfGp_event_onEventFlag(8);
            m45a += 1;
            dComIfGs_onEventBit(0x380);
        } else {
            dComIfGp_evmng_cutEnd(id);
        }
    }
}

/* 00000258-00000410       .text ControlEffect__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::ControlEffect() {
    /* Matching but ugly as fuck */

    if (m45c == 0) {
        // HACK: make this branch be at the beginning of the machine code but the body at the end
        goto bleh;
    }
    if (m45e != 0) {
        if (m2a8 == NULL) {
            m2a8 = dComIfGp_particle_set(0x8104, &current.pos, NULL, NULL, 0xff);
        } else {
            m2a8->setGlobalTranslation(current.pos.x, current.pos.y, current.pos.z);
        }
        return;
    }
    if (m2a8 != NULL) {
        m2a8->becomeInvalidEmitter();
        m2a8 = NULL;
    }
    if (m2ac == NULL) {
        dComIfGp_getVibration().StartShock(4, 1, cXyz(0.0f, 1.0f, 0.0f));
        m2ac = dComIfGp_particle_setToon(0x8105, &current.pos, NULL, NULL, 0xff);
    } else {
        m2ac->setGlobalTranslation(current.pos.x, current.pos.y, current.pos.z);
    }
    goto finish;

    bleh:
    if (m2ac == NULL) {
        return;
    }
    m2ac->becomeInvalidEmitter();
    m2ac = NULL;
    return;
    finish:;
}

/* 0000044C-00000560       .text play_anim__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::play_anim() {
    if (m44c > 375 && m438 > 0.0f) {
        m438 = m438 - 1.0f;
    } else if ((m44c < 15 || m44c > 60) && m438 < M_brk->getFrameMax()) {
        m438 += 1.0f;
    }

    if (m44c < 60 && m434 < M_bck->getFrameMax()) {
        m434 += 1.0f;
    } else if (m44c > 375 && m434 > 0.0f) {
        m434 -= 1.0f;
    }
}

/* 00000560-0000058C       .text appear_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::appear_proc_init() {
    m448 = 30;
    m2e0 = &Act_c::appear_proc;
}

/* 0000058C-000005EC       .text appear_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::appear_proc() {
    if (m448 == 10) {
        dComIfG_Bgsp()->Regist(mpBgW, this);
    }
    if (m448 == 0) {
        wait_proc_init();
    }
}

/* 000005EC-00000618       .text wait_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::wait_proc_init() {
    m448 = 300;
    m2e0 = &Act_c::wait_proc;
}

/* 00000618-00000644       .text wait_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::wait_proc() {
    if (m448 == 0) {
        quake_proc_init();
    }
}

/* 00000644-000006E0       .text stay_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::stay_proc_init() {
    u8 param = fopAcM_GetParam(this);
    if (param == 0xff) {
        param = 0;
    }
    m438 = 30.0f;
    m434 = 30.0f;
    m448 = param * 15 + 30;
    m44c = 330;
    dComIfG_Bgsp()->Regist(mpBgW, this);
    m2e0 = &Act_c::stay_proc;
}

/* 000006E0-00000720       .text stay_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::stay_proc() {
    if (m29e != 0 && m448-- == 0) {
        quake_proc_init();
    }
}

/* 00000720-000007B8       .text quake_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::quake_proc_init() {
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    mDoAud_seStart(0x380f, &eyePos, 0, reverb);
    m448 = 45;
    m2e0 = &Act_c::quake_proc;
}

/* 000007B8-0000084C       .text quake_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::quake_proc() {
    m454 = m454 + m456;
    cLib_addCalcAngleS2(&m456, 0x1000, 2, 0x100);
    const float f1 = 750.0f;
    const float f3 = 50.0f;
    const float f2 = 0.25f;
    cLib_addCalc2(&m430, REG10_F(10) + f1, f2, f3);
    if (!m448) {
        vanish_proc_init();
    }
}

/* 0000084C-00000878       .text vanish_proc_init__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::vanish_proc_init() {
    /* Nonmatching */
    m448 = 0x5a;
    m2e0 = &Act_c::vanish_proc;
}

/* 00000878-000008F8       .text vanish_proc__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::vanish_proc() {
    m454 = m454 + m456;
    cLib_addCalcAngleS2(&m456, 0, 4, 0x40);
    if (m448 == 0x50) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
    if (m448 < 0) {
        fopAcM_delete(this);
    }
}

/* 000008F8-00000AEC       .text ride_call_back__14daObjMagmarockFP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void daObjMagmarock::ride_call_back(dBgW* i_dbgw, fopAc_ac_c* i_this, fopAc_ac_c* i_other) {
    /* Nonmatching */
    Act_c *p_this = (Act_c*)i_this;
    cXyz temp = p_this->current.pos - i_other->current.pos;
    cXyz vertical(0.0f, 1.0f, 0.0f);
    cXyz vec = temp.outprod(vertical);
    f32 len = vec.abs();
    if (vec.normalizeRS()) {
        f32 inter1 = (p_this->current.pos.y - p_this->home.pos.y) * 0.001f * 4.0f + 2.0f;
        s16 unk = -len * inter1;
        cLib_addCalcAngleS2(&p_this->m298, unk, 8, 0x200);
        p_this->m29c = 1;
        p_this->m29e = 1;
        f32 sin = cM_ssin(p_this->m298);
        p_this->m2c0.x = vec.x * sin;
        p_this->m2c0.y = vec.y * sin;
        p_this->m2c0.z = vec.z * sin;
        p_this->m2c0.w = cM_scos(p_this->m298);
    }
}

/* 00000AEC-00000B0C       .text CheckCreateHeap__14daObjMagmarockFP10fopAc_ac_c */
BOOL daObjMagmarock::CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->CreateHeap();
}

/* 00000B0C-00000DA0       .text CreateHeap__Q214daObjMagmarock5Act_cFv */
BOOL daObjMagmarock::Act_c::CreateHeap() {
    J3DModelData *modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(M_arcname, 9));
    JUT_ASSERT(0x14d, modelData != NULL);
    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    M_brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, 0xc);
    M_bck = (J3DAnmTransform*)dComIfG_getObjectRes(M_arcname, 6);
    JUT_ASSERT(0x155, M_brk != NULL);
    JUT_ASSERT(0x156, M_bck != NULL);

    int brkAnmRes = mBrkAnm.init(modelData, M_brk, FALSE, J3DFrameCtrl::EMode_LOOP);
    int bckAnmRes = mBckAnm.init(modelData, M_bck, FALSE, J3DFrameCtrl::EMode_LOOP);

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
    mDoMtx_copy(mDoMtx_stack_c::now, mtx);

    cBgD_t* cBgD = (cBgD_t*)dComIfG_getObjectRes(M_arcname, 0xf);
    mpBgW = dBgW_NewSet(cBgD, cBgW::MOVE_BG_e, &mtx);
    mpBgW->SetCrrFunc(&dBgS_MoveBGProc_Typical);
    if (mpBgW == NULL) {
        return FALSE;
    }
    return mpModel != NULL && brkAnmRes != 0 && bckAnmRes != 0;
}


/* 00000DA0-000013B4       .text CreateInit__Q214daObjMagmarock5Act_cFv */
BOOL daObjMagmarock::Act_c::CreateInit() {
    /* Nonmatching */
    scale.setall(1.0f);
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(
        this,
        /*minX=*/ -200.0,
        /*minY=*/ -30.0,
        /*minZ=*/ -200.0,
        /*maxX=*/ 200.0,
        /*maxY=*/ 30.0,
        /*maxZ=*/ 200
    );
    mDoMtx_copy(mpModel->getBaseTRMtx(), mtx);
    m430 = 0;
    m298 = 0;
    m29a = 0;
    m450 = 0;
    m448 = 0x1e;
    m44c = 0;
    m438 = 0.0f;
    m454 = 0;
    m456 = 0;
    m45a = 0;
    m29e = 0;
    // TODO CLEAN UP
    speed.setall(0);
    home.pos = current.pos;
    home.pos.y += 15.0f;
    gravity = -2.5f;
    m2b0 = m2c0 = m2d0 = ZeroQuat;
    set_mtx();
    mpBgW->SetRideCallback(&ride_call_back);
    m29f = fopAcM_GetParam(this) >> 0x18;
    if (m29f != 0) {
        stay_proc_init();
    } else {
        appear_proc_init();
        if (m2a0 == NULL) {
            s8 reverb = dComIfGp_getReverb(current.roomNo);
            mDoAud_seStart(0x380e, &eyePos, 0, reverb);
            dComIfGp_getVibration().StartShock(4, 1, cXyz(0.0f, 1.0f, 0.0f));
            m35c = tevStr;
            g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &m35c);
            m35c.mColorC0.r = m35c.mColorC0.r + (s32)((0xff-m35c.mColorC0.r)*0.12f)&0xff;
            m35c.mColorC0.g = m35c.mColorC0.g + (s32)((0xff-m35c.mColorC0.g)*0.12f)&0xff;
            m35c.mColorC0.b = m35c.mColorC0.b + (s32)((0xff-m35c.mColorC0.b)*0.12f)&0xff;

            m35c.mColorK0.r = m35c.mColorK0.r + (s32)((0xff-m35c.mColorK0.r)*0.12f);
            m35c.mColorK0.g = m35c.mColorK0.g + (s32)((0xff-m35c.mColorK0.g)*0.12f);
            m35c.mColorK0.b = m35c.mColorK0.b + (s32)((0xff-m35c.mColorK0.b)*0.12f);
            m2a0 = dComIfGp_particle_setToon(0x8072, &current.pos, NULL, NULL, (u8)(REG10_F(25)*102.f+153.0f));
            m2a4 = dComIfGp_particle_setToon(0x8073, &current.pos, NULL, NULL, (u8)(REG10_F(26)*102.f+153.0f));

            if (m2a0 != NULL) {
                const GXColor *temp = &Act_c::default_color;
                m2a0->setGlobalPrmColor(temp->r, temp->g, temp->b);
                m2a0->setGlobalEnvColor(temp->r, temp->g, temp->b);
            }
            if (m2a4 != NULL) {
                const GXColor *temp = &Act_c::default_color;
                m2a4->setGlobalPrmColor(temp->r, temp->g, temp->b);
                m2a4->setGlobalEnvColor(temp->r, temp->g, temp->b);
            }
        }
    }
    return TRUE;
}
const GXColor daObjMagmarock::Act_c::default_color = {0xFF, 0xFF, 0xFF, 0xFF};

/* 000013B4-00001560       .text LiftUpRequest__Q214daObjMagmarock5Act_cFR4cXyz */
BOOL daObjMagmarock::Act_c::LiftUpRequest(cXyz &param_1) {
    m43c = param_1;
    if (checkProcess(&Act_c::appear_proc) == 0) {
        if (checkProcess(&Act_c::wait_proc) != 0) {
            cXyz temp = current.pos - m43c;
            temp.y = 0.0f;
            if (!temp.normalizeRS()) {
                temp.x = 0.0f;
                temp.y = 0.0f;
                temp.z = 1.0f;
            }
            temp *= 10.0f;
            current.pos += temp;
        }
        return FALSE;
    }
    cLib_addCalcPos2(&current.pos, param_1, 0.05f, 5.0f);
    cLib_addCalc2(&m430, 750.0f, 0.5f, 40.0f);
    cLib_addCalcAngleS2(&m456, 0x1200, 4, 0x100);
    m454 = m454 + m456;
    cLib_addCalc2(&current.pos.y, param_1.y, 0.25f, 150.0f);
    m45c = 1;
    return TRUE;
}


/* 00001560-0000167C       .text BeforeLiftRequest__Q214daObjMagmarock5Act_cFR4cXyz */
bool daObjMagmarock::Act_c::BeforeLiftRequest(cXyz &param_1) {
    /* Nonmatching: floating point constants order */
    m43c = param_1;
    if (m43c.y < home.pos.y + 25.0f) {
        m43c.y = home.pos.y + 25.0f;
    }
    if (checkProcess(&Act_c::wait_proc) == 0) {
        return false;
    }
    cLib_addCalcPos2(&current.pos, m43c, 0.05f, 5.0f);
    cLib_addCalc2(&m430, 500.0f, 0.25f, 20.0f);
    cLib_addCalcAngleS2(&m456, 0xa00, 8, 0x100);
    m454 += m456;
    cLib_addCalc2(&current.pos.y, m43c.y, 0.25f, 150.0f);
    m45c = 1;
    m45e = 1;
    return true;
}

/* 0000167C-000017DC       .text calc_ground_quat__Q214daObjMagmarock5Act_cFv */
void daObjMagmarock::Act_c::calc_ground_quat() {
    const f32 LIMIT = -99999990.0;
    f32 y = dComIfGp_getMagma() != NULL
        ? dComIfGp_getMagma()->checkYpos(current.pos)
        : (current.pos.y - 10.0f);
    if (y > LIMIT) {
        home.pos.y = y + 10.0f + 15.0f;
    }

    home.pos.x = current.pos.x;
    home.pos.z = current.pos.z;

    m40c[0].x = 0.0f;
    m40c[0].y = 0.0f;
    m40c[0].z = 120.0f;

    m40c[1].x = 103.9f;
    m40c[1].y = 0.0f;
    m40c[1].z = -60.0f;

    m40c[2].x = -103.9f;
    m40c[2].y = 0.0f;
    m40c[2].z = -60.0f;

    for(int i = 0; i < 3; i++) {
        m40c[i] += home.pos;
        f32 y = dComIfGp_getMagma() != NULL
            ? dComIfGp_getMagma()->checkYpos(m40c[i])
            : (current.pos.y - 10.0f);
        if (y > -99999990.0f) {
            m40c[i].y = y+15.0f;
        }
    }

    dLib_calc_QuatFromTriangle(&m2d0, 0.25, m40c, &m40c[1], &m40c[2]);
}

/* 000017DC-0000198C       .text Create__Q214daObjMagmarock6MethodFPv */
cPhs_State daObjMagmarock::Method::Create(void *i_this) {
    daObjMagmarock::Act_c* pthis = (Act_c*)i_this;
    fopAcM_ct(pthis, Act_c);
    cPhs_State ret = dComIfG_resLoad(&pthis->mPhase, daObjMagmarock::Act_c::M_arcname);
    if (ret == cPhs_COMPLEATE_e) {
        if (g_dComIfG_gameInfo.play.getMagma() == NULL){
            ret = cPhs_INIT_e;
        } else if(!fopAcM_entrySolidHeap(pthis, daObjMagmarock::CheckCreateHeap, 0x5d40)) {
            ret = cPhs_ERROR_e;
        } else {
            pthis->CreateInit();
        }
    }
    return ret;
}

/* 00001A90-00001B14       .text Delete__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::Delete(void *i_this) {
    daObjMagmarock::Act_c* pthis = (Act_c*)i_this;

    dComIfG_resDelete(&pthis->mPhase, Act_c::M_arcname);
    if (pthis->heap != NULL) {
        if (pthis->mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(pthis->mpBgW);
        }
    }
    return TRUE;
}

/* 00001B14-00001B38       .text Execute__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::Execute(void *i_this) {
    Act_c* pthis = (Act_c*)i_this;
    return pthis->_execute();
}

/* 00001B38-00001EC0       .text _execute__Q214daObjMagmarock5Act_cFv */
bool daObjMagmarock::Act_c::_execute() {
    /* Nonmatching */
    calc_ground_quat();
    if (m45c == 0) {
        Process ptmf = &Act_c::quake_proc;
        BOOL thing = m2e0 == ptmf;
        if (!thing) {
            ptmf = &Act_c::vanish_proc;
            BOOL thing = m2e0 == ptmf;
            if (!thing) {
                cLib_addCalc2(&m430, 0.0f, 0.2f, 20.0f);
                cLib_addCalcAngleS2(&m456, 0, 4, 0x100);
            }
        }
        current.pos.y = current.pos.y + speed.y;
        speed.y = speed.y + gravity;
    } else {
        speed.y = 0.0f;
    }
    if (current.pos.y < home.pos.y + 100.0f) {
        if (home.pos.y + 100.0f <= old.pos.y) {
            dComIfGp_getVibration().StartShock(4, 1, cXyz(0.0f, 1.0f, 0.0f));
        }
        f32 cy = current.pos.y;
        f32 hy = home.pos.y;
        if (cy < hy) {
            hy -= 30.0f;
            if (cy < hy) {
                current.pos.y = hy;
            }
            speed.y = speed.y - (REG10_F(26) + 0.4f)*(current.pos.y-home.pos.y);
        }
        speed.y = speed.y * (0.65f - REG10_F(25));
    }
    if (m45c == 0) {
        Process ptmf = &Act_c::stay_proc;
        BOOL thing = m2e0 == ptmf;
        if (!thing) {
            m448 -= 1;
            m44c += 1;
        }
    }
    set_mtx();
    demo_move();
    ControlEffect();
    m45c = 0;
    m45e = 0;
    (this->*m2e0)();
    play_anim();
    shape_angle.x = m430 * JMASCos(m454);
    shape_angle.z = m430 * JMASSin(m454);
    if (m29c == 0) {
        m2c0 = ZeroQuat;
    }
    // inline?
    Quaternion temp;
    mDoMtx_quatSlerp(&m2b0, &m2c0, &temp, 0.25f);
    m2b0 = temp;

    m29c = 0;
    if (mpBgW->ChkUsed()) {
        // inline?
        mpBgW->mIgnorePlaneType = mpBgW->mIgnorePlaneType | 4 /* Roof */;
        mpBgW->Move();
    }
    return FALSE;
}

/* 00001EC0-00002128       .text Draw__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::Draw(void *i_this) {
    /* Nonmatching */
    Act_c *p_this = static_cast<Act_c*>(i_this);
    actor_place* pcurrent = &p_this->current;
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &pcurrent->pos, &p_this->tevStr);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &pcurrent->pos, &p_this->m35c);
    p_this->m35c.mColorC0.r = p_this->m35c.mColorC0.r + (s32)((0xff-p_this->m35c.mColorC0.r)*0.12f)&0xff;
    p_this->m35c.mColorC0.g = p_this->m35c.mColorC0.g + (s32)((0xff-p_this->m35c.mColorC0.g)*0.12f)&0xff;
    p_this->m35c.mColorC0.b = p_this->m35c.mColorC0.b + (s32)((0xff-p_this->m35c.mColorC0.b)*0.12f)&0xff;

    p_this->m35c.mColorK0.r = p_this->m35c.mColorK0.r + (s32)((0xff-p_this->m35c.mColorK0.r)*0.12f);
    p_this->m35c.mColorK0.g = p_this->m35c.mColorK0.g + (s32)((0xff-p_this->m35c.mColorK0.g)*0.12f);
    p_this->m35c.mColorK0.b = p_this->m35c.mColorK0.b + (s32)((0xff-p_this->m35c.mColorK0.b)*0.12f);
    g_env_light.setLightTevColorType(p_this->mpModel, &p_this->tevStr);
    p_this->mBrkAnm.entry(p_this->mpModel->getModelData(), (s16)p_this->m438);
    p_this->mBckAnm.entry(p_this->mpModel->getModelData(), (s16)p_this->m434);
    mDoExt_modelUpdateDL(p_this->mpModel);
    return TRUE;
}

/* 00002128-00002130       .text IsDelete__Q214daObjMagmarock6MethodFPv */
BOOL daObjMagmarock::Method::IsDelete(void*) {
    return TRUE;
}

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
    /* Size         */ sizeof(daObjMagmarock::Act_c) ,
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Magmarock_e,
    /* Actor SubMtd */ &daObjMagmarock::Method::Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
