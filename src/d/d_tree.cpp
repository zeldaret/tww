#include "d/dolzel.h" // IWYU pragma: keep
#include "d/d_tree.h"
#include "d/actor/d_a_player.h"
#include "dolphin/gf/GF.h"
#include "SSystem/SComponent/c_counter.h"
#include "m_Do/m_Do_lib.h"
#include "f_op/f_op_overlap_mng.h"

#include "assets/l_Txa_swood_aTEX.h"
const u16 l_Txa_swood_aTEX__width = 64;
const u16 l_Txa_swood_aTEX__height = 64;

static Vec l_pos[] = {
    {-10.0f, 105.608147f, 5.0f},
    {10.0f, 105.608147f, 5.0f},
    {0.0f, 115.841797f, 0.0f},
    {-19.090694f, 190.686432f, 37.321354f},
    {0.0f, 105.608147f, -10.0f},
    {41.625153f, 211.34726f, -14.772539f},
    {-33.026093f, 215.296951f, -44.96241f},
    {-10.0f, 20.0f, 5.0f},
    {10.0f, 20.0f, 5.0f},
    {0.0f, 20.0f, -10.0f},
    {10.0f, 105.608147f, -5.0f},
    {10.0f, 20.0f, -5.0f},
    {-10.0f, 105.608147f, -5.0f},
    {-10.0f, 20.0f, -5.0f},
    {0.0f, 105.608147f, 10.0f},
    {0.0f, 20.0f, 10.0f},
    {-10.0f, 0.0f, 5.0f},
    {10.0f, 0.0f, 5.0f},
    {0.0f, 0.0f, -10.0f},
    {10.0f, 0.0f, -5.0f},
    {-10.0f, 0.0f, -5.0f},
    {0.0f, 0.0f, 10.0f},
    {2.909025f, 212.994461f, -45.632366f},
    {-10.776078f, 184.271301f, 5.599532f},
    {33.920052f, 212.994461f, 34.134495f},
    {72.31778f, 168.951508f, 19.206579f},
    {86.002876f, 197.674683f, -32.025314f},
    {41.30674f, 168.951508f, -60.560272f},
    {-10.575331f, 211.978516f, -22.376558f},
    {14.409488f, 243.166702f, 23.706152f},
    {58.760258f, 202.669464f, 34.361908f},
    {96.549309f, 224.54863f, -8.227419f},
    {71.564476f, 193.360443f, -54.310123f},
    {27.213718f, 233.857651f, -64.965866f},
    {41.625156f, 211.347275f, -14.772542f},
    {22.596979f, 256.019928f, -40.096336f},
    {14.065658f, 241.755569f, -4.058219f},
    {44.6987f, 256.019958f, 16.753942f},
    {73.287094f, 230.837082f, 5.639604f},
    {81.818398f, 245.101456f, -30.398512f},
    {51.185356f, 230.837082f, -51.210663f},
    {-7.857542f, 194.658112f, -10.762144f},
    {-53.937096f, 156.796143f, -1.809134f},
    {-66.201447f, 183.508667f, 50.850483f},
    {-28.940256f, 145.54512f, 79.264961f},
    {17.139292f, 183.407074f, 70.311951f},
    {29.403631f, 156.69455f, 17.652328f},
    {-19.090696f, 190.686417f, 37.321354f},
    {-33.985317f, 188.75563f, -13.250698f},
    {-70.496834f, 213.49118f, 28.887436f},
    {-54.248596f, 175.144028f, 73.452583f},
    {-4.665742f, 206.592773f, 89.977669f},
    {31.845766f, 181.857224f, 47.839523f},
    {15.597519f, 220.204346f, 3.274376f},
    {-19.090696f, 190.686432f, 37.321358f},
    {-12.561728f, 237.465271f, 9.606261f},
    {-45.613617f, 216.75177f, 16.922333f},
    {-54.143745f, 229.519012f, 53.517914f},
    {-27.798243f, 208.733109f, 74.704277f},
    {5.253643f, 229.446609f, 67.388199f},
    {13.783756f, 216.679367f, 30.792624f},
    {-65.836937f, 200.599899f, -79.042107f},
    {-78.85379f, 178.159485f, -24.599487f},
    {-47.995983f, 222.830963f, 1.654331f},
    {2.405176f, 189.776688f, -0.382604f},
    {15.422019f, 212.217102f, -54.825226f},
    {-15.435799f, 167.545624f, -81.079041f},
    {-33.026093f, 215.296951f, -44.962418f},
    {-81.844887f, 199.673126f, -57.441658f},
    {-73.009483f, 243.963348f, -16.443239f},
    {-21.627028f, 220.240952f, 6.308706f},
    {14.903163f, 244.573044f, -36.047581f},
    {6.067755f, 200.282806f, -77.045998f},
    {-45.314705f, 224.005219f, -99.797928f},
    {-33.026093f, 215.296967f, -44.962421f},
    {-59.207829f, 247.753891f, -80.459984f},
    {-68.884155f, 237.886353f, -43.257812f},
    {-46.492485f, 263.598114f, -22.947197f},
    {-10.970461f, 246.166f, -25.998304f},
    {-1.294143f, 256.033539f, -63.200481f},
    {-23.685818f, 230.321808f, -83.511086f},
};

static GXColor l_color[] = {
    {0x80, 0x80, 0x80, 0xFF},
    {0x8D, 0x8D, 0x8D, 0xFF},
    {0x99, 0x99, 0x99, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF},
    {0x9C, 0x9C, 0x9C, 0xFF},
    {0x97, 0x97, 0x97, 0xFF},
    {0x8C, 0x8C, 0x8C, 0xFF},
    {0x33, 0x33, 0x33, 0xFF},
    {0x66, 0x66, 0x66, 0xFF},
    {0xBF, 0xBF, 0xBF, 0xFF},
};

static cXy l_texCoord[] = {
    {0.862864f, 0.532151f},
    {0.864665f, 1.0f},
    {0.878197f, 1.0f},
    {0.878197f, 0.53125f},
    {0.0f, 0.73413f},
    {0.15625f, 0.625f},
    {0.156459f, 0.375f},
    {0.0f, 0.259522f},
    {-0.15625f, 0.375f},
    {-0.15625f, 0.625f},
    {0.5f, 1.0f},
    {1.0f, 0.0f},
    {0.0f, 0.0f},
    {0.878197f, 0.990122f},
    {0.878197f, 0.871582f},
    {0.878197f, 0.625094f},
};

#include "assets/l_Oba_swood_noneDL.h"
#include "assets/l_Oba_swood_a_cuttDL.h"
#include "assets/l_Oba_swood_a_cutuDL.h"
#include "assets/l_Oba_swood_a_hapaDL.h"
#include "assets/l_Oba_swood_a_mikiDL.h"

#include "assets/l_matDL__d_tree.h"
l_matDL__d_tree(l_Txa_swood_aTEX);

#include "assets/l_Txa_kage_32TEX.h"
const u16 l_Txa_kage_32TEX__width = 32;
const u16 l_Txa_kage_32TEX__height = 32;

u8 g_dTree_shadowPos[][3] = {
    {0xB5, 0x00, 0x4B},
    {0x4B, 0x00, 0x4B},
    {0xB5, 0x00, 0xB5},
    {0x4B, 0x00, 0xB5},
};

u8 g_dTree_shadowTexCoord[][2] = {
    {0x00, 0x00},
    {0x01, 0x00},
    {0x01, 0x01},
    {0x00, 0x01},
};

#include "assets/g_dTree_Oba_kage_32DL.h"

#include "assets/g_dTree_shadowMatDL.h"
g_dTree_shadowMatDL(l_Txa_kage_32TEX);

const u32 g_dTree_Oba_kage_32DL_SIZE = sizeof(g_dTree_Oba_kage_32DL);
const u32 g_dTree_shadowMatDL_SIZE = sizeof(g_dTree_shadowMatDL);

static bool l_CutSoundFlag;

/* 800787BC-80078960       .text WorkCo__12dTree_data_cFP10fopAc_ac_cUli */
void dTree_data_c::WorkCo(fopAc_ac_c* i_actor, u32, int) {
    if (field_0x001) {
        return;
    }

    if (mAnimIdx < 8) {
        dTree_anm_c* anm = dComIfGp_getTree()->getAnm(mAnimIdx);
        s32 newAnm = dComIfGp_getTree()->newAnm(anm->field_0x02);
        if (newAnm < 0) {
            return;
        }
        mAnimIdx = newAnm;
    }

    cXyz vel;
    vel.x = mPos.x - i_actor->current.pos.x;
    vel.y = mPos.y - i_actor->current.pos.y;
    vel.z = mPos.z - i_actor->current.pos.z;
    vel.abs2XZ();

    dTree_anm_c* anm = dComIfGp_getTree()->getAnm(mAnimIdx);
    
    s16 angle = cM_atan2s(vel.x, vel.z);
    f32 cos = cM_scos(i_actor->current.angle.y - angle);
    if (cos > 0.9f && fopAcM_GetName(i_actor) == fpcNm_PLAYER_e) {
        ((daPy_py_c*)i_actor)->onFrollCrashFlg(7);
    }
    
    f32 var_f1 = cLib_maxLimit(std::abs(i_actor->speedF * 50.0f), 4000.0f);
    if (std::fabsf(anm->mAnimTimer) < std::fabsf(var_f1 * cos)) {
        anm->mAnimTimer = var_f1 * cos;
        anm->field_0x0a = angle;
    }
}

/* 80078960-80078CC0       .text WorkAt_NoCutAnim__12dTree_data_cFP10fopAc_ac_cUliP15dCcMassS_HitInfP8cCcD_Obj */
void dTree_data_c::WorkAt_NoCutAnim(fopAc_ac_c* i_actor, u32, int i_roomNo, dCcMassS_HitInf* i_hitInf, cCcD_Obj* i_hitObj) {
    if (field_0x001) {
        return;
    }

    if (mAnimIdx < 8) {
        dTree_anm_c* anm = dComIfGp_getTree()->getAnm(mAnimIdx);
        s32 newAnm = dComIfGp_getTree()->newAnm(anm->field_0x02);
        if (newAnm < 0) {
            return;
        }
        mAnimIdx = newAnm;
    }

    dCcD_GObjInf* hitObjInf = dCcD_GetGObjInf(i_hitObj);
    cXyz vel = *hitObjInf->GetAtVecP();
    f32 mag = vel.absXZ();

    if (cM3d_IsZero(mag)) {
        if (fopAcM_GetName(i_actor) == fpcNm_PLAYER_e) {
            vel.x = mPos.x - i_actor->current.pos.x;
            vel.y = mPos.y - i_actor->current.pos.y;
            vel.z = mPos.z - i_actor->current.pos.z;
            mag = vel.absXZ();
        } else if (fopAcM_GetName(i_actor) == fpcNm_BOMB_e || fopAcM_GetName(i_actor) == fpcNm_Bomb2_e) {
            vel.x = mPos.x - i_actor->current.pos.x;
            vel.y = mPos.y - i_actor->current.pos.y;
            vel.z = mPos.z - i_actor->current.pos.z;
            mag = 200.0f - vel.absXZ();
            if (mag < 0.0f) {
                mag = 0.0f;
            }

            VECNormalize(&vel, &vel);
            VECScale(&vel, &vel, mag);
        }
    }

    dTree_anm_c* anm = dComIfGp_getTree()->getAnm(mAnimIdx);

    s16 var_r30 = cM_atan2s(vel.x, vel.z);
    f32 anm_timer = mag * 50.0f > 4000.0f ? 4000.0f : mag * 50.0f;
    if (std::fabsf(anm->mAnimTimer) < std::fabsf(anm_timer)) {
        anm->mAnimTimer = anm_timer;
        anm->field_0x0a = var_r30;
    }
}

/* 80078CC0-80078ED4       .text WorkAt__12dTree_data_cFP10fopAc_ac_cUliP15dCcMassS_HitInf */
void dTree_data_c::WorkAt(fopAc_ac_c* i_actor, u32 param_1, int i_roomNo, dCcMassS_HitInf* i_hitInf) {
    cCcD_Obj* hitObj = i_hitInf->GetAtHitObj();
    if (hitObj != NULL && (hitObj->ChkAtType(AT_TYPE_WIND) ||
        hitObj->ChkAtType(AT_TYPE_BOMB) ||
        hitObj->ChkAtType(AT_TYPE_FIRE) ||
        hitObj->ChkAtType(AT_TYPE_NORMAL_ARROW) ||
        hitObj->ChkAtType(AT_TYPE_FIRE_ARROW) ||
        hitObj->ChkAtType(AT_TYPE_ICE_ARROW) ||
        hitObj->ChkAtType(AT_TYPE_LIGHT_ARROW) ||
        hitObj->ChkAtType(AT_TYPE_HOOKSHOT)))
    {
        WorkAt_NoCutAnim(i_actor, param_1, i_roomNo, i_hitInf, hitObj);
    } else {
        cXyz vel;
        vel.x = mPos.x - i_actor->current.pos.x;
        vel.y = mPos.y - i_actor->current.pos.y;
        vel.z = mPos.z - i_actor->current.pos.z;
        vel.abs2XZ();

        s16 var_r30 = cM_atan2s(vel.x, vel.z);

        if (field_0x001) {
            return;
        }

        if (mAnimIdx < 8) {
            dTree_anm_c* anm = dComIfGp_getTree()->getAnm(mAnimIdx);
            s32 newAnm = dComIfGp_getTree()->newAnm(anm->field_0x02);
            if (newAnm < 0) {
                return;
            }
            mAnimIdx = newAnm;
        }

        field_0x001 = 1;
        dTree_anm_c* anm = dComIfGp_getTree()->getAnm(mAnimIdx);
        anm->field_0x0a = dComIfGp_getTree()->getPlayerSwordMoveAngY();
        anm->mAnimTimer = 0.0f;
        anm->field_0x10 = -2.0f;
        anm->field_0x14 = 12.0f;

        Mtx m;
        MTXScale(m, 0.4f, 1.0f, 0.4f);
        MTXConcat(mShadowMtx, m, mShadowMtx);

        if (!l_CutSoundFlag) {
            l_CutSoundFlag = true;
            mDoAud_seStart(JA_SE_OBJ_CUT_TREE_DOWN, &mPos, 0, dComIfGp_getReverb(i_roomNo));
        }

#if VERSION > VERSION_DEMO
        dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
#endif
    }
}

/* 80078ED4-80078FA8       .text hitCheck__12dTree_data_cFP10fopAc_ac_ci */
BOOL dTree_data_c::hitCheck(fopAc_ac_c*, int i_roomNo) {
    fopAc_ac_c* actor = NULL;
    dCcMassS_HitInf hitInf;
    u32 ret = dComIfG_Ccsp()->ChkMass(&mPos, &actor, &hitInf);

    if (ret == 0 || actor == NULL) {
        return 0;
    }

    if (ret & 2)
        WorkCo(actor, ret, i_roomNo);
    if (ret & 1)
        WorkAt(actor, ret, i_roomNo, &hitInf);

    return 0;
}

/* 80078FA8-8007945C       .text animation__12dTree_data_cFi */
void dTree_data_c::animation(int i_roomNo) {
    dTree_anm_c* anm = dComIfGp_getTree()->getAnm(mAnimIdx);
    
    if (!field_0x001) {
        f32 temp = anm->field_0x08 * -1.0f;
        anm->mAnimTimer += temp;
        anm->mAnimTimer *= 0.9f;
        s16 temp2 = anm->mAnimTimer;
        anm->field_0x08 += temp2;

        if (anm->field_0x08 * temp >= 0.0f) {
            f32 var_f0 = std::fabsf(anm->mAnimTimer);
            if (var_f0 < 40.0f) {
                anm->field_0x08 = 0;
                anm->mAnimTimer = 0.0f;

                int idx = (anm->field_0x02 >> 13) & 7;
                dTree_anm_c* anm2 = dComIfGp_getTree()->getAnm(idx);
                if (cLib_chaseAngleS(&anm->field_0x04, anm2->field_0x04, 800)
                    && cLib_chaseAngleS(&anm->field_0x06, anm2->field_0x06, 800))
                {
                    dComIfGp_getTree()->deleteAnm(mAnimIdx);
                    mAnimIdx = idx;
                }
            } else if (var_f0 > 400.0f) {
                cXyz pos(mPos.x, mPos.y + 203.0f, mPos.z);
                dComIfGp_particle_setSimple(dPa_name::ID_IT_JN_O_HAPPA01, &pos);
                mDoAud_seStart(JA_SE_OBJ_TREE_SWING, &mPos, 0, dComIfGp_getReverb(i_roomNo));
            }
        }

        anm->field_0x04 = anm->field_0x08;
    } else {
        f32 var_f0 = anm->field_0x10 * cM_ssin(anm->field_0x0a);
        f32 var_f0_2 = anm->field_0x10 * cM_scos(anm->field_0x0a);

        anm->field_0x14 += -2.0f;
        if (anm->field_0x14 < -40.0f) {
            anm->field_0x14 = -40.0f;
        }

        anm->field_0x18 += var_f0;
        anm->field_0x20 += var_f0_2;
        anm->field_0x1c += anm->field_0x14;

        if (anm->field_0x1c < -5.0f) {
            anm->field_0x1c = -5.0f;
            anm->field_0x10 = 0.0f;
        }

        cLib_chaseF(&anm->mAnimTimer, 1500.0f, 40.0f);

        if (anm->field_0x04 != 13600) {
            if (cLib_chaseAngleS(&anm->field_0x04, 13600, anm->mAnimTimer)) {
                static cXyz l_particleOffset(0.0f, 150.0f, 0.0f);
                static cXyz l_scale(1.6f, 1.6f, 1.6f);

                cXyz sp18;
                MTXMultVec(anm->field_0x24, &l_particleOffset, &sp18);

                JPABaseEmitter* emitter = dComIfGp_particle_setToon(dPa_name::ID_AK_JT_ELEMENTSMOKE00, &sp18, NULL, &l_scale, 0xAA, &mSmokeEcallback, i_roomNo, NULL, NULL, NULL);
                if (emitter != NULL) {
                    emitter->setRate(20.0f);
                    emitter->setSpread(1.0f);
                    emitter->setDirectionalSpeed(15.0f);
                    emitter->setLifeTime(60);
                    emitter->setMaxFrame(1);
                }

                sp18.y -= 50.0f;
                dComIfGp_particle_set(dPa_name::ID_IT_JN_HAPPA02, &sp18);

#if VERSION == VERSION_DEMO
                dComIfGp_getVibration().StartShock(4, -0x21, cXyz(0.0f, 1.0f, 0.0f));
#endif
            }
        } else if (anm->field_0x10 == 0.0f) {
            cLib_onBit<u8>(mState, 8);
            MTXCopy(anm->field_0x24, field_0x070);
            field_0x070[0][3] = mPos.x + anm->field_0x18;
            field_0x070[1][3] = mPos.y + anm->field_0x1c;
            field_0x070[2][3] = mPos.z + anm->field_0x20;

            dComIfGp_getTree()->deleteAnm(mAnimIdx);
            mAnimIdx = (anm->field_0x02 >> 13) & 7;
        }
    }
}

/* 8007945C-8007946C       .text newData__12dTree_room_cFP12dTree_data_c */
void dTree_room_c::newData(dTree_data_c* i_data) {
    i_data->mpNext = mpData;
    mpData = i_data;
}

/* 8007946C-800794D0       .text deleteData__12dTree_room_cFv */
void dTree_room_c::deleteData() {
    while (mpData != NULL) {
        cLib_setBit<u8>(mpData->mState, 0x00);
#if VERSION > VERSION_DEMO
        mDoAud_seDeleteObject(&mpData->mPos);
#endif
        mpData = mpData->mpNext;
    }
}

/* 800794D0-800795E8       .text __ct__14dTree_packet_cFv */
dTree_packet_c::dTree_packet_c() {
    dTree_data_c* data = mData;
    for (s32 i = 0; i < ARRAY_SIZE(mData); i++, data++)
        cLib_setBit<u8>(data->mState, 0x00);

    dTree_anm_c* anm = mAnm;
    for (s32 i = 0; i < ARRAY_SIZE(mAnm); i++, anm++)
        anm->mState = 0;

    s16 angle = 0;
    for (s32 i = 0; i < 8; i++, angle += 0x2000)
        setAnm(i, angle);
}

dPa_smokeEcallBack dTree_data_c::mSmokeEcallback(1, 1, 0, 1);

/* 800795E8-800795F4       .text __ct__12dTree_room_cFv */
dTree_room_c::dTree_room_c() {
    mpData = NULL;
}

/* 800795F4-80079600       .text __ct__11dTree_anm_cFv */
dTree_anm_c::dTree_anm_c() {
    mState = 0;
}

/* 80079600-8007960C       .text __ct__12dTree_data_cFv */
dTree_data_c::dTree_data_c() {
    cLib_setBit<u8>(mState, 0x00);
}

/* 8007960C-80079898       .text draw__14dTree_packet_cFv */
void dTree_packet_c::draw() {
    static GXVtxDescList l_shadowVtxDescList[] = {
        {GX_VA_POS, GX_INDEX8},
        {GX_VA_TEX0, GX_INDEX8},
        {GX_VA_NULL, GX_NONE},
    };
    static GXVtxAttrFmtList l_shadowVtxAttrFmtList[] = {
        {GX_VA_POS, GX_POS_XYZ, GX_S8, 0x00},
        {GX_VA_TEX0, GX_TEX_ST, GX_S8, 0x00},
        {GX_VA_NULL, GX_POS_XYZ, GX_S8, 0x00},
    };
    static GXVtxDescList l_vtxDescList[] = {
        {GX_VA_POS, GX_INDEX8},
        {GX_VA_CLR0, GX_INDEX8},
        {GX_VA_TEX0, GX_INDEX8},
        {GX_VA_NULL, GX_NONE},
    };
    static GXVtxAttrFmtList l_vtxAttrFmtList[] = {
        {GX_VA_POS, GX_POS_XYZ, GX_F32, 0x00},
        {GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0x00},
        {GX_VA_TEX0, GX_TEX_ST, GX_F32, 0x00},
        {GX_VA_NULL, GX_POS_XYZ, GX_S8, 0x00},
    };
    static struct {
        void* list;
        u32 nbytes;
    } l_modelDataStatus[] = {
        {&l_Oba_swood_noneDL,   0x20},
        {&l_Oba_swood_a_hapaDL, 0x160},
        {&l_Oba_swood_a_mikiDL, 0xC0},
        {&l_Oba_swood_a_cuttDL, 0xA0},
        {&l_Oba_swood_a_cutuDL, 0x60},
    };

    static GXColor l_shadowColor = {0x00, 0x00, 0x00, 0x64};

    static u8 l_modelStatus[2][3] = {0, 1, 2, 3, 1, 4};

    j3dSys.reinitGX();
#if VERSION > VERSION_JPN
    GXSetNumIndStages(0);
#endif
    GFSetVtxDescv(l_shadowVtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_shadowVtxAttrFmtList);
    GFSetArray(GX_VA_POS, g_dTree_shadowPos, 3);
    GFSetArray(GX_VA_TEX0, g_dTree_shadowTexCoord, 2);
    GXCallDisplayList(g_dTree_shadowMatDL, 0x80);
    GFSetTevColor(GX_TEVREG0, l_shadowColor);

    dTree_room_c* room = &mRoom[0];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mRoom); room++, i++) {
        dKy_tevstr_c* tevstr = dComIfGp_roomControl_getTevStr(i);
        dKy_GfFog_tevstr_set(tevstr);
        for (dTree_data_c* data = room->getData(); data != NULL; data = data->mpNext) {
            if (!cLib_checkBit<u8>(data->mState, 0x04)) {
                GFLoadPosMtxImm(data->field_0x0d0, GX_PNMTX0);
                GXCallDisplayList(g_dTree_Oba_kage_32DL, 0x20);
            }
        }
    }

    GFSetVtxDescv(l_vtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_vtxAttrFmtList);
    GFSetArray(GX_VA_POS, l_pos, sizeof(cXyz));
    GFSetArray(GX_VA_CLR0, l_color, sizeof(GXColor));
    GFSetArray(GX_VA_TEX0, l_texCoord, sizeof(cXy));
    GXCallDisplayList(l_matDL, 0xA0);

    room = &mRoom[0];
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mRoom); room++, i++) {
        dKy_tevstr_c* tevstr = dComIfGp_roomControl_getTevStr(i);
        GFSetTevColorS10(GX_TEVREG0, tevstr->mColorC0);
        GFSetTevColor(GX_TEVREG1, tevstr->mColorK0);
        dKy_GfFog_tevstr_set(tevstr);
        for (dTree_data_c* data = room->getData(); data != NULL; data = data->mpNext) {
            if (!cLib_checkBit<u8>(data->mState, 0x04)) {
                u8* var_r25 = l_modelStatus[data->field_0x001];
                if (data->field_0x003 != 0) {
                    GXColor sp;
                    sp.a = data->field_0x003;
                    GFSetTevColor(GX_TEVREG2, sp);
                    GFLoadPosMtxImm(data->field_0x010, GX_PNMTX0);
                    GXCallDisplayList(l_modelDataStatus[var_r25[0]].list,
                                      l_modelDataStatus[var_r25[0]].nbytes);
                    GXCallDisplayList(l_modelDataStatus[var_r25[1]].list,
                                      l_modelDataStatus[var_r25[1]].nbytes);
                }

                GFLoadPosMtxImm(data->field_0x040, GX_PNMTX0);
                GXCallDisplayList(l_modelDataStatus[var_r25[2]].list,
                                  l_modelDataStatus[var_r25[2]].nbytes);
            }
        }
    }

#if VERSION > VERSION_JPN
    J3DShape::resetVcdVatCache();
#endif
}

/* 80079898-80079B24       .text calc__14dTree_packet_cFv */
void dTree_packet_c::calc() {
    dTree_anm_c* anm = getAnm();

    for (s32 i = 0; i < 8; anm++, i++) {
        anm->field_0x06 = anm->field_0x02 + 100.0f + cM_scos((g_Counter.mTimer + (i * 250)) * 4000.0f) * 100.0f;
        anm->field_0x04 = 100.0f + cM_scos((g_Counter.mTimer + (i * 250)) * 1000.0f) * 100.0f;
    }

    int roomNo = dComIfGp_roomControl_getStayNo();
    dTree_data_c* data = mRoom[roomNo].getData();
    if (data != NULL) {
        daPy_py_c* player = (daPy_py_c*)dComIfGp_getPlayer(0);
        setPlayerCutFlg(player->getCutAtFlg());

        cXyz sp38;
        cXyz sp2C;
        sp38 = player->getSwordTopPos();

        sp2C = sp38 - player->current.pos;
        setPlayerSwordAngY(cM_atan2s(sp2C.x, sp2C.z));

        sp2C = getPlayerSwordTop() - sp38;
        setPlayerSwordMoveAngY(cM_atan2s(sp2C.x, sp2C.z));

        setPlayerSwordTop(sp38);

        l_CutSoundFlag = false;
        dComIfG_Ccsp()->SetMassAttr(40.0f, 200.0f, 19, 1);

        while (true) {
            if (!cLib_checkBit<u8>(data->mState, 0x08))
                data->hitCheck(player, roomNo);

            if (data->mAnimIdx >= 8)
                data->animation(roomNo);

            data = data->mpNext;
            if (data == NULL)
                break;
        }
    }
}

/* 80079B24-80079E6C       .text checkGroundY__FP12dTree_data_cR4cXyz */
f32 checkGroundY(dTree_data_c* i_data, cXyz& i_pos) {
    dBgS_GndChk chk;
    i_pos.y += 50.0f;
    chk.SetPos(&i_pos);
    f32 y = dComIfG_Bgsp()->GroundCross(&chk);
    i_pos.y -= 50.0f;

    cXyz norm;
    if (y <= -G_CM3D_F_INF) {
        y = i_pos.y;
        norm.set(0.0f, 1.0f, 0.0f);
    } else {
        norm = *dComIfG_Bgsp()->GetTriPla(chk)->GetNP();
    }

    f32 var_f4 = std::sqrtf(1.0f - (norm.x * norm.x));
    f32 var_f2;
    f32 var_f3;
    if (var_f4 != 0.0f) {
        var_f2 = norm.y * var_f4;
        var_f3 = -norm.z * var_f4;
    } else {
        var_f2 = 0.0f;
        var_f3 = 0.0f;
    }

    i_data->mShadowMtx[0][0] = var_f4;
    i_data->mShadowMtx[0][1] = norm.x;
    i_data->mShadowMtx[0][2] = 0.0f;
    i_data->mShadowMtx[0][3] = i_pos.x;

    i_data->mShadowMtx[1][0] = -norm.x * var_f2;
    i_data->mShadowMtx[1][1] = norm.y;
    i_data->mShadowMtx[1][2] = var_f3;
    i_data->mShadowMtx[1][3] = y + 1.0f;

    i_data->mShadowMtx[2][0] = norm.x * var_f3;
    i_data->mShadowMtx[2][1] = norm.z;
    i_data->mShadowMtx[2][2] = var_f2;
    i_data->mShadowMtx[2][3] = i_pos.z;

    return y;
}

/* 80079E6C-8007A14C       .text update__14dTree_packet_cFv */
void dTree_packet_c::update() {
    dTree_anm_c* anm = getAnm();
    for (int i = 0; i < (s32)ARRAY_SIZE(mAnm); i++, anm++) {
        mDoMtx_stack_c::YrotS(anm->field_0x0a);
        mDoMtx_stack_c::XrotM(anm->field_0x04);
        mDoMtx_stack_c::YrotM(anm->field_0x06 - anm->field_0x0a);
        mDoMtx_copy(mDoMtx_stack_c::get(), anm->field_0x24);

        mDoMtx_stack_c::YrotS(anm->field_0x0a);
        mDoMtx_stack_c::XrotM(anm->field_0x08);
        mDoMtx_stack_c::YrotM(anm->field_0x02 - anm->field_0x0a);
        mDoMtx_copy(mDoMtx_stack_c::get(), anm->field_0x54);
    }

    dTree_data_c* data = getData();
    anm = getAnm();

    s32 numPerFrame = 0;
    mDoLib_clipper::changeFar(mDoLib_clipper::getFar() * 1.8181819f);

    for (int i = 0; i < (s32)ARRAY_SIZE(mData); i++) {
        if (cLib_checkBit<u8>(data->mState, 2)) {
            if (cLib_checkBit<u8>(data->mState, 0x10) && numPerFrame < 4) {
                data->mPos.y = checkGroundY(data, data->mPos);
                cLib_offBit<u8>(data->mState, 0x10);
                numPerFrame++;
            }

            cXyz pos(data->mPos.x, data->mPos.y + 260.0f, data->mPos.z);
            if (mDoLib_clipper::clip(j3dSys.getViewMtx(), pos, 260.0f)) {
                cLib_onBit<u8>(data->mState, 0x04);
            } else {
                cLib_offBit<u8>(data->mState, 0x04);

                dTree_anm_c* var_r22 = &anm[data->mAnimIdx];
                if (cLib_checkBit<u8>(data->mState, 8)) {
                    mDoMtx_concat(j3dSys.getViewMtx(), data->field_0x070, data->field_0x010);
                    cLib_chaseUC(&data->field_0x003, 0, 8);
                } else {
                    var_r22->field_0x24[0][3] = data->mPos.x + var_r22->field_0x18;
                    var_r22->field_0x24[1][3] = data->mPos.y + var_r22->field_0x1c;
                    var_r22->field_0x24[2][3] = data->mPos.z + var_r22->field_0x20;
                    mDoMtx_concat(j3dSys.getViewMtx(), var_r22->field_0x24, data->field_0x010);
                }

                var_r22->field_0x54[0][3] = data->mPos.x;
                var_r22->field_0x54[1][3] = data->mPos.y;
                var_r22->field_0x54[2][3] = data->mPos.z;

                mDoMtx_concat(j3dSys.getViewMtx(), var_r22->field_0x54, data->field_0x040);
                mDoMtx_concat(j3dSys.getViewMtx(), data->mShadowMtx, data->field_0x0d0);
            }
        }
        data++;
    }

    mDoLib_clipper::resetFar();
    dComIfGd_setXluListBG();
    j3dSys.getDrawBuffer(1)->entryImm(this, 0);
    dComIfGd_setXluList();
}

/* 8007A14C-8007A238       .text setData__14dTree_packet_cFP12dTree_data_ciR4cXyzUci */
void dTree_packet_c::setData(dTree_data_c* i_data, int i_nextIdx, cXyz& i_pos, u8 param_3, int i_roomNo) {
    f32 y;
    if (fopOvlpM_IsPeek()) {
        y = checkGroundY(i_data, i_pos);
        cLib_setBit<u8>(i_data->mState, 0x02 | 0x04);
    } else {
        y = i_pos.y;
        cLib_setBit<u8>(i_data->mState, 0x02 | 0x04 | 0x10);
    }

    i_data->field_0x001 = param_3;
    i_data->field_0x003 = param_3 == 1 ? 0 : 0xFF;
    i_data->mAnimIdx = (u8)cM_rndF(7.0f);
    i_data->mPos.set(i_pos.x, y, i_pos.z);
    mRoom[i_roomNo].newData(i_data);
    mNextIdx = i_nextIdx;
}

/* 8007A238-8007A36C       .text newData__14dTree_packet_cFR4cXyzUci */
dTree_data_c* dTree_packet_c::newData(cXyz& i_pos, u8 param_1, int i_roomNo) {
    JUT_ASSERT(VERSION_SELECT(1601, 1603, 1608, 1608), 0 <= i_roomNo && i_roomNo < 64);

    dTree_data_c* data = &mData[mNextIdx];
    s32 i = mNextIdx;
    for (; i < (s32)ARRAY_SIZE(mData); data++, i++) {
        if (!cLib_checkBit<u8>(data->mState, 2)) {
            setData(data, i, i_pos, param_1, i_roomNo);
            return data;
        }
    }

    data = getData();
    for (i = 0; i < mNextIdx; data++, i++) {
        if (!cLib_checkBit<u8>(data->mState, 2)) {
            setData(data, i, i_pos, param_1, i_roomNo);
            return data;
        }
    }

    return NULL;
}

/* 8007A36C-8007A3DC       .text newAnm__14dTree_packet_cFs */
s32 dTree_packet_c::newAnm(s16 param_0) {
    dTree_anm_c* anm = &mAnm[8];
    for (s32 i = 8; i < 64 + 8; anm++, i++) {
        if (anm->mState == 0) {
            anm->mState = 1;
            anm->field_0x02 = param_0;
            anm->field_0x06 = param_0;
            anm->field_0x04 = 0;
            anm->field_0x08 = 0;
            anm->field_0x0a = 0;
            anm->mAnimTimer = 0;
            anm->field_0x10 = 0;
            anm->field_0x14 = 0;
            anm->field_0x18 = 0;
            anm->field_0x1c = 0;
            anm->field_0x20 = 0;
            return i;
        }
    }
    return -1;
}

/* 8007A3DC-8007A428       .text setAnm__14dTree_packet_cFis */
void dTree_packet_c::setAnm(int i_no, s16 param_1) {
    dTree_anm_c* anm = getAnm(i_no);
    anm->mState = 1;
    anm->field_0x02 = param_1;
    anm->field_0x06 = param_1;
    anm->field_0x04 = 0;
    anm->field_0x08 = 0;
    anm->field_0x0a = 0;
    anm->mAnimTimer = 0;
    anm->field_0x10 = 0;
    anm->field_0x14 = 0;
    anm->field_0x18 = 0;
    anm->field_0x1c = 0;
    anm->field_0x20 = 0;
}
