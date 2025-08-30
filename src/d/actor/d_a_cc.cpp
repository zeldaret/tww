/**
 * d_a_cc.cpp
 * Enemy - ChuChu
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_cc.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_bomb2.h"
#include "d/res/res_cc.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/d_com_inf_game.h"
#include "d/d_cc_uty.h"
#include "d/d_material.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_kankyo_mng.h"

static u8 DEMO_COME_START_FLAG;
static u8 DEMO_RET_START_FLAG;
static u8 DEMO_SHORT_CUT_FLAG;
static fopAc_ac_c* target_info[10];
static s32 target_info_count;

/* 00000078-000002AC       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == 0) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 iVar4 = joint->getJntNo();
        J3DModel* pJVar2 = j3dSys.getModel();
        cc_class* pvVar4 = (cc_class*)pJVar2->getUserArea();

        if (pvVar4 != NULL) {
            if (iVar4 == 0) {
                MTXCopy(pJVar2->getAnmMtx(iVar4), *calc_mtx);
                cMtx_ZrotM(*calc_mtx, pvVar4->m3BA);
                pJVar2->setAnmMtx(iVar4, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            }

            if (iVar4 <= 3) {
                MTXCopy(pJVar2->getAnmMtx(iVar4), *calc_mtx);
                f32 fVar1 = iVar4 * 0.5f;
                cMtx_YrotM(*calc_mtx, pvVar4->m310.y * fVar1);
                cMtx_XrotM(*calc_mtx, pvVar4->m310.x * fVar1);
                cMtx_ZrotM(*calc_mtx, pvVar4->m310.z * fVar1);

                if (iVar4 == 3) {
                    cXyz sp08(0.0f, 0.0f, 0.0f);
                    MtxPosition(&sp08, &pvVar4->m470);
                }
                pJVar2->setAnmMtx(iVar4, *calc_mtx);
                MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
            }
        }
    }
    return TRUE;
}

/* 000002E8-00000524       .text draw_SUB__FP8cc_class */
void draw_SUB(cc_class* i_this) {
    if ((i_this->mBehaviorType == 2) && (i_this->m2FB != 3)) {
        i_this->m2B4->calc();
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);
        enemy_fire(&i_this->mEnemyFire);
    } else {
        J3DModel* pJVar1;

        if (i_this->m2F5 != 0x35) {
            if (i_this->m301 == 0) {
                pJVar1 = i_this->m2B4->getModel();
            } else {
                pJVar1 = i_this->m2D8->getModel();
            }
        } else {
            pJVar1 = i_this->m2BC->getModel();
        }

        mDoMtx_stack_c::transS(i_this->actor.current.pos.x, i_this->actor.current.pos.y - i_this->m328, i_this->actor.current.pos.z);
        mDoMtx_stack_c::XrotM(i_this->m316.x);
        mDoMtx_stack_c::ZrotM(i_this->m316.z);
        mDoMtx_stack_c::YrotM(i_this->actor.shape_angle.y);
        mDoMtx_stack_c::XrotM(i_this->actor.shape_angle.x);
        mDoMtx_stack_c::ZrotM(i_this->actor.shape_angle.z);

        cXyz sp08;
        if (i_this->mCurrAction != 5 && i_this->m2F5 != 0x35 && i_this->m301 == 0 && i_this->mCurrAction != 6 && i_this->m34E[4] == 0) {
            sp08.x = 1.1f;
            sp08.y = 1.0f;
            sp08.z = 0.9f;
            i_this->m31C += 1000;
        } else {
            sp08.setall(i_this->m334);
            i_this->m31C = 0;
        }

        mDoMtx_stack_c::YrotM(i_this->m31C);
        mDoMtx_stack_c::scaleM(sp08);
        mDoMtx_stack_c::YrotM(-i_this->m31C);
        pJVar1->setBaseTRMtx(mDoMtx_stack_c::get());

        if (i_this->m301 == 0) {
            i_this->m2B4->calc();
            enemy_fire(&i_this->mEnemyFire);
        }

        if (i_this->m2FE != 0) {
            J3DModel* model = i_this->m2C4->getModel();
            model->setBaseTRMtx(mDoMtx_stack_c::get());
        }

        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);
    }
}

/* 00000524-00000900       .text daCC_Draw__FP8cc_class */
static BOOL daCC_Draw(cc_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    J3DModel* pJVar3 = i_this->m2B4->getModel();

    if (i_this->mBehaviorType == 4) {
        return TRUE;
    }

    dSnap_RegistFig(0xac, a_this, 1.0f, 1.0f, 1.0f);

    if (i_this->m2F5 != 0x35) {
        i_this->m2B8->entry(pJVar3->getModelData());
        i_this->m2B8->setFrame(i_this->mColorType);

        if (i_this->m2FE != 0) {
            pJVar3 = i_this->m2C4->getModel();

            switch (i_this->m2FE) {
            case 1:
                i_this->m2C8->entry(pJVar3->getModelData());
                i_this->m2C8->setFrame(i_this->m2FF);
                i_this->m2D0->entry(pJVar3->getModelData());
                i_this->m2D0->setFrame(i_this->m2FF);
                break;

            case 2:
                i_this->m2CC->entry(pJVar3->getModelData());
                i_this->m2CC->setFrame(i_this->m2FF);
                i_this->m2D4->entry(pJVar3->getModelData());
                i_this->m2D4->setFrame(i_this->m2FF);
                break;
            }
        }

        if (i_this->m301 != 0) {
            pJVar3 = i_this->m2D8->getModel();
        }
    } else {
        pJVar3 = i_this->m2BC->getModel();
        i_this->m2C0->entry(pJVar3->getModelData());
        i_this->m2C0->setFrame(i_this->mColorType);
    }

    g_env_light.setLightTevColorType(pJVar3, &a_this->tevStr);

    if ((i_this->mEnemyIce).mFreezeTimer > 0x14) {
        dMat_control_c::iceUpdateDL(i_this->m2B4, -1, &i_this->mDFC);
        return TRUE;
    }

    if (i_this->m2F5 != 0x35) {
        if (i_this->m301 == 0) {
            i_this->m2B4->entryDL();
            a_this->model = i_this->m2B4->mpModel;
        } else {
            i_this->m2D8->updateDL();
        }

        if (i_this->m2FE != 0) {
            i_this->m2C4->updateDL();
        }
    } else {
        i_this->m2BC->updateDL();
    }

    if (i_this->m2F9 == 0) {
        f32 fVar2 = 36.0f;
        if ((i_this->m320 == CC_BCK_TACHI2HUSE) || (i_this->m320 == CC_BCK_HUSE_WALK)) {
            fVar2 = 50.0f;
        }

        dComIfGd_setSimpleShadow2(&a_this->current.pos, i_this->mAcch.GetGroundH(), fVar2, i_this->mAcch.m_gnd);
    }

    if (i_this->m2F5 != 0x35) {
        i_this->m2B8->remove(i_this->m2B4->getModel()->getModelData());
        if (i_this->m2FE != 0) {
            pJVar3 = i_this->m2C4->mpModel;
            switch (i_this->m2FE) {
            case 1:
                i_this->m2C8->remove(pJVar3->getModelData());
                i_this->m2D0->remove(pJVar3->getModelData());
                break;

            case 2:
                i_this->m2CC->remove(pJVar3->getModelData());
                i_this->m2D4->remove(pJVar3->getModelData());
                break;
            }
        }
    } else {
        i_this->m2C0->remove(pJVar3->getModelData());
    }
    return TRUE;
}

/* 00000900-00000AB0       .text cc_eff_set__FP8cc_classUc */
void cc_eff_set(cc_class* i_this, unsigned char arg1) {
    u16 userID = dPa_name::ID_COMMON_03F0;
    cXyz sp1C = i_this->m470;
    GXColor sp18 = {};

    if (arg1 != 0) {
        userID = dPa_name::ID_COMMON_03EF;
        sp1C = i_this->actor.current.pos;
    }

    JPABaseEmitter* pJVar6 = dComIfGp_particle_set(userID, &sp1C, &i_this->actor.shape_angle);
    if (pJVar6 != NULL) {
        static GXColor eff_color_dt[] = {
            {0x8d, 0xde, 0x43, 0xFF},
            {0xEC, 0x4A, 0x22, 0xFF},
            {0x5B, 0xAD, 0xC8, 0xFF},
            {0x28, 0x10, 0x27, 0xFF},
            {0xFF, 0xC3, 0x3C, 0xFF},
        };

        f32 tmp = (i_this->actor.tevStr.mColorK0.r / 255.0f);
        sp18.r = tmp * eff_color_dt[i_this->mColorType].r;

        tmp = (i_this->actor.tevStr.mColorK0.g / 255.0f);
        sp18.g = tmp * eff_color_dt[i_this->mColorType].g;

        tmp = (i_this->actor.tevStr.mColorK0.b / 255.0f);
        sp18.b = tmp * eff_color_dt[i_this->mColorType].b;

        pJVar6->setGlobalPrmColor(sp18.r, sp18.g, sp18.b);
    }
}

/* 00000AB0-00000BDC       .text anm_init__FP8cc_classifUcfi */
void anm_init(cc_class* i_this, const int transformResIdx, const float morf, const unsigned char loopMode, const float speed, const int soundResIdx) {
    i_this->m320 = transformResIdx;
    if (soundResIdx >= 0) {
        i_this->m2B4->setAnm(
            (J3DAnmTransform*)dComIfG_getObjectRes("CC", transformResIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("CC", soundResIdx)
        );
    } else {
        i_this->m2B4->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("CC", transformResIdx), loopMode, morf, speed, 0.0f, -1.0f, NULL);
    }
}

/* 00000BDC-00000C74       .text damage_mode_move__FP8cc_class */
void damage_mode_move(cc_class* i_this) {
    i_this->m2F6 = 2;
    if (i_this->m2F5 != 0x2d && i_this->m2F5 != 0x2e) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_STARS_BLOW, &i_this->actor.attention_info.position);
        i_this->mCurrAction = 3;
        i_this->m2F5 = 0x28;
    }
}

/* 00000C74-00000D30       .text s_b_sub__FPvPv */
void* s_b_sub(void* arg0, void* arg1) {
    if (fopAcM_IsActor(arg0)) {
        bool bVar2 = false;
        if (fopAcM_GetName(arg0) == PROC_BOMB) {
            daBomb_c* bomb = (daBomb_c*)arg0;
            if (bomb->chk_state(daBomb_c::STATE_0)) {
                bVar2 = true;
            }
        } else if (fopAcM_GetName(arg0) == PROC_Bomb2) {
            daBomb2::Act_c* bomb2 = (daBomb2::Act_c*)arg0;
            if (bomb2->chk_explode() != false) {
                bVar2 = true;
            }
        }

        if (bVar2 && target_info_count < ARRAY_SSIZE(target_info)) {
            target_info[target_info_count] = (fopAc_ac_c*)arg0;
            target_info_count++;
        }
    }
    return FALSE;
}

/* 00000D30-00001028       .text naraku_check__FP8cc_class */
void naraku_check(cc_class* i_this) {
    if (i_this->mAcch.GetGroundH() != -G_CM3D_F_INF && dComIfG_Bgsp()->ChkPolySafe(i_this->mAcch.m_gnd) &&
        dComIfG_Bgsp()->GetGroundCode(i_this->mAcch.m_gnd) == 4)
    {
        i_this->m2FA++;
        if (i_this->actor.current.pos.y < -500.0f || i_this->m2FA > 0x32) {
            i_this->actor.speedF = 0.0f;
            i_this->actor.speed.x = 0.0f;
            i_this->actor.speed.y = 0.0f;
            i_this->actor.speed.z = 0.0f;
            i_this->actor.gravity = 0.0f;
            fopAcM_delete(&i_this->actor);
            fopAcM_onActor(&i_this->actor);
            return;
        }
    }

#if VERSION > VERSION_DEMO
    if (i_this->actor.current.pos.y < i_this->m3BC.y - 20000.0f) {
        fopAcM_delete(&i_this->actor);
        fopAcM_onActor(&i_this->actor);
    } else
#endif
        if (i_this->mAcch.MaskWaterIn())
    {
        if (i_this->mCurrAction != 1) {
            cXyz sp24 = i_this->actor.current.pos;
            sp24.y = i_this->mAcch.m_wtr.GetHeight();
            if (!i_this->m300) {
                fopKyM_createWpillar(&sp24, 1.0f, 0.4f, 0);
                fopAcM_seStart(&i_this->actor, JA_SE_OBJ_FALL_WATER_M, 0);
                i_this->m300 = true;
                cXyz sp18(0.5f, 0.5f, 0.5f);
#if VERSION == VERSION_DEMO
                i_this->m368.remove();
                dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &i_this->actor.current.pos, NULL, &sp18, 0xff, &i_this->m368);
                i_this->m368.setRate(0.0f);
#else
                i_this->m390.remove();
                dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &i_this->actor.current.pos, NULL, &sp18, 0xff, &i_this->m390);
                i_this->m390.setRate(0.0f);
#endif
            }

            f32 fVar1 = 40.0f + REG12_F(0);
            if (i_this->m2FE != 0) {
                fVar1 = 100.0f + REG12_F(0);
            }

            if (i_this->actor.current.pos.y < sp24.y - fVar1) {
                if (i_this->m2FE != 0) {
                    i_this->actor.speedF = 0.0f;
                    i_this->actor.speed.x = 0.0f;
                    i_this->actor.speed.y = 0.0f;
                    i_this->actor.speed.z = 0.0f;
                    i_this->actor.gravity = 0.0f;
                    fopAcM_delete(&i_this->actor);
                    fopAcM_onActor(&i_this->actor);
                }

                i_this->mCurrAction = 1;
                i_this->m2F5 = 0x14;

                if (i_this->actor.health <= 0 && (i_this->mCurrAction != 4)) {
                    i_this->mCurrAction = 4;
                    i_this->m2F5 = 0x32;
                }
            }
        }

    } else if (i_this->m300) {
        i_this->m2F8 = 0;
        i_this->m300 = false;
#if VERSION == VERSION_DEMO
        i_this->m368.remove();
#else
        i_this->m390.remove();
#endif
    }
}

/* 00001028-00001068       .text denki_start__FP8cc_class */
void denki_start(cc_class* i_this) {
    if ((i_this->mColorType != 2) && (i_this->mColorType != 4)) {
        return;
    }

    if (i_this->m2F7 != 0) {
        return;
    }

    i_this->mCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
    i_this->mCyl.OnAtHitBit();
    i_this->m2F7 = 1;
    i_this->mCyl.SetTgSpl(dCcG_Tg_Spl_UNK1);
}

/* 00001068-000010D8       .text denki_end__FP8cc_class */
void denki_end(cc_class* i_this) {
    if ((i_this->mColorType == 2) || (i_this->mColorType == 4)) {
#if VERSION == VERSION_DEMO
        if (i_this->mpEmitter1 == NULL) {
            return;
        }

        i_this->mpEmitter1->becomeInvalidEmitter();
        i_this->mpEmitter1 = NULL;
        i_this->mpEmitter2->becomeInvalidEmitter();
        i_this->mpEmitter2 = NULL;
#else
        i_this->m368.remove();
        i_this->m37C.remove();
#endif
        i_this->m2F7 = 0;
        i_this->mCyl.SetTgSpl(dCcG_Tg_Spl_UNK0);
    }
}

/* 000010D8-00001344       .text shock_damage_check__FP8cc_class */
BOOL shock_damage_check(cc_class* i_this) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    cXyz sp1C;
    target_info_count = 0;

    for (s32 i = 0; i < ARRAY_SSIZE(target_info); i++) {
        target_info[i] = NULL;
    }

    fpcM_Search(s_b_sub, &i_this->actor);

    if (target_info_count != 0) {
        for (s32 i = 0; i < target_info_count; i++) {
            sp1C.x = target_info[i]->current.pos.x - i_this->actor.current.pos.x;
            sp1C.z = target_info[i]->current.pos.z - i_this->actor.current.pos.z;

            if (std::sqrtf(SQUARE(sp1C.x) + SQUARE(sp1C.z)) < 1000.0f) {
                if (i_this->m302 == 0) {
                    damage_mode_move(i_this);
                    i_this->m302 = 1;
                    return TRUE;
                }
            } else {
                i_this->m302 = 0;
            }
        }
    } else {
        i_this->m302 = 0;
    }

    if (player->checkHammerQuake()) {
        sp1C = player->getSwordTopPos();
        sp1C.x -= i_this->actor.current.pos.x;
        sp1C.z -= i_this->actor.current.pos.z;
        if (std::sqrtf(SQUARE(sp1C.x) + SQUARE(sp1C.z)) < 1000.0f) {
            damage_mode_move(i_this);
            return TRUE;
        }
    }
    return FALSE;
}

/* 00001344-000013B8       .text black_light_check__FP8cc_class */
void black_light_check(cc_class* i_this) {
    if (i_this->mColorType == 3) {
        if (i_this->mCurrAction != 6 && dComIfGp_getDetect().chk_light(&i_this->actor.current.pos)) {
#if VERSION > VERSION_DEMO
            i_this->mStts.SetWeight(0xFE);
#endif
            i_this->mCurrAction = 6;
            i_this->m2F5 = 0x50;
        }
    }
}

/* 000013B8-00001F78       .text body_atari_check__FP8cc_class */
BOOL body_atari_check(cc_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    i_this->mStts.Move();

    if (i_this->mCyl.ChkTgHit()) {

        cCcD_Obj* pcVar6 = i_this->mCyl.GetTgHitObj();
        fopAc_ac_c* pdVar7 = i_this->mCyl.GetTgHitAc();
        if (pcVar6 == NULL) {
            return FALSE;
        }

        cXyz sp30 = *i_this->mCyl.GetTgHitPosP();

        if ((i_this->m304 != 0) && (pdVar7 != NULL) && (dComIfGp_getPlayer(0) != pdVar7)) {
            i_this->m304 = 2;
            a_this->health = 0;
            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &sp30);
            cXyz sp24(2.0f, 2.0f, 2.0f);
            dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, &sp30, &player->shape_angle, &sp24);
            i_this->mCurrAction = 3;
            i_this->m2F5 = 0x28;
            return TRUE;
        }

        i_this->actor.setBtNowFrame(1000.0f);

        CcAtInfo sp3C;
        sp3C.pParticlePos = NULL;
        bool bVar4 = false;
        i_this->m2F6 = 0;

        if (pcVar6->ChkAtType(AT_TYPE_LIGHT)) {
            if (i_this->mColorType == 3) {
                if (i_this->mCurrAction != 6) {
#if VERSION > VERSION_DEMO
                    i_this->mStts.SetWeight(0xfe);
#endif
                    i_this->mCurrAction = 6;
                    i_this->m2F5 = 0x50;
                    return TRUE;
                }
            } else {
                return FALSE;
            }
        }

        switch (pcVar6->GetAtType()) {
        case AT_TYPE_GRAPPLING_HOOK:
            if (a_this->stealItemLeft > 0) {
                s8 sVar9 = a_this->health;
                u8 bVar1 = a_this->stealItemBitNo;
                a_this->health = 10;
                sp3C.mpObj = i_this->mCyl.GetTgHitObj();
                cc_at_check(a_this, &sp3C);
                if (i_this->mColorType == 2) {
                    a_this->stealItemBitNo = bVar1;
                }
                a_this->health = sVar9;
            }

            if (i_this->m2F5 == 0x15) {
                fopAcM_seStart(a_this, JA_SE_LK_MS_WEP_HIT, 0x36);
#if VERSION == VERSION_DEMO
                a_this->gravity = -(REG12_F(19) + 10.0f);
#else
                a_this->gravity = -(REG12_F(19) + 3.0f);
#endif
                i_this->m324 = 0.0f;
                i_this->m2F8 = 0;
                return FALSE;
            }
            bVar4 = true;
            i_this->m2F6 = 9;
            break;

        case AT_TYPE_MACHETE:
        case AT_TYPE_SWORD:
        case AT_TYPE_UNK800:
        case AT_TYPE_DARKNUT_SWORD:
        case AT_TYPE_MOBLIN_SPEAR:
            if (i_this->m2F7 != 0) {
                return FALSE;
            }

            if (player->getCutType() == 6 || player->getCutType() == 7 || player->getCutType() == 8 || player->getCutType() == 9 ||
                player->getCutType() == 10 || player->getCutType() == 0xc || player->getCutType() == 0xe || player->getCutType() == 5 ||
                player->getCutType() == 0xf || player->getCutType() == 0x10 || player->getCutType() == 0x15 || player->getCutType() == 0x17 ||
                player->getCutType() == 0x19 || player->getCutType() == 0x1a || player->getCutType() == 0x1b || player->getCutType() == 0x1e ||
                player->getCutType() == 0x1f)
            {
                i_this->m2F6 = 1;
            }

            if (i_this->mColorType == 3) {
                fopAcM_seStart(a_this, JA_SE_LK_SW_HIT_S, 0x36);
                bVar4 = true;
                i_this->m2F6 = 0;
            }
            break;

        case AT_TYPE_WIND:
            bVar4 = true;
            i_this->m2F6 = 3;
            a_this->current.angle.y = cM_atan2s(a_this->current.pos.x - sp30.x, a_this->current.pos.z - sp30.z);
            if ((pdVar7 != NULL) && (pdVar7 == player)) {
                a_this->current.angle.y = player->shape_angle.y;
                if (i_this->m2F5 == 0x15) {
                    a_this->speedF = REG12_F(18) + 20.0f;
                    return FALSE;
                }
            }
            break;

        case AT_TYPE_BOOMERANG:
            i_this->m2F6 = 4;
            bVar4 = true;
            if (i_this->m2F5 == 0x15) {
                fopAcM_seStart(a_this, JA_SE_LK_W_WEP_HIT, 0x36);
#if VERSION == VERSION_DEMO
                a_this->gravity = -(REG12_F(19) + 10.0f);
#else
                a_this->gravity = -(REG12_F(19) + 3.0f);
#endif
                i_this->m324 = 0.0f;
                i_this->m2F8 = 0;
                return FALSE;
            }
            break;

        case AT_TYPE_BOKO_STICK:
        case AT_TYPE_UNK2000:
        case AT_TYPE_STALFOS_MACE:
            if (i_this->mColorType == 3) {
                fopAcM_seStart(a_this, JA_SE_LK_W_WEP_HIT, 0x36);
                bVar4 = true;
                i_this->m2F6 = 0;
            }
            break;

        case AT_TYPE_HOOKSHOT:
            if (i_this->mColorType == 3) {
                fopAcM_seStart(a_this, JA_SE_LK_MS_WEP_HIT, 0x36);
            }
            i_this->m2F6 = 7;
            bVar4 = true;
            if (i_this->m2F5 == 0x15) {
                a_this->speedF = 0.0f;
                a_this->speed.x = 0.0f;
                a_this->speed.y = 0.0f;
                a_this->speed.z = 0.0f;
                a_this->gravity = -(REG12_F(19) + 3.0f);
                i_this->m324 = 0.0f;
                i_this->m2F8 = 0;
                return 0;
            }
            break;

        case AT_TYPE_SKULL_HAMMER:
            if (i_this->mColorType == 3) {
                fopAcM_seStart(a_this, JA_SE_LK_HAMMER_HIT, 0x36);
            }

            i_this->m2F6 = 1;

            if (player->getCutType() == 0x12 || player->getCutType() == 0x13) {
                i_this->m2F6 = 6;
            }

            if (i_this->mColorType == 3) {
                bVar4 = true;
                i_this->m2F6 = 0;
            }
            break;

        case AT_TYPE_FIRE:
        case AT_TYPE_FIRE_ARROW:
            if (i_this->mColorType == 3) {
                bVar4 = true;
                i_this->m2F6 = 0;
                fopAcM_seStart(a_this, JA_SE_LK_MS_WEP_HIT, 0x36);
            } else {
                i_this->mEnemyFire.mFireDuration = 100;
                i_this->m2F6 = 8;
            }
            break;

        case AT_TYPE_LIGHT_ARROW:
            i_this->mEnemyIce.mLightShrinkTimer = 1;
            i_this->mEnemyIce.mParticleScale = 0.5f;
            i_this->mEnemyIce.mYOffset = 80.0f;
            fopAcM_seStart(a_this, JA_SE_CM_CC_DIE_SWING, 0);
            fopAcM_monsSeStart(a_this, JA_SE_CV_CC_DIE, 0);
            a_this->attention_info.flags = 0;
            denki_end(i_this);
            i_this->m2F6 = 8;
            break;

        case AT_TYPE_ICE_ARROW:
            if (i_this->mColorType == 3) {
                bVar4 = true;
                i_this->m2F6 = 0;
                fopAcM_seStart(a_this, JA_SE_LK_MS_WEP_HIT, 0x36);
            } else {
                i_this->mEnemyIce.mFreezeDuration = REG8_S(2) + 200;
                if (REG8_S(2) != 0) {
                    a_this->health = 100;
                }

                fopAcM_seStart(a_this, JA_SE_CM_CC_DIE_SWING, 0);
                fopAcM_monsSeStart(a_this, JA_SE_CV_CC_DIE, 0);
                enemy_fire_remove(&i_this->mEnemyFire);
                denki_end(i_this);
                bVar4 = true;
                i_this->m2F6 = 8;
            }
            break;

        default:
            if (i_this->mColorType == 3) {
                bVar4 = true;
                i_this->m2F6 = 0;
                fopAcM_seStart(a_this, JA_SE_LK_MS_WEP_HIT, 0x36);
            }
            break;
        }

        if (!bVar4) {
            sp3C.mpObj = i_this->mCyl.GetTgHitObj();
            cc_at_check(a_this, &sp3C);

            if ((i_this->m2F6 == 1) || (i_this->m2F6 == 6) || (a_this->health <= 0)) {
                dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &sp30);
                cXyz sp18(2.0f, 2.0f, 2.0f);
                dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, &sp30, &player->shape_angle, &sp18);
            } else {
                dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, &sp30, &player->shape_angle);
            }
        }

        if ((i_this->m2F6 == 7) && (i_this->mCurrAction != 3)) {
            i_this->mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mCyl.ClrAtSet();
            i_this->m32C = 0.0f;
            i_this->m330 = 0.0f;
            i_this->m348 = 0;
            i_this->m310.x = 0;
            i_this->m310.y = 0;
            i_this->m310.z = 0;
            i_this->mCurrAction = 0;
            i_this->m2F5 = 10;
            return TRUE;
        }

        if ((i_this->mColorType == 3) && (i_this->m2F6 != 4 && (i_this->m2F6 != 3)) && (i_this->m2F6 != 9)) {
            i_this->m2F6 = 0;
        }

        if (i_this->m2F6 == 6) {
            i_this->mCurrAction = 4;
            i_this->m2F5 = 0x34;
        } else {
            i_this->mCurrAction = 3;
            i_this->m2F5 = 0x28;
        }
        return TRUE;
    }
    return FALSE;
}

/* 00001F78-00002180       .text search_angle_set__FP8cc_class */
BOOL search_angle_set(cc_class* i_this) {
    if (i_this->mBehaviorType != 3) {
        if (fopAcM_searchPlayerDistance(&i_this->actor) > 40.0f) {
            i_this->actor.current.angle.y = fopAcM_searchPlayerAngleY(&i_this->actor);
            i_this->actor.current.angle.y += i_this->m34C;
            return TRUE;
        }
    } else {
        f32 fVar7 = i_this->m3BC.x - i_this->actor.current.pos.x;
        f32 fVar1 = i_this->m3BC.z - i_this->actor.current.pos.z;
        if (std::sqrtf(SQUARE(fVar7) + SQUARE(fVar1)) > i_this->m340) {
            i_this->actor.current.angle.y = cM_atan2s(fVar7, fVar1);
        } else if (std::sqrtf(SQUARE(fVar7) + SQUARE(fVar1)) < 100.0f && cM_rnd() < 0.1f &&
                   (s16)cLib_distanceAngleS(i_this->actor.shape_angle.y, i_this->actor.current.angle.y) < 0x100)
        {
            i_this->actor.current.angle.y += cM_rndFX(16384.0f);
        }
    }
    return FALSE;
}

/* 00002180-00002A20       .text action_nomal_move__FP8cc_class */
void action_nomal_move(cc_class* i_this) {
    switch (i_this->m2F5) {
    case 0:
        i_this->mCyl.OffTgSetBit();
        i_this->mCyl.ClrCoSet();
        i_this->mCyl.ClrTgHit();
        anm_init(i_this, CC_BCK_START, 0.0f, 0, 0.0f, -1);
        if (i_this->mBehaviorType == 0) {
            anm_init(i_this, CC_BCK_TSTART01, 0.0f, 0, 0.0f, -1);
        }
        i_this->m2F5++;

    case 1:
        if (fopAcM_searchPlayerDistance(&i_this->actor) < i_this->mNoticeRange) {
            fopAcM_OnStatus(&i_this->actor, fopAcStts_SHOWMAP_e);
            if (i_this->mBehaviorType == 1) {
                anm_init(i_this, CC_BCK_TSTART01, 0.0f, 0, 1.0f, -1);
                i_this->m2F5 = 2;
            } else {
                fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_ENTER_GND, 0);
                anm_init(i_this, CC_BCK_START, 0.0f, 0, 1.0f, -1);
                i_this->m2F9 = 0;
                i_this->actor.gravity = -3.0f;
                i_this->m2F5 = 3;
                i_this->mCyl.OnTgSetBit();
                i_this->actor.attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            }
        }
        break;

    case 2:
        if (i_this->m2B4->checkFrame(22.0f)) {
            i_this->m2F9 = 0;
            i_this->actor.gravity = -11.0f;
        }

        if (i_this->m2B4->getFrame() > 22.0f) {
            cLib_addCalcAngleS2(&i_this->actor.shape_angle.x, 0, 1, 0x1000);
        }

        if (i_this->mAcch.ChkGroundHit()) {
            fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_LANDING, dComIfG_Bgsp()->GetMtrlSndId(i_this->mAcch.m_gnd));
            cc_eff_set(i_this, 1);
            i_this->actor.shape_angle.x = 0;
            i_this->actor.speed.y = 0.0f;
            anm_init(i_this, CC_BCK_TSTART02, 0.0f, 0, 1.0f, -1);
            i_this->m2F5 = 3;
            i_this->mCyl.OnTgSetBit();
            i_this->actor.attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            denki_start(i_this);
        }
        break;

    case 3:
        if (!i_this->m2B4->isStop()) {
            break;
        }
        i_this->m2F5++;

    case 4:
        i_this->actor.attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;

        for (s32 i = 0; i < ARRAY_SSIZE(i_this->m35C); i++) {
            i_this->m35C[i] = 0;
        }

        i_this->mCyl.SetTgType(~(AT_TYPE_UNK400000 | AT_TYPE_UNK20000 | AT_TYPE_WATER));
        i_this->mCyl.OnCoSetBit();
        i_this->mCyl.OnTgSetBit();
        i_this->m34E[0] = 10;
        i_this->m34E[0] += (s16)cM_rndF(15.0f);
        i_this->m34E[0] += i_this->m34E[1];
        denki_start(i_this);

        if (i_this->m320 != CC_BCK_TACHI_WALK) {
            anm_init(i_this, CC_BCK_TACHI_WALK, 2.0f, 2, 1.0f, -1);
        }

        fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_MOVE_STAND, 0);
        i_this->m2F5++;
        break;

    case 5:
        search_angle_set(i_this);
        if (i_this->m2B4->checkFrame(0.0f)) {
            fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_MOVE_STAND, 0);
        }
        cLib_addCalc2(&i_this->actor.speedF, 2.0f, 0.2f, 0.5f);
        if (i_this->m34E[0] != 0) {
            break;
        }

        if ((i_this->mBehaviorType == 2) && (i_this->m34E[5] == 0)) {
            i_this->m2F5 = 6;
            break;
        }

        if ((i_this->mColorType == 1) || (i_this->mColorType == 4)) {
            f32 tmp = 380.0f;
            if (fopAcM_searchPlayerDistance(&i_this->actor) < tmp) {
                i_this->mCurrAction = 2;
                i_this->m2F5 = 0x1e;
                return;
            }
            break;
        }
        i_this->m2F5++;

    case 6:
        denki_start(i_this);
        fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_STAND_TO_LIE, 0);
        i_this->mCyl.SetTgType(
            AT_TYPE_BOMB | AT_TYPE_BOOMERANG | AT_TYPE_NORMAL_ARROW | AT_TYPE_HOOKSHOT | AT_TYPE_SKULL_HAMMER | AT_TYPE_FIRE_ARROW | AT_TYPE_ICE_ARROW |
            AT_TYPE_LIGHT_ARROW | AT_TYPE_LIGHT | AT_TYPE_GRAPPLING_HOOK
        );
        i_this->mCyl.OffCoSetBit();
        anm_init(i_this, CC_BCK_TACHI2HUSE, 2.0f, 0, 1.0f, -1);
        i_this->m2F5++;
        break;

    case 7:
        if (!i_this->m2B4->isStop()) {
            break;
        }

        if ((i_this->mBehaviorType == 2) && (i_this->m34E[5] == 0)) {
            i_this->mCurrAction = 5;
            i_this->m2F5 = 0x44;
            break;
        }

        anm_init(i_this, CC_BCK_HUSE_WALK, 0.0f, 2, 1.0f, -1);
        i_this->m2F5++;

    case 8:
        i_this->m34E[0] = 0x46;
        i_this->m34E[0] += (s16)cM_rndF(15.0f);
        fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_MOVE_LIE, 0);
        i_this->actor.speedF = 1.0f;
        i_this->m2F5++;
        break;

    case 9:
        if (i_this->m2B4->checkFrame(0.0f)) {
            fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_MOVE_LIE, 0);
        }
        search_angle_set(i_this);
        if (i_this->m34E[0] != 0) {
            break;
        }
        i_this->m2F5++;

    case 10:
        i_this->mCyl.SetTgType(~(AT_TYPE_UNK400000 | AT_TYPE_UNK20000 | AT_TYPE_WATER));
        anm_init(i_this, CC_BCK_HUSE2TACHI, 0.0f, 0, 1.0f, -1);
        fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_LIE_TO_STAND, 0);
        i_this->m2F5++;
        break;

    case 0xb:
        if (i_this->m2B4->isStop()) {
            f32 tmp = 380.0f;
            fopAcM_monsSeStart(&i_this->actor, JA_SE_CV_CC_STAND_UP, 0);
            if ((i_this->mBehaviorType != 3) && fopAcM_searchPlayerDistance(&i_this->actor) < tmp && i_this->mAcch.ChkGroundHit()) {
                i_this->mCurrAction = 2;
                i_this->m2F5 = 0x1e;
                return;
            }
            i_this->m2F5 = 4;
        }
    }

    cLib_addCalcAngleS2(&i_this->actor.shape_angle.y, i_this->actor.current.angle.y, 1, 0x400);

    if ((i_this->m2F5 < 4 || i_this->m2F5 > 0xb || !shock_damage_check(i_this)) && i_this->m2F5 >= 3) {
        body_atari_check(i_this);
        black_light_check(i_this);
    }
}

/* 00002A20-00002E24       .text action_oyogu__FP8cc_class */
void action_oyogu(cc_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;

    switch (i_this->m2F5) {
    case 0x14:
        for (s32 i = 0; i < ARRAY_SSIZE(i_this->m35C); i++) {
            i_this->m35C[i] = 0;
        }

        denki_start(i_this);

#if VERSION > VERSION_DEMO
        i_this->m301 = 0;
#endif

        fopAcM_seStart(a_this, JA_SE_CM_CC_STAND_TO_LIE, 0);
        i_this->m310.x = 0;
        i_this->m310.y = 0;
        i_this->m310.z = 0;
        i_this->mCyl.SetTgType(
            AT_TYPE_GRAPPLING_HOOK | AT_TYPE_WIND | AT_TYPE_LIGHT_ARROW | AT_TYPE_ICE_ARROW | AT_TYPE_FIRE_ARROW | AT_TYPE_HOOKSHOT | AT_TYPE_NORMAL_ARROW |
            AT_TYPE_BOOMERANG
        );
        i_this->mCyl.OffCoSetBit();
        if ((i_this->mColorType != 2) && (i_this->mColorType != 4)) {
            i_this->mCyl.OffAtSetBit();
            i_this->mCyl.OffAtSetBit();
        }

        fopAcM_seStart(a_this, JA_SE_CM_CC_STAND_TO_LIE, 0);

        if (i_this->m320 != CC_BCK_TACHI2HUSE) {
            anm_init(i_this, CC_BCK_TACHI2HUSE, 2.0f, 0, 1.0f, -1);
        }

        a_this->speedF = 0.0f;
        a_this->speed.x = 0.0f;
        a_this->speed.y = 0.0f;
        a_this->speed.z = 0.0f;
        a_this->gravity = -3.0f;
        i_this->m324 = 0.0;
        i_this->m2F8 = 0;
        i_this->m2F5++;

    case 0x15:
        if (i_this->m320 == CC_BCK_TACHI2HUSE) {
            if (i_this->m2B4->isStop()) {
                anm_init(i_this, CC_BCK_HUSE_WALK, 0.0, 2, 1.0, -1);
            }
        }

        cLib_addCalc0(&a_this->gravity, 0.2f, 1.0f);
        cLib_addCalc0(&a_this->speed.y, 0.2f, 1.0f);
        i_this->m35C[0] += 0x800;
        f32 sin = cM_ssin(i_this->m35C[0]) * 3.0f + -15.0f;
        cLib_addCalc2(&i_this->m328, sin, 1.0f, 10.0f);

        if (i_this->mAcch.MaskWaterIn()) {
            cLib_addCalc2(&a_this->current.pos.y, i_this->mAcch.m_wtr.GetHeight() - 20.0f, 1.0f, i_this->m324);
            cLib_addCalc2(&i_this->m324, 6.0f, 1.0f, 1.0f);
            if (std::fabsf(a_this->current.pos.y - (i_this->mAcch.m_wtr.GetHeight() - 20.0f)) < 2.0f) {
                i_this->m2F8 = 1;
#if VERSION == VERSION_DEMO
                cLib_addCalc2(&a_this->speedF, 1.0f, 0.3f, 1.0f);
                if (a_this->speedF < 2.0f) {
                    search_angle_set(i_this);
                }
#else
                cLib_addCalc2(&a_this->speedF, REG8_F(17) + 1.0f, 0.3f, 1.0f);
                if (REG8_F(17) || a_this->speedF < 2.0f) {
                    search_angle_set(i_this);
                }
#endif
            }
        }

        if (i_this->m2B4->checkFrame(0.0f)) {
            fopAcM_seStart(a_this, JA_SE_CM_CC_MOVE_LIE, 0);
        }
        break;
    }

    body_atari_check(i_this);

    if (!i_this->mAcch.MaskWaterIn()) {
        a_this->gravity = -3.0;
        if (i_this->mAcch.ChkGroundHit() || (i_this->mBehaviorType == 2 && i_this->m34E[5] == 0)) {
            i_this->m2F8 = 0;
            i_this->m328 = 0.0f;
            if (i_this->mBehaviorType != 2) {
                i_this->mCurrAction = 0;
                i_this->m2F5 = 10;
            } else {
                i_this->mCurrAction = 5;
                i_this->m2F5 = 0x44;
            }
        }
    }
}

/* 00002E24-000032A0       .text action_attack_move__FP8cc_class */
void action_attack_move(cc_class* i_this) {
    switch (i_this->m2F5) {
    case 0x1E:
        for (s32 i = 0; i < ARRAY_SSIZE(i_this->m35C); i++) {
            i_this->m35C[i] = 0;
        }

        i_this->actor.speedF = 0.0f;
        denki_start(i_this);

#if VERSION > VERSION_JPN
        i_this->actor.attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
#endif

        i_this->mCyl.OnCoSetBit();
        fopAcM_monsSeStart(&i_this->actor, JA_SE_CV_CC_ATTACK, 0);
        i_this->m306 = 0;
        anm_init(i_this, CC_BCK_ATACK01, 0.0f, 0, 1.0f, -1);
        i_this->m2F5++;

    case 0x1F:
        if (!i_this->m2B4->isStop())
            break;

        i_this->m34E[0] = 10;
        i_this->m2F5++;

    case 0x20:
        if (i_this->m34E[0] == 0) {
            i_this->actor.current.angle.y = fopAcM_searchPlayerAngleY(&i_this->actor);
            i_this->mCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
            i_this->mCyl.OnAtHitBit();
            anm_init(i_this, CC_BCK_ATACK02, 0.0f, 0, 1.0f, -1);
            fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_ATTACK, 0);
            i_this->actor.speedF = 18.0f;
            i_this->actor.gravity = -3.0f;
            i_this->actor.speed.y = 25.0f;
            i_this->m2F5++;
        }
        break;

    case 0x21:
        i_this->mAcch.OnLineCheck();
        if ((i_this->actor.speedF > 0.0f) && i_this->mCyl.ChkAtShieldHit()) {
            i_this->actor.speedF *= -0.5f;
            i_this->actor.speed.y = 0.0f;
        }

        if (i_this->mAcch.ChkGroundHit()) {
            if ((i_this->mColorType != 2) && (i_this->mColorType != 4)) {
                i_this->mCyl.OffAtSetBit();
                i_this->mCyl.OffAtSetBit();
            }

            fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_LANDING, dComIfG_Bgsp()->GetMtrlSndId(i_this->mAcch.m_gnd));

            cc_eff_set(i_this, 1);
            i_this->actor.speedF = 0.0f;
            anm_init(i_this, CC_BCK_ATACK03, 0.0f, 0, 1.0f, -1);
            i_this->m2F5++;
        }
        break;

    case 0x22:
        if (i_this->m2B4->isStop()) {
            i_this->m34E[1] = 5;
            i_this->m34E[1] += cM_rndF(i_this->m34E[1]);
            i_this->mCurrAction = 0;
            i_this->m2F5 = 4;
        }
    }

    i_this->actor.setBtNowFrame(1000.0f);

    if ((i_this->m2F5 >= 0x1F) && (i_this->m2F5 <= 0x22)) {
        i_this->m306++;
        if (i_this->m306 > (s16)REG8_F(7) && i_this->m306 < (s16)(REG8_F(8) + 25.0f)) {
            i_this->actor.setBtNowFrame(5.0f);
        }
    }

    if ((i_this->m2F5 > 0x20) || !shock_damage_check(i_this)) {
        cLib_addCalcAngleS2(&i_this->actor.shape_angle.y, i_this->actor.current.angle.y, 1, 0x1000);
        black_light_check(i_this);
        body_atari_check(i_this);
    }
}

/* 000032A0-00003C58       .text action_damage_move__FP8cc_class */
void action_damage_move(cc_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    cXyz sp28;
    cXyz sp1C;
    GXColor sp18 = {};
    JPABaseEmitter* pJVar6;

    switch (i_this->m2F5) {
    case 0x28:
        for (s32 i = 0; i < ARRAY_SSIZE(i_this->m35C); i++) {
            i_this->m35C[i] = 0;
        }

        i_this->mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mCyl.ClrAtSet();
        i_this->mCyl.OnTgSetBit();
        i_this->mCyl.OnCoSetBit();

#if VERSION > VERSION_JPN
        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
#endif

        if (i_this->mColorType == 3 && i_this->m2F6 == 0) {
            i_this->mCyl.OffTgSetBit();
            i_this->mCyl.ClrTgHit();
            i_this->m32C = 0.0f;
            i_this->m330 = 0.0f;
            i_this->m348 = 0;
            i_this->m310.x = 0;
            i_this->m310.y = 0;
            i_this->m310.z = 0;
            a_this->speedF = 0.0f;
            i_this->m2F5 = 0x2d;
            break;
        }

        denki_end(i_this);
        anm_init(i_this, CC_BCK_TACHI2HUSE, 0.0f, 0, 0.0f, -1);

        i_this->mCyl.SetTgType(~(AT_TYPE_UNK400000 | AT_TYPE_UNK20000 | AT_TYPE_WATER));

        i_this->m34A = (fopAcM_searchPlayerAngleY(a_this) - -0x8000) - a_this->shape_angle.y;
        i_this->m348 = 0;
        i_this->m32C = 7000.0f;

        if ((i_this->m2F6 == 1) || (a_this->health <= 0)) {
            i_this->m32C = 16000.0f;
            i_this->m2F6 = 1;
        }

        if (a_this->health > 0) {
            fopAcM_seStart(a_this, JA_SE_CM_CC_DMG_SWING, 0);
            fopAcM_monsSeStart(a_this, JA_SE_CV_CC_DAMAGE, 0);
        } else {
            fopAcM_seStart(a_this, JA_SE_CM_CC_DIE_SWING, 0);
            fopAcM_monsSeStart(a_this, JA_SE_CV_CC_DIE, 0);
        }

        cc_eff_set(i_this, 0);

        a_this->speed.y = 0.0f;
        i_this->m330 = 250.0f;

        switch (i_this->m2F6) {
        case 1:
            i_this->m330 = 500.0f;
            a_this->speedF = 60.0f;
            break;

        case 4:
        case 9:
            anm_init(i_this, CC_BCK_MAHI, 0.0f, 0, 1.0f, -1);
            dComIfGp_particle_set(dPa_name::ID_COMMON_STARS_BLOW, &a_this->attention_info.position);
            i_this->m32C = 0.0f;
            i_this->m330 = 0.0f;
            i_this->m348 = 0;
            break;

        case 3:
            if (fopAcM_checkCarryNow(a_this)) {
                fopAcM_cancelCarryNow(a_this);
                a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
                i_this->mCyl.OnCoSetBit();
                a_this->gravity = -3.0f;
                a_this->speedF = 0.0f;
            }
            i_this->m32C = 16000.0f;
            i_this->m348 = 10000;
            break;

        default:
            a_this->speedF = 20.0f;
            break;
        }

        if (i_this->mBehaviorType == 3) {
            a_this->speedF = 0.0f;
        }

        if (i_this->m2F6 != 3) {
            a_this->current.angle.y = fopAcM_searchPlayerAngleY(a_this) - -0x8000;
        }

        i_this->m2F5++;

    case 0x29:
        cMtx_YrotS(*calc_mtx, i_this->m34A);

        sp28.x = 0.0f;
        sp28.y = 0.0f;
        sp28.z = i_this->m32C * cM_ssin(i_this->m348);
        MtxPosition(&sp28, &sp1C);

        i_this->m310.z = -sp1C.x;
        i_this->m310.x = sp1C.z;

        cLib_addCalc0(&a_this->speedF, 0.8f, 4.0f);

        if (i_this->m2F6 != 3) {
            i_this->m348 = i_this->m348 + 0x3000;
        }

        cLib_addCalc0(&i_this->m32C, 1.0f, i_this->m330);

        if (std::fabsf(i_this->m32C) < 1.0f) {
            a_this->speedF = 0.0f;
            i_this->m310.x = 0;
            i_this->m310.y = 0;
            i_this->m310.z = 0;

            if ((i_this->m2F6 == 4) || (i_this->m2F6 == 2)) {
                i_this->m34E[4] = 0x2d;
                i_this->m34E[4] += 0x2d;
                i_this->m34E[4] += REG8_S(5);
                enemy_piyo_set(a_this);
                fopAcM_seStart(a_this, JA_SE_CM_MD_PIYO, 0);
                i_this->m2F5 = 0x2b;
            } else if (i_this->m2F6 == 9) {
                i_this->m34E[4] = REG8_S(4) + 0x14;
                i_this->m2F5 = 0x2c;
            } else {
                i_this->m2F5++;
            }
        }
        break;

    case 0x2a:
        if (a_this->health > 0) {
            if (i_this->m34E[4] == 0) {
                i_this->mCurrAction = 0;
                i_this->m2F5 = 6;
                if ((i_this->mColorType == 1) || (i_this->mColorType == 4)) {
                    i_this->m2F5 = 4;
                }
            }
        } else {
            i_this->mCurrAction = 4;
            i_this->m2F5 = 0x32;
        }
        break;

    case 0x2b:
        if (i_this->m34E[4] <= 1) {
            anm_init(i_this, CC_BCK_HUKKATSU, 0.0f, 2, 1.0f, -1);
            i_this->m34E[4] = 0x3c;
            i_this->m34E[4] += REG8_S(6);
            i_this->m2F5++;
        }
        break;

    case 0x2c:
        if (i_this->m34E[4] == 0) {
            i_this->mCurrAction = 0;
            i_this->m2F5 = 6;
            if ((i_this->mColorType == 1) || (i_this->mColorType == 4)) {
                i_this->m2F5 = 4;
            }
        }
        break;

    case 0x2d:
        i_this->m301 = 1;
        i_this->m2D8->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("CC", CC_BCK_CC_PTCL), 0, 0.0f, 1.0f, 0.0f, -1.0f, NULL);

        pJVar6 = dComIfGp_particle_set(dPa_name::ID_SCENE_82A8, &a_this->attention_info.position, &a_this->current.angle);
        if (pJVar6 != NULL) {
            f32 tmp = (a_this->tevStr.mColorK0.r / 255.0f);
            sp18.r = tmp * 40.0f;

            tmp = (a_this->tevStr.mColorK0.g / 255.0f);
            sp18.g = tmp * 16.0f;

            tmp = (a_this->tevStr.mColorK0.b / 255.0f);
            sp18.b = tmp * 39.0f;
            pJVar6->setGlobalPrmColor(sp18.r, sp18.g, sp18.b);
        }
        i_this->mStts.SetWeight(0xFE);
        i_this->m2F5++;
        break;

    case 0x2e:
        if (i_this->m2D8->checkFrame(12.0f)) {
            fopAcM_seStart(a_this, JA_SE_CM_B_CC_RECOVER, 0);
        }

        if (i_this->m2D8->isStop()) {
            i_this->mCyl.OnTgSetBit();
            i_this->m301 = 0;
            i_this->mStts.SetWeight(0x32);
            i_this->mCyl.SetTgType(~(AT_TYPE_UNK400000 | AT_TYPE_UNK20000 | AT_TYPE_WATER));
            anm_init(i_this, CC_BCK_HUSE2TACHI, 0.0f, 0, 1.0f, -1);
            fopAcM_seStart(a_this, JA_SE_CM_CC_LIE_TO_STAND, 0);

            a_this->shape_angle.y = fopAcM_searchPlayerAngleY(a_this);
            a_this->current.angle.y = a_this->shape_angle.y;
            i_this->mCurrAction = 0;
            i_this->m2F5 = 0xb;
        }
    }

    if (a_this->health > 0 && !body_atari_check(i_this)) {
        if (i_this->m2F5 >= 0x2A) {
            shock_damage_check(i_this);
        }
        black_light_check(i_this);
    }
}

/* 00003C58-000040E4       .text action_dead_move__FP8cc_class */
void action_dead_move(cc_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    cXyz sp08 = a_this->current.pos;
    sp08.y += 60.0f;

    switch (i_this->m2F5) {
    case 50:
        denki_end(i_this);
        i_this->mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mCyl.ClrAtSet();
        i_this->mCyl.OffTgSetBit();
        i_this->mCyl.OffCoSetBit();
        i_this->mCyl.ClrTgHit();
        i_this->m2F5++;

    case 51:
        if (i_this->mBehaviorType == 3) {
            if (a_this->stealItemBitNo != 0xff) {
                fopAcM_createDisappear(a_this, &sp08, 5, daDisItem_IBALL_e, a_this->stealItemBitNo);
            }
        } else if (i_this->m304 == 0) {
            fopAcM_createDisappear(a_this, &sp08, 5, daDisItem_IBALL_e, a_this->stealItemBitNo);
        } else if (i_this->m304 != 2) {
            u8 dVar7;
            if (dComIfGs_getLife() <= 4) {
                dVar7 = daDisItem_HEART_e;
            } else if (cM_rndF(1.0f) < 0.5f) {
                if (dComIfGs_getMagic() <= 0x10) {
                    dVar7 = daDisItem_MAGIC_e;
                } else if (dComIfGs_getArrowNum() <= 10) {
                    dVar7 = daDisItem_ARROW_e;
                } else {
                    dVar7 = daDisItem_HEART_e;
                }
            } else {
                dVar7 = daDisItem_NONE13_e;
            }
            fopAcM_createDisappear(a_this, &sp08, 5, dVar7);
        } else {
            fopAcM_createDisappear(a_this, &sp08, 5, daDisItem_NONE13_e);
        }
        fopAcM_delete(a_this);
        fopAcM_onActor(a_this);
        break;

    case 52:
        denki_end(i_this);
        cc_eff_set(i_this, 1);

        fopAcM_seStart(a_this, JA_SE_CM_CC_DIE_SWING, 0);
        fopAcM_monsSeStart(a_this, JA_SE_CV_CC_DIE, 0);

        i_this->m2BC->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("CC", CC_BCK_CC_BETA), 0, 0.0f, 1.0f, 0.0f, -1.0f, NULL);
        a_this->speedF = 0.0f;
        a_this->speed.x = 0.0f;
        a_this->speed.y = 0.0f;
        a_this->speed.z = 0.0f;
        i_this->mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mCyl.ClrAtSet();
        i_this->mCyl.OffTgSetBit();
        i_this->mCyl.OffCoSetBit();
        i_this->mCyl.ClrTgHit();
        i_this->m34E[0] = 0;
        i_this->m2F5++;

    case 53:
        if (i_this->m2BC->isStop()) {
            if (i_this->mBehaviorType == 3) {
                if (a_this->stealItemBitNo != 0xff) {
                    fopAcM_createDisappear(a_this, &sp08, 5, daDisItem_IBALL_e, a_this->stealItemBitNo);
                }
            } else if (i_this->m304 == 0) {
                fopAcM_createDisappear(a_this, &sp08, 5, daDisItem_IBALL_e, a_this->stealItemBitNo);
            } else if (i_this->m304 != 2) {
                u8 dVar7;
                if (dComIfGs_getLife() <= 4) {
                    dVar7 = daDisItem_HEART_e;
                } else if (cM_rndF(1.0f) < 0.5f) {
                    if (dComIfGs_getMagic() <= 0x10) {
                        dVar7 = daDisItem_MAGIC_e;
                    } else if (dComIfGs_getArrowNum() <= 10) {
                        dVar7 = daDisItem_ARROW_e;
                    } else {
                        dVar7 = daDisItem_HEART_e;
                    }
                } else {
                    dVar7 = daDisItem_NONE13_e;
                }
                fopAcM_createDisappear(a_this, &sp08, 5, dVar7);
            } else {
                fopAcM_createDisappear(a_this, &sp08, 5, daDisItem_NONE13_e);
            }
            fopAcM_delete(a_this);
            fopAcM_onActor(a_this);
        }
        break;
    }
}

/* 000040E4-000042E8       .text deku_come_demo__FP8cc_class */
void deku_come_demo(cc_class* i_this) {
    static char* cut_name_tbl[] = {
        "START_RET",
        "NEXT_RET",
    };
    int iVar2;
    s8 actIdx;

    switch (i_this->m2FC) {
    case 1:
        i_this->m2FC++;
        i_this->m308 = dComIfGp_evmng_getEventIdx("CyuCyu_STR");
        break;

    case 2:
        if (i_this->actor.eventInfo.checkCommandDemoAccrpt()) {
            i_this->m2FC++;
            i_this->m34E[5] = 0x28;
            if (DEMO_SHORT_CUT_FLAG != 0) {
                i_this->m34E[5] = 0x14;
            }
            DEMO_COME_START_FLAG = 2;
        } else {
            fopAcM_orderOtherEventId(&i_this->actor, i_this->m308);
        }
        break;

    case 3:
        if (i_this->m34E[5] == 0) {
            iVar2 = dComIfGp_evmng_getMyStaffId("CyuCyu");
            dComIfGp_evmng_cutEnd(iVar2);
            i_this->m2FC++;
        }
        break;

    case 4:
        iVar2 = dComIfGp_evmng_getMyStaffId("CyuCyu");
        actIdx = dComIfGp_evmng_getMyActIdx(iVar2, cut_name_tbl, ARRAY_SSIZE(cut_name_tbl), 1, 0);
        if (actIdx == 1) {
            dComIfGp_evmng_cutEnd(iVar2);
            i_this->m2FC++;
        }
        break;

    case 5:
        if (dComIfGp_evmng_endCheck(i_this->m308)) {
            dComIfGp_event_reset();
            i_this->m2FC = 0;
            DEMO_COME_START_FLAG = 0;
            dComIfGs_onTmpBit(0x304);
        }
        break;
    }
}

/* 000042E8-00004518       .text deku_ret_demo__FP8cc_class */
void deku_ret_demo(cc_class* i_this) {
    static char* cut_name_tbl[] = {
        "START_RET",
        "NEXT_RET",
    };
    int iVar2;
    s8 actIdx;

    switch (i_this->m2FD) {
    case 2:
        if (i_this->actor.eventInfo.checkCommandDemoAccrpt()) {
            i_this->m2FD++;
            i_this->m34E[5] = 0x28;
            if (DEMO_SHORT_CUT_FLAG != 0) {
                i_this->m34E[5] = 0x14;
            }
        } else {
            fopAcM_orderOtherEventId(&i_this->actor, i_this->m308);
        }
        break;

    case 3:
        if (i_this->m34E[5] == 0) {
            anm_init(i_this, CC_BCK_START, 0.0f, 0, 1.0f, -1);
            DEMO_RET_START_FLAG = 2;
            i_this->m34E[5] = 0x50;
            if (DEMO_SHORT_CUT_FLAG != 0) {
                i_this->m34E[5] = 0x28;
            }
            i_this->m2FD++;
        }
        break;

    case 4:
        if (i_this->m34E[5] == 0) {
            int iVar2 = dComIfGp_evmng_getMyStaffId("CyuCyu");
            dComIfGp_evmng_cutEnd(iVar2);
            i_this->m2FD++;
        }
        break;

    case 5:
        iVar2 = dComIfGp_evmng_getMyStaffId("CyuCyu");
        actIdx = dComIfGp_evmng_getMyActIdx(iVar2, cut_name_tbl, ARRAY_SSIZE(cut_name_tbl), 1, 0);
        if (actIdx == 1) {
            dComIfGp_evmng_cutEnd(iVar2);
            i_this->m2FD++;
        }
        break;

    case 6:
        if (dComIfGp_evmng_endCheck(i_this->m308)) {
            dComIfGp_event_reset();
            i_this->m2FD = 0;
            DEMO_RET_START_FLAG = 0;
            DEMO_SHORT_CUT_FLAG = 1;
            i_this->m2F5 = 0x3f;
        }
        break;
    }
}

/* 00004518-00004CAC       .text action_noboru__FP8cc_class */
void action_noboru(cc_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    switch (i_this->m2F5) {
    case 0x3c:
        i_this->m3BA = -0x4000;
        i_this->m2FB = 0;
        a_this->attention_info.flags = 0;
        anm_init(i_this, CC_BCK_DEKU_START, 0.0f, 0, 0.0f, -1);
        i_this->m2F5++;

    case 0x3d:
        if (i_this->m2FB >= 1) {
            fopAcM_seStart(a_this, JA_SE_CM_CC_ENTER_GND, 0);
            anm_init(i_this, CC_BCK_DEKU_START, 0.0, 0, 1.0, -1);
            i_this->m2F5++;
        }
        break;

    case 0x3e:
        if (!i_this->m2B4->isStop()) {
            break;
        }
        i_this->m344 = cM_rndF(43.0f);
        anm_init(i_this, CC_BCK_TACHI_WALK, 1.0f, 2, 1.0f, -1);
        i_this->m2F5++;

    case 0x3f:
        if (i_this->m2B4->checkFrame(i_this->m344)) {
            fopAcM_monsSeStart(a_this, JA_SE_CV_CC_PARASITE, 0);
        }

        if (!player->checkFrontRollCrash()) {
            break;
        }

        anm_init(i_this, CC_BCK_ATACK01, 0.0, 0, 1.0, -1);
        i_this->m2F5 = i_this->m2F5 + 1;

    case 0x40:
        if (DEMO_COME_START_FLAG == 0) {
            i_this->m2FC = 1;
            DEMO_COME_START_FLAG = 1;
        } else if (DEMO_COME_START_FLAG == 2) {
            i_this->m2F5 = 0x41;
        }
        break;

    case 0x41:
        fopAcM_monsSeStart(a_this, JA_SE_CV_CC_ATTACK, 0);
        anm_init(i_this, CC_BCK_ATACK02, 0.0f, 0, 1.0f, -1);
        i_this->m3BA = 0;
        a_this->current.angle.x = 0;
        a_this->current.angle.y = 0;
        a_this->current.angle.z = 0;
        a_this->current.angle.y = cM_rndFX(4096.0f) + 12288.0f;
        a_this->shape_angle.x = a_this->current.angle.x;
        a_this->shape_angle.y = a_this->current.angle.y;
        a_this->shape_angle.z = a_this->current.angle.z;
        i_this->m2FB = 3;

        anm_init(i_this, CC_BCK_ATACK02, 0.0f, 0, 1.0f, -1);
        fopAcM_seStart(a_this, JA_SE_CM_CC_ATTACK, 0);

        a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
        i_this->mCyl.SetTgType(~(AT_TYPE_UNK400000 | AT_TYPE_UNK20000 | AT_TYPE_WATER));
        i_this->mCyl.OnTgSetBit();
        i_this->mCyl.OnCoSetBit();
        i_this->mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mCyl.ClrAtSet();
        a_this->speedF = 15.0f;
        a_this->speed.y = 50.0f;
        a_this->gravity = -3.0f;
        i_this->m2F9 = 0;
        i_this->m2F5++;
        break;

    case 0x42:
        if (i_this->mAcch.ChkGroundHit()) {
            anm_init(i_this, CC_BCK_ATACK03, 0.0f, 0, 1.0f, -1);
            fopAcM_seStart(a_this, JA_SE_CM_CC_LANDING, dComIfG_Bgsp()->GetMtrlSndId(i_this->mAcch.m_gnd));

            cc_eff_set(i_this, 1);
            a_this->speed.y = 0.0f;
            denki_start(i_this);
            i_this->m2F5++;
        }
        break;

    case 0x43:
        if (DEMO_COME_START_FLAG == 0) {
            i_this->m34E[5] = 600;
            i_this->mCurrAction = 0;
            i_this->m2F5 = 3;
        }
        break;

    case 0x44:
        i_this->mCyl.OffTgSetBit();
        i_this->mCyl.OffCoSetBit();
        i_this->mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mCyl.ClrAtSet();
        i_this->mCyl.ClrTgHit();
        i_this->m310.x = 0;
        i_this->m310.y = 0;
        i_this->m310.z = 0;
        i_this->m2F9 = 1;
#if VERSION == VERSION_DEMO
        i_this->m368.remove();
#else
        i_this->m390.remove();
#endif
        a_this->attention_info.flags = 0;

        if (i_this->m320 != CC_BCK_TACHI_WALK) {
            anm_init(i_this, CC_BCK_TACHI2HUSE, 0.0f, 0, 0.0f, -1);
        }

        fopAcM_seStart(a_this, JA_SE_CM_CC_STAND_TO_LIE, 0);

        if (DEMO_RET_START_FLAG == 0) {
            DEMO_RET_START_FLAG = 1;
            i_this->m2FD = 1;
        }

        a_this->speed.x = 0.0f;
        a_this->speed.y = 0.0f;
        a_this->speed.z = 0.0f;
        a_this->speedF = 0.0f;
        i_this->m2F5++;

    case 0x45:
        cLib_addCalc0(&i_this->m334, 0.1f, 0.2f);

        if (i_this->m334 > 0.1f) {
            break;
        }

        a_this->shape_angle.x = 0;
        a_this->shape_angle.y = 0;
        a_this->shape_angle.z = 0;
        a_this->current.angle.x = 0;
        a_this->current.angle.y = 0;
        a_this->current.angle.z = 0;
        a_this->gravity = 0.0f;
        a_this->speed.x = 0.0f;
        a_this->speed.y = 0.0f;
        a_this->speed.z = 0.0f;
        i_this->m34E[0] = 0;
        if (i_this->m2FD != 0) {
            i_this->m34E[0] = 0x3c;
        }
        anm_init(i_this, CC_BCK_START, 0.0f, 0, 0.0f, -1);
        i_this->m2FB = 4;
        i_this->m3BA = -0x4000;
        i_this->m2F5++;

    case 0x46:
        if (DEMO_RET_START_FLAG == 2) {
            fopAcM_seStart(a_this, JA_SE_CM_CC_LIE_TO_STAND, 0);
            i_this->m334 = 1.0;
            anm_init(i_this, CC_BCK_START, 0.0f, 0, 1.0f, -1);
            i_this->m2F5 = 0x3e;
        }

        if (i_this->m34E[0] == 30 && i_this->m2FD == 1) {
            i_this->m2FD = 2;
            i_this->m308 = dComIfGp_evmng_getEventIdx("CyuCyu_RET");
            i_this->m334 = 1.0f;
            i_this->m2F5 = 0x47;
        }
        break;

    case 0x47:
        deku_ret_demo(i_this);
        if (DEMO_RET_START_FLAG >= 2 && i_this->m320 == CC_BCK_START && i_this->m2B4->isStop()) {
            anm_init(i_this, CC_BCK_TACHI_WALK, 1.0f, 2, 1.0f, -1);
        }
    }

    if (i_this->m2FC != 0) {
        deku_come_demo(i_this);
    }
}

/* 00004CAC-0000561C       .text action_up_check__FP8cc_class */
void action_up_check(cc_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)i_this;
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    s16 bVar4 = 0;

    switch (i_this->m2F5) {
    case 0x50:
        i_this->m2F6 = 5;
        i_this->mCyl.OnTgShield();
        i_this->mCyl.OnTgSetBit();
        i_this->mCyl.SetTgType(~(AT_TYPE_UNK400000 | AT_TYPE_UNK20000 | AT_TYPE_WATER));
        anm_init(i_this, CC_BCK_MAHI, 0.0f, 0, 0.0f, -1);
#if VERSION > VERSION_DEMO
        i_this->m2F9 = 0;
#endif
        fopAcM_seStart(a_this, JA_SE_CM_CC_STONED, 0);

        a_this->speed.x = 0.0f;
        a_this->speed.y = 0.0f;
        a_this->speed.z = 0.0f;

        i_this->mCyl.OnCoSetBit();
        i_this->mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mCyl.ClrAtSet();

        for (s32 i = 0; i < ARRAY_SSIZE(i_this->m35C); i++) {
            i_this->m35C[i] = 0;
        }

        a_this->speedF = 0.0f;
        fopAcM_seStart(a_this, JA_SE_CM_CC_DMG_SWING, 0);
        fopAcM_monsSeStart(a_this, JA_SE_CV_CC_DAMAGE, 0);
        i_this->m2F5++;

    case 0x51:
        i_this->m2C8->setFrame(0.0f);
        i_this->m2D0->setFrame(0.0f);
        i_this->m2FE = 1;
        i_this->m2FF = 0;
#if VERSION > VERSION_DEMO
        i_this->m301 = 0;
#endif
        i_this->m34E[4] = 600;
        fopAcM_OnStatus(a_this, fopAcStts_FREEZE_e);
        i_this->m2F5++;
        break;

    case 0x52:
        if (i_this->m2FE != 2) {
            cLib_onBit<u32>(a_this->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        }

        cLib_addCalc0(&a_this->speedF, 0.5f, 1.0f);

        if (fopAcM_checkCarryNow(a_this)) {
            i_this->m338 = a_this->current.pos.y;
            a_this->speedF = 0.0f;
            i_this->mCyl.OffCoSetBit();
            a_this->current.angle.y = player->shape_angle.y;
            a_this->gravity = 0.0f;
            a_this->speed.x = 0.0f;
            a_this->speed.y = 0.0f;
            a_this->speed.z = 0.0f;
            i_this->mCyl.OffCoSetBit();
            a_this->attention_info.flags = 0;
            i_this->m2F5++;
        }
        break;

    case 0x53:
        a_this->current.angle.y = player->shape_angle.y;
        if (!fopAcM_checkCarryNow(a_this)) {
            a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            i_this->mCyl.OnCoSetBit();
            a_this->gravity = -3.0f;
            if (fopAcM_GetSpeedF(a_this) > 0.0f) {
                a_this->speed.y = 12.0f;
                a_this->speedF = 20.0f;
                i_this->m2F5 = 0x54;
            } else {
                fopAcM_seStart(a_this, JA_SE_OBJ_PUT_STONE, 0);
                a_this->speedF = 0.0f;
                i_this->m2F5 = 0x52;
            }
        }
        break;

    case 0x54:
        if (i_this->mAcch.ChkWallHit()) {
            a_this->speedF *= -0.5f;
        }

        if (i_this->mAcch.ChkGroundHit()) {
            a_this->speedF = 0.0f;
            fopAcM_seStart(a_this, JA_SE_OBJ_PUT_STONE, 0);
            bVar4 = 1;
        }
        cLib_addCalc0(&a_this->speedF, 0.5f, 1.0f);
        break;
    }

    if (i_this->m338 + 10.0f <= a_this->current.pos.y) {
        cLib_addCalcAngleS2(&a_this->shape_angle.y, a_this->current.angle.y, 1, 0x1000);
    }

    if (i_this->m2F5 >= 0x52) {
        if (dComIfGp_getDetect().chk_light(&a_this->current.pos) != false) {
            i_this->m34E[4] = 600;
        }

        if (i_this->m34E[4] == 1) {
            i_this->m34E[2] = 0x28;
            fopAcM_seStart(a_this, JA_SE_CM_CC_STONED_RECOVER, 0);
        }

        if (i_this->m34E[2] != 0) {
            i_this->m35C[0] += 20000;
            a_this->shape_angle.z = cM_ssin(i_this->m35C[0]) * 2000.0f;
            if (i_this->m34E[2] == 1) {
                i_this->m2FE = 2;
                i_this->m2FF = 0;
                a_this->shape_angle.z = 0;
                i_this->m2CC->setFrame(0.0f);
                i_this->m2D4->setFrame(0.0f);
                cLib_offBit<u32>(a_this->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
            }
        }

        if (i_this->m2FE == 2 && i_this->m2FF >= 0x19) {
            if (fopAcM_checkCarryNow(a_this)) {
                fopAcM_cancelCarryNow(a_this);
                cLib_offBit<u32>(a_this->attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
            }

            a_this->attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
            i_this->mCyl.OffTgShield();
            i_this->m2FF = 0;
            i_this->m2FE = 0;
            a_this->shape_angle.z = 0;
            a_this->gravity = -3.0f;
            i_this->mCyl.OnTgSetBit();
            a_this->current.angle.y = a_this->shape_angle.y;
            fopAcM_OffStatus(a_this, fopAcStts_FREEZE_e);
#if VERSION > VERSION_DEMO
            i_this->mStts.SetWeight(0x32);
#endif
            i_this->mCurrAction = 0;
            i_this->m2F5 = 6;
        }
    }

    if (i_this->mCurrAction != 0 && i_this->m2FE != 2) {
        i_this->mStts.Move();
        if (i_this->mCyl.ChkTgHit()) {
            player = dComIfGp_getPlayer(0);
            cCcD_Obj* pcVar6 = i_this->mCyl.GetTgHitObj();
            if (pcVar6 == NULL) {
                return;
            }

            cXyz sp24 = *i_this->mCyl.GetTgHitPosP();
            dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, &sp24, &player->shape_angle);

            switch (pcVar6->GetAtType()) {
            case AT_TYPE_SWORD:
            case AT_TYPE_MACHETE:
            case AT_TYPE_UNK800:
            case AT_TYPE_DARKNUT_SWORD:
            case AT_TYPE_MOBLIN_SPEAR:
                fopAcM_seStart(a_this, JA_SE_LK_SW_HIT_S, 13);
                break;

            case AT_TYPE_BOKO_STICK:
            case AT_TYPE_BOOMERANG:
            case AT_TYPE_UNK2000:
            case AT_TYPE_STALFOS_MACE:
                fopAcM_seStart(a_this, JA_SE_LK_W_WEP_HIT, 13);
                break;

            case AT_TYPE_SKULL_HAMMER:
                bVar4 = 1;
                break;

            case AT_TYPE_HOOKSHOT:
            case AT_TYPE_SPIKE:
            case AT_TYPE_NORMAL_ARROW:
            case AT_TYPE_ICE_ARROW:
            case AT_TYPE_FIRE_ARROW:
            case AT_TYPE_LIGHT_ARROW:
            case AT_TYPE_GRAPPLING_HOOK:
                fopAcM_seStart(a_this, JA_SE_LK_MS_WEP_HIT, 13);
                break;
            }
        }
    }

    if (bVar4) {
        JPABaseEmitter* pJVar7 = dComIfGp_particle_set(dPa_name::ID_SCENE_82A9, &a_this->attention_info.position, &a_this->current.angle);
        if (pJVar7 != NULL) {
            pJVar7->setGlobalPrmColor(a_this->tevStr.mColorK0.r, a_this->tevStr.mColorK0.g, a_this->tevStr.mColorK0.b);
            pJVar7->setGlobalEnvColor(a_this->tevStr.mColorK0.r, a_this->tevStr.mColorK0.g, a_this->tevStr.mColorK0.b);
        }

        cXyz sp18 = a_this->current.pos;
        sp18.y += 60.0f;

        fopAcM_seStart(a_this, JA_SE_OBJ_BREAK_STONE, 0);

        fopAcM_createDisappear(a_this, &sp18, 5, daDisItem_IBALL_e, a_this->stealItemBitNo);
        fopAcM_delete(a_this);
        fopAcM_onActor(a_this);
    }
}

/* 0000561C-000056CC       .text action_tomaru__FP8cc_class */
void action_tomaru(cc_class* i_this) {
    switch (i_this->m2F5) {
    case 100:
        if (dComIfGs_isSwitch(i_this->mDisableSpawnSwitchNo, dComIfGp_roomControl_getStayNo())) {
            i_this->m34E[6] = 0x28;
            i_this->m2F5++;
        }
        break;

    case 101:
        if (i_this->m34E[6] == 0) {
            fopAcM_OnStatus(&i_this->actor, fopAcStts_SHOWMAP_e);
            i_this->mCyl.OnTgSetBit();
            i_this->mCurrAction = 0;
            i_this->m2F5 = 0;
        }
        break;
    }
}

/* 000056CC-00005778       .text tsubo_search__FPvPv */
void* tsubo_search(void* arg1, void* arg2) {
    fopAc_ac_c* actor1 = (fopAc_ac_c*)arg1;
    cc_class* i_this = (cc_class*)arg2;

#if VERSION == VERSION_DEMO
    s32 tmp = 0;
    if (tmp < 100)
#endif
    {
        if (fopAcM_IsActor(actor1) && fopAcM_GetName(actor1) == PROC_TSUBO && actor1->current.pos.x == i_this->actor.current.pos.x &&
            std::fabsf(actor1->current.pos.y - i_this->actor.current.pos.y) < 10.0f && actor1->current.pos.z == i_this->actor.current.pos.z)
        {
            i_this->m30C = fopAcM_GetID(actor1);
        }
    }
    return NULL;
}

/* 00005778-000059B8       .text action_tubo_search__FP8cc_class */
void action_tubo_search(cc_class* i_this) {
    fopAc_ac_c* pfVar2;

    switch (i_this->m2F5) {
    case 0x6E:
        i_this->m30C = fpcM_ERROR_PROCESS_ID_e;
        fpcM_Search(tsubo_search, &i_this->actor);
        if (i_this->m30C == fpcM_ERROR_PROCESS_ID_e) {
            fopAcM_delete(&i_this->actor);
        } else {
            i_this->m2F5++;
        }
        break;

    case 0x6F:
        pfVar2 = fopAcM_SearchByID(i_this->m30C);

        if (REG8_F(0)) {
            i_this->mNoticeRange = 400.0f;
        }

        if (pfVar2 != NULL) {
            i_this->actor.current.pos = pfVar2->current.pos;
            if (i_this->mNoticeRange == 0.0f) {
                return;
            }

            if (fopAcM_searchPlayerDistance(&i_this->actor) > i_this->mNoticeRange) {
                return;
            }
        }

        fopAcM_OnStatus(&i_this->actor, fopAcStts_SHOWMAP_e);
        i_this->m2F9 = 0;
        i_this->actor.current.angle.y = fopAcM_searchPlayerAngleY(&i_this->actor);
        i_this->actor.shape_angle.y = i_this->actor.current.angle.y;
        i_this->mCyl.OnAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mCyl.OnAtHitBit();
        i_this->mCyl.OnAtVsBitSet(cCcD_TgSPrm_IsOther_e);
        i_this->mCyl.OffAtVsBitSet(cCcD_TgSPrm_IsPlayer_e);

        anm_init(i_this, CC_BCK_HUSE2TACHI, 0.0, 0, 1.0, -1);
        fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_LIE_TO_STAND, 0);
        denki_start(i_this);
        i_this->actor.gravity = -3.0;
        i_this->mBehaviorType = 0;
        i_this->m2F5++;
        break;

    case 0x70:
        i_this->mCyl.OffAtVsBitSet(cCcD_TgSPrm_IsOther_e);
        i_this->mCyl.OnAtVsBitSet(cCcD_TgSPrm_IsPlayer_e);
#if VERSION > VERSION_JPN
        i_this->actor.attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
#endif
        i_this->mCurrAction = 0;
        i_this->m2F5 = 0xb;
        break;
    }
}

/* 000059B8-00005A58       .text BG_check__FP8cc_class */
void BG_check(cc_class* i_this) {
    if (i_this->m2F9 == 0) {
        i_this->mAcchCir.SetWall(20.0f, 30.0f);
        i_this->mAcch.CrrPos(*dComIfG_Bgsp());
        if (i_this->m2F8 != 0 && i_this->mAcch.MaskWaterIn()) {
            i_this->actor.current.pos.y = i_this->mAcch.m_wtr.GetHeight() - 20.0f;
        }
        fopAcM_getGroundAngle(&i_this->actor, &i_this->m316);
        naraku_check(i_this);
    }
}

/* 00005A58-00006214       .text daCC_Execute__FP8cc_class */
static BOOL daCC_Execute(cc_class* i_this) {
    i_this->actor.model = NULL;
    switch (i_this->mColorType) {
    case 2:
        fopAcM_setGbaName(&i_this->actor, dItem_BOW_e, 30, 0x2b);
        break;

    case 3:
        fopAcM_setGbaName(&i_this->actor, dItem_MIRROR_SHIELD_e, 16, 0x2e);
        break;

    case 4:
        fopAcM_setGbaName(&i_this->actor, dItem_BOW_e, 10, 0x28);
        break;
    }

    if ((i_this->m2F5 >= 6 && i_this->m2F5 < 11) || i_this->mCurrAction == 1) {
        i_this->actor.eyePos = i_this->actor.current.pos;
        i_this->actor.eyePos.y += 10.0f;
    } else {
        i_this->actor.eyePos = i_this->actor.current.pos;
        i_this->actor.eyePos.y += 70.0f;
    }

    if (i_this->mCurrAction != 5) {
        i_this->actor.attention_info.position = i_this->actor.eyePos;
        i_this->actor.attention_info.position.y += 30.0f;
    } else {
        i_this->actor.attention_info.position = i_this->actor.current.pos;
        i_this->actor.attention_info.position.y += 30.0f;
    }

    if (enemy_ice(&i_this->mEnemyIce)) {
        J3DModel* model = i_this->m2B4->getModel();
        model->setBaseTRMtx(mDoMtx_stack_c::get());
        i_this->m2B4->calc();
        naraku_check(i_this);
        return TRUE;
    }

    for (s32 i = 0; i < 7; i++) {
        if (i_this->m34E[i] != 0) {
            i_this->m34E[i]--;
        }
    }

    if (i_this->mCurrAction != 5 && i_this->mCurrAction != 4 && i_this->actor.health > 0 && i_this->mBehaviorType == 2 && DEMO_RET_START_FLAG != 0) {
        i_this->m34E[5] = 0;
        i_this->mCurrAction = 5;
        i_this->m2F5 = 0x44;
    }

    switch (i_this->mCurrAction) {
    case 0:
        action_nomal_move(i_this);
        break;
    case 1:
        action_oyogu(i_this);
        break;
    case 2:
        action_attack_move(i_this);
        break;
    case 3:
        action_damage_move(i_this);
        break;
    case 4:
        action_dead_move(i_this);
        break;
    case 5:
        action_noboru(i_this);
        break;
    case 6:
        action_up_check(i_this);
        break;
    case 7:
        action_tomaru(i_this);
        break;
    case 8:
        action_tubo_search(i_this);
        break;
    }

    if (i_this->mBehaviorType == 4) {
        return TRUE;
    }

    if (i_this->mColorType == 2 || i_this->mColorType == 4) {
#if VERSION > VERSION_DEMO
        MtxP mtx = i_this->m2B4->getModel()->getAnmMtx(3);
        i_this->m3A4.x = mtx[0][3];
        i_this->m3A4.y = mtx[1][3];
        i_this->m3A4.z = mtx[2][3];
#endif

        switch (i_this->m2F7) {
        case 0:
#if VERSION == VERSION_DEMO
            if (i_this->mpEmitter1 != NULL) {
                i_this->mpEmitter1->becomeInvalidEmitter();
                i_this->mpEmitter2->becomeInvalidEmitter();
                i_this->mpEmitter1 = NULL;
                i_this->mpEmitter2 = NULL;
            }
#else
            i_this->m368.remove();
            i_this->m37C.remove();
#endif
            break;

        case 1:
#if VERSION == VERSION_DEMO
            i_this->mpEmitter1 = dComIfGp_particle_set(dPa_name::ID_COMMON_03ED, &i_this->actor.current.pos);
            i_this->mpEmitter2 = dComIfGp_particle_set(dPa_name::ID_COMMON_03EE, &i_this->actor.current.pos);
            if (i_this->mpEmitter1 != NULL && i_this->mpEmitter2 != NULL) {
                i_this->m2F7++;
            }
#else
            if (i_this->m368.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_COMMON_03ED, &i_this->m3A4, NULL, NULL, 0xff, &i_this->m368);
            }

            if (i_this->m37C.getEmitter() == NULL) {
                dComIfGp_particle_set(dPa_name::ID_COMMON_03EE, &i_this->m3A4, NULL, NULL, 0xff, &i_this->m37C);
            }

            if (i_this->m368.getEmitter() != NULL && i_this->m37C.getEmitter() != NULL) {
                i_this->m2F7++;
            }
#endif
            break;

        case 2:
#if VERSION == VERSION_DEMO
            if (i_this->mpEmitter1 != NULL) {
                i_this->mpEmitter1->setGlobalRTMatrix(i_this->m2B4->getModel()->getAnmMtx(3));
            }

            if (i_this->mpEmitter2 != NULL) {
                i_this->mpEmitter2->setGlobalRTMatrix(i_this->m2B4->getModel()->getAnmMtx(3));
            }
#else
            if (i_this->m368.getEmitter() != NULL) {
                i_this->m368.getEmitter()->setGlobalRTMatrix(i_this->m2B4->getModel()->getAnmMtx(3));
            }

            if (i_this->m37C.getEmitter() != NULL) {
                i_this->m37C.getEmitter()->setGlobalRTMatrix(i_this->m2B4->getModel()->getAnmMtx(3));
            }
#endif

            if (i_this->m34E[3] == 0) {
                fopAcM_seStart(&i_this->actor, JA_SE_CM_CC_BLUE_SPARK, 0);
                i_this->m34E[3] = cM_rndF(42.0f) + 30.0f;
            }
            break;
        }
    }

    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);
    cXyz sp30;
    sp30.x = 0.0f;
    sp30.y = 0.0f;
    sp30.z = fopAcM_GetSpeedF(&i_this->actor);
    cXyz sp24;
    MtxPosition(&sp30, &sp24);

    i_this->actor.speed.x = sp24.x;
    i_this->actor.speed.z = sp24.z;
    i_this->actor.speed.y += i_this->actor.gravity;

    if (i_this->mCurrAction != 5) {
        i_this->m316.setall(0);
        if (i_this->actor.speed.y < -55.0f) {
            i_this->actor.speed.y = -55.0f;
        }
    } else if (i_this->actor.speed.y < -55.0f) {
        i_this->actor.speed.y = -55.0f;
    } else if (i_this->actor.speed.y > 1.0f) {
        i_this->actor.speed.y = 1.0f;
    }

    if (i_this->m2F5 != 0x35) {
        if (i_this->mBehaviorType == 2 && i_this->m2FB != 3) {
            i_this->m2B4->getModel()->setBaseTRMtx(i_this->m7EC);
#if VERSION > VERSION_JPN
            i_this->actor.current.pos = i_this->m3BC;
#endif
        }

        if (i_this->m301 == 0) {
            i_this->m2B4->play(NULL, 0, 0);
        } else {
            i_this->m2D8->play(NULL, 0, 0);
        }

        if (i_this->m2FE != 0) {
            i_this->m2C4->play(NULL, 0, 0);
            switch (i_this->m2FE) {
            case 1:
                i_this->m2FF++;
                if (i_this->m2FF > 0x19) {
                    i_this->m2FF = 0x19;
                }
                break;

            case 2:
                i_this->m2FF++;
                if (i_this->m2FF > 0x19) {
                    i_this->m2FF = 0x19;
                }
                break;
            }
        }

        if (i_this->mBehaviorType == 2 && i_this->m2FB != 3) {
            cXyz sp18(0.0f, 0.0f, 0.0f);
            mDoMtx_stack_c::copy(i_this->m7EC);
            mDoMtx_stack_c::multVec(&sp18, &i_this->m3BC);
            i_this->actor.current.pos = i_this->m3BC;
        }
    } else {
        i_this->m2BC->play(NULL, 0, 0);
    }

    i_this->mCyl.SetC(i_this->actor.current.pos);
    f32 fVar8 = 100.0f;
    if (i_this->m320 == CC_BCK_HUSE_WALK) {
        fVar8 = 30.0f;
    }
    i_this->mCyl.SetH(fVar8);
    i_this->mCyl.SetR(35.0f);
    dComIfG_Ccsp()->Set(&i_this->mCyl);
    if (!fopAcM_checkCarryNow(&i_this->actor)) {
        if (i_this->mCyl.ChkCoSet()) {
            fopAcM_posMove(&i_this->actor, i_this->mStts.GetCCMoveP());
        } else {
            fopAcM_posMove(&i_this->actor, NULL);
        }
    }
    BG_check(i_this);
    draw_SUB(i_this);
    return TRUE;
}

/* 00006214-0000621C       .text daCC_IsDelete__FP8cc_class */
static BOOL daCC_IsDelete(cc_class*) {
    return TRUE;
}

/* 0000621C-00006290       .text daCC_Delete__FP8cc_class */
static BOOL daCC_Delete(cc_class* i_this) {
#if VERSION == VERSION_DEMO
    if (i_this->mpEmitter1 != NULL) {
        i_this->mpEmitter1->becomeInvalidEmitter();
        i_this->mpEmitter1 = NULL;
        i_this->mpEmitter2->becomeInvalidEmitter();
        i_this->mpEmitter2 = NULL;
    }
#endif

    i_this->m368.remove();

#if VERSION > VERSION_DEMO
    i_this->m37C.remove();
    i_this->m390.remove();
#endif
    dComIfG_resDeleteDemo(&i_this->mPhase, "CC");
    enemy_fire_remove(&i_this->mEnemyFire);
    return TRUE;
}

/* 00006290-00006A2C       .text useHeapInit__FP10fopAc_ac_c */
static BOOL useHeapInit(fopAc_ac_c* a_this) {
    cc_class* i_this = (cc_class*)a_this;

    s32 fileIndex = CC_BCK_START;
    if (i_this->mBehaviorType == 1) {
        fileIndex = CC_BCK_TSTART01;
    } else if (i_this->mBehaviorType == 2) {
        fileIndex = CC_BCK_HUSE2TACHI;
    }

    i_this->m2B4 = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("CC", CC_BMD_CC),
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("CC", fileIndex),
        J3DFrameCtrl::EMode_NONE,
        0.0f,
        0,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );

    if (i_this->m2B4 == NULL || i_this->m2B4->getModel() == NULL) {
        return FALSE;
    }

    i_this->m2B4->getModel()->setUserArea((u32)i_this);

    for (u16 i = 0; i < i_this->m2B4->getModel()->getModelData()->getJointNum(); i++) {
        i_this->m2B4->getModel()->getModelData()->getJointNodePointer(i)->setCallBack(nodeCallBack);
    }

    J3DModel* model = i_this->m2B4->getModel();

    i_this->m2B8 = new mDoExt_brkAnm();

    if (i_this->m2B8 == NULL) {
        return FALSE;
    }

    if (!i_this->m2B8->init(
            model->getModelData(), (J3DAnmTevRegKey*)dComIfG_getObjectRes("CC", CC_BRK_CC), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE
        ))
    {
        return FALSE;
    }

    i_this->m2C4 = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("CC", CC_BDL_CC_IWA), NULL, NULL, NULL, J3DFrameCtrl::EMode_NONE, 0.0f, 0, -1, 1, NULL, 0, 0x11020203
    );

    if (i_this->m2C4 == NULL || i_this->m2C4->getModel() == NULL) {
        return FALSE;
    }

    model = i_this->m2C4->getModel();
    i_this->m2C8 = new mDoExt_brkAnm();
    if (i_this->m2C8 == NULL) {
        return FALSE;
    }

    if (!i_this->m2C8->init(
            model->getModelData(), (J3DAnmTevRegKey*)dComIfG_getObjectRes("CC", CC_BRK_CC_IWA01), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE
        ))
    {
        return FALSE;
    }

    i_this->m2CC = new mDoExt_brkAnm();
    if (i_this->m2CC == NULL) {
        return FALSE;
    }

    if (!i_this->m2CC->init(
            model->getModelData(), (J3DAnmTevRegKey*)dComIfG_getObjectRes("CC", CC_BRK_CC_IWA02), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE
        ))
    {
        return FALSE;
    }

    i_this->m2D0 = new mDoExt_btkAnm();
    if (i_this->m2D0 == NULL) {
        return FALSE;
    }

    if (!i_this->m2D0->init(
            model->getModelData(), (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("CC", CC_BTK_CC_IWA01), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE
        ))
    {
        return FALSE;
    }

    i_this->m2D4 = new mDoExt_btkAnm();
    if (i_this->m2D4 == NULL) {
        return FALSE;
    }

    if (!i_this->m2D4->init(
            model->getModelData(), (J3DAnmTextureSRTKey*)dComIfG_getObjectRes("CC", CC_BTK_CC_IWA02), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE
        ))
    {
        return FALSE;
    }

    i_this->m2BC = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("CC", CC_BDL_CC_BETA), NULL, NULL, NULL, J3DFrameCtrl::EMode_NONE, 0.0f, 0, -1, 1, NULL, 0, 0x11020203
    );

    if (i_this->m2BC == NULL || i_this->m2BC->getModel() == NULL) {
        return FALSE;
    }

    model = i_this->m2BC->getModel();
    i_this->m2C0 = new mDoExt_brkAnm();
    if (i_this->m2C0 == NULL) {
        return FALSE;
    }

    if (!i_this->m2C0->init(
            model->getModelData(), (J3DAnmTevRegKey*)dComIfG_getObjectRes("CC", CC_BRK_CC_BETA), true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE
        ))
    {
        return FALSE;
    }

    i_this->m2D8 = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("CC", CC_BDL_CC_PTCL),
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("CC", CC_BCK_CC_PTCL),
        J3DFrameCtrl::EMode_NONE,
        1.0f,
        1,
        -1,
        1,
        NULL,
        0,
        0x11020203
    );

    if (i_this->m2D8 == NULL || i_this->m2D8->getModel() == NULL) {
        return FALSE;
    }

    if (!i_this->mDFC.create(i_this->m2B4->getModel())) {
        return FALSE;
    }
    return TRUE;
}

static dCcG_At_Spl cc_atsp_kind[] = {dCcG_At_Spl_UNK0, dCcG_At_Spl_UNK0, dCcG_At_Spl_UNKB, dCcG_At_Spl_UNK0, dCcG_At_Spl_UNKB};
static int cc_atatp_kind[] = {1, 1, 2, 2, 2};
static s8 cc_HP_kind[] = {2, 1, 2, 4, 1};

/* 00006A74-00007160       .text daCC_Create__FP10fopAc_ac_c */
static cPhs_State daCC_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcCyl body_co_cyl = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK2000,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e,
            /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_IsOther_e,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
            /* SrcGObjAt Se      */ dCcG_SE_UNK6,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCylS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 15.0f,
            /* Height */ 0.0f,
        }},
    };

    static s8 fire_j[] = {0, 1, 2, 3, 4, 5, -1, -1, -1, -1};
    static f32 fire_sc[] = {1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f};

    cc_class* i_this = (cc_class*)a_this;

    fopAcM_SetupActor(a_this, cc_class);

    cPhs_State PVar3 = dComIfG_resLoad(&i_this->mPhase, "CC");
    if (PVar3 == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(a_this, useHeapInit, 0x47a0)) {
            return cPhs_ERROR_e;
        }

        i_this->mBehaviorType = fopAcM_GetParam(a_this) & 0xFF;
        i_this->mColorType = (fopAcM_GetParam(a_this) >> 8) & 0xFF;
        i_this->mNoticeRangeByte = (fopAcM_GetParam(a_this) >> 0x10) & 0xFF;
        i_this->mDisableSpawnSwitchNo = (fopAcM_GetParam(a_this) >> 0x18) & 0xFF;

        if (REG8_S(9) != 0) {
            i_this->mColorType = REG8_S(9) - 1;
        }

        if (REG8_S(8) != 0) {
            i_this->mBehaviorType = 3;
        }

        if (i_this->mBehaviorType == 0xff) {
            i_this->mBehaviorType = 0;
        }

        if (i_this->mColorType == 0xff) {
            i_this->mColorType = 0;
        }

        if (i_this->mNoticeRangeByte == 0xff) {
            i_this->mNoticeRangeByte = 0;
        }

        if (i_this->mBehaviorType != 4) {
            if (i_this->mNoticeRangeByte == 0) {
                i_this->mNoticeRange = 1000.0f;
                if (i_this->mBehaviorType == 1) {
                    i_this->mNoticeRange = 1200.0f;
                }
            } else {
                i_this->mNoticeRange = i_this->mNoticeRangeByte * 10.0f;
            }

            if (i_this->mColorType >= 10) {
                i_this->mColorType -= 10;
                i_this->mNoticeRange = 60000.0f;
                if (i_this->mColorType == 5) {
                    i_this->m304 = true;
                    i_this->mColorType = 1;
                }
            }
        } else {
            i_this->mNoticeRange = i_this->mNoticeRangeByte * 10.0f;
        }

        i_this->m3BC = a_this->current.pos;
        fopAcM_OffStatus(a_this, fopAcStts_SHOWMAP_e);
        a_this->stealItemLeft = 1;

        switch (i_this->mColorType) {
        case 0:
            a_this->gbaName = 0x16;
            a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("c_green", 0);
            break;

        case 1:
            a_this->gbaName = 0x15;
            a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("c_red", 0);
            break;

        case 2:
            a_this->gbaName = 0x1E;
            a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("c_blue", 0);
            break;

        case 3:
            a_this->gbaName = 0x10;
            a_this->stealItemLeft = 3;
            a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("c_black", 0);
            fopAcM_OnStatus(a_this, fopAcStts_UNK8000000_e);
            break;

        case 4:
            a_this->gbaName = 10;
            a_this->itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("c_kiiro", 0);
            break;
        }

        fopAcM_SetMtx(a_this, i_this->m2B4->mpModel->getBaseTRMtx());
        a_this->attention_info.flags = 0;

        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this), NULL, NULL);

        if (i_this->mBehaviorType == 1) {
            a_this->shape_angle.x = -0x8000;
        }

        i_this->mStts.Init(0x32, 4, a_this);

        if (i_this->m304) {
            i_this->mCyl.SetTgGrp(cCcD_TgSPrm_IsOther_e | cCcD_TgSPrm_IsPlayer_e | cCcD_TgSPrm_IsEnemy_e | cCcD_TgSPrm_Set_e);
        }

        i_this->mCyl.Set(body_co_cyl);
        i_this->mCyl.SetStts(&i_this->mStts);
        i_this->mCyl.SetAtSpl(cc_atsp_kind[i_this->mColorType]);
        i_this->mCyl.SetAtAtp(cc_atatp_kind[i_this->mColorType]);

        a_this->max_health = cc_HP_kind[i_this->mColorType];
        a_this->health = cc_HP_kind[i_this->mColorType];

        i_this->m34C = cM_rndFX((fopAcM_GetID(a_this) & 7) * 0x500);
        i_this->m334 = 1.0f;
        i_this->mCyl.OffAtSPrmBit(cCcD_AtSPrm_Set_e);
        i_this->mCyl.ClrAtSet();
        i_this->m2F9 = 1;
        i_this->mEnemyIce.mpActor = a_this;
        i_this->mEnemyIce.mWallRadius = 35.0f;
        i_this->mEnemyIce.mCylHeight = 100.0f;

        i_this->mEnemyFire.mpMcaMorf = i_this->m2B4;
        i_this->mEnemyFire.mpActor = a_this;

        for (s32 i = 0; i < ARRAY_SSIZE(i_this->mEnemyFire.mFlameJntIdxs); i++) {
            i_this->mEnemyFire.mFlameJntIdxs[i] = fire_j[i];
            i_this->mEnemyFire.mParticleScale[i] = fire_sc[i];
        }

        if (i_this->mBehaviorType == 2) {
            a_this->gravity = 0.0f;
            DEMO_COME_START_FLAG = 0;
            DEMO_RET_START_FLAG = 0;
            DEMO_SHORT_CUT_FLAG = 0;

            i_this->mCyl.OnTgSetBit();
            i_this->mCyl.OnCoSetBit();

            i_this->mDisableSpawnSwitchNo = 0xff;
            i_this->mCurrAction = 5;
            i_this->m2F5 = 0x3c;
            i_this->m2B4->getModel()->setBaseTRMtx(i_this->m7EC);
            draw_SUB(i_this);
            return PVar3;
        }

        i_this->m340 = a_this->current.angle.z * 10.0f;
        if (i_this->m340 < 100.0f) {
            i_this->m340 = 100.0f;
        }

        a_this->current.angle.z = 0;
        a_this->shape_angle.z = 0;

        if (i_this->mBehaviorType != 3) {
            if (i_this->mDisableSpawnSwitchNo != 0xff) {
#if VERSION <= VERSION_JPN
                i_this->actor.attention_info.flags = 0;
#endif
                if (i_this->mBehaviorType != 1) {
                    a_this->gravity = -3.0f;
                    i_this->m2F9 = 0;
                }

                i_this->mCyl.OffTgSetBit();
                i_this->mCyl.OffCoSetBit();
                i_this->mCyl.ClrTgHit();
                i_this->mCurrAction = 7;
                i_this->m2F5 = 100;
            }
        } else {
            a_this->stealItemBitNo = i_this->mDisableSpawnSwitchNo;
            i_this->mStts.SetWeight(0xFF);
            fopAcM_OffStatus(a_this, fopAcStts_UNK80000_e);
        }

        if (i_this->mBehaviorType == 4) {
            i_this->mCurrAction = 8;
            i_this->m2F5 = 0x6e;
        }

        BG_check(i_this);
        draw_SUB(i_this);

        i_this->actor.initBt(REG8_F(4) + 150.0f, REG8_F(5) + 100.0f);
        i_this->actor.setBtAttackData(0.0f, 10.0f, REG8_F(6) + 500.0f, fopEn_enemy_c::OPENING_JUMP_PARRY);
        i_this->actor.setBtNowFrame(1000.0f);
    }
    return PVar3;
}

static actor_method_class l_daCC_Method = {
    (process_method_func)daCC_Create,
    (process_method_func)daCC_Delete,
    (process_method_func)daCC_Execute,
    (process_method_func)daCC_IsDelete,
    (process_method_func)daCC_Draw,
};

actor_process_profile_definition g_profile_CC = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_CC,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(cc_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_CC,
    /* Actor SubMtd */ &l_daCC_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK80000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
