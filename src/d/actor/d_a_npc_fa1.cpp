/**
 * d_a_npc_fa1.cpp
 * Item - Fairy / 回復妖精 (Recovery fairy)
 */

#include "d/actor/d_a_npc_fa1.h"
#include "SSystem/SComponent/c_lib.h"
#include "d/d_com_inf_game.h"
#include "d/d_item.h"
#include "d/d_priority.h"
#include "d/d_procname.h"
#include "d/d_snap.h"
#include "f_op/f_op_actor_mng.h"

#include "weak_data_1811.h" // IWYU pragma: keep


/* 800FAFC0-800FB004       .text __ct__16daNpc_Fa1_HIO3_cFv */
daNpc_Fa1_HIO3_c::daNpc_Fa1_HIO3_c() {
    mNo = -1;
    static const hio_prm_c init_data = {
        1.0f,
        0.1f,
        50.0f,
        20.0f,
        0x3600,
    };
    prm = init_data;
}

/* 800FB004-800FB068       .text __ct__16daNpc_Fa1_HIO2_cFv */
daNpc_Fa1_HIO2_c::daNpc_Fa1_HIO2_c() {
    mNo = -1;
    static const hio_prm_c init_data = {
        20.0f,
        1.5f,
        -2.5f,
        5.0f,
        -2.5f,
        5.0f,
        0x3600,
        0xB4,
        3,
    };
    prm = init_data;
}

/* 800FB068-800FB174       .text __ct__15daNpc_Fa1_HIO_cFv */
daNpc_Fa1_HIO_c::daNpc_Fa1_HIO_c() {
    mNo = -1;
    static const hio_prm_c init_data = {
        3.0f,
        3.5f,
        40.0f,
        12.0f,
        8.0f,
        200.0f,
        100.0f,
        -50.0f,
        2.0f,
        3.0f,
        -2.5f,
        5.0f,
        -3.0f,
        4000,
        5000,
        0x55,
        0x2D,
        500,
        300,
        0x2000,
        0x55,
        0x157C,
        400,
    };
    prm = init_data;
}

static daNpc_Fa1_HIO_c l_HIO;
static s32 l_hio_counter;

static dCcD_SrcCyl l_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsEnemy_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsEnemy_e,
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
        /* Radius */ 10.0f,
        /* Height */ 20.0f,
    },
};

daNpc_Fa1_c::MoveFunc_t moveProc[] = {
    &daNpc_Fa1_c::normal_move,
    &daNpc_Fa1_c::get_player_move,
    &daNpc_Fa1_c::escape_move,
    &daNpc_Fa1_c::bottle_appear_move,
    &daNpc_Fa1_c::bottle_baba_wait,
    &daNpc_Fa1_c::bottle_baba_move,
    &daNpc_Fa1_c::bottle_baba_move2,
    &daNpc_Fa1_c::bigelf_change,
    &daNpc_Fa1_c::hover_move,
};

daNpc_Fa1_c::MoveSubFunc_t moveSubProc[] = {
    &daNpc_Fa1_c::straight,
    &daNpc_Fa1_c::turn,
    &daNpc_Fa1_c::areaMove,
    &daNpc_Fa1_c::areaOutMove,
};

daNpc_Fa1_c::BottleMoveSubFunc_t bottleMoveSubProc[] = {
    &daNpc_Fa1_c::up1,
    &daNpc_Fa1_c::down,
    &daNpc_Fa1_c::up2,
};

daNpc_Fa1_c::BottleBabaSubFunc_t bottleBabaSubProc[] = {
    &daNpc_Fa1_c::baba_down,
    &daNpc_Fa1_c::up2,
};

/* 800FB174-800FB1BC       .text __dt__16daNpc_Fa1_HIO3_cFv */
//daNpc_Fa1_HIO3_c::~daNpc_Fa1_HIO3_c() {
//    /* Nonmatching */
//}
//
///* 800FB1BC-800FB204       .text __dt__16daNpc_Fa1_HIO2_cFv */
//daNpc_Fa1_HIO2_c::~daNpc_Fa1_HIO2_c() {
//    /* Nonmatching */
//}

/* 800FB204-800FB22C       .text __ct__28daNpc_Fa1_McaMorfCallBack1_cFv */
daNpc_Fa1_McaMorfCallBack1_c::daNpc_Fa1_McaMorfCallBack1_c() {
    m04 = 0;
    m06 = 0;
}

/* 800FB22C-800FB24C       .text execute__28daNpc_Fa1_McaMorfCallBack1_cFUsP16J3DTransformInfo */
bool daNpc_Fa1_McaMorfCallBack1_c::execute(unsigned short param_1, J3DTransformInfo* param_2) {
    if (param_1 == m06) {
        param_2->mRotation.x = m04;
    }
    return TRUE;
}

/* 800FB24C-800FB2B8       .text setPointLightParam__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::setPointLightParam() {
    mPointLight.mPos = attention_info.position;
    mPointLight.mColor.r = 200;
    mPointLight.mColor.g = 200;
    mPointLight.mColor.b = 200;
    mPointLight.mPower = 100.0f;
    mPointLight.mFluctuation = 0.0f;
    mPointLight.mFluctuation = dKy_yuragi_ratio_set(0.7f);
}

/* 800FB2B8-800FB514       .text createInit__11daNpc_Fa1_cFv */
int daNpc_Fa1_c::createInit() {
    m794 = fopAcM_GetParam(this);
    m764 = NULL;
    // zero() doesn't match.
    m768.setall(0.0f);
    m793 = 0;
    if (m794 == 3) {
        init_bottle_baba_wait();
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
    } else if ((m794 == 2) || (m794 == 5)) {
        init_bottle_appear_move();
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
    } else if (m794 == 6) {
        init_hover_move();
        fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
    } else {
        if (m794 == 4) {
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            scale.x = 500.0f;
        } else {
            scale.x = l_HIO.prm.m10;
        }
        if (m794 == 1) {
            m793 = 1;
            fopAcM_OffStatus(this, fopAcStts_NOCULLEXEC_e);
            current.angle.y += (s16)(cLib_getRndValue((u16)0, (u16)0xFF) * 0x100);
        } else {
            m794 = 0;
        }
        init_normal_move();
    }
    cXyz local_18(current.pos);
    local_18.y += 60.0f;
    mGndChk.SetPos(&local_18);
    mGroundYPos = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if ((m794 != 6) && (mGroundYPos != -G_CM3D_F_INF)) {
        home.pos.y = mGroundYPos + 50.0f;
    }
    mStts.Init(0xFF, 0xFF, this);
    mCyl.SetStts(&mStts);
    mCyl.Set(l_cyl_src);
    setMtx();
    if (m794 == 3) {
        setPointLightParam();
        dKy_efplight_set(&mPointLight);
    }
    JPABaseEmitter* pJVar4 = dComIfGp_particle_set(dPa_name::ID_COMMON_0052, &current.pos, NULL,
                                                   NULL, 0xFF, &mSparklePtclCallback);
    mpEmitter = pJVar4;
    return TRUE;
}

/* 800FB514-800FB5D8       .text _draw__11daNpc_Fa1_cFv */
BOOL daNpc_Fa1_c::_draw() {
    J3DModel* pJVar1 = mpDoExt_McaMorf->getModel();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pJVar1, &tevStr);
    mpDoExt_McaMorf->entryDL();
    f32 fVar1 = mGroundYPos;
    if (fVar1 != -G_CM3D_F_INF) {
        dComIfGd_setSimpleShadow(&current.pos, fVar1, 10.0f, &m774, 0, 1.0f,
                                 &dDlst_shadowControl_c::mSimpleTexObj);
    }
    dSnap_RegistFig(DSNAP_TYPE_FA, this, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 800FB5D8-800FB6AC       .text _execute__11daNpc_Fa1_cFv */
BOOL daNpc_Fa1_c::_execute() {
    cLib_calcTimer(&mTimer);
    (this->*moveProc[mActionType])();
    shape_angle.y = current.angle.y;
    mpDoExt_McaMorf->play(NULL, 0, 0);
    setMtx();
    if (m794 == 3) {
        setPointLightParam();
    }
    if ((mActionType == ActionType_PLAYER_MOVE_e) && (mpEmitter != NULL)) {
        mpEmitter->mRate = 1.0f;
    }
    dComIfGp_att_LookRequest(this, 400.0f, 300.0f, -300.0f, 0x6000, 1);
    return TRUE;
}

/* 800FB6AC-800FB730       .text checkBinCatch__11daNpc_Fa1_cFv */
BOOL daNpc_Fa1_c::checkBinCatch() {
    if (eventInfo.checkCommandCatch()) {
        fopAcM_delete(this);
        return TRUE;
    }
    
    dComIfGp_att_CatchRequest(
        this, dItem_FAIRY_BOTTLE_e,
        l_HIO.prm.m1C, l_HIO.prm.m20,
        l_HIO.prm.m24, l_HIO.prm.m48,
        1
    );
    eventInfo.onCondition(dEvtCnd_CANCATCH_e);
    
    return FALSE;
}

/* 800FB730-800FB830       .text position_move__11daNpc_Fa1_cFff */
void daNpc_Fa1_c::position_move(float param_1, float param_2) {
    f32 fVar1;

    fVar1 = current.pos.y - home.pos.y;
    if (fVar1 > param_1) {
        maxFallSpeed = -param_2;
    } else if (fVar1 < -param_1) {
        maxFallSpeed = param_2;
    }
    if (maxFallSpeed < 0.0f) {
        speed.y -= gravity;
        if (speed.y < maxFallSpeed) {
            speed.y = maxFallSpeed;
        }
    } else {
        speed.y += gravity;
        if (speed.y > maxFallSpeed) {
            speed.y = maxFallSpeed;
        }
    }
    speed.x = speedF * cM_ssin(current.angle.y);
    speed.z = speedF * cM_scos(current.angle.y);
    fopAcM_posMove(this, NULL);
}

/* 800FB830-800FB904       .text BGCheck__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::BGCheck() {
    cM3dGPla* pcVar1;
    s32 bVar2;
    f32 fVar3;

    mGndChk.SetPos(&current.pos);
    fVar3 = dComIfG_Bgsp()->GroundCross(&mGndChk);
    mGroundYPos = fVar3;
    if (fVar3 != -G_CM3D_F_INF) {
        pcVar1 = dComIfG_Bgsp()->GetTriPla(mGndChk);
        m774.set(pcVar1->mNormal);
        bVar2 = dComIfG_Bgsp()->GetRoomId(mGndChk);
        current.roomNo = bVar2;
        tevStr.mRoomNo = bVar2;
        bVar2 = dComIfG_Bgsp()->GetPolyColor(mGndChk);
        tevStr.mEnvrIdxOverride = bVar2;
    } else {
        m774.set(0.0f, 1.0f, 0.0f);
    }
}

/* 800FB904-800FB988       .text init_normal_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_normal_move() {
    mActionType = ActionType_NORMAL_MOVE_e;
    speedF = l_HIO.prm.m08;
    gravity = 0.1f;
    maxFallSpeed = -1.0f;
    mTimer = cLib_getRndValue((u16)l_HIO.prm.m44, (u16)60);
    if (m794 == 4) {
        init_areaMove();
    } else {
        init_straight2();
    }
}

/* 800FB988-800FBA68       .text normal_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::normal_move() {
    speedF = l_HIO.prm.m08;
    (this->*moveSubProc[mMoveType])();
    position_move(10.0f, 1.0f);
    BGCheck();
    findPlayer();
    mCyl.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCyl);
    if (mCyl.ChkCoHit()) {
        init_get_player_move();
    } else if ((!checkBinCatch() && (m793 & 1) != 0) && (mTimer == 0)) {
        init_escape_move();
    }
}

/* 800FBA68-800FBAB0       .text init_straight__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_straight() {
    mMoveType = MoveType_STRAIGHT_e;
    mMoveTimer = cLib_getRndValue((u8)60, (u8)60);
    gravity = 0.1f;
}

/* 800FBAB0-800FBAC8       .text init_straight2__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_straight2() {
    mMoveType = MoveType_STRAIGHT_e;
    mMoveTimer = 0;
    gravity = 1.0f;
}

/* 800FBAC8-800FBBC8       .text straight__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::straight() {
    scale.x = l_HIO.prm.m10;
    if (!cLib_calcTimer(&mMoveTimer)) {
        cXyz local_28 = current.pos - home.pos;
        if (local_28.absXZ() > scale.x) {
            init_turn();
        }
    }
}

/* 800FBBC8-800FBC10       .text init_turn__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_turn() {
    mMoveType = MoveType_TURN_e;
    mMoveTimer = cLib_getRndValue((u8)60, (u8)60);
    gravity = 0.1f;
}

/* 800FBC10-800FBCA0       .text turn__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::turn() {
    if (cLib_calcTimer(&mMoveTimer)) {
        cXyz local_28 = current.pos - home.pos;
        cLib_addCalcAngleS(&current.angle.y, cM_atan2s(-local_28.x, -local_28.z), 0x20, 0x800, 1);
    } else {
        init_straight();
    }
}

/* 800FBCA0-800FBCC0       .text init_areaMove__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_areaMove() {
    mMoveType = MoveType_UP_e;
    gravity = 1.0f;
    m798 = 0;
    m79A = 0;
}

/* 800FBCC0-800FBE14       .text areaMove__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::areaMove() {
    s16 sVar1;

    cXyz local_28 = current.pos - home.pos;
    if (local_28.absXZ() > scale.x) {
        init_areaOutMove();
    } else {
        sVar1 = current.angle.y;
        if (!cLib_calcTimer(&m798)) {
            m79A ^= 1;
            m798 = cLib_getRndValue(0xF, 0x14) & 0xFF;
        }
        sVar1 += m79A ? -0x2000 : 0x2000;
        cLib_addCalcAngleS(&current.angle.y, sVar1, 0x20, 0x800, 1);
    }
}

/* 800FBE14-800FBE34       .text init_areaOutMove__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_areaOutMove() {
    mMoveType = MoveType_AREAOUTMOVE_e;
    gravity = 0.1f;
    m798 = 0;
    m79A = 0;
}

/* 800FBE34-800FBF94       .text areaOutMove__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::areaOutMove() {
    s16 sVar2;

    cXyz local_28 = current.pos - home.pos;
    if (local_28.absXZ() < scale.x) {
        init_areaMove();
    } else {
        sVar2 = (s16)cLib_targetAngleY(&current.pos, &home.pos);
        if (!cLib_calcTimer(&m798)) {
            m79A ^= 1;
            m798 = cLib_getRndValue(0xF, 0x14) & 0xFF;
        }
        sVar2 += m79A ? -0x2000 : 0x2000;
        cLib_addCalcAngleS(&current.angle.y, sVar2, 0x20, 0x800, 1);
    }
}

/* 800FBF94-800FC03C       .text init_get_player_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_get_player_move() {
    mActionType = ActionType_PLAYER_MOVE_e;
    mTimer = l_HIO.prm.m42;
    m78A = l_HIO.prm.m3C;
    m780 = 60.0f;
    current.angle.y = 0;
    mMcaMorfCallback1.m04 = 0;
    current.pos.y = dComIfGp_getPlayer(0)->current.pos.y;
    mDoAud_seStart(JA_SE_OBJ_FAILY_GET, &current.pos, 0,
                   dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
}

/* 800FC03C-800FC178       .text get_player_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::get_player_move() {
    f32 fVar1 = mpDoExt_McaMorf->mFrameCtrl.getRate();
    fVar1 += 0.05f;
    if (fVar1 > 1.5f) {
        fVar1 = 1.5f;
    }
    mpDoExt_McaMorf->mFrameCtrl.setRate(fVar1);
    s16 sVar4 = m78A;
    current.angle.y = current.angle.y - sVar4;
    sVar4 += l_HIO.prm.m40;
    if (sVar4 > l_HIO.prm.m3E) {
        sVar4 = l_HIO.prm.m3E;
    }
    m78A = sVar4;
    cXyz* local_18 = &m768;
    s16 uVar2 = current.angle.y + 0x4000;
    fopAc_ac_c* apdVar3 = dComIfGp_getPlayer(0);
    fVar1 = m780;
    local_18->x = fVar1 * cM_ssin(uVar2);
    local_18->z = fVar1 * cM_scos(uVar2);
    local_18->y += l_HIO.prm.m0C;
    current.pos = apdVar3->current.pos + *local_18;
    BGCheck();
    if (mTimer == 0) {
        execItemGet(dItem_RECOVER_FAIRY_e);
        fopAcM_delete(this);
    }
}

/* 800FC178-800FC1A4       .text init_escape_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_escape_move() {
    mActionType = ActionType_ESCAPE_MOVE_e;
    gravity = l_HIO.prm.m18;
    maxFallSpeed = l_HIO.prm.m14;
    mTimer = l_HIO.prm.m46;
}

/* 800FC1A4-800FC2E0       .text escape_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::escape_move() {
    s16 sVar2;

    speed.y += gravity;
    if (speed.y > maxFallSpeed) {
        speed.y = maxFallSpeed;
    }
    speed.x = speedF * cM_ssin(current.angle.y);
    speed.z = speedF * cM_scos(current.angle.y);
    fopAcM_posMove(this, NULL);
    BGCheck();
    sVar2 = mMcaMorfCallback1.m04;
    if (sVar2 < 0) {
        sVar2 += 0x800;
        if (sVar2 > 0) {
            sVar2 = 0;
        }
    } else if (sVar2 > 0) {
        sVar2 += -0x800;
        if (sVar2 < 0) {
            sVar2 = 0;
        }
    }
    mMcaMorfCallback1.m04 = sVar2;
    mCyl.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCyl);
    if (mCyl.ChkCoHit()) {
        init_get_player_move();
    } else if (mTimer == 0) {
        fopAcM_delete(this);
    }
}

/* 800FC2E0-800FC310       .text init_hover_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_hover_move() {
    mActionType = ActionType_HOVER_MOVE_e;
    gravity = l_HIO.m78.prm.m0C;
    maxFallSpeed = -l_HIO.m78.prm.m08;
    speedF = 0.0f;
}

/* 800FC310-800FC380       .text hover_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::hover_move() {
    position_move(l_HIO.m78.prm.m10, l_HIO.m78.prm.m08);
    BGCheck();
    s16 target = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
    cLib_addCalcAngleS(&current.angle.y, target, 8, 0x2000, 0x400);
}

/* 800FC380-800FC3C8       .text init_bottle_appear_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_bottle_appear_move() {
    mActionType = ActionType_BOTTLE_APPEAR_MOVE_e;
    init_up1();
    if (m794 == 5) {
        execItemGet(dItem_RECOVER_FAIRY_e);
    }
}

/* 800FC3C8-800FC5A8       .text bottle_appear_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::bottle_appear_move() {
    f32 fVar1 = mpDoExt_McaMorf->mFrameCtrl.getRate();
    fVar1 += 0.05f;
    if (fVar1 > 1.5f) {
        fVar1 = 1.5f;
    }
    mpDoExt_McaMorf->mFrameCtrl.setRate(fVar1);
    current.angle.y = current.angle.y - m78A;
    m78A += m78E;
    if (m78A > m78C) {
        m78A = m78C;
    }
    s16 uVar2 = current.angle.y + 0x4000;
    fopAc_ac_c* apdVar3 = dComIfGp_getPlayer(0);
    m768.x = m780 * cM_ssin(uVar2);
    m768.z = m780 * cM_scos(uVar2);
    m768.y += speed.y;
    current.pos = apdVar3->current.pos + m768;
    if (maxFallSpeed < 0.0f) {
        speed.y -= gravity;
        if (speed.y < maxFallSpeed) {
            speed.y = maxFallSpeed;
        }
    } else {
        speed.y += gravity;
        if (speed.y > maxFallSpeed) {
            speed.y = maxFallSpeed;
        }
    }
    m780 += 2.0f;
    if (m780 > 60.0f) {
        m780 = 60.0f;
    }
    BGCheck();
    (this->*bottleMoveSubProc[mMoveType])();
    if (mTimer == 0) {
        if (m794 != 5) {
            execItemGet(dItem_RECOVER_FAIRY_e);
        }
        fopAcM_delete(this);
    }
}

/* 800FC5A8-800FC6DC       .text init_up1__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_up1() {
    mMoveType = MoveType_STRAIGHT_e;
    mTimer = l_HIO.prm.m4A;
    maxFallSpeed = l_HIO.prm.m30;
    speed.y = l_HIO.prm.m28;
    gravity = l_HIO.prm.m34;
    m78A = 0;
    m78C = 0;
    m78E = 0;
    fopAc_ac_c* apdVar3 = dComIfGp_getPlayer(0);
    m768 = current.pos - apdVar3->current.pos;
    m780 = m768.absXZ();
    current.angle.y = cM_atan2s(m768.x, m768.z) + -0x4000;
}

/* 800FC6DC-800FC70C       .text up1__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::up1() {
    if (speed.y < 0.0f) {
        init_down();
    }
}

/* 800FC70C-800FC730       .text init_down__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_down() {
    mMoveType = MoveType_TURN_e;
    m78C = l_HIO.prm.m4C;
    m78E = l_HIO.prm.m4E;
}

/* 800FC730-800FC768       .text down__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::down() {
    if (m768.y < l_HIO.prm.m38) {
        init_up2();
    }
}

/* 800FC768-800FC7E0       .text init_up2__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_up2() {
    mMoveType = MoveType_UP_e;
    maxFallSpeed = l_HIO.prm.m2C;
    mDoAud_seStart(JA_SE_OBJ_BOTTLE_FAILY, &current.pos, 0,
                   dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
}

/* 800FC7E0-800FC7E4       .text up2__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::up2() {
    /* Empty function */
}

/* 800FC7E4-800FC81C       .text init_bottle_baba_wait__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_bottle_baba_wait() {
    mActionType = ActionType_BOTTLE_BABA_WAIT_e;
    speed.setall(0.0f);
    speedF = 0.0f;
    maxFallSpeed = 0.0f;
    gravity = 0.0f;
    mTimer = l_HIO.m50.prm.m24;
}

/* 800FC81C-800FC848       .text bottle_baba_wait__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::bottle_baba_wait() {
    if (mTimer == 0) {
        init_bottle_baba_move2();
    }
}

/* 800FC848-800FC8E4       .text init_bottle_baba_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_bottle_baba_move() {
    mActionType = ActionType_BOTTLE_BABA_MOVE_e;
    fopAcM_SearchByName(PROC_NPC_BA1, &m764);
    mTimer = l_HIO.m50.prm.m22;
    speedF = l_HIO.m50.prm.m08;
    m798 = 1;
    m79C = l_HIO.m50.prm.m10;
    m7A0 = l_HIO.m50.prm.m0C;
    if (m764 != 0) {
        current.pos.x = m764->current.pos.x + 30.0f;
        current.pos.z = m764->current.pos.z;
    }
    init_baba_down();
}

/* 800FC8E4-800FCA94       .text bottle_baba_move__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::bottle_baba_move() {
    if (m764 == NULL) {
        init_bottle_baba_move();
        BGCheck();
    } else {
        speedF = l_HIO.m50.prm.m08;
        cXyz local_28 = m764->current.pos - current.pos;
        s16 sVar1 = cM_atan2s(local_28.x, local_28.z);
        current.angle.y = sVar1 + l_HIO.m50.prm.m20;
        speed.x = speedF * cM_ssin(current.angle.y);
        speed.z = speedF * cM_scos(current.angle.y);
        if (maxFallSpeed < 0.0f) {
            speed.y -= gravity;
            if (speed.y < maxFallSpeed) {
                speed.y = maxFallSpeed;
            }
        } else {
            speed.y += gravity;
            if (speed.y > maxFallSpeed) {
                speed.y = maxFallSpeed;
            }
        }
        current.pos += speed;
        BGCheck();
        u8 dVar1 = mMoveType;
        (this->*bottleBabaSubProc[dVar1])();
        if ((dVar1 == 1) && (current.pos.y > m764->current.pos.y + 150.0f)) {
            fopAcM_delete(this);
        }
    }
}

/* 800FCA94-800FCAF4       .text init_bottle_baba_move2__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_bottle_baba_move2() {
    mActionType = ActionType_BOTTLE_BABA_MOVE2_e;
    m764 = dComIfGp_getPlayer(0);
    speedF = l_HIO.m50.prm.m08;
    m798 = 0;
    m79C = l_HIO.m50.prm.m18;
    m7A0 = l_HIO.m50.prm.m14;
    init_baba_down();
}

/* 800FCAF4-800FCC94       .text bottle_baba_move2__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::bottle_baba_move2() {
    if (m764 == NULL) {
        init_bottle_baba_move2();
        BGCheck();
    } else {
        speedF = l_HIO.m50.prm.m08;
        cXyz local_28 = m764->current.pos - current.pos;
        s16 sVar1 = cM_atan2s(local_28.x, local_28.z);
        current.angle.y = sVar1 + l_HIO.m50.prm.m20;
        speed.x = speedF * cM_ssin(current.angle.y);
        speed.z = speedF * cM_scos(current.angle.y);
        if (maxFallSpeed < 0.0f) {
            speed.y -= gravity;
            if (speed.y < maxFallSpeed) {
                speed.y = maxFallSpeed;
            }
        } else {
            speed.y += gravity;
            if (speed.y > maxFallSpeed) {
                speed.y = maxFallSpeed;
            }
        }
        current.pos += speed;
        BGCheck();
        (this->*bottleBabaSubProc[mMoveType])();
        if ((current.pos.y > m764->current.pos.y + 180.0f)) {
            init_bottle_baba_move();
        }
    }
}

/* 800FCC94-800FCD28       .text init_baba_down__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_baba_down() {
    mMoveType = MoveType_STRAIGHT_e;
    speed.y = 0.0f;
    maxFallSpeed = m79C;
    gravity = l_HIO.m50.prm.m1C;
    if (mActionType == ActionType_BOTTLE_BABA_MOVE_e) {
        mDoAud_seStart(JA_SE_OBJ_BA_FAILY_2, &current.pos, 0,
                       dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }
}

/* 800FCD28-800FCD5C       .text baba_down__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::baba_down() {
    if (current.pos.y < m764->current.pos.y) {
        init_baba_up();
    }
}

/* 800FCD5C-800FCDD8       .text init_baba_up__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_baba_up() {
    mMoveType = MoveType_TURN_e;
    maxFallSpeed = m7A0;
    if (mActionType == ActionType_BOTTLE_BABA_MOVE2_e) {
        mDoAud_seStart(JA_SE_OBJ_BA_FAILY_1, &current.pos, 0,
                       dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }
}

/* 800FCDD8-800FCE7C       .text init_bigelf_change__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::init_bigelf_change() {
    mActionType = ActionType_BIGELF_CHANGE_e;
    fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
    speedF = l_HIO.m78.prm.m14;
    speed.x = speedF * cM_ssin(current.angle.y);
    speed.z = speedF * cM_scos(current.angle.y);
    current.pos += speed;
}

/* 800FCE7C-800FCF4C       .text bigelf_change__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::bigelf_change() {
    cXyz local_28 = home.pos - current.pos;
    s16 sVar1 = cM_atan2s(local_28.x, local_28.z);
    current.angle.y = sVar1 + l_HIO.m78.prm.m18;
    speed.x = speedF * cM_ssin(current.angle.y);
    speed.z = speedF * cM_scos(current.angle.y);
    current.pos += speed;
    BGCheck();
}

/* 800FCF4C-800FD050       .text findPlayer__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::findPlayer() {
    /* Nonmatching */
    s16 sVar1;
    s16 sVar2;
    s16 sVar4;
    s16 sVar6;
    cXyz local_28;
    fopAc_ac_c* apdVar3 = dComIfGp_getPlayer(0);

    local_28 = apdVar3->current.pos - current.pos;
    sVar2 = cM_atan2s(local_28.x, local_28.z) - current.angle.y;
    sVar1 = mMcaMorfCallback1.m04;
    if (sVar2 < 0) {
        if (sVar2 < -0x4000) {
            sVar2 = -0x4000;
        }
        sVar4 = ((sVar2 - sVar1) >> 2);
        if (sVar4 < -0x800) {
            sVar4 = -0x800;
        }
        sVar6 = sVar1 + sVar4;
        if (sVar6 < sVar2) {
            sVar6 = sVar2;
        }
    } else {
        if (sVar2 > 0x4000) {
            sVar2 = 0x4000;
        }
        sVar4 = ((sVar2 - sVar1) >> 2);
        if (sVar4 > 0x800) {
            sVar4 = 0x800;
        }
        sVar6 = sVar1 + sVar4;
        if (sVar6 > sVar2) {
            sVar6 = sVar2;
        }
    }
    mMcaMorfCallback1.m04 = sVar6;
}

/* 800FD050-800FD0F0       .text _delete__11daNpc_Fa1_cFv */
BOOL daNpc_Fa1_c::_delete() {
    mSparklePtclCallback.end();
    if (m794 == 3) {
        dKy_efplight_cut(&mPointLight);
    }
    if (l_hio_counter != 0) {
        l_hio_counter--;
    }
    if ((l_hio_counter <= 0) && (l_HIO.mNo >= 0)) {
        mDoHIO_deleteChild(l_HIO.mNo);
        l_HIO.mNo = -1;
    }
    return TRUE;
}

/* 800FD0F0-800FD110       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* i_this) {
    return ((daNpc_Fa1_c*)i_this)->CreateHeap();
}

/* 800FD110-800FD224       .text _create__11daNpc_Fa1_cFv */
cPhs_State daNpc_Fa1_c::_create() {
    static u32 a_heap_size_tbl = 0x1100;
    cPhs_State phase_state = cPhs_COMPLEATE_e;

    fopAcM_SetupActor(this, daNpc_Fa1_c);
    if (fopAcM_entrySolidHeap(this, CheckCreateHeap, a_heap_size_tbl)) {
        fopAcM_SetMtx(this, mpDoExt_McaMorf->mpModel->getBaseTRMtx());
    } else {
        return cPhs_ERROR_e;
    }
    if (l_HIO.mNo < 0) {
        l_HIO.mNo = mDoHIO_createChild("回復妖精", &l_HIO);  // Recovery Fairy
        l_hio_counter = 1;
    } else {
        l_hio_counter++;
    }
    if (!createInit()) {
        phase_state = cPhs_ERROR_e;
    }
    return phase_state;
}

/* 800FD4E8-800FD61C       .text CreateHeap__11daNpc_Fa1_cFv */
int daNpc_Fa1_c::CreateHeap() {
    J3DModelData* pModelData = (J3DModelData*)dComIfG_getObjectRes("Always", ALWAYS_BDL_FA);
    mpDoExt_McaMorf =
        new mDoExt_McaMorf(pModelData,
            &mMcaMorfCallback1, NULL,
            (J3DAnmTransformKey*)dComIfG_getObjectRes("Always", ALWAYS_BCK_FA),
            J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, 0, NULL,
            0x00000000,
            0x11020203);
    if (mpDoExt_McaMorf == NULL) {
        return false;
    } else if (mpDoExt_McaMorf->getModel() == NULL) {
        mpDoExt_McaMorf = NULL;
        return false;
    } else {
        mMcaMorfCallback1.m06 = pModelData->getJointName()->getIndex("neck");
        mMcaMorfCallback1.m04 = 0;
        return true;
    }
}

/* 800FD61C-800FD6DC       .text setMtx__11daNpc_Fa1_cFv */
void daNpc_Fa1_c::setMtx() {
    J3DModel* pJVar5 = mpDoExt_McaMorf->getModel();
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_YrotM(mDoMtx_stack_c::get(), shape_angle.y);
    pJVar5->setBaseTRMtx(mDoMtx_stack_c::get());
    mpDoExt_McaMorf->calc();
    MtxP pMVar4 = mpDoExt_McaMorf->getModel()->getAnmMtx(mMcaMorfCallback1.m06);
    attention_info.position.set(pMVar4[0][3], pMVar4[1][3], pMVar4[2][3]);
    eyePos = attention_info.position;
}

/* 800FD6DC-800FD6FC       .text daNpc_Fa1_Create__FP10fopAc_ac_c */
cPhs_State daNpc_Fa1_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Fa1_c*)i_this)->_create();
}

/* 800FD6FC-800FD71C       .text daNpc_Fa1_Delete__FP11daNpc_Fa1_c */
BOOL daNpc_Fa1_Delete(daNpc_Fa1_c* i_this) {
    return ((daNpc_Fa1_c*)i_this)->_delete();
}

/* 800FD71C-800FD73C       .text daNpc_Fa1_Execute__FP11daNpc_Fa1_c */
BOOL daNpc_Fa1_Execute(daNpc_Fa1_c* i_this) {
    return ((daNpc_Fa1_c*)i_this)->_execute();
}

/* 800FD73C-800FD75C       .text daNpc_Fa1_Draw__FP11daNpc_Fa1_c */
BOOL daNpc_Fa1_Draw(daNpc_Fa1_c* i_this) {
    return ((daNpc_Fa1_c*)i_this)->_draw();
}

/* 800FD75C-800FD764       .text daNpc_Fa1_IsDelete__FP11daNpc_Fa1_c */
BOOL daNpc_Fa1_IsDelete(daNpc_Fa1_c*) {
    return TRUE;
}

/* 800FD764-800FD7D8       .text __dt__15daNpc_Fa1_HIO_cFv */
//daNpc_Fa1_HIO_c::~daNpc_Fa1_HIO_c() {
//    /* Nonmatching */
//}

static actor_method_class l_daNpc_Fa1_Method = {
    (process_method_func)daNpc_Fa1_Create,
    (process_method_func)daNpc_Fa1_Delete,
    (process_method_func)daNpc_Fa1_Execute,
    (process_method_func)daNpc_Fa1_IsDelete,
    (process_method_func)daNpc_Fa1_Draw,
};

actor_process_profile_definition g_profile_NPC_FA1 = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_FA1,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Fa1_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_FA1,
    /* Actor SubMtd */ &l_daNpc_Fa1_Method,
    /* Status       */ fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
