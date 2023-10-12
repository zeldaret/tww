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

public:
    /* 0x0CC */ JUTTexture * mpFrameTexture[4];
    /* 0x0DC */ JUTTexture * mpContentsTexture;
    /* 0x0E0 */ JGeometry::TBox2<f32> mWindowBox;
    /* 0x0F0 */ JUTPalette * mpPalette;
    /* 0x0F4 */ JUtility::TColor mColorTL;
    /* 0x0F8 */ JUtility::TColor mColorTR;
    /* 0x0FC */ JUtility::TColor mColorBL;
    /* 0x100 */ JUtility::TColor mColorBR;
    /* 0x104 */ JUtility::TColor mFrameColor[2];
    /* 0x10C */ s16 mTextureWidth;
    /* 0x10E */ s16 mTextureHeight;
    /* 0x110 */ u8 field_0x110;
    /* 0x111 */ u8 field_0x111;
    /* 0x112 */ u8 field_0x112;
    /* 0x113 */ u8 field_0x113;
};

STATIC_ASSERT(sizeof(J2DWindow) == 0x114);

#endif /* J2DWINDOW_H */
