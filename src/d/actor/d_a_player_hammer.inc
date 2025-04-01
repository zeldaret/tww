/**
 * d_a_player_hammer.inc
 *
 * Code relating to the Skull Hammer item.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is known because of an assert contained within
 * a function from this file.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"

/* 8015023C-80150324       .text setHammerModel__9daPy_lk_cFv */
void daPy_lk_c::setHammerModel() {
    J3DAnmTransform *bck = getItemAnimeResource(LKANM_BCK_HAMMERDAM);
    JKRHeap *oldHeap = setItemHeap();
    J3DModelData *tmp_modelData =
        initModel(&mpEquipItemModel, LINK_BDL_HAMMER, 0x37221222);
    int ret = mSwordAnim.init(tmp_modelData, bck, false, J3DFrameCtrl::EMode_LOOP,
                              1.0f, 0, -1, false);
    if (!ret) {
      JUT_ASSERT(32, FALSE);
    }
    mSwBlur.mpPosBuffer = new (0x20) Vec[2 * 0x300];
    mDoExt_setCurrentHeap(oldHeap);
    m35EC = 0.0f;
}

/* 80150324-801508FC       .text setHammerQuake__9daPy_lk_cFP13cBgS_PolyInfoPC4cXyzi */
void daPy_lk_c::setHammerQuake(cBgS_PolyInfo*, const cXyz*, int) {
    /* Nonmatching */
    static JGeometry::TVec3<f32> smoke_kusa_particle_scale;
    static JGeometry::TVec3<f32> emitter_scale;
    static JGeometry::TVec3<f32> emitter_trans;
}

/* 801508FC-80150B60       .text setHammerWaterSplash__9daPy_lk_cFv */
void daPy_lk_c::setHammerWaterSplash() {
    /* Nonmatching */
}

/* 80150B60-80150C40       .text procHammerSideSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerSideSwing_init() {
    /* Nonmatching - floats */
    commonProcInit(daPyProc_HAMMER_SIDE_SWING_e);
    setSingleMoveAnime(ANM_HAMSWINGA, daPy_HIO_ham_c0::m.field_0x8,
                       daPy_HIO_ham_c0::m.field_0xC, daPy_HIO_ham_c0::m.field_0x0,
                       daPy_HIO_ham_c0::m.field_0x14);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    voiceStart(1);
    m34D4 = shape_angle.y;
    setBlurPosResource(LKANM__HAMMERSIDE_POS);
    setAtParam(AT_TYPE_SKULL_HAMMER, 4, dCcG_At_Spl_UNK0, dCcG_SE_UNK5,
               dCcG_AtHitMark_Nrm_e, 17, 50.0f);
    mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_HAMSWINGAA));
    m35EC = daPy_HIO_ham_c0::m.field_0xC;
    return true;
}

/* 80150C40-80150DDC       .text procHammerSideSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerSideSwing() {
    m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.0099999998f) {
      mVelocity = 0.0f;
      m34B8 = 3;
      checkNextMode(0);
      return true;
    } else {
      if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >
          daPy_HIO_ham_c0::m.field_0x10) {
        f32 dVar4 = mVelocity;
        u8 uVar1 = m34B8;
        mVelocity = 0.0f;
        m34B8 = 3;
        if (checkNextMode(1)) {
          return true;
        }
        mVelocity = dVar4;
        m34B8 = uVar1;
      }
      if (changeCutReverseProc(ANM_CUTREL)) {
        setHammerQuake(NULL, NULL, -1);
        return true;
      } else {
        if (mpAttnActorLockOn != NULL) {
          setShapeAngleToAtnActor();
          m34D4 = shape_angle.y;
        } else {
          cLib_addCalcAngleS(&shape_angle.y, m34D4, daPy_HIO_turn_c0::m.field_0x4,
                             daPy_HIO_turn_c0::m.field_0x0,
                             daPy_HIO_turn_c0::m.field_0x2);
        }
        current.angle.y = shape_angle.y;
        if ((mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >=
             daPy_HIO_ham_c0::m.field_0x18) &&
            (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() <
             daPy_HIO_ham_c0::m.field_0x1C)) {
          if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_HAMMER_SWING);
          }
          onResetFlg0(daPyRFlg0_UNK2);
        }
      }
    }
    return true;
}

/* 80150DDC-80150F08       .text procHammerFrontSwingReady_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwingReady_init() {
    /* Nonmatching - floats */
    commonProcInit(daPyProc_HAMMER_FRONT_SWING_READY_e);
    setSingleMoveAnime(ANM_HAMSWINGBPRE, daPy_HIO_ham_c0::m.field_0x20,
                       daPy_HIO_ham_c0::m.field_0x24,
                       daPy_HIO_ham_c0::m.field_0x2,
                       daPy_HIO_ham_c0::m.field_0x28);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    if (mpAttention->Lockon() || (mStickDistance <= 0.05f)) {
      m34D4 = shape_angle.y;
    } else {
      m34D4 = m34E8;
    }
    setAtParam(AT_TYPE_SKULL_HAMMER, 4, dCcG_At_Spl_UNK0, dCcG_SE_UNK5,
               dCcG_AtHitMark_Nrm_e, 18, 50.0f);
    voiceStart(7);
    mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_HAMSWINGBPREA));
    m35EC = daPy_HIO_ham_c0::m.field_0x24;
    m355C = 0;
    return true;
}

/* 80150F08-80150F98       .text procHammerFrontSwingReady__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwingReady() {
    m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.0099999998f) {
      return procHammerFrontSwing_init();
    } else {
      if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        m34D4 = shape_angle.y;
      } else {
        cLib_addCalcAngleS(&shape_angle.y, m34D4, daPy_HIO_turn_c0::m.field_0x4,
                           daPy_HIO_turn_c0::m.field_0x0,
                           daPy_HIO_turn_c0::m.field_0x2);
      }
      current.angle.y = shape_angle.y;
      return true;
    }
}

/* 80150F98-801510DC       .text procHammerFrontSwing_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwing_init() {
    commonProcInit(daPyProc_HAMMER_FRONT_SWING_e);
    setSingleMoveAnime(ANM_HAMSWINGBHIT, 4.0f * daPy_HIO_ham_c0::m.field_0x2C,
                       daPy_HIO_ham_c0::m.field_0x30,
                       daPy_HIO_ham_c0::m.field_0x4, 0.0f);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    voiceStart(1);
    if (mpAttention->Lockon() || (mStickDistance <= 0.05f)) {
      m34D4 = shape_angle.y;
    } else {
      m34D4 = m34E8;
    }
    m34D4 = shape_angle.y;
    setBlurPosResource(LKANM__HAMMERFRONT_POS);
    mCutType = 18;
    offResetFlg0(daPyRFlg0_UNK8000000);
    onResetFlg0(daPy_RFLG0(daPyRFlg0_UNK1 | daPyRFlg0_UNK2));
    m34D0 = 0;
    mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_HAMSWINGBHITA));
    m35EC = daPy_HIO_ham_c0::m.field_0x30;
    return true;
}

/* 801510DC-801513D4       .text procHammerFrontSwing__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwing() {
    /* Nonmatching */
}

/* 801513D4-80151450       .text procHammerFrontSwingEnd_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwingEnd_init() {
    commonProcInit(daPyProc_HAMMER_FRONT_SWING_END_e);
    setSingleMoveAnime(ANM_HAMSWINGBEND, daPy_HIO_ham_c0::m.field_0x34,
                       daPy_HIO_ham_c0::m.field_0x38,
                       daPy_HIO_ham_c0::m.field_0x6,
                       daPy_HIO_ham_c0::m.field_0x40);
    current.angle.y = shape_angle.y;
    mVelocity = 0.0f;
    mCutType = 18;
    offResetFlg0(daPyRFlg0_UNK8000000);
    return true;
}

/* 80151450-801514B0       .text procHammerFrontSwingEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procHammerFrontSwingEnd() {
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.0099999998f) {
        return checkNextMode(0);
      } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >
            daPy_HIO_ham_c0::m.field_0x3C) {
          return checkNextMode(1);
        } else {
          return true;
        }
      }
}
