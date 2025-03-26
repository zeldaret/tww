// The original name of this file is unknown, but it must exist because d_a_npc_nz's "cut" functions
// are in a separate .text section from the rest of its functions.

#include "d/actor/d_a_npc_nz.h"
#include "d/actor/d_a_esa.h"
#include "d/actor/d_a_tsubo.h"
#include "d/actor/d_a_obj_barrel.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"

/* 000032BC-000032E8       .text searchEsa_CB__FPvPv */
static BOOL searchEsa_CB(void* param_1, void* i_this) {
    return static_cast<daNpc_Nz_c*>(i_this)->_searchEsa((fopAc_ac_c*)param_1);
}

/* 000032E8-000034F0       .text _searchEsa__10daNpc_Nz_cFP10fopAc_ac_c */
BOOL daNpc_Nz_c::_searchEsa(fopAc_ac_c* pActor) {
    if(fopAcM_GetName(pActor) == PROC_ESA) {
        esa_class* pBait = static_cast<esa_class*>(pActor);
        if(pBait->field_0x298 == 0) {
            cXyz delta = pBait->current.pos - current.pos;
            if(mpMorf->getFrame() < 6.0f) {
                cLib_addCalcPos2(&pBait->current.pos, current.pos, 0.1f, 2.5f);
                mDoMtx_stack_c::transS(pBait->current.pos);
                mDoMtx_stack_c::ZXYrotM(pBait->current.angle);
                pBait->mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
            }

            if(delta.absXZ() < field_0x910) {
                mpBait = pBait;
                field_0x910 = delta.absXZ();
            }
        }
    }

    return false;
}

/* 000034F0-00003528       .text searchNzAndBomb_CB__FPvPv */
static BOOL searchNzAndBomb_CB(void* param_1, void*) {
    fopAc_ac_c* pActor = static_cast<fopAc_ac_c*>(param_1);

    if(fopAcM_GetName(pActor) == PROC_NZ || fopAcM_GetName(pActor) == PROC_BOMB) {
        fopAcM_delete(pActor);
    }

    return false;
}

/* 00003528-0000377C       .text searchTsuboAndBarrel_CB__FPvPv */
static BOOL searchTsuboAndBarrel_CB(void* param_1, void* param_2) {
    fopAc_ac_c* pActor1 = static_cast<fopAc_ac_c*>(param_1);
    daNpc_Nz_c* i_this = static_cast<daNpc_Nz_c*>(param_2);

    if(fopAcM_GetName(param_1) == PROC_TSUBO || fopAcM_GetName(param_1) == PROC_Obj_Barrel) {
        cXyz delta = i_this->field_0x6C4 - pActor1->current.pos;

        if(delta.absXZ() < 300.0f) {
            bool success = false;
            if(fopAcM_GetName(pActor1) == PROC_TSUBO) {
                success = static_cast<daTsubo::Act_c*>(pActor1)->pos_init();
            }
            else if(fopAcM_GetName(pActor1) == PROC_TSUBO) {
                success = static_cast<daObjBarrel::Act_c*>(pActor1)->pos_init();
            }

            if(!success) {
                fopAcM_delete(pActor1);
            }
        }
    }

    return false;
}

/* 0000377C-00003908       .text searchEsaInit_CB__FPvPv */
static BOOL searchEsaInit_CB(void* pActor1, void* pActor2) {
    if(fopAcM_GetName(pActor1) == PROC_ESA) {
        esa_class* pBait = static_cast<esa_class*>(pActor1);
        daNpc_Nz_c* pNz = static_cast<daNpc_Nz_c*>(pActor2);

        cXyz pos(pNz->field_0x6C4);
        pos.x += cM_ssin(pNz->current.angle.y) * 150.0f;
        pos.z += cM_scos(pNz->current.angle.y) * 150.0f;
        s16 angle = cAngle::d2s(cM_rndFX(358.0f));
        f32 mag = cM_rndF(30.0f);
        pos.x += mag * cM_ssin(angle);
        pos.z += mag * cM_scos(angle);

        pBait->current.pos = pos;
        pBait->old.pos = pos;

        mDoMtx_stack_c::transS(pBait->current.pos);
        mDoMtx_stack_c::ZXYrotM(pBait->current.angle);
        pBait->mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    }

    return false;
}

/* 00003908-00003B90       .text cutProc__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutProc() {
    typedef void(daNpc_Nz_c::*Func_t)(void);
    struct mode_entry_t {
        Func_t start;
        Func_t proc;
    };

    field_0x8F4 = dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
    if(field_0x8F4 == -1) {
        return;
    }

    static char* action_table[] = {
        "EATESA",
        "EATESA1ST",
        "KILLALL",
        "SHOW",
        "HIDE",
        "SETANM",
        "GOHOME",
        "CHKGETITEM",
    };

    static mode_entry_t cut_tbl[] = {
        {
            &daNpc_Nz_c::cutEatesaStart,
            &daNpc_Nz_c::cutEatesaProc,
        },
        {
            &daNpc_Nz_c::cutEatesaFirstStart,
            &daNpc_Nz_c::cutEatesaFirstProc,
        },
        {
            &daNpc_Nz_c::cutKillAllStart,
            &daNpc_Nz_c::cutKillAllProc,
        },
        {
            &daNpc_Nz_c::cutShowStart,
            &daNpc_Nz_c::cutShowProc,
        },
        {
            &daNpc_Nz_c::cutHideStart,
            &daNpc_Nz_c::cutHideProc,
        },
        {
            &daNpc_Nz_c::cutSetAnmStart,
            &daNpc_Nz_c::cutSetAnmProc,
        },
        {
            &daNpc_Nz_c::cutGoHomeStart,
            &daNpc_Nz_c::cutGoHomeProc,
        },
        {
            &daNpc_Nz_c::cutChkGetItemStart,
            &daNpc_Nz_c::cutChkGetItemProc,
        }
    };

    static char* a_demo_name_tbl[] = {
        "DEFAULT_NPC_NZ_ESA",
    };

    int actIdx = dComIfGp_evmng_getMyActIdx(field_0x8F4, action_table, ARRAY_SIZE(action_table), TRUE, 0);
    if(actIdx == -1) {
        dComIfGp_evmng_cutEnd(field_0x8F4);
        return;
    }

    if(dComIfGp_evmng_getIsAddvance(field_0x8F4)) {
        (this->*cut_tbl[actIdx].start)();
    }
    
    (this->*cut_tbl[actIdx].proc)();
}

/* 00003B90-00003BB8       .text cutEatesaStart__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutEatesaStart() {
    setAnm(6, false);
}

/* 00003BB8-00003CEC       .text cutEatesaProc__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutEatesaProc() {
    fopAcM_Search((fopAcIt_JudgeFunc)&searchEsa_CB, this);
    fopAc_ac_c* pBait = mpBait;

    if(mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
        current.angle.y = shape_angle.y = home.angle.y + (s16)((int)cM_rndFX(4.0f) * 2048);
    }

    if(pBait) {
        fopAcM_delete(pBait);
        mpBait = NULL;
        field_0x910 = FLOAT_MAX;
    }
    else {
        if(mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            current.angle.y = shape_angle.y = home.angle.y;
            dComIfGp_evmng_cutEnd(field_0x8F4);
        }
    }
}

/* 00003CEC-00003D40       .text cutEatesaFirstStart__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutEatesaFirstStart() {
    fopAcM_Search((fopAcIt_JudgeFunc)&searchEsa_CB, this);
    current.angle.y = shape_angle.y = home.angle.y;
    setAnm(0xA, false);
}

/* 00003D40-00003F54       .text cutEatesaFirstProc__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutEatesaFirstProc() {
    cXyz target(field_0x6C4);
    target.x += cM_ssin(home.angle.y) * 100.0f;
    target.z += cM_scos(home.angle.y) * 100.0f;

    if(field_0x6D5 == 10) {
        f32 temp2 = cLib_addCalcPosXZ(&current.pos, target, 0.25f, 10.0f, 2.0f);
        s16 temp3 = cLib_targetAngleY(&current.pos, &target);
        cLib_addCalcAngleS2(&shape_angle.y, temp3, 8, 0x1000);
        
        if(cLib_IsZero(temp2) && mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
            setAnm(6, false);
            field_0x906 = 2;
        }
        else {
            return;
        }
    }
    
    fopAcM_Search((fopAcIt_JudgeFunc)&searchEsa_CB, this);
    fopAc_ac_c* pBait = mpBait;
    if(pBait) {
        if(mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f) && cLib_calcTimer(&field_0x906) == 0) {
            fopAcM_delete(pBait);
            mpBait = NULL;
            dComIfGp_evmng_cutEnd(field_0x8F4);
        }
    }
    else {
        dComIfGp_evmng_cutEnd(field_0x8F4);
    }
}

/* 00003F54-0000404C       .text cutKillAllStart__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutKillAllStart() {
    fopAcM_Search((fopAcIt_JudgeFunc)&searchNzAndBomb_CB, this);
    fopAcM_Search((fopAcIt_JudgeFunc)&searchTsuboAndBarrel_CB, this);
    fopAcM_Search((fopAcIt_JudgeFunc)&searchEsaInit_CB, this);
    
    cXyz pos = field_0x6C4;
    s16 r5 = home.angle.y + 0x8000;
    pos.x += cM_ssin(home.angle.y) * 250.0f;
    pos.z += cM_scos(home.angle.y) * 250.0f;

    daPy_getPlayerActorClass()->setPlayerPosAndAngle(&pos, r5);
}

/* 0000404C-00004080       .text cutKillAllProc__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutKillAllProc() {
    dComIfGp_evmng_cutEnd(field_0x8F4);
}

/* 00004080-0000408C       .text cutShowStart__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutShowStart() {
    field_0x8FC = true;
}

/* 0000408C-000040C0       .text cutShowProc__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutShowProc() {
    dComIfGp_evmng_cutEnd(field_0x8F4);
}

/* 000040C0-000040CC       .text cutHideStart__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutHideStart() {
    field_0x8FC = false;
}

/* 000040CC-00004100       .text cutHideProc__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutHideProc() {
    dComIfGp_evmng_cutEnd(field_0x8F4);
}

/* 00004100-00004204       .text cutSetAnmStart__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutSetAnmStart() {
    u32* pAnmNo = dComIfGp_evmng_getMyIntegerP(field_0x8F4, "anm_no");
    s32 anmNo = 0;
    u32* pLoopCount = dComIfGp_evmng_getMyIntegerP(field_0x8F4, "loop_count");

    if(pAnmNo) {
        anmNo = *pAnmNo;
    }

    if(pLoopCount) {
        field_0x906 = *pLoopCount;
    }
    else {
        field_0x906 = 0;
    }

    setAnm(anmNo, false);
    if(anmNo == 8) {
        fopAcM_seStart(this, JA_SE_CV_M_NZ_TALK_IN, 0);
    }
}

/* 00004204-000043C0       .text cutSetAnmProc__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutSetAnmProc() {
    if(mpMorf->checkFrame(mpMorf->getEndFrame() - 1.0f)) {
        field_0x906--;
    }

    if(field_0x906 <= 0) {
        dComIfGp_evmng_cutEnd(field_0x8F4);
    }

    if(field_0x6D5 == 8) {
        if(mpMorf->checkFrame(8.0f)) {
            setSmokeParticle();
        }
        else if (mpMorf->checkFrame(13.0f)) {
            J3DModel* pModel = mpMorf->getModel();

            cXyz scale(0.65f, 0.65f, 0.65f);
            csXyz temp2(current.angle);
            temp2.y -= 0x4000;
            cXyz temp4(10.0f, 0.0f, 10.0f);
            cXyz pos;
            GXColor color;
            color.r = 0x80;
            color.g = 0x80;
            color.b = 0x80;

            mDoMtx_stack_c::copy(pModel->getAnmMtx(m_jnt.getHeadJntNum()));
            mDoMtx_stack_c::multVec(&temp4, &pos);
            dComIfGp_particle_set(dPa_name::ID_COMMON_0057, &pos, &shape_angle, &scale, 0xFF, 0, -1, &color);
        }
    }
}

/* 000043C0-000043C4       .text cutGoHomeStart__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutGoHomeStart() {
    return;
}

/* 000043C4-000044D4       .text cutGoHomeProc__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutGoHomeProc() {
    s16 target = cLib_targetAngleY(&current.pos, &home.pos);
    cLib_addCalcAngleS2(&current.angle.y, target, 4, 0x1000);
    shape_angle.y = current.angle.y;
    s16 dist = cLib_distanceAngleS(target, current.angle.y);
    if(dist < 0x4000) {
        if(field_0x6D5 != 0xA) {
            fopAcM_seStart(this, JA_SE_CV_M_NZ_TALK_OUT, 0);
        }

        setAnm(0xA, false);
        if(cLib_addCalcPosXZ(&current.pos, home.pos, 0.5f, 10.0f, 1.0f) < 1.0f) {
            dComIfGp_evmng_cutEnd(field_0x8F4);
        }
    }
}

/* 000044D4-00004520       .text cutChkGetItemStart__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutChkGetItemStart() {
    if(field_0x8F8 >= 3) {
        fopAcM_orderChangeEventId(dComIfGp_getPlayer(0), this, field_0x8FA, dEvtFlag_NOPARTNER_e, 0xFFFF);
    }
}

/* 00004520-00004554       .text cutChkGetItemProc__10daNpc_Nz_cFv */
void daNpc_Nz_c::cutChkGetItemProc() {
    dComIfGp_evmng_cutEnd(field_0x8F4);
}
