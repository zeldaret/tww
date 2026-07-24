#ifndef D_SEAFIGHTGAME_H
#define D_SEAFIGHTGAME_H

#include "dolphin/types.h"

struct dSeaFightGame_ship_data {
    /* 0x0 */ u8 m_pos[4][2];
    /* 0x8 */ u8 mMaxHP;
    /* 0x9 */ u8 mCurHP;
    /* 0xA */ u8 field_0xa;
    /* 0xB */ u8 mShipStartX;
    /* 0xC */ u8 mShipStartY;
    /* 0xD */ u8 field_0xd;
    /* 0xE */ u8 field_0xe;
};

class dSeaFightGame_info_c {
public:
    // checkState__20dSeaFightGame_info_cFUcUc (func,weak) found in d_a_mgameboard.o 
    // ?? checkState(int i) { }
    u8 getShipStartX(int i) { return mShips[i].mShipStartX; }
    u8 getShipStartY(int i) { return mShips[i].mShipStartY; }
    // getShipVecY__20dSeaFightGame_info_cFi (func,weak) found in d_a_mgameboard.o 
    // ?? getShipVecY(int i) { }
    bool isClearGame() { return mAliveShipNum == 0; }

    u8 getMaxHP(int i) { return mShips[i].mMaxHP; }
    u8 getCurHP(int i) { return mShips[i].mCurHP; }

    // checkRestBullet__20dSeaFightGame_info_cFv (func,weak) found in d_a_mgameboard.o 
    u8 checkRestBullet() { return mBulletNum; }
    // getRest__20dSeaFightGame_info_cFv
    u8 getRest() { return mAliveShipNum; }
    

    int init(int, int);
    int put_ship(u8, u8);
    bool checkPutShip(int, int, int, int);
    int attack(u8, u8);
    int getNearEnemy(int, int);

    /* 0x00 */ u8 mGrid[8][8];
    /* 0x40 */ dSeaFightGame_ship_data mShips[4];
    /* 0x7C */ u8 mAliveShipNum;
    /* 0x7D */ u8 mBulletNum;
    /* 0x7E */ u8 mScore;
    /* 0x80 */ int mDeadShipNum;
    /* 0x84 */ u32 field_0x84[31];
};

#endif /* D_SEAFIGHTGAME_H */
