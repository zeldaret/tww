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
static void hand_draw(sitem_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if (i_this->field_0x2C0 < 6) {
        J3DModel* model = i_this->mpModel;
        g_env_light.setLightTevColorType(model, &actor->tevStr);
        mDoExt_modelUpdateDL(model);
    }

    i_this->mVineLineMat.update(10, (GXColor){0x00, 0xB4, 0x32, 0xFF}, &actor->tevStr);

    dComIfGd_set3DlineMat(&i_this->mVineLineMat);

    if (i_this->field_0x308 > 0.1f) {
        i_this->mVineStubLineMat.update(5, (GXColor){0x00, 0xB4, 0x32, 0xFF}, &actor->tevStr);
        dComIfGd_set3DlineMat(&i_this->mVineStubLineMat);
    }
}

/* 000001FC-00000248       .text daSitem_Draw__FP11sitem_class */
static BOOL daSitem_Draw(sitem_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->eyePos, &actor->tevStr);
    hand_draw(i_this);

    return TRUE;
}

/* 00000248-0000034C       .text hand_mtx_set__FP11sitem_class */
static void hand_mtx_set(sitem_class* i_this) {
    MtxTrans(i_this->field_0x2E0.x, i_this->field_0x2E0.y, i_this->field_0x2E0.z, false);

    cMtx_XrotM(*calc_mtx, i_this->field_0x2EC);
    cMtx_YrotM(*calc_mtx, i_this->field_0x2EE);
    cMtx_XrotM(*calc_mtx, REG12_S(1) + 0x4000);

    cXyz pos;
    pos.set(0.0f, REG12_F(4) + -60.0f, 0.0f);
    MtxPosition(&pos, &i_this->field_0xB00);

    MtxTrans(0.0, REG12_F(3) + -50.0f, 0.0, true);

    J3DModel* model = i_this->mpModel;
    model->setBaseTRMtx(*calc_mtx);
}

static f32 size_d[] = {10.0f, 10.0f, 9.5f, 9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.5f};

/* 00000388-00000410       .text control3__FP11sitem_class */
static void control3(sitem_class* i_this) {
    sitem_s* cur = i_this->mVinePoints;
    for (int i = 0; i < 10; i++, cur++) {
        f32 fVar1 = cM_ssin(i_this->field_0x2BC * 500 + i * 100);

        f32 fVar2 = 0.8f + 0.1f * fVar1;
        cur->field_0x18 = fVar2 * size_d[i];
    }
}

/* 00000410-00000748       .text control1__FP11sitem_class */
static void control1(sitem_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    static f32 g_d[10] = {50.0f, 50.0f, 35.0f, 25.0f, 15.0f, 9.0f, 6.0f, 6.0f, 6.0f, 6.0f};

    i_this->mVinePoints[0].pos = actor->current.pos;

    int i;
    sitem_s *vine_i = &i_this->mVinePoints[1];

    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);

    cXyz local_a4;
    local_a4.x = 0;
    local_a4.y = 0;
    local_a4.z = i_this->field_0x2FC;

    cXyz local_b0;
    cXyz local_bc;
    MtxPosition(&local_a4, &local_bc);

    local_a4.z = i_this->field_0x2F4;

    Vec vec;
    f32 scale;
    f32 fVar1;

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

        vec.x = local_c8.x * scale +
            ((vine_i->pos.x - vine_i[-1].pos.x) +
             local_bc.x * scale);

        vec.y = local_c8.y * scale +
            ((vine_i->pos.y - vine_i[-1].pos.y) +
             local_bc.y * scale);

        vec.z = local_c8.z * scale +
            ((vine_i->pos.z - vine_i[-1].pos.z) +
             local_bc.z * scale);

        iVar8 = cM_atan2s(vec.x, vec.z);
        iVar9 = -cM_atan2s(vec.y, std::sqrtf(vec.x * vec.x + vec.z * vec.z));

        MtxPush();
        cMtx_YrotS(*calc_mtx, iVar8);
        cMtx_XrotM(*calc_mtx, iVar9);

        MtxPosition(&local_a4, &local_b0);
        MtxPull();

        vine_i->pos = vine_i[-1].pos + local_b0;
    }
}

/* 00000748-000009E8       .text control2__FP11sitem_class */
static void control2(sitem_class* i_this) {
    cXyz local_6c;
    local_6c.x = 0.0f;
    local_6c.y = 0.0f;
    local_6c.z = i_this->field_0x2F4;

    i_this->mVinePoints[9].pos = i_this->field_0x2C8;

    int i;
    s16 angle_1;
    s32 angle_0;
    sitem_s *vine_i = &i_this->mVinePoints[8];
    
    for (i = 8; i >= 1; i--, vine_i--) {
        Vec delta;
        delta.x = vine_i->pos.x - vine_i[1].pos.x;
        delta.y = vine_i->pos.y - vine_i[1].pos.y;
        delta.z = vine_i->pos.z - vine_i[1].pos.z;

        angle_0 = cM_atan2s(delta.x, delta.z);
        
        angle_1 = -cM_atan2s(delta.y, std::sqrtf(delta.x * delta.x + delta.z * delta.z));

        cMtx_YrotS(*calc_mtx, angle_0);
        cMtx_XrotM(*calc_mtx, angle_1);

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
static void cut_control1(sitem_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->mVineStubPoints[0].pos = actor->current.pos;

    int i;
    sitem_s* stub_i = &i_this->mVineStubPoints[1];

    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);

    cXyz local_a0;
    local_a0.z = i_this->field_0x308;

    Vec vec;
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

        vec.x = local_b8.x + (stub_i->pos.x - stub_i[-1].pos.x);
        vec.y = local_b8.y + (stub_i->pos.y - stub_i[-1].pos.y);
        vec.z = local_b8.z + (stub_i->pos.z - stub_i[-1].pos.z);

        iVar5 = cM_atan2s(vec.x, vec.z);
        vec.x = std::sqrtf(vec.x * vec.x + vec.z * vec.z);

        iVar6 = -cM_atan2s(vec.y, vec.x);
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
        i_this->mParticleCallback[0].remove();

#if VERSION == VERSION_DEMO
        i_this->mpParticleEmitter[0] = 
#endif
        dComIfGp_particle_set(
            dPa_name::ID_IT_SN_TSURU_TAIEKI00,
            &i_this->mVineStubPoints[4].pos, &i_this->field_0xD40[0], NULL,
            0xFF, &i_this->mParticleCallback[0], fopAcM_GetRoomNo(actor)
        );

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
static void my_break(sitem_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    i_this->field_0x2C2[0] = 0x32;
    i_this->field_0x2C0 = 6;

    csXyz acStack_18(0, actor->current.angle.y, 0);
    fopAcM_createItemFromTable(&i_this->field_0x2C8, i_this->mItemTableNo, i_this->mItemBit & 0x7F, fopAcM_GetHomeRoomNo(actor), 0, &acStack_18, 1, NULL);

    if (i_this->mPodType <= 1) {
        dComIfGp_particle_set(dPa_name::ID_IT_SN_BOKKURI_TANE00, &i_this->field_0x2C8);

        dComIfGp_particle_set(dPa_name::ID_IT_SN_BOKKURI_HAHEN00, &i_this->field_0x2C8, NULL, NULL, 0xFF, NULL, -1, &actor->tevStr.mColorK0, &actor->tevStr.mColorK0);

        if (i_this->mPodType == 1) {
            dComIfGp_particle_set(dPa_name::ID_IT_SN_BOKKURI_TOGE00, &i_this->field_0x2C8, NULL, NULL, 0xFF, NULL, -1, &actor->tevStr.mColorK0, &actor->tevStr.mColorK0);
        }
    }

    if (i_this->mPodType == 2) {
        dComIfGp_particle_set(dPa_name::ID_IT_SN_BOKKURI_MATSU00, &i_this->field_0x2C8, NULL, NULL, 0xFF, NULL, -1, &actor->tevStr.mColorK0, &actor->tevStr.mColorK0);
    }

#if VERSION > VERSION_DEMO
    fopAcM_seStart(actor, JA_SE_OBJ_BREAK_CHAIR, 0);
#endif

    daObjEff::Act_c::make_pinecone_smoke(&i_this->field_0x2C8);
}

/* 00001094-000015C0       .text cut_control2__FP11sitem_class */
static void cut_control2(sitem_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    cXyz local_b0;
    cXyz local_ec;
    cXyz local_c8;
    local_b0.x = 0.0;
    local_b0.y = 0.0;
    local_b0.z = i_this->field_0x2F4;

    i_this->mVinePoints[9].pos = i_this->field_0x2C8;

    int i;
    sitem_s *vine_i = &i_this->mVinePoints[8];

    Vec vec;
    f32 fVar4;
    f32 fVar2;
    f32 fVar1;

    s16 iVar7;
    s32 angle_0;
    s16 iVar9;

    fVar1 = i_this->field_0x300;

    for (i = 8; i >= 0; i--, vine_i--) {
        local_c8.x = fVar1 * cM_ssin(i_this->field_0x2BC * (REG0_S(5) + 0x9C4) + i * (REG0_S(6) + 3000));
        local_c8.y = fVar1 * cM_ssin(i_this->field_0x2BC * (REG0_S(5) + 0xB86) + i * (REG0_S(6) + 4000));
        local_c8.z = fVar1 * cM_scos(i_this->field_0x2BC * (REG0_S(7) + 0xAF0) + i * (REG0_S(8) + 0xDAC));

        vec.x = local_c8.x + (vine_i->pos.x - vine_i[1].pos.x);

        fVar4 = (vine_i->pos.y - 10.0f) + local_c8.y;
        fVar2 = i_this->field_0x304 + 5.0f;

        if (fVar4 < fVar2) {
            fVar4 = fVar2;
        }

        vec.y = fVar4 - vine_i[1].pos.y;

        vec.z = local_c8.z + ((vine_i->pos).z - vine_i[1].pos.z);

        angle_0 = cM_atan2s(vec.x, vec.z);

        iVar7 = -cM_atan2s(vec.y, std::sqrtf(vec.x * vec.x + vec.z * vec.z));

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
        i_this->mParticleCallback[1].remove();

#if VERSION == VERSION_DEMO
        i_this->mpParticleEmitter[1] =
#endif
        dComIfGp_particle_set(
            dPa_name::ID_IT_SN_TSURU_TAIEKI00,
            &i_this->mVinePoints[0].pos, i_this->field_0xD40 + 1, NULL,
            0xFF, &i_this->mParticleCallback[1], fopAcM_GetRoomNo(actor)
        );
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
static void hand_move(sitem_class* i_this) {
    /* Nonmatching - demo only */
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    f32 fVar17;
    f32 fVar16;
    f32 zero;
    f32 fVar1;
    f32 fVar14;
    f32 fVar15;
    u8 *puVar3;
    bool bVar6;
    s16 sVar5;
    sitem_s *vine_i;
    cXyz *pcVar8;
    u8 iVar11;
    f32 fVar13;
    cXyz local_120;
    cXyz cStack_12c;
    cXyz local_138;
    cXyz local_144;
    cXyz local_150;
    CcAtInfo at_info;
    dBgS_GndChk local_f8;

    bVar6 = false;

    fVar17 = 0.1f;
    fVar16 = 8.0f;
    zero = 0.0f;
    fVar14 = 1.0f;
    fVar15 = REG0_F(0xB) + 5.0f;

    fVar1 = REG0_F(5) + hr_d[i_this->field_0x2B9];
    fVar13 = max_d[i_this->field_0x2B9];

    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    cMtx_XrotM(*calc_mtx, actor->current.angle.x);

    sVar5 = i_this->field_0x2C0;

    switch (sVar5) {
        case 0:
        case 1:
            local_120.x = (REG0_F(0xD) + 25.0f) * cM_ssin(i_this->field_0x2BC * 600);
            local_120.y = fVar13;
            local_120.z = (REG0_F(0xD) + 25.0f) * cM_ssin(i_this->field_0x2BC * 700);

            MtxPosition(&local_120, &cStack_12c);

            local_138 = actor->current.pos + cStack_12c;
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
            i_this->field_0x2C8 += actor->speed;

            actor->speed.y -= 3.0f;
            if (actor->speed.y < -90.0f) {
                actor->speed.y = -90.0f;
            }

            i_this->mBgAcch.CrrPos(*dComIfG_Bgsp());
            i_this->field_0x2C6 = 5;

            if (actor->speed.y < 0.0f) {
                Vec vec;
                vec = i_this->field_0x2C8;
                vec.y += 100.0f;
                local_f8.SetPos(&vec);

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
                fopAcM_delete(actor);
            }
            break;
    }
        
    cLib_addCalc2(&i_this->field_0x2F4, fVar1, 0.5f, fVar14);
    cLib_addCalc2(&i_this->field_0x2FC, zero, 1.0f, 0.2f);
    cLib_addCalc2(&i_this->field_0x300, fVar15, 1.0f, 1.5f);

    if (!bVar6) {
        cLib_addCalc2(&actor->speedF, fVar16, 1.0f, fVar17);
        if ((i_this->field_0xB0C > 1.0f) && (i_this->field_0x2C0 != 3)) {
            cMtx_YrotS(*calc_mtx, (s16)i_this->field_0xB10);

            local_120.x = 0.0f;
            local_120.y = REG6_F(9);
            local_120.z = i_this->field_0xB0C;

            MtxPosition(&local_120, &cStack_12c);
            
            local_138 += cStack_12c;

            fVar17 = 0.1f;
            actor->speedF = i_this->field_0xB0C * 0.2f;
            if (actor->speedF > REG6_F(8) + 30.0f) {
                actor->speedF = REG6_F(8) + 30.0f;
            }
        }
        cLib_addCalc0(&i_this->field_0xB0C, 1.0f, REG6_F(7) + 5.0f);

        cLib_addCalc2(&i_this->field_0x2C8.x, local_138.x, fVar17, actor->speedF);
        cLib_addCalc2(&i_this->field_0x2C8.y, local_138.y, fVar17, actor->speedF);
        cLib_addCalc2(&i_this->field_0x2C8.z, local_138.z, fVar17, actor->speedF);

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
    vine_i = i_this->mVinePoints;
    pcVar8 = i_this->mVineLineMat.getPos(0);
    puVar3 = i_this->mVineLineMat.getSize(0);

    for (int i = 10; i != 0; i--, vine_i++, pcVar8++, puVar3++) {
        *pcVar8 = vine_i->pos;
        *puVar3 = vine_i->field_0x18;
    }
    pcVar8 = i_this->mVineLineMat.getPos(0);

    actor->eyePos = pcVar8[5];
    actor->attention_info.position = actor->eyePos;

    i_this->mCcStts.Move();
    if (!bVar6) {
        i_this->mBoomerangSph.SetC(actor->eyePos);
    }
    else {
        i_this->mBoomerangSph.SetC(non_pos);
    }

    iVar11 = 0;
    dComIfG_Ccsp()->Set(&i_this->mBoomerangSph);

    for (int i = 0; i < 3; i++) {
        int index = (i_this->field_0x2BC & 3U) + i * 2;
        index %= 10;

        local_144 = pcVar8[index];

        if (!bVar6) {
            i_this->mVinePodSph[i].SetC(local_144);
        }
        else {
            i_this->mVinePodSph[i].SetC(non_pos);
        }

        if (i_this->field_0x2C0 == 3) {
            i_this->mVinePodSph[i].OffCoSetBit();
        } else {
            i_this->mVinePodSph[i].OnCoSetBit();
        }

        dComIfG_Ccsp()->Set(&i_this->mVinePodSph[i]);
    }

    i_this->mVinePodSph[3].SetR(50.0f);
    i_this->mVinePodSph[3].SetC(i_this->field_0xB00);
    i_this->mVinePodSph[3].OnCoSetBit();

    dComIfG_Ccsp()->Set(&i_this->mVinePodSph[3]);

    at_info.mpObj = NULL;
    if (i_this->field_0x2C6 == 0) {
        if (i_this->mVinePodSph[3].ChkTgHit() || (i_this->field_0xB0C > 100.0f && i_this->mVinePodSph[3].ChkCoHit())) {
            at_info.mpObj = i_this->mVinePodSph[3].GetTgHitObj();

            if (at_info.mpObj && at_info.mpObj->ChkAtType(AT_TYPE_GRAPPLING_HOOK)) {
                return;
            }

            my_break(i_this);
            iVar11 = 3;
        } else {
            for (int i = 0; i < 3; i++) {
                if (i_this->mVinePodSph[i].ChkTgHit()) {
                    at_info.mpObj = i_this->mVinePodSph[i].GetTgHitObj();
                    if (at_info.mpObj && at_info.mpObj->ChkAtType(AT_TYPE_GRAPPLING_HOOK)) {
                        return;
                    }

                    iVar11 = 1;
                    break;
                }
            }

            if ((iVar11 || i_this->mBoomerangSph.ChkTgHit()) && (i_this->field_0x2C6 == 0)) {
                i_this->field_0x2C6 = 0x14;
                if (iVar11 == 0) {
                    at_info.mpObj = i_this->mBoomerangSph.GetTgHitObj();
                    at_power_check(&at_info);

                    if (at_info.mResultingAttackType == 8) {
                        i_this->field_0xB0C = REG6_F(6) + 300.0f;
                        i_this->field_0xB10 = fopAcM_searchPlayerAngleY(actor) + 0x8000;
                        return;
                    }
                }
                i_this->field_0x2C0 = 5;

                actor->speed.x = cM_rndFX(10.0f);
                actor->speed.y = cM_rndF(5.0f) + 10.0f;
                actor->speed.z = cM_rndFX(10.0f);
                
                local_150.x = 0.3f;
                local_150.y = 0.3f;
                local_150.z = 0.3f;
                
                dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUFLASH, &actor->eyePos, NULL, &local_150);
                i_this->field_0xD4C = 1;
                iVar11 = 1;
            }
        }
        if (iVar11) {
            if (at_info.mpObj) {
                def_se_set(actor, at_info.mpObj, 0x21);
            }
            
            sitem_s* vine_i = vine_i = i_this->mVinePoints;
            sitem_s* stub_i = i_this->mVineStubPoints;
            for (int i = 0; i < 5; i++, vine_i++, stub_i++) {
                stub_i->pos = vine_i->pos;
                stub_i->field_0x18 = vine_i->field_0x18;

                if (i == 4) {
                    cXyz diff = stub_i->pos - stub_i[-1].pos;
                    i_this->field_0x308 = (REG0_F(2) + 1.5f) * diff.abs();
                }
            }
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
    fopAcM_RegisterDeleteID(i_this);
    dComIfG_resDeleteDemo(&i_this->mPhs, "Sitem");
    i_this->mParticleCallback[0].remove();
    i_this->mParticleCallback[1].remove();

    return TRUE;
}

static u16 bmd_data[3] = {
    dRes_INDEX_SITEM_BDL_KMI_00_e,
    dRes_INDEX_SITEM_BDL_KMI_01_e,
    dRes_INDEX_SITEM_BDL_KMI_02_e,
};

/* 00002760-00002824       .text useHeapInit__FP11sitem_class */
static BOOL useHeapInit(sitem_class* i_this) {
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
    return useHeapInit((sitem_class*) i_this);
}

/* 00002844-00002C04       .text daSitem_Create__FP10fopAc_ac_c */
static cPhs_State daSitem_Create(fopAc_ac_c* i_this) {
    fopAcM_RegisterCreateID(i_this);
    sitem_class* a_this = (sitem_class*)i_this;
    fopAcM_ct(i_this, sitem_class);
    
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
            non_pos.set(0.0f, 30000.0f, -20000.0f);

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
