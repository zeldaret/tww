/**
 * d_a_bgn2.cpp
 * Boss - Puppet Ganon (Phase 2) / Ｇ（タラバ） (G (King crab))
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_bgn2.h"
#include "d/actor/d_a_bgn.h"
#include "d/actor/d_a_bgn3.h"
#include "d/actor/d_a_player.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_s_play.h"
#include "d/res/res_bgn.h"

class daBgn2_HIO_c : public JORReflexible {
public:
    daBgn2_HIO_c();
    virtual ~daBgn2_HIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07[0x08 - 0x07];
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ f32 m14;
    /* 0x18 */ s16 m18;
    /* 0x1A */ s16 m1A;
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
};

/* 000000EC-00000194       .text __ct__12daBgn2_HIO_cFv */
daBgn2_HIO_c::daBgn2_HIO_c() {
    mNo = -1;
    m05 = 0;
    m06 = 0;
    m08 = 280.0f;
    m0C = 3000.0f;
    m10 = 15.0f;
    m14 = -2.0f;
    m18 = 0x5dc;
    m1A = 0xa28;
    m1C = 0xed8;
    m1E = 0x3c;
    m20 = 0x32;
    m22 = 0x28;
    m24 = 100;
    m26 = DEMO_SELECT(80, 100);
    m28 = DEMO_SELECT(50, 100);
    m2A = DEMO_SELECT(200, 600);
    m2C = 100;
    m2E = 3;
    m30 = 10;
}

static bgn_class* bgn;
static bgn3_class* bgn3;
static cXyz zero(0.0f, 0.0f, 0.0f);
static bool hio_set;
static daBgn2_HIO_c l_HIO;
static dKy_tevstr_c bg_tevstr;
static s32 ki_all_count;

/* 00000194-000002BC       .text anm_init__FP10bgn2_classifUcfi */
static void anm_init(bgn2_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    if (soundFileIdx >= 0) {
        i_this->mpBodyMorf->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("Bgn", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("Bgn", soundFileIdx)
        );
    } else {
        i_this->mpBodyMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Bgn", bckFileIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 000002BC-00000308       .text bgn_s_sub__FPvPv */
static void* bgn_s_sub(void* param_1, void*) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BGN)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 00000308-00000354       .text bgn3_s_sub__FPvPv */
static void* bgn3_s_sub(void* param_1, void*) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_BGN3)) {
        return param_1;
    } else {
        return NULL;
    }
}

/* 00000354-0000035C       .text daBgn2_Draw__FP10bgn2_class */
static BOOL daBgn2_Draw(bgn2_class*) {
    return TRUE;
}

/* 0000035C-000006EC       .text gr_check__FP10bgn2_classP4cXyz */
static s32 gr_check(bgn2_class* i_this, cXyz* param_2) {
    fopAc_ac_c* actor = &i_this->actor;
    dBgS_LinChk local_a0;

    cXyz local_ac = *param_2;
    local_ac.y += 200.0f;
    cXyz local_b8 = *param_2;
    local_b8.y -= 1000.0f;
    local_a0.Set(&local_ac, &local_b8, actor);
    if (dComIfG_Bgsp()->LineCross(&local_a0)) {
        *param_2 = local_a0.mLin.GetEnd();
        param_2->y = REG0_F(8) + -2.0f;
        if (dComIfG_Bgsp()->GetAttributeCode(local_a0) == dBgS_Attr_WATER_e) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00000B60-00000CA0       .text asi_eff_set__FP10bgn2_class */
static void asi_eff_set(bgn2_class* i_this) {
    /* Nonmatching - retail-only regalloc */
    cXyz local_1c;
    cXyz local_28;

    local_28.setall(0.0f);
    g_env_light.settingTevStruct(TEV_TYPE_BG2, &local_28, &bg_tevstr);
    for (s32 i = 0; i < 6; i++) {
        s32 j = i * 5 + 8;
        local_1c = i_this->m2B98[j];
        if (!gr_check(i_this, &local_1c)) {
            dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_KGTT2JUMPHANDSPLASH00, &local_1c, 0xFF, g_whiteColor, g_whiteColor, 0);
        } else {
#if VERSION == VERSION_DEMO
            GXColor c1;
            c1.r = bg_tevstr.mColorC0.r;
            c1.g = bg_tevstr.mColorC0.g;
            c1.b = bg_tevstr.mColorC0.b;
            c1.a = 0xA0;
            GXColor c2;
            c2.r = bg_tevstr.mColorK0.r;
            c2.g = bg_tevstr.mColorK0.g;
            c2.b = bg_tevstr.mColorK0.b;
            c2.a = 0xA0;
            dComIfGp_particle_setSimple(dPa_name::ID_AK_ST_O_KGTT2JUMPHANDSMOKE00, &local_1c, 0xA0, c1, c2, 0);
#else
            dComIfGp_particle_setSimple(dPa_name::ID_AK_ST_O_KGTT2JUMPHANDSMOKE00, &local_1c, 0xFF, g_whiteColor, g_whiteColor, 0);
#endif
            if (!(i_this->m0310 & 1)) {
                dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_KGTCOMMONHAMON00, &local_1c, 0xFF, g_whiteColor, g_whiteColor, 0);
            }
        }
    }
}

/* 00000CA0-00000D88       .text asi_hamon_set__FP10bgn2_class */
static void asi_hamon_set(bgn2_class* i_this) {
    cXyz local_1c;
    cXyz local_28;

    local_28.setall(0.0f);
    g_env_light.settingTevStruct(TEV_TYPE_BG2, &local_28, &bg_tevstr);
    for (s32 i = 0; i < 30; i++) {
        s32 j = i + 4;
        local_1c = i_this->m2B98[j];
        if ((!gr_check(i_this, &local_1c)) && (!(i_this->m0310 + i & 7))) {
            dComIfGp_particle_setSimple(dPa_name::ID_AK_SN_O_KGTCOMMONHAMON00, &local_1c, 0xFF, g_whiteColor, g_whiteColor, 0);
        }
    }
}

/* 00000D88-00000FA8       .text attack_eff_set__FP10bgn2_class4cXyz */
static void attack_eff_set(bgn2_class* i_this, cXyz param_2) {
    /* Nonmatching */
#if VERSION == VERSION_DEMO
    fopAc_ac_c* actor = &i_this->actor;
#endif
    JPABaseEmitter* emitter;
    J3DModel* pJVar5;
    cXyz local_28;

    daPy_py_c* player = daPy_getPlayerActorClass();
    if (!gr_check(i_this, &param_2)) {
        pJVar5 = i_this->mpBodyMorf->getModel();
        emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT2CHESTSPLASH00, &param_2);
        if (emitter != NULL) {
            emitter->setGlobalRTMatrix(pJVar5->getAnmMtx(2));
        }
        emitter = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT2STOMACHSPLASH00, &param_2);
        if (emitter != NULL) {
            emitter->setGlobalRTMatrix(pJVar5->getAnmMtx(0x22));
        }
        fopAcM_seStart(player, JA_SE_CM_BGN_T_FALL_WATER, 0);
    } else {
        fopAcM_seStart(player, JA_SE_CM_BGN_T_FALL, 0);
#if VERSION == VERSION_DEMO
        local_28.setall(0.0f);
        g_env_light.settingTevStruct(TEV_TYPE_BG2, &local_28, &bg_tevstr);
        emitter = dComIfGp_particle_setToon(dPa_name::ID_AK_ST_KGTCOMMONSMOKE00, &param_2, NULL, NULL, 0xA0, NULL, fopAcM_GetRoomNo(actor));
        if (emitter != NULL) {
            emitter->setGlobalPrmColor(bg_tevstr.mColorC0.r, bg_tevstr.mColorC0.g, bg_tevstr.mColorC0.b);
            emitter->setGlobalEnvColor(bg_tevstr.mColorK0.r, bg_tevstr.mColorK0.g, bg_tevstr.mColorK0.b);
        }
#else
        for (s32 i = 0; i < 16; i++) {
            local_28.x = param_2.x + cM_rndFX(500.0f);
            local_28.y = param_2.y + cM_rndF(100.0f);
            local_28.z = param_2.z + cM_rndFX(500.0f);
            dComIfGp_particle_setSimple(dPa_name::ID_AK_ST_O_KGTT2JUMPHANDSMOKE00, &local_28, 0xFF, g_whiteColor, g_whiteColor, 0);
        }
#endif
    }
}

/* 00000FA8-00000FE4       .text checkGround__FP10bgn2_class */
static s32 checkGround(bgn2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    if (actor->current.pos.y <= l_HIO.m08) {
        actor->current.pos.y = l_HIO.m08;
        actor->speed.y = 0.0f;
        return TRUE;
    }
    return FALSE;
}

/* 00000FE4-00001210       .text move_se_set__FP10bgn2_class */
static void move_se_set(bgn2_class* i_this) {
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

/* 00001210-0000137C       .text pos_move__FP10bgn2_class */
static s32 pos_move(bgn2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    cXyz local_18;
    cXyz local_24;

    local_18.x = 0.0f;
    local_18.y = 0.0f;
    local_18.z = actor->speedF;
    cMtx_YrotS(*calc_mtx, actor->current.angle.y);
    MtxPosition(&local_18, &local_24);
    actor->speed.x = local_24.x;
    actor->speed.z = local_24.z;
    i_this->m034C = i_this->m0340;
    i_this->m0340.x += actor->speed.x;
    i_this->m0340.z += actor->speed.z;
    fVar1 = std::sqrtf(SQUARE(i_this->m0340.x) + SQUARE(i_this->m0340.z));
    if (fVar1 > REG0_F(3) + 1500.0f) {
        i_this->m0340.x = i_this->m034C.x;
        i_this->m0340.z = i_this->m034C.z;
        actor->speedF = 0.0f;
        return TRUE;
    }
    return FALSE;
}

/* 0000137C-0000144C       .text start__FP10bgn2_class */
static void start(bgn2_class* i_this) {
    switch (i_this->m0314) {
    case 0:
        anm_init(i_this, BGN_BCK_DERU1, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m0314 = 1;
    // fallthrough
    case 1:
        if (i_this->mpBodyMorf->isStop()) {
            i_this->m0312 = 1;
            anm_init(i_this, BGN_BCK_RAKKA1, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m0314 = 1;
        }
        break;
    }
}

/* 0000144C-00001474       .text ki_set__FP10bgn2_class */
static void ki_set(bgn2_class* i_this) {
    if (i_this->m2ED2 != 0) {
        return;
    }
    i_this->m2ED0 = l_HIO.m2E;
    i_this->m2ED2 = l_HIO.m2C;
}

/* 00001474-00001860       .text plesattack__FP10bgn2_class */
static void plesattack(bgn2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    s8 sVar6;

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s8 bVar1 = false;
    switch (i_this->m0314) {
    case 0:
        if (actor->current.pos.y > l_HIO.m0C + 2.0f) {
            cLib_addCalc2(&actor->current.pos.y, l_HIO.m0C, 0.1f, l_HIO.m10);
            actor->speed.y = 0.0f;
            actor->speedF = REG0_F(9) + 30.0f;
            break;
        }
        i_this->m2E82 = 0;
        anm_init(i_this, BGN_BCK_RAKKA1, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m0314 = 1;
        if (actor->health == 3) {
            i_this->m0330[0] = l_HIO.m1E;
        } else if (actor->health == 2) {
            i_this->m0330[0] = l_HIO.m20;
        } else {
            i_this->m0330[0] = l_HIO.m22;
            // fallthrough
        }
    case 1:
        if (i_this->mpBodyMorf->isStop()) {
            anm_init(i_this, BGN_BCK_RAKKA2, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m0314 = 2;
        }
        // fallthrough
    case 2:
        if ((i_this->m0330[0] != 0) && (actor->speed.y = actor->speed.y - l_HIO.m14, i_this->m0330[0] == 1)) {
            fopAcM_seStart(actor, JA_SE_CM_BGN_T_FALL_WIND, 0);
        }
        i_this->m2E78 = 1;
        i_this->m2E79 = 1;
        if (checkGround(i_this)) {
            ki_set(i_this);
            anm_init(i_this, BGN_BCK_SETTI1, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m0314 = 3;
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            sVar6 = actor->health;
            if (sVar6 == 3) {
                i_this->m0330[0] = l_HIO.m24;
            } else if (sVar6 == 2) {
                i_this->m0330[0] = l_HIO.m26;
            } else {
                i_this->m0330[0] = l_HIO.m28;
            }
            attack_eff_set(i_this, actor->current.pos);
        }
        break;
    case 3:
        asi_hamon_set(i_this);
        if (i_this->m0330[0] > 10) {
            bVar1 = true;
        }
        if (i_this->m0330[0] == 0) {
            i_this->m0312 = 2;
            i_this->m0314 = 0;
            actor->speed.y = 0.0f;
            return;
        }
    }
    i_this->m0318 = player->current.pos;
    actor->current.angle.y = cM_atan2s(i_this->m0318.x - actor->current.pos.x, i_this->m0318.z - actor->current.pos.z);
    pos_move(i_this);
    cLib_addCalc0(&actor->speedF, 1.0f, 2.0f);
    actor->current.pos.y = actor->current.pos.y + actor->speed.y;
    actor->speed.y = actor->speed.y + l_HIO.m14;
    checkGround(i_this);
    if (bVar1) {
        cLib_addCalc2(&i_this->m2EC4, REG0_F(9) + 250.0f, 1.0f, REG0_F(10) + 50.0f);
    }
}

/* 00001860-00001C5C       .text jumpattack__FP10bgn2_class */
static void jumpattack(bgn2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    J3DModel* pBrk;
    cXyz local_34;

    int frame = (int)i_this->mpBodyMorf->getFrame();
    i_this->m2E82 = 0;
    pBrk = i_this->mpBodyMorf->getModel();
    switch (i_this->m0314) {
    case 0:
        anm_init(i_this, BGN_BCK_JUMP1, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m0314 = 1;
    // fallthrough
    case 1:
        actor->speedF = 0.0f;
        if (frame == 6) {
            i_this->m2EC8[0] = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT2CHESTPOTA00, &actor->current.pos);
            i_this->m2EC8[1] = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTT2STOMACHPOTA00, &actor->current.pos);
        }
        if ((frame >= 5) && (frame <= 20)) {
            asi_eff_set(i_this);
        }
        if (frame == REG0_S(0) + 0x14) {
            actor->speed.y = REG0_F(8) + 250.0f;
            i_this->m0314 = 2;
            fopAcM_seStart(actor, JA_SE_CM_BGN_T_JUMP_UP, 0);
        case 2:
            actor->speedF = REG0_F(9) + 50.0f;
            break;
        }
    }
    if (i_this->m2EC8[0] != NULL) {
        i_this->m2EC8[0]->setGlobalRTMatrix(pBrk->getAnmMtx(2));
    }
    if (i_this->m2EC8[1] != NULL) {
        i_this->m2EC8[1]->setGlobalRTMatrix(pBrk->getAnmMtx(0x22));
    }
    actor->current.angle.y = cM_atan2s(-actor->current.pos.x, -actor->current.pos.z);
    local_34 = actor->current.pos;
    local_34.y = 0.0f;
    actor->current.pos.y += actor->speed.y;
    actor->speed.y -= (REG0_F(10) + 8.0f);
    if ((actor->speed.y <= 0.0f) && (actor->speed.y = 0.0f, i_this->m0314 >= 2)) {
        for (s32 i = 0; i < 2; i++) {
            if (i_this->m2EC8[i] != NULL) {
                i_this->m2EC8[i]->becomeInvalidEmitter();
                i_this->m2EC8[i] = NULL;
            }
        }
        if (pos_move(i_this) || (local_34.abs() < 500.0f)) {
            i_this->m0312 = 1;
            i_this->m0314 = 0;
            if (actor->health == 3) {
                i_this->m2E82 = l_HIO.m18;
            } else if (actor->health == 2) {
                i_this->m2E82 = l_HIO.m1A;
            } else {
                i_this->m2E82 = l_HIO.m1C;
            }
            if (cM_rndF(1.0f) < 0.5f) {
                i_this->m2E82 *= -1;
            }
        }
    }
#if VERSION == VERSION_DEMO
    if ((s8)checkGround(i_this)) {
        cLib_addCalc2(&i_this->m2EC4, REG0_F(9) + 250.0f, 1.0f, REG0_F(10) + 50.0f);
    }
#else
    checkGround(i_this);
#endif
}

/* 00001C5C-00001D4C       .text mahi__FP10bgn2_class */
static void mahi(bgn2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    switch (i_this->m0314) {
    case 0:
        fopAcM_monsSeStart(actor, JA_SE_CV_BGN_HIT_2, 0);
        i_this->m0330[0] = l_HIO.m2A;
        i_this->m0314 = 1;
        // fallthrough
    case 1:
        i_this->mpHeadMorf->play(&actor->current.pos, 0, 0);
        if (i_this->m0330[0] == 0) {
            i_this->m0312 = 2;
            i_this->m0314 = 0;
            actor->speed.y = 0.0f;
            actor->current.angle.y = actor->shape_angle.y;
        }
        break;
    }
    asi_hamon_set(i_this);
    checkGround(i_this);
}

/* 00001D4C-00001EB4       .text damage__FP10bgn2_class */
static void damage(bgn2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    i_this->mpHeadMorf->play(&actor->current.pos, 0, 0);
    switch (i_this->m0314) {
    case 0:
        anm_init(i_this, BGN_BCK_DAMAGE1, 2.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m0314 = 1;
    // fallthrough
    case 1:
        if (i_this->mpBodyMorf->isStop()) {
            i_this->m0314 = 2;
        }
    // fallthrough
    case 2:
        if ((actor->current.pos.y > 1490.0f) && (i_this->m0314 == 2)) {
            i_this->m0312 = 2;
            actor->speed.y = REG0_F(8) + 250.0f;
            i_this->m0314 = 2;
            actor->current.angle.y = actor->shape_angle.y;
        } else {
            cLib_addCalc2(&i_this->m2EC4, REG0_F(0xb) + 250.0f, 1.0f, REG0_F(0xc) + 100.0f);
        }
        break;
    }
    cLib_addCalc2(&actor->current.pos.y, 1500.0f, 0.2f, 200.0f);
    i_this->m2E82 = 0x800;
    i_this->m2E80 = 0x800;
}

/* 00001EB4-00002320       .text hensin__FP10bgn2_class */
static void hensin(bgn2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    cXyz local_2c;

    cLib_addCalc2(&i_this->m0340.x, 0.0f, 0.05f, 50.0f);
    cLib_addCalc2(&i_this->m0340.z, 0.0f, 0.05f, 50.0f);
    i_this->m2E82 = 0;
    i_this->m2E80 = 0;
    switch (i_this->m0314) {
#if VERSION == VERSION_DEMO
    case 0:
        anm_init(i_this, BGN_BCK_WAIT2, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->m0314 = 1;
        i_this->m0330[0] = 0x96;
        bgn->mCSMode = 10;
        actor->speed.y = 0.0f;
    case 1:
#else
    case 0:
        anm_init(i_this, BGN_BCK_SETTI1, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->m0314 = 1;
        bgn->mCSMode = 10;
        actor->speed.y = REG8_F(0xc) + 50.0f;
        i_this->m0330[0] = 0x30;
        break;
    case 1:
        if (i_this->m0330[0] == 0) {
            i_this->m0314 = 2;
            anm_init(i_this, BGN_BCK_WAIT2, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m0330[0] = REG8_S(5) + 0x5a;
            actor->speed.y = 0.0f;
        }
        break;
    case 2:
#endif
        if ((int)i_this->mpBodyMorf->getFrame() == 3) {
            fopAcM_seStart(actor, JA_SE_CM_BGN_T_SLIDE, 0);
        }
        if (i_this->m0330[0] == 0) {
            i_this->m0314 = 5;
            i_this->m0330[0] = 0x46;
            anm_init(i_this, BGN_BCK_MODORU1, 10.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            fopAcM_seStart(actor, JA_SE_CM_BGN_T_TO_M_1, 0);
        }
        break;
#if VERSION == VERSION_DEMO
    case 2:
        break;
#endif
    case 3:
        break;
    case 4:
        break;
    case 5:
#if VERSION > VERSION_DEMO
        if (i_this->m0330[0] == 0x32) {
            bgn->mCA60 = 0x96;
        }
#endif
        if (i_this->m0330[0] <= 0x32) {
            cLib_addCalc2(&i_this->m2E7C, 1.0f, 1.0f, 0.04f);
            if (i_this->m2E7C > 0.99f) {
                bgn->mCC90 = 1;
                bgn->mCSMode++;
                bgn3->actor.current.angle = actor->shape_angle;
                bgn3->actor.shape_angle = actor->shape_angle;
                bgn3->actor.current.pos = actor->current.pos;
                bgn3->m10060 = 1.0f;
                local_2c.setall(REG0_F(4) + 10.0f);
                dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUBAKUEN, &bgn3->actor.current.pos, NULL, &local_2c);
                dComIfGp_particle_set(dPa_name::ID_AK_JN_SIBOUFLASH, &bgn3->actor.current.pos, NULL, &local_2c);
                mDoAud_seStart(JA_SE_CM_BGN_METAM_EXPLODE, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                dComIfGp_getVibration().StartShock(REG0_S(2) + 8, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                mDoAud_bgmStart(JA_BGM_BGN_HAYAMUSHI);
            }
        }
        break;
    }
    actor->current.pos.y += actor->speed.y;
    actor->speed.y += l_HIO.m14;
    asi_hamon_set(i_this);
    checkGround(i_this);
}

/* 00002320-000026A4       .text move__FP10bgn2_class */
static void move(bgn2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar1;
    cXyz* pcVar8;
    u8* pcVar7;
    f32 dVar9;
    cXyz local_a0;
    cXyz cStack_ac;

    switch (i_this->m0312) {
    case 0:
        start(i_this);
        break;
    case 1:
        plesattack(i_this);
        move_se_set(i_this);
        break;
    case 2:
        jumpattack(i_this);
        move_se_set(i_this);
        break;
    case 4:
        mahi(i_this);
        break;
    case 5:
        damage(i_this);
        break;
    case 6:
        hensin(i_this);
        move_se_set(i_this);
    case 10:
        break;
    }
    cLib_addCalc2(&actor->current.pos.x, i_this->m0340.x, 0.05f, 1000.0f);
    cLib_addCalc2(&actor->current.pos.z, i_this->m0340.z, 0.05f, 1000.0f);
    actor->shape_angle.y = actor->shape_angle.y + i_this->m2E80;
    fVar1 = i_this->m2E80;
    if (fVar1 < 0.0f) {
        fVar1 *= -1.0f;
    }
    fVar1 *= 0.02631579f;
    if (fVar1 > 100.0f) {
        fVar1 = 100.0f;
    }
    fopAcM_seStart(actor, JA_SE_CM_BGN_T_ROUND, fVar1);
    cLib_addCalcAngleS2(&i_this->m2E80, i_this->m2E82, 1, 100);
    MTXCopy(i_this->mpBodyMorf->getModel()->getAnmMtx(2), *calc_mtx);
    local_a0.setall(0.0f);
    MtxPosition(&local_a0, &cStack_ac);
    cLib_addCalc0(&i_this->m2EC4, 1.0f, 25.0f);
    pcVar8 = i_this->mRedRopeMat.getPos(0);
    pcVar7 = i_this->mRedRopeMat.getSize(0);
    for (s32 i = 0; i < 60; i++) {
        dVar9 = i_this->m2EC4 * cM_ssin(cM_rad2s(0.053247336f * (f32)(i)));
        dVar9 *= (0.01666667f * (f32)(0x3B - i));
        local_a0.x = dVar9 * cM_ssin(i_this->m0310 * (REG0_S(3) + 300) + i * (REG0_S(4) + 2000));
        local_a0.y = 0.0f;
        local_a0.z = dVar9 * cM_ssin(i_this->m0310 * (REG0_S(5) + 0xfa) + i * (REG0_S(6) + 2000));
        *pcVar8 = cStack_ac + local_a0;
        *pcVar7 = REG0_S(3) + 10;
        cStack_ac.y += 50.0f;
        pcVar8++;
        pcVar7++;
    }
}

/* 000026A4-00002C88       .text damage_check__FP10bgn2_class */
static void damage_check(bgn2_class* i_this) {
    fopAc_ac_c* actor = &i_this->actor;
    char cVar5;
    JPABaseEmitter* pJVar2;
    f32 dVar8;
    csXyz local_78;
    cXyz local_58;
    CcAtInfo local_4c;
#if VERSION == VERSION_DEMO
    daPy_py_c* player = daPy_getPlayerActorClass();
#endif

    if (i_this->m033A == 0) {
        local_4c.pParticlePos = NULL;
        if (i_this->m039C.ChkTgHit()) {
            local_4c.mpObj = i_this->m039C.GetTgHitObj();
            at_power_check(&local_4c);
            if ((local_4c.mResultingAttackType == 9) || (local_4c.mResultingAttackType == 2)) {
                i_this->m0312 = 4;
                i_this->m0314 = 0;
                i_this->m033A = 0x14;
                i_this->m0358 = REG0_S(5) + 0x14;
                dScnPly_ply_c::nextPauseTimer = 4;
#if VERSION == VERSION_DEMO
                local_58.z = 2.0f;
                local_58.y = 2.0f;
                local_58.x = 2.0f;
                local_78.z = 0;
                local_78.x = 0;
                local_78.y = player->shape_angle.y + 0x8000;
                dComIfGp_particle_set(dPa_name::ID_AK_JN_OK, i_this->m039C.GetTgHitPosP(), &local_78, &local_58);
#else
                dComIfGp_particle_set(dPa_name::ID_AK_JN_CRITICALHITFLASH, i_this->m039C.GetTgHitPosP());
                local_58.z = 2.0f;
                local_58.y = 2.0f;
                local_58.x = 2.0f;
                local_78.z = 0;
                local_78.x = 0;
                local_78.y = fopAcM_searchPlayerAngleY(actor);
#endif
                dComIfGp_particle_set(
                    DEMO_SELECT(dPa_name::ID_IT_SN_DK_KAMEN_HAHEN00, dPa_name::ID_AK_JN_OK),
                    i_this->m039C.GetTgHitPosP(),
                    DEMO_SELECT(&actor->shape_angle, &local_78),
                    DEMO_SELECT(NULL, &local_58)
                );
                dKy_SordFlush_set(DEMO_SELECT(actor->current.pos, *i_this->m039C.GetTgHitPosP()), 1);
                dComIfGp_getVibration().StartShock(REG0_S(2) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                def_se_set(actor, local_4c.mpObj, 0x40);
                return;
            }
        }
        if (i_this->m2A48.ChkTgHit()) {
            i_this->m033A = 0x14;
#if VERSION > VERSION_DEMO
            i_this->m2D6A = 1;
            i_this->mArrowHitFlashTimer = 30;
#endif
            i_this->m0312 = 5;
            i_this->m0314 = 0;
            if (actor->health != 0) {
                actor->health--;
#if VERSION > VERSION_DEMO
                mDoAud_seStart(JA_SE_LK_ARROW_HIT, NULL, 0x35, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
#endif
                dVar8 = (REG0_F(5) + 2.0f);
                if (actor->health == 0) {
                    mDoAud_bgmStop(30);
#if VERSION == VERSION_DEMO
                    fopAcM_monsSeStart(actor, JA_SE_CV_BGN_HIT_2, 0);
                    fopAcM_seStart(actor, JA_SE_LK_LAST_HIT, 0);
                    fopAcM_seStart(actor, JA_SE_CM_BGN_M_BRK_ORB, 0);
#else
                    mDoAud_monsSeStart(JA_SE_CV_BGN_HIT_2, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    mDoAud_seStart(JA_SE_LK_LAST_HIT, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
                    mDoAud_seStart(JA_SE_CM_BGN_M_BRK_ORB, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
#endif
                    i_this->m0312 = 6;
                    i_this->m0314 = 0;
                    pJVar2 = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTBREAKWEAKPOINT00, &i_this->m2E6C);
                    if (pJVar2 != NULL) {
                        JGeometry::TVec3<f32> scale(dVar8, dVar8, dVar8);
                        pJVar2->setGlobalScale(scale);
                    }
                    pJVar2 = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTBREAKWEAKPOINT01, &i_this->m2E6C);
                    if (pJVar2 != NULL) {
                        JGeometry::TVec3<f32> scale(dVar8, dVar8, dVar8);
                        pJVar2->setGlobalScale(scale);
                    }
#if VERSION > VERSION_DEMO
                    for (s32 i = 0; i < 2; i++) {
                        if (i_this->m2EC8[i] != NULL) {
                            i_this->m2EC8[i]->becomeInvalidEmitter();
                            i_this->m2EC8[i] = NULL;
                        }
                    }
#endif
                } else {
#if VERSION == VERSION_DEMO
                    fopAcM_monsSeStart(actor, JA_SE_CV_BGN_HIT_1, 0);
#else
                    mDoAud_monsSeStart(JA_SE_CV_BGN_HIT_1, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(actor)));
#endif
                    pJVar2 = dComIfGp_particle_set(dPa_name::ID_AK_SN_KGTHITWEAKPOINT00, &i_this->m2E6C);
                    if (pJVar2 != NULL) {
                        JGeometry::TVec3<f32> scale(dVar8, dVar8, dVar8);
                        pJVar2->setGlobalScale(scale);
                    }
                }
            }
        }
        cVar5 = 0;
        if (i_this->m039C.ChkTgHit()) {
            local_4c.mpObj = i_this->m039C.GetTgHitObj();
            cVar5 = 1;
        }
        for (s32 i = 0; i < 2; i++) {
            if (i_this->m04C8[i].ChkTgHit()) {
                local_4c.mpObj = i_this->m04C8[i].GetTgHitObj();
                cVar5 = 2;
            }
        }
        for (s32 i = 0; i < 30; i++) {
            if (i_this->m0720[i].ChkTgHit()) {
                local_4c.mpObj = i_this->m0720[i].GetTgHitObj();
                cVar5 = 3;
            }
        }
        if ((cVar5 != 0) && (i_this->m033C == 0)) {
            i_this->m033C = 10;
            def_se_set(actor, local_4c.mpObj, 0x44);
        }
    }
}

/* 00002C88-00002CE0       .text ki_c_sub__FPvPv */
static void* ki_c_sub(void* param_1, void*) {
    if ((fopAc_IsActor(param_1)) && (fopAcM_GetName(param_1) == PROC_KI)) {
        ki_all_count++;
    }
    return NULL;
}

/* 00002CE0-00002D24       .text ki_check__FP10bgn2_class */
static s32 ki_check(bgn2_class* i_this) {
    ki_all_count = 0;
    fpcM_Search(ki_c_sub, i_this);
    return ki_all_count;
}

/* 00002D24-000037B0       .text daBgn2_Execute__FP10bgn2_class */
static BOOL daBgn2_Execute(bgn2_class* i_this) {
    /* Nonmatching */
    static s32 body_d[] = {
        0x00000001,
        0x00000022,
    };

    static f32 body_scale[] = {
        550.0f,
        400.0f,
    };

    static f32 asi_scale[] = {
        100.0f,
        130.0f,
        100.0f,
        80.0f,
        50.0f,
    };

    static s16 fl_check_d[] = {
        0x0015, 0x001A, 0x001F, 0x0024, 0x0029, 0x0015, 0x001A, 0x001F, 0x0024, 0x0029, 0x0015, 0x001A, 0x001F, 0x0024, 0x0029, 0x0015,
        0x001A, 0x001F, 0x0024, 0x0029, 0x0015, 0x001A, 0x001F, 0x0024, 0x0029, 0x0015, 0x001A, 0x001F, 0x0024, 0x0029, 0x0002, 0x000A,
    };

    fopAc_ac_c* actor = &i_this->actor;
    f32 fVar2;
    J3DModel* pJVar16;
    f32 dVar18;
    f32 dVar19;
    cXyz local_a0;
    cXyz local_ac;
    cXyz local_b8;

    bgn = (bgn_class*)fpcM_Search(bgn_s_sub, i_this);
    if (bgn == NULL) {
        return TRUE;
    }
    bgn3 = (bgn3_class*)fpcM_Search(bgn3_s_sub, i_this);
#if VERSION > VERSION_DEMO
    if (bgn3 == NULL) {
        return TRUE;
    }
#endif
    if (l_HIO.m06 != 0) {
        actor->health = l_HIO.m06;
    }
    if (bgn->m02B5 != 1) {
        i_this->m0312 = 10;
        actor->current.pos.set(0.0f, 2000.0f, 0.0f);
        fopAcM_OffStatus(actor, 0);
        actor->attention_info.flags = 0;
        i_this->m2ED2 = l_HIO.m2C;
        return TRUE;
    }
    if (i_this->m0312 == 10) {
        i_this->m0312 = 0;
        i_this->m0314 = 0;
        actor->health = 3;
    }
    actor->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    cLib_addCalc2(&i_this->m2E7C, 0.0f, 1.0f, 0.01f);
    i_this->m0310++;
    actor->attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 4;
    for (s32 i = 0; i < 5; i++) {
        if (i_this->m0330[i] != 0) {
            i_this->m0330[i]--;
        }
    }
    if (i_this->m033A != 0) {
        i_this->m033A--;
    }
    if (i_this->m033C != 0) {
        i_this->m033C--;
    }
    if (i_this->m2ED2 != 0) {
        i_this->m2ED2--;
    }
    if (l_HIO.m05 == 0) {
        move(i_this);
    }
    i_this->mpHeadMorf->play(&actor->current.pos, 0, 0);
    i_this->mpBodyMorf->play(&actor->current.pos, 0, 0);
    i_this->mJyakutenCBrkAnm->play();
    i_this->mJyakutenBBrkAnm->play();
    mDoMtx_stack_c::transS(actor->current.pos.x, actor->current.pos.y, actor->current.pos.z);
    mDoMtx_stack_c::YrotM(actor->shape_angle.y);
    mDoMtx_stack_c::XrotM(actor->shape_angle.x);
    mDoMtx_stack_c::ZrotM(actor->shape_angle.z);
    pJVar16 = i_this->mpBodyMorf->getModel();
    pJVar16->setBaseTRMtx(mDoMtx_stack_c::get());
    local_a0.setall(0.0f);
    i_this->mpBodyMorf->calc();
    MTXCopy(pJVar16->getAnmMtx(3), *calc_mtx);
    MtxTrans(REG0_F(0), REG0_F(1), REG0_F(2) + 100.0f, true);
    if (i_this->m0358 != 0) {
        i_this->m0358--;
    }
    dVar18 = (i_this->m0358 * (REG0_F(0xe) + 500.0f));
    dVar19 = cM_ssin(i_this->m0310 * 0x2100);
    f32 tmp = cM_scos(i_this->m0310 * 0x2300);
    cMtx_YrotM(*calc_mtx, dVar18 * dVar19);
    cMtx_XrotM(*calc_mtx, dVar18 * tmp);
    MtxScale(REG0_F(7) + 2.0f, REG0_F(7) + 2.0f, REG0_F(7) + 2.0f, true);
    i_this->mpHeadMorf->getModel()->setBaseTRMtx(*calc_mtx);
    MtxPosition(&local_a0, &i_this->m2B74);
    i_this->mpHeadMorf->calc();
    MTXCopy(pJVar16->getAnmMtx(0x23), *calc_mtx);
    MtxTrans(REG0_F(3) + 150.0f, REG0_F(4) + 150.0f, REG0_F(5), true);
    cMtx_YrotM(*calc_mtx, 0x4000);
    MtxScale(REG0_F(6) + 2.0f, REG0_F(6) + 2.0f, REG0_F(6) + 2.0f, true);
    for (s32 i = 0; i < 3; i++) {
        i_this->mpJyakutenModel[i]->setBaseTRMtx(*calc_mtx);
    }
    MtxPosition(&local_a0, &i_this->m2E6C);
    i_this->m039C.SetC(i_this->m2B74);
    i_this->m039C.SetR(REG0_F(0) + 150.0f);
    dComIfG_Ccsp()->Set(&i_this->m039C);
    actor->eyePos = i_this->m2B74;
    actor->attention_info.position = actor->eyePos;
    actor->attention_info.position.y += 100.0f;
    for (s32 i = 0; i < 2; i++) {
        MTXCopy(pJVar16->getAnmMtx(body_d[i]), *calc_mtx);
        if (i == 1) {
            local_a0.x = 400.0f;
        }
        MtxPosition(&local_a0, &i_this->m2B80[i]);
        i_this->m04C8[i].SetC(i_this->m2B80[i]);
        i_this->m04C8[i].SetR(REG0_F(i + 1) + body_scale[i]);
        if (i_this->m2E78 != 0) {
            i_this->m04C8[i].OnAtSetBit();
        } else {
            i_this->m04C8[i].OffAtSetBit();
        }
        dComIfG_Ccsp()->Set(&i_this->m04C8[i]);
    }
    i_this->m2E78 = 0;
    local_a0.x = 0.0f;
#if VERSION > VERSION_DEMO
    if (i_this->m2D6A != 0) {
        i_this->m2D6A++;
        if (i_this->m2D6A > 100) {
            i_this->m2D6A = 0;
        }
    }
    if (i_this->mArrowHitFlashTimer != 0) {
        i_this->mArrowHitFlashTimer--;
    }
#endif
    for (s32 i = 0; i < DEMO_SELECT(30, 32); i++) {
#if VERSION > VERSION_DEMO
        if (i < 30) {
#endif
            MTXCopy(pJVar16->getAnmMtx(i + 4), *calc_mtx);
            MtxPosition(&local_a0, &i_this->m2B98[i]);
            i_this->m0720[i].SetC(i_this->m2B98[i]);
            fVar2 = (REG0_F(2) + 1.6f) * asi_scale[i % 5];
            i_this->m0720[i].SetR(fVar2);
            if (i_this->m2E79 != 0) {
                i_this->m0720[i].OnAtSetBit();
            } else {
                i_this->m0720[i].OffAtSetBit();
            }
            dComIfG_Ccsp()->Set(&i_this->m0720[i]);
#if VERSION > VERSION_DEMO
        }
#endif
#if VERSION > VERSION_DEMO
        if (i_this->m2D6A == fl_check_d[i]) {
            i_this->mArrowHitEffectTimer[i] = 100;
        }
        if (i_this->mArrowHitEffectTimer[i] != 0) {
            i_this->mArrowHitEffectTimer[i]--;
            if (i < 30) {
                local_ac = i_this->m2B98[i];
            } else if (i == 30) {
                local_ac = i_this->m2B80[0];
                fVar2 = (REG8_F(3) + 400.0f);
            } else if (i == 31) {
                local_ac = i_this->m2B80[1];
                fVar2 = (REG8_F(4) + 400.0f);
            }
            dVar18 = (REG8_F(0) + 0.0003f) * (fVar2 * i_this->mArrowHitEffectTimer[i]);
            if (i_this->mpArrowHitEmitter1[i] == NULL) {
                i_this->mpArrowHitEmitter1[i] = dComIfGp_particle_set(dPa_name::ID_AK_JN_CCTHUNDER00, &local_ac);
            } else {
                i_this->mpArrowHitEmitter1[i]->setGlobalTranslation(local_ac.x, local_ac.y, local_ac.z);
                JGeometry::TVec3<f32> scale(dVar18, dVar18, dVar18);
                i_this->mpArrowHitEmitter1[i]->setGlobalScale(scale);
            }
            if (i_this->mpArrowHitEmitter2[i] == NULL) {
                i_this->mpArrowHitEmitter2[i] = dComIfGp_particle_set(dPa_name::ID_AK_JN_CCTHUNDER01, &local_ac);
            } else {
                i_this->mpArrowHitEmitter2[i]->setGlobalTranslation(local_ac.x, local_ac.y, local_ac.z);
                JGeometry::TVec3<f32> scale(dVar18, dVar18, dVar18);
                i_this->mpArrowHitEmitter2[i]->setGlobalScale(scale);
            }
        } else {
            if (i_this->mpArrowHitEmitter1[i] != NULL) {
                i_this->mpArrowHitEmitter1[i]->becomeInvalidEmitter();
                i_this->mpArrowHitEmitter1[i] = NULL;
            }
            if (i_this->mpArrowHitEmitter2[i] != NULL) {
                i_this->mpArrowHitEmitter2[i]->becomeInvalidEmitter();
                i_this->mpArrowHitEmitter2[i] = NULL;
            }
        }
#endif
    }
    i_this->m2E79 = 0;
    i_this->m2A48.SetC(i_this->m2E6C);
    i_this->m2A48.SetR(REG0_F(9) + 210.0f);
    dComIfG_Ccsp()->Set(&i_this->m2A48);
    damage_check(i_this);
    if (i_this->m2ED0 != 0) {
        i_this->m2ED0--;
        if (ki_check(i_this) < l_HIO.m30) {
            local_b8.x = cM_rndFX(2500.0f);
            local_b8.y = cM_rndF(500.0f) + 3500.0f;
            local_b8.z = cM_rndFX(2500.0f);
            fopAcM_create(PROC_KI, 0xFFFF0003, &local_b8, fopAcM_GetRoomNo(actor));
        }
    }
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    return TRUE;
}

/* 000037B0-000037B8       .text daBgn2_IsDelete__FP10bgn2_class */
static BOOL daBgn2_IsDelete(bgn2_class*) {
    return TRUE;
}

/* 000037B8-00003828       .text daBgn2_Delete__FP10bgn2_class */
static BOOL daBgn2_Delete(bgn2_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Bgn");
    if (i_this->m30D8 != 0) {
        hio_set = false;
        mDoHIO_deleteChild(l_HIO.mNo);
    }
    return TRUE;
}

/* 00003828-00003C60       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    J3DModelData* modelData;
    J3DAnmTevRegKey* pBrk;
    ResTIMG* pBti;
    bgn2_class* i_this = (bgn2_class*)a_this;

    i_this->mpHeadMorf = new mDoExt_McaMorf(
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
    if ((i_this->mpHeadMorf == NULL) || (i_this->mpHeadMorf->getModel() == NULL)) {
        return FALSE;
    }
    i_this->mpBodyMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Bgn", BGN_BDL_BGN_KUMO1),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Bgn", BGN_BCK_WAIT1),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );
    if ((i_this->mpBodyMorf == NULL) || (i_this->mpBodyMorf->getModel() == NULL)) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BDL_BGN_JYAKUTENA, BGN_BDL_BGN_JYAKUTENA2));
    i_this->mpJyakutenModel[2] = mDoExt_J3DModel__create(modelData, DEMO_SELECT(0x80000, 0), DEMO_SELECT(0x11000022, 0x11020203));
    if (i_this->mpJyakutenModel[2] == NULL) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BDL_BGN_JYAKUTENB, BGN_BDL_BGN_JYAKUTENB2));
    i_this->mpJyakutenModel[1] = mDoExt_J3DModel__create(modelData, DEMO_SELECT(0x80000, 0), DEMO_SELECT(0x11000022, 0x11020203));
    if (i_this->mpJyakutenModel[1] == NULL) {
        return FALSE;
    }
    i_this->mJyakutenBBrkAnm = new mDoExt_brkAnm();
#if VERSION > VERSION_DEMO
    if (i_this->mJyakutenBBrkAnm == NULL) {
        return FALSE;
    }
#endif
    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BRK_BGN_JYAKUTENBC, BGN_BRK_BGN_JYAKUTENB2));
    if (!i_this->mJyakutenBBrkAnm->init(modelData, pBrk, true, J3DFrameCtrl::EMode_LOOP)) {
        return FALSE;
    }
    modelData = (J3DModelData*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BDL_BGN_JYAKUTENC, BGN_BDL_BGN_JYAKUTENC2));
    i_this->mpJyakutenModel[0] = mDoExt_J3DModel__create(modelData, DEMO_SELECT(0x80000, 0), DEMO_SELECT(0x11000022, 0x11020203));
    if (i_this->mpJyakutenModel[0] == NULL) {
        return FALSE;
    }
    i_this->mJyakutenCBrkAnm = new mDoExt_brkAnm();
#if VERSION > VERSION_DEMO
    if (i_this->mJyakutenCBrkAnm == NULL) {
        return FALSE;
    }
#endif
    pBrk = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Bgn", DEMO_SELECT(BGN_BRK_BGN_JYAKUTENBC, BGN_BRK_BGN_JYAKUTENC2));
    if (!i_this->mJyakutenCBrkAnm->init(modelData, pBrk, true, J3DFrameCtrl::EMode_LOOP)) {
        return FALSE;
    }
    pBti = (ResTIMG*)dComIfG_getObjectRes("Bgn", BGN_BTI_NOT_CUT1);
    if (!i_this->mRedRopeMat.init(1, 0x3C, pBti, 1)) {
        return FALSE;
    }
    return TRUE;
}

/* 00003CA8-00003FF4       .text daBgn2_Create__FP10fopAc_ac_c */
static cPhs_State daBgn2_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph cc_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK8,
            /* SrcObjAt  Atp     */ 4,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNKA,
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
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNKA,
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
#if VERSION > VERSION_DEMO
    fopAcM_SetupActor(a_this, bgn2_class);
#endif
    bgn2_class* i_this = (bgn2_class*)a_this;
    cPhs_State res = dComIfG_resLoad(&i_this->mPhase, "Bgn");

    if (res == cPhs_COMPLEATE_e) {
#if VERSION == VERSION_DEMO
        fopAcM_SetupActor(a_this, bgn2_class);
#endif
        bgn = NULL;
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x96000)) {
            return cPhs_ERROR_e;
        }
        if (hio_set == false) {
            i_this->m30D8 = 1;
            hio_set = true;
            l_HIO.mNo = mDoHIO_createChild("Ｇ（タラバ）", &l_HIO); // G (King crab)
        }
        i_this->mStts.Init(0xFF, 0xFF, a_this);
        i_this->m039C.Set(cc_sph_src);
        i_this->m039C.SetStts(&i_this->mStts);
        i_this->m039C.OffAtSetBit();
        for (s32 i = 0; i < 2; i++) {
            i_this->m04C8[i].Set(cc_sph_src);
            i_this->m04C8[i].SetStts(&i_this->mStts);
            i_this->m04C8[i].OffAtSetBit();
        }
        for (s32 i = 0; i < 30; i++) {
            i_this->m0720[i].Set(cc_sph_src);
            i_this->m0720[i].SetStts(&i_this->mStts);
        }
        i_this->m2A48.Set(core_sph_src);
        i_this->m2A48.SetStts(&i_this->mStts);
        i_this->m0340 = a_this->current.pos;
        a_this->health = 3;
        a_this->max_health = 3;
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));
        i_this->mAcchCir.SetWall(50.0f, 50.0f);
#if VERSION > VERSION_DEMO
        bg_tevstr = a_this->tevStr;
#endif
        daBgn2_Execute(i_this);
    }
    return res;
}

static actor_method_class l_daBgn2_Method = {
    (process_method_func)daBgn2_Create,
    (process_method_func)daBgn2_Delete,
    (process_method_func)daBgn2_Execute,
    (process_method_func)daBgn2_IsDelete,
    (process_method_func)daBgn2_Draw,
};

actor_process_profile_definition g_profile_BGN2 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BGN2,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(bgn2_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BGN2,
    /* Actor SubMtd */ &l_daBgn2_Method,
    /* Status       */ fopAcStts_UNK4000_e | fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
