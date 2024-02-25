#ifndef D_MENU_CLOTH_H
#define D_MENU_CLOTH_H

#include "dolphin/types.h"
#include "SSystem/SComponent/c_xyz.h"
#include "dolphin/gx/GXStruct.h"

class JKRArchive;

class dMCloth_c {
public:
    dMCloth_c();
    ~dMCloth_c();

    void getBackNrm() {}
    void getNrm() {}
    void getOffsetVec() {}
    void getPos() {}
    void getShadowPos() {}
    void getTexObj() {}
    void setArchive(JKRArchive* arc) {}
    void setClothType(unsigned char) {}

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
};

class daCLOTH_HIO_c {
public:
    daCLOTH_HIO_c();
};

class daCLOTH_ChildHIO_c {
public:
    daCLOTH_ChildHIO_c();
    ~daCLOTH_ChildHIO_c();
};

#endif /* D_MENU_CLOTH_H */
