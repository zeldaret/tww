/**
 * d_a_npc_tc.cpp
 * NPC - Tingle, Ankle, David Jr. & Knuckle
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_tc.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_tc.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/actor/d_a_obj_smplbg.h"
#include "d/d_lib.h"

class daNpc_Tc_HIO_c : public mDoHIO_entry_c{
public:
    daNpc_Tc_HIO_c();
    virtual ~daNpc_Tc_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ dNpc_HIO_c mNpc;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ u8 field_0x34;
    /* 0x35 */ u8 field_0x35[0x38 - 0x35];
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ bool field_0x44;
    /* 0x45 */ u8 field_0x45[0x48 - 0x45];
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ cXyz field_0x60;
    /* 0x6C */ cXyz field_0x6C;
    /* 0x78 */ s16 field_0x78;
    /* 0x7A */ s16 field_0x7A;
    /* 0x7C */ u8 field_0x7C;
    /* 0x7D */ u8 field_0x7D;
    /* 0x7E */ u8 field_0x7E;
    /* 0x7F */ u8 field_0x7F[8];
    /* 0x87 */ u8 field_0x87[8];
    /* 0x8F */ u8 field_0x8F;
    /* 0x90 */ u8 field_0x90;
    /* 0x91 */ u8 field_0x91;
    /* 0x92 */ u8 field_0x92;
    /* 0x93 */ u8 field_0x93;
    /* 0x94 */ f32 field_0x94;
    /* 0x98 */ f32 field_0x98;
    /* 0x9C */ f32 field_0x9C;
    /* 0xA0 */ f32 field_0xA0;
    /* 0xA4 */ f32 field_0xA4;
    /* 0xA8 */ f32 field_0xA8;
    /* 0xAC */ f32 field_0xAC;
    /* 0xB0 */ f32 field_0xB0;
    /* 0xB4 */ f32 field_0xB4;
    /* 0xB8 */ f32 field_0xB8;
    /* 0xBC */ f32 field_0xBC;
    /* 0xC0 */ f32 field_0xC0;
    /* 0xC4 */ f32 field_0xC4;
    /* 0xC8 */ f32 field_0xC8;
    /* 0xCC */ f32 field_0xCC;
    /* 0xD0 */ f32 field_0xD0;
    /* 0xD4 */ f32 field_0xD4;
    /* 0xD8 */ f32 field_0xD8;
    /* 0xDC */ f32 field_0xDC;
    /* 0xE0 */ f32 field_0xE0;
    /* 0xE4 */ f32 field_0xE4;
    /* 0xE8 */ f32 field_0xE8;
    /* 0xEC */ f32 field_0xEC;
    /* 0xF0 */ f32 field_0xF0;
};  // Size: 0xF4

static daNpc_Tc_HIO_c l_HIO;

/* 000000EC-00000394       .text __ct__14daNpc_Tc_HIO_cFv */
daNpc_Tc_HIO_c::daNpc_Tc_HIO_c() {
    field_0x60.set(-100.0f, 1700.0f, -50.0f);
    field_0x6C.set(100.0f, 1700.0f, 50.0f);

    field_0x7A = 0;
    field_0x78 = -0x8000;

    field_0x7C = dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80);
    field_0x7D = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A20);
    field_0x7E = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1708);

    for (int i = 0; i < 8; i++) {
        field_0x87[i] = dComIfGs_isGetCollectMap(i+1);
    }

    for (int i = 0; i < 8; i++) {
        field_0x7F[i] = dComIfGs_isCollectMapTriforce(i+1);
    }

    field_0x8F = dComIfGs_isStageTbox(3, 0xf);
    field_0x90 = dComIfGs_isStageTbox(4, 0xf);
    field_0x91 = dComIfGs_isStageTbox(5, 0xf);
    field_0x92 = dComIfGs_isStageTbox(7, 0xf);
    field_0x93 = dComIfGs_isStageTbox(6, 0xf);// weird?


    mNpc.m04 = -20.0;
    mNpc.mMaxHeadX = 0x1FFE;
    mNpc.mMaxBackboneX = 10000;
    mNpc.mMaxHeadY = 0;
    mNpc.mMaxBackboneY = 0x1C70;
    mNpc.mMinHeadX = -0x9C4;
    mNpc.mMinBackboneX = -10000;
    mNpc.mMinHeadY = 0;
    mNpc.mMinBackboneY = -0x1C70;
    mNpc.mMaxTurnStep = 3000;
    mNpc.mMaxHeadTurnVel = 0x800;
    mNpc.mAttnYOffset = 65.0;
    mNpc.mMaxAttnAngleY = 0x4000;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 400.0;
    
    field_0x2C = 900.0f;
    field_0x30 = 400.0f;
    field_0x34 = 0;
    field_0x38 = 20.0f;
    field_0x40 = 14.0f;
    field_0x3C = -2.5f;
    field_0x48 = -25.0f;
    field_0x50 = 8.0f;
    field_0x4C = -2.5f;
    field_0x54 = 0.35f;
    field_0x58 = 4.0f;
    field_0x5C = 8.0f;
    field_0x94 = 0.0f;
    field_0x98 = 8.0f;
    field_0x9C = 8.0f;
    field_0xA0 = 5.0f;
    field_0xA4 = 8.0f;
    field_0xA8 = 4.0f;
    field_0xAC = 0.0f;
    field_0xB0 = 6.0f;
    field_0xB4 = 6.0f;
    field_0xB8 = 0.0f;
    field_0xBC = 8.0f;
    field_0xC0 = 8.0f;
    field_0xC4 = 8.0f;
    field_0xC8 = 8.0f;
    field_0xCC = 8.0f;
    field_0xD0 = 8.0f;
    field_0xD4 = 8.0f;
    field_0xD8 = 8.0f;
    field_0xDC = 8.0f;
    field_0xE0 = 8.0f;
    field_0xE4 = 8.0f;
    field_0xE8 = 8.0f;
    field_0xF0 = 8.0f;
    field_0xEC = 8.0f;

    /* Nonmatching */
}

/* 000003D0-0000059C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {

    /* Nonmatching */
}

/* 0000059C-000005C8       .text searchTower_CB__FPvPv */
static void* searchTower_CB(void* i_actor, void* i_this) {
    return static_cast<daNpc_Tc_c*>(i_this)->_searchTower(static_cast<fopAc_ac_c*>(i_actor));
    /* Nonmatching */
}

/* 000005C8-00000630       .text _searchTower__10daNpc_Tc_cFP10fopAc_ac_c */
fopAc_ac_c* daNpc_Tc_c::_searchTower(fopAc_ac_c* i_actor) {
    if (fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == PROC_Obj_Smplbg && ((daObjSmplbg::Act_c*)i_actor)->prm_get_type() == 0) {
        return i_actor;
    }
    return NULL;
    /* Nonmatching */
}

/* 00000630-00000744       .text initTexPatternAnm__10daNpc_Tc_cFb */
BOOL daNpc_Tc_c::initTexPatternAnm(bool) {
    /* Nonmatching */
}

/* 00000744-000007D0       .text playTexPatternAnm__10daNpc_Tc_cFv */
void daNpc_Tc_c::playTexPatternAnm() {
    /* Nonmatching */
}

/* 000007D0-00000948       .text smoke_set__10daNpc_Tc_cFfffff */
void daNpc_Tc_c::smoke_set(f32, f32, f32, f32, f32) {
    /* Nonmatching */
}

/* 00000948-00001168       .text setAnm__10daNpc_Tc_cFv */
void daNpc_Tc_c::setAnm() {
    /* Nonmatching */
}

/* 00001168-000011C0       .text setTexAnm__10daNpc_Tc_cFv */
void daNpc_Tc_c::setTexAnm() {
    /* Nonmatching */
}

/* 000011C0-0000136C       .text chkAttention__10daNpc_Tc_cF4cXyzs */
void daNpc_Tc_c::chkAttention(cXyz, s16) {
    /* Nonmatching */
}

/* 0000136C-00001424       .text eventOrder__10daNpc_Tc_cFv */
void daNpc_Tc_c::eventOrder() {
    /* Nonmatching */
}

/* 00001424-00001470       .text checkOrder__10daNpc_Tc_cFv */
void daNpc_Tc_c::checkOrder() {
    /* Nonmatching */
}

/* 00001470-000014FC       .text existTcMonument__10daNpc_Tc_cFv */
void daNpc_Tc_c::existTcMonument() {
    /* Nonmatching */
}

/* 000014FC-0000156C       .text anmAtr__10daNpc_Tc_cFUs */
void daNpc_Tc_c::anmAtr(u16) {
    /* Nonmatching */
}

/* 0000156C-00001618       .text stopTower__10daNpc_Tc_cFv */
void daNpc_Tc_c::stopTower() {
    /* Nonmatching */
}

/* 00001618-000017A4       .text startTower__10daNpc_Tc_cFv */
void daNpc_Tc_c::startTower() {
    /* Nonmatching */
}

/* 000017A4-00001900       .text next_msgStatusBlue__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusBlue(u32*) {
    /* Nonmatching */
}

/* 00001900-00001AEC       .text next_msgStatusNormal__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusNormal(u32*) {
    /* Nonmatching */
}

/* 00001AEC-00001B64       .text next_msgStatus__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatus(u32*) {
    /* Nonmatching */
}

/* 00001B64-00001B88       .text setFirstMsg__10daNpc_Tc_cFPbUlUl */
void daNpc_Tc_c::setFirstMsg(bool*, u32, u32) {
    /* Nonmatching */
}

/* 00001B88-00001BE0       .text getMsgNormal__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgNormal() {
    /* Nonmatching */
}

/* 00001BE0-00001BE8       .text getMsgBlue__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgBlue() {
    /* Nonmatching */
}

/* 00001BE8-00001C74       .text getMsg__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsg() {
    /* Nonmatching */
}

/* 00001C74-00001C98       .text getArg__10daNpc_Tc_cFv */
void daNpc_Tc_c::getArg() {
    /* Nonmatching */
}

/* 00001C98-0000202C       .text createInit__10daNpc_Tc_cFv */
void daNpc_Tc_c::createInit() {
    /* Nonmatching */
}

/* 0000202C-000020C4       .text searchStoolPos__10daNpc_Tc_cFPvPv */
void daNpc_Tc_c::searchStoolPos(void*, void*) {
    /* Nonmatching */
}

/* 000020C4-00002148       .text setAttention__10daNpc_Tc_cFv */
void daNpc_Tc_c::setAttention() {
    /* Nonmatching */
}

/* 00002148-00002220       .text calcMove__10daNpc_Tc_cFv */
void daNpc_Tc_c::calcMove() {
    /* Nonmatching */
}

/* 00002220-000024C4       .text lookBack__10daNpc_Tc_cFv */
void daNpc_Tc_c::lookBack() {
    /* Nonmatching */
}

/* 000024C4-00002594       .text statusWait__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWait() {
    if (field_0x7FC == 2 || field_0x7FC == 1) {
        JUT_ASSERT(0x601, m_tower_actor != NULL);

        if (!m_tower_actor->isStop()) {
            field_0x7F9 = 0x14;
        } else {
            field_0x7F9 = 0x13;
        }
    }

    if (field_0x7E9) {
        field_0x6CF = 3;
    } else if (field_0x7E8) {
        field_0x7FB = 2;
    }
    /* Nonmatching */
}

/* 00002594-000026E4       .text statusSit__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusSit() {
    mSmokeCallBack.end();
    calc_sitpos();
    current.pos.set(field_0x7AC);
    gravity = 0.0f;
    
    if(field_0x7F9 != 6) {
        if(dLib_checkPlayerInCircle(current.pos, l_HIO.field_0x2C, 100.0f)) {
            if (!field_0x7F2) {
                field_0x7F2 = true;
                field_0x7FB = 3;
                field_0x6CF = 10;
                return;
            }
            field_0x7F9 = 6;
        }
    }

    if(mpMorf->isStop() && field_0x7F9 == 6) {
        speedF = l_HIO.field_0x38;
        speed.y = l_HIO.field_0x40;
        gravity = l_HIO.field_0x3C;
        field_0x7F9 = 7;
        field_0x6CF = 4;
    }
    /* Nonmatching */
}

/* 000026E4-00002798       .text statusJump__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusJump() {
    if (speed.y <= 0.0f && field_0x7F9 == 7) {
        field_0x7F9 = 8;
    }

    if (mObjAcch.ChkGroundHit() && field_0x7F9 == 8) {
        speedF = 0.0f;
        field_0x7F9 = 9;
        field_0x7F3 = 0x33;
        return;
    }

    if (cLib_calcTimer(&field_0x7F3) == 0 && field_0x7F9 == 9) {
        field_0x7F9 = 5;
        field_0x6CF = 5;
    }
    /* Nonmatching */
}

/* 00002798-000029B0       .text statusWalkToJail__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWalkToJail() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    
    s16 angle = cLib_targetAngleY(&current.pos, &player->current.pos);
    if (mObjAcch.ChkWallHit()) {
        if (field_0x7E9) {
            field_0x79C = 0.0f;
            speedF = 0.0f;

            if (!field_0x7F1 || l_HIO.field_0x44 != 0) {
                field_0x7F9 = 2;
                dComIfGp_event_reset();
                field_0x6CF = 0xC;
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B40) == 0) {
                    if (dComIfGs_getClearCount() != 0) {
                        field_0x7FB = 6;
                    } else {
                        field_0x7FB = 5;
                    }
                } else {
                    field_0x7FB = 7;
                }

                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B40);
                field_0x7F1 = true;
                return;

            }
            field_0x6CF = 6;
        } else if (field_0x7E8) {
            field_0x7FB = 2;
        }
    }

    if (mObjAcch.ChkWallHit() && std::fabsf(cM_scos(angle)) > 0.9f) {
        field_0x79C = 0.0f;
        if (speedF == 0.0f) {
            field_0x7F9 = 1;
        }
    } else {
        field_0x7F9 = 5;
        field_0x79C = l_HIO.field_0x58;
        if (speedF == 0.0f) {
            speedF = l_HIO.field_0x5C;
        }
    }
    if (mObjAcch.ChkWallHit()) {
        if(!dLib_checkPlayerInCircle(current.pos, l_HIO.field_0x30, 100.0f)) {
            field_0x6CF = 8;
        }
    }
    /* Nonmatching */
}

/* 000029B0-00002A20       .text statusTalkNearJail__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusTalkNearJail() {
    field_0x79C = 0.0f;
    speedF = 0.0f;
    if (talk(1) == 0x12) {
        field_0x6CF = 7;
        dComIfGp_event_reset();
        field_0x7E9 = false;
    }
    /* Nonmatching */
}

/* 00002A20-00002BD4       .text statusWaitNearJail__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWaitNearJail() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    
    s16 angle = cLib_targetAngleY(&current.pos, &player->current.pos);
    if (mObjAcch.ChkWallHit()) {
        if (field_0x7E9) {
            field_0x79C = 0.0f;
            speedF = 0.0f;

            if (!field_0x7F1 || l_HIO.field_0x44 != 0) {
                field_0x7F9 = 2;
                dComIfGp_event_reset();
                field_0x6CF = 0xC;
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B40) == 0) {
                    field_0x7FB = 5;
                } else {
                    field_0x7FB = 7;
                }

                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B40);
                field_0x7F1 = true;
                return;

            }
            field_0x6CF = 6;
        } else if (field_0x7E8) {
            field_0x7FB = 2;
        }
    }

    if (mObjAcch.ChkWallHit() && std::fabsf(cM_scos(angle)) > 0.9f) {
        field_0x79C = 0.0f;
        if (speedF == 0.0f) {
            field_0x7F9 = 1;
        }
    } else {
        field_0x7F9 = 5;
        field_0x79C = l_HIO.field_0x58;
        if (speedF == 0.0f) {
            speedF = l_HIO.field_0x5C;
        }
    }

    /* Nonmatching */
}

/* 00002BD4-00002D80       .text statusWalkToStool__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWalkToStool() {
    calc_sitpos();
    if(dLib_checkPlayerInCircle(current.pos, l_HIO.field_0x30, 100.0f)) {
        field_0x79C = 0.0f;
        if (speedF == 0.0f) {
            field_0x6CF = 5;
        }
        
    } else {
        field_0x780.set(field_0x7A0);
        cLib_targetAngleY(&current.pos, &field_0x7B8);
        cLib_addCalcPosXZ2(&current.pos, field_0x7B8, 0.1f, speedF);
        if((field_0x7B8 - current.pos).absXZ() < 5.0f) {
            field_0x79C = 0.0f;
            if (speedF == 0.0f) {
                field_0x7F9 = 1;
                field_0x6CF = 9;
            }
        } else {
            field_0x7F9 = 5;
            field_0x79C = l_HIO.field_0x58;   
        }
    }
    /* Nonmatching */
}

/* 00002D80-00002F94       .text statusSitToStool__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusSitToStool() {
    calc_sitpos();
    cLib_addCalcAngleS2(&current.angle.y, field_0x790.y, 4, 0x800);

    if (std::fabsf(field_0x790.y - current.angle.y) < 16.0f) {
        if (speed.y == 0.0f && mObjAcch.ChkGroundHit()) {
            speed.y = 22.0f;
            gravity = -2.5f;
        }

        if (speed.y < 0.0f) {
            field_0x7F9 = 3;
        }

        if (speed.y < 0.0f && current.pos.y < field_0x7AC.y) {
            gravity = 0.0f;
            speed.y = 0.0f;
            current.pos.y = field_0x7AC.y;
        }

        cLib_addCalcPosXZ2(&current.pos, field_0x7AC, 0.1f, 4.0f);
        f32 diff = (field_0x7AC - current.pos).absXZ();
        if (current.pos.y == field_0x7AC.y && diff < 5.0f) {
            field_0x6E0.set(current.pos);
            field_0x6EC = current.angle;
            smoke_set(2.0f, 0.25f, 0.0f, 5.0f, 20.0f);
            field_0x6CF = 2;
        }
    }
    /* Nonmatching */
}

/* 00002F94-00003028       .text statusTalk__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusTalk() {
    if(talk(1) != 0x12) {
        return;
    }
    switch(field_0x7FC) {
        case 0:
            startTower();
            field_0x7F9 = 0x13;
        case 1:
            startTower();
            break;
        default:
            field_0x7F9 = 1;
            field_0x6CF = 1;
            dComIfGp_event_reset();
            field_0x7E9 = false;
            break; // m2c 
    }



    /* Nonmatching */
}

/* 00003028-00003088       .text statusPayRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusPayRupee() {
    if(talk(1) == 0x12) {
        dComIfGp_event_reset();
        field_0x7FB = 9;
        field_0x6CF = 0xE;
    }
    /* Nonmatching */
}

/* 00003088-000030F8       .text statusDemoPayRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoPayRupee() {
    if(dComIfGp_evmng_endCheck("TC_PAY_RUPEE")) {
        dComIfGp_event_reset();
        field_0x7FB = 1;
        field_0x6CF = 3;
    }
    /* Nonmatching */
}

/* 000030F8-00003158       .text statusGetRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusGetRupee() {
    if(talk(1) == 0x12) {
        dComIfGp_event_reset();
        field_0x7FB = 8;
        field_0x6CF = 16;
    }
    /* Nonmatching */
}

/* 00003158-000031CC       .text statusDemoGetRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoGetRupee() {
    if(dComIfGp_evmng_endCheck("TC_GET_RUPEE")) {
        field_0x812 = true;
        dComIfGp_event_reset();
        field_0x7FB = 1;
        field_0x6CF = 3;
    }
    /* Nonmatching */
}

/* 000031CC-0000322C       .text statusMonumentComplete__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusMonumentComplete() {
    if(talk(1) == 0x12) {
        dComIfGp_event_reset();
        field_0x7FB = 8;
        field_0x6CF = 18;
    }
    /* Nonmatching */
}

/* 0000322C-000032A0       .text statusDemoMonumentComplete__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoMonumentComplete() {
    if(dComIfGp_evmng_endCheck("TC_GET_RUPEE")) {
        field_0x813 = true;
        dComIfGp_event_reset();
        field_0x7FB = 1;
        field_0x6CF = 3;
    }
    /* Nonmatching */
}

/* 000032A0-00003308       .text statusDemoJump__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoJump() {
    if(dComIfGp_evmng_endCheck("TC_JUMP_DEMO")) {
        field_0x6CF = 5;
        dComIfGp_event_reset();
    }
    /* Nonmatching */
}

/* 00003308-00003384       .text statusDemoRescue__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoRescue() {
    //meow 
    if(dComIfGp_evmng_endCheck("TC_RESCUE")) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B80);
        dComIfGp_event_reset();
        fopAcM_delete(this);
    }
    /* Nonmatching */
}

/* 00003384-00003430       .text statusDemoTalk__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoTalk() {
    if (dComIfGp_evmng_endCheck("TC_TALK_NEAR_JAIL") || dComIfGp_evmng_endCheck("TC_TALK_NEAR_JAIL_S") || dComIfGp_evmng_endCheck("TC_TALK_NEAR_JAIL2")) {
        field_0x6CF = 7;
        dComIfGp_event_reset();
        field_0x7E9 = false;
    }
    /* Nonmatching */
}

/* 00003430-00003610       .text help_action__10daNpc_Tc_cFPv */
void daNpc_Tc_c::help_action(void*) {
    /* Nonmatching */
}

/* 00003610-0000374C       .text wait_action__10daNpc_Tc_cFPv */
void daNpc_Tc_c::wait_action(void*) {
    /* Nonmatching */
}

/* 0000374C-00003830       .text calc_sitpos__10daNpc_Tc_cFv */
void daNpc_Tc_c::calc_sitpos() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    cXyz temp(0.0f, 80.0f, -25.0f);
    cXyz temp3(0.0f, 0.0f, 00.0f);

    cXyz temp2(0.0f, 0.0f, -60.0f);
    cXyz unused(0.0f, 0.0f, 0.0f);
    s16 angle = cLib_targetAngleY(&player->current.pos, &field_0x7A0);
    mDoMtx_stack_c::transS(field_0x7A0);
    mDoMtx_stack_c::YrotM(angle);
    mDoMtx_stack_c::multVec(&temp, &field_0x7AC);
    mDoMtx_stack_c::multVec(&temp2, &field_0x7B8);
    /* Nonmatching */
}

/* 00003830-000038A0       .text set_mtx__10daNpc_Tc_cFv */
void daNpc_Tc_c::set_mtx() {
    J3DModel* model = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    /* Nonmatching */
}

/* 000038A0-00003A40       .text _draw__10daNpc_Tc_cFv */
BOOL daNpc_Tc_c::_draw() {


    static const s32 a_bmt_tbl[5] = {
        -1,
        TC_BMT_TCB,
        TC_BMT_TCC,
        TC_BMT_TCA,
        -1
    };

    static const u8 a_snap_tbl[] = {
        DSNAP_TYPE_UNK79,
        DSNAP_TYPE_UNK7A,
        DSNAP_TYPE_UNK7C,
        DSNAP_TYPE_UNK7B,
        DSNAP_TYPE_UNK79,
    };

    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* pModelData;

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBtpAnm.entry(pModelData, field_0x760);

    if (a_bmt_tbl[field_0x7FC] != -1) {
        J3DMaterialTable* bmt = (J3DMaterialTable*)dComIfG_getObjectRes("Tc", a_bmt_tbl[field_0x7FC]);
        mpMorf->entryDL(bmt);
    } else {
        mpMorf->entryDL();
    }
    mBtpAnm.remove(pModelData);


    cXyz shadowPos(current.pos.x, current.pos.y + 150.0f + REG8_F(12), current.pos.z);
    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, mpMorf->getModel(), &shadowPos, REG8_F(13) + 800.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );


    dSnap_RegistFig(a_snap_tbl[field_0x7FC], this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);

    if (l_HIO.field_0x34 != 0) {
        mEventCut.getAttnPos();
    }
    return TRUE;
    /* Nonmatching */
}

/* 00003A40-00003BE0       .text setTower__10daNpc_Tc_cFv */
void daNpc_Tc_c::setTower() {
    m_tower_actor = (daObjSmplbg::Act_c*)fopAcM_Search(&searchTower_CB, this);
    JUT_ASSERT(0x8E9, m_tower_actor != NULL);
    cXyz temp;
    s16 temp2;
    switch(field_0x7FC) {
        case 2:
            temp = l_HIO.field_0x60;
            temp2 = l_HIO.field_0x7A;
            break;
        case 1:
            temp = l_HIO.field_0x6C;
            temp2 = l_HIO.field_0x78;
            break;
        
    }

    switch(field_0x7FC) {
        case 1:
        case 2:
            mDoMtx_stack_c::transS(m_tower_actor->current.pos);
            mDoMtx_stack_c::ZXYrotM(m_tower_actor->shape_angle);
            mDoMtx_stack_c::multVec(&temp, &current.pos);

            s16 temp3 = m_tower_actor->shape_angle.y + temp2;
            if (m_tower_actor->field_0x2D8 != 0) {
                if (field_0x7F9 == 0x13 || field_0x7F9 == 0x14) {
                    cLib_addCalcAngleS2(&current.angle.y, temp3, 4, 0x800);
                }
            } else {
                current.angle.y = temp3;
            }
            break;
    }

    /* Nonmatching */
}

/* 00003BE0-00003E90       .text _execute__10daNpc_Tc_cFv */
BOOL daNpc_Tc_c::_execute() {
    u32 mtrlSndId;
    if (field_0x7FC == 2 || field_0x7FC == 1 || field_0x7FC == 0) { // is this an inline?
        setTower();
    }

    m_jnt.setParam(
    l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY, l_HIO.mNpc.mMinBackboneX,
    l_HIO.mNpc.mMinBackboneY, l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY,
    l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY, l_HIO.mNpc.mMaxTurnStep);

    playTexPatternAnm();

    s8 roomNo = fopAcM_GetRoomNo(this);
    if(mObjAcch.ChkGroundHit()) {
        mtrlSndId = dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd);
    } else {
        mtrlSndId = 0;
    }

    field_0x798 = mpMorf->play(&eyePos, mtrlSndId, dComIfGp_getReverb(roomNo));
    mpMorf->calc();
    checkOrder();

    (this->*mCurrActionFunc)(NULL);

    if (field_0x6CF != 1) {
        if (!mEventCut.cutProc()) {
            cutProc();
        } else {
            if (mEventCut.getNowCut() != -1) {
                switch(mEventCut.getNowCut()) {
                    case 2:
                    case 4:
                        if (mEventCut.getMoveSpeed() == 0.0f) {
                            field_0x7F9 = 1;
                        } else {
                            field_0x7F9 = 5;
                        }
                        break;
                    case 0:
                        field_0x7F9 = 1;
                        break;
   
                }
            } else {
                field_0x7F9 = 1;
            }
        }
    }
    dBgS* bgs = dComIfG_Bgsp();

    if (dComIfGp_event_runCheck() == FALSE) {
        mEventCut.setAttnNoTurnFlag(false);
        mEventCut.setAttnFlag(false);
    }
    eventOrder();
    setAnm();
    setTexAnm();
    if (field_0x6CF != 8) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    cXyz tempPos = current.pos;

    mObjAcch.CrrPos(*bgs);

    field_0x7C4 = current.pos - tempPos;

    tevStr.mRoomNo = bgs->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = bgs->GetPolyColor(mObjAcch.m_gnd);


    set_mtx();

    if (field_0x7FC == 4) {
        if (field_0x6CF == 0xb) {
            setCollision(60.0f, 150.0f);
        }
    } else {
        setCollision(60.0f, 150.0f);
    }
    return TRUE;

    /* Nonmatching */
}

/* 00003E90-00003F1C       .text _delete__10daNpc_Tc_cFv */
BOOL daNpc_Tc_c::_delete() {
    dComIfG_resDelete(&mPhs, "Tc");
    mSmokeCallBack.remove();
    field_0x714.remove();
    field_0x728.remove();
    if(heap != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
    /* Nonmatching */
}

/* 00003F1C-00003F3C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*i_this) {
    return static_cast<daNpc_Tc_c*>(i_this)->_createHeap();
    /* Nonmatching */
}

/* 00003F3C-00003FC0       .text isCreate__10daNpc_Tc_cFv */
bool daNpc_Tc_c::isCreate() {
    switch(field_0x7FC) {
        case 3:
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1708)) {
                return false;
            }
            break;

        case 0:
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80)) {
                return false;
            }
            break;
    }
    return true;
    /* Nonmatching */
}

daNpc_Tc_c::daNpc_Tc_c() {}

/* 00003FC0-00004090       .text _create__10daNpc_Tc_cFv */
cPhs_State daNpc_Tc_c::_create() {
    fopAcM_SetupActor(this, daNpc_Tc_c);
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, "Tc");
    if(phase_state == cPhs_COMPLEATE_e) {
        getArg();

        if(!isCreate()) {
            return cPhs_ERROR_e;
        }

        if(!fopAcM_entrySolidHeap(this, createHeap_CB, 0x1C80)) {
            return cPhs_ERROR_e;
        }

        cullMtx = mpMorf->getModel()->getBaseTRMtx();
        createInit();
    }
    return phase_state;

    /* Nonmatching */
}

/* 000045D0-000047DC       .text _createHeap__10daNpc_Tc_cFv */
BOOL daNpc_Tc_c::_createHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Tc", TC_BDL_TC));
    JUT_ASSERT(0xA30, modelData != NULL);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL, NULL,
        J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x15021222
    );

    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    m_jnt.setHeadJntNum(2);
    JUT_ASSERT(0xA40, m_jnt.getHeadJntNum() >= 0);
    m_jnt.setBackboneJntNum(1);
    JUT_ASSERT(0xA42, m_jnt.getBackboneJntNum() >= 0);
    modelData->getJointNodePointer(2)->setCallBack(nodeCallBack);
    modelData->getJointNodePointer(1)->setCallBack(nodeCallBack);
    mpMorf->getModel()->setUserArea(reinterpret_cast<u32>(this));

    field_0x7F6 = 0;
    if (!initTexPatternAnm(false)) {
        return FALSE;
    }
    return TRUE;
    /* Nonmatching */
}

/* 000047DC-000047FC       .text daNpc_Tc_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Tc_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Tc_c*)i_this)->_create();
}

/* 000047FC-0000481C       .text daNpc_Tc_Delete__FP10daNpc_Tc_c */
static BOOL daNpc_Tc_Delete(daNpc_Tc_c* i_this) {
    return ((daNpc_Tc_c*)i_this)->_delete();
}

/* 0000481C-0000483C       .text daNpc_Tc_Execute__FP10daNpc_Tc_c */
static BOOL daNpc_Tc_Execute(daNpc_Tc_c* i_this) {
    return ((daNpc_Tc_c*)i_this)->_execute();
}

/* 0000483C-0000485C       .text daNpc_Tc_Draw__FP10daNpc_Tc_c */
static BOOL daNpc_Tc_Draw(daNpc_Tc_c* i_this) {
    return ((daNpc_Tc_c*)i_this)->_draw();
}

/* 0000485C-00004864       .text daNpc_Tc_IsDelete__FP10daNpc_Tc_c */
static BOOL daNpc_Tc_IsDelete(daNpc_Tc_c*) {
    return TRUE;
}

/* 00004BAC-00004E6C       .text next_msgStatusNormal2__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusNormal2(u32*) {
    /* Nonmatching */
}

/* 00004E6C-00004F68       .text getMsgNormal2__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgNormal2() {
    /* Nonmatching */
}

/* 00004F68-00004FD8       .text setRupeeSizeMsg__10daNpc_Tc_cFv */
void daNpc_Tc_c::setRupeeSizeMsg() {
    /* Nonmatching */
}

/* 00004FD8-00005054       .text existUnknownCollectMap__10daNpc_Tc_cFv */
void daNpc_Tc_c::existUnknownCollectMap() {
    /* Nonmatching */
}

/* 00005054-000050DC       .text analysisCollectMap__10daNpc_Tc_cFv */
void daNpc_Tc_c::analysisCollectMap() {
    /* Nonmatching */
}

/* 000050DC-00005158       .text existKnownCollectMap__10daNpc_Tc_cFv */
void daNpc_Tc_c::existKnownCollectMap() {
    /* Nonmatching */
}

/* 00005158-000053D4       .text next_msgStatusWhite__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusWhite(u32*) {
    /* Nonmatching */
}

/* 000053D4-00005498       .text getMsgWhite__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgWhite() {
    /* Nonmatching */
}

/* 00005498-00005720       .text next_msgStatusRed__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusRed(u32*) {
    /* Nonmatching */
}

/* 00005720-00005730       .text setFinishMsg__10daNpc_Tc_cFv */
void daNpc_Tc_c::setFinishMsg() {
    /* Nonmatching */
}

/* 00005730-00005944       .text getMsgRed__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgRed() {
    /* Nonmatching */
}

/* 00005944-000059A8       .text checkMonumentFee__10daNpc_Tc_cFUsUs */
void daNpc_Tc_c::checkMonumentFee(u16, u16) {
    /* Nonmatching */
}

/* 000059A8-00005A50       .text checkAllMonumentFee__10daNpc_Tc_cFv */
void daNpc_Tc_c::checkAllMonumentFee() {
    /* Nonmatching */
}

/* 00005A50-00005B10       .text checkAllMonumentPay__10daNpc_Tc_cFv */
void daNpc_Tc_c::checkAllMonumentPay() {
    /* Nonmatching */
}

/* 00005B10-00005B98       .text checkMonumentPay__10daNpc_Tc_cFUsUs */
void daNpc_Tc_c::checkMonumentPay(u16, u16) {
    /* Nonmatching */
}

/* 00005C58-00005E60       .text cutProc__10daNpc_Tc_cFv */
void daNpc_Tc_c::cutProc() {
    /* Nonmatching */
}

/* 00005E60-00005E6C       .text cutSitToJumpStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutSitToJumpStart(int) {
    /* Nonmatching */
}

/* 00005E6C-00005FA4       .text cutSitToJumpProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutSitToJumpProc(int) {
    /* Nonmatching */
}

/* 00005FA4-00005FA8       .text cutPresentStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutPresentStart(int) {
    /* Nonmatching */
}

/* 00005FA8-00006174       .text cutPresentProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutPresentProc(int) {
    /* Nonmatching */
}

/* 00006174-000061F0       .text cutSetAnmStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutSetAnmStart(int) {
    /* Nonmatching */
}

/* 000061F0-000062A0       .text cutSetAnmProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutSetAnmProc(int) {
    /* Nonmatching */
}

/* 000062A0-000062D8       .text cutBackJumpStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutBackJumpStart(int) {
    /* Nonmatching */
}

/* 000062D8-000063BC       .text cutBackJumpProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutBackJumpProc(int) {
    /* Nonmatching */
}

/* 000063BC-000064C8       .text cutEffectStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutEffectStart(int) {
    /* Nonmatching */
}

/* 000064C8-000064F4       .text cutEffectProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutEffectProc(int) {
    /* Nonmatching */
}

/* 000064F4-00006564       .text cutDoorOpenStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorOpenStart(int) {
    /* Nonmatching */
}

/* 00006564-00006590       .text cutDoorOpenProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorOpenProc(int) {
    /* Nonmatching */
}

/* 00006590-00006600       .text cutDoorCloseStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorCloseStart(int) {
    /* Nonmatching */
}

/* 00006600-0000662C       .text cutDoorCloseProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorCloseProc(int) {
    /* Nonmatching */
}

/* 0000662C-0000669C       .text cutDoorClose2Start__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorClose2Start(int) {
    /* Nonmatching */
}

/* 0000669C-000066C8       .text cutDoorClose2Proc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutDoorClose2Proc(int) {
    /* Nonmatching */
}

/* 000066C8-000066E0       .text cutPayStart__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutPayStart(int) {
    /* Nonmatching */
}

/* 000066E0-0000670C       .text cutPayProc__10daNpc_Tc_cFi */
void daNpc_Tc_c::cutPayProc(int) {
    /* Nonmatching */
}

static actor_method_class l_daNpc_Tc_Method = {
    (process_method_func)daNpc_Tc_Create,
    (process_method_func)daNpc_Tc_Delete,
    (process_method_func)daNpc_Tc_Execute,
    (process_method_func)daNpc_Tc_IsDelete,
    (process_method_func)daNpc_Tc_Draw,
};

actor_process_profile_definition g_profile_NPC_TC = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_TC,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Tc_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_TC,
    /* Actor SubMtd */ &l_daNpc_Tc_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
