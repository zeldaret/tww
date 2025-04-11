//
// Generated by dtk
// Translation Unit: d_wood.cpp
//

#include "d/d_wood.h"
#include "JAZelAudio/JAIZelBasic.h"
#include "JSystem/JUtility/JUTAssert.h"
#include "SSystem/SComponent/c_lib.h"
#include "d/d_bg_s_gnd_chk.h"
#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "d/d_kankyo_wether.h"
#include "d/d_procname.h"
#include "d/d_tree.h"
#include "d/d_cc_d.h"
#include "dolphin/gf/GFGeometry.h"
#include "dolphin/gf/GFTev.h"
#include "dolphin/gf/GFTransform.h"
#include "dolphin/gx/GXAttr.h"
#include "dolphin/gx/GXDisplayList.h"
#include "dolphin/gx/GXStruct.h"
#include "dolphin/types.h"
#include "m_Do/m_Do_lib.h"
#include "m_Do/m_Do_mtx.h"

#include "weak_data_1811.h" // IWYU pragma: keep

//-----------------------------------------
// Types
//-----------------------------------------
enum AttrSway_e {
    SWAY_LIGHT,
    SWAY_MEDIUM,
    SWAY_STRONG,
    SWAY_PUSH,
};

struct AttrSway_c {
    /* 0x0 */ s16 phaseVelY;
    /* 0x2 */ s16 ampY;
    /* 0x4 */ s16 phaseVelX;
    /* 0x6 */ s16 ampX;
    /* 0x8 */ f32 phaseBiasX;
};
struct Attr_c {
    /* 0x00 */ AttrSway_c kSways[4][2];
    /* 0x60 */ u8 kCutCooldown;         // = 20
    /* 0x61 */ u8 kCutFadeStart;        // = 20 (Countdown time at which bush starts to fade out)
    /* 0x62 */ u8 kCutAlphaFadeSpeed;   // = 14
    /* 0x64 */ f32 kCutInitVelY;        // = 18.0f
    /* 0x68 */ f32 kCutYAccel;          // = -3.0f (Units per frame per frame)
    /* 0x6C */ f32 kCutZVel;            // = 2.5f (Units per frame)
    /* 0x70 */ s16 kCutPitchVel;        // = 200 (shortRad per frame)
    /* 0x74 */ f32 kUncutShadowScale;   // = 1.5f
    /* 0x78 */ f32 kCutShadowScale;     // = 0.3f
    /* 0x7C */ f32 kCollisionRad;       // = 80.0f;
    /* 0x80 */ f32 kCollisionRadCut;    // = 15.0f;
    /* 0x84 */ f32 kCollisionHeight;    // = 80.0f;
    /* 0x88 */ f32 kCollisionHeightCut; // = 15.0f;
    /* 0x8C */ f32 kClipRadius;         // = 100.0f;
    /* 0x90 */ f32 kClipCenterYOffset;  // = 40.0f;
    /* 0x94 */ u8 kPushBackCountdown;   // = 23
    /* 0x95 */ u8 L_Alpha_Cutoff;       // = 0x80;
};

typedef void (dWood::Anm_c::*modeProcFunc)(dWood::Packet_c *);

//-----------------------------------------
// Data
//-----------------------------------------

namespace dWood {
namespace {
// .data

#include "assets/l_Txa_swood_bTEX.h"
const u16 l_Txa_swood_bTEX__width = 64;
const u16 l_Txa_swood_bTEX__height = 64;

Vec l_pos[] = {
    {0.000022f, 14.922843f, -89.982368f},
    {-77.927017f, 14.922843f, -44.991203f},
    {-77.927025f, 14.922843f, 44.991173f},
    {-0.000008f, 14.922843f, 89.982353f},
    {77.92701f, 14.922843f, 44.99118f},
    {77.92701f, 14.922843f, -44.99118f},
    {0.0f, 86.107872f, 0.0f},
    {48.073795f, 32.79335f, -83.266212f},
    {-48.073753f, 32.79335f, -83.266228f},
    {-96.147537f, 32.79335f, -0.000015f},
    {-48.073772f, 32.79335f, 83.266212f},
    {48.073757f, 32.79335f, 83.266212f},
    {96.14753f, 32.79335f, 0.0f},
    {0.0f, 94.79158f, 0.0f},
    {46.784023f, 67.793831f, -81.032257f},
    {-46.783981f, 67.793831f, -81.032272f},
    {-93.568001f, 67.793831f, -0.000015f},
    {-46.784004f, 67.793831f, 81.032257f},
    {46.783993f, 67.793831f, 81.032257f},
    {93.567993f, 67.793831f, 0.0f},
    {0.0f, 105.391602f, 0.0f},
    {28.882326f, 98.615974f, -50.02562f},
    {-28.882303f, 98.615974f, -50.025642f},
    {-57.764622f, 98.615974f, -0.000009f},
    {-28.882315f, 98.615974f, 50.02562f},
    {28.882305f, 98.615974f, 50.02562f},
    {57.764614f, 98.615974f, 0.0f},
    {0.0f, 109.061028f, 0.0f},
    {41.2393f, 1.173791f, -71.42852f},
    {-41.239262f, 1.173791f, -71.428535f},
    {-82.478554f, 1.173791f, -0.000013f},
    {-41.239281f, 1.173791f, 71.42852f},
    {41.239265f, 1.173791f, 71.42852f},
    {82.478539f, 1.173791f, 0.0f},
    {0.0f, 70.268173f, 0.0f},
    {0.000025f, 50.810505f, -97.695068f},
    {-84.6064f, 50.810505f, -48.847549f},
    {-84.606422f, 50.810505f, 48.847519f},
    {-0.00001f, 50.810505f, 97.695053f},
    {84.6064f, 50.810505f, 48.84753f},
    {84.6064f, 50.810505f, -48.847527f},
    {0.0f, 102.071098f, 0.0f},
    {0.000021f, 82.279785f, -80.035629f},
    {-69.312889f, 82.279785f, -40.017834f},
    {-69.312904f, 82.279785f, 40.017811f},
    {-0.000008f, 82.279785f, 80.035637f},
    {69.312889f, 82.279785f, 40.017818f},
    {69.312889f, 82.279785f, -40.017815f},
    {0.0f, 109.022469f, 0.0f},
    {3.255973f, 0.0f, -5.921541f},
    {3.255973f, 0.0f, 5.921541f},
    {-5.16166f, 0.0f, 0.0f},
    {0.114389f, 11.775252f, -0.249098f},
    {-0.862972f, 19.754194f, 8.598756f},
    {-9.357565f, 19.58444f, 11.268269f},
    {-8.081571f, 19.758448f, 3.069652f},
    {-2.221876f, 19.009287f, -8.072796f},
    {-9.50218f, 19.009287f, -4.024319f},
    {-8.414586f, 19.009287f, -12.021413f},
    {13.461897f, 22.025139f, 1.575613f},
    {5.560989f, 22.025139f, 4.229024f},
    {5.656257f, 22.025139f, -3.749505f},
};

GXColor l_color[] = {
    {0x7F, 0x7F, 0x7F, 0xFF},
    {0x98, 0x98, 0x99, 0xFF},
    {0x99, 0x99, 0x99, 0xFF},
    {0xCC, 0xCC, 0xCC, 0xFF},
    {0xFF, 0xFF, 0xFF, 0xFF},
    {0x66, 0x66, 0x66, 0xFF},
    {0xB2, 0xB2, 0xB2, 0xFF},
    {0xE5, 0xE5, 0xE5, 0xFF},
    {0xF4, 0xF4, 0xF4, 0xFF},
    {0xAB, 0xAB, 0xAB, 0xFF},
    {0xFC, 0xFC, 0xFC, 0xFF},
    {0xF7, 0xF7, 0xF7, 0xFF},
    {0xF8, 0xF8, 0xF8, 0xFF},
    {0xC3, 0xC3, 0xC3, 0xFF},
    {0xA1, 0xA1, 0xA1, 0xFF},
    {0xF5, 0xF5, 0xF5, 0xFF},
    {0xFB, 0xFB, 0xFB, 0xFF},
    {0x73, 0x73, 0x73, 0xFF},
    {0x43, 0x43, 0x43, 0xFF},
    {0x9A, 0x9A, 0x9A, 0xFF},
};

cXy l_texCoord[] = {
    {0.5f, 1.0f},
    {1.0f, 0.0f},
    {0.0f, 0.0f},
    {1.0f, 0.455793f},
    {1.0f, 0.75f},
    {0.705793f, 0.75f},
    {0.958472f, 1.0f},
    {0.792867f, 0.75f},
    {0.958472f, 0.75f},
    {0.792867f, 1.0f},
};

#include "assets/l_Oba_swood_bDL.h"
#include "assets/l_Oba_swood_b_cutDL.h"
#include "assets/l_matDL__d_wood.h"
l_matDL__d_wood(l_Txa_swood_bTEX);

// .rodata
const Attr_c L_attr = {
    /* kSways */ {
        /* SWAY_LIGHT */ {
            {
                /* phaseVelY  */ 0x00C8,
                /* ampY       */ 0x0050,
                /* phaseVelX  */ 0x05DC,
                /* ampX       */ 0x0032,
                /* phaseBiasX */ 0.6f,
            },
            {
                /* phaseVelY  */ 0x00B4,
                /* ampY       */ 0x001E,
                /* phaseVelX  */ 0x0C80,
                /* ampX       */ 0x000A,
                /* phaseBiasX */ 0.2f,
            },
        },
        /* SWAY_MEDIUM */ {
            {
                /* phaseVelY  */ 0x01F4,
                /* ampY       */ 0x0096,
                /* phaseVelX  */ 0x04B0,
                /* ampX       */ 0x0096,
                /* phaseBiasX */ 0.6f,
            },
            {
                /* phaseVelY  */ 0x02BC,
                /* ampY       */ 0x0032,
                /* phaseVelX  */ 0x0898,
                /* ampX       */ 0x001E,
                /* phaseBiasX */ 0.2f,
            },
        },
        /* SWAY_STRONG */ {
            {
                /* phaseVelY  */ 0x0258,
                /* ampY       */ 0x00C8,
                /* phaseVelX  */ 0x0898,
                /* ampX       */ 0x012C,
                /* phaseBiasX */ 0.6f,
            },
            {
                /* phaseVelY  */ 0x01BC,
                /* ampY       */ 0x001E,
                /* phaseVelX  */ 0x0FA0,
                /* ampX       */ 0x0032,
                /* phaseBiasX */ 0.2f,
            },
        },
        /* SWAY_PUSH */ {
            {
                /* phaseVelY  */ 0x0258,
                /* ampY       */ 0x00C8,
                /* phaseVelX  */ 0x1838,
                /* ampX       */ 0x01F4,
                /* phaseBiasX */ 0.6f,
            },
            {
                /* phaseVelY  */ 0x01BC,
                /* ampY       */ 0x001E,
                /* phaseVelX  */ 0x03E8,
                /* ampX       */ 0x0032,
                /* phaseBiasX */ 0.2f,
            },
        },
    },
    /* kCutCooldown        */ 0x14,
    /* kCutFadeStart       */ 0x14,
    /* kCutAlphaFadeSpeed  */ 0x0E,
    /* kCutInitVelY        */ 18.0f,
    /* kCutYAccel          */ -3.0f,
    /* kCutZVel            */ 2.5f,
    /* kCutPitchVel        */ 0x00C8,
    /* kUncutShadowScale   */ 1.5f,
    /* kCutShadowScale     */ 0.3f,
    /* kCollisionRad       */ 80.0f,
    /* kCollisionRadCut    */ 15.0f,
    /* kCollisionHeight    */ 80.0f,
    /* kCollisionHeightCut */ 15.0f,
    /* kClipRadius         */ 100.0f,
    /* kClipCenterYOffset  */ 40.0f,
    /* kPushBackCountdown  */ 0x23,
    /* L_Alpha_Cutoff      */ 0x80,
};
} // namespace
} // namespace dWood

//-----------------------------------------
// Constants
//-----------------------------------------
const s32 L_Room_Max = 64;
const f32 l_Ground_check_y_offset = 100.0f;
const f32 kGroundHeightBias = 1.0f;

const u32 l_Oba_swood_bDL_SIZE = 0x100;
const u32 l_Oba_swood_b_cutDL_SIZE = 0xc0;

s32 dWood::Anm_c::M_init_num = 0;

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
    MTXIdentity(mModelMtx);
    MTXIdentity(mTrunkModelMtx);
    mMode = Mode_Max;
    mCountdown = 0;
    mForceDir = 0;
    mWindPow = 0.0f;
    mPosOffsetY = 0.0f;
    mPosOffsetZ = 0.0f;
    mVelY = 0.0f;

    for (u32 i = 0; i < 2; i++) {
        mPhaseY[i] = 0;
        mPhaseX[i] = 0;
        mAmpY[i] = 0;
        mAmpX[i] = 0;
    }

    mNormAnimIdx = AnmID_Norm0;
    mAlphaScale = 0xff;
}

/* 800BD710-800BD800       .text play__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::play(dWood::Packet_c *i_packet) {
    if (mMode != Mode_Max) {
        static modeProcFunc mode_proc[] = {
            &dWood::Anm_c::mode_cut,       &dWood::Anm_c::mode_push_into,
            &dWood::Anm_c::mode_push_back, &dWood::Anm_c::mode_fan,
            &dWood::Anm_c::mode_norm,      &dWood::Anm_c::mode_to_norm,
        };
        (this->*mode_proc[mMode])(i_packet);
    }
}

/* 800BD800-800BD848       .text copy_angamp__Q25dWood5Anm_cFPCQ25dWood5Anm_c */
void dWood::Anm_c::copy_angamp(const dWood::Anm_c *other) {
    if (this == other) {
        return;
    }

    for (u32 i = 0; i < 2; i++) {
        mPhaseY[i] = other->mPhaseY[i];
        mPhaseX[i] = other->mPhaseX[i];
        mAmpY[i] = other->mAmpY[i];
        mAmpX[i] = other->mAmpX[i];
    }
}

/* 800BD848-800BD8BC       .text mode_cut_init__Q25dWood5Anm_cFPCQ25dWood5Anm_cs */
void dWood::Anm_c::mode_cut_init(const dWood::Anm_c *, s16 targetAngle) {
    for (u32 i = 0; i < 2; i++) {
        mPhaseY[i] = 0;
        mPhaseX[i] = 0;
        mAmpY[i] = 0;
        mAmpX[i] = 0;
    }

    mForceDir = targetAngle;
    mVelY = L_attr.kCutInitVelY;
    mPosOffsetY = 0.0f;
    mPosOffsetZ = 0.0f;
    mAlphaScale = 0xff;
    mCountdown = L_attr.kCutCooldown;
    mMode = Anm_c::Mode_Cut;
}

/* 800BD8BC-800BD9E4       .text mode_cut__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::mode_cut(dWood::Packet_c *) {
    mVelY = mVelY + L_attr.kCutYAccel;
    if (mVelY < -40.0f) {
        mVelY = -40.0f;
    }

    mPosOffsetY = mPosOffsetY + mVelY;
    mPosOffsetZ = mPosOffsetZ + L_attr.kCutZVel;
    mPhaseX[0] = mPhaseX[0] - L_attr.kCutPitchVel;

    mDoMtx_YrotS(mDoMtx_stack_c::now, mForceDir);
    mDoMtx_stack_c::transM(0.0f, mPosOffsetY, mPosOffsetZ);
    mDoMtx_XrotM(mDoMtx_stack_c::now, mPhaseX[0]);
    mDoMtx_YrotM(mDoMtx_stack_c::now, -mForceDir);
    mDoMtx_copy(mDoMtx_stack_c::now, mModelMtx);

    // Fade out the bush as it falls
    if (mCountdown < attr().kCutFadeStart) {
        int alphaScale = mAlphaScale;
        alphaScale -= attr().kCutAlphaFadeSpeed;
        if (alphaScale < 0) {
            alphaScale = 0;
        }
        mAlphaScale = (u8)alphaScale;
    }

    if ((s32)mCountdown > 0) {
        mCountdown = mCountdown + -1;
    }
}

/* 800BD9E4-800BDA38       .text mode_push_into_init__Q25dWood5Anm_cFPCQ25dWood5Anm_cs */
void dWood::Anm_c::mode_push_into_init(const dWood::Anm_c *anm, s16 targetAngle) {
    copy_angamp(anm);
    mForceDir = targetAngle;
    mAlphaScale = 0xff;
    mCountdown = 2;
    mMode = Mode_PushInto;
}

/* 800BDA38-800BDC24       .text mode_push_into__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::mode_push_into(dWood::Packet_c *packet) {
    if (--mCountdown <= 0) {
        mode_push_back_init();
    }
    else {
        f32 rotY = 0.0f;
        f32 rotX = rotY;
        for (s32 i = 0; i < 2; i++) {
            s32 phaseVelX = attr_sway(SWAY_PUSH, i).phaseVelX;
            s32 ampY = attr_sway(SWAY_PUSH, i).ampY;
            s32 ampX = attr_sway(SWAY_PUSH, i).ampX;
            f32 phaseBiasX = attr_sway(SWAY_PUSH, i).phaseBiasX;

            mPhaseY[i] += attr_sway(SWAY_PUSH, i).phaseVelY;
            cLib_chaseAngleS(&mPhaseX[i], 0, phaseVelX);
            cLib_chaseS(&mAmpY[i], ampY/4, 0x14);
            cLib_addCalcAngleS(&mAmpX[i], ampX, 8, 0x14, 5);
            
            rotY += mAmpY[i] * JMASCos(mPhaseY[i]);
            rotX +=  mAmpX[i] * (phaseBiasX + JMASCos(mPhaseX[i]));
        }

        mDoMtx_YrotS(mModelMtx, (s16)rotY + mForceDir);
        mDoMtx_XrotM(mModelMtx, (s32)rotX);
        mDoMtx_YrotM(mModelMtx, -mForceDir);
    }
}

/* 800BDC24-800BDC48       .text mode_push_back_init__Q25dWood5Anm_cFv */
void dWood::Anm_c::mode_push_back_init() {
    mCountdown = L_attr.kPushBackCountdown;
    mAlphaScale = 0xff;
    mMode = Mode_PushBack;
}

/* 800BDC48-800BDECC       .text mode_push_back__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::mode_push_back(dWood::Packet_c *packet) {
    if (--mCountdown <= 0) {
        AnmID_e animIdx = packet->search_anm(Anm_c::Mode_Norm);
        mode_to_norm_init(animIdx);
    }
    else {
        f32 t = mCountdown * (1.0f / L_attr.kPushBackCountdown);

        f32 rotY = 0.0;
        f32 rotX = rotY;
        for (s32 i = 0; i < 2; i++) {
            s32 phaseVelX = attr_sway(SWAY_PUSH, i).phaseVelX;
            s16 ampY = t * attr_sway(SWAY_PUSH, i).ampY;
            s16 ampX = t * attr_sway(SWAY_PUSH, i).ampX;
            f32 phaseBiasX = attr_sway(SWAY_PUSH, i).phaseBiasX;

            mPhaseY[i] += attr_sway(SWAY_PUSH, i).phaseVelY;
            mPhaseX[i] += phaseVelX;
            cLib_chaseS(&mAmpY[i], (s32)ampY, 0x14);
            cLib_chaseS(&mAmpX[i], (s32)ampX, 0x14);

            rotY += mAmpY[i] * JMASCos(mPhaseY[i]);
            rotX +=  mAmpX[i] * (phaseBiasX + JMASCos(mPhaseX[i]));
        }

        mDoMtx_YrotS(mModelMtx, (s16)rotY + mForceDir);
        mDoMtx_XrotM(mModelMtx, (s32)rotX);
        mDoMtx_YrotM(mModelMtx, -mForceDir);
    }
}

/* 800BDECC-800BDED0       .text mode_fan__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::mode_fan(dWood::Packet_c *) {}

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

    f32 rotY = 0.0f;
    f32 rotX = rotY;
    for (s32 i = 0; i < 2; i++) {
        s32 phaseVelX = attr_sway(swayID, i).phaseVelX;
        s16 ampY = attr_sway(swayID, i).ampY;
        s16 ampX = attr_sway(swayID, i).ampX;
        f32 phaseBiasX = attr_sway(swayID, i).phaseBiasX;

        mPhaseY[i] += attr_sway(swayID, i).phaseVelY;
        mPhaseX[i] += phaseVelX;
        cLib_chaseS(&mAmpY[i], ampY, 2);
        cLib_chaseS(&mAmpX[i], ampX, 2);

        rotY += mAmpY[i] * JMASCos(mPhaseY[i]);
        rotX += mAmpX[i] * (phaseBiasX + JMASCos(mPhaseX[i]));
    }

    mDoMtx_YrotS(mModelMtx, (s16)rotY + mForceDir); // Y Rotation (Yaw)
    mDoMtx_XrotM(mModelMtx, rotX);                  // X Rotation
    mDoMtx_YrotM(mModelMtx, -mForceDir);            // Y Rotation
}

/* 800BE148-800BE154       .text mode_norm_set_wind__Q25dWood5Anm_cFfs */
void dWood::Anm_c::mode_norm_set_wind(f32 windPow, s16 windDir) {
    mWindPow = windPow;
    mForceDir = windDir;
}

/* 800BE154-800BE1F0       .text mode_to_norm_init__Q25dWood5Anm_cFQ25dWood7AnmID_e */
void dWood::Anm_c::mode_to_norm_init(dWood::AnmID_e anm_id_norm) {
    JUT_ASSERT(1239, (anm_id_norm >= 0) && (anm_id_norm < AnmID_Norm_Max));

    mode_to_norm_set_AnmID(anm_id_norm);
    mAlphaScale = 0xff;
    mCountdown = 0x14;
    mMode = Anm_c::Mode_ToNorm;
}

/* 800BE1F0-800BE428       .text mode_to_norm__Q25dWood5Anm_cFPQ25dWood8Packet_c */
void dWood::Anm_c::mode_to_norm(dWood::Packet_c *packet) {
    const Anm_c *normAnim = packet->get_anm_p(mode_to_norm_get_AnmID());

    AttrSway_e swayID;
    if (normAnim->mWindPow < 0.33f) {
        swayID = SWAY_LIGHT;
    } else {
        if (normAnim->mWindPow < 0.66f) {
            swayID = SWAY_MEDIUM;
        } else {
            swayID = SWAY_STRONG;
        }
    }

    cLib_chaseAngleS(&mForceDir, normAnim->mForceDir, 3000);

    f32 rotY = 0.0f;
    f32 rotX = rotY;
    for (s32 i = 0; i < 2; i++) {
        f32 phaseBiasX = attr_sway(swayID, i).phaseBiasX;
        s32 phaseVelX = attr_sway(swayID, i).phaseVelX;
        s16 rotXStep = phaseVelX + 3000;

        cLib_chaseS(&mPhaseY[i], normAnim->mPhaseY[i], attr_sway(swayID, i).phaseVelY + 3000);
        cLib_chaseS(&mPhaseX[i], normAnim->mPhaseX[i], rotXStep);
        cLib_chaseS(&mAmpY[i], normAnim->mAmpY[i], 0xf);
        cLib_chaseS(&mAmpX[i], normAnim->mAmpX[i], 0xf);

        rotY += mAmpY[i] * JMASCos(mPhaseY[i]);
        rotX += mAmpX[i] * (phaseBiasX + JMASCos(mPhaseX[i]));
    }

    mDoMtx_YrotS(mModelMtx, (s16)rotY + mForceDir);
    mDoMtx_XrotM(mModelMtx, rotX);
    mDoMtx_YrotM(mModelMtx, -mForceDir);

    if (mCountdown > 0) {
        mCountdown -= 1;
    }
}

/* 800BE428-800BE4DC       .text __ct__Q25dWood6Unit_cFv */
dWood::Unit_c::Unit_c() {
    clear();
}

/* 800BE4DC-800BE93C       .text set_ground__Q25dWood6Unit_cFv */
bool dWood::Unit_c::set_ground() {
    cXyz pos(mPos.x, mPos.y + l_Ground_check_y_offset, mPos.z);

    // Cast the current position to the ground
    dBgS_ObjGndChk gndChk;
    gndChk.SetPos(&pos);
    f32 gndHeight = dComIfG_Bgsp()->GroundCross(&gndChk);

    if (gndHeight > C_BG_MIN_HEIGHT) {
        mPos.y = gndHeight;
        cM3dGPla *triPla = dComIfG_Bgsp()->GetTriPla(gndChk);

        cXyz gndNorm = *triPla->GetNP();
        f32 unkFloat = std::sqrtf(1.0f - gndNorm.x * gndNorm.x);

        f32 scaledNormY;
        f32 scaledNormZ;
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
    int anmIdx = mAnmIdx;

    mDoMtx_copy(anim[anmIdx].mModelMtx, mDoMtx_stack_c::get());
    mDoMtx_stack_c::now[0][3] = mDoMtx_stack_c::now[0][3] + mPos.x;
    mDoMtx_stack_c::now[1][3] = mDoMtx_stack_c::now[1][3] + mPos.y;
    mDoMtx_stack_c::now[2][3] = mDoMtx_stack_c::now[2][3] + mPos.z;
    mDoMtx_concat(j3dSys.getViewMtx(), mDoMtx_stack_c::now, mModelViewMtx);

    mDoMtx_copy(anim[anmIdx].mTrunkModelMtx, mDoMtx_stack_c::get());
    mDoMtx_stack_c::now[0][3] = mPos.x;
    mDoMtx_stack_c::now[1][3] = mPos.y;
    mDoMtx_stack_c::now[2][3] = mPos.z;
    mDoMtx_concat(j3dSys.getViewMtx(), mDoMtx_stack_c::get(), mTrunkModelViewMtx);

    mDoMtx_concat(j3dSys.getViewMtx(), mShadowModelMtx, mShadowModelViewMtx);
}

/* 800BEA28-800BEA50       .text clear__Q25dWood6Unit_cFv */
void dWood::Unit_c::clear() {
    cLib_memSet(this, 0, 0x18c);
}

/* 800BEA50-800BEE9C       .text cc_hit_before_cut__Q25dWood6Unit_cFPQ25dWood8Packet_c */
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
                    targetAngle = cLib_targetAngleY(&actor->current.pos, &mPos);
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
                dComIfGp_particle_set(dPa_name::ID_COMMON_CUT_L_TREE_DOWN, &mPos, NULL,
                                      NULL, 0xff, NULL, -1, &mTevStr.mColorK0,
                                      NULL, NULL);

                mDoAud_seStart(JA_SE_OBJ_CUT_L_TREE_DOWN, &mPos, 0, 0);

                f32 newShadowScale = L_attr.kCutShadowScale / L_attr.kUncutShadowScale;

                mDoMtx_copy(mShadowModelMtx, mDoMtx_stack_c::get());
                mDoMtx_stack_c::scaleM(newShadowScale, 1.0f, newShadowScale);
                mDoMtx_copy(mDoMtx_stack_c::get(), mShadowModelMtx);
            }
        }
    }
}

/* 800BEE9C-800BEEA0       .text cc_hit_after_cut__Q25dWood6Unit_cFPQ25dWood8Packet_c */
void dWood::Unit_c::cc_hit_after_cut(dWood::Packet_c *) {}

/* 800BEEA0-800BEF78       .text proc__Q25dWood6Unit_cFPQ25dWood8Packet_c */
void dWood::Unit_c::proc(dWood::Packet_c *packet) {
    // If this unit is active, and performing a non-normal animation...
    if (cLib_checkBit(mFlags, STATE_ACTIVE)) {
        AnmID_e animIdx = mAnmIdx;

        if (animIdx >= 8) {
            Anm_c *anim = packet->get_anm_p(animIdx);
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
dWood::Room_c::Room_c() {
    mpUnit = NULL;
}

/* 800BEF84-800BEF94       .text entry_unit__Q25dWood6Room_cFPQ25dWood6Unit_c */
void dWood::Room_c::entry_unit(dWood::Unit_c *unit) {
    unit->mpNext = mpUnit;
    mpUnit = unit;
}

/* 800BEF94-800BEFF0       .text delete_all_unit__Q25dWood6Room_cFv */
void dWood::Room_c::delete_all_unit() {
    Unit_c *unit;
    while (unit = mpUnit, unit != NULL) {
        mpUnit = unit->mpNext;
        mDoAud_zelAudio_c::getInterface()->seDeleteObject((Vec *)unit);
        unit->clear();
    }
}

/* 800BEFF0-800BF0D4       .text __ct__Q25dWood8Packet_cFv */
dWood::Packet_c::Packet_c() {
    for (s32 i = 0; i < 8; i++) {
        mAnm[i].mode_norm_init();
    }
}

/* 800BF110-800BF194       .text __dt__Q25dWood8Packet_cFv */
dWood::Packet_c::~Packet_c() {};

/* 800BF194-800BF1C8       .text delete_room__Q25dWood8Packet_cFi */
void dWood::Packet_c::delete_room(int room_no) {
    mRoom[room_no].delete_all_unit();
}

/* 800BF1C8-800BF2D4       .text put_unit__Q25dWood8Packet_cFRC4cXyzi */
s32 dWood::Packet_c::put_unit(const cXyz &pos, int room_no) {
    JUT_ASSERT(1760, (room_no >= 0) && (room_no < L_Room_Max));

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
    int roomIdx = dComIfGp_roomControl_getStayNo();

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
    f32 windVel = dKyw_get_wind_pow();
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
            cXyz clipPos(unit->mPos.x, unit->mPos.y + L_attr.kClipCenterYOffset, unit->mPos.z);
            s32 res = mDoLib_clipper::clip(j3dSys.getViewMtx(), clipPos, L_attr.kClipRadius);

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
    u8 bVar1;
    int iVar2;
    int iVar3;
    uint uVar4;
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
        {GX_VA_POS, GX_CLR_RGBA, GX_RGB8, 0x00},
        {GX_VA_TEX0, GX_CLR_RGBA, GX_RGB8, 0x00},
        {GX_VA_NULL, GX_CLR_RGBA, GX_RGB8, 0x00},
    };
    static GXVtxDescList l_vtxDescList[] = {
        {GX_VA_POS, GX_INDEX8},
        {GX_VA_CLR0, GX_INDEX8},
        {GX_VA_TEX0, GX_INDEX8},
        {GX_VA_NULL, GX_NONE},
    };
    static GXVtxAttrFmtList l_vtxAttrFmtList[] = {
        {GX_VA_POS, GX_CLR_RGBA, GX_F32, 0x00},
        {GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0x00},
        {GX_VA_TEX0, GX_CLR_RGBA, GX_F32, 0x00},
        {GX_VA_NULL, GX_CLR_RGBA, GX_RGB8, 0x00},
    };
    static GXColor l_shadowColor = {0x00, 0x00, 0x00, 0x64};

    // Assign the shadow material and draw state
    GFSetVtxDescv(l_shadowVtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_shadowVtxAttrFmtList);
    GFSetArray(GX_VA_POS, g_dTree_shadowPos, 3);
    GFSetArray(GX_VA_TEX0, g_dTree_shadowTexCoord, 2);
    dKy_GxFog_set();
    GXCallDisplayList(g_dTree_shadowMatDL, g_dTree_shadowMatDL_SIZE & ~0b11111);
    GFSetTevColor(GX_TEVREG0, l_shadowColor);

    // Draw the drop shadows for each active unit
    Room_c* room;
    int i;

    for (i = 0, room = mRoom; i < (s32)ARRAY_SIZE(mRoom); room++, i++) {
        for (Unit_c *data = room->mpUnit; data != NULL; data = data->mpNext) {
            if (!cLib_checkBit(data->mFlags, Unit_c::STATE_FRUSTUM_CULLED)) {
                GFLoadPosMtxImm(data->mShadowModelViewMtx, 0);
                GXCallDisplayList(g_dTree_Oba_kage_32DL, g_dTree_Oba_kage_32DL_SIZE  & ~0b11111); // This is probably an inline
            }
        }
    }

    // Assign the body and trunk material and draw state
    GXColor alphaColor = {0xff, 0xff, 0xff, 0xff};
    GFSetVtxDescv(l_vtxDescList);
    GFSetVtxAttrFmtv(GX_VTXFMT0, l_vtxAttrFmtList);
    GFSetArray(GX_VA_POS, l_pos, sizeof(*l_pos));
    GFSetArray(GX_VA_CLR0, l_color, sizeof(*l_color));
    GFSetArray(GX_VA_TEX0, l_texCoord, sizeof(*l_texCoord));
    GXCallDisplayList(l_matDL, 0xa0);
    GFSetAlphaCompare(GX_GREATER, L_attr.L_Alpha_Cutoff, GX_AOP_OR, GX_GREATER, L_attr.L_Alpha_Cutoff);
    GFSetTevColor(GX_TEVREG2, alphaColor);

    // Draw the trunk and body for each active unit
    for (i = 0, room = mRoom; i < (s32)ARRAY_SIZE(mRoom); i++, room++) {
        dKy_tevstr_c *tevStr = dComIfGp_roomControl_getTevStr(i);
        GFSetTevColorS10(GX_TEVREG0, tevStr->mColorC0);
        GFSetTevColor(GX_TEVREG1, tevStr->mColorK0);

        dKy_GfFog_tevstr_set(tevStr);

        for (Unit_c *data = room->mpUnit; data != NULL; data = data->mpNext) {
            if (!cLib_checkBit(data->mFlags, Unit_c::STATE_FRUSTUM_CULLED)) {
                if (!cLib_checkBit(data->mFlags, Unit_c::STATE_CUT)) {
                    u32 alphaScale = mAnm[data->mAnmIdx].mAlphaScale;
                    alphaColor.a = alphaScale;
                    bool fading = alphaColor.a != 0xff;

                    if (fading) {
                        GFSetAlphaCompare(GX_GREATER, 0, GX_AOP_OR, GX_GREATER,
                                          0); // Disable Alpha Test
                    }
                    GFSetTevColor(GX_TEVREG2, alphaColor);
                    GFLoadPosMtxImm(data->mModelViewMtx, 0);
                    GXCallDisplayList(l_Oba_swood_bDL, l_Oba_swood_bDL_SIZE);

                    if (fading) {
                        GFSetAlphaCompare(
                            GX_GREATER, L_attr.L_Alpha_Cutoff, GX_AOP_OR,
                            GX_GREATER,
                            L_attr.L_Alpha_Cutoff); // Alpha Test < 50%
                    }
                    alphaColor.a = 0xff;
                    GFSetTevColor(GX_TEVREG2, alphaColor);
                }
                GFLoadPosMtxImm(data->mTrunkModelViewMtx, 0);
                GXCallDisplayList(l_Oba_swood_b_cutDL, l_Oba_swood_b_cutDL_SIZE);
            }
        }
    }

#if VERSION != VERSION_JPN
    J3DShape::resetVcdVatCache();
#endif
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

/* 800BF938-800BFA70       .text search_anm__Q25dWood8Packet_cFQ35dWood5Anm_c6Mode_e */
dWood::AnmID_e dWood::Packet_c::search_anm(dWood::Anm_c::Mode_e i_mode) {
    u32 animIdx;

    JUT_ASSERT(VERSION_SELECT(2059, 2061, 2061), (i_mode >= 0) && (i_mode < Anm_c::Mode_Max));

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
