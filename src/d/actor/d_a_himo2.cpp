/**
 * d_a_himo2.cpp
 * Item - Grappling Hook / ロープ (Rope)
 */

#include "d/dolzel.h" // IWYU pragma: keep
#include "d/actor/d_a_bk.h"
#include "d/actor/d_a_player_main.h"
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
#include "m_Do/m_Do_graphic.h"
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
#if VERSION > VERSION_DEMO
static btd_class* btd;
dr2_class* dr;
#endif

/* 800EB60C-800EBABC       .text spin_draw__FP11himo2_class */
void spin_draw(himo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int r27;
    s16 r22;
    s16 r23;
    s16 r26;
    f32 f4;
    s16 r24;
    f32 f5;
    s16 r30;
    cXyz* r29;
    cXyz local_504;
    cXyz local_510;
    cXyz local_51c;
    cXyz local_528;

    r26 = 0;
    r23 = i_this->m2510;
    f4 = (i_this->m217C->scale.y - 1.0f) * 8.0f;
    f5 = (i_this->m217C->scale.y - 1.0f) *  -7.0f;
#if VERSION > VERSION_DEMO
    if ((fopAcM_GetParam(i_this->m217C) & 0x0F) == 3) {
        f4 += REG8_F(8) + -3.0f;
        f5 += REG8_F(9) + 1.5f;
    }
#endif
    if (i_this->m217C->scale.y < 0.7f) {
        f4 += 3.0f;
    }
    if (i_this->m251C != 0) {
        r24 = 700;
        local_504.x = REG0_F(0) * 10.0f - 15.0f;
    } else {
        r24 = -700;
        local_504.x = REG0_F(0) * 10.0f + 15.0f;
    }
    local_504.x = local_504.x + i_this->m24B8;
    local_504.y = f4 + -152.5f;
    local_504.z = i_this->m24B4 + 26.0f + f5;
    cMtx_YrotS(*calc_mtx, r23);
    MtxPosition(&local_504, &local_510);
    local_51c.x = i_this->m217C->current.pos.x + local_510.x;
    local_51c.y = i_this->m217C->current.pos.y + local_510.y;
    local_51c.z = i_this->m217C->current.pos.z + local_510.z;
    local_504.x = 0.0f;
    local_504.y = 0.0f;
    local_504.z = 3.90625f;
    r30 = -0x30d4;
    r29 = i_this->m1F30.getPos(0);
    r29 += i_this->m1F6C;
    cXyz local_4f8[100];
    for (r27 = 0; r27 < 100; r27++) {
        cXyz* r21 = &local_4f8[r27];
        r21->y = -200000.0f;
        if (r27 < 50) {
            r22 = r30;
            r30 += (s16)(REG0_S(2) + 100);
        } else if ((r27 >= 50) && (r27 <= i_this->m24BC + 49)) {
            r22 = r30;
            r30 = (s16)(r30 + i_this->m24C8);
            if (r27 >= 100 - (REG0_S(4) + 5)) {
                r30 += REG0_S(5) + -1000;
            }
            if ((i_this->m217C != NULL) && ((fopAcM_GetParam(i_this->m217C) & 0xF0) != 0)) {
                r26 = REG0_S(4) + r26 + -400;
            }
        } else {
            r22 = r30;
            if (i_this->m24BC == 0) {
                r30 += (s16)(REG0_S(2) + 70);
            } else {
                r30 += 50;
            }
        }
        cMtx_YrotS(*calc_mtx, r23);
        cMtx_ZrotM(*calc_mtx, r26);
        cMtx_XrotM(*calc_mtx, r22);
        cMtx_YrotM(*calc_mtx, r24);
        MtxPosition(&local_504, &local_510);
        local_51c.x = local_51c.x + local_510.x;
        local_51c.y = local_51c.y + local_510.y;
        local_51c.z = local_51c.z + local_510.z;
        if (r27 == REG0_S(6) + 48) {
            i_this->m2504 = local_51c;
        }
        if ((i_this->m24D8 < 2) || (r27 >= 50)) {
            if (r27 == 99) {
                MtxTrans(local_51c.x, local_51c.y, local_51c.z, false);
                cMtx_YrotM(*calc_mtx, r23);
                cMtx_ZrotM(*calc_mtx, r26);
                cMtx_XrotM(*calc_mtx, r22);
                cMtx_YrotM(*calc_mtx, r24);
                MtxTrans(0.0f, 0.0f, -3.0f, true);
                cMtx_XrotM(*calc_mtx, i_this->m24CA);
                local_528.x = 0.0f;
                local_528.y = 0.0f;
                local_528.z = 15.0f;
                MtxPosition(&local_528, &i_this->m24CC);
                MtxScale(0.2f, 0.2f, 0.2f, true);
                J3DModel* pJVar10 = i_this->m24B0;
                pJVar10->setBaseTRMtx(*calc_mtx);
                g_env_light.setLightTevColorType(pJVar10, &actor->tevStr);
                mDoExt_modelUpdateDL(pJVar10);
            } else {
                local_4f8[r27] = local_51c;
            }
        }
    }
    for (int i = 99; i >= 0; i--) {
        if (local_4f8[i].y > -100000.0f) {
            r29->x = local_4f8[i].x;
            r29->y = local_4f8[i].y;
            r29->z = local_4f8[i].z;
            i_this->m1F6C++;
            r29++;
        }
    }
}

/* 800EBABC-800EBCD0       .text himo2_control__FP11himo2_classP7himo2_s */
void himo2_control(himo2_class* i_this, himo2_s* param_2) {
    f32 fVar1;
    f32 fVar2;
    f32 dVar8;
    cXyz local_68;
    cXyz local_74;

    local_68.x = 0.0f;
    local_68.y = 0.0f;
#if VERSION > VERSION_DEMO
    if (i_this->m02DC == 0) {
        local_68.z = i_this->m2188 * 15.625f * (REG8_F(18) + 0.002f);
    } else
#endif
    {
        local_68.z = i_this->m2188 * 15.625f * (REG0_F(1) + 0.0007f);
    }
    int i;
    int i2;
    i2 = i_this->m02CC + 1;
    param_2 += i2;
    for (i = i2; i < 100; i++, param_2++) {
        dVar8 = ((param_2->m10.y + i_this->m02E4) - param_2[-1].m10.y);
        fVar1 = param_2->m10.x - param_2[-1].m10.x;
        fVar2 = param_2->m10.z - param_2[-1].m10.z;
        s16 r30;
        int r29;
        r29 = cM_atan2s(fVar1, fVar2);
        r30 = -cM_atan2s(dVar8, std::sqrtf((fVar1 * fVar1) + (fVar2 * fVar2)));
        cMtx_YrotS(*calc_mtx, r29);
        cMtx_XrotM(*calc_mtx, r30);
        MtxPosition(&local_68, &local_74);
        param_2->m10.x = param_2[-1].m10.x + local_74.x;
        param_2->m10.y = param_2[-1].m10.y + local_74.y;
        param_2->m10.z = param_2[-1].m10.z + local_74.z;
    }
}

/* 800EBCD0-800EBFEC       .text himo2_control2__FP11himo2_classP7himo2_s */
void himo2_control2(himo2_class* i_this, himo2_s* param_2) {
    cXyz local_a8;
    cXyz local_b4;
    f32 f30;
    f32 f29;
    f32 f28;
    f32 f1;
    s16 r27;
    int r26;

    param_2 += 98;

    local_a8.x = 0.0f;
    local_a8.y = 0.0f;
#if VERSION == VERSION_DEMO
    local_a8.z = i_this->m2188 * 15.625f * (REG0_F(1) + 0.0007f);
#else
    if (i_this->m02DC == 0) {
        local_a8.z = i_this->m2188 * 15.625f * (REG8_F(18) + 0.002f);
    } else {
        local_a8.z = i_this->m2188 * 15.625f * (REG0_F(1) + 0.0007f);
    }
#endif
    f28 = 0.0f;
    f29 = f28;
#if VERSION > VERSION_DEMO
    f1 = (REG8_F(17) + 10.0f);
#endif
    int iVar4 = i_this->m02CC + 1;
    for (; iVar4 < 100; iVar4++, param_2--) {
        f30 = (param_2->m10.y - param_2[1].m10.y);
#if VERSION == VERSION_DEMO
        if ((i_this->m02DC > 0) && (i_this->m02DC <= 3))
#else
        if ((i_this->m02DC >= 0) && (i_this->m02DC <= 3))
#endif
        {
#if VERSION > VERSION_DEMO
            if (i_this->m02DC != 0)
#endif
            {
                f1 = (i_this->m2530 * (s32)(99 - iVar4)) * 0.01f;
            }
            f29 = f1 * cM_ssin(i_this->m02D8 * (REG0_S(5) + 700) + iVar4 * (REG0_S(6) + 2000));
            f28 = f1 * cM_scos(i_this->m02D8 * (REG0_S(7) + 500) + iVar4 * (REG0_S(8) + 2000));
        }
        f32 fVar1 = f29 + (param_2->m10.x - param_2[1].m10.x);
        f32 dVar7 = fVar1;
        f32 fVar2 = f28 + (param_2->m10.z - param_2[1].m10.z);
        f32 dVar6 = fVar2;
        r26 = cM_atan2s(fVar1, fVar2);
        dVar6 = std::sqrtf((dVar7 * dVar7) + (dVar6 * dVar6));
        r27 = -cM_atan2s(f30, dVar6);
        param_2[1].m1E = r26;
        param_2[1].m1C = r27;
        cMtx_YrotS(*calc_mtx, r26);
        cMtx_XrotM(*calc_mtx, r27);
        MtxPosition(&local_a8, &local_b4);
        param_2->m10.x = param_2[1].m10.x + local_b4.x;
        param_2->m10.y = param_2[1].m10.y + local_b4.y;
        param_2->m10.z = param_2[1].m10.z + local_b4.z;
    }
}

/* 800EBFEC-800EC1E4       .text himo2_draw__FP11himo2_classP7himo2_s */
void himo2_draw(himo2_class* i_this, himo2_s* param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    int r30;
    cXyz* pcVar6;
    J3DModel* pJVar5;
    himo2_s* phVar4;
    pcVar6 = i_this->m1F30.getPos(0);
    pcVar6 += i_this->m1F6C;
    *pcVar6 = i_this->m02B4;
    i_this->m1F6C++;
    phVar4 = &param_2[i_this->m02CC + 1];
    r30 = i_this->m02CC;
    pcVar6++;
    for (; r30 < 98; r30++, phVar4++) {
        if (r30 == 97) {
            if ((i_this->m02DC == 0) && (i_this->m2188 < REG0_F(3) + 50.0f)) {
                MTXCopy(player->getLeftHandMatrix(), *calc_mtx);
                MtxTrans(10.0f, 0.0f, 0.0f, true);
                cMtx_YrotM(*calc_mtx, 0x4000);
            } else {
                MtxTrans(phVar4->m10.x, phVar4->m10.y, phVar4->m10.z, false);
                cMtx_YrotM(*calc_mtx, phVar4->m1E);
                cMtx_XrotM(*calc_mtx, phVar4->m1C);
                MtxTrans(0.0f, 0.0f, 12.0f, true);
                MtxRotX(M_PI, 1);
                MtxRotZ(M_PI, 1);
            }
            MtxScale(0.2f, 0.2f, 0.2f, true);
            cXyz local_38;
            local_38.x = 0.0f;
            local_38.y = 0.0f;
            local_38.z = 15.0f;
            MtxPosition(&local_38, &i_this->m24CC);
            pJVar5 = i_this->m24B0;
            pJVar5->setBaseTRMtx(*calc_mtx);
            g_env_light.setLightTevColorType(pJVar5, &actor->tevStr);
            mDoExt_modelUpdateDL(pJVar5);
        } else {
            pcVar6->x = phVar4->m10.x;
            pcVar6->y = phVar4->m10.y;
            pcVar6->z = phVar4->m10.z;
            i_this->m1F6C++;
            pcVar6++;
        }
    }
}

#if VERSION == VERSION_DEMO
void himo_e_control(himo2_class* i_this, himo2_s*) {
    /* Nonmatching*/
}

void himo_e_draw(himo2_class* i_this, himo2_s*) {
    /* Nonmatching*/
}
#endif

/* 800EC1E4-800EC300       .text himo_hang_draw__FP11himo2_class */
void himo_hang_draw(himo2_class* i_this) {
    cXyz* pcVar3 = i_this->m1F30.getPos(0);
    pcVar3 += i_this->m1F6C;
    cXyz local_38 = i_this->m02EC[0] - i_this->m2504;
    local_38.x *= 0.25f;
    local_38.y *= 0.25f;
    local_38.z *= 0.25f;
    for (int uVar2 = 0; uVar2 < 5; uVar2++, pcVar3++, i_this->m1F6C++) {
        pcVar3->x = i_this->m2504.x + local_38.x * uVar2;
        pcVar3->y = i_this->m2504.y + local_38.y * uVar2;
        pcVar3->z = i_this->m2504.z + local_38.z * uVar2;
    }
}

/* 800EC300-800EC338       .text himo2_disp__FP11himo2_class */
void himo2_disp(himo2_class* i_this) {
    if (i_this->m02DC < 10) {
        himo2_draw(i_this, &i_this->m0310[0]);
    } else {
        himo_hang_draw(i_this);
#if VERSION == VERSION_DEMO
        himo_e_draw(i_this, i_this->m1120);
#endif
    }
}

/* 800EC338-800ECBE8       .text daHimo2_Draw__FP11himo2_class */
static BOOL daHimo2_Draw(himo2_class* i_this) {
    /* Nonmatching */
    fopAc_ac_c* actor = &i_this->actor;
    cXyz* r19;
    int r6;
    f32 f1;
    f32 f29;
    cXyz sp44;
    cXyz sp38;
    cXyz sp2C;

    if (i_this->m24D9 >= 0 && i_this->m029E == 0 &&
        (i_this->m02DC != 0 || (!daPy_getPlayerActorClass()->checkPlayerNoDraw() && !daPy_getPlayerActorClass()->checkPlayerGuard())))
    {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
        i_this->m1F6C = 0;
        dComIfGd_setListP1();
        if (i_this->m24D8 != 0) {
            spin_draw(i_this);
        }
        if ((i_this->m24D9 == 0) || (i_this->m24D9 >= 3)) {
            himo2_disp(i_this);
        }
        if (i_this->m1F6C > 200) {
            dComIfGd_setList();
            return TRUE;
        } else {
            r19 = i_this->m1F30.getPos(0);
            cXyz local_a10[200];
            for (int i = 0; i < i_this->m1F6C; i++) {
                local_a10[i] = *r19;
                r19++;
            }
            for (int i = 0; i < i_this->m1F6C; i++) {
                r19--;
                *r19 = local_a10[i];
            }
#ifdef __MWERKS__
            i_this->m1F30.update((u16)i_this->m1F6C, rope_scale, (GXColor){200, 0x96, 50, 0xFF}, 0, &actor->tevStr);
#else
            GXColor local_a50 = {200, 0x96, 50, 0xFF};
            i_this->m1F30.update((u16)i_this->m1F6C, rope_scale, local_a50, 0, &actor->tevStr);
#endif
            dComIfGd_set3DlineMat(&i_this->m1F30);
            daPy_py_c* apdVar2 = (daPy_py_c*)dComIfGp_getPlayer(0);
            cMtx_YrotS(*calc_mtx, -apdVar2->shape_angle.y);
            sp44 = i_this->m02EC[1] - i_this->m1F84;
            MtxPosition(&sp44, &sp38);
            sp38.z = sp38.z * (REG0_F(5) + 500.0f);
            if (sp38.z > 16384.0f) {
                sp38.z = 16384.0f;
            }
            if (sp38.z < -16384.0f) {
                sp38.z = -16384.0f;
            }
            cLib_addCalcAngleS2(&i_this->m1F90, sp38.z, 2, REG0_S(2) + 0x800);
            sp38.x *= REG0_F(6) + -200.0f;
            f1 = REG0_F(7) + 4000.0f;
            if (sp38.x > f1) {
                sp38.x = f1;
            }
            if (sp38.x < -f1) {
                sp38.x = -f1;
            }
            cLib_addCalcAngleS2(&i_this->m1F94, sp38.x, 2, REG0_S(2) + 0x800);
            if (sp38.y < REG0_F(8) + -20.0f) {
                cLib_addCalcAngleS2(&i_this->m1F92, -0x8000, 2, 0x1000);
            } else {
                cLib_addCalcAngleS2(&i_this->m1F92, 0, 2, 0x1000);
            }
            i_this->m1F84 = i_this->m02EC[1];
            sp44.z = 0.0f;
            sp44.x = 0.0f;
            f29 = ((REG0_F(10) + i_this->m2188 * (REG0_F(9) + 3.0f)) - 120.0f);
            for (int i = 0; i < 5; i++) {
                r19 = i_this->m1F98.getPos(i);

                if (f29 > (300.0f * (4 - i))) {
                    cLib_addCalc0(&i_this->m1F70[i], 1.0f, (REG0_F(11) + 0.2f));
                } else {
                    cLib_addCalc2(&i_this->m1F70[i], 1.0f, 1.0f, REG0_F(12) + 0.1f);
                }

                sp44.y = (15.0f * i_this->m1F70[i]);
                cMtx_YrotS(*calc_mtx, apdVar2->shape_angle.y);
                r6 = ((1.0f - i_this->m1F70[i]) * (-20000.0f + REG0_F(13)));
                int r4 = REG0_S(0) + i_this->m1F94;
                cMtx_ZrotM(*calc_mtx, i_this->m1F92 + i * (r4 - 2000) + r6);
                cMtx_XrotM(*calc_mtx, i_this->m1F90);
                MtxTrans(0.0f, -sp44.y, 0.0f, true);
                for (int j = 0; j < 32; j++, r19++) {
                    cMtx_XrotM(*calc_mtx, 0x800);
                    MtxPosition(&sp44, r19);
                    *r19 += i_this->m02EC[1];
                }
            }
#if __MWERKS__
            i_this->m1F98.update(0x20, rope_scale, (GXColor){200, 0x96, 50, 0xFF}, 0, &actor->tevStr);
#else
            GXColor local_a54 = {200, 0x96, 50, 0xFF};
            i_this->m1F98.update(0x20, rope_scale, local_a54, 0, &actor->tevStr);
#endif
            dComIfGd_set3DlineMat(&i_this->m1F98);
            r19 = i_this->m1FD8.getPos(0);
            f32 f1_2;
            if (((int)i_this->m2188 & REG0_S(4) + 64) != 0) {
                f1_2 = REG0_F(14) + 15.0f;
            } else {
                f1_2 = 0.0f;
            }
            cLib_addCalc2(&i_this->m1FD4, f1_2, 1.0f, REG0_F(15) + 4.0f);
            sp2C = i_this->m02EC[0] - i_this->m02EC[1];
            s16 r3 = cM_atan2s(sp2C.x, sp2C.z);
            r3 += REG0_S(0) - 0x4000;
            cMtx_YrotS(*calc_mtx, r3);
            sp44.x = 0.0f;
            sp44.y = (REG0_F(7) + -10.0f - i_this->m1FD4);
            sp44.z = (REG0_F(8) + 10.0f + i_this->m1FD4);
            sp44.y *= i_this->m1F70[0];
            sp44.z *= i_this->m1F70[0];
            MtxPosition(&sp44, &sp38);
            sp2C.x *= (1.0f / 15.0f);
            sp2C.y *= (1.0f / 15.0f);
            sp2C.z *= (1.0f / 15.0f);
            int r3_2 = 0;
            for (int i = 0; i < 16; i++, r3_2 += 0x888) {
                s16 r3_2 = i * 0x888;
                f32 fVar1 = cM_ssin(r3_2);
                r19->x = i_this->m02EC[1].x + sp2C.x * i + sp38.x * fVar1;
                r19->y = i_this->m02EC[1].y + sp2C.y * i + sp38.y * fVar1;
                r19->z = i_this->m02EC[1].z + sp2C.z * i + sp38.z * fVar1;
                r19++;
            }
#ifdef __MWERKS__
            i_this->m1FD8.update(16, rope_scale, (GXColor){200, 0x96, 50, 0xFF}, 0, &actor->tevStr);
#else
            GXColor local_a58 = {200, 0x96, 50, 0xFF};
            i_this->m1FD8.update(16, rope_scale, local_a58, 0, &actor->tevStr);
#endif
            dComIfGd_set3DlineMat(&i_this->m1FD8);
            dComIfGd_setList();
        }
    }
    return TRUE;
}

/* 800ECBE8-800ECC54       .text s_a_d_sub__FPvPv */
void* s_a_d_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KUI)) {
        himo2_class* rope = (himo2_class*)param_2;
        rope->m218C[rope->m24AC] = (fopAc_ac_c*)param_1;
        rope->m24AC++;
    }
    return NULL;
}

/* 800ECC54-800ED19C       .text search_target__FP11himo2_class4cXyz */
fopAc_ac_c* search_target(himo2_class* i_this, cXyz param_2) {
    fopAc_ac_c* r28;
    s16 r27;
    s16 r26;
    int r25;
    bool r24;
    f32 f0;
    daPy_py_c* player;
    s16 r4;
    s16 r21;
    f32 f4;
    f32 f31;
    cXyz sp3C;
    cXyz sp30;

    player = daPy_getPlayerActorClass();
    i_this->m24AC = 0;
    for (int i = 0; i < 100; i++) {
        i_this->m218C[i] = NULL;
    }
    fpcM_Search(s_a_d_sub, i_this);
    cMtx_YrotS(*calc_mtx, -player->shape_angle.y);
    f31 = 100.0f;
    r27 = 0x4000 - l_himo2HIO.m08;
    r26 = l_himo2HIO.m08 + 0x4000;
    if (i_this->m24AC != 0) {
        for (r25 = 0; r25 < i_this->m24AC;) {
            r24 = false;
            r28 = i_this->m218C[r25];
            if ((fopAcM_GetParam(r28) & 0xF0) != 0) {
                r24 = true;
            }
            sp3C.x = player->current.pos.x - r28->current.pos.x;
            sp3C.z = player->current.pos.z - r28->current.pos.z;
            s16 r3 = r28->current.angle.y - cM_atan2s(sp3C.x, sp3C.z);
            if (r3 < 0 && !r24) {
                r3 = -r3;
                i_this->m251C = 1;
            } else {
                i_this->m251C = 0;
            }
            if ((r24) || (r3 > r27 && (r3 < r26))) {
                sp3C.x = r28->current.pos.x - player->current.pos.x;
                sp3C.y = r28->current.pos.y - player->current.pos.y;
                sp3C.z = r28->current.pos.z - player->current.pos.z;
                MtxPosition(&sp3C, &sp30);
                if ((sp30.z > 100.0f) && (r24 || (std::fabsf(sp30.y) < l_himo2HIO.m14))) {
                    f4 = std::sqrtf(sp30.x * sp30.x + sp30.z * sp30.z);
                    if (f4 < f31) {
                        cXyz sp24;
                        camera_class* camera = dComIfGp_getCamera(0);
                        sp24.x = param_2.x - camera->mLookat.mEye.x;
                        sp24.y = param_2.y - camera->mLookat.mEye.y;
                        sp24.z = param_2.z - camera->mLookat.mEye.z;
                        cXyz sp18;
                        sp18.x = r28->current.pos.x - camera->mLookat.mEye.x;
                        sp18.y = r28->current.pos.y - camera->mLookat.mEye.y;
                        sp18.z = r28->current.pos.z - camera->mLookat.mEye.z;
                        r21 = (s16)cM_atan2s(sp24.x, sp24.z);
                        r21 = (s16)cM_atan2s(sp18.x, sp18.z) - r21;
                        if (r21 < 0) {
                            r21 = -r21;
                        }
                        f32 f2 = std::sqrtf(SQUARE(sp18.x) + SQUARE(sp18.y) + SQUARE(sp18.z));
                        r4 = (s16)cM_atan2s((r28->scale).z * l_himo2HIO.m10, f2);
                        if (r4 < 0) {
                            r4 = -r4;
                        }
                        if (r21 > (s16)-r4 && r21 < r4) {
                            f32 f2;
                            f2 = std::sqrtf(SQUARE(sp24.x) + SQUARE(sp24.z));
                            s16 r21 = -cM_atan2s(sp24.y, f2);
                            f2 = std::sqrtf(SQUARE(sp18.x) + SQUARE(sp18.z));
                            s16 r3 = -cM_atan2s(sp18.y, f2);
                            if (r24) {
                                r4 = 2000;
                            } else {
                                r4 = l_himo2HIO.m0C;
                            }
                            if ((r21 < r3 + l_himo2HIO.m0E) && ((s16)(r3 - r21) < r4)) {
                                return r28;
                            }
                        }
                    }
                }
            }
            r25++;
            if (r25 == i_this->m24AC) {
                r25 = 0;
                f31 += 100.0f;
                if (r24) {
                    f0 = 2000.0f;
                } else {
                    f0 = l_himo2HIO.m18;
                }
                if (f31 > f0) {
                    return NULL;
                }
            }
        }
    } else {
        return NULL;
    }
    return NULL;
}

/* 800ED19C-800ED2E0       .text setTargetPos__11himo2_classFP4cXyzPfPf */
BOOL himo2_class::setTargetPos(cXyz* param_1, f32* param_2, f32* param_3) {
    /* Nonmatching - pfVar1 != NULL comparison */
    *param_2 = -1.0f;
    *param_3 = -1.0f;
    m2524 = *param_1;
    fopAc_ac_c* pfVar1 = search_target(this, m2524);
    m217C = pfVar1;
    if (pfVar1 != NULL) {
        if ((fopAcM_GetParam(m217C) & 0xF0) != 0) {
            *param_2 = 700.0f;
            *param_3 = 100.0f;
        } else {
            *param_2 = ((fopAcM_GetParam(m217C) >> 0x10) & 0x0F) * 100.0f;
            *param_3 = ((fopAcM_GetParam(m217C) >> 0x14) & 0x0F) * 100.0f;
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
int himo2_bg_check(himo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    u8 flag;
    u32 uVar3;
    int iVar4;
    JPABaseEmitter* pJVar5;
    csXyz local_38;

    if (i_this->m02A2 != 0) {
        return FALSE;
    }

    i_this->m2574.CrrPos(g_dComIfG_gameInfo.play.mBgS);
    if ((i_this->m2574.ChkWallHit() || i_this->m2574.ChkRoofHit()) || i_this->m2574.ChkGroundHit()) {
        i_this->m02DC = 9;
        actor->speedF *= -1.0f;
        i_this->m0308 = 30;
        cBgS_PolyInfo local_24;
        flag = i_this->m2574.GetOnePolyInfo(&local_24);
        JUT_ASSERT(DEMO_SELECT(1534, 1569), flag == NULL);
        uVar3 = dComIfG_Bgsp()->GetMtrlSndId(local_24);
        mDoAud_seStart(JA_SE_LK_SW_HIT_S, &actor->current.pos, uVar3, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        iVar4 = dComIfG_Bgsp()->GetAttributeCode(local_24);
        if ((iVar4 == dBgS_Attr_WOOD_e) || (iVar4 == dBgS_Attr_STONE_e)) {
            local_38.x = actor->current.angle.x;
            local_38.y = actor->current.angle.y;
            local_38.z = actor->current.angle.z;
            local_38.y = actor->current.angle.y + 0x8000;
            mDoAud_seStart(JA_SE_LK_MS_WEP_HIT, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            if (iVar4 == dBgS_Attr_WOOD_e) {
                pJVar5 = dComIfGp_particle_set(
                    dPa_name::ID_AK_JN_ELEMENTKIKUZU00,
                    &actor->current.pos,
                    &local_38,
                    NULL,
                    0xFF,
                    NULL,
                    -1,
                    &actor->tevStr.mColorK0,
                    &actor->tevStr.mColorK0,
                    NULL
                );
                if (pJVar5 != NULL) {
                    pJVar5->mSpread = 0.2f;
                    pJVar5->mVolumeSweep = 0.15f;
                }
            } else {
                local_38.x = local_38.x + 0x4000;
                pJVar5 = dComIfGp_particle_set(dPa_name::ID_AK_JN_ELEMENTHIBANA00, &actor->current.pos, &local_38);
                if (pJVar5 != NULL) {
                    pJVar5->mInitialVelAxis = 15.0f;
                }
                dKy_Sound_set(actor->current.pos, 100, fopAcM_GetID(actor), 5);
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

/* 800ED688-800ED6F4       .text pl_pos_add__FP11himo2_class */
void pl_pos_add(himo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_28 = daPy_getPlayerActorClass()->old.pos - daPy_getPlayerActorClass()->current.pos;
    actor->current.pos += local_28;
}

/* 800ED6F4-800F0038       .text new_himo2_move__FP11himo2_class */
void new_himo2_move(himo2_class* i_this) {
    /* Nonmatching - regalloc, retail-only inlining issues */
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* link;
    bool r27;
    bool r26;
    bool r25;
    fopAc_ac_c* r24;
    dAttention_c* attention; // r23
    u32 r30;
    int r23;
    s16 r22;
    f32 f31;
    f32 f30;
    f32 f28;
    f32 f27;
    f32 f26;
    f32 dVar25;
    f32 fVar26;
    cXyz sp130;
    cXyz sp124;
    cXyz sp118;
    cXyz sp10C;
#if VERSION == VERSION_DEMO
    btd_class* btd;
    dr2_class* dr;
#endif

    daPy_py_c* player;
    camera_class* camera;
    player = (daPy_py_c*)dComIfGp_getPlayer(0);
    camera = (camera_class*)dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    cXyz sp100 = i_this->m02EC[0];
    cXyz spF4 = i_this->m02EC[1];
    cXyz spE8;
    f32 f3 = actor->current.pos.x - sp100.x;
    f32 f4 = (actor->current.pos.y - sp100.y);
    f32 f0 = actor->current.pos.z - sp100.z;
    i_this->m2188 = std::sqrtf(SQUARE(f3) + SQUARE(f4) + SQUARE(f0));
    if (i_this->m0308 != 0) {
        i_this->m0308--;
    }
    if (i_this->m02A2 != 0) {
        i_this->m02A2--;
    }
    if (i_this->m029C != 0) {
        i_this->m029C--;
    }
    if (i_this->m029E != 0) {
        i_this->m029E--;
    }
    if (i_this->m02A0 != 0) {
        i_this->m02A0--;
    }
    attention = &dComIfGp_getAttention();
    r30 = attention->Lockon() == false;
    if (r30) {
        rope_scale = l_himo2HIO.m20;
    } else {
        rope_scale = l_himo2HIO.m1C;
        i_this->m029E = 0;
    }
    r27 = false;
    r26 = false;
    r25 = false;
    r24 = NULL;
    if (attention->LockonTruth()) {
        r24 = attention->LockonTarget(0);
        if (r24) {
            i_this->m2524 = r24->eyePos;
            r27 = true;
        }
    }
    if ((i_this->m02DC != 0) && (i_this->m24D9 < 3)) {
        link = (daPy_py_c*)daPy_getPlayerLinkActorClass();
        if ((link->checkRopeForceEnd()) && (!actor->eventInfo.checkCommandDemoAccrpt())) {
            i_this->m24D9 = 0;
            i_this->m24D8 = 0;
            fopAcM_SetParam(actor, 0);
#if VERSION == VERSION_DEMO
            i_this->m02DC = 9;
            i_this->m0308 = 30;
#else
            i_this->m0308 = 0x1E;
            if (i_this->m02DC == 11) {
                fopAcM_seStart(actor, JA_SE_LK_ROPE_UNCOIL, 0);
                i_this->m02DC = 0;
            } else {
                i_this->m02DC = 9;
            }
            if ((i_this->m217C != NULL) && (fopAcM_GetName(i_this->m217C) == PROC_KUI)) {
                i_this->m217C->health = 0;
            }
#endif
            i_this->m217C = NULL;
        }
    }
    
    switch (i_this->m02DC) {
    case 0: {
        actor->speedF = 0.0f;
        if ((r30 == 0) && player->checkRopeReadyAnime()) {
            cMtx_YrotS(*calc_mtx, player->shape_angle.y);
            cMtx_ZrotM(*calc_mtx, REG0_S(2) + -12000);
            cMtx_YrotM(*calc_mtx, i_this->m02D8 * (REG0_S(3) + 0x2000));
            sp130.x = 0.0f;
            sp130.y = 0.0f;
            sp130.z = REG0_F(11) + 70.0f;
            MtxPosition(&sp130, &actor->current.pos);
            actor->current.pos += sp100;
            i_this->m02CC = REG0_S(5) + 0x60;
            if ((i_this->m02D8 & 7) == 0) {
                fopAcM_seStart(actor, JA_SE_LK_ROPE_COIL_1, 0);
            }
        } else {
            r23 = (i_this->m2188 * (REG0_F(3) + 0.060000002f));
            i_this->m02CC = 97 - r23;
            cLib_addCalc2(&actor->current.pos.x, sp100.x, 1.0f, i_this->m2500 * 200.0f);
            cLib_addCalc2(&actor->current.pos.y, sp100.y, 1.0f, i_this->m2500 * 200.0f);
            cLib_addCalc2(&actor->current.pos.z, sp100.z, 1.0f, i_this->m2500 * 200.0f);
            cLib_addCalc2(&i_this->m2500, 1.0f, 1.0f, 0.005f);
            sp130 = actor->current.pos - sp100;
            if (sp130.abs() > 5.0f) {
                fopAcM_seStart(player, JA_SE_LK_ROPE_UNWIND, 0);
            }
        }
        if (fopAcM_GetParam(actor) == 1) {
            i_this->m2500 = 0.0f;
            i_this->m02E4 = 0.0f;
            i_this->m0308 = REG0_S(2) + 0x28;
            i_this->m029E = 0;
            i_this->m02A0 = REG0_S(9) + 10;
            i_this->m02A2 = 3;
            camera = (camera_class*)dComIfGp_getCamera(0);
            f28 = i_this->m2524.x - camera->mLookat.mEye.x;
            f27 = i_this->m2524.y - camera->mLookat.mEye.y;
            f32 f26 = i_this->m2524.z - camera->mLookat.mEye.z;
            sp130.z = REG0_F(15) * 100.0f + 1000.0f;
            f30 = SQUARE(f26);
            f31 = SQUARE(f28);
            if (std::sqrtf(f31 + SQUARE(f27) + f30) > sp130.z) {
                int r24 = cM_atan2s(f28, f26);
                r22 = -cM_atan2s(f27, std::sqrtf(f31 + f30));
                cMtx_YrotS(*calc_mtx, r24);
                cMtx_XrotM(*calc_mtx, r22);
                sp130.x = 0.0f;
                sp130.y = 0.0f;
                MtxPosition(&sp130, &sp124);
                i_this->m2524.x = camera->mLookat.mEye.x + sp124.x;
                i_this->m2524.y = camera->mLookat.mEye.y + sp124.y;
                i_this->m2524.z = camera->mLookat.mEye.z + sp124.z;
            }
            himo2_s* phVar18 = i_this->m0310;
            if (r30 != 0) {
                i_this->m02DC = 2;
                i_this->m2530 = 4.0f;
                i_this->m02CC = REG0_S(6) + 0x5A;
                actor->current.pos = sp100;
                for (int iVar8 = 0; iVar8 < 100; iVar8++) {
                    phVar18->m10 = sp100;
                    phVar18++;
                }
            } else {
                i_this->m02DC = 1;
                i_this->m0308 = REG0_S(4) + 2;
                i_this->m2530 = 4.0f;
                i_this->m02CC = REG0_S(6) + 0x5A;
                actor->current.pos = sp100;
                for (int iVar8 = 0; iVar8 < 100; iVar8++) {
                    phVar18->m10 = sp100;
                    phVar18++;
                }
            }
        }
        break;
    }
    case 1: {
        cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
        cMtx_ZrotM(*calc_mtx, REG0_S(2) + -12000);
        cMtx_YrotM(*calc_mtx, i_this->m02D8 * (REG0_S(3) + 0x2000));
        sp130.x = 0.0f;
        sp130.y = 0.0f;
        sp130.z = REG0_F(11) + 70.0f;
        MtxPosition(&sp130, &actor->current.pos);
        actor->current.pos += sp100;
        i_this->m02CC = REG0_S(5) + 0x60;
        if ((i_this->m02D8 & 7) == 0) {
            fopAcM_seStart(actor, JA_SE_LK_ROPE_SWING_ROUND, 0);
        }
        s16 r4 = i_this->m02D8 * (REG0_S(3) + 0x2000);
        if ((r4 >= (s16)(REG0_S(7) + -20000)) && (r4 < (s16)(REG0_S(7) + -0x2e20))) {
            r25 = true;
        }
        if ((i_this->m0308 == 0) && (r25)) {
            i_this->m02DC = 3;
            if (r27) {
                i_this->m0308 = REG0_S(4) + 70;
                i_this->m217C = r24;
                fpc_ProcID fVar10 = fopAcM_GetID(r24);
                i_this->m2180 = fVar10;
            } else {
                i_this->m0308 = REG0_S(2) + 20;
                i_this->m2180 = fpcM_ERROR_PROCESS_ID_e;
            }
            sp130 = i_this->m2524 - actor->current.pos;
            actor->current.angle.y = cM_atan2s(sp130.x, sp130.z);
            f32 f2 = std::sqrtf(sp130.x * sp130.x + sp130.z * sp130.z);
            actor->current.angle.x = -cM_atan2s(sp130.y, f2);
            fopAcM_seStart(actor, JA_SE_LK_ROPE_LAUNCH, 0);
        }
        break;
    }
    case 2: {
        i_this->m02CC = REG0_S(0);
        if (i_this->m217C != NULL) {
            if (((fopAcM_GetParam(i_this->m217C) & 0xF0) != 0) || ((fopAcM_GetParam(i_this->m217C) & 0x0F) == 3)) {
                sp10C = i_this->m217C->current.pos;
            } else {
                sp10C = i_this->m2524;
            }
            cMtx_YrotS(*calc_mtx, actor->current.angle.y);
            cMtx_XrotM(*calc_mtx, actor->current.angle.x);
            sp130.y = 0.0f;
            sp130.x = 0.0f;
            sp130.z = REG0_F(14) * 100.0f + 100.0f;
            MtxPosition(&sp130, &sp124);
            sp10C.x = sp10C.x + sp124.x;
            sp10C.y = sp10C.y + sp124.y;
            sp10C.z = sp10C.z + sp124.z;
        } else {
            sp10C = i_this->m2524;
        }
        dVar25 = (sp10C.x - actor->current.pos.x);
        f30 = (sp10C.y - actor->current.pos.y);
        f28 = (sp10C.z - actor->current.pos.z);
        f31 = (f28 * f28);
        f27 = (dVar25 * dVar25);
        f32 f26 = std::sqrtf(f31 + (f27 + (f30 * f30)));
        f27 = std::sqrtf(f27 + f31);
        r23 = (s16)(f26 * (REG0_F(3) + -5.0f));
        if (r23 < (s16)(REG0_S(2) + -3000)) {
            r23 = REG0_S(2) + -3000;
        }
        if ((i_this->m217C != NULL) || (f26 > (actor->speedF * 10.0f))) {
            actor->current.angle.y = cM_atan2s(dVar25, f28);
            actor->current.angle.x = -cM_atan2s(f30, f27);
        }
        actor->speedF = 20.0f;
        cMtx_YrotS(*calc_mtx, actor->current.angle.y);
        cMtx_XrotM(*calc_mtx, actor->current.angle.x + r23);
        sp130.y = 0.0f;
        sp130.x = 0.0f;
        sp130.z = actor->speedF;
        MtxPosition(&sp130, &actor->speed);
        actor->current.pos += actor->speed;
        pl_pos_add(i_this);
        if (i_this->m217C != NULL) {
            if ((f30 < (actor->speedF * 10.0f)) || (i_this->m0308 == 0)) {
                i_this->m02DC = 10;
                i_this->m24D9 = 0xFF;
                i_this->m24D8 = 1;
#if VERSION > VERSION_DEMO
                if (btd != 0) {
                    fopAcM_OffStatus(&btd->actor, fopAcStts_UNK4000_e);
                }
#endif
                break;
            }
            if ((i_this->m02A2 == 0) && i_this->m2050.ChkAtHit()) {
                i_this->m02DC = 9;
                actor->speedF *= -1.0f;
                i_this->m0308 = 0x28;
                i_this->m217C = NULL;
                break;
            }
        } else if (!himo2_bg_check(i_this)) {
            if ((i_this->m02A2 == 0) && i_this->m2050.ChkAtHit()) {
                i_this->m02DC = 9;
                actor->speedF *= -1.0f;
                i_this->m0308 = 0x28;
                break;
            }
            if (i_this->m0308 == 0) {
                i_this->m02DC = 8;
                i_this->m0308 = 50;
                fopAcM_seStart(actor, JA_SE_LK_ROPE_MAXLENGTH, 0);
                break;
            }
        } else {
            break;
        }
        if ((CPad_CHECK_TRIG_X(0) || CPad_CHECK_TRIG_Y(0) || CPad_CHECK_TRIG_Z(0)) && (i_this->m02A0 == 0)) {
            i_this->m02DC = 8;
            i_this->m0308 = 0x28;
            fopAcM_seStart(actor, JA_SE_LK_ROPE_MAXLENGTH, 0);
            i_this->m217C = NULL;
        }
        break;
    }
    case 3: {
        i_this->m02CC = REG0_S(0);
        // fakematch - why is this not getting inlined?
        // r24 = fopAcM_SearchByID(i_this->m2180);
        fpc_ProcID sp08 = i_this->m2180;
        r24 = (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &sp08);
        if (r24 != NULL) {
            sp130 = r24->eyePos - actor->current.pos;
            cLib_addCalcAngleS2(&actor->current.angle.y, cM_atan2s(sp130.x, sp130.z), 2, REG0_S(1) + 0x800);
            f32 f2 = std::sqrtf(sp130.x * sp130.x + sp130.z * sp130.z);
            cLib_addCalcAngleS2(&actor->current.angle.x, -cM_atan2s(sp130.y, f2), 2, REG0_S(1) + 0x800);
            if (sp130.abs() < (REG0_F(3) + 50.0f)) {
                r26 = true;
            }
        }
        actor->speedF = REG0_F(14) + 30.0f;
        cMtx_YrotS(*calc_mtx, actor->current.angle.y);
        cMtx_XrotM(*calc_mtx, actor->current.angle.x);
        sp130.y = 0.0f;
        sp130.x = 0.0f;
        sp130.z = actor->speedF;
        MtxPosition(&sp130, &actor->speed);
        actor->current.pos += actor->speed;
        pl_pos_add(i_this);
        r23 = himo2_bg_check(i_this);
        if (r23 != 0) {
            r26 = true;
            i_this->m2500 = 0.1f;
        }
        if ((i_this->m02A2 == 0) && i_this->m2050.ChkAtHit()) {
            r26 = true;
            i_this->m2500 = 0.1f;
        }
        if (i_this->m0308 == 0) {
            r26 = true;
            i_this->m2500 = 0.02f;
        }
        if (((CPad_CHECK_TRIG_X(0) || CPad_CHECK_TRIG_Y(0) || CPad_CHECK_TRIG_Z(0)) && (i_this->m02A0 == 0)) || (r26)) {
            i_this->m02DC = 5;
        }
        break;
    }
    case 4: {
        // fakematch - why is this not getting inlined?
        // r24 = fopAcM_SearchByID(i_this->m2180);
        fpc_ProcID sp08 = i_this->m2180;
        r24 = (fopAc_ac_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeByID, &sp08);
        if (r24 == NULL) {
            i_this->m02DC = 5;
        } else {
            cMtx_YrotS(*calc_mtx, (i_this->m02D8 << 13));
            sp130.x = 0.0f;
            sp130.y = 0.0f;
            sp130.z = i_this->m2184;
            MtxPosition(&sp130, &sp124);
            actor->current.pos = r24->eyePos + sp124;
            cLib_addCalc0(&i_this->m2184, 1.0f, 5.0f);
            if (i_this->m2184 < 0.1f) {
                fopAcM_SetParam(actor, 0);
            }
            r23 = (i_this->m2188 * (REG0_F(5) + 0.060000002f));
            r23 = 97 - r23;
            if ((r23 < i_this->m02CC) || (i_this->m2184 < 0.1f)) {
                i_this->m02CC = r23;
            }
            if ((CPad_CHECK_TRIG_X(0) || CPad_CHECK_TRIG_Y(0)) || CPad_CHECK_TRIG_Z(0)) {
                i_this->m02DC = 5;
                if (fopAcM_GetName(r24) == PROC_BK) {
                    bk_class* bk = (bk_class*)r24;
                    bk->dr.mAction = 0;
                    bk->dr.mMode = 0;
                }
            }
        }
        i_this->m02E4 = -5.0f;
        break;
    }
    case 5: {
        i_this->m02CC = REG0_S(0);
        cLib_addCalc2(&actor->current.pos.x, sp100.x, 1.0f, (REG0_F(15) + 400.0f) * i_this->m2500);
        cLib_addCalc2(&actor->current.pos.y, sp100.y, 1.0f, (REG0_F(15) + 400.0f) * i_this->m2500);
        cLib_addCalc2(&actor->current.pos.z, sp100.z, 1.0f, (REG0_F(15) + 400.0f) * i_this->m2500);
        cLib_addCalc2(&i_this->m2500, 1.0f, 1.0f, 0.01f);
        pl_pos_add(i_this);
        sp130 = actor->current.pos - sp100;
        r23 = -1;
        if (sp130.abs() > 5.0f) {
            fopAcM_seStart(player, JA_SE_LK_ROPE_UNWIND, 0);
        } else {
            fopAcM_SetParam(actor, 0);
            fopAcM_seStart(actor, JA_SE_LK_ROPE_UNCOIL, 0);
            i_this->m02DC = 0;
            i_this->m217C = NULL;
            i_this->m24D8 = 0;
        }
        break;
    }
    case 8: {
        cLib_addCalc2(&actor->speedF, -50.0f, 1.0f, 6.0f);
    }
    case 9: {
        cLib_addCalc2(&actor->current.pos.x, sp100.x, 1.0f, (REG0_F(15) + 400.0f) * i_this->m2500);
        cLib_addCalc2(&actor->current.pos.y, sp100.y, 1.0f, (REG0_F(15) + 400.0f) * i_this->m2500);
        cLib_addCalc2(&actor->current.pos.z, sp100.z, 1.0f, (REG0_F(15) + 400.0f) * i_this->m2500);
        cLib_addCalc2(&i_this->m2500, 1.0f, 1.0f, 0.01f);
        pl_pos_add(i_this);
        sp130 = actor->current.pos - sp100;
        r23 = -1;
        if (sp130.abs() > 5.0f) {
            fopAcM_seStart(player, JA_SE_LK_ROPE_UNWIND, 0);
        } else {
            fopAcM_SetParam(actor, 0);
            i_this->m02DC = 0;
            actor->current.pos = sp100;
            i_this->m029E = REG0_S(6) + 20;
        }
        i_this->m02CC = REG0_S(0);
        break;
    }
    case 10: {
        r23 = (i_this->m2188 * (REG0_F(1) + 0.060000002f));
        i_this->m02CC = 100 - r23;
        actor->current.pos = i_this->m2504;
        cLib_addCalc2(&i_this->m02E4, -6.25f, 1.0f, 0.375f);
        if (fopAcM_GetParam(actor) == 3) {
            i_this->m02DC = 11;
            if ((fopAcM_GetParam(i_this->m217C) & 0xF0) != 0) {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0540);
            } else {
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0580);
            }
        }
        i_this->m217C->health = 1;
        goto label_1260;
    }
    case 11: {
        actor->current.pos = i_this->m2504;
        r23 = (i_this->m2188 * (REG0_F(2) + 0.060000002f));
        i_this->m02CC = 100 - r23;
        i_this->m217C->health = 3;
    label_1260:
        if (fopAcM_GetParam(actor) == 4) {
            fopAcM_SetParam(actor, 0);
            fopAcM_seStart(actor, JA_SE_LK_ROPE_UNCOIL, 0);
            i_this->m02DC = 0;
            i_this->m217C->health = 0;
            i_this->m217C = NULL;
            if (i_this->m24D9 != 0) {
                i_this->m24D9 = 6;
                i_this->m029C = 120;
            }
            i_this->m24D8 = 0;
        }
    }
    }
    
#if VERSION == VERSION_DEMO
    btd = (btd_class*)fpcM_Search(b_a_sub, i_this);
    dr = (dr2_class*)fpcM_Search(dr_a_sub, i_this);
#endif
    
    f26 = 0.0f;
    
    switch (i_this->m24D9) {
    case -1: {
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_NOPARTNER_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            break;
        }
        i_this->m24F4 = REG0_F(12) + 50.0f;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->m24D9 = 2;
        i_this->m24B4 = -400.0f;
        i_this->m24BC = 0;
        i_this->m24C8 = 0;
        i_this->m24C4 = 0.0f;
        i_this->m24CA = 0;
        if (i_this->m251C != 0) {
            i_this->m2510 = i_this->m217C->current.angle.y + -0x4000;
        } else {
            i_this->m2510 = i_this->m217C->current.angle.y + 0x4000;
        }
        if ((fopAcM_GetParam(i_this->m217C) & 0xF0) != 0) {
            i_this->m24B8 = REG0_F(6) + -90.0f;
            i_this->m2514 = -1.0f;
            i_this->m2518 = REG0_F(7) + 1.0f;
            i_this->m24FC = REG0_F(16) + 3.5f;
        } else {
            i_this->m24B8 = 0.0f;
            switch (l_himo2HIO.m06) {
            case 0:
                if (cM_rndF(1.0f) < 0.5f) {
                    i_this->m2514 = 1.0f;
                } else {
                    i_this->m2514 = -1.0f;
                }
                if (cM_rndF(1.0f) < 0.5f) {
                    i_this->m2518 = 1.0f;
                } else {
                    i_this->m2518 = -1.0f;
                }
                break;
            case 1:
                i_this->m2514 = 1.0f;
                i_this->m2518 = 1.0f;
                break;
            case 2:
                i_this->m2514 = 1.0f;
                i_this->m2518 = -1.0f;
                break;
            case 3:
                i_this->m2514 = -1.0f;
                i_this->m2518 = 1.0f;
                break;
            case 4:
                i_this->m2514 = -1.0f;
                i_this->m2518 = -1.0f;
                break;
            }
            if (i_this->m2518 < 0.0f) {
                i_this->m24FC = REG0_F(6) + 3.0f;
            } else {
                i_this->m24FC = 1.0f;
            }
        }
        i_this->m24E8 = i_this->m217C->current.pos;
    }
    case 2: {
        cLib_addCalc0(&i_this->m24B8, 1.0f, (REG0_F(7) + 3.0f));
        cLib_addCalc2(&i_this->m24B4, -144.0f, 1.0f, 10.0f);
        if (i_this->m24B4 > -145.0f) {
            if (i_this->m24BC < 400) {
                fVar26 = 20.0f - (i_this->m217C->scale.y - 1.0f) * 17.0f;
                if (fVar26 < 0.5f) {
                    fVar26 = 0.5f;
                }
                int r3 = (i_this->m24C4 / fVar26);
                int r5 = r3 + 1;
                i_this->m24C0 = i_this->m24BC;
                i_this->m24BC += r5;
                i_this->m24C4 += 1.0f;
                if (i_this->m24C0 == 0) {
                    fopAcM_seStart(actor, JA_SE_LK_ROPE_COIL_1, 0);
                } else if ((i_this->m24C0 >= 13) && (i_this->m24BC <= r5 + 13)) {
                    fopAcM_seStart(actor, JA_SE_LK_ROPE_COIL_2, 0);
                } else if ((i_this->m24C0 >= 26) && (i_this->m24BC <= r5 + 26)) {
                    fopAcM_seStart(actor, JA_SE_LK_ROPE_COIL_3, 0);
                } else if ((i_this->m24C0 >= 39) && (i_this->m24BC <= r5 + 39)) {
                    fopAcM_seStart(actor, JA_SE_LK_ROPE_COIL_3, 0);
                }
            }
            s16 r4;
#if VERSION == VERSION_DEMO
            r4 = (4000.0f - (i_this->m217C->scale.y - 1.0f) * 2000.0f);
#else
            f32 f3;
            if ((fopAcM_GetParam(i_this->m217C) & 0x0F) == 3) {
                f3 = (i_this->m217C->scale.y - 0.14f) + REG8_F(7);
            } else {
                f3 = i_this->m217C->scale.y;
            }
            r4 = (4000.0f - (f3 - 1.0f) * 2000.0f);
#endif
            cLib_addCalcAngleS2(&i_this->m24C8, r4, 1, (r4 / 8));
            if (i_this->m24BC > 49) {
                if (i_this->m24CA == 9000) {
                    i_this->m24CA = 0x238c;
                } else if (i_this->m24CA < 9000) {
                    i_this->m24CA = 9000;
                    if ((fopAcM_GetParam(i_this->m217C) & 0xF0) != 0) {
                        fopAcM_seStart(actor, JA_SE_LK_ROPE_HOOK_BODY, 0);
                    } else {
                        fopAcM_seStart(actor, JA_SE_LK_ROPE_HOOK_WOOD, 0);
                    }
                }
            }
        }
        cLib_addCalc2(&i_this->m24E8.x, i_this->m217C->current.pos.x, 0.3f, 100.0f);
        cLib_addCalc2(&i_this->m24E8.y, i_this->m217C->current.pos.y, 0.3f, 100.0f);
        cLib_addCalc2(&i_this->m24E8.z, i_this->m217C->current.pos.z, 0.3f, 100.0f);
        i_this->m24DC = i_this->m217C->current.pos;
        cMtx_YrotS(*calc_mtx, i_this->m2510);
        sp130.x = (REG0_F(5) * 10.0f + 50.0f) * i_this->m2514;
        sp130.y = (REG0_F(4) * 10.0f - 200.0f) + 140.0f;
        sp130.z = ((REG0_F(3) * 10.0f + 200.f) - 80.0f) * i_this->m2518;
        MtxPosition(&sp130, &sp124);
        i_this->m24DC.x = i_this->m24DC.x + sp124.x * i_this->m24FC;
        i_this->m24DC.y = i_this->m24DC.y + sp124.y * i_this->m24FC;
        i_this->m24DC.z = i_this->m24DC.z + sp124.z * i_this->m24FC;
        if ((fopAcM_GetParam(i_this->m217C) & 0xF0) != 0) {
            cLib_addCalc2(&i_this->m24FC, REG0_F(6) + 1.8f, REG0_F(4) + 0.2f, REG0_F(5) + 0.1f);
        } else {
            cLib_addCalc2(&i_this->m24FC, 1.0f, REG0_F(4) + 0.2f, REG0_F(5) + 0.1f);
        }
        break;
    }
    case 3: {
        i_this->m217C->health = 2;
        cMtx_YrotS(*calc_mtx, i_this->m217C->current.angle.y);
        sp130.x = ((REG0_F(11) + 2000.0f) - 800.0f) - 300.0f;
        sp130.y = i_this->m217C->home.pos.y + REG0_F(12) + 2000.0f;
        sp130.z = REG0_F(13) + 1000.0f;
        MtxPosition(&sp130, &sp124);
        cLib_addCalc2(&i_this->m24DC.x, sp124.x, 0.3f, 200.0f);
        cLib_addCalc2(&i_this->m24DC.y, sp124.y, 0.3f, 200.0f);
        cLib_addCalc2(&i_this->m24DC.z, sp124.z, 0.3f, 200.0f);
        cLib_addCalc2(&i_this->m24E8.y, i_this->m217C->home.pos.y + 2500.0f + REG0_F(14), 0.3f, 100.0f);
        cLib_addCalc2(&i_this->m24F4, REG0_F(13) + 80.0f, 1.0f, 2.0f);
        if (i_this->m029C < 30) {
#if VERSION == VERSION_DEMO
            mDoGph_gInf_c::setBlureRate(180 + REG0_S(4));
            mDoGph_gInf_c::onBlure();
#else
            btd->m6E15 = 0xB4;
#endif
        }
        if (i_this->m029C == 30) {
            fopAcM_seStartCurrent((fopAc_ac_c*)dr, JA_SE_CM_BTD_ROPE_SET, 0);
        }
        if (((dComIfGp_getStartStageName()[0] != 'X') && (i_this->m029C <= 1)) && (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0420))) {
            dKy_custom_colset(0, 4, 1.0f);
        }
        if ((i_this->m029C != 0) || (REG0_S(8) != 0)) {
            break;
        }
#if VERSION == VERSION_DEMO
        mDoGph_gInf_c::offBlure();
#else
        btd->m6E15 = 1;
#endif
        i_this->m24D9 = 4;
        if ((dComIfGp_getStartStageName()[0] == 'X') || (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0420))) {
            i_this->m029C = 0;
        } else {
            dComIfGs_onEventBit(dSv_event_flag_c::UNK_0420);
            i_this->m029C = REG0_S(2) + 62;
            daYkgr_c::hide();
        }
        i_this->m02E0 = 0;
        i_this->m217C->health = 0;
#if VERSION > VERSION_DEMO
        if (btd != 0) {
            fopAcM_OnStatus(&btd->actor, 0x4000);
        }
#endif
    }
    case 4: {
        dKy_custom_colset(0, 4, 1.0f);
        if (i_this->m029C == (s16)(REG0_S(2) + 57)) {
            mDoAud_seStart(JA_SE_CV_DRG_SET_ROPE, NULL, 0, 0);
        }
        if (i_this->m029C <= 1) {
            dKy_custom_colset(0, 4, 0.0f);
        }
        if ((i_this->m029C == 0) && (REG0_S(8) == 0)) {
            dr->unk_50C = 0;
            dKy_custom_colset(0, 4, 0.0f);
            i_this->m24D9 = 5;
            i_this->m029C = 50;
            i_this->m02E0 = 0;
            fopAcM_SetParam(actor, 2);
            dComIfGp_event_reset();
#if VERSION > VERSION_DEMO
            i_this->m02A4 = 20;
#endif
            i_this->m2510 = fopAcM_searchPlayerAngleY(actor) + 0x8000;
            i_this->m2512 = i_this->m2510;
            i_this->m24F4 = 65.0f;
            i_this->m24F8 = 65.0f;
            cMtx_YrotS(*calc_mtx, i_this->m2510);
            sp130.x = REG0_F(7) + 100.0f + 200.0f;
            sp130.y = player->current.pos.y + 700.0f + REG0_F(8);
            sp130.z = REG0_F(9) + -500.0f;
            MtxPosition(&sp130, &i_this->m24DC);
            i_this->m24DC.x = i_this->m24DC.x + player->current.pos.x * (REG0_F(15) + 0.55f);
            i_this->m24DC.z = i_this->m24DC.z + player->current.pos.z * (REG0_F(15) + 0.55f);
            i_this->m24E8 = player->current.pos;
            i_this->m24E8.y = i_this->m24E8.y - 50.0f;
            daYkgr_c::show();
        } else {
            i_this->m24F4 = REG0_F(12) + 50.0f;
            dr->unk_50C = 1;
            i_this->m24DC.x = ((REG0_F(14) + 3000.0f) - 10000.0f) + 2000.0f;
            i_this->m24DC.y = REG0_F(15) + 10000.0f + 2000.0f + 9720.0f;
            i_this->m24DC.z = (REG0_F(16) + 6000.0f) - 2000.0f;
            i_this->m24E8.x = REG0_F(17);
            i_this->m24E8.y = (REG0_F(18) + 10000.0f + 2000.0f + 9720.0f) - 300.0f;
            i_this->m24E8.z = REG0_F(19);
        }
        break;
    }
    case 5: {
        if (i_this->m029C == 0) {
            if (i_this->m02E0 == 0) {
                mDoAud_seStart(JA_SE_CV_DRG_ROCKFALL_1, NULL, 0, 0);
            } else if (i_this->m02E0 == 1) {
                mDoAud_seStart(JA_SE_CV_DRG_ROCKFALL_1_2, NULL, 0, 0);
            } else if (i_this->m02E0 >= 2) {
                mDoAud_seStart(JA_SE_CV_DRG_ROCKFALL_1_3, NULL, 0, 0);
                i_this->m02E0 = 2;
            }
            i_this->m02E0++;
            i_this->m029C = 50;
        }
        f26 = g_mDoCPd_cpadInfo[0].mCStickPosY;
    label_1d50:
        f32 f2 = g_mDoCPd_cpadInfo[0].mCStickPosX;
        i_this->m2512 += (s16)(f2 * (REG0_F(6) + 1000.0f));
        cLib_addCalcAngleS2(&i_this->m2510, i_this->m2512, 4, 0x1000);
        if (f26 <= -0.1f) {
            cLib_addCalc2(&i_this->m24F8, REG0_F(7) + 70.0f, 1.0f, std::fabsf(f26) * 3.0f);
        } else if (f26 >= 0.1f) {
            cLib_addCalc2(&i_this->m24F8, REG0_F(8) + 20.0f, 1.0f, std::fabsf(f26) * 3.0f);
        }
        cLib_addCalc2(&i_this->m24F4, i_this->m24F8, 0.1f, 10.0f);
        cMtx_YrotS(*calc_mtx, i_this->m2510);
        sp130.x = REG0_F(7) + 100.0f + 200.0f;
        sp130.y = player->current.pos.y + 700.0f + REG0_F(8);
        sp130.z = REG0_F(9) + -500.0f;
        MtxPosition(&sp130, &i_this->m24DC);
        i_this->m24DC.x = i_this->m24DC.x + player->current.pos.x * (REG0_F(15) + 0.55f);
        i_this->m24DC.z = i_this->m24DC.z + player->current.pos.z * (REG0_F(15) + 0.55f);
        cLib_addCalc2(&i_this->m24E8.x, player->current.pos.x, 0.3f, 100.0f);
        cLib_addCalc2(&i_this->m24E8.y, (player->current.pos.y - 50.0f) + REG0_F(10), 0.3f, 100.0f);
        cLib_addCalc2(&i_this->m24E8.z, player->current.pos.z, 0.3f, 100.0f);
#if VERSION > VERSION_DEMO
        if ((i_this->m02A4 == 0) && (!player->checkPlayerFly())) {
            camera->mCamera.Start();
            i_this->m24D9 = 0;
            i_this->m24D8 = 0;
            fopAcM_SetParam(actor, 0);
            i_this->m02DC = 0;
            i_this->m217C = NULL;
            dComIfGp_event_reset();
        }
#endif
        break;
    }
    case 6: {
        if (!player->getRopeJumpLand() && (i_this->m029C != 0)) {
            if (!actor->eventInfo.checkCommandDemoAccrpt()) {
                fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            }
            dr->unk_4CA = 0x5A;
            cLib_addCalc2(&i_this->m24F8, REG0_F(8) + 20.0f, 1.0f, REG0_F(9) + 2.0f);
#if VERSION == VERSION_DEMO
            f26 = 0.0f;
#endif
            goto label_1d50;
        }
        i_this->m24D9 = 7;
        i_this->m029C = 10;
    }
    case 7: {
        if (i_this->m029C != 0) {
            break;
        }
        if (dr->unk_4BA >= 10) {
            i_this->m24D9 = 0;
            camera->mCamera.Reset(i_this->m24E8, i_this->m24DC);
            camera->mCamera.Start();
            camera->mCamera.SetTrimSize(0);
            dComIfGp_event_reset();
            break;
        }
        i_this->m24F4 = REG0_F(12) + 50.0f;
        fopAcM_OnStatus(&btd->actor, 0x4000);
        i_this->m24D9 = 8;
        i_this->m24E8.x = 0.0f;
        i_this->m24E8.y = REG0_F(5) * 0.1f + 3000.0f;
        i_this->m24E8.z = REG0_F(6) * 0.1f;
        cMtx_YrotS(*calc_mtx, btd->actor.current.angle.y);
        sp130.x = REG0_F(7) * 0.1f;
        sp130.y = REG0_F(8) * 0.1f + 1000.0f;
        sp130.z = REG0_F(9) * 0.1f + 1400.0f;
        MtxPosition(&sp130, &i_this->m24DC);
        i_this->m24F4 = REG0_F(13) + 80.0f;
        i_this->m029C = 210;
        dBgS_LinChk lin_chk;
        lin_chk.Set(&i_this->m24E8, &i_this->m24DC, actor);
        if (dComIfG_Bgsp()->LineCross(&lin_chk)) {
            i_this->m24DC = lin_chk.GetCross();
        }
    }
    case 8: {
        dr->unk_40A = 3;
        if (i_this->m029C == 200) {
            mDoAud_seStart(JA_SE_CV_DRG_ROCKFALL_2, NULL, 0, 0);
        }
        if (i_this->m029C == 170) {
            fopAcM_seStartCurrent((fopAc_ac_c*)dr, JA_SE_CM_BTD_BEF_ROCK_FALL, 0);
        }
        if (i_this->m029C > 150) {
            fVar26 = 2000.0f;
        } else {
            fVar26 = 100.0f;
        }
        cLib_addCalc2(&dr->unk_414, fVar26, 0.5f, 100.0f);
        if (i_this->m029C <= 120) {
            cLib_addCalc2(&i_this->m24E8.y, REG0_F(5) * 0.1f + 650.0f, 1.0f, 100.0f);
            cLib_addCalc2(&i_this->m24DC.y, 0.0f, 0.5f, 100.0f);
            if (i_this->m029C == (s16)(REG0_S(4) + 0x6E)) {
                i_this->m2520 = REG0_F(11) + 50.0f;
#if VERSION == VERSION_DEMO
                mDoGph_gInf_c::setBlureRate(180 + REG0_S(4));
                mDoGph_gInf_c::onBlure();
#else
                btd->m6E15 = 0xB4;
#endif
            }
            if (i_this->m029C <= 80) {
                cLib_addCalc2(&i_this->m24F4, REG0_F(14) + 40.0f, 0.5f, 2.0f);
            }
        }
        if (i_this->m029C == 2) {
#if VERSION == VERSION_DEMO
            mDoGph_gInf_c::offBlure();
#else
            btd->m6E15 = 1;
#endif
        }
        if (i_this->m029C == 0) {
            if (btd->m6190 >= 3) {
                i_this->m24D9 = 9;
                i_this->m029C = 220;
            } else {
                i_this->m24D9 = 0;
                cXyz spDC = player->eyePos;
                spDC.x *= 0.9f;
                spDC.z *= 0.9f;
                camera->mCamera.Reset(player->eyePos, spDC);
                camera->mCamera.Start();
                camera->mCamera.SetTrimSize(0);
                fopAcM_OffStatus(&btd->actor, fopAcStts_UNK4000_e);
                dComIfGp_event_reset();
            }
            dr->unk_40A = 0;
        }
        break;
    }
    case 9: {
        cLib_addCalc2(&i_this->m24F4, REG0_F(4) + 50.0f, 0.5f, 3.0f);
        cLib_addCalc2(&i_this->m24E8.y, btd->actor.eyePos.y + REG0_F(5) * 0.1f + 200.0f, 0.2f, 1000.0f);
        cMtx_YrotS(*calc_mtx, btd->actor.current.angle.y);
        sp130.x = REG0_F(7) * 0.1f + -300.0f;
        sp130.y = REG0_F(8) * 0.1f + 100.0f;
        sp130.z = REG0_F(9) * 0.1f + 2000.0f;
        MtxPosition(&sp130, &sp124);
        cLib_addCalc2(&i_this->m24DC.x, sp124.x, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m24DC.y, sp124.y, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m24DC.z, sp124.z, 0.1f, 50.0f);
        if (i_this->m029C == DEMO_SELECT(89, 99)) {
#if VERSION == VERSION_DEMO
            mDoGph_gInf_c::setBlureRate(180 + REG0_S(4));
            mDoGph_gInf_c::onBlure();
#else
            btd->m6E15 = 0xB4;
#endif
        }
        if (i_this->m029C == 40) {
#if VERSION == VERSION_DEMO
            mDoGph_gInf_c::offBlure();
#else
            btd->m6E15 = 1;
#endif
        }
        if (i_this->m029C == 0) {
            i_this->m24D9 = 0;
            cXyz spD0 = player->eyePos;
            spD0.x *= 0.9f;
            spD0.z *= 0.9f;
            camera->mCamera.Reset(player->eyePos, spD0);
            camera->mCamera.Start();
            camera->mCamera.SetTrimSize(0);
            fopAcM_OffStatus(&btd->actor, fopAcStts_UNK4000_e);
            dComIfGp_event_reset();
        }
        break;
    }
    }
    
    if (i_this->m24D9 > 0) {
        f32 f26 = cM_ssin(i_this->m02D8 * 0x3300);
        f27 = (i_this->m2520 * f26);
        f26 = cM_scos(i_this->m02D8 * 0x3000);
        cXyz spC4;
        cXyz spB8;
        f32 f1 = (i_this->m2520 * f26);
        spC4.x = (i_this->m24DC.x + f27);
        spC4.y = i_this->m24DC.y + f1;
        spC4.z = i_this->m24DC.z;
        spB8.x = (i_this->m24E8.x + f27);
        spB8.y = i_this->m24E8.y + f1;
        spB8.z = i_this->m24E8.z;
        f32 f1_3 = cM_scos(i_this->m02D8 * 0x1C00);
        f32 f1_2 = (i_this->m2520 * f1_3);
        s16 r23 = 7.5f * f1_2;
        camera->mCamera.Set(spB8, spC4, r23, i_this->m24F4);
        cLib_addCalc0(&i_this->m2520, 1.0f, (REG0_F(16) + 2.0f));
        s16 r23_2 = 0;
        if ((i_this->m217C != NULL) && ((fopAcM_GetParam(i_this->m217C) & 0xF0) != 0)) {
            r23_2 = -50;
        }
        if ((i_this->m24BC > (s16)(r23_2 + 0x82)) && (REG0_S(8) == 0)) {
            if ((fopAcM_GetParam(i_this->m217C) & 0xF0) != 0) {
                if (i_this->m24D9 == 2) {
                    if (dr->unk_4BA >= 10) {
                        i_this->m24D9 = 4;
                        i_this->m24D8 = 2;
                        i_this->m029C = 0;
#if VERSION > VERSION_DEMO
                        if (btd != 0) {
                            fopAcM_OnStatus(&btd->actor, 0x4000);
                        }
#endif
                    } else {
                        i_this->m24D9 = 3;
                        i_this->m029C = REG0_S(2) + 65;
                    }
                    i_this->m24D8 = 2;
                }
            } else {
                camera->mCamera.Start();
                i_this->m24D9 = 0;
                i_this->m24D8 = 2;
                fopAcM_SetParam(actor, 2);
                dComIfGp_event_reset();
            }
        }
    }
    if (i_this->m02CC < 2) {
        i_this->m02CC = 2;
    }
}

/* 800F01BC-800F062C       .text daHimo2_Execute__FP11himo2_class */
static BOOL daHimo2_Execute(himo2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int iVar5;
    cXyz local_c8;

    daPy_py_c* apdVar1 = (daPy_py_c*)daPy_getPlayerActorClass();
#if VERSION > VERSION_DEMO
    if (btd == NULL) {
        btd = (btd_class*)fpcM_Search(b_a_sub, i_this);
    }
    if (dr == NULL) {
        dr = (dr2_class*)fpcM_Search(dr_a_sub, i_this);
    }
#endif
    i_this->m02D8++;
    rope_scale = l_himo2HIO.m1C;
    local_c8.x = 4.0f;
    local_c8.y = 0.0f;
    local_c8.z = 0.0f;
    if (apdVar1->getRopeGrabRightHand()) {
        MTXCopy(apdVar1->getLeftHandMatrix(), *calc_mtx);
        MtxPosition(&local_c8, &i_this->m02EC[1]);
        MTXCopy(apdVar1->getRightHandMatrix(), *calc_mtx);
        MtxPosition(&local_c8, &i_this->m02EC[0]);
    } else {
        MTXCopy(apdVar1->getLeftHandMatrix(), *calc_mtx);
        MtxPosition(&local_c8, &i_this->m02EC[0]);
        MTXCopy(apdVar1->getRightHandMatrix(), *calc_mtx);
        MtxPosition(&local_c8, &i_this->m02EC[1]);
    }
    i_this->m02B4 = i_this->m02EC[0];
    iVar5 = i_this->m02CC + -50;
    if (iVar5 < 3) {
        iVar5 = 3;
    }
    dBgS_GndChk gndChk;
    himo2_s* phVar3 = &i_this->m1120[0];
    for (int i = 0; i < iVar5; i++, phVar3++) {
        if (i_this->m02DC != 2) {
            Vec pos;
            pos = phVar3->m10;
            pos.y += 60.0f;
            gndChk.SetPos(&pos);
            phVar3->m0C = (5.0f + dComIfG_Bgsp()->GroundCross(&gndChk));
        } else {
            phVar3->m0C = -100000.0f;
        }
    }
    new_himo2_move(i_this);
    phVar3 = &i_this->m0310[0];
    for (int i = 0; i < (i_this->m02CC + 1); i++, phVar3++) {
        phVar3->m10 = i_this->m02B4;
    }
    phVar3 = &i_this->m0310[0];
    himo2_control(i_this, phVar3);
    i_this->m0310[99].m10 = actor->current.pos;
    himo2_control2(i_this, phVar3);
#if VERSION == VERSION_DEMO
    if (i_this->m02DC != 0) {
        himo2_s* phVar3 = &i_this->m1120[0];
        i_this->m1120[0].m10 = i_this->m02B4;
        himo_e_control(i_this, phVar3);
    }
#endif
    if ((i_this->m02DC == 2) || (i_this->m02DC == 3)) {
        i_this->m2050.SetR(20.0f);
    } else {
        i_this->m2050.SetR(-100.0f);
    }
    i_this->m2050.SetC(actor->current.pos);
    dComIfG_Ccsp()->Set(&i_this->m2050);
    actor->eyePos = actor->current.pos;
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
    ResTIMG* pRVar1;
    J3DModelData* modelData;
    himo2_class* a_this = (himo2_class*)i_this;

    pRVar1 = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE);
    if (!a_this->m1F30.init(1, 200, pRVar1, 0)) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Link", LINK_BDL_ROPEEND);
    JUT_ASSERT(DEMO_SELECT(3833, 3933), modelData != NULL);
    a_this->m24B0 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (a_this->m24B0 == NULL) {
        return FALSE;
    }
    pRVar1 = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE);
    if (!a_this->m1F98.init(5, 0x20, pRVar1, 0)) {
        return FALSE;
    }
    pRVar1 = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE);
    if (!a_this->m1FD8.init(1, 16, pRVar1, 0)) {
        return FALSE;
    }
    return TRUE;
}

/* 800F07F4-800F0B08       .text daHimo2_Create__FP10fopAc_ac_c */
static cPhs_State daHimo2_Create(fopAc_ac_c* i_this) {
    himo2_class* a_this = (himo2_class*)i_this;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    fopAcM_ct(i_this, himo2_class);

    cPhs_State phase_state;
    if (!fopAcM_entrySolidHeap(&a_this->actor, CallbackCreateHeap, REG0_S(9) + 0x9050)) {
        phase_state = cPhs_ERROR_e;
    } else {
        a_this->m24B0->setBaseScale(cXyz(1.0f, 1.0f, 1.0f));
        a_this->m02CC = REG0_S(1) + 96;
        i_this->current.pos = player->getLeftHandPos();
        a_this->m2574.Set(fopAcM_GetPosition_p(i_this), fopAcM_GetOldPosition_p(i_this), i_this, 1, &a_this->m2534, fopAcM_GetSpeed_p(i_this), NULL, NULL);
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
                /* SrcGObjAt Se      */ dCcG_SE_METAL,
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
        a_this->m2014.Init(0xFF, 0xFF, i_this);
        a_this->m2050.Set(sph_src);
        a_this->m2050.SetStts(&a_this->m2014);
#if VERSION > VERSION_DEMO
        btd = NULL;
        dr = NULL;
#endif
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
