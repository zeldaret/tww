/**
 * d_a_bmdhand.cpp
 * Boss - Kalle Demos (ceiling tentacles) / 森ボス触手 (Forest boss tentacle)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bmdhand.h"
#include "d/d_s_play.h"
#include "d/res/res_bmdhand.h"
#include "d/actor/d_a_bmd.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

class daBmdhand_HIO_c : public JORReflexible {
public:
    daBmdhand_HIO_c();
    virtual ~daBmdhand_HIO_c() {};

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05[0x08 - 0x05];
    /* 0x06 */ f32 m08;
    /* 0x0C */ s16 m0C;
};

/* 000000EC-00000118       .text __ct__15daBmdhand_HIO_cFv */
daBmdhand_HIO_c::daBmdhand_HIO_c() {
    mNo = 0xFF;
    m08 = -20.0f;
    m0C = 1000;
}

static bmd_class* boss;
static bool hio_set;
static daBmdhand_HIO_c l_HIO;

static s32 boss_joint_d[] = {0x1C, 0x1C, 0x1C, 0x1C, 0x25, 0x25, 0x25, 0x25, 0x2E, 0x2E, 0x2E, 0x2E, 0x40, 0x40, 0x40, 0x40, 0x37, 0x37, 0x37, 0x37};
static f32 boss_joint_xad[] = {60.0f, 20.0f, -20.0f, -60.0f};

/* 00000118-000001CC       .text hand_draw__FP13bmdhand_class */
void hand_draw(bmdhand_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m320 > 0.01f) {
        g_env_light.setLightTevColorType(i_this->m2B4->getModel(), &actor->tevStr);
        i_this->m2B4->updateDL();
    }
    GXColor local_18 = {0xFF, 0xFF, 0xFF, 0xFF};
    i_this->m554.update(0x14, local_18, &actor->tevStr);
    dComIfGd_set3DlineMat(&i_this->m554);
}

/* 000001CC-0000022C       .text daBmdhand_Draw__FP13bmdhand_class */
static BOOL daBmdhand_Draw(bmdhand_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m310 > 0.1f) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->eyePos, &actor->tevStr);
        hand_draw(i_this);
    }
    return TRUE;
}

/* 0000022C-00000310       .text hand_mtx_set__FP13bmdhand_class */
void hand_mtx_set(bmdhand_class* i_this) {
    f32 x;

    MtxTrans(i_this->m2F0.x, i_this->m2F0.y, i_this->m2F0.z, false);
    mDoMtx_XrotM(*calc_mtx, i_this->m300);
    mDoMtx_YrotM(*calc_mtx, i_this->m302);
    mDoMtx_XrotM(*calc_mtx, REG12_S(1) + -0x4000);
    x = i_this->m320;
    MtxScale(x, x, x, true);
    MtxTrans(0.0f, REG12_F(3) + -130.0f, 0.0f, true);
    i_this->m2B4->getModel()->setBaseTRMtx(*calc_mtx);
}

/* 00000310-00000388       .text control3__FP13bmdhand_class */
void control3(bmdhand_class* i_this) {
    hand_s* phVar1 = &i_this->m324[0];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m324); i++, phVar1++) {
        if (i < 10) {
            phVar1->m18 = 10.5f;
        } else {
            phVar1->m18 = (15.0f - (s32)(i - 10U)) * 0.7f;
        }
    }
}

/* 00000388-000006E4       .text control1__FP13bmdhand_class */
void control1(bmdhand_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 dVar8;
    f32 dVar10;
    f32 dVar7;

    i_this->m324[0].m00 = actor->current.pos;
    s32 i = 1;
    hand_s* phVar5 = &i_this->m324[1];
    mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cXyz local_94;
    cXyz cStack_a0;
    cXyz local_ac;
    local_94.x = 0.0f;
    local_94.y = i_this->m314;
    local_94.z = i_this->m318;
    MtxPosition(&local_94, &local_ac);
    cLib_addCalc2(&i_this->m314, REG0_F(7) + -10.0f, 1.0f, 0.1f);
    cLib_addCalc2(&i_this->m318, REG0_F(8) + 50.0f, 1.0f, 1.0f);
    local_94.z = i_this->m310;
    f32 dVar9 = i_this->m31C;
    cXyz local_c4;
    for (i = 1; i < 0x13; i++, ++phVar5) {
        local_c4.x = (dVar9 * cM_ssin(i_this->m2B8 * (REG0_S(5) + 0x44c) + i * (REG0_S(6) + 4000)));
        local_c4.z = (dVar9 * cM_scos(i_this->m2B8 * (REG0_S(7) + 800) + i * (REG0_S(8) + 4000)));
        f32 fVar1 = (i < 15) ? 1.0f : 1.0f - (i - 15) * 0.2f;
        dVar8 = phVar5->m00.x - phVar5[-1].m00.x + (local_ac.x * fVar1) + (local_c4.x * fVar1);
        dVar10 = phVar5->m00.y - phVar5[-1].m00.y + local_ac.y;
        dVar7 = phVar5->m00.z - phVar5[-1].m00.z + (local_ac.z * fVar1) + (local_c4.z * fVar1);
        s16 iVar4;
        int iVar3 = cM_atan2s(dVar8, dVar7);
        iVar4 = -cM_atan2s(dVar10, std::sqrtf((dVar8 * dVar8) + (dVar7 * dVar7)));
        mDoMtx_YrotS(*calc_mtx, iVar3);
        mDoMtx_XrotM(*calc_mtx, iVar4);
        MtxPosition(&local_94, &cStack_a0);
        phVar5->m00 = phVar5[-1].m00 + cStack_a0;
    }
}

/* 000006E4-00000A1C       .text control2__FP13bmdhand_class */
void control2(bmdhand_class* i_this) {
    cXyz local_7c;
    cXyz cStack_88;

    local_7c.x = 0.0f;
    local_7c.y = 0.0f;
    local_7c.z = i_this->m310;
    cLib_addCalc2(&i_this->m324[0x13].m00.x, (i_this->m2D8).x, 1.0f, i_this->m30C * 50.0f);
    cLib_addCalc2(&i_this->m324[0x13].m00.y, (i_this->m2D8).y, 1.0f, i_this->m30C * 50.0f);
    cLib_addCalc2(&i_this->m324[0x13].m00.z, (i_this->m2D8).z, 1.0f, i_this->m30C * 50.0f);
    cLib_addCalc2(&i_this->m30C, 1.0f, 1.0f, 0.01f);
    s32 i = 0x12;
    s16 iVar4;
    int iVar3;
    hand_s* phVar5 = &i_this->m324[0x12];
    for (i = 0x12; i >= 1; i--, phVar5--) {
        f32 fVar1 = phVar5->m00.x - phVar5[1].m00.x;
        f32 dVar9 = ((phVar5->m00.y - phVar5[1].m00.y) - 10.0f);
        f32 fVar2 = phVar5->m00.z - phVar5[1].m00.z;
        iVar3 = cM_atan2s(fVar1, fVar2);
        iVar4 = -cM_atan2s(dVar9, std::sqrtf((fVar1 * fVar1) + (fVar2 * fVar2)));
        mDoMtx_YrotS(*calc_mtx, iVar3);
        mDoMtx_XrotM(*calc_mtx, iVar4);
        if (i == 0x12) {
            local_7c.z = i_this->m310 + 70.0f + REG12_F(6);
        } else {
            local_7c.z = i_this->m310;
        }
        MtxPosition(&local_7c, &cStack_88);
        phVar5->m00 = phVar5[1].m00 + cStack_88;
    }
    i_this->m2F0 = i_this->m324[0x13].m00;
    local_7c = i_this->m324[0x12].m00 - i_this->m324[0x13].m00;
    i_this->m300 = -cM_atan2s(local_7c.y, local_7c.z);
    i_this->m302 = cM_atan2s(local_7c.x, std::sqrtf(local_7c.y * local_7c.y + local_7c.z * local_7c.z));
    hand_mtx_set(i_this);
}

/* 00000A1C-00000EFC       .text cut_control__FP13bmdhand_class */
void cut_control(bmdhand_class* i_this) {
    /* Nonmatching - regalloc */
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    f32 fVar2;
    f32 fVar3;
    f32 dVar8;
    f32 dVar9;
    f32 dVar10;
    f32 dVar11;
    cXyz local_e8;
    cXyz cStack_f4;
    cXyz local_100;
    cXyz local_110;
    cXyz local_124;

    i_this->m324[0].m00 = actor->current.pos;
    hand_s* pcVar6 = &i_this->m324[1];
    mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
    local_e8.x = 0.0f;
    local_e8.y = i_this->m314;
    local_e8.z = i_this->m318;
    MtxPosition(&local_e8, &local_100);
    cLib_addCalc2(&i_this->m314, REG14_F(7) + -3.0f, 1.0f, REG12_F(4) + 0.1f);
    cLib_addCalc2(&i_this->m318, REG14_F(8) + 20.0f + 10.0f, 1.0f, REG12_F(5) + 0.2f);
    cLib_addCalc0(&i_this->m31C, (REG12_F(6) + 1.0f), 1.0f);
    local_e8.z = i_this->m310;
    dVar9 = (REG7_F(10) + 0.5f);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m324); i++, pcVar6++) {
        local_124.x = i_this->m31C * cM_ssin(i_this->m2B8 * (REG0_S(4) + 0xdac) + i * (REG0_S(5) + 4000));
        local_124.y = i_this->m31C * cM_scos(i_this->m2B8 * (REG0_S(6) + 4000) + i * (REG0_S(7) + 4000));
        local_124.z = i_this->m31C * cM_scos(i_this->m2B8 * (REG0_S(8) + 0xed8) + i * (REG0_S(9) + 4000));
        f32 factor = 1.0f - i * (REG0_F(9) + 0.03763158f);
        local_110.x = local_100.x * factor;
        local_110.z = local_100.z * factor;
        fVar2 = pcVar6[1].m00.x + local_124.x + (local_110.x + (pcVar6->m00.x - pcVar6[-1].m00.z));
        dVar11 = fVar2;
        fVar3 = pcVar6[1].m00.y + (local_124.y + pcVar6->m00.y + local_100.y);
        fVar1 = (5.0f + boss->m328);
        if (fVar3 < fVar1) {
            fVar3 = fVar1;
        }
        dVar10 = (fVar3 - pcVar6[-1].m00.x);
        fVar1 = pcVar6[1].m00.z + local_124.z + (local_110.z + (pcVar6->m00.z - pcVar6[-1].m00.y));
        dVar8 = fVar1;
        int iVar4 = cM_atan2s(fVar2, fVar1);
        s16 iVar5 = -cM_atan2s(dVar10, std::sqrtf((dVar11 * dVar11) + (dVar8 * dVar8)));
        mDoMtx_YrotS(*calc_mtx, iVar4);
        mDoMtx_XrotM(*calc_mtx, iVar5);
        MtxPosition(&local_e8, &cStack_f4);
        pcVar6[1].m00 = pcVar6->m00;
        pcVar6[0].m00 = pcVar6[-1].m00 + cStack_f4;
        pcVar6[1].m00.x = (dVar9 * (pcVar6->m00.x - pcVar6[1].m00.x));
        pcVar6[1].m00.y = (dVar9 * (pcVar6->m00.y - pcVar6[1].m00.y));
        pcVar6[1].m00.z = (dVar9 * (pcVar6->m00.z - pcVar6[1].m00.z));
        if ((i == 0x13) && (i_this->m2CA != 0)) {
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8067, &pcVar6->m00, 0xFF, g_whiteColor, g_whiteColor, 0);
        }
    }
}

/* 00000EFC-00000FAC       .text cut_control3__FP13bmdhand_class */
void cut_control3(bmdhand_class* i_this) {
    hand_s* phVar1 = &i_this->m324[0];

    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m324); i++, phVar1++) {
        if (i < 10) {
            phVar1->m18 = 10.5f;
        } else {
            phVar1->m18 = (15.0f - (s32)(i - 10U)) * 0.7f;
        }
    }
    cLib_addCalc2(&i_this->m2F0.y, i_this->m2CC.y, 1.0f, 10.0f);
    hand_mtx_set(i_this);
}

/* 00000FAC-000012DC       .text start_control1__FP13bmdhand_class */
void start_control1(bmdhand_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    f32 fVar2;
    f32 dVar10;
    cXyz local_94;
    cXyz cStack_a0;
    cXyz local_ac;
    cXyz local_c4;

    i_this->m324[0].m00 = actor->current.pos;
    s32 i = 1;
    hand_s* phVar5 = &i_this->m324[i];
    mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
    local_94.x = 0.0f;
    local_94.y = i_this->m314;
    local_94.z = i_this->m318;
    MtxPosition(&local_94, &local_ac);
    cLib_addCalc2(&i_this->m314, REG0_F(7), 1.0f, 0.1f);
    cLib_addCalc2(&i_this->m318, REG0_F(8) + 5.0f, 1.0f, 1.0f);
    local_94.z = i_this->m310;
    f32 dVar9 = i_this->m31C;
    for (i = 1; i < 0x13; i++, phVar5++) {
        local_c4.x = (dVar9 * cM_ssin(i_this->m2B8 * (REG0_S(5) + 0x640) + i * (REG0_S(6) + 3000)));
        local_c4.y = (dVar9 * cM_ssin(i_this->m2B8 * (REG0_S(5) + 0x6a4) + i * (REG0_S(6) + 4000)));
        local_c4.z = (dVar9 * cM_scos(i_this->m2B8 * (REG0_S(7) + 0x578) + i * (REG0_S(8) + 0xdac)));
        fVar1 = local_c4.x + (local_ac.x + (phVar5->m00.x - phVar5[-1].m00.x));
        dVar10 = local_c4.y + (local_ac.y + (phVar5->m00.y - phVar5[-1].m00.y));
        fVar2 = local_c4.z + (local_ac.z + (phVar5->m00.z - phVar5[-1].m00.z));
        s16 iVar4;
        int iVar3 = cM_atan2s(fVar1, fVar2);
        iVar4 = -cM_atan2s(dVar10, std::sqrtf((fVar1 * fVar1) + (fVar2 * fVar2)));
        mDoMtx_YrotS(*calc_mtx, iVar3);
        mDoMtx_XrotM(*calc_mtx, iVar4);
        MtxPosition(&local_94, &cStack_a0);
        phVar5->m00 = phVar5[-1].m00 + cStack_a0;
    }
}

/* 000012DC-0000158C       .text start_control2__FP13bmdhand_class */
void start_control2(bmdhand_class* i_this) {
    cXyz local_7c;
    cXyz cStack_88;

    local_7c.x = 0.0f;
    local_7c.y = 0.0f;
    local_7c.z = i_this->m310;
    i_this->m324[0x13].m00 = (i_this->m2D8);
    s32 i = 0x12;
    s16 iVar4;
    int iVar3;
    hand_s* phVar5 = &i_this->m324[i];
    for (i = 0x12; i >= 1; i--, phVar5--) {
        f32 fVar1 = phVar5->m00.x - phVar5[1].m00.x;
        f32 dVar9 = ((phVar5->m00.y - phVar5[1].m00.y) - 5.0f);
        f32 fVar2 = phVar5->m00.z - phVar5[1].m00.z;
        iVar3 = cM_atan2s(fVar1, fVar2);
        iVar4 = -cM_atan2s(dVar9, std::sqrtf((fVar1 * fVar1) + (fVar2 * fVar2)));
        mDoMtx_YrotS(*calc_mtx, iVar3);
        mDoMtx_XrotM(*calc_mtx, iVar4);
        MtxPosition(&local_7c, &cStack_88);
        phVar5->m00 = phVar5[1].m00 + cStack_88;
    }
    i_this->m2F0 = i_this->m324[0x13].m00;
    local_7c = i_this->m324[0x12].m00 - i_this->m324[0x13].m00;
    i_this->m300 = -cM_atan2s(local_7c.y, local_7c.z);
    i_this->m302 = cM_atan2s(local_7c.x, std::sqrtf(local_7c.y * local_7c.y + local_7c.z * local_7c.z));
    hand_mtx_set(i_this);
}

/* 0000158C-0000161C       .text hand_close__FP13bmdhand_class */
void hand_close(bmdhand_class* i_this) {
    J3DAnmTransform* pAnimRes;

    pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Bmdhand", BMDHAND_BCK_FOOK_TOJIRU);
    i_this->m2B4->setAnm(pAnimRes, 0, REG0_F(6) + 5.0f, 1.0f, 0.0f, -1.0f, NULL);
}

/* 0000161C-000016AC       .text hand_open__FP13bmdhand_class */
void hand_open(bmdhand_class* i_this) {
    J3DAnmTransform* pAnimRes;

    pAnimRes = (J3DAnmTransform*)dComIfG_getObjectRes("Bmdhand", BMDHAND_BCK_FOOK_HIRAKU);
    i_this->m2B4->setAnm(pAnimRes, 0, REG0_F(6) + 5.0f, 1.0f, 0.0f, -1.0f, NULL);
}

/* 000016AC-00001D30       .text hand_calc__FP13bmdhand_class */
void hand_calc(bmdhand_class* i_this) {
    /* Nonmatching - swapped fadds instruction */
    fopAc_ac_c* actor = &i_this->actor;
    f32 dVar6;
    f32 fVar7;
    cXyz local_b8;
    cXyz local_c4;

    local_b8.y = 0.0f;
    local_b8.x = 0.0f;
    if ((i_this->m2B8 & 0xfU) == 0) {
        dBgS_LinChk local_ac;
        cXyz local_d0(i_this->m2D8);
        cXyz local_dc(local_d0);
        local_dc.y = local_d0.y + 2500.0f;
        local_ac.Set(&local_d0, &local_dc, actor);
        if (dComIfG_Bgsp()->LineCross(&local_ac)) {
            i_this->m2CC = local_ac.GetCross();
            i_this->m2CC.y += l_HIO.m08;
        }
    }
    switch (i_this->m2BC) {
    case 0:
        mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
        if ((actor->base.mParameters & 1U) == 0) {
            local_b8.z = REG0_F(9) + 250.0f;
        } else {
            local_b8.z = REG0_F(10) + 350.0f;
        }
        MtxPosition(&local_b8, &local_c4);
        i_this->m2D8 = actor->current.pos + local_c4;
        i_this->m2D8.y = i_this->m2CC.y;
        i_this->m2E4 = i_this->m2D8;
        if (i_this->m30C > 0.9f) {
            if (boss->m331 < 0x14) {
                boss->m331++;
            }
            i_this->m2BC = 1;
            i_this->m2C0[0] = (s16)(cM_rndF(30.0f) + 10.0f);
            mDoAud_seStart(JA_SE_CM_BKM_VINE_SET, &i_this->m2D8, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        break;
    case 1:
        mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
        if ((actor->base.mParameters & 1U) == 0) {
            local_b8.z = REG0_F(9) + 250.0f;
        } else {
            local_b8.z = REG0_F(10) + 350.0f;
        }
        MtxPosition(&local_b8, &local_c4);
        i_this->m2E4.x = actor->current.pos.x + local_c4.x;
        i_this->m2E4.z = actor->current.pos.z + local_c4.z;
        local_c4 = i_this->m2E4 - i_this->m2D8;
        fVar7 = std::sqrtf(local_c4.x * local_c4.x + local_c4.z * local_c4.z);
        if (fVar7 > REG14_F(0) + 100.0f) {
            if (i_this->m2C0[0] == 0) {
                i_this->m2BC = 2;
                i_this->m2C0[0] = 0x28;
                i_this->m308 = 0.0f;
            }
        } else {
            i_this->m2C0[0] = (s16)cM_rndF(30.0f);
        }
        break;
    case 2:
        if (i_this->m2C0[0] <= 0x14) {
            if (i_this->m2C0[0] == 0x14) {
                i_this->m308 = 0.0f;
            }
            i_this->m2E4.y = i_this->m2CC.y;
            fVar7 = 1.0f;
        } else {
            i_this->m2E4.y = (i_this->m2CC.y - 150.0f) + REG0_F(0xe);
            fVar7 = 0.1f;
        }
        dVar6 = fVar7;
        cLib_addCalc2(&i_this->m2D8.x, i_this->m2E4.x, fVar7, i_this->m308 * 30.0f);
        cLib_addCalc2(&i_this->m2D8.z, i_this->m2E4.z, dVar6, i_this->m308 * 30.0f);
        cLib_addCalc2(&i_this->m2D8.y, i_this->m2E4.y, dVar6, i_this->m308 * 30.0f);
        cLib_addCalc2(&i_this->m308, 1.0f, 1.0f, 0.1f);
        if (i_this->m2C0[0] == 0) {
            i_this->m2BC = 1;
            i_this->m2C0[0] = (s16)cM_rndF(30.0f);
        }
        break;
    }
}

/* 00002168-000025D4       .text start_hand_calc__FP13bmdhand_class */
void start_hand_calc(bmdhand_class* i_this) {
    /* Nonmatching - swapped fadds instruction, math */
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_a8;
    cXyz cStack_b4;

    local_a8.y = 0.0f;
    local_a8.x = 0.0f;
    dBgS_LinChk local_9c;
    cXyz local_c0(i_this->m2D8);
    cXyz local_cc(local_c0);
    local_cc.y = local_c0.y + 2500.0f;
    local_9c.Set(&local_c0, &local_cc, actor);
    if (dComIfG_Bgsp()->LineCross(&local_9c)) {
        i_this->m2CC = local_9c.GetCross();
        i_this->m2CC.y += l_HIO.m08;
    }
    if (i_this->m2BC == 0) {
        mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
        f32 fVar1 = (i_this->m2E4.y - i_this->m2D8.y) * ((REG13_F(4) + 0.1f) * (REG13_F(5) + 2.0f));
        local_a8.x = fVar1 * cM_ssin(i_this->m2B8 * (REG13_S(5) + 0x5dc));
        local_a8.y = fVar1 * cM_scos(i_this->m2B8 * (REG13_S(7) + 500));
        if ((actor->base.mParameters & 1U) == 0) {
            local_a8.z = REG0_F(9) + 250.0f;
        } else {
            local_a8.z = REG0_F(10) + 350.0f;
        }
        MtxPosition(&local_a8, &cStack_b4);
        i_this->m2E4 = actor->current.pos + cStack_b4;
        i_this->m2E4.y = i_this->m2CC.y;
        cLib_addCalc2(&i_this->m2D8.x, i_this->m2E4.x, 1.0f, i_this->m308 * 50.0f);
        cLib_addCalc2(&i_this->m2D8.z, i_this->m2E4.z, 1.0f, i_this->m308 * 50.0f);
        cLib_addCalc2(&i_this->m2D8.y, i_this->m2E4.y, 1.0f, i_this->m308 * 10.0f);
        cLib_addCalc2(&i_this->m308, REG13_F(6) + 1.0f, 1.0f, REG13_F(7) + 0.01f);
    }
}

/* 000025D4-00002E74       .text hand_move__FP13bmdhand_class */
void hand_move(bmdhand_class* i_this) {
    /* Nonmatching - regalloc, math */
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar10;
    cXyz local_40;
    cXyz local_4c;
    cXyz local_58;

    hand_s* pcVar9 = i_this->m324;
    if (boss != NULL) {
        actor->current.angle.y = ((u16)actor->base.mParameters & 0x1f) * -0xccc + REG8_S(4) + -13000 + boss->shape_angle.y;
        MTXCopy(boss->mpMorf->mpModel->getAnmMtx(boss_joint_d[(actor->base.mParameters & 0x1fU)]), *calc_mtx);
        local_40.x = REG14_F(6);
        local_40.y = REG14_F(7);
        local_40.z = boss_joint_xad[(actor->base.mParameters & 3U)];
        MtxPosition(&local_40, &actor->current.pos);
        if ((i_this->m2BA != 2) && (boss->m332 == 3)) {
            i_this->m2BA = 2;
            i_this->m314 = 3.0f;
            i_this->m318 = 40.0f;
            fVar10 = cM_rndF(20.0f);
            i_this->m31C = fVar10 + 30.0f;
            fVar10 = cM_rndF(30.0f);
            i_this->m2C0[1] = (s16)(fVar10 + 50.0f);
        }
        switch (i_this->m2BA) {
        case 0:
            cLib_addCalc2(&i_this->m310, REG14_F(0xb) + 30.0f, 0.1f, 1.0f);
            cLib_addCalc2(&i_this->m31C, REG14_F(0x11) + 50.0f + 20.0f, 0.1f, 0.5);
            cLib_addCalc2(&i_this->m320, 1.0f, 1.0f, 0.01f);
            hand_calc(i_this);
            control1(i_this);
            control2(i_this);
            control3(i_this);
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            if ((i_this->m2BC > 0) && (i_this->m5CC.ChkTgHit() || (i_this->m6F8.ChkTgHit()))) {
                i_this->m2BA = 1;
                fopAcM_monsSeStart(actor, JA_SE_CV_BKM_CUT_VINE_1, 0);
                mDoAud_seStart(JA_SE_CM_BKM_CUT_VINE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                local_58.setall(0.5f);
                dComIfGp_particle_set(dPa_name::ID_COMMON_0013, &actor->eyePos, NULL, &local_58, 0xFF);
                dComIfGp_particle_set(dPa_name::ID_COMMON_0016, &actor->eyePos, NULL, &local_58, 0xFF);
                if (boss->m331 > 0) {
                    boss->m331--;
                    boss->m312 = 3;
                }
                i_this->m2C0[0] = l_HIO.m0C;
                i_this->m314 = 3.0f;
                i_this->m318 = 40.0f;
                fVar10 = cM_rndF(20.0f);
                i_this->m31C = fVar10 + 30.0f;
                i_this->m2C8 = 0x14;
            }
            break;
        case 1:
            i_this->m2C8 = 0x14;
            i_this->m2CA = 2;
            cLib_addCalc2(&i_this->m310, REG14_F(0xc) + 20.0f, 0.1f, 0.5f);
            cut_control(i_this);
            cut_control3(i_this);
            if (i_this->m2C0[0] < 100) {
                cLib_addCalc2(&i_this->m320, 0.0f, 1.0f, 0.01f);
            }
            if (i_this->m2C0[0] == 0) {
                i_this->m2BA = 0;
                i_this->m2BC = 0;
                i_this->m30C = 0.0f;
                i_this->m31C = 0.0f;
            }
            break;
        case 2:
            i_this->m2C8 = 0x14;
            if (i_this->m2C0[1] == 0) {
                cLib_addCalc2(&i_this->m310, REG14_F(0xc) + 20.0f, 0.1f, 0.5f);
            }
            if ((boss->m302 == 2) && (boss->m308[0] < 100)) {
                cLib_addCalc0(&i_this->m320, 1.0f, 0.01f);
            }
            cut_control(i_this);
            cut_control3(i_this);
            if (boss->m332 == 4) {
                fVar10 = cM_rndF(50.0f);
                i_this->m2C0[0] = (s16)fVar10;
                i_this->m2BA = 5;
                i_this->m2BC = 0;
            } else if (boss->m332 == 9) {
                i_this->m2BA = 4;
            }
            break;
        case 3:
            switch (i_this->m2BE) {
            case 0:
                if (boss->m332 == 5) {
                    i_this->m2BE = 1;
                    i_this->m2E4.y = 10000.0f;
                    i_this->m2D8 = actor->current.pos;
                    i_this->m30C = 1.0f;
                    fVar10 = cM_rndF(50.0f);
                    i_this->m2C0[0] = (s16)fVar10;
                }
                break;
            case 1:
                if (i_this->m2C0[0] == 0) {
                    i_this->m2BE = 2;
                }
                break;
            case 2:
                if (i_this->m2E4.y - i_this->m2D8.y < 10.0f) {
                    boss->m331 = boss->m331 + 1;
                    i_this->m2BE = 3;
                }
            // fallthrough
            case 3:
                cLib_addCalc2(&i_this->m310, REG13_F(1) + 30.0f, 0.1f, REG13_F(2) + 0.5f);
                cLib_addCalc2(&i_this->m31C, REG13_F(3) + 200.0f, 0.1f, 10.0f);
                if (i_this->m2E4.y - i_this->m2D8.y < 800.0f) {
                    cLib_addCalc2(&i_this->m320, 1.0f, 1.0f, 0.02f);
                }
                start_hand_calc(i_this);
                start_control1(i_this);
                start_control2(i_this);
                control3(i_this);
                break;
            }
            if (boss->m332 == 7) {
                i_this->m2BA = 0;
                i_this->m2BC = 0;
            }
            break;
        case 4:
            i_this->m2C8 = 0x14;
            cLib_addCalc0(&i_this->m310, 0.1f, 0.2f);
            cLib_addCalc0(&i_this->m320, 1.0f, 0.01f);
            cut_control(i_this);
            cut_control3(i_this);
            break;
        case 5:
            i_this->m2C8 = REG8_S(2) + 0x46;
            if (i_this->m2C0[0] == 0) {
                i_this->m2BA = 0;
                i_this->m2BC = 0;
                fVar10 = cM_rndF(0.2f);
                i_this->m30C = fVar10;
                i_this->m31C = 0.0f;
            }
            break;
        }
    }
    cXyz* line_data = i_this->m554.getPos(0);
    u8* line_size = i_this->m554.getSize(0);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m324); i++, pcVar9++, line_data++, line_size++) {
        *line_data = pcVar9->m00;
        *line_size = pcVar9->m18;

        if (i == 10) {
            actor->eyePos = pcVar9->m00;
            actor->attention_info.position = actor->eyePos;
            i_this->m5CC.SetC(actor->eyePos);
            dComIfG_Ccsp()->Set(&i_this->m5CC);
        } else if (i == (s32)((i_this->m2B8 & 3U) * 4 + 3)) {
            i_this->m6F8.SetC(pcVar9->m00);
            dComIfG_Ccsp()->Set(&i_this->m6F8);
        }
    }
    if (i_this->m2C8 != 0) {
        local_4c.x = 0.0f;
        local_4c.y = -20000.0f;
        local_4c.z = 0.0f;
        i_this->m5CC.SetC(local_4c);
        dComIfG_Ccsp()->Set(&i_this->m5CC);
        i_this->m6F8.SetC(local_4c);
        dComIfG_Ccsp()->Set(&i_this->m6F8);
        fopAcM_OffStatus(actor, 0);
        actor->attention_info.flags = 0;
    }
}

/* 00002E74-00002EC0       .text s_a_d_sub__FPvPv */
void* s_a_d_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BMD)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 00002EC0-00003028       .text daBmdhand_Execute__FP13bmdhand_class */
static BOOL daBmdhand_Execute(bmdhand_class* i_this) {
    if (boss == NULL) {
        boss = (bmd_class*)fpcM_Search(s_a_d_sub, i_this);
    }
    i_this->m2B8++;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m2C0); i++) {
        if (i_this->m2C0[i] != 0) {
            i_this->m2C0[i]--;
        }
    }
    if (i_this->m2C8 != 0) {
        i_this->m2C8--;
    }
    if (i_this->m2CA != 0) {
        i_this->m2CA--;
    }
    i_this->m2FC = i_this->m2F0.y;
    hand_move(i_this);
    f32 dVar4 = (i_this->m2CC.y - 1.0f);
    if ((i_this->m2F0.y < dVar4) && (i_this->m2FC >= dVar4)) {
        hand_open(i_this);
    }
    if ((i_this->m2F0.y > dVar4) && (i_this->m2FC <= dVar4)) {
        i_this->m304 = 3;
    }
    if (i_this->m304 != 0) {
        i_this->m304--;
        if (i_this->m304 == 0) {
            hand_close(i_this);
        }
    }
    i_this->m2B4->play(NULL, 0, 0);
    return TRUE;
}

/* 00003028-00003030       .text daBmdhand_IsDelete__FP13bmdhand_class */
static BOOL daBmdhand_IsDelete(bmdhand_class*) {
    return TRUE;
}

/* 00003030-000030C4       .text daBmdhand_Delete__FP13bmdhand_class */
static BOOL daBmdhand_Delete(bmdhand_class* i_this) {
    dComIfG_resDelete(&i_this->m2AC, "Bmdhand");
    if (i_this->m824 != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    boss = NULL;
    mDoAud_seDeleteObject(&i_this->m2D8);
    return TRUE;
}

/* 000030C4-00003210       .text useHeapInit__FP13bmdhand_class */
s32 useHeapInit(bmdhand_class* i_this) {
    mDoExt_McaMorf* morf;
    ResTIMG* pImg;

    morf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bmdhand", BMDHAND_BMD_BKM_FOOK),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bmdhand", BMDHAND_BCK_FOOK_HIRAKU),
        J3DFrameCtrl::EMode_NONE,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    i_this->m2B4 = morf;
    if (i_this->m2B4->getModel() == NULL) {
        return FALSE;
    }
    if (i_this->m2B4 == NULL) {
        return FALSE;
    }
    pImg = (ResTIMG*)dComIfG_getObjectRes("Bmdhand", BMDHAND_BTI_SYOKUSYU_UE);
    if (!i_this->m554.init(1, 0x14, pImg, 1)) {
        return FALSE;
    }
    return TRUE;
}

/* 00003210-00003230       .text solidHeapCB__FP10fopAc_ac_c */
static BOOL solidHeapCB(fopAc_ac_c* a_this) {
    bmdhand_class* i_this = (bmdhand_class*)a_this;
    useHeapInit(i_this);
}

/* 00003230-000034FC       .text daBmdhand_Create__FP10fopAc_ac_c */
static cPhs_State daBmdhand_Create(fopAc_ac_c* a_this) {
    /* Nonmatching - .data */
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 100.0f,
        }},
    };
    cPhs_State res;

    fopAc_ac_c* actor = a_this;
    fopAcM_SetupActor(actor, bmdhand_class);
    bmdhand_class* i_this = (bmdhand_class*)a_this;
    res = dComIfG_resLoad(&i_this->m2AC, "Bmdhand");
    if (res == cPhs_ERROR_e) {
        return cPhs_ERROR_e;
    } else if (res != cPhs_COMPLEATE_e) {
        return res;
    }
    if (!fopAcM_entrySolidHeap(actor, solidHeapCB, 0x3040)) {
        return cPhs_ERROR_e;
    }
    if (hio_set == 0) {
        hio_set = 1;
        i_this->m824 = 1;
        l_HIO.mNo = mDoHIO_createChild("森ボス触手", &l_HIO); // Forest boss tentacle
    }
    actor->health = 2;
    i_this->m2B8 = (s16)cM_rndF(10000.0f);
    boss = NULL;
    i_this->m590.Init(0xFF, 0xFF, actor);
    i_this->m5CC.Set(cc_sph_src);
    i_this->m5CC.SetStts(&i_this->m590);
    i_this->m5CC.SetR(110.0f);
    i_this->m6F8.Set(cc_sph_src);
    i_this->m6F8.SetStts(&i_this->m590);
    i_this->m5CC.SetR(90.0f);
    if (!(g_dComIfG_gameInfo.save.getMemory().getBit().isStageBossDemo()) && (dComIfGp_getStartStageName()[0] != 'X')) {
        i_this->m2BA = 3;
    }
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daBmdhand_Method = {
    (process_method_func)daBmdhand_Create,
    (process_method_func)daBmdhand_Delete,
    (process_method_func)daBmdhand_Execute,
    (process_method_func)daBmdhand_IsDelete,
    (process_method_func)daBmdhand_Draw,
};

actor_process_profile_definition g_profile_BMDHAND = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BMDHAND,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bmdhand_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BMDHAND,
    /* Actor SubMtd */ &l_daBmdhand_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
