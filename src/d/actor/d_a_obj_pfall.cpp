/**
 * d_a_obj_pfall.cpp
 * NPC - Rat (crawlspaces) (opens trap doors)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_pfall.h"
#include "d/d_procname.h"
#include "d/d_com_inf_game.h"
#include "d/res/res_pfall.h"
#include "d/d_lib.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_priority.h"

static const int l_bck_ix_tbl[] = {
    PFALL_BCK_NZ_WAIT,
    PFALL_BCK_HIKU,
};

static daObj_PfallHIO_c l_HIO;

/* 000000EC-0000010C       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daObj_Pfall_c*>(i_this)->CreateHeap();
}

/* 0000010C-00000140       .text __ct__16daObj_PfallHIO_cFv */
daObj_PfallHIO_c::daObj_PfallHIO_c() {
    mNo = -1;
    field_0x05 = false;
    field_0x06 = 0;
    field_0x08 = 3.0f;
    field_0x0C = 0;
}

/* 00000140-00000190       .text setAnm__13daObj_Pfall_cFv */
void daObj_Pfall_c::setAnm() {
    static const int a_anm_bcks_tbl[] = {
        PFALL_BCK_NZ_WAIT,
        PFALL_BCK_HIKU,
    };

    static const dLib_anm_prm_c a_anm_prm_tbl[] = {
        {
            /* mAnmIdx     */ -1,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 0,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 1,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
    };

    dLib_bcks_setAnm("Pfall", mpMorf, &mBckIdx, &field_0x481, &mOldAnmPrmIdx, a_anm_bcks_tbl, a_anm_prm_tbl, false);
}

/* 00000190-000004DC       .text set_mtx__13daObj_Pfall_cFv */
void daObj_Pfall_c::set_mtx() {
    static cXyz offset_pos_left(-35.0f, 0.0f, 105.0f);
    static cXyz offset_pos_right(35.0f, 0.0f, -105.0f);

    field_0x3C4->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::transM(offset_pos_left);
    mDoMtx_stack_c::transM(0.0f, -10.0f, 0.0f);
    mDoMtx_stack_c::ZrotM(field_0x3B4);
    mDoMtx_stack_c::transM(0.0f, 10.0f, 0.0f);
    field_0x3C4->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), field_0x3CC);

    field_0x3FC->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    mDoMtx_stack_c::transM(offset_pos_right);
    mDoMtx_stack_c::YrotM( -0x8000);
    mDoMtx_stack_c::transM(0.0f, -10.0f, 0.0f);
    mDoMtx_stack_c::ZrotM(field_0x3B4);
    mDoMtx_stack_c::transM(0.0f, 10.0f, 0.0f);
    field_0x3FC->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), field_0x404);

    J3DModel* pModel = mpMorf->getModel();
    static cXyz offset_pos(0.0f, 0.0f, -130.0f);
    static cXyz scale(0.5f, 0.5f, 0.5f);

    pModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);

    mDoMtx_stack_c::transM(offset_pos);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    mDoMtx_stack_c::transM(0.0f, field_0x438 + l_HIO.field_0x08, 0.0f);
    mDoMtx_stack_c::YrotM(-0x8000);
    mpHimoModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000518-00000858       .text CreateHeap__13daObj_Pfall_cFv */
BOOL daObj_Pfall_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Pfall", PFALL_BDL_AOTSI);
    JUT_ASSERT(0xD1, modelData != NULL);
    field_0x3C4 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    field_0x3FC = mDoExt_J3DModel__create(modelData, 0, 0x11020203);

    if(field_0x3C4 == NULL || field_0x3FC == NULL) {
        return FALSE;
    }

    J3DModelData* himoModelData = (J3DModelData*)dComIfG_getObjectRes("Pfall", PFALL_BDL_PSUZU);
    JUT_ASSERT(0xD9, himoModelData != NULL);
    mpHimoModel = mDoExt_J3DModel__create(himoModelData, 0, 0x11020203);

    if (mpHimoModel == NULL) {
        return FALSE;  
    }

    J3DModelData* nzModelData = (J3DModelData*)dComIfG_getObjectRes("Pfall", PFALL_BDL_NZ);
    JUT_ASSERT(0xE0, nzModelData != NULL);
    mpMorf = new mDoExt_McaMorf(
        nzModelData,
        NULL, NULL,
        NULL,
        -1, 1.0f, 0, -1, 1,
        NULL,
        0x00080000,
        0x11000002
    );

    if(mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    mpMorf->getModel()->setUserArea((u32)this);
    set_mtx();
    mpMorf->calc();
    mpBgW = new dBgW();

    if(mpBgW == NULL) {
        return FALSE;
    }
    cBgD_t* pData = (cBgD_t*)dComIfG_getObjectRes("Pfall", PFALL_DZB_AOTOSI);

    if (mpBgW->Set(pData, cBgW::MOVE_BG_e, &field_0x3CC) == true) {
        return FALSE;
    }
    mpBgW2 = new dBgW();

    if(mpBgW2 == NULL) {
        return FALSE;
    }
    
    pData = (cBgD_t*)dComIfG_getObjectRes("Pfall", PFALL_DZB_AOTOSI);
    
    if (mpBgW2->Set(pData, cBgW::MOVE_BG_e, &field_0x404) == true) {
        return FALSE;
    }
    return TRUE;
}

/* 00000858-000008CC       .text CreateInit__13daObj_Pfall_cFv */
void daObj_Pfall_c::CreateInit() {
    dComIfG_Bgsp()->Regist(mpBgW, this);
    dComIfG_Bgsp()->Regist(mpBgW2, this);
    set_mtx();
    field_0x481 = 1;
    mode_wait_init();
}

/* 000008CC-000009E8       .text _create__13daObj_Pfall_cFv */
cPhs_State daObj_Pfall_c::_create() {
    fopAcM_SetupActor(this, daObj_Pfall_c);
    cPhs_State phase = dComIfG_resLoad(&mPhsPfall, "Pfall");

    if (phase == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CallbackCreateHeap, 0x38E0)) {
            return cPhs_ERROR_e;
        } else {
            CreateInit();
        }
    }
    return phase;
}

/* 000009EC-00000AB0       .text _delete__13daObj_Pfall_cFv */
bool daObj_Pfall_c::_delete() {
    dComIfG_resDelete(&mPhsPfall, "Pfall");
    if(mpBgW && mpBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
    if(mpBgW2 && mpBgW2->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBgW2);
    }
    return true;
}

/* 00000AB0-00000C04       .text cutProc__13daObj_Pfall_cFv */
void daObj_Pfall_c::cutProc() {
    static char* action_table[3] = {
        "WAIT",
        "OPEN",
        "HIKU"
    };
    int staffIdx = dComIfGp_evmng_getMyStaffId("Nzfall");
    if(staffIdx != -1) {
        int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, action_table, ARRAY_SIZE(action_table), NULL, 0);
        if(actIdx == -1) {
            dComIfGp_evmng_cutEnd(staffIdx);
        } else {
            if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
                switch(actIdx) {
                    case 0:
                        cutWaitStart(staffIdx);
                        break;
                    case 1:
                        cutOpenStart(staffIdx);
                        break;
                    case 2:
                        cutHikuStart(staffIdx);
                        break;
                }
            }
            switch(actIdx) {
                case 0:
                    cutWaitProc(staffIdx);
                    break;
                case 1:
                    cutOpenProc(staffIdx);
                    break;
                case 2:
                    cutHikuProc(staffIdx);
                    break;
            }
        }
    }
}

/* 00000C04-00000C6C       .text cutWaitStart__13daObj_Pfall_cFi */
void daObj_Pfall_c::cutWaitStart(int staffIdx) {
    int* pTimerData = dComIfGp_evmng_getMyIntegerP(staffIdx, "Timer");
    if (pTimerData == NULL) {
        mTimer = 0;
    }
    else {
        mTimer = (s16)*pTimerData;
    }
}

/* 00000C6C-00000D18       .text cutWaitProc__13daObj_Pfall_cFi */
void daObj_Pfall_c::cutWaitProc(int staffIdx) {
    if(cLib_calcTimer(&mTimer) == 0) {
        if(!field_0x483) {
            field_0x483 = true;
            fopAcM_monsSeStart(this, JA_SE_CV_NZ_LAUGH, 0);
        }
        dComIfGp_evmng_cutEnd(staffIdx);
    }
}

/* 00000D18-00000D94       .text cutOpenStart__13daObj_Pfall_cFi */
void daObj_Pfall_c::cutOpenStart(int) {
    field_0x3B4 = 0;
    field_0x3B0 = 0;
    fopAcM_seStart(this, JA_SE_OBJ_TC_JAIL_FLR_BRK, 0);
}

/* 00000D94-00000E74       .text cutOpenProc__13daObj_Pfall_cFi */
void daObj_Pfall_c::cutOpenProc(int staffIdx) {
    if (field_0x3B0 >= 7) {
        dComIfGp_evmng_cutEnd(staffIdx);
    } else {
        const s16 temp[] = {
            0xC568,
            0xD508,
            0xC950,
            0xD120,
            0xCD38,
            0xCF2C,
            0xCE32
        };
        s16 temp2 = cLib_addCalcAngleS(&field_0x3B4, temp[field_0x3B0], 4, 0x2000, 0x100);
        if ((s16)std::fabsf(temp2) <= 0x100) {
            field_0x3B0++;
        }
    }
}

/* 00000E74-00000E80       .text cutHikuStart__13daObj_Pfall_cFi */
void daObj_Pfall_c::cutHikuStart(int) {
    field_0x481 = 2;
}

/* 00000E80-00000F00       .text cutHikuProc__13daObj_Pfall_cFi */
void daObj_Pfall_c::cutHikuProc(int staffIdx) {
    if(field_0x481 == 2){
        if(mpMorf->isStop()) {
            dComIfGp_evmng_cutEnd(staffIdx);
            field_0x481 = 1;
        }
    }
}

/* 00000F00-00000F1C       .text mode_wait_init__13daObj_Pfall_cFv */
void daObj_Pfall_c::mode_wait_init() {
    field_0x3B8 = l_HIO.field_0x0C;
    field_0x3A8 = NULL;
} 

/* 00000F1C-00000FC0       .text mode_wait__13daObj_Pfall_cFv */
void daObj_Pfall_c::mode_wait() {
    if(dLib_checkPlayerInCircle(current.pos, 100.0f, 100.0f) 
        && dComIfGp_getPlayer(0)->speedF == 0.0f
        && cLib_calcTimer(&field_0x3B8) == 0) {
            mode_event_init();
    }
    mpBgW->Move();
    mpBgW2->Move();
}

/* 00000FC0-00000FCC       .text mode_event_init__13daObj_Pfall_cFv */
void daObj_Pfall_c::mode_event_init() {
    field_0x3A8 = 1;
}

/* 00000FCC-000010A4       .text mode_event__13daObj_Pfall_cFv */
void daObj_Pfall_c::mode_event() {
    if(eventInfo.checkCommandDemoAccrpt()) {
        if(dComIfGp_evmng_endCheck("NZFALL")) {
            if(l_HIO.field_0x06 != 0) {
                mode_wait_init();
            } else {
                dComIfGp_setNextStage("sea", 15, 11);
            }
        }
    } else {
        fopAcM_orderOtherEvent(this, "NZFALL");
    }
    mpBgW->Move();
    mpBgW2->Move();
}

/* 000010A4-00001130       .text mode_proc_call__13daObj_Pfall_cFv */
void daObj_Pfall_c::mode_proc_call() {
    typedef void(daObj_Pfall_c::*ProcFunc)(void);
    static const ProcFunc mode_proc[] = {
        &daObj_Pfall_c::mode_wait,
        &daObj_Pfall_c::mode_event,
    };

    (this->*mode_proc[field_0x3A8])();
}

/* 00001130-000012F4       .text _execute__13daObj_Pfall_cFv */
bool daObj_Pfall_c::_execute() {
    attention_info.position = current.pos;
    eyePos = current.pos;
    
    if(dComIfGp_event_runCheck()) {
        cutProc();
    }

    if(field_0x481 == 2) {
        if(mpMorf->getFrame() == 6.0f) {
            fopAcM_seStart(this, JA_SE_OBJ_TC_JAIL_STRING, 0);
        }
        f32 frame = mpMorf->getFrame();
        if (!(frame > 0.0f && frame <= 6.0f)) {
            if (frame > 6.0f && frame <= 10.0f) {
                field_0x438 += 1.0f;
            }
            else {
                if (!(frame > 10.0f && frame <= 23.0f) && frame > 23.0f && frame <= 29.0f) {
                    field_0x438 -= 3.0f;
                }
            }
        }     
    } else {
        field_0x438 = 0.0f;
    }
    mpMorf->play(NULL, 0, 0);
    fopAcM_posMoveF(this, NULL);
    set_mtx();
    mode_proc_call();
    setAnm();
    return false;
}

/* 000012F4-0000142C       .text nz_draw__13daObj_Pfall_cFv */
void daObj_Pfall_c::nz_draw() {
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* pModelData = pModel->getModelData();

    J3DJoint* rootJoint = pModelData->getJointNodePointer(0);

    J3DShape* matShape = pModelData->getMaterialNodePointer(0)->getShape();
    J3DShape* matShape2 = pModelData->getMaterialNodePointer(1)->getShape();
    J3DShape* matShape3 = pModelData->getMaterialNodePointer(2)->getShape();

    matShape->hide();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);

    mpMorf->updateDL();
    dComIfGd_setListMaskOff();

    matShape->show();
    pModel->getMatPacket(0)->unlock();
    matShape2->hide();
    matShape3->hide();
    rootJoint->entryIn();
    matShape2->show();
    matShape3->show();

    dComIfGd_setList();
}

/* 0000142C-000014E4       .text _draw__13daObj_Pfall_cFv */
bool daObj_Pfall_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(field_0x3C4, &tevStr);

    g_env_light.setLightTevColorType(field_0x3FC, &tevStr);
    mDoExt_modelUpdateDL(field_0x3C4);
    mDoExt_modelUpdateDL(field_0x3FC);
    nz_draw();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpHimoModel, &tevStr);
    mDoExt_modelUpdateDL(mpHimoModel);
    return true;
}

// to match .rodata
static const int dummy[] = {0x00FF0080};

/* 000014E4-00001504       .text daObj_PfallCreate__FPv */
static cPhs_State daObj_PfallCreate(void* i_this) {
    return static_cast<daObj_Pfall_c*>(i_this)->_create();
}

/* 00001504-00001528       .text daObj_PfallDelete__FPv */
static BOOL daObj_PfallDelete(void* i_this) {
    return static_cast<daObj_Pfall_c*>(i_this)->_delete();
}

/* 00001528-0000154C       .text daObj_PfallExecute__FPv */
static BOOL daObj_PfallExecute(void* i_this) {
    return static_cast<daObj_Pfall_c*>(i_this)->_execute();
}

/* 0000154C-00001570       .text daObj_PfallDraw__FPv */
static BOOL daObj_PfallDraw(void* i_this) {
    return static_cast<daObj_Pfall_c*>(i_this)->_draw();
}

/* 00001570-00001578       .text daObj_PfallIsDelete__FPv */
static BOOL daObj_PfallIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_PfallMethodTable = {
    (process_method_func)daObj_PfallCreate,
    (process_method_func)daObj_PfallDelete,
    (process_method_func)daObj_PfallExecute,
    (process_method_func)daObj_PfallIsDelete,
    (process_method_func)daObj_PfallDraw,
};

actor_process_profile_definition g_profile_OBJ_PFALL = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_PFALL,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Pfall_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_PFALL,
    /* Actor SubMtd */ &daObj_PfallMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_4_e,
};
