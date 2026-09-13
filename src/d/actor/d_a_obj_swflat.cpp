/**
 * d_a_obj_swflat.cpp
 * Object - Tower of the Gods - Floor switch (requires statues to stay active)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_swflat.h"
#include "d/d_cc_d.h"
#include "res/Object/Hfbot.h"

static daObjSwflat_HIO_c l_HIO;

namespace daObjSwflat {
static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e | cCcD_CoSPrm_NoCrr_e | cCcD_CoSPrm_NoCoHitInfSet_e,
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
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 10.0f,
        /* Height */ 20.0f,
    }},
};
}

/* 000000EC-00000138       .text __ct__17daObjSwflat_HIO_cFv */
daObjSwflat_HIO_c::daObjSwflat_HIO_c() {
    mChildID = -1;
    mRefCount = 0;
    mbKeepSwitch = 0;
    mbDebug = 0;
    mRadius = 10.0f;
    mHeight = 20.0f;
    mDelay = 0x1e;
    mWait = 0x1e;
}

const char daObjSwflat::Act_c::M_arcname[] = "Hfbot";
Mtx daObjSwflat::Act_c::M_tmp_mtx;

/* 00000138-00000280       .text CreateHeap__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HFBOT_BDL_HFBOT1_e);
    if (model_data == NULL) {
        return FALSE;
    }

    mpModel = mDoExt_J3DModel__create(model_data, 0, 0x11020203);

    J3DAnmTevRegKey* brk_data = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HFBOT_BRK_HFBOT1_e);
    if (brk_data == NULL) {
        return FALSE;
    }

    mpBrkAnm = new mDoExt_brkAnm();
    if (mpBrkAnm == NULL) {
        return FALSE;
    }

    int init_result = mpBrkAnm->init(model_data, brk_data, TRUE, 0);
    return mpModel != NULL && init_result != 0;
}

/* 000002C8-00000630       .text Create__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Create() {
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    init_mtx();
    fopAcM_setCullSizeSphere(this, 0.0f, 0.0f, 0.0f, 90.0f);

    mStts.Init(0xff, 0xff, this);
    mCyl.Set(l_cyl_src);
    mCyl.SetStts(&mStts);

    mType = prmGetType();
    mSwNo = prmGetSwNo();
    mSwNo2 = prmGetSwNo2();

    mFrame = 0;
    mFrameMax = (s16)(mpBrkAnm->getEndFrame() - 5.0f);
    mPos = current.pos;

    mWaitFlag = 0;
    if (l_HIO.mbKeepSwitch == 1) {
        if (mSwNo != 0xff) {
            fopAcM_offSwitch(this, mSwNo);
        }
        if (mSwNo2 != 0xff) {
            fopAcM_offSwitch(this, mSwNo2);
        }
    }

    u8 sw_no = mSwNo;
    if (mType == 2) {
        if (fopAcM_isSwitch(this, mSwNo2)) {
            mType = 0;
            sw_no = mSwNo2;
        } else {
            mType = 1;
        }
    }

    if (fopAcM_isSwitch(this, sw_no)) {
        mPressedPrev = 1;
        mPressed = 1;
        if (mType != 0) {
            mpEmtrOn = dComIfGp_particle_set(0x8164, &mPos, &shape_angle);
            mOnTimer = 0xfa;
        } else {
            mpEmtrOn = NULL;
            mOnTimer = 0;
            mWaitFlag = 1;
            mpBrkAnm->setFrame(mpBrkAnm->getEndFrame());
        }
        mpEmtrOff = NULL;
        mOffTimer = 0;
    } else {
        mPressedPrev = 0;
        mPressed = 0;
        mpEmtrOff = dComIfGp_particle_set(0x8163, &mPos, &shape_angle);
        mOffTimer = 0xfa;
        mpEmtrOn = NULL;
        mOnTimer = 0;
    }

    mDemoState = 0;
    mDemoTimer = 0;
    mWaitTimer = 0;

    if (l_HIO.mChildID < 0) {
        l_HIO.mChildID = mDoHIO_createChild("フラットスイッチ", &l_HIO);
    }
    l_HIO.mRefCount++;
    return TRUE;
}

/* 00000630-000007BC       .text Mthd_Create__Q211daObjSwflat5Act_cFv */
cPhs_State daObjSwflat::Act_c::Mthd_Create() {
    fopAcM_ct(this, Act_c);
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, M_arcname);

    if (phase_state == cPhs_COMPLEATE_e) {
        phase_state = MoveBGCreate(M_arcname, dRes_INDEX_HFBOT_DZB_HFBOT1_e, NULL, 0xFFFFFFFF);
        JUT_ASSERT(385, (phase_state == cPhs_COMPLEATE_e) || (phase_state == cPhs_ERROR_e));
    }
    return phase_state;
}

/* 00000974-0000097C       .text Delete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Delete() {
    return TRUE;
}

/* 0000097C-00000A64       .text Mthd_Delete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Mthd_Delete() {
    if (heap != NULL) {
        if (mpEmtrOff != NULL) {
            mpEmtrOff->becomeInvalidEmitter();
            mpEmtrOff = NULL;
        }
        if (mpEmtrOn != NULL) {
            mpEmtrOn->becomeInvalidEmitter();
            mpEmtrOn = NULL;
        }
    }

    if (l_HIO.mChildID >= 0) {
        if (--l_HIO.mRefCount == 0) {
            mDoHIO_deleteChild(l_HIO.mChildID);
            l_HIO.mChildID = -1;
        }
    }

    BOOL move_bg_delete_val = MoveBGDelete();
    dComIfG_resDelete(&mPhs, M_arcname);
    return move_bg_delete_val;
}

/* 00000A64-00000AE4       .text set_mtx__Q211daObjSwflat5Act_cFv */
void daObjSwflat::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 00000AE4-00000B20       .text init_mtx__Q211daObjSwflat5Act_cFv */
void daObjSwflat::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00000B20-0000121C       .text Execute__Q211daObjSwflat5Act_cFPPA3_A4_f */
BOOL daObjSwflat::Act_c::Execute(Mtx** pMtx) {
    u8 hit;
    u8 player_on = FALSE;
    mCyl.SetC(current.pos);
    if (l_HIO.mbDebug) {
        mCyl.SetR(l_HIO.mRadius);
        mCyl.SetH(l_HIO.mHeight);
    }
    dComIfG_Ccsp()->Set(&mCyl);

    hit = FALSE;
    if (mCyl.ChkCoHit()) {
        fopAc_ac_c* actor = mCyl.GetCoHitAc();
        if (actor != NULL) {
            if (fopAcM_CheckStatus(actor, fopAcStts_FREEZE_e)) {
                hit = TRUE;
                if (fopAcM_GetProfName(actor) == fpcNm_PLAYER_e) {
                    player_on = TRUE;
                }
            }
        }
    }

    if (mDemoTimer == 0) {
        if (hit) {
            mPressed = 1;
            mCyl.SetR(15.0f);
        } else if (mType == 1) {
            mPressed = 0;
            mCyl.SetR(10.0f);
        }
    }

    if (prmGetType() == 2) {
        if (fopAcM_isSwitch(this, mSwNo2)) {
            mType = 0;
            if (mWaitFlag == 0) {
                mWaitTimer = l_HIO.mWait;
                mWaitFlag = 1;
            }
        }
    }

    hit = FALSE;
    if (mPressed == 1) {
        if (mPressedPrev == 0) {
            mDoAud_seStart(JA_SE_OBJ_FLAT_SW_ON, &current.pos);
        }
        if (mWaitFlag == 0) {
            mDoAud_seStart(JA_SE_OBJ_FLAT_SW_LIGHT, &current.pos);
        }
        if (mFrame < mFrameMax) {
            mFrame++;
            mpBrkAnm->setFrame(mFrame);
        }
        if (!player_on) {
            fopAcM_onSwitch(this, mSwNo);
        }
        if (mWaitFlag == 0) {
            if (mpEmtrOn == NULL) {
                mpEmtrOn = dComIfGp_particle_set(0x8164, &mPos, &shape_angle);
                mOnTimer = 0xfa;
                hit = TRUE;
                if (prmGetType() == 0) {
                    mWaitTimer = l_HIO.mWait;
                    mWaitFlag = 1;
                }
            } else if (mOnTimer < 0xfa) {
                mOnTimer += 0x19;
                mpEmtrOn->setGlobalAlpha(mOnTimer);
                fopAcM_onSwitch(this, mSwNo);
            }
        }
        if (mpEmtrOff != NULL) {
            mOffTimer -= 0x19;
            mpEmtrOff->setGlobalAlpha(mOffTimer);
            if (mOffTimer == 0) {
                mpEmtrOff->becomeInvalidEmitter();
                mpEmtrOff = NULL;
            }
        }
    } else {
        if (mFrame > 0) {
            mFrame--;
            mpBrkAnm->setFrame(mFrame);
        }
        fopAcM_offSwitch(this, mSwNo);
        if (mpEmtrOff == NULL) {
            mpEmtrOff = dComIfGp_particle_set(0x8163, &mPos, &shape_angle);
            mOffTimer = 0xfa;
        } else if (mOffTimer < 0xfa) {
            mOffTimer += 0x19;
            mpEmtrOff->setGlobalAlpha(mOffTimer);
        }
        if (mpEmtrOn != NULL) {
            mOnTimer -= 0x19;
            mpEmtrOn->setGlobalAlpha(mOnTimer);
            if (mOnTimer == 0) {
                mpEmtrOn->becomeInvalidEmitter();
                mpEmtrOn = NULL;
            }
        }
    }

    switch (mDemoState) {
    case 0:
        mDemoTimer = 0;
        if (hit && player_on) {
            mDemoState = 1;
            mDemoTimer = 0x1e;
        }
        break;
    case 1:
        if (eventInfo.checkCommandDemoAccrpt()) {
            mDemoState = 2;
            if (l_HIO.mbDebug) {
                mDemoTimer = l_HIO.mDelay;
            }
        } else {
            fopAcM_orderPotentialEvent(this, 1, 0, 0);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
        break;
    case 2:
        mDemoTimer--;
        if (mDemoTimer <= 1) {
            dComIfGp_event_reset();
            mDemoState = 0;
            fopAcM_onSwitch(this, mSwNo);
        }
        break;
    }

    if (mWaitFlag != 0) {
        mPressed = 1;
        if (mWaitTimer != 0) {
            mWaitTimer--;
        } else {
            if (mpEmtrOn != NULL) {
                mOnTimer -= 0x19;
                mpEmtrOn->setGlobalAlpha(mOnTimer);
                if (mOnTimer == 0) {
                    mpEmtrOn->becomeInvalidEmitter();
                    mpEmtrOn = NULL;
                }
            }
            if (mpEmtrOff != NULL) {
                mOffTimer -= 0x19;
                mpEmtrOff->setGlobalAlpha(mOffTimer);
                if (mOffTimer == 0) {
                    mpEmtrOff->becomeInvalidEmitter();
                    mpEmtrOff = NULL;
                }
            }
            if (mFrame < mFrameMax + 5) {
                mFrame++;
                mpBrkAnm->setFrame(mFrame);
            }
        }
    }

    set_mtx();
    *pMtx = &M_tmp_mtx;
    mPressedPrev = mPressed;
    return TRUE;
}

/* 0000121C-000012D4       .text Draw__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    J3DModelData* model_data = mpModel->getModelData();
    mpBrkAnm->entry(model_data, mpBrkAnm->getFrame());
    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();
    return TRUE;
}

/* 000012D4-000012DC       .text IsDelete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::IsDelete() {
    return TRUE;
}

namespace daObjSwflat {
namespace {
/* 000012DC-000012FC       .text Mthd_Create__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->Mthd_Create();
}

/* 000012FC-0000131C       .text Mthd_Delete__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->Mthd_Delete();
}

/* 0000131C-0000133C       .text Mthd_Execute__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->MoveBGExecute();
}

/* 0000133C-00001368       .text Mthd_Draw__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->Draw();
}

/* 00001368-00001394       .text Mthd_IsDelete__Q211daObjSwflat28@unnamed@d_a_obj_swflat_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return ((daObjSwflat::Act_c*)i_this)->IsDelete();
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace
}; // namespace daObjSwflat

actor_process_profile_definition g_profile_Obj_Swflat = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0002,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_Obj_Swflat_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjSwflat::Act_c),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_Obj_Swflat_e,
    /* Actor SubMtd */ &daObjSwflat::Mthd_Table,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* Cull Type    */ fopAc_CULLSPHERE_CUSTOM_e,
};
