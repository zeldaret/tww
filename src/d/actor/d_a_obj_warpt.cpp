/**
 * d_a_obj_warpt.cpp
 * Object - Warp pot
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_warpt.h"
#include "d/actor/d_a_player.h"
#include "d/res/res_ltubw.h"
#include "d/d_bg_w.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_a_obj.h"
#include "d/d_bg_s_movebg_actor.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_hostIO.h"

class daObj_Warpt_HIO_c : public mDoHIO_entry_c {
public:
    daObj_Warpt_HIO_c();
    virtual ~daObj_Warpt_HIO_c() {}
    void genMessage(JORMContext*) {}

    /* 0x04 */ u8 m04;
    /* 0x05 */ u8 m05;
    /* 0x06 */ u8 m06;
    /* 0x08 */ f32 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
    /* 0x14 */ GXColor m14;
    /* 0x18 */ GXColor m18;
}; // size = 0x1C

static daObj_Warpt_HIO_c l_HIO;

const char daObj_Warpt_c::m_arc_name[] = "ltubw";
const u16 daObj_Warpt_c::m_event_reg[] = {0xA207, 0xA107, 0xA007, 0x9F07, 0xA307, 0xA407};
const GXColor daObj_Warpt_c::m_def_smoke_prm_color[] = {
    {0x9F, 0x7F, 0x9C, 0x80},
    {0x9F, 0x7F, 0x9C, 0x80},
    {0x99, 0xEC, 0x5F, 0x80},
    {0x5C, 0x85, 0xFF, 0x80},
    {0xFF, 0xFF, 0x57, 0x80},
};
const GXColor daObj_Warpt_c::m_def_smoke_env_color[] = {
    {0x2F, 0x87, 0xDE, 0x80},
    {0x2F, 0x87, 0xDE, 0x80},
    {0x3D, 0x50, 0xD1, 0x80},
    {0xFF, 0xF0, 0xAF, 0x80},
    {0xFF, 0x00, 0x4B, 0x80},
};

const dCcD_SrcCyl daObj_Warpt_c::m_cyl_body_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_GrpAll_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsPlayer_e | cCcD_CoSPrm_VsOther_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_Shield_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 85.0f,
        /* Height */ 150.0f,
    }},
};

const dCcD_SrcCyl daObj_Warpt_c::m_cyl_huta_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
#if VERSION <= VERSION_JPN
        /* SrcObjTg  Type    */ AT_TYPE_ALL,
#else
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
#endif
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ 0,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ dCcG_TgSPrm_NoHitMark_e,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 70.0f,
        /* Height */ 20.0f,
    }},
};

/* 000000EC-00000190       .text __ct__17daObj_Warpt_HIO_cFv */
daObj_Warpt_HIO_c::daObj_Warpt_HIO_c() {
    m04 = 0;
    m05 = 0;
    m06 = 0;
    m08 = 150.0f;
    m0C = 30.0f;
    m10 = -2.5f;
    m14 = (GXColor){0, 0, 0, 128};
    m18 = (GXColor){0, 0, 0, 128};
}

/* 000001D8-000001F8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* a_this) {
    return ((daObj_Warpt_c*)a_this)->_createHeap();
}

/* 000001F8-00000270       .text _createHeap__13daObj_Warpt_cFv */
BOOL daObj_Warpt_c::_createHeap() {
    if (isRealHuta()) {
        if (!createHutaHeap()) {
            return false;
        }
    } else {
        mpLidBgW = NULL;
        mpLidModel1 = NULL;
        mpLidModel2 = NULL;
    }

    if (!createBodyHeap()) {
        return false;
    }
    return true;
}

/* 00000270-00000488       .text createHutaHeap__13daObj_Warpt_cFv */
bool daObj_Warpt_c::createHutaHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, LTUBW_BDL_ITUHU);
    JUT_ASSERT(264, modelData);

    mpLidModel1 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpLidModel1 == NULL) {
        return false;
    }

    mpLidBgW = new dBgW();
    if (mpLidBgW == NULL) {
        return false;
    }

    if (mpLidBgW->Set((cBgD_t*)dComIfG_getObjectRes(m_arc_name, LTUBW_DZB_ITUHT), cBgW::MOVE_BG_e, &m344) == TRUE) {
        return false;
    }

    J3DModelData* modelData2 = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, LTUBW_BDL_YWPFM00);
    modelData = modelData2;
    if (modelData == NULL) {
        return false;
    }

    mpLidModel2 = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpLidModel2 == NULL) {
        return false;
    }

    J3DAnmTevRegKey* brk = (J3DAnmTevRegKey*)dComIfG_getObjectRes(m_arc_name, LTUBW_BRK_YWPFM00);
    JUT_ASSERT(291, brk);

    if (!mLidBrk.init(modelData, brk, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false, FALSE)) {
        return false;
    }
    return true;
}

/* 00000488-00000620       .text createBodyHeap__13daObj_Warpt_cFv */
bool daObj_Warpt_c::createBodyHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, LTUBW_BDL_ITUBW);
    JUT_ASSERT(305, modelData);

    mpBodyModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpBodyModel == NULL) {
        return false;
    }

    mpBodyBgW2 = new dBgW();
    if (mpBodyBgW2 == NULL) {
        return false;
    }

    if (mpBodyBgW2->Set((cBgD_t*)dComIfG_getObjectRes(m_arc_name, LTUBW_DZB_ITUBW), cBgW::MOVE_BG_e, &m310) == TRUE) {
        return false;
    }

    mpBodyBgW1 = new dBgW();
    if (mpBodyBgW1 == NULL) {
        return false;
    }

    if (mpBodyBgW1->Set((cBgD_t*)dComIfG_getObjectRes(m_arc_name, LTUBW_DZB_ITUSO), cBgW::MOVE_BG_e, &m2DC) == TRUE) {
        return false;
    }
    return true;
}

/* 00000620-00000648       .text ride_CB__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_CB(dBgW*, fopAc_ac_c* a_this, fopAc_ac_c* arg2) {
    ((daObj_Warpt_c*)a_this)->_ride(arg2);
}

/* 00000648-00000750       .text _ride__13daObj_Warpt_cFP10fopAc_ac_c */
void daObj_Warpt_c::_ride(fopAc_ac_c* arg1) {
    if (fpcM_GetName(arg1) == PROC_PLAYER) {
        daPy_py_c* player = (daPy_py_c*)arg1;

        fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
        dLib_checkPlayerInCircle(m830, 1.0f, 20.0f);

        if (l_HIO.m06 == 0) {
#if VERSION > VERSION_DEMO
            if (!player->checkPlayerFly())
#endif
            {
                if (m290 != 3) {
                    if (dLib_checkPlayerInCircle(m830, l_HIO.m0C, 20.0f)) {
                        modeProc(PROC_INIT_e, 3);
                    }
                }
            }
        }
    }
}

/* 00000750-00000758       .text isHuta__13daObj_Warpt_cFv */
bool daObj_Warpt_c::isHuta() {
    return m2C6;
}

/* 00000758-00000784       .text isSp__13daObj_Warpt_cFv */
bool daObj_Warpt_c::isSp() {
    return m2B4 == 2 || m2B4 == 3 || m2B4 == 4;
}

/* 00000784-0000080C       .text isOtherHuta__13daObj_Warpt_cFv */
bool daObj_Warpt_c::isOtherHuta() {
    return isSp() && m2AC != 0xff && !dComIfGs_isSwitch(m2AC, dComIfGp_roomControl_getStayNo());
}

/* 0000080C-00000864       .text isRealHuta__13daObj_Warpt_cFv */
bool daObj_Warpt_c::isRealHuta() {
    return isHuta() && !isOtherHuta();
}

/* 00000864-000008E8       .text warp__13daObj_Warpt_cFi */
void daObj_Warpt_c::warp(int sclsnum) {
    mDoAud_seStart(JA_SE_OBJ_OTOSHIANA_OPEN);
    if (sclsnum != 0xff) {
        dLib_setNextStageBySclsNum(sclsnum, current.roomNo);
    }
}

/* 000008E8-00000968       .text onWarpBit__13daObj_Warpt_cFUc */
void daObj_Warpt_c::onWarpBit(u8 bit) {
    u8 tmp = dComIfGs_getEventReg(m_event_reg[m2B8]);
    cLib_onBit<u8>(tmp, bit);
    dComIfGs_setEventReg(m_event_reg[m2B8], tmp);
}

/* 00000968-000009D0       .text isWarpBit__13daObj_Warpt_cFUc */
bool daObj_Warpt_c::isWarpBit(u8 bit) {
    u8 tmp = (u8)dComIfGs_getEventReg(m_event_reg[m2B8]);
    return cLib_checkBit(tmp, bit);
}

/* 000009D0-00000BB8       .text setMtx__13daObj_Warpt_cFv */
void daObj_Warpt_c::setMtx() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);
    mpBodyModel->setBaseTRMtx(mDoMtx_stack_c::get());

    cMtx_copy(mDoMtx_stack_c::get(), m310);
    cMtx_copy(mDoMtx_stack_c::get(), m2DC);

    mpBodyBgW1->Move();
    m830 = current.pos;
    m830.y += l_HIO.m08;

#if VERSION == VERSION_DEMO
    if (m840 == 1) {
        dComIfG_Bgsp()->Regist(mpBodyBgW2, this);
        mpBodyBgW2->Move();
    }
#else
    if (m840 == 1) {
        if (mpBodyBgW2 != NULL && !mpBodyBgW2->ChkUsed()) {
            dComIfG_Bgsp()->Regist(mpBodyBgW2, this);
        }
    }

    if (mpBodyBgW2 != NULL && mpBodyBgW2->ChkUsed()) {
        mpBodyBgW2->Move();
    }
#endif

    if (mpLidBgW != NULL && mpLidModel1 != NULL) {
        mDoMtx_stack_c::transS(m830.x, m830.y, m830.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::scaleM(scale.x, scale.y, scale.z);

        mpLidModel1->setBaseTRMtx(mDoMtx_stack_c::get());
        mpLidModel2->setBaseTRMtx(mDoMtx_stack_c::get());

        cMtx_copy(mDoMtx_stack_c::get(), m344);
        mpLidBgW->Move();
    }
}

/* 00000BB8-00000C3C       .text initCollision__13daObj_Warpt_cFv */
void daObj_Warpt_c::initCollision() {
    mStts.Init(0xff, 0xff, this);
    mCyl1.Set(m_cyl_body_src);
    mCyl1.SetStts(&mStts);
    if (mpLidBgW != NULL && mpLidModel1 != NULL) {
        mCyl2.Set(m_cyl_huta_src);
        mCyl2.SetStts(&mStts);
    }
}

/* 00000C3C-00000CCC       .text setCollision__13daObj_Warpt_cFv */
void daObj_Warpt_c::setCollision() {
    mCyl1.SetC(current.pos);
    dComIfG_Ccsp()->Set(&mCyl1);
    if (mpLidBgW != NULL && mpLidModel1 != NULL) {
        mCyl2.OffCoSetBit();
        mCyl2.SetC(m830);
        dComIfG_Ccsp()->Set(&mCyl2);
    }
}

/* 00000CCC-00000E90       .text breakHuta__13daObj_Warpt_cFi */
void daObj_Warpt_c::breakHuta(int arg1) {
    if (mpLidBgW == NULL || mpLidModel1 == NULL) {
        return;
    }

    switch (arg1) {
    case 0:
        dComIfGp_particle_set(dPa_name::ID_SCENE_8165, &m830);
        dComIfGp_particle_set(dPa_name::ID_SCENE_8166, &m830);
        break;

    case 1:
        fopAcM_seStart(this, JA_SE_OBJ_COL_BRK_WRAILING, 0);
        dComIfGp_particle_set(dPa_name::ID_COMMON_03E5, &m830, NULL, NULL, 0xff, NULL, -1, &tevStr.mColorK0, &tevStr.mColorK0);
#if VERSION > VERSION_DEMO
        if (mpLidBgW != NULL && mpLidBgW->ChkUsed())
#endif
        {
            dComIfG_Bgsp()->Release(mpLidBgW);
        }
        break;
    }
}

/* 00000E90-00000F40       .text openHuta__13daObj_Warpt_cFv */
void daObj_Warpt_c::openHuta() {
    if (isSp()) {
        if (m2BC == 0xff) {
            mDoAud_seStart(JA_SE_READ_RIDDLE_1);
        }
        onWarpBit(m2C4);
    } else {
        dComIfGs_onSwitch(m2AC, dComIfGp_roomControl_getStayNo());
    }
    m2C6 = false;
}

/* 00000F40-000010E0       .text checkHitSE__13daObj_Warpt_cFv */
void daObj_Warpt_c::checkHitSE() {
    cCcD_Obj* pcVar1 = mCyl1.GetTgHitObj();
    mStts.Move();
    if (pcVar1 == NULL) {
        return;
    }

    switch (pcVar1->GetAtType()) {
    case AT_TYPE_FIRE_ARROW:
    case AT_TYPE_UNK800:
    case AT_TYPE_UNK8:
    case AT_TYPE_SWORD:
    case AT_TYPE_MACHETE:
    case AT_TYPE_HOOKSHOT:
    case AT_TYPE_NORMAL_ARROW:
    case AT_TYPE_SKULL_HAMMER:
    case AT_TYPE_DARKNUT_SWORD:
    case AT_TYPE_LIGHT_ARROW:
    case AT_TYPE_ICE_ARROW:
    case AT_TYPE_STALFOS_MACE:
    case AT_TYPE_MOBLIN_SPEAR:
    case AT_TYPE_GRAPPLING_HOOK:
    case AT_TYPE_PGANON_SWORD:
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
        s32 cutType = player->getCutType();
        if (cutType != 8 && cutType != 9) {
            fopAcM_seStart(this, JA_SE_OBJ_COL_SWM_NSTPOT, 0);
            daObj::HitEff_hibana(this, &mCyl1);
        }
        break;
    }
}

/* 000010E0-00001178       .text modeOpenInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeOpenInit() {
    if (m844.getEmitter() == NULL) {
        dComIfGp_particle_set(dPa_name::ID_SCENE_8161, &current.pos, NULL, NULL, 0xff, &m844, -1, &m86C, &m870);
    }
    m858.remove();
}

/* 00001178-000011E8       .text modeOpen__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeOpen() {
    fopAcM_seStart(this, JA_SE_OBJ_OTOSHIANA_SUS, 0);
}

/* 000011E8-00001258       .text modeCloseInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeCloseInit() {
    dComIfGp_particle_set(dPa_name::ID_SCENE_8162, &current.pos, NULL, NULL, 0xff, &m858, -1, &m86C, &m870);
}

/* 00001258-00001388       .text modeClose__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeClose() {
    if (mpLidBgW != NULL && mpLidModel1 != NULL) {
        cCcD_Obj* pcVar1 = mCyl2.GetTgHitObj();
        if (pcVar1 != NULL) {
            if (pcVar1->ChkAtType(AT_TYPE_BOMB)) {
                breakHuta(1);
                openHuta();
                modeProc(PROC_INIT_e, 0);
            } else if (pcVar1->ChkAtType(AT_TYPE_UNK20000) || pcVar1->ChkAtType(AT_TYPE_FIRE_ARROW) || pcVar1->ChkAtType(AT_TYPE_FIRE)) {
                breakHuta(0);
                modeProc(PROC_INIT_e, 2);
            } else if (pcVar1->ChkAtType(AT_TYPE_SKULL_HAMMER) || pcVar1->ChkAtType(AT_TYPE_STALFOS_MACE)) {
                breakHuta(1);
                openHuta();
                modeProc(PROC_INIT_e, 0);
            }
        }
    } else if (dComIfGs_isSwitch(m2AC, dComIfGp_roomControl_getStayNo())) {
        openHuta();
        modeProc(PROC_INIT_e, 0);
    }
}

/* 00001388-00001400       .text modeBreakFireInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeBreakFireInit() {
    fopAcM_seStart(this, JA_SE_OBJ_WARP_POT_CV_BURN, 0);
    m83C = 60;
}

/* 00001400-0000149C       .text modeBreakFire__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeBreakFire() {
    mLidBrk.play();
    if (!cLib_calcTimer(&m83C)) {
#if VERSION > VERSION_DEMO
        if (mpLidBgW != NULL && mpLidBgW->ChkUsed())
#endif
        {
            dComIfG_Bgsp()->Release(mpLidBgW);
        }
        openHuta();
        modeProc(PROC_INIT_e, 0);
    }
}

/* 0000149C-000014A0       .text modeEventWarpInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeEventWarpInit() {
}

/* 000014A0-00001634       .text modeEventWarp__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeEventWarp() {
    daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);

    if (eventInfo.checkCommandDemoAccrpt()) {
#if VERSION > VERSION_DEMO
        if (mpBodyBgW2 != NULL && mpBodyBgW2->ChkUsed())
#endif
        {
            dComIfG_Bgsp()->Release(mpBodyBgW2);
        }
        player->onNoResetFlg0(daPy_py_c::daPyFlg0_NO_FALL_VOICE);
        int staffIdx = dComIfGp_evmng_getMyStaffId("Warpt");
        char* cutName = dComIfGp_getPEvtManager()->getMyNowCutName(staffIdx);

        bool cVar3 = true;
        if (strcmp(cutName, "WARP") == 0) {
            if (isSp()) {
                cVar3 = spWarp();
            } else {
                cVar3 = normalWarp();
            }
            dComIfGp_evmng_cutEnd(staffIdx);
        }

        if (dComIfGp_evmng_endCheck("DEFAULT_WARP") && !cVar3) {
            m840 = 30;
            dComIfGp_event_reset();
            player->onNoResetFlg1(daPy_py_c::daPyFlg1_FORCE_VOMIT_JUMP_SHORT);
            modeProc(PROC_INIT_e, 0);
        }
    } else {
#if VERSION == VERSION_DEMO
        fopAcM_orderOtherEvent(this, "DEFAULT_WARP");
#else
        fopAcM_orderOtherEvent2(this, "DEFAULT_WARP", dEvtFlag_TALK_e, -1);
#endif
    }
}

/* 00001634-000016A4       .text normalWarp__13daObj_Warpt_cFv */
bool daObj_Warpt_c::normalWarp() {
    bool ret = true;
    if (dComIfGs_isSwitch(m2B0, dComIfGp_roomControl_getStayNo())) {
        warp(m29C);
    } else {
        ret = false;
    }
    return ret;
}

/* 000016A4-000017D8       .text spWarp__13daObj_Warpt_cFv */
bool daObj_Warpt_c::spWarp() {
    bool uVar3 = 1;
    if (m2B4 == 2) {
        if (isWarpBit(2)) {
            warp(m2A4);
        } else if (isWarpBit(4)) {
            warp(m2A8);
        } else {
            uVar3 = 0;
        }
    } else if (m2B4 == 3) {
        if (isWarpBit(4)) {
            warp(m2A8);
        } else if (isWarpBit(1)) {
            warp(m2A0);
        } else {
            uVar3 = 0;
        }
    } else if (m2B4 == 4) {
        if (isWarpBit(1)) {
            warp(m2A0);
        } else if (isWarpBit(2)) {
            warp(m2A4);
        } else {
            uVar3 = 0;
        }
    }
    return uVar3;
}

/* 000017D8-000017DC       .text modeEventOpenInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeEventOpenInit() {
}

/* 000017DC-00001858       .text modeEventOpen__13daObj_Warpt_cFv */
void daObj_Warpt_c::modeEventOpen() {
    if (eventInfo.checkCommandDemoAccrpt() && dComIfGp_evmng_endCheck("WARPT_OPEN")) {
        dComIfGp_event_reset();
        modeProc(PROC_INIT_e, 0);
    }
}

/* 00001858-000019D8       .text modeProc__13daObj_Warpt_cFQ213daObj_Warpt_c6Proc_ei */
void daObj_Warpt_c::modeProc(daObj_Warpt_c::Proc_e proc, int index) {
    typedef void (daObj_Warpt_c::*ModeProcFunc)();
    struct mode_entry_t {
        /* 0x00 */ ModeProcFunc init;
        /* 0x04 */ ModeProcFunc run;
        /* 0x08 */ char* name;
    }; // size = 0x8

    static mode_entry_t mode_tbl[] = {
        {
            &daObj_Warpt_c::modeOpenInit,
            &daObj_Warpt_c::modeOpen,
            "OEPN",
        },
        {
            &daObj_Warpt_c::modeCloseInit,
            &daObj_Warpt_c::modeClose,
            "CLOSE",
        },
        {
            &daObj_Warpt_c::modeBreakFireInit,
            &daObj_Warpt_c::modeBreakFire,
            "BREAK_FIRE",
        },
        {
            &daObj_Warpt_c::modeEventWarpInit,
            &daObj_Warpt_c::modeEventWarp,
            "EVENT_WARP",
        },
        {
            &daObj_Warpt_c::modeEventOpenInit,
            &daObj_Warpt_c::modeEventOpen,
            "EVENT_OPEN",
        },
    };

    if (proc == PROC_INIT_e) {
        m290 = index;
        (this->*mode_tbl[m290].init)();
    } else if (proc == PROC_RUN_e) {
        (this->*mode_tbl[m290].run)();
    }
}

/* 000019D8-00001BCC       .text _execute__13daObj_Warpt_cFv */
bool daObj_Warpt_c::_execute() {
    if (m844.getEmitter() != NULL) {
        if (l_HIO.m14.r != 0 || l_HIO.m14.g != 0 || l_HIO.m14.b != 0) {
            m844.getEmitter()->setGlobalPrmColor(l_HIO.m14.r, l_HIO.m14.g, l_HIO.m14.b);
        }

        if (l_HIO.m18.r != 0 || l_HIO.m18.g != 0 || l_HIO.m18.b != 0) {
            m844.getEmitter()->setGlobalEnvColor(l_HIO.m18.r, l_HIO.m18.g, l_HIO.m18.b);
        }
    }

    if (m858.getEmitter() != NULL) {
        if (l_HIO.m14.r != 0 || l_HIO.m14.g != 0 || l_HIO.m14.b != 0) {
            m858.getEmitter()->setGlobalPrmColor(l_HIO.m14.r, l_HIO.m14.g, l_HIO.m14.b);
        }

        if (l_HIO.m18.r != 0 || l_HIO.m18.g != 0 || l_HIO.m18.b != 0) {
            m858.getEmitter()->setGlobalEnvColor(l_HIO.m18.r, l_HIO.m18.g, l_HIO.m18.b);
        }
    }

    if (l_HIO.m04 != 0) {
        l_HIO.m04 = 0;
        breakHuta(0);
        modeProc(PROC_INIT_e, 2);
    }
    modeProc(PROC_RUN_e, 5);
    fopAcM_posMoveF(this, mStts.GetCCMoveP());
    mAcch.CrrPos(*dComIfG_Bgsp());
    setMtx();
    setCollision();
    checkHitSE();
    cLib_calcTimer(&m840);
    return true;
}

/* 00001BCC-00001D7C       .text _draw__13daObj_Warpt_cFv */
bool daObj_Warpt_c::_draw() {
    dComIfGd_setListBG();
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpBodyModel, &tevStr);
    mDoExt_modelUpdateDL(mpBodyModel);
    dComIfGd_setList();

    if (isHuta()) {
        if (m290 == 2 && mpLidModel2 != NULL) {
            g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &m830, &tevStr);
            g_env_light.setLightTevColorType(mpLidModel2, &tevStr);
            mLidBrk.entry(mpLidModel2->getModelData());
            mDoExt_modelUpdateDL(mpLidModel2);
        } else if (mpLidBgW != NULL && mpLidModel1 != NULL) {
            dComIfGd_setListBG();
            g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &m830, &tevStr);
            g_env_light.setLightTevColorType(mpLidModel1, &tevStr);
            mDoExt_modelUpdateDL(mpLidModel1);
            dComIfGd_setList();
        }
    }
    dComIfGd_setSimpleShadow2(&current.pos, mAcch.GetGroundH(), 80.0f, mAcch.m_gnd);
    return true;
}

/* 00001D7C-00001F30       .text getArg__13daObj_Warpt_cFv */
void daObj_Warpt_c::getArg() {
    u32 uVar4 = fopAcM_GetParam(this);
    u32 uVar6 = home.angle.x;
    u32 uVar5 = home.angle.z;
    m2B4 = uVar4 & 0xF;

    if (!isSp()) {
        m298 = (uVar4 >> 4) & 0xff;
        m29C = (uVar4 >> 12) & 0xff;
        m2AC = (uVar6 >> 0) & 0xff;
        m2B0 = (uVar6 >> 8) & 0xff;

        if (m2B4 == 1) {
            dComIfGs_onSwitch(m2AC, dComIfGp_roomControl_getStayNo());
        }

        if (dComIfGs_isSwitch(m2AC, dComIfGp_roomControl_getStayNo())) {
            m2C6 = false;
        } else {
            m2C6 = true;
        }
    } else {
        m2B8 = (uVar4 >> 4) & 0xf;
        m2A0 = (uVar4 >> 8) & 0xff;
        m2A4 = (uVar4 >> 16) & 0xff;
        m2A8 = (uVar4 >> 24) & 0xff;

        switch (m2B4) {
        case 2:
            m2C4 = 1;
            m2C5 = 0;
            break;

        case 3:
            m2C4 = 2;
            m2C5 = 1;
            break;

        case 4:
            m2C4 = 4;
            m2C5 = 2;
            break;
        }

        m2AC = (uVar6 >> 0) & 0xff;
        m2B0 = (uVar6 >> 8) & 0xff;
        m2BC = (uVar5 >> 0) & 0xff;
        m2C0 = (uVar5 >> 8) & 0xff;

        if (m2C0 != 0xff) {
            onWarpBit(m2C4);
        }

        if (isWarpBit(m2C4)) {
            m2C6 = false;
        } else {
            m2C6 = true;
        }
    }
}

/* 00001F30-0000215C       .text createInit__13daObj_Warpt_cFv */
void daObj_Warpt_c::createInit() {
    m86C = m_def_smoke_prm_color[m2B4];
    m870 = m_def_smoke_env_color[m2B4];

    fopAcM_SetMtx(this, mpBodyModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, -80.0f, -0.0f, -80.0f, 80.0f, 160.0f, 80.0f);

    if (mpLidBgW != NULL) {
        mpLidBgW->SetCrrFunc(dBgS_MoveBGProc_Typical);
        dComIfG_Bgsp()->Regist(mpLidBgW, this);
    }

    mpBodyBgW1->SetCrrFunc(dBgS_MoveBGProc_Typical);
    dComIfG_Bgsp()->Regist(mpBodyBgW1, this);

    if (isHuta()) {
        modeProc(PROC_INIT_e, 1);
    } else {
        modeProc(PROC_INIT_e, 0);
    }

    mpBodyBgW2->SetRideCallback(ride_CB);
    initCollision();
    setCollision();

    mAcchCir.SetWall(30.0f, 50.0f);
    mAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
    mAcch.SetWallNone();
    mAcch.SetWaterNone();
    mAcch.SetRoofNone();

    fopAcM_SetGravity(this, -6.5f);
    fopAcM_posMoveF(this, NULL);

    if (dLib_checkPlayerInCircle(current.pos, 50.0f, 100.0f)) {
        m840 = 30;
    } else {
        m840 = 5;
    }
    setMtx();
}

/* 0000215C-00002378       .text _create__13daObj_Warpt_cFv */
cPhs_State daObj_Warpt_c::_create() {
    fopAcM_SetupActor(this, daObj_Warpt_c);
    cPhs_State PVar1 = dComIfG_resLoad(&mPhase, m_arc_name);
    if (PVar1 == cPhs_COMPLEATE_e) {
        getArg();
        u32 maxHeapSize;
        if (isRealHuta()) {
            maxHeapSize = 0x1f00;
        } else {
            maxHeapSize = 0xe20;
        }

        if (!fopAcM_entrySolidHeap(this, createHeap_CB, maxHeapSize)) {
            return cPhs_ERROR_e;
        }
        createInit();
    }
    return PVar1;
}

/* 00002728-00002858       .text _delete__13daObj_Warpt_cFv */
bool daObj_Warpt_c::_delete() {
    dComIfG_resDelete(&mPhase, m_arc_name);
    if (mpLidBgW != NULL && mpLidBgW->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpLidBgW);
    }

    if (mpBodyBgW2 != NULL && mpBodyBgW2->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBodyBgW2);
    }

    if (mpBodyBgW1 != NULL && mpBodyBgW1->ChkUsed()) {
        dComIfG_Bgsp()->Release(mpBodyBgW1);
    }

    m844.remove();
    m858.remove();
    return true;
}

/* 00002858-00002878       .text daObj_WarptCreate__FPv */
static cPhs_State daObj_WarptCreate(void* i_this) {
    return ((daObj_Warpt_c*)i_this)->_create();
}

/* 00002878-0000289C       .text daObj_WarptDelete__FPv */
static BOOL daObj_WarptDelete(void* i_this) {
    return ((daObj_Warpt_c*)i_this)->_delete();
}

/* 0000289C-000028C0       .text daObj_WarptExecute__FPv */
static BOOL daObj_WarptExecute(void* i_this) {
    return ((daObj_Warpt_c*)i_this)->_execute();
}

/* 000028C0-000028E4       .text daObj_WarptDraw__FPv */
static BOOL daObj_WarptDraw(void* i_this) {
    return ((daObj_Warpt_c*)i_this)->_draw();
}

/* 000028E4-000028EC       .text daObj_WarptIsDelete__FPv */
static BOOL daObj_WarptIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_WarptMethodTable = {
    (process_method_func)daObj_WarptCreate,
    (process_method_func)daObj_WarptDelete,
    (process_method_func)daObj_WarptExecute,
    (process_method_func)daObj_WarptIsDelete,
    (process_method_func)daObj_WarptDraw,
};

actor_process_profile_definition g_profile_OBJ_WARPT = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_WARPT,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Warpt_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_WARPT,
    /* Actor SubMtd */ &daObj_WarptMethodTable,
#if VERSION == VERSION_DEMO
    /* Status       */ 0x17 | fopAcStts_SHOWMAP_e | fopAcStts_NOCULLEXEC_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
#else
    /* Status       */ 0x17 | fopAcStts_SHOWMAP_e | fopAcStts_CULL_e | fopAcStts_UNK40000_e,
#endif
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
