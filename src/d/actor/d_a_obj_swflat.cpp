/**
 * d_a_obj_swflat.cpp
 * Object - Tower of the Gods - Floor switch (requires statues to stay active)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_swflat.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_mtx.h"
#include "res/Object/Hfbot.h"

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


class daObjSwflat_HIO_c : public JORReflexible {
public:
    daObjSwflat_HIO_c();
    virtual ~daObjSwflat_HIO_c() {}
    void genMessage(JORMContext* ctx) { UNUSED(ctx); }

public:
    /* 0x04 */ s8 mNo;
    /* 0x08 */ int mCount;
    /* 0x0C */ f32 mRadius;
    /* 0x10 */ f32 mHeight;
    /* 0x14 */ s16 mEventTime;
    /* 0x16 */ s16 mFixTime;
    /* 0x18 */ u8 mDebug;
    /* 0x19 */ u8 mResetSw;
};  // Size: 0x1C

static daObjSwflat_HIO_c l_HIO;
Mtx daObjSwflat::Act_c::M_tmp_mtx;

/* 000000EC-00000138       .text __ct__17daObjSwflat_HIO_cFv */
daObjSwflat_HIO_c::daObjSwflat_HIO_c() {
    mNo = -1;
    mCount = 0;
    mResetSw = 0;
    mDebug = 0;
    mRadius = 10.0f;
    mHeight = 20.0f;
    mEventTime = 30;
    mFixTime = 30;
}

const char daObjSwflat::Act_c::M_arcname[] = "Hfbot";

/* 00000138-00000280       .text CreateHeap__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::CreateHeap() {
    J3DModelData* model_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HFBOT_BDL_HFBOT1_e);
    if (model_data == NULL) {
        return FALSE;
    }
    mpModel = mDoExt_J3DModel__create(model_data, 0, 0x11020203);

    J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(M_arcname, dRes_INDEX_HFBOT_BRK_HFBOT1_e);
    if (brk == NULL) {
        return FALSE;
    }
    mpBrkAnm = new mDoExt_brkAnm();
    if (mpBrkAnm == NULL) {
        return FALSE;
    }
    int ok = mpBrkAnm->init(model_data, brk, true, J3DFrameCtrl::EMode_NONE);
    return mpModel != NULL && ok != 0;
}

/* 00000280-00000630       .text Create__Q211daObjSwflat5Act_cFv */
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
    mFrameMax = mpBrkAnm->getEndFrame() - 5.0f;
    mEffPos = current.pos;
    mFixed = 0;

    if (l_HIO.mResetSw == 1) {
        if (mSwNo != 0xFF) {
            fopAcM_offSwitch(this, mSwNo);
        }
        if (mSwNo2 != 0xFF) {
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
        mWasOn = 1;
        mIsOn = 1;
        if (mType != 0) {
            mpEmitterOn = dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBUTTONON, &mEffPos, &shape_angle);
            mAlphaOn = 250;
        } else {
            mpEmitterOn = NULL;
            mAlphaOn = 0;
            mFixed = 1;
            mpBrkAnm->setFrame(mpBrkAnm->getEndFrame());
        }
        mpEmitterOff = NULL;
        mAlphaOff = 0;
    } else {
        mWasOn = 0;
        mIsOn = 0;
        mpEmitterOff = dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBUTTONOFF, &mEffPos, &shape_angle);
        mAlphaOff = 250;
        mpEmitterOn = NULL;
        mAlphaOn = 0;
    }

    mEvState = 0;
    mTimer = 0;
    mFixTimer = 0;

    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("フラットスイッチ", &l_HIO);
    }
    l_HIO.mCount++;
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

/* 00000994-0000099C       .text Delete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Delete() {
    return TRUE;
}

/* 0000099C-00000A84       .text Mthd_Delete__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Mthd_Delete() {
    if (heap != NULL) {
        if (mpEmitterOff != NULL) {
            mpEmitterOff->becomeInvalidEmitter();
            mpEmitterOff = NULL;
        }
        if (mpEmitterOn != NULL) {
            mpEmitterOn->becomeInvalidEmitter();
            mpEmitterOn = NULL;
        }
    }

    if (l_HIO.mNo >= 0) {
        l_HIO.mCount--;
        if (l_HIO.mCount == 0) {
            mDoHIO_deleteChild(l_HIO.mNo);
            l_HIO.mNo = -1;
        }
    }

    BOOL result = MoveBGDelete();
    dComIfG_resDelete(&mPhs, M_arcname);
    return result;
}

/* 00000A84-00000B04       .text set_mtx__Q211daObjSwflat5Act_cFv */
void daObjSwflat::Act_c::set_mtx() {
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::ZXYrotM(shape_angle);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    cMtx_copy(mDoMtx_stack_c::get(), M_tmp_mtx);
}

/* 00000B04-00000B40       .text init_mtx__Q211daObjSwflat5Act_cFv */
void daObjSwflat::Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
}

/* 00000B40-0000123C       .text Execute__Q211daObjSwflat5Act_cFPPA3_A4_f */
BOOL daObjSwflat::Act_c::Execute(Mtx** mtx) {
    bool is_player = false;

    mCyl.SetC(current.pos);
    if (l_HIO.mDebug) {
        mCyl.SetR(l_HIO.mRadius);
        mCyl.SetH(l_HIO.mHeight);
    }
    dComIfG_Ccsp()->Set(&mCyl);

    bool is_ride = false;
    if (mCyl.ChkCoHit()) {
        fopAc_ac_c* hit_ac = mCyl.GetCoHitAc();
        if (hit_ac != NULL && fopAcM_CheckStatus(hit_ac, fopAcStts_FREEZE_e)) {
            is_ride = true;
            if (fopAcM_GetProfName(hit_ac) == fpcNm_PLAYER_e) {
                is_player = true;
            }
        }
    }

    if (mTimer == 0) {
        if (is_ride) {
            mIsOn = 1;
            mCyl.SetR(15.0f);
        } else if (mType == 1) {
            mIsOn = 0;
            mCyl.SetR(10.0f);
        }
    }

    if (prmGetType() == 2 && fopAcM_isSwitch(this, mSwNo2)) {
        mType = 0;
        if (!mFixed) {
            mFixTimer = l_HIO.mFixTime;
            mFixed = 1;
        }
    }

    bool is_new = false;
    if (mIsOn == 1) {
        if (!mWasOn) {
            mDoAud_seStart(JA_SE_OBJ_FLAT_SW_ON, &current.pos);
        }
        if (!mFixed) {
            mDoAud_seStart(JA_SE_OBJ_FLAT_SW_LIGHT, &current.pos);
        }
        if (mFrame < mFrameMax) {
            mFrame++;
            mpBrkAnm->setFrame(mFrame);
        }
        if (!is_player) {
            fopAcM_onSwitch(this, mSwNo);
        }

        if (!mFixed) {
            if (mpEmitterOn == NULL) {
                mpEmitterOn = dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBUTTONON, &mEffPos, &shape_angle);
                mAlphaOn = 250;
                is_new = true;
                if (prmGetType() == 0) {
                    mFixTimer = l_HIO.mFixTime;
                    mFixed = 1;
                }
            } else if (mAlphaOn < 250) {
                mAlphaOn += 25;
                mpEmitterOn->setGlobalAlpha(mAlphaOn);
                fopAcM_onSwitch(this, mSwNo);
            }
        }

        if (mpEmitterOff != NULL) {
            mAlphaOff -= 25;
            mpEmitterOff->setGlobalAlpha(mAlphaOff);
            if (mAlphaOff == 0) {
                mpEmitterOff->becomeInvalidEmitter();
                mpEmitterOff = NULL;
            }
        }
    } else {
        if (mFrame > 0) {
            mFrame--;
            mpBrkAnm->setFrame(mFrame);
        }
        fopAcM_offSwitch(this, mSwNo);

        if (mpEmitterOff == NULL) {
            mpEmitterOff = dComIfGp_particle_set(dPa_name::ID_AK_SN_SIRENBUTTONOFF, &mEffPos, &shape_angle);
            mAlphaOff = 250;
        } else if (mAlphaOff < 250) {
            mAlphaOff += 25;
            mpEmitterOff->setGlobalAlpha(mAlphaOff);
        }

        if (mpEmitterOn != NULL) {
            mAlphaOn -= 25;
            mpEmitterOn->setGlobalAlpha(mAlphaOn);
            if (mAlphaOn == 0) {
                mpEmitterOn->becomeInvalidEmitter();
                mpEmitterOn = NULL;
            }
        }
    }

    switch (mEvState) {
    case 0:
        mTimer = 0;
        if (is_new && is_player) {
            mEvState = 1;
            mTimer = 30;
        }
        break;
    case 1:
        if (eventInfo.checkCommandDemoAccrpt()) {
            mEvState = 2;
            if (l_HIO.mDebug) {
                mTimer = l_HIO.mEventTime;
            }
        } else {
            fopAcM_orderPotentialEvent(this, 1, 0, 0);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
        break;
    case 2:
        mTimer--;
        if (mTimer <= 1) {
            dComIfGp_event_reset();
            mEvState = 0;
            fopAcM_onSwitch(this, mSwNo);
        }
        break;
    }

    if (mFixed) {
        mIsOn = 1;
        if (mFixTimer != 0) {
            mFixTimer--;
        } else {
            if (mpEmitterOn != NULL) {
                mAlphaOn -= 25;
                mpEmitterOn->setGlobalAlpha(mAlphaOn);
                if (mAlphaOn == 0) {
                    mpEmitterOn->becomeInvalidEmitter();
                    mpEmitterOn = NULL;
                }
            }
            if (mpEmitterOff != NULL) {
                mAlphaOff -= 25;
                mpEmitterOff->setGlobalAlpha(mAlphaOff);
                if (mAlphaOff == 0) {
                    mpEmitterOff->becomeInvalidEmitter();
                    mpEmitterOff = NULL;
                }
            }
            if (mFrame < mFrameMax + 5) {
                mFrame++;
                mpBrkAnm->setFrame(mFrame);
            }
        }
    }

    set_mtx();
    *mtx = &M_tmp_mtx;
    mWasOn = mIsOn;
    return TRUE;
}

/* 0000123C-000012F4       .text Draw__Q211daObjSwflat5Act_cFv */
BOOL daObjSwflat::Act_c::Draw() {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mpBrkAnm->entry(mpModel->getModelData());

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(mpModel);
    dComIfGd_setList();

    return TRUE;
}

/* 000012F4-000012FC       .text IsDelete__Q211daObjSwflat5Act_cFv */
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
