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

private:
    /* 0x0000 */ u32 field_0x0;
    /* 0x0004 */ u8 field_0x4;
    /* 0x0005 */ u8 field_0x5;
    /* 0x0006 */ u8 field_0x6;
    /* 0x0007 */ u8 field_0x7;
    /* 0x0008 */ u8 field_0x8;
    /* 0x0009 */ u8 field_0x9;
    /* 0x000a */ u8 field_0xa;
    /* 0x000b */ u8 field_0xb;
    /* 0x000c */ f32 field_0xc;
    /* 0x0010 */ f32 field_0x10;
    /* 0x0014 */ f32 field_0x14;
    /* 0x0018 */ f32 field_0x18;
    /* 0x001c */ f32 field_0x1c;
    /* 0x0020 */ f32 field_0x20;
    /* 0x0024 */ u16 field_0x24;
    /* 0x0026 */ u16 field_0x26;
    /* 0x0028 */ u16 field_0x28;
    /* 0x002a */ u16 field_0x2a;
    /* 0x002c */ u16 field_0x2c;
    /* 0x002e */ u16 field_0x2e;
    /* 0x0030 */ u16 field_0x30;
    /* 0x0032 */ u16 field_0x32;
    /* 0x0034 */ u16 field_0x34;
    /* 0x0036 */ u16 field_0x36;
    /* 0x0038 */ u16 field_0x38;
    /* 0x003a */ u16 field_0x3a;
    /* 0x003c */ u16 field_0x3c;
    /* 0x003e */ u16 field_0x3e;
    /* 0x0040 */ u16 field_0x40;
    /* 0x0042 */ u16 field_0x42;
    /* 0x0044 */ f32 field_0x44;
    /* 0x0048 */ f32 field_0x48;
    /* 0x004c */ f32 field_0x4c;
    /* 0x0050 */ u16 field_0x50;
    /* 0x0052 */ u16 field_0x52;
    /* 0x0054 */ f32 field_0x54;
    /* 0x0058 */ u16 field_0x58;
    /* 0x005a */ u8 field_0x5a;
    /* 0x005b */ u8 field_0x5b;
    /* 0x005c */ f32 field_0x5c;
    /* 0x0060 */ u8 field_0x60;
    /* 0x0061 */ u8 field_0x61;
    /* 0x0062 */ u8 field_0x62;
    /* 0x0063 */ u8 field_0x63;
    /* 0x0064 */ f32 field_0x64;
    /* 0x0068 */ f32 field_0x68;
    /* 0x006c */ f32 field_0x6c;
    /* 0x0070 */ f32 field_0x70;
    /* 0x0074 */ f32 field_0x74;
    /* 0x0078 */ f32 field_0x78;
    /* 0x007c */ u16 field_0x7c;
    /* 0x007e */ u16 field_0x7e;
    /* 0x0080 */ u16 field_0x80;
    /* 0x0082 */ u16 field_0x82;
    /* 0x0084 */ u16 field_0x84;
    /* 0x0086 */ u16 field_0x86;
    /* 0x0088 */ u16 field_0x88;
    /* 0x008a */ u16 field_0x8a;
    /* 0x008c */ u16 field_0x8c;
    /* 0x008e */ u16 field_0x8e;
    /* 0x0090 */ u16 field_0x90;
    /* 0x0092 */ u16 field_0x92;
    /* 0x0094 */ u16 field_0x94;
    /* 0x0096 */ u16 field_0x96;
    /* 0x0098 */ u16 field_0x98;
    /* 0x009a */ u16 field_0x9a;
    /* 0x009c */ f32 field_0x9c;
    /* 0x00a0 */ f32 field_0xa0;
    /* 0x00a4 */ f32 field_0xa4;
    /* 0x00a8 */ u16 field_0xa8;
    /* 0x00aa */ u16 field_0xaa;
    /* 0x00ac */ f32 field_0xac;
    /* 0x00b0 */ u16 field_0xb0;
    /* 0x00b2 */ u8 field_0xb2;
    /* 0x00b3 */ u8 field_0xb3;
    /* 0x00b4 */ f32 field_0xb4;
    /* 0x00b8 */ u8 field_0xb8;
    /* 0x00b9 */ u8 field_0xb9;
    /* 0x00ba */ u8 field_0xba;
    /* 0x00bb */ u8 field_0xbb;
    /* 0x00bc */ f32 field_0xbc;
    /* 0x00c0 */ f32 field_0xc0;
    /* 0x00c4 */ f32 field_0xc4;
    /* 0x00c8 */ f32 field_0xc8;
    /* 0x00cc */ f32 field_0xcc;
    /* 0x00d0 */ f32 field_0xd0;
    /* 0x00d4 */ u16 field_0xd4;
    /* 0x00d6 */ u16 field_0xd6;
    /* 0x00d8 */ u16 field_0xd8;
    /* 0x00da */ u16 field_0xda;
    /* 0x00dc */ u16 field_0xdc;
    /* 0x00de */ u16 field_0xde;
    /* 0x00e0 */ u16 field_0xe0;
    /* 0x00e2 */ u16 field_0xe2;
    /* 0x00e4 */ u16 field_0xe4;
    /* 0x00e6 */ u16 field_0xe6;
    /* 0x00e8 */ u16 field_0xe8;
    /* 0x00ea */ u16 field_0xea;
    /* 0x00ec */ u16 field_0xec;
    /* 0x00ee */ u16 field_0xee;
    /* 0x00f0 */ u16 field_0xf0;
    /* 0x00f2 */ u16 field_0xf2;
    /* 0x00f4 */ f32 field_0xf4;
    /* 0x00f8 */ f32 field_0xf8;
    /* 0x00fc */ f32 field_0xfc;
    /* 0x0100 */ u16 field_0x100;
    /* 0x0102 */ u16 field_0x102;
    /* 0x0104 */ f32 field_0x104;
    /* 0x0108 */ u16 field_0x108;
    /* 0x010a */ u8 field_0x10a;
    /* 0x010b */ u8 field_0x10b;
    /* 0x010c */ f32 field_0x10c;
};

class daCLOTH_ChildHIO_c {
public:
    daCLOTH_ChildHIO_c();
    ~daCLOTH_ChildHIO_c();
};

#endif /* D_MENU_CLOTH_H */
