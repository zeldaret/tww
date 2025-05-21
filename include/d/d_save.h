#ifndef D_SAVE_D_SAVE_H
#define D_SAVE_D_SAVE_H

#include "global.h"
#include "SSystem/SComponent/c_xyz.h"
#include "string.h"

class dSv_player_status_a_c {
public:
    void init();

    u8 getSelectItem(int i_no) { return mSelectItem[i_no]; }
    void setSelectItem(int i_no, u8 i_invIdx) { mSelectItem[i_no] = i_invIdx; }
    u8 getSelectEquip(int i_no) { return mSelectEquip[i_no]; }
    void setSelectEquip(int i_no, u8 i_itemNo) { mSelectEquip[i_no] = i_itemNo; }
    u8 getWalletSize() { return mWalletSize; }
    void setWalletSize(u8 size) { mWalletSize = size; }
    int getRupee() { return mRupee; }
    void setRupee(u16 rupee) { mRupee = rupee; }
    u16 getRupeeMax() { return 0; } // TODO
    u8 getMagic() { return mMagic; }
    void setMagic(u8 magic) { mMagic = magic; }
    u8 getMaxMagic() { return mMaxMagic; }
    void setMaxMagic(u8 magic) { mMaxMagic = magic; }
    u16 getLife() { return mLife; }
    void setLife(u16 life) { mLife = life; }
    u16 getMaxLife() { return mMaxLife; }
    void setMaxLife(u16 life) { mMaxLife = life; }

    /* 0x00 */ u16 mMaxLife;
    /* 0x02 */ u16 mLife;
    /* 0x04 */ u16 mRupee;
    /* 0x06 */ u16 field_0x6;
    /* 0x08 */ u8 field_0x8;
    /* 0x09 */ u8 mSelectItem[5];   // X, Y, Z button
    /* 0x0E */ u8 mSelectEquip[4];  // Sword, Shield, Bracelet, ?
    /* 0x12 */ u8 mWalletSize;
    /* 0x13 */ u8 mMaxMagic;
    /* 0x14 */ u8 mMagic;
    /* 0x15 */ u8 field_0x15;
    /* 0x16 */ u8 field_0x16;
    /* 0x17 */ /* 1 byte of alignment padding */
};  // Size: 0x18

STATIC_ASSERT(sizeof(dSv_player_status_a_c) == 0x18);

class dSv_player_status_b_c {
public:
    void init();

    void setDateIpl(s64 i_time) { mDateIPL = i_time; }
    u16 getDate() { return mDate; }
    f32 getTime() { return mTime; }
    void setDate(u16 i_date) { mDate = i_date; }
    void setTime(f32 i_time) { mTime = i_time; }
    s64 getDateIpl() { return mDateIPL; }
    s16 getWindY() { return mTactWindAngleY; }
    s16 getWindX() { return mTactWindAngleX; }
    void setWindY(s16 i_windY) { mTactWindAngleY = i_windY; }
    void setWindX(s16 i_windX) { mTactWindAngleX = i_windX; }

    /* 0x00 */ u64 mDateIPL;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 mTime;
    /* 0x10 */ u16 mDate;
    /* 0x12 */ s16 mTactWindAngleX;
    /* 0x14 */ s16 mTactWindAngleY;
    /* 0x16 */ /* 2 bytes of alignment padding */
};  // Size: 0x18

STATIC_ASSERT(sizeof(dSv_player_status_b_c) == 0x18);

class dSv_player_return_place_c {
public:
    void init();
    void set(char const*, s8, u8);

    s8 getRoomNo() { return mRoomNo; }
    u8 getPoint() { return mPoint; }
    char* getName() { return mName; }

    /* 0x00 */ char mName[8];
    /* 0x08 */ s8 mRoomNo;
    /* 0x09 */ u8 mPoint;
    /* 0x0A */ u8 unk_0xa;
    /* 0x0B */ u8 unk_0xb;
};  // Size: 0xC

STATIC_ASSERT(sizeof(dSv_player_return_place_c) == 0xC);

class dSv_player_item_c {
public:
    void init();
    void setBottleItemIn(u8, u8);
    void setEmptyBottleItemIn(u8);
    void setEmptyBottle();
    void setEquipBottleItemIn(u8);
    void setEquipBottleItemIn(u8, u8);
    void setEquipBottleItemEmpty();
    void setEquipBottleItemEmpty(u8);
    u8 checkBottle(u8);
    u8 checkEmptyBottle();

    u8 getItem(int i_idx) { return mItems[i_idx]; }
    void setItem(int i_idx, u8 i_itemNo) { mItems[i_idx] = i_itemNo; }

    /* 0x00 */ u8 mItems[21];
};  // Size: 0x15

STATIC_ASSERT(sizeof(dSv_player_item_c) == 0x15);

class dSv_player_get_item_c {
public:
    void init();
    void onItem(int, u8);
    BOOL isItem(int, u8);
    void onBottleItem(u8);
    BOOL isBottleItem(u8);

    /* 0x0 */ u8 mItemFlags[21];
};  // Size: 0x15

STATIC_ASSERT(sizeof(dSv_player_get_item_c) == 0x15);

class dSv_player_item_record2_c {
public:
    u8 getArrowNum() { return mArrowNum; }
    void setArrowNum(u8 num) { mArrowNum = num; }
    u8 getBombNum() { return mBombNum; }
    void setBombNum(u8 num) { mBombNum = num; }
    u8 getPictureNum() { return mPictureNum; }
    void setPictureNum(u8 num) { mPictureNum = num; }

    /* 0x0 */ u8 mPictureNum;
    /* 0x1 */ u8 mArrowNum;
    /* 0x2 */ u8 mBombNum;
};  // Size: 0x3

class dSv_player_item_record_c {
public:
    void init();
    void resetTimer(u16);
    void decTimer();
    u16 getTimer();

    u8 getArrowNum() { return mItemRecord2.getArrowNum(); }
    void setArrowNum(u8 num) { mItemRecord2.setArrowNum(num); }
    u8 getBombNum() { return mItemRecord2.getBombNum(); }
    void setBombNum(u8 num) { mItemRecord2.setBombNum(num); }
    u8 getPictureNum() { return mItemRecord2.getPictureNum(); }
    void setPictureNum(u8 num) { mItemRecord2.setPictureNum(num); }

    /* 0x0 */ u16 mTimer;
    /* 0x2 */ dSv_player_item_record2_c mItemRecord2;
    /* 0x5 */ u8 mBottleNum[3];
};  // Size: 0x8

STATIC_ASSERT(sizeof(dSv_player_item_record_c) == 0x8);

class dSv_player_item_max2_c {
public:
    void setReserved1Num(u8 num) { mReserved1Num = num; }
    u8 getArrowNum() { return mArrowNum; }
    void setArrowNum(u8 num) { mArrowNum = num; }
    u8 getBombNum() { return mBombNum; }
    void setBombNum(u8 num) { mBombNum = num; }

    /* 0x0 */ u8 mReserved1Num;
    /* 0x1 */ u8 mArrowNum;
    /* 0x2 */ u8 mBombNum;
};  // Size: 0x3

class dSv_player_item_max_c {
public:
    void init();

    void setReserved1Num(u8 num) { mItemMax2.setReserved1Num(num); }
    u8 getArrowNum() { return mItemMax2.getArrowNum(); }
    void setArrowNum(u8 num) { mItemMax2.setArrowNum(num); }
    u8 getBombNum() { return mItemMax2.getBombNum(); }
    void setBombNum(u8 num) { mItemMax2.setBombNum(num); }

    /* 0x0 */ dSv_player_item_max2_c mItemMax2;
    /* 0x3 */ u8 field_0x3[5];
};  // Size: 0x8

STATIC_ASSERT(sizeof(dSv_player_item_max_c) == 0x8);

class dSv_player_bag_item_c {
public:
    void init();
    void setBeastItem(u8);
    void setBeastItemEmpty(u8);
    bool checkBeastItem(u8);
    void setBaitItemChange(u8);
    void setBaitItemChange(u8, u8);
    void setBaitItemEmpty(u8);
    void setBaitItemEmpty();
    void setBaitItem(u8);
    u8 checkBaitItemEmpty();
    u8 checkBaitItem(u8);
    void setReserveItemChange(u8, u8);
    void setReserveItemChange(u8);
    void setReserveItemEmpty(u8);
    void setReserveItemEmpty();
    void setReserveItem(u8);
    u8 checkReserveItemEmpty();
    u8 checkReserveItem(u8);

    u8 getBeast(int i_idx) { return mBeast[i_idx]; }
    void setBeast(int i_idx, u8 i_itemNo) { mBeast[i_idx] = i_itemNo; }
    u8 getBait(int i_idx) { return mBait[i_idx]; }
    void setBait(int i_idx, u8 i_itemNo) { mBait[i_idx] = i_itemNo; }
    u8 getReserve(int i_idx) { return mReserve[i_idx]; }
    void setReserve(int i_idx, u8 i_itemNo) { mReserve[i_idx] = i_itemNo; }

    /* 0x00 */ u8 mBeast[8];
    /* 0x08 */ u8 mBait[8];
    /* 0x10 */ u8 mReserve[8];
};  // Size: 0x18

STATIC_ASSERT(sizeof(dSv_player_bag_item_c) == 0x18);

class dSv_player_get_bag_item_c {
public:
    void init();
    void onBeast(u8);
    BOOL isBeast(u8);
    void onBait(u8);
    BOOL isBait(u8);
    void onReserve(u8);
    BOOL isReserve(u8);

    /* 0x0 */ u32 mReserveFlags;
    /* 0x4 */ u8 mBeastFlags;
    /* 0x5 */ u8 mBaitFlags;
    /* 0x6 */ u8 unk_0x6[0xC - 0x6]; // there's probably an unused field here
};  // Size: 0xC

STATIC_ASSERT(sizeof(dSv_player_get_bag_item_c) == 0xC);

class dSv_player_bag_item_record_c {
public:
    void init();

    u8 getBeastNum(int i_idx) { return mBeastNum[i_idx]; }
    void setBeastNum(int i_idx, u8 num) { mBeastNum[i_idx] = num; }
    u8 getBaitNum(int i_idx) { return mBaitNum[i_idx]; }
    void setBaitNum(int i_idx, u8 num) { mBaitNum[i_idx] = num; }
    u8 getReserveNum(int i_idx) { return mReserveNum[i_idx]; }
    void setReserveNum(int i_idx, u8 num) { mReserveNum[i_idx] = num; }

    /* 0x00 */ u8 mBeastNum[8];
    /* 0x08 */ u8 mBaitNum[8];
    /* 0x10 */ u8 mReserveNum[8];
};  // Size: 0x18

STATIC_ASSERT(sizeof(dSv_player_bag_item_record_c) == 0x18);

class dSv_player_collect_c {
public:
    void init();
    void onCollect(int, u8);
    void offCollect(int, u8);
    BOOL isCollect(int, u8);
    void setCollect(int idx, u8 byte) { mCollect[idx] = byte; }
    u8 checkCollect(int idx) { return mCollect[idx]; }
    void onTact(u8);
    BOOL isTact(u8);
    void onTriforce(u8);
    BOOL isTriforce(u8);
    void onSymbol(u8);
    BOOL isSymbol(u8);
    int getTriforceNum();

    /* 0x0 */ u8 mCollect[8];
    /* 0x8 */ u8 field_0x8;
    /* 0x9 */ u8 mTact;
    /* 0xA */ u8 mTriforce;
    /* 0xB */ u8 mSymbol;
    /* 0xC */ u8 field_0xc;
};  // Size: 0xD

STATIC_ASSERT(sizeof(dSv_player_collect_c) == 0xD);

enum dIslandRoomNo_e {
    // Room 0 on the sea is not an island, it's the sea floor, used to load islands as you sail.
    dIsleRoom_SeaFloor_e = 0,

    /* 0x01 */ dIsleRoom_ForsakenFortress_e       = 1,
    /* 0x02 */ dIsleRoom_StarIsland_e             = 2,
    /* 0x03 */ dIsleRoom_NorthernFairyIsland_e    = 3,
    /* 0x04 */ dIsleRoom_GaleIsle_e               = 4,
    /* 0x05 */ dIsleRoom_CrescentMoonIsland_e     = 5,
    /* 0x06 */ dIsleRoom_SevenStarIsles_e         = 6,
    /* 0x07 */ dIsleRoom_OverlookIsland_e         = 7,
    /* 0x08 */ dIsleRoom_FourEyeReef_e            = 8,
    /* 0x09 */ dIsleRoom_MotherandChildIsles_e    = 9,
    /* 0x0A */ dIsleRoom_SpectacleIsland_e        = 10,
    /* 0x0B */ dIsleRoom_WindfallIsland_e         = 11,
    /* 0x0C */ dIsleRoom_PawprintIsle_e           = 12,
    /* 0x0D */ dIsleRoom_DragonRoostIsland_e      = 13,
    /* 0x0E */ dIsleRoom_FlightControlPlatform_e  = 14,
    /* 0x0F */ dIsleRoom_WesternFairyIsland_e     = 15,
    /* 0x10 */ dIsleRoom_RockSpireIsle_e          = 16,
    /* 0x11 */ dIsleRoom_TingleIsland_e           = 17,
    /* 0x12 */ dIsleRoom_NorthernTriangleIsland_e = 18,
    /* 0x13 */ dIsleRoom_EasternFairyIsland_e     = 19,
    /* 0x14 */ dIsleRoom_FireMountain_e           = 20,
    /* 0x15 */ dIsleRoom_StarBeltArchipelago_e    = 21,
    /* 0x16 */ dIsleRoom_ThreeEyeReef_e           = 22,
    /* 0x17 */ dIsleRoom_GreatfishIsle_e          = 23,
    /* 0x18 */ dIsleRoom_CyclopsReef_e            = 24,
    /* 0x19 */ dIsleRoom_SixEyeReef_e             = 25,
    /* 0x1A */ dIsleRoom_ToweroftheGods_e         = 26,
    /* 0x1B */ dIsleRoom_EasternTriangleIsland_e  = 27,
    /* 0x1C */ dIsleRoom_ThornedFairyIsland_e     = 28,
    /* 0x1D */ dIsleRoom_NeedleRockIsle_e         = 29,
    /* 0x1E */ dIsleRoom_IsletofSteel_e           = 30,
    /* 0x1F */ dIsleRoom_StoneWatcherIsland_e     = 31,
    /* 0x20 */ dIsleRoom_SouthernTriangleIsland_e = 32,
    /* 0x21 */ dIsleRoom_PrivateOasis_e           = 33,
    /* 0x22 */ dIsleRoom_BombIsland_e             = 34,
    /* 0x23 */ dIsleRoom_BirdsPeakRock_e          = 35,
    /* 0x24 */ dIsleRoom_DiamondSteppeIsland_e    = 36,
    /* 0x25 */ dIsleRoom_FiveEyeReef_e            = 37,
    /* 0x26 */ dIsleRoom_SharkIsland_e            = 38,
    /* 0x27 */ dIsleRoom_SouthernFairyIsland_e    = 39,
    /* 0x28 */ dIsleRoom_IceRingIsle_e            = 40,
    /* 0x29 */ dIsleRoom_ForestHaven_e            = 41,
    /* 0x2A */ dIsleRoom_CliffPlateauIsles_e      = 42,
    /* 0x2B */ dIsleRoom_HorseshoeIsland_e        = 43,
    /* 0x2C */ dIsleRoom_OutsetIsland_e           = 44,
    /* 0x2D */ dIsleRoom_HeadstoneIsland_e        = 45,
    /* 0x2E */ dIsleRoom_TwoEyeReef_e             = 46,
    /* 0x2F */ dIsleRoom_AngularIsles_e           = 47,
    /* 0x30 */ dIsleRoom_BoatingCourse_e          = 48,
    /* 0x31 */ dIsleRoom_FiveStarIsles_e          = 49,
};

enum dIslandIndex_e {
    dIsleIdx_ForsakenFortress_e       = 0,
    dIsleIdx_StarIsland_e             = 1,
    dIsleIdx_NorthernFairyIsland_e    = 2,
    dIsleIdx_GaleIsle_e               = 3,
    dIsleIdx_CrescentMoonIsland_e     = 4,
    dIsleIdx_SevenStarIsles_e         = 5,
    dIsleIdx_OverlookIsland_e         = 6,
    dIsleIdx_FourEyeReef_e            = 7,
    dIsleIdx_MotherandChildIsles_e    = 8,
    dIsleIdx_SpectacleIsland_e        = 9,
    dIsleIdx_WindfallIsland_e         = 10,
    dIsleIdx_PawprintIsle_e           = 11,
    dIsleIdx_DragonRoostIsland_e      = 12,
    dIsleIdx_FlightControlPlatform_e  = 13,
    dIsleIdx_WesternFairyIsland_e     = 14,
    dIsleIdx_RockSpireIsle_e          = 15,
    dIsleIdx_TingleIsland_e           = 16,
    dIsleIdx_NorthernTriangleIsland_e = 17,
    dIsleIdx_EasternFairyIsland_e     = 18,
    dIsleIdx_FireMountain_e           = 19,
    dIsleIdx_StarBeltArchipelago_e    = 20,
    dIsleIdx_ThreeEyeReef_e           = 21,
    dIsleIdx_GreatfishIsle_e          = 22,
    dIsleIdx_CyclopsReef_e            = 23,
    dIsleIdx_SixEyeReef_e             = 24,
    dIsleIdx_ToweroftheGods_e         = 25,
    dIsleIdx_EasternTriangleIsland_e  = 26,
    dIsleIdx_ThornedFairyIsland_e     = 27,
    dIsleIdx_NeedleRockIsle_e         = 28,
    dIsleIdx_IsletofSteel_e           = 29,
    dIsleIdx_StoneWatcherIsland_e     = 30,
    dIsleIdx_SouthernTriangleIsland_e = 31,
    dIsleIdx_PrivateOasis_e           = 32,
    dIsleIdx_BombIsland_e             = 33,
    dIsleIdx_BirdsPeakRock_e          = 34,
    dIsleIdx_DiamondSteppeIsland_e    = 35,
    dIsleIdx_FiveEyeReef_e            = 36,
    dIsleIdx_SharkIsland_e            = 37,
    dIsleIdx_SouthernFairyIsland_e    = 38,
    dIsleIdx_IceRingIsle_e            = 39,
    dIsleIdx_ForestHaven_e            = 40,
    dIsleIdx_CliffPlateauIsles_e      = 41,
    dIsleIdx_HorseshoeIsland_e        = 42,
    dIsleIdx_OutsetIsland_e           = 43,
    dIsleIdx_HeadstoneIsland_e        = 44,
    dIsleIdx_TwoEyeReef_e             = 45,
    dIsleIdx_AngularIsles_e           = 46,
    dIsleIdx_BoatingCourse_e          = 47,
    dIsleIdx_FiveStarIsles_e          = 48,

    dIsleIdx_COUNT_e = 49,
};

class dSv_player_map_c {
public:
    void init();
    void onGetMap(int);
    BOOL isGetMap(int);
    void onOpenMap(int);
    void offOpenMap(int);
    BOOL isOpenMap(int);
    void onCompleteMap(int);
    void offCompleteMap(int);
    BOOL isCompleteMap(int);
    void onTriforce(int);
    void offTriforce(int);
    BOOL isTriforce(int);
    int getCollectMapNum();
    void onFmapBit(int, u8);
    BOOL isFmapBit(int, u8);
    void onSaveArriveGrid(int);
    BOOL isSaveArriveGrid(int);
    void onSaveArriveGridForAgb(int);
    BOOL isSaveArriveGridForAgb(int);

    /* 0x00 */ u32 field_0x0[4][4];
    /* 0x40 */ u8 mFmapBits[dIsleIdx_COUNT_e];
    /* 0x71 */ u8 field_0x71[16];
    /* 0x81 */ u8 field_0x81;
    /* 0x82 */ u8 field_0x82[0x84 - 0x82];
};  // Size: 0x84

STATIC_ASSERT(sizeof(dSv_player_map_c) == 0x84);

class dSv_player_info_c {
public:
    void init();

    const char* getPlayerName() const { return mPlayerName; }
    void setPlayerName(const char* name) { strcpy(mPlayerName, name); }
    u8 getClearCount() { return mClearCount; }
    void setClearCount(u8 count) { mClearCount = count; }
    void clearCountUp() {}
    void addDeathCount() {
        if (mDeathCount < 9999)
            mDeathCount++;
    }
    void getPuzzleInfo() {}
    void setPuzzleInfo(u8) {}
    void setPuzzleData(int, u8) {}
    u8 getRandomSalvage() { return mRandomSalvagePoint; }
    void setRandomSalvage(u8 point) { mRandomSalvagePoint = point; }

    /* 0x00 */ u8 field_0x0[0x10];
    /* 0x10 */ u16 field_0x10;
    /* 0x10 */ u16 mDeathCount;
    /* 0x14 */ char mPlayerName[17];
    /* 0x25 */ char field_0x25[17];
    /* 0x36 */ char field_0x36[17];
    /* 0x47 */ char field_0x47[17];
    /* 0x58 */ u8 mClearCount;
    /* 0x59 */ u8 mRandomSalvagePoint;
    /* 0x5A */ u8 field_0x5a[0x5c - 0x5a];
};  // Size: 0x5C

STATIC_ASSERT(sizeof(dSv_player_info_c) == 0x5C);

class dSv_player_config_c {
public:
    void init();
    s32 checkVibration();

    u8 getRuby() { return mRuby; }
    void setRuby(u8 ruby) { mRuby = ruby; }
    u8 getSound() { return mSoundMode; }
    void setSound(u8 mode) { mSoundMode = mode; }
    u8 getAttentionType() { return mAttentionType; }
    void setAttentionType(u8 type) { mAttentionType = type; }
    u8 getVibration() { return mVibration; }
    void setVibration(u8 vib) { mVibration = vib; }

    /* 0x0 */ u8 mRuby;
    /* 0x1 */ u8 mSoundMode;
    /* 0x2 */ u8 mAttentionType;
    /* 0x3 */ u8 mVibration;
    /* 0x4 */ u8 field_0x4;
};

STATIC_ASSERT(sizeof(dSv_player_config_c) == 0x5);

class dSv_player_priest_c {
public:
    void init();
    void set(u8, cXyz&, s16, s8);

    u8 getFlag() { return field_0xf; }
    cXyz& getPos() { return field_0x0; }
    s16 getRotate() { return field_0xc; }
    s8 getRoomNo() { return field_0xe; }

    /* 0x0 */ cXyz field_0x0;
    /* 0xC */ s16 field_0xc;
    /* 0xE */ s8 field_0xe;
    /* 0xF */ u8 field_0xf;
};

STATIC_ASSERT(sizeof(dSv_player_priest_c) == 0x10);

class dSv_player_status_c_c {
public:
    void init();

    /* 0x00 */ dSv_player_status_a_c mRecollectStatusA;
    /* 0x18 */ dSv_player_item_c mRecollectItem;
    /* 0x2D */ dSv_player_item_record2_c mRecollectItemRecord;
    /* 0x30 */ dSv_player_item_max2_c mRecollectItemMax;
    /* 0x33 */ dSv_player_bag_item_c mRecollectBagItem;
    /* 0x4B */ dSv_player_bag_item_record_c mRecollectBagItemRecord;
    /* 0x63 */ dSv_player_collect_c mRecollectCollect;
};  // Size: 0x70

STATIC_ASSERT(sizeof(dSv_player_status_c_c) == 0x70);

class dSv_player_c {
public:
    void init();

    dSv_player_status_a_c& getPlayerStatusA() { return mPlayerStatusA; }
    dSv_player_status_a_c* getpPlayerStatusA() { return &mPlayerStatusA; }

    dSv_player_status_b_c& getPlayerStatusB() { return mPlayerStatusB; }
    dSv_player_status_b_c* getpPlayerStatusB() { return &mPlayerStatusB; }
    
    dSv_player_return_place_c& getPlayerReturnPlace() { return mReturnPlace; }
    dSv_player_return_place_c* getpPlayerReturnPlace() { return &mReturnPlace; }
    
    dSv_player_item_c& getItem() { return mPlayerItem; }
    dSv_player_item_c* getpItem() { return &mPlayerItem; }

    dSv_player_get_item_c& getGetItem() { return mGetItem; }
    dSv_player_get_item_c* getpGetItem() { return &mGetItem; }
    
    dSv_player_item_record_c& getItemRecord() { return mItemRecord; }
    dSv_player_item_record_c* getpItemRecord() { return &mItemRecord; }
    
    dSv_player_item_max_c& getItemMax() { return mItemMax; }
    dSv_player_item_max_c* getpItemMax() { return &mItemMax; }
    
    dSv_player_bag_item_c& getBagItem() { return mBagItem; }
    dSv_player_bag_item_c* getpBagItem() { return &mBagItem; }
    
    dSv_player_get_bag_item_c& getGetBagItem() { return mGetBagItem; }
    dSv_player_get_bag_item_c* getpGetBagItem() { return &mGetBagItem; }
    
    dSv_player_bag_item_record_c& getBagItemRecord() { return mBagItemRecord; }
    dSv_player_bag_item_record_c* getpBagItemRecord() { return &mBagItemRecord; }
    
    dSv_player_collect_c& getCollect() { return mCollect; }
    dSv_player_collect_c* getpCollect() { return &mCollect; }
    
    dSv_player_map_c& getMap() { return mMap; }
    dSv_player_map_c* getpMap() { return &mMap; }
    
    dSv_player_info_c& getPlayerInfo() { return mInfo; }
    dSv_player_info_c* getpPlayerInfo() { return &mInfo; }
    
    dSv_player_config_c& getConfig() { return mConfig; }
    dSv_player_config_c* getpConfig() { return &mConfig; }
    
    dSv_player_priest_c& getPriest() { return mPriest; }
    dSv_player_priest_c* getpPriest() { return &mPriest; }

    dSv_player_status_c_c* getpPlayerStatusC(int i_idx) { return &mStatusC[i_idx]; }

    static const int PLAYER_STATUS_C_COUNT = 4;

    static const int PACKED_STRUCT_SIZE =
        sizeof(dSv_player_status_a_c) +
        sizeof(dSv_player_status_b_c) +
        sizeof(dSv_player_return_place_c) +
        sizeof(dSv_player_item_c) +
        sizeof(dSv_player_get_item_c) +
        sizeof(dSv_player_item_record_c) +
        sizeof(dSv_player_item_max_c) +
        sizeof(dSv_player_bag_item_c) +
        sizeof(dSv_player_get_bag_item_c) +
        sizeof(dSv_player_bag_item_record_c) +
        sizeof(dSv_player_collect_c) +
        sizeof(dSv_player_map_c) +
        sizeof(dSv_player_info_c) +
        sizeof(dSv_player_config_c) +
        sizeof(dSv_player_priest_c) +
        sizeof(dSv_player_status_c_c) * PLAYER_STATUS_C_COUNT;

    /* 0x000 */ dSv_player_status_a_c mPlayerStatusA;
    /* 0x018 */ dSv_player_status_b_c mPlayerStatusB;
    /* 0x030 */ dSv_player_return_place_c mReturnPlace;
    /* 0x03C */ dSv_player_item_c mPlayerItem;
    /* 0x051 */ dSv_player_get_item_c mGetItem;
    /* 0x066 */ dSv_player_item_record_c mItemRecord;
    /* 0x06E */ dSv_player_item_max_c mItemMax;
    /* 0x076 */ dSv_player_bag_item_c mBagItem;
    /* 0x08E */ /* 2 bytes of alignment padding */
    /* 0x090 */ dSv_player_get_bag_item_c mGetBagItem;
    /* 0x09C */ dSv_player_bag_item_record_c mBagItemRecord;
    /* 0x0B4 */ dSv_player_collect_c mCollect;
    /* 0x0C1 */ /* 3 bytes of alignment padding */
    /* 0x0C4 */ dSv_player_map_c mMap;
    /* 0x148 */ dSv_player_info_c mInfo;
    /* 0x1A4 */ dSv_player_config_c mConfig;
    /* 0x1A9 */ /* 3 bytes of alignment padding */
    /* 0x1AC */ dSv_player_priest_c mPriest;
    /* 0x1BC */ dSv_player_status_c_c mStatusC[PLAYER_STATUS_C_COUNT];
    /* 0x37C */ /* 4 bytes of alignment padding */
};  // Size: 0x380

STATIC_ASSERT(sizeof(dSv_player_c) == 0x380);

class dSv_memBit_c {
public:
    enum {
        /* 0x0 */ MAP,
        /* 0x1 */ COMPASS,
        /* 0x2 */ BOSS_KEY,
        /* 0x3 */ STAGE_BOSS_ENEMY,
        /* 0x4 */ STAGE_LIFE,
        /* 0x5 */ STAGE_BOSS_DEMO,
    };

    void init();
    void onTbox(int);
    BOOL isTbox(int);
    void onSwitch(int);
    void offSwitch(int);
    BOOL isSwitch(int);
    BOOL revSwitch(int);
    void onItem(int);
    BOOL isItem(int);
    void onVisitedRoom(int);
    BOOL isVisitedRoom(int);
    void onDungeonItem(int);
    void offDungeonItem(int);
    BOOL isDungeonItem(int);

    u8 getKeyNum() { return mKeyNum; }
    void setKeyNum(u8 i_keyNum) { mKeyNum = i_keyNum; }
    void onDungeonItemMap() { onDungeonItem(MAP); }
    void offDungeonItemMap() { offDungeonItem(MAP); }
    BOOL isDungeonItemMap() { return isDungeonItem(MAP); }
    void onDungeonItemCompass() { onDungeonItem(COMPASS); }
    void offDungeonItemCompass() { offDungeonItem(COMPASS); }
    BOOL isDungeonItemCompass() { return isDungeonItem(COMPASS); }
    void onDungeonItemBossKey() { onDungeonItem(BOSS_KEY); }
    void offDungeonItemBossKey() { offDungeonItem(BOSS_KEY); }
    BOOL isDungeonItemBossKey() { return isDungeonItem(BOSS_KEY); }
    void onStageBossEnemy() { onDungeonItem(STAGE_BOSS_ENEMY); }
    void offStageBossEnemy() { offDungeonItem(STAGE_BOSS_ENEMY); }
    BOOL isStageBossEnemy() { return isDungeonItem(STAGE_BOSS_ENEMY); }
    void onStageLife() { onDungeonItem(STAGE_LIFE); }
    void offStageLife() { offDungeonItem(STAGE_LIFE); }
    BOOL isStageLife() { return isDungeonItem(STAGE_LIFE); }
    void onStageBossDemo() { onDungeonItem(STAGE_BOSS_DEMO); }
    void offStageBossDemo() { offDungeonItem(STAGE_BOSS_DEMO); }
    BOOL isStageBossDemo() { return isDungeonItem(STAGE_BOSS_DEMO); }

    /* 0x00 */ u32 mTbox;
    /* 0x04 */ u32 mSwitch[4];
    /* 0x14 */ u32 mItem[1];
    /* 0x18 */ u32 mVisitedRoom[2];
    /* 0x20 */ u8 mKeyNum;
    /* 0x21 */ u8 mDungeonItem;
};  // Size: 0x24

STATIC_ASSERT(sizeof(dSv_memBit_c) == 0x24);

class dSv_ocean_c {
public:
    void init();
    void onOceanSvBit(u8 i_grid, u16 i_bit);
    BOOL isOceanSvBit(u8 i_grid, u16 i_bit);

    /* 0x0 */ u16 field_0x0[50];
};

STATIC_ASSERT(sizeof(dSv_ocean_c) == 0x64);

class dSv_event_c {
public:
    void init();
    void onEventBit(u16);
    void offEventBit(u16);
    BOOL isEventBit(u16);
    void setEventReg(u16, u8);
    u8 getEventReg(u16);

    u8* getPEventBit() { return mFlags; }

    /* 0x0 */ u8 mFlags[0x100];
};  // Size: 0x100

STATIC_ASSERT(sizeof(dSv_event_c) == 0x100);

class dSv_reserve_c {
public:
    void init();

    /* 0x0 */ u8 mReserve[0x50];
};  // Size: 0x50

class dSv_memory_c {
public:
    dSv_memory_c() { init(); }
    void init();

    dSv_memBit_c& getBit() { return mMembit; }

    /* 0x0 */ dSv_memBit_c mMembit;
};  // Size: 0x24

STATIC_ASSERT(sizeof(dSv_memory_c) == 0x24);

class dSv_danBit_c {
public:
    int init(s8);
    void onSwitch(int);
    void offSwitch(int);
    BOOL isSwitch(int);
    BOOL revSwitch(int);

    u8 getGbaRupeeCount() { return mGbaRupeeCount; }
    void incGbaRupeeCount() { mGbaRupeeCount++; }

    /* 0x0 */ s8 mStageNo;
    /* 0x1 */ u8 mGbaRupeeCount;
    /* 0x4 */ u32 mSwitch[2];
};  // Size: 0xC

class dSv_zoneBit_c {
public:
    void init();
    void clearRoomSwitch();
    void onSwitch(int);
    void offSwitch(int);
    BOOL isSwitch(int);
    BOOL revSwitch(int);
    void onItem(int);
    BOOL isItem(int);

    static const int SWITCH_MAX = 48;

    /* 0x0 */ u16 mSwitch[3];
    /* 0x6 */ u16 mItem;
};  // Size: 0x8

class dSv_zoneActor_c {
public:
    void init();
    void on(int);
    BOOL is(int);

    static const int ACTOR_MAX = 512;

    /* 0x0 */ u32 mActorFlags[16];
};  // Size: 0x40

class dSv_zone_c {
public:
    dSv_zone_c() { mRoomNo = -1; }
    void init(int);

    dSv_zoneBit_c& getZoneBit() { return mZoneBit; }
    dSv_zoneActor_c& getActor() { return mZoneActor; }
    s8 getRoomNo() { return mRoomNo; }
    void reset() { mRoomNo = -1; }

    /* 0x00 */ s8 mRoomNo;
    /* 0x02 */ dSv_zoneBit_c mZoneBit;
    /* 0x0C */ dSv_zoneActor_c mZoneActor;
};  // Size: 0x4C

class dSv_restart_c {
public:
    void setRoom(cXyz const&, s16, s8);
    void setRestartOption(s8);
    void setRestartOption(s8, cXyz*, s16, s8);

    void setRoomParam(u32 param) { mRestartParam = param; }
    void setStartPoint(s16 point) { mStartCode = point; }
    void setLastSceneInfo(f32 speed, u32 mode) {
        mLastSpeedF = speed;
        mLastMode = mode;
    }

    s16 getStartPoint() { return mStartCode; }
    f32 getLastSpeedF() { return mLastSpeedF; }
    u32 getLastMode() { return mLastMode; }
    s8 getRoomNo() { return mRestartRoom; }
    u32 getRoomParam() { return mRestartParam; }
    cXyz& getRoomPos() { return mRestartPos; }
    s16 getRoomAngleY() { return mRestartAngle; }
    s8 getRestartOption() { return mOption; }
    s8 getRestartOptionRoomNo() { return mOptionRoomNo; }
    s16 getRestartOptionPoint() { return mOptionPoint; }
    s16 getRestartOptionAngleY() { return mOptionRoomAngleY; }
    cXyz& getRestartOptionPos() { return mOptionRoomPos; }

    /* 0x00 */ s8 mRestartRoom;
    /* 0x01 */ u8 mOption;
    /* 0x02 */ s8 mOptionRoomNo;
    /* 0x04 */ s16 mOptionPoint;
    /* 0x06 */ s16 mOptionRoomAngleY;
    /* 0x08 */ cXyz mOptionRoomPos;
    /* 0x14 */ s16 mStartCode;
    /* 0x16 */ s16 mRestartAngle;
    /* 0x18 */ cXyz mRestartPos;
    /* 0x24 */ u32 mRestartParam;
    /* 0x28 */ f32 mLastSpeedF;
    /* 0x2C */ u32 mLastMode;
};  // Size: 0x30

class dSv_turnRestart_c {
public:
    void set(cXyz const&, s16, s8, u32, cXyz const&, s16, int);

    u32 getParam() { return mParam; }
    cXyz& getPos() { return mPosition; }
    s16 getAngleY() { return mAngleY; }
    s8 getRoomNo() { return mRoomNo; }
    cXyz& getShipPos() { return mShipPos; }
    s16 getShipAngleY() { return mShipAngleY; }
#if VERSION > VERSION_DEMO
    // The "HasShip" name is fake. These inlines don't exist in the demo, but probably do in the final release.
    BOOL getHasShip() { return mHasShip; }
    void setHasShip(BOOL hasShip) { mHasShip = hasShip; }
#endif

    /* 0x00 */ cXyz mPosition;
    /* 0x0C */ u32 mParam;
    /* 0x10 */ s16 mAngleY;
    /* 0x12 */ s8 mRoomNo;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14[0x24 - 0x14];
    /* 0x24 */ cXyz mShipPos;
    /* 0x30 */ s16 mShipAngleY;
#if VERSION > VERSION_DEMO
    /* 0x34 */ BOOL mHasShip;
#endif
};  // Size: 0x38

class dSv_save_c {
public:
    void init();

    dSv_player_c& getPlayer() { return mPlayer; }
    dSv_memory_c* getPSave() { return mMemory; }
    dSv_ocean_c& getOcean() { return mOcean; }
    dSv_ocean_c* getPOcean() { return &mOcean; }
    dSv_event_c& getEvent() { return mEvent; }
    dSv_event_c* getPEvent() { return &mEvent; }
    dSv_reserve_c* getPReserve() { return &mReserve; }

    dSv_memory_c& getSave(int i_stageNo) { return mMemory[i_stageNo]; }
    void putSave(int i_stageNo, dSv_memory_c i_mem) { mMemory[i_stageNo] = i_mem; }

    enum SaveStageTbl {
        /* 0x00 */ STAGE_SEA,
        /* 0x01 */ STAGE_SEA2,
        /* 0x02 */ STAGE_FF,
        /* 0x03 */ STAGE_DRC,
        /* 0x04 */ STAGE_FW,
        /* 0x05 */ STAGE_TOTG,
        /* 0x06 */ STAGE_ET,
        /* 0x07 */ STAGE_WT,
        /* 0x08 */ STAGE_GT,
        /* 0x09 */ STAGE_HYRULE,
        /* 0x0A */ STAGE_SHIP,
        /* 0x0B */ STAGE_MISC, // Mostly interior rooms but not all
        /* 0x0C */ STAGE_SUBDUNGEON, // Name based on the debug map select entry サブダンジョン
        /* 0x0D */ STAGE_SUBDUNGEON_NEW, // Name based on the debug map select entry サブダン新規追加
        /* 0x0E */ STAGE_BLUE_CHU_JELLY,
        /* 0x0F */ STAGE_TEST,
        /* 0x10 */ STAGE_MAX,
    };

    static const int PACKED_STRUCT_SIZE =
        dSv_player_c::PACKED_STRUCT_SIZE +
        sizeof(dSv_memory_c) * STAGE_MAX +
        sizeof(dSv_ocean_c) +
        sizeof(dSv_event_c) +
        sizeof(dSv_reserve_c);

    /* 0x000 */ dSv_player_c mPlayer;
    /* 0x380 */ dSv_memory_c mMemory[STAGE_MAX];
    /* 0x5C0 */ dSv_ocean_c mOcean;
    /* 0x624 */ dSv_event_c mEvent;
    /* 0x724 */ dSv_reserve_c mReserve;
    /* 0x774 */ /* 4 bytes of padding */
};  // Size: 0x778

STATIC_ASSERT(sizeof(dSv_save_c) == 0x778);

class dSv_info_c {
public:
    void init();
    void reinit();
    void getSave(int);
    void putSave(int);
    void initZone();
    int createZone(int);
    void onSwitch(int, int);
    void offSwitch(int, int);
    BOOL isSwitch(int, int);
    BOOL revSwitch(int, int);
    void onItem(int, int);
    BOOL isItem(int, int);
    void onActor(int, int);
    BOOL isActor(int, int);
    int memory_to_card(char*, int);
    int card_to_memory(char*, int);
    int initdata_to_card(char*, int);

    dSv_save_c& getSavedata() { return mSavedata; }
    dSv_player_c& getPlayer() { return mSavedata.getPlayer(); }
    dSv_memory_c* getPSave() { return mSavedata.getPSave(); }
    dSv_ocean_c& getOcean() { return mSavedata.getOcean(); }
    dSv_ocean_c* getPOcean() { return mSavedata.getPOcean(); }
    dSv_event_c& getEvent() { return mSavedata.getEvent(); }
    dSv_event_c* getPEvent() { return mSavedata.getPEvent(); }
    dSv_reserve_c* getPReserve() { return mSavedata.getPReserve(); }
    dSv_restart_c& getRestart() { return mRestart; }
    dSv_event_c& getTmp() { return mTmp; }
    dSv_turnRestart_c& getTurnRestart() { return mTurnRestart; }
    dSv_memory_c& getMemory() { return mMemory; }
    dSv_danBit_c& getDan() { return mDan; }
    dSv_zone_c& getZone(int id) { return mZone[id]; }

    void removeZone(int zoneNo) { mZone[zoneNo].reset(); }
    void initDan(s8 i_stage) { mDan.init(i_stage); }

    u8 getDataNum() { return mDataNum; }
    void getMemCardCheckID() {}
    void getNewFile() {}
    void getNoFile() {}
    void setDataNum(u8 num) { mDataNum = num; }
    void setMemCardCheckID(u64) {}
    void setNewFile(u8) {}
    void setNoFile(u8) {}

    static const int MEMORY_SWITCH = 0x80;
    static const int DAN_SWITCH = 0x40;
    static const int ZONE_SWITCH = 0x30;

    static const int MEMORY_ITEM = 0x40;
    static const int ZONE_ITEM = 0x10;

    static const int ZONE_MAX = 0x20;

    /* 0x0000 */ dSv_save_c mSavedata;
    /* 0x0778 */ dSv_memory_c mMemory;
    /* 0x079C */ dSv_danBit_c mDan;
    /* 0x07A8 */ dSv_zone_c mZone[ZONE_MAX];
    /* 0x1128 */ dSv_restart_c mRestart;
    /* 0x1158 */ dSv_event_c mTmp;
    /* 0x1258 */ dSv_turnRestart_c mTurnRestart;
    /* 0x1290 */ u8 mDataNum;
    /* 0x1291 */ u8 field_0x1291;
    /* 0x1292 */ u8 field_0x1292;
    /* 0x1298 */ s64 field_0x1298;
};  // Size: 0x12A0

#if VERSION > VERSION_DEMO
STATIC_ASSERT(sizeof(dSv_info_c) == 0x12A0);
#endif

#include "d/d_save_event_bit.inc"

#endif /* D_SAVE_D_SAVE_H */
