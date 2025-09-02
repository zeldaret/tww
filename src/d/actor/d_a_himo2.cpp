/**
 * d_a_himo2.cpp
 * Item - Grappling Hook / ロープ (Rope)
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_bk.h"
#include "d/actor/d_a_ykgr.h"
#include "d/actor/d_a_himo2.h"
#include "d/actor/d_a_btd.h"
#include "d/actor/d_a_dr2.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/res/res_link.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_controller_pad.h"
#include "m_Do/m_Do_hostIO.h"

class himo2HIO_c : public JORReflexible {
public:
    himo2HIO_c() {
        m06 = 0;
        m08 = 15000;
        m0A = 1000;
        m0C = 600;
        m0E = 400;
        m10 = 60.0f;
        m14 = 1500.0f;
        m18 = 1000.0f;
        m1C = 2.3f;
        m20 = 1.9f;
    }
    virtual ~himo2HIO_c() {}
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x06 */ s16 m06;
    /* 0x08 */ s16 m08;
    /* 0x0A */ s16 m0A;
    /* 0x0C */ s16 m0C;
    /* 0x0E */ s16 m0E;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
};

himo2HIO_c l_himo2HIO;
f32 rope_scale;
static btd_class* btd;
dr2_class* dr;

/* 800EB60C-800EBABC       .text spin_draw__FP11himo2_class */
void spin_draw(himo2_class* param_1) {
    /* Nonmatching - regalloc, cXyz */
    f32 fVar1;
    s16 sVar2;
    s16 sVar3;
    s16 sVar4;
    int iVar6;
    cXyz* pcVar7;
    s16 sVar8;
    s16 sVar9;
    int iVar11;
    f32 dVar12;
    cXyz local_504;
    cXyz local_510;
    cXyz local_51c;
    cXyz local_528;

    sVar4 = 0;
    sVar2 = param_1->m2510;
    local_504.y = (param_1->m217C->scale.y - 1.0f) * 8.0f;
    local_504.z *= -7.0f;
    fVar1 = param_1->m217C->scale.y;
    if ((fopAcM_GetParam(param_1->m217C) & 0x0F) == 3) {
        local_504.y += REG8_F(8) + -3.0f;
        local_504.z += REG8_F(9) + 1.5f;
    }
    if (fVar1 < 0.7f) {
        local_504.y += 3.0f;
    }
    if (param_1->m251C != 0) {
        sVar9 = 700;
        local_504.x = REG0_F(0) * 10.0f - 15.0f;
    } else {
        sVar9 = -700;
        local_504.x = REG0_F(0) * 10.0f + 15.0f;
    }
    local_504.x = local_504.x + param_1->m24B8;
    local_504.y = local_504.y + -152.5f;
    local_504.z = param_1->m24B4 + 26.0f + local_504.z;
    mDoMtx_YrotS(*calc_mtx, sVar2);
    MtxPosition(&local_504, &local_510);
    local_51c.x = param_1->m217C->current.pos.x + local_510.x;
    local_51c.y = param_1->m217C->current.pos.y + local_510.y;
    local_51c.z = param_1->m217C->current.pos.z + local_510.z;
    local_504.x = 0.0f;
    local_504.y = 0.0f;
    local_504.z = 3.90625f;
    sVar8 = -0x30d4;
    pcVar7 = param_1->m1F30.mpLines->mpSegments + param_1->m1F6C;
    iVar11 = 0;
    iVar6 = 0;
    dVar12 = -200000.0f;
    cXyz local_4f8[100];
    for (; iVar11 < 100; iVar11++, iVar6 += 12) {
        local_4f8[iVar6].y = dVar12;
        if (iVar11 < 50) {
            sVar3 = sVar8 + REG0_S(2) + 100;
        } else if ((iVar11 >= 50) && (param_1->m24BC + 49 <= iVar11)) {
            sVar3 = sVar8 + param_1->m24C8;
            if (100 - (REG0_S(4) + 5) >= iVar11) {
                sVar3 = REG0_S(5) + sVar3 + -1000;
            }
            if ((param_1->m217C != NULL) && (fopAcM_GetParam(param_1->m217C) != 0)) {
                sVar4 = REG0_S(4) + sVar4 + -400;
            }
        } else {
            if (param_1->m24BC == 0) {
                sVar3 = sVar8 + REG0_S(2) + 70;
            } else {
                sVar3 = sVar8 + 50;
            }
        }
        mDoMtx_YrotS(*calc_mtx, sVar2);
        mDoMtx_ZrotM(*calc_mtx, sVar4);
        mDoMtx_XrotM(*calc_mtx, sVar8);
        mDoMtx_YrotM(*calc_mtx, sVar9);
        MtxPosition(&local_504, &local_510);
        local_51c.x = local_51c.x + local_510.x;
        local_51c.y = local_51c.y + local_510.y;
        local_51c.z = local_51c.z + local_510.z;
        if (iVar11 == REG0_S(6) + 48) {
            param_1->m2504 = local_51c;
        }
        if ((param_1->m24D8 < 2) || (iVar11 >= 50)) {
            if (iVar11 == 99) {
                MtxTrans(local_51c.x, local_51c.y, local_51c.z, false);
                mDoMtx_YrotM(*calc_mtx, sVar2);
                mDoMtx_ZrotM(*calc_mtx, sVar4);
                mDoMtx_XrotM(*calc_mtx, sVar8);
                mDoMtx_YrotM(*calc_mtx, sVar9);
                MtxTrans(0.0f, 0.0f, -3.0f, true);
                mDoMtx_XrotM(*calc_mtx, param_1->m24CA);
                local_528.x = 0.0f;
                local_528.y = 0.0f;
                local_528.z = 15.0f;
                MtxPosition(&local_528, &param_1->m24CC);
                MtxScale(0.2f, 0.2f, 0.2f, true);
                J3DModel* pJVar10 = param_1->m24B0;
                pJVar10->setBaseTRMtx(*calc_mtx);
                g_env_light.setLightTevColorType(pJVar10, &param_1->tevStr);
                mDoExt_modelUpdateDL(pJVar10);
            } else {
                local_4f8[iVar6] = local_51c;
            }
        }
        sVar8 = sVar3;
    }
    iVar6 = 99;
    for (iVar11 = 0; iVar11 < 100; iVar11++, iVar6++) {
        if (local_4f8[iVar6].y > -100000.0f) {
            pcVar7->x = local_4f8[iVar6].x;
            pcVar7->y = local_4f8[iVar6].y;
            pcVar7->z = local_4f8[iVar6].z;
            param_1->m1F6C++;
            pcVar7++;
        }
    }
}

/* 800EBABC-800EBCD0       .text himo2_control__FP11himo2_classP7himo2_s */
void himo2_control(himo2_class* param_1, himo2_s* param_2) {
    /* Nonmatching - for loop, regalloc */
    f32 fVar1;
    f32 fVar2;
    int i;
    int iVar4;
    int iVar5;
    himo2_s* puVar5;
    f32 dVar6;
    f32 dVar7;
    f32 dVar8;
    f32 dVar9;
    cXyz local_74;
    cXyz local_68;

    local_68.x = 0.0f;
    local_68.y = 0.0f;
    if (param_1->m02DC == 0) {
        local_68.z = param_1->m2188 * 15.625f * (REG8_F(18) + 0.002f);
    } else {
        local_68.z = param_1->m2188 * 15.625f * (REG0_F(1) + 0.0007f);
    }
    i = param_1->m02CC + 1;
    puVar5 = param_2 + i;
    dVar9 = 0.0f;
    for (; i < 100; i++) {
        dVar8 = ((puVar5->m10.y + param_1->m02E4) - puVar5[-1].m10.y);
        fVar1 = puVar5->m10.x - puVar5[-1].m10.x;
        dVar7 = fVar1;
        fVar2 = puVar5->m10.z - puVar5[-1].m10.z;
        dVar6 = fVar2;
        iVar4 = cM_atan2s(fVar1, fVar2);
        dVar6 = std::sqrtf((dVar7 * dVar7) + (dVar6 * dVar6));
        iVar5 = cM_atan2s(dVar8, dVar6);
        mDoMtx_YrotS(*calc_mtx, iVar4);
        mDoMtx_XrotM(*calc_mtx, -iVar5);
        MtxPosition(&local_68, &local_74);
        puVar5->m10.x = puVar5[-1].m10.x + local_74.x;
        puVar5->m10.y = puVar5[-1].m10.y + local_74.y;
        puVar5->m10.z = puVar5[-1].m10.z + local_74.z;
        puVar5++;
    }
}

/* 800EBCD0-800EBFEC       .text himo2_control2__FP11himo2_classP7himo2_s */
void himo2_control2(himo2_class* param_1, himo2_s* param_2) {
    /* Nonmatching - for loop, regalloc */
    cXyz local_b4;
    cXyz local_a8;

    local_a8.x = 0.0f;
    local_a8.y = 0.0f;
    himo2_s* puVar6 = param_2 + 98;
    if (param_1->m02DC == 0) {
        local_a8.z = param_1->m2188 * 15.625f * (REG8_F(18) + 0.002f);
    } else {
        local_a8.z = param_1->m2188 * 15.625f * (REG0_F(1) + 0.0007f);
    }
    f32 dVar9 = 0.0f;
    f32 dVar8 = (REG8_F(17) + 10.0f);
    int iVar4 = param_1->m02CC;
    f32 dVar10 = dVar9;
    for (; ++iVar4 < 100;) {
        f32 dVar11 = (puVar6->m10.y - puVar6[1].m10.y);
        int iVar3 = param_1->m02DC;
        if ((iVar3 >= 0) && (iVar3 < 4)) {
            if (iVar3 != 0) {
                int uStack_94 = 99 - iVar4 ^ 0x80000000;
                dVar8 = (param_1->m2530 * uStack_94) * 0.01f;
            }
            dVar10 = dVar8 * cM_ssin((param_1->m02D8 * (REG0_S(5) + 700) + iVar4 * (REG0_S(6) + 2000)) & 0xFFFF);
            dVar9 = dVar8 * cM_scos((param_1->m02D8 * (REG0_S(7) + 500) + iVar4 * (REG0_S(8) + 2000)) & 0xFFFF);
        }
        f32 fVar1 = dVar10 + (puVar6->m10.x - puVar6[1].m10.x);
        f32 dVar7 = fVar1;
        f32 fVar2 = dVar9 + (puVar6->m10.z - puVar6[1].m10.z);
        f32 dVar6 = fVar2;
        iVar3 = cM_atan2s(fVar1, fVar2);
        dVar6 = std::sqrtf((dVar7 * dVar7) + (dVar6 * dVar6));
        int iVar5 = cM_atan2s(dVar11, dVar6);
        puVar6[1].m1E = iVar3;
        puVar6[1].m1C = -iVar5;
        mDoMtx_YrotS(*calc_mtx, iVar3);
        mDoMtx_XrotM(*calc_mtx, -iVar5);
        MtxPosition(&local_a8, &local_b4);
        puVar6->m10.x = puVar6[1].m10.x + local_b4.x;
        puVar6->m10.y = puVar6[1].m10.y + local_b4.y;
        puVar6->m10.z = puVar6[1].m10.z + local_b4.z;
        puVar6++;
    }
}

/* 800EBFEC-800EC1E4       .text himo2_draw__FP11himo2_classP7himo2_s */
void himo2_draw(himo2_class* param_1, himo2_s* param_2) {
    /* Nonmatching - regalloc */
    daPy_py_c* apdVar1 = (daPy_py_c*)dComIfGp_getPlayer(0);
    cXyz* pcVar6 = param_1->m1F30.mpLines->mpSegments + param_1->m1F6C;
    pcVar6->x = param_1->m02B4.x;
    pcVar6->y = param_1->m02B4.y;
    pcVar6->z = param_1->m02B4.z;
    param_1->m1F6C++;
    int iVar2 = param_1->m02CC;
    himo2_s* phVar4 = param_2 + iVar2 + 1;
    pcVar6++;
    for (; iVar2 < 98; iVar2++, phVar4++) {
        if (iVar2 == 97) {
            if ((param_1->m02DC == 0) && (param_1->m2188 < REG0_F(3) + 50.0f)) {
                MTXCopy(apdVar1->getLeftHandMatrix(), *calc_mtx);
                MtxTrans(10.0f, 0.0f, 0.0f, true);
                mDoMtx_YrotM(*calc_mtx, 0x4000);
            } else {
                MtxTrans(phVar4->m10.x, phVar4->m10.y, phVar4->m10.z, false);
                mDoMtx_YrotM(*calc_mtx, phVar4->m1E);
                mDoMtx_XrotM(*calc_mtx, phVar4->m1C);
                MtxTrans(0.0f, 0.0f, 12.0f, true);
                MtxRotX(M_PI, 1);
                MtxRotZ(M_PI, 1);
            }
            MtxScale(0.2f, 0.2f, 0.2f, true);
            cXyz local_38;
            local_38.x = 0.0f;
            local_38.y = 0.0f;
            local_38.z = 15.0f;
            MtxPosition(&local_38, &param_1->m24CC);
            J3DModel* pJVar5 = param_1->m24B0;
            pJVar5->setBaseTRMtx(*calc_mtx);
            g_env_light.setLightTevColorType(pJVar5, &param_1->tevStr);
            mDoExt_modelUpdateDL(pJVar5);
        } else {
            pcVar6->x = phVar4->m10.x;
            pcVar6->y = phVar4->m10.y;
            pcVar6->z = phVar4->m10.z;
            param_1->m1F6C++;
            pcVar6++;
        }
    }
}

/* 800EC1E4-800EC300       .text himo_hang_draw__FP11himo2_class */
void himo_hang_draw(himo2_class* param_1) {
    /* Nonmatching - for loop */
    cXyz* pcVar3 = param_1->m1F30.mpLines->mpSegments + param_1->m1F6C;
    cXyz local_38 = param_1->m02EC[0] - param_1->m2504;
    for (int uVar2 = 0; uVar2 < 5; uVar2++, pcVar3++, param_1->m1F6C++) {
        pcVar3->x = param_1->m2504.x + local_38.x * 0.25f * uVar2;
        pcVar3->y = param_1->m2504.y + local_38.y * 0.25f * uVar2;
        pcVar3->z = param_1->m2504.z + local_38.z * 0.25f * uVar2;
    }
}

/* 800EC300-800EC338       .text himo2_disp__FP11himo2_class */
void himo2_disp(himo2_class* param_1) {
    if (param_1->m02DC < 10) {
        himo2_draw(param_1, &param_1->m0310[0]);
    } else {
        himo_hang_draw(param_1);
    }
}

/* 800EC338-800ECBE8       .text daHimo2_Draw__FP11himo2_class */
static BOOL daHimo2_Draw(himo2_class* param_1) {
    /* Nonmatching - cXyz */
    f32 fVar1;
    int iVar3;
    int iVar5;
    cXyz* pcVar7;
    int iVar8;
    f32 dVar10;
    f32 dVar11;
    f32 dVar12;
    f32 dVar13;
    f32 dVar14;
    cXyz local_a4c;
    cXyz local_a40;
    cXyz local_a34;
    cXyz local_a28;
    cXyz local_a1c;
    f32 local_b0;
    f32 local_a8;

    if (((param_1->m24D9 >= 0) && (param_1->m029E == 0)) &&
        (param_1->m02DC != 0 || (!(daPy_getPlayerActorClass()->checkPlayerNoDraw()) && !(daPy_getPlayerActorClass()->checkPlayerGuard()))))
    {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &param_1->current.pos, &param_1->tevStr);
        param_1->m1F6C = 0;
        dComIfGd_setListP1();
        if (param_1->m24D8 != 0) {
            spin_draw(param_1);
        }
        if ((param_1->m24D9 == 0) || (param_1->m24D9 >= 3)) {
            himo2_disp(param_1);
        }
        if (param_1->m1F6C > 200) {
            dComIfGd_setList();
            return TRUE;
        } else {
            pcVar7 = param_1->m1F30.mpLines->mpSegments;
            cXyz local_a10[200];
            iVar3 = 0;
            for (iVar5 = 0; iVar5 < param_1->m1F6C; iVar5++) {
                local_a10[iVar3].x = pcVar7->x;
                local_a10[iVar3].y = pcVar7->y;
                local_a10[iVar3].z = pcVar7->z;
                pcVar7++;
                iVar3 = iVar3 + 12;
            }
            iVar3 = 0;
            for (iVar5 = 0; iVar5 < param_1->m1F6C; iVar5++) {
                pcVar7[-1].x = local_a10[iVar3].x;
                pcVar7[0].y = local_a10[iVar3].y;
                pcVar7[0].z = local_a10[iVar3].z;
                iVar3 = iVar3 + 12;
                pcVar7 = pcVar7 + -1;
            }
            GXColor local_a50 = {200, 0x96, 50, 0xFF};
            param_1->m1F30.update((u16)param_1->m1F6C, rope_scale, local_a50, 0, &param_1->tevStr);
            dComIfGd_set3DlineMat(&param_1->m1F30);
            daPy_py_c* apdVar2 = (daPy_py_c*)dComIfGp_getPlayer(0);
            mDoMtx_YrotS(*calc_mtx, -apdVar2->shape_angle.y);
            local_a40 = param_1->m02EC[1] - param_1->m1F84;
            MtxPosition(&local_a40, &local_a28);
            local_a28.z = local_a28.z * (REG0_F(5) + 500.0f);
            if (local_a28.z > 16384.0f) {
                local_a28.z = 16384.0f;
            }
            if (local_a28.z < -16384.0f) {
                local_a28.z = -16384.0f;
            }
            local_b0 = local_a28.z;
            cLib_addCalcAngleS2(&param_1->m1F90, local_a28.z, 2, REG0_S(2) + 0x800);
            local_a28.x *= REG0_F(6) + -200.0f;
            fVar1 = REG0_F(7) + 4000.0f;
            if (local_a28.x > fVar1) {
                local_a28.x = fVar1;
            }
            if (local_a28.x < -fVar1) {
                local_a28.x = -fVar1;
            }
            local_a8 = local_a28.x;
            cLib_addCalcAngleS2(&param_1->m1F94, local_a28.x, 2, REG0_S(2) + 0x800);
            if (local_a28.y < REG0_F(8) + -20.0f) {
                cLib_addCalcAngleS2(&param_1->m1F92, -0x8000, 2, 0x1000);
            } else {
                cLib_addCalcAngleS2(&param_1->m1F92, 0, 2, 0x1000);
            }
            param_1->m1F84 = param_1->m02EC[1];
            local_a1c.z = 0.0f;
            local_a1c.x = 0.0f;
            dVar13 = ((REG0_F(10) + param_1->m2188 * (REG0_F(9) + 3.0f)) - 120.0f);
            iVar5 = 0;
            iVar3 = 0;
            dVar14 = 300.0f;
            dVar10 = 15.0f;
            dVar11 = 1.0f;
            dVar12 = -20000.0f;
            for (int iVar9 = 0; iVar9 < 5; iVar9++) {
                pcVar7 = param_1->m1F98.mpLines->mPosArr[iVar3 + -8];

                if (dVar13 > (dVar14 * (4 - iVar9))) {
                    cLib_addCalc0(&param_1->m1F70, dVar11, (REG0_F(11) + 0.2f));
                } else {
                    cLib_addCalc2(&param_1->m1F70, 1.0f, 1.0f, REG0_F(12) + 0.1f);
                }

                local_a1c.y = (dVar10 * param_1->m1F70);
                mDoMtx_YrotS(*calc_mtx, apdVar2->shape_angle.y);
                iVar8 = ((dVar11 - param_1->m1F70) * (dVar12 + REG0_F(13)));
                local_a8 = iVar8;
                mDoMtx_ZrotM(*calc_mtx, param_1->m1F92 + iVar9 * (REG0_S(0) + param_1->m1F94 + -2000) + iVar8);
                mDoMtx_XrotM(*calc_mtx, param_1->m1F90);
                MtxTrans(0.0f, -local_a1c.y, 0.0f, true);
                for (int j = 0; j < 32; j++, pcVar7++) {
                    mDoMtx_XrotM(*calc_mtx, 0x800);
                    MtxPosition(&local_a1c, pcVar7);
                    param_1->m02EC[1] += *pcVar7;
                }
                iVar5 += 4;
                iVar3 += 24;
            }
            GXColor local_a54 = {200, 0x96, 50, 0xFF};
            param_1->m1F98.update(0x20, rope_scale, local_a54, 0, &param_1->tevStr);
            dComIfGd_set3DlineMat(&param_1->m1F98);
            pcVar7 = ((param_1->m1FD8).mpLines)->mpSegments;
            local_a8 = param_1->m2188;
            if (((int)param_1->m2188 & REG0_S(4) + 64) != 0) {
                fVar1 = REG0_F(14) + 15.0f;
            } else {
                fVar1 = 0.0f;
            }
            cLib_addCalc2(&param_1->m1FD4, fVar1, 1.0f, REG0_F(15) + 4.0f);
            local_a4c = param_1->m02EC[0] - param_1->m02EC[1];
            mDoMtx_YrotS(*calc_mtx, (cM_atan2s(local_a4c.x, local_a4c.z) + REG0_S(0) + -0x4000));
            local_a1c.x = 0.0f;
            local_a1c.y = (REG0_F(7) + -10.0f - param_1->m1FD4) * param_1->m1F70;
            local_a1c.z = (REG0_F(8) + 10.0f + param_1->m1FD4) * param_1->m1F70;
            MtxPosition(&local_a1c, &local_a28);
            local_a34.x = local_a34.x * 0.06666667f;
            local_a34.y = local_a34.y * 0.06666667f;
            local_a34.z = local_a34.z * 0.06666667f;
            int uVar6 = 0;
            int uVar4 = 0;
            for (int i = 0; i < 16; i++) {
                f32 fVar1 = cM_ssin(uVar4 & 0xFFFF);
                pcVar7->x = param_1->m02EC[0].x + local_a34.x * uVar6 + local_a28.x * fVar1;
                pcVar7->y = param_1->m02EC[0].y + local_a34.y * uVar6 + local_a28.y * fVar1;
                pcVar7->z = param_1->m02EC[0].z + local_a34.z * uVar6 + local_a28.z * fVar1;
                pcVar7++;
                uVar6 += 1;
                uVar4 += 0x888;
            }
            GXColor local_a58 = {200, 0x96, 50, 0xFF};
            param_1->m1FD8.update(16, rope_scale, local_a58, 0, &param_1->tevStr);
            dComIfGd_set3DlineMat(&param_1->m1FD8);
            dComIfGd_setList();
        }
    }
    return TRUE;
}

/* 800ECBE8-800ECC54       .text s_a_d_sub__FPvPv */
void* s_a_d_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KUI)) {
        himo2_class* rope = (himo2_class*)param_2;
        (&rope->m218C)[rope->m24AC] = (fopAc_ac_c*)param_1;
        rope->m24AC++;
    }
    return NULL;
}

/* 800ECC54-800ED19C       .text search_target__FP11himo2_class4cXyz */
fopAc_ac_c* search_target(himo2_class* param_1, cXyz param_2) {
    /* Nonmatching - cXyz, regalloc */
    bool bVar1;
    f32 fVar2;
    f32 fVar3;
    f32 fVar4;
    f32 fVar5;
    f32 fVar6;
    f32 fVar7;
    f32 fVar8;
    f32 fVar9;
    daPy_py_c* apdVar11;
    s16 sVar12;
    s16 sVar13;
    s16 sVar14;
    s16 sVar15;
    int iVar16;
    uint uVar17;
    fopAc_ac_c* pfVar18;
    int iVar19;
    f32 dVar21;
    f32 dVar22;
    cXyz local_60;
    cXyz local_54;

    apdVar11 = daPy_getPlayerActorClass();
    param_1->m24AC = 0;
    for (int iVar16 = 0, iVar19 = 100; iVar19 != 0; iVar16 += 4, iVar19--) {
        (&param_1->m218C)[iVar16] = NULL;
    }
    fpcEx_Search(s_a_d_sub, param_1);
    mDoMtx_YrotS(*calc_mtx, -apdVar11->shape_angle.y);
    dVar22 = 100.0f;
    sVar12 = 0x4000 - l_himo2HIO.m08;
    sVar13 = l_himo2HIO.m08 + 0x4000;
    if (param_1->m24AC != 0) {
        uVar17 = 0;
        do {
            do {
                if ((uint)(s8)param_1->m24AC <= uVar17) {
                    return NULL;
                }
                pfVar18 = (&param_1->m218C)[uVar17];
                bVar1 = fopAcM_GetParam(pfVar18) != 0;
                local_54.x = apdVar11->current.pos.x - pfVar18->current.pos.x;
                local_54.z = apdVar11->current.pos.z - pfVar18->current.pos.z;
                iVar16 = cM_atan2s(local_54.x, local_54.z);
                sVar14 = pfVar18->current.angle.y - iVar16;
                if ((sVar14 >= -1) || (!bVar1)) {
                    sVar14 = -sVar14;
                    param_1->m251C = 1;
                } else {
                    param_1->m251C = 0;
                }
                if ((bVar1) || (sVar12 > sVar14 && (sVar14 < sVar13))) {
                    local_54.x = pfVar18->current.pos.x - apdVar11->current.pos.x;
                    local_54.y = pfVar18->current.pos.y - apdVar11->current.pos.y;
                    local_54.z = pfVar18->current.pos.z - apdVar11->current.pos.z;
                    MtxPosition(&local_54, &local_60);
                    if ((local_60.z > 100.0f) && (bVar1 || (std::fabsf(local_60.y) < l_himo2HIO.m14))) {
                        dVar21 = std::sqrtf(local_60.x * local_60.x + local_60.z * local_60.z);
                        if (dVar21 < dVar22) {
                            fVar2 = dComIfGp_getCamera(0)->mLookat.mEye.x;
                            fVar4 = dComIfGp_getCamera(0)->mLookat.mEye.y;
                            fVar5 = dComIfGp_getCamera(0)->mLookat.mEye.z;
                            fVar6 = param_2.x - fVar2;
                            fVar3 = param_2.y;
                            fVar8 = param_2.z - fVar5;
                            fVar2 = pfVar18->current.pos.x - fVar2;
                            fVar7 = pfVar18->current.pos.y - fVar4;
                            fVar5 = pfVar18->current.pos.z - fVar5;
                            iVar16 = cM_atan2s(fVar6, fVar8);
                            iVar19 = cM_atan2s(fVar2, fVar5);
                            sVar14 = iVar19 - iVar16;
                            if (sVar14 < 0) {
                                sVar14 = -sVar14;
                            }
                            fVar9 = std::sqrtf(fVar5 * fVar5 + fVar2 * fVar2 + fVar7 * fVar7);
                            sVar15 = cM_atan2s((pfVar18->scale).z * l_himo2HIO.m10, fVar9);
                            if (sVar15 < 0) {
                                sVar15 = -sVar15;
                            }
                            if ((-sVar15 > sVar14) && (sVar14 < sVar15)) {
                                fVar6 = std::sqrtf(fVar6 * fVar6 + fVar8 * fVar8);
                                iVar16 = cM_atan2s(fVar3 - fVar4, fVar6);
                                fVar2 = std::sqrtf(fVar2 * fVar2 + fVar5 * fVar5);
                                iVar19 = cM_atan2s(fVar7, fVar2);
                                sVar14 = l_himo2HIO.m0C;
                                if (bVar1) {
                                    sVar14 = 2000;
                                }
                                if ((-iVar16 < -iVar19 + l_himo2HIO.m0E) && ((-iVar19 + iVar16) < sVar14)) {
                                    return pfVar18;
                                }
                            }
                        }
                    }
                }
                uVar17++;
            } while (uVar17 != (s8)param_1->m24AC);
            uVar17 = 0;
            dVar22 = (dVar22 + 100.0f);
            if (bVar1) {
                fVar2 = 2000.0f;
            } else {
                fVar2 = l_himo2HIO.m18;
            }
        } while (!(dVar22 > fVar2));
    }
    return NULL;
}

/* 800ED19C-800ED2E0       .text setTargetPos__11himo2_classFP4cXyzPfPf */
BOOL himo2_class::setTargetPos(cXyz* param_1, float* param_2, float* param_3) {
    /* Nonmatching - pfVar1 */
    *param_2 = -1.0f;
    *param_3 = -1.0f;
    m2524 = *param_1;
    fopAc_ac_c* pfVar1 = search_target(this, m2524);
    m217C = pfVar1;
    if (pfVar1 != NULL) {
        if (fopAcM_GetParam(m217C) != 0) {
            *param_2 = 700.0f;
            *param_3 = 100.0f;
        } else {
            *param_2 = (fopAcM_GetParam(m217C) >> 0x10 & 0x0F) * 100.0f;
            *param_3 = (fopAcM_GetParam(m217C) >> 0x14 & 0x0F) * 100.0f;
            if (*param_2 >= 1500.0f) {
                *param_2 = -1.0f;
            }
            if (*param_3 >= 1500.0f) {
                *param_3 = -1.0f;
            }
        }
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 800ED2E0-800ED32C       .text dr_a_sub__FPvPv */
void* dr_a_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_DR2)) {
        return param_1;
    } else {
        return param_2 = NULL;
    }
}

/* 800ED32C-800ED378       .text b_a_sub__FPvPv */
void* b_a_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BTD)) {
        return param_1;
    } else {
        return param_2 = NULL;
    }
}

/* 800ED378-800ED688       .text himo2_bg_check__FP11himo2_class */
int himo2_bg_check(himo2_class* param_1) {
    u8 flag;
    u32 uVar3;
    int iVar4;
    JPABaseEmitter* pJVar5;
    csXyz local_38;

    if (param_1->m02A2 != 0) {
        return FALSE;
    } else {
        param_1->m2574.CrrPos(g_dComIfG_gameInfo.play.mBgS);
        if ((param_1->m2574.ChkWallHit() || param_1->m2574.ChkRoofHit()) || param_1->m2574.ChkGroundHit()) {
            param_1->m02DC = 9;
            param_1->speedF *= -1.0f;
            param_1->m0308 = 30;
            cBgS_PolyInfo local_24;
            flag = param_1->m2574.GetOnePolyInfo(&local_24);
            JUT_ASSERT(1569, flag == NULL);
            uVar3 = dComIfG_Bgsp()->GetMtrlSndId(local_24);
            mDoAud_seStart(JA_SE_LK_SW_HIT_S, &param_1->current.pos, uVar3, dComIfGp_getReverb(fopAcM_GetRoomNo(param_1)));
            iVar4 = dComIfG_Bgsp()->GetAttributeCode(local_24);
            if ((iVar4 == dBgS_Attr_WOOD_e) || (iVar4 == dBgS_Attr_STONE_e)) {
                local_38.x = param_1->current.angle.x;
                local_38.y = param_1->current.angle.y;
                local_38.z = param_1->current.angle.z;
                local_38.y = param_1->current.angle.y + 0x8000;
                mDoAud_seStart(JA_SE_LK_MS_WEP_HIT, &param_1->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(param_1)));
                if (iVar4 == dBgS_Attr_WOOD_e) {
                    pJVar5 = dComIfGp_particle_set(
                        dPa_name::ID_COMMON_002B,
                        &param_1->current.pos,
                        &local_38,
                        NULL,
                        0xFF,
                        NULL,
                        -1,
                        &param_1->tevStr.mColorK0,
                        &param_1->tevStr.mColorK0,
                        NULL
                    );
                    if (pJVar5 != NULL) {
                        pJVar5->mSpread = 0.2f;
                        pJVar5->mVolumeSweep = 0.15f;
                    }
                } else {
                    local_38.x = local_38.x + 0x4000;
                    pJVar5 = dComIfGp_particle_set(dPa_name::ID_COMMON_002C, &param_1->current.pos, &local_38);
                    if (pJVar5 != NULL) {
                        pJVar5->mInitialVelAxis = 15.0f;
                    }
                    dKy_Sound_set(param_1->current.pos, 100, fopAcM_GetID(param_1), 5);
                }
                if (pJVar5 != NULL) {
                    pJVar5->mRate = 8.0f;
                    pJVar5->mMaxFrame = 1;
                }
            }
            return true;
        } else {
            return false;
        }
    }
}

/* 800ED688-800ED6F4       .text pl_pos_add__FP11himo2_class */
void pl_pos_add(himo2_class* param_1) {
    cXyz local_28 = daPy_getPlayerActorClass()->old.pos - daPy_getPlayerActorClass()->current.pos;
    param_1->current.pos += local_28;
}

/* 800ED6F4-800F0038       .text new_himo2_move__FP11himo2_class */
void new_himo2_move(himo2_class* param_1) {
    /* Nonmatching - cXyz, regalloc */
    f32 fVar1;
    bool bVar2;
    bool bVar3;
    bool bVar4;
    dAttention_c* this_00;
    uint uVar6;
    daPy_py_c* this_01;
    int iVar8;
    s16 sVar15;
    int iVar9;
    s16 psVar11;
    daYkgr_c* pdVar13;
    int __x;
    f32 dVar19;
    f32 dVar20;
    f32 dVar21;
    f32 dVar22;
    f32 dVar23;
    f32 dVar24;
    f32 dVar25;
    f32 fVar26;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    dComIfGp_getPlayerCameraID(0);
    camera_class* camera = (camera_class*)dComIfGp_getCamera(0);
    cXyz local_140 = param_1->m02EC[0];
    cXyz local_110 = param_1->m02EC[1];
    fVar26 = param_1->current.pos.x - local_140.x;
    dVar19 = (param_1->current.pos.y - local_140.y);
    fVar1 = param_1->current.pos.z - local_140.z;
    fVar26 = std::sqrtf(fVar1 * fVar1 + fVar26 * fVar26 + (dVar19 * dVar19));
    param_1->m2188 = fVar26;
    if (param_1->m0308 != 0) {
        param_1->m0308--;
    }
    if (param_1->m02A2 != 0) {
        param_1->m02A2--;
    }
    if (param_1->m029C != 0) {
        param_1->m029C--;
    }
    if (param_1->m029E != 0) {
        param_1->m029E--;
    }
    if (param_1->m02A0 != 0) {
        param_1->m02A0--;
    }
    this_00 = &dComIfGp_getAttention();
    if (this_00->Lockon()) {
        rope_scale = l_himo2HIO.m20;
    } else {
        rope_scale = l_himo2HIO.m1C;
        param_1->m029E = 0;
    }
    bVar3 = false;
    bVar4 = false;
    bVar2 = false;
    fopAc_ac_c* pfVar17 = NULL;
    if (((this_00->LockonTruth() & 0xFF) != 0) && (pfVar17 = this_00->LockonTarget(0), pfVar17 != NULL)) {
        param_1->m2524 = pfVar17->eyePos;
        bVar3 = true;
    }
    if ((param_1->m02DC != 0) && (param_1->m24D9 < 3)) {
        this_01 = (daPy_py_c*)daPy_getPlayerLinkActorClass();
        if ((this_01->checkRopeForceEnd()) && (!param_1->eventInfo.checkCommandDemoAccrpt())) {
            param_1->m24D9 = 0;
            param_1->m24D8 = 0;
            fopAcM_SetParam(param_1, 0);
            param_1->m0308 = 0x1E;
            if (param_1->m02DC == 11) {
                fopAcM_seStart(param_1, JA_SE_LK_ROPE_UNCOIL, 0);
                param_1->m02DC = 0;
            } else {
                param_1->m02DC = 9;
            }
            if ((param_1->m217C != NULL) && (fopAcM_GetName(param_1) == PROC_KUI)) {
                param_1->m217C->health = 0;
            }
            param_1->m217C = NULL;
        }
    }
    cXyz local_11c;
    switch (param_1->m02DC) {
    case 0: {
        param_1->speedF = 0.0f;
        if ((uVar6 == 0) && player->checkRopeReadyAnime()) {
            mDoMtx_YrotS(*calc_mtx, player->shape_angle.y);
            mDoMtx_ZrotM(*calc_mtx, REG0_S(2) + -12000);
            mDoMtx_YrotM(*calc_mtx, param_1->m02D8 * (REG0_S(3) + 0x2000));
            local_110.x = 0.0f;
            local_110.y = 0.0f;
            local_110.z = REG0_F(11) + 70.0f;
            MtxPosition(&local_110, &param_1->current.pos);
            param_1->current.pos += local_140;
            param_1->m02CC = REG0_S(5) + 0x60;
            if ((param_1->m02D8 & 7) == 0) {
                fopAcM_seStart(param_1, JA_SE_LK_ROPE_COIL_1, 0);
            }
        } else {
            iVar8 = (param_1->m2188 * (REG0_F(3) + 0.060000002f));
            param_1->m02CC = 97 - iVar8;
            cLib_addCalc2(&param_1->current.pos.x, local_140.x, 1.0f, param_1->m2500 * 200.0f);
            cLib_addCalc2(&param_1->current.pos.y, local_140.y, 1.0f, param_1->m2500 * 200.0f);
            cLib_addCalc2(&param_1->current.pos.z, local_140.z, 1.0f, param_1->m2500 * 200.0f);
            cLib_addCalc2(&param_1->m2500, 1.0f, 1.0f, 0.005f);
            local_110 = param_1->current.pos - local_140;
            iVar8 = -1;
            iVar8 = local_110.abs();
            if (dVar21 > 5.0f) {
                fopAcM_seStart(param_1, JA_SE_LK_ROPE_UNWIND, 0);
            }
        }
        if (fopAcM_GetParam(param_1) == 1) {
            param_1->m2500 = 0.0f;
            param_1->m02E4 = 0.0f;
            param_1->m0308 = REG0_S(2) + 0x28;
            param_1->m029E = 0;
            param_1->m02A0 = REG0_S(9) + 10;
            param_1->m02A2 = 3;
            camera = (camera_class*)dComIfGp_getCamera(0);
            dVar20 = param_1->m2524.x - camera->mLookat.mEye.x;
            dVar22 = param_1->m2524.y - camera->mLookat.mEye.y;
            dVar21 = param_1->m2524.z - camera->mLookat.mEye.z;
            local_110.z = REG0_F(15) * 100.0f + 1000.0f;
            dVar23 = (dVar21 * dVar21);
            dVar24 = (dVar20 * dVar20);
            fVar26 = std::sqrtf(dVar23 + (dVar24 + (dVar22 * dVar22)));
            if (local_110.z > fVar26) {
                psVar11 = cM_atan2s(dVar20, dVar21);
                fVar26 = std::sqrtf(dVar24 + dVar23);
                iVar9 = cM_atan2s(dVar22, fVar26);
                mDoMtx_YrotS(*calc_mtx, psVar11);
                mDoMtx_XrotM(*calc_mtx, -iVar9);
                local_110.x = 0.0f;
                local_110.y = 0.0f;
                MtxPosition(&local_110, &local_11c);
                param_1->m2524.x = camera->mLookat.mEye.x + local_11c.x;
                param_1->m2524.y = camera->mLookat.mEye.y + local_11c.y;
                param_1->m2524.z = camera->mLookat.mEye.z + local_11c.z;
            }
            himo2_s* phVar18 = &param_1->m0310[100];
            if (uVar6 != 0) {
                param_1->m02DC = 2;
                param_1->m2530 = 4.0f;
                param_1->m02CC = REG0_S(6) + 0x5A;
                param_1->current.pos = local_140;
                for (int iVar8 = 0; iVar8 < 100; iVar8++) {
                    phVar18->m10 = local_140;
                    phVar18++;
                }
            } else {
                param_1->m02DC = 1;
                param_1->m0308 = REG0_S(4) + 2;
                param_1->m2530 = 4.0f;
                param_1->m02CC = REG0_S(6) + 0x5A;
                param_1->current.pos = local_140;
                for (int iVar8 = 0; iVar8 < 100; iVar8++) {
                    phVar18->m10 = local_140;
                    phVar18++;
                }
            }
        }
        break;
    }
    case 1: {
        mDoMtx_YrotS(*calc_mtx, param_1->shape_angle.y);
        mDoMtx_ZrotM(*calc_mtx, REG0_S(2) + -12000);
        mDoMtx_YrotM(*calc_mtx, param_1->m02D8 * (REG0_S(3) + 0x2000));
        local_110.x = 0.0f;
        local_110.y = 0.0f;
        local_110.z = REG0_F(11) + 70.0f;
        MtxPosition(&local_110, &param_1->current.pos);
        param_1->current.pos += local_140;
        param_1->m02CC = REG0_S(5) + 0x60;
        if ((param_1->m02D8 & 7) == 0) {
            fopAcM_seStart(param_1, JA_SE_LK_ROPE_SWING_ROUND, 0);
        }
        sVar15 = param_1->m02D8 * (REG0_S(3) + 0x2000);
        if (((REG0_S(7) + -20000) >= sVar15) && (sVar15 < (REG0_S(7) + -0x2e20))) {
            bVar2 = true;
        }
        if ((param_1->m0308 == 0) && (bVar2)) {
            param_1->m02DC = 3;
            if (bVar3) {
                param_1->m0308 = REG0_S(4) + 70;
                param_1->m217C = pfVar17;
                fpc_ProcID fVar10 = fopAcM_GetID(pfVar17);
                param_1->m2180 = fVar10;
            } else {
                param_1->m0308 = REG0_S(2) + 20;
                param_1->m2180 = fpcM_ERROR_PROCESS_ID_e;
            }
            local_110 = param_1->m2524 - param_1->current.pos;
            psVar11 = cM_atan2s(local_110.x, local_110.z);
            param_1->current.angle.y = psVar11;
            fVar26 = std::sqrtf(local_110.x * local_110.x + local_110.z * local_110.z);
            iVar8 = cM_atan2s(local_110.y, fVar26);
            param_1->current.angle.x = -iVar8;
            fopAcM_seStart(param_1, JA_SE_LK_ROPE_LAUNCH, 0);
        }
        break;
    }
    case 2: {
        param_1->m02CC = REG0_S(0);
        cXyz local_134;
        if (param_1->m217C != NULL) {
            if (((fopAcM_GetParam(param_1) & 0xF0) == 0) && ((fopAcM_GetParam(param_1->m217C) & 0x0F) == 3)) {
                local_134 = param_1->m217C->current.pos;
            } else {
                local_134 = param_1->m2524;
            }
            mDoMtx_YrotS(*calc_mtx, param_1->current.angle.y);
            mDoMtx_XrotM(*calc_mtx, param_1->current.angle.x);
            local_110.y = 0.0f;
            local_110.x = 0.0f;
            local_110.z = REG0_F(14) * 100.0f + 100.0f;
            MtxPosition(&local_110, &local_11c);
            local_134.x = local_134.x + local_11c.x;
            local_134.y = local_134.y + local_11c.y;
            local_134.z = local_134.z + local_11c.z;
        } else {
            local_134 = param_1->m2524;
        }
        dVar25 = (local_134.x - param_1->current.pos.x);
        dVar23 = (local_134.y - param_1->current.pos.y);
        dVar20 = (local_134.z - param_1->current.pos.z);
        dVar24 = (dVar20 * dVar20);
        dVar22 = (dVar25 * dVar25);
        fVar26 = std::sqrtf(dVar24 + (dVar22 + (dVar23 * dVar23)));
        dVar21 = fVar26;
        fVar26 = std::sqrtf(dVar22 + dVar24);
        dVar22 = fVar26;
        iVar8 = (dVar21 * (REG0_F(3) + -5.0f));
        sVar15 = iVar8;
        if (sVar15 < (REG0_S(2) + -3000)) {
            sVar15 = REG0_S(2) + -3000;
        }
        if ((param_1->m217C != NULL) || ((param_1->speedF * 10.0f) > dVar21)) {
            param_1->current.angle.y = cM_atan2s(dVar25, dVar20);
            param_1->current.angle.x = -cM_atan2s(dVar23, dVar22);
        }
        param_1->speedF = 20.0f;
        mDoMtx_YrotS(*calc_mtx, param_1->current.angle.y);
        mDoMtx_XrotM(*calc_mtx, param_1->current.angle.x + sVar15);
        local_110.y = 0.0f;
        local_110.x = 0.0f;
        local_110.z = param_1->speedF;
        MtxPosition(&local_110, &param_1->speed);
        param_1->current.pos += param_1->speed;
        pl_pos_add(param_1);
        if (param_1->m217C != NULL) {
            if ((dVar21 < (param_1->speedF * 10.0f)) || (param_1->m0308 == 0)) {
                param_1->m02DC = 10;
                param_1->m24D9 = 0xFF;
                param_1->m24D8 = 1;
                if (btd != 0) {
                    fopAcM_OffStatus(btd, fopAcStts_UNK4000_e);
                }
            } else if ((param_1->m02A2 == 0) && param_1->m2050.ChkAtHit()) {
                param_1->m02DC = 9;
                param_1->speedF *= -1.0f;
                param_1->m0308 = 0x28;
                param_1->m217C = NULL;
            } else if (!himo2_bg_check(param_1)) {
                if ((param_1->m02A2 == 0) && param_1->m2050.ChkAtHit()) {
                    param_1->m02DC = 9;
                    param_1->speedF *= -1.0f;
                    param_1->m0308 = 0x28;
                } else if (param_1->m0308 == 0) {
                    param_1->m02DC = 8;
                    param_1->m0308 = 50;
                    fopAcM_seStart(param_1, JA_SE_LK_ROPE_MAXLENGTH, 0);
                }
            }
        } else if ((CPad_CHECK_TRIG_X(0) || CPad_CHECK_TRIG_Y(0) || CPad_CHECK_TRIG_Z(0)) && (param_1->m02A0 == 0)) {
            param_1->m02DC = 8;
            param_1->m0308 = 0x28;
            fopAcM_seStart(param_1, JA_SE_LK_ROPE_MAXLENGTH, 0);
            param_1->m217C = NULL;
        }
        break;
    }
    case 3: {
        param_1->m02CC = REG0_S(0);
        pfVar17 = fopAcM_SearchByID(param_1->m2180);
        if (pfVar17 != NULL) {
            local_110 = pfVar17->eyePos - param_1->current.pos;
            cLib_addCalcAngleS2(&param_1->current.angle.y, cM_atan2s(local_110.x, local_110.z), 2, REG0_S(1) + 0x800);
            fVar26 = std::sqrtf(local_110.x * local_110.x + local_110.z * local_110.z);
            cLib_addCalcAngleS2(&param_1->current.angle.x, -cM_atan2s(local_110.y, fVar26), 2, REG0_S(1) + 0x800);
            __x = local_110.abs();
            if (dVar21 < (REG0_F(3) + 50.0f)) {
                bVar4 = true;
            }
        }
        param_1->speedF = REG0_F(14) + 30.0f;
        mDoMtx_YrotS(*calc_mtx, param_1->current.angle.y);
        mDoMtx_XrotM(*calc_mtx, param_1->current.angle.x);
        local_110.y = 0.0f;
        local_110.x = 0.0f;
        local_110.z = param_1->speedF;
        MtxPosition(&local_110, &param_1->speed);
        param_1->current.pos += param_1->speed;
        pl_pos_add(param_1);
        iVar8 = himo2_bg_check(param_1);
        if (iVar8 != 0) {
            bVar4 = true;
            param_1->m2500 = 0.1f;
        }
        if ((param_1->m02A2 == 0) && param_1->m2050.ChkAtHit()) {
            bVar4 = true;
            param_1->m2500 = 0.1f;
        }
        if (param_1->m0308 == 0) {
            bVar4 = true;
            param_1->m2500 = 0.02f;
        }
        if (((CPad_CHECK_TRIG_X(0) || CPad_CHECK_TRIG_Y(0) || CPad_CHECK_TRIG_Z(0)) && (param_1->m02A0 == 0)) || (bVar4)) {
            param_1->m02DC = 5;
        }
        break;
    }
    case 4: {
        pfVar17 = fopAcM_SearchByID(param_1->m2180);
        if (pfVar17 == NULL) {
            param_1->m02DC = 5;
        } else {
            mDoMtx_YrotS(*calc_mtx, (param_1->m02D8 << 13));
            local_110.x = 0.0f;
            local_110.y = 0.0f;
            local_110.z = param_1->m2184;
            MtxPosition(&local_110, &local_11c);
            param_1->current.pos = pfVar17->eyePos + local_11c;
            cLib_addCalc0(&param_1->m2184, 1.0f, 5.0f);
            if (param_1->m2184 < 0.1f) {
                fopAcM_SetParam(param_1, 0);
            }
            iVar8 = (param_1->m2188 * (REG0_F(5) + 0.060000002f));
            iVar8 = 97 - iVar8;
            if ((iVar8 < param_1->m02CC) || (param_1->m2184 < 0.1f)) {
                param_1->m02CC = iVar8;
            }
            if ((CPad_CHECK_TRIG_X(0) || CPad_CHECK_TRIG_Y(0)) || CPad_CHECK_TRIG_Z(0)) {
                param_1->m02DC = 5;
                sVar15 = fopAcM_GetName(pfVar17);
                if (sVar15 == PROC_BK) {
                    bk_class* boko;
                    boko->dr.mAction = 0;
                    boko->dr.mMode = 0;
                }
            }
        }
        param_1->m02E4 = -5.0f;
        break;
    }
    case 5: {
        param_1->m02CC = REG0_S(0);
        cLib_addCalc2(&param_1->current.pos.x, local_140.x, 1.0f, (REG0_F(15) + 400.0f) * param_1->m2500);
        cLib_addCalc2(&param_1->current.pos.y, local_140.y, 1.0f, (REG0_F(15) + 400.0f) * param_1->m2500);
        cLib_addCalc2(&param_1->current.pos.z, local_140.z, 1.0f, (REG0_F(15) + 400.0f) * param_1->m2500);
        cLib_addCalc2(&param_1->m2500, 1.0f, 1.0f, 0.01f);
        pl_pos_add(param_1);
        local_110 = param_1->current.pos - local_140;
        iVar8 = -1;
        iVar8 = local_110.abs();
        if (dVar21 > 5.0f) {
            fopAcM_seStart(param_1, JA_SE_LK_ROPE_UNWIND, 0);
        } else {
            fopAcM_SetParam(param_1, 0);
            fopAcM_seStart(param_1, JA_SE_LK_ROPE_UNCOIL, 0);
            param_1->m02DC = 0;
            param_1->m217C = NULL;
            param_1->m24D8 = 0;
        }
        break;
    }
    case 8: {
        cLib_addCalc2(&param_1->speedF, -50.0f, 1.0f, 6.0f);
    }
    case 9: {
        cLib_addCalc2(&param_1->current.pos.x, local_140.x, 1.0f, (REG0_F(15) + 400.0f) * param_1->m2500);
        cLib_addCalc2(&param_1->current.pos.y, local_140.y, 1.0f, (REG0_F(15) + 400.0f) * param_1->m2500);
        cLib_addCalc2(&param_1->current.pos.z, local_140.z, 1.0f, (REG0_F(15) + 400.0f) * param_1->m2500);
        cLib_addCalc2(&param_1->m2500, 1.0f, 1.0f, 0.01f);
        pl_pos_add(param_1);
        local_110 = param_1->current.pos - local_140;
        iVar8 = -1;
        iVar8 = local_110.abs();
        if (dVar21 > 5.0f) {
            fopAcM_seStart(param_1, JA_SE_LK_ROPE_UNWIND, 0);
        } else {
            fopAcM_SetParam(param_1, 0);
            param_1->m02DC = 0;
            param_1->current.pos = local_140;
            param_1->m029E = REG0_S(6) + 20;
        }
        param_1->m02CC = REG0_S(0);
        break;
    }
    case 10: {
        iVar8 = (param_1->m2188 * (REG0_F(1) + 0.060000002f));
        param_1->m02CC = 100 - iVar8;
        param_1->current.pos = param_1->m2504;
        cLib_addCalc2(&param_1->m02E4, -6.25f, 1.0f, 0.375f);
        if (fopAcM_GetParam(param_1) == 3) {
            param_1->m02DC = 11;
            if ((fopAcM_GetParam(param_1->m217C) & 0xF0) != 0) {
                dComIfGs_onEventBit(0x540);
            } else {
                dComIfGs_onEventBit(0x580);
            }
        }
        param_1->m217C->health = 1;
    }
    case 11: {
        param_1->current.pos = param_1->m2504;
        iVar8 = (param_1->m2188 * (REG0_F(2) + 0.060000002f));
        param_1->m02CC = 100 - iVar8;
        param_1->m217C->health = 3;
        if (fopAcM_GetParam(param_1) == 4) {
            fopAcM_SetParam(param_1, 0);
            fopAcM_seStart(param_1, JA_SE_LK_ROPE_UNCOIL, 0);
            param_1->m02DC = 0;
            param_1->m217C->health = 0;
            param_1->m217C = NULL;
            if (param_1->m24D9 != 0) {
                param_1->m24D9 = 6;
                param_1->m029C = 120;
            }
            param_1->m24D8 = 0;
        }
    }
    }
    dVar21 = 0.0f;
    switch (param_1->m24D9) {
    default:
        break;
    case -1: {
        if (!param_1->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(param_1, dEvtFlag_NOPARTNER_e, 0xFFFF, 0);
            param_1->eventInfo.onCondition(dEvtCnd_UNK2_e);
            break;
        }
        param_1->m24F4 = REG0_F(12) + 50.0f;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        param_1->m24D9 = 2;
        param_1->m24B4 = -400.0f;
        param_1->m24BC = 0;
        param_1->m24C8 = 0;
        param_1->m24C4 = 0.0f;
        param_1->m24CA = 0;
        if (param_1->m251C != 0) {
            param_1->m2510 = param_1->m217C->current.angle.y + -0x4000;
        } else {
            param_1->m2510 = param_1->m217C->current.angle.y + 0x4000;
        }
        if ((fopAcM_GetParam(param_1->m217C) & 0xF0) != 0) {
            param_1->m24B8 = REG0_F(6) + -90.0f;
            param_1->m2514 = -1.0f;
            param_1->m2518 = REG0_F(7) + 1.0f;
            param_1->m24FC = REG0_F(16) + 3.5f;
        } else {
            param_1->m24B8 = 0.0f;
            if (l_himo2HIO.m06 == 2) {
                param_1->m2514 = 1.0f;
                param_1->m2518 = -1.0f;
            } else if (l_himo2HIO.m06 < 2) {
                if (l_himo2HIO.m06 == 0) {
                    fVar26 = cM_rndF(1.0f);
                    if (fVar26 < 0.5f) {
                        param_1->m2514 = 1.0f;
                    } else {
                        param_1->m2514 = -1.0f;
                    }
                    fVar26 = cM_rndF(1.0f);
                    if (fVar26 < 0.5f) {
                        param_1->m2518 = 1.0f;
                    } else {
                        param_1->m2518 = -1.0f;
                    }
                } else if (l_himo2HIO.m06 < -1) {
                    param_1->m2514 = 1.0f;
                    param_1->m2518 = 1.0f;
                }
            } else if (l_himo2HIO.m06 == 4) {
                param_1->m2514 = -1.0f;
                param_1->m2518 = -1.0f;
            } else if (l_himo2HIO.m06 < 4) {
                param_1->m2514 = -1.0f;
                param_1->m2518 = 1.0f;
            }
            if (param_1->m2518 < 0.0f) {
                param_1->m24FC = REG0_F(6) + 3.0f;
            } else {
                param_1->m24FC = 1.0f;
            }
        }
        param_1->m24E8 = param_1->m217C->current.pos;
    }
    case 2: {
        cLib_addCalc0(&param_1->m24B8, (REG0_F(7) + 3.0f), dVar19);
        cLib_addCalc2(&param_1->m24B4, -144.0f, 1.0f, 10.0f);
        if (param_1->m24B4 > -145.0f) {
            if (param_1->m24BC < 400) {
                fVar26 = 20.0f - ((param_1->m217C->scale).y - 1.0f) * 17.0f;
                if (fVar26 < 0.5f) {
                    fVar26 = 0.5f;
                }
                iVar8 = (param_1->m24C4 / fVar26);
                param_1->m24C0 = param_1->m24BC;
                param_1->m24BC += iVar8;
                param_1->m24C4 += 1.0f;
                iVar9 = param_1->m24C0;
                if (iVar9 == 0) {
                    fopAcM_seStart(param_1, JA_SE_LK_ROPE_COIL_1, 0);
                } else if ((iVar9 >= 13) && (param_1->m24BC <= iVar8 + 13)) {
                    fopAcM_seStart(param_1, JA_SE_LK_ROPE_COIL_2, 0);
                } else if ((iVar9 >= 26) && (param_1->m24BC <= iVar8 + 26)) {
                    fopAcM_seStart(param_1, JA_SE_LK_ROPE_COIL_3, 0);
                } else if ((iVar9 >= 39) && (param_1->m24BC <= iVar8 + 39)) {
                    fopAcM_seStart(param_1, JA_SE_LK_ROPE_COIL_3, 0);
                }
            }
            if ((fopAcM_GetParam(param_1->m217C) & 0x0F) == 3) {
                fVar26 = ((param_1->m217C->scale).y - 0.14f) + REG8_F(7);
            } else {
                fVar26 = (param_1->m217C->scale).y;
            }
            uVar6 = (uint)(4000.0f - (fVar26 - 1.0f) * 2000.0f);
            sVar15 = uVar6;
            cLib_addCalcAngleS2(&param_1->m24C8, sVar15, 1, (sVar15 >> 3) + (u16)(sVar15 < 0 && (uVar6 & 7) != 0));
            if (param_1->m24BC < 49) {
                if (param_1->m24CA == 9000) {
                    param_1->m24CA = 0x238c;
                } else if (param_1->m24CA < 9000) {
                    param_1->m24CA = 9000;
                    if ((fopAcM_GetParam(param_1->m217C) & 0xF0) != 0) {
                        fopAcM_seStart(param_1, JA_SE_LK_ROPE_HOOK_BODY, 0);
                    } else {
                        fopAcM_seStart(param_1, JA_SE_LK_ROPE_HOOK_WOOD, 0);
                    }
                }
            }
        }
        cLib_addCalc2(&param_1->m24E8.x, param_1->m217C->current.pos.x, 0.3f, 100.0f);
        cLib_addCalc2(&param_1->m24E8.y, param_1->m217C->current.pos.y, 0.3f, 100.0f);
        cLib_addCalc2(&param_1->m24E8.z, param_1->m217C->current.pos.z, 0.3f, 100.0f);
        param_1->m24DC = param_1->m217C->current.pos;
        mDoMtx_YrotS(*calc_mtx, param_1->m2510);
        local_110.x = (REG0_F(5) * 10.0f + 50.0f) * param_1->m2514;
        local_110.y = (REG0_F(4) * 10.0f - 200.0f) + 140.0f;
        local_110.z = ((REG0_F(3) * 10.0f + 200.f) - 80.0f) * param_1->m2518;
        MtxPosition(&local_110, &local_11c);
        param_1->m24DC.x = param_1->m24DC.x + local_11c.x * param_1->m24FC;
        param_1->m24DC.y = param_1->m24DC.y + local_11c.y * param_1->m24FC;
        param_1->m24DC.z = param_1->m24DC.z + local_11c.z * param_1->m24FC;
        if ((fopAcM_GetParam(param_1->m217C) & 0xF0) != 0) {
            cLib_addCalc2(&param_1->m24FC, REG0_F(6) + 1.8f, REG0_F(4) + 0.2f, REG0_F(5) + 0.1f);
        } else {
            cLib_addCalc2(&param_1->m24FC, 1.0f, REG0_F(4) + 0.2f, REG0_F(5) + 0.1f);
        }
    }
    case 3: {
        param_1->m217C->health = 2;
        mDoMtx_YrotS(*calc_mtx, param_1->m217C->current.angle.y);
        local_110.x = ((REG0_F(11) + 2000.0f) - 800.0f) - 300.0f;
        local_110.y = param_1->m217C->home.pos.y + REG0_F(12) + 2000.0f;
        local_110.z = REG0_F(13) + 1000.0f;
        MtxPosition(&local_110, &local_11c);
        cLib_addCalc2(&param_1->m24DC.x, local_11c.x, 0.3f, 200.0f);
        cLib_addCalc2(&param_1->m24DC.y, local_11c.y, 0.3f, 200.0f);
        cLib_addCalc2(&param_1->m24DC.z, local_11c.z, 0.3f, 200.0f);
        cLib_addCalc2(&param_1->m24E8.y, param_1->m217C->home.pos.y + 2500.0f + REG0_F(14), 0.3f, 100.0f);
        cLib_addCalc2(&param_1->m24F4, REG0_F(13) + 80.0f, 1.0f, 2.0f);
        if (param_1->m029C < 30) {
            btd->m6E15 = 0xB4;
        }
        if (param_1->m029C == 30) {
            fopAcM_seStartCurrent((fopAc_ac_c*)dr, JA_SE_CM_BTD_ROPE_SET, 0);
        }
        if (((dComIfGp_getStartStageName()[0] != 'X') && (param_1->m029C <= 1)) && (!dComIfGs_isEventBit(0x420))) {
            dKy_custom_colset(0, 4, 1.0f);
        }
        if ((param_1->m029C != 0) || (REG0_S(8) != 0)) {
            break;
        }
        btd->m6E15 = 1;
        param_1->m24D9 = 4;
        if ((dComIfGp_getStartStageName()[0] == 'X') || (dComIfGs_isEventBit(0x420))) {
            param_1->m029C = 0;
        } else {
            dComIfGs_onEventBit(0x420);
            param_1->m029C = REG0_S(2) + 62;
            pdVar13->hide();
        }
        param_1->m02E0 = 0;
        param_1->m217C->health = 0;
        if (btd != 0) {
            fopAcM_OnStatus(btd, 0x4000);
        }
    }
    case 4: {
        dKy_custom_colset(0, 4, 1.0f);
        if (param_1->m029C == (s16)(REG0_S(2) + 57)) {
            mDoAud_seStart(JA_SE_CV_DRG_SET_ROPE, 0, 0, 0);
        }
        if (param_1->m029C <= 1) {
            dKy_custom_colset(0, 4, 0.0f);
        }
        if ((param_1->m029C == 0) && (REG0_S(8) == 0)) {
            dr->unk_50C = 0;
            dKy_custom_colset(0, 4, 0.0f);
            param_1->m24D9 = 5;
            param_1->m029C = 50;
            param_1->m02E0 = 0;
            fopAcM_SetParam(param_1, 2);
            dComIfGp_event_reset();
            param_1->m02A4 = 20;
            sVar15 = fopAcM_searchPlayerAngleY(param_1);
            param_1->m2510 = sVar15 + 0x8000;
            param_1->m2512 = param_1->m2510;
            param_1->m24F4 = 65.0f;
            param_1->m24F8 = 65.0f;
            mDoMtx_YrotS(*calc_mtx, param_1->m2510);
            local_110.x = REG0_F(7) + 100.0f + 200.0f;
            local_110.y = param_1->current.pos.y + 700.0f + REG0_F(8);
            local_110.z = REG0_F(9) + -500.0f;
            MtxPosition(&local_110, &param_1->m24DC);
            param_1->m24DC.x = param_1->m24DC.x + param_1->current.pos.x * (REG0_F(15) + 0.55f);
            param_1->m24DC.z = param_1->m24DC.z + param_1->current.pos.z * (REG0_F(15) + 0.55f);
            param_1->m24E8 = pdVar13->current.pos;
            param_1->m24E8.y = param_1->m24E8.y - 50.0f;
            pdVar13->show();
        } else {
            param_1->m24F4 = REG0_F(12) + 50.0f;
            dr->unk_50C = 1;
            dVar19 = 2000.0f;
            param_1->m24DC.x = ((REG0_F(14) + 3000.0f) - 10000.0f) + 2000.0f;
            param_1->m24DC.y = REG0_F(15) + 10000.0f + 2000.0f + 9720.0f;
            param_1->m24DC.z = (REG0_F(16) + 6000.0f) - 2000.0f;
            param_1->m24E8.x = REG0_F(17);
            param_1->m24E8.y = (REG0_F(18) + 10000.0f + 2000.0f + 9720.0f) - 300.0f;
            param_1->m24E8.z = REG0_F(19);
        }
        break;
    }
    case 5: {
        if (param_1->m029C == 0) {
            if (param_1->m02E0 == 0) {
                mDoAud_seStart(JA_SE_CV_DRG_ROCKFALL_1, 0, 0, 0);
            } else if (param_1->m02E0 == 1) {
                mDoAud_seStart(JA_SE_CV_DRG_ROCKFALL_1_2, 0, 0, 0);
            } else if (param_1->m02E0 >= 2) {
                mDoAud_seStart(JA_SE_CV_DRG_ROCKFALL_1_3, 0, 0, 0);
                param_1->m02E0 = 2;
            }
            param_1->m02E0++;
            param_1->m029C = 50;
        }
        dVar21 = g_mDoCPd_cpadInfo[0].mCStickPosY;
    }
    case 6: {
        iVar8 = g_mDoCPd_cpadInfo[0].mCStickPosX * (REG0_F(6) + 1000.0f);
        param_1->m2512 += iVar8;
        cLib_addCalcAngleS2(&param_1->m2510, param_1->m2512, 4, 0x1000);
        if (dVar21 <= -0.1f) {
            fVar26 = std::fabsf(dVar21);
            cLib_addCalc2(&param_1->m24F8, REG0_F(7) + 70.0f, 1.0f, fVar26 * 3.0f);
        } else if (dVar21 >= 0.1f) {
            fVar26 = ::std::fabsf(dVar21);
            cLib_addCalc2(&param_1->m24F8, REG0_F(8) + 20.0f, 1.0f, fVar26 * 3.0f);
        }
        cLib_addCalc2(&param_1->m24F4, param_1->m24F8, 0.1f, 10.0f);
        mDoMtx_YrotS(*calc_mtx, param_1->m2510);
        local_110.x = REG0_F(7) + 100.0f + 200.0f;
        local_110.y = param_1->current.pos.y + 700.0f + REG0_F(8);
        local_110.z = REG0_F(9) + -500.0f;
        MtxPosition(&local_110, &param_1->m24DC);
        param_1->m24DC.x = param_1->m24DC.x + param_1->current.pos.x * (REG0_F(15) + 0.55f);
        param_1->m24DC.z = param_1->m24DC.z + param_1->current.pos.z * (REG0_F(15) + 0.55f);
        cLib_addCalc2(&param_1->m24E8.x, param_1->current.pos.x, 0.3f, 100.0f);
        cLib_addCalc2(&param_1->m24E8.y, (param_1->current.pos.y - 50.0f) + REG0_F(10), 0.3f, 100.0f);
        cLib_addCalc2(&param_1->m24E8.z, param_1->current.pos.z, 0.3f, 100.0f);
        if ((param_1->m02A4 == 0) && (!player->checkPlayerFly())) {
            camera->mCamera.Start();
            param_1->m24D9 = 0;
            param_1->m24D8 = 0;
            fopAcM_SetParam(param_1, 0);
            param_1->m02DC = 0;
            param_1->m217C = NULL;
            dComIfGp_event_reset();
        }
        break;
    }
    case 7: {
        if (player->getRopeJumpLand() || (param_1->m029C == 0)) {
            if (!param_1->eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderPotentialEvent(param_1, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                param_1->eventInfo.onCondition(dEvtCnd_UNK2_e);
            }
            dr->unk_4CA = 0x5A;
            cLib_addCalc2(&param_1->m24F8, REG0_F(8) + 20.0f, 1.0f, REG0_F(9) + 2.0f);
        } else {
            param_1->m24D9 = 7;
            param_1->m029C = 10;
        }
        if (param_1->m029C != 0) {
            break;
        }
        if (dr->unk_4BA < 9) {
            param_1->m24D9 = 0;
            camera->mCamera.Reset(param_1->m24DC, param_1->m24E8);
            camera->mCamera.Start();
            camera->mCamera.SetTrimSize(0);
            dComIfGp_event_reset();
            break;
        }
        param_1->m24F4 = REG0_F(12) + 50.0f;
        fopAcM_OnStatus(btd, 0x4000);
        param_1->m24D9 = 8;
        param_1->m24E8.x = 0.0f;
        param_1->m24E8.y = REG0_F(5) * 0.1f + 3000.0f;
        param_1->m24E8.z = REG0_F(6) * 0.1f;
        mDoMtx_YrotS(*calc_mtx, btd->current.angle.y);
        local_110.x = REG0_F(7) * 0.1f;
        local_110.y = REG0_F(8) * 0.1f + 1000.0f;
        local_110.z = REG0_F(9) * 0.1f + 1400.0f;
        MtxPosition(&local_110, &param_1->m24DC);
        param_1->m24F4 = REG0_F(13) + 80.0f;
        param_1->m029C = 210;
        dBgS_LinChk dStack_104;
        dStack_104.Set(&param_1->m24E8, &param_1->m24DC, param_1);
        if (dComIfG_Bgsp()->LineCross(&dStack_104)) {
            param_1->m24DC = dStack_104.GetCross();
        }
    }
    case 8: {
        dr->unk_40A = 3;
        if (param_1->m029C == 200) {
            mDoAud_seStart(JA_SE_CV_DRG_ROCKFALL_2, 0, 0, 0);
        }
        if (param_1->m029C == 170) {
            fopAcM_seStartCurrent((fopAc_ac_c*)dr, JA_SE_CM_BTD_BEF_ROCK_FALL, 0);
        }
        if (param_1->m029C > 150) {
            fVar26 = 2000.0f;
        } else {
            fVar26 = 100.0f;
        }
        cLib_addCalc2(&dr->unk_414, fVar26, 0.5f, 100.0f);
        if (param_1->m029C <= 120) {
            cLib_addCalc2(&param_1->m24E8.y, REG0_F(5) * 0.1f + 650.0f, 1.0f, 100.0f);
            cLib_addCalc2(&param_1->m24DC.y, 0.0f, 0.5f, 100.0f);
            if (param_1->m029C == (s16)(REG0_S(4) + 0x6E)) {
                param_1->m2520 = REG0_F(11) + 50.0f;
                btd->m6E15 = 0xB4;
            }
            if (param_1->m029C < 81) {
                cLib_addCalc2(&param_1->m24F4, REG0_F(14) + 40.0f, 0.5f, 2.0f);
            }
        }
        if (param_1->m029C == 2) {
            btd->m6E15 = 1;
        }
        if (param_1->m029C == 0) {
            if (btd->m6190 >= 3) {
                param_1->m24D9 = 9;
                param_1->m029C = 220;
            } else {
                param_1->m24D9 = 0;
                cXyz local_164 = param_1->eyePos;
                local_164.x *= 0.9f;
                local_164.z *= 0.9f;
                camera->mCamera.Reset(param_1->eyePos, local_164);
                camera->mCamera.Start();
                camera->mCamera.SetTrimSize(0);
                fopAcM_OffStatus(btd, fopAcStts_UNK4000_e);
                dComIfGp_event_reset();
            }
            dr->unk_40A = 0;
        }
        break;
    }
    case 9: {
        cLib_addCalc2(&param_1->m24F4, REG0_F(4) + 50.0f, 0.5f, 3.0f);
        cLib_addCalc2(&param_1->m24E8.y, btd->eyePos.y + REG0_F(5) * 0.1f + 200.0f, 0.2f, 1000.0f);
        mDoMtx_YrotS(*calc_mtx, btd->current.angle.y);
        local_110.x = REG0_F(7) * 0.1f + -300.0f;
        local_110.y = REG0_F(8) * 0.1f + 100.0f;
        local_110.z = REG0_F(9) * 0.1f + 2000.0f;
        MtxPosition(&local_110, &local_11c);
        cLib_addCalc2(&param_1->m24DC.x, local_11c.x, 0.1f, 50.0f);
        cLib_addCalc2(&param_1->m24DC.y, local_11c.y, 0.1f, 50.0f);
        cLib_addCalc2(&param_1->m24DC.z, local_11c.z, 0.1f, 50.0f);
        if (param_1->m029C == 99) {
            btd->m6E15 = 0xB4;
        }
        if (param_1->m029C == 40) {
            btd->m6E15 = 1;
        }
        if (param_1->m029C == 0) {
            param_1->m24D9 = 0;
            cXyz local_170 = param_1->eyePos;
            local_170.x *= 0.9f;
            local_170.z *= 0.9f;
            camera->mCamera.Reset(param_1->eyePos, local_170);
            camera->mCamera.Start();
            camera->mCamera.SetTrimSize(0);
            fopAcM_OffStatus(btd, fopAcStts_UNK4000_e);
            dComIfGp_event_reset();
        }
        break;
    }
    }
    if (param_1->m24D9 < 0) {
        dVar21 = cM_ssin(param_1->m02D8 * 0x3300);
        dVar22 = (param_1->m2520 * dVar21);
        dVar21 = cM_scos(param_1->m02D8 * 0x3000);
        cXyz local_188;
        cXyz local_17c;
        local_188.y = (param_1->m2520 * dVar21);
        local_17c.x = (param_1->m24DC.x + dVar22);
        local_17c.y = param_1->m24DC.y + local_188.y;
        local_17c.z = param_1->m24DC.z;
        local_188.x = (param_1->m24E8.x + dVar22);
        local_188.y = param_1->m24E8.y + local_188.y;
        local_188.z = param_1->m24E8.z;
        dVar21 = cM_scos(param_1->m02D8 * 0x1C00);
        iVar8 = ((param_1->m2520 * dVar21) * 7.5f);
        camera->mCamera.Set(local_188, local_17c, iVar8, param_1->m24F4);
        cLib_addCalc0(&param_1->m2520, (REG0_F(16) + 2.0f), dVar19);
        sVar15 = 0;
        if ((param_1->m217C != NULL) && ((fopAcM_GetParam(param_1->m217C) & 0xF0) != 0)) {
            sVar15 = -50;
        }
        if (((sVar15 + 0x82) < param_1->m24BC) && (REG0_S(8) == 0)) {
            if ((fopAcM_GetParam(param_1->m217C) & 0xF0) == 0) {
                if (dr->unk_4BA < 10) {
                    param_1->m24D9 = 4;
                    param_1->m24D8 = 2;
                    param_1->m029C = 0;
                    if (btd != 0) {
                        fopAcM_OnStatus(btd, 0x4000);
                    }
                } else {
                    param_1->m24D9 = 3;
                    param_1->m029C = REG0_S(2) + 65;
                }
                param_1->m24D8 = 2;
            } else if (param_1->m24D9 == 2) {
                camera->mCamera.Start();
                param_1->m24D9 = 0;
                param_1->m24D8 = 2;
                fopAcM_SetParam(param_1, 2);
                dComIfGp_event_reset();
            }
        }
    }
    if (param_1->m02CC < 2) {
        param_1->m02CC = 2;
    }
}

/* 800F01BC-800F062C       .text daHimo2_Execute__FP11himo2_class */
static BOOL daHimo2_Execute(himo2_class* param_1) {
    /* Nonmatching - last for loop, regalloc */
    daPy_py_c* apdVar1;
    himo2_s* phVar3;
    int iVar4;
    int iVar5;
    f32 dVar7;
    f32 dVar8;
    f32 dVar9;
    f32 fVar10;
    cXyz local_c8;

    apdVar1 = daPy_getPlayerActorClass();
    if (btd == NULL) {
        btd = (btd_class*)fpcEx_Search(b_a_sub, param_1);
    }
    if (dr == NULL) {
        dr = (dr2_class*)fpcEx_Search(dr_a_sub, param_1);
    }
    param_1->m02D8++;
    rope_scale = l_himo2HIO.m1C;
    local_c8.x = 4.0f;
    local_c8.y = 0.0f;
    local_c8.z = 0.0f;
    if (apdVar1->getRopeGrabRightHand()) {
        MTXCopy(apdVar1->getLeftHandMatrix(), *calc_mtx);
        MtxPosition(&local_c8, &param_1->m02EC[1]);
        MTXCopy(apdVar1->getRightHandMatrix(), *calc_mtx);
        MtxPosition(&local_c8, &param_1->m02EC[0]);
    } else {
        MTXCopy(apdVar1->getLeftHandMatrix(), *calc_mtx);
        MtxPosition(&local_c8, &param_1->m02EC[0]);
        MTXCopy(apdVar1->getRightHandMatrix(), *calc_mtx);
        MtxPosition(&local_c8, &param_1->m02EC[1]);
    }
    param_1->m02B4 = param_1->m02EC[0];
    iVar5 = param_1->m02CC + -50;
    if (iVar5 < 3) {
        iVar5 = 3;
    }
    dBgS_GndChk local_bc;
    phVar3 = &param_1->m1120[0];
    dVar7 = 60.0f;
    dVar8 = 5.0f;
    dVar9 = -100000.0f;
    for (iVar4 = 0; iVar4 < iVar5; iVar4++) {
        if (param_1->m02DC != 2) {
            local_bc.m_pos.x = phVar3->m10.x;
            local_bc.m_pos.y = phVar3->m10.y + dVar7;
            local_bc.m_pos.z = phVar3->m10.z;
            fVar10 = dComIfG_Bgsp()->GroundCross(&local_bc);
            phVar3->m0C = (dVar8 + fVar10);
        } else {
            phVar3->m0C = dVar9;
        }
        phVar3++;
    }
    new_himo2_move(param_1);
    phVar3 = &param_1->m0310[0];
    for (iVar5 = 0; iVar5 < param_1->m02CC++; iVar5++, phVar3++) {
        phVar3->m10 = param_1->m02B4;
    }
    himo2_control(param_1, phVar3);
    param_1->m0310[99].m10 = param_1->current.pos;
    himo2_control2(param_1, phVar3);
    if ((param_1->m02DC == 2) || (param_1->m02DC == 3)) {
        param_1->m2050.SetR(20.0f);
    } else {
        param_1->m2050.SetR(-100.0f);
    }
    param_1->m2050.SetC(param_1->current.pos);
    dComIfG_Ccsp()->Set(&param_1->m2050);
    param_1->eyePos = param_1->current.pos;
    return TRUE;
}

/* 800F062C-800F0634       .text daHimo2_IsDelete__FP11himo2_class */
static BOOL daHimo2_IsDelete(himo2_class*) {
    return TRUE;
}

/* 800F0634-800F0670       .text daHimo2_Delete__FP11himo2_class */
static BOOL daHimo2_Delete(himo2_class*) {
    mDoHIO_deleteChild(l_himo2HIO.mNo);
    return TRUE;
}

/* 800F0670-800F07F4       .text CallbackCreateHeap__FP10fopAc_ac_c */
static int CallbackCreateHeap(fopAc_ac_c* i_this) {
    /* Nonmatching - "a_this->m1FD8.init" */
    ResTIMG* pRVar1;
    J3DModelData* modelData;
    himo2_class* a_this = (himo2_class*)i_this;

    pRVar1 = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE);
    if (!a_this->m1F30.init(1, 200, pRVar1, 0)) {
        return FALSE;
    } else {
        modelData = (J3DModelData*)dComIfG_getObjectRes("Link", LINK_BDL_ROPEEND);
        JUT_ASSERT(3933, modelData != NULL);
        a_this->m24B0 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (a_this->m24B0 == NULL) {
            return FALSE;
        } else {
            pRVar1 = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE);
            if (!a_this->m1F98.init(5, 0x20, pRVar1, 0)) {
                return FALSE;
            } else {
                pRVar1 = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE);
                return a_this->m1FD8.init(1, 16, pRVar1, 0) != FALSE;
            }
        }
    }
}

/* 800F07F4-800F0B08       .text daHimo2_Create__FP10fopAc_ac_c */
static cPhs_State daHimo2_Create(fopAc_ac_c* i_this) {
    /* Nonmatching - regalloc */
    cPhs_State phase_state;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    himo2_class* a_this = (himo2_class*)i_this;

    fopAcM_SetupActor(i_this, himo2_class);
    if (!fopAcM_entrySolidHeap(a_this, CallbackCreateHeap, REG0_S(9) + 0x9050)) {
        phase_state = cPhs_ERROR_e;
    } else {
        a_this->m24B0->setBaseScale(cXyz(1.0f, 1.0f, 1.0f));
        a_this->m02CC = REG0_S(1) + 96;
        a_this->current.pos = player->getLeftHandPos();
        a_this->m2574.Set(&a_this->current.pos, &a_this->old.pos, a_this, 1, &a_this->m2534, &a_this->speed, NULL, NULL);
        a_this->m2534.SetWall(30.0f, 30.0f);
        a_this->m2574.ClrRoofNone();
        a_this->m2574.m_roof_crr_height = REG0_F(7) + 60.0f;
        a_this->m2500 = 1.0f;
        l_himo2HIO.mNo = mDoHIO_createChild("ロープ", &l_himo2HIO); // Rope
        rope_scale = 2.0f;
        static dCcD_SrcSph sph_src = {
            // dCcD_SrcGObjInf
            {
                /* Flags             */ 0,
                /* SrcObjAt  Type    */ AT_TYPE_GRAPPLING_HOOK,
                /* SrcObjAt  Atp     */ 1,
                /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e,
                /* SrcObjTg  Type    */ 0,
                /* SrcObjTg  SPrm    */ 0,
                /* SrcObjCo  SPrm    */ 0,
                /* SrcGObjAt Se      */ dCcG_SE_UNK5,
                /* SrcGObjAt HitMark */ dCcG_AtHitMark_Unk1_e,
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
                /* Radius */ 20.0f,
            }},
        };
        a_this->m2014.Init(0xFF, 0xFF, a_this);
        a_this->m2050.Set(sph_src);
        a_this->m2050.SetStts(&a_this->m2014);
        btd = 0;
        dr = 0;
        phase_state = cPhs_COMPLEATE_e;
    }
    return phase_state;
}

static actor_method_class l_daHimo2_Method = {
    (process_method_func)daHimo2_Create,
    (process_method_func)daHimo2_Delete,
    (process_method_func)daHimo2_Execute,
    (process_method_func)daHimo2_IsDelete,
    (process_method_func)daHimo2_Draw,
};

actor_process_profile_definition g_profile_HIMO2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_HIMO2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(himo2_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_HIMO2,
    /* Actor SubMtd */ &l_daHimo2_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
