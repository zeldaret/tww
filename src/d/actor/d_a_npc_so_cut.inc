// The original name of this file is unknown, but it must exist because d_a_npc_so's "cut" functions
// are in a separate .text section from the rest of its functions.

#include "d/actor/d_a_npc_so.h"
#include "f_op/f_op_kankyo_mng.h"
#include "f_op/f_op_camera.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/d_procname.h"
#include "d/actor/d_a_esa.h"
#include "d/actor/d_a_ship.h"
#include "d/actor/d_a_player.h"

/* 00004CE8-000051E8       .text cutProc__10daNpc_So_cFv */
void daNpc_So_c::cutProc() {
    mB6C = dComIfGp_evmng_getMyStaffId("NpcSo");
    if (mB6C != -1) {
        struct CutEntry {
            daNpc_So_c::CutFunc init;
            daNpc_So_c::CutFunc run;
        };

        static char* action_table[] = {
            "SWIM",           "JUMP",          "APPEAR",        "DIVE",
            "DISAPPEAR",      "SET_ANM",       "EFFECT",        "EQUIP",
            "UNEQUIP",        "EATESA",        "EATESA1ST",     "JUMP_MAPOPEN",
            "MINIGAME",       "TURN",          "MINIGAME_WARP", "MINIGAME_RETURN",
            "PARTNER_SHIP",   "MINIGAME_WAIT", "MINIGAME_END",  "MINIGAME_PL_TURN",
            "MINIGAME_PL_UP",
        };

        static CutEntry cut_tbl[] = {
            {
                &daNpc_So_c::cutSwimStart,
                &daNpc_So_c::cutSwimProc,
            },
            {
                &daNpc_So_c::cutJumpStart,
                &daNpc_So_c::cutJumpProc,
            },
            {
                &daNpc_So_c::cutAppearStart,
                &daNpc_So_c::cutAppearProc,
            },
            {
                &daNpc_So_c::cutDiveStart,
                &daNpc_So_c::cutDiveProc,
            },
            {
                &daNpc_So_c::cutDisappearStart,
                &daNpc_So_c::cutDisappearProc,
            },
            {
                &daNpc_So_c::cutSetAnmStart,
                &daNpc_So_c::cutSetAnmProc,
            },
            {
                &daNpc_So_c::cutEffectStart,
                &daNpc_So_c::cutEffectProc,
            },
            {
                &daNpc_So_c::cutEquipStart,
                &daNpc_So_c::cutEquipProc,
            },
            {
                &daNpc_So_c::cutUnequipStart,
                &daNpc_So_c::cutUnequipProc,
            },
            {
                &daNpc_So_c::cutEatesaStart,
                &daNpc_So_c::cutEatesaProc,
            },
            {
                &daNpc_So_c::cutEatesaFirstStart,
                &daNpc_So_c::cutEatesaFirstProc,
            },
            {
                &daNpc_So_c::cutJumpMapopenStart,
                &daNpc_So_c::cutJumpMapopenProc,
            },
            {
                &daNpc_So_c::cutMiniGameStart,
                &daNpc_So_c::cutMiniGameProc,
            },
            {
                &daNpc_So_c::cutTurnStart,
                &daNpc_So_c::cutTurnProc,
            },
            {
                &daNpc_So_c::cutMiniGameWarpStart,
                &daNpc_So_c::cutMiniGameWarpProc,
            },
            {
                &daNpc_So_c::cutMiniGameReturnStart,
                &daNpc_So_c::cutMiniGameReturnProc,
            },
            {
                &daNpc_So_c::cutPartnerShipStart,
                &daNpc_So_c::cutPartnerShipProc,
            },
            {
                &daNpc_So_c::cutMiniGameWaitStart,
                &daNpc_So_c::cutMiniGameWaitProc,
            },
            {
                &daNpc_So_c::cutMiniGameEndStart,
                &daNpc_So_c::cutMiniGameEndProc,
            },
            {
                &daNpc_So_c::cutMiniGamePlTurnStart,
                &daNpc_So_c::cutMiniGamePlTurnProc,
            },
            {
                &daNpc_So_c::cutMiniGamePlUpStart,
                &daNpc_So_c::cutMiniGamePlUpProc,
            },
        };

        s32 index = dComIfGp_evmng_getMyActIdx(mB6C, action_table, ARRAY_SIZE(action_table), TRUE, 0);
        if (index == -1) {
            dComIfGp_evmng_cutEnd(mB6C);
        } else {
            if (dComIfGp_evmng_getIsAddvance(mB6C)) {
                (this->*cut_tbl[index].init)();
            }
            (this->*cut_tbl[index].run)();
        }
    }
}

/* 000051E8-000051EC       .text cutSwimStart__10daNpc_So_cFv */
void daNpc_So_c::cutSwimStart() {
}

/* 000051EC-00005364       .text cutSwimProc__10daNpc_So_cFv */
void daNpc_So_c::cutSwimProc() {
    cXyz local_30 = mEventCut.getAttnPos();
    mAFC = REG12_F(10) + 7.0f;

    f32 abs = (current.pos - local_30).absXZ();
    s16 target = cLib_targetAngleY(fopAcM_GetPosition_p(this), &local_30);
    cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x400);
    if (abs < REG12_F(7) + 150.0f) {
        mAFC = 0.0f;
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 00005364-000054A4       .text cutJumpStart__10daNpc_So_cFv */
void daNpc_So_c::cutJumpStart() {
    mA9C = 0xf;
    current.pos.y = dLib_getWaterY(current.pos, mAcch);
    f32* pfVar1 = dComIfGp_evmng_getMyFloatP(mB6C, "Speed_y");
    f32* pfVar2 = dComIfGp_evmng_getMyFloatP(mB6C, "SpeedF");

    shape_angle.x = l_HIO.m68;

    if (pfVar1 != NULL) {
        speed.y = *pfVar1;
    } else {
        speed.y = 40.0f;
    }

    if (pfVar2 != NULL) {
        mAFC = *pfVar2;
    } else {
        mAFC = 5.0f;
    }

    offsetSwim();
    speedF = mAFC;
    setAnm(4, false);

    fopAcM_seStart(this, JA_SE_CM_SO_JUMP_L, 0);
}

/* 000054A4-00005598       .text cutJumpProc__10daNpc_So_cFv */
void daNpc_So_c::cutJumpProc() {
    f32 waterHeight = dLib_getWaterY(current.pos, mAcch);

    if (cLib_calcTimer(&mA9C) == 0 && current.pos.y <= waterHeight) {
        fopAcM_seStart(this, JA_SE_CM_SO_LANDING_L, 0);
        fopKyM_createWpillar(fopAcM_GetPosition_p(this), scale.x * 1.4f, 1.4f, 0);
        mAFC = 0.0f;
        speedF = mAFC;
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 00005598-00005610       .text cutAppearStart__10daNpc_So_cFv */
void daNpc_So_c::cutAppearStart() {
    fopAcM_seStart(this, JA_SE_CM_SO_RISE, 0);
    offsetAppear();
}

/* 00005610-00005668       .text cutAppearProc__10daNpc_So_cFv */
void daNpc_So_c::cutAppearProc() {
    if (std::abs(mB34 - mB38.x) < 10.0f) {
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 00005668-00005688       .text cutDiveStart__10daNpc_So_cFv */
void daNpc_So_c::cutDiveStart() {
    offsetDive();
}

/* 00005688-000056E0       .text cutDiveProc__10daNpc_So_cFv */
void daNpc_So_c::cutDiveProc() {
    if (std::abs(mB34 - mB38.x) < 10.0f) {
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 000056E0-00005778       .text cutDisappearStart__10daNpc_So_cFv */
void daNpc_So_c::cutDisappearStart() {
    offsetDive();
    fopAcM_seStart(this, JA_SE_CM_SO_DIVE, 0);
    fopKyM_createWpillar(fopAcM_GetPosition_p(this), scale.x * 1.2f, 1.4f, 0);
}

/* 00005778-000057D0       .text cutDisappearProc__10daNpc_So_cFv */
void daNpc_So_c::cutDisappearProc() {
    if (std::abs(mB34 - mB38.x) < 10.0f) {
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 000057D0-000058D0       .text cutSetAnmStart__10daNpc_So_cFv */
void daNpc_So_c::cutSetAnmStart() {
    const char* name = dComIfGp_evmng_getMyStringP(mB6C, "Name");

    if (name != NULL) {
        if (strcmp(name, "WAIT") == 0) {
            m6D3 = 1;
        } else if (strcmp(name, "TALK") == 0) {
            m6D3 = 3;
        } else if (strcmp(name, "JUMP") == 0) {
            m6D3 = 4;
        } else if (strcmp(name, "SWIM") == 0) {
            m6D3 = 2;
        }
    } else {
        m6D3 = 1;
    }
}

/* 000058D0-0000599C       .text cutSetAnmProc__10daNpc_So_cFv */
void daNpc_So_c::cutSetAnmProc() {
    const char* name = dComIfGp_evmng_getMyStringP(mB6C, "Name");

    if ((m6D3 == 1) || (m6D3 == 4) || (m6D3 == 3) || (m6D3 == 2)) {
        dComIfGp_evmng_cutEnd(mB6C);
    }

    if (mpMorf->isStop()) {
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 0000599C-00005AA8       .text cutEffectStart__10daNpc_So_cFv */
void daNpc_So_c::cutEffectStart() {
    cXyz local_1C = current.pos;
    local_1C.y -= 80.0f;
    cXyz local_28;
    local_28.setall(1.0f);

    // reg swap
    JPABaseEmitter* pEmitter =
        g_dComIfG_gameInfo.play.getParticle()->setNormal(dPa_name::ID_IT_SN_PF_BIKON00, &local_1C, NULL, &local_28, 0xFF, NULL, -1, NULL, NULL, NULL);
    // JPABaseEmitter* pEmitter = dComIfGp_particle_set(dPa_name::ID_IT_SN_PF_BIKON00, &local_1C, NULL, &local_28);
    pEmitter->setGlobalParticleScale(0.62f, 0.6f);
    fopAcM_seStart(this, JA_SE_CM_CMN_NOTICE, 0);
}

/* 00005AA8-00005ADC       .text cutEffectProc__10daNpc_So_cFv */
void daNpc_So_c::cutEffectProc() {
    dComIfGp_evmng_cutEnd(mB6C);
}

/* 00005ADC-00005AE0       .text cutEquipStart__10daNpc_So_cFv */
void daNpc_So_c::cutEquipStart() {
}

/* 00005AE0-00005B1C       .text cutEquipProc__10daNpc_So_cFv */
void daNpc_So_c::cutEquipProc() {
    mA78 = 1;
    dComIfGp_evmng_cutEnd(mB6C);
}

/* 00005B1C-00005B20       .text cutUnequipStart__10daNpc_So_cFv */
void daNpc_So_c::cutUnequipStart() {
}

/* 00005B20-00005B5C       .text cutUnequipProc__10daNpc_So_cFv */
void daNpc_So_c::cutUnequipProc() {
    mA78 = 0;
    dComIfGp_evmng_cutEnd(mB6C);
}

/* 00005B5C-00005B98       .text cutEatesaStart__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaStart() {
    offsetZero();
    mAFC = 0.0f;
    speedF = 0.0f;
}

/* 00005B98-00005BF8       .text cutEatesaProc__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaProc() {
    fopAc_ac_c* pfVar1 = fopAcM_Search(searchEsa_CB, this);
    if (pfVar1 != NULL) {
        esa_class* esa = static_cast<esa_class*>(pfVar1);
        esa->field_0x298 = 1;
    } else {
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 00005BF8-00005C6C       .text cutEatesaFirstStart__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaFirstStart() {
    offsetZero();

    daShip_c* ship = dComIfGp_getShipActor();

    mB10.mRadius = REG8_F(11) + 650.0f;
    mB10.mAngle = ship->shape_angle.y;
#if VERSION > VERSION_DEMO
    mBDA = 1;
    mAFC = 0.0f;
    speedF = 0.0f;
#endif
}

/* 00005C6C-000060FC       .text cutEatesaFirstProc__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaFirstProc() {
    fopAc_ac_c* partner = dComIfGp_getPlayer(1);
    daShip_c* ship = dComIfGp_getShipActor();

    cXyz local_28 = partner->current.pos;

    if (ship != NULL) {
        s32 idx = (s16)(ship->shape_angle.y - 0x4000 + REG12_S(6));
        local_28 = ship->current.pos;
        f32 tmp = 260.0f;
        local_28.x += cM_ssin(idx) * tmp;
        local_28.z += cM_scos(idx) * tmp;
    }

    f32 abs = (current.pos - local_28).absXZ();
    if (abs < REG8_F(11) + 700.0f) {
        cLib_addCalc2(&mB10.mRadius, 30.0f, 0.05f, REG8_F(10) + 8.0f);
    }

    mB10.mAngleSpeed = 0x300;
    mB10.mTranslation = local_28;
    mB10.mTranslation.y = dLib_getWaterY(mB10.mTranslation, mAcch);

    dLib_setCirclePath(&mB10);
    mB10.mPos.y = dLib_getWaterY(mB10.mPos, mAcch);

    cXyz local_34 = mB10.mPos;
#if VERSION > VERSION_DEMO
    local_34.y -= 100.0f;
#endif

#if VERSION == VERSION_DEMO
    f32 abs1 = (current.pos - local_34).absXZ();
    s16 target = cLib_targetAngleY(&mB54, &local_34);
    cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x400);

    if (abs1 < REG12_F(7) + 100.0f) {
        mAFC = 0.0f;
        if (speedF < 1.0f) {
            fopAc_ac_c* pfVar1 = fopAcM_Search(searchEsa_CB, this);
            if (pfVar1 != NULL) {
                esa_class* esa = static_cast<esa_class*>(pfVar1);
                esa->field_0x298 = 1;
            } else {
                dComIfGp_evmng_cutEnd(mB6C);
            }
        }
    } else if (abs1 < REG12_F(7) + 200.0f) {
        mAFC = 12.0f;
    } else {
        mAFC = REG12_F(10) + 20.0f;
    }
#else
    f32 abs1 = (current.pos - local_34).absXZ();
    f32 abs2 = (current.pos - local_28).absXZ();

    mEventCut.setAttnFlag(0);
    mEventCut.setAttnPos(local_34);
    mB44 = local_34;

    f32 fVar5;

    if (abs2 < REG12_F(7) + 100.0f) {
        fVar5 = 2.0f;
        if (abs2 <= 50.0f) {
            fVar5 = 0.0f;
            fopAc_ac_c* pfVar1 = fopAcM_Search(searchEsa_CB, this);
            if (pfVar1 != NULL) {
                esa_class* esa = static_cast<esa_class*>(pfVar1);
                esa->field_0x298 = 1;
            } else {
                dComIfGp_evmng_cutEnd(mB6C);
                mBDA = 0;
                mB04 = 0.0f;
            }
        }

    } else if (abs1 < REG12_F(7) + 200.0f) {
        fVar5 = 12.0f;
    } else {
        fVar5 = REG12_F(10) + 20.0f;
    }

    if (fVar5) {
        s16 target = cLib_targetAngleY(&mB54, &local_34);
        cLib_addCalcAngleS2(&shape_angle.y, target, 3, 0x1200);
    }

    cLib_addCalcPos2(fopAcM_GetPosition_p(this), local_34, 0.1f, fVar5);
    current.pos.y = dLib_getWaterY(current.pos, mAcch) - 100.0f;
#endif
}

/* 000060FC-00006148       .text cutJumpMapopenStart__10daNpc_So_cFv */
void daNpc_So_c::cutJumpMapopenStart() {
    mBBC = 0;
    offsetZero();
    setAnm(2, false);
    mBDA = 1;
}

/* 00006148-000064B8       .text cutJumpMapopenProc__10daNpc_So_cFv */
void daNpc_So_c::cutJumpMapopenProc() {
    daShip_c* ship = dComIfGp_getShipActor();

    if (ship == NULL) {
        dComIfGp_evmng_cutEnd(mB6C);
        return;
    }

    if (mBBC == 0) {
        mB34 = mB38.x;
        gravity = l_HIO.m80;
        speed.y = l_HIO.m84;
        mB00 = speed.y;
        speedF = 0.0f;
        mAFC = speedF;
        shape_angle.x = l_HIO.m68;

        fopAcM_seStart(this, JA_SE_CM_SO_JUMP_DRAW, 0);
        mBBC++;
    } else if (mBBC == 1) {
        s16 sVar2 = ship->shape_angle.y;
        u16 idx = sVar2 + 0x4000;
        mBB0 = ship->current.pos;
        f32 tmp = -l_HIO.m88;
        mBB0.x += cM_ssin(idx) * tmp;
        mBB0.z += cM_scos(idx) * tmp;

        f32 fVar1 = current.pos.y;
        if (speed.y < 1.0) {
            speed.y = 1.0f;
        }

        if (cLib_chasePosXZ(fopAcM_GetPosition_p(this), mBB0, l_HIO.m90) != 0) {
            current.pos.y = fVar1;
            if (l_HIO.m94 == 0) {
                g_dComIfG_gameInfo.play.mFmapOpen = 2;
            }
            shape_angle.y += 0x8000;
            mBBC++;
        }
    } else if (mBBC == 2) {
        s16 sVar2 = ship->shape_angle.y;
        u16 idx = sVar2 + 0x4000;
        mBB0 = ship->current.pos;
        f32 tmp = -l_HIO.m8C;
        mBB0.x += cM_ssin(idx) * tmp;
        mBB0.z += cM_scos(idx) * tmp;

        f32 fVar1 = current.pos.y;
        if (cLib_chasePosXZ(&current.pos, mBB0, l_HIO.m90) != 0) {
            current.pos.y = fVar1;
            fopAcM_seStart(this, JA_SE_CM_SO_DIVE, 0);
            fopKyM_createWpillar(fopAcM_GetPosition_p(this), scale.x * 1.4f, 1.4f, 0);
            mAFC = 0.0f;
            speedF = 0.0f;
            speed.y = 0.0f;
            mB00 = speed.y;
            dComIfGp_evmng_cutEnd(mB6C);
            offsetDive();
            mBDA = 0;
        }
    }
}

/* 000064B8-00006710       .text cutMiniGameStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameStart() {
    mB78 = 0;
    mB80 = 0;
    mB7C = 0;
    mB74 = 0;

    offsetDive();
    dComIfGp_startMiniGame(8);
    mDoAud_seStart(JA_SE_START_WHISTLE);

    daPy_py_c* partner = (daPy_py_c*)dComIfGp_getPlayer(1);
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));

    if (REG8_S(1) == 0) {
        f32 tmp1 = 100.0f;
        f32 tmp2 = -200.0f;

        mBCC = partner->current.pos;
        mBCC.x += cM_ssin(partner->shape_angle.y) * tmp1;
        mBCC.z += cM_scos(partner->shape_angle.y) * tmp1;
        mBCC.y += 50.0f;

        mBC0 = partner->current.pos;
        mBC0.x += cM_ssin(partner->shape_angle.y) * tmp2;
        mBC0.z += cM_scos(partner->shape_angle.y) * tmp2;
        mBC0.y += 100.0f;

        camera->mCamera.Reset(mBCC, mBC0);
        camera->mCamera.Start();
    }

    partner->mDemo.setOriginalDemoType();
    partner->mDemo.setParam0(0);
    partner->mDemo.setDemoMode(daPy_demo_c::DEMO_BOW_MINIGAME_e);

    mBDB = 0;
    mBDE = false;
}

/* 00006710-00006FE4       .text cutMiniGameProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s16 sVar4 = player->shape_angle.y;
    cXyz local_34 = player->current.pos;

    bool bVar1 = false;
    daShip_c* ship = dComIfGp_getShipActor();

    if (ship != NULL) {
        sVar4 = ship->shape_angle.y - 0x4000 + REG12_S(6);
        local_34 = ship->current.pos;
    }

    if (player->checkArrowShoot()) {
        mB78++;
    }

    if (mB78 >= 10) {
        bVar1 = true;
        if (mB74 <= 6) {
#if VERSION > VERSION_DEMO
            player->mDemo.setDemoMode(daPy_demo_c::DEMO_N_TALK_e);
            player->mDemo.setParam0(1);
            initCam();
            moveCam();
            mDoAud_seStart(JA_SE_END_WHISTLE);
#endif
            dComIfGp_endMiniGame(8);
            speedF = 0.0f;
            mAFC = 0.0f;
#if VERSION == VERSION_DEMO
            speed.y = 0.0f;
            mB00 = 0.0f;
#endif
            dComIfGp_evmng_cutEnd(mB6C);
            return;
        }
    }

    switch (mB74) {
    case 0:
        setAnm(2, false);
        mA9C = 30;
        mB84 = 0;
        mB74++;
        mAFC = 0.0f;
        speedF = mAFC;
        offsetSwim();
        break;

    case 1:
        if (cLib_calcTimer(&mA9C) == 0) {
            mB74++;
        }
        break;

    case 2: {
        setAnm(2, false);
        f32 tmp = 1000.0f;
        mB8C = cM_rndF(400.0f) + 1000.0f;
        mB88 = cM_rndF(tmp) + -tmp / 2.0f;
        cXyz local_40(mB88, 0.0f, mB8C);
        cXyz local_4C(0.0f, 0.0f, 0.0f);
        mDoMtx_stack_c::YrotS(sVar4);
        mDoMtx_stack_c::multVec(&local_40, &local_4C);
        local_4C += local_34;
        mEventCut.setAttnPos(local_4C);
        mB74++;
        offsetSwim();
    } break;

    case 3: {
        cXyz local_58 = mEventCut.getAttnPos();
        mAFC = REG12_F(10) + 12.0f;
        f32 abs = (current.pos - local_58).absXZ();
        s16 sVar4 = cLib_targetAngleY(fopAcM_GetPosition_p(this), &local_58);
        cLib_addCalcAngleS2(&shape_angle.y, sVar4, 8, 0x400);
        if (abs < REG12_F(7) + 150.0f) {
            mAFC = 0.0f;
            mB74++;
        }
    } break;

    case 4: {
        f32 tmp = 300.0f;
        mB88 += cM_rndF(tmp) + -tmp / 2.0f;
        cXyz local_64(mB88, 0.0f, mB8C);
        cXyz local_70(0.0f, 0.0f, 0.0f);
        mDoMtx_stack_c::YrotS(sVar4);
        mDoMtx_stack_c::multVec(&local_64, &local_70);
        local_70 += local_34;
        mEventCut.setAttnPos(local_70);
        mAFC = 0.0f;
        speedF = mAFC;
        mA9C = 30;
        mB74++;
        offsetSwim();
    } break;

    case 5: {
        cXyz local_7C = mEventCut.getAttnPos();
        mAFC = 0.0f;
        f32 abs = (current.pos - local_7C).absXZ();
        sVar4 = cLib_targetAngleY(fopAcM_GetPosition_p(this), &local_7C);
        cLib_addCalcAngleS2(&shape_angle.y, sVar4, 8, 0x400);
        if (cLib_calcTimer(&mA9C) == 0) {
            mB74++;
        }
    } break;

    case 6:
        current.pos.y = dLib_getWaterY(current.pos, mAcch);
        mAFC = mB08 * (cM_rndF(5.0f) + 5.0f);
        speedF = mAFC;
        speed.y = mB08 * 18.0f + speedF * 4.0f;
        if (speed.y > l_HIO.m50) {
            speed.y = l_HIO.m50;
        }

        gravity = -0.8f;
        setAnm(4, false);
        shape_angle.x = l_HIO.m68;
        offsetZero();
        mB74++;
        fopAcM_seStart(this, JA_SE_CM_SO_JUMP_L, 0);
        break;

    case 7: {
#if VERSION == VERSION_DEMO
        if (mB84 == 0) {
#else
        f32 dVar8 = dLib_getWaterY(current.pos, mAcch);
        if (mB84 == 0 && mB7C < 10) {
            if (m6D8 == 0)
#endif
            {
#if VERSION == VERSION_DEMO
                setCollision(70.0f, 140.0f);
                mSph.SetR(l_HIO.m3C);
                mSph.SetC(current.pos);
                dComIfG_Ccsp()->Set(&mSph);
#else

                if (current.pos.y >= dVar8 + 50.0f) {
                    mSph.SetR(l_HIO.m3C);
                    mSph.SetC(current.pos);
                    dComIfG_Ccsp()->Set(&mSph);
                } else {
                    cXyz cStack_88(0.0f, 30000.0f, 0.0f);
                    mSph.SetR(0.0f);
                    mSph.SetC(cStack_88);
                    dComIfG_Ccsp()->Set(&mSph);
                }
#endif
            }

            if (checkTgHit()) {
                mB7C++;
#if VERSION > VERSION_DEMO
                if (mB7C >= 10) {
                    mB7C = 10;
                }
#endif
            }
        }

#if VERSION == VERSION_DEMO
        f32 dVar8 = dLib_getWaterY(current.pos, mAcch);
        if (current.pos.y <= dVar8)
#else
        if (current.pos.y <= dVar8)
#endif
        {
            fopAcM_seStart(this, JA_SE_CM_SO_LANDING_L, 0);
            fopKyM_createWpillar(fopAcM_GetPosition_p(this), scale.x * 1.4f, 1.4f, 0);
            mAFC = 0.0f;
            speedF = mAFC;
            mB80++;
            if (mB80 >= 10 || bVar1) {
                player->mDemo.setDemoMode(daPy_demo_c::DEMO_N_TALK_e);
                player->mDemo.setParam0(1);
#if VERSION > VERSION_DEMO
                initCam();
                moveCam();
#endif

                mDoAud_seStart(JA_SE_END_WHISTLE);

#if VERSION == VERSION_DEMO
                initCam();
                moveCam();
#endif

                dComIfGp_endMiniGame(8);
                speedF = 0.0f;
                mAFC = 0.0f;
                dComIfGp_evmng_cutEnd(mB6C);
            } else {
                mB74 = 0;
            }
        }
    } break;
    }
}

/* 00006FE4-00006FF0       .text cutTurnStart__10daNpc_So_cFv */
void daNpc_So_c::cutTurnStart() {
    mA9C = 30;
}

/* 00006FF0-00007114       .text cutTurnProc__10daNpc_So_cFv */
void daNpc_So_c::cutTurnProc() {
    daShip_c* ship = dComIfGp_getShipActor();

    if (ship == NULL) {
        dComIfGp_evmng_cutEnd(mB6C);
    } else {
        s16 idx = ship->shape_angle.y + 0x4000;
        cXyz local_18 = ship->current.pos;
        f32 tmp = -300.0f;
        local_18.x += cM_ssin(idx) * tmp;
        local_18.z += cM_scos(idx) * tmp;

        s16 sVar2 = cLib_targetAngleY(fopAcM_GetPosition_p(this), &local_18);
        cLib_addCalcAngleS2(&shape_angle.y, sVar2, 8, 0x400);
        s32 sVar3 = cLib_distanceAngleS(shape_angle.y, sVar2);
        if (cLib_calcTimer(&mA9C) == 0 || sVar3 <= 0x400) {
            dComIfGp_evmng_cutEnd(mB6C);
        }
    }
}

/* 00007114-00007324       .text cutMiniGameWarpStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWarpStart() {
#if VERSION > VERSION_JPN
    JAIZelBasic::zel_basic->field_0x00bf = 1;
#endif

    daPy_py_c* partner = (daPy_py_c*)dComIfGp_getPlayer(1);
    partner->mDemo.setOriginalDemoType();
    partner->mDemo.setParam0(0);

    daShip_c* ship = (daShip_c*)dComIfGp_getShipActor();
#if VERSION > VERSION_DEMO
    mB90.y = dLib_getWaterY(mB90, mAcch);
#endif
    mBA0 = ship->current.pos;
    mBAC = ship->shape_angle.y;
    ship->initStartPos(&mB90, mB9C + 0x4000);

    csXyz unused(ship->shape_angle);
    s16 tmp = mB9C + REG8_S(6);
    partner->setPlayerPosAndAngle(&mB90, tmp);
    mAFC = 0.0f;
    speedF = mAFC;

    s16 sVar1 = ship->shape_angle.y;
    u16 uVar2 = (sVar1 - 0x4000 + REG12_S(6));
    f32 tmp2 = 300.0f;
    current.pos = mB90;
    current.pos.x += cM_ssin(uVar2) * tmp2;
    current.pos.z += cM_scos(uVar2) * tmp2;

    mBDB = 1;
    mA9C = REG12_S(1) + 10;

    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Reset(mBCC, mBC0);
    camera->mCamera.Start();
}

/* 00007324-00007438       .text cutMiniGameWarpProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWarpProc() {
    daPy_py_c* partner = (daPy_py_c*)dComIfGp_getPlayer(1);
    partner->mDemo.setOriginalDemoType();
    partner->mDemo.setParam0(0);

    daShip_c* ship = dComIfGp_getShipActor();
    partner->mDemo.setDemoMode(daPy_demo_c::DEMO_N_TALK_e);
    partner->mDemo.setParam0(1);

    s16 sVar1 = ship->shape_angle.y;
    u16 idx = sVar1 - 0x4000 + REG12_S(6);
    f32 tmp = 300.0f;
    current.pos = ship->current.pos;
    current.pos.x += cM_ssin(idx) * tmp;
    current.pos.z += cM_scos(idx) * tmp;

    if (cLib_calcTimer(&mA9C) == 0) {
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 00007438-00007524       .text cutMiniGameReturnStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameReturnStart() {
#if VERSION > VERSION_JPN
    JAIZelBasic::zel_basic->field_0x00bf = 0;
#endif

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(1);
    player->mDemo.setOriginalDemoType();
    player->mDemo.setParam0(0);

    daShip_c* ship = (daShip_c*)fopAcM_SearchByName(PROC_SHIP);
    s16 tmp = mB9C + REG8_S(6);
    player->setPlayerPosAndAngle(&mBA0, tmp);
    ship->initStartPos(&mBA0, mBAC);
    mAFC = 0.0f;
    speedF = mAFC;
    mBDB = 1;
    setAnm(2, false);
    offsetDive();
}

/* 00007524-0000781C       .text cutMiniGameReturnProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameReturnProc() {
    daShip_c* ship = dComIfGp_getShipActor();
    s16 uVar2 = ship->shape_angle.y - 0x4000 + REG12_S(6);
    f32 tmp = 300.0f;
    current.pos = ship->current.pos;
    current.pos.x += cM_ssin(uVar2) * tmp;
    current.pos.z += cM_scos(uVar2) * tmp;
    shape_angle.x = 0;

    f32 abs = (mBA0 - current.pos).absXZ();
    if (abs < 400.0f) {
        daPy_py_c* partner = (daPy_py_c*)dComIfGp_getPlayer(1);
        partner->mDemo.setOriginalDemoType();
        partner->mDemo.setParam0(0);
        partner->mDemo.setDemoMode(daPy_demo_c::DEMO_N_TALK_e);
        partner->mDemo.setParam0(1);

        cXyz local_1C(0.0f, 0.0f, 0.0f);
        cXyz local_28(0.0f, 0.0f, 0.0f);
        s16 tmp = partner->shape_angle.y;
        mDoMtx_YrotS(*calc_mtx, tmp);

        local_1C.set(REG0_F(4) + -50.0f, REG0_F(5) + 50.0f, REG0_F(6) + 100.0f);
        MtxPosition(&local_1C, &local_28);

        mBC0 = partner->current.pos + local_28;
        mBCC = partner->current.pos;
        mBCC.y += REG0_F(7) + 90.0f;

        camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
        camera->mCamera.Reset(mBCC, mBC0);
        camera->mCamera.Start();
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 0000781C-00007820       .text cutPartnerShipStart__10daNpc_So_cFv */
void daNpc_So_c::cutPartnerShipStart() {
}

/* 00007820-00007878       .text cutPartnerShipProc__10daNpc_So_cFv */
void daNpc_So_c::cutPartnerShipProc() {
    daShip_c* ship = dComIfGp_getShipActor();
    dComIfGp_event_setTalkPartner(ship);
    dComIfGp_evmng_cutEnd(mB6C);
}

/* 00007878-000078E0       .text cutMiniGameWaitStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWaitStart() {
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    if (REG8_S(1) == 0) {
        camera->mCamera.Stop();
        camera->mCamera.SetTrimSize(1);
    }
}

/* 000078E0-00007914       .text cutMiniGameWaitProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWaitProc() {
    dComIfGp_evmng_cutEnd(mB6C);
}

/* 00007914-00007934       .text cutMiniGameEndStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameEndStart() {
    mA9C = REG12_S(0) + 0x2d;
    mBDE = false;
}

/* 00007934-0000798C       .text cutMiniGameEndProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameEndProc() {
    initCam();
    moveCam();
    if (cLib_calcTimer(&mA9C) == 0) {
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 0000798C-000079AC       .text cutMiniGamePlTurnStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlTurnStart() {
    mA9C = REG12_S(2) + 10;
    mBDE = false;
}

/* 000079AC-00007AC0       .text cutMiniGamePlTurnProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlTurnProc() {
    daPy_py_c* partner = (daPy_py_c*)dComIfGp_getPlayer(1);
    partner->mDemo.setOriginalDemoType();
    partner->mDemo.setParam0(0);

    daShip_c* ship = dComIfGp_getShipActor();
    partner->mDemo.setDemoMode(daPy_demo_c::DEMO_N_TALK_e);
    partner->mDemo.setParam0(1);

    s16 sVar1 = ship->shape_angle.y;
    u16 iVar5 = sVar1 - 0x4000 + REG12_S(6);
    f32 tmp = 300.0f;
    current.pos = ship->current.pos;
    current.pos.x += cM_ssin(iVar5) * tmp;
    current.pos.z += cM_scos(iVar5) * tmp;

    if (cLib_calcTimer(&mA9C) == 0) {
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 00007AC0-00007B1C       .text cutMiniGamePlUpStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlUpStart() {
    mA9C = 30;

    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Stop();
    camera->mCamera.SetTrimSize(1);
}

/* 00007B1C-00007CBC       .text cutMiniGamePlUpProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlUpProc() {
    daPy_py_c* partner = (daPy_py_c*)dComIfGp_getPlayer(1);
    partner->mDemo.setDemoMode(daPy_demo_c::DEMO_N_TALK_e);

    cXyz local_28(0.0f, 0.0f, 0.0f);
    cXyz local_34(0.0f, 0.0f, 0.0f);

    s16 angle = partner->shape_angle.y;
    mDoMtx_YrotS(*calc_mtx, angle);
    local_28.set(REG0_F(4) + -50.0f, REG0_F(5) + 50.0f, REG0_F(6) + 100.0f);
    MtxPosition(&local_28, &local_34);

    mBC0 = partner->current.pos + local_34;
    mBCC = partner->current.pos;
    mBCC.y += REG0_F(7) + 90.0f;

    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    camera->mCamera.Set(mBCC, mBC0);

    if (cLib_calcTimer(&mA9C) == 0) {
        dComIfGp_evmng_cutEnd(mB6C);
    }
}

/* 00007CBC-00007E74       .text initCam__10daNpc_So_cFv */
void daNpc_So_c::initCam() {
    if (mBDE != 1) {
        mBDE = 1;
        camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));

        if (REG8_S(1) == 0) {
            camera->mCamera.Stop();
            camera->mCamera.SetTrimSize(1);

            fopAc_ac_c* partner = dComIfGp_getPlayer(1);
            f32 tmp1 = 100.0f;
            f32 tmp2 = -200.0f;

            mBCC = partner->current.pos;
            mBCC.x += cM_ssin(partner->shape_angle.y) * tmp1;
            mBCC.z += cM_scos(partner->shape_angle.y) * tmp1;
            mBCC.y += 50.0f;
            mBC0 = partner->current.pos;
            mBC0.x += cM_ssin(partner->shape_angle.y) * tmp2;
            mBC0.z += cM_scos(partner->shape_angle.y) * tmp2;
            mBC0.y += 100.0f;
        }
    }
}

/* 00007E74-00008010       .text moveCam__10daNpc_So_cFv */
void daNpc_So_c::moveCam() {
    if (REG8_S(1) == 0) {
        camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
        fopAc_ac_c* partner = dComIfGp_getPlayer(1);
        cXyz local_2C;
        cXyz local_20;

        f32 tmp1 = 150.0f;
        f32 tmp2 = -400.0f;

        local_20 = partner->current.pos;
        local_20.x += cM_ssin(partner->shape_angle.y) * tmp1;
        local_20.z += cM_scos(partner->shape_angle.y) * tmp1;
        local_20.y += 100.0f;

        local_2C = partner->current.pos;
        local_2C.x += cM_ssin(partner->shape_angle.y) * tmp2;
        local_2C.z += cM_scos(partner->shape_angle.y) * tmp2;
        local_2C.y += 300.0f;

        cLib_addCalcPos2(&mBC0, local_2C, 0.05f, 5.0f);
        cLib_addCalcPos2(&mBCC, local_20, 0.05f, 5.0f);

        camera->mCamera.Set(mBCC, mBC0);
    }
}
