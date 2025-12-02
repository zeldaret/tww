/**
 * d_a_fm.cpp
 * Enemy - Floormaster
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_fm.h"
#include "d/actor/d_a_player_main.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"
#include "d/d_lib.h"
#include "d/d_jnt_hit.h"
#include "d/d_snap.h"
#include "d/d_material.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_tsubo.h"
#include "d/actor/d_a_npc_cb1.h"
#include "d/actor/d_a_npc_md.h"
#include "d/d_s_play.h"
#include "d/d_a_obj.h"

const u32 daFm_c::m_heapsize = 0x2100;
const char daFm_c::m_arc_name[] = "Fm";

const dCcD_SrcSph daFm_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_UNK8 & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_UNK400000,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_NoCrr_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoConHit_e | dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGSphS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
    }},
};


const dCcD_SrcCyl daFm_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ AT_TYPE_UNK800,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_WATER & ~AT_TYPE_UNK20000 & ~AT_TYPE_WIND & ~AT_TYPE_UNK400000 & ~AT_TYPE_LIGHT,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e | cCcD_CoSPrm_NoCrr_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ dCcG_SE_UNK23,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 60.0f,
        /* Height */ 0.0f,
    }},
};

class daFm_HIO_c : public mDoHIO_entry_c{
public:
    daFm_HIO_c();
    virtual ~daFm_HIO_c() {};

public:
    /* 0x000 */ u8 field_0x000[0x004 - 0x000];
    /* 0x004 */ s8 field_0x004;
    /* 0x005 */ s8 field_0x005;
    /* 0x006 */ s8 field_0x006;
    /* 0x007 */ s8 field_0x007;
    /* 0x008 */ s8 field_0x008;
    /* 0x009 */ s8 field_0x009;
    /* 0x00A */ s8 field_0x00A;
    /* 0x00B */ s8 field_0x00B;
    /* 0x00C */ s8 field_0x00C;
    /* 0x00D */ s8 field_0x00D;
    /* 0x00E */ s8 field_0x00E;
    /* 0x00F */ s8 field_0x00F[6];
    /* 0x015 */ u8 field_0x015[0x01F - 0x015];
    /* 0x01F */ s8 field_0x01F;
    /* 0x020 */ f32 field_0x020;
    /* 0x024 */ f32 field_0x024;
    /* 0x028 */ cXyz field_0x028;
    /* 0x034 */ cXyz field_0x034;
    /* 0x040 */ f32 field_0x040;
    /* 0x044 */ f32 field_0x044;
    /* 0x048 */ f32 field_0x048;
    /* 0x04C */ f32 field_0x04C;
    /* 0x050 */ f32 field_0x050;
    /* 0x054 */ f32 field_0x054;
    /* 0x058 */ f32 field_0x058;
    /* 0x05C */ s16 field_0x05C;
    /* 0x05E */ s16 field_0x05E;
    /* 0x060 */ s16 mMaxHealth;
    /* 0x062 */ s16 field_0x062;
    /* 0x064 */ s16 field_0x064;
    /* 0x066 */ s16 field_0x066;
    /* 0x068 */ s16 field_0x068;
    /* 0x06A */ u8 field_0x06A[0x06C - 0x06A];
    /* 0x06C */ f32 field_0x06C;
    /* 0x070 */ f32 field_0x070;
    /* 0x074 */ s16 field_0x074;
    /* 0x076 */ s16 field_0x076;
    /* 0x078 */ f32 field_0x078;
    /* 0x07C */ f32 field_0x07C;
    /* 0x080 */ s16 field_0x080;
    /* 0x082 */ s16 field_0x082;
    /* 0x084 */ s16 field_0x084;
    /* 0x086 */ s16 field_0x086;
    /* 0x088 */ s16 field_0x088;
    /* 0x08A */ s16 field_0x08A;
    /* 0x08C */ s16 field_0x08C;
    /* 0x08E */ s16 field_0x08E;
    /* 0x090 */ s16 field_0x090;
    /* 0x092 */ s16 field_0x092;
    /* 0x094 */ s16 field_0x094;
    /* 0x096 */ s16 field_0x096;
    /* 0x098 */ s16 field_0x098;
    /* 0x09A */ s16 field_0x09A;
    /* 0x09C */ s16 field_0x09C;
    /* 0x09E */ s16 field_0x09E;
    /* 0x0A0 */ s16 field_0x0A0;
    /* 0x0A2 */ s16 field_0x0A2;
    /* 0x0A4 */ f32 field_0x0A4;
    /* 0x0A8 */ f32 field_0x0A8;
    /* 0x0AC */ f32 field_0x0AC;
    /* 0x0B0 */ f32 field_0x0B0;
    /* 0x0B4 */ f32 field_0x0B4;
    /* 0x0B8 */ f32 field_0x0B8;
    /* 0x0BC */ f32 field_0x0BC;
    /* 0x0C0 */ f32 field_0x0C0;
    /* 0x0C4 */ f32 field_0x0C4;
    /* 0x0C8 */ f32 field_0x0C8;
    /* 0x0CC */ f32 field_0x0CC;
    /* 0x0D0 */ f32 field_0x0D0;
    /* 0x0D4 */ f32 field_0x0D4;
    /* 0x0D8 */ f32 field_0x0D8;
    /* 0x0DC */ f32 field_0x0DC;
    /* 0x0E0 */ f32 field_0x0E0;
    /* 0x0E4 */ f32 field_0x0E4;
    /* 0x0E8 */ f32 field_0x0E8;
    /* 0x0EC */ f32 field_0x0EC;
    /* 0x0F0 */ f32 field_0x0F0;
    /* 0x0F4 */ f32 field_0x0F4;
    /* 0x0F8 */ f32 field_0x0F8;
    /* 0x0FC */ s16 field_0x0FC;
    /* 0x0FE */ s16 field_0x0FE;
    /* 0x100 */ s16 field_0x100;
    /* 0x102 */ u8 field_0x102[0x104 - 0x102];
    /* 0x104 */ f32 field_0x104;
    /* 0x108 */ f32 field_0x108;
    /* 0x10C */ f32 field_0x10C;
    /* 0x110 */ f32 field_0x110;
    /* 0x114 */ f32 field_0x114;
    /* 0x118 */ s16 field_0x118;
    /* 0x11A */ s16 field_0x11A;
    /* 0x11C */ f32 field_0x11C;
    /* 0x120 */ f32 field_0x120;
    /* 0x124 */ f32 field_0x124;
    /* 0x128 */ f32 field_0x128;
    /* 0x12C */ f32 field_0x12C;
    /* 0x130 */ JntHit_HIO_c field_0x130;
    /* 0x158 */ u8 field_0x158[0x15C - 0x158];
};  // Size: 0x15C

static daFm_HIO_c l_HIO;

/* 000000EC-000003EC       .text __ct__10daFm_HIO_cFv */
daFm_HIO_c::daFm_HIO_c() {
    field_0x006 = 0;
    field_0x007 = 0;
    field_0x008 = 0;
    field_0x004 = 0;
    field_0x01F = 0;
    field_0x00B = 0;
    field_0x009 = 0;
    field_0x00A = 0;
    field_0x00C = 0;
    field_0x005 = 0;
    field_0x068 = 0x1e;
    field_0x06C = 240.0f;
    field_0x070 = 100.0f;
    field_0x074 = 0;
    field_0x076 = 0xF;
    field_0x078 = 120.0f;
    field_0x07C = 100.0f;
    field_0x080 = 5;
    field_0x082 = 0xF;
    field_0x11C = 100;
    field_0x00E = 0;
    field_0x00D = 0;
    field_0x062 = 0x78;

    for (int i = 0; i < 6; ++i) {
        switch(i) {

            case 5:
                field_0x00F[i] = 1;
                break;
            case 0:
            case 1:
            case 2:
            case 3:
                field_0x00F[i] = 0;
                break;
        }
    }

    field_0x050 = 0.0f;
    field_0x054 = 0.0f;
    field_0x058 = 0.0f;
    field_0x05C = 0;
    field_0x05E = 0;
    mMaxHealth = 0;
    field_0x020 = -10.0f;
    field_0x024 = 5.0f;
    field_0x028.x = -10.0f;
    field_0x028.y = 0.0f;
    field_0x028.z = 0.0f;
    field_0x034.x = -30.0f;
    field_0x034.y = 40.0f;
    field_0x034.z = -20.0f;

    field_0x040 = 0.0f;
    field_0x044 = 0.0f;
    field_0x048 = 0.0f;
    field_0x04C = 0.0f;
    field_0x104 = 0.0f;
    field_0x108 = -20.0f;
    field_0x10C = -0.0f;
    field_0x0A8 = 600.0f;
    field_0x064 = 0xC;
    field_0x066 = 0x28;
    field_0x084 = 0x5A;
    field_0x086 = 0xF0;
    field_0x088 = 0x3C;
    field_0x08A = 1;
    field_0x08C = 0x3C;
    field_0x08E = 0x78;
    field_0x090 = 10;
    field_0x092 = 0x11;
    field_0x094 = 0;
    field_0x096 = 500;
    field_0x098 = 18000;
    field_0x09A = 7000;
    field_0x0C0 = 15.0;
    field_0x120 = 0.01f;
    field_0x124 = 1.0f;
    field_0x128 = 0.1f;
    field_0x12C = 0.02f;
    field_0x0C4 = 290.0f;
    field_0x0C8 = 80.0f;
    field_0x0CC = 7.0f;
    field_0x0D0 = 2.0f;
    field_0x0D4 = 5.0f;
    field_0x0D8 = 80.0f;
    field_0x0DC = 100.0f;
    field_0x0E0 = 150.0f;
    field_0x0E4 = 500.0f;
    field_0x0E8 = 800.0f;
    field_0x0EC = 30.0f;
    field_0x0F0 = 25.0f;
    field_0x0F4 = 9.0f;
    field_0x0F8 = -2.5f;
    field_0x0FC = 16.0f;
    field_0x09C = 5;
    field_0x100 = 0x1e;
    field_0x110 = 20.0f;
    field_0x114 = 50.0f;
    field_0x118 = -0x3E60;
    field_0x11A = 0;
    field_0x0B0 = 30.0f;
    field_0x0A0 = 0x14;
    field_0x0A2 = 0x96;
    field_0x0B4 = 1000.0f;
    field_0x0B8 = 1000.0f;
    field_0x09E = 0x96;
    field_0x0AC = 300.0f;
    field_0x0BC = 750.0f;
    // field_0x0A6 = 10;
    /* Nonmatching */
}

/* 000003EC-00000438       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* node, int arg1) {
    J3DJoint* joint = (J3DJoint*)node;
    if (arg1 == 0) {
        daFm_c* i_this = (daFm_c*)j3dSys.getModel()->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeControl(joint, j3dSys.getModel());
        }
    }
    return TRUE;
    /* Nonmatching */
}

/* 00000438-00000690       .text _nodeControl__6daFm_cFP7J3DNodeP8J3DModel */
void daFm_c::_nodeControl(J3DNode* node, J3DModel* model) {

    /* Nonmatching */
}

/* 00000690-000006B0       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 000006B0-00000718       .text _createHeap__6daFm_cFv */
void daFm_c::_createHeap() {
    /* Nonmatching */
}

/* 00000718-0000086C       .text holeCreateHeap__6daFm_cFv */
void daFm_c::holeCreateHeap() {
    /* Nonmatching */
}

/* 0000086C-000009CC       .text bodyCreateHeap__6daFm_cFv */
void daFm_c::bodyCreateHeap() {
    /* Nonmatching */
}

/* 000009CC-00000A30       .text jntHitCreateHeap__6daFm_cFv */
void daFm_c::jntHitCreateHeap() {
    /* Nonmatching */
}

/* 00000A30-00000A6C       .text pathMove_CB__FP4cXyzP4cXyzP4cXyzPv */
int pathMove_CB(cXyz*, cXyz*, cXyz*, void*) {
    /* Nonmatching */
    return 0;
}

/* 00000A6C-00000D40       .text _pathMove__6daFm_cFP4cXyzP4cXyzP4cXyz */
void daFm_c::_pathMove(cXyz*, cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 00000D40-00000D6C       .text searchNearOtherActor_CB__FPvPv */
void searchNearOtherActor_CB(void*, void*) {
    /* Nonmatching */
}

/* 00000D6C-00000F18       .text searchNearOtherActor__6daFm_cFP10fopAc_ac_c */
void daFm_c::searchNearOtherActor(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00000F18-00000F44       .text searchNearFm_CB__FPvPv */
void searchNearFm_CB(void*, void*) {
    /* Nonmatching */
}

/* 00000F44-00001150       .text searchNearFm__6daFm_cFP10fopAc_ac_c */
void daFm_c::searchNearFm(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 00001150-00001384       .text moveRndBack__6daFm_cFv */
void daFm_c::moveRndBack() {
    /* Nonmatching */
}

/* 00001384-000015F8       .text moveRndEscape__6daFm_cFv */
void daFm_c::moveRndEscape() {
    /* Nonmatching */
}

/* 000015F8-00001680       .text spAttackVJump__6daFm_cFv */
void daFm_c::spAttackVJump() {
    /* Nonmatching */
}

/* 00001680-00001708       .text spAttackJump__6daFm_cFv */
void daFm_c::spAttackJump() {
    /* Nonmatching */
}

/* 00001708-00001738       .text spAttackNone__6daFm_cFv */
void daFm_c::spAttackNone() {
    /* Nonmatching */
}

/* 00001738-000017CC       .text iceProc__6daFm_cFv */
void daFm_c::iceProc() {
    /* Nonmatching */
}

/* 000017CC-00001864       .text bodySetMtx__6daFm_cFv */
void daFm_c::bodySetMtx() {
    /* Nonmatching */
}

/* 00001864-00001920       .text holeSetMtx__6daFm_cFv */
void daFm_c::holeSetMtx() {
    /* Nonmatching */
}

/* 00001920-00001A50       .text setCollision__6daFm_cFv */
void daFm_c::setCollision() {
    /* Nonmatching */
}

/* 00001A50-00001C90       .text setAttention__6daFm_cFv */
void daFm_c::setAttention() {
    /* Nonmatching */
}

/* 00001C90-00002530       .text checkTgHit__6daFm_cFv */
bool daFm_c::checkTgHit() {
    /* Nonmatching */
}

/* 00002530-000026A0       .text setGrabPos__6daFm_cFv */
void daFm_c::setGrabPos() {
    /* Nonmatching */
}

/* 000026A0-00002868       .text getOffsetPos__6daFm_cFv */
void daFm_c::getOffsetPos() {
    /* Nonmatching */
}

/* 00002868-000028D4       .text checkPlayerGrabBomb__6daFm_cFv */
bool daFm_c::checkPlayerGrabBomb() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    fopAc_ac_c* ac = fopAcM_SearchByID(pLink->getGrabActorID());
    if(ac == NULL) {
        return false;
    }
    return (u8)(fopAcM_GetName(ac) == PROC_BOMB);// is this real?
    /* Nonmatching */
}

/* 000028D4-00002954       .text checkPlayerGrabNpc__6daFm_cFv */
bool daFm_c::checkPlayerGrabNpc() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    fopAc_ac_c* ac = fopAcM_SearchByID(pLink->getGrabActorID());
    if(ac == NULL) {
        return false;
    }
    return (u8)(isNpc(ac) != 0); // is this real?
    /* Nonmatching */
}

/* 00002954-000029A8       .text checkPlayerGrabTarget__6daFm_cFv */
bool daFm_c::checkPlayerGrabTarget() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    return (u8)(pLink->getGrabActorID() == mProcId);// is this real?
    /* Nonmatching */
}

/* 000029A8-00002CEC       .text isGrabPos__6daFm_cFv */
bool daFm_c::isGrabPos() {
    /* Nonmatching */
}

/* 00002CEC-00002E7C       .text isGrab__6daFm_cFv */
bool daFm_c::isGrab() {
    /* Nonmatching */
}

/* 00002E7C-00002F98       .text isGrabFoot__6daFm_cFv */
bool daFm_c::isGrabFoot() {
    /* Nonmatching */
}

/* 00002F98-00002FDC       .text modeSwWaitInit__6daFm_cFv */
void daFm_c::modeSwWaitInit() {
    setAnm(8, false);
    field_0x3E0 = l_HIO.field_0x11C;
    /* Nonmatching */
}

/* 00002FDC-000031B0       .text modeSwWait__6daFm_cFv */
void daFm_c::modeSwWait() {
    resetInvKine();

    if (!dComIfGs_isSwitch(field_0x2D4, fopAcM_GetRoomNo(this))) {
        return;
    }
    if (field_0x2E4 != 0) {
        setHoleScale(l_HIO.field_0x120, 0.1f, l_HIO.field_0x124);
        if(eventInfo.mCommand == dEvtCmd_INDEMO_e){
            if (field_0x2E4 != 0 && cLib_calcTimer(&field_0x650) != 0) {
                return;
            }
        } else {
            if (dComIfGp_evmng_startCheck("DEFAULT_FM_SW_APEEAR") == 0) {
                fopAcM_orderOtherEvent2(this,"DEFAULT_FM_SW_APEEAR",dEvtFlag_NOPARTNER_e);
            }
        }
        // (this->parent).parent.actor_status = (this->parent).parent.actor_status | 0x4000;
    } else {
        if(dComIfGp_evmng_startCheck("DEFAULT_FM_SW_APEEAR") != 0) {
            field_0x2E5 = true;
        }
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);

    }
    switch(field_0x2D0) {
        case 0:
            modeProc(PROC_0_e, 2);
            break;
        case 1:
            if(setHoleScale(l_HIO.field_0x120, 0.1f, l_HIO.field_0x124) != 0) {
                modeProc(PROC_0_e,3);
            }
            break;
        case 2:
            if(setHoleScale(l_HIO.field_0x120, 0.1f, l_HIO.field_0x124) != 0) {
                modeProc(PROC_0_e,4);
            }
            break;
    }

    /* Nonmatching */
}

/* 000031B0-00003200       .text modeHideInit__6daFm_cFv */
void daFm_c::modeHideInit() {
    setAnm(8, false);
    field_0x650 = setRnd(l_HIO.field_0x080,l_HIO.field_0x082);
    /* Nonmatching */
}

/* 00003200-000032E0       .text modeHide__6daFm_cFv */
void daFm_c::modeHide() {
    field_0x690 = current.pos;
    resetInvKine();
    if(setHoleScale(l_HIO.field_0x11C, 0.1f, l_HIO.field_0x124) != 0) {
        current.pos.x = mBaseTarget->current.pos.x;
        current.pos.z = mBaseTarget->current.pos.z;
        if(cLib_calcTimer(&field_0x650) == 0) {
            if(std::fabsf(field_0x69C.y - mBaseTarget->current.pos.y) <=  l_HIO.field_0x0A4 && field_0xAE4 == 1) {
                modeProc(PROC_0_e,2);
            }
        }
    }
    /* Nonmatching */
}

/* 000032E0-00003344       .text modeUnderFootInit__6daFm_cFv */
void daFm_c::modeUnderFootInit() {
    setAnm(8, false);
    field_0x650 = l_HIO.field_0x062;
    current.pos.x = mBaseTarget->current.pos.x;
    current.pos.z = mBaseTarget->current.pos.z;
    field_0x3E0 = l_HIO.field_0x11C;  
    /* Nonmatching */
}

/* 00003344-000034E4       .text modeUnderFoot__6daFm_cFv */
void daFm_c::modeUnderFoot() {
    if (cLib_calcTimer(&field_0x648) == 0) {
        field_0x660 = mBaseTarget->current.pos;
        field_0x648 = l_HIO.field_0x086;
    }
    cLib_addCalcPosXZ2(&current.pos, field_0x660, 0.1f, l_HIO.field_0x0BC);

    field_0x690 = current.pos;
    resetInvKine();
    if(std::fabsf(field_0x69C.y - mBaseTarget->current.pos.y) >  l_HIO.field_0x0A4|| field_0xAE4 == 0) {
        modeProc(PROC_0_e,1);
    } else {
        if(setHoleScale(l_HIO.field_0x120, 0.1f, l_HIO.field_0x128) != 0) {
            if(cLib_calcTimer(&field_0x650) == 0) {
                if(isGrabFoot() && !dComIfGp_event_runCheck()) {
                    modeProc(PROC_0_e,0xf);
                } else {
                    if(field_0x9D4 < l_HIO.field_0x0E0 && field_0xAE5 == 0) {
                        modeProc(PROC_0_e, 5);
                    } else {
                        modeProc(PROC_0_e, 1);
                    }
                }
            }
        }
    }
    /* Nonmatching */
}

/* 000034E4-00003528       .text modePathMoveInit__6daFm_cFv */
void daFm_c::modePathMoveInit() {
    setAnm(8, false);
    field_0x3E0 = l_HIO.field_0x120;
    /* Nonmatching */
}

/* 00003528-00003670       .text modePathMove__6daFm_cFv */
void daFm_c::modePathMove() {
    field_0x690 = current.pos;
    resetInvKine();
    turnToBaseTarget();
    if(isGrabFoot() && !dComIfGp_event_runCheck()) {
        modeProc(PROC_0_e,0xf);
    } else {
        
        dLib_pathMove(&field_0x3B0, (s8*)&field_0x3BC, mpPath, 3.0f, pathMove_CB, this);
        cLib_addCalcPosXZ2(&current.pos, field_0x3B0, (l_HIO.field_0x0CC + 1.0f) *0.005f * field_0x394, 20.0f);

        daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
        
        if(field_0x9D4 <l_HIO.field_0x0E0  && std::fabsf(pLink->current.pos.y - current.pos.y) < l_HIO.field_0x0A4 && field_0xAE5 == 0) {
            modeProc(PROC_0_e,5);
        }
    }
    /* Nonmatching */
}

/* 00003670-000036B4       .text modeGoalKeeperInit__6daFm_cFv */
void daFm_c::modeGoalKeeperInit() {
    setAnm(8, false);
    field_0x3E0 = l_HIO.field_0x120;
    /* Nonmatching */
}

/* 000036B4-000038DC       .text modeGoalKeeper__6daFm_cFv */
void daFm_c::modeGoalKeeper() {

    if(field_0x2E5 && dComIfGp_evmng_endCheck("DEFAULT_FM_SUIKOMI_NPC")) {
        modeProc(PROC_0_e,6);
        return;
    }

    resetInvKine();
    turnToBaseTarget();
    if(isGrabFoot() && !dComIfGp_event_runCheck()) {
        modeProc(PROC_0_e, 0xf);
    } else {
        if(field_0x2E4 != 0) {
            modeProc(PROC_0_e, 5);
        } else {
            if(field_0x9D4 < l_HIO.field_0x0E4 && std::fabsf(current.pos.y - mBaseTarget->current.pos.y) < l_HIO.field_0x0A4) {
                cXyz temp = mBaseTarget->current.pos - field_0x69C;
                temp.y = 0.0f;
                // cXyz temp(mBaseTarget->current.pos.x - field_0x69C.x, 0.0f, mBaseTarget->current.pos.z - field_0x69C.z);

                if(temp.abs() < field_0x2E0 && field_0xAE5 == 0) {
                    modeProc(PROC_0_e,5);
                }
            }
            field_0x690 = field_0x69C;
            cLib_addCalcPosXZ2(&current.pos, field_0x690, (l_HIO.field_0x0C8 + 1.0f) *0.005f * field_0x394, 40.0f);
        }
    }
    /* Nonmatching */
}

/* 000038DC-00003938       .text modeAppearInit__6daFm_cFv */
void daFm_c::modeAppearInit() {
    setAnm(2, false);
    field_0x660 = current.pos;
    shape_angle.y = field_0x9D0;
    field_0x650 = 0x1e;
    /* Nonmatching */
}

/* 00003938-00003A00       .text modeAppear__6daFm_cFv */
void daFm_c::modeAppear() {
    if(field_0x2D0 == 0) {
        moveRndBack();
    }
    resetInvKine();
    if(!checkTgHit()) {
        searchTarget();
        if(mpActorTarget != NULL) {
            setGrabPos();
            if(field_0x2E4 != 0 && cLib_calcTimer(&field_0x650) != 0) {
                return;
            }
            if(isGrabPos()) {
                modeProc(PROC_0_e,8);
                return;
            }
        }
        if(field_0x2C5 == 1) {
            modeProc(PROC_0_e,7);
        }
    }
    /* Nonmatching */
}

/* 00003A00-00003A68       .text modeDisappearInit__6daFm_cFv */
void daFm_c::modeDisappearInit() {
    if(field_0x2C5 != 8 && field_0x2C5 != 6) {
        setAnm(3, false);
    }

    if(field_0x2C5 == 6) {
        setAnm(8, false);
    }
    /* Nonmatching */
}

/* 00003A68-00003BDC       .text modeDisappear__6daFm_cFv */
void daFm_c::modeDisappear() {
    if (field_0x2D0 != 2) {
        field_0x690 = current.pos;
    }
    resetInvKine();
    cancelGrab();
    if (field_0x2C5 == 8) {
        if (mpMorf->isStop()) {
            if(field_0x2E4 != 0 || field_0x2E5) {
                modeProc(PROC_0_e, 0x12);
            } else {
                fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
                if(isGrabFoot() && !dComIfGp_event_runCheck()) {
                    modeProc(PROC_0_e, 0xf);
                } else {
                    switch(field_0x2D0) {
                        case 0:
                            modeProc(PROC_0_e, 1);
                            break;
                        case 1:
                            modeProc(PROC_0_e, 3);
                            break;
                        case 2:
                            modeProc(PROC_0_e, 4);
                            break;
                    }
                }
            }
        }
    }
    /* Nonmatching */
}

/* 00003BDC-00003C5C       .text modeWaitInit__6daFm_cFv */
void daFm_c::modeWaitInit() {
    field_0x658 = l_HIO.field_0x084;
    field_0x650 = setRnd(l_HIO.field_0x088,l_HIO.field_0x08A);

    field_0x654 = l_HIO.field_0x086;
    field_0x65C = (s16)l_HIO.field_0x0FC;
    field_0x6B4 = 0;
    field_0x660 = current.pos;
    /* Nonmatching */
}

/* 00003C5C-00003F90       .text modeWait__6daFm_cFv */
void daFm_c::modeWait() {
    resetInvKine();
    cancelGrab();
    if(checkTgHit()) {
        return;
    }
    if (!areaCheck()) {
        modeProc(PROC_0_e, 6);
        return;
    }
    if (isGrabFoot()) {
        modeProc(PROC_0_e, 6);
        return;
    }

    searchTarget();
    s32 angle = cLib_distanceAngleS(shape_angle.y, field_0x9D0);
    if(mpActorTarget != NULL) {
        if(field_0x9D4 > l_HIO.field_0x0DC) {
            angle = cLib_targetAngleY(&current.pos, &mGrabPos);
            bool isnpc = isNpc(mpActorTarget);
            if(isnpc || isLink(mpActorTarget)) {
                cLib_addCalcAngleS2(&shape_angle.y, angle, 8, 0x300);

            } else {
                cLib_addCalcAngleS2(&shape_angle.y, angle, 4, 0x800);

            }
        }
        setGrabPos();
        if(isGrabPos()) {
            if(checkPlayerGrabTarget()) {
                if(isNpc(mpActorTarget)) {
                    modeProc(PROC_0_e,8);
                    return;
                }
                if (cLib_calcTimer(&field_0x65C) == 0) {
                    return;
                }
            } else {

                if(cLib_calcTimer(&field_0x65C) == 0) {
                    modeProc(PROC_0_e, 8);
                    return;
                }
                modeProc(PROC_0_e, 8);
                return;
            }

        }
    } else {
        if(angle > l_HIO.field_0x096) {
            cLib_addCalcAngleS2(&shape_angle.y, field_0x9D0, 10, 0x100);
        }
    }
    if(field_0x2D0 == 2) {
        cXyz diff = field_0x69C - mBaseTarget->current.pos;
        diff.y = 0.0f;
        if(diff.abs() > field_0x2E0) {
            modeProc(PROC_0_e, 6);
        } else {
            moveRndBack();
        }
    }
    if(field_0x9D4 > l_HIO.field_0x0E0 && field_0x9D4 < l_HIO.field_0x0E4) {
        turnToBaseTarget();
    }
    if(field_0x9D4 > l_HIO.field_0x0E4) {
        if(cLib_calcTimer(&field_0x658) == 0) {
            modeProc(PROC_0_e,6);
        }
    } else {
        field_0x658 = l_HIO.field_0x084;
    }
    /* Nonmatching */
}

/* 00003F90-00003FF8       .text modeAttackInit__6daFm_cFv */
void daFm_c::modeAttackInit() {
    if(dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK400_e | daPyStts0_UNK2_e)) {
        modeProc(PROC_0_e,7);
    } else {
        setAnm(4, false);
        field_0x650 = l_HIO.field_0x090;
    }
    /* Nonmatching */
}

/* 00003FF8-000049CC       .text modeAttack__6daFm_cFv */
void daFm_c::modeAttack() {
    if(field_0x2C5 != 5 && isGrab()) {
        cXyz temp = mGrabPos - current.pos;
        temp.y = 0.0f;
        f32 abs = temp.abs();
        if (!(abs > l_HIO.field_0x0DC && abs < l_HIO.field_0x0C0) && abs < l_HIO.field_0x0E0 + 10.0f) {
            field_0x660 = mGrabPos;
            cLib_addCalcPosXZ2(&current.pos, field_0x660, (l_HIO.field_0x0C8 + 1.0f) *0.005f * field_0x394, 40.0f);
        }
    }
    if(!checkTgHit()) {
        if(field_0x2C5 == 5) {
            if(mpMorf->isStop()) {
                modeProc(PROC_0_e, 7);
                return;
            }
        }

        if(mpActorTarget == NULL) {
            setAnm(5, false);
        } else {
            calcInvKine(mpActorTarget);
            s16 angle = fopAcM_searchActorAngleY(this, mpActorTarget);

            if(cLib_distanceAngleS(shape_angle.y, angle) > l_HIO.field_0x096) {
                cLib_addCalcAngleS2(&shape_angle.y, angle, 4, l_HIO.field_0x092);
            }
            daPy_lk_c* pLink;

            if (field_0xAE4 == 0) {
                modeProc(PROC_0_e, 6);
            } else if(dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK400_e | daPyStts0_UNK2_e)) {
                f32 oldPosY = mGrabPos.y;
                mGrabPos = daPy_getPlayerLinkActorClass()->current.pos;
                mGrabPos.y = oldPosY;
            } else {
                pLink = daPy_getPlayerLinkActorClass();
                if (isGrabPos()) {
                    setAnm(5, false);
                } else {
                    setGrabPos();
                    if(isGrab()) {
                        if(isLink(mpActorTarget) && field_0x2C5 == 4) {
                            if(mpMorf->isStop() && cLib_calcTimer(&field_0x650)) {
                                setAnm(5, false);
                            }
                        } else {
                            cXyz temp2 = mGrabPos - current.pos;
                            temp2.y = 0.0f;
                            f32 abs2 = temp2.abs();
                            pLink = daPy_getPlayerLinkActorClass();
                            if (!(abs2 > l_HIO.field_0x0DC && abs2 < l_HIO.field_0x0C0)) {
                                setAnm(5, false);
                            } else if(pLink->speedF < 1.0f) {
                                f32 temp3 = std::fabsf(l_HIO.field_0x0B0 - l_HIO.field_0x0A0);
                                if(temp3 == 0.0f) {
                                    temp3 = 1.0f;
                                }
                                pLink->setOutPower(l_HIO.field_0x0A0 * std::fabsf(temp3 - l_HIO.field_0x0B0) + temp3, cLib_targetAngleY(&field_0x63C, &mGrabPos), 0);
                            }
                        }
                    } else {
                        pLink = daPy_getPlayerLinkActorClass();
                        if(isLink(mpActorTarget) || field_0x2C5 != 4) {
                            if(isNpc(mpActorTarget)) {
                                if(fopAcM_CheckStatus(mpActorTarget, fopAcStts_CARRY_e)) {
                                    fopAcM_seStart(this, JA_SE_CM_FM_GRAB_HAND, 0);
                                    fopAcM_setCarryNow(mpActorTarget, FALSE);
                                    field_0x684 = 4;
                                    if(fopAcM_GetName(mpActorTarget) == PROC_NPC_CB1) {
                                        //      5] noCarryAction__11daNpc_Cb1_cFv (func,weak) found in d_a_fm.o 
                                        ((daNpc_Cb1_c*)mpActorTarget)->noCarryAction();
                                        // _m_status = _m_status | 1; no clue
                                    }
                                    if(fopAcM_GetName(mpActorTarget) == PROC_NPC_MD) {
                                        ((daNpc_Md_c*)mpActorTarget)->noCarryAction();
                                        // fopAcM_OnStatus(mpActorTarget, fopAcStts_UNK800_e);

                                        // pfVar3[0x13].parent.parent.mLnTg.parent.mpTagData =
                                        //     (create_request *)
                                        //     ((uint)pfVar3[0x13].parent.parent.mLnTg.parent.mpTagData | 0x800);
                                    }
                                    field_0x6B8 = 1;
                                    if(field_0x2E4 == 0) {
                                        if(fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0)) <= l_HIO.field_0x0DC &&
                                            (std::fabsf(pLink->current.pos.y - current.pos.y) <= l_HIO.field_0x0A4) ||
                                            dComIfGp_event_runCheck()) {
                                                modeProc(PROC_0_e, 0xD);
                                        } else {
                                            modeProc(PROC_0_e, 0x10);
                                        }
                                    } else {
                                        if(dComIfGp_evmng_startCheck("DEFAULT_FM_SW_APEEAR")) {
                                            dComIfGp_event_reset();
                                        }
                                        modeProc(PROC_0_e, 0xd);
                                    }
                                } else {
                                    fopAcM_cancelCarryNow(mpActorTarget );
                                }
                            } else {
                                if(fopAcM_GetName(mpActorTarget) == PROC_BOMB) {
                                    if(fopAcM_CheckStatus(mpActorTarget, fopAcStts_CARRY_e)) {
                                        fopAcM_setCarryNow(mpActorTarget, 0);
                                        field_0x684 = 2;
                                        fopAcM_seStart(this, JA_SE_CM_MD_PIYO, 0);
                                        modeProc(PROC_0_e, 0xd);
                                    } else {
                                        modeProc(PROC_0_e, 7);
                                    }
                                } else if(fopAcM_GetName(mpActorTarget) == PROC_TSUBO) {
                                    if(fopAcM_CheckStatus(mpActorTarget, fopAcStts_CARRY_e)) {
                                        fopAcM_setCarryNow(mpActorTarget, 0);
                                        field_0x684 = 3;
                                        fopAcM_seStart(this, JA_SE_CM_FM_GRAB, 0);
                                        modeProc(PROC_0_e, 0xd);
                                    } else {
                                        fopAcM_cancelCarryNow(mpActorTarget);
                                    }
                                }
                            }
                        } else {
                            if(mpMorf->isStop()) {
                                modeProc(PROC_0_e, 0xd);
                                fopAcM_seStart(this, JA_SE_CM_FM_GRAB_HAND, 0);
                                pLink->voiceStart(28);
                            } else if(pLink->speedF < 1.0f) {
                                cXyz temp4 = mGrabPos - field_0x63C;
                                temp4.y = 0.0f;
                                f32 abs4 = temp4.abs();
                                if (!(abs4 > l_HIO.field_0x0DC && abs4 < l_HIO.field_0x0C0)) {
                                    f32 temp5 = std::fabsf(l_HIO.field_0x0B0 - l_HIO.field_0x0A0);
                                    if(temp5 == 0.0f) {
                                        temp5 = 1.0f;
                                    }
                                    pLink->setOutPower(l_HIO.field_0x0A0 * std::fabsf(temp5 - l_HIO.field_0x0B0) + temp5, cLib_targetAngleY(&field_0x63C, &mGrabPos), 0);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    /* Nonmatching */
}

/* 000049CC-000049F4       .text modeThrowInit__6daFm_cFv */
void daFm_c::modeThrowInit() {
    /* Nonmatching */
}

/* 000049F4-00004CE4       .text modeThrow__6daFm_cFv */
void daFm_c::modeThrow() {
    resetInvKine();
    if(field_0x2C5 == 1 && cLib_calcTimer(&field_0x650) == 0) {
        modeProc(PROC_0_e, 7);
    }
    if(field_0x684 != 0 && mpActorTarget == NULL) {
        modeProc(PROC_0_e, 10);
        return;
    }
    if(field_0x684 == 0) {
        return;
    }
    if(checkTgHit()) {
        return;
    }

    if(field_0x2D0 != 2 || isNpc(mpActorTarget) != true) {
        s16 angle = fopAcM_searchPlayerAngleY(this);
        cLib_addCalcAngleS2(&shape_angle.y, angle, 4, 0x800);
    }

    if(l_HIO.field_0x0F8 == mpMorf->getFrame()) {
        if (isNpc(mpActorTarget)) {
            mpActorTarget->speedF = l_HIO.field_0x0EC;
            mpActorTarget->speed.y = l_HIO.field_0x0F0;
            fopAcM_cancelCarryNow(mpActorTarget);
            field_0x684 = 0;
            mGrabPos = current.pos;
        } else {
            s16 procName = fopAcM_GetName(mpActorTarget);
            if(procName == PROC_BOMB || procName == PROC_TSUBO) {
                mpActorTarget->current.angle.y = shape_angle.y;
                mpActorTarget->shape_angle.y = shape_angle.y;
                mpActorTarget->speedF = l_HIO.field_0x0EC;
                f32 temp = field_0x9D4 / (REG12_F(13) + 1000.0f);
                f32 temp2 = 0.0f;
                
                if(temp <= 0.0f){
                    temp2 = temp;
                } else {
                    if(temp >= 1.0f) {
                        temp2 = 1.0f;
                    }
                }

                temp2 *= l_HIO.field_0x0F0;
                daTsubo::Act_c* actor = (daTsubo::Act_c*)mpActorTarget;
                
                if(fopAcM_GetName(mpActorTarget) == PROC_TSUBO) {
                    switch(daObj::PrmAbstract(this, PRM_SWSAVE_W, PRM_SWSAVE_S)) {
                        case 0:
                        case 1:
                        case 2:
                        case 4:
                        case 5:
                        case 6:
                            actor->speed.y = temp2;
                            actor->m810 = 1;
                            break;
                    }
                } else {
                    mpActorTarget->speed.y = temp2;
                }
            mpActorTarget->gravity = l_HIO.field_0x0F4;
            fopAcM_cancelCarryNow(mpActorTarget);
            field_0x684 = 0;
            mGrabPos = current.pos;
            }
        }
    }

    if (field_0x2C5 == 11) {
        if (mpMorf->isStop()) {
            field_0x650 = 0x3c;
        }
    }
    //  5] set_drop_spd_y0__Q27daTsubo5Act_cFf (func,weak) found in d_a_fm.o 
    // ^ gets mentioned in debug but cant seem to find its existance
    
    /* Nonmatching */
}

/* 00004CE4-00004D20       .text modeGrabFootDemoInit__6daFm_cFv */
void daFm_c::modeGrabFootDemoInit() {
    /* Nonmatching */
}

/* 00004D20-000050B4       .text modeGrabFootDemo__6daFm_cFv */
void daFm_c::modeGrabFootDemo() {
    /* Nonmatching */
}

/* 000050B4-000050F8       .text modeParalysisInit__6daFm_cFv */
void daFm_c::modeParalysisInit() {
    setAnm(0xd, true);
    field_0x650 = l_HIO.field_0x118;
    /* Nonmatching */
}

/* 000050F8-00005218       .text modeParalysis__6daFm_cFv */
void daFm_c::modeParalysis() {
    if(field_0x650 == l_HIO.field_0x118 - 0x14) {
        enemy_piyo_set(this);
    }
    if(field_0x650 <= l_HIO.field_0x118 - 0x14 && field_0x650 >= l_HIO.field_0x118 -0x3C) {
        fopAcM_seStart(this, JA_SE_CM_MD_PIYO, 0);
    }
    if(field_0x650 == l_HIO.field_0x118 - 0x3c) {
        setAnm(1, false);
        field_0x64C = 0x28;
        field_0x68C = 0x2b00;
    }
    if(cLib_calcTimer(&field_0x650) == 0) {
        modeProc(PROC_0_e, 7);
    }
    cancelGrab();
    checkTgHit();
    /* Nonmatching */
}

/* 00005218-0000525C       .text modeDamageInit__6daFm_cFv */
void daFm_c::modeDamageInit() {
    /* Nonmatching */
}

/* 0000525C-00005308       .text modeDamage__6daFm_cFv */
bool daFm_c::modeDamage() { // idk if bool tbh
    resetInvKine();
    cancelGrab();
    if(field_0x2C5 == 1 && field_0x64C == 0) {
        searchTarget();
        if(mpActorTarget != NULL && !isNpc(mpActorTarget)) {
            modeProc(PROC_0_e, 7);
        }
        if(!cLib_calcTimer(&field_0x650)) {
            modeProc(PROC_0_e, 7);
        }
    }
    return checkTgHit();
    /* Nonmatching */
}

/* 00005308-000053E0       .text modeGrabInit__6daFm_cFv */
void daFm_c::modeGrabInit() {
    /* Nonmatching */
}

/* 000053E0-00005A7C       .text modeGrab__6daFm_cFv */
void daFm_c::modeGrab() {
    /* Nonmatching */
}

/* 00005A7C-00005AD8       .text modeGrabDemoInit__6daFm_cFv */
void daFm_c::modeGrabDemoInit() {
    /* Nonmatching */
}

/* 00005AD8-00005EDC       .text modeGrabDemo__6daFm_cFv */
void daFm_c::modeGrabDemo() {
    /* Nonmatching */
}

/* 00005EDC-00005F04       .text modeDeathInit__6daFm_cFv */
void daFm_c::modeDeathInit() {
    /* Nonmatching */
}

/* 00005F04-00005FA4       .text modeDeath__6daFm_cFv */
void daFm_c::modeDeath() {
    /* Nonmatching */
}

/* 00005FA4-00005FF0       .text modePrepareItemInit__6daFm_cFv */
void daFm_c::modePrepareItemInit() {
    /* Nonmatching */
}

/* 00005FF0-000061A4       .text modePrepareItem__6daFm_cFv */
void daFm_c::modePrepareItem() {
    /* Nonmatching */
}

/* 000061A4-000061CC       .text modeGrabNpcDemoInit__6daFm_cFv */
void daFm_c::modeGrabNpcDemoInit() {
    /* Nonmatching */
}

/* 000061CC-0000638C       .text modeGrabNpcDemo__6daFm_cFv */
void daFm_c::modeGrabNpcDemo() {
    /* Nonmatching */
}

/* 0000638C-000063C4       .text modePlayerStartDemoInit__6daFm_cFv */
void daFm_c::modePlayerStartDemoInit() {
    /* Nonmatching */
}

/* 000063C4-000066A0       .text modePlayerStartDemo__6daFm_cFv */
void daFm_c::modePlayerStartDemo() {
    /* Nonmatching */
}

/* 000066A0-000066A4       .text modeDeleteInit__6daFm_cFv */
void daFm_c::modeDeleteInit() {
    /* Nonmatching */
}

/* 000066A4-00006744       .text modeDelete__6daFm_cFv */
void daFm_c::modeDelete() {
    /* Nonmatching */
}

/* 00006744-000067A0       .text modeBikubikuInit__6daFm_cFv */
void daFm_c::modeBikubikuInit() {
    /* Nonmatching */
}

/* 000067A0-000068D0       .text modeBikubiku__6daFm_cFv */
void daFm_c::modeBikubiku() {
    /* Nonmatching */
}

/* 000068D0-00006D8C       .text modeProc__6daFm_cFQ26daFm_c6Proc_ei */
void daFm_c::modeProc(daFm_c::Proc_e, int) {
    /* Nonmatching */
}

/* 00006D8C-00006DE8       .text setAnm__6daFm_cFScb */
void daFm_c::setAnm(signed char, bool) {
    /* Nonmatching */
}

/* 00006DE8-00006EA4       .text cancelGrab__6daFm_cFv */
void daFm_c::cancelGrab() {
    if(mpActorTarget != NULL) {
        if(field_0x684 != 0 && fopAcM_CheckStatus(mpActorTarget, fopAcStts_CARRY_e) && !checkPlayerGrabTarget()) {
            mpActorTarget->gravity = 0.0f;
            mpActorTarget->speedF = 0.0f;
            mpActorTarget->speed.x = 0.0f;
            mpActorTarget->speed.y = 0.0f;
            mpActorTarget->speed.z = 0.0f;
            mpActorTarget->current.angle.x = 0;
            mpActorTarget->current.angle.z = 0;
            mpActorTarget->shape_angle.x = 0;
            mpActorTarget->shape_angle.z = 0;
            fopAcM_cancelCarryNow(mpActorTarget);
        }
        field_0x684 = 0;
    }
    /* Nonmatching */
}

/* 00006EA4-0000702C       .text calcInvKine__6daFm_cFP10fopAc_ac_c */
void daFm_c::calcInvKine(fopAc_ac_c*) {
    /* Nonmatching */
}

/* 0000702C-000070F4       .text resetInvKine__6daFm_cFv */
void daFm_c::resetInvKine() {
    /* Nonmatching */
}

/* 000070F4-000071E0       .text grabBomb__6daFm_cFv */
void daFm_c::grabBomb() {
    /* Nonmatching */
}

/* 000071E0-0000743C       .text grabTsubo__6daFm_cFv */
void daFm_c::grabTsubo() {
    /* Nonmatching */
}

/* 0000743C-00007680       .text grabPlayer__6daFm_cFv */
void daFm_c::grabPlayer() {
    daPy_lk_c* pLink = daPy_getPlayerLinkActorClass();
    cXyz offset = pLink->getHeadTopPos() - pLink->current.pos;
    cXyz temp(0.0f, 0.0f, 0.0f);
    csXyz angle(0, 0, 0);
    switch(field_0x2C5) {
        case 5:
            return;
        case 6:
            return;
        case 4:
            pLink = daPy_getPlayerLinkActorClass();
            offset = pLink->getHeadTopPos() - pLink->current.pos;
            cXyz offset2(5.0f, 0.0f, 10.0f);
            csXyz angle2;
            angle2.set(-3000, 0, 7000);
            cXyz temp2 = l_HIO.field_0x028 + offset2;
            f32 abs = offset.abs();
            temp2.y -= abs;
            mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(5));
            mDoMtx_stack_c::ZXYrotM(angle.x, angle.y, angle.z);
            mDoMtx_stack_c::transM(temp2);
            MTXCopy(mDoMtx_stack_c::get(), field_0x6BC);
            mDoMtx_stack_c::get();
            break;
    }
    /* Nonmatching */
}

/* 00007680-00007828       .text grabNPC__6daFm_cFv */
void daFm_c::grabNPC() {
    if(isNpc(mpActorTarget) == true) {
        cXyz temp(0.0f, 0.0f, 0.0f);
        csXyz angle(0, 0, 0);
        if(fopAcM_GetName(mpActorTarget) == PROC_NPC_CB1) {
            temp.set(-15.0f, -10.0f, 8.0f);
            angle.x = 0;
            angle.y = 16000;
            angle.z = -4000;
        }

        if(fopAcM_GetName(mpActorTarget) == PROC_NPC_MD) {
            temp.set(10.0f, 0.0f, 5.0f);
            angle.x = 4000;
            angle.y = 18000;
            angle.z = -4000;
        }
        cXyz temp2 = l_HIO.field_0x034 + temp;
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(5));
        mDoMtx_stack_c::transM(temp2);
        mDoMtx_stack_c::ZXYrotM(angle.x, angle.y, angle.z);
        MTXCopy(mDoMtx_stack_c::get(), field_0x6BC);
        mDoMtx_stack_c::multVecZero(&mpActorTarget->current.pos);
        MtxToRot(mDoMtx_stack_c::get(),&mpActorTarget->shape_angle);
    }
    /* Nonmatching */
}

/* 00007828-00007A4C       .text searchTarget__6daFm_cFv */
void daFm_c::searchTarget() {
    /* Nonmatching */
}

/* 00007A4C-00007C18       .text setBaseTarget__6daFm_cFv */
void daFm_c::setBaseTarget() {
    /* Nonmatching */
}

/* 00007C18-00007C4C       .text turnToBaseTarget__6daFm_cFv */
void daFm_c::turnToBaseTarget() {
    cLib_addCalcAngleS2(&shape_angle.y, field_0x9D0, 4, 0x800);
    /* Nonmatching */
}

/* 00007C4C-00007C7C       .text isNpc__6daFm_cFP10fopAc_ac_c */
bool daFm_c::isNpc(fopAc_ac_c* i_actor) {
    if(i_actor == NULL) {
        return false;
    }
    return fopAcM_GetName(i_actor) == PROC_NPC_CB1 || fopAcM_GetName(i_actor) == PROC_NPC_MD;
    /* Nonmatching */
}

/* 00007C7C-00007CD0       .text checkHeight__6daFm_cFP10fopAc_ac_c */
bool daFm_c::checkHeight(fopAc_ac_c* i_actor) {
    if (i_actor == NULL) {
        return false;
    }
    return l_HIO.field_0x0A4* 0.5f > std::fabsf(i_actor->current.pos.y - current.pos.y)  ;
    /* Nonmatching */
}

/* 00007CD0-00007CEC       .text isLink__6daFm_cFP10fopAc_ac_c */
bool daFm_c::isLink(fopAc_ac_c* i_actor) {
    return i_actor == dComIfGp_getLinkPlayer();
    /* Nonmatching */
}

/* 00007CEC-00007D0C       .text isLinkControl__6daFm_cFv */
bool daFm_c::isLinkControl() {
    return dComIfGp_getPlayer(0) != dComIfGp_getLinkPlayer();
    /* Nonmatching */
}

/* 00007D0C-00007F5C       .text areaCheck__6daFm_cFv */
bool daFm_c::areaCheck() {
    cXyz temp;
    bool ret = true;

    s16 angle = 0;
    for(int i = 0; i < 12; i++) {
        temp.set(l_HIO.field_0x0DC, -30.0f, 0.0f);
        mDoMtx_stack_c::transS(current.pos);
        mDoMtx_stack_c::YrotM(angle);
        mDoMtx_stack_c::transM(temp);

        mDoMtx_stack_c::multVecZero(&field_0xA48[i]);
        cXyz temp2 = field_0xA48[i];

        temp2.y += 60.0f;

        if(field_0x2D0 == 0 || field_0x2D0 == 1) {
            cXyz diff = field_0xA48[i] - field_0x69C;
            if(diff.abs() > field_0x2E0) {
                field_0xAD8[i] = false;
                ret = false;
            } else {
                field_0xAD8[i] = true;

            }
        }
        if(field_0xAD8[i] && field_0x2D0 == 2) {
            if(!lineCheck(&temp2, &temp2)) {
                field_0xAD8[i] = false;
                ret = false;

            } else {
                field_0xAD8[i] = true;
            }
        }
        angle += 0x1555;
    }
    return ret;
    /* Nonmatching */
}

/* 00007F5C-00007FDC       .text lineCheck__6daFm_cFP4cXyzP4cXyz */
bool daFm_c::lineCheck(cXyz*, cXyz*) {
    /* Nonmatching */
}

/* 00007FDC-00008044       .text setRnd__6daFm_cFii */
int daFm_c::setRnd(int param_1, int param_2) {
    f32 rnd = cM_rndF(std::fabsf((f32)(param_2 - param_1)));
    return param_1 + (int)rnd;
    /* Nonmatching */
}

/* 00008044-00008114       .text setHoleEffect__6daFm_cFv */
void daFm_c::setHoleEffect() {
    /* Nonmatching */
}

/* 00008114-000081E0       .text holeExecute__6daFm_cFv */
void daFm_c::holeExecute() {
    /* Nonmatching */
}

/* 000081E0-00008258       .text setHoleScale__6daFm_cFfff */
u8 daFm_c::setHoleScale(f32 param_1, f32 param_2, f32 param_3) {
    cLib_addCalc2(&field_0x3E0, param_1, param_2, param_3);
    /* Nonmatching */
}

/* 00008258-00008564       .text _execute__6daFm_cFv */
bool daFm_c::_execute() {
    holeExecute();
    daBomb_c* bomb = (daBomb_c*)fopAcM_SearchByID(mProcId);
    if(bomb != NULL && fopAcM_GetName(bomb) == PROC_BOMB && !bomb->chk_state(daBomb_c::STATE_0)) {
        mpActorTarget = NULL;
        mProcId = 0;
        modeProc(PROC_0_e, 7);
    }
    if(enemy_ice(&mEnemyIce)) {
        setBaseTarget();
        if(mBaseTarget == NULL) {
            bodySetMtx();
            holeSetMtx();
            mpMorf->calc();
        } else {

        }
    }

    /* Nonmatching */
}

/* 00008564-000085A4       .text MtxToRot__6daFm_cFPA4_fP5csXyz */
void daFm_c::MtxToRot(Mtx i_mtx, csXyz* angle) {
    Mtx mtx;
    mDoMtx_inverseTranspose(i_mtx, mtx);
    mDoMtx_MtxToRot(mtx, angle);
    /* Nonmatching */
}

/* 000085A4-000089A4       .text debugDraw__6daFm_cFv */
void daFm_c::debugDraw() {
    if(l_HIO.field_0x00E != 0) {
        for(int i = 0; i < 12; i++) {
            
        }
    }
    /* Nonmatching */
}

/* 000089A4-00008A14       .text holeDraw__6daFm_cFv */
void daFm_c::holeDraw() {
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    mBtkAnm.entry(mpModel->getModelData());
    mDoExt_modelUpdateDL(mpModel);
    mBtkAnm.remove(mpModel->getModelData());

    /* Nonmatching */
}

/* 00008A14-00008A88       .text bodyDraw__6daFm_cFv */
void daFm_c::bodyDraw() {
    g_env_light.setLightTevColorType(mpMorf->getModel(), &tevStr);
    if(mEnemyIce.mFreezeTimer > 0x14) {
        dMat_control_c::iceEntryDL(mpMorf, -1, &mInvisibleModel);
    } else {
        mpMorf->entryDL();
    }

    /* Nonmatching */
}

/* 00008A88-00008B4C       .text _draw__6daFm_cFv */
bool daFm_c::_draw() {
    debugDraw();
    if (field_0x3E0 > 0.015f) {
        holeDraw();
    }

    bool temp = false;
    int temp2 = field_0x2AC;
    if (temp2 != 1 && temp2 != 0x12 && temp2 != 0 &&
        (temp2 != 2 && (temp2 != 4) && (temp2 != 3 && (temp2 != 0x11)))) {
        temp = true;
    }
    if (temp) {
        bodyDraw();
        dSnap_RegistFig(DSNAP_TYPE_UNKB5, this, field_0x61C, shape_angle.y, 1.0f, 1.0f, 1.0f);
    }
    return true;
    /* Nonmatching */
}

/* 00008B4C-00008C78       .text getArg__6daFm_cFv */
void daFm_c::getArg() {
    u32 params = fopAcM_GetParam(this);

    s16 homeAngleX = home.angle.x;
    s16 homeAngleZ = home.angle.z;
    field_0x2C7 = params;
    field_0x2D0 = fopAcM_GetParamBit(params, 0x8, 2);
    field_0x2DC = fopAcM_GetParamBit(params, 0xa, 2);
    m_path_no = fopAcM_GetParamBit(params, 0x10, 8);
    field_0x2D4 = params >> 0x18;
    field_0x2D8 = homeAngleX & 0xff;
    field_0x2C8 = fopAcM_GetParamBit(homeAngleX, 0x08, 8);
    params = homeAngleZ & 0xff;

    if(params == 0xff) {
        field_0x2E0 = 0.0f;
    } else {
        field_0x2E0 = (f32)params * 100.0f;
    }

    if ((f32)home.angle.y != 0.0f && field_0x2D4 != 0xff) {
        field_0x2E4 = 1;
    }

    if (field_0x2D0 == 3) {
        field_0x2D0 = 0;
    }

    if (field_0x2DC == 3) {
        field_0x2DC = 0;
    }

    if (field_0x2E0 == 0.0f) {
        field_0x2E0 = 3000.0f;
    }

    home.angle.z = 0;
    current.angle.z = 0;
    shape_angle.z = 0;
    home.angle.x = 0;
    current.angle.x = 0;
    shape_angle.x = 0;
    /* Nonmatching */
}

/* 00008C78-000090DC       .text createInit__6daFm_cFv */
void daFm_c::createInit() {
    mStts2.Init(200.0f, 0.0f, this);
    mSph.Set(m_sph_src);
    mSph.SetStts(&mStts2);
    mStts.Init(200.0f, 0.0f, this);
    mCyl.Set(m_cyl_src);
    mCyl.SetStts(&mStts);
    mAcchCir.SetWall(30.0f, 200.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));

    mAcch.SetRoofNone();
    if(field_0x2E4 != 0) {
        mAcch.SetWallNone();
    }

    J3DModelData* modelData = mpMorf->getModel()->getModelData();
    for(u16 i = 0; i < modelData->getJointNum(); i++) {
        switch(i) {
            case 0: 
            case 1:
            case 2:
            case 3:
            case 5:
                modelData->getJointNodePointer(i)->setCallBack(nodeControl_CB);
                break;

        }
    }

    for(int i = 0; i < 6; i++) {
        field_0x330[i] = ZeroQuat;
    }
    bodySetMtx();
    holeSetMtx();
    mpMorf->calc();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);

    if(field_0x2D0 == 0) {
        itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Fmastr", 0);
    } else if(field_0x2D0 == 1) {
        itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Fmastr1", 0);
    } else if(field_0x2D0 == 2) {
        itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Fmastr2", 0);
    }

    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -300.0f, -50.0f, -300.0f, 300.0f, 400.0f, 300.0f);
    if(m_path_no != 0xFF) {
        mpPath = dPath_GetRoomPath(m_path_no, fopAcM_GetRoomNo(this));
    }
    mEnemyIce.mpActor = this;
    mEnemyIce.m00C = 1;
    mEnemyIce.mWallRadius = 100.0f;
    mEnemyIce.mCylHeight = 200.0f;

    mBtHeight = 240.0f;
    mBtBodyR = 100.0f;
    attention_info.flags = 0;
    stealItemLeft = 3;
    max_health = l_HIO.mMaxHealth;
    health = max_health;
    mGrabPos = current.pos;
    
    field_0x684 = 0;
    mpActorTarget = NULL;
    field_0x69C = current.pos;
    setBaseTarget();
    field_0x690 = current.pos;
    setAnm(8, false);
    field_0x394 = cM_rndF(9.0f) + 1.0f;
    field_0x610 = l_HIO.field_0x028;
    if(field_0x2AC != 0x11) {
        if(field_0x2D4 != 0xff && !dComIfGs_isSwitch(field_0x2D4, fopAcM_GetRoomNo(this))) {
            modeProc(PROC_0_e, 0);
        } else {
            switch(field_0x2D0) {
                case 0:
                    modeProc(PROC_0_e, 2);
                    break;
                case 1:
                    modeProc(PROC_0_e, 3);
                    JUT_ASSERT(0x1444, m_path_no != 0xff);
                    break;
                case 2:
                    modeProc(PROC_0_e, 4);
                    break;
            }
        }
    }


    /* Nonmatching */
}

/* 000090DC-00009258       .text _create__6daFm_cFv */
cPhs_State daFm_c::_create() {
    fopAc_ac_c* ac;
    fopAcM_SetupActor(this, daFm_c);
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, m_arc_name);
    if(phase_state == cPhs_COMPLEATE_e) {
        phase_state = cPhs_ERROR_e;
    }
    
    if(parentActorID != 1) {
        ac = fopAcM_SearchByID(parentActorID);

        if(ac != NULL && fopAc_IsActor(ac) && isLink(ac)) {
            modeProc(PROC_0_e, 0x11);
        }
    }

    if(field_0x2AC != 0x11) {
        getArg();
        if(field_0x2D8 != 0xff && dComIfGs_isSwitch(field_0x2D8, fopAcM_GetRoomNo(this))) {
            return cPhs_ERROR_e;
        }

        if(field_0x2D4 != 0xff && dComIfGs_isSwitch(field_0x2D4, fopAcM_GetRoomNo(this)) && field_0x2E4 != 0) {
            return cPhs_ERROR_e;
        }
    }

    if(!fopAcM_entrySolidHeap(this, createHeap_CB, 0x2100)) {
        return cPhs_ERROR_e;
    }
    createInit();
    return phase_state;


    /* Nonmatching */
}

/* 0000A094-0000A0FC       .text _delete__6daFm_cFv */
bool daFm_c::_delete() {
    cancelGrab();
    dComIfG_resDelete(&mPhs, m_arc_name);
    mpFollowEcallBack.remove();
    if(heap != NULL) {
        mpMorf->stopZelAnime();
    }
    return TRUE;
    /* Nonmatching */
}

/* 0000A0FC-0000A11C       .text daFmCreate__FPv */
static cPhs_State daFmCreate(void* i_this) {
    return ((daFm_c*)i_this)->_create();
}

/* 0000A11C-0000A140       .text daFmDelete__FPv */
static BOOL daFmDelete(void* i_this) {
    return ((daFm_c*)i_this)->_delete();
}

/* 0000A140-0000A164       .text daFmExecute__FPv */
static BOOL daFmExecute(void* i_this) {
    return ((daFm_c*)i_this)->_execute();
}

/* 0000A164-0000A188       .text daFmDraw__FPv */
static BOOL daFmDraw(void* i_this) {
    return ((daFm_c*)i_this)->_draw();
}

/* 0000A188-0000A190       .text daFmIsDelete__FPv */
static BOOL daFmIsDelete(void*) {
    return TRUE;
}

static actor_method_class daFmMethodTable = {
    (process_method_func)daFmCreate,
    (process_method_func)daFmDelete,
    (process_method_func)daFmExecute,
    (process_method_func)daFmIsDelete,
    (process_method_func)daFmDraw,
};

actor_process_profile_definition g_profile_FM = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_FM,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daFm_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_FM,
    /* Actor SubMtd */ &daFmMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e | fopAcStts_UNK200000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
