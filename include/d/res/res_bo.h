#ifndef RES_BO_H
#define RES_BO_H

#include "global.h" // IWYU pragma: keep

enum BO_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    BO_BCK_ATTACK1=0x5,
    BO_BCK_BOU1=0x6,
    BO_BCK_DAMAGE1=0x7,
    BO_BCK_DERU_S1=0x8,
    BO_BCK_DERU_U1=0x9,
    BO_BCK_FUKKATU1=0xA,
    BO_BCK_HAKIDASU1=0xB,
    BO_BCK_HANEKAERI1=0xC,
    BO_BCK_KAMU1=0xD,
    BO_BCK_KARERU1=0xE,
    BO_BCK_KUSIZASI1=0xF,
    BO_BCK_MODORU_S1=0x10,
    BO_BCK_MODORU_U1=0x11,
    BO_BCK_PUNCH1=0x12,
    BO_BCK_SIORERU1=0x13,
    BO_BCK_TABERU1=0x14,
    BO_BCK_WAIT_L1=0x15,
    BO_BCK_WAIT_R1=0x16,
    
    /* BDLM */
    BO_BDL_BO_SITA1=0x19,
    BO_BDL_BO_UE1=0x1A,
    
    /* BRK */
    BO_BRK_TO_BOKO1=0x1D,
};

#endif /* RES_BO_H */
