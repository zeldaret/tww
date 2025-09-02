/**
 * d_a_himo3.cpp
 * Object - Rope (Pirate Ship rope minigame, Forsaken Fortress)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_himo3.h"
#include "d/actor/d_a_player.h"
#include "d/res/res_always.h"
#include "d/res/res_bgn.h"
#include "d/res/res_link.h"
#include "d/res/res_himo3.h"
#include "d/d_s_play.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/d_kankyo_wether.h"
#include "f_op/f_op_actor_mng.h"

class himo3HIO_c : public JORReflexible {
public:
    himo3HIO_c() {
        m06 = 0;
        m08 = 0.75f;
        m0C = 0.5f;
        m10 = 0xEB;
        m12 = 0x7D;
        m14 = 0;
        m18 = 5.0f;
    }
    virtual ~himo3HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x06 */ s16 m06;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ s16 m10;
    /* 0x10 */ s16 m12;
    /* 0x10 */ s16 m14;
    /* 0x18 */ f32 m18;
}; // size = 0x1C

static f32 HIMO3_SCALE;
static bool hio_set;
static himo3HIO_c l_HIO;

/* 000000EC-00000C58       .text himo3_control__FP11himo3_classP7himo3_s */
void himo3_control(himo3_class* i_this, himo3_s* arg1) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s32 i = 1;
    cXyz spAC;
    cXyz spA0;
    cXyz sp94;
    f32 unaff_f28;
    himo3_s* pcVar11 = &arg1[1];

    if (i_this->m02BE != 0) {
        s16 target;
        if (i_this->m02BE == 1) {
            if (player->getRopeGrabRightHand()) {
                spAC = player->getRightHandPos();
            } else {
                spAC = player->getLeftHandPos();
            }
            target = player->shape_angle.y;
        } else {
            spAC = i_this->m21F4;
            target = i_this->m2200;
        }

        if (i_this->m15C4.y == -23535.0f) {
            i_this->m15C4 = spAC;
        }

        cXyz sp88 = spAC - i_this->current.pos;
        f32 sqrt = sp88.abs();
        s32 iVar8 = sqrt / HIMO3_SCALE;
        unaff_f28 = sqrt / HIMO3_SCALE - iVar8;
        if (iVar8 >= i_this->m15C0 - 1) {
            iVar8 = i_this->m15C0 - 1;
        }

        if (iVar8 > 1) {
            for (i = 1; i < iVar8; i++, pcVar11++) {
                f32 fVar12 = (f32)i / iVar8;
                pcVar11->m00.x = i_this->current.pos.x + sp88.x * fVar12;
                pcVar11->m00.y = i_this->current.pos.y + sp88.y * fVar12;
                pcVar11->m00.z = i_this->current.pos.z + sp88.z * fVar12;
            }
        }

        cLib_addCalcAngleS2(&i_this->current.angle.y, target, 2, 0x2000);

        spA0 = spAC - i_this->m15C4;
        cMtx_YrotS(*calc_mtx, -target);
        MtxPosition(&spA0, &sp94);
        f32 tmp1 = sp94.z * DEMO_SELECT(REG0_F(5) + -10.0f, -10.0f);
        f32 tmp2 = DEMO_SELECT(REG0_F(6) + 10.0f, 10.0f);
        cLib_addCalc2(&i_this->m15D0, tmp1, 0.1f, tmp2 * i_this->m15E4);

        tmp1 = sp94.x * DEMO_SELECT(REG0_F(5) + -10.0f, -10.0f);
        tmp2 = DEMO_SELECT(REG0_F(6) + 10.0f, 10.0f);
        cLib_addCalc2(&i_this->m15D8, tmp1, 0.1f, tmp2 * i_this->m15E4);

        if (std::fabsf(sp94.z) > 1.0f || std::fabsf(sp94.x) > 1.0f) {
            cLib_addCalc2(&i_this->m15E4, 1.0f, 1.0f, 0.05f);
        } else {
            cLib_addCalc2(&i_this->m15E4, 0.1f, 1.0f, 0.05f);
        }

        if (fopAcM_GetParam(i_this) == 3) {
            i_this->m02BE = 0;
            i_this->m02BC = 0x1e;
            i_this->m15E0 = 0.0f;
        }
        i_this->m15C4 = spAC;
    } else {
        i_this->m15D0 += i_this->m15D4;
        f32 tmp = i_this->m15D0 * DEMO_SELECT(REG0_F(7) + -0.003f, -0.003f);
        i_this->m15D4 += tmp;
        cLib_addCalc0(&i_this->m15D0, 0.05f, DEMO_SELECT(REG0_F(9) + 1.0f, 1.0f));
        i_this->m15D8 += i_this->m15DC;
        tmp = i_this->m15D8 * DEMO_SELECT(REG0_F(7) + -0.003f, -0.003f);
        i_this->m15DC += tmp;
        cLib_addCalc0(&i_this->m15D8, 0.05f, DEMO_SELECT(REG0_F(9) + 1.0f, 1.0f));

        if (fopAcM_GetParam(i_this) == 1) {
            i_this->m02BE = 1;
            i_this->m15E0 = 1.0f;
            if (strcmp(dComIfGp_getStartStageName(), "majroom") == 0 || strcmp(dComIfGp_getStartStageName(), "Majroom") == 0 ||
                strcmp(dComIfGp_getStartStageName(), "MajyuE") == 0)
            {
                dComIfGs_onEventBit(0x402);
            }
        } else if (fopAcM_GetParam(i_this) == 2) {
            i_this->m02BE = 2;
            i_this->m15E0 = 1.0f;
        }
        i_this->m15C4.y = -23535.0f;
    }

    cMtx_YrotS(*calc_mtx, i_this->current.angle.y);
    spA0.x = i_this->m15D8;
    spA0.y = 0.0f;
    spA0.z = i_this->m15D0;
    cXyz sp7C;
    MtxPosition(&spA0, &sp7C);
    cXyz* pcVar7 = dKyw_get_wind_vec();
    s16 iVar8 = cM_atan2s(pcVar7->x, pcVar7->z);
    f32* pfVar9 = dKyw_get_wind_power();

    if (i_this->m02BE != 0) {
        cLib_addCalc2(&i_this->m15E8, *pfVar9 * 0.5f, 1.0f, 0.05f);
    } else {
        cLib_addCalc2(&i_this->m15E8, *pfVar9, 1.0f, 0.001f);
    }

    if (i_this->m15F0 > 0.01f) {
        i_this->m15FA++;
    } else {
        i_this->m15FA = 0;
    }

    cLib_addCalc2(&i_this->m15F0, i_this->m15F4, 0.2f, DEMO_SELECT(REG0_F(2) + 0.05f, 0.05f));
    cLib_addCalc0(&i_this->m15F4, 1.0f, DEMO_SELECT(REG0_F(3) + 0.005f, 0.005f));
    cMtx_YrotS(*calc_mtx, i_this->m15F8);
    spA0.x = 0.0f;
    spA0.y = 0.0f;
    spA0.z = cM_ssin(i_this->m15FA * DEMO_SELECT(REG0_S(5) + 500, 500)) * DEMO_SELECT(REG0_F(4) + 100.0f, 100.0f) * i_this->m15F0;
    cXyz sp70;
    MtxPosition(&spA0, &sp70);
    cMtx_YrotS(*calc_mtx, iVar8);
    spA0.x = 0.0f;
    spA0.y = 0.0f;
    spA0.z = cM_ssin(i_this->m02BA * DEMO_SELECT(REG0_S(5) + 500, 500)) * DEMO_SELECT(REG0_F(4) + 100.0f, 100.0f) * i_this->m15E8;
    cXyz sp64;
    MtxPosition(&spA0, &sp64);
    sp64 += sp70;
    f32 tmpReg = DEMO_SELECT(REG0_F(1), 0.0f);
    spA0.x = 0.0f;
    spA0.y = 0.0f;
    f32 tmp200 = DEMO_SELECT(REG0_F(8) + -200.0f, -200.0f);

    s32 j = 0;

    f32 fVar12;
    if ((i_this->m02BE == 0) && (i_this->m02BC == 0)) {
        fVar12 = DEMO_SELECT(REG0_F(2) + 30.0f + 20.0f - 20.0f, 30.0f);
    } else {
        fVar12 = -200.0f;
    }

    u8 bVar4 = 0;
    s16 unaff_r24;
    s16 unaff_r23;

    for (; i < i_this->m15C0; i++, pcVar11++) {
        cXyz sp60;
        sp60.z = 0.0f;
        sp60.y = 0.0f;
        sp60.x = 0.0f;

        f32 fVar1 = pcVar11->m00.x - pcVar11[-1].m00.x + pcVar11->m0C.x + sp7C.x + sp64.x + sp60.x;
        f32 fVar2 = pcVar11->m00.y - pcVar11[-1].m00.y + tmp200 + pcVar11->m0C.y + sp60.y;
        f32 fVar3 = pcVar11->m00.z - pcVar11[-1].m00.z + pcVar11->m0C.z + sp7C.z + sp64.z + sp60.z;

        unaff_r24 = -cM_atan2s(fVar2, fVar3);
        unaff_r23 = (s16)cM_atan2s(fVar1 + 0.0f, std::sqrtf(SQUARE(fVar2) + SQUARE(fVar3)));
        cMtx_XrotS(*calc_mtx, unaff_r24);
        cMtx_YrotM(*calc_mtx, unaff_r23);

        spA0.z = HIMO3_SCALE;
        if (bVar4 == 0) {
            spA0.z = HIMO3_SCALE - unaff_f28 * HIMO3_SCALE;
            bVar4++;
        }
        MtxPosition(&spA0, &sp94);
        pcVar11->m0C = pcVar11->m00;
        pcVar11->m00 = pcVar11[-1].m00 + sp94;
        pcVar11->m0C.x = (pcVar11->m00.x - pcVar11->m0C.x) * tmpReg;
        pcVar11->m0C.y = (pcVar11->m00.y - pcVar11->m0C.y) * tmpReg;
        pcVar11->m0C.z = (pcVar11->m00.z - pcVar11->m0C.z) * tmpReg;

        if ((i_this->m0298 == 0xf) && (i == i_this->m15C0 - 1)) {
            if (i_this->m02BE == 0) {
                i_this->mCyl.SetC(pcVar11->m00);
            } else {
                cXyz sp4C(-10000.0f, -10000.0f, 0.0f);
                i_this->mCyl.SetC(sp4C);
            }
            dComIfG_Ccsp()->Set(&i_this->mCyl);
        } else if (((i + i_this->m02BA * 3 & 0xf) == 0) && (j < 5)) {
            i_this->mSphs[j].SetR(fVar12);
            i_this->mSphs[j].SetC(pcVar11->m00);
            dComIfG_Ccsp()->Set(&i_this->mSphs[j]);
            j++;
        }
    }

    cXyz* pcVar10 = i_this->mLineMat.getPos(0);
    himo3_s* phVar11 = i_this->m02C0;
    for (s32 i = 0; i < i_this->m15C0; i++, phVar11++, pcVar10++) {
        if (i_this->m15E0 >= 0.999f) {
            *pcVar10 = phVar11->m00;
        } else {
            cLib_addCalc2(&pcVar10->x, phVar11->m00.x, 1.0f, i_this->m15E0 * 100.0f);
            cLib_addCalc2(&pcVar10->y, phVar11->m00.y, 1.0f, i_this->m15E0 * 100.0f);
            cLib_addCalc2(&pcVar10->z, phVar11->m00.z, 1.0f, i_this->m15E0 * 100.0f);
        }

        if ((i_this->m0298 != 0xf) && (i == i_this->m15C0 - 1)) {
            MtxTrans(pcVar10->x, pcVar10->y, pcVar10->z, 0);
            cMtx_XrotM(*calc_mtx, unaff_r24);
            cMtx_YrotM(*calc_mtx, unaff_r23);
            f32 fVar14 = l_HIO.m08;
            if (i_this->m0298 != 1) {
                cMtx_XrotM(*calc_mtx, -0x4000);
                fVar14 = l_HIO.m0C;
            }
            MtxScale(fVar14, fVar14, fVar14, true);
            i_this->mpModel->setBaseTRMtx(*calc_mtx);
        }
    }

    cLib_addCalc2(&i_this->m15E0, 1.0f, 1.0f, DEMO_SELECT(REG0_F(3) + 0.05f, 0.05f));
}

/* 00000C58-00000D1C       .text ga_draw__FP11himo3_class */
void ga_draw(himo3_class* i_this) {
    h3_ga_s* ga = &i_this->m2114[0];

    for (s32 i = 0; i < ARRAY_SSIZE(i_this->m2114); i++, ga++) {
        if (ga->m2E == 1) {
            MtxTrans(ga->mPos.x, ga->mPos.y, ga->mPos.z, 0);
            cMtx_YrotM(*calc_mtx, ga->m1E);
            cMtx_XrotM(*calc_mtx, ga->m1C);
            MtxScale(ga->m24, ga->m24 * ga->m28, ga->m24, true);
            MtxTrans(0.0f, -18.0f, 0.0f, 1);
            ga->mpModel->setBaseTRMtx(*calc_mtx);
            mDoExt_modelUpdateDL(ga->mpModel);
        }
    }
}

/* 00000D1C-00000EF8       .text daHimo3_Draw__FP11himo3_class */
static BOOL daHimo3_Draw(himo3_class* i_this) {
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &i_this->current.pos, &i_this->tevStr);
    f32 fVar1;
    if (i_this->m0298 == 0xf) {
        fVar1 = DEMO_SELECT(REG0_F(0) + 4.625f, 4.625f);
    } else {
        fVar1 = DEMO_SELECT(REG0_F(0) + 3.75f, 3.75f);
    }

    i_this->mLineMat.update(i_this->m15C0, fVar1, (GXColor){200, 150, 50, 255}, 0, &i_this->tevStr);
    dComIfGd_set3DlineMat(&i_this->mLineMat);

    if (i_this->m0298 != 0xf) {
        J3DModel* model = i_this->mpModel;
        g_env_light.setLightTevColorType(model, &i_this->tevStr);
        mDoExt_modelUpdateDL(model);

        if (i_this->m0298 == 0) {
            if (l_HIO.m06 == 2) {
                dComIfGd_setSpotModel(dDlst_alphaModel_c::TYPE_TWO_SPHERES, i_this->m1840, 0x20);
            } else {
                GXColor color;
                color.r = l_HIO.m10;
                color.g = l_HIO.m12;
                color.b = l_HIO.m14;
                color.a = 0;
                dComIfGd_setAlphaModelColor(color);
                if (l_HIO.m06 == 0) {
                    dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_SPHERE, i_this->m1840, i_this->m1878);
                } else {
                    dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_TWO_SPHERES, i_this->m1840, i_this->m1878);
                }
            }

            dComIfGd_setSimpleShadow2(&i_this->m1624, i_this->mAcch.GetGroundH(), i_this->m20F8, i_this->mAcch.m_gnd);
            ga_draw(i_this);
        }
    }
    return TRUE;
}

/* 00000EF8-00001108       .text ga_move__FP11himo3_class */
void ga_move(himo3_class* i_this) {
    cXyz sp30(0.0f, 0.0f, 10.0f);
    cXyz sp24;

    if (i_this->m2114[0].m2E) {
        if (i_this->m2114[0].m2F != 0) {
            i_this->m2114[0].m2F--;
        } else {
            i_this->m2114[0].m2F = cM_rndF(10.0f);
            i_this->m2114[0].m10.x = i_this->m1624.x + cM_rndFX(150.0f);
            i_this->m2114[0].m10.y = i_this->m1624.y + cM_rndFX(100.0f);
            i_this->m2114[0].m10.z = i_this->m1624.z + cM_rndFX(150.0f);
        }

        cXyz sp0C = i_this->m2114[0].m10 - i_this->m2114[0].mPos;
        cLib_addCalcAngleS2(&i_this->m2114[0].m1E, cM_atan2s(sp0C.x, sp0C.z), 2, 0x1000);
        cLib_addCalcAngleS2(&i_this->m2114[0].m1C, -cM_atan2s(sp0C.y, std::sqrtf(SQUARE(sp0C.x) + SQUARE(sp0C.z))), 2, 0x1000);
        cMtx_YrotS(*calc_mtx, i_this->m2114[0].m1E);
        cMtx_XrotM(*calc_mtx, i_this->m2114[0].m1C);
        MtxPosition(&sp30, &sp24);
        i_this->m2114[0].mPos += sp24;
        i_this->m2114[0].m28 = cM_ssin(i_this->m2114[0].m2C);
        i_this->m2114[0].m2C += 0x3E00;
    }
}

/* 00001108-00001128       .text setActorHang__11himo3_classF4cXyzs */
void himo3_class::setActorHang(cXyz arg1, short arg2) {
    m21F4 = arg1;
    m2200 = arg2;
}

/* 00001128-000014F8       .text path_move__FP11himo3_class */
void path_move(himo3_class* i_this) {
    cXyz sp28;
    cXyz sp10;
    dPnt* pnt;

    switch (i_this->m02A4) {
    case 0:
        i_this->m029C += i_this->m029D;
        if (i_this->m029C >= (s8)i_this->ppd->m_num) {
            if (dPath_ChkClose(i_this->ppd)) {
                i_this->m029C = 0;
            } else {
                i_this->m029D = -1;
                i_this->m029C = i_this->ppd->m_num - 2;
            }

            if ((s32)i_this->ppd->m_nextID != 0xFFFF) {
                i_this->ppd = dPath_GetRoomPath(i_this->ppd->m_nextID, fopAcM_GetRoomNo(i_this));
                JUT_ASSERT(DEMO_SELECT(890, 891), i_this->ppd != NULL);
            }
        } else if (i_this->m029C < 0) {
            i_this->m029D = 1;
            i_this->m029C = 1;
        }

        i_this->m02A4 = 1;
        pnt = &i_this->ppd->m_points[i_this->m029C];
        i_this->m02A8 = pnt->m_position;

    case 1:
        sp10 = i_this->m02A8 - i_this->current.pos;
        if (i_this->m02BE == 0) {
            u8 uStack_14 = i_this->ppd->m_points[i_this->m029C].mArg3;
            if (uStack_14 != 0 && uStack_14 != 0xff) {
                cLib_addCalc2(&i_this->speedF, uStack_14, 1.0f, uStack_14 * 0.1f);
            } else {
                uStack_14 = i_this->m0299;
                cLib_addCalc2(&i_this->speedF, uStack_14, 1.0f, uStack_14 * 0.1f);
            }
        } else {
            cLib_addCalc0(&i_this->speedF, 1.0f, 1.0f);
        }

        sp28.x = 0.0f;
        sp28.y = 0.0f;
        sp28.z = i_this->speedF;
        cMtx_YrotS(*calc_mtx, cM_atan2s(sp10.x, sp10.z));
        f32 fVar8 = std::sqrtf(SQUARE(sp10.x) + SQUARE(sp10.z));
        cMtx_XrotM(*calc_mtx, -cM_atan2s(sp10.y, fVar8));
        MtxPosition(&sp28, &i_this->speed);
        i_this->current.pos += i_this->speed;
        if (sp10.abs() < i_this->speedF * 2.0f) {
            i_this->m02A4 = 0;
        }
        break;
    }
}

/* 000014F8-00001A3C       .text daHimo3_Execute__FP11himo3_class */
static BOOL daHimo3_Execute(himo3_class* i_this) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    if (i_this->m02BC != 0) {
        i_this->m02BC--;
    }

    if (i_this->m029B != 0) {
        path_move(i_this);
    }

    i_this->m02BA++;
    i_this->m02C0[0].m00 = i_this->current.pos;
    himo3_control(i_this, i_this->m02C0);

    if (i_this->m0298 != 0xf) {
        if (i_this->mSph.ChkTgHit()) {
            cCcD_Obj* pcVar5 = i_this->mSph.GetTgHitObj();
            if (pcVar5 != NULL && pcVar5->ChkAtType(AT_TYPE_WIND)) {
                i_this->m15F8 = player->shape_angle.y;
                i_this->m15F4 = DEMO_SELECT(REG0_F(0) + 1.0f, 1.0f);
            }
        }

        i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        i_this->m1870 = l_HIO.m18;
        cMtx_copy(i_this->mpModel->getBaseTRMtx(), *calc_mtx);

        if (i_this->m0298 == 0) {
            MtxTrans(DEMO_SELECT(REG0_F(6) + 10.0f, 10.0f), DEMO_SELECT(REG0_F(7) + -140.0f, -140.0f), DEMO_SELECT(REG0_F(8) + -15.0f, -15.0f), 1);
        } else {
            MtxTrans(DEMO_SELECT(REG0_F(6), 0.0f), DEMO_SELECT(REG0_F(7), 0.0f), DEMO_SELECT(REG0_F(8) + 35.0f, 35.0f), 1);
        }

        MtxScale(i_this->m1870, i_this->m1870, i_this->m1870, true);
        MTXCopy(*calc_mtx, i_this->m1840);

        cXyz sp28;
        sp28.z = 0.0f;
        sp28.y = 0.0f;
        sp28.x = 0.0f;
        MtxPosition(&sp28, &i_this->m1624);
        i_this->mSph.SetC(i_this->m1624);
        dComIfG_Ccsp()->Set(&i_this->mSph);

        if (i_this->m0298 == 0) {
            for (s32 i = 0; i < ARRAY_SSIZE(i_this->m02B4); i++) {
                if (i_this->m02B4[i]) {
                    i_this->m02B4[i]--;
                }
            }

            if (i_this->m02B4[0] == 0) {
                i_this->m02B4[0] = cM_rndF(DEMO_SELECT(REG0_F(2) + 10.0f, 10.0f)) + 5.0f + DEMO_SELECT(REG0_F(3), 0.0f);
                i_this->m187C = cM_rndF(DEMO_SELECT(REG0_F(6) + 16.0f, 16.0f)) + 4.0f + DEMO_SELECT(REG0_F(7), 0.0f);
            }

            if (i_this->m02B4[1] == 0) {
                i_this->m02B4[1] = cM_rndF(6.0f) + 3.0f;
            }

            cLib_addCalc2(&i_this->m1878, i_this->m187C, 1.0f, DEMO_SELECT(REG0_F(4) + 0.1f, 0.1f));
#if VERSION == VERSION_DEMO
            if (!i_this->m2110) {
#else
            if (i_this->m20FC.getEmitter() == NULL) {
#endif
                static cXyz fire_scale(0.7f, 0.7f, 0.7f);
#if VERSION == VERSION_DEMO
                i_this->demo_m20FC =
#endif
                    dComIfGp_particle_set(dPa_name::ID_COMMON_01EA, &i_this->m1624, NULL, &fire_scale, 0xff, &i_this->m20FC);
#if VERSION == VERSION_DEMO
                i_this->m2110 = 1;
#endif
                i_this->m1620 = 1.0f;
            }

#if VERSION == VERSION_DEMO
            JPABaseEmitter* pJVar6 = i_this->demo_m20FC;
#else
            JPABaseEmitter* pJVar6 = i_this->m20FC.getEmitter();
#endif
            if (pJVar6 != NULL) {
                f32 fVar3 = DEMO_SELECT(REG0_F(3) + -0.03f, -0.03f);
                f32 fVar1 = (i_this->m1624.x - i_this->m1630.x) * fVar3;
                if (fVar1 > 1.0f) {
                    fVar1 = 1.0f;
                } else if (fVar1 < -1.0f) {
                    fVar1 = -1.0f;
                }

                f32 fVar4 = fVar3 * ((i_this->m1624).z - (i_this->m1630).z);
                if (fVar4 > 1.0f) {
                    fVar4 = 1.0f;
                } else if (fVar4 < -1.0f) {
                    fVar4 = -1.0f;
                }

                JGeometry::TVec3<f32> s;
                s.x = fVar1;
                s.y = 0.1f;
                s.z = fVar4;
                pJVar6->setDirection(s);

                f32 tmp = 1.0f;
                f32 sqrt = std::sqrtf(SQUARE(fVar1) + SQUARE(fVar4));
                f32 sqrt2 = 1.0f + sqrt * DEMO_SELECT(REG0_F(12) + 2.0f, 2.0f);
                if (sqrt2 > DEMO_SELECT(REG0_F(13) + 4.0f, 4.0f)) {
                    sqrt2 = DEMO_SELECT(REG0_F(13) + 4.0f, 4.0f);
                }

                JGeometry::TVec3<f32> s2;
                s2.x = tmp;
                s2.y = sqrt2;
                s2.z = tmp;

#if VERSION == VERSION_DEMO
                pJVar6 = i_this->demo_m20FC;
#endif
                pJVar6->setGlobalParticleScale(s2);
                cLib_addCalc2(&i_this->m1620, cM_rndF(0.2f) + 1.0f, 0.5f, 0.02f);
            } else {
                i_this->m1620 = 0.0f;
            }

            cXyz sp1C(i_this->m1624.x, DEMO_SELECT(i_this->m1624.y + REG0_F(7), i_this->m1624.y) + 20.0f, i_this->m1624.z);
            dComIfGp_particle_setSimple(dPa_name::ID_COMMON_4004, &sp1C);
            i_this->m1600.mPos = i_this->m1624;
            i_this->m1600.mColor.r = 600;
            i_this->m1600.mColor.g = 400;
            i_this->m1600.mColor.b = 0x78;
            i_this->m1600.mPower = (s16)(i_this->m1620 * 150.0f);
            i_this->m1600.mFluctuation = 250.0f;
            ga_move(i_this);
        }
    }
    i_this->m1630 = i_this->m1624;
    return TRUE;
}

/* 00001A3C-00001A44       .text daHimo3_IsDelete__FP11himo3_class */
static BOOL daHimo3_IsDelete(himo3_class* i_this) {
#if VERSION == VERSION_DEMO
    if (i_this->demo_m20FC != 0) {
        i_this->m20FC.remove();
    }
#endif
    return TRUE;
}

/* 00001A44-00001AE0       .text daHimo3_Delete__FP11himo3_class */
static BOOL daHimo3_Delete(himo3_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Himo3");
    if (i_this->m0298 == 0) {
        dKy_plight_cut(&i_this->m1600);
    }

    if (DEMO_SELECT(i_this->m2111, i_this->m2110) != 0) {
        hio_set = false;
        mDoHIO_deleteChild(l_HIO.mNo);
    }

#if VERSION > VERSION_DEMO
    i_this->m20FC.remove();
#endif
    return TRUE;
}

/* 00001AE0-00001DD4       .text useHeapInit__FP11himo3_class */
cPhs_State useHeapInit(himo3_class* i_this) {
    static s32 hook_bmd[] = {HIMO3_BMD_SLAMP_00, LINK_BDL_ROPEEND, HIMO3_BMD_SLAMP_00, HIMO3_BMD_SLAMP_00, HIMO3_BMD_SLAMP_00};

#if VERSION == VERSION_DEMO
    if (!i_this->mLineMat.init(1, 200, (ResTIMG*)dComIfG_getObjectRes("Always", i_this->m0298 == 0xf ? ALWAYS_BTI_TXM_ROPE1 : ALWAYS_BTI_ROPE), 0)) {
        return cPhs_ERROR_e;
    }
#else
    if (i_this->m0298 == 0xf) {
        if (!i_this->mLineMat.init(1, 200, (ResTIMG*)dComIfG_getObjectRes("Bgn", BGN_BTI_NOT_CUT1), 0)) {
            return cPhs_ERROR_e;
        }
    } else if (!i_this->mLineMat.init(1, 200, (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE), 0)) {
        return cPhs_ERROR_e;
    }
#endif

    J3DModelData* modelData = NULL;
    if (i_this->m0298 != 0xf) {
        if (i_this->m0298 == 1) {
            modelData = (J3DModelData*)dComIfG_getObjectRes("Link", hook_bmd[i_this->m0298]);
        } else if (i_this->m0298 <= 4) {
            modelData = (J3DModelData*)dComIfG_getObjectRes("Himo3", hook_bmd[i_this->m0298]);
        }

        JUT_ASSERT(DEMO_SELECT(1250, 1284), modelData != NULL);

        i_this->mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (i_this->mpModel == NULL) {
            return cPhs_ERROR_e;
        }
    }

    if (i_this->m0298 == 0) {
        modelData = (J3DModelData*)dComIfG_getObjectRes("Himo3", HIMO3_BMD_H3_GA);
        JUT_ASSERT(DEMO_SELECT(1264, 1298), modelData != NULL);
        s32 tmp = 0;

        for (s32 i = 0; i < ARRAY_SSIZE(i_this->m2114); i++) {
            i_this->m2114[i].mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
            if (i_this->m2114[i].mpModel == NULL) {
                return cPhs_INIT_e;
            }

            if (tmp == 0 || cM_rndF(1.0f) < 0.5f) {
                i_this->m2114[i].m2E = true;
                i_this->m2114[i].mPos = i_this->current.pos;
                i_this->m2114[i].m24 = cM_rndF(0.3f) + 0.3f;
                i_this->m2114[i].m2C = cM_rndF(30000.0f);
            }
        }
    }
    return cPhs_COMPLEATE_e;
}

/* 00001DD4-00002128       .text daHimo3_Create__FP10fopAc_ac_c */
static cPhs_State daHimo3_Create(fopAc_ac_c* a_this) {
    /* Nonmatching */
    static dCcD_SrcCyl cc_cyl_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 50.0f,
            /* Height */ 4000.0f,
        }},
    };
    static dCcD_SrcSph sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
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
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 50.0f,
        }},
    };
    static dCcD_SrcSph sph2_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 80.0f,
        }},
    };

    himo3_class* i_this = (himo3_class*)a_this;

    fopAcM_SetupActor(a_this, himo3_class);

    cPhs_State PVar1 = dComIfG_resLoad(&i_this->mPhase, "Himo3");
    if (PVar1 == cPhs_COMPLEATE_e) {
        i_this->m0298 = (fopAcM_GetParam(a_this) >> 0) & 0xFF;
        i_this->m0299 = (fopAcM_GetParam(a_this) >> 16) & 0xFF;
        i_this->m029A = (fopAcM_GetParam(a_this) >> 24) & 0xFF;

        if (i_this->m0298 == 0xff) {
            i_this->m0298 = 0;
        }

        if (fopAcM_createHeap(i_this, 0xa220, 0) == 0) {
            return cPhs_ERROR_e;
        }

        PVar1 = useHeapInit(i_this);
        fopAcM_adjustHeap(a_this);

        if (PVar1 == cPhs_ERROR_e) {
            return cPhs_ERROR_e;
        }

        i_this->m15C0 = (fopAcM_GetParam(a_this) >> 8) & 0xFF;
        if (i_this->m0298 == 0xf) {
            HIMO3_SCALE = DEMO_SELECT(REG0_F(4) + 22.0f, 22.0f);
            i_this->m15C0 = DEMO_SELECT(REG0_S(0) + 200, 200);
            i_this->m029A = 0xff;
        } else {
            HIMO3_SCALE = 20.0f;
        }

        i_this->m15FC = i_this->m15C0 * HIMO3_SCALE - 50.0f;
        if (i_this->m0298 == 0) {
            i_this->m15FC -= 50.0f;
        }

        if (i_this->m15C0 > 0xc8) {
            return cPhs_ERROR_e;
        }

        if (i_this->m029A != 0xff) {
            i_this->ppd = dPath_GetRoomPath(i_this->m029A, fopAcM_GetRoomNo(a_this));
            if (i_this->ppd == NULL) {
                return cPhs_ERROR_e;
            }
            i_this->m029B = i_this->m029A + 1;
            i_this->m029D = 1;
        }

        i_this->m15E0 = 1.0f;
        i_this->mStts.Init(0xff, 0xff, i_this);

        if (i_this->m0298 == 0xf) {
            i_this->mCyl.Set(cc_cyl_src);
            i_this->mCyl.SetStts(&i_this->mStts);
        } else {
            for (s32 i = 0; i < ARRAY_SSIZE(i_this->mSphs); i++) {
                i_this->mSphs[i].Set(sph_src);
                i_this->mSphs[i].SetStts(&i_this->mStts);
            }

            i_this->mSph.Set(sph2_src);
            i_this->mSph.SetStts(&i_this->mStts);
            i_this->mAcch.Set(&i_this->m1624, &i_this->m1630, i_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(i_this));

            if (i_this->m0298 == 0) {
                i_this->mAcchCir.SetWall(40.0f, 50.0f);
                i_this->m20F8 = 20.0f;
                dKy_plight_set(&i_this->m1600);
            } else if (i_this->m0298 == 1) {
                i_this->mAcchCir.SetWall(20.0f, 20.0f);
                i_this->mSph.SetR(20.0f);
                i_this->m20F8 = 10.0f;
            }
        }

        if (!hio_set) {
            hio_set = true;
            DEMO_SELECT(i_this->m2111, i_this->m2110) = 0;
            l_HIO.mNo = mDoHIO_createChild("ぶら下がりロープ", &l_HIO);
        }

        for (s32 i = 0; i < 10; i++) {
            daHimo3_Execute(i_this);
        }
    }
    return PVar1;
}

static actor_method_class l_daHimo3_Method = {
    (process_method_func)daHimo3_Create,
    (process_method_func)daHimo3_Delete,
    (process_method_func)daHimo3_Execute,
    (process_method_func)daHimo3_IsDelete,
    (process_method_func)daHimo3_Draw,
};

actor_process_profile_definition g_profile_HIMO3 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0008,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_HIMO3,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(himo3_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_HIMO3,
    /* Actor SubMtd */ &l_daHimo3_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
