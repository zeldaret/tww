/**
 * d_a_sss.cpp
 * Enemy - Dexivine (Forbidden Woods, Wind Temple)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_sss.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "res/Object/Sss.h"

f32 size_d[10] = {10, 10, 9.5, 9.0, 8.5, 8.0, 7.5, 7.0, 6.5, 6.5};
f32 g_d[10] = {50, 50, 35, 25, 15, 9, 6, 6, 6, 6};

cXyz non_pos;

/* 000000EC-000001F0       .text hand_draw__FP9sss_class */
void hand_draw(sss_class* i_this) {
    /* Nonmatching */
    g_env_light.setLightTevColorType(i_this->field_0x2B4->getModel(), &i_this->tevStr);
    i_this->field_0x2B4->updateDL();
    GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    i_this->field_0x300.update(10, color, &i_this->tevStr);
    dComIfGd_set3DlineMat(&i_this->field_0x300);
    if (i_this->field_0x2FC > 0.1f) {
        GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
        i_this->field_0x454.update(5, color, &i_this->tevStr);
        dComIfGd_set3DlineMat(&i_this->field_0x454);
    }
}

/* 000001F0-00000248       .text daSss_Draw__FP9sss_class */
static BOOL daSss_Draw(sss_class* i_this) {
    /* Nonmatching */
    if (i_this->field_0x2B8 != 0) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->eyePos, &i_this->tevStr);
        hand_draw(i_this);
    }
    return TRUE;
}

/* 00000248-000002C8       .text hand_close__FP9sss_class */
void hand_close(sss_class* i_this) {
    /* Nonmatching */
    J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_TOJIRU_e);
    i_this->field_0x2B4->setAnm(anm, 0, 1, 1, 0, -1, NULL);
}

/* 000002C8-00000348       .text hand_open__FP9sss_class */
void hand_open(sss_class* i_this) {
    /* Nonmatching */
    J3DAnmTransform* anm = (J3DAnmTransform*)dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_HIRAKU_e);
    i_this->field_0x2B4->setAnm(anm, 0, 1, 1, 0, -1, NULL);
}

/* 00000348-00000444       .text hand_mtx_set__FP9sss_class */
void hand_mtx_set(sss_class* i_this) {
    /* Nonmatching */
    MtxTrans(i_this->field_0x2D4.x, i_this->field_0x2D4.y, i_this->field_0x2D4.z, false);
    mDoMtx_XrotM(*calc_mtx, i_this->field_0x2E0);
    mDoMtx_YrotM(*calc_mtx, i_this->field_0x2E2);
    mDoMtx_XrotM(*calc_mtx, REG12_S(1) + -0x4000);
    MtxScale(0.5, REG0_F(0) + 0.2f, 0.5, true);
    MtxTrans(0, REG12_F(3) + -130, 0, true);
    PSMTXCopy(*calc_mtx, i_this->field_0x2B4->getModel()->getBaseTRMtx());
}

/* 00000444-000004CC       .text control3__FP9sss_class */
void control3(sss_class* i_this) {
    /* Nonmatching */
    int iVar1;
    int iVar2;
    sss_s* pcVar3;
    int iVar4;

    pcVar3 = i_this->field_0x33C;
    iVar1 = 0;
    iVar2 = 0;
    for (iVar4 = 10; iVar4 != 0; iVar4--) {
        pcVar3->field_0x18 = (cM_ssin(i_this->field_0x2BC * 500 + iVar2) * 0.1 + 0.8) * size_d[iVar1];
        iVar1 = iVar1 + 4;
        iVar2 = iVar2 + 100;
        pcVar3 = pcVar3 + 1;
    }
}

/* 000004CC-00000804       .text control1__FP9sss_class */
void control1(sss_class* i_this) {
    /* Nonmatching */
    i_this->field_0x33C[0].field_0x00 = i_this->current.pos;
    sss_s* psVar1 = i_this->field_0x33C;
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    cXyz local_a4(0, 0, i_this->field_0x2F0);
    cXyz local_bc;
    MtxPosition(&local_a4, &local_bc);
    local_a4.z = i_this->field_0x2E8;
    float fVar1 = i_this->field_0x2F4;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    int iVar8;
    int iVar9;
    cXyz local_b0;
    cXyz local_c8;
    cXyz local_d4;
    for (int i = 1; i < 9; i++) {
        psVar1 = psVar1 + 1;
        local_b0.x = fVar1 * cM_ssin((i_this->field_0x2BC * REG0_S(5) + 1100) + i * (REG0_S(6) + 4000));
        local_b0.y = g_d[i];
        local_b0.z = fVar1 * cM_scos((i_this->field_0x2BC * REG0_S(7) + 800) + i * (REG0_S(8) + 4000));
        MtxPosition(&local_b0, &local_c8);
        fVar6 = local_c8.x * 1.0f + (psVar1->field_0x00.x - psVar1[-1].field_0x00.x) + local_bc.x * 1.0f;
        fVar4 = local_c8.y * 1.0f;
        fVar2 = psVar1->field_0x00.y;
        fVar3 = psVar1[-1].field_0x00.y;
        fVar5 = local_bc.y * 1.0f;
        fVar7 = local_c8.z * 1.0f + (psVar1->field_0x00.z - psVar1[-1].field_0x00.z) + local_bc.z * 1.0f;
        iVar8 = cM_atan2s(fVar6, fVar7);
        fVar6 = fVar6 * fVar6 + fVar7 * fVar7;
        fVar6 = std::sqrtf(fVar6);
        iVar9 = cM_atan2s(fVar4 + (fVar2 - fVar3) + fVar5, fVar6);
        MtxPush();
        mDoMtx_YrotS(*calc_mtx, iVar8);
        mDoMtx_XrotM(*calc_mtx, -iVar9);
        MtxPosition(&local_a4, &local_b0);
        MtxPull();
        local_d4 = psVar1[-1].field_0x00 + local_b0;
        psVar1->field_0x00 = local_d4;
    }
}

/* 00000840-00000B0C       .text control2__FP9sss_class */
void control2(sss_class* i_this) {
    /* Nonmatching */
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    int iVar5;
    int iVar6;
    sss_s *psVar7;
    int iVar8;
    cXyz local_90;
    cXyz local_84;
    cXyz cStack_78;

    cXyz local_6c(0, 0, i_this->field_0x2E8);
    i_this->field_0x33C[9].field_0x00 = i_this->field_0x2C8;
    psVar7 = i_this->field_0x33C + 8;
    for (iVar8 = 8; iVar8 > 0; iVar8--) {
        fVar3 = psVar7->field_0x00.x - psVar7[1].field_0x00.x;
        fVar1 = psVar7->field_0x00.y;
        fVar2 = psVar7[1].field_0x00.y;
        fVar4 = psVar7->field_0x00.z - psVar7[1].field_0x00.z;
        iVar5 = cM_atan2s(fVar3, fVar4);
        fVar3 = fVar3 * fVar3 + fVar4 * fVar4;
        fVar3 = std::sqrtf(fVar3);
        iVar6 = cM_atan2s(fVar1 - fVar2, fVar3);
        mDoMtx_YrotS(*calc_mtx, iVar5);
        mDoMtx_XrotM(*calc_mtx, -iVar6);
        if (iVar8 == 8) {
            local_6c.z = i_this->field_0x2E8 - 10;
            if (local_6c.z < 0) {
                local_6c.z = 0;
            }
        } else {
            local_6c.z = i_this->field_0x2E8;
        }
        MtxPosition(&local_6c, &cStack_78);
        local_84 = psVar7[1].field_0x00 + cStack_78;
        psVar7->field_0x00 = local_84;
        psVar7 = psVar7 - 1;
    }
    i_this->field_0x2D4 = i_this->field_0x33C[9].field_0x00;
    local_90 = i_this->field_0x33C[8].field_0x00 - i_this->field_0x33C[9].field_0x00;
    local_6c = local_90;
    iVar8 = cM_atan2s(local_90.y, local_90.z);
    i_this->field_0x2E0 = -iVar8;
    fVar1 = local_6c.y * local_6c.y + local_6c.z * local_6c.z;
    fVar1 = std::sqrtf(fVar1);
    iVar8 = cM_atan2s(local_6c.x, fVar1);
    i_this->field_0x2E2 = iVar8;
    hand_mtx_set(i_this);
}

/* 00000B0C-00000F78       .text cut_control1__FP9sss_class */
void cut_control1(sss_class* i_this) {
    /* Nonmatching */
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    int iVar5;
    int iVar6;
    JPABaseEmitter *pJVar7;
    sss_s *psVar8;
    int iVar9;
    cXyz local_d0;
    cXyz local_c4;
    cXyz local_b8;
    cXyz local_ac;
    cXyz local_a0;

    i_this->field_0x490[0].field_0x00 = i_this->current.pos;
    psVar8 = i_this->field_0x490;
    mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, i_this->current.angle.x);
    local_a0.z = i_this->field_0x2FC;
    fVar1 = REG0_F(18) + 50;
    for (iVar9 = 1; iVar9 < 5; iVar9++) {
        psVar8 = psVar8 + 1;
        local_ac.x = cM_ssin((i_this->field_0x2BC * REG0_S(5) + 4100) + iVar9 * REG0_S(6) + 10000);
        local_ac.y = REG0_F(17) + 50;
        local_ac.z = cM_scos((i_this->field_0x2BC * REG0_S(7) + 4400) + iVar9 * REG0_S(8) + 10000);
        MtxPosition(&local_ac, &local_b8);
        fVar2 = local_b8.x + (psVar8->field_0x00.x - psVar8[-1].field_0x00.x);
        fVar3 = local_b8.y + (psVar8->field_0x00.y - psVar8[-1].field_0x00.y);
        fVar4 = local_b8.z + (psVar8->field_0x00.z - psVar8[-1].field_0x00.z);
        iVar5 = cM_atan2s(fVar2, fVar4);
        fVar2 = fVar2 * fVar2 + fVar4 * fVar4;
        fVar2 = std::sqrtf(fVar2);
        iVar6 = cM_atan2s(fVar3, fVar2);
        MtxPush();
        mDoMtx_YrotS(*calc_mtx, iVar5);
        mDoMtx_XrotM(*calc_mtx, -iVar6);
        MtxPosition(&local_a0, &local_ac);
        MtxPull();
        local_c4 = psVar8[-1].field_0x00 - local_ac;
        psVar8->field_0x00 = local_c4;
    }
    if (!i_this->field_0xA10 && i_this->field_0xA18) {
        pJVar7 = dComIfGp_particle_set(0x8184, &i_this->field_0x490[4].field_0x00);
        i_this->field_0xA10 = pJVar7;
        i_this->field_0x2C2[1] = 60;
    }
    if (i_this->field_0xA10) {
        local_d0 = i_this->field_0x490[4].field_0x00 - i_this->field_0x490[3].field_0x00;
        local_a0 = local_d0;
        iVar9 = cM_atan2s(local_d0.x, local_d0.z);
        fVar1 = local_a0.x * local_a0.x + local_a0.z * local_a0.z;
        fVar1 = std::sqrtf(fVar1);
        iVar5 = cM_atan2s(local_a0.y, fVar1);
        fVar1 = i_this->field_0x490[4].field_0x00.z;
        fVar2 = i_this->field_0x490[4].field_0x00.y;
        pJVar7 = i_this->field_0xA10;
        pJVar7->setGlobalTranslation(i_this->field_0x490[4].field_0x00.x, fVar2, fVar1);
        i_this->field_0xA10->setGlobalRotation(JGeometry::TVec3<s16>(-iVar5, iVar9, 0));
        if (i_this->field_0x2C2[1] == 1) {
            pJVar7 = i_this->field_0xA10;
            pJVar7->becomeInvalidEmitter();
            i_this->field_0xA10 = NULL;
        }
    }
}

/* 00000F78-000014F4       .text cut_control2__FP9sss_class */
void cut_control2(sss_class* i_this) {
    /* Nonmatching */
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    int iVar6;
    int iVar7;
    JPABaseEmitter *pJVar8;
    sss_s *psVar9;
    int iVar10;
    cXyz local_ec;
    cXyz local_e0;
    cXyz local_d4;
    float local_c8;
    float local_c4;
    float local_c0;
    cXyz cStack_bc;

    cXyz local_b0(0, 0, i_this->field_0x2E8);
    i_this->field_0x33C[9].field_0x00 = i_this->field_0x2C8;
    psVar9 = i_this->field_0x33C + 8;
    fVar1 = i_this->field_0x2F4;
    for (iVar10 = 8; iVar10 > -1; iVar10--) {
        iVar6 = i_this->field_0x2BC;
        local_c8 = fVar1 * cM_ssin(iVar6 * (REG0_S(5) + 2500) + iVar10 * (REG0_S(6) + 3000));
        local_c4 = fVar1 * cM_ssin(iVar6 * (REG0_S(5) + 2950) + iVar10 * (REG0_S(6) + 4000));
        local_c0 = fVar1 * cM_scos(iVar6 * (REG0_S(7) + 2800) + iVar10 * (REG0_S(8) + 3500));
        fVar3 = local_c8 + (psVar9->field_0x00.x - psVar9[1].field_0x00.x);
        fVar4 = psVar9->field_0x00.y - 10 + local_c4;
        fVar2 = i_this->field_0x2F8 + 5;
        if (fVar4 < fVar2) {
            fVar4 = fVar2;
        }
        fVar2 = psVar9[1].field_0x00.y;
        fVar5 = local_c0 + (psVar9->field_0x00.z - psVar9[1].field_0x00.z);
        iVar6 = cM_atan2s(fVar3, fVar5);
        fVar3 = fVar3 * fVar3 + fVar5 * fVar5;
        fVar3 = std::sqrtf(fVar3);
        iVar7 = cM_atan2s(fVar4 - fVar2, fVar3);
        mDoMtx_YrotS(*calc_mtx, iVar6);
        mDoMtx_XrotM(*calc_mtx, -iVar7);
        if (iVar10 == 8) {
            local_b0.z = i_this->field_0x2E8 - 10;
            if (local_b0.z < 0) {
                local_b0.z = 0;
            }
        } else {
            local_b0.z = i_this->field_0x2E8;
        }
        MtxPosition(&local_b0, &cStack_bc);
        local_d4 = psVar9[1].field_0x00 + cStack_bc;
        psVar9->field_0x00 = local_d4;
        psVar9 = psVar9 - 1;
    }
    i_this->field_0x2D4 = i_this->field_0x33C[9].field_0x00;
    local_e0 = i_this->field_0x33C[8].field_0x00 - i_this->field_0x33C[9].field_0x00;
    local_b0 = local_e0;
    iVar10 = cM_atan2s(local_e0.y, local_e0.z);
    i_this->field_0x2E0 = -iVar10;
    fVar1 = local_b0.y * local_b0.y + local_b0.z * local_b0.z;
    fVar1 = std::sqrtf(fVar1);
    iVar10 = cM_atan2s(local_b0.x, fVar1);
    i_this->field_0x2E2 = iVar10;
    hand_mtx_set(i_this);
    if (!i_this->field_0xA14 && i_this->field_0xA18) {
        pJVar8 = dComIfGp_particle_set(0x8184, &i_this->field_0x33C[0].field_0x00);
        i_this->field_0xA14 = pJVar8;
    }
    if (i_this->field_0xA14) {
        local_ec = i_this->field_0x33C[0].field_0x00 - i_this->field_0x33C[1].field_0x00;
        local_b0 = local_ec;
        iVar10 = cM_atan2s(local_ec.x, local_ec.z);
        fVar1 = local_b0.x * local_b0.x + local_b0.z * local_b0.z;
        fVar1 = std::sqrtf(fVar1);
        iVar6 = cM_atan2s(local_b0.y, fVar1);
        fVar1 = i_this->field_0x33C[0].field_0x00.z;
        fVar2 = i_this->field_0x33C[0].field_0x00.y;
        pJVar8 = i_this->field_0xA14;
        pJVar8->setGlobalTranslation(i_this->field_0x33C[0].field_0x00.x, fVar2, fVar1);
        pJVar8->setGlobalRotation(JGeometry::TVec3<s16>(-iVar6, iVar10, 0));
        if (i_this->field_0x2C2[1] == 1) {
            pJVar8 = i_this->field_0xA14;
            pJVar8->becomeInvalidEmitter();
            i_this->field_0xA14 = NULL;
            i_this->field_0xA18 = false;
        }
    }
}

/* 000014F4-00002614       .text hand_move__FP9sss_class */
void hand_move(sss_class*) {
    /* Nonmatching */
}

/* 00002614-00002618       .text hand_main__FP9sss_class */
void hand_main(sss_class*) {
    /* Nonmatching */
}

/* 00002618-0000269C       .text daSss_Execute__FP9sss_class */
static BOOL daSss_Execute(sss_class* i_this) {
    /* Nonmatching */
    int j;

    i_this->field_0x2BC = i_this->field_0x2BC + 1;
    j = 0;
    for (int i = 2; i != 0; i--) {
        if (i_this->field_0x2C2[j] != '\0') {
            i_this->field_0x2C2[j] = i_this->field_0x2C2[j] - 1;
        }
        j = j + 1;
    }
    if (i_this->field_0x2C2[2] != '\0') {
        i_this->field_0x2C2[2] = i_this->field_0x2C2[2] - 1;
    }
    if (!i_this->field_0x2B8) {
        hand_main(i_this);
    } else {
        hand_move(i_this);
    }
    return TRUE;
}

/* 0000269C-000026A4       .text daSss_IsDelete__FP9sss_class */
static BOOL daSss_IsDelete(sss_class*) {
    return TRUE;
}

/* 000026A4-00002720       .text daSss_Delete__FP9sss_class */
static BOOL daSss_Delete(sss_class* i_this) {
    /* Nonmatching */
    dComIfG_resDelete(&i_this->field_0x2AC, "Sss");
    JPABaseEmitter* emitter = i_this->field_0xA10;
    if (emitter) {
        emitter->setMaxFrame(-1);
        emitter->setStatus(JPAEmtrStts_StopEmit);
    }
    emitter = i_this->field_0xA14;
    if (emitter) {
        emitter->setMaxFrame(-1);
        emitter->setStatus(JPAEmtrStts_StopEmit);
    }
    return TRUE;
}

/* 00002720-000028A0       .text useHeapInit__FP9sss_class */
BOOL useHeapInit(sss_class* i_this) {
    /* Nonmatching */
    BOOL ret;

    mDoExt_McaMorf* mca_morf = (mDoExt_McaMorf*) operator new(0xB4);
    if (mca_morf) {
        J3DAnmTransformKey* anm = (J3DAnmTransformKey*) dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BCK_SSS_HIRAKU_e);
        J3DModelData* model = (J3DModelData*) dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BMD_SSS_HAND_e);
        mca_morf = new mDoExt_McaMorf(model, NULL, NULL, anm, J3DFrameCtrl::EMode_NONE, 1, 0, -1, TRUE, NULL, 0, 0x11020203);
    }
    i_this->field_0x2B4 = mca_morf;
    if (!i_this->field_0x2B4->getModel()) {
        ret = FALSE;
    } else {
        ResTIMG* tex = (ResTIMG*) dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BTI_SSS_e);
        if (!i_this->field_0x300.init(1, 10, tex, TRUE)) {
            ret = FALSE;
        } else {
            tex = (ResTIMG*) dComIfG_getObjectRes("Sss", dRes_INDEX_SSS_BTI_SSS_e);
            ret = i_this->field_0x454.init(1, 5, tex, TRUE);
        }
    }
    return ret;
}

/* 000028A0-000028C0       .text daSss_solidHeapCB__FP10fopAc_ac_c */
static BOOL daSss_solidHeapCB(fopAc_ac_c* i_actor) {
    /* Nonmatching */
    return useHeapInit((sss_class*)i_actor);
}

/* 000028C0-00002BB4       .text daSss_Create__FP10fopAc_ac_c */
static cPhs_State daSss_Create(fopAc_ac_c* i_actor) {
    /* Nonmatching */
    static dCcD_SrcSph tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 20.0f,
        }},
    };
    static dCcD_SrcSph bm_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_BOOMERANG | AT_TYPE_WIND,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 80.0f,
        }},
    };

    fopAcM_ct(i_actor, sss_class);

    sss_class* i_this = (sss_class*) i_actor;

    cPhs_State state = dComIfG_resLoad(&i_this->field_0x2AC, "Sss");
    if (state == cPhs_COMPLEATE_e) {
        if (fopAcM_entrySolidHeap(i_actor, daSss_solidHeapCB, 0x3040)) {
            non_pos.x = 0;
            non_pos.y = 30000;
            non_pos.z = -20000;
            i_this->field_0x2B8 = fopAcM_GetParam(i_this);
            if (i_this->field_0x2B8 == 0xFF) {
                i_this->field_0x2B8 = 0;
            }
            if (i_this->field_0x2B8 != 1) {
                i_this->field_0x2B8 = 0x23;
            }
            i_this->field_0x2B9 = fopAcM_GetParam(i_this) >> 8;
            i_this->field_0x2BA = fopAcM_GetParam(i_this) >> 0x10;
            if (i_this->field_0x2BA == 0xFF) {
                i_this->field_0x2BA = false;
            }
            i_this->health = 2;
            i_this->field_0x2BC = cM_rndF(10000);
            i_this->field_0x51C.Init(0xFF, 0xFF, i_this);
            for (int i = 0; i < 3; i++) {
                i_this->field_0x558[i].Set(tg_sph_src);
                i_this->field_0x558[i].SetStts(&i_this->field_0x51C);
            }
            i_this->field_0x8DC.Set(bm_sph_src);
            i_this->field_0x8DC.SetStts(&i_this->field_0x51C);
            i_this->field_0x2C8 = i_this->current.pos;
            if (!i_this->field_0x2BA) {
                i_this->field_0x2C8.y = i_this->field_0x2C8.y + 230;
            }
            daSss_Execute(i_this);
        } else {
            state = cPhs_ERROR_e;
        }
    }
    return state;
}

static actor_method_class l_daSss_Method = {
    (process_method_func)daSss_Create,
    (process_method_func)daSss_Delete,
    (process_method_func)daSss_Execute,
    (process_method_func)daSss_IsDelete,
    (process_method_func)daSss_Draw,
};

actor_process_profile_definition g_profile_SSS = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_SSS_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sss_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_SSS_e,
    /* Actor SubMtd */ &l_daSss_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
