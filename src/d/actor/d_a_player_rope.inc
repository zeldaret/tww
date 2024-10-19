/**
 * d_a_player_rope.inc
 *
 * Code relating to the Grappling Hook item.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_himo2.h"
#include "d/d_attention.h"
#include "f_op/f_op_actor_mng.h"
#include "m_Do/m_Do_audio.h"

/* 80142D08-80142D68       .text checkRopeAnime__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkRopeAnime() const {
    /* Nonmatching */
}

/* 80142D68-80142E0C       .text freeRopeItem__9daPy_lk_cFv */
void daPy_lk_c::freeRopeItem() {
    /* Nonmatching */
}

/* 80142E0C-80142E98       .text checkRopeRoofHit__9daPy_lk_cFs */
BOOL daPy_lk_c::checkRopeRoofHit(s16) {
    /* Nonmatching */
}

/* 80142E98-80142FC8       .text changeRopeSwingProc__9daPy_lk_cFv */
void daPy_lk_c::changeRopeSwingProc() {
    /* Nonmatching */
}

/* 80142FC8-801430D4       .text changeRopeEndProc__9daPy_lk_cFi */
void daPy_lk_c::changeRopeEndProc(int) {
    /* Nonmatching */
}

/* 801430D4-80143138       .text checkSpecialRope__9daPy_lk_cFv */
BOOL daPy_lk_c::checkSpecialRope() {
    /* Nonmatching */
}

/* 80143138-8014327C       .text changeRopeToHangProc__9daPy_lk_cFv */
void daPy_lk_c::changeRopeToHangProc() {
    /* Nonmatching */
}

/* 8014327C-80143694       .text checkRopeSwingWall__9daPy_lk_cFP4cXyzP4cXyzPsPf */
BOOL daPy_lk_c::checkRopeSwingWall(cXyz*, cXyz*, s16*, f32*) {
    /* Nonmatching */
    static JGeometry::TVec3<f32> dynamic_scale;
    static JGeometry::TVec3<f32> particle_scale;
}

/* 80143694-80143A44       .text setBlendRopeMoveAnime__9daPy_lk_cFi */
void daPy_lk_c::setBlendRopeMoveAnime(int) {
    /* Nonmatching */
}

/* 80143A44-80143C5C       .text throwRope__9daPy_lk_cFv */
void daPy_lk_c::throwRope() {
    /* Nonmatching */
}

/* 80143C5C-80143DF4       .text checkNextActionRopeReady__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextActionRopeReady() {
    /* Nonmatching */
}

/* 80143DF4-80143EAC       .text checkNextRopeMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkNextRopeMode() {
    /* Nonmatching */
}

/* 80143EAC-80143F3C       .text checkHangRopeActorNull__9daPy_lk_cFv */
BOOL daPy_lk_c::checkHangRopeActorNull() {
    /* Nonmatching */
}

/* 80143F3C-80144038       .text procRopeSubject_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeSubject_init() {
    if(mCurProc == daPyProc_ROPE_SUBJECT_e) {
        return false;
    }

    commonProcInit(daPyProc_ROPE_SUBJECT_e);

    mVelocity = 0.0f;

    if(fopAcM_GetParam(mActorKeepEquip.getActor()) == 0) {
        setActAnimeUpper(LKANM_BCK_ROPETHROWWAIT, UPPER_MOVE2_e, 0.0f, 0.0f, -1, -1.0f);
        setSingleMoveAnime(ANM_ATNRS, 0.0f, 0.0f, -1, daPy_HIO_rope_c0::m.field_0x54);
    }

    dComIfGp_setPlayerStatus0(0, daPyStts0_ROPE_AIM_e);

    current.angle.y = shape_angle.y;

    mDoAud_seStart(0x81C);

    m3570 = 0;
    m3600 = -1.0f;
    m3604 = -1.0f;

    return true;
}

/* 80144038-8014422C       .text procRopeSubject__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeSubject() {
    if(!checkItemModeActorPointer()) {
        return true;
    }

    himo2_class* grapple = (himo2_class*)mActorKeepEquip.getActor();
    if(fopAcM_GetParam(grapple) == 0) {
        dComIfGp_clearPlayerStatus0(0, daPyStts0_UNK40000_e);
    }
    else {
        dComIfGp_setPlayerStatus0(0, daPyStts0_UNK40000_e);
    }

    if(mpAttention->Lockon()) {
        setSpeedAndAngleAtn();
    }

    if(checkNextMode(0) == 0 && setBodyAngleToCamera()) {
        if(mBodyAngle.x > 0) {
            mBodyAngle.x = 0;
        }

        cXyz sight;
        checkSightLine(2200.0f, &sight);
        mSightPacket.onDrawFlg();
        mSightPacket.setPos(&sight);

        if(grapple->setTargetPos(&sight, &m3600, &m3604)) {
            mSightPacket.onDrawFlg();
            if(mSightPacket.getLockFlg()) {
                mSightPacket.incFrame();
                if(mSightPacket.checkSEFrame() == 26) {
                    mSightPacket.resetFrame();
                }

                if(mSightPacket.checkSEFrame() == 0) {
                    mDoAud_seStart(0x820);
                }
            }
            else {
                mSightPacket.onLockFlg();
                mSightPacket.resetFrame();
                mDoAud_seStart(0x820);
            }
        }
        else {
            mSightPacket.offLockFlg();
        }
    }

    return true;
}

/* 8014422C-80144464       .text procRopeReady_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeReady_init() {
    /* Nonmatching */
}

/* 80144464-80144620       .text procRopeReady__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeReady() {
    /* Nonmatching */
}

/* 80144620-80144C58       .text procRopeSwing_init__9daPy_lk_cFP10fopAc_ac_cs */
BOOL daPy_lk_c::procRopeSwing_init(fopAc_ac_c*, s16) {
    /* Nonmatching */
}

/* 80144C58-801456D8       .text procRopeSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeSwing() {
    /* Nonmatching */
    static cXyz local_height_offset;
}

/* 801456D8-801457FC       .text procRopeHangWait_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procRopeHangWait_init(int) {
    /* Nonmatching */
}

/* 801457FC-80145B38       .text procRopeHangWait__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeHangWait() {
    /* Nonmatching */
}

/* 80145B38-80145C3C       .text specialRopeHangUp__9daPy_lk_cFv */
void daPy_lk_c::specialRopeHangUp() {
    /* Nonmatching */
}

/* 80145C3C-80145DBC       .text procRopeUp_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeUp_init() {
    /* Nonmatching */
}

/* 80145DBC-80145F64       .text procRopeUp__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeUp() {
    /* Nonmatching */
}

/* 80145F64-801460EC       .text procRopeDown_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeDown_init() {
    /* Nonmatching */
}

/* 801460EC-80146240       .text procRopeDown__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeDown() {
    /* Nonmatching */
}

/* 80146240-801463E8       .text procRopeSwingStart_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeSwingStart_init() {
    /* Nonmatching */
}

/* 801463E8-80146610       .text procRopeSwingStart__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeSwingStart() {
    /* Nonmatching */
}

/* 80146610-801466E8       .text procRopeMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeMove_init() {
    /* Nonmatching */
}

/* 801466E8-80146848       .text procRopeMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeMove() {
    /* Nonmatching */
}

/* 80146848-801468C4       .text procRopeThrowCatch_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeThrowCatch_init() {
    /* Nonmatching */
}

/* 801468C4-801469A8       .text procRopeThrowCatch__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeThrowCatch() {
    /* Nonmatching */
}

/* 801469A8-80146A44       .text procRopeUpHang_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeUpHang_init() {
    /* Nonmatching */
}

/* 80146A44-80146AF0       .text procRopeUpHang__9daPy_lk_cFv */
BOOL daPy_lk_c::procRopeUpHang() {
    /* Nonmatching */
}
