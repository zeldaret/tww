#ifndef J2DPICTURE_H
#define J2DPICTURE_H

#include "JSystem/J2DGraph/J2DPane.h"
#include "JSystem/JUtility/TColor.h"
#include "dolphin/gx/GX.h"

class JKRArchive;
class JUTTexture;
class JUTPalette;

class J2DPicture : public J2DPane {
public:
    virtual ~J2DPicture();
    virtual u16 getTypeID() { return 0x12; }
    virtual void drawSelf(f32 x, f32 y);
    virtual void drawSelf(f32 x, f32 y, Mtx* mtx);
    virtual void drawOut(f32, f32, f32, f32, f32, f32);
    virtual void drawOut(f32, f32, f32, f32, f32, f32, f32, f32);

    void setWhite(JUtility::TColor white) { mColorWhite = white; }
    void setBlack(JUtility::TColor black) { mColorBlack = black; }

private:
    /* 0x0CC */ JUTTexture * mpTexture[2];
    /* 0x0D4 */ u32 field_0xd4[2];
    /* 0x0DC */ u8 mNumTexture;
    /* 0x0E0 */ f32 mBlendKonstColorF[4];
    /* 0x0F0 */ f32 mBlendKonstAlphaF[4];
    /* 0x100 */ JUTPalette * mpPalette;
    /* 0x104 */ JUtility::TColor mColorWhite;
    /* 0x108 */ JUtility::TColor mColorBlack;
    /* 0x10C */ JUtility::TColor mNewColor[4];
    /* 0x11C */ JUtility::TColor mBlendKonstColor;
    /* 0x120 */ JUtility::TColor mBlendKonstAlpha;
};

STATIC_ASSERT(sizeof(J2DPicture) == 0x124);

#endif /* J2DPICTURE_H */
