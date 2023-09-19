#ifndef D_SAVE_D_SAVE_H
#define D_SAVE_D_SAVE_H

#include "global.h"
#include "SSystem/SComponent/c_xyz.h"

class dSv_player_status_a_c {
public:
    /* 800589A8 */ void init();
  
    u8 getSelectEquip(int i_no) { return mSelectEquip[i_no]; }
    u8 getWalletSize() { return mWalletSize; }
    int getRupee() const { return mRupee; }
    u8 getMagic() { return mMagic; }

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
};  // Size: 0x18

STATIC_ASSERT(sizeof(dSv_player_status_a_c) == 0x18);

class dSv_player_status_b_c {
public:
    void init();

    void setDateIpl(s64 i_time) { mDateIPL = i_time; }
    u16 getDate() const { return mDate; }
    f32 getTime() const { return mTime; }
    void setDate(u16 i_date) { mDate = i_date; }
    void setTime(f32 i_time) { mTime = i_time; }
    s64 getDateIpl() const { return mDateIPL; }

    /* 0x00 */ u64 mDateIPL;
    /* 0x08 */ f32 field_0x8;
    /* 0x0C */ f32 mTime;
    /* 0x10 */ u16 mDate;
    /* 0x12 */ s16 mTactWindAngleX;
    /* 0x14 */ s16 mTactWindAngleY;
};  // Size: 0x18

STATIC_ASSERT(sizeof(dSv_player_status_b_c) == 0x18);

class dSv_player_return_place_c {
public:
    void init();
    void set(char const*, s8, u8);

    const s8 getRoomNo() const { return mRoomNo; }
    u8 getPlayerStatus() const { return mPlayerStatus; }
    char* getName() { return mName; }

    /* 0x00 */ char mName[8];
    /* 0x08 */ s8 mRoomNo;
    /* 0x09 */ u8 mPlayerStatus;
    /* 0x0A */ u8 unk_0xa;
    /* 0x0B */ u8 unk_0xb;
};  // Size: 0xC

STATIC_ASSERT(sizeof(dSv_player_return_place_c) == 0xC);

class dSv_player_item_c {
public:
    /* 80058C60 */ void init();
    /* 80058C7C */ void setBottleItemIn(u8, u8);
    /* 80058E1C */ void setEmptyBottleItemIn(u8);
    /* 80058E44 */ void setEmptyBottle();
    /* 800591B0 */ void setEquipBottleItemIn(u8);
    /* 80058F74 */ void setEquipBottleItemIn(u8, u8);
    /* 80059408 */ void setEquipBottleItemEmpty();
    /* 8005918C */ void setEquipBottleItemEmpty(u8);
    /* 8005942C */ u8 checkBottle(u8);
    /* 8005946C */ u8 checkEmptyBottle();

    u8 getItem(int i_idx) const { return mItems[i_idx]; }

    /* 0x00 */ u8 mItems[21];
};  // Size: 0x15

STATIC_ASSERT(sizeof(dSv_player_item_c) == 0x15);

class dSv_player_get_item_c {
public:
    /* 800594A8 */ void init();
    /* 800594C4 */ void onItem(int, u8);
    /* 8005955C */ BOOL isItem(int, u8);
    /* 800595F8 */ void onBottleItem(u8);
    /* 80059740 */ bool isBottleItem(u8);

    /* 0x0 */ u8 mItemFlags[21];
};  // Size: 0x15

STATIC_ASSERT(sizeof(dSv_player_get_item_c) == 0x15);

class dSv_player_item_record_c {
public:
    /* 80059848 */ void init();
    /* 8005987C */ void resetTimer(u16);
    /* 80059894 */ void decTimer();
    /* 800598D0 */ u16 getTimer();

    u8 getArrowNum() const { return mArrowNum; }
    u8 getBombNum() const { return mBombNum; }

    /* 0x0 */ u16 mTimer;
    /* 0x2 */ u8 field_0x2;
    /* 0x3 */ u8 mArrowNum;
    /* 0x4 */ u8 mBombNum;
    /* 0x5 */ u8 mBottleNum[3];
};  // Size: 0x8

STATIC_ASSERT(sizeof(dSv_player_item_record_c) == 0x8);

class dSv_player_item_max_c {
public:
    /* 800598D8 */ void init();

    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 mArrowNum;
    /* 0x2 */ u8 mBombNum;
    /* 0x3 */ u8 field_0x3[5];
};  // Size: 0x8

STATIC_ASSERT(sizeof(dSv_player_item_max_c) == 0x8);

class dSv_player_bag_item_c {
public:
    /* 80059908 */ void init();
    /* 80059968 */ void setBeastItem(u8);
    /* 800599D8 */ void setBeastItemEmpty(u8);
    /* 80059C30 */ bool checkBeastItem(u8);
    /* 80059C60 */ void setBaitItemChange(u8);
    /* 80059EB0 */ void setBaitItemChange(u8, u8);
    /* 8005A1A4 */ void setBaitItemEmpty(u8);
    /* 8005A0C8 */ void setBaitItemEmpty();
    /* 8005A248 */ void setBaitItem(u8);
    /* 8005A2D0 */ u8 checkBaitItemEmpty();
    /* 8005A2F4 */ u8 checkBaitItem(u8);
    /* 8005A584 */ void setReserveItemChange(u8, u8);
    /* 8005A334 */ void setReserveItemChange(u8);
    /* 8005A7C0 */ void setReserveItemEmpty(u8);
    /* 8005A79C */ void setReserveItemEmpty();
    /* 8005A7E4 */ void setReserveItem(u8);
    /* 8005A854 */ bool checkReserveItemEmpty();
    /* 8005A878 */ bool checkReserveItem(u8);

    u8 getBeast(int i_idx) const { return mBeast[i_idx]; }
    u8 getBait(int i_idx) const { return mBait[i_idx]; }
    u8 getReserve(int i_idx) const { return mReserve[i_idx]; }

    /* 0x00 */ u8 mBeast[8];
    /* 0x08 */ u8 mBait[8];
    /* 0x10 */ u8 mReserve[8];
};  // Size: 0x18

STATIC_ASSERT(sizeof(dSv_player_bag_item_c) == 0x18);

class dSv_player_get_bag_item_c {
public:
    /* 8005A8B8 */ void init();
    /* 8005A8CC */ void onBeast(u8);
    /* 8005A960 */ BOOL isBeast(u8);
    /* 8005A9F8 */ void onBait(u8);
    /* 8005AA8C */ BOOL isBait(u8);
    /* 8005AB24 */ void onReserve(u8);
    /* 8005ABB4 */ BOOL isReserve(u8);

    /* 0x0 */ u32 mReserveFlags;
    /* 0x4 */ u8 mBeastFlags;
    /* 0x5 */ u8 mBaitFlags;
    /* 0x6 */ u8 unk_0x6[0xC - 0x6];
};  // Size: 0xC

STATIC_ASSERT(sizeof(dSv_player_get_bag_item_c) == 0xC);

class dSv_player_bag_item_record_c {
public:
    /* 8005AC48 */ void init();

    u8 getBeastNum(int i_idx) const { return mBeastNum[i_idx]; }
    u8 getBaitNum(int i_idx) const { return mBaitNum[i_idx]; }
    u8 getReserveNum(int i_idx) const { return mReserveNum[i_idx]; }

    /* 0x00 */ u8 mBeastNum[8];
    /* 0x08 */ u8 mBaitNum[8];
    /* 0x10 */ u8 mReserveNum[8];
};  // Size: 0x18

STATIC_ASSERT(sizeof(dSv_player_bag_item_record_c) == 0x18);

class dSv_player_collect_c {
public:
    /* 8005ACA8 */ void init();
    /* 8005ACE0 */ void onCollect(int, u8);
    /* 8005AD78 */ void offCollect(int, u8);
    /* 8005AE10 */ BOOL isCollect(int, u8);
    /* 8005AEAC */ void onTact(u8);
    /* 8005AF40 */ BOOL isTact(u8);
    /* 8005AFD8 */ void onTriforce(u8);
    /* 8005B06C */ BOOL isTriforce(u8);
    /* 8005B104 */ void onSymbol(u8);
    /* 8005B198 */ BOOL isSymbol(u8);
    /* 8005B230 */ int getTriforceNum();

    /* 0x0 */ u8 field_0x0[8];
    /* 0x8 */ u8 field_0x8;
    /* 0x9 */ u8 mTact;
    /* 0xA */ u8 mTriforce;
    /* 0xB */ u8 mSymbol;
    /* 0xC */ u8 field_0xc;
};  // Size: 0xD

STATIC_ASSERT(sizeof(dSv_player_collect_c) == 0xD);

class dSv_player_map_c {
public:
    /* 8005B290 */ void init();
    /* 8005B320 */ void onGetMap(int);
    /* 8005B3CC */ BOOL isGetMap(int);
    /* 8005B47C */ void onOpenMap(int);
    /* 8005B528 */ void offOpenMap(int);
    /* 8005B5D4 */ BOOL isOpenMap(int);
    /* 8005B684 */ void onCompleteMap(int);
    /* 8005B730 */ void offCompleteMap(int);
    /* 8005B7DC */ BOOL isCompleteMap(int);
    /* 8005B88C */ void onTriforce(int);
    /* 8005B92C */ void offTriforce(int);
    /* 8005B9CC */ BOOL isTriforce(int);
    /* 8005BA70 */ int getCollectMapNum();
    /* 8005BAE8 */ void onFmapBit(int, u8);
    /* 8005BB84 */ BOOL isFmapBit(int, u8);
    /* 8005BC24 */ void onSaveArriveGrid(int);
    /* 8005BCBC */ BOOL isSaveArriveGrid(int);
    /* 8005BD54 */ void onSaveArriveGridForAgb(int);
    /* 8005BDEC */ BOOL isSaveArriveGridForAgb(int);

    /* 0x00 */ u32 field_0x0[4][4];
    /* 0x40 */ u8 field_0x40[49];
    /* 0x71 */ u8 field_0x71[16];
    /* 0x81 */ u8 field_0x81;
    /* 0x82 */ u8 field_0x82[0x84 - 0x82];
};  // Size: 0x84

STATIC_ASSERT(sizeof(dSv_player_map_c) == 0x84);

class dSv_player_info_c {
public:
    /* 8005BE84 */ void init();

    /* 0x00 */ u8 field_0x0[0x10];
    /* 0x10 */ u16 field_0x10;
    /* 0x10 */ u16 field_0x12;
    /* 0x14 */ char mPlayerName[17];
    /* 0x25 */ char field_0x25[17];
    /* 0x36 */ char field_0x36[17];
    /* 0x47 */ char field_0x47[17];
    /* 0x58 */ u8 mClearCount;
    /* 0x59 */ u8 mFmapIdx;
    /* 0x5A */ u8 field_0x5a[0x5c - 0x5a];
};  // Size: 0x5C

STATIC_ASSERT(sizeof(dSv_player_info_c) == 0x5C);

class dSv_player_config_c {
public:
    /* 8005BF2C */ void init();
    /* 8005BFA4 */ s32 checkVibration();

    u8 getVibration() const { return mVibration; }

    /* 0x0 */ u8 field_0x0;
    /* 0x1 */ u8 mSoundMode;
    /* 0x2 */ u8 mAttentionType;
    /* 0x3 */ u8 mVibration;
    /* 0x4 */ u8 field_0x4;
};

STATIC_ASSERT(sizeof(dSv_player_config_c) == 0x5);

class dSv_player_priest_c {
public:
    /* 8005BFC8 */ void init();
    /* 8005BFD4 */ void set(u8, cXyz&, s16, s8);

    /* 0x0 */ cXyz field_0x0;
    /* 0xC */ s16 field_0xc;
    /* 0xE */ s8 field_0xe;
    /* 0xF */ u8 field_0xf;
};

STATIC_ASSERT(sizeof(dSv_player_priest_c) == 0x10);

class dSv_player_status_c_c {
public:
    /* 8005BFFC */ void init();

    /* 0x00 */ dSv_player_status_a_c mRecollectStatusA;
    /* 0x18 */ dSv_player_item_c mRecollectItem;
    /* 0x2D */ u8 mRecollectItemRecord[3];
    /* 0x30 */ u8 mRecollectItemMax[3];
    /* 0x33 */ dSv_player_bag_item_c mRecollectBagItem;
    /* 0x4B */ dSv_player_bag_item_record_c mRecollectBagItemRecord;
    /* 0x63 */ u8 mRecollectCollect[13];
};  // Size: 0x70

STATIC_ASSERT(sizeof(dSv_player_status_c_c) == 0x70);

class dSv_player_c {
public:
    /* 8005C000 */ void init();

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

    /* 0x000 */ dSv_player_status_a_c mPlayerStatusA;
    /* 0x018 */ dSv_player_status_b_c mPlayerStatusB;
    /* 0x030 */ dSv_player_return_place_c mReturnPlace;
    /* 0x03C */ dSv_player_item_c mPlayerItem;
    /* 0x051 */ dSv_player_get_item_c mGetItem;
    /* 0x066 */ dSv_player_item_record_c mItemRecord;
    /* 0x06E */ dSv_player_item_max_c mItemMax;
    /* 0x076 */ dSv_player_bag_item_c mBagItem;
    /* 0x090 */ dSv_player_get_bag_item_c mGetBagItem;
    /* 0x09C */ dSv_player_bag_item_record_c mBagItemRecord;
    /* 0x0B4 */ dSv_player_collect_c mCollect;
    /* 0x0C4 */ dSv_player_map_c mMap;
    /* 0x148 */ dSv_player_info_c mInfo;
    /* 0x1A4 */ dSv_player_config_c mConfig;
    /* 0x1AC */ dSv_player_priest_c mPriest;
    /* 0x1BC */ dSv_player_status_c_c mStatusC[4];
};  // Size: 0x380 ?

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
        /* 0x7 */ STAGE_BOSS_ENEMY_2 = 7
    };

    /* 8005C094 */ void init();
    /* 8005C0EC */ void onTbox(int);
    /* 8005C188 */ BOOL isTbox(int);
    /* 8005C228 */ void onSwitch(int);
    /* 8005C2D4 */ void offSwitch(int);
    /* 8005C380 */ BOOL isSwitch(int);
    /* 8005C430 */ BOOL revSwitch(int);
    /* 8005C4EC */ void onItem(int);
    /* 8005C598 */ BOOL isItem(int);
    /* 8005C648 */ void onVisitedRoom(int);
    /* 8005C6F4 */ BOOL isVisitedRoom(int);
    /* 8005C7A4 */ void onDungeonItem(int);
    /* 8005C844 */ BOOL isDungeonItem(int);

    u8 getKeyNum() { return mKeyNum; }
    void setKeyNum(u8 i_keyNum) { mKeyNum = i_keyNum; }
    void onDungeonItemMap() { onDungeonItem(MAP); }
    BOOL isDungeonItemMap() { return isDungeonItem(MAP); }
    void onDungeonItemCompass() { onDungeonItem(COMPASS); }
    BOOL isDungeonItemCompass() { return isDungeonItem(COMPASS); }
    void onDungeonItemBossKey() { onDungeonItem(BOSS_KEY); }
    BOOL isDungeonItemBossKey() { return isDungeonItem(BOSS_KEY); }
    void onStageBossEnemy() { onDungeonItem(STAGE_BOSS_ENEMY); }
    BOOL isStageBossEnemy() { return isDungeonItem(STAGE_BOSS_ENEMY); }
    BOOL isStageBossEnemy2() { return isDungeonItem(STAGE_BOSS_ENEMY_2); }
    void onStageLife() { onDungeonItem(STAGE_LIFE); }
    BOOL isStageLife() { return isDungeonItem(STAGE_LIFE); }

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
    /* 8005C8E8 */ void init();
    /* 8005C908 */ void onOceanSvBit(u8, u16);
    /* 8005C9E8 */ BOOL isOceanSvBit(u8, u16);

    /* 0x0 */ u16 field_0x0[50];
};

STATIC_ASSERT(sizeof(dSv_ocean_c) == 0x64);

class dSv_event_c {
public:
    /* 8005CACC */ void init();
    /* 8005CB04 */ void onEventBit(u16);
    /* 8005CB1C */ void offEventBit(u16);
    /* 8005CB34 */ BOOL isEventBit(u16);
    /* 8005CB58 */ void setEventReg(u16, u8);
    /* 8005CB7C */ u8 getEventReg(u16);

    /* 0x0 */ u8 mFlags[0x100];
};  // Size: 0x100

STATIC_ASSERT(sizeof(dSv_event_c) == 0x100);

class dSv_reserve_c {
public:
    /* 8005CB94 */ void init();

    /* 0x0 */ u8 mReserve[0x50];
};  // Size: 0x50

class dSv_memory_c {
public:
    dSv_memory_c() { init(); }
    /* 8005CBB0 */ void init();

    dSv_memBit_c& getBit() { return mMembit; }
    const dSv_memBit_c& getBit() const { return mMembit; }

    /* 0x0 */ dSv_memBit_c mMembit;
};  // Size: 0x24

STATIC_ASSERT(sizeof(dSv_memory_c) == 0x24);

class dSv_danBit_c {
public:
    /* 8005CBD0 */ int init(s8);
    /* 8005CC08 */ void onSwitch(int);
    /* 8005CCB4 */ void offSwitch(int);
    /* 8005CD60 */ BOOL isSwitch(int);
    /* 8005CE10 */ BOOL revSwitch(int);

    /* 0x0 */ s8 mStageNo;
    /* 0x1 */ u8 field_0x1;
    /* 0x4 */ u32 mSwitch[2];
};  // Size: 0xC

class dSv_zoneBit_c {
public:
    /* 8005CECC */ void init();
    /* 8005CEF4 */ void clearRoomSwitch();
    /* 8005CF00 */ void onSwitch(int);
    /* 8005CFAC */ void offSwitch(int);
    /* 8005D054 */ BOOL isSwitch(int);
    /* 8005D100 */ BOOL revSwitch(int);
    /* 8005D1B8 */ void onItem(int);
    /* 8005D254 */ BOOL isItem(int);

    static const int SWITCH_MAX = 48;

    /* 0x0 */ u16 mSwitch[3];
    /* 0x6 */ u16 mItem;
};  // Size: 0x8

class dSv_zoneActor_c {
public:
    /* 8005D2F4 */ void init();
    /* 8005D314 */ void on(int);
    /* 8005D3BC */ BOOL is(int);

    static const int ACTOR_MAX = 512;

    /* 0x0 */ u32 mActorFlags[16];
};  // Size: 0x40

class dSv_zone_c {
public:
    dSv_zone_c() { mRoomNo = -1; }
    /* 8005D468 */ void init(int);

    dSv_zoneBit_c& getZoneBit() { return mZoneBit; }
    const dSv_zoneBit_c& getBit() const { return mZoneBit; }
    dSv_zoneActor_c& getActor() { return mZoneActor; }
    const dSv_zoneActor_c& getActor() const { return mZoneActor; }

    void reset() { mRoomNo = -1; }

    /* 0x00 */ s8 mRoomNo;
    /* 0x02 */ dSv_zoneBit_c mZoneBit;
    /* 0x0C */ dSv_zoneActor_c mZoneActor;
};  // Size: 0x4C

class dSv_restart_c {
public:
    /* 8005D4A4 */ void setRoom(cXyz const&, s16, s8);
    /* 8005D4C8 */ void setRestartOption(s8);
    /* 8005D584 */ void setRestartOption(s8, cXyz*, s16, s8);

    void setRoomParam(u32 param) { mRestartParam = param; }
    void setStartPoint(s16 point) { mStartCode = point; }
    void setLastSceneInfo(f32 speed, u32 mode) {
        mLastSpeedF = speed;
        mLastMode = mode;
    }

    s16 getStartPoint() const { return mStartCode; }
    u32 getLastMode() const { return mLastMode; }
    s8 getRoomNo() const { return mRestartRoom; }
    u32 getRoomParam() const { return mRestartParam; }
    cXyz& getRoomPos() { return mRestartPos; }
    s16 getRoomAngleY() const { return mRestartAngle; }

    /* 0x00 */ s8 mRestartRoom;
    /* 0x01 */ u8 field_0x1;
    /* 0x02 */ s8 mRoomNo;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 mRoomAngleY;
    /* 0x08 */ cXyz mRoomPos;
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

    u32 getParam() const { return mParam; }
    cXyz& getPos() { return mPosition; }
    s16 getAngleY() const { return mAngleY; }

    cXyz& getShipPos() { return field_0x24; }
    s16 getShipAngleY() const { return field_0x30; }
    s8 getRoomNo() { return mRoomNo; }

    /* 0x00 */ cXyz mPosition;
    /* 0x0C */ u32 mParam;
    /* 0x10 */ s16 mAngleY;
    /* 0x12 */ s8 mRoomNo;
    /* 0x13 */ u8 field_0x13;
    /* 0x14 */ u8 field_0x14[0x24 - 0x14];
    /* 0x24 */ cXyz field_0x24;
    /* 0x30 */ s16 field_0x30;
    /* 0x34 */ int field_0x34;
};  // Size: 0x38

class dSv_save_c {
public:
    /* 8005D860 */ void init();

    dSv_player_c& getPlayer() { return mPlayer; }
    dSv_event_c& getEvent() { return mEvent; }

    dSv_memory_c& getSave(int i_stageNo) { return mMemory[i_stageNo]; }
    void putSave(int i_stageNo, dSv_memory_c i_mem) { mMemory[i_stageNo] = i_mem; }

    const static int STAGE_MAX = 16;

    /* 0x000 */ dSv_player_c mPlayer;
    /* 0x380 */ dSv_memory_c mMemory[STAGE_MAX];
    /* 0x5C0 */ dSv_ocean_c mOcean;
    /* 0x624 */ dSv_event_c mEvent;
};  // Size: 0x724

STATIC_ASSERT(sizeof(dSv_save_c) == 0x728);

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
    void memory_to_card(char*, int);
    void card_to_memory(char*, int);
    int initdata_to_card(char*, int);

    dSv_save_c& getSavedata() { return mSavedata; }
    dSv_player_c& getPlayer() { return mSavedata.getPlayer(); }
    dSv_event_c& getEvent() { return mSavedata.getEvent(); }
    dSv_restart_c& getRestart() { return mRestart; }
    dSv_turnRestart_c& getTurnRestart() { return mTurnRestart; }
    dSv_memory_c& getMemory() { return mMemory; }
    dSv_zone_c& getZone(int id) { return mZone[id]; }

    void removeZone(int zoneNo) { mZone[zoneNo].reset(); }
    void initDan(s8 i_stage) { mDan.init(i_stage); }

    static const int MEMORY_SWITCH = 0x80;
    static const int DAN_SWITCH = 0x40;
    static const int ZONE_SWITCH = 0x30;

    static const int MEMORY_ITEM = 0x40;
    static const int ZONE_ITEM = 0x10;

    static const int ZONE_MAX = 0x20;

    /* 0x0000 */ dSv_save_c mSavedata;
    /* 0x0724 */ u8 unk_0x724[0x50];
    /* 0x0778 */ dSv_memory_c mMemory;
    /* 0x079C */ dSv_danBit_c mDan;
    /* 0x07A8 */ dSv_zone_c mZone[ZONE_MAX];
    /* 0x1128 */ dSv_restart_c mRestart;
    /* 0x1158 */ dSv_event_c mTmp;
    /* 0x1258 */ dSv_turnRestart_c mTurnRestart;
    /* 0x1290 */ u8 field_0x1290;
    /* 0x1291 */ u8 field_0x1291;
    /* 0x1292 */ u8 field_0x1292;
    /* 0x1298 */ s64 field_0x1298;
};  // Size: 0x12A0

STATIC_ASSERT(sizeof(dSv_info_c) == 0x12A0);

enum dSv_eventBit_e {
    EV_BIT_TALKED_TO_IRCH_IN_FOREST_HAVEN = 0x3802,
};

#endif /* D_SAVE_D_SAVE_H */
