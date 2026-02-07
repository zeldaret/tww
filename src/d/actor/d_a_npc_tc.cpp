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

    /* Nonmatching */
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
    /* Nonmatching */
}

/* 0000059C-000005C8       .text searchTower_CB__FPvPv */
static void* searchTower_CB(void* i_actor, void* i_this) {
    return static_cast<daNpc_Tc_c*>(i_this)->_searchTower(static_cast<fopAc_ac_c*>(i_actor));
    /* Nonmatching */
}

/* 000005C8-00000630       .text _searchTower__10daNpc_Tc_cFP10fopAc_ac_c */
fopAc_ac_c* daNpc_Tc_c::_searchTower(fopAc_ac_c* i_actor) {
    if (fopAcM_IsActor(i_actor) && fopAcM_GetName(i_actor) == PROC_Obj_Smplbg && ((daObjSmplbg::Act_c*)i_actor)->prm_get_type() == 0) {
        return i_actor;
    }
    return NULL;
    /* Nonmatching */
}



/* 00000630-00000744       .text initTexPatternAnm__10daNpc_Tc_cFb */
BOOL daNpc_Tc_c::initTexPatternAnm(bool param_1) {
    J3DModelData* modeldata = mpMorf->getModel()->getModelData();

    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Tc", l_btp_ix_tbl[mTexPatternNum]);
    JUT_ASSERT(0x188, m_head_tex_pattern != NULL);

    if(mBtpAnm.init(modeldata, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, param_1, FALSE) == FALSE) {
        return FALSE;
    }
    field_0x760 = 0;
    field_0x762 = 0;
    return TRUE;
    /* Nonmatching */
}

/* 00000744-000007D0       .text playTexPatternAnm__10daNpc_Tc_cFv */
void daNpc_Tc_c::playTexPatternAnm() {
    if (cLib_calcTimer(&field_0x762) == 0) {
        if (field_0x760 >= m_head_tex_pattern->getFrameMax()) {
            field_0x760 -= m_head_tex_pattern->getFrameMax();
            field_0x762 = cM_rndF(100.0f) + 30.0f;
        } else {
            field_0x760++;
        }
    }
    /* Nonmatching */
}

/* 000007D0-00000948       .text smoke_set__10daNpc_Tc_cFfffff */
void daNpc_Tc_c::smoke_set(f32 i_rate, f32 i_spread, f32 i_initialVelOmni, f32 i_initialVelAxis, f32 i_initialVelDir) { // maybe rename
    static JGeometry::TVec3<f32> smoke_scale(1.0f, 1.0f, 1.0);
    if(mSmokeCallBack.getEmitter() == NULL) {
        dComIfGp_particle_setToon(dPa_name::ID_COMMON_2022, &field_0x6E0, &field_0x6EC, NULL, 0xB9, &mSmokeCallBack, fopAcM_GetRoomNo(this));
    }

    if(mSmokeCallBack.getEmitter() != NULL) {
        mSmokeCallBack.getEmitter()->setRate(i_rate);
        mSmokeCallBack.getEmitter()->setSpread(i_spread);
        mSmokeCallBack.getEmitter()->setAwayFromCenterSpeed(i_initialVelOmni);
        mSmokeCallBack.getEmitter()->setAwayFromAxisSpeed(i_initialVelAxis);
        mSmokeCallBack.getEmitter()->setDirectionalSpeed(i_initialVelDir);
        mSmokeCallBack.getEmitter()->setGlobalScale(smoke_scale);
    }
    /* Nonmatching */
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
            /* mAnmIdx     */ -1,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 0.0f,
            /* mPlaySpeed  */ 0.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 0,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 1,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 2,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 3,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 4,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 5,
            /* mNextPrmIdx */ 7,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 6,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 6.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 7,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 6.0f,
            /* mPlaySpeed  */ 0.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 7,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 2.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 8,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 9,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 10,
            /* mNextPrmIdx */ 16,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 11,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 12,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 13,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 10,
            /* mNextPrmIdx */ 4,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 11,
            /* mNextPrmIdx */ 4,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 12,
            /* mNextPrmIdx */ 2,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_NONE
        },
        {
            /* mAnmIdx     */ 14,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 15,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 16,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 3,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
        {
            /* mAnmIdx     */ 3,
            /* mNextPrmIdx */ -1,
            /* field_0x02  */ 0,
            /* mMorf       */ 8.0f,
            /* mPlaySpeed  */ 1.0f,
            /* mLoopMode   */ J3DFrameCtrl::EMode_LOOP
        },
    };
//   pfVar8 = &local_1a4.z;
//   pfVar6 = (float *)&UNK_807cc3cc;
//   iVar10 = 0x30;
//   do {
//     pfVar1 = pfVar6 + 1;
//     pfVar6 = pfVar6 + 2;
//     fVar2 = *pfVar6;
//     pfVar8[1] = *pfVar1;
//     pfVar8 = pfVar8 + 2;
//     *pfVar8 = fVar2;
//     iVar10 = iVar10 + -1;
//   } while (iVar10 != 0);

    if (mAnmPrmIdx == 0x16) {
        if (mpMorf->isLoop()) {
            field_0x6CD++;
            if(field_0x6CD >= 3) {
                field_0x6CD = 0;
                mAnmPrmIdx = 1;
            }
        }
    } else {
        field_0x6CD = 0;
    }

    if (mAnmPrmIdx == 0x17) {
        if (mpMorf->isLoop()) {
            field_0x6CE ++;
            if(field_0x6CE >= 5) {
                field_0x6CE = 0;
                mAnmPrmIdx = 0x15;
            }
        }
    } else {
        field_0x6CE = 0;
    }

    if (mAnmPrmIdx == 0xB) {
        if (mpMorf->isLoop()) {
            field_0x6CC++;
            if(field_0x6CC >= 4) {
                field_0x6CC = 0;
                mAnmPrmIdx = 4;
            }
        }
    } else {
        field_0x6CC = 0;
    }

    for (int i = 0; i < 24; i++) {
        a_anm_prm_tbl[i].mMorf = l_HIO.field_0x94[i];
    }

#if VERSION != VERSION_DEMO
    if (mBckIdx == 14 && (int)mpMorf->getFrame() == 1) {
        if(field_0x7FC == 1) {
            fopAcM_monsSeStart(this, JA_SE_CV_TC_B_PUSH_BAR, 0);
        } else if(field_0x7FC == 2) {
            fopAcM_monsSeStart(this, JA_SE_CV_TC_T_PUSH_BAR, 0);
        }
    }
#endif

    if (mBckIdx == 7) {
        if (mpMorf->getFrame() == 1.0f) {
            field_0x6E0 = current.pos;
            field_0x6EC = current.angle;
            smoke_set(10.0f, 0.25f, 0.0f, 2.0f, 15.0f);
        } else {
            mSmokeCallBack.end();
        }
    } 

    if (mBckIdx == 11) {
        field_0x7DC.setall(0.0f);
        mDoMtx_stack_c::copy(mpMorf->getModel()->getAnmMtx(11));
        mDoMtx_stack_c::multVec(&field_0x7DC, &field_0x7DC);
        cXyz pos;

        pos.setall(1.0f);

        if (mpMorf->getFrame() == 1.0f) {
            dComIfGp_particle_set(dPa_name::ID_SCENE_8189, &current.pos, &current.angle, &pos);
            dComIfGp_particle_set(dPa_name::ID_SCENE_818A, &current.pos, &current.angle, &pos);
            dComIfGp_particle_set(dPa_name::ID_SCENE_818B, &current.pos, &current.angle, &pos);
            dComIfGp_particle_set(dPa_name::ID_SCENE_818C, &field_0x7DC, NULL, NULL, 0xff, &field_0x714, fopAcM_GetRoomNo(this));
            dComIfGp_particle_set(dPa_name::ID_SCENE_818D, &field_0x7DC, NULL, NULL, 0xff, &field_0x728, fopAcM_GetRoomNo(this));
        }

        if (mpMorf->getFrame() == 88.0f) {
            f32 sin = cM_ssin(current.angle.y);
            f32 cos = cM_scos(current.angle.y);

            cXyz tempPos(current.pos.x + sin * 10.0f, current.pos.y, current.pos.z + cos * 10.0f);
            field_0x6E0 = tempPos;
            field_0x6EC = current.angle;

            smoke_set(5.0f, 0.25f, 0.0f, 10.0f, 1.0f);
        } else if (mpMorf->getFrame() == 143.0f) {
            field_0x6E0 = current.pos;
            field_0x6EC = current.angle;
            smoke_set(10.0f, 0.25f, 0.0f, 15.0f, 1.0f);
        } else {
            mSmokeCallBack.end();
        }
        if (mpMorf->getFrame() == 178.0f) {
            field_0x714.end();
            field_0x728.end();
        }
    }

    if (mBckIdx == 9) {
        if (mpMorf->getFrame() == 0.0f || mpMorf->getFrame() == 12.0f) {
            field_0x6E0 = current.pos;
            field_0x6EC = current.angle;
            smoke_set(2.0f, 0.25f, 0.0f, 1.0f, 10.0f);
        } else {
            mSmokeCallBack.end();
        }
    }

    if (mBckIdx == 10) {
        if (mpMorf->getFrame() == 24.0f) {
            field_0x6E0 = current.pos;
            field_0x6EC = current.angle;
            smoke_set(4.0f, 0.25f, 0.0f, 2.0f, 10.0f);
        } else {
            mSmokeCallBack.end();
        }
    }
    
    if (mOldAnmPrmIdx != mAnmPrmIdx) {
        if (mAnmPrmIdx == 6) {
            cXyz particlePos(current.pos);
            particlePos.y -= 80.0f;
            cXyz particleScale;
            particleScale.setall(1.0f);

            JPABaseEmitter* pEmitter = dComIfGp_particle_set(dPa_name::ID_SCENE_8152, &particlePos, NULL, &particleScale);
            
            pEmitter->setGlobalParticleScale(0.62f, 0.6f);
            fopAcM_seStart(this, JA_SE_CM_CMN_NOTICE, 0);
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

    s8 texPatternNum = a_tex_pattern_num_tbl[field_0x7F7];
    if (texPatternNum != mTexPatternNum && texPatternNum != -1) {
        mTexPatternNum = texPatternNum;
        initTexPatternAnm(true);
    }

    /* Nonmatching */
}

/* 000011C0-0000136C       .text chkAttention__10daNpc_Tc_cF4cXyzs */
bool daNpc_Tc_c::chkAttention(cXyz param_1, s16 param_2) {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);

    f32 maxAttnDist = l_HIO.mNpc.mMaxAttnDistXZ;
    switch(field_0x7FC) {
        case 1:
        case 2:
            maxAttnDist = l_HIO.mNpc.mMaxAttnDistXZ;
            maxAttnDist *= 0.5f;
            break;
    }

    if (field_0x6CF == 5 || field_0x6CF == 4 || field_0x6CF == 2) {
        maxAttnDist = l_HIO.field_0x2C;
    }

    int maxAttnAngleY = l_HIO.mNpc.mMaxAttnAngleY;
    cXyz temp;
    temp.x = player->current.pos.x - param_1.x;
    temp.z = player->current.pos.z - param_1.z;
    f32 temp2 = std::sqrtf(temp.x * temp.x + temp.z * temp.z);
    s16 temp3 = cM_atan2s(temp.x, temp.z);

    if (field_0x7E8) {
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


    if (field_0x7FB == 1 || field_0x7FB == 2) {
        eventInfo.onCondition(dEvtCnd_CANTALK_e);
        if (field_0x7FB == 1) {
            fopAcM_orderSpeakEvent(this);
        }
    } else if (field_0x7FB == 8 || field_0x7FB == 9) {
        fopAcM_orderOtherEvent(this, a_demo_name_tbl[field_0x7FB - 3], 0x14F);
    }
    else if (field_0x7FB >= 3) {
        fopAcM_orderOtherEvent(this, a_demo_name_tbl[field_0x7FB - 3], -1);
    }
    /* Nonmatching */
}

/* 00001424-00001470       .text checkOrder__10daNpc_Tc_cFv */
void daNpc_Tc_c::checkOrder() {
    if (eventInfo.mCommand == dEvtCmd_INDEMO_e) {
        field_0x7FB = 0;
        return;
    }

    if (eventInfo.mCommand != dEvtCmd_INTALK_e) {
        return;
    }

    if (field_0x7FB != 1 && field_0x7FB != 2) {
        return;
    }
    field_0x7FB = 0;
    mTalkingNearJail = true;

    /* Nonmatching */
}

/* 00001470-000014FC       .text existTcMonument__10daNpc_Tc_cFv */
bool daNpc_Tc_c::existTcMonument() {
    
    if(dComIfGs_isStageTbox(dSv_save_c::STAGE_DRC, 0xF) || dComIfGs_isStageTbox(dSv_save_c::STAGE_FW, 0xF) 
    || dComIfGs_isStageTbox(dSv_save_c::STAGE_TOTG, 0xF) || dComIfGs_isStageTbox(dSv_save_c::STAGE_WT, 0xF)
    || dComIfGs_isStageTbox(dSv_save_c::STAGE_ET, 0xF)) {
        return true;
    }
    return false;
    /* Nonmatching */
}

/* 000014FC-0000156C       .text anmAtr__10daNpc_Tc_cFUs */
void daNpc_Tc_c::anmAtr(u16 i_msgStatus) {
    static const s8 anm_atr[] = {
        0x01,
        0x03,
        0x02,
        0x04,
        0x0A,
        0x0B,
        0x0C,
        0x0D,
        0x0E,
        0x10,
        0x12,
        0x11,
        0x16,
        0x17,
        0x15,
        0x14
    };

    switch (i_msgStatus) {
        case fopMsgStts_MSG_TYPING_e:
            if(field_0x6C8) {
                return;
            }

            u8 msgAnmAtr = dComIfGp_getMesgAnimeAttrInfo();
            field_0x6C8 = TRUE;
            if(anm_atr[msgAnmAtr] == 0x10 && mAnmPrmIdx == 4) {
                return;
            }

            mAnmPrmIdx = anm_atr[msgAnmAtr];
            break;


        case fopMsgStts_MSG_DISPLAYED_e:
            field_0x6C8 = FALSE;
            break;
    }
    /* Nonmatching */
}

/* 0000156C-00001618       .text stopTower__10daNpc_Tc_cFv */
void daNpc_Tc_c::stopTower() {
    JUT_ASSERT(VERSION_SELECT(0x3F5, 0x3F4, 0x3F4, 0x3F4), m_tower_actor != NULL);

    daObjSmplbg::Act_c* tower = m_tower_actor;
    switch (field_0x7FC) {

        case 1:
        case 2:
            m_jnt.offHeadLock();
            mAnmPrmIdx = 0x14;
            tower->onStop();
            break;
        case 0:
            tower->onStop();
            break;
    }
    /* Nonmatching */
}

/* 00001618-000017A4       .text startTower__10daNpc_Tc_cFv */
void daNpc_Tc_c::startTower() {
    JUT_ASSERT(VERSION_SELECT(0x408, 0x407, 0x407, 0x407), m_tower_actor != NULL);
    daObjSmplbg::Act_c* tower = m_tower_actor;

    cXyz temp;
    s16 temp2;
    switch(field_0x7FC) {
        case 2:
            temp = l_HIO.field_0x60;
            temp2 = l_HIO.field_0x7A;
            break;
        case 1:
            temp = l_HIO.field_0x6C;
            temp2 = l_HIO.field_0x78;
            break;
    }

    switch(field_0x7FC) {
        case 1:
        case 2:
            m_jnt.onHeadLock();
            mDoMtx_stack_c::transS(m_tower_actor->current.pos);
            mDoMtx_stack_c::ZXYrotM(m_tower_actor->shape_angle);
            temp2 = m_tower_actor->shape_angle.y + temp2;
            cLib_addCalcAngleS2(&current.angle.y, temp2, 4, 0x400);
            if(cLib_distanceAngleS(current.angle.y, temp2) < 0x600) {
                tower->offStop();
                mAnmPrmIdx = 0x13;
            }
            break;

        default:
            tower->offStop();
            break;
    }

    /* Nonmatching */
}

/* 000017A4-00001900       .text next_msgStatusBlue__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusBlue(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e; // maybe int
    if ((mAnmPrmIdx == 0x11 || mAnmPrmIdx == 0x12) && !mpMorf->isStop()) {
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
    /* Nonmatching */
}

/* 00001900-00001AEC       .text next_msgStatusNormal__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatusNormal(u32* pMsgNo) {
    u16 msgStatus = fopMsgStts_MSG_CONTINUES_e; // maybe int
    if ((mAnmPrmIdx == 0x11 || mAnmPrmIdx == 0x12) && !mpMorf->isStop()) {
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
    /* Nonmatching */
}

/* 00001AEC-00001B64       .text next_msgStatus__10daNpc_Tc_cFPUl */
u16 daNpc_Tc_c::next_msgStatus(u32* pMsgNo) {
    u16 msg;
    switch(field_0x7FC) {
        case 4:
            msg = next_msgStatusNormal(pMsgNo);
            break;
        case 0:
            msg = next_msgStatusNormal2(pMsgNo);
            break;
        case 3:
            msg = next_msgStatusBlue(pMsgNo);
            break;
        case 1:
            msg = next_msgStatusRed(pMsgNo);
            break;
        case 2:
            msg = next_msgStatusWhite(pMsgNo);
            break;
        default:
            msg = fopMsgStts_MSG_ENDS_e;
            break;
    }
    return msg;
    /* Nonmatching */
}

/* 00001B64-00001B88       .text setFirstMsg__10daNpc_Tc_cFPbUlUl */
u32 daNpc_Tc_c::setFirstMsg(bool* param_1, u32 param_2, u32 param_3) {
    if (!*param_1) {
        *param_1 = true;
    } else {
        param_2 = param_3;
    }
    return param_2; // unsure if real
    /* Nonmatching */
}

/* 00001B88-00001BE0       .text getMsgNormal__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgNormal() {
    u32 msg;
    if (!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B40)) {
        msg = 0x10D3;
        field_0x7F1 = true;
    } else {
        msg= 0x10D9;
    }
    return msg;

    /* Nonmatching */
}

/* 00001BE0-00001BE8       .text getMsgBlue__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsgBlue() {
    return 0xDDD;
    /* Nonmatching */
}

/* 00001BE8-00001C74       .text getMsg__10daNpc_Tc_cFv */
u32 daNpc_Tc_c::getMsg() {
    u32 msg = 0;
    switch(field_0x7FC) {
        case 4:
            msg = getMsgNormal();
            break;
        case 0:
            msg = getMsgNormal2();
            break;
        case 3:
            msg = getMsgBlue();
            break;
        case 1:
            msg = getMsgRed();
            break;
        case 2:
            msg = getMsgWhite();
            break;
    }
    return msg;
    /* Nonmatching */
}

/* 00001C74-00001C98       .text getArg__10daNpc_Tc_cFv */
void daNpc_Tc_c::getArg() {
    field_0x7FC = fopAcM_GetParam(this) & 0xf;
    if(field_0x7FC != 0xF) {
        return;
    }
    field_0x7FC = 4;
    /* Nonmatching */
}

extern dCcD_SrcCyl dNpc_cyl_src;
/* 00001C98-0000202C       .text createInit__10daNpc_Tc_cFv */
void daNpc_Tc_c::createInit() {
#if VERSION != VERSION_DEMO
    if (field_0x7FC == 4) {
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
    field_0x7F1 = false;
    field_0x7F7 = 1;
    switch (field_0x7FC) {
        case 4:
            mAnmPrmIdx = 3;
            fopAcM_Search(&searchStoolPos, this);
            if (setAction(&daNpc_Tc_c::help_action, NULL)) {
                gravity = 0.0f;
                mAcchCir.SetWall(60.0f, 50.0f);
            }

            break;
        case 3:
        case 0:
            gravity = -9.0f;
            mAnmPrmIdx = 1;
            if (setAction(&daNpc_Tc_c::wait_action, NULL)) {
                mAcchCir.SetWall(60.0f, 50.0f);
            }
            break;
        case 1:
        case 2:
            gravity = -9.0f;
            m_jnt.onHeadLock();
            mAnmPrmIdx = 0x13;
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
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 000020C4-00002148       .text setAttention__10daNpc_Tc_cFv */
void daNpc_Tc_c::setAttention() {
    s8 temp = mAnmPrmIdx;
    if (temp != 1 && temp != 5 && temp != 4 && temp != 10 &&
        temp != 0x13 && temp != 0x15 && temp != 0x14) {
        return;
    }

    eyePos.set(mEyePos.x, mEyePos.y, mEyePos.z);

    attention_info.position.set(mAttPos.x, mAttPos.y + l_HIO.mNpc.mAttnYOffset, mAttPos.z);

    /* Nonmatching */
}

/* 00002148-00002220       .text calcMove__10daNpc_Tc_cFv */
void daNpc_Tc_c::calcMove() {
    f32 speed;
    if (mAnmPrmIdx != 5) {
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
    /* Nonmatching */
}

/* 00002220-000024C4       .text lookBack__10daNpc_Tc_cFv */
void daNpc_Tc_c::lookBack() {
    cXyz temp6;
    cXyz temp3(0.0f, 0.0f, 0.0f);
    cXyz* dstPos = NULL;
    s16 desiredYRot = current.angle.y;
    s16 target;
    if (field_0x6CF == 3) {
        m_jnt.setTrn();
    }
    s8 temp = field_0x6CF;
    if (temp == 5 || temp == 7 || temp == 2) {
        m_jnt.setTrn();
        field_0x7E8 = true;
    }

    if (field_0x7FC == 2 || field_0x7FC == 1) {
        if (field_0x6CF == 1) {
            if (mAnmPrmIdx == 0x13 || mAnmPrmIdx == 0x14) {
                m_jnt.onBackBoneLock();
                m_jnt.clrTrn();
            }
        } else if (mAnmPrmIdx == 0x13 || mAnmPrmIdx == 0x14) {
            m_jnt.onBackBoneLock();
            m_jnt.clrTrn();
        } else {
            m_jnt.offBackBoneLock();
            m_jnt.setTrn();
            field_0x7E8 = true;
        }
    }

    if (field_0x6CF == 8) {
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
        
    } else if (field_0x7E8){
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
        cLib_addCalcAngleS2(&field_0x78C, target, 4, 0x800);
    } else {
        field_0x78C = 0;
    }
    m_jnt.lookAtTarget(&current.angle.y, dstPos, temp3, desiredYRot, field_0x78C, false);

    /* Nonmatching */
}

/* 000024C4-00002594       .text statusWait__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWait() {
    if (field_0x7FC == 2 || field_0x7FC == 1) {
        JUT_ASSERT(VERSION_SELECT(0x5FE, 0x601, 0x601, 0x601), m_tower_actor != NULL);

        if (!m_tower_actor->isStop()) {
            mAnmPrmIdx = 0x14;
        } else {
            mAnmPrmIdx = 0x13;
        }
    }

    if (mTalkingNearJail) {
        field_0x6CF = 3;
    } else if (field_0x7E8) {
        field_0x7FB = 2;
    }
    /* Nonmatching */
}

/* 00002594-000026E4       .text statusSit__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusSit() {
    mSmokeCallBack.end();
    calc_sitpos();
    current.pos.set(mSitPos);
    gravity = 0.0f;
    
    if(mAnmPrmIdx != 6) {
        if(dLib_checkPlayerInCircle(current.pos, l_HIO.field_0x2C, 100.0f)) {
            if (!mHasEnteredSitRadius) {
                mHasEnteredSitRadius = true;
                field_0x7FB = 3;
                field_0x6CF = 10;
                return;
            }
            mAnmPrmIdx = 6;
        }
    }

    if(mpMorf->isStop() && mAnmPrmIdx == 6) {
        speedF = l_HIO.field_0x38;
        speed.y = l_HIO.field_0x40;
        gravity = l_HIO.field_0x3C;
        mAnmPrmIdx = 7;
        field_0x6CF = 4;
    }
    /* Nonmatching */
}

/* 000026E4-00002798       .text statusJump__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusJump() {
    if (speed.y <= 0.0f && mAnmPrmIdx == 7) {
        mAnmPrmIdx = 8;
    }

    if (mObjAcch.ChkGroundHit() && mAnmPrmIdx == 8) {
        speedF = 0.0f;
        mAnmPrmIdx = 9;
        mJumpLandingTimer = 0x33;
        return;
    }

    if (cLib_calcTimer(&mJumpLandingTimer) == 0 && mAnmPrmIdx == 9) {
        mAnmPrmIdx = 5;
        field_0x6CF = 5;
    }
    /* Nonmatching */
}

/* 00002798-000029B0       .text statusWalkToJail__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWalkToJail() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    
    s16 angle = cLib_targetAngleY(&current.pos, &player->current.pos);
    if (mObjAcch.ChkWallHit()) {
        if (mTalkingNearJail) {
            mTargetSpeed = 0.0f;
            speedF = 0.0f;

            if (!field_0x7F1 || l_HIO.field_0x44 != 0) {
                mAnmPrmIdx = 2;
                dComIfGp_event_reset();
                field_0x6CF = 12;
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B40) == 0) {
                    if (dComIfGs_getClearCount() != 0) {
                        field_0x7FB = 6;
                    } else {
                        field_0x7FB = 5;
                    }
                } else {
                    field_0x7FB = 7;
                }

                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B40);
                field_0x7F1 = true;
                return;

            }
            field_0x6CF = 6;
        } else if (field_0x7E8) {
            field_0x7FB = 2;
        }
    }

    if (mObjAcch.ChkWallHit() && std::fabsf(cM_scos(angle)) > 0.9f) {
        mTargetSpeed = 0.0f;
        if (speedF == 0.0f) {
            mAnmPrmIdx = 1;
        }
    } else {
        mAnmPrmIdx = 5;
        mTargetSpeed = l_HIO.field_0x58;
        if (speedF == 0.0f) {
            speedF = l_HIO.field_0x5C;
        }
    }
    if (mObjAcch.ChkWallHit()) {
        if(!dLib_checkPlayerInCircle(current.pos, l_HIO.field_0x30, 100.0f)) {
            field_0x6CF = 8;
        }
    }
    /* Nonmatching */
}

/* 000029B0-00002A20       .text statusTalkNearJail__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusTalkNearJail() {
    mTargetSpeed = 0.0f;
    speedF = 0.0f;
    if (talk(1) == 0x12) {
        field_0x6CF = 7;
        dComIfGp_event_reset();
        mTalkingNearJail = false;
    }
    /* Nonmatching */
}

/* 00002A20-00002BD4       .text statusWaitNearJail__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWaitNearJail() {
    fopAc_ac_c* player = dComIfGp_getPlayer(0);
    
    s16 angle = cLib_targetAngleY(&current.pos, &player->current.pos);
    if (mObjAcch.ChkWallHit()) {
        if (mTalkingNearJail) {
            mTargetSpeed = 0.0f;
            speedF = 0.0f;

            if (!field_0x7F1 || l_HIO.field_0x44 != 0) {
                mAnmPrmIdx = 2;
                dComIfGp_event_reset();
                field_0x6CF = 12;
                if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B40) == 0) {
                    field_0x7FB = 5;
                } else {
                    field_0x7FB = 7;
                }

                dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B40);
                field_0x7F1 = true;
                return;

            }
            field_0x6CF = 6;
        } else if (field_0x7E8) {
            field_0x7FB = 2;
        }
    }

    if (mObjAcch.ChkWallHit() && std::fabsf(cM_scos(angle)) > 0.9f) {
        mTargetSpeed = 0.0f;
        if (speedF == 0.0f) {
            mAnmPrmIdx = 1;
        }
    } else {
        mAnmPrmIdx = 5;
        mTargetSpeed = l_HIO.field_0x58;
        if (speedF == 0.0f) {
            speedF = l_HIO.field_0x5C;
        }
    }

    /* Nonmatching */
}

/* 00002BD4-00002D80       .text statusWalkToStool__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusWalkToStool() {
    calc_sitpos();
    if(dLib_checkPlayerInCircle(current.pos, l_HIO.field_0x30, 100.0f)) {
        mTargetSpeed = 0.0f;
        if (speedF == 0.0f) {
            field_0x6CF = 5;
        }
        
    } else {
        mStoolLookPos.set(mStoolPos);
        cLib_targetAngleY(&current.pos, &mWalkToStoolPos);
        cLib_addCalcPosXZ2(&current.pos, mWalkToStoolPos, 0.1f, speedF);
        f32 temp = (mWalkToStoolPos - current.pos).absXZ();
        if(temp < 5.0f) {
            mTargetSpeed = 0.0f;
            if (speedF == 0.0f) {
                mAnmPrmIdx = 1;
                field_0x6CF = 9;
            }
        } else {
            mAnmPrmIdx = 5;
            mTargetSpeed = l_HIO.field_0x58;   
        }
    }
    /* Nonmatching */
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
            mAnmPrmIdx = 3;
        }

        if (speed.y < 0.0f && current.pos.y < mSitPos.y) {
            gravity = 0.0f;
            speed.y = 0.0f;
            current.pos.y = mSitPos.y;
        }

        cLib_addCalcPosXZ2(&current.pos, mSitPos, 0.1f, 4.0f);
        f32 diff = (mSitPos - current.pos).absXZ();
        if (current.pos.y == mSitPos.y && diff < 5.0f) {
            field_0x6E0.set(current.pos);
            field_0x6EC = current.angle;
            smoke_set(2.0f, 0.25f, 0.0f, 5.0f, 20.0f);
            field_0x6CF = 2;
        }
    }
    /* Nonmatching */
}

/* 00002F94-00003028       .text statusTalk__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusTalk() {
    if(talk(1) != 0x12) {
        return;
    }
    
    switch(field_0x7FC) {
        case 1:
        case 2:
            startTower();
            mAnmPrmIdx = 0x13;
            // fallthrough
        case 0:
            startTower();
            // fallthrough
        default:
            mAnmPrmIdx = 1;
            field_0x6CF = 1;
            dComIfGp_event_reset();
            mTalkingNearJail = false;
            break;
    }

    /* Nonmatching */
}

/* 00003028-00003088       .text statusPayRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusPayRupee() {
    if(talk(1) == 0x12) {
        dComIfGp_event_reset();
        field_0x7FB = 9;
        field_0x6CF = 14;
    }
    /* Nonmatching */
}

/* 00003088-000030F8       .text statusDemoPayRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoPayRupee() {
    if(dComIfGp_evmng_endCheck("TC_PAY_RUPEE")) {
        dComIfGp_event_reset();
        field_0x7FB = 1;
        field_0x6CF = 3;
    }
    /* Nonmatching */
}

/* 000030F8-00003158       .text statusGetRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusGetRupee() {
    if(talk(1) == 0x12) {
        dComIfGp_event_reset();
        field_0x7FB = 8;
        field_0x6CF = 16;
    }
    /* Nonmatching */
}

/* 00003158-000031CC       .text statusDemoGetRupee__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoGetRupee() {
    if(dComIfGp_evmng_endCheck("TC_GET_RUPEE")) {
        field_0x812 = true;
        dComIfGp_event_reset();
        field_0x7FB = 1;
        field_0x6CF = 3;
    }
    /* Nonmatching */
}

/* 000031CC-0000322C       .text statusMonumentComplete__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusMonumentComplete() {
    if(talk(1) == 0x12) {
        dComIfGp_event_reset();
        field_0x7FB = 8;
        field_0x6CF = 18;
    }
    /* Nonmatching */
}

/* 0000322C-000032A0       .text statusDemoMonumentComplete__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoMonumentComplete() {
    if(dComIfGp_evmng_endCheck("TC_GET_RUPEE")) {
        field_0x813 = true;
        dComIfGp_event_reset();
        field_0x7FB = 1;
        field_0x6CF = 3;
    }
    /* Nonmatching */
}

/* 000032A0-00003308       .text statusDemoJump__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoJump() {
    if(dComIfGp_evmng_endCheck("TC_JUMP_DEMO")) {
        field_0x6CF = 5;
        dComIfGp_event_reset();
    }
    /* Nonmatching */
}

/* 00003308-00003384       .text statusDemoRescue__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoRescue() {
    if(dComIfGp_evmng_endCheck("TC_RESCUE")) {
        dComIfGs_onEventBit(dSv_event_flag_c::UNK_0B80);
        dComIfGp_event_reset();
        fopAcM_delete(this);
    }
    /* Nonmatching */
}

/* 00003384-00003430       .text statusDemoTalk__10daNpc_Tc_cFv */
void daNpc_Tc_c::statusDemoTalk() {
    if (dComIfGp_evmng_endCheck("TC_TALK_NEAR_JAIL") || dComIfGp_evmng_endCheck("TC_TALK_NEAR_JAIL_S") || dComIfGp_evmng_endCheck("TC_TALK_NEAR_JAIL2")) {
        field_0x6CF = 7;
        dComIfGp_event_reset();
        mTalkingNearJail = false;
    }
    /* Nonmatching */
}

/* 00003430-00003610       .text help_action__10daNpc_Tc_cFPv */
BOOL daNpc_Tc_c::help_action(void*) {
    //check switch order if not working
    if (mActionStatus == ACTION_STARTING) {
        field_0x6CF = 2;
        mActionStatus++; // ACTION_ONGOING
    } else if (mActionStatus != ACTION_ENDING) {
        if (dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80)) {
            fopAcM_delete(this);
        }
        if (dComIfGp_evmng_endCheck("OpenDoor")) {
            mTargetSpeed = 0.0f;
            speedF = 0.0f;
            field_0x7FB = 4;
            field_0x6CF = 11;
            return true;
        } else {
            s16 temp = m_jnt.getHead_y() + current.angle.y+  m_jnt.getBackbone_y();
            field_0x7E8 = chkAttention(current.pos, temp);
            field_0x7FB = 0;
            switch(field_0x6CF) {
                case 1:
                    statusWait();
                    break;
                case 3:
                    statusTalk();
                    break;
                case 2:
                    statusSit();
                    break;
                case 4:
                    statusJump();
                    break;
                case 5:
                    statusWalkToJail();
                    break;
                case 6:
                    statusTalkNearJail();
                    break;
                case 7:
                    statusWaitNearJail();
                    break;
                case 8:
                    statusWalkToStool();
                    break;
                case 9:
                    statusSitToStool();
                    break;
                case 10:
                    statusDemoJump();
                    break;
                case 0xb:
                    statusDemoRescue();
                    break;
                case 0xc:
                    statusDemoTalk();
                    break;
            }
            calcMove();
            lookBack();
            setAttention();
        }
    }
    return true;
    /* Nonmatching */
}

/* 00003610-0000374C       .text wait_action__10daNpc_Tc_cFPv */
BOOL daNpc_Tc_c::wait_action(void*) {
    if (mActionStatus == 0) {
        field_0x6CF = 1;
        mActionStatus++;
    } else if (mActionStatus != -1) {
        s16 temp = m_jnt.getHead_y() + current.angle.y+  m_jnt.getBackbone_y();
        field_0x7E8 = chkAttention(current.pos, temp);
        field_0x7FB = 0;
        switch(field_0x6CF) {
            case 1:
                statusWait();
                break;
            case 3:
                statusTalk();
                break;
            case 0xd:
                statusPayRupee();
                break;
            case 0xe:
                statusDemoPayRupee();
                break;
            case 0xf:
                statusGetRupee();
                break;
            case 0x10:
                statusDemoGetRupee();
                break;
            case 0x11:
                statusMonumentComplete();
                break;
            case 0x12:
                statusDemoMonumentComplete();
                break;
        }
        calcMove();
        lookBack();
        setAttention();
    }
    return TRUE;
    /* Nonmatching */
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
    /* Nonmatching */
}

/* 00003830-000038A0       .text set_mtx__10daNpc_Tc_cFv */
void daNpc_Tc_c::set_mtx() {
    J3DModel* model = mpMorf->getModel();
    mDoMtx_stack_c::transS(current.pos);
    mDoMtx_stack_c::YrotM(current.angle.y);
    model->setBaseTRMtx(mDoMtx_stack_c::get());
    /* Nonmatching */
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
        DSNAP_TYPE_UNK79,
        DSNAP_TYPE_UNK7A,
        DSNAP_TYPE_UNK7C,
        DSNAP_TYPE_UNK7B,
        DSNAP_TYPE_UNK79,
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
    mBtpAnm.entry(pModelData, field_0x760);
    if (a_bmt_tbl[field_0x7FC] != -1) {
        J3DMaterialTable* bmt = (J3DMaterialTable*)dComIfG_getObjectRes("Tc", a_bmt_tbl[field_0x7FC]);
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
    dSnap_RegistFig(a_snap_tbl[field_0x7FC], this, 1.0f, 1.0f, 1.0f);
#else
    dSnap_RegistFig(a_snap_tbl[field_0x7FC], this, current.pos, current.angle.y, 1.0f, 1.0f, 1.0f);
#endif
    if (l_HIO.field_0x34 != 0) {
        mEventCut.getAttnPos();
    }
    return TRUE;
    /* Nonmatching */
}


/* 00003A40-00003BE0       .text setTower__10daNpc_Tc_cFv */
void daNpc_Tc_c::setTower() {
    m_tower_actor = (daObjSmplbg::Act_c*)fopAcM_Search(&searchTower_CB, this);
    JUT_ASSERT(VERSION_SELECT(0x8EB, 0x8E9, 0x8E9, 0x8E9), m_tower_actor != NULL);
    cXyz temp;
    s16 temp2;
    switch(field_0x7FC) {
        case 2:
            temp = l_HIO.field_0x60;
            temp2 = l_HIO.field_0x7A;
            break;
        case 1:
            temp = l_HIO.field_0x6C;
            temp2 = l_HIO.field_0x78;
            break;
        
    }

    switch(field_0x7FC) {
        case 1:
        case 2:
            mDoMtx_stack_c::transS(m_tower_actor->current.pos);
            mDoMtx_stack_c::ZXYrotM(m_tower_actor->shape_angle);
            mDoMtx_stack_c::multVec(&temp, &current.pos);

            s16 temp3 = m_tower_actor->shape_angle.y + temp2;
            if (m_tower_actor->field_0x2D8 != 0) {
                if (mAnmPrmIdx == 0x13 || mAnmPrmIdx == 0x14) {
                    cLib_addCalcAngleS2(&current.angle.y, temp3, 4, 0x800);
                }
            } else {
                current.angle.y = temp3;
            }
            break;
    }

    /* Nonmatching */
}

/* 00003BE0-00003E90       .text _execute__10daNpc_Tc_cFv */
BOOL daNpc_Tc_c::_execute() {
    // dComIfGs_onGetCollectMap mentioned in debug?
    if (field_0x7FC == 2 || field_0x7FC == 1 || field_0x7FC == 0) { // is this an inline?
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

    if (field_0x6CF != 1) {
        if (!mEventCut.cutProc()) {
            cutProc();
        } else {
            if (mEventCut.getNowCut() != -1) {
                switch(mEventCut.getNowCut()) {
                    case 2:
                    case 4:
                        if (mEventCut.getMoveSpeed() == 0.0f) {
                            mAnmPrmIdx = 1;
                        } else {
                            mAnmPrmIdx = 5;
                        }
                        break;
                    case 0:
                        mAnmPrmIdx = 1;
                        break;
   
                }
            } else {
                mAnmPrmIdx = 1;
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
    if (field_0x6CF != 8) {
        fopAcM_posMoveF(this, mStts.GetCCMoveP());
    }
    cXyz tempPos = current.pos;

    mObjAcch.CrrPos(*dComIfG_Bgsp());

    mDeltaPos = current.pos - tempPos;

    tevStr.mRoomNo = dComIfG_Bgsp()->GetRoomId(mObjAcch.m_gnd);
    tevStr.mEnvrIdxOverride = dComIfG_Bgsp()->GetPolyColor(mObjAcch.m_gnd);


    set_mtx();

    if (field_0x7FC == 4) {
        if (field_0x6CF == 0xb) {
            setCollision(60.0f, 150.0f);
        }
    } else {
        setCollision(60.0f, 150.0f);
    }
    return TRUE;

    /* Nonmatching */
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
    /* Nonmatching */
}

/* 00003F1C-00003F3C       .text createHeap_CB__FP10fopAc_ac_c */
static BOOL createHeap_CB(fopAc_ac_c*i_this) {
    return static_cast<daNpc_Tc_c*>(i_this)->_createHeap();
    /* Nonmatching */
}

/* 00003F3C-00003FC0       .text isCreate__10daNpc_Tc_cFv */
bool daNpc_Tc_c::isCreate() {
    switch(field_0x7FC) {
        case 3:
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_1708)) {
                return false;
            }
            break;

        case 0:
            if(!dComIfGs_isEventBit(dSv_event_flag_c::UNK_0B80)) {
                return false;
            }
            break;
    }
    return true;
    /* Nonmatching */
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

    /* Nonmatching */
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
    /* Nonmatching */
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
