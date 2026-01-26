#ifndef D_METER_H
#define D_METER_H

#include "d/d_drawlist.h"
#include "f_op/f_op_msg_mng.h"
#include "m_Do/m_Do_hostIO.h"

class J2DPane;
class JPABaseEmitter;
class fopAc_ac_c;
struct fopMsgM_pane_class;
class msg_class;
class sub_meter_class;

class dMeter_HIO_c : public JORReflexible {
public:
    dMeter_HIO_c();
    virtual ~dMeter_HIO_c();

    void genMessage(JORMContext* ctx);

    /* 0x004 */ s8 mNo;
    /* 0x005 */ u8 field_0x5[0x006 - 0x005];
    /* 0x006 */ short field_0x6;
    /* 0x008 */ u8 field_0x8[0x00C - 0x008];
    /* 0x00C */ f32 field_0xc;
    /* 0x010 */ f32 field_0x10;
    /* 0x014 */ f32 field_0x14;
    /* 0x018 */ f32 field_0x18;
    /* 0x01C */ f32 field_0x1c;
    /* 0x020 */ f32 field_0x20;
    /* 0x024 */ f32 field_0x24;
    /* 0x028 */ f32 field_0x28;
    /* 0x02C */ u8 field_0x2c;
    /* 0x02D */ u8 field_0x2d;
    /* 0x02E */ short field_0x2e;
    /* 0x030 */ short field_0x30;
    /* 0x032 */ short field_0x32;
    /* 0x034 */ short field_0x34;
    /* 0x036 */ short field_0x36;
    /* 0x038 */ short field_0x38;
    /* 0x03A */ u8 field_0x3A[0x03C - 0x03A];
    /* 0x03C */ f32 field_0x3c;
    /* 0x040 */ short field_0x40;
    /* 0x042 */ short field_0x42;
    /* 0x044 */ short field_0x44;
    /* 0x046 */ short field_0x46;
    /* 0x048 */ f32 field_0x48;
    /* 0x04C */ f32 field_0x4c;
    /* 0x050 */ short field_0x50;
    /* 0x052 */ short field_0x52;
    /* 0x054 */ short field_0x54;
    /* 0x056 */ short field_0x56;
    /* 0x058 */ f32 field_0x58;
    /* 0x05C */ f32 field_0x5c;
    /* 0x060 */ u8 field_0x60;
    /* 0x061 */ u8 field_0x61;
    /* 0x062 */ u8 field_0x62;
    /* 0x063 */ u8 field_0x63;
    /* 0x064 */ short field_0x64;
    /* 0x066 */ short field_0x66;
    /* 0x068 */ short field_0x68;
    /* 0x06A */ short field_0x6a;
    /* 0x06C */ short field_0x6c[3];
    /* 0x072 */ short field_0x72[3];
    /* 0x078 */ short field_0x78[3];
    /* 0x07E */ short field_0x7e;
    /* 0x080 */ u8 field_0x80[0x088 - 0x080];
    /* 0x088 */ short field_0x88;
    /* 0x08A */ short field_0x8a;
    /* 0x08C */ short field_0x8c;
    /* 0x08E */ short field_0x8e;
    /* 0x090 */ short field_0x90;
    /* 0x092 */ short field_0x92;
    /* 0x094 */ short field_0x94;
    /* 0x096 */ short field_0x96;
    /* 0x098 */ short field_0x98;
    /* 0x09A */ short field_0x9a;
    /* 0x09C */ short field_0x9c;
    /* 0x09E */ short field_0x9e;
    /* 0x0A0 */ short field_0xa0;
    /* 0x0A2 */ short field_0xa2;
    /* 0x0A4 */ short field_0xa4;
    /* 0x0A6 */ short field_0xa6;
    /* 0x0A8 */ short field_0xa8;
    /* 0x0AA */ short field_0xaa;
    /* 0x0AC */ short field_0xac;
    /* 0x0AE */ short field_0xae;
    /* 0x0B0 */ short field_0xb0;
    /* 0x0B2 */ short field_0xb2;
    /* 0x0B4 */ short field_0xb4;
    /* 0x0B6 */ short field_0xb6;
    /* 0x0B8 */ short field_0xb8;
    /* 0x0BA */ short field_0xba;
    /* 0x0BC */ short field_0xbc;
    /* 0x0BE */ short field_0xbe;
    /* 0x0C0 */ short field_0xc0;
    /* 0x0C2 */ short field_0xc2;
    /* 0x0C4 */ short field_0xc4;
    /* 0x0C6 */ short field_0xc6;
    /* 0x0C8 */ short field_0xc8;
    /* 0x0CA */ short field_0xca;
    /* 0x0CC */ short field_0xcc;
    /* 0x0CE */ short field_0xce;
    /* 0x0D0 */ short field_0xd0;
    /* 0x0D2 */ short field_0xd2;
    /* 0x0D4 */ short field_0xd4;
    /* 0x0D6 */ short field_0xd6;
    /* 0x0D8 */ short field_0xd8;
    /* 0x0DA */ short field_0xda;
    /* 0x0DC */ short field_0xdc;
    /* 0x0DE */ short field_0xde;
    /* 0x0E0 */ short field_0xe0;
    /* 0x0E2 */ short field_0xe2;
    /* 0x0E4 */ short field_0xe4;
    /* 0x0E6 */ short field_0xe6;
    /* 0x0E8 */ short field_0xe8;
    /* 0x0EA */ short field_0xea;
    /* 0x0EC */ short field_0xec;
    /* 0x0EE */ short field_0xee;
    /* 0x0F0 */ short field_0xf0;
    /* 0x0F2 */ short field_0xf2;
    /* 0x0F4 */ short field_0xf4;
    /* 0x0F6 */ short field_0xf6;
    /* 0x0F8 */ short field_0xf8;
    /* 0x0FA */ short field_0xfa;
    /* 0x0FC */ short field_0xfc;
    /* 0x0FE */ short field_0xfe;
    /* 0x100 */ short field_0x100;
    /* 0x102 */ short field_0x102;
    /* 0x104 */ short field_0x104;
    /* 0x106 */ short field_0x106;
    /* 0x108 */ short field_0x108;
    /* 0x10A */ short field_0x10a;
    /* 0x10C */ short field_0x10c;
    /* 0x10E */ short field_0x10e;
    /* 0x110 */ short field_0x110;
    /* 0x112 */ short field_0x112;
    /* 0x114 */ short field_0x114;
    /* 0x116 */ short field_0x116;
    /* 0x118 */ short field_0x118;
    /* 0x11A */ short field_0x11a;
    /* 0x11C */ short field_0x11c;
    /* 0x11E */ short field_0x11e;
    /* 0x120 */ u8 field_0x120;
    /* 0x121 */ u8 field_0x121;
    /* 0x122 */ u8 field_0x122;
    /* 0x123 */ u8 field_0x123;
    /* 0x124 */ short field_0x124;
    /* 0x126 */ short field_0x126;
    /* 0x128 */ short field_0x128;
    /* 0x12A */ short field_0x12a;
    /* 0x12C */ short field_0x12c;
    /* 0x12E */ short field_0x12e;
    /* 0x130 */ short field_0x130;
    /* 0x132 */ short field_0x132;
    /* 0x134 */ short field_0x134;
    /* 0x136 */ short field_0x136;
    /* 0x138 */ short field_0x138;
    /* 0x13A */ short field_0x13a;
    /* 0x13C */ short field_0x13c;
    /* 0x13E */ short field_0x13e;
    /* 0x140 */ short field_0x140;
    /* 0x142 */ u8 field_0x142;
    /* 0x143 */ u8 field_0x143;
    /* 0x144 */ u8 field_0x144;
    /* 0x145 */ u8 field_0x145;
    /* 0x146 */ u8 field_0x146;
    /* 0x147 */ u8 field_0x147;
    /* 0x148 */ u8 field_0x148;
    /* 0x149 */ u8 field_0x149;
    /* 0x14A */ u8 field_0x14a;
    /* 0x14B */ u8 field_0x14b;
    /* 0x14C */ u8 field_0x14c;
    /* 0x14D */ u8 field_0x14D[0x14E - 0x14D];
    /* 0x14E */ short field_0x14e;
    /* 0x150 */ short field_0x150;
    /* 0x152 */ short field_0x152;
    /* 0x154 */ short field_0x154;
};

class dMeter_menuHIO_c : public JORReflexible {
public:
    dMeter_menuHIO_c();
    virtual ~dMeter_menuHIO_c();

    void genMessage(JORMContext* ctx);

    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x5[0x08 - 0x05];
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xc;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1c;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ short field_0x28;
    /* 0x2A */ short field_0x2a;
    /* 0x2C */ short field_0x2c;
    /* 0x2E */ short field_0x2e;
    /* 0x30 */ short field_0x30;
    /* 0x32 */ short field_0x32;
    /* 0x34 */ short field_0x34;
    /* 0x36 */ short field_0x36;
    /* 0x38 */ short field_0x38;
    /* 0x3A */ short field_0x3a;
    /* 0x3C */ f32 field_0x3c;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4c;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5c;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ u8 field_0x6c;
    /* 0x6D */ u8 field_0x6d;
    /* 0x6E */ u8 field_0x6e;
    /* 0x6F */ u8 field_0x6f;
    /* 0x70 */ u8 field_0x70;
    /* 0x71 */ u8 field_0x71;
    /* 0x72 */ u8 field_0x72;
    /* 0x73 */ u8 field_0x73;
    /* 0x74 */ u8 field_0x74;
    /* 0x75 */ u8 field_0x75;
    /* 0x76 */ u8 field_0x76;
    /* 0x77 */ u8 field_0x77;
    /* 0x78 */ u8 field_0x78;
    /* 0x79 */ u8 field_0x79;
    /* 0x7A */ u8 field_0x7a;
    /* 0x7B */ u8 field_0x7b;
    /* 0x7C */ short field_0x7c;
    /* 0x7E */ short field_0x7e;
    /* 0x80 */ short field_0x80;
    /* 0x82 */ short field_0x82;
    /* 0x84 */ short field_0x84;
    /* 0x86 */ u8 field_0x86[0x88 - 0x86];
    /* 0x88 */ short field_0x88;
    /* 0x8A */ short field_0x8a;
    /* 0x8C */ short field_0x8c;
    /* 0x8E */ short field_0x8e;
    /* 0x90 */ short field_0x90;
    /* 0x92 */ short field_0x92;
    /* 0x94 */ f32 field_0x94;
    /* 0x98 */ u8 field_0x98;
    /* 0x99 */ u8 field_0x99;
    /* 0x9A */ s16 field_0x9a;
    /* 0x9C */ s16 field_0x9c;
    /* 0x9E */ s16 field_0x9e;
    /* 0xA0 */ f32 field_0xa0;
    /* 0xA4 */ short field_0xa4;
    /* 0xA6 */ short field_0xa6;
    /* 0xA8 */ short field_0xa8;
    /* 0xAA */ short field_0xaa;
    /* 0xAC */ short field_0xac;
    /* 0xAE */ short field_0xae;
    /* 0xB0 */ short field_0xb0;
    /* 0xB2 */ short field_0xb2;
    /* 0xB4 */ short field_0xb4;
    /* 0xB6 */ short field_0xb6;
    /* 0xB8 */ u8 field_0xb8;
    /* 0xB9 */ u8 field_0xB9[0xBA - 0xB9];
    /* 0xBA */ short field_0xba;
    /* 0xBC */ short field_0xbc;
    /* 0xBE */ u8 field_0xbe;
    /* 0xBF */ u8 field_0xbf;
    /* 0xC0 */ u8 field_0xc0;
    /* 0xC1 */ u8 field_0xc1;
    /* 0xC2 */ u8 field_0xc2;
    /* 0xC3 */ u8 field_0xc3;
    /* 0xC4 */ u8 field_0xc4;
    /* 0xC5 */ u8 field_0xc5;
    /* 0xC6 */ u8 field_0xc6;
    /* 0xC7 */ u8 field_0xc7;
    /* 0xC8 */ u8 field_0xc8;
    /* 0xC9 */ u8 field_0xc9;
    /* 0xCA */ u8 field_0xca;
};

class dMeter_msg_HIO_c : public JORReflexible {
public:
    dMeter_msg_HIO_c();
    virtual ~dMeter_msg_HIO_c();

    void genMessage(JORMContext* ctx);

    /* 0x04 */ s8 mNo;
    /* 0x05 */ GXColor field_0x5;
    /* 0x09 */ GXColor field_0x9;
    /* 0x0D */ u8 field_0xd;
    /* 0x0E */ u8 field_0xe;
    /* 0x0F */ u8 field_0xf;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
    /* 0x18 */ u8 field_0x18;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
    /* 0x1B */ u8 field_0x1b;
    /* 0x1C */ u8 field_0x1c;
    /* 0x1D */ u8 field_0x1d;
    /* 0x1E */ u8 field_0x1e;
    /* 0x1F */ u8 field_0x1f;
    /* 0x20 */ u8 field_0x20;
    /* 0x21 */ u8 field_0x21;
    /* 0x22 */ u8 field_0x22;
    /* 0x23 */ u8 field_0x23;
    /* 0x24 */ u8 field_0x24;
    /* 0x25 */ u8 field_0x25;
    /* 0x26 */ u8 field_0x26;
    /* 0x27 */ u8 field_0x27;
    /* 0x28 */ u8 field_0x28;
    /* 0x29 */ u8 field_0x29;
    /* 0x2A */ u8 field_0x2a;
    /* 0x2B */ u8 field_0x2b;
    /* 0x2C */ u8 field_0x2c;
    /* 0x2D */ u8 field_0x2d;
    /* 0x2E */ u8 field_0x2e;
    /* 0x2F */ u8 field_0x2f;
    /* 0x30 */ u8 field_0x30;
    /* 0x31 */ u8 field_0x31[0x38 - 0x31];
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3c;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ short field_0x44;
    /* 0x46 */ short field_0x46;
    /* 0x48 */ short field_0x48;
    /* 0x4A */ short field_0x4a;
    /* 0x4C */ short field_0x4c;
    /* 0x4E */ u8 field_0x4E[0x50 - 0x4E];
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ u8 field_0x58;
    /* 0x59 */ u8 field_0x59[0x5A - 0x59];
    /* 0x5A */ short field_0x5a;
    /* 0x5C */ short field_0x5c;
    /* 0x5E */ short field_0x5e;
    /* 0x60 */ short field_0x60;
    /* 0x62 */ short field_0x62;
    /* 0x64 */ u8 field_0x64;
    /* 0x65 */ u8 field_0x65[0x66 - 0x65];
    /* 0x66 */ short field_0x66;
    /* 0x68 */ short field_0x68;
    /* 0x6A */ short field_0x6a;
    /* 0x6C */ short field_0x6c;
    /* 0x6E */ short field_0x6e;
    /* 0x70 */ short field_0x70;
    /* 0x72 */ u8 field_0x72;
    /* 0x73 */ u8 field_0x73[0x74 - 0x73];
    /* 0x74 */ short field_0x74;
    /* 0x76 */ short field_0x76;
    /* 0x78 */ short field_0x78;
    /* 0x7A */ short field_0x7a;
    /* 0x7C */ short field_0x7c;
    /* 0x7E */ u8 field_0x7e;
    /* 0x7F */ u8 field_0x7f;
    /* 0x80 */ u8 field_0x80;
    /* 0x81 */ u8 field_0x81;
    /* 0x82 */ u8 field_0x82;
    /* 0x83 */ u8 field_0x83;
    /* 0x84 */ u8 field_0x84;
    /* 0x85 */ u8 field_0x85;
    /* 0x86 */ u8 field_0x86;
    /* 0x87 */ u8 field_0x87;
    /* 0x88 */ u8 field_0x88;
    /* 0x89 */ u8 field_0x89;
    /* 0x8A */ u8 field_0x8a;
};

class dMeter_message_HIO_c : public JORReflexible {
public:
    dMeter_message_HIO_c();
    virtual ~dMeter_message_HIO_c();

    void genMessage(JORMContext* ctx);

    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x5;
    /* 0x06 */ u8 field_0x6;
    /* 0x07 */ u8 field_0x7;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 field_0x9;
    /* 0x0A */ u8 field_0xa;
    /* 0x0B */ u8 field_0xb;
    /* 0x0C */ u8 field_0xc;
    /* 0x0D */ u8 field_0xd;
    /* 0x0E */ u8 field_0xe;
    /* 0x0F */ u8 field_0xf;
    /* 0x10 */ u8 field_0x10;
    /* 0x11 */ u8 field_0x11;
    /* 0x12 */ u8 field_0x12;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ u8 field_0x17;
    /* 0x18 */ u8 field_0x18;
    /* 0x19 */ u8 field_0x19;
    /* 0x1A */ u8 field_0x1a;
    /* 0x1B */ u8 field_0x1b;
    /* 0x1C */ u8 field_0x1c;
    /* 0x1D */ u8 field_0x1d;
    /* 0x1E */ u8 field_0x1e;
    /* 0x1F */ u8 field_0x1f;
    /* 0x20 */ u8 field_0x20;
    /* 0x21 */ u8 field_0x21;
    /* 0x22 */ u8 field_0x22;
    /* 0x23 */ u8 field_0x23;
    /* 0x24 */ u8 field_0x24;
    /* 0x25 */ u8 field_0x25;
    /* 0x26 */ u8 field_0x26;
    /* 0x27 */ u8 field_0x27;
    /* 0x28 */ u8 field_0x28;
    /* 0x29 */ u8 field_0x29;
    /* 0x2A */ u8 field_0x2a;
    /* 0x2B */ u8 field_0x2b;
    /* 0x2C */ u8 field_0x2c;
    /* 0x2D */ u8 field_0x2d;
    /* 0x2E */ u8 field_0x2e;
    /* 0x2F */ u8 field_0x2f;
    /* 0x30 */ u8 field_0x30;
    /* 0x31 */ u8 field_0x31;
    /* 0x32 */ u8 field_0x32;
    /* 0x33 */ u8 field_0x33[0x34 - 0x33];
    /* 0x34 */ short field_0x34;
    /* 0x36 */ short field_0x36;
    /* 0x38 */ short field_0x38;
    /* 0x3A */ u8 field_0x3a;
    /* 0x3B */ u8 field_0x3b;
    /* 0x3C */ short field_0x3c;
    /* 0x3E */ u8 field_0x3E[0x40 - 0x3E];
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ u8 field_0x44;
    /* 0x45 */ u8 field_0x45[0x46 - 0x45];
    /* 0x46 */ short field_0x46;
    /* 0x48 */ short field_0x48;
    /* 0x4A */ u8 field_0x4a;
    /* 0x4B */ u8 field_0x4b;
    /* 0x4C */ u8 field_0x4c;
    /* 0x4D */ u8 field_0x4d;
    /* 0x4E */ u8 field_0x4e;
    /* 0x4F */ u8 field_0x4f;
    /* 0x50 */ u8 field_0x50;
    /* 0x51 */ u8 field_0x51;
    /* 0x52 */ u8 field_0x52;
    /* 0x53 */ u8 field_0x53;
    /* 0x54 */ short field_0x54;
    /* 0x56 */ short field_0x56;
    /* 0x58 */ short field_0x58;
    /* 0x5A */ u8 field_0x5a;
    /* 0x5B */ u8 field_0x5b;
    /* 0x5C */ u8 field_0x5c;
    /* 0x5D */ u8 field_0x5d;
    /* 0x5E */ u8 field_0x5e;
    /* 0x5F */ u8 field_0x5F[0x60 - 0x5F];
    /* 0x60 */ short field_0x60;
    /* 0x62 */ short field_0x62;
    /* 0x64 */ short field_0x64;
    /* 0x66 */ short field_0x66;
    /* 0x68 */ short field_0x68;
    /* 0x6A */ short field_0x6a;
    /* 0x6C */ short field_0x6c;
    /* 0x6E */ short field_0x6e;
    /* 0x70 */ short field_0x70;
    /* 0x72 */ short field_0x72;
    /* 0x74 */ short field_0x74;
    /* 0x76 */ short field_0x76;
    /* 0x78 */ u8 field_0x78;
    /* 0x79 */ u8 field_0x79[0x7A - 0x79];
    /* 0x7A */ short field_0x7a;
    /* 0x7C */ short field_0x7c;
    /* 0x7E */ short field_0x7e;
    /* 0x80 */ short field_0x80;
    /* 0x82 */ short field_0x82;
};

class dDlst_2DMETER1_c : public dDlst_base_c {
public:
    virtual ~dDlst_2DMETER1_c();
    virtual void draw();
};

class dDlst_2DMETER2_c : public dDlst_base_c {
public:
    virtual ~dDlst_2DMETER2_c();
    virtual void draw();
};

class dMeter_map_HIO_c : public JORReflexible {
public:
    dMeter_map_HIO_c();
    virtual ~dMeter_map_HIO_c();

    void genMessage(JORMContext* ctx);

    /* 0x04 */ s8 mNo;
    /* 0x05 */ u8 field_0x5;
    /* 0x06 */ u8 field_0x6;
    /* 0x07 */ u8 field_0x7;
    /* 0x08 */ short field_0x8;
    /* 0x0A */ short field_0xa;
    /* 0x0C */ short field_0xc;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ short field_0x14;
    /* 0x16 */ short field_0x16;
    /* 0x18 */ u8 field_0x18[0x20 - 0x18];
};

class mapCtrlDisp_c {
public:
    // TODO: these two functions are supposed to be weak
    void initMapCtrlDisp();
    void moveMapCtrlDisp();

    void Create() {}
    void Delete() {}
    void getAlpha() {}
    void getHideOffsetX() {}
    void getShowOffsetX() {}
    void hideSEOff() {}
    void hideSEOn() {}
    void isMode() {}
    void setAlpha(u8) {}
    void setHide() {}
    void showSEOff() {}
    void showSEOn() {}

    /* 0x00 */ u8 field_0x0;
    /* 0x01 */ u8 field_0x1;
    /* 0x02 */ u8 field_0x2;
    /* 0x04 */ short field_0x4;
};

class dMeter_info_c {
public:
    ~dMeter_info_c() {}

    /* 0x00 */ u8 field_0x0;
    /* 0x01 */ u8 field_0x1;
};

enum dMeterStatus_e {
    dMtrStts_UNK1_e = 0x00000001,
    dMtrStts_UNK2_e = 0x00000002,
    dMtrStts_UNK4_e = 0x00000004,
    dMtrStts_UNK8_e = 0x00000008,
    dMtrStts_UNK10_e = 0x00000010,
    dMtrStts_UNK20_e = 0x00000020,
    dMtrStts_UNK40_e = 0x00000040,
    dMtrStts_UNK80_e = 0x00000080,
    dMtrStts_UNK100_e = 0x00000100,
    dMtrStts_UNK200_e = 0x00000200,
    dMtrStts_UNK400_e = 0x00000400,
    dMtrStts_UNK800_e = 0x00000800,
    dMtrStts_UNK1000_e = 0x00001000,
    dMtrStts_UNK2000_e = 0x00002000,
    dMtrStts_UNK4000_e = 0x00004000,
    dMtrStts_UNK8000_e = 0x00008000,
    dMtrStts_UNK10000_e = 0x00010000,
    dMtrStts_UNK20000_e = 0x00020000,
    dMtrStts_UNK40000_e = 0x00040000,
    dMtrStts_UNK80000_e = 0x00080000,
    dMtrStts_UNK100000_e = 0x00100000,
    dMtrStts_UNK200000_e = 0x00200000,
    dMtrStts_UNK400000_e = 0x00400000,
    dMtrStts_UNK800000_e = 0x00800000,
};

class sub_meter_class : public msg_class {
public:
    /* 0x00FC */ JKRExpHeap* heap;
    /* 0x0100 */ fopMsgM_pane_class field_0x0100[3];
    /* 0x01A8 */ fopMsgM_pane_class field_0x01a8;
    /* 0x01E0 */ fopMsgM_pane_class field_0x01e0;
    /* 0x0218 */ fopMsgM_pane_class field_0x0218;
    /* 0x0250 */ fopMsgM_pane_class field_0x0250;
    /* 0x0288 */ fopMsgM_pane_class field_0x0288;
    /* 0x02C0 */ fopMsgM_pane_class field_0x02c0;
    /* 0x02F8 */ fopMsgM_pane_class field_0x02f8;
    /* 0x0330 */ fopMsgM_pane_class field_0x0330;
    /* 0x0368 */ fopMsgM_pane_class field_0x0368;
    /* 0x03A0 */ fopMsgM_pane_class field_0x03a0;
    /* 0x03D8 */ fopMsgM_pane_class field_0x03d8;
    /* 0x0410 */ fopMsgM_pane_class field_0x0410;
    /* 0x0448 */ fopMsgM_pane_class field_0x0448[4];
    /* 0x0528 */ fopMsgM_pane_class field_0x0528;
    /* 0x0560 */ fopMsgM_pane_class field_0x0560;
    /* 0x0598 */ fopMsgM_pane_class field_0x0598;
    /* 0x05D0 */ fopMsgM_pane_class field_0x05d0;
    /* 0x0608 */ fopMsgM_pane_class field_0x0608;
    /* 0x0640 */ fopMsgM_pane_class mHeart[20];
    /* 0x0AA0 */ fopMsgM_pane_class mHeartShadow[20];
    /* 0x0F00 */ fopMsgM_pane_class field_0x0f00;
    /* 0x0F38 */ fopMsgM_pane_class field_0x0f38[8];
    /* 0x10F8 */ fopMsgM_pane_class field_0x10f8;
    /* 0x1130 */ fopMsgM_pane_class field_0x1130;
    /* 0x1168 */ fopMsgM_pane_class field_0x1168;
    /* 0x11A0 */ fopMsgM_pane_class field_0x11a0;
    /* 0x11D8 */ fopMsgM_pane_class field_0x11d8;
    /* 0x1210 */ fopMsgM_pane_class field_0x1210;
    /* 0x1248 */ fopMsgM_pane_class field_0x1248;
    /* 0x1280 */ fopMsgM_pane_class field_0x1280;
    /* 0x12B8 */ fopMsgM_pane_class field_0x12b8;
    /* 0x12F0 */ fopMsgM_pane_class field_0x12f0;
    /* 0x1328 */ fopMsgM_pane_class field_0x1328;
    /* 0x1360 */ fopMsgM_pane_class field_0x1360;
    /* 0x1398 */ fopMsgM_pane_class field_0x1398;
    /* 0x13D0 */ fopMsgM_pane_class field_0x13d0;
    /* 0x1408 */ fopMsgM_pane_class field_0x1408;
    /* 0x1440 */ fopMsgM_pane_class field_0x1440;
    /* 0x1478 */ fopMsgM_pane_class field_0x1478[3];
    /* 0x1520 */ fopMsgM_pane_class field_0x1520;
    /* 0x1558 */ fopMsgM_pane_class field_0x1558;
    /* 0x1590 */ fopMsgM_pane_class field_0x1590[4];
    /* 0x1670 */ fopMsgM_pane_class field_0x1670;
    /* 0x16A8 */ fopMsgM_pane_class field_0x16a8;
    /* 0x16E0 */ fopMsgM_pane_class field_0x16e0;
    /* 0x1718 */ fopMsgM_pane_class field_0x1718[4];
    /* 0x17F8 */ fopMsgM_pane_class field_0x17f8;
    /* 0x1830 */ fopMsgM_pane_class field_0x1830;
    /* 0x1868 */ fopMsgM_pane_class field_0x1868[3];
    /* 0x1910 */ fopMsgM_pane_class field_0x1910;
    /* 0x1948 */ fopMsgM_pane_class field_0x1948;
    /* 0x1980 */ fopMsgM_pane_class field_0x1980;
    /* 0x19B8 */ fopMsgM_pane_class field_0x19b8;
    /* 0x19F0 */ fopMsgM_pane_class field_0x19f0[4];
    /* 0x1AD0 */ fopMsgM_pane_class field_0x1ad0[2];
    /* 0x1B40 */ fopMsgM_pane_class field_0x1b40[4];
    /* 0x1C20 */ fopMsgM_pane_class field_0x1c20[2];
    /* 0x1C90 */ fopMsgM_pane_class field_0x1c90;
    /* 0x1CC8 */ fopMsgM_pane_class field_0x1cc8;
    /* 0x1D00 */ fopMsgM_pane_class field_0x1d00;
    /* 0x1D38 */ fopMsgM_pane_class field_0x1d38;
    /* 0x1D70 */ fopMsgM_pane_class field_0x1d70;
    /* 0x1DA8 */ fopMsgM_pane_class field_0x1da8[2];
    /* 0x1E18 */ fopMsgM_pane_class field_0x1e18[2];
    /* 0x1E88 */ fopMsgM_pane_class field_0x1e88;
    /* 0x1EC0 */ fopMsgM_pane_class field_0x1ec0;
    /* 0x1EF8 */ fopMsgM_pane_class field_0x1ef8;
    /* 0x1F30 */ fopMsgM_pane_class field_0x1f30[3];
    /* 0x1FD8 */ fopMsgM_pane_class field_0x1fd8[3];
    /* 0x2080 */ fopMsgM_pane_class field_0x2080[3];
    /* 0x2128 */ fopMsgM_pane_class field_0x2128[3];
    /* 0x21D0 */ fopMsgM_pane_class field_0x21d0;
    /* 0x2208 */ fopMsgM_pane_class field_0x2208;
    /* 0x2240 */ fopMsgM_pane_class field_0x2240;
    /* 0x2278 */ fopMsgM_pane_class field_0x2278;
    /* 0x22B0 */ fopMsgM_pane_class field_0x22b0;
    /* 0x22E8 */ fopMsgM_pane_class field_0x22e8;
    /* 0x2320 */ fopMsgM_pane_class field_0x2320[3];
    /* 0x23C8 */ fopMsgM_pane_class field_0x23c8[3];
    /* 0x2470 */ fopMsgM_pane_class field_0x2470[3];
    /* 0x2518 */ fopMsgM_pane_class field_0x2518;
    /* 0x2550 */ fopMsgM_pane_class field_0x2550[2];
    /* 0x25C0 */ fopMsgM_pane_class field_0x25c0[2];
    /* 0x2630 */ fopMsgM_pane_class field_0x2630[2];
    /* 0x26A0 */ fopMsgM_pane_class field_0x26a0;
    /* 0x26D8 */ fopMsgM_pane_class field_0x26d8;
    /* 0x2710 */ fopMsgM_pane_class field_0x2710;
    /* 0x2748 */ fopMsgM_pane_class field_0x2748;
    /* 0x2780 */ fopMsgM_pane_class field_0x2780;
    /* 0x27B8 */ fopMsgM_pane_class field_0x27b8;
    /* 0x27F0 */ fopMsgM_pane_class field_0x27f0;
    /* 0x2828 */ fopMsgM_pane_class field_0x2828;
    /* 0x2860 */ fopMsgM_pane_class field_0x2860;
    /* 0x2898 */ fopMsgM_pane_class field_0x2898;
    /* 0x28D0 */ fopMsgM_pane_class field_0x28d0;
    /* 0x2908 */ fopMsgM_pane_class field_0x2908;
    /* 0x2940 */ fopMsgM_pane_class field_0x2940[2];
    /* 0x29B0 */ fopMsgM_pane_class field_0x29b0[2];
    /* 0x2A20 */ fopMsgM_pane_class field_0x2a20;
    /* 0x2A58 */ fopMsgM_pane_class field_0x2a58;
    /* 0x2A90 */ fopMsgM_pane_class field_0x2a90[9];
    /* 0x2C88 */ fopMsgM_pane_class field_0x2c88;
    /* 0x2CC0 */ fopMsgM_pane_class field_0x2cc0;
    /* 0x2CF8 */ fopMsgM_pane_class field_0x2cf8;
    /* 0x2D30 */ fopMsgM_pane_class field_0x2d30;
    /* 0x2D68 */ fopMsgM_pane_class field_0x2d68;
    /* 0x2DA0 */ fopMsgM_pane_class field_0x2da0;
    /* 0x2DD8 */ fopMsgM_pane_class field_0x2dd8;
    /* 0x2E10 */ fopMsgM_pane_class field_0x2e10[4];
    /* 0x2EF0 */ JUtility::TColor field_0x2ef0;
    /* 0x2EF4 */ JUtility::TColor field_0x2ef4;
    /* 0x2EF8 */ JUtility::TColor field_0x2ef8;
    /* 0x2EFC */ JUtility::TColor field_0x2efc;
    /* 0x2F00 */ JUtility::TColor field_0x2f00;
    /* 0x2F04 */ JUtility::TColor field_0x2f04;
    /* 0x2F08 */ JUtility::TColor field_0x2f08;
    /* 0x2F0C */ JUtility::TColor field_0x2f0c;
    /* 0x2F10 */ JUtility::TColor field_0x2f10;
    /* 0x2F14 */ JUtility::TColor field_0x2f14;
    /* 0x2F18 */ JUtility::TColor field_0x2f18;
    /* 0x2F1C */ JUtility::TColor field_0x2f1c;
    /* 0x2F20 */ JPABaseEmitter* mpRupyParticle;
    /* 0x2F24 */ JPABaseEmitter* field_0x2f24[2];
    /* 0x2F2C */ JPABaseEmitter* field_0x2f2c[2];
    /* 0x2F34 */ ResTIMG* arrowTex[2];
    /* 0x2F3C */ ResTIMG* actionTex[3];
    /* 0x2F48 */ ResTIMG* xyIconTex[3];
    /* 0x2F54 */ ResTIMG* field_0x2f54[3];
    /* 0x2F60 */ ResTIMG* moveIconTex[2];
    /* 0x2F68 */ f32 field_0x2f68;
    /* 0x2F6C */ f32 field_0x2f6c;
    /* 0x2F70 */ f32 field_0x2f70;
    /* 0x2F74 */ f32 field_0x2f74[9];
    /* 0x2F98 */ f32 field_0x2f98[9];
    /* 0x2FBC */ f32 field_0x2fbc;
    /* 0x2FC0 */ f32 field_0x2fc0;
    /* 0x2FC4 */ s16 field_0x2fc4;
    /* 0x2FC6 */ u8 field_0x2fc6[0x2FD8 - 0x2FC6];
    /* 0x2FD8 */ s16 field_0x2fd8;
    /* 0x2FDA */ s16 field_0x2fda;
    /* 0x2FDC */ u8 field_0x2fdc[0x2FE4 - 0x2FDC];
    /* 0x2FE4 */ s16 field_0x2fe4;
    /* 0x2FE6 */ u8 field_0x2fe6[0x2FE8 - 0x2FE6];
    /* 0x2FE8 */ s16 field_0x2fe8;
    /* 0x2FEA */ u8 field_0x2fea[0x2FEC - 0x2FEA];
    /* 0x2FEC */ s16 field_0x2fec;
    /* 0x2FEE */ u8 field_0x2fee[0x2FF0 - 0x2FEE];
    /* 0x2FF0 */ s16 field_0x2ff0;
    /* 0x2FF2 */ u8 field_0x2ff2[0x2FFC - 0x2FF2];
    /* 0x2FFC */ int mAdjustRupy;
    /* 0x3000 */ int field_0x3000;
    /* 0x3004 */ u32 mStatusFlags;
    /* 0x3008 */ u16 mRupyCount;
    /* 0x300A */ s16 mAdjustHp;
    /* 0x300C */ s16 field_0x300c;
    /* 0x300E */ s16 field_0x300e;
    /* 0x3010 */ s16 field_0x3010;
    /* 0x3012 */ s16 field_0x3012;
    /* 0x3014 */ s16 field_0x3014;
    /* 0x3016 */ u16 field_0x3016;
    /* 0x3018 */ u8 field_0x3018;
    /* 0x3019 */ u8 field_0x3019;
    /* 0x301A */ u8 field_0x301a;
    /* 0x301B */ u8 field_0x301b;
    /* 0x301C */ u8 field_0x301c;
    /* 0x301D */ u8 field_0x301d;
    /* 0x301E */ u8 mMaxHP;
    /* 0x301F */ u8 mCurrHP;
    /* 0x3020 */ u8 field_0x3020;
    /* 0x3021 */ u8 field_0x3021[3];
    /* 0x3024 */ u8 field_0x3024;
    /* 0x3025 */ s8 field_0x3025;
    /* 0x3026 */ u8 field_0x3026;
    /* 0x3027 */ u8 field_0x3027;
    /* 0x3028 */ u8 field_0x3028;
    /* 0x3029 */ u8 field_0x3029;
    /* 0x302A */ u8 field_0x302a;
    /* 0x302B */ u8 field_0x302b[0x302C - 0x302B];
};

extern dMeter_map_HIO_c g_meter_mapHIO;
extern dMeter_HIO_c g_meterHIO;
extern dMeter_menuHIO_c g_menuHIO;
extern dMeter_msg_HIO_c g_msgHIO;
extern dMeter_message_HIO_c g_messageHIO;

u8 dMenu_flag();
void dMenu_flagSet(u8);

void dMeter_mtrShow();
void dMeter_mtrHide();
void dMenu_setPushMenuButton(u8);

void dMeter_weponChange(sub_meter_class* i_Meter);
void dMeter_weponAnime(sub_meter_class* i_Meter);
void dMeter_weponTrans(sub_meter_class* i_Meter);
void dMeter_weponAlpha(sub_meter_class* i_Meter);

void dMeter_actionForce(sub_meter_class* i_Meter);
void dMeter_actionChange(sub_meter_class* i_Meter);
void dMeter_actionTrans(sub_meter_class* i_Meter);
void dMeter_actionAlpha(sub_meter_class* i_Meter);

void dMeter_numberSet(J2DPane* param_1, u8 param_2);

void dMeter_xyBowLightAnime(sub_meter_class* i_Meter, int param_2);
void dMeter_xyItemCountUp(sub_meter_class* i_Meter);
void dMeter_xyItemChange(sub_meter_class* i_Meter, int param_2);
void dMeter_xyAlpha(sub_meter_class* i_Meter);
void dMeter_xyTrans(sub_meter_class* i_Meter);

void dMeter_rAlpha(sub_meter_class* i_Meter);
void dMeter_rTrans(sub_meter_class* i_Meter);

void dMeter_zakoEnemyMove(sub_meter_class* i_Meter);
void dMeter_bossEnemyMove(sub_meter_class* i_Meter, fopAc_ac_c* param_2);
void dMeter_zakoEnemyHide(sub_meter_class* i_Meter);
void dMeter_bossEnemyHide(sub_meter_class* i_Meter);
void dMeter_bossAnime(sub_meter_class* i_Meter);
void dMeter_bossEyeAnime(sub_meter_class* i_Meter);

void dMeter_magicGaugeMove(sub_meter_class* i_Meter);
void dMeter_flyGaugeMove(sub_meter_class* i_Meter, u8 param_2, s16 param_3, s16 param_4);
void dMeter_magicChange(sub_meter_class* i_Meter, f32 param_2);
void dMeter_magicLength(sub_meter_class* i_Meter, f32 param_2);
void dMeter_magicTransNowInit(sub_meter_class* i_Meter);
void dMeter_magicInitTrans(sub_meter_class* i_Meter);
void dMeter_magicTransScale(sub_meter_class* i_Meter, f32 param_2, f32 param_3, f32 param_4);
void dMeter_magicColor(sub_meter_class* i_Meter);
void dMeter_magicAlpha(sub_meter_class* i_Meter);

void dMeter_menuLRMove(sub_meter_class* i_Meter);
void dMeter_menuPlusMove(sub_meter_class* i_Meter);

void dMeter_walletChange(sub_meter_class* i_Meter);

void dMeter_compassDirOpen(sub_meter_class* i_Meter);
void dMeter_compassWindOpen(sub_meter_class* i_Meter);
void dMeter_compassWindClose(sub_meter_class* i_Meter);
void dMeter_compassDirClose(sub_meter_class* i_Meter);
void dMeter_compassAnimeMove(sub_meter_class* i_Meter);
void dMeter_compassValueInit(sub_meter_class* i_Meter);

void dMeter_clockShow(sub_meter_class* i_Meter);
void dMeter_clockHide(sub_meter_class* i_Meter);
void dMeter_clockInit(sub_meter_class* i_Meter);
void dMeter_clockMove(sub_meter_class* i_Meter);
void dMeter_clockStarLight(fopMsgM_pane_class* param_1, s16* param_2);
void dMeter_starLightFrame(s16* param_1);
void dMeter_clockMultiInit(sub_meter_class* i_Meter);
void dMeter_clockMultiMove(sub_meter_class* i_Meter);

void dMeter_swimOpenProc(sub_meter_class* i_Meter);
void dMeter_swimMoveProc(sub_meter_class* i_Meter);
void dMeter_swimMainRotate(sub_meter_class* i_Meter);
void dMeter_swimMainBlink(sub_meter_class* i_Meter);
void dMeter_swimMainDown(sub_meter_class* i_Meter);
void dMeter_swimTekariScroll(sub_meter_class* i_Meter);
void dMeter_swimLightMove(sub_meter_class* i_Meter);
void dMeter_swimLightBirth(sub_meter_class* i_Meter);
void dMeter_swimLightAnime(sub_meter_class* i_Meter, s16 param_2);

void dMeter_arrowErase(fopMsgM_pane_class* param_1);
void dMeter_screenDataTimeSet(sub_meter_class* i_Meter);

#endif /* D_METER_H */
