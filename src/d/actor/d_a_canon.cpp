/**
 * d_a_canon.cpp
 * Cannon Minigame
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_canon.h"
#include "d/actor/d_a_npc_kg2.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_sea.h"
#include "d/res/res_bomber.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_2dnumber.h"
#include "d/d_kankyo.h"
#include "d/d_kankyo_wether.h"
#include "d/d_priority.h"
#include "d/d_s_play.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_kankyo_mng.h"
#include "f_op/f_op_camera.h"
#include "f_op/f_op_camera_mng.h"
#include "m_Do/m_Do_controller_pad.h"

LIGHT_INFLUENCE plight;
WIND_INFLUENCE pwind;

const char daCanon_c::M_arcname[] = "Bomber";
static const s16 angle_x_tbl[] = {0xF000, 0xF24A, 0xF493, 0xF6DC, 0xF925, 0xFB6E, 0xFDB7, 0x0000};
static const s16 angle_y_tbl[] = {0xEE00, 0xF324, 0xF895, 0xFD6C, 0x294, 0x76B, 0xCDC, 0x1200};

static dCcD_SrcCyl canon_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ 0,
        /* SrcObjTg  SPrm    */ 0,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
        /* SrcGObjAt Se      */ 0,
        /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
        /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
        /* SrcGObjAt Mtrl    */ 0,
        /* SrcGObjAt SPrm    */ 0,
        /* SrcGObjTg Se      */ 0,
        /* SrcGObjTg HitMark */ 0,
        /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
        /* SrcGObjTg Mtrl    */ 0,
        /* SrcGObjTg SPrm    */ 0,
        /* SrcGObjCo SPrm    */ 0,
    },
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 75.0f,
        /* Height */ 50.0f,
    }},
};

static dCcD_SrcCyl canon_cyl2_src = {
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
        /* Radius */ 300.0f,
        /* Height */ 500.0f,
    }},
};

/* 000000EC-000002C8       .text set_mtx__9daCanon_cFv */
void daCanon_c::set_mtx() {
    cXyz sp14(REG10_F(26) + 0.65f, REG10_F(26) + 0.65f, REG10_F(26) + 0.65f);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + sp14.x * 100.0f, current.pos.z);
    mDoMtx_stack_c::YrotM(shape_angle.y - -0x8000);

    if (checkProcess(&daCanon_c::fire_proc)) {
        mDoMtx_stack_c::YrotM(m660 * cM_ssin(m65E));
        mDoMtx_stack_c::XrotM(m660 * cM_scos(m65E));
        mDoMtx_stack_c::transM(0.0f, m638, 0.0f);
    }

    mpModel1->setBaseScale(sp14);
    mpModel1->setBaseTRMtx(mDoMtx_stack_c::get());
    MTXCopy(mDoMtx_stack_c::get(), m5C4);
}

/* 000002C8-00000340       .text bul_set_mtx__9daCanon_cFP4cXyz */
void daCanon_c::bul_set_mtx(cXyz* arg1) {
    cXyz scale(1.0f, 1.0f, 1.0f);
    mpModel2->setBaseScale(scale);
    mDoMtx_stack_c::transS(arg1->x, arg1->y, arg1->z);
    mpModel2->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000340-00000448       .text getGridPos__9daCanon_cFii */
cXyz daCanon_c::getGridPos(int arg1, int arg2) {
    cXyz sp08 = current.pos;
    f32 fVar2 = arg2 * 1500.0f + 10500.0f + REG10_F(11);
    sp08.x += fVar2 * cM_ssin(home.angle.y + angle_y_tbl[arg1]);
    sp08.z += fVar2 * cM_scos(home.angle.y + angle_y_tbl[arg1]);
    sp08.y = daSea_calcWave(sp08.x, sp08.z);
    return sp08;
}

/* 00000448-00000554       .text getBulEndPos__9daCanon_cFss */
cXyz daCanon_c::getBulEndPos(short arg1, short arg2) {
    cXyz sp08 = current.pos;
    f32 fVar2 = (((home.angle.x + 0x1000) - arg2) / 4096.0f);
    f32 fVar3 = fVar2 * 1500.0f * 7.0f + 10500.0f + REG10_F(10);
    sp08.x += fVar3 * cM_ssin(arg1);
    sp08.z += fVar3 * cM_scos(arg1);
    sp08.y = daSea_calcWave(sp08.x, sp08.z);
    return sp08;
}

/* 00000554-000005A0       .text createCheck__9daCanon_cFiii */
BOOL daCanon_c::createCheck(int arg1, int arg2, int arg3) {
    s32 idx = arg3;
    while (idx != 0) {
        if (arg1 == m5F4[--idx * 2]) {
            return FALSE;
        }
    }

    m5F4[arg3 * 2] = arg1;
    m5F4[arg3 * 2 + 1] = arg2;
    return TRUE;
}

/* 000005A0-00000628       .text daCanon_nodeCallBack__FP7J3DNodei */
static BOOL daCanon_nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == 0) {
        J3DModel* pJVar2 = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        s32 uVar1 = joint->getJntNo();
        daCanon_c* pvVar3 = (daCanon_c*)pJVar2->getUserArea();
        mDoMtx_stack_c::copy(pJVar2->getAnmMtx(uVar1));
        mDoMtx_stack_c::YrotM(pvVar3->shape_angle.x);
        pJVar2->setAnmMtx(uVar1, mDoMtx_stack_c::get());
    }
    return TRUE;
}

/* 00000628-0000063C       .text target_createCB__FPv */
BOOL target_createCB(void* v_this) {
    fopAcM_OffStatus((daCanon_c*)v_this, fopAcStts_CULL_e | fopAcStts_NOCULLEXEC_e);
    return TRUE;
}

/* 0000063C-0000074C       .text createTargetObj__9daCanon_cFv */
void daCanon_c::createTargetObj() {
    int i = 5;
    while (i != 0) {
        int iVar1 = cM_rndF(8.0f);
        int fVar5 = cM_rndF(8.0f);
        if (createCheck(iVar1, fVar5, 5 - i)) {
            cXyz sp1C = getGridPos(iVar1, fVar5);
            m600[5 - i] = fopAcM_createChild(tk_Obj_Barrel2_e, fopAcM_GetID(this), 0x37f003f, &sp1C, -1, NULL, NULL, -1, target_createCB);
            i--;
        }
    }
}

/* 0000074C-000007F4       .text daCanon_BreakTarget__FPvPv */
void* daCanon_BreakTarget(void* arg1, void* arg2) {
    if (fopAcM_IsActor(arg1) && fopAcM_GetName(arg1) == tk_Obj_Barrel2_e) {
        fopAc_ac_c* ac1 = (fopAc_ac_c*)arg1;
        if (fopAcM_GetID(arg2) == fopAcM_GetLinkId(ac1)) {
            fopAcM_create(PROC_BOMB, daBomb_c::prm_make(daBomb_c::STATE_0, false, false), &ac1->current.pos, -1, NULL, NULL, -1, dEv_extra_createCB);
        }
    }
    return NULL;
}

/* 000007F4-00000820       .text breakAllObj__9daCanon_cFv */
void daCanon_c::breakAllObj() {
    fopAcM_Search(daCanon_BreakTarget, this);
}

/* 00000820-00000A8C       .text makeFireEffect__9daCanon_cFR4cXyzR5csXyzi */
void daCanon_c::makeFireEffect(cXyz& arg1, csXyz& arg2, int arg3) {
    camera_class* camera = dComIfGp_getCamera(dComIfGp_getPlayerCameraID(0));
    cXyz sp2C(0.75f, 0.75f, 0.75f);
    csXyz sp18;
    sp18.x = -fopCamM_GetAngleX(camera);
    sp18.y = fopCamM_GetAngleY(camera) - -0x8000;
    sp18.z = 0;

    if (arg3 == 0) {
        dComIfGp_particle_setBombSmoke(dPa_name::ID_COMMON_SMOKE_CIRCLE, &arg1, &arg2, &sp2C);
    } else {
        dComIfGp_particle_set(dPa_name::ID_COMMON_LIGHT_FLASH, &arg1, &sp18, &sp2C);
        dComIfGp_particle_setBombSmoke(dPa_name::ID_COMMON_SMOKE_CLOUD, &arg1, &arg2, &sp2C);
        dComIfGp_particle_setBombSmoke(dPa_name::ID_COMMON_SMOKE_CIRCLE, &arg1, &arg2, &sp2C);
        dComIfGp_particle_setToon(dPa_name::ID_COMMON_SMOKE_DEBRIS, &arg1, &arg2, &sp2C);
    }

    plight.mPos = arg1;
    plight.mPos.y += 100.0f;
    plight.mColor.r = 200;
    plight.mColor.g = 200;
    plight.mColor.b = 0xa0;
    plight.mPower = 600.0f;
    plight.mFluctuation = 100.0f;
    dKy_efplight_set(&plight);

    pwind.mPos = arg1;
    pwind.mDir.x = 0.0f;
    pwind.mDir.y = 1.0f;
    pwind.mDir.z = 0.0f;
    pwind.mRadius = 1000.0f;
    pwind.field_0x20 = 0.0f;
    pwind.mStrength = 1.0f;
    dKyw_pntwind_set(&pwind);

    m664 = true;

    fopAcM_seStart(this, JA_SE_OBJ_BOMB_EXPLODE, 0);
    dComIfGp_getVibration().StartShock(7, -0x21, cXyz(0.0f, 1.0f, 0.0f));
}

/* 00000A8C-00000AB8       .text wait_proc_init__9daCanon_cFv */
void daCanon_c::wait_proc_init() {
    attention_info.flags = fopAc_Attn_ACTION_SPEAK_e | fopAc_Attn_LOCKON_TALK_e;
    setProcess(&daCanon_c::wait_proc);
}

/* 00000AB8-00000D14       .text wait_proc__9daCanon_cFv */
void daCanon_c::wait_proc() {
    static char* cut_name_tbl[] = {"Canon_game"};

    f32 unused_abs = (dComIfGp_getPlayer(0)->current.pos - current.pos).absXZ();

    int iVar2 = dComIfGp_evmng_getMyStaffId("Canon");
    if (iVar2 != -1) {
        if (!dComIfGp_evmng_getMyActIdx(iVar2, cut_name_tbl, ARRAY_SSIZE(cut_name_tbl), 1, 0)) {
            cXyz sp24 = current.pos;
            daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
            createTargetObj();
            m65A = 0;
            m65C = 10;
            sp24.x -= cM_ssin(home.angle.y) * 200.0f;
            sp24.z -= cM_scos(home.angle.y) * 200.0f;
            player->setPlayerPosAndAngle(&sp24, home.angle.y);
            dComIfGp_startMiniGame(3);

            for (s32 i = 0; i < ARRAY_SSIZE(m584); i++) {
                m584[i]->onBeforeTex();
            }

            for (s32 i = 0; i < ARRAY_SSIZE(m5AC); i++) {
                m5AC[i]->onBeforeTex();
            }

            game_start_proc_init();
        } else {
            dComIfGp_evmng_cutEnd(iVar2);
        }
    }
}

/* 00000D14-00000DD4       .text game_start_proc_init__9daCanon_cFv */
void daCanon_c::game_start_proc_init() {
    m656 = 60;
    shape_angle.y = home.angle.y;
    shape_angle.x = 0x2aaa;

    if (daNpc_Kg2_c::l_kg2_pointer != NULL) {
        fopAcM_seStart(daNpc_Kg2_c::l_kg2_pointer, JA_SE_PLAYSPOT_START, 0);
    }

    setProcess(&daCanon_c::game_start_proc);
}

/* 00000DD4-00000E08       .text game_start_proc__9daCanon_cFv */
void daCanon_c::game_start_proc() {
    if (m656-- < 0) {
        game_proc_init();
    }
}

/* 00000E08-00000E2C       .text game_proc_init__9daCanon_cFv */
void daCanon_c::game_proc_init() {
    setProcess(&daCanon_c::game_proc);
}

/* 00000E2C-00000FA0       .text game_proc__9daCanon_cFv */
void daCanon_c::game_proc() {
    PadMove();

    if (CPad_CHECK_TRIG_A(0)) {
        cXyz sp08 = current.pos;
        sp08.x += cM_ssin(shape_angle.x) * 200.0f * cM_ssin(shape_angle.y);
        sp08.y += cM_scos(shape_angle.x) * 200.0f;
        sp08.z += cM_ssin(shape_angle.x) * 200.0f * cM_scos(shape_angle.y);

        makeFireEffect(sp08, shape_angle, 0);
        m614 = sp08;

        fopAcM_seStart(this, JA_SE_LK_SHIP_CANNON_FIRE, 0);

        fire_proc_init();
    }
}

/* 00000FA0-00001074       .text fire_proc_init__9daCanon_cFv */
void daCanon_c::fire_proc_init() {
    f32 tmp = (((home.angle.x + 0x1000) - shape_angle.x) / 4096.0f);
    m652 = tmp * 8.0f * 7.0f + 64.0f;
    m654 = m652;
    m65E = 0;
    m660 = 0x400;
    m638 = -20.0f;
    setProcess(&daCanon_c::fire_proc);
    m65C--;
    m584[m65C]->offBeforeTex();
}

/* 00001074-000013AC       .text fire_proc__9daCanon_cFv */
void daCanon_c::fire_proc() {
    cLib_addCalcAngleS2(&m660, 0, 4, 0x100);
    m65E += 0x3800;
    cLib_addCalc2(&m638, 0.0, 0.25, 5.0);
    m620 = getBulEndPos(shape_angle.y, shape_angle.x);
    if (m652-- != 0 && !mCyl2.ChkAtHit()) {
        f32 fVar4 = (f32)m652 / m654;
        f32 tmp2 = 1.0f - (fVar4 - 0.5f) * (fVar4 - 0.5f) * 4.0f;

        cXyz sp54 = m620 - m614;
        s16 idx = 0x4000 - shape_angle.x;
        f32 tmp1 = sp54.absXZ() * 0.25f * (cM_ssin(idx) / cM_scos(idx));

        m62C = (m614 * fVar4) + (m620 * (1.0f - fVar4));
        m62C.y += tmp1 * tmp2;
        bul_set_mtx(&m62C);
        mCyl2.SetC(m62C);
        dComIfG_Ccsp()->Set(&mCyl2);

        mDoAud_seStart(JA_SE_LK_SHIP_CANNON_FLY, &m62C, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    } else {
        mDoAud_seStopActor(&m62C);
        fopKyM_createWpillar(&m62C, 2.0f, 1.0f, 1);
        pause_proc_init();
    }
}

/* 000013AC-00001654       .text pause_proc_init__9daCanon_cFv */
void daCanon_c::pause_proc_init() {
    m656 = 30;
    if (mCyl2.ChkAtHit()) {
        m5AC[m65A]->offBeforeTex();
        csXyz sp08(csXyz::Zero);
        makeFireEffect(m62C, sp08, 1);
        m65A++;
        dComIfGp_setMiniGameRupee(m65A);
        dComIfGp_getVibration().StartShock(7, 0x3e, cXyz(cM_ssin(shape_angle.y), 0.0f, cM_scos(shape_angle.y)));

        if (m65A == 5) {
            if (daNpc_Kg2_c::l_kg2_pointer != NULL) {
                fopAcM_seStart(daNpc_Kg2_c::l_kg2_pointer, JA_SE_PLAYSPOT_END_S, 0);
            }
        } else if (m65C == 0) {
            if (daNpc_Kg2_c::l_kg2_pointer != NULL) {
                fopAcM_seStart(daNpc_Kg2_c::l_kg2_pointer, JA_SE_PLAYSPOT_END_F, 0);
            }
        } else if (daNpc_Kg2_c::l_kg2_pointer != NULL) {
            fopAcM_seStart(daNpc_Kg2_c::l_kg2_pointer, JA_SE_PLAYSPOT_DESTROY, 0);
        }
        mCyl2.ClrAtHit();
    } else if (m65C == 0 && daNpc_Kg2_c::l_kg2_pointer != NULL) {
        fopAcM_seStart(daNpc_Kg2_c::l_kg2_pointer, JA_SE_PLAYSPOT_END_F, 0);
    }

    setProcess(&daCanon_c::pause_proc);
}

/* 00001654-000016A8       .text pause_proc__9daCanon_cFv */
void daCanon_c::pause_proc() {
    if (m656-- < 0) {
        if (m65C > 0 && m65A < 5) {
            game_proc_init();
        } else {
            end_proc_init();
        }
    }
}

/* 000016A8-00001714       .text end_proc_init__9daCanon_cFv */
void daCanon_c::end_proc_init() {
    m656 = 60;

    setProcess(&daCanon_c::end_proc);

    if (m65A == 5) {
        dComIfGp_setMiniGameResult(1);
        daNpc_Kg2_c::setCanonGameResult(1);
    } else {
        dComIfGp_setMiniGameResult(2);
        daNpc_Kg2_c::setCanonGameResult(2);
    }
}

/* 00001714-00001814       .text end_proc__9daCanon_cFv */
void daCanon_c::end_proc() {
    static char* cut_name_tbl[] = {"Canon_game"};

    if (m656 > 0) {
        if (m656 == 30) {
            breakAllObj();
        }
        m656--;
    } else {
        int staffIdx = dComIfGp_evmng_getMyStaffId("Canon");
        if (staffIdx == -1) {
            wait_proc_init();
        } else if (!dComIfGp_evmng_getMyActIdx(staffIdx, cut_name_tbl, ARRAY_SIZE(cut_name_tbl), 1, 0)) {
            dComIfGp_evmng_cutEnd(staffIdx);
            if (dComIfGp_getMiniGameType() == 3) {
                dComIfGp_endMiniGame(3);
            }
            wait_proc_init();
        }
    }
}

/* 00001814-00001A18       .text PadMove__9daCanon_cFv */
void daCanon_c::PadMove() {
    interface_of_controller_pad* pad = &g_mDoCPd_cpadInfo[0];
    f32 stickX = pad->mMainStickPosX;
    f32 stickY = pad->mMainStickPosY;
    s16 target1 = shape_angle.y;
    s16 target2 = shape_angle.x;

    if (stickX > 0.5f) {
        target1 += (s16)((0.5f - stickX) * 1024.0f);
        s16 sVar1 = home.angle.y + -0x1200;
        if (shape_angle.y >= sVar1 && target1 < sVar1) {
            target1 = sVar1;
        }
    } else if (stickX < -0.5f) {
        target1 += (s16)((-0.5f - stickX) * 1024.0f);
        s16 sVar1 = home.angle.y + 0x1200;
        if (shape_angle.y <= sVar1 && target1 > sVar1) {
            target1 = sVar1;
        }
    }

    if (stickY > 0.5f) {
        target2 += (s16)((stickY - 0.5f) * 512.0f);
        s16 sVar1 = home.angle.x + 0x1000;
        if (shape_angle.x <= sVar1 && target2 > sVar1) {
            target2 = sVar1;
        }
    } else if (stickY < -0.5f) {
        target2 += (s16)((stickY + 0.5f) * 512.0f);
        s16 sVar1 = home.angle.x;
        if (shape_angle.x >= sVar1 && target2 < sVar1) {
            target2 = sVar1;
        }
    }

    s16 sVar2 = cLib_addCalcAngleS(&shape_angle.y, target1, 4, 0x100, 0x10);
    s16 sVar4 = cLib_addCalcAngleS(&shape_angle.x, target2, 4, 0x100, 0x10);

    if (sVar2 != 0 || sVar4 != 0) {
        fopAcM_seStart(this, JA_SE_LK_SHIP_CANNON_MOVE, 0);
    }
}

/* 00001A18-00001A38       .text CheckCreateHeap__FP10fopAc_ac_c */
static BOOL CheckCreateHeap(fopAc_ac_c* a_this) {
    return ((daCanon_c*)a_this)->CreateHeap();
}

/* 00001A38-00001E04       .text CreateHeap__9daCanon_cFv */
BOOL daCanon_c::CreateHeap() {
    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(M_arcname, BOMBER_INDEX_BDL_VCANK);
    JUT_ASSERT(823, modelData != NULL);

    mpModel1 = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    if (mpModel1 == NULL) {
        return FALSE;
    }

    J3DModelData* modelData2 = (J3DModelData*)dComIfG_getObjectRes(M_arcname, BOMBER_INDEX_BMD_AISI);
    JUT_ASSERT(831, modelData2 != NULL);

    s8 cVar10 = modelData->getJointName()->getIndex("canon");
    modelData->getJointNodePointer(cVar10)->setCallBack(daCanon_nodeCallBack);
    mpModel1->setUserArea((u32)this);
    mpModel2 = mDoExt_J3DModel__create(modelData2, 0, 0x11020203);
    if (mpModel2 == NULL) {
        return FALSE;
    }

    ResTIMG* pRVar3 = (ResTIMG*)dComIfG_getObjectRes("Bomber", BOMBER_INDEX_BTI_GAME_BOMB_01);
    ResTIMG* pRVar4 = (ResTIMG*)dComIfG_getObjectRes("Bomber", BOMBER_INDEX_BTI_GAME_BOMB_02);

    for (s32 i = 0; i < ARRAY_SSIZE(m584); i++) {
        m584[i] = new dDlst_2DObject_c();
        if (m584[i] == NULL) {
            return FALSE;
        }

        if (!m584[i]->init(pRVar3, pRVar4)) {
            return FALSE;
        }
    }

    ResTIMG* pRVar5 = (ResTIMG*)dComIfG_getObjectRes("Bomber", BOMBER_INDEX_BTI_GAME_SHIP_NODAMAGE);
    ResTIMG* pRVar6 = (ResTIMG*)dComIfG_getObjectRes("Bomber", BOMBER_INDEX_BTI_GAME_HUNE_DAMAGE);

    // Bug: m5AC only has 5 elements, copy-paste mistake.
    for (s32 i = 0; i < ARRAY_SSIZE(m584); i++) {
        m5AC[i] = new dDlst_2DObject_c();
        if (m5AC[i] == NULL) {
            return FALSE;
        }

        if (!m5AC[i]->init(pRVar5, pRVar6)) {
            return FALSE;
        }
    }

    ResTIMG* pRVar7 = (ResTIMG*)dComIfG_getObjectRes("Bomber", BOMBER_INDEX_BTI_GAME_RULE);
    ResTIMG* pRVar8 = (ResTIMG*)dComIfG_getObjectRes("Bomber", BOMBER_INDEX_BTI_GAME_BATTERY);
    ResTIMG* pRVar9 = (ResTIMG*)dComIfG_getObjectRes("Bomber", BOMBER_INDEX_BTI_GAME_BATTERY_BASE);
    ResTIMG* pRVar10 = (ResTIMG*)dComIfG_getObjectRes("Bomber", BOMBER_INDEX_BTI_RUPY_NUM_DEGREE);
    m5C0 = new dDlst_2DBattery_c();

    if (m5C0 == NULL) {
        return FALSE;
    }

    if (!m5C0->init(pRVar7, pRVar8, pRVar9, pRVar10)) {
        return FALSE;
    }
    return TRUE;
}

const f32 unused_4851[] = {0.8f, -0.8f, 0.1f};

/* 00001E4C-00002074       .text GameInfo2DDraw__9daCanon_cFv */
void daCanon_c::GameInfo2DDraw() {
    for (s32 i = 0; i < ARRAY_SSIZE(m584); i++) {
        m584[i]->setPosition(REG10_F(5) + 30.0f, (REG10_F(6) + 368.0f) + (REG10_F(7) + -27.0f) * i);
        m584[i]->setScale(unused_4851[0] + REG10_F(20));
        dComIfGd_set2DOpa(m584[i]);
    }

    for (s32 i = 0; i < ARRAY_SSIZE(m5AC); i++) {
        m5AC[i]->setPosition(REG10_F(8) + 540.0f, (REG10_F(9) + 115.0f) + (REG10_F(10) + 47.0f) * i);
        m5AC[i]->setScale(REG10_F(21) + 1.0f);
        dComIfGd_set2DOpa(m5AC[i]);
    }

    m5C0->setRotate(cM_sht2d((s16)(0x4000 - shape_angle.x)));
    dComIfGd_set2DOpa(m5C0);
}

/* 00002074-00002094       .text daCanonCreate__FPv */
static cPhs_State daCanonCreate(void* i_this) {
    return ((daCanon_c*)i_this)->_create();
}

/* 00002094-000023C0       .text _create__9daCanon_cFv */
cPhs_State daCanon_c::_create() {
    fopAcM_SetupActor(this, daCanon_c);

    cPhs_State PVar1 = dComIfG_resLoad(&mPhase, M_arcname);
    if (PVar1 == cPhs_COMPLEATE_e) {
        if (!fopAcM_entrySolidHeap(this, CheckCreateHeap, 0x62E0)) {
            return cPhs_ERROR_e;
        }

        set_mtx();
        MTXCopy(mDoMtx_stack_c::get(), m5C4);
        fopAcM_SetMtx(this, mpModel1->getBaseTRMtx());
        MTXCopy(mpModel1->getBaseTRMtx(), m5C4);

        mStts1.Init(0xff, 0xff, this);
        mCyl1.Set(canon_cyl_src);
        mCyl1.SetStts(&mStts1);
        mCyl2.Set(canon_cyl2_src);
        mCyl2.SetStts(&mStts1);

        shape_angle.x = 0x2AAA;
        home.angle.x = 0x2000;

        wait_proc_init();

        m64E = 0;
        m650 = 3;

        m63C = current.pos;
        m63C.x += cM_ssin(shape_angle.x) * 200.0f * cM_ssin(shape_angle.y);
        m63C.z += cM_ssin(shape_angle.x) * 200.0f * cM_scos(shape_angle.y);

        m648 = csXyz::Zero;
        m648.y = shape_angle.y;

        canon_p = this;
    }
    return PVar1;
}

bool daCanon_c::_delete() {
    dComIfG_resDeleteDemo(&mPhase, M_arcname);
    if (dComIfGp_getMiniGameType() == 3) {
        dComIfGp_endMiniGame(3);
    }
    mDoAud_seDeleteObject(&m62C);
    daCanon_c::canon_p = NULL;
    return true;
}

/* 00002578-00002600       .text daCanonDelete__FPv */
static BOOL daCanonDelete(void* i_this) {
    return ((daCanon_c*)i_this)->_delete();
}

bool daCanon_c::_execute() {
    if (m664) {
        dKy_actor_addcol_set(0, 0, 0, 0.0f);
        dKy_efplight_cut(&plight);
        dKyw_pntwind_cut(&pwind);
        m664 = false;
    }

    set_mtx();

    (this->*m290)();

    cXyz sp08 = current.pos;
    sp08.x += REG10_F(12) * cM_ssin(shape_angle.y);
    sp08.z += REG10_F(12) * cM_scos(shape_angle.y);

    mCyl1.SetC(sp08);
    mCyl1.SetR(REG10_F(13) + 75.0f);
    dComIfG_Ccsp()->Set(&mCyl1);
    return false;
}

/* 00002600-0000274C       .text daCanonExecute__FPv */
static BOOL daCanonExecute(void* i_this) {
    return ((daCanon_c*)i_this)->_execute();
}

bool daCanon_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel1, &tevStr);
    mDoExt_modelUpdateDL(mpModel1);

    if (checkProcess(&daCanon_c::fire_proc)) {
        g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &m62C, &tevStr);
        g_env_light.setLightTevColorType(mpModel2, &tevStr);
        mDoExt_modelUpdateDL(mpModel2);
    }

    if (dComIfGp_getMiniGameType() == 3) {
        GameInfo2DDraw();
    }
    return true;
}

/* 0000274C-0000283C       .text daCanonDraw__FPv */
static BOOL daCanonDraw(void* i_this) {
    return ((daCanon_c*)i_this)->_draw();
}

/* 0000283C-00002844       .text daCanonIsDelete__FPv */
static BOOL daCanonIsDelete(void*) {
    return TRUE;
}

static actor_method_class daCanonMethodTable = {
    (process_method_func)daCanonCreate,
    (process_method_func)daCanonDelete,
    (process_method_func)daCanonExecute,
    (process_method_func)daCanonIsDelete,
    (process_method_func)daCanonDraw,
};

actor_process_profile_definition g_profile_Canon = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_Canon,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daCanon_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_Canon,
    /* Actor SubMtd */ &daCanonMethodTable,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
