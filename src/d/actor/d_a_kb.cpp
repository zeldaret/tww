/**
 * d_a_kb.cpp
 * NPC - Pig
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kb.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_cc_d.h"
#include "d/actor/d_a_esa.h"
#include "d/actor/d_a_tag_kb_item.h"
#include "d/actor/d_a_player.h"
#include "d/d_s_play.h"
#include "f_op/f_op_kankyo_mng.h"
#include "f_op/f_op_camera.h"
#include "res/Object/Kb.h"
#include "d/d_snap.h"
#include "d/d_vibration.h"

// Several functions use the same joint index for the tail on both the normal and big pig models
// Because of this, PG_JNT_J_PG_TAIL_e *must* match the value of PG_BIG_JNT_J_PG_TAIL_e
// Otherwise the code that deals with these joints would break in a couple places
STATIC_ASSERT(PG_JNT_J_PG_TAIL_e == PG_BIG_JNT_J_PG_TAIL_e);

static bool ALL_ANGER;
static bool DEMO_START;

/* 00000078-000001A4       .text anm_init__FP8kb_classifUcfi */
void anm_init(kb_class* i_this, int param_1, f32 param_2, u8 param_3, f32 param_4, int param_5) {
    i_this->m50C = param_1;

#if VERSION == VERSION_DEMO
    i_this->mpMorf->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectRes("Kb", param_1),
        param_3, param_2, param_4, 0.0f, -1.0f,
        (J3DAnmTransform*)dComIfG_getObjectRes("Kb", param_5)
    );
#else
    if(param_5 >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Kb", param_1),
            param_3, param_2, param_4, 0.0f, -1.0f,
            (J3DAnmTransform*)dComIfG_getObjectRes("Kb", param_5)
        );
    }
    else {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Kb", param_1),
            param_3, param_2, param_4, 0.0f, -1.0f,
            NULL
        );
    }
#endif
}

static u16 kb_btp_idx[] = {dRes_INDEX_KB_BTP_PG_EYE1_e, dRes_INDEX_KB_BTP_PG_EYE1_e, dRes_INDEX_KB_BTP_PG_EYE2_e, dRes_INDEX_KB_BTP_PG_BIG_EYE1_e, dRes_INDEX_KB_BTP_PG_BIG_EYE1_e, dRes_INDEX_KB_BTP_PG_BIG_EYE2_e, dRes_INDEX_KB_BTP_PG_EYE1_e};
static u16 kb_bmt_idx[] = {dRes_INDEX_KB_BMT_PG_PINK_e, dRes_INDEX_KB_BMT_PG_BUTI_e, dRes_INDEX_KB_BMT_PG_KURO_e, dRes_INDEX_KB_BMT_PG_BIG_PINK_e, dRes_INDEX_KB_BMT_PG_BIG_BUTI_e, dRes_INDEX_KB_BMT_PG_BIG_KURO_e, dRes_INDEX_KB_BMT_PG_PINK_e};

/* 000001A4-00000258       .text tex_anm_set__FP8kb_classUs */
void tex_anm_set(kb_class* i_this, u16 param_1) {
    i_this->m509 = 1;
    J3DAnmTexPattern* pPattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Kb", kb_btp_idx[param_1]);
    i_this->m50A = 2;
    i_this->m500 = pPattern;
    i_this->m508 = 0;
    i_this->m500->setFrame(0.0f);

    const u16 num = pPattern->getUpdateMaterialNum();
    for(u16 i = 0; i < num; i++) {
        i_this->mpTexNoAnm[i].setAnmTexPattern(pPattern);
    }
}

/* 00000258-0000028C       .text kb_eye_tex_anm__FP8kb_class */
void kb_eye_tex_anm(kb_class* i_this) {
    if(i_this->m509) {
        if(i_this->m508 < i_this->m50A) {
            i_this->m508++;
        }
        else {
            i_this->m509 = 0;
        }
    }
}

/* 0000028C-00000654       .text esa_search_sub__FPvPv */
void* esa_search_sub(void* param_1, void* param_2) {
    dBgS_LinChk linChk;

    if(fopAcM_IsActor(param_1) && fopAcM_GetName(param_1) == fpcNm_ESA_e) {
        esa_class* pEsa = (esa_class*)param_1;
        fopAc_ac_c* pActor = (fopAc_ac_c*)param_2;

        if(pEsa->field_0x298 == 0 && pEsa->mState == 1 && std::abs(pActor->current.pos.y - pEsa->current.pos.y) < 40.0f) {
            if(fopAcM_searchActorDistanceXZ(pActor, pEsa) < 400.0f && cLib_distanceAngleS(pActor->current.angle.y, fopAcM_searchActorAngleY(pActor, pEsa)) < 0x55F0) {
                cXyz temp(pEsa->current.pos);
                temp.y += 40.0f;

                cXyz temp2(pActor->current.pos);
                temp2.y += 40.0f;

                linChk.Set(&temp2, &temp, pActor);
                if(!dComIfG_Bgsp()->LineCross(&linChk)) {
                    return param_1;
                }
            }
        }
    }

    return NULL;
}

/* 00000AC8-00000B60       .text item_tag_search__FPvPv */
void* item_tag_search(void* param_1, void* param_2) {
    if(fopAcM_IsActor(param_1) && fopAcM_GetName(param_1) == fpcNm_TAG_KB_ITEM_e) {
        daTagKbItem_c* pItem = (daTagKbItem_c*)param_1;
        fopAc_ac_c* pActor = (fopAc_ac_c*)param_2;

        if(std::abs(pActor->current.pos.y - pItem->current.pos.y) < 40.0f && fopAcM_searchActorDistanceXZ(pActor, pItem) < 400.0f) {
            return param_1;
        }
    }

    return NULL;
}

/* 00000B60-00000B9C       .text search_get_esa__FP8kb_class */
void* search_get_esa(kb_class* i_this) {
    void* pProc = fpcEx_Search(esa_search_sub, i_this);
    if(pProc) {
        return pProc;
    }

    return NULL;
}

/* 00000B9C-00000BD8       .text search_get_item__FP8kb_class */
daTagKbItem_c* search_get_item(kb_class* i_this) {
    void* pProc = fpcEx_Search(item_tag_search, i_this);
    if(pProc) {
        return (daTagKbItem_c*)pProc;
    }

    return NULL;
}

/* 00000BD8-00000DB0       .text carry_check__FP8kb_class */
BOOL carry_check(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    cLib_onBit<u32>(actor->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    if(fopAcM_checkCarryNow(actor)) {
        cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
        i_this->mSph.OnTgSetBit();
        i_this->m41E = 1;
        i_this->m420 = 10;
        i_this->m4CC = 0;
        i_this->m440 = 0;
        i_this->m540.end();
        i_this->m404 = 0;
        actor->gravity = 0.0f;
        actor->speed.y = 0.0f;

        fopAc_ac_c* pActor = fopAcM_SearchByID(i_this->m4D8);
        if(i_this->m4D8 != fpcM_ERROR_PROCESS_ID_e && pActor != NULL) {
            ((esa_class*)pActor)->field_0x298 = 0;
        }
        i_this->m4D8 = fpcM_ERROR_PROCESS_ID_e;

        actor->shape_angle.z = 0;
        actor->speedF = 0.0f;
        actor->speed.set(0.0f, 0.0f, 0.0f);
        i_this->m4BC = actor->current.pos.y;
        i_this->m436 = 0;
        i_this->m438 = 0;
        i_this->m44A = 0;

        anm_init(i_this, dRes_INDEX_KB_BCK_JITA2_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_KB_BAS_JITA2_e);

        if(i_this->mShapeType >= 8) {
            fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_CATCH, 0);
        }
        else {
            fopAcM_monsSeStart(actor, JA_SE_CV_PG_CATCH, 0);
        }

        return TRUE;
    }

    return FALSE;
}

/* 00000DB0-00000EF4       .text speed_pos_set__FP8kb_class */
void speed_pos_set(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    if(daPy_getPlayerActorClass()->getGrabMissActor() == actor) {
        i_this->m40B = 1;
        i_this->mpMorf->setPlaySpeed(0.0f);
        actor->shape_angle.z = 0;
        actor->shape_angle.x = 0;
        actor->current.angle.x = 0;
        actor->current.angle.z = 0;
    }
    else {
        if(i_this->m40B) {
            i_this->mpMorf->setPlaySpeed(1.0f);
            i_this->m40B = 0;
        }

        cMtx_YrotS(*calc_mtx, actor->current.angle.y);
        cXyz temp1, temp2;
        temp1.x = 0.0f;
        temp1.y = 0.0f;
        temp1.z = actor->speedF;
        MtxPosition(&temp1, &temp2);
        actor->speed.x = temp2.x;
        actor->speed.z = temp2.z;
        actor->speed.y += actor->gravity;

        if(actor->speed.y < -20.0f) {
            actor->speed.y = -20.0f;
        }

        if(!fopAcM_checkCarryNow(actor)) {
            if(i_this->mSph.ChkCoSet()) {
                fopAcM_posMove(actor, i_this->mStts.GetCCMoveP());
            }
            else {
                fopAcM_posMove(actor, NULL);
            }
        }
    }
}

#if VERSION == VERSION_DEMO
void hamon_set(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    cXyz scale;
    scale.setall(i_this->m5D0);

    dComIfGp_particle_setShipTail(dPa_name::ID_AK_JN_HAMON00, &actor->current.pos, NULL, &scale, 0xFF, &i_this->m540);
}
#else
/* 00000EF4-00000FA0       .text hamon_set__FP8kb_classf */
void hamon_set(kb_class* i_this, f32 param_2) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    cXyz scale;
    scale.setall(i_this->m5D0);

    if(i_this->m540.getEmitter() == NULL) {
        dComIfGp_particle_setShipTail(dPa_name::ID_AK_JN_HAMON00, &actor->current.pos, NULL, &scale, 0xFF, &i_this->m540);
    }

    if(i_this->m540.getEmitter()) {
        i_this->m540.setRate(param_2);
    }
}
#endif

/* 00000FA0-00001130       .text sibuki_set__FP8kb_class */
void sibuki_set(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    f32 scaleXZ = 0.4f;
    f32 scaleY = 0.75f;
    i_this->m440 = 1;
    cXyz pos(actor->current.pos);
    pos.y = i_this->mAcch.m_wtr.GetHeight();
    i_this->m4C4 = 30.0f;
    if(i_this->m4D4) {
        scaleXZ = REG8_F(4) + 0.8f;
    }
    fopKyM_createWpillar(&pos, scaleXZ, scaleY, 0.0f);
    fopAcM_seStart(actor, JA_SE_OBJ_FALL_WATER_S, 0);

    if(i_this->mShapeType >= 8) {
        fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_CATCH, 0);
    }
    else {
        fopAcM_monsSeStart(actor, JA_SE_CV_PG_CATCH, 0);
    }

    i_this->m5D0 = i_this->m4D4 * 0.5f + 1.0f;
#if VERSION == VERSION_DEMO
    hamon_set(i_this);
    i_this->m540.setRate(1.0f);
#else
    hamon_set(i_this, 1.0f);
#endif
}

/* 00001130-00001268       .text swim_mode_change_check__FP8kb_class */
BOOL swim_mode_change_check(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    f32 temp = i_this->m4D4 * 20.0f + 20.0f;
    if(i_this->mAcch.ChkWaterHit() && i_this->mAcch.m_wtr.GetHeight() > actor->current.pos.y && std::abs(i_this->mAcch.m_wtr.GetHeight() - i_this->mAcch.GetGroundH()) > temp) {
        if(i_this->m440 == 0) {
            sibuki_set(i_this);
        }
        else {
            i_this->m5D0 = 1.0f;
#if VERSION == VERSION_DEMO
            i_this->m540.setRate(1.0f);
#else
            if(i_this->m540.getEmitter()) {
                i_this->m540.setRate(1.0f);
            }
#endif
        }

#if VERSION > VERSION_DEMO
        i_this->m554.end();
#endif

        i_this->m41E = 2;
        i_this->m420 = 0x14;

        return TRUE;
    }
    if(i_this->m404) {
        if(i_this->m440 == 0) {
            i_this->m440 = 1;
            i_this->m4C4 = 30.0f;
            i_this->m5D0 = i_this->m4D4 * 0.5f + 0.5f;
#if VERSION == VERSION_DEMO
            hamon_set(i_this);
            i_this->m540.setRate(0.0f);
#else
            hamon_set(i_this, 0.0f);
#endif
        }
    }
    else if(i_this->m440) {
        i_this->m440 = 0;
        i_this->m540.end();
    }

    return FALSE;
}

/* 00001268-000014E0       .text pl_attack_hit_check__FP8kb_class */
void pl_attack_hit_check(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    if(i_this->mSph.ChkTgHit()) {
        if(i_this->m403 == 0) {
            i_this->m403 = 1;

            dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &actor->current.pos, &actor->shape_angle);

#if VERSION > VERSION_DEMO
            for(int i = 0; i < 2; i++) {
                i_this->m5A8[i].end();
            }
#endif

            i_this->m4DC = *i_this->mSph.GetTgHitPosP();

            if(i_this->m420 != 5) {
                i_this->m420 = 4;
            }

            CcAtInfo atInfo;
            atInfo.pParticlePos = NULL;
            atInfo.mpObj = i_this->mSph.GetTgHitObj();
            cc_at_check(actor, &atInfo);

            if(dComIfGs_getSelectEquip(0) == dItemNo_NONE_e) {
                actor->health = 10;
            }

            if(actor->health <= 0) {
                actor->health = 10;
                ALL_ANGER = true;
                cLib_onBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
                i_this->m420 = 0x21;
                i_this->m41E = 3;
            }

            if(i_this->mShapeType >= 8) {
                fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_CATCH, 0);
            }
            else {
                fopAcM_monsSeStart(actor, JA_SE_CV_PG_CATCH, 0);
            }
        }
    }
    else {
        i_this->m403 = 0;

        if(ALL_ANGER) {
            if(i_this->m50C != 0x16) {
                anm_init(i_this, dRes_INDEX_KB_BCK_RUN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 2.0f, dRes_INDEX_KB_BAS_RUN1_e);
            }

            cLib_onBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);

            i_this->m4C4 = 30.0f;
            i_this->m41E = 3;
            i_this->m420 = 0x23;
        }
    }
}

/* 0000151C-0000160C       .text he_set__FP8kb_class */
void he_set(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    daPy_py_c* pPlayer = daPy_getPlayerActorClass();

    i_this->m5D4[0] = i_this->m4A4;
    i_this->m5EC[0] = pPlayer->shape_angle;

    if(i_this->m594.getEmitter() == NULL) {
        i_this->m5D4[0] = i_this->m4A4;
        // this could just use "i_this->m5D4" but I think pointer to first element is a clearer way to write it?
        dComIfGp_particle_set(dPa_name::ID_AK_SN_PIGGAS00, &i_this->m5D4[0], NULL, NULL, 0xFF, &i_this->m594, fopAcM_GetRoomNo(actor));
    }

    if(i_this->m594.getEmitter()) {
        i_this->m594.getEmitter()->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(PG_JNT_J_PG_TAIL_e));
    }
}

/* 0000160C-000016E0       .text smoke_set__FP8kb_class */
void smoke_set(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    f32 scale = i_this->m4D4 + 1.0f;

    if(i_this->m554.getEmitter() == NULL) {
        dComIfGp_particle_setToon(dPa_name::ID_AK_JT_ELEMENTSMOKE00, &i_this->m5D4[0], &i_this->m5EC[0], NULL, 0xB9, &i_this->m554, fopAcM_GetRoomNo(actor));
    }

    if(i_this->m554.getEmitter()) {
        JGeometry::TVec3<f32> scaleVec(scale, scale, scale);
        i_this->m554.getEmitter()->setRate(1.0f);
        i_this->m554.getEmitter()->setSpread(1.0f);
        i_this->m554.getEmitter()->setGlobalScale(scaleVec);
    }
}

/* 000016E0-000017EC       .text smoke_set2__FP8kb_class */
void smoke_set2(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    f32 scale = i_this->m4D4 + 1.0f;

    if(i_this->m554.getEmitter() == NULL) {
        dComIfGp_particle_setToon(dPa_name::ID_AK_JT_ELEMENTSMOKE01, &i_this->m5D4[0], &actor->shape_angle, NULL, 0xB9, &i_this->m554, fopAcM_GetRoomNo(actor));
    }

    if(i_this->m554.getEmitter()) {
        JGeometry::TVec3<f32> scaleVec(scale, scale, scale);
        i_this->m554.getEmitter()->setMaxFrame(25);
        i_this->m554.getEmitter()->setAwayFromCenterSpeed(0.0f);
        i_this->m554.getEmitter()->setAwayFromAxisSpeed(5.0f);
        i_this->m554.getEmitter()->setRate(3.0f);
        i_this->m554.getEmitter()->setDirectionalSpeed(2.0f);
        i_this->m554.getEmitter()->setGlobalScale(scaleVec);
        i_this->m554.getEmitter()->setLifeTime(25);
    }
}

/* 000017EC-000018DC       .text smoke_set3__FP8kb_class */
void smoke_set3(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    JGeometry::TVec3<f32> scaleVec;
    if(i_this->mShapeType >= 8) {
        scaleVec.set(3.0f, 3.0f, 3.0f);
    }
    else {
        scaleVec.set(1.0f, 1.0f, 1.0f);
    }

    if(i_this->m574.getEmitter() == NULL) {
        dComIfGp_particle_setToon(dPa_name::ID_AK_ST_PIGDIGSMOKE00, &i_this->m5D4[1], &actor->shape_angle, NULL, 0xA0, &i_this->m574, fopAcM_GetRoomNo(actor));
    }

    i_this->m574.onWindOff();

    if(i_this->m574.getEmitter()) {
        i_this->m574.getEmitter()->setGlobalScale(scaleVec);
    }
}

/* 000018DC-000019A4       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* i_node, int calcTiming) {
    if(calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = reinterpret_cast<J3DJoint*>(i_node);
        s32 jntNo = joint->getJntNo();
        J3DModel* pModel = j3dSys.getModel();
        kb_class* i_kb = (kb_class*)pModel->getUserArea();

        if(i_kb && jntNo == PG_JNT_J_PG_TAIL_e) {
            MTXCopy(pModel->getAnmMtx(jntNo), *calc_mtx);
            cXyz temp(0.0f, 0.0f, 0.0f);
            MtxPosition(&temp, &i_kb->m4A4);
            pModel->setAnmMtx(jntNo, *calc_mtx);
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }

    return TRUE;
}

/* 000019A4-00001ACC       .text draw_SUB__FP8kb_class */
void draw_SUB(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    J3DModel* pModel = i_this->mpMorf->getModel();
    MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
    cMtx_XrotM(*calc_mtx, i_this->m4F4.x);
    cMtx_ZrotM(*calc_mtx, i_this->m4F4.z);
    MtxScale(i_this->m4E8.x, i_this->m4E8.y, i_this->m4E8.x, true);

    if(i_this->m41E != 4) {
        cLib_addCalc2(&i_this->m4C0, i_this->m4C4, 1.0f, 5.0f);
    }

    MtxTrans(0.0f, i_this->m4C0, 0.0f, true);
    cMtx_YrotM(*calc_mtx, actor->shape_angle.y);
    cMtx_XrotM(*calc_mtx, actor->shape_angle.x);
    cMtx_ZrotM(*calc_mtx, actor->shape_angle.z);
    MtxTrans(0.0f, -30.0f, 0.0f, true);
    pModel->setBaseTRMtx(*calc_mtx);
}

/* 00001ACC-00001F6C       .text daKb_Draw__FP8kb_class */
static BOOL daKb_Draw(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    J3DModel* pModel = i_this->mpMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    J3DModelData* pModelData = pModel->getModelData();
    pModelData->setTexNoAnimator(i_this->m500, i_this->mpTexNoAnm);
    i_this->m500->setFrame(i_this->m508);
    pModelData->setMaterialTable(i_this->mpMaterialTable, J3DMatCopyFlag_Material);
    i_this->mTevStr = actor->tevStr;
    i_this->mTevStr.mColorC0.r = actor->tevStr.mColorC0.r + (0x78 - actor->tevStr.mColorC0.r) * i_this->m4B0;
    i_this->mTevStr.mColorC0.g = actor->tevStr.mColorC0.g + (-actor->tevStr.mColorC0.g) * i_this->m4B0;
    i_this->mTevStr.mColorC0.b = actor->tevStr.mColorC0.b + (-actor->tevStr.mColorC0.b) * i_this->m4B0;
    i_this->mTevStr.mColorK0.r = actor->tevStr.mColorK0.r + (0x78 - actor->tevStr.mColorK0.r) * i_this->m4B0;
    i_this->mTevStr.mColorK0.g = actor->tevStr.mColorK0.g + (-actor->tevStr.mColorK0.g) * i_this->m4B0;
    i_this->mTevStr.mColorK0.b = actor->tevStr.mColorK0.b + (-actor->tevStr.mColorK0.b) * i_this->m4B0;
    g_env_light.setLightTevColorType(pModel, &i_this->mTevStr);
    i_this->mpMorf->updateDL();

    if(
        i_this->m420 < 0x2D && !fopAcM_checkCarryNow(actor)
#if VERSION > VERSION_DEMO
        && i_this->m41E != 2
#endif
    ) {
        cXyz shadowPos(actor->current.pos.x, actor->current.pos.y + 150.0f + REG8_F(0x12), actor->current.pos.z);
        i_this->mShadowId = dComIfGd_setShadow(i_this->mShadowId, 
                                     1, 
                                     pModel, 
                                     &shadowPos, REG8_F(0x13) + 800.0f, REG8_F(0x11) + 40.0f, 
                                     actor->current.pos.y, 
                                     i_this->mAcch.GetGroundH(),
                                     i_this->mAcch.m_gnd, 
                                     &actor->tevStr);
    }

#if VERSION > VERSION_DEMO
    if(i_this->m4D4 == 2.0f) {
        f32 temp = i_this->m4D4 + 1.0f;
        dSnap_RegistFig(DSNAP_TYPE_KB, actor, temp - 0.4f, temp - 1.1f, 1.0f);
    }
    else
#endif
    {
        dSnap_RegistFig(DSNAP_TYPE_KB, actor, 1.0f, 1.0f, 1.0f);
    }

    return TRUE;
}

/* 00001F6C-0000233C       .text way_check__FP8kb_classsUc */
s16 way_check(kb_class* i_this, s16 param_1, u8 param_2) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    dBgS_LinChk linChk;

    s16 angle = param_1;

    cXyz temp1;
    cXyz temp3 = actor->current.pos;
    temp3.y += 50.0f;
    s16 temp = 0x2000;
    if(cM_rnd() < 0.5f) {
        temp = -0x2000;
    }

    temp1.set(0.0f, 50.0f, 300.0f);
    if(param_2) {
        temp3 = actor->current.pos;
        temp3.y += 100.0f;

        temp1.x = 0.0f;
        temp1.y = 100.0f;
        temp1.z = 100.0f;
    }

    cXyz temp2;
    for(int i = 0; i < 8; i++) {
        cMtx_YrotS(*calc_mtx, angle);
        MtxPosition(&temp1, &temp2);
        temp2 += actor->current.pos;
        linChk.Set(&temp3, &temp2, actor);
        if(!dComIfG_Bgsp()->LineCross(&linChk)) {
            return angle;
        }

        angle += temp;
    }

    return param_1;
}

/* 0000233C-00002748       .text target_set__FP8kb_classUc */
void target_set(kb_class* i_this, u8 param_1) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;
    daPy_py_c* pPlayer = daPy_getPlayerActorClass();

    s16 temp;
    cXyz temp2;
    switch(param_1) {
        case 0:
            temp = actor->shape_angle.y;
            if(i_this->m426[3] == 0) {
                temp = way_check(i_this, cM_rndFX(32768.0f), 0);
            }

            break;
        case 1:
            temp = way_check(i_this, 0x8000 + fopAcM_searchPlayerAngleY(actor) + (s16)cM_rndFX(10000.0f), 0);

            break;
        case 2: {
            temp2.x = i_this->m450.x - actor->current.pos.x;
            temp2.z = i_this->m450.z - actor->current.pos.z;
            i_this->m422 = way_check(i_this, (s16)cM_atan2s(temp2.x, temp2.z), 1);
        }

            break;
        case 3:
            if(i_this->m4D8 != fpcM_ERROR_PROCESS_ID_e) {
                fopAc_ac_c* pActor = fopAcM_SearchByID(i_this->m4D8);
                if(pActor) {
                    dBgS_LinChk linChk;

                    cXyz temp4, temp3;
                    temp3 = pActor->current.pos;
                    temp3.y += 10.0f;
                    temp4 = actor->current.pos;
                    temp4.y += 10.0f;

                    linChk.Set(&temp4, &temp3, actor);
                    if(!dComIfG_Bgsp()->LineCross(&linChk)) {
                        i_this->m45C = pActor->current.pos;
                    }
                    else {
                        i_this->m4D8 = fpcM_ERROR_PROCESS_ID_e;
                    }
                }
            }

            break;
    }

    if(param_1 < 3) {
        cMtx_YrotS(*calc_mtx, temp);
        temp2.set(0.0f, 0.0f, 1000.0f);
        MtxPosition(&temp2, &i_this->m45C);
        i_this->m45C += actor->current.pos;
    }
}

/* 00002748-00002834       .text esa_demo_check__FP8kb_class */
BOOL esa_demo_check(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    if(i_this->m426[4] != 0) {
        return FALSE;
    }
        
    if(fopAcM_searchPlayerDistanceXZ(actor) > 2000.0f) {
        return FALSE;
    }

    if(i_this->mAcch.ChkWallHit()) {
        return FALSE;
    }

    fopAc_ac_c* pEsa = (fopAc_ac_c*)search_get_esa(i_this);
    if(pEsa) {
        i_this->m4D8 = fopAcM_GetID(pEsa);
        i_this->field_0x498 = pEsa->current.pos;

        if(!DEMO_START) {
            DEMO_START = true;

            i_this->m406 = 1;
            i_this->m41E = 4;
            i_this->m420 = 0x28;

            return TRUE;
        }
    }

    return FALSE;
}

/* 00002834-00003120       .text normal_move__FP8kb_class */
void normal_move(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

#if VERSION == VERSION_DEMO
    if(swim_mode_change_check(i_this) == TRUE) {
        return;
    }
#else
    if(swim_mode_change_check(i_this)) {
        return;
    }
#endif

    f32 diffX = i_this->m45C.x - actor->current.pos.x;
    f32 diffZ = i_this->m45C.z - actor->current.pos.z;
    f32 temp1 = std::sqrtf(diffX + diffX + diffZ * diffZ);
    i_this->m422 = cM_atan2s(diffX, diffZ);

    switch(i_this->m420) {
        case 0:
            i_this->m420 += 1;
            i_this->m426[0] = cM_rndF(50.0f) + 50.0f;
            actor->shape_angle.z = 0;

            if(i_this->m50C != 0x17) {
                anm_init(i_this, dRes_INDEX_KB_BCK_WAIT1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_KB_BAS_WAIT1_e);
            }

            i_this->m4B4 = 0.0f;
            i_this->m4B8 = 2.5f;
        case 1: {
            if(esa_demo_check(i_this)) {
                return;
            }

            if(i_this->m426[0] == 0) {
                i_this->m420 = 2;
            }

            f32 f31 = 200.0f;
            if(fopAcM_searchPlayerDistance(actor) < f31 && i_this->m408 == 0) {
                if(dComIfGp_checkPlayerStatus0(0, daPyStts0_CRAWL_e)) {
                    i_this->m426[1] = cM_rndF(60.0f) + 60.0f;
                }
                else if(i_this->m426[1] == 0 && i_this->m405 == 0) {
                    i_this->m420 = 4;
                }
            }

            break;
        }
        case 2:
            i_this->m420 += 1;
            i_this->m426[0] = cM_rndF(50.0f) + 50.0f;
            i_this->m4B4 = 3.0f;

            if(i_this->m50C != 0x18) {
                anm_init(i_this, dRes_INDEX_KB_BCK_WALK1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_KB_BAS_WALK1_e);
            }

            i_this->m4B8 = 2.0f;
            target_set(i_this, 0);
            i_this->m424 = 0x800;
        case 3: {
            if(esa_demo_check(i_this)) {
                return;
            }

            if(i_this->m426[0] == 0) {
                i_this->m420 = 0;
                break;
            }

            f32 f31 = 200.0f;
            if(fopAcM_searchPlayerDistance(actor) < f31) {
                if(i_this->m408 != 0) {
                    break;
                }

                if(dComIfGp_checkPlayerStatus0(0, daPyStts0_CRAWL_e)) {
                    i_this->m426[1] = cM_rndF(30.0f) + 30.0f;
                    break;
                }
                else if(i_this->m426[1] == 0 && i_this->m405 == 0) {
                    i_this->m420 = 4;
                    break;
                }
            }

            if(i_this->m4CC && (i_this->m450.x || i_this->m450.y || i_this->m450.z)) {
                f32 diffX = i_this->m450.x - actor->current.pos.x;
                f32 diffZ = i_this->m450.z - actor->current.pos.z;
                if(std::sqrtf(diffX * diffX + diffZ * diffZ) > i_this->m4CC * 0.5f) {
                    i_this->m422 = cM_atan2s(diffX, diffZ);
                    cMtx_YrotS(*calc_mtx, i_this->m422);
                    cXyz temp(0.0f, 0.0f, 1000.0f);
                    MtxPosition(&temp, &i_this->m45C);
                    i_this->m45C += actor->current.pos;
                }
            }

            break;
        }
        case 4:
            if(i_this->mbCanBeBigPig != 2 && i_this->mbCanBeBigPig != 3 && i_this->mbCanBeBigPig != 4) {
                i_this->m4CC = 0.0f;
            }

            i_this->m420 += 1;
            i_this->m4B4 = 12.0f;
            if(i_this->mShapeType >= 8) {
                i_this->m4B4 *= 0.5f;
            }

            if(i_this->m50C != 0x16) {
                anm_init(i_this, dRes_INDEX_KB_BCK_RUN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.5f, dRes_INDEX_KB_BAS_RUN1_e);
            }

            i_this->m4B8 = 2.0f;
            i_this->m426[0] = 0;
            i_this->m424 = 0x2000;
        case 5: {
            if(i_this->m426[0] == 0) {
                target_set(i_this, 1);
                i_this->m426[0] = cM_rndF(10.0f) + 10.0f;
            }

            if(i_this->mpMorf->checkFrame(0.0f) || i_this->mpMorf->checkFrame(5.0f)) {
                if(i_this->mShapeType >= 8 && i_this->mpMorf->checkFrame(0.0f)) {
                    dComIfGp_getVibration().StartShock(1, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                    fopAcM_monsSeStart(actor, JA_SE_CM_PG_L_JUMP, 0);
                }

                if(i_this->m426[2] == 0) {
                    if(i_this->mShapeType >= 8) {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_NORMAL, 0);
                    }
                    else {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_NORMAL, 0);
                    }
                }
            }

            f32 f31 = 400.0f;
            if(fopAcM_searchPlayerDistance(actor) > f31) {
                i_this->m420 = 0;
            }

            break;
        }
        case 6:
            if(i_this->mpMorf->isStop()) {
                i_this->m4C4 = 30.0f;
                i_this->m420 = 2;
                i_this->m426[1] = cM_rndF(30.0f) + 30.0f;
            }

            break;
    }

    if(i_this->m420 > 1 && i_this->m420 != 6) {
        if(i_this->m40B == 0) {
            cLib_addCalcAngleS2(&actor->current.angle.y, i_this->m422, 4, i_this->m424);
        }

        if(i_this->m420 == 5) {
            if(i_this->m426[2] == 0) {
                s16 dist = cLib_distanceAngleS(actor->current.angle.y, i_this->m422);
                if(dist > 0x4000) {
                    if(i_this->mShapeType >= 8) {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_TURN, 0);
                    }
                    else {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_TURN, 0);
                    }

                    i_this->m426[2] = 0x18;
                }
            }

            if(i_this->m40B == 0) {
                if(std::abs(actor->speedF - i_this->m4B4) < 0.2f) {
                    actor->shape_angle.z = (actor->current.angle.y - i_this->m422) * 0.5f;
                    if(actor->shape_angle.z < 0) {
                        if((int)(u16)actor->shape_angle.z < (u16)-0x2000) {
                            actor->shape_angle.z = -0x2000;
                        }
                    }
                    else if(actor->shape_angle.z > 0x2000) {
                        actor->shape_angle.z = 0x2000;
                    }
                }
                else {
                    actor->shape_angle.z = 0;
                }
            }
        }
    }

    cLib_addCalc2(&actor->speedF, i_this->m4B4, 1.0f, i_this->m4B8);
    cLib_onBit<u32>(actor->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    carry_check(i_this);
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 2, 0x1000);
}

/* 00003120-00003DEC       .text carry_move__FP8kb_class */
void carry_move(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    daPy_py_c* pPlayer = daPy_getPlayerActorClass();

    switch(i_this->m420) {
        case 0xA:
            i_this->mSph.OffCoSetBit();
            actor->shape_angle.z = 0;
            cLib_addCalcAngleS2(&i_this->m4F4.x, 0, 2, 0x400);
            cLib_addCalcAngleS2(&i_this->m4F4.z, 0, 2, 0x400);

            if(i_this->m4BC != actor->current.pos.y) {
                i_this->m438 += 1;
                
                if(i_this->m438 == 4) {
                    dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &actor->current.pos, &actor->shape_angle);
                }

                cLib_addCalcAngleS2(&actor->shape_angle.x, -0x7FFF, 1, 0x1000);
                i_this->m4C4 = 20.0f;
            }

            if(std::abs(actor->current.pos.y - pPlayer->current.pos.y) >= 110.0f) {
                actor->shape_angle.x = -0x7FFF;
#if VERSION == VERSION_DEMO
                i_this->m44A = 3;
                i_this->m420 = 0xB;
#endif

                if(i_this->mbCanBeBigPig == 3) {
                    he_set(i_this);
                }

                i_this->m426[2] = 0;
                i_this->m4C8 = 1.8f;
                
                dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &actor->current.pos, &actor->shape_angle);

                anm_init(i_this, dRes_INDEX_KB_BCK_JITA2_e, 5.0f, J3DFrameCtrl::EMode_NONE, i_this->m4C8, dRes_INDEX_KB_BAS_JITA2_e);

                if(i_this->mShapeType >= 8) {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_CATCH, 0);
                }
                else {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PG_CATCH, 0);
                }

#if VERSION > VERSION_DEMO
                i_this->mAcch.OnLineCheck();
                i_this->m44A = 3;
                i_this->m420 = 0xB;
#endif
            }

            actor->current.angle.y = actor->shape_angle.y;

            break;
        case 0xB:
            if(i_this->mbCanBeBigPig == 3) {
                he_set(i_this);
            }

            if(i_this->m44A != 0) {
                if(i_this->mpMorf->isStop()) {
                    i_this->m44A -= 1;

                    if(i_this->m44A <= 0) {
                        anm_init(i_this, dRes_INDEX_KB_BCK_JITA1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_KB_BAS_JITA1_e);

                        i_this->m426[2] = cM_rndF(300.0f) + 600.0f;
                        i_this->m44A = 0;
                    }
                    else {
                        i_this->m4C8 -= 0.6f;
                        if(i_this->m4C8 < 0.0f) {
                            i_this->m4C8 = 0.0f;
                        }

                        if(i_this->m44A > 1) {
                            if(i_this->mShapeType >= 8) {
                                fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_CATCH, 0);
                            }
                            else {
                                fopAcM_monsSeStart(actor, JA_SE_CV_PG_CATCH, 0);
                            }
                        }

                        anm_init(i_this, dRes_INDEX_KB_BCK_JITA2_e, 0.0f, J3DFrameCtrl::EMode_NONE, i_this->m4C8, dRes_INDEX_KB_BAS_JITA2_e);
                    }
                }
            }
            else {
                if(i_this->m426[2] == 0) {
                    i_this->m44A = 3;
                    i_this->m4C8 = 1.8f;
                    
                    anm_init(i_this, dRes_INDEX_KB_BCK_JITA2_e, 5.0f, J3DFrameCtrl::EMode_NONE, i_this->m4C8, dRes_INDEX_KB_BAS_JITA2_e);

                    if(i_this->mShapeType >= 8) {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_CATCH, 0);
                    }
                    else {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_CATCH, 0);
                    }

                    dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &actor->current.pos, &actor->shape_angle);
                }
                else if(pPlayer->getFootOnGround()) {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PG_CARRY, 0);
                }
            }

            cLib_addCalcAngleS2(&actor->shape_angle.x, -0x7FFF, 1, 0x1000);

#if VERSION == VERSION_DEMO
            if(!fopAcM_checkCarryNow(actor)) {
                actor->gravity = -3.0f;

                if(actor->speedF <= 0.0f) {
                    i_this->m4C4 = 30.0f;
                    i_this->m426[0] = 0;

                    if(i_this->mbCanBeBigPig == 2) {
                        i_this->m426[5] = 0x1E;
                    }

                    if(i_this->mbCanBeBigPig == 3) {
                        i_this->m594.end();
                    }

                    i_this->m420 = 0xD;
                    cLib_onBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
                }
                else {
                    i_this->m436 = 0;
                    i_this->m4C4 = 30.0f;
                    
                    if(i_this->mbCanBeBigPig == 3) {
                        i_this->m594.end();
                    }

                    anm_init(i_this, dRes_INDEX_KB_BCK_JITA2_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_KB_BAS_JITA2_e);

                    actor->shape_angle.x = 0x8000;
                    actor->speedF = 20.0f;
                    actor->speed.y = 20.0f;
                    i_this->m420 = 0xC;
                }
            }
#endif

            actor->current.angle.y = actor->shape_angle.y;

            break;
        case 0xC:
            if(i_this->mAcch.ChkWaterHit() && i_this->mAcch.m_wtr.GetHeight() > actor->current.pos.y && i_this->m440 == 0) {
                sibuki_set(i_this);
            }

            if(i_this->mAcch.ChkWallHit() && std::abs(actor->speedF) > 3.0f) {
                actor->speedF *= -0.5f;
            }

            if(i_this->m444 > 3) {
#if VERSION > VERSION_DEMO
                if(i_this->m444 != 2) {
                    return;
                }

                if(i_this->m436 == 0) {
                    return;
                }

                actor->speedF = 20.0f;
                actor->speed.y = 20.0f;
#endif
                return;
            }

            if(!i_this->mAcch.ChkGroundHit()) {
                actor->speedF *= 0.99f;
            }

            if(i_this->m436 == 0) {
                actor->shape_angle.x += 0x1000;
                cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 2, 0x800);
            }
            else {
                cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x800);
            }

            if((i_this->m440 == 0 && !i_this->mAcch.ChkGroundHit()) || (i_this->m440 && i_this->mAcch.m_wtr.GetHeight() < actor->current.pos.y)) {
                return;
            }

            if(i_this->mShapeType >= 8) {
                dComIfGp_getVibration().StartShock(1, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                fopAcM_monsSeStart(actor, JA_SE_CM_PG_L_JUMP, 0);

                if(strcmp(dComIfGp_getStartStageName(), "sea") == 0 && fopAcM_GetRoomNo(actor) == dIsleRoom_OutsetIsland_e && i_this->mAcch.GetGroundH() != -G_CM3D_F_INF && dComIfG_Bgsp()->GetSpecialCode(i_this->mAcch.m_gnd) != 4 && !dKy_daynight_check()) {
                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_3402);
                }
            }

            if(i_this->m440 != 0) {
                if(i_this->mShapeType >= 8) {
                    i_this->mStts.SetWeight(0x64);
                }
                else {
                    i_this->mStts.SetWeight(0x32);
                }

#if VERSION > VERSION_DEMO
                dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(actor));
#endif

                i_this->m41E = 2;
                i_this->m420 = 0x14;

                return;
            }

            cLib_addCalc0(&actor->speedF, 1.0f, 4.0f);

            dComIfGp_particle_set(dPa_name::ID_AK_JN_TUBA00, &actor->current.pos, &actor->shape_angle);

            if(i_this->mShapeType >= 8) {
                fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_CATCH, 0);
            }
            else {
                fopAcM_monsSeStart(actor, JA_SE_CV_PG_CATCH, 0);
            }

            i_this->m444 = 6;

            if(i_this->m436 == 0) {
                actor->speed.y = 20.0f;
                i_this->m436 = 1;

                if(i_this->mbCanBeBigPig == 4) {
                    i_this->m444 = 0x1E;
#if VERSION > VERSION_DEMO
                    actor->speed.y = 0.0f;
                    actor->speedF = 0.0f;
#endif
                }

                dComIfGp_getCamera(0)->mCamera.ForceLockOff(fopAcM_GetID(actor));

                if(i_this->m50C != 0x17) {
                    anm_init(i_this, dRes_INDEX_KB_BCK_WAIT1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_KB_BAS_WAIT1_e);
                }

                i_this->mSph.OnCoSetBit();
            }
            else {
                i_this->m420 = 0xD;

                if(i_this->mbCanBeBigPig == 2) {
                    i_this->m426[5] = 0x1E;
                }

                if(i_this->m404 == 0) {
                    i_this->m450 = actor->current.pos;
                }

                cLib_onBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
                i_this->m426[0] = 0x10;
                actor->speedF = 0.0f;
                i_this->m4B4 = 0.0f;
                actor->speed.set(0.0f, 0.0f, 0.0f);

                if(dComIfGs_getSelectEquip(0) != dItemNo_NONE_e) {
                    actor->health -= 1;
                }
            }

            break;
        case 0xD:
            cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x2000);

            if(i_this->m426[0] == 0 && !fopAcM_checkCarryNow(actor) && i_this->m444 == 0) {
#if VERSION > VERSION_DEMO
                i_this->mAcch.OffLineCheck();
#endif
                i_this->m4C4 = 30.0f;
                actor->shape_angle.x = 0;
                i_this->mSph.OnCoSetBit();
                
                anm_init(i_this, dRes_INDEX_KB_BCK_NAKU1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_KB_BAS_NAKU1_e);

                actor->speedF = 0.0f;
                i_this->m4B4 = 0.0f;
                actor->speed.set(0.0f, 0.0f, 0.0f);
                i_this->m422 = actor->current.angle.y;
                i_this->m426[2] = 0;
                i_this->m45C = actor->current.pos;
                i_this->m41E = 0;
                i_this->m420 = 6;

                if(actor->health <= 0) {
                    actor->health = 10;

                    ALL_ANGER = true;

                    actor->speedF = cM_rndFX(2.0f) + 15.0f;
                    i_this->mSph.OnAtSetBit();
                    i_this->mSph.OnAtHitBit();
                    i_this->m426[0] = 0x14;
                    actor->current.angle.y = actor->shape_angle.y;
                    i_this->m442 = fopAcM_searchPlayerAngleY(actor);
                    i_this->m5D4[0] = actor->current.pos;
                    i_this->m5EC[0] = actor->current.angle;
                    
                    smoke_set(i_this);

                    i_this->m448 = 0;
                    i_this->m420 = 0x24;
                }

                if(swim_mode_change_check(i_this)) {
                    return;
                }
            }
    }

#if VERSION > VERSION_DEMO
    if((i_this->m420 == 0xA || i_this->m420 == 0xB) && !fopAcM_checkCarryNow(actor)) {
        actor->gravity = -3.0f;

        if(actor->speedF <= 0.0f) {
            i_this->m4C4 = 30.0f;
            i_this->m426[0] = 0;

            if(i_this->mbCanBeBigPig == 2) {
                i_this->m426[5] = 0x1E;
            }

            if(i_this->mbCanBeBigPig == 3) {
                i_this->m594.end();
            }

            i_this->m420 = 0xD;
            cLib_onBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
        }
        else {
            i_this->m436 = 0;
            i_this->m4C4 = 30.0f;
            
            if(i_this->mbCanBeBigPig == 3) {
                i_this->m594.end();
            }

            anm_init(i_this, dRes_INDEX_KB_BCK_JITA2_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_KB_BAS_JITA2_e);

            actor->shape_angle.x = 0x8000;
            actor->speedF = 20.0f;
            actor->speed.y = 20.0f;
            i_this->m420 = 0xC;
        }
    }
#endif
}

/* 00003DEC-0000494C       .text swim_move__FP8kb_class */
void swim_move(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    dBgS_LinChk linChk;

#if VERSION > VERSION_DEMO
    csXyz temp(actor->shape_angle);
    int temp3 = 0;
#endif

    f32 temp2 = i_this->mAcch.m_wtr.GetHeight();

    switch(i_this->m420) {
        case 0x14:
            i_this->mSph.OffTgSetBit();
            i_this->mSph.ClrTgHit();
            actor->health = 10;
            i_this->m436 = 0;
            i_this->m438 = 0;
            i_this->m43A = 0;
            actor->shape_angle.z = 0;
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
            i_this->mSph.OnCoSetBit();
            anm_init(i_this, dRes_INDEX_KB_BCK_JITA1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_KB_BAS_JITA1_e);
            actor->speedF = 1.5f;
            actor->speed.x = 0.0f;
            actor->speed.z = 0.0f;
            actor->shape_angle.z = 0;
            actor->gravity = 0.0f;
            actor->speed.y = -20.0f;
            i_this->m420 += 1;
        case 0x15:
            cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x2000);
            cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 1, 0x2000);
            cLib_addCalc0(&actor->speed.y, 1.0f, 2.0f);

            if(actor->speed.y > -0.1f) {
                actor->shape_angle.x = 0;
                actor->shape_angle.z = 0;
                actor->speed.y = 0.0f;
                i_this->m420 += 1;
            }

            break;
        case 0x16:
        {
            f32 temp3 = i_this->m4D4 * (REG8_F(6) + 10.0f) + 10.0f;

            if(i_this->m426[6] == 0) {
                i_this->m426[6] = cM_rndF(15.0f) + 15.0f;

                if(i_this->mShapeType >= 8) {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_NORMAL, 0);
                }
                else {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PG_NORMAL, 0);
                }
            }

            i_this->m436 += 0x800;

            f32 temp4 = cM_ssin(i_this->m436) * (REG8_F(7) + 5.0f) + 29.0f;
            temp4 += i_this->m4D4 * (REG8_F(8) + 29.0f);
            cLib_addCalc2(&actor->current.pos.y, temp2 - temp4, 1.0f, 3.0f);

            if(std::abs(i_this->mAcch.m_wtr.GetHeight() - i_this->mAcch.GetGroundH()) < temp3) {
                i_this->m5D0 = 0.5f;

#if VERSION == VERSION_DEMO
                i_this->m540.setRate(0.0f);
#else
                if(i_this->m540.getEmitter()) {
                    i_this->m540.setRate(0.0f);
                }
#endif

                if(i_this->m50C != 0x18) {
                    anm_init(i_this, dRes_INDEX_KB_BCK_WALK1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, dRes_INDEX_KB_BAS_WALK1_e);
                }

                actor->gravity = -3.0f;
                i_this->m420 += 1;
            }

            carry_check(i_this);

            break;
        }
        case 0x17:
#if VERSION == VERSION_DEMO
            if(swim_mode_change_check(i_this) == TRUE) {
                return;
            }
#else
            if(swim_mode_change_check(i_this)) {
                return;
            }
#endif

            if(i_this->m440 == 0) {
                i_this->m540.end();
#if VERSION == VERSION_DEMO
                i_this->m420 = 0x18;
                i_this->m440 = 0;
#else
                i_this->m440 = 0;
                i_this->m420 = 0x18;
#endif
            }

            if(i_this->m426[6] == 0) {
                i_this->m426[6] = cM_rndF(15.0f) + 15.0f;

                if(i_this->mShapeType >= 8) {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_NORMAL, 0);
                }
                else {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PG_NORMAL, 0);
                }
            }

            carry_check(i_this);

            break;
        case 0x18:
            anm_init(i_this, dRes_INDEX_KB_BCK_DASSUI_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);

            i_this->m436 = 0;
#if VERSION > VERSION_DEMO
            actor->speedF = 0.0f;
#endif
            i_this->m420 += 1;

            break;
        case 0x19:
#if VERSION == VERSION_DEMO
            csXyz temp(actor->shape_angle);
            int temp3 = 0;
#endif

            if(i_this->mpMorf->checkFrame(10.0f) || i_this->mpMorf->checkFrame(11.0f)) {
                if(i_this->mpMorf->checkFrame(11.0f)) {
                    temp.y += 0x8000;
                    temp3 = 1;
                }

                if(i_this->m5A8[temp3].getEmitter() == NULL) {
                    dComIfGp_particle_set(dPa_name::ID_AK_SN_PIGDASSUI, &actor->current.pos, &temp, NULL, 0xFF, &i_this->m5A8[temp3], fopAcM_GetRoomNo(actor));
                }

                JPABaseEmitter* pEmtr = i_this->m5A8[temp3].getEmitter();
                if(pEmtr && i_this->m4D4) {
                    JGeometry::TVec3<f32> scale(2.0f, 2.0f, 2.0f);
                    pEmtr->setGlobalScale(scale);
                }
            }

            if(i_this->mpMorf->isStop() || carry_check(i_this) == TRUE) {
                for(int i = 0; i < 2; i++) {
                    i_this->m5A8[i].end();
                }

                i_this->m436 = 0;
                i_this->m438 = 0;
                i_this->m440 = 0;

                if(i_this->m41E != 1) {
                    i_this->mSph.OnTgSetBit();
                    cLib_onBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_MISC_e);

                    if(i_this->m404 == 0) {
                        i_this->m450 = actor->current.pos;
                    }

                    i_this->m41E = 0;
                    i_this->m420 = 2;
                    i_this->m426[1] = cM_rndF(20.0f) + 20.0f;
                    i_this->m426[3] = cM_rndF(20.0f) + 20.0f;
                }
            }
            break;
    }

#if VERSION > VERSION_DEMO
    actor->current.angle = actor->shape_angle;
#endif

    if(i_this->m420 >= 0x18) {
        return;
    }

    if(!actor->speed.y) {
        cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 4, 0x800);

        if(i_this->m43A == 0) {
            target_set(i_this, 2);
            i_this->m43A = 1;
            
            if(i_this->mAcch.ChkWallHit()) {
                cXyz temp1, temp2, temp3;
                dComIfG_Bgsp()->GetTriPnt(i_this->mAcchCir, &temp1, &temp2, &temp3);
                
                if((s16)cLib_distanceAngleS(actor->current.angle.y, cM_atan2s(temp1.x - actor->current.pos.x, temp1.z - actor->current.pos.z)) < 0x2000) {
                    if(cM_rnd() < 0.5f) {
                        i_this->m422 = actor->shape_angle.y + 0x4000;
                    }
                    else {
                        i_this->m422 = actor->shape_angle.y - 0x4000;
                    }

                    i_this->m43A = cM_rndF(20.0f) + 5.0f;
                }
            }
        }

        cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m422, 2, 0x200);
        if((s16)cLib_distanceAngleS(actor->shape_angle.y, i_this->m422) < 0x100 && i_this->m43A > 0) {
            i_this->m43A -= 1;
        }
    }

#if VERSION == VERSION_DEMO
    actor->current.angle = actor->shape_angle;
#endif
}

/* 0000494C-0000519C       .text attack_move__FP8kb_class */
void attack_move(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    daPy_py_c* pPlayer = daPy_getPlayerActorClass();

    switch(i_this->m420) {
        case 0x1E:
        {
            anm_init(i_this, dRes_INDEX_KB_BCK_DAMAGE1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);

            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);

            f32 diffX = i_this->m4DC.x - pPlayer->current.pos.x;
            f32 diffZ = i_this->m4DC.z - pPlayer->current.pos.z;
            f32 temp1 = std::sqrtf(diffX + diffX + diffZ * diffZ);
            actor->current.angle.y = cM_atan2s(diffX, diffZ);

            cMtx_YrotS(*calc_mtx, actor->current.angle.y);
            cXyz temp(0.0f, 0.0f, 12288.0f);
            cXyz temp2;
            MtxPosition(&temp, &temp2);
            i_this->m4FA.x = temp2.x;
            i_this->m4FA.z = temp2.z;

            actor->speedF = 50.0f;
            i_this->m420 += 1;

            break;
        }
        case 0x1F:
            cLib_addCalcAngleS2(&actor->shape_angle.x, i_this->m4FA.x, 1, 0x800);
            cLib_addCalcAngleS2(&actor->shape_angle.z, i_this->m4FA.z, 1, 0x800);
            cLib_addCalc0(&actor->speedF, 0.5f, 7.0f);

            if(i_this->mpMorf->isStop()) {
                actor->speedF = 0.0f;
                i_this->m420 += 1;
            }

            break;
        case 0x20:
            cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x800);
            cLib_addCalcAngleS2(&actor->shape_angle.z, 0, 1, 0x800);

            if(actor->shape_angle.x < 0x100 && actor->shape_angle.z < 0x100) {
                actor->shape_angle.x = 0;
                actor->shape_angle.z = 0;
                i_this->m420 = 4;
            }

            break;
        case 0x21:
        {
            if(i_this->m50C != 0x16) {
                anm_init(i_this, dRes_INDEX_KB_BCK_RUN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 2.0f, dRes_INDEX_KB_BAS_RUN1_e);
            }

            cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);

            f32 diffX = i_this->m4DC.x - actor->current.pos.x;
            f32 diffZ = i_this->m4DC.z - actor->current.pos.z;
            actor->shape_angle.x = 0;
            actor->shape_angle.z = 0;
            actor->shape_angle.y = cM_atan2s(diffX, diffZ);
            actor->current.angle.y = actor->shape_angle.y + 0x8000;
            actor->speedF = cM_rndFX(3.0f) + 7.0f;
            
            if(i_this->mShapeType < 8) {
                actor->speed.y = cM_rndFX(5.0f) + 30.0f;
            }

            i_this->mAcch.OnLineCheck();
            i_this->m4C4 = 30.0f;
            i_this->m420 += 1;

            break;
        }
        case 0x22:
            actor->shape_angle.x -= 0x2000;

            if(i_this->mAcch.ChkGroundHit()) {
                ALL_ANGER = false;

                i_this->mAcch.OffLineCheck();

                dComIfGp_getVibration().StartShock(1, -0x21, cXyz(0.0f, 1.0f, 0.0f));

                i_this->m420 = 0x23;
            }

            break;
        case 0x23:
            if(abs(actor->shape_angle.x) > 0x100) {
                actor->shape_angle.x -= 0x1000;
            }

            cLib_addCalc0(&actor->speedF, 1.0f, 4.0f);

            if(abs(actor->shape_angle.x) < 0x100) {
                actor->speedF = cM_rndFX(2.0f) + 15.0f;
                i_this->mSph.OnAtSetBit();
                i_this->mSph.OnAtHitBit();
                i_this->m426[0] = 0x14;
                actor->current.angle.y = actor->shape_angle.y;
                i_this->m442 = fopAcM_searchPlayerAngleY(actor);
                i_this->m5D4[0] = actor->current.pos;
                i_this->m5EC[0] = actor->current.angle;

                smoke_set(i_this);

                i_this->m448 = 0;
                i_this->m420 = 0x24;
            }

            break;
        case 0x24:
            bool temp = false;
            if(i_this->mSph.ChkAtHit()) {
                fopAc_ac_c* pPlayer = daPy_getPlayerActorClass();
                fopAc_ac_c* pHitActor = i_this->mSph.GetAtHitAc();
                if(pHitActor && pHitActor == pPlayer) {
                    temp = true;
                }
            }
            if(i_this->mSph.ChkAtShieldHit() || temp) {
                if(i_this->m50C != 0x16) {
                    anm_init(i_this, dRes_INDEX_KB_BCK_RUN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 2.0f, dRes_INDEX_KB_BAS_RUN1_e);
                }

                actor->current.angle.y = actor->shape_angle.y + 0x8000;
                actor->speedF = cM_rndFX(3.0f) + 7.0f;

                if(i_this->mShapeType < 8) {
                    actor->speed.y = cM_rndFX(5.0f) + 30.0f;
                }

                i_this->m4C4 = 30.0f;
                i_this->m41E = 3;
                i_this->m420 = 0x22;
                i_this->m554.end();
            }
            else {
                if((s16)cLib_distanceAngleS(actor->current.angle.y, i_this->m442) < 0x100) {
                    i_this->m442 = fopAcM_searchPlayerAngleY(actor) + cM_rndFX(4096.0f);
                }

                i_this->m5D4[0] = actor->current.pos;
                i_this->m5EC[0] = actor->current.angle;

                cLib_addCalcAngleS2(&actor->shape_angle.y, i_this->m442, 2, 0x2000);

                actor->current.angle.y = actor->shape_angle.y;

                if((i_this->mpMorf->checkFrame(0.0f) || i_this->mpMorf->checkFrame(5.0f)) && i_this->m426[2] == 0) {
                    if(i_this->mShapeType >= 8) {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_NORMAL, 0);
                    }
                    else {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_NORMAL, 0);
                    }
                }

                if(i_this->m426[2] == 0 && (s16)cLib_distanceAngleS(actor->current.angle.y, actor->shape_angle.y) > 0x4000) {
                    if(i_this->mShapeType >= 8) {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_TURN, 0);
                    }
                    else {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_TURN, 0);
                    }

                    i_this->m426[2] = 0x18;
                }

                actor->shape_angle.z = (actor->current.angle.y - actor->shape_angle.y) * 0.5f;
                if(actor->shape_angle.z < 0) {
                    if((int)(u16)actor->shape_angle.z < (u16)-0x1000) {
                        actor->shape_angle.z = -0x1000;
                    }
                }
                else if(actor->shape_angle.z > 0x1000) {
                    actor->shape_angle.z = 0x1000;
                }
            }
            break;
    }

#if VERSION == VERSION_DEMO
    if(swim_mode_change_check(i_this) == TRUE)
#else
    if(swim_mode_change_check(i_this))
#endif
    {
#if VERSION == VERSION_DEMO
        i_this->m554.end();
#endif
        
        actor->shape_angle.x = 0;
        actor->speed.y = 0.0f;
        actor->gravity = 0.0f;

        if(i_this->m420 == 0x22) {
            i_this->mAcch.OffLineCheck();
        }

        ALL_ANGER = false;

        i_this->mSph.ClrAtSet();
    }
}

/* 0000519C-000054A8       .text money_drop__FP8kb_class */
void money_drop(kb_class* i_this) {
    /* Nonmatching - regalloc */

    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    int i;

    static u32 gold_rate_dt[] = {
        dItemNo_GREEN_RUPEE_e, dItemNo_BLUE_RUPEE_e, dItemNo_YELLOW_RUPEE_e
    };
    static u32 item_rate_dt[] = {
        dItemNo_ARROW_10_e, dItemNo_BOMB_5_e, dItemNo_SMALL_MAGIC_e
    };

    csXyz temp = actor->current.angle;
    cXyz temp3;
    cXyz temp4;

    u8 count = 0;

    i_this->m407 = 0;

    for(i = 0; i < 2; i++) {
        f32 rnd = cM_rnd();
        if(REG8_S(4) == 0) {
            if(rnd < 0.9f) {
                rnd *= 10.0f;
                u32 temp2 = gold_rate_dt[(int)(0.3f * rnd)];
                i_this->m407 = 1;
                cMtx_YrotS(*calc_mtx, cM_rndFX(32768.0f));
                temp3.set(0.0f, 0.0f, 20.0f);
                MtxPosition(&temp3, &temp4);
                temp4 += actor->current.pos;

                fopAc_ac_c* pItem = (fopAc_ac_c*)fopAcM_fastCreateItem(&temp4, temp2, -1, &temp, &actor->scale, cM_rndF(5.0f), cM_rndF(10.0f) + 20.0f, -3.0f);
                if(pItem) {
                    fopAcM_OnStatus(pItem, fopAcStts_UNK4000_e);
                    fopAcM_seStart(actor, JA_SE_OBJ_LUPY_OUT, 0);
                    count += 1;
                }
            }
        }
    }

    for(i = 0; i < 2; i++) {
        f32 rnd = cM_rnd();
        if(rnd < 0.9f) {
            rnd *= 10.0f;
            u32 temp2 = item_rate_dt[(int)(0.3f * rnd)];
            i_this->m407 = 1;
            cMtx_YrotS(*calc_mtx, cM_rndFX(32768.0f));
            temp3.set(0.0f, 0.0f, 20.0f);
            MtxPosition(&temp3, &temp4);
            temp4 += actor->current.pos;

            fopAc_ac_c* pItem = (fopAc_ac_c*)fopAcM_fastCreateItem(&temp4, temp2, -1, &temp, &actor->scale, cM_rndF(5.0f), cM_rndF(10.0f) + 20.0f, -3.0f);
            if(pItem) {
                fopAcM_OnStatus(pItem, fopAcStts_UNK4000_e);

                if(count == 0) {
                    fopAcM_seStart(actor, JA_SE_OBJ_ITEM_OUT, 0);
                }
            }
        }
    }
}

/* 000054A8-00006670       .text esa_demo_move__FP8kb_class */
void esa_demo_move(kb_class* i_this) {
    /* Nonmatching - regalloc */

    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    daPy_py_c* pPlayer = daPy_getPlayerActorClass();
    camera_class* pCamera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    dBgS_LinChk linChk;

    switch(i_this->m420) {
        case 0x28:
            if(i_this->m50C != 0x18) {
                anm_init(i_this, dRes_INDEX_KB_BCK_WALK1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.5f, dRes_INDEX_KB_BAS_WALK1_e);
            }

            i_this->mSph.SetCoVsGrp(cCcD_CoSPrm_VsEnemy_e);
            fopAcM_OnStatus(actor, fopAcStts_UNK4000_e);
            i_this->m420 += 1;
        case 0x29:
            if(!actor->eventInfo.checkCommandDemoAccrpt()) {
                dComIfGp_event_onEventFlag(1);
                fopAcM_orderPotentialEvent(actor, dEvtType_OTHER_e, 0xFFFF, 0);
                actor->eventInfo.onCondition(dEvtCnd_UNK2_e);

                break;
            }

            pPlayer->changeOriginalDemo();
            pPlayer->changeDemoMode(daPy_demo_c::DEMO_N_WAIT_e);

            pCamera->mCamera.Stop();
            pCamera->mCamera.SetTrimSize(2);

            i_this->m426[0] = 200;
            i_this->m53C = 50.0f;
            i_this->m420 += 1;
        case 0x2A:
        {
            i_this->m520.x = actor->current.pos.x + REG12_F(1);
            i_this->m520.y = actor->current.pos.y + 60.0f + REG12_F(2);
            i_this->m520.z = actor->current.pos.z + REG12_F(3);
            cMtx_YrotS(*calc_mtx, REG12_F(4));
            cXyz temp;
            temp.x = 0.0f;
            temp.y = 0.0f;
            temp.z = REG12_F(5) + 300.0f;
            cXyz temp2;
            MtxPosition(&temp, &temp2);
            temp2 += i_this->field_0x498;
            temp2.y += REG12_F(7) + 300.0f;
            linChk.Set(&i_this->m520, &temp2, actor);
            if(dComIfG_Bgsp()->LineCross(&linChk)) {
                temp.z = -(REG12_F(5) + 300.0f);
                MtxPosition(&temp, &temp2);
                temp2 += i_this->field_0x498;
                temp2.y += REG12_F(7) + 300.0f;
            }
            
            i_this->m514 = temp2;
            actor->speedF = REG12_F(9) + 3.0f;
            f32 diffX = i_this->field_0x498.x - actor->current.pos.x;
            f32 diffZ = i_this->field_0x498.z - actor->current.pos.z;
            cLib_addCalcAngleS2(&actor->current.angle.y, (s16)cM_atan2s(diffX, diffZ), 4, 0x800);
            actor->shape_angle.y = actor->current.angle.y;

            if(i_this->mAcch.ChkWallHit()) {
                i_this->m426[0] = 0;
            }

            if(std::sqrtf(diffX * diffX + diffZ * diffZ) < 40.0f) {
                actor->speedF = 0.0f;
                actor->speed.setall(0.0f);
                
                anm_init(i_this, dRes_INDEX_KB_BCK_EAT1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 2.0f, dRes_INDEX_KB_BAS_EAT1_e);

                i_this->m44A = 1;
                i_this->m420 += 1;
            }
            else if(i_this->m426[0] == 0) {
                i_this->m420 = 0x31;
            }

            break;
        }
        case 0x2B:
            if(i_this->mpMorf->isStop()) {
                i_this->m44A -= 1;
                if(i_this->m44A == 0) {
                    if(i_this->m4D8 != fpcM_ERROR_PROCESS_ID_e) {
                        fopAc_ac_c* pEsa = fopAcM_SearchByID(i_this->m4D8);
                        if(pEsa) {
                            fopAcM_delete(pEsa);
                        }

                        i_this->m4D8 = fpcM_ERROR_PROCESS_ID_e;
                    }

                    anm_init(i_this, dRes_INDEX_KB_BCK_NAKU1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_KB_BAS_NAKU1_e);

                    if(i_this->mShapeType >= 8) {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_TURN, 0);
                    }
                    else {
                        fopAcM_monsSeStart(actor, JA_SE_CV_PG_TURN, 0);
                    }

                    i_this->m420 +=1;
                }
            }

            break;
        case 0x2C:
#if VERSION > VERSION_DEMO
            i_this->m40A = 0;
#endif

            if(i_this->mpMorf->isStop()) {
                if(i_this->mAcch.GetGroundH() != -G_CM3D_F_INF) {
                    if(dComIfG_Bgsp()->GetSpecialCode(i_this->mAcch.m_gnd) == 5) {
                        if(i_this->mShapeType >= 8) {
                            anm_init(i_this, dRes_INDEX_KB_BCK_RUN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 2.0f, dRes_INDEX_KB_BAS_RUN1_e);

                            i_this->m409 = 1;
                            i_this->m5D4[0] = actor->current.pos;
                            i_this->m5EC[0] = actor->current.angle;

                            smoke_set2(i_this);

                            i_this->m5D4[1] = actor->current.pos;
                            i_this->m5D4[1].y = i_this->mAcch.GetGroundH() + 15.0f;
                            i_this->m5EC[1] = actor->current.angle;

                            smoke_set3(i_this);

                            i_this->m420 += 1;
                        }
                        else {
                            i_this->m420 = 0x31;
                        }

                        break;
                    }

                    if(dComIfG_Bgsp()->GetAttributeCode(i_this->mAcch.m_gnd) == dBgS_Attr_DIRT_e || dComIfG_Bgsp()->GetAttributeCode(i_this->mAcch.m_gnd) == dBgS_Attr_GRASS_e || dComIfG_Bgsp()->GetAttributeCode(i_this->mAcch.m_gnd) == dBgS_Attr_SAND_e || dComIfG_Bgsp()->GetAttributeCode(i_this->mAcch.m_gnd) == dBgS_Attr_WATER_e) {
                        i_this->m5D4[0] = actor->current.pos;
                        i_this->m5EC[0] = actor->current.angle;

                        smoke_set2(i_this);

                        i_this->m5D4[1] = actor->current.pos;
                        i_this->m5D4[1].y = i_this->mAcch.GetGroundH() + 15.0f;
                        i_this->m5EC[1] = actor->current.angle;

                        smoke_set3(i_this);
                        anm_init(i_this, dRes_INDEX_KB_BCK_RUN1_e, 5.0f, J3DFrameCtrl::EMode_LOOP, 2.0f, dRes_INDEX_KB_BAS_RUN1_e);

                        i_this->m420 += 1;

                        break;
                    }
                }

                i_this->m420 = 0x31;
            }

            break;
        case 0x2D:
            if(i_this->m40A == 0) {
                if(i_this->mShapeType >= 8) {
                    fopAcM_seStart(actor, JA_SE_CM_PG_L_DIG, 0);
                }
                else {
                    fopAcM_seStart(actor, JA_SE_CM_PG_DIG, 0);
                }

                i_this->m40A = 1;
            }

            i_this->m5D4[0] = actor->current.pos;
            i_this->m5EC[0] = actor->current.angle;
            i_this->m5D4[1] = actor->current.pos;
            i_this->m5D4[1].y = i_this->mAcch.GetGroundH() + 15.0f;
            i_this->m5EC[1] = actor->current.angle;

            cLib_addCalcAngleS2(&actor->shape_angle.x, REG12_F(9) + 10000.0f, 1, REG12_F(10) + 300.0f);
            cLib_addCalc2(&i_this->m4C0, REG12_F(0xB) + -33.0f, 1.0f, REG12_F(0xC) + 1.0f);

            if(std::abs(i_this->m4C0 - (REG12_F(0xB) + -30.0f)) < 1.0f) {
                actor->shape_angle.x = REG12_F(9) + 10000.0f;
                i_this->m4C0 = -33.0f;
                i_this->m554.end();
                i_this->m574.end();
                
                if(i_this->m409 != 0) {
                    daTagKbItem_c* pItem = search_get_item(i_this);
                    if(pItem) {
                        pItem->kb_dig(actor);

                        i_this->m407 = 1;

                        if(actor->home.angle.z == 1) {
                            actor->home.angle.z = 0;
                            i_this->m407 = 0;

                            for(int i = 0; i < 10; i++) {
                                fopAcM_create(fpcNm_KS_e, 0x00000007, &actor->current.pos);
                            }
                        }
                    }
                    else {
                        money_drop(i_this);
                    }
                }
                else {
                    money_drop(i_this);
                }

                i_this->m426[0] = REG12_F(0xF) + 40.0f;
                i_this->m420 += 1;
            }

            break;
        case 0x2E:
            if(i_this->m426[0] == 0x23) {
                if(i_this->m407) {
                    pPlayer->changeDemoMode(daPy_demo_c::DEMO_SMILE_e);
                }
                else {
                    pPlayer->changeDemoMode(daPy_demo_c::DEMO_UNK_018_e);
                }
            }

            if(i_this->m426[0] == 0) {
                actor->shape_angle.x = -0x7FFF;
                
                pPlayer->changeDemoMode(daPy_demo_c::DEMO_N_WAIT_e);

                i_this->m5D4[1] = actor->current.pos;
                i_this->m5D4[1].y = i_this->mAcch.GetGroundH() + 15.0f + REG8_F(0x11);
                i_this->m5EC[1] = actor->current.angle;

                smoke_set3(i_this);

                actor->speed.y = REG12_F(0xE) + 20.0f;

                if(i_this->mShapeType >= 8) {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PG_L_CATCH, 0);
                }
                else {
                    fopAcM_monsSeStart(actor, JA_SE_CV_PG_CATCH, 0);
                }

                i_this->m426[0] = REG12_F(0xF) + 40.0f;
                i_this->m420 += 1;
            }

            break;
        case 0x2F:
            i_this->m5D4[1] = actor->current.pos;
            i_this->m5D4[1].y = i_this->mAcch.GetGroundH() + 15.0f + REG8_F(0x11);
            i_this->m5EC[1] = actor->current.angle;
            i_this->m520.x = actor->current.pos.x + REG12_F(1);
            i_this->m520.y = actor->current.pos.y + 60.0f + REG12_F(2);
            i_this->m520.z = actor->current.pos.z + REG12_F(3);
            
            cLib_addCalc2(&i_this->m4C0, REG12_F(0xB) + 30.0f, 1.0f, REG12_F(0xC) + 10.0f);
            cLib_addCalcAngleS2(&actor->shape_angle.x, 0, 1, 0x1000);

            if(i_this->m426[0] == 0 || (actor->speed.y < 0.0f && i_this->mAcch.GetGroundH() + 10.0f + REG8_F(5) > actor->current.pos.y)) {
                i_this->m574.end();

                if(i_this->mShapeType >= 8) {
                    dComIfGp_getVibration().StartShock(1, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                    fopAcM_seStart(actor, JA_SE_CM_PG_L_JUMP, 0);
                }
                else {
                    fopAcM_seStart(actor, JA_SE_CM_PG_DIG_LANDING, 0);
                }

                actor->shape_angle.x = 0;
                i_this->m4C0 = 30.0f;
                actor->speedF = 0.0f;

                anm_init(i_this, dRes_INDEX_KB_BCK_NAKU1_e, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, dRes_INDEX_KB_BAS_NAKU1_e);

                i_this->m420 += 1;
            }

            break;
        case 0x30:
            i_this->m520.x = actor->current.pos.x + REG12_F(1);
            i_this->m520.y = actor->current.pos.y + 60.0f + REG12_F(2);
            i_this->m520.z = actor->current.pos.z + REG12_F(3);

            if(i_this->mpMorf->isStop()) {
                i_this->m420 += 1;
            }

            break;
        case 0x31:
            if(i_this->mShapeType >= 8) {
                fopAcM_monsSeStart(actor, JA_SE_CM_PG_L_JUMP, 0);
            }

            pPlayer->cancelOriginalDemo();

            pCamera->mCamera.Reset(i_this->m520, i_this->m514);
            pCamera->mCamera.Start();
            pCamera->mCamera.SetTrimSize(0);

            dComIfGp_event_reset();

            fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
            i_this->mSph.SetCoVsGrp(cCcD_CoSPrm_VsGrpAll_e);

            DEMO_START = false;

            i_this->m406 = 0;
            i_this->m426[4] = 0x64;
            actor->gravity = -3.0f;
            i_this->m420 = 2;
            i_this->m41E = 0;

            break;
    }

    if(i_this->m420 >= 0x2A) {
        pCamera->mCamera.Set(i_this->m520, i_this->m514, i_this->m53C, 0);
        pPlayer->setPlayerPosAndAngle(&pPlayer->current.pos, fopAcM_searchActorAngleY(pPlayer, actor));
    }
}

/* 00006670-0000671C       .text BG_check__FP8kb_class */
void BG_check(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    i_this->mAcchCir.SetWall(i_this->m4D4 * (REG12_F(0x11) + 10.0f) + 25.0f, i_this->m4D4 * 30.0f + 35.0f);
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
#if VERSION > VERSION_DEMO
    actor->tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(i_this->mAcch.m_gnd);
    actor->tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(i_this->mAcch.m_gnd);
#endif
}

/* 0000671C-00006E38       .text daKb_Execute__FP8kb_class */
static BOOL daKb_Execute(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

#if VERSION > VERSION_DEMO
    if(REG8_S(1) != 0) {
        i_this->m540.setRate(1.0f);
    }
#endif

    for(int i = 0; i < 8; i++) {
        if(i_this->m426[i] != 0) {
            i_this->m426[i] -= 1;
        }
    }

    i_this->m446 += 1;

    switch(i_this->m41E) {
        case 0:
            pl_attack_hit_check(i_this);
            normal_move(i_this);

            if(i_this->m426[7] == 0 && i_this->mAcch.ChkGroundHit()) {
                if(i_this->mShapeType < 8 && strcmp(dComIfGp_getStartStageName(), "sea") == 0 && fopAcM_GetRoomNo(actor) == dIsleRoom_OutsetIsland_e) {
                    if(i_this->mAcch.GetGroundH() != -G_CM3D_F_INF && dComIfG_Bgsp()->GetSpecialCode(i_this->mAcch.m_gnd) == 4) {
                        u8 temp = 1 << (i_this->mShapeType & 3);
                        u8 temp2 = dComIfGs_getEventReg(dSv_event_flag_c::UNK_BFFF);
                        temp2 |= temp;
                        dComIfGs_setEventReg(dSv_event_flag_c::UNK_BFFF, temp2);
                        i_this->m405 = temp;
                    }
                    else {
                        i_this->m405 = 0;
                    }
                }

                if(i_this->mShapeType >= 8 && strcmp(dComIfGp_getStartStageName(), "sea") == 0 && fopAcM_GetRoomNo(actor) == dIsleRoom_OutsetIsland_e && i_this->mAcch.GetGroundH() != -G_CM3D_F_INF && dComIfG_Bgsp()->GetSpecialCode(i_this->mAcch.m_gnd) != 4) {
                    if(i_this->mShapeType >= 8) {
                        i_this->mStts.SetWeight(100);
                    }
                    else {
                        i_this->mStts.SetWeight(0x32);
                    }

                    dComIfGs_onEventBit(dSv_event_flag_c::UNK_3402);
                }
            }

            break;
        case 1:
            carry_move(i_this);
            break;
        case 2:
            swim_move(i_this);
            break;
        case 3:
            attack_move(i_this);
            break;
        case 4:
            esa_demo_move(i_this);
            break;
    }

    kb_eye_tex_anm(i_this);

    cXyz* ccMoveP = i_this->mStts.GetCCMoveP();
    if(ccMoveP) {
        actor->current.pos.x += ccMoveP->x;
        actor->current.pos.y += ccMoveP->y;
        actor->current.pos.z += ccMoveP->z;
    }

    if(i_this->m41E != 3) {
        f32 temp = i_this->m4D4 + 1.0f;
        if(i_this->m444) {
            i_this->m444 -= 1;

            if(i_this->m444 >= 3) {
                temp = i_this->m4D4 + 0.5625f;
            }
            else {
                temp = i_this->m4D4 + 1.125f;
            }
        }

        cLib_addCalc2(&i_this->m4E8.y, temp, 0.5f, 0.5f);
    }

#if VERSION == VERSION_DEMO
    draw_SUB(i_this);
#endif

    actor->attention_info.position = actor->current.pos;
    actor->attention_info.position.y += i_this->m4D4 * 50.0f + 50.0f;
    actor->eyePos = actor->attention_info.position;

#if VERSION > VERSION_DEMO
    cXyz temp = actor->current.pos;
    temp.y += i_this->m4D4 * 35.0f + 25.0f;
    i_this->mSph.SetC(temp);
    i_this->mSph.SetR(i_this->m4D4 * 25.0f + 20.0f);
    dComIfG_Ccsp()->Set(&i_this->mSph);
    dComIfG_Ccsp()->SetMass(&i_this->mSph, 3);
    temp = actor->current.pos;
    speed_pos_set(i_this);
    BG_check(i_this);
#endif

#if VERSION > VERSION_DEMO
    if(i_this->mAcch.GetGroundH() != -G_CM3D_F_INF)
#endif
    {
        s8 roomNo = fopAcM_GetRoomNo(actor);

        u32 mtrlSndId;
        if (i_this->mAcch.ChkGroundHit() != 0) {
            mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(i_this->mAcch.m_gnd);
        }
        else {
            mtrlSndId = 0;
        }

        i_this->mpMorf->play(&actor->eyePos, mtrlSndId, dComIfGp_getReverb(roomNo));
    }
#if VERSION > VERSION_DEMO
    else {
        i_this->mpMorf->play(NULL, 0, 0);
    }
#endif

    if(i_this->mAcch.ChkGroundHit()) {
        fopAcM_getGroundAngle(actor, &i_this->m4F4);

        if(i_this->m450.x == 0.0f && i_this->m450.y == 0.0f && i_this->m450.z == 0.0f) {
            i_this->m450 = actor->current.pos;
        }

        if(i_this->m41E != 1 && i_this->mAcch.GetGroundH() != -G_CM3D_F_INF) {
            i_this->m404 = 0;

            if(dComIfG_Bgsp()->GetAttributeCode(i_this->mAcch.m_gnd) == dBgS_Attr_WATER_e) {
                i_this->m404 = 1;
            }
        }
    }

#if VERSION == VERSION_DEMO
    cXyz temp = actor->current.pos;
    temp.y += i_this->m4D4 * 35.0f + 25.0f;
    i_this->mSph.SetC(temp);
    i_this->mSph.SetR(i_this->m4D4 * 25.0f + 20.0f);
    dComIfG_Ccsp()->Set(&i_this->mSph);
    dComIfG_Ccsp()->SetMass(&i_this->mSph, 3);
    temp = actor->current.pos;
    speed_pos_set(i_this);
    BG_check(i_this);
#else
    draw_SUB(i_this);
#endif

    if(fopAcM_checkCarryNow(actor)) {
        actor->current.pos = temp;
    }

    if(i_this->m41E == 3 && i_this->m420 >= 0x24) {
        if(actor->speed.y > -20.0f) {
            actor->speed.y -= 3.0f;
        }

        cXyz temp3 = actor->old.pos - actor->current.pos;
        f32 temp2 = temp3.abs();
        if(temp2 < 1.0f) {
            i_this->m448 += 1;
            if(i_this->m448 > 10) {
                ALL_ANGER = false;
                cLib_offBit<u32>(actor->attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
                i_this->mSph.OffAtSetBit();
                i_this->m41E = 0;
                i_this->m420 = 2;
                i_this->m554.end();
            }
        }
    }

    f32 temp2 = 0.0f;
    if(i_this->m426[5] || (0x21 <= i_this->m420 && i_this->m420 <= 0x24)) {
        i_this->m44C += (s16)(REG8_F(10) + 1000.0f);
        temp2 = 1.0f - (REG8_F(0xB) + 0.5f) * std::abs(cM_ssin(i_this->m44C));
    }

    cLib_addCalc2(&i_this->m4B0, temp2, 1.0f, 0.1f);

    return TRUE;
}

/* 00006E38-00006E40       .text daKb_IsDelete__FP8kb_class */
static BOOL daKb_IsDelete(kb_class* i_this) {
    return TRUE;
}

/* 00006E40-00006F28       .text daKb_Delete__FP8kb_class */
static BOOL daKb_Delete(kb_class* i_this) {
    fopAc_ac_c* actor = (fopAc_ac_c*)&i_this->actor;

    dComIfG_resDelete(&i_this->mPhs, "Kb");

#if VERSION > VERSION_DEMO
    if(actor->heap) {
        i_this->mpMorf->stopZelAnime();
    }
#endif

    i_this->m540.end();
    i_this->m554.end();
    i_this->m574.end();
    i_this->m594.end();
    for(int i = 0; i < 2; i++) {
        i_this->m5A8[i].end();
    }

    if(i_this->m406) {
        DEMO_START = false;
        i_this->m406 = 0;
    }

    return TRUE;
}

/* 00006F28-000071F4       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* i_actor) {
    /* Nonmatching - regalloc */
    kb_class* i_this = (kb_class*)i_actor;

    J3DModelData* pModelData;
    if(i_this->mShapeType >= 8) {
        pModelData = (J3DModelData*)dComIfG_getObjectRes("Kb", dRes_INDEX_KB_BDL_PG_BIG_e);
    }
    else {
        pModelData = (J3DModelData*)dComIfG_getObjectRes("Kb", dRes_INDEX_KB_BDL_PG_e);
    }

    i_this->mpMorf = new mDoExt_McaMorf(
        pModelData,
        NULL, NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Kb", dRes_INDEX_KB_BCK_WAIT1_e),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        dComIfG_getObjectRes("Kb", dRes_INDEX_KB_BAS_WAIT1_e),
        0x00080000,
        0x11020022
    );

    if (i_this->mpMorf == NULL || i_this->mpMorf->getModel() == NULL) {
        return FALSE;
    }
    J3DModel* pModel = i_this->mpMorf->getModel();

    J3DAnmTexPattern* pAnmTexPattern;
    for(int i = 0; i < 6; i++) {
        pAnmTexPattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Kb", kb_btp_idx[i]);
        pAnmTexPattern->searchUpdateMaterialID(pModel->getModelData());
    }

    u16 materialCount = pAnmTexPattern->getUpdateMaterialNum();
    i_this->mpTexNoAnm = new J3DTexNoAnm[materialCount];

    if(i_this->mpTexNoAnm == NULL) {
        return FALSE;
    }

    for(u16 i = 0; i < materialCount; i++) {
        i_this->mpTexNoAnm[i].setAnmIndex(i);
    }

    u32 temp = i_this->mShapeType & 3;
    if(i_this->mShapeType >= 8) {
        temp += 3;
    }

    tex_anm_set(i_this, temp);

    i_this->mpMaterialTable = (J3DMaterialTable*)dComIfG_getObjectRes("Kb", kb_bmt_idx[temp]);
    i_this->mpMorf->getModel()->setUserArea((u32)i_this);

    for (u16 i = 0; i < i_this->mpMorf->getModel()->getModelData()->getJointNum(); i++) {
        i_this->mpMorf->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
    }

    return TRUE;
}

/* 00007258-00007798       .text daKb_Create__FP10fopAc_ac_c */
static cPhs_State daKb_Create(fopAc_ac_c* i_actor) {
    static dCcD_SrcSph co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 4,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK6,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK6,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
        }},
    };

    fopAcM_ct(i_actor, kb_class);

    kb_class* i_this = (kb_class*)i_actor;

    cPhs_State status = dComIfG_resLoad(&i_this->mPhs, "Kb");
    if(status == cPhs_COMPLEATE_e) {
        i_this->mShapeType = (fopAcM_GetParam(i_this) >> 0) & 0xF;
        i_this->m401 = (fopAcM_GetParam(i_this) >> 4) & 0xF;
        i_this->mbCanBeBigPig = (fopAcM_GetParam(i_this) >> 8);
        i_this->m41D = (fopAcM_GetParam(i_this) >> 0x10);

        if(i_this->mShapeType == 0xFF) {
            i_this->mShapeType = 0;
        }

        if(i_this->m401 == 0xFF) {
            i_this->m401 = 0;
        }

        i_actor->health = 10;

        if(i_this->m41D != 0xFF) {
            i_this->mpPath = dPath_GetRoomPath(i_this->m41D, fopAcM_GetRoomNo(i_actor));
        }

        i_actor->gravity = -3.0f;

        if(i_this->mbCanBeBigPig != 0xFF) {
            if(strcmp(dComIfGp_getStartStageName(), "sea") == 0 && fopAcM_GetRoomNo(i_actor) == dIsleRoom_OutsetIsland_e) {
                u8 reg = dComIfGs_getEventReg(dSv_event_flag_c::UNK_BFFF);
                u8 temp = 1 << (i_this->mShapeType & 3);

                if(REG8_S(8)) {
                    dComIfGs_setEventReg(dSv_event_flag_c::UNK_BFFF, 0);
                    REG8_S(8) = 0;
                }

                if(REG8_S(9) || dComIfGs_isEventBit(dSv_event_flag_c::UNK_0520)) {
                    if(i_this->mbCanBeBigPig == 0) {
                        return cPhs_ERROR_e;
                    }

                    u8 temp4 = reg & 0xFF;
                    u8 temp3 = reg & 7;
                    u8 temp2 = i_this->mShapeType & 3;
                    if(temp3 == 0 || temp3 == 7) {
                        if(temp2 != 2) {
                            return cPhs_ERROR_e;
                        }
                    }
                    else if(temp3 == 5 || temp3 == 6) {
                        if(temp2 != 2) {
                            return cPhs_ERROR_e;
                        }
                    }
                    else if(temp3 == 3) {
                        if(temp2 != 0) {
                            return cPhs_ERROR_e;
                        }
                    }
                    else if((temp4 & temp) == 0) {
                        return cPhs_ERROR_e;
                    }
                
                    i_this->m4D4 = 2.0f;
                    fopAcM_SetParam(i_this, fopAcM_GetParam(i_this) + 8);
                    i_this->mShapeType += 8;
                    i_actor->attention_info.distances[fopAc_Attn_TYPE_CARRY_e] = 0x12;
                    fopAcM_OnStatus(i_actor, fopAcStts_UNK10000_e);
                }
                else {
                    if((reg & temp) == 0) {
                        if(i_this->mbCanBeBigPig == 1) {
                            return cPhs_ERROR_e;
                        }
                    }
                    else if(i_this->mbCanBeBigPig == 0) {
                        return cPhs_ERROR_e;
                    }
                }
            }

            if(strcmp(dComIfGp_getStartStageName(), "sea") == 0 && fopAcM_GetRoomNo(i_actor) == dIsleRoom_WindfallIsland_e && i_this->m41D != 0xFF && i_this->mpPath) {
                s32 point = cM_rndF(i_this->mpPath->m_num);
                if(point == 0) {
                    point = 1;
                }
                else if(point == i_this->mpPath->m_num) {
                    point -= 1;
                }
                i_actor->current.pos = i_this->mpPath->m_points[point].m_position;
                i_actor->current.pos.y += 150.0f;

                i_this->m401 = 3;
                if(i_this->mbCanBeBigPig == 2) {
                    i_actor->health = 5;
                }
            }
        }

        i_this->m4CC = i_this->m401 * 100.0f;
        if(!i_this->m4CC) {
            i_this->m4CC = 300.0f;
        }

        i_this->m4E8.setall(i_this->m4D4 + 1.0f);

        if(!fopAcM_entrySolidHeap(i_actor, useHeapInit, 0x3AB4)) {
            return cPhs_ERROR_e;
        }

        dKy_tevstr_init(&i_this->mTevStr, i_actor->home.roomNo, 0xFF);
        fopAcM_SetMtx(i_actor, i_this->mpMorf->getModel()->getBaseTRMtx());
        i_this->mAcch.Set(fopAcM_GetPosition_p(i_actor), fopAcM_GetOldPosition_p(i_actor), i_actor, 1, &i_this->mAcchCir,
                          fopAcM_GetSpeed_p(i_actor), NULL, NULL);
        i_this->mAcch.ClrWaterNone();
        i_this->mAcch.SetWaterCheckOffset(300.0f);
        i_this->m446 = cM_rndF(10000.0f);
        i_this->mStts.Init(0x32, 2, i_actor);
        i_this->mSph.Set(co_sph_src);
        i_this->mSph.SetStts(&i_this->mStts);

        if(i_this->mShapeType >= 8) {
            i_this->mSph.SetAtAtp(0xC);
        }

        i_actor->attention_info.flags = fopAc_Attn_LOCKON_MISC_e;
        fopAcM_SetModel(i_actor, i_this->mpMorf->getModel());

        if(i_this->mShapeType >= 8) {
            i_this->mStts.SetWeight(0xF0);
        }
        else {
            i_this->mStts.SetWeight(0x32);
        }

        i_this->mSph.ClrAtSet();
        i_this->m4C4 = 30.0f;
        i_this->m4C0 = 30.0f;
        i_this->m426[7] = 5;
        BG_check(i_this);
        draw_SUB(i_this);
    }

    return status;
}

static actor_method_class l_daKb_Method = {
    (process_method_func)daKb_Create,
    (process_method_func)daKb_Delete,
    (process_method_func)daKb_Execute,
    (process_method_func)daKb_IsDelete,
    (process_method_func)daKb_Draw,
};

actor_process_profile_definition g_profile_KB = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_KB_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kb_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_KB_e,
    /* Actor SubMtd */ &l_daKb_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENV_e,
    /* Cull Type    */ fopAc_CULLBOX_0_e,
};
