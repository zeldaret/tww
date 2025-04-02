/**
 * d_a_hookshot.cpp
 * Hookshot
 */

#include "d/actor/d_a_hookshot.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_procname.h"

#include "weak_data_1811.h" // IWYU pragma: keep

#include "assets/l_chainS3TCTEX__d_hookshot.h"
const u16 l_chainS3TCTEX__width = 32;
const u16 l_chainS3TCTEX__height = 32;

static Vec l_pos[] = {
    {-2.0f, 1.522254f, -0.0f},
    {-2.0f, 1.522254f, 7.0f},
    {2.0f, 1.522254f, -0.0f},
    {-3.5f, 0.0f, -1.5f},
    {-3.5f, 0.0f, 8.5f},
    {3.5f, 0.0f, -1.5f},
    {-2.0f, -1.522254f, -0.0f},
    {-2.0f, -1.522254f, 7.0f},
    {2.0f, -1.522254f, -0.0f},
    {2.0f, 1.522254f, 7.0f},
    {3.5f, 0.0f, 8.5f},
    {2.0f, -1.522254f, 7.0f},
};

static cXy l_texCoord[] = {
    {0.02736f, 0.041406f},
    {0.97264f, 0.041406f},
    {0.830848f, 0.40324f},
    {0.169152f, 0.40324f},
    {0.03125f, 0.0f},
    {0.96875f, 0.0f},
    {0.767857f, 0.494086f},
    {0.232143f, 0.494086f},
    {0.038462f, 0.48226f},
    {0.038462f, 0.983522f},
    {0.961538f, 0.48226f},
    {0.961538f, 0.983522f},
};

#include "assets/l_chainDL__d_hookshot.h"

#include "assets/l_matDL__d_hookshot.h"
l_matDL__d_hookshot(l_chainS3TCTEX);

/* 800F104C-800F12C8       .text draw__16daHookshot_shapeFv */
void daHookshot_shape::draw() {
    daHookshot_c* hookshot = reinterpret_cast<daHookshot_c*>(getUserArea());
    int chain_count = hookshot->getChainCnt();
    if (chain_count < 1) {
        return;
    }
    
    j3dSys.reinitGX();
    GXSetNumIndStages(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_INDEX8);
    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX8);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_F32, 0);
    GXSetArray(GX_VA_POS, &l_pos, sizeof(l_pos[0]));
    GXSetArray(GX_VA_TEX0, &l_texCoord, sizeof(l_texCoord[0]));
    dKy_GxFog_set();
    // Not sure why the size passed here is smaller than l_matDL's size in the symbol maps.
    GXCallDisplayList(&l_matDL, sizeof(l_matDL) - 0x08);
    GXSetTevColorS10(GX_TEVREG0, hookshot->tevStr.mColorC0);
    GXSetTevColor(GX_TEVREG1, hookshot->tevStr.mColorK0);
    GXSetCurrentMtx(0);
    
    cXyz chain_pos = daPy_getPlayerLinkActorClass()->getHookshotRootPos();
    cXyz chain_offset(
        7.0f * cM_scos(hookshot->shape_angle.x) * cM_ssin(hookshot->shape_angle.y),
        -7.0f * cM_ssin(hookshot->shape_angle.x),
        7.0f * cM_scos(hookshot->shape_angle.x) * cM_scos(hookshot->shape_angle.y)
    );
    s16 z = (g_Counter.mTimer << 0x0C) + ((g_Counter.mTimer >> 0x04) & 0xFFF);
    for (int i = 0; i <= chain_count; i++) {
        // Draw each individual link of the Hookshot's chain.
        mDoMtx_stack_c::transS(chain_pos);
        mDoMtx_stack_c::ZXYrotM(hookshot->shape_angle.x, hookshot->shape_angle.y, z);
        z += (((((g_Counter.mTimer + i) << 0x0C) + (g_Counter.mTimer >> ((i&0xF)+1) & 0xFFF))) & 0x1FFF) + 0x3000;
        mDoMtx_stack_c::revConcat(j3dSys.getViewMtx());
        GXLoadPosMtxImm(mDoMtx_stack_c::get(), 0);
        // Not sure why the size passed here is smaller than l_chainDL's size in the symbol maps.
        GXCallDisplayList(&l_chainDL, sizeof(l_chainDL) - 0x1A);
        chain_pos += chain_offset;
    }
    
    J3DShape::resetVcdVatCache();
}

/* 800F12C8-800F1324       .text draw__12daHookshot_cFv */
BOOL daHookshot_c::draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    dComIfGd_getOpaListP1()->entryImm(&mShape, 0);
    return TRUE;
}

/* 800F1324-800F1344       .text daHookshot_Draw__FP12daHookshot_c */
static BOOL daHookshot_Draw(daHookshot_c* i_this) {
    return i_this->draw();
}

/* 800F1344-800F13E8       .text daHookshot_rockLineCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
void daHookshot_rockLineCallback(fopAc_ac_c* hookshot_actor, dCcD_GObjInf* objInf, fopAc_ac_c* collided_actor, dCcD_GObjInf*) {
    daHookshot_c* i_this = (daHookshot_c*)hookshot_actor;
    f32 f31 = objInf->GetAtHitPosP()->abs2(i_this->current.pos);
    f32 f1 = i_this->getObjSightCrossPos()->abs2(i_this->current.pos);
    if (f1 > f31) {
        i_this->setObjSightCrossPos(objInf->GetAtHitPosP());
        if (fopAcM_CheckStatus(collided_actor, fopAcStts_UNK80000_e | fopAcStts_UNK200000_e | fopAcStts_UNK10000000_e)) {
            i_this->onObjHookFlg();
        } else {
            i_this->offObjHookFlg();
        }
    }
}

/* 800F13E8-800F14CC       .text procWait_init__12daHookshot_cFi */
BOOL daHookshot_c::procWait_init(BOOL playSe) {
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    fopAcM_SetParam(this, Mode_Wait);
    mCurrProcFunc = &daHookshot_c::procWait;
    mChainCnt = 0;
    current.pos = link->getHookshotRootPos();
    mCarryActorID = fpcM_ERROR_PROCESS_ID_e;
    mObjHookFlg = FALSE;
    if (playSe) {
        mDoAud_seStart(JA_SE_LK_HS_WIND_UP_FIN, &link->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }
    return TRUE;
}

/* 800F14CC-800F1990       .text procWait__12daHookshot_cFv */
BOOL daHookshot_c::procWait() {
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    current.pos = link->getHookshotRootPos();
    MtxP leftHandtx = link->getModelJointMtx(0x08); // cl_LhandA joint
    cMtx_copy(leftHandtx, mMtx);
    mMtx[0][3] = current.pos.x;
    mMtx[1][3] = current.pos.y;
    mMtx[2][3] = current.pos.z;
    mObjHookFlg = FALSE;
    
    if (fopAcM_GetParam(this) == Mode_Shot) {
        int angleY = link->getBodyAngleY() + link->shape_angle.y;
        int angleX = link->getBodyAngleX();
        mMoveVec.x = cM_ssin(angleY) * cM_scos(angleX);
        mMoveVec.y = -cM_ssin(angleX);
        mMoveVec.z = cM_scos(angleY) * cM_scos(angleX);
        mSightCps.ResetAtHit();
        mSightCps.OffAtNoTgHitInfSet();
        mSightCps.SetAtHitCallback(NULL);
        
        cXyz r1_3C = current.pos - mMoveVec * 60.0f;
        mLinChk.Set(&r1_3C, &current.pos, this);
        m2A0 = true;
        if (dComIfG_Bgsp()->LineCross(&mLinChk)) {
            if (dComIfG_Bgsp()->ChkPolyHSStick(mLinChk)) {
                fopAcM_SetParam(this, Mode_Pull);
                mShipRideFlg = false;
                mCurrProcFunc = &daHookshot_c::procPlayerPull;
                cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinChk);
                mHookAngle.x = cM_atan2s(triPla->GetNP()->y, triPla->GetNP()->absXZ());
                mHookAngle.y = cM_atan2s(-triPla->GetNP()->x, -triPla->GetNP()->z);
                mHookAngle.z = 0;
                mMoveVec = cXyz::Zero;
            } else {
                fopAcM_SetParam(this, Mode_Return);
                mCurrProcFunc = &daHookshot_c::procReturn;
            }
        } else {
            mMoveVec *= 7.0f;
            
            mSightCps.SetStartEnd(r1_3C, current.pos);
            mSightCps.SetR(5.0f);
            mSightCps.CalcAtVec();
            dComIfG_Ccsp()->Set(&mSightCps);
            // Using the inline breaks the match.
            // dComIfG_Ccsp()->SetMass(&mCps, 1);
            g_dComIfG_gameInfo.play.mCcS.SetMass(&mSightCps, 1);
            
            m2A3 = 0;
            mCurrProcFunc = &daHookshot_c::procShot;
        }
    } else {
        mSightCps.OnAtNoTgHitInfSet();
        mObjSightCrossPos.set(
            current.pos.x + cM_ssin(link->shape_angle.y) * 1500.0f * cM_scos(link->getBodyAngleX()),
            current.pos.y - cM_ssin(link->getBodyAngleX()) * 1500.0f,
            current.pos.z + cM_scos(link->shape_angle.y) * 1500.0f * cM_scos(link->getBodyAngleX())
        );
        mSightCps.SetStartEnd(current.pos, mObjSightCrossPos);
        mSightCps.SetR(5.0f);
        mSightCps.CalcAtVec();
        mSightCps.SetAtHitCallback(daHookshot_rockLineCallback);
        dComIfG_Ccsp()->Set(&mSightCps);
    }
    
    return TRUE;
}

/* 800F1990-800F2144       .text procShot__12daHookshot_cFv */
BOOL daHookshot_c::procShot() {
    /* Nonmatching */
}

/* 800F2144-800F247C       .text procPlayerPull__12daHookshot_cFv */
BOOL daHookshot_c::procPlayerPull() {
    /* Nonmatching */
}

/* 800F247C-800F26EC       .text procReturn__12daHookshot_cFv */
BOOL daHookshot_c::procReturn() {
    /* Nonmatching */
}

/* 800F26EC-800F2B54       .text execute__12daHookshot_cFv */
BOOL daHookshot_c::execute() {
    /* Nonmatching */
}

/* 800F2B54-800F2B74       .text daHookshot_Execute__FP12daHookshot_c */
static BOOL daHookshot_Execute(daHookshot_c* i_this) {
    return i_this->execute();
}

/* 800F2B74-800F2B7C       .text daHookshot_IsDelete__FP12daHookshot_c */
static BOOL daHookshot_IsDelete(daHookshot_c* i_this) {
    return TRUE;
}

/* 800F2B7C-800F2BF0       .text hookshot_delete__12daHookshot_cFv */
BOOL daHookshot_c::hookshot_delete() {
    if (mCarryActorID != fpcM_ERROR_PROCESS_ID_e) {
        fopAc_ac_c* hooked_actor = fopAcM_SearchByID(mCarryActorID);
        if (hooked_actor && fopAcM_CheckStatus(hooked_actor, fopAcStts_HOOK_CARRY_e)) {
            fopAcM_cancelHookCarryNow(hooked_actor);
            mCarryActorID = fpcM_ERROR_PROCESS_ID_e;
        }
    }
    return TRUE;
}

/* 800F2BF0-800F2C14       .text daHookshot_Delete__FP12daHookshot_c */
static BOOL daHookshot_Delete(daHookshot_c* i_this) {
    i_this->hookshot_delete();
    return TRUE;
}

static dCcD_SrcCps l_at_cps_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_HOOKSHOT,
        /* SrcObjAt  Atp     */ 0x01,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ dCcG_SE_HOOKSHOT,
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
    // cM3dGCpsS
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 5.0f,
    },
};

/* 800F2C14-800F2CC8       .text create__12daHookshot_cFv */
cPhs_State daHookshot_c::create() {
    fopAcM_SetupActor(this, daHookshot_c);
    
    mShape.setUserArea(reinterpret_cast<u32>(this));
    mLinChk.ClrSttsRoofOff();
    procWait_init(FALSE);
    gravity = -5.0f;
    
    mStts.Init(10, 0xFF, this);
    mSightCps.Set(l_at_cps_src);
    mSightCps.SetStts(&mStts);
    
    int roomNo = dComIfGp_roomControl_getStayNo();
    tevStr.mRoomNo = roomNo;
    mStts.SetRoomId(roomNo);
    current.roomNo = roomNo;
    
    return cPhs_COMPLEATE_e;
}

/* 800F3134-800F3154       .text daHookshot_Create__FP10fopAc_ac_c */
static cPhs_State daHookshot_Create(fopAc_ac_c* i_actor) {
    return reinterpret_cast<daHookshot_c*>(i_actor)->create();
}

static actor_method_class l_daHookshot_Method = {
    (process_method_func)daHookshot_Create,
    (process_method_func)daHookshot_Delete,
    (process_method_func)daHookshot_Execute,
    (process_method_func)daHookshot_IsDelete,
    (process_method_func)daHookshot_Draw,
};

actor_process_profile_definition g_profile_HOOKSHOT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0006,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_HOOKSHOT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daHookshot_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ 0x019E,
    /* Actor SubMtd */ &l_daHookshot_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
