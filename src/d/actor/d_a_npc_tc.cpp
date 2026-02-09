/**
 * d_a_npc_tc.cpp
 * NPC - Tingle, Ankle, David Jr. & Knuckle
 */

#include "d/dolzel_rel.h" // IWYU pragma: keep
#include "d/actor/d_a_npc_tc.h"
#include "m_Do/m_Do_ext.h"
#include "d/d_procname.h"
#include "d/d_priority.h"
#include "d/res/res_tc.h"
#include "d/d_s_play.h"
#include "d/d_snap.h"
#include "d/actor/d_a_obj_smplbg.h"
#include "d/d_lib.h"


#if VERSION == VERSION_DEMO
static f32 lbl_285_data_1C[] = {
	0.0f,
    2.125f,
    0.0f,
    1.75f,
    0.0f
};
#endif

class daNpc_Tc_HIO_c : public mDoHIO_entry_c{
public:
    daNpc_Tc_HIO_c();
    virtual ~daNpc_Tc_HIO_c() {}

    void genMessage(JORMContext* ctx) {}

public:
    /* 0x04 */ dNpc_HIO_c mNpc;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ u8 field_0x34;
    /* 0x35 */ u8 field_0x35[0x38 - 0x35];
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ bool field_0x44;
    /* 0x45 */ u8 field_0x45[0x48 - 0x45];
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ cXyz field_0x60;
    /* 0x6C */ cXyz field_0x6C;
    /* 0x78 */ s16 field_0x78;
    /* 0x7A */ s16 field_0x7A;
    /* 0x7C */ u8 field_0x7C;
    /* 0x7D */ u8 field_0x7D;
    /* 0x7E */ u8 field_0x7E;
    /* 0x7F */ u8 field_0x7F[8];
    /* 0x87 */ u8 field_0x87[8];
    /* 0x8F */ u8 field_0x8F;
    /* 0x90 */ u8 field_0x90;
    /* 0x91 */ u8 field_0x91;
    /* 0x92 */ u8 field_0x92;
    /* 0x93 */ u8 field_0x93;
    /* 0x94 */ f32 field_0x94[24];
};  // Size: 0xF4

static daNpc_Tc_HIO_c l_HIO;

#include "d/actor/d_a_npc_tc_msg_normal2.inc"

#include "d/actor/d_a_npc_tc_msg_white.inc"

#include "d/actor/d_a_npc_tc_msg_red.inc"

/* 000000EC-00000394       .text __ct__14daNpc_Tc_HIO_cFv */
daNpc_Tc_HIO_c::daNpc_Tc_HIO_c() {
    field_0x60.set(-100.0f, 1700.0f, -50.0f);
    field_0x6C.set(100.0f, 1700.0f, 50.0f);

    field_0x7A = 0;
    field_0x78 = -0x8000;
    field_0x7C = dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80);
    field_0x7D = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1A20);
    field_0x7E = dComIfGs_isEventBit(dSv_event_flag_c::UNK_1708);

    for (int i = 0; i < 8; i++) {
        field_0x87[i] = dComIfGs_isGetCollectMap(i+1);
    }

    for (int i = 0; i < 8; i++) {
        field_0x7F[i] = dComIfGs_isCollectMapTriforce(i+1);
    }

    field_0x8F = dComIfGs_isStageTbox(dSv_save_c::STAGE_DRC, 0xf);
    field_0x90 = dComIfGs_isStageTbox(dSv_save_c::STAGE_FW, 0xf);
    field_0x91 = dComIfGs_isStageTbox(dSv_save_c::STAGE_TOTG, 0xf);
    field_0x92 = dComIfGs_isStageTbox(dSv_save_c::STAGE_WT, 0xf);
    field_0x93 = dComIfGs_isStageTbox(dSv_save_c::STAGE_ET, 0xf);

    mNpc.m04 = -20.0f;
    mNpc.mMaxHeadX = 0x1FFE;
    mNpc.mMaxHeadY = 10000;
    mNpc.mMaxBackboneX = 0;
    mNpc.mMaxBackboneY = 0x1C70;
    mNpc.mMinHeadX = -0x9C4;
    mNpc.mMinHeadY = -10000;
    mNpc.mMinBackboneX = 0;
    mNpc.mMinBackboneY = -0x1C70;
    mNpc.mMaxTurnStep = 3000;
    mNpc.mMaxHeadTurnVel = 0x800;
    mNpc.mAttnYOffset = 65.0f;
    mNpc.mMaxAttnAngleY = 0x4000;
    mNpc.m22 = 0;
    mNpc.mMaxAttnDistXZ = 400.0f;
    
    field_0x2C = 900.0f;
    field_0x30 = 400.0f;
    field_0x34 = 0;
    field_0x38 = 20.0f;
    field_0x40 = 14.0f;
    field_0x3C = -2.5f;
    field_0x48 = -25.0f;
    field_0x50 = 8.0f;
    field_0x4C = -2.5f;
    field_0x54 = 0.35f;
    field_0x58 = 4.0f;
    field_0x5C = 8.0f;
    field_0x94[0] = 0.0f;
    field_0x94[1] = 8.0f;
    field_0x94[2] = 8.0f;
    field_0x94[3] = 5.0f;
    field_0x94[4] = 8.0f;
    field_0x94[5] = 4.0f;
    field_0x94[6] = 0.0f;
    field_0x94[7] = 6.0f;
    field_0x94[8] = 6.0f;
    field_0x94[9] = 0.0f;
    field_0x94[10] = 8.0f;
    field_0x94[11] = 8.0f;
    field_0x94[12] = 8.0f;
    field_0x94[13] = 8.0f;
    field_0x94[14] = 8.0f;
    field_0x94[15] = 8.0f;
    field_0x94[16] = 8.0f;
    field_0x94[17] = 8.0f;
    field_0x94[18] = 8.0f;
    field_0x94[19] = 8.0f;
    field_0x94[20] = 8.0f;
    field_0x94[21] = 8.0f;
    field_0x94[23] = 8.0f;
    field_0x94[22] = 8.0f;
}

static const int l_btp_ix_tbl[] = {
    TC_BTP_MABA01
};

/* 000003D0-0000059C       .text nodeCallBack__FP7J3DNodei */
static BOOL nodeCallBack(J3DNode* node, int calcTiming) {
    if (calcTiming == J3DNodeCBCalcTiming_In) {
        J3DModel* model = j3dSys.getModel();
        J3DJoint* joint = (J3DJoint*)node;
        daNpc_Tc_c* i_this = (daNpc_Tc_c*)model->getUserArea();

        if(i_this != NULL) {
            s32 jntNo = joint->getJntNo();
            mDoMtx_stack_c::copy(model->getAnmMtx(jntNo));
            if(jntNo == i_this->m_jnt.getHeadJntNum()) {
                static cXyz l_offsetAttPos(0.0f, 0.0f, 0.0f);
                static cXyz l_offsetEyePos(24.0f, -16.0f, 0.0f);
                mDoMtx_stack_c::multVec(&l_offsetAttPos, &i_this->getAttentionBasePos());
                mDoMtx_stack_c::YrotM(-i_this->m_jnt.getHead_y());
                mDoMtx_stack_c::ZrotM(-i_this->m_jnt.getHead_x());
                mDoMtx_stack_c::multVec(&l_offsetEyePos, &i_this->getEyePos());
                i_this->incAttnSetCount();             
            } else if(jntNo == i_this->m_jnt.getBackboneJntNum()) {
                mDoMtx_stack_c::XrotM((int)i_this->m_jnt.getBackbone_y());
                mDoMtx_stack_c::ZrotM((int)i_this->m_jnt.getBackbone_x());
            }
            cMtx_copy(mDoMtx_stack_c::get(), J3DSys::mCurrentMtx);
            model->setAnmMtx(jntNo, mDoMtx_stack_c::get());
        }
    }
    return TRUE;
}

/* 0000059C-000005C8       .text searchTower_CB__FPvPv */
static void* searchTower_CB(void* i_actor, void* i_this) {
    return static_cast<daNpc_Tc_c*>(i_this)->_searchTower(static_cast<fopAc_ac_c*>(i_actor));
}

/* 000005C8-00000630       .text _searchTower__10daNpc_Tc_cFP10fopAc_ac_c */
fopAc_ac_c* daNpc_Tc_c::_searchTower(fopAc_ac_c* i_actor) {
    if (fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == PROC_Obj_Smplbg && ((daObjSmplbg::Act_c*)i_actor)->prm_get_type() == 0) {
        return i_actor;
    }
    return NULL;
}



/* 00000630-00000744       .text initTexPatternAnm__10daNpc_Tc_cFb */
BOOL daNpc_Tc_c::initTexPatternAnm(bool param_1) {
    J3DModelData* modeldata = mpMorf->getModel()->getModelData();

    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Tc", l_btp_ix_tbl[mTexPatternNum]);
    JUT_ASSERT(0x188, m_head_tex_pattern != NULL);

    if(mBtpAnm.init(modeldata, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, param_1, FALSE) == FALSE) {
        return FALSE;
    }
    mBlinkFrame = 0;
    mBlinkTimer = 0;
    return TRUE;
}

/* 00000744-000007D0       .text playTexPatternAnm__10daNpc_Tc_cFv */
void daNpc_Tc_c::playTexPatternAnm() {
    if (cLib_calcTimer(&mBlinkTimer) == 0) {
        if (mBlinkFrame >= m_head_tex_pattern->getFrameMax()) {
            mBlinkFrame -= m_head_tex_pattern->getFrameMax();
            mBlinkTimer = cM_rndF(100.0f) + 30.0f;
        } else {
            mBlinkFrame++;
        }
    }
}

/* 000007D0-00000948       .text smoke_set__10daNpc_Tc_cFfffff */
void daNpc_Tc_c::smoke_set(f32 i_rate, f32 i_spread, f32 i_initialVelOmni, f32 i_initialVelAxis, f32 i_initialVelDir) {
    static JGeometry::TVec3<f32> smoke_scale(1.0f, 1.0f, 1.0);
    if(mSmokeCallBack.getEmitter() == NULL) {
        dComIfGp_particle_setToon(dPa_name::ID_COMMON_2022, &mSmokePos, &mSmokeAngle, NULL, 0xB9, &mSmokeCallBack, fopAcM_GetRoomNo(this));
    }

    if(mSmokeCallBack.getEmitter() != NULL) {
        mSmokeCallBack.getEmitter()->setRate(i_rate);
        mSmokeCallBack.getEmitter()->setSpread(i_spread);
        mSmokeCallBack.getEmitter()->setAwayFromCenterSpeed(i_initialVelOmni);
        mSmokeCallBack.getEmitter()->setAwayFromAxisSpeed(i_initialVelAxis);
        mSmokeCallBack.getEmitter()->setDirectionalSpeed(i_initialVelDir);
        mSmokeCallBack.getEmitter()->setGlobalScale(smoke_scale);
    }
}

/* 00000948-00001168       .text setAnm__10daNpc_Tc_cFv */
void daNpc_Tc_c::setAnm() {
    static const int a_anm_bck_tbl[] = {
        TC_BCK_WAIT01,
        TC_BCK_WAIT03,
        TC_BCK_WAIT02,
        TC_BCK_TALK01,
        TC_BCK_WALK01,
        TC_BCK_JAMP_A,
        TC_BCK_JAMP_B,
        TC_BCK_JAMP_C,
        TC_BCK_GUARD,
        TC_BCK_JTBT,
        TC_BCK_HAPPY,
        TC_BCK_DANCE01,
        TC_BCK_DANCE02,
        TC_BCK_GET,
        TC_BCK_MAWASU,
        TC_BCK_WAIT04,
        TC_BCK_TALK02,
    };

    dLib_anm_prm_c a_anm_prm_tbl[24] = {
        {
            /* mBckIdx     */ -1,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 0.0f,
            /* mPlaySpeed  */ 0.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_WAIT01,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_WAIT03,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_WAIT02,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_TALK01,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_WALK01,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_JAMP_A,
            /* mNextPrmIdx */ ANM_PRM_IDX_JAMP_B,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_JAMP_B,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 6.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_JAMP_C,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 6.0f,
            /* mPlaySpeed  */ 0.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_JAMP_C,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 2.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_GUARD,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_JTBT,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_HAPPY,
            /* mNextPrmIdx */ ANM_PRM_IDX_HAPPY2,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_DANCE01,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_DANCE02,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_GET,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_HAPPY,
            /* mNextPrmIdx */ ANM_PRM_IDX_TALK01,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_DANCE01,
            /* mNextPrmIdx */ ANM_PRM_IDX_TALK01,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_DANCE02,
            /* mNextPrmIdx */ ANM_PRM_IDX_WAIT03,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mBckIdx     */ BCK_IDX_MAWASU,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_WAIT04,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_TALK02,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_TALK01,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mBckIdx     */ BCK_IDX_TALK01,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
    };

    if (mAnmPrmIdx == ANM_PRM_IDX_TALK01_WAIT01) { 
        if (mpMorf->isLoop()) {
            mTalk01Wait01Timer++;
            if(mTalk01Wait01Timer >= 3) {
                mTalk01Wait01Timer = 0;
                mAnmPrmIdx = ANM_PRM_IDX_WAIT01;
            }
        }
    } else {
        mTalk01Wait01Timer = 0;
    }

    if (mAnmPrmIdx == ANM_PRM_IDX_TALK01_TALK02) {
        if (mpMorf->isLoop()) {
            mTalk01Talk02Timer++;
            if(mTalk01Talk02Timer >= 5) {
                mTalk01Talk02Timer = 0;
                mAnmPrmIdx = ANM_PRM_IDX_TALK02;
            }
        }
    } else {
        mTalk01Talk02Timer = 0;
    }

    if (mAnmPrmIdx == ANM_PRM_IDX_JTBT) {
        if (mpMorf->isLoop()) {
            mJtbtTimer++;
            if(mJtbtTimer >= 4) {
                mJtbtTimer = 0;
                mAnmPrmIdx = ANM_PRM_IDX_TALK01;
            }
        }
    } else {
        mJtbtTimer = 0;
    }

    for (int i = 0; i < 24; i++) {
        a_anm_prm_tbl[i].mMorf = l_HIO.field_0x94[i];
    }

#if VERSION != VERSION_DEMO
    if (mBckIdx == BCK_IDX_MAWASU && (int)mpMorf->getFrame() == 1) {
        if(mType == TYPE_RED) {
            fopAcM_monsSeStart(this, JA_SE_CV_TC_B_PUSH_BAR, 0);
        } else if(mType == TYPE_WHITE) {
            fopAcM_monsSeStart(this, JA_SE_CV_TC_T_PUSH_BAR, 0);
        }
    }
#endif

    if (mBckIdx == BCK_IDX_JAMP_C) {
        if (mpMorf->getFrame() == 1.0f) {
            mSmokePos = current.pos;
            mSmokeAngle = current.angle;
            smoke_set(10.0f, 0.25f, 0.0f, 2.0f, 15.0f);
        } else {
            mSmokeCallBack.end();
        }
    } 

    if (mBckIdx == BCK_IDX_DANCE01) {
        mParticlePos.setall(0.0f);
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(11));
        mDoMtx_stack_c::multVec(&mParticlePos, &mParticlePos);
        cXyz pos;

        pos.setall(1.0f);

        if (mpMorf->getFrame() == 1.0f) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_8189, &current.pos, &current.angle, &pos);
            dComIfGp_particle_set(dPa_name::ID_SCENE_818A, &current.pos, &current.angle, &pos);
            dComIfGp_particle_set(dPa_name::ID_SCENE_818B, &current.pos, &current.angle, &pos);
            dComIfGp_particle_set(dPa_name::ID_SCENE_818C, &mParticlePos, NULL, NULL, 0xff, &field_0x714, fopAcM_GetRoomNo(this));
            dComIfGp_particle_set(dPa_name::ID_SCENE_818D, &mParticlePos, NULL, NULL, 0xff, &field_0x728, fopAcM_GetRoomNo(this));
        }

        if (mpMorf->getFrame() == 88.0f) {
            f32 sin = cM_ssin(current.angle.y);
            f32 cos = cM_scos(current.angle.y);

            cXyz tempPos(current.pos.x + sin * 10.0f, current.pos.y, current.pos.z + cos * 10.0f);
            mSmokePos = tempPos;
            mSmokeAngle = current.angle;

            smoke_set(5.0f, 0.25f, 0.0f, 10.0f, 1.0f);
        } else if (mpMorf->getFrame() == 143.0f) {
            mSmokePos = current.pos;
            mSmokeAngle = current.angle;
            smoke_set(10.0f, 0.25f, 0.0f, 15.0f, 1.0f);
        } else {
            mSmokeCallBack.end();
        }
        if (mpMorf->getFrame() == 178.0f) {
            field_0x714.end();
            field_0x728.end();
        }
    }

    if (mBckIdx == BCK_IDX_JTBT) {
        if (mpMorf->getFrame() == 0.0f || mpMorf->getFrame() == 12.0f) {
            mSmokePos = current.pos;
            mSmokeAngle = current.angle;
            smoke_set(2.0f, 0.25f, 0.0f, 1.0f, 10.0f);
        } else {
            mSmokeCallBack.end();
        }
    }

    if (mBckIdx == BCK_IDX_HAPPY) {
        if (mpMorf->getFrame() == 24.0f) {
            mSmokePos = current.pos;
            mSmokeAngle = current.angle;
            smoke_set(4.0f, 0.25f, 0.0f, 2.0f, 10.0f);
        } else {
            mSmokeCallBack.end();
        }
    }
    
    if (mOldAnmPrmIdx != mAnmPrmIdx) {
        if (mAnmPrmIdx == ANM_PRM_IDX_JAMP_A) {
            cXyz particlePos(current.pos);
            particlePos.y -= 80.0f;
            cXyz particleScale;
            particleScale.setall(1.0f);

            JPABaseEmitter* pEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_8152, &particlePos, NULL, &particleScale);
            
            pEmitter->setGlobalParticleScale(0.62f, 0.6f);
            fopAcM_seStart(this, JA_SE_CM_CMN_NOTICE, 0); // regswap for demo likely happens here, daNpc_Tc_c::cutEffectStart also has a regswap with identical code
        }
        mSmokeCallBack.end();
    }
    dLib_bcks_setAnm("Tc", mpMorf, &mBckIdx, &mAnmPrmIdx, &mOldAnmPrmIdx, a_anm_bck_tbl, a_anm_prm_tbl, false);
    /* Nonmatching */
}

/* 00001168-000011C0       .text setTexAnm__10daNpc_Tc_cFv */
void daNpc_Tc_c::setTexAnm() {
    static s8 a_tex_pattern_num_tbl[2] = {
        0xFF,
        0x00,
    };

    s8 texPatternNum = a_tex_pattern_num_tbl[mTexPatternNumIdx];
    if (texPatternNum != mTexPatternNum && texPatternNum != -1) {
        mTexPatternNum = texPatternNum;
        initTexPatternAnm(true);
    }
}

/* 000011C0-0000136C       .text chkAttention__10daNpc_Tc_cF4cXyzs */
bool daNpc_Tc_c::chkAttention(cXyz param_1, s16 param_2) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    f32 maxAttnDist = l_HIO.mNpc.mMaxAttnDistXZ;
    switch(mType) {
        case TYPE_RED:
        case TYPE_WHITE:
            maxAttnDist = l_HIO.mNpc.mMaxAttnDistXZ;
            maxAttnDist *= 0.5f;
            break;
    }

    if (mStatus == STATUS_WALK_TO_JAIL || mStatus == STATUS_JUMP || mStatus == STATUS_SIT) {
        maxAttnDist = l_HIO.field_0x2C;
    }

    int maxAttnAngleY = l_HIO.mNpc.mMaxAttnAngleY;
    cXyz temp;
    temp.x = player->current.pos.x - param_1.x;
    temp.z = player->current.pos.z - param_1.z;
    f32 temp2 = std::sqrtf(temp.x * temp.x + temp.z * temp.z);
    s16 temp3 = cM_atan2s(temp.x, temp.z);

    if (mHasAttention) {
        maxAttnDist += 40.0f;
        maxAttnAngleY += 0x71C;
    }

    temp3 -= param_2;
    return maxAttnAngleY > abs(temp3) && maxAttnDist > temp2;
}

#include "d/actor/d_a_npc_tc_cut.inc"

/* 0000136C-00001424       .text eventOrder__10daNpc_Tc_cFv */
void daNpc_Tc_c::eventOrder() {
    static char* a_demo_name_tbl[] = {
        "TC_JUMP_DEMO",
        "TC_RESCUE",
        "TC_TALK_NEAR_JAIL",
        "TC_TALK_NEAR_JAIL_S",
        "TC_TALK_NEAR_JAIL2",
        "TC_GET_RUPEE",
        "TC_PAY_RUPEE"
    };


    if (mEventIdx == 1 || mEventIdx == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (mEventIdx == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (mEventIdx == 8 || mEventIdx == 9) {
        fopAcM_orderOtherEvent(this, a_demo_name_tbl[mEventIdx - 3], 0x14F);
    }
    else if (mEventIdx >= 3) {
        fopAcM_orderOtherEvent(this, a_demo_name_tbl[mEventIdx - 3]);
    }
}

/* 00001424-00001470       .text checkOrder__10daNpc_Tc_cFv */
void daNpc_Tc_c::checkOrder() {
    if (eventInfo.mCommand == dEvtCmd_INDEMO_e) {
        mEventIdx = 0;
        return;
    }

    if (eventInfo.mCommand != dEvtCmd_INTALK_e) {
        return;
    }

    if (mEventIdx != 1 && mEventIdx != 2) {
        return;
    }
    mEventIdx = 0;
    mTalkingNearJail = true;
}

/* 00001470-000014FC       .text existTcMonument__10daNpc_Tc_cFv */
bool daNpc_Tc_c::existTcMonument() {
    if(dComIfGs_isStageTbox(dSv_save_c::STAGE_DRC, 0xF) || dComIfGs_isStageTbox(dSv_save_c::STAGE_FW, 0xF) 
    || dComIfGs_isStageTbox(dSv_save_c::STAGE_TOTG, 0xF) || dComIfGs_isStageTbox(dSv_save_c::STAGE_WT, 0xF)
    || dComIfGs_isStageTbox(dSv_save_c::STAGE_ET, 0xF)) {
        return true;
    }
    return false;
}

/* 000014FC-0000156C       .text anmAtr__10daNpc_Tc_cFUs */
void daNpc_Tc_c::anmAtr(u16 i_msgStatus) {
    static const s8 anm_atr[] = {
        ANM_PRM_IDX_WAIT01,
        ANM_PRM_IDX_WAIT02,
        ANM_PRM_IDX_WAIT03,
        ANM_PRM_IDX_TALK01,
        ANM_PRM_IDX_GUARD,
        ANM_PRM_IDX_JTBT,
        ANM_PRM_IDX_HAPPY,
        ANM_PRM_IDX_DANCE01,
        ANM_PRM_IDX_DANCE02,
        ANM_PRM_IDX_HAPPY2,
        ANM_PRM_IDX_DANCE02_TO_WAIT03,
        ANM_PRM_IDX_DANCE01_TO_TALK01,
        ANM_PRM_IDX_TALK01_WAIT01,
        ANM_PRM_IDX_TALK01_TALK02,
        ANM_PRM_IDX_TALK02,
        ANM_PRM_IDX_WAIT04
    };

    switch (i_msgStatus) {
        case fopMsgStts_MSG_TYPING_e:
            if(field_0x6C8) {
                return;
            }
            u8 msgAnmAtr = dComIfGp_getMesgAnimeAttrInfo();
            field_0x6C8 = TRUE;
            if(anm_atr[msgAnmAtr] == ANM_PRM_IDX_HAPPY2 && mAnmPrmIdx == ANM_PRM_IDX_TALK01) {
                return;
            }
            mAnmPrmIdx = anm_atr[msgAnmAtr];
            break;

        case fopMsgStts_MSG_DISPLAYED_e:
            field_0x6C8 = FALSE;
            break;
    }
}

/* 0000156C-00001618       .text stopTower__10daNpc_Tc_cFv */
void daNpc_Tc_c::stopTower() {
    JUT_ASSERT(VERSION_SELECT(0x3F5, 0x3F4, 0x3F4, 0x3F4), m_tower_actor != NULL);

    daObjSmplbg::Act_c* tower = m_tower_actor;
    switch (mType) {
        case TYPE_RED:
        case TYPE_WHITE:
            m_jnt.offHeadLock();
            mAnmPrmIdx = ANM_PRM_IDX_WAIT04;
            tower->onStop();
            break;
        case TYPE_NORMAL2:
            tower->onStop();
            break;
    }
}

/* 00001618-000017A4       .text startTower__10daNpc_Tc_cFv */
void daNpc_Tc_c::startTower() {
    JUT_ASSERT(VERSION_SELECT(0x408, 0x407, 0x407, 0x407), m_tower_actor != NULL);
    daObjSmplbg::Act_c* tower = m_tower_actor;

    cXyz temp;
    s16 temp2;
    switch(mType) {
        case TYPE_WHITE:
            temp = l_HIO.field_0x60;
            temp2 = l_HIO.field_0x7A;
            break;
        case TYPE_RED:
            temp = l_HIO.field_0x6C;
            temp2 = l_HIO.field_0x78;
            break;
    }

    switch(mType) {
        case TYPE_RED:
        case TYPE_WHITE:
            m_jnt.onHeadLock();
            mDoMtx_stack_c::transS(m_tower_actor->current.pos);
            mDoMtx_stack_c::ZXYrotM(m_tower_actor->shape_angle);
            temp2 = m_tower_actor->shape_angle.y + temp2;
            cLib_addCalcAngleS2(&current.angle.y, temp2, 4, 0x400);
            if(cLib_distanceAngleS(current.angle.y, temp2) < 0x600) {
                tower->offStop();
                mAnmPrmIdx = ANM_PRM_IDX_MAWASU;
            }
            break;
        default:
            tower->offStop();
            break;
    }
}

/* 000017A4-00001900       .text next_msgStatusBlue__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusBlue(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;
    if ((mAnmPrmIdx == ANM_PRM_IDX_DANCE01_TO_TALK01 || mAnmPrmIdx == ANM_PRM_IDX_DANCE02_TO_WAIT03) && !mpMorf->isStop()) {
        msgStatus = fopMsgStts_MSG_DISPLAYED_e;
    } else {
        switch (*pMsgNo) {
            case 0xDDD:
                if (dComIfGs_isStageTbox(dSv_save_c::STAGE_DRC, 0xF) || dComIfGs_isStageTbox(dSv_save_c::STAGE_FW, 0xF) || dComIfGs_isStageTbox(dSv_save_c::STAGE_TOTG, 0xF) || dComIfGs_isStageTbox(dSv_save_c::STAGE_WT, 0xF) || dComIfGs_isStageTbox(dSv_save_c::STAGE_ET, 0xF)) {
                    *pMsgNo = 0xDDE;
                } else {
                    *pMsgNo = 0xDF9;
                }
                break;
            case 0xDDE:
                *pMsgNo = 0xDDF;
                break;
            case 0xDDF:
                *pMsgNo = 0xDE0;
                break;
            case 0xDF9:
                *pMsgNo = 0xDFA;
                break;
            default:
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
        }
    }
    return msgStatus;
}

/* 00001900-00001AEC       .text next_msgStatusNormal__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusNormal(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e;
    if ((mAnmPrmIdx == ANM_PRM_IDX_DANCE01_TO_TALK01 || mAnmPrmIdx == ANM_PRM_IDX_DANCE02_TO_WAIT03) && !mpMorf->isStop()) {
        msgStatus = fopMsgStts_MSG_DISPLAYED_e;
    } else {
        switch(*pMsgNo) {
            case 0x10CD:
                *pMsgNo = 0x10CE;
                break;
            case 0x10DF:
                *pMsgNo = 0x10CE;
                break;
            case 0x10CE:
                *pMsgNo = 0x10CF;
                break;
            case 0x10CF:
                *pMsgNo = 0x10D0;
                break;
            case 0x10D0:
                *pMsgNo = 0x10D1;
                break;
            case 0x10D1:
                *pMsgNo = 0x10D2;
                break;
            case 0x10D3:
                *pMsgNo = 0x10D2;
                break;
            case 0x10D4:
                *pMsgNo = 0x10D5;
                break;
            case 0x10D5:
                *pMsgNo = 0x10D6;
                break;
            case 0x10D6:
                *pMsgNo = 0x10D7;
                break;
            case 0x10D7:
                *pMsgNo = 0x10D8;
                break;
            case 0x10D9:
                *pMsgNo = 0x10D8;
                break;
            case 0x10DA:
                *pMsgNo = 0x10DB;
                break;
            case 0x10DB:
                *pMsgNo = 0x10DC;
                break;
            case 0x10DD:
                *pMsgNo = 0x10DE;
                break;
            case 0xDAD:
                *pMsgNo = 0xDAE;
                break;
            case 0xDAF:
                *pMsgNo = 0xDB0;
                break;
            default:
                msgStatus = fopMsgStts_MSG_ENDS_e;
                break;
        }
    }
    return msgStatus;
}

/* 00001AEC-00001B64       .text next_msgStatus__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatus(u32* pMsgNo) {
    u16 msg;
    switch(mType) {
        case TYPE_NORMAL:
            msg = next_msgStatusNormal(pMsgNo);
            break;
        case TYPE_NORMAL2:
            msg = next_msgStatusNormal2(pMsgNo);
            break;
        case TYPE_BLUE:
            msg = next_msgStatusBlue(pMsgNo);
            break;
        case TYPE_RED:
            msg = next_msgStatusRed(pMsgNo);
            break;
        case TYPE_WHITE:
            msg = next_msgStatusWhite(pMsgNo);
            break;
        default:
            msg = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return msg;
}

/* 00001B64-00001B88       .text setFirstMsg__10daNpc_Tc_cFPbUlUl */
u32 daNpc_Tc_c::setFirstMsg(bool* param_1, u32 param_2, u32 param_3) {
    if (!*param_1) {
        *param_1 = true;
    } else {
        param_2 = param_3;
    }
    return param_2;
}

/* 00001B88-00001BE0       .text getMsgNormal__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgNormal() {
    u32 msg;
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B40)) {
        msg = 0x10D3;
        mHasTalkedNearJail  = true;
    } else {
        msg= 0x10D9;
    }
    return msg;
}

/* 00001BE0-00001BE8       .text getMsgBlue__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgBlue() {
    return 0xDDD;
}

/* 00001BE8-00001C74       .text getMsg__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsg() {
    u32 msg = 0;
    switch(mType) {
        case TYPE_NORMAL:
            msg = getMsgNormal();
            break;
        case TYPE_NORMAL2:
            msg = getMsgNormal2();
            break;
        case TYPE_BLUE:
            msg = getMsgBlue();
            break;
        case TYPE_RED:
            msg = getMsgRed();
            break;
        case TYPE_WHITE:
            msg = getMsgWhite();
            break;
    }
    return msg;
}

/* 00001C74-00001C98       .text getArg__10daNpc_Tc_cFv */
void daNpc_Tc_c::getArg() {
    mType = fopAcM_GetParam(this) & 0xf;
    if(mType != 0xF) {
        return;
    }
    mType = TYPE_NORMAL;
}

extern dCcD_SrcCyl dNpc_cyl_src;
/* 00001C98-0000202C       .text createInit__10daNpc_Tc_cFv */
void daNpc_Tc_c::createInit() {
#if VERSION != VERSION_DEMO
    if (mType == TYPE_NORMAL) {
        fopAcM_OnStatus(this, fopAcStts_UNK4000_e);
    }
#endif
    field_0x790 = current.angle;
    attention_info.flags = fopAc_Attn_LOCKON_TALK_e | fopAc_Attn_ACTION_SPEAK_e;
    mAttPos.set(current.pos);
    mEyePos.set(current.pos);
#if VERSION == VERSION_DEMO
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this));
#endif
    mStts.Init(0xFE, 0xFE, this);
    mCyl.Set(dNpc_cyl_src);
    mCyl.SetStts(&mStts);
    mHasTalkedNearJail  = false;
    mTexPatternNumIdx = 1;
    switch (mType) {
        case TYPE_NORMAL:
            mAnmPrmIdx = ANM_PRM_IDX_WAIT02;
            fopAcM_Search(&searchStoolPos, this);
            if (setAction(&daNpc_Tc_c::help_action, NULL)) {
                gravity = 0.0f;
                mAcchCir.SetWall(60.0f, 50.0f);
            }

            break;
        case TYPE_BLUE:
        case TYPE_NORMAL2:
            gravity = -9.0f;
            mAnmPrmIdx = ANM_PRM_IDX_WAIT01;
            if (setAction(&daNpc_Tc_c::wait_action, NULL)) {
                mAcchCir.SetWall(60.0f, 50.0f);
            }
            break;
        case TYPE_RED:
        case TYPE_WHITE:
            gravity = -9.0f;
            m_jnt.onHeadLock();
            mAnmPrmIdx = ANM_PRM_IDX_MAWASU;
            if (setAction(&daNpc_Tc_c::wait_action, NULL)) {
                mAcchCir.SetWall(60.0f, 10.0f);
            }
            break;
    }
#if VERSION != VERSION_DEMO
    mObjAcch.Set(fopAcM_GetPosition_p(this), fopAcM_GetOldPosition_p(this), this, 1, &mAcchCir, fopAcM_GetSpeed_p(this), &current.angle, &shape_angle);
#endif
    mOldAnmPrmIdx = 0;
    setTexAnm();
    setAnm();
    set_mtx();
    mpMorf->calc();
    mEventCut.setActorInfo2("Tc", this);
}

/* 0000202C-000020C4       .text searchStoolPos__10daNpc_Tc_cFPvPv */
void* daNpc_Tc_c::searchStoolPos(void* i_actor, void* i_this) {
    fopAc_ac_c* actor = static_cast<fopAc_ac_c*>(i_actor);
    daNpc_Tc_c* a_this = static_cast<daNpc_Tc_c*>(i_this);

    dStage_objectNameInf* inf = dStage_searchName("Ostool");
    
    if(inf == NULL) {
        return NULL;
    }

    if(inf->procname == fopAcM_GetProfName(i_actor) && inf->argument == actor->argument) {
        a_this->mStoolPos.set(actor->current.pos);
    }
    return NULL;
}

/* 000020C4-00002148       .text setAttention__10daNpc_Tc_cFv */
void daNpc_Tc_c::setAttention() {
    s8 temp = mAnmPrmIdx;
    if (temp != ANM_PRM_IDX_WAIT01 && temp != ANM_PRM_IDX_WALK01 && temp != ANM_PRM_IDX_TALK01 && temp != ANM_PRM_IDX_GUARD &&
        temp != ANM_PRM_IDX_MAWASU && temp != ANM_PRM_IDX_TALK02 && temp != ANM_PRM_IDX_WAIT04) {
        return;
    }

    eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);
    attention_info.position.set(mAttPos.x, mAttPos.y + l_HIO.mNpc.mAttnYOffset, mAttPos.z);
}

/* 00002148-00002220       .text calcMove__10daNpc_Tc_cFv */
void daNpc_Tc_c::calcMove() {
    f32 speed;
    if (mAnmPrmIdx != ANM_PRM_IDX_WALK01) {
        return;
    }
    cLib_chaseF(&speedF, mTargetSpeed, 0.1f);
    if (mEventCut.getMoveSpeed() != 0.0f) {
        switch(mEventCut.getNowCut()) {
            case 2:
            case 4:
                speed = l_HIO.field_0x54 * mEventCut.getMoveSpeed();
                break;
        }
    } else {
        speed = speedF * l_HIO.field_0x54;
    }
    if(speed < 0.5f) {
        speed = 0.5f;
    }
    mpMorf->setPlaySpeed(speed);
}

/* 00002220-000024C4       .text lookBack__10daNpc_Tc_cFv */
void daNpc_Tc_c::lookBack() {
    cXyz temp6;
    cXyz temp3(0.0f, 0.0f, 0.0f);
    cXyz* dstPos = NULL;
    s16 desiredYRot = current.angle.y;
    s16 target;
    if (mStatus == STATUS_TALK) {
        m_jnt.setTrn();
    }
    if (mStatus == STATUS_WALK_TO_JAIL || mStatus == STATUS_WAIT_NEAR_JAIL || mStatus == STATUS_SIT) {
        m_jnt.setTrn();
        mHasAttention = true;
    }

    if (mType == TYPE_WHITE || mType == TYPE_RED) {
        if (mStatus == STATUS_WAIT) {
            if (mAnmPrmIdx == ANM_PRM_IDX_MAWASU || mAnmPrmIdx == ANM_PRM_IDX_WAIT04) {
                m_jnt.onBackBoneLock();
                m_jnt.clrTrn();
            }
        } else if (mAnmPrmIdx == ANM_PRM_IDX_MAWASU || mAnmPrmIdx == ANM_PRM_IDX_WAIT04) {
            m_jnt.onBackBoneLock();
            m_jnt.clrTrn();
        } else {
            m_jnt.offBackBoneLock();
            m_jnt.setTrn();
            mHasAttention = true;
        }
    }

    if (mStatus == 8) {
        m_jnt.setTrn();
        temp6 = mStoolLookPos;
        dstPos = &temp6;
        temp3.set(current.pos);
        temp3.y = eyePos.y;
    } else if (mEventCut.getAttnFlag()) {
        m_jnt.setTrn();
        temp6 = mEventCut.getAttnPos();
        dstPos = &temp6;
        temp3.set(current.pos);
        temp3.y = eyePos.y;
        
    } else if (mHasAttention){
        temp6 = dNpc_playerEyePos(l_HIO.mNpc.m04);
        dstPos = &temp6;
        temp3.set(current.pos);
        temp3.y = eyePos.y;
    }

    if (m_jnt.trnChk()) {
        target = l_HIO.mNpc.mMaxHeadTurnVel;

        s16 temp4 = mEventCut.getTurnSpeed();
        if (temp4 != 0) {
            target = temp4;
        }
        cLib_addCalcAngleS2(&mMaxHeadTurnVelocity, target, 4, 0x800);
    } else {
        mMaxHeadTurnVelocity = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos, temp3, desiredYRot, mMaxHeadTurnVelocity, false);
}

/* 000024C4-00002594       .text statusWait__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWait() {
    if (mType == TYPE_WHITE || mType == TYPE_RED) {
        JUT_ASSERT(VERSION_SELECT(0x5FE, 0x601, 0x601, 0x601), m_tower_actor != NULL);

        if (m_tower_actor->isStop()) {
            mAnmPrmIdx = ANM_PRM_IDX_WAIT04;
        } else {
            mAnmPrmIdx = ANM_PRM_IDX_MAWASU;
        }
    }

    if (mTalkingNearJail) {
        mStatus = STATUS_TALK;
    } else if (mHasAttention) {
        mEventIdx = 2;
    }
}

/* 00002594-000026E4       .text statusSit__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusSit() {
    mSmokeCallBack.end();
    calc_sitpos();
    current.pos.set(mSitPos);
    gravity = 0.0f;
    
    if(mAnmPrmIdx != ANM_PRM_IDX_JAMP_A) {
        if(dLib_checkPlayerInCircle(current.pos, l_HIO.field_0x2C, 100.0f)) {
            if (!mHasEnteredSitRadius) {
                mHasEnteredSitRadius = true;
                mEventIdx = 3;
                mStatus = STATUS_DEMO_JUMP;
                return;
            }
            mAnmPrmIdx = ANM_PRM_IDX_JAMP_A;
        }
    }

    if(mpMorf->isStop() && mAnmPrmIdx == ANM_PRM_IDX_JAMP_A) {
        speedF = l_HIO.field_0x38;
        speed.y = l_HIO.field_0x40;
        gravity = l_HIO.field_0x3C;
        mAnmPrmIdx = ANM_PRM_IDX_JAMP_B;
        mStatus = STATUS_JUMP;
    }
}

/* 000026E4-00002798       .text statusJump__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusJump() {
    if (speed.y <= 0.0f && mAnmPrmIdx == ANM_PRM_IDX_JAMP_B) {
        mAnmPrmIdx = ANM_PRM_IDX_JAMP_C1;
    }

    if (mObjAcch.ChkGroundHit() && mAnmPrmIdx == ANM_PRM_IDX_JAMP_C1) {
        speedF = 0.0f;
        mAnmPrmIdx = ANM_PRM_IDX_JAMP_C2;
        mJumpLandingTimer = 0x33;
        return;
    }

    if (cLib_calcTimer(&mJumpLandingTimer) == 0 && mAnmPrmIdx == ANM_PRM_IDX_JAMP_C2) {
        mAnmPrmIdx = ANM_PRM_IDX_WALK01;
        mStatus = STATUS_WALK_TO_JAIL;
    }
}

/* 00002798-000029B0       .text statusWalkToJail__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWalkToJail() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    
    s16 angle = cLib_targetAngleY(&current.pos, &player->current.pos);
    if (mObjAcch.ChkWallHit()) {
        if (mTalkingNearJail) {
            mTargetSpeed = 0.0f;
            speedF = 0.0f;

            if (!mHasTalkedNearJail  || l_HIO.field_0x44 != 0) {
                mAnmPrmIdx = ANM_PRM_IDX_WAIT03;
                dComIfGp_event_reset();
                mStatus = STATUS_DEMO_TALK;
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B40) == 0) {
                    if (dComIfGs_getClearCount() != 0) {
                        mEventIdx = 6;
                    } else {
                        mEventIdx = 5;
                    }
                } else {
                    mEventIdx = 7;
                }

                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B40);
                mHasTalkedNearJail  = true;
                return;

            }
            mStatus = STATUS_TALK_NEAR_JAIL;
        } else if (mHasAttention) {
            mEventIdx = 2;
        }
    }

    if (mObjAcch.ChkWallHit() && std::fabsf(cM_scos(angle)) > 0.9f) {
        mTargetSpeed = 0.0f;
        if (speedF == 0.0f) {
            mAnmPrmIdx = ANM_PRM_IDX_WAIT01;
        }
    } else {
        mAnmPrmIdx = ANM_PRM_IDX_WALK01;
        mTargetSpeed = l_HIO.field_0x58;
        if (speedF == 0.0f) {
            speedF = l_HIO.field_0x5C;
        }
    }
    if (mObjAcch.ChkWallHit()) {
        if(!dLib_checkPlayerInCircle(current.pos, l_HIO.field_0x30, 100.0f)) {
            mStatus = STATUS_WALK_TO_STOOL;
        }
    }
}

/* 000029B0-00002A20       .text statusTalkNearJail__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusTalkNearJail() {
    mTargetSpeed = 0.0f;
    speedF = 0.0f;
    if (talk(1) == 0x12) {
        mStatus = STATUS_WAIT_NEAR_JAIL;
        dComIfGp_event_reset();
        mTalkingNearJail = false;
    }
}

/* 00002A20-00002BD4       .text statusWaitNearJail__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWaitNearJail() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    
    s16 angle = cLib_targetAngleY(&current.pos, &player->current.pos);
    if (mObjAcch.ChkWallHit()) {
        if (mTalkingNearJail) {
            mTargetSpeed = 0.0f;
            speedF = 0.0f;

            if (!mHasTalkedNearJail || l_HIO.field_0x44 != 0) {
                mAnmPrmIdx = ANM_PRM_IDX_WAIT03;
                dComIfGp_event_reset();
                mStatus = STATUS_DEMO_TALK;
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B40) == 0) {
                    mEventIdx = 5;
                } else {
                    mEventIdx = 7;
                }

                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B40);
                mHasTalkedNearJail = true;
                return;

            }
            mStatus = STATUS_TALK_NEAR_JAIL;
        } else if (mHasAttention) {
            mEventIdx = 2;
        }
    }

    if (mObjAcch.ChkWallHit() && std::fabsf(cM_scos(angle)) > 0.9f) {
        mTargetSpeed = 0.0f;
        if (speedF == 0.0f) {
            mAnmPrmIdx = ANM_PRM_IDX_WAIT01;
        }
    } else {
        mAnmPrmIdx = ANM_PRM_IDX_WALK01;
        mTargetSpeed = l_HIO.field_0x58;
        if (speedF == 0.0f) {
            speedF = l_HIO.field_0x5C;
        }
    }
}

/* 00002BD4-00002D80       .text statusWalkToStool__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWalkToStool() {
    calc_sitpos();
    if(dLib_checkPlayerInCircle(current.pos, l_HIO.field_0x30, 100.0f)) {
        mTargetSpeed = 0.0f;
        if (speedF == 0.0f) {
            mStatus = STATUS_WALK_TO_JAIL;
        }
        
    } else {
        mStoolLookPos.set(mStoolPos);
        cLib_targetAngleY(&current.pos, &mWalkToStoolPos);
        cLib_addCalcPosXZ2(&current.pos, mWalkToStoolPos, 0.1f, speedF);
        f32 temp = (mWalkToStoolPos - current.pos).absXZ();
        if(temp < 5.0f) {
            mTargetSpeed = 0.0f;
            if (speedF == 0.0f) {
                mAnmPrmIdx = ANM_PRM_IDX_WAIT01;
                mStatus = STATUS_SIT_TO_STOOL;
            }
        } else {
            mAnmPrmIdx = ANM_PRM_IDX_WALK01;
            mTargetSpeed = l_HIO.field_0x58;   
        }
    }
}

/* 00002D80-00002F94       .text statusSitToStool__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusSitToStool() {
    calc_sitpos();
    cLib_addCalcAngleS2(&current.angle.y, field_0x790.y, 4, 0x800);

    if (std::fabsf(field_0x790.y - current.angle.y) < 16.0f) {
        if (speed.y == 0.0f && mObjAcch.ChkGroundHit()) {
            speed.y = 22.0f;
            gravity = -2.5f;
        }

        if (speed.y < 0.0f) {
            mAnmPrmIdx = ANM_PRM_IDX_WAIT02;
        }

        if (speed.y < 0.0f && current.pos.y < mSitPos.y) {
            gravity = 0.0f;
            speed.y = 0.0f;
            current.pos.y = mSitPos.y;
        }

        cLib_addCalcPosXZ2(&current.pos, mSitPos, 0.1f, 4.0f);
        f32 diff = (mSitPos - current.pos).absXZ();
        if (current.pos.y == mSitPos.y && diff < 5.0f) {
            mSmokePos.set(current.pos);
            mSmokeAngle = current.angle;
            smoke_set(2.0f, 0.25f, 0.0f, 5.0f, 20.0f);
            mStatus = STATUS_SIT;
        }
    }
}

/* 00002F94-00003028       .text statusTalk__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusTalk() {
    if(talk(1) != 0x12) {
        return;
    }
    
    switch(mType) {
        case TYPE_RED:
        case TYPE_WHITE:
            startTower();
            mAnmPrmIdx = ANM_PRM_IDX_MAWASU;
            // fallthrough
        case TYPE_NORMAL2:
            startTower();
            // fallthrough
        default:
            mAnmPrmIdx = ANM_PRM_IDX_WAIT01;
            mStatus = STATUS_WAIT;
            dComIfGp_event_reset();
            mTalkingNearJail = false;
            break;
    }
}

/* 00003028-00003088       .text statusPayRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusPayRupee() {
    if(talk(1) == 0x12) {
        dComIfGp_event_reset();
        mEventIdx = 9;
        mStatus = STATUS_DEMO_PAY_RUPEE;
    }
}

/* 00003088-000030F8       .text statusDemoPayRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoPayRupee() {
    if(dComIfGp_evmng_endCheck("TC_PAY_RUPEE")) {
        dComIfGp_event_reset();
        mEventIdx = 1;
        mStatus = STATUS_TALK;
    }
}

/* 000030F8-00003158       .text statusGetRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusGetRupee() {
    if(talk(1) == 0x12) {
        dComIfGp_event_reset();
        mEventIdx = 8;
        mStatus = STATUS_DEMO_GET_RUPEE;
    }
}

/* 00003158-000031CC       .text statusDemoGetRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoGetRupee() {
    if(dComIfGp_evmng_endCheck("TC_GET_RUPEE")) {
        field_0x812 = true;
        dComIfGp_event_reset();
        mEventIdx = 1;
        mStatus = STATUS_TALK;
    }
}

/* 000031CC-0000322C       .text statusMonumentComplete__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusMonumentComplete() {
    if(talk(1) == 0x12) {
        dComIfGp_event_reset();
        mEventIdx = 8;
        mStatus = STATUS_DEMO_MONUMENT_COMPLETE;
    }
}

/* 0000322C-000032A0       .text statusDemoMonumentComplete__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoMonumentComplete() {
    if(dComIfGp_evmng_endCheck("TC_GET_RUPEE")) {
        field_0x813 = true;
        dComIfGp_event_reset();
        mEventIdx = 1;
        mStatus = STATUS_TALK;
    }
}

/* 000032A0-00003308       .text statusDemoJump__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoJump() {
    if(dComIfGp_evmng_endCheck("TC_JUMP_DEMO")) {
        mStatus = STATUS_WALK_TO_JAIL;
        dComIfGp_event_reset();
    }
}

/* 00003308-00003384       .text statusDemoRescue__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoRescue() {
    if(dComIfGp_evmng_endCheck("TC_RESCUE")) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B80);
        dComIfGp_event_reset();
        fopAcM_delete(this);
    }
}

/* 00003384-00003430       .text statusDemoTalk__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoTalk() {
    if (dComIfGp_evmng_endCheck("TC_TALK_NEAR_JAIL") || dComIfGp_evmng_endCheck("TC_TALK_NEAR_JAIL_S") || dComIfGp_evmng_endCheck("TC_TALK_NEAR_JAIL2")) {
        mStatus = STATUS_WAIT_NEAR_JAIL;
        dComIfGp_event_reset();
        mTalkingNearJail = false;
    }
}

/* 00003430-00003610       .text help_action__10daNpc_Tc_cFPv */
BOOL daNpc_Tc_c::help_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        mStatus = STATUS_SIT;
        mActionStatus++; // ACTION_ONGOING
    } else if (mActionStatus != ACTION_ENDING) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80)) {
            fopAcM_delete(this);
        }
        if (dComIfGp_evmng_endCheck("OpenDoor")) {
            mTargetSpeed = 0.0f;
            speedF = 0.0f;
            mEventIdx = 4;
            mStatus = STATUS_DEMO_RESCUE;
            return true;
        } else {
            s16 temp = m_jnt.getHead_y() + current.angle.y+  m_jnt.getBackbone_y();
            mHasAttention = chkAttention(current.pos, temp);
            mEventIdx = 0;
            switch(mStatus) {
                case STATUS_WAIT:
                    statusWait();
                    break;
                case STATUS_TALK:
                    statusTalk();
                    break;
                case STATUS_SIT:
                    statusSit();
                    break;
                case STATUS_JUMP:
                    statusJump();
                    break;
                case STATUS_WALK_TO_JAIL:
                    statusWalkToJail();
                    break;
                case STATUS_TALK_NEAR_JAIL:
                    statusTalkNearJail();
                    break;
                case STATUS_WAIT_NEAR_JAIL:
                    statusWaitNearJail();
                    break;
                case STATUS_WALK_TO_STOOL:
                    statusWalkToStool();
                    break;
                case STATUS_SIT_TO_STOOL:
                    statusSitToStool();
                    break;
                case STATUS_DEMO_JUMP:
                    statusDemoJump();
                    break;
                case STATUS_DEMO_RESCUE:
                    statusDemoRescue();
                    break;
                case STATUS_DEMO_TALK:
                    statusDemoTalk();
                    break;
            }
            calcMove();
            lookBack();
            setAttention();
        }
    }
    return true;
}

/* 00003610-0000374C       .text wait_action__10daNpc_Tc_cFPv */
BOOL daNpc_Tc_c::wait_action(void*) {
    if (mActionStatus == ACTION_STARTING) {
        mStatus = STATUS_WAIT;
        mActionStatus++; // ACTION_ONGOING
    } else if (mActionStatus != ACTION_ENDING) {
        s16 temp = m_jnt.getHead_y() + current.angle.y+  m_jnt.getBackbone_y();
        mHasAttention = chkAttention(current.pos, temp);
        mEventIdx = 0;
        switch(mStatus) {
            case STATUS_WAIT:
                statusWait();
                break;
            case STATUS_TALK:
                statusTalk();
                break;
            case STATUS_PAY_RUPEE:
                statusPayRupee();
                break;
            case STATUS_DEMO_PAY_RUPEE:
                statusDemoPayRupee();
                break;
            case STATUS_GET_RUPEE:
                statusGetRupee();
                break;
            case STATUS_DEMO_GET_RUPEE:
                statusDemoGetRupee();
                break;
            case STATUS_MONUMENT_COMPLETE:
                statusMonumentComplete();
                break;
            case STATUS_DEMO_MONUMENT_COMPLETE:
                statusDemoMonumentComplete();
                break;
        }
        calcMove();
        lookBack();
        setAttention();
    }
    return TRUE;
}

/* 0000374C-00003830       .text calc_sitpos__10daNpc_Tc_cFv */
void daNpc_Tc_c::calc_sitpos() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    cXyz temp3;
    cXyz temp4;

    cXyz temp;
    cXyz temp2;

    temp.set(0.0f, 80.0f, -25.0f);
    temp3.set(0.0f, 80.0f, -25.0f);

    temp2.set(0.0f, 0.0f, -60.0f);
    temp4.set(0.0f, 0.0f, -60.0f);

    s16 angle = cLib_targetAngleY(&player->current.pos, &mStoolPos);
    mDoMtx_stack_c::transS(mStoolPos);
    mDoMtx_stack_c::YrotM(angle);
    mDoMtx_stack_c::multVec(&temp3, &mSitPos);
    mDoMtx_stack_c::multVec(&temp4, &mWalkToStoolPos);
}

/* 00003830-000038A0       .text set_mtx__10daNpc_Tc_cFv */
void daNpc_Tc_c::set_mtx() {
    J3DModel* model = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
}

/* 000038A0-00003A40       .text _draw__10daNpc_Tc_cFv */
BOOL daNpc_Tc_c::_draw() {
    static const int a_bmt_tbl[5] = {
        -1,
        TC_BMT_TCB,
        TC_BMT_TCC,
        TC_BMT_TCA,
        -1
    };

    static const u8 a_snap_tbl[] = {
        DSNAP_TYPE_TC_NORMAL,
        DSNAP_TYPE_TC_RED,
        DSNAP_TYPE_TC_WHITE,
        DSNAP_TYPE_TC_BLUE,
        DSNAP_TYPE_TC_NORMAL,
    };

    static const u32 dummy[] = {
        0xFF000080,
        0x0000FF80,
        0xFF000080,
        0xFF000080,
        0xFF000080,
        0x00FF0080,
    };
    
    J3DModel* pModel = mpMorf->getModel();
    J3DModelData* pModelData = pModel->getModelData();

    g_env_light.settingTevStruct(TEV_TYPE_ACTOR, &current.pos, &tevStr);
    g_env_light.setLightTevColorType(pModel, &tevStr);
    mBtpAnm.entry(pModelData, mBlinkFrame);
    if (a_bmt_tbl[mType] != -1) {
        J3DMaterialTable* bmt = (J3DMaterialTable*)dComIfG_getObjectRes("Tc", a_bmt_tbl[mType]);
        mpMorf->entryDL(bmt);
    } else {
        mpMorf->entryDL();
    }
    mBtpAnm.remove(pModelData);

#if VERSION == VERSION_DEMO
    dNpc_setShadowModel(mpModel, pModelData, pModel);

    cXyz shadowPos(current.pos.x, current.pos.y + 150.0f, current.pos.z);
    
    mShadowId = dComIfGd_setRealShadow(mShadowId,1,mpModel,&shadowPos,800.0f,current.pos.y-mObjAcch.GetGroundH(),NULL);
    if(mShadowId == 0){
        dComIfGd_setSimpleShadow(
            &current.pos,
            mObjAcch.GetGroundH(),
            40.0f,
            dComIfG_Bgsp()->GetTriPla(mObjAcch.m_gnd)->GetNP()
        );
    }
#else
    cXyz shadowPos(current.pos.x, current.pos.y + 150.0f + REG8_F(18), current.pos.z);
    mShadowId = dComIfGd_setShadow(
        mShadowId, 1, mpMorf->getModel(), &shadowPos, REG8_F(19) + 800.0f, 20.0f,
        current.pos.y, mObjAcch.GetGroundH(), mObjAcch.m_gnd, &tevStr, 0, 1.0f, dDlst_shadowControl_c::getSimpleTex()
    );
#endif

#if VERSION <= VERSION_JPN
    dSnap_RegistFig(a_snap_tbl[mType], this, 1.0f, 1.0f, 1.0f);
#else
    dSnap_RegistFig(a_snap_tbl[mType], this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);
#endif
    if (l_HIO.field_0x34 != 0) {
        mEventCut.getAttnPos();
    }
    return TRUE;
}


/* 00003A40-00003BE0       .text setTower__10daNpc_Tc_cFv */
void daNpc_Tc_c::setTower() {
    m_tower_actor = (daObjSmplbg::Act_c*)fopAcM_Search(&searchTower_CB, this);
    JUT_ASSERT(VERSION_SELECT(0x8EB, 0x8E9, 0x8E9, 0x8E9), m_tower_actor != NULL);
    cXyz temp;
    s16 temp2;
    switch(mType) {
        case TYPE_WHITE:
            temp = l_HIO.field_0x60;
            temp2 = l_HIO.field_0x7A;
            break;
        case TYPE_RED:
            temp = l_HIO.field_0x6C;
            temp2 = l_HIO.field_0x78;
            break;
        
    }

    switch(mType) {
        case TYPE_RED:
        case TYPE_WHITE:
            mDoMtx_stack_c::transS(m_tower_actor->current.pos);
            mDoMtx_stack_c::ZXYrotM(m_tower_actor->shape_angle);
            mDoMtx_stack_c::multVec(&temp, &current.pos);

            s16 temp3 = m_tower_actor->shape_angle.y + temp2;
            if (m_tower_actor->isStop()) {
                if (mAnmPrmIdx == ANM_PRM_IDX_MAWASU || mAnmPrmIdx == ANM_PRM_IDX_WAIT04) {
                    cLib_addCalcAngleS2(&current.angle.y, temp3, 4, 0x800);
                }
            } else {
                current.angle.y = temp3;
            }
            break;
    }
}

/* 00003BE0-00003E90       .text _execute__10daNpc_Tc_cFv */
BOOL daNpc_Tc_c::_execute() {
    // dComIfGs_onGetCollectMap mentioned in debug?
    if (mType == TYPE_WHITE || mType == TYPE_RED || mType == TYPE_NORMAL2) {
        setTower();
    }

    m_jnt.setParam(
    l_HIO.mNpc.mMaxBackboneX, l_HIO.mNpc.mMaxBackboneY, l_HIO.mNpc.mMinBackboneX,
    l_HIO.mNpc.mMinBackboneY, l_HIO.mNpc.mMaxHeadX, l_HIO.mNpc.mMaxHeadY,
    l_HIO.mNpc.mMinHeadX, l_HIO.mNpc.mMinHeadY, l_HIO.mNpc.mMaxTurnStep);

    playTexPatternAnm();

    s8 roomNo = fopAcM_GetRoomNo(this);
    u32 mtrlSndId = mObjAcch.ChkGroundHit() ? dComIfG_Bgsp()->GetMtrlSndId(mObjAcch.m_gnd) : 0;

    field_0x798 = mpMorf->play(&eyePos, mtrlSndId, dComIfGp_getReverb(roomNo));
    mpMorf->calc();
    checkOrder();

    (this->*mCurrActionFunc)(NULL);

    if (mStatus != STATUS_WAIT) {
        if (!mEventCut.cutProc()) {
            cutProc();
        } else {
            if (mEventCut.getNowCut() != -1) {
                switch(mEventCut.getNowCut()) {
                    case 2:
                    case 4:
                        if (mEventCut.getMoveSpeed() == 0.0f) {
                            mAnmPrmIdx = ANM_PRM_IDX_WAIT01;
                        } else {
                            mAnmPrmIdx = ANM_PRM_IDX_WALK01;
                        }
                        break;
                    case 0:
                        mAnmPrmIdx = ANM_PRM_IDX_WAIT01;
                        break;
   
                }
            } else {
                mAnmPrmIdx = ANM_PRM_IDX_WAIT01;
            }
        }
    }

    if (!dComIfGp_event_runCheck()) {
        mEventCut.setAttnNoTurnFlag(false);
        mEventCut.setAttnFlag(false);
    }

    eventOrder();
    setAnm();
    setTexAnm();

    if (mStatus != STATUS_WALK_TO_STOOL) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    cXyz tempPos = current.pos;

    mObjAcch.CrrPos(*dComIfG_Bgsp());

    mDeltaPos = current.pos - tempPos;

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);

    set_mtx();

    if (mType == TYPE_NORMAL) {
        if (mStatus == STATUS_DEMO_RESCUE) {
            setCollision(60.0f, 150.0f);
        }
    } else {
        setCollision(60.0f, 150.0f);
    }
    return TRUE;
}

/* 00003E90-00003F1C       .text _delete__10daNpc_Tc_cFv */
BOOL daNpc_Tc_c::_delete() {
    dComIfG_resDelete(&mPhs, "Tc");
    mSmokeCallBack.remove();
    field_0x714.remove();
    field_0x728.remove();
#if VERSION == VERSION_DEMO
    if(mpMorf != NULL) {
#else
    if(heap != NULL) {
#endif
        mpMorf->stopZelAnime();
    }
    return TRUE;
}

/* 00003F1C-00003F3C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*i_this) {
    return static_cast<daNpc_Tc_c*>(i_this)->_createHeap();
}

/* 00003F3C-00003FC0       .text isCreate__10daNpc_Tc_cFv */
bool daNpc_Tc_c::isCreate() {
    switch(mType) {
        case TYPE_BLUE:
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1708)) {
                return false;
            }
            break;

        case TYPE_NORMAL2:
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80)) {
                return false;
            }
            break;
    }
    return true;
}

/* 00003FC0-00004090       .text _create__10daNpc_Tc_cFv */
cPhs_State daNpc_Tc_c::_create() {
#if VERSION == VERSION_DEMO

    cPhs_State phase_state = dComIfG_resLoad(&mPhs, "Tc");
    if(phase_state == cPhs_COMPLEATE_e) {
        fopAcM_SetupActor(this, daNpc_Tc_c);

#else
    fopAcM_SetupActor(this, daNpc_Tc_c);
    cPhs_State phase_state = dComIfG_resLoad(&mPhs, "Tc");
    if(phase_state == cPhs_COMPLEATE_e) {
#endif
        getArg();

        if(!isCreate()) {
            return cPhs_ERROR_e;
        }

        if(!fopAcM_entrySolidHeap(this, createHeap_CB, VERSION_SELECT(0xCDA0, 0x1C80, 0x1C80, 0x1C80))) {
            return cPhs_ERROR_e;
        }

        cullMtx = mpMorf->getModel()->getBaseTRMtx();
        createInit();
    }
    return phase_state;
}
daNpc_Tc_c::daNpc_Tc_c() {}

/* 000045D0-000047DC       .text _createHeap__10daNpc_Tc_cFv */
BOOL daNpc_Tc_c::_createHeap() {
    J3DModelData* modelData = static_cast<J3DModelData*>(dComIfG_getObjectRes("Tc", TC_BDL_TC));
    JUT_ASSERT(VERSION_SELECT(0xA26, 0xA30, 0xA30, 0xA30), modelData != NULL);

    mpMorf = new mDoExt_McaMorf(
        modelData,
        NULL, NULL, NULL,
        J3DFrameCtrl::EMode_NULL, 1.0f, 0, -1, 1,
        NULL,
        0x80000,
        0x15021222
    );

    if (mpMorf == NULL || mpMorf->getModel() == NULL) {
        return FALSE;
    }
    m_jnt.setHeadJntNum(2);

    JUT_ASSERT(VERSION_SELECT(0xA36, 0xA40, 0xA40, 0xA40), m_jnt.getHeadJntNum() >= 0);

    m_jnt.setBackboneJntNum(1);
    JUT_ASSERT(VERSION_SELECT(0xA38, 0xA42, 0xA42, 0xA42), m_jnt.getBackboneJntNum() >= 0);
    modelData->getJointNodePointer(2)->setCallBack(nodeCallBack);
    modelData->getJointNodePointer(1)->setCallBack(nodeCallBack);
    mpMorf->getModel()->setUserArea(reinterpret_cast<u32>(this));

    mTexPatternNum = 0;
    if (!initTexPatternAnm(false)) {
        return FALSE;
    }

#if VERSION == VERSION_DEMO
    mpModel = mDoExt_J3DModel__create(modelData, 0, 0x11020203);
    return mpModel != NULL ? TRUE : FALSE;
#else
    return TRUE;
#endif
}

/* 000047DC-000047FC       .text daNpc_Tc_Create__FP10fopAc_ac_c */
static cPhs_State daNpc_Tc_Create(fopAc_ac_c* i_this) {
    return ((daNpc_Tc_c*)i_this)->_create();
}

/* 000047FC-0000481C       .text daNpc_Tc_Delete__FP10daNpc_Tc_c */
static BOOL daNpc_Tc_Delete(daNpc_Tc_c* i_this) {
    return ((daNpc_Tc_c*)i_this)->_delete();
}

/* 0000481C-0000483C       .text daNpc_Tc_Execute__FP10daNpc_Tc_c */
static BOOL daNpc_Tc_Execute(daNpc_Tc_c* i_this) {
    return ((daNpc_Tc_c*)i_this)->_execute();
}

/* 0000483C-0000485C       .text daNpc_Tc_Draw__FP10daNpc_Tc_c */
static BOOL daNpc_Tc_Draw(daNpc_Tc_c* i_this) {
    return ((daNpc_Tc_c*)i_this)->_draw();
}

/* 0000485C-00004864       .text daNpc_Tc_IsDelete__FP10daNpc_Tc_c */
static BOOL daNpc_Tc_IsDelete(daNpc_Tc_c*) {
    return TRUE;
}

static actor_method_class l_daNpc_Tc_Method = {
    (process_method_func)daNpc_Tc_Create,
    (process_method_func)daNpc_Tc_Delete,
    (process_method_func)daNpc_Tc_Execute,
    (process_method_func)daNpc_Tc_IsDelete,
    (process_method_func)daNpc_Tc_Draw,
};

actor_process_profile_definition g_profile_NPC_TC = {
    /* LayerID      */ fpcLy_CURRENT_e,
    /* ListID       */ 0x0007,
    /* ListPrio     */ fpcPi_CURRENT_e,
    /* ProcName     */ PROC_NPC_TC,
    /* Proc SubMtd  */ &g_fpcLf_Method.base,
    /* Size         */ sizeof(daNpc_Tc_c),
    /* SizeOther    */ 0,
    /* Parameters   */ 0,
    /* Leaf SubMtd  */ &g_fopAc_Method.base,
    /* Priority     */ PRIO_NPC_TC,
    /* Actor SubMtd */ &l_daNpc_Tc_Method,
    /* Status       */ fopAcStts_UNK40000_e,
    /* Group        */ fopAc_ACTOR_e,
    /* CullType     */ fopAc_CULLBOX_12_e,
};
