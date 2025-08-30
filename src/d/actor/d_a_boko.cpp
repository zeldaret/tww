/**
 * d_a_boko.cpp
 * Object - Enemy weapons
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_boko.h"
#include "d/actor/d_a_player.h"
#include "d/res/res_boko.h"
#include "d/res/res_nata.h"
#include "d/res/res_club.h"
#include "d/res/res_tkwn.h"
#include "d/res/res_spear.h"
#include "d/res/res_pgsw.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_bg_s_lin_chk.h"
#include "d/d_s_play.h"
#include "SSystem/SComponent/c_counter.h"

u32 daBoko_c::m_bound_se[] = {
    /* Type_BOKO_STICK_e    */ JA_SE_CM_BOKOBOU_BOUND,
    /* Type_MACHETE_e       */ JA_SE_CM_NATA_BOUND,
    /* Type_STALFOS_MACE_e  */ JA_SE_OBJ_ST_CLUB_FALL,
    /* Type_DARKNUT_SWORD_e */ JA_SE_OBJ_TN_SWORD_FALL,
    /* Type_MOBLIN_SPEAR_e  */ JA_SE_CM_LANCE_BOUND,
    /* Type_PGANON_SWORD_e  */ JA_SE_OBJ_TN_SWORD_FALL,
};

u32 daBoko_c::m_heap_size[] = {
    /* Type_BOKO_STICK_e    */ 0x2300,
    /* Type_MACHETE_e       */ 0x1240,
    /* Type_STALFOS_MACE_e  */ 0x1240,
    /* Type_DARKNUT_SWORD_e */ 0x1240,
    /* Type_MOBLIN_SPEAR_e  */ DEMO_SELECT(0x3000, 0x4200),
    /* Type_PGANON_SWORD_e  */ 0x2000
};

char* daBoko_c::m_arc_name[] = {
    /* Type_BOKO_STICK_e    */ "Boko",
    /* Type_MACHETE_e       */ "Nata",
    /* Type_STALFOS_MACE_e  */ "Club",
    /* Type_DARKNUT_SWORD_e */ "Tkwn",
    /* Type_MOBLIN_SPEAR_e  */ "Spear",
    /* Type_PGANON_SWORD_e  */ "Pgsw"
};

Vec daBoko_c::m_cull_min[] = {
    /* Type_BOKO_STICK_e    */ {-20.0f, -10.0f, -95.0f},
    /* Type_MACHETE_e       */ {-20.0f, -10.0f, -95.0f},
    /* Type_STALFOS_MACE_e  */ {-35.0f, -35.0f, -125.0f},
    /* Type_DARKNUT_SWORD_e */ {-45.0f, -10.0f, -145.0f},
    /* Type_MOBLIN_SPEAR_e  */ {-20.0f, -20.0f, -180.0f},
    /* Type_PGANON_SWORD_e  */ {-50.0f, -20.0f, -140.0f},
};

Vec daBoko_c::m_cull_max[] = {
    /* Type_BOKO_STICK_e    */ {20.0f, 10.0f, 95.0f},
    /* Type_MACHETE_e       */ {20.0f, 10.0f, 95.0f},
    /* Type_STALFOS_MACE_e  */ {35.0f, 35.0f, 120.0f},
    /* Type_DARKNUT_SWORD_e */ {45.0f, 10.0f, 130.0f},
    /* Type_MOBLIN_SPEAR_e  */ {20.0f, 20.0f, 200.0f},
    /* Type_PGANON_SWORD_e  */ {50.0f, 20.0f, 120.0f},
};

static cXyz l_break_particle_offset(0.0f, 0.0f, 30.0f);
dBgS_ObjGndChk daBoko_c::m_ground_check;
dBgS_ObjLinChk daBoko_c::m_line_check;

const s16 daBoko_HIO_c0::throw_timer = 2;
const f32 daBoko_HIO_c0::throw_speed = 70.0f;

static daBoko_HIO_c l_HIO;

/* 000000EC-0000017C       .text keDraw__8daBoko_cFv */
void daBoko_c::keDraw() {
#ifdef __MWERKS__
    mpLineKe->lineMat.update(0xA, 1.25f, (GXColor){0xFF, 0x64, 0x00, 0xFF}, 2, &tevStr);
#else
    GXColor color = {0xFF, 0x64, 0x00, 0xFF};
    mpLineKe->lineMat.update(0xA, 1.25f, color, 2, &tevStr);
#endif
    dComIfGd_set3DlineMat(&mpLineKe->lineMat);
}

/* 0000017C-00000620       .text keCalc1__8daBoko_cFP6ke_c_si */
void daBoko_c::keCalc1(ke_c_s* arg1, int arg2) {
    s32 i;
    cXyz* pcVar11 = &arg1->m000[1];
    cXyz* pcVar10 = &arg1->m078[1];
    cXyz sp18(0.0f, 0.0f, 21.875f);
    f32 tmp = -6.25f;
    f32 fVar1;
    f32 fVar7;
    f32 fVar5;
    f32 fVar6;

    dBgS_GndChk gndChk;
    gndChk.m_pos.set(pcVar11->x, pcVar11->y + 100.0f, pcVar11->z);

    f32 fVar14 = dComIfG_Bgsp()->GroundCross(&gndChk) + 3.0f;
    if (fVar14 == -G_CM3D_F_INF) {
        fVar14 = G_CM3D_F_INF;
    }

    if (fVar14 - pcVar11->y > 50.0f) {
        fVar14 = pcVar11->y;
    }

    i = 1;
    fVar1 = arg2 * 0.001f + 0.75f;

    for (; i < 10; i++, pcVar11++, pcVar10++) {
        fVar7 = pcVar10->x + (pcVar11->x - pcVar11[-1].x);
        fVar6 = pcVar10->z + (pcVar11->z - pcVar11[-1].z);
        f32 fVar5tmp = pcVar11->y + pcVar10->y + tmp;

        if (fVar5tmp < fVar14) {
            fVar5tmp = fVar14;
        }

        fVar5 = fVar5tmp - pcVar11[-1].y;
        s16 iVar7 = -cM_atan2s(fVar5, fVar6);
        s32 iVar8 = cM_atan2s(fVar7, std::sqrtf(SQUARE(fVar5) + SQUARE(fVar6)));
        mDoMtx_XrotS(*calc_mtx, iVar7);
        mDoMtx_YrotM(*calc_mtx, iVar8);
        cXyz sp0C;
        MtxPosition(&sp18, &sp0C);

        pcVar10->x = pcVar11->x;
        pcVar10->y = pcVar11->y;
        pcVar10->z = pcVar11->z;

        pcVar11->x = pcVar11[-1].x + sp0C.x;
        pcVar11->y = pcVar11[-1].y + sp0C.y;
        pcVar11->z = pcVar11[-1].z + sp0C.z;

        pcVar10->x = fVar1 * (pcVar11->x - pcVar10->x);
        pcVar10->y = fVar1 * (pcVar11->y - pcVar10->y);
        pcVar10->z = fVar1 * (pcVar11->z - pcVar10->z);
    }

    cXyz* segments = mpLineKe->lineMat.mpLines[arg2].mpSegments;
    for (s32 i = 0; i < 10; i++) {
        *segments++ = arg1->m000[i];
    }
}

/* 000009DC-00000B2C       .text keCalc__8daBoko_cFv */
void daBoko_c::keCalc() {
    ke_c_s* ke = &mpLineKe->m001C[0];

    MTXCopy(mpModel->getBaseTRMtx(), *calc_mtx);

    for (s32 i = 0; i < ARRAY_SSIZE(mpLineKe->m001C); i++, ke++) {
        MtxPush();
        cXyz sp08;
        sp08.x = cM_ssin(15000 * i) * 12.0f;
        sp08.y = cM_ssin(10000 * i) * 12.0f;
        sp08.z = cM_ssin(7000 * i) * 10.0f + 100.0f;
        MtxPosition(&sp08, &ke->m000[0]);
        keCalc1(ke, i);
        MtxPull();
    }
}

/* 00000B2C-00000DC4       .text draw__8daBoko_cFv */
BOOL daBoko_c::draw() {
    daPy_py_c* player = daPy_getPlayerActorClass();

    if (checkNoDraw()) {
        if (mParticleCallBack.getEmitter() != NULL) {
            mParticleCallBack.getEmitter()->setStatus(4);
        }
        return TRUE;
    }

    if (mParticleCallBack.getEmitter() != NULL) {
        mParticleCallBack.getEmitter()->clearStatus(4);
    }

    if (mFlameTimer != 0) {
        dStage_darkStatus_c* dark_stts = dStage_roomControl_c::getDarkStatus();
        if (dark_stts != NULL) {
            GXColor color = {0xEB, 0x7D, 0, 0};
            dComIfGd_setAlphaModelColor(color);

            s32 i;
            for (i = 0; i < 2; i++) {
                dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_SPHERE, mAlphaModelMtx[i], dark_stts->getBokoAlpha(i));
            }

            if (getNowMode() == Mode_PLAYER_CARRY_e && dStage_roomControl_c::getDarkMode() != 0) {
                for (s32 j = i; j < 4; j++) {
                    dComIfGd_setSpotModel(dDlst_alphaModel_c::TYPE_SPHERE, mAlphaModelMtx[j], dark_stts->getBokoAlpha(j));
                }
            }
        }
    }

    if (getNowMode() == Mode_PLAYER_CARRY_e && player->checkPlayerNoDraw()) {
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    if (fopAcM_GetParam(this) == Type_PGANON_SWORD_e) {
        mBrkAnm.entry(mpModel->getModelData());
    }

    mDoExt_modelEntryDL(mpModel);

    if (fopAcM_GetParam(this) == Type_PGANON_SWORD_e) {
        mBrkAnm.remove(mpModel->getModelData());
    }

#if VERSION > VERSION_DEMO
    if (fopAcM_GetParam(this) == Type_STALFOS_MACE_e && getNowMode() != Mode_PLAYER_CARRY_e && getNowMode() != Mode_ENEMY_CARRY_e) {
        cXyz sp0C(current.pos.x, current.pos.y + 100.0f, current.pos.z);
        m2B4 = dComIfGd_setShadow(m2B4, 1, mpModel, &sp0C, 400.0f, 0.0f, current.pos.y, mAcch.GetGroundH(), mAcch.m_gnd, &tevStr);
    }
#endif

    if (mpLineKe != NULL) {
        keDraw();
    }
    return TRUE;
}

/* 00000DC4-00000DE4       .text daBoko_Draw__FP8daBoko_c */
static BOOL daBoko_Draw(daBoko_c* i_this) {
    return i_this->draw();
}

/* 00000DE4-00000EB0       .text setTopRootPos__8daBoko_cFi */
void daBoko_c::setTopRootPos(int arg1) {
    s32 type = fopAcM_GetParam(this);
    if (arg1 != 0) {
        mDoMtx_stack_c::transS(current.pos.x, current.pos.y + 5.0f, current.pos.z);
        mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
    } else {
        mDoMtx_stack_c::copy(mpModel->getBaseTRMtx());
    }
    mDoMtx_stack_c::multVec(&m_top_offset[type], &m2D0);
    mDoMtx_stack_c::multVec(&m_root_offset[type], &m2DC);
}

/* 00000EB0-00000F60       .text setBaseMatrix__8daBoko_cFv */
void daBoko_c::setBaseMatrix() {
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y + 5.0f, current.pos.z);
    mDoMtx_stack_c::ZXYrotM(shape_angle.x, shape_angle.y, shape_angle.z);
#if VERSION > VERSION_DEMO
    if (fopAcM_GetParam(this) == Type_STALFOS_MACE_e) {
        mDoMtx_stack_c::XrotM(-1000);
        mDoMtx_stack_c::transM(0.0f, 10.0f, 0.0f);
    }
#endif
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 00000F60-00000FA4       .text checkNoDraw__8daBoko_cFv */
BOOL daBoko_c::checkNoDraw() {
    return m2B9 || getNowMode() == Mode_4_e || (getNowMode() == Mode_PLAYER_CARRY_e && dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK80_e));
}

/* 00000FA4-00001340       .text setFlameEffect__8daBoko_cFv */
void daBoko_c::setFlameEffect() {
    /* Nonmatching */
    static const s16 base_angle[] = {150, 200, 180, 120};

    dStage_darkStatus_c* dark_stts = dStage_roomControl_c::getDarkStatus();

    if (dark_stts != NULL) {
        for (s32 i = 0; i < 4; i++) {
            cLib_addCalc2(&m7E4, cM_rndF(0.2f) + 1.0f, 0.5f, 0.01f);
            f32 scale = m7E4 * dark_stts->getBokoScale(i);
            s16 y = g_Counter.mTimer * base_angle[i];
            mDoMtx_stack_c::transS(m2D0.x, m2D0.y, m2D0.z);
            mDoMtx_stack_c::ZXYrotM(0, y, y);
            mDoMtx_stack_c::scaleM(scale, scale, scale);
            MTXCopy(mDoMtx_stack_c::get(), mAlphaModelMtx[i]);
        }
    }

    if (mParticleCallBack.getEmitter() == NULL) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_01EA, &m2D0, NULL, &scale, 0xff, &mParticleCallBack);
        m320 = m2D0;
    }

    JPABaseEmitter* pJVar5 = mParticleCallBack.getEmitter();
    if (pJVar5 != NULL) {
        f32 fVar1 = (REG0_F(4) + -0.03f) * (m2D0.x - m320.x);
        if (fVar1 > 1.0f) {
            fVar1 = 1.0f;
        } else if (fVar1 < -1.0f) {
            fVar1 = -1.0f;
        }

        f32 fVar2 = (REG0_F(4) + -0.03f) * (m2D0.z - m320.z);
        if (fVar2 > 1.0f) {
            fVar2 = 1.0f;
        } else if (fVar2 < -1.0f) {
            fVar2 = -1.0f;
        }

        JGeometry::TVec3<f32> s(fVar1, 0.1f, fVar2);
        pJVar5->setDirection(s);

        s = current.pos - old.pos;
        f32 fVar11 = (REG0_F(12) + 0.05f) * std::sqrtf(SQUARE(s.x) + SQUARE(s.y) + SQUARE(s.z)) + 1.0f;
        if (fVar11 > REG0_F(13) + 2.0f) {
            fVar11 = REG0_F(13) + 2.0f;
        }

        JGeometry::TVec3<f32> s2(1.0f, fVar11, 1.0f);
        pJVar5->setGlobalParticleScale(s2);
        m320 = m2D0;
        mDoAud_seStart(JA_SE_OBJ_TORCH_BURNING, &m2D0, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
    }

    if (!checkNoDraw()) {
        dComIfGp_particle_setSimple(dPa_name::ID_COMMON_4004, &m2D0);
    }
}

/* 00001340-000013CC       .text setRoomInfo__8daBoko_cFv */
void daBoko_c::setRoomInfo() {
    int roomNo;
    if (mAcch.GetGroundH() != -G_CM3D_F_INF) {
        roomNo = dComIfG_Bgsp()->GetRoomId(mAcch.m_gnd);
        tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mAcch.m_gnd);
    } else {
        roomNo = dComIfGp_roomControl_getStayNo();
    }
    current.roomNo = tevStr.mRoomNo = roomNo;
    mStts.SetRoomId(roomNo);
}

/* 000013CC-0000155C       .text setThrowReverse__8daBoko_cFs */
void daBoko_c::setThrowReverse(s16 arg1) {
    fopAcM_seStart(this, m_bound_se[fopAcM_GetParam(this)], 100);
    procMove_init();

    if (shape_angle.x >= 0) {
        m2C2 = -0x7ff;
    } else {
        m2C2 = 0x7ff;
    }

    m2C0 = 0;
    fopAcM_SetGravity(this, -3.0f);
    fopAcM_GetSpeed(this).y = 15.0f;
    speedF *= 0.25f;
    current.angle.y = arg1 + cM_rndFX(12288.0f);

    s32 sVar1 = cLib_distanceAngleS(current.angle.y, shape_angle.y);
    if (sVar1 >= 0x4000) {
        m2C2 = -(cM_rndFX(500.0f) + 3500.0f);
        shape_angle.y = current.angle.y - -0x8000;
    } else {
        m2C2 = cM_rndFX(500.0f) + 3500.0f;
        shape_angle.y = current.angle.y;
    }
}

/* 0000155C-000015E0       .text procWait_init__8daBoko_cFv */
BOOL daBoko_c::procWait_init() {
    speedF = 0.0f;
    m2C0 = 0;
    m2C2 = 0;
    mCurrentProc = &daBoko_c::procWait;
    cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    setNowMode(Mode_WAIT_e);
    fopAcM_cancelCarryNow(this);
    gravity = -3.0f;
    return TRUE;
}

/* 000015E0-000016E4       .text procWait__8daBoko_cFv */
BOOL daBoko_c::procWait() {
    if (fopAcM_checkCarryNow(this)) {
        gravity = 0.0f;
        mCurrentProc = &daBoko_c::procCarry;
        speedF = 0.0f;
        speed = cXyz::Zero;
        if (getNowMode() != Mode_PLAYER_CARRY_e) {
            setNowMode(Mode_ENEMY_CARRY_e);
        }
        cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        mbFloorFlg = false;
        procCarry();
    } else if (!mbFloorFlg) {
        fopAcM_posMoveF(this, NULL);
        mAcch.CrrPos(*dComIfG_Bgsp());
        if (!mAcch.ChkGroundHit()) {
            procMove_init();
        }
        setRoomInfo();
        setBaseMatrix();
    }
    return TRUE;
}

/* 000016E4-0000175C       .text procMove_init__8daBoko_cFv */
BOOL daBoko_c::procMove_init() {
    mCurrentProc = &daBoko_c::procMove;
    setNowMode(Mode_MOVE_e);
    fopAcM_setCarryNow(this, FALSE);
    cLib_offBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
    m2BB = 0x14;
    mbFloorFlg = false;
    return TRUE;
}

/* 0000175C-00001E94       .text procMove__8daBoko_cFv */
BOOL daBoko_c::procMove() {
    /* Nonmatching - fpr regswap */
    BOOL bVar4 = FALSE;
    fopAcM_posMoveF(this, NULL);
    f32 fVar14_2 = m2DC.y;
    f32 fVar15_2 = m2D0.y;
    setTopRootPos(1);

    cXyz sp1C(m2DC.x, fVar14_2, m2DC.z);
    m_ground_check.SetPos(&sp1C);

    f32 fVar14 = dComIfG_Bgsp()->GroundCross(&m_ground_check);
    if (fVar14 == -G_CM3D_F_INF) {
        fVar14 = mAcch.GetGroundH();
    }
    f32 fVar2 = m2DC.y - fVar14;
    sp1C.set(m2D0.x, fVar15_2, m2D0.z);
    m_ground_check.SetPos(&sp1C);

    f32 fVar15 = dComIfG_Bgsp()->GroundCross(&m_ground_check);
    if (fVar15 == -G_CM3D_F_INF) {
        fVar15 = mAcch.GetGroundH();
    }

    f32 fVar3 = m2D0.y - fVar15;
    if ((fVar2 < fVar3 && fVar2 < 0.0f) || (fVar3 < fVar2 && fVar3 < 0.0f)) {
        if (speed.y < -10.0f) {
            speed.y *= -0.5f;
            if (speed.y > 20.0f) {
                speed.y = 20.0f;
            }
        }

        if (m2BB != 0) {
            if (fVar2 < fVar3) {
                current.pos.y -= fVar2;
            } else {
                current.pos.y -= fVar3;
            }
            m2BB--;
        }

        sp1C.set(m2D0.x - m2DC.x, fVar15 - fVar14, m2D0.z - m2DC.z);
        s16 sVar5 = shape_angle.x - cM_atan2s(-sp1C.y, sp1C.absXZ());
        m2C0 = sVar5 * -0.2f;
        if (m2C0 == 0 && sVar5 != 0) {
            m2C0 = -sVar5;
        }

        if (m2C0 == 0 && std::fabsf(speedF) < 1.0f) {
            m2C0 = -sVar5;
            if (m2BB > 2) {
                m2BB -= 2;
            } else {
                m2BB = 0;
            }

            if (shape_angle.x > 0) {
                m2C0 = -0x5a;
            } else {
                m2C0 = 0x5a;
            }
        }

        u32 uVar7 = speed.y * 8.0f;
        if (uVar7 > 100) {
            uVar7 = 100;
        }

        fopAcM_seStart(this, m_bound_se[fopAcM_GetParam(this)], uVar7);
        speedF *= 0.7f;
        m2C2 *= 0.7f;
        bVar4 = TRUE;
    }

    s32 iVar6 = abs(m2C0);
    s32 iVar8 = abs(m2C2);
    if (iVar8 > iVar6) {
        shape_angle.x += m2C2;
    } else {
        shape_angle.x += m2C0;
    }

    if (m2C2 == 0) {
        if (shape_angle.x > 0x3a00) {
            shape_angle.x = 0x3a00;
        } else if (shape_angle.x < -0x3a00) {
            shape_angle.x = -0x3a00;
        }
    }

    if (m2C0 != 0) {
        s16 target_angle_z;
        if (abs(shape_angle.z) <= 0x4000) {
            target_angle_z = 0;
        } else {
            target_angle_z = -0x8000;
        }
        cLib_addCalcAngleS(&shape_angle.z, target_angle_z, 5, 0x1000, 0x100);
    }

    f32 fVar14_3 = speed.y;
    mAcch.CrrPos(*dComIfG_Bgsp());
    setRoomInfo();

    if (mAcch.ChkGroundHit() && fVar14 <= 2.5f) {
        if (dComIfG_Bgsp()->ChkMoveBG(mAcch.m_gnd) && fopAcM_GetName(dComIfG_Bgsp()->GetActorPointer(mAcch.m_gnd)) == PROC_TBOX) {
            if (speedF < 15.0f) {
                speedF = 15.0f;
            }
            speed.y = 20.0f;
        } else {
            cM3dGPla* pcVar10 = dComIfG_Bgsp()->GetTriPla(mAcch.m_gnd);
            s16 iVar6 = cM_atan2s(pcVar10->mNormal.x, pcVar10->mNormal.z);
            s16 tmp = iVar6 - shape_angle.y;
            iVar6 = cM_atan2s(std::sqrtf(SQUARE(pcVar10->mNormal.x) + SQUARE(pcVar10->mNormal.z)) * cM_scos(tmp), pcVar10->mNormal.y);
            s16 __x = iVar6 - shape_angle.x;

            if (abs(__x) > 0x1000 && m2BB != 0) {
                speed.y = 15.0f;
                if (speedF < 15.0f) {
                    speedF = 15.0f;
                }
                m2C2 = 0;
                m2C0 = -(__x >> 2);
                if (m2BB > 4) {
                    m2BB -= 4;
                } else {
                    m2BB = 0;
                }
            } else {
                shape_angle.x = iVar6;
                shape_angle.z = 0;
                procWait_init();
            }
        }

        if (!bVar4) {
            u32 uVar7 = std::fabsf(old.pos.y - current.pos.y) * 8.0f;
            if (uVar7 > 100) {
                uVar7 = 100;
            }

            fopAcM_seStart(this, m_bound_se[fopAcM_GetParam(this)], uVar7);
            speedF *= 0.7f;
        }
    } else {
        speed.y = fVar14_3;
    }
    setBaseMatrix();
    return TRUE;
}

/* 00001E94-000021B8       .text procThrow__8daBoko_cFv */
BOOL daBoko_c::procThrow() {
    cXyz sp18 = m2DC;
    fopAcM_posMoveF(this, NULL);
    shape_angle.x = cM_atan2s(-speed.y, speed.absXZ());
    shape_angle.y = cM_atan2s(speed.x, speed.z);
    current.angle.y = shape_angle.y;
    if (m2C8 > 0) {
        m2C8--;
        if (m2C8 == 0) {
            fopAcM_SetGravity(this, -3.0f);
        }
    }

    mAcch.CrrPos(*dComIfG_Bgsp());
    setRoomInfo();
    setBaseMatrix();
    setTopRootPos(0);

    BOOL bVar1 = FALSE;
    s16 unaff_r28;

    if (mCps.ChkAtHit() || mAcch.ChkGroundHit() || mAcch.ChkWallHit() || mAcch.ChkRoofHit()) {
        bVar1 = TRUE;
        if (mAcch.ChkRoofHit() && speed.y > 0.0f) {
            speed.y *= -0.5f;
        }

        if (mCps.ChkAtHit()) {
            unaff_r28 = current.angle.y + cM_rndF(16384.0f);
        } else if (mAcch.ChkWallHit()) {
            unaff_r28 = mAcchCir.GetWallAngleY();
        } else {
            unaff_r28 = current.angle.y;
        }
    }

    mCps.SetStartEnd(sp18, m2D0);
    dComIfG_Ccsp()->Set(&mCps);

    if (!bVar1) {
        m_line_check.Set(&old.pos, &m2D0, this);
        if (dComIfG_Bgsp()->LineCross(&m_line_check)) {
            bVar1 = true;
            cM3dGPla* pcVar6 = dComIfG_Bgsp()->GetTriPla(m_line_check);
            bool bVar7;
            if (!(pcVar6->mNormal.y >= 0.5f) && !(pcVar6->mNormal.y < -0.8f)) {
                bVar7 = true;
            } else {
                bVar7 = false;
            }

            if (bVar7) {
                unaff_r28 = cM_atan2s(pcVar6->mNormal.x, pcVar6->mNormal.z);
            } else {
                unaff_r28 = current.angle.y;
            }
        }
    }

    if (bVar1) {
        setThrowReverse(unaff_r28);
    }

    return TRUE;
}

/* 000021B8-00002624       .text procCarry__8daBoko_cFv */
BOOL daBoko_c::procCarry() {
    if (fopAcM_checkCarryNow(this) || !mbThrow) {
        mDoMtx_multVecZero(mpModel->getBaseTRMtx(), &current.pos);
        mDoMtx_MtxToRot(mpModel->getBaseTRMtx(), &shape_angle);
    }

    fopAc_ac_c* link = dComIfGp_getLinkPlayer();
    cXyz linkFootPos(link->current.pos.x, link->current.pos.y + 5.0f, link->current.pos.z);

    if (!fopAcM_checkCarryNow(this)) {
        fopAcM_setCarryNow(this, FALSE);
        setTopRootPos(1);

        if (mbThrow) {
            mCurrentProc = &daBoko_c::procThrow;
            setNowMode(Mode_THROW_e);
            gravity = 0.0f;
            shape_angle.x = m2CA;
            shape_angle.y = link->shape_angle.y;
            current.angle.y = shape_angle.y;
            speedF = 70.0f * cM_scos(shape_angle.x);
            speed.y = -70.0f * cM_ssin(shape_angle.x);
            m2C8 = 2;
            mbThrow = false;
            mCps.ResetAtHit();
            m_line_check.Set(&linkFootPos, &current.pos, this);

            if (dComIfG_Bgsp()->LineCross(&m_line_check)) {
                current.pos = m_line_check.GetCross();
#if VERSION == VERISON_DEMO
                setThrowReverse(shape_angle.y - -0x8000);
#else
                cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(m_line_check);
                current.pos += *triPla->GetNP() * 10.0f;
                setThrowReverse(cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z));
#endif
            } else {
                procThrow();
            }
        } else if (mbFloorFlg) {
            if (shape_angle.z >= 0x4000) {
                shape_angle.z = 0;
                shape_angle.x += 0x8000;
                shape_angle.y += 0x8000;
            }
            procWait_init();
        } else {
            current.angle.y = shape_angle.y + 0x8000;
            if (getNowMode() == Mode_PLAYER_CARRY_e) {
                m_line_check.Set(&linkFootPos, &current.pos, this);
                if (dComIfG_Bgsp()->LineCross(&m_line_check)) {
                    current.pos = m_line_check.GetCross();
                }
            }

            procMove_init();

            s32 i;
            for (i = 0; i < 3; i++) {
                m_ground_check.SetPos(&current.pos);
                if (dComIfG_Bgsp()->GroundCross(&m_ground_check) != -G_CM3D_F_INF) {
                    break;
                }
                current.pos.x -= 50.0f * cM_ssin(shape_angle.y);
                current.pos.z -= 50.0f * cM_scos(shape_angle.y);
            }

            if (i == 3) {
                current.pos = linkFootPos;
                current.pos.y = 50.0f;
            }

            old.pos = current.pos;
            current.pos.y -= 5.0f;
            m2C0 = 0;
            gravity = -3.0f;
            procMove();
        }
    }
    return TRUE;
}

/* 00002624-00002A04       .text execute__8daBoko_cFv */
BOOL daBoko_c::execute() {
    if (mCurrentProc) {
        (this->*mCurrentProc)();
    }

    attention_info.position = current.pos;
    eyePos = attention_info.position;

    BOOL bVar4 = FALSE;
    if (mSph.ChkTgHit()) {
        cCcD_Obj* pcVar2 = mSph.GetTgHitObj();
        if (pcVar2 != NULL) {
            if (mFlameTimer > 0 && pcVar2->ChkAtType(AT_TYPE_WATER)) {
                mFlameTimer = 1;
                bVar4 = TRUE;
            } else if (mFlameTimer == 0 && pcVar2->ChkAtType(AT_TYPE_UNK20000 | AT_TYPE_FIRE)) {
                mDoAud_seStart(JA_SE_OBJ_TORCH_IGNITION, &m2D0, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                fopAcM_SetCullSize(this, fopAc_CULLSPHERE_6_e);
                mFlameTimer = 900;
            }
        }
    }

    mpModel->calc();
    setTopRootPos(0);

    if (mFlameTimer != 0) {
        if (getNowMode() != Mode_ENEMY_CARRY_e) {
            mFlameTimer--;
        }

        f32 waterY;
        if (bVar4 || (fopAcM_getWaterY(&m2D0, &waterY) && waterY >= m2D0.y)) {
            if (mFlameTimer != 0) {
                dComIfGp_particle_set(dPa_name::ID_COMMON_035A, &m2D0);
            }
            mFlameTimer = 0;
        }

        if (mFlameTimer != 0) {
            setFlameEffect();
        } else {
            fopAcM_SetCullSize(this, fopAc_CULLBOX_CUSTOM_e);
            m7E4 = 0.0f;
            if (mParticleCallBack.getEmitter() != NULL) {
                mDoAud_seStart(JA_SE_OBJ_TORCH_OFF, &m2D0, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
                mParticleCallBack.remove();
            }
        }

        mLight.mPos = m2D0;
        mLight.mPower = m7E4 * 150.0f;
    } else {
        mSph.ResetTgHit();
        mLight.mPower = 0.0f;
    }

    if (fopAcM_GetParam(this) == Type_BOKO_STICK_e) {
        if (mFlameTimer > 0) {
            mSph.OnAtSPrmBit(cCcD_TgSPrm_Set_e);
        } else {
            mSph.OffAtSPrmBit(cCcD_TgSPrm_Set_e);
        }
        mSph.SetC(m2D0);
        dComIfG_Ccsp()->Set(&mSph);
        if (getNowMode() == Mode_PLAYER_CARRY_e) {
            dComIfG_Ccsp_SetMass(&mSph, 1);
        } else {
            dComIfG_Ccsp_SetMass(&mSph, 4);
        }
    }

    if (mpLineKe != NULL) {
        keCalc();
    }

    if (fopAcM_GetParam(this) == Type_PGANON_SWORD_e) {
        if (dComIfGs_isEventBit(0x3a08)) {
            mBrkAnm.play();
            bVar4 = true;
            if (mBrkAnm.isStop()) {
                fopAcM_delete(this);
            }
        }
    }
    return TRUE;
}

/* 00002A04-00002A24       .text daBoko_Execute__FP8daBoko_c */
static BOOL daBoko_Execute(daBoko_c* i_this) {
    return i_this->execute();
}

/* 00002A24-00002A2C       .text daBoko_IsDelete__FP8daBoko_c */
static BOOL daBoko_IsDelete(daBoko_c* i_this) {
    return TRUE;
}

/* 00002A2C-00002AA4       .text bokoDelete__8daBoko_cFv */
BOOL daBoko_c::bokoDelete() {
    mDoAud_seDeleteObject(&m2D0);
    mParticleCallBack.end();
    dKy_plight_cut(&mLight);
    dComIfG_resDelete(&mPhase, m_arc_name[fopAcM_GetParam(this)]);
    return TRUE;
}

/* 00002AA4-00002AC8       .text daBoko_Delete__FP8daBoko_c */
static BOOL daBoko_Delete(daBoko_c* i_this) {
    i_this->bokoDelete();
    return TRUE;
}

/* 00002AC8-00002AE8       .text daBoko_createHeap__FP10fopAc_ac_c */
static BOOL daBoko_createHeap(fopAc_ac_c* i_this) {
    return static_cast<daBoko_c*>(i_this)->createHeap();
}

/* 00002AE8-00002CFC       .text createHeap__8daBoko_cFv */
BOOL daBoko_c::createHeap() {
    static const s32 model_idx[] = {BOKO_BDL_BOKO, NATA_BDL_BK_NATA, CLUB_BDL_ST_BUKI, TKWN_BDL_TN_KEN1, SPEAR_BDL_MO_YARI, PGSW_BDL_BPG_KEN1};

    u32 type = fopAcM_GetParam(this);
    if (type >= Type_COUNT_e) {
        JUT_ASSERT(DEMO_SELECT(1702, 1740), FALSE);
    }

    u32 unused = type == Type_PGANON_SWORD_e;

    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes(m_arc_name[type], model_idx[type]));
    JUT_ASSERT(DEMO_SELECT(1708, 1746), modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);
    if (mpModel == NULL) {
        return FALSE;
    }

    if (type == 4) {
        mpLineKe = new LineKe();
        if (mpLineKe == NULL) {
            return FALSE;
        }

        if (!mpLineKe->lineMat.init(0x10, 10, 0)) {
            return FALSE;
        }
    } else if (type == 5 &&
               !mBrkAnm.init(
                   modelData,
                   static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes("Pgsw", PGSW_BRK_KIERU_KEN1)),
                   true, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, false, FALSE
               ))
    {
        return FALSE;
    }

    return TRUE;
}

/* 00002DE4-00003154       .text create__8daBoko_cFv */
cPhs_State daBoko_c::create() {
    static dCcD_SrcSph sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_UNK20000,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_GrpAll_e,
            /* SrcObjTg  Type    */ AT_TYPE_WATER | AT_TYPE_FIRE | AT_TYPE_UNK20000,
            /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_None_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK0,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ dCcG_AtSPrm_NoHitMark_e,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 20.0f,
        }},
    };
    static dCcD_SrcCps at_cps_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ AT_TYPE_BOKO_STICK,
            /* SrcObjAt  Atp     */ 1,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e | cCcD_AtSPrm_VsOther_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ 0,
            /* SrcGObjAt Se      */ 0,
            /* SrcGObjAt HitMark */ dCcG_AtHitMark_Big_e,
            /* SrcGObjAt Spl     */ dCcG_At_Spl_UNK1,
            /* SrcGObjAt Mtrl    */ 0,
            /* SrcGObjAt SPrm    */ 0,
            /* SrcGObjTg Se      */ 0,
            /* SrcGObjTg HitMark */ 0,
            /* SrcGObjTg Spl     */ dCcG_Tg_Spl_UNK0,
            /* SrcGObjTg Mtrl    */ 0,
            /* SrcGObjTg SPrm    */ 0,
            /* SrcGObjCo SPrm    */ 0,
        },
        // cM3dGCpsS
        {{
            /* P0 */ {0.0f, 0.0f, 0.0f},
            /* P1 */ {0.0f, 0.0f, 0.0f},
            /* Height */ 20.0f,
        }},
    };

    fopAcM_SetupActor(this, daBoko_c);

    u32 type = fopAcM_GetParam(this);
    if (type == Type_UNK_7_e) {
        type = Type_BOKO_STICK_e;
        fopAcM_SetParam(this, type);
        fopAcM_SetCullSize(this, fopAc_CULLSPHERE_6_e);
        mFlameTimer = 900;
    }

    cPhs_State PVar5 = dComIfG_resLoad(&mPhase, m_arc_name[type]);
    if (PVar5 == cPhs_COMPLEATE_e) {
        if (type >= Type_COUNT_e) {
            return cPhs_ERROR_e;
        }

        if (!fopAcM_entrySolidHeap(this, daBoko_createHeap, m_heap_size[type])) {
            return cPhs_ERROR_e;
        }

        if (mpModel == NULL) {
            return cPhs_ERROR_e;
        }

        mpModel->setBaseScale(scale);
        fopAcM_SetMtx(this, mpModel->getBaseTRMtx());

        Vec* min = &m_cull_min[type];
        fopAcM_SetMin(this, min->x, min->y, min->z);
        Vec* max = &m_cull_max[type];
        fopAcM_SetMax(this, max->x, max->y, max->z);

        mAcchCir.SetWall(10.0f, 60.0f);
        mAcch.Set(
            fopAcM_GetPosition_p(this),
            fopAcM_GetOldPosition_p(this),
            this,
            1,
            &mAcchCir,
            fopAcM_GetSpeed_p(this),
            fopAcM_GetAngle_p(this),
            fopAcM_GetShapeAngle_p(this)
        );

        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_ACTION_CARRY_e);
        attention_info.distances[fopAc_Attn_TYPE_CARRY_e] = 0x11;
        fopAcM_SetGravity(this, -3.0f);
        fopAcM_SetMaxFallSpeed(this, -100.0f);
        mStts.Init(10, 0xff, this);

        if (type == Type_BOKO_STICK_e) {
            mpModel->getModelData()->getJointNodePointer(2)->getMesh()->getShape()->hide();
        }
        mSph.Set(sph_src);
        mSph.SetStts(&mStts);
        mCps.Set(at_cps_src);
        mCps.SetStts(&mStts);
        mCps.SetAtType(getAtType());
        mCps.SetAtAtp(getAtPoint());
        mCps.SetAtSe(getSeType());
        mCps.SetR(getCpsR());

        mCurrentProc = &daBoko_c::procWait;

        setBaseMatrix();
        setTopRootPos(0);

        if (mFlameTimer != 0) {
            m7E4 = 1.0f;
            setFlameEffect();
        }

        mAcch.ClrRoofNone();
        mAcch.SetRoofCrrHeight(30.0f);
        m_line_check.ClrSttsRoofOff();

        mpModel->calc();

        if (type == Type_BOKO_STICK_e) {
            dKy_plight_set(&mLight);
            mLight.mColor.r = 600;
            mLight.mColor.g = 400;
            mLight.mColor.b = 0x78;
            mLight.mPower = m7E4 * 150.0f;
            mLight.mFluctuation = 250.0f;
        }

        fopAcM_SetModel(this, mpModel);
        m2F4 = current.pos;
    }
    return PVar5;
}

/* 00003154-000032F0       .text __ct__8daBoko_cFv */
daBoko_c::daBoko_c() {
}

/* 00003824-00003844       .text daBoko_Create__FP10fopAc_ac_c */
static cPhs_State daBoko_Create(fopAc_ac_c* i_this) {
    return static_cast<daBoko_c*>(i_this)->create();
}

static actor_method_class l_daBoko_Method = {
    (process_method_func)daBoko_Create,
    (process_method_func)daBoko_Delete,
    (process_method_func)daBoko_Execute,
    (process_method_func)daBoko_IsDelete,
    (process_method_func)daBoko_Draw,
};

actor_process_profile_definition g_profile_BOKO = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0009,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_BOKO,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daBoko_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_BOKO,
    /* Actor SubMtd */ &l_daBoko_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK4000_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
