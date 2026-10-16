/**
 * d_a_sitem.cpp
 * Object - Hanging vines with item pods (Forbidden Woods)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_eff.h"
#include "d/actor/d_a_sitem.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/d_particle_name.h"
#include "res/Object/Sitem.h"

static cXyz non_pos;

/* 000000EC-000001FC       .text hand_draw__FP11sitem_class */
void hand_draw(sitem_class* i_this) {
    if (i_this->field_0x2C0 < 6) {
        J3DModel* model = i_this->mpModel;
        g_env_light.setLightTevColorType(model, &i_this->actor.tevStr);
        mDoExt_modelUpdateDL(model);
    }

    i_this->mVineLineMat.update(10, (GXColor){0x00, 0xB4, 0x32, 0xFF}, &i_this->actor.tevStr);

    dComIfGd_set3DlineMat(&i_this->mVineLineMat);

    if (i_this->field_0x308 > 0.1f) {
        i_this->mVineStubLineMat.update(5, (GXColor){0x00, 0xB4, 0x32, 0xFF}, &i_this->actor.tevStr);
        dComIfGd_set3DlineMat(&i_this->mVineStubLineMat);
    }
}

/* 000001FC-00000248       .text daSitem_Draw__FP11sitem_class */
static BOOL daSitem_Draw(sitem_class* i_this) {
    g_env_light.settingTevStruct(0 /* TODO: Actor enum */, &i_this->actor.eyePos, &i_this->actor.tevStr);
    hand_draw(i_this);

    return TRUE;
}

/* 00000248-0000034C       .text hand_mtx_set__FP11sitem_class */
void hand_mtx_set(sitem_class* i_this) {
    MtxTrans(i_this->field_0x2E0.x, i_this->field_0x2E0.y, i_this->field_0x2E0.z, false);

    cMtx_XrotM(*calc_mtx, i_this->field_0x2EC);
    cMtx_YrotM(*calc_mtx, i_this->field_0x2EE);
    cMtx_XrotM(*calc_mtx, REG12_S(1) + 0x4000);

    cXyz pos(0.0f, REG12_F(4) + -60.0f, 0.0f);
    MtxPosition(&pos, &i_this->field_0xB00);

    MtxTrans(0.0, REG12_F(3) + -50.0f, 0.0, true);

    J3DModel* model = i_this->mpModel;
    model->setBaseTRMtx(*calc_mtx);
}

static f32 size_d[] = {10.0f, 10.0f, 9.5f, 9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.5f};

/* 00000388-00000410       .text control3__FP11sitem_class */
void control3(sitem_class* i_this) {
    sitem_s* cur = i_this->mVinePoints;
    for (int i = 0; i < 10; i++, cur++) {
        f32 fVar1 = cM_ssin(i_this->field_0x2BC * 500 + i * 100);

        f32 fVar2 = 0.8f + 0.1f * fVar1;
        cur->field_0x18 = fVar2 * size_d[i];
    }
}

/* 00000410-00000748       .text control1__FP11sitem_class */
void control1(sitem_class* i_this) {
    static f32 g_d[10] = {50.0f, 50.0f, 35.0f, 25.0f, 15.0f, 9.0f, 6.0f, 6.0f, 6.0f, 6.0f};

    i_this->mVinePoints[0].pos = i_this->actor.current.pos;

    int i;
    sitem_s *vine_i = &i_this->mVinePoints[1];

    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);

    cXyz local_a4;
    local_a4.x = 0;
    local_a4.y = 0;
    local_a4.z = i_this->field_0x2FC;

    cXyz local_b0;
    cXyz local_bc;
    MtxPosition(&local_a4, &local_bc);

    local_a4.z = i_this->field_0x2F4;

    f32 vec_x;
    f32 vec_y;
    f32 vec_z;
    f32 scale;
    float fVar1;

    s16 iVar9;
    s32 iVar8;

    fVar1 = i_this->field_0x300;
    for (i = 1; i < 9; i++, vine_i++) {
        local_b0.x = fVar1 * cM_ssin(i_this->field_0x2BC * (REG0_S(5) + 0x44c) + i * (REG0_S(6) + 4000));
        local_b0.y = g_d[i];
        local_b0.z = fVar1 * cM_scos(i_this->field_0x2BC * (REG0_S(7) + 800) + i * (REG0_S(8) + 4000));
        
        scale = 1.0f;
        cXyz local_c8;
        MtxPosition(&local_b0, &local_c8);

        vec_x = local_c8.x * scale +
            ((vine_i->pos.x - vine_i[-1].pos.x) +
             local_bc.x * scale);

        vec_y = local_c8.y * scale +
            ((vine_i->pos.y - vine_i[-1].pos.y) +
             local_bc.y * scale);

        vec_z = local_c8.z * scale +
            ((vine_i->pos.z - vine_i[-1].pos.z) +
             local_bc.z * scale);

        iVar8 = cM_atan2s(vec_x, vec_z);
        iVar9 = -cM_atan2s(vec_y, std::sqrtf(vec_x * vec_x + vec_z * vec_z));

        MtxPush();
        mDoMtx_YrotS(*calc_mtx, (s16) iVar8);
        mDoMtx_XrotM(*calc_mtx, iVar9);

        MtxPosition(&local_a4, &local_b0);
        MtxPull();

        vine_i->pos = vine_i[-1].pos + local_b0;
    }
}

/* 00000748-000009E8       .text control2__FP11sitem_class */
void control2(sitem_class* i_this) {
    cXyz local_6c;
    local_6c.x = 0.0f;
    local_6c.y = 0.0f;
    local_6c.z = i_this->field_0x2F4;

    i_this->mVinePoints[9].pos = i_this->field_0x2C8;

    f32 delta_x;
    f32 delta_y;
    f32 delta_z;

    int i;
    s16 angle_1;
    s32 angle_0;
    sitem_s *vine_i;

    vine_i = &i_this->mVinePoints[8];
    for (i = 8; i >= 1; i--, vine_i--) {
        delta_x = vine_i->pos.x - vine_i[1].pos.x;
        delta_y = vine_i->pos.y - vine_i[1].pos.y;
        delta_z = vine_i->pos.z - vine_i[1].pos.z;

        angle_0 = cM_atan2s(delta_x, delta_z);
        
        angle_1 = -cM_atan2s(delta_y, std::sqrtf(delta_x * delta_x + delta_z * delta_z));

        mDoMtx_YrotS(*calc_mtx, angle_0);
        mDoMtx_XrotM(*calc_mtx, angle_1);

        local_6c.z = i_this->field_0x2F4;

        cXyz cStack_78;
        MtxPosition(&local_6c, &cStack_78);

        vine_i->pos = vine_i[1].pos + cStack_78;
    }

    i_this->field_0x2E0 = i_this->mVinePoints[9].pos;

    local_6c = i_this->mVinePoints[8].pos - i_this->mVinePoints[9].pos;
    i_this->field_0x2EC = -cM_atan2s(local_6c.y, local_6c.z);
    i_this->field_0x2EE = cM_atan2s(local_6c.x, std::sqrtf(local_6c.y * local_6c.y + local_6c.z * local_6c.z));
    
    hand_mtx_set(i_this);
}

/* 000009E8-00000E2C       .text cut_control1__FP11sitem_class */
void cut_control1(sitem_class* i_this) {
    i_this->mVineStubPoints[0].pos = i_this->actor.current.pos;

    int i;
    sitem_s* stub_i = &i_this->mVineStubPoints[1];

    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);

    cXyz local_a0;
    local_a0.z = i_this->field_0x308;

    f32 fVar2;
    f32 fVar3;
    f32 fVar4;
    f32 fVar1;

    s16 iVar6;
    s32 iVar5;

    fVar1 = REG0_F(0x12) + 50.0f;

    for (i = 1; i < 5; i++, stub_i++) {
        cXyz local_ac;
        local_ac.x = fVar1 * cM_ssin(i_this->field_0x2BC * (REG0_S(5) + 0x1004) + i * (REG0_S(6) + 10000));
        local_ac.y = REG0_F(0x11) + 50.0f;
        local_ac.z = fVar1 * cM_scos(i_this->field_0x2BC * (REG0_S(7) + 0x1130) + i * (REG0_S(8) + 10000));

        cXyz local_b8;
        MtxPosition(&local_ac, &local_b8);

        fVar2 = local_b8.x + (stub_i->pos.x - stub_i[-1].pos.x);
        fVar3 = local_b8.y + (stub_i->pos.y - stub_i[-1].pos.y);
        fVar4 = local_b8.z + (stub_i->pos.z - stub_i[-1].pos.z);

        iVar5 = cM_atan2s(fVar2, fVar4);
        fVar2 = std::sqrtf(fVar2 * fVar2 + fVar4 * fVar4);

        iVar6 = -cM_atan2s(fVar3, fVar2);
        MtxPush();

        cMtx_YrotS(*calc_mtx, iVar5);
        cMtx_XrotM(*calc_mtx, iVar6);

        MtxPosition(&local_a0, &local_ac);
        MtxPull();

        stub_i->pos = stub_i[-1].pos + local_ac;
    }

#if VERSION == VERSION_DEMO
    JPABaseEmitter* emitter = i_this->mpParticleEmitter[0];
#else
    JPABaseEmitter* emitter = i_this->mParticleCallback[0].getEmitter();
#endif

    if (!emitter && i_this->field_0xD4C) {
        i_this->mParticleCallback[0].end();

#if VERSION == VERSION_DEMO
        i_this->mpParticleEmitter[0] = dComIfGp_particle_set(0x8184, &i_this->mVineStubPoints[4].pos, &i_this->field_0xD40[0], NULL, 0xFF, &i_this->mParticleCallback[0], fopAcM_GetRoomNo(&i_this->actor), NULL, NULL, NULL);;
#else
        dComIfGp_particle_set(0x8184, &i_this->mVineStubPoints[4].pos, &i_this->field_0xD40[0], NULL, 0xFF, &i_this->mParticleCallback[0], fopAcM_GetRoomNo(&i_this->actor), NULL, NULL, NULL);
#endif

        i_this->field_0x2C6 = 0x3C;
    } else {
        local_a0 = i_this->mVineStubPoints[4].pos - i_this->mVineStubPoints[3].pos;

        s16 iVar8 = cM_atan2s(local_a0.x, local_a0.z);

        i_this->field_0xD40[0].y = iVar8;
        f32 fVar1 = std::sqrtf(local_a0.x * local_a0.x + local_a0.z * local_a0.z);

        iVar8 = cM_atan2s(local_a0.y, fVar1);
        i_this->field_0xD40[0].x = -iVar8;

#if VERSION == VERSION_DEMO
        if (i_this->field_0x2C6 == 1 && i_this->mpParticleEmitter[0]) {
            i_this->mpParticleEmitter[0]->becomeInvalidEmitter();
            i_this->mpParticleEmitter[0] = NULL;
        }
#else
        if (i_this->field_0x2C6 == 1 && i_this->mParticleCallback[0].getEmitter() != NULL) {
            i_this->mParticleCallback[0].end();
        }
#endif
    }
}

/* 00000E2C-00001058       .text my_break__FP11sitem_class */
void my_break(sitem_class* i_this) {
    i_this->field_0x2C2[0] = 0x32;
    i_this->field_0x2C0 = 6;

    csXyz acStack_18(0, i_this->actor.current.angle.y, 0);
    fopAcM_createItemFromTable(&i_this->field_0x2C8, i_this->mItemTableNo, i_this->mItemBit & 0x7F, fopAcM_GetHomeRoomNo(&i_this->actor), 0, &acStack_18, 1, NULL);

    if (i_this->mPodType <= 1) {
        dComIfGp_particle_set(0x8168, &i_this->field_0x2C8, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);

        dComIfGp_particle_set(0x8167, &i_this->field_0x2C8, NULL, NULL, 0xFF, NULL, -1, &i_this->actor.tevStr.mColorK0, &i_this->actor.tevStr.mColorK0, NULL);

        if (i_this->mPodType == 1) {
            dComIfGp_particle_set(0x8169, &i_this->field_0x2C8, NULL, NULL, 0xFF, NULL, -1, &i_this->actor.tevStr.mColorK0, &i_this->actor.tevStr.mColorK0, NULL);
        }
    }

    if (i_this->mPodType == 2) {
        dComIfGp_particle_set(0x816a, &i_this->field_0x2C8, NULL, NULL, 0xFF, NULL, -1, &i_this->actor.tevStr.mColorK0, &i_this->actor.tevStr.mColorK0, NULL);
    }

#if VERSION > VERSION_DEMO
    fopAcM_seStart(&i_this->actor, 0x6936, 0);
#endif

    daObjEff::Act_c::make_pinecone_smoke(&i_this->field_0x2C8);
}

/* 00001094-000015C0       .text cut_control2__FP11sitem_class */
void cut_control2(sitem_class* i_this) {
    cXyz local_b0;
    cXyz local_ec;
    cXyz local_c8;
    local_b0.x = 0.0;
    local_b0.y = 0.0;
    local_b0.z = i_this->field_0x2F4;

    i_this->mVinePoints[9].pos = i_this->field_0x2C8;

    int i;
    sitem_s *vine_i = &i_this->mVinePoints[8];

    f32 fVar3;
    f32 fVar4;
    f32 fVar2;
    f32 fVar5;
    f32 fVar6;
    f32 fVar1;

    s16 iVar7;
    s32 angle_0;
    s16 iVar9;

    fVar1 = i_this->field_0x300;

    for (i = 8; i >= 0; i--, vine_i--) {
        local_c8.x = fVar1 * JMASSin(i_this->field_0x2BC * (REG0_S(5) + 0x9C4) + i * (REG0_S(6) + 3000));
        local_c8.y = fVar1 * JMASSin(i_this->field_0x2BC * (REG0_S(5) + 0xB86) + i * (REG0_S(6) + 4000));
        local_c8.z = fVar1 * JMASCos(i_this->field_0x2BC * (REG0_S(7) + 0xAF0) + i * (REG0_S(8) + 0xDAC));

        fVar3 = local_c8.x + (vine_i->pos.x - vine_i[1].pos.x);

        fVar4 = (vine_i->pos.y - 10.0f) + local_c8.y;
        fVar2 = i_this->field_0x304 + 5.0f;

        if (fVar4 < fVar2) {
            fVar4 = fVar2;
        }

        fVar6 = fVar4 - vine_i[1].pos.y;

        fVar5 = local_c8.z + ((vine_i->pos).z - vine_i[1].pos.z);

        angle_0 = cM_atan2s(fVar3, fVar5);

        iVar7 = -cM_atan2s(fVar6, std::sqrtf(fVar3 * fVar3 + fVar5 * fVar5));

        cMtx_YrotS(*calc_mtx, angle_0);
        cMtx_XrotM(*calc_mtx, iVar7);

        local_b0.z = i_this->field_0x2F4;

        MtxPosition(&local_b0, &local_ec);
        vine_i->pos = vine_i[1].pos + local_ec;
    }

    i_this->field_0x2E0 = i_this->mVinePoints[9].pos;
    local_b0 = i_this->mVinePoints[8].pos - i_this->mVinePoints[9].pos;

    iVar9 = cM_atan2s(local_b0.y, local_b0.z);
    i_this->field_0x2EC = -iVar9;

    iVar9 = cM_atan2s(local_b0.x, std::sqrtf(local_b0.y * local_b0.y + local_b0.z * local_b0.z));
    i_this->field_0x2EE = iVar9;
    hand_mtx_set(i_this);

#if VERSION == VERSION_DEMO
    JPABaseEmitter* emitter = i_this->mpParticleEmitter[1];
#else
    JPABaseEmitter* emitter = i_this->mParticleCallback[1].getEmitter();
#endif

    if (!emitter && i_this->field_0xD4C) {
        i_this->mParticleCallback[1].end();

#if VERSION == VERSION_DEMO
        i_this->mpParticleEmitter[1] =
#endif
        dComIfGp_particle_set(0x8184, &i_this->mVinePoints[0].pos, i_this->field_0xD40 + 1, NULL, 0xFF, &i_this->mParticleCallback[1], fopAcM_GetRoomNo(&i_this->actor), NULL, NULL, NULL);
    } else {
        local_b0 = i_this->mVinePoints[0].pos - i_this->mVinePoints[1].pos;

        iVar9 = cM_atan2s(local_b0.x, local_b0.z);

        i_this->field_0xD40[1].y = iVar9;

        iVar9 = cM_atan2s(local_b0.y, std::sqrtf(local_b0.x * local_b0.x + local_b0.z * local_b0.z));
        i_this->field_0xD40[1].x = -iVar9;

#if VERSION == VERSION_DEMO
        if (i_this->field_0x2C6 == 1 && i_this->mpParticleEmitter[1]) {
            i_this->mpParticleEmitter[1]->becomeInvalidEmitter();
            i_this->mpParticleEmitter[1] = NULL;
            i_this->field_0xD4C = 0;
        }
#else
        if (i_this->field_0x2C6 == 1 && i_this->mParticleCallback[1].getEmitter() != NULL) {
            i_this->mParticleCallback[1].end();
            i_this->field_0xD4C = 0;
        }
#endif
    }
}

static f32 hr_d[4] = {10.0f, 25.0f, 40.0f, 65.0f};
static f32 max_d[4] = {100.0f, 250.0f, 400.0f, 600.0f};

/* 000015C0-00002304       .text hand_move__FP11sitem_class */
void hand_move(sitem_class* i_this) {
    /* Nonmatching - demo only */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    f32 fVar17;
    f32 fVar16;
    f32 zero;
    float fVar1;
    float fVar14;
    float fVar15;
    u8 *puVar3;
    cXyz *pcVar4;
    bool bVar6;
    short sVar5;
    sitem_s *psVar7;
    cXyz *pcVar8;
    int iVar9;
    int iVar11;
    int iVar10;
    int iVar12;
    float fVar13;
    cXyz local_120;
    cXyz cStack_12c;
    cXyz local_138;
    cXyz local_144;
    cXyz local_150;
    cXyz local_174;
    CcAtInfo local_114;
    dBgS_GndChk local_f8;
    long long local_a0;

    bVar6 = false;

    fVar17 = 0.1f;
    fVar16 = 8.0f;
    zero = 0.0f;
    fVar14 = 1.0f;
    fVar15 = REG0_F(0xB) + 5.0f;

    fVar1 = REG0_F(5) + hr_d[i_this->field_0x2B9];
    fVar13 = max_d[i_this->field_0x2B9];

    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);

    sVar5 = i_this->field_0x2C0;

    switch (sVar5) {
        case 0:
        case 1:
            local_120.x = (REG0_F(0xD) + 25.0f) * cM_ssin(i_this->field_0x2BC * 600);
            local_120.y = fVar13;
            local_120.z = (REG0_F(0xD) + 25.0f) * cM_ssin(i_this->field_0x2BC * 700);

            MtxPosition(&local_120, &cStack_12c);

            local_138 = i_this->actor.current.pos + cStack_12c;
            if (i_this->field_0x2C0 == 0) {
                i_this->field_0x2C8 = local_138;
                i_this->field_0x2C0 = 1;
            }
            break;
        case 5:
            fVar15 = 50.0f;
            i_this->field_0x300 = 50.0f;
            bVar6 = true;
            fVar1 = 25.0f;

            i_this->field_0x2D4 = i_this->field_0x2C8;

            PSVECAdd(&i_this->field_0x2C8, &i_this->actor.speed, &i_this->field_0x2C8);

            i_this->actor.speed.y -= 3.0f;

            if (i_this->actor.speed.y < -90.0f) {
                i_this->actor.speed.y = -90.0f;
            }

            i_this->mBgAcch.CrrPos(g_dComIfG_gameInfo.play.mBgS);

            i_this->field_0x2C6 = 5;

            if (i_this->actor.speed.y < 0.0f) {
                float x = (i_this->field_0x2C8).x;
                float y = (i_this->field_0x2C8).y;
                float z = (i_this->field_0x2C8).z;

                y += 100.0f;

                local_f8.m_pos.x = x;
                local_f8.m_pos.y = y;
                local_f8.m_pos.z = z;

                i_this->field_0x304 = dComIfG_Bgsp()->GroundCross(&local_f8);

                if (i_this->field_0x304 == -G_CM3D_F_INF || i_this->field_0x2C8.y <= i_this->field_0x304 + 30.0f) {
                    i_this->field_0x2C8.y = i_this->field_0x304 + 30.0f;
                    my_break(i_this);
                }
            }

            break;
        case 6:
            bVar6 = true;
            fVar15 = zero;
            i_this->field_0x2C6 = 10;
            if (i_this->field_0x2C2[0] < 0x28) {
                fVar14 = fVar1 * 0.05f;
                fVar1 = fVar15;
            }

            if (i_this->field_0x2C2[0] == 0) {
                fopAcM_delete(&i_this->actor);
            }
            break;
    }
        
    cLib_addCalc2(&i_this->field_0x2F4, fVar1, 0.5f, fVar14);
    cLib_addCalc2(&i_this->field_0x2FC, zero, 1.0f, 0.2f);
    cLib_addCalc2(&i_this->field_0x300, fVar15, 1.0f, 1.5f);

    if (!bVar6) {
        cLib_addCalc2(&i_this->actor.speedF, fVar16, 1.0f, fVar17);
        if ((i_this->field_0xB0C > 1.0f) && (i_this->field_0x2C0 != 3)) {
            cMtx_YrotS(*calc_mtx, (int)i_this->field_0xB10);

            local_120.x = 0.0f;
            local_120.y = REG6_F(9);
            local_120.z = i_this->field_0xB0C;

            MtxPosition(&local_120, &cStack_12c);
            PSVECAdd(&local_138, &cStack_12c, &local_138);

            fVar17 = 0.1f;
            i_this->actor.speedF = i_this->field_0xB0C * 0.2f;
            if (i_this->actor.speedF > REG6_F(8) + 30.0f) {
                i_this->actor.speedF = REG6_F(8) + 30.0f;
            }
        }
        cLib_addCalc0(&i_this->field_0xB0C, 1.0f, REG6_F(7) + 5.0f);

        cLib_addCalc2(&(i_this->field_0x2C8).x, local_138.x, fVar17, i_this->actor.speedF);
        cLib_addCalc2(&(i_this->field_0x2C8).y, local_138.y, fVar17, i_this->actor.speedF);
        cLib_addCalc2(&(i_this->field_0x2C8).z, local_138.z, fVar17, i_this->actor.speedF);

        control1(i_this);
        control2(i_this);
    } else {
        cut_control1(i_this);
        cut_control2(i_this);
        
        sitem_s* stub = i_this->mVineStubPoints;
        cXyz* positions = i_this->mVineStubLineMat.getPos(0);
        u8* sizes = i_this->mVineStubLineMat.getSize(0);

        for (int i = 0; i < 5; i++, stub++, positions++, sizes++) {
            *positions = stub->pos;
            *sizes = stub->field_0x18;
        }

        cLib_addCalc0(&i_this->field_0x308, 1.0f, REG0_F(1) + 1.0f);
    }

    control3(i_this);
    psVar7 = i_this->mVinePoints;
    pcVar8 = i_this->mVineLineMat.getPos(0);
    puVar3 = i_this->mVineLineMat.getSize(0);

    for (int i = 10; i != 0; i--, psVar7++, pcVar8++, puVar3++) {
        *pcVar8 = psVar7->pos;
        local_a0 = psVar7->field_0x18;
        *puVar3 = psVar7->field_0x18;
    }
    pcVar8 = i_this->mVineLineMat.getPos(0);

    i_this->actor.eyePos = pcVar8[5];
    i_this->actor.attention_info.position = i_this->actor.eyePos;

    i_this->mCcStts.Move();
    if (!bVar6) {
        i_this->mBoomerangSph.SetC(i_this->actor.eyePos);
    }
    else {
        i_this->mBoomerangSph.SetC(non_pos);
    }

    iVar11 = 0;
    dComIfG_Ccsp()->Set(&i_this->mBoomerangSph);
    iVar10 = 0;
    iVar12 = 0;

    for (; iVar10 < 3; iVar10++) {
        int index = ((int)i_this->field_0x2BC & 3U) + iVar10 * 2;
        index = index % 10;

        pcVar4 = pcVar8 + index;
        local_144 = *pcVar4;

        if (!bVar6) {
            i_this->mVinePodSph[iVar10].SetC(local_144);
        }
        else {
            i_this->mVinePodSph[iVar10].SetC(non_pos);
        }

        if (i_this->field_0x2C0 == 3) {
            i_this->mVinePodSph[iVar10].OffCoSetBit();
        } else {
            i_this->mVinePodSph[iVar10].OnCoSetBit();
        }
        dComIfG_Ccsp()->Set(&i_this->mVinePodSph[iVar10]);
    }

    i_this->mVinePodSph[3].SetR(50.0f);
    i_this->mVinePodSph[3].SetC(i_this->field_0xB00);
    i_this->mVinePodSph[3].GetObjCo().OnSPrmBit(1); // TODO: add flag

    dComIfG_Ccsp()->Set(&i_this->mVinePodSph[3]);

    local_114.mpObj = NULL;
    if (i_this->field_0x2C6 == 0) {
        if (i_this->mVinePodSph[3].ChkTgHit() || (i_this->field_0xB0C > 100.0f && i_this->mVinePodSph[3].ChkCoHit())) {
            local_114.mpObj = i_this->mVinePodSph[3].GetTgHitObj();

            if (local_114.mpObj && local_114.mpObj->ChkAtType(AT_TYPE_GRAPPLING_HOOK)) {
                return;
            }

            my_break(i_this);
            iVar11 = 3;
        } else {
            iVar12 = 0;
            for (iVar9 = 0; iVar9 < 3; iVar9++) {
                if (i_this->mVinePodSph[iVar9].ChkTgHit()) {
                    local_114.mpObj = i_this->mVinePodSph[iVar9].GetTgHitObj();
                    if (local_114.mpObj && local_114.mpObj->ChkAtType(AT_TYPE_GRAPPLING_HOOK)) {
                        return;
                    }

                    iVar11 = 1;
                    break;
                }
                iVar12 = iVar12 + 300;
            }

            if (((iVar11 & 0xFF) || (iVar12 = i_this->mBoomerangSph.ChkTgHit(), (u32) iVar12 != 0))
                && (i_this->field_0x2C6 == 0)) {
                i_this->field_0x2C6 = 0x14;
                if (((u8) iVar11) == 0) {
                    local_114.mpObj = i_this->mBoomerangSph.GetTgHitObj();
                    at_power_check(&local_114);

                    if (local_114.mResultingAttackType == 8) {
                        i_this->field_0xB0C = REG6_F(6) + 300.0f;
                        i_this->field_0xB10 = fopAcM_searchPlayerAngleY(&i_this->actor) + 0x8000;
                        return;
                    }
                }
                i_this->field_0x2C0 = 5;
                fVar14 = cM_rndFX(10.0f);
                i_this->actor.speed.x = fVar14;
                fVar14 = cM_rndF(5.0f);
                i_this->actor.speed.y = fVar14 + 10.0f;
                fVar14 = cM_rndFX(10.0f);
                i_this->actor.speed.z = fVar14;
                local_150.x = 0.3f;
                local_150.y = 0.3f;
                local_150.z = 0.3f;
                dComIfGp_particle_set(0x16, &i_this->actor.eyePos, NULL, &local_150, 0xFF, NULL, -1, NULL, NULL, NULL);
                i_this->field_0xD4C = 1;
                iVar11 = 1;
            }
        }
        if (iVar11 & 0xFF) {
            if (local_114.mpObj) {
                def_se_set(&i_this->actor, local_114.mpObj, 0x21);
            }
            psVar7 = i_this->mVinePoints;
            pcVar8 = &i_this->mVineStubPoints[0].pos;
            iVar12 = 0;
            do {
                pcVar8->x = (psVar7->pos).x;
                pcVar8->y = (psVar7->pos).y;
                pcVar8->z = (psVar7->pos).z;
                pcVar8[2].x = psVar7->field_0x18;
                if (iVar12 == 4) {
                    local_174 = *pcVar8 - *(cXyz*)((u8*)pcVar8 - 0x1C);
                    fVar14 = PSVECSquareMag(&local_174);
                    fVar14 = std::sqrtf(fVar14);
                    i_this->field_0x308 = (REG0_F(2) + 1.5f) * fVar14;
                }
                iVar12 = iVar12 + 1;
                psVar7 = psVar7 + 1;
                pcVar8 = (cXyz *)&pcVar8[2].y;
            } while (iVar12 < 5);
        }
    }
}

/* 00002684-000026F4       .text daSitem_Execute__FP11sitem_class */
static BOOL daSitem_Execute(sitem_class* i_this) {
    i_this->field_0x2BC++;

    for (int i = 0; i < 2; i++) {
        if (i_this->field_0x2C2[i] != 0) {
            i_this->field_0x2C2[i]--;
        }
    }

    if (i_this->field_0x2C6 != 0) {
        i_this->field_0x2C6--;
    }

    hand_move(i_this);

    return TRUE;
}

/* 000026F4-000026FC       .text daSitem_IsDelete__FP11sitem_class */
static BOOL daSitem_IsDelete(sitem_class*) {
    return TRUE;
}

/* 000026FC-00002760       .text daSitem_Delete__FP11sitem_class */
static BOOL daSitem_Delete(sitem_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhs, "Sitem");
    i_this->mParticleCallback[0].end();
    i_this->mParticleCallback[1].end();

    return TRUE;
}

#if VERSION == VERSION_DEMO
static u16 bmd_data[3] = {10, 6, 7};
#else
static u16 bmd_data[3] = {4, 5, 6};
#endif

/* 00002760-00002824       .text useHeapInit__FP11sitem_class */
BOOL useHeapInit(sitem_class* i_this) {
    J3DModelData* modelData = (J3DModelData*) dComIfG_getObjectRes("Sitem", bmd_data[i_this->mPodType]);
    i_this->mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);

    if (!i_this->mpModel) {
        return FALSE;
    }
    
    if (!i_this->mVineLineMat.init(1, 10, TRUE)) {
        return FALSE;
    }
    
    if (!i_this->mVineStubLineMat.init(1, 5, 1)) {
        return FALSE;
    }

    return TRUE;
}

/* 00002824-00002844       .text daSitem_solidHeapCB__FP10fopAc_ac_c */
static BOOL daSitem_solidHeapCB(fopAc_ac_c* i_this) {
    useHeapInit((sitem_class*) i_this);
}

/* 00002844-00002C04       .text daSitem_Create__FP10fopAc_ac_c */
static cPhs_State daSitem_Create(fopAc_ac_c* i_this) {
    sitem_class* a_this = (sitem_class*)i_this;
    fopAcM_ct(&a_this->actor, sitem_class);
    
    static dCcD_SrcSph tg_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
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
            /* SrcObjAt  SPrm    */ 0,
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

    cPhs_State phase = dComIfG_resLoad(&a_this->mPhs, "Sitem");
    if (phase == cPhs_COMPLEATE_e) {
        // Retail reads parameters before creating the heap; the demo reads them afterward.
#if VERSION > VERSION_DEMO
        a_this->mPodType = fopAcM_GetParam(i_this) & 0xFF;
        if (a_this->mPodType == 0xFF) {
            a_this->mPodType = 0;
        }

        a_this->field_0x2B9 = (fopAcM_GetParam(i_this) >> 8) & 0xFF;
        if (a_this->field_0x2B9 > 3) {
            a_this->field_0x2B9 = 0;
        }

        a_this->mItemTableNo = (fopAcM_GetParam(i_this) >> 24) & 0xFF;
        if (a_this->mItemTableNo == 0xFF) {
            a_this->mItemTableNo = 0;
        }

        a_this->mItemBit = (fopAcM_GetParam(i_this) >> 16) & 0xFF;
#endif
        if (fopAcM_entrySolidHeap(i_this, daSitem_solidHeapCB, 0x3040)) {
            non_pos.x = 0.0f;
            non_pos.y = 30000.0f;
            non_pos.z = -20000.0f;

#if VERSION == VERSION_DEMO
            a_this->mPodType = fopAcM_GetParam(i_this) & 0xFF;
            if (a_this->mPodType == 0xFF) {
                a_this->mPodType = 0;
            }

            a_this->field_0x2B9 = (fopAcM_GetParam(i_this) >> 8) & 0xFF;
            if (a_this->field_0x2B9 > 3) {
                a_this->field_0x2B9 = 0;
            }

            a_this->mItemTableNo = (fopAcM_GetParam(i_this) >> 24) & 0xFF;
            if (a_this->mItemTableNo == 0xFF) {
                a_this->mItemTableNo = 0;
            }

            a_this->mItemBit = (fopAcM_GetParam(i_this) >> 16) & 0xFF;
#endif

            i_this->health = 2;

            a_this->field_0x2BC = cM_rndF(10000.0f);

            a_this->mCcStts.Init(0xFF, 0xFF, i_this);

            for (int i = 0; i < 4; i++) {
                a_this->mVinePodSph[i].Set(tg_sph_src);
                a_this->mVinePodSph[i].SetStts(&a_this->mCcStts);

                if (a_this->mPodType != 1) {
                    a_this->mVinePodSph[i].OffAtSetBit();
                }
            }

            a_this->mBoomerangSph.Set(bm_sph_src);
            a_this->mBoomerangSph.SetStts(&a_this->mCcStts);
            a_this->field_0x2C8 = i_this->current.pos;

            a_this->mBgAcch.Set(&a_this->field_0x2C8, &a_this->field_0x2D4, i_this, 1, &a_this->mBgAcchCir, fopAcM_GetSpeed_p(&a_this->actor));
            a_this->mBgAcchCir.SetWall(30.0f, 50.0f);

            for (int i = 0; i < 2; i++) {
                daSitem_Execute(a_this);
            }
        } else {
            phase = cPhs_ERROR_e;
        }
    }

    return phase;
}

static actor_method_class l_daSitem_Method = {
    (process_method_func)daSitem_Create,
    (process_method_func)daSitem_Delete,
    (process_method_func)daSitem_Execute,
    (process_method_func)daSitem_IsDelete,
    (process_method_func)daSitem_Draw,
};

actor_process_profile_definition g_profile_SITEM = {
    /* Layer ID     */ fpcLy_CURRENT_e,
    /* List ID      */ 0x0007,
    /* List Prio    */ fpcPi_CURRENT_e,
    /* Proc Name    */ fpcNm_SITEM_e,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(sitem_class),
    /* Size Other   */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Draw Prio    */ fpcDwPi_SITEM_e,
    /* Actor SubMtd */ &l_daSitem_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* Cull Type    */ fopAc_CULLBOX_CUSTOM_e,
};
