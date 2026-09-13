#ifndef D_2DNUMBER_H
#define D_2DNUMBER_H

#include "d/d_drawlist.h"
#include "JSystem/J2DGraph/J2DTextBox.h"

struct ResTIMG;
class JUTFont;
struct fopMsgM_pane_class;
class J2DTextBox;

class dDlst_2DNumber_c : public dDlst_base_c {
public:
    dDlst_2DNumber_c();
    ~dDlst_2DNumber_c();
    bool init(int, s16, s16, s16, s16, u8);
    void draw();

private:
    /* 0x04 */ J2DPicture* mNum[4];
    /* 0x14 */ cXy mPos[4];
    /* 0x34 */ f32 mWidth;
    /* 0x38 */ f32 mHeight;
    /* 0x3C */ int mValue;
    /* 0x40 */ u8 mFlag;
    /* 0x41 */ u8 mDigitNum;
};

class dDlst_2DMinigame_c : public dDlst_base_c {
public:
    bool init(ResTIMG* img1, ResTIMG* img2);
    void draw();

    void setTitlePos(f32 x, f32 y) { mTitlePos.x = x; mTitlePos.y = y; }
    void setScorePos(f32 x, f32 y) { mScorePos.x = x; mScorePos.y = y; }
    void setTitleAlpha(u8 alpha) { mTitle->setAlpha(alpha); }
    void setScoreAlpha(u8 alpha) { mScore->setAlpha(0xFF); mScoreShadow->setAlpha(alpha); } // ???

public:
    /* 0x04 */ J2DPicture* mTitle;
    /* 0x08 */ J2DPicture* mScore;
    /* 0x0C */ J2DPicture* mScoreShadow;
    /* 0x10 */ cXy mTitlePos;
    /* 0x18 */ cXy mTitleSize;
    /* 0x20 */ cXy mScorePos;
    /* 0x28 */ cXy mScoreSize;
};

class dDlst_2DBattery_c : public dDlst_base_c {
public:
    BOOL init(ResTIMG*, ResTIMG*, ResTIMG*, ResTIMG*);
    void setRotate(f32);
    void draw();

public:
    /* 0x04 */ J2DPicture* mRule;
    /* 0x08 */ J2DPicture* mBattery;
    /* 0x0C */ J2DPicture* mBatteryBase;
    /* 0x10 */ J2DPicture* mNum[3][2]; /* [tens, ones, degree][no shadow, shadow] */
    /* 0x28 */ cXy mPicturePos;
    /* 0x28 */ cXy mNumPos;
    /* 0x38 */ cXy mRuleSize;
    /* 0x40 */ cXy mBatterySize;
    /* 0x48 */ cXy mBatteryBaseSize;
    /* 0x50 */ cXy mNumSize;
    /* 0x58 */ f32 mRotation;
}; // size = 0x5C

class dDlst_2DObject_c : public dDlst_base_c {
public:
    BOOL init(ResTIMG*, ResTIMG*);
    void draw();
    void setPosition(f32 x, f32 y) { mPos.x = x; mPos.y = y; }
    void setScale(f32 scale) { mScale = scale; }
    void onBeforeTex() { mCurrentNo = 0; }
    void offBeforeTex() { mCurrentNo = 1; }

public:
    /* 0x04 */ J2DPicture* mPicture[2];
    /* 0x0C */ cXy mPos;
    /* 0x14 */ cXy mSize[2];
    /* 0x24 */ f32 mScale;
    /* 0x28 */ u8 mCurrentNo;
}; // size = 0x2C

class dDlst_2DOutFont_c {
public:
    dDlst_2DOutFont_c() {
        mpRubyFont = NULL;
        mpRubyTextBox = NULL;
        m2C = NULL;
#if VERSION >= VERSION_USA
        m74 = 0;
#endif
    }

    void setLeftUpPos(f32 x, f32 y) {
        mPosTopLeftX = x;
        mPosTopLeftY = y;
    }

    void initial();
    void setPane(JUTFont*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*);
    void setPaneEx(JUTFont*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*, char*);
    void setRuby(JUTFont*, fopMsgM_pane_class*);
    void setRubyEx(JUTFont*, fopMsgM_pane_class*, char*);
    f32 charWidth(int);
    f32 rubyCharWidth(int);
    f32 iconset(int, char**);
    void messageSet(u32);
    void outFontStickAnime1(u8);
    void outFontStickAnime2(u8, u8);
    void outFontStickAnime3(u8, u8);
    void outFontStickAnimePiece(u8, u8);
    void move();
    void setAlpha(u8);

#if VERSION >= VERSION_USA
    /* 0x00 */ J2DTextBox::TFontSize mFontSize;
#endif
    /* 0x08 */ J2DPicture* mpPic[3];
    /* 0x14 */ J2DTextBox* mpTextBox;
    /* 0x18 */ J2DTextBox* mpRubyTextBox;
    /* 0x1C */ JUTFont* mpFont;
    /* 0x20 */ JUTFont* mpRubyFont;
    /* 0x24 */ char* m24;
    /* 0x28 */ char* m28;
    /* 0x2C */ char* m2C;
    /* 0x30 */ f32 mPosTopLeftX;
    /* 0x34 */ f32 mPosTopLeftY;
    /* 0x38 */ f32 m38[3];
    /* 0x44 */ f32 m44[3];
    /* 0x50 */ f32 m50[3];
    /* 0x5C */ f32 m5C[3];
    /* 0x68 */ f32 m68;
    /* 0x6C */ f32 m6C;
    /* 0x70 */ f32 mCharSpace;
#if VERSION >= VERSION_USA
    /* 0x74 */ u8 m74;
#endif
    /* 0x76 */ s16 m76[3];
    /* 0x7C */ s16 m7C[3];
    /* 0x82 */ s16 m82;
    /* 0x84 */ u8 mIconNum;
    /* 0x85 */ u8 mIconNo[3];
    /* 0x88 */ char m88[100];
    /* 0xEC */ char mEC[100];
}; // Size = 0x150

STATIC_ASSERT(sizeof(dDlst_2DOutFont_c) == VERSION_SELECT(0x148, 0x148, 0x150, 0x150));

#endif /* D_2DNUMBER_H */
