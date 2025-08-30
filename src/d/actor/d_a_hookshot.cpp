/**
 * d_a_hookshot.cpp
 * Item - Hookshot
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_hookshot.h"
#include "d/d_com_inf_game.h"
#include "m_Do/m_Do_mtx.h"
#include "SSystem/SComponent/c_counter.h"
#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_ship.h" // IWYU pragma: keep
#include "d/d_procname.h"
#include "d/d_priority.h"

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
    
#if VERSION > VERSION_JPN
    j3dSys.reinitGX();
    GXSetNumIndStages(0);
#endif
    
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
    
#if VERSION > VERSION_JPN
    J3DShape::resetVcdVatCache();
#endif
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
#if VERSION == VERSION_USA
        if (fopAcM_CheckStatus(collided_actor, fopAcStts_UNK80000_e | fopAcStts_UNK200000_e | fopAcStts_UNK10000000_e))
#else
        if (fopAcM_CheckStatus(collided_actor, fopAcStts_UNK80000_e | fopAcStts_UNK200000_e))
#endif
        {
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
        s16 angleY = link->getBodyAngleY() + link->shape_angle.y;
        s16 angleX = link->getBodyAngleX();
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
            dComIfG_Ccsp_SetMass(&mSightCps, 1);
            
            m2A3 = false;
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
    if (fopAcM_GetParam(this) == Mode_Return) {
        mCurrProcFunc = &daHookshot_c::procReturn;
        return TRUE;
    }
    
    if (mSightCps.ChkAtHit()) {
        fopAc_ac_c* hit_ac = mSightCps.GetAtHitAc();
        if (hit_ac) {
            mCarryActorID = fopAcM_GetID(hit_ac);
            if (fopAcM_CheckStatus(hit_ac, fopAcStts_UNK80000_e)) {
                fopAcM_setHookCarryNow(hit_ac);
                mCarryOffset = hit_ac->current.pos - current.pos;
                fopAcM_seStartCurrent(this, JA_SE_LK_HS_SPIKE, 0);
#if VERSION > VERSION_DEMO
                dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
#endif
            } else if (fopAcM_CheckStatus(hit_ac, fopAcStts_UNK200000_e)) {
                current.pos = *mSightCps.GetAtHitPosP();
                mCarryOffset = current.pos - hit_ac->current.pos;
                m2A4 = hit_ac->shape_angle.y;
                mHookAngle.x = shape_angle.x;
                mHookAngle.y = shape_angle.y;
                mHookAngle.z = 0;
                mMoveVec = cXyz::Zero;
                fopAcM_SetParam(this, Mode_Pull);
                mShipRideFlg = false;
                mCurrProcFunc = &daHookshot_c::procPlayerPull;
                fopAcM_seStartCurrent(this, JA_SE_LK_HS_SPIKE, 0);
#if VERSION > VERSION_DEMO
                dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
#endif
                return TRUE;
            } else if (mSightCps.ChkAtShieldHit()) {
                fopAcM_seStartCurrent(this, JA_SE_LK_HS_REBOUND, 0x20);
            }
        }
        fopAcM_SetParam(this, Mode_Return);
        mCurrProcFunc = &daHookshot_c::procReturn;
    } else if (m2A3 || current.pos.abs(daPy_getPlayerLinkActorClass()->getHookshotRootPos()) >= 1500.0f) {
        if (m2A3) {
            if (m2A6 == dPa_name::ID_SCENE_825F) {
                dComIfGp_particle_setP1(m2A6, &current.pos);
            } else {
                dComIfGp_particle_setP1(m2A6, &current.pos, &m2BA);
            }
            fopAcM_seStartCurrent(this, JA_SE_LK_HS_REBOUND, mMtrlSndId);
        }
        fopAcM_SetParam(this, Mode_Return);
        mCurrProcFunc = &daHookshot_c::procReturn;
    } else {
        cXyz sp8C = current.pos + (mMoveVec * 15.0f);
        mLinChk.Set(&current.pos, &sp8C, this);
        if (dComIfG_Bgsp()->LineCross(&mLinChk)) {
            sp8C = mLinChk.GetLinP()->GetEnd();
            if (dComIfG_Bgsp()->ChkPolyHSStick(mLinChk)) {
                fopAcM_SetParam(this, Mode_Pull);
                mShipRideFlg = false;
                mCurrProcFunc = &daHookshot_c::procPlayerPull;
                
                cM3dGPla* plane = dComIfG_Bgsp()->GetTriPla(mLinChk);
                mHookAngle.x = cM_atan2s(plane->GetNP()->y, plane->GetNP()->absXZ());
                mHookAngle.y = cM_atan2s(-plane->GetNP()->x, -plane->GetNP()->z);
                mHookAngle.z = 0;
                mMoveVec = cXyz::Zero;
                
                fopAcM_seStartCurrent(this, JA_SE_LK_HS_SPIKE, dComIfG_Bgsp()->GetMtrlSndId(mLinChk));
#if VERSION > VERSION_DEMO
                dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
#endif
            } else {
                cM3dGPla* plane = dComIfG_Bgsp()->GetTriPla(mLinChk);
                cM3d_CalcVecZAngle(*plane->GetNP(), &m2BA);
                if (
                    strcmp(dComIfGp_getStartStageName(), "kazeB") == 0 &&
                    (
                        (sp8C.y < 950.0f && cBgW_CheckBGround(dComIfG_Bgsp()->GetTriPla(mLinChk)->GetNP()->y)) ||
                        dComIfG_Bgsp()->GetAttributeCode(mLinChk) == dBgS_Attr_SAND_e
                    )
                ) {
                    m2A6 = dPa_name::ID_SCENE_825F;
                } else {
                    m2A6 = dPa_name::ID_COMMON_PURPLE_HIT;
                }
                mMtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mLinChk);
                m2A3 = true;
            }
        }
        
        mSightCps.SetStartEnd(current.pos, sp8C);
        mSightCps.SetR(5.0f);
        mSightCps.CalcAtVec();
        dComIfG_Ccsp()->Set(&mSightCps);
        dComIfG_Ccsp_SetMass(&mSightCps, 1);
        current.pos = sp8C;
    }

    return TRUE;
}

/* 800F2144-800F247C       .text procPlayerPull__12daHookshot_cFv */
BOOL daHookshot_c::procPlayerPull() {
    fopAc_ac_c* carry_actor = NULL;
    if (mCarryActorID != fpcM_ERROR_PROCESS_ID_e) {
        carry_actor = fopAcM_SearchByID(mCarryActorID);
        if (carry_actor == NULL || fopAcM_GetParam(this) == Mode_Return) {
            mCurrProcFunc = &daHookshot_c::procReturn;
            mCarryActorID = fpcM_ERROR_PROCESS_ID_e;
            return TRUE;
        }
        if (carry_actor->shape_angle.y != m2A4) {
            mDoMtx_stack_c::YrotS(carry_actor->shape_angle.y - m2A4);
            cXyz sp4C;
            mDoMtx_stack_c::multVec(&mCarryOffset, &sp4C);
            mCarryOffset = sp4C;
            m2A4 = carry_actor->shape_angle.y;
        }
        current.pos = carry_actor->current.pos + mCarryOffset;
    } else {
        if (fopAcM_GetParam(this) == Mode_Return || !dComIfG_Bgsp()->ChkPolySafe(mLinChk)) {
            mCurrProcFunc = &daHookshot_c::procReturn;
            return TRUE;
        }
        if (dComIfG_Bgsp()->ChkMoveBG(mLinChk)) {
            dComIfG_Bgsp()->MoveBgTransPos(mLinChk, true, &current.pos, &mHookAngle, NULL);
        }
    }
    
    cXyz sp40 = current.pos - daPy_getPlayerLinkActorClass()->getHookshotRootPos();
    f32 f1 = sp40.abs();
    int r5 = f1 / 7.0f;
    if (r5 >= 1) {
        r5 = (r5 > mChainCnt ? r5 - mChainCnt : 0);
        int iVar6;
        if (mChainCnt <= 9) {
            iVar6 = r5 + mChainCnt;
        } else {
            iVar6 = r5 + 9;
        }
        mChainCnt -= iVar6;
        mMoveVec = sp40 * ((iVar6 * 7.0f) / f1);
    } else {
        mChainCnt = 0;
    }
    
    if (mChainCnt <= 0) {
        if (carry_actor && carry_actor == dComIfGp_getShipActor()) {
            mShipRideFlg = true;
        }
        procWait_init(TRUE);
    }
    
    return TRUE;
}

/* 800F247C-800F26EC       .text procReturn__12daHookshot_cFv */
BOOL daHookshot_c::procReturn() {
    fopAc_ac_c* carry_actor;
    if (mCarryActorID != fpcM_ERROR_PROCESS_ID_e) {
        carry_actor = fopAcM_SearchByID(mCarryActorID);
        if (carry_actor == NULL || !fopAcM_checkHookCarryNow(carry_actor)) {
            mCarryActorID = fpcM_ERROR_PROCESS_ID_e;
            carry_actor = NULL;
        }
    } else {
        carry_actor = NULL;
    }
    
    if (mChainCnt <= 9) {
        if (carry_actor) {
            fopAcM_cancelHookCarryNow(carry_actor);
        }
        procWait_init(TRUE);
        procWait();
    } else {
        cXyz sp4C = current.pos - daPy_getPlayerLinkActorClass()->getHookshotRootPos();
        f32 f1 = sp4C.abs();
        if ((int)(f1 / 7.0f) <= 9) {
            if (carry_actor != NULL) {
                fopAcM_cancelHookCarryNow(carry_actor);
            }
            procWait_init(TRUE);
            procWait();
        } else {
            mChainCnt -= 9;
            current.pos -= sp4C * (63.0f / f1);
            
            if (carry_actor) {
                carry_actor->current.pos = current.pos + mCarryOffset;
                cXyz sp40(
                    carry_actor->current.pos.x,
                    carry_actor->current.pos.y + 100.0f,
                    carry_actor->current.pos.z
                );
                sp40.y += 100.0f;
                mGndChk.SetPos(&sp40);
                f32 ground_y = dComIfG_Bgsp()->GroundCross(&mGndChk);
                if (ground_y > carry_actor->current.pos.y) {
                    carry_actor->current.pos.y = ground_y;
                    mCarryOffset.y = ground_y - current.pos.y;
                }
            }
        }
    }
    
    return TRUE;
}

/* 800F26EC-800F2B54       .text execute__12daHookshot_cFv */
BOOL daHookshot_c::execute() {
    daPy_lk_c* link = daPy_getPlayerLinkActorClass();
    
    if (fopAcM_GetParam(this) != Mode_Wait) {
        mDoAud_seStart(JA_SE_LK_HS_CHAIN, &link->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        if (fopAcM_GetParam(this) != Mode_Shot) {
            mDoAud_seStart(JA_SE_LK_HS_WIND_UP, &link->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
        }
    }
    
    if (mCurrProcFunc != NULL) {
        (this->*mCurrProcFunc)();
    }
    
    eyePos = attention_info.position = current.pos;
    cXyz sp3C;
    sp3C = current.pos - link->getHookshotRootPos();
    mChainCnt = sp3C.abs() / 7.0f;
    
    if (fopAcM_GetParam(this) != Mode_Pull || mChainCnt > 18) {
        shape_angle.x = cM_atan2s(-sp3C.y, sp3C.absXZ());
        shape_angle.y = cM_atan2s(sp3C.x, sp3C.z);
    } else {
        shape_angle.x = link->shape_angle.x;
        shape_angle.y = link->shape_angle.y;
    }
    
    if (fopAcM_GetParam(this) != Mode_Wait && !m2A0) {
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, 0);
        mDoMtx_stack_c::YrotM(-0x4000);
        MTXCopy(mDoMtx_stack_c::get(), mMtx);
    } else {
        m2A0 = false;
    }
    
    int roomNo = dComIfGp_roomControl_getStayNo();
    tevStr.mRoomNo = roomNo;
    mStts.SetRoomId(roomNo);
    current.roomNo = roomNo;
    
    if (fopAcM_GetParam(this) != Mode_Wait) {
        m2A1 = link->setItemWaterEffect(this, m2A1, 0);
    }
    
    if (fopAcM_GetParam(this) == Mode_Shot) {
        speedF = current.pos.abs(old.pos);
    } else if (fopAcM_GetParam(this) == Mode_Return || fopAcM_GetParam(this) == Mode_Pull) {
        speedF = -current.pos.abs(old.pos);
    } else {
        speedF = 0.0f;
    }
    
    return TRUE;
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
        fopAc_ac_c* carry_actor = fopAcM_SearchByID(mCarryActorID);
        if (carry_actor && fopAcM_CheckStatus(carry_actor, fopAcStts_HOOK_CARRY_e)) {
            fopAcM_cancelHookCarryNow(carry_actor);
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
    {{
        /* Start  */ {0.0f, 0.0f, 0.0f},
        /* End    */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 5.0f,
    }},
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
    /* Priority     */ PRIO_HOOKSHOT,
    /* Actor SubMtd */ &l_daHookshot_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
