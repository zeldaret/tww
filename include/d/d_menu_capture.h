#ifndef D_MENU_CAPTURE_H
#define D_MENU_CAPTURE_H

#include "d/d_com_inf_game.h"
#include "d/d_drawlist.h"
#include "d/d_menu_cloth.h"
#include "d/d_menu_item.h"
#include "f_ap/f_ap_game.h"
#include "m_Do/m_Do_graphic.h"
#include "JSystem/J2DGraph/J2DOrthoGraph.h"


extern dMCloth_c* cloth_c;

class dDlst_MENU_CLOTH_c : public dDlst_base_c {
public:
    virtual ~dDlst_MENU_CLOTH_c() {}

    virtual void draw() {
        Mtx44 mtx;

        const view_port_class* viewport = dComIfGp_getCurrentViewport();
        const f32 aspect = viewport->mWidth / viewport->mHeight;
        C_MTXPerspective(mtx, 30.0f, aspect * g_HIO.mAspectRatio, 1.0f, 100000.0f);

        GXSetProjection(mtx, GX_PERSPECTIVE);

        GXColor clothColor = g_miHIO.mClothColor;
        GXColor shadowColor = g_miHIO.mShadowColor;

        cloth_c->draw(0.0f, clothColor, shadowColor, 1);

        dComIfGp_getCurrentGrafPort()->setPort();
    }
};

class dDlst_MENU_CAPTURE_c : public dDlst_base_c {
public:
    dDlst_MENU_CAPTURE_c() { setDrawFlagOff(); }
    virtual ~dDlst_MENU_CAPTURE_c() {}

    virtual void draw() {
        if (checkDrawFlag() == 1) {
            setDrawFlagOn2();
            GXSetTexCopySrc(0, 0, 0x280, 0x1e0);
            GXSetTexCopyDst(0x140, 0xf0, GXTexFmt(mDoGph_gInf_c::mFrameBufferTimg->format), 1);
            GXCopyTex(mDoGph_gInf_c::mFrameBufferTex, 0);
            GXPixModeSync();
        } else {
            GXSetTexCopySrc(0, 0, 0x280, 0x1e0);
            GXSetTexCopyDst(0x140, 0xf0, GX_TF_RGB565, 1);
            GXCopyTex(mDoGph_gInf_c::mZbufferTex, 0);
            GXPixModeSync();
            GXTexObj tex_obj;
            GXInitTexObj(&tex_obj, mDoGph_gInf_c::mFrameBufferTex, 0x140, 0xf0, GXTexFmt(mDoGph_gInf_c::mFrameBufferTimg->format), GX_CLAMP, GX_CLAMP, false);
            GXInitTexObjLOD(&tex_obj, GX_LINEAR, GX_LINEAR, 0.0, 0.0, 0.0, 0, 0, GX_ANISO_1);
            GXLoadTexObj(&tex_obj, GX_TEXMAP0);
            GXSetNumChans(0);
            GXSetNumTexGens(1);
            GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, false, GX_PTIDENTITY);
            GXSetNumTevStages(1);
            GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
            GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
            GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
            GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO);
            GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, true, GX_TEVPREV);
            GXSetZCompLoc(1);
            GXSetZMode(false, GX_ALWAYS, false);
            GXSetBlendMode(GX_BM_NONE, GX_BL_ZERO, GX_BL_ZERO, GX_LO_OR);
            GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_OR, GX_ALWAYS, 0);
            GXColor local_68 = g_clearColor;
            GXSetFog(GX_FOG_NONE, 0.0, 0.0, 0.0, 0.0, local_68);
            GXSetFogRangeAdj(false, 0, NULL);
            GXSetCullMode(GX_CULL_NONE);
            GXSetDither(1);
            Mtx44 mtx;
            C_MTXOrtho(mtx, 0.0, 1.0, 0.0, 1.0, 0.0, 10.0);
            GXSetProjection(mtx, GX_ORTHOGRAPHIC);
            GXLoadPosMtxImm(mDoMtx_getIdentity(), 0);
            GXSetCurrentMtx(0);

            GXClearVtxDesc();
            GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
            GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_S8, 0);
            GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S8, 0);

            {
                GXBegin(GX_QUADS, GX_VTXFMT0, 4);

                GXPosition3s8(0, 0, -5);
                GXTexCoord2s8(0, 0);

                GXPosition3s8(1, 0, -5);
                GXTexCoord2s8(1, 0);

                GXPosition3s8(1, 1, -5);
                GXTexCoord2s8(1, 1);

                GXPosition3s8(0, 1, -5);
                GXTexCoord2s8(0, 1);

                GXEnd();
            }
        }
    }

    u8 checkDrawFlag() { return mStatus; }
    void setDrawFlagOff() { mStatus = 0; }
    void setDrawFlagOn() { mStatus = 1; }
    void setDrawFlagOn2() { mStatus = 2; }

public:
    /* 0x04 */ u8 mStatus;
};

#endif //D_MENU_CAPTURE_H
