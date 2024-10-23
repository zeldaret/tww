//
// Generated by dtk
// Translation Unit: d_wood.cpp
//

#include "d/d_wood.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "JSystem/J3DGraphBase/J3DShape.h"
#include "JSystem/J3DU/J3DUClipper.h"
#include "JSystem/JMath/JMath.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "SSystem/SComponent/c_bg_s_gnd_chk.h"
#include "SSystem/SComponent/c_lib.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_bg_s_spl_grp_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "d/d_kankyo_wether.h"
#include "d/d_procname.h"
#include "d/d_tree.h"
#include "dolphin/gf/GFGeometry.h"
#include "dolphin/gf/GFTev.h"
#include "dolphin/gf/GFTransform.h"
#include "dolphin/gx/GXAttr.h"
#include "dolphin/gx/GXDisplayList.h"
#include "dolphin/types.h"
#include "m_Do/m_Do_lib.h"
#include "m_Do/m_Do_mtx.h"

// These belong in the d_tree compilation unit. But in order to match, they must
// be in this compilation unit so they can have a 16-bit offset, allowing us
// load their pointer using a single load immediate instruction
u8 g_dTree_shadowTexCoord[2];

//-----------------------------------------
// Types
//-----------------------------------------
typedef u8 ALIGN_DECL(32) jData;

typedef void (dWood::Anm_c::*modeProcFunc)(dWood::Packet_c *);

enum AttrSway_e {
    SWAY_LIGHT,
    SWAY_MEDIUM,
    SWAY_STRONG,
    SWAY_EXTREME,
};

struct AttrSway_c {
    /* 0x0 */ s16 phaseVelY;
    /* 0x2 */ s16 ampY;
    /* 0x4 */ s16 phaseVelX;
    /* 0x6 */ s16 ampX;
    /* 0x8 */ float phaseBiasX;
};
struct Attr_c {
    /* 0x0 */ AttrSway_c kSways[4][2];
    /* 0x60 */ u8 kCutCooldown;           // = 23
    /* 0x61 */ u8 kCutPosOffsetX;         // = 0
    /* 0x64 */ float kCutInitVelY;        // = 18.0f
    /* 0x68 */ float kCutYAccel;          // = -3.0f (Units per frame per frame)
    /* 0x6C */ float kCutZVel;            // = 2.5f (Units per frame)
    /* 0x70 */ float kCutPitchVel;        // = 8 (shortRad per frame)
    /* 0x74 */ float kUncutShadowScale;   // = 1.5f
    /* 0x78 */ float kCutShadowScale;     // = 0.3f
    /* 0x7c */ float kCollisionRad;       // = 80.0f;
    /* 0x80 */ float kCollisionRadCut;    // = 15.0f;
    /* 0x84 */ float kCollisionHeight;    // = 80.0f;
    /* 0x88 */ float kCollisionHeightCut; // = 15.0f;
    /* 0x8c */ float kClipRadius;         // = 100.0f;
    /* 0x90 */ float kClipCenterYOffset;  // = 40.0f;
    /* 0x94 */ u8 kPushBackCountdown;     // = 23
    /* 0x95 */ const u8 L_Alpha_Cutoff;   // = 0x80;
};

//-----------------------------------------
// Data
//-----------------------------------------
static Vec _pad0[1] = {};
static Vec _pad1[1] = {};

namespace dWood {
namespace {
// .data
jData l_Txa_swood_bTEX[0x800] = {};
u8 l_pos[0x2e8] = {};
u8 l_color[0x50] = {};
u8 l_texCoord[0x50] = {};
jData l_Oba_swood_bDL[0x11c] = {};
jData l_Oba_swood_b_cutDL[0xcb] = {};
jData l_matDL[0xa3] = {};

// .rodata
const Attr_c L_attr = {};
} // namespace
} // namespace dWood

//-----------------------------------------
// Constants
//-----------------------------------------
const s32 L_Room_Max = 64;
const float l_Ground_check_y_offset = 100.0f;
const float l_Ground_check_unk0 = 1.0E+9;
const double l_Ground_check_unk1 = 0.5;
const double l_Ground_check_unk2 = 3.0;
const float kGroundHeightBias = 1.0f;

//-----------------------------------------
// Helpers
//-----------------------------------------
namespace {
inline const Attr_c &attr() { return dWood::L_attr; }

inline const AttrSway_c &attr_sway(AttrSway_e swayID, int idx) {
    return attr().kSways[swayID][idx];
}
} // namespace

//-----------------------------------------
// Classes
//-----------------------------------------

/* 800BD678-800BD710       .text __ct__Q25dWood5Anm_cFv */
dWood::Anm_c::Anm_c() {
    int iVar1;
    int iVar2;

    MTXIdentity(mModelMtx);
    MTXIdentity(mTrunkModelMtx);
    mMode = Mode_Max;
    mCountdown = 0;
    mWindDir = 0;
    mWindPow = 0.0;
    mPosOffsetY = 0.0;
    mPosOffsetZ = 0.0;
    mVelY = 0.0;

    iVar1 = 0;
    for (u32 i = 0; i < 2; i++) {
        mPhaseY[iVar1] = 0;
        mPhaseX[iVar1] = 0;
        mAmpY[iVar1] = 0;
        mAmpX[iVar1] = 0;
        iVar1 = iVar1 + 1;
    }

    mNormAnimIdx = AnmID_Norm0;
    mAlphaScale = 0xff;
    return;
}

/* 800BD710-800BD800       .text play__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::play(dWood::Packet_c *i_packet) {
    if (mMode != 6) {
        static modeProcFunc mode_proc[] = {
            &dWood::Anm_c::mode_cut,       &dWood::Anm_c::mode_push_into,
            &dWood::Anm_c::mode_push_back, &dWood::Anm_c::mode_fan,
            &dWood::Anm_c::mode_norm,      &dWood::Anm_c::mode_to_norm,
        };
        (this->*mode_proc[mMode])(i_packet);
    }
    return;
}

/* 800BD800-800BD848       .text copy_angamp__Q25dWood5Anm_cFPCQ25dWood5Anm_c */
void dWood::Anm_c::copy_angamp(const dWood::Anm_c *other) {
    if (this == other) {
        return;
    }

    s32 iVar1 = 0;
    for (u32 i = 0; i < 2; i++) {
        mPhaseY[iVar1] = other->mPhaseY[iVar1];
        mPhaseX[iVar1] = other->mPhaseX[iVar1];
        mAmpY[iVar1] = other->mAmpY[iVar1];
        mAmpX[iVar1] = other->mAmpX[iVar1];
        iVar1 = iVar1 + 1;
    }
}

/* 800BD848-800BD8BC       .text mode_cut_init__Q25dWood5Anm_cFPCQ25dWood5Anm_cs
 */
void dWood::Anm_c::mode_cut_init(const dWood::Anm_c *, short targetAngle) {
    s32 iVar1 = 0;
    for (u32 i = 0; i < 2; i++) {
        mPhaseY[iVar1] = 0;
        mPhaseX[iVar1] = 0;
        mAmpY[iVar1] = 0;
        mAmpX[iVar1] = 0;
        iVar1 = iVar1 + 1;
    }

    mWindDir = targetAngle;
    mVelY = L_attr.kCutInitVelY;
    mPosOffsetY = 0.0;
    mPosOffsetZ = 0.0;
    mAlphaScale = 0xff;
    mCountdown = L_attr.kCutCooldown;
    mMode = Anm_c::Mode_Cut;
}

/* 800BD8BC-800BD9E4       .text mode_cut__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::mode_cut(dWood::Packet_c *) {
    /* Nonmatching */
    mVelY = mVelY + L_attr.kCutYAccel;
    if (mVelY < -40.0f) {
        mVelY = -40.0f;
    }

    mPosOffsetY = mPosOffsetY + mVelY;
    mPosOffsetZ = mPosOffsetZ + L_attr.kCutZVel;
    mPhaseX[0] = mPhaseX[0] + L_attr.kCutPitchVel;

    mDoMtx_YrotS(mDoMtx_stack_c::now, (int)mWindDir);
    mDoMtx_stack_c::transM(L_attr.kCutPosOffsetX, mPosOffsetY, mPosOffsetZ);
    mDoMtx_XrotM(mDoMtx_stack_c::now, mPhaseX[0]);
    mDoMtx_YrotM(mDoMtx_stack_c::now, -mWindDir);
    mDoMtx_copy(mDoMtx_stack_c::now, mModelMtx);

    // Fade out the bush as it falls
    if (mCountdown < 20) {
        int alphaScale = mAlphaScale - 14;
        if (alphaScale < 0) {
            alphaScale = 0;
        }
        mAlphaScale = (u8)alphaScale;
    }

    if (mCountdown > 0) {
        mCountdown = mCountdown + -1;
    }
}

/* 800BD9E4-800BDA38       .text
 * mode_push_into_init__Q25dWood5Anm_cFPCQ25dWood5Anm_cs */
void dWood::Anm_c::mode_push_into_init(const dWood::Anm_c *packet,
                                       short targetAngle) {
    copy_angamp(packet);
    mWindDir = targetAngle;
    mAlphaScale = 0xff;
    mCountdown = 2;
    mMode = Mode_PushInto;
}

/* 800BDA38-800BDC24       .text
 * mode_push_into__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::mode_push_into(dWood::Packet_c *packet) { /* Nonmatching */
}

/* 800BDC24-800BDC48       .text mode_push_back_init__Q25dWood5Anm_cFv */
void dWood::Anm_c::mode_push_back_init() {
    mCountdown = L_attr.kPushBackCountdown;
    mAlphaScale = 0xff;
    mMode = Mode_PushBack;
}

/* 800BDC48-800BDECC       .text
 * mode_push_back__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::mode_push_back(dWood::Packet_c *packet) { /* Nonmatching */
}

/* 800BDECC-800BDED0       .text mode_fan__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::mode_fan(dWood::Packet_c *) { /* Nonmatching */
}

/* 800BDED0-800BDF5C       .text mode_norm_init__Q25dWood5Anm_cFv */
void dWood::Anm_c::mode_norm_init() {
    mMode = Mode_Norm;

    for (u32 i = 0; i < 2; i++) {
        mPhaseY[i] = M_init_num * 0x2000;
        mPhaseX[i] = M_init_num * 0x2000;
        mAmpY[i] = attr_sway(SWAY_LIGHT, i).ampY;
        mAmpX[i] = attr_sway(SWAY_LIGHT, i).ampX;
    }

    mAlphaScale = 0xff;

    M_init_num++;
    M_init_num = M_init_num % 8;
}

/* 800BDF5C-800BE148       .text mode_norm__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::mode_norm(dWood::Packet_c *packet) {
    AttrSway_e swayID;
    if (mWindPow < 0.33f) {
        swayID = SWAY_LIGHT;
    } else {
        if (mWindPow < 0.66f) {
            swayID = SWAY_MEDIUM;
        } else {
            swayID = SWAY_STRONG;
        }
    }

    float rotY = 0.0f;
    float rotX = rotY;
    for (s32 i = 0; i < 2; i++) {
        const AttrSway_c *sway = &attr_sway(swayID, i);
        s32 phaseVelX = sway->phaseVelX;
        s16 ampY = sway->ampY;
        s16 ampX = sway->ampX;
        float phaseBiasX = sway->phaseBiasX;

        mPhaseY[i] += sway->phaseVelY;
        mPhaseX[i] += phaseVelX;
        cLib_chaseS(&mAmpY[i], ampY, 2);
        cLib_chaseS(&mAmpX[i], ampX, 2);

        rotY += mAmpY[i] * JMASCos(mPhaseY[i]);
        rotX += mAmpX[i] * (phaseBiasX + JMASCos(mPhaseX[i]));
    }

    mDoMtx_YrotS(mModelMtx, (s16)rotY + mWindDir); // Y Rotation (Yaw)
    mDoMtx_XrotM(mModelMtx, rotX);                 // X Rotation
    mDoMtx_YrotM(mModelMtx, -mWindDir);            // Y Rotation
}

/* 800BE148-800BE154       .text mode_norm_set_wind__Q25dWood5Anm_cFfs */
void dWood::Anm_c::mode_norm_set_wind(float windPow, short windDir) {
    mWindPow = windPow;
    mWindDir = windDir;
    return;
}
/* 800BE154-800BE1F0       .text
 * mode_to_norm_init__Q25dWood5Anm_cFQ25dWood7AnmID_e */
void dWood::Anm_c::mode_to_norm_init(dWood::AnmID_e anm_id_norm) {
    bool bVar1;
    u32 uVar2;

    JUT_ASSERT(0x4d7, (anm_id_norm >= 0) && (anm_id_norm < AnmID_Norm_Max));

    mode_to_norm_set_AnmID(anm_id_norm);
    mAlphaScale = 0xff;
    mCountdown = 0x14;
    mMode = Anm_c::Mode_ToNorm;
}

/* 800BE1F0-800BE428       .text mode_to_norm__Q25dWood5Anm_cFPQ25dWood8Packet_c
 */
void dWood::Anm_c::mode_to_norm(dWood::Packet_c *packet) {
    /* Nonmatching */
    Anm_c *normAnim = packet->get_anm_p(mode_to_norm_get_AnmID());

    AttrSway_e swayID;
    if (mWindPow < 0.33f) {
        swayID = SWAY_LIGHT;
    } else {
        if (mWindPow < 0.66f) {
            swayID = SWAY_MEDIUM;
        } else {
            swayID = SWAY_STRONG;
        }
    }

    cLib_chaseAngleS(&mWindDir, normAnim->mWindDir, 3000);

    float fVar1 = 0.0;
    float fVar5 = fVar1;

    for (s32 i = 0; i < 2; i++) {
        const AttrSway_c *sway = &attr_sway(swayID, i);
        float phaseBiasX = sway->phaseBiasX;
        s16 rotXStep = sway->phaseVelX + 3000;

        cLib_chaseS(&mPhaseY[i], normAnim->mPhaseY[i], sway->phaseVelY + 3000);
        cLib_chaseS(&mPhaseX[i], normAnim->mPhaseX[i], rotXStep);
        cLib_chaseS(&mAmpY[i], normAnim->mAmpY[i], 0xf);
        cLib_chaseS(&mAmpX[i], normAnim->mAmpX[i], 0xf);

        fVar1 += mAmpY[i] * JMASCos(mPhaseY[i]);
        fVar5 += mAmpX[i] * (phaseBiasX + JMASCos(mPhaseX[i]));
    }

    mDoMtx_YrotS(mModelMtx, (s16)fVar1 + mWindDir);
    mDoMtx_XrotM(mModelMtx, fVar5);
    mDoMtx_YrotM(mModelMtx, -mWindDir);

    if (mCountdown > 0) {
        mCountdown -= 1;
    }
}

/* 800BE428-800BE4DC       .text __ct__Q25dWood6Unit_cFv */
dWood::Unit_c::Unit_c() { clear(); }

/* 800BE4DC-800BE93C       .text set_ground__Q25dWood6Unit_cFv */
bool dWood::Unit_c::set_ground() {
    bool uVar4;

    cXyz pos(mPos.x, mPos.y + l_Ground_check_y_offset, mPos.z);

    // Cast the current position to the ground
    dBgS_ObjGndChk gndChk;
    gndChk.SetPos(&pos);
    f32 gndHeight = dComIfG_Bgsp()->GroundCross(&gndChk);

    if (gndHeight > l_Ground_check_unk0) {
        mPos.y = gndHeight;
        cM3dGPla *triPla = dComIfG_Bgsp()->GetTriPla(gndChk);

        cXyz gndNorm = *triPla->GetNP();
        float unkFloat = std::sqrtf(1.0f - gndNorm.x * gndNorm.x);

        float scaledNormY;
        float scaledNormZ;
        if (unkFloat != 0.0f) {
            scaledNormY = gndNorm.y * unkFloat;
            scaledNormZ = -gndNorm.z * unkFloat;
        } else {
            scaledNormY = 0.0f;
            scaledNormZ = 0.0f;
        }

        MtxP mtx = mDoMtx_stack_c::get();

        mtx[0][0] = unkFloat;
        mtx[0][1] = gndNorm.x;
        mtx[0][2] = 0.0f;
        mtx[0][3] = mPos.x;

        mtx[1][0] = -gndNorm.x * scaledNormY;
        mtx[1][1] = gndNorm.y;
        mtx[1][2] = scaledNormZ;
        mtx[1][3] = kGroundHeightBias + gndHeight;

        mtx[2][0] = gndNorm.x * scaledNormZ;
        mtx[2][1] = gndNorm.z;
        mtx[2][2] = scaledNormY;
        mtx[2][3] = mPos.z;
        mDoMtx_stack_c::scaleM(L_attr.kUncutShadowScale, kGroundHeightBias,
                               L_attr.kUncutShadowScale);
        mDoMtx_copy(mDoMtx_stack_c::now, mShadowModelMtx);
        return true;
    } else {
        return false;
    }
}

/* 800BE93C-800BEA28       .text set_mtx__Q25dWood6Unit_cFPQ25dWood5Anm_c */
void dWood::Unit_c::set_mtx(dWood::Anm_c *anim) {
    int iVar1;

    iVar1 = mAnmIdx;

    mDoMtx_copy(anim[iVar1].mModelMtx, mDoMtx_stack_c::get());
    mDoMtx_stack_c::now[0][3] = mDoMtx_stack_c::now[0][3] + mPos.x;
    mDoMtx_stack_c::now[1][3] = mDoMtx_stack_c::now[1][3] + mPos.y;
    mDoMtx_stack_c::now[2][3] = mDoMtx_stack_c::now[2][3] + mPos.z;
    mDoMtx_concat(j3dSys.getViewMtx(), mDoMtx_stack_c::now, mModelViewMtx);

    mDoMtx_copy(anim[iVar1].mTrunkModelMtx, mDoMtx_stack_c::get());
    mDoMtx_stack_c::now[0][3] = mPos.x;
    mDoMtx_stack_c::now[1][3] = mPos.y;
    mDoMtx_stack_c::now[2][3] = mPos.z;
    mDoMtx_concat(j3dSys.getViewMtx(), mDoMtx_stack_c::get(),
                  mTrunkModelViewMtx);

    mDoMtx_concat(j3dSys.getViewMtx(), mShadowModelMtx, mShadowModelViewMtx);
}

/* 800BEA28-800BEA50       .text clear__Q25dWood6Unit_cFv */
void dWood::Unit_c::clear() { cLib_memSet(this, 0, 0x18c); }

/* 800BEA50-800BEE9C       .text
 * cc_hit_before_cut__Q25dWood6Unit_cFPQ25dWood8Packet_c */
void dWood::Unit_c::cc_hit_before_cut(dWood::Packet_c *packet) {
    AnmID_e animIdx;
    AnmID_e oldAnimIdx;
    s16 targetAngle;

    dCcMassS_HitInf inf;
    fopAc_ac_c *actor;
    u32 ret = dComIfG_Ccsp()->ChkMass(&mPos, &actor, &inf);

    if (mAnimCooldown > 0) {
        mAnimCooldown -= 1;
    }

    // Evaluate for attacks that will not cut us down
    if (cLib_checkBit(ret, 0x01UL)) {
        cCcD_Obj *atHitObj = inf.GetAtHitObj();
        if (atHitObj != NULL && (atHitObj->ChkAtType(AT_TYPE_WIND) ||
                                 atHitObj->ChkAtType(AT_TYPE_BOMB) ||
                                 atHitObj->ChkAtType(AT_TYPE_FIRE) ||
                                 atHitObj->ChkAtType(AT_TYPE_NORMAL_ARROW) ||
                                 atHitObj->ChkAtType(AT_TYPE_FIRE_ARROW) ||
                                 atHitObj->ChkAtType(AT_TYPE_ICE_ARROW) ||
                                 atHitObj->ChkAtType(AT_TYPE_LIGHT_ARROW) ||
                                 atHitObj->ChkAtType(AT_TYPE_HOOKSHOT))) {

            // Clear the hit bit so that we don't get cut down
            ret &= ~0x01;

            if (actor != NULL && mAnimCooldown == 0) {
                animIdx = packet->search_anm(Anm_c::Mode_PushInto);
                mAnimCooldown = 20;

                // Play the cut sound
                mDoAud_seStart(JA_SE_OBJ_TREE_SWING, &mPos, 0, 0);

                // If we are currently performing a basic animation, assign a
                // new animation
                oldAnimIdx = mAnmIdx;
                if ((oldAnimIdx < 8) && (animIdx != AnmID_Norm_Invalid)) {
                    mAnmIdx = animIdx;
                }

                // If we were able to allocate an animation (or we already have
                // one), start the "PushInto" (shrinking) animation
                if ((mAnmIdx >= 8) && packet->get_anm_p(mAnmIdx)->get_mode() >=
                                          Anm_c::Mode_PushInto) {
                    targetAngle =
                        cLib_targetAngleY(&actor->current.pos, &mPos);
                    packet->get_anm_p(mAnmIdx)->mode_push_into_init(
                        packet->mAnm + oldAnimIdx, (s32)targetAngle);
                }
            }
        }
    }

    // Check for collisions that are not attacks
    if (cLib_checkBit(ret, 0x02UL) && actor && inf.GetCoHitObj() &&
        inf.GetCoHitObj()->GetStts()) {
        animIdx = packet->search_anm(Anm_c::Mode_PushInto);

        if (fopAcM_GetProfName(actor) == PROC_PLAYER &&
            inf.GetCoHitLen() >= 2.0f && mAnimCooldown == 0) {

            mAnimCooldown = 20;
            mDoAud_seStart(JA_SE_OBJ_TREE_SWING, &mPos, 0, 0);

            // If we are currently performing a basic animation, assign a new
            // animation
            oldAnimIdx = mAnmIdx;
            if ((oldAnimIdx < 8) && (animIdx != AnmID_Norm_Invalid)) {
                mAnmIdx = animIdx;
            }

            // If we were able to allocate an animation (or we already have
            // one), start the "PushInto" (shrinking) animation
            if ((mAnmIdx >= 8) && (packet->get_anm_p(mAnmIdx)->get_mode() >=
                                   Anm_c::Mode_PushInto)) {
                targetAngle = cLib_targetAngleY(&actor->current.pos, &mPos);
                packet->get_anm_p(mAnmIdx)->mode_push_into_init(
                    packet->mAnm + oldAnimIdx, (s32)targetAngle);
            }
        }
    }

    // Check for attacks that WILL cut us down
    if (cLib_checkBit(ret, 0x01UL)) {
        AnmID_e oldAnimIdx = mAnmIdx;

        if ((mAnmIdx < 8)) {
            animIdx = packet->search_anm(Anm_c::Mode_Cut);
            if (animIdx != AnmID_Norm_Invalid) {
                mAnmIdx = animIdx;
            }
        }

        if ((mAnmIdx >= 8)) {
            if (packet->get_anm_p(mAnmIdx)->get_mode() > Anm_c::Mode_Cut) {
                targetAngle = cLib_targetAngleY(&actor->current.pos, &mPos);
                packet->get_anm_p(mAnmIdx)->mode_cut_init(
                    packet->get_anm_p(oldAnimIdx), (s32)targetAngle);

                // Compute the color settings for particels
                g_env_light.settingTevStruct(TEV_TYPE_BG0, &mPos, &mTevStr);

                // Spawn cut down particles (a bunch of leaves)
                dComIfGp_particle_set(dPa_name::ID_CUT_L_TREE_DOWN, &mPos, NULL,
                                      NULL, 0xff, NULL, -1, &mTevStr.mColorK0,
                                      NULL, NULL);

                mDoAud_seStart(JA_SE_OBJ_CUT_L_TREE_DOWN, &mPos, 0, 0);

                float newShadowScale =
                    L_attr.kCutShadowScale / L_attr.kUncutShadowScale;

                mDoMtx_copy(mShadowModelMtx, mDoMtx_stack_c::get());
                mDoMtx_stack_c::scaleM(newShadowScale, 1.0, newShadowScale);
                mDoMtx_copy(mDoMtx_stack_c::get(), mShadowModelMtx);
            }
        }
    }
}

/* 800BEE9C-800BEEA0       .text
 * cc_hit_after_cut__Q25dWood6Unit_cFPQ25dWood8Packet_c */
void dWood::Unit_c::cc_hit_after_cut(dWood::Packet_c *) {}

/* 800BEEA0-800BEF78       .text proc__Q25dWood6Unit_cFPQ25dWood8Packet_c */
void dWood::Unit_c::proc(dWood::Packet_c *packet) {
    // If this unit is active, and performing a non-normal animation...
    if (cLib_checkBit(mFlags, STATE_ACTIVE)) {
        AnmID_e animIdx = mAnmIdx;

        if (animIdx >= 8) {
            Anm_c* anim = packet->get_anm_p(animIdx);
            Anm_c::Mode_e mode = anim->mMode;
            if (mode == Anm_c::Mode_ToNorm) {
                if (anim->mCountdown <= 0) {
                    mAnmIdx = anim->mode_to_norm_get_AnmID();
                    anim->mMode = Anm_c::Mode_Max;
                }
            } else if (mode == Anm_c::Mode_Cut) {
                if (anim->mCountdown <= 0) {
                    AnmID_e newAnimIdx = packet->search_anm(Anm_c::Mode_Norm);
                    mAnmIdx = newAnimIdx;
                    anim->mMode = Anm_c::Mode_Max;
                    cLib_onBit(mFlags, STATE_CUT);
                }
            } else if (mode == Anm_c::Mode_Max) {
                animIdx = packet->search_anm(Anm_c::Mode_Norm);
                mAnmIdx = animIdx;
            }
        }
    }
}

/* 800BEF78-800BEF84       .text __ct__Q25dWood6Room_cFv */
dWood::Room_c::Room_c() { mpUnit = (Unit_c *)0x0; }

/* 800BEF84-800BEF94       .text entry_unit__Q25dWood6Room_cFPQ25dWood6Unit_c
 */
void dWood::Room_c::entry_unit(dWood::Unit_c *unit) {
    unit->mpNext = mpUnit;
    mpUnit = unit;
    return;
}

/* 800BEF94-800BEFF0       .text delete_all_unit__Q25dWood6Room_cFv */
void dWood::Room_c::delete_all_unit() {
    Unit_c *unit;
    while (unit = mpUnit, unit != (Unit_c *)0x0) {
        mpUnit = unit->mpNext;
        mDoAud_zelAudio_c::getInterface()->seDeleteObject((Vec *)unit);
        unit->clear();
    }
}

/* 800BEFF0-800BF0D4       .text __ct__Q25dWood8Packet_cFv */
dWood::Packet_c::Packet_c() {
    u32 iVar1 = 0;
    u32 iVar2 = 0;
    for (s32 i = 0; i < 8; i++) {
        mAnm[i].mode_norm_init();
    }
}

/* 800BF194-800BF1C8       .text delete_room__Q25dWood8Packet_cFi */
void dWood::Packet_c::delete_room(int room_no) {
    mRoom[room_no].delete_all_unit();
}

/* 800BF1C8-800BF2D4       .text put_unit__Q25dWood8Packet_cFRC4cXyzi */
s32 dWood::Packet_c::put_unit(const cXyz &pos, int room_no) {
    JUT_ASSERT(0x6e0, (room_no >= 0) && (room_no < 64));

    const s32 unitCount = ARRAY_SIZE(mUnit);
    s32 unitIdx = search_empty_UnitID();
    if (unitIdx != unitCount) {
        Unit_c *unit = &mUnit[unitIdx];
        cLib_setBit(unit->mFlags, Unit_c::STATE_ACTIVE);
        unit->mPos.x = pos.x;
        unit->mPos.y = pos.y;
        unit->mPos.z = pos.z;
        unit->mAnmIdx = search_anm(Anm_c::Mode_Norm);
        s8 valid = unit->set_ground();
        if (valid & 0xff) {
            mRoom[room_no].entry_unit(unit);
        } else {
            unit->clear();
        }
    }
    return unitIdx;
}

/* 800BF2D4-800BF404       .text calc_cc__Q25dWood8Packet_cFv */
// Collision Calculations
void dWood::Packet_c::calc_cc() {
    /* Nonmatching */
    const s32 roomIdx = dStage_roomControl_c::mStayNo;

    if ((roomIdx >= 0) && (roomIdx < (s32)ARRAY_SIZE(mRoom))) {
        dComIfG_Ccsp()->SetMassAttr(L_attr.kCollisionRad,
                                    L_attr.kCollisionHeight, (u8)0x13, 1);

        Room_c *room = &mRoom[roomIdx];
        for (Unit_c *unit = room->mpUnit; unit != NULL; unit = unit->mpNext) {
            if (!cLib_checkBit(unit->mFlags, Unit_c::STATE_CUT)) {
                unit->cc_hit_before_cut(this);
            }
        }

        dComIfG_Ccsp()->SetMassAttr(L_attr.kCollisionRadCut,
                                    L_attr.kCollisionHeightCut, (u8)0x12, 1);
        for (Unit_c *unit = room->mpUnit; unit != NULL; unit = unit->mpNext) {
            if (cLib_checkBit(unit->mFlags, Unit_c::STATE_CUT)) {
                unit->cc_hit_after_cut(this);
            }
        }
    }
}

/* 800BF404-800BF4EC       .text calc__Q25dWood8Packet_cFv */
void dWood::Packet_c::calc() {
    calc_cc();

    cXyz *windDir = dKyw_get_wind_vec();
    float windVel = dKyw_get_wind_pow();
    s16 windAngle = cM_atan2s(windDir->x, windDir->z);

    for (s32 i = 0; i < (s32)8; i++) {
        mAnm[i].mode_norm_set_wind(windVel, (s32)windAngle);
    }

    for (s32 i = 0; i < (s32)ARRAY_SIZE(mAnm); i++) {
        mAnm[i].play(this);
    }

    for (s32 i = 0; i < (s32)ARRAY_SIZE(mUnit); i++) {
        mUnit[i].proc(this);
    }
}

/* 800BF4EC-800BF614       .text update__Q25dWood8Packet_cFv */
void dWood::Packet_c::update() {
    s32 i = 0;
    for (Unit_c *unit = mUnit; i < (s32)ARRAY_SIZE(mUnit); i++, unit++) {
        if (cLib_checkBit(unit->mFlags, Unit_c::STATE_ACTIVE)) {
            cXyz clipPos(unit->mPos.x, unit->mPos.y + L_attr.kClipCenterYOffset,
                         unit->mPos.z);
            s32 res = mDoLib_clipper::clip(j3dSys.getViewMtx(), clipPos,
                                           L_attr.kClipRadius);

            if (res != 0) {
                cLib_onBit(unit->mFlags, Unit_c::STATE_FRUSTUM_CULLED);
            } else {
                cLib_offBit(unit->mFlags, Unit_c::STATE_FRUSTUM_CULLED);
                unit->set_mtx(mAnm);
            }
        }
    }

    dComIfGd_setXluListBG();
    j3dSys.getDrawBuffer(0)->entryImm(this, 0);
    dComIfGd_setXluList();
}

/* 800BF614-800BF900       .text draw__Q25dWood8Packet_cFv */
void dWood::Packet_c::draw() {
    /* Nonmatching */
    u8 bVar1;
    int iVar2;
    int iVar3;
    uint uVar4;
    Unit_c *pUnit;
    int iVar6;
    int iVar7;
    GXColor local_48;
    GXColor local_44;
    GXColor local_40;
    GXColor local_38;
    GXColorS10 local_30;

    static GXVtxDescList l_shadowVtxDescList[] = {
        {GX_VA_POS, GX_INDEX8},
        {GX_VA_TEX0, GX_INDEX8},
        {GX_VA_NULL, GX_NONE},
    };
    static GXVtxAttrFmtList l_shadowVtxAttrFmtList[] = {
        {GX_VA_POS, GX_CLR_RGBA, GX_RGB8},
        {GX_VA_TEX0, GX_CLR_RGBA, GX_RGB8},
        {GX_VA_NULL, GX_CLR_RGBA, GX_RGB8},
    };
    static GXVtxDescList l_vtxDescList[] = {
        {GX_VA_POS, GX_INDEX8},
        {GX_VA_CLR0, GX_INDEX8},
        {GX_VA_TEX0, GX_INDEX8},
        {GX_VA_NULL, GX_NONE},
    };
    static GXVtxAttrFmtList l_vtxAttrFmtList[] = {
        {GX_VA_POS, GX_CLR_RGBA, GX_F32},
        {GX_VA_CLR0, GX_CLR_RGBA, GX_RGB8},
        {GX_VA_TEX0, GX_CLR_RGBA, GX_F32},
        {GX_VA_NULL, GX_CLR_RGBA, GX_RGB8},
    };
    static const GXColor l_shadowColor = {0x00, 0x00, 0x00, 0x64};

    // Assign the shadow material and draw state
    GFSetVtxDescv(l_shadowVtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_shadowVtxAttrFmtList);
    GFSetArray(GX_VA_POS, g_dTree_shadowPos, 3);
    GFSetArray(GX_VA_TEX0, g_dTree_shadowTexCoord, 2);
    dKy_GxFog_set();
    GXCallDisplayList(g_dTree_shadowMatDL, g_dTree_shadowMatDL_SIZE & ~0b11111);
    GFSetTevColor(GX_TEVREG0, l_shadowColor);

    // Draw the drop shadows for each active unit
    Room_c *room = &mRoom[0];
    void *dl = g_dTree_Oba_kage_32DL;
    const u32 dlSize = g_dTree_Oba_kage_32DL_SIZE;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mRoom); room++, i++) {
        for (Unit_c *data = room->mpUnit; data != NULL; data = data->mpNext) {
            if (!cLib_checkBit(data->mFlags, Unit_c::STATE_FRUSTUM_CULLED)) {
                GFLoadPosMtxImm(pUnit->mShadowModelViewMtx, 0);
                GXCallDisplayList(dl, dlSize);
            }
        }
    }

    // Assign the body and trunk material and draw state
    GXColor alphaColor = {0xff, 0xff, 0xff, 0xff};
    GFSetVtxDescv(l_vtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_vtxAttrFmtList);
    GFSetArray(GX_VA_POS, l_pos, 0xc);
    GFSetArray(GX_VA_CLR0, l_color, 4);
    GFSetArray(GX_VA_TEX0, l_texCoord, 8);
    GXCallDisplayList(l_matDL, 0xa0);
    GFSetAlphaCompare(GX_GREATER, L_attr.L_Alpha_Cutoff, GX_AOP_OR, GX_GREATER,
                      L_attr.L_Alpha_Cutoff);
    GFSetTevColor(GX_TEVREG2, alphaColor);

    // Draw the trunk and body for each active unit
    room = mRoom;
    for (s32 i = 0; i < (s32)ARRAY_SIZE(mRoom); room++, i++) {
        dKy_tevstr_c *tevStr = dComIfGp_roomControl_getTevStr(i);
        GFSetTevColorS10(GX_TEVREG0, tevStr->mColorC0);
        GFSetTevColor(GX_TEVREG1, tevStr->mColorK0);

        dKy_GfFog_tevstr_set(tevStr);

        for (Unit_c *data = room->mpUnit; data != NULL; data = data->mpNext) {
            if (!cLib_checkBit(data->mFlags, Unit_c::STATE_FRUSTUM_CULLED)) {
                if (!cLib_checkBit(data->mFlags, Unit_c::STATE_CUT)) {
                    u32 alphaScale = mAnm[pUnit->mAnmIdx].mAlphaScale;
                    alphaColor.a = alphaScale;

                    if ((alphaScale & 0xff) != 0xff) {
                        GFSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_GREATER,
                                          0); // Disable Alpha Test
                    }
                    GFSetTevColor(GX_TEVREG2, alphaColor);
                    GFLoadPosMtxImm(pUnit->mModelViewMtx, 0);
                    GXCallDisplayList(l_Oba_swood_bDL,
                                      ARRAY_SIZE(l_Oba_swood_bDL));

                    if ((alphaScale & 0xff) != 0xff) {
                        GFSetAlphaCompare(
                            GX_GREATER, L_attr.L_Alpha_Cutoff, GX_AOP_OR,
                            GX_GREATER,
                            L_attr.L_Alpha_Cutoff); // Alpha Test < 50%
                    }
                    alphaColor.a = 0xff;
                    GFSetTevColor(GX_TEVREG2, alphaColor);
                }
                GFLoadPosMtxImm(pUnit->mTrunkModelViewMtx, 0);
                GXCallDisplayList(l_Oba_swood_b_cutDL,
                                  ARRAY_SIZE(l_Oba_swood_b_cutDL));
            }
        }
    }
    J3DShape::sOldVcdVatCmd = 0;
}

/* 800BF900-800BF938       .text search_empty_UnitID__Q25dWood8Packet_cCFv */
s32 dWood::Packet_c::search_empty_UnitID() const {
    const Unit_c *unit;
    int idx = 0;
    unit = mUnit;

    for (s32 i = 0; i < ARRAY_SIZE(mUnit); i++) {
        if ((s32)unit->mFlags == 0) {
            return idx;
        }
        idx += 1;
        unit = unit + 1;
    }

    return ARRAY_SIZE(mUnit);
}

/* 800BF938-800BFA70       .text
 * search_anm__Q25dWood8Packet_cFQ35dWood5Anm_c6Mode_e */
dWood::AnmID_e dWood::Packet_c::search_anm(dWood::Anm_c::Mode_e i_mode) {
    /* Nonmatching */
    u32 animIdx;

    JUT_ASSERT(0x80d, (i_mode >= 0) && (i_mode < Anm_c::Mode_Max));

    if (i_mode == Anm_c::Mode_Norm) {
        static s32 anm_norm_num = 0;
        animIdx = anm_norm_num++;
        anm_norm_num = anm_norm_num % 8;
    } else {
        // Return the first anim slot which has an unset mode
        animIdx = 8;
        for (s32 i = 0; i < 64; i++) {
            if (mAnm[animIdx].mMode == Anm_c::Mode_Max) {
                return (AnmID_e)animIdx;
            }
            animIdx++;
        }

        // If none are available, return the first one which has a higher mode
        animIdx = 8;
        for (s32 i = 0; i < 64; i++) {
            if (i_mode < mAnm[animIdx].mMode) {
                return (AnmID_e)animIdx;
            }
            animIdx++;
        }

        // If no available anim slot is found, return -1
        animIdx = AnmID_Norm_Invalid;
    }

    return (AnmID_e)animIdx;
}
