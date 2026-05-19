/**
 * d_a_st.cpp
 * Enemy - Stalfos / スタ (Stal)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_st.h"
#include "d/actor/d_a_boko.h"
#include "d/actor/d_a_player.h"
#include "d/d_s_play.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_snap.h"
#include "d/res/res_st.h"

enum BehaviorType {
    BEHAVIOR_NORMAL = 0,
    BEHAVIOR_UNDERGROUND = 1,
    BEHAVIOR_IN_HORIZONTAL_COFFIN = 2,
    BEHAVIOR_IN_VERTICAL_COFFIN = 3,
    BEHAVIOR_UPPER_BODY_ONLY = 14,
};

static bool hio_set;
static bool another_hit;
static HIO_c l_HIO;

/* 000000EC-000005B4       .text smoke_set_s__FP8st_classf */
static void smoke_set_s(st_class* i_this, f32 rate) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk linChk;
    s32 attribCode;
    attribCode = 0;
    cXyz startPos = i_this->m1F6C;
    startPos.y += 100.0f;
    cXyz endPos = i_this->m1F6C;
    endPos.y -= 100.0f;
    linChk.Set(&startPos, &endPos, actor);

    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        endPos = linChk.GetCross();
        i_this->m1F6C.y = endPos.y + 30.0f;
        attribCode = dComIfG_Bgsp()->GetAttributeCode(linChk);
    } else {
        i_this->m1F6C.y -= 20000.0f;
    }

    if (i_this->m1F83 != 0 && attribCode != dBgS_Attr_GRASS_e) {
        return;
    }

    i_this->m1F83++;

    switch (attribCode) {
        case dBgS_Attr_NORMAL_e:
        case dBgS_Attr_DIRT_e:
        case dBgS_Attr_WOOD_e:
        case dBgS_Attr_STONE_e:
        case dBgS_Attr_SAND_e:
            {
                i_this->m1E88[2].remove();
                JPABaseEmitter* emitter1 = dComIfGp_particle_setToon(
                    dPa_name::ID_AK_JT_ELEMENTSMOKE00, &i_this->m1F6C, &i_this->m1F78, NULL, 0xB9, &i_this->m1E88[2], fopAcM_GetRoomNo(actor)
                );
                if (emitter1) {
                    emitter1->setRate(rate);
                    emitter1->setSpread(1.0f);
                    JGeometry::TVec3<f32> scale;
                    scale.x = scale.y = scale.z = 0.8f;
                    emitter1->setGlobalDynamicsScale(scale);
                    scale.x = scale.y = scale.z = 2.0f + REG0_F(11);
                    emitter1->setGlobalParticleScale(scale);
                }
                break;
            }
        case dBgS_Attr_GRASS_e:
            JPABaseEmitter* emitter2 = dComIfGp_particle_set(dPa_name::ID_AK_JN_ELEMENTKUSA00, &i_this->m1F6C, &i_this->m1F78);
            if (emitter2) {
                emitter2->setRate(rate * 0.5f);
                emitter2->setMaxFrame(3);
            }
            break;
    }
}

/* 00000A28-00000BE8       .text spin_smoke_move__FP8st_class */
static void spin_smoke_move(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_28;

    if (i_this->m1F80 != 0) {
        i_this->m1F80--;
        if (i_this->m1F80 >= 10) {
            i_this->m1F78.x = 0;
            i_this->m1F78.z = 0;
            local_28.x = 0.0f;
            local_28.y = 0.0f;
            MtxTrans(actor->current.pos.x, actor->current.pos.y + 7.5f, actor->current.pos.z, false);
            local_28.z = (REG0_F(2) + 1.0f) * -175.0f;
            cMtx_YrotM(*calc_mtx, i_this->m1F7E);
            MtxPosition(&local_28, &i_this->m1F6C);
            i_this->m1F78.y = i_this->m1F7E;
            smoke_set_s(i_this, REG0_F(3) + 3.0f);
            if (i_this->m1F82 == 2) {
                i_this->m1F7E += (s16)((REG0_F(11) + 5000.0f) * i_this->m0308);
            } else if (i_this->m1F82 == 0) {
                i_this->m1F7E += (s16)(REG0_S(7) + 2000);
            } else {
                s16 r4 = i_this->m1F7E;
                s16 r0 = -(REG0_S(7) + 2000);
                i_this->m1F7E = r4 + r0;
            }
        } else {
            i_this->m1F6C.y = actor->current.pos.y + 20000.0f;
        }
        if (i_this->m1F80 == 0) {
            i_this->m1E88[2].remove();
            i_this->m1F83 = 0;
        }
    }
}

/* 00000BE8-00000D10       .text anm_init__FP8st_classifUcfi */
static void anm_init(st_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (soundFileIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("St", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("St", soundFileIdx)
        );
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("St", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000D10-00000E38       .text head_anm_init__FP8st_classifUcfi */
static void head_anm_init(st_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (soundFileIdx >= 0) {
        i_this->mpMorf2->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("St", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("St", soundFileIdx)
        );
    } else {
        i_this->mpMorf2->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("St", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000E38-00001394       .text ke_control__FP8st_classP7st_ke_si */
static void ke_control(st_class* i_this, st_ke_s* param_2, int param_3) {
    cXyz* pcVar6;
    cXyz* pcVar5;
    f32 y;
    f32 x;
    f32 dVar11;
    f32 z;
    f32 dVar8;
    cXyz local_120;
    cXyz local_12c;
    cXyz local_138;
    cXyz local_144;

    dVar11 = -G_CM3D_F_INF;
    pcVar6 = &param_2->m000[1];
    pcVar5 = &param_2->m078[1];
    if (i_this->m1DD8 != 0) {
        dBgS_GndChk gndChk;
        Vec pos;
        pos = *pcVar6;
        pos.y += 50.0f;
        gndChk.SetPos(&pos);
        dVar11 = 3.0f + dComIfG_Bgsp()->GroundCross(&gndChk);
        if ((dVar11 - pcVar6->y) > 50.0f) {
            dVar11 = pcVar6->y;
        }
    }
    cMtx_YrotS(*calc_mtx, param_2->m0F0.y);
    cMtx_XrotM(*calc_mtx, param_2->m0F0.x);
    local_120.x = 0.0f;
    local_120.y = 30.0f;
    local_120.z = -20.0f;
    MtxPosition(&local_120, &local_138);
    local_120.x = 0.0f;
    local_120.y = 0.0f;
    local_120.z = 17.5f;
    for (s32 i = 1; i < 10; i++, pcVar6++, pcVar5++) {
        if (i > 5) {
            local_144.x = 0.0f;
            local_144.y = 0.0f;
            local_144.z = 0.0f;
        } else {
            local_144.x = local_138.x * (s32)(5 - i) * 0.1f;
            local_144.y = local_138.y * (s32)(5 - i) * 0.1f;
            local_144.z = local_138.z * (s32)(5 - i) * 0.1f;
        }
        x = (local_144.x + (pcVar5->x + (pcVar6->x - pcVar6[-1].x)));
        z = local_144.z + (pcVar5->z + (pcVar6->z - pcVar6[-1].z));
        dVar8 = (REG0_F(2) + ((local_144.y + (pcVar6->y + pcVar5->y)) - 10.0f));
        if (dVar8 < dVar11) {
            dVar8 = dVar11;
        }
        y = (dVar8 - pcVar6[-1].y);
        s16 iVar2 = -cM_atan2s(y, z);
        int iVar3 = cM_atan2s(x, std::sqrtf(SQUARE(y) + SQUARE(z)));
        cMtx_XrotS(*calc_mtx, iVar2);
        cMtx_YrotM(*calc_mtx, iVar3);
        MtxPosition(&local_120, &local_12c);
        *pcVar5 = *pcVar6;
        pcVar6->x = pcVar6[-1].x + local_12c.x;
        pcVar6->y = pcVar6[-1].y + local_12c.y;
        pcVar6->z = pcVar6[-1].z + local_12c.z;
        pcVar5->x = (((param_3 * 0.001f) + 0.75f) * (pcVar6->x - pcVar5->x));
        pcVar5->y = (((param_3 * 0.001f) + 0.75f) * (pcVar6->y - pcVar5->y));
        pcVar5->z = (((param_3 * 0.001f) + 0.75f) * (pcVar6->z - pcVar5->z));
    }
}

/* 0000152C-00001570       .text ke_pos_set__FP8st_classP7st_ke_si */
static void ke_pos_set(st_class* i_this, st_ke_s* param_2, int param_3) {
    cXyz* pos = i_this->mLineMat.getPos(param_3);
    for (s32 i = 0; i < 10; i++, pos++) {
        *pos = param_2->m000[i];
    }
}

/* 00001570-000015FC       .text ke_disp__FP8st_class */
static void ke_disp(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

#ifdef __MWERKS__
    i_this->mLineMat.update(10, 1.2f, (GXColor){0xFF, 0x64, 0, 0xFF}, 2, &actor->tevStr);
#else
    GXColor color = (GXColor){0xFF, 0x64, 0, 0xFF};
    i_this->mLineMat.update(10, 1.2f, color, 2, &actor->tevStr);
#endif
    dComIfGd_set3DlineMat(&i_this->mLineMat);
}

/* 000015FC-00001664       .text ke_move__FP8st_class */
static void ke_move(st_class* i_this) {
    st_ke_s* psVar2 = i_this->mKe;
    for (s32 i = 0; i < 3; i++, psVar2++) {
        ke_control(i_this, psVar2, i);
        ke_pos_set(i_this, psVar2, i);
    }
}

/* 00001664-00001A18       .text nun_control__FP8st_class */
static void nun_control(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 y;
    f32 z;
    f32 x;
    f32 f30;
    cXyz local_5c;
    cXyz local_68;
    cXyz local_74;

    local_74.x = 0.0f;
    local_74.y = 0.0f;
    local_74.z = 0.0f;
    if (i_this->m1DC8 == 2) {
        cMtx_YrotS(*calc_mtx, (actor->shape_angle.y + -8000) + REG8_S(3));
        cMtx_XrotM(*calc_mtx, REG8_S(4));
        cMtx_ZrotM(*calc_mtx, i_this->m02E8 * (REG8_S(5) + 0x1800));
        local_5c.x = REG8_F(1) + 200.0f;
        local_5c.y = 0.0f;
        local_5c.z = 0.0f;
        MtxPosition(&local_5c, &local_74);
        if ((i_this->m02E8 & 7) == 0) {
            fopAcM_seStart(actor, JA_SE_CM_ST_SWING_NUN_S, 0);
        }
    } else {
        local_74.x = 0.0f;
        local_74.y = 0.0f;
        local_74.z = 0.0f;
    }
    local_5c.x = 0.0f;
    local_5c.y = 0.0f;
    local_5c.z = REG6_F(4) + 30.0f;
    if (i_this->m1DC8 == 1) {
        f30 = (REG6_F(2) + 1.3f);
    } else if (i_this->m1DC8 == 2) {
        f30 = 0.3f;
    } else if (i_this->m1DC8 == 3) {
        f30 = (REG8_F(14) + 2.5f);
    }
    x = local_74.x + (i_this->mNun.m38[2].x + (i_this->mNun.m00[2].x - i_this->mNun.m00[1].x));
    y = local_74.y + ((i_this->mNun.m38[2].y + (i_this->mNun.m00[2].y - i_this->mNun.m00[1].y)) - 20.0f);
    z = local_74.z + (i_this->mNun.m38[2].z + (i_this->mNun.m00[2].z - i_this->mNun.m00[1].z));
    s16 iVar4 = -cM_atan2s(y, z);
    int iVar5 = cM_atan2s(x, std::sqrtf(SQUARE(y) + SQUARE(z)));
    cMtx_XrotS(*calc_mtx, iVar4);
    cMtx_YrotM(*calc_mtx, iVar5);
    MtxPosition(&local_5c, &local_68);
    i_this->mNun.m24[1].y = iVar5;
    i_this->mNun.m24[1].x = iVar4;
    MtxPosition(&local_5c, &local_68);
    i_this->mNun.m38[2] = i_this->mNun.m00[2];
    i_this->mNun.m00[2].x = i_this->mNun.m00[1].x + local_68.x;
    i_this->mNun.m00[2].y = i_this->mNun.m00[1].y + local_68.y;
    i_this->mNun.m00[2].z = i_this->mNun.m00[1].z + local_68.z;
    i_this->mNun.m38[2].x = (f30 * (i_this->mNun.m00[2].x - i_this->mNun.m38[2].x));
    i_this->mNun.m38[2].y = (f30 * (i_this->mNun.m00[2].y - i_this->mNun.m38[2].y));
    i_this->mNun.m38[2].z = (f30 * (i_this->mNun.m00[2].z - i_this->mNun.m38[2].z));
}

/* 00001A18-00001B08       .text nun_pos_set__FP8st_class */
static void nun_pos_set(st_class* i_this) {
    MtxTrans(i_this->mNun.m00[1].x, i_this->mNun.m00[1].y, i_this->mNun.m00[1].z, false);
    cMtx_XrotM(*calc_mtx, i_this->mNun.m24[1].x);
    cMtx_YrotM(*calc_mtx, i_this->mNun.m24[1].y);
    cMtx_YrotM(*calc_mtx, REG8_S(7) + -0x4000);
    MtxTrans(REG6_F(10) + 80.0f, REG6_F(11), REG6_F(12), true);
    cMtx_YrotM(*calc_mtx, -0x8000);
    MtxScale(i_this->mEnemyIce.mScaleXZ, i_this->mEnemyIce.mScaleY, i_this->mEnemyIce.mScaleXZ, true);
    J3DModel* model = i_this->mParts[3].mpPartModel;
    model->setBaseTRMtx(*calc_mtx);
}

/* 00001B08-00001C78       .text nun_move__FP8st_class */
static void nun_move(st_class* i_this) {
    cXyz local_18;

    MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0xb), *calc_mtx);
    MtxTrans(REG8_F(5) + 10.0f, REG8_F(6), REG8_F(7), true);
    cMtx_YrotM(*calc_mtx, REG0_S(5));
    cMtx_ZrotM(*calc_mtx, REG0_S(6));
    MtxScale(i_this->mEnemyIce.mScaleXZ, i_this->mEnemyIce.mScaleY, i_this->mEnemyIce.mScaleXZ, true);
    J3DModel* model = i_this->mParts[4].mpPartModel;
    model->setBaseTRMtx(*calc_mtx);
    MtxTrans(REG8_F(8) + 60.0f, REG8_F(9), REG8_F(10), true);
    cMtx_YrotM(*calc_mtx, REG8_S(7));
    cMtx_ZrotM(*calc_mtx, REG8_S(8));
    local_18.x = REG0_F(10);
    local_18.y = REG0_F(11);
    local_18.z = REG0_F(12);
    MtxPosition(&local_18, &i_this->mNun.m00[1]);
    nun_control(i_this);
    nun_pos_set(i_this);
}

/* 00001C78-00001D34       .text st_part_drawShadow__FP8st_classP8J3DModelP4cXyzPi */
static void st_part_drawShadow(st_class* i_this, J3DModel* param_2, cXyz* param_3, int* param_4) {
    fopAc_ac_c* actor = &i_this->actor;

    if (*param_4 == 0) {
        i_this->mShadowId = dComIfGd_setShadow(
            i_this->mShadowId,
            1,
            param_2,
            param_3,
            1000.0f,
            50.0f,
            actor->current.pos.y,
            i_this->mAcch.GetGroundH(),
            i_this->mAcch.m_gnd,
            &actor->tevStr,
            0,
            1.0f,
            dDlst_shadowControl_c::getSimpleTex()
        );
        *param_4 = 1;
    } else if (i_this->mShadowId != 0) {
        dComIfGd_addRealShadow(i_this->mShadowId, param_2);
    }
}

/* 00001D34-00001E80       .text st_part_draw__FP8st_class */
static void st_part_draw(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int local_28;
    cXyz local_24;

    local_24.set(actor->current.pos.x, actor->current.pos.y + 200.0f, actor->current.pos.z);
    local_28 = 0;
    for (s32 i = 0; i < 26; i++) {
        if (
            (i_this->mParts[i].mPartState < 10) &&
            !(
                (i_this->m1DC8 != 0) &&
                ((i == 5) || (i == 6) || !(i != 7))
            ) &&
            (i != 0xB)
        ) {
            J3DModel* model = i_this->mParts[i].mpPartModel;
            if (model != NULL) {
                if (((i == 0xF) || (i == 0x10) || (i == 0x11)) && (i_this->m1DD8 == 2)) {
                    if (i == 0xF) {
                        g_env_light.setLightTevColorType(i_this->mpMorf2->getModel(), &actor->tevStr);
                        i_this->mpMorf2->entryDL();
                        st_part_drawShadow(i_this, i_this->mpMorf2->getModel(), &local_24, &local_28);
                    }
                } else {
                    g_env_light.setLightTevColorType(model, &actor->tevStr);
                    mDoExt_modelUpdateDL(model);
                    st_part_drawShadow(i_this, model, &local_24, &local_28);
                }
            }
        }
    }
}

#if VERSION == VERSION_DEMO
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        J3DModel* model = j3dSys.getModel();
        st_class* i_this = (st_class*)model->getUserArea();
        if (i_this) {
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            cMtx_YrotM(*calc_mtx, i_this->m1DE6[jntNo].y);
            cMtx_XrotM(*calc_mtx, i_this->m1DE6[jntNo].x);
            cMtx_ZrotM(*calc_mtx, i_this->m1DE6[jntNo].z);
            model->setAnmMtx(jntNo, *calc_mtx);
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}
#endif

/* 00001E80-00001F90       .text daSt_Draw__FP8st_class */
static BOOL daSt_Draw(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
#if VERSION == VERSION_DEMO
    if ((i_this->m02B9 != 0) || (i_this->m02FA != 0))
#else
    if ((i_this->m02B9 != 0) || (i_this->mCountdownToDeath != 0) || (i_this->m02FA != 0))
#endif
    {
        return TRUE;
    }
    dSnap_RegistFig(DSNAP_TYPE_ST, actor, 1.0f, 1.0f, 1.0f);
    st_part_draw(i_this);
    if ((i_this->mShadowId != 0) && (i_this->m1DD0 >= 2)) {
        fopAc_ac_c* heldWeapon = fopAcM_SearchByID(i_this->mHeldWeaponEntityId);
        if ((heldWeapon != NULL) && (heldWeapon->model != NULL)) {
            dComIfGd_addRealShadow(i_this->mShadowId, heldWeapon->model);
        }
    }
    if (((i_this->mActionState != 0x21) && (i_this->m02C4 != 0x23)) && (i_this->mEnemyIce.mLightShrinkTimer == 0 && (i_this->mTimers[2] == 0))) {
        ke_disp(i_this);
    }
    return TRUE;
}

/* 00001F90-00002080       .text wait_set__FP8st_class */
static void wait_set(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m1DC8 != 0) {
        anm_init(i_this, ST_BCK_HYUNHYUN, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m1DC8 = 2;
        fopAcM_monsSeStart(actor, JA_SE_CV_ST_NUNCHAKU_S, 0);
    } else if (i_this->m02CC == 0) {
        anm_init(i_this, ST_BCK_WAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
    } else {
        anm_init(i_this, ST_BCK_LWAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
    }
}

/* 00002080-00002164       .text walk_set__FP8st_classf */
static void walk_set(st_class* i_this, f32 param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    if (i_this->m1DC8 != 0) {
        anm_init(i_this, ST_BCK_HYUNHYUN, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m1DC8 = 2;
        fopAcM_monsSeStart(actor, JA_SE_CV_ST_NUNCHAKU_S, 0);
    } else if (i_this->m02CC == 0) {
        anm_init(i_this, ST_BCK_WALK, 10.0f, J3DFrameCtrl::EMode_LOOP, param_2, -1);
    } else {
        anm_init(i_this, ST_BCK_LWALK, 10.0f, J3DFrameCtrl::EMode_LOOP, param_2, -1);
    }
}

/* 00002164-00002320       .text speed_pos_calc__FP8st_class */
static void speed_pos_calc(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_1c;
    cXyz local_28;

    if ((i_this->mAcch.ChkGroundHit()) && (i_this->m02E4 != 0)) {
        cLib_addCalcAngleS2(
            &actor->current.angle.y, cM_atan2s(i_this->mPlayerPos.x - actor->current.pos.x, i_this->mPlayerPos.z - actor->current.pos.z), 2, i_this->m02E4
        );
        i_this->m02E4 = 0;
    }
    cMtx_YrotS(*calc_mtx, actor->current.angle.y + i_this->m0302);
    local_1c.x = 0.0f;
    local_1c.y = 0.0f;
    local_1c.z = actor->speedF;
    MtxPosition(&local_1c, &local_28);
    cLib_addCalc2(&actor->speedF, i_this->m02DC, 1.0f, i_this->m02E0);
    i_this->m02E0 = 1.0f;
    actor->speed.x = local_28.x;
    actor->speed.z = local_28.z;
    if (i_this->m1DE0 > 0.1f) {
        cMtx_YrotS(*calc_mtx, i_this->m1DDE);
        local_1c.x = 0.0f;
        local_1c.y = 0.0f;
        local_1c.z = i_this->m1DE0;
        MtxPosition(&local_1c, &local_28);
        actor->speed += local_28;
    }
    cLib_addCalc0(&i_this->m1DE0, 1.0f, REG0_F(9) + 2.5f);
    actor->current.pos.x += actor->speed.x;
    actor->current.pos.y += actor->speed.y;
    actor->speed.y -= 5.0f;
    actor->current.pos.z += actor->speed.z;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
}

/* 00002320-00002604       .text jyunkai__FP8st_class */
static void jyunkai(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
    i_this->m02DC = 0.0f;
    i_this->m02E0 = 5.0f;
    switch (i_this->m02C4) {
        case 0:
            {
                i_this->m1F84 = 2;
                int frame = (int)i_this->mpMorf->getFrame();
                if (((frame >= l_HIO.m06) && (frame <= l_HIO.m0A)) || ((frame >= l_HIO.m08) && (frame <= l_HIO.m0C))) {
                    i_this->m02DC = l_HIO.m10;
                    i_this->m02E4 = 0x800;
                    if ((frame == l_HIO.m06) || (frame == l_HIO.m08)) {
                        fopAcM_seStart(actor, JA_SE_ST_WALK, 0);
                    }
                }
                i_this->mPlayerPos = player->current.pos;
                if (i_this->mTimers[0] == 0) {
                    wait_set(i_this);
                    i_this->m02C4 = 1;
                    i_this->mTimers[0] = cM_rndF(60.0f) + 100.0f;
                }
                break;
            }
        case 1:
            if (i_this->mTimers[0] == 0) {
                walk_set(i_this, REG8_F(0) + 1.0f);
                i_this->m02C4 = 0;
                i_this->mTimers[0] = cM_rndF(60.0f) + 100.0f;
                i_this->m1F84 = 1;
            }
            break;
    }
#if VERSION == VERSION_DEMO
    if ((i_this->mTimers[1] == 0) && (fopAcM_searchPlayerDistance(actor) < 280.0f))
#else
    if (((!dComIfGp_event_runCheck()) && (i_this->mTimers[1] == 0)) && (fopAcM_searchPlayerDistance(actor) < 280.0f))
#endif
    {
        if (i_this->m1DD0 == 10) {
            i_this->mActionState = 5;
            i_this->m02C4 = 0;
            i_this->m0308 = 0.0f;
            if (cM_rndF(1.0f) < 0.5f) {
                if (i_this->m02CC == 0) {
                    i_this->mFightBehavior = 0;
                } else {
                    i_this->mFightBehavior = 5;
                }
            } else if (i_this->m02CC == 0) {
                i_this->mFightBehavior = 10;
            } else {
                i_this->mFightBehavior = 0xF;
            }
        } else if (i_this->m1DD0 == 0) {
            i_this->mActionState = 0x1d;
            if (i_this->m1DC8 == 0) {
                i_this->m02C4 = 0;
            } else {
                i_this->m02C4 = 3;
            }
        }
    }
}

/* 00002604-00002630       .text attack_set__FP8st_classifUc */
static void attack_set(st_class* i_this, int bckFileIdx, f32 morf, u8 loopMode) {
    anm_init(i_this, bckFileIdx, morf, loopMode, 1.0f, -1);
}

/* 00002630-000029F8       .text buki_smoke_set__FP8st_class */
static void buki_smoke_set(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_b4;
    cXyz local_c0;
    cXyz local_cc;
    cXyz local_d8;

    i_this->m1E88[1].remove();
    MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0xb), *calc_mtx);
    local_b4.x = (REG0_F(13) + 80.0f) + 30.0f;
    local_b4.y = 0.0f;
    local_b4.z = 0.0f;
    MtxPosition(&local_b4, &local_c0);
    local_c0.y = REG0_F(8) + (i_this->mAcch.GetGroundH() + 30.0f);
    JPABaseEmitter* emitter =
        dComIfGp_particle_setToon(dPa_name::ID_AK_JT_ELEMENTSMOKE01, &local_c0, NULL, NULL, 0xB9, &i_this->m1E88[1], fopAcM_GetRoomNo(actor));
    if (emitter != NULL) {
        emitter->setMaxFrame(1);
        emitter->setRate(20.0f);
        emitter->setAwayFromCenterSpeed(20.0f);
        JGeometry::TVec3<f32> scale(1.0f, 0.0f, 1.0f);
        emitter->setEmitterScale(scale);
    }
    dBgS_LinChk linChk;
    local_cc = local_c0;
    local_cc.y += 100.0f;
    local_d8 = local_c0;
    local_d8.y -= 200.0f;
    linChk.Set(&local_cc, &local_d8, actor);
    if (dComIfG_Bgsp()->LineCross(&linChk)) {
        mDoAud_seStart(JA_SE_LK_HAMMER_HIT, &actor->current.pos, dComIfG_Bgsp()->GetMtrlSndId(linChk), dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
    }
}

/* 000029F8-00003F4C       .text fight__FP8st_class */
static void fight(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 dVar8;
    f32 dVar10;
    f32 dVar9;
    cXyz local_d8;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    dVar10 = 0.0f;
    dVar9 = 0.02f;
    dVar8 = fopAcM_searchPlayerDistance(actor);
    i_this->mPlayerPos = player->current.pos;
    i_this->m02E4 = 0x200;
    switch (i_this->m02C4) {
        case 0:
            i_this->m02DC = 0.0f;
    }
    i_this->m0ED1 = 0;
    switch (i_this->mFightBehavior) {
        case 0:
            attack_set(i_this, ST_BCK_ATTACKR1, 5.0f, J3DFrameCtrl::EMode_NONE);
            i_this->mFightBehavior++;
            break;
        case 1:
            if ((int)i_this->mpMorf->getFrame() == 10) {
                fopAcM_seStart(actor, JA_SE_CM_ST_CLUB_UP, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_ST_ATTACK_S, 0);
            }
            if (i_this->mpMorf->isStop()) {
                attack_set(i_this, ST_BCK_ATTACKR1_END, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->mFightBehavior++;
            }
            break;
        case 2:
            if ((int)i_this->mpMorf->getFrame() == 6) {
                fopAcM_seStart(actor, JA_SE_CM_ST_CLUB_SWING, 0);
                i_this->m1F80 = REG0_S(5) + 0x17;
                i_this->m1F82 = 0;
                i_this->m1F7E = (actor->current.angle.y + 0x4ee0) + REG0_S(6);
            }
            i_this->m0ED1 = 1;
            if (i_this->mpMorf->isStop()) {
                attack_set(i_this, ST_BCK_OTOTOR, 1.0f, J3DFrameCtrl::EMode_LOOP);
                i_this->mFightBehavior++;
                i_this->mTimers[0] = cM_rndF(50.0f) + 30.0f;
            }
            break;
        case 3:
            i_this->m02DC = REG8_F(3) + -2.0f;
            i_this->m0302 = ((REG0_F(13) + 10000.0f) * cM_ssin(i_this->m02E8 * (REG0_S(8) + 500)));
            if (i_this->mTimers[0] == 0) {
                if ((cM_rndF(1.0f) < 0.5f) || (dVar8 < 300.0f)) {
                    if (cM_rndF(1.0f) < 0.5f) {
                        attack_set(i_this, ST_BCK_ATTACKREND, 5.0f, J3DFrameCtrl::EMode_NONE);
                        i_this->m02CC = 1;
                        i_this->mFightBehavior = 0x65;
                    } else {
                        attack_set(i_this, ST_BCK_ATTACKR2, 5.0f, J3DFrameCtrl::EMode_NONE);
                        i_this->m02CC = 0;
                        i_this->mFightBehavior = 100;
                    }
                } else {
                    i_this->mFightBehavior = 0x19;
                }
            }
            break;
        case 5:
            attack_set(i_this, ST_BCK_ATTACKL1, 5.0f, J3DFrameCtrl::EMode_NONE);
            i_this->mFightBehavior++;
            break;
        case 6:
            if ((int)i_this->mpMorf->getFrame() == 15) {
                fopAcM_seStart(actor, JA_SE_CM_ST_CLUB_UP, 0);
                fopAcM_monsSeStart(actor, JA_SE_CV_ST_ATTACK_S, 0);
            }
            if (i_this->mpMorf->isStop()) {
                attack_set(i_this, ST_BCK_ATTACKL1_END, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->mFightBehavior++;
            }
            break;
        case 7:
            if ((int)i_this->mpMorf->getFrame() == 8) {
                fopAcM_seStart(actor, JA_SE_CM_ST_CLUB_SWING, 0);
                i_this->m1F80 = REG0_S(5) + 0x17;
                i_this->m1F82 = 1;
                i_this->m1F7E = (actor->current.angle.y + 0x10000 + REG0_S(6)) - 0x72a0;
            }
            i_this->m0ED1 = 1;
            if (i_this->mpMorf->isStop()) {
                attack_set(i_this, ST_BCK_OTOTOL, 1.0f, J3DFrameCtrl::EMode_LOOP);
                i_this->mFightBehavior++;
                i_this->mTimers[0] = cM_rndF(50.0f) + 30.0f;
            }
            break;
        case 8:
            i_this->m02DC = REG8_F(3) + -2.0f;
            i_this->m0302 = ((REG0_F(13) + 10000.0f) * cM_ssin(i_this->m02E8 * (REG0_S(8) + 500)));
            if (i_this->mTimers[0] == 0) {
                if ((cM_rndF(1.0f) < 0.5f) || (dVar8 < 300.0f)) {
                    if (cM_rndF(1.0f) < 0.5f) {
                        attack_set(i_this, ST_BCK_ATTACKLEND, 5.0f, J3DFrameCtrl::EMode_NONE);
                        i_this->m02CC = 0;
                        i_this->mFightBehavior = 0x65;
                    } else {
                        attack_set(i_this, ST_BCK_ATTACKL2, 5.0f, J3DFrameCtrl::EMode_NONE);
                        i_this->m02CC = 1;
                        i_this->mFightBehavior = 100;
                    }
                } else {
                    i_this->mFightBehavior = 0x14;
                }
            }
            break;
        case 10:
            attack_set(i_this, ST_BCK_ATTACKR1, 5.0f, J3DFrameCtrl::EMode_NONE);
            i_this->mFightBehavior++;
            fopAcM_monsSeStart(actor, JA_SE_CV_ST_ATTACK_L, 0);
            break;
        case 0xb:
            if (i_this->mpMorf->isStop()) {
                attack_set(i_this, ST_BCK_KAITENR1, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->mFightBehavior++;
            }
            break;
        case 0xc:
            dVar10 = 1.0f;
            dVar9 = 0.1f;
            if (i_this->mpMorf->isStop()) {
                i_this->mFightBehavior++;
                i_this->mTimers[0] = cM_rndF(50.0f) + 30.0f;
                i_this->m1F80 = 0xf;
                i_this->m1F82 = 2;
                i_this->m1F7E = (actor->current.angle.y + 0x2000) + REG0_S(8);
            }
            break;
        case 0xd:
            i_this->m1F80 = 0xf;
            i_this->m02DC = REG8_F(3) + 10.0f;
            dVar10 = 1.0f;
            dVar9 = 0.1f;
            i_this->m0302 = (s16)(int)((REG0_F(13) + 10000.0f) * cM_ssin(i_this->m02E8 * (REG0_S(8) + 500)));
            if (((i_this->mTimers[0] == 0) && (-0x400 < i_this->m0304)) && (i_this->m0304 < 0x400)) {
                attack_set(i_this, ST_BCK_KAITENR1_END, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->mFightBehavior++;
            }
            break;
        case 0xe:
            if ((i_this->mpMorf->isStop()) && (std::fabsf(i_this->m0308) < 0.01f)) {
                attack_set(i_this, ST_BCK_OTOTOR, 5.0f, J3DFrameCtrl::EMode_LOOP);
                i_this->mTimers[0] = cM_rndF(50.0f) + 30.0f;
                i_this->mFightBehavior = 3;
            }
            break;
        case 0xf:
            attack_set(i_this, ST_BCK_ATTACKL1, 5.0f, J3DFrameCtrl::EMode_NONE);
            i_this->mFightBehavior++;
            fopAcM_monsSeStart(actor, JA_SE_CV_ST_ATTACK_L, 0);
            break;
        case 0x10:
            if (i_this->mpMorf->isStop()) {
                attack_set(i_this, ST_BCK_KAITENL1, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->mFightBehavior++;
            }
            break;
        case 0x11:
            dVar10 = -1.0f;
            dVar9 = 0.1f;
            if (i_this->mpMorf->isStop()) {
                i_this->mFightBehavior++;
                i_this->mTimers[0] = cM_rndF(50.0f) + 30.0f;
                i_this->m1F80 = 0xf;
                i_this->m1F82 = 2;
                i_this->m1F7E = (actor->current.angle.y + 0x2000) + REG0_S(9);
            }
            break;
        case 0x12:
            i_this->m1F80 = 0xf;
            i_this->m02DC = REG8_F(3) + 10.0f;
            dVar10 = -1.0f;
            dVar9 = 0.1f;
            i_this->m0302 = (s16)(int)((REG0_F(13) + 10000.0f) * cM_ssin(i_this->m02E8 * (REG0_S(8) + 500)));
            if (((i_this->mTimers[0] == 0) && (-0x400 < i_this->m0304)) && (i_this->m0304 < 0x400)) {
                attack_set(i_this, ST_BCK_KAITENL1_END, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->mFightBehavior++;
            }
            break;
        case 0x13:
            if ((i_this->mpMorf->isStop()) && (std::fabsf(i_this->m0308) < 0.01f)) {
                attack_set(i_this, ST_BCK_OTOTOL, 5.0f, J3DFrameCtrl::EMode_LOOP);
                i_this->mTimers[0] = cM_rndF(50.0f) + 30.0f;
                i_this->mFightBehavior = 8;
            }
            break;
        case 0x14:
            attack_set(i_this, ST_BCK_KAITENR2, 5.0f, J3DFrameCtrl::EMode_NONE);
            i_this->mFightBehavior++;
            break;
        case 0x15:
            dVar10 = 1.0f;
            dVar9 = 0.1f;
            if (i_this->mpMorf->isStop()) {
                i_this->mFightBehavior++;
                i_this->mTimers[0] = cM_rndF(50.0f) + 30.0f;
                i_this->m1F80 = 0xf;
                i_this->m1F82 = 2;
                i_this->m1F7E = (actor->current.angle.y + 0x2000) + REG0_S(8);
            }
            break;
        case 0x16:
            i_this->m1F80 = 0xf;
            i_this->m02DC = REG8_F(3) + 10.0f;
            dVar10 = 1.0f;
            dVar9 = 0.1f;
            i_this->m0302 = (s16)(int)((REG0_F(13) + 10000.0f) * cM_ssin(i_this->m02E8 * (REG0_S(8) + 500)));
            if (((i_this->mTimers[0] == 0) && (-0x400 < i_this->m0304)) && (i_this->m0304 < 0x400)) {
                attack_set(i_this, ST_BCK_KAITENR2_END, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->mFightBehavior++;
            }
            break;
        case 0x17:
            if ((i_this->mpMorf->isStop()) && (std::fabsf(i_this->m0308) < 0.01f)) {
                attack_set(i_this, ST_BCK_OTOTOR, 5.0f, J3DFrameCtrl::EMode_LOOP);
                i_this->mTimers[0] = cM_rndF(50.0f) + 30.0f;
                i_this->mFightBehavior = 3;
            }
            break;
        case 0x19:
            attack_set(i_this, ST_BCK_KAITENL2, 5.0f, J3DFrameCtrl::EMode_NONE);
            i_this->mFightBehavior++;
            break;
        case 0x1a:
            i_this->m0ED1 = 2;
            dVar10 = -1.0f;
            dVar9 = 0.1f;
            if (i_this->mpMorf->isStop()) {
                i_this->mFightBehavior++;
                i_this->mTimers[0] = cM_rndF(50.0f) + 30.0f;
                i_this->m1F80 = 0xf;
                i_this->m1F82 = 2;
                i_this->m1F7E = (actor->current.angle.y + 0x2000) + REG0_S(9);
            }
            break;
        case 0x1b:
            i_this->m1F80 = 0xf;
            i_this->m02DC = REG8_F(3) + 10.0f;
            dVar10 = -1.0f;
            dVar9 = 0.1f;
            i_this->m0302 = (s16)(int)((REG0_F(13) + 10000.0f) * cM_ssin(i_this->m02E8 * (REG0_S(8) + 500)));
            if (((i_this->mTimers[0] == 0) && (-0x400 < i_this->m0304)) && (i_this->m0304 < 0x400)) {
                attack_set(i_this, ST_BCK_KAITENL2_END, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->mFightBehavior++;
            }
            break;
        case 0x1c:
            if ((i_this->mpMorf->isStop()) && (std::fabsf(i_this->m0308) < 0.01f)) {
                attack_set(i_this, ST_BCK_OTOTOL, 5.0f, J3DFrameCtrl::EMode_LOOP);
                i_this->mFightBehavior = 8;
                i_this->mTimers[0] = cM_rndF(50.0f) + 30.0f;
            }
            break;
        case 100:
            if ((int)i_this->mpMorf->getFrame() == 15) {
                fopAcM_seStart(actor, JA_SE_CM_ST_CLUB_SWING, 0);
            }
            if ((int)i_this->mpMorf->getFrame() == 24) {
                buki_smoke_set(i_this);
            }
            i_this->m0ED1 = 1;
        case 0x65:
            if (i_this->mpMorf->isStop()) {
                i_this->mActionState = 0;
                wait_set(i_this);
                i_this->m02C4 = 1;
                i_this->mTimers[1] = cM_rndF(40.0f);
            }
            break;
    }
    cLib_addCalc2(&i_this->m0308, dVar10, 1.0f, dVar9);
    i_this->m0304 += (s16)((REG0_F(11) + 5000.0f) * i_this->m0308);
    if (std::fabsf(i_this->m0308) > 0.05f) {
        s16 r4 = i_this->m02CA;
        i_this->m02CA = r4 + (int)((REG0_F(11) + 5000.0f) * std::fabsf(i_this->m0308));
        if ((i_this->m02CA >= 100) && (r4 < 100)) {
            u32 r23 = (std::fabsf(i_this->m0308 * 100.0f));
            if (r23 < 0x32) {
                r23 = 0x32;
            }
            fopAcM_seStart(actor, JA_SE_CM_ST_CLUB_SWING_L, r23);
        }
    } else {
        i_this->m02CA = 0;
    }
    MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0xb), *calc_mtx);
    local_d8.x = REG0_F(10) + 80.0f;
    local_d8.y = 0.0f;
    local_d8.z = 0.0f;
    i_this->m0EC4 = i_this->m0EB8;
    MtxPosition(&local_d8, &i_this->m0EB8);
    if (std::fabsf(i_this->m0308) > 0.5f) {
        dBgS_LinChk linChk;
        i_this->m0ED1 = 2;
        if ((std::fabsf(i_this->m0308) > 0.9f) && (std::fabsf(actor->speedF) > std::fabsf(i_this->m02DC) * 0.9f)) {
            linChk.Set(&i_this->m0EC4, &i_this->m0EB8, actor);
            if (dComIfG_Bgsp()->LineCross(&linChk)) {
                i_this->mActionState = 0;
                wait_set(i_this);
                i_this->m02C4 = 1;
                i_this->mTimers[1] = cM_rndF(40.0f);
            }
        }
    }
    if (std::fabsf(i_this->m0308) > 0.5f) {
        i_this->m0ED1 = 2;
    }
}

/* 00003F4C-000044C8       .text fight2__FP8st_class */
static void fight2(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_2c;
    cXyz cStack_38;

    bool r30 = false;
    local_2c.x = 0.0f;
    local_2c.y = 0.0f;
    local_2c.z = 0.0f;
    i_this->m02DC = 0.0f;
    switch (i_this->m02C4) {
        case 0:
            i_this->m02F6 = 10;
            i_this->m0ED0 = 1;
            attack_set(i_this, ST_BCK_KYORO, 5.0f, J3DFrameCtrl::EMode_NONE);
            i_this->m02C4++;
            fopAcM_monsSeStart(actor, JA_SE_CV_ST_NO_CLUB, 0);
            break;
        case 1:
            i_this->m02F6 = 10;
            i_this->m0ED0 = 1;
            if (i_this->mpMorf->isStop()) {
                attack_set(i_this, ST_BCK_NUKU1, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->m02C4++;
            }
            break;
        case 2:
            i_this->m02F6 = 10;
            i_this->m0ED0 = 1;
            if (i_this->mpMorf->isStop()) {
                attack_set(i_this, ST_BCK_NUKU2, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->m02C4 = 0x65;
                i_this->m1DC8 = 1;
                MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0x03), *calc_mtx);
                MtxPosition(&local_2c, &cStack_38);
                dComIfGp_particle_set(dPa_name::ID_AK_SN_STBIKON00, &cStack_38, &actor->shape_angle);
                fopAcM_seStart(actor, JA_SE_CM_ST_PULLOUT_ARM, 0);
            }
            break;
        case 3:
            i_this->m1DC8 = 3;
            attack_set(i_this, ST_BCK_HONE_ATTACK, 3.0f, J3DFrameCtrl::EMode_LOOP);
            i_this->m02C4++;
            i_this->mTimers[0] = (int)cM_rndF(3.0f) * 0x28;
            fopAcM_monsSeStart(actor, JA_SE_CV_ST_NUNCHAKU_L, 0);
            break;
        case 4:
            i_this->m0ED1 = 1;
            if (((((int)i_this->mpMorf->getFrame() == 1) || ((int)i_this->mpMorf->getFrame() == 11)) || ((int)i_this->mpMorf->getFrame() == 21)) ||
                ((int)i_this->mpMorf->getFrame() == 31))
            {
                fopAcM_seStart(actor, JA_SE_CM_ST_SWING_NUN_L, 0);
            }
            if (i_this->mTimers[0] == 0) {
                r30 = true;
            }
            break;
        case 0x32:
            anm_init(i_this, ST_BCK_WAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m1DC8 = 1;
            i_this->m02C4++;
            i_this->mTimers[0] = 0x14;
        case 0x33:
            i_this->m02F6 = 10;
            i_this->m0ED0 = 1;
            if (i_this->mTimers[0] == 0) {
                attack_set(i_this, ST_BCK_TUKERU1, 5.0f, J3DFrameCtrl::EMode_NONE);
                i_this->m02C4++;
            }
            break;
        case 0x34:
            i_this->m02F6 = 10;
            i_this->m0ED0 = 1;
            if (i_this->mpMorf->isStop()) {
                attack_set(i_this, ST_BCK_TUKERU2, 1.0f, J3DFrameCtrl::EMode_NONE);
                i_this->m02C4++;
                i_this->m1DC8 = 0;
            }
            break;
        case 0x35:
            i_this->m02F6 = 10;
            i_this->m0ED0 = 1;
            if (i_this->mpMorf->isStop()) {
                i_this->m02C4 = 100;
                anm_init(i_this, ST_BCK_FUKKI_WAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            }
            break;
        case 0x64:
            if (i_this->m1DD0 == 10) {
                r30 = true;
            }
            break;
        case 0x65:
            if (i_this->mpMorf->isStop()) {
                r30 = true;
            }
            break;
    }
    if (r30) {
        i_this->mActionState = 0;
        wait_set(i_this);
        i_this->m02C4 = 1;
        i_this->mTimers[1] = cM_rndF(40.0f);
    }
}

/* 000044C8-00004784       .text ground_wait__FP8st_class */
static void ground_wait(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 f31;

    i_this->m02F6 = 10;
    i_this->m0ED0 = DEMO_SELECT(1, 2);
    switch (i_this->m02C4) {
        case 0:
            actor->attention_info.flags = 0;
            fopAcM_OffStatus(actor, fopAcStts_SHOWMAP_e);
            if (i_this->m02B9 != 0xFF) {
                if (dComIfGs_isSwitch(i_this->m02B9 - 1, fopAcM_GetRoomNo(actor))) {
                    i_this->m02C4 = 1;
                }
            } else {
                if (i_this->mAmbushSightRange != 0xFF) {
                    f31 = i_this->mAmbushSightRange * 10.0f;
                } else {
                    f31 = 500.0f;
                }
                if (fopAcM_searchPlayerDistance(actor) < f31) {
                    i_this->m02C4 = 1;
                }
            }
            break;
        case 1:
            i_this->m02B9 = 0;
            fopAcM_seStart(actor, JA_SE_CM_ST_OUT_OF_GROUND, 0);
            anm_init(i_this, ST_BCK_START, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m02C4 = 2;
            actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
            i_this->m1E88[0].remove();
            dComIfGp_particle_setToon(dPa_name::ID_AK_ST_STSTARTSMOKE00, &actor->current.pos, NULL, NULL, 0xB9, &i_this->m1E88[0], fopAcM_GetRoomNo(actor));
            i_this->mTimers[0] = 60;
            break;
        case 2:
#if VERSION == VERSION_DEMO
            if ((i_this->mTimers[0] != 0) && ((i_this->mTimers[0] & 7) == 0) && (cM_rndF(1.0f) < 0.5f))
#else
            if ((fopAcM_CheckStatus(actor, fopAcStts_BOSS_e)) && (i_this->mTimers[0] != 0) && ((i_this->mTimers[0] & 7) == 0) && (cM_rndF(1.0f) < 0.5f))
#endif
            {
                dComIfGp_getVibration().StartShock(REG0_S(2) + DEMO_SELECT(2, 4), -0x21, cXyz(0.0f, 1.0f, 0.0f));
            }
            if (i_this->mpMorf->isStop()) {
                i_this->mActionState = 0;
                i_this->m02C4 = 0;
            }
            break;
    }
}

/* 00004784-00004990       .text kan_wait__FP8st_class */
static void kan_wait(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 f31;

    i_this->m02F6 = 10;
    i_this->m0ED0 = 2;
    switch (i_this->m02C4) {
        case 0:
            actor->attention_info.flags = 0;
            fopAcM_OffStatus(actor, fopAcStts_SHOWMAP_e);
            if (i_this->m02B9 != 0xFF) {
                if (dComIfGs_isSwitch(i_this->m02B9 - 1, fopAcM_GetRoomNo(actor))) {
                    i_this->m02C4 = 1;
                }
            } else {
                if (i_this->mAmbushSightRange != 0xFF) {
                    f31 = i_this->mAmbushSightRange * 10.0f;
                } else {
                    f31 = 500.0f;
                }
                if (fopAcM_searchPlayerDistance(actor) < f31) {
                    i_this->m02C4 = 1;
                }
            }
            break;
        case 1:
            if (i_this->mBehaviorType == BEHAVIOR_IN_HORIZONTAL_COFFIN) {
                anm_init(i_this, ST_BCK_YOKO_START, 1.0f, J3DFrameCtrl::EMode_NONE, 0.0f, -1);
            } else {
                anm_init(i_this, ST_BCK_TATE_START, 1.0f, J3DFrameCtrl::EMode_NONE, 0.0f, -1);
            }
            i_this->m02C4 = 2;
            i_this->m02B9 = 0;
            i_this->mTimers[0] = l_HIO.m18;
            i_this->mTimers[2] = l_HIO.m18 + 0x14;
        case 2:
            if (i_this->mTimers[0] == 0) {
                i_this->mpMorf->setPlaySpeed(1.0f);
                i_this->m02C4 = 3;
                actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
                fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
            }
            break;
        case 3:
            if (i_this->mpMorf->isStop()) {
                i_this->mActionState = 0;
                i_this->m02C4 = 0;
            }
            break;
    }
}

/* 00004990-00004CF0       .text st_break_wait__FP8st_class */
static void st_break_wait(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
#if VERSION > VERSION_DEMO
    cXyz local_24;
#endif

    i_this->m02DC = 0.0f;
    if (i_this->m1DDC == 0) {
        i_this->m02F6 = 10;
    }
    i_this->m0ED0 = 1;
    switch (i_this->m02C4) {
        case 0:
            anm_init(i_this, ST_BCK_FUKKI_WAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m02C4 = 1;
            i_this->mTimers[0] = l_HIO.m1A;
            i_this->m1DDC = l_HIO.m1A;
        case 1:
            if (i_this->mTimers[0] == 0) {
                i_this->m02C4 = 2;
                i_this->m0ED3 = 2;
                fopAcM_seStartCurrent(actor, JA_SE_CM_ST_RECOVER_BODY, 0);
#if VERSION > VERSION_DEMO
                i_this->m02F8 = 500;
#endif
            }
            break;
        case 2:
#if VERSION > VERSION_DEMO
            i_this->m0ED0 = 2;
#endif
            i_this->m1F68 = 1;
            if (i_this->m0ED2 >= 0x19) {
                i_this->m02C4 = 100;
                i_this->mTimers[0] = 10;
            }
            break;
        case 3:
#if VERSION > VERSION_DEMO
            i_this->m0ED0 = 2;
#endif
            i_this->m1F68 = 1;
            if ((i_this->m0ED2 >= 0x19) && (i_this->m1DD0 == 10)) {
                i_this->m02C4 = 100;
                i_this->mTimers[0] = 10;
            }
            break;
        case 0xA:
            anm_init(i_this, ST_BCK_FUKKI_WAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m02C4 = 0xb;
        case 0xB:
#if VERSION > VERSION_DEMO
            i_this->m0ED0 = 2;
#endif
            i_this->m1F68 = 1;
            if (i_this->m0ED2 >= 0x19) {
                i_this->m02C4 = 100;
                i_this->mTimers[0] = 10;
            }
            break;
        case 0x23:
        case 0x14:
            i_this->m1DDC = 100;
            i_this->mTimers[0] = 100;
#if VERSION > VERSION_DEMO
            if (i_this->m02C4 == 0x23) {
                actor->attention_info.flags = 0;
                fopAcM_OffStatus(actor, fopAcStts_SHOWMAP_e);
            }
#endif
            break;
        case 0x64:
            if ((i_this->m1F68 = 2, i_this->mTimers[0] == 0)) {
                i_this->mActionState = 0;
                wait_set(i_this);
                i_this->m02C4 = 1;
                i_this->mTimers[1] = cM_rndF(40.0f);
                i_this->m1E84 = 0x10;
            }
            break;
    }
#if VERSION > VERSION_DEMO
    if (i_this->m02F8 != 0) {
        i_this->m02F8--;
        if (i_this->m02F8 == 0) {
            local_24 = actor->current.pos;
            local_24.y += 100.0f;
            fopAcM_createDisappear(actor, &local_24, 10, daDisItem_IBALL_e);
            fopAcM_delete(actor);
            if (i_this->mDeathSwitch != 0) {
                dComIfGs_onSwitch(i_this->mDeathSwitch, fopAcM_GetRoomNo(actor));
            }
            fopAcM_onActor(actor);
            fopAc_ac_c* heldWeapon = fopAcM_SearchByID(i_this->mHeldWeaponEntityId);
            if (heldWeapon != NULL) {
                fopAcM_cancelCarryNow(heldWeapon);
            }
        }
    }
#endif
}

/* 00004CF0-00005098       .text head_damage__FP8st_class */
static void head_damage(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int frame;
    cXyz local_24;
    cXyz cStack_30;

    local_24.setall(0.0f);
    csXyz local_38(actor->shape_angle);
    local_38.y -= 0x8000;
    i_this->m02DC = 0.0f;
    i_this->m0ED0 = 1;
    switch (i_this->m02C4) {
        case 0:
            anm_init(i_this, ST_BCK_MAHIR, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m02C4 = 1;
            fopAcM_seStart(actor, JA_SE_CM_ST_TURN_HEAD, 0);
            break;
        case 1:
            frame = (int)i_this->mpMorf->getFrame();
            if (frame == 32) {
                MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0xf), *calc_mtx);
                MtxPosition(&local_24, &cStack_30);
                dComIfGp_particle_set(dPa_name::ID_AK_SN_STBIKON00, &cStack_30, &local_38);
                fopAcM_seStart(actor, JA_SE_CM_ST_STOP_HEAD, 0);
            }
            if (i_this->mpMorf->isStop()) {
                i_this->mActionState = 0;
                wait_set(i_this);
                i_this->m02C4 = 1;
                i_this->mTimers[1] = cM_rndF(40.0f);
            }
            break;
        case 10:
            anm_init(i_this, ST_BCK_MAHI2, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m02C4 = 11;
            fopAcM_seStart(actor, JA_SE_CM_ST_TURN_HEAD, 0);
            break;
        case 11:
            frame = (int)i_this->mpMorf->getFrame();
            if (frame == 30) {
                MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0xf), *calc_mtx);
                MtxPosition(&local_24, &cStack_30);
                dComIfGp_particle_set(dPa_name::ID_AK_SN_STBIKON00, &cStack_30, &local_38);
                fopAcM_seStart(actor, JA_SE_CM_ST_STOP_HEAD, 0);
            }
            if (i_this->mpMorf->isStop()) {
                i_this->mActionState = 0x20;
                i_this->m02C4 = -1;
            }
            break;
    }
}

/* 000050D4-00005484       .text ue_move__FP8st_class */
static void ue_move(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int frame;
    JPABaseEmitter* emitter;
    cXyz local_30;
    cXyz cStack_3c;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
#if VERSION == VERSION_DEMO
    s8 r27 = 0;
#endif
    switch (i_this->m02C4) {
        case -1:
            anm_init(i_this, ST_BCK_UE_JUMP1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m02C4 = 1;
            actor->speed.y = 30.0f;
            break;
        case 0:
            anm_init(i_this, ST_BCK_UE_JUMP1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m02C4 = 1;
            actor->current.angle.y = fopAcM_searchPlayerAngleY(actor) + 0x8000;
            actor->speed.y = DEMO_SELECT(50.0f, 40.0f);
            i_this->m02DC = DEMO_SELECT(30.0f, 20.0f);
            actor->speedF = DEMO_SELECT(30.0f, 20.0f);
            break;
        case 1:
            if (i_this->mAcch.ChkGroundHit()) {
                anm_init(i_this, ST_BCK_UE_JUMP2, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->m02C4 = 2;
            }
            break;
        case 2:
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, ST_BCK_UE_WALK, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.2f, -1);
                i_this->m02C4 = 3;
            }
            break;
        case 3:
            cMtx_YrotS(*calc_mtx, (fopAcM_searchPlayerAngleY(actor) + 0x8000) + (s16)cM_rndFX(10000.0f));
            local_30.x = 0.0f;
            local_30.y = 0.0f;
            local_30.z = 500.0f;
            MtxPosition(&local_30, &cStack_3c);
            i_this->mPlayerPos = player->current.pos + cStack_3c;
            i_this->m02C4 = 4;
            i_this->mTimers[0] = 0x14;
        case 4:
            frame = (int)i_this->mpMorf->getFrame();
            if (frame == 10) {
                emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_STASE00, &actor->eyePos);
                if (emitter != NULL) {
                    emitter->setGlobalRTMatrix(i_this->mpMorf->getModel()->getAnmMtx(0xF));
                }
            }
            i_this->m02DC = REG8_F(1) + 10.0f;
            i_this->m02E4 = 0x1000;
            if (i_this->mTimers[0] == 0) {
                i_this->m02C4 = 3;
            }
            if (fopAcM_searchPlayerDistance(actor) > 530.0f) {
                anm_init(i_this, ST_BCK_UE_WAIT, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->m02C4 = 5;
                i_this->mTimers[0] = 10;
            }
            break;
        case 5:
            i_this->m02DC = 0.0f;
            i_this->m02E4 = 0x2000;
            i_this->mPlayerPos = player->current.pos;
            if ((i_this->mTimers[0] == 0) && (fopAcM_searchPlayerDistance(actor) < 480.0f)) {
                i_this->m02C4 = -1;
            }
            break;
    }
#if VERSION == VERSION_DEMO
    if (r27 != 0) {
        fopAcM_delete(actor);
    }
#else
    if (i_this->mAcch.GetGroundH() == -G_CM3D_F_INF) {
        actor->current.pos = actor->home.pos;
        actor->old.pos = actor->home.pos;
    }
#endif
}

/* 00005484-000057A0       .text sita_move__FP8st_class */
static void sita_move(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    int frame;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
#if VERSION == VERSION_DEMO
    actor->attention_info.flags = 0;
    fopAcM_OffStatus(actor, fopAcStts_SHOWMAP_e);
#else
    actor->eyePos = actor->current.pos;
    actor->eyePos.y += 70.0f;
    actor->attention_info.position = actor->eyePos;
    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
#endif
    switch (i_this->m02C4) {
        case 0:
            i_this->m02C4 = 1;
            i_this->mTimers[0] = 60;
            i_this->mTimers[1] = cM_rndF(200.0f) + 350.0f;
        case 1:
            anm_init(i_this, ST_BCK_SITA_WALK, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.2f, -1);
            i_this->m02C4 = 2;
        case 2:
            i_this->m02C4 = 3;
        case 3:
            i_this->m02DC = REG8_F(1) + 10.0f;
            i_this->m02E4 = 0x800;
            i_this->mPlayerPos = player->current.pos;
            if ((i_this->mTimers[0] == 0) && (fopAcM_searchPlayerDistance(actor) < DEMO_SELECT(200.0f, 260.0f))) {
                i_this->m02C4 = 5;
            }
            break;
        case 5:
            i_this->mPlayerPos = player->current.pos;
            i_this->m02E4 = 0x2000;
            anm_init(i_this, ST_BCK_KICK1, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m02C4 = 6;
            break;
        case 6:
            i_this->m02DC = REG8_F(1) + 5.0f;
            if (i_this->mpMorf->isStop()) {
                anm_init(i_this, ST_BCK_KICK2, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->m02C4 = 7;
            }
            break;
        case 7:
            frame = (int)i_this->mpMorf->getFrame();
            if (frame < 10) {
                i_this->m0ED1 = 3;
            }
            i_this->m02DC = REG8_F(1);
            if (i_this->mpMorf->isStop()) {
                i_this->m02C4 = 1;
                i_this->mTimers[0] = 0x14;
            }
    }
#if VERSION == VERSION_DEMO
    if (i_this->mTimers[1] == 0) {
        fopAc_ac_c* upperBody = fopAcM_SearchByID(i_this->mUpperBodyEntityId);
        if (upperBody != NULL) {
            i_this->m0ED3 = 0xb;
            i_this->mActionState = 0x1e;
            i_this->m02C4 = 10;
            upperBody = fopAcM_SearchByID(i_this->mUpperBodyEntityId);
            fopAcM_delete(upperBody);
        }
    }
#else
    fopAc_ac_c* upperBody = fopAcM_SearchByID(i_this->mUpperBodyEntityId);
    if (upperBody != NULL) {
        if (i_this->mTimers[1] < 5) {
            i_this->m0ED0 = 2;
        }
        i_this->m1E86 = 1;
        if (i_this->mTimers[1] == 0) {
            i_this->m0ED3 = 0xb;
            i_this->mActionState = 0x1e;
            i_this->m02C4 = 10;
            i_this->m02F8 = 0;
            fopAcM_delete(upperBody);
            i_this->m1E86 = 0;
        }
    }
#endif
}

/* 000057A0-00005950       .text St_move__FP8st_class */
static void St_move(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_18;

    MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0xB), *calc_mtx);
    local_18.x = 160.0f;
    local_18.y = REG0_F(11);
    local_18.z = REG0_F(12);
    MtxPosition(&local_18, &i_this->m0EAC);
    i_this->m1F84 = 0;
    switch (i_this->mActionState) {
        case 0:
            jyunkai(i_this);
            break;
        case 5:
            fight(i_this);
            break;
        case 0xf:
            ground_wait(i_this);
            break;
        case 0x10:
            kan_wait(i_this);
            break;
        case 0x1d:
            fight2(i_this);
            break;
        case 0x1e:
            st_break_wait(i_this);
            break;
        case 0x1f:
            head_damage(i_this);
            break;
        case 0x20:
            ue_move(i_this);
            break;
        case 0x21:
            sita_move(i_this);
    }
    if (i_this->mActionState != 0x10) {
        speed_pos_calc(i_this);
    }
#if VERSION == VERSION_DEMO
    if ((i_this->m1F84 != 0) && (i_this->m1DD0 == 10)) {
        if (i_this->m1F84 == 1) {
            if (i_this->m1F84_demo != NULL) {
                i_this->m1F84_demo->becomeInvalidEmitter();
                i_this->m1F88.remove();
            }
            i_this->m1F84_demo = dComIfGp_particle_setToon(
                dPa_name::ID_AK_ST_STWALKSMOKE00, &i_this->m0EAC, &actor->shape_angle, NULL, 0xB9, &i_this->m1F88, fopAcM_GetRoomNo(actor)
            );
        }
    } else if (i_this->m1F84_demo != NULL) {
        i_this->m1F84_demo->becomeInvalidEmitter();
        i_this->m1F88.remove();
        i_this->m1F84_demo = NULL;
    }
#else
    if ((i_this->m1F84 != 0) && (i_this->m1DD0 == 10)) {
        if ((i_this->m1F84 == 1) && (i_this->m1F88.getEmitter() == NULL)) {
            dComIfGp_particle_setToon(
                dPa_name::ID_AK_ST_STWALKSMOKE00, &i_this->m0EAC, &actor->shape_angle, NULL, 0xB9, &i_this->m1F88, fopAcM_GetRoomNo(actor)
            );
        }
    } else {
        i_this->m1F88.remove();
    }
#endif
}

static u8 hit_bit[] = {0x01, 0xFF, 0xFF, 0x02, 0x04, 0x08, 0x10};

/* 00005950-000060B4       .text damage_check__FP8st_class */
static void damage_check(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* heldWeapon;
    cXyz local_54;
    CcAtInfo atInfo;

#if VERSION > VERSION_DEMO
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
#endif
    i_this->mStts.Move();
    if (i_this->m02F6 == 0) {
        for (s32 i = 0; i < 7; i++) {
            if (i_this->m054C[i].ChkTgHit()) {
                atInfo.mpObj = i_this->m054C[i].GetTgHitObj();
                atInfo.pParticlePos = i_this->m054C[i].GetTgHitPosP();
                if (atInfo.mpObj->ChkAtType(AT_TYPE_LIGHT_ARROW)) {
                    i_this->mEnemyIce.mLightShrinkTimer = 1;
                    heldWeapon = fopAcM_SearchByID(i_this->mHeldWeaponEntityId);
                    if (heldWeapon != NULL) {
                        fopAcM_cancelCarryNow(heldWeapon);
                    }
                    i_this->m1DD0 = 0;
                    return;
                }
                i_this->m02F6 = 5;
                if ((i == 0) && (i_this->m1DD8 != 0)) {
                    s8 bVar1 = actor->stealItemLeft;
                    actor->stealItemLeft = 0;
                    cc_at_check(actor, &atInfo);
                    actor->stealItemLeft = bVar1;
                    if (
                        (actor->health <= 0)
#if VERSION > VERSION_DEMO
                        || (atInfo.mResultingAttackType == 9 || (atInfo.mResultingAttackType == 2))
#endif
                    ) {
                        head_anm_init(i_this, ST_BCK_HEADB_DEAD, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                        i_this->mParts[15].mPartState = 8;
#if VERSION > VERSION_DEMO
                        if ((atInfo.mResultingAttackType == 9) && (player->getCutType() != daPy_py_c::CUT_TYPE_HAMMER_SIDESWING)) {
                            i_this->mParts[15].mPartVelocity.x = 0.0f;
                            i_this->mParts[15].mPartVelocity.y = -5.0f;
                            i_this->mParts[15].mPartVelocity.z = 0.0f;
                            dScnPly_ply_c::setPauseTimer(6);
                        } else
#endif
                        {
                            i_this->mParts[15].mPartRotAdd.x = cM_rndFX(9000.0f);
                            i_this->mParts[15].mPartRotAdd.z = cM_rndFX(9000.0f);
#if VERSION == VERSION_DEMO
                            cMtx_YrotS(*calc_mtx, fopAcM_searchPlayerAngleY(actor));
                            local_54.x = 0.0f;
                            local_54.y = 50.0f;
                            local_54.z = -50.0f;
#else
                            cMtx_YrotS(*calc_mtx, player->shape_angle.y);
                            if (player->getCutType() == daPy_py_c::CUT_TYPE_HAMMER_SIDESWING) {
                                local_54.x = REG8_F(4) + -100.0f;
                                local_54.y = 30.0f;
                                local_54.z = 0.0f;
                                dScnPly_ply_c::setPauseTimer(6);
                            } else {
                                local_54.x = 0.0f;
                                local_54.y = 50.0f;
                                local_54.z = 50.0f;
                            }
#endif
                            MtxPosition(&local_54, &i_this->mParts[15].mPartVelocity);
                        }
                        i_this->mParts[15].mWaitTimer = 30;
                        fopAcM_monsSeStart(actor, JA_SE_CV_ST_DIE, 0);
                    } else {
                        head_anm_init(i_this, ST_BCK_HEADB_DAMAGE, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                        i_this->mParts[15].mPartState = 7;
                        i_this->mParts[15].mWaitTimer = 0x7f;
#if VERSION > VERSION_DEMO
                        i_this->m1E82 = REG8_S(2) + 0x14;
                        fopAcM_monsSeStart(actor, JA_SE_CV_ST_HIT_BODY, 0);
#endif
                    }
                } else {
                    at_power_check(&atInfo);
                    if (atInfo.mDamage != 0) {
                        mDoAud_onEnemyDamage();
                    }
                    if ((fopAcM_GetName(atInfo.mpActor) == PROC_HIMO2) && (actor->stealItemLeft != 0)) {
                        actor->stealItemLeft--;
                        fopAcM_createStealItem(&actor->current.pos, actor->itemTableIdx, fopAcM_GetRoomNo(actor), 0, actor->stealItemBitNo);
                        actor->stealItemBitNo++;
                    }
                    if (
                        (fopAcM_GetName(atInfo.mpActor) == PROC_PLAYER)
#if VERSION > VERSION_DEMO
                        || (atInfo.mResultingAttackType == 2)
#endif
                    ) {
#if VERSION > VERSION_DEMO
                        if (atInfo.mResultingAttackType == 2) {
                            i_this->m1E84 = 0;
                        }
#endif
                        def_se_set(actor, atInfo.mpObj, 0x34);
                        fopAcM_monsSeStart(actor, JA_SE_CV_ST_HIT_BODY, 0);
#if VERSION == VERSION_DEMO
                        i_this->m1DE4 = REG6_S(6) + 20;
#else
                        if (atInfo.mResultingAttackType == 9) {
                            i_this->m1DE4 = REG6_S(7) + 0x14;
                        } else {
                            i_this->m1DE4 = REG6_S(6) + 10;
                        }
#endif
                        i_this->m1E84 -= atInfo.mDamage;
                        mDoAud_bgmHitSound(atInfo.mHitSoundId);
                        if (i_this->m1E84 <= 0) {
#if VERSION == VERSION_DEMO
                            i_this->m02C4 = 0;
#endif
                            i_this->m1DC8 = 0;
                            if (((atInfo.mPlCutBit == 0x80) && (i_this->mActionState != 0x21)) && (i_this->mActionState != 0x20)) {
                                i_this->mActionState = 0x21;
#if VERSION > VERSION_DEMO
                                i_this->m02C4 = 0;
#endif
                                i_this->m0ED3 = 10;
                                i_this->mUpperBodyEntityId =
                                    fopAcM_create(PROC_ST, 0xe, &actor->current.pos, fopAcM_GetRoomNo(actor), &actor->home.angle, NULL, 0xff, NULL);
                                i_this->m1E84 = 5;
#if VERSION > VERSION_DEMO
                                i_this->m1E86 = 0;
#endif
                            } else {
#if VERSION == VERSION_DEMO
                                if (i_this->mActionState == 0x21) {
                                    i_this->m02C4 = 0x23;
                                }
                                if (i_this->mActionState == 0x20) {
                                    i_this->m02C4 = 0x14;
                                }
#else
                                if (i_this->mActionState == 0x21) {
                                    i_this->m02C4 = 0x23;
                                } else if ((i_this->mActionState == 0x20) || ((i_this->mActionState == 0x1F) && (i_this->m02C4 >= 0xA))) {
                                    i_this->m02C4 = 0x14;
                                } else {
                                    i_this->m02C4 = 0;
                                }
#endif
                                i_this->mActionState = 0x1e;
                                i_this->m0ED3 = 1;
#if VERSION > VERSION_DEMO
                                i_this->m02F8 = 0;
#endif
                                fopAcM_seStart(actor, JA_SE_CM_ST_BREAD_BODY, 0);
                                fopAcM_monsSeStart(actor, JA_SE_CV_ST_BREAK, 0);
                            }
                        }
                    } else if (i == 0) {
                        i_this->m1DE4 = REG6_S(7) + DEMO_SELECT(10, 5);
                        if (
                            (i_this->mActionState == 0x20) ||
#if VERSION == VERSION_DEMO
                            // @bug Typo: Bitwise & instead of logical &.
                            ((i_this->mActionState == 0x1F) & (i_this->m02C4 >= 0xA))
#else
                            ((i_this->mActionState == 0x1F) && (i_this->m02C4 >= 0xA))
#endif
                        ) {
                            i_this->mActionState = 0x1F;
                            i_this->m02C4 = 10;
                        } else if (i_this->mActionState != 0x21) {
                            i_this->mActionState = 0x1F;
                            i_this->m02C4 = 0;
                        }
                        fopAcM_seStart(actor, JA_SE_CM_ST_HIT_HEAD_FLY, 0);
                        fopAcM_monsSeStart(actor, JA_SE_CV_ST_HIT_HEAD_FLY, 0);
                    } else {
                        def_se_set(actor, atInfo.mpObj, 0x34);
                        fopAcM_monsSeStart(actor, JA_SE_CV_ST_HIT_BODY, 0);
                        i_this->m1DE4 = REG6_S(7) + DEMO_SELECT(10, 8);
                        if ((i_this->mActionState != 0x21) && (i_this->mActionState != 0x20)) {
                            i_this->mActionState = 0;
                            wait_set(i_this);
                            i_this->m02C4 = 1;
                            i_this->mTimers[1] = 10;
                        }
                    }
                }
#if VERSION == VERSION_DEMO
                if (i_this->m1DE4 != 0) {
                    if ((i_this->mActionState == 0x21) || (i_this->mActionState == 0x20)) {
                        i_this->m1DE5 = -1;
                        i_this->m1DDE = atInfo.m0C.y;
                        i_this->m1DE0 = 40.0f + REG0_F(8);
                    } else {
                        i_this->m1DE5 = hit_bit[i];
                    }
                }
#endif
                break;
            }
        }
    }
#if VERSION == VERSION_DEMO
    f32 var_f30 = i_this->m1DE4 * (180.0f + REG6_F(5));
    f32 temp_f0 = 1500.0f + REG6_F(6);
    if (var_f30 > temp_f0) {
        var_f30 = temp_f0;
    }
    for (s32 i = 0; i < 26; i++) {
        if ((var_f30 > 1.0f) && (((i_this->m1DE5 & 1) && (i >= 0xE) && (i <= 0x10)) || ((i_this->m1DE5 & 2) && (i >= 3) && (i <= 7)) ||
                                 ((i_this->m1DE5 & 4) && (i >= 8) && (i <= 0xD)) || ((i_this->m1DE5 & 8) && (i >= 0x14) && (i <= 0x16)) ||
                                 ((i_this->m1DE5 & 0x10) && (i >= 0x17) && (i <= 0x19))))
        {
            i_this->m1DE6[i].x = var_f30 * cM_ssin(i_this->m02E8 * (REG8_S(5) + 0x2904) + (i * (REG8_S(6) + 0x1D4C)));
            i_this->m1DE6[i].y = var_f30 * cM_ssin(i_this->m02E8 * (REG8_S(5) + 0x2C24) + (i * (REG8_S(6) + 0x1B58)));
            i_this->m1DE6[i].z = var_f30 * cM_scos(i_this->m02E8 * (REG8_S(5) + 0x2AF8) + (i * (REG8_S(6) + 0x1C20)));
        } else {
            csXyz spC(0, 0, 0);
            i_this->m1DE6[i] = spC;
        }
    }
#endif
    if (i_this->m1DE4 != 0) {
        i_this->m1DE4--;
#if VERSION == VERSION_DEMO
        if (i_this->m1DE4 == 0) {
            i_this->m1DE5 = 0;
        }
#endif
    }
}

/* 000060B4-0000665C       .text part_posmove__FP8st_classP4st_p */
static f32 part_posmove(st_class* i_this, st_p* param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 f31;
    cXyz local_b8;
    cXyz local_c4;
#if VERSION == VERSION_DEMO
    dBgS_GndChk gndChk;

    param_2->mPartPrevPos = param_2->mPartPos;
    param_2->mPartPos += param_2->mPartVelocity;
    if (param_2->mPartVelocity.y > -100.0f) {
        param_2->mPartVelocity.y -= 5.0f;
    }
    param_2->mPartRot += param_2->mPartRotAdd;
    local_b8 = param_2->mPartPos;
    local_b8.y += 300.0f;
    gndChk.SetPos(&local_b8);
    f31 = dComIfG_Bgsp()->GroundCross(&gndChk);
    if (param_2->mPartPos.y <= f31) {
        param_2->mPartPos.y = f31;
    }
#else
    dBgS_LinChk linChk;

    param_2->mPartPrevPos = param_2->mPartPos;
    param_2->mPartPos += param_2->mPartVelocity;
    if (param_2->mPartVelocity.y >= -50.0f) {
        param_2->mPartVelocity.y -= 5.0f;
    }
    f31 = (param_2->mPartPos.y - 100.0f);
    param_2->mPartRot += param_2->mPartRotAdd;
    if (param_2->mPartVelocity.y > 0.0f) {
        local_b8 = param_2->mPartPos;
        local_b8.y += 100.0f;
        local_c4 = param_2->mPartPos;
        local_c4.y -= 100.0f;
        linChk.Set(&local_c4, &local_b8, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            local_c4 = *linChk.GetCrossP();
            if (param_2->mPartPos.y >= local_c4.y) {
                param_2->mPartPos.y = local_c4.y - 10.0f;
                param_2->mPartVelocity.y = -5.0f;
            }
        }
    } else {
        local_b8 = param_2->mPartPos;
        local_b8.y += 100.0f;
        local_c4 = param_2->mPartPos;
        local_c4.y -= 100.0f;
        linChk.Set(&local_b8, &local_c4, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            local_c4 = *linChk.GetCrossP();
            f31 = local_c4.y;
        }
    }
#endif
    local_b8 = param_2->mPartPos - param_2->mPartPrevPos;
    local_b8.y = 0.0f;
    if (local_b8.abs() > 0.0f) {
#if VERSION == VERSION_DEMO
        dBgS_LinChk linChk;
#endif
        cMtx_YrotS(*calc_mtx, cM_atan2s(local_b8.x, local_b8.z));
        local_b8.x = 0.0f;
        local_b8.y = 30.0f;
        local_b8.z = param_2->mPartVelocity.abs() + 30.0f;
        MtxPosition(&local_b8, &local_c4);
        local_b8 = param_2->mPartPos;
        local_b8.y += 30.0f;
        local_c4 += param_2->mPartPos;
        linChk.Set(&local_b8, &local_c4, actor);
        if (dComIfG_Bgsp()->LineCross(&linChk)) {
            param_2->mPartPos.x = param_2->mPartPrevPos.x;
            param_2->mPartPos.z = param_2->mPartPrevPos.z;
            param_2->mPartVelocity.x *= -0.3f;
            param_2->mPartVelocity.z *= -0.3f;
        }
    }
    return f31;
}

/* 0000665C-00007D38       .text part_move__FP8st_classi */
static void part_move(st_class* i_this, int jointIndex) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* emitter;
    fopAc_ac_c* pfVar4;
    st_class* upperBody;
    int frame;
    f32 dVar11;
    f32 fVar12;
    cXyz local_50;
    cXyz local_5c;

    st_p* this_part = &i_this->mParts[jointIndex];
    local_50.setall(0.0f);
    daBoko_c* heldWeapon = NULL;
    daBoko_c* var_r26 = NULL;
    if (jointIndex == 0xB) {
        heldWeapon = (daBoko_c*)fopAcM_SearchByID(i_this->mHeldWeaponEntityId);
        var_r26 = heldWeapon;
    }
    this_part->m3E++;
    if (this_part->mWaitTimer != 0) {
        this_part->mWaitTimer--;
    }
    if (i_this->mEnemyIce.mLightShrinkTimer == 0) {
        switch (this_part->mPartState) {
            case 0:
                MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(jointIndex), *calc_mtx);
                MtxPosition(&local_50, &this_part->mPartPos);
                if (i_this->m0ED3 == 1) {
                    this_part->m05 = 1;
                    this_part->mPartVelocity.x = cM_rndFX(20.0f);
                    this_part->mPartVelocity.y = cM_rndF(20.0f) + 40.0f;
                    this_part->mPartVelocity.z = cM_rndFX(20.0f);
                    if ((i_this->m0ED2 != 0) && (jointIndex != 0xb)) {
                        i_this->m0ED2--;
                    }
                    if (jointIndex == 0xF) {
                        i_this->m1DD8 = 1;
                        this_part->mPartState = 6;
                        this_part->mPartRotAdd.setall(0);
                        i_this->m1DDA = this_part->mPartRot.y;
                        head_anm_init(i_this, ST_BCK_HEADB_JUMP1, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                    } else {
                        this_part->mPartState = 5;
                        this_part->mPartRotAdd.x = cM_rndFX(6000.0f);
                        this_part->mPartRotAdd.y = cM_rndFX(6000.0f);
                    }
                }
                if (i_this->m0ED3 == 10) {
                    if (jointIndex < 0x13) {
                        this_part->mPartState = 10;
                        if (jointIndex == 0xB) {
                            this_part->mPartState = 5;
                            this_part->m05 = 1;
                            this_part->mPartVelocity.x = cM_rndFX(20.0f);
                            this_part->mPartVelocity.y = cM_rndF(20.0f) + 40.0f;
                            this_part->mPartVelocity.z = cM_rndFX(20.0f);
                            this_part->mPartRotAdd.x = cM_rndFX(6000.0f);
                            this_part->mPartRotAdd.y = cM_rndFX(6000.0f);
                        }
                        if ((i_this->m0ED2 != 0) && (jointIndex != 0xB)) {
                            i_this->m0ED2--;
                        }
                    }
                } else if ((i_this->m0ED3 == 0x14) && (jointIndex >= 0x13)) {
                    this_part->mPartState = 0xb;
                    if ((i_this->m0ED2 != 0) && (jointIndex != 0xB)) {
                        i_this->m0ED2--;
                    }
                }
                break;
            case 1:
                if (this_part->mWaitTimer != 0) {
                    if ((this_part->mWaitTimer & 4) != 0) {
                        this_part->mPartRot.y += 0x100;
                    } else {
                        this_part->mPartRot.y -= 0x100;
                    }
                } else {
                    MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(jointIndex), *calc_mtx);
                    MtxPosition(&local_50, &local_5c);
                    if (jointIndex == 0xF) {
                        local_5c.y -= REG6_F(13) + 20.0f;
                    }
                    local_50 = local_5c - this_part->mPartPos;
                    fVar12 = local_50.abs();
                    if (fVar12 < REG13_F(3) + 60.0f) {
                        this_part->mPartState = 2;
                    } else {
                        fVar12 = (fVar12 - 50.0f) * (REG8_F(8) + 1.0f);
                        if (fVar12 > REG8_F(9) + 300.0f) {
                            fVar12 = REG8_F(10) + 300.0f;
                        }
                        local_50.x += fVar12 * cM_ssin(this_part->m3E * 1000);
                        local_50.y += fVar12 * 0.5f + fVar12 * cM_scos(this_part->m3E * 0x44c) * 0.7f;
                        local_50.z += fVar12 * cM_scos(this_part->m3E * 0x4b0);
                        cLib_addCalcAngleS2(&this_part->m3A, cM_atan2s(local_50.x, local_50.z), 4, 0x2000);
                        fVar12 = std::sqrtf(SQUARE(local_50.x) + SQUARE(local_50.z));
                        cLib_addCalcAngleS2(&this_part->m38, -cM_atan2s(local_50.y, fVar12), 4, 0x2000);
                        cMtx_YrotS(*calc_mtx, this_part->m3A);
                        cMtx_XrotM(*calc_mtx, this_part->m38);
                        local_50.x = 0.0f;
                        local_50.y = 0.0f;
                        local_50.z = this_part->m44 * 20.0f;
                        MtxPosition(&local_50, &this_part->mPartVelocity);
                        VECAdd(&this_part->mPartPos, &this_part->mPartVelocity, &this_part->mPartPos);
                        if (jointIndex == 0xF) {
                            this_part->mPartRot.x = this_part->m38;
                            this_part->mPartRot.y = this_part->m3A;
                            this_part->mPartRot.z = this_part->m3C;
                        } else {
                            this_part->mPartRot += this_part->mPartRotAdd;
                        }
                        cLib_addCalc2(&this_part->m44, 1.0f, 1.0f, 0.01f);
                    }
                }
                break;
            case 2:
                MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(jointIndex), *calc_mtx);
                MtxPosition(&local_50, &local_5c);
                if (jointIndex == 0xF) {
                    local_5c.y -= REG6_F(13) + 20.0f;
                }
                cLib_addCalc2(&this_part->mPartPos.x, local_5c.x, 1.0f, std::fabsf(this_part->mPartVelocity.x) + 5.0f);
                cLib_addCalc2(&this_part->mPartPos.y, local_5c.y, 1.0f, std::fabsf(this_part->mPartVelocity.y) + 5.0f);
                cLib_addCalc2(&this_part->mPartPos.z, local_5c.z, 1.0f, std::fabsf(this_part->mPartVelocity.z) + 5.0f);
                local_50 = this_part->mPartPos - local_5c;
                this_part->mPartRot += this_part->mPartRotAdd;
                if (local_50.abs() <= 5.0f) {
                    this_part->mPartState = 0;
                    this_part->m05 = 0;
                    if ((i_this->m0ED2 < 0x19) && (jointIndex != 0xB)) {
                        i_this->m0ED2++;
                    }
                    if (jointIndex == 0xB) {
                        i_this->m1DD0 = 10;
                    }
                    if (jointIndex == 0xF) {
                        i_this->m1DD8 = 0;
                    }
                }
                break;
            case 5:
                dVar11 = (part_posmove(i_this, this_part) + 10.0f);
                if (std::fabsf(DEMO_SELECT(dVar11, actor->home.pos.y) - this_part->mPartPos.y) > 2000.0f) {
                    dVar11 = actor->current.pos.y;
                    this_part->mPartPos = actor->current.pos;
                }
                if (this_part->mPartPos.y <= dVar11) {
                    this_part->mPartPos.y = dVar11;
#if VERSION > VERSION_DEMO
                    if (((jointIndex == 0xB) && (heldWeapon != NULL)) && (i_this->m1DD0 >= 2)) {
                        fopAcM_cancelCarryNow(heldWeapon);
                        i_this->m1DD0 = 0;
                    }
#endif
                    if (this_part->mPartVelocity.y < -40.0f) {
                        this_part->mPartVelocity.y = cM_rndF(10.0f) + 20.0f;
                        this_part->mPartVelocity.x *= cM_rndFX(0.3f);
                        this_part->mPartVelocity.z *= cM_rndFX(0.3f);
#if VERSION == VERSION_DEMO
                        if (((jointIndex == 0xB) && (heldWeapon != NULL)) && (i_this->m1DD0 >= 2)) {
                            fopAcM_cancelCarryNow(heldWeapon);
                            i_this->m1DD0 = 0;
                        }
#endif
                    } else {
                        this_part->mPartVelocity.z = 0.0f;
                        this_part->mPartVelocity.y = 0.0f;
                        this_part->mPartVelocity.x = 0.0f;
                        this_part->mPartRotAdd.z = 0;
                        this_part->mPartRotAdd.y = 0;
                        this_part->mPartRotAdd.x = 0;
                        cLib_addCalcAngleS2(&this_part->mPartRot.x, -0x8000, 1, 0xc00);
                        cLib_addCalcAngleS2(&this_part->mPartRot.y, 0, 1, 0xc00);
                    }
                }
                if ((i_this->m0ED3 == 2) || (i_this->m0ED3 == 0xb)) {
                    this_part->m3E = cM_rndF(65536.0f);
                    this_part->m44 = 0.0f;
                    if (jointIndex == 0xB) {
                        if ((heldWeapon != NULL) && (!fopAcM_checkCarryNow(heldWeapon))) {
                            fopAcM_setCarryNow(heldWeapon, 0);
                            this_part->mPartPos = heldWeapon->current.pos;
                            i_this->m1DD0 = 2;
                            this_part->mWaitTimer = 0;
                            this_part->mPartRotAdd.y = 0x800;
                            this_part->mPartRotAdd.x = 0;
                            this_part->mPartState = 1;
                            if (i_this->m1DC8 != 0) {
                                i_this->mActionState = 0x1d;
                                i_this->m02C4 = 0x32;
                            } else {
                                i_this->mActionState = 0x1e;
                                i_this->m02C4 = 3;
#if VERSION > VERSION_DEMO
                                i_this->m02F8 = 500;
#endif
                                anm_init(i_this, ST_BCK_FUKKI_WAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                            }
                        }
                    } else {
                        this_part->mPartState = 1;
                        this_part->mPartRotAdd.x = cM_rndFX(4000.0f);
                        this_part->mPartRotAdd.y = cM_rndFX(4000.0f);
                        this_part->mWaitTimer = cM_rndF(50.0f) + 30.0f;
                    }
                }
                break;
            case 6:
#if VERSION > VERSION_DEMO
                if ((i_this->m1DDC == 0) && (this_part->mPartVelocity.y <= 0.0f)) {
                    this_part->m3E = cM_rndF(65536.0f);
                    this_part->m44 = 0.0f;
                    this_part->mPartState = 1;
                    this_part->mWaitTimer = 0;
                    break;
                }
#endif
                dVar11 = part_posmove(i_this, this_part);
                if (std::fabsf(DEMO_SELECT(dVar11, actor->home.pos.y) - this_part->mPartPos.y) > DEMO_SELECT(3000.0f, 2000.0f)) {
                    dVar11 = actor->current.pos.y;
                    this_part->mPartPos = actor->current.pos;
#if VERSION > VERSION_DEMO
                    this_part->mPartVelocity.y = 0.0f;
#endif
                }
                if (this_part->mPartPos.y <= dVar11) {
                    this_part->mPartPos.y = dVar11;
                    if (this_part->mPartVelocity.y < -10.0f) {
                        this_part->mWaitTimer = cM_rndF(10.0f) + 2.0f;
                        head_anm_init(i_this, ST_BCK_HEADB_JUMP2, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                        fopAcM_seStart(actor, JA_SE_CM_ST_JUMP_HEAD, 0);
                    }
                    if (this_part->mWaitTimer != 0) {
                        this_part->mPartVelocity.setall(0.0f);
                        if (this_part->mWaitTimer == 1) {
                            local_50 = actor->current.pos - this_part->mPartPos;
                            i_this->m1DDA = cM_atan2s(local_50.x, local_50.z) + (s16)cM_rndFX(20000.0f);
                            cMtx_YrotS(*calc_mtx, i_this->m1DDA);
                            local_50.x = 0.0f;
                            local_50.y = REG13_F(0) + (cM_rndF(35.0f) + 20.0f);
                            local_50.z = REG13_F(1) + 20.0f;
                            MtxPosition(&local_50, &this_part->mPartVelocity);
                            head_anm_init(i_this, ST_BCK_HEADB_JUMP1, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                            fopAcM_monsSeStart(actor, JA_SE_CV_ST_JUMP_HEAD, 0);
                        }
                    }
                    cLib_addCalcAngleS2(&this_part->mPartRot.x, 0, 2, 0xc00);
                    cLib_addCalcAngleS2(&this_part->mPartRot.y, i_this->m1DDA, 2, 0xc00);
#if VERSION == VERSION_DEMO
                    if (i_this->m1DDC == 0) {
                        this_part->m3E = cM_rndF(65536.0f);
                        this_part->m44 = 0.0f;
                        this_part->mPartState = 1;
                        this_part->mWaitTimer = 0;
                    }
#endif
                } else {
                    frame = (int)i_this->mpMorf2->getFrame();
                    if (frame == 5) {
                        emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_STASE00, &this_part->mPartPos);
                        if (emitter != NULL) {
                            emitter->setGlobalRTMatrix(i_this->mpMorf2->getModel()->getAnmMtx(0x1));
                        }
                    }
                }
                break;
            case 7:
#if VERSION == VERSION_DEMO
                dVar11 = part_posmove(i_this, this_part);
                if (!(this_part->mPartPos.y <= dVar11)) {
                    break;
                }
                this_part->mPartPos.y = dVar11;
                if ((i_this->mpMorf->isStop()) || (this_part->mPartVelocity.y < -20.0f)) {
                    head_anm_init(i_this, ST_BCK_HEADB_WAIT, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                }
                this_part->mPartVelocity.setall(0.0f);
                if (i_this->m1DDC == 0) {
                    this_part->m3E = cM_rndF(65536.0f);
                    this_part->m44 = 0.0f;
                    this_part->mPartState = 1;
                    this_part->mWaitTimer = 0;
                    break;
                }
                if (this_part->mWaitTimer == 0) {
                    this_part->mPartState = 6;
                }
#else
                if ((i_this->m1DDC == 0) && (this_part->mPartVelocity.y <= 0.0f)) {
                    this_part->m3E = cM_rndF(65536.0f);
                    this_part->m44 = 0.0f;
                    this_part->mPartState = 1;
                    this_part->mWaitTimer = 0;
                } else {
                    dVar11 = part_posmove(i_this, this_part);
                    if (std::fabsf(actor->home.pos.y - this_part->mPartPos.y) > 2000.0f) {
                        dVar11 = actor->current.pos.y;
                        this_part->mPartPos = actor->current.pos;
                        this_part->mPartVelocity.y = 0.0f;
                    }
                    if (this_part->mPartPos.y <= dVar11) {
                        this_part->mPartPos.y = dVar11;
                        if ((i_this->mpMorf->isStop()) || (this_part->mPartVelocity.y < -20.0f)) {
                            head_anm_init(i_this, ST_BCK_HEADB_WAIT, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                        }
                        this_part->mPartVelocity.setall(0.0f);
                    }
                    if (this_part->mWaitTimer == 0) {
                        this_part->mPartState = 6;
                    }
                }
#endif
                break;
            case 8:
                i_this->m02F6 = 10;
                dVar11 = DEMO_SELECT(part_posmove(i_this, this_part), part_posmove(i_this, this_part) + 20.0f);
                if (std::fabsf(DEMO_SELECT(dVar11, actor->home.pos.y) - this_part->mPartPos.y) > 3000.0f) {
                    dVar11 = this_part->mPartPos.y;
                }
                if (this_part->mPartPos.y <= dVar11) {
                    this_part->mPartPos.y = dVar11;
#if VERSION == VERSION_DEMO
                    i_this->mCountdownToDeath = 1;
#endif
                }
#if VERSION > VERSION_DEMO
                else {
                    break;
                }
#else
                if (!(this_part->mPartPos.y <= dVar11)) {
                    break;
                }
#endif
                for (s32 i = 0; i < 26; i++) {
                    if ((i != 0xb) && (i_this->mParts[i].mpPartModel != NULL)) {
                        if (i == 0xf) {
                            fopAcM_createDisappear(actor, &i_this->mParts[i].mPartPos, 5, daDisItem_IBALL_e);
                        } else {
                            dComIfGp_particle_set(dPa_name::ID_AK_SN_STPARTSDEAD00, &i_this->mParts[i].mPartPos);
                        }
                    }
                }
#if VERSION == VERSION_DEMO
                fopAcM_delete(actor);
#else
                i_this->mCountdownToDeath = 5;
#endif
                if (i_this->mDeathSwitch != 0) {
                    dComIfGs_onSwitch(i_this->mDeathSwitch, fopAcM_GetRoomNo(actor));
                }
                fopAcM_onActor(actor);
                pfVar4 = fopAcM_SearchByID(i_this->mHeldWeaponEntityId);
                if (pfVar4 == NULL) {
                    return;
                }
                fopAcM_cancelCarryNow(pfVar4);
                return;
                break;
            case 10:
                if (i_this->m0ED3 == 0xb) {
                    upperBody = (st_class*)fopAcM_SearchByID(i_this->mUpperBodyEntityId);
                    if (upperBody != NULL) {
                        this_part->mPartState = 1;
                        this_part->mPartPos = upperBody->mParts[jointIndex].mPartPos;
                        if (jointIndex != 0xF) {
                            this_part->mPartRotAdd.x = cM_rndFX(4000.0f);
                            this_part->mPartRotAdd.y = cM_rndFX(4000.0f);
                        } else {
                            csXyz local_88(0, 0, 0);
                            this_part->mPartRotAdd = local_88;
                            this_part->mPartRot = this_part->mPartRotAdd;
                        }
                        this_part->m3E = cM_rndF(65536.0f);
                        this_part->mWaitTimer = 0;
                        this_part->m44 = 0.5f;
                        this_part->m05 = 1;
                    }
                }
            case 11:
                break;
        }
    }

    switch (this_part->m05) {
        case 0:
#if VERSION == VERSION_DEMO
            this_part->mpPartModel->setBaseTRMtx(i_this->mpMorf->getModel()->getAnmMtx(jointIndex));
#else
            MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(jointIndex), *calc_mtx);
#endif
#if VERSION > VERSION_DEMO
            if (i_this->m1DE4 != 0) {
                fVar12 = (int)i_this->m1DE4 * (REG8_F(7) + 2.0f);
                f32 sin = cM_ssin((i_this->m02E8 * 0x3800) + (jointIndex * 0x3000));
                f32 cos2 = cM_scos((i_this->m02E8 * 0x3a00) + (jointIndex * 0x3100));
                f32 cos1 = cM_scos((i_this->m02E8 * 0x3c00) + (jointIndex * 0x2800));
                MtxTrans(fVar12 * sin, fVar12 * cos1, fVar12 * cos2, true);
            }
            this_part->mpPartModel->setBaseTRMtx(*calc_mtx);
#endif
            if (((jointIndex == 0xB) && (heldWeapon != NULL)) && (i_this->m1DD0 != 0)) {
                if (i_this->m1DD0 == 1) {
                    fopAcM_setCarryNow(heldWeapon, 0);
                    i_this->m1DD0 = 10;
                } else if ((i_this->m1DD0 >= 2) && (fopAcM_checkCarryNow(heldWeapon))) {
                    cMtx_YrotM(*calc_mtx, REG8_S(1) + 16000);
                    cMtx_XrotM(*calc_mtx, REG8_S(2));
                    cMtx_ZrotM(*calc_mtx, REG8_S(3));
                    MtxTrans(REG8_F(9), REG8_F(10), REG8_F(11) + 65.0f, true);
                    if (i_this->m02B9 != 0) {
                        MtxTrans(20000.0f, 20000.0f, 20000.0f, false);
                    }
                    var_r26->setMatrix(*calc_mtx);
                }
            }
            if (jointIndex == 0xF) {
                this_part->mPartRot = actor->shape_angle + i_this->m02FC;
            }
            break;
        case 1:
            MtxTrans(this_part->mPartPos.x, this_part->mPartPos.y, this_part->mPartPos.z, false);
            cMtx_YrotM(*calc_mtx, this_part->mPartRot.y);
            cMtx_XrotM(*calc_mtx, this_part->mPartRot.x);
            MtxScale(i_this->mEnemyIce.mScaleXZ, i_this->mEnemyIce.mScaleY, i_this->mEnemyIce.mScaleXZ, true);
            if ((jointIndex == 0xF) && (i_this->m1DD8 != 0)) {
#if VERSION > VERSION_DEMO
                if (i_this->m1E82 != 0) {
                    i_this->m1E82--;
                    fVar12 = (int)i_this->m1E82 * (REG8_F(5) + 1.0f);
                    f32 sin = cM_ssin(i_this->m02E8 * 0x3800);
                    f32 cos = cM_scos(i_this->m02E8 * 0x3c00);
                    MtxTrans(fVar12 * sin, 0.0f, fVar12 * cos, true);
                }
#endif
                i_this->mpMorf2->getModel()->setBaseTRMtx(*calc_mtx);
                i_this->m1DD8 = 2;
                if (i_this->mEnemyIce.mLightShrinkTimer != 0) {
                    i_this->mEnemyIce.mYOffset = REG8_F(3) + 10.0f;
                    actor->current.pos = i_this->mParts[jointIndex].mPartPos;
                }
            } else {
                this_part->mpPartModel->setBaseTRMtx(*calc_mtx);
            }
            if (((var_r26 != NULL) && (jointIndex == 0xB)) && (i_this->m1DD0 >= 2)) {
                var_r26->setMatrix(*calc_mtx);
            }
            break;
    }
    if (jointIndex == 0xF) {
#if VERSION == VERSION_DEMO
        actor->eyePos = this_part->mPartPos;
        actor->attention_info.position = this_part->mPartPos;
        actor->attention_info.position.y += 30.0f;
#else
        if (i_this->m1E86 == 0) {
            actor->eyePos = this_part->mPartPos;
            actor->attention_info.position = this_part->mPartPos;
            actor->attention_info.position.y += 30.0f;
        }
#endif
        if (i_this->m1DD8 == 2) {
            MTXCopy(i_this->mpMorf2->getModel()->getAnmMtx(0x2), *calc_mtx);
            local_50.x = REG0_F(4);
            local_50.y = REG0_F(5);
            local_50.z = REG0_F(6);
        } else {
            MTXCopy(this_part->mpPartModel->getBaseTRMtx(), *calc_mtx);
            local_50.x = REG0_F(4) - 5.0f;
            local_50.y = REG0_F(5) - 25.0f;
            local_50.z = REG0_F(6);
        }
        for (s32 i = 0; i < 3; i++) {
            MtxPosition(&local_50, &i_this->mKe[i].m000[0]);
            i_this->mKe[i].m0F0 = this_part->mPartRot;
            i_this->mKe[i].m0F0.y += (s16)((i + -1) * 0x800);
            if (i == 1) {
                i_this->mKe[i].m0F0.x += 0x500;
            }
        }
    }
}

static s32 cc_j_no[] = {0xF, 0x2, 0x1, 0x4, 0x9, 0x15, 0x18};

/* 00007D38-00008144       .text cc_set__FP8st_class */
static void cc_set(st_class* i_this) {
    f32 fVar1;
    s8 bVar2;
    cXyz local_34;
    cXyz local_40;
    cXyz local_4c;
    cXyz local_58;

    local_34.x = 0.0f;
    local_34.y = 0.0f;
    local_34.z = 0.0f;
    local_4c.x = -50000.0f;
    local_4c.y = -50000.0f;
    local_4c.z = 0.0f;
    local_58.x = 50000.0f;
    local_58.y = -50000.0f;
    local_58.z = 0.0f;
    for (s32 i = 0; i < 7; i++) {
        if (i_this->m0ED0 == 2) {
            bVar2 = false;
        } else {
            bVar2 = false;
            if ((i_this->mActionState == 0x21) || (i_this->m02C4 == 0x23)) {
                if ((i_this->m0ED0 == 0) && (i >= 5)) {
                    bVar2 = true;
                }
            } else if (i_this->mActionState == 0x20) {
                if (((i_this->m0ED0 == 0) || (i == 0)) && (i < 5)) {
                    bVar2 = true;
                }
            } else if ((i_this->m0ED0 == 0) || (i == 0)) {
                bVar2 = true;
            }
        }
        if (bVar2) {
            if ((i == 0) && (i_this->m1DD8 != 0)) {
                MTXCopy(i_this->mpMorf2->getModel()->getBaseTRMtx(), *calc_mtx);
            } else {
                MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(cc_j_no[i]), *calc_mtx);
            }
            MtxPosition(&local_34, &local_40);
            i_this->m054C[i].SetC(local_40);
            if (i == 0) {
                i_this->m054C[i].SetR(45.0f);
            } else {
                i_this->m054C[i].SetR(25.0f);
            }
            i_this->m054C[i].OnTgSetBit();
        } else {
            i_this->m054C[i].SetR(-500.0f);
            i_this->m054C[i].SetC(local_4c);
        }
        dComIfG_Ccsp()->Set(&i_this->m054C[i]);
    }
    if ((i_this->m0ED1 != 0) && (i_this->m0ED0 == 0)) {
        if (i_this->m1DC8 != 0) {
            local_40.x = i_this->mNun.m00[2].x;
            local_40.y = i_this->mNun.m00[2].y;
            local_40.z = i_this->mNun.m00[2].z;
            i_this->m0D80.SetR(30.0f);
        } else if (i_this->m0ED1 == 3) {
            MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0x19), *calc_mtx);
            local_34.x = 0.0f;
            local_34.y = 0.0f;
            local_34.z = 0.0f;
            MtxPosition(&local_34, &local_40);
            i_this->m0D80.SetR(30.0f);
            i_this->m0D80.SetAtSpl(dCcG_At_Spl_UNK0);
        } else {
            i_this->m0D80.SetAtSpl(dCcG_At_Spl_UNK6);
            MTXCopy(i_this->mpMorf->getModel()->getAnmMtx(0xb), *calc_mtx);
            if (i_this->m0ED1 == 2) {
                if (std::fabsf(i_this->m0308) > 0.5f) {
                    i_this->m0D80.SetAtSpl(dCcG_At_Spl_UNK7);
                }
                fVar1 = std::fabsf(i_this->m0308) * 1.5f;
            } else {
                fVar1 = 1.0f;
            }
            if ((i_this->m02E8 & 1) != 0) {
                local_34.x = REG0_F(10) + 80.0f;
                i_this->m0D80.SetR(fVar1 * 70.0f);
            } else {
                local_34.x = REG0_F(10) + 30.0f;
                i_this->m0D80.SetR(fVar1 * 50.0f);
            }
            local_34.y = 0.0f;
            local_34.z = 0.0f;
            MtxPosition(&local_34, &local_40);
        }
        if (i_this->m1E87 == 0) {
            i_this->m0D80.StartCAt(local_40);
            i_this->m1E87++;
        } else {
            i_this->m0D80.MoveCAt(local_40);
        }
        i_this->m0D80.OnAtSetBit();
    } else {
        i_this->m1E87 = 0;
        i_this->m0D80.SetC(local_58);
    }
    dComIfG_Ccsp()->Set(&i_this->m0D80);
    i_this->m0ED0 = 0;
    i_this->m0ED1 = 0;
}

/* 00008144-000082F8       .text eff_move__FP8st_class */
static void eff_move(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;

    if (i_this->m1F60 != 0) {
        i_this->m1F60--;
    }
    if (i_this->m1F68 == 1) {
        i_this->m1F64 = 1.0f;
        if (i_this->m1F60 == 0) {
            i_this->m1F60 = 0xF;
            for (s32 i = 0; i < 20; i++) {
                if (i_this->m1EE8[i] == NULL) {
                    i_this->m1EE8[i] = dComIfGp_particle_set(dPa_name::ID_AK_SN_STRECONSTRUCT00, &actor->current.pos);
                    if (i_this->m1EE8[i] != NULL) {
                        i_this->m1EE8[i]->becomeImmortalEmitter();
                        i_this->m1F38[i] = 200;
                    }
                    break;
                }
            }
        }
    }
    if (i_this->m1F68 == 2) {
        cLib_addCalc0(&i_this->m1F64, 1.0f, 0.1f);
    }
    for (s32 i = 0; i < 20; i++) {
        if (i_this->m1EE8[i] != NULL) {
            i_this->m1EE8[i]->setGlobalParticleWidthScale(i_this->m1F64);
            if ((i_this->m1F38[i] != 0) && (i_this->m1F38[i]--, i_this->m1F38[i] == 0)) {
                i_this->m1EE8[i]->becomeInvalidEmitter();
                i_this->m1EE8[i] = NULL;
            }
        }
    }
}

/* 000082F8-000087C8       .text daSt_Execute__FP8st_class */
static BOOL daSt_Execute(st_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    st_class* upperBody;
    fopAc_ac_c* heldWeapon;
    J3DModel* model;

#if VERSION > VERSION_DEMO
    if (i_this->mCountdownToDeath != 0) {
        i_this->mCountdownToDeath--;
        if (i_this->mCountdownToDeath == 0) {
            fopAcM_delete(actor);
        }
        return TRUE;
    }
    if ((i_this->m02FA != 0) || (actor->home.pos.y - actor->current.pos.y > 4000.0f)) {
        fopAcM_delete(actor);
        return TRUE;
    }
    if (i_this->m2364 != 0) {
        i_this->m2364--;
        if (i_this->m2364 == 0) {
            fopAcM_OffStatus(actor, fopAcStts_UNK4000_e);
        }
    }
#endif
    if (enemy_ice(&i_this->mEnemyIce)) {
        model = i_this->mpMorf->getModel();
        MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
        cMtx_YrotM(*calc_mtx, actor->shape_angle.y + i_this->m0304);
        MtxScale(i_this->mEnemyIce.mScaleXZ, i_this->mEnemyIce.mScaleY, i_this->mEnemyIce.mScaleXZ, true);
        model->setBaseTRMtx(*calc_mtx);
        i_this->mpMorf->calc();
        i_this->mpMorf2->calc();
        for (s32 i = 0; i < 26; i++) {
            if ((i_this->mParts[i].mpPartModel != NULL) && (i_this->m1DC8 == 0 || (i != 3 && (i != 4)))) {
                part_move(i_this, i);
            }
        }
        if ((i_this->mActionState != 0x21) && (i_this->m02C4 != 0x23)) {
            ke_move(i_this);
        }
        if (i_this->m1DC8 != 0) {
            nun_move(i_this);
        }
        return TRUE;
    }
    another_hit = 0;
#if VERSION == VERSION_DEMO
    if ((i_this->m02FA != 0) || (actor->home.pos.y - actor->current.pos.y > 4000.0f)) {
        fopAcM_delete(actor);
        return TRUE;
    }
#endif
    if (i_this->mUpperBodyEntityId != 0xFFF) {
        upperBody = (st_class*)fopAcM_SearchByID(i_this->mUpperBodyEntityId);
        if ((upperBody != NULL) && (upperBody->mCountdownToDeath != 0)) {
            fopAcM_delete(actor);
            for (s32 i = 0; i < 26; i++) {
                if (i_this->mParts[i].mPartState < 10) {
                    dComIfGp_particle_set(dPa_name::ID_AK_SN_STPARTSDEAD00, &i_this->mParts[i].mPartPos);
                }
            }
            heldWeapon = fopAcM_SearchByID(i_this->mHeldWeaponEntityId);
            if (heldWeapon != NULL) {
                fopAcM_cancelCarryNow(heldWeapon);
            }
            return TRUE;
        }
    }
    i_this->m02E8++;
    for (s32 i = 0; i < 5; i++) {
        if (i_this->mTimers[i] != 0) {
            i_this->mTimers[i]--;
        }
    }
    if (i_this->m02F6 != 0) {
        i_this->m02F6--;
    }
    if (i_this->m1DDC != 0) {
        i_this->m1DDC--;
    }
#if VERSION == VERSION_DEMO
    damage_check(i_this);
    St_move(i_this);
#else
    St_move(i_this);
    damage_check(i_this);
#endif
    cLib_addCalcAngleS2(&actor->shape_angle.y, actor->current.angle.y + i_this->m0302, 2, 0x1000);
    i_this->m0302 = 0;
    i_this->mpMorf->play(&actor->eyePos, 0, 0);
    i_this->mpMorf2->play(&actor->eyePos, 0, 0);
    model = i_this->mpMorf->getModel();
    model->setBaseScale(actor->scale);
    MtxTrans(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z, false);
    cMtx_YrotM(*calc_mtx, actor->shape_angle.y + i_this->m0304);
    model->setBaseTRMtx(*calc_mtx);
    i_this->mpMorf->calc();
    i_this->mpMorf2->calc();
    cc_set(i_this);
    for (s32 i = 0; i < 26; i++) {
        if ((i_this->mParts[i].mpPartModel != NULL) && (i_this->m1DC8 == 0 || (i != 3 && (i != 4)))) {
            part_move(i_this, i);
        }
    }
    if (i_this->m0ED3 != 2) {
        i_this->m0ED3 = 0;
    }
    cLib_addCalcAngleS2(&i_this->m0304, 0, 2, 0x40);
    if ((i_this->mActionState != 0x21) && (i_this->m02C4 != 0x23)) {
        ke_move(i_this);
    }
    if (i_this->m1DC8 != 0) {
        nun_move(i_this);
    }
    eff_move(i_this);
    spin_smoke_move(i_this);
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    return TRUE;
}

/* 000087C8-000087D0       .text daSt_IsDelete__FP8st_class */
static BOOL daSt_IsDelete(st_class*) {
    return TRUE;
}

/* 000087D0-000088CC       .text daSt_Delete__FP8st_class */
static BOOL daSt_Delete(st_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "St");
    if (i_this->m02FB != 0) {
        hio_set = false;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    for (s32 i = 0; i < 3; i++) {
        i_this->m1E88[i].remove();
    }
    i_this->m1F88.remove();
    for (s32 i = 0; i < 20; i++) {
        if (i_this->m1EE8[i] != NULL) {
            i_this->m1EE8[i]->becomeInvalidEmitter();
            i_this->m1EE8[i] = NULL;
        }
    }
    return TRUE;
}

/* 000088CC-00008B44       .text createHeap__FP10fopAc_ac_c */
static BOOL createHeap(fopAc_ac_c* a_this) {
    static u16 st_part_bdl[] = {
        0,
        ST_BDL_ST_HARA,
        ST_BDL_ST_MUNE,
        ST_BDL_ST_KATAL,
        ST_BDL_ST_UDEL,
        ST_BDL_ST_HANDL,
        ST_BDL_ST_YUBI1L,
        ST_BDL_ST_YUBI2L,
        ST_BDL_ST_KATAR,
        ST_BDL_ST_UDER,
        ST_BDL_ST_HANDR,
        ST_BDL_ST_BUKI,
        ST_BDL_ST_YUBI1R,
        ST_BDL_ST_YUBI2R,
        ST_BDL_ST_KUBI,
        ST_BDL_ST_HEAD,
        ST_BDL_ST_AGO,
        ST_BDL_ST_HAT,
        0,
        ST_BDL_ST_KOTUBAN,
        ST_BDL_ST_MOMOL,
        ST_BDL_ST_SUNEL,
        ST_BDL_ST_ASIL,
        ST_BDL_ST_MOMOR,
        ST_BDL_ST_SUNER,
        ST_BDL_ST_ASIR
    };
    st_class* i_this = (st_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("St", ST_BDL_ST),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("St", ST_BCK_WAIT),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11000022
    );
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
        return FALSE;
    }
#if VERSION == VERSION_DEMO
    J3DModel* model = i_this->mpMorf->getModel();
    model->setUserArea((u32)i_this);
    for (u16 i = 0; i < model->getModelData()->getJointNum(); i++) {
        if ((i < 0x1A) && (i != 0xB)) {
            model->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
        }
    }
#endif
    i_this->mpMorf2 = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("St", ST_BDL_HEADB),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("St", ST_BCK_HEADB_WAIT),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11000022
    );
    if ((i_this->mpMorf2 == NULL) || (i_this->mpMorf2->getModel() == NULL)) {
        return FALSE;
    }
    for (s32 i = 0; i < 26; i++) {
        if (st_part_bdl[i] != 0) {
            J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("St", st_part_bdl[i]);
            i_this->mParts[i].mpPartModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
            if (i_this->mParts[i].mpPartModel == NULL) {
                return FALSE;
            }
        }
    }
    if (i_this->mLineMat.init(3, 10, 0)) {
        return TRUE;
    }
    return FALSE;
}

/* 00008B44-00008F60       .text daSt_Create__FP10fopAc_ac_c */
static cPhs_State daSt_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph head_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcG_TgHitMark_Unk1_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 40.0f,
        }},
    };
    static dCcD_SrcSph body_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_NORMAL_ARROW & ~AT_TYPE_UNK20000 & ~AT_TYPE_FIRE_ARROW & ~AT_TYPE_ICE_ARROW &
                ~AT_TYPE_LIGHT_ARROW & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* Radius */ 40.0f,
        }},
    };
    static dCcD_SrcSph wepon_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_STALFOS_MACE,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
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
            /* Radius */ 60.0f,
        }},
    };

    fopAcM_ct(a_this, st_class);
    st_class* i_this = (st_class*)a_this;
    fopEn_enemy_c* e_this = (fopEn_enemy_c*)a_this;
    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "St");
    if (res == cPhs_COMPLEATE_e) {
        for (s32 i = 0; i < 2; i++) {
            i_this->m1E88[i].setFollowOff();
        }
        a_this->gbaName = 0x4;
        i_this->mBehaviorType = fopAcM_GetParam(a_this) & 0xF;
        i_this->mAmbushSightRange = (fopAcM_GetParam(a_this) >> 8);
        i_this->mUnusedParam = (fopAcM_GetParam(a_this) >> 0x10);
        i_this->mAmbushSwitch = (fopAcM_GetParam(a_this) >> 0x18);
        i_this->mDeathSwitch = a_this->current.angle.z;
        a_this->current.angle.z = 0;
#if VERSION > VERSION_DEMO
        if ((i_this->mDeathSwitch != 0) && (i_this->mDeathSwitch <= 0x7F)) {
            fopAcM_OnStatus(a_this, fopAcStts_BOSS_e);
        }
#endif
        if (i_this->mDeathSwitch == 0xFF) {
            i_this->mDeathSwitch = 0;
        }
        if ((i_this->mDeathSwitch != 0) && (dComIfGs_isSwitch(i_this->mDeathSwitch, fopAcM_GetRoomNo(a_this)))) {
            return cPhs_ERROR_e;
        }
        a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Stal", 0);
        if (!fopAcM_entrySolidHeap(a_this, createHeap, 0)) {
            return cPhs_ERROR_e;
        }
        if (hio_set == false) {
            l_HIO.mNo = mDoHIO_createChild("スタ", &l_HIO); // Stal
            i_this->m02FB = 1;
            hio_set = true;
        }
        if ((i_this->mpMorf == NULL) || (i_this->mpMorf->getModel() == NULL)) {
            return cPhs_ERROR_e;
        }
        if (i_this->mBehaviorType == BEHAVIOR_UNDERGROUND) {
            i_this->mActionState = 0xF;
            if (i_this->mAmbushSwitch != 0xFF) {
                i_this->m02B9 = i_this->mAmbushSwitch + 1;
            } else {
                i_this->m02B9 = 0xFF;
            }
#if VERSION > VERSION_DEMO
            i_this->m2364 = 5;
            fopAcM_OnStatus(a_this, fopAcStts_UNK4000_e);
#endif
        } else if ((i_this->mBehaviorType == BEHAVIOR_IN_HORIZONTAL_COFFIN) || (i_this->mBehaviorType == BEHAVIOR_IN_VERTICAL_COFFIN)) {
            i_this->mActionState = 0x10;
            if (i_this->mAmbushSwitch != 0xFF) {
                i_this->m02B9 = i_this->mAmbushSwitch + 1;
            } else {
                i_this->m02B9 = 0xFF;
            }
        }
        i_this->mpMorf->getModel()->setUserArea((u32)a_this);
        e_this->initBt(162.5f, 125.0f);
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        fopAcM_OnStatus(a_this, fopAcStts_SHOWMAP_e);
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mAcchCir.SetWall(DEMO_SELECT(50.0f, 60.0f), 100.0f);
        i_this->mStts.Init(0x32, 2, a_this);
        for (s32 i = 0; i < 7; i++) {
            if (i == 0) {
                i_this->m054C[i].Set(head_sph_src);
            } else {
                i_this->m054C[i].Set(body_sph_src);
            }
            i_this->m054C[i].SetStts(&i_this->mStts);
        }
        i_this->m0D80.Set(wepon_sph_src);
        i_this->m0D80.SetStts(&i_this->mStts);
        if (i_this->mBehaviorType != BEHAVIOR_UPPER_BODY_ONLY) {
            i_this->mHeldWeaponEntityId = fopAcM_create(PROC_BOKO, daBoko_c::Type_STALFOS_MACE_e, &a_this->current.pos, fopAcM_GetRoomNo(a_this));
            i_this->m1DD0 = 1;
            a_this->health = 16;
            a_this->max_health = 16;
            i_this->m1E84 = 0x10;
        } else {
            a_this->health = 16;
            a_this->max_health = 16;
            i_this->m1E84 = 5;
            i_this->mActionState = 0x20;
            i_this->m0ED3 = 0x14;
        }
        i_this->m0ED2 = 0x19;
        i_this->mUpperBodyEntityId = 0xFFF;
        i_this->mEnemyIce.mpActor = a_this;
        i_this->mEnemyIce.mDeathSwitch = i_this->mDeathSwitch;
        a_this->stealItemLeft = 3;
#if VERSION > VERSION_DEMO
        i_this->m02F6 = 0xF;
        daSt_Execute(i_this);
#endif
    }
    return res;
}

static actor_method_class l_daSt_Method = {
    (process_method_func)daSt_Create,
    (process_method_func)daSt_Delete,
    (process_method_func)daSt_Execute,
    (process_method_func)daSt_IsDelete,
    (process_method_func)daSt_Draw,
};

actor_process_profile_definition g_profile_ST = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_ST,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(st_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_ST,
    /* Actor SubMtd */ &l_daSt_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
