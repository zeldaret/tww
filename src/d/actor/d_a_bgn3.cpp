/**
 * d_a_bgn3.cpp
 * Boss - Puppet Ganon (Phase 3) / Ｇ（ハヤムシ）(G (Fast worm))
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bgn3.h"
#include "d/actor/d_a_bgn.h"
#include "d/actor/d_a_esa.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/res/res_bgn.h"

class daBgn3_HIO_c : public JORReflexible {
public:
    daBgn3_HIO_c();
    virtual ~daBgn3_HIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07[0x08 - 0x07];
    /* 0x08 */ f32 m08;
    /* 0x0C */ s16 m0C;
    /* 0x0E */ s16 m0E;
    /* 0x10 */ f32 m10;
    /* 0x14 */ s16 m14;
    /* 0x16 */ s16 m16;
    /* 0x18 */ f32 m18;
    /* 0x1C */ s16 m1C;
    /* 0x1E */ s16 m1E;
    /* 0x20 */ s16 m20;
    /* 0x22 */ s16 m22;
    /* 0x24 */ s16 m24;
    /* 0x26 */ s16 m26;
    /* 0x28 */ s16 m28;
    /* 0x2A */ s16 m2A;
    /* 0x2C */ s16 m2C;
    /* 0x2E */ s16 m2E;
    /* 0x30 */ s16 m30;
    /* 0x32 */ u8 m32[0x34 - 0x32];
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ s16 m3C;
    /* 0x3E */ u8 m3E;
    /* 0x3F */ u8 m3F[0x40 - 0x3F];
    /* 0x40 */ f32 m40;
    /* 0x44 */ f32 m44;
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ s16 m50;
    /* 0x52 */ s16 m52;
    /* 0x54 */ s16 m54;
};

static bgn_class* bgn;
static esa_class* esa;
static cXyz zero(0.0f, 0.0f, 0.0f);
static bool hio_set;
static daBgn3_HIO_c l_HIO;
static GXColor ke_color;
static s32 ki_all_count;

static u16 ke_max[] = {0x0028, 0x0023, 0x001E, 0x0019, 0x0014, 0x000F, 0x000F};

static f32 size_d[] = {1.0f, 0.9f, 0.8f, 0.7f, 0.6f, 0.5f, 0.4f, 0.3f, 0.6f};

/* 000000EC-000001F4       .text __ct__12daBgn3_HIO_cFv */
daBgn3_HIO_c::daBgn3_HIO_c() {
    mNo = -1;
    m05 = 0;
    m06 = 0;
    m08 = 50.0f;
    m0C = 800;
    m0E = 3;
    m20 = 0x3c;
    m10 = 60.0f;
    m14 = 1000;
    m16 = 3;
    m22 = 0x28;
    m18 = 80.0f;
    m1C = 0x4b0;
    m1E = 3;
    m24 = 0x1e;
    m26 = 10;
    m28 = 0x14;
    m2A = 0x2d;
    m2C = 0x78;
    m2E = 200;
    m30 = 0xfa;
    m34 = 5.0f;
    m38 = 0.5f;
    m3C = 3;
    m3E = 1;
    m40 = 150.0f;
    m44 = 45.0f;
    m48 = 8.0f;
    m4C = -8.0f;
    m50 = 0xbc;
    m52 = 0x98;
    m54 = 0x42;
}

/* 000001F4-00000240       .text bgn_s_sub__FPvPv */
void* bgn_s_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BGN)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 00000240-00000368       .text daBgn3_Draw__FP10bgn3_class */
static BOOL daBgn3_Draw(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    bgn = (bgn_class*)fpcM_Search(bgn_s_sub, i_this);
    if (((bgn != NULL) && (bgn->m02B5 == 2)) && (l_HIO.m3E != 0)) {
        i_this->mLineMat.update(5, l_HIO.m48, ke_color, 3, &actor->tevStr);
        dComIfGd_set3DlineMat(&i_this->mLineMat);
        part_s3* part = i_this->mParts;
        for (s32 i = 0; i < 8; i++, part++) {
            part->mLineMat.update(5, l_HIO.m48, ke_color, 3, &actor->tevStr);
            dComIfGd_set3DlineMat(&part->mLineMat);
        }
    }
    return TRUE;
}

/* 00000368-000006F8       .text gr_check__FP10bgn3_classP4cXyz */
s32 gr_check(bgn3_class* i_this, cXyz* param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_ac;
    cXyz local_b8;
    dBgS_LinChk local_a0;

    local_ac = *param_2;
    local_ac.y += 200.0f;
    local_b8 = *param_2;
    local_b8.y -= 1000.0f;
    local_a0.Set(&local_ac, &local_b8, actor);
    if (dComIfG_Bgsp()->LineCross(&local_a0)) {
        *param_2 = local_a0.mLin.GetEnd();
        param_2->y = REG0_F(8) + -2.0f;
        if (dComIfG_Bgsp()->GetAttributeCode(local_a0) == 0x13) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00000B6C-00000D90       .text tail_eff_set__FP10bgn3_class */
void tail_eff_set(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    float fVar5;
    cXyz local_38;

    if ((i_this->m0FD88 + 2U & 3) == 0) {
        local_38 = actor->current.pos;
        if (!gr_check(i_this, &local_38)) {
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8443, &local_38, 0xff, g_whiteColor, g_whiteColor, 0);
            if (i_this->m0FD94 == 0) {
                fVar5 = cM_rndF(20.0f);
                i_this->m0FD94 = (s16)(fVar5 + 20.0f);
                fopAcM_seStart(actor, JA_SE_CM_BGN_M_HEAD_RIPPLE, 0);
            }
        }
    }
    for (s32 i = 0; i < 9; i++) {
        if ((i_this->m0FD88 + i & 3U) == 0) {
            local_38 = i_this->mParts[i].m00D4;
            if (!gr_check(i_this, &local_38)) {
                dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8407, &local_38, 0xff, g_whiteColor, g_whiteColor, 0);
                if ((i == 8) && (i_this->m0FD94 == 0)) {
                    fVar5 = cM_rndF(20.0f);
                    i_this->m0FD94 = (s16)(fVar5 + 20.0f);
                    mDoAud_seStart(JA_SE_CM_BGN_M_TAIL_RIPPL, &i_this->m10054, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                }
            }
        }
    }
}

/* 00000D90-00000EB8       .text move_splash_set__FP10bgn3_class */
void move_splash_set(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_28;

    if ((i_this->m0FD88 + 2U & 3) == 0) {
        local_28 = actor->current.pos;
        if (!gr_check(i_this, &local_28)) {
            dComIfGp_particle_setSimple(dPa_name::ID_SCENE_840E, &local_28, 0xff, g_whiteColor, g_whiteColor, 0);
        }
    }
    for (s32 i = 0; i < 9; i++) {
        if ((i_this->m0FD88 + i & 7U) == 0) {
            local_28 = i_this->mParts[i].m00D4;
            if (!gr_check(i_this, &local_28)) {
                dComIfGp_particle_setSimple(dPa_name::ID_SCENE_840D, &local_28, 0xff, g_whiteColor, g_whiteColor, 0);
            }
        }
    }
}

/* 00000EB8-0000101C       .text drop_eff_set__FP10bgn3_class */
void drop_eff_set(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_18;

    local_18 = actor->current.pos;
    if (!gr_check(i_this, &local_18)) {
        dComIfGp_particle_set(dPa_name::ID_SCENE_8414, &local_18);
        dComIfGp_particle_set(dPa_name::ID_SCENE_8415, &local_18);
        dComIfGp_particle_set(dPa_name::ID_SCENE_8416, &local_18);
        dComIfGp_particle_setSimple(dPa_name::ID_SCENE_840E, &local_18, 0xff, g_whiteColor, g_whiteColor, 0);
        dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8408, &local_18, 0xff, g_whiteColor, g_whiteColor, 0);
    }
}

/* 0000101C-00001068       .text esa_s_sub__FPvPv */
void* esa_s_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_ESA)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 00001068-000013D0       .text part_control__FP10bgn3_class */
void part_control(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    float fVar1;
    float fVar2;
    f32 dVar11;
    f32 dVar10;
    f32 dVar9;
    f32 dVar8;
    f32 dVar6;
    cXyz local_b0;
    cXyz cStack_bc;
    cXyz local_c8;

    dVar9 = i_this->m0FDB8;
    dVar8 = (REG0_F(8) + 150.0f);
    dVar10 = (REG0_F(6) + -5.0f);
    i_this->mParts[0].m00D4 = i_this->m0FD7C;
    s32 i = 1;
    part_s3* ppVar4 = &i_this->mParts[i];
    cMtx_YrotS(*calc_mtx, actor->shape_angle.y);
    cMtx_XrotM(*calc_mtx, actor->shape_angle.x);
    local_b0.set(0.0f, 0.0f, -i_this->m0FDBC);
    MtxPosition(&local_b0, &local_c8);
    for (i = 1; i < 10; i++, ppVar4++) {
        fVar1 = (70.0f + REG0_F(0x13)) * ppVar4[-1].m00F4;
        fVar2 = ppVar4->m00E8.y + (ppVar4->m00D4.y + dVar10);
        if (fVar2 <= fVar1) {
            fVar2 = fVar1;
        }
        fVar1 = local_c8.x + (ppVar4->m00E8.x + (ppVar4->m00D4.x - ppVar4[-1].m00D4.x));
        dVar11 = (fVar2 - ppVar4[-1].m00D4.y);
        fVar2 = local_c8.z + (ppVar4->m00E8.z + (ppVar4->m00D4.z - ppVar4[-1].m00D4.z));
        ppVar4[-1].m00E2 = cM_atan2s(fVar1, fVar2);
        dVar6 = std::sqrtf((fVar1 * fVar1) + (fVar2 * fVar2));
        ppVar4[-1].m00E0 = -cM_atan2s(dVar11, dVar6);
        cMtx_YrotS(*calc_mtx, ppVar4[-1].m00E2);
        cMtx_XrotM(*calc_mtx, ppVar4[-1].m00E0);
        local_b0.set(0.0f, 0.0f, dVar8 * ppVar4[-1].m00F4);
        MtxPosition(&local_b0, &cStack_bc);
        ppVar4->m00E8 = ppVar4->m00D4;
        ppVar4->m00D4 = ppVar4[-1].m00D4 + cStack_bc;
        ppVar4->m00E8.x = (dVar9 * (ppVar4->m00D4.x - ppVar4->m00E8.x));
        ppVar4->m00E8.y = (dVar9 * (ppVar4->m00D4.y - ppVar4->m00E8.y));
        ppVar4->m00E8.z = (dVar9 * (ppVar4->m00D4.z - ppVar4->m00E8.z));
    }
    cLib_addCalc2(&i_this->m0FDB8, l_HIO.m38, 1.0f, 0.002f);
    cLib_addCalc2(&i_this->m0FDBC, l_HIO.m34, 1.0f, 0.5f);
}

/* 000013D0-00001800       .text checkWall__FP10bgn3_class */
s32 checkWall(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    float fVar5;
    cXyz local_ac;
    cXyz cStack_b8;

    local_ac = actor->current.pos - actor->old.pos;
    local_ac.y = 0.0f;
    fVar5 = local_ac.abs();
    if (fVar5 > 0.0f) {
        dBgS_LinChk local_a0;
        cMtx_YrotS(*calc_mtx, cM_atan2s(local_ac.x, local_ac.z));
        local_ac.x = 0.0f;
        local_ac.y = 100.0f;
        local_ac.z = REG0_F(4) + 150.0f;
        MtxPosition(&local_ac, &cStack_b8);
        cStack_b8 += actor->current.pos;
        local_ac = actor->current.pos;
        local_ac.y += 100.0f;
        local_a0.Set(&local_ac, &cStack_b8, actor);
        if (dComIfG_Bgsp()->LineCross(&local_a0)) {
            actor->current.pos.x = actor->old.pos.x;
            actor->current.pos.z = actor->old.pos.z;
            return TRUE;
        }
    }
    return FALSE;
}

/* 00001800-00001848       .text checkGround__FP10bgn3_class */
s32 checkGround(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (actor->current.pos.y <= REG0_F(9) + 150.0f) {
        actor->current.pos.y = REG0_F(9) + 150.0f;
        actor->speed.y = 0.0f;
        return TRUE;
    }
    return FALSE;
}

/* 00001848-000018EC       .text pos_move__FP10bgn3_class */
void pos_move(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_1c;
    cXyz local_28;

    local_1c.x = 0.0f;
    local_1c.y = 0.0f;
    local_1c.z = actor->speedF;
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    MtxPosition(&local_1c, &local_28);
    actor->speed.x = local_28.x;
    actor->speed.z = local_28.z;
    actor->current.pos += actor->speed;
    actor->speed.y += REG0_F(3) + -5.0f;
}

/* 000018EC-00001D64       .text move0__FP10bgn3_class */
void move0(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 bVar1;
    short maxSpeed;
    int iVar2;
    short sVar3;
    s8 sVar4;
    s16 sVar5;
    f32 dVar6;
    float fVar7;
    cXyz local_4c;

    if (esa != NULL) {
        i_this->m0FD90 = 2;
    }
    if ((int)i_this->m0FD90 != 0) {
        i_this->m0FD90--;
        maxSpeed = i_this->m0FD8E;
        if (maxSpeed < 0) {
            maxSpeed *= -1;
        }
        if (i_this->m0FDB0 != 0) {
            sVar3 = (s16)cM_atan2s(-actor->current.pos.x, -actor->current.pos.z);
        } else {
            if (esa != NULL) {
                local_4c = esa->current.pos - actor->current.pos;
                sVar3 = (s16)cM_atan2s(local_4c.x, local_4c.z);
                maxSpeed *= 2;
            } else {
                dVar6 = cM_ssin(i_this->m0FD88 * (REG0_S(9) + 0x900));
                sVar3 = fopAcM_searchPlayerAngleY(actor);
                sVar3 = sVar3 + (s16)((REG0_F(0x12) + 4000.0f) * dVar6);
            }
        }
        cLib_addCalcAngleS2(&actor->current.angle.y, sVar3, 4, maxSpeed);
    } else {
        actor->current.angle.y += i_this->m0FD8E;
    }
    if (actor->health == 3) {
        fVar7 = l_HIO.m08;
    } else if (actor->health == 2) {
        fVar7 = l_HIO.m10;
    } else {
        fVar7 = l_HIO.m18;
    }
    cLib_addCalc2(&actor->speedF, fVar7, 1.0f, 3.0f);
    pos_move(i_this);
    checkGround(i_this);
    bVar1 = false;
    iVar2 = checkWall(i_this);
    if ((iVar2 != 0) && (i_this->m0FDAA[1] == 0)) {
        i_this->m0FD90 = 0;
        actor->current.angle.y += 0x8000;
        i_this->m0FDB8 = REG0_F(5) + 0.9f;
        bVar1 = true;
        i_this->m0FDAA[1] = 0x14;
        dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        fopAcM_seStart(actor, JA_SE_CM_BGN_M_HIT_WALL, 0);
        i_this->m100AC = l_HIO.m3C;
        if (actor->health == 3) {
            sVar5 = l_HIO.m0E;
        } else if (actor->health == 2) {
            sVar5 = l_HIO.m16;
        } else {
            sVar5 = l_HIO.m1E;
        }
        i_this->m0FD92 = i_this->m0FD92 + 1;
        if (i_this->m0FD92 >= sVar5) {
            i_this->m0FD92 = 0;
            if (actor->health == 3) {
                i_this->m0FD90 = l_HIO.m20;
            } else if (actor->health == 2) {
                i_this->m0FD90 = l_HIO.m22;
            } else {
                i_this->m0FD90 = l_HIO.m24;
            }
        }
    }
    if (i_this->m0FDAE == 0) {
        fVar7 = cM_rndF(50.0f);
        i_this->m0FDAE = (s16)(fVar7 + 30.0f);
        bVar1 = true;
    }
    if (bVar1) {
        sVar4 = actor->health;
        if (sVar4 == 3) {
            i_this->m0FD8E = l_HIO.m0C;
        } else if (sVar4 == 2) {
            i_this->m0FD8E = l_HIO.m14;
        } else {
            i_this->m0FD8E = l_HIO.m1C;
        }
        fVar7 = cM_rndF(1.0f);
        if (fVar7 < 0.5f) {
            i_this->m0FD8E *= -1;
        }
    }
    i_this->m0FF28.OnAtSetBit();
    i_this->m0FDFC.OnAtSetBit();
    actor->current.angle.x = 0;
}

/* 00001D64-00001E6C       .text mahi__FP10bgn3_class */
void mahi(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    switch (i_this->m0FD8C) {
    case 0:
        i_this->m0FD8C = 1;
    // fallthrough
    case 1:
        i_this->m002B4->play(&actor->current.pos, 0, 0);
        if (i_this->m0FDAA[0] == 0) {
            i_this->m0FD8A = 0;
            i_this->m0FD8C = 0;
        }
        break;
    }
    cLib_addCalc0(&actor->speedF, 1.0f, 3.0f);
    pos_move(i_this);
    actor->current.angle.x = 0;
    checkGround(i_this);
    if ((checkWall(i_this)) && (i_this->m0FDAA[1] == 0)) {
        i_this->m0FD90 = 0;
        actor->current.angle.y += 0x8000;
        i_this->m0FDB8 = REG0_F(5) + 0.9f;
    }
}

/* 00001E6C-00002100       .text damage__FP10bgn3_class */
void damage(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    short sVar1;
    float fVar4;
    cXyz local_34;

    switch (i_this->m0FD8C) {
    case 0:
        actor->speed.y = 150.0f;
        actor->speedF = 30.0f;
        i_this->m0FD8C = 1;
        i_this->m0FDB8 = 1.0f;
        break;
    case 1:
        cLib_addCalc2(&i_this->m100A0, REG0_F(9) + 350.0f, 1.0f, REG0_F(10) + 50.0f);
        if (checkGround(i_this)) {
            actor->speed.y = 50.0f;
            i_this->m0FD8C = 2;
            actor->current.angle.y = cM_rndF(65536.0f);
            i_this->m0FDB8 = 1.0f;
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            drop_eff_set(i_this);
        }
        break;
    case 2:
        if (checkGround(i_this)) {
            i_this->m0FD8A = 0;
            i_this->m0FD8C = 0;
        }
        break;
    }
    pos_move(i_this);
    local_34 = actor->current.pos - actor->old.pos;
    fVar4 = std::sqrtf(local_34.x * local_34.x + local_34.z * local_34.z);
    actor->current.angle.x = -cM_atan2s(local_34.y, fVar4);
    sVar1 = actor->current.angle.x;
    if (sVar1 > 0x3000) {
        actor->current.angle.x = 0x3000;
    } else if (sVar1 < -0x3000) {
        actor->current.angle.x = -0x3000;
    }
    checkGround(i_this);
    if ((checkWall(i_this)) && (i_this->m0FDAA[1] == 0)) {
        actor->current.angle.y += 0x8000;
        i_this->m0FDAA[1] = 0x14;
    }
    i_this->m0FF28.OffAtSetBit();
    i_this->m0FDFC.OffAtSetBit();
}

/* 00002100-00002524       .text end__FP10bgn3_class */
void end(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    short sVar1;
    float fVar7;
    cXyz local_44;

    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    switch (i_this->m0FD8C) {
    case 0:
        actor->speed.y = 150.0f;
        actor->speedF = 0.0f;
        i_this->m0FD8C = 1;
        bgn->mCA62 = 0x14;
        i_this->m0FDB8 = 1.0f;
        fopAcM_monsSeStart(player, JA_SE_CV_BK_SURPRISE, 0);
        break;
    case 1:
    case 2:
    case 3:
    case 4:
        i_this->m100A0 = actor->current.pos.y - 150.0f;
        if (i_this->m100A0 > 350.0f) {
            i_this->m100A0 = 350.0f;
        }
        if (checkGround(i_this)) {
            i_this->m0FD8C++;
            actor->current.angle.y = cM_rndF(65536.0f);
            i_this->m0FDB8 = 1.0f;
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            drop_eff_set(i_this);
            actor->speed.y = REG0_F(0xb) + 130.0f;
            actor->speedF = 0.0f;
            actor->current.angle.y = cM_rndF(65536.0f);
            fopAcM_monsSeStart(actor, JA_SE_CV_BGN_HIT_1, 0);
        }
        if ((i_this->m0FD8C == 4) && (actor->speed.y <= -30.0f)) {
            i_this->m0FD8C = 5;
            i_this->m0FD8E = 0;
        }
        break;
    case 5:
        actor->speed.y += REG0_F(0xc) + 5.5f;
        if (actor->speed.y > 0.0f) {
            cLib_addCalc2(&i_this->m10060, 1.0f, 1.0f, 0.015f);
        }
        actor->current.angle.y = actor->current.angle.y + i_this->m0FD8E;
        actor->shape_angle.y = actor->shape_angle.y + i_this->m0FD8E;
        cLib_addCalcAngleS2(&i_this->m0FD8E, 5000, 4, 100);
        cLib_addCalc2(&i_this->m0FDBC, REG0_F(6) + 50.0f, 1.0f, 1.0f);
        cLib_addCalc0(&i_this->m100A0, 1.0f, (REG0_F(10) + 50.0f));
        break;
    }
    pos_move(i_this);
    local_44 = actor->current.pos - actor->old.pos;
    fVar7 = std::sqrtf(local_44.x * local_44.x + local_44.z * local_44.z);
    actor->current.angle.x = -cM_atan2s(local_44.y, fVar7);
    sVar1 = actor->current.angle.x;
    if (sVar1 > 0x3000) {
        actor->current.angle.x = 0x3000;
    } else if (sVar1 < -0x3000) {
        actor->current.angle.x = -0x3000;
    }
    checkGround(i_this);
    i_this->m0FF28.OffAtSetBit();
    i_this->m0FDFC.OffAtSetBit();
    cLib_addCalc2(&actor->current.pos.x, -15.0f, 0.05f, 30.0f);
    cLib_addCalc2(&actor->current.pos.z, 375.17, 0.05f, 30.0f);
}

/* 00002524-00002C18       .text damage_check__FP10bgn3_class */
void damage_check(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    char cVar5;
    s8 sVar6;
    dCcD_GObjInf* pdVar2;
    JPABaseEmitter* pJVar3;
    s16 sVar7;
    s8 bVar10;
    f32 dVar11;
    csXyz local_78;
    cXyz local_58;
    CcAtInfo local_4c;

    if (i_this->m0FDB4 == 0) {
        local_4c.pParticlePos = NULL;
        if (i_this->m0FDFC.ChkTgHit()) {
            local_4c.mpObj = i_this->m0FDFC.GetTgHitObj();
            local_4c.mpActor = at_power_check(&local_4c);
            fopAcM_monsSeStart(actor, JA_SE_CV_BGN_M_HIT_FACE, 0);
            fopAcM_seStart(actor, JA_SE_CM_BGN_M_FACE_HIT, 0);
            if (local_4c.mResultingAttackType == 9) {
                bVar10 = 6;
                dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                dScnPly_ply_c::nextPauseTimer = 5;
                i_this->m100A8 = 0x1e;
                sVar7 = l_HIO.m30;
            } else if (local_4c.mResultingAttackType == 2) {
                bVar10 = 5;
                i_this->m100A8 = 0x19;
                sVar7 = l_HIO.m2E;
            } else if (local_4c.mResultingAttackType == 1) {
                pdVar2 = dCcD_GetGObjInf(local_4c.mpObj);
                if ((pdVar2->GetAtSpl()) == 1) {
                    bVar10 = 4;
                    dScnPly_ply_c::nextPauseTimer = 3;
                    i_this->m100A8 = 0x14;
                    sVar7 = l_HIO.m2C;
                } else {
                    bVar10 = 3;
                    dScnPly_ply_c::nextPauseTimer = 2;
                    i_this->m100A8 = 0xf;
                    sVar7 = l_HIO.m2A;
                }
            } else if (fopAcM_GetName(local_4c.mpActor) == PROC_ARROW) {
                bVar10 = 2;
                i_this->m100A8 = 10;
                sVar7 = l_HIO.m28;
            } else {
                bVar10 = 1;
                i_this->m100A8 = 7;
                sVar7 = l_HIO.m26;
            }
            if (bVar10 != 0) {
                if (i_this->m0FD8A != 1) {
                    i_this->m0FDAA[0] = sVar7;
                    i_this->m0FD8A = 1;
                }
                i_this->m0FD8C = 0;
                i_this->m0FDB4 = 0x14;
                if (bVar10 >= 4) {
                    dComIfGp_particle_set(dPa_name::ID_COMMON_0010, i_this->m0FDFC.GetTgHitPosP());
                    local_58.z = 2.0f;
                    local_58.y = 2.0f;
                    local_58.x = 2.0f;
                    local_78.z = 0;
                    local_78.x = 0;
                    local_78.y = fopAcM_searchPlayerAngleY(actor);
                    dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, i_this->m0FDFC.GetTgHitPosP(), &local_78, &local_58);
                    dKy_SordFlush_set(*i_this->m0FDFC.GetTgHitPosP(), 1);
                }
                def_se_set(actor, local_4c.mpObj, 0x40);
                return;
            }
        }
        if (i_this->mParts[8].m00F8.ChkTgHit()) {
            i_this->m0FDB4 = 0x14;
            i_this->m0FD9E = 1;
            i_this->m0FD8A = 2;
            i_this->m0FD8C = 0;
            sVar6 = actor->health;
            if (sVar6 != 0) {
                actor->health = sVar6 + -1;
                mDoAud_seStart(JA_SE_LK_ARROW_HIT, NULL, 0x35, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                dVar11 = (REG0_F(5) + 2.0f);
                if (actor->health == 0) {
                    mDoAud_bgmStop(30);
                    pJVar3 = dComIfGp_particle_set(dPa_name::ID_SCENE_8457, &i_this->m10054);
                    if (pJVar3 != NULL) {
                        JGeometry::TVec3<f32> scale(dVar11, dVar11, dVar11);
                        pJVar3->setGlobalScale(scale);
                    }
                    pJVar3 = dComIfGp_particle_set(dPa_name::ID_SCENE_8458, &i_this->m10054);
                    if (pJVar3 != NULL) {
                        JGeometry::TVec3<f32> scale(dVar11, dVar11, dVar11);
                        pJVar3->setGlobalScale(scale);
                    }
                    i_this->m0FD8A = 3;
                    i_this->m0FD8C = 0;
                    i_this->m0FDB4 = 10000;
                    mDoAud_monsSeStart(JA_SE_CV_BGN_HIT_LAST, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    mDoAud_seStart(JA_SE_CM_BGN_M_BRK_ORB, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                } else {
                    pJVar3 = dComIfGp_particle_set(dPa_name::ID_SCENE_8459, &i_this->m10054);
                    if (pJVar3 != NULL) {
                        JGeometry::TVec3<f32> scale(dVar11, dVar11, dVar11);
                        pJVar3->setGlobalScale(scale);
                    }
                    mDoAud_monsSeStart(JA_SE_CV_BGN_HIT_1, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                }
            }
        }
        cVar5 = 0;
        if (i_this->m0FF28.ChkTgHit()) {
            local_4c.mpObj = i_this->m0FF28.GetTgHitObj();
            cVar5 = 1;
        }
        for (s32 i = 0; i < 8; i++) {
            pdVar2 = &i_this->mParts[i].m00F8;
            if (pdVar2->ChkTgHit()) {
                local_4c.mpObj = pdVar2->GetTgHitObj();
                cVar5 = 2;
            }
        }
        if ((cVar5 != 0) && (i_this->m0FDB6 == 0)) {
            i_this->m0FDB6 = 10;
            def_se_set(actor, local_4c.mpObj, 0x44);
        }
    }
}

/* 00002C18-00002E4C       .text ke_control__FP9bgn3_ke_sif */
void ke_control(bgn3_ke_s* param_1, int param_2, float param_3) {
    /* Nonmatching */
    cXyz local_90;
    cXyz local_9c;
    cXyz local_a8;

    s32 i = 1;
    cXyz* pcVar3 = &param_1->m00[i];
    local_90.x = 0.0f;
    local_90.y = 0.0f;
    local_90.z = param_3;
    for (i = 1; i < 5; i++, pcVar3++) {
        float fVar1 = (0.1f * (s32)(5U - i));
        local_a8.x = param_1->m78.x * fVar1;
        local_a8.y = param_1->m78.y * fVar1;
        local_a8.z = param_1->m78.z * fVar1;
        f32 fVar_x = local_a8.x + (pcVar3->x - pcVar3[-1].x);
        f32 fVar_z = local_a8.z + (pcVar3->z - pcVar3[-1].z);
        f32 fVar_y = (l_HIO.m4C + (pcVar3->y + local_a8.y)) - pcVar3[-1].y;
        s16 iVar4 = -cM_atan2s(fVar_x, fVar_z);
        int iVar5 = cM_atan2s(fVar_y, std::sqrtf((fVar_x * fVar_x) + (fVar_z * fVar_z)));
        cMtx_XrotS(*calc_mtx, (int)iVar4);
        cMtx_YrotM(*calc_mtx, iVar5);
        MtxPosition(&local_90, &local_9c);
        pcVar3->x = pcVar3[-1].x + local_9c.x;
        pcVar3->y = pcVar3[-1].y + local_9c.y;
        pcVar3->z = pcVar3[-1].z + local_9c.z;
    }
}

/* 00002E4C-00002EE4       .text ke_move__FP19mDoExt_3DlineMat0_cP9bgn3_ke_sif */
void ke_move(mDoExt_3DlineMat0_c* param_1, bgn3_ke_s* param_2, int param_3, float param_4) {
    cXyz* pcVar3;

    if (l_HIO.m3E != 0) {
        ke_control(param_2, param_3, param_4);
        pcVar3 = param_1->getPos(param_3);
        for (s32 i = 0; i < 5; i++, pcVar3++) {
            pcVar3->x = param_2->m00[i].x;
            pcVar3->y = param_2->m00[i].y;
            pcVar3->z = param_2->m00[i].z;
        }
    }
}

/* 00002EE4-00003110       .text move_se_set__FP10bgn3_class */
void move_se_set(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    u32 uVar2;
    cXyz local_28;

    local_28 = actor->current.pos - actor->old.pos;
    local_28.y = 0.0f;
    uVar2 = local_28.abs() * 3.5f;
    if (uVar2 > 100) {
        uVar2 = 100;
    }
    fopAcM_seStart(actor, JA_SE_CM_BGN_MECHA_ROTATE, uVar2);
    local_28 = actor->current.pos - actor->old.pos;
    local_28.z = 0.0f;
    local_28.x = 0.0f;
    uVar2 = local_28.abs() * 2.0f;
    if (uVar2 > 100) {
        uVar2 = 100;
    }
    fopAcM_seStart(actor, JA_SE_CM_BGN_MECHA_ROPE, uVar2);
}

/* 00003110-00004058       .text move__FP10bgn3_class */
void move(bgn3_class* i_this) {
    /* Nonmatching */
    static s16 fl_check_d[] = {0x0015, 0x0013, 0x0011, 0x000F, 0x000D, 0x000B, 0x0009, 0x0007, 0x0005};
    fopAc_ac_c* actor = &i_this->actor;
    float fVar1;
    BOOL bVar5;
    J3DModel* pJVar12;
    f32 dVar20;
    f32 dVar21;
    f32 dVar22;
    cXyz local_d8;
    cXyz local_e4;
    cXyz cStack_f0;

    bVar5 = false;
    if (l_HIO.m05 == 0) {
        switch (i_this->m0FD8A) {
        case 10:
            break;
        case 0:
            move0(i_this);
            if (actor->speedF > 10.0f) {
                bVar5 = true;
                move_splash_set(i_this);
                fopAcM_seStart(actor, JA_SE_CM_BGN_M_CRAWL, 0);
                move_se_set(i_this);
            }
            break;
        case 1:
            mahi(i_this);
            break;
        case 2:
            damage(i_this);
            break;
        case 3:
            end(i_this);
            break;
        }
    }
    tail_eff_set(i_this);
    damage_check(i_this);
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y, 4, 0x1000);
    cLib_addCalcAngleS2(&actor->shape_angle.x, actor->current.angle.x, 8, 0x400);
    cMtx_YrotS(*calc_mtx, (int)actor->shape_angle.y);
    cMtx_XrotM(*calc_mtx, actor->shape_angle.x);
    local_d8.x = 0.0f;
    local_d8.y = 0.0f;
    local_d8.z = REG0_F(3) + -300.0f;
    MtxPosition(&local_d8, &local_e4);
    i_this->m0FD7C = actor->current.pos + local_e4;
    for (s32 i = 0; i < 9; i++) {
        i_this->mParts[i].m00F4 = (REG0_F(0xb) + 1.7f) * size_d[i];
    }
    part_control(i_this);
    i_this->m002B4->play(&actor->current.pos, 0, 0);
    i_this->m017C0->play();
    i_this->m017C4->play();
    MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, actor->shape_angle.y);
    cMtx_XrotM(*calc_mtx, actor->shape_angle.x);
    cMtx_ZrotM(*calc_mtx, actor->shape_angle.z);
    MtxPush();
    pJVar12 = i_this->m002CC;
    MtxScale(REG0_F(10) + 2.0f, REG0_F(10) + 2.0f, REG0_F(10) + 2.0f, true);
    pJVar12->setBaseTRMtx(*calc_mtx);
    local_d8.x = 0.0f;
    local_d8.y = 0.0f;
    local_d8.z = 0.0f;
    MtxPosition(&local_d8, &local_e4);
    i_this->m0FF28.SetC(local_e4);
    i_this->m0FF28.SetR(REG0_F(1) + 200.0f);
    dComIfG_Ccsp()->Set(&i_this->m0FF28);
    if (i_this->m0FD9E == 0x17) {
        i_this->m0FD9C = 0x32;
        i_this->m0FDA8 = 100;
    }
    if (i_this->m0FDA8 != 0) {
        i_this->m0FDA8--;
        fVar1 = i_this->m0FDA8 * 100.0f * (REG8_F(8) + 0.001f);
        dVar20 = fVar1;
        if (i_this->m0FDA0 == NULL) {
            i_this->m0FDA0 = dComIfGp_particle_set(dPa_name::ID_COMMON_03ED, &local_e4);
        } else {
            i_this->m0FDA0->setGlobalTranslation(local_e4.x, local_e4.y, local_e4.z);
            JGeometry::TVec3<f32> scale(fVar1, fVar1, fVar1);
            i_this->m0FDA0->setGlobalScale(scale);
        }
        if (i_this->m0FDA4 == NULL) {
            local_d8.setall(dVar20);
            i_this->m0FDA4 = dComIfGp_particle_set(dPa_name::ID_COMMON_03EE, &local_e4);
        } else {
            i_this->m0FDA4->setGlobalTranslation(local_e4.x, local_e4.y, local_e4.z);
            JGeometry::TVec3<f32> scale(dVar20, dVar20, dVar20);
            i_this->m0FDA4->setGlobalScale(scale);
        }
    } else {
        if (i_this->m0FDA0 != NULL) {
            i_this->m0FDA0->becomeInvalidEmitter();
            i_this->m0FDA0 = NULL;
        }
        if (i_this->m0FDA4 != NULL) {
            i_this->m0FDA4->becomeInvalidEmitter();
            i_this->m0FDA4 = NULL;
        }
    }
    MtxPull();
    for (s32 i = 0; i < 40; i++) {
        MtxPush();
        cMtx_XrotM(*calc_mtx, -((REG0_S(5) + 0x3fffU & (s32)i * (REG0_S(4) + 1000)) - (REG0_S(6) + 0x2000)));
        cMtx_ZrotM(*calc_mtx, -((REG0_S(8) + 0xfffU & (s32)i * (REG0_S(7) + 5000)) - (REG0_S(9) + 0x800)));
        local_d8.y = (100.0f + REG13_F(0xd));
        MtxPosition(&local_d8, i_this->mHairs[i].m00);
        local_d8.y = l_HIO.m40;
        MtxPosition(&local_d8, &i_this->mHairs[i].m78);
        i_this->mHairs[i].m78 -= local_e4;
        ke_move(&i_this->mLineMat, &i_this->mHairs[i], i, (2.0f * l_HIO.m44));
        MtxPull();
    }
    MtxTrans(0.0f, 0.0f, REG0_F(2) + 250.0f, true);
    if (i_this->m100A8 != 0) {
        i_this->m100A8--;
    }
    dVar22 = (i_this->m100A8 * (REG0_F(0xe) + 500.0f));
    dVar20 = cM_ssin(i_this->m0FD88 * 0x2100U);
    cMtx_YrotM(*calc_mtx, (dVar22 * cM_scos(i_this->m0FD88 * 0x2300U)));
    cMtx_XrotM(*calc_mtx, (dVar22 * dVar20));
    i_this->m002B4->getModel()->setBaseTRMtx(*calc_mtx);
    local_d8.setall(0.0f);
    MtxPosition(&local_d8, &local_e4);
    i_this->m0FDFC.SetC(local_e4);
    i_this->m0FDFC.SetR(REG0_F(0) + 150.0f);
    dComIfG_Ccsp()->Set(&i_this->m0FDFC);
    actor->eyePos = local_e4;
    actor->attention_info.position = actor->eyePos;
    actor->attention_info.position.y += REG0_F(7) + 100.0f;
    i_this->m002B4->calc();
    if (i_this->m0FD9E != 0) {
        i_this->m0FD9E++;
        if (i_this->m0FD9E > 100) {
            i_this->m0FD9E = 0;
        }
    }
    s32 i = 0;
    part_s3* ppVar18 = &i_this->mParts[i];
    for (i = 0; i < 9; i++, ppVar18++) {
        MtxTrans(ppVar18->m00D4.x, ppVar18->m00D4.y, ppVar18->m00D4.z, false);
        cMtx_YrotM(*calc_mtx, ppVar18->m00E2);
        cMtx_XrotM(*calc_mtx, ppVar18->m00E0);
        MtxPush();
        MtxScale(ppVar18->m00F4, ppVar18->m00F4, ppVar18->m00F4, true);
        local_d8.setall(0.0f);
        MtxPosition(&local_d8, &local_e4);
        if (i == 8) {
            if (actor->health == 3) {
                ppVar18->m0000 = i_this->m017BC;
            } else if (actor->health == 2) {
                ppVar18->m0000 = i_this->m017B8;
            } else if (actor->health == 1) {
                ppVar18->m0000 = i_this->m017B4;
            } else {
                ppVar18->m0000 = NULL;
            }
            i_this->m10054 = local_e4;
        }
        if (ppVar18->m0000 != NULL) {
            ppVar18->m0000->setBaseTRMtx(*calc_mtx);
        }
        ppVar18->m00F8.SetC(local_e4);
        ppVar18->m00F8.SetR(ppVar18->m00F4 * (100.0f + REG0_F(0xc)));
        if (bVar5) {
            ppVar18->m00F8.OnAtSetBit();
        } else {
            ppVar18->m00F8.OffAtSetBit();
        }
        dComIfG_Ccsp()->Set(&ppVar18->m00F8);
        MtxPull();
        if ((i < 7) && (l_HIO.m3E != 0)) {
            dVar21 = 60.0f;
            for (s32 j = 0; j < ke_max[i]; j++) {
                MtxPush();
                cMtx_XrotM(*calc_mtx, (REG0_S(5) + 0x3fffU & j * (REG0_S(4) + 1000)) - (REG0_S(6) + 0x2000));
                cMtx_ZrotM(*calc_mtx, (REG0_S(8) + 0xfffU & j * (REG0_S(7) + 5000)) - (REG0_S(9) + 0x800));
                local_e4.y = 100.0f + REG13_F(0xd);
                local_d8.y = ppVar18->m00F4 * (dVar21 + REG13_F(0xc));
                MtxPosition(&local_d8, ppVar18->mHairs[j].m00);
                local_d8.y = l_HIO.m40;
                MtxPosition(&local_d8, &ppVar18->mHairs[j].m78);
                ppVar18->mHairs[j].m78 -= local_e4;
                ke_move(&ppVar18->mLineMat, &ppVar18->mHairs[j], j, (ppVar18->m00F4 * l_HIO.m44));
                MtxPull();
            }
        }
        if (i_this->m0FD9E == fl_check_d[i]) {
            ppVar18->m00D0 = 0x32;
            ppVar18->m0238 = 100;
        }
        if (ppVar18->m00D0 != 0) {
            ppVar18->m00D0--;
        }
        if (ppVar18->m0238 != 0) {
            ppVar18->m0238--;
            fVar1 = (REG8_F(0) + 0.04f) * (ppVar18->m00F4 * ppVar18->m0238);
            dVar21 = fVar1;
            if (ppVar18->m0230 == NULL) {
                ppVar18->m0230 = dComIfGp_particle_set(dPa_name::ID_COMMON_03ED, &ppVar18->m00D4);
            } else {
                ppVar18->m0230->setGlobalTranslation(ppVar18->m00D4.x, ppVar18->m00D4.y, ppVar18->m00D4.z);
                JGeometry::TVec3<f32> scale(fVar1, fVar1, fVar1);
                ppVar18->m0230->setGlobalScale(scale);
            }
            if (ppVar18->m0234 == NULL) {
                local_d8.setall(dVar21);
                ppVar18->m0234 = dComIfGp_particle_set(dPa_name::ID_COMMON_03EE, &ppVar18->m00D4);
            } else {
                ppVar18->m0234->setGlobalTranslation(ppVar18->m00D4.x, ppVar18->m00D4.y, ppVar18->m00D4.z);
                JGeometry::TVec3<f32> scale(dVar21, dVar21, dVar21);
                ppVar18->m0234->setGlobalScale(scale);
            }
        } else {
            if (ppVar18->m0230 != NULL) {
                ppVar18->m0230->becomeInvalidEmitter();
                ppVar18->m0230 = NULL;
            }
            if (ppVar18->m0234 != NULL) {
                ppVar18->m0234->becomeInvalidEmitter();
                ppVar18->m0234 = NULL;
            }
        }
    }
    if (bVar5) {
        i_this->m0FDFC.OnAtSetBit();
        i_this->m0FF28.OnAtSetBit();
    } else {
        i_this->m0FDFC.OffAtSetBit();
        i_this->m0FF28.OffAtSetBit();
    }
    cMtx_copy(i_this->m002CC->getBaseTRMtx(), *calc_mtx);
    local_d8.setall(0.0f);
    MtxPosition(&local_d8, &cStack_f0);
    cLib_addCalc0(&i_this->m100A0, 1.0f, 25.0f);
    cXyz* pcVar13 = i_this->m10064.getPos(0);
    u8* pcVar14 = i_this->m10064.getSize(0);
    for (s32 i = 0; i < 0x3C; i++) {
        f32 temp = (i_this->m100A0 * (cM_ssin(cM_rad2s(0.053247336f * (f32)i))));
        fVar1 = temp * (0.01666667f * (f32)(0x3b - i));
        local_d8.x = fVar1 * cM_ssin(i_this->m0FD88 * (REG0_S(3) + 300) + i * (REG0_S(4) + 2000));
        local_d8.y = 0.0f;
        local_d8.z = fVar1 * cM_ssin(i_this->m0FD88 * (REG0_S(5) + 0xfa) + i * (REG0_S(6) + 2000));
        *pcVar13 = cStack_f0 + local_d8;
        *pcVar14 = REG0_S(3) + 10;
        cStack_f0.y += 50.0f;
        pcVar13++;
        pcVar14++;
    }
}

/* 00004058-000040B0       .text ki_c_sub__FPvPv */
void* ki_c_sub(void* param_1, void* param_2) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KS)) {
        ki_all_count++;
    }
    return NULL;
}

/* 000040B0-000040F4       .text ki_check__FP10bgn3_class */
s32 ki_check(bgn3_class* i_this) {
    ki_all_count = 0;
    fpcM_Search(ki_c_sub, i_this);
    return ki_all_count;
}

/* 000040F4-00004358       .text daBgn3_Execute__FP10bgn3_class */
static BOOL daBgn3_Execute(bgn3_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_28;

    bgn = (bgn_class*)fpcM_Search(bgn_s_sub, i_this);
    if (bgn == NULL) {
        return TRUE;
    }
    if (l_HIO.m06 != 0) {
        actor->health = l_HIO.m06;
    }
    esa = (esa_class*)fpcEx_Search(esa_s_sub, i_this);
    if (bgn->m02B5 != 2) {
        i_this->m0FD8A = 10;
        actor->current.pos.x = 0.0f;
        actor->current.pos.y = 30000.0f;
        actor->current.pos.z = 0.0f;
        fopAcM_OffStatus(actor, 0);
        actor->attention_info.flags = 0;
        return TRUE;
    }
    if (i_this->m0FD8A == 10) {
        actor->current.pos = actor->home.pos;
        i_this->m0FD8A = 0;
        i_this->m0FD90 = 0xb4;
        i_this->m0FDB0 = 0xb4;
    }
    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    cLib_addCalc2(&i_this->m10060, 0.0f, 1.0f, 0.01f);
    i_this->m0FD88 = i_this->m0FD88 + 1;
    actor->attention_info.distances[2] = 0x22;
    for (s32 i = 0; i < 5; i++) {
        if (i_this->m0FDAA[i] != 0) {
            i_this->m0FDAA[i]--;
        }
    }
    if (i_this->m0FDB4 != 0) {
        i_this->m0FDB4--;
    }
    if (i_this->m0FDB6 != 0) {
        i_this->m0FDB6--;
    }
    if (i_this->m0FD94 != 0) {
        i_this->m0FD94--;
    }
    if (i_this->m0FD9C != 0) {
        i_this->m0FD9C--;
    }
    move(i_this);
    if (i_this->m100AC != 0) {
        i_this->m100AC--;
        if (ki_check(i_this) < 0x14) {
            local_28.x = cM_rndFX(2500.0f);
            local_28.y = cM_rndF(500.0f) + 3500.0f;
            local_28.z = cM_rndFX(2500.0f);
            fopAcM_create(PROC_KS, 3, &local_28, fopAcM_GetRoomNo(actor));
        }
    }
    return TRUE;
}

/* 00004358-00004360       .text daBgn3_IsDelete__FP10bgn3_class */
static BOOL daBgn3_IsDelete(bgn3_class*) {
    return TRUE;
}

/* 00004360-000043EC       .text daBgn3_Delete__FP10bgn3_class */
static BOOL daBgn3_Delete(bgn3_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->m002AC, "Bgn");
    if (i_this->m100B0 != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    mDoAud_seDeleteObject(&i_this->m10054);
    return TRUE;
}

/* 000043EC-00004848       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    mDoExt_McaMorf* morf;
    J3DModelData* pJVar1;
    int iVar3;
    J3DAnmTevRegKey* pJVar6;
    ResTIMG* pImg;
    bgn3_class* i_this = (bgn3_class*)a_this;

    morf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_HEAD1),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bgn", BGN_BCK_BGN_HEAD1),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    i_this->m002B4 = morf;
    if ((i_this->m002B4 == NULL) || (i_this->m002B4->getModel() == NULL)) {
        return FALSE;
    }
    pJVar1 = (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_DEKU1);
    i_this->m002CC = mDoExt_J3DModel__create(pJVar1, 0, 0x11020203);
    if (i_this->m002CC == NULL) {
        return FALSE;
    }
    iVar3 = i_this->mLineMat.init(0x28, 5, 0);
    if (iVar3 == 0) {
        return FALSE;
    }
    for (s32 i = 0; i < 9; i++) {
        i_this->mParts[i].m0000 = mDoExt_J3DModel__create(pJVar1, 0, 0x11020203);
        if (i_this->mParts[i].m0000 == 0) {
            return false;
        }
        if ((i < 7) && (!i_this->mParts[i].mLineMat.init(ke_max[i], 5, 0))) {
            return false;
        }
    }
    pJVar1 = (J3DModelData*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BDL_BGN_JYAKUTENA, BGN_BDL_BGN_JYAKUTENA3));
    i_this->m017BC = mDoExt_J3DModel__create(pJVar1, 0, 0x11020203);
    if (i_this->m017BC == NULL) {
        return FALSE;
    }
    pJVar1 = (J3DModelData*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BDL_BGN_JYAKUTENB, BGN_BDL_BGN_JYAKUTENB3));
    i_this->m017B8 = mDoExt_J3DModel__create(pJVar1, 0, 0x11020203);
    if (i_this->m017B8 == NULL) {
        return FALSE;
    }
    i_this->m017C4 = new mDoExt_brkAnm();
    if (i_this->m017C4 == NULL) {
        return FALSE;
    }
    pJVar6 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BRK_BGN_JYAKUTENBC, BGN_BRK_BGN_JYAKUTENB3));
    iVar3 = i_this->m017C4->init(pJVar1, pJVar6, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (iVar3 == 0) {
        return FALSE;
    }
    pJVar1 = (J3DModelData*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BDL_BGN_JYAKUTENC, BGN_BDL_BGN_JYAKUTENC3));
    i_this->m017B4 = mDoExt_J3DModel__create(pJVar1, 0, 0x11020203);
    if (i_this->m017B4 == NULL) {
        return FALSE;
    }
    i_this->m017C0 = new mDoExt_brkAnm();
    if (i_this->m017C0 == NULL) {
        return FALSE;
    }
    pJVar6 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BRK_BGN_JYAKUTENBC, BGN_BRK_BGN_JYAKUTENC3));
    iVar3 = i_this->m017C0->init(pJVar1, pJVar6, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (iVar3 == 0) {
        return FALSE;
    }
    pImg = (ResTIMG*)dComIfG_getObjectRes("Bgn", BGN_BTI_NOT_CUT1);
    iVar3 = i_this->m10064.init(1, 0x3c, pImg, 1);
    if (!iVar3) {
        return FALSE;
    }
    return TRUE;
}

/* 00004890-00004BC0       .text daBgn3_Create__FP10fopAc_ac_c */
static cPhs_State daBgn3_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK9,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e | dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 50.0f,
        }},
    };
    static dCcD_SrcSph core_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_LIGHT_ARROW,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK9,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoConHit_e,
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
            /* Radius */ 70.0f,
        }},
    };

    fopAc_ac_c* actor = a_this;
    bgn3_class* i_this = (bgn3_class*)a_this;
    fopAcM_SetupActor(actor, bgn3_class);
    cPhs_State res;
    res = dComIfG_resLoad(&i_this->m002AC, "Bgn");
    if (res == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(actor, useHeapInit, 0x96000)) {
            return cPhs_ERROR_e;
        }
        if (hio_set == 0) {
            i_this->m100B0 = 1;
            hio_set = 1;
            l_HIO.mNo = mDoHIO_createChild("Ｇ（ハヤムシ）", &l_HIO); // G (Fast worm)
        }
        i_this->m0FDC0.Init(0xff, 0xff, actor);
        i_this->m0FF28.Set(cc_sph_src);
        i_this->m0FF28.SetStts(&i_this->m0FDC0);
        i_this->m0FF28.OffAtSetBit();
        i_this->m0FDFC.Set(cc_sph_src);
        i_this->m0FDFC.SetStts(&i_this->m0FDC0);
        i_this->m0FDFC.OffAtSetBit();
        for (s32 i = 0; i < 9; i++) {
            if (i == 8) {
                i_this->mParts[i].m00F8.Set(core_sph_src);
            } else {
                i_this->mParts[i].m00F8.Set(cc_sph_src);
            }
            i_this->mParts[i].m00F8.SetStts(&i_this->m0FDC0);
            i_this->mParts[i].m00F8.OffAtSetBit();
        }
        actor->health = 3;
        actor->max_health = 3;
        ke_color.r = (u8)l_HIO.m50;
        ke_color.g = (u8)l_HIO.m52;
        ke_color.b = (u8)l_HIO.m54;
        ke_color.a = 0xff;
        for (s32 i = 0; i < 9; i++) {
            i_this->mParts[i].m0018 = actor->tevStr;
        }
        daBgn3_Execute(i_this);
    }
    return res;
}

static actor_method_class l_daBgn3_Method = {
    (process_method_func)daBgn3_Create,
    (process_method_func)daBgn3_Delete,
    (process_method_func)daBgn3_Execute,
    (process_method_func)daBgn3_IsDelete,
    (process_method_func)daBgn3_Draw,
};

actor_process_profile_definition g_profile_BGN3 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BGN3,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bgn3_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BGN3,
    /* Actor SubMtd */ &l_daBgn3_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
