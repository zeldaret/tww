#ifndef RES_DEMO42_H
#define RES_DEMO42_H

#include "global.h"

enum DEMO42_RES_FILE_ID {
    /* BCKS */
    DEMO42_BCK_24_GND_CUT14_WALKING_L=0x0,
    DEMO42_BCK_24_GND_CUT15_SWORDTOLINK_O=0x1,
    DEMO42_BCK_24_GND_CUT16_SUNDERWAIT_L=0x2,
    DEMO42_BCK_24_GND_CUT16_SUPER_O=0x3,
    DEMO42_BCK_24_GND_CUT16_SUPERWAIT_L=0x4,
    DEMO42_BCK_42_SHMS_CUT13_O=0x17,
    DEMO42_BCK_42_SWMS2_CUT10_O=0x18,
    DEMO42_BCK_42_SWMS2_CUT13_O=0x19,
    DEMO42_BCK_42_SWMS2_CUT14_O=0x1A,
    DEMO42_BCK_42_SWMS2_CUT16_O=0x1B,
    DEMO42_BCK_42_SWMS2_CUT1_L=0x1C,
    DEMO42_BCK_42_SWMS2_CUT45B_L=0x1D,
    DEMO42_BCK_42_SWMS2_CUT45_O=0x1E,
    DEMO42_BCK_42_SWMS2_CUT46B_L=0x1F,
    DEMO42_BCK_42_SWMS2_CUT46_O=0x20,
    DEMO42_BCK_42_SWMS2_CUT48_O=0x21,
    DEMO42_BCK_42_GN_CUT11B_L=0x22,
    DEMO42_BCK_42_GN_CUT11_O=0x23,
    DEMO42_BCK_42_GN_CUT12_O=0x24,
    DEMO42_BCK_42_GN_CUT13_O=0x25,
    DEMO42_BCK_42_GN_CUT15_O=0x26,
    DEMO42_BCK_42_GN_CUT16_O=0x27,
    DEMO42_BCK_42_GN_CUT17B_L=0x28,
    DEMO42_BCK_42_GN_CUT17C_O=0x29,
    DEMO42_BCK_42_GN_CUT17_O=0x2A,
    DEMO42_BCK_42_GN_CUT18_L=0x2B,
    DEMO42_BCK_42_GN_CUT1_L=0x2C,
    DEMO42_BCK_42_GN_CUT20_L=0x2D,
    DEMO42_BCK_42_GN_CUT23_O=0x2E,
    DEMO42_BCK_42_GN_CUT24_L=0x2F,
    DEMO42_BCK_42_GN_CUT25_L=0x30,
    DEMO42_BCK_42_GN_CUT28_O=0x31,
    DEMO42_BCK_42_GN_CUT29_O=0x32,
    DEMO42_BCK_42_GN_CUT30_L=0x33,
    DEMO42_BCK_42_GN_CUT31B_L=0x34,
    DEMO42_BCK_42_GN_CUT31B_O=0x35,
    DEMO42_BCK_42_GN_CUT31_L=0x36,
    DEMO42_BCK_42_GN_CUT31_O=0x37,
    DEMO42_BCK_42_GN_CUT32_L=0x38,
    DEMO42_BCK_42_GN_CUT39_L=0x39,
    DEMO42_BCK_42_GN_CUT41_L=0x3A,
    DEMO42_BCK_42_GN_CUT42_L=0x3B,
    DEMO42_BCK_42_GN_CUT45_L=0x3C,
    DEMO42_BCK_42_GN_CUT49B_L=0x3D,
    DEMO42_BCK_42_GN_CUT49C_O=0x3E,
    DEMO42_BCK_42_GN_CUT49D_L=0x3F,
    DEMO42_BCK_42_GN_CUT49E_O=0x40,
    DEMO42_BCK_42_GN_CUT49F_L=0x41,
    DEMO42_BCK_42_GN_CUT49_O=0x42,
    DEMO42_BCK_42_GN_CUT5_L=0x43,
    DEMO42_BCK_42_GN_CUT9_L=0x44,
    DEMO42_BCK_42_HI_CUT32_L=0x45,
    DEMO42_BCK_42_HI_CUT33_L=0x46,
    DEMO42_BCK_42_HI_CUT42_L=0x47,
    DEMO42_BCK_42_MON_CUT10_O=0x48,
    DEMO42_BCK_42_PZ_CUT1_L=0x49,
    DEMO42_BCK_42_PZ_CUT22B_L=0x4A,
    DEMO42_BCK_42_PZ_CUT22_O=0x4B,
    DEMO42_BCK_42_PZ_CUT46B_L=0x4C,
    DEMO42_BCK_42_PZ_CUT46_O=0x4D,
    DEMO42_BCK_42_PZ_CUT47_L=0x4E,
    DEMO42_BCK_25_PZ_CUT23_WAIT_L=0xE6,
    
    /* BTK */
    DEMO42_BTK_24_GND_CUT14_WALKING_L=0x5,
    DEMO42_BTK_24_GND_CUT15_SWORDTOLINK_O=0x6,
    DEMO42_BTK_24_GND_CUT16_SUNDERWAIT_L=0x7,
    DEMO42_BTK_24_GND_CUT16_SUPER_O=0x8,
    DEMO42_BTK_24_GND_CUT16_SUPERWAIT_L=0x9,
    DEMO42_BTK_CY_SRT=0x13,
    DEMO42_BTK_42_GN_CUT11B_L=0x4F,
    DEMO42_BTK_42_GN_CUT11_O=0x50,
    DEMO42_BTK_42_GN_CUT12_O=0x51,
    DEMO42_BTK_42_GN_CUT13_O=0x52,
    DEMO42_BTK_42_GN_CUT15_O=0x53,
    DEMO42_BTK_42_GN_CUT16_O=0x54,
    DEMO42_BTK_42_GN_CUT17B_L=0x55,
    DEMO42_BTK_42_GN_CUT17C_O=0x56,
    DEMO42_BTK_42_GN_CUT17_O=0x57,
    DEMO42_BTK_42_GN_CUT18_L=0x58,
    DEMO42_BTK_42_GN_CUT1_L=0x59,
    DEMO42_BTK_42_GN_CUT20_L=0x5A,
    DEMO42_BTK_42_GN_CUT23_O=0x5B,
    DEMO42_BTK_42_GN_CUT24_L=0x5C,
    DEMO42_BTK_42_GN_CUT25_L=0x5D,
    DEMO42_BTK_42_GN_CUT28_O=0x5E,
    DEMO42_BTK_42_GN_CUT29_O=0x5F,
    DEMO42_BTK_42_GN_CUT30_L=0x60,
    DEMO42_BTK_42_GN_CUT31B_L=0x61,
    DEMO42_BTK_42_GN_CUT31B_O=0x62,
    DEMO42_BTK_42_GN_CUT31_L=0x63,
    DEMO42_BTK_42_GN_CUT31_O=0x64,
    DEMO42_BTK_42_GN_CUT32_L=0x65,
    DEMO42_BTK_42_GN_CUT39_L=0x66,
    DEMO42_BTK_42_GN_CUT41_L=0x67,
    DEMO42_BTK_42_GN_CUT42_L=0x68,
    DEMO42_BTK_42_GN_CUT45_L=0x69,
    DEMO42_BTK_42_GN_CUT49B_L=0x6A,
    DEMO42_BTK_42_GN_CUT49C_O=0x6B,
    DEMO42_BTK_42_GN_CUT49D_L=0x6C,
    DEMO42_BTK_42_GN_CUT49E_O=0x6D,
    DEMO42_BTK_42_GN_CUT49F_L=0x6E,
    DEMO42_BTK_42_GN_CUT49_O=0x6F,
    DEMO42_BTK_42_GN_CUT5_L=0x70,
    DEMO42_BTK_42_GN_CUT9_L=0x71,
    DEMO42_BTK_42_HI_CUT32_L=0x72,
    DEMO42_BTK_42_HI_CUT33_L=0x73,
    DEMO42_BTK_42_HI_CUT42_L=0x74,
    DEMO42_BTK_42_PZ_CUT1_L=0x75,
    DEMO42_BTK_42_PZ_CUT22B_L=0x76,
    DEMO42_BTK_42_PZ_CUT22_O=0x77,
    DEMO42_BTK_42_PZ_CUT46B_L=0x78,
    DEMO42_BTK_42_PZ_CUT46_O=0x79,
    DEMO42_BTK_42_PZ_CUT47_L=0x7A,
    DEMO42_BTK_42_SHMS_CUT13_O=0x7B,
    DEMO42_BTK_42_SWMS2_CUT10_O=0x7C,
    DEMO42_BTK_42_SWMS2_CUT13_O=0x7D,
    DEMO42_BTK_42_SWMS2_CUT14_O=0x7E,
    DEMO42_BTK_42_SWMS2_CUT16_O=0x7F,
    DEMO42_BTK_42_SWMS2_CUT1_L=0x80,
    DEMO42_BTK_42_SWMS2_CUT45B_L=0x81,
    DEMO42_BTK_42_SWMS2_CUT45_O=0x82,
    DEMO42_BTK_42_SWMS2_CUT46B_L=0x83,
    DEMO42_BTK_42_SWMS2_CUT46_O=0x84,
    DEMO42_BTK_42_SWMS2_CUT48_O=0x85,
    DEMO42_BTK_25_PZ_CUT23_WAIT_L=0xE7,
    DEMO42_BTK_25_TRI_PLUS=0xE9,
    DEMO42_BTK_V_42_TRI=0xEB,
    DEMO42_BTK_GNN_BTL_TAKI=0xF0,
    DEMO42_BTK_GNN_DEMO_TAKI_E=0xF1,
    DEMO42_BTK_GNN_DEMO_TAKI_S=0xF2,
    DEMO42_BTK_V42_TRI_ONE=0xF9,
    
    /* BTP */
    DEMO42_BTP_24_GND_CUT14_WALKING_L=0xA,
    DEMO42_BTP_24_GND_CUT15_SWORDTOLINK_O=0xB,
    DEMO42_BTP_24_GND_CUT16_SUNDERWAIT_L=0xC,
    DEMO42_BTP_24_GND_CUT16_SUPER_O=0xD,
    DEMO42_BTP_24_GND_CUT16_SUPERWAIT_L=0xE,
    DEMO42_BTP_42_HI_CUT32_L=0x86,
    DEMO42_BTP_42_HI_CUT33_L=0x87,
    DEMO42_BTP_42_HI_CUT42_L=0x88,
    DEMO42_BTP_42_GN_CUT1_L=0xBD,
    DEMO42_BTP_42_GN_CUT11_O=0xBE,
    DEMO42_BTP_42_GN_CUT11B_L=0xBF,
    DEMO42_BTP_42_GN_CUT12_O=0xC0,
    DEMO42_BTP_42_GN_CUT13_O=0xC1,
    DEMO42_BTP_42_GN_CUT15_O=0xC2,
    DEMO42_BTP_42_GN_CUT16_O=0xC3,
    DEMO42_BTP_42_GN_CUT17_O=0xC4,
    DEMO42_BTP_42_GN_CUT17B_L=0xC5,
    DEMO42_BTP_42_GN_CUT17C_O=0xC6,
    DEMO42_BTP_42_GN_CUT18_L=0xC7,
    DEMO42_BTP_42_GN_CUT20_L=0xC8,
    DEMO42_BTP_42_GN_CUT23_O=0xC9,
    DEMO42_BTP_42_GN_CUT24_L=0xCA,
    DEMO42_BTP_42_GN_CUT25_L=0xCB,
    DEMO42_BTP_42_GN_CUT28_O=0xCC,
    DEMO42_BTP_42_GN_CUT29_O=0xCD,
    DEMO42_BTP_42_GN_CUT30_L=0xCE,
    DEMO42_BTP_42_GN_CUT31_L=0xCF,
    DEMO42_BTP_42_GN_CUT31_O=0xD0,
    DEMO42_BTP_42_GN_CUT31B_L=0xD1,
    DEMO42_BTP_42_GN_CUT31B_O=0xD2,
    DEMO42_BTP_42_GN_CUT32_L=0xD3,
    DEMO42_BTP_42_GN_CUT39_L=0xD4,
    DEMO42_BTP_42_GN_CUT41_L=0xD5,
    DEMO42_BTP_42_GN_CUT42_L=0xD6,
    DEMO42_BTP_42_GN_CUT45_L=0xD7,
    DEMO42_BTP_42_GN_CUT49_O=0xD8,
    DEMO42_BTP_42_GN_CUT49B_L=0xD9,
    DEMO42_BTP_42_GN_CUT49C_O=0xDA,
    DEMO42_BTP_42_GN_CUT49D_L=0xDB,
    DEMO42_BTP_42_GN_CUT49E_O=0xDC,
    DEMO42_BTP_42_GN_CUT49F_L=0xDD,
    DEMO42_BTP_42_GN_CUT5_L=0xDE,
    DEMO42_BTP_42_GN_CUT9_L=0xDF,
    DEMO42_BTP_42_PZ_CUT22B_L=0xE0,
    DEMO42_BTP_42_PZ_CUT22_O=0xE1,
    DEMO42_BTP_42_PZ_CUT1_L=0xE2,
    DEMO42_BTP_42_PZ_CUT46_O=0xE3,
    DEMO42_BTP_42_PZ_CUT46B_L=0xE4,
    DEMO42_BTP_42_PZ_CUT47_L=0xE5,
    DEMO42_BTP_25_PZ_CUT23_WAIT_L=0xE8,
    
    /* BRK */
    DEMO42_BRK_GND_MARK_FLASH=0xF,
    DEMO42_BRK_CY_COLOR=0x14,
    DEMO42_BRK_42_GN_CUT11B_L=0x89,
    DEMO42_BRK_42_GN_CUT11_O=0x8A,
    DEMO42_BRK_42_GN_CUT12_O=0x8B,
    DEMO42_BRK_42_GN_CUT13_O=0x8C,
    DEMO42_BRK_42_GN_CUT15_O=0x8D,
    DEMO42_BRK_42_GN_CUT16_O=0x8E,
    DEMO42_BRK_42_GN_CUT17B_L=0x8F,
    DEMO42_BRK_42_GN_CUT17C_O=0x90,
    DEMO42_BRK_42_GN_CUT17_O=0x91,
    DEMO42_BRK_42_GN_CUT18_L=0x92,
    DEMO42_BRK_42_GN_CUT1_L=0x93,
    DEMO42_BRK_42_GN_CUT20_L=0x94,
    DEMO42_BRK_42_GN_CUT23_O=0x95,
    DEMO42_BRK_42_GN_CUT24_L=0x96,
    DEMO42_BRK_42_GN_CUT25_L=0x97,
    DEMO42_BRK_42_GN_CUT28_O=0x98,
    DEMO42_BRK_42_GN_CUT29_O=0x99,
    DEMO42_BRK_42_GN_CUT30_L=0x9A,
    DEMO42_BRK_42_GN_CUT31B_L=0x9B,
    DEMO42_BRK_42_GN_CUT31B_O=0x9C,
    DEMO42_BRK_42_GN_CUT31_L=0x9D,
    DEMO42_BRK_42_GN_CUT31_O=0x9E,
    DEMO42_BRK_42_GN_CUT32_L=0x9F,
    DEMO42_BRK_42_GN_CUT39_L=0xA0,
    DEMO42_BRK_42_GN_CUT41_L=0xA1,
    DEMO42_BRK_42_GN_CUT42_L=0xA2,
    DEMO42_BRK_42_GN_CUT45_L=0xA3,
    DEMO42_BRK_42_GN_CUT49B_L=0xA4,
    DEMO42_BRK_42_GN_CUT49C_O=0xA5,
    DEMO42_BRK_42_GN_CUT49D_L=0xA6,
    DEMO42_BRK_42_GN_CUT49E_O=0xA7,
    DEMO42_BRK_42_GN_CUT49F_L=0xA8,
    DEMO42_BRK_42_GN_CUT49_O=0xA9,
    DEMO42_BRK_42_GN_CUT5_L=0xAA,
    DEMO42_BRK_42_GN_CUT9_L=0xAB,
    DEMO42_BRK_42_MON_CUT10_O=0xAC,
    DEMO42_BRK_42_PZ_CUT1_L=0xAD,
    DEMO42_BRK_42_PZ_CUT22B_L=0xAE,
    DEMO42_BRK_42_PZ_CUT22_O=0xAF,
    DEMO42_BRK_42_PZ_CUT46B_L=0xB0,
    DEMO42_BRK_42_PZ_CUT46_O=0xB1,
    DEMO42_BRK_42_PZ_CUT47_L=0xB2,
    DEMO42_BRK_42_SWMS2_CUT10_O=0xB3,
    DEMO42_BRK_42_SWMS2_CUT13_O=0xB4,
    DEMO42_BRK_42_SWMS2_CUT14_O=0xB5,
    DEMO42_BRK_42_SWMS2_CUT16_O=0xB6,
    DEMO42_BRK_42_SWMS2_CUT1_L=0xB7,
    DEMO42_BRK_42_SWMS2_CUT45B_L=0xB8,
    DEMO42_BRK_42_SWMS2_CUT45_O=0xB9,
    DEMO42_BRK_42_SWMS2_CUT46B_L=0xBA,
    DEMO42_BRK_42_SWMS2_CUT46_O=0xBB,
    DEMO42_BRK_42_SWMS2_CUT48_O=0xBC,
    DEMO42_BRK_ZELDA_MARK_ON=0xFB,
    DEMO42_BRK_ZELDA_MARK_OFF=0xFC,
    
    /* BDLM */
    DEMO42_BDL_HI_COMP=0x12,
    DEMO42_BDL_25_TRI_PLUS=0xEA,
    DEMO42_BDL_CL_MON=0xED,
    DEMO42_BDL_MASTERSW_LV2=0xEE,
    DEMO42_BDL_TRI_ONLY=0xEF,
    DEMO42_BDL_GNN_BTL_TAKI=0xF3,
    DEMO42_BDL_GNN_DEMO_TAKI_S=0xF5,
    DEMO42_BDL_V_42_TRI=0xF8,
    DEMO42_BDL_V42_TRI_ONE=0xFA,
    
    /* STB */
    DEMO42_STB_G2BEFORE=0xF7,
};

enum DEMO42_RES_FILE_INDEX {
    /* BCKS */
    DEMO42_INDEX_BCK_24_GND_CUT14_WALKING_L=0x8,
    DEMO42_INDEX_BCK_24_GND_CUT15_SWORDTOLINK_O=0x9,
    DEMO42_INDEX_BCK_24_GND_CUT16_SUNDERWAIT_L=0xA,
    DEMO42_INDEX_BCK_24_GND_CUT16_SUPER_O=0xB,
    DEMO42_INDEX_BCK_24_GND_CUT16_SUPERWAIT_L=0xC,
    DEMO42_INDEX_BCK_42_SHMS_CUT13_O=0xD,
    DEMO42_INDEX_BCK_42_SWMS2_CUT10_O=0xE,
    DEMO42_INDEX_BCK_42_SWMS2_CUT13_O=0xF,
    DEMO42_INDEX_BCK_42_SWMS2_CUT14_O=0x10,
    DEMO42_INDEX_BCK_42_SWMS2_CUT16_O=0x11,
    DEMO42_INDEX_BCK_42_SWMS2_CUT1_L=0x12,
    DEMO42_INDEX_BCK_42_SWMS2_CUT45B_L=0x13,
    DEMO42_INDEX_BCK_42_SWMS2_CUT45_O=0x14,
    DEMO42_INDEX_BCK_42_SWMS2_CUT46B_L=0x15,
    DEMO42_INDEX_BCK_42_SWMS2_CUT46_O=0x16,
    DEMO42_INDEX_BCK_42_SWMS2_CUT48_O=0x17,
    DEMO42_INDEX_BCK_42_GN_CUT11B_L=0x18,
    DEMO42_INDEX_BCK_42_GN_CUT11_O=0x19,
    DEMO42_INDEX_BCK_42_GN_CUT12_O=0x1A,
    DEMO42_INDEX_BCK_42_GN_CUT13_O=0x1B,
    DEMO42_INDEX_BCK_42_GN_CUT15_O=0x1C,
    DEMO42_INDEX_BCK_42_GN_CUT16_O=0x1D,
    DEMO42_INDEX_BCK_42_GN_CUT17B_L=0x1E,
    DEMO42_INDEX_BCK_42_GN_CUT17C_O=0x1F,
    DEMO42_INDEX_BCK_42_GN_CUT17_O=0x20,
    DEMO42_INDEX_BCK_42_GN_CUT18_L=0x21,
    DEMO42_INDEX_BCK_42_GN_CUT1_L=0x22,
    DEMO42_INDEX_BCK_42_GN_CUT20_L=0x23,
    DEMO42_INDEX_BCK_42_GN_CUT23_O=0x24,
    DEMO42_INDEX_BCK_42_GN_CUT24_L=0x25,
    DEMO42_INDEX_BCK_42_GN_CUT25_L=0x26,
    DEMO42_INDEX_BCK_42_GN_CUT28_O=0x27,
    DEMO42_INDEX_BCK_42_GN_CUT29_O=0x28,
    DEMO42_INDEX_BCK_42_GN_CUT30_L=0x29,
    DEMO42_INDEX_BCK_42_GN_CUT31B_L=0x2A,
    DEMO42_INDEX_BCK_42_GN_CUT31B_O=0x2B,
    DEMO42_INDEX_BCK_42_GN_CUT31_L=0x2C,
    DEMO42_INDEX_BCK_42_GN_CUT31_O=0x2D,
    DEMO42_INDEX_BCK_42_GN_CUT32_L=0x2E,
    DEMO42_INDEX_BCK_42_GN_CUT39_L=0x2F,
    DEMO42_INDEX_BCK_42_GN_CUT41_L=0x30,
    DEMO42_INDEX_BCK_42_GN_CUT42_L=0x31,
    DEMO42_INDEX_BCK_42_GN_CUT45_L=0x32,
    DEMO42_INDEX_BCK_42_GN_CUT49B_L=0x33,
    DEMO42_INDEX_BCK_42_GN_CUT49C_O=0x34,
    DEMO42_INDEX_BCK_42_GN_CUT49D_L=0x35,
    DEMO42_INDEX_BCK_42_GN_CUT49E_O=0x36,
    DEMO42_INDEX_BCK_42_GN_CUT49F_L=0x37,
    DEMO42_INDEX_BCK_42_GN_CUT49_O=0x38,
    DEMO42_INDEX_BCK_42_GN_CUT5_L=0x39,
    DEMO42_INDEX_BCK_42_GN_CUT9_L=0x3A,
    DEMO42_INDEX_BCK_42_HI_CUT32_L=0x3B,
    DEMO42_INDEX_BCK_42_HI_CUT33_L=0x3C,
    DEMO42_INDEX_BCK_42_HI_CUT42_L=0x3D,
    DEMO42_INDEX_BCK_42_MON_CUT10_O=0x3E,
    DEMO42_INDEX_BCK_42_PZ_CUT1_L=0x3F,
    DEMO42_INDEX_BCK_42_PZ_CUT22B_L=0x40,
    DEMO42_INDEX_BCK_42_PZ_CUT22_O=0x41,
    DEMO42_INDEX_BCK_42_PZ_CUT46B_L=0x42,
    DEMO42_INDEX_BCK_42_PZ_CUT46_O=0x43,
    DEMO42_INDEX_BCK_42_PZ_CUT47_L=0x44,
    DEMO42_INDEX_BCK_25_PZ_CUT23_WAIT_L=0x45,
    
    /* BTK */
    DEMO42_INDEX_BTK_24_GND_CUT14_WALKING_L=0x48,
    DEMO42_INDEX_BTK_24_GND_CUT15_SWORDTOLINK_O=0x49,
    DEMO42_INDEX_BTK_24_GND_CUT16_SUNDERWAIT_L=0x4A,
    DEMO42_INDEX_BTK_24_GND_CUT16_SUPER_O=0x4B,
    DEMO42_INDEX_BTK_24_GND_CUT16_SUPERWAIT_L=0x4C,
    DEMO42_INDEX_BTK_CY_SRT=0x4D,
    DEMO42_INDEX_BTK_42_GN_CUT11B_L=0x4E,
    DEMO42_INDEX_BTK_42_GN_CUT11_O=0x4F,
    DEMO42_INDEX_BTK_42_GN_CUT12_O=0x50,
    DEMO42_INDEX_BTK_42_GN_CUT13_O=0x51,
    DEMO42_INDEX_BTK_42_GN_CUT15_O=0x52,
    DEMO42_INDEX_BTK_42_GN_CUT16_O=0x53,
    DEMO42_INDEX_BTK_42_GN_CUT17B_L=0x54,
    DEMO42_INDEX_BTK_42_GN_CUT17C_O=0x55,
    DEMO42_INDEX_BTK_42_GN_CUT17_O=0x56,
    DEMO42_INDEX_BTK_42_GN_CUT18_L=0x57,
    DEMO42_INDEX_BTK_42_GN_CUT1_L=0x58,
    DEMO42_INDEX_BTK_42_GN_CUT20_L=0x59,
    DEMO42_INDEX_BTK_42_GN_CUT23_O=0x5A,
    DEMO42_INDEX_BTK_42_GN_CUT24_L=0x5B,
    DEMO42_INDEX_BTK_42_GN_CUT25_L=0x5C,
    DEMO42_INDEX_BTK_42_GN_CUT28_O=0x5D,
    DEMO42_INDEX_BTK_42_GN_CUT29_O=0x5E,
    DEMO42_INDEX_BTK_42_GN_CUT30_L=0x5F,
    DEMO42_INDEX_BTK_42_GN_CUT31B_L=0x60,
    DEMO42_INDEX_BTK_42_GN_CUT31B_O=0x61,
    DEMO42_INDEX_BTK_42_GN_CUT31_L=0x62,
    DEMO42_INDEX_BTK_42_GN_CUT31_O=0x63,
    DEMO42_INDEX_BTK_42_GN_CUT32_L=0x64,
    DEMO42_INDEX_BTK_42_GN_CUT39_L=0x65,
    DEMO42_INDEX_BTK_42_GN_CUT41_L=0x66,
    DEMO42_INDEX_BTK_42_GN_CUT42_L=0x67,
    DEMO42_INDEX_BTK_42_GN_CUT45_L=0x68,
    DEMO42_INDEX_BTK_42_GN_CUT49B_L=0x69,
    DEMO42_INDEX_BTK_42_GN_CUT49C_O=0x6A,
    DEMO42_INDEX_BTK_42_GN_CUT49D_L=0x6B,
    DEMO42_INDEX_BTK_42_GN_CUT49E_O=0x6C,
    DEMO42_INDEX_BTK_42_GN_CUT49F_L=0x6D,
    DEMO42_INDEX_BTK_42_GN_CUT49_O=0x6E,
    DEMO42_INDEX_BTK_42_GN_CUT5_L=0x6F,
    DEMO42_INDEX_BTK_42_GN_CUT9_L=0x70,
    DEMO42_INDEX_BTK_42_HI_CUT32_L=0x71,
    DEMO42_INDEX_BTK_42_HI_CUT33_L=0x72,
    DEMO42_INDEX_BTK_42_HI_CUT42_L=0x73,
    DEMO42_INDEX_BTK_42_PZ_CUT1_L=0x74,
    DEMO42_INDEX_BTK_42_PZ_CUT22B_L=0x75,
    DEMO42_INDEX_BTK_42_PZ_CUT22_O=0x76,
    DEMO42_INDEX_BTK_42_PZ_CUT46B_L=0x77,
    DEMO42_INDEX_BTK_42_PZ_CUT46_O=0x78,
    DEMO42_INDEX_BTK_42_PZ_CUT47_L=0x79,
    DEMO42_INDEX_BTK_42_SHMS_CUT13_O=0x7A,
    DEMO42_INDEX_BTK_42_SWMS2_CUT10_O=0x7B,
    DEMO42_INDEX_BTK_42_SWMS2_CUT13_O=0x7C,
    DEMO42_INDEX_BTK_42_SWMS2_CUT14_O=0x7D,
    DEMO42_INDEX_BTK_42_SWMS2_CUT16_O=0x7E,
    DEMO42_INDEX_BTK_42_SWMS2_CUT1_L=0x7F,
    DEMO42_INDEX_BTK_42_SWMS2_CUT45B_L=0x80,
    DEMO42_INDEX_BTK_42_SWMS2_CUT45_O=0x81,
    DEMO42_INDEX_BTK_42_SWMS2_CUT46B_L=0x82,
    DEMO42_INDEX_BTK_42_SWMS2_CUT46_O=0x83,
    DEMO42_INDEX_BTK_42_SWMS2_CUT48_O=0x84,
    DEMO42_INDEX_BTK_25_PZ_CUT23_WAIT_L=0x85,
    DEMO42_INDEX_BTK_25_TRI_PLUS=0x86,
    DEMO42_INDEX_BTK_V_42_TRI=0x87,
    DEMO42_INDEX_BTK_GNN_BTL_TAKI=0x88,
    DEMO42_INDEX_BTK_GNN_DEMO_TAKI_E=0x89,
    DEMO42_INDEX_BTK_GNN_DEMO_TAKI_S=0x8A,
    DEMO42_INDEX_BTK_V42_TRI_ONE=0x8B,
    
    /* BTP */
    DEMO42_INDEX_BTP_24_GND_CUT14_WALKING_L=0x8E,
    DEMO42_INDEX_BTP_24_GND_CUT15_SWORDTOLINK_O=0x8F,
    DEMO42_INDEX_BTP_24_GND_CUT16_SUNDERWAIT_L=0x90,
    DEMO42_INDEX_BTP_24_GND_CUT16_SUPER_O=0x91,
    DEMO42_INDEX_BTP_24_GND_CUT16_SUPERWAIT_L=0x92,
    DEMO42_INDEX_BTP_42_HI_CUT32_L=0x93,
    DEMO42_INDEX_BTP_42_HI_CUT33_L=0x94,
    DEMO42_INDEX_BTP_42_HI_CUT42_L=0x95,
    DEMO42_INDEX_BTP_42_GN_CUT1_L=0x96,
    DEMO42_INDEX_BTP_42_GN_CUT11_O=0x97,
    DEMO42_INDEX_BTP_42_GN_CUT11B_L=0x98,
    DEMO42_INDEX_BTP_42_GN_CUT12_O=0x99,
    DEMO42_INDEX_BTP_42_GN_CUT13_O=0x9A,
    DEMO42_INDEX_BTP_42_GN_CUT15_O=0x9B,
    DEMO42_INDEX_BTP_42_GN_CUT16_O=0x9C,
    DEMO42_INDEX_BTP_42_GN_CUT17_O=0x9D,
    DEMO42_INDEX_BTP_42_GN_CUT17B_L=0x9E,
    DEMO42_INDEX_BTP_42_GN_CUT17C_O=0x9F,
    DEMO42_INDEX_BTP_42_GN_CUT18_L=0xA0,
    DEMO42_INDEX_BTP_42_GN_CUT20_L=0xA1,
    DEMO42_INDEX_BTP_42_GN_CUT23_O=0xA2,
    DEMO42_INDEX_BTP_42_GN_CUT24_L=0xA3,
    DEMO42_INDEX_BTP_42_GN_CUT25_L=0xA4,
    DEMO42_INDEX_BTP_42_GN_CUT28_O=0xA5,
    DEMO42_INDEX_BTP_42_GN_CUT29_O=0xA6,
    DEMO42_INDEX_BTP_42_GN_CUT30_L=0xA7,
    DEMO42_INDEX_BTP_42_GN_CUT31_L=0xA8,
    DEMO42_INDEX_BTP_42_GN_CUT31_O=0xA9,
    DEMO42_INDEX_BTP_42_GN_CUT31B_L=0xAA,
    DEMO42_INDEX_BTP_42_GN_CUT31B_O=0xAB,
    DEMO42_INDEX_BTP_42_GN_CUT32_L=0xAC,
    DEMO42_INDEX_BTP_42_GN_CUT39_L=0xAD,
    DEMO42_INDEX_BTP_42_GN_CUT41_L=0xAE,
    DEMO42_INDEX_BTP_42_GN_CUT42_L=0xAF,
    DEMO42_INDEX_BTP_42_GN_CUT45_L=0xB0,
    DEMO42_INDEX_BTP_42_GN_CUT49_O=0xB1,
    DEMO42_INDEX_BTP_42_GN_CUT49B_L=0xB2,
    DEMO42_INDEX_BTP_42_GN_CUT49C_O=0xB3,
    DEMO42_INDEX_BTP_42_GN_CUT49D_L=0xB4,
    DEMO42_INDEX_BTP_42_GN_CUT49E_O=0xB5,
    DEMO42_INDEX_BTP_42_GN_CUT49F_L=0xB6,
    DEMO42_INDEX_BTP_42_GN_CUT5_L=0xB7,
    DEMO42_INDEX_BTP_42_GN_CUT9_L=0xB8,
    DEMO42_INDEX_BTP_42_PZ_CUT22B_L=0xB9,
    DEMO42_INDEX_BTP_42_PZ_CUT22_O=0xBA,
    DEMO42_INDEX_BTP_42_PZ_CUT1_L=0xBB,
    DEMO42_INDEX_BTP_42_PZ_CUT46_O=0xBC,
    DEMO42_INDEX_BTP_42_PZ_CUT46B_L=0xBD,
    DEMO42_INDEX_BTP_42_PZ_CUT47_L=0xBE,
    DEMO42_INDEX_BTP_25_PZ_CUT23_WAIT_L=0xBF,
    
    /* BRK */
    DEMO42_INDEX_BRK_GND_MARK_FLASH=0xC2,
    DEMO42_INDEX_BRK_CY_COLOR=0xC3,
    DEMO42_INDEX_BRK_42_GN_CUT11B_L=0xC4,
    DEMO42_INDEX_BRK_42_GN_CUT11_O=0xC5,
    DEMO42_INDEX_BRK_42_GN_CUT12_O=0xC6,
    DEMO42_INDEX_BRK_42_GN_CUT13_O=0xC7,
    DEMO42_INDEX_BRK_42_GN_CUT15_O=0xC8,
    DEMO42_INDEX_BRK_42_GN_CUT16_O=0xC9,
    DEMO42_INDEX_BRK_42_GN_CUT17B_L=0xCA,
    DEMO42_INDEX_BRK_42_GN_CUT17C_O=0xCB,
    DEMO42_INDEX_BRK_42_GN_CUT17_O=0xCC,
    DEMO42_INDEX_BRK_42_GN_CUT18_L=0xCD,
    DEMO42_INDEX_BRK_42_GN_CUT1_L=0xCE,
    DEMO42_INDEX_BRK_42_GN_CUT20_L=0xCF,
    DEMO42_INDEX_BRK_42_GN_CUT23_O=0xD0,
    DEMO42_INDEX_BRK_42_GN_CUT24_L=0xD1,
    DEMO42_INDEX_BRK_42_GN_CUT25_L=0xD2,
    DEMO42_INDEX_BRK_42_GN_CUT28_O=0xD3,
    DEMO42_INDEX_BRK_42_GN_CUT29_O=0xD4,
    DEMO42_INDEX_BRK_42_GN_CUT30_L=0xD5,
    DEMO42_INDEX_BRK_42_GN_CUT31B_L=0xD6,
    DEMO42_INDEX_BRK_42_GN_CUT31B_O=0xD7,
    DEMO42_INDEX_BRK_42_GN_CUT31_L=0xD8,
    DEMO42_INDEX_BRK_42_GN_CUT31_O=0xD9,
    DEMO42_INDEX_BRK_42_GN_CUT32_L=0xDA,
    DEMO42_INDEX_BRK_42_GN_CUT39_L=0xDB,
    DEMO42_INDEX_BRK_42_GN_CUT41_L=0xDC,
    DEMO42_INDEX_BRK_42_GN_CUT42_L=0xDD,
    DEMO42_INDEX_BRK_42_GN_CUT45_L=0xDE,
    DEMO42_INDEX_BRK_42_GN_CUT49B_L=0xDF,
    DEMO42_INDEX_BRK_42_GN_CUT49C_O=0xE0,
    DEMO42_INDEX_BRK_42_GN_CUT49D_L=0xE1,
    DEMO42_INDEX_BRK_42_GN_CUT49E_O=0xE2,
    DEMO42_INDEX_BRK_42_GN_CUT49F_L=0xE3,
    DEMO42_INDEX_BRK_42_GN_CUT49_O=0xE4,
    DEMO42_INDEX_BRK_42_GN_CUT5_L=0xE5,
    DEMO42_INDEX_BRK_42_GN_CUT9_L=0xE6,
    DEMO42_INDEX_BRK_42_MON_CUT10_O=0xE7,
    DEMO42_INDEX_BRK_42_PZ_CUT1_L=0xE8,
    DEMO42_INDEX_BRK_42_PZ_CUT22B_L=0xE9,
    DEMO42_INDEX_BRK_42_PZ_CUT22_O=0xEA,
    DEMO42_INDEX_BRK_42_PZ_CUT46B_L=0xEB,
    DEMO42_INDEX_BRK_42_PZ_CUT46_O=0xEC,
    DEMO42_INDEX_BRK_42_PZ_CUT47_L=0xED,
    DEMO42_INDEX_BRK_42_SWMS2_CUT10_O=0xEE,
    DEMO42_INDEX_BRK_42_SWMS2_CUT13_O=0xEF,
    DEMO42_INDEX_BRK_42_SWMS2_CUT14_O=0xF0,
    DEMO42_INDEX_BRK_42_SWMS2_CUT16_O=0xF1,
    DEMO42_INDEX_BRK_42_SWMS2_CUT1_L=0xF2,
    DEMO42_INDEX_BRK_42_SWMS2_CUT45B_L=0xF3,
    DEMO42_INDEX_BRK_42_SWMS2_CUT45_O=0xF4,
    DEMO42_INDEX_BRK_42_SWMS2_CUT46B_L=0xF5,
    DEMO42_INDEX_BRK_42_SWMS2_CUT46_O=0xF6,
    DEMO42_INDEX_BRK_42_SWMS2_CUT48_O=0xF7,
    DEMO42_INDEX_BRK_ZELDA_MARK_ON=0xF8,
    DEMO42_INDEX_BRK_ZELDA_MARK_OFF=0xF9,
    
    /* BDLM */
    DEMO42_INDEX_BDL_HI_COMP=0xFC,
    DEMO42_INDEX_BDL_25_TRI_PLUS=0xFD,
    DEMO42_INDEX_BDL_CL_MON=0xFE,
    DEMO42_INDEX_BDL_MASTERSW_LV2=0xFF,
    DEMO42_INDEX_BDL_TRI_ONLY=0x100,
    DEMO42_INDEX_BDL_GNN_BTL_TAKI=0x101,
    DEMO42_INDEX_BDL_GNN_DEMO_TAKI_S=0x102,
    DEMO42_INDEX_BDL_V_42_TRI=0x103,
    DEMO42_INDEX_BDL_V42_TRI_ONE=0x104,
    
    /* STB */
    DEMO42_INDEX_STB_G2BEFORE=0x107,
};

#endif /* RES_DEMO42_H */
