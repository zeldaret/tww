#ifndef D_OVLP_FADE4_H
#define D_OVLP_FADE4_H

#include "d/d_drawlist.h"
#include "f_op/f_op_overlap_mng.h"

class dDlst_snapShot2_c : public dDlst_base_c {
public:
    ~dDlst_snapShot2_c() {}
    void draw();

    void init(void* imagePtr, u16 w, u16 h) { mImagePtr = imagePtr; mWidth = w; mHeight = h; }
    void setImagePtr(void* imagePtr) { mImagePtr = imagePtr; }
    void setWd(u16 w) { mWidth = w; }
    void setHt(u16 h) { mHeight = h; }
    u16 getWd() { return mWidth; }
    u16 getHt() { return mHeight; }

    /* 0x04 */ void* mImagePtr;
    /* 0x08 */ u16 mWidth;
    /* 0x0A */ u16 mHeight;
};

class dDlst_2Dt_Sp_c : public dDlst_base_c {
public:
    ~dDlst_2Dt_Sp_c() {}
    void draw();
    void init(ResTIMG*, f32, f32, f32, f32, GXColor);

    void setPos(f32 x, f32 y) { mPosX = x; mPosY = y; }
    void setWidth(f32 w) { mWidth = w; }
    void setHeight(f32 h) { mHeight = h; }
    void setImageWidth(u32 w) { mImageWidth = w; }
    void setImageHeight(u32 h) { mImageHeight = h; }
    void setImagePtr(void* v) { mImagePtr = v; }
    void setPer(f32 f) { mPercent = f; }

    /* 0x04 */ GXTexObj mTexObj;
    /* 0x24 */ ResTIMG* mTimg;
    /* 0x28 */ void* mImagePtr;
    /* 0x2C */ u32 mImageWidth;
    /* 0x30 */ u32 mImageHeight;
    /* 0x34 */ f32 mPosX;
    /* 0x38 */ f32 mPosY;
    /* 0x3C */ f32 mWidth;
    /* 0x40 */ f32 mHeight;
    /* 0x44 */ GXColor mColor;
    /* 0x48 */ f32 mPercent;
};

class dDlst_2DtEff1_c : public dDlst_base_c {
public:
    ~dDlst_2DtEff1_c() {}
    void init(_GXColor);
    void draw();

    /* 0x004 */ f32 field_0x4;
    /* 0x008 */ u8 field_0x8;
    /* 0x00C */ dDlst_snapShot2_c field_0xc;
    /* 0x018 */ dDlst_2Dt_Sp_c field_0x18;
    /* 0x064 */ dDlst_snapShot2_c field_0x64;
    /* 0x070 */ dDlst_2Dt_Sp_c field_0x70;
    /* 0x0BC */ dDlst_snapShot2_c field_0xbc;
    /* 0x0C8 */ dDlst_2Dt_Sp_c field_0xc8;
    /* 0x114 */ u16 field_0x114;
    /* 0x116 */ u16 field_0x116;
};

class dOvlpFd4_c : public overlap_task_class {
public:
    dOvlpFd4_c();
    void drawFadeOut();
    void drawFadeIn();
    void execFirstSnap();
    void execFadeOut();
    void execNextSnap();
    void execFadeIn();

    typedef void (dOvlpFd4_c::*DrawFunc)();
    typedef void (dOvlpFd4_c::*ExecuteFunc)();

    void setDraw(DrawFunc func) { mDrawFunc = func; }
    void setExecute(ExecuteFunc func) { mExecuteFunc = func; }

    /* 0x0CC */ ExecuteFunc mExecuteFunc;
    /* 0x0D8 */ DrawFunc mDrawFunc;
    /* 0x0E4 */ dDlst_snapShot2_c field_0xe4;
    /* 0x0F0 */ dDlst_snapShot2_c field_0xf0;
    /* 0x0FC */ dDlst_2Dt_Sp_c field_0xfc;
    /* 0x148 */ dDlst_2Dt_Sp_c field_0x148;
    /* 0x194 */ dDlst_2DtEff1_c tEff1_dlst;
    /* 0x2AC */ u8 field_0x2ac;
    /* 0x2AD */ u8 field_0x2ad;
    /* 0x2AE */ s8 field_0x2ae;
    /* 0x2B0 */ s16 field_0x2b0;
    /* 0x2B4 */ f32 field_0x2b4;
    /* 0x2B8 */ u8 field_0x2b8[0x2BC - 0x2B8];
    /* 0x2BC */ f32 field_0x2bc;
    /* 0x2C0 */ u8 field_0x2c0;
    /* 0x2C1 */ s8 field_0x2c1;
    /* 0x2C2 */ u8 field_0x2c2[0x2C8 - 0x2C2];
    /* 0x2C8 */ f32 field_0x2c8;
    /* 0x2CC */ u8 field_0x2cc;
};

#endif /* D_OVLP_FADE4_H */
