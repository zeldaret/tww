#ifndef J2DPRINT_H
#define J2DPRINT_H

#include "JSystem/J2DGraph/J2DTextBox.h"
#include "JSystem/JUtility/TColor.h"

class JUTFont;

class J2DPrint {
public:
    struct TSize {
        /* 0x0 */ f32 field_0x0;
        /* 0x4 */ f32 field_0x4;
    };

    J2DPrint(JUTFont*, f32, f32, JUtility::TColor, JUtility::TColor, JUtility::TColor, JUtility::TColor);
    virtual ~J2DPrint() {};
    void private_initiate(JUTFont*, f32, f32, JUtility::TColor, JUtility::TColor, JUtility::TColor, JUtility::TColor, bool);
    static char* setBuffer(u32);
    void setFontSize();
    void locate(f32, f32);
    void printReturn(const char*, f32, f32, J2DTextBoxHBinding, J2DTextBoxVBinding, f32, f32, u8);
    f32 parse(const u8*, int, int, u16*, J2DPrint::TSize&, u8, bool);
    void doCtrlCode(int);
    u16 doEscapeCode(const u8**, u8);
    void initchar();
    s32 getNumberS32(const u8**, s32, s32, int);
    f32 getNumberF32(const u8**, f32, f32, int);

    static char* mStrBuff;
    static bool mHeapFlag;
    static u32 mStrBuffSize;
    static u8 mBufferNotEnough;

    /* 0x04 */ JUTFont* mFont;
    /* 0x08 */ JUtility::TColor field_0x8;
    /* 0x0C */ JUtility::TColor field_0xc;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ s16 field_0x20;
    /* 0x22 */ bool field_0x22;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2c;
    /* 0x30 */ f32 mCursorV;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ JUtility::TColor field_0x38;
    /* 0x3C */ JUtility::TColor field_0x3c;
    /* 0x40 */ JUtility::TColor mCharColor;
    /* 0x44 */ JUtility::TColor mGradColor;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4c;
    /* 0x50 */ f32 mFontSizeX;
    /* 0x54 */ f32 mFontSizeY;
    /* 0x58 */ s16 field_0x58;
    /* 0x5A */ bool field_0x5a;
};

#endif /* J2DPRINT_H */
