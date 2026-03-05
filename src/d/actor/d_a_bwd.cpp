/**
 * d_a_bwd.cpp
 * Boss - Molgera / 風ボス (Wind boss)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bwd.h"
#include "d/actor/d_a_bwds.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_lib.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_snap.h"
#include "d/res/res_bwd.h"
#include "f_op/f_op_camera.h"
#include "m_Do/m_Do_graphic.h"
#include "JSystem/JUtility/JUTReport.h"

class daBwd_HIO_c : public JORReflexible {
public:
    daBwd_HIO_c();
    virtual ~daBwd_HIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ u8 m08;
    /* 0x09 */ u8 m09[0x0C - 0x09];
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ s16 m14;
    /* 0x16 */ u8 m16[0x18 - 0x16];
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ s16 m24;
    /* 0x26 */ s16 m26;
    /* 0x28 */ f32 m28;
    /* 0x2C */ f32 m2C;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ s16 m38;
    /* 0x3A */ s16 m3A;
    /* 0x3C */ s16 m3C;
    /* 0x3E */ s16 m3E;
};

/* 000000EC-0000019C       .text __ct__11daBwd_HIO_cFv */
daBwd_HIO_c::daBwd_HIO_c() {
    mNo = 0xFF;
    m05 = 0;
    m06 = 0;
    m07 = 0;
    m08 = 0;
    m0C = -400.0f;
    m10 = 6.0f;
    m14 = 0x78;
    m18 = 700.0f;
    m1C = 3000.0f;
    m20 = 1.3f;
    m24 = 3;
    m26 = 5;
    m28 = 800.0f;
    m2C = -500.0f;
    m30 = 3.5f;
    m34 = 2.0f;
    m38 = 0x8c;
    m3A = 0x78;
    m3C = 0x50;
    m3E = 0x96;
}

static GXColor eff_col;
static bool hio_set;
static daBwd_HIO_c l_HIO;
static cXyz suna_gr_pos[6] = {
    cXyz(-3791.0f, 0.0f, -467.0f),
    cXyz(2138.0f, 0.0f, -3176.0f),
    cXyz(1655.0f, 0.0f, 3434.0f),
    cXyz(-2405.0f, 0.0f, 2935.0f),
    cXyz(3747.0f, 0.0f, 753.0f),
    cXyz(-1393.0f, 0.0f, -3546.0f)
};
static csXyz suna_gr_ang[6];
static cXyz center_pos(0.0f, 0.0f, 0.0f);
static s32 ko_count;
static fopAc_ac_c* ko_ac[22];
static cXyz set_pos;

/* 0000019C-000001B4       .text g_eff_on__FP9bwd_class */
void g_eff_on(bwd_class* i_this) {
    if (i_this->m3960 != 0) {
        return;
    }
    i_this->m3960 = 1;
}

/* 000001B4-000001CC       .text g_eff_off__FP9bwd_class */
void g_eff_off(bwd_class* i_this) {
    if (i_this->m3960 == 0) {
        return;
    }
    i_this->m3960 = -1;
}

/* 000001CC-00000250       .text ko_s_sub__FPvPv */
void* ko_s_sub(void* param_1, void* param_2) {
    UNUSED(param_2);
    fopAc_ac_c* actor = (fopAc_ac_c*)param_1;

    if ((fopAc_IsActor(actor)) && (fopAcM_GetName(actor) == PROC_BWDS)) {
        if (ko_count < l_HIO.m26) {
            ko_ac[ko_count] = actor;
            ko_count++;
        }
        return FALSE;
    }
    return FALSE;
}

/* 00000250-0000029C       .text ko_delete_sub__FPvPv */
void* ko_delete_sub(void* param_1, void* param_2) {
    UNUSED(param_2);
    bwds_class* actor = (bwds_class*)param_1;

    if ((fopAc_IsActor(actor)) && (fopAcM_GetName(actor) == PROC_BWDS)) {
        actor->m04F4 = 1;
    }
    return FALSE;
}

/* 0000029C-000003C4       .text anm_init__FP9bwd_classifUcfi */
void anm_init(bwd_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    void* pSoundAnimRes;
    J3DAnmTransform* pJVar1;

    if (soundFileIdx >= 0) {
        pSoundAnimRes = dComIfG_getObjectRes("Bwd", soundFileIdx);
        pJVar1 = (J3DAnmTransform*)dComIfG_getObjectRes("Bwd", bckFileIdx);
        i_this->m02C0->setAnm(pJVar1, loopMode, morf, speed, 0.0f, -1.0f, pSoundAnimRes);
    } else {
        pJVar1 = (J3DAnmTransform*)dComIfG_getObjectRes("Bwd", bckFileIdx);
        i_this->m02C0->setAnm(pJVar1, loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 000003C4-00000480       .text gr_draw__FP9bwd_class */
void gr_draw(bwd_class* i_this) {
    cXyz local_18;

    local_18.setall(0.0f);
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &local_18, &i_this->m1714);
    if (i_this->m1865 == 0) {
        dComIfGd_setListBG();
        g_env_light.setLightTevColorType(i_this->m1868, &i_this->m1714);
        mDoExt_modelUpdateDL(i_this->m1868);
        dComIfGd_setList();
    }
}

/* 000004BC-00000564       .text suna_draw__FP9bwd_class */
void suna_draw(bwd_class* i_this) {
    for (s32 i = 0; i < 2; i++) {
        if (i_this->m17E4[i] != 0) {
            g_env_light.setLightTevColorType(i_this->m17EC[i], &i_this->m1714);
            i_this->m17F4[i]->entry(i_this->m17EC[i]->getModelData());
            mDoExt_modelUpdateDL(i_this->m17EC[i]);
            i_this->m17F4[i]->remove(i_this->m17EC[i]->getModelData());
        }
    }
}

/* 00000564-00000760       .text daBwd_Draw__FP9bwd_class */
static BOOL daBwd_Draw(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* pJVar5;

    if (i_this->m3C1C > 1) {
        mDoGph_gInf_c::setBlureRate(i_this->m3C1C);
        mDoGph_gInf_c::onBlure();
    } else if (i_this->m3C1C == 1) {
        i_this->m3C1C = 0;
        mDoGph_gInf_c::offBlure();
    }
    pJVar5 = i_this->m02C0->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->current.pos, &actor->tevStr);
    g_env_light.setLightTevColorType(pJVar5, &actor->tevStr);
    i_this->m02C4->entry(pJVar5->getModelData());
    i_this->m02C0->entryDL();
    if (i_this->m1BB6 < 2) {
        sita_s* psVar3;
        s32 i = 0;
        for (psVar3 = i_this->m1908, i = 0; i < 0x1E; i++, psVar3++) {
            g_env_light.setLightTevColorType(psVar3->m00, &actor->tevStr);
            mDoExt_modelUpdateDL(psVar3->m00);
        }
    }
    if (i_this->m170C != 0) {
        for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m02D4); i++) {
            if (i_this->m02D4[i] != NULL) {
                pJVar5 = i_this->m02D4[i];
                g_env_light.setLightTevColorType(pJVar5, &actor->tevStr);
                i_this->m0374[i]->entry(pJVar5->getModelData());
                mDoExt_modelUpdateDL(pJVar5);
            }
        }
    }
    dSnap_RegistFig(DSNAP_TYPE_BWD, actor, 1.0f, 1.0f, 1.0f);
    gr_draw(i_this);
    suna_draw(i_this);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m3B08); i++) {
        if (i_this->m3B08[i] != 0) {
            i_this->m3B34[i]->entry(i_this->m3B24[i]->getModel()->getModelData());
            i_this->m3B2C[i]->entry(i_this->m3B24[i]->getModel()->getModelData());
            i_this->m3B24[i]->updateDL();
        }
    }
    return TRUE;
}

/* 00000760-00000FBC       .text fly_pos_move__FP9bwd_classss */
void fly_pos_move(bwd_class* i_this, s16 param_2, s16 param_3) {
    /* Nonmatching - sVar1, target */
    fopAc_ac_c* actor = &i_this->actor;
    s16 sVar1;
    f32 fVar2;
    f32 fVar3;
    s16 target;
    int iVar4;
    int iVar5;
    s8 cVar6;
    f32 dVar12;
    cXyz local_ec;
    cXyz cStack_f8;

    fVar2 = i_this->m18B4.x - actor->current.pos.x;
    dVar12 = (i_this->m18B4.y - actor->current.pos.y);
    fVar3 = i_this->m18B4.z - actor->current.pos.z;
    iVar4 = cM_atan2s(fVar2, fVar3);
    fVar2 = std::sqrtf((fVar2 * fVar2) + (fVar3 * fVar3));
    iVar5 = cM_atan2s(dVar12, fVar2);
    sVar1 = actor->current.angle.y;
    cLib_addCalcAngleS2(&actor->current.angle.y, param_3 + iVar4, REG0_S(3) + 10, (i_this->m18C4 * i_this->m18C8));
    sVar1 = (sVar1 - actor->current.angle.y) * 0x20;
    target = REG0_S(1) + 0x157c;
    if (sVar1 > target) {
        iVar4 = -target;
        target = sVar1;
    } else if (sVar1 < iVar4) {
        target = iVar4;
    }
    cLib_addCalcAngleS2(&actor->current.angle.z, target, REG0_S(3) + 10, (i_this->m18C4 * i_this->m18C8 * 0.5f));
    cLib_addCalcAngleS2(&actor->current.angle.x, param_2 - iVar5, REG0_S(3) + 10, (i_this->m18C4 * i_this->m18C8));
    cLib_addCalc2(&i_this->m18C8, 1.0f, 1.0f, 0.04);
    local_ec.x = 0.0f;
    local_ec.y = 0.0f;
    local_ec.z = actor->speedF;
    mDoMtx_YrotS(*calc_mtx, actor->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, actor->current.angle.x);
    MtxPosition(&local_ec, &actor->speed);
    actor->current.pos.x = actor->current.pos.x + actor->speed.x;
    actor->current.pos.y = actor->current.pos.y + actor->speed.y;
    actor->current.pos.z = actor->current.pos.z + actor->speed.z;
    if (i_this->m18FC == 0) {
        dBgS_LinChk local_e0;
        local_ec.x = 0.0f;
        local_ec.y = 0.0f;
        local_ec.z = REG0_F(7) + 700.0f;
        MtxPosition(&local_ec, &cStack_f8);
        cStack_f8 += actor->current.pos;
        local_e0.Set(&actor->current.pos, &cStack_f8, NULL);
        cVar6 = dComIfG_Bgsp()->LineCross(&local_e0);
        local_e0.Set(&cStack_f8, &actor->current.pos, NULL);
        if (dComIfG_Bgsp()->LineCross(&local_e0)) {
            cVar6 = 2;
        }
        if (cVar6 != 0) {
            i_this->m18FC = 0x1e;
            dComIfGp_getVibration().StartShock(REG0_S(2) + 7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            if (i_this->m3C1E != 0) {
                i_this->m3C1C = 0xb4;
            }
            i_this->m3C4C = REG0_F(0x13) + 50.0f;
            if ((cVar6 == 1) && (i_this->m3AE0[0] == 0)) {
                i_this->m3954.x = actor->current.pos.x;
                i_this->m3954.z = actor->current.pos.z;
                i_this->m3C15 = 2;
                i_this->m3C14 = 0x5a;
                i_this->m17C8 = i_this->m3954;
                i_this->m17C4 = 199;
                i_this->m3B08[1] = 1;
                i_this->m3B0C[1] = i_this->m3954;
                dComIfGp_particle_setToon(dPa_name::ID_SCENE_A25A, &i_this->m3954, NULL, NULL, eff_col.a, &i_this->m3978[0], (s8)actor->current.roomNo);
                i_this->m3978[0].setColor(eff_col);
                dComIfGp_particle_set(dPa_name::ID_SCENE_8259, &i_this->m3954, NULL, NULL, eff_col.a, &i_this->m3AB8[0], (s8)actor->current.roomNo);
                mDoAud_seStart(JA_SE_CM_BWD_IN_SAND_1, &i_this->m3954, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                i_this->m3AE0[0] = 0x6e;
            } else if (i_this->m3AE0[1] == 0) {
                i_this->m3954.x = actor->current.pos.x;
                i_this->m3954.z = actor->current.pos.z;
                i_this->m3B08[0] = 1;
                i_this->m3B0C[0] = i_this->m3954;
                ;
                i_this->m3C15 = 2;
                i_this->m3C14 = 0x5a;
                dComIfGp_particle_setToon(dPa_name::ID_SCENE_A258, &i_this->m3954, NULL, NULL, eff_col.a, &i_this->m3978[1], (s8)actor->current.roomNo);
                i_this->m3978[1].setColor(eff_col);
                dComIfGp_particle_set(dPa_name::ID_SCENE_8257, &i_this->m3954, NULL, NULL, eff_col.a, &i_this->m3AB8[1], (s8)actor->current.roomNo);
                mDoAud_seStart(JA_SE_CM_BWD_OUT_SAND_1, &i_this->m3954, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                i_this->m3AE0[1] = 0x6e;
            }
        }
    }
}

/* 000013F4-00001640       .text damage_check__FP9bwd_class */
void damage_check(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 sVar6;
    cCcD_Obj* pcVar5;
    CcAtInfo local_34;

    if (i_this->m18D6 == 0) {
        local_34.pParticlePos = NULL;
#if VERSION == VERSION_USA
        fopAc_ac_c* pfVar2 = fopAcM_SearchByID(i_this->m1BC0);
        if (pfVar2 != NULL) {
            pfVar2->current.pos = actor->eyePos;
        }
#endif
        if (i_this->m1BB1 != 0) {
            i_this->mCcD_Sph.SetTgType(~(AT_TYPE_WATER | AT_TYPE_UNK20000 | AT_TYPE_WIND | AT_TYPE_UNK400000 | AT_TYPE_LIGHT));
        } else {
            i_this->mCcD_Sph.SetTgType(AT_TYPE_HOOKSHOT);
        }
        if (i_this->mCcD_Sph.ChkTgHit()) {
            i_this->m18D6 = 6;
            local_34.mpObj = i_this->mCcD_Sph.GetTgHitObj();
            if (local_34.mpObj != NULL) {
                local_34.pParticlePos = i_this->mCcD_Sph.GetTgHitPosP();
                if (local_34.mpObj->ChkAtType(AT_TYPE_HOOKSHOT)) {
                    i_this->m1BB0 = 1;
                    local_34.mpActor = local_34.mpObj->GetAc();
                    i_this->m1BBC = fopAcM_GetID(local_34.mpActor);
                    i_this->m18AE = 3;
                    i_this->m18B0 = 0;
                    mDoAud_seStart(JA_SE_LK_HS_SPIKE, &actor->eyePos, 0x20, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                } else {
                    if (i_this->m1BB1 != 0) {
                        sVar6 = actor->health;
                        actor->health = 0x14;
                        cc_at_check(actor, &local_34);
                        actor->health = sVar6 + -1;
                        fopAcM_monsSeStart(actor, JA_SE_CV_BWD_DAMAGE, 0);
                        i_this->m1BB4++;
                        i_this->m1BB3 = 0x14;
                    }
                }
            }
        }
        for (s32 i = 0; i < 9; i++) {
            if (i_this->mDamageSpheres[i].ChkTgHit()) {
                pcVar5 = i_this->mDamageSpheres[i].GetTgHitObj();
                def_se_set(actor, pcVar5, 0x40);
                return;
            }
        }
    }
}

/* 0000167C-000018E8       .text start__FP9bwd_class */
void start(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar7;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->m18B0) {
    case 0:
        i_this->m17C4 = 0xC9;
        fVar7 = player->current.pos.abs();
        if (fVar7 < 3200.0f) {
            i_this->m18B0 = 1;
            i_this->m18AC = 0;
            i_this->m3C1E = 0x32;
        }
        break;
    case 1:
        if (i_this->m18AC == 0x3C) {
            i_this->m17E4[0] = 1;
            for (s32 i = 0; i < 3; i++) {
                mDoAud_seStart(JA_SE_OBJ_BWD_SANDFALL_S, &suna_gr_pos[i], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            }
        }
        if (i_this->m18AC == 200) {
            i_this->m17D8 = REG0_S(4) + 500;
        }
        if (i_this->m18AC >= 0xDC) {
            cLib_addCalc2(&i_this->m17E0, 900.0f, 0.1f, REG0_F(0xd) + 0.9f);
        }
        if (i_this->m18AC == 0x28f) {
            i_this->m1865 = 1;
        }
        if (i_this->m18AC >= 600) {
            i_this->m394C = 1;
            if (i_this->m18AC == 0x294) {
                i_this->m18AE = 0xB;
                i_this->m18B0 = 0;
                actor->current.pos.x = 0.0f;
                actor->current.pos.y = ((l_HIO.m28 + -2000.0f) - 200.0f) + REG0_F(0xb);
                actor->current.pos.z = 0.0f;
                i_this->m18CC[1] = 0x28;
                g_eff_on(i_this);
                dComIfGp_getVibration().StopQuake(-1);
            }
        }
        break;
    }
    i_this->m1BB6 = 1;
}

/* 000018E8-00001AEC       .text wait__FP9bwd_class */
void wait(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    i_this->m394C = 1;
    i_this->m17C8 = actor->current.pos;
    i_this->m17C4 = 1;
    actor->current.angle.z = 0;
    actor->current.angle.x = 0;
    if (i_this->m1BB8 > 80.0f) {
        cLib_addCalcAngleS2(&actor->current.angle.y, fopAcM_searchPlayerAngleY(actor), 10, 0x800);
    }
    switch (i_this->m18B0) {
    case -10:
        if (!(player->current.pos.y < 900.0f)) {
            break;
        }
        i_this->m18CC[0] = 0x7a;
        i_this->m18D0 = 0xde;
        i_this->m18B0 = 1;
        break;
    case 0:
        i_this->m18B0++;
    case 1:
        if (i_this->m18CC[0] == 0) {
            anm_init(i_this, BWD_BCK_BWD_WAIT, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m18B0++;
            mDoAud_seStart(JA_SE_CM_BWD_OUT_SAND_2, &i_this->m3954, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        } else {
            if (i_this->m18CC[0] == 0x78) {
                g_eff_on(i_this);
            }
            break;
        }
    case 2:
        cLib_addCalc2(&actor->current.pos.y, l_HIO.m0C + l_HIO.m28, 0.1f, 20.0f);
        if (i_this->m18D0 == 0) {
            if (i_this->m1BB8 < l_HIO.m18) {
                i_this->m18AE = 5;
                i_this->m18B0 = 0;
            } else {
                if (i_this->m1BB8 > l_HIO.m1C) {
                    i_this->m18AE = 2;
                    i_this->m18B0 = 0;
                }
            }
        }
        break;
    }
}

/* 00001AEC-00001CBC       .text reset__FP9bwd_class */
void reset(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar4;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    switch (i_this->m18B0) {
    case 0:
        i_this->m18B0++;
        i_this->m18CC[0] = 0x96;
        // fallthrough
    case 1:
        cLib_addCalc2(&actor->current.pos.y, REG0_F(0x11) + -1500.0f + l_HIO.m28, 1.0f, 10.0f);
        if (i_this->m18CC[0] == 100) {
            g_eff_off(i_this);
        }
        if (i_this->m18CC[0] == 0) {
            i_this->m18AE = 1;
            i_this->m18B0 = 0;
            i_this->m18D0 = 0xde;
            i_this->m18CC[0] = 0x7a;
            actor->current.pos.x = player->current.pos.x + cM_rndFX(300.0f);
            actor->current.pos.y = l_HIO.m28 + -1500.0f;
            actor->current.pos.z = player->current.pos.z + cM_rndFX(300.0f);
            while (true) {
                fVar4 = std::sqrtf(actor->current.pos.x * actor->current.pos.x + actor->current.pos.z * actor->current.pos.z);
                if (fVar4 < REG0_F(0x12) + 3000.0f) {
                    break;
                }
                actor->current.pos.x *= 0.9f;
                actor->current.pos.z *= 0.9f;
            }
        }
        break;
    }
}

/* 00001CBC-000026A4       .text sita_hit__FP9bwd_class */
void sita_hit(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    JPABaseEmitter* pJVar5;
    int iVar6;
    mDoExt_McaMorf* pmVar9;
    int iVar11;
    f32 fVar12;
    csXyz local_40;
    cXyz local_2c;
    cXyz local_38;

    daPy_py_c* player = daPy_getPlayerActorClass();
    iVar6 = (int)i_this->m02C0->getFrame();
    i_this->m17C4 = 200;
    switch (i_this->m18B0) {
    case 0:
        anm_init(i_this, BWD_BCK_BWD_NUKARERU, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m18B0++;
        i_this->m1BAC = 1.0f;
        // fallthrough
    case 1:
        if (!i_this->m02C0->isStop()) {
            break;
        }
        anm_init(i_this, BWD_BCK_BWD_NUKARERU_LOOP, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m18B0++;
        break;
    case 2:
        if (i_this->m1BB1 == 0) {
            i_this->m18AE = 1;
            i_this->m18B0 = 0;
            i_this->m18CC[0] = 0;
            break;
        }
        if (i_this->m1BB4 < 3) {
            break;
        }
        i_this->m1BB5++;
        dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &i_this->m1908[29].m04);
        local_38.z = 2.0f;
        local_38.y = 2.0f;
        local_38.x = 2.0f;
        local_40.z = 0;
        local_40.x = 0;
        local_40.y = fopAcM_searchPlayerAngleY(actor);
        dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &i_this->m1908[29].m04, &local_40, &local_38);
        if ((i_this->m1BB5 >= 4) || (l_HIO.m06 != 0)) {
            fopAcM_monsSeStart(actor, JA_SE_CV_BWD_LAST_HIT, 0);
            i_this->m18AE = 0xc;
            i_this->m18B0 = 0;
            i_this->m1BB2 = 0x32;
            dScnPly_ply_c::nextPauseTimer = 8;
            mDoAud_bgmStop(30);
            i_this->m1710 = 0;
            break;
        }
        dScnPly_ply_c::nextPauseTimer = 4;
        anm_init(i_this, BWD_BCK_BWD_DAMAGE1, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m18B0++;
        i_this->m1BB1 = 0;
        i_this->m1BB4 = 0;
        i_this->m1BB2 = 0x32;
        fopAcM_monsSeStart(actor, JA_SE_CV_BWD_DAMAGE_L, 0);
        break;
    case 3:
        if (!i_this->m02C0->isStop()) {
            break;
        }
        anm_init(i_this, BWD_BCK_BWD_DAMAGE2, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m18B0++;
        i_this->m18CC[0] = 300;
        i_this->m3954.x = actor->current.pos.x;
        i_this->m3954.z = actor->current.pos.z;
        dComIfGp_particle_set(dPa_name::ID_SCENE_8253, &i_this->m3954, &actor->shape_angle);
        pJVar5 = dComIfGp_particle_set(dPa_name::ID_SCENE_8252, &i_this->m3954);
        i_this->m3964 = pJVar5;
        dComIfGp_particle_set(dPa_name::ID_SCENE_8254, &i_this->m3954, &actor->shape_angle);
        dComIfGp_particle_set(dPa_name::ID_SCENE_8255, &i_this->m3954, &actor->shape_angle);
        if (i_this->m3AE4 == 0) {
            i_this->m3AE4 = 0x4d;
            i_this->m3954.x = actor->current.pos.x;
            i_this->m3954.z = actor->current.pos.z;
            dComIfGp_particle_setToon(
                dPa_name::ID_SCENE_A256, &i_this->m3954, &actor->shape_angle, NULL, eff_col.a, &i_this->m3978[2], (s8)actor->current.roomNo
            );
            i_this->m3978[2].setColor(eff_col);
        }
        // fallthrough
    case 4:
        pJVar5 = i_this->m3964;
        if (pJVar5 != NULL) {
            pmVar9 = i_this->m02C0;
            if (pmVar9->isStop()) {
                pJVar5->becomeInvalidEmitter();
                i_this->m3964 = NULL;
            } else {
                pJVar5->setGlobalRTMatrix(pmVar9->getModel()->getAnmMtx(0xe));
            }
        }
        i_this->m1BB6 = 1;
        iVar11 = (int)i_this->m02C0->getFrame();
        if (iVar11 == 0x32) {
            g_eff_off(i_this);
        }
        if (iVar6 == 0x30) {
            mDoAud_seStart(JA_SE_CM_BWD_IN_SAND_3, &i_this->m3954, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (((((iVar6 == 0x30) && (l_HIO.m24 >= 1)) || ((iVar6 == 0x31) && (l_HIO.m24 >= 2)) || (iVar6 == 0x32 && (l_HIO.m24 >= 3))) ||
             (iVar6 == 0x33 && (l_HIO.m24 >= 4))) &&
            (ko_count < l_HIO.m26))
        {
            local_2c = i_this->m1908[0].m04;
            local_2c.y = REG0_F(9) + -600.0f + l_HIO.m28;
            fopAcM_create(PROC_BWDS, 0x23, &local_2c, fopAcM_GetRoomNo(actor));
            if (i_this->m1710 == 0) {
                if (dComIfGp_getStartStageName()[0] == 'X') {
                    mDoAud_bgmStart(JA_BGM_UNK_152);
                } else {
                    mDoAud_bgmStart(JA_BGM_UNK_124);
                }
                i_this->m1710 = 10;
            }
        }
        if (i_this->m18CC[0] == 0) {
            if ((i_this->m1BB5 >= 2) || (l_HIO.m07 != 0)) {
                i_this->m18AE = 10;
                i_this->m18B0 = 0;
                fVar12 = cM_rndFX(300.0f);
                actor->current.pos.x = player->current.pos.x + fVar12;
                actor->current.pos.y = l_HIO.m28 + -2000.0f;
                fVar12 = cM_rndFX(300.0f);
                actor->current.pos.z = player->current.pos.z + fVar12;
                while (true) {
                    fVar12 = std::sqrtf(actor->current.pos.x * actor->current.pos.x + actor->current.pos.z * actor->current.pos.z);
                    if (fVar12 < REG0_F(0x12) + 3000.0f) {
                        break;
                    }
                    actor->current.pos.x *= 0.9f;
                    actor->current.pos.z *= 0.9f;
                }
                i_this->m18CC[1] = 0x28;
                for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m0508); i++) {
                    i_this->m0508[i] = actor->current.pos;
                }
                g_eff_on(i_this);
            } else {
                i_this->m18AE = 1;
                i_this->m18B0 = 0;
                i_this->m18D0 = 0xde;
                i_this->m18CC[0] = 0x7a;
                fVar12 = cM_rndFX(300.0f);
                actor->current.pos.x = player->current.pos.x + fVar12;
                actor->current.pos.y = l_HIO.m28 + -1500.0f;
                fVar12 = cM_rndFX(300.0f);
                actor->current.pos.z = player->current.pos.z + fVar12;
                while (true) {
                    fVar12 = std::sqrtf(actor->current.pos.x * actor->current.pos.x + actor->current.pos.z * actor->current.pos.z);
                    if (fVar12 < REG0_F(0x12) + 3000.0f) {
                        break;
                    }
                    actor->current.pos.x *= 0.9f;
                    actor->current.pos.z *= 0.9f;
                }
            }
        }
        break;
    }
}

/* 000026A4-00002F30       .text eat_attack__FP9bwd_class */
void eat_attack(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    s8 bVar2;
    s16 sVar6;
    int iVar8;
    s8 cVar10;
    cXyz local_38;

    daPy_py_c* player = daPy_getPlayerActorClass();
    cVar10 = 0;
    i_this->m17C8 = actor->current.pos;
    i_this->m17C4 = 1;
    if ((i_this->m3C1E == 0) && (i_this->m1BB8 > 80.0f)) {
        sVar6 = fopAcM_searchPlayerAngleY(actor);
        cLib_addCalcAngleS2(&actor->current.angle.y, sVar6, 10, 0x800);
    }
    i_this->m18D6 = 5;
    i_this->m1BB6 = 1;
    bVar2 = false;
    switch (i_this->m18B0) {
    case 0:
        anm_init(i_this, BWD_BCK_BWD_ATTACK, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m18B0++;
        i_this->m3954.x = actor->current.pos.x;
        i_this->m3954.z = actor->current.pos.z;
        dComIfGp_particle_set(dPa_name::ID_SCENE_824E, &i_this->m3954, &actor->shape_angle);
        mDoAud_seStart(JA_SE_CV_BWD_ATTACK, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        break;
    case 1:
        fVar1 = i_this->m02C0->getFrame();
        if (fVar1 >= 27.0f) {
            if (((int)fVar1 == 0x1b) && (i_this->m3AE6 == 0)) {
                i_this->m3AE6 = REG0_S(4) + 10;
                i_this->m3978[3].remove();
                i_this->m3954.x = actor->current.pos.x;
                i_this->m3954.z = actor->current.pos.z;
                dComIfGp_particle_setToon(
                    dPa_name::ID_SCENE_A24F, &i_this->m3954, &actor->shape_angle, NULL, eff_col.a, &i_this->m3978[3], (s8)actor->current.roomNo
                );
                i_this->m3978[3].setColor(eff_col);
            }
            for (s32 i = 0; i < 9; i++) {
                if (i_this->mDamageSpheres[i].ChkAtHit()) {
                    bVar2 = true;
                    break;
                }
            }
            if (i_this->m1BB8 < REG0_F(2) + 150.0f) {
                bVar2 = true;
            }
        }
        if (bVar2) {
            anm_init(i_this, BWD_BCK_BWD_ATTACK_EAT, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m18B0 = 5;
            i_this->m18CC[0] = 0x96;
            i_this->m3C1E++;
            i_this->m3954.x = actor->current.pos.x;
            i_this->m3954.z = actor->current.pos.z;
            dComIfGp_particle_set(dPa_name::ID_SCENE_8250, &i_this->m3954, &actor->shape_angle);
            if (i_this->m3AE8 == 0) {
                i_this->m3AE8 = 0x3c;
                i_this->m3978[4].remove();
                i_this->m3954.x = actor->current.pos.x;
                i_this->m3954.z = actor->current.pos.z;
                dComIfGp_particle_setToon(
                    dPa_name::ID_SCENE_A251, &i_this->m3954, &actor->shape_angle, NULL, eff_col.a, &i_this->m3978[4], (s8)actor->current.roomNo
                );
                i_this->m3978[4].setColor(eff_col);
            }
            mDoAud_seStart(JA_SE_CM_BWD_MOUTH_CLOSE_2, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        } else {
            if (i_this->m02C0->isStop()) {
                anm_init(i_this, BWD_BCK_BWD_ATTACK_SHIPPAI, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                mDoAud_seStart(JA_SE_CM_BWD_MOUTH_CLOSE_2, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                i_this->m18B0++;
            }
        }
        break;
    case 2:
        if (i_this->m02C0->isStop()) {
            cVar10 = 1;
        }
        break;
    case 3:
        break;
    case 4:
        break;
    case 5:
        if ((int)i_this->m02C0->getFrame() == 10) {
            mDoAud_seStart(JA_SE_CM_BWD_HEAD_BACK_1, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if ((int)i_this->m02C0->getFrame() == 30) {
            mDoAud_seStart(JA_SE_CM_BWD_IN_SAND_2, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if ((int)i_this->m02C0->getFrame() == 50) {
            g_eff_off(i_this);
        }
        if (i_this->m18CC[0] == 0x3c) {
            local_38 = i_this->m1908[0].m04;
            local_38.y = i_this->m3954.y + REG0_F(9);
            iVar8 = player->setThrowDamage(&local_38, actor->shape_angle.y, (REG0_F(7) + 60.0f), (REG0_F(8) + 130.0f), 0);
            if (iVar8 == 1) {
                i_this->m3C1E++;
                i_this->m3C20 = 0;
                if (i_this->m3AEA == 0) {
                    i_this->m3AEA = 0x14;
                    i_this->m3978[5].remove();
                    i_this->m3954.x = actor->current.pos.x;
                    i_this->m3954.z = actor->current.pos.z;
                    dComIfGp_particle_setToon(dPa_name::ID_SCENE_A24A, &i_this->m3954, NULL, NULL, eff_col.a, &i_this->m3978[5], (s8)actor->current.roomNo);
                    i_this->m3978[5].setColor(eff_col);
                }
                dComIfGp_particle_set(dPa_name::ID_SCENE_8249, &player->current.pos);
                mDoAud_seStart(JA_SE_CM_BWD_SPIT_OUT, &i_this->m3954, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            } else {
                local_38 = i_this->m1908[0].m04;
                local_38.y = REG0_F(9) + -450.0f + l_HIO.m28;
                player->setPlayerPosAndAngle(&local_38, player->shape_angle.y);
                i_this->m3C1E = 0x96;
            }
        }
        if (i_this->m18CC[0] == 0) {
            cVar10 = 2;
        }
        break;
    }
    if (cVar10 != 0) {
        i_this->m18AE = 1;
        i_this->m18B0 = 0;
        if (cVar10 == 1) {
            i_this->m18D0 = 100;
        } else {
            i_this->m18CC[0] = 0x7a;
            i_this->m18D0 = 0xde;
        }
    }
}

/* 00002F30-00003694       .text fly__FP9bwd_class */
void fly(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 dVar7;
    f32 dVar8;
    f32 fVar9;
    cXyz local_48;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (actor->current.pos.y > 1000.0f) {
        i_this->m3C50 = 2;
    }
    switch (i_this->m18B0) {
    case 0:
        if (i_this->m18CC[1] == 0) {
            anm_init(i_this, BWD_BCK_BWD_FLY, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m18B0 = 1;
            i_this->m18B4.x = actor->current.pos.x;
            i_this->m18B4.y = l_HIO.m28 + (cM_rndFX(800.0f) + 2000.0f);
            i_this->m18B4.z = actor->current.pos.z;
            actor->current.angle.x = -0x4000;
            i_this->m18CC[1] = REG0_F(0x12) + (cM_rndF(50.0f) + 200.0f);
            i_this->m1904 = REG0_S(0) + 5;
            i_this->m18D0 = REG0_S(4) + 0xb4;
        } else {
            i_this->m17C8 = i_this->m3954;
            i_this->m17C4 = 0xff;
            break;
        }
    case 1:
        mDoAud_seStart(JA_SE_CM_BWD_FLYING, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        if ((int)i_this->m02C0->getFrame() == 2) {
            mDoAud_seStart(JA_SE_CM_BWD_MOUTH_CLOSE_1, &actor->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if ((int)i_this->m02C0->getFrame() == 0x14) {
            mDoAud_seStart(JA_SE_CV_BWD_FLYING, &actor->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->m18D0 == 0x50) {
            g_eff_off(i_this);
        }
        if (actor->current.pos.y < i_this->m3954.y) {
            i_this->m17C8 = i_this->m3954;
            i_this->m17C4 = 0xff;
        } else {
            if (i_this->m18D0 == 0) {
                i_this->m17C4 = 200;
            }
        }
        local_48 = i_this->m18B4 - actor->current.pos;
        if ((local_48.abs() < REG0_F(0xe) + 500.0f) || (i_this->m18CC[0] == 0)) {
            i_this->m18CC[0] = 100;
            i_this->m18B4.x = cM_rndFX(REG0_F(0x10) + 1500.0f);
            i_this->m18B4.y = l_HIO.m28 + (REG0_F(0xf) + 2000.0f + cM_rndFX(800.0f));
            i_this->m18B4.z = cM_rndFX(REG0_F(0x10) + 1500.0f);
            i_this->m18C8 = 0.0f;
        }
        i_this->m18C4 = REG0_F(0x12) + 500.0f;
        actor->speedF = REG0_F(0x11) + 40.0f;
        if (i_this->m18CC[1] == 0) {
            i_this->m18B0 = 2;
            i_this->m18CC[0] = 0x96;
            anm_init(i_this, BWD_BCK_BWD_JATTACK1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            mDoAud_seStart(JA_SE_CV_BWD_GO_UNDER_G, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        break;
    case 2:
        mDoAud_seStart(JA_SE_CM_BWD_FLYING, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        if (i_this->m02C0->isStop()) {
            anm_init(i_this, BWD_BCK_BWD_JATTACK2, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        i_this->m18B4 = player->eyePos;
        local_48 = i_this->m18B4 - actor->current.pos;
        if ((local_48.abs() < REG0_F(0xe) + 1000.0f) || (i_this->m18CC[0] == 0)) {
            i_this->m18B0 = 3;
            i_this->m18B4.y -= 10000.0f;
            i_this->m18CC[0] = 200;
            anm_init(i_this, BWD_BCK_BWD_JATTACK3, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        cLib_addCalc2(&i_this->m18C4, REG0_F(0xf) + 800.0f, 1.0f, 10.0f);
        break;
    case 3:
        mDoAud_seStart(JA_SE_CM_BWD_FLYING, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        cLib_addCalc2(&i_this->m18C4, REG0_F(0xc) + 1200.0f, 1.0f, 20.0f);
        if (i_this->m18CC[0] == 0) {
            i_this->m18AE = 1;
            i_this->m18B0 = 0;
            i_this->m18CC[0] = 0x7a;
            i_this->m18D0 = 0xde;
            dVar7 = cM_rndFX(1500.0f);
            dVar8 = (REG0_F(0x11) + -1500.0f + l_HIO.m28);
            fVar9 = cM_rndFX(1500.0f);
            actor->current.pos.x = fVar9;
            actor->current.pos.y = dVar8;
            actor->current.pos.z = dVar7;
        }
        break;
    }
    fly_pos_move(i_this, 0, 0);
    i_this->m170C = 1;
    i_this->m1BB6 = 2;
}

/* 00003694-00003D3C       .text s_fly__FP9bwd_class */
void s_fly(bwd_class* i_this) {
    static f32 target_x[] = {-1500.0f, 1500.0f, 0.0f};
    static f32 target_y[] = {3500.0f, 3000.0f, 4000.0f};
    static f32 target_z[] = {-1500.0f, 1500.0f, 0.0f};
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar6;
    cXyz local_28;

    switch (i_this->m18B0) {
    case 0:
        if (i_this->m18CC[1] == 0) {
            anm_init(i_this, BWD_BCK_BWD_FLY, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m18B0 = 1;
            i_this->m18B4.x = 0.0f;
            i_this->m18B4.y = l_HIO.m28 + 3000.0f;
            i_this->m18B4.z = 0.0f;
            actor->current.angle.x = -0x4000;
            i_this->m18D0 = REG0_S(4) + 0xb4;
            i_this->m1904 = REG0_S(0) + 5;
        } else {
            i_this->m17C8 = i_this->m3954;
            i_this->m17C4 = 0xff;
            break;
        }
    case 1:
        mDoAud_seStart(JA_SE_CM_BWD_FLYING, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        if ((int)i_this->m02C0->getFrame() == 2) {
            mDoAud_seStart(JA_SE_CM_BWD_MOUTH_CLOSE_1, &actor->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if ((int)i_this->m02C0->getFrame() == 20) {
            mDoAud_seStart(JA_SE_CV_BWD_FLYING, &actor->current.pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->m18D0 == 0x50) {
            g_eff_off(i_this);
        }
        if (actor->current.pos.y < i_this->m3954.y) {
            i_this->m17C8 = i_this->m3954;
            i_this->m17C4 = 0xff;
        } else {
            if (i_this->m18D0 == 0) {
                i_this->m17C4 = 200;
            }
        }
        local_28 = i_this->m18B4 - actor->current.pos;
        if (local_28.abs() < REG0_F(0xe) + 500.0f) {
            if (i_this->m3C24 == 3) {
                i_this->m18B0 = 2;
                i_this->m18CC[0] = 0x96;
                anm_init(i_this, BWD_BCK_BWD_JATTACK1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                mDoAud_seStart(JA_SE_CV_BWD_GO_UNDER_G, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            } else {
                i_this->m18B4.x = target_x[i_this->m3C24];
                i_this->m18B4.y = target_y[i_this->m3C24];
                i_this->m18B4.z = target_z[i_this->m3C24];
                i_this->m18C8 = 0.0f;
                i_this->m3C24++;
            }
        }
        i_this->m18C4 = REG0_F(0x12) + 500.0f;
        actor->speedF = REG0_F(0x11) + 40.0f;
        break;
    case 2:
        mDoAud_seStart(JA_SE_CM_BWD_FLYING, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        if (i_this->m02C0->isStop()) {
            anm_init(i_this, BWD_BCK_BWD_JATTACK2, 2.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        }
        i_this->m18B4.x = 0.0f;
        i_this->m18B4.y = 800.0f;
        i_this->m18B4.z = 0.0f;
        local_28 = i_this->m18B4 - actor->current.pos;
        if (local_28.abs() < REG0_F(0xe) + 1000.0f) {
            i_this->m18B0 = 3;
            i_this->m18B4.y -= 10000.0f;
            i_this->m18CC[0] = 200;
            anm_init(i_this, BWD_BCK_BWD_JATTACK3, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        }
        cLib_addCalc2(&i_this->m18C4, REG0_F(0xf) + 800.0f, 1.0f, 10.0f);
        break;
    case 3:
        mDoAud_seStart(JA_SE_CM_BWD_FLYING, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        cLib_addCalc2(&i_this->m18C4, REG0_F(0xc) + 1200.0f, 1.0f, 20.0f);
        if (i_this->m18CC[0] == 0) {
            i_this->m18AE = 1;
            i_this->m18B0 = 0;
            i_this->m18CC[0] = 0xac;
            i_this->m18D0 = 0x12e;
            fVar6 = REG0_F(0x11) + -1500.0f + l_HIO.m28;
            actor->current.pos.x = 0.0f;
            actor->current.pos.y = fVar6;
            actor->current.pos.z = 0.0f;
        }
        break;
    }
    fly_pos_move(i_this, 0, 0);
    i_this->m170C = 1;
    i_this->m1BB6 = 2;
}

/* 00003D3C-00004ABC       .text end__FP9bwd_class */
void end(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    bool bVar2;
    mDoExt_McaMorf* pmVar7;
    JPABaseEmitter* pJVar8;
    s16 uVar9;
    s16 uVar10;
    f32 fVar13;
    cXyz local_b4;
    cXyz local_c0;

    bVar2 = true;
    dBgS_GndChk local_a8;
    Vec pos;
    pos = actor->current.pos;
    pos.y += REG0_F(0xd) + 1000.0f;
    local_a8.SetPos(&pos);
    fVar13 = dComIfG_Bgsp()->GroundCross(&local_a8);
    if (fVar13 != -G_CM3D_F_INF) {
        i_this->m18DC = fVar13;
    }
    uVar9 = 0;
    uVar10 = 0;
    switch (i_this->m18B0) {
    case 0:
        if (dComIfGp_getStartStageName()[0] == 'X') {
            dLib_setNextStageBySclsNum(0, actor->current.roomNo);
            mDoAud_seStart(JA_SE_LK_B_BOSS_WARP, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            dComIfGs_onEventBit(dSv_event_flag_c::MOLGERA_TRIALS_CLEAR);
            dComIfGs_onTmpBit(dSv_event_tmp_flag_c::UNK_0480);
            return;
        }
#if VERSION != VERSION_USA
        mDoAud_bgmStreamPrepare(JA_STRM_BWD_CLEAR);
#endif
        anm_init(i_this, BWD_BCK_BWD_DEAD1, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m18B0 = 1;
        i_this->m3C1E = 100;
        actor->current.angle.y = 0;
        fpcM_Search(ko_delete_sub, i_this);
        if (i_this->m3AEC == 0) {
            i_this->m3AEC = 0x28;
            i_this->m3978[6].remove();
            i_this->m3954.x = actor->current.pos.x;
            i_this->m3954.z = actor->current.pos.z;
            dComIfGp_particle_setToon(
                dPa_name::ID_SCENE_A267, &i_this->m3954, &actor->shape_angle, NULL, eff_col.a, &i_this->m3978[6], (s8)actor->current.roomNo
            );
            i_this->m3978[6].setColor(eff_col);
        }
        dComIfGp_particle_set(dPa_name::ID_SCENE_8265, &i_this->m3954, &actor->shape_angle);
        pJVar8 = dComIfGp_particle_set(dPa_name::ID_SCENE_8266, &i_this->m3954);
        i_this->m3968 = pJVar8;
        i_this->m3C24 = 0;
        mDoAud_seStart(JA_SE_CM_BWD_LAST_HEAD_BACK, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
    case 1:
        pJVar8 = i_this->m3968;
        if (pJVar8 != NULL) {
            pmVar7 = i_this->m02C0;
            if (i_this->m02C0->isStop()) {
                pJVar8->becomeInvalidEmitter();
                i_this->m3968 = NULL;
            } else {
                pJVar8->setGlobalRTMatrix(pmVar7->getModel()->getAnmMtx(0xe));
            }
        }
        if ((int)i_this->m02C0->getFrame() == 30) {
            mDoAud_seStart(JA_SE_CM_BWD_LAST_IN_SAND, &i_this->m3954, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if ((int)i_this->m02C0->getFrame() == 50) {
            g_eff_off(i_this);
        }
        bVar2 = false;
        i_this->m1BB6 = 1;
        if (i_this->m02C0->isStop()) {
#if VERSION == VERSION_USA
            mDoAud_bgmStreamPrepare(JA_STRM_BWD_CLEAR);
#endif
            anm_init(i_this, BWD_BCK_BWD_DEAD2, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            actor->current.pos.y = -2000.0f;
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m0508); i++) {
                i_this->m0508[i] = actor->current.pos;
            }
            i_this->m18B0 = 2;
            i_this->m18B4.x = 0.0f;
            i_this->m18B4.y = l_HIO.m28 + 1500.0f;
            i_this->m18B4.z = 0.0f;
            actor->current.angle.x = -0x4000;
            i_this->m18CC[1] = REG0_S(9) + 0xb4;
            i_this->m1904 = REG0_S(1) + 3;
        }
        break;
    case 2:
        i_this->m1BB6 = 2;
        local_b4 = i_this->m18B4 - actor->current.pos;
        fVar13 = local_b4.abs();
        if ((fVar13 < REG0_F(0xe) + 500.0f) || (i_this->m18CC[0] == 0)) {
            i_this->m18CC[0] = (s16)(int)cM_rndF(20.0f);
            i_this->m18B4.x = cM_rndFX(REG0_F(0x10) + 1600.0f);
            i_this->m18B4.y = l_HIO.m28 + (REG0_F(0xf) + 2000.0f + cM_rndFX(500.0f));
            i_this->m18B4.z = cM_rndFX(REG0_F(0x10) + 1600.0f);
        }
        i_this->m18C4 = REG0_F(0x12) + 1000.0f;
        actor->speedF = REG0_F(0x11) + 65.0f;
        if (i_this->m3C20 == 0x96) {
            mDoAud_seStart(JA_SE_CV_BWD_DIE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->m3C20 > 0x96) {
            mDoAud_seStart(JA_SE_CM_BWD_FLYING, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if (i_this->m18CC[1] == 0) {
            i_this->m18B0 = 0x17;
            i_this->m18CC[0] = 0x3c;
            i_this->m18CC[1] = 0x5a;
            i_this->m3C1E = 0x66;
            i_this->m3C20 = 0;
            i_this->m3C44 = 0.0f;
            actor->speedF = 0.0f;
            i_this->m18C4 = 0.0f;
            mDoAud_seStart(JA_SE_CM_BWD_HARDEN, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            mDoAud_bgmStreamPlay();
        }
        i_this->m18FE += REG0_S(5) + 0xc1c;
        i_this->m1900 += REG0_S(5) + 0xdac;
        uVar9 = ((REG0_F(0xd) + 7000.0f) * cM_ssin(i_this->m18FE));
        uVar10 = ((REG0_F(0xd) + 7000.0f) * cM_scos(i_this->m1900));
        break;
    case 23:
        i_this->m1BB6 = 2;
        if (i_this->m18CC[0] == 0x14) {
            anm_init(i_this, BWD_BCK_BWD_DEAD3, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m02C8 = 1.0f;
        }
        if (((i_this->m18CC[0] == 0) && ((i_this->m18AC & 3U) == 0)) && (i_this->m0414 < 0x14)) {
            i_this->m03C4[i_this->m0414] = 1.0f;
            i_this->m0414++;
        }
        if (((i_this->m18CC[1] == 0) && ((i_this->m18AC & 3U) == 0)) && (i_this->m3C24 < 0x14)) {
            if (i_this->m3C24 == 0x13) {
                i_this->m18B0 = 3;
                i_this->m18CC[0] = 0;
                mDoAud_seStart(JA_SE_CM_BWD_LAST_EXPLODE, &actor->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            } else {
                i_this->m3C24++;
            }
        }
        break;
    case 3:
        i_this->m1BB6 = 2;
        if (i_this->m18CC[0] == 0) {
            i_this->m18CC[0] = 2;
            local_c0.x = 2.0f;
            local_c0.y = 2.0f;
            local_c0.z = 2.0f;
            csXyz local_d4(0, 0, 0);
            local_d4.x = (s16)(int)cM_rndF(65536.0f);
            local_d4.y = (s16)(int)cM_rndF(65536.0f);
            dComIfGp_particle_set(dPa_name::ID_SCENE_825D, i_this->m0418 + i_this->m3C24, &local_d4, &local_c0);
            dComIfGp_particle_set(dPa_name::ID_SCENE_825E, i_this->m0418 + i_this->m3C24, &local_d4, &local_c0);
            mDoAud_seStart(JA_SE_CM_MONS_EXPLODE, i_this->m0418 + i_this->m3C24, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
            i_this->m02D4[i_this->m3C24] = NULL;
            if (i_this->m3C24 == 0) {
                i_this->m18B0 = 4;
                i_this->m18CC[0] = 10;
            } else {
                i_this->m3C24--;
            }
        }
        break;
    case 4:
        bVar2 = false;
        i_this->m1BB6 = 2;
        if (i_this->m18CC[0] == 0) {
            fopAcM_createDisappear(actor, &actor->current.pos, 0x32, daDisItem_NONE1_e, 0xff);
            i_this->m18E4 = actor->current.pos;
            actor->current.pos.y = -20000.0f;
            i_this->m1B88.y = -20000.0f;
            i_this->m3C1E = 0x68;
            i_this->m3C20 = 0;
            i_this->m18B0 = 5;
        }
        break;
    case 5:
        bVar2 = false;
        i_this->m1BB6 = 2;
        break;
    }
    if (bVar2) {
        fly_pos_move(i_this, uVar9, uVar10);
        i_this->m170C = 1;
    }
}

/* 00004C54-0000527C       .text control1__FP9bwd_class */
void control1(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 dVar8;
    f32 dVar10;
    cXyz local_104;
    cXyz local_110;
    cXyz local_11c;
    cXyz local_128;

    MTXCopy(i_this->m02C0->getModel()->getAnmMtx(0x1d), *calc_mtx);
    local_104.x = REG0_F(2) + -50.0f;
    local_104.y = REG0_F(3);
    local_104.z = REG0_F(4);
    MtxPosition(&local_104, &i_this->m1908[0].m04);
    s32 i = 1;
    sita_s* psVar5 = &i_this->m1908[i];
    mDoMtx_YrotS(*calc_mtx, (int)actor->current.angle.y);
    mDoMtx_XrotM(*calc_mtx, actor->current.angle.x);
    local_104.x = 0.0f;
    local_104.y = 0.0f;
    local_104.z = i_this->m1BA4;
    MtxPosition(&local_104, &local_11c);
    local_104.z = i_this->m1BA0;
    f32 dVar9 = i_this->m1BA8;
    local_128.setall(0.0f);
    dBgS_GndChk local_f8;
    for (i = 1; i < 0x1d; i++, ++psVar5) {
        if (i_this->m1BB0 == 0) {
            if (i_this->m1BB3 != 0) {
                dVar9 = i_this->m1BB3 * (REG0_F(3) + 4.5f);
                local_110.x = dVar9 * cM_ssin(i_this->m18AC * (REG0_S(5) + 0x1fa4) + i * (REG0_S(6) + 0xa28));
                local_110.y = (dVar9 * cM_scos(i_this->m18AC * (REG0_S(5) + 0x2198) + i * (REG0_S(6) + 0x898)));
                local_110.z = dVar9 * cM_scos(i_this->m18AC * (REG0_S(5) + 0x206c) + i * (REG0_S(6) + 0x960));
            } else {
                local_110.x = dVar9 * cM_ssin(i_this->m18AC * (REG0_S(5) + 0x44c) + i * (REG0_S(6) + 2000));
                if (i_this->m1BB1 != 0) {
                    local_110.y = -5.0f;
                } else {
                    local_110.y = REG0_F(5) + 5.0f;
                }
                local_110.z = dVar9 * cM_scos(i_this->m18AC * (REG0_S(7) + 900) + i * (REG0_S(8) + 2000));
            }
            MtxPosition(&local_110, &local_128);
        }
        dVar10 = (local_128.y + (psVar5->m04.y + local_11c.y));
        if (local_110.y < 0.0f) {
            Vec pos;
            pos = psVar5->m04;
            pos.y += 200.0f;
            local_f8.SetPos(&pos);
            dVar8 = (REG0_F(0x10) + dComIfG_Bgsp()->GroundCross(&local_f8) + 30.0f);
            if (dVar10 <= dVar8) {
                dVar10 = dVar8;
            }
        }
        f32 x = local_128.x + (local_11c.x + (psVar5->m04.x - psVar5[-1].m04.x));
        f32 y = (dVar10 - psVar5[-1].m04.y);
        f32 z = local_128.z + (local_11c.z + (psVar5->m04.z - psVar5[-1].m04.z));
        s16 iVar3;
        int iVar2 = cM_atan2s(x, z);
        iVar3 = -cM_atan2s(y, std::sqrtf((x * x) + (z * z)));
        MtxPush();
        mDoMtx_YrotS(*calc_mtx, iVar2);
        mDoMtx_XrotM(*calc_mtx, iVar3);
        MtxPosition(&local_104, &local_110);
        MtxPull();
        psVar5->m04 = psVar5[-1].m04 + local_110;
    }
}

/* 0000527C-00005438       .text control2__FP9bwd_class */
void control2(bwd_class* i_this) {
    cXyz rel_offset, abs_offset;
    rel_offset.x = 0;
    rel_offset.y = 0;
    rel_offset.z = i_this->m1BA0;
    i_this->m1908[29].m04 = i_this->m1B88;

    int i = 28;
    s16 Yangle;
    int XZangle;
    sita_s* sita_i = &i_this->m1908[i];
    for (i = 28; i >= 1; i--, sita_i--) {
        f32 delta_pos_x = sita_i->m04.x - sita_i[1].m04.x;
        f32 delta_pos_y = sita_i->m04.y - sita_i[1].m04.y;
        f32 delta_pos_z = sita_i->m04.z - sita_i[1].m04.z;
        XZangle = cM_atan2s(delta_pos_x, delta_pos_z);
        Yangle = -cM_atan2s(delta_pos_y, std::sqrtf(delta_pos_x * delta_pos_x + delta_pos_z * delta_pos_z));
        mDoMtx_YrotS(*calc_mtx, XZangle);
        mDoMtx_XrotM(*calc_mtx, Yangle);
        MtxPosition(&rel_offset, &abs_offset);
        sita_i->m04 = sita_i[1].m04 + abs_offset;
    }
}

/* 00005438-00005D78       .text sita_move__FP9bwd_class */
void sita_move(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    fopAc_ac_c* pfVar2;
    f32 dVar7;
    f32 dVar8;
    f32 dVar9;
    f32 fVar10;
    cXyz local_c8;
    cXyz local_d4;
    cXyz local_f8;

    if (i_this->m1BB3 != 0) {
        i_this->m1BB3--;
    }
    local_c8.x = (REG0_F(0xd) + 100.0f) * cM_ssin(i_this->m18AC * (REG0_S(5) + 0x44c));
    local_c8.y = REG0_F(0) + 600.0f + (REG0_F(0xe) + 50.0f) * cM_ssin(i_this->m18AC * (REG0_S(4) + 700));
    local_c8.z = (REG0_F(0xd) + 100.0f) * cM_ssin(i_this->m18AC * (REG0_S(7) + 900));
    local_f8 = i_this->m1908[0].m04 + local_c8;
    if (i_this->m1B88.y < i_this->m3954.y) {
        fopAcM_OffStatus(actor, 0);
        actor->attention_info.flags = 0;
    }
    dVar8 = 0.1f;
    dVar9 = ((REG0_F(7) + 100.0f) * i_this->m1BAC);
    if (i_this->m1BB0 != 0) {
        pfVar2 = fopAcM_SearchByID(i_this->m1BBC);
        if ((pfVar2 == NULL) || (!daPy_getPlayerLinkActorClass()->checkHookshotReturn())) {
            i_this->m1BB0 = 0;
        } else {
            i_this->m18D6 = 5;
            local_f8 = pfVar2->current.pos;
            dVar8 = 1.0f;
            dVar9 = 200.0f;
            if (i_this->m1BA0 > REG0_F(2) + 50.0f) {
                i_this->m1BB0 = 0;
            }
        }
        i_this->m1BAC = 0.0f;
        i_this->m1BB1 = (s8)l_HIO.m14;
        i_this->m1B94 = i_this->m1B88;
    } else {
        if (i_this->m1BB1 != 0) {
            i_this->m1BB1--;
            dBgS_GndChk local_bc;
            Vec pos;
            pos = i_this->m1B88;
            pos.y += 200.0f;
            local_bc.SetPos(&pos);
            fVar10 = REG0_F(0x10) + dComIfG_Bgsp()->GroundCross(&local_bc) + 30.0f;
            if (fVar10 != -G_CM3D_F_INF) {
                cLib_addCalc2(&i_this->m1B88.y, fVar10, 0.1f, REG0_F(0xb) + 2.0f);
            }
            if (i_this->m1BB3 != 0) {
                f32 f1 = i_this->m1BB3 * (REG0_F(3) + 3.0f);
                local_d4.x = (f1 * cM_ssin(i_this->m18AC * (REG0_S(5) + 0x1fa4)));
                local_d4.y = (f1 * cM_ssin(i_this->m18AC * (REG0_S(5) + 0x2260)));
                local_d4.z = (f1 * cM_ssin(i_this->m18AC * (REG0_S(5) + 0x206c)));
                dVar8 = 1.0f;
                dVar9 = f1;
                local_f8 = i_this->m1B94 + local_d4;
            } else {
                local_f8 = i_this->m1B94;
            }
        } else {
            cLib_addCalc2(&i_this->m1BAC, 1.0f, 1.0f, 0.01f);
        }
        if (i_this->m1BB2 != 0) {
            i_this->m1BB2--;
            local_c8.x = (REG0_F(0x11) + 400.0f) * cM_ssin((int)i_this->m18AC * (REG0_S(5) + 0xc1c));
            local_c8.y = 400.0f;
            local_c8.z = (REG0_F(0x11) + 400.0f) * cM_ssin((int)i_this->m18AC * (REG0_S(7) + 0x1324));
            local_f8 = i_this->m1908[0].m04 + local_c8;
            dVar8 = 1.0f;
            dVar9 = 200.0f;
        }
    }
    local_c8 = i_this->m1B88 - i_this->m1908[0].m04;
    fVar10 = local_c8.abs();
    dVar7 = ((REG0_F(2) + 0.035f) * fVar10);
    if (i_this->m1BB6 != 0) {
        local_f8 = i_this->m1908[0].m04;
        dVar8 = 1.0f;
        dVar9 = 50.0f;
        if (i_this->m1BB6 != 2) {
            fopAcM_OffStatus(actor, 0);
            actor->attention_info.flags = 0;
        }
        if (dVar7 < (REG0_F(1) + 20.0f)) {
            dVar7 = (REG0_F(1) + 20.0f);
        }
    }
    cLib_addCalc2(&i_this->m1B88.x, local_f8.x, dVar8, dVar9);
    cLib_addCalc2(&i_this->m1B88.y, local_f8.y, dVar8, dVar9);
    cLib_addCalc2(&i_this->m1B88.z, local_f8.z, dVar8, dVar9);
    cLib_addCalc2(&i_this->m1BA0, dVar7, 1.0f, 2.0f);
    i_this->m1BA8 = REG0_F(3) + 10.0f;
    control1(i_this);
    control2(i_this);
    sita_s* psVar5 = i_this->m1908;
    for (s32 i = 0; i < 30; i++, ++psVar5) {
        MtxTrans(psVar5->m04.x, psVar5->m04.y, psVar5->m04.z, false);
        fVar10 = (1.0f + REG0_F(9)) + (0.2f + REG0_F(9)) * cM_scos((int)i_this->m18AC * (REG0_S(7) + 1000) + i * (REG0_S(8) + 2000));
        MtxScale(fVar10, fVar10, fVar10, true);
        psVar5->m00->setBaseTRMtx(*calc_mtx);
        if (i == 29) {
            actor->eyePos = psVar5->m04;
            actor->attention_info.position = actor->eyePos;
            actor->attention_info.position.y += 20.0f;
            i_this->mCcD_Sph.SetC(psVar5->m04);
            dComIfG_Ccsp()->Set(&i_this->mCcD_Sph);
        } else if ((((i == 0) || (i == 6)) || (i == 12)) || (i == 18 || (i == 24))) {
            i_this->mCcD_Sph_Array5[i / 6].SetC(psVar5->m04);
            dComIfG_Ccsp()->Set(&i_this->mCcD_Sph_Array5[i / 6]);
        }
    }
}

/* 00005D78-00005DFC       .text move__FP9bwd_class */
void move(bwd_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    switch (i_this->m18AE) {
    case 0:
        start(i_this);
        break;
    case 1:
        wait(i_this);
        break;
    case 2:
        reset(i_this);
        break;
    case 3:
        sita_hit(i_this);
        break;
    case 5:
        eat_attack(i_this);
        break;
    case 10:
        fly(i_this);
        break;
    case 11:
        s_fly(i_this);
        break;
    case 12:
        end(i_this);
    case 13:
        break;
    }
}

/* 00005DFC-00007320       .text demo_camera__FP9bwd_class */
void demo_camera(bwd_class* i_this) {
    /* Nonmatching - regalloc */
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    f32 fVar2;
    s16 sVar3;
    camera_class* camera2;
    fopAc_ac_c* pfVar7;
    cXyz local_98;
    cXyz local_a4;
    cXyz local_b0;
    cXyz local_d4;
    cXyz local_e0;

    fopAc_ac_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    daPy_py_c* player2 = (daPy_py_c*)player;
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    switch (i_this->m3C1E) {
    case 0:
        break;
    case 1:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        i_this->m3C1E++;
        camera2 = dComIfGp_getCamera(0);
        i_this->m3C28 = camera2->mLookat.mEye;
        i_this->m3C34 = camera2->mLookat.mCenter;
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->m3C20 = 0;
        i_this->m3C22 = 0;
        i_this->m3C48 = 55.0f;
        i_this->m3C44 = 0.0f;
        i_this->m3C1C = 0x96;
        // fallthrough
    case 2:
        local_98.x = 0.0f;
        local_98.y = 5000.0f;
        local_98.z = 0.0f;
        player2->setPlayerPosAndAngle(&local_98, (int)player->shape_angle.y);
        mDoMtx_YrotS(*calc_mtx, (int)actor->shape_angle.y);
        local_98.x = 0.0f;
        local_98.y = REG0_F(6) + 500.0f;
        local_98.z = REG0_F(7) + 1500.0f;
        MtxPosition(&local_98, &local_a4);
        local_a4 += actor->current.pos;
        cLib_addCalc2(&i_this->m3C28.x, local_a4.x, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m3C28.y, local_a4.y, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m3C28.z, local_a4.z, 0.1f, 50.0f);
        local_98.x = 0.0f;
        local_98.y = REG0_F(8) + 400.0f;
        local_98.z = REG0_F(9);
        MtxPosition(&local_98, &local_a4);
        local_a4 += actor->current.pos;
        cLib_addCalc2(&i_this->m3C34.x, local_a4.x, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m3C34.y, local_a4.y, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m3C34.z, local_a4.z, 0.1f, 50.0f);
        break;
    case 3:
        local_a4 = player->current.pos;
        local_a4.y += 100.0f;
        cLib_addCalc2(&i_this->m3C34.x, local_a4.x, 0.1f, 100.0f);
        cLib_addCalc2(&i_this->m3C34.y, local_a4.y, 0.1f, 100.0f);
        cLib_addCalc2(&i_this->m3C34.z, local_a4.z, 0.1f, 100.0f);
        if (i_this->m3C20 > 0x3c) {
            i_this->m3C1E = 0x96;
        }
        break;
    case 0x32:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->m3C1E = 0x33;
        i_this->m3C20 = 0;
        i_this->m3C22 = 0;
        i_this->m3C48 = 55.0f;
        i_this->m3C44 = 0.0f;
        player2->changeOriginalDemo();
        mDoAud_bgmStreamPlay();
        i_this->m3C1C = 100;
    case 0x33:
        i_this->m3C34.set(0.0f, REG0_F(0) + 500.0f, 0.0f);
        i_this->m3C28.set(REG0_F(1) + 200.0f, REG0_F(2) + 388.0f, REG0_F(3) + 3575.0f);
        local_98.set(0.0f, player->current.pos.y, REG0_F(4) + 3000.0f);
        player2->setPlayerPosAndAngle(&local_98, -0x8000);
        if (i_this->m3C20 >= 0x1E) {
            if (i_this->m3C20 == 0x1E) {
                dComIfGp_getVibration().StartQuake(REG0_S(5) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            }
            i_this->m3C4C = REG0_F(5) + 3.0f;
            if (i_this->m3C20 == 0x32) {
                player2->changeDemoMode(daPy_demo_c::DEMO_UNK_028_e);
            }
        }
        if ((int)i_this->m3C22 != REG0_S(3) + 0xaa) {
            break;
        }
        i_this->m3C1E = 0x34;
        i_this->m3C20 = 0;
        i_this->m3C15 = 1;
    case 0x34:
        i_this->m3C4C = REG0_F(5) + 3.5f;
        i_this->m1864 = 10;
        if (i_this->m3C20 >= 0x96) {
            if (i_this->m3C20 == 0x96) {
                i_this->m3C34.set(25.0f, REG0_F(8) + 597.0f, 1578.0f);
            }
            i_this->m3C34.x -= (REG0_F(4) + 0.5f);
            i_this->m3C28.x = -156.0f;
            i_this->m3C28.y = 767.0f;
            i_this->m3C28.z = 2148.0f;
        } else {
            if (i_this->m3C20 == 0x14) {
                i_this->m17E4[1] = 1;
                for (s32 i = 3; i < (s32)ARRAY_SIZE(suna_gr_pos); i++) {
                    mDoAud_seStart(JA_SE_OBJ_BWD_SANDFALL_S, &suna_gr_pos[i], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                }
            }
            i_this->m3C34.x = -1110.0f;
            i_this->m3C34.y = 1598.0f;
            i_this->m3C34.z = -45.0f;
            i_this->m3C28.x = -4426.0f;
            i_this->m3C28.y = 2574.0f;
            i_this->m3C28.z = 888.0f;
            // fallthrough
        }
        if ((int)i_this->m3C22 != REG0_S(5) + 0x280) {
            break;
        }
        i_this->m3C1E = 0x35;
        i_this->m3C20 = 0;
        i_this->m3C48 = 45.0f;
        i_this->m17E0 = 900.0f;
        local_98.set(player->current.pos.x, player->current.pos.y + 400.0f, player->current.pos.z);
        player2->setPlayerPosAndAngle(&local_98, -0x8000);
        // fallthrough
    case 0x35:
        if ((i_this->m3C20 >= 0x46) && (i_this->m3C20 < (s16)(REG0_S(8) + 0x5a))) {
            if (i_this->m3C20 == 0x55) {
                player2->changeDemoMode(daPy_demo_c::DEMO_S_SURP_e);
            }
            i_this->m3C34.set(player->current.pos.x, (player->eyePos.y + REG0_F(6)) - 30.0f, player->current.pos.z);
            i_this->m3C28.set(player->current.pos.x + REG0_F(7), (player->eyePos.y + REG0_F(8)) - 30.0f, (player->current.pos.z - 200.0f) + REG0_F(9));
        } else {
            i_this->m3C34.x = 6.0f;
            i_this->m3C34.y = 1166.0f;
            i_this->m3C34.z = -319.0f;
            i_this->m3C28.x = 180.0f;
            i_this->m3C28.y = 1362.0f;
            i_this->m3C28.z = 3253.0f;
            cLib_addCalc2(&i_this->m3C48, 55.0f, 0.1f, 0.1f);
        }
        if (i_this->m3C22 < 0x2ee) {
            i_this->m3C4C = REG0_F(5) + 3.0f;
        }
        if ((int)i_this->m3C22 != REG0_S(3) + 0x2f8) {
            break;
        }
        i_this->m3C1E = 0x3c;
        i_this->m3C20 = 0;
        dComIfGp_getVibration().StopQuake(-1);
        i_this->m3C1C = 200;
        // fallthrough
    case 0x3C:
        if (i_this->m3C1C > 2) {
            cLib_addCalcAngleS2(&i_this->m3C1C, 1, 1, 1);
        }
        cLib_addCalc2(&i_this->m3C34.x, actor->current.pos.x, 0.1f, 100.0f);
        local_98.y = i_this->m1908[0].m04.y + REG0_F(10) + 200.0f;
        fVar2 = REG0_F(0xc) + -200.0f + 300.0f + l_HIO.m28;
        if (local_98.y < fVar2) {
            local_98.y = fVar2;
        }
        cLib_addCalc2(&i_this->m3C34.y, local_98.y, 0.1f, 100.0f);
        cLib_addCalc2(&i_this->m3C34.z, actor->current.pos.z, 0.1f, 100.0f);
        cLib_addCalc2(&i_this->m3C28.x, actor->current.pos.x * 0.5f, 0.05f, 50.0f);
        cLib_addCalc2(&i_this->m3C28.y, l_HIO.m28 + 100.0f + REG0_F(0xf) + 300.0f, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m3C28.z, ((actor->current.pos.z + 1700.0f + 500.0f) - 200.0f) + REG0_F(9), 0.05f, 50.0f);
        if ((int)i_this->m3C22 == REG0_S(4) + 0x5b4) {
            i_this->m3C1E = 0x96;
            if (dComIfGp_getStartStageName()[0] == 'X') {
                mDoAud_bgmStart(JA_BGM_PAST_RANE);
            } else {
                mDoAud_bgmStart(JA_BGM_RANE_BATTLE);
            }
            i_this->m3C50 = 1;
            dComIfGs_onStageBossDemo();
        }
        break;
    case 0x64:
        if (!actor->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(actor, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            actor->eventInfo.onCondition(dEvtCnd_UNK2_e);
            return;
        }
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(2);
        i_this->m3C1E = 0x65;
        i_this->m3C20 = 0;
        i_this->m3C22 = 0;
        i_this->m3C48 = 55.0f;
        camera2 = dComIfGp_getCamera(0);
        i_this->m3C28 = camera2->mLookat.mEye;
        i_this->m3C34 = camera2->mLookat.mCenter;
        i_this->m3C44 = 0.0f;
        player2->changeOriginalDemo();
        set_pos.x = actor->current.pos.x - 100.0f;
        set_pos.y = player->current.pos.y;
        set_pos.z = actor->current.pos.z + 777.0f;
        i_this->m3C1C = 0x96;
        // fallthrough
    case 0x65: {
        dBgS_GndChk local_8c;
        Vec pos;
        pos = set_pos;
        pos.y += 1000.0f;
        local_8c.SetPos(&pos);
        fVar1 = dComIfG_Bgsp()->GroundCross(&local_8c);
        if (fVar1 != -G_CM3D_F_INF) {
            set_pos.y = fVar1;
        } else {
            set_pos.y = 3000.0f;
        }
        player2->setPlayerPosAndAngle(&set_pos, -0x8000);
    }
        cLib_addCalc2(&i_this->m3C34.x, actor->current.pos.x, 0.1f, 100.0f);
        local_98.y = i_this->m1908[0].m04.y + REG0_F(10) + 200.0f;
        fVar2 = REG0_F(0xc) + -200.0f + 300.0f + l_HIO.m28;
        if (local_98.y < fVar2) {
            local_98.y = fVar2;
        }
        cLib_addCalc2(&i_this->m3C34.y, local_98.y, 0.1f, 100.0f);
        cLib_addCalc2(&i_this->m3C34.z, actor->current.pos.z, 0.1f, 100.0f);
        cLib_addCalc2(&i_this->m3C28.x, actor->current.pos.x, 0.05f, 50.0f);
        cLib_addCalc2(&i_this->m3C28.y, l_HIO.m28 + 100.0f + REG0_F(0xf) + 300.0f, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m3C28.z, actor->current.pos.z + 1700.0f + 500.0f + REG0_F(9), 0.05f, 50.0f);
        cLib_addCalcAngleS2(&i_this->m3C1C, 1, 1, 1);
        break;
    case 0x66:
        cLib_addCalc2(&i_this->m3C34.x, i_this->m0418[i_this->m3C24].x, 0.1f, i_this->m3C44 * 200.0f);
        cLib_addCalc2(&i_this->m3C34.y, i_this->m0418[i_this->m3C24].y, 0.1f, i_this->m3C44 * 200.0f);
        cLib_addCalc2(&i_this->m3C34.z, i_this->m0418[i_this->m3C24].z, 0.1f, i_this->m3C44 * 200.0f);
        cLib_addCalc2(&i_this->m3C44, 1.0f, 1.0f, 0.02f);
        if (i_this->m3C20 == 0x32) {
            player2->changeDemoMode(daPy_demo_c::DEMO_LOOKUP_e);
        }
        break;
    case 0x68:
        i_this->m3C48 = REG0_F(6) + 55.0f;
        if (i_this->m3C20 == 0x14) {
            local_b0.x = 1.0f;
            local_b0.y = 1.0f;
            local_b0.z = 1.0f;
            i_this->m18E0 = fopAcM_createItemForBoss(&i_this->m18E4, 0, fopAcM_GetRoomNo(actor), NULL, &local_b0, 1);
        }
        if (i_this->m3C20 >= 0x2C) {
            i_this->m3C1E = 0x69;
            i_this->m3C20 = 0;
        }
        break;
    case 0x69:
        i_this->m3C28.x = (player->current.pos.x - 300.0f) + REG0_F(8);
        i_this->m3C28.y = (player->current.pos.y - 50.0f) + REG0_F(9) + 100.0f + 100.0f;
        i_this->m3C28.z = (player->current.pos.z - 600.0f) + REG0_F(10);
        i_this->m3C34.x = player->current.pos.x + REG0_F(0xb);
        i_this->m3C34.y = player->current.pos.y + REG0_F(0xc);
        i_this->m3C34.z = (player->current.pos.z - 350.0f) + REG0_F(0xd);
        pfVar7 = fopAcM_SearchByID(i_this->m18E0);
        if ((i_this->m3C20 < 10) && (pfVar7 != NULL)) {
            pfVar7->current.pos.set(player->current.pos.x, player->current.pos.y + 300.0f, player->current.pos.z - 350.0f);
            pfVar7->speed.setall(0.0f);
        }
        if (i_this->m3C20 == 0x14) {
            player2->changeDemoMode(daPy_demo_c::DEMO_SURPRISED_e);
        }
        if (i_this->m3C20 == 0x3a) {
            player2->changeDemoMode(daPy_demo_c::DEMO_UNK_029_e);
        }
        if ((i_this->m3C20 >= 0x78) && (REG0_S(3) == 0)) {
            i_this->m3C1E = 0x6a;
            i_this->m3C20 = 0;
            actor->current.angle.y = 0;
            i_this->m17C8.x = 0.0f;
            i_this->m17C8.z = 0.0f;
            i_this->m17C4 = 0xca;
            i_this->m1865 = 0;
            i_this->m3C15 = 5;
            i_this->m3C1C = 100;
        }
        break;
    case 0x6A:
        if (i_this->m3C20 == 0x32) {
            i_this->m17E4[0]++;
        }
        if (i_this->m3C20 == 0x6e) {
            i_this->m17E4[1]++;
        }
        cLib_addCalc2(&i_this->m17E0, REG0_F(7) + 400.0f, 0.1f, 1.0f);
        i_this->m3C34.x = 0.0f;
        i_this->m3C34.z = 0.0f;
        i_this->m3C34.y = REG0_F(0xc) + 200.0f;
        actor->current.angle.y = actor->current.angle.y + (int)i_this->m3C44;
        if ((int)i_this->m3C20 < REG0_S(6) + 400) {
            cLib_addCalc2(&i_this->m3C44, 40.0f, 1.0f, 0.5f);
        }
        if ((int)i_this->m3C20 > REG0_S(6) + 600) {
            cLib_addCalc2(&i_this->m3C44, 0.0f, 1.0f, 0.5f);
        }
        mDoMtx_YrotS(*calc_mtx, (int)actor->current.angle.y);
        local_98.x = 0.0f;
        local_98.y = REG0_F(0xd) + 1200.0f;
        local_98.z = REG0_F(0xe) + 2600.0f;
        MtxPosition(&local_98, &i_this->m3C28);
        if ((int)i_this->m3C20 == REG0_S(6) + 0x208) {
            i_this->m17C4 = 200;
            dComIfGs_onStageBossEnemy();
            local_98.x = 0.0f;
            local_98.y = 300.0f;
            local_98.z = 0.0f;
            fopAcM_createWarpFlower(&local_98, 0, fopAcM_GetRoomNo(actor), 0);
            i_this->m3C50 = 0;
        }
        if ((int)i_this->m3C20 != REG0_S(6) + 0x2a8) {
            break;
        }
        i_this->m3C1E = 0x96;
    case 0x96:
        dComIfGp_event_reset();
        i_this->m3C1E = 0;
        camera->mCamera.Reset(i_this->m3C34, i_this->m3C28);
        camera->mCamera.Start();
        camera->mCamera.SetTrimSize(0);
        i_this->m3C1C = 1;
        break;
    default:
        break;
    }
    if (i_this->m3C1E != 0) {
        f32 fx = i_this->m3C4C * cM_ssin(i_this->m3C20 * 0x3300);
        f32 fy = i_this->m3C4C * cM_scos(i_this->m3C20 * 0x3000);
        local_d4.x = i_this->m3C28.x + fx;
        local_d4.y = i_this->m3C28.y + fy;
        local_d4.z = i_this->m3C28.z;
        local_e0.x = i_this->m3C34.x + fx;
        local_e0.y = i_this->m3C34.y + fy;
        local_e0.z = i_this->m3C34.z;
        sVar3 = (i_this->m3C4C * cM_scos(i_this->m18AC * 0x1c00) * 7.5f);
        camera->mCamera.Set(local_e0, local_d4, sVar3, i_this->m3C48);
        cLib_addCalc0(&i_this->m3C4C, 1.0f, (REG0_F(0x10) + 2.0f));
        JUTReport(410, 410, "K MAIN COUNT  %d", i_this->m3C22);
        JUTReport(410, 430, "K SUB  COUNT  %d", i_this->m3C20);
        i_this->m3C20++;
        i_this->m3C22++;
    }
    if ((i_this->m3C1E >= 0x32) && (i_this->m3C1E < 100)) {
        if ((i_this->m3C22 > 0x28) && (i_this->m3C22 < 0x2da)) {
            mDoAud_seStart(JA_SE_ATM_JINARI, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
        if ((i_this->m3C22 > 0x154) && (i_this->m3C22 < 700)) {
            mDoAud_seStart(JA_SE_ATM_BWD_SAND_FLOW, &center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
    }
    if (((i_this->m3C1E >= 100) && (i_this->m3C22 >= 700)) && (i_this->m3C22 <= 0x4b0)) {
        mDoAud_seStart(JA_SE_ATM_BWD_SAND_EBB, &center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
    }
}

/* 00007320-000074A4       .text bwd_kankyo__FP9bwd_class */
void bwd_kankyo(bwd_class* i_this) {
    if (i_this->m3C14 != 0) {
        i_this->m3C14--;
    }
    switch (i_this->m3C15) {
    case 0:
        dKy_custom_colset(0, 1, 0.0f);
        break;
    case 1:
        dKy_custom_colset(0, 1, i_this->m3C18);
        cLib_addCalc2(&i_this->m3C18, 1.0f, 1.0f, 0.01f);
        break;
    case 2:
        dKy_custom_colset(1, 2, i_this->m3C18);
        cLib_addCalc2(&i_this->m3C18, 1.0f, 1.0f, 0.05f);
        if (i_this->m3C14 == 0) {
            if (i_this->m18AE == 0xc) {
                i_this->m3C15 = 4;
            } else {
                i_this->m3C15 = 3;
            }
        }
        break;
    case 3:
        dKy_custom_colset(1, 2, i_this->m3C18);
        cLib_addCalc0(&i_this->m3C18, 1.0f, 0.02f);
        break;
    case 4:
        dKy_custom_colset(3, 2, i_this->m3C18);
        cLib_addCalc0(&i_this->m3C18, 1.0f, 0.02f);
        break;
    case 5:
        dKy_custom_colset(3, 4, i_this->m3C18);
        cLib_addCalc2(&i_this->m3C18, 1.0f, 1.0f, 0.02f);
        break;
    }
}

/* 000074A4-00008C24       .text daBwd_Execute__FP9bwd_class */
static BOOL daBwd_Execute(bwd_class* i_this) {
    /* Nonmatching - regalloc */
    static s32 jno[] = {0x10, 0x12, 0x13, 0x17, 0x19, 0x1A, 0x04, 0x07, 0x0B};
    static f32 jsize[] = {180.0f, 120.0f, 90.0f, 180.0f, 120.0f, 90.0f, 230.0f, 150.0f, 150.0f};
    static s16 demo_ang[] = {0x3E80, 0xBB80};
    fopAc_ac_c* actor = &i_this->actor;
    u8 uVar1;
    f32 fVar4;
    uint uVar5;
    int iVar8;
    J3DAnmTextureSRTKey* pJVar11;
    J3DModel* pJVar14;
    int iVar15;
    int iVar16;
    uint uVar18;
    cM3dGSph* sph;
    f32 dVar24;
    f32 fVar26;
    cXyz local_110;
    cXyz cStack_11c;
    cXyz local_128;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    if (dComIfGp_getStartStageName()[0] == 'X') {
        i_this->m3C1C = 0x32;
    }
    calc_mtx = mtx;
    if (i_this->m3C50 != 0) {
        if (i_this->m3C50 == 2) {
            dCam_getBody()->SetTypeForce("Boss03", NULL);
            i_this->m3C50 = 1;
        } else {
            dCam_getBody()->SetTypeForce("WindBoss", NULL);
        }
    }
    dBgS_GndChk local_104;
    Vec pos;
    pos = actor->current.pos;
    pos.x += REG0_F(0xd) + 5500.0f;
    local_104.SetPos(&pos);
    fVar26 = dComIfG_Bgsp()->GroundCross(&local_104);
    if ((fVar26 < 850.0f) && (fVar26 != -G_CM3D_F_INF)) {
        i_this->m3954.y = fVar26;
    }
    i_this->m1BB6 = 0;
    ko_count = 0;
    s32 count = ko_count;
    s32 i = l_HIO.m26;
    for (; i > count; count++) {
        ko_ac[count] = NULL;
    }
    fpcM_Search(ko_s_sub, i_this);
    if (i_this->m1710 > 1) {
        i_this->m1710--;
    }
    if ((ko_count == 0) && (i_this->m1710 == 1)) {
        if (dComIfGp_getStartStageName()[0] == 'X') {
            mDoAud_bgmStart(JA_BGM_PAST_RANE);
        } else {
            mDoAud_bgmStart(JA_BGM_RANE_BATTLE);
        }
        i_this->m1710 = 0;
    }
    local_110 = player->current.pos - actor->current.pos;
    local_110.y = 0.0f;
    fVar26 = local_110.abs();
    i_this->m1BB8 = fVar26;
    i_this->m170C = 0;
    i_this->m18AC++;
    for (s32 i = 0; i < 5; i++) {
        if (i_this->m18CC[i] != 0) {
            i_this->m18CC[i]--;
        }
    }
    if (i_this->m18D6 != 0) {
        i_this->m18D6--;
    }
    if (i_this->m18FC != 0) {
        i_this->m18FC--;
    }
    if (l_HIO.m05 == 0) {
        move(i_this);
        i_this->m02C0->play(&actor->eyePos, 0, 0);
        local_110.x = 0.0f;
        local_110.y = 0.0f;
        local_110.z = REG0_F(0) + -200.0f;
        mDoMtx_YrotS(*calc_mtx, (int)actor->current.angle.y);
        mDoMtx_XrotM(*calc_mtx, actor->current.angle.x);
        MtxPosition(&local_110, &cStack_11c);
        local_110 = (actor->current.pos + cStack_11c) - i_this->m18F0;
        iVar8 = cM_atan2s(local_110.x, local_110.z);
        i_this->m1108[i_this->m1708].y = (s16)iVar8;
        fVar26 = std::sqrtf(local_110.x * local_110.x + local_110.z * local_110.z);
        i_this->m1108[i_this->m1708].x = -cM_atan2s(local_110.y, fVar26);
        fVar26 = cM_ssin(i_this->m1902);
        fVar4 = REG0_F(0xf) + 5000.0f;
        iVar8 = fVar4 * fVar26;
        i_this->m1902 += REG0_S(7) + 1000;
        i_this->m1108[i_this->m1708].z = actor->current.angle.z + iVar8;
        i_this->m0508[i_this->m1708] = actor->current.pos + cStack_11c;
        (i_this->m18F0) = actor->current.pos + cStack_11c;
        if (i_this->m170C != 0) {
            for (s32 i = 0; i < 20; i++) {
                if (i_this->m02D4[i] != 0) {
                    uVar18 = i_this->m1708 - (i + 1) * i_this->m1904;
                    uVar5 = uVar18 & 0xff;
                    mDoMtx_stack_c::transS(i_this->m0508[uVar5].x, i_this->m0508[uVar5].y, i_this->m0508[uVar5].z);
                    uVar18 = uVar18 & 0xff;
                    mDoMtx_stack_c::YrotM(i_this->m1108[uVar18].y);
                    mDoMtx_stack_c::XrotM(i_this->m1108[uVar18].x);
                    mDoMtx_stack_c::ZrotM(i_this->m1108[uVar18].z);
                    fVar26 = (REG0_F(2) + 1.1f) - (s32)i * 0.02f;
                    mDoMtx_stack_c::scaleM(fVar26, fVar26, 1.0f);
                    i_this->m02D4[i]->setBaseTRMtx(mDoMtx_stack_c::get());
                    MTXCopy(mDoMtx_stack_c::get(), *calc_mtx);
                    local_110.x = REG0_F(0xd);
                    local_110.y = REG0_F(0xe);
                    local_110.z = REG0_F(0xf);
                    MtxPosition(&local_110, &i_this->m0418[i]);
                    if (((i & 1) == 0) && (i_this->m03C4[i] < 0.1f)) {
                        dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8241, &i_this->m0418[i], 0xff, g_whiteColor, g_whiteColor, 0);
                    }
                    i_this->m0374[i]->setPlaySpeed(i_this->m03C4[i]);
                    i_this->m0374[i]->play();
                }
            }
        }
        if (actor->speedF > 1.0f) {
            i_this->m1708++;
            i_this->m1708 = i_this->m1708 & 0xff;
        }
    }
    actor->shape_angle = actor->current.angle;
    pJVar14 = i_this->m02C0->getModel();
    mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    if (((i_this->m18AE == 10) || (i_this->m18AE == 0xb)) || ((i_this->m18AE == 0xc) && (i_this->m18B0 >= 2))) {
        fVar26 = 1.0f;
    } else {
        fVar26 = l_HIO.m20;
    }
    mDoMtx_stack_c::scaleM(fVar26, fVar26, fVar26);
    pJVar14->setBaseTRMtx(mDoMtx_stack_c::get());
    i_this->m02C0->calc();
    sita_move(i_this);
    damage_check(i_this);
    static cXyz joffset[] = {
        cXyz(100.0f, 0.0f, 0.0f),
        cXyz(100.0f, 0.0f, 0.0f),
        cXyz(100.0f, 0.0f, 0.0f),
        cXyz(100.0f, 0.0f, -100.0f),
        cXyz(100.0f, 0.0f, -100.0f),
        cXyz(100.0f, 0.0f, -100.0f),
        cXyz(0.0f, 0.0f, 0.0f),
        cXyz(0.0f, 0.0f, 0.0f),
        cXyz(0.0f, 0.0f, 0.0f),
    };
    for (s32 i = 0; i < (s32)ARRAY_SIZE(joffset); i++) {
        MTXCopy(i_this->m02C0->getModel()->getAnmMtx(jno[i]), *calc_mtx);
        local_128 = joffset[i];
        MtxPosition(&local_128, &cStack_11c);
        sph = &i_this->mDamageSpheres[i];
        sph->SetC(cStack_11c);
        if (i_this->m18AE == 10) {
            sph->SetR(jsize[i]);
        } else {
            sph->SetR(l_HIO.m20 * jsize[i]);
        }
        dComIfG_Ccsp()->Set(&i_this->mDamageSpheres[i]);
    }
    demo_camera(i_this);
    if ((i_this->m394C != 0) && (player->current.pos.y < 900.0f)) {
        local_110 = i_this->m17C8 - player->current.pos;
        local_110.y = 0.0f;
        fVar26 = local_110.abs();
        dVar24 = (1.0f - (REG0_F(4) + 0.00025f) * fVar26);
        if (dVar24 < 0.0f) {
            dVar24 = 0.0f;
        }
        iVar8 = cM_atan2s(local_110.x, local_110.z);
        player->setOutPower((f32)(l_HIO.m10 * dVar24), (int)(s16)iVar8, 0);
        i_this->m394C = 0;
    }
    i_this->m02C4->setPlaySpeed(i_this->m02C8);
    i_this->m02C4->play();
    pJVar14 = i_this->m1868;
    if (i_this->m1864 != 0) {
        i_this->m1864--;
        i_this->m18A0.x = cM_rndFX(REG0_F(0x12) + 4.0f);
        i_this->m18A0.x = cM_rndFX(REG0_F(0x12) + 4.0f);
    }
    mDoMtx_stack_c::transS(i_this->m18A0.x, l_HIO.m28 + (i_this->m18A0.y + l_HIO.m2C), i_this->m18A0.z);
    if (i_this->m1865 != 0) {
        mDoMtx_stack_c::transM(0.0f, -20000.0f, 0.0f);
    }
    pJVar14->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), i_this->m186C);
    i_this->m189C->Move();
    for (s32 i = 0; i < 2; i++) {
        if (i_this->m17E4[i] != 0) {
            i_this->m185C[i]->Move();
            fVar26 = i_this->m17E0 + 50.0f + REG0_F(8);
            i_this->m3B3C = 0.0f;
            i_this->m3B40 = fVar26;
            i_this->m3B44 = 0.0f;
            i_this->m3B48[i].y = REG0_S(i) + 0xc + demo_ang[i];
            switch (i_this->m17E4[i]) {
            case 3:
                break;
            case 1:
                i_this->m17E6[i] = 0;
                i_this->m17E4[i] = 2;
                // fallthrough
            case 2:
                if (i_this->m17E6[i] == 0x32) {
                    for (s32 j = 0; j < 3; j++) {
                        iVar15 = j + i;
                        suna_gr_ang[iVar15].z = 0;
                        suna_gr_ang[iVar15].x = 0;
                        suna_gr_ang[iVar15].y = cM_atan2s(-suna_gr_pos[iVar15].x, -suna_gr_pos[iVar15].z);
                        dComIfGp_particle_setToon(
                            dPa_name::ID_SCENE_A260,
                            &suna_gr_pos[iVar15],
                            &suna_gr_ang[iVar15],
                            NULL,
                            eff_col.a,
                            &i_this->m3B54[iVar15],
                            (s8)actor->current.roomNo
                        );
                        i_this->m3B54[iVar15].setColor(eff_col);
                    }
                }
                if (i_this->m17E6[i] == 0xb4) {
                    pJVar11 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bwd", BWD_BTK_TAKI_WAIT);
                    i_this->m17F4[i]->init(i_this->m17EC[i]->getModelData(), pJVar11, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, 0);
                    i_this->m17E4[i] = 3;
                }
                break;
            case 4:
                pJVar11 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bwd", BWD_BTK_TAKI_END);
                iVar16 = i_this->m17F4[i]->init(i_this->m17EC[i]->getModelData(), pJVar11, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
                if (iVar16 == 1) {
                    i_this->m17E4[i] = 5;
                    i_this->m17E6[i] = 0;
                }
                break;
            case 5:
                if (i_this->m17E6[i] >= 0x3C) {
                    i_this->m17E4[i] = 0;
                    for (s32 j = 0; j < 3; j++) {
                        i_this->m3B54[j + i].remove();
                    }
                }
                break;
            }
            i_this->m17E6[i]++;
            i_this->m17F4[i]->play();
            pJVar14 = i_this->m17EC[i];
            mDoMtx_stack_c::transS(0.0f, REG0_F(3) + -500.0f + l_HIO.m28, 0.0f);
            mDoMtx_stack_c::YrotM(i_this->m3B48[i].y);
            pJVar14->setBaseTRMtx(mDoMtx_stack_c::get());
            MTXCopy(mDoMtx_stack_c::get(), (i_this->m17FC[i]));
            if (((i_this->m17E4[i] == 2) && (i_this->m17E6[i] >= 0x32)) || (i_this->m17E4[i] == 3)) {
                pJVar14 = 0;
                for (s32 j = 0; j < 3; j++) {
                    mDoAud_seStart(JA_SE_OBJ_BWD_SANDFALL_L, &suna_gr_pos[j + i], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                }
            }
        }
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(suna_gr_pos); i++) {
        Vec pos;
        pos = suna_gr_pos[i];
        pos.x += suna_gr_pos[i].x;
        pos.y += (f32)(1000.0f + REG0_F(0xd));
        pos.z += suna_gr_pos[i].z;
        local_104.SetPos(&pos);
        fVar26 = dComIfG_Bgsp()->GroundCross(&local_104);
        if (fVar26 != -G_CM3D_F_INF) {
            suna_gr_pos[i].y = fVar26;
        }
    }
    if (i_this->m3960 != 0) {
        if (i_this->m3960 == 1) {
            i_this->m3960++;
            i_this->m3AF4.remove();
            dComIfGp_particle_set(dPa_name::ID_SCENE_824D, &i_this->m3954, &actor->shape_angle, NULL, 0xff, &i_this->m3AF4, (s8)actor->current.roomNo);
        } else if (i_this->m3960 < 0) {
            i_this->m3960 = 0;
            i_this->m3AF4.remove();
        } else {
            mDoAud_seStart(JA_SE_CM_BWD_SAND_MOVE, &i_this->m3954, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
        }
    }
    for (s32 j = 0; j < (s32)ARRAY_SIZE(i_this->m3978); j++) {
        if (i_this->m3AE0[j] != 0) {
            i_this->m3AE0[j]--;
            if (i_this->m3AE0[j] == 0) {
                i_this->m3978[j].remove();
                if (j < 2) {
                    i_this->m3AB8[j].remove();
                }
            }
        }
    }
    for (s32 i = 0; i < 2; i++) {
        if (i_this->m3B08[i] != 0) {
            fVar26 = i_this->m3B08[i] - 1.0f;
            i_this->m3B24[i]->setPlaySpeed((s16)fVar26);
            i_this->m3B2C[i]->setFrame(fVar26);
            i_this->m3B34[i]->setFrame(fVar26);
            mDoMtx_stack_c::transS(i_this->m3B0C[i].x, i_this->m3B0C[i].y, i_this->m3B0C[i].z);
            mDoMtx_stack_c::scaleM(l_HIO.m30, l_HIO.m34, l_HIO.m30);
            i_this->m3B24[i]->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
            i_this->m3B08[i]++;
            if (i_this->m3B08[i] > 0x3c) {
                i_this->m3B08[i] = 0;
            }
        }
    }
    if (i_this->m18D8 == 0) {
        i_this->m18D8 = 1;
        fopAcM_create(PROC_BWDG, 0, &actor->home.pos, fopAcM_GetRoomNo(actor), NULL, NULL, 0xff, NULL);
    }
    uVar1 = i_this->m17C4;
    if (uVar1 != 0) {
        if (uVar1 == 0xff) {
            cLib_addCalc2(&i_this->m17D4, REG0_F(5) + 0.35f, 0.2f, REG0_F(6) + 0.1f);
            cLib_addCalcAngleS2(&i_this->m17D8, REG0_S(9) + -0x5dc, 1, 0x1e);
            cLib_addCalc2(&i_this->m17DC, 1.0f, 1.0f, 0.1f);
        } else if (uVar1 == 200) {
            cLib_addCalcAngleS2(&i_this->m17D8, 0, 1, 0x1e);
        } else if (uVar1 == 0xc9) {
            i_this->m17D4 = REG0_F(9) + -0.3f;
        } else if (uVar1 == 0xca) {
            cLib_addCalc2(&i_this->m17D4, REG0_F(4) + -0.7f, 0.1f, 0.005f);
            cLib_addCalcAngleS2(&i_this->m17D8, REG0_S(9) + -500, 1, 0x1e);
            cLib_addCalc2(&i_this->m17DC, 1.0f, 1.0f, 0.005f);
        } else {
            cLib_addCalc2(&i_this->m17D4, -0.75f, 0.1f, 0.01f);
            cLib_addCalcAngleS2(&i_this->m17D8, REG0_S(7) + 1000, 1, 0x1e);
            cLib_addCalc2(&i_this->m17DC, 1.0f, 1.0f, 0.01f);
            i_this->m17C4 = i_this->m17C4 - 1;
        }
    } else {
        cLib_addCalc0(&i_this->m17D4, 0.1f, 0.01f);
        cLib_addCalcAngleS2(&i_this->m17D8, 0, 1, 0x14);
        cLib_addCalc0(&i_this->m17DC, 1.0f, 0.01f);
    }
    bwd_kankyo(i_this);
    return TRUE;
}

/* 00008C24-00008C2C       .text daBwd_IsDelete__FP9bwd_class */
static BOOL daBwd_IsDelete(bwd_class*) {
    return TRUE;
}

/* 00008C2C-00008E0C       .text daBwd_Delete__FP9bwd_class */
static BOOL daBwd_Delete(bwd_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhaseBwd, "Bwd");
    dComIfG_resDeleteDemo(&i_this->mPhaseBwds, "Bwds");
    if (i_this->m3C51 != 0) {
        hio_set = 0;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    dComIfG_Bgsp()->Release(i_this->m189C);
    dComIfG_Bgsp()->Release(i_this->m185C[0]);
    dComIfG_Bgsp()->Release(i_this->m185C[1]);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m0418); i++) {
        mDoAud_seDeleteObject(&i_this->m0418[i]);
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(suna_gr_pos); i++) {
        mDoAud_seDeleteObject(&suna_gr_pos[i]);
    }
    mDoAud_seDeleteObject(&center_pos);
    mDoAud_seDeleteObject(&i_this->m3954);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m3978); i++) {
        i_this->m3978[i].remove();
        if (i < 2) {
            i_this->m3AB8[i].remove();
        }
    }
    i_this->m3AF4.remove();
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m3B54); i++) {
        i_this->m3B54[i].remove();
    }
    return TRUE;
}

/* 00008E0C-000096D8       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    static s32 taki_bdl[] = {BWD_BDL_HTAKI1, BWD_BDL_HTAKI2};
    static s32 s_bdl[] = {BWD_BDL_GSP00, BWD_BDL_GSP01};
    static s32 s_btk[] = {BWD_BTK_GSP00, BWD_BTK_GSP01};
    static s32 s_brk[] = {BWD_BRK_GSP00, BWD_BRK_GSP01};
    static s32 s_bck[] = {BWD_BCK_GSP00, BWD_BCK_GSP01};
    bwd_class* i_this = (bwd_class*)a_this;
    mDoExt_McaMorf* pmVar1;
    J3DModelData* modelData;
    int iVar8;
    int iVar10;
    cBgD_t* pcVar13;
    uint uVar14;
    int iVar16;
    u16 fileIndex;

    pmVar1 = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bwd", BWD_BDL_BWD),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bwd", BWD_BCK_BWD_WAIT),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    i_this->m02C0 = pmVar1;
    if ((i_this->m02C0 == NULL) || (i_this->m02C0->getModel() == NULL)) {
        return FALSE;
    }
    i_this->m02CC = mDoExt_J3DModel__create(i_this->m02C0->getModel()->getModelData(), 0, 0x11020203);
    if (i_this->m02CC == NULL) {
        return FALSE;
    }
    i_this->m02C4 = new mDoExt_brkAnm();
    iVar8 = i_this->m02C4->init(
        i_this->m02C0->getModel()->getModelData(),
        (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bwd", BWD_BRK_BWD),
        true,
        J3DFrameCtrl::EMode_NONE,
        1.0f,
        0,
        -1,
        false,
        0
    );
    if (iVar8 == 0) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bwd", BWD_BDL_BERO);
    for (s32 i = 0; i < 30; i++) {
        if (i == 29) {
            modelData = (J3DModelData*)dComIfG_getObjectRes("Bwd", BWD_BDL_BERO_SAKI);
        }
        i_this->m1908[i].m00 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (i_this->m1908[i].m00 == 0) {
            return FALSE;
        }
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bwd", BWD_BDL_BWD_SHIPPOA);
    fileIndex = BWD_BRK_BWD_SHIPPOA;
    for (s32 i = 0; i < 20; i++) {
        if (i == 0x13) {
            modelData = (J3DModelData*)dComIfG_getObjectRes("Bwd", BWD_BDL_BWD_SHIPPOB);
            fileIndex = BWD_BRK_BWD_SHIPPOB;
        }
        i_this->m02D4[i] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (i_this->m02D4[i] == 0) {
            return FALSE;
        }
        i_this->m0324[i] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (i_this->m0324[i] == 0) {
            return FALSE;
        }
        i_this->m0374[i] = new mDoExt_brkAnm();
        iVar10 =
            i_this->m0374[i]->init(modelData, (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bwd", fileIndex), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
        if (iVar10 == 0) {
            return FALSE;
        }
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bwd", BWD_BDL_HTRYF1);
    JUT_ASSERT(0x11c4, modelData != NULL);
    i_this->m1868 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (i_this->m1868 == NULL) {
        return FALSE;
    }
    i_this->m189C = new dBgW();
    if (i_this->m189C == NULL) {
        return FALSE;
    }
    uVar14 = i_this->m189C->Set((cBgD_t*)dComIfG_getObjectRes("Bwd", BWD_DZB_HTRYF1), dBgW::MOVE_BG_e, &i_this->m186C);
    if ((uVar14 & 0xff) == 1) {
        return FALSE;
    }
    i_this->m189C->SetCrrFunc(dBgS_MoveBGProc_Typical);
    for (s32 i = 0; i < 2; i++) {
        i_this->m185C[i] = new dBgW();
        if (i_this->m185C[i] == 0) {
            return FALSE;
        }
        pcVar13 = (cBgD_t*)dComIfG_getObjectRes("Bwd", BWD_DZB_HTAKI1);
        uVar14 = i_this->m185C[i]->Set(pcVar13, dBgW::MOVE_BG_e, &i_this->m17FC[i]);
        if ((uVar14 & 0xff) == 1) {
            return FALSE;
        }
        i_this->m185C[i]->SetCrrFunc(dBgS_MoveBGProc_Typical);
        modelData = (J3DModelData*)dComIfG_getObjectRes("Bwd", taki_bdl[i]);
        JUT_ASSERT(0x11ed, modelData != NULL);
        i_this->m17EC[i] = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
        if (i_this->m17EC[i] == 0) {
            return FALSE;
        }
        i_this->m17F4[i] = new mDoExt_btkAnm();
        if (i_this->m17F4[i] == 0) {
            return FALSE;
        }
        iVar16 = i_this->m17F4[i]->init(
            modelData, (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bwd", BWD_BTK_TAKI_START), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0
        );
        if (iVar16 == 0) {
            return FALSE;
        }
    }
    for (s32 i = 0; i < 2; i++) {
        pmVar1 = new mDoExt_McaMorf(
            (J3DModelData*)dComIfG_getObjectRes("Bwd", s_bdl[i]),
            NULL,
            NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes("Bwd", s_bck[i]),
            J3DFrameCtrl::EMode_NONE,
            1.0f,
            0,
            -1,
            0,
            NULL,
            0,
            0x11020203
        );
        i_this->m3B24[i] = pmVar1;
        if ((i_this->m3B24[i] == NULL) || (i_this->m3B24[i]->getModel() == NULL)) {
            return FALSE;
        }
        modelData = i_this->m3B24[i]->getModel()->getModelData();
        i_this->m3B2C[i] = new mDoExt_btkAnm();
        if (i_this->m3B2C[i] == 0) {
            return FALSE;
        }
        iVar10 = i_this->m3B2C[i]->init(
            modelData, (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Bwd", s_btk[i]), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0
        );
        if (iVar10 == 0) {
            return FALSE;
        }
        i_this->m3B34[i] = new mDoExt_brkAnm();
        iVar10 =
            i_this->m3B34[i]->init(modelData, (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bwd", s_brk[i]), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
        if (iVar10 == 0) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00009720-00009C7C       .text daBwd_Create__FP10fopAc_ac_c */
static cPhs_State daBwd_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph body_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK800,
            /* SrcObjAt  Atp     */ 8,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
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
            /* Radius */ 15.0f,
        }},
    };
    static dCcD_SrcSph bero_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ 0,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
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
            /* Radius */ 70.0f,
        }},
    };
    static dCcD_SrcSph bero_co_sph_src = {
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
    f32 fVar1;
    cPhs_State res;

    fopAcM_ct(a_this, bwd_class);
    bwd_class* i_this = (bwd_class*)a_this;
    fopAc_ac_c* actor = &i_this->actor;
    res = dComIfG_resLoad(&i_this->mPhaseBwd, "Bwd");
    if (res != cPhs_COMPLEATE_e) {
        return res;
    }
    res = dComIfG_resLoad(&i_this->mPhaseBwds, "Bwds");
    if (res != cPhs_COMPLEATE_e) {
        return res;
    }
    i_this->m02BC = fopAcM_GetParam(actor) & 0xFF;
    if (!fopAcM_entrySolidHeap(actor, useHeapInit, 0x96000)) {
        return cPhs_ERROR_e;
    }
    if (dComIfG_Bgsp()->Regist(i_this->m189C, actor)) {
        return cPhs_ERROR_e;
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m185C); i++) {
        if (dComIfG_Bgsp()->Regist(i_this->m185C[i], actor)) {
            return cPhs_ERROR_e;
        }
    }
    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    actor->attention_info.distances[2] = 0x22;
    if (hio_set == 0) {
        i_this->m3C51 = 1;
        hio_set = 1;
        l_HIO.mNo = mDoHIO_createChild("風ボス", &l_HIO); // Wind boss
    }
    actor->health = 0xc;
    actor->max_health = 0xc;
    i_this->mCcD_Stts.Init(0xfa, 0, actor);
    for (s32 i = 0; i < 17; i++) {
        i_this->mDamageSpheres[i].SetStts(&i_this->mCcD_Stts);
        i_this->mDamageSpheres[i].Set(body_sph_src);
    }
    i_this->mCcD_Sph.SetStts(&i_this->mCcD_Stts);
    i_this->mCcD_Sph.Set(bero_sph_src);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mCcD_Sph_Array5); i++) {
        i_this->mCcD_Sph_Array5[i].SetStts(&i_this->mCcD_Stts);
        i_this->mCcD_Sph_Array5[i].Set(bero_co_sph_src);
    }
    if (!(dComIfGs_isStageBossDemo()) && (dComIfGp_getStartStageName()[0] != 'X')) {
        actor->current.pos.x = 0.0f;
        actor->current.pos.y = -20000.0f;
        actor->current.pos.z = 0.0f;
        i_this->m18AE = 0;
        i_this->m17DC = 1.0f;
        i_this->m17E0 = 200.0f;
        fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
        i_this->m3C50 = 1;
    } else {
        if ((dComIfGs_isStageBossEnemy()) && (dComIfGp_getStartStageName()[0] != 'X')) {
            i_this->m18AE = 0xd;
            actor->current.pos.x = 0.0f;
            actor->current.pos.y = -20000.0f;
            actor->current.pos.z = 0.0f;
            i_this->m17E0 = REG0_F(0xb) + 400.0f;
            i_this->m3C15 = 5;
        } else {
            dComIfGs_offTmpBit(dSv_event_tmp_flag_c::UNK_0480);
            fopAcM_OnStatus(actor, fopAcStts_SHOWMAP_e);
            i_this->m18AE = 1;
            i_this->m18B0 = -10;
            fVar1 = REG0_F(0x11) + -1500.0f;
            actor->current.pos.x = 0.0f;
            actor->current.pos.y = fVar1;
            actor->current.pos.z = 0.0f;
            i_this->m17E0 = 900.0f;
            i_this->m1865 = 1;
            i_this->m17E4[0] = 1;
            i_this->m17E4[1] = 1;
            i_this->m3C15 = 1;
            if (dComIfGp_getStartStageName()[0] == 'X') {
                mDoAud_bgmStart(JA_BGM_PAST_RANE);
            } else {
                mDoAud_bgmStart(JA_BGM_RANE_BATTLE);
            }
        }
    }
    i_this->m1B88.y = actor->current.pos.y;
    for (s32 i = 0; i < 30; i++) {
        fVar1 = actor->current.pos.y;
        i_this->m1908[i].m04.x = 0;
        i_this->m1908[i].m04.y = fVar1;
        i_this->m1908[i].m04.z = 0;
    }
    eff_col.r = 0xa0;
    eff_col.g = 0xa0;
    eff_col.b = 0x80;
    eff_col.a = 0x96;
    i_this->m1714 = actor->tevStr;
#if VERSION == VERSION_USA
    i_this->m1BC0 = fopAcM_create(PROC_ATT, 0x65, &actor->current.pos, fopAcM_GetRoomNo(actor));
#endif
    return cPhs_COMPLEATE_e;
}

static actor_method_class l_daBwd_Method = {
    (process_method_func)daBwd_Create,
    (process_method_func)daBwd_Delete,
    (process_method_func)daBwd_Execute,
    (process_method_func)daBwd_IsDelete,
    (process_method_func)daBwd_Draw,
};

actor_process_profile_definition g_profile_BWD = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BWD,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bwd_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BWD,
    /* Actor SubMtd */ &l_daBwd_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
