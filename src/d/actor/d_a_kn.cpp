/**
 * d_a_kn.cpp
 * NPC - Crab
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kn.h"
#include "d/res/res_kn.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"

enum Mode {
#if VERSION == VERSION_DEMO
    Mode_0_e = 0,
    Mode_1_e = 1,
    Mode_10_e = 10,
#else
    Mode_10_e = 0,
#endif
    Mode_11_e,
    Mode_12_e,
    Mode_13_e,
    Mode_14_e,
    Mode_15_e,
    Mode_16_e,
    Mode_17_e,
    Mode_18_e,
    Mode_19_e,
    Mode_20_e,
};

static const GXColor unused_color = {0xFF, 0, 0, 0x40};
#if VERSION == VERSION_DEMO
static const GXColor unused_colors[] = {
    {0xFF, 0, 0, 0xFF},
    {0, 0xFF, 0, 0xFF},
    {0, 0, 0xFF, 0xFF},
};
#endif

/* 00000078-00000120       .text daKN_Draw__FP8kn_class */
static BOOL daKN_Draw(kn_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;

    if (i_this->m2CC < 0.0f) {
        return TRUE;
    }

#if VERSION == VERSION_DEMO
    if (i_this->m2B4 == 1) {
        cMtx_YrotS(*calc_mtx, a_this->current.angle.y);
        cXyz sp14;
        cXyz sp08;
        sp14.x = 0.0f;
        sp14.y = 0.0f;
        sp14.z = 100.0f;
        MtxPosition(&sp14, &sp08);
        sp08 += a_this->current.pos;
        sp14 = a_this->current.pos;
        sp14.y += 50.0f;
        sp08.y += 50.0f;
        return TRUE;
    }
#endif

    J3DModel* pJVar1 = i_this->mpMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &a_this->current.pos, &a_this->tevStr);
    g_env_light.setLightTevColorType(pJVar1, &a_this->tevStr);
    i_this->mpMorf->updateDL();
    dSnap_RegistFig(0x56, a_this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00000120-00000248       .text anm_init__FP8kn_classifUcfi */
void anm_init(kn_class* i_this, int anmResIdx, float morf, unsigned char loopMode, float speed, int soundResIdx) {
    if (soundResIdx >= 0) {
        i_this->mpMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("KN", anmResIdx), loopMode, morf, speed, 0.0f, -1.0f, (void*)dComIfG_getObjectRes("KN", soundResIdx)
        );
    } else {
        i_this->mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("KN", anmResIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000248-00000368       .text smoke_set__FP8kn_class */
void smoke_set(kn_class* i_this) {
    f32 fVar1 = REG8_F(10) + 1.0f;
    JGeometry::TVec3<f32> s;
    s.set(fVar1, fVar1, fVar1);

    i_this->m314.remove();
    i_this->m334 = dComIfGp_particle_setToon(0x2027, &i_this->m300, &i_this->actor.shape_angle, NULL, 0xb9, &i_this->m314, fopAcM_GetRoomNo(&i_this->actor));
    if (i_this->m334 != NULL) {
        i_this->m334->setMaxFrame(0x19);
        i_this->m334->setAwayFromCenterSpeed(0.0f);
        i_this->m334->setAwayFromAxisSpeed(5.0f);
        i_this->m334->setRate(3.0f);
        i_this->m334->setDirectionalSpeed(2.0f);
        i_this->m334->setGlobalScale(s);
        s32 lifeTime = 25;
        i_this->m334->setLifeTime(lifeTime);
    }
}

/* 00000368-00000440       .text shibuki_set__FP8kn_class */
void shibuki_set(kn_class* i_this) {
    f32 fVar1 = REG8_F(11) + 0.55f;
    JGeometry::TVec3<f32> s;
    s.set(fVar1, fVar1, fVar1);

    JPABaseEmitter* pJVar2 = dComIfGp_particle_set(dPa_name::ID_COMMON_0023, &i_this->actor.current.pos);
    if (pJVar2 != NULL) {
        pJVar2->setRate(1.5f);
        pJVar2->setSpread(1.0f);
        pJVar2->setDirectionalSpeed(4.0f);
        pJVar2->setMaxFrame(0x19);
        pJVar2->setGlobalScale(s);
    }
}

/* 00000440-00000CE8       .text kn_move__FP8kn_class */
void kn_move(kn_class* i_this) {
    f32 fVar8;
    f32 fVar1;
    f32 f26 = 3.0f;
    f32 f29 = 200.0f;
    f32 f28 = 300.0f;
    f32 f27 = 500.0f;

    fVar8 = i_this->m2EC.x - i_this->actor.current.pos.x;
    fVar1 = i_this->m2EC.z - i_this->actor.current.pos.z;
    s16 sVar5;
    s32 idx;
    f32 rand;
    s32 idx2;

    switch (i_this->m2BD) {
#if VERSION == VERSION_DEMO
    case Mode_0_e:
        anm_init(i_this, KN_BCK_WALK, 5.0f, 2, 1.0f, -1);
        i_this->m2CC = -25.0f;
        i_this->actor.current.angle.z = -0x2000;
        i_this->m2BD++;
        break;

    case Mode_1_e:
        cLib_addCalc0(&i_this->m2CC, 0.3f, 1.0f);
        if (i_this->m2CC > -10.0f) {
            cLib_addCalcAngleS2(&i_this->actor.current.angle.z, 0, 2, 0x200);
        }
        i_this->actor.shape_angle.z = i_this->actor.current.angle.z;
        if (abs(i_this->actor.shape_angle.z) < 0x100) {
            i_this->actor.current.angle.z = 0;
            i_this->actor.shape_angle.z = 0;
            i_this->m2BD = Mode_12_e;
        }
        break;
#endif
    case Mode_10_e:
        if (cM_rnd() < 0.5f) {
            anm_init(i_this, KN_BCK_WAIT01, 5.0f, 2, 1.0f, -1);
        } else {
            anm_init(i_this, KN_BCK_WAIT02, 5.0f, 2, 1.0f, -1);
        }
        i_this->m2D2 = 0x800;
        i_this->m2CA = cM_rndF(2.0f) + 1.0f;
        i_this->m2BD++;

    case Mode_11_e:
        cLib_addCalc0(&i_this->actor.speedF, 1.0f, 2.0f);
        if (i_this->mpMorf->checkFrame(43.0f)) {
            i_this->m2CA--;
            if (i_this->m2CA <= 0) {
                i_this->m2BD = Mode_12_e;
            }
        }

        if ((i_this->m2C2[2] == 0) && fopAcM_searchPlayerDistance(&i_this->actor) < f28) {
            i_this->m2BD = Mode_18_e;
        }
        break;

    case Mode_12_e:
        anm_init(i_this, KN_BCK_WALK, 5.0f, 2, 1.0f, -1);
        i_this->m2D0 = i_this->actor.current.angle.y + cM_rndFX(10752.0f);
        i_this->m2E8 = f26;
        if (cM_rnd() < 0.5f) {
            i_this->m2E8 = -f26;
        }

        if (i_this->m2C2[2] != 0) {
            i_this->m2D0 = cM_atan2s(fVar8, fVar1);
            i_this->m2E8 = f26;
        }

#if VERSION == VERSION_DEMO
        // Fakematch?
        idx = 40;
        rand = cM_rndF(idx);
        idx2 = 20;
        i_this->m2C2[0] = idx2 + rand;
#else
        idx = 40;
        idx2 = 20;
        i_this->m2C2[0] = cM_rndF(idx) + idx2;
#endif
        i_this->m2E4 = i_this->m2E8;
        i_this->m2D2 = 0x800;
        i_this->m2BE = 0;
        i_this->m2BD++;

    case Mode_13_e:
        if (fopAcM_searchPlayerDistance(&i_this->actor) < f28) {
            i_this->m2BD = Mode_18_e;
        } else if (i_this->m2C2[2] == 0) {
            if (i_this->m2BE != 0) {
                shibuki_set(i_this);
                i_this->m2BF = 0;
                i_this->m2BD = Mode_15_e;
            } else if (std::sqrtf(SQUARE(fVar8) + SQUARE(fVar1)) > f29) {
                i_this->m2C2[1] = 0x14;
                i_this->m2E4 = i_this->m2E8 * -1.0f;
                i_this->m2BD = Mode_14_e;
            } else if (i_this->m2C2[0] == 0) {
                i_this->m2BD = Mode_10_e;
            }
        }
        break;

    case Mode_14_e:
        if (i_this->m2C2[1] == 0) {
            if (std::sqrtf(SQUARE(fVar8) + SQUARE(fVar1)) > f29) {
                i_this->m2D0 = cM_atan2s(fVar8, fVar1);
                i_this->m2E4 = std::fabsf(i_this->m2E8);
                i_this->m2C2[1] = 8;
            } else {
                i_this->m2BD = Mode_10_e;
            }
        }
        break;

    case Mode_15_e:
        i_this->actor.speedF = 0.0f;
        i_this->m2E4 = 0.0;
        i_this->m2C0 = 0;
        i_this->m2C2[0] = 0x14;
        anm_init(i_this, KN_BCK_PATA, 5.0f, 2, 1.0f, -1);
        i_this->m2BD++;

    case Mode_16_e:
        if (i_this->m2C2[0] == 0) {
            f32 fVar9 = -7.0f;
            if (i_this->actor.scale.x > 1.5f) {
                fVar9 = -11.0f;
            }

            if (i_this->m2C0 == 0) {
                if (std::fabsf(i_this->m2CC - fVar9) <= 1.0f) {
                    if (i_this->m2BF != 0) {
                        i_this->m314.remove();
                    }
                    i_this->m2CC = fVar9;
                    i_this->m2C0 = 1;
                    i_this->m2C2[3] = cM_rndF(30.0f) + 30.0f;
                } else {
                    cLib_addCalc2(&i_this->m2CC, fVar9, 0.1f, 1.0f);
                }
            }

            if ((i_this->m2C0 != 0) && (i_this->m2C2[3] == 0) && fopAcM_searchPlayerDistance(&i_this->actor) > f27) {
                if (i_this->m2BF != 0) {
                    i_this->m300 = i_this->actor.current.pos;
                    i_this->m300.y += 20.0f;
                    smoke_set(i_this);
                } else {
                    shibuki_set(i_this);
                }
                anm_init(i_this, KN_BCK_PATA, 5.0f, 2, 1.0f, -1);
                i_this->m2BD = Mode_17_e;
            }
        }
        break;

    case Mode_17_e:
        cLib_addCalc0(&i_this->m2CC, 0.1f, 1.0f);
        if (i_this->m2CC < 0.2f) {
            if (i_this->m2BF != 0) {
                i_this->m314.remove();
            }
            i_this->m2CC = 0.0f;
            i_this->m2C2[2] = 0x28;
            i_this->m2BD = Mode_12_e;
        }
        break;

    case Mode_18_e:
        anm_init(i_this, KN_BCK_WALK, 5.0f, 2, 2.0f, -1);
        i_this->m2E8 = 40.0;
        i_this->m2C2[0] = 0;
        i_this->m2C2[1] = 0;
        i_this->m2C2[2] = 0;
        i_this->m2D2 = 0x100;
        i_this->m2E4 = i_this->m2E8;
        i_this->m2BE = 0;
        i_this->m2E4 = i_this->m2E8;

        sVar5 = fopAcM_searchPlayerAngleY(&i_this->actor) - -0x8000;
        if ((s16)cLib_distanceAngleS(sVar5, i_this->actor.current.angle.y) < 0x4000) {
            i_this->m2D0 = sVar5;
        } else {
            i_this->m2D0 = i_this->actor.current.angle.y;
            if ((s16)cLib_distanceAngleS(sVar5, i_this->actor.current.angle.y) > (s16)(cLib_distanceAngleS(sVar5, i_this->actor.current.angle.y) - -0x8000)) {
                i_this->m2E4 = i_this->m2E8 * -1.0f;
            }
        }
        i_this->m2BD++;

    case Mode_19_e:
        if (i_this->mAcchCir.ChkWallHit() || std::sqrtf(SQUARE(fVar8) + SQUARE(fVar1)) > f29) {
#if VERSION > VERSION_DEMO
            i_this->actor.speedF = 0.0f;
            i_this->m2E4 = 0.0f;
            i_this->actor.speed.x = 0.0f;
            i_this->actor.speed.y = 0.0f;
            i_this->actor.speed.z = 0.0f;
#endif
            i_this->m300 = i_this->actor.current.pos;
            i_this->m2BF = 1;
            smoke_set(i_this);
            i_this->m2BD = Mode_15_e;
        } else if (i_this->m2BE != 0) {
            i_this->m2BF = 0;
            shibuki_set(i_this);
            i_this->m2BD = Mode_15_e;
        }
        break;
    }

    if (i_this->m2BD >= Mode_13_e) {
        if (i_this->m2BD < Mode_18_e) {
            i_this->m2E0 = 1.0f;
            if ((s16)cLib_distanceAngleS(i_this->actor.current.angle.y, i_this->m2D0) > 0x100) {
                i_this->m2E0 = 2.0f;
            }
            cLib_addCalc2(&i_this->m2DC, i_this->m2E0, 0.5f, 1.0f);
            i_this->mpMorf->setPlaySpeed(i_this->m2DC);
        }
        cLib_addCalcAngleS2(&i_this->actor.current.angle.y, i_this->m2D0, 1, i_this->m2D2);
        cLib_addCalc2(&i_this->actor.speedF, i_this->m2E4, 0.3f, 1.0f);
    }

    i_this->actor.shape_angle.y = i_this->actor.current.angle.y + 0x4000;
}

void oya_kn_move(kn_class* i_this) {
    f32 tmp1 = 300.0f;
    f32 tmp2 = 500.0f;

    if (fopAcM_searchPlayerDistance(&i_this->actor) > tmp2 || fopAcM_searchPlayerDistance(&i_this->actor) < tmp1) {
        return;
    }

    if (i_this->m2C2[0] == 0) {
        fopAcM_prm_class* puVar1 = fopAcM_CreateAppend();
        puVar1->base.position = i_this->actor.current.pos;
        puVar1->base.angle = i_this->actor.current.angle;
        if (cM_rnd() < 0.5f) {
            puVar1->base.angle.y -= -0x8000;
        }
        puVar1->base.parameters = 2;
        puVar1->room_no = fopAcM_GetRoomNo(&i_this->actor);
        fopAcM_Create(PROC_KN, NULL, puVar1);
        i_this->m2C2[0] = 10;
        i_this->m2D4--;
        if (i_this->m2D4 <= 0) {
            fopAcM_delete(&i_this->actor);
        }
    }
}

/* 00000CE8-00000D64       .text BG_check__FP8kn_class */
void BG_check(kn_class* i_this) {
    i_this->actor.current.pos.y -= i_this->m2CC;
    i_this->actor.old.pos.y -= i_this->m2CC;

    i_this->mAcch.CrrPos(*dComIfG_Bgsp());

    i_this->actor.current.pos.y += i_this->m2CC;
    i_this->actor.old.pos.y += i_this->m2CC;
}

/* 00000D64-00000F80       .text daKN_Execute__FP8kn_class */
static BOOL daKN_Execute(kn_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;

    for (s32 i = 0; i < ARRAY_SSIZE(i_this->m2C2); i++) {
        if (i_this->m2C2[i] != 0) {
            i_this->m2C2[i]--;
        }
    }

#if VERSION == VERSION_DEMO
    switch (i_this->m2BC) {
    case 0:
        kn_move(i_this);
        break;

    case 1:
        oya_kn_move(i_this);
        break;
    }

    if (i_this->m2B4 == 1) {
        return TRUE;
    }
#else
    kn_move(i_this);
#endif

    cMtx_YrotS(*calc_mtx, a_this->current.angle.y);
    cMtx_XrotM(*calc_mtx, a_this->current.angle.x);

    cXyz sp14;
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = a_this->speedF;
    cXyz sp08;
    MtxPosition(&sp14, &sp08);

    a_this->speed.x = sp08.x;
    a_this->speed.z = sp08.z;

#if VERSION == VERSION_DEMO
    if (a_this->speed.y > -80.0f) {
        a_this->speed.y -= 3.0f;
    }
#else
    a_this->speed.y += a_this->gravity;
    if (a_this->speed.y < -20.0f) {
        a_this->speed.y = -20.0f;
    }
#endif

    fopAcM_posMove(a_this, NULL);
    BG_check(i_this);

    if (i_this->mAcch.ChkGroundHit()) {
        fopAcM_getGroundAngle(a_this, &i_this->m2F8);
        if (
#if VERSION == VERSION_DEMO
            i_this->m2BC == 0 &&
#endif
            ((i_this->m2BD == Mode_13_e) || (i_this->m2BD == Mode_19_e)) &&
            i_this->mAcch.GetGroundH() != -G_CM3D_F_INF && dComIfG_Bgsp()->GetAttributeCode(i_this->mAcch.m_gnd) == dBgS_Attr_WATER_e)
        {
            i_this->m2BE = 1;
        }
    }

    i_this->mpMorf->play(NULL, 0, 0);
    J3DModel* pJVar3 = i_this->mpMorf->getModel();
    mDoMtx_stack_c::transS(a_this->current.pos.x, a_this->current.pos.y, a_this->current.pos.z);
    mDoMtx_stack_c::XrotM(i_this->m2F8.x);
    mDoMtx_stack_c::ZrotM(i_this->m2F8.z);
    mDoMtx_stack_c::YrotM(a_this->shape_angle.y);
    mDoMtx_stack_c::XrotM(a_this->shape_angle.x);
    mDoMtx_stack_c::ZrotM(a_this->shape_angle.z);
    pJVar3->setBaseScale(a_this->scale);
    mDoMtx_stack_c::transM(0.0f, i_this->m2CC, 0.0f);
    pJVar3->setBaseTRMtx(mDoMtx_stack_c::get());
    return TRUE;
}

/* 00000F80-00000F88       .text daKN_IsDelete__FP8kn_class */
static BOOL daKN_IsDelete(kn_class*) {
    return TRUE;
}

/* 00000F88-00000FD8       .text daKN_Delete__FP8kn_class */
static BOOL daKN_Delete(kn_class* i_this) {
    i_this->m314.remove();
    dComIfG_resDeleteDemo(&i_this->mPhase, "KN");
    return TRUE;
}

/* 00000FD8-000010E0       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    kn_class* i_this = (kn_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("KN", KN_BDL_KN),
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("KN", KN_BCK_PATA),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0x80000,
        0x11000002
    );
    if ((i_this->mpMorf == NULL) || (i_this->mpMorf->mpModel == NULL)) {
        return FALSE;
    }
    return TRUE;
}

/* 000010E0-000012B0       .text daKN_Create__FP10fopAc_ac_c */
static cPhs_State daKN_Create(fopAc_ac_c* a_this) {
    kn_class* i_this = (kn_class*)a_this;

#if VERSION == VERSION_DEMO
    cPhs_State PVar1 = dComIfG_resLoad(&i_this->mPhase, "KN");
    if (PVar1 == cPhs_COMPLEATE_e) {
        fopAcM_SetupActor(&i_this->actor, kn_class);
#else
    fopAcM_SetupActor(a_this, kn_class);
    cPhs_State PVar1 = dComIfG_resLoad(&i_this->mPhase, "KN");
    if (PVar1 == cPhs_COMPLEATE_e) {
#endif
        i_this->m2B4 = fopAcM_GetParam(a_this);
        i_this->m2B5 = fopAcM_GetParam(a_this) >> 8;
        i_this->m2EC = a_this->current.pos;

#if VERSION == VERSION_DEMO
        if (i_this->m2B4 == 1) {
            i_this->m2D4 = i_this->m2B5;
            if ((i_this->m2B5 == 0xff) || (i_this->m2B5 == 0)) {
                i_this->m2D4 = 100;
            }
            i_this->m2BC = 1;
            i_this->m2BD = Mode_20_e;
            return PVar1;
        }
#endif

        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x2860)) {
            return cPhs_ERROR_e;
        }

        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        fopAcM_setCullSizeBox(a_this, -30.0f, -0.0f, -30.0f, 30.0f, 60.0f, 30.0f);

        a_this->gravity = -5.0f;
        a_this->attention_info.flags = 0;
        i_this->mAcchCir.SetWall(10.0f, 30.0f);
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        a_this->scale.x = 1.5f;
        a_this->scale.y = 1.5f;
        a_this->scale.z = 1.5f;

#if VERSION == VERSION_DEMO
        if (i_this->m2B4 == 2) {
            a_this->current.angle.z = -0x2000;
            i_this->m2CC = -25.0f;
            i_this->m2BC = 0;
            i_this->m2BD = Mode_0_e;
        } else
#endif
        {

            if (cM_rnd() < 0.5f) {
                a_this->scale.x = 2.5f;
                a_this->scale.y = 2.5f;
                a_this->scale.z = 2.5f;
            }
#if VERSION == VERSION_DEMO
            i_this->m2BC = 0;
#endif
            i_this->m2BD = Mode_10_e;
#if VERSION > VERSION_DEMO
            daKN_Execute(i_this);
#endif
        }
    }
    return PVar1;
}

static actor_method_class l_daKN_Method = {
    (process_method_func)daKN_Create,
    (process_method_func)daKN_Delete,
    (process_method_func)daKN_Execute,
    (process_method_func)daKN_IsDelete,
    (process_method_func)daKN_Draw,
};

actor_process_profile_definition g_profile_KN = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KN,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kn_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KN,
    /* Actor SubMtd */ &l_daKN_Method,
    /* Status       */ DEMO_SELECT(fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_NOCULLEXEC_e, fopAcStts_CULL_e | fopAcStts_UNK40000_e),
    /* Group        */ fopAc_ENV_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
