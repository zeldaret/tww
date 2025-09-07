/**
 * d_a_mflft.cpp
 * Object - Dragon Roost Cavern - Flame lift (platform lifted up by lava plume)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_mflft.h"
#include "d/res/res_mflft.h"
#include "d/res/res_always.h"
#include "d/d_bg_w.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_kankyo_wether.h"
#include "d/d_s_play.h"
#include "f_op/f_op_actor_mng.h"

static cXyz* wind_vec;
static s16 wy;
static f32* wp;

/* 00000078-00000170       .text setLiftUp__11mflft_classF4cXyz */
void mflft_class::setLiftUp(cXyz arg1) {
    if ((m29A != 0) || (std::fabsf(arg1.y - actor.current.pos.y) < 200.0f)) {
        actor.current.pos.x = arg1.x;
        actor.current.pos.z = arg1.z;
        cLib_addCalc2(&actor.current.pos.y, arg1.y, 0.2f, m2D0 * 1000.0f);
        cLib_addCalc2(&m2D0, 1.0f, 1.0f, 0.05f);
        actor.speed.y = 0.0f;
#if VERSION > VERSION_DEMO
        if (m2CE == 0) {
            dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }
#endif
        m2CE = 5;
    }
}

/* 000001AC-00000408       .text ride_call_back__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_call_back(dBgW*, fopAc_ac_c* arg1, fopAc_ac_c* arg2) {
    mflft_class* i_this = (mflft_class*)arg1;

    cMtx_YrotS(*calc_mtx, -i_this->actor.current.angle.y);
    cXyz sp38 = arg2->current.pos - i_this->actor.current.pos;
    cXyz sp2C;
    MtxPosition(&sp38, &sp2C);
    sp38 = arg2->old.pos - i_this->actor.current.pos;
    cXyz sp20;
    MtxPosition(&sp38, &sp20);
    s16 iVar2 = ((REG0_F(0) + 10.0f) / i_this->actor.scale.z) * sp2C.z;
    s16 iVar1 = ((REG0_F(0) + 10.0f) / i_this->actor.scale.x) * -sp2C.x;

    cLib_addCalcAngleS2(&i_this->actor.current.angle.x, iVar2, 10, 0x800);
    cLib_addCalcAngleS2(&i_this->actor.current.angle.z, iVar1, 10, 0x800);

    f32 fVar3 = (REG0_F(4) + 50.0f) * std::fabsf(sp2C.z - sp20.z);
    if (i_this->m2BC < fVar3) {
        i_this->m2BC = fVar3;
    }

    fVar3 = (REG0_F(4) + 50.0f) * std::fabsf(sp2C.x - sp20.x);
    if (i_this->m2C4 < fVar3) {
        i_this->m2C4 = fVar3;
    }

    fVar3 = (REG0_F(8) + 5.0f) * std::fabsf(sp2C.x - sp20.x);
    if ((fVar3 > 10.0f) && (i_this->m2B0 < fVar3)) {
        cLib_addCalc2(&i_this->m2B0, fVar3, 1.0f, REG0_F(7) + 1.2f);
    }

    fVar3 = (REG0_F(8) + 5.0f) * std::fabsf(sp2C.z - sp20.z);
    if ((fVar3 > 10.0f) && (i_this->m2B8 < fVar3)) {
        cLib_addCalc2(&i_this->m2B8, fVar3, 1.0f, REG0_F(7) + 1.2f);
    }
}

/* 00000408-00000488       .text himo_Draw__FP11mflft_class */
void himo_Draw(mflft_class* i_this) {
    i_this->mLineMat.update(10, (GXColor){150, 150, 150, 255}, &i_this->actor.tevStr);
    dComIfGd_set3DlineMat(&i_this->mLineMat);
}

/* 00000488-00000530       .text daMflft_Draw__FP11mflft_class */
static BOOL daMflft_Draw(mflft_class* i_this) {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &i_this->actor.current.pos, &i_this->actor.tevStr);
    g_env_light.setLightTevColorType(i_this->mpModel, &i_this->actor.tevStr);

    dComIfGd_setListBG();
    mDoExt_modelUpdateDL(i_this->mpModel);
    dComIfGd_setList();
    himo_Draw(i_this);
    return TRUE;
}

/* 00000530-00000614       .text kikuzu_set__FP11mflft_classP4cXyz */
void kikuzu_set(mflft_class* i_this, cXyz* arg1) {
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    csXyz sp18 = player->shape_angle;
    sp18.y -= -0x8000;

    JPABaseEmitter* pJVar4 = dComIfGp_particle_set(
        dPa_name::ID_COMMON_002B, arg1, &sp18, NULL, 0xff, NULL, -1, &i_this->actor.tevStr.mColorK0, &i_this->actor.tevStr.mColorK0, NULL
    );
    if (pJVar4 != NULL) {
        pJVar4->setRate(10.0f);
        pJVar4->setMaxFrame(1);
        pJVar4->setSpread(0.2f);
        pJVar4->setVolumeSweep(0.15f);
        JGeometry::TVec3<f32> s(REG0_F(16) + 0.7f, REG0_F(16) + 0.7f, REG0_F(16) + 0.7f);
        pJVar4->setGlobalParticleScale(s);
    }
}

/* 00000614-00000AB8       .text himo_cut_control__FP11mflft_classP4cXyzPUcUc */
void himo_cut_control(mflft_class* i_this, cXyz* arg1, unsigned char* arg2, unsigned char arg3) {
    dBgS_GndChk gndChk;
    cXyz sp30;
    cXyz sp24;

    sp30.x = 0.0f;
    sp30.y = 0.0f;
    sp30.z = *wp * 7.0f;

    cMtx_YrotS(*calc_mtx, wy);
    cXyz sp18;
    MtxPosition(&sp30, &sp18);

    cXyz sp0C;
    if (arg3 != 0) {
        sp0C.x = 0.0f;
        sp0C.y = 0.0f;
        sp0C.z = 0.0f;
        sp30.z = REG0_F(2) + 135.0f;
    } else {
        cMtx_YrotS(*calc_mtx, i_this->m6F8 + i_this->actor.shape_angle.y);
        sp30.z = REG0_F(11) + -4.0f;
        MtxPosition(&sp30, &sp0C);
        sp30.z = REG0_F(2) + 10.0f;
    }

    arg1++;
    for (s32 i = 1; i < 10; i++, arg1++, arg2++) {
        f32 fVar1;
        f32 fVar8;
        f32 fVar2 = (arg1->x - arg1[-1].x) + sp18.x + REG0_F(3) + sp0C.x;
        fVar1 = arg1->y - 10.0f;
        if (arg3 == 0) {
            sp24 = *arg1;
            sp24.y += 50.0f;
            gndChk.m_pos = sp24;
            f32 fVar9 = dComIfG_Bgsp()->GroundCross(&gndChk);
            if (fVar1 <= fVar9 + 10.0f) {
                fVar1 = fVar9 + 10.0f;
            }
        }

        fVar8 = fVar1 - arg1[-1].y;
        fVar1 = (arg1->z - arg1[-1].z) + sp18.z + sp0C.z;

        s16 iVar5;
        s32 iVar4 = cM_atan2s(fVar2, fVar1);
        iVar5 = -cM_atan2s(fVar8, std::sqrtf(SQUARE(fVar2) + SQUARE(fVar1)));

        cMtx_YrotS(*calc_mtx, iVar4);
        cMtx_XrotM(*calc_mtx, iVar5);
        MtxPosition(&sp30, &sp24);

        arg1->x = arg1[-1].x + sp24.x;
        arg1->y = arg1[-1].y + sp24.y;
        arg1->z = arg1[-1].z + sp24.z;
        *arg2 = 3;
    }
}

/* 00000E38-00001718       .text mflft_move__FP11mflft_class */
void mflft_move(mflft_class* i_this) {
    static u8 himo_off_check[] = {1, 2, 4};
    static s16 himo_off_ya[] = {0x0001, 0x0000, 0x5555, 0x2AAA, 0xAAAA, 0xD555, 0x8000, 0x0001};
    f32 fVar1;
    f32 fVar10;

    i_this->m298++;
    switch (i_this->m29A) {
    case 0: {
        s32 uVar6 = 0;
        for (s32 i = 0; i < ARRAY_SSIZE(i_this->m2D4); i++) {
            if (i_this->m2D4[i] != 0) {
                uVar6 |= himo_off_check[i];
            }
        }

        s16 target;
        s16 sVar2 = himo_off_ya[uVar6];
        if (sVar2 != 1) {
            target = -0x3000;
        } else {
            i_this->m6FA = 0;
            target = 0;
        }

        if (uVar6 == 7) {
            i_this->m29A = 1;
            dComIfGs_onEventBit(0x2a10);
            dBgS_ObjGndChk_Yogan gndChk;
            Vec pos;
            pos.x = i_this->actor.current.pos.x;
            pos.y = i_this->actor.current.pos.y;
            pos.z = i_this->actor.current.pos.z;
            pos.y += 1000.0f;

            gndChk.SetPos(&pos);
            f32 fVar10 = dComIfG_Bgsp()->GroundCross(&gndChk);
            if (fVar10 != -G_CM3D_F_INF) {
                i_this->m734 = fVar10;
            }

            if (i_this->m2A1 != 0xff) {
                dComIfGs_onSwitch(i_this->m2A1, fopAcM_GetRoomNo(&i_this->actor));
            }
        } else {
            if (i_this->m6F5 != 0) {
                i_this->m6F5--;
                if ((i_this->m6F5 == 0) && (uVar6 != 0)) {
                    u8 eventReg = dComIfGs_getEventReg(0xa507);
                    if (eventReg < 6) {
                        eventReg++;
                        dComIfGs_setEventReg(0xa507, eventReg);
                    }
                }
            }

            cLib_addCalcAngleS2(&i_this->m6FA, target, 4, 0x2000);
            cLib_addCalcAngleS2(&i_this->m6F8, sVar2, 2, 0x2000);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.x, 0, 10, 0x200);
            cLib_addCalcAngleS2(&i_this->actor.current.angle.z, 0, 10, 0x200);

            if (i_this->m2CE != 0) {
                fVar10 = 2000.0f;
                fVar1 = 250.0f;
                if (i_this->m778 == 0) {
                    i_this->m778 = 1;
                }
            } else {
                fVar10 = 100.0f;
                fVar1 = 20.0f;
                if (i_this->m778 == 2) {
                    i_this->m778 = 3;
                }
            }

            i_this->m2C8.x = i_this->m2BC * cM_ssin(i_this->m298 * 0x5dc);
            i_this->m2C8.z = i_this->m2C4 * cM_ssin(i_this->m298 * 0x514);
            cLib_addCalc2(&i_this->m2BC, fVar10, 1.0, fVar1 + REG0_F(3));
            cLib_addCalc2(&i_this->m2C4, fVar10, 1.0, fVar1 + REG0_F(3));
            i_this->m2A4.x = i_this->m2B0 * cM_ssin(i_this->m298 * 0x2ee);
            i_this->m2A4.z = i_this->m2B8 * cM_ssin(i_this->m298 * 900);
            cLib_addCalc0(&i_this->m2B0, 1.0, REG0_F(6) + 0.25f);
            cLib_addCalc0(&i_this->m2B8, 1.0, REG0_F(6) + 0.25f);
            i_this->actor.shape_angle = i_this->actor.current.angle + i_this->m2C8;
            i_this->actor.current.pos = i_this->actor.home.pos + i_this->m2A4;
        }
    } break;

    case 1:
        cLib_addCalc2(&i_this->actor.current.pos.x, i_this->actor.home.pos.x, 0.1f, 5.0f);
        cLib_addCalc2(&i_this->actor.current.pos.z, i_this->actor.home.pos.z, 0.1f, 5.0f);
        cLib_addCalcAngleS2(&i_this->actor.current.angle.x, 0, 10, 0x300);
        cLib_addCalcAngleS2(&i_this->actor.current.angle.z, 0, 10, 0x300);
        cLib_addCalcAngleS2(&i_this->m6FA, 0, 4, 0x200);

        if (i_this->m2CE != 0) {
            fVar10 = 2500.0f;
            fVar1 = 250.0f;
            if (i_this->m778 == 0) {
                i_this->m778 = 1;
            }
        } else {
            fVar10 = 400.0f;
            fVar1 = 20.0f;
            if (i_this->m778 == 2) {
                i_this->m778 = 3;
            }
        }
        i_this->m2C8.x = i_this->m2BC * cM_ssin(i_this->m298 * 800);
        i_this->m2C8.z = i_this->m2C4 * cM_ssin(i_this->m298 * 700);
        cLib_addCalc2(&i_this->m2BC, fVar10, 1.0f, fVar1);
        cLib_addCalc2(&i_this->m2C4, fVar10, 1.0f, fVar1);

        i_this->actor.shape_angle = i_this->actor.current.angle + i_this->m2C8;
        i_this->actor.current.pos.y += i_this->actor.speed.y;
        i_this->actor.speed.y -= 5.0f;
        if (i_this->actor.speed.y < -300.0f) {
            i_this->actor.speed.y = -300.0f;
        }

        if (i_this->actor.current.pos.y <= i_this->m734 + 80.0f) {
            i_this->actor.current.pos.y = i_this->m734 + 80.0f;
            if (i_this->actor.speed.y < -50.0f) {
                i_this->m2C4 = 2000.0f;
                i_this->m2BC = 2000.0f;
                dComIfGp_particle_set(dPa_name::ID_SCENE_8231, &i_this->actor.current.pos, &i_this->actor.shape_angle);
                fopAcM_seStartCurrent(&i_this->actor, JA_SE_OBJ_BAL_LIFT_LANDING, 0);
                dComIfGp_getVibration().StartShock(REG0_S(2) + DEMO_SELECT(4, 5), -0x21, cXyz(0.0f, 1.0f, 0.0f));
            }
            i_this->actor.speed.y = 0.0f;
            cLib_addCalcAngleS2(&i_this->m6FA, 0, 2, 0x2000);
        }
        break;
    }
}

static f32 bure_p[] = {0.0f, 0.1f, 0.3f, 0.6f, 0.85f, 1.0f, 0.85f, 0.6f, 0.3f, 0.1f, 0.0f, 0.0f};

/* 000019C0-00001E5C       .text himo_move__FP11mflft_class */
void himo_move(mflft_class* i_this) {
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    cXyz sp48;
    cXyz sp3C;
    cXyz* line1;
    cXyz* line2;
    s32 i;
    u8* lineSize;

    for (i = 0; i < ARRAY_SSIZE(i_this->m6EC); i++) {
        cMtx_YrotS(*calc_mtx, i_this->m298);

        sp48.x = sp48.y = 0.0f;
        sp48.z = i_this->m6EC[i] * cM_ssin(i_this->m298 * 15000);
        MtxPosition(&sp48, &sp3C);

        line1 = i_this->mLineMat.mpLines[i].mpSegments;
        line2 = i_this->mLineMat.mpLines[i + 3].mpSegments;

        if (i_this->m2D4[i] == 0) {
            sp48 = i_this->m2FC[i] - i_this->m2D8[i];
            lineSize = i_this->mLineMat.mpLines[i].mpSize;

            for (s32 j = 0; j < 10; line1++, line2++, lineSize++, j++) {
                if (j < 9) {
                    f32 tmp = j / 27.0f;
                    *line1 = i_this->m2D8[i] + (sp48 * tmp);
                    line1->x += sp3C.x * bure_p[j] * (REG0_F(0) + 1.0f);
                    line1->z += sp3C.z * bure_p[j] * (REG0_F(0) + 1.0f);
                } else {
                    *line1 = i_this->m2FC[i];
                }
                *line2 = i_this->m2D8[i];
                *lineSize = 3;
            }

            if (i_this->mCyls[i].ChkTgHit() && (i_this->m6EC[i] < 10)) {
                i_this->m6EC[i] = REG0_S(3) + 0xf;
                CcAtInfo ccAtInfo;
                ccAtInfo.mpObj = i_this->mCyls[i].GetTgHitObj();
                at_power_check(&ccAtInfo);

                if (ccAtInfo.mDamage > 1) {
                    ccAtInfo.mDamage = 4;
                }

                i_this->m6F2[i] -= ccAtInfo.mDamage;

                s32 soundId;
                if (i_this->m6F2[i] <= 0) {
                    i_this->m2D4[i] = 1;
                    i_this->m2C4 = 2000.0f;
                    i_this->m2BC = 2000.0f;
                    soundId = JA_SE_LK_CUT_SBRIDGE_ROPE;
                    i_this->m6F5 = 0x14;
                } else {
                    soundId = JA_SE_LK_HIT_SBRIDGE_ROPE;
                }

                if (ccAtInfo.mpActor != NULL) {
                    sp48 = i_this->m2D8[i];
                    sp48.y = ccAtInfo.mpActor->eyePos.y;
                    dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &sp48, &player->shape_angle);
                    kikuzu_set(i_this, &sp48);
                    mDoAud_seStart(soundId, &ccAtInfo.mpActor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(&i_this->actor)));
                }
            }
            i_this->mCyls[i].SetC(i_this->m2D8[i]);
            dComIfG_Ccsp()->Set(&i_this->mCyls[i]);
        } else {
#if VERSION > VERSION_DEMO
            cXyz* line2 = i_this->mLineMat.mpLines[i + 3].mpSegments;
#endif

            *i_this->mLineMat.mpLines[i].mpSegments = i_this->m2D8[i];
            lineSize = i_this->mLineMat.mpLines[i].mpSize;
            himo_cut_control(i_this, line1, lineSize, NULL);
            *line2 = i_this->m2FC[i];
            lineSize = i_this->mLineMat.mpLines[i + 3].mpSize;
            himo_cut_control(i_this, line2, lineSize, 1);
        }
    }
}

/* 00001E5C-00002008       .text eff_cont__FP11mflft_class */
void eff_cont(mflft_class* i_this) {
    cXyz sp24 = i_this->actor.current.pos;
    sp24.y -= REG0_F(1) + 90.0f;

    switch (i_this->m778) {
    case 0:
        break;

    case 1:
        i_this->m774 = dComIfGp_particle_set(dPa_name::ID_SCENE_8105, &sp24);
        if (i_this->m774 != NULL) {
            cXyz s(1.8f, 1.8f, 1.8f);
            i_this->m774->setGlobalScale(s);
            i_this->m778 = 2;
        } else {
            i_this->m778 = 0;
        }
        break;

    case 2:
        if (i_this->m774 != NULL) {
            MtxTrans(0.0f, -90.0f, 0.0f, 1);
            i_this->m774->setGlobalRTMatrix(*calc_mtx);
        }

    case 3:
        if (i_this->m778 == 3) {
            if (i_this->m774 != NULL) {
                i_this->m774->becomeInvalidEmitter();
                i_this->m774 = NULL;
            }
            i_this->m778 = 0;
        }
        break;
    }
}

/* 00002008-00002284       .text daMflft_Execute__FP11mflft_class */
static BOOL daMflft_Execute(mflft_class* i_this) {
    if (i_this->m2CE != 0) {
        i_this->m2CE--;

#if VERSION == VERSION_DEMO
        if ((i_this->m298 & 7) == 0) {
            if (cM_rndF(1.0f) < 0.5f) {
                dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            }
        }
#endif

    } else {
        i_this->m2D0 = 0.0f;
    }

    wind_vec = dKyw_get_wind_vec();
    wy = cM_atan2s(wind_vec->x, wind_vec->z);
    wp = dKyw_get_wind_power();
    mflft_move(i_this);

    MtxTrans(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z, 0);

    cMtx_YrotM(*calc_mtx, i_this->actor.shape_angle.y);
    cMtx_YrotM(*calc_mtx, i_this->m6F8);
    cMtx_XrotM(*calc_mtx, i_this->m6FA);
    cMtx_YrotM(*calc_mtx, -i_this->m6F8);
    cMtx_XrotM(*calc_mtx, i_this->actor.shape_angle.x);
    cMtx_ZrotM(*calc_mtx, i_this->actor.shape_angle.z);

    i_this->mpModel->setBaseTRMtx(*calc_mtx);

    for (s32 i = 0; i < ARRAY_SSIZE(i_this->m2FC); i++) {
        static f32 xd[] = {0.0f, -117.0f, 117.0f};
        static f32 zd[] = {-134.0f, 70.0f, 70.0f};

        MtxPush();

        cXyz sp08;
        sp08.x = i_this->actor.scale.x * xd[i];
        sp08.y = 15.0f;
        sp08.z = i_this->actor.scale.z * zd[i];
        MtxPosition(&sp08, &i_this->m2D8[i]);

        if (i_this->m6F6 != 0) {
            i_this->m6F6--;
            i_this->m2FC[i] = i_this->m2D8[i];
            i_this->m2FC[i].y = i_this->actor.home.pos.y + 2000.0f + REG0_F(19);
        }

        if (i_this->m6EC[i] != 0) {
            i_this->m6EC[i]--;
        }

        MtxPull();
    }

    MtxPush();

    eff_cont(i_this);

    MtxPull();

    f32 y = 1.0f;
    if (i_this->m2CE != 0) {
        y = 5.0f;
    }
    MtxScale(1.0f, y, 1.0f, 1);

    MTXCopy(*calc_mtx, i_this->m700);

    i_this->pm_bgw->Move();
    himo_move(i_this);
    return TRUE;
}

/* 00002284-0000228C       .text daMflft_IsDelete__FP11mflft_class */
static BOOL daMflft_IsDelete(mflft_class*) {
    return TRUE;
}

/* 0000228C-00002310       .text daMflft_Delete__FP11mflft_class */
static BOOL daMflft_Delete(mflft_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Mflft");

#if VERSION > VERSION_DEMO
    if (i_this->actor.heap != NULL)
#endif
    {
        dComIfG_Bgsp()->Release(i_this->pm_bgw);
    }

    if (i_this->m774 != NULL) {
        i_this->m774->becomeInvalidEmitter();
        i_this->m774 = NULL;
    }

    return TRUE;
}

/* 00002310-000024C8       .text CallbackCreateHeap__FP10fopAc_ac_c */
static BOOL CallbackCreateHeap(fopAc_ac_c* a_this) {
    mflft_class* actor = (mflft_class*)a_this;

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes("Mflft", MFLFT_BDL_MFLFT);
    actor->mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (actor->mpModel == NULL) {
        return FALSE;
    }

    JUT_ASSERT(DEMO_SELECT(1042, 1053), modelData != NULL);

    actor->pm_bgw = new dBgW();
    JUT_ASSERT(DEMO_SELECT(1047, 1058), actor->pm_bgw != NULL);

    actor->pm_bgw->Set((cBgD_t*)dComIfG_getObjectRes("Mflft", MFLFT_DZB_MFLFT), dBgW::MOVE_BG_e, &actor->m700);
    actor->pm_bgw->SetCrrFunc(dBgS_MoveBGProc_Typical);
    actor->pm_bgw->SetRideCallback(ride_call_back);
    if (!actor->mLineMat.init(6, 10, (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE), 1)) {
        return FALSE;
    }
    return TRUE;
}

/* 000024C8-00002A34       .text daMflft_Create__FP10fopAc_ac_c */
static cPhs_State daMflft_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcCyl himo_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
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
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 10.0f,
            /* Height */ 1000.0f,
        }},
    };

    mflft_class* i_this = (mflft_class*)a_this;

    fopAcM_SetupActor(&i_this->actor, mflft_class);

    cPhs_State PVar2 = dComIfG_resLoad(&i_this->mPhase, "Mflft");
    if (PVar2 == cPhs_COMPLEATE_e) {
        i_this->m2A0 = fopAcM_GetParam(a_this);
        if (i_this->m2A0 == 0xff) {
            i_this->m2A0 = 0;
        }

        i_this->m2A1 = fopAcM_GetParam(a_this) >> 0x18;
        if (!fopAcM_entrySolidHeap(a_this, CallbackCreateHeap, 0x10000)) {
            return cPhs_ERROR_e;
        }

        if ((i_this->pm_bgw != NULL) && dComIfG_Bgsp()->Regist(i_this->pm_bgw, a_this)) {
            return cPhs_ERROR_e;
        }

        switch (i_this->m2A0) {
        case 1:
            a_this->scale.x = 0.9f;
            a_this->scale.z = 0.9f;
            break;

        case 2:
            a_this->scale.x = 0.8f;
            a_this->scale.z = 0.8f;
            break;

        case 3:
            a_this->scale.x = 0.7f;
            a_this->scale.z = 0.7f;
            break;

        default:
            a_this->scale.z = 1.0f;
            a_this->scale.x = 1.0f;
            break;
        }

        a_this->scale.y = 1.0f;
        fopAcM_SetMtx(a_this, i_this->mpModel->getBaseTRMtx());
        fopAcM_SetMin(a_this, a_this->scale.x * -200.0f, -10000.0f, a_this->scale.z * -200.0f);
        fopAcM_SetMax(a_this, a_this->scale.x * 200.0f, 10000.0f, a_this->scale.z * 200.0f);

        i_this->mpModel->setBaseScale(a_this->scale);
        i_this->mStts.Init(0xff, 0xff, a_this);

        for (s32 i = 0; i < ARRAY_SSIZE(i_this->mCyls); i++) {
            i_this->mCyls[i].Set(himo_cyl_src);
            i_this->mCyls[i].SetStts(&i_this->mStts);
            i_this->m6F2[i] = 3;
        }

        i_this->m6F6 = 10;
        if ((i_this->m2A1 != 0xff) && dComIfGs_isSwitch(i_this->m2A1, fopAcM_GetRoomNo(a_this))) {
            for (s32 i = 0; i < ARRAY_SSIZE(i_this->m2D4); i++) {
                i_this->m2D4[i] = 1;
            }

            dBgS_ObjGndChk_Yogan gndChk;
            Vec pos;
            pos.x = a_this->current.pos.x;
            pos.y = a_this->current.pos.y;
            pos.z = a_this->current.pos.z;
            pos.y += 1000.0f;

            gndChk.SetPos(&pos);
            f32 fVar9 = dComIfG_Bgsp()->GroundCross(&gndChk);
            if (fVar9 != -G_CM3D_F_INF) {
                a_this->current.pos.y = fVar9;
            }
        }

        daMflft_Execute(i_this);
    }

    return PVar2;
}

static actor_method_class l_daMflft_Method = {
    (process_method_func)daMflft_Create,
    (process_method_func)daMflft_Delete,
    (process_method_func)daMflft_Execute,
    (process_method_func)daMflft_IsDelete,
    (process_method_func)daMflft_Draw,
};

actor_process_profile_definition g_profile_MFLFT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_MFLFT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(mflft_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_MFLFT,
    /* Actor SubMtd */ &l_daMflft_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
