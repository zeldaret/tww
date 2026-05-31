#ifndef D_ITEM_DATA_H
#define D_ITEM_DATA_H

#include "global.h"

enum ItemTable {
    /* 0x00 */ dItemNo_HEART_e,
    /* 0x01 */ dItemNo_GREEN_RUPEE_e,
    /* 0x02 */ dItemNo_BLUE_RUPEE_e,
    /* 0x03 */ dItemNo_YELLOW_RUPEE_e,
    /* 0x04 */ dItemNo_RED_RUPEE_e,
    /* 0x05 */ dItemNo_PURPLE_RUPEE_e,
    /* 0x06 */ dItemNo_ORANGE_RUPEE_e,
    /* 0x07 */ dItemNo_HEART_PIECE_e,
    /* 0x08 */ dItemNo_HEART_CONTAINER_e,
    /* 0x09 */ dItemNo_SMALL_MAGIC_e,
    /* 0x0A */ dItemNo_LARGE_MAGIC_e,
    /* 0x0B */ dItemNo_BOMB_5_e,
    /* 0x0C */ dItemNo_BOMB_10_e,
    /* 0x0D */ dItemNo_BOMB_20_e,
    /* 0x0E */ dItemNo_BOMB_30_e,
    /* 0x0F */ dItemNo_SILVER_RUPEE_e,
    /* 0x10 */ dItemNo_ARROW_10_e,
    /* 0x11 */ dItemNo_ARROW_20_e,
    /* 0x12 */ dItemNo_ARROW_30_e,
    /* 0x13 */ dItemNo_NOENTRY_19_e, // Unused
    /* 0x14 */ dItemNo_NOENTRY_20_e, // Unused
    /* 0x15 */ dItemNo_SMALL_KEY_e,
    /* 0x16 */ dItemNo_RECOVER_FAIRY_e,
    /* 0x17 */ dItemNo_HEART_PIECE_2_e, // Not an item, used only for its msg no
    /* 0x18 */ dItemNo_HEART_PIECE_3_e, // Not an item, used only for its msg no
    /* 0x19 */ dItemNo_HEART_PIECE_4_e, // Not an item, used only for its msg no
    /* 0x1A */ dItemNo_SUB_DUN_RUPEE_e, // Used in VERSION_JPN only
    /* 0x1B */ dItemNo_NOENTRY_27_e, // Unused
    /* 0x1C */ dItemNo_NOENTRY_28_e, // Unused
    /* 0x1D */ dItemNo_NOENTRY_29_e, // Unused
    /* 0x1E */ dItemNo_TRIPLE_HEART_e,
    /* 0x1F */ dItemNo_JOY_PENDANT_e,
    /* 0x20 */ dItemNo_TELESCOPE_e,
    /* 0x21 */ dItemNo_TINGLE_TUNER_e,
    /* 0x22 */ dItemNo_WIND_WAKER_e,
    /* 0x23 */ dItemNo_PICTO_BOX_e,
    /* 0x24 */ dItemNo_SPOILS_BAG_e,
    /* 0x25 */ dItemNo_GRAPPLING_HOOK_e,
    /* 0x26 */ dItemNo_DELUXE_PICTO_BOX_e,
    /* 0x27 */ dItemNo_BOW_e,
    /* 0x28 */ dItemNo_POWER_BRACELETS_e,
    /* 0x29 */ dItemNo_IRON_BOOTS_e,
    /* 0x2A */ dItemNo_MAGIC_ARMOR_e,
    /* 0x2B */ dItemNo_WATER_BOOTS_e, // Unused
    /* 0x2C */ dItemNo_BAIT_BAG_e,
    /* 0x2D */ dItemNo_BOOMERANG_e,
    /* 0x2E */ dItemNo_BARE_HAND_e, // Unused
    /* 0x2F */ dItemNo_HOOKSHOT_e,
    /* 0x30 */ dItemNo_DELIVERY_BAG_e,
    /* 0x31 */ dItemNo_BOMB_BAG_e,
    /* 0x32 */ dItemNo_FUKU_e,
    /* 0x33 */ dItemNo_SKULL_HAMMER_e,
    /* 0x34 */ dItemNo_DEKU_LEAF_e,
    /* 0x35 */ dItemNo_MAGIC_ARROW_e,
    /* 0x36 */ dItemNo_LIGHT_ARROW_e,
    /* 0x37 */ dItemNo_NEW_FUKU_e,
    /* 0x38 */ dItemNo_SWORD_e,
    /* 0x39 */ dItemNo_MASTER_SWORD_1_e,
    /* 0x3A */ dItemNo_MASTER_SWORD_2_e,
    /* 0x3B */ dItemNo_SHIELD_e,
    /* 0x3C */ dItemNo_MIRROR_SHIELD_e,
    /* 0x3D */ dItemNo_DROPPED_SWORD_e,
    /* 0x3E */ dItemNo_MASTER_SWORD_3_e,
    /* 0x3F */ dItemNo_HEART_PIECE_ALT_e,
    /* 0x40 */ dItemNo_NOENTRY_64_e, // Unused
    /* 0x41 */ dItemNo_NOENTRY_65_e, // Unused
    /* 0x42 */ dItemNo_PIRATES_CHARM_e,
    /* 0x43 */ dItemNo_HEROS_CHARM_e,
    /* 0x44 */ dItemNo_GRASS_BALL_e, // Unused
    /* 0x45 */ dItemNo_SKULL_NECKLACE_e,
    /* 0x46 */ dItemNo_BOKOBABA_SEED_e,
    /* 0x47 */ dItemNo_GOLDEN_FEATHER_e,
    /* 0x48 */ dItemNo_KNIGHTS_CREST_e,
    /* 0x49 */ dItemNo_RED_JELLY_e,
    /* 0x4A */ dItemNo_GREEN_JELLY_e,
    /* 0x4B */ dItemNo_BLUE_JELLY_e,
    /* 0x4C */ dItemNo_MAP_e,
    /* 0x4D */ dItemNo_COMPASS_e,
    /* 0x4E */ dItemNo_BOSS_KEY_e,
    /* 0x4F */ dItemNo_EMPTY_BSHIP_e, // Unused
    /* 0x50 */ dItemNo_EMPTY_BOTTLE_e,
    /* 0x51 */ dItemNo_RED_POTION_e,
    /* 0x52 */ dItemNo_GREEN_POTION_e,
    /* 0x53 */ dItemNo_BLUE_POTION_e,
    /* 0x54 */ dItemNo_HALF_SOUP_BOTTLE_e,
    /* 0x55 */ dItemNo_SOUP_BOTTLE_e,
    /* 0x56 */ dItemNo_WATER_BOTTLE_e,
    /* 0x57 */ dItemNo_FAIRY_BOTTLE_e,
    /* 0x58 */ dItemNo_FIREFLY_BOTTLE_e,
    /* 0x59 */ dItemNo_FOREST_WATER_e,
    /* 0x5A */ dItemNo_UNK_BOTTLE_5A_e, // Unused
    /* 0x5B */ dItemNo_UNK_BOTTLE_5B_e, // Unused
    /* 0x5C */ dItemNo_UNK_BOTTLE_5C_e, // Unused
    /* 0x5D */ dItemNo_UNK_BOTTLE_5D_e, // Unused
    /* 0x5E */ dItemNo_UNK_BOTTLE_5E_e, // Unused
    /* 0x5F */ dItemNo_UNK_BOTTLE_5F_e, // Unused
    /* 0x60 */ dItemNo_UNK_BOTTLE_60_e, // Unused
    /* 0x61 */ dItemNo_TRIFORCE1_e,
    /* 0x62 */ dItemNo_TRIFORCE2_e,
    /* 0x63 */ dItemNo_TRIFORCE3_e,
    /* 0x64 */ dItemNo_TRIFORCE4_e,
    /* 0x65 */ dItemNo_TRIFORCE5_e,
    /* 0x66 */ dItemNo_TRIFORCE6_e,
    /* 0x67 */ dItemNo_TRIFORCE7_e,
    /* 0x68 */ dItemNo_TRIFORCE8_e,
    /* 0x69 */ dItemNo_PEARL_NAYRU_e,
    /* 0x6A */ dItemNo_PEARL_DIN_e,
    /* 0x6B */ dItemNo_PEARL_FARORE_e,
    /* 0x6C */ dItemNo_KNOWLEDGE_TF_e, // Unused
    /* 0x6D */ dItemNo_WINDS_REQUIEM_e,
    /* 0x6E */ dItemNo_BALLAD_OF_GALES_e,
    /* 0x6F */ dItemNo_COMMAND_MELODY_e,
    /* 0x70 */ dItemNo_EARTH_GODS_LYRIC_e,
    /* 0x71 */ dItemNo_WIND_GODS_ARIA_e,
    /* 0x72 */ dItemNo_SONG_OF_PASSING_e,
    /* 0x73 */ dItemNo_NOENTRY_115_e, // Unused
    /* 0x74 */ dItemNo_NOENTRY_116_e, // Unused
    /* 0x75 */ dItemNo_NOENTRY_117_e, // Unused
    /* 0x76 */ dItemNo_NOENTRY_118_e, // Unused
    /* 0x77 */ dItemNo_NOENTRY_119_e, // Unused
    /* 0x78 */ dItemNo_SAIL_e,
    /* 0x79 */ dItemNo_TRIFORCE_MAP_1_e,
    /* 0x7A */ dItemNo_TRIFORCE_MAP_2_e,
    /* 0x7B */ dItemNo_TRIFORCE_MAP_3_e,
    /* 0x7C */ dItemNo_TRIFORCE_MAP_4_e,
    /* 0x7D */ dItemNo_TRIFORCE_MAP_5_e,
    /* 0x7E */ dItemNo_TRIFORCE_MAP_6_e,
    /* 0x7F */ dItemNo_TRIFORCE_MAP_7_e,
    /* 0x80 */ dItemNo_TRIFORCE_MAP_8_e,
    /* 0x81 */ dItemNo_NOENTRY_129_e, // Unused
    /* 0x82 */ dItemNo_BIRD_BAIT_5_e,
    /* 0x83 */ dItemNo_HYOI_PEAR_e,
    /* 0x84 */ dItemNo_ESA_1_e, // Unused
    /* 0x85 */ dItemNo_ESA_2_e, // Unused
    /* 0x86 */ dItemNo_ESA_3_e, // Unused
    /* 0x87 */ dItemNo_ESA_4_e, // Unused
    /* 0x88 */ dItemNo_ESA_5_e, // Unused
    /* 0x89 */ dItemNo_MAGIC_BEAN_e, // Unused
    /* 0x8A */ dItemNo_BIRD_ESA_10_e, // Unused
    /* 0x8B */ dItemNo_NOENTRY_139_e, // Unused
    /* 0x8C */ dItemNo_TOWN_FLOWER_e,
    /* 0x8D */ dItemNo_SEA_FLOWER_e,
    /* 0x8E */ dItemNo_EXOTIC_FLOWER_e,
    /* 0x8F */ dItemNo_HEROS_FLAG_e,
    /* 0x90 */ dItemNo_BIG_CATCH_FLAG_e,
    /* 0x91 */ dItemNo_BIG_SALE_FLAG_e,
    /* 0x92 */ dItemNo_PINWHEEL_e,
    /* 0x93 */ dItemNo_SICKLE_MOON_FLAG_e,
    /* 0x94 */ dItemNo_SKULL_TOWER_IDOL_e,
    /* 0x95 */ dItemNo_FOUNTAIN_IDOL_e,
    /* 0x96 */ dItemNo_POSTMAN_STATUE_e,
    /* 0x97 */ dItemNo_SHOP_GURU_STATUE_e,
    /* 0x98 */ dItemNo_FATHER_LETTER_e,
    /* 0x99 */ dItemNo_NOTE_TO_MOM_e,
    /* 0x9A */ dItemNo_MAGGIES_LETTER_e,
    /* 0x9B */ dItemNo_MOBLINS_LETTER_e,
    /* 0x9C */ dItemNo_CABANA_DEED_e,
    /* 0x9D */ dItemNo_COMPLIMENTARY_ID_e,
    /* 0x9E */ dItemNo_FILL_UP_COUPON_e,
    /* 0x9F */ dItemNo_LEGENDARY_PICTOGRAPH_e, // Originally "salvage item 1", but was repurposed
    /* 0xA0 */ dItemNo_SALVAGE_ITEM_2_e, // Unused
    /* 0xA1 */ dItemNo_SALVAGE_ITEM_3_e, // Unused
    /* 0xA2 */ dItemNo_XXX_039_e, // Unused
    /* 0xA3 */ dItemNo_TINGLE_STATUE_1_e,
    /* 0xA4 */ dItemNo_TINGLE_STATUE_2_e,
    /* 0xA5 */ dItemNo_TINGLE_STATUE_3_e,
    /* 0xA6 */ dItemNo_TINGLE_STATUE_4_e,
    /* 0xA7 */ dItemNo_TINGLE_STATUE_5_e,
    /* 0xA8 */ dItemNo_TINGLE_STATUE_6_e, // Unused
    /* 0xA9 */ dItemNo_NOENTRY_169_e, // Unused
    /* 0xAA */ dItemNo_HURRICANE_SPIN_e,
    /* 0xAB */ dItemNo_MAX_RUPEE_UP1_e,
    /* 0xAC */ dItemNo_MAX_RUPEE_UP2_e,
    /* 0xAD */ dItemNo_MAX_BOMB_UP1_e,
    /* 0xAE */ dItemNo_MAX_BOMB_UP2_e,
    /* 0xAF */ dItemNo_MAX_ARROW_UP1_e,
    /* 0xB0 */ dItemNo_MAX_ARROW_UP2_e,
    /* 0xB1 */ dItemNo_MAGIC_POWER_e,
    /* 0xB2 */ dItemNo_MAX_MP_UP1_e,
    /* 0xB3 */ dItemNo_TINGLE_RUPEE_1_e,
    /* 0xB4 */ dItemNo_TINGLE_RUPEE_2_e,
    /* 0xB5 */ dItemNo_TINGLE_RUPEE_3_e,
    /* 0xB6 */ dItemNo_TINGLE_RUPEE_4_e,
    /* 0xB7 */ dItemNo_TINGLE_RUPEE_5_e,
    /* 0xB8 */ dItemNo_TINGLE_RUPEE_6_e,
    /* 0xB9 */ dItemNo_LITHOGRAPH_1_e, // Unused
    /* 0xBA */ dItemNo_LITHOGRAPH_2_e, // Unused
    /* 0xBB */ dItemNo_LITHOGRAPH_3_e, // Unused
    /* 0xBC */ dItemNo_LITHOGRAPH_4_e, // Unused
    /* 0xBD */ dItemNo_LITHOGRAPH_5_e, // Unused
    /* 0xBE */ dItemNo_LITHOGRAPH_6_e, // Unused
    /* 0xBF */ dItemNo_COLLECT_MAP_64_e, // Unused
    /* 0xC0 */ dItemNo_COLLECT_MAP_63_e, // Unused
    /* 0xC1 */ dItemNo_COLLECT_MAP_62_e, // Unused
    /* 0xC2 */ dItemNo_COLLECT_MAP_61_e,
    /* 0xC3 */ dItemNo_COLLECT_MAP_60_e,
    /* 0xC4 */ dItemNo_COLLECT_MAP_59_e,
    /* 0xC5 */ dItemNo_COLLECT_MAP_58_e,
    /* 0xC6 */ dItemNo_COLLECT_MAP_57_e,
    /* 0xC7 */ dItemNo_COLLECT_MAP_56_e,
    /* 0xC8 */ dItemNo_COLLECT_MAP_55_e,
    /* 0xC9 */ dItemNo_COLLECT_MAP_54_e,
    /* 0xCA */ dItemNo_COLLECT_MAP_53_e,
    /* 0xCB */ dItemNo_COLLECT_MAP_52_e,
    /* 0xCC */ dItemNo_COLLECT_MAP_51_e,
    /* 0xCD */ dItemNo_COLLECT_MAP_50_e,
    /* 0xCE */ dItemNo_COLLECT_MAP_49_e,
    /* 0xCF */ dItemNo_COLLECT_MAP_48_e,
    /* 0xD0 */ dItemNo_COLLECT_MAP_47_e,
    /* 0xD1 */ dItemNo_COLLECT_MAP_46_e,
    /* 0xD2 */ dItemNo_COLLECT_MAP_45_e,
    /* 0xD3 */ dItemNo_COLLECT_MAP_44_e,
    /* 0xD4 */ dItemNo_COLLECT_MAP_43_e,
    /* 0xD5 */ dItemNo_COLLECT_MAP_42_e,
    /* 0xD6 */ dItemNo_COLLECT_MAP_41_e,
    /* 0xD7 */ dItemNo_COLLECT_MAP_40_e,
    /* 0xD8 */ dItemNo_COLLECT_MAP_39_e,
    /* 0xD9 */ dItemNo_COLLECT_MAP_38_e,
    /* 0xDA */ dItemNo_COLLECT_MAP_37_e,
    /* 0xDB */ dItemNo_COLLECT_MAP_36_e,
    /* 0xDC */ dItemNo_COLLECT_MAP_35_e,
    /* 0xDD */ dItemNo_COLLECT_MAP_34_e,
    /* 0xDE */ dItemNo_COLLECT_MAP_33_e,
    /* 0xDF */ dItemNo_COLLECT_MAP_32_e,
    /* 0xE0 */ dItemNo_COLLECT_MAP_31_e,
    /* 0xE1 */ dItemNo_COLLECT_MAP_30_e,
    /* 0xE2 */ dItemNo_COLLECT_MAP_29_e,
    /* 0xE3 */ dItemNo_COLLECT_MAP_28_e,
    /* 0xE4 */ dItemNo_COLLECT_MAP_27_e,
    /* 0xE5 */ dItemNo_COLLECT_MAP_26_e,
    /* 0xE6 */ dItemNo_COLLECT_MAP_25_e,
    /* 0xE7 */ dItemNo_COLLECT_MAP_24_e,
    /* 0xE8 */ dItemNo_COLLECT_MAP_23_e,
    /* 0xE9 */ dItemNo_COLLECT_MAP_22_e,
    /* 0xEA */ dItemNo_COLLECT_MAP_21_e,
    /* 0xEB */ dItemNo_COLLECT_MAP_20_e,
    /* 0xEC */ dItemNo_COLLECT_MAP_19_e,
    /* 0xED */ dItemNo_COLLECT_MAP_18_e,
    /* 0xEE */ dItemNo_COLLECT_MAP_17_e,
    /* 0xEF */ dItemNo_COLLECT_MAP_16_e,
    /* 0xF0 */ dItemNo_COLLECT_MAP_15_e,
    /* 0xF1 */ dItemNo_COLLECT_MAP_14_e,
    /* 0xF2 */ dItemNo_COLLECT_MAP_13_e,
    /* 0xF3 */ dItemNo_COLLECT_MAP_12_e,
    /* 0xF4 */ dItemNo_COLLECT_MAP_11_e,
    /* 0xF5 */ dItemNo_COLLECT_MAP_10_e,
    /* 0xF6 */ dItemNo_COLLECT_MAP_09_e,
    /* 0xF7 */ dItemNo_COLLECT_MAP_08_e,
    /* 0xF8 */ dItemNo_COLLECT_MAP_07_e,
    /* 0xF9 */ dItemNo_COLLECT_MAP_06_e,
    /* 0xFA */ dItemNo_COLLECT_MAP_05_e,
    /* 0xFB */ dItemNo_COLLECT_MAP_04_e,
    /* 0xFC */ dItemNo_COLLECT_MAP_03_e,
    /* 0xFD */ dItemNo_COLLECT_MAP_02_e,
    /* 0xFE */ dItemNo_COLLECT_MAP_01_e,
    /* 0xFF */ dItemNo_NONE_e,
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
