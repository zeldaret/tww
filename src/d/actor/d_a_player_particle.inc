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
    } else if (field_0x10 != 0.0f) {
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
void daPy_swimTailEcallBack_c::execute(JPABaseEmitter*) {
    /* Nonmatching */
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
    /* Nonmatching */
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
void daPy_followEcallBack_c::execute(JPABaseEmitter*) {
    /* Nonmatching */
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

/* 80129FD4-8012A040       .text execute__25daPy_waterDropEcallBack_cFP14JPABaseEmitter */
void daPy_waterDropEcallBack_c::execute(JPABaseEmitter* emitter) {
    daPy_followEcallBack_c::execute(emitter);
    bool shouldEnd = false;
    if (emitter->checkStatus(0x08) && emitter->getParticleNumber() == 0) {
        shouldEnd = true;
    }
    if (shouldEnd) {
        end();
    }
}

/* 8012A040-8012A058       .text setup__25daPy_waterDropEcallBack_cFP14JPABaseEmitterPC4cXyzPC5csXyzSc */
void daPy_waterDropEcallBack_c::setup(JPABaseEmitter* emitter, const cXyz* pos, const csXyz* angle, s8) {
    mpEmitter = emitter;
    mpEmitter->becomeImmortalEmitter();
}

/* 8012A058-8012A0B4       .text end__25daPy_waterDropEcallBack_cFv */
void daPy_waterDropEcallBack_c::end() {
    /* Nonmatching */
}

/* 8012A0B4-8012A0E0       .text makeEmitterColor__28daPy_mtxPosFollowEcallBack_cFUsPA4_fPC4cXyzPC5csXyzPC8_GXColorPC8_GXColor */
void daPy_mtxPosFollowEcallBack_c::makeEmitterColor(u16, MtxP, const cXyz*, const csXyz*, const GXColor*, const GXColor*) {
    /* Nonmatching */
}

/* 8012A0E0-8012A160       .text execute__28daPy_mtxPosFollowEcallBack_cFP14JPABaseEmitter */
void daPy_mtxPosFollowEcallBack_c::execute(JPABaseEmitter*) {
    /* Nonmatching */
}

/* 8012A160-8012A288       .text execute__18daPy_dmEcallBack_cFP14JPABaseEmitter */
void daPy_dmEcallBack_c::execute(JPABaseEmitter*) {
    /* Nonmatching */
}

/* 8012A288-8012A8D8       .text setAuraEffect__9daPy_lk_cFv */
void daPy_lk_c::setAuraEffect() {
    /* Nonmatching */
}

/* 8012A8D8-8012B340       .text setWaterRipple__9daPy_lk_cFv */
void daPy_lk_c::setWaterRipple() {
    /* Nonmatching */
}

/* 8012B340-8012B8EC       .text setFootEffectType__9daPy_lk_cFiP4cXyzii */
void daPy_lk_c::setFootEffectType(int, cXyz*, int, int) {
    /* Nonmatching */
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
    /* Nonmatching */
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
    for (int i = 0; i < (int)ARRAY_SIZE(m33B8); i++) {
        m33B8[i].end();
    }
    daPy_dmEcallBack_c::setTimer(0);
    daPy_dmEcallBack_c::setType(3);
    mLightInfluence.mPower = 0.0f;
}

/* 8012CA44-8012CD60       .text setItemWaterEffect__9daPy_lk_cFP10fopAc_ac_cii */
u32 daPy_lk_c::setItemWaterEffect(fopAc_ac_c*, int, int) {
    /* Nonmatching */
}
