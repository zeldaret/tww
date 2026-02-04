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

    void getBackNrm() {}
    void getNrm() {}
    void getOffsetVec() {}
    void getPos() {}
    void getShadowPos() {}
    void getTexObj() {}
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

    /* 0x0004 */ u16 field_0x4;
    /* 0x0006 */ u8 field_0x6[0x44 - 0x06];
    /* 0x0044 */ JKRArchive* mpArc;
    /* 0x0048 */ cXyz field_0x48[882];
    /* 0x29A0 */ cXyz field_0x29a0[882];
    /* 0x52F8 */ cXyz field_0x52f8[441];
    /* 0x67A4 */ cXyz field_0x67a4[441];
    /* 0x7C50 */ cXyz field_0x7c50[441];
    /* 0x90FC */ GXTexObj mTexObj;
    /* 0x911C */ u8 field_0x911c[0x913C - 0x911C];
    /* 0x913C */ u8 field_0x913c;
    /* 0x913D */ u8 mClothType;
    /* 0x913E */ u8 field_913e[0x9168 - 0x913E];
};

class daCLOTH_HIO_c : public JORReflexible {
public:
    daCLOTH_HIO_c();
};

class daCLOTH_ChildHIO_c {
public:
    daCLOTH_ChildHIO_c();
    ~daCLOTH_ChildHIO_c();
};

#endif /* D_MENU_CLOTH_H */
