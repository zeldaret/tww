/**
 * d_a_player.cpp
 * Player - Base Player Class
 */

#include "dolphin/types.h"
#include "d/actor/d_a_player.h"
#include "d/d_com_inf_game.h"
#include "f_op/f_op_camera.h"

/* 801028FC-80102940       .text changePlayer__9daPy_py_cFP10fopAc_ac_c */
void daPy_py_c::changePlayer(fopAc_ac_c* newPlayer) {
    if (!newPlayer) {
        return;
    }
    s8 stayNo = dComIfGp_roomControl_getStayNo();
    if (stayNo != newPlayer->current.roomNo) {
        return;
    }
    dComIfGp_setPlayer(0, newPlayer);
    dComIfGp_getCamera(0)->mCamera.mpPlayerActor = newPlayer;
    dComIfGp_att_ChangeOwner();
}

/* 80102940-80102B84       .text objWindHitCheck__9daPy_py_cFP8dCcD_Cyl */
void daPy_py_c::objWindHitCheck(dCcD_Cyl* cyl) {
    cXyz targetSpeed(0.0f, 0.0f, 0.0f);
    f32 maxStep = 3.0f;
    
    if (cyl->ChkTgHit()) {
        cCcD_Obj* hitObj = cyl->GetTgHitObj();
        if (hitObj && hitObj->ChkAtType(AT_TYPE_WIND)) {
            targetSpeed = *cyl->GetTgRVecP();
            f32 distXZ = cyl->GetTgRVecP()->absXZ();
            maxStep = 1.0f;
            if (distXZ < 1.0f) {
                targetSpeed = (current.pos - *cyl->GetTgHitPosP()) * 30.0f;
                distXZ = targetSpeed.absXZ();
            }
            if (distXZ > 30.0f) {
                targetSpeed *= 30.0f / distXZ;
            }
        }
    }
    
    cLib_addCalc(&field_0x2f8.x, targetSpeed.x, 0.5f, maxStep, 0.5f);
    cLib_addCalc(&field_0x2f8.z, targetSpeed.z, 0.5f, maxStep, 0.5f);
    current.pos.x += field_0x2f8.x;
    current.pos.z += field_0x2f8.z;
}

/* 80102B84-80102BB4       .text execute__25daPy_mtxFollowEcallBack_cFP14JPABaseEmitter */
void daPy_mtxFollowEcallBack_c::execute(JPABaseEmitter* emitter) {
    emitter->setGlobalRTMatrix(mpMtx);
}

/* 80102BB4-80102BF8       .text end__25daPy_mtxFollowEcallBack_cFv */
void daPy_mtxFollowEcallBack_c::end() {
    if (!mpEmitter) {
        return;
    }
    mpEmitter->becomeInvalidEmitter();
    mpEmitter->quitImmortalEmitter();
    mpEmitter->setEmitterCallBackPtr(NULL);
    mpEmitter = NULL;
}

/* 80102BF8-80102C84       .text makeEmitter__25daPy_mtxFollowEcallBack_cFUsPA4_fPC4cXyzPC4cXyz */
JPABaseEmitter* daPy_mtxFollowEcallBack_c::makeEmitter(u16 particleID, MtxP mtx, const cXyz* pos, const cXyz* scale) {
    end();
    mpMtx = mtx;
    return dComIfGp_particle_setP1(particleID, pos, NULL, scale, 0xFF, this);
}

/* 80102C84-80102D14       .text makeEmitterColor__25daPy_mtxFollowEcallBack_cFUsPA4_fPC4cXyzPC8_GXColorPC8_GXColor */
JPABaseEmitter* daPy_mtxFollowEcallBack_c::makeEmitterColor(u16 particleID, MtxP mtx, const cXyz* pos, const GXColor* prmColor, const GXColor* envColor) {
    end();
    mpMtx = mtx;
    return dComIfGp_particle_setP1(particleID, pos, NULL, NULL, 0xFF, this, -1, prmColor, envColor);
}

/* 80102D14-80102D90       .text setDoButtonQuake__9daPy_py_cFv */
void daPy_py_c::setDoButtonQuake() {
    if (checkNoResetFlg0(daPyFlg0_UNK200000)) {
        return;
    }
    
    onNoResetFlg0(daPyFlg0_UNK200000);
    mQuakeTimer = 60;
    
    u32 pattern = 0x0010FFEE;
    dComIfGp_getVibration().StartQuake((u8*)&pattern, 0, 1, cXyz(0.0f, 1.0f, 0.0f));
}

/* 80102D90-80102E18       .text stopDoButtonQuake__9daPy_py_cFi */
void daPy_py_c::stopDoButtonQuake(BOOL param_1) {
    if (mQuakeTimer > 0) {
        mQuakeTimer--;
        if (mQuakeTimer == 0) {
            dComIfGp_getVibration().StopQuake(-1);
        }
    }
    if (param_1 && mQuakeTimer == 0) {
        offNoResetFlg0(daPyFlg0_UNK200000);
    }
}
