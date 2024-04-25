#ifndef RES_TN_H
#define RES_TN_H

#include "global.h"

enum TN_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    TN_BAS_AAT_KAITEN2=0x6,
    TN_BAS_AAT_KAITEN3=0x7,
    TN_BAS_AAT_KAITEN4=0x8,
    TN_BAS_AAT_KAITEN_FB1=0x9,
    TN_BAS_AAT_KAITEN_LR1=0xA,
    TN_BAS_AAT_TATE1=0xB,
    TN_BAS_AAT_YOKO1=0xC,
    TN_BAS_AHAJIKI1=0xD,
    TN_BAS_AHAZURE1=0xE,
    TN_BAS_ASURI_FB1=0xF,
    TN_BAS_ASURI_LR1=0x10,
    TN_BAS_AWALK1=0x11,
    TN_BAS_BAT_JUMP1=0x12,
    TN_BAS_BAT_KAITEN2=0x13,
    TN_BAS_BAT_KAITEN3=0x14,
    TN_BAS_BAT_KAITEN4=0x15,
    TN_BAS_BAT_KERI1=0x16,
    TN_BAS_BAT_SHOUTEI_L1=0x17,
    TN_BAS_BAT_SYOUTEI_S1=0x18,
    TN_BAS_BAT_TATE1=0x19,
    TN_BAS_BAT_YOKO1=0x1A,
    TN_BAS_BBACK1=0x1B,
    TN_BAS_BBACK_S1=0x1C,
    TN_BAS_BHIROU_K1=0x1D,
    TN_BAS_BOKIRU_A1=0x1E,
    TN_BAS_BOKIRU_U1=0x1F,
    TN_BAS_BRUN1=0x20,
    TN_BAS_BRUN2=0x21,
    TN_BAS_BSURI_SFB1=0x22,
    TN_BAS_BSURI_SLR1=0x23,
    TN_BAS_S_DEMO_M1=0x24,
    TN_BAS_S_DEMO_M2=0x25,
    
    /* BCK */
    TN_BCK_AAT_KAITEN1=0x28,
    TN_BCK_AAT_KAITEN2=0x29,
    TN_BCK_AAT_KAITEN3=0x2A,
    TN_BCK_AAT_KAITEN4=0x2B,
    TN_BCK_AAT_KAITEN_FB1=0x2C,
    TN_BCK_AAT_KAITEN_LR1=0x2D,
    TN_BCK_AAT_TATE1=0x2E,
    TN_BCK_AAT_YOKO1=0x2F,
    TN_BCK_AGUARD1=0x30,
    TN_BCK_AGUARD2=0x31,
    TN_BCK_AHAJIKI1=0x32,
    TN_BCK_AHAKAI1=0x33,
    TN_BCK_AHAZURE1=0x34,
    TN_BCK_AKAMAE1=0x35,
    TN_BCK_AKIDUKU1=0x36,
    TN_BCK_AKYORO1=0x37,
    TN_BCK_AMAHI1=0x38,
    TN_BCK_ANIOU1=0x39,
    TN_BCK_ASURI_FB1=0x3A,
    TN_BCK_ASURI_LR1=0x3B,
    TN_BCK_ATATE_ON1=0x3C,
    TN_BCK_AWAIT1=0x3D,
    TN_BCK_AWALK1=0x3E,
    TN_BCK_BAT_JUMP1=0x3F,
    TN_BCK_BAT_KAITEN2=0x40,
    TN_BCK_BAT_KAITEN3=0x41,
    TN_BCK_BAT_KAITEN4=0x42,
    TN_BCK_BAT_KERI1=0x43,
    TN_BCK_BAT_SYOUTEI_L1=0x44,
    TN_BCK_BAT_SYOUTEI_S1=0x45,
    TN_BCK_BAT_TATE1=0x46,
    TN_BCK_BAT_YOKO1=0x47,
    TN_BCK_BBACK1=0x48,
    TN_BCK_BBACK_S1=0x49,
    TN_BCK_BDOWN_A1=0x4A,
    TN_BCK_BDOWN_U1=0x4B,
    TN_BCK_BHIROU_K1=0x4C,
    TN_BCK_BKAMAE_S1=0x4D,
    TN_BCK_BOKIRU_A1=0x4E,
    TN_BCK_BOKIRU_U1=0x4F,
    TN_BCK_BRUN1=0x50,
    TN_BCK_BRUN2=0x51,
    TN_BCK_BSURI_SFB1=0x52,
    TN_BCK_BSURI_SLR1=0x53,
    TN_BCK_S_DEMO_M1=0x54,
    TN_BCK_S_DEMO_M2=0x55,
    TN_BCK_S_DEMO_Y1=0x56,
    TN_BCK_S_DEMO_Y2=0x57,
    TN_BCK_YAT_KAITEN1=0x58,
    TN_BCK_YAT_KAITEN2=0x59,
    TN_BCK_YAT_KAITEN3=0x5A,
    TN_BCK_YAT_KAITEN4=0x5B,
    TN_BCK_YAT_TATE1=0x5C,
    TN_BCK_YAT_YOKO1=0x5D,
    TN_BCK_YGUARD1=0x5E,
    TN_BCK_YHAJIKI1=0x5F,
    TN_BCK_YHAKAI1=0x60,
    TN_BCK_YHAZURE1=0x61,
    TN_BCK_YKAMAE1=0x62,
    TN_BCK_YKIDUKU1=0x63,
    TN_BCK_YKIHON1=0x64,
    TN_BCK_YKYORO1=0x65,
    TN_BCK_YMAHI1=0x66,
    TN_BCK_YWALK1=0x67,
    
    /* BMDM */
    TN_BMD_TN_KABUTO1=0x6A,
    TN_BMD_TN_KABUTO2=0x6B,
    TN_BMD_TN_MAIN=0x6C,
    TN_BMD_TN_TATE1=0x6D,
    TN_BMD_TN_YOROI1=0x6E,
    
    /* BRK */
    TN_BRK_TN_KABUTO1=0x71,
    TN_BRK_TN_KABUTO2=0x72,
    TN_BRK_TN_MAIN=0x73,
    TN_BRK_TN_TATE1=0x74,
    TN_BRK_TN_YOROI1=0x75,
};

#endif /* RES_TN_H */
