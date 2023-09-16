#ifndef D_SEAFIGHTGAME_H
#define D_SEAFIGHTGAME_H

#include "dolphin/types.h"

struct dSeaFightGame_ship_data {
    /* 0x0 */ u8 m_pos[4][2];
    /* 0x8 */ u8 field_0x8;
    /* 0x9 */ u8 field_0x9;
    /* 0xA */ u8 field_0xa;
    /* 0xB */ u8 field_0xb;
    /* 0xC */ u8 field_0xc;
    /* 0xD */ u8 field_0xd;
    /* 0xE */ u8 field_0xe;
};

class dSeaFightGame_info_c {
public:
    int init(int, int);
    int put_ship(u8, u8);
    bool checkPutShip(int, int, int, int);
    int attack(u8, u8);

    /* 0x00 */ u8 mGrid[8][8];
    /* 0x40 */ dSeaFightGame_ship_data mShips[4];
    /* 0x7C */ u8 mAliveShipNum;
    /* 0x7D */ u8 mBulletNum;
    /* 0x7E */ u8 mScore;
    /* 0x80 */ int mDeadShipNum;
};

#endif /* D_SEAFIGHTGAME_H */