//
// Generated by dtk
// Translation Unit: JAIZelScene.cpp
//

#include "JAZelAudio/JAIZelBasic.h"
#include "dolphin/types.h"

u8 JAIZelBasic::m_bgm_wave_info[96] = {};
u8 JAIZelBasic::m_dy_wave_set_1st[][2] = {
    {0x00, 0x00},
    {0x09, 0x17},
    {0x0A, 0x16},
    {0x0B, 0x24},
    {0x27, 0x0F},
    {0x13, 0x15},
    {0x10, 0x25},
    {0x11, 0x00},
    {0x14, 0x2A},
    {0x15, 0x18},
    {0x15, 0x19},
    {0x1B, 0x3B},
    {0x1A, 0x15},
    {0x1C, 0x15},
    {0x27, 0x1D},
    {0x1F, 0x2D},
    {0x21, 0x34},
    {0x15, 0x1A},
    {0x23, 0x29},
    {0x15, 0x2B},
    {0x2C, 0x3E},
    {0x2E, 0x00},
    {0x30, 0x34},
    {0x31, 0x10},
    {0x32, 0x0A},
    {0x33, 0x38},
    {0x15, 0x34},
    {0x15, 0x35},
    {0x36, 0x09},
    {0x36, 0x0B},
    {0x36, 0x23},
    {0x36, 0x14},
    {0x28, 0x3D},
    {0x39, 0x00},
    {0x3A, 0x3C},
    {0x3A, 0x3C},
    {0x2E, 0x1D},
    {0x3C, 0x00},
    {0x3C, 0x00},
    {0x29, 0x3C},
    {0x2A, 0x3C},
    {0x0F, 0x3C},
    {0x3E, 0x3F},
    {0x39, 0x1D},
    {0x40, 0x00},
    {0x00, 0x00},
    {0x00, 0x00},
    {0x00, 0x00},
    {0x00, 0x00},
    {0x00, 0x00},
};

u8 JAIZelBasic::m_dy_wave_set_2nd[][2] = {
    {0x00, 0x00},
    {0x0D, 0x00},
    {0x0E, 0x00},
    {0x0D, 0x00},
    {0x12, 0x00},
    {0x1E, 0x00},
    {0x20, 0x28},
    {0x22, 0x00},
    {0x20, 0x1E},
    {0x26, 0x00},
    {0x2F, 0x00},
    {0x0C, 0x00},
    {0x37, 0x00},
    {0x0F, 0x00},
    {0x00, 0x00},
    {0x00, 0x00},
    {0x00, 0x00},
    {0x00, 0x00},
    {0x00, 0x00},
    {0x00, 0x00},
};

JAIZelBasic::scene_info_s JAIZelBasic::m_scene_info[] = {
    {0x0000,               0x00, 0x00},
    {JA_BGM_D_RYU_MT,      0x01, 0x05},
    {0x0000,               0x01, 0x01},
    {JA_BGM_D_FOREST,      0x03, 0x05},
    {JA_BGM_I_MAJU_2ND,    0x02, 0x05},
    {JA_BGM_D_GANON_1,     0x17, 0x00},
    {JA_BGM_D_GANON_1,     0x17, 0x00},
    {0x0000,               0x03, 0x02},
    {JA_BGM_I_MAJU,        0x02, 0x05},
    {0x0000,               0x07, 0x04},
    {JA_BGM_KAMI_TOWER,    0x06, 0x05},
    {JA_BGM_HOUSE,         0x1B, 0x00},
    {JA_BGM_PIRATE_C,      0x04, 0x00},
    {JA_BGM_HOUSE_G,       0x09, 0x00},
    {JA_BGM_BOAT_SHOP,     0x10, 0x00},
    {JA_BGM_D_EARTH,       0x12, 0x05},
    {JA_BGM_I_LINK_FOREST, 0x05, 0x03},
    {JA_BGM_PIRATE,        0x0E, 0x00},
    {0x0000,               0x00, 0x00},
    {JA_BGM_I_MAJU,        0x02, 0x00},
    {JA_BGM_D_GANON_1,     0x17, 0x00},
    {JA_BGM_D_GANON_1,     0x17, 0x00},
    {JA_BGM_JABOO_CAVE,    0x28, 0x00},
    {JA_BGM_D_WIND,        0x08, 0x05},
    {0x0000,               0x08, 0x09},
    {JA_BGM_D_GANON_1,     0x17, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_DRUG_STORE,    0x16, 0x00},
    {JA_BGM_HOUSE,         0x0C, 0x00},
    {JA_BGM_HOUSE,         0x1A, 0x00},
    {JA_BGM_HOUSE,         0x0D, 0x00},
    {JA_BGM_HOUSE,         0x1B, 0x00},
    {JA_BGM_HOUSE,         0x1B, 0x00},
    {0x0000,               0x19, 0x00},
    {JA_BGM_HOUSE,         0x19, 0x00},
    {0x0000,               0x01, 0x05},
    {JA_BGM_D_GANON_2,     0x18, 0x0A},
    {0x0000,               0x06, 0x07},
    {JA_BGM_DRUG_STORE,    0x16, 0x00},
    {JA_BGM_I_WOOD_INNER,  0x0F, 0x0C},
    {0x0000,               0x1C, 0x00},
    {JA_BGM_JABOO_CAVE,    0x22, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_JABOO_CAVE,    0x27, 0x00},
    {0x0000,               0x12, 0x0B},
    {JA_BGM_D_GANON_1,     0x17, 0x00},
    {JA_BGM_UNK_130,       0x17, 0x00},
    {JA_BGM_UNK_131,       0x17, 0x00},
    {JA_BGM_UNK_132,       0x17, 0x00},
    {JA_BGM_UNK_133,       0x17, 0x00},
    {JA_BGM_D_GANON_1,     0x17, 0x00},
    {JA_BGM_D_GANON_1,     0x17, 0x00},
    {JA_BGM_DEATH_VALLEY,  0x25, 0x00},
    {JA_BGM_HYRULE_ON,     0x14, 0x00},
    {0x0000,               0x1D, 0x00},
    {JA_BGM_KAMI_TOWER,    0x06, 0x05},
    {0x0000,               0x0F, 0x0C},
    {0x0000,               0x1E, 0x00},
    {0x0000,               0x1F, 0x00},
    {JA_BGM_D_EARTH,       0x12, 0x05},
    {JA_BGM_HOUSE,         0x19, 0x00},
    {JA_BGM_D_FOREST,      0x03, 0x05},
    {JA_BGM_I_MAJU_2ND,    0x02, 0x05},
    {0x0000,               0x07, 0x04},
    {JA_BGM_D_WIND,        0x08, 0x05},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_ELF,           0x24, 0x00},
    {JA_BGM_ELF,           0x24, 0x00},
    {JA_BGM_ELF,           0x24, 0x00},
    {JA_BGM_ELF,           0x24, 0x00},
    {JA_BGM_ELF,           0x24, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x23, 0x0D},
    {0x0000,               0x06, 0x05},
    {JA_BGM_HOUSE,         0x1B, 0x00},
    {JA_BGM_HOUSE,         0x0C, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x29, 0x00},
    {JA_BGM_HYRULE_ON,     0x14, 0x05},
    {0x0000,               0x2C, 0x00},
    {0x0000,               0x2A, 0x00},
    {0x0000,               0x20, 0x00},
    {JA_BGM_ELF,           0x24, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_HOUSE,         0x09, 0x00},
    {JA_BGM_HOUSE_G,       0x09, 0x00},
    {JA_BGM_D_GANON_2,     0x18, 0x0A},
    {JA_BGM_D_GANON_1,     0x17, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {JA_BGM_SUB_DUNGEON,   0x26, 0x00},
    {0x0000,               0x00, 0x00},
    {0x0000,               0x00, 0x00},
    {0x0000,               0x00, 0x00},
    {0x0000,               0x00, 0x00},
};

JAIZelBasic::scene_info_s JAIZelBasic::m_isle_info[] = {
    {0x0000,               0x00, 0x00},
    {JA_BGM_I_MAJU,        0x02, 0x0A},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x2B, 0x06},
    {0x0000,               0x1A, 0x06},
    {JA_BGM_ISLAND_TAURA,  0x0B, 0x00},
    {0x0000,               0x0A, 0x06},
    {JA_BGM_ISLAND_DRAGON, 0x19, 0x06},
    {0x0000,               0x15, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x11, 0x06},
    {0x0000,               0x21, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x10, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x13, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x13, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x21, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {JA_BGM_ISLAND_WOOD,   0x0F, 0x00},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {JA_BGM_ISLAND_LINK,   0x0A, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x24, 0x06},
    {0x0000,               0x0A, 0x06},
    {0x0000,               0x15, 0x06},
    {0x0000,               0x0A, 0x06},
};

const char* JAIZelBasic::spot_dir_name[] = {
    "M_NewD2",
    "M_DragB",
    "kindan",
    "ma3room",
    "GanonF",
    "GanonG",
    "kinBOSS",
    "majroom",
    "Mjtower",
    "Siren",
    "LinkRM",
    "Asoko",
    "Ojhous",
    "Obshop",
    "M_Dai",
    "A_mori",
    "A_umikz",
    "sea",
    "MajyuE",
    "GanonH",
    "GanonI",
    "Ekaze",
    "kaze",
    "kazeB",
    "GanonL",
    "Opub",
    "Pdrgsh",
    "Pnezumi",
    "Kaisen",
    "Orichh",
    "Ocmera",
    "Obombh",
    "Adanmae",
    "Atorizk",
    "M_Dra09",
    "GanonJ",
    "SirenB",
    "Ocrogh",
    "Omori",
    "Xboss0",
    "Pjavdou",
    "Omasao",
    "Onobuta",
    "Edaichi",
    "M_DaiB",
    "GanonA",
    "GanonB",
    "GanonC",
    "GanonD",
    "GanonE",
    "GanonF",
    "GanonG",
    "Hyrule",
    "Hyroom",
    "Xboss1",
    "SirenMB",
    "Otkura",
    "Xboss2",
    "Xboss3",
    "M_DaiMB",
    "Comori",
    "kinMB",
    "ma2room",
    "M2tower",
    "kazeMB",
    "MiniKaz",
    "MiniHyo",
    "TyuTyu",
    "WarpD",
    "ShipD",
    "Cave01",
    "Cave02",
    "Cave03",
    "Cave04",
    "TF_01",
    "TF_02",
    "TF_03",
    "Fairy01",
    "Fairy02",
    "Fairy03",
    "Fairy04",
    "Fairy05",
    "TF_04",
    "PShip",
    "ADMumi",
    "Nitiyou",
    "Abesso",
    "Abship",
    "kenroom",
    "M2ganon",
    "GanonK",
    "GTower",
    "Fairy06",
    "Cave05",
    "Cave06",
    "Pfigure",
    "figureA",
    "figureB",
    "figureC",
    "figureD",
    "figureE",
    "figureF",
    "figureG",
    "Ojhous2",
    "GanonM",
    "GanonN",
    "Cave09",
    "Cave10",
    "Cave11",
    "Cave07",
    "TF_06",
    "ITest62",
    "ITest63",
    "SubD71",
    "SubD43",
    "SubD42",
    "sea_T",
    "dummy",
    "dummy",
    ""
};
