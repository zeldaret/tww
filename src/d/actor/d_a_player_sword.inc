/**
 * d_a_player_sword.inc
 *
 * Code relating using a sword item.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is known because of an assert contained within
 * a function from this file.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_HIO.h"
#include "JSystem/J3DGraphLoader/J3DAnmLoader.h"

/* 80154B80-80154FBC       .text setSwordModel__9daPy_lk_cFi */
void daPy_lk_c::setSwordModel(BOOL r28) {
    struct sword_model_tbl_s {
        /* 0x00 */ u16 bladeModel;
        /* 0x02 */ u16 glowModel;
        /* 0x04 */ u16 glowBtk;
        /* 0x06 */ u16 glowBrk;
        /* 0x08 */ u16 tipStabModel;
        /* 0x0A */ u16 tipStabBpk;
        /* 0x0C */ u16 tipStabBtk;
        /* 0x0E */ u16 tipStabBrk;
    };
    static const sword_model_tbl_s sword_model_tbl[] = {
        {
            LINK_BDL_SWA,
            LINK_BDL_YHSLS00,
            LKANM_BTK_YHSLS00,
            LKANM_BRK_YHSLS00,
            LINK_BDL_CUTFH,
            LKANM_BPK_CUTFH,
            LKANM_BTK_CUTFH,
            LKANM_BRK_CUTFH
        },
        {
            LINK_BDL_SWMS,
            LINK_BDL_YMSLI00,
            LKANM_BTK_YMSLI00,
            LKANM_BRK_YMSLI00,
            LINK_BDL_CUTFM,
            LKANM_BPK_CUTFM,
            LKANM_BTK_CUTFM,
            LKANM_BRK_CUTFM
        },
    };
    
    u8* buffer;
    
    J3DAnmTransform* bck = checkNormalSwordEquip() ? getItemAnimeResource(LKANM_BCK_CUTAA) : getItemAnimeResource(LKANM_BCK_CUTAMS);
    
    mEquipItem = daPyItem_SWORD_e;
    JKRHeap* oldHeap = setItemHeap();
    
    const sword_model_tbl_s& model_tbl = checkNormalSwordEquip() ? sword_model_tbl[0] : sword_model_tbl[1];
    J3DModelData* modelData = initModel(&mpEquipItemModel, model_tbl.bladeModel, 0x37221222);
    BOOL ret = mSwordAnim.init(modelData, bck, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(86, FALSE); }
    
    if (!checkNormalSwordEquip()) {
        buffer = new(0x20) u8[0x400];
        JKRReadIdxResource(buffer, 0x400, LKANM_BTK_TSWMS, dComIfGp_getAnmArchive());
        mpEquipItemBtk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(buffer));
        mpEquipItemBtk->setFrame(0.0f);
        mpEquipItemBtk->searchUpdateMaterialID(modelData);
        modelData->entryTexMtxAnimator(mpEquipItemBtk);
    }
    
    mSwBlur.mpPosBuffer = new(0x20) Vec[2 * 0x300];
    modelData = initModel(&mpSwordModel1, model_tbl.glowModel, 0x13000222);
    
    buffer = new(0x20) u8[0x400];
    JKRReadIdxResource(buffer, 0x400, model_tbl.glowBtk, dComIfGp_getAnmArchive());
    mpSwordBtk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(buffer));
    mpSwordBtk->setFrame(0.0f);
    mpSwordBtk->searchUpdateMaterialID(modelData);
    modelData->entryTexMtxAnimator(mpSwordBtk);
    
    buffer = new(0x20) u8[0x400];
    JKRReadIdxResource(buffer, 0x400, model_tbl.glowBrk, dComIfGp_getAnmArchive());
    mpEquipItemBrk = static_cast<J3DAnmTevRegKey*>(J3DAnmLoaderDataBase::load(buffer));
    mpEquipItemBrk->setFrame(0.0f);
    mpEquipItemBrk->searchUpdateMaterialID(modelData);
    modelData->entryTevRegAnimator(mpEquipItemBrk);
    
    modelData = initModel(&mpSwordTipStabModel, model_tbl.tipStabModel, 0x13000223);
    
    buffer = new(0x20) u8[0x400];
    JKRReadIdxResource(buffer, 0x400, model_tbl.tipStabBtk, dComIfGp_getAnmArchive());
    mpCutfBtk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(buffer));
    mpCutfBtk->setFrame(0.0f);
    mpCutfBtk->searchUpdateMaterialID(modelData);
    modelData->entryTexMtxAnimator(mpCutfBtk);
    
    buffer = new(0x20) u8[0x400];
    JKRReadIdxResource(buffer, 0x400, model_tbl.tipStabBrk, dComIfGp_getAnmArchive());
    mpCutfBrk = static_cast<J3DAnmTevRegKey*>(J3DAnmLoaderDataBase::load(buffer));
    mpCutfBrk->setFrame(0.0f);
    mpCutfBrk->searchUpdateMaterialID(modelData);
    modelData->entryTevRegAnimator(mpCutfBrk);
    
    buffer = new(0x20) u8[0x400];
    JKRReadIdxResource(buffer, 0x400, model_tbl.tipStabBpk, dComIfGp_getAnmArchive());
    mpCutfBpk = static_cast<J3DAnmColor*>(J3DAnmLoaderDataBase::load(buffer));
    mpCutfBpk->setFrame(0.0f);
    mpCutfBpk->searchUpdateMaterialID(modelData);
    modelData->entryMatColorAnimator(mpCutfBpk);
    
    mDoExt_setCurrentHeap(oldHeap);
    mDoAud_bgmSetSwordUsing(1);
    m355C = 0;
    
    if (r28) {
        onNoResetFlg1(daPyFlg1_UNK200000);
        mpSwordBtk->setFrame(mpSwordBtk->getFrameMax() - 0.001f);
    }
}

/* 80154FBC-80155490       .text setLightSaver__9daPy_lk_cFv */
void daPy_lk_c::setLightSaver() {
    /* Nonmatching */
    static JGeometry::TVec3<f32> d_scale(1.4f, 1.4f, 1.4f);
    static JGeometry::TVec3<f32> p_scale(1.6f, 1.4f, 1.4f);
}

/* 80155490-801554C8       .text checkDemoShieldNoDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::checkDemoShieldNoDraw() {
    /* Nonmatching */
    return dComIfGs_isEventBit(0x3f40) != 0;
}

/* 801554C8-80155544       .text checkDemoSwordNoDraw__9daPy_lk_cFi */
BOOL daPy_lk_c::checkDemoSwordNoDraw(int param_0) {
    /* Nonmatching - extra clrlwi instruction */
    if (((mEquipItem == daPyItem_SWORD_e) || (param_0 != 0)) &&
    ((dComIfGs_isEventBit(0x3f40) ||
      ((mCurProc == daPyProc_DEMO_TOOL_e && (m34D6 == 1)))))) {
      return true;
    } else {
      return false;
    }
}

/* 80155544-80155574       .text checkChanceMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkChanceMode() {
    if ((dComIfGp_getDoStatus() == 26) || (checkModeFlg(ModeFlg_PARRY))) {
        return true;
      }
      return false;
}

/* 80155574-8015559C       .text checkCutRollChange__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkCutRollChange() const {
    if ((mCurProc == daPyProc_CUT_TURN_MOVE_e) && !(m34D0 < 0)) {
        return true;
      }
      return false;
}

/* 8015559C-801555FC       .text getSwordBlurColor__9daPy_lk_cFv */
int daPy_lk_c::getSwordBlurColor() {
    if (mEquipItem == daPyItem_SWORD_e) {
        if (checkChanceMode()) {
          return 2;
        }
        if (checkNoResetFlg1(daPyFlg1_UNK8000)) {
          return 1;
        }
      }
      return 0;
}

/* 801555FC-80155694       .text setNormalCutAtParam__9daPy_lk_cFUc */
void daPy_lk_c::setNormalCutAtParam(u8 cutType) {
    int atp;
    f32 radius;
    if (checkNormalSwordEquip()) {
        atp = 1;
        radius = daPy_HIO_cut_c0::m.field_0x3C;
        m35FC = daPy_HIO_cut_c0::m.field_0x40;
    } else {
        atp = 2;
        radius = daPy_HIO_cut_c0::m.field_0x44;
        m35FC = daPy_HIO_cut_c0::m.field_0x48;
    }
    setAtParam(AT_TYPE_SWORD, atp, dCcG_At_Spl_UNK0, dCcG_SE_UNK1, dCcG_AtHitMark_Nrm_e, cutType, radius);
}

/* 80155694-8015572C       .text setFinishCutAtParam__9daPy_lk_cFUc */
void daPy_lk_c::setFinishCutAtParam(u8 cutType) {
    int atp;
    f32 radius;
    if (checkNormalSwordEquip()) {
        atp = 2;
        radius = daPy_HIO_cut_c0::m.field_0x3C;
        m35FC = daPy_HIO_cut_c0::m.field_0x40;
    } else {
        atp = 4;
        radius = daPy_HIO_cut_c0::m.field_0x44;
        m35FC = daPy_HIO_cut_c0::m.field_0x48;
    }
    setAtParam(AT_TYPE_SWORD, atp, dCcG_At_Spl_UNK1, dCcG_SE_UNK1, dCcG_AtHitMark_Big_e, cutType, radius);
}

/* 8015572C-801557C4       .text setExtraCutAtParam__9daPy_lk_cFUc */
void daPy_lk_c::setExtraCutAtParam(u8 cutType) {
    int atp;
    f32 radius;
    if (checkNormalSwordEquip()) {
        atp = 1;
        radius = daPy_HIO_cut_c0::m.field_0x5C;
        m35FC = daPy_HIO_cut_c0::m.field_0x60;
    } else {
        atp = 2;
        radius = daPy_HIO_cut_c0::m.field_0x64;
        m35FC = daPy_HIO_cut_c0::m.field_0x68;
    }
    setAtParam(AT_TYPE_SWORD, atp, dCcG_At_Spl_UNK0, dCcG_SE_UNK1, dCcG_AtHitMark_Nrm_e, cutType, radius);
}

/* 801557C4-8015585C       .text setExtraFinishCutAtParam__9daPy_lk_cFUc */
void daPy_lk_c::setExtraFinishCutAtParam(u8 cutType) {
    int atp;
    f32 radius;
    if (checkNormalSwordEquip()) {
        atp = 2;
        radius = daPy_HIO_cut_c0::m.field_0x5C;
        m35FC = daPy_HIO_cut_c0::m.field_0x60;
    } else {
        atp = 4;
        radius = daPy_HIO_cut_c0::m.field_0x64;
        m35FC = daPy_HIO_cut_c0::m.field_0x68;
    }
    setAtParam(AT_TYPE_SWORD, atp, dCcG_At_Spl_UNK1, dCcG_SE_UNK1, dCcG_AtHitMark_Big_e, cutType, radius);
}

/* 8015585C-80155970       .text setJumpCutAtParam__9daPy_lk_cFv */
void daPy_lk_c::setJumpCutAtParam() {
    /* Nonmatching - floats */
    mCutCount = 0;
    if (mEquipItem == daPyItem_SWORD_e) {
        int atp;
        f32 radius;
        if (checkNormalSwordEquip()) {
            atp = 2;
            radius = daPy_HIO_cut_c0::m.field_0x4C;
            m35FC = daPy_HIO_cut_c0::m.field_0x50;
        } else {
            atp = 4;
            radius = daPy_HIO_cut_c0::m.field_0x54;
            m35FC = daPy_HIO_cut_c0::m.field_0x58;
        }
        setAtParam(AT_TYPE_SWORD, atp, dCcG_At_Spl_UNK1, dCcG_SE_UNK1, dCcG_AtHitMark_Big_e, 0xA, radius);
    } else if (mEquipItem == dItem_SKULL_HAMMER_e) {
        setAtParam(AT_TYPE_SKULL_HAMMER, 4, dCcG_At_Spl_UNK1, dCcG_SE_UNK5, dCcG_AtHitMark_Nrm_e, 0x13, 50.0f);
    } else if (mActorKeepEquip.getActor()) {
        setEnemyWeaponAtParam(TRUE);
    } else {
        setAtParam(AT_TYPE_MACHETE, 2, dCcG_At_Spl_UNK1, dCcG_SE_UNK1, dCcG_AtHitMark_Big_e, 0xE, 30.0f);
    }
}

/* 80155970-801559F0       .text getCutDirection__9daPy_lk_cFv */
int daPy_lk_c::getCutDirection() {
    int iVar1;
    s16 sVar2;

    if (mStickDistance <= 0.05f) {
        iVar1 = 4;
    } else {
        if (mpAttnActorLockOn != NULL) {
            sVar2 = fopAcM_searchActorAngleY(this, mpAttnActorLockOn);
            sVar2 =  m34E8 - sVar2;
        } else {
            sVar2 = m34E8 - m34DE;
        }
        iVar1 = getDirectionFromAngle(sVar2);
    }
    return iVar1 + 1;
}

/* 801559F0-80155C3C       .text changeCutProc__9daPy_lk_cFv */
int daPy_lk_c::changeCutProc() {
    u32 bVar1;
    short sVar2;
    int iVar4;
  
    if (m34C5 == 5) {
      iVar4 = changeSpecialBattle();
      if (iVar4 != 0) {
        m34C4 = 0;
        return true;
      }
    }
    m34C4++;
    iVar4 = getCutDirection() - 1;
    if (mpAttention->Lockon() || (mStickDistance <= 0.05f)) {
      sVar2 = shape_angle.y;
    } else {
      sVar2 = m34E8;
    }
    bVar1 = m34C4;
    if (bVar1 > 4) {
      mCutCount = bVar1 - 2;
    } else {
      mCutCount = bVar1;
    }
    bVar1 = m34C4;
    if (bVar1 == 4) {
      if ((iVar4 == 3) || (iVar4 == 0)) {
        procCutEA_init();
      } else {
        procCutEB_init();
      }
    } else if (bVar1 < 4) {
      if (iVar4 == 0) {
        procCutF_init(sVar2);
      } else if (iVar4 == 3) {
        procCutR_init(sVar2);
      } else if (iVar4 == 4) {
        if (mpAttention->Lockon()) {
          procCutA_init(sVar2);
        } else {
          procCutL_init(sVar2);
        }
      } else {
        procCutL_init(sVar2);
      }
    } else if (bVar1 == 6) {
      if (iVar4 == 0) {
        procCutTurn_init(1);
      } else if (iVar4 == 4) {
        procCutExB_init();
      } else if (iVar4 == 3) {
        procCutExMJ_init(1);
      } else {
        procCutExMJ_init(0);
      }
    } else if (bVar1 < 6) {
      if (iVar4 == 0) {
        procCutExMJ_init(1);
      } else if (iVar4 == 3) {
        procCutKesa_init();
      } else {
        procCutExA_init();
      }
    }
    m3578 = 0;
    return true;
}

/* 80155C3C-80156034       .text changeCutReverseProc__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
int daPy_lk_c::changeCutReverseProc(daPy_ANM) {
    /* Nonmatching */
}

/* 80156034-80156198       .text procCutA_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutA_init(s16 param_0) {
    commonProcInit(daPyProc_CUT_A_e);
    setSingleMoveAnime(
        ANM_CUTA, daPy_HIO_cutA_c0::m.field_0x4, daPy_HIO_cutA_c0::m.field_0x8,
        daPy_HIO_cutA_c0::m.field_0x2, daPy_HIO_cutA_c0::m.field_0x24);
    if (checkNormalSwordEquip()) {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTAA));
    } else {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTAMS));
    }
    m35EC = daPy_HIO_cutA_c0::m.field_0x8;
    current.angle.y = shape_angle.y;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    voiceStart(0);
    m34D4 = param_0;
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    m3522 = daPy_HIO_cutA_c0::m.field_0x0;
    m351E = m34DC;
    onNoResetFlg0(daPyFlg0_UNK4);
    setBlurPosResource(LKANM__CUTA_POS);
    setNormalCutAtParam(1);
    return true;
}

/* 80156198-80156424       .text procCutA__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutA() {
    J3DFrameCtrl &frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if ((swordButton()) && (m34C5 == 0)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    m3522 = daPy_HIO_cutA_c0::m.field_0x0;
    if (frameCtrl.getRate() < 0.0099999998f) {
      mVelocity = 0.0f;
      m34B8 = 3;
      checkNextMode(0);
      return true;
    } else {
      if (frameCtrl.getFrame() > daPy_HIO_cutA_c0::m.field_0xC) {
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
      if (changeCutReverseProc(ANM_CUTRER)) {
        return true;
      } else {
        setSpecialBattle(1);
        if ((doTrigger()) && (dComIfGp_getDoStatus() == 26)) {
          changeSpecialBattle();
        } else {
          if ((swordTrigger()) && (m34C5 != 5)) {
            m34C5 = 1;
          }
          m34C2 = 1;
          if (mpAttnActorLockOn != NULL) {
            setShapeAngleToAtnActor();
            m34D4 = shape_angle.y;
          } else {
            cLib_addCalcAngleS(
                &shape_angle.y, m34D4, daPy_HIO_turn_c0::m.field_0x4,
                daPy_HIO_turn_c0::m.field_0x0, daPy_HIO_turn_c0::m.field_0x2);
          }
          current.angle.y = shape_angle.y;
          if (frameCtrl.checkPass(daPy_HIO_cutA_c0::m.field_0x28)) {
            mVelocity = std::fabsf(speedF) * daPy_HIO_cutA_c0::m.field_0x10 +
                        daPy_HIO_cutA_c0::m.field_0x14;
          }
          if ((frameCtrl.getFrame() >= daPy_HIO_cutA_c0::m.field_0x2C) &&
              (frameCtrl.getFrame() < daPy_HIO_cutA_c0::m.field_0x30)) {
            if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
              onResetFlg0(daPyRFlg0_UNK1);
              seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
            }
            onResetFlg0(daPyRFlg0_UNK2);
          }
          cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_cutA_c0::m.field_0x20,
                       daPy_HIO_cutA_c0::m.field_0x18,
                       daPy_HIO_cutA_c0::m.field_0x1C);
          return true;
        }
      }
    }
}

/* 80156424-80156584       .text procCutF_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutF_init(s16 param_0) {
    commonProcInit(daPyProc_CUT_F_e);
    setSingleMoveAnime(
        ANM_CUTF, daPy_HIO_cutF_c0::m.field_0x4, daPy_HIO_cutF_c0::m.field_0x8,
        daPy_HIO_cutF_c0::m.field_0x2, daPy_HIO_cutF_c0::m.field_0x24);
    if (checkNormalSwordEquip()) {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTFA));
    } else {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTFMS));
    }
    m35EC = daPy_HIO_cutF_c0::m.field_0x8;
    mpCutfBpk->setFrame(daPy_HIO_cutF_c0::m.field_0x8);
    mpCutfBtk->setFrame(daPy_HIO_cutF_c0::m.field_0x8);
    m3700 = cXyz::Zero;
    m34C2 = 1;
    voiceStart(0);
    m34D4 = param_0;
    m351E = m34DC;
    m3522 = daPy_HIO_cutF_c0::m.field_0x0;
    onNoResetFlg0(daPyFlg0_UNK4);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    setNormalCutAtParam(2);
    return true;
}

/* 80156584-80156828       .text procCutF__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutF() {
    J3DFrameCtrl &frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if ((swordButton()) && (m34C5 == 0)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    mpCutfBpk->setFrame(frameCtrl.getFrame());
    mpCutfBtk->setFrame(frameCtrl.getFrame());
    m3522 = daPy_HIO_cutF_c0::m.field_0x0;
    if (frameCtrl.getRate() < 0.0099999998f) {
      mVelocity = 0.0f;
      m34B8 = 3;
      checkNextMode(0);
      return true;
    } else {
      if (frameCtrl.getFrame() > daPy_HIO_cutF_c0::m.field_0xC) {
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
      if (changeCutReverseProc(ANM_CUTRER)) {
        return true;
      } else {
        setSpecialBattle(1);
        if ((doTrigger()) && (dComIfGp_getDoStatus() == 26)) {
          changeSpecialBattle();
        } else {
          if ((swordTrigger()) && (m34C5 != 5)) {
            m34C5 = 2;
          }
          m34C2 = 1;
          if (mpAttnActorLockOn != NULL) {
            setShapeAngleToAtnActor();
            m34D4 = shape_angle.y;
          } else {
            cLib_addCalcAngleS(
                &shape_angle.y, m34D4, daPy_HIO_turn_c0::m.field_0x4,
                daPy_HIO_turn_c0::m.field_0x0, daPy_HIO_turn_c0::m.field_0x2);
          }
          current.angle.y = shape_angle.y;
          if (frameCtrl.checkPass(daPy_HIO_cutF_c0::m.field_0x28)) {
            mVelocity = std::fabsf(speedF) * daPy_HIO_cutF_c0::m.field_0x10 +
                        daPy_HIO_cutF_c0::m.field_0x14;
          }
          if ((frameCtrl.getFrame() >= daPy_HIO_cutF_c0::m.field_0x2C) &&
              (frameCtrl.getFrame() < daPy_HIO_cutF_c0::m.field_0x30)) {
            if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
              onResetFlg0(daPyRFlg0_UNK1);
              seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
            }
            onResetFlg0(daPyRFlg0_UNK2);
          }
          cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_cutF_c0::m.field_0x20,
                       daPy_HIO_cutF_c0::m.field_0x18,
                       daPy_HIO_cutF_c0::m.field_0x1C);
          return true;
        }
      }
    }
}

/* 80156828-80156984       .text procCutR_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutR_init(s16 param_0) {
    commonProcInit(daPyProc_CUT_R_e);
    setSingleMoveAnime(
        ANM_CUTR, daPy_HIO_cutR_c0::m.field_0x4, daPy_HIO_cutR_c0::m.field_0x8,
        daPy_HIO_cutR_c0::m.field_0x2, daPy_HIO_cutR_c0::m.field_0x24);
    if (checkNormalSwordEquip()) {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTRA));
    } else {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTRMS));
    }
    m35EC = daPy_HIO_cutR_c0::m.field_0x8;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    voiceStart(0);
    m34D4 = param_0;
    m351E = m34DC;
    m3522 = daPy_HIO_cutR_c0::m.field_0x0;
    onNoResetFlg0(daPyFlg0_UNK4);
    setBlurPosResource(LKANM__CUTR_POS);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    setNormalCutAtParam(3);
    return true;
}

/* 80156984-80156C10       .text procCutR__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutR() {
    J3DFrameCtrl &frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if ((swordButton()) && (m34C5 == 0)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    m3522 = daPy_HIO_cutR_c0::m.field_0x0;
    if (frameCtrl.getRate() < 0.0099999998f) {
      mVelocity = 0.0f;
      m34B8 = 3;
      checkNextMode(0);
      return true;
    } else {
      if (frameCtrl.getFrame() > daPy_HIO_cutR_c0::m.field_0xC) {
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
      if (changeCutReverseProc(ANM_CUTRER)) {
        return true;
      } else {
        setSpecialBattle(1);
        if ((doTrigger()) && (dComIfGp_getDoStatus() == 26)) {
          changeSpecialBattle();
        } else {
          if ((swordTrigger()) && (m34C5 != 5)) {
            m34C5 = 3;
          }
          m34C2 = 1;
          if (mpAttnActorLockOn != NULL) {
            setShapeAngleToAtnActor();
            m34D4 = shape_angle.y;
          } else {
            cLib_addCalcAngleS(
                &shape_angle.y, m34D4, daPy_HIO_turn_c0::m.field_0x4,
                daPy_HIO_turn_c0::m.field_0x0, daPy_HIO_turn_c0::m.field_0x2);
          }
          current.angle.y = shape_angle.y;
          if (frameCtrl.checkPass(daPy_HIO_cutR_c0::m.field_0x28)) {
            mVelocity = std::fabsf(speedF) * daPy_HIO_cutR_c0::m.field_0x10 +
                        daPy_HIO_cutR_c0::m.field_0x14;
          }
          if ((frameCtrl.getFrame() >= daPy_HIO_cutR_c0::m.field_0x2C) &&
              (frameCtrl.getFrame() < daPy_HIO_cutR_c0::m.field_0x30)) {
            if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
              onResetFlg0(daPyRFlg0_UNK1);
              seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
            }
            onResetFlg0(daPyRFlg0_UNK2);
          }
          cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_cutR_c0::m.field_0x20,
                       daPy_HIO_cutR_c0::m.field_0x18,
                       daPy_HIO_cutR_c0::m.field_0x1C);
          return true;
        }
      }
    }
}

/* 80156C10-80156D6C       .text procCutL_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutL_init(s16 param_0) {
    commonProcInit(daPyProc_CUT_L_e);
    setSingleMoveAnime(
        ANM_CUTL, daPy_HIO_cutL_c0::m.field_0x4, daPy_HIO_cutL_c0::m.field_0x8,
        daPy_HIO_cutL_c0::m.field_0x2, daPy_HIO_cutL_c0::m.field_0x24);
    if (checkNormalSwordEquip()) {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTLA));
    } else {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTLMS));
    }
    m35EC = daPy_HIO_cutL_c0::m.field_0x8;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    voiceStart(0);
    m34D4 = param_0;
    m351E = m34DC;
    m3522 = daPy_HIO_cutL_c0::m.field_0x0;
    onNoResetFlg0(daPyFlg0_UNK4);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    setBlurPosResource(LKANM__CUTL_POS);
    setNormalCutAtParam(4);
    return true;
}

/* 80156D6C-80156FF8       .text procCutL__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutL() {
    J3DFrameCtrl &frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if ((swordButton()) && (m34C5 == 0)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    m3522 = daPy_HIO_cutL_c0::m.field_0x0;
    if (frameCtrl.getRate() < 0.0099999998f) {
      mVelocity = 0.0f;
      m34B8 = 2;
      checkNextMode(0);
      return true;
    } else {
      if (frameCtrl.getFrame() > daPy_HIO_cutL_c0::m.field_0xC) {
        f32 dVar4 = mVelocity;
        u8 uVar1 = m34B8;
        mVelocity = 0.0f;
        m34B8 = 2;
        if (checkNextMode(1)) {
          return true;
        }
        mVelocity = dVar4;
        m34B8 = uVar1;
      }
      if (changeCutReverseProc(ANM_CUTREL)) {
        return true;
      } else {
        setSpecialBattle(1);
        if ((doTrigger()) && (dComIfGp_getDoStatus() == 26)) {
          changeSpecialBattle();
        } else {
          if ((swordTrigger()) && (m34C5 != 5)) {
            m34C5 = 4;
          }
          m34C2 = 1;
          if (mpAttnActorLockOn != NULL) {
            setShapeAngleToAtnActor();
            m34D4 = shape_angle.y;
          } else {
            cLib_addCalcAngleS(
                &shape_angle.y, m34D4, daPy_HIO_turn_c0::m.field_0x4,
                daPy_HIO_turn_c0::m.field_0x0, daPy_HIO_turn_c0::m.field_0x2);
          }
          current.angle.y = shape_angle.y;
          if (frameCtrl.checkPass(daPy_HIO_cutL_c0::m.field_0x28)) {
            mVelocity = std::fabsf(speedF) * daPy_HIO_cutL_c0::m.field_0x10 +
                        daPy_HIO_cutL_c0::m.field_0x14;
          }
          if ((frameCtrl.getFrame() >= daPy_HIO_cutL_c0::m.field_0x2C) &&
              (frameCtrl.getFrame() < daPy_HIO_cutL_c0::m.field_0x30)) {
            if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
              onResetFlg0(daPyRFlg0_UNK1);
              seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
            }
            onResetFlg0(daPyRFlg0_UNK2);
          }
          cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_cutL_c0::m.field_0x20,
                       daPy_HIO_cutL_c0::m.field_0x18,
                       daPy_HIO_cutL_c0::m.field_0x1C);
          return true;
        }
      }
    }
}

/* 80156FF8-80157154       .text procCutEA_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutEA_init() {
    commonProcInit(daPyProc_CUT_EA_e);
    setSingleMoveAnime(
        ANM_CUTEA, daPy_HIO_cutEA_c0::m.field_0x4, daPy_HIO_cutEA_c0::m.field_0x8,
        daPy_HIO_cutEA_c0::m.field_0x0, daPy_HIO_cutEA_c0::m.field_0x20);
    if (checkNormalSwordEquip()) {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTEAA));
    } else {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTEAMS));
    }
    m35EC = daPy_HIO_cutEA_c0::m.field_0x8;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    m34D0 = daPy_HIO_cutEA_c0::m.field_0x2;
    onNoResetFlg0(daPyFlg0_UNK4);
    voiceStart(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    setBlurPosResource(LKANM__CUTEA_POS);
    setFinishCutAtParam(6);
    m34C4 = 0;
    m3522 = 0;
    return true;
}

/* 80157154-80157348       .text procCutEA__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutEA() {
    J3DFrameCtrl &frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if ((swordButton()) && (m34C5 == 0)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    if (frameCtrl.getRate() < 0.0099999998f) {
      if ((int)m34D0 > 0) {
        m34D0--;
      } else {
        mVelocity = 0.0f;
        m34B8 = 3;
        checkNextMode(0);
        return true;
      }
    }
    if (changeCutReverseProc(ANM_CUTREL)) {
      return true;
    } else if (mpAttnActorLockOn != NULL) {
      setShapeAngleToAtnActor();
      current.angle.y = shape_angle.y;
    }
    setSpecialBattle(1);
    if ((doTrigger()) && (dComIfGp_getDoStatus() == 26)) {
      changeSpecialBattle();
    } else {
      if (frameCtrl.checkPass(daPy_HIO_cutEA_c0::m.field_0x24)) {
        mVelocity = std::fabsf(speedF) * daPy_HIO_cutEA_c0::m.field_0xC +
                    daPy_HIO_cutEA_c0::m.field_0x10;
      }
      if ((frameCtrl.getFrame() >= daPy_HIO_cutEA_c0::m.field_0x28) &&
          (frameCtrl.getFrame() < daPy_HIO_cutEA_c0::m.field_0x2C)) {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
          onResetFlg0(daPyRFlg0_UNK1);
          seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
      }
      m34C2 = 1;
      cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_cutEA_c0::m.field_0x1C,
                   daPy_HIO_cutEA_c0::m.field_0x14,
                   daPy_HIO_cutEA_c0::m.field_0x18);
      return true;
    }
}

/* 80157348-801574A4       .text procCutEB_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutEB_init() {
    commonProcInit(daPyProc_CUT_EB_e);
    setSingleMoveAnime(
        ANM_CUTEB, daPy_HIO_cutEB_c0::m.field_0x4, daPy_HIO_cutEB_c0::m.field_0x8,
        daPy_HIO_cutEB_c0::m.field_0x0, daPy_HIO_cutEB_c0::m.field_0x20);
    if (checkNormalSwordEquip()) {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTEBA));
    } else {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTEBMS));
    }
    m35EC = daPy_HIO_cutEB_c0::m.field_0x8;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    m34D0 = daPy_HIO_cutEB_c0::m.field_0x2;
    onNoResetFlg0(daPyFlg0_UNK4);
    voiceStart(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    setBlurPosResource(LKANM__CUTEB_POS);
    setFinishCutAtParam(7);
    m34C4 = 0;
    m3522 = 0;
    return true;
}

/* 801574A4-8015768C       .text procCutEB__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutEB() {
    J3DFrameCtrl &frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if ((swordButton()) && (m34C5 == 0)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    if (frameCtrl.getRate() < 0.0099999998f) {
      if ((int)m34D0 > 0) {
        m34D0--;
      } else {
        mVelocity = 0.0f;
        m34B8 = 2;
        checkNextMode(0);
        return true;
      }
    }
    if (changeCutReverseProc(ANM_CUTRER)) {
      return true;
    }
    setShapeAngleToAtnActor();
    current.angle.y = shape_angle.y;
    setSpecialBattle(1);
    if ((doTrigger()) && (dComIfGp_getDoStatus() == 26)) {
      changeSpecialBattle();
    } else {
      if (frameCtrl.checkPass(daPy_HIO_cutEB_c0::m.field_0x24)) {
        mVelocity = std::fabsf(speedF) * daPy_HIO_cutEB_c0::m.field_0xC +
                    daPy_HIO_cutEB_c0::m.field_0x10;
      }
      if ((frameCtrl.getFrame() >= daPy_HIO_cutEB_c0::m.field_0x28) &&
          (frameCtrl.getFrame() < daPy_HIO_cutEB_c0::m.field_0x2C)) {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
          onResetFlg0(daPyRFlg0_UNK1);
          seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
      }
      m34C2 = 1;
      cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_cutEB_c0::m.field_0x1C,
                   daPy_HIO_cutEB_c0::m.field_0x14,
                   daPy_HIO_cutEB_c0::m.field_0x18);
      return true;
    }
}

/* 8015768C-801577EC       .text procCutExA_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExA_init() {
    commonProcInit(daPyProc_CUT_EX_A_e);
    setSingleMoveAnime(ANM_EXCA1, daPy_HIO_cutExA_c0::m.field_0x8,
                       daPy_HIO_cutExA_c0::m.field_0xC,
                       daPy_HIO_cutExA_c0::m.field_0x0,
                       daPy_HIO_cutExA_c0::m.field_0x10);
    if (checkNormalSwordEquip()) {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_EXCA1A));
    } else {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_EXCA1MS));
    }
    m35EC = daPy_HIO_cutExA_c0::m.field_0xC;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    m34D0 = daPy_HIO_cutExA_c0::m.field_0x2;
    onNoResetFlg0(daPyFlg0_UNK4);
    voiceStart(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    setBlurPosResource(LKANM__CUTEXA_POS);
    setExtraCutAtParam(26);
    m3522 = daPy_HIO_cutExA_c0::m.field_0x4;
    return true;
}

/* 801577EC-80157A18       .text procCutExA__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExA() {
    J3DFrameCtrl &frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if ((swordButton()) && (m34C5 == 0)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    m3522 = daPy_HIO_cutExA_c0::m.field_0x4;
    if (frameCtrl.getRate() < 0.0099999998f) {
      mVelocity = 0.0f;
      checkNextMode(0);
      return true;
    } else {
      if (frameCtrl.getFrame() > daPy_HIO_cutExA_c0::m.field_0x1C) {
        f32 dVar4 = mVelocity;
        mVelocity = 0.0f;
        if (checkNextMode(1)) {
          return true;
        }
        mVelocity = dVar4;
      } else if (frameCtrl.checkPass(11.0f)) {
        onModeFlg(ModeFlg_00000080);
      }
      if (changeCutReverseProc(ANM_CUTREL)) {
        return true;
      } else {
        setSpecialBattle(1);
        if ((doTrigger()) && (dComIfGp_getDoStatus() == 26)) {
          changeSpecialBattle();
        } else {
          if ((swordTrigger()) && (m34C5 != 5)) {
            m34C5 = 26;
          }
          if (mpAttnActorLockOn != NULL) {
            setShapeAngleToAtnActor();
            current.angle.y = shape_angle.y;
          }
          if ((frameCtrl.getFrame() >= daPy_HIO_cutExA_c0::m.field_0x14) &&
              (frameCtrl.getFrame() < daPy_HIO_cutExA_c0::m.field_0x18)) {
            if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
              onResetFlg0(daPyRFlg0_UNK1);
              seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
            }
            onResetFlg0(daPyRFlg0_UNK2);
          }
          m34C2 = 1;
          cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_cutEA_c0::m.field_0x1C,
                       daPy_HIO_cutEA_c0::m.field_0x14,
                       daPy_HIO_cutEA_c0::m.field_0x18);
          return true;
        }
      }
    }
}

/* 80157A18-80157B74       .text procCutExB_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExB_init() {
    commonProcInit(daPyProc_CUT_EX_B_e);
    setSingleMoveAnime(ANM_EXCB1, daPy_HIO_cutExB_c0::m.field_0x4,
                       daPy_HIO_cutExB_c0::m.field_0x8,
                       daPy_HIO_cutExB_c0::m.field_0x0,
                       daPy_HIO_cutExB_c0::m.field_0xC);
    if (checkNormalSwordEquip()) {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_EXCB1A));
    } else {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_EXCB1MS));
    }
    m35EC = daPy_HIO_cutExB_c0::m.field_0x8;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    m34D0 = daPy_HIO_cutExB_c0::m.field_0x2;
    onNoResetFlg0(daPyFlg0_UNK4);
    voiceStart(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    setBlurPosResource(LKANM__CUTEXB_POS);
    setExtraFinishCutAtParam(27);
    m34C4 = 0;
    m3522 = 0;
    return true;
}

/* 80157B74-80157D3C       .text procCutExB__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExB() {
    /* Nonmatching - floats */
    J3DFrameCtrl &frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if ((swordButton()) && (m34C5 == 0)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    if (frameCtrl.getRate() < 0.0099999998f) {
      if ((int)m34D0 > 0) {
        m34D0--;
      } else {
        mVelocity = 0.0f;
        checkNextMode(0);
        return true;
      }
    } else if (frameCtrl.checkPass(14.0f)) {
      onModeFlg(ModeFlg_00000080);
    }
    if (changeCutReverseProc(ANM_CUTREL)) {
      return true;
    } else if (mpAttnActorLockOn != NULL) {
      setShapeAngleToAtnActor();
      current.angle.y = shape_angle.y;
    }
    setSpecialBattle(1);
    if ((doTrigger()) && (dComIfGp_getDoStatus() == 26)) {
      changeSpecialBattle();
    } else {
      if ((frameCtrl.getFrame() >= daPy_HIO_cutExB_c0::m.field_0x10) &&
          (frameCtrl.getFrame() < daPy_HIO_cutExB_c0::m.field_0x14)) {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
          onResetFlg0(daPyRFlg0_UNK1);
          seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
      }
      m34C2 = 1;
      cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_cutEA_c0::m.field_0x1C,
                   daPy_HIO_cutEA_c0::m.field_0x14,
                   daPy_HIO_cutEA_c0::m.field_0x18);
      return true;
    }
}

/* 80157D3C-80158220       .text procCutTurn_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procCutTurn_init(int) {
    /* Nonmatching */
}

/* 80158220-80158460       .text procCutTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurn() {
    /* Nonmatching */
}

/* 80158460-801585D8       .text procCutRoll_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutRoll_init() {
    /* Nonmatching */
}

/* 801585D8-801588F0       .text procCutRoll__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutRoll() {
    /* Nonmatching */
}

/* 801588F0-80158A40       .text procCutRollEnd_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutRollEnd_init() {
    /* Nonmatching - floats, regalloc */
    commonProcInit(daPyProc_CUT_ROLL_END_e);
    setSingleMoveAnime(ANM_WAITQ,daPy_HIO_move_c0::m.field_0x84,0.0f,-1,daPy_HIO_basic_c0::m.field_0xC);
    mVelocity = 0.0f;
    current.angle.y = shape_angle.y;
    m34D0 = daPy_HIO_cutRoll_c0::m.field_0x6;
    static JGeometry::TVec3<f32> emitter_trans(0.0f, 55.0f, 0.0f);
    static JGeometry::TVec3<f32> particle_scale(0.76f, 0.76f, 0.76f);
    m33A8.makeEmitter(dPa_name::ID_COMMON_STARS_SPIN, mpCLModel->getAnmMtx(15), &current.pos,NULL);
    JPABaseEmitter* emitter = m33A8.getEmitter();
    if (emitter != NULL) {
        emitter->setStatus(0x40);
        emitter->setVolumeSize(5);
        emitter->setLifeTime(daPy_HIO_cutRoll_c0::m.field_0x6);
        emitter->setEmitterTranslation(emitter_trans);
        emitter->setGlobalParticleScale(particle_scale);
    }
    return true;
}

/* 80158A40-80158A98       .text procCutRollEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutRollEnd() {
    seStartOnlyReverb(JA_SE_CM_MD_PIYO);
    if ((int)m34D0 > 0) {
      m34D0--;
    } else {
      checkNextMode(0);
    }
    return true;
}

/* 80158A98-80158B00       .text procCutTurnCharge_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnCharge_init() {
    commonProcInit(daPyProc_CUT_TURN_CHARGE_e);
    setSingleMoveAnime(ANM_CUTTURNP, daPy_HIO_cutTurnR_c0::m.field_0xC,
                       daPy_HIO_cutTurnR_c0::m.field_0x10,
                       daPy_HIO_cutTurnR_c0::m.field_0x4,
                       daPy_HIO_cutTurnR_c0::m.field_0x14);
    mVelocity = 0.0f;
    current.angle.y = shape_angle.y;
    return true;
}

/* 80158B00-80158B58       .text procCutTurnCharge__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnCharge() {
    if ((!swordButton()) || (daPy_dmEcallBack_c::m_type == 1)) {
        checkNextMode(0);
      } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.0099999998f) {
        procCutTurnMove_init();
      }
      return true;
}

/* 80158B58-80158D40       .text procCutTurnMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnMove_init() {
    /* Nonmatching */
    static Vec eff_scale = {1.5f, 1.5f, 1.5f};
    bool bVar1;
    uint uVar2;
    int iVar3;
    cXyz* pcVar4;
    
    commonProcInit(daPyProc_CUT_TURN_MOVE_e);
    setSingleMoveAnime(ANM_CUTTURNPWFB,0.0f,0.0f,-1,daPy_HIO_cutTurnR_c0::m.field_0x1C);
    if ((mEquipItem == daPyItem_BOKO_e) &&
       (mAnmRatioUpper[UPPER_MOVE0_e].getAnmTransform() != NULL)) {
      mFrameCtrlUpper[UPPER_MOVE0_e].setFrame(mFrameCtrlUpper[UPPER_MOVE0_e].getEnd() - 0.001f);
      mAnmRatioUpper[UPPER_MOVE0_e].getAnmTransform()->setFrame(mFrameCtrlUpper[UPPER_MOVE0_e].getFrame());
    }
    m3598 = 1.0f;
    m34B8 = 0;
    if (dComIfGs_isEventBit(0xb20)) {
        bVar1 = true;
    } else {
        if (dComIfGs_isTmpBit(0x402)) {
          bVar1 = true;
        } else {
          bVar1 = false;
        }
    }
    if (((bVar1) && (mEquipItem == daPyItem_SWORD_e)) && (2 < dComIfGs_getMagic())) {
      uVar2 = (2 - (uint)dComIfGp_getMiniGameType());
      if (((uVar2 >> 5 & 0xff) == 0) && (dComIfGp_getMiniGameType() != 6)) {
        pcVar4 = NULL;
        if (dComIfGs_getSelectEquip(0) == dItem_SWORD_e) {
            pcVar4->x = eff_scale.x;
            pcVar4->y = eff_scale.y;
            pcVar4->z = eff_scale.z;
        }
        m32E4.makeEmitter(0x29, mpCLModel->getAnmMtx(8),&current.pos, pcVar4);
        m32F0.makeEmitter(0x2a, mpCLModel->getAnmMtx(8),&current.pos, pcVar4);
        m34D0 = 0x2f;
        goto LAB_80158d10;
      }
    }
    m34D0 = -1;
  LAB_80158d10:
    dComIfGp_setPlayerStatus0(0, daPyStts0_SPIN_ATTACK_e);
    return true;
}

/* 80158D40-80159130       .text procCutTurnMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnMove() {
    setShapeAngleToAtnActor();
    m34E6 = shape_angle.y;
    if ((0 < (s32)m34D0) && (m34D0 = (s32)m34D0 + -1, (s32)m34D0 == 0)) {
      dComIfGp_setPlayerStatus1(0, daPyStts1_UNK20000_e);
    }
    if ((s32)m34D0 != -1) {
      mDoAud_seStart(JA_SE_LK_SWORD_CHARGE);
    }
    if (changeSlideProc()) {
      return true;
    } else {
      if (daPy_dmEcallBack_c::m_type == 1) {
        checkNextMode(0);
      } else if (swordButton()) {
        f32 dVar8 = 0.0f;
        if (mStickDistance > 0.05f) {
          s32 uVar5 = getDirectionFromAngle(m34E8 - m34E6);
          daPy_ANM dVar6 = (daPy_ANM)0xffff;
          cLib_addCalcAngleS(&current.angle.y, m34E8, 4, 12000, 0x2000);
          f32 in_f30;
          if (((u32)m34B8 == 0) || ((u32)m34B8 == 1)) {
            if ((uVar5 == 2) || (uVar5 == 3)) {
              dVar6 = ANM_CUTTURNPWLR;
              in_f30 = daPy_HIO_cutTurnR_c0::m.field_0x24;
              mVelocity *= 0.5f;
            } else if (m34B8 != uVar5) {
              mVelocity *= 0.5f;
            }
          } else if ((uVar5 == 0) || (uVar5 == 1)) {
            dVar6 = ANM_CUTTURNPWFB;
            in_f30 = daPy_HIO_cutTurnR_c0::m.field_0x1C;
            mVelocity *= 0.5f;
          } else if (m34B8 != uVar5) {
            mVelocity *= 0.5f;
          }
          if (m34B8 == uVar5) {
            dVar8 = (daPy_HIO_move_c0::m.field_0x14 * mStickDistance);
          } else {
            m34B8 = (u8)uVar5;
          }
          if (dVar6 != (daPy_ANM)0xffff) {
            setSingleMoveAnime(dVar6, 0.0f, 0.0f, -1, in_f30);
          }
        }
        setNormalSpeedF(dVar8, 0.5f, 2.0f, 0.25f);
        if (m34B8 == 0) {
          dVar8 = daPy_HIO_cutTurnR_c0::m.field_0x18;
        } else if (m34B8 == 1) {
          dVar8 = -daPy_HIO_cutTurnR_c0::m.field_0x18;
        } else if (m34B8 == 3) {
          dVar8 = -daPy_HIO_cutTurnR_c0::m.field_0x20;
        } else {
          dVar8 = daPy_HIO_cutTurnR_c0::m.field_0x20;
        }
        f32 dVar7 = (mVelocity / mMaxNormalSpeed);
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(dVar7 * dVar8);
        if (dVar8 >= 0.0f) {
          mFrameCtrlUnder[UNDER_MOVE0_e].setLoop(
              mFrameCtrlUnder[UNDER_MOVE0_e].getStart());
        } else {
          mFrameCtrlUnder[UNDER_MOVE0_e].setLoop(
              mFrameCtrlUnder[UNDER_MOVE0_e].getEnd());
        }
        initSeAnime();
        m3598 = 1.0f - ((1.0f - daPy_HIO_cutTurnR_c0::m.field_0x28) * dVar7);
        if (mVelocity <= 0.001f) {
          onModeFlg(ModeFlg_00000001);
          m3598 = 0.0f;
        } else {
          offModeFlg(ModeFlg_00000001);
          m3598 = 1.0f;
        }
        if ((mEquipItem == daPyItem_BOKO_e) &&
            (mAnmRatioUpper[UPPER_MOVE0_e].getAnmTransform() !=
             (J3DAnmTransform *)0x0)) {
          mFrameCtrlUpper[UPPER_MOVE0_e].setFrame(
              mFrameCtrlUpper[UPPER_MOVE0_e].getEnd() - 0.001f);
          mAnmRatioUpper[UPPER_MOVE0_e].getAnmTransform()->setFrame(
              mFrameCtrlUpper[UPPER_MOVE0_e].getFrame());
        }
      } else {
        if (m34D0 == 0) {
          procCutRoll_init();
        } else {
          mVelocity = speedF;
          procCutTurn_init(0);
        }
      }
    }
    return true;
}

/* 80159130-801592A4       .text procCutReverse_init__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
BOOL daPy_lk_c::procCutReverse_init(daPy_ANM param_0) {
    dComIfGp_getVibration().StartShock(4, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    if (param_0 == ANM_JATTACK) {
      return true;
    } else {
      s32 uVar2 = mNoResetFlg0 >> 2 & 1;
      commonProcInit(daPyProc_CUT_REVERSE_e);
      if ((uVar2) != 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
      }
      setSingleMoveAnime(
          param_0, daPy_HIO_cut_c0::m.field_0x2C, daPy_HIO_cut_c0::m.field_0x30,
          daPy_HIO_cut_c0::m.field_0x6, daPy_HIO_cut_c0::m.field_0x38);
      mVelocity = 12.0f;
      current.angle.y = shape_angle.y + 0x8000;
      m3522 = 0;
      voiceStart(37);
      if ((mCurrAttributeCode == dBgS_Attr_ICE_e) && (!checkHeavyStateOn())) {
        m36A0.x += 10.0f * cM_ssin(current.angle.y);
        m36A0.z += 10.0f * cM_scos(current.angle.y);
      }
    }
    return true;
}

/* 801592A4-80159390       .text procCutReverse__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutReverse() {
    cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_guard_c0::m.field_0x18,
                 daPy_HIO_guard_c0::m.field_0x1C,
                 daPy_HIO_guard_c0::m.field_0x20);
    if ((swordButton()) && (mEquipItem == daPyItem_SWORD_e)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.0099999998f) {
      current.angle.y = shape_angle.y;
      checkNextMode(0);
    } else {
      if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >
          daPy_HIO_cut_c0::m.field_0x34) {
        current.angle.y = shape_angle.y;
        if (!checkNextMode(1)) {
          current.angle.y = shape_angle.y + 0x8000;
        }
      }
    }
    return true;
}

/* 80159390-80159500       .text procJumpCut_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procJumpCut_init(int param_0) {
    fopAc_ac_c *uVar1 = mActorKeepEquip.getActor();
    if ((daPy_dmEcallBack_c::m_type == 1) ||
        ((mEquipItem == daPyItem_BOKO_e && (uVar1 == NULL)))) {
      return false;
    } else {
      commonProcInit(daPyProc_JUMP_CUT_e);
      if (param_0 != 0) {
        setSingleMoveAnime(ANM_JATTACK, daPy_HIO_cutJump_c0::m.field_0x20,
                           daPy_HIO_cutJump_c0::m.field_0x24,
                           daPy_HIO_cutJump_c0::m.field_0x6,
                           daPy_HIO_cutJump_c0::m.field_0x28);
        mVelocity = daPy_HIO_cutJump_c0::m.field_0x2C;
        speed.y = daPy_HIO_cutJump_c0::m.field_0x30;
        gravity = daPy_HIO_cutJump_c0::m.field_0x34;
      } else {
        setSingleMoveAnime(ANM_JATTACK, daPy_HIO_cutJump_c0::m.field_0x8,
                           daPy_HIO_cutJump_c0::m.field_0xC,
                           daPy_HIO_cutJump_c0::m.field_0x0,
                           daPy_HIO_cutJump_c0::m.field_0x10);
        mVelocity = daPy_HIO_cutJump_c0::m.field_0x14;
        speed.y = daPy_HIO_cutJump_c0::m.field_0x18;
        gravity = daPy_HIO_cutJump_c0::m.field_0x1C;
      }
      current.angle.y = shape_angle.y;
      m3570 = 0;
      voiceStart(1);
      dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
      if (mEquipItem == daPyItem_BOKO_e) {
        setBlurPosResource(LKANM__WEAPONJUMP_POS);
      } else {
        setBlurPosResource(LKANM__CUTJUMP_POS);
      }
      setJumpCutAtParam();
      return true;
    }
}

/* 80159500-80159608       .text procJumpCut__9daPy_lk_cFv */
BOOL daPy_lk_c::procJumpCut() {
    /* Nonmatching - floats */
    if (mAcch.ChkGroundHit()) {
      return procJumpCutLand_init();
    } else {
      if ((current.angle.y == shape_angle.y) &&
          (changeCutReverseProc(ANM_JATTACK))) {
        current.angle.y = current.angle.y + 0x8000;
        mVelocity = 27.0f;
      } else if (current.angle.y != shape_angle.y) {
        cLib_addCalc(&mVelocity, 5.0f, 0.2f, 1.0f, 0.1f);
      }
      if ((mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >=
           daPy_HIO_cutJump_c0::m.field_0x48) &&
          (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() <
           daPy_HIO_cutJump_c0::m.field_0x4C)) {
        if (mEquipItem != daPyItem_NONE_e) {
          if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
          }
          onResetFlg0(daPyRFlg0_UNK2);
        }
      }
      return true;
    }
}

/* 80159608-80159864       .text procJumpCutLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procJumpCutLand_init() {
    /* Nonmatching - floats */
    f32 dVar3 = (m35F0 - current.pos.y);
    commonProcInit(daPyProc_JUMP_CUT_LAND_e);
    if (!dComIfGp_event_runCheck()) {
      if (dVar3 >= (100.0f * daPy_HIO_fall_c0::m.field_0x10)) {
        setDamagePoint(-2.0f);
      } else {
        if (dVar3 >= (100.0f * daPy_HIO_fall_c0::m.field_0x14)) {
          setDamagePoint(-1.0f);
        }
      }
      if (dVar3 >= (100.0f * daPy_HIO_fall_c0::m.field_0x14)) {
        mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x0;
        onModeFlg(ModeFlg_DAMAGE);
      }
    }
    mVelocity = 0.0f;
    setSingleMoveAnime(ANM_JATTACKLAND, daPy_HIO_cutJump_c0::m.field_0x38,
                       daPy_HIO_cutJump_c0::m.field_0x3C,
                       daPy_HIO_cutJump_c0::m.field_0x2,
                       daPy_HIO_cutJump_c0::m.field_0x40);
    if (mEquipItem == daPyItem_NONE_e) {
      m3570 = 0;
    } else {
      onResetFlg0(daPyRFlg0_UNK2);
      if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
        seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        mSwBlur.initSwBlur(mpCLModel->getBaseTRMtx(),
                           (10.0f * daPy_HIO_cutJump_c0::m.field_0x48),
                           getBlurTopRate(), getSwordBlurColor());
        onNoResetFlg0(daPyFlg0_CUT_AT_FLG);
      }
      setJumpCutAtParam();
      m3570 = 1;
    }
    m34D0 = daPy_HIO_cutJump_c0::m.field_0x4;
    current.angle.y = shape_angle.y + 0x8000;
    m34BE = 3;
    onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
    onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
    if (mEquipItem == dItem_SKULL_HAMMER_e) {
      setHammerQuake(NULL, NULL, -1);
    } else {
      if (checkHeavyStateOn()) {
        dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
      }
    }
    return true;
}

/* 80159864-80159998       .text procJumpCutLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procJumpCutLand() {
    current.angle.y = shape_angle.y;
    resetFootEffect();
    if ((m3570 != 0) && (changeCutReverseProc(ANM_CUTRER))) {
      return true;
    } else {
      if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.0099999998f) {
        if ((int)m34D0 > 0) {
          m34D0--;
          checkNextMode(1);
        } else {
          checkNextMode(0);
        }
      } else {
        if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >
            daPy_HIO_cutJump_c0::m.field_0x44) {
          checkNextMode(1);
        } else {
          if (m3570 != 0) {
            m3570 = 0;
            if ((abs(m3578) > 0xf800) && (daPy_dmEcallBack_c::m_type != 1) &&
                ((mEquipItem == daPyItem_SWORD_e ||
                  (mEquipItem == daPyItem_BOKO_e)))) {
              procCutTurn_init(1);
            } else {
              onResetFlg0(daPyRFlg0_UNK2);
            }
          }
        }
      }
    }
    return true;
}

/* 80159998-80159B80       .text procCutExMJ_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procCutExMJ_init(int param_0) {
    /* Nonmatching - floats */
    daPy_ANM dVar3;

    commonProcInit(daPyProc_CUT_EX_MJ_e);
    if (param_0 != 0) {
      dVar3 = ANM_MROLLRC;
      m34D6 = 0x71;
      setBlurPosResource(LKANM__BTROTATECUTR_POS);
      m35A0 = daPy_HIO_cutExMJ_c0::m.field_0x20;
    } else {
      dVar3 = ANM_MROLLLC;
      m34D6 = 0x70;
      setBlurPosResource(LKANM__BTROTATECUTL_POS);
      m35A0 = daPy_HIO_cutExMJ_c0::m.field_0x24;
    }
    setSingleMoveAnime(
        dVar3, daPy_HIO_cutExMJ_c0::m.field_0x4, daPy_HIO_cutExMJ_c0::m.field_0x8,
        daPy_HIO_cutExMJ_c0::m.field_0x0, daPy_HIO_cutExMJ_c0::m.field_0xC);
    if (checkNormalSwordEquip()) {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_MROLLCA));
    } else {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_MROLLCMS));
    }
    m35EC = daPy_HIO_cutExMJ_c0::m.field_0x8;
    onNoResetFlg0(daPyFlg0_UNK4);
    voiceStart(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    if (m34C4 != 6) {
      m3522 = daPy_HIO_cutExMJ_c0::m.field_0x2;
      setExtraCutAtParam(30);
    } else {
      m34C4 = 0;
      m3522 = 0;
      setExtraFinishCutAtParam(30);
    }
    speed.y = daPy_HIO_cutExMJ_c0::m.field_0x10;
    gravity = daPy_HIO_cutExMJ_c0::m.field_0x14;
    m34D4 = 0;
    offNoResetFlg0(daPyFlg0_NO_FALL_VOICE);
    offNoResetFlg0(daPyFlg0_CUT_AT_FLG);
    mVelocity = 7.5f;
    return true;
}

/* 80159B80-80159E60       .text procCutExMJ__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExMJ() {
    /* Nonmatching - floats */
    m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if ((swordButton()) && (m34C5 == 0)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    if (m34C4 != 0) {
      m3522 = daPy_HIO_cutExMJ_c0::m.field_0x2;
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.0099999998f) {
      if (m34D4 == 0) {
        m34D4 = 1;
      } else if (m34D4 == 1) {
        setSingleMoveAnime(ANM_JMPEDS, 0.0f, 0.0f, -1,
                           daPy_HIO_cutExMJ_c0::m.field_0x1C);
        offModeFlg(ModeFlg_00000400);
        setTextureAnime(0x37, 0);
        resetSeAnime();
        m34D4 = 2;
      }
      if (m34D6 == 0x71) {
        if (!(m34EC > 0) || (m34EC > 0x4000)) {
          m34EC -= 0x1800;
        } else {
          cLib_addCalcAngleS(&m34EC, 1, 2, 0x1800, 0x800);
        }
      } else if (!(m34EC < 0) || (m34EC < -0x4000)) {
        m34EC += 0x1800;
      } else {
        cLib_addCalcAngleS(&m34EC, -1, 2, 0x1800, 0x800);
      }
      if (mAcch.ChkGroundHit()) {
        return changeLandProc(daPy_HIO_autoJump_c0::m.field_0x24);
      }
    }
    if (mpAttnActorLockOn != NULL) {
      setShapeAngleToAtnActor();
      current.angle.y = shape_angle.y;
    }
    setSpecialBattle(1);
    if ((doTrigger()) && (dComIfGp_getDoStatus() == 26)) {
      return changeSpecialBattle();
    } else {
      if ((m34C4 != 0) && ((swordTrigger() && (m34C5 != 5)))) {
        m34C5 = 30;
      }
      if (speed.y < -gravity) {
        gravity = daPy_HIO_cutExMJ_c0::m.field_0x18;
      }
      setFallVoice();
      if ((m34D4 != 2) && (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= m35A0)) {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
          onResetFlg0(daPyRFlg0_UNK1);
          seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
      }
      if (current.pos.y < m3688.y - 200.0f) {
        cLib_chaseF(&mVelocity, 0.0f,
                    (0.1f * daPy_HIO_autoJump_c0::m.field_0x3C));
      }
      return true;
    }
}

/* 80159E60-80159FB0       .text procCutKesa_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutKesa_init() {
    commonProcInit(daPyProc_CUT_KESA_e);
    setSingleMoveAnime(ANM_CUTKESA, daPy_HIO_cutKesa_c0::m.field_0x4,
                       daPy_HIO_cutKesa_c0::m.field_0x8,
                       daPy_HIO_cutKesa_c0::m.field_0x0,
                       daPy_HIO_cutKesa_c0::m.field_0xC);
    if (checkNormalSwordEquip()) {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_EXCA1A));
    } else {
      mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_EXCA1MS));
    }
    m35EC = daPy_HIO_cutKesa_c0::m.field_0x8;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    onNoResetFlg0(daPyFlg0_UNK4);
    voiceStart(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    setBlurPosResource(LKANM__CUTKESA_POS);
    setExtraCutAtParam(31);
    m3522 = daPy_HIO_cutKesa_c0::m.field_0x2;
    return true;
}

/* 80159FB0-8015A1DC       .text procCutKesa__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutKesa() {
    J3DFrameCtrl &frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if ((swordButton()) && (m34C5 == 0)) {
      onNoResetFlg0(daPyFlg0_UNK4);
    } else {
      offNoResetFlg0(daPyFlg0_UNK4);
    }
    m3522 = daPy_HIO_cutKesa_c0::m.field_0x2;
    if (frameCtrl.getRate() < 0.0099999998f) {
      mVelocity = 0.0f;
      checkNextMode(0);
      return true;
    } else {
      if (frameCtrl.getFrame() > daPy_HIO_cutKesa_c0::m.field_0x18) {
        f32 dVar4 = mVelocity;
        mVelocity = 0.0f;
        if (checkNextMode(1)) {
          return true;
        }
        mVelocity = dVar4;
      } else if (frameCtrl.checkPass(16.0f)) {
        onModeFlg(ModeFlg_00000080);
      }
      if (changeCutReverseProc(ANM_CUTREL)) {
        return true;
      } else {
        setSpecialBattle(1);
        if ((doTrigger()) && (dComIfGp_getDoStatus() == 26)) {
          changeSpecialBattle();
        } else {
          if ((swordTrigger()) && (m34C5 != 5)) {
            m34C5 = 31;
          }
          if (mpAttnActorLockOn != NULL) {
            setShapeAngleToAtnActor();
            current.angle.y = shape_angle.y;
          }
          if ((frameCtrl.getFrame() >= daPy_HIO_cutKesa_c0::m.field_0x10) &&
              (frameCtrl.getFrame() < daPy_HIO_cutKesa_c0::m.field_0x14)) {
            if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
              onResetFlg0(daPyRFlg0_UNK1);
              seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
            }
            onResetFlg0(daPyRFlg0_UNK2);
          }
          m34C2 = 1;
          cLib_addCalc(&mVelocity, 0.0f, daPy_HIO_cutEA_c0::m.field_0x1C,
                       daPy_HIO_cutEA_c0::m.field_0x14,
                       daPy_HIO_cutEA_c0::m.field_0x18);
          return true;
        }
      }
    }
}
