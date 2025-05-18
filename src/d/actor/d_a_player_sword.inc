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

#include "d/actor/d_a_boko.h"
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
            LKANM_BRK_CUTFH,
        },
        {
            LINK_BDL_SWMS,
            LINK_BDL_YMSLI00,
            LKANM_BTK_YMSLI00,
            LKANM_BRK_YMSLI00,
            LINK_BDL_CUTFM,
            LKANM_BPK_CUTFM,
            LKANM_BTK_CUTFM,
            LKANM_BRK_CUTFM,
        },
    };

    u8* buffer;

    J3DAnmTransform* bck =
        checkNormalSwordEquip() ? getItemAnimeResource(LKANM_BCK_CUTAA) : getItemAnimeResource(LKANM_BCK_CUTAMS);

    mEquipItem = daPyItem_SWORD_e;
    JKRHeap* oldHeap = setItemHeap();

    const sword_model_tbl_s& model_tbl = checkNormalSwordEquip() ? sword_model_tbl[0] : sword_model_tbl[1];
    J3DModelData* modelData = initModel(&mpEquipItemModel, model_tbl.bladeModel, 0x37221222);
    BOOL ret = mSwordAnim.init(modelData, bck, false, J3DFrameCtrl::EMode_LOOP, 1.0f, 0, -1, false);
    if (!ret) {
        JUT_ASSERT(86, FALSE);
    }

    if (!checkNormalSwordEquip()) {
        buffer = new (0x20) u8[0x400];
        JKRReadIdxResource(buffer, 0x400, LKANM_BTK_TSWMS, dComIfGp_getAnmArchive());
        mpEquipItemBtk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(buffer));
        mpEquipItemBtk->setFrame(0.0f);
        mpEquipItemBtk->searchUpdateMaterialID(modelData);
        modelData->entryTexMtxAnimator(mpEquipItemBtk);
    }

    mSwBlur.mpPosBuffer = new (0x20) Vec[2 * 0x300];
    modelData = initModel(&mpSwordModel1, model_tbl.glowModel, 0x13000222);

    buffer = new (0x20) u8[0x400];
    JKRReadIdxResource(buffer, 0x400, model_tbl.glowBtk, dComIfGp_getAnmArchive());
    mpSwordBtk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(buffer));
    mpSwordBtk->setFrame(0.0f);
    mpSwordBtk->searchUpdateMaterialID(modelData);
    modelData->entryTexMtxAnimator(mpSwordBtk);

    buffer = new (0x20) u8[0x400];
    JKRReadIdxResource(buffer, 0x400, model_tbl.glowBrk, dComIfGp_getAnmArchive());
    mpEquipItemBrk = static_cast<J3DAnmTevRegKey*>(J3DAnmLoaderDataBase::load(buffer));
    mpEquipItemBrk->setFrame(0.0f);
    mpEquipItemBrk->searchUpdateMaterialID(modelData);
    modelData->entryTevRegAnimator(mpEquipItemBrk);

    modelData = initModel(&mpSwordTipStabModel, model_tbl.tipStabModel, 0x13000223);

    buffer = new (0x20) u8[0x400];
    JKRReadIdxResource(buffer, 0x400, model_tbl.tipStabBtk, dComIfGp_getAnmArchive());
    mpCutfBtk = static_cast<J3DAnmTextureSRTKey*>(J3DAnmLoaderDataBase::load(buffer));
    mpCutfBtk->setFrame(0.0f);
    mpCutfBtk->searchUpdateMaterialID(modelData);
    modelData->entryTexMtxAnimator(mpCutfBtk);

    buffer = new (0x20) u8[0x400];
    JKRReadIdxResource(buffer, 0x400, model_tbl.tipStabBrk, dComIfGp_getAnmArchive());
    mpCutfBrk = static_cast<J3DAnmTevRegKey*>(J3DAnmLoaderDataBase::load(buffer));
    mpCutfBrk->setFrame(0.0f);
    mpCutfBrk->searchUpdateMaterialID(modelData);
    modelData->entryTevRegAnimator(mpCutfBrk);

    buffer = new (0x20) u8[0x400];
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
    static JGeometry::TVec3<f32> d_scale(1.4f, 1.4f, 1.4f);
    static JGeometry::TVec3<f32> p_scale(1.6f, 1.4f, 1.4f);
    static const GXColor g_prm0 = {0x09, 0x14, 0x06, 0xFF};
    static const GXColor g_env0 = {0x0C, 0x18, 0x00, 0xFF};
    static const GXColor y_prm0 = {0x14, 0x12, 0x0C, 0xFF};
    static const GXColor y_env0 = {0x18, 0x18, 0x00, 0xFF};
    static const GXColor g_prm1 = {0x80, 0xFF, 0x64, 0xFF};
    static const GXColor y_prm1 = {0xFF, 0xFF, 0xC8, 0xFF};
    static const GXColor y_env1 = {0xA5, 0xA5, 0x10, 0xFF};
    static const GXColor s_prm1 = {0xC8, 0xC8, 0xFF, 0xFF};
    static const GXColor s_env1 = {0x60, 0x60, 0xA5, 0xFF};
    JPABaseEmitter* pJVar7;
    const GXColor* pbVar8;
    const GXColor* pbVar9;

    if (((mEquipItem != daPyItem_SWORD_e || mpEquipItemBrk == NULL) || mpSwordBtk == NULL) ||
        (mpSwordModel1 == NULL || mpEquipItemModel == NULL))
    {
        return;
    }
    if (checkChanceMode()) {
        mpEquipItemBrk->setFrame(1.0f);
    } else if (checkNoResetFlg1(daPyFlg1_UNK8000)) {
        mpEquipItemBrk->setFrame(0.0f);
    } else {
        mpEquipItemBrk->setFrame(2.0f);
    }
    mpSwordModel1->setBaseTRMtx(mpEquipItemModel->getBaseTRMtx());
    if (!checkDemoSwordNoDraw(0) &&
        ((checkChanceMode() || checkNoResetFlg1(daPyFlg1_UNK8000)) || checkFinalMasterSwordEquip()))
    {
        simpleAnmPlay(mpSwordBtk);
        if ((m3454.getEmitter() == NULL) && (checkChanceMode() || checkNoResetFlg1(daPyFlg1_UNK8000))) {
            pJVar7 = m3454.makeEmitter(dPa_name::ID_COMMON_0309, mpSwordModel1->getAnmMtx(2), &current.pos, NULL);
            if (pJVar7 != 0) {
                if (checkMasterSwordEquip()) {
                    pJVar7->setGlobalDynamicsScale(d_scale);
                    pJVar7->setGlobalParticleScale(p_scale);
                }
            }
        } else if (!checkChanceMode() && (!checkNoResetFlg1(daPyFlg1_UNK8000) && checkFinalMasterSwordEquip())) {
            m3454.end();
        }
        if (checkChanceMode()) {
            pbVar8 = &g_prm0;
            pbVar9 = &g_env0;
        } else {
            pbVar8 = &y_prm0;
            pbVar9 = &y_env0;
        }
        pJVar7 = m3454.getEmitter();
        if (pJVar7 != NULL) {
            pJVar7->setGlobalPrmColor(pbVar8->r, pbVar8->g, pbVar8->b);
            pJVar7->setGlobalEnvColor(pbVar9->r, pbVar9->g, pbVar9->b);
        }
        if ((dComIfGp_getDoStatus() == dActStts_PARRY_e && m355C == 0) ||
            ((checkNoResetFlg1(daPyFlg1_UNK8000) || checkFinalMasterSwordEquip()) &&
             !checkNoResetFlg1(daPyFlg1_UNK200000)))
        {
            if (dComIfGp_getDoStatus() == dActStts_PARRY_e && m355C == 0) {
                pbVar9 = &g_prm1;
                pbVar8 = pbVar9;
                dComIfGp_getVibration().StartShock(6, 1, cXyz(0.0f, 1.0f, 0.0f));
            } else if (checkNoResetFlg1(daPyFlg1_UNK8000)) {
                pbVar9 = &y_prm1;
                pbVar8 = &y_env1;
            } else {
                pbVar9 = &s_prm1;
                pbVar8 = &s_env1;
            }
            pJVar7 = dComIfGp_particle_setP1(
                dPa_name::ID_COMMON_030A, &current.pos, NULL, NULL, 0xFF, NULL, -1, pbVar9, pbVar8, NULL
            );
            if (pJVar7 != 0) {
                pJVar7->setGlobalRTMatrix(mpEquipItemModel->getAnmMtx(2));
                if (checkMasterSwordEquip()) {
                    pJVar7->setGlobalDynamicsScale(d_scale);
                    pJVar7->setGlobalParticleScale(p_scale);
                }
                if (pbVar9 == &g_prm1) {
                    m355C = 0x1e;
                } else {
                    onNoResetFlg1(daPyFlg1_UNK200000);
                }
            }
        }
    } else {
        m3454.end();
        mpSwordBtk->setFrame(0.0f);
    }
    if (m355C > 0 && !checkChanceMode()) {
        m355C--;
    }
}

/* 80155490-801554C8       .text checkDemoShieldNoDraw__9daPy_lk_cFv */
BOOL daPy_lk_c::checkDemoShieldNoDraw() {
    if (dComIfGs_isEventBit(0x3f40)) {
        return TRUE;
    } else {
        return FALSE;
    }
}

/* 801554C8-80155544       .text checkDemoSwordNoDraw__9daPy_lk_cFi */
BOOL daPy_lk_c::checkDemoSwordNoDraw(BOOL param_0) {
    if ((mEquipItem == daPyItem_SWORD_e || param_0) &&
        (dComIfGs_isEventBit(0x3f40) || (mCurProc == daPyProc_DEMO_TOOL_e && m34D6 == 1)))
    {
        return true;
    } else {
        return false;
    }
}

/* 80155544-80155574       .text checkChanceMode__9daPy_lk_cFv */
BOOL daPy_lk_c::checkChanceMode() {
    if (dComIfGp_getDoStatus() == dActStts_PARRY_e || checkModeFlg(ModeFlg_PARRY)) {
        return true;
    }
    return false;
}

/* 80155574-8015559C       .text checkCutRollChange__9daPy_lk_cCFv */
BOOL daPy_lk_c::checkCutRollChange() const {
    if (mCurProc == daPyProc_CUT_TURN_MOVE_e && m34D0 >= 0) {
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
    int direction;
    if (mStickDistance <= 0.05f) {
        direction = DIR_NONE;
    } else {
        s16 angle;
        if (mpAttnActorLockOn != NULL) {
            angle = m34E8 - fopAcM_searchActorAngleY(this, mpAttnActorLockOn);
        } else {
            angle = m34E8 - m34DE;
        }
        direction = getDirectionFromAngle(angle);
    }
    return direction + 1;
}

/* 801559F0-80155C3C       .text changeCutProc__9daPy_lk_cFv */
int daPy_lk_c::changeCutProc() {
    if (m34C5 == 5 && changeSpecialBattle()) {
        m34C4 = 0;
        return true;
    }
    m34C4++;
    int direction = getCutDirection() - 1;
    short sVar2;
    if (mpAttention->Lockon() || mStickDistance <= 0.05f) {
        sVar2 = shape_angle.y;
    } else {
        sVar2 = m34E8;
    }
    u32 bVar1 = m34C4;
    if (bVar1 > 4) {
        mCutCount = bVar1 - 2;
    } else {
        mCutCount = bVar1;
    }
    bVar1 = m34C4;

    if (bVar1 == 4) {
        if (direction == DIR_RIGHT || direction == DIR_FORWARD) {
            procCutEA_init();
        } else {
            procCutEB_init();
        }
    } else if (bVar1 < 4) {
        if (direction == DIR_FORWARD) {
            procCutF_init(sVar2);
        } else if (direction == DIR_RIGHT) {
            procCutR_init(sVar2);
        } else if (direction == DIR_NONE) {
            if (mpAttention->Lockon()) {
                procCutA_init(sVar2);
            } else {
                procCutL_init(sVar2);
            }
        } else {
            procCutL_init(sVar2);
        }
    } else if (bVar1 == 6) {
        if (direction == DIR_FORWARD) {
            procCutTurn_init(1);
        } else if (direction == DIR_NONE) {
            procCutExB_init();
        } else if (direction == DIR_RIGHT) {
            procCutExMJ_init(1);
        } else {
            procCutExMJ_init(0);
        }
    } else if (bVar1 < 6) {
        if (direction == DIR_FORWARD) {
            procCutExMJ_init(1);
        } else if (direction == DIR_RIGHT) {
            procCutKesa_init();
        } else {
            procCutExA_init();
        }
    }

    m3578 = 0;
    return true;
}

/* 80155C3C-80156034       .text changeCutReverseProc__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
int daPy_lk_c::changeCutReverseProc(daPy_ANM param_0) {
    if (mEquipItem != dItem_SKULL_HAMMER_e) {
        if (mAtCps[0].ChkAtShieldHit() || mAtCps[1].ChkAtShieldHit() || mAtCps[2].ChkAtShieldHit()) {
            return procCutReverse_init(param_0);
        }
    }

    if (checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
        cXyz local_24;
        local_24.x = current.pos.x;
        local_24.y = current.pos.y + 30.0f;
        local_24.z = current.pos.z;
        mLinkLinChk.Set(&local_24, &mSwordTopPos, this);
        if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
            cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
            if (!cBgW_CheckBGround(triPla->GetNP()->y) ||
                (mCurProc == daPyProc_HAMMER_FRONT_SWING_e && triPla->GetNP()->y < 0.64278764f))
            {
                if (mEquipItem != dItem_DEKU_LEAF_e) {
                    u32 uVar7 = dComIfG_Bgsp()->GetMtrlSndId(mLinkLinChk);
                    u32 uVar12;
                    if (mAtCps[0].GetAtType() == AT_TYPE_BOKO_STICK) {
                        uVar12 = JA_SE_LK_W_WEP_HIT;
                    } else if (mAtCps[0].GetAtType() == AT_TYPE_STALFOS_MACE ||
                               mAtCps[0].GetAtType() == AT_TYPE_SKULL_HAMMER)
                    {
                        uVar12 = JA_SE_LK_HAMMER_HIT;
                    } else {
                        uVar12 = JA_SE_LK_SW_HIT_S;
                    }
                    if (mAtCps[0].GetAtType() != AT_TYPE_SKULL_HAMMER || !checkNoResetFlg0(daPyFlg0_UNK10000000)) {
                        mDoAud_seStart(uVar12, &mSwordTopPos, uVar7, mReverb);
                    }
                    if (mAtCps[0].GetAtType() == AT_TYPE_SKULL_HAMMER && mCurProc != daPyProc_JUMP_CUT_e) {
                        onNoResetFlg0(daPyFlg0_UNK10000000);
                    }
                    int attrib_code = dComIfG_Bgsp()->GetAttributeCode(mLinkLinChk);
                    if (attrib_code == dBgS_Attr_WOOD_e || attrib_code == dBgS_Attr_STONE_e ||
                        attrib_code == dBgS_Attr_METAL_e)
                    {
                        triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
                        csXyz local_44;
                        local_44.x = cM_atan2s(-triPla->GetNP()->y, triPla->GetNP()->absXZ());
                        local_44.y = cM_atan2s(triPla->GetNP()->x, triPla->GetNP()->z);
                        local_44.z = 0;
                        JPABaseEmitter* emitter;
                        if (attrib_code == dBgS_Attr_WOOD_e) {
                            emitter = dComIfGp_particle_setP1(
                                dPa_name::ID_COMMON_002B,
                                mLinkLinChk.GetCrossP(),
                                &local_44,
                                NULL,
                                0xff,
                                NULL,
                                -1,
                                &tevStr.mColorK0,
                                &tevStr.mColorK0
                            );
                            if (emitter != 0) {
                                emitter->setSpread(0.2f);
                                emitter->setVolumeSweep(0.15f);
                                emitter->setRate(8.0f);
                                emitter->setMaxFrame(1);
                            }
                        } else {
                            local_44.x += 0x4000;
                            emitter =
                                dComIfGp_particle_setP1(dPa_name::ID_COMMON_002C, mLinkLinChk.GetCrossP(), &local_44);
                            if (emitter != 0) {
                                emitter->setAwayFromAxisSpeed(20.0f);
                                emitter->setRate(20.0f);
                                emitter->setMaxFrame(1);
                                emitter->setDirectionalSpeed(20.0f);
                            }
                        }
                    }
                }
                dKy_Sound_set(current.pos, 100, fopAcM_GetID(this), 5);
                return procCutReverse_init(param_0);
            }
            if (mCurProc == daPyProc_HAMMER_FRONT_SWING_e) {
                return true;
            }
        }
    }
    return false;
}

/* 80156034-80156198       .text procCutA_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutA_init(s16 param_0) {
    commonProcInit(daPyProc_CUT_A_e);
    setSingleMoveAnime(
        ANM_CUTA,
        daPy_HIO_cutA_c0::m.field_0x4,
        daPy_HIO_cutA_c0::m.field_0x8,
        daPy_HIO_cutA_c0::m.field_0x2,
        daPy_HIO_cutA_c0::m.field_0x24
    );
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
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if (swordButton() && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    m3522 = daPy_HIO_cutA_c0::m.field_0x0;
    if (frameCtrl.getRate() < 0.01f) {
        mVelocity = 0.0f;
        mDirection = DIR_RIGHT;
        checkNextMode(0);
        return true;
    }

    if (frameCtrl.getFrame() > daPy_HIO_cutA_c0::m.field_0xC) {
        f32 dVar4 = mVelocity;
        u8 orig_direction = mDirection;
        mVelocity = 0.0f;
        mDirection = DIR_RIGHT;
        if (checkNextMode(1)) {
            return true;
        }
        mVelocity = dVar4;
        mDirection = orig_direction;
    }
    if (changeCutReverseProc(ANM_CUTRER)) {
        return true;
    }

    setSpecialBattle(TRUE);
    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }

    if (swordTrigger() && m34C5 != 5) {
        m34C5 = 1;
    }
    m34C2 = 1;
    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        m34D4 = shape_angle.y;
    } else {
        cLib_addCalcAngleS(
            &shape_angle.y,
            m34D4,
            daPy_HIO_turn_c0::m.field_0x4,
            daPy_HIO_turn_c0::m.field_0x0,
            daPy_HIO_turn_c0::m.field_0x2
        );
    }
    current.angle.y = shape_angle.y;
    if (frameCtrl.checkPass(daPy_HIO_cutA_c0::m.field_0x28)) {
        mVelocity = std::fabsf(speedF) * daPy_HIO_cutA_c0::m.field_0x10 + daPy_HIO_cutA_c0::m.field_0x14;
    }
    if (frameCtrl.getFrame() >= daPy_HIO_cutA_c0::m.field_0x2C && frameCtrl.getFrame() < daPy_HIO_cutA_c0::m.field_0x30)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    cLib_addCalc(
        &mVelocity, 0.0f, daPy_HIO_cutA_c0::m.field_0x20, daPy_HIO_cutA_c0::m.field_0x18, daPy_HIO_cutA_c0::m.field_0x1C
    );

    return true;
}

/* 80156424-80156584       .text procCutF_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutF_init(s16 param_0) {
    commonProcInit(daPyProc_CUT_F_e);
    setSingleMoveAnime(
        ANM_CUTF,
        daPy_HIO_cutF_c0::m.field_0x4,
        daPy_HIO_cutF_c0::m.field_0x8,
        daPy_HIO_cutF_c0::m.field_0x2,
        daPy_HIO_cutF_c0::m.field_0x24
    );
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
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if (swordButton() && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    mpCutfBpk->setFrame(frameCtrl.getFrame());
    mpCutfBtk->setFrame(frameCtrl.getFrame());
    m3522 = daPy_HIO_cutF_c0::m.field_0x0;
    if (frameCtrl.getRate() < 0.01f) {
        mVelocity = 0.0f;
        mDirection = DIR_RIGHT;
        checkNextMode(0);
        return true;
    }

    if (frameCtrl.getFrame() > daPy_HIO_cutF_c0::m.field_0xC) {
        f32 dVar4 = mVelocity;
        u8 orig_direction = mDirection;
        mVelocity = 0.0f;
        mDirection = DIR_RIGHT;
        if (checkNextMode(1)) {
            return true;
        }
        mVelocity = dVar4;
        mDirection = orig_direction;
    }
    if (changeCutReverseProc(ANM_CUTRER)) {
        return true;
    }
    setSpecialBattle(TRUE);
    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }

    if (swordTrigger() && m34C5 != 5) {
        m34C5 = 2;
    }
    m34C2 = 1;
    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        m34D4 = shape_angle.y;
    } else {
        cLib_addCalcAngleS(
            &shape_angle.y,
            m34D4,
            daPy_HIO_turn_c0::m.field_0x4,
            daPy_HIO_turn_c0::m.field_0x0,
            daPy_HIO_turn_c0::m.field_0x2
        );
    }
    current.angle.y = shape_angle.y;
    if (frameCtrl.checkPass(daPy_HIO_cutF_c0::m.field_0x28)) {
        mVelocity = std::fabsf(speedF) * daPy_HIO_cutF_c0::m.field_0x10 + daPy_HIO_cutF_c0::m.field_0x14;
    }
    if (frameCtrl.getFrame() >= daPy_HIO_cutF_c0::m.field_0x2C && frameCtrl.getFrame() < daPy_HIO_cutF_c0::m.field_0x30)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    cLib_addCalc(
        &mVelocity, 0.0f, daPy_HIO_cutF_c0::m.field_0x20, daPy_HIO_cutF_c0::m.field_0x18, daPy_HIO_cutF_c0::m.field_0x1C
    );
    return true;
}

/* 80156828-80156984       .text procCutR_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutR_init(s16 param_0) {
    commonProcInit(daPyProc_CUT_R_e);
    setSingleMoveAnime(
        ANM_CUTR,
        daPy_HIO_cutR_c0::m.field_0x4,
        daPy_HIO_cutR_c0::m.field_0x8,
        daPy_HIO_cutR_c0::m.field_0x2,
        daPy_HIO_cutR_c0::m.field_0x24
    );
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
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if (swordButton() && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    m3522 = daPy_HIO_cutR_c0::m.field_0x0;
    if (frameCtrl.getRate() < 0.01f) {
        mVelocity = 0.0f;
        mDirection = DIR_RIGHT;
        checkNextMode(0);
        return true;
    }

    if (frameCtrl.getFrame() > daPy_HIO_cutR_c0::m.field_0xC) {
        f32 dVar4 = mVelocity;
        u8 orig_direction = mDirection;
        mVelocity = 0.0f;
        mDirection = DIR_RIGHT;
        if (checkNextMode(1)) {
            return true;
        }
        mVelocity = dVar4;
        mDirection = orig_direction;
    }

    if (changeCutReverseProc(ANM_CUTRER)) {
        return true;
    }

    setSpecialBattle(TRUE);
    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }

    if (swordTrigger() && m34C5 != 5) {
        m34C5 = 3;
    }
    m34C2 = 1;
    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        m34D4 = shape_angle.y;
    } else {
        cLib_addCalcAngleS(
            &shape_angle.y,
            m34D4,
            daPy_HIO_turn_c0::m.field_0x4,
            daPy_HIO_turn_c0::m.field_0x0,
            daPy_HIO_turn_c0::m.field_0x2
        );
    }
    current.angle.y = shape_angle.y;
    if (frameCtrl.checkPass(daPy_HIO_cutR_c0::m.field_0x28)) {
        mVelocity = std::fabsf(speedF) * daPy_HIO_cutR_c0::m.field_0x10 + daPy_HIO_cutR_c0::m.field_0x14;
    }
    if (frameCtrl.getFrame() >= daPy_HIO_cutR_c0::m.field_0x2C && frameCtrl.getFrame() < daPy_HIO_cutR_c0::m.field_0x30)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    cLib_addCalc(
        &mVelocity, 0.0f, daPy_HIO_cutR_c0::m.field_0x20, daPy_HIO_cutR_c0::m.field_0x18, daPy_HIO_cutR_c0::m.field_0x1C
    );
    return true;
}

/* 80156C10-80156D6C       .text procCutL_init__9daPy_lk_cFs */
BOOL daPy_lk_c::procCutL_init(s16 param_0) {
    commonProcInit(daPyProc_CUT_L_e);
    setSingleMoveAnime(
        ANM_CUTL,
        daPy_HIO_cutL_c0::m.field_0x4,
        daPy_HIO_cutL_c0::m.field_0x8,
        daPy_HIO_cutL_c0::m.field_0x2,
        daPy_HIO_cutL_c0::m.field_0x24
    );
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
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if (swordButton() && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    m3522 = daPy_HIO_cutL_c0::m.field_0x0;
    if (frameCtrl.getRate() < 0.01f) {
        mVelocity = 0.0f;
        mDirection = DIR_LEFT;
        checkNextMode(0);
        return true;
    }

    if (frameCtrl.getFrame() > daPy_HIO_cutL_c0::m.field_0xC) {
        f32 dVar4 = mVelocity;
        u8 orig_direction = mDirection;
        mVelocity = 0.0f;
        mDirection = DIR_LEFT;
        if (checkNextMode(1)) {
            return true;
        }
        mVelocity = dVar4;
        mDirection = orig_direction;
    }
    if (changeCutReverseProc(ANM_CUTREL)) {
        return true;
    }

    setSpecialBattle(TRUE);
    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }
    if (swordTrigger() && m34C5 != 5) {
        m34C5 = 4;
    }
    m34C2 = 1;
    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        m34D4 = shape_angle.y;
    } else {
        cLib_addCalcAngleS(
            &shape_angle.y,
            m34D4,
            daPy_HIO_turn_c0::m.field_0x4,
            daPy_HIO_turn_c0::m.field_0x0,
            daPy_HIO_turn_c0::m.field_0x2
        );
    }
    current.angle.y = shape_angle.y;
    if (frameCtrl.checkPass(daPy_HIO_cutL_c0::m.field_0x28)) {
        mVelocity = std::fabsf(speedF) * daPy_HIO_cutL_c0::m.field_0x10 + daPy_HIO_cutL_c0::m.field_0x14;
    }
    if (frameCtrl.getFrame() >= daPy_HIO_cutL_c0::m.field_0x2C && frameCtrl.getFrame() < daPy_HIO_cutL_c0::m.field_0x30)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    cLib_addCalc(
        &mVelocity, 0.0f, daPy_HIO_cutL_c0::m.field_0x20, daPy_HIO_cutL_c0::m.field_0x18, daPy_HIO_cutL_c0::m.field_0x1C
    );
    return true;
}

/* 80156FF8-80157154       .text procCutEA_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutEA_init() {
    commonProcInit(daPyProc_CUT_EA_e);
    setSingleMoveAnime(
        ANM_CUTEA,
        daPy_HIO_cutEA_c0::m.field_0x4,
        daPy_HIO_cutEA_c0::m.field_0x8,
        daPy_HIO_cutEA_c0::m.field_0x0,
        daPy_HIO_cutEA_c0::m.field_0x20
    );
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
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if (swordButton() && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    if (frameCtrl.getRate() < 0.01f) {
        if (m34D0 > 0) {
            m34D0--;
        } else {
            mVelocity = 0.0f;
            mDirection = DIR_RIGHT;
            checkNextMode(0);
            return true;
        }
    }
    if (changeCutReverseProc(ANM_CUTREL)) {
        return true;
    }

    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        current.angle.y = shape_angle.y;
    }
    setSpecialBattle(TRUE);
    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }

    if (frameCtrl.checkPass(daPy_HIO_cutEA_c0::m.field_0x24)) {
        mVelocity = std::fabsf(speedF) * daPy_HIO_cutEA_c0::m.field_0xC + daPy_HIO_cutEA_c0::m.field_0x10;
    }
    if (frameCtrl.getFrame() >= daPy_HIO_cutEA_c0::m.field_0x28 &&
        frameCtrl.getFrame() < daPy_HIO_cutEA_c0::m.field_0x2C)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    m34C2 = 1;
    cLib_addCalc(
        &mVelocity,
        0.0f,
        daPy_HIO_cutEA_c0::m.field_0x1C,
        daPy_HIO_cutEA_c0::m.field_0x14,
        daPy_HIO_cutEA_c0::m.field_0x18
    );
    return true;
}

/* 80157348-801574A4       .text procCutEB_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutEB_init() {
    commonProcInit(daPyProc_CUT_EB_e);
    setSingleMoveAnime(
        ANM_CUTEB,
        daPy_HIO_cutEB_c0::m.field_0x4,
        daPy_HIO_cutEB_c0::m.field_0x8,
        daPy_HIO_cutEB_c0::m.field_0x0,
        daPy_HIO_cutEB_c0::m.field_0x20
    );
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
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if (swordButton() && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    if (frameCtrl.getRate() < 0.01f) {
        if (m34D0 > 0) {
            m34D0--;
        } else {
            mVelocity = 0.0f;
            mDirection = DIR_LEFT;
            checkNextMode(0);
            return true;
        }
    }
    if (changeCutReverseProc(ANM_CUTRER)) {
        return true;
    }
    setShapeAngleToAtnActor();
    current.angle.y = shape_angle.y;
    setSpecialBattle(TRUE);
    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }

    if (frameCtrl.checkPass(daPy_HIO_cutEB_c0::m.field_0x24)) {
        mVelocity = std::fabsf(speedF) * daPy_HIO_cutEB_c0::m.field_0xC + daPy_HIO_cutEB_c0::m.field_0x10;
    }
    if (frameCtrl.getFrame() >= daPy_HIO_cutEB_c0::m.field_0x28 &&
        frameCtrl.getFrame() < daPy_HIO_cutEB_c0::m.field_0x2C)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    m34C2 = 1;
    cLib_addCalc(
        &mVelocity,
        0.0f,
        daPy_HIO_cutEB_c0::m.field_0x1C,
        daPy_HIO_cutEB_c0::m.field_0x14,
        daPy_HIO_cutEB_c0::m.field_0x18
    );
    return true;
}

/* 8015768C-801577EC       .text procCutExA_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExA_init() {
    commonProcInit(daPyProc_CUT_EX_A_e);
    setSingleMoveAnime(
        ANM_EXCA1,
        daPy_HIO_cutExA_c0::m.field_0x8,
        daPy_HIO_cutExA_c0::m.field_0xC,
        daPy_HIO_cutExA_c0::m.field_0x0,
        daPy_HIO_cutExA_c0::m.field_0x10
    );
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
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if (swordButton() && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    m3522 = daPy_HIO_cutExA_c0::m.field_0x4;
    if (frameCtrl.getRate() < 0.01f) {
        mVelocity = 0.0f;
        checkNextMode(0);
        return true;
    }

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
    }

    setSpecialBattle(TRUE);
    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }

    if (swordTrigger() && m34C5 != 5) {
        m34C5 = 26;
    }
    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        current.angle.y = shape_angle.y;
    }
    if (frameCtrl.getFrame() >= daPy_HIO_cutExA_c0::m.field_0x14 &&
        frameCtrl.getFrame() < daPy_HIO_cutExA_c0::m.field_0x18)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    m34C2 = 1;
    cLib_addCalc(
        &mVelocity,
        0.0f,
        daPy_HIO_cutEA_c0::m.field_0x1C,
        daPy_HIO_cutEA_c0::m.field_0x14,
        daPy_HIO_cutEA_c0::m.field_0x18
    );
    return true;
}

/* 80157A18-80157B74       .text procCutExB_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutExB_init() {
    commonProcInit(daPyProc_CUT_EX_B_e);
    setSingleMoveAnime(
        ANM_EXCB1,
        daPy_HIO_cutExB_c0::m.field_0x4,
        daPy_HIO_cutExB_c0::m.field_0x8,
        daPy_HIO_cutExB_c0::m.field_0x0,
        daPy_HIO_cutExB_c0::m.field_0xC
    );
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
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if (swordButton() && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }

    if (frameCtrl.getRate() < 0.01f) {
        if (m34D0 > 0) {
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
    }

    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        current.angle.y = shape_angle.y;
    }

    setSpecialBattle(TRUE);

    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }

    if (frameCtrl.getFrame() >= daPy_HIO_cutExB_c0::m.field_0x10 &&
        frameCtrl.getFrame() < daPy_HIO_cutExB_c0::m.field_0x14)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    m34C2 = 1;
    cLib_addCalc(
        &mVelocity,
        0.0f,
        daPy_HIO_cutEA_c0::m.field_0x1C,
        daPy_HIO_cutEA_c0::m.field_0x14,
        daPy_HIO_cutEA_c0::m.field_0x18
    );
    return true;
}

/* 80157D3C-80158220       .text procCutTurn_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procCutTurn_init(int param_0) {
    float fVar1;

    commonProcInit(daPyProc_CUT_TURN_e);
    if (param_0 != 0) {
        fVar1 = daPy_HIO_cutTurn_c0::m.field_0xC;
    } else {
        fVar1 = daPy_HIO_cutTurn_c0::m.field_0x8;
    }
    if (mEquipItem == daPyItem_SWORD_e) {
        setSingleMoveAnime(
            ANM_CUTTURN,
            daPy_HIO_cutTurn_c0::m.field_0x4,
            fVar1,
            daPy_HIO_cutTurn_c0::m.field_0x0,
            daPy_HIO_cutTurn_c0::m.field_0x28
        );
    } else {
        setSingleMoveAnime(
            ANM_CUTTURNC,
            daPy_HIO_cutTurn_c0::m.field_0x4,
            fVar1,
            daPy_HIO_cutTurn_c0::m.field_0x0,
            daPy_HIO_cutTurn_c0::m.field_0x28
        );
    }
    if (mEquipItem == daPyItem_SWORD_e) {
        if (checkNormalSwordEquip()) {
            mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTTURNA));
        } else {
            mSwordAnim.changeBckOnly(getItemAnimeResource(LKANM_BCK_CUTTURNMS));
        }
        if (checkNormalSwordEquip()) {
            m35A4 = daPy_HIO_cutTurn_c0::m.field_0x40;
            if (checkNoResetFlg1(daPyFlg1_UNK8000)) {
                mAtCyl.SetAtAtp(4);
            } else {
                mAtCyl.SetAtAtp(2);
            }
        } else {
            m35A4 = daPy_HIO_cutTurn_c0::m.field_0x44;
            if (checkNoResetFlg1(daPyFlg1_UNK8000)) {
                mAtCyl.SetAtAtp(8);
            } else {
                mAtCyl.SetAtAtp(4);
            }
        }
        setBlurPosResource(LKANM__CUTTURN_POS);
    } else {
        daBoko_c* boko = (daBoko_c*)mActorKeepEquip.getActor();
        u32 uVar5;
        if (boko == NULL) {
            uVar5 = 0;
            mAtCyl.SetAtAtp(1);
        } else {
            uVar5 = fopAcM_GetParam(boko);
            mAtCyl.SetAtAtp(boko->getAtPoint());
        }
        if (uVar5 == 0) {
            m35A4 = daPy_HIO_cutTurn_c0::m.field_0x60;
        } else if (uVar5 == 1) {
            m35A4 = daPy_HIO_cutTurn_c0::m.field_0x64;
        } else if (uVar5 == 2) {
            m35A4 = daPy_HIO_cutTurn_c0::m.field_0x68;
        } else if (uVar5 == 3) {
            m35A4 = daPy_HIO_cutTurn_c0::m.field_0x6C;
        } else if (uVar5 == 4) {
            m35A4 = daPy_HIO_cutTurn_c0::m.field_0x70;
        } else {
            m35A4 = daPy_HIO_cutTurn_c0::m.field_0x74;
        }
        setBlurPosResource(LKANM__WEAPONTURN_POS);
    }
    mAtCyl.SetR(m35A4 * 0.5f);
    m35EC = fVar1;
    m3700 = cXyz::Zero;
    m34C2 = 1;
    m34D0 = daPy_HIO_cutTurn_c0::m.field_0x2;
    current.angle.y = shape_angle.y;
    m3578 = 0;
    voiceStart(1);
    dComIfGp_setPlayerStatus0(0, daPyStts0_SWORD_SWING_e);
    mCutType = 8;
    offResetFlg0(daPyRFlg0_UNK8000000);
    mAtCyl.SetR(m35A4 * 0.5f);
    if (!checkNoResetFlg0(daPyFlg0_UNK80000000)) {
        m32E4.makeEmitter(dPa_name::ID_COMMON_001E, mpCLModel->getAnmMtx(0x28), &current.pos, NULL);
        if (mCurrAttributeCode == dBgS_Attr_GRASS_e) {
            GXColor color = {tevStr.mColorC0.r, tevStr.mColorC0.g, tevStr.mColorC0.b, tevStr.mColorC0.a};
            m32F0.makeEmitterColor(
                dPa_name::ID_COMMON_0021, mpCLModel->getAnmMtx(0x23), &current.pos, &color, &tevStr.mColorK0
            );
            m35A0 = 18.0f;
        } else if (mCurrAttributeCode == dBgS_Attr_WATER_e) {
            GXColor amb, dif;
            dKy_get_seacolor(&amb, &dif);
            m32F0.makeEmitterColor(dPa_name::ID_COMMON_0020, mpCLModel->getAnmMtx(0x23), &current.pos, &amb, NULL);
            m35A0 = 17.0f;
        } else {
            dComIfGp_particle_setToonP1(
                dPa_name::ID_COMMON_201F,
                &current.pos,
                NULL,
                NULL,
                daPy_HIO_basic_c0::m.field_0x2,
                &mSmokeEcallBack,
                -1,
                NULL,
                NULL,
                NULL
            );
            m35A0 = 21.0f;
        }
    }
    mProcVar0.m3570 = 0;
    if (m34C4 == 6) {
        onNoResetFlg0(daPyFlg0_UNK4);
        mProcVar0.m3570 = 1;
    } else {
        mCutCount = 0;
    }
    mVelocity = 0.0f;
    m34C4 = 0;
    endFlameDamageEmitter();
    return true;
}

/* 80158220-80158460       .text procCutTurn__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurn() {
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if ((mProcVar0.m3570 != 0 && swordButton()) && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }

    if (frameCtrl.getRate() < 0.01f) {
        if (m34D0 > 0) {
            m34D0--;
        } else {
            mDirection = DIR_RIGHT;
            checkNextMode(0);
            return true;
        }
    } else if (frameCtrl.getFrame() > daPy_HIO_cutTurn_c0::m.field_0x10) {
        u8 orig_direction = mDirection;
        mDirection = DIR_RIGHT;
        if (checkNextMode(1)) {
            return true;
        }
        mDirection = orig_direction;
    } else if (frameCtrl.getFrame() > 17.0f) {
        m32E4.end();
    }

    if (frameCtrl.getFrame() > m35A0) {
        m32F0.end();
        mSmokeEcallBack.end();
    }
    setSpecialBattle(1);
    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }

    if (frameCtrl.getFrame() >= daPy_HIO_cutTurn_c0::m.field_0x30 &&
        frameCtrl.getFrame() < daPy_HIO_cutTurn_c0::m.field_0x34)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_KAITENGIRI);
        }
        onResetFlg0(daPyRFlg0_UNK2);
        cLib_chaseF(mAtCyl.GetRP(), m35A4, 18.0f);
    }

    if (frameCtrl.checkPass(daPy_HIO_cutTurn_c0::m.field_0x34)) {
        m331C.setAlpha(0x80);
        m332C.setAlpha(0x80);
        m333C.setAlpha(0x80);
    } else if (m331C.getAlpha() == 0x80) {
        m331C.setAlpha(0x00);
        m332C.setAlpha(0x00);
        m333C.setAlpha(0x00);
    }
    m34C2 = 1;
    return true;
}

/* 80158460-801585D8       .text procCutRoll_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutRoll_init() {
    commonProcInit(daPyProc_CUT_ROLL_e);
    setSingleMoveAnime(
        ANM_CUTTURNB,
        daPy_HIO_cutRoll_c0::m.field_0x8,
        daPy_HIO_cutRoll_c0::m.field_0xC,
        daPy_HIO_cutRoll_c0::m.field_0x0,
        daPy_HIO_cutRoll_c0::m.field_0x10
    );
    m3578 = 0;
    seStartMapInfo(JA_SE_LK_V_KAITEN_S);
    dComIfGp_setItemMagicCount(-2);
    mCutType = 9;
    mCutCount = 0;
    offResetFlg0(daPyRFlg0_UNK8000000);
    if (checkNormalSwordEquip()) {
        m35A4 = daPy_HIO_cutRoll_c0::m.field_0x20;
        if (checkNoResetFlg1(daPyFlg1_UNK8000)) {
            mAtCyl.SetAtAtp(4);
        } else {
            mAtCyl.SetAtAtp(2);
        }
    } else {
        m35A4 = daPy_HIO_cutRoll_c0::m.field_0x24;
        if (checkNoResetFlg1(daPyFlg1_UNK8000)) {
            mAtCyl.SetAtAtp(8);
        } else {
            mAtCyl.SetAtAtp(4);
        }
    }
    mAtCyl.SetR(m35A4 * 0.5f);
    m34D0 = daPy_HIO_cutRoll_c0::m.field_0x2;
    current.angle.y = shape_angle.y;
    m34BE = 4;
    dComIfGp_setPlayerStatus0(0, daPyStts0_SPIN_ATTACK_e);
    endFlameDamageEmitter();
    return true;
}

/* 801585D8-801588F0       .text procCutRoll__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutRoll() {
    s16 uVar1;
    f32 fVar2;
    s16 sVar3;
    cXyz local_48;
    cXyz local_3c;

    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        uVar1 = current.angle.y;
        if (mAcch.ChkWallHit() && (mDemo.getDemoMode() != daPy_demo_c::DEMO_UNK2B_e)) {
            fVar2 = 25.0f + mAcchCir[0].GetWallR();
            local_48.set(current.pos.x, current.pos.y + mAcchCir[0].GetWallH(), current.pos.z);
            f32 cos = cM_scos(uVar1);
            f32 sin = cM_ssin(uVar1);
            local_3c.x = local_48.x + fVar2 * sin;
            local_3c.y = local_48.y;
            local_3c.z = local_48.z + fVar2 * cos;
            mLinkLinChk.Set(&local_48, &local_3c, this);
            if (dComIfG_Bgsp()->LineCross(&mLinkLinChk)) {
                cM3dGPla* triPla = dComIfG_Bgsp()->GetTriPla(mLinkLinChk);
                shape_angle.y = cM_atan2s(-triPla->GetNP()->x, -triPla->GetNP()->z);
                current.angle.y = shape_angle.y;
                return procFrontRollCrash_init();
            }
        }
        if (mStickDistance > 0.05f) {
            cLib_addCalcAngleS(
                &current.angle.y,
                m34E8,
                daPy_HIO_move_c0::m.field_0x6,
                daPy_HIO_move_c0::m.field_0x0,
                daPy_HIO_move_c0::m.field_0x4
            );
            shape_angle.y = current.angle.y;
        }
        sVar3 = current.angle.y - uVar1;
        if (dComIfGp_event_runCheck() != 0) {
            if (mDemo.getDemoMode() != daPy_demo_c::DEMO_UNK2B_e) {
                m34D0 = 0;
            } else {
                m34D0 = 5;
            }
        }
        if (m34D0 > 0) {
            m34D0--;
            mVelocity = daPy_HIO_cutRoll_c0::m.field_0x14;
            m34EC -= daPy_HIO_cutRoll_c0::m.field_0x4 + sVar3;
            if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
                onResetFlg0(daPyRFlg0_UNK1);
            }
            onResetFlg0(daPyRFlg0_UNK2);
            cLib_chaseF(mAtCyl.GetRP(), m35A4, 18.0f);
            seStartMapInfo(JA_SE_LK_V_KAITEN_S);
        } else if (cLib_addCalc(&mVelocity, 0.0f, 0.1f, 2.5f, 1.0f) < 0.5f) {
            shape_angle.y = shape_angle.y + m34EC;
            current.angle.y = shape_angle.y;
            if (dComIfGp_event_runCheck() != 0 && (mDemo.getDemoMode() != daPy_demo_c::DEMO_UNK2B_e)) {
                procWait_init();
            } else {
                procCutRollEnd_init();
            }
        } else {
            f32 f2 = -0x200 + daPy_HIO_cutRoll_c0::m.field_0x4 + sVar3;
            m34EC -= (0x200 + (f2 * (mVelocity / daPy_HIO_cutRoll_c0::m.field_0x14)));
        }
    } else {
        seStartMapInfo(JA_SE_LK_V_KAITEN_S);
    }
    return true;
}

/* 801588F0-80158A40       .text procCutRollEnd_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutRollEnd_init() {
    commonProcInit(daPyProc_CUT_ROLL_END_e);
    setSingleMoveAnime(ANM_WAITQ, daPy_HIO_move_c0::m.field_0x84, 0.0f, -1, daPy_HIO_basic_c0::m.field_0xC);
    mVelocity = 0.0f;
    current.angle.y = shape_angle.y;
    m34D0 = daPy_HIO_cutRoll_c0::m.field_0x6;
    static JGeometry::TVec3<f32> emitter_trans(0.0f, 55.0f, 0.0f);
    static JGeometry::TVec3<f32> particle_scale(0.76f, 0.76f, 0.76f);
    JPABaseEmitter* emitter =
        m33A8.makeEmitter(dPa_name::ID_COMMON_STARS_SPIN, mpCLModel->getAnmMtx(15), &current.pos, NULL);
    if (emitter != NULL) {
        emitter->becomeImmortalEmitter();
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
    if (m34D0 > 0) {
        m34D0--;
    } else {
        checkNextMode(0);
    }
    return true;
}

/* 80158A98-80158B00       .text procCutTurnCharge_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnCharge_init() {
    commonProcInit(daPyProc_CUT_TURN_CHARGE_e);
    setSingleMoveAnime(
        ANM_CUTTURNP,
        daPy_HIO_cutTurnR_c0::m.field_0xC,
        daPy_HIO_cutTurnR_c0::m.field_0x10,
        daPy_HIO_cutTurnR_c0::m.field_0x4,
        daPy_HIO_cutTurnR_c0::m.field_0x14
    );
    mVelocity = 0.0f;
    current.angle.y = shape_angle.y;
    return true;
}

/* 80158B00-80158B58       .text procCutTurnCharge__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnCharge() {
    if (!swordButton() || daPy_dmEcallBack_c::checkCurse()) {
        checkNextMode(0);
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        procCutTurnMove_init();
    }
    return true;
}

/* 80158B58-80158D40       .text procCutTurnMove_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnMove_init() {
    static Vec eff_scale = {1.5f, 1.5f, 1.5f};
    BOOL bVar1;
    cXyz* pcVar4;

    commonProcInit(daPyProc_CUT_TURN_MOVE_e);
    setSingleMoveAnime(ANM_CUTTURNPWFB, 0.0f, 0.0f, -1, daPy_HIO_cutTurnR_c0::m.field_0x1C);
    if (mEquipItem == daPyItem_BOKO_e && (mAnmRatioUpper[UPPER_MOVE0_e].getAnmTransform() != NULL)) {
        mFrameCtrlUpper[UPPER_MOVE0_e].setFrame(mFrameCtrlUpper[UPPER_MOVE0_e].getEnd() - 0.001f);
        mAnmRatioUpper[UPPER_MOVE0_e].getAnmTransform()->setFrame(mFrameCtrlUpper[UPPER_MOVE0_e].getFrame());
    }
    m3598 = 1.0f;
    mDirection = DIR_FORWARD;

    if (dComIfGs_isEventBit(0xb20)) {
        bVar1 = true;
    } else if (dComIfGs_isTmpBit(0x402)) {
        bVar1 = true;
    } else {
        bVar1 = false;
    }

    if (bVar1 && mEquipItem == daPyItem_SWORD_e && dComIfGs_getMagic() >= 2 && !checkSwordMiniGame() &&
        dComIfGp_getMiniGameType() != 6)
    {
        pcVar4 = checkNormalSwordEquip() ? NULL : (cXyz*)&eff_scale;
        m32E4.makeEmitter(dPa_name::ID_COMMON_0029, mpCLModel->getAnmMtx(8), &current.pos, pcVar4);
        m32F0.makeEmitter(dPa_name::ID_COMMON_002A, mpCLModel->getAnmMtx(8), &current.pos, pcVar4);
        m34D0 = 0x2f;
    } else {
        m34D0 = -1;
    }

    dComIfGp_setPlayerStatus0(0, daPyStts0_SPIN_ATTACK_e);
    return true;
}

/* 80158D40-80159130       .text procCutTurnMove__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutTurnMove() {
    setShapeAngleToAtnActor();
    m34E6 = shape_angle.y;
    if (0 < m34D0) {
        m34D0--;
        if (m34D0 == 0) {
            dComIfGp_setPlayerStatus1(0, daPyStts1_UNK20000_e);
        }
    }
    if (m34D0 != -1) {
        mDoAud_seStart(JA_SE_LK_SWORD_CHARGE);
    }
    if (changeSlideProc()) {
        return true;
    }

    if (daPy_dmEcallBack_c::checkCurse()) {
        checkNextMode(0);
    } else if (swordButton()) {
        f32 dVar8 = 0.0f;
        if (mStickDistance > 0.05f) {
            int direction = getDirectionFromAngle(m34E8 - m34E6);
            daPy_ANM dVar6 = (daPy_ANM)0xffff;
            cLib_addCalcAngleS(&current.angle.y, m34E8, 4, 12000, 0x2000);
            f32 in_f30;
            if (mDirection == DIR_FORWARD || mDirection == DIR_BACKWARD) {
                if (direction == DIR_LEFT || direction == DIR_RIGHT) {
                    dVar6 = ANM_CUTTURNPWLR;
                    in_f30 = daPy_HIO_cutTurnR_c0::m.field_0x24;
                    mVelocity *= 0.5f;
                } else if (mDirection != direction) {
                    mVelocity *= 0.5f;
                }
            } else if (direction == DIR_FORWARD || direction == DIR_BACKWARD) {
                dVar6 = ANM_CUTTURNPWFB;
                in_f30 = daPy_HIO_cutTurnR_c0::m.field_0x1C;
                mVelocity *= 0.5f;
            } else if (mDirection != direction) {
                mVelocity *= 0.5f;
            }
            if (mDirection == direction) {
                dVar8 = daPy_HIO_move_c0::m.field_0x14 * mStickDistance;
            } else {
                mDirection = direction;
            }
            if (dVar6 != (daPy_ANM)0xffff) {
                setSingleMoveAnime(dVar6, 0.0f, 0.0f, -1, in_f30);
            }
        }
        setNormalSpeedF(dVar8, 0.5f, 2.0f, 0.25f);
        if (mDirection == DIR_FORWARD) {
            dVar8 = daPy_HIO_cutTurnR_c0::m.field_0x18;
        } else if (mDirection == DIR_BACKWARD) {
            dVar8 = -daPy_HIO_cutTurnR_c0::m.field_0x18;
        } else if (mDirection == DIR_RIGHT) {
            dVar8 = -daPy_HIO_cutTurnR_c0::m.field_0x20;
        } else { // DIR_LEFT
            dVar8 = daPy_HIO_cutTurnR_c0::m.field_0x20;
        }
        f32 dVar7 = mVelocity / mMaxNormalSpeed;
        mFrameCtrlUnder[UNDER_MOVE0_e].setRate(dVar7 * dVar8);
        if (dVar8 >= 0.0f) {
            mFrameCtrlUnder[UNDER_MOVE0_e].setLoop(mFrameCtrlUnder[UNDER_MOVE0_e].getStart());
        } else {
            mFrameCtrlUnder[UNDER_MOVE0_e].setLoop(mFrameCtrlUnder[UNDER_MOVE0_e].getEnd());
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
        if (mEquipItem == daPyItem_BOKO_e && (mAnmRatioUpper[UPPER_MOVE0_e].getAnmTransform() != (J3DAnmTransform*)0x0))
        {
            mFrameCtrlUpper[UPPER_MOVE0_e].setFrame(mFrameCtrlUpper[UPPER_MOVE0_e].getEnd() - 0.001f);
            mAnmRatioUpper[UPPER_MOVE0_e].getAnmTransform()->setFrame(mFrameCtrlUpper[UPPER_MOVE0_e].getFrame());
        }
    } else if (m34D0 == 0) {
        procCutRoll_init();
    } else {
        mVelocity = speedF;
        procCutTurn_init(0);
    }

    return true;
}

/* 80159130-801592A4       .text procCutReverse_init__9daPy_lk_cFQ29daPy_lk_c8daPy_ANM */
BOOL daPy_lk_c::procCutReverse_init(daPy_ANM param_0) {
    dComIfGp_getVibration().StartShock(4, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    if (param_0 == ANM_JATTACK) {
        return true;
    }

    BOOL uVar2 = checkNoResetFlg0(daPyFlg0_UNK4) ? TRUE : FALSE;
    commonProcInit(daPyProc_CUT_REVERSE_e);
    if (uVar2 != 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    }
    setSingleMoveAnime(
        param_0,
        daPy_HIO_cut_c0::m.field_0x2C,
        daPy_HIO_cut_c0::m.field_0x30,
        daPy_HIO_cut_c0::m.field_0x6,
        daPy_HIO_cut_c0::m.field_0x38
    );
    mVelocity = 12.0f;
    current.angle.y = shape_angle.y + 0x8000;
    m3522 = 0;
    voiceStart(37);
    if (mCurrAttributeCode == dBgS_Attr_ICE_e && !checkHeavyStateOn()) {
        m36A0.x += 10.0f * cM_ssin(current.angle.y);
        m36A0.z += 10.0f * cM_scos(current.angle.y);
    }

    return true;
}

/* 801592A4-80159390       .text procCutReverse__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutReverse() {
    cLib_addCalc(
        &mVelocity,
        0.0f,
        daPy_HIO_guard_c0::m.field_0x18,
        daPy_HIO_guard_c0::m.field_0x1C,
        daPy_HIO_guard_c0::m.field_0x20
    );
    if (swordButton() && mEquipItem == daPyItem_SWORD_e) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        current.angle.y = shape_angle.y;
        checkNextMode(0);
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_cut_c0::m.field_0x34) {
        current.angle.y = shape_angle.y;
        if (!checkNextMode(1)) {
            current.angle.y = shape_angle.y + 0x8000;
        }
    }
    return true;
}

/* 80159390-80159500       .text procJumpCut_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procJumpCut_init(int param_0) {
    fopAc_ac_c* equip_actor = mActorKeepEquip.getActor();
    if (daPy_dmEcallBack_c::checkCurse() || (mEquipItem == daPyItem_BOKO_e && equip_actor == NULL)) {
        return false;
    }

    commonProcInit(daPyProc_JUMP_CUT_e);
    if (param_0 != 0) {
        setSingleMoveAnime(
            ANM_JATTACK,
            daPy_HIO_cutJump_c0::m.field_0x20,
            daPy_HIO_cutJump_c0::m.field_0x24,
            daPy_HIO_cutJump_c0::m.field_0x6,
            daPy_HIO_cutJump_c0::m.field_0x28
        );
        mVelocity = daPy_HIO_cutJump_c0::m.field_0x2C;
        speed.y = daPy_HIO_cutJump_c0::m.field_0x30;
        gravity = daPy_HIO_cutJump_c0::m.field_0x34;
    } else {
        setSingleMoveAnime(
            ANM_JATTACK,
            daPy_HIO_cutJump_c0::m.field_0x8,
            daPy_HIO_cutJump_c0::m.field_0xC,
            daPy_HIO_cutJump_c0::m.field_0x0,
            daPy_HIO_cutJump_c0::m.field_0x10
        );
        mVelocity = daPy_HIO_cutJump_c0::m.field_0x14;
        speed.y = daPy_HIO_cutJump_c0::m.field_0x18;
        gravity = daPy_HIO_cutJump_c0::m.field_0x1C;
    }
    current.angle.y = shape_angle.y;
    mProcVar0.m3570 = 0;
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

/* 80159500-80159608       .text procJumpCut__9daPy_lk_cFv */
BOOL daPy_lk_c::procJumpCut() {
    if (mAcch.ChkGroundHit()) {
        return procJumpCutLand_init();
    }

    if (current.angle.y == shape_angle.y && changeCutReverseProc(ANM_JATTACK)) {
        current.angle.y = current.angle.y + 0x8000;
        mVelocity = 27.0f;
    } else if (current.angle.y != shape_angle.y) {
        cLib_addCalc(&mVelocity, 5.0f, 0.2f, 1.0f, 0.1f);
    }
    if ((mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= daPy_HIO_cutJump_c0::m.field_0x48) &&
        (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() < daPy_HIO_cutJump_c0::m.field_0x4C))
    {
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

/* 80159608-80159864       .text procJumpCutLand_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procJumpCutLand_init() {
    f32 dVar3 = m35F0 - current.pos.y;
    commonProcInit(daPyProc_JUMP_CUT_LAND_e);
    if (!dComIfGp_event_runCheck()) {
        if (dVar3 >= (100.0f * daPy_HIO_fall_c0::m.field_0x10)) {
            setDamagePoint(-2.0f);
        } else if (dVar3 >= (100.0f * daPy_HIO_fall_c0::m.field_0x14)) {
            setDamagePoint(-1.0f);
        }
        if (dVar3 >= (100.0f * daPy_HIO_fall_c0::m.field_0x14)) {
            mDamageWaitTimer = daPy_HIO_dam_c0::m.field_0x0;
            onModeFlg(ModeFlg_DAMAGE);
        }
    }
    mVelocity = 0.0f;
    setSingleMoveAnime(
        ANM_JATTACKLAND,
        daPy_HIO_cutJump_c0::m.field_0x38,
        daPy_HIO_cutJump_c0::m.field_0x3C,
        daPy_HIO_cutJump_c0::m.field_0x2,
        daPy_HIO_cutJump_c0::m.field_0x40
    );
    if (mEquipItem == daPyItem_NONE_e) {
        mProcVar0.m3570 = 0;
    } else {
        onResetFlg0(daPyRFlg0_UNK2);
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
            mSwBlur.initSwBlur(
                mpCLModel->getBaseTRMtx(),
                (10.0f * daPy_HIO_cutJump_c0::m.field_0x48),
                getBlurTopRate(),
                getSwordBlurColor()
            );
            onNoResetFlg0(daPyFlg0_CUT_AT_FLG);
        }
        setJumpCutAtParam();
        mProcVar0.m3570 = 1;
    }
    m34D0 = daPy_HIO_cutJump_c0::m.field_0x4;
    current.angle.y = shape_angle.y + 0x8000;
    m34BE = 3;
    onResetFlg0(daPyRFlg0_RIGHT_FOOT_ON_GROUND);
    onResetFlg0(daPyRFlg0_LEFT_FOOT_ON_GROUND);
    if (mEquipItem == dItem_SKULL_HAMMER_e) {
        setHammerQuake(NULL, NULL, -1);
    } else if (checkHeavyStateOn()) {
        dComIfGp_getVibration().StartShock(5, -0x31, cXyz(0.0f, 1.0f, 0.0f));
    }
    return true;
}

/* 80159864-80159998       .text procJumpCutLand__9daPy_lk_cFv */
BOOL daPy_lk_c::procJumpCutLand() {
    current.angle.y = shape_angle.y;
    resetFootEffect();
    if (mProcVar0.m3570 != 0 && changeCutReverseProc(ANM_CUTRER)) {
        return true;
    }

    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (m34D0 > 0) {
            m34D0--;
            checkNextMode(1);
        } else {
            checkNextMode(0);
        }
    } else if (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() > daPy_HIO_cutJump_c0::m.field_0x44) {
        checkNextMode(1);
    } else if (mProcVar0.m3570 != 0) {
        mProcVar0.m3570 = 0;
        if (abs(m3578) > 0xf800 && !daPy_dmEcallBack_c::checkCurse() &&
            (mEquipItem == daPyItem_SWORD_e || mEquipItem == daPyItem_BOKO_e))
        {
            procCutTurn_init(1);
        } else {
            onResetFlg0(daPyRFlg0_UNK2);
        }
    }
    return true;
}

/* 80159998-80159B80       .text procCutExMJ_init__9daPy_lk_cFi */
BOOL daPy_lk_c::procCutExMJ_init(int param_0) {
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
        dVar3,
        daPy_HIO_cutExMJ_c0::m.field_0x4,
        daPy_HIO_cutExMJ_c0::m.field_0x8,
        daPy_HIO_cutExMJ_c0::m.field_0x0,
        daPy_HIO_cutExMJ_c0::m.field_0xC
    );
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
    m35EC = mFrameCtrlUnder[UNDER_MOVE0_e].getFrame();
    if (swordButton() && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    if (m34C4 != 0) {
        m3522 = daPy_HIO_cutExMJ_c0::m.field_0x2;
    }
    if (mFrameCtrlUnder[UNDER_MOVE0_e].getRate() < 0.01f) {
        if (m34D4 == 0) {
            m34D4 = 1;
        } else if (m34D4 == 1) {
            setSingleMoveAnime(ANM_JMPEDS, 0.0f, 0.0f, -1, daPy_HIO_cutExMJ_c0::m.field_0x1C);
            offModeFlg(ModeFlg_00000400);
            setTextureAnime(0x37, 0);
            resetSeAnime();
            m34D4 = 2;
        }
        if (m34D6 == 0x71) {
            if (!(m34EC > 0) || m34EC > 0x4000) {
                m34EC -= 0x1800;
            } else {
                cLib_addCalcAngleS(&m34EC, 1, 2, 0x1800, 0x800);
            }
        } else if (!(m34EC < 0) || m34EC < -0x4000) {
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
    setSpecialBattle(TRUE);
    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }

    if (m34C4 != 0 && (swordTrigger() && m34C5 != 5)) {
        m34C5 = 30;
    }
    if (speed.y < -gravity) {
        gravity = daPy_HIO_cutExMJ_c0::m.field_0x18;
    }
    setFallVoice();
    if (m34D4 != 2 && (mFrameCtrlUnder[UNDER_MOVE0_e].getFrame() >= m35A0)) {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    if (current.pos.y < m3688.y - 200.0f) {
        cLib_chaseF(&mVelocity, 0.0f, (0.1f * daPy_HIO_autoJump_c0::m.field_0x3C));
    }
    return true;
}

/* 80159E60-80159FB0       .text procCutKesa_init__9daPy_lk_cFv */
BOOL daPy_lk_c::procCutKesa_init() {
    commonProcInit(daPyProc_CUT_KESA_e);
    setSingleMoveAnime(
        ANM_CUTKESA,
        daPy_HIO_cutKesa_c0::m.field_0x4,
        daPy_HIO_cutKesa_c0::m.field_0x8,
        daPy_HIO_cutKesa_c0::m.field_0x0,
        daPy_HIO_cutKesa_c0::m.field_0xC
    );
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
    J3DFrameCtrl& frameCtrl = mFrameCtrlUnder[UNDER_MOVE0_e];
    m35EC = frameCtrl.getFrame();
    if (swordButton() && m34C5 == 0) {
        onNoResetFlg0(daPyFlg0_UNK4);
    } else {
        offNoResetFlg0(daPyFlg0_UNK4);
    }
    m3522 = daPy_HIO_cutKesa_c0::m.field_0x2;
    if (frameCtrl.getRate() < 0.01f) {
        mVelocity = 0.0f;
        checkNextMode(0);
        return true;
    }

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
    }

    setSpecialBattle(TRUE);
    if (doTrigger() && dComIfGp_getDoStatus() == dActStts_PARRY_e) {
        return changeSpecialBattle();
    }
    if (swordTrigger() && m34C5 != 5) {
        m34C5 = 31;
    }
    if (mpAttnActorLockOn != NULL) {
        setShapeAngleToAtnActor();
        current.angle.y = shape_angle.y;
    }
    if (frameCtrl.getFrame() >= daPy_HIO_cutKesa_c0::m.field_0x10 &&
        frameCtrl.getFrame() < daPy_HIO_cutKesa_c0::m.field_0x14)
    {
        if (!checkNoResetFlg0(daPyFlg0_CUT_AT_FLG)) {
            onResetFlg0(daPyRFlg0_UNK1);
            seStartSwordCut(JA_SE_LK_SW_KAZEKIRI_S);
        }
        onResetFlg0(daPyRFlg0_UNK2);
    }
    m34C2 = 1;
    cLib_addCalc(
        &mVelocity,
        0.0f,
        daPy_HIO_cutEA_c0::m.field_0x1C,
        daPy_HIO_cutEA_c0::m.field_0x14,
        daPy_HIO_cutEA_c0::m.field_0x18
    );

    return true;
}
