#ifndef D_ITEM_DATA_H
#define D_ITEM_DATA_H

#include "global.h"

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
    /* 0x3C */ MIRROR_SHIELD,
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

struct dItem_data_item_resource {
    /* 0x00 */ char* mArcname;
    /* 0x04 */ char* mTexture; // Filename in /files/res/Msg/itemicon.arc of its inventory icon.
    /* 0x08 */ s16 mBmdIdx;
    /* 0x0A */ s16 mSrtIdx; // BTK
    /* 0x0C */ s16 mSrtIdx2; // BTK
    /* 0x0E */ s16 mTevIdx; // BRK
    /* 0x10 */ s16 mTevIdx2; // BRK
    /* 0x12 */ s16 mBckIdx;
    /* 0x14 */ s8 mTevFrm; // If specified, keep the BRK animation on this frame.
    /* 0x16 */ s16 mItemMesgNum; // Message containing this item's name
    /* 0x18 */ u32 mUnused; // Always 0, doesn't seem to be read
    /* 0x1C */ u32 mUnknown; // Varies between items, but doesn't seem to be read. Resembles a differed dlist flag.
    /* 0x20 */ u16 mHeapSize;
};

STATIC_ASSERT(sizeof(dItem_data_item_resource) == 0x24);

struct dItem_data_field_item_res {
    /* 0x00 */ char* mArc;
    /* 0x04 */ s16 mBmdIdx;
    /* 0x06 */ s16 mSrtIdx; // BTK
    /* 0x08 */ s16 mSrtIdx2; // BTK
    /* 0x0A */ s16 mTevIdx; // BRK
    /* 0x0C */ s16 mTevIdx2; // BRK
    /* 0x0E */ s16 mBckIdx;
    /* 0x10 */ s8 mTevFrm; // Unused, the equivalent in item_resource is used instead.
    /* 0x14 */ u32 mUnknown;
    /* 0x18 */ u16 mHeapSize;
};

STATIC_ASSERT(sizeof(dItem_data_field_item_res) == 0x1C);

struct dItem_data_item_info {
    /* 0x00 */ u8 mShadowSize;
    /* 0x01 */ u8 mCollisionH; // Cylinder Height
    /* 0x02 */ u8 mCollisionR; // Cylinder Radius
    /* 0x03 */ u8 mFlag; // TODO enum
};

STATIC_ASSERT(sizeof(dItem_data_item_info) == 0x4);

struct dItem_data_effect_info {
    /* 0x00 */ u16 m_appear;
    /* 0x02 */ u16 m_sp_effect;
};

STATIC_ASSERT(sizeof(dItem_data_effect_info) == 0x4);

class dItem_data {
public:
    static char* item_arcname_tbl[0x70];
    static char* item_texture_tbl[0x74];
    static dItem_data_item_resource item_resource[0x100];
    static dItem_data_field_item_res field_item_res[0x100];
    static dItem_data_item_info item_info[0x100];
    static dItem_data_effect_info effect_info[0x81];
    
    static char* getArcname(u8 no) { return item_resource[no].mArcname; }
    static char* getTexture(u8 no) { return item_resource[no].mTexture; }
    static s16 getBmdIdx(u8 no) { return item_resource[no].mBmdIdx; }
    static s16 getSrtIdx(u8 no) { return item_resource[no].mSrtIdx; }
    static s16 getSrtIdx2(u8 no) { return item_resource[no].mSrtIdx2; }
    static s16 getTevIdx(u8 no) { return item_resource[no].mTevIdx; }
    static s16 getTevIdx2(u8 no) { return item_resource[no].mTevIdx2; }
    static s16 getBckIdx(u8 no) { return item_resource[no].mBckIdx; }
    // static s16 getBmtIdx(u8 no) { return item_resource[no].mBmtIdx; }
    static s8 getTevFrm(u8 no) { return item_resource[no].mTevFrm; }
    static s16 getItemMesgNum(u8 no) { return item_resource[no].mItemMesgNum; }
    static u32 getHeapSize(u8 no) { return item_resource[no].mHeapSize; }
    
    static char* getFieldArc(u8 no) { return field_item_res[no].mArc; }
    static s16 getFieldBmdIdx(u8 no) { return field_item_res[no].mBmdIdx; }
    static s16 getFieldSrtIdx(u8 no) { return field_item_res[no].mSrtIdx; }
    static s16 getFieldSrtIdx2(u8 no) { return field_item_res[no].mSrtIdx2; }
    static s16 getFieldTevIdx(u8 no) { return field_item_res[no].mTevIdx; }
    static s16 getFieldTevIdx2(u8 no) { return field_item_res[no].mTevIdx2; }
    static s16 getFieldBckIdx(u8 no) { return field_item_res[no].mBckIdx; }
    // static s16 getFieldBmtIdx(u8 no) { return field_item_res[no].mBmtIdx; }
    static u32 getFieldHeapSize(u8 no) { return field_item_res[no].mHeapSize; }
    
    static u8 getShadowSize(u8 no) { return item_info[no].mShadowSize; }
    static u8 getH(u8 no) { return item_info[no].mCollisionH; }
    static u8 getR(u8 no) { return item_info[no].mCollisionR; }
    static bool chkFlag(u8 no, u32 mask) { return item_info[no].mFlag & mask; }
    
    static bool checkAppearEffect(u8 no);
    static u16 getAppearEffect(u8 no);
    static bool checkSpecialEffect(u8 no);
    static u16 getSpecialEffect(u8 no);
};

#endif /* D_ITEM_DATA_H */