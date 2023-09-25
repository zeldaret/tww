/**
 * d_a_player_HIO.inc
 *
 * Parameters for Link's various actions.
 * 
 * This file is not a standalone translation unit and is instead directly 
 * included into d_a_player_main.cpp.
 * 
 * The original name of this file is not known, but a best guess was taken 
 * based on the original names of the classes it contains.
 */

#include "dolphin/types.h"

class daPy_HIO_basic_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daPy_HIO_basic_c0 {
public:
    static daPy_HIO_basic_c1 const m;
};

const daPy_HIO_basic_c1 daPy_HIO_basic_c0::m = {
    1, 160, 1.0f, 50.0f, 2.4f, 700.0f, 0.6f, 5.0f, 0.75f,
};

class daPy_HIO_move_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x0E */ s16 field_0xE;
    /* 0x10 */ s16 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
};  // Size: 0x88

class daPy_HIO_move_c0 {
public:
    static daPy_HIO_move_c1 const m;
};

const daPy_HIO_move_c1 daPy_HIO_move_c0::m = {
    3000, 250,  100,  5,     200,  100,  4,    6,    12,    3.5f, 17.0f, 2.5f, 1.8f,
    0.6f, 0.5f, 0.5f, 1.0f,  0.8f, 1.1f, 0.4f, 0.8f, 1.2f,  2.3f, 0.95f, 1.6f, 0.35f,
    6.0f, 0.5f, 1.0f, 0.87f, 0.6f, 0.0f, 6.0f, 0.8f, 0.85f, 0.7f, 0.5f,  1.3f,
};

class daPy_HIO_atnMove_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
};  // Size: 0x30

class daPy_HIO_atnMove_c0 {
public:
    static daPy_HIO_atnMove_c1 const m;
};

const daPy_HIO_atnMove_c1 daPy_HIO_atnMove_c0::m = {
    3000, 2000, 6, 5.0f, 12.0f, 7.5f, 4.0f, 0.5f, 0.01f, 0.9f, 1.25f, 1.0f, 1.8f,
};

class daPy_HIO_atnMoveB_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
};  // Size: 0x34

class daPy_HIO_atnMoveB_c0 {
public:
    static daPy_HIO_atnMoveB_c1 const m;
};

const daPy_HIO_atnMoveB_c1 daPy_HIO_atnMoveB_c0::m = {
    3000, 2000, 6, 2.5f, 15.0f, 8.0f, 2.0f, 0.5f, 0.75f, 1.0f, 0.8f, 0.95f, 0.99f, -0.99f,
};

class daPy_HIO_turn_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x0E */ s16 field_0xE;
    /* 0x10 */ s16 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
};  // Size: 0x40

class daPy_HIO_turn_c0 {
public:
    static daPy_HIO_turn_c1 const m;
};

const daPy_HIO_turn_c1 daPy_HIO_turn_c0::m = {
    0x3CDF, 0x1F40, 30,   4,    4096, 512,  28,   62,   62,   0.7f,
    5.0f,   1.0f,   0.0f, 5.0f, 1.1f, 0.0f, 2.0f, 1.0f, 0.0f, 5.0f,
};

class daPy_HIO_cutA_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
};  // Size: 0x34

class daPy_HIO_cutA_c0 {
public:
    static daPy_HIO_cutA_c1 const m;
};

const daPy_HIO_cutA_c1 daPy_HIO_cutA_c0::m = {
    2, 19, 1.2f, 4.0f, 16.0f, 0.2f, 10.0f, 2.6f, 0.5f, 0.7f, 2.5f, 6.0f, 5.0f, 11.0f,
};

class daPy_HIO_cutF_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
};  // Size: 0x34

class daPy_HIO_cutF_c0 {
public:
    static daPy_HIO_cutF_c1 const m;
};

const daPy_HIO_cutF_c1 daPy_HIO_cutF_c0::m = {
    2, 19, 1.2f, 4.0f, 17.0f, 0.2f, 8.0f, 0.95f, 0.5f, 0.7f, 2.5f, 6.0f, 5.0f, 12.0f,
};

class daPy_HIO_cutR_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
};  // Size: 0x34

class daPy_HIO_cutR_c0 {
public:
    static daPy_HIO_cutR_c1 const m;
};

const daPy_HIO_cutR_c1 daPy_HIO_cutR_c0::m = {
    2, 19, 1.2f, 4.0f, 16.0f, 0.2f, 1.0f, 0.95f, 0.5f, 0.7f, 2.5f, 6.0f, 6.0f, 12.0f,
};

class daPy_HIO_cutL_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
};  // Size: 0x34

class daPy_HIO_cutL_c0 {
public:
    static daPy_HIO_cutL_c1 const m;
};

const daPy_HIO_cutL_c1 daPy_HIO_cutL_c0::m = {
    2, 18, 1.2f, 4.0f, 16.0f, 0.2f, 1.0f, 0.95f, 0.5f, 0.7f, 2.5f, 6.0f, 5.0f, 10.0f,
};

class daPy_HIO_cutEA_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
};  // Size: 0x30

class daPy_HIO_cutEA_c0 {
public:
    static daPy_HIO_cutEA_c1 const m;
};

const daPy_HIO_cutEA_c1 daPy_HIO_cutEA_c0::m = {
    19, 1.0f, 4.0f, 0.2f, 15.0f, 4.0f, 0.5f, 0.7f, 2.0f, 6.0f, 5.0f, 11.0f,
};

class daPy_HIO_cutEB_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
};  // Size: 0x30

class daPy_HIO_cutEB_c0 {
public:
    static daPy_HIO_cutEB_c1 const m;
};

const daPy_HIO_cutEB_c1 daPy_HIO_cutEB_c0::m = {
    19, 0.9f, 4.0f, 0.2f, 7.0f, 1.5f, 0.5f, 0.7f, 2.0f, 6.0f, 5.0f, 11.0f,
};

class daPy_HIO_cutExA_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
};  // Size: 0x20

class daPy_HIO_cutExA_c0 {
public:
    static daPy_HIO_cutExA_c1 const m;
};

const daPy_HIO_cutExA_c1 daPy_HIO_cutExA_c0::m = {
    21, 0, 1, 1.1f, 4.0f, 1.0f, 12.0f, 18.0f, 18.0f,
};

class daPy_HIO_cutExB_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
};  // Size: 0x18

class daPy_HIO_cutExB_c0 {
public:
    static daPy_HIO_cutExB_c1 const m;
};

const daPy_HIO_cutExB_c1 daPy_HIO_cutExB_c0::m = {
    36, 0.9f, 5.0f, 5.0f, 14.0f, 20.0f,
};

class daPy_HIO_cutExMJ_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
};  // Size: 0x28

class daPy_HIO_cutExMJ_c0 {
public:
    static daPy_HIO_cutExMJ_c1 const m;
};

const daPy_HIO_cutExMJ_c1 daPy_HIO_cutExMJ_c0::m = {
    6, 2, 0.9f, 0.0f, 1.0f, 29.0f, -5.0f, -1.7f, 30.0f, 3.0f, 1.0f,
};

class daPy_HIO_cutKesa_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daPy_HIO_cutKesa_c0 {
public:
    static daPy_HIO_cutKesa_c1 const m;
};

const daPy_HIO_cutKesa_c1 daPy_HIO_cutKesa_c0::m = {
    49, 2, 1.3f, 4.0f, 1.0f, 22.0f, 26.0f, 32.0f,
};

class daPy_HIO_cutTurn_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
};  // Size: 0x78

class daPy_HIO_cutTurn_c0 {
public:
    static daPy_HIO_cutTurn_c1 const m;
};

const daPy_HIO_cutTurn_c1 daPy_HIO_cutTurn_c0::m = {
    21,   1,    1.2f, 2.0f,   5.0f,   21.0f,  0.8f,   0.0f,   5.0f,   0.5f, 0.7f,
    3.0f, 0.0f, 3.0f, 18.5f,  1.0f,   1.5f,   180.0f, 230.0f, 1.0f,   1.3f, 1.5f,
    1.7f, 2.2f, 1.5f, 180.0f, 200.0f, 250.0f, 270.0f, 360.0f, 250.0f,
};

class daPy_HIO_cutTurnR_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
};  // Size: 0x2C

class daPy_HIO_cutTurnR_c0 {
public:
    static daPy_HIO_cutTurnR_c1 const m;
};

const daPy_HIO_cutTurnR_c1 daPy_HIO_cutTurnR_c0::m = {
    0, 4, 9, 27379, 1748, 0.8f, 1.0f, 3.0f, 0.8f, 3.0f, 0.8f, 3.0f, 0.95f,
};

class daPy_HIO_cutRoll_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
};  // Size: 0x28

class daPy_HIO_cutRoll_c0 {
public:
    static daPy_HIO_cutRoll_c1 const m;
};

const daPy_HIO_cutRoll_c1 daPy_HIO_cutRoll_c0::m = {
    6, 90, 14000, 60, 1.2f, 4.0f, 1.0f, 30.0f, 1.0f, 1.5f, 180.0f, 230.0f,
};

class daPy_HIO_cutJump_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
};  // Size: 0x50

class daPy_HIO_cutJump_c0 {
public:
    static daPy_HIO_cutJump_c1 const m;
};

const daPy_HIO_cutJump_c1 daPy_HIO_cutJump_c0::m = {
    15,   14,   2,    15,    0.74f, 2.0f, 1.0f, 18.0f, 27.0f, -3.0f, 0.8f,
    1.0f, 5.0f, 9.0f, 18.0f, -3.0f, 1.1f, 1.0f, 2.0f,  12.0f, 13.0f, 15.0f,
};

class daPy_HIO_cutBoko_c1 {
public:
    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x0E */ s16 field_0xE;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
};  // Size: 0x84

class daPy_HIO_cutBoko_c0 {
public:
    static daPy_HIO_cutBoko_c1 const m;
};

const daPy_HIO_cutBoko_c1 daPy_HIO_cutBoko_c0::m = {
    0.0f,  0,     34,    42,   13,   11,   8,    1.1f, 0.9f,  1.0f, 27.0f, 0.4f,
    11.0f, 2.6f,  0.5f,  0.8f, 3.0f, 8.0f, 6.0f, 7.0f, 13.0f, 0.9f, 20.0f, 69.0f,
    6.0f,  25.0f, 32.0f, 0.7f, 3.0f, 3.0f, 0.8f, 0.0f, 0.6f,  5.0f, 8.0f,  10.0f,
};

class daPy_HIO_cut_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
};  // Size: 0x6C

class daPy_HIO_cut_c0 {
public:
    static daPy_HIO_cut_c1 const m;
};

const daPy_HIO_cut_c1 daPy_HIO_cut_c0::m = {
    14,    15,   12,    18,   -1.8f, 1.0f, 1.0f,  0.8f, 0.0f,  3.0f, 1.1f,  0.0f, 6.0f,  0.5f, 2.0f,
    11.0f, 0.0f, 20.0f, 1.5f, 30.0f, 2.5f, 20.0f, 1.7f, 30.0f, 2.0f, 50.0f, 1.7f, 50.0f, 2.0f,
};

class daPy_HIO_roll_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
};  // Size: 0x48

class daPy_HIO_roll_c0 {
public:
    static daPy_HIO_roll_c1 const m;
};

const daPy_HIO_roll_c1 daPy_HIO_roll_c0::m = {
    19,   24,   5000, 1.1f,  0.0f, 17.0f, 2.0f,  1.5f, 0.5f, 5.0f,
    0.7f, 6.0f, 1.0f, 20.0f, 6.0f, 15.0f, 10.0f, 0.4f, 7.0f,
};

class daPy_HIO_backJump_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
};  // Size: 0x34

class daPy_HIO_backJump_c0 {
public:
    static daPy_HIO_backJump_c1 const m;
};

const daPy_HIO_backJump_c1 daPy_HIO_backJump_c0::m = {
    11, 5, 0.8f, 2.0f, 0.0f, 22.5f, 19.0f, -3.0f, 30.0f, 10.0f, 0.8f, 0.0f, 0.0f, 2.0f,
};

class daPy_HIO_slip_c1 {
public:
    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
};  // Size: 0x24

class daPy_HIO_slip_c0 {
public:
    static daPy_HIO_slip_c1 const m;
};

const daPy_HIO_slip_c1 daPy_HIO_slip_c0::m = {
    0.0f, 0.6f, 1.1f, 0.4f, 1.25f, 0.1875f, 0.6f, 1.7f, 2.5f,
};

class daPy_HIO_slide_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
};  // Size: 0x4C

class daPy_HIO_slide_c0 {
public:
    static daPy_HIO_slide_c1 const m;
};

const daPy_HIO_slide_c1 daPy_HIO_slide_c0::m = {
    9,    9,    9,    8,    14336, 0.3f, 2.0f, 5.0f, 0.3f,  0.0f, 5.0f,
    0.8f, 2.0f, 6.0f, 5.0f, 1.0f,  2.0f, 6.0f, 5.0f, 30.0f, 3.0f,
};

class daPy_HIO_autoJump_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
};  // Size: 0x44

class daPy_HIO_autoJump_c0 {
public:
    static daPy_HIO_autoJump_c1 const m;
};

const daPy_HIO_autoJump_c1 daPy_HIO_autoJump_c0::m = {
    0,    5,    11,   11000, 100,  -2.5f, -175.0f, 9.0f, 1.6f, 0.4f,
    0.8f, 1.3f, 3.0f, 1.0f,  1.0f, 0.0f,  20.0f,   0.8f, 7.0f,
};

class daPy_HIO_fall_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
};  // Size: 0x54

class daPy_HIO_fall_c0 {
public:
    static daPy_HIO_fall_c1 const m;
};

const daPy_HIO_fall_c1 daPy_HIO_fall_c0::m = {
    13,   30,   9,    9,    22,   50,   3,    60.0f, 20.0f, 1.0f, 0.8f,  4.0f,
    0.0f, 0.3f, 1.0f, 9.0f, 5.0f, 6.0f, 1.3f, 6.0f,  19.0f, 6.0f, 26.0f, 1.2f,
};

class daPy_HIO_swim_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
};  // Size: 0x80

class daPy_HIO_swim_c0 {
public:
    static daPy_HIO_swim_c1 const m;
};

const daPy_HIO_swim_c1 daPy_HIO_swim_c0::m = {
    24,    2330, 5000, 1200,  17,   18.0f, 1.0f, -50.0f, 0.02f, 2.0f,  0.5f, 90.0f,
    15.0f, 0.7f, 0.0f, 19.0f, 3.0f, 0.0f,  0.5f, 18.0f,  1.0f,  5.0f,  0.6f, 1.1f,
    5.3f,  0.0f, 0.4f, 6.0f,  9.5f, 37.5f, 2.5f, 1.0f,   30.0f, 0.35f,
};

class daPy_HIO_b_jump_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
};  // Size: 0x4C

class daPy_HIO_b_jump_c0 {
public:
    static daPy_HIO_b_jump_c1 const m;
};

const daPy_HIO_b_jump_c1 daPy_HIO_b_jump_c0::m = {
    256,    0,    8,    3500, 1.0f,  2.0f,  1.0f,   4.0f,  0.0f, 5.0f, -5.0f,
    -3.75f, 0.6f, 0.0f, 1.0f, 32.5f, 12.5f, -3.75f, 10.0f, 2.5f, 6.5f,
};

class daPy_HIO_b_roll_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
};  // Size: 0x3C

class daPy_HIO_b_roll_c0 {
public:
    static daPy_HIO_b_roll_c1 const m;
};

const daPy_HIO_b_roll_c1 daPy_HIO_b_roll_c0::m = {
    1700,  30,   5,    22,   6,     6144,  0.8f,  4.0f,  5.0f,
    17.0f, 0.5f, 3.0f, 0.0f, 20.0f, 40.0f, -4.0f, -3.5f, 15.0f,
};

class daPy_HIO_b_slide_c1 {
public:
    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
};  // Size: 0x10

class daPy_HIO_b_slide_c0 {
public:
    static daPy_HIO_b_slide_c1 const m;
};

const daPy_HIO_b_slide_c1 daPy_HIO_b_slide_c0::m = {
    42.5f,
    0.5f,
    6.25f,
    2.5f,
};

class daPy_HIO_b_verJump_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
};  // Size: 0x44

class daPy_HIO_b_verJump_c0 {
public:
    static daPy_HIO_b_verJump_c1 const m;
};

const daPy_HIO_b_verJump_c1 daPy_HIO_b_verJump_c0::m = {
    5,    19,   17,    0.2f,   2.0f, 6.0f, -9.0f, 70.0f, 1.5f,
    4.0f, 8.0f, -7.0f, -10.0f, 1.0f, 2.0f, 0.0f,  5.5f,  25.0f,
};

class daPy_HIO_wall_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
};  // Size: 0x68

class daPy_HIO_wall_c0 {
public:
    static daPy_HIO_wall_c1 const m;
};

const daPy_HIO_wall_c1 daPy_HIO_wall_c0::m = {
    10,   7,    14,   14,   28,   28,   1.3f, 1.1f, 1.6f, 1.8f,  0.8f, 0.9f, 3.0f, 0.0f,  1.0f,
    1.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 5.0f, 8.5f, 25.0f, 0.9f, 0.9f, 1.0f, 0.98f,
};

class daPy_HIO_smallJump_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daPy_HIO_smallJump_c0 {
public:
    static daPy_HIO_smallJump_c1 const m;
};

const daPy_HIO_smallJump_c1 daPy_HIO_smallJump_c0::m = {
    6, 4, 0.2f, 0.0f, 0.0f, 5.0f, 45.0f, 7.0f,
};

class daPy_HIO_wallCatch_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
};  // Size: 0x58

class daPy_HIO_wallCatch_c0 {
public:
    static daPy_HIO_wallCatch_c1 const m;
};

const daPy_HIO_wallCatch_c1 daPy_HIO_wallCatch_c0::m = {
    5,    7,    24,   13,   7,     75.0f, 110.0f, 130.0f, 170.0f, 0.8f, 2.5f, 0.75f,
    5.0f, 0.0f, 2.0f, 0.0f, 23.0f, 1.0f,  1.0f,   0.8f,   2.0f,   1.0f, 6.0f, 6.0f,
};

class daPy_HIO_hang_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
};  // Size: 0x34

class daPy_HIO_hang_c0 {
public:
    static daPy_HIO_hang_c1 const m;
};

const daPy_HIO_hang_c1 daPy_HIO_hang_c0::m = {
    21, 13, 0.8f, 2.0f, 10.0f, 2.0f, 0.7f, 1.0f, 13.0f, 8.0f, 0.7f, 1.4f, 1.0f, 1.0f,
};

class daPy_HIO_guard_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
};  // Size: 0x28

class daPy_HIO_guard_c0 {
public:
    static daPy_HIO_guard_c1 const m;
};

const daPy_HIO_guard_c1 daPy_HIO_guard_c0::m = {
    11, 0.85f, 0.0f, 2.0f, 7.5f, 0.02f, 0.5f, 1.125f, 0.3f, 12.5f,
};

class daPy_HIO_nockback_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
};  // Size: 0x3C

class daPy_HIO_nockback_c0 {
public:
    static daPy_HIO_nockback_c1 const m;
};

const daPy_HIO_nockback_c1 daPy_HIO_nockback_c0::m = {
    11, 0, 24, 0.9f, 0.0f, 2.0f, 52.0f, 0.02f, 0.5f, 4.9f, 3.0f, 12.5f, 0.8f, 8.0f, 3.0f, 16.0f,
};

class daPy_HIO_iceSlip_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
};  // Size: 0x74

class daPy_HIO_iceSlip_c0 {
public:
    static daPy_HIO_iceSlip_c1 const m;
};

const daPy_HIO_iceSlip_c1 daPy_HIO_iceSlip_c0::m = {
    29,    8000, 36,   36,    36,    36,   9,    0.9f,  0.0f, 2.0f, 12.0f,
    3.0f,  0.7f, 3.0f, 30.0f, 3.0f,  0.8f, 3.0f, 33.0f, 2.0f, 0.7f, 7.0f,
    30.0f, 0.0f, 0.7f, 7.0f,  30.0f, 0.0f, 0.6f, 1.0f,  6.0f, 1.0f,
};

class daPy_HIO_damage_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ f32 field_0x6;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
};  // Size: 0x3C

class daPy_HIO_damage_c0 {
public:
    static daPy_HIO_damage_c1 const m;
};

const daPy_HIO_damage_c1 daPy_HIO_damage_c0::m = {
    9, 8000, 9, 0.0f, 13.0f, 0.05f, 0.6f, 0.0f, 0.5f, 1.2f, 0.25f, 1.5f, 12.0f, 0.6f, 0.0f, 1.0f,
};

class daPy_HIO_laDamage_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x0E */ s16 field_0xE;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8C;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ f32 field_0x94;
};  // Size: 0x98

class daPy_HIO_laDamage_c0 {
public:
    static daPy_HIO_laDamage_c1 const m;
};

const daPy_HIO_laDamage_c1 daPy_HIO_laDamage_c0::m = {
    0,     1300,   36,    36,   36,   36,    19,    2,    2,     2,     0.0f,
    25.0f, -13.0f, 60.0f, 0.7f, 0.0f, 30.0f, 2.0f,  0.8f, 0.0f,  30.0f, 2.0f,
    0.7f,  1.0f,   30.0f, 2.0f, 0.7f, 1.0f,  30.0f, 2.0f, 16.0f, 1.5f,  18.0f,
    1.0f,  1.2f,   0.0f,  1.0f, 1.3f, 0.0f,  1.0f,  1.3f, 0.0f,  1.0f,
};

class daPy_HIO_huDamage_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x0E */ s16 field_0xE;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8C;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ f32 field_0x94;
};  // Size: 0x98

class daPy_HIO_huDamage_c0 {
public:
    static daPy_HIO_huDamage_c1 const m;
};

const daPy_HIO_huDamage_c1 daPy_HIO_huDamage_c0::m = {
    0,     2000,  36,    36,   36,   36,    19,    2,    2,     2,     0.0f,
    80.0f, -9.0f, 50.0f, 0.6f, 0.0f, 34.0f, 2.0f,  0.6f, 0.0f,  34.0f, 2.0f,
    0.6f,  1.0f,  34.0f, 2.0f, 0.6f, 1.0f,  34.0f, 2.0f, 16.0f, 1.5f,  18.0f,
    1.0f,  1.2f,  0.0f,  1.0f, 1.3f, 0.0f,  1.0f,  1.3f, 0.0f,  1.0f,
};

class daPy_HIO_elecDamage_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
};  // Size: 0xC

class daPy_HIO_elecDamage_c0 {
public:
    static daPy_HIO_elecDamage_c1 const m;
};

const daPy_HIO_elecDamage_c1 daPy_HIO_elecDamage_c0::m = {
    20,
    75,
    1.0f,
    0.0f,
};

class daPy_HIO_slowJump_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
};  // Size: 0x3C

class daPy_HIO_slowJump_c0 {
public:
    static daPy_HIO_slowJump_c1 const m;
};

const daPy_HIO_slowJump_c1 daPy_HIO_slowJump_c0::m = {
    19,   40,   -2.0f, 16.25f, 10.5f, 0.9f,  0.0f,   15.0f,
    5.0f, 2.0f, 0.8f,  0.0f,   5.0f,  25.0f, 100.0f, 6.0f,
};

class daPy_HIO_sideStep_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
};  // Size: 0x34

class daPy_HIO_sideStep_c0 {
public:
    static daPy_HIO_sideStep_c1 const m;
};

const daPy_HIO_sideStep_c1 daPy_HIO_sideStep_c0::m = {
    256, 6200, 4, 5, 30.0f, 0.3f, 0.0f, 1.0f, -2.4f, 0.85f, 1.0f, 0.0f, 1.5f, 14.0f, 50.0f,
};

class daPy_HIO_grab_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x0E */ s16 field_0xE;
    /* 0x10 */ s16 field_0x10;
    /* 0x12 */ s16 field_0x12;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1A;
    /* 0x1C */ s16 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
    /* 0x70 */ f32 field_0x70;
    /* 0x74 */ f32 field_0x74;
    /* 0x78 */ f32 field_0x78;
    /* 0x7C */ f32 field_0x7C;
    /* 0x80 */ f32 field_0x80;
    /* 0x84 */ f32 field_0x84;
    /* 0x88 */ f32 field_0x88;
    /* 0x8C */ f32 field_0x8C;
    /* 0x90 */ f32 field_0x90;
    /* 0x94 */ f32 field_0x94;
    /* 0x98 */ f32 field_0x98;
    /* 0x9C */ f32 field_0x9C;
    /* 0xA0 */ f32 field_0xA0;
    /* 0xA4 */ f32 field_0xA4;
    /* 0xA8 */ f32 field_0xA8;
};  // Size: 0xAC

class daPy_HIO_grab_c0 {
public:
    static daPy_HIO_grab_c1 const m;
};

const daPy_HIO_grab_c1 daPy_HIO_grab_c0::m = {
    4,    9,     6,     12,   4,    14,   7,    19,    5,    5,    0,    40,   300,
    40,   12,    0.8f,  0.0f, 1.0f, 0.9f, 0.0f, 9.0f,  1.0f, 1.0f, 0.0f, 1.0f, -0.8f,
    0.0f, 0.0f,  4.0f,  0.8f, 1.0f, 7.0f, 0.0f, -1.1f, 0.0f, 0.0f, 0.0f, 1.0f, 3.0f,
    1.0f, 19.0f, 34.0f, 2.0f, 1.2f, 1.1f, 3.0f, 6.0f,  2.0f, 0.8f, 0.4f,
};

class daPy_HIO_ladder_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
};  // Size: 0x44

class daPy_HIO_ladder_c0 {
public:
    static daPy_HIO_ladder_c1 const m;
};

const daPy_HIO_ladder_c1 daPy_HIO_ladder_c0::m = {
    13,   1.0f, 1.0f, 0.9f, 3.0f, 1.3f, 3.0f, 1.0f, 2.0f,
    1.2f, 0.5f, 0.0f, 1.0f, 0.8f, 0.0f, 0.0f, 0.8f,
};

class daPy_HIO_crouch_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x0E */ s16 field_0xE;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
};  // Size: 0x50

class daPy_HIO_crouch_c0 {
public:
    static daPy_HIO_crouch_c1 const m;
};

const daPy_HIO_crouch_c1 daPy_HIO_crouch_c0::m = {
    8500, 2500, 10000, 9,    32,   7000, 500,  8,    0.8f,  2.0f, 0.8f, 5.0f,
    1.0f, 0.0f, 7.0f,  3.0f, 3.0f, 1.0f, 5.0f, 3.0f, -1.0f, 0.0f, 3.0f, 2.0f,
};

class daPy_HIO_pushpull_c1 {
public:
    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
};  // Size: 0x18

class daPy_HIO_pushpull_c0 {
public:
    static daPy_HIO_pushpull_c1 const m;
};

const daPy_HIO_pushpull_c1 daPy_HIO_pushpull_c0::m = {
    1.0f, 5.0f, 1.0f, 5.0f, 1.0f, 5.0f,
};

class daPy_HIO_rope_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
};  // Size: 0x68

class daPy_HIO_rope_c0 {
public:
    static daPy_HIO_rope_c1 const m;
};

const daPy_HIO_rope_c1 daPy_HIO_rope_c0::m = {
    12000, 12000, 7,    90,   11,    11,   15.0f, 30.0f, 50.0f, 1.0f, 0.0f, 3.0f, 0.5f,  4.0f, 6.0f,
    0.8f,  1.5f,  1.5f, 4.0f, 27.0f, 1.3f, 1.0f,  0.0f,  1.0f,  3.0f, 0.8f, 3.0f, 11.0f, 0.0f,
};

class daPy_HIO_boom_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
};  // Size: 0x30

class daPy_HIO_boom_c0 {
public:
    static daPy_HIO_boom_c1 const m;
};

const daPy_HIO_boom_c1 daPy_HIO_boom_c0::m = {
    10, 11, 1.5f, 2.0f, 3.0f, 10.0f, 7.0f, 0.8f, 5.0f, 1.0f, 1.0f, 0.0f, 11.0f,
};

class daPy_HIO_fan_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
};  // Size: 0x5C

class daPy_HIO_fan_c0 {
public:
    static daPy_HIO_fan_c1 const m;
};

const daPy_HIO_fan_c1 daPy_HIO_fan_c0::m = {
    0,    34,   13,   12,   40,    20,    1.0f,  0.0f,  5.0f,  200.0f, 100.0f, 0.5f, 3.0f,
    1.0f, 0.0f, 3.0f, 5.0f, -2.0f, -0.5f, 15.0f, 15.0f, 12.0f, 9.4f,   0.6f,   2.0f, 5.0f,
};

class daPy_HIO_tact_c1 {
public:
    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daPy_HIO_tact_c0 {
public:
    static daPy_HIO_tact_c1 const m;
};

const daPy_HIO_tact_c1 daPy_HIO_tact_c0::m = {
    0.8f, 6.0f, 0.08f, 4.0f, 1.0f, 1.0f, 1.0f,
};

class daPy_HIO_ham_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
};  // Size: 0x44

class daPy_HIO_ham_c0 {
public:
    static daPy_HIO_ham_c1 const m;
};

const daPy_HIO_ham_c1 daPy_HIO_ham_c0::m = {
    60,   28,   35,   12,   1.2f, 4.0f, 55.0f, 2.0f,  25.0f, 36.0f,
    1.0f, 2.0f, 3.0f, 1.0f, 0.0f, 0.9f, 5.0f,  10.0f, 0.0f,
};

class daPy_HIO_boots_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
};  // Size: 0x14

class daPy_HIO_boots_c0 {
public:
    static daPy_HIO_boots_c1 const m;
};

const daPy_HIO_boots_c1 daPy_HIO_boots_c0::m = {
    19, 150, 1.0f, 0.0f, 19.0f, 5.0f,
};

class daPy_HIO_bottle_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ s16 field_0xC;
    /* 0x0E */ s16 field_0xE;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
    /* 0x58 */ f32 field_0x58;
    /* 0x5C */ f32 field_0x5C;
    /* 0x60 */ f32 field_0x60;
    /* 0x64 */ f32 field_0x64;
    /* 0x68 */ f32 field_0x68;
    /* 0x6C */ f32 field_0x6C;
};  // Size: 0x70

class daPy_HIO_bottle_c0 {
public:
    static daPy_HIO_bottle_c1 const m;
};

const daPy_HIO_bottle_c1 daPy_HIO_bottle_c0::m = {
    16,   16,    50,   45,    69,   124,  81,   36,   1.2f, 0.0f, 15.0f,
    0.0f, 1.2f,  0.0f, 15.0f, 0.0f, 1.0f, 0.0f, 4.0f, 0.0f, 2.0f, 0.0f,
    5.0f, 15.0f, 0.0f, 5.0f,  0.0f, 0.0f, 5.0f, 0.9f, 0.0f, 2.0f,
};

class daPy_HIO_bow_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daPy_HIO_bow_c0 {
public:
    static daPy_HIO_bow_c1 const m;
};

const daPy_HIO_bow_c1 daPy_HIO_bow_c0::m = {
    4, 6, 0.9f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
};

class daPy_HIO_food_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daPy_HIO_food_c0 {
public:
    static daPy_HIO_food_c1 const m;
};

const daPy_HIO_food_c1 daPy_HIO_food_c0::m = {
    17, 21, 0.6f, 0.0f, 4.0f, 1.1f, 2.0f, 4.0f,
};

class daPy_HIO_item_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
};  // Size: 0x34

class daPy_HIO_item_c0 {
public:
    static daPy_HIO_item_c1 const m;
};

const daPy_HIO_item_c1 daPy_HIO_item_c0::m = {
    15, 10, 7, 1.0f, 2.0f, 1.0f, 0.7f, 1.0f, 3.0f, 4.0f, 0.8f, 3.0f, 4.0f, 6.0f,
};

class daPy_HIO_ship_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
};  // Size: 0x18

class daPy_HIO_ship_c0 {
public:
    static daPy_HIO_ship_c1 const m;
};

const daPy_HIO_ship_c1 daPy_HIO_ship_c0::m = {
    14336, 2000, 5325, 1.0f, 0.2f, 8.0f, 8.0f,
};

class daPy_HIO_restart_c1 {
public:
    /* 0x00 */ f32 field_0x0;
    /* 0x04 */ f32 field_0x4;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
};  // Size: 0x18

class daPy_HIO_restart_c0 {
public:
    static daPy_HIO_restart_c1 const m;
};

const daPy_HIO_restart_c1 daPy_HIO_restart_c0::m = {
    1.0f, 5.0f, 80.0f, 1.0f, 0.0f, 2.0f,
};

class daPy_HIO_holdup_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0A */ s16 field_0xA;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
    /* 0x40 */ f32 field_0x40;
    /* 0x44 */ f32 field_0x44;
    /* 0x48 */ f32 field_0x48;
    /* 0x4C */ f32 field_0x4C;
    /* 0x50 */ f32 field_0x50;
    /* 0x54 */ f32 field_0x54;
};  // Size: 0x58

class daPy_HIO_holdup_c0 {
public:
    static daPy_HIO_holdup_c1 const m;
};

const daPy_HIO_holdup_c1 daPy_HIO_holdup_c0::m = {
    72,   11,   60,   60,   89,   44,   1.0f, 0.0f,  1.0f,  1.1f, 0.0f, 5.0f, 1.0f,
    0.0f, 5.0f, 1.0f, 0.0f, 5.0f, 1.5f, 2.0f, 10.0f, 10.0f, 1.0f, 0.0f, 5.0f,
};

class daPy_HIO_vomit_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ s16 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
    /* 0x1C */ f32 field_0x1C;
    /* 0x20 */ f32 field_0x20;
    /* 0x24 */ f32 field_0x24;
    /* 0x28 */ f32 field_0x28;
    /* 0x2C */ f32 field_0x2C;
    /* 0x30 */ f32 field_0x30;
    /* 0x34 */ f32 field_0x34;
    /* 0x38 */ f32 field_0x38;
    /* 0x3C */ f32 field_0x3C;
};  // Size: 0x40

class daPy_HIO_vomit_c0 {
public:
    static daPy_HIO_vomit_c1 const m;
};

const daPy_HIO_vomit_c1 daPy_HIO_vomit_c0::m = {
    6,     22000,   9,    7,    9,    0.3f, 1.0f, 10.0f, 28.0f,
    64.5f, 12.725f, 1.0f, 4.0f, 0.0f, 0.5f, 1.0f, 8.0f,  8.0f,
};

class daPy_HIO_warp_c1 {
public:
    /* 0x00 */ s16 field_0x0;
    /* 0x02 */ s16 field_0x2;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 field_0x6;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 field_0xC;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ f32 field_0x14;
    /* 0x18 */ f32 field_0x18;
};  // Size: 0x1C

class daPy_HIO_warp_c0 {
public:
    static daPy_HIO_warp_c1 const m;
};

const daPy_HIO_warp_c1 daPy_HIO_warp_c0::m = {
    53, 12, 28, 4, 1.2f, 1.6f, 0.5f, 0.1f, 1.35f,
};
