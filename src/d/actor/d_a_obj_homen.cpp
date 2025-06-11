/**
 * d_a_obj_homen.cpp
 * Object - Wind Temple - Face stone Hookshot target
 */

#pragma sym off
#include "d/actor/d_a_obj_homen.h"
#pragma sym on
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_homen.h"
#include "f_op/f_op_actor_mng.h"

#include "weak_bss_936_to_1036.h" // IWYU pragma: keep
#include "weak_data_1811.h" // IWYU pragma: keep

namespace daObjHomen {

// This unnamed namespace holds the HIO class and its attributes which are unused in retail.
namespace {

struct Attr_c {
    /* 0x00 */ f32 field_0x00;
    /* 0x04 */ f32 field_0x04;
    /* 0x08 */ s16 field_0x08;
    /* 0x0A */ s16 field_0x0A;
    /* 0x0C */ s16 field_0x0C;
    /* 0x0E */ u8 field_0x0E[0x10 - 0x0E];
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ s16 field_0x1C;
    /* 0x1E */ s16 field_0x1E;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ s16 field_0x24;
    /* 0x26 */ u8 field_0x26[0x28 - 0x26];
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
#if VERSION > VERSION_DEMO
    /* 0x3C */ u8 field_0x3C[0x50 - 0x3C];
    /* 0x50 */ f32 field_0x50;
#endif
};  // Size: 0x54

const Attr_c L_attr = {
    -2.0f,
    -36.f,
    120,
    2000,
    3,
    {},
    0.6f,
    0.0f,
    0.0f,
    20,
    6,
    215.0f,
    1,
    {},
    57.0f,
    37.5f,
    105.0f,
    92.0f,
    200.0f,
#if VERSION > VERSION_DEMO
    {},
    25.0f,
#endif
};

#ifdef DEBUG
class Hio_c {
    
};

Hio_c L_hio;

static inline Hio_c& attr() {
    return L_hio;
}
#endif

}; // namespace

const char Act_c::M_arcname[] = "Homen";

const dCcD_SrcSph Act_c::M_sph_srcS = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_HOOKSHOT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 35.0f,
    },
};

const dCcD_SrcSph Act_c::M_sph_srcL = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_HOOKSHOT,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 50.0f,
    },
};

const dCcD_SrcCps Act_c::M_cps_srcL = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
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
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 135.0f,
    },
};

const dCcD_SrcCps Act_c::M_cps_srcS = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 1,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
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
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 45.0f,
    },
};

/* 000000EC-00000110       .text solidHeapCB__Q210daObjHomen5Act_cFP10fopAc_ac_c */
BOOL Act_c::solidHeapCB(fopAc_ac_c* i_this) {
    return ((Act_c*)i_this)->create_heap();
}

/* 00000110-000002B4       .text create_heap__Q210daObjHomen5Act_cFv */
bool Act_c::create_heap() {
    static int bdl_idx[] = {
        HOMEN_BDL_HOMEN1,
        HOMEN_BDL_HOMEN2,
    };
    static int dzb_idx[] = {
        HOMEN_DZB_HOMEN1,
        HOMEN_DZB_HOMEN2,
    };
    
    J3DModelData* mdl_data = (J3DModelData*)dComIfG_getObjectRes(M_arcname, bdl_idx[mType]);
    JUT_ASSERT(VERSION_SELECT(578, 615, 615, 615), mdl_data != NULL);
#if VERSION > VERSION_DEMO
    if (mdl_data != NULL)
#endif
    {
        mpModel = mDoExt_J3DModel__create(mdl_data, 0, 0x11000002);
    }
    
    init_mtx();
    
#if VERSION == VERSION_DEMO
    int r28 = 0;
#endif
    
    cBgD_t* bgw_data = (cBgD_t*)dComIfG_getObjectRes(M_arcname, dzb_idx[mType]);
    JUT_ASSERT(VERSION_SELECT(590, 628, 628, 628), bgw_data != NULL);
#if VERSION > VERSION_DEMO
    if (bgw_data != NULL)
#endif
    {
        mpBgW = new dBgW();
#if VERSION == VERSION_DEMO
        if (mpBgW != NULL && mpBgW->Set(bgw_data, cBgW::MOVE_BG_e, &mMtx)) {
            r28 |= 1;
        }
#else
        if (mpBgW != NULL && mpBgW->Set(bgw_data, cBgW::MOVE_BG_e, &mMtx) == true) {
            return false;
        }
#endif
    }
    
#if VERSION == VERSION_DEMO
    bool ret = false;
    if (mdl_data != NULL && r28 == 0) {
        ret = true;
    };
    return ret;
#else
    return mdl_data != NULL && mpModel != NULL && mpBgW != NULL;
#endif
}

/* 000002B4-000005B0       .text _create__Q210daObjHomen5Act_cFv */
cPhs_State Act_c::_create() {
    fopAcM_SetupActor(this, Act_c);
    
    if (param_get_sw() != 0xFF && is_switch() == true) {
        return cPhs_ERROR_e;
    }
    
    cPhs_State phase_state = dComIfG_resLoad(&mPhase, M_arcname);
    
    mType = param_get_arg0() & 1;
    
    if (phase_state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(this, &Act_c::solidHeapCB, 0)) {
            fopAcM_SetMtx(this, this->mpModel->getBaseTRMtx());
            dComIfG_Bgsp()->Regist(mpBgW, this);
            mpBgW->SetCrrFunc(NULL);
            
            struct daObjHomen__cullbox {
                /* 0x0 */ Vec mMin;
                /* 0xC */ Vec mMax;
            };
            static daObjHomen__cullbox culling_dat[] = {
                {-300.0f, -30.0f, -100.0f, 300.0f, 600.0f, 300.0f},
                {-100.0f, -30.0f, -100.0f, 100.0f, 250.0f, 120.0f},
            };
            fopAcM_setCullSizeBox(this,
                culling_dat[mType].mMin.x, culling_dat[mType].mMin.y, culling_dat[mType].mMin.z,
                culling_dat[mType].mMax.x, culling_dat[mType].mMax.y, culling_dat[mType].mMax.z
            );
            
            mSphStts.Init(0, 0xFF, this);
            if (mType == 0) {
                mSph.Set(M_sph_srcL);
            } else {
                mSph.Set(M_sph_srcS);
            }
            
            mSph.SetStts(&mSphStts);
            mSph.SetTgVec((cXyz&)cXyz::Zero);
            mSph.OnTgNoHitMark();
            
            for (int i = 0; i < 2; i++) {
                mCpsStts[i].Init(100, 0xFF, this);
                if (mType == 0) {
                    mCps[i].Set(M_cps_srcL);
                } else {
                    mCps[i].Set(M_cps_srcS);
                }
                mCps[i].SetStts(&mCpsStts[i]);
                
                static f32 at_col_radius[] = {
                    135.0f,
                    45.0f,
                };
                mCpsS[i].mStart = current.pos;
                mCpsS[i].mEnd = current.pos;
                mCpsS[i].mRadius = at_col_radius[mType & 1];
            }
            
            process_init(0);
            if (param_get_enemy() != 0xF) {
                fopAcM_SetGroup(this, fopAc_ENEMY_e);
            }
            
            mEventIdx = dComIfGp_evmng_getEventIdx("homen_down");
            mHookshotID = fpcM_ERROR_PROCESS_ID_e;
        } else {
            phase_state = cPhs_ERROR_e;
        }
    }
    
    return phase_state;
}

/* 000011A4-00001230       .text _delete__Q210daObjHomen5Act_cFv */
bool Act_c::_delete() {
    dComIfG_resDelete(&mPhase, M_arcname);
    if (
#if VERSION > VERSION_DEMO
        heap != NULL &&
#endif
        mpBgW != NULL &&
        mpBgW->ChkUsed()
    ) {
        dComIfG_Bgsp()->Release(mpBgW);
    }
    return true;
}

/* 00001230-00001374       .text set_mtx__Q210daObjHomen5Act_cFv */
void Act_c::set_mtx() {
    if (mType == 0 && field_0x7EC == 1) {
        cXyz sp14(0.0f, 0.0f, -200.0f);
        cXyz sp08(0.0f, 0.0f, 200.0f);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::transM(sp08);
        mDoMtx_stack_c::ZrotM(shape_angle.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::XrotM(shape_angle.x);
        mDoMtx_stack_c::transM(sp14);
    } else {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZrotM(shape_angle.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::XrotM(shape_angle.x);
    }
    
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), mMtx);
}

/* 00001374-000013D0       .text init_mtx__Q210daObjHomen5Act_cFv */
void Act_c::init_mtx() {
    mpModel->setBaseScale(scale);
    set_mtx();
    mpModel->calc();
}

/* 000013D0-00001498       .text exe_event__Q210daObjHomen5Act_cFv */
void Act_c::exe_event() {
    switch (field_0x7F6) {
    case 1:
        if (eventInfo.mCommand == dEvtCmd_INDEMO_e) {
            field_0x7F6 = 2;
        } else {
            fopAcM_orderOtherEventId(this, field_0x7F4);
            eventInfo.onCondition(dEvtCnd_UNK2_e);
        }
        break;
    case 2:
        if (dComIfGp_evmng_endCheck(field_0x7F4)) {
            dComIfGp_event_reset();
            field_0x7F4 = -1;
            field_0x7F6 = 0;
        }
        break;
    }
}

/* 00001498-0000159C       .text make_enemy__Q210daObjHomen5Act_cFv */
void Act_c::make_enemy() {
    struct enemy_dat_s {
        /* 0x00 */ s16 proc_name;
        /* 0x04 */ u32 param;
    };  // Size: 0x08
    static const enemy_dat_s make_enemy_dat[] = {
        /* 0x0 */ { PROC_BK, 0xFFFF0000 },
        /* 0x1 */ { PROC_BK, 0xFFFF0020 },
        /* 0x2 */ { PROC_BK, 0xFFFF0040 },
        /* 0x3 */ { PROC_BK, 0xFFFF0060 },
        /* 0x4 */ { PROC_BK, 0xFFFF0080 },
        /* 0x5 */ { PROC_BK, 0xFFFF00A0 },
        /* 0x6 */ { PROC_CC, 0xFF000000 },
        /* 0x7 */ { PROC_CC, 0xFF000100 },
        /* 0x8 */ { PROC_CC, 0xFF000200 },
        /* 0x9 */ { PROC_CC, 0xFF000300 },
        /* 0xA */ { PROC_CC, 0xFF000400 },
    };
    
    int enemy_idx = param_get_enemy();
    if (enemy_idx != 0xF && enemy_idx < ARRAY_SIZE(make_enemy_dat)) {
#if VERSION == VERSION_DEMO
        static cXyz y_offset[2] = {
            cXyz(0.0f, 300.0f, 350.0f),
            cXyz(0.0f, 0.0f, 0.0f),
        };
#else
        cXyz y_offset[2] = {
            cXyz(0.0f, 300.0f, 350.0f),
            cXyz(0.0f, 0.0f, 25.0f),
        };
#endif
        cXyz offset;
        cMtx_multVec(mMtx, &y_offset[mType & 1], &offset);
        
        fpc_ProcID enemy_id = fopAcM_create(
            make_enemy_dat[enemy_idx].proc_name,
            make_enemy_dat[enemy_idx].param,
            &offset, fopAcM_GetRoomNo(this)
        );
        mEnemyID = enemy_id;
        if (enemy_id == fpcM_ERROR_PROCESS_ID_e) {
            fopAcM_SetGroup(this, fopAc_ACTOR_e);
        }
    }
}

/* 0000159C-00001658       .text make_item__Q210daObjHomen5Act_cFv */
void Act_c::make_item() {
    csXyz sp08(0, 0, 0);
    cXyz sp10(1.0f, 1.0f, 1.0f);
    if (param_get_item() != 0x3F) {
        fopAcM_createItemFromTable(
            &current.pos,
            param_get_item(), param_get_itembit(),
            fopAcM_GetRoomNo(this), daItemType_0_e,
            &sp08, daItemAct_1_e, &sp10
        );
    }
}

/* 00001658-00001698       .text manage_item_timer__Q210daObjHomen5Act_cFv */
void Act_c::manage_item_timer() {
    if (mItemTimer <= 0) return;
    mItemTimer--;
    if (mItemTimer == 0) {
        make_item();
    }
}

/* 00001698-000016D8       .text manage_enemy_timer__Q210daObjHomen5Act_cFv */
void Act_c::manage_enemy_timer() {
    if (mEnemyTimer <= 0) return;
    mEnemyTimer--;
    if (mEnemyTimer == 0) {
        make_enemy();
    }
}

/* 000016D8-00001864       .text get_norse_offset__Q210daObjHomen5Act_cFP4cXyzi */
void Act_c::get_norse_offset(cXyz* param_1, int param_2) {
    static cXyz offset_data0[] = {
        cXyz(0.0f, 453.0f, 140.0f),
        cXyz(0.0f, 181.5f, 48.0f),
    };
    static cXyz offset_data1[] = {
        cXyz(0.0f, 453.0f, 190.0f),
        cXyz(0.0f, 181.5f, 68.0f),
    };
    static cXyz* offset_table[] = {
        offset_data0,
        offset_data1,
    };
    *param_1 = offset_table[param_2 & 1][mType];
}

/* 00001864-000018C8       .text get_norse_point__Q210daObjHomen5Act_cFP4cXyzi */
void Act_c::get_norse_point(cXyz* param_1, int param_2) {
    cXyz sp14;
    cXyz sp08;
    get_norse_offset(&sp14, param_2);
    cMtx_multVec(mMtx, &sp14, &sp08);
    *param_1 = sp08;
}

/* 000018C8-000018D8       .text process_free_init__Q210daObjHomen5Act_cFv */
BOOL Act_c::process_free_init() {
    mEnemyID = fpcM_ERROR_PROCESS_ID_e;
    return TRUE;
}

/* 000018D8-0000196C       .text process_free_main__Q210daObjHomen5Act_cFv */
void Act_c::process_free_main() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    if (player->checkEquipHeavyBoots()) {
        fopAcM_OnStatus(this, fopAcStts_UNK80000_e);
        fopAcM_OffStatus(this, fopAcStts_UNK200000_e);
    } else {
        fopAcM_OnStatus(this, fopAcStts_UNK200000_e);
        fopAcM_OffStatus(this, fopAcStts_UNK80000_e);
    }
    if (fopAcM_checkHookCarryNow(this)) {
        process_init(1);
    }
    set_co_collision();
}

/* 0000196C-00001AFC       .text process_wait_falldown_init__Q210daObjHomen5Act_cFv */
BOOL Act_c::process_wait_falldown_init() {
    fopAcM_cancelHookCarryNow(this);
    mEnemyTimer = 6;
    mItemTimer = 20;
    field_0x7DA = 0;
    // attr(); // Debug only
    dComIfG_Bgsp()->Release(mpBgW);
    mpBgW = NULL;
    
    static int vibe_level_1st[] = {
        2, 1,
    };
    dComIfGp_getVibration().StartShock(vibe_level_1st[mType & 1], -0x11, cXyz(0.0f, 1.0f, 0.0f));
    
    if (mType != 0) {
        field_0x7FC = current.pos;
        if (mHookshotID != fpcM_ERROR_PROCESS_ID_e) {
            fopAc_ac_c* hookshot = fopAcM_SearchByID(mHookshotID);
            if (hookshot != NULL) {
                Mtx sp3C;
                cXyz sp30;
                cXyz sp24;
                get_norse_offset(&sp30, 1);
                mDoMtx_stack_c::YrotS(shape_angle.y);
                MTXCopy(mDoMtx_stack_c::get(), sp3C);
                cMtx_multVec(sp3C, &sp30, &sp24);
                field_0x7FC = hookshot->current.pos - sp24;
            }
        }
    }
    
    if (mType == 0) {
        dComIfGs_onEventBit(0x3410);
    }
    
    return TRUE;
}

/* 00001AFC-00001BA4       .text process_wait_falldown_main__Q210daObjHomen5Act_cFv */
void Act_c::process_wait_falldown_main() {
    if (field_0x7DA < 3) {
        cLib_addCalc2(&current.pos.x, field_0x7FC.x, 0.5f, 20.0f);
        cLib_addCalc2(&current.pos.y, field_0x7FC.y, 0.5f, 20.0f);
        cLib_addCalc2(&current.pos.z, field_0x7FC.z, 0.5f, 20.0f);
        field_0x7DA++;
    } else {
        process_init(2);
    }
    
    set_co_collision();
}

/* 00001BA4-00001C84       .text process_falldown_init__Q210daObjHomen5Act_cFv */
BOOL Act_c::process_falldown_init() {
    gravity = -2.0f;
    maxFallSpeed = -36.0f;
    cXyz gndPos(current.pos);
    gndPos.y += 100.0f;
    mGndChk.SetPos(&gndPos);
    mGndChk.SetActorPid(fopAcM_GetID(this));
    mGroundY = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if (mType == 0) {
        field_0x7D6 = 90;
    } else {
        field_0x7D6 = 120;
    }
    field_0x7DC = cM_rndFX(3072.0f);
    return TRUE;
}

/* 00001C84-00001EC8       .text process_falldown_main__Q210daObjHomen5Act_cFv */
void Act_c::process_falldown_main() {
    set_at_collision();
    cXyz sp34;
    get_norse_point(&sp34, 0);
    
    if (mType == 0 && field_0x7EC == 0) {
        cXyz sp28(0.0f, 0.0f, 0.0f);
        cXyz sp1C;
        cMtx_multVec(mMtx, &sp28, &sp1C);
        if (sp1C.y - 1.0f <= mGroundY) {
            field_0x7EC = 1;
            gravity = 0.0f;
            speed.setall(0.0f);
            speedF = 0.0f;
        }
    } else if (current.pos.y < mGroundY) {
        gravity = 0.0f;
        speed.setall(0.0f);
        speedF = 0.0f;
    }
    
    if (sp34.y < mGroundY) {
        fpc_ProcID smoke_id = fopAcM_createChild(
            PROC_Obj_Homensmk,
            fopAcM_GetID(this),
            field_0x7EC << 1 | mType,
            &current.pos,
            fopAcM_GetRoomNo(this),
            &shape_angle
        );
        mSmokeID = smoke_id;
        if (smoke_id != fpcM_ERROR_PROCESS_ID_e) {
            static int vibe_level_2nd[] = {
                6, 4,
            };
            dComIfGp_getVibration().StartShock(vibe_level_2nd[mType & 1], -0x11, cXyz(0.0f, 1.0f, 0.0f));
            gravity = 0.0f;
            speed.setall(0.0f);
            speedF = 0.0f;
            field_0x7D6 = 0;
            field_0x7D4 = 0;
            process_init(3);
        }
    } else {
        if (field_0x7EC == 0) {
            cLib_addCalcAngleS2(&shape_angle.z, field_0x7DC, 20, 0x1000);
            cLib_addCalcAngleS2(&shape_angle.y, field_0x7D8 + 0x8000, 10, 0x1000);
        }
    }
    
    if (gravity != 0.0f) {
        static f32 speed_table[] = {
            20.0f, 12.0f,
        };
        speedF = speed_table[mType & 1];
    }
}

/* 00001EC8-00001FA8       .text process_wait_init__Q210daObjHomen5Act_cFv */
BOOL Act_c::process_wait_init() {
    on_switch();
    field_0x7DE = 1;
    if (mType == 0) {
        mDoAud_seStart(JA_SE_OBJ_MASK_S_BREAK, &current.pos);
    } else {
        mDoAud_seStart(JA_SE_OBJ_MASK_L_BREAK, &current.pos);
    }
    return TRUE;
}

/* 00001FA8-00001FEC       .text process_wait_main__Q210daObjHomen5Act_cFv */
void Act_c::process_wait_main() {
    if (field_0x7DE > 0) {
        field_0x7DE--;
        if (field_0x7DE == 0) {
            process_init(4);
        }
    }
}

/* 00001FEC-00002054       .text process_none_init__Q210daObjHomen5Act_cFv */
BOOL Act_c::process_none_init() {
    if (mType == 0) {
        mDoAud_seStart(JA_SE_READ_RIDDLE_1);
    }
    return TRUE;
}

/* 00002054-000020AC       .text process_none_main__Q210daObjHomen5Act_cFv */
void Act_c::process_none_main() {
    if (mEnemyID != fpcM_ERROR_PROCESS_ID_e) {
        fopAc_ac_c* enemy;
        if (!fopAcM_SearchByID(mEnemyID, &enemy)) {
            mEnemyID = fpcM_ERROR_PROCESS_ID_e;
            fopAcM_delete(this);
        }
    }
}

/* 000020AC-000021C4       .text process_init__Q210daObjHomen5Act_cFs */
BOOL Act_c::process_init(s16 state) {
    static ProcInitFunc init_table[] = {
        &Act_c::process_free_init,
        &Act_c::process_wait_falldown_init,
        &Act_c::process_falldown_init,
        &Act_c::process_wait_init,
        &Act_c::process_none_init,
    };
    if (state >= 0 && state < 5) {
        if ((this->*init_table[state])()) {
            mState = state;
            return TRUE;
        }
    }
    return FALSE;
}

/* 000021C4-000022A8       .text process_main__Q210daObjHomen5Act_cFv */
void Act_c::process_main() {
    static ProcMainFunc main_table[] = {
        &Act_c::process_free_main,
        &Act_c::process_wait_falldown_main,
        &Act_c::process_falldown_main,
        &Act_c::process_wait_main,
        &Act_c::process_none_main,
    };
    if (mState >= 0 && mState < 5) {
        (this->*main_table[mState])();
    }
}

/* 000022A8-000023C8       .text set_co_collision__Q210daObjHomen5Act_cFv */
void Act_c::set_co_collision() {
    if (mSph.ChkTgHit()) {
        cCcD_Obj* hitObj = mSph.GetTgHitObj();
        daPy_py_c* player = daPy_getPlayerActorClass();
        if (hitObj && hitObj->ChkAtType(AT_TYPE_HOOKSHOT)) {
            field_0x7D8 = player->shape_angle.y;
            fopAc_ac_c* hookshot = mSph.GetTgHitAc();
            mHookshotID = fopAcM_GetID(hookshot);
            if (mType == 0) {
                dComIfGs_onEventBit(0x3880);
            }
        }
        mSph.ClrTgHit();
    } else {
        f32 sp08[] = {
            105.0f, 57.0f,
        };
        cXyz sp10;
        get_norse_point(&sp10, 0);
        mSph.SetC(sp10);
        mSph.SetR(sp08[mType & 1]);
        dComIfG_Ccsp()->Set(&mSph);
    }
}

/* 000023C8-00002728       .text set_at_collision__Q210daObjHomen5Act_cFv */
void Act_c::set_at_collision() {
    static cXyz at_offset[][2][2] = {
        {
            {
                cXyz(-120.0f, 30.0f, 140.0f),
                cXyz(-120.0f, 550.0f, 140.0f),
            },
            {
                cXyz(120.0f, 30.0f, 140.0f),
                cXyz(120.0f, 550.0f, 140.0f),
            },
        },
        {
            {
                cXyz(-45.0f, 20.0f, 80.0f),
                cXyz(-45.0f, 190.0f, 80.0f),
            },
            {
                cXyz(45.0f, 20.0f, 80.0f),
                cXyz(45.0f, 190.0f, 80.0f),
            },
        },
    };
    
    for (int i = 0; i < 2; i++) {
        cXyz sp74;
        cXyz sp68;
        
        sp74 = at_offset[mType & 1][i][0];
        cMtx_multVec(mMtx, &sp74, &sp68);
        mCpsS[i].mStart = sp68;
        
        sp74 = at_offset[mType & 1][i][1];
        cMtx_multVec(mMtx, &sp74, &sp68);
        mCpsS[i].mEnd = sp68;
        
        mCps[i].cM3dGCps::Set(mCpsS[i]);
        dComIfG_Ccsp()->Set(&mCps[i]);
    }
}

/* 00002728-00002810       .text adjust_hookshot__Q210daObjHomen5Act_cFv */
void Act_c::adjust_hookshot() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    if (!player->checkEquipHeavyBoots()) {
        if (mHookshotID != fpcM_ERROR_PROCESS_ID_e && fopAcM_SearchByID(mHookshotID) != NULL) {
            Mtx sp24;
            cXyz sp18;
            cXyz sp0C;
            get_norse_offset(&sp18, 1);
            mDoMtx_stack_c::YrotS(shape_angle.y);
            MTXCopy(mDoMtx_stack_c::get(), sp24);
            cMtx_multVec(sp24, &sp18, &sp0C);
            player->setHookshotCarryOffset(fopAcM_GetID(this), &sp0C);
            mHookshotID = fpcM_ERROR_PROCESS_ID_e;
        }
    }
}

/* 00002810-000028E0       .text _execute__Q210daObjHomen5Act_cFv */
bool Act_c::_execute() {
    adjust_hookshot();
    exe_event();
    manage_item_timer();
    manage_enemy_timer();
    process_main();
    if (mpBgW != NULL) {
        mpBgW->Move();
    }
    field_0x7D4 += field_0x7D6;
    if (field_0x7D4 > 2000) {
        field_0x7D4 = 2000;
    }
    shape_angle.x += field_0x7D4;
    if (shape_angle.x >= 0x5000) {
        shape_angle.x = 0x5000;
        field_0x7D4 = 0;
        field_0x7D6 = 0;
    }
    fopAcM_calcSpeed(this);
    fopAcM_posMove(this, NULL);
    set_mtx();
    
    return true;
}

/* 000028E0-00002954       .text _draw__Q210daObjHomen5Act_cFv */
bool Act_c::_draw() {
    if (mState != 4 && mState != 3) {
        g_env_light.settingTevStruct(TEV_TYPE_BG0, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(mpModel, &tevStr);
        mDoExt_modelUpdateDL(mpModel);
    }
    return true;
}

namespace {
/* 00002954-00002974       .text Mthd_Create__Q210daObjHomen27@unnamed@d_a_obj_homen_cpp@FPv */
cPhs_State Mthd_Create(void* i_this) {
    return ((Act_c*)i_this)->_create();
}

/* 00002974-00002998       .text Mthd_Delete__Q210daObjHomen27@unnamed@d_a_obj_homen_cpp@FPv */
BOOL Mthd_Delete(void* i_this) {
    return ((Act_c*)i_this)->_delete();
}

/* 00002998-000029BC       .text Mthd_Execute__Q210daObjHomen27@unnamed@d_a_obj_homen_cpp@FPv */
BOOL Mthd_Execute(void* i_this) {
    return ((Act_c*)i_this)->_execute();
}

/* 000029BC-000029E0       .text Mthd_Draw__Q210daObjHomen27@unnamed@d_a_obj_homen_cpp@FPv */
BOOL Mthd_Draw(void* i_this) {
    return ((Act_c*)i_this)->_draw();
}

/* 000029E0-000029E8       .text Mthd_IsDelete__Q210daObjHomen27@unnamed@d_a_obj_homen_cpp@FPv */
BOOL Mthd_IsDelete(void* i_this) {
    return TRUE;
}

static actor_method_class Mthd_Table = {
    (process_method_func)Mthd_Create,
    (process_method_func)Mthd_Delete,
    (process_method_func)Mthd_Execute,
    (process_method_func)Mthd_IsDelete,
    (process_method_func)Mthd_Draw,
};
}; // namespace

}; // namespace daObjHomen

actor_process_profile_definition g_profile_Obj_Homen = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Obj_Homen,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObjHomen::Act_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Obj_Homen,
    /* Actor SubMtd */ &daObjHomen::Mthd_Table,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
