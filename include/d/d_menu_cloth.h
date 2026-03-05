#ifndef D_MENU_CLOTH_H
#define D_MENU_CLOTH_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/gx/GXStruct.h"

class JKRArchive;

enum {
    MENU_CLOTH_TYPE_DEFAULT = 0,
    MENU_CLOTH_TYPE_FILE_SELECT = 1,
    MENU_CLOTH_TYPE_CLOTH_ONLY = 2,
};
typedef u8 MenuClothType;

class dMCloth_c {
public:
    dMCloth_c();
    virtual ~dMCloth_c();

    cXyz* getPos() { return mPosArr[mCurArr]; }
    cXyz* getNrm() { return mNrmArr[mCurArr]; }
    cXyz* getBackNrm() { return mBackNrmArr; }
    cXyz* getOffsetVec() { return mOffsetVecArr; }
    cXyz* getShadowPos() { return mShadowPosArr; }
    GXTexObj* getTexObj() { return &mTexObj; }
    void setArchive(JKRArchive* arc) { mpArc = arc; }
    void setClothType(MenuClothType type) { mClothType = type; } // ?

    void lightSet1(cXyz);
    void cloth_init();
    void init();
    void setBackNrm();
    void setNrmVtx(cXyz* pDst, int x, int y);
    void plot(float xMin, float yMin, float xMax, float yMax);
    void plot_shadow(float xMin, float yMin, float xMax, float yMax);
    void alpha_out();
    void TevSettingMenu();
    void TevSettingFileSelect();
    void TevSetting();
    void ShadowTevSettingMenu();
    void ShadowTevSettingFileSelect();
    void ShadowTevSetting();
    void draw(float, GXColor, GXColor, unsigned char);
    void cloth_move_sin();
    void cloth_move_simple();
    void cloth_move();

private:
    static s16 init_angle_z;

public:
    static const int ARR_SIZE = 441;
    static const int INNER_SIZE = 11;

    /* 0x0004 */ u16 unused_0x4;
    /* 0x0006 */ u8 field_0x6[0x08 - 0x06];
    /* 0x0008 */ s16 mWaveProgress;
    /* 0x000A */ s16 mFadeInCounter;
    /* 0x000C */ u8 mAlphaOut;
    /* 0x000D */ u8 mCurrentAlpha;
    /* 0x000E */ u8 field_0xe[0x44 - 0x0E];
    /* 0x0044 */ JKRArchive* mpArc;
    /* 0x0048 */ cXyz mPosArr[2][ARR_SIZE];
    /* 0x29A0 */ cXyz mNrmArr[2][ARR_SIZE];
    /* 0x52F8 */ cXyz mBackNrmArr[ARR_SIZE];
    /* 0x67A4 */ cXyz mOffsetVecArr[ARR_SIZE];
    /* 0x7C50 */ cXyz mShadowPosArr[ARR_SIZE];
    /* 0x90FC */ GXTexObj mTexObj;
    /* 0x911C */ u8 field_0x911c[0x913C - 0x911C];
    /* 0x913C */ u8 mCurArr;
    /* 0x913D */ MenuClothType mClothType;
    /* 0x913E */ u8 field_0x913e[0x9140 - 0x913E];
    /* 0x9140 */ cXyz mScale;
    /* 0x914C */ u8 field_0x914C[0x9158 - 0x914C];
    /* 0x9158 */ csXyz mRot;
    /* 0x915E */ GXColor mColor1;
    /* 0x9162 */ GXColor mColor2;
};

class daCLOTH_ChildHIO_c {
public:
    daCLOTH_ChildHIO_c();
    virtual ~daCLOTH_ChildHIO_c();

public:
    /* 0x0004 */ cXyz scale;
    /* 0x0010 */ cXyz pos;
    /* 0x001c */ csXyz rot;
    /* 0x0022 */ GXColorS10 color1;
    /* 0x002a */ GXColorS10 color2;
    /* 0x0032 */ s16 startAlpha;
    /* 0x0034 */ s16 fadeInLength;
    /* 0x0036 */ s16 waveProgressStep;
    /* 0x0038 */ u16 waveFreqX;
    /* 0x003a */ u16 waveFreqY;
    /* 0x003c */ f32 waveAmpX;
    /* 0x0040 */ f32 waveAmpY;
    /* 0x0044 */ f32 waveAmpZ;
    /* 0x0048 */ s16 lightPitch;
    /* 0x004a */ s16 lightYaw;
    /* 0x004c */ f32 lightDistance;
    /* 0x0050 */ s16 wavePreSteps;
    /* 0x0054 */ f32 maxStep;
};

class daCLOTH_HIO_c : public JORReflexible {
public:
    daCLOTH_HIO_c();
    virtual ~daCLOTH_HIO_c();

public:
    /* 0x0004 */ s8 mNo;
    /* 0x0008 */ daCLOTH_ChildHIO_c mChildren[3];
};

#endif /* D_MENU_CLOTH_H */
