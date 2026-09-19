// The name of this .inc file is known because of an assert contained in it.
#include "d/actor/d_a_npc_tt.h"

static const s16 l_bck_ix_tbl[] = {
    dRes_INDEX_TT_BCK_WAIT01_e,
    dRes_INDEX_TT_BCK_TALK01_e,
    dRes_INDEX_TT_BCK_TALK01_e,
    dRes_INDEX_TT_BCK_TALK02_e,
    dRes_INDEX_TT_BCK_STEP01_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_TURN_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_ND_e,
    dRes_INDEX_TT_BCK_POSE_NL_e,
    dRes_INDEX_TT_BCK_POSE_NR_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
    dRes_INDEX_TT_BCK_POSE_CC_e,
};

static const s16 l_bas_ix_tbl[] = {
    dRes_INDEX_TT_BAS_WAIT01_e,
    dRes_INDEX_TT_BAS_TALK01_e,
    dRes_INDEX_TT_BAS_TALK01_e,
    dRes_INDEX_TT_BAS_TALK01_e,
    dRes_INDEX_TT_BAS_STEP01_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_TURN_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_ND_e,
    dRes_INDEX_TT_BAS_POSE_NL_e,
    dRes_INDEX_TT_BAS_POSE_NR_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
    dRes_INDEX_TT_BAS_POSE_CC_e,
};

static const int l_btp_ix_tbl[] = {
    dRes_INDEX_TT_BTP_MABA01_e
};

/* 00002CD4-00002DEC       .text initTexPatternAnm__10daNpc_Tt_cFb */
BOOL daNpc_Tt_c::initTexPatternAnm(bool i_modify) {
    
    J3DModelData* modelData = mpMorf->getModel()->getModelData();

    m_head_tex_pattern = (J3DAnmTexPattern*)dComIfG_getObjectRes("Tt", l_btp_ix_tbl[mTexPatternIdx]);
    JUT_ASSERT(130, m_head_tex_pattern != NULL);

    if (!mBtpAnm.init(modelData, m_head_tex_pattern, TRUE, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, i_modify, FALSE)) {
        return FALSE;
    }

    mBlinkFrame = 0;
    mBlinkTimer = 0;
    return TRUE;
}

/* 00002DEC-00002E78       .text playTexPatternAnm__10daNpc_Tt_cFv */
void daNpc_Tt_c::playTexPatternAnm() {
    if (cLib_calcTimer(&mBlinkTimer) == 0) {
        if (mBlinkFrame >= m_head_tex_pattern->getFrameMax()) {
            mBlinkFrame -= m_head_tex_pattern->getFrameMax();
            mBlinkTimer = cM_rndF(100.0f) + 30.0f;
        } else {
            mBlinkFrame++;
        }
    }
}

/* 00002E78-00002F94       .text setAnm__10daNpc_Tt_cFi */
void daNpc_Tt_c::setAnm(int newAnmIdx) {
    if (mTexPatternIdx != 0) {
        mTexPatternIdx = 0;
        initTexPatternAnm(true);
    }
    s8 anmIdx = newAnmIdx;
    f32 morf = 8.0f;
    f32 speed = 1.0f;
    s32 loopMode = J3DFrameCtrl::EMode_LOOP;

    if(newAnmIdx >= 7 && newAnmIdx <= 31) {
        morf = 7.0f;
        mSoundTimer = morf;
    }

    if (newAnmIdx == 6) {
        speed = 0.9f;
    }

    if (newAnmIdx < 5) {
        clrFlag(0x40);
    } else {
        loopMode = J3DFrameCtrl::EMode_NONE;
    }

    if(newAnmIdx == 2) {
        speed = 0.0f;
    }

    if (anmIdx != mCurrAnmIdx && anmIdx != -1) {
        mCurrAnmIdx = anmIdx;
        mAnmLoopCount = 0;
        mAnmTimer = 0.0f;
        dNpc_setAnm(mpMorf, loopMode, morf, speed, l_bck_ix_tbl[mCurrAnmIdx], l_bas_ix_tbl[mCurrAnmIdx], "Tt");
    }
}

/* 00002F94-00002FFC       .text danceInit__10daNpc_Tt_cFi */
void daNpc_Tt_c::danceInit(int param_1) {
    if (param_1 != 0 || !chkFlag(0x40)) {
        mDanceStep = 0;
        mDanceStepTimer = 8;
        setAnm(5);
        setFlag(0x40);
    }
}

/* 00002FFC-000030B0       .text danceProc__10daNpc_Tt_cFv */
BOOL daNpc_Tt_c::danceProc() {
    if (!chkFlag(0x40)) {
        return FALSE;
        
    }
    if (mpMorf->isMorf()) {
        return FALSE;
    }

    if (mDanceStep == 5 && mDanceStepTimer == 0x19) {
        mHeadAnm.swing_vertical_init(2, 0x1194, -1000, 1);
    }

    if(mDanceStepTimer != 0) {
        mDanceStepTimer--;
        return FALSE;
    }
    return danceNext();
}

/* 000030B0-00003210       .text danceNext__10daNpc_Tt_cFv */
BOOL daNpc_Tt_c::danceNext() {
    if (mDanceStep < 6) {
        mDanceStep++;
    } else {
        mDanceStep = 0;
    }

    switch(mDanceStep) {
        case 0:
        case 2:
            setAnm(5);
            mDanceStepTimer = 8;
            break;
        case 1:
            setAnm(10);
            mDanceStepTimer = 8;
            break;
            
        case 3:
            setAnm(9);
            mDanceStepTimer = 8;
            break;
        case 4:
            setAnm(6);
            mDanceStepTimer = 58;
            break;
        case 5:
            if(chkFlag(0x100)) {
                clrFlag(0x100);
                fopAcM_seStart(this, JA_SE_CV_TT_DANCE_FIN, 0);
            }
            setAnm(8);
            mDanceStepTimer = 53;
            break;
    }
    return mDanceStep == 0;
}
