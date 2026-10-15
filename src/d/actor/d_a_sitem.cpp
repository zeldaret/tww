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
    if (i_this->mAction < 6) {
        J3DModel* model = i_this->mpModel;
        g_env_light.setLightTevColorType(model, &i_this->actor.tevStr);
        mDoExt_modelUpdateDL(model);
    }

    i_this->mVineLineMat.update(10, (GXColor){0x00, 0xB4, 0x32, 0xFF}, &i_this->actor.tevStr);

    dComIfGd_set3DlineMat(&i_this->mVineLineMat);

    if (i_this->mVineStubSegmentLength > 0.1f) {
        i_this->mVineStubLineMat.update(5, (GXColor){0x00, 0xB4, 0x32, 0xFF}, &i_this->actor.tevStr);
        dComIfGd_set3DlineMat(&i_this->mVineStubLineMat);
    }
}

/* 000001FC-00000248       .text daSitem_Draw__FP11sitem_class */
static BOOL daSitem_Draw(sitem_class* i_this) {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.eyePos, &i_this->actor.tevStr);
    hand_draw(i_this);

    return TRUE;
}

/* 00000248-0000034C       .text hand_mtx_set__FP11sitem_class */
void hand_mtx_set(sitem_class* i_this) {
    MtxTrans(i_this->mVineEndPos.x, i_this->mVineEndPos.y, i_this->mVineEndPos.z, false);

    cMtx_XrotM(*calc_mtx, i_this->mPodAngleX);
    cMtx_YrotM(*calc_mtx, i_this->mPodAngleY);
    cMtx_XrotM(*calc_mtx, REG12_S(1) + 0x4000);

    cXyz pos(0.0f, REG12_F(4) + -60.0f, 0.0f);
    MtxPosition(&pos, &i_this->mPodCenterPos);

    MtxTrans(0.0, REG12_F(3) + -50.0f, 0.0, true);

    J3DModel* model = i_this->mpModel;
    model->setBaseTRMtx(*calc_mtx);
}

static f32 size_d[] = {10.0f, 10.0f, 9.5f, 9.0f, 8.5f, 8.0f, 7.5f, 7.0f, 6.5f, 6.5f};

/* 00000388-00000410       .text control3__FP11sitem_class */
// Computes vine thickness
void control3(sitem_class* i_this) {
    sitem_s* cur = i_this->mVinePoints;
    for (int i = 0; i < 10; i++, cur++) {
        f32 sin = cM_ssin(i_this->mFrameCounter * 500 + i * 100);

        f32 thickness = 0.8f + 0.1f * sin;
        cur->thickness = thickness * size_d[i];
    }
}

/* 00000410-00000748       .text control1__FP11sitem_class */
// Computes vine shape from ceiling downward
void control1(sitem_class* i_this) {
    static f32 g_d[10] = {50.0f, 50.0f, 35.0f, 25.0f, 15.0f, 9.0f, 6.0f, 6.0f, 6.0f, 6.0f};

    i_this->mVinePoints[0].pos = i_this->actor.current.pos;

    int i;
    sitem_s* vine_i = &i_this->mVinePoints[1];

    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);

    cXyz segment_offset;
    segment_offset.x = 0;
    segment_offset.y = 0;
    segment_offset.z = i_this->mVineAxialBias;

    cXyz offset;
    cXyz axial_offset;
    MtxPosition(&segment_offset, &axial_offset);

    segment_offset.z = i_this->mVineSegmentLength;

    f32 vec_x;
    f32 vec_y;
    f32 vec_z;
    f32 scale;
    f32 sway_amplitude;

    s16 angle_x;
    s32 angle_y;

    sway_amplitude = i_this->mVineSwayAmplitude;
    for (i = 1; i < 9; i++, vine_i++) {
        offset.x = sway_amplitude * cM_ssin(i_this->mFrameCounter * (REG0_S(5) + 0x44c) + i * (REG0_S(6) + 4000));
        offset.y = g_d[i];
        offset.z = sway_amplitude * cM_scos(i_this->mFrameCounter * (REG0_S(7) + 800) + i * (REG0_S(8) + 4000));

        scale = 1.0f;
        cXyz sway_offset;
        MtxPosition(&offset, &sway_offset);

        vec_x = sway_offset.x * scale +
            ((vine_i->pos.x - vine_i[-1].pos.x) +
             axial_offset.x * scale);

        vec_y = sway_offset.y * scale +
            ((vine_i->pos.y - vine_i[-1].pos.y) +
             axial_offset.y * scale);

        vec_z = sway_offset.z * scale +
            ((vine_i->pos.z - vine_i[-1].pos.z) +
             axial_offset.z * scale);

        angle_y = cM_atan2s(vec_x, vec_z);
        angle_x = -cM_atan2s(vec_y, std::sqrtf(vec_x * vec_x + vec_z * vec_z));

        MtxPush();
        mDoMtx_YrotS(*calc_mtx, (s16) angle_y);
        mDoMtx_XrotM(*calc_mtx, angle_x);

        MtxPosition(&segment_offset, &offset);
        MtxPull();

        vine_i->pos = vine_i[-1].pos + offset;
    }
}

/* 00000748-000009E8       .text control2__FP11sitem_class */
// Constrains vine from pod upward and orients pod
void control2(sitem_class* i_this) {
    cXyz segment_offset;
    segment_offset.x = 0.0f;
    segment_offset.y = 0.0f;
    segment_offset.z = i_this->mVineSegmentLength;

    i_this->mVinePoints[9].pos = i_this->mPodPos;

    f32 delta_x;
    f32 delta_y;
    f32 delta_z;

    int i;
    s16 angle_x;
    s32 angle_y;
    sitem_s* vine_i;

    vine_i = &i_this->mVinePoints[8];
    for (i = 8; i >= 1; i--, vine_i--) {
        delta_x = vine_i->pos.x - vine_i[1].pos.x;
        delta_y = vine_i->pos.y - vine_i[1].pos.y;
        delta_z = vine_i->pos.z - vine_i[1].pos.z;

        angle_y = cM_atan2s(delta_x, delta_z);

        angle_x = -cM_atan2s(delta_y, std::sqrtf(delta_x * delta_x + delta_z * delta_z));

        mDoMtx_YrotS(*calc_mtx, angle_y);
        mDoMtx_XrotM(*calc_mtx, angle_x);

        segment_offset.z = i_this->mVineSegmentLength;

        cXyz offset;
        MtxPosition(&segment_offset, &offset);

        vine_i->pos = vine_i[1].pos + offset;
    }

    i_this->mVineEndPos = i_this->mVinePoints[9].pos;

    segment_offset = i_this->mVinePoints[8].pos - i_this->mVinePoints[9].pos;
    i_this->mPodAngleX = -cM_atan2s(segment_offset.y, segment_offset.z);
    i_this->mPodAngleY = cM_atan2s(segment_offset.x, std::sqrtf(segment_offset.y * segment_offset.y + segment_offset.z * segment_offset.z));

    hand_mtx_set(i_this);
}

/* 000009E8-00000E2C       .text cut_control1__FP11sitem_class */
void cut_control1(sitem_class* i_this) {
    i_this->mVineStubPoints[0].pos = i_this->actor.current.pos;

    int i;
    sitem_s* stub_i = &i_this->mVineStubPoints[1];

    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);

    cXyz segment_offset;
    segment_offset.z = i_this->mVineStubSegmentLength;

    f32 delta_x;
    f32 delta_y;
    f32 delta_z;
    f32 sway_amplitude;

    s16 angle_x;
    s32 angle_y;

    sway_amplitude = REG0_F(0x12) + 50.0f;

    for (i = 1; i < 5; i++, stub_i++) {
        cXyz offset;
        offset.x = sway_amplitude * cM_ssin(i_this->mFrameCounter * (REG0_S(5) + 0x1004) + i * (REG0_S(6) + 10000));
        offset.y = REG0_F(0x11) + 50.0f;
        offset.z = sway_amplitude * cM_scos(i_this->mFrameCounter * (REG0_S(7) + 0x1130) + i * (REG0_S(8) + 10000));

        cXyz sway_offset;
        MtxPosition(&offset, &sway_offset);

        delta_x = sway_offset.x + (stub_i->pos.x - stub_i[-1].pos.x);
        delta_y = sway_offset.y + (stub_i->pos.y - stub_i[-1].pos.y);
        delta_z = sway_offset.z + (stub_i->pos.z - stub_i[-1].pos.z);

        angle_y = cM_atan2s(delta_x, delta_z);
        delta_x = std::sqrtf(delta_x * delta_x + delta_z * delta_z);

        angle_x = -cM_atan2s(delta_y, delta_x);
        MtxPush();

        cMtx_YrotS(*calc_mtx, angle_y);
        cMtx_XrotM(*calc_mtx, angle_x);

        MtxPosition(&segment_offset, &offset);
        MtxPull();

        stub_i->pos = stub_i[-1].pos + offset;
    }

#if VERSION == VERSION_DEMO
    JPABaseEmitter* emitter = i_this->mpCutParticleEmitter[0];
#else
    JPABaseEmitter* emitter = i_this->mCutParticleCallback[0].getEmitter();
#endif

    if (!emitter && i_this->mCutParticleFlag) {
        i_this->mCutParticleCallback[0].end();

#if VERSION == VERSION_DEMO
        i_this->mpCutParticleEmitter[0] =
#endif
        dComIfGp_particle_set(dPa_name::ID_IT_SN_TSURU_TAIEKI00, &i_this->mVineStubPoints[4].pos, &i_this->mCutParticleAngle[0], NULL, 0xFF, &i_this->mCutParticleCallback[0], fopAcM_GetRoomNo(&i_this->actor), NULL, NULL, NULL);

        i_this->mHitCooldownTimer = 0x3C;
    } else {
        segment_offset = i_this->mVineStubPoints[4].pos - i_this->mVineStubPoints[3].pos;

        s16 particle_angle = cM_atan2s(segment_offset.x, segment_offset.z);

        i_this->mCutParticleAngle[0].y = particle_angle;
        f32 horizontal_length = std::sqrtf(segment_offset.x * segment_offset.x + segment_offset.z * segment_offset.z);

        particle_angle = cM_atan2s(segment_offset.y, horizontal_length);
        i_this->mCutParticleAngle[0].x = -particle_angle;

#if VERSION == VERSION_DEMO
        if (i_this->mHitCooldownTimer == 1 && i_this->mpCutParticleEmitter[0]) {
            i_this->mpCutParticleEmitter[0]->becomeInvalidEmitter();
            i_this->mpCutParticleEmitter[0] = NULL;
        }
#else
        if (i_this->mHitCooldownTimer == 1 && i_this->mCutParticleCallback[0].getEmitter() != NULL) {
            i_this->mCutParticleCallback[0].end();
        }
#endif
    }
}

/* 00000E2C-00001058       .text my_break__FP11sitem_class */
void my_break(sitem_class* i_this) {
    i_this->mTimers[0] = 0x32;
    i_this->mAction = 6;

    csXyz item_angle(0, i_this->actor.current.angle.y, 0);
    fopAcM_createItemFromTable(&i_this->mPodPos, i_this->mItemTableNo, i_this->mItemBit & 0x7F, fopAcM_GetHomeRoomNo(&i_this->actor), 0, &item_angle, 1, NULL);

    if (i_this->mPodType <= 1) {
        dComIfGp_particle_set(dPa_name::ID_IT_SN_BOKKURI_TANE00, &i_this->mPodPos, NULL, NULL, 0xFF, NULL, -1, NULL, NULL, NULL);

        dComIfGp_particle_set(dPa_name::ID_IT_SN_BOKKURI_HAHEN00, &i_this->mPodPos, NULL, NULL, 0xFF, NULL, -1, &i_this->actor.tevStr.mColorK0, &i_this->actor.tevStr.mColorK0, NULL);

        if (i_this->mPodType == 1) {
            dComIfGp_particle_set(dPa_name::ID_IT_SN_BOKKURI_TOGE00, &i_this->mPodPos, NULL, NULL, 0xFF, NULL, -1, &i_this->actor.tevStr.mColorK0, &i_this->actor.tevStr.mColorK0, NULL);
        }
    }

    if (i_this->mPodType == 2) {
        dComIfGp_particle_set(dPa_name::ID_IT_SN_BOKKURI_MATSU00, &i_this->mPodPos, NULL, NULL, 0xFF, NULL, -1, &i_this->actor.tevStr.mColorK0, &i_this->actor.tevStr.mColorK0, NULL);
    }

#if VERSION > VERSION_DEMO
    fopAcM_seStart(&i_this->actor, JA_SE_OBJ_BREAK_CHAIR, 0);
#endif

    daObjEff::Act_c::make_pinecone_smoke(&i_this->mPodPos);
}

/* 00001094-000015C0       .text cut_control2__FP11sitem_class */
void cut_control2(sitem_class* i_this) {
    cXyz segment_offset;
    cXyz offset;
    cXyz sway_offset;
    segment_offset.x = 0.0;
    segment_offset.y = 0.0;
    segment_offset.z = i_this->mVineSegmentLength;

    i_this->mVinePoints[9].pos = i_this->mPodPos;

    int i;
    sitem_s* vine_i = &i_this->mVinePoints[8];

    f32 delta_x;
    f32 point_y;
    f32 min_y;
    f32 delta_z;
    f32 delta_y;
    f32 sway_amplitude;

    s16 angle_x;
    s32 angle_y;
    s16 angle;

    sway_amplitude = i_this->mVineSwayAmplitude;

    for (i = 8; i >= 0; i--, vine_i--) {
        sway_offset.x = sway_amplitude * JMASSin(i_this->mFrameCounter * (REG0_S(5) + 0x9C4) + i * (REG0_S(6) + 3000));
        sway_offset.y = sway_amplitude * JMASSin(i_this->mFrameCounter * (REG0_S(5) + 0xB86) + i * (REG0_S(6) + 4000));
        sway_offset.z = sway_amplitude * JMASCos(i_this->mFrameCounter * (REG0_S(7) + 0xAF0) + i * (REG0_S(8) + 0xDAC));

        delta_x = sway_offset.x + (vine_i->pos.x - vine_i[1].pos.x);

        point_y = (vine_i->pos.y - 10.0f) + sway_offset.y;
        min_y = i_this->mGroundY + 5.0f;

        if (point_y < min_y) {
            point_y = min_y;
        }

        delta_y = point_y - vine_i[1].pos.y;

        delta_z = sway_offset.z + ((vine_i->pos).z - vine_i[1].pos.z);

        angle_y = cM_atan2s(delta_x, delta_z);

        angle_x = -cM_atan2s(delta_y, std::sqrtf(delta_x * delta_x + delta_z * delta_z));

        cMtx_YrotS(*calc_mtx, angle_y);
        cMtx_XrotM(*calc_mtx, angle_x);

        segment_offset.z = i_this->mVineSegmentLength;

        MtxPosition(&segment_offset, &offset);
        vine_i->pos = vine_i[1].pos + offset;
    }

    i_this->mVineEndPos = i_this->mVinePoints[9].pos;
    segment_offset = i_this->mVinePoints[8].pos - i_this->mVinePoints[9].pos;

    angle = cM_atan2s(segment_offset.y, segment_offset.z);
    i_this->mPodAngleX = -angle;

    angle = cM_atan2s(segment_offset.x, std::sqrtf(segment_offset.y * segment_offset.y + segment_offset.z * segment_offset.z));
    i_this->mPodAngleY = angle;
    hand_mtx_set(i_this);

#if VERSION == VERSION_DEMO
    JPABaseEmitter* emitter = i_this->mpCutParticleEmitter[1];
#else
    JPABaseEmitter* emitter = i_this->mCutParticleCallback[1].getEmitter();
#endif

    if (!emitter && i_this->mCutParticleFlag) {
        i_this->mCutParticleCallback[1].end();

#if VERSION == VERSION_DEMO
        i_this->mpCutParticleEmitter[1] =
#endif
        dComIfGp_particle_set(dPa_name::ID_IT_SN_TSURU_TAIEKI00, &i_this->mVinePoints[0].pos, i_this->mCutParticleAngle + 1, NULL, 0xFF, &i_this->mCutParticleCallback[1], fopAcM_GetRoomNo(&i_this->actor), NULL, NULL, NULL);
    } else {
        segment_offset = i_this->mVinePoints[0].pos - i_this->mVinePoints[1].pos;

        angle = cM_atan2s(segment_offset.x, segment_offset.z);

        i_this->mCutParticleAngle[1].y = angle;

        angle = cM_atan2s(segment_offset.y, std::sqrtf(segment_offset.x * segment_offset.x + segment_offset.z * segment_offset.z));
        i_this->mCutParticleAngle[1].x = -angle;

#if VERSION == VERSION_DEMO
        if (i_this->mHitCooldownTimer == 1 && i_this->mpCutParticleEmitter[1]) {
            i_this->mpCutParticleEmitter[1]->becomeInvalidEmitter();
            i_this->mpCutParticleEmitter[1] = NULL;
            i_this->mCutParticleFlag = 0;
        }
#else
        if (i_this->mHitCooldownTimer == 1 && i_this->mCutParticleCallback[1].getEmitter() != NULL) {
            i_this->mCutParticleCallback[1].end();
            i_this->mCutParticleFlag = 0;
        }
#endif
    }
}

static f32 hr_d[4] = {10.0f, 25.0f, 40.0f, 65.0f};
static f32 max_d[4] = {100.0f, 250.0f, 400.0f, 600.0f};

/* 000015C0-00002304       .text hand_move__FP11sitem_class */
void hand_move(sitem_class* i_this) {
    /* Nonmatching - demo-only */
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    f32 scale;
    f32 base_speed;
    f32 zero;
    f32 segment_length;
    f32 step;
    f32 sway_amplitude;
    u8* line_sizes;
    cXyz* collision_point;
    bool is_cut;
    s16 action;
    sitem_s* vine_point;
    cXyz* line_positions;
    int hit_flags;
    f32 vine_length;
    cXyz offset;
    cXyz world_offset;
    cXyz target_pos;
    cXyz collision_pos;
    cXyz particle_scale;
    cXyz stub_delta;
    CcAtInfo attack_info;
    dBgS_GndChk ground_check;

    is_cut = false;

    scale = 0.1f;
    base_speed = 8.0f;
    zero = 0.0f;
    step = 1.0f;
    sway_amplitude = REG0_F(0xB) + 5.0f;

    segment_length = REG0_F(5) + hr_d[i_this->mVineLengthType];
    vine_length = max_d[i_this->mVineLengthType];

    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);

    action = i_this->mAction;

    switch (action) {
        case 0:
        case 1:
            offset.x = (REG0_F(0xD) + 25.0f) * cM_ssin(i_this->mFrameCounter * 600);
            offset.y = vine_length;
            offset.z = (REG0_F(0xD) + 25.0f) * cM_ssin(i_this->mFrameCounter * 700);

            MtxPosition(&offset, &world_offset);

            target_pos = i_this->actor.current.pos + world_offset;
            if (i_this->mAction == 0) {
                i_this->mPodPos = target_pos;
                i_this->mAction = 1;
            }
            break;
        case 5:
            sway_amplitude = 50.0f;
            i_this->mVineSwayAmplitude = 50.0f;
            is_cut = true;
            segment_length = 25.0f;

            i_this->mOldPodPos = i_this->mPodPos;

            PSVECAdd(&i_this->mPodPos, &i_this->actor.speed, &i_this->mPodPos);

            i_this->actor.speed.y -= 3.0f;

            if (i_this->actor.speed.y < -90.0f) {
                i_this->actor.speed.y = -90.0f;
            }

            i_this->mBgAcch.CrrPos(g_dComIfG_gameInfo.play.mBgS);

            i_this->mHitCooldownTimer = 5;

            if (i_this->actor.speed.y < 0.0f) {
                f32 x = (i_this->mPodPos).x;
                f32 y = (i_this->mPodPos).y;
                f32 z = (i_this->mPodPos).z;

                y += 100.0f;

                ground_check.m_pos.x = x;
                ground_check.m_pos.y = y;
                ground_check.m_pos.z = z;

                i_this->mGroundY = dComIfG_Bgsp()->GroundCross(&ground_check);

                if (i_this->mGroundY == -G_CM3D_F_INF || i_this->mPodPos.y <= i_this->mGroundY + 30.0f) {
                    i_this->mPodPos.y = i_this->mGroundY + 30.0f;
                    my_break(i_this);
                }
            }

            break;
        case 6:
            is_cut = true;
            sway_amplitude = zero;
            i_this->mHitCooldownTimer = 10;
            if (i_this->mTimers[0] < 0x28) {
                step = segment_length * 0.05f;
                segment_length = sway_amplitude;
            }

            if (i_this->mTimers[0] == 0) {
                fopAcM_delete(&i_this->actor);
            }
            break;
    }

    cLib_addCalc2(&i_this->mVineSegmentLength, segment_length, 0.5f, step);
    cLib_addCalc2(&i_this->mVineAxialBias, zero, 1.0f, 0.2f);
    cLib_addCalc2(&i_this->mVineSwayAmplitude, sway_amplitude, 1.0f, 1.5f);

    if (!is_cut) {
        cLib_addCalc2(&i_this->actor.speedF, base_speed, 1.0f, scale);
        if ((i_this->mSwayOffset > 1.0f) && (i_this->mAction != 3)) {
            cMtx_YrotS(*calc_mtx, (int)i_this->mSwayAngleY);

            offset.x = 0.0f;
            offset.y = REG6_F(9);
            offset.z = i_this->mSwayOffset;

            MtxPosition(&offset, &world_offset);
            PSVECAdd(&target_pos, &world_offset, &target_pos);

            scale = 0.1f;
            i_this->actor.speedF = i_this->mSwayOffset * 0.2f;
            if (i_this->actor.speedF > REG6_F(8) + 30.0f) {
                i_this->actor.speedF = REG6_F(8) + 30.0f;
            }
        }
        cLib_addCalc0(&i_this->mSwayOffset, 1.0f, REG6_F(7) + 5.0f);

        cLib_addCalc2(&(i_this->mPodPos).x, target_pos.x, scale, i_this->actor.speedF);
        cLib_addCalc2(&(i_this->mPodPos).y, target_pos.y, scale, i_this->actor.speedF);
        cLib_addCalc2(&(i_this->mPodPos).z, target_pos.z, scale, i_this->actor.speedF);

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
            *sizes = stub->thickness;
        }

        cLib_addCalc0(&i_this->mVineStubSegmentLength, 1.0f, REG0_F(1) + 1.0f);
    }

    control3(i_this);
    vine_point = i_this->mVinePoints;
    line_positions = i_this->mVineLineMat.getPos(0);
    line_sizes = i_this->mVineLineMat.getSize(0);

    for (int i = 10; i != 0; i--, vine_point++, line_positions++, line_sizes++) {
        *line_positions = vine_point->pos;
        *line_sizes = vine_point->thickness;
    }
    line_positions = i_this->mVineLineMat.getPos(0);

    i_this->actor.eyePos = line_positions[5];
    i_this->actor.attention_info.position = i_this->actor.eyePos;

    i_this->mCcStts.Move();
    if (!is_cut) {
        i_this->mBoomerangSph.SetC(i_this->actor.eyePos);
    } else {
        i_this->mBoomerangSph.SetC(non_pos);
    }

    hit_flags = 0;
    dComIfG_Ccsp()->Set(&i_this->mBoomerangSph);
    for (int sphere_index = 0; sphere_index < 3; sphere_index++) {
        int index = ((int)i_this->mFrameCounter & 3U) + sphere_index * 2;
        index = index % 10;

        collision_point = line_positions + index;
        collision_pos = *collision_point;

        if (!is_cut) {
            i_this->mVinePodSph[sphere_index].SetC(collision_pos);
        } else {
            i_this->mVinePodSph[sphere_index].SetC(non_pos);
        }

        if (i_this->mAction == 3) {
            i_this->mVinePodSph[sphere_index].OffCoSetBit();
        } else {
            i_this->mVinePodSph[sphere_index].OnCoSetBit();
        }
        dComIfG_Ccsp()->Set(&i_this->mVinePodSph[sphere_index]);
    }

    i_this->mVinePodSph[3].SetR(50.0f);
    i_this->mVinePodSph[3].SetC(i_this->mPodCenterPos);
    i_this->mVinePodSph[3].OnCoSetBit();

    dComIfG_Ccsp()->Set(&i_this->mVinePodSph[3]);

    attack_info.mpObj = NULL;
    if (i_this->mHitCooldownTimer == 0) {
        if (i_this->mVinePodSph[3].ChkTgHit() || (i_this->mSwayOffset > 100.0f && i_this->mVinePodSph[3].ChkCoHit())) {
            attack_info.mpObj = i_this->mVinePodSph[3].GetTgHitObj();

            if (attack_info.mpObj && attack_info.mpObj->ChkAtType(AT_TYPE_GRAPPLING_HOOK)) {
                return;
            }

            my_break(i_this);
            hit_flags = 3;
        } else {
            for (int hit_index = 0; hit_index < 3; hit_index++) {
                if (i_this->mVinePodSph[hit_index].ChkTgHit()) {
                    attack_info.mpObj = i_this->mVinePodSph[hit_index].GetTgHitObj();
                    if (attack_info.mpObj && attack_info.mpObj->ChkAtType(AT_TYPE_GRAPPLING_HOOK)) {
                        return;
                    }

                    hit_flags = 1;
                    break;
                }
            }

            if (((hit_flags & 0xFF) || i_this->mBoomerangSph.ChkTgHit())
                && (i_this->mHitCooldownTimer == 0)) {
                i_this->mHitCooldownTimer = 0x14;
                if (((u8) hit_flags) == 0) {
                    attack_info.mpObj = i_this->mBoomerangSph.GetTgHitObj();
                    at_power_check(&attack_info);

                    if (attack_info.mResultingAttackType == 8) {
                        i_this->mSwayOffset = REG6_F(6) + 300.0f;
                        i_this->mSwayAngleY = fopAcM_searchPlayerAngleY(&i_this->actor) + 0x8000;
                        return;
                    }
                }
                i_this->mAction = 5;
                f32 speed = cM_rndFX(10.0f);
                i_this->actor.speed.x = speed;
                speed = cM_rndF(5.0f);
                i_this->actor.speed.y = speed + 10.0f;
                speed = cM_rndFX(10.0f);
                i_this->actor.speed.z = speed;
                particle_scale.x = 0.3f;
                particle_scale.y = 0.3f;
                particle_scale.z = 0.3f;
                dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUFLASH, &i_this->actor.eyePos, NULL, &particle_scale, 0xFF, NULL, -1, NULL, NULL, NULL);
                i_this->mCutParticleFlag = 1;
                hit_flags = 1;
            }
        }
        if (hit_flags & 0xFF) {
            if (attack_info.mpObj) {
                def_se_set(&i_this->actor, attack_info.mpObj, 0x21);
            }
            vine_point = i_this->mVinePoints;
            line_positions = &i_this->mVineStubPoints[0].pos;
            int point_count = 0;
            do {
                line_positions->x = (vine_point->pos).x;
                line_positions->y = (vine_point->pos).y;
                line_positions->z = (vine_point->pos).z;
                line_positions[2].x = vine_point->thickness;
                if (point_count == 4) {
                    stub_delta = *line_positions - *(cXyz*)((u8*)line_positions - 0x1C);
                    f32 stub_length = PSVECSquareMag(&stub_delta);
                    stub_length = std::sqrtf(stub_length);
                    i_this->mVineStubSegmentLength = (REG0_F(2) + 1.5f) * stub_length;
                }
                point_count = point_count + 1;
                vine_point = vine_point + 1;
                line_positions = (cXyz*)&line_positions[2].y;
            } while (point_count < 5);
        }
    }
}

/* 00002684-000026F4       .text daSitem_Execute__FP11sitem_class */
static BOOL daSitem_Execute(sitem_class* i_this) {
    i_this->mFrameCounter++;

    for (int i = 0; i < 2; i++) {
        if (i_this->mTimers[i] != 0) {
            i_this->mTimers[i]--;
        }
    }

    if (i_this->mHitCooldownTimer != 0) {
        i_this->mHitCooldownTimer--;
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
    i_this->mCutParticleCallback[0].end();
    i_this->mCutParticleCallback[1].end();

    return TRUE;
}

static u16 bmd_data[3] = {
    dRes_INDEX_SITEM_BDL_KMI_00_e,
    dRes_INDEX_SITEM_BDL_KMI_01_e,
    dRes_INDEX_SITEM_BDL_KMI_02_e,
};

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
    return useHeapInit((sitem_class*) i_this);
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

        a_this->mVineLengthType = (fopAcM_GetParam(i_this) >> 8) & 0xFF;
        if (a_this->mVineLengthType > 3) {
            a_this->mVineLengthType = 0;
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

            a_this->mVineLengthType = (fopAcM_GetParam(i_this) >> 8) & 0xFF;
            if (a_this->mVineLengthType > 3) {
                a_this->mVineLengthType = 0;
            }

            a_this->mItemTableNo = (fopAcM_GetParam(i_this) >> 24) & 0xFF;
            if (a_this->mItemTableNo == 0xFF) {
                a_this->mItemTableNo = 0;
            }

            a_this->mItemBit = (fopAcM_GetParam(i_this) >> 16) & 0xFF;
#endif

            i_this->health = 2;

            a_this->mFrameCounter = cM_rndF(10000.0f);

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
            a_this->mPodPos = i_this->current.pos;

            a_this->mBgAcch.Set(&a_this->mPodPos, &a_this->mOldPodPos, i_this, 1, &a_this->mBgAcchCir, fopAcM_GetSpeed_p(&a_this->actor));
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
