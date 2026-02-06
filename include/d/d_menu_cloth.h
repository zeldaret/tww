#ifndef D_MENU_CLOTH_H
#define D_MENU_CLOTH_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/gx/GXStruct.h"

class JKRArchive;

class dMCloth_c {
public:
    dMCloth_c();
    virtual ~dMCloth_c();

    cXyz* getBackNrm() { return field_0x52f8; }
    cXyz* getNrm() { return field_0x29a0[mCurArr]; }
    cXyz* getOffsetVec() {}
    cXyz* getPos() { return field_0x48[mCurArr]; }
    cXyz* getShadowPos() {}
    GXTexObj* getTexObj() { return &mTexObj; }
    void setArchive(JKRArchive* arc) { mpArc = arc; }
    void setClothType(u8 type) { mClothType = type; } // ?

    void lightSet1(cXyz);
    void cloth_init();
    void init();
    void setBackNrm();
    void setNrmVtx(cXyz*, int, int);
    void plot(float, float, float, float);
    void plot_shadow(float, float, float, float);
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

    /* 0x0004 */ u16 field_0x4;
    /* 0x0006 */ u8 field_0x6[0x08 - 0x06];
    /* 0x0008 */ u16 field_0x8;
    /* 0x000A */ u16 field_0xa;
    /* 0x000C */ u8 field_0xc;
    /* 0x000D */ u8 field_0xd;
    /* 0x000E */ u8 field_0xe[0x44 - 0x0E];
    /* 0x0044 */ JKRArchive* mpArc;
    /* 0x0048 */ cXyz field_0x48[2][ARR_SIZE];
    /* 0x29A0 */ cXyz field_0x29a0[2][ARR_SIZE];
    /* 0x52F8 */ cXyz field_0x52f8[ARR_SIZE];
    /* 0x67A4 */ cXyz field_0x67a4[ARR_SIZE];
    /* 0x7C50 */ cXyz field_0x7c50[ARR_SIZE];
    /* 0x90FC */ GXTexObj mTexObj;
    /* 0x911C */ u8 field_0x911c[0x913C - 0x911C];
    /* 0x913C */ u8 mCurArr;
    /* 0x913D */ u8 mClothType;
    /* 0x913E */ u8 field_0x913e[0x9140 - 0x913E];
    /* 0x9140 */ cXyz field_0x9140;
    /* 0x914C */ u8 field_0x914C[0x9158 - 0x914C];
    /* 0x9158 */ csXyz field_0x9158;
    /* 0x915E */ s8 field_0x915e[8];
};

class daCLOTH_ChildHIO_c {
public:
    daCLOTH_ChildHIO_c();
    virtual ~daCLOTH_ChildHIO_c();

public:
    /* 0x0004 */ cXyz field_0x4;
    /* 0x0010 */ f32 field_0x10;
    /* 0x0014 */ f32 field_0x14;
    /* 0x0018 */ f32 field_0x18;
    /* 0x001c */ csXyz field_0x1c;
    /* 0x0022 */ s16 field_0x22;
    /* 0x0024 */ s16 field_0x24;
    /* 0x0026 */ s16 field_0x26;
    /* 0x0028 */ s16 field_0x28;
    /* 0x002a */ s16 field_0x2a;
    /* 0x002c */ s16 field_0x2c;
    /* 0x002e */ s16 field_0x2e;
    /* 0x0030 */ s16 field_0x30;
    /* 0x0032 */ u16 field_0x32;
    /* 0x0034 */ u16 field_0x34;
    /* 0x0036 */ s16 field_0x36;
    /* 0x0038 */ u16 field_0x38;
    /* 0x003a */ u16 field_0x3a;
    /* 0x003c */ f32 field_0x3c;
    /* 0x0040 */ f32 field_0x40;
    /* 0x0044 */ f32 field_0x44;
    /* 0x0048 */ s16 field_0x48;
    /* 0x004a */ s16 field_0x4a;
    /* 0x004c */ f32 field_0x4c;
    /* 0x0050 */ u16 field_0x50;
    /* 0x0054 */ f32 field_0x54;
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
