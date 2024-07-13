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
#include "d/actor/d_a_player_hio.h"
#include "JSystem/J3DGraphLoader/J3DAnmLoader.h"
#include "JSystem/JKernel/JKRSolidHeap.h"

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
    BOOL ret = mSwordAnim.init(modelData, bck, false, J3DFrameCtrl::LOOP_REPEAT_e, 1.0f, 0, -1, false);
    if (!ret) { JUT_ASSERT(86, FALSE); }
    
    if (!checkNormalSwordEquip()) {
        buffer = new(0x20) u8[0x400];
        JKRReadIdxResource(buffer, 0x400, LKANM_BTK_TSWMS, dComIfGp_getAnmArchive());
        mpEquipItemBtk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(buffer));
        mpEquipItemBtk->setFrame(0.0f);
        mpEquipItemBtk->searchUpdateMaterialID(modelData);
        modelData->entryTexMtxAnimator(mpEquipItemBtk);
    }
    
    mSwBlur.mpPosBuffer = new(0x20) u8[0x4800];
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
}

/* 801554C8-80155544       .text checkDemoSwordNoDraw__9daPy_lk_cFi */
BOOL daPy_lk_c::checkDemoSwordNoDraw(int) {
    /* Nonmatching */
}

/* 80155544-80155574       .text checkChanceMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkChanceMode() {
    /* Nonmatching */
}

/* 80155574-8015559C       .text checkCutRollChange__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkCutRollChange() const {
    /* Nonmatching */
}

/* 8015559C-801555FC       .text getSwordBlurColor__9daPy_lk_cFv */
void daPy_lk_c::getSwordBlurColor() {
    /* Nonmatching */
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
    setAtParam(AT_TYPE_SWORD, atp, dCcG_At_Spl_UNK0, dCcD_SE_UNK1, G_AT_MARK_NORMAL_HIT, cutType, radius);
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
    setAtParam(AT_TYPE_SWORD, atp, dCcG_At_Spl_UNK1, dCcD_SE_UNK1, G_AT_MARK_BIG_HIT, cutType, radius);
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
    setAtParam(AT_TYPE_SWORD, atp, dCcG_At_Spl_UNK0, dCcD_SE_UNK1, G_AT_MARK_NORMAL_HIT, cutType, radius);
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
    setAtParam(AT_TYPE_SWORD, atp, dCcG_At_Spl_UNK1, dCcD_SE_UNK1, G_AT_MARK_BIG_HIT, cutType, radius);
}

/* 8015585C-80155970       .text setJumpCutAtParam__9daPy_lk_cFv */
void daPy_lk_c::setJumpCutAtParam() {
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
        setAtParam(AT_TYPE_SWORD, atp, dCcG_At_Spl_UNK1, dCcD_SE_UNK1, G_AT_MARK_BIG_HIT, 0xA, radius);
    } else if (mEquipItem == dItem_SKULL_HAMMER_e) {
        setAtParam(AT_TYPE_SKULL_HAMMER, 4, dCcG_At_Spl_UNK1, dCcD_SE_UNK5, G_AT_MARK_NORMAL_HIT, 0x13, 50.0f);
    } else if (mActorKeepEquip.getActor()) {
        setEnemyWeaponAtParam(TRUE);
    } else {
        setAtParam(AT_TYPE_MACHETE, 2, dCcG_At_Spl_UNK1, dCcD_SE_UNK1, G_AT_MARK_BIG_HIT, 0xE, 30.0f);
    }
}

/* 80155970-801559F0       .text getCutDirection__9daPy_lk_cFv */
int daPy_lk_c::getCutDirection(){
    int iVar1;
    s16 sVar2;

    if (m35B0 <= 0.05f) {
        iVar1 = 4;
    }
    else {
        if (mpAttnActorLockOn != NULL) {
            sVar2 = fopAcM_searchActorAngleY(this, mpAttnActorLockOn);
            sVar2 =  m34E8 - sVar2;
        }
        else {
            sVar2 = m34E8 - m34DE;
        }
        iVar1 = getDirectionFromAngle(sVar2);
    }
    return iVar1 + 1;
}

/* 801559F0-80155C3C       .text changeCutProc__9daPy_lk_cFv */
void daPy_lk_c::changeCutProc() {
    /* Nonmatching */
}

/* 80155C3C-80156034       .text changeCutReverseProc__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
void daPy_lk_c::changeCutReverseProc(daPy_ANM) {
    /* Nonmatching */
}

/* 80156034-80156198       .text procCutA_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutA_init(s16) {
    /* Nonmatching */
}

/* 80156198-80156424       .text procCutA__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutA() {
    /* Nonmatching */
}

/* 80156424-80156584       .text procCutF_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutF_init(s16) {
    /* Nonmatching */
}

/* 80156584-80156828       .text procCutF__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutF() {
    /* Nonmatching */
}

/* 80156828-80156984       .text procCutR_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutR_init(s16) {
    /* Nonmatching */
}

/* 80156984-80156C10       .text procCutR__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutR() {
    /* Nonmatching */
}

/* 80156C10-80156D6C       .text procCutL_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutL_init(s16) {
    /* Nonmatching */
}

/* 80156D6C-80156FF8       .text procCutL__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutL() {
    /* Nonmatching */
}

/* 80156FF8-80157154       .text procCutEA_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutEA_init() {
    /* Nonmatching */
}

/* 80157154-80157348       .text procCutEA__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutEA() {
    /* Nonmatching */
}

/* 80157348-801574A4       .text procCutEB_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutEB_init() {
    /* Nonmatching */
}

/* 801574A4-8015768C       .text procCutEB__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutEB() {
    /* Nonmatching */
}

/* 8015768C-801577EC       .text procCutExA_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExA_init() {
    /* Nonmatching */
}

/* 801577EC-80157A18       .text procCutExA__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExA() {
    /* Nonmatching */
}

/* 80157A18-80157B74       .text procCutExB_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExB_init() {
    /* Nonmatching */
}

/* 80157B74-80157D3C       .text procCutExB__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExB() {
    /* Nonmatching */
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
    /* Nonmatching */
    static JGeometry::TVec3<f32> emitter_trans(0.0f, 55.0f, 0.0f);
    static JGeometry::TVec3<f32> particle_scale(0.76f, 0.76f, 0.76f);
}

/* 80158A40-80158A98       .text procCutRollEnd__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutRollEnd() {
    /* Nonmatching */
}

/* 80158A98-80158B00       .text procCutTurnCharge_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnCharge_init() {
    /* Nonmatching */
}

/* 80158B00-80158B58       .text procCutTurnCharge__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnCharge() {
    /* Nonmatching */
}

/* 80158B58-80158D40       .text procCutTurnMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnMove_init() {
    /* Nonmatching */
    static Vec eff_scale = {1.5f, 1.5f, 1.5f};
}

/* 80158D40-80159130       .text procCutTurnMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnMove() {
    /* Nonmatching */
}

/* 80159130-801592A4       .text procCutReverse_init__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
BOOL daPy_lk_c::procCutReverse_init(daPy_ANM) {
    /* Nonmatching */
}

/* 801592A4-80159390       .text procCutReverse__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutReverse() {
    /* Nonmatching */
}

/* 80159390-80159500       .text procJumpCut_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procJumpCut_init(int) {
    /* Nonmatching */
}

/* 80159500-80159608       .text procJumpCut__9daPy_lk_cFv */
BOOL daPy_lk_c::procJumpCut() {
    /* Nonmatching */
}

/* 80159608-80159864       .text procJumpCutLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procJumpCutLand_init() {
    /* Nonmatching */
}

/* 80159864-80159998       .text procJumpCutLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procJumpCutLand() {
    /* Nonmatching */
}

/* 80159998-80159B80       .text procCutExMJ_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procCutExMJ_init(int) {
    /* Nonmatching */
}

/* 80159B80-80159E60       .text procCutExMJ__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExMJ() {
    /* Nonmatching */
}

/* 80159E60-80159FB0       .text procCutKesa_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutKesa_init() {
    /* Nonmatching */
}

/* 80159FB0-8015A1DC       .text procCutKesa__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutKesa() {
    /* Nonmatching */
}
