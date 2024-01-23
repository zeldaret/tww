#ifndef J2DPICTURE_H
#define J2DPICTURE_H

#include "JSystem/J2DGraph/J2DPane.h"
#include "JSystem/JUtility/JUTTexture.h"
#include "JSystem/JUtility/TColor.h"
#include "dolphin/gx/GX.h"

class JKRArchive;
class JUTTexture;
class JUTPalette;
struct ResTIMG;
struct ResTLUT;

enum J2DBinding {
    J2DBind_Bottom = (1 << 0),
    J2DBind_Top    = (1 << 1),
    J2DBind_Right  = (1 << 2),
    J2DBind_Left   = (1 << 3),
};

enum J2DMirror {
    J2DMirror_Y    = (1 << 0),
    J2DMirror_X    = (1 << 1),
};

class J2DPicture : public J2DPane {
public:
    J2DPicture();
    J2DPicture(J2DPane*, JSURandomInputStream*);
    J2DPicture(const ResTIMG*);
    J2DPicture(const char*);
    J2DPicture(u32, const JGeometry::TBox2<f32>&, const ResTIMG*, const ResTLUT*);
    virtual ~J2DPicture();
    virtual u16 getTypeID() { return 0x12; }
    virtual void drawSelf(f32 x, f32 y);
    virtual void drawSelf(f32 x, f32 y, Mtx* mtx);
    virtual void drawOut(f32 p1, f32 p2, f32 p3, f32 p4, f32 p5, f32 p6) {
        if (mpTexture[0]) {
            drawOut(JGeometry::TBox2<f32>(p1, p2, p1 + p3, p2 + p4), JGeometry::TBox2<f32>(p5, p6, p5 + mpTexture[0]->getWidth(), p6 + mpTexture[0]->getHeight()));
        }
    }
    virtual void drawOut(f32 p1, f32 p2, f32 p3, f32 p4, f32 p5, f32 p6, f32 p7, f32 p8) {
        drawOut(JGeometry::TBox2<f32>(p1, p2, p1 + p3, p2 + p4), JGeometry::TBox2<f32>(p5, p6, p5 + p7, p6 + p8));
    }
    JUTTexture * getTexture(u8 idx) const {
        return idx < mNumTexture ? mpTexture[idx] : NULL;
    }
    void initiate(const ResTIMG*, const ResTLUT*);
    void private_initiate(const ResTIMG*, const ResTLUT*);
    void initinfo();
    bool insert(const ResTIMG*, u8, f32);
    bool insert(const char*, u8, f32);
    bool remove(u8);
    const ResTIMG * changeTexture(const ResTIMG*, u8);
    const ResTIMG * changeTexture(const char*, u8);
    void drawFullSet(f32, f32, f32, f32, J2DBinding, J2DMirror, bool, Mtx*);
    void draw(f32, f32, f32, f32, bool, bool, bool);
    void draw(f32 x, f32 y, bool mirrorX, bool mirrorY, bool tumble) {
        if (mNumTexture > 0)
            draw(x, y, mpTexture[0]->getWidth(), mpTexture[0]->getHeight(), mirrorX, mirrorY, tumble);
    }
    void drawOut(const JGeometry::TBox2<f32>&, const JGeometry::TBox2<f32>&);
    void drawTexCoord(f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, Mtx*);
    void setTevMode();
    void swap(f32&, f32&);
    void setBlendKonstColor();
    void setBlendKonstAlpha();
    void getNewColor(JUtility::TColor*);

    void setBlendColorRatio(f32 f1, f32 f2, f32 f3, f32 f4) {
        mBlendKonstColorF[0] = f1;
        mBlendKonstColorF[1] = f2;
        mBlendKonstColorF[2] = f3;
        mBlendKonstColorF[3] = f4;
        setBlendKonstColor();
    }
    void setBlendAlphaRatio(f32 f1, f32 f2, f32 f3, f32 f4) {
        mBlendKonstAlphaF[0] = f1;
        mBlendKonstAlphaF[1] = f2;
        mBlendKonstAlphaF[2] = f3;
        mBlendKonstAlphaF[3] = f4;
        setBlendKonstAlpha();
    }
    void setBlendRatio(f32 f1, f32 f2, f32 f3, f32 f4) {
        setBlendColorRatio(f1, f2, f3, f4);
        setBlendAlphaRatio(f1, f2, f3, f4);
    }
    bool setWhite(JUtility::TColor white) { mColorWhite = white; return true; }
    bool setBlack(JUtility::TColor black) { mColorBlack = black; return true; }
    bool setBlackWhite(JUtility::TColor black, JUtility::TColor white) {
        mColorBlack = black;
        mColorWhite = white;
        return true;
    }
    void setCornerColor(JUtility::TColor c0, JUtility::TColor c1, JUtility::TColor c2, JUtility::TColor c3) {
        mCornerColor[0] = c0;
        mCornerColor[1] = c1;
        mCornerColor[2] = c2;
        mCornerColor[3] = c3;
    }
    void setCornerColor(JUtility::TColor c) { setCornerColor(c, c, c, c); }

    u8 getNumTexture() { return mNumTexture; }

    void setBinding(J2DBinding v) { mBinding = v; }
    void setMirror(J2DMirror v) {} // untested { mFlag = (mFlag & ~0x03) | v; }
    J2DMirror getMirror() const { return J2DMirror(mFlag & 0x03); }

    void setTumble(bool v) {} // untested { mFlag = (mFlag & ~0x04) | (v << 2); }
    bool isTumble() const { return mFlag >> 2 & 1; }

private:
    /* 0x0CC */ JUTTexture* mpTexture[4];
    /* 0x0DC */ u8 mNumTexture;
    /* 0x0DD */ u8 mValidTexture;
    /* 0x0DE */ u8 mBinding;
    /* 0x0DF */ u8 mFlag;
    /* 0x0E0 */ f32 mBlendKonstColorF[4];
    /* 0x0F0 */ f32 mBlendKonstAlphaF[4];
    /* 0x100 */ JUTPalette* mpPalette;
    /* 0x104 */ JUtility::TColor mColorWhite;
    /* 0x108 */ JUtility::TColor mColorBlack;
    /* 0x10C */ JUtility::TColor mCornerColor[4];
    /* 0x11C */ JUtility::TColor mBlendKonstColor;
    /* 0x120 */ JUtility::TColor mBlendKonstAlpha;
};

STATIC_ASSERT(sizeof(J2DPicture) == 0x124);

#endif /* J2DPICTURE_H */
