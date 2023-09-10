#ifndef D_SAVE_D_SAVE_H
#define D_SAVE_D_SAVE_H

#include "global.h"
#include "SSystem/SComponent/c_xyz.h"

enum ItemTable {
    /* 0x00 */ HEART,
    /* 0x01 */ GREEN_RUPEE,
    /* 0x02 */ BLUE_RUPEE,
    /* 0x03 */ YELLOW_RUPEE,
    /* 0x04 */ RED_RUPEE,
    /* 0x05 */ PURPLE_RUPEE,
    /* 0x06 */ ORANGE_RUPEE,
    /* 0x07 */ KAKERA_HEART,
    /* 0x08 */ UTUWA_HEART,
    /* 0x09 */ S_MAGIC,
    /* 0x0A */ L_MAGIC,
    /* 0x0B */ BOMB_5,
    /* 0x0C */ BOMB_10,
    /* 0x0D */ BOMB_20,
    /* 0x0E */ BOMB_30,
    /* 0x0F */ SILVER_RUPEE,
    /* 0x10 */ ARROW_10,
    /* 0x11 */ ARROW_20,
    /* 0x12 */ ARROW_30,
    /* 0x13 */ noentry19,
    /* 0x14 */ noentry20,
    /* 0x15 */ SMALL_KEY,
    /* 0x16 */ RECOVER_FAIRY,
    /* 0x17 */ noentry23,
    /* 0x18 */ noentry24,
    /* 0x19 */ noentry25,
    /* 0x1A */ SUB_DUN_RUPEE,
    /* 0x1B */ noentry27,
    /* 0x1C */ noentry28,
    /* 0x1D */ noentry29,
    /* 0x1E */ TRIPLE_HEART,
    /* 0x1F */ PENDANT,
    /* 0x20 */ TELESCOPE,
    /* 0x21 */ TNCL_WHITSL,
    /* 0x22 */ WIND_TACT,
    /* 0x23 */ CAMERA,
    /* 0x24 */ EMONO_BAG,
    /* 0x25 */ ROPE,
    /* 0x26 */ CAMERA2,
    /* 0x27 */ BOW,
    /* 0x28 */ PWR_GROOVE,
    /* 0x29 */ HVY_BOOTS,
    /* 0x2A */ DRGN_SHIELD,
    /* 0x2B */ WATER_BOOTS,
    /* 0x2C */ ESA_BAG,
    /* 0x2D */ BOOMERANG,
    /* 0x2E */ BARE_HAND,
    /* 0x2F */ HOOKSHOT,
    /* 0x30 */ WARASHIBE_BAG,
    /* 0x31 */ BOMB_BAG,
    /* 0x32 */ FUKU,
    /* 0x33 */ HUMMER,
    /* 0x34 */ DEKU_LEAF,
    /* 0x35 */ MAGIC_ARROW,
    /* 0x36 */ LIGHT_ARROW,
    /* 0x37 */ noentry55,
    /* 0x38 */ SWORD,
    /* 0x39 */ MASTER_SWORD,
    /* 0x3A */ LV3_SWORD,
    /* 0x3B */ SHIELD,
    /* 0x3C */ MIRROW_SHIELD,
    /* 0x3D */ DROPPED_SWORD,
    /* 0x3E */ MASTER_SWORD_EX,
    /* 0x3F */ KAKERA_HEART2,
    /* 0x40 */ noentry64,
    /* 0x41 */ noentry65,
    /* 0x42 */ PIRATES_OMAMORI,
    /* 0x43 */ HEROS_OMAMORI,
    /* 0x44 */ GRASS_BALL,
    /* 0x45 */ SKULL_NECKLACE,
    /* 0x46 */ BOKOBABA_SEED,
    /* 0x47 */ GOLDEN_FEATHER,
    /* 0x48 */ BOKO_BELT,
    /* 0x49 */ RED_JELLY,
    /* 0x4A */ GREEN_JELLY,
    /* 0x4B */ BLUE_JELLY,
    /* 0x4C */ MAP,
    /* 0x4D */ COMPASS,
    /* 0x4E */ BOSS_KEY,
    /* 0x4F */ EMPTY_BSHIP,
    /* 0x50 */ EMPTY_BOTTLE,
    /* 0x51 */ RED_BOTTLE,
    /* 0x52 */ GREEN_BOTTLE,
    /* 0x53 */ BLUE_BOTTLE,
    /* 0x54 */ BOTTLESHIP,
    /* 0x55 */ SOUP_BOTTLE,
    /* 0x56 */ BIN_IN_WATER,
    /* 0x57 */ FAIRY_BOTTLE,
    /* 0x58 */ FIREFLY_BOTTLE,
    /* 0x59 */ FWATER_BOTTLE,
    /* 0x5A */ UNK_BOTTLE_5A,
    /* 0x5B */ UNK_BOTTLE_5B,
    /* 0x5C */ UNK_BOTTLE_5C,
    /* 0x5D */ UNK_BOTTLE_5D,
    /* 0x5E */ UNK_BOTTLE_5E,
    /* 0x5F */ UNK_BOTTLE_5F,
    /* 0x60 */ UNK_BOTTLE_60,
    /* 0x61 */ TRIFORCE1,
    /* 0x62 */ TRIFORCE2,
    /* 0x63 */ TRIFORCE3,
    /* 0x64 */ TRIFORCE4,
    /* 0x65 */ TRIFORCE5,
    /* 0x66 */ TRIFORCE6,
    /* 0x67 */ TRIFORCE7,
    /* 0x68 */ TRIFORCE8,
    /* 0x69 */ PEARL1,
    /* 0x6A */ PEARL2,
    /* 0x6B */ PEARL3,
    /* 0x6C */ KNOWLEDGE_TF,
    /* 0x6D */ TACT_SONG1,
    /* 0x6E */ TACT_SONG2,
    /* 0x6F */ TACT_SONG3,
    /* 0x70 */ TACT_SONG4,
    /* 0x71 */ TACT_SONG5,
    /* 0x72 */ TACT_SONG6,
    /* 0x73 */ noentry115,
    /* 0x74 */ noentry116,
    /* 0x75 */ noentry117,
    /* 0x76 */ noentry118,
    /* 0x77 */ noentry119,
    /* 0x78 */ NORMAL_SAIL,
    /* 0x79 */ TRIFORCE_MAP1,
    /* 0x7A */ TRIFORCE_MAP2,
    /* 0x7B */ TRIFORCE_MAP3,
    /* 0x7C */ TRIFORCE_MAP4,
    /* 0x7D */ TRIFORCE_MAP5,
    /* 0x7E */ TRIFORCE_MAP6,
    /* 0x7F */ TRIFORCE_MAP7,
    /* 0x80 */ TRIFORCE_MAP8,
    /* 0x81 */ noentry129,
    /* 0x82 */ BIRD_ESA_5,
    /* 0x83 */ ANIMAL_ESA,
    /* 0x84 */ ESA1,
    /* 0x85 */ ESA2,
    /* 0x86 */ ESA3,
    /* 0x87 */ ESA4,
    /* 0x88 */ ESA5,
    /* 0x89 */ MAGIC_BEAN,
    /* 0x8A */ BIRD_ESA_10,
    /* 0x8B */ noentry139,
    /* 0x8C */ FLOWER_1,
    /* 0x8D */ FLOWER_2,
    /* 0x8E */ FLOWER_3,
    /* 0x8F */ HEROS_FLAG,
    /* 0x90 */ TAIRYO_FLAG,
    /* 0x91 */ SALES_FLAG,
    /* 0x92 */ WIND_FLAG,
    /* 0x93 */ RED_FLAG,
    /* 0x94 */ FOSSIL_HEAD,
    /* 0x95 */ WATER_STATUE,
    /* 0x96 */ POSTMAN_STATUE,
    /* 0x97 */ PRESIDENT_STATUE,
    /* 0x98 */ LETTER00,
    /* 0x99 */ MAGIC_SEED,
    /* 0x9A */ MAGYS_LETTER,
    /* 0x9B */ MO_LETTER,
    /* 0x9C */ COTTAGE_PAPER,
    /* 0x9D */ KAISEN_PRESENT1,
    /* 0x9E */ KAISEN_PRESENT2,
    /* 0x9F */ SALVAGE_ITEM1,
    /* 0xA0 */ SALVAGE_ITEM2,
    /* 0xA1 */ SALVAGE_ITEM3,
    /* 0xA2 */ XXX_039,
    /* 0xA3 */ TINGLE_STATUE1,
    /* 0xA4 */ TINGLE_STATUE2,
    /* 0xA5 */ TINGLE_STATUE3,
    /* 0xA6 */ TINGLE_STATUE4,
    /* 0xA7 */ TINGLE_STATUE5,
    /* 0xA8 */ TINGLE_STATUE6,
    /* 0xA9 */ noentry169,
    /* 0xAA */ noentry170,
    /* 0xAB */ MAX_RUPEE_UP1,
    /* 0xAC */ MAX_RUPEE_UP2,
    /* 0xAD */ MAX_BOMB_UP1,
    /* 0xAE */ MAX_BOMB_UP2,
    /* 0xAF */ MAX_ARROW_UP1,
    /* 0xB0 */ MAX_ARROW_UP2,
    /* 0xB1 */ MAGIC_POWER,
    /* 0xB2 */ MAX_MP_UP1,
    /* 0xB3 */ TINCLE_RUPEE1,
    /* 0xB4 */ TINCLE_RUPEE2,
    /* 0xB5 */ TINCLE_RUPEE3,
    /* 0xB6 */ TINCLE_RUPEE4,
    /* 0xB7 */ TINCLE_RUPEE5,
    /* 0xB8 */ TINCLE_RUPEE6,
    /* 0xB9 */ LITHOGRAPH1,
    /* 0xBA */ LITHOGRAPH2,
    /* 0xBB */ LITHOGRAPH3,
    /* 0xBC */ LITHOGRAPH4,
    /* 0xBD */ LITHOGRAPH5,
    /* 0xBE */ LITHOGRAPH6,
    /* 0xBF */ COLLECT_MAP_64,
    /* 0xC0 */ COLLECT_MAP_63,
    /* 0xC1 */ COLLECT_MAP_62,
    /* 0xC2 */ COLLECT_MAP_61,
    /* 0xC3 */ COLLECT_MAP_60,
    /* 0xC4 */ COLLECT_MAP_59,
    /* 0xC5 */ COLLECT_MAP_58,
    /* 0xC6 */ COLLECT_MAP_57,
    /* 0xC7 */ COLLECT_MAP_56,
    /* 0xC8 */ COLLECT_MAP_55,
    /* 0xC9 */ COLLECT_MAP_54,
    /* 0xCA */ COLLECT_MAP_53,
    /* 0xCB */ COLLECT_MAP_52,
    /* 0xCC */ COLLECT_MAP_51,
    /* 0xCD */ COLLECT_MAP_50,
    /* 0xCE */ COLLECT_MAP_49,
    /* 0xCF */ COLLECT_MAP_48,
    /* 0xD0 */ COLLECT_MAP_47,
    /* 0xD1 */ COLLECT_MAP_46,
    /* 0xD2 */ COLLECT_MAP_45,
    /* 0xD3 */ COLLECT_MAP_44,
    /* 0xD4 */ COLLECT_MAP_43,
    /* 0xD5 */ COLLECT_MAP_42,
    /* 0xD6 */ COLLECT_MAP_41,
    /* 0xD7 */ COLLECT_MAP_40,
    /* 0xD8 */ COLLECT_MAP_39,
    /* 0xD9 */ COLLECT_MAP_38,
    /* 0xDA */ COLLECT_MAP_37,
    /* 0xDB */ COLLECT_MAP_36,
    /* 0xDC */ COLLECT_MAP_35,
    /* 0xDD */ COLLECT_MAP_34,
    /* 0xDE */ COLLECT_MAP_33,
    /* 0xDF */ COLLECT_MAP_32,
    /* 0xE0 */ COLLECT_MAP_31,
    /* 0xE1 */ COLLECT_MAP_30,
    /* 0xE2 */ COLLECT_MAP_29,
    /* 0xE3 */ COLLECT_MAP_28,
    /* 0xE4 */ COLLECT_MAP_27,
    /* 0xE5 */ COLLECT_MAP_26,
    /* 0xE6 */ COLLECT_MAP_25,
    /* 0xE7 */ COLLECT_MAP_24,
    /* 0xE8 */ COLLECT_MAP_23,
    /* 0xE9 */ COLLECT_MAP_22,
    /* 0xEA */ COLLECT_MAP_21,
    /* 0xEB */ COLLECT_MAP_20,
    /* 0xEC */ COLLECT_MAP_19,
    /* 0xED */ COLLECT_MAP_18,
    /* 0xEE */ COLLECT_MAP_17,
    /* 0xEF */ COLLECT_MAP_16,
    /* 0xF0 */ COLLECT_MAP_15,
    /* 0xF1 */ COLLECT_MAP_14,
    /* 0xF2 */ COLLECT_MAP_13,
    /* 0xF3 */ COLLECT_MAP_12,
    /* 0xF4 */ COLLECT_MAP_11,
    /* 0xF5 */ COLLECT_MAP_10,
    /* 0xF6 */ COLLECT_MAP_09,
    /* 0xF7 */ COLLECT_MAP_08,
    /* 0xF8 */ COLLECT_MAP_07,
    /* 0xF9 */ COLLECT_MAP_06,
    /* 0xFA */ COLLECT_MAP_05,
    /* 0xFB */ COLLECT_MAP_04,
    /* 0xFC */ COLLECT_MAP_03,
    /* 0xFD */ COLLECT_MAP_02,
    /* 0xFE */ COLLECT_MAP_01,
    /* 0xFF */ NO_ITEM,
};

class dSv_player_status_a_c {
public:
    /* 800589A8 */ void init();

    u8 getSelectItemIndex(int i_no) const { return mSelectItem[i_no]; }
    u8 getSelectEquip(int i_no) const { return mSelectEquip[i_no]; }

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
    /* 80058B54 */ void init();

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
    /* 80058B84 */ void init();
    /* 80058BC8 */ void set(char const*, s8, u8);

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
    /* 8005955C */ bool isItem(int, u8);
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
    /* 8005A854 */ u8 checkReserveItemEmpty();
    /* 8005A878 */ u8 checkReserveItem(u8);

    /* 0x00 */ u8 field_0x0[8];
    /* 0x08 */ u8 field_0x8[8];
    /* 0x10 */ u8 field_0x10[8];
};  // Size: 0x18

STATIC_ASSERT(sizeof(dSv_player_bag_item_c) == 0x18);

class dSv_player_get_bag_item_c {
public:
    /* 8005A8B8 */ void init();
    /* 8005A8CC */ void onBeast(u8);
    /* 8005A960 */ bool isBeast(u8);
    /* 8005A9F8 */ void onBait(u8);
    /* 8005AA8C */ bool isBait(u8);
    /* 8005AB24 */ void onReserve(u8);
    /* 8005ABB4 */ bool isReserve(u8);

    /* 0x0 */ u32 mReserveFlags;
    /* 0x4 */ u8 mBeastFlags;
    /* 0x5 */ u8 mBaitFlags;
    /* 0x6 */ u8 unk_0x6[0xC - 0x6];
};  // Size: 0xC

STATIC_ASSERT(sizeof(dSv_player_get_bag_item_c) == 0xC);

class dSv_player_bag_item_record_c {
public:
    /* 8005AC48 */ void init();

    /* 0x00 */ u8 field_0x0[8];
    /* 0x08 */ u8 field_0x8[8];
    /* 0x10 */ u8 field_0x10[8];
};  // Size: 0x18

STATIC_ASSERT(sizeof(dSv_player_bag_item_record_c) == 0x18);

class dSv_player_collect_c {
public:
    /* 8005ACA8 */ void init();
    /* 8005ACE0 */ void onCollect(int, u8);
    /* 8005AD78 */ void offCollect(int, u8);
    /* 8005AE10 */ bool isCollect(int, u8);
    /* 8005AEAC */ void onTact(u8);
    /* 8005AF40 */ bool isTact(u8);
    /* 8005AFD8 */ void onTriforce(u8);
    /* 8005B06C */ BOOL isTriforce(u8);
    /* 8005B104 */ void onSymbol(u8);
    /* 8005B198 */ bool isSymbol(u8);
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
    /* 8005BFA4 */ void checkVibration();

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

    /* 0x00 */ u32 mTbox;
    /* 0x04 */ u32 mSwitch[4];
    /* 0x14 */ u32 mItem[1];
    /* 0x18 */ u32 mVisitedRoom[2];
    /* 0x20 */ u8 field_0x20;
    /* 0x21 */ u8 mDungeonItem;
};  // Size: 0x24

class dSv_ocean_c {
public:
    /* 8005C8E8 */ void init();
    /* 8005C908 */ void onOceanSvBit(u8, u16);
    /* 8005C9E8 */ BOOL isOceanSvBit(u8, u16);

    /* 0x0 */ u16 field_0x0[50];
};

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

class dSv_reserve_c {
public:
    /* 8005CB94 */ void init();

    /* 0x0 */ u8 mReserve[0x50];
};  // Size: 0x50

class dSv_memory_c {
public:
    /* 8005CBB0 */ void init();

    dSv_memBit_c& getBit() { return mMembit; }
    const dSv_memBit_c& getBit() const { return mMembit; }

    /* 0x0 */ dSv_memBit_c mMembit;
};  // Size: 0x24

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
    /* 8005D468 */ void init(int);

    dSv_zoneBit_c& getZoneBit() { return mZoneBit; }
    const dSv_zoneBit_c& getBit() const { return mZoneBit; }
    dSv_zoneActor_c& getActor() { return mZoneActor; }
    const dSv_zoneActor_c& getActor() const { return mZoneActor; }

    /* 0x00 */ s8 mRoomNo;
    /* 0x02 */ dSv_zoneBit_c mZoneBit;
    /* 0x0C */ dSv_zoneActor_c mZoneActor;
};  // Size: 0x4C

class dSv_restart_c {
public:
    /* 8005D4A4 */ void setRoom(cXyz const&, s16, s8);
    /* 8005D4C8 */ void setRestartOption(s8);
    /* 8005D584 */ void setRestartOption(s8, cXyz*, s16, s8);

    /* 0x00 */ s8 mRestartRoom;
    /* 0x01 */ u8 field_0x1;
    /* 0x02 */ s8 mRoomNo;
    /* 0x04 */ s16 field_0x4;
    /* 0x06 */ s16 mRoomAngleY;
    /* 0x08 */ cXyz mRoomPos;
    /* 0x14 */ u16 mStartCode;
    /* 0x16 */ s16 mRestartAngle;
    /* 0x18 */ cXyz mRestartPos;
    /* 0x24 */ u32 mRestartParam;
};  // Size: 0x28

class dSv_turnRestart_c {
public:
    /* 8005D5B4 */ void set(cXyz const&, s16, s8, u32, cXyz const&, s16, int);

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

    dSv_memory_c& getSave(int i_stageNo) { return mMemory[i_stageNo]; }
    void putSave(int i_stageNo, dSv_memory_c i_mem) { mMemory[i_stageNo] = i_mem; }

    const static int STAGE_MAX = 16;

    /* 0x000 */ dSv_player_c mPlayer;
    /* 0x380 */ dSv_memory_c mMemory[STAGE_MAX];
    /* 0x5C0 */ dSv_ocean_c mOcean;
    /* 0x624 */ dSv_event_c mEvent;
};  // Size: 0x724

class dSv_info_c {
public:
    /* 8005D604 */ void init();
    /* 8005D660 */ void reinit();
    /* 8005D8C8 */ void getSave(int);
    /* 8005D988 */ void putSave(int);
    /* 8005DA70 */ void initZone();
    /* 8005DAC8 */ int createZone(int);
    /* 8005DB24 */ void onSwitch(int, int);
    /* 8005DCEC */ void offSwitch(int, int);
    /* 8005DE98 */ BOOL isSwitch(int, int);
    /* 8005DFE0 */ BOOL revSwitch(int, int);
    /* 8005E190 */ void onItem(int, int);
    /* 8005E324 */ BOOL isItem(int, int);
    /* 8005E4BC */ void onActor(int, int);
    /* 8005E5F0 */ BOOL isActor(int, int);
    /* 8005E780 */ void memory_to_card(char*, int);
    /* 8005EA24 */ void card_to_memory(char*, int);
    /* 8005ED00 */ int initdata_to_card(char*, int);

    dSv_player_c& getPlayer() { return mSavedata.getPlayer(); }

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
    /* 0x1150 */ f32 field_0x1150;
    /* 0x1154 */ int field_0x1154;
    /* 0x1158 */ dSv_event_c mTmp;
    /* 0x1258 */ dSv_turnRestart_c mTurnRestart;
    /* 0x1290 */ u8 field_0x1290;
    /* 0x1291 */ u8 field_0x1291;
    /* 0x1292 */ u8 field_0x1292;
    /* 0x1298 */ s64 field_0x1298;
};  // Size: 0x12A0

STATIC_ASSERT(sizeof(dSv_info_c) == 0x12A0);

#endif /* D_SAVE_D_SAVE_H */
