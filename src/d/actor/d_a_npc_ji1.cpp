/**
 * d_a_npc_ji1.cpp
 * NPC - Orca
 */

#include "d/actor/d_a_npc_ji1.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_tsubo.h"
#include "d/res/res_ji.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_snap.h"
#include "d/d_lib.h"
#include "f_op/f_op_msg.h"

#include "weak_data_1811.h" // IWYU pragma: keep
#include "weak_bss_936_to_1036.h" // IWYU pragma: keep

static void daNpc_Ji1_setHairAngle(daNpc_Ji1_c*);

static daNpc_Ji1_HIO_c l_HIO;

static fpc_ProcID l_msgId;
static msg_class* l_msg;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 60.0f,
        /* Height */ 170.0f,
    },
};

static dCcD_SrcCyl l_cyl2_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 60.0f,
        /* Height */ 200.0f,
    },
};

static dCcD_SrcCyl l_cylAt_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_BOMB,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {
        /* Center */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 150.0f,
        /* Height */ 100.0f,
    },
};

static dCcD_SrcCps l_cpsAt_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsPlayer_e | cCcD_AtSPrm_VsOther_e,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ 0,
        /* SrcGObjAt Spl     */ 0x01,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ 0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCpsS
    {
        /* Start  */ 0.0f, 0.0f, 0.0f,
        /* End    */ 0.0f, 0.0f, 0.0f,
        /* Radius */ 80.0f,
    },
};

/* 000000EC-00000380       .text __ct__15daNpc_Ji1_HIO_cFv */
daNpc_Ji1_HIO_c::daNpc_Ji1_HIO_c() {
    field_0x04 = -1;
    field_0x08 = 100.0f;
    field_0x0C = 7000;
    field_0x0E = 4000;
    field_0x10 = 9000;
    field_0x12 = 7000;                           
    field_0x14 = 5000;
    field_0x16 = 1;
    field_0x18 = 2000;
    field_0x1C = 0.0f;
    field_0x20 = 20.0f;
    field_0x24 = 20.0f;
    field_0x28 = 0;
    field_0x2C = 200.0f;
    field_0x30 = 0;
    field_0x34 = 150.0f;
    field_0x38 = 20.0f;
    field_0x3C = 90.0f;
    field_0x40 = 10.0f;
    field_0x44 = 2.0f;
    field_0x48 = 2.0f;
    field_0x4C = 1.25f;
    field_0x50 = 1.5f;
    field_0x54[0] = 9;
    field_0x54[1] = 9;
    field_0x54[2] = 9;
    field_0x54[3] = 2;
    field_0x54[4] = 2;
    field_0x54[5] = 2;
    field_0x60[0] = 100;
    field_0x60[1] = 300;
    field_0x60[2] = 500;
    field_0x60[3] = 1000;
    field_0x68 = 0;
    field_0x6C = 0.7;
    field_0x70 = 1.5;
    field_0x78 = 1.4;
    field_0x74 = 1.4;
    field_0x80 = 1.4;
    field_0x7C = 1.2;
    field_0x84 = 0.1;
    field_0x88 = 0xB;
    field_0x8A = 0x32;
    field_0x8C = 0x28;
    field_0x8E = 0x1e;
    field_0x90 = 0x14;
    field_0x92 = 0xf;
    field_0x94 = 10;
    field_0x96 = 0xB4;
    field_0x98 = 0x8C;
    field_0x9A = 100;
    field_0x9C = 0x50;
    field_0x9E = 0x3C;
    field_0xA0 = 0x32;
    field_0xA4 = 6.0f;
    field_0xA8 = 16.0f;
    field_0xAC = 70.0f;
    field_0xB0 = 10.0f;
    field_0xB4 = 1.0f;
    field_0xB8 = 0;
    field_0xBC = 0.25f;
    field_0xC0 = -5.0f;
    field_0xC4[0].x = 90.0;
    field_0xC4[0].y = 5.0;
    field_0xC4[0].z = 30.0;
    field_0xC4[1].x = 90.0;
    field_0xC4[1].y = 5.0;
    field_0xC4[1].z = -30.0;
    field_0xC4[2].x = -20.0;
    field_0xC4[2].y = -20.0;
    field_0xC4[2].z = 0.0;
    field_0xE8 = 0xC800;
    field_0xEA = 0x3800;
    field_0xEC = 0xC600;
    field_0xEE = 0x3A00;
    field_0xF0 = 0xC600;
    field_0xF2 = 0x3A00;
    field_0xF4 = 0xfB00;
    field_0xF6 = 0x3800;
    field_0xF8 = 0xf600;
    field_0xFA = 0x3A00;
    field_0xFC = 0xf100;
    field_0xFE = 0x3A00;
}

/* 000003C0-000003E4       .text daNpc_Ji1_XyCheckCB__FPvi */
static s16 daNpc_Ji1_XyCheckCB(void*, int i_itemBtn) {
    return dComIfGp_getSelectItem(i_itemBtn) == BOKO_BELT ? TRUE : FALSE;
}

/* 000003E4-00000404       .text daJi1_CoHitCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
static void daJi1_CoHitCallback(fopAc_ac_c* i_this, dCcD_GObjInf*, fopAc_ac_c* actor, dCcD_GObjInf*) {
    if(actor == dComIfGp_getPlayer(0)) {
        static_cast<daNpc_Ji1_c*>(i_this)->field_0xC28 = 1;
    }
}

/* 00000404-00000424       .text daJi1_TgHitCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
static void daJi1_TgHitCallback(fopAc_ac_c* i_this, dCcD_GObjInf*, fopAc_ac_c* actor, dCcD_GObjInf*) {
    u32 temp = daPy_getPlayerActorClass()->getCutType();
    if(actor) {
        static_cast<daNpc_Ji1_c*>(i_this)->field_0xC24 = temp;
    }
}

/* 00000424-000004A0       .text daJi1_AtHitCallback__FP10fopAc_ac_cP12dCcD_GObjInfP10fopAc_ac_cP12dCcD_GObjInf */
static void daJi1_AtHitCallback(fopAc_ac_c* i_this, dCcD_GObjInf* param_2, fopAc_ac_c* actor, dCcD_GObjInf*) {
    if(fopAc_IsActor(actor)) {
        if(fpcM_GetName(actor) == PROC_PLAYER) {
            if(!param_2->ChkAtShieldHit()) {
                static_cast<daNpc_Ji1_c*>(i_this)->field_0xC3C++;
            }
            else {
                static_cast<daNpc_Ji1_c*>(i_this)->battleSubActionNockBackInit(0);
            }
        }
    }
}

/* 000004A0-000004CC       .text isGuardAnim__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::isGuardAnim() {
    if((field_0xD64 >= 8 && field_0xD64 <= 10) || field_0xD64 == 0xF) {
        return true;
    }

    return false;
}

/* 000004CC-000004F8       .text isAttackAnim__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::isAttackAnim() {
    if(field_0xD64 == 0x13 || field_0xD64 == 0x14 || field_0xD64 == 7) {
        return true;
    }

    return false;
}

/* 000004F8-0000056C       .text isAttackFrame__11daNpc_Ji1_cFv */
int daNpc_Ji1_c::isAttackFrame() {
    f32 frame = field_0x330->getFrame();
    f32 temp2 = 0.0f;
    f32 temp3 = temp2;

    if(field_0xD64 == 0x13) {
        temp2 = 28.0f;
        temp3 = 35.0f;
    }
    else if (field_0xD64 == 0x14) {
        temp2 = 25.0f;
        temp3 = 35.0f;
    }
    else {
        if(field_0xD64 == 7) {
            temp2 = 12.0f;
            temp3 = 28.0f;
        }
    }

    if(temp2 > frame) {
        return -1;
    }

    return temp3 < frame;
}

/* 0000056C-000005A0       .text isItemWaitAnim__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::isItemWaitAnim() {
    if(field_0xD64 == 0 || field_0xD64 == 0xC || field_0xD64 == 0xD || field_0xD64 == 0x18) {
        return true;
    }

    return false;
}

/* 000005A0-00000630       .text isClearRecord__11daNpc_Ji1_cFs */
BOOL daNpc_Ji1_c::isClearRecord(s16 param_1) {
    if(dComIfGs_isEventBit(0xF20)) {
        return false;
    }

    u8 level = dComIfGs_getEventReg(0xD003);
    if (param_1 >= l_HIO.field_0x60[level]) {
        return TRUE;
    }

    return FALSE;
}

/* 00000630-000006F8       .text setClearRecord__11daNpc_Ji1_cFs */
void daNpc_Ji1_c::setClearRecord(s16 hits) {
    u8 oldLevel = dComIfGs_getEventReg(0xD003);

    u8 newLevel = 0;
    while(hits >= l_HIO.field_0x60[newLevel] && newLevel <= 3) {
        newLevel++;
    }

    if(oldLevel < newLevel) {
        dComIfGs_setEventReg(0xD003, newLevel);
        if(hits >= l_HIO.field_0x60[3]) {
            dComIfGs_onEventBit(0xF20);
        }
    }
}

/* 000006F8-00000864       .text daNpc_Ji1_plRoomOutCheck__Fv */
static BOOL daNpc_Ji1_plRoomOutCheck() {
    cXyz plyrPos = daPy_getPlayerActorClass()->current.pos;
    static cXyz out_chk_pos(0.0f, 0.0f, 500.0f);

    cXyz temp = plyrPos - out_chk_pos;
    if(temp.absXZ() < 100.0f && dComIfGp_getDoStatus() == dActStts_OPEN_e) {
        return true;
    }

    return false;
}

/* 00000864-00000E98       .text normalSubActionHarpoonGuard__11daNpc_Ji1_cFs */
BOOL daNpc_Ji1_c::normalSubActionHarpoonGuard(s16 param_1) {
    /* Nonmatching - regalloc */

    if(field_0xD6C == 0) {
        if(field_0x7E0.ChkTgHit()) {
            field_0xD6C = 1;
            field_0xD74++;
            field_0xD68 = 0;
            setAnm(9, 0.0f, 1);
            dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, field_0x7E0.GetTgHitPosP());
            fopAcM_seStart(this, JA_SE_CV_JI_DEFENCE, 0);
            fopAcM_seStart(this, JA_SE_OBJ_COL_SWS_NMTLP, 0);
        }
        else {
            if(field_0xD64 == 0xD) {
                if(field_0x330->checkFrame(field_0x330->getEndFrame() - 2.0f) && ++field_0xD68 > 1) {
                    setAnm(0, 12.0f, 0);
                }
            }
        }
    }

    if(field_0xD6C == 1) {
        cLib_addCalcAngleS2(&current.angle.y, param_1, 2, 0x2000);
        if(field_0xD64 == 0xB) {
            if(field_0x330->checkFrame(field_0x330->getEndFrame() - 14.0f)) {
                setParticle(3, 3.0f, 0.5f);
                fopAcM_seStart(this, JA_SE_CV_JI_ATTACK, 0);
            }
            else if(field_0x330->checkFrame(field_0x330->getEndFrame() - 2.0f)) {
                dtParticle();
                if(field_0xD68++ > 2) {
                    field_0xD6C = 0;
                    setAnm(0, 16.0f, 0);
                }
                else {
                    setAnm(0xB, 4.0f, 1);
                    field_0x330->setPlaySpeed(2.0f);
                }
            }
        }
        else {
            if(field_0x330->checkFrame(field_0x330->getEndFrame() - 2.0f)) {
                field_0xD6C = 0;
                if(field_0xD74 == 3) {
                    setAnm(5, 4.0f, 0);
                    field_0xC84 = 0xC;
                    field_0x2C8 = field_0x2B0;

                    setAction(&daNpc_Ji1_c::eventAction, 0);
                }
                else if(field_0xD74 == 5) {
                    setAnm(5, 4.0f, 0);
                    field_0xC84 = 0xD;
                    field_0x2C8 = field_0x2B0;

                    setAction(&daNpc_Ji1_c::eventAction, 0);
                }
                else if(field_0xD74 > 5) {
                    setAnm(5, 4.0f, 0);
                    field_0xC84 = 0xE;
                    field_0x2C8 = field_0x2B0;

                    setAction(&daNpc_Ji1_c::eventAction, 0);

                    field_0xD74 = 0;
                }
                else {
                    setAnm(0xD, 8.0f, 0);
                }
            }
        }
    }
}

/* 00000E98-00001294       .text normalSubActionGuard__11daNpc_Ji1_cFs */
BOOL daNpc_Ji1_c::normalSubActionGuard(s16 param_1) {
    /* Nonmatching - regalloc */

    if(field_0xD6C == 0) {
        if(field_0x7E0.ChkTgHit()) {
            field_0xD6C = 1;
            field_0xD68 = 0;
            setAnm(0xF, 0.0f, 1);
            fopAcM_seStart(this, JA_SE_CV_JI_DEFENCE, 0);
        }
    }

    if(field_0xD6C == 1) {
        cLib_addCalcAngleS2(&current.angle.y, param_1, 2, 0x2000);
        if(field_0x330->checkFrame(field_0x330->getEndFrame() - 2.0f) && field_0xD68++ > 1) {
            field_0xD6C = 0;
            if(field_0xD74 == 3) {
                setAnm(5, 4.0f, 0);
                field_0xC84 = 0xC;
                field_0x2C8 = field_0x2B0;

                setAction(&daNpc_Ji1_c::eventAction, 0);
            }
            else if(field_0xD74 == 5) {
                setAnm(5, 4.0f, 0);
                field_0xC84 = 0xD;
                field_0x2C8 = field_0x2B0;

                setAction(&daNpc_Ji1_c::eventAction, 0);
            }
            else if(field_0xD74 > 5) {
                setAnm(5, 4.0f, 0);
                field_0xC84 = 0xE;
                field_0x2C8 = field_0x2B0;

                setAction(&daNpc_Ji1_c::eventAction, 0);
            }
            else {
                setAnm(0x1, 8.0f, 0);
            }
        }
    }
}

/* 00001294-000015E4       .text normalAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::normalAction(void*) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz delta = player->current.pos - current.pos;
    f32 temp = delta.absXZ();
    
    if(field_0xC78 == 0) {
        field_0x7E0.OnTgShield();
        if(field_0xD84 == 1) {
            setAnm(0, 8.0f, 0);
        }
        else {
            setAnm(1, 8.0f, 0);
        }

        if(dComIfGs_isEventBit(0x520)) {
            eventInfo.setXyCheckCB(&daNpc_Ji1_XyCheckCB);
        }

        field_0xC78 += 1;
    }
    else if(field_0xC78 != -1) {
        cXyz delta2 = player->current.pos - current.pos;
        s16 temp2 = cM_atan2s(delta2.x, delta2.z);

        if(eventInfo.checkCommandTalk()) {
            s16 temp3 = cLib_targetAngleY(&current.pos, &player->current.pos);
            temp3 -= m_jnt.getHead_y();
            temp3 -= m_jnt.getBackbone_y();
            cLib_addCalcAngleS2(&current.angle.y, temp3, 8, 0x800);
            if(cLib_distanceAngleS(current.angle.y, temp3) < 0x100) {
                setAction(&daNpc_Ji1_c::talkAction, 0);
            }
        }

        if(temp < l_HIO.field_0x2C && isGuardAnim() == 0 && field_0xD64 != 0xD) {
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
            if(dComIfGs_isEventBit(0x520)) {
                eventInfo.onCondition(dEvtCnd_CANTALKITEM_e);
            }
        }

        if(field_0xD84 == 1) {
            normalSubActionHarpoonGuard(temp2);
        }
        else {
            normalSubActionGuard(temp2);
        }
    }

    return true;
}

/* 000015E4-000019B0       .text kaitenExpAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::kaitenExpAction(void*) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    cXyz delta = player->current.pos - current.pos;
    f32 temp = delta.absXZ();

    if(field_0xD64 == 0x10) {
        if(field_0x330->checkFrame(19.0f)) {
            if(field_0xD68 == 1) {
                dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
            }

            fopAcM_seStart(this, JA_SE_CV_JI_ATTACK, 0);
            fopAcM_seStart(this, JA_SE_CM_JI_SHOTEI, 0);
            setParticle(3, 3.0f, 0.5f);
        }

        if(field_0x330->checkFrame(field_0x330->getEndFrame() - 2.0f)) {
            if(++field_0xD68 > 1) {
                field_0xD68 = 0;
                setAnm(0x11, 4.0f, 0);
            }
            
            dtParticle();
        }
    }

    if(field_0xC78 == 0) {
        setAnm(0x10, 4.0f, 0);
        if(!eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderOtherEventId(this, field_0xC54[6]);
            eventInfo.onCondition(dEvtCmd_INDEMO_e);

            return false;
        }

        field_0xC78++;
    }
    else if(field_0xC78 != -1) {
        int staffIdx = dComIfGp_evmng_getMyStaffId("Ji1");
        if(getEventActionNo(staffIdx) == 2) {
            setAction(&daNpc_Ji1_c::kaitenspeakAction, 0);
        }
        else {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }

    return true;
}

/* 000019B0-00001B9C       .text kaitenspeakAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::kaitenspeakAction(void*) {
    if(field_0xC78 == 0) {
        setAnm(1, 8.0f, 0);
        field_0xC78++;
    }
    else if(field_0xC78 != -1) {
        cXyz temp = daPy_getPlayerActorClass()->current.pos - current.pos;
        s16 temp2 = cM_atan2s(temp.x, temp.z) - current.angle.y;
        m_jnt.setTrn();
        if(abs(temp2) < 0x1000) {
            setAnm(3, 8.0f, 0);
        }

        int staffIdx = dComIfGp_evmng_getMyStaffId("Ji1");
        if(getEventActionNo(staffIdx) == 2) {
            if(temp2 == 0) {
                m_jnt.clrTrn();

                setAction(&daNpc_Ji1_c::talkAction, 0);
            }
        }
        else {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }

    return true;
}

/* 00001B9C-0000214C       .text kaitenwaitAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::kaitenwaitAction(void*) {
    daPy_py_c* player = (daPy_py_c*)daPy_getPlayerActorClass();
    cXyz delta = player->current.pos - current.pos;
    f32 temp = delta.absXZ();
    
    if(field_0xC78 == 0) {
        if(!dComIfGs_isEventBit(0x501)) {
            setAnm(0x12, 16.0f, 0);
        }
        else {
            setAnm(1, 4.0f, 0);
        }

        field_0xC78 += 1;
    }
    else if(field_0xC78 != -1) {
        if(!dComIfGs_isEventBit(0x501) && daNpc_Ji1_plRoomOutCheck()) {
            field_0xC84 = 9;
            setAction(&daNpc_Ji1_c::eventAction, 0);
            field_0x2C8 = &daNpc_Ji1_c::kaitenwaitAction;

            return true;
        }

        daPy_py_c* r27 = (daPy_py_c*)daPy_getPlayerActorClass();
        cXyz delta2 = player->current.pos - current.pos;
        s16 temp2 = cM_atan2s(delta2.x, delta2.z);

        if(!dComIfGs_isEventBit(0x501) && isGuardAnim() == 0) {
            cXyz delta3 = r27->current.pos - current.pos;
            s16 temp3 = cM_atan2s(delta3.x, delta3.z);
            cLib_addCalcAngleS2(&current.angle.y, temp3, 0x10, 0x800);
            if(r27->checkFrontRoll()) {
                setAnm(1, 6.0f, 0);
            }
            else {
                setAnm(0x12, 16.0f, 0);
            }
        }

        if(eventInfo.checkCommandTalk()) {
            s16 temp3 = cLib_targetAngleY(&current.pos, &player->current.pos);
            temp3 -= m_jnt.getHead_y();
            temp3 -= m_jnt.getBackbone_y();
            cLib_addCalcAngleS2(&current.angle.y, temp3, 8, 0x800);
            if(cLib_distanceAngleS(current.angle.y, temp3) < 0x100) {
                setAction(&daNpc_Ji1_c::talkAction, 0);
            }
        }

        if(temp < l_HIO.field_0x2C && isGuardAnim() == 0 && field_0xD64 != 0xD && r27->speedF < 1.0f) {
            eventInfo.onCondition(dEvtCnd_CANTALK_e);
        }

        if(player->checkFrontRollCrash() && (!dComIfGs_isEventBit(0x501) || l_HIO.field_0x30)) {
            field_0xD79 = 1;
            dComIfGp_getDetect().set_quake(0);
            
            setAction(&daNpc_Ji1_c::kaitenAction, 0);
        }

        if(field_0xD84 == 1) {
            normalSubActionHarpoonGuard(temp2);
        }
        else {
            normalSubActionGuard(temp2);
        }
    }

    return true;
}

/* 0000214C-00002738       .text kaitenAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::kaitenAction(void*) {
    if(field_0xC78 == 0) {
        if(!eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderOtherEventId(this, field_0xC54[5]);
            eventInfo.onCondition(dEvtCmd_INDEMO_e);

            return false;
        }

        int staffIdx = dComIfGp_evmng_getMyStaffId("Ji1");
        l_msgId = -1;
        field_0x2AC = 0x974;
        dComIfGp_evmng_cutEnd(staffIdx);
        current.angle.y = 0;
        field_0xC78 += 1;
    }
    else if(field_0xC78 != -1) {
        int staffIdx = dComIfGp_evmng_getMyStaffId("Ji1");
        int actionNo = getEventActionNo(staffIdx);
        if(l_msgId == -1) {
            if(actionNo == 2) {
                if(field_0x2AC == 0x974) {
                    current.angle.y = -0x8000;
                }
                else if(field_0x2AC == 0x975) {
                    dComIfGp_evmng_cutEnd(staffIdx);
                }

                l_msgId = fopMsgM_messageSet(field_0x2AC, &eyePos);
            }
            else if(actionNo == 1) {
                m_jnt.onHeadLock();
                m_jnt.onBackBoneLock();
                setAnm(4, 8.0f, 0);
                dComIfGp_evmng_cutEnd(staffIdx);
            }
        }
        else if(field_0xC78 == 1) {
            l_msg = fopMsgM_SearchByID(l_msgId);
            if(l_msg) {
                if(actionNo == 2) {
                    dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
                    mDoAud_seStart(JA_SE_CM_AJ_ANGRY_FOOT, NULL);
                }

                field_0xC78 += 1;
            }
        }
        else if(l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
            l_msg->mStatus = next_msgStatus(&field_0x2AC);
            if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                fopMsgM_messageSet(field_0x2AC);
                setAnimFromMsgNo(field_0x2AC);
            }
         }
        else if(l_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
            if(actionNo == 2) {
                l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                l_msgId = -1;
                field_0x2AC = 0x975;
                field_0xC78 = 1;

                return true;
            }

            if(staffIdx != -1) {
                dComIfGp_evmng_cutEnd(staffIdx);
            }

            if(dComIfGp_evmng_endCheck(field_0xC54[5])) {
                dComIfGs_onEventBit(0x501);
                field_0xD28 = home.pos;
                home.angle.y = 0;
                l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                if(field_0x2AC == 0x967) {
                    field_0xD70 = -1;
                    fopAcM_seStart(this, JA_SE_VS_JI_OPENING, 0);
                    mDoAud_bgmStop(45);

                    setAction(&daNpc_Ji1_c::plmoveAction, 0);
                }
                else {
                    setAnm(1, 8.0f, 0);
                    setAction(&daNpc_Ji1_c::normalAction, 0);
                }

                dComIfGp_event_reset();
            }
        }
        else if(dComIfGp_checkMesgSendButton() && actionNo == 3 && field_0x2AC == 0x976) {
            setAnm(2, 4.0f, 0);
            m_jnt.offHeadLock();
            m_jnt.offBackBoneLock();
            dComIfGp_evmng_cutEnd(staffIdx);
        }

        if(actionNo == 4) {
            cXyz delta = daPy_getPlayerActorClass()->current.pos - current.pos;
            s16 temp = cM_atan2s(delta.x, delta.z);
            cLib_addCalcAngleS2(&current.angle.y, temp, 4, 0x1000);
        }
    }

    return true;
}

/* 00002738-00002870       .text getMsg1stType__11daNpc_Ji1_cFv */
u32 daNpc_Ji1_c::getMsg1stType() {
    if(!dComIfGs_isEventBit(1)) {
        if(!dComIfGs_isEventBit(0x501)) {
            if(dComIfGs_isEventBit(0x640)) {
                return 0x964;
            }

            dComIfGs_onEventBit(0x640);
            return 0x961;
        }
        
        if(dComIfGs_isEventBit(0x2F40)) {
            return 0x95B;
        }

        if(field_0xD79) {
            return 0x977;
        }

        if(!field_0xD78) {
            field_0xD78 = 1;
            return 0x978;
        }

        return 0x97B;
    }

    if(dComIfGs_isEventBit(0x2F10)) {
        return 0x973;
    }

    if(!dComIfGs_isEventBit(0x108)) {
        dComIfGs_onEventBit(0x108);
        eventInfo.setEventId(-1);

        return 0x965;
    }

    return 0x94D;
}

/* 00002870-00002A08       .text getMsg2ndType__11daNpc_Ji1_cFv */
u32 daNpc_Ji1_c::getMsg2ndType() {
    u32 msgNo;

    if(dComIfGp_event_chkTalkXY()) {
        m_jnt.offBackBoneLock();
        if(!dComIfGs_isEventBit(0xD80)) {
            dComIfGs_onEventBit(0xD80);
            msgNo = 0x9AE;
        }
        else if(dComIfGs_getBeastNum(3) < 10) {
            msgNo = 0x9BB;
        }
        else if(dComIfGs_isEventBit(0xB20)) {
            msgNo = 0x9BC;
        }
        else {
            msgNo = 0x9B0;
        }
    }
    else if(dComIfGs_isEventBit(0x2)) {
        if(dComIfGs_isEventBit(0xF20)) {
            if(dComIfGs_getEventReg(0xCF03) >= 3) {
                msgNo = 0x9AC;
            }
            else {
                msgNo = 0x9AD;
            }
        }
        else if(dComIfGs_getEventReg(0xCF03) >= 3) {
            msgNo = 0x9AA;
        }
        else {
            msgNo = 0x9AB;
        }
    }
    else {
        msgNo = 0x986;
        dComIfGs_onEventBit(0x2);
    }

    dComIfGs_setEventReg(0xCF03, 0);
    return msgNo;
}

/* 00002A08-00002A60       .text getMsg__11daNpc_Ji1_cFv */
u32 daNpc_Ji1_c::getMsg() {
    if(dComIfGs_isEventBit(0x520)) {
        return getMsg2ndType();
    }
    
    return getMsg1stType();
}

/* 00002A60-00002C64       .text next_msgStatus__11daNpc_Ji1_cFPUl */
u16 daNpc_Ji1_c::next_msgStatus(u32* pMsgNo) {
    u16 status = fopMsgStts_MSG_CONTINUES_e;
    switch(field_0x2AC) {
        case 0x951:
        case 0x952:
        case 0x956:
        case 0x957:
        case 0x959:
        case 0x95B:
        case 0x95F:
        case 0x961:
        case 0x962:
        case 0x965:
        case 0x975:
        case 0x978:
        case 0x979:
        case 0x986:
        case 0x987:
        case 0x988:
        case 0x989:
        case 0x98B:
        case 0x98D:
        case 0x98F:
        case 0x991:
        case 0x993:
        case 0x99B:
        case 0x99D:
        case 0x99F:
        case 0x9A1:
        case 0x9A7:
        case 0x9AA:
        case 0x9AC:
        case 0x9AE:
        case 0x9B0:
        case 0x9B1:
        case 0x9B2:
        case 0x9B3:
        case 0x9B8:
        case 0x9B9:
            field_0x2AC = field_0x2AC + 1;
            break;
        case 0x97B:
            field_0x2AC = 0x9C0;
            break;
        case 0x9A2:
            if(dComIfGs_isEventBit(0xF10)) {
                field_0x2AC = 0x9A3;
            }
            else {
                field_0x2AC = 0x9A5;
            }

            break;
        case 0x9AF:
            if(dComIfGs_getBeastNum(3) >= 10) {
                field_0x2AC = 0x9B0;
            }
            else {
                field_0x2AC = 0x9BB;
            }

            break;
        case 0x997:
        case 0x999:
            field_0x2AC = 0x998;
            break;
        case 0x99A:
            if(dComIfGs_getEventReg(0xD003) == 1) {
                field_0x2AC = 0x99B;
            }
            else if(dComIfGs_getEventReg(0xD003) == 2) {
                field_0x2AC = 0x99D;
            }
            else {
                field_0x2AC = 0x99F;
            }

            break;
        case 0x95C:
        case 0x973:
        case 0x976:
        case 0x977:
        case 0x97A:
        case 0x9C0:
            field_0x2AC = 0x967;
            break;
        case 0x94D:
        case 0x966:
            field_0x2AC = 0x94E;
            break;
        case 0x967:
            if(l_msg->mSelectNum == 0) {
                status = fopMsgStts_MSG_ENDS_e;
            }
            else if (l_msg->mSelectNum == 1) {
                field_0x2AC = 0x968;
            }

            break;
        case 0x94E:
            if(l_msg->mSelectNum == 0) {
                status = fopMsgStts_MSG_ENDS_e;
            }
            else if (l_msg->mSelectNum == 1) {
                field_0x2AC = 0x94F;
            }

            break;
        case 0x98A:
        case 0x9AB:
        case 0x9AD:
            if(l_msg->mSelectNum == 0) {
                status = fopMsgStts_MSG_ENDS_e;
            }
            else if (l_msg->mSelectNum == 1) {
                field_0x2AC = 0x995;
            }

            break;
        default:
            status = fopMsgStts_MSG_ENDS_e;
    }

    return status;
}

/* 00002C64-000033D0       .text talkAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::talkAction(void*) {
    if(field_0xC78 == 0) {
        if(dComIfGp_event_chkTalkXY() && !dComIfGp_evmng_ChkPresentEnd()) {
            if(dComIfGs_isEventBit(0xD80) == 0) {
                daPy_py_c* player = daPy_getPlayerActorClass();
                cXyz delta = player->current.pos - current.pos;
                f32 dummy = delta.absXZ();

                s16 temp = cM_atan2s(delta.x, delta.z);
                cLib_addCalcAngleS2(&current.angle.y, temp, 8, 0x1000);
                field_0xD7E = 1;
                m_jnt.onBackBoneLock();
            }

            return 0;
        }

        field_0xD7E = 0;
        field_0x2AC = getMsg();
        field_0xC78 += 1;
        l_msgId = -1;
        l_msg = 0;
    }
    else if(field_0xC78 != -1) {
        if(l_msgId == -1) {
            l_msgId = fopMsgM_messageSet(field_0x2AC, &eyePos);
        }
        else if(l_msg == 0) {
            l_msg = fopMsgM_SearchByID(l_msgId);
        }
        else {
            setAnimFromMsgNo(field_0x2AC);
            if(l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
                l_msg->mStatus = next_msgStatus(&field_0x2AC);
                if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                    fopMsgM_messageSet(field_0x2AC);
                    setAnimFromMsgNo(field_0x2AC);
                }
            }
            else if(l_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
                l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                dComIfGp_event_reset();

                if(field_0x2AC == 0x963 || field_0x2AC == 0x98A) {
                    int staffIdx = dComIfGp_evmng_getMyStaffId("Ji1");
                    dComIfGp_evmng_cutEnd(staffIdx);
                    if(dComIfGp_evmng_endCheck(field_0xC54[6])) {
                        if(field_0x2AC == 0x98A) {
                            field_0xD70 = -1;
                            fopAcM_seStart(this, JA_SE_VS_JI_OPENING, 0);
                            mDoAud_bgmStop(45);

                            setAction(&daNpc_Ji1_c::plmoveAction, 0);
                        }
                        else {
                            setAction(&daNpc_Ji1_c::kaitenwaitAction, 0);
                        }
                    }
                }
                else if(field_0x2AC == 0x94E || field_0x2AC == 0x967 || field_0x2AC == 0x9AB || field_0x2AC == 0x9AD || field_0x2AC == 0x9B4) {
                    if(field_0x2AC == 0x9B4) {
                        field_0xD7B = 1;
                    }

                    field_0xD70 = -1;
                    fopAcM_seStart(this, JA_SE_VS_JI_OPENING, 0);
                    mDoAud_bgmStop(45);

                    setAction(&daNpc_Ji1_c::plmoveAction, 0);
                }
                else if(field_0x2AC == 0x995) {
                    setAction(&daNpc_Ji1_c::plmoveAction, 0);
                }
                else {
                    setAction(field_0x2BC, 0);
                }
            }
            
            if(field_0xD64 == 0x16 && field_0x330->getFrame() >= l_HIO.field_0xB4) {
                BackSlide(l_HIO.field_0xAC, l_HIO.field_0xB0);
            }
        }
    }

    return TRUE;
}

/* 000033D0-000039AC       .text speakAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::speakAction(void*) {
}

/* 000039AC-00003F54       .text speakBadAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::speakBadAction(void*) {
    int staffIdx = dComIfGp_evmng_getMyStaffId("Ji1");
    if(field_0xC78 == 0) {
        if(!eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderOtherEventId(this, field_0xC54[3]);
            eventInfo.onCondition(dEvtCnd_UNK2_e);

            return false;
        }

        if(MoveToPlayer(280.0f, 0)) {
            return false;
        }

        dComIfGp_evmng_cutEnd(staffIdx);
        switch(field_0xD70) {
            case 0:
                field_0x2AC = 0x96F;
                break;
            case 1:
                field_0x2AC = 0x970;
                break;
            case 2:
                field_0x2AC = 0x971;
                break;
            case 3:
                field_0x2AC = 0x980;
                break;
            case 4:
                field_0x2AC = 0x985;
                break;
            case 5:
                field_0x2AC = 0x972;
                break;
            default:
                field_0x2AC = 0x9B6;
                break;
        }

        setAnm(7, 4.0f, 0);
        field_0xC78 += 1;
        l_msgId = -1;
    }
    else if(field_0xC78 != -1) {
        if(l_msgId == -1) {
            if(field_0xD64 == 7) {
                if(field_0x330->getFrame() > field_0x330->getEndFrame() - 2.0f) {
                    l_msgId = fopMsgM_messageSet(field_0x2AC, &eyePos);
                    field_0xBFC.swing_horizone_init(2, 0x1000, 0x1000, 1);
                    setAnm(5, 0.0f, 0);
                }
                else if(field_0x330->checkFrame(field_0x330->getEndFrame() - 10.0f)) {
                    dComIfGp_evmng_cutEnd(staffIdx);
                    fopAcM_seStart(this, JA_SE_CV_JI_ATTACK, 0);
                    dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
                }
                else if(field_0x330->checkFrame(field_0x330->getEndFrame() - 14.0f)) {
                    fopAcM_seStart(this, JA_SE_CM_JI_ATTACK, 0);
                }
            }
        }
        else {
            if(field_0xC78 == 1) {
                l_msg = fopMsgM_SearchByID(l_msgId);
                if(l_msg) {
                    field_0xC78 += 1;
                }
            }
            else {
                if(l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
                    setAnimFromMsgNo(field_0x2AC);
                    l_msg->mStatus = next_msgStatus(&field_0x2AC);

                    if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                        fopMsgM_messageSet(field_0x2AC);
                    }
                }
                else if(l_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
                    if(staffIdx != -1) {
                        dComIfGp_evmng_cutEnd(staffIdx);
                    }

                    if(dComIfGp_evmng_endCheck(field_0xC54[3])) {
                        l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                        if(field_0x2AC == 0x969) {
                            field_0xD70 = 0;
                            setAction(&daNpc_Ji1_c::teachAction, 0);
                        }
                        else {
                            setAction(field_0x2BC, 0);
                        }

                        dComIfGp_event_reset();
                    }
                }
            }
        }
    }    

    return true;
}

/* 00003F54-00004050       .text initPosObject__11daNpc_Ji1_cFPvPv */
void* daNpc_Ji1_c::initPosObject(void* pActor, void* pData) {
    if(fopAc_IsActor(pActor) && fopAcM_GetName(pActor) == PROC_TSUBO) {
        ((daTsubo::Act_c*)pActor)->pos_init();
    }

    return 0;
}

/* 00004050-000040FC       .text initPos__11daNpc_Ji1_cFi */
void daNpc_Ji1_c::initPos(int param_1) {
    if(param_1 >= 0) {
        setAnm(param_1, 0.0f, 0);
    }

    fopAcM_Search(&initPosObject, this);
    old.pos = field_0xD28;
    current.pos = old.pos;
    current.angle = csXyz(home.angle.y, 0, 0);
}

/* 00004138-00004268       .text createItem__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::createItem() {
    u8 itemNo;

    if(field_0xD7C) {
        itemNo = dItem_SWORD_e;
    }
    else if(field_0xD7B == 1) {
        itemNo = dItem_HURRICANE_SPIN_e;
    }
    else if(dComIfGs_getEventReg(0xD003) == 1) {
        itemNo = dItem_PURPLE_RUPEE_e;
    }
    else if(dComIfGs_getEventReg(0xD003) == 2) {
        itemNo = dItem_ORANGE_RUPEE_e;
    }
    else if(field_0xD70 >= l_HIO.field_0x60[3] && dComIfGs_isEventBit(0xF10)) {
        itemNo = dItem_SILVER_RUPEE_e;
    }
    else {
        itemNo = dItem_HEART_PIECE_e;
        dComIfGs_onEventBit(0xF10);
    }

    fpc_ProcID itemPID = fopAcM_createItemForPresentDemo(&current.pos, itemNo, 0, -1, current.roomNo);
    if(itemPID != fpcM_ERROR_PROCESS_ID_e) {
        dComIfGp_event_setItemPartnerId(itemPID);
    }

    field_0xD7D = itemNo;
}

/* 00004268-00004448       .text set_mtx__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::set_mtx() {
    J3DModel* pModel = field_0x330->getModel();

    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    pModel->setBaseTRMtx(mDoMtx_stack_c::get());
    field_0x330->calc();
    field_0x3F8->setBaseTRMtx(pModel->getAnmMtx(m_jnt.getHeadJntNum()));

    if(field_0x430) {
        field_0x430->setGlobalRTMatrix(pModel->getAnmMtx(m_jnt.getHeadJntNum()));
    }

    if(field_0xD84 == 1) {
        mDoMtx_stack_c::copy(pModel->getAnmMtx(handRJointNo));
        mDoMtx_stack_c::XYZrotM(field_0xD5C);
        mDoMtx_stack_c::transM(field_0xD50);
        mpMorf->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());
    }
    mpMorf->calc();

    if(field_0xD84) {
        cXyz temp(0.0f, 0.0f, 100.0f);
        cXyz temp2(0.0f, 0.0f, -100.0f);

        if(field_0xD64 == 0x14) {
            temp.z = 70.0f;
        }

        field_0xB90 = field_0xB78;
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(1));
        mDoMtx_stack_c::multVec(&temp, &field_0xB78);
        mDoMtx_stack_c::multVec(&temp2, &field_0xB84);
    }
}

/* 00004448-00004488       .text getEventActionNo__11daNpc_Ji1_cFi */
s32 daNpc_Ji1_c::getEventActionNo(int staffIdx) {
    static char* ActionNames[] = {
        "00_dummy",
        "01_dummy",
        "02_dummy",
        "03_dummy",
        "04_dummy",
        "05_dummy",
        "06_dummy",
    };

    return dComIfGp_evmng_getMyActIdx(staffIdx, ActionNames, ARRAY_SIZE(ActionNames), FALSE, 0);
}

/* 00004488-00004714       .text eventAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::eventAction(void*) {
    if(field_0xC78 == 0) {
        int staffIdx = dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
        if(!eventInfo.checkCommandDemoAccrpt() && staffIdx == -1) {
            fopAcM_orderOtherEventId(this, field_0xC54[field_0xC84]);
            eventInfo.onCondition(dEvtCnd_UNK2_e);

            return false;
        }

        field_0xC78 += 1;
    }
    else if(field_0xC78 == -1) {
        field_0xC84 = 0x12;
    }
    else {
        int staffIdx = dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
        privateCut();
        AnimeControlToWait();
        if(dComIfGp_evmng_endCheck(field_0xC54[field_0xC84])) {
            dComIfGp_event_reset();

            setAction(field_0x2C8, 0);
        }
        else if(staffIdx == -1) {
            setAction(field_0x2C8, 0);
        }
    }

    return true;
}

/* 00004714-00004778       .text evn_init_pos_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_init_pos_init(int staffIdx) {
    int* data = dComIfGp_evmng_getMyIntegerP(staffIdx, "AnmNo");

    u32 value = 0;
    if(data) {
        value = *data;
    }

    initPos(value);
    return 1;
}

/* 00004778-00004838       .text evn_setAnm_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_setAnm_init(int staffIdx) {
    int* iData = dComIfGp_evmng_getMyIntegerP(staffIdx, "AnmNo");
    f32* fData = dComIfGp_evmng_getMyFloatP(staffIdx, "hokan");

    if(iData) {
        int iVal = *iData;
        f32 fVal = 0.0f;
        if(fData) {
            fVal = *fData;
        }

        if(field_0xD84 != 1 && iVal == 5) {
            iVal = 1;
        }

        setAnm(iVal, fVal, 0);
    }

    return 1;
}

/* 00004838-000049AC       .text evn_talk_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_talk_init(int staffIdx) {
    int* pMsgNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "MsgNo");
    int* pEndMsgNo = dComIfGp_evmng_getMyIntegerP(staffIdx, "EndMsgNo");

    l_msgId = fpcM_ERROR_PROCESS_ID_e;
    l_msg = 0;
    if(pMsgNo) {
        field_0x2AC = *pMsgNo;
        if(field_0x2AC == 0x9A4) {
            if(field_0xC38 == 2) {
                field_0x2AC = 0x9A9;
            }
            else if(field_0xD7D == 7) {
                field_0x2AC = 0x9A6;
            }
        }
        else if(field_0x2AC == 0x9A1) {
            if(field_0xC38 == 2) {
                field_0x2AC = 0x9A7;
            }
        }
        else if(field_0x2AC == 0x9B7) {
            if(field_0x2C8 == &daNpc_Ji1_c::kaitenwaitAction) {
                field_0x2AC = 0x95E;
            }
            else if(field_0x2C8 == &daNpc_Ji1_c::teachAction) {
                field_0x2AC = 0x95D;
            }
        }
    }
    else {
        field_0x2AC = 0;
    }

    if(pEndMsgNo) {
        field_0xD80 = *pEndMsgNo;
    }
    else {
        field_0xD80 = 0;
    }

    return 1;
}

/* 000049AC-00004B1C       .text evn_talk__11daNpc_Ji1_cFv */
u32 daNpc_Ji1_c::evn_talk() {
    if(l_msgId == fpcM_ERROR_PROCESS_ID_e) {
        l_msgId = fopMsgM_messageSet(field_0x2AC, &eyePos);
    }
    else if(!l_msg) {
        l_msg = fopMsgM_SearchByID(l_msgId);
        fopMsgM_demoMsgFlagOn();
    }
    else {
        setAnimFromMsgNo(field_0x2AC);
        if(l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
            l_msg->mStatus = next_msgStatus(&field_0x2AC);
            if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                fopMsgM_messageSet(field_0x2AC);
            }
            else if(l_msg->mStatus == fopMsgStts_MSG_ENDS_e) {
                if(field_0x2AC == 0x9BA) {
                    field_0xD7B = 0;
                    field_0xD6C = 0;
                }
                else if(field_0x2AC == 0x95A) {
                    field_0xD7C = 0;
                    field_0xD6C = 0;
                }
            }
        }
        else {
            if(l_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
                l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                l_msg = 0;
                l_msgId = fpcM_ERROR_PROCESS_ID_e;

                return true;
            }

            if((l_msg->mStatus == fopMsgStts_BOX_OPENING_e || l_msg->mStatus == fopMsgStts_MSG_TYPING_e) && field_0x2AC == field_0xD80) {
                field_0xD80 = 0;
                return true;
            }
        }
    }

    return false;
}

/* 00004B1C-00004B84       .text evn_continue_talk_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_continue_talk_init(int staffIdx) {
    int* data = dComIfGp_evmng_getMyIntegerP(staffIdx, "EndMsgNo");

    if(data) {
        field_0xD80 = *data;
    }
    else {
        field_0xD80 = 0;
    }

    return 1;
}

/* 00004B84-00004CF4       .text evn_continue_talk__11daNpc_Ji1_cFv */
u32 daNpc_Ji1_c::evn_continue_talk() {
    if(l_msgId == fpcM_ERROR_PROCESS_ID_e) {
        l_msgId = fopMsgM_messageSet(field_0x2AC, &eyePos);
    }
    else if(!l_msg) {
        l_msg = fopMsgM_SearchByID(l_msgId);
        fopMsgM_demoMsgFlagOn();
    }
    else {
        setAnimFromMsgNo(field_0x2AC);
        if(l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
            l_msg->mStatus = next_msgStatus(&field_0x2AC);
            if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                fopMsgM_messageSet(field_0x2AC);
            }
            else if(l_msg->mStatus == fopMsgStts_MSG_ENDS_e) {
                if(field_0x2AC == 0x9BA) {
                    field_0xD7B = 0;
                    field_0xD6C = 0;
                }
                else if(field_0x2AC == 0x95A) {
                    field_0xD7C = 0;
                    field_0xD6C = 0;
                }
            }
        }
        else {
            if(l_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
                l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                l_msg = 0;
                l_msgId = fpcM_ERROR_PROCESS_ID_e;

                return true;
            }

            if((l_msg->mStatus == fopMsgStts_BOX_OPENING_e || l_msg->mStatus == fopMsgStts_MSG_TYPING_e) && field_0x2AC == field_0xD80) {
                field_0xD80 = 0;
                return true;
            }
        }
    }

    return false;
}

/* 00004CF4-00004D50       .text evn_setAngle_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_setAngle_init(int staffIdx) {
    int* data = dComIfGp_evmng_getMyIntegerP(staffIdx, "angle");

    if(data) {
        current.angle.y = *data;
    }

    return 1;
}

/* 00004D50-00004E8C       .text evn_sound_proc_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_sound_proc_init(int staffIdx) {
    int* data = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm");

    if(data) {
        switch(*data) {
            case 0:
                mDoAud_bgmStop(45);
                break;
            case 1:
                mDoAud_bgmStart(JA_BGM_HOUSE_G);
                break;
            case 2:
                fopAcM_seStart(this, JA_SE_VS_JI_ENDING, 0);
                break;
            case 3:
                dComIfGp_getVibration().StartShock(5, -0x11, cXyz(0.0f, 1.0f, 0.0f));
        }
    }

    return 1;
}

/* 00004E8C-00004F60       .text evn_head_swing_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_head_swing_init(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm");
    u32 value;
    if(!pData) {
        value = 0;
    }
    else {
        value = *pData;
    }

    switch(value) {
        case 0:
            field_0xBFC.swing_horizone_init(2, 0x1000, 0x1000, 1);
            break;
        case 1:
            field_0xBFC.swing_vertical_init(2, 0x1000, 0x800, 1);
            break;
        case 2:
            field_0xBFC.swing_vertical_init(1, 0x1400, 0x1000, 1);
            break;
    }

    return true;
}

/* 00004F60-00005008       .text evn_harpoon_proc_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_harpoon_proc_init(int staffIdx) {
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm");
    u32 value;
    if(!pData) {
        value = 0;
    }
    else {
        value = *pData;
    }

    switch(value) {
        case 0:
            harpoonRelease(0);
            break;
        case 1:
            field_0xD84 = 0;
            break;
        case 2:
            field_0xD84 = 1;
            break;
    }

    return true;
}

/* 00005008-00005078       .text evn_RollAtControl_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_RollAtControl_init(int staffIdx) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    field_0xD18 = 400.0f;
    field_0xD16 = cLib_targetAngleY(&current.pos, &player->current.pos);
    field_0xD16 += 0x2000;
    field_0xC30 = 30;
    field_0xD68 = 0;

    return 1;
}

/* 00005078-00005314       .text evn_RollAtControl__11daNpc_Ji1_cFv */
u32 daNpc_Ji1_c::evn_RollAtControl() {
    static cXyz hit_scale(1.25f, 1.25f, 1.25f);

    field_0xD16 += 0x540;
    cLib_chaseF(&field_0xD18, 0.0f, 1.0f);
    field_0xD1C = current.pos;
    field_0xD1C.x += field_0xD18 * cM_ssin(field_0xD16);
    field_0xD1C.z += field_0xD18 * cM_scos(field_0xD16);
    dComIfGp_evmng_setGoal(&field_0xD1C);
    field_0x6B0.SetC(current.pos);
    dComIfG_Ccsp()->Set(&field_0x6B0);
    field_0x7E0.SetC(current.pos);
    dComIfG_Ccsp()->Set(&field_0x7E0);
    if(field_0xC30 == 0xA) {
        setAnm(0x19, 0.0f, 0);
        BackSlideInit();
        setHitParticle(&hit_scale, JA_SE_CV_JI_FUTTOBI);
    }
    if(field_0xD64 == 0x19) {
        if(field_0x330->getFrame() < 10.0f) {
            daPy_py_c* player = daPy_getPlayerActorClass();
            cXyz temp = player->current.pos - current.pos;
            cLib_addCalcAngleS2(&current.angle.y, cM_atan2s(temp.x, temp.z), 2, 0x2000);
        }
        else {
            if(field_0x330->checkFrame(20.0f) && field_0xD68++ < 2) {
                setHitParticle(&hit_scale, JA_SE_CV_JI_FUTTOBI);
                BackSlideInit();
                setAnm(0x19, 4.0f, 1);
            }
        }

        BackSlide(120.0f, 10.0f);
    }

    if(field_0xC30 > 0) {
        field_0xC30 -= 1;
    }
    else {
        return true;
    }

    return false;
}

/* 00005314-000053F8       .text evn_game_mode_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_game_mode_init(int staffIdx) {
    int* data = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm");

    u32 value;
    if(data) {
        value = *data;
    }
    else {
        value = 0;
    }

    switch(value) {
        case 0:
            dComIfGp_endMiniGame(6);
            break;
        case 1:
            dComIfGp_startMiniGame(6);
            game_life_point = 3;
        case 2:
            dComIfGp_endMiniGame(2);
            break;
    }

    return 1;
}

/* 000053F8-0000545C       .text evn_turn_to_player__11daNpc_Ji1_cFv */
u32 daNpc_Ji1_c::evn_turn_to_player() {
    daPy_py_c* player = daPy_getPlayerActorClass();
    s16 target = cLib_targetAngleY(&current.pos, &player->current.pos);
    if (cLib_addCalcAngleS(&current.angle.y, target, 4, 0x1000, 0x100) == 0) {
        return 1;
    } else {
        return 0;
    }
}

/* 0000545C-00005508       .text evn_hide_init__11daNpc_Ji1_cFi */
u32 daNpc_Ji1_c::evn_hide_init(int staffIdx) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    int* pData = dComIfGp_evmng_getMyIntegerP(staffIdx, "prm");
    u32 value;
    if(!pData) {
        value = 0;
    }
    else {
        value = *pData;
    }

    if((value & 1) == 0) {
        field_0xD85 = 0;
    }
    else {
        field_0xD85 = 1;
    }

    if(value & 2) {
        player->onPlayerNoDraw();
    }
    else {
        player->offPlayerNoDraw();
    }

    return true;
}

/* 00005508-000055E4       .text AnimeControlToWait__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::AnimeControlToWait() {
    /* Nonmatching */
    if(field_0x330->getPlayMode() == J3DFrameCtrl::EMode_NONE) {
        if(field_0x330->checkFrame(field_0x330->getEndFrame() - 1.0f)) {
            if(isAttackAnim() || isGuardAnim()) {
                setAnm(5, 4.0f, 0);
            }
            else if(isItemWaitAnim()) {
                setAnm(0, 4.0f, 0);
            }
        }
    }
}

/* 000055E4-000057DC       .text privateCut__11daNpc_Ji1_cFv */
u32 daNpc_Ji1_c::privateCut() {
    int staffIdx = dComIfGp_evmng_getMyStaffId(mEventCut.getActorName());
    if(staffIdx == -1) {
        return false;
    }

    static char* cut_name_tbl[] = {
        "SETANM",
        "TALKMSG",
        "INITPOS",
        "CREATEITEM",
        "SOUND",
        "HEADSWING",
        "HARPOON",
        "ROLLAT_CNT",
        "GAME_MODE",
        "TURN_TO_PLAYER",
        "HIDE",
        "CONTINUETALK",
        "SETANGLE",
    };
    enum {
        ACT_SETANM,
        ACT_TALKMSG,
        ACT_INITPOS,
        ACT_CREATEITEM,
        ACT_SOUND,
        ACT_HEADSWING,
        ACT_HARPOON,
        ACT_ROLLAT_CNT,
        ACT_GAME_MODE,
        ACT_TURN_TO_PLAYER,
        ACT_HIDE,
        ACT_CONTINUETALK,
        ACT_SETANGLE,
    };
    int actIdx = dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), 1, 0);
    if(actIdx == -1) {
        dComIfGp_evmng_cutEnd(staffIdx);
    }
    else {
        if(dComIfGp_evmng_getIsAddvance(staffIdx)) {
            switch(actIdx) {
                case ACT_SETANM:
                    evn_setAnm_init(staffIdx);
                    break;
                case ACT_TALKMSG:
                    evn_talk_init(staffIdx);
                    break;
                case ACT_INITPOS:
                    evn_init_pos_init(staffIdx);
                    break;
                case ACT_CREATEITEM:
                    createItem();
                    break;
                case ACT_SOUND:
                    evn_sound_proc_init(staffIdx);
                    break;
                case ACT_HEADSWING:
                    evn_head_swing_init(staffIdx);
                    break;
                case ACT_HARPOON:
                    evn_harpoon_proc_init(staffIdx);
                    break;
                case ACT_ROLLAT_CNT:
                    evn_RollAtControl_init(staffIdx);
                    break;
                case ACT_GAME_MODE:
                    evn_game_mode_init(staffIdx);
                    break;
                case ACT_HIDE:
                    evn_hide_init(staffIdx);
                    break;
                case ACT_CONTINUETALK:
                    evn_continue_talk_init(staffIdx);
                    break;
                case ACT_SETANGLE:
                    evn_setAngle_init(staffIdx);
                    break;
            }
        }

        BOOL end;
        switch(actIdx) {
            case ACT_TALKMSG:
                end = evn_talk();
                break;
            case ACT_ROLLAT_CNT:
                end = evn_RollAtControl();
                break;
            case ACT_TURN_TO_PLAYER:
                end = evn_turn_to_player();
                break;
            case ACT_CONTINUETALK:
                end = evn_continue_talk();
                break;
            default:
                end = true;
        }

        if(end) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }
    }

    return true;
}

/* 000057DC-000058B8       .text setParticle__11daNpc_Ji1_cFiff */
u32 daNpc_Ji1_c::setParticle(int max, f32 rate, f32 spread) {
    dtParticle();
    if(field_0x2E0.getEmitter() == 0) {
        JPABaseEmitter* emitter = dComIfGp_particle_setToon(dPa_name::ID_COMMON_2022, &current.pos, 0, 0, 0xB9, &field_0x2E0, fopAcM_GetRoomNo(this));
        if(emitter) {
            emitter->setRate(rate);
            emitter->setSpread(spread);
            emitter->setRandomDirectionSpeed(1.5f);
            emitter->setMaxFrame(max);

            return true;
        }
    }

    return false;
}

/* 000058B8-000058F0       .text dtParticle__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::dtParticle() {
    if(field_0x2E0.getEmitter()) {
        field_0x2E0.remove();
    }
}

/* 000058F0-000059E8       .text setParticleAT__11daNpc_Ji1_cFiff */
u32 daNpc_Ji1_c::setParticleAT(int max, f32 rate, f32 spread) {
    if(field_0x300.getEmitter() == 0) {
        JPABaseEmitter* emitter = dComIfGp_particle_setToon(dPa_name::ID_COMMON_2022, &field_0x320, 0, 0, 0xB9, &field_0x300, fopAcM_GetRoomNo(this));
        if(field_0x300.getEmitter()) {
            JGeometry::TVec3<f32> scaleVec;
            scaleVec.x = 2.0f;
            scaleVec.y = 2.0f;
            scaleVec.z = 2.0f;
            emitter->setGlobalParticleScale(scaleVec);
            emitter->setVolumeSweep(0.15f);
            emitter->setRate(rate);
            emitter->setSpread(spread);
            emitter->setRandomDirectionSpeed(1.5f);
            emitter->setMaxFrame(max);

            return true;
        }
    }

    return false;
}

/* 000059E8-00005A20       .text dtParticleAT__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::dtParticleAT() {
    if(field_0x300.getEmitter()) {
        field_0x300.remove();
    }
}

/* 00005A20-00005F30       .text startspeakAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::startspeakAction(void*) {
    /* Nonmatching */
}

/* 00005F30-00006238       .text endspeakAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::endspeakAction(void*) {
    int staffIdx = dComIfGp_evmng_getMyStaffId("Ji1");
    int actionNo = getEventActionNo(staffIdx);

    if(field_0xC78 == 0) {
        if(!eventInfo.checkCommandDemoAccrpt()) {
            fopAcM_orderOtherEventId(this, field_0xC54[2]);
            eventInfo.onCondition(dEvtCnd_UNK2_e);

            return false;
        }

        if(actionNo == 0) {
            dComIfGp_evmng_cutEnd(staffIdx);
        }

        if(dComIfGs_isEventBit(0x520)) {
            field_0x2AC = 0x996;
        }
        else if(dComIfGs_isEventBit(0x1)) {
            field_0x2AC = 0x96D;
        }
        else if(!dComIfGs_isEventBit(0x2F40)) {
            field_0x2AC = 0x950;
        }
        else {
            field_0x2AC = 0x954;
        }

        field_0xC78 += 1;
        l_msgId = -1;
    }
    else if(field_0xC78 != -1) {
        if(l_msgId == -1) {
            l_msgId = fopMsgM_messageSet(field_0x2AC, &eyePos);
            setAnm(5, 4.0f, 0);
        }
        else {
            if(field_0xC78 == 1) {
                l_msg = fopMsgM_SearchByID(l_msgId);
                if(l_msg) {
                    field_0xC78 += 1;
                }
            }
            else {
                if(l_msg->mStatus == fopMsgStts_MSG_DISPLAYED_e) {
                    setAnimFromMsgNo(field_0x2AC);
                    l_msg->mStatus = next_msgStatus(&field_0x2AC);

                    if(l_msg->mStatus == fopMsgStts_MSG_CONTINUES_e) {
                        fopMsgM_messageSet(field_0x2AC);
                    }
                }
                else if(l_msg->mStatus == fopMsgStts_BOX_CLOSED_e) {
                    l_msg->mStatus = fopMsgStts_MSG_DESTROYED_e;
                    mDoAud_bgmStop(45);
                    setAction(&daNpc_Ji1_c::reiAction, 0);
                }
            }
        }
    }    

    return true;
}

/* 00006238-00006728       .text reiAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::reiAction(void*) {
    /* Nonmatching */
}

/* 00006728-00006C1C       .text plmoveAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::plmoveAction(void*) {
    /* Nonmatching */
}

/* 00006C1C-00007140       .text teachMove__11daNpc_Ji1_cFf */
void daNpc_Ji1_c::teachMove(f32 param_1) {
    /* Nonmatching */
}

/* 00007140-00007424       .text teachSpRollCutMove__11daNpc_Ji1_cFf */
BOOL daNpc_Ji1_c::teachSpRollCutMove(float) {
    /* Nonmatching */
}

/* 00007424-000074B0       .text calcCoCorrectValue__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::calcCoCorrectValue() {
    /* Nonmatching */
}

/* 000074B0-00007548       .text calcBgCorrectValue__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::calcBgCorrectValue() {
    /* Nonmatching */
}

/* 00007548-00007A80       .text MoveToPlayer__11daNpc_Ji1_cFfUc */
BOOL daNpc_Ji1_c::MoveToPlayer(f32, u8) {
    /* Nonmatching */
}

/* 00007A80-00007B14       .text teachSubActionAttackInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::teachSubActionAttackInit() {
    /* Nonmatching */

    setAnm(0x7, 0.0f, 0);
    field_0x330->setPlaySpeed(0.4f);
    fopAcM_seStart(this, JA_SE_CV_JI_ATTACK, 0);
}

/* 00007B14-00007D2C       .text teachSubActionAttack__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::teachSubActionAttack() {
    /* Nonmatching */
}

/* 00007D2C-00007D8C       .text teachSubActionJumpInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::teachSubActionJumpInit() {
    setAnm(0xB, 0.0f, 1);
    field_0xC9C = 0;
    field_0xD38 = current.pos;
}

/* 00007D8C-00007F14       .text teachSubActionJump__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::teachSubActionJump() {
    /* Nonmatching */
}

/* 00007F14-00009070       .text teachAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::teachAction(void*) {
    /* Nonmatching */
}

/* 00009070-00009B64       .text teachSPRollCutAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::teachSPRollCutAction(void*) {
    /* Nonmatching */

    daPy_py_c* player = daPy_getPlayerActorClass();

    if(field_0xC78 == 0) {
        dComIfGp_setItemMagicCount(dComIfGs_getMaxMagic());
        setAnm(5, 0.0f, 0);
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
        field_0xC90 = 0;
        field_0xD34 = 0;
        field_0xC30 = 0;
        dComIfGs_onTmpBit(0x402);
        field_0xD70 = 6;
        field_0xC78++;
    }
    else if(field_0xC78 != -1) {
        dComIfGp_setItemMagicCount(dComIfGs_getMaxMagic());
        if(daNpc_Ji1_plRoomOutCheck()) {
            field_0xC84 = 9;
            setAction(&daNpc_Ji1_c::eventAction, 0);
            field_0x2C8 = &daNpc_Ji1_c::teachSPRollCutAction;

            return true;
        }
        else {
            cXyz temp = player->current.pos - current.pos;
            cM_atan2s(temp.x, temp.z);
            f32 what = temp.absXZ();

            s32 cutType = player->getCutType();
            f32 y_diff = std::fabsf(temp.y);
            if(cutType == 9 && y_diff < 20.0f) {
                dComIfGs_onEventBit(0xB20);
                dComIfGs_offTmpBit(0x402);
                dComIfGp_setItemBeastNumCount(3, -10);
                field_0x7E0.OffTgShield();
                field_0xC84 = 10;

                setAction(&daNpc_Ji1_c::eventAction, 0);
                field_0x2C8 = &daNpc_Ji1_c::teachSPRollCutAction;
                
                return TRUE;
            }
            
            if(cutType == 8) {
                field_0xC84 = 0xB;

                setAction(&daNpc_Ji1_c::eventAction, 0);
                field_0x2C8 = &daNpc_Ji1_c::teachSPRollCutAction;

                return TRUE;
            }

            field_0x7E0.OnTgShield();
            if(field_0x7E0.ChkTgHit() && field_0xD6C != 1) {
                switch(field_0xC24) {
                    case 1:
                    case 6:
                    case 8:
                        setAnm(8, 0.0f, 1);
                        break;
                    case 9:
                        break;
                    case 10:
                        setAnm(10, 0.0f, 1);
                        field_0xC9C = 0;
                        field_0xD38 = current.pos;
                        break;
                    default:
                        setAnm(9, 0.0f, 1);
                }

                if(field_0xC24 == 9) {
                    setHitParticle(0, 0x4833);
                    field_0xC9C = 0;
                    field_0xD38 = current.pos;
                    setParticle(0x10, 1.0f, 0.1f);
                }
                else {
                    setGuardParticle();
                }

                field_0xD6C = 1;
                field_0xC8C = field_0xC24;
            }

            if(field_0xD6C == 1) {
                if(!player->getCutAtFlg() || field_0x330->getFrame() > field_0x330->getEndFrame() - 2.0f) {
                    if(field_0xC90 == 0) {
                        if(field_0xC8C == 9) {
                            field_0xC84 = 0xA;

                            setAction(&daNpc_Ji1_c::eventAction, 0);

                            field_0x2C8 = &daNpc_Ji1_c::normalAction;

                            return true;
                        }

                        fopAcM_orderOtherEventId(this, field_0xC54[3]);
                        eventInfo.onCondition(dEvtCnd_UNK2_e);
                        field_0xC90 = 2;
                    }
                }

                if(field_0xD64 == 10 && field_0xC8C == 9) {
                    cLib_addCalc2(&field_0xC9C, l_HIO.field_0x34 * 2.0f, 0.25f, l_HIO.field_0x38);
                    cXyz temp(field_0xD38);
                    temp.x -= field_0xC9C * cM_ssin(current.angle.y);
                    temp.z -= field_0xC9C * cM_scos(current.angle.y);

                    f32 temp2 = 45.0f;
                    if(field_0x434.ChkWallHit()) {
                        temp2 = 10.0f;
                    }

                    cLib_addCalcPos2(&current.pos, temp, 0.8f, temp2);
                    fopAcM_seStart(this, JA_SE_CM_JI_SLIP, 0);
                }

                if(field_0x330->getFrame() > field_0x330->getEndFrame() - 2.0f) {
                    field_0x6B0.OffTgShield();
                    field_0x7E0.OnTgShield();
                    if(field_0xC90 == 2) {
                        field_0xD6C = 0;
                        field_0xC9C = 0.0f;
                        field_0xD38 = current.pos;

                        field_0xC4C = 0.0f;
                        field_0xC50 = 0.0f;
                        field_0xC2C = 0.0f;

                        setAction(&daNpc_Ji1_c::speakBadAction, 0);
                    }
                    else {
                        field_0xC90 = 0;
                        field_0xD6C = 0;
                        field_0xC9C = 0.0f;
                        field_0xD38 = current.pos;

                        setAction(&daNpc_Ji1_c::speakAction, 0);
                    }
                }
            }
            else {
                if(!teachSpRollCutMove(1.0f)) {
                    if(field_0x330->checkFrame(field_0x330->getEndFrame() - 2.0f)) {
                        setAnm(5, 4.0f, 0);
                    }
                }
            }
            
            if(field_0xD6C != 1) {
                dtParticle();
            }
            if(field_0xD6C != 1 && isGuardAnim()) {
                if(field_0x330->getFrame() > field_0x330->getEndFrame() - 2.0f) {
                    setAnm(5, 4.0f, 0);
                }
            }
        }
    }

    return true;
}

/* 00009B64-00009B7C       .text playerCutAtCheck__Fv */
static bool playerCutAtCheck() {
    /* Nonmatching */

    return daPy_getPlayerActorClass()->getCutAtFlg();
}

/* 00009B7C-00009F1C       .text battleGameSetTimer__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::battleGameSetTimer() {
    /* Nonmatching */
}

/* 00009F1C-0000A400       .text battleMove__11daNpc_Ji1_cFf */
void daNpc_Ji1_c::battleMove(f32) {
    /* Nonmatching */
}

/* 0000A400-0000A430       .text battleSubActionWaitInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::battleSubActionWaitInit() {
    /* Nonmatching */

    field_0xC9C = 0;
    setSubAction(&daNpc_Ji1_c::battleSubActionWait);
}

/* 0000A430-0000A564       .text battleSubActionWait__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::battleSubActionWait() {
    /* Nonmatching */
}

/* 0000A564-0000A5FC       .text battleSubActionNockBackInit__11daNpc_Ji1_cFi */
void daNpc_Ji1_c::battleSubActionNockBackInit(int param_1) {
    if(param_1) {
        setGuardParticle();
    }

    field_0xC9C = 0;
    field_0xD38 = current.pos;
    field_0x330->setPlaySpeed(-1.0f);
    setSubAction(&daNpc_Ji1_c::battleSubActionNockBack);
    field_0x2A4 = 30.0f;
}

/* 0000A5FC-0000A744       .text battleSubActionNockBack__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::battleSubActionNockBack() {
    /* Nonmatching */
}

/* 0000A744-0000A808       .text battleSubActionAttackInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::battleSubActionAttackInit() {
    /* Nonmatching */

    setAnm(0x7, 0.0f, 0);
    field_0x330->setPlaySpeed(l_HIO.field_0x6C);
    fopAcM_seStart(this, JA_SE_CV_JI_ATTACK, 0);
    field_0xC34 = 0;
    setSubAction(&daNpc_Ji1_c::battleSubActionYokoAttack);
}

/* 0000A808-0000AAA4       .text battleSubActionAttack__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::battleSubActionAttack() {
    /* Nonmatching */
}

/* 0000AAA4-0000AB68       .text battleSubActionTateAttackInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::battleSubActionTateAttackInit() {
    /* Nonmatching */

    setAnm(0x13, 0.0f, 0);
    field_0x330->setPlaySpeed(l_HIO.field_0x78);
    fopAcM_seStart(this, JA_SE_CV_JI_ATTACK, 0);
    field_0xC34 = 0;
    setSubAction(&daNpc_Ji1_c::battleSubActionYokoAttack);
}

/* 0000AB68-0000AE2C       .text battleSubActionTateAttack__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::battleSubActionTateAttack() {
    /* Nonmatching */
}

/* 0000AE2C-0000AEF0       .text battleSubActionYokoAttackInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::battleSubActionYokoAttackInit() {
    /* Nonmatching */

    setAnm(0x14, 0.0f, 0);
    field_0x330->setPlaySpeed(l_HIO.field_0x80);
    fopAcM_seStart(this, JA_SE_CV_JI_ATTACK, 0);
    field_0xC34 = 0;
    setSubAction(&daNpc_Ji1_c::battleSubActionYokoAttack);
}

/* 0000AEF0-0000B254       .text battleSubActionYokoAttack__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::battleSubActionYokoAttack() {
    /* Nonmatching */
}

/* 0000B254-0000B2D4       .text battleSubActionJumpInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::battleSubActionJumpInit() {
    /* Nonmatching */

    setAnm(0xB, 0.0f, 1);
    field_0xC9C = 0;
    field_0xD38 = current.pos;
    setSubAction(&daNpc_Ji1_c::battleSubActionJump);
}

/* 0000B2D4-0000B5EC       .text battleSubActionJump__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::battleSubActionJump() {
    /* Nonmatching */
}

/* 0000B5EC-0000B67C       .text battleSubActionDamageInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::battleSubActionDamageInit() {
    /* Nonmatching */

    setAnm(0x19, 0.0f, 1);
    field_0x330->setPlaySpeed(1.5f);
    field_0xC9C = 0;
    field_0xD38 = current.pos;
    setSubAction(&daNpc_Ji1_c::battleSubActionDamage);
}

/* 0000B67C-0000B8AC       .text battleSubActionDamage__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::battleSubActionDamage() {
    /* Nonmatching */
}

/* 0000B8AC-0000B92C       .text battleSubActionJpGuardInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::battleSubActionJpGuardInit() {
    /* Nonmatching */

    setAnm(0xA, 0.0f, 1);
    field_0xC9C = 0;
    field_0xD38 = current.pos;
    setSubAction(&daNpc_Ji1_c::battleSubActionJpGuard);
}

/* 0000B92C-0000BAEC       .text battleSubActionJpGuard__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::battleSubActionJpGuard() {
    /* Nonmatching */
}

/* 0000BAEC-0000BB6C       .text battleSubActionGuardInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::battleSubActionGuardInit() {
    /* Nonmatching */

    field_0xC9C = 0;
    field_0xD38 = current.pos;
    setParticle(0x10, 1.0f, 0.1f);
    setSubAction(&daNpc_Ji1_c::battleSubActionGuard);
}

/* 0000BB6C-0000BD8C       .text battleSubActionGuard__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::battleSubActionGuard() {
    /* Nonmatching */
}

/* 0000BD8C-0000BFE0       .text battleAtSet__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::battleAtSet() {
    /* Nonmatching */
}

/* 0000BFE0-0000C7E4       .text battleGuardCheck__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::battleGuardCheck() {
    /* Nonmatching */

    if(field_0x7E0.ChkTgHit() && field_0xD6C != 1) {
        switch(field_0xC24) {
            case 0xF:
            case 0x10:
                battleSubActionJumpInit();
                break;
            case 5:
                current.angle.y += 0x8000;
                battleSubActionDamageInit();
                break;
            case 0x1:
            case 0x6:
            case 0x8:
            case 0x9:
            case 0x1A: {
                if(!isAttackAnim()) {
                    if(!checkSubAction(&daNpc_Ji1_c::battleSubActionNockBack)) {
                        setAnm(8, 0.0f, 1);
                        battleSubActionGuardInit();
                        break;
                    }
                }

                int attackFrame = isAttackFrame();
                if(checkSubAction(&daNpc_Ji1_c::battleSubActionNockBack)) {
                    setAnm(8, 0.0f, 1);
                    battleSubActionGuardInit();
                }
                else {
                    if(attackFrame == 0) {
                        battleSubActionNockBackInit(1);
                        field_0xD6C = 1;
                        return 0;
                    }
                    
                    if(attackFrame == 1) {
                        setAnm(8, 0.0f, 1);
                        battleSubActionGuardInit();
                        break;
                    }

                    return 0;
                }

                break;
            }
            case 0xA:
                battleSubActionJpGuardInit();
                break;
            case 0x0:
            case 0x2:
            case 0x3:
            case 0x4:
            case 0x7:
            case 0xB:
            case 0xC:
            case 0xD:
            case 0xE:
            case 0x11:
            case 0x12:
            case 0x13:
            case 0x14:
            case 0x15:
            case 0x16:
            case 0x17:
            case 0x18:
            case 0x19:
            case 0x1B:
            case 0x1C:
            case 0x1D:
            case 0x1E:
            case 0x1F:
            default: {
                if(!isAttackAnim()) {
                    if(!checkSubAction(&daNpc_Ji1_c::battleSubActionNockBack)) {
                        setAnm(9, 0.0f, 1);
                        battleSubActionGuardInit();
                        break;
                    }
                }

                int attackFrame = isAttackFrame();
                if(checkSubAction(&daNpc_Ji1_c::battleSubActionNockBack)) {
                    setAnm(9, 0.0f, 1);
                    battleSubActionGuardInit();
                }
                else {
                    if(attackFrame == 0) {
                        battleSubActionNockBackInit(1);
                        field_0xD6C = 1;
                        return 0;
                    }
                    
                    if(attackFrame == 1) {
                        setAnm(9, 0.0f, 1);
                        battleSubActionGuardInit();
                        break;
                    }

                    return 0;
                }

                break;
            }
        }
        
        if(field_0xC24 == 0) {
            setGuardParticle();
        }
        else {
            if(field_0xC24 == 0xF || field_0xC24 == 0x10 || field_0xC24 == 0x5) {
                fopAcM_seStart(this, JA_SE_LK_SW_CRT_HIT, 0);

                static cXyz scale(1.25f, 1.25f, 1.25f);
                if(field_0xC24 == 5) {
                    setHitParticle(&scale, JA_SE_CV_JI_FUTTOBI);
                }
                else {
                    setHitParticle(&scale, JA_SE_CV_JI_DEFENCE);
                }

                if(field_0xD70 < l_HIO.field_0x60[3] - 1) {
                    field_0xD70 += 2;
                    
                    dComIfGp_plusMiniGameRupee(2);
                }
                else {
                    field_0xD70 += 1;
                    
                    dComIfGp_plusMiniGameRupee(1);
                }
            }
            else {
                setHitParticle(0, JA_SE_CV_JI_DEFENCE);
                field_0xD70 += 1;
                
                dComIfGp_plusMiniGameRupee(1);
            }

            if(field_0xD70 >= l_HIO.field_0x60[3]) {
                field_0xC84 = 8;
                if(dComIfGs_isEventBit(0xF20)) {
                    field_0xC38 = 2;
                }
                else if(dComIfGs_isEventBit(0xF10)) {
                    field_0xC38 = 0;
                }
                else {
                    field_0xC38 = 1;
                }

                setAction(&daNpc_Ji1_c::eventAction, 0);

                dComIfGp_setMessageCountNumber(field_0xD70);
                field_0x2C8 = &daNpc_Ji1_c::normalAction;
                if (dComIfG_getTimerPtr()) {
                    dComIfG_TimerDeleteRequest();
                    setClearRecord(field_0xD70);
                }

                return TRUE;
            }
        }

        field_0xD6C = 1;
        field_0x2A4 = 30.0f;
    }

    if(!field_0xA40.ChkAtShieldHit() && field_0xA40.ChkAtHit()) {
        field_0xA40.ClrAtHit();
    }

    if(field_0xC3C > 2) {
        if(checkAction(&daNpc_Ji1_c::battleAction)) {
            dComIfG_TimerDeleteRequest();
            
            if(isClearRecord(field_0xD70)) {
                setClearRecord(field_0xD70);
                field_0xC84 = 7;

                setAction(&daNpc_Ji1_c::eventAction, 0);

                dComIfGp_setMessageCountNumber(field_0xD70);
                field_0x2C8 = &daNpc_Ji1_c::normalAction;
            }
            else {
                setAction(&daNpc_Ji1_c::endspeakAction, 0);
            }
        }
    }

    return TRUE;
}

/* 0000C7E4-0000CA98       .text battleAction__11daNpc_Ji1_cFPv */
BOOL daNpc_Ji1_c::battleAction(void*) {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    if(field_0xC78 == 0) {
        u8 icon;
        switch(dComIfGs_getSelectEquip(0)) {
            case dItem_SWORD_e:
                icon = 1;
                break;
                icon = 2;
                break;
            case dItem_MASTER_SWORD_2_e:
                icon = 2;
                break;
            case dItem_MASTER_SWORD_1_e:
            default:
                icon = 2;
                break;
        }

        dTimer_createTimer(6, 1000, 2, icon, 221.0f, 439.0f, 32.0f, 419.0f);
        dComIfGp_setMiniGameRupee(0);
        field_0xC3C = 0;
        setAnm(5, 0.0f, 0);
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
        attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 3;
        field_0xC30 = (s16)cM_rndF(150.0f) + 30;
        field_0xD70 = 0;
        field_0xD6C = 0;
        battleSubActionWaitInit();
        field_0xC38 = 0;
        field_0xC78++;
    }
    else if(field_0xC78 == -1) {
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
        attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 0xB5;
    }
    else {
        cXyz temp = player->current.pos - current.pos;
        cM_atan2s(temp.x, temp.z);
        f32 what = temp.absXZ();
        field_0x7E0.OffTgShield();
        battleGuardCheck();
        (this->*field_0x2D4)();

        if(field_0xD6C != 1) {
            dtParticle();
        }

        if(!isAttackAnim() || checkSubAction(&daNpc_Ji1_c::battleSubActionNockBack)) {
            dtParticleAT();
        }

        game_life_point = cLib_minLimit<int>(3 - field_0xC3C, 0);
    }

    return true;
}

/* 0000CA98-0000CC28       .text checkCutType__11daNpc_Ji1_cFii */
BOOL daNpc_Ji1_c::checkCutType(int param_1, int param_2) {
    daPy_py_c* player = daPy_getPlayerActorClass();

    BOOL ret = false;
    switch(param_2) {
        case 0:
            switch(param_1) {
                case 3:
                case 7:
                case 0x1A:
                case 0x1B:
                case 0x1E:
                case 0x1F:
                    ret = true;
                    break;
                case 8:
                    if(player->checkComboCutTurn()) {
                        ret = true;
                    }
                    break;
                default:
                    break;
            }

            break;
        case 1:
            switch(param_1) {
                case 0:
                case 3:
                case 6:
                case 0x1A:
                case 0x1B:
                case 0x1E:
                case 0x1F:
                    ret = true;
                    break;
                case 8:
                    if(player->checkComboCutTurn()) {
                        ret = true;
                    }
                    break;
                default:
                    break;
            }

            break;
        case 2:
            switch(param_1) {
                case 0:
                case 3:
                case 6:
                case 0x1A:
                case 0x1B:
                case 0x1E:
                case 0x1F:
                    ret = true;
                    break;
                case 8:
                    if(player->checkComboCutTurn()) {
                        ret = true;
                    }
                    break;
                default:
                    break;
            }

            break;
        case 3:
            switch(param_1) {
                case 8:
                case 9:
                    ret = true;
                    break;
                default:
                    break;
            }

            break;
        case 4:
            switch(param_1) {
                case 5:
                case 0xF:
                case 0x10:
                    ret = true;
                    break;
                default:
                    break;
            }

            break;
        default:
            switch(param_1) {
                case 0xA:
                    ret = true;
                    break;
            }

            break;
    }

    return ret;
}

/* 0000CC28-0000CF28       .text setAnimFromMsgNo__11daNpc_Ji1_cFUl */
void daNpc_Ji1_c::setAnimFromMsgNo(u32 msgNo) {
    /* Nonmatching */

    if(l_msg) {
        msgNo = l_msg->mMsgNo;
    }

    // the switch cases for this are annoying to work out
    switch(msgNo) {
        case 0x9B1:
            if(field_0xD84 == 1) {
                setAnm(0, 4.0f, 0);
                return;
            }

            setAnm(1, 4.0f, 0);
            return;
        case 0x961:
        case 0x986:
            setAnm(3, 8.0f, 0);
            return;
        case 0x962:
            setAnm(3, 4.0f, 0);
            return;
        case 0x9AF:
        case 0x9B3:
        case 0x9B4:
            if(field_0xD84 == 1) {
                setAnm(0, 4.0f, 0);
                return;
            }

            setAnm(2, 4.0f, 0);
            return;
        case 0x963:
        case 0x964:
        case 0x965:
        case 0x966:
        case 0x967:
        case 0x968:
            setAnm(2, 4.0f, 0);
            return;
        case 0x975:
            setAnm(4, 4.0f, 0);
            return;
        case 0x9AE:
            if(field_0xD64 == 0x16 && field_0x330->checkFrame(field_0x330->getEndFrame() - 1)) {
                setAnm(0x15, l_HIO.field_0xA8, 0);
                return;
            }

            if(field_0xD64 != 0x15) {
                setAnm(0x16, l_HIO.field_0xA4, 0);
            }

            return;
        case 0x9B9:
            if(l_msg->mStatus != 0xE) {
                return;
            }
            if(field_0xD64 != 0x17) {
                return;
            }

            if(field_0x430 != 0) {
                field_0x430->becomeInvalidEmitter();
                field_0x430 = 0;
                field_0x430 = dComIfGp_particle_set(dPa_name::ID_SCENE_81A5, &current.pos);
            }

            setAnm(0x18, 8.0f, 0);
            field_0xD84 = 1;

            return;
    }
}

/* 0000CF28-0000DAB0       .text setAnm__11daNpc_Ji1_cFifi */
BOOL daNpc_Ji1_c::setAnm(int param_1, f32 param_2, int param_3) {
    /* Nonmatching */

    if(param_3 == 0 & field_0xD64 - param_1 == 0) {
        return false;
    }
    else {
        field_0xD64 = param_1;

        f32 speed = 1.0f;
        if(param_1 != field_0xD64 && isGuardAnim()) {
            fopAcM_seStart(this, JA_SE_CM_JI_DEFENSE, 0);
        }

        J3DAnmTransform* bckAnm;
        s32 loopMode;
        void* pSoundAnimRes;

        switch(param_1) {
            case 0:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_WAIT01));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_WAIT01);

                break;
            case 1:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_WAIT02));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_WAIT02);

                break;
            case 2:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_TALK01));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_TALK01);

                break;
            case 3:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_TALK02));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_TALK02);

                break;
            case 4:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_AKIRE));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_AKIRE);

                break;
            case 5:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_KAMAE));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_KAMAE);

                break;
            case 6:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_KROT));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_KROT);
                speed = l_HIO.field_0x48;

                break;
            case 7:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_INASI));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_INASI);
                speed = l_HIO.field_0x44;

                break;
            case 8:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_TATEGUARD));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_TATEGUARD);

                break;
            case 9:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_YKGUARD));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_YKGUARD);

                break;
            case 10:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_JPGUARD));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_JPGUARD);

                break;
            case 11:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_TOKAMAE));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_TOKAMAE);

                break;
            case 12:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_REI));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_REI);

                break;
            case 13:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_WARAI));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_WARAI);
                speed = l_HIO.field_0x4C;

                break;
            case 14:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_JPGUARD));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_JPGUARD);
                speed = 2.0f;

                break;
            case 15:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_GUARD));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_GUARD);
                speed = 2.0f;

                break;
            case 16:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_BTKAMASI));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_BTKAMASI);

                break;
            case 17:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_BTKAMAE));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_BTKAMAE);

                break;
            case 18:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_UDEGUMI));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_UDEGUMI);

                break;
            case 19:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_TATEATTACK));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_TATEATTACK);

                break;
            case 20:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_YOKOATTACK));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_YOKOATTACK);

                break;
            case 21:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_ODOROKU));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_ODOROKU);

                break;
            case 22:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_BIBIRI));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_BIBIRI);

                BackSlideInit();
                if(field_0xD84 == 1) {
                    harpoonRelease(0);
                }

                break;
            case 23:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_NAKU));
                loopMode = J3DFrameCtrl::EMode_LOOP;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_NAKU);

                if(field_0x430 == 0) {
                    field_0x430 = dComIfGp_particle_set(dPa_name::ID_SCENE_81A4, &current.pos);
                    harpoonRelease(0);
                }

                break;
            case 24:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_NUGUI));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_NUGUI);

                break;
            case 25:
                bckAnm = static_cast<J3DAnmTransform*>(dComIfG_getObjectRes("Ji", JI_BCK_JI_DAMAGE));
                loopMode = J3DFrameCtrl::EMode_NONE;
                pSoundAnimRes = dComIfG_getObjectRes("Ji", JI_BAS_JI_DAMAGE);

                break;
            default:
                return 0;
        }

        field_0x330->setAnm(bckAnm, loopMode, param_2, speed, 0.0f, -1.0f, pSoundAnimRes);
        if(field_0xD64 == 0x13) {
            mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Ji", JI_BCK_JIYARI_TATEATTACK), J3DFrameCtrl::EMode_LOOP, 0.0f, 1.0f, 0.0f, -1.0f, NULL);
        }
        else if(field_0xD64 == 0x14) {
            mpMorf->setAnm((J3DAnmTransform*)dComIfG_getObjectRes("Ji", JI_BCK_JIYARI_YOKOATTACK), J3DFrameCtrl::EMode_LOOP, 0.0f, 1.0f, 0.0f, -1.0f, NULL);
        }

        return true;
    }
}

/* 0000DAB0-0000DC04       .text nodeCallBack1__FP7J3DNodei */
static BOOL nodeCallBack1(J3DNode* node, int calcTiming) {
    /* Nonmatching */

    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Ji1_c* i_this = (daNpc_Ji1_c*)model->getUserArea();
        s32 jntNo = joint->getJntNo();

        if(i_this) {
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            if(jntNo == i_this->m_jnt.getHeadJntNum()) {
                mDoMtx_stack_c::XrotM(i_this->field_0xBFC.field_0x02 + i_this->m_jnt.getHead_y());
                mDoMtx_stack_c::ZrotM(i_this->field_0xBFC.field_0x00 - i_this->m_jnt.getHead_x());
            }
            if(jntNo == i_this->m_jnt.getBackboneJntNum()) {
                mDoMtx_stack_c::XrotM(i_this->m_jnt.getBackbone_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getBackbone_x());

                for(int i = 0; i < 3; i++) {
                    mDoMtx_stack_c::multVec(&l_HIO.field_0xC4[i], &i_this->field_0xBD8[i]);
                }
            }

            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        }
    }
    
    return true;
}

/* 0000DC04-0000DD68       .text nodeCallBack2__FP7J3DNodei */
static BOOL nodeCallBack2(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Ji1_c* i_this = (daNpc_Ji1_c*)model->getUserArea();
        s32 jntNo = joint->getJntNo();

        if(i_this) {
            cMtx_copy(model->getAnmMtx(jntNo), *calc_mtx);
            if(jntNo == i_this->hair1JointNo) {
                mDoMtx_ZrotM(*calc_mtx, i_this->field_0xBAA + i_this->field_0xBD2);
                mDoMtx_YrotM(*calc_mtx, i_this->field_0xBAC);
            }
            else if(jntNo == i_this->hair2JointNo) {
                mDoMtx_ZrotM(*calc_mtx, i_this->field_0xBAE + i_this->field_0xBD4);
                mDoMtx_YrotM(*calc_mtx, i_this->field_0xBB0);
            }
            else {
                mDoMtx_ZrotM(*calc_mtx, i_this->field_0xBB2 + i_this->field_0xBD6);
                mDoMtx_YrotM(*calc_mtx, i_this->field_0xBB4);
            }

            model->setAnmMtx(jntNo, *calc_mtx);
            cMtx_copy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    
    return true;
}

/* 0000DD68-0000DE90       .text nodeCallBack3__FP7J3DNodei */
static BOOL nodeCallBack3(J3DNode* node, int calcTiming) {
    if (calcTiming != J3DNodeCBCalcTiming_In) {
        return true;
    }
    else {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Ji1_c* i_this = (daNpc_Ji1_c*)model->getUserArea();

        s32 jntNo = joint->getJntNo();
        mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
        s16 temp = i_this->field_0xBA2 * cM_ssin(i_this->field_0xBA4);
        if(jntNo == i_this->armLJointNo) {
            mDoMtx_stack_c::XrotM(temp);
        }
        else if(jntNo == i_this->armRJointNo) {
            mDoMtx_stack_c::XrotM(temp);
        }

        model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
        
        return true;
    }
}

/* 0000DE90-0000DEB0       .text daNpc_Ji1_Draw__FP11daNpc_Ji1_c */
static BOOL daNpc_Ji1_Draw(daNpc_Ji1_c* i_this) {
    return i_this->_draw();
}

/* 0000DEB0-0000DED0       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Ji1_c*>(i_this)->CreateHeap();
}

/* 0000DED0-0000DF78       .text _create__11daNpc_Ji1_cFv */
cPhs_State daNpc_Ji1_c::_create() {
    fopAcM_SetupActor(this, daNpc_Ji1_c);

    cPhs_State state = dComIfG_resLoad(&field_0xC7C, "Ji");
    if(state == cPhs_COMPLEATE_e) {
        if(!fopAcM_entrySolidHeap(this, &CheckCreateHeap, 0x16840)) {
            return cPhs_ERROR_e;
        }

        CreateInit();
    }

    return state;
}

/* 0000E864-0000F324       .text CreateHeap__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::CreateHeap() {
    /* Nonmatching */

    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Ji", JI_BDL_JI));
    field_0x330 = new mDoExt_McaMorf(
        modelData,
        NULL, NULL,
        static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes("Ji", JI_BCK_WAIT01)),
        J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 1,
        dComIfG_getObjectRes("Ji", JI_BAS_WAIT01),
        0x00000000,
        0x11020203
    );

    if(field_0x330 == NULL || field_0x330->getModel() == NULL) {
        return false;
    }

    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(current.angle.y);
    field_0x330->getModel()->setBaseTRMtx(mDoMtx_stack_c::get());

    m_jnt.setHeadJntNum(modelData->getJointName()->getIndex("head"));
    JUT_ASSERT(0x15AB, m_jnt.getHeadJntNum() >= 0);

    m_jnt.setBackboneJntNum(modelData->getJointName()->getIndex("backbone1"));
    JUT_ASSERT(0x15B0, m_jnt.getBackboneJntNum() >= 0);

    armLJointNo = modelData->getJointName()->getIndex("armL1");
    JUT_ASSERT(0x15B4, armLJointNo >= 0);

    armRJointNo = modelData->getJointName()->getIndex("armR1");
    JUT_ASSERT(0x15B7, armRJointNo >= 0);

    handRJointNo = modelData->getJointName()->getIndex("handR");
    JUT_ASSERT(0x15BA, handRJointNo >= 0);

    mpMorf = new mDoExt_McaMorf(
        static_cast<J3DModelData*>(dComIfG_getObjectRes("Ji", JI_BDL_JI_YARI)),
        NULL, NULL,
        static_cast<J3DAnmTransformKey*>(dComIfG_getObjectRes("Ji", JI_BCK_JIYARI_TATEATTACK)),
        J3DFrameCtrl::EMode_NONE, 0.0f, 0, -1, 1,
        0,
        0x00000000,
        0x11020203
    );


    if(mpMorf == NULL || mpMorf->getModel() == NULL) {
        return false;
    }

    modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Ji", JI_BDL_YJITR00));
    field_0x3F8 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);

    J3DAnmTevRegKey* a_brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes("Ji", JI_BRK_YJITR00));
    JUT_ASSERT(0x15CD, a_brk != NULL);

    J3DAnmTextureSRTKey* a_btk = static_cast<J3DAnmTextureSRTKey*>(dComIfG_getObjectRes("Ji", JI_BTK_YJITR00));
    JUT_ASSERT(0x15D0, a_btk != NULL);

    int temp1 = field_0x3FC.init(modelData, a_brk, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);
    int temp2 = field_0x418.init(modelData, a_btk, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0);

    if(field_0x3F8 == 0 || temp1 == 0 || temp2 == 0) {
        return false;
    }

    headTexPattern = static_cast<J3DAnmTexPattern*>(dComIfG_getObjectRes("Ji", JI_BTP_JI));
    JUT_ASSERT(0x15D8, headTexPattern != NULL);

    if(field_0x3D8.init(modelData, headTexPattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, 0) == 0) {
        return false;
    }

    hair1JointNo = modelData->getJointName()->getIndex("hair1");
    JUT_ASSERT(0x15DF, hair1JointNo >= 0);
    hair2JointNo = modelData->getJointName()->getIndex("hair2");
    JUT_ASSERT(0x15E1, hair2JointNo >= 0);
    hair3JointNo = modelData->getJointName()->getIndex("hair3");
    JUT_ASSERT(0x15E3, hair3JointNo >= 0);

    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == hair1JointNo || i == hair2JointNo || i == hair3JointNo) {
            modelData->getJointNodePointer(i)->setCallBack(nodeCallBack2);
        }
    }
    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        if(i == m_jnt.getHeadJntNum() || i == m_jnt.getBackboneJntNum()) {
            modelData->getJointNodePointer(i)->setCallBack(nodeCallBack1);
        }
        else if(i == armLJointNo || i == armRJointNo) {
            modelData->getJointNodePointer(i)->setCallBack(nodeCallBack3);
        }
    }

    field_0x330->getModel()->setUserArea((u32)this);

    field_0x5F8.SetWall(60.0f, 50.0f);
    field_0x434.Set(&current.pos, &old.pos, this, 1, &field_0x5F8, &speed);
    field_0x434.OnLineCheck();

    field_0xC54[0] = dComIfGp_evmng_getEventIdx("Ji1_StartSpeak");
    field_0xC54[1] = dComIfGp_evmng_getEventIdx("Ji1_Speak");
    field_0xC54[2] = dComIfGp_evmng_getEventIdx("Ji1_EndSpeak");
    field_0xC54[3] = dComIfGp_evmng_getEventIdx("Ji1_BadSpeak");
    field_0xC54[4] = dComIfGp_evmng_getEventIdx("Ji1_linkmove");
    field_0xC54[5] = dComIfGp_evmng_getEventIdx("Ji1_kaiten");
    field_0xC54[6] = dComIfGp_evmng_getEventIdx("Ji1_kaiten_exp");
    field_0xC54[7] = dComIfGp_evmng_getEventIdx("Ji1_ItemGetEnd");
    field_0xC54[8] = dComIfGp_evmng_getEventIdx("Ji1_ItemGetTalkEnd");
    field_0xC54[9] = dComIfGp_evmng_getEventIdx("Ji1_pl_backroom");
    field_0xC54[0xA] = dComIfGp_evmng_getEventIdx("Ji1_TeachSpRollCut");
    field_0xC54[0xB] = dComIfGp_evmng_getEventIdx("Ji1_SpRollFail");
    field_0xC54[0xC] = dComIfGp_evmng_getEventIdx("Ji1_NormAng");
    field_0xC54[0xD] = dComIfGp_evmng_getEventIdx("Ji1_NormAng2");
    field_0xC54[0xE] = dComIfGp_evmng_getEventIdx("Ji1_NormAngFin");
    field_0xC54[0xF] = dComIfGp_evmng_getEventIdx("Ji1_SwordGetTalkEnd");
    field_0xC54[0x10] = dComIfGp_evmng_getEventIdx("Ji1_KmonTalk");
    field_0xC54[0x11] = dComIfGp_evmng_getEventIdx("Ji1_EquipTalk");

    if(dComIfGs_isEventBit(0x1) && !dComIfGs_isEventBit(0x108)) {
        eventInfo.setEventId(field_0xC54[0x11]);
    }

    return true;
}

/* 0000F324-0000FB0C       .text CreateInit__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::CreateInit() {
    /* Nonmatching */

    cXyz temp(190.0f, 230.0f, -1100.0f);
    csXyz temp2(0, 0, 0);

    fopAcM_createChild("Kmon", fopAcM_GetID(this), 0, &temp, fopAcM_GetRoomNo(this), &temp2);
    fopAcM_SetMtx(this, field_0x330->getModel()->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -70.0f, 0.0f, -70.0f, 70.0f, 200.0f, 70.0f);
    gravity = -30.0f;
    attention_info.flags = fopAc_Attn_LOCKON_MISC_e | fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;

    field_0x638.Init(0xFF, 0xFF, this);
    field_0x674.Init(0xFF, 0xFF, this);
    field_0x6B0.Set(l_cyl_src);
    field_0x6B0.SetStts(&field_0x638);
    field_0x7E0.Set(l_cyl2_src);
    field_0x7E0.SetStts(&field_0x674);
    field_0x7E0.SetTgHitCallback(daJi1_TgHitCallback);
    field_0x7E0.SetCoHitCallback(daJi1_CoHitCallback);
    field_0x6B0.OffTgShield();
    field_0x7E0.OnTgShield();
    field_0x910.Set(l_cylAt_src);
    field_0x910.SetStts(&field_0x638);
    field_0xA40.Set(l_cpsAt_src);
    field_0xA40.SetStts(&field_0x638);
    field_0xA40.SetStartEnd(field_0xB84, field_0xB78);
    field_0xA40.SetR(50.0f);
    field_0xA40.SetAtHitCallback(daJi1_AtHitCallback);

    field_0x290 = 240.0f;
    field_0x294 = 100.0f;
    field_0xD64 = -1;
    field_0xD68 = 0;
    field_0xD6C = 0;
    field_0xD70 = 0;
    field_0xD74 = 0;
    field_0xD78 = 0;
    field_0xD79 = 0;
    field_0xC94 = 0;
    field_0xC90 = 0;
    field_0xC98 = l_HIO.field_0x54[field_0xD70];
    field_0xC28 = 0;
    field_0xC2C = 0;
    field_0xC4C = 0;
    field_0xC50 = 0;
    field_0xC9C = 0;

    field_0xD38 = current.pos;
    if(dComIfGs_isEventBit(0x520)) {
        if(!dComIfGs_isEventBit(0x2)) {
            field_0xD84 = 0;
            field_0xD50.x = -13.0f;
            field_0xD50.y = -4.0f;
            field_0xD50.z = 10.0f;
            field_0xD5C.x = 0x4000;
            field_0xD5C.y = 0;
            field_0xD5C.z = 0x7FFF;
            current.pos.x = 0.0f;
            current.pos.y = 0.0f;
            current.pos.z = -850.0f;
            current.angle.y = -0x8000;

            setAction(&daNpc_Ji1_c::kaitenExpAction, 0);
        }
        else {
            field_0xD84 = 1;
            field_0xD50.x = -13.0f;
            field_0xD50.y = -4.0f;
            field_0xD50.z = 10.0f;
            field_0xD5C.x = 0x4000;
            field_0xD5C.y = 0;
            field_0xD5C.z = 0x7FFF;

            setAction(&daNpc_Ji1_c::normalAction, 0);
        }

        field_0xD28 = home.pos;
    }
    else {
        if(dComIfGs_isEventBit(0x501) || dComIfGs_isEventBit(0x1)) {
            field_0xD84 = 1;
            field_0xD50.x = -13.0f;
            field_0xD50.y = -4.0f;
            field_0xD50.z = 10.0f;
            field_0xD5C.x = 0x4000;
            field_0xD5C.y = 0;
            field_0xD5C.z = 0x7FFF;
            field_0xD28 = home.pos;

            setAction(&daNpc_Ji1_c::normalAction, 0);
        }
        else {
            field_0xD84 = 0;
            if(!dComIfGs_isEventBit(0x640) || l_HIO.field_0x30) {
                field_0xD68 = 0;

                setAction(&daNpc_Ji1_c::kaitenExpAction, 0);
            }
            else {
                setAction(&daNpc_Ji1_c::kaitenwaitAction, 0);
            }
            
            current.pos.x = 0.0f;
            current.pos.y = 0.0f;
            current.pos.z = -850.0f;
            current.angle.y = -0x8000;
            field_0xD28 = current.pos;
            home.angle.y = current.angle.y;
        }
    }

    dComIfGp_att_offAleart();
    mEventCut.setActorInfo("Ji1", this);
    mEventCut.setJntCtrlPtr(&m_jnt);
    field_0xC84 = 0x12;
    field_0xD7B = 0;
    field_0xD7C = 0;
    field_0xD7E = 0;
    
    cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_MISC_e);
    attention_info.distances[fopAc_Attn_TYPE_TALK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_SPEAK_e] = 0xA9;
    attention_info.distances[fopAc_Attn_TYPE_BATTLE_e] = 0xB5;
    field_0x414 = 0.0f;
    field_0x42C = 0.0f;
    field_0x430 = 0;

    set_mtx();

    return true;
}

/* 0000FB0C-0000FC24       .text _delete__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::_delete() {
    if(dComIfGp_getMiniGameType() == 2) {
        dComIfGp_endMiniGame(2);
    }
    if(dComIfGp_getMiniGameType() == 6) {
        dComIfGp_endMiniGame(6);
    }

    dComIfG_resDelete(&field_0xC7C, "Ji");
    if(heap && field_0x330) {
        field_0x330->stopZelAnime();
    }

    mDoAud_seDeleteObject(&field_0xB78);
    mDoAud_seDeleteObject(&field_0xB84);
    
    dComIfGp_att_revivalAleart();

    field_0x2E0.remove();
    field_0x300.remove();

    return true;
}

/* 0000FC24-00010100       .text _execute__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::_execute() {
    /* Nonmatching */

    if(field_0xD84 == 2) {
        harpoonMove();
    }

    if(cLib_calcTimer(&field_0x3EE) == 0) {
        field_0x3EC++;
        if(field_0x3EC >= headTexPattern->getFrameMax()) {
            field_0x3EC -= headTexPattern->getFrameMax();
            field_0x3EE = (s16)cM_rndF(100.0f) + 30;
        }
    }

    s8 roomNo = fopAcM_GetRoomNo(this);
    u32 sound;
    if(field_0x434.ChkGroundHit()) {
        sound = dComIfG_Bgsp()->GetMtrlSndId(field_0x434.m_gnd);
    }
    else {
        sound = 0;
    }
    field_0x330->play(&current.pos, sound, dComIfGp_getReverb(roomNo));
    field_0x330->calc();

    if(isItemWaitAnim()) {
        static cXyz aim_offset(-13.0f, -4.0f, 10.0f);
        static csXyz aim_angle(0x4000, 0, 0x7FFF);

        field_0xD5C = aim_angle;
        cLib_addCalcPos2(&field_0xD50, aim_offset, 0.25f, 5.0f);
    }
    else {
        static cXyz aim_offset(-13.06f, -4.0f, 44.35f);
        static csXyz aim_angle(0x3E84, 0, 0x7E93);

        field_0xD5C = aim_angle;
        cLib_addCalcPos2(&field_0xD50, aim_offset, 0.25f, 5.0f);
    }

    if(field_0xD84 == 1 && (field_0xD64 == 0x13 || field_0xD64 == 0x14)) {
        mpMorf->setFrame(field_0x330->getFrame());
    }
    else {
        mpMorf->setFrame(0.0f);
        mpMorf->setPlaySpeed(0.0f);
    }

    mpMorf->calc();

    field_0xBFC.move();

    if(field_0xD64 == 0x17) {
        field_0x42C += 1.0f;
        if(field_0x42C >= 60.0f) {
            field_0x42C = 30.0f;
        }
    }
    else {
        if(field_0xD64 != 0x18 && field_0x430 != 0) {
            field_0x430->becomeInvalidEmitter();
            field_0x430 = 0;
        }

        if(field_0x42C > 0.0f) {
            field_0x414 += 1.0f;
            if(field_0x414 >= 30.0f) {
                field_0x42C = 0;
                field_0x414 = 0;
            }
        }
    }

    (this->*field_0x2B0)(0);
    lookBack();
    daNpc_Ji1_setHairAngle(this);

    attention_info.position.set(current.pos.x, current.pos.y + 190.0f, current.pos.z);
    shape_angle = current.angle;
    eyePos.set(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    fopAcM_posMoveF(this, field_0x638.GetCCMoveP());
    cXyz temp(current.pos);
    field_0x434.CrrPos(*dComIfG_Bgsp());
    field_0xC40 = current.pos - temp;
    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(field_0x434.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(field_0x434.m_gnd);
    set_mtx();
    field_0x6B0.SetC(current.pos);
    dComIfG_Ccsp()->Set(&field_0x6B0);
    field_0x7E0.SetC(current.pos);
    dComIfG_Ccsp()->Set(&field_0x7E0);
    field_0xC28 = 0;

    return true;
}

/* 00010100-0001031C       .text _draw__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::_draw() {
    /* Nonmatching */

    if(field_0xD85) {
        return true;
    }
    else {
        J3DModel* model1 = field_0x330->getModel();
        J3DModelData* modelData1 = model1->getModelData();
        J3DModel* model2 = mpMorf->getModel();

        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
        g_env_light.setLightTevColorType(model1, &tevStr);
        g_env_light.setLightTevColorType(model2, &tevStr);
        field_0x3D8.entry(modelData1, field_0x3EC);
        field_0x330->entryDL();
        if(field_0xD84 == 1) {
            mpMorf->entryDL();
        }
        else if(field_0xD84 == 2) {
            mpMorf->updateDL();
        }

        field_0x418.entry(field_0x3F8->getModelData(), (s16)field_0x42C);
        field_0x3FC.entry(field_0x3F8->getModelData(), (s16)field_0x414);
        mDoExt_modelUpdateDL(field_0x3F8);
        cXyz temp(current.pos.x, current.pos.y + 150.0f, current.pos.z);
        field_0x3F0 = dComIfGd_setShadow(
            field_0x3F0, 1, field_0x330->getModel(), &temp, 800.0f, 20.0f,
            current.pos.y, field_0x434.GetGroundH(), field_0x434.m_gnd, &tevStr
        );
        if(field_0x3F0 != 0 && field_0xD84 != 0) {
            dComIfGd_addRealShadow(field_0x3F0, mpMorf->getModel());
        }

        dSnap_RegistFig(DSNAP_TYPE_JI1, this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);
        
        return true;
    }
}

static cXyz l_head_front(0.0f, 1.0f, 0.0f);
static cXyz l_head_top(1.0f, 0.0f, 0.0f);

/* 0001031C-00010E3C       .text daNpc_Ji1_setHairAngle__FP11daNpc_Ji1_c */
static void daNpc_Ji1_setHairAngle(daNpc_Ji1_c* i_this) {
    /* Nonmatching */
}

/* 00010E3C-00010FC0       .text chkAttention__11daNpc_Ji1_cF4cXyzs */
BOOL daNpc_Ji1_c::chkAttention(cXyz param_1, s16 param_2) {
    daPy_py_c* player = daPy_getPlayerActorClass();
    f32 temp = 800.0f;
    s32 temp2 = l_HIO.field_0x10 + l_HIO.field_0x12;

    cXyz temp4;
    temp4.x = player->current.pos.x - param_1.x;
    temp4.z = player->current.pos.z - param_1.z;

    f32 dist = std::sqrtf(temp4.x * temp4.x + temp4.z * temp4.z);
    s16 angle = cM_atan2s(temp4.x, temp4.z);

    if(field_0xD7A != 0) {
        temp += 40.0f;
        temp2 += 0x71C;
    }

    angle -= param_2;
    field_0xD7A = temp2 > abs(angle) && temp > dist;
    
    return temp2 > abs(angle) && temp > dist;
}

/* 00010FC0-0001132C       .text lookBack__11daNpc_Ji1_cFv */
BOOL daNpc_Ji1_c::lookBack() {
    BOOL ret = false;

    daPy_py_c* player = daPy_getPlayerActorClass();

    cXyz temp = fopAcM_GetPosition(player) - fopAcM_GetPosition(this);
    f32 dist = temp.absXZ();

    bool temp2 = true;
    chkAttention(current.pos, current.angle.y);

    cXyz attnPos;
    if(mEventCut.getAttnFlag()) {
        attnPos = mEventCut.getAttnPos();
    }

    cXyz* dstPos;
    if(field_0xD7E) {
        attnPos = player->getLeftHandPos();
        dstPos = &attnPos;
    }
    else {
        if(
            (field_0xD7A != 0 || isGuardAnim()) ||
            (checkAction(&daNpc_Ji1_c::kaitenwaitAction) && !dComIfGs_isEventBit(0x501)) ||
            (!checkAction(&daNpc_Ji1_c::normalAction) && dist < 600.0f)
        ) {
            if(field_0xD64 == 0xD) {
                dstPos = 0;
            }
            else {
                attnPos = dNpc_playerEyePos(0.0f);
                dstPos = &attnPos;
            }
        }
        else {
            dstPos = 0;
        }
    }

    s16 maxHeadRot = l_HIO.field_0x10;
    s16 maxSpineRot = l_HIO.field_0x12;
    if(field_0xD64 == 0x10 || field_0xD64 == 0x11) {
        maxHeadRot = 0x3E80;
        maxSpineRot = 0x1F40;
    }

    m_jnt.setParam(l_HIO.field_0x0E, maxSpineRot, -l_HIO.field_0x0E, -maxHeadRot, l_HIO.field_0x0C, maxHeadRot, -l_HIO.field_0x0C, -maxHeadRot, l_HIO.field_0x14);
    if(m_jnt.trnChk()) {
        cLib_addCalcAngleS2(&field_0xC88, l_HIO.field_0x18, l_HIO.field_0x16, 0x800);
        temp2 = false;
        ret = true;
    }
    else {
        field_0xC88 = 0;
    }

    m_jnt.lookAtTarget(&current.angle.y, dstPos, eyePos, current.angle.y, field_0xC88, temp2);

    return ret;
}

/* 0001132C-000114EC       .text setHitParticle__11daNpc_Ji1_cFP4cXyzUl */
void daNpc_Ji1_c::setHitParticle(cXyz* param_1, u32 param_2) {
    /* Nonmatching */

    cXyz* pRVec = field_0x7E0.GetTgRVecP();
    cXyz scale(0.75f, 0.75f, 0.75f);
    csXyz angle;
    angle.y = cM_atan2s(pRVec->x, pRVec->z);
    angle.x = cM_atan2s(pRVec->z, pRVec->y);

    if(param_1) {
        scale = *param_1;
    }

    dComIfGp_particle_set(dPa_name::ID_COMMON_NORMAL_HIT, field_0x7E0.GetTgHitPosP(), &angle, &scale);
    dComIfGp_particle_set(dPa_name::ID_COMMON_0010, field_0x7E0.GetTgHitPosP(), 0, &scale);
    fopAcM_seStart(this, JA_SE_CM_JI_DAMAGE, 0);
    fopAcM_seStart(this, param_2, 0);
    dKy_SordFlush_set(*field_0x7E0.GetTgHitPosP(), 0);
}

/* 000114EC-0001161C       .text setGuardParticle__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::setGuardParticle() {
    dComIfGp_particle_set(dPa_name::ID_COMMON_PURPLE_HIT, field_0x7E0.GetTgHitPosP());
    fopAcM_seStart(this, JA_SE_OBJ_COL_SWS_NMTLP, 0);
    fopAcM_seStart(this, JA_SE_CV_JI_DEFENCE, 0);
    dKy_SordFlush_set(*field_0x7E0.GetTgHitPosP(), 0);
}

/* 0001161C-00011644       .text BackSlideInit__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::BackSlideInit() {
    field_0xC9C = 0;
    field_0xD38 = current.pos;
}

/* 00011644-0001173C       .text BackSlide__11daNpc_Ji1_cFff */
void daNpc_Ji1_c::BackSlide(f32 param_1, f32 param_2) {
    /* Nonmatching */

    cLib_addCalc2(&field_0xC9C, param_1, 0.25f, 50.0f);
    cXyz temp(field_0xD38);
    temp.x -= field_0xC9C * cM_ssin(current.angle.y);
    temp.z -= field_0xC9C * cM_scos(current.angle.y);

    if(field_0x434.ChkWallHit()) {
        param_2 *= 0.35f;
    }

    cLib_addCalcPosXZ(&current.pos, temp, 0.8f, param_2, 1.0f);
}

/* 0001173C-000118E0       .text harpoonRelease__11daNpc_Ji1_cFP4cXyz */
void daNpc_Ji1_c::harpoonRelease(cXyz* param_1) {
    MTXCopy(mpMorf->getModel()->getAnmMtx(1), field_0xCA0);
    mpMorf->setFrame(0.0f);
    field_0xCD0.x = field_0xCA0[0][3];
    field_0xCD0.y = field_0xCA0[1][3];
    field_0xCD0.z = field_0xCA0[2][3];
    field_0xCA0[0][3] = 0.0f;
    field_0xCA0[1][3] = 0.0f;
    field_0xCA0[2][3] = 0.0f;

    if(param_1) {
        field_0xCDC = *param_1;
    }
    else {
        field_0xCDC.set(0.0f, 5.0f, 0.0f);
    }

    field_0xD14 = 0x400;

    field_0xD04 = cM_ssin(field_0xD14) * cM_scos(current.angle.y);
    field_0xD08 = 0.0f;
    field_0xD0C = cM_ssin(field_0xD14) * cM_ssin(current.angle.y);
    field_0xD10 = cM_scos(field_0xD14);

    field_0xCF4 = ZeroQuat;

    field_0xD84 = 2;
}

/* 000118E0-00011F74       .text harpoonMove__11daNpc_Ji1_cFv */
void daNpc_Ji1_c::harpoonMove() {
    /* Nonmatching */
}

/* 00011F74-00011F98       .text daNpc_Ji1_Execute__FP11daNpc_Ji1_c */
static BOOL daNpc_Ji1_Execute(daNpc_Ji1_c* i_this) {
    i_this->_execute();
    return true;
}

/* 00011F98-00011FA0       .text daNpc_Ji1_IsDelete__FP11daNpc_Ji1_c */
static BOOL daNpc_Ji1_IsDelete(daNpc_Ji1_c*) {
    return true;
}

/* 00011FA0-00011FC0       .text daNpc_Ji1_Delete__FP11daNpc_Ji1_c */
static BOOL daNpc_Ji1_Delete(daNpc_Ji1_c* i_this) {
    return i_this->_delete();
}

/* 00011FC0-00011FE0       .text daNpc_Ji1_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Ji1_Create(fopAc_ac_c* i_this) {
    return static_cast<daNpc_Ji1_c*>(i_this)->_create();
}

static actor_method_class l_daNpc_Ji1_Method = {
    (process_method_func)daNpc_Ji1_Create,
    (process_method_func)daNpc_Ji1_Delete,
    (process_method_func)daNpc_Ji1_Execute,
    (process_method_func)daNpc_Ji1_IsDelete,
    (process_method_func)daNpc_Ji1_Draw,
};

actor_process_profile_definition g_profile_NPC_JI1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_JI1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Ji1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_JI1,
    /* Actor SubMtd */ &l_daNpc_Ji1_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
