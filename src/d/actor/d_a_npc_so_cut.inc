// The original name of this file is unknown, but it must exist because d_a_npc_so's "cut" functions
// are in a separate .text section from the rest of its functions.

#include "d/actor/d_a_npc_so.h"
#include "d/d_s_play.h"
#include "d/d_lib.h"
#include "f_op/f_op_kankyo_mng.h"
#include "f_op/f_op_actor_mng.h"
#include "d/d_com_inf_game.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_ship.h"
#include "JAZelAudio/JAZelAudio_SE.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "JSystem/JMath/JMATrigonometric.h"
#include "d/d_camera.h"

#include "d/d_procname.h"

// Forward declarations
void searchEsa_CB(void*, void*);

/* 00004CE8-000051D0       .text cutProc__10daNpc_So_cFv */
void daNpc_So_c::cutProc() {
    typedef void (daNpc_So_c::*cut_func)();
    struct cut_entry {
        cut_func mStart;
        cut_func mProc;
    };

    mStaffId = dComIfGp_getPEvtManager()->getMyStaffId("NpcSo", NULL, 0);
    if (mStaffId != -1) {
        static char* cut_name[] = {
            "SWIM",            "JUMP",            "APPEAR",          "DIVE",            "DISAPPEAR",
            "SET_ANM",         "EFFECT",          "EQUIP",           "UNEQUIP",         "EATESA",
            "EATESA1ST",       "JUMP_MAPOPEN",    "MINIGAME",        "TURN",            "MINIGAME_WARP",
            "MINIGAME_RETURN", "PARTNER_SHIP",    "MINIGAME_WAIT",   "MINIGAME_END",    "MINIGAME_PL_TURN",
            "MINIGAME_PL_UP",
        };

        static cut_entry cut_table[] = {
            {&daNpc_So_c::cutSwimStart, &daNpc_So_c::cutSwimProc},
            {&daNpc_So_c::cutJumpStart, &daNpc_So_c::cutJumpProc},
            {&daNpc_So_c::cutAppearStart, &daNpc_So_c::cutAppearProc},
            {&daNpc_So_c::cutDiveStart, &daNpc_So_c::cutDiveProc},
            {&daNpc_So_c::cutDisappearStart, &daNpc_So_c::cutDisappearProc},
            {&daNpc_So_c::cutSetAnmStart, &daNpc_So_c::cutSetAnmProc},
            {&daNpc_So_c::cutEffectStart, &daNpc_So_c::cutEffectProc},
            {&daNpc_So_c::cutEquipStart, &daNpc_So_c::cutEquipProc},
            {&daNpc_So_c::cutUnequipStart, &daNpc_So_c::cutUnequipProc},
            {&daNpc_So_c::cutEatesaStart, &daNpc_So_c::cutEatesaProc},
            {&daNpc_So_c::cutEatesaFirstStart, &daNpc_So_c::cutEatesaFirstProc},
            {&daNpc_So_c::cutJumpMapopenStart, &daNpc_So_c::cutJumpMapopenProc},
            {&daNpc_So_c::cutMiniGameStart, &daNpc_So_c::cutMiniGameProc},
            {&daNpc_So_c::cutTurnStart, &daNpc_So_c::cutTurnProc},
            {&daNpc_So_c::cutMiniGameWarpStart, &daNpc_So_c::cutMiniGameWarpProc},
            {&daNpc_So_c::cutMiniGameReturnStart, &daNpc_So_c::cutMiniGameReturnProc},
            {&daNpc_So_c::cutPartnerShipStart, &daNpc_So_c::cutPartnerShipProc},
            {&daNpc_So_c::cutMiniGameWaitStart, &daNpc_So_c::cutMiniGameWaitProc},
            {&daNpc_So_c::cutMiniGameEndStart, &daNpc_So_c::cutMiniGameEndProc},
            {&daNpc_So_c::cutMiniGamePlTurnStart, &daNpc_So_c::cutMiniGamePlTurnProc},
            {&daNpc_So_c::cutMiniGamePlUpStart, &daNpc_So_c::cutMiniGamePlUpProc},
        };

        int act_idx = dComIfGp_getPEvtManager()->getMyActIdx(mStaffId, cut_name, ARRAY_SIZE(cut_name), 1, 0);
        if (act_idx == -1) {
            dComIfGp_getPEvtManager()->cutEnd(mStaffId);
        } else {
            if (dComIfGp_getPEvtManager()->getIsAddvance(mStaffId)) {
                (this->*cut_table[act_idx].mStart)();
            }
            (this->*cut_table[act_idx].mProc)();
        }
    }
}

/* 000051E8-000051EC       .text cutSwimStart__10daNpc_So_cFv */
void daNpc_So_c::cutSwimStart() {
}

/* 000051EC-00005364       .text cutSwimProc__10daNpc_So_cFv */
void daNpc_So_c::cutSwimProc() {
    cXyz attnPos = mEventCut.getAttnPos();
    m0AFC = 7.0f + REG12_F(10);
    
    f32 dist = (current.pos - attnPos).absXZ();
    
    s16 targetAngle = cLib_targetAngleY(&current.pos, &attnPos);
    cLib_addCalcAngleS2(&shape_angle.y, targetAngle, 8, 0x400);
    
    if (dist < 150.0f + REG12_F(7)) {
        m0AFC = 0.0f;
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}

/* 00005364-000054A4       .text cutJumpStart__10daNpc_So_cFv */
void daNpc_So_c::cutJumpStart() {
    m0A9C = 15;
    current.pos.y = dLib_getWaterY(current.pos, mAcch);
    
    f32* speedYP = (f32*)dComIfGp_getPEvtManager()->getMySubstanceP(mStaffId, "Speed_y", 0);
    f32* speedFP = (f32*)dComIfGp_getPEvtManager()->getMySubstanceP(mStaffId, "SpeedF", 0);
    
    shape_angle.x = l_HIO.m0068;
    
    if (speedYP != NULL) {
        speed.y = *speedYP;
    } else {
        speed.y = 40.0f;
    }
    
    if (speedFP != NULL) {
        m0AFC = *speedFP;
    } else {
        m0AFC = 5.0f;
    }
    
    offsetSwim();
    speedF = m0AFC;
    setAnm(4, false);
    
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_SO_JUMP_L, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

/* 000054A4-00005598       .text cutJumpProc__10daNpc_So_cFv */
void daNpc_So_c::cutJumpProc() {
    f32 waterY = dLib_getWaterY(current.pos, mAcch);
    
    if (cLib_calcTimer(&m0A9C) == 0 && current.pos.y <= waterY) {
        s8 reverb = dComIfGp_getReverb(current.roomNo);
        JAIZelBasic::zel_basic->seStart(JA_SE_CM_SO_LANDING_L, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
        fopKyM_createWpillar(&current.pos, 1.4f * scale.x, 1.4f, 0);
        
        m0AFC = 0.0f;
        speedF = m0AFC;
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}

/* 00005598-00005610       .text cutAppearStart__10daNpc_So_cFv */
void daNpc_So_c::cutAppearStart() {
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_SO_RISE, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
    offsetAppear();
}

/* 00005610-00005668       .text cutAppearProc__10daNpc_So_cFv */
void daNpc_So_c::cutAppearProc() {
    if (std::abs(mB34 - mB38) < 10.0f) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}

/* 00005668-00005688       .text cutDiveStart__10daNpc_So_cFv */
void daNpc_So_c::cutDiveStart() {
    offsetDive();
}

/* 00005688-000056E0       .text cutDiveProc__10daNpc_So_cFv */
void daNpc_So_c::cutDiveProc() {
    if (std::abs(mB34 - mB38) < 10.0f) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}

/* 000056E0-00005778       .text cutDisappearStart__10daNpc_So_cFv */
void daNpc_So_c::cutDisappearStart() {
    offsetDive();
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_SO_DIVE, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
    fopKyM_createWpillar(&current.pos, 1.2f * scale.x, 1.4f, 0);
}

/* 00005778-000057D0       .text cutDisappearProc__10daNpc_So_cFv */
void daNpc_So_c::cutDisappearProc() {
    if (std::abs(mB34 - mB38) < 10.0f) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}

/* 000057D0-000058D0       .text cutSetAnmStart__10daNpc_So_cFv */
void daNpc_So_c::cutSetAnmStart() {
    char* name = (char*)dComIfGp_getPEvtManager()->getMySubstanceP(mStaffId, "Name", 4);
    if (name != NULL) {
        if (strcmp(name, "WAIT") == 0) {
            m06D3 = 1;
        } else if (strcmp(name, "TALK") == 0) {
            m06D3 = 3;
        } else if (strcmp(name, "JUMP") == 0) {
            m06D3 = 4;
        } else if (strcmp(name, "SWIM") == 0) {
            m06D3 = 2;
        }
    } else {
        m06D3 = 1;
    }
}

/* 000058D0-0000599C       .text cutSetAnmProc__10daNpc_So_cFv */
void daNpc_So_c::cutSetAnmProc() {
    dEvent_manager_c* evtMgr = dComIfGp_getPEvtManager();
    evtMgr->getMySubstanceP(mStaffId, "Name", 4);

    if (m06D3 == 1 || m06D3 == 4 || m06D3 == 3 || m06D3 == 2) {
        evtMgr->cutEnd(mStaffId);
    }
    if (mpMorf->isStop()) {
        evtMgr->cutEnd(mStaffId);
    }
}

/* 0000599C-00005AA8       .text cutEffectStart__10daNpc_So_cFv */
void daNpc_So_c::cutEffectStart() {
    cXyz pos = current.pos;
    pos.y -= 80.0f;
    cXyz scale_v(1.0f, 1.0f, 1.0f);
    
    JPABaseEmitter* emitter = dComIfGp_particle_set(0x8152, &pos, NULL, &scale_v);
    *(f32*)((u8*)emitter + 0x1F0) = 0.62f;
    *(f32*)((u8*)emitter + 0x1F4) = 0.6f;
    *(f32*)((u8*)emitter + 0x1F8) = 1.0f;
    
    s8 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::zel_basic->seStart(JA_SE_CM_CMN_NOTICE, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
}

/* 00005AA8-00005ADC       .text cutEffectProc__10daNpc_So_cFv */
void daNpc_So_c::cutEffectProc() {
    dComIfGp_getPEvtManager()->cutEnd(mStaffId);
}


/* 00005ADC-00005AE0       .text cutEquipStart__10daNpc_So_cFv */
void daNpc_So_c::cutEquipStart() {
}

/* 00005AE0-00005B1C       .text cutEquipProc__10daNpc_So_cFv */
void daNpc_So_c::cutEquipProc() {
    mEquipNecklace = 1;
    dComIfGp_getPEvtManager()->cutEnd(mStaffId);
}

/* 00005B1C-00005B20       .text cutUnequipStart__10daNpc_So_cFv */
void daNpc_So_c::cutUnequipStart() {
}

/* 00005B20-00005B5C       .text cutUnequipProc__10daNpc_So_cFv */
void daNpc_So_c::cutUnequipProc() {
    mEquipNecklace = 0;
    dComIfGp_getPEvtManager()->cutEnd(mStaffId);
}

/* 00005B5C-00005B98       .text cutEatesaStart__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaStart() {
    offsetZero();
    m0AFC = 0.0f;
    speedF = 0.0f;
}

/* 00005B98-00005BF8       .text cutEatesaProc__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaProc() {
    void* esa = fopAcIt_Judge((fopAcIt_JudgeFunc)searchEsa_CB, this);
    if (esa != NULL) {
        *(u8*)((u32)esa + 0x298) = 1;
    } else {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}


/* 000060FC-00006148       .text cutJumpMapopenStart__10daNpc_So_cFv */
void daNpc_So_c::cutJumpMapopenStart() {
    mBbc = 0;
    offsetZero();
    setAnm(2, false);
    mBDA = 1;
}

/* 00006148-000064B8       .text cutJumpMapopenProc__10daNpc_So_cFv */
void daNpc_So_c::cutJumpMapopenProc() {
    daShip_c* ship = dComIfGp_getShipActor();
    if (ship == NULL) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
        return;
    }

    switch (mBbc) {
    case 0: {
        mB34 = mB38;
        maxFallSpeed = l_HIO.m0080;
        speed.y = l_HIO.m0084;
        mB00 = speed.y;
        gravity = 0.0f;
        m0AFC = gravity;
        mB9C = l_HIO.m0068;
        
        u32 reverb = dComIfGp_getReverb(current.roomNo);
        JAIZelBasic::zel_basic->seStart(0x593C, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
        mBbc++;
        break;
    }
    case 1: {
        s16 angle = ship->shape_angle.y + 0x4000;
        cXyz target;
        target.x = ship->current.pos.x + -l_HIO.m0088 * JMASSin(angle);
        target.y = ship->current.pos.y;
        target.z = ship->current.pos.z + -l_HIO.m0088 * JMASCos(angle);
        
        if (cLib_chasePosXZ(&current.pos, target, l_HIO.m0090)) {
            shape_angle.y = ship->shape_angle.y + 0x8000;
            mBbc++;
        }
        break;
    }
    case 2: {
        s16 angle = ship->shape_angle.y + 0x4000;
        cXyz target;
        target.x = ship->current.pos.x + -l_HIO.m008C * JMASSin(angle);
        target.y = ship->current.pos.y;
        target.z = ship->current.pos.z + -l_HIO.m008C * JMASCos(angle);
        
        if (cLib_chasePosXZ(&current.pos, target, l_HIO.m0090)) {
            u32 reverb = dComIfGp_getReverb(current.roomNo);
            JAIZelBasic::zel_basic->seStart(0x593B, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
            fopKyM_createWpillar(&current.pos, 1.4f * scale.x, 1.4f, 0);
            
            m0AFC = 0.0f;
            gravity = 0.0f;
            speed.y = 0.0f;
            mB00 = speed.y;
            
            dComIfGp_getPEvtManager()->cutEnd(mStaffId);
            offsetDive();
            mBDA = 0;
        }
        break;
    }
    }
}

/* 000064B8-0000670C       .text cutMiniGameStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameStart() {
    mB78 = 0;
    mB80 = 0;
    mB7C = 0;
    mB74 = 0;
    offsetDive();
    
    g_dComIfG_gameInfo.play.mMiniGameType = 8;
    g_dComIfG_gameInfo.play.mMinigameFlags |= 0x80;
    
    JAIZelBasic::zel_basic->seStart(0x8F0, NULL, 0, 0, 1.0f, 1.0f, -1.0f, -1.0f, 0);
    
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    
    if (REG8_S(1) == 0) {
        mBCC.x = player->current.pos.x;
        mBCC.y = player->current.pos.y;
        mBCC.z = player->current.pos.z;
        
        mBCC.x += l_HIO.m0050 * JMASSin(player->shape_angle.y);
        mBCC.z += l_HIO.m0050 * JMASCos(player->shape_angle.y);
        mBCC.y += l_HIO.m0074;
        
        mBC0 = player->current.pos;
        mBC0.x += -200.0f * JMASSin(player->shape_angle.y);
        mBC0.z += -200.0f * JMASCos(player->shape_angle.y);
        mBC0.y += l_HIO.m0050;
        
        dCamera_c* camera = (dCamera_c*)dComIfGp_getCamera(0);
        camera->Reset(mBCC, mBC0);
        camera->Start();
    }
    
    player->mRopePos.z = 3.0f;
    player->mDemo.setOriginalDemoType();
    player->mDemo.setParam0(0);
    player->mDemo.setParam1(0x44);
    mBDB = 0;
    m0BDE = 0;
}

/* 00006710-00006FE4       .text cutMiniGameProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    s16 playerAngle = player->shape_angle.y;
    cXyz playerPos = player->current.pos;
    bool forced_end = false;
    
    daShip_c* ship = dComIfGp_getShipActor();
    if (ship != NULL) {
        s16 angle = ship->shape_angle.y + REG12_S(6);
        playerAngle = angle - 0x4000;
        playerPos = ship->current.pos;
    }
    
    if (player->checkResetFlg0(daPy_py_c::daPyRFlg0_ARROW_SHOOT)) {
        mB78++;
    }
    
    if (mB78 >= 10) {
        forced_end = true;
        if (mBbc <= 6) {
            player->mDemo.setDemoMode(6);
            player->mDemo.setParam0(1);
            initCam();
            moveCam();
            
            u32 reverb = dComIfGp_getReverb(current.roomNo);
            JAIZelBasic::zel_basic->seStart(0x8F1, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
            
            g_dComIfG_gameInfo.play.mMiniGameType = 0;
            g_dComIfG_gameInfo.play.mMinigameFlags ^= 0x80;
            g_dComIfG_gameInfo.play.mMinigameResult = 0;
            
            gravity = 0.0f;
            m0AFC = 0.0f;
            dComIfGp_getPEvtManager()->cutEnd(mStaffId);
            return;
        }
    }
    
    switch (mBbc) {
    case 0:
        cLib_addCalcAngleS2(&shape_angle.y, playerAngle, 4, 0x800);
        cLib_addCalc2(&speedF, 0.0f, 0.2f, 2.0f);
        mBCC.y = current.pos.y;
        
        if (cLib_calcTimer(&m0A9C) == 0 && cLib_distanceAngleS(shape_angle.y, playerAngle) < 0x2000) {
            mBbc++;
        }
        break;
    case 1:
        switch (mB74) {
        case 0:
            setAnm(2, false);
            m0A9C = 30;
            mB84 = 0;
            mB74++;
            speedF = 0.0f;
            m0AFC = 0.0f;
            offsetSwim();
            break;
        case 1:
            if (cLib_calcTimer(&m0A9C) == 0) {
                mB74++;
            }
            break;
        case 2:
            setAnm(2, false);
            mB8C = 0.0f + cM_rndF(l_HIO.m0064);
            mB88 = 0.0f + cM_rndF(-0.0f * 0.0f);
            
            mDoMtx_stack_c::YrotS(playerAngle);
            {
                cXyz offset(mB88, 0.0f, mB8C);
                mDoMtx_stack_c::multVec(&offset, &mB90);
            }
            mB90 += playerPos;
            mB74++;
            offsetSwim();
            break;
        case 3:
            {
                cXyz dist = mB90 - current.pos;
                dist.y = 0.0f;
                f32 mag = PSVECSquareMag(&dist);
                cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &mB90), 8, 0x400);
                if (mag < l_HIO.m0054 + 0.0f) {
                    m0AFC = 0.0f;
                    mB74++;
                } else {
                    m0AFC = -40.0f + 0.001f;
                }
            }
            break;
        case 4:
            setAnm(2, false);
            mB88 = 0.0f * (cM_rndF(l_HIO.m0074) - 0.0f);
            mDoMtx_stack_c::YrotS(playerAngle);
            {
                cXyz offset(mB88, 0.0f, mB8C);
                mDoMtx_stack_c::multVec(&offset, &mB90);
            }
            mB90 += playerPos;
            m0AFC = 0.0f;
            m0A9C = 30;
            mB74++;
            offsetSwim();
            break;
        case 5:
            cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &mB90), 8, 0x400);
            if (cLib_calcTimer(&m0A9C) == 0) {
                mB74++;
            }
            break;
        case 6:
            {
                current.pos.y = dLib_getWaterY(current.pos, mAcch);
                speedF = mB08 * (cM_rndF(0.0f) + 0.0f);
                m0AFC = speedF;
                speed.y = l_HIO.m007C * mB08 + 0.5f * speedF;
                if (speed.y > l_HIO.m003C) speed.y = l_HIO.m003C;
                gravity = 1.0f;
                setAnm(4, false);
                shape_angle.x = l_HIO.m0054;
                offsetZero();
                mB74++;
                u32 reverb = dComIfGp_getReverb(current.roomNo);
                JAIZelBasic::zel_basic->seStart(0x5938, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
            }
            break;
        case 7:
            {
                f32 waterY = dLib_getWaterY(current.pos, mAcch);
                if (mB84 == 0 && mB7C < 10) {
                    if (current.pos.y < waterY + l_HIO.m0060) {
                        checkTgHit();
                    }
                }
                
                if (current.pos.y <= waterY) {
                    u32 reverb = dComIfGp_getReverb(current.roomNo);
                    JAIZelBasic::zel_basic->seStart(0x5939, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
                    fopKyM_createWpillar(&current.pos, 0.0f * scale.x, 0.0f, 0);
                    m0AFC = 0.0f;
                    speedF = 0.0f;
                    mB80++;
                    if (mB80 >= 10 || forced_end) {
                        player->mDemo.setDemoMode(6);
                        player->mDemo.setParam0(1);
                        initCam();
                        moveCam();
                        JAIZelBasic::zel_basic->seStart(0x8F1, &eyePos, 0, reverb, 1.0f, 1.0f, -1.0f, -1.0f, 0);
                        g_dComIfG_gameInfo.play.mMiniGameType = 0;
                        g_dComIfG_gameInfo.play.mMinigameFlags ^= 0x80;
                        g_dComIfG_gameInfo.play.mMinigameResult = 0;
                        gravity = 0.0f;
                        m0AFC = 0.0f;
                        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
                    } else {
                        mB74 = 0;
                    }
                }
            }
            break;
        }
    }
}

/* 00006FE4-00006FF0       .text cutTurnStart__10daNpc_So_cFv */
void daNpc_So_c::cutTurnStart() {
    m0A9C = 30;
}

/* 00006FF0-00007114       .text cutTurnProc__10daNpc_So_cFv */
void daNpc_So_c::cutTurnProc() {
    daShip_c* ship = dComIfGp_getShipActor();
    if (ship == NULL) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    } else {
        s16 targetAngle = ship->shape_angle.y + 0x4000;
        cXyz targetPos;
        targetPos.x = ship->current.pos.x;
        targetPos.y = ship->current.pos.y;
        targetPos.z = ship->current.pos.z;
        targetPos.x += -300.0f * JMASSin(targetAngle);
        targetPos.z += -300.0f * JMASCos(targetAngle);

        s16 target = cLib_targetAngleY(&current.pos, &targetPos);
        cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x400);

        s32 dist = cLib_distanceAngleS(shape_angle.y, target);
        if (cLib_calcTimer(&m0A9C) == 0 || dist <= 0x400) {
            dComIfGp_getPEvtManager()->cutEnd(mStaffId);
        }
    }
}

/* 00005BF8-00005C6C       .text cutEatesaFirstStart__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaFirstStart() {
    offsetZero();
    daShip_c* ship = dComIfGp_getShipActor();
    mB28 = 600.0f + REG8_F(11);
    mB30 = ship->shape_angle.y;
    mBDA = 1;
    m0AFC = 0.0f;
    speedF = 0.0f;
}

/* 00005C6C-000060FC       .text cutEatesaFirstProc__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaFirstProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    daShip_c* ship = dComIfGp_getShipActor();
    
    cXyz targetPos = player->current.pos;
    if (ship != NULL) {
        s16 targetAngle = ship->shape_angle.y + REG12_S(6) - 0x4000;
        
        cXyz offset;
        f32 radius = 600.0f;
        offset.x = radius * JMASSin(targetAngle);
        offset.y = 0.0f;
        offset.z = radius * JMASCos(targetAngle);
        
        targetPos = ship->current.pos + offset;
    }
    
    cXyz diff = targetPos - current.pos;
    diff.y = 0.0f;
    f32 distSq = diff.abs2();
    
    f32 targetSpeed = 8.0f + REG8_F(11);
    if (distSq < targetSpeed * targetSpeed) {
        cLib_addCalc2(&mB28, 50.0f + REG8_F(10), 0.2f, 2.0f + REG8_F(10));
    }
    
    mB32 = 0x300;
    mB10 = current.pos;
    mB10.y = dLib_getWaterY(mB10, mAcch);
    
    dComIfGp_getPEvtManager()->cutEnd(mStaffId);
}

/* 00007114-00007324       .text cutMiniGameWarpStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWarpStart() {
    JAIZelBasic::zel_basic->field_0x00bf = 1;
    
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    player->mDemo.setOriginalDemoType();
    player->mDemo.setParam0(0);
    
    daShip_c* ship = dComIfGp_getShipActor();
    current.pos.y = dLib_getWaterY(eyePos, mAcch);
    mB90.y = current.pos.y;
    
    mBA0 = ship->current.pos;
    mBAC = ship->current.angle.y;
    
    ship->initStartPos(&mB90, mB9C + 0x4000);
    
    dCamera_c* camera = (dCamera_c*)dComIfGp_getCamera(0);
    camera->Reset(mBCC, mBC0);
    camera->Start();
    
    m0AFC = 1.0f;
    speedF = 1.0f; // mB08 in actor? Check assembly 8408: stfs f0, 0x254(r31)
    mBDB = 1;
    m0A9C = REG8_S(6) + 10;
}

/* 00007324-00007438       .text cutMiniGameWarpProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWarpProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    player->mDemo.setOriginalDemoType();
    player->mDemo.setParam0(0);
    player->mDemo.setDemoMode(6);
    player->mDemo.setParam0(1);
    
    daShip_c* ship = dComIfGp_getShipActor();
    mB90.x = ship->current.pos.x;
    mB90.y = ship->current.pos.y;
    mB90.z = ship->current.pos.z;
    
    // Position calculation based on ship angle and HIO reg 0x750
    s16 angle = ship->current.angle.y + REG12_S(6);
    s16 targetAngle = angle - 0x4000;
    
    current.pos = ship->current.pos;
    mBCC.x = current.pos.x + 100.0f * JMASSin(targetAngle);
    mBCC.y = current.pos.y;
    mBCC.z = current.pos.z + 100.0f * JMASCos(targetAngle);
    
    if (cLib_calcTimer(&m0A9C) == 0) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}

/* 00007438-00007524       .text cutMiniGameReturnStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameReturnStart() {
    JAIZelBasic::zel_basic->field_0x00bf = 0;
    
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    player->mDemo.setOriginalDemoType();
    player->mDemo.setParam0(0);
    
    daShip_c* ship = (daShip_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeForPName, (void*)PROC_SHIP);
    
    ship->initStartPos(&mBA0, mB9C + REG8_S(6));
    ship->initStartPos(&mBA0, mBAC);
    
    m0AFC = 1.0f;
    speedF = 1.0f;
    mBDB = 1;
    setAnm(2, false);
    offsetDive();
}


/* 00007524-0000781C       .text cutMiniGameReturnProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameReturnProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    daShip_c* ship = dComIfGp_getShipActor();
    current.pos = ship->current.pos;
    
    s16 angle = ship->current.angle.y + REG12_S(6);
    s16 targetAngle = angle - 0x4000;
    
    current.pos.x += l_HIO.m0088 * JMASSin(targetAngle);
    current.pos.z += l_HIO.m0088 * JMASCos(targetAngle);
    
    shape_angle.y = 0;
    
    cXyz diff = mB90 - current.pos;
    f32 magSq = PSVECSquareMag(&diff);
    
    if (magSq < l_HIO.m0078) {
         player->mDemo.setOriginalDemoType();
         player->mDemo.setParam0(0);
         player->mDemo.setDemoMode(6);
         player->mDemo.setParam0(1);
         
         mDoMtx_stack_c::YrotS(player->shape_angle.y);
         cXyz offset;
         offset.x = l_HIO.m0034 + REG0_F(4);
         offset.y = l_HIO.m0038 + REG0_F(5);
         offset.z = l_HIO.m003C + REG0_F(6);
         
         mDoMtx_stack_c::multVec(&offset, &mBC0);
         mBC0 += player->current.pos;
         
         mBCC = player->current.pos;
         mBCC.y += l_HIO.m0040 + REG0_F(7);
         
         dCamera_c* camera = (dCamera_c*)dComIfGp_getCamera(0);
         camera->Reset(mBCC, mBC0);
         camera->Start();
         
         dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}
/* 0000781C-00007820       .text cutPartnerShipStart__10daNpc_So_cFv */
void daNpc_So_c::cutPartnerShipStart() {
}

/* 00007820-00007878       .text cutPartnerShipProc__10daNpc_So_cFv */
void daNpc_So_c::cutPartnerShipProc() {
    daShip_c* ship = dComIfGp_getShipActor();
    dEvt_control_c* event = g_dComIfG_gameInfo.play.getEvent();
    event->mPtTalk = event->getPId(ship);
    dComIfGp_getPEvtManager()->cutEnd(mStaffId);
}

/* 00007878-000078E0       .text cutMiniGameWaitStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWaitStart() {
    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    if (REG8_S(1) == 0) {
        cam->mCamera.Stop();
        cam->mCamera.SetTrimSize(1);
    }
}

/* 000078E0-00007914       .text cutMiniGameWaitProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWaitProc() {
    dComIfGp_getPEvtManager()->cutEnd(mStaffId);
}

/* 00004754-000048BC       .text initCam__10daNpc_So_cFv */
void daNpc_So_c::initCam() {
    if (m0BDE == 1) {
        return;
    }
    m0BDE = 1;

    int camID = dComIfGp_getPlayerCameraID(0);
    camera_class* cam = (camera_class*)dComIfGp_getCamera(camID);

    if (REG8_S(1) != 0) {
        return;
    }

    cam->mCamera.Stop();
    cam->mCamera.SetTrimSize(1);

    fopAc_ac_c* player = dComIfGp_getLinkPlayer();

    mBCC = player->current.pos;
    mBCC.x += 100.0f * JMASSin(player->shape_angle.y);
    mBCC.z += 100.0f * JMASCos(player->shape_angle.y);
    mBCC.y += 50.0f;

    mBC0 = player->current.pos;
    mBC0.x += -200.0f * JMASSin(player->shape_angle.y);
    mBC0.z += -200.0f * JMASCos(player->shape_angle.y);
    mBC0.y += 100.0f;
}

/* 000048BC-00004A78       .text moveCam__10daNpc_So_cFv */
void daNpc_So_c::moveCam() {
    if (REG8_S(1) != 0) {
        return;
    }

    int camID = dComIfGp_getPlayerCameraID(0);
    camera_class* cam = (camera_class*)dComIfGp_getCamera(camID);

    fopAc_ac_c* player = dComIfGp_getLinkPlayer();

    cXyz target1 = player->current.pos;
    s16 angle = player->shape_angle.y;
    target1.x += 150.0f * JMASSin(angle);
    target1.z += 150.0f * JMASCos(angle);
    target1.y += 100.0f;

    cXyz target2 = player->current.pos;
    target2.x += -400.0f * JMASSin(angle);
    target2.z += -400.0f * JMASCos(angle);
    target2.y += 300.0f;

    cLib_addCalcPos2(&mBC0, target2, 0.05f, 5.0f);
    cLib_addCalcPos2(&mBCC, target1, 0.05f, 5.0f);

    cam->mCamera.Set(mBCC, mBC0);
}

/* 00007914-00007934       .text cutMiniGameEndStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameEndStart() {
    m0A9C = REG12_S(0) + 45;
    m0BDE = 0;
}

/* 00007934-0000798C       .text cutMiniGameEndProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameEndProc() {
    initCam();
    moveCam();
    if (cLib_calcTimer(&m0A9C) == 0) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}

/* 0000798C-000079AC       .text cutMiniGamePlTurnStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlTurnStart() {
    m0A9C = REG12_S(2) + 10;
    m0BDE = 0;
}

/* 000079AC-00007AC0       .text cutMiniGamePlTurnProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlTurnProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    
    player->mDemo.setOriginalDemoType();
    player->mDemo.setParam0(0);
    
    daShip_c* ship = dComIfGp_getShipActor();
    
    player->mDemo.setDemoMode(6);
    player->mDemo.setParam0(1);
    
    s16 angle = ship->shape_angle.y + REG12_S(6) - 0x4000;
    current.pos = ship->current.pos;
    
    current.pos.x += 300.0f * JMASSin(angle);
    current.pos.z += 300.0f * JMASCos(angle);
    
    if (cLib_calcTimer(&m0A9C) == 0) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}

/* 00007AC0-00007AE0       .text cutMiniGamePlUpStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlUpStart() {
    m0A9C = 30;

    camera_class* cam = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    cam->mCamera.Stop();
    cam->mCamera.SetTrimSize(1);
}

/* 00007AE0-00007C24       .text cutMiniGamePlUpProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlUpProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getLinkPlayer();
    player->mDemo.setDemoMode(6);

    cXyz offset(0.0f, 0.0f, 0.0f);
    cXyz result(0.0f, 0.0f, 0.0f);

    mDoMtx_YrotS(*calc_mtx, player->shape_angle.y);

    offset.x = -50.0f + REG0_F(4);
    offset.y = 50.0f + REG0_F(5);
    offset.z = 100.0f + REG0_F(6);

    MtxPosition(&offset, &result);
    mBC0 = player->current.pos + result;

    mBCC = player->current.pos;
    mBCC.y += 90.0f + REG0_F(7);

    int camID = dComIfGp_getPlayerCameraID(0);
    camera_class* cam = (camera_class*)dComIfGp_getCamera(camID);
    cam->mCamera.Set(mBCC, mBC0);

    if (cLib_calcTimer(&m0A9C) == 0) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}
