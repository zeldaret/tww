/**
 * d_a_obj_ikada.cpp
 * Object - Various Great Sea ships (Beedle, Submarines, Skull Platforms/Rafts, and Salvage Corp.)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_obj_ikada.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_majuu_flag.h"
#include "d/actor/d_a_player.h"
#include "d/d_bg_s_movebg_actor.h"
#include "d/d_cc_d.h"
#include "d/d_com_inf_game.h"
#include "d/d_lib.h"
#include "d/d_priority.h"
#include "d/d_procname.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/res/res_always.h"
#include "d/res/res_ikadah.h"
#include "d/res/res_link.h"
#include "f_op/f_op_actor_mng.h"
#include "f_op/f_op_kankyo_mng.h"

cXyz daObj_Ikada_c::m_rope_base_vec(0.0f, -10.0f, 0.0f);
cXyz daObj_Ikada_c::m_crane_offset(200.0f, -340.0f, 0.0f);
static daObj_Ikada_HIO_c l_HIO;

const u32 daObj_Ikada_c::m_heapsize[] = {0x1D00, 0x2F60, 0x2E20, 0x32E0, 0x6D60};
const char daObj_Ikada_c::m_arc_name[] = "IkadaH";
const f32 daObj_Ikada_c::m_rope_joint_len = 10.0f;
const s32 daObj_Ikada_c::m_rope_min_cnt = 15;

const dCcD_SrcSph daObj_Ikada_c::m_sph_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
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
        /* Radius */ 75.0f,
    }},
};

/* 000000EC-00000254       .text __ct__17daObj_Ikada_HIO_cFv */
daObj_Ikada_HIO_c::daObj_Ikada_HIO_c() {
    mbDebugDraw = 0;
    m05 = 0;
    m06 = 0;
    mbNoRotAnim = 0;
    m08 = 0;
    mShipOffsY_Attention = 900.0f;
    mShipOffsY_Eye = 300.0f;
    mSvWaveOffsX = -320.0f;
    mSvTrackOffsX = 240.0f;
    mTerryWaveOffsZ = 660.0f;
    mTerryWaveOffsY = 20.0f;
    mTerryTrackOffsZ = -180.0f;
    m24 = 0x3c;
    mSvOffsX[0] = 265.0f;
    mSvOffsX[1] = -18.0f;
    mSvOffsX[2] = -97.0f;
    mSvOffsX[3] = -175.0f;
    mFlagScale = 0.0f;
    mFlagOffset.x = 0.0f;
    mFlagOffset.y = 0.0f;
    mFlagOffset.z = 0.0f;
    m1C = 0;
    m20 = 1.5f;
    m1E = 100;
    m28 = 100.0f;
    mTrackIndTransY = -0.04;
    mTrackIndScaleY = 4.0f;
    mSplashScaleMax = 200.0f;
    mSplashMaxScaleTimer = 300.0f;
    mWaveVelFade = 2.0f;
    mTrackVel = 300.0f;
    mWaveVelSpeed = 2.0f;
    mWaveMaxVelocity = 15.0f;
    mWaveVelOffs = 0.0f;
    mWaveCollapsePos[0].x = -80.0f;
    mWaveCollapsePos[0].y = -50.0f;
    mWaveCollapsePos[0].z = -150.0f;
    mWaveCollapsePos[1].x = -40.0f;
    mWaveCollapsePos[1].y = -100.0f;
    mWaveCollapsePos[1].z = -350.0f;
    m94 = 3000;
    mPlayerStopDistance = 6000;
    m98 = 1000;
    m9A = 1000;
    m9C = 300.0f;
    mVelocityTargetTerry1 = 12.0f;
    mVelocityTargetTerry3 = 15.0f;
    mA8 = 30.0f;
}

/* 000002D8-00000324       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* node, int arg1) {
    J3DJoint* joint = (J3DJoint*)node;
    if (arg1 == 0) {
        daObj_Ikada_c* i_this = (daObj_Ikada_c*)j3dSys.getModel()->getUserArea();
        if (i_this != NULL) {
            i_this->_nodeControl(joint, j3dSys.getModel());
        }
    }
    return TRUE;
}

/* 00000324-00000458       .text _nodeControl__13daObj_Ikada_cFP7J3DNodeP8J3DModel */
void daObj_Ikada_c::_nodeControl(J3DNode* node, J3DModel* model) {
    J3DJoint* joint = (J3DJoint*)node;
    s32 uVar1 = joint->getJntNo();
    mDoMtx_stack_c::copy(model->getAnmMtx(uVar1));
    mDoMtx_stack_c::ZXYrotM(mJointRot[uVar1].x, mJointRot[uVar1].y, mJointRot[uVar1].z);
    if (uVar1 == 1) {
        mDoMtx_stack_c::XrotM(m115A + m115E * (REG12_S(5) + 5) * cM_ssin(m115C));
    }
    MTXCopy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
    model->setAnmMtx(uVar1, mDoMtx_stack_c::get());
}

/* 00000458-00000494       .text pathMove_CB__FP4cXyzP4cXyzP4cXyzPv */
BOOL pathMove_CB(cXyz* arg1, cXyz* arg2, cXyz* arg3, void* v_this) {
    return ((daObj_Ikada_c*)v_this)->_pathMove(arg1, arg2, arg3);
}

/* 00000494-000007A0       .text _pathMove__13daObj_Ikada_cFP4cXyzP4cXyzP4cXyz */
BOOL daObj_Ikada_c::_pathMove(cXyz* arg1, cXyz* arg2, cXyz* arg3) {
    s8 index;
    if (mCurPathPoint < mpPath->m_num - 1) {
        index = mCurPathPoint + 1;
    } else {
        index = 0;
    }

    if (mpPath->m_points[index].mArg3 != 0xff) {
        mbCraneMode = 1;
    } else {
        mbCraneMode = 0;
    }

    mCurPathP0 = *arg2;
    mCurPathP0.y = current.pos.y;
    mCurPathP1 = *arg3;
    mCurPathP1.y = current.pos.y;

    cXyz sp4C = mCurPathP1 - mCurPathP0;
    if (!sp4C.normalizeRS()) {
        return TRUE;
    }

    s16 uVar3 = cLib_addCalcAngleS(&current.angle.y, cM_atan2s(sp4C.x, sp4C.z), 8, 0x200, 8);
    f32 speed = speedF * std::fabsf(cM_scos(uVar3));
    cLib_chasePosXZ(arg1, mCurPathP1, speed);

    if ((*arg1 - mCurPathP1).absXZ() < speed * (REG12_F(2) + 1.0f) || (*arg1 - mCurPathP1).absXZ() == 0.0f) {
        if (mbCraneMode != 0) {
            modeProc(PROC_00_e, 5);
        }
        return TRUE;
    }
    return FALSE;
}

/* 000007A0-000007C8       .text ride_CB__FP4dBgWP10fopAc_ac_cP10fopAc_ac_c */
void ride_CB(dBgW*, fopAc_ac_c* ac1, fopAc_ac_c* ac2) {
    ((daObj_Ikada_c*)ac1)->_ride(ac2);
}

/* 000007C8-00000A00       .text _ride__13daObj_Ikada_cFP10fopAc_ac_c */
void daObj_Ikada_c::_ride(fopAc_ac_c* actor) {
    if (mType == 1) {
        if (actor == dComIfGp_getLinkPlayer()) {
            mbIsLinkRiding = true;
        }

        if (fopAcM_GetName(actor) == PROC_BOMB) {
            daBomb_c* bomb = (daBomb_c*)actor;

            if (bomb->getBombRestTime() <= 1) {
                cXyz sp24 = actor->current.pos;
                dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &sp24);

                daPy_py_c* player = daPy_getPlayerActorClass();
                cXyz sp18(2.0f, 2.0f, 2.0f);
                dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, &sp24, &player->shape_angle, &sp18);
                fopAcM_seStart(this, JA_SE_LK_LAST_HIT, 0);

                if (mBombSmokeEasterEgg.getEmitter() == NULL) {
                    mBombSmokeAngle = cLib_targetAngleY(&current.pos, &sp24) - shape_angle.y;
                    mBombSmokeRot = shape_angle;
                    mBombSmokeRot.y += mBombSmokeAngle;
                    mBombSmokePos = current.pos;
                    dComIfGp_particle_setShipTail(
                        dPa_name::ID_COMMON_03E1, &mBombSmokePos, &mBombSmokeRot, &scale, 0xff, &mBombSmokeEasterEgg, fopAcM_GetRoomNo(this)
                    );
                    m04A8 = 230;
                }

                mLinkRideRockAmpl = 300;
                modeProc(PROC_00_e, 12);
            }
        }
    }
}

/* 00000A00-00000A20       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* a_this) {
    return ((daObj_Ikada_c*)a_this)->_createHeap();
}

/* 00000A20-00000AA4       .text setCollision__13daObj_Ikada_cFv */
void daObj_Ikada_c::setCollision() {
    if (!mbIsLinkRiding && !dComIfGp_checkPlayerStatus0(0, daPyStts0_HOOKSHOT_AIM_e)) {
        mSph.SetR(l_HIO.m9C * scale.x);
        mSph.SetC(current.pos);
        dComIfG_Ccsp()->Set(&mSph);
    }
}

/* 00000AA4-00000DFC       .text checkTgHit__13daObj_Ikada_cFv */
bool daObj_Ikada_c::checkTgHit() {
    cCcD_Obj* sp64;
    cXyz sp58;
    cXyz sp4C;
    cXyz sp40;
    daPy_py_c* player = daPy_getPlayerActorClass();

    if (player->checkHammerQuake()) {
        sp58 = player->getSwordTopPos();
        f32 abs = (sp58 - current.pos).absXZ();
        if (abs < 1000.0f && mbIsLinkRiding) {
            mLinkRideRockAmpl = 200;
            modeProc(PROC_00_e, 11);
            return true;
        }
    }

    mStts.Move();
    if (cLib_calcTimer(&m12E4) == 0) {
        cCcD_Obj* pcVar3 = mSph.GetTgHitObj();
        sp4C = *mSph.GetTgHitPosP();
        sp64 = mSph.GetTgHitObj();
        if (pcVar3 == NULL) {
            return false;
        }

        bool ret = true;
        if ((s32)pcVar3->GetAtType() != AT_TYPE_BOMB) {
            ret = false;
        }

        if (ret) {
            m12E4 = 5;
            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &sp4C);
            daPy_py_c* player = daPy_getPlayerActorClass();
            sp40.set(2.0f, 2.0f, 2.0f);
            dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, &sp4C, &player->shape_angle, &sp40);
            fopAcM_seStart(this, JA_SE_LK_LAST_HIT, 0);

            if (mBombSmokeEasterEgg.getEmitter() == NULL) {
                mBombSmokeAngle = cLib_targetAngleY(&current.pos, &sp4C) - shape_angle.y;
                mBombSmokeRot = shape_angle;
                mBombSmokeRot.y += mBombSmokeAngle;
                mBombSmokePos = current.pos;
                dComIfGp_particle_setShipTail(
                    dPa_name::ID_COMMON_03E1, &mBombSmokePos, &mBombSmokeRot, &scale, 0xff, &mBombSmokeEasterEgg, fopAcM_GetRoomNo(this)
                );
                m04A8 = 230;
            }
            mLinkRideRockAmpl = 300;
            modeProc(PROC_00_e, 0xc);
            return true;
        }
    }
    return false;
}

/* 00000E38-00000F04       .text pathMove__13daObj_Ikada_cFv */
void daObj_Ikada_c::pathMove() {
    cLib_addCalc2(&speedF, mVelocityFwdTarget, 0.1f, 2.0f);
    dLib_pathMove(&mPathPosTarget, &mCurPathPoint, mpPath, speedF, pathMove_CB, this);
    cLib_addCalcPosXZ2(&current.pos, mPathPosTarget, REG12_F(0) + 0.01f, speedF);
    if (speedF != 0.0f && mVelocityFwdTarget != 0.0f) {
        cLib_addCalcAngleS2(&shape_angle.y, cLib_targetAngleY(&current.pos, &mPathPosTarget), 8, 0x100);
    }
}

/* 00000F04-00000FBC       .text HandleRight__13daObj_Ikada_cFv */
void daObj_Ikada_c::HandleRight() {
    m1154 += l_HIO.m20;
    if (m1154 >= mBckAnm.getEndFrame()) {
        m1154 = mBckAnm.getStartFrame();
    }
}

/* 00000FBC-00001074       .text HandleLeft__13daObj_Ikada_cFv */
void daObj_Ikada_c::HandleLeft() {
    m1154 -= l_HIO.m20;
    if (m1154 <= mBckAnm.getStartFrame()) {
        m1154 = mBckAnm.getEndFrame();
    }
}

/* 00001074-000012EC       .text createWave__13daObj_Ikada_cFv */
void daObj_Ikada_c::createWave() {
    static JGeometry::TVec3<f32> wave_l_direction(0.5f, 1.0f, -0.3f);
    static JGeometry::TVec3<f32> wave_r_direction(-0.5f, 1.0f, -0.3f);

    if (mWaveLCallback.getEmitter() == NULL) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_0037, &mWavePos, &mWaveRot, NULL, 0xff, &mWaveLCallback);
        if (mWaveLCallback.getEmitter() != NULL) {
            mWaveLCallback.getEmitter()->setDirection(wave_l_direction);
        }
    }

    if (mWaveRCallback.getEmitter() == NULL) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_0037, &mWavePos, &mWaveRot, NULL, 0xff, &mWaveRCallback);
        if (mWaveRCallback.getEmitter() != NULL) {
            mWaveRCallback.getEmitter()->setDirection(wave_r_direction);
        }
    }

    if (mSplashCallBack.getEmitter() == NULL) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_0035, &mWavePos, &mWaveRot, NULL, 0xff, &mSplashCallBack);
    }

    if (mTrackCallBack.getEmitter() == NULL) {
        dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0036, &mTrackPos, &shape_angle, NULL, 0x0, &mTrackCallBack);

        JPABaseEmitter* emitter = mTrackCallBack.getEmitter();
        if (emitter != NULL) {
            JGeometry::TVec3<f32> scale = (Vec){1.0f, 1.0f, 1.0f};
            emitter->setGlobalDynamicsScale(scale);
            emitter->setGlobalParticleScale(scale);
        }
    }
}

/* 000012EC-00001528       .text setWave__13daObj_Ikada_cFv */
void daObj_Ikada_c::setWave() {
    f32 fVar2 = l_HIO.mTrackVel;
    f32 fVar1 = l_HIO.mWaveVelFade;
    f32 target = l_HIO.mSplashScaleMax;
    f32 fVar4 = l_HIO.mWaveMaxVelocity;

    if (speedF <= 2.0f) {
        fVar1 = 0.0f;
        target = fVar1;
        mTrackCallBack.stop();
    } else {
        createWave();
    }

    mWavePos.y = dLib_getWaterY(mWavePos, mObjAcch);
    mWaveRot.y = shape_angle.y;

    if (mTrackCallBack.getEmitter() != NULL) {
        mTrackCallBack.setIndirectTexData(l_HIO.mTrackIndTransY, l_HIO.mTrackIndScaleY);
        mTrackCallBack.setSpeed(fVar2);
        mTrackCallBack.setWaterY(mWavePos.y);
        if (mObjAcch.ChkWaterHit()) {
            fVar2 = mObjAcch.m_wtr.GetHeight();
        } else {
            fVar2 = -G_CM3D_F_INF;
        }
        mTrackCallBack.setWaterFlatY(fVar2);
        mTrackCallBack.setLimitSpeed(3.0f);
    }
    mWaveRCallback.setSpeed(fVar1);
    mWaveLCallback.setSpeed(fVar1);
    mWaveRCallback.setMaxSpeed(fVar4);
    mWaveLCallback.setMaxSpeed(fVar4);
    mWaveRCallback.setPitch(l_HIO.mWaveVelOffs + 1.0f);
    mWaveLCallback.setPitch(1.0f - l_HIO.mWaveVelOffs);

    cXyz sp2C = l_HIO.mWaveCollapsePos[0];
    cXyz sp20 = l_HIO.mWaveCollapsePos[1];
    cXyz sp14 = l_HIO.mWaveCollapsePos[0];
    cXyz sp08 = l_HIO.mWaveCollapsePos[1];

    mWaveRCallback.setAnchor(&sp2C, &sp20);
    sp14.x = (f32)(f64)sp14.x * -1.0f;
    sp08.x = (f32)(f64)sp08.x * -1.0f;
    mWaveLCallback.setAnchor(&sp14, &sp08);

    mWaveRCallback.setMaxDisSpeed(l_HIO.mWaveVelSpeed);
    mWaveLCallback.setMaxDisSpeed(l_HIO.mWaveVelSpeed);
    cLib_addCalc2(&mSplashScaleTimer, target, 0.1f, 10.0f);
    mSplashCallBack.setSpeed(mSplashScaleTimer);
    mSplashCallBack.setMaxSpeed(l_HIO.mSplashMaxScaleTimer);
}

/* 00001528-00001690       .text incRopeCnt__13daObj_Ikada_cFii */
void daObj_Ikada_c::incRopeCnt(int arg1, int arg2) {
    cXyz* pcVar5 = &mRopeLine.mpLines->mpSegments[0];
    cXyz* pcVar4 = &m07DC[m07D8];
    s32 i;

    s32 iVar3 = m07D8 + arg1;
    if (iVar3 >= 200) {
        iVar3 = 200;
    } else if (iVar3 < arg2) {
        iVar3 = arg2;
    }

    s32 iVar2 = iVar3 - m07D8;
    if (iVar2 > 0) {
        cXyz sp20 = m_rope_base_vec * iVar2;
        for (i = 0; i < m07D8; i++, pcVar5++) {
            *pcVar5 += sp20;
        }
    } else {
        pcVar5 += m07D8;
    }

    for (i = m07D8; i < iVar3; i++, pcVar4++, pcVar5++) {
        *pcVar4 = m_rope_base_vec;
        if (m07D8 != 0) {
            *pcVar5 = pcVar5[-1] - m_rope_base_vec;
        }
    }
    m07D8 = (s16)iVar3;
}

/* 00001690-00001DEC       .text setRopePos__13daObj_Ikada_cFv */
void daObj_Ikada_c::setRopePos() {
    static cXyz ripple_scale(0.6f, 0.6f, 0.6f);

    cXyz spBC;
    cXyz spB0;
    cXyz spA4;
    cXyz sp98;
    MtxP ropeEndMtx;
    cXyz* pcVar6;
    cXyz* pcVar7;

    if (m07D8 == 0) {
        pcVar6 = &mRopeLine.mpLines->mpSegments[0];
        pcVar7 = &m07DC[0];
    } else {
        pcVar6 = &mRopeLine.mpLines->mpSegments[m07D8] - 1;
        pcVar7 = &m07DC[m07D8 - 1];
    }

    spBC = *pcVar6;

    mDoMtx_stack_c::copy(mpModel->getAnmMtx(1));
    mDoMtx_stack_c::transM(m_crane_offset.x, m_crane_offset.y, m_crane_offset.z);
    mDoMtx_stack_c::multVecZero(pcVar6);

    if (mCurMode == 1) {
        ropeEndMtx = mpRopeEnd->getBaseTRMtx();
        spB0.set(ropeEndMtx[0][3] - pcVar6->x, ropeEndMtx[1][3] - pcVar6->y, ropeEndMtx[2][3] - pcVar6->z);
        spB0.normalizeZP();
        spB0 *= 10.0f;

        pcVar6--;
        pcVar7--;
        for (s32 i = m07D8 - 2; i >= 0; i--, pcVar6--, pcVar7--) {
            *pcVar6 = pcVar6[1] + spB0;
            *pcVar7 = cXyz::Zero;
        }
    } else {
        pcVar6--;
        pcVar7--;

        for (s32 i = m07D8 - 2; i >= 0; i--, pcVar6--, pcVar7--) {
            spBC = *pcVar6;
            if (pcVar6->y < dLib_getWaterY(*pcVar6, mObjAcch)) {
                *pcVar7 *= 0.6f;
            } else {
                *pcVar7 *= 0.9f;
            }
            pcVar7->y -= 3.0f;
            *pcVar6 += *pcVar7;

            spB0 = pcVar6[0] - pcVar6[1];
            f32 abs = spB0.abs();
            if (abs < 0.01f) {
                *pcVar6 = pcVar6[1] + m_rope_base_vec;
            } else {
                *pcVar6 = pcVar6[1] + spB0 * 10.0f / abs;
            }

            *pcVar7 += (*pcVar6 - spBC) * 0.05f;
        }
    }

    s16 iVar3;
    s16 iVar4;
    pcVar7 = mRopeLine.mpLines->mpSegments;
    if (m07D8 > 1) {
        spA4 = pcVar7[0] - pcVar7[1];
        iVar3 = 0;
        iVar4 = 0;
    } else {
        mDoMtx_stack_c::copy(mpModel->getAnmMtx(1));
        mDoMtx_stack_c::transM(m_crane_offset.x, m_crane_offset.y, m_crane_offset.z);
        cMtx_copy(mDoMtx_stack_c::get(), ropeEndMtx);
        spA4.set(pcVar7->x - ropeEndMtx[0][3], pcVar7->y - ropeEndMtx[1][3], pcVar7->z - ropeEndMtx[2][3]);
        iVar3 = 0;
        iVar4 = 0;
    }

    f32 sin = cM_ssin(shape_angle.y);
    f32 cos = cM_scos(shape_angle.y);

    sp98.x = cos * spA4.x - sin * spA4.z;
    sp98.y = spA4.y;
    sp98.z = sin * spA4.x + cos * spA4.z;
    mDoMtx_stack_c::transS(pcVar7->x, pcVar7->y, pcVar7->z);

    mDoMtx_stack_c::ZXYrotM(cM_atan2s(sp98.z, sp98.y) + iVar3, shape_angle.y, cM_atan2s(-sp98.x, std::sqrtf(sp98.y * sp98.y + sp98.z * sp98.z)) + iVar4);
    mDoMtx_stack_c::XrotM(-0x4000);
    mDoMtx_stack_c::multVecZero(&m0474);

    mpRopeEnd->setBaseTRMtx(mDoMtx_stack_c::get());
    f32 fVar9 = pcVar7->y;
    pcVar7->y = dLib_getWaterY(*pcVar7, mObjAcch);
    f32 fVar1 = pcVar7->y;
    pcVar7->y = fVar9;

    if (fVar1 > pcVar7->y) {
        cXyz* ptr = pcVar7;
        for (s32 i = m07D8; i > 0; i--, pcVar7++) {
            if (pcVar7->y <= fVar1) {
                ptr = pcVar7;
            }
        }

        m0444.x = ptr->x;
        m0444.y = fVar1;
        m0444.z = ptr->z;

        if (mRippleCallBack.getEmitter() == NULL) {
            dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &m0444, NULL, &ripple_scale, 0xff, &mRippleCallBack);
            if (mRippleCallBack.getEmitter() != NULL) {
                mRippleCallBack.setRate(0.0f);
                if (m0440 == 0) {
                    fopKyM_createWpillar(&m0444, 1.0f, 0.7f, 0);
                    m0440 = 0x14;
                }
            }
        }
    } else {
        mRippleCallBack.remove();
    }

    if (m0440 != 0) {
        m0440--;
    }
}

/* 00001DEC-000024A4       .text setMtx__13daObj_Ikada_cFv */
void daObj_Ikada_c::setMtx() {
    dLib_waveRot(&current.pos, 0.0f, &mWave);
    s16 waveAnim2Ampl = (mLinkRideRockAmpl * (REG12_S(5) + 10)) * cM_ssin(mLinkRideRockTimer);
    s32 waveAnim1X = (REG8_S(5) + 200) * cM_ssin(mWaveAnimTimer);
    s32 waveAnim1Z = (REG8_S(6) + 60) * cM_ssin(mWaveAnimTimer);
    s16 angleY = fopAcM_searchPlayerAngleY(this) + shape_angle.y;
    s32 waveAnim2X = waveAnim2Ampl * cM_scos(angleY);
    s32 waveAnim2Z = waveAnim2Ampl * cM_ssin(angleY);

    if (l_HIO.mbNoRotAnim == 0) {
        shape_angle.x = mWave.mRotX + waveAnim2X + waveAnim1X;
        shape_angle.z = mWave.mRotZ + waveAnim2Z + waveAnim1Z;
    }

    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, 0, shape_angle.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);

    if (mType == 4) {
        mDoMtx_stack_c::transM(0.0f, 30.0f, -260.0f);
    }

    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

    if (mType == 4) {
        mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
        mDoMtx_stack_c::XYZrotM(shape_angle.x, 0, shape_angle.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);
        mDoMtx_stack_c::YrotM(0x4000);

        for (s32 i = 0; i < 4; i++) {
            Vec sp3C = {l_HIO.mSvOffsX[i], 0.0f, 0.0f};
            fopAc_ac_c* ac;
            if (fopAcM_SearchByID(mSvId[i], &ac)) {
                mDoMtx_stack_c::multVec(&sp3C, &ac->current.pos);
            }
        }

        Vec sp30 = {l_HIO.mSvWaveOffsX, 0.0f, 0.0f};
        mDoMtx_stack_c::multVec(&sp30, &mWavePos);
        sp30.x = l_HIO.mSvTrackOffsX;
        mDoMtx_stack_c::multVec(&sp30, &mTrackPos);
    }

    cMtx_copy(mDoMtx_stack_c::get(), mMtx);

    if (isBonbori()) {
        mLightRotY += 0xd0;
        mLightRotX += 0x100;
#if VERSION == VERSION_DEMO
        cXyz sp24;
        sp24.x = REG12_F(2);
        sp24.y = REG12_F(3) + 340.0f;
        sp24.z = REG12_F(4) + 200.0f;
#else
        cXyz sp24(REG12_F(2), REG12_F(3) + 340.0f, REG12_F(4) + 200.0f);
#endif

        mDoMtx_stack_c::copy(mpModel->getBaseTRMtx());
        mDoMtx_stack_c::multVec(&sp24, &mFirePos);
        mDoMtx_stack_c::transM(sp24.x, sp24.y, sp24.z);
        mDoMtx_stack_c::YrotM(mLightRotY);
        mDoMtx_stack_c::XrotM(mLightRotX);
        mDoMtx_stack_c::scaleM(mLightPower, mLightPower, mLightPower);
        cMtx_copy(mDoMtx_stack_c::get(), mLightMtx);
        mDoMtx_stack_c::multVecZero(&mPLight.mPos);
        mPLight.mColor.r = 600;
        mPLight.mColor.g = 400;
        mPLight.mColor.b = 120;
        mPLight.mFluctuation = 250.0f;
    }

    if ((mType == 1) || (mType == 3)) {
#if VERSION == VERSION_DEMO
        cXyz sp18;
        sp18.x = REG12_F(2) - 105.0f;
        sp18.y = REG12_F(3) + 380.0f;
        sp18.z = REG12_F(4) + 40.0f;
#else
        cXyz sp18(REG12_F(2) - 105.0f, REG12_F(3) + 380.0f, REG12_F(4) + 40.0f);
#endif
        mDoMtx_stack_c::copy(mpModel->getBaseTRMtx());
        mDoMtx_stack_c::multVec(&sp18, &mSePos);
    }

    if (isWave()) {
        mDoMtx_stack_c::transS(current.pos.x, current.pos.y, current.pos.z);
        mDoMtx_stack_c::XYZrotM(shape_angle.x, 0, shape_angle.z);
        mDoMtx_stack_c::YrotM(shape_angle.y);

        Vec sp0C = {0.0f, l_HIO.mShipOffsY_Attention, 0.0f};
        mDoMtx_stack_c::multVec(&sp0C, &attention_info.position);
        sp0C.y = l_HIO.mShipOffsY_Eye;
        mDoMtx_stack_c::multVec(&sp0C, &eyePos);
        sp0C.y = 0.0f;

        if (mType != 4) {
            f32 fVar1 = REG8_F(5) + 5.0f;
            if (mCurMode == 10) {
                fVar1 = REG8_F(5) + 20.0f;
            }
            sp0C.z = l_HIO.mTerryWaveOffsZ + fVar1;
            sp0C.y = l_HIO.mTerryWaveOffsY;
            mDoMtx_stack_c::multVec(&sp0C, &mWavePos);
            sp0C.z = l_HIO.mTerryTrackOffsZ;
            sp0C.y = 0.0f;
            mDoMtx_stack_c::multVec(&sp0C, &mTrackPos);
        }
    }
}

/* 000024A4-000027A4       .text modeProc__13daObj_Ikada_cFQ213daObj_Ikada_c6Proc_ei */
void daObj_Ikada_c::modeProc(daObj_Ikada_c::Proc_e proc, int mode) {
    typedef void (daObj_Ikada_c::*modeFunc)();
    struct ModeFuncs {
        /* 0x00 */ modeFunc init;
        /* 0x0C */ modeFunc exec;
        /* 0x18 */ const char* name;
    }; // size = 0x1C

    static ModeFuncs mode_tbl[] = {
        {&daObj_Ikada_c::modeWaitInit, &daObj_Ikada_c::modeWait, "WAIT"},
        {&daObj_Ikada_c::modeCraneUpInit, &daObj_Ikada_c::modeCraneUp, "CRANE_UP"},
        {&daObj_Ikada_c::modeCraneUpWaitInit, &daObj_Ikada_c::modeCraneUpWait, "CRANE_UP_WAIT"},
        {&daObj_Ikada_c::modeCraneDownInit, &daObj_Ikada_c::modeCraneDown, "CRANE_DOWN"},
        {&daObj_Ikada_c::modeCraneDownWaitInit, &daObj_Ikada_c::modeCraneDownWait, "CRANE_DOWN_WAIT"},
        {&daObj_Ikada_c::modeCraneTurnInit, &daObj_Ikada_c::modeCraneTurn, "CRANE_TURN"},
        {&daObj_Ikada_c::modeCraneResetInit, &daObj_Ikada_c::modeCraneReset, "CRANE_RESET"},
        {&daObj_Ikada_c::modeCraneWaitInit, &daObj_Ikada_c::modeCraneWait, "CRANE_WAIT"},
        {&daObj_Ikada_c::modePathMoveInit, &daObj_Ikada_c::modePathMove, "PATH_MOVE"},
        {&daObj_Ikada_c::modeStopInit, &daObj_Ikada_c::modeStop, "STOP"},
        {&daObj_Ikada_c::modePathMoveTerryInit, &daObj_Ikada_c::modePathMoveTerry, "PATH_MOVE_TERRY"},
        {&daObj_Ikada_c::modeStopTerryInit, &daObj_Ikada_c::modeStopTerry, "STOP"},
        {&daObj_Ikada_c::modeStopBombTerryInit, &daObj_Ikada_c::modeStopBombTerry, "STOP_BOMB"},
    };

    if (proc == PROC_00_e) {
        mCurMode = mode;
        (this->*mode_tbl[mCurMode].init)();
    } else if (proc == PROC_01_e) {
        (this->*mode_tbl[mCurMode].exec)();
    }
}

/* 000027A4-000027A8       .text modeWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeWaitInit() {
}

/* 000027A8-00002840       .text modeWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeWait() {
    if (mType == 4) {
        if (l_HIO.m1C != 0) {
            if (m07D8 > l_HIO.m1C) {
                incRopeCnt(-1, 0);
            } else if (m07D8 < l_HIO.m1C) {
                incRopeCnt(1, 0);
            }
        }

        if (REG12_S(4) != 0) {
            modeProcInit(1);
        }
    }
}

/* 00002840-00002844       .text modeCraneUpInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUpInit() {
}

/* 00002844-0000289C       .text modeCraneUp__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUp() {
    if (m07D8 > 15) {
        HandleRight();
        incRopeCnt(-1, 0);
    } else {
        modeProcInit(2);
    }
}

/* 0000289C-000028B0       .text modeCraneUpWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUpWaitInit() {
    mTimer = l_HIO.m24;
}

/* 000028B0-000028F8       .text modeCraneUpWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneUpWait() {
    if (cLib_calcTimer(&mTimer) == 0) {
        modeProcInit(6);
    }
}

/* 000028F8-00002904       .text modeCraneDownInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDownInit() {
    m115E = 150;
}

/* 00002904-000029B0       .text modeCraneDown__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDown() {
    cLib_addCalcAngleS2(&m115E, 0, 10, 10);
    if (m115E < 0x14) {
        HandleLeft();
        if (m07D8 < l_HIO.m1E) {
            incRopeCnt(1, 0);
        } else {
            modeProcInit(7);
        }
    } else {
        m115C += REG12_S(2) + 0x1830;
    }
}

/* 000029B0-000029C4       .text modeCraneDownWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDownWaitInit() {
    mTimer = l_HIO.m24;
}

/* 000029C4-00002A0C       .text modeCraneDownWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneDownWait() {
    if (cLib_calcTimer(&mTimer) == 0) {
        modeProcInit(3);
    }
}

/* 00002A0C-00002A24       .text modeCraneTurnInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneTurnInit() {
    m115E = 150;
    speedF = 0.0f;
}

/* 00002A24-00002AEC       .text modeCraneTurn__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneTurn() {
    cLib_addCalcAngleS2(&m115E, 0, 10, 10);
    if (m115E < 0x14) {
        HandleRight();
        if (m1168 == 1) {
            m1158 = 0x4000;
        } else {
            m1158 = -0x4000;
        }
        cLib_addCalcAngleS2(&m115A, m1158, 10, 0x100);
        if (cLib_distanceAngleS(m115A, m1158) <= 0x100) {
            modeProcInit(4);
        }
    } else {
        m115C += REG12_S(2) + 0x1830;
    }
}

/* 00002AEC-00002B04       .text modeCraneResetInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneResetInit() {
    m115E = 150;
    speedF = 0.0f;
}

/* 00002B04-00002BB4       .text modeCraneReset__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneReset() {
    cLib_addCalcAngleS2(&m115E, 0, 10, 10);
    if (m115E < 20) {
        HandleLeft();
        m1158 = 0;
        cLib_addCalcAngleS2(&m115A, m1158, 10, 0x100);
        if (cLib_distanceAngleS(m115A, m1158) <= 0x100) {
            modeProcInit(8);
        }
    } else {
        m115C += REG12_S(2) + 0x1830;
    }
}

/* 00002BB4-00002BC0       .text modeCraneWaitInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneWaitInit() {
    mTimer = 600;
}

/* 00002BC0-00002C08       .text modeCraneWait__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeCraneWait() {
    if (cLib_calcTimer(&mTimer) == 0) {
        modeProcInit(1);
    }
}

/* 00002C08-00002C60       .text modePathMoveInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMoveInit() {
    if (cM_rndF(1.0f) < 0.5) {
        m1168 = 0;
    } else {
        m1168 = 1;
    }
}

/* 00002C60-00002DC0       .text modePathMove__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMove() {
    if (l_HIO.m06 != 0) {
        HandleRight();
    }

    if (l_HIO.m05 != 0) {
        HandleLeft();
    }

    if (l_HIO.m08 == 0 && mPathId != 0xFF) {
        if (mbCraneMode != 0) {
            if ((mCurPathP1 - current.pos).absXZ() < 50.0f) {
                mVelocityFwdTarget = 1.0f;
            } else {
                mVelocityFwdTarget = 8.0f;
            }
        } else {
            mVelocityFwdTarget = 8.0f;
        }
        pathMove();
    }
}

/* 00002DC0-00002DC4       .text modeStopInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopInit() {
}

/* 00002DC4-00002F04       .text modeStop__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStop() {
    if (l_HIO.m06 != 0) {
        HandleRight();
    }

    if (l_HIO.m05 != 0) {
        HandleLeft();
    }

    if (m02F4 == 8) {
        mVelocityFwdTarget = 0.0f;
        if (mPathId != 0xff) {
            pathMove();
        }
    }

    if (m1166 == 0) {
        if (m07D8 <= 15) {
            HandleLeft();
            incRopeCnt(1, 0);
        } else if (m02F4 != 9) {
            if (m02F4 == 7) {
                modeProcInit(3);
            } else {
                modeProcInit(m02F4);
            }
        } else {
            modeProcInit(8);
        }
    } else if (m07D8 > 2) {
        HandleRight();
        incRopeCnt(-2, 0);
        if (m07D8 < 2) {
            m07D8 = 2;
        }
    }
}

/* 00002F04-00002F10       .text modePathMoveTerryInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMoveTerryInit() {
    mTimer = 10;
}

/* 00002F10-00003228       .text modePathMoveTerry__13daObj_Ikada_cFv */
void daObj_Ikada_c::modePathMoveTerry() {
    setCollision();
    if (!checkTgHit()) {
        bool bPlayerNear = false;
        f32 dVar4 = fopAcM_searchPlayerDistanceXZ(this);
        if ((dVar4 < l_HIO.mPlayerStopDistance) && cLib_calcTimer(&mStopTimer) == 0) {
            mStopTimer = cM_rndF(120.0f) + 240.0f;
            if (cM_rndF(100.0f) < 50.0f) {
                mDoAud_seStart(JA_SE_OBJ_BS_MELODY_1, &mSePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            } else {
                mDoAud_seStart(JA_SE_OBJ_BS_MELODY_2, &mSePos, 0, dComIfGp_getReverb(fopAcM_GetRoomNo(this)));
            }
        }

        if (mType == 1) {
            mVelocityFwdTarget = l_HIO.mVelocityTargetTerry1;
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                if (dVar4 < l_HIO.m94) {
                    bPlayerNear = true;
                }
            } else if (dVar4 < l_HIO.m9A) {
                bPlayerNear = true;
            }
        } else if (mType == 3) {
            mVelocityFwdTarget = l_HIO.mVelocityTargetTerry3;
            if (dVar4 < l_HIO.mPlayerStopDistance) {
                mVelocityFwdTarget = l_HIO.mA8;
            }

            if (dVar4 < l_HIO.m98) {
                bPlayerNear = true;
            }
        }

        if (mbIsLinkRiding) {
            mTimer = 30;
        } else if (cLib_calcTimer(&mTimer) == 0 && bPlayerNear) {
            modeProcInit(11);
            return;
        }
        mLinkRideRockTimer += REG12_S(2) + 0x1830;
        cLib_addCalcAngleS2(&mLinkRideRockAmpl, 0, 10, 10);
        if (mLinkRideRockAmpl <= 10) {
            mLinkRideRockAmpl = 0;
        }

        if (mPathId != 0xff) {
            pathMove();
        }
    }
}

/* 00003228-00003234       .text modeStopTerryInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopTerryInit() {
    mTimer = 210;
}

/* 00003234-0000342C       .text modeStopTerry__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopTerry() {
    setCollision();
    if (!checkTgHit()) {
        bool bVar1 = false;
        f32 dVar4 = fopAcM_searchPlayerDistanceXZ(this);

        if (mType == 1) {
            if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e)) {
                if (dVar4 >= l_HIO.m94) {
                    bVar1 = true;
                }
            } else if (dVar4 >= l_HIO.m9A) {
                bVar1 = true;
            }
        } else if (mType == 3 && dVar4 >= l_HIO.m98) {
            bVar1 = true;
        }

        if (bVar1) {
            modeProcInit(10);
        } else {
            if (mbIsLinkRiding) {
                if (cLib_calcTimer(&mTimer) == 0) {
                    modeProcInit(10);
                    return;
                }
            } else {
                mTimer = 300;
            }

            mLinkRideRockTimer += REG12_S(2) + 0x1830;
            cLib_addCalcAngleS2(&mLinkRideRockAmpl, 0, 10, 10);
            if (mLinkRideRockAmpl <= 10) {
                mLinkRideRockAmpl = 0;
            }

            mVelocityFwdTarget = 0.0f;

            if (mPathId != 0xff) {
                pathMove();
            }
        }
    }
}

/* 0000342C-00003430       .text modeStopBombTerryInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopBombTerryInit() {
}

/* 00003430-000034D0       .text modeStopBombTerry__13daObj_Ikada_cFv */
void daObj_Ikada_c::modeStopBombTerry() {
    setCollision();
    if (!checkTgHit()) {
        mLinkRideRockTimer += REG12_S(2) + 0x1830;
        cLib_addCalcAngleS2(&mLinkRideRockAmpl, 0, 10, 10);
        if (mLinkRideRockAmpl <= 10) {
            mLinkRideRockAmpl = 0;
        }

        mVelocityFwdTarget = 0.0f;

        if (mPathId != 0xff) {
            pathMove();
        }
    }
}

/* 000034D0-00003750       .text epProc__13daObj_Ikada_cFv */
void daObj_Ikada_c::epProc() {
    if (dKy_daynight_check() == dKy_TIME_DAY_e) {
        mFireParticle.remove();
        mPLight.mPower = 0.0f;
    } else {
        if (mFireParticle.getEmitter() == NULL) {
            static cXyz fire_scale(0.5f, 0.5f, 0.5f);

            fire_scale.x = REG12_F(10) + 0.5f;
            fire_scale.y = fire_scale.x;
            fire_scale.z = fire_scale.x;
            dComIfGp_particle_set(dPa_name::ID_COMMON_01EA, &mFirePos, NULL, &fire_scale, 0xff, &mFireParticle);
        }

        if (mFireParticle.getEmitter() != NULL) {
            cXyz sp18 = mFirePos;
            sp18.y += 20.0f;

            dComIfGp_particle_setSimple(dPa_name::ID_COMMON_4004, &sp18);

            if (cLib_calcTimer(&mEpTimer0) == 0) {
                mEpTimer0 = (s16)(REG0_F(3) + cM_rndF(REG0_F(2) + 5.0f));
                m050C = REG0_F(7) + (cM_rndF(REG0_F(6) + 4.0f) + 8.0f);
            }

            if (cLib_calcTimer(&mEpTimer1) == 0) {
                mEpTimer1 = (s16)(cM_rndF(6.0f) + 3.0f);
                mLightPowerTarget = cM_rndF(0.075f) + 0.75f;
            }

            cLib_addCalc2(&m0508, m050C, 1.0, REG0_F(4) + 0.1f + 0.9f);
            cLib_addCalc2(&mLightPower, mLightPowerTarget, 0.4f, 0.04f);
            mPLight.mPower = mLightPower * 150.0f;
        }
    }
}

/* 00003750-00003CA0       .text _execute__13daObj_Ikada_cFv */
bool daObj_Ikada_c::_execute() {
    mWaveAnimTimer += REG8_S(4) + 0x200;
    f32 fVar9 = 5.0f + REG8_F(5);
    if (mCurMode == 10) {
        fVar9 = 20.0f + REG8_F(5);
    }
    f32 fVar8 = fVar9 * cM_ssin(mWaveAnimTimer);

    if (mBombSmokeEasterEgg.getEmitter() != NULL) {
        mBombSmokeRot = shape_angle;
        mBombSmokeRot.y += mBombSmokeAngle;

        JGeometry::TVec3<f32> scale = (Vec){3.0f, 3.0f, 3.0f};
        JPABaseEmitter* emitter = mBombSmokeEasterEgg.getEmitter();
        emitter->setGlobalDynamicsScale(scale);
        emitter->setGlobalParticleScale(scale);

        mBombSmokePos = current.pos;
        mBombSmokePos.y = l_HIO.m28;

        if (cLib_calcTimer(&m04A8) == 0) {
            mBombSmokeEasterEgg.remove();
        }
    }

    if ((m1166 == 1) && (mCurMode != 9)) {
        m02F4 = mCurMode;
        modeProcInit(9);
    }

    if (isBonbori()) {
        epProc();
    }

    if (mType == 4) {
        setRopePos();
    }

    if (mType == 4) {
        mBckAnm.setFrame(m1154);
        if (REG12_S(0) != 0) {
            mJointRot[REG12_S(0)].x = REG12_S(1);
            mJointRot[REG12_S(0)].y = REG12_S(2);
            mJointRot[REG12_S(0)].z = REG12_S(3);
        }
    }

    modeProc(PROC_01_e, 13);

    current.pos.y = fVar8 + dLib_getWaterY(current.pos, mObjAcch);
    setMtx();
    mpModel->calc();

    if (isWave()) {
        f32 s = scale.x;
        s32 uVar5 = fopAcM_checkCullingBox(mpModel->getBaseTRMtx(), s * -1000.0f, s * -50.0f, s * -1000.0f, s * 1000.0f, s * 1000.0f, s * 1000.0f);
        if (speedF <= 2.0f || uVar5 & 0xFF || fopAcM_searchPlayerDistanceXZ(this) > 18000.0f) {
            mWaveRCallback.remove();
            mWaveLCallback.remove();
            mSplashCallBack.remove();
            mTrackCallBack.stop();
        } else {
            setWave();
        }
    }

    mpBgW->Move();

    if (isFlag()) {
        fopAc_ac_c* ac = (daMajuu_Flag_c*)fopAcM_SearchByID(mFlagPcId);
        if (ac != NULL) {
            daMajuu_Flag_c* pfVar6 = (daMajuu_Flag_c*)ac;
            pfVar6->setOtherMatrix(&mMtx);

            if (l_HIO.mFlagOffset.x || l_HIO.mFlagOffset.y || l_HIO.mFlagOffset.z) {
                mFlagOffset = l_HIO.mFlagOffset;
            }

            if (l_HIO.mFlagScale) {
                mFlagScale = l_HIO.mFlagScale;
            }

            pfVar6->setBaseScale(mFlagScale);
            pfVar6->setOtherOffset(&mFlagOffset);
        }
    }

    mbIsLinkRiding = false;

    if (mType == 1 || mType == 3) {
        f32 sqrt = (current.pos - old.pos).abs();
        f32 fVar1 = sqrt / 30.0f;

        if (fVar1 <= 0.0f) {
            fVar1 = 0.0f;
        } else if (fVar1 >= 1.0f) {
            fVar1 = 1.0f;
        }
        s8 reverb = fVar1 * 100.0f;
        fopAcM_seStart(this, JA_SE_OBJ_BS_BOAT_CRUISE, reverb);
    }
    return false;
}

const u32 unused_5617[] = {
    0xFFFF0080,
    0xFF80,
    0xFF80,
    0xFF000080,
    0xFF000080,
    0xFF80,
    0xFF000080,
    0xFF000080,
    0xFF000080,
};

/* 00003CA0-00003CD4       .text debugDraw__13daObj_Ikada_cFv */
void daObj_Ikada_c::debugDraw() {
    cXyz sp08 = current.pos;
    sp08.y += 20.0f;
}

/* 00003CD4-00003EE0       .text _draw__13daObj_Ikada_cFv */
bool daObj_Ikada_c::_draw() {
    if (l_HIO.mbDebugDraw) {
        debugDraw();
    }

    if (mFireParticle.getEmitter() != NULL) {
        GXColor color;
        color.r = 0xEB;
        color.g = 0x7D;
        color.b = 0;
        color.a = 0;
        dComIfGd_setAlphaModelColor(color);
        dComIfGd_setAlphaModel(dDlst_alphaModel_c::TYPE_SPHERE, mLightMtx, m0508);
    }

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);

    dComIfGd_setListBG();

    if (mType == 4) {
        J3DModelData* modelData = mpModel->getModelData();
        mBckAnm.entry(modelData, mBckAnm.getFrame());
        mDoExt_modelUpdateDL(mpModel);
        mpModel->getModelData()->getJointNodePointer(0)->setMtxCalc(NULL);
    } else {
        mDoExt_modelUpdateDL(mpModel);
    }

    dComIfGd_setList();

    if (isCrane()) {
        if (m07D8 >= 2) {
            static GXColor rope_color = {200, 150, 50, 255};

            mRopeLine.update(m07D8, 5.0f, rope_color, 0, &tevStr);
            dComIfGd_set3DlineMat(&mRopeLine);
        }
        g_env_light.setLightTevColorType(mpRopeEnd, &tevStr);
        mDoExt_modelUpdateDL(mpRopeEnd);
    }

    if (isCrane()) {
        dSnap_RegistFig(DSNAP_TYPE_UNK83, this, 1.0f, 1.0f, 1.0f);
    }

    return true;
}

/* 00003EE0-00003F34       .text getArg__13daObj_Ikada_cFv */
void daObj_Ikada_c::getArg() {
    u32 uVar2 = fopAcM_GetParam(this);
    u32 sVar1 = home.angle.x;

    mType = uVar2 & 0xF;
    if (mType != 4) {
        m0294 = (uVar2 >> 4) & 0x3F;
        m0298 = (uVar2 >> 10) & 0xFF;
        m02A0 = (uVar2 >> 18) & 0xFF;
        m029C = (sVar1 >> 0) & 0xFF;
        mPathId = (sVar1 >> 8) & 0xFF;
    } else {
        mPathId = (uVar2 >> 0x10) & 0xFF;
    }
}

/* 00003F34-00004838       .text createInit__13daObj_Ikada_cFv */
void daObj_Ikada_c::createInit() {
    mInitPos = current.pos;
    mStopTimer = cM_rndF(120.0f) + 240.0f;

    if ((mType == 1) || (mType == 2) || (mType == 0)) {
        fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e | 0x5);
    }
    mPathPosTarget = current.pos;
    if (mPathId != 0xFF && (mType == 4 || mType == 1 || mType == 3)) {
        mpPath = dPath_GetRoomPath(mPathId, current.roomNo);
        if (mType == 4) {
            modeProcInit(8);
        }
    } else {
        modeProcInit(0);
    }

    if (mType == 1 || mType == 3) {
        modeProcInit(11);
    }

    if (mType == 4) {
        mSvId[0] = fopAcM_createChild("Sv0", fopAcM_GetID(this), 0xffffffff, &current.pos, tevStr.mRoomNo, 0, 0, 0);
        mSvId[1] = fopAcM_createChild("Sv1", fopAcM_GetID(this), 0xffffffff, &current.pos, tevStr.mRoomNo, 0, 0, 0);
        mSvId[2] = fopAcM_createChild("Sv2", fopAcM_GetID(this), 0xffffffff, &current.pos, tevStr.mRoomNo, 0, 0, 0);
        mSvId[3] = fopAcM_createChild("Sv3", fopAcM_GetID(this), 0xffffffff, &current.pos, tevStr.mRoomNo, 0, 0, 0);
    }

    mLightRotY = cM_rndF(32768.0f);
    mLightRotX = cM_rndF(32768.0f);

    current.pos.y = dLib_getWaterY(current.pos, mObjAcch);
    mpBgW->SetGrpRoomInf(fopAcM_GetRoomNo(this));

    if (mType != 4) {
        setMtx();
        mpBgW->Move();
    }

    dComIfG_Bgsp()->Regist(mpBgW, this);

    if (mType == 1) {
        mpBgW->SetRideCallback(ride_CB);
    }

    if (mType == 1) {
        mpBgW->SetCrrFunc(dBgS_MoveBGProc_TypicalRotY);
    } else {
        mpBgW->SetCrrFunc(dBgS_MoveBGProc_Typical);
    }
    mAcchCir.SetWall(30.0f, 30.0f);
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), NULL, NULL);
    mObjAcch.SetWallNone();
    mObjAcch.SetRoofNone();

    if (isWave()) {
        createWave();
    }

    if (isBonbori()) {
        dKy_plight_set(&mPLight);
    }

    fopAcM_SetGravity(this, 0.0f);
    fopAcM_posMoveF(this, NULL);
    fopAcM_SetMtx(this, mpModel->getBaseTRMtx());
    fopAcM_setCullSizeBox(this, scale.x * -1000.0f, scale.x * -50.0f, scale.x * -1000.0f, scale.x * 1000.0f, scale.x * 1000.0f, scale.x * 1000.0f);
    fopAcM_setCullSizeFar(this, 10.0f);

    if (isFlag()) {
        static const cXyz flag_offset[] = {
            cXyz(0.0f, 700.0f, 0.0f),
            cXyz(0.0f, 0.0f, 0.0f),
            cXyz(0.0f, 0.0f, 0.0f),
            cXyz(0.0f, 0.0f, 0.0f),
            cXyz(100.0f, 530.0f, 0.0f),
        };
        static const u32 params[] = {4, 4, 4, 4, 0x2000000};
        static const f32 flag_scale[] = {0.2f, 0.0f, 0.0f, 0.0f, 0.12f};

        mFlagPcId = fopAcM_create(PROC_MAJUU_FLAG, params[mType], &current.pos, tevStr.mRoomNo, &current.angle);
        mFlagOffset = flag_offset[mType];
        mFlagScale = flag_scale[mType];
    }

    mWave.mAnimX = cM_rndF(32768.0f);
    mWave.mAnimZ = cM_rndF(32768.0f);

    if (mType == 4) {
        mpModel->calc();
        m07D8 = 15;

        cXyz* pcVar8 = &mRopeLine.mpLines->mpSegments[m07D8] - 1;
        cXyz* pcVar7 = &m07DC[m07D8 - 1];

        mDoMtx_stack_c::copy(mpModel->getAnmMtx(1));
        mDoMtx_stack_c::transM(m_crane_offset.x, m_crane_offset.y, m_crane_offset.z);
        mDoMtx_stack_c::multVecZero(pcVar8);

        cXyz sp80(0.0f, -1.0f, 0.0f);
        sp80 *= 10.0f;

        pcVar8--;
        pcVar7--;

        for (s32 i = m07D8 - 2; i >= 0; i--, pcVar8--, pcVar7--) {
            *pcVar8 = pcVar8[1] + sp80;
            *pcVar7 = cXyz::Zero;
        }

        pcVar8 = &mRopeLine.mpLines->mpSegments[0];
        cXyz sp74 = mRopeLine.mpLines->mpSegments[0] - mRopeLine.mpLines->mpSegments[1];

        f32 sin = cM_ssin(shape_angle.y);
        f32 cos = cM_scos(shape_angle.y);
#if VERSION == VERSION_DEMO
        cXyz sp68;
        sp68.x = cos * sp74.x - sin * sp74.z;
        sp68.y = sp74.y;
        sp68.z = sin * sp74.x + cos * sp74.z;
#else
        cXyz sp68(cos * sp74.x - sin * sp74.z, sp74.y, sin * sp74.x + cos * sp74.z);
#endif

        mDoMtx_stack_c::transS(pcVar8->x, pcVar8->y, pcVar8->z);
        mDoMtx_stack_c::ZXYrotM((s16)cM_atan2s(sp68.z, sp68.y), shape_angle.y, (s16)cM_atan2s(-sp68.x, std::sqrtf(sp68.y * sp68.y + sp68.z * sp68.z)));
        mDoMtx_stack_c::XrotM(-0x4000);
        mDoMtx_stack_c::multVecZero(&m0474);
        mpRopeEnd->setBaseTRMtx(mDoMtx_stack_c::get());
    }

    mStts.Init(0xff, 0xff, this);
    mSph.Set(m_sph_src);
    mSph.SetStts(&mStts);
}

/* 00004838-00004B60       .text _createHeap__13daObj_Ikada_cFv */
BOOL daObj_Ikada_c::_createHeap() {
    static const s32 bdl[] = {IKADAH_BDL_VIKAE, IKADAH_BDL_VTSP, IKADAH_BDL_VIKAH, IKADAH_BDL_VTSP2, IKADAH_BDL_VSVSP};
    static const s32 dzb[] = {IKADAH_DZB_VIKAE, IKADAH_DZB_VTSP, IKADAH_DZB_VIKAH, IKADAH_DZB_VTSP, IKADAH_DZB_VSVSP};

    J3DModelData* modelData = (J3DModelData*)dComIfG_getObjectRes(m_arc_name, bdl[mType]);
    JUT_ASSERT(2170, modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000022);
    if (mpModel == NULL) {
        return FALSE;
    }

    if (mType == 4) {
        J3DAnmTransform* bck = (J3DAnmTransform*)dComIfG_getObjectRes(m_arc_name, IKADAH_BCK_SVSHIP_KAITEN);
        JUT_ASSERT(2180, bck != NULL);

        if (!mBckAnm.init(modelData, bck, true, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false)) {
            return FALSE;
        }
    }

    mpModel->setUserArea((u32)this);

    if (mType == 4) {
        for (u16 i = 0; i < modelData->getJointNum(); i++) {
            switch (i) {
            case 1:
            case 2:
            case 3:
                modelData->getJointNodePointer(i)->setCallBack(nodeControl_CB);
                break;
            }
        }
    }

    setMtx();

    mpBgW = new dBgW();
    if (mpBgW == NULL) {
        return FALSE;
    }

    cBgD_t* cbgd = (cBgD_t*)dComIfG_getObjectRes(m_arc_name, dzb[mType]);
    if (mpBgW->Set(cbgd, cBgW::MOVE_BG_e, &mMtx) == true) {
        return FALSE;
    }

    if (mType == 4) {
        ResTIMG* pImg = (ResTIMG*)dComIfG_getObjectRes("Always", ALWAYS_BTI_ROPE);
        if (!mRopeLine.init(1, 200, pImg, 0)) {
            return FALSE;
        }

#if VERSION > VERSION_DEMO
        J3DModelData*
#endif
            modelData = (J3DModelData*)dComIfG_getObjectRes("Link", LINK_BDL_ROPEEND);
        JUT_ASSERT(2228, modelData != NULL);

        mpRopeEnd = mDoExt_J3DModel__create(modelData, 0x80000, 0x11000002);
        if (mpRopeEnd == NULL) {
            return FALSE;
        }
    }
    return TRUE;
}

/* 00004B60-00004C18       .text _create__13daObj_Ikada_cFv */
cPhs_State daObj_Ikada_c::_create() {
    fopAcM_SetupActor(this, daObj_Ikada_c);

    cPhs_State ret = dComIfG_resLoad(&mPhase, m_arc_name);
    if (ret == cPhs_COMPLEATE_e) {
        getArg();
        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize[mType])) {
            return cPhs_ERROR_e;
        }
        createInit();
    }
    return ret;
}

/* 00005320-0000543C       .text _delete__13daObj_Ikada_cFv */
bool daObj_Ikada_c::_delete() {
    dComIfG_resDelete(&mPhase, m_arc_name);

    mWaveRCallback.remove();
    mWaveLCallback.remove();
    mSplashCallBack.remove();
    mTrackCallBack.remove();
    mRippleCallBack.remove();
    mFireParticle.remove();
    mBombSmokeEasterEgg.remove();

#if VERSION > VERSION_DEMO
    mDoAud_seDeleteObject(&mSePos);
#endif

    if (isBonbori()) {
        dKy_plight_cut(&mPLight);
    }

#if VERSION == VERSION_DEMO
    if (mpBgW != NULL) {
#else
    if (heap != NULL && mpBgW != NULL) {
#endif
        if (mpBgW->ChkUsed()) {
            dComIfG_Bgsp()->Release(mpBgW);
        }
    }
    return true;
}

/* 0000543C-0000545C       .text daObj_IkadaCreate__FPv */
static cPhs_State daObj_IkadaCreate(void* i_this) {
    return ((daObj_Ikada_c*)i_this)->_create();
}

/* 0000545C-00005480       .text daObj_IkadaDelete__FPv */
static BOOL daObj_IkadaDelete(void* i_this) {
    return ((daObj_Ikada_c*)i_this)->_delete();
}

/* 00005480-000054A4       .text daObj_IkadaExecute__FPv */
static BOOL daObj_IkadaExecute(void* i_this) {
    return ((daObj_Ikada_c*)i_this)->_execute();
}

/* 000054A4-000054C8       .text daObj_IkadaDraw__FPv */
static BOOL daObj_IkadaDraw(void* i_this) {
    return ((daObj_Ikada_c*)i_this)->_draw();
}

/* 000054C8-000054D0       .text daObj_IkadaIsDelete__FPv */
static BOOL daObj_IkadaIsDelete(void*) {
    return TRUE;
}

static actor_method_class daObj_IkadaMethodTable = {
    (process_method_func)daObj_IkadaCreate,
    (process_method_func)daObj_IkadaDelete,
    (process_method_func)daObj_IkadaExecute,
    (process_method_func)daObj_IkadaIsDelete,
    (process_method_func)daObj_IkadaDraw,
};

actor_process_profile_definition g_profile_OBJ_IKADA = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0003,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OBJ_IKADA,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daObj_Ikada_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OBJ_IKADA,
    /* Actor SubMtd */ &daObj_IkadaMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
