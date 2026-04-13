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

    mStaffId = dComIfGp_getPEvtManager()->getMyStaffId("NpcSo", NULL, 0);
    if (mStaffId != -1) {
        int act_idx = dComIfGp_getPEvtManager()->getMyActIdx(mStaffId, cut_name, ARRAY_SIZE(cut_name), 1, 0);
        if (act_idx != -1) {
            if (dComIfGp_getPEvtManager()->getIsAddvance(mStaffId)) {
                (this->*cut_table[act_idx].mStart)();
            }
            (this->*cut_table[act_idx].mProc)();
        } else {
            dComIfGp_getPEvtManager()->cutEnd(mStaffId);
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
    
    cXyz diff = current.pos - attnPos;
    diff.y = 0.0f;
    f32 dist = diff.abs();
    
    s16 targetAngle = cLib_targetAngleY(&current.pos, &attnPos);
    cLib_addCalcAngleS2(&shape_angle.y, targetAngle, 8, 0x400);
    
    if (dist < 1.0f + REG12_F(7)) {
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
    
    fopAcM_seStart(this, JA_SE_CM_SO_JUMP_L, 0);
}

/* 000054A4-00005598       .text cutJumpProc__10daNpc_So_cFv */
void daNpc_So_c::cutJumpProc() {
    f32 waterY = dLib_getWaterY(current.pos, mAcch);
    
    if (cLib_calcTimer(&m0A9C) == 0 && current.pos.y <= waterY) {
        fopAcM_seStart(this, JA_SE_CM_SO_LANDING_L, 0);
        fopKyM_createWpillar(&current.pos, 1.4f * scale.x, 1.4f, 0);
        
        m0AFC = 0.0f;
        speedF = m0AFC;
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}

/* 00005598-00005610       .text cutAppearStart__10daNpc_So_cFv */
void daNpc_So_c::cutAppearStart() {
    fopAcM_seStart(this, JA_SE_CM_SO_RISE, 0);
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
    fopAcM_seStart(this, JA_SE_CM_SO_DIVE, 0);
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
    if (m06D3 == 1 || m06D3 == 4 || m06D3 == 3 || m06D3 == 2) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    } else if (mpMorf->isStop() || mpMorf->checkFrame(0.0f)) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}

/* 0000599C-00005AA8       .text cutEffectStart__10daNpc_So_cFv */
void daNpc_So_c::cutEffectStart() {
    cXyz pos = current.pos;
    pos.y -= 150.0f;
    cXyz scale_v(1.0f, 1.0f, 1.0f);
    
    JPABaseEmitter* emitter = dComIfGp_particle_set(0x8152, &pos, NULL, &scale_v);
    *(f32*)((u8*)emitter + 0x1F0) = m_heapsize.m00D8;
    *(f32*)((u8*)emitter + 0x1F4) = m_heapsize.m00DC;
    *(f32*)((u8*)emitter + 0x1F8) = 1.0f;
    
    fopAcM_seStart(this, JA_SE_CM_CMN_NOTICE, 0);
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
    
    u32 reverb = dComIfGp_getReverb(current.roomNo);
    JAIZelBasic::zel_basic->seStart(0x8F0, &eyePos, 0, reverb, l_HIO.m0094, l_HIO.m00C8, -1.0f, -1.0f, 0); /* TODO: nonmatching, asm uses offsets 0xA8/0xC8 */
    
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    
    if (l_HIO.m012A == 0) { // heap 0x13E? No, check assembly
        mBCC.x = player->current.pos.x;
        mBCC.y = player->current.pos.y;
        mBCC.z = player->current.pos.z;
        
        mBCC.x += l_HIO.m003C * JMASSin(player->shape_angle.y);
        mBCC.z += l_HIO.m003C * JMASCos(player->shape_angle.y);
        mBCC.y += l_HIO.m0060;
        
        mBC0 = player->current.pos;
        mBC0.x += l_HIO.m00F4 * JMASSin(player->shape_angle.y);
        mBC0.z += l_HIO.m00F4 * JMASCos(player->shape_angle.y);
        mBC0.y += l_HIO.m0070;
        
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
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    s16 playerAngle = player->shape_angle.y;
    cXyz playerPos = player->current.pos;
    bool forced_end = false;
    
    daShip_c* ship = dComIfGp_getShipActor();
    if (ship != NULL) {
        s16 angle = ship->shape_angle.y + g_regHIO.mChild[11].mShortRegs[24];
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
            JAIZelBasic::zel_basic->seStart(0x8F1, &eyePos, 0, reverb, l_HIO.m0094, l_HIO.m00C8, -1.0f, -1.0f, 0);
            
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
            mB8C = l_HIO.m00F8 + cM_rndF(l_HIO.m0064);
            mB88 = l_HIO.m00F8 + cM_rndF(-l_HIO.m00F8 * l_HIO.m00FC);
            
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
                if (mag < l_HIO.m0054 + l_HIO.m012C) {
                    m0AFC = 0.0f;
                    mB74++;
                } else {
                    m0AFC = l_HIO.m0130 + l_HIO.m00E0;
                }
            }
            break;
        case 4:
            setAnm(2, false);
            mB88 = l_HIO.m00FC * (cM_rndF(l_HIO.m0074) - l_HIO.m00FC);
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
                speedF = mB08 * (cM_rndF(l_HIO.m00CC) + l_HIO.m00CC);
                m0AFC = speedF;
                speed.y = l_HIO.m007C * mB08 + l_HIO.m0100 * speedF;
                if (speed.y > l_HIO.m003C) speed.y = l_HIO.m003C;
                gravity = l_HIO.m0104;
                setAnm(4, false);
                shape_angle.x = l_HIO.m0054;
                offsetZero();
                mB74++;
                u32 reverb = dComIfGp_getReverb(current.roomNo);
                JAIZelBasic::zel_basic->seStart(0x5938, &eyePos, 0, reverb, l_HIO.m0094, l_HIO.m00C8, -1.0f, -1.0f, 0);
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
                    JAIZelBasic::zel_basic->seStart(0x5939, &eyePos, 0, reverb, l_HIO.m0094, l_HIO.m00C8, -1.0f, -1.0f, 0);
                    fopKyM_createWpillar(&current.pos, l_HIO.m00D0 * scale.x, 0.0f, 0);
                    m0AFC = 0.0f;
                    speedF = 0.0f;
                    mB80++;
                    if (mB80 >= 10 || forced_end) {
                        player->mDemo.setDemoMode(6);
                        player->mDemo.setParam0(1);
                        initCam();
                        moveCam();
                        JAIZelBasic::zel_basic->seStart(0x8F1, &eyePos, 0, reverb, l_HIO.m0094, l_HIO.m00C8, -1.0f, -1.0f, 0);
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
        targetPos.x = ship->current.pos.x + -300.0f * JMASSin(targetAngle);
        targetPos.y = ship->current.pos.y;
        targetPos.z = ship->current.pos.z + -300.0f * JMASCos(targetAngle);

        s16 target = cLib_targetAngleY(&current.pos, &targetPos);
        cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x400);

        if (cLib_calcTimer(&m0A9C) == 0 || cLib_distanceAngleS(shape_angle.y, target) <= 0x400) {
            dComIfGp_getPEvtManager()->cutEnd(mStaffId);
        }
    }
}

/* 00005BF8-00005C6C       .text cutEatesaFirstStart__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaFirstStart() {
    offsetZero();
    mB28 = 600.0f + g_regHIO.mChild[11].mFloatRegs[14];
    
    daShip_c* ship = dComIfGp_getShipActor();
    if (ship != NULL) {
        mB30 = ship->shape_angle.y;
    }
    mBDA = 1;
    m0AFC = 0.0f;
    speedF = 0.0f;
}

/* 00005C6C-000060FC       .text cutEatesaFirstProc__10daNpc_So_cFv */
void daNpc_So_c::cutEatesaFirstProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    daShip_c* ship = dComIfGp_getShipActor();
    
    cXyz targetPos = player->current.pos;
    if (ship != NULL) {
        s16 targetAngle = ship->shape_angle.y + g_regHIO.mChild[11].mShortRegs[8] - 0x4000;
        
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
    
    f32 targetSpeed = 8.0f + g_regHIO.mChild[11].mFloatRegs[14];
    if (distSq < targetSpeed * targetSpeed) {
        cLib_addCalc2(&mB28, 50.0f + g_regHIO.mChild[11].mFloatRegs[13], 0.2f, 2.0f + g_regHIO.mChild[11].mFloatRegs[13]);
    }
    
    mB32 = 0x300;
    mB10 = current.pos;
    mB10.y = dLib_getWaterY(mB10, mAcch);
    
    dComIfGp_getPEvtManager()->cutEnd(mStaffId);
}

/* 00007114-00007324       .text cutMiniGameWarpStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWarpStart() {
    JAIZelBasic::zel_basic->field_0x00bf = 1;
    
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
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
    m0A9C = g_regHIO.mChild[7].mShortRegs[22] + 10;
}

/* 00007324-00007438       .text cutMiniGameWarpProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWarpProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    player->mDemo.setOriginalDemoType();
    player->mDemo.setParam0(0);
    player->mDemo.setDemoMode(6);
    player->mDemo.setParam0(1);
    
    daShip_c* ship = dComIfGp_getShipActor();
    mB90.x = ship->current.pos.x;
    mB90.y = ship->current.pos.y;
    mB90.z = ship->current.pos.z;
    
    // Position calculation based on ship angle and HIO reg 0x750
    s16 angle = ship->current.angle.y + g_regHIO.mChild[7].mShortRegs[16];
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
    
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    player->mDemo.setOriginalDemoType();
    player->mDemo.setParam0(0);
    
    daShip_c* ship = (daShip_c*)fopAcIt_Judge((fopAcIt_JudgeFunc)fpcSch_JudgeForPName, (void*)PROC_SHIP);
    
    ship->initStartPos(&mBA0, mB9C + g_regHIO.mChild[5].mShortRegs[8]);
    ship->initStartPos(&mBA0, mBAC);
    
    m0AFC = 1.0f;
    speedF = 1.0f;
    mBDB = 1;
    setAnm(2, false);
    offsetDive();
}


/* 00007524-0000781C       .text cutMiniGameReturnProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameReturnProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    daShip_c* ship = dComIfGp_getShipActor();
    current.pos = ship->current.pos;
    
    s16 angle = ship->current.angle.y + g_regHIO.mChild[11].mShortRegs[8];
    s16 targetAngle = angle - 0x4000;
    
    current.pos.x += m_heapsize.m0088 * JMASSin(targetAngle);
    current.pos.z += m_heapsize.m0088 * JMASCos(targetAngle);
    
    shape_angle.y = 0;
    
    cXyz diff = mB90 - current.pos;
    f32 magSq = PSVECSquareMag(&diff);
    
    if (magSq < m_heapsize.m0078) {
         player->mDemo.setOriginalDemoType();
         player->mDemo.setParam0(0);
         player->mDemo.setDemoMode(6);
         player->mDemo.setParam0(1);
         
         mDoMtx_stack_c::YrotS(player->shape_angle.y);
         cXyz offset;
         offset.x = m_heapsize.m0034 + g_regHIO.mChild[11].mFloatRegs[7];
         offset.y = m_heapsize.m0038 + g_regHIO.mChild[11].mFloatRegs[8];
         offset.z = m_heapsize.m003C + g_regHIO.mChild[11].mFloatRegs[9];
         
         mDoMtx_stack_c::multVec(&offset, &mBCC);
         mBCC += ship->current.pos;
         mBCC.y += m_heapsize.m0040 + g_regHIO.mChild[11].mFloatRegs[10];
         
         mBC0 = ship->current.pos;
         mBC0.y += m_heapsize.m0044 + g_regHIO.mChild[11].mFloatRegs[11];
         
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
    if (ship != NULL) {
        dEvt_control_c* event = g_dComIfG_gameInfo.play.getEvent();
        event->mPtTalk = event->getPId(ship);
    }
    dComIfGp_getPEvtManager()->cutEnd(mStaffId);
}

/* 00007878-000078E0       .text cutMiniGameWaitStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWaitStart() {
    if (g_regHIO.mChild[11].mShortRegs[3] == 0) {
        dCamera_c* camera = (dCamera_c*)dComIfGp_getCamera(0);
        camera->Stop();
        camera->SetTrimSize(1);
    }
}

/* 000078E0-00007914       .text cutMiniGameWaitProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGameWaitProc() {
    dComIfGp_getPEvtManager()->cutEnd(mStaffId);
}

/* 00004754-000048BC       .text initCam__10daNpc_So_cFv */
void daNpc_So_c::initCam() {
    if (m0BDE != 0) {
        return;
    }
    m0BDE = 1;

    dCamera_c* cam = dCam_getBody();
    cam->Stop();
    cam->SetTrimSize(1);
    cam->SetTypeForce("BoatBattle", this);

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    daShip_c* ship = dComIfGp_getShipActor();

    s16 angle;
    cXyz basePos;
    if (ship != NULL) {
        angle = ship->shape_angle.y + g_regHIO.mChild[11].mShortRegs[24];
        basePos = ship->current.pos;
    } else {
        angle = player->shape_angle.y;
        basePos = player->current.pos;
    }

    mDoMtx_stack_c::YrotS(angle);
    cXyz offset;
    offset.x = m_heapsize.m0034 + g_regHIO.mChild[11].mFloatRegs[7];
    offset.y = m_heapsize.m0038 + g_regHIO.mChild[11].mFloatRegs[8];
    offset.z = m_heapsize.m003C + g_regHIO.mChild[11].mFloatRegs[9];

    mDoMtx_stack_c::multVec(&offset, &mBCC);
    mBCC += basePos;
    mBCC.y += m_heapsize.m0040 + g_regHIO.mChild[11].mFloatRegs[10];

    mBC0 = basePos;
    mBC0.y += m_heapsize.m0044 + g_regHIO.mChild[11].mFloatRegs[11];

    cam->Set(mBCC, mBC0);
}

/* 000048BC-00004A78       .text moveCam__10daNpc_So_cFv */
void daNpc_So_c::moveCam() {
    dCamera_c* cam = dCam_getBody();

    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    daShip_c* ship = dComIfGp_getShipActor();

    s16 angle;
    cXyz basePos;
    if (ship != NULL) {
        angle = ship->shape_angle.y + g_regHIO.mChild[11].mShortRegs[24];
        basePos = ship->current.pos;
    } else {
        angle = player->shape_angle.y;
        basePos = player->current.pos;
    }

    mDoMtx_stack_c::YrotS(angle);
    cXyz offset;
    offset.x = m_heapsize.m0034 + g_regHIO.mChild[11].mFloatRegs[7];
    offset.y = m_heapsize.m0038 + g_regHIO.mChild[11].mFloatRegs[8];
    offset.z = m_heapsize.m003C + g_regHIO.mChild[11].mFloatRegs[9];

    cXyz target;
    mDoMtx_stack_c::multVec(&offset, &target);
    target += basePos;
    target.y += m_heapsize.m0040 + g_regHIO.mChild[11].mFloatRegs[10];
    cLib_addCalcPos2(&mBCC, target, 0.5f, 10.0f);

    target = basePos;
    target.y += m_heapsize.m0044 + g_regHIO.mChild[11].mFloatRegs[11];
    cLib_addCalcPos2(&mBC0, target, 0.5f, 10.0f);

    cam->Set(mBCC, mBC0);
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
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    daShip_c* ship = dComIfGp_getShipActor();
    
    player->mDemo.setOriginalDemoType();
    player->mDemo.setParam0(3);
    player->mDemo.setDemoMode(6);
    player->mDemo.setParam0(1);
    
    s16 angle = player->shape_angle.y + g_regHIO.mChild[11].mShortRegs[10] - 0x4000;
    current.pos = player->current.pos;
    
    current.pos.x += 300.0f * JMASSin(angle);
    current.pos.z += 300.0f * JMASCos(angle);
    
    dComIfGp_getPEvtManager()->cutEnd(mStaffId);
}

/* 00007AC0-00007AE0       .text cutMiniGamePlUpStart__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlUpStart() {
    m0A9C = g_regHIO.mChild[11].mShortRegs[22] + 10;
    m0BDE = 0;
}

/* 00007AE0-00007C24       .text cutMiniGamePlUpProc__10daNpc_So_cFv */
void daNpc_So_c::cutMiniGamePlUpProc() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
    player->mDemo.setOriginalDemoType();
    player->mDemo.setParam0(14);
    player->mDemo.setDemoMode(1);
    player->mDemo.setParam0(1);
    
    if (cLib_calcTimer(&m0A9C) == 0) {
        dComIfGp_getPEvtManager()->cutEnd(mStaffId);
    }
}
