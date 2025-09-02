/**
 * d_a_btd.cpp
 * Boss - Gohma / ボスゴーマ (Boss Goma)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/d_lib.h"
#include "d/d_camera.h"
#include "d/actor/d_a_player.h"
#include "d/d_snap.h"
#include "d/d_s_play.h"
#include "d/actor/d_a_dr2.h"
#include "d/actor/d_a_kui.h"
#include "d/actor/d_a_btd.h"
#include "d/actor/d_a_ykgr.h"
#include "d/res/res_btd.h"
#include "m_Do/m_Do_ext.h"
#include "m_Do/m_Do_graphic.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "f_op/f_op_camera.h"
#include "JSystem/JUtility/JUTReport.h"

/* 000000EC-000001C8       .text __ct__11daBtd_HIO_cFv */
class daBtd_HIO_c : public JORReflexible {
public:
    daBtd_HIO_c();
    virtual ~daBtd_HIO_c() {};
    void genMessage(JORMContext*) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x07 */ u8 m07;
    /* 0x08 */ f32 m08;
    /* 0x0C */ s16 m0C;
    /* 0x0E */ s16 m0E;
    /* 0x10 */ u8 m10;
    /* 0x11 */ s8 m11;
    /* 0x12 */ s8 m12;
    /* 0x13 */ s8 m13;
    /* 0x14 */ f32 m14;
    /* 0x18 */ f32 m18;
    /* 0x1C */ f32 m1C;
    /* 0x20 */ f32 m20;
    /* 0x24 */ f32 m24;
    /* 0x28 */ f32 m28;
    /* 0x2C */ s16 m2C;
    /* 0x2E */ s16 m2E;
    /* 0x30 */ f32 m30;
    /* 0x34 */ f32 m34;
    /* 0x38 */ f32 m38;
    /* 0x3C */ s16 m3C;
    /* 0x3E */ s16 m3E;
    /* 0x40 */ s16 m40;
    /* 0x42 */ s16 m42;
    /* 0x44 */ s16 m44;
    /* 0x46 */ s16 m46;
    /* 0x48 */ f32 m48;
    /* 0x4C */ f32 m4C;
    /* 0x50 */ f32 m50;
    /* 0x54 */ u8 m54;
}; // Size: 0x54

daBtd_HIO_c::daBtd_HIO_c() {
    mNo = 0xFF;
    m05 = 0;
    m06 = 0;
    m07 = 0;
    m08 = 1.0f;
    m0C = 0x96;
    m0E = 5;
    m10 = 0;
    m14 = 100.0f;
    m18 = 0.5f;
    m1C = 0.5f;
    m20 = 0.2f;
    m24 = 0.2f;
    m2C = 10;
    m28 = 150.0f;
    m30 = 4.0f;
    m34 = 20.0f;
    m38 = 6.0f;
    m3C = 0xb6;
    m3E = 0x9c;
    m40 = 0x56;
    m42 = 0xff;
    m44 = 0x8e;
    m46 = 0x24;
    m48 = 12.0f;
    m4C = 35.0f;
    m50 = 1.0f;
    m54 = 0;
}

static kui_class* kui;
static dr2_class* dr2;
static cXyz static_center_pos;
static daBtd_HIO_c l_HIO;

static s8 joint_check[] = {-1,   0x05, -1,   -1,   0x11, -1,   -1,   -1,   -1, -1, 0x12, -1,   -1, -1,   0x06, -1,  -1,   -1,   -1,
                           -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1,   -1, -1, -1,   -1,   -1, 0x04, -1,   -1,  0x0D, -1,   -1,
                           0x0F, -1,   -1,   0x0E, -1,   -1,   0x11, 0x03, -1, -1, 0x0B, -1,   -1, 0x0C, -1,   -1,  -1,   0x02, -1,
                           -1,   -1,   0x64, -1,   0x00, 0x01, 0x65, 0x66, -1, -1, 0x07, 0x08, -1, -1,   0x09, 0x0A};

/* 000001C8-0000024C       .text wave_set__FP9btd_class */
void wave_set(btd_class* i_this) {
    mDoAud_seStart(JA_SE_CM_BTD_MAGMA_MOVE, &static_center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
    i_this->m6E7C = 0.0f;
}

/* 0000024C-00000268       .text get_anm__FP9btd_class */
mDoExt_McaMorf* get_anm(btd_class* i_this) {
    if (i_this->m02E0 != 0) {
        return i_this->m02C8;
    }
    return i_this->m02BC;
}

/* 00000268-00000284       .text get_btk__FP9btd_class */
mDoExt_btkAnm* get_btk(btd_class* i_this) {
    if (i_this->m02E0 != 0) {
        return i_this->btkS;
    }
    return i_this->btk;
}

/* 00000284-000002A0       .text get_brk__FP9btd_class */
mDoExt_brkAnm* get_brk(btd_class* i_this) {
    if (i_this->m02E0 != 0) {
        return i_this->brkS;
    }
    return i_this->brk;
}

/* 000002A0-000003D4       .text anm_init__FP9btd_classifUcfi */
void anm_init(btd_class* i_this, int bckFileIdx, f32 morf, u8 loopMode, f32 speed, int soundFileIdx) {
    void* pSoundAnimRes;
    J3DAnmTransform* pJVar1;

    mDoExt_McaMorf* btdAnm = get_anm(i_this);
    if (soundFileIdx >= 0) {
        pSoundAnimRes = dComIfG_getObjectRes("Btd", soundFileIdx);
        pJVar1 = (J3DAnmTransform*)dComIfG_getObjectRes("Btd", bckFileIdx);
        btdAnm->setAnm(pJVar1, loopMode, morf, speed, 0.0f, -1.0f, pSoundAnimRes);
    } else {
        pJVar1 = (J3DAnmTransform*)dComIfG_getObjectRes("Btd", bckFileIdx);
        btdAnm->setAnm(pJVar1, loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 000003D4-00000778       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 jntNo = joint->getJntNo();
        int r28 = joint_check[jntNo];
        J3DModel* model = j3dSys.getModel();
        btd_class* i_this = (btd_class*)model->getUserArea();
        if ((i_this != NULL) && (r28 >= 0)) {
            cXyz local_38;
            MTXCopy(model->getAnmMtx(jntNo), *calc_mtx);
            if (r28 == 100) {
                local_38.x = REG0_F(9);
                local_38.y = REG0_F(10);
                local_38.z = REG0_F(11);
                MtxPosition(&local_38, &i_this->m03E0);
                if (i_this->m6E4C == 0) {
                    i_this->eyePos = i_this->m03E0;
                    i_this->attention_info.position = i_this->eyePos;
                    i_this->attention_info.position.y += 50.0f;
                }
                local_38.x = REG0_F(9);
                local_38.y = REG0_F(10) + -50.0f;
                local_38.z = REG0_F(11) + 200.0f;
                MtxPosition(&local_38, &i_this->m60B0.mPos);
                mDoMtx_YrotM(*calc_mtx, i_this->m5E8E);
                model->setAnmMtx(jntNo, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            } else if ((r28 == 0x65) || (r28 == 0x66)) {
                if (r28 == 0x65) {
                    mDoMtx_XrotM(*calc_mtx, i_this->m02FA);
                } else {
                    mDoMtx_XrotM(*calc_mtx, i_this->m02FA * -0.6818f);
                }
                model->setAnmMtx(jntNo, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            } else {
                if (r28 <= 1) {
                    local_38.x = 0.0f;
                    local_38.y = 0.0f;
                    local_38.z = 300.0f;
                } else if (r28 == 2) {
                    local_38.x = REG0_F(0);
                    local_38.y = REG0_F(1) + 50.0f;
                    local_38.z = REG0_F(2) + -100.0f;
                } else if (r28 == 8) {
                    local_38.x = REG0_F(5) + 350.0f;
                    local_38.y = 100.0f;
                    local_38.z = 0.0f;
                } else if (r28 == 10) {
                    local_38.x = -(REG0_F(5) + 350.0f);
                    local_38.y = -100.0f;
                    local_38.z = 0.0f;
                } else {
                    local_38.x = REG0_F(6);
                    local_38.y = REG0_F(7);
                    local_38.z = REG0_F(8);
                }
                MtxPosition(&local_38, &i_this->m02FC[r28]);
            }
            if (r28 == 2) {
                mDoMtx_YrotM(*calc_mtx, i_this->m5E88);
                mDoMtx_XrotM(*calc_mtx, i_this->m5E8A);
                mDoMtx_ZrotM(*calc_mtx, i_this->m5E88);
                model->setAnmMtx(jntNo, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            }
        }
    }
    return TRUE;
}

/* 000007B4-00000828       .text hahen_draw__FP9btd_class */
void hahen_draw(btd_class* i_this) {
    btd_hahen_s* pbVar2 = &i_this->hahen[0];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->hahen); i++, pbVar2++) {
        if (pbVar2->m04 != 0) {
            g_env_light.setLightTevColorType(pbVar2->model, &i_this->tevStr);
            mDoExt_modelUpdate(pbVar2->model);
        }
    }
}

/* 00000828-000009B4       .text daBtd_Draw__FP9btd_class */
static BOOL daBtd_Draw(btd_class* i_this) {
    J3DModel* model;
    fopAc_ac_c* actor = i_this;

    u8 bVar1 = i_this->m6E15;
    if (bVar1 > 1) {
        mDoGph_gInf_c::mBlureRate = bVar1;
        mDoGph_gInf_c::onBlure();
    } else if (bVar1 == 1) {
        i_this->m6E15 = 0;
        mDoGph_gInf_c::offBlure();
    }
    dSnap_RegistFig(DSNAP_TYPE_BTD, actor, actor->eyePos, actor->current.angle.y, 1.0f, 1.0f, 1.0f);
    if (i_this->m6E4C != 0) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->m6E50, &i_this->tevStr);
        model = i_this->m02D4->getModel();
        g_env_light.setLightTevColorType(model, &i_this->tevStr);
        i_this->m02D8->entry(model->getModelData());
        i_this->m02DC->entry(model->getModelData());
        i_this->m02D4->entryDL();
    } else {
        mDoExt_McaMorf* morf = get_anm(i_this);
        mDoExt_btkAnm* btk = get_btk(i_this);
        mDoExt_brkAnm* brk = get_brk(i_this);
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &actor->eyePos, &i_this->tevStr);
        model = morf->getModel();
        g_env_light.setLightTevColorType(model, &i_this->tevStr);
        btk->entry(model->getModelData());
        brk->entry(model->getModelData());
        morf->entryDL();
        hahen_draw(i_this);
    }
    return TRUE;
}

/* 000009B4-00000A08       .text player_view_check__FP9btd_class */
u16 player_view_check(btd_class* i_this) {
    s16 uVar1;
    s16 sVar2;

    sVar2 = fopAcM_searchActorAngleY(i_this, dComIfGp_getPlayer(0));
    sVar2 = i_this->current.angle.y - sVar2;
    uVar1 = sVar2;
    if (uVar1 < 0) {
        uVar1 = -sVar2;
    }
    return uVar1;
}

/* 00000A08-00000A38       .text eff_off__FP9btd_class */
void eff_off(btd_class* i_this) {
    for (int i = 0; i < 7; i++) {
        if (i_this->m6028[i] > 2) {
            i_this->m6028[i] = 2;
        }
    }
}

/* 00000A38-00000C14       .text hahen_set2__FP9btd_class */
void hahen_set2(btd_class* i_this) {
    cXyz local_1c;

    local_1c.x = i_this->m02FC[8].x;
    local_1c.y = i_this->m02FC[8].y;
    local_1c.z = i_this->m02FC[8].z;
    local_1c.y = i_this->m02FC[8].y - (REG0_F(14) + 100.0f);
    dComIfGp_particle_set(dPa_name::ID_SCENE_80AA, &local_1c);
    local_1c.x = i_this->m02FC[10].x;
    local_1c.y = i_this->m02FC[10].y;
    local_1c.z = i_this->m02FC[10].z;
    local_1c.y = i_this->m02FC[10].y - (REG0_F(14) + 100.0f);
    dComIfGp_particle_set(dPa_name::ID_SCENE_80AA, &local_1c);
    mDoAud_seStart(JA_SE_CM_BTD_ARM_STRIKE, &i_this->m02FC[8], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
    mDoAud_seStart(JA_SE_CM_BTD_ARM_STRIKE, &i_this->m02FC[10], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
    dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
}

/* 00000C14-00000D84       .text hahen_set_s__FP9btd_classP4cXyzP5csXyz */
void hahen_set_s(btd_class* i_this, cXyz* param_2, csXyz* param_3) {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Always", ALWAYS_BDL_MPI_KOISHI));
    J3DAnmTexPattern* anmTexPattern = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("Always", ALWAYS_BTP_MPI_KOISHI));
    JPABaseEmitter* emitter = (JPABaseEmitter*)dComIfGp_particle_set(dPa_name::ID_SCENE_80A8, param_2, param_3);
    if (emitter != NULL) {
        emitter->mGlobalParticleScale.x = 4.0f;
        emitter->mGlobalParticleScale.y = 4.0f;
        emitter->mGlobalParticleScale.z = 4.0f;
        dPa_J3DmodelEmitter_c* modelEmitter = new dPa_J3DmodelEmitter_c(emitter, modelData, i_this->tevStr, anmTexPattern, 1, 0);
        if (modelEmitter != NULL) {
            dComIfGp_particle_addModelEmitter(modelEmitter);
        }
    }
    dComIfGp_particle_set(dPa_name::ID_SCENE_80A9, param_2);
}

/* 00000D84-00000E44       .text smoke_set_s__FP9btd_classP4cXyzP5csXyz */
void smoke_set_s(btd_class* i_this, cXyz* param_2, csXyz* param_3) {
    dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0AB, param_2, param_3, NULL, 0xB9, &i_this->mPa_SmokeEcallBack[0], fopAcM_GetRoomNo(i_this));
    dComIfGp_particle_setToon(dPa_name::ID_SCENE_A0AC, param_2, param_3, NULL, 0xB9, &i_this->mPa_SmokeEcallBack[1], fopAcM_GetRoomNo(i_this));
}

/* 00000E44-00000F14       .text hahen_set__FP9btd_classSc */
void hahen_set(btd_class* i_this, s8 param_2) {
    int iVar1;

    i_this->m6048 = i_this->current.angle;
    if (param_2 != 0) {
        iVar1 = 10;
        i_this->m6048.y += 0x4000;
    } else {
        iVar1 = 8;
        i_this->m6048.y += -0x4000;
    }
    i_this->m603C = i_this->m02FC[iVar1];
    i_this->m603C.y -= (REG0_F(14) + 100.0f);
    hahen_set_s(i_this, &i_this->m603C, &i_this->m6048);
    smoke_set_s(i_this, &i_this->m603C, &i_this->m6048);
}

/* 00000F14-00001398       .text startdemo__FP9btd_class */
void startdemo(btd_class* i_this) {
    cXyz local_30;
    cXyz local_3c;
    cXyz local_48;

    daPy_py_c* apdVar3 = daPy_getPlayerActorClass();
    i_this->m02F0 = 30;
    i_this->current.angle.y = fopAcM_searchActorAngleY(i_this, daPy_getPlayerActorClass());
    local_30.x = -1534.0f;
    local_30.y = 0.0f;
    local_30.z = 909.0f;
    local_3c = apdVar3->current.pos - local_30;
    switch (i_this->mGohmaState) {
    case 0:
        if (i_this->m6E16 == 0) {
            i_this->mKankyoState = 6;
            i_this->m6E88 = 0;
            i_this->current.pos.y = -10000.0f;
            if (i_this->eventInfo.checkCommandDemoAccrpt()) {
                i_this->m6E16 = 1;
                mDoAud_bgmStreamPlay();
            } else if (local_3c.abs() > REG0_F(13) + 200.0f) {
                fopAcM_orderPotentialEvent(i_this, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
                i_this->eventInfo.onCondition(dEvtCnd_UNK2_e);
            }
        }
        break;
    case 1:
        i_this->mKankyoState = 8;
        anm_init(i_this, BTD_BCK_SSTART, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->current.pos.y = i_this->home.pos.y;
        i_this->mGohmaState = 2;
        fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_ENTER, 0);
        local_48.x = 0.0f;
        local_48.y = 0.0f;
        local_48.z = 0.0f;
        dComIfGp_particle_set(dPa_name::ID_SCENE_80BD, &local_48, &i_this->current.angle);
        break;
    case 2:
        if (i_this->m6E1A <= 0x46) {
            i_this->mKankyoState = 8;
        }
        if ((i_this->m6E1A == 0x28) || (i_this->m6E1A == 0xDC)) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_AFT_DAMAGE, 0);
        }
        if (i_this->m6E1A == 0xD7) {
            wave_set(i_this);
            i_this->m6E48 = 40.0f;
            hahen_set2(i_this);
        }
        if (((i_this->m6E1A >= 0x46) && (i_this->m6E1A <= 0xC3)) && (i_this->m602E = 3, i_this->m6E1A >= 0x5A)) {
            mDoAud_seStart(JA_SE_CM_BTD_HIFUKI, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            i_this->mKankyoState = 2;
        }
        if (i_this->m6E1A >= 0x46) {
            i_this->m602C = 3;
        }
        if ((i_this->m02BC->isStop()) && (REG0_F(7) == 0.0f)) {
            i_this->m6E16 = 0x96;
            i_this->m02E4 = 0;
            i_this->mGohmaState = 0;
            i_this->m02EC[0] = (s16)(cM_rndF(50.0f) + 70.0f);
            if (dComIfGp_getStartStageName()[0] == 'X') {
                mDoAud_bgmStart(JA_BGM_PAST_GOMA);
            } else {
                mDoAud_bgmStart(JA_BGM_GOMA);
            }
            g_dComIfG_gameInfo.save.getMemory().getBit().onStageBossDemo();
        }
        break;
    }
}

/* 00001398-00001898       .text damage_check__FP9btd_class */
void damage_check(btd_class* i_this) {
    cCcD_Obj* pcVar2;
    short sVar4;
    u32 uVar7;
    dCcD_GObjInf* pdVar9;
    csXyz local_48;
    cXyz local_40;
    CcAtInfo local_34;

    if ((i_this->m02F6 != 0) && (i_this->m02F6 == 1)) {
        i_this->m02F6 = 2;
        i_this->m02E4 = 2;
        i_this->mGohmaState = 0x14;
        fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_DMG_ROCK, 0);
        eff_off(i_this);
        return;
    }
    if ((i_this->m1A6C.ChkTgHit()) && (i_this->m02E0 == 0 && (i_this->mActionState == 0))) {
        i_this->mActionState = 10;
        pcVar2 = i_this->m1A6C.GetTgHitObj();
        def_se_set(i_this, pcVar2, 0x40);
    }
    if (((i_this->m1A6C.ChkTgHit()) && (i_this->m02E0 == 1)) && (i_this->m1A6C.OnTgNoConHit(), i_this->mActionState == 0)) {
        i_this->mActionState = 7;
        local_34.mpObj = i_this->m1A6C.GetTgHitObj();
        local_34.pParticlePos = i_this->m1A6C.GetTgHitPosP();
        at_power_check(&local_34);
        i_this->mTotalDamage = i_this->mTotalDamage + local_34.mDamage;
        i_this->health = i_this->health - local_34.mDamage;
        if ((i_this->health <= 0) || (l_HIO.m06 != 0)) {
            dScnPly_ply_c::nextPauseTimer = REG0_S(7) + 8;
            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &i_this->m03E0);
            local_40.z = 2.0f;
            local_40.y = 2.0f;
            local_40.x = 2.0f;
            local_48.z = 0;
            local_48.x = 0;
            local_48.y = fopAcM_searchActorAngleY(i_this, daPy_getPlayerActorClass());
            dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &i_this->m03E0, &local_48, &local_40);
            i_this->m02E4 = 0xb;
            i_this->mGohmaState = 0x32;
            mDoAud_seStart(JA_SE_LK_LAST_HIT, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            return;
        }
        if (i_this->m02E4 == 2) {
            if (i_this->mTotalDamage >= l_HIO.m0E) {
                i_this->mGohmaState = 10;
                i_this->mTotalDamage = 0;
            } else {
                uVar7 = BTD_BCK_HIT_M;
                if (local_34.mResultingAttackType == 1) {
                    sVar4 = fopAcM_searchActorAngleY(i_this, daPy_getPlayerActorClass());
                    sVar4 = sVar4 - i_this->current.angle.y;
                    if ((sVar4 > -0x100) && (sVar4 < 0x100)) {
                        uVar7 = BTD_BCK_HIT_M;
                    } else if (sVar4 > 0) {
                        uVar7 = BTD_BCK_HIT_R;
                    } else {
                        uVar7 = BTD_BCK_HIT_L;
                    }
                }
                anm_init(i_this, uVar7, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mGohmaState = 3;
            }
        } else {
            i_this->m02E4 = 2;
            i_this->mGohmaState = 0;
        }
        fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_DAMAGE, 0);
        eff_off(i_this);
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m0428); i++) {
        if (i_this->m5FC4[i] == 0) {
            pdVar9 = &i_this->m0428[i];
            if (pdVar9->ChkTgHit()) {
                i_this->m0428[i].OnTgNoConHit();
                i_this->m5FC4[i] = 10;
                i_this->m5E98[i] = i_this->m02FC[i];
                pcVar2 = pdVar9->GetTgHitObj();
                def_se_set_p(i_this, &i_this->m5E98[i], pcVar2, 0x42);
                break;
            }
        } else {
            i_this->m5FC4[i]--;
        }
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m575C); i++) {
        if (i_this->m5FEA[i] == 0) {
            if (i_this->m575C[i].ChkTgHit()) {
                i_this->m575C[i].OnTgNoConHit();
                i_this->m5FEA[i] = 10;
                def_se_set_p(i_this, &i_this->m5E98[i + 0x13], i_this->m575C[i].GetTgHitObj(), 0x42);
                return;
            }
        } else {
            i_this->m5FEA[i]--;
        }
    }
}

/* 00001898-000019D8       .text sibuki_set__FP9btd_class */
void sibuki_set(btd_class* i_this) {
    cXyz local_38;

    btd_sibuki_s* pbVar2 = &i_this->mBtdSibukiS[0];
    i_this->m6E14 = 0;
    local_38.x = 0.0f;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mBtdSibukiS); i++, pbVar2++) {
        if (pbVar2->m00 == 0) {
            pbVar2->m00 = 1;
            mDoMtx_YrotS(*calc_mtx, cM_rndFX(32768.0f));
            local_38.z = REG0_F(13) + (cM_rndFX(200.0f) + 300.0f);
            local_38.y = cM_rndF(50.0f);
            MtxPosition(&local_38, &pbVar2->m04);
            local_38.z = l_HIO.m48 + cM_rndF(l_HIO.m48 * 0.5f);
            local_38.y = l_HIO.m4C + cM_rndF(l_HIO.m4C * 0.5f);
            MtxPosition(&local_38, &pbVar2->m10);
            mDoMtx_YrotS(*calc_mtx, cM_rndFX(32768.0f));
        }
    }
}

/* 000019D8-00001A84       .text kubi_calc__FP9btd_class */
void kubi_calc(btd_class* i_this) {
    MtxTrans(i_this->m6E50.x, i_this->m6E50.y, i_this->m6E50.z, false);
    mDoMtx_YrotM(*calc_mtx, i_this->m6E74.y);
    mDoMtx_XrotM(*calc_mtx, i_this->m6E74.x);
    mDoMtx_ZrotM(*calc_mtx, i_this->m6E74.z);
    J3DModel* model = i_this->m02D4->getModel();
    MTXCopy(*calc_mtx, model->getBaseTRMtx());
    i_this->m02D4->calc();
    i_this->m02D8->play();
    i_this->m02DC->play();
}

/* 00001A84-000028C4       .text damage__FP9btd_class */
s32 damage(btd_class* i_this) {
    /* Nonmatching - regalloc */
    static s32 hibi_brk[] = {BTD_BRK_HIBI01, BTD_BRK_HIBI02, BTD_BRK_HIBI03};
    static u16 hibi_eff_name[] = {dPa_name::ID_SCENE_80C8, dPa_name::ID_SCENE_80C9, dPa_name::ID_SCENE_80CA};
    static u16 hahen_eff_name[] = {
        dPa_name::ID_SCENE_80C4,
        dPa_name::ID_SCENE_80C4,
        dPa_name::ID_SCENE_80C4,
        dPa_name::ID_SCENE_80C4,
        dPa_name::ID_SCENE_80C5,
        dPa_name::ID_SCENE_80C5,
        dPa_name::ID_SCENE_80C5,
        dPa_name::ID_SCENE_80C5,
        dPa_name::ID_SCENE_80C6,
        dPa_name::ID_SCENE_80C7,
        dPa_name::ID_SCENE_80C7,
        dPa_name::ID_SCENE_80C7
    };
    static s32 hahen_eff_index[] = {0x2E, 0x21, 0x24, 0x42, 0x31, 0x27, 0x2A, 0x46, 0x37, 0x20, 0x2D, 0x34};
    int state;
    mDoExt_McaMorf* iVar2;
    J3DAnmTevRegKey* pJVar2;
    int iVar3;
    JPABaseEmitter* pJVar4;
    J3DModel* pJVar8;
    cXyz local_58;

    iVar2 = get_anm(i_this);
    state = 1;
    i_this->m02F0 = 5;
    if (i_this->mGohmaState >= 10) {
        i_this->mActionState = 10;
    }
    if (i_this->mGohmaState <= 0xb) {
        state = 0;
    }
    switch (state) {
    case 0:
        anm_init(i_this, BTD_BCK_DAMAGE1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mGohmaState++;
    case 1:
        if (iVar2->isStop()) {
            anm_init(i_this, BTD_BCK_DAMAGE2, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mStunTimer = l_HIO.m0C;
            i_this->mGohmaState++;
        }
        break;
    case 2:
        if (i_this->mStunTimer == 0) {
            i_this->m02E4 = 0;
            i_this->mGohmaState = 0;
            i_this->m02EC[0] = cM_rndF(50.0f) + 50.0f;
        }
        break;
    case 3:
        if (iVar2->isStop()) {
            anm_init(i_this, BTD_BCK_DAMAGE2, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->mGohmaState = 2;
        }
        break;
    case 10:
        anm_init(i_this, BTD_BCK_DAMAGE3, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mGohmaState++;
        fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_AFT_DAMAGE, 0);
    case 0xb:
        if (iVar2->isStop()) {
            i_this->m02E4 = 0;
            i_this->mGohmaState = 0;
            i_this->m02EC[0] = cM_rndF(50.0f) + 50.0f;
        }
        break;
    case 0x14:
        anm_init(i_this, BTD_BCK_SIZUMU1, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mGohmaState++;
        i_this->m6E7C = 0.0f;
        break;
    case 0x15:
        if (iVar2->isStop()) {
            anm_init(i_this, BTD_BCK_SIZUMU2, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m02EC[0] = (REG0_S(7) + 0x14) * 5;
            i_this->mGohmaState++;
        }
    case 0x16:
        if (i_this->m02EC[0] == REG0_S(5) + 0x28) {
            pJVar8 = iVar2->getModel();
            pJVar2 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Btd", hibi_brk[i_this->m6190]);
            i_this->brk->init(pJVar8->getModelData(), pJVar2, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, 0);
            i_this->m6190++;
            mDoAud_seStart(JA_SE_CM_BTD_BRK_SHIELD_S, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            for (int i = 0, j = 0; i < 3; i++, j++) {
                pJVar4 = dComIfGp_particle_set(hibi_eff_name[j], &i_this->current.pos);
                if (pJVar4 != NULL) {
                    pJVar4->setGlobalRTMatrix(iVar2->getModel()->getAnmMtx(0x37));
                }
            }
            if (l_HIO.m06 != 0) {
                i_this->m6190 = 3;
            }
            if ((l_HIO.m07 != 0) && (i_this->m6190 >= 3)) {
                i_this->m6190 = 2;
            }
        }
        if (i_this->m02EC[0] == 0) {
            if (i_this->m6190 >= 3) {
                i_this->mGohmaState = 0x28;
            } else {
                anm_init(i_this, BTD_BCK_SIZUMU3, 15.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mGohmaState++;
                static_center_pos.setall(0.0f);
                mDoAud_seStart(JA_SE_CM_BTD_INTO_MAGMA_N, &static_center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
                fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_WAIT, 0);
                i_this->m6E7C = 0.0f;
                i_this->m02EC[0] = 0x96;
            }
        }
        break;
    case 0x17:
        if ((i_this->m02EC[0] == 1) || (i_this->m02EC[0] == 0x46)) {
            i_this->m6E7C = 0.0f;
        }
        if (iVar2->isStop()) {
            i_this->mGohmaState = 0x1e;
            i_this->m02EC[0] = 0;
        }
        break;
    case 0x1e:
        i_this->m6E88 = 0;
        if (i_this->m02EC[0] == 0) {
            anm_init(i_this, BTD_BCK_MOTIAGE1, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            i_this->m02F6 = 0;
            mDoAud_seStart(JA_SE_CM_BTD_ENT_BLAST, &static_center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_ENTER, 0);
            i_this->m02EC[0] = 0x3c;
            i_this->m6E7C = 0.0f;
            i_this->mKankyoTimer = 0x14;
        }
        break;
    case 0x1f:
        if (i_this->m02EC[0] == 0x37) {
            sibuki_set(i_this);
        }
        if (i_this->m02EC[0] == 1) {
            i_this->m6E7C = 0.0f;
        }
        if (iVar2->isStop()) {
            anm_init(i_this, BTD_BCK_MOTIAGE2, 1.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            mDoAud_seStart(JA_SE_CM_BTD_LIFT_UP, &static_center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            i_this->m6E7C = 0.0f;
        }
        break;
    case 0x20:
        i_this->m6E88 = 0;
        if (iVar2->isStop()) {
            anm_init(i_this, BTD_BCK_MOTIAGE3, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            dr2_class* dr2Var = dr2;
            mDoAud_seStart(JA_SE_CM_BTD_JUMP_DOWN, &dr2Var->unk_4A8, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            dComIfGp_particle_set(dPa_name::ID_SCENE_80BC, &i_this->current.pos, &i_this->current.angle);
            i_this->mGohmaState++;
            i_this->m02EC[0] = 0x1e;
        }
        break;
    case 0x21:
        if (i_this->m02EC[0] == 0x14) {
            mDoAud_seStart(JA_SE_CM_BTD_LANDING, &static_center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            i_this->m6E7C = 0.0f;
            sibuki_set(i_this);
        }
        if (iVar2->isStop()) {
            i_this->m02E4 = 0;
            i_this->mGohmaState = 0;
            i_this->m02EC[0] = cM_rndF(50.0f) + 50.0f;
        }
        break;
    case 0x28:
        anm_init(i_this, BTD_BCK_WARERU1, 3.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mGohmaState++;
        mDoAud_seStart(JA_SE_CM_BTD_FALL_FWD, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        mDoAud_bgmStop(30);
        i_this->m02EC[0] = 0x96;
        i_this->m6E7C = 0.0f;
    case 0x29:
        if (i_this->m02EC[0] == (s16)(REG0_S(5) + 0x26)) {
            dr2->unk_4BA = 10;
            if (dComIfGp_getStartStageName()[0] == 'X') {
                mDoAud_bgmStart(JA_BGM_PAST_GOMA_2);
            } else {
                mDoAud_bgmStart(JA_BGM_GOMA_2);
            };
            btd_hahen_s* pbVar10 = &i_this->hahen[0];
            for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->hahen); i++, pbVar10++) {
                if (pbVar10->m04 == 0) {
                    if (i < 5) {
                        iVar3 = 2;
                    } else {
                        iVar3 = cM_rndF(18.999f);
                    }
                    pbVar10->m04 = 1;
                    pbVar10->m08.x = i_this->m02FC[iVar3].x;
                    pbVar10->m08.y = i_this->m02FC[iVar3].y;
                    pbVar10->m08.z = i_this->m02FC[iVar3].z;
                    pbVar10->m08.x = pbVar10->m08.x + cM_rndFX(REG0_F(2) + 50.0f);
                    pbVar10->m08.y = pbVar10->m08.y + cM_rndFX(REG0_F(2) + 50.0f);
                    pbVar10->m08.z = pbVar10->m08.z + cM_rndFX(REG0_F(2) + 50.0f);
                    mDoMtx_YrotS(*calc_mtx, ((short)cM_rndFX(2000.0f) + cM_atan2s(pbVar10->m08.x, pbVar10->m08.z)));
                    local_58.x = 0.0f;
                    local_58.y = REG0_F(1) + (cM_rndF(5.0f) + 20.0f);
                    local_58.z = REG0_F(0) + (cM_rndF(5.0f) + 20.0f);
                    MtxPosition(&local_58, &pbVar10->m14);
                    pbVar10->m22 = cM_rndF(65536.0f);
                    pbVar10->m20 = cM_rndF(65536.0f);
                }
            }
            for (s32 i = 0, j = 0, k = 0; i < (s32)ARRAY_SIZE(hahen_eff_name); i++, j++, k++) {
                pJVar4 = dComIfGp_particle_set(hahen_eff_name[k], &i_this->current.pos);
                if (pJVar4 != NULL) {
                    pJVar4->setGlobalRTMatrix(iVar2->mpModel->getAnmMtx(hahen_eff_index[j]));
                }
            }
        }
        if (i_this->m02EC[0] == 0x65) {
            mDoAud_seStart(JA_SE_CM_BTD_GET_UP, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_ENTER, 0);
        }
        if (iVar2->isStop()) {
            mDoAud_seStart(JA_SE_CM_BTD_BRK_SHIELD_L, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_AFT_DAMAGE, 0);
            i_this->m02E0 = 1;
            anm_init(i_this, BTD_BCK_WARERU2, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
        }
        break;
    case 0x2a:
        if (iVar2->isStop()) {
            i_this->m02E4 = 0;
            i_this->mGohmaState = 0;
            i_this->m02EC[0] = cM_rndF(50.0f) + 50.0f;
        }
    }
    return state;
}

/* 000028C4-000036A0       .text end__FP9btd_class */
void end(btd_class* i_this) {
    /* Nonmatching - regalloc, branching */
    static u16 last_eff_name[] = {
        dPa_name::ID_SCENE_80D2,
        dPa_name::ID_SCENE_80D3,
        dPa_name::ID_SCENE_80D4,
        dPa_name::ID_SCENE_80D0,
        dPa_name::ID_SCENE_80D0,
        dPa_name::ID_SCENE_80D0,
        dPa_name::ID_SCENE_80D0,
        dPa_name::ID_SCENE_80D0,
        dPa_name::ID_SCENE_80D0,
        dPa_name::ID_SCENE_80D0,
        dPa_name::ID_SCENE_80D0,
        dPa_name::ID_SCENE_80D1,
        dPa_name::ID_SCENE_80D1,
        dPa_name::ID_SCENE_80D1,
        dPa_name::ID_SCENE_80D1,
        dPa_name::ID_SCENE_80D1,
        dPa_name::ID_SCENE_80D1,
        dPa_name::ID_SCENE_80D1,
        dPa_name::ID_SCENE_80D1
    };
    static s32 last_eff_index[] = {0x20, 0x2D, 0x34, 0x42, 0x43, 0x2E, 0x2F, 0x21, 0x22, 0x24, 0x25, 0x46, 0x47, 0x31, 0x32, 0x27, 0x28, 0x2A, 0x2B};
    mDoExt_McaMorf* iVar2;
    J3DMaterialTable* pJVar2;
    J3DAnmTevRegKey* pJVar3;
    J3DAnmTextureSRTKey* pJVar4;
    JPABaseEmitter* pJVar6;
    J3DModel* pJVar10;
    float fVar13;
    cXyz local_2c;

    iVar2 = get_anm(i_this);
    i_this->mActionState = 10;
    switch (i_this->mGohmaState) {
    case 0x32:
        if (dComIfGp_getStartStageName()[0] == 'X') {
            dLib_setNextStageBySclsNum(0, i_this->current.roomNo);
            mDoAud_seStart(JA_SE_LK_B_BOSS_WARP, NULL, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            dComIfGs_onEventBit(0x3240);
            dComIfGs_onTmpBit(0x480);
            mDoAud_bgmStop(30);
        } else {
            i_this->mGohmaState = 0x33;
            anm_init(i_this, BTD_BCK_DEAD, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m6E16 = 100;
            i_this->m6E1A = 0;
            i_this->m6E18 = 0;
            i_this->m02EC[0] = REG0_S(3) + 0x21c;
            mDoAud_bgmStop(20);
            mDoAud_bgmStreamPrepare(JA_STRM_BOSS_CLEAR);
            pJVar10 = iVar2->mpModel;
            pJVar2 = (J3DMaterialTable*)dComIfG_getObjectRes("Btd", BTD_BMT_DEADA);
            pJVar10->getModelData()->setMaterialTable(pJVar2, J3DMatCopyFlag_Material);
            pJVar3 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Btd", BTD_BRK_DEADA);
            i_this->brkS->init(pJVar10->getModelData(), pJVar3, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            pJVar4 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Btd", BTD_BTK_DEADA);
            i_this->btkS->init(pJVar10->getModelData(), pJVar4, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            wave_set(i_this);
        }
        break;
    case 0x33:
        if (i_this->m6E1A == 3) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_AFT_DAMAGE, 0);
        }
        if (i_this->m6E1A == 0x40) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_DMG_ROCK, 0);
            wave_set(i_this);
        }
        if (i_this->m6E1A == 0x78) {
            mDoAud_seStart(JA_SE_CM_BTD_BECOME_BLACK, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            wave_set(i_this);
        }
        if (i_this->m6E1A == 0xa0) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_AFT_JITABATA, 0);
        }
        if (i_this->m6E1A == 200) {
            static_center_pos.set(0.0f, 300.0f, 0.0f);
            mDoAud_seStart(JA_SE_CM_BTD_ENDURE, &static_center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_DIE, 0);
        }
        if (i_this->m6E1A == 0x136) {
            mDoAud_seStart(JA_SE_CM_BTD_BECOME_RED, &static_center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        }
        if (i_this->m02EC[0] == 0x65) {
            mDoAud_bgmStreamPlay();
            i_this->current.pos.y = -10000.0f;
            i_this->m6E4C = 1;
            i_this->m6E50 = i_this->eyePos;
            i_this->m6E74 = i_this->current.angle;
            i_this->m6E16++;
            i_this->m6E1A = 0;
            i_this->m6E40 = 0.0f;
            i_this->mGohmaState++;
            i_this->speedF = 30.0f;
            i_this->m02EC[0] = 0x46;
            mDoAud_seStart(JA_SE_CM_BTD_LAST_EXPLODE, &static_center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            pJVar6 = dComIfGp_particle_set(dPa_name::ID_SCENE_80DE, &i_this->m6E50);
            i_this->m6038 = pJVar6;
            i_this->m6E48 = 30.0f;
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
            i_this->m6E15 = 0xb4;
        } else {
            if (i_this->m02EC[0] == 0x1cc) {
                i_this->m02E0 = 2;
            }
            if (i_this->m02EC[0] == 0xf1) {
                pJVar10 = iVar2->mpModel;
                pJVar3 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Btd", BTD_BRK_DEADB);
                i_this->brkS->init(pJVar10->getModelData(), pJVar3, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
                pJVar4 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Btd", BTD_BTK_DEADB);
                i_this->btkS->init(pJVar10->getModelData(), pJVar4, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            }
            if (i_this->m02EC[0] == 0xbf) {
                for (s32 i = 0; i < (s32)ARRAY_SIZE(last_eff_index); i++) {
                    pJVar6 = dComIfGp_particle_set(last_eff_name[i], &i_this->current.pos);
                    if (pJVar6 != NULL) {
                        pJVar6->setGlobalRTMatrix(iVar2->mpModel->getAnmMtx(last_eff_index[i]));
                    }
                }
            }
        }
        break;
    case 0x34:
        i_this->m6E88 = 0;
        local_2c = i_this->m6E5C - i_this->m6E50;
        fVar13 = std::sqrtf(local_2c.x * local_2c.x + local_2c.z * local_2c.z);
        local_2c.y += fVar13 * (REG0_F(14) + 3.5f);
        i_this->m6E74.y = cM_atan2s(local_2c.x, local_2c.z);
        mDoMtx_YrotS(*calc_mtx, -cM_atan2s(local_2c.y, std::sqrtf(local_2c.x * local_2c.x + local_2c.z * local_2c.z)));
        mDoMtx_XrotM(*calc_mtx, i_this->m6E74.y);
        local_2c.x = 0.0f;
        local_2c.y = 0.0f;
        local_2c.z = i_this->speedF;
        MtxPosition(&local_2c, &i_this->m6E68);
        i_this->m6E50 += i_this->m6E68;
        if (i_this->m6E68.y < 0.0f) {
            cLib_addCalc2(&i_this->speedF, 300.0f, 1.0f, 2.0f);
        }
        i_this->eyePos = i_this->m6E50;
        local_2c = i_this->m6E5C - i_this->m6E50;
        fVar13 = local_2c.abs();
        if (fVar13 < i_this->speedF * 2.0f) {
            i_this->mGohmaState = 0x35;
        }
        break;
    case 0x35:
        i_this->m6E88 = 0;
        cLib_addCalc2(&i_this->m6E50.x, i_this->m6E5C.x, 1.0f, std::fabsf(i_this->m6E68.x));
        i_this->m6E50.y = i_this->m6E50.y + i_this->m6E68.y;
        i_this->m6E68.y = i_this->m6E68.y - (REG0_F(3) + 5.0f);
        if (i_this->m6E50.y <= i_this->m6E5C.y) {
            i_this->m6E50.y = i_this->m6E5C.y;
            if (i_this->m6E68.y < -50.0f) {
                i_this->m6E68.y = i_this->m6E68.y * (REG0_F(4) + -0.3f);
                i_this->m6E48 = 40.0f;
                dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                mDoAud_seStart(JA_SE_CM_BTD_DROP_HEAD, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
                i_this->mGohmaState = 0x36;
                i_this->m02EC[0] = 0x32;
                static cXyz pos(i_this->m6E50);
                pos.y -= 100.0f;
                smoke_set_s(i_this, &pos, &i_this->m6E74);
                pJVar6 = i_this->m6038;
                if (pJVar6 != NULL) {
                    pJVar6->becomeInvalidEmitter();
                    i_this->m6038 = NULL;
                }
            }
        }
        cLib_addCalc2(&i_this->m6E50.z, i_this->m6E5C.z, 1.0f, std::fabsf(i_this->m6E68.z));
        i_this->eyePos = i_this->m6E50;
        i_this->m6E74.x += REG0_S(3) + 1000;
        i_this->m6E74.z += REG0_S(4) + 0x5dc;
        kubi_calc(i_this);
        pJVar6 = i_this->m6038;
        if (pJVar6 != NULL) {
            pJVar6->setGlobalRTMatrix(i_this->m02D4->mpModel->getAnmMtx(0));
        }
        break;
    case 0x36:
        i_this->m6E88 = 0;
        cLib_addCalcAngleS2(&i_this->m6E74.x, 0x2000, 2, 0x200);
        cLib_addCalcAngleS2(&i_this->m6E74.z, 0x2000, 2, 0x200);
        i_this->m6E50.y += i_this->m6E68.y;
        i_this->m6E68.y -= (REG0_F(3) + 5.0f);
        if (i_this->m6E50.y <= i_this->m6E5C.y) {
            i_this->m6E50.y = i_this->m6E5C.y;
            ;
            i_this->m6E68.y = 0.0f;
        }
        i_this->eyePos = i_this->m6E50;
        if (i_this->m02EC[0] == 1) {
            i_this->m6E50.y = i_this->m6E50.y - 100.0f;
            mDoAud_seStart(JA_SE_CM_BOSS_EXPLODE, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_createDisappear(i_this, &i_this->m6E50, 0xF, daDisItem_HEART_CONTAINER_e, 0xFF);
            i_this->mGohmaState = 0x37;
            i_this->m6E50.y = -10000.0f;
            i_this->m02EC[0] = 0x96;
        }
        kubi_calc(i_this);
        break;
    case 0x37:
        i_this->m6E88 = 0;
        if (i_this->m02EC[0] == 2) {
            dr2->unk_43C = 1;
            i_this->m6E84 = -200.0f;
        }
        if (i_this->m02EC[0] == 1) {
            i_this->m6E16++;
            i_this->mGohmaState = 0x38;
        }
        break;
    case 0x39:
        i_this->mKankyoState = 6;
    }
}

static s32 jab_bck[] = {BTD_BCK_RJAB1, BTD_BCK_RJAB2, BTD_BCK_RJAB3, 0, 0, BTD_BCK_LJAB1, BTD_BCK_LJAB2, BTD_BCK_LJAB3};
static s32 punch_bck[] = {
    BTD_BCK_RATTACK1,
    BTD_BCK_RATTACK2,
    BTD_BCK_RATTACK3,
    BTD_BCK_RATTACK4,
    BTD_BCK_RATTACK5,
    BTD_BCK_LATTACK1,
    BTD_BCK_LATTACK2,
    BTD_BCK_LATTACK3,
    BTD_BCK_LATTACK4,
    BTD_BCK_LATTACK5
};

/* 000036A0-00003BCC       .text wait__FP9btd_class */
void wait(btd_class* i_this) {
    /* Nonmatching - .data */
    short sVar1;
    daPy_py_c* apdVar2;
    u16 uVar5;

    apdVar2 = daPy_getPlayerActorClass();
    uVar5 = player_view_check(i_this);
    u8 bVar8 = false;
    if (apdVar2->current.pos.y > REG0_F(5) + 400.0f) {
        bVar8 = true;
    }
    switch (i_this->mGohmaState) {
    case 0:
        anm_init(i_this, BTD_BCK_WAIT1, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mGohmaState++;
    case 1:
        if ((uVar5 < 0x1800) && (i_this->m02EC[0] == 0)) {
            i_this->m02E4 = 1;
            i_this->mGohmaState = 0;
            if (cM_rndF(1.0f) < 0.5f) {
                i_this->m02E9 = 0;
                i_this->m02EA = 1;
            } else {
                i_this->m02E9 = 5;
                i_this->m02EA = 0;
            }
            if (l_HIO.m10 == 0) {
                if ((uVar5 > 0x400) && (cM_rndF(1.0f) < 0.5f)) {
                    i_this->mAttackType = 5;
                } else if (uVar5 > 0x800) {
                    i_this->mAttackType = 5;
                } else if (i_this->m02E0 == 0) {
                    if (cM_rndF(1.0f) < l_HIO.m18) {
                        i_this->mAttackType = 0;
                    } else if (cM_rndF(1.0f) < l_HIO.m1C) {
                        i_this->mAttackType = 1;
                    } else {
                        i_this->mAttackType = 2;
                    }
                } else if (cM_rndF(1.0f) < l_HIO.m20) {
                    i_this->mAttackType = 0;
                } else if (cM_rndF(1.0f) < l_HIO.m24) {
                    i_this->mAttackType = 1;
                } else {
                    i_this->mAttackType = 2;
                }
            } else if (l_HIO.m10 == 1) {
                i_this->mAttackType = 0;
            } else if (l_HIO.m10 == 2) {
                i_this->mAttackType = 1;
            } else if (l_HIO.m10 == 3) {
                i_this->mAttackType = 2;
            } else if (l_HIO.m10 == 4) {
                i_this->mAttackType = 5;
                i_this->m02E9 = 5;
                i_this->m02EA = 0;
            }
        } else {
            i_this->m5E94 = 0x100;
            if ((uVar5 >= 0x6000) && (i_this->m02EC[1] == 0)) {
                i_this->mGohmaState = 2;
                anm_init(i_this, BTD_BCK_KYORO, 10.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->m02EC[0] = 0x96;
            } else if (bVar8) {
                if ((kui != NULL) && (kui->health == 3)) {
                    i_this->mGohmaState = 10;
                } else {
                    i_this->mGohmaState = 0x14;
                }
            }
            i_this->m5E86 = 1;
        }
        break;
    case 2:
        if ((uVar5 < 0x6000) || (i_this->m02EC[0] == 0)) {
            i_this->mGohmaState = 0;
            i_this->m02EC[1] = 0x28;
        }
        break;
    case 10:
        anm_init(i_this, BTD_BCK_UEMUKI_WAIT, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mGohmaState++;
        i_this->m02EC[0] = 300;
        i_this->m02EC[1] = (s16)(cM_rndF(80.0f) + 90.0f);
    case 0xb:
        if ((i_this->m02EC[1] == 0) && (i_this->m02EC[0] > 0x96)) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_WAIT, 0);
            i_this->m02EC[1] = (s16)(cM_rndF(80.0f) + 90.0f);
        }
        i_this->m5E86 = 3;
        i_this->m5E94 = 0x100;
        sVar1 = apdVar2->shape_angle.y;
        i_this->m5E90 = sVar1 + 0x4000;
        if ((!bVar8) || (kui != NULL && (kui->health != 3))) {
            i_this->mGohmaState = 0;
        }
        if (i_this->m02EC[0] == 0) {
            i_this->m02E4 = 1;
            i_this->mAttackType = 3;
            i_this->mGohmaState = 0;
        }
        break;
    case 0x14:
        anm_init(i_this, BTD_BCK_YOKO_WAIT, 20.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
        i_this->mGohmaState++;
        i_this->m02EC[0] = 0x96;
    case 0x15:
        i_this->m5E86 = 1;
        i_this->m5E94 = 0x100;
        if ((!bVar8) || (kui != NULL && (kui->health == 3))) {
            i_this->mGohmaState = 0;
        }
        if (i_this->m02EC[0] == 0) {
            i_this->m02E4 = 1;
            i_this->mAttackType = 4;
            i_this->mGohmaState = 0;
        }
    }
}

/* 00003BCC-00003E64       .text jab_attack__FP9btd_class */
void jab_attack(btd_class* i_this) {
    mDoExt_McaMorf* iVar3;
    int iVar6;

    iVar3 = get_anm(i_this);
    switch (i_this->mGohmaState) {
    case 0:
        anm_init(i_this, jab_bck[i_this->m02E9], 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_JAB, 0);
        i_this->mGohmaState++;
        break;
    case 1:
        if (iVar3->isStop()) {
            i_this->m02E9++;
            anm_init(i_this, jab_bck[i_this->m02E9], 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            iVar6 = 8;
            if (i_this->m02EA != 0) {
                iVar6 = 10;
            }
            mDoAud_seStart(JA_SE_CM_BTD_WIND_JAB, &i_this->m02FC[iVar6], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        }
        break;
    case 2:
        i_this->m5E84 = 1;
        if (iVar3->isStop()) {
            i_this->m02E9++;
            anm_init(i_this, jab_bck[i_this->m02E9], 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
        }
        break;
    case 3:
        if (iVar3->isStop()) {
            i_this->m02E4 = 0;
            i_this->mGohmaState = 0;
            i_this->m02EC[0] = (s16)(l_HIO.m14 + cM_rndF(50.0f));
        }
        break;
    }
}

/* 00003E64-00004418       .text punch_attack__FP9btd_class */
void punch_attack(btd_class* i_this) {
    int iVar1;
    mDoExt_McaMorf* iVar3;
    int iVar6;

    iVar3 = get_anm(i_this);
    switch (i_this->mGohmaState) {
    case 0:
        anm_init(i_this, punch_bck[i_this->m02E9], 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mGohmaState++;
        fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_ATTACK, 0);
        break;
    case 1:
        if (iVar3->isStop()) {
            i_this->m02E9++;
            anm_init(i_this, punch_bck[i_this->m02E9], 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            iVar6 = 8;
            if (i_this->m02EA != 0) {
                iVar6 = 10;
            }
            mDoAud_seStart(JA_SE_CM_BTD_WIND_ATTACK, &i_this->m02FC[iVar6], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        }
        break;
    case 2:
        i_this->m5E84 = 2;
        if (iVar3->isStop()) {
            i_this->m02E9++;
            anm_init(i_this, punch_bck[i_this->m02E9], 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            iVar6 = 8;
            if (i_this->m02EA != 0) {
                iVar6 = 10;
            }
            mDoAud_seStart(JA_SE_CM_BTD_ARM_STRIKE, &i_this->m02FC[iVar6], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            hahen_set(i_this, i_this->m02EA);
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }
        break;
    case 3:
        if (iVar3->isStop()) {
            i_this->m02E9++;
            anm_init(i_this, punch_bck[i_this->m02E9], 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m02EC[0] = (s16)(l_HIO.m28 + cM_rndF(100.0f));
            i_this->mGohmaState++;
        }
        break;
    case 4:
        iVar6 = 8;
        if (i_this->m02EA != 0) {
            iVar6 = 10;
        }
        iVar1 = iVar3->mFrameCtrl.getFrame();
        if (iVar1 == 2) {
            mDoAud_seStart(JA_SE_CM_BTD_ARM_PULLOUT_1, &i_this->m02FC[iVar6], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_JITABATA, 0);
        }
        if (i_this->m02EC[0] == 0) {
            i_this->m02E9++;
            anm_init(i_this, punch_bck[i_this->m02E9], 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_AFT_JITABATA, 0);
            mDoAud_seStart(JA_SE_CM_BTD_ARM_PULLOUT_2, &i_this->m02FC[iVar6], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            i_this->m6032 = 0x17;
            i_this->m6030 = 0x17;
            i_this->m6034 = 3;
        }
        break;
    case 5:
        if (iVar3->isStop()) {
            i_this->m02E4 = 0;
            i_this->mGohmaState = 0;
            i_this->m02EC[0] = (s16)(l_HIO.m14 + cM_rndF(50.0f));
        }
        break;
    }
    if ((i_this->mGohmaState == 3) || (i_this->mGohmaState == 4)) {
        i_this->m5E7C = i_this->m02EA + 2;
    }
}

/* 00004418-00004948       .text punch2_attack__FP9btd_class */
void punch2_attack(btd_class* i_this) {
    mDoExt_McaMorf* iVar3;
    int iVar6;

    iVar3 = get_anm(i_this);
    switch (i_this->mGohmaState) {
    case 0:
        anm_init(i_this, punch_bck[i_this->m02E9], 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mGohmaState++;
        fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_ATTACK, 0);
        break;
    case 1:
        if (iVar3->isStop()) {
            i_this->m02E9++;
            anm_init(i_this, punch_bck[i_this->m02E9], 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            iVar6 = 8;
            if (i_this->m02EA != 0) {
                iVar6 = 10;
            }
            mDoAud_seStart(JA_SE_CM_BTD_WIND_ATTACK, &i_this->m02FC[iVar6], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        }
        i_this->m5E92 = REG0_S(2) + 0xf;
        i_this->m5E94 = REG0_S(3) + 0xc00;
        break;
    case 2:
        i_this->m5E84 = 2;
        if (iVar3->isStop()) {
            i_this->m02E9++;
            anm_init(i_this, punch_bck[i_this->m02E9], 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            iVar6 = 8;
            if (i_this->m02EA != 0) {
                iVar6 = 10;
            }
            mDoAud_seStart(JA_SE_CM_BTD_ARM_STRIKE, &i_this->m02FC[iVar6], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            hahen_set(i_this, i_this->m02EA);
            dComIfGp_getVibration().StartShock(REG0_S(2) + 5, -0x21, cXyz(0.0f, 1.0f, 0.0f));
        }
        break;
    case 3:
        if (iVar3->isStop()) {
            i_this->m02E9++;
            anm_init(i_this, punch_bck[i_this->m02E9], 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->m02EC[0] = (s16)(cM_rndF(80.0f) + 80.0f);
            i_this->mGohmaState++;
        }
        break;
    case 4:
        iVar6 = 8;
        if (i_this->m02EA != 0) {
            iVar6 = 10;
        }
        if (iVar3->isStop()) {
            i_this->m02E9++;
            anm_init(i_this, punch_bck[i_this->m02E9], 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_AFT_JITABATA, 0);
            mDoAud_seStart(JA_SE_CM_BTD_ARM_PULLOUT_2, &i_this->m02FC[iVar6], 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            i_this->m6032 = 0x17;
            i_this->m6030 = 0x17;
            i_this->m6034 = 3;
        }
        break;
    case 5:
        if (iVar3->isStop()) {
            if (l_HIO.m10 != 4) {
                i_this->m02E4 = 0;
                i_this->mGohmaState = 0;
                i_this->m02EC[0] = 0;
            } else {
                i_this->mGohmaState = 0;
                i_this->m02E9 = 5;
            }
        }
        break;
    }
}

/* 00004948-00004FE4       .text fire_attack__FP9btd_class */
void fire_attack(btd_class* i_this) {
    mDoExt_McaMorf* iVar2;
    cXyz local_2c;
    cXyz cStack_38;

    iVar2 = get_anm(i_this);
    i_this->m5E86 = 2;
    switch (i_this->mGohmaState) {
    case 0:
        anm_init(i_this, BTD_BCK_FATTACK1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mGohmaState++;
        i_this->m02EC[0] = 0x28;
        i_this->m6E7C = 0.0f;
        break;
    case 1:
        if (i_this->m02EC[0] == (s16)(REG0_S(6) + 0x10)) {
            hahen_set2(i_this);
        }
        if (i_this->m02EC[0] == 0x1f) {
            fopAcM_monsSeStart(i_this, JA_SE_CV_BTD_BEF_FIRE, 0);
        }
        if (iVar2->isStop()) {
            anm_init(i_this, BTD_BCK_FATTACK2, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
        }
        break;
    case 2:
        if (iVar2->isStop()) {
            if (i_this->m02E0 != 0) {
                i_this->mGohmaState = 6;
                anm_init(i_this, BTD_BCK_HASAMI_ATTACK, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                fopAcM_monsSeStart(i_this, JA_SE_CM_MAGTAIL_ATTACK, 0);
            } else {
                anm_init(i_this, BTD_BCK_FATTACK3, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
                i_this->m02EC[0] = l_HIO.m2C * 9;
                i_this->mGohmaState = 3;
            }
        }
        break;
    case 3:
        i_this->mKankyoState = 1;
        mDoAud_seStart(JA_SE_CM_BTD_HIFUKI_BEF, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        if (i_this->m02EC[0] > 9) {
            i_this->m6028[1] = 1;
        }
        i_this->m6028[0] = REG0_S(6) + 0x14;
        if (i_this->m02EC[0] == 0) {
            if (i_this->m02E0 != 0) {
                anm_init(i_this, BTD_BCK_HASAMI_ATTACK, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mGohmaState = 5;
                fopAcM_monsSeStart(i_this, JA_SE_CM_MAGTAIL_ATTACK, 0);
            } else {
                anm_init(i_this, BTD_BCK_FATTACK4, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
                i_this->mGohmaState++;
                i_this->m02EC[0] = REG0_S(3) + 0x19;
                mDoAud_seStart(JA_SE_CM_BTD_WIND_BEF_FIRE, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            }
            i_this->m600C[3] = NULL;
        }
        break;
    case 4:
        i_this->m602C = 0xc;
        i_this->m602E = 3;
        if (iVar2->isStop()) {
            i_this->m02E4 = 0;
            i_this->mGohmaState = 0;
            i_this->m02EC[0] = (s16)(l_HIO.m14 + cM_rndF(50.0f));
        }
        if (i_this->m02EC[0] <= 1) {
            i_this->mKankyoState = 2;
            mDoAud_seStart(JA_SE_CM_BTD_HIFUKI, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            MTXCopy(iVar2->getModel()->getAnmMtx(0x3a), *calc_mtx);
            local_2c.x = 0.0f;
            local_2c.y = i_this->m5E80 * -200.0f;
            local_2c.z = i_this->m5E80 * 1000.0f;
            MtxPosition(&local_2c, &cStack_38);
            i_this->m1B98.SetR(i_this->m5E80 * 200.0f);
            if (i_this->m02EC[0] == 1) {
                i_this->m1B98.StartCAt(cStack_38);
            } else {
                i_this->m1B98.MoveCAt(cStack_38);
            }
            dComIfG_Ccsp()->Set(&i_this->m1B98);
            i_this->m5E80 += 0.1f;
            if (i_this->m5E80 > 1.0f) {
                i_this->m5E80 = 0.0f;
            }
        } else {
            i_this->m5E80 = 0.0f;
        }
        break;
    case 5:
        i_this->m5E84 = 3;
        if (iVar2->isStop()) {
            anm_init(i_this, BTD_BCK_FATTACK4, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState = 4;
            i_this->m02EC[0] = REG0_S(3) + 0x19;
            mDoAud_seStart(JA_SE_CM_BTD_WIND_BEF_FIRE, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        }
        break;
    case 6:
        i_this->m5E84 = 3;
        if (iVar2->isStop()) {
            anm_init(i_this, BTD_BCK_FATTACK3, 15.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m02EC[0] = (s16)(l_HIO.m2C << 2);
            i_this->mGohmaState = 3;
        }
    }
    if ((i_this->mGohmaState >= 2) || (i_this->m02EC[0] < 0x10)) {
        i_this->m5E7C = 1;
    }
}

/* 00004FE4-000053E4       .text up_fire_attack__FP9btd_class */
void up_fire_attack(btd_class* i_this) {
    bool bVar2;
    daPy_py_c* apdVar4;
    mDoExt_McaMorf* iVar5;
    cXyz local_2c;
    cXyz cStack_38;

    apdVar4 = daPy_getPlayerActorClass();
    iVar5 = get_anm(i_this);
    bVar2 = true;
    i_this->m5E86 = 3;
    switch (i_this->mGohmaState) {
    case 0:
        anm_init(i_this, BTD_BCK_UE_KAEN1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mGohmaState++;
        i_this->m02EC[0] = 0x28;
        break;
    case 1:
        if (iVar5->isStop()) {
            anm_init(i_this, BTD_BCK_UE_KAEN2, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m02EC[0] = l_HIO.m2C * 9;
            i_this->mGohmaState++;
        }
        break;
    case 2:
        i_this->mKankyoState = 1;
        mDoAud_seStart(JA_SE_CM_BTD_HIFUKI_BEF, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        i_this->m6028[1] = 1;
        i_this->m6028[0] = REG0_S(6) + 0x14;
        if (i_this->m02EC[0] == 0) {
            anm_init(i_this, BTD_BCK_UE_KAEN3, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            i_this->m02EC[0] = REG0_S(3) + 0x19;
            mDoAud_seStart(JA_SE_CM_BTD_WIND_BEF_FIRE, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            i_this->m600C[3] = NULL;
        }
        break;
    case 3:
        i_this->m602C = 0xc;
        i_this->m602E = 3;
        if (i_this->m02EC[0] == 0) {
            i_this->mKankyoState = 2;
            mDoAud_seStart(JA_SE_CM_BTD_HIFUKI, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            MTXCopy(iVar5->getModel()->getAnmMtx(0x3a), *calc_mtx);
            local_2c.x = 0.0f;
            local_2c.y = i_this->m5E80 * -200.0f;
            local_2c.z = i_this->m5E80 * 1000.0f;
            MtxPosition(&local_2c, &cStack_38);
            i_this->m1B98.SetR(i_this->m5E80 * 200.0f);
            i_this->m1B98.SetC(cStack_38);
            dComIfG_Ccsp()->Set(&i_this->m1B98);
            i_this->m5E80 += 0.1f;
            if (i_this->m5E80 > 1.0f) {
                i_this->m5E80 = 0.0f;
            }
        } else {
            i_this->m5E80 = 0.0f;
        }
        if (iVar5->isStop()) {
            i_this->m02E4 = 0;
            i_this->mGohmaState = 0;
            i_this->m02EC[0] = (s16)(l_HIO.m14 + cM_rndF(50.0f));
        }
        break;
    }
    if ((apdVar4->current.pos.y < REG0_F(5) + 400.0f) || (kui != 0 && (kui->health != 3))) {
        i_this->m02E4 = 0;
        i_this->mGohmaState = 0;
        i_this->m02EC[0] = (s16)(l_HIO.m14 + cM_rndF(50.0f));
    }
}

/* 000053E4-000058A4       .text yoko_fire_attack__FP9btd_class */
void yoko_fire_attack(btd_class* i_this) {
    bool bVar2;
    daPy_py_c* apdVar4;
    mDoExt_McaMorf* iVar5;
    float fVar8;
    cXyz local_2c;
    cXyz cStack_38;

    apdVar4 = daPy_getPlayerActorClass();
    iVar5 = get_anm(i_this);
    bVar2 = true;
    i_this->m5E86 = 1;
    switch (i_this->mGohmaState) {
    case 0:
        anm_init(i_this, BTD_BCK_YOKO_KAEN1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
        i_this->mGohmaState++;
        i_this->m02EC[0] = 0x28;
        break;
    case 1:
        if (iVar5->isStop()) {
            anm_init(i_this, BTD_BCK_YOKO_KAEN2, 1.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, -1);
            i_this->m02EC[0] = l_HIO.m2C * 7;
            i_this->mGohmaState++;
        }
        break;
    case 2:
        i_this->mKankyoState = 1;
        mDoAud_seStart(JA_SE_CM_BTD_HIFUKI_BEF, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
        i_this->m6028[1] = 1;
        i_this->m6028[0] = REG0_S(6) + 0x14;
        if (i_this->m02EC[0] == 0) {
            anm_init(i_this, BTD_BCK_YOKO_KAEN3, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, -1);
            i_this->mGohmaState++;
            i_this->m02EC[0] = REG0_S(3) + 0x19;
            mDoAud_seStart(JA_SE_CM_BTD_WIND_BEF_FIRE, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            i_this->m600C[3] = NULL;
        }
        break;
    case 3:
        local_2c = apdVar4->eyePos - i_this->eyePos;
        fVar8 = std::sqrtf(local_2c.x * local_2c.x + local_2c.z * local_2c.z);
        i_this->m5E8C = -cM_atan2s(local_2c.y, fVar8) - 0x9c4;
        i_this->m602C = 0xc;
        i_this->m602E = 3;
        if (i_this->m02EC[0] == 0) {
            i_this->mKankyoState = 2;
            mDoAud_seStart(JA_SE_CM_BTD_HIFUKI, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            MTXCopy(iVar5->getModel()->getAnmMtx(0x3a), *calc_mtx);
            local_2c.x = 0.0f;
            local_2c.y = i_this->m5E80 * -200.0f;
            local_2c.z = i_this->m5E80 * 1000.0f;
            MtxPosition(&local_2c, &cStack_38);
            i_this->m1B98.SetR(i_this->m5E80 * 200.0f);
            i_this->m1B98.SetC(cStack_38);
            dComIfG_Ccsp()->Set(&i_this->m1B98);
            i_this->m5E80 += 0.1f;
            if (i_this->m5E80 > REG0_F(9) + 1.0f) {
                i_this->m5E80 = 0.0f;
            }
        } else {
            i_this->m5E80 = 0.0f;
        }
        if (iVar5->isStop()) {
            i_this->m02E4 = 0;
            i_this->mGohmaState = 0;
            fVar8 = cM_rndF(50.0f);
            i_this->m02EC[0] = (s16)(l_HIO.m14 + fVar8);
        }
        break;
    }
    if ((apdVar4->current.pos.y < REG0_F(5) + 400.0f) || (kui != 0 && (kui->health == 3))) {
        i_this->m02E4 = 0;
        i_this->mGohmaState = 0;
        fVar8 = cM_rndF(50.0f);
        i_this->m02EC[0] = (s16)(l_HIO.m14 + fVar8);
    }
    i_this->m5E94 = 0x200;
}

/* 000058A4-00005930       .text attack__FP9btd_class */
void attack(btd_class* i_this) {
    i_this->m02F0 = 5;
    switch (i_this->mAttackType) {
    case 0:
        jab_attack(i_this);
        break;
    case 1:
        punch_attack(i_this);
        break;
    case 2:
        fire_attack(i_this);
        break;
    case 3:
        up_fire_attack(i_this);
        break;
    case 4:
        yoko_fire_attack(i_this);
        break;
    case 5:
        punch2_attack(i_this);
        break;
    }
}

/* 00005930-00005BCC       .text move__FP9btd_class */
void move(btd_class* i_this) {
    /* Nonmatching - regalloc */
    daPy_py_c* apdVar1;
    s16 uVar2;
    short target;
    s8 bVar5;
    short sVar4;
    cXyz local_28;

    apdVar1 = daPy_getPlayerActorClass();
    i_this->m5E84 = 0;
    i_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    bVar5 = false;
    switch (i_this->m02E4) {
    case 0:
        wait(i_this);
        break;
    case 1:
        attack(i_this);
        break;
    case 2:
        bVar5 = damage(i_this);
        break;
    case 0xA:
        startdemo(i_this);
        bVar5 = true;
        break;
    case 0xB:
        end(i_this);
        bVar5 = true;
        break;
    }
    if (bVar5 != false) {
        fopAcM_OffStatus(i_this, 0);
        i_this->attention_info.flags = 0;
    }
    damage_check(i_this);
    if (i_this->m5E94 != 0) {
        if (((dr2 != NULL) && (dr2->unk_4BA == 0 || (dr2->unk_4BA >= 0xA))) && (dr2->unk_4CA == 0 || (dr2->unk_4CA >= 0x62))) {
            sVar4 = i_this->m5E90;
            if (sVar4 != 0) {
                sVar4 = fopAcM_searchActorAngleY(i_this, daPy_getPlayerActorClass());
            }
            cLib_addCalcAngleS2(&i_this->current.angle.y, sVar4, i_this->m5E92, i_this->m5E94);
        }
        i_this->m5E90 = 0;
        i_this->m5E92 = 10;
        i_this->m5E94 = 0;
    }
    if (i_this->m5E86 != 0) {
        local_28 = apdVar1->current.pos;
        if (local_28.x * local_28.x + local_28.z * local_28.z < 40000.0f) {
            target = 0;
            sVar4 = 0;
        } else {
            sVar4 = fopAcM_searchActorAngleY(i_this, daPy_getPlayerActorClass());
            sVar4 = sVar4 - i_this->current.angle.y;
            if (sVar4 > 0x1388) {
                sVar4 = 5000;
            } else if (sVar4 < -5000) {
                sVar4 = -5000;
            }
            local_28 = apdVar1->eyePos - i_this->eyePos;
            uVar2 = cM_atan2s(local_28.x, local_28.z) - i_this->current.angle.y;
            target = ((short)uVar2 / 2);
            if (target > 0x2000) {
                target = 0x2000;
            } else if (target < -0x2000) {
                target = -0x2000;
            }
        }
    } else {
        target = 0;
        sVar4 = 0;
    }
    cLib_addCalcAngleS2(&i_this->m5E88, sVar4, 4, 0x200);
    cLib_addCalcAngleS2(&i_this->m5E8E, target, 4, 0x200);
    cLib_addCalcAngleS2(&i_this->m5E8A, i_this->m5E8C, 4, 0x100);
    i_this->m5E86 = 0;
    i_this->m5E8C = 0;
}

/* 00005BCC-00005C24       .text k_a_d_sub__FPvPv */
void* k_a_d_sub(void* i_this, void* param_2) {
    if (((fopAc_IsActor(i_this)) && (fopAcM_GetName(i_this) == PROC_KUI)) && (fopAcM_GetParam(i_this) == 0x511)) {
        return i_this;
    }
    return NULL;
}

/* 00005C24-00005C70       .text dr2_a_d_sub__FPvPv */
void* dr2_a_d_sub(void* i_this, void* param_2) {
    if ((fopAc_IsActor(i_this)) && (fopAcM_GetName(i_this) == PROC_DR2)) {
        return i_this;
    } else {
        return NULL;
    }
}

/* 00005C70-00005CC8       .text wepon_s_sub__FPvPv */
void* wepon_s_sub(void* i_this, void* param_2) {
    if (((fopAc_IsActor(i_this)) && (fopAcM_GetName(i_this) == PROC_HIMO2)) || (fopAcM_GetName(i_this) == PROC_BOOMERANG)) {
        return i_this;
    }
    return NULL;
}

/* 00005CC8-00005DC4       .text hahen_move__FP9btd_class */
void hahen_move(btd_class* i_this) {
    btd_hahen_s* pbVar2 = &i_this->hahen[0];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->hahen); i++, pbVar2++) {
        if (pbVar2->m04 != 0) {
            pbVar2->m08 += pbVar2->m14;
            pbVar2->m20 += 0x900;
            pbVar2->m22 += 0x600;
            pbVar2->m14.y -= 3.0f;
            MtxTrans(pbVar2->m08.x, pbVar2->m08.y, pbVar2->m08.z, false);
            mDoMtx_YrotM(*calc_mtx, pbVar2->m22);
            mDoMtx_XrotM(*calc_mtx, pbVar2->m20);
            pbVar2->model->setBaseTRMtx(*calc_mtx);
            if (pbVar2->m08.y < -100.0f) {
                pbVar2->m04 = 0;
            }
        }
    }
}

/* 00005DC4-000060E0       .text sibuki_move__FP9btd_class */
void sibuki_move(btd_class* i_this) {
    /* Nonmatching - regalloc */
    daPy_py_c* apdVar4 = daPy_getPlayerActorClass();
    btd_sibuki_s* sibuikiS = &i_this->mBtdSibukiS[0];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mBtdSibukiS); i++, sibuikiS++) {
        if (sibuikiS->m00 == 0) {
            continue;
        }
        if ((char)sibuikiS->m00 <= 2) {
            bool bVar2 = false;
            if ((i == 0) && (l_HIO.m54 != 0)) {
                cLib_addCalc2(&sibuikiS->m04.x, apdVar4->current.pos.x, 1.0f, 30.0f);
                cLib_addCalc2(&sibuikiS->m04.y, apdVar4->current.pos.y + 70.0f, 1.0f, 30.0f);
                cLib_addCalc2(&sibuikiS->m04.z, apdVar4->current.pos.z, 1.0f, 30.0f);
                sibuikiS->m10.y = -10.0f;
            } else {
                sibuikiS->m10.y = sibuikiS->m10.y - l_HIO.m50;
                sibuikiS->m04 += sibuikiS->m10;
            }
            if (sibuikiS->m10.y < 0.0f) {
                if (sibuikiS->m00 == 1) {
                    i_this->m1CC4[i].StartCAt(sibuikiS->m04);
                    sibuikiS->m00++;
                } else {
                    i_this->m1CC4[i].MoveCAt(sibuikiS->m04);
                }
                dComIfG_Ccsp()->Set(&i_this->m1CC4[i]);
                if (sibuikiS->m04.y < 0.0f) {
                    sibuikiS->m04.y = 0.0f;
                    bVar2 = true;
                }
            }
            if ((bVar2) || (i_this->m1CC4[i].ChkAtHit())) {
                cXyz local_38 = apdVar4->current.pos - sibuikiS->m04;
                sibuikiS->m00 = 0;
                if ((local_38.abs() < 1500.0f) && (i_this->m6E14 < 20)) {
                    i_this->m6E14++;
                    dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8064, &sibuikiS->m04, 0xff, g_whiteColor, g_whiteColor, 0);
                    mDoAud_seStart(JA_SE_OBJ_BTD_FIRE_DROP, &sibuikiS->m04, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
                    sibuikiS->m00 = 0;
                }
            } else {
                dComIfGp_particle_setSimple(dPa_name::ID_SCENE_8063, &sibuikiS->m04, 0xff, g_whiteColor, g_whiteColor, 0);
            }
        } else {
            sibuikiS->m00++;
            if (sibuikiS->m00 == 0x1e) {
                sibuikiS->m00 = 0;
            }
        }
    }
}

/* 000060E0-000072BC       .text demo_camera__FP9btd_class */
void demo_camera(btd_class* i_this) {
    /* Nonmatching - sVar3, cXyz */
    int iVar1;
    float fVar2;
    short sVar3;
    camera_class* pcVar4;
    daPy_py_c* apdVar5;
    camera_class* pcVar7;
    f32 dVar8;
    cXyz local_c8;
    cXyz local_bc;
    cXyz local_b0;
    cXyz local_a4;
    cXyz local_44;
    cXyz local_38;

    apdVar5 = daPy_getPlayerActorClass();
    pcVar7 = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    i_this->m6E1A = i_this->m6E1A + 1;
    i_this->m6E18 = i_this->m6E18 + 1;
    sVar3 = i_this->m6E16;
    switch (sVar3) {
    case 0:
        i_this->mKankyoState = 6;
        i_this->m6E16++;
        i_this->m6E3C = REG0_F(12) + 50.0f;
        pcVar7->mCamera.Stop();
        pcVar7->mCamera.SetTrimSize(2);
        i_this->m6E1C.x = 282.0f;
        i_this->m6E1C.y = 2775.0f;
        i_this->m6E1C.z = -582.0f;
        i_this->m6E28.x = -1200.0f;
        i_this->m6E28.y = 0.0f;
        i_this->m6E28.z = 660.0f;
        i_this->m6E1A = 0;
        i_this->m6E18 = 0;
        i_this->m6E40 = 0.0f;
        static_center_pos.setall(0.0f);
        break;
    case 1:
        i_this->mKankyoState = 6;
        if (i_this->m6E1A > 0x32) {
            i_this->m6E1C.y = i_this->m6E1C.y - (REG0_F(6) + 5.0f);
        }
        local_44.x = -1373.0f;
        local_44.y = apdVar5->current.pos.y;
        local_44.z = 790.0f;
        apdVar5->setPlayerPosAndAngle(&local_44, i_this->current.angle.y + 0x8000);
        if (i_this->m6E1A != 0x6f) {
            return;
        }
        i_this->m6E1A = 0;
        i_this->m6E16 = 3;
        i_this->m6E1C.x = -1728.0f;
        i_this->m6E1C.y = 111.0f;
        i_this->m6E1C.z = 844.0f;
        i_this->m6E28.x = -1397.0f;
        i_this->m6E28.y = 110.0f;
        i_this->m6E28.z = 685.0f;
        break;
    case 2:
        i_this->mKankyoState = 6;
        if (i_this->m6E1A > 0x32) {
            cLib_addCalc2(&i_this->m6E28.x, -1536.0f, 0.1f, i_this->m6E40 * 139.0f);
            cLib_addCalc2(&i_this->m6E28.y, 411.0f, 0.1f, i_this->m6E40 * 301.0f);
            cLib_addCalc2(&i_this->m6E28.z, 752.0f, 0.1f, i_this->m6E40 * 67.0f);
            cLib_addCalc2(&i_this->m6E40, 1.0f, 0.1f, 0.005f);
        }
        if ((i_this->m6E1A < 0xb4) || (REG0_S(6) != 0)) {
            i_this->m6E1A = 0;
            i_this->m6E16 = 4;
            i_this->m6E40 = 0.0f;
            i_this->m6E1C.x = -2501.0f;
            i_this->m6E1C.y = 418.0f;
            i_this->m6E1C.z = -32.0f;
            i_this->m6E28.x = -2139.0f;
            i_this->m6E28.y = 373.0f;
            i_this->m6E28.z = 17.0f;
            i_this->m6E3C = 60.0f;
            if (i_this->m6E1A >= 0x8C) {
                i_this->mKankyoState = 7;
                i_this->m6E48 = 20.0f;
                mDoAud_seStart(JA_SE_ATM_JINARI);
                if (i_this->m6E1A == 0x8c) {
                    dComIfGp_getVibration().StartQuake(REG0_S(5) + 3, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                }
            }
            i_this->mKankyoState = 7;
            i_this->m6E48 = 15.0f;
            mDoAud_seStart(JA_SE_ATM_JINARI);
            cLib_addCalc2(&i_this->m6E1C.x, -1763.0f, 0.1f, i_this->m6E40 * 738.0f);
            cLib_addCalc2(&i_this->m6E1C.y, 167.0f, 0.1f, i_this->m6E40 * 251.0f);
            cLib_addCalc2(&i_this->m6E1C.z, 812.0f, 0.1f, i_this->m6E40 * 844.0f);
            cLib_addCalc2(&i_this->m6E28.x, -1430.0f, 0.1f, i_this->m6E40 * 709.0f);
            cLib_addCalc2(&i_this->m6E28.y, 123.0f, 0.1f, i_this->m6E40 * 250.0f);
            cLib_addCalc2(&i_this->m6E28.z, 663.0f, 0.1f, i_this->m6E40 * 646.0f);
            cLib_addCalc2(&i_this->m6E40, REG0_F(10) + 0.01f, 0.1f, 0.001f);
            if (i_this->m6E1A > 0x28) {
                cLib_addCalc2(&i_this->m6E84, 0.0f, 0.1f, 1.0f);
            }
            if (i_this->m6E1A == 0x1e) {
                mDoAud_seStart(JA_SE_CM_BTD_ENT_BUBBLE, &static_center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            }
            if (i_this->m6E1A == 0x50) {
                wave_set(i_this);
            }
            if (i_this->m6E1A == 0x91) {
                wave_set(i_this);
            }
            if (i_this->m6E1A == 0x96) {
                dComIfGp_getVibration().StartQuake(REG0_S(5) + 4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
                i_this->mGohmaState = 1;
                i_this->m6E1A = 0;
                i_this->m6E16 = 5;
                i_this->m6E40 = 0.0f;
                i_this->m6E84 = 0.0f;
                mDoAud_seStart(JA_SE_CM_BTD_ENT_BLAST, &static_center_pos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
                i_this->mKankyoState = 8;
            }
        }
        break;
    case 3:
        if (i_this->m6E1A == 10) {
            dComIfGp_getVibration().StopQuake(-1);
        }
        if (i_this->m6E1A == 0x32) {
            wave_set(i_this);
        }
        sVar3 = i_this->m6E1A;
        if (sVar3 >= 0xA) {
            if (sVar3 < 0xcd) {
                cLib_addCalc2(&i_this->m6E28.x, i_this->eyePos.x * 0.3f, 0.2f, i_this->m6E40 * 200.0f);
                fVar2 = (i_this->eyePos.y + REG0_F(5) * 0.1f) - 100.0f;
                if (fVar2 < REG0_F(6) + 300.0f) {
                    fVar2 = REG0_F(6) + 300.0f;
                }
                cLib_addCalc2(&i_this->m6E28.y, fVar2, 0.2f, i_this->m6E40 * 200.0f);
                cLib_addCalc2(&i_this->m6E28.z, i_this->eyePos.z * 0.3f, 0.2f, i_this->m6E40 * 200.0f);
            } else {
                if (sVar3 == 0xcd) {
                    i_this->m6E40 = 0.0f;
                }
                cLib_addCalc2(&i_this->m6E1C.x, -1750.0f, 0.2f, i_this->m6E40 * 2000.0f);
                cLib_addCalc2(&i_this->m6E1C.y, 50.0f, 0.2f, i_this->m6E40 * 2000.0f);
                cLib_addCalc2(&i_this->m6E1C.z, 851.0f, 0.2f, i_this->m6E40 * 2000.0f);
                cLib_addCalc2(&i_this->m6E28.x, -299.0f, 0.2f, i_this->m6E40 * 2000.0f);
                cLib_addCalc2(&i_this->m6E28.y, 319.0f, 0.2f, i_this->m6E40 * 2000.0f);
                cLib_addCalc2(&i_this->m6E28.z, 248.0f, 0.2f, i_this->m6E40 * 2000.0f);
                if (i_this->m6E1A >= 0xFF) {
                    cLib_addCalc2(&i_this->m6E3C, 45.0f, 0.2f, 1.5f);
                }
            }
            cLib_addCalc2(&i_this->m6E40, 1.0f, 0.1f, 0.01f);
        }
        break;
    case 5:
        if (!i_this->eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderPotentialEvent(i_this, dEvtFlag_STAFF_ALL_e, 0xFFFF, 0);
            i_this->eventInfo.onCondition(dEvtCnd_UNK2_e);
        } else {
            i_this->m6E16 = 0x65;
        }
        i_this->m6E3C = REG0_F(12) + 50.0f;
        pcVar4 = dComIfGp_getCamera(0);
        i_this->m6E1C.x = (dComIfGp_getCamera(0)->mLookat.mEye).x;
        i_this->m6E1C.y = pcVar4->mLookat.mEye.y;
        i_this->m6E1C.z = pcVar4->mLookat.mEye.z;
        i_this->m6E28 = pcVar4->mLookat.mCenter;
        pcVar7->mCamera.Stop();
        pcVar7->mCamera.SetTrimSize(2);
        break;
    case 100:
        apdVar5->setPlayerPosAndAngle(&apdVar5->current.pos, i_this->current.angle.y + 0x8000);
        cLib_addCalc2(&i_this->m6E3C, REG0_F(4) + 50.0f, 0.5f, 3.0f);
        cLib_addCalc2(&i_this->m6E28.x, i_this->eyePos.x * 0.3f, 0.2f, 200.0f);
        fVar2 = (i_this->eyePos.y + REG0_F(5) * 0.1f) - 500.0f;
        if (fVar2 < REG0_F(6) + 500.0f) {
            fVar2 = REG0_F(6) + 500.0f;
        }
        cLib_addCalc2(&i_this->m6E28.y, fVar2, 0.2f, 200.0f);
        cLib_addCalc2(&i_this->m6E28.z, i_this->eyePos.z * 0.3f, 0.2f, 200.0f);
        mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
        local_38.x = REG0_F(7) * 0.1f + -500.0f;
        local_38.y = REG0_F(8) * 0.1f + 70.0f;
        local_38.z = REG0_F(9) * 0.1f + 2000.0f;
        MtxPosition(&local_38, &local_44);
        cLib_addCalc2(&i_this->m6E1C.x, local_44.x, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m6E1C.y, local_44.y, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m6E1C.z, local_44.z, 0.1f, 50.0f);
        if (i_this->m6E1A >= 0x140) {
            i_this->mKankyoState = 3;
        }
        break;
    case 101:
        if (i_this->m6E1A < 0x3c) {
            i_this->mKankyoState = 4;
        }
        if (i_this->m6E1A == 0x5a) {
            i_this->m6E15 = 1;
        }
        if (i_this->m6E1A > (short)(REG0_S(2) + 0x5a)) {
            cLib_addCalc2(&i_this->m6E28.x, i_this->eyePos.x, i_this->m6E40 * 0.2f, i_this->m6E40 * 200.0f);
            cLib_addCalc2(&i_this->m6E28.y, i_this->eyePos.y + REG0_F(5) * 0.1f, i_this->m6E40 * 0.5f, i_this->m6E40 * 500.0f);
            cLib_addCalc2(&i_this->m6E28.z, i_this->eyePos.z, i_this->m6E40 * 0.2f, i_this->m6E40 * 200.0f);
            cLib_addCalc2(&i_this->m6E40, 1.0f, 1.0f, 0.1f);
        }
        mDoMtx_YrotS(*calc_mtx, i_this->current.angle.y);
        local_38.x = REG0_F(7) * 0.1f + -500.0f;
        local_38.y = REG0_F(8) * 0.1f + 70.0f;
        local_38.z = REG0_F(9) * 0.1f + 2000.0f;
        MtxPosition(&local_38, &local_44);
        cLib_addCalc2(&i_this->m6E1C.x, local_44.x, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m6E1C.y, local_44.y, 0.1f, 50.0f);
        cLib_addCalc2(&i_this->m6E1C.z, local_44.z, 0.1f, 50.0f);
        local_38.x = REG0_F(10) * 0.1f + -250.0f;
        local_38.y = REG0_F(11) * 0.1f + 100.0f;
        local_38.z = REG0_F(12) * 0.1f + 1600.0f;
        MtxPosition(&local_38, &i_this->m6E5C);
        if (i_this->m6E1A > 0x6e) {
            local_38.x = REG0_F(10) * 0.1f + -50.0f;
            local_38.y = 0.0f;
            local_38.z = REG0_F(12) * 0.1f + 1650.0f;
            MtxPosition(&local_38, &apdVar5->current.pos);
            apdVar5->setPlayerPosAndAngle(&apdVar5->current.pos, i_this->current.angle.y + -0x4000);
        }
        break;
    case 0x66:
        i_this->m6E16 = sVar3 + 1;
        i_this->m6E1A = 0;
        i_this->m6E40 = 0.0f;
        i_this->m6E28.x = 0.0f;
        i_this->m6E28.y = 0.0f;
        i_this->m6E28.z = 0.0f;
        i_this->m6E3C = 55.0f;
        i_this->m6E36 = -6000;
        i_this->m6E34 = -11000;
        i_this->m6E44 = 2800.0f;
        break;
    case 0x67:
        cLib_addCalcAngleS2(&i_this->m6E36, 0x4000, 0x10, i_this->m6E40 * 22384.0f);
        cLib_addCalcAngleS2(&i_this->m6E34, REG0_S(2) + -6000, 0x10, i_this->m6E40 * 5000.0f);
        cLib_addCalc2(&i_this->m6E44, 500.0f, 0.0625f, i_this->m6E40 * 2300.0f);
        mDoMtx_YrotS(*calc_mtx, i_this->m6E36);
        mDoMtx_XrotM(*calc_mtx, i_this->m6E34);
        local_38.x = 0.0f;
        local_38.y = 0.0f;
        local_38.z = i_this->m6E44;
        MtxPosition(&local_38, &i_this->m6E1C);
        cLib_addCalc2(&i_this->m6E40, REG0_F(10) + 0.0048f, 0.1f, 4.8e-05f);
        if (i_this->m6E1A == 3) {
            mDoAud_seStart(JA_SE_ATM_MAGMA_CHILL, &i_this->eyePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(i_this)));
            daYkgr_c::stop();
        }
        if (i_this->m6E1A >= 3) {
            i_this->mKankyoState = 5;
        }
        if (i_this->m6E1A == 0x118) {
            static_center_pos.set(0.0f, -50.0f, 0.0f);
            g_dComIfG_gameInfo.save.getMemory().getBit().onStageBossEnemy();
            fopAcM_createWarpFlower(&static_center_pos, 0, fopAcM_GetRoomNo(i_this), 0);
            i_this->m6E90 = 0;
        }
        if (i_this->m6E1A == 0x1c2) {
            i_this->m6E16 = 0x97;
            i_this->mGohmaState = 0x39;
        }
        break;
    case 0x68:
        pcVar7->mCamera.Reset(i_this->m6E28, i_this->m6E1C);
        break;
    case 0x96:
        local_a4 = apdVar5->eyePos;
        local_b0.x = local_a4.x * 0.9f;
        local_b0.z = local_a4.z * 0.9f;
        pcVar7->mCamera.Reset(local_a4, local_b0);
        break;
    case 0x97:
        i_this->m6E16 = 0;
        pcVar7->mCamera.Start();
        pcVar7->mCamera.SetTrimSize(0);
        dComIfGp_event_onEventFlag(8);
        fopAcM_OffStatus(i_this, fopAcStts_UNK4000_e);
        break;
    }
    if (i_this->m6E16 != 0) {
        local_c8.x = i_this->m6E1C.x + i_this->m6E48 * cM_ssin(i_this->m6E1A * 0x3300 & 0xffffU);
        local_c8.y = i_this->m6E1C.y + i_this->m6E48 * cM_scos(i_this->m6E1A * 0x3000 & 0xffffU);
        local_c8.z = i_this->m6E1C.z;
        local_bc.x = i_this->m6E28.x + i_this->m6E48 * cM_ssin(i_this->m6E1A * 0x3300 & 0xffffU);
        dVar8 = local_bc.x;
        local_bc.y = i_this->m6E28.y + i_this->m6E48 * cM_scos(i_this->m6E1A * 0x3000 & 0xffffU);
        local_bc.z = i_this->m6E28.z;
        iVar1 = (i_this->m6E48 * cM_scos(i_this->m02E2 * 0x1c00 & 0xffffU) * 7.5f);
        pcVar7->mCamera.Set(local_bc, local_c8, (short)iVar1, i_this->m6E3C);
        cLib_addCalc0(&i_this->m6E48, (REG0_F(16) + 2.0f), dVar8);
        JUTReport(30, 430, "K MAIN COUNT  %d", i_this->m6E18);
        JUTReport(410, 430, "K SUB  COUNT  %d", i_this->m6E1A);
        if (i_this->m6E16 < 100) {
            if (i_this->m6E18 == 2) {
                apdVar5->changeOriginalDemo();
            }
            if (i_this->m6E18 == 0x73) {
                apdVar5->changeDemoMode(daPy_demo_c::DEMO_LOOKUP_e);
            }
            if (i_this->m6E18 == 0x136) {
                apdVar5->changeDemoMode(daPy_demo_c::DEMO_UNK_028_e);
            }
            if (i_this->m6E18 == 0x1c4) {
                apdVar5->changeDemoMode(daPy_demo_c::DEMO_SURPRISED_e);
            }
            if (i_this->m6E18 == 0x1d1) {
                apdVar5->changeDemoMode(daPy_demo_c::DEMO_A_WAIT_e);
                apdVar5->changeDemoParam0(2);
            }
            if (i_this->m6E18 == 0x294) {
                apdVar5->changeDemoMode(daPy_demo_c::DEMO_UNK_027_e);
            }
            if (i_this->m6E18 == REG0_S(3) + 0x2dd) {
                apdVar5->changeDemoMode(daPy_demo_c::DEMO_A_WAIT_e);
                apdVar5->changeDemoParam0(2);
            }
        } else {
            if (i_this->m6E18 == 2) {
                apdVar5->changeOriginalDemo();
            }
            if (i_this->m6E18 == 10) {
                apdVar5->changeDemoMode(daPy_demo_c::DEMO_A_WAIT_e);
                apdVar5->changeDemoParam0(2);
            }
            if (i_this->m6E18 == REG0_S(2) + 0x2b5) {
                apdVar5->changeDemoMode(daPy_demo_c::DEMO_SMILE_e);
            }
            if (i_this->m6E18 == REG0_S(2) + 0x2c1) {
                apdVar5->changeDemoMode(daPy_demo_c::DEMO_UNK_029_e);
            }
        }
    }
}

static f32 at_size[] = {
    100.0f, 100.0f, 250.0f, 300.0f, 300.0f, 300.0f, 300.0f, 100.0f, 250.0f, 100.0f, 250.0f, 150.0f, 150.0f, 150.0f, 150.0f, 150.0f, 150.0f, 150.0f, 150.0f
};

/* 000072BC-00007608       .text btd_effect__FP9btd_class */
void btd_effect(btd_class* i_this) {
    static s32 eff_index[] = {0x43, 0x47, 0x20, 0x2D, 0x34};
    static u16 eff_name[] = {dPa_name::ID_SCENE_80A1, dPa_name::ID_SCENE_80A1, dPa_name::ID_SCENE_80A2, dPa_name::ID_SCENE_80A3, dPa_name::ID_SCENE_80A4};
    static u16 effF_name[] = {
        dPa_name::ID_SCENE_80A6,
        dPa_name::ID_SCENE_80A7,
        dPa_name::ID_SCENE_80A0,
        dPa_name::ID_SCENE_809F,
        dPa_name::ID_SCENE_80B1,
        dPa_name::ID_SCENE_80B3,
        dPa_name::ID_SCENE_A0B5
    };
    static u16 effF_nameR[] = {
        dPa_name::ID_SCENE_80A6,
        dPa_name::ID_SCENE_80A7,
        dPa_name::ID_SCENE_80A0,
        dPa_name::ID_SCENE_809F,
        dPa_name::ID_SCENE_80B0,
        dPa_name::ID_SCENE_80B2,
        dPa_name::ID_SCENE_A0B4
    };
    mDoExt_McaMorf* iVar2;
    JPABaseEmitter* iVar4;
    u16 userID;

    iVar2 = get_anm(i_this);
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m5FF8); i++)
        if (i_this->m5FF8[i] != 0) {
            MTXCopy(iVar2->getModel()->getAnmMtx(eff_index[i]), *calc_mtx);
            if (i_this->m02E0 >= 2) {
                MtxTrans(0.0f, -10000.0f, 0.0f, false);
            }
            iVar4 = i_this->m5FF8[i];
            iVar4->setGlobalRTMatrix(*calc_mtx);
        } else {
            iVar4 = dComIfGp_particle_set(eff_name[i], &i_this->current.pos);
            i_this->m5FF8[i] = iVar4;
        }
    for (s32 i = 0, j = 0; i < (s32)ARRAY_SIZE(i_this->m600C); i++, j++) {
        if (i_this->m6028[j] != 0) {
            i_this->m6028[j]--;
            iVar4 = i_this->m600C[i];
            if (iVar4 != NULL) {
                if (i >= 4) {
                    if (i_this->m02EA != 0) {
                        iVar4->setGlobalRTMatrix(iVar2->getModel()->getAnmMtx(0x48));
                    } else {
                        iVar4->setGlobalRTMatrix(iVar2->getModel()->getAnmMtx(0x44));
                    }
                } else {
                    iVar4->setGlobalRTMatrix(iVar2->getModel()->getAnmMtx(0x3a));
                }
            } else if (i == 6) {
                userID = dPa_name::ID_SCENE_A0B5;
                if (i_this->m02EA != 0) {
                    userID = dPa_name::ID_SCENE_A0B4;
                }
                iVar4 = dComIfGp_particle_setToon(
                    (s16)userID, &i_this->current.pos, NULL, NULL, 0xB9, &i_this->mPa_SmokeEcallBack[2], (u8)fopAcM_GetRoomNo(i_this)
                );
                i_this->m600C[i] = iVar4;
            } else {
                if (i_this->m02EA != 0) {
                    iVar4 = dComIfGp_particle_set(effF_nameR[j], &i_this->current.pos);
                    i_this->m600C[i] = iVar4;
                } else {
                    iVar4 = dComIfGp_particle_set(effF_name[j], &i_this->current.pos);
                    i_this->m600C[i] = iVar4;
                }
                if (i == 5) {
                    iVar4 = i_this->m600C[i];
                    iVar4->becomeImmortalEmitter();
                }
            }
        } else {
            iVar4 = i_this->m600C[i];
            if (i_this->m600C[i] != NULL) {
                if ((i != 3) && (i != 6)) {
                    if (i == 5) {
                        i_this->m600C[i]->quitImmortalEmitter();
                    }
                    iVar4 = i_this->m600C[i];
                    iVar4->mMaxFrame = -1;
                    iVar4->stopCreateParticle();
                }
                i_this->m600C[i] = 0;
            }
        }
    }
}

/* 00007608-00007950       .text btd_kankyo__FP9btd_class */
void btd_kankyo(btd_class* i_this) {
    u8 uVar1;
    u8 uVar2;

    uVar2 = 0;
    if (i_this->mKankyoTimer != 0) {
        i_this->mKankyoTimer--;
        i_this->mKankyoState = 2;
    }
    dKy_custom_timeset(l_HIO.m30);
    uVar1 = i_this->mKankyoState;
    if (uVar1 == 0) {
        cLib_addCalc0(&i_this->m60D0, 1.0f, 0.04f);
    } else if (uVar1 == 1) {
        cLib_addCalc2(&i_this->m60D4, 1.0f, 1.0f, 0.065f);
        i_this->m60D8 = (u8)l_HIO.m3C;
        i_this->m60D9 = (u8)l_HIO.m3E;
        i_this->m60DA = (u8)l_HIO.m40;
    } else if (uVar1 == 2) {
        cLib_addCalc2(&i_this->m60D0, 1.0f, 1.0f, 0.2f);
        cLib_addCalc2(&i_this->m60D4, 1.0f, 1.0f, 0.22500001f);
        dKy_custom_timeset(l_HIO.m34);
        i_this->m60D8 = (u8)l_HIO.m42;
        i_this->m60D9 = (u8)l_HIO.m44;
        i_this->m60DA = (u8)l_HIO.m46;
    } else if (uVar1 == 3) {
        cLib_addCalc2(&i_this->m60D0, 0.6f, 1.0f, 0.01f);
    } else if (uVar1 == 4) {
        cLib_addCalc2(&i_this->m60D0, 1.0, 1.0f, 0.2f);
    } else if (uVar1 == 5) {
        cLib_addCalc2(&i_this->m60D0, 1.0f, 1.0f, 0.005f);
        uVar2 = 1;
    } else if (uVar1 == 6) {
        i_this->m60D0 = 0.0f;
        uVar2 = 2;
    } else if (uVar1 == 7) {
        cLib_addCalc2(&i_this->m60D0, 1.0f, 1.0f, 0.03333f);
        uVar2 = 2;
        dKy_custom_timeset(l_HIO.m38);
    } else if (uVar1 == 8) {
        cLib_addCalc0(&i_this->m60D0, 1.0f, 0.06666f);
        uVar2 = 3;
    }
    i_this->m60B0.mColor.r = (u8)(i_this->m60D8 * i_this->m60D4);
    i_this->m60B0.mColor.g = (u8)(i_this->m60D9 * i_this->m60D4);
    i_this->m60B0.mColor.b = (u8)(i_this->m60DA * i_this->m60D4);
    i_this->m60B0.mPower = (REG0_F(8) + 5000.0f) * i_this->m60D4;
    i_this->m60B0.mFluctuation = REG0_F(9);
    switch (uVar2) {
    case 0: {
        dKy_custom_colset(0, 3, i_this->m60D0);
        break;
    }
    case 1: {
        dKy_custom_colset(0, 5, i_this->m60D0);
        break;
    }
    case 2: {
        dKy_custom_colset(6, 7, i_this->m60D0);
        break;
    }
    case 3: {
        dKy_custom_colset(0, 7, i_this->m60D0);
        break;
    }
    }
    i_this->mKankyoState = 0;
    cLib_addCalc0(&i_this->m60D4, 1.0f, 0.025f);
}

/* 00007950-000081B8       .text daBtd_Execute__FP9btd_class */
static BOOL daBtd_Execute(btd_class* i_this) {
    /* Nonmatching - cXyz, last for loop */
    static f32 hand_co_pos_X[] = {630.0f, 750.0f, 700.0f, -630.0f, -750.0f, -700.0f};
    static f32 hand_co_pos_Y[] = {0.0f, 100.0f, 0.0f, 0.0f, 100.0f, 0.0f};
    static f32 hand_co_pos_Z[] = {1680.0f, 1600.0f, 1320.0f, 1680.0f, 1600.0f, 1320.0f};
    static f32 hand_co_size_H[] = {250.0f, 200.0f, 200.0f, 250.0f, 200.0f, 200.0f};
    static f32 hand_co_size_R[] = {30.0f, 170.0f, 180.0f, 30.0f, 170.0f, 180.0f};
    u8 uVar1;
    daPy_py_c* apdVar3;
    short sVar4;
    mDoExt_McaMorf* this_02;
    fopAc_ac_c* pvVar6;
    cM3dGSph* this_03;
    cXyz* pDst;
    cM3dGCyl* this_04;
    J3DModel* pJVar9;
    f32 dVar11;
    float fVar12;
    cXyz local_78;
    cXyz local_6c;
    cXyz local_60;

    apdVar3 = daPy_getPlayerActorClass();
    if (dComIfGp_getStartStageName()[0] == 'X') {
        i_this->m6E15 = 0x32;
    }
    if (i_this->m6E90 != 0) {
        dCam_getBody()->SetTypeForce("Boss01", NULL);
    }
    i_this->m6E88 = 1;
    i_this->floor->getPos().y = i_this->m6E80;
    i_this->m6E7C += REG0_F(15) + 30.0f;
    if (i_this->m6E7C > REG0_F(18) + 2300.0f) {
        i_this->m6E7C = REG0_F(18) + 2300.0f;
    }
    mDoExt_baseAnm* btk = get_btk(i_this);
    mDoExt_baseAnm* brk = get_brk(i_this);
    if (kui == NULL) {
        kui = (kui_class*)fpcM_Search(k_a_d_sub, i_this);
    }
    if (dr2 == NULL) {
        dr2 = (dr2_class*)fpcM_Search(dr2_a_d_sub, i_this);
    }
    i_this->attention_info.distances[2] = 4;
    i_this->m02E2 = i_this->m02E2 + 1;
    for (int i = 0; i < 4; i++) {
        if (i_this->m02EC[i] != 0) {
            i_this->m02EC[i]--;
        }
    }
    if (i_this->mActionState != 0) {
        i_this->mActionState--;
    }
    move(i_this);
    fVar12 = l_HIO.m08;
    i_this->scale.z = l_HIO.m08;
    i_this->scale.y = fVar12;
    i_this->scale.x = fVar12;
    this_02 = get_anm(i_this);
    pJVar9 = this_02->getModel();
    pJVar9->setBaseScale(i_this->scale);
    mDoMtx_stack_c::transS(i_this->current.pos.x, i_this->current.pos.y, i_this->current.pos.z);
    mDoMtx_stack_c::YrotM(i_this->current.angle.y);
    mDoMtx_stack_c::XrotM(i_this->current.angle.x);
    mDoMtx_stack_c::ZrotM(i_this->current.angle.z);
    pJVar9->setBaseTRMtx(mDoMtx_stack_c::now);
    if (l_HIO.m05 == 0) {
        this_02->play(&i_this->eyePos, 0, 0);
    }
    this_02->calc();
    fVar12 = 1.0f;
    if (i_this->m02E0 != 0) {
        fVar12 = 0.6f;
    }
    dVar11 = fVar12;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m0428); i++) {
        if (((i_this->m02E0 != 0) && (i != 8)) && (i != 10)) {
            i_this->m0428[i].OffTgShield();
        }
        this_03 = &i_this->m0428[i];
        this_03->SetR(dVar11 * at_size[i]);
        if (i_this->m6E4C != 0) {
            local_60.x = 0.0f;
            local_60.y = -20000.0f;
            local_60.z = 0.0f;
            this_03->SetC(local_60);
        } else {
            this_03->SetC(i_this->m02FC[i]);
        }
        if ((i == 8) || (i == 10)) {
            if ((i_this->m5E84 == 1) || (i_this->m5E84 == 2)) {
                i_this->m0428[i].OnAtSetBit();
                if (i_this->m5E84 == 2) {
                    i_this->m0428[i].SetAtAtp(2);
                } else {
                    i_this->m0428[i].SetAtAtp(1);
                }
            } else {
                i_this->m0428[i].OffAtSetBit();
            }
            i_this->m0428[i].OffCoSetBit();
            i_this->m0428[i].OffTgSetBit();
        } else {
            if ((i < 2) && (i_this->m5E84 == 3)) {
                i_this->m0428[i].OnAtSetBit();
            } else {
                i_this->m0428[i].OffAtSetBit();
            }
            if ((i < 2) && (i_this->m02E0 == 0)) {
                i_this->m0428[i].OffCoSetBit();
                i_this->m0428[i].OffTgSetBit();
            }
        }
        dComIfG_Ccsp()->Set(&i_this->m0428[i]);
    }
    sVar4 = 0;
    dVar11 = 1.0f;
    if (i_this->m5E7C == 2) {
        sVar4 = -(REG0_S(5) + 0x1068);
        dVar11 = (REG0_F(10) + 0.95f);
    } else if (i_this->m5E7C == 3) {
        sVar4 = REG0_S(5) + 0x1068;
        dVar11 = (REG0_F(10) + 0.95f);
    }
    local_78.x = 0.0f;
    local_78.y = -10000.0f;
    local_78.z = 0.0f;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m575C); i++) {
        i_this->m575C[i].SetC(local_78);
    }
    mDoMtx_YrotS(*calc_mtx, (short)(i_this->current.angle.y + sVar4));
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m575C); i++) {
        uVar1 = i_this->m5E7C;
        if ((uVar1 != 0) && ((uVar1 == 1 || (uVar1 == 2 && (i <= 2))) || (uVar1 == 3 && (i >= 3)))) {
            local_6c.x = hand_co_pos_X[i];
            local_6c.y = hand_co_pos_Y[i];
            local_6c.z = (float)(dVar11 * hand_co_pos_Z[i]);
            pDst = &i_this->m5E98[i];
            MtxPosition(&local_6c, pDst);
            i_this->m5E98[i] += i_this->current.pos;
            this_04 = &i_this->m575C[i];
            this_04->SetC(*pDst);
            this_04->SetH(hand_co_size_H[i]);
            this_04->SetR(hand_co_size_R[i]);
        }
        dComIfG_Ccsp()->Set(&i_this->m575C[i]);
    }
    i_this->m5E7C = 0;
    pvVar6 = (fopAc_ac_c*)fpcM_Search(wepon_s_sub, i_this);
    if ((pvVar6 != NULL) && (pvVar6->speedF > 10.0f)) {
        local_6c = pvVar6->current.pos - i_this->eyePos;
        if (local_6c.abs() < 400.0f) {
            i_this->m02F8 = 0x14;
        }
    }
    local_6c = apdVar3->eyePos - i_this->eyePos;
    if (apdVar3->mCutType != 0) {
        fVar12 = local_6c.abs();
        if (fVar12 < 400.0f) {
            i_this->m02F8 = 0x14;
        }
    }
    if ((i_this->m02F8 != 0) && (i_this->m02E0 == 0)) {
        i_this->m02F8--;
        cLib_addCalcAngleS2(&i_this->m02FA, 13000, 1, 0x1000);
    } else {
        cLib_addCalcAngleS2(&i_this->m02FA, 0, 4, 0x400);
    }
    if (i_this->m02F0 == 0) {
        i_this->m02F0 = cM_rndF(150.0f) + 100.0f;
        i_this->m02F8 = 0x14;
    }
    if (i_this->m02E0 != 0) {
        i_this->m1A6C.OffTgShield();
    }
    i_this->m1A6C.SetR(REG0_F(5) + 80.0f);
    i_this->m1A6C.SetC(i_this->m03E0);
    dComIfG_Ccsp()->Set(&i_this->m1A6C);
    btk->play();
    brk->play();
    g_env_light.settingTevStruct(TEV_TYPE_BG0, &i_this->eyePos, &i_this->m60E0);
    hahen_move(i_this);
    sibuki_move(i_this);
    demo_camera(i_this);
    btd_effect(i_this);
    btd_kankyo(i_this);
    return TRUE;
}

/* 000081B8-000081C0       .text daBtd_IsDelete__FP9btd_class */
static BOOL daBtd_IsDelete(btd_class*) {
    return TRUE;
}

/* 000081C0-00008304       .text daBtd_Delete__FP9btd_class */
static BOOL daBtd_Delete(btd_class* i_this) {
    dComIfG_resDelete(&i_this->m02AC, "Btd");
    dComIfG_resDelete(&i_this->m02B4, "Magma");
    mDoHIO_deleteChild(l_HIO.mNo);
    // !@bug: this for loop only iterates through the first 19 elements of the array.
    for (int i = 0; i < 19; i++) {
        mDoAud_seDeleteObject(&i_this->m5E98[i]);
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->mBtdSibukiS); i++) {
        mDoAud_seDeleteObject(&i_this->mBtdSibukiS[i].m04);
    }
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m02FC); i++) {
        mDoAud_seDeleteObject(&i_this->m02FC[i]);
    }
    if (dr2 != NULL) {
        mDoAud_seDeleteObject(&dr2->unk_4A8);
    }
    mDoAud_seDeleteObject(&static_center_pos);
    dKy_efplight_cut(&i_this->m60B0);
    return TRUE;
}

/* 00008304-00008D30       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    J3DModelData* modelDataA;
    J3DAnmTextureSRTKey* pJVar10;
    int iVar11;
    J3DAnmTevRegKey* pJVar13;
    J3DModelData* modelDataB;
    J3DModel* pJVar15;
    f32 dVar18;

    btd_class* i_this = (btd_class*)a_this;
    i_this->m02BC = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Btd", BTD_BMD_BTD),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Btd", BTD_BCK_WAIT1),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        0,
        NULL,
        0,
        0x11020203
    );
    if ((i_this->m02BC == NULL) || (i_this->m02BC->getModel() == NULL)) {
        return FALSE;
    }
    for (u16 uVar16 = 0; uVar16 < i_this->m02BC->getModel()->getModelData()->getJointNum(); uVar16++) {
        if (joint_check[uVar16] >= 0) {
            i_this->m02BC->getModel()->getModelData()->getJointNodePointer(uVar16)->setCallBack(nodeCallBack);
        }
    }
    i_this->m02BC->getModel()->setUserArea((u32)i_this);
    pJVar15 = i_this->m02BC->getModel();
    i_this->btk = new mDoExt_btkAnm();
    JUT_ASSERT(5370, i_this->btk);
    pJVar10 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Btd", BTD_BTK_BTD);
    iVar11 = i_this->btk->init(pJVar15->getModelData(), pJVar10, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (iVar11 == 0) {
        return FALSE;
    }
    i_this->brk = new mDoExt_brkAnm();
    JUT_ASSERT(5390, i_this->brk);
    pJVar13 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Btd", BTD_BRK_BTD);
    iVar11 = i_this->brk->init(pJVar15->getModelData(), pJVar13, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    if (iVar11 == 0) {
        return FALSE;
    }
    i_this->m02C8 = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Btd", BTD_BMD_SOTAI),
        NULL,
        NULL,
        (J3DAnmTransformKey*)dComIfG_getObjectRes("Btd", BTD_BCK_WAIT1),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        0,
        NULL,
        0,
        0x11020203
    );
    if ((i_this->m02C8 == NULL) || (i_this->m02C8->getModel() == NULL)) {
        return FALSE;
    }
    for (u16 uVar16 = 0; uVar16 < i_this->m02C8->getModel()->getModelData()->getJointNum(); uVar16++) {
        if (joint_check[uVar16] >= 0) {
            i_this->m02C8->getModel()->getModelData()->getJointNodePointer(uVar16)->setCallBack(nodeCallBack);
        }
    }
    i_this->m02C8->getModel()->setUserArea((u32)i_this);
    pJVar15 = i_this->m02C8->getModel();
    i_this->btkS = new mDoExt_btkAnm();
    JUT_ASSERT(5432, i_this->btkS);
    pJVar10 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Btd", BTD_BTK_DEADA);
    iVar11 = i_this->btkS->init(pJVar15->getModelData(), pJVar10, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
    if (iVar11 == 0) {
        return FALSE;
    }
    pJVar10 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Btd", BTD_BTK_SOTAI);
    i_this->btkS->init(pJVar15->getModelData(), pJVar10, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, 0);
    i_this->brkS = new mDoExt_brkAnm();
    JUT_ASSERT(5463, i_this->brkS);
    pJVar13 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Btd", BTD_BRK_DEADA);
    iVar11 = i_this->brkS->init(pJVar15->getModelData(), pJVar13, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
    if (iVar11 == 0) {
        return FALSE;
    }
    pJVar13 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Btd", BTD_BRK_SOTAI);
    i_this->brkS->init(pJVar15->getModelData(), pJVar13, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, true, 0);
    i_this->m02D4 = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Btd", BTD_BMD_NAMAKUBI), NULL, NULL, NULL, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 0, NULL, 0, 0x11020203
    );
    if ((i_this->m02D4 == NULL) || (pJVar15 = i_this->m02D4->getModel(), pJVar15 == NULL)) {
        return FALSE;
    }
    i_this->m02D8 = new mDoExt_btkAnm();
    if (i_this->m02D8 == NULL) {
        return FALSE;
    }
    pJVar10 = (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("Btd", BTD_BTK_NAMAKUBI);
    iVar11 = i_this->m02D8->init(pJVar15->getModelData(), pJVar10, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
    if (iVar11 == 0) {
        return FALSE;
    }
    i_this->m02DC = new mDoExt_brkAnm();
    if (i_this->m02DC == NULL) {
        return FALSE;
    }
    pJVar13 = (J3DAnmTevRegKey*)dComIfG_getObjectRes("Btd", BTD_BRK_NAMAKUBI);
    iVar11 = i_this->m02DC->init(pJVar15->getModelData(), pJVar13, true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, 0);
    if (iVar11 == 0) {
        return FALSE;
    }
    modelDataA = (J3DModelData*)dComIfG_getObjectRes("Btd", BTD_BMD_HAHENA);
    modelDataB = (J3DModelData*)dComIfG_getObjectRes("Btd", BTD_BMD_KAMENA);
    JUT_ASSERT(5544, modelDataA && modelDataB);
    dVar18 = 1.0f;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->hahen); i++) {
        if (i < 5) {
            pJVar15 = mDoExt_J3DModel__create(modelDataB, 0, 0x11020203);
            i_this->hahen[i].model = pJVar15;
        } else {
            pJVar15 = mDoExt_J3DModel__create(modelDataA, 0, 0x11020203);
            i_this->hahen[i].model = pJVar15;
        }
        JUT_ASSERT(5594, i_this->hahen[i].model);
        cXyz vec;
        vec.x = dVar18 + cM_rndF(0.5f);
        vec.y = dVar18 + cM_rndF(0.5f);
        vec.z = dVar18 + cM_rndF(0.5f);
        i_this->hahen[i].model->setBaseScale(vec);
    }
    return TRUE;
}

/* 00008D78-000091D0       .text daBtd_Create__FP10fopAc_ac_c */
static cPhs_State daBtd_Create(fopAc_ac_c* a_this) {
    /* Nonmatching - "mr r27, r3" instruction in wrong place */
    static dCcD_SrcSph at_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_SPIKE,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Nrm_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK9,
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
            /* Radius */ 200.0f,
        }},
    };
    static dCcD_SrcSph eye_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 50.0f,
        }},
    };
    static dCcD_SrcSph fire_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_FIRE,
            /* SrcObjAt  Atp     */ 2,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNKA,
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
            /* Radius */ 100.0f,
        }},
    };
    static dCcD_SrcSph sibuki_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_FIRE,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK2,
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
            /* Radius */ 40.0f,
        }},
    };
    static dCcD_SrcCyl hand_cyl_src = {
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
            /* SrcGObjTg Se      */ dCcG_SE_UNK5,
            /* SrcGObjTg HitMark */ dCcg_TgHitMark_Purple_e,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 0.0f,
            /* Height */ 0.0f,
        }},
    };

    cPhs_State res;

    btd_class* i_this = (btd_class*)a_this;
    fopAcM_SetupActor(i_this, btd_class);
    res = dComIfG_resLoad(&i_this->m02AC, "Btd");
    if (res != cPhs_COMPLEATE_e) {
        return res;
    } else {
        res = dComIfG_resLoad(&i_this->m02B4, "Magma");
        if (res != cPhs_COMPLEATE_e) {
            return res;
        } else {
            dr2 = NULL;
            kui = NULL;
            i_this->mPa_SmokeEcallBack[0].setFollowOff();
            i_this->mPa_SmokeEcallBack[1].setFollowOff();
            i_this->mPa_SmokeEcallBack[2].setFollowOff();
            if ((dComIfGs_isStageBossEnemy()) && (dComIfGp_getStartStageName()[0] != 'X')) {
                res = cPhs_ERROR_e;
            } else {
                if (!fopAcM_entrySolidHeap(i_this, useHeapInit, 0x5B8C0)) {
                    res = cPhs_ERROR_e;
                } else {
                    i_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
                    l_HIO.mNo = mDoHIO_createChild("ボスゴーマ", &l_HIO); // Boss Goma
                    i_this->m03EC.Init(0xff, 0xff, i_this);
                    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m0428); i++) {
                        i_this->m0428[i].Set(at_sph_src);
                        i_this->m0428[i].SetStts(&i_this->m03EC);
                    }
                    i_this->m1A6C.SetStts(&i_this->m03EC);
                    i_this->m1A6C.Set(eye_sph_src);
                    i_this->m1B98.SetStts(&i_this->m03EC);
                    i_this->m1B98.Set(fire_sph_src);
                    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m1CC4); i++) {
                        i_this->m1CC4[i].Set(sibuki_sph_src);
                        i_this->m1CC4[i].SetStts(&i_this->m03EC);
                    }
                    for (s32 i = 0; i < (s32)ARRAY_SIZE(i_this->m575C); i++) {
                        i_this->m575C[i].Set(hand_cyl_src);
                        i_this->m575C[i].SetStts(&i_this->m03EC);
                    }
                    i_this->m02EC[0] = (s16)(l_HIO.m14 + cM_rndF(50.0f));
                    dKy_efplight_set(&i_this->m60B0);
                    i_this->health = 10;
                    i_this->max_health = 10;
                    if ((g_dComIfG_gameInfo.save.getMemory().getBit().isStageBossDemo()) || (dComIfGp_getStartStageName()[0] == 'X')) {
                        dComIfGs_offTmpBit(0x480);
                        i_this->m6E80 = -50.0f;
                        i_this->m6E84 = 0.0f;
                        if (dComIfGp_getStartStageName()[0] == 'X') {
                            mDoAud_bgmStart(JA_BGM_PAST_GOMA);
                        } else {
                            mDoAud_bgmStart(JA_BGM_GOMA);
                        }
                        i_this->m02EC[0] = (s16)((cM_rndF(50.0f) + 70.0f) + 100.0f);
                        fopAcM_OnStatus(i_this, fopAcStts_SHOWMAP_e | fopAcStts_UNK4000_e);
                    } else {
                        i_this->m02E4 = 10;
                        i_this->m6E80 = -50.0f;
                        i_this->m6E84 = -30.0f;
                        i_this->m02EC[0] = REG0_S(4) + 0x96;
                        i_this->m6E7C = REG0_F(18) + 2300.0f;
                        fopAcM_OnStatus(i_this, fopAcStts_SHOWMAP_e | fopAcStts_UNK4000_e);
                    }
                    i_this->m6E90 = 1;
                    if (dComIfGp_createMagma()) {
                        cXyz local_48;
                        local_48.x = 0.0f;
                        local_48.y = -300.0f;
                        local_48.z = 0.0f;
                        i_this->floor = dComIfGp_getMagma()->newFloor(local_48, i_this->scale, fopAcM_GetRoomNo(i_this), -0xFA);
                        JUT_ASSERT(6096, i_this->floor != NULL);
                    }
                    fopAcM_create(PROC_Ykgr, 0x10FF00, &i_this->current.pos);
                    dKy_custom_timeset(l_HIO.m30);
                    res = cPhs_COMPLEATE_e;
                }
            }
        }
    }
    return res;
}

static actor_method_class l_daBtd_Method = {
    (process_method_func)daBtd_Create,
    (process_method_func)daBtd_Delete,
    (process_method_func)daBtd_Execute,
    (process_method_func)daBtd_IsDelete,
    (process_method_func)daBtd_Draw,
};

actor_process_profile_definition g_profile_BTD = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BTD,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(btd_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BTD,
    /* Actor SubMtd */ &l_daBtd_Method,
    /* Status       */ fopAcStts_UNK40000_e | fopAcStts_BOSS_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
