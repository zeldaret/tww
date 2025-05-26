/**
 * d_a_player_particle.inc
 *
 * Code relating to various particle effects.
 *
 * This file is not a standalone translation unit and is instead directly
 * included into d_a_player_main.cpp.
 *
 * The original name of this file is not known, but a best guess was taken
 * based on the original names of the functions it contains.
 */

#include "d/actor/d_a_player_main.h"
#include "d/actor/d_a_player_main_data.h"
#include "d/actor/d_a_player_HIO.h"
#include "d/actor/d_a_sea.h"
#include "d/actor/d_a_ship.h"
#include "d/d_procname.h"
#include "f_op/f_op_kankyo_mng.h"
#include "m_Do/m_Do_lib.h"
#include "SSystem/SComponent/c_math.h"

#include "assets/l_sightDL__d_a_player_main.h"

/* 8012901C-80129034       .text setup__24daPy_swimTailEcallBack_cFP14JPABaseEmitterPC4cXyzPC5csXyzSc */
void daPy_swimTailEcallBack_c::setup(JPABaseEmitter* emitter, const cXyz* pos, const csXyz* angle, s8) {
    mpEmitter = emitter;
    field_0x04 = false;
    field_0x20 = angle;
    field_0x05 = false;
}

/* 80129034-801290D8       .text getMaxWaterY__24daPy_swimTailEcallBack_cFPQ29JGeometry8TVec3<f> */
void daPy_swimTailEcallBack_c::getMaxWaterY(JGeometry::TVec3<f32>* pos) {
    if (daSea_ChkArea(pos->x, pos->z)) {
        pos->y = daSea_calcWave(pos->x, pos->z) + 2.0f;
        if (field_0x10 > pos->y) {
            pos->y = field_0x10 + 2.0f;
        }
    } else if (field_0x10 != -G_CM3D_F_INF) {
        pos->y = field_0x10 + 2.0f;
    } else {
        pos->y = field_0x0C;
    }
}

/* 801290D8-8012910C       .text remove__24daPy_swimTailEcallBack_cFv */
void daPy_swimTailEcallBack_c::remove() {
    if (mpEmitter != NULL) {
        mpEmitter->setEmitterCallBackPtr(NULL);
        mpEmitter->becomeInvalidEmitter();
        mpEmitter = NULL;
    }
}

/* 8012910C-80129310       .text execute__24daPy_swimTailEcallBack_cFP14JPABaseEmitter */
void daPy_swimTailEcallBack_c::execute(JPABaseEmitter* emitter) {
    static JGeometry::TVec3<f32> right_dir(-1.0f, 0.0f, 0.0f);

    GXColor ambColor;
    GXColor difColor;
    dKy_get_seacolor(&ambColor, &difColor);
    emitter->setGlobalPrmColor(ambColor.r, ambColor.g, ambColor.b);

    if (field_0x04) {
        s16 sp8 = emitter->getGlobalAlpha();
        cLib_chaseS(&sp8, 0, 0x14);
        emitter->setGlobalAlpha(sp8);
        if (sp8 == 0) {
            emitter->becomeInvalidEmitter();
            emitter->setEmitterCallBackPtr(NULL);
            mpEmitter = NULL;
            return;
        }
    }

    if (field_0x20 != NULL) {
        emitter->setGlobalTranslation(mPos.x, mPos.y, mPos.z);
        JGeometry::TVec3<s16> rot(0, 0, 0);
        rot.y = field_0x20->y;
        emitter->setGlobalRotation(rot);
    }else {
        JGeometry::TVec3<f32> sp20;
        emitter->getGlobalTranslation(sp20);
        getMaxWaterY(&sp20);
        emitter->setGlobalTranslation(sp20);
        cLib_chaseF(&field_0x08, 0.0f, 0.08f);
    }

    emitter->setDirectionalSpeed(1.0f + 12.0f * field_0x08);

    if (field_0x05) {
        emitter->setDirection(right_dir);
    }

    for (JSULink<JPABaseParticle>* link = emitter->getParticleList()->getFirst(); link != NULL;) {
        JSULink<JPABaseParticle>* nextLink = link->getNext();
        JPABaseParticle* particle = link->getObject();

        JGeometry::TVec3<f32> offsetPos;
        particle->getOffsetPosition(offsetPos);
        getMaxWaterY(&offsetPos);
        particle->setOffsetPosition(offsetPos);

        link = nextLink;
    }
}

/* 80129310-80129348       .text draw__24daPy_swimTailEcallBack_cFP14JPABaseEmitter */
void daPy_swimTailEcallBack_c::draw(JPABaseEmitter*) {
    if (dPa_control_c::isStatus(0x01)) {
        GXSetZMode(GX_FALSE, GX_NEVER, GX_FALSE);
    }
}

/* 80129348-8012952C       .text draw__18daPy_sightPacket_cFv */
void daPy_sightPacket_c::draw() {
    j3dSys.reinitGX();
    GXSetNumIndStages(0);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_S8, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_U8, 0);

    GXTexObj texObj;
    GXColor color;
    if (mLockFlag) {
        GXInitTexObj(&texObj, mpLockTex, mpImg->width, mpImg->height, (GXTexFmt)mpImg->format, (GXTexWrapMode)mpImg->wrapS, (GXTexWrapMode)mpImg->wrapT, (mpImg->mipmapCount > 1) ? GX_TRUE : GX_FALSE);

        color.r = 0xFF;
        color.g = 0xFF;
        color.b = 0x32;
        color.a = mLockAlpha;
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevColor(GX_TEVREG1, color);
    } else {
        GXInitTexObj(&texObj, mpSightTex, 0x80, 0x80, GX_TF_I4, GX_CLAMP, GX_CLAMP, GX_FALSE);

        color.r = 0xFF;
        color.g = 0x00;
        color.b = 0x00;
        color.a = 0xFF;
        GXSetTevColor(GX_TEVREG0, color);
        GXSetTevColor(GX_TEVREG1, color);
    }

    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);
    GXLoadPosMtxImm(mMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXCallDisplayList(&l_sightDL, sizeof(l_sightDL) - 0x09);
    J3DShape::resetVcdVatCache();
}

/* 8012952C-801296FC       .text setSight__18daPy_sightPacket_cFv */
void daPy_sightPacket_c::setSight() {
    cXyz proj;
    mDoLib_project(&mPos, &proj);
    mDoMtx_stack_c::transS(proj);

    if (mLockFlag) {
        f32 var_f2;
        f32 var_f31;
        if (mFrame < 13) {
            var_f2 = 1.0f - ((s16)mFrame / 13.0f);
            var_f31 = -var_f2;
        } else {
            var_f2 = (mFrame - 13) / 13.0f;
            var_f31 = var_f2;
        }

        mLockAlpha = 150.0f + (30.0f * var_f2);
        f32 temp_f3 = 0.65f + (0.35f * var_f2);

        mDoMtx_stack_c::scaleM(temp_f3 * mpImg->width, temp_f3 * mpImg->height, temp_f3);
        mDoMtx_stack_c::ZrotM(32768.0f * cM_ssin(16384.0f * var_f31));
    } else {
        mDoMtx_stack_c::scaleM(10.0f, 10.0f, 10.0f);
    }

    mDoMtx_copy(mDoMtx_stack_c::get(), mMtx);
    dComIfGd_set2DXlu(this);
}

/* 801296FC-801297F4       .text initSwBlur__13daPy_swBlur_cFPA4_fifi */
void daPy_swBlur_c::initSwBlur(MtxP mtx, int idx, f32 blurTopRate, int blurColorType) {
    int i = idx * 2;

    mBlurTopRate = blurTopRate;
    mBlurColorType = blurColorType;

    mDoMtx_multVec(mtx, mpPosBuffer + i + 0, &field_0x034[0]);
    mDoMtx_multVec(mtx, mpPosBuffer + i + 1, &field_0x304[0]);

    field_0x034[0] += (field_0x034[0] - field_0x304[0]) * mBlurTopRate;
    field_0x034[1] = field_0x034[0];
    field_0x304[1] = field_0x304[0];
    field_0x014 = 0;
    field_0x018 = idx;
    field_0x028.set(mtx[0][3], mtx[1][3], mtx[2][3]);
}

/* 801297F4-80129A78       .text copySwBlur__13daPy_swBlur_cFPA4_fi */
void daPy_swBlur_c::copySwBlur(MtxP mtx, int param_2) {
    int var_r31 = param_2 - field_0x018;
    field_0x018 = param_2;

    int var_r30;
    if (var_r31 > 0) {
        var_r30 = -2;

        if (var_r31 > 60) {
            var_r31 = 60;
        }
    } else if (var_r31 < 0) {
        var_r30 = 2;

        if (var_r31 < -60) {
            var_r31 = 60;
        } else {
            var_r31 = -var_r31;
        }
    } else {
        var_r31 = 10;
        var_r30 = 0;
    }

    for (int i = 59 - var_r31; i >= 0; i--) {
        field_0x034[i + var_r31] = field_0x034[i];
        field_0x304[i + var_r31] = field_0x304[i];
    }

    // Probably fakematch
    f32 var_f31 = 0.0f;
    f32 frac = 1.0f / var_r31;
    int i;
    int buffIdx = field_0x018 * 2;
    cXyz sp50(mtx[0][3], mtx[1][3], mtx[2][3]);
    cXyz sp38 = field_0x028 - sp50;
    field_0x028 = sp50;
    for (i = 0; i < var_r31 && buffIdx >= 0; i++) {
        mDoMtx_multVec(mtx, mpPosBuffer + buffIdx + 0, &field_0x034[i]);
        mDoMtx_multVec(mtx, mpPosBuffer + buffIdx + 1, &field_0x304[i]);

        field_0x034[i] += (field_0x034[i] - field_0x304[i]) * mBlurTopRate;
        field_0x034[i] += sp38 * var_f31;
        field_0x304[i] += sp38 * var_f31;
        var_f31 += frac;
        buffIdx += var_r30;
    }

    field_0x014 += var_r31;
    if (field_0x014 >= 59) {
        field_0x014 = 58;
    }
}

/* 80129A78-80129DD0       .text draw__13daPy_swBlur_cFv */
void daPy_swBlur_c::draw() {
    j3dSys.reinitGX();
    GXSetNumIndStages(0);

    static GXTexObj texObj;
    u16 texWidth = 16;
    u16 texHeight = 4;
    GXTexFmt texFormat = GX_TF_I4;
    GXInitTexObj(&texObj, (u8*)mpTex + mpTex->imageOffset, texWidth, texHeight, texFormat, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&texObj, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(&texObj, GX_TEXMAP0);

    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_CLR_RGBA, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_CLR_RGBA, GX_S16, 8);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetNumChans(0);

    if (mBlurColorType == NORMAL_SLASH_BLUR) {
        // Normal color.
        static GXColor n_color0 = {0xFF, 0xFF, 0xFF, 0x96};
        GXSetTevColor(GX_TEVREG0, n_color0);
    } else if (mBlurColorType == ELIXIR_SOUP_SLASH_BLUR) {
        // Elixir Soup color.
        static GXColor y_color0 = {0xFF, 0xFF, 0x7B, 0x96};
        GXSetTevColor(GX_TEVREG0, y_color0);
    } else {
        // Parrying color.
        static GXColor g_color0 = {0x5A, 0xFF, 0x5A, 0x96};
        GXSetTevColor(GX_TEVREG0, g_color0);
    }

    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_C0);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_A0, GX_CA_TEXA, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXLoadPosMtxImm(j3dSys.getViewMtx(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetBlendMode(GX_BM_BLEND, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_SET);
    GXSetCullMode(GX_CULL_NONE);
    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
    GXSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_GREATER, 0);

    int r30 = 0xFF / ((field_0x014 >> 1) + 1);
    s16 r29 = r30;
    s16 r28 = 0x00;
    GXBegin(GX_QUADS, GX_VTXFMT0, 4 + field_0x014*4);
    for (int i = field_0x014; i >= 0; i--) {
        GXPosition3f32(field_0x034[i+0].x, field_0x034[i+0].y, field_0x034[i+0].z);
        GXTexCoord2s16(r29, 0x00);
        GXPosition3f32(field_0x304[i+0].x, field_0x304[i+0].y, field_0x304[i+0].z);
        GXTexCoord2s16(r29, 0xFF);
        GXPosition3f32(field_0x304[i+1].x, field_0x304[i+1].y, field_0x304[i+1].z);
        GXTexCoord2s16(r28, 0xFF);
        GXPosition3f32(field_0x034[i+1].x, field_0x034[i+1].y, field_0x034[i+1].z);
        GXTexCoord2s16(r28, 0x00);
        r28 = r29;
        r29 += r30;
    }
    J3DShape::resetVcdVatCache();
}

/* 80129DD0-80129E9C       .text execute__24daPy_fanSwingEcallBack_cFP14JPABaseEmitter */
void daPy_fanSwingEcallBack_c::execute(JPABaseEmitter* emitter) {
    if (emitter->isEnableDeleteEmitter()) {
        emitter->quitImmortalEmitter();
        emitter->setEmitterCallBackPtr(NULL);
        mpEmitter = NULL;
    } else if (mAlphaOutFlg != FALSE) {
        s16 alpha = emitter->getGlobalAlpha();
        cLib_chaseS(&alpha, 0, 50);
        emitter->setGlobalAlpha(alpha);

        if (alpha == 0) {
            emitter->quitImmortalEmitter();
            emitter->setEmitterCallBackPtr(NULL);
            mpEmitter = NULL;
        }
    }
}

/* 80129E9C-80129F48       .text execute__25daPy_waterDropPcallBack_cFP14JPABaseEmitterP15JPABaseParticle */
void daPy_waterDropPcallBack_c::execute(JPABaseEmitter* emitter, JPABaseParticle* ptcl) {
    if (field_0x4) {
        JGeometry::TVec3<f32> ptclPos;
        ptcl->getGlobalPosition(ptclPos);

        cXyz pos(ptclPos.x, ptclPos.y + 25.0f, ptclPos.z);
        mGndChk.SetPos(&pos);

        pos.y = dComIfG_Bgsp()->GroundCross(&mGndChk);

        if (pos.y > ptclPos.y) {
            fopKyM_create(PROC_WATER_MARK, 1, &pos);
        }
    }
}

/* 80129F48-80129F98       .text execute__22daPy_followEcallBack_cFP14JPABaseEmitter */
void daPy_followEcallBack_c::execute(JPABaseEmitter* emitter) {
    emitter->setGlobalTranslation(mPos.x, mPos.y, mPos.z);
    JGeometry::TVec3<s16> rot(mAngle.x, mAngle.y, mAngle.z);
    emitter->setGlobalRotation(rot);
}

/* 80129F98-80129FA0       .text setup__22daPy_followEcallBack_cFP14JPABaseEmitterPC4cXyzPC5csXyzSc */
void daPy_followEcallBack_c::setup(JPABaseEmitter* emitter, const cXyz*, const csXyz*, s8) {
    mpEmitter = emitter;
}

/* 80129FA0-80129FD4       .text end__22daPy_followEcallBack_cFv */
void daPy_followEcallBack_c::end() {
    if (mpEmitter) {
        mpEmitter->becomeInvalidEmitter();
        mpEmitter->setEmitterCallBackPtr(NULL);
        mpEmitter = NULL;
    }
}

daPy_waterDropPcallBack_c daPy_waterDropEcallBack_c::m_pcallback;

/* 80129FD4-8012A040       .text execute__25daPy_waterDropEcallBack_cFP14JPABaseEmitter */
void daPy_waterDropEcallBack_c::execute(JPABaseEmitter* emitter) {
    daPy_followEcallBack_c::execute(emitter);
    if (emitter->isEnableDeleteEmitter())
        end();
}

/* 8012A040-8012A058       .text setup__25daPy_waterDropEcallBack_cFP14JPABaseEmitterPC4cXyzPC5csXyzSc */
void daPy_waterDropEcallBack_c::setup(JPABaseEmitter* emitter, const cXyz* pos, const csXyz* angle, s8) {
    mpEmitter = emitter;
    mpEmitter->becomeImmortalEmitter();
}

/* 8012A058-8012A0B4       .text end__25daPy_waterDropEcallBack_cFv */
void daPy_waterDropEcallBack_c::end() {
    if (mpEmitter != NULL) {
        mpEmitter->quitImmortalEmitter();
        mpEmitter->deleteAllParticle();
        mpEmitter->setParticleCallBackPtr(NULL);

        daPy_followEcallBack_c::end();
    }
}

/* 8012A0B4-8012A0E0       .text makeEmitterColor__28daPy_mtxPosFollowEcallBack_cFUsPA4_fPC4cXyzPC5csXyzPC8_GXColorPC8_GXColor */
void daPy_mtxPosFollowEcallBack_c::makeEmitterColor(u16 particleID, MtxP mtx, const cXyz* pos, const csXyz* angle, const GXColor* prmColor, const GXColor* envColor) {
    mpAngle = angle;
    daPy_mtxFollowEcallBack_c::makeEmitterColor(particleID, mtx, pos, prmColor, envColor);
}

/* 8012A0E0-8012A160       .text execute__28daPy_mtxPosFollowEcallBack_cFP14JPABaseEmitter */
void daPy_mtxPosFollowEcallBack_c::execute(JPABaseEmitter* emitter) {
    mDoMtx_stack_c::transS(mpMtx[0][3], mpMtx[1][3], mpMtx[2][3]);
    if (mpAngle != NULL) {
        mDoMtx_stack_c::YrotM(mpAngle->y);
    }

    emitter->setGlobalRTMatrix(mDoMtx_stack_c::get());
}

s16 daPy_dmEcallBack_c::m_timer = 0;
u16 daPy_dmEcallBack_c::m_type = 3;

/* 8012A160-8012A288       .text execute__18daPy_dmEcallBack_cFP14JPABaseEmitter */
void daPy_dmEcallBack_c::execute(JPABaseEmitter* emitter) {
    if (checkFlame()) {
        JGeometry::TVec3<f32> pos;
        emitter->getGlobalTranslation(pos);

        emitter->setGlobalTranslation(mpMtx[0][3], mpMtx[1][3], mpMtx[2][3]);

        pos.x = (mpMtx[0][3] - pos.x) * -0.05f;
        pos.z = (mpMtx[2][3] - pos.z) * -0.05f;
        f32 sq = pos.x * pos.x + pos.z * pos.z;

        if (sq > 1.0f) {
            f32 distFrac = 1.0f / std::sqrtf(sq);

            pos.x *= distFrac;
            pos.z *= distFrac;
        }

        emitter->setDirection(JGeometry::TVec3<f32>(pos.x, 0.6f, pos.z));
    } else {
        emitter->setGlobalRTMatrix(mpMtx);
    }
}

/* 8012A288-8012A8D8       .text setAuraEffect__9daPy_lk_cFv */
void daPy_lk_c::setAuraEffect() {
    static const u16 aura_emitter_joint[] = {
        0x0007,
        0x000B,
        0x0008,
        0x000C,
        0x0021,
        0x0026,
        0x0022,
        0x0027,
        0x0000,
        0x000F,
    };
    static const u16 aura_model_joint[] = {
        0x0000,
        0x000F,
        0x0008,
        0x000C,
        0x0021,
        0x0026,
    };

    J3DAnmTevRegKey* curYaura00Brk = mYaura00rBrk.getBrkAnm();
    J3DAnmTevRegKey* curYmgcs00Brk = mYmgcs00Brk.getBrkAnm();
    f32 yauraFrame = curYaura00Brk->getFrame();
    f32 ymgcsFrame = curYmgcs00Brk->getFrame();
    f32 y00BtkFrameMax = mpYaura00Btk->getFrameMax();

    if (checkNoDamageMode()) {
        J3DAnmTevRegKey* pYaura00Brk;
        J3DAnmTevRegKey* pYmgcs00Brk;

        if (checkEquipDragonShield()) {
            if (dComIfGp_event_getMode() == 0) {
                m3548 -= 1;
            }

            if (m3548 == 0) {
                if (dComIfGs_getMagic() != 0) {
                    m3548 = daPy_HIO_magicShield_c0::m.field_0x0;
                    dComIfGp_setItemMagicCount(-1);
                } else {
                    offNoResetFlg1(daPyFlg1_EQUIP_DRAGON_SHIELD);
                }
            }

            pYaura00Brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(l_arcName, LINK_BRK_YAURA00_R));
            pYmgcs00Brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(l_arcName, LINK_BRK_YMGCS00_MS));
        } else {
            if (dComIfGp_event_getMode() == 0) {
                mTinkleShieldTimer -= 1;
            }

            pYaura00Brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(l_arcName, LINK_BRK_YAURA00_G));
            pYmgcs00Brk = static_cast<J3DAnmTevRegKey*>(dComIfG_getObjectRes(l_arcName, LINK_BRK_YMGCS00_TS));
        }

        if (pYaura00Brk != curYaura00Brk) {
            mYaura00rBrk.init(mMagicArmorAuraEntries[0].getModel()->getModelData(), pYaura00Brk, FALSE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            curYaura00Brk = pYaura00Brk;
        }

        if (pYmgcs00Brk != curYmgcs00Brk) {
            mYmgcs00Brk.init(mpYmgcs00Model->getModelData(), pYmgcs00Brk, FALSE, J3DFrameCtrl::EMode_NONE, 1.0f, 0, -1, true, 0);
            curYmgcs00Brk = pYmgcs00Brk;
        }
    }

    if (checkNoDamageMode() && (dComIfGp_event_getMode() == 0 || (eventInfo.checkCommandDoor() && !dComIfGp_event_chkEventFlag(dEvtFlag_TALK_e))) ) {
        if (yauraFrame < 0.01f) {
            for (int idx = 0; idx < (int)ARRAY_SIZE(mMagicArmorAuraEntries); idx++) {
                mMagicArmorAuraEntries[idx].setFrame(cM_rndF(y00BtkFrameMax));
            }
        }

        yauraFrame += 1.0f;
        if (yauraFrame >= curYaura00Brk->getFrameMax()) {
            yauraFrame = curYaura00Brk->getFrameMax() - 0.001f;
        }

        ymgcsFrame += 1.0f;
        if (ymgcsFrame >= curYmgcs00Brk->getFrameMax()) {
            ymgcsFrame = curYmgcs00Brk->getFrameMax() - 0.001f;
        }

        seStartMapInfo(JA_SE_LK_MG_SHELD_USING);
    } else {
        yauraFrame -= 1.0f;
        if (yauraFrame < 0.0f) {
            yauraFrame = 0.0f;
        }

        ymgcsFrame -= 1.0f;
        if (ymgcsFrame < 0.0f) {
            ymgcsFrame = 0.0f;
        }
    }

    mYaura00rBrk.entryFrame(yauraFrame);
    mYmgcs00Brk.entryFrame(ymgcsFrame);
    if (yauraFrame > 0.0f) {
        f32 var_f28, var_f31;
        daPy_aura_c* auraEntry = mMagicArmorAuraEntries;
        if (dComIfGp_checkPlayerStatus0(0, daPyStts0_SHIP_RIDE_e) && dComIfGp_getShipActor() != NULL) {
            var_f31 = 0.0f;
            var_f28 = 1.0f + (std::fabsf(dComIfGp_getShipActor()->speedF) / 15.0f);
            if (var_f28 > 1.5f) {
                var_f28 = 1.5f;
            }
        } else {
            var_f31 = std::fabsf(mVelocity) / daPy_HIO_move_c0::m.field_0x18;
            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }
            var_f28 = 1.0f;
        }

        cXyz localScale = scale * (var_f28 * cM_fcos(M_PI * (0.5f * var_f31)));

        for (int idx = 0; idx < (int)ARRAY_SIZE(mMagicArmorAuraEntries); idx++, auraEntry++) {
            f32 var_f0 = 1.0f + auraEntry->getFrame();
            if (var_f0 >= y00BtkFrameMax) {
                var_f0 -= y00BtkFrameMax;
            }
            auraEntry->setFrame(var_f0);
            auraEntry->getModel()->setBaseTRMtx(mpCLModel->getAnmMtx(aura_model_joint[idx]));

            if (idx == 0) {
                auraEntry->getModel()->setBaseScale(scale * var_f31 * 1.2f);
            } else if (idx != 1) {
                auraEntry->getModel()->setBaseScale(localScale);
            } else {
                auraEntry->getModel()->setBaseScale((scale * (1.0f - (0.3f * var_f31))) * 2.0f);
            }
        }
    }

    if (checkNoDamageMode() || mYmgcs00Brk.getBrkAnm()->getFrame() > 0.0f) {
        mpYmgcs00Model->setBaseTRMtx(mpCLModel->getBaseTRMtx());
        mpYmgcs00Model->calc();
        simpleAnmPlay(mpYmgcs00Btk);
    }
}

/* 8012A8D8-8012B340       .text setWaterRipple__9daPy_lk_cFv */
void daPy_lk_c::setWaterRipple() {
    static Vec waterfall_ripple_scale = {0.75f, 0.75f, 0.75f};
    static JGeometry::TVec3<f32> normal_ripple_scale(1.0f, 1.0f, 1.0f);
    static JGeometry::TVec3<f32> small_ripple_scale(0.4f, 0.4f, 0.4f);
    static const Vec wave_offset = {0.0f, 18.0f, 0.0f};
    static const Vec swim_offset = {0.0f, 30.0f, 0.0f};
    static const Vec swim_side_offset = {0.0f, 0.0f, 30.0f};

    // Probably fakematch
    BOOL var_r3;
    if (mCurProc == daPyProc_DEMO_DEAD_e && dComIfGp_checkPlayerStatus0(0, daPyStts0_SWIM_e)) {
        var_r3 = TRUE;
    } else {
        var_r3 = FALSE;
    }

    // Probably fakematch (May use inlines?)
    if ((var_r3 && m34D6 != 0) ||
        (mCurProc != daPyProc_VOMIT_WAIT_e && !var_r3 && (!checkModeFlg(ModeFlg_IN_SHIP | ModeFlg_HANG) || checkModeFlg(ModeFlg_SWIM)) && ((checkNoResetFlg0(daPyFlg0_UNK80) && m35D0 > 5.0f + mCyl.GetC().y && m35D0 < mCyl.GetC().y + mCyl.GetH()) || (mCurrAttributeCode == dBgS_Attr_WATER_e && mAcch.ChkGroundHit())))
    ) {

        if (m3280.getEmitter() == NULL) {
            dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &current.pos, NULL, NULL, 0xFF, &m3280);
        }

        f32 var_f1 = (0.1f * std::fabsf(getSpeedF()));
        var_f1 *= var_f1;
        if (var_f1 > 1.0f) {
            var_f1 = 1.0f;
        }
        m3280.setRate(var_f1);
        simpleAnmPlay(mpSuimenMunyaBtk);

        JPABaseEmitter* emitter = m3280.getEmitter();
        if (emitter != NULL && ((emitter->mGlobalParticleScale.x < 0.8f && checkNoResetFlg0(daPyFlg0_UNK80)) || (emitter->mGlobalParticleScale.x > 0.8f && !checkNoResetFlg0(daPyFlg0_UNK80)))) {
            m3280.end();

            emitter = dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_0033, &current.pos, NULL, NULL, 0xFF, &m3280);
        }

        if (emitter != NULL) {
            if (checkNoResetFlg0(daPyFlg0_UNK80)) {
                emitter->setGlobalScale(normal_ripple_scale);
            } else {
                emitter->setGlobalScale(small_ripple_scale);
            }
        }
    } else if (m3280.getEmitter() != NULL) {
        m3280.end();
    }

    if (checkModeFlg(ModeFlg_SWIM)) {
        if (!mSwimTailEcallBack[0].field_0x04) {
            mSwimTailEcallBack[0].field_0x08 = std::fabsf(mVelocity / mMaxNormalSpeed);
        }

        if (!mSwimTailEcallBack[1].field_0x04) {
            mSwimTailEcallBack[1].field_0x08 = std::fabsf(mVelocity / mMaxNormalSpeed);
        }
        cXyz local_1c;
        cMtx_multVec(mpCLModel->getAnmMtx(15), &wave_offset, &local_1c);

        cXyz local_20;
        cXyz local_28;
        local_1c.y = m35D0;

        f32 cos = cM_scos(shape_angle.y) * 5.0f;
        f32 sin = cM_ssin(shape_angle.y) * 5.0f;

        local_20.x = local_1c.x + cos;
        local_20.y = local_1c.y;
        local_20.z = local_1c.z - sin;
        local_28.x = local_1c.x - cos;
        local_28.y = local_1c.y;
        local_28.z = local_1c.z + sin;
        mSwimTailEcallBack[0].mPos.set(local_20);
        mSwimTailEcallBack[0].field_0x0C = m35D0 + 2.0f;
        mSwimTailEcallBack[0].field_0x10 = mAcch.m_wtr.GetHeight();
        mSwimTailEcallBack[1].mPos.set(local_28);
        mSwimTailEcallBack[1].field_0x0C = m35D0 + 2.0f;
        mSwimTailEcallBack[1].field_0x10 = mAcch.m_wtr.GetHeight();

        cXyz local_40;
        cMtx_multVec(mpCLModel->getAnmMtx(15), &swim_offset, &local_40);
        MtxP suimenMunyaMtx = mpSuimenMunyaModel->getBaseTRMtx();

        cXyz local_4c;
        mDoMtx_multVecZero(suimenMunyaMtx, &local_4c);

        local_40.y = m35D0;
        local_4c -= local_40;

        cXyz local_50;
        local_50.z = (local_4c.absXZ() / mMaxNormalSpeed) * 0.5f + 1.0f;
        if (local_50.z > 1.5f) {
            local_50.z = 1.5f;
        }
        local_50.x = 1.0f;
        local_50.y = 1.0f;

        if (mCurProc == daPyProc_DEMO_DEAD_e) {
            mDoMtx_stack_c::transS(current.pos.x + cM_ssin(shape_angle.y) * 60.0f, local_40.y + 2.0f, current.pos.z + cM_scos(shape_angle.y) * 60.0f);
        } else {
            mDoMtx_stack_c::transS(local_40.x, local_40.y + 2.0f, local_40.z);
        }

        if (dPa_control_c::isStatus(0x01)) {
            MtxP mtx = mpCLModel->getAnmMtx(15);
            cXyz local_5c;
            mDoMtx_multVecZero(mtx, &local_5c);

            cXyz local_68;
            cMtx_multVec(mtx, &swim_side_offset, &local_68);
            cXyz local_74(local_5c.x * 2.0f - local_68.x, local_5c.y, local_5c.z * 2.0f - local_68.z);
            cXyz local_80(local_5c.x * 2.0f - local_40.x, local_5c.y, local_5c.z * 2.0f - local_40.z);

            if (daSea_ChkArea(local_68.x, local_68.z)) {
                local_68.y = daSea_calcWave(local_68.x, local_68.z);
            }

            if (daSea_ChkArea(local_74.x, local_74.z)) {
                local_74.y = daSea_calcWave(local_74.x, local_74.z);
            }

            if (daSea_ChkArea(local_80.x, local_80.z)) {
                local_80.y = daSea_calcWave(local_80.x, local_80.z);
            }

            cXyz local_b8 = local_40 - local_80;
            cXyz local_c4 = local_74 - local_68;

            mDoMtx_stack_c::ZXYrotM(cM_atan2s(-local_b8.y, local_b8.absXZ()), shape_angle.y, cM_atan2s(-local_c4.y, local_c4.absXZ()));
        } else {
            mDoMtx_stack_c::YrotM(shape_angle.y);
        }

        mpSuimenMunyaModel->setBaseTRMtx(mDoMtx_stack_c::get());
        mpSuimenMunyaModel->setBaseScale(local_50);
    }

    static JGeometry::TVec3<f32> waterfall_splash_trans(0.0f, 15.0f, 0.0f);

    if (((mAcch.ChkGroundHit() || checkModeFlg(ModeFlg_SWIM)) && mCurrAttributeCode == dBgS_Attr_WATERFALL_e) || (checkModeFlg(ModeFlg_HANG) && m3588 == 0x17)) {
        if (m3400.getEmitter() == NULL) {
            m3400.makeEmitter(dPa_name::ID_COMMON_0023, mpCLModel->getAnmMtx(15), &current.pos, NULL);
            JPABaseEmitter* emitter = m3400.getEmitter();

            if (emitter != NULL) {
                emitter->setRate(4.0f);
                emitter->setSpread(1.0f);
                emitter->setEmitterTranslation(waterfall_splash_trans);
            }
        }

        if (m34CD == 0) {
            cXyz local_ac;
            mDoMtx_multVecZero(mpCLModel->getAnmMtx(0), &local_ac);

            dComIfGp_particle_setSingleRipple(dPa_name::ID_COMMON_003F, &local_ac, NULL, (cXyz*)&waterfall_ripple_scale);
            m34CD = 15;
            dComIfGp_getVibration().StartQuake(4, 1, cXyz(0.0f, 1.0f, 0.0f));
        } else {
            m34CD -= 1;
            if (m34CD == 5) {
                dComIfGp_getVibration().StopQuake(-1);
            }
        }
    } else {
        if (m3400.getEmitter() != NULL) {
            dComIfGp_getVibration().StopQuake(-1);
        }

        m3400.end();
    }

    if (m3400.getEmitter() != NULL) {
        GXColor amb, dif;
        dKy_get_seacolor(&amb, &dif);
        m3400.getEmitter()->setGlobalPrmColor(amb.r, amb.g, amb.b);
    }
}

/* 8012B340-8012B8EC       .text setFootEffectType__9daPy_lk_cFiP4cXyzii */
void daPy_lk_c::setFootEffectType(int effectID, cXyz* i_pos, int param_2, int param_3) {
    static JGeometry::TVec3<f32> run_splash_scale(0.6f, 0.6f, 0.6f);
    static Vec grass_scale = {1.5f, 1.5f, 1.5f};
    static JGeometry::TVec3<f32> run_grass_scale(0.65f, 0.65f, 0.65f);
    static Vec smoke_scale = {1.25f, 1.25f, 1.25f};
    static JGeometry::TVec3<f32> heavy_emit_smoke_scale(1.0f, 0.0f, 1.0f);
    static JGeometry::TVec3<f32> heavy_dyn_smoke_scale(0.25f, 0.25f, 0.25f);
    static JGeometry::TVec3<f32> heavy_pat_smoke_scale(0.75f, 0.75f, 0.75f);

    JPABaseEmitter* emitter = NULL;

    csXyz angle;
    daPy_footEffect_c* footEffect = &mFootEffect[param_2];
    if (mAcch.ChkGroundHit() && !checkNoResetFlg0(static_cast<daPy_lk_c::daPy_FLG0>(daPyFlg0_UNK80000000 | daPyFlg0_UNK20000000))) {
        angle.x = getGroundAngle(&mAcch.m_gnd, current.angle.y);
    } else {
        angle.x = 0;
    }

    angle.y = current.angle.y;
    angle.z = 0;

    footEffect->setPos(i_pos);
    footEffect->setAngle(&angle);
    if (effectID == dPa_name::ID_COMMON_0023) {
        if (checkNoResetFlg0(daPyFlg0_UNK80) && m35D0 > 10.0f + i_pos->y) {
            footEffect->mPos.y = m35D0 - 10.0f;
        }
    } else if (mCurProc == daPyProc_CUT_ROLL_e && effectID == dPa_name::ID_COMMON_2022) {
        effectID = -2;
    } else if (param_3 == 5) {
        effectID = dPa_name::ID_COMMON_2027;
    }

    s32 oldEffectID = footEffect->getID();
    if (effectID != oldEffectID) {
        if (oldEffectID != -1) {
            footEffect->getSmokeCallBack()->remove();
            footEffect->getOtherCallBack()->remove();
        }

        if (effectID == -2) {
            emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_2022, &footEffect->getPos(), &footEffect->getAngle(), (cXyz*)&smoke_scale, (u8)daPy_HIO_basic_c0::m.field_0x2, footEffect->getSmokeCallBack(), fopAcM_GetRoomNo(this));
        } else if (effectID == dPa_name::ID_COMMON_2022 || effectID == dPa_name::ID_COMMON_2027) {
            emitter = dComIfGp_particle_setToonP1(effectID, &footEffect->getPos(), &footEffect->getAngle(), (cXyz*)&smoke_scale, (u8)daPy_HIO_basic_c0::m.field_0x2, footEffect->getSmokeCallBack(), fopAcM_GetRoomNo(this));
        } else if (effectID == dPa_name::ID_COMMON_0024) {
            GXColor color = {tevStr.mColorC0.r, tevStr.mColorC0.g, tevStr.mColorC0.b, tevStr.mColorC0.a};
            emitter = dComIfGp_particle_setP1(effectID, &footEffect->getPos(), &footEffect->getAngle(), (cXyz*)&grass_scale, 0xFF, footEffect->getOtherCallBack(), -1, &color, &tevStr.mColorK0);
        } else {
            GXColor amb, dif;
            dKy_get_seacolor(&amb, &dif);
            emitter = dComIfGp_particle_setP1(effectID, &footEffect->getPos(), &footEffect->getAngle(), NULL, 0xFF, footEffect->getOtherCallBack(), -1, &amb);
        }

        if (emitter != NULL) {
            footEffect->setID(effectID);
        }

        if (effectID == -2) {
            effectID = dPa_name::ID_COMMON_2022;
        }
    }

    if (emitter != NULL) {
        if (param_3 == 5) {
            if (effectID == dPa_name::ID_COMMON_2027) {
                emitter->setLifeTime(40);
                emitter->setRate(10.0f);
                emitter->setEmitterScale(heavy_emit_smoke_scale);
                emitter->setGlobalDynamicsScale(heavy_dyn_smoke_scale);
                emitter->setGlobalParticleScale(heavy_pat_smoke_scale);
            } else {
                emitter->setRate(15.0f);
                emitter->setSpread(1.0f);
                if (effectID == dPa_name::ID_COMMON_0024) {
                    emitter->setDirectionalSpeed(12.0f);
                }
            }
        } else if (param_3 == 1) {
            emitter->setRate(16.0f);
            emitter->setSpread(1.0f);
        } else if (param_3 == 3) {
            emitter->setRate(8.0f);
            emitter->setSpread(0.3f);
        } else if (param_3 == 2) {
            if (effectID == dPa_name::ID_COMMON_0024) {
                emitter->setGlobalScale(run_grass_scale);
                emitter->setRate(10.0f);
                emitter->setSpread(1.0f);
                emitter->setLifeTime(15);
            } else {
                emitter->setRate(18.0f);
                emitter->setSpread(1.0f);
                emitter->setGlobalScale(run_splash_scale);
            }
        } else if (param_3 == 4 && effectID == dPa_name::ID_COMMON_0023) {
            emitter->setRate(3.0f);
            emitter->setSpread(0.2f);
        } else {
            emitter->setRate(3.0f);
            emitter->setSpread(0.05f);
        }
    }
}

/* 8012B8EC-8012B9DC       .text setFootMark__9daPy_lk_cFP4cXyz */
void daPy_lk_c::setFootMark(cXyz* i_pos) {
    cXyz pos(i_pos->x, i_pos->y + 5.0f, i_pos->z);
    mGndChk.SetPos(&pos);

    pos.y = dComIfG_Bgsp()->GroundCross(&mGndChk);
    if (pos.y != -G_CM3D_F_INF && dComIfG_Bgsp()->GetAttributeCode(mGndChk) == dBgS_Attr_SAND_e) {
        fopKyM_create(PROC_WATER_MARK, (shape_angle.y << 16) | 2, &pos, &scale, NULL);
    }

    if (m336C.mpEmitter != NULL) {
        fopKyM_create(PROC_WATER_MARK, shape_angle.y << 16, i_pos, &scale);
    }
}

/* 8012B9DC-8012C128       .text setFootEffect__9daPy_lk_cFv */
void daPy_lk_c::setFootEffect() {
    if (!mAcch.ChkGroundHit() || checkNoResetFlg0(daPyFlg0_UNK80000000)) {
        resetFootEffect();
        m3410.end();
        return;
    }

    cXyz pos;
    if (getFootOnGround()) {
        if (getRightFootOnGround()) {
            mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x27), &pos);
            setFootMark(&pos);
        }

        if (getLeftFootOnGround()) {
            mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x22), &pos);
            setFootMark(&pos);
        }
    }

    if (checkResetFlg0(daPyRFlg0_UNK10) && mCurrAttributeCode == dBgS_Attr_WATER_e && m35D0 > 25.0f + current.pos.y) {
        cXyz& p = m3410.getPos();
        p.x = current.pos.x + 45.0f * cM_ssin(current.angle.y);
        p.y = m35D0;
        p.z = current.pos.z + 45.0f * cM_scos(current.angle.y);

        m3410.setAngle(0, current.angle.y + 0x8000, 0);

        if (m3410.mpEmitter == NULL) {
            GXColor amb, dif;
            dKy_get_seacolor(&amb, &dif);

            JPABaseEmitter* emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_0023, &p, NULL, NULL, 0xFF, &m3410, -1, &amb);
            if (emitter != NULL) {
                emitter->setLifeTime(15);
                emitter->setRate(4.0f);
                emitter->setSpread(0.6f);
                emitter->setDirectionalSpeed(11.0f);
            }
        }
    } else {
        m3410.end();
    }

    if (strcmp(dComIfGp_getStartStageName(), "Adanmae") == 0) {
        if (checkResetFlg0(daPyRFlg0_UNK10)) {
            if (getFootOnGround() && m35D0 <= current.pos.y) {
                dComIfGp_particle_setP1(dPa_name::ID_SCENE_8237, &pos, &current.angle);
            }
        }
    }

    s32 effectID = dComIfGp_particle_checkAtrCodeEffect(mCurrAttributeCode);
    if (effectID == -1) {
        return;
    }

    s32 var_r29;
    if (
        checkResetFlg0(daPyRFlg0_UNK10) && getFootOnGround() &&
        (checkHeavyStateOn() || effectID == dPa_name::ID_COMMON_0023 || effectID == dPa_name::ID_COMMON_0024)
    ) {
        if (getRightFootOnGround()) {
            m34BE = 2;
        } else {
            m34BE = 1;
        }

        if (checkHeavyStateOn()) {
            var_r29 = 5;
            dComIfGp_getVibration().StartShock(2, -0x31, cXyz(0.0f, 1.0f, 0.0f));
        } else {
            var_r29 = 2;
        }
    } else {
        if (mCurProc == daPyProc_JUMP_CUT_LAND_e) {
            var_r29 = 3;
        } else if (mCurProc == daPyProc_FRONT_ROLL_e) {
            var_r29 = 4;
        } else {
            var_r29 = 0;
        }
    }

    if (m34BE == 0) {
        return;
    }

    if (mCurProc == daPyProc_DEMO_LAST_COMBO_e) {
        f32 rnd = cM_rndFX(17.5f);
        cXyz sp44 = m370C;
        mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x1), &m370C);

        if (mProcVar0.m3570 != 0) {
            current.angle.y = shape_angle.y - 0x4000;
            mProcVar0.m3570 = 0;
        } else {
            cXyz sp38 = m370C - sp44;
            current.angle.y = cM_atan2s(sp38.x, sp38.z);
        }

        pos.x = m370C.x + rnd * cM_scos(current.angle.y);
        pos.y = current.pos.y;
        pos.z = m370C.z - rnd * cM_scos(current.angle.y);
        setFootEffectType(effectID, &pos, 0, var_r29);
    } else {
        if (m34BE == 4) {
            f32 rnd = cM_rndFX(17.5f);
            pos.x = current.pos.x + rnd * cM_scos(current.angle.y);
            pos.y = current.pos.y;
            pos.z = current.pos.z - rnd * cM_scos(current.angle.y);
            setFootEffectType(effectID, &pos, 0, var_r29);

        } else if (m34BE == 3) {
            if (mCurrAttributeCode == dBgS_Attr_GRASS_e || mCurrAttributeCode == dBgS_Attr_WATER_e) {
                mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x27), &pos);
                setFootEffectType(effectID, &pos, 0, var_r29);

                mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x22), &pos);
                setFootEffectType(effectID, &pos, 1, var_r29);

            } else {
                setFootEffectType(effectID, &current.pos, 0, var_r29);
            }
        } else if (m34BE == 1) {
            mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x22), &pos);
            setFootEffectType(effectID, &pos, 0, var_r29);
        } else if (m34BE == 2) {
            mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x27), &pos);
            setFootEffectType(effectID, &pos, 0, var_r29);
        } else if (m34BE == 5) {
            setFootEffectType(effectID, &current.pos, 0, 1);
        } else if (m34BE == 6) {
            mDoMtx_multVecZero(mpCLModel->getAnmMtx(0), &pos);


            mGndChk.SetPos(&pos);

            f32 groundY = dComIfG_Bgsp()->GroundCross(&mGndChk);
            if (groundY != -G_CM3D_F_INF) {
                pos.y = groundY;
            }

            setFootEffectType(effectID, &pos, 0, 1);
        }
    }
}

/* 8012C128-8012C1A8       .text resetFootEffect__9daPy_lk_cFv */
void daPy_lk_c::resetFootEffect() {
    daPy_footEffect_c* pFootEffect = mFootEffect;
    for (int idx = 0; idx < (s32)ARRAY_SIZE(mFootEffect); idx++, pFootEffect++) {
        pFootEffect->getSmokeCallBack()->remove();
        pFootEffect->getOtherCallBack()->remove();
        pFootEffect->setID(-1);
    }

    m34BE = 0;
}

/* 8012C1A8-8012C2A4       .text setSwimTail__9daPy_lk_cFv */
void daPy_lk_c::setSwimTail() {
    static JGeometry::TVec3<f32> tail_scale(1.0f, 1.0f, -1.0f);

    if (mSwimTailEcallBack[0].getEmitter() == NULL) {
        dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_003A, &mSwimTailEcallBack[0].getPos(), &current.angle, &scale, 0xFF, &mSwimTailEcallBack[0]);
        mSwimTailEcallBack[0].field_0x05 = true;
    }

    if (mSwimTailEcallBack[1].getEmitter() == NULL) {
        dComIfGp_particle_setShipTail(dPa_name::ID_COMMON_003A, &mSwimTailEcallBack[1].getPos(), &current.angle, &scale, 0xFF, &mSwimTailEcallBack[1]);
    }
}

/* 8012C2A4-8012C330       .text setCutWaterSplash__9daPy_lk_cFv */
void daPy_lk_c::setCutWaterSplash() {
    if (m336C.getEmitter() != NULL) {
        cXyz pos;
        mDoMtx_multVecZero(mpCLModel->getAnmMtx(4), &pos);

        dComIfGp_particle_setP1(dPa_name::ID_COMMON_0039, &pos);
    }
}

/* 8012C330-8012C45C       .text setSwimWaterDrop__9daPy_lk_cFP25daPy_waterDropEcallBack_c */
void daPy_lk_c::setSwimWaterDrop(daPy_waterDropEcallBack_c* callBack) {
    f32 tmp = m35D0 + 10.0f;
    if (checkNoResetFlg1(daPy_lk_c::daPyFlg1_WATER_DROP) || !checkNoResetFlg0(daPy_lk_c::daPyFlg0_UNK80) || (callBack->getPos().y > tmp && !checkModeFlg(ModeFlg_SWIM))) {
        if (callBack->getEmitter() == NULL && (callBack->field_0x1C || checkNoResetFlg1(daPy_lk_c::daPyFlg1_WATER_DROP))) {
            JPABaseEmitter* emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_0038, &callBack->getPos(), NULL, NULL, 0xFF, callBack);

            if (emitter != NULL) {
                emitter->setParticleCallBackPtr(&daPy_waterDropEcallBack_c::m_pcallback);
            }
        }

        callBack->field_0x1C = FALSE;
        offNoResetFlg1(daPy_lk_c::daPyFlg1_WATER_DROP);
    } else if (checkNoResetFlg0(daPy_lk_c::daPyFlg0_UNK80) && callBack->getPos().y < m35D0) {
        callBack->end();
        if (mCurProc != daPyProc_VOMIT_WAIT_e) {
            callBack->field_0x1C = TRUE;
        }
    }
}

/* 8012C45C-8012C620       .text setWaterDrop__9daPy_lk_cFv */
void daPy_lk_c::setWaterDrop() {
    MtxP mtx = mpCLModel->getAnmMtx(0x0E);
    cXyz tmp;
    mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x0E), &tmp);
    m334C.setPos(&tmp);

    mDoMtx_multVecZero(mpCLModel->getAnmMtx(0x02), &tmp);
    m336C.setPos(&tmp);

    if (checkModeFlg(ModeFlg_00000001)) {
        daPy_waterDropEcallBack_c::m_pcallback.field_0x4 = TRUE;
    } else {
        daPy_waterDropEcallBack_c::m_pcallback.field_0x4 = FALSE;
    }

    if (daPy_dmEcallBack_c::checkFlame()) {
        m334C.end();
        m336C.end();
        m3460[0].end();
        m3460[1].end();
        return;
    }

    if (dKyr_player_overhead_bg_chk() && dStage_stagInfo_GetSTType(dComIfGp_getStageStagInfo()) != dStageType_MISC_e && mCurProc != daPyProc_DEMO_LAST_COMBO_e && mAcch.m_roof_y == G_CM3D_F_INF) {
        if (m3460[0].getEmitter() == NULL) {
            m3460[0].makeEmitter(dPa_name::ID_COMMON_0432, mpCLModel->getAnmMtx(0x0E), &current.pos, NULL);
        }

        if (m3460[1].getEmitter() == NULL) {
            m3460[1].makeEmitter(dPa_name::ID_COMMON_0432, mpCLModel->getAnmMtx(0x02), &current.pos, NULL);
        }

        m334C.end();
        m336C.end();
        return;
    }

    m3460[0].end();
    m3460[1].end();
    setSwimWaterDrop(&m334C);
    setSwimWaterDrop(&m336C);
}

/* 8012C620-8012C754       .text setDamageFlameEmitter__9daPy_lk_cFv */
void daPy_lk_c::setDamageFlameEmitter() {
    static JGeometry::TVec3<f32> arm_flame_scale(0.6f, 0.6f, 0.6f);
    static const u16 flame_joint[ARRAY_SIZE(mDmEcallBack)] = {
        0x000F, // head_jnt
        0x0003, // stomach_jnt
        0x0007, // LarmB_jnt
        0x000B, // RarmB_jnt
    };

    if (!daPy_dmEcallBack_c::checkFlame()) {
        endDamageEmitter();

        const u16* jointNoP = flame_joint;
        daPy_dmEcallBack_c* dmECB = mDmEcallBack;
        for (int i = 0; i < (s32)ARRAY_SIZE(mDmEcallBack); i++, jointNoP++, dmECB++) {
            cXyz jointPos;
            mDoMtx_multVecZero(mpCLModel->getAnmMtx(*jointNoP), &jointPos);
            dmECB->makeEmitter(dPa_name::ID_COMMON_03F1, mpCLModel->getAnmMtx(*jointNoP), &jointPos, NULL);
            if (dmECB->getEmitter() == NULL) {
                continue;
            }
            if (i == 2 || i == 3) {
                dmECB->getEmitter()->setGlobalScale(arm_flame_scale);
            }
        }
    }

    daPy_dmEcallBack_c::setFlame(100);
}

/* 8012C754-8012C7F0       .text setDamageCurseEmitter__9daPy_lk_cFv */
void daPy_lk_c::setDamageCurseEmitter() {
    if (!daPy_dmEcallBack_c::checkCurse()) {
        endDamageEmitter();

        mDmEcallBack[0].makeEmitter(dPa_name::ID_SCENE_815B, mpCLModel->getAnmMtx(0x1E), &current.pos, NULL);

        if (checkUpperReadyThrowAnime()) {
            resetActAnimeUpper(UPPER_MOVE2_e, -1.0f);
            freeRopeItem();
        }
    }

    cancelNoDamageMode();
    daPy_dmEcallBack_c::setCurse(200);
}

/* 8012C7F0-8012C880       .text setDamageElecEmitter__9daPy_lk_cFv */
void daPy_lk_c::setDamageElecEmitter() {
    if (!daPy_dmEcallBack_c::checkElec()) {
        endDamageEmitter();

        mDmEcallBack[0].makeEmitter(dPa_name::ID_COMMON_03ED, mpCLModel->getAnmMtx(4), &current.pos, NULL);
        mDmEcallBack[1].makeEmitter(dPa_name::ID_COMMON_03EE, mpCLModel->getAnmMtx(4), &current.pos, NULL);
    }

    daPy_dmEcallBack_c::setElec(daPy_HIO_elecDamage_c0::m.field_0x2);
}

/* 8012C880-8012C8F8       .text setDamageEmitter__9daPy_lk_cFv */
void daPy_lk_c::setDamageEmitter() {
    dCcD_GObjInf* tgHitGObj = mCyl.GetTgHitGObj();
    if (tgHitGObj != NULL) {
        if (tgHitGObj->GetAtSpl() == dCcG_At_Spl_UNK3) {
            setDamageCurseEmitter();
        } else if (tgHitGObj->GetAtSpl() == dCcG_At_Spl_UNKB) {
            setDamageElecEmitter();
        } else if (tgHitGObj->ChkAtType(AT_TYPE_FIRE)) {
            setDamageFlameEmitter();
        }
    }
}

/* 8012C8F8-8012C9D8       .text endFlameDamageEmitter__9daPy_lk_cFv */
void daPy_lk_c::endFlameDamageEmitter() {
    if (!daPy_dmEcallBack_c::checkFlame()) return;

    if (current.pos.y < m35D0 - 10.0f) {
        for (int i = 0; i < (s32)ARRAY_SIZE(mDmEcallBack); i++) {
            cXyz pos;
            mDoMtx_multVecZero(mDmEcallBack[i].mpMtx, &pos);
            pos.y = m35D0;

            dComIfGp_particle_set(dPa_name::ID_COMMON_035A, &pos);
        }
    }

    endDamageEmitter();
}

/* 8012C9D8-8012CA44       .text endDamageEmitter__9daPy_lk_cFv */
void daPy_lk_c::endDamageEmitter() {
    for (int i = 0; i < (int)ARRAY_SIZE(mDmEcallBack); i++) {
        mDmEcallBack[i].end();
    }
    daPy_dmEcallBack_c::setTimer(0);
    daPy_dmEcallBack_c::setType(3);
    mLightInfluence.mPower = 0.0f;
}

/* 8012CA44-8012CD60       .text setItemWaterEffect__9daPy_lk_cFP10fopAc_ac_cii */
u32 daPy_lk_c::setItemWaterEffect(fopAc_ac_c* i_actor, int param_1, int param_2) {
    static cXyz eff_scale0(0.5f, 0.5f, 0.5f);
    static cXyz eff_scale2(0.13f, 0.13f, 0.13f);
    static JGeometry::TVec3<f32> direction(0.0f, 1.0f, 0.0f);

    f32 waterY;
    if (fopAcM_getWaterY(&i_actor->current.pos, &waterY) && ((param_1 != 0 && i_actor->current.pos.y > waterY) || (param_1 == 0 && waterY >= i_actor->current.pos.y))) {
        param_1 ^= 1;
        if (param_1 == 0 && param_2 == 0) {
            return param_1;
        }

        f32 deltaY = std::fabsf(i_actor->old.pos.y - i_actor->current.pos.y);
        f32 waterDistY = std::fabsf(waterY - i_actor->current.pos.y);
        cXyz pos;
        if (deltaY < 1.0f) {
            pos = i_actor->current.pos;
        } else {
            f32 var_f31 = waterDistY / deltaY;

            if (var_f31 > 1.0f) {
                var_f31 = 1.0f;
            }

            pos = i_actor->old.pos * var_f31 + i_actor->current.pos * (1.0f - var_f31);
        }

        dComIfGp_particle_setSingleRipple(dPa_name::ID_COMMON_003D, &pos, NULL, &eff_scale0);
        dComIfGp_particle_setSingleRipple(dPa_name::ID_COMMON_003F, &pos, NULL, &eff_scale0);

        GXColor amb, dif;
        dKy_get_seacolor(&amb, &dif);
        JPABaseEmitter* emitter = dComIfGp_particle_setP1(dPa_name::ID_COMMON_0023, &pos, NULL, &eff_scale2, 0xFF, NULL, -1, &amb);

        if (emitter != NULL) {
            emitter->setMaxFrame(1);
            emitter->setLifeTime(20);
            emitter->setRate(40.0f);
            emitter->setAwayFromAxisSpeed(20.0f);
            emitter->setDirectionalSpeed(80.0f);
            emitter->setSpread(0.0f);
            emitter->setDirection(direction);
        }
    }

    return param_1;
}
