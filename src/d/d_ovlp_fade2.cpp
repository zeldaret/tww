//
// Generated by dtk
// Translation Unit: d_ovlp_fade2.cpp
//

#include "d/d_ovlp_fade2.h"
#include "d/d_com_inf_game.h"
#include "d/d_procname.h"
#include "d/d_s_play.h"
#include "f_ap/f_ap_game.h"
#include "f_op/f_op_overlap.h"
#include "m_Do/m_Do_graphic.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"

void dOvlpFd2_dlst_c::entry() {
    dComIfGd_set2DXlu(this);
}

/* 802237F4-80223D20       .text draw__15dOvlpFd2_dlst_cFv */
void dOvlpFd2_dlst_c::draw() {
    GXSetViewport(0.0f, 0.0f, 640.0f, 480.0f, 0.0f, 1.0f);
    GXSetScissor(0, 0, 640, 480);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetZCompLoc(1);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
    GXSetCullMode(GX_CULL_NONE);
    GXSetDither(GX_TRUE);
    GXSetClipMode(GX_CLIP_DISABLE);
    GXLoadPosMtxImm(mDoMtx_getIdentity(), GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2s16(0, 0);
        GXPosition2s16(640, 0);
        GXPosition2s16(640, 480);
        GXPosition2s16(0, 480);
    GXEnd();

    Mtx44 proj;
    C_MTXPerspective(proj, 60.0f, g_HIO.field_0x0c * 1.33333333f, 100.0f, 100000.0f);
    GXSetProjection(proj, GX_PERSPECTIVE);

    GXInitTexObj(mDoGph_gInf_c::getFrameBufferTexObj(), mDoGph_gInf_c::getFrameBufferTex(), 320, 240, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(mDoGph_gInf_c::getFrameBufferTexObj(), GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    GXLoadTexObj(mDoGph_gInf_c::getFrameBufferTexObj(), GX_TEXMAP0);
    GXSetNumChans(1);
                       
    GXSetChanCtrl(GX_COLOR0, false, GX_SRC_REG, GX_SRC_REG, 0, GX_DF_NONE, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0, (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF });
    GXSetNumTexGens(1);
    GXSetTexCoordGen(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY);
    GXSetNumTevStages(1);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_RASC, GX_CC_TEXC, GX_CC_ZERO);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetZCompLoc(GX_TRUE);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    GXSetBlendMode(GX_BM_NONE, GX_BL_SRC_ALPHA, GX_BL_INV_SRC_ALPHA, GX_LO_CLEAR);
    GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
    GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, g_clearColor);
    GXSetCullMode(GX_CULL_NONE);
    GXSetDither(GX_TRUE);
    GXSetClipMode(GX_CLIP_ENABLE);
    GXLoadPosMtxImm(mtx, GX_PNMTX0);
    GXSetCurrentMtx(0);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XY, GX_S16, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_POS_XYZ, GX_S8, 0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
        GXPosition2s16(-320, 240);
        GXTexCoord2u8(0, 0);

        GXPosition2s16(320, 240);
        GXTexCoord2u8(1, 0);

        GXPosition2s16(320, -240);
        GXTexCoord2u8(1, 1);

        GXPosition2s16(-320, -240);
        GXTexCoord2u8(0, 1);
    GXEnd();

    J2DOrthoGraph* graf = dComIfGp_getCurrentGrafPort();
    graf->setOrtho(-9.0f, -21.0f, 659.0f, 524.0f, -1.0f, 1.0f);
    graf->setup2D();
}

/* 80223D20-80223D84       .text __ct__10dOvlpFd2_cFv */
dOvlpFd2_c::dOvlpFd2_c() {
    mProc = &dOvlpFd2_c::execFirstSnap;
    dComIfGp_2dShowOff();
    mTimer = 2;
}

/* 80223D84-80223E18       .text execFirstSnap__10dOvlpFd2_cFv */
void dOvlpFd2_c::execFirstSnap() {
    if (mHasSnap) {
        if (cLib_calcTimer(&mTimer) == 0) {
            mProc = &dOvlpFd2_c::execFadeOut;
            fopOvlpM_Done(this);
            mTimer = -12;
        }

        dComIfGp_setWindowNum(0);
        if (mDoGph_gInf_c::isMonotone())
            mDoGph_gInf_c::offMonotone();
    }
}

/* 80223E18-80223F8C       .text execFadeOut__10dOvlpFd2_cFv */
void dOvlpFd2_c::execFadeOut() {
    dComIfGp_setWindowNum(0);
    cLib_chaseAngleS(&field_0x112, 2000, 100);
    s16 r5 = (((field_0x110 + 0x4000) & 0x8000) | 0x4000) - field_0x112;
    field_0x110 += field_0x112;
    s16 r0_1 = r5 - field_0x110;
    if (field_0x112 * r0_1 < 0) {
        if (mTimer == 0) {
            if (fopOvlpM_IsOutReq(this)) {
                fopOvlpM_SceneIsStart();
                mProc = &dOvlpFd2_c::execNextSnap;
                field_0x110 = -0x4000;
                mTimer = 15;
            }
        }
    }

    if (mTimer < 0) {
        if (++mTimer == 0) {
            JUTFader* fader = JFWDisplay::getManager()->getFader();
            if (fader != NULL)
                fader->startFadeOut(16);
            mTimer = REG0_S(1) + 20;
        }
    } else {
        cLib_calcTimer(&mTimer);
    }

    s16 r0_2 = REG0_S(0) + 0x800;
    rotZ += r0_2;
    cLib_addCalc2(&scale, REG0_F(1) + 1.0f, 1.0f, REG0_F(2) + 0.05f);
}

/* 80223F8C-80224034       .text execNextSnap__10dOvlpFd2_cFv */
void dOvlpFd2_c::execNextSnap() {
    if (cLib_calcTimer(&mTimer) == 0 && !JFWDisplay::getManager()->getFader()->startFadeIn(16)) {
        field_0x110 += field_0x112;
        mHasSnap = false;
        dComIfGp_setWindowNum(1);
        dComIfGp_2dShowOff();
        mProc = &dOvlpFd2_c::execFadeIn;
    }
}

/* 80224034-802240F4       .text execFadeIn__10dOvlpFd2_cFv */
void dOvlpFd2_c::execFadeIn() {
    s16 r3 = REG0_S(0) + 0x800;
    rotZ -= r3;
    cLib_addCalc0(&scale, 1.0f, REG0_F(3) + 0.03f);

    if (scale < 0.001f) {
        if (!field_0x11e) {
            fopOvlpM_SceneIsStart();
            field_0x11e = 1;
        } else {
            fopOvlpM_Done(this);
            dComIfGp_setWindowNum(1);
            dComIfGp_2dShowOn();
        }
    } else {
        dComIfGp_setWindowNum(0);
        fopOvlpM_SceneIsStop();
    }
}

void dOvlpFd2_c::draw() {
    if (!mHasSnap) {
        dComIfGd_set2DXlu(&dSnap_dlst);
        mHasSnap = true;
    } else if (dComIfGp_getWindowNum() == 0) {
        mDoMtx_stack_c::transS(0.0f, 0.0f, -420.f + REG0_F(0));
        mDoMtx_stack_c::ZrotM(rotZ);
        mDoMtx_stack_c::scaleM(1.0f, 1.0f + scale, 1.0f);
        mDoMtx_stack_c::ZrotM(-rotZ);
        mDoMtx_copy(mDoMtx_stack_c::get(), dOvlpFd2_dlst.getMtx());
        dOvlpFd2_dlst.entry();
    }
    mDoGph_gInf_c::offBlure();
}

/* 802240F4-80224200       .text dOvlpFd2_Draw__FP10dOvlpFd2_c */
static BOOL dOvlpFd2_Draw(dOvlpFd2_c* i_this) {
    i_this->draw();
    return TRUE;
}

/* 80224200-8022422C       .text dOvlpFd2_Execute__FP10dOvlpFd2_c */
static BOOL dOvlpFd2_Execute(dOvlpFd2_c* i_this) {
    (i_this->*i_this->mProc)();
    return TRUE;
}

/* 8022422C-80224234       .text dOvlpFd2_IsDelete__FP10dOvlpFd2_c */
static BOOL dOvlpFd2_IsDelete(dOvlpFd2_c*) {
    return TRUE;
}

/* 80224234-8022423C       .text dOvlpFd2_Delete__FP10dOvlpFd2_c */
static BOOL dOvlpFd2_Delete(dOvlpFd2_c*) {
    return TRUE;
}

/* 8022423C-80224268       .text dOvlpFd2_Create__FPv */
static cPhs_State dOvlpFd2_Create(void* i_this) {
    new (i_this) dOvlpFd2_c();
    return cPhs_COMPLEATE_e;
}

// Fakematch. Manually define this template function here to make it non-weak, fixing the weak function ordering.
template <>
s8 cLib_calcTimer<s8>(s8* value) {
    if (*(s8*)value != 0) {
        *value = *value - 1;
    }
    return *value;
}

overlap_method_class l_dOvlpFd2_Method = {
    (process_method_func)dOvlpFd2_Create,
    (process_method_func)dOvlpFd2_Delete,
    (process_method_func)dOvlpFd2_Execute,
    (process_method_func)dOvlpFd2_IsDelete,
    (process_method_func)dOvlpFd2_Draw,
};

overlap_process_profile_definition g_profile_OVERLAP2 = {
    fpcLy_ROOT_e,
    2,
    fpcPi_CURRENT_e,
    PROC_OVERLAP2,
    &g_fpcLf_Method.base,
    sizeof(dOvlpFd2_c),
    0,
    0,
    &g_fopOvlp_Method,
    0x1E3,
    &l_dOvlpFd2_Method,
};

#if VERSION != VERSION_JPN
overlap_process_profile_definition g_profile_OVERLAP3 = {
    fpcLy_ROOT_e,
    2,
    fpcPi_CURRENT_e,
    PROC_OVERLAP3,
    &g_fpcLf_Method.base,
    sizeof(dOvlpFd2_c),
    0,
    0,
    &g_fopOvlp_Method,
    0x1E4,
    &l_dOvlpFd2_Method,
};
#endif
