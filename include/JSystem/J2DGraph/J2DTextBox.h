#ifndef J2DTEXTBOX_H
#define J2DTEXTBOX_H

#include "JSystem/J2DGraph/J2DPane.h"
#include "JSystem/JKernel/JKRArchive.h"
#include "JSystem/JUtility/JUTResFont.h"

enum J2DTextBoxHBinding {
    /* 0x0 */ HBIND_CENTER,
    /* 0x1 */ HBIND_RIGHT,
    /* 0x2 */ HBIND_LEFT
};

enum J2DTextBoxVBinding {
    /* 0x0 */ VBIND_CENTER,
    /* 0x1 */ VBIND_BOTTOM,
    /* 0x2 */ VBIND_TOP
};

struct J2DTbxBlockHeader {
    /* 0x00 */ u32 mMagic;
    /* 0x04 */ s32 mSize;
};

class J2DTextBox : public J2DPane {
public:
    struct TFontSize {
        /* 0x0 */ f32 mSizeX;
        /* 0x4 */ f32 mSizeY;
    };

    J2DTextBox(const char*, const char*);
    J2DTextBox(J2DPane*, JSURandomInputStream*);
    J2DTextBox(u32, const JGeometry::TBox2<f32>&, const ResFONT*, const char*, J2DTextBoxHBinding,
               J2DTextBoxVBinding);

    void initiate(const ResFONT*, const char*, J2DTextBoxHBinding, J2DTextBoxVBinding);
    void setFont(JUTFont*);
    void setFontSize(f32 sizeX, f32 sizeY) {
        mFontSizeX = sizeX > 0.0f ? sizeX : 0.0f;
        mFontSizeY = sizeY > 0.0f ? sizeY : 0.0f;
    }
    void setFontSize(TFontSize size) {
        setFontSize(size.mSizeX, size.mSizeY);
    }
    void getFontSize(TFontSize& size) const {
        size.mSizeX = mFontSizeX;
        size.mSizeY = mFontSizeY;
    }
    void setCharColor(JUtility::TColor c) { mCharColor.set(c); }
    void setGradColor(JUtility::TColor c) { mGradColor.set(c); }
    void setBlack(JUtility::TColor c) { mBlack = c; }
    void setWhite(JUtility::TColor c) { mBlack = c; }
    void setLineSpace(f32 x) { mLineSpace = x; }
    void setCharSpace(f32 x) { mCharSpace = x; }
    void draw(f32, f32, f32, J2DTextBoxHBinding);
    char* getStringPtr() const;
    s32 setString(const char*, ...);

    virtual ~J2DTextBox();
    virtual bool setConnectParent(bool);
    virtual void drawSelf(f32, f32);
    virtual void drawSelf(f32, f32, Mtx*);
    virtual void resize(f32, f32);
    virtual u16 getTypeID() { return 19; };

private:
    /* 0xCC */ JUTFont* mpFont;
    /* 0xD0 */ JUtility::TColor mCharColor;
    /* 0xD4 */ JUtility::TColor mGradColor;
    /* 0xD8 */ f32 field_0xd8;
    /* 0xDC */ f32 field_0xdc;
    /* 0xE0 */ f32 mCharSpace;
    /* 0xE4 */ f32 mLineSpace;
    /* 0xE8 */ f32 mFontSizeX;
    /* 0xEC */ f32 mFontSizeY;
    /* 0xF0 */ char* mStringPtr;
    /* 0xF4 */ JUtility::TColor mWhite;
    /* 0xF8 */ JUtility::TColor mBlack;
    /* 0xFC */ u8 mBindingH;
    /* 0xFD */ u8 mBindingV;
    /* 0xFE */ bool mTextFontOwned;
};     // Size: 0x100

#endif /* J2DTEXTBOX_H */