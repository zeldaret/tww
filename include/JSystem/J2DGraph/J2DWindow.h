#ifndef J2DWINDOW_H
#define J2DWINDOW_H

#include "JSystem/J2DGraph/J2DPane.h"
#include "JSystem/JGeometry.h"
#include "JSystem/JUtility/TColor.h"

class JKRArchive;
class JUTTexture;
class JUTPalette;

class J2DWindow : public J2DPane {
public:
    struct TContentsColor {
        TContentsColor() {}
        /* 0x0 */ JUtility::TColor mTL;
        /* 0x4 */ JUtility::TColor mTR;
        /* 0x8 */ JUtility::TColor mBL;
        /* 0xC */ JUtility::TColor mBR;
    };  // Size: 0x10

    J2DWindow(J2DPane*, JSURandomInputStream*);

    virtual ~J2DWindow();
    virtual u16 getTypeID() { return 0x11; }
    virtual void resize(f32 x, f32 y);
    virtual void drawSelf(f32 x, f32 y);
    virtual void drawSelf(f32 x, f32 y, Mtx* mtx);

    void initinfo2();
    void draw_private(const JGeometry::TBox2<f32>&, const JGeometry::TBox2<f32>&);
    void setContentsColor(JUtility::TColor, JUtility::TColor, JUtility::TColor, JUtility::TColor);
    void drawContents(const JGeometry::TBox2<f32>&);
    void drawFrameTexture(JUTTexture*, f32, f32, f32, f32, u16, u16, u16, u16, bool);
    void drawFrameTexture(JUTTexture*, f32, f32, bool, bool, bool);
    void drawContentsTexture(f32, f32, f32, f32);
    void setTevMode(JUTTexture*, JUtility::TColor, JUtility::TColor);

    void getBlack() const {}
    void getContentsColor(TContentsColor& param_0) const {
        param_0.mTL = mColorTL;
        param_0.mTR = mColorTR;
        param_0.mBL = mColorBL;
        param_0.mBR = mColorBR;
    }
    void getWhite() const {}
    void setBlack(JUtility::TColor) {}
    void setContentsColor(TContentsColor) {}
    void setContentsColor(JUtility::TColor) {}
    void setWhite(JUtility::TColor) {}

public:
    /* 0x0CC */ JUTTexture* mpFrameTexture1;
    /* 0x0D0 */ JUTTexture* mpFrameTexture2;
    /* 0x0D4 */ JUTTexture* mpFrameTexture3;
    /* 0x0D8 */ JUTTexture* mpFrameTexture4;
    /* 0x0DC */ JUTTexture* mpContentsTexture;
    /* 0x0E0 */ JGeometry::TBox2<f32> mWindowBox;
    /* 0x0F0 */ JUTPalette* mpPalette;
    /* 0x0F4 */ JUtility::TColor mColorTL;
    /* 0x0F8 */ JUtility::TColor mColorTR;
    /* 0x0FC */ JUtility::TColor mColorBL;
    /* 0x100 */ JUtility::TColor mColorBR;
    /* 0x104 */ JUtility::TColor mWhite;
    /* 0x108 */ JUtility::TColor mBlack;
    /* 0x10C */ s16 mTextureWidth;
    /* 0x10E */ s16 mTextureHeight;
    /* 0x110 */ u8 field_0x110;
    /* 0x111 */ u8 field_0x111;
    /* 0x112 */ u8 field_0x112;
    /* 0x113 */ u8 field_0x113;
};

STATIC_ASSERT(sizeof(J2DWindow) == 0x114);

#endif /* J2DWINDOW_H */
