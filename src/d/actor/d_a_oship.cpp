/**
 * d_a_oship.cpp
 * Enemy - Warship (Great Sea enemy ship)
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_oship.h"
#include "d/actor/d_a_bomb.h"
#include "d/actor/d_a_majuu_flag.h"
#include "d/actor/d_a_player.h"
#include "d/actor/d_a_salvage.h"
#include "d/actor/d_a_ship.h"
#include "d/res/res_oship.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/d_cc_d.h"

const s32 daOship_c::m_heapsize = 0x1280;

const char daOship_c::m_arc_name[] = "Oship";

const dCcD_SrcCyl daOship_c::m_cyl_src = {
    // dCcD_SrcGObjInf
    {
        /* Flags             */ 0,
        /* SrcObjAt  Type    */ 0,
        /* SrcObjAt  Atp     */ 0,
        /* SrcObjAt  SPrm    */ 0,
        /* SrcObjTg  Type    */ AT_TYPE_ALL & ~AT_TYPE_BOOMERANG,
        /* SrcObjTg  SPrm    */ cCcD_TgSPrm_Set_e | cCcD_TgSPrm_IsOther_e,
        /* SrcObjCo  SPrm    */ cCcD_CoSPrm_Set_e | cCcD_CoSPrm_IsOther_e | cCcD_CoSPrm_VsGrpAll_e,
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
    // cM3dGCylS
    {{
        /* Center */ {0.0f, 0.0f, 0.0f},
        /* Radius */ 75.0f,
        /* Height */ 115.0f,
    }},
};

static daOship_HIO_c l_HIO;

/* 000000EC-00000234       .text __ct__13daOship_HIO_cFv */
daOship_HIO_c::daOship_HIO_c() {
    m04 = 0;
    m06 = false;
    m05 = false;
    m07 = false;
    m08 = false;
    mTrackOffsY = -0.04;
    mTrackScaleY = 4.0;
    mAttentionOffsY = 900.0;
    mEyeOffsY = 300.0;
    mWaveOffsZ = 380.0;
    mTrackOffsZ = 0.0;
    mDistRangeA = 2500.0;
    mDistRangeB = 6000.0;
    mDistRangeC = 12000.0;
    mAttackDelayA = 0x1e;
    mAttackDelayB = 200;
    mSplashScaleTimerTarget = 200.0;
    mSplashMaxScaleTimer = 300.0;
    mWaveVelFade1 = 2.0;
    mTrackVel = 300.0;
    mWaveVelSpeed = 2.0;
    mWaveMaxVelocity = 15.0;
    mWaveVelFadeOffs = 0.0;
    mWaveCollapsePos0.set(-80.0f, -50.0f, -150.0f);
    mWaveCollapsePos1.set(-40.0f, -100.0f, -350.0f);
    mBombOffset.set(450.0f, 0.0f, 0.0f);
    mBombSpeed = 85.0;
    mBombAcceleration = -2.0;
    mBombNoGravityTime = 0x23;
    mBadAimAdjustDistanceStart = 3500.0;
    mBadAimMax = 0x3000;
    field_0x8E = 0x3000;
    field_0x90 = 0x3500;
    mNode2RotZ = 0x2800;
    mPathSpeed = 20.0;
    mSpecScale = 0.75;
}

/* 000002B8-000002D8       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c* i_this) {
    return ((daOship_c *)i_this)->_createHeap();
}

/* 000002D8-00000324       .text nodeControl_CB__FP7J3DNodei */
static BOOL nodeControl_CB(J3DNode* i_nodeP, int i_calcTiming) {
    if (i_calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model_p = j3dSys.getModel();
        daOship_c* this_p = (daOship_c *) model_p->getUserArea();
        if (this_p) {
            this_p->_nodeControl(i_nodeP, model_p);
        }
    }
    return true;
}

/* 00000324-00000410       .text _nodeControl__9daOship_cFP7J3DNodeP8J3DModel */
void daOship_c::_nodeControl(J3DNode* i_nodeP, J3DModel* i_modelP) {
    J3DJoint* jnt_p = (J3DJoint *) i_nodeP;
    s32 jnt_no = jnt_p->getJntNo();

    mDoMtx_stack_c::copy(i_modelP->getAnmMtx(jnt_no));
    csXyz aim_rot(0, 0, 0);

    switch (jnt_no) {
        case 1:
            aim_rot.x = mAimRotY;
            break;
        case 2:
            mDoMtx_stack_c::ZrotM(l_HIO.mNode2RotZ);
            aim_rot.z = -mAimRotX;
            break;
        default:
            break;
    }

    mDoMtx_stack_c::ZXYrotM(aim_rot.x, aim_rot.y, aim_rot.z);
    cMtx_copy(mDoMtx_stack_c::get(), j3dSys.mCurrentMtx);
    i_modelP->setAnmMtx(jnt_no, mDoMtx_stack_c::get());
}

/* 0000044C-00000488       .text pathMove_CB__FP4cXyzP4cXyzP4cXyzPv */
int pathMove_CB(cXyz* param_1, cXyz* param_2, cXyz* param_3, void* i_this) {
    return ((daOship_c *)i_this)->_pathMove(param_1, param_2, param_3);
}

/* 00000488-00000718       .text _pathMove__9daOship_cFP4cXyzP4cXyzP4cXyz */
BOOL daOship_c::_pathMove(cXyz* p_pos, cXyz* p_p0, cXyz* p_p1) {
    mPathP0.set(*p_p0);
    mPathP0.y = current.pos.y;

    mPathP1.set(*p_p1);
    mPathP1.y = current.pos.y;

    cXyz diff = mPathP1 - mPathP0;

    if (!diff.normalizeRS()) {
        return TRUE;
    }

    s16 target = cM_atan2s(diff.x, diff.z);
    s16 speed_f_phase = cLib_addCalcAngleS(&current.angle.y, target, 8, 0x200, 8);
    f32 final_speed_f = std::fabsf(cM_scos(speed_f_phase)) * speedF;
    cLib_chasePosXZ(p_pos, mPathP1, final_speed_f);


    if ((*p_pos - mPathP1).absXZ() < final_speed_f * (REG12_F(5) + 1.0f) || 
        (*p_pos - mPathP1).absXZ() == 0.0f) {
        return TRUE;
    } 

    return FALSE;
}

/* 00000718-000007E4       .text pathMove__9daOship_cFv */
void daOship_c::pathMove() {
    cLib_addCalc2(&speedF, mVelocityFwdTarget, 0.1f, 2.0f);
    dLib_pathMove(&mOrigPos, &m2D4, mpPath, speedF, pathMove_CB, this);
    cLib_addCalcPosXZ2(&current.pos, mOrigPos, REG12_F(0) + 0.01f, speedF);
    
    if (speedF != 0.0f && mVelocityFwdTarget != 0.0f) {
        s16 target = cLib_targetAngleY(&current.pos, &mOrigPos);
        cLib_addCalcAngleS2(&shape_angle.y, target, 8, 0x100);
    }
}

/* 000007E4-000008A0       .text plFireRepeat__9daOship_cFv */
bool daOship_c::plFireRepeat() {
    if (dComIfGp_getShipActor() && dComIfGp_getShipActor()->checkShootCannon()) {
        mPlFireTimer = cM_rndF(20.0f) + 10.0f;
        mAimCounter++;
    }

    if (mPlFireTimer != -1 && cLib_calcTimer(&mPlFireTimer) == 0) {
        modeProcInit(MODE_ATTACK);
        mPlFireTimer = -1;
        return true;
    }

    return false;
}

/* 000008A0-000008F8       .text lineCheck__9daOship_cFP4cXyzP4cXyz */
bool daOship_c::lineCheck(cXyz* param_1, cXyz* param_2) {
    mLinChk.Set(param_1, param_2, this);

    /* This cast may be fake */ 
    return (BOOL)dComIfG_Bgsp()->LineCross(&mLinChk);
}

/* 000008F8-00000990       .text changeModeByRange__9daOship_cFv */
void daOship_c::changeModeByRange() {
    f32 search_ac_dist = fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0));
    Mode_e proc_no;

    if (search_ac_dist < l_HIO.mDistRangeA) {
        proc_no = MODE_RANGE_A;
    } else if (search_ac_dist < l_HIO.mDistRangeB) {
        proc_no = MODE_RANGE_B;
    } else if (search_ac_dist < l_HIO.mDistRangeC) {
        proc_no = MODE_RANGE_C;
    } else {
        proc_no = MODE_RANGE_D;
    }

    if (mCurrentProc != proc_no) {
        modeProcInit(proc_no);
    } 
}

/* 00000990-00000C08       .text createWave__9daOship_cFv */
void daOship_c::createWave() {
    static const JGeometry::TVec3<f32> wave_l_direction(0.5, 1.0f, -0.3f);
    static const JGeometry::TVec3<f32> wave_r_direction(-0.5, 1.0f, -0.3f);

    if (!mWaveCallback1.getEmitter()) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_0037, &mWavePos, &mWaveRot, NULL, 0xFF, &mWaveCallback1);
        if (mWaveCallback1.getEmitter()) {
            mWaveCallback1.getEmitter()->setDirection(wave_l_direction);
        }
    }

    if (!mWaveCallback2.getEmitter()) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_0037, &mWavePos, &mWaveRot, NULL, 0xFF, &mWaveCallback2);
        if (mWaveCallback2.getEmitter()) {
            mWaveCallback2.getEmitter()->setDirection(wave_r_direction);
        }
    }

    if (!mSplashCallback.getEmitter()) {
        dComIfGp_particle_set(dPa_name::ID_COMMON_0035, &mWavePos, &mWaveRot, NULL, 0xFF, &mSplashCallback);
    }

    if (!mTrackCallback.getEmitter()) {
        dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0036, &mTrackPos, &shape_angle, NULL, 0, &mTrackCallback);
        JPABaseEmitter* emitter_p = mTrackCallback.getEmitter();
        if (emitter_p) {
            Vec vec_scale = { 3.0f, 3.0f, 3.0f };
            JGeometry::TVec3<f32> scale = vec_scale;
            emitter_p->setGlobalDynamicsScale(scale);
            emitter_p->setGlobalParticleScale(scale);
        }
    }
}

/* 00000C08-00000E50       .text setWave__9daOship_cFv */
void daOship_c::setWave() {
    f32 track_vel;
    f32 wave_vel_fade;
    f32 splash_scale_target;
    f32 wave_max_velocity;

    track_vel = l_HIO.mTrackVel;
    wave_vel_fade = l_HIO.mWaveVelFade1;
    splash_scale_target = l_HIO.mSplashScaleTimerTarget;
    wave_max_velocity = l_HIO.mWaveMaxVelocity;

    if (fopAcM_GetSpeedF(this) <= 2.0f || mCurrentProc == 3) {
        wave_vel_fade = 0.0f;
        splash_scale_target = 0.0f;
        mTrackCallback.stop();
    } else {
        createWave();
    }

    mWavePos.y = dLib_getWaterY(mWavePos, mAcch);
    mWaveRot.y = shape_angle.y;

    if (mTrackCallback.getEmitter()) {
        mTrackCallback.setIndirectTexData(l_HIO.mTrackOffsY, l_HIO.mTrackScaleY);
        mTrackCallback.setSpeed(track_vel);
        mTrackCallback.setWaterY(mWavePos.y);

        if (mAcch.ChkWaterHit()) {
            track_vel = mAcch.m_wtr.GetHeight();
        } else {
            track_vel = -G_CM3D_F_INF;
        }

        mTrackCallback.setWaterFlatY(track_vel);
        mTrackCallback.setLimitSpeed(3.0f);
    }

    mWaveCallback2.setSpeed(wave_vel_fade);
    mWaveCallback1.setSpeed(wave_vel_fade);

    mWaveCallback2.setMaxSpeed(wave_max_velocity);
    mWaveCallback1.setMaxSpeed(wave_max_velocity);

    mWaveCallback2.setPitch(l_HIO.mWaveVelFadeOffs + 1.0f);
    mWaveCallback1.setPitch(1.0f - l_HIO.mWaveVelFadeOffs);

    cXyz collapse_pos_0_cb2 = l_HIO.mWaveCollapsePos0;
    cXyz collapse_pos_1_cb2 = l_HIO.mWaveCollapsePos1;
    cXyz collapse_pos_0_cb1 = collapse_pos_0_cb2;
    cXyz collapse_pos_1_cb1 = collapse_pos_1_cb2;

    mWaveCallback2.setAnchor(&collapse_pos_0_cb2, &collapse_pos_1_cb2);
    
    collapse_pos_0_cb1.x *= -1.0f;
    collapse_pos_1_cb1.x *= -1.0f;
    mWaveCallback1.setAnchor(&collapse_pos_0_cb1, &collapse_pos_1_cb1);

    mWaveCallback2.setMaxDisSpeed(l_HIO.mWaveVelSpeed);
    mWaveCallback1.setMaxDisSpeed(l_HIO.mWaveVelSpeed);

    cLib_addCalc2(&mSplashScaleTimer, splash_scale_target, 0.1f, 10.0f);
    mSplashCallback.setSpeed(mSplashScaleTimer);
    mSplashCallback.setMaxSpeed(l_HIO.mSplashMaxScaleTimer);
}

/* 00000E50-00001184       .text checkTgHit__9daOship_cFv */
bool daOship_c::checkTgHit() {
    mStts.Move();
    if (l_HIO.m05) {
        health = 0;
        modeProcInit(MODE_DELETE);
        return true;
    }

    if (cLib_calcTimer(&mHitTimer) == 0) {
        cXyz hit_pos;
        CcAtInfo at_info;
        cCcD_Obj* hit_obj_p;
        at_info.pParticlePos = NULL;

        for (int i = 0; i < ARRAY_SSIZE(mCyl); i++) {
            hit_obj_p = mCyl[i].GetTgHitObj();
            hit_pos = *mCyl[i].GetTgHitPosP();
            at_info.mpObj = mCyl[i].GetTgHitObj();
            if (hit_obj_p) break;
        }

        if (!hit_obj_p) {
            return false;
        }

        bool is_bomb_attack = true;
        switch (hit_obj_p->GetAtType()) {
            case AT_TYPE_BOMB:
                health--;
                break;
            default:
                is_bomb_attack = false;
                break;
        }

        if (is_bomb_attack) {
            if (mSmokePtclCount < 3 && !mSmokeFollowCallback[mSmokePtclCount].getEmitter()) {
                s16 target_angle = cLib_targetAngleY(&current.pos, &hit_pos);
                this->mSmokeRotY[mSmokePtclCount] = target_angle - shape_angle.y;
                mSmokeRot[mSmokePtclCount] = shape_angle;
                mSmokeRot[mSmokePtclCount].y += mSmokeRotY[mSmokePtclCount];
                dComIfGp_particle_set(
                    dPa_name::ID_COMMON_03E1, 
                    &mSmokePos, &mSmokeRot[mSmokePtclCount], 
                    &scale, 0xff, &mSmokeFollowCallback[mSmokePtclCount], 
                    fopAcM_GetRoomNo(this)
                );
                mSmokePtclCount++;
            }

            daPy_py_c* player_p = (daPy_py_c *) dComIfGp_getPlayer(0);
            dComIfGp_particle_set(dPa_name::ID_COMMON_0010, &hit_pos);
            
            cXyz particle_scale(2.0f, 2.0f, 2.0f);
            dComIfGp_particle_set(dPa_name::ID_COMMON_BIG_HIT, &hit_pos, &player_p->shape_angle, &particle_scale);
        
            mHitTimer = 5;

            if (health <= 0) {
                fopAcM_seStart(this, JA_SE_LK_LAST_HIT, 0);
                modeProcInit(MODE_DELETE);
            } else {
                mAimCounter = 6;
                modeProcInit(MODE_DAMAGE);
            }
            return true;
        }
    }
    return false;
}

/* 00001184-000011F4       .text setAttention__9daOship_cFv */
void daOship_c::setAttention() {
    attention_info.position = current.pos;
    eyePos = current.pos;
    if (!dComIfGp_event_runCheck()) {
        attention_info.position.y += l_HIO.mAttentionOffsY;
        eyePos.y += l_HIO.mEyeOffsY;
    }
}

/* 000011F4-00001330       .text setCollision__9daOship_cFv */
void daOship_c::setCollision() {
    static f32 cyl_offset[5] = {
        50.0f, -50.0f, 0.0f,
        180.0f, -180.0f
    };

    static f32 cyl_r[5] = {
        170.0f, 170.0f, 290.0f,
        200.0f, 200.0f
    };

    static f32 cyl_h[5] = {
        500.0f, 500.0f, 190.0f,
        190.0f, 190.0f
    };

    f32 sin_angle_y = cM_ssin(current.angle.y);
    f32 cos_angle_y = cM_scos(current.angle.y);
    
    dCcD_Cyl* curr_cyl_p = mCyl;
    for (int i = 0; i < ARRAY_SSIZE(mCyl); i++, curr_cyl_p++) {
        cXyz cyl_center(
            current.pos.x + sin_angle_y * cyl_offset[i],
            current.pos.y - 30.0f,
            current.pos.z + cos_angle_y * cyl_offset[i]
        );
        curr_cyl_p->SetC(cyl_center);
        curr_cyl_p->SetR(cyl_r[i]);
        curr_cyl_p->SetH(cyl_h[i]);
        dComIfG_Ccsp()->Set(curr_cyl_p);
    }
}

/* 00001330-000014D4       .text attackCannon__9daOship_cFi */
void daOship_c::attackCannon(int i_index) {
    csXyz rot = shape_angle;
    rot.x -= mAimRotX;
    rot.y += mAimRotY;
    
    int bomb_prm = daBomb_c::prm_make(daBomb_c::STATE_4, true, true);
    daBomb_c* bomb_p = (daBomb_c *) fopAcM_fastCreate(
        PROC_BOMB, bomb_prm, 
        &mBombSpawnPos, tevStr.mRoomNo, 
        &rot
    );
    
    mBombPcId[i_index] = fpcM_GetID(bomb_p);
    mBombAlloc[i_index] = true;

    bomb_p->setNoGravityTime(l_HIO.mBombNoGravityTime);
    fopAcM_SetSpeedF(bomb_p, l_HIO.mBombSpeed * cM_scos(rot.x));

    bomb_p->speed.y = -(l_HIO.mBombSpeed * cM_ssin(rot.x));

    fopAcM_SetGravity(bomb_p, l_HIO.mBombAcceleration);
    bomb_p->scale.setall(2.0f);

    mDoAud_seStart(JA_SE_LK_SHIP_CANNON_FIRE, &mBombSpawnPos);
}

/* 000014D4-000017CC       .text setMtx__9daOship_cFv */
void daOship_c::setMtx() {
    f32 sway = f32(mAttackSwayAmount) * f32(REG12_S(3) + 1);
    dLib_waveRot(&current.pos, sway, &mWave);
    
    s16 temp_r30 = f32(mAttackSwayAmount * (REG12_S(5) + 10)) * cM_ssin(mAttackSwayTimer);
    s16 temp_r0 = shape_angle.y + fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));
    s16 temp_r4 = f32(temp_r30) * cM_scos(temp_r0);
    s16 temp_r3 = f32(temp_r30) * cM_ssin(temp_r0);

    if (mCurrentProc != 3) {
        shape_angle.x = mWave.mRotX + temp_r4;
        shape_angle.z = mWave.mRotZ + temp_r3;
    }

    mpModel->setBaseScale(scale);
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::XYZrotM(shape_angle.x, 0, shape_angle.z);
    mDoMtx_stack_c::YrotM(shape_angle.y);
    cMtx_copy(mDoMtx_stack_c::get(), mFlagMtx);
    mpModel->setBaseTRMtx(mDoMtx_stack_c::get());

    Vec o = { 0.0f, 0.0f, 0.0f };

    o.y = l_HIO.mAttentionOffsY;
    mDoMtx_stack_c::multVec(&o, &attention_info.position);
    
    o.y = l_HIO.mEyeOffsY;
    mDoMtx_stack_c::multVec(&o, &eyePos);

    o.y = 0.0f;
    o.z = l_HIO.mWaveOffsZ;
    mDoMtx_stack_c::multVec(&o, &mWavePos);

    o.z = l_HIO.mTrackOffsZ;
    mDoMtx_stack_c::multVec(&o, &mTrackPos);
}

/* 000017CC-000017EC       .text modeWaitInit__9daOship_cFv */
void daOship_c::modeWaitInit() {
    changeModeByRange();
}

/* 000017EC-0000180C       .text modeWait__9daOship_cFv */
void daOship_c::modeWait() {
    changeModeByRange();
}

/* 0000180C-00001820       .text modeRangeAInit__9daOship_cFv */
void daOship_c::modeRangeAInit() {
    mAttackTimer = l_HIO.mAttackDelayA;
}

/* 00001820-00001900       .text modeRangeA__9daOship_cFv */
void daOship_c::modeRangeA() {
    if ((mSubMode == 2 || mSubMode == 1) && mPathId != 0xFF) {
        mVelocityFwdTarget = l_HIO.mPathSpeed;
        pathMove();
    }

    mTargetPos = dComIfGp_getPlayer(0)->current.pos;
    current.pos.y = dLib_getWaterY(current.pos, mAcch);

    if (!checkTgHit() && !plFireRepeat()) {
        if (cLib_calcTimer(&mAttackTimer) == 0) {
            modeProcInit(MODE_ATTACK);
        } else {
            changeModeByRange();
        }
    }
}

/* 00001900-00001934       .text modeRangeBInit__9daOship_cFv */
void daOship_c::modeRangeBInit() {
    if (mSubMode == 0) {
        mAttackTimer = l_HIO.mAttackDelayA;
        return;
    }
    
    mAttackTimer = l_HIO.mAttackDelayB;
}

/* 00001934-00001A14       .text modeRangeB__9daOship_cFv */
void daOship_c::modeRangeB() {
    if ((mSubMode == 2 || mSubMode == 1) && mPathId != 0xFF) {
        mVelocityFwdTarget = l_HIO.mPathSpeed;
        pathMove();
    }

    mTargetPos = dComIfGp_getPlayer(0)->current.pos;
    current.pos.y = dLib_getWaterY(current.pos, mAcch);

    if (!checkTgHit() && !plFireRepeat()) {
        if (cLib_calcTimer(&mAttackTimer) == 0) {
            modeProcInit(MODE_ATTACK);
        } else {
            changeModeByRange();
        }
    }
}

/* 00001A14-00001A28       .text modeRangeCInit__9daOship_cFv */
void daOship_c::modeRangeCInit() {
    mAttackTimer = l_HIO.mAttackDelayB;
}

/* 00001A28-00001AFC       .text modeRangeC__9daOship_cFv */
void daOship_c::modeRangeC() {
    if (mSubMode == 2 && mPathId != 0xFF) {
        mVelocityFwdTarget = l_HIO.mPathSpeed;
        pathMove();
    }

    mTargetPos = dComIfGp_getPlayer(0)->current.pos;
    current.pos.y = dLib_getWaterY(current.pos, mAcch);

    if (!checkTgHit() && !plFireRepeat()) {
        if (cLib_calcTimer(&mAttackTimer) == 0) {
            modeProcInit(MODE_ATTACK);
        } else {
            changeModeByRange();
        }
    }
}

/* 00001AFC-00001B00       .text modeRangeDInit__9daOship_cFv */
void daOship_c::modeRangeDInit() {
    /* Empty method */
}

/* 00001B00-00001B7C       .text modeRangeD__9daOship_cFv */
void daOship_c::modeRangeD() {
    if (!checkTgHit()) {
        if (mSubMode == 2 && mPathId != 0xFF) {
            mVelocityFwdTarget = l_HIO.mPathSpeed;
            pathMove();
        }
        current.pos.y = dLib_getWaterY(current.pos, mAcch);
        changeModeByRange();
    }
}

/* 00001B7C-00001B90       .text modeDamageInit__9daOship_cFv */
void daOship_c::modeDamageInit() {
    mAttackTimer = 60;
    mAttackSwayAmount = 300;
}

/* 00001B90-00001C98       .text modeDamage__9daOship_cFv */
void daOship_c::modeDamage() {
    mAttackSwayTimer += REG12_S(2) + 0x1830;
    cLib_addCalcAngleS2(&mAttackSwayAmount, 0, 10, 10);

    f32 final_sway_amt = (mAttackSwayAmount * cM_ssin(mAttackSwayTimer) * 0.025f);
    f32 water_height = dLib_getWaterY(current.pos, mAcch);
    current.pos.y = final_sway_amt + water_height;

    if (!checkTgHit() && (cLib_calcTimer(&mAttackTimer) == 0 || mAttackTimer <= -1)) {
        changeModeByRange();
    }
}

/* 00001C98-00001EC8       .text modeAttackInit__9daOship_cFv */
void daOship_c::modeAttackInit() {
    mAttackTimer = -1;
    mTargetPos = dComIfGp_getPlayer(0)->current.pos;

    f32 target_to_curr_dist = (current.pos - mTargetPos).absXZ();

    f32 target_dist = 0.0f;
    if (target_to_curr_dist > l_HIO.mBadAimAdjustDistanceStart) {
        target_dist = (target_to_curr_dist - l_HIO.mBadAimAdjustDistanceStart) * 0.5f;
    }

    target_dist += 300.0f;

    if (cM_rndF(100.0f) < 10.0f) {
        target_dist = 0.0f;
    }

    if (dComIfGp_checkPlayerStatus0(0, daPyStts0_UNK1000000_e | daPyStts0_SWIM_e)) {
        mAimCounter = 0;
        target_dist += 3000.0f;
    } else if (mAimCounter < 6) {
        target_dist += (6 - mAimCounter) * 500.0f;
    }

    if (l_HIO.m08) {
        target_dist = 0.0f;
    }

    s16 angle = fopAcM_searchActorAngleY(this, dComIfGp_getPlayer(0));

    mTargetPos.x -= target_dist * cM_ssin(angle);
    mTargetPos.z -= target_dist * cM_scos(angle);
}

/* 00001EC8-00002044       .text modeAttack__9daOship_cFv */
void daOship_c::modeAttack() {
    if (mPathId != 0xFF) {
        mVelocityFwdTarget = 0.0f;
        pathMove();
    }

    if (!checkTgHit()) {
        current.pos.y = dLib_getWaterY(current.pos, mAcch);
        if (mAttackTimer <= -1) {
            cLib_distanceAngleS(mAimRotY, mAimRotYTarget);
            cLib_distanceAngleS(mAimRotX, mAimRotXTarget);
            mAttackTimer = -1;
            if (l_HIO.m06) {
                changeModeByRange();
            } else if (lineCheck(&mSmokePos, &mTargetPos)) {
                changeModeByRange();
            } else {
                for (int i = 0; i < ARRAY_SSIZE(mBombAlloc); i++) {
                    if (!mBombAlloc[i] && speedF <= 2.0f) {
                        attackCannon(i);
                        mAttackTimer = 15;
                        mAttackSwayAmount = 100;
                        return;
                    }
                }
            }
        } else if (cLib_calcTimer(&mAttackTimer) == 0) {
            changeModeByRange();
        } else {
            mAttackSwayTimer += REG12_S(2) + 0x1830;
            cLib_addCalcAngleS2(&mAttackSwayAmount, 0, 10, 10);
        }
    } 
}

/* 00002044-00002104       .text modeDeleteInit__9daOship_cFv */
void daOship_c::modeDeleteInit() {
    fopAcM_seStart(this, JA_SE_OBJ_ENEMY_SHIP_SINK, 0);

    for (int i = 0; i < ARRAY_SSIZE(mSmokeFollowCallback); i++) {
        mSmokeFollowCallback[i].end();
    }

    fopAcM_createDisappear(this, &current.pos, 5, daDisItem_IBALL_e);
}

/* 00002104-00002414       .text modeDelete__9daOship_cFv */
void daOship_c::modeDelete() {
    if (isSpecial()) {
        if (eventInfo.checkCommandDemoAccrpt()) {
            s16 temp = cLib_addCalcAngleS(&shape_angle.x, -15000, 0x14, 0x1000, 0x100);
            f32 water_height = dLib_getWaterY(current.pos, mAcch);

            f32 water_height2 = -1000.0f;
            water_height2 += water_height;

            f32 temp2 = cLib_addCalc(&current.pos.y, water_height2, 0.02f, 50.0f, 10.0f);
            
            if (s16(std::abs(temp)) <= 0x100 && std::fabsf(temp2 - water_height) < 500.0f && mSwitchA != 0xFF) {
                dComIfGs_onSwitch(mSwitchA, fopAcM_GetRoomNo(this));
                daSalvage_c* salvage_p = (daSalvage_c *) fopAcM_SearchByName(PROC_Salvage);
                salvage_p->onSalvageForOship(this);
                mDoAud_seStart(JA_SE_READ_RIDDLE_1);
            }
            
            if (dComIfGp_evmng_endCheck("GOLD_SHIP_DELETE")) {
#if VERSION > VERSION_DEMO
                dComIfGs_onEventBit(dSv_event_flag_c::UNK_3E80);
#endif
                dComIfGp_event_onEventFlag(8);
                fopAcM_delete(this);
            }
        } else {
            fopAcM_orderOtherEvent2(this, "GOLD_SHIP_DELETE", dEvtFlag_NOPARTNER_e);
        }        
    } else {
        s16 temp = cLib_addCalcAngleS(&shape_angle.x, -15000, 0x14, 0x1000, 0x100);
        f32 water_height = dLib_getWaterY(current.pos, mAcch);

        f32 water_height2 = -1000.0f;
        water_height2 += water_height;

        f32 temp2 = cLib_addCalc(&current.pos.y, water_height2, 0.02f, 50.0f, 10.0f);

        if (s16(std::abs(temp)) <= 0x100 && std::fabsf(temp2 - water_height) < 500.0f) {
            if (mSwitchA != 0xFF) {
                dComIfGs_onSwitch(mSwitchA, fopAcM_GetRoomNo(this));
                daSalvage_c* salvage_p = (daSalvage_c *) fopAcM_SearchByName(PROC_Salvage);
                salvage_p->onSalvageForOship(this);
            }

            fopAc_ac_c* flag_p = (fopAc_ac_c *) fopAcM_SearchByID(mFlagPcId); 
            if (flag_p) {
                fopAcM_delete(flag_p);
            }
            fopAcM_delete(this);
        }
    }
}

/* 00002414-0000263C       .text modeProc__9daOship_cFQ29daOship_c6Proc_ei */
void daOship_c::modeProc(daOship_c::Proc_e i_procType, int i_procNo) {
    static const ModeEntry mode_tbl[8] = {
        { &daOship_c::modeWaitInit,   &daOship_c::modeWait,   "WAIT"    },
        { &daOship_c::modeAttackInit, &daOship_c::modeAttack, "ATTACK"  },
        { &daOship_c::modeDamageInit, &daOship_c::modeDamage, "DAMAGE"  },
        { &daOship_c::modeDeleteInit, &daOship_c::modeDelete, "DELETE"  },
        { &daOship_c::modeRangeAInit, &daOship_c::modeRangeA, "RANGE_A" },
        { &daOship_c::modeRangeBInit, &daOship_c::modeRangeB, "RANGE_B" },
        { &daOship_c::modeRangeCInit, &daOship_c::modeRangeC, "RANGE_C" },
        { &daOship_c::modeRangeDInit, &daOship_c::modeRangeD, "RANGE_D" }
    };
    
    if (i_procType == PROC_INIT) {
        fopAcM_OnStatus(this, fopAcStts_SHOWMAP_e);
        cLib_onBit<u32>(attention_info.flags, fopAc_Attn_LOCKON_BATTLE_e);
        mCurrentProc = i_procNo;
        (this->*mode_tbl[mCurrentProc].mInitFunc)();
    } else if (i_procType == PROC_EXEC) {
        (this->*mode_tbl[mCurrentProc].mUpdFunc)();
    }
}

/* 0000263C-00002AD4       .text _execute__9daOship_cFv */
bool daOship_c::_execute() {
    attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    attention_info.distances[fopAc_Attn_TYPE_CARRY_e] = 34;

    for (int i = 0; i < ARRAY_SSIZE(mSmokeFollowCallback); i++) {
        if (mSmokeFollowCallback[i].getEmitter()) {
            mSmokeRot[i] = shape_angle;
            mSmokeRot[i].y += mSmokeRotY[i];
            
            Vec vec_scale = { 3.0f, 3.0f, 3.0f };
            JGeometry::TVec3<f32> scale = vec_scale;
            
            JPABaseEmitter* emitter_p = mSmokeFollowCallback[i].getEmitter();

            emitter_p->setGlobalDynamicsScale(scale);
            emitter_p->setGlobalParticleScale(scale);
        }
    }

    for (int i = 0; i < ARRAY_SSIZE(mBombAlloc); i++) {
        if (mBombAlloc[i]) {
            fopAc_ac_c* bomb_p = (fopAc_ac_c *) fopAcM_SearchByID(mBombPcId[i]);

            if (!bomb_p) {
                mBombAlloc[i] = false;
            } else if (l_HIO.m07 && bomb_p->speed.y <= REG12_F(1) + -20.0f) {
                cLib_addCalc2(&bomb_p->speedF, REG12_F(3) + 10.0f, 0.1f, REG12_F(4) + 10.0f);
                bomb_p->speed.y = REG12_F(2) + -20.0f;
            }
        }
    }

    mAimRotYTarget = cLib_targetAngleY(&current.pos, &mTargetPos) - shape_angle.y;

    f32 target_to_curr_dist = (current.pos - mTargetPos).absXZ();

    s32 distance_angle = 0;
    if (target_to_curr_dist > l_HIO.mBadAimAdjustDistanceStart) {
        distance_angle = cLib_distanceAngleS(target_to_curr_dist, l_HIO.mBadAimAdjustDistanceStart);
        if (distance_angle > l_HIO.mBadAimMax) {
            distance_angle = l_HIO.mBadAimMax;
        }
    }

    mAimRotXTarget = cLib_targetAngleX(&current.pos, &mTargetPos);
    mAimRotXTarget += distance_angle;

    cLib_addCalcAngleS2(&mAimRotX, mAimRotXTarget, 6, 0x300);
    cLib_addCalcAngleS2(&mAimRotY, mAimRotYTarget, 6, 0x300);

    modeProc(PROC_EXEC, MODE_NULL);

    mpModel->calc();

    Vec bomb_offset = { 0.0f, 0.0f, 0.0f };
    bomb_offset = l_HIO.mBombOffset;
    cMtx_multVec(mpModel->getAnmMtx(2), &bomb_offset, &mBombSpawnPos);
    
    Vec smoke_offset = { 0.0f, 0.0f, 0.0f };
    cMtx_multVec(mpModel->getAnmMtx(1), &smoke_offset, &mSmokePos);

    setAttention();
    setCollision();
    setMtx();

    s32 cull_box_check = fopAcM_checkCullingBox(mpModel->getBaseTRMtx(), -300.0f, -100.0f, -650.0f, 300.0f, 700.0f, 800.0f);

    if (fopAcM_GetSpeedF(this) <= 2.0f || 
        (cull_box_check & 0xFF) || 
        fopAcM_searchActorDistanceXZ(this, dComIfGp_getPlayer(0)) > 18000.0f) {
        mWaveCallback2.remove();
        mWaveCallback1.remove();
        mSplashCallback.remove();
        mTrackCallback.stop();        
    } else {
        setWave();
    }

    if (!isSpecial()) {
        daMajuu_Flag_c* majuu_flag_p = (daMajuu_Flag_c *) fopAcM_SearchByID(mFlagPcId);
        if (majuu_flag_p) {
            majuu_flag_p->mpParentMtx = mFlagMtx;
            majuu_flag_p->mpParentPos = &mFlagOffset;
        }
    }

    return false;
}

static void dummy() {
    static const GXColor dummy_c1 = { 0xFF, 0x00, 0x00, 0x80 };
    static const GXColor dummy_c2 = { 0xFF, 0xFF, 0x00, 0x80 };
    static const GXColor dummy_c3 = { 0xFF, 0x00, 0x00, 0x80 };
    static const GXColor dummy_c4 = { 0xFF, 0x00, 0xFF, 0x80 };
    static const GXColor dummy_c5 = { 0x00, 0xFF, 0x00, 0x80 };
}

/* 00002AD4-00002B54       .text _draw__9daOship_cFv */
bool daOship_c::_draw() {
    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(mpModel, &tevStr);
    dDlst_texSpecmapST(&eyePos, &tevStr, mpModel->getModelData(), l_HIO.mSpecScale);
    mDoExt_modelEntryDL(mpModel);
    return true;
}

/* 00002B54-00002DFC       .text createInit__9daOship_cFv */
void daOship_c::createInit() {
    itemTableIdx = dComIfGp_CharTbl()->GetNameIndex("Oship", 0);

    mOrigPos = current.pos;

    max_health = 3;
    health = max_health;

    mPlFireTimer = -1;
    changeModeByRange();

    attention_info.flags = fopAc_Attn_LOCKON_BATTLE_e;
    attention_info.distances[fopAc_Attn_TYPE_CARRY_e] = DEMO_SELECT(43, 34);

    mStts.Init(0xFF, 0, this);
    for (int i = 0; i < ARRAY_SSIZE(mCyl); i++) {
        mCyl[i].Set(m_cyl_src);
        mCyl[i].SetStts(&mStts);
    }

    mWave.mAnimX = cM_rndF(32768.0f);
    mWave.mAnimZ = cM_rndF(32768.0f);

    setMtx();
    mpModel->calc();
    cullMtx = mpModel->getBaseTRMtx();

    fopAcM_setCullSizeBox(
        this, 
        -300.0f, -100.0f, 
        -650.0f, 300.0f, 
        700.0f, 800.0f
    );
    fopAcM_setCullSizeFar(this, 10.0f);

    if (!isSpecial()) {
        mFlagPcId = fopAcM_create(
            PROC_MAJUU_FLAG, 4, 
            &current.pos, tevStr.mRoomNo, 
            &current.angle
        );
        static cXyz flag_offset = cXyz(0.0f, 800.0f, 0.0f);
        mFlagOffset = flag_offset;
    }

    if (mPathId != 0xFF) {
        mpPath = dPath_GetRoomPath(mPathId, current.roomNo);
    }

    createWave();

    mAcchCir.SetWall(30.0f, 30.0f);
    mAcch.Set(
        fopAcM_GetPosition_p(this), 
        fopAcM_GetOldPosition_p(this), 
        this, 1, &mAcchCir, 
        fopAcM_GetSpeed_p(this)
    );

    mAcch.SetWallNone();
    mAcch.SetRoofNone();
}

/* 00002DFC-00002F44       .text _createHeap__9daOship_cFv */
BOOL daOship_c::_createHeap() {
    int file_index;

    file_index = OSHIP_BDL_VBTSP;
    if (isSpecial()) {
        file_index = OSHIP_BDL_VBTST;
    }

    J3DModelData* modelData = (J3DModelData *) dComIfG_getObjectRes(m_arc_name, file_index);
    JUT_ASSERT(DEMO_SELECT(1616, 1573), modelData != NULL);

    mpModel = mDoExt_J3DModel__create(modelData, 0x80000, 0x37441422);

    if (!mpModel) {
        return FALSE;
    }

    mpModel->setUserArea((u32) this);
    for (u16 i = 0; i < modelData->getJointNum(); i++) {
        switch (i) {
            case 1:
            case 2:
                modelData->getJointNodePointer(i)->setCallBack(nodeControl_CB);
                break;
            default:
                break;
        }
    }

    return TRUE;
}

/* 00002F44-00002F90       .text getArg__9daOship_cFv */
void daOship_c::getArg() {
    u32 prms = fopAcM_GetParam(this);

    mSubMode = prms & 0xFF;
    mTriforce = (prms >> 8) & 0xF;
    mRandomSalvagePoint = (prms >> 12) & 0xF;
    mPathId = (prms >> 16) & 0xFF;
    mSwitchA = (prms >> 24) & 0xFF;

    s16 home_angle_x = home.angle.x;

    mSwitchB = home_angle_x & 0xFF;
    mModelType = (home_angle_x >> 8) & 0xFF;

    home.angle.x = 0;
    current.angle.x = 0;
    shape_angle.x = 0;
}

/* 00002F90-000030EC       .text _create__9daOship_cFv */
cPhs_State daOship_c::_create() {
    fopAcM_ct(this, daOship_c);

    cPhs_State state = dComIfG_resLoad(&mPhs, m_arc_name);
    
    if (state == cPhs_COMPLEATE_e) {
        getArg();

        if (mSwitchA != 0xFF && dComIfGs_isSwitch(mSwitchA, fopAcM_GetRoomNo(this))) {
            return cPhs_ERROR_e;
        }

        if (mSwitchB != 0xFF && !dComIfGs_isSwitch(mSwitchB, fopAcM_GetRoomNo(this))) {
            return cPhs_ERROR_e;
        }

        if (mTriforce != 0xF) {
            if (!dComIfGs_isCollectMapTriforce(mTriforce + 1)) {
                return cPhs_ERROR_e;
            }
            if (mRandomSalvagePoint != 0xF && mRandomSalvagePoint != dComIfGs_getRandomSalvagePoint()) {
                return cPhs_ERROR_e;
            }
        }
        
        if (!fopAcM_entrySolidHeap(this, createHeap_CB, m_heapsize)) {
            return cPhs_ERROR_e;
        }

        createInit();
    }

    return state;
}

/* 00003E78-00003F20       .text _delete__9daOship_cFv */
bool daOship_c::_delete() {
    dComIfG_resDelete(&mPhs, m_arc_name);

    for (int i = 0; i < ARRAY_SSIZE(mSmokeFollowCallback); i++) {
        mSmokeFollowCallback[i].end();
    }

    mWaveCallback2.remove();
    mWaveCallback1.remove();
    mSplashCallback.remove();
    mTrackCallback.remove();
#if VERSION > VERSION_DEMO
    mDoAud_seDeleteObject(&mBombSpawnPos);
#endif 

    return true;
}

/* 00003F20-00003F40       .text daOshipCreate__FPv */
static cPhs_State daOshipCreate(void* i_this) {
    return ((daOship_c*)i_this)->_create();
}

/* 00003F40-00003F64       .text daOshipDelete__FPv */
static BOOL daOshipDelete(void* i_this) {
    return ((daOship_c*)i_this)->_delete();
}

/* 00003F64-00003F88       .text daOshipExecute__FPv */
static BOOL daOshipExecute(void* i_this) {
    return ((daOship_c*)i_this)->_execute();
}

/* 00003F88-00003FAC       .text daOshipDraw__FPv */
static BOOL daOshipDraw(void* i_this) {
    return ((daOship_c*)i_this)->_draw();
}

/* 00003FAC-00003FB4       .text daOshipIsDelete__FPv */
static BOOL daOshipIsDelete(void*) {
    return TRUE;
}

static actor_method_class daOshipMethodTable = {
    (process_method_func)daOshipCreate,
    (process_method_func)daOshipDelete,
    (process_method_func)daOshipExecute,
    (process_method_func)daOshipIsDelete,
    (process_method_func)daOshipDraw,
};

actor_process_profile_definition g_profile_OSHIP = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_OSHIP,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daOship_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_OSHIP,
    /* Actor SubMtd */ &daOshipMethodTable,
    /* Status       */ fopAcStts_CULL_e | fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ENEMY_e,
    /* CullType     */ fopAc_CULLBOX_CUSTOM_e,
};
