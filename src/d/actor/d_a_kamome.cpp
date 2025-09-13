/**
 * d_a_kamome.cpp
 * NPC - Seagull
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_kamome.h"
#include "d/actor/d_a_esa.h"
#include "d/actor/d_a_sea.h"
#include "d/res/res_kamome.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_snap.h"
#include "d/d_priority.h"
#include "d/d_com_inf_game.h"
#include "d/d_s_play.h"
#include "d/d_kankyo.h"
#include "f_op/f_op_actor_mng.h"

class kamomeHIO_c : public JORReflexible {
public:
    kamomeHIO_c() {
        m05 = 0;
        m06 = 1;
        m08 = 8;
        m0C = 400.0f;
        m10 = 300.0f;
    }
    virtual ~kamomeHIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 m05;
    /* 0x06 */ s16 m06;
    /* 0x08 */ s16 m08;
    /* 0x0C */ f32 m0C;
    /* 0x10 */ f32 m10;
}; // size = 0x14

static bool hio_set;
static kamomeHIO_c l_kamomeHIO;
static esa_class* esa_info[100];
static s32 esa_check_count;
static s32 ko_count;

/* 000000EC-000001E4       .text anm_init__FP12kamome_classifUcfi */
void anm_init(kamome_class* i_this, int anmResIdx, float morf, unsigned char loopMode, float speed, int soundAnmResIdx) {
    if (REG0_S(3) == 0x23) {
        anmResIdx = KAMOME_BCK_KA_LAND1;
    } else if (REG0_S(3) == 0x24) {
        anmResIdx = KAMOME_BCK_KA_FLY1;
    }
    i_this->mpMorf->setAnm(
        (J3DAnmTransform*)dComIfG_getObjectRes("Kamome", anmResIdx), loopMode, morf, speed, 0.0f, -1.0f, dComIfG_getObjectRes("Kamome", soundAnmResIdx)
    );
}

/* 000001E4-000004B8       .text s_a_d_sub__FPvPv */
void* s_a_d_sub(void* ac1, void* ac2) {
    dBgS_LinChk linChk;
    fopAc_ac_c* actor2 = (fopAc_ac_c*)ac2;

    if ((esa_check_count < 100) && fopAc_IsActor(ac1) && fpcM_GetName(ac1) == PROC_ESA) {
        esa_class* esa = (esa_class*)ac1;
        if (esa->field_0x298 == 0) {
            cXyz sp14;
            cXyz sp08;

            sp08 = esa->current.pos;
            sp08.y += 10.0f;
            sp14 = actor2->current.pos;

            linChk.Set(&sp14, &sp08, actor2);
            if (!dComIfG_Bgsp()->LineCross(&linChk)) {
                esa_info[esa_check_count] = esa;
                esa_check_count++;
            }
        }
    }
    return NULL;
}

/* 000008F0-00000A44       .text search_esa__FP12kamome_class */
fopAc_ac_c* search_esa(kamome_class* i_this) {
    esa_check_count = 0;
    fpcM_Search(s_a_d_sub, &i_this->actor);

    if (esa_check_count != 0) {
        f32 fVar3 = 50.0f;
        s32 i = 0;
        while (i < esa_check_count) {
            esa_class* esa = esa_info[i];
            f32 x = esa->current.pos.x - i_this->actor.current.pos.x;
            f32 z = esa->current.pos.z - i_this->actor.current.pos.z;
            if (std::sqrtf(SQUARE(x) + SQUARE(z)) < fVar3) {
                esa->field_0x298 = 1;
                return esa;
            }

            i++;
            if (i == esa_check_count) {
                i = 0;
                fVar3 += 50.0f;
                if (fVar3 > 10000.0f) {
                    return NULL;
                }
            }
        }
    }
    return NULL;
}

/* 00000A44-00000A90       .text s_a_i_sub__FPvPv */
void* s_a_i_sub(void* ac1, void* ac2) {
    if (fopAc_IsActor(ac1) && fpcM_GetName(ac1) == PROC_NPC_LS1) {
        return ac1;
    }
    return NULL;
}

/* 00000A90-00000ABC       .text search_imouto__FP12kamome_class */
fopAc_ac_c* search_imouto(kamome_class* i_this) {
    return (fopAc_ac_c*)fpcM_Search(s_a_i_sub, &i_this->actor);
}

/* 00000ABC-00000B84       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == 0) {
        J3DJoint* joint = (J3DJoint*)node;
        s32 uVar1 = joint->getJntNo();
        J3DModel* pJVar2 = j3dSys.getModel();
        kamome_class* pKamome = (kamome_class*)pJVar2->getUserArea();
        if (pKamome != NULL) {
            MTXCopy(pJVar2->getAnmMtx(uVar1), *calc_mtx);
            cMtx_YrotM(*calc_mtx, pKamome->mJointRotY);
            cMtx_ZrotM(*calc_mtx, pKamome->mJointRotZ);
            pJVar2->setAnmMtx(uVar1, *calc_mtx);
            MTXCopy(*calc_mtx, J3DSys::mCurrentMtx);
        }
    }
    return TRUE;
}

/* 00000B84-00000CAC       .text daKamome_Draw__FP12kamome_class */
static BOOL daKamome_Draw(kamome_class* i_this) {
    if ((i_this->mSwitchNo != 0) || (i_this->mbNoDraw != 0)) {
#if VERSION <= VERSION_JPN
        i_this->mbNoDraw = 0;
#endif
        return TRUE;
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &i_this->actor.current.pos, &i_this->actor.tevStr);
    g_env_light.setLightTevColorType(i_this->mpMorf->getModel(), &i_this->actor.tevStr);
    i_this->mpMorf->entryDL();

    cXyz sp08(i_this->actor.current.pos.x, i_this->actor.current.pos.y + REG0_F(1) * 10.0f, i_this->actor.current.pos.z);

    i_this->mShadowId = dComIfGd_setShadow(
        i_this->mShadowId,
        1,
        i_this->mpMorf->getModel(),
        &sp08,
        REG0_F(2) * 10.0f + 500.0f,
        20.0f,
        sp08.y,
        i_this->mAcch.GetGroundH(),
        i_this->mAcch.m_gnd,
        &i_this->actor.tevStr
    );

    dSnap_RegistFig(0x55, &i_this->actor, 1.0f, 1.0f, 1.0f);
    return TRUE;
}

/* 00000CAC-00000F70       .text kamome_pos_move__FP12kamome_class */
void kamome_pos_move(kamome_class* i_this) {
    f32 fVar4 = i_this->mTargetPos.x - i_this->actor.current.pos.x;
    f32 fVar1 = i_this->mTargetPos.y - i_this->actor.current.pos.y;
    f32 fVar5 = i_this->mTargetPos.z - i_this->actor.current.pos.z;
    s16 rotTargetY = cM_atan2s(fVar4, fVar5);
    s16 rotTargetX = -cM_atan2s(fVar1, std::sqrtf(SQUARE(fVar4) + SQUARE(fVar5)));
    s16 sVar3 = i_this->actor.current.angle.y;
    cLib_addCalcAngleS2(&i_this->actor.current.angle.y, rotTargetY, REG0_S(3) + 10, i_this->mRotVel * i_this->mRotVelFade);
    sVar3 = (sVar3 - i_this->actor.current.angle.y) * 0x20;

    s16 rotTargetZ = REG0_S(1) + 5500;
    if (sVar3 > rotTargetZ) {
        sVar3 = rotTargetZ;
    } else if (sVar3 < -rotTargetZ) {
        sVar3 = -rotTargetZ;
    }

    cLib_addCalcAngleS2(&i_this->actor.current.angle.z, sVar3, REG0_S(3) + 10, i_this->mRotVel * i_this->mRotVelFade * 0.5f);
    cLib_addCalcAngleS2(&i_this->actor.current.angle.x, rotTargetX, REG0_S(3) + 10, i_this->mRotVel * i_this->mRotVelFade);
    cLib_addCalc2(&i_this->mRotVelFade, 1.0f, 1.0f, 0.04f);
    cLib_addCalc2(&(i_this->actor).speedF, i_this->mVelocityFwdTarget, 1.0f, i_this->mVelocityFwdTargetMaxVel);
    cXyz fwd;
    fwd.x = 0.0f;
    fwd.y = 0.0f;
    fwd.z = i_this->actor.speedF;
    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x);
    MtxPosition(&fwd, &i_this->actor.speed);
    i_this->actor.current.pos.x += i_this->actor.speed.x;
    i_this->actor.current.pos.y += i_this->actor.speed.y;
    i_this->actor.current.pos.z += i_this->actor.speed.z;

    if (i_this->mRiseTimer != 0) {
        i_this->mRiseTimer--;
        i_this->actor.current.pos.y += 5.0f;
    }
}

/* 00000F70-00000FFC       .text kamome_bgcheck__FP12kamome_class */
void kamome_bgcheck(kamome_class* i_this) {
    f32 fVar1 = i_this->mScale * 40.0f;
    i_this->actor.current.pos.y = i_this->actor.current.pos.y - fVar1;
    i_this->actor.old.pos.y = i_this->actor.old.pos.y - fVar1;
    i_this->mAcch.CrrPos(*dComIfG_Bgsp());
    i_this->actor.current.pos.y = i_this->actor.current.pos.y + fVar1;
    i_this->actor.old.pos.y = i_this->actor.old.pos.y + fVar1;
}

/* 00000FFC-00001150       .text kamome_ground_pos_move__FP12kamome_class */
void kamome_ground_pos_move(kamome_class* i_this) {
    s16 iVar2 = cM_atan2s(i_this->mTargetPos.x - i_this->actor.current.pos.x, i_this->mTargetPos.z - i_this->actor.current.pos.z);

    cLib_addCalcAngleS2(&i_this->actor.current.angle.y, iVar2, REG0_S(3) + 2, i_this->mRotVel * i_this->mRotVelFade);
    cLib_addCalc2(&i_this->mRotVelFade, 1.0f, 1.0f, 0.1f);
    cLib_addCalc2(&i_this->actor.speedF, i_this->mVelocityFwdTarget, 1.0f, i_this->mVelocityFwdTargetMaxVel);

    cXyz sp14;
    sp14.x = 0.0f;
    sp14.y = 0.0f;
    sp14.z = i_this->actor.speedF;
    cMtx_YrotS(*calc_mtx, i_this->actor.current.angle.y);

    cXyz sp08;
    MtxPosition(&sp14, &sp08);
    i_this->actor.speed.x = sp08.x;
    i_this->actor.speed.z = sp08.z;

    i_this->actor.current.pos.x += i_this->actor.speed.x;
    i_this->actor.current.pos.y += i_this->actor.speed.y;
    i_this->actor.current.pos.z += i_this->actor.speed.z;

    i_this->actor.speed.y -= 3.0f;
    kamome_bgcheck(i_this);

    if (i_this->mAcch.ChkGroundHit()) {
        i_this->actor.speed.y = -0.5f;
    }
}

/* 00001150-000011B8       .text ko_s_sub__FPvPv */
void* ko_s_sub(void* ac1, void* ac2) {
    kamome_class* i_this = (kamome_class*)ac1;
    if (fopAcM_IsActor(&i_this->actor) && fopAcM_GetName(&i_this->actor) == PROC_KAMOME && (fopAcM_GetParam(&i_this->actor) & 0xf) == 7) {
        ko_count++;
    }
    return NULL;
}

/* 000011B8-000011FC       .text ko_check__FP12kamome_class */
s32 ko_check(kamome_class* i_this) {
    ko_count = 0;
    fpcM_Search(ko_s_sub, &i_this->actor);
    return ko_count;
}

/* 000011FC-00001304       .text heisou_control__FP12kamome_class */
void heisou_control(kamome_class* i_this) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    i_this->mbNoDraw = 1;
#if VERSION > VERSION_DEMO
    if (dComIfGs_getTime() >= 90.0f && dComIfGs_getTime() <= 270.0f && dKy_rain_check() < 10)
#endif
    {
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && (i_this->mGlobalTimer & 0x7f) == 0) {
            s32 ko = ko_check(i_this);
            if (ko < i_this->mKoMaxCount) {
                cXyz sp08 = player->current.pos;
                sp08.y += 4000.0f;
                fopAcM_create(PROC_KAMOME, ko << 8 | 0xffff0007, &sp08, fopAcM_GetRoomNo(&i_this->actor));
            }
        }
    }
}

/* 00001304-00001360       .text h_s_sub__FPvPv */
void* h_s_sub(void* ac1, void* ac2) {
    kamome_class* i_this = (kamome_class*)ac1;
    if (fopAcM_IsActor(&i_this->actor) && fopAcM_GetName(&i_this->actor) == PROC_KAMOME && (fopAcM_GetParam(&i_this->actor) & 0xf) == 6) {
        return &i_this->actor;
    }
    return NULL;
}

/* 00001360-000013BC       .text search_master__FP12kamome_class */
BOOL search_master(kamome_class* i_this) {
    kamome_class* pvVar1 = (kamome_class*)fpcM_Search(h_s_sub, &i_this->actor);
    if (pvVar1 != NULL && (s32)i_this->mKoMaxCount < pvVar1->mKoMaxCount) {
        return TRUE;
    }
    return FALSE;
}

/* 000013BC-00001A0C       .text kamome_heisou_move__FP12kamome_class */
void kamome_heisou_move(kamome_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    s32 frame;

    switch (i_this->mAnimState) {
    case 0:
        frame = i_this->mpMorf->getFrame();
        if ((i_this->mTimers[0] == 0) && (frame == REG0_S(0) + 9)) {
            i_this->mAnimState = 1;
            anm_init(i_this, KAMOME_BCK_KA_WAIT1, REG0_F(0) + 12.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT1);
        }
        break;

    case 1:
        if ((i_this->mGlobalTimer & 0x3fU) == 0 && cM_rndF(1.0f) < 0.5f) {
            i_this->mGlobalTimer = (s16)cM_rndF(10000.0f);
            i_this->mAnimState = 2;
            anm_init(i_this, KAMOME_BCK_KA_SING1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, 0);
        } else if ((i_this->mTimers[0] == 0) && (a_this->current.pos.y < i_this->mTargetPos.y)) {
            i_this->mAnimState = 0;
            i_this->mTimers[0] = cM_rndF(60.0f) + 20.0f;
            anm_init(i_this, KAMOME_BCK_KA_WAIT2, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT2);
        }
        break;

    case 2:
        frame = i_this->mpMorf->getFrame();
        if (frame == 8) {
            fopAcM_seStart(a_this, JA_SE_CV_KAMOME, 0);
        }

        if (i_this->mpMorf->isStop()) {
            i_this->mAnimState = 1;
            anm_init(i_this, KAMOME_BCK_KA_WAIT1, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT1);
        }
        break;
    }

    i_this->m2B4++;

    switch (i_this->mMoveState) {
    case 0:
        cXyz sp44;
        sp44.x = (REG17_F(5) + 300.0f) * cM_ssin(i_this->m2B4 * (REG17_S(5) + 200));
        sp44.y = i_this->m2B8 + 600.0f + REG17_F(6);
        sp44.z = (REG17_F(4) + 150.0f) + (REG17_F(7) + 300.0f) * cM_ssin(i_this->m2B4 * (REG17_S(6) + 30));
        cMtx_YrotS(*calc_mtx, player->shape_angle.y);
        cXyz sp34;
        MtxPosition(&sp44, &sp34);
        i_this->mTargetPos.x = sp34.x + player->current.pos.x;
        i_this->mTargetPos.z = sp34.z + player->current.pos.z;
        if (daSea_ChkArea(i_this->mTargetPos.x, i_this->mTargetPos.z)) {
            i_this->mTargetPos.y = sp34.y + daSea_calcWave(i_this->mTargetPos.x, i_this->mTargetPos.z);
        } else {
            i_this->mTargetPos.y = player->current.pos.y + sp34.y;
        }
        break;
    }

    BOOL iVar2;
#if VERSION == VERSION_DEMO
    if (!dComIfGp_att_chkEnemySound() && dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
        iVar2 = search_master(i_this);
    } else {
        iVar2 = FALSE;
    }
#else
    if (dComIfGs_getTime() >= 90.0f && dComIfGs_getTime() <= 270.0f && dKy_rain_check() < 10 && !dComIfGp_att_chkEnemySound() &&
        dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e))
    {
        iVar2 = search_master(i_this);
    } else {
        iVar2 = FALSE;
    }
#endif

    cXyz sp28 = player->old.pos - player->current.pos;
    f32 fVar6;
    i_this->mVelocityFwdTarget = (REG17_F(8) + 1.2f) * sp28.abs();
    if ((i_this->mVelocityFwdTarget > REG17_F(13) + 30.0f) && iVar2) {
        fVar6 = 0.0f;
        sp28 = i_this->mTargetPos - a_this->current.pos;
        if (sp28.abs() < REG17_F(9) + 200.0f) {
            i_this->mVelocityFwdTarget = 0.0f;
        }
    } else {
        i_this->mVelocityFwdTarget = 20.0f;
        fVar6 = a_this->home.pos.y;
    }

    cLib_addCalc2(&i_this->m2B8, fVar6, 1.0f, 20.0f);
    i_this->mVelocityFwdTargetMaxVel = REG17_F(10) + 0.25f;
    i_this->mRotVel = REG17_F(11) + 300.0f;
    kamome_pos_move(i_this);
    i_this->mJointRotYTarget = fopAcM_searchPlayerAngleY(a_this) - a_this->current.angle.y;

    s16 sVar3 = REG17_S(3) + 5000;
    if (i_this->mJointRotYTarget > sVar3) {
        i_this->mJointRotYTarget = sVar3;
    } else if (i_this->mJointRotYTarget < (s16)-sVar3) {
        i_this->mJointRotYTarget = -sVar3;
    }

    if (a_this->current.pos.y > 3000.0f) {
        i_this->mbNoDraw = 1;
    }
}

/* 00001A0C-00002740       .text kamome_path_move__FP12kamome_class */
void kamome_path_move(kamome_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    s8 moveType = 0;
    s32 frame;
    dPnt* pdVar8;
    s32 nextID;
    f32 x;
    f32 y;
    f32 z;
    f32 sqrt;

    switch (i_this->mAnimState) {
    case 0:
        frame = i_this->mpMorf->getFrame();
        if ((a_this->current.pos.y > i_this->mTargetPos.y) && (frame == REG0_S(0) + 9)) {
            i_this->mAnimState = 1;
            i_this->mTimers[0] = cM_rndF(200.0f) + 50.0f;
            anm_init(i_this, KAMOME_BCK_KA_WAIT1, REG0_F(0) + 12.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT1);
        }
        break;

    case 1:
        if (((i_this->mGlobalTimer & 0x3f) == 0) && cM_rndF(1.0) < 0.5f) {
            i_this->mGlobalTimer = (s16)cM_rndF(10000.0f);
            i_this->mAnimState = 2;
            anm_init(i_this, KAMOME_BCK_KA_SING1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, 0);
        } else if (a_this->current.pos.y <= i_this->mTargetPos.y) {
            i_this->mAnimState = 0;
            anm_init(i_this, KAMOME_BCK_KA_WAIT2, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT2);
        }
        break;

    case 2:
        frame = i_this->mpMorf->getFrame();
        if (frame == 8) {
            fopAcM_seStart(a_this, JA_SE_CV_KAMOME, 0);
        }

        if (i_this->mpMorf->isStop()) {
            i_this->mAnimState = 1;
            i_this->mTimers[0] = cM_rndF(100.0f) + 20.0f;
            anm_init(i_this, KAMOME_BCK_KA_WAIT1, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT1);
        }
        break;

    case 3:
        break;

    case 19:
        if (i_this->mpMorf->isStop()) {
            i_this->mAnimState = 0;
            anm_init(i_this, KAMOME_BCK_KA_WAIT2, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT2);
        }
        break;

    case 20:
        break;
    }

    switch (i_this->mMoveState) {
    case 0:
        i_this->mCurPointIdx += i_this->mPathIdxIncr;
        if (i_this->mCurPointIdx >= (s8)i_this->mpPath->m_num) {
            if (dPath_ChkClose(i_this->mpPath)) {
                i_this->mCurPointIdx = 0;
            } else {
                i_this->mPathIdxIncr = -1;
                i_this->mCurPointIdx = i_this->mpPath->m_num - 2;
            }

            nextID = i_this->mpPath->m_nextID;
            if (nextID != 0xFFFF) {
                i_this->mpPath = dComIfGp_getStage().getPathInf()->m_path;
                i_this->mpPath += nextID;
            }
        } else if ((s8)i_this->mCurPointIdx < 0) {
            i_this->mPathIdxIncr = 1;
            i_this->mCurPointIdx = 1;
        }

    case -1:
        i_this->mMoveState = 1;
        pdVar8 = i_this->mpPath->m_points;
        pdVar8 += i_this->mCurPointIdx;
        if (i_this->m308 != 0) {
            i_this->mVelocityFwdTarget = 25.0f;
            i_this->mVelocityFwdTargetMaxVel = 2.0f;
            i_this->m308 = 0;
        } else if (a_this->current.pos.y < i_this->mTargetPos.y) {
            i_this->mVelocityFwdTarget = cM_rndF(5.0f) + 20.0f;
            i_this->mVelocityFwdTargetMaxVel = REG0_F(11) + 1.0f;
        } else {
            i_this->mVelocityFwdTarget = cM_rndF(5.0f) + 30.0f;
            i_this->mVelocityFwdTargetMaxVel = REG0_F(13) + 1.0f;
        }
        i_this->mRotVelFade = REG0_F(7);
        if (pdVar8->mArg3 == 1) {
            i_this->mMoveState = 10;
            i_this->mTargetPos = pdVar8->m_position;
        } else {
            i_this->mTargetPos.x = pdVar8->m_position.x + cM_rndFX(150.0f);
            i_this->mTargetPos.y = pdVar8->m_position.y + cM_rndFX(150.0f);
            i_this->mTargetPos.z = pdVar8->m_position.z + cM_rndFX(150.0f);
        }

        if (i_this->mTimers[3] == 0) {
            fopAc_ac_c* iVar5 = search_esa(i_this);
            if (iVar5 != NULL) {
                i_this->mEsaProcID = fopAcM_GetID(iVar5);
                i_this->mMoveState = 10;
                i_this->mRotVel = 1000.0;
                i_this->mbUsePathMovement = 0;
            }
        }
        break;

    case 1:
        cLib_addCalc2(&i_this->mRotVelFade, 1.0f, 1.0f, 0.04f);
        x = i_this->mTargetPos.x - a_this->current.pos.x;
        y = i_this->mTargetPos.y - a_this->current.pos.y;
        z = i_this->mTargetPos.z - a_this->current.pos.z;
        sqrt = std::sqrtf(SQUARE(x) + SQUARE(y) + SQUARE(z));
        i_this->mRotVel = REG0_F(5) * 10.0f + 100.0f + (REG0_F(6) * 1000.0f + 500000.0f) / sqrt;
        if (i_this->mRotVel > REG0_F(4) * 10.0f + 5000.0f) {
            i_this->mRotVel = REG0_F(4) * 10.0f + 5000.0f;
        }

        if (sqrt < REG0_F(10) * 10.0f + 300.0f) {
            i_this->mMoveState = 0;
            if (i_this->mpPath->m_points[i_this->mCurPointIdx].mArg3 == 6) {
                fopAcM_delete(a_this);
            }
        }
        break;

    case 10:
        i_this->mVelocityFwdTarget = 20.0f;
        x = i_this->mTargetPos.x - a_this->current.pos.x;
        y = (i_this->mTargetPos.y + 50.0f + REG6_F(8) * 10.0f) - a_this->current.pos.y;
        z = i_this->mTargetPos.z - a_this->current.pos.z;

        if (std::sqrtf(SQUARE(x) + SQUARE(y) + SQUARE(z)) < REG6_F(9) * 10.0f + 300.0f) {
            i_this->mMoveState = 0x14;
            anm_init(i_this, KAMOME_BCK_KA_LAND1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, KAMOME_BAS_KA_LAND1);
            i_this->mAnimState = 10;
            a_this->speed.y = 0.0f;
            i_this->m2FC = a_this->current.angle.y + (s16)cM_rndFX(15000.0f);
            i_this->mTimers[2] = 0x3c;
            moveType = -1;
        }
        break;

    case 0x14:
        moveType = -1;
        frame = i_this->mpMorf->getFrame();
        a_this->current.pos.y += a_this->speed.y;
        if (frame > REG6_S(2) + 0xf) {
            a_this->speed.y -= REG6_F(7) + 0.8f;
            cLib_addCalcAngleS2(&a_this->current.angle.y, i_this->m2FC, 2, 1000);
        }
        cLib_addCalcAngleS2(&a_this->current.angle.x, 0, 5, 0x800);
        cLib_addCalcAngleS2(&a_this->current.angle.z, 0, 5, 0x800);
        kamome_bgcheck(i_this);

        if (i_this->mAcch.ChkGroundHit()) {
            a_this->speed.y = -0.5f;
        } else {
            cLib_addCalc2(&a_this->current.pos.x, i_this->mTargetPos.x, 0.1f, std::fabsf(a_this->speed.x));
            cLib_addCalc2(&a_this->current.pos.z, i_this->mTargetPos.z, 0.1f, std::fabsf(a_this->speed.z));
        }

        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, KAMOME_BCK_KA_WAIT3, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 0);
        }

        if (i_this->mTimers[2] == 0) {
            i_this->mMoveState = 0x17;
        }
        break;

    case 0x16:
        moveType = 1;
        i_this->m2AB = 1;
        if (i_this->mTimers[2] == 0) {
            i_this->mCurPointIdx += i_this->mPathIdxIncr;
            if (i_this->mCurPointIdx >= (s8)i_this->mpPath->m_num) {
                if (dPath_ChkClose(i_this->mpPath)) {
                    i_this->mCurPointIdx = 0;
                } else {
                    i_this->mPathIdxIncr = -1;
                    i_this->mCurPointIdx = i_this->mpPath->m_num - 2;
                }

                nextID = i_this->mpPath->m_nextID;
                if (nextID != 0xFFFF) {
                    i_this->mpPath = dComIfGp_getStage().getPathInf()->m_path;
                    i_this->mpPath += nextID;
                }
            } else if (i_this->mCurPointIdx < 0) {
                i_this->mPathIdxIncr = 1;
                i_this->mCurPointIdx = 1;
            }
            pdVar8 = &i_this->mpPath->m_points[i_this->mCurPointIdx];
            i_this->mTargetPos = pdVar8->m_position;
            if (pdVar8->mArg3 == 2) {
                i_this->mMoveState = 0x19;
                anm_init(i_this, KAMOME_BCK_KA_FLY1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, KAMOME_BAS_KA_FLY1);
            } else {
                i_this->mMoveState = 0x17;
                i_this->mRotVel = 2500.0f;
                i_this->mRotVelFade = 1.0f;
                anm_init(i_this, KAMOME_BCK_KA_MOVE1, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_MOVE1);
            }
        }
        i_this->mVelocityFwdTarget = 0.0f;
        a_this->speedF = 0.0f;
        break;

    case 0x13:
        moveType = 1;
        if (i_this->mpMorf->isStop()) {
            i_this->mMoveState = 0x16;
        }
        i_this->mVelocityFwdTarget = 0.0f;
        a_this->speedF = 0.0f;
        break;

    case 0x17:
        moveType = 1;
        frame = i_this->mpMorf->getFrame();
        if ((frame >= l_kamomeHIO.m06) && (frame <= l_kamomeHIO.m08)) {
            i_this->mVelocityFwdTarget = i_this->mScale * 5.0f;
            a_this->speedF = i_this->mScale * 5.0f;
        } else {
            i_this->mVelocityFwdTarget = 0.0f;
            a_this->speedF = 0.0f;
            x = i_this->mTargetPos.x - a_this->current.pos.x;
            z = i_this->mTargetPos.z - a_this->current.pos.z;
            if (std::sqrtf(SQUARE(x) + SQUARE(z)) < 50.0f) {
                pdVar8 = i_this->mpPath->m_points;
                pdVar8 += i_this->mCurPointIdx;
                if (cM_rndF(1.0f) < 0.5f) {
                    i_this->mMoveState = 0x13;
                    anm_init(i_this, KAMOME_BCK_KA_SING2, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, 0);
                } else {
                    i_this->mMoveState = 0x16;
                    if (pdVar8->mArg3 == 3) {
                        anm_init(i_this, KAMOME_BCK_KA_WAIT3, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 0);
                        i_this->mTimers[2] = cM_rndF(50.0f) + 50.0f;
                    }
                }
            }
        }
        break;

    case 0x19:
        moveType = 1;
        a_this->speed.y = 0.0f;
        frame = i_this->mpMorf->getFrame();
        if (frame < 5) {
            i_this->mVelocityFwdTarget = 0.0f;
            i_this->mVelocityFwdTargetMaxVel = 1.0f;
        } else {
            i_this->mMoveState = 0xff;
            i_this->mRotVel = REG0_F(4) * 10.0f + 5000.0f;
            i_this->mVelocityFwdTarget = 25.0f;
            i_this->mVelocityFwdTargetMaxVel = 2.0f;
            a_this->speedF = 0.0f;
            i_this->mAnimState = 0x14;
            i_this->mRiseTimer = REG0_S(4) + 10;
        }
    }

    switch (moveType) {
    case 0:
        kamome_pos_move(i_this);
        break;

    case 1:
        kamome_ground_pos_move(i_this);
        break;
    }
}

/* 00002740-00003628       .text kamome_auto_move__FP12kamome_class */
void kamome_auto_move(kamome_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    fopAc_ac_c* pfVar4;
    s8 moveType = 0;
    s32 frame;
    cXyz sp30;
    f32 x;
    f32 y;
    f32 z;

    switch (i_this->mAnimState) {
    case 0:
        frame = i_this->mpMorf->getFrame();
        if ((i_this->mTimers[0] == 0) && (frame == REG0_S(0) + 9)) {
            i_this->mAnimState = 1;
            anm_init(i_this, KAMOME_BCK_KA_WAIT1, REG0_F(0) + 12.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT1);
        }
        break;

    case 1:
        if ((i_this->mGlobalTimer & 0x3f) == 0 && cM_rndF(1.0) < 0.5f) {
            i_this->mGlobalTimer = (s16)cM_rndF(10000.0f);
            i_this->mAnimState = 2;
            anm_init(i_this, KAMOME_BCK_KA_SING1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, 0);
        } else if ((i_this->mTimers[0] == 0) && (a_this->current.pos.y < i_this->mTargetPos.y)) {
            i_this->mAnimState = 0;
            i_this->mTimers[0] = cM_rndF(60.0f) + 20.0f;
            anm_init(i_this, KAMOME_BCK_KA_WAIT2, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT2);
        }
        break;

    case 2:
        frame = i_this->mpMorf->getFrame();
        if (frame == 8) {
            fopAcM_seStart(a_this, JA_SE_CV_KAMOME, 0);
        }

        if (i_this->mpMorf->isStop()) {
            i_this->mAnimState = 1;
            anm_init(i_this, KAMOME_BCK_KA_WAIT1, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT1);
        }
        break;

    case 3:
        break;

    case 19:
        if (i_this->mpMorf->isStop()) {
            i_this->mAnimState = 0;
            i_this->mTimers[0] = cM_rndF(60.0f) + 20.0f;
            anm_init(i_this, KAMOME_BCK_KA_WAIT2, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT2);
        }

    case 20:
        break;
    }

    switch (i_this->mMoveState) {
    case 0:
        if (i_this->mTimers[1] == 0) {
            x = (a_this->home.pos.x + cM_rndFX(1000.0f)) - a_this->current.pos.x;
            z = (a_this->home.pos.z + cM_rndFX(1000.0f)) - a_this->current.pos.z;
            if (std::sqrtf(SQUARE(x) + SQUARE(z)) > 200.0f) {
                i_this->mTimers[1] = cM_rndF(150.0f) + 50.0f;
                i_this->mTargetPos.x = x + a_this->current.pos.x;
                i_this->mTargetPos.y = a_this->home.pos.y + cM_rndF(500.0f);
                i_this->mTargetPos.z = z + a_this->current.pos.z;
                i_this->mRotVelFade = 0.0f;

                if (a_this->current.pos.y < i_this->mTargetPos.y) {
                    i_this->mVelocityFwdTarget = REG0_F(10) + 20.0f;
                    i_this->mVelocityFwdTargetMaxVel = REG0_F(11) + 0.2f;
                } else {
                    i_this->mVelocityFwdTarget = REG0_F(12) + 36.0f;
                    i_this->mVelocityFwdTargetMaxVel = REG0_F(13) + 0.5f;
                }

                i_this->mRotVel = cM_rndF(300.0f) + 200.0f;

                if (i_this->mTimers[3] == 0) {
                    fopAc_ac_c* iVar3 = search_esa(i_this);
                    if (iVar3 != NULL) {
                        i_this->mEsaProcID = fopAcM_GetID(iVar3);
                        i_this->mMoveState = 10;
                        i_this->mRotVel = 1000.0;
                    }
                }
            }
        }
        break;

    case 10:
        pfVar4 = fopAcM_SearchByID(i_this->mEsaProcID);
        if (pfVar4 != NULL) {
            sp30.x = 0.0f;
            sp30.y = 0.0f;
            sp30.z = REG6_F(16) * 10.0f + -100.0f;
            cMtx_YrotS(*calc_mtx, a_this->current.angle.y);
            cXyz sp24;
            MtxPosition(&sp30, &sp24);
            i_this->mTargetPos.x = pfVar4->current.pos.x + sp24.x;
            i_this->mTargetPos.y = pfVar4->current.pos.y + 80.0f + REG6_F(8) * 10.0f;
            i_this->mTargetPos.z = pfVar4->current.pos.z + sp24.z;
            i_this->mVelocityFwdTarget = 20.0f;
            x = i_this->mTargetPos.x - a_this->current.pos.x;
            y = i_this->mTargetPos.y - a_this->current.pos.y;
            z = i_this->mTargetPos.z - a_this->current.pos.z;
            if (std::sqrtf(SQUARE(x) + SQUARE(y) + SQUARE(z)) < REG6_F(9) * 10.0f + 300.0f) {
                i_this->mMoveState = 0x14;
                anm_init(i_this, KAMOME_BCK_KA_LAND1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, KAMOME_BAS_KA_LAND1);
                i_this->mAnimState = 10;
                a_this->speed.y = 0.0f;
                i_this->m2FC = a_this->current.angle.y + (s16)cM_rndFX(15000.0f);
                i_this->mTimers[2] = 0x3c;
                moveType = -1;
            }
        } else {
            i_this->mMoveState = 0;
        }
        break;

    case 0x14:
        moveType = -1;
        frame = i_this->mpMorf->getFrame();
        a_this->current.pos.y += a_this->speed.y;
        if (frame > REG6_S(2) + 0xf) {
            a_this->speed.y -= REG6_F(7) + 0.8f;
            cLib_addCalcAngleS2(&a_this->current.angle.y, i_this->m2FC, 2, 1000);
        }
        cLib_addCalcAngleS2(&a_this->current.angle.x, 0, 5, 0x800);
        cLib_addCalcAngleS2(&a_this->current.angle.z, 0, 5, 0x800);
        kamome_bgcheck(i_this);

        if (i_this->mAcch.ChkGroundHit()) {
            a_this->speed.y = -1.0f;
        } else {
            cLib_addCalc2(&a_this->current.pos.x, i_this->mTargetPos.x, 0.1f, std::fabsf(a_this->speed.x));
            cLib_addCalc2(&a_this->current.pos.z, i_this->mTargetPos.z, 0.1f, std::fabsf(a_this->speed.z));
        }

        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, KAMOME_BCK_KA_WAIT3, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 0);
        }

        if (i_this->mTimers[2] == 0) {
            i_this->mMoveState = 0x16;
        }
        break;

    case 0x15:
        moveType = 1;
        pfVar4 = search_esa(i_this);
        if (pfVar4 == NULL) {
            i_this->mMoveState = 0x19;
            anm_init(i_this, KAMOME_BCK_KA_FLY1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, KAMOME_BAS_KA_FLY1);
        } else {
            i_this->mEsaProcID = fopAcM_GetID(pfVar4);
            i_this->mMoveState = 0x16;
        }
        break;

    case 0x16:
        moveType = 1;
        i_this->mVelocityFwdTarget = 0.0f;
        (i_this->actor).speedF = 0.0f;
        i_this->mRotVel = 0.0f;
        if (i_this->mTimers[2] == 0) {
            i_this->mMoveState = 0x17;
            pfVar4 = fopAcM_SearchByID(i_this->mEsaProcID);
            if (pfVar4 != NULL) {
                i_this->mTargetPos.x = pfVar4->current.pos.x;
                i_this->mTargetPos.z = pfVar4->current.pos.z;
                anm_init(i_this, KAMOME_BCK_KA_MOVE1, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_MOVE1);
            } else {
                i_this->mMoveState = 0x19;
                anm_init(i_this, KAMOME_BCK_KA_FLY1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, KAMOME_BAS_KA_FLY1);
            }
        }
        break;

    case 0x13:
        moveType = 1;
        if (i_this->mpMorf->isStop()) {
            i_this->mMoveState = 0x15;
            i_this->mTimers[2] = cM_rndF(30.0f) + 20.0f;
            anm_init(i_this, KAMOME_BCK_KA_WAIT3, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 0);
        }
        i_this->mVelocityFwdTarget = 0.0f;
        a_this->speedF = 0.0f;
        break;

    case 0x17:
        moveType = 1;
        i_this->m2AB = 1;
        frame = i_this->mpMorf->getFrame();
        if ((frame >= l_kamomeHIO.m06) && (frame <= l_kamomeHIO.m08)) {
            i_this->mVelocityFwdTarget = i_this->mScale * 5.0f;
            a_this->speedF = i_this->mScale * 5.0f;
            i_this->mRotVel = 4000.0f;
            i_this->mRotVelFade = 1.0f;
        } else {
            i_this->mVelocityFwdTarget = 0.0f;
            a_this->speedF = 0.0f;
            i_this->mRotVel = 0.0f;
            x = i_this->mTargetPos.x - a_this->current.pos.x;
            z = i_this->mTargetPos.z - a_this->current.pos.z;
            if (std::sqrtf(SQUARE(x) + SQUARE(z)) < 85.0f) {
                anm_init(i_this, KAMOME_BCK_KA_EAT1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, 0);
                i_this->mMoveState = 0x18;
            }

            if (i_this->mAcch.ChkWallHit()) {
                i_this->mMoveState = 0x19;
                anm_init(i_this, KAMOME_BCK_KA_FLY1, 0.0f, J3DFrameCtrl::EMode_NONE, 1.0f, KAMOME_BAS_KA_FLY1);
            }
        }
        break;

    case 0x18:
        moveType = 1;
        i_this->mVelocityFwdTarget = 0.0f;
        a_this->speedF = 0.0f;
        frame = i_this->mpMorf->getFrame();
        if (frame == 9) {
            pfVar4 = fopAcM_SearchByID(i_this->mEsaProcID);
            if (pfVar4 != NULL) {
                fopAcM_delete(pfVar4);
            }
        }

        if (i_this->mpMorf->isStop()) {
            if (cM_rndF(1.0f) < 0.2f) {
                i_this->mMoveState = 0x13;
                anm_init(i_this, KAMOME_BCK_KA_SING2, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, 0);
            } else {
                i_this->mMoveState = 0x15;
                i_this->mTimers[2] = cM_rndF(20.0f);
                anm_init(i_this, KAMOME_BCK_KA_WAIT3, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 0);
            }
        }
        break;

    case 0x19:
        moveType = 1;
        a_this->speed.y = 0.0f;
        frame = i_this->mpMorf->getFrame();
        if (frame < 5) {
            i_this->mVelocityFwdTarget = 0.0f;
            i_this->mVelocityFwdTargetMaxVel = 1.0f;
        } else {
            i_this->mMoveState = 0;
            i_this->mAnimState = 0x14;
            i_this->mTimers[3] = cM_rndF(100.0f) + 100.0f;
            i_this->mRiseTimer = REG0_S(4) + 10;
            if (i_this->mPathIdx != 0xff) {
                i_this->mbUsePathMovement = i_this->mPathIdx + 1;
                i_this->m308 = 1;
            } else {
                i_this->mTimers[1] = 0x32;
                i_this->mRotVel = REG0_F(4) * 10.0f + 1000.0f;
                i_this->mVelocityFwdTarget = 25.0f;
                i_this->mVelocityFwdTargetMaxVel = 2.0f;
                a_this->speedF = 0.0f;
                MtxTrans(a_this->current.pos.x, a_this->current.pos.y, a_this->current.pos.z, 0);
                sp30.set(0.0f, 1000.0f, 2000.0f);
                cMtx_YrotM(*calc_mtx, a_this->current.angle.y);
                MtxPosition(&sp30, &i_this->mTargetPos);
            }
        }
    }

    switch (moveType) {
    case 0:
        kamome_pos_move(i_this);
        break;

    case 1:
        kamome_ground_pos_move(i_this);
        if (i_this->mMoveState != 0x19) {
            if (a_this->current.pos.y - i_this->mAcch.GetGroundH() > 200.0f || fopAcM_searchPlayerDistance(a_this) < l_kamomeHIO.m0C) {
                i_this->mMoveState = 0;
                esa_class* pfVar5 = (esa_class*)fopAcM_SearchByID(i_this->mEsaProcID);
                if (pfVar5 != NULL) {
                    pfVar5->field_0x298 = 0;
                }
                i_this->mAnimState = 0;
                i_this->mTimers[0] = cM_rndF(60.0f) + 20.0f;
                anm_init(i_this, KAMOME_BCK_KA_WAIT2, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.5f, KAMOME_BAS_KA_WAIT2);
                if (i_this->mPathIdx != 0xff) {
                    i_this->mbUsePathMovement = i_this->mPathIdx + 1;
                    i_this->mTimers[3] = cM_rndF(250.0f) + 250.0f;
                    i_this->m308 = 1;
                } else {
                    i_this->mTimers[1] = 0x32;
                    i_this->mRotVel = REG0_F(4) * 10.0f + 5000.0f;
                    i_this->mVelocityFwdTarget = 30.0f;
                    i_this->mVelocityFwdTargetMaxVel = 3.0f;
                    a_this->speedF = 0.0f;
                    MtxTrans(a_this->current.pos.x, a_this->current.pos.y, a_this->current.pos.z, 0);
                    sp30.set(0.0f, 1000.0f, 2000.0f);
                    cMtx_YrotM(*calc_mtx, a_this->current.angle.y);
                    MtxPosition(&sp30, &i_this->mTargetPos);
                    i_this->mTimers[3] = cM_rndF(250.0f) + 250.0f;
                }
            }
        }
        break;
    }
}

/* 00003628-00004574       .text kamome_imouto_move__FP12kamome_class */
void kamome_imouto_move(kamome_class* i_this) {
    fopAc_ac_c* a_this = (fopAc_ac_c*)&i_this->actor;
    fopAc_ac_c* player = (fopAc_ac_c*)dComIfGp_getPlayer(0);
    s8 cVar8 = 0;
    s32 frame;
    cXyz sp34;

    switch (i_this->mAnimState) {
    case 0:
        frame = i_this->mpMorf->getFrame();
        if ((i_this->mTimers[0] == 0) && (frame == REG0_S(0) + 9)) {
            i_this->mAnimState = 1;
            anm_init(i_this, KAMOME_BCK_KA_WAIT1, REG0_F(0) + 12.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT1);
        }
        break;

    case 1:
        if ((i_this->mGlobalTimer & 0x3f) == 0 && (cM_rndF(1.0f) < 0.5f)) {
            i_this->mGlobalTimer = (s16)cM_rndF(10000.0f);
            i_this->mAnimState = 2;
            anm_init(i_this, KAMOME_BCK_KA_SING1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, 0);
        } else if ((i_this->mTimers[0] == 0) && (a_this->current.pos.y < i_this->mTargetPos.y)) {
            i_this->mAnimState = 0;
            i_this->mTimers[0] = cM_rndF(60.0f) + 20.0f;
            anm_init(i_this, KAMOME_BCK_KA_WAIT2, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_WAIT2);
        }
        break;

    case 2:
        frame = i_this->mpMorf->getFrame();
        if (frame == 8) {
            fopAcM_seStart(a_this, JA_SE_CV_KAMOME, 0);
        }

        if (i_this->mpMorf->isStop()) {
            i_this->mAnimState = 1;
            anm_init(i_this, KAMOME_BCK_KA_WAIT1, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 8);
        }
        break;

    case 3:
        break;

    case 19:
        if (i_this->mpMorf->isStop()) {
            i_this->mAnimState = 0;
            i_this->mTimers[0] = cM_rndF(60.0f) + 20.0f;
            anm_init(i_this, KAMOME_BCK_KA_WAIT2, 0.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 9);
        }
        break;
    case 20:
        break;
    }

    switch (i_this->mMoveState) {
    case 0:
        if (i_this->mTimers[1] == 0) {
            f32 fVar11 = (a_this->home.pos.x + cM_rndFX(1000.0f)) - a_this->current.pos.x;
            f32 fVar9 = (a_this->home.pos.z + cM_rndFX(1000.0f)) - a_this->current.pos.z;
            if (std::sqrtf(SQUARE(fVar11) + SQUARE(fVar9)) > 200.0f) {
                i_this->mTimers[1] = cM_rndF(150.0f) + 50.0f;
                i_this->mTargetPos.x = fVar11 + a_this->current.pos.x;
                i_this->mTargetPos.y = a_this->home.pos.y + cM_rndF(500.0f);
                i_this->mTargetPos.z = fVar9 + a_this->current.pos.z;
                i_this->mRotVelFade = 0.0f;

                if (a_this->current.pos.y < i_this->mTargetPos.y) {
                    i_this->mVelocityFwdTarget = REG0_F(10) + 20.0f;
                    i_this->mVelocityFwdTargetMaxVel = REG0_F(11) + 0.2f;
                } else {
                    i_this->mVelocityFwdTarget = REG0_F(12) + 36.0f;
                    i_this->mVelocityFwdTargetMaxVel = REG0_F(13) + 0.5f;
                }

                i_this->mRotVel = cM_rndF(300.0f) + 200.0f;

                if (i_this->mTimers[3] == 0) {
                    i_this->mpTargetActor = search_imouto(i_this);
                    if (i_this->mpTargetActor != NULL) {
                        sp34 = player->current.pos - i_this->mpTargetActor->current.pos;
                        if (sp34.abs() < l_kamomeHIO.m10) {
                            i_this->mTimers[3] = 0x32;
                            i_this->mpTargetActor = NULL;
                        } else {
                            i_this->mMoveState = 10;
                            i_this->mRotVel = 1000.0f;
                            i_this->mTargetPos.x = i_this->mpTargetActor->current.pos.x + cM_rndFX(150.0f);
                            i_this->mTargetPos.y = i_this->mpTargetActor->current.pos.y + 80.0f;
                            i_this->mTargetPos.z = i_this->mpTargetActor->current.pos.z + cM_rndFX(150.0f);
                        }
                    }
                }
            }
        }
        break;

    case 10:
        sp34 = player->current.pos - i_this->mTargetPos;
        if (sp34.abs() < l_kamomeHIO.m10) {
            i_this->mMoveState = 0;
            i_this->mTimers[3] = 0x32;
        } else {
            i_this->mVelocityFwdTarget = 20.0f;
            f32 fVar11 = i_this->mTargetPos.x - a_this->current.pos.x;
            f32 fVar9 = i_this->mTargetPos.y - a_this->current.pos.y;
            f32 fVar10 = i_this->mTargetPos.z - a_this->current.pos.z;
            if (std::sqrtf(SQUARE(fVar11) + SQUARE(fVar9) + SQUARE(fVar10)) < REG6_F(9) * 10.0f + 300.0f) {
                i_this->mMoveState = 0x14;
                anm_init(i_this, KAMOME_BCK_KA_LAND1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, KAMOME_BAS_KA_LAND1);
                i_this->mAnimState = 10;
                a_this->speed.y = 0.0f;
                i_this->m2FC = a_this->current.angle.y + (s32)cM_rndFX(15000.0f);
                i_this->mTimers[2] = 0x3c;
                cVar8 = -1;
            }
        }
        break;

    case 0x14:
        cVar8 = -1;
        frame = i_this->mpMorf->getFrame();
        a_this->current.pos.y += a_this->speed.y;
        if (frame > REG6_S(2) + 0xf) {
            a_this->speed.y -= REG6_F(7) + 0.8f;
            cLib_addCalcAngleS2(&a_this->current.angle.y, i_this->m2FC, 2, 1000);
        }

        cLib_addCalcAngleS2(&(i_this->actor).current.angle.x, 0, 5, 0x800);
        cLib_addCalcAngleS2(&(i_this->actor).current.angle.z, 0, 5, 0x800);
        kamome_bgcheck(i_this);

        if (i_this->mAcch.ChkGroundHit()) {
            a_this->speed.y = -1.0f;
        } else {
            cLib_addCalc2(&a_this->current.pos.x, i_this->mTargetPos.x, 0.1f, std::fabsf(a_this->speed.x));
            cLib_addCalc2(&a_this->current.pos.z, i_this->mTargetPos.z, 0.1f, std::fabsf(a_this->speed.z));
        }

        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, KAMOME_BCK_KA_WAIT3, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 0);
        }

        if (i_this->mTimers[2] == 0) {
            i_this->mMoveState = 0x16;
        }
        break;

    case 0x15:
        cVar8 = 1;
        i_this->mMoveState = 0x16;
        break;

    case 0x16:
        cVar8 = 1;
        i_this->m2AB = 1;
        i_this->mVelocityFwdTarget = 0.0f;
        a_this->speedF = 0.0f;
        i_this->mRotVel = 0.0f;

        if (i_this->mTimers[2] == 0) {
            i_this->mMoveState = 0x17;
            i_this->mTargetPos.x = i_this->mpTargetActor->current.pos.x + cM_rndFX(REG0_F(8) + 150.0f);
            i_this->mTargetPos.z = i_this->mpTargetActor->current.pos.z + cM_rndFX(REG0_F(8) + 150.0f);
            anm_init(i_this, KAMOME_BCK_KA_MOVE1, 3.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, KAMOME_BAS_KA_MOVE1);
        }
        break;

    case 0x13:
        cVar8 = 1;
        if (i_this->mpMorf->isStop()) {
            i_this->mMoveState = 0x15;
            i_this->mTimers[2] = cM_rndF(30.0f) + 20.0f;
            anm_init(i_this, KAMOME_BCK_KA_WAIT3, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 0);
        }
        i_this->mVelocityFwdTarget = 0.0f;
        a_this->speedF = 0.0f;
        break;

    case 0x17:
        cVar8 = 1;
        frame = i_this->mpMorf->getFrame();
        if ((frame >= l_kamomeHIO.m06) && (frame <= l_kamomeHIO.m08)) {
            i_this->mVelocityFwdTarget = i_this->mScale * 5.0f;
            a_this->speedF = i_this->mScale * 5.0f;
            i_this->mRotVel = 4000.0f;
            i_this->mRotVelFade = 1.0f;
        } else {
            i_this->mVelocityFwdTarget = 0.0f;
            a_this->speedF = 0.0f;
            i_this->mRotVel = 0.0f;
            f32 fVar11 = i_this->mTargetPos.x - a_this->current.pos.x;
            f32 fVar9 = i_this->mTargetPos.z - a_this->current.pos.z;
            if ((std::sqrtf(SQUARE(fVar11) + SQUARE(fVar9)) < 85.0f) || ((i_this->mAcch.ChkWallHit()) || i_this->mSph.ChkCoHit())) {
                anm_init(i_this, KAMOME_BCK_KA_EAT1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, 0);
                i_this->mMoveState = 0x18;
            }
        }
        break;

    case 0x18:
        cVar8 = 1;
        i_this->mVelocityFwdTarget = 0.0f;
        a_this->speedF = 0.0f;
        if (i_this->mpMorf->isStop()) {
            if (cM_rndF(1.0f) < 0.2f) {
                i_this->mMoveState = 0x13;
                anm_init(i_this, KAMOME_BCK_KA_SING2, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, 0);
            } else {
                i_this->mMoveState = 0x15;
                i_this->mTimers[2] = cM_rndF(20.0f);
                anm_init(i_this, KAMOME_BCK_KA_WAIT3, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 0);
            }
        }
        break;

    case 0x19:
        cVar8 = 1;
        a_this->speed.y = 0.0f;
        frame = i_this->mpMorf->getFrame();
        if (frame < 5) {
            i_this->mVelocityFwdTarget = 0.0f;
            i_this->mVelocityFwdTargetMaxVel = 1.0f;
        } else {
            i_this->mMoveState = 0;
            i_this->mAnimState = 0x14;
            i_this->mTimers[3] = cM_rndF(100.0f) + 100.0f;
            i_this->mRiseTimer = REG0_S(4) + 10;
            if (i_this->mPathIdx != 0xff) {
                i_this->mbUsePathMovement = i_this->mPathIdx + 1;
                i_this->m308 = 1;
            } else {
                i_this->mTimers[1] = 0x32;
                i_this->mRotVel = REG0_F(4) * 10.0f + 1000.0f;
                i_this->mVelocityFwdTarget = 25.0f;
                i_this->mVelocityFwdTargetMaxVel = 2.0f;
                a_this->speedF = 0.0f;
                MtxTrans(a_this->current.pos.x, a_this->current.pos.y, a_this->current.pos.z, 0);
                sp34.set(0.0f, 1000.0f, 2000.0f);
                cMtx_YrotM(*calc_mtx, a_this->current.angle.y);
                MtxPosition(&sp34, &i_this->mTargetPos);
            }
        }
    }

    switch (cVar8) {
    case 0:
        kamome_pos_move(i_this);
        break;

    case 1:
        kamome_ground_pos_move(i_this);
        if ((i_this->mMoveState != 0x19) &&
            (a_this->current.pos.y - i_this->mAcch.GetGroundH() > 200.0f || fopAcM_searchPlayerDistance(a_this) < l_kamomeHIO.m10))
        {
            i_this->mMoveState = 0;
            i_this->mAnimState = 0;
            i_this->mTimers[0] = cM_rndF(60.0f) + 20.0f;
            anm_init(i_this, KAMOME_BCK_KA_WAIT2, 3.0, J3DFrameCtrl::EMode_LOOP, 1.5f, KAMOME_BAS_KA_WAIT2);

            if (i_this->mPathIdx != 0xff) {
                i_this->mbUsePathMovement = i_this->mPathIdx + 1;
                i_this->mTimers[3] = cM_rndF(250.0f) + 250.0f;
                i_this->m308 = 1;
            } else {
                i_this->mTimers[1] = 0x32;
                i_this->mRotVel = REG0_F(4) * 10.0f + 5000.0f;
                i_this->mVelocityFwdTarget = 30.0f;
                i_this->mVelocityFwdTargetMaxVel = 3.0f;
                a_this->speedF = 0.0f;
                MtxTrans(a_this->current.pos.x, a_this->current.pos.y, a_this->current.pos.z, 0);
                sp34.set(0.0f, 1000.0f, 2000.0f);
                cMtx_YrotM(*calc_mtx, a_this->current.angle.y);
                MtxPosition(&sp34, &i_this->mTargetPos);
                i_this->mTimers[3] = cM_rndF(250.0f) + 250.0f;
            }
        }
    }

    cXyz* moveP = i_this->mStts.GetCCMoveP();
    if (moveP != NULL) {
        a_this->current.pos += *moveP;
    }

    i_this->mSph.SetC(a_this->current.pos);
    i_this->mSph.SetR(REG17_F(18) + 40.0f);
    dComIfG_Ccsp()->Set(&i_this->mSph);
}

/* 00004574-00004680       .text kamome_imouto2_move__FP12kamome_class */
void kamome_imouto2_move(kamome_class* i_this) {
    switch (i_this->mMoveState) {
    case 0:
        i_this->m2AB = 1;
        if (i_this->mTimers[1] == 0) {
            anm_init(i_this, KAMOME_BCK_KA_EAT1, 5.0f, J3DFrameCtrl::EMode_NONE, 1.0f, 0);
            i_this->mMoveState++;
        }
        break;

    case 1:
        if (i_this->mpMorf->isStop()) {
            anm_init(i_this, KAMOME_BCK_KA_WAIT3, 5.0f, J3DFrameCtrl::EMode_LOOP, 1.0f, 0);
            i_this->mTimers[1] = cM_rndF(50.0f) + 50.0f;
            i_this->mMoveState--;
        }
        break;
    }
}

/* 00004680-00004768       .text daKamome_setMtx__FP12kamome_class */
void daKamome_setMtx(kamome_class* i_this) {
    MtxTrans(i_this->actor.current.pos.x, i_this->actor.current.pos.y, i_this->actor.current.pos.z, 0);

    cMtx_YrotM(*calc_mtx, i_this->actor.current.angle.y + i_this->mRotY);
    cMtx_XrotM(*calc_mtx, i_this->actor.current.angle.x + i_this->mRotX);
    cMtx_ZrotM(*calc_mtx, i_this->actor.current.angle.z);

    J3DModel* pJVar1 = i_this->mpMorf->getModel();
    pJVar1->setBaseTRMtx(*calc_mtx);
    pJVar1->getModelData()->getJointNodePointer(8)->setCallBack(nodeCallBack);
    i_this->mpMorf->calc();
    pJVar1->getModelData()->getJointNodePointer(8)->setCallBack(NULL);
}

/* 00004768-000049F8       .text daKamome_Execute__FP12kamome_class */
static BOOL daKamome_Execute(kamome_class* i_this) {
    i_this->mGlobalTimer++;
#if VERSION > VERSION_JPN
    i_this->mbNoDraw = 0;
#endif

    if (i_this->mType == 6) {
        heisou_control(i_this);
        return TRUE;
    }

    if (i_this->mSwitchNo != 0) {
        if (dComIfGs_isSwitch(i_this->mSwitchNo - 1, fopAcM_GetRoomNo(&i_this->actor))) {
            i_this->mSwitchNo = 0;
            anm_init(i_this, KAMOME_BCK_KA_WAIT2, 1.0f, J3DFrameCtrl::EMode_LOOP, cM_rndF(0.5f) + 1.0f, KAMOME_BAS_KA_WAIT2);
            i_this->mTimers[0] = cM_rndF(60.0f) + 40.0f;
            i_this->mVelocityFwdTarget = 30.0f;
            i_this->actor.speedF = 30.0f;
        } else {
            return TRUE;
        }
    }

    if (l_kamomeHIO.m05 == 0) {
        for (s32 i = 0; i < ARRAY_SSIZE(i_this->mTimers); i++) {
            if (i_this->mTimers[i] != 0) {
                i_this->mTimers[i]--;
            }
        }

        if (i_this->mbUsePathMovement != 0) {
            kamome_path_move(i_this);
        } else if (i_this->mType == 4) {
            kamome_imouto_move(i_this);
        } else if (i_this->mType == 5) {
            kamome_imouto2_move(i_this);
        } else if (i_this->mType == 7) {
            kamome_heisou_move(i_this);
        } else {
            kamome_auto_move(i_this);
        }

        i_this->mpMorf->play(&i_this->actor.eyePos, 0, 0);
        cLib_addCalcAngleS2(&i_this->mJointRotY, i_this->mJointRotYTarget, 4, 0x800);
        cLib_addCalcAngleS2(&i_this->mJointRotZ, i_this->mJointRotZTarget, 4, 0x800);

        if (i_this->m2AB != 0) {
            if (i_this->mTimers[5] == 0) {
                i_this->mTimers[5] = cM_rndF(20.0) + 10.0f;
                i_this->mJointRotYTarget = cM_rndFX(REG0_F(8) + 3000.0f);
                i_this->mJointRotZTarget = cM_rndFX(REG0_F(8) + 3000.0f);
            }
            i_this->m2AB = 0;
        } else {
            i_this->mJointRotZTarget = 0;
            i_this->mJointRotYTarget = 0;
        }
    }

    daKamome_setMtx(i_this);

    i_this->actor.eyePos = i_this->actor.current.pos;
    return TRUE;
}

/* 000049F8-00004A00       .text daKamome_IsDelete__FP12kamome_class */
static BOOL daKamome_IsDelete(kamome_class*) {
    return TRUE;
}

/* 00004A00-00004A70       .text daKamome_Delete__FP12kamome_class */
static BOOL daKamome_Delete(kamome_class* i_this) {
    dComIfG_resDeleteDemo(&i_this->mPhase, "Kamome");
    if (i_this->m688 != 0) {
        hio_set = false;
        mDoHIO_deleteChild(l_kamomeHIO.mNo);
    }
    return TRUE;
}

/* 00004A70-00004B94       .text createHeap__FP10fopAc_ac_c */
static BOOL createHeap(fopAc_ac_c* a_this) {
    kamome_class* i_this = (kamome_class*)a_this;

    i_this->mpMorf = new mDoExt_McaMorf(
        (J3DModelData*)dComIfG_getObjectRes("Kamome", KAMOME_BDL_KA),
        NULL,
        NULL,
        (J3DAnmTransform*)dComIfG_getObjectRes("Kamome", KAMOME_BCK_KA_WAIT1),
        J3DFrameCtrl::EMode_LOOP,
        1.0f,
        0,
        -1,
        1,
        dComIfG_getObjectRes("Kamome", KAMOME_BAS_KA_WAIT1),
        0x80000,
        0x11000022
    );
    if (i_this->mpMorf == NULL || i_this->mpMorf->getModel() == NULL) {
        return FALSE;
    }

    i_this->mpMorf->getModel()->setUserArea((u32)&i_this->actor);
    return TRUE;
}

/* 00004B94-00004F84       .text daKamome_Create__FP10fopAc_ac_c */
static cPhs_State daKamome_Create(fopAc_ac_c* a_this) {
    static dCcD_SrcSph co_sph_src = {
        // dCcD_SrcGObjInf
        {
            /* Flags             */ 0,
            /* SrcObjAt  Type    */ 0,
            /* SrcObjAt  Atp     */ 0,
            /* SrcObjAt  SPrm    */ cCcD_AtSPrm_Set_e | cCcD_AtSPrm_VsEnemy_e,
            /* SrcObjTg  Type    */ 0,
            /* SrcObjTg  SPrm    */ 0,
            /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsPlayer_e | cCcD_CoSPrm_VsGrpAll_e,
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
        // cM3dGSphS
        {{
            /* Center */ {0.0f, 0.0f, 0.0f},
            /* Radius */ 40.0f,
        }},
    };

    kamome_class* i_this = (kamome_class*)a_this;

#if VERSION == VERSION_DEMO
    cPhs_State PVar1 = dComIfG_resLoad(&i_this->mPhase, "Kamome");
    if (PVar1 == cPhs_COMPLEATE_e) {
        fopAcM_SetupActor(a_this, kamome_class);
#else
    fopAcM_SetupActor(a_this, kamome_class);

    cPhs_State PVar1 = dComIfG_resLoad(&i_this->mPhase, "Kamome");
    if (PVar1 == cPhs_COMPLEATE_e) {
#endif

        i_this->mType = fopAcM_GetParam(a_this);
        if (i_this->mType == 0xff) {
            i_this->mType = 0;
        }

        i_this->mKoMaxCount = fopAcM_GetParam(a_this) >> 8;
        i_this->mPathIdx = fopAcM_GetParam(a_this) >> 0x10;
        i_this->mSwitchNoPrm = fopAcM_GetParam(a_this) >> 0x18;

        if (!fopAcM_entrySolidHeap(a_this, createHeap, DEMO_SELECT(0x59A0, 0x1360))) {
            return cPhs_ERROR_e;
        }

        if (i_this->mPathIdx != 0xff) {
            i_this->mpPath = dPath_GetRoomPath(i_this->mPathIdx, fopAcM_GetRoomNo(a_this));
            if (i_this->mpPath == NULL) {
                return cPhs_ERROR_e;
            }
            i_this->mPathIdxIncr = 1;
            i_this->mbUsePathMovement = i_this->mPathIdx + 1;
            i_this->mPathIdxIncr = 1;
        }

        if (i_this->mSwitchNoPrm != 0xff) {
            i_this->mSwitchNo = i_this->mSwitchNoPrm + 1;
        }

        fopAcM_SetMtx(a_this, i_this->mpMorf->getModel()->getBaseTRMtx());
        f32 tmp = REG0_F(2) + 1.0f;
        f32 fVar6 = REG0_F(3) + 1.0f;
        i_this->mScale = fVar6 + cM_rndF(tmp - fVar6);
        if ((i_this->mType == 4) || (i_this->mType == 5)) {
            i_this->mScale = i_this->mScale * (REG0_F(9) + 0.75f);
        }

        cXyz sp10;
        sp10.set(i_this->mScale, i_this->mScale, i_this->mScale);
        i_this->mpMorf->getModel()->setBaseScale(sp10);
        daKamome_setMtx(i_this);
        i_this->mAcch.Set(fopAcM_GetPosition_p(a_this), fopAcM_GetOldPosition_p(a_this), a_this, 1, &i_this->mAcchCir, fopAcM_GetSpeed_p(a_this));

        if ((i_this->mType == 4) || (i_this->mType == 5)) {
            i_this->mAcchCir.SetWall(50.0f, 80.0f);
        } else {
            i_this->mAcchCir.SetWall(30.0f, 20.0f);
        }

        if (i_this->mType == 4) {
            i_this->mStts.Init(0x32, 0xff, a_this);
            i_this->mSph.Set(co_sph_src);
            i_this->mSph.SetStts(&i_this->mStts);
        }

        i_this->mGlobalTimer = (s16)cM_rndF(10000.0f);

        if (!hio_set) {
            l_kamomeHIO.mNo = mDoHIO_createChild("カモメ", &l_kamomeHIO);
            i_this->m688 = 1;
            hio_set = true;
        }

        if ((i_this->mType != 6) && (i_this->mType == 7)) {
            i_this->m2B4 = cM_rndF(10000.0f);
            fopAcM_setStageLayer(a_this);
            fopAcM_SetRoomNo(a_this, 0xff);
        }
    }
    return PVar1;
}

static actor_method_class l_daKamome_Method = {
    (process_method_func)daKamome_Create,
    (process_method_func)daKamome_Delete,
    (process_method_func)daKamome_Execute,
    (process_method_func)daKamome_IsDelete,
    (process_method_func)daKamome_Draw,
};

actor_process_profile_definition g_profile_KAMOME = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_KAMOME,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(kamome_class),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_KAMOME,
    /* Actor SubMtd */ &l_daKamome_Method,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_0_e,
};
