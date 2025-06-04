#ifndef D_ITEM_DATA_H
#define D_ITEM_DATA_H

#include "global.h"

enum ItemTable {
    /* 0x00 */ dItem_HEART_e,
    /* 0x01 */ dItem_GREEN_RUPEE_e,
    /* 0x02 */ dItem_BLUE_RUPEE_e,
    /* 0x03 */ dItem_YELLOW_RUPEE_e,
    /* 0x04 */ dItem_RED_RUPEE_e,
    /* 0x05 */ dItem_PURPLE_RUPEE_e,
    /* 0x06 */ dItem_ORANGE_RUPEE_e,
    /* 0x07 */ dItem_HEART_PIECE_e,
    /* 0x08 */ dItem_HEART_CONTAINER_e,
    /* 0x09 */ dItem_SMALL_MAGIC_e,
    /* 0x0A */ dItem_LARGE_MAGIC_e,
    /* 0x0B */ dItem_BOMB_5_e,
    /* 0x0C */ dItem_BOMB_10_e,
    /* 0x0D */ dItem_BOMB_20_e,
    /* 0x0E */ dItem_BOMB_30_e,
    /* 0x0F */ dItem_SILVER_RUPEE_e,
    /* 0x10 */ dItem_ARROW_10_e,
    /* 0x11 */ dItem_ARROW_20_e,
    /* 0x12 */ dItem_ARROW_30_e,
    /* 0x13 */ noentry19, // Unused
    /* 0x14 */ noentry20, // Unused
    /* 0x15 */ dItem_SMALL_KEY_e,
    /* 0x16 */ dItem_RECOVER_FAIRY_e,
    /* 0x17 */ dItem_HEART_PIECE_2_e, // Not an item, used only for its msg no
    /* 0x18 */ dItem_HEART_PIECE_3_e, // Not an item, used only for its msg no
    /* 0x19 */ dItem_HEART_PIECE_4_e, // Not an item, used only for its msg no
    /* 0x1A */ dItem_SUB_DUN_RUPEE_e, // Used in VERSION_JPN only
    /* 0x1B */ noentry27, // Unused
    /* 0x1C */ noentry28, // Unused
    /* 0x1D */ noentry29, // Unused
    /* 0x1E */ dItem_TRIPLE_HEART_e,
    /* 0x1F */ dItem_JOY_PENDANT_e,
    /* 0x20 */ dItem_TELESCOPE_e,
    /* 0x21 */ dItem_TINGLE_TUNER_e,
    /* 0x22 */ dItem_WIND_WAKER_e,
    /* 0x23 */ CAMERA,
    /* 0x24 */ dItem_SPOILS_BAG_e,
    /* 0x25 */ dItem_GRAPPLING_HOOK_e,
    /* 0x26 */ CAMERA2,
    /* 0x27 */ dItem_BOW_e,
    /* 0x28 */ dItem_POWER_BRACELETS_e,
    /* 0x29 */ dItem_IRON_BOOTS_e,
    /* 0x2A */ dItem_MAGIC_ARMOR_e,
    /* 0x2B */ WATER_BOOTS, // Unused
    /* 0x2C */ dItem_BAIT_BAG_e,
    /* 0x2D */ dItem_BOOMERANG_e,
    /* 0x2E */ BARE_HAND, // Unused
    /* 0x2F */ dItem_HOOKSHOT_e,
    /* 0x30 */ dItem_DELIVERY_BAG_e,
    /* 0x31 */ dItem_BOMB_BAG_e,
    /* 0x32 */ dItem_FUKU_e,
    /* 0x33 */ dItem_SKULL_HAMMER_e,
    /* 0x34 */ dItem_DEKU_LEAF_e,
    /* 0x35 */ dItem_MAGIC_ARROW_e,
    /* 0x36 */ dItem_LIGHT_ARROW_e,
    /* 0x37 */ dItem_NEW_FUKU_e,
    /* 0x38 */ dItem_SWORD_e,
    /* 0x39 */ dItem_MASTER_SWORD_1_e,
    /* 0x3A */ dItem_MASTER_SWORD_2_e,
    /* 0x3B */ dItem_SHIELD_e,
    /* 0x3C */ dItem_MIRROR_SHIELD_e,
    /* 0x3D */ dItem_DROPPED_SWORD_e,
    /* 0x3E */ dItem_MASTER_SWORD_3_e,
    /* 0x3F */ KAKERA_HEART2,
    /* 0x40 */ noentry64, // Unused
    /* 0x41 */ noentry65, // Unused
    /* 0x42 */ dItem_PIRATES_CHARM_e,
    /* 0x43 */ dItem_HEROS_CHARM_e,
    /* 0x44 */ GRASS_BALL, // Unused
    /* 0x45 */ dItem_SKULL_NECKLACE_e,
    /* 0x46 */ dItem_BOKOBABA_SEED_e,
    /* 0x47 */ dItem_GOLDEN_FEATHER_e,
    /* 0x48 */ BOKO_BELT,
    /* 0x49 */ dItem_RED_JELLY_e,
    /* 0x4A */ dItem_GREEN_JELLY_e,
    /* 0x4B */ dItem_BLUE_JELLY_e,
    /* 0x4C */ dItem_MAP_e,
    /* 0x4D */ dItem_COMPASS_e,
    /* 0x4E */ dItem_BOSS_KEY_e,
    /* 0x4F */ EMPTY_BSHIP, // Unused
    /* 0x50 */ dItem_EMPTY_BOTTLE_e,
    /* 0x51 */ dItem_RED_POTION_e,
    /* 0x52 */ dItem_GREEN_POTION_e,
    /* 0x53 */ dItem_BLUE_POTION_e,
    /* 0x54 */ dItem_HALF_SOUP_BOTTLE_e,
    /* 0x55 */ dItem_SOUP_BOTTLE_e,
    /* 0x56 */ dItem_WATER_BOTTLE_e,
    /* 0x57 */ dItem_FAIRY_BOTTLE_e,
    /* 0x58 */ dItem_FIREFLY_BOTTLE_e,
    /* 0x59 */ dItem_FOREST_WATER_e,
    /* 0x5A */ UNK_BOTTLE_5A, // Unused
    /* 0x5B */ UNK_BOTTLE_5B, // Unused
    /* 0x5C */ UNK_BOTTLE_5C, // Unused
    /* 0x5D */ UNK_BOTTLE_5D, // Unused
    /* 0x5E */ UNK_BOTTLE_5E, // Unused
    /* 0x5F */ UNK_BOTTLE_5F, // Unused
    /* 0x60 */ UNK_BOTTLE_60, // Unused
    /* 0x61 */ dItem_TRIFORCE1_e,
    /* 0x62 */ dItem_TRIFORCE2_e,
    /* 0x63 */ dItem_TRIFORCE3_e,
    /* 0x64 */ dItem_TRIFORCE4_e,
    /* 0x65 */ dItem_TRIFORCE5_e,
    /* 0x66 */ dItem_TRIFORCE6_e,
    /* 0x67 */ dItem_TRIFORCE7_e,
    /* 0x68 */ dItem_TRIFORCE8_e,
    /* 0x69 */ dItem_PEARL_NAYRU_e,
    /* 0x6A */ dItem_PEARL_DIN_e,
    /* 0x6B */ dItem_PEARL_FARORE_e,
    /* 0x6C */ KNOWLEDGE_TF, // Unused
    /* 0x6D */ TACT_SONG1,
    /* 0x6E */ TACT_SONG2,
    /* 0x6F */ TACT_SONG3,
    /* 0x70 */ TACT_SONG4,
    /* 0x71 */ TACT_SONG5,
    /* 0x72 */ TACT_SONG6,
    /* 0x73 */ noentry115, // Unused
    /* 0x74 */ noentry116, // Unused
    /* 0x75 */ noentry117, // Unused
    /* 0x76 */ noentry118, // Unused
    /* 0x77 */ noentry119, // Unused
    /* 0x78 */ NORMAL_SAIL,
    /* 0x79 */ TRIFORCE_MAP1,
    /* 0x7A */ TRIFORCE_MAP2,
    /* 0x7B */ TRIFORCE_MAP3,
    /* 0x7C */ TRIFORCE_MAP4,
    /* 0x7D */ TRIFORCE_MAP5,
    /* 0x7E */ TRIFORCE_MAP6,
    /* 0x7F */ TRIFORCE_MAP7,
    /* 0x80 */ TRIFORCE_MAP8,
    /* 0x81 */ noentry129, // Unused
    /* 0x82 */ dItem_BIRD_BAIT_5_e,
    /* 0x83 */ dItem_HYOI_PEAR_e,
    /* 0x84 */ ESA1, // Unused
    /* 0x85 */ ESA2, // Unused
    /* 0x86 */ ESA3, // Unused
    /* 0x87 */ ESA4, // Unused
    /* 0x88 */ ESA5, // Unused
    /* 0x89 */ MAGIC_BEAN, // Unused
    /* 0x8A */ BIRD_ESA_10, // Unused
    /* 0x8B */ noentry139, // Unused
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
    /* 0x98 */ dItem_FATHER_LETTER_e,
    /* 0x99 */ dItem_NOTE_TO_MOM_e,
    /* 0x9A */ MAGYS_LETTER,
    /* 0x9B */ MO_LETTER,
    /* 0x9C */ COTTAGE_PAPER,
    /* 0x9D */ KAISEN_PRESENT1,
    /* 0x9E */ KAISEN_PRESENT2,
    /* 0x9F */ SALVAGE_ITEM1,
    /* 0xA0 */ SALVAGE_ITEM2, // Unused
    /* 0xA1 */ SALVAGE_ITEM3, // Unused
    /* 0xA2 */ XXX_039, // Unused
    /* 0xA3 */ TINGLE_STATUE1,
    /* 0xA4 */ TINGLE_STATUE2,
    /* 0xA5 */ TINGLE_STATUE3,
    /* 0xA6 */ TINGLE_STATUE4,
    /* 0xA7 */ TINGLE_STATUE5,
    /* 0xA8 */ TINGLE_STATUE6, // Unused
    /* 0xA9 */ noentry169, // Unused
    /* 0xAA */ dItem_HURRICANE_SPIN_e,
    /* 0xAB */ dItem_MAX_RUPEE_UP1_e,
    /* 0xAC */ dItem_MAX_RUPEE_UP2_e,
    /* 0xAD */ dItem_MAX_BOMB_UP1_e,
    /* 0xAE */ dItem_MAX_BOMB_UP2_e,
    /* 0xAF */ dItem_MAX_ARROW_UP1_e,
    /* 0xB0 */ dItem_MAX_ARROW_UP2_e,
    /* 0xB1 */ dItem_MAGIC_POWER_e,
    /* 0xB2 */ dItem_MAX_MP_UP1_e,
    /* 0xB3 */ TINCLE_RUPEE1,
    /* 0xB4 */ TINCLE_RUPEE2,
    /* 0xB5 */ TINCLE_RUPEE3,
    /* 0xB6 */ TINCLE_RUPEE4,
    /* 0xB7 */ TINCLE_RUPEE5,
    /* 0xB8 */ TINCLE_RUPEE6,
    /* 0xB9 */ LITHOGRAPH1, // Unused
    /* 0xBA */ LITHOGRAPH2, // Unused
    /* 0xBB */ LITHOGRAPH3, // Unused
    /* 0xBC */ LITHOGRAPH4, // Unused
    /* 0xBD */ LITHOGRAPH5, // Unused
    /* 0xBE */ LITHOGRAPH6, // Unused
    /* 0xBF */ dItem_COLLECT_MAP_64_e, // Unused
    /* 0xC0 */ dItem_COLLECT_MAP_63_e, // Unused
    /* 0xC1 */ dItem_COLLECT_MAP_62_e, // Unused
    /* 0xC2 */ dItem_COLLECT_MAP_61_e,
    /* 0xC3 */ dItem_COLLECT_MAP_60_e,
    /* 0xC4 */ dItem_COLLECT_MAP_59_e,
    /* 0xC5 */ dItem_COLLECT_MAP_58_e,
    /* 0xC6 */ dItem_COLLECT_MAP_57_e,
    /* 0xC7 */ dItem_COLLECT_MAP_56_e,
    /* 0xC8 */ dItem_COLLECT_MAP_55_e,
    /* 0xC9 */ dItem_COLLECT_MAP_54_e,
    /* 0xCA */ dItem_COLLECT_MAP_53_e,
    /* 0xCB */ dItem_COLLECT_MAP_52_e,
    /* 0xCC */ dItem_COLLECT_MAP_51_e,
    /* 0xCD */ dItem_COLLECT_MAP_50_e,
    /* 0xCE */ dItem_COLLECT_MAP_49_e,
    /* 0xCF */ dItem_COLLECT_MAP_48_e,
    /* 0xD0 */ dItem_COLLECT_MAP_47_e,
    /* 0xD1 */ dItem_COLLECT_MAP_46_e,
    /* 0xD2 */ dItem_COLLECT_MAP_45_e,
    /* 0xD3 */ dItem_COLLECT_MAP_44_e,
    /* 0xD4 */ dItem_COLLECT_MAP_43_e,
    /* 0xD5 */ dItem_COLLECT_MAP_42_e,
    /* 0xD6 */ dItem_COLLECT_MAP_41_e,
    /* 0xD7 */ dItem_COLLECT_MAP_40_e,
    /* 0xD8 */ dItem_COLLECT_MAP_39_e,
    /* 0xD9 */ dItem_COLLECT_MAP_38_e,
    /* 0xDA */ dItem_COLLECT_MAP_37_e,
    /* 0xDB */ dItem_COLLECT_MAP_36_e,
    /* 0xDC */ dItem_COLLECT_MAP_35_e,
    /* 0xDD */ dItem_COLLECT_MAP_34_e,
    /* 0xDE */ dItem_COLLECT_MAP_33_e,
    /* 0xDF */ dItem_COLLECT_MAP_32_e,
    /* 0xE0 */ dItem_COLLECT_MAP_31_e,
    /* 0xE1 */ dItem_COLLECT_MAP_30_e,
    /* 0xE2 */ dItem_COLLECT_MAP_29_e,
    /* 0xE3 */ dItem_COLLECT_MAP_28_e,
    /* 0xE4 */ dItem_COLLECT_MAP_27_e,
    /* 0xE5 */ dItem_COLLECT_MAP_26_e,
    /* 0xE6 */ dItem_COLLECT_MAP_25_e,
    /* 0xE7 */ dItem_COLLECT_MAP_24_e,
    /* 0xE8 */ dItem_COLLECT_MAP_23_e,
    /* 0xE9 */ dItem_COLLECT_MAP_22_e,
    /* 0xEA */ dItem_COLLECT_MAP_21_e,
    /* 0xEB */ dItem_COLLECT_MAP_20_e,
    /* 0xEC */ dItem_COLLECT_MAP_19_e,
    /* 0xED */ dItem_COLLECT_MAP_18_e,
    /* 0xEE */ dItem_COLLECT_MAP_17_e,
    /* 0xEF */ dItem_COLLECT_MAP_16_e,
    /* 0xF0 */ dItem_COLLECT_MAP_15_e,
    /* 0xF1 */ dItem_COLLECT_MAP_14_e,
    /* 0xF2 */ dItem_COLLECT_MAP_13_e,
    /* 0xF3 */ dItem_COLLECT_MAP_12_e,
    /* 0xF4 */ dItem_COLLECT_MAP_11_e,
    /* 0xF5 */ dItem_COLLECT_MAP_10_e,
    /* 0xF6 */ dItem_COLLECT_MAP_09_e,
    /* 0xF7 */ dItem_COLLECT_MAP_08_e,
    /* 0xF8 */ dItem_COLLECT_MAP_07_e,
    /* 0xF9 */ dItem_COLLECT_MAP_06_e,
    /* 0xFA */ dItem_COLLECT_MAP_05_e,
    /* 0xFB */ dItem_COLLECT_MAP_04_e,
    /* 0xFC */ dItem_COLLECT_MAP_03_e,
    /* 0xFD */ dItem_COLLECT_MAP_02_e,
    /* 0xFE */ dItem_COLLECT_MAP_01_e,
    /* 0xFF */ dItem_NONE_e,
};

#define MSG_NO_FOR_ITEM(item_no) item_no + 101

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
};  // Size: 0x24

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
};  // Size: 0x1C

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
    static const u8 getH(u8 no) { return item_info[no].mCollisionH; }
    static const u8 getR(u8 no) { return item_info[no].mCollisionR; }
    static bool chkFlag(u8 no, u32 mask) { return item_info[no].mFlag & mask; }
    
    static bool checkAppearEffect(u8 no);
    static u16 getAppearEffect(u8 no);
    static bool checkSpecialEffect(u8 no);
    static u16 getSpecialEffect(u8 no);
};

#endif /* D_ITEM_DATA_H */
