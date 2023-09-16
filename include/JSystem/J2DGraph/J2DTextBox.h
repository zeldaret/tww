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
    J2DTextBox(const char*, const char*);
    J2DTextBox(J2DPane*, JSURandomInputStream*);
    J2DTextBox(u32, const JGeometry::TBox2<f32>&, const ResFONT*, const char*, J2DTextBoxHBinding,
               J2DTextBoxVBinding);

    void initiate(const ResFONT*, const char*, J2DTextBoxHBinding, J2DTextBoxVBinding);
    void setFont(JUTFont*);
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
    /* 0xCC */ JUTResFont* mpFont;
    /* 0xD0 */ JUtility::TColor mGradientFirst;
    /* 0xD4 */ JUtility::TColor mGradientSecond;
    /* 0xD8 */ f32 field_0xd8;
    /* 0xDC */ f32 field_0xdc;
    /* 0xD0 */ f32 field_0xe0;
    /* 0xE4 */ f32 mFontLeading;
    /* 0xE8 */ f32 mFontWidth;
    /* 0xEC */ f32 mFontHeight;
    /* 0xF0 */ char* mStringPtr;
    /* 0xF4 */ JUtility::TColor mTextColor;
    /* 0xF8 */ JUtility::TColor mTextBGColor;
    /* 0xFC */ u8 mBindingH;
    /* 0xFD */ u8 mBindingV;
    /* 0xFE */ bool mTextFontOwned;
};     // Size: 0x100

#endif /* J2DTEXTBOX_H */