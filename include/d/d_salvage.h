#ifndef D_SALVAGE_H
#define D_SALVAGE_H

#include "SSystem/SComponent/c_xyz.h"
#include "SSystem/SComponent/c_lib.h"

class JPABaseEmitter;
class fopAc_ac_c;

class dSalvage_info_c {
public:
    void setFlag(u8 bit) { cLib_onBit(mFlag, bit); }
    void clrFlag(u8 bit) { cLib_offBit(mFlag, bit); }
    void resetFlag() { mFlag = 0; }
    u8 checkFlag(u8 bit) { return cLib_checkBit(mFlag, bit); }

public:
    /* 0x00 */ cXyz mPos;
    /* 0x0C */ cXyz mScale;
    /* 0x18 */ f32 mR;
    /* 0x1C */ f32 mH;
    /* 0x20 */ s32 mSwitchNo;
    /* 0x24 */ JPABaseEmitter* mEmtr;
    /* 0x28 */ f32 mDistance;
    /* 0x2C */ s8 mRoomNo;
    /* 0x2D */ u8 mSaveNo;
    /* 0x2E */ u8 mType;
    /* 0x2F */ u8 mKind;
    /* 0x30 */ u8 mItemNo;
    /* 0x31 */ u8 mFlag;
    /* 0x32 */ u8 field_0x32;
    /* 0x33 */ u8 mNowAlpha;
    /* 0x34 */ u8 mDrawMode;
    /* 0x35 */ u8 field_0x35;
}; // size = 0x38

class dSalvage_control_c {
public:
    void init();
    void init_end();
    void entry(fopAc_ac_c*, JPABaseEmitter*);
    void init_room(s8);
    void init_one(int);
    void init_one_sub(int);
    void calcDistanceXZ();
    cXyz getPos(int);
    cXyz* getPosP(int);
    cXyz getScale(int);
    f32 getR(int);
    f32 getH(int);
    s8 getRoomNo(int);
    u8 getItemNo(int);
    s32 getSwitchNo(int);
    u8 getSaveNo(int);
    u8 getType(int);
    u8 getKind(int);
    f32 getDistance(int);
    u8* getAlphaPtr(int);
    s32 getDrawMode(int);
    BOOL checkRegist(int);
    BOOL checkUsed(int);
    void setPos(int, cXyz);
    void setFlag(int, u8);
    void clrFlag(int, u8);
    void setNowAlpha(int, u8);
    void setDrawMode(int, int);

public:
    enum {
        MAX_SEA = 128,
        MAX_ROOM = 32,
        MAX_TOTAL = MAX_ROOM + MAX_SEA,
    };

    /* 0x00 */ u8 mSeaNum;
    /* 0x01 */ u8 mRoomNum;
    /* 0x04 */ dSalvage_info_c mInfo[MAX_TOTAL];
}; // size = 0x2304

#endif /* D_SALVAGE_H */
