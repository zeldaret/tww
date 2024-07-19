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
#include "d/actor/d_a_sea.h"

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
    } else if (field_0x10 != -1e9f) {
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
        emitter->setGlobalTranslation(field_0x14.x, field_0x14.y, field_0x14.z);
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

    for (JSULink<JPABaseParticle>* link = emitter->mActiveParticles.getFirst(); link != NULL;) {
        JSULink<JPABaseParticle>* nextLink = link->getNext();
        JPABaseParticle* particle = link->getObject();

        JGeometry::TVec3<f32> sp14;
        particle->getGlobalPosition(sp14);
        getMaxWaterY(&sp14);
        particle->setOffsetPosition(sp14);

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
    /* Nonmatching */
}

/* 8012952C-801296FC       .text setSight__18daPy_sightPacket_cFv */
void daPy_sightPacket_c::setSight() {
    /* Nonmatching */
}

/* 801296FC-801297F4       .text initSwBlur__13daPy_swBlur_cFPA4_fifi */
void daPy_swBlur_c::initSwBlur(MtxP, int, f32, int) {
    /* Nonmatching */
}

/* 801297F4-80129A78       .text copySwBlur__13daPy_swBlur_cFPA4_fi */
void daPy_swBlur_c::copySwBlur(MtxP, int) {
    /* Nonmatching */
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

    if (mBlurColorType == 0) {
        // Normal color.
        static GXColor n_color = {0xFF, 0xFF, 0xFF, 0x96};
        GXSetTevColor(GX_TEVREG0, n_color);
    } else if (mBlurColorType == 1) {
        // Elixir Soup color.
        static GXColor y_color = {0xFF, 0xFF, 0x7B, 0x96};
        GXSetTevColor(GX_TEVREG0, y_color);
    } else {
        // Parrying color.
        static GXColor g_color = {0x5A, 0xFF, 0x5A, 0x96};
        GXSetTevColor(GX_TEVREG0, g_color);
    }

    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
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
        GXPosition3f32(field_0x034[i].x, field_0x034[i].y, field_0x034[i].z);
        GXTexCoord2s16(r29, 0x00);
        GXPosition3f32(field_0x304[i].x, field_0x304[i].y, field_0x304[i].z);
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
void daPy_fanSwingEcallBack_c::execute(JPABaseEmitter*) {
    /* Nonmatching */
}

/* 80129E9C-80129F48       .text execute__25daPy_waterDropPcallBack_cFP14JPABaseEmitterP15JPABaseParticle */
void daPy_waterDropPcallBack_c::execute(JPABaseEmitter*, JPABaseParticle*) {
    /* Nonmatching */
}

/* 80129F48-80129F98       .text execute__22daPy_followEcallBack_cFP14JPABaseEmitter */
void daPy_followEcallBack_c::execute(JPABaseEmitter* emitter) {
    JGeometry::TVec3<f32> pos(field_0x08.x, field_0x08.y, field_0x08.z);
    emitter->setGlobalTranslation(pos);
    JGeometry::TVec3<s16> rot;
    rot.x = field_0x14.x;
    rot.y = field_0x14.y;
    rot.z = field_0x14.z;
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
    if (m_type == 0) {
        cXy v;
        v.x = emitter->mGlobalTranslation.x;
        v.y = emitter->mGlobalTranslation.z;

        emitter->setGlobalTranslation(mpMtx[0][3], mpMtx[1][3], mpMtx[2][3]);

        v.x = (mpMtx[0][3] - v.x) * -0.05f;
        v.y = (mpMtx[2][3] - v.y) * -0.05f;
        f32 sq = v.x * v.x + v.y * v.y;

        if (sq > 1.0f) {
            f32 distFrac = 1.0f / sqrtf(sq);

            v.x *= distFrac;
            v.y *= distFrac;
        }

        emitter->setDirection(JGeometry::TVec3<f32>(v.x, 0.6f, v.y));
    } else {
        emitter->setGlobalRTMatrix(mpMtx);
    }
}

/* 8012A288-8012A8D8       .text setAuraEffect__9daPy_lk_cFv */
void daPy_lk_c::setAuraEffect() {
    /* Nonmatching */
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
}

/* 8012A8D8-8012B340       .text setWaterRipple__9daPy_lk_cFv */
void daPy_lk_c::setWaterRipple() {
    /* Nonmatching */
    static Vec waterfall_ripple_scale = {0.75f, 0.75f, 0.75f};
    static JGeometry::TVec3<f32> normal_ripple_scale;
    static JGeometry::TVec3<f32> small_ripple_scale;
    static JGeometry::TVec3<f32> waterfall_splash_trans;
    static const Vec wave_offset = {0.0f, 18.0f, 0.0f};
    static const Vec swim_offset = {0.0f, 30.0f, 0.0f};
    static const Vec swim_side_offset = {0.0f, 0.0f, 30.0f};
}

/* 8012B340-8012B8EC       .text setFootEffectType__9daPy_lk_cFiP4cXyzii */
void daPy_lk_c::setFootEffectType(int, cXyz*, int, int) {
    /* Nonmatching */
    static JGeometry::TVec3<f32> run_splash_scale;
    static Vec grass_scale = {1.5f, 1.5f, 1.5f};
    static JGeometry::TVec3<f32> run_grass_scale;
    static Vec smoke_scale = {1.25f, 1.25f, 1.25f};
    static JGeometry::TVec3<f32> heavy_emit_smoke_scale;
    static JGeometry::TVec3<f32> heavy_dyn_smoke_scale;
    static JGeometry::TVec3<f32> heavy_pat_smoke_scale;
}

/* 8012B8EC-8012B9DC       .text setFootMark__9daPy_lk_cFP4cXyz */
void daPy_lk_c::setFootMark(cXyz*) {
    /* Nonmatching */
}

/* 8012B9DC-8012C128       .text setFootEffect__9daPy_lk_cFv */
void daPy_lk_c::setFootEffect() {
    /* Nonmatching */
}

/* 8012C128-8012C1A8       .text resetFootEffect__9daPy_lk_cFv */
void daPy_lk_c::resetFootEffect() {
    /* Nonmatching */
}

/* 8012C1A8-8012C2A4       .text setSwimTail__9daPy_lk_cFv */
void daPy_lk_c::setSwimTail() {
    /* Nonmatching */
    static JGeometry::TVec3<f32> tail_scale(1.0f, 1.0f, -1.0f);
}

/* 8012C2A4-8012C330       .text setCutWaterSplash__9daPy_lk_cFv */
void daPy_lk_c::setCutWaterSplash() {
    /* Nonmatching */
}

/* 8012C330-8012C45C       .text setSwimWaterDrop__9daPy_lk_cFP25daPy_waterDropEcallBack_c */
void daPy_lk_c::setSwimWaterDrop(daPy_waterDropEcallBack_c*) {
    /* Nonmatching */
}

/* 8012C45C-8012C620       .text setWaterDrop__9daPy_lk_cFv */
void daPy_lk_c::setWaterDrop() {
    /* Nonmatching */
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
            dmECB->makeEmitter(0x3F1, mpCLModel->getAnmMtx(*jointNoP), &jointPos, NULL);
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
    /* Nonmatching */
}

/* 8012C7F0-8012C880       .text setDamageElecEmitter__9daPy_lk_cFv */
void daPy_lk_c::setDamageElecEmitter() {
    /* Nonmatching */
}

/* 8012C880-8012C8F8       .text setDamageEmitter__9daPy_lk_cFv */
void daPy_lk_c::setDamageEmitter() {
    /* Nonmatching */
}

/* 8012C8F8-8012C9D8       .text endFlameDamageEmitter__9daPy_lk_cFv */
void daPy_lk_c::endFlameDamageEmitter() {
    /* Nonmatching */
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
u32 daPy_lk_c::setItemWaterEffect(fopAc_ac_c*, int, int) {
    /* Nonmatching */
    static cXyz eff_scale0(0.5f, 0.5f, 0.5f);
    static cXyz eff_scale2(0.13f, 0.13f, 0.13f);
    static JGeometry::TVec3<f32> direction(0.0f, 1.0f, 0.0f);
}
