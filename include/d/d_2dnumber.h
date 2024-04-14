#ifndef D_2DNUMBER_H
#define D_2DNUMBER_H

#include "d/d_drawlist.h"

struct ResTIMG;
class JUTFont;
class fopMsgM_pane_class;

class dDlst_2DNumber_c : public dDlst_base_c {
public:
    dDlst_2DNumber_c();
    ~dDlst_2DNumber_c();
    bool init(int, s16, s16, s16, s16, u8);
    void draw();

private:
    /* 0x04 */ J2DPicture* mPicture[4];
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

public:
    /* 0x04 */ J2DPicture* mPicture[3];
    /* 0x10 */ cXy mPos1;
    /* 0x18 */ cXy mSize1;
    /* 0x20 */ cXy mPos2;
    /* 0x28 */ cXy mSize2;
};

class dDlst_2DBattery_c : public dDlst_base_c {
public:
    bool init(ResTIMG*, ResTIMG*, ResTIMG*, ResTIMG*);
    void setRotate(float);
    void draw();

public:
    /* 0x04 */ J2DPicture* mPicture[3];
    /* 0x10 */ J2DPicture* mNum[3][2];
    /* 0x28 */ f32 field_0x28[14];
};

class dDlst_2DObject_c : public dDlst_base_c {
public:
    bool init(ResTIMG*, ResTIMG*);
    void draw();

public:
    /* 0x04 */ J2DPicture* mPicture[2];
    /* 0x0C */ cXy mPos;
    /* 0x10 */ cXy mSize[2];
    /* 0x18 */ f32 mScale;
    /* 0x1C */ u8 mCurrentNo;
};

class dDlst_2DOutFont_c {
public:
    void setLeftUpPos(f32, f32) {}
    
    void initial();
    void setPane(JUTFont*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*);
    void setPaneEx(JUTFont*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*, fopMsgM_pane_class*, char*);
    void setRuby(JUTFont*, fopMsgM_pane_class*);
    void setRubyEx(JUTFont*, fopMsgM_pane_class*, char*);
    void charWidth(int);
    void rubyCharWidth(int);
    void iconset(int, char**);
    void messageSet(u32);
    void outFontStickAnime1(u8);
    void outFontStickAnime2(u8, u8);
    void outFontStickAnime3(u8, u8);
    void outFontStickAnimePiece(u8, u8);
    void move();
    void setAlpha(u8);
};

#endif /* D_2DNUMBER_H */
