#ifndef JAZELAUDIO_BGM_H
#define JAZELAUDIO_BGM_H

enum {
    // These are official BGM sequence enum names extracted from WWHD.
    JA_BGM_SE_SEQUENCE = 0x80000800,
    JA_BGM_ISLAND_LINK = 0x80000001,
    JA_BGM_ITEM_GET = 0x80000002,
    JA_BGM_GOMA = 0x80000003,
    JA_BGM_BATTLE_NORM = 0x80000004,
    JA_BGM_KINDAN_BOSS = 0x80000005,
    JA_BGM_D_RYU_MT = 0x80000006,
    JA_BGM_I_MAJU = 0x80000007,
    JA_BGM_HOUSE = 0x80000008,
    JA_BGM_OPEN_BOX = 0x80000009,
    JA_BGM_DIE_LINK = 0x8000000A,
    JA_BGM_SEA_GAME = 0x8000000B,
    JA_BGM_SEA_GOAL = 0x8000000C,
    JA_BGM_SEA_FAIL = 0x8000000D,
    JA_BGM_ISLAND_LINK_2 = 0x8000000E,
    JA_BGM_I_MAJU_JAIL = 0x8000000F,
    JA_BGM_GOMA_2 = 0x80000010,
    JA_BGM_JI_TRAINING = 0x80000011,
    JA_BGM_TETRA_MEET = 0x80000012,
    JA_BGM_BK_FLY_DOWN = 0x80000013,
    JA_BGM_DK_BATTLE = 0x80000014,
    JA_BGM_MJ_TOWER_BATTLE = 0x80000015,
    JA_BGM_FIND_TETRA = 0x80000016,
    JA_BGM_I_LINK_FOREST = 0x80000017,
    JA_BGM_HOUSE_G = 0x80000018,
    JA_BGM_MBOSS = 0x80000019,
    JA_BGM_MBOSS_S = 0x8000001A,
    JA_BGM_BOAT_SHOP = 0x8000001B,
    JA_BGM_SEA_ENEMY = 0x8000001C,
    JA_BGM_MORNING = 0x8000001D,
    JA_BGM_SELECT = 0x8000001E,
    JA_BGM_MEDRI_AWAKE = 0x8000001F,
    JA_BGM_MAKORE_AWAKE = 0x80000020,
    JA_BGM_TAKT_MAKORE = 0x80000021,
    JA_BGM_TAKT_MEDRI = 0x80000022,
    JA_BGM_BST_BATTLE = 0x80000023,
    JA_BGM_GET_HEART = 0x80000024,
    JA_BGM_ITEM_GET_S = 0x80000025,
    JA_BGM_D_FOREST = 0x80000026,
    JA_BGM_GET_SONG = 0x80000027,
    JA_BGM_KAMI_TOWER = 0x80000028,
    JA_BGM_RANE_BATTLE = 0x80000029,
    JA_BGM_PIRATE = 0x8000002A,
    JA_BGM_DIOCTA_BATTLE = 0x8000002B,
    JA_BGM_PIRATE_C = 0x8000002C,
    JA_BGM_D_EARTH = 0x8000002D,
    JA_BGM_SEA = 0x8000002E,
    JA_BGM_D_WIND = 0x8000002F,
    JA_BGM_TAKT_CHUYA = 0x80000030,
    JA_BGM_TAKT_KAZE = 0x80000031,
    JA_BGM_TAKT_SHIPPU = 0x80000032,
    JA_BGM_TETRA_MEET_B = 0x80000033,
    JA_BGM_HYRULE_OFF = 0x80000034,
    JA_BGM_HYRULE_ON = 0x80000035,
    JA_BGM_CB_NEXTYEAR = 0x80000036,
    JA_BGM_CB_NEXTYEAR_W = 0x80000037,
    JA_BGM_ISLAND_LINK_0 = 0x80000038,
    JA_BGM_ISLAND_WOOD = 0x80000039,
    JA_BGM_ISLAND_DRAGON = 0x8000003A,
    JA_BGM_ISLAND_TAURA = 0x8000003B,
    JA_BGM_SEA_STORM = 0x8000003C,
    JA_BGM_PIRATE_DEMO5 = 0x8000003D,
    JA_BGM_JI_TRAINING_2 = 0x8000003E,
    JA_BGM_I_WOOD_INNER = 0x8000003F,
    JA_BGM_DRUG_STORE = 0x80000040,
    JA_BGM_P_GANON_1 = 0x80000041,
    JA_BGM_D_GANON_1 = 0x80000042,
    JA_BGM_D_GANON_2 = 0x80000043,
    JA_BGM_BAACHAN = 0x80000044,
    JA_BGM_DEKU_PINCH = 0x80000045,
    JA_BGM_DIOCTA_2 = 0x80000046,
    JA_BGM_P_GANON_2 = 0x80000047,
    JA_BGM_BIG_POW = 0x80000048,
    JA_BGM_PAST_BIG_POW = 0x80000049,
    JA_BGM_PAST_BKM = 0x8000004A,
    JA_BGM_PAST_GOMA = 0x8000004B,
    JA_BGM_PAST_RANE = 0x8000004C,
    JA_BGM_GANON_BATTLE = 0x8000004D,
    JA_BGM_MASTER_SWORD = 0x8000004E,
    JA_BGM_GET_PEARL = 0x8000004F,
    JA_BGM_BIRDMAN = 0x80000050,
    JA_BGM_BIRDMAN_GOAL = 0x80000051,
    JA_BGM_BIRDMAN_FAIL = 0x80000052,
    JA_BGM_ELF = 0x80000053,
    JA_BGM_PAST_GOMA_2 = 0x80000054,
    JA_BGM_ISLAND_LINK_3 = 0x80000055,
    JA_BGM_DEATH_VALLEY = 0x80000056,
    JA_BGM_JABOO_CAVE = 0x80000057,
    JA_BGM_SUB_DUNGEON = 0x80000058,
    JA_BGM_BGN_KUGUTSU = 0x80000059,
    JA_BGM_BGN_TARABA = 0x8000005A,
    JA_BGM_BGN_HAYAMUSHI = 0x8000005B,
    JA_BGM_BGN_TARABA_IN = 0x8000005C,
    JA_BGM_BGN_GET_BOX = 0x8000005D,
    JA_BGM_I_MAJU_2ND = 0x8000005E,
    JA_BGM_MAKORE_TAKT_8 = 0x8000005F,
    JA_BGM_MEDORI_TAKT_8 = 0x80000060,
    JA_BGM_TRIFORCE_DEMO = 0x80000061,
};

enum  {
    // These are official BGM stream enum names extracted from WWHD.
    JA_STRM_PROLOGUE = 0xC0000000,
    JA_STRM_DEMO_TETRA_FLY = 0xC0000001,
    JA_STRM_BTD_START = 0xC0000002,
    JA_STRM_BOSS_CLEAR = 0xC0000003,
    JA_STRM_DEMO_MJ_SISTER = 0xC0000004,
    JA_STRM_DEMO_GO_MAJU = 0xC0000005,
    JA_STRM_MJ_DEMO_INTRO = 0xC0000006,
    JA_STRM_BKM_START = 0xC0000007,
    JA_STRM_DK_START = 0xC0000008,
    JA_STRM_BST_START = 0xC0000009,
    JA_STRM_DEMO_14_01 = 0xC000000A,
    JA_STRM_DEMO_14_02 = 0xC000000B,
    JA_STRM_DEMO_14_03 = 0xC000000C,
    JA_STRM_DEMO_14_04 = 0xC000000D,
    JA_STRM_DEMO_14_05 = 0xC000000E,
    JA_STRM_RANE_START = 0xC000000F,
    JA_STRM_DEMO_15_01 = 0xC0000010,
    JA_STRM_DEMO_15_02 = 0xC0000011,
    JA_STRM_DEMO_15_03 = 0xC0000012,
    JA_STRM_DEMO_15_04 = 0xC0000013,
    JA_STRM_DEMO_04_01 = 0xC0000014,
    JA_STRM_DEMO_04_02 = 0xC0000015,
    JA_STRM_DEMO_08_01 = 0xC0000016,
    JA_STRM_DEMO_08_02 = 0xC0000017,
    JA_STRM_DEMO_08_03 = 0xC0000018,
    JA_STRM_BST_CLEAR = 0xC0000019,
    JA_STRM_DK_CLEAR = 0xC000001A,
    JA_STRM_BWD_CLEAR = 0xC000001B,
    JA_STRM_DEMO_05_01 = 0xC000001C,
    JA_STRM_DEMO_24_01 = 0xC000001D,
    JA_STRM_DEMO_24_02 = 0xC000001E,
    JA_STRM_DEMO_24_03 = 0xC000001F,
    JA_STRM_DEMO_24_04 = 0xC0000020,
    JA_STRM_DEMO_24_05 = 0xC0000021,
    JA_STRM_DEMO_24_06 = 0xC0000022,
    JA_STRM_DEMO_33_01 = 0xC0000023,
    JA_STRM_DEMO_01_01 = 0xC0000024,
    JA_STRM_DEMO_19_01 = 0xC0000025,
    JA_STRM_DEMO_25_01 = 0xC0000026,
    JA_STRM_DEMO_25_02 = 0xC0000027,
    JA_STRM_DEMO_25_03 = 0xC0000028,
    JA_STRM_DEMO_25_04 = 0xC0000029,
    JA_STRM_DEMO_18_01 = 0xC000002A,
    JA_STRM_DEMO_26_01 = 0xC000002B,
    JA_STRM_DEMO_26_02 = 0xC000002C,
    JA_STRM_DEMO_23_01 = 0xC000002D,
    JA_STRM_DEMO_23_02 = 0xC000002E,
    JA_STRM_DEMO_23_03 = 0xC000002F,
    JA_STRM_DEMO_23_04 = 0xC0000030,
    JA_STRM_DEMO_23_05 = 0xC0000031,
    JA_STRM_DEMO_44_01 = 0xC0000032,
    JA_STRM_DEMO_43_01 = 0xC0000033,
    JA_STRM_BPW_START = 0xC0000034,
    JA_STRM_DEMO_27_01 = 0xC0000035,
    JA_STRM_DEMO_28_01 = 0xC0000036,
    JA_STRM_DEMO_28_02 = 0xC0000037,
    JA_STRM_DEMO_29_01 = 0xC0000038,
    JA_STRM_DEMO_36_01 = 0xC0000039,
    JA_STRM_DEMO_34_01 = 0xC000003A,
    JA_STRM_DEMO_30_01 = 0xC000003B,
    JA_STRM_DEMO_31_01 = 0xC000003C,
    JA_STRM_DEMO_32_01 = 0xC000003D,
    JA_STRM_TITLE = 0xC000003E,
    JA_STRM_DEMO_42_01 = 0xC000003F,
    JA_STRM_DEMO_42_02 = 0xC0000040,
    JA_STRM_DEMO_42_03 = 0xC0000041,
    JA_STRM_DEMO_42_04 = 0xC0000042,
    JA_STRM_DEMO_42_05 = 0xC0000043,
    JA_STRM_DEMO_42_06 = 0xC0000044,
    JA_STRM_DEMO_35_01 = 0xC0000045,
    JA_STRM_DEMO_35_02 = 0xC0000046,
    JA_STRM_DEMO_35_03 = 0xC0000047,
    JA_STRM_DEMO_35_04 = 0xC0000048,
    JA_STRM_DEMO_42_07 = 0xC0000049,
    JA_STRM_DEMO_42_LAUGH = 0xC000004A,
};

enum {
    // These are special hardcoded BGM sequence numbers that are checked in JAIZelBasic::bgmStart.
    // These enum names are not official.
    JA_BGM_UNK_105 = 0x80000105, // 0x05 JA_BGM_KINDAN_BOSS
    JA_BGM_UNK_110 = 0x80000110, // 0x14 JA_BGM_DK_BATTLE
    JA_BGM_UNK_111 = 0x80000111, // 0x14 JA_BGM_DK_BATTLE
    JA_BGM_UNK_112 = 0x80000112, // 0x14 JA_BGM_DK_BATTLE
    JA_BGM_UNK_115 = 0x80000115, // 0x15 JA_BGM_DIE_LINK
    JA_BGM_UNK_120 = 0x80000120, // 0x23 JA_BGM_BST_BATTLE
    JA_BGM_UNK_121 = 0x80000121, // 0x23 JA_BGM_BST_BATTLE
    JA_BGM_UNK_122 = 0x80000122, // 0x23 JA_BGM_BST_BATTLE
    JA_BGM_UNK_123 = 0x80000123, // 0x23 JA_BGM_BST_BATTLE
    JA_BGM_UNK_124 = 0x80000124, // 0x29 JA_BGM_RANE_BATTLE
    JA_BGM_UNK_125 = 0x80000125, // 0x28 JA_BGM_KAMI_TOWER
    JA_BGM_UNK_126 = 0x80000126, // 0x28 JA_BGM_KAMI_TOWER
    JA_BGM_UNK_130 = 0x80000130, // 0x42 JA_BGM_D_GANON_1
    JA_BGM_UNK_131 = 0x80000131, // 0x42 JA_BGM_D_GANON_1
    JA_BGM_UNK_132 = 0x80000132, // 0x42 JA_BGM_D_GANON_1
    JA_BGM_UNK_133 = 0x80000133, // 0x42 JA_BGM_D_GANON_1
    JA_BGM_UNK_140 = 0x80000140, // 0x48 JA_BGM_BIG_POW
    JA_BGM_UNK_150 = 0x80000150, // 0x49 JA_BGM_PAST_BIG_POW
    JA_BGM_UNK_151 = 0x80000151, // 0x4A JA_BGM_PAST_BKM
    JA_BGM_UNK_152 = 0x80000152, // 0x4C JA_BGM_PAST_RANE
};

#endif /* JAZELAUDIO_BGM_H */