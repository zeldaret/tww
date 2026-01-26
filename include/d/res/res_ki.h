#ifndef RES_KI_H
#define RES_KI_H

#include "global.h" // IWYU pragma: keep

enum KI_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    KI_BAS_ATTACK1=0x7,
    KI_BAS_BITA1=0x8,
    KI_BAS_DAMAGE1=0x9,
    KI_BAS_FLY1=0xA,
    KI_BAS_FLY2=0xB,
    KI_BAS_WAIT1=0xC,
    
    /* BCK */
    KI_BCK_ATTACK1=0xF,
    KI_BCK_BITA1=0x10,
    KI_BCK_DAMAGE1=0x11,
    KI_BCK_FLY1=0x12,
    KI_BCK_FLY2=0x13,
    KI_BCK_WAIT1=0x14,
    
    /* BDLM */
    KI_BDL_FK=0x17,
    KI_BDL_KI=0x18,
    
    /* BTK */
    KI_BTK_FK=0x1B,
    
    /* BTP */
    KI_BTP_AKE1=0x1E,
    KI_BTP_GURU1=0x1F,
    KI_BTP_METOJI1=0x20,
    KI_BTP_TOJI1=0x21,
};

#endif /* RES_KI_H */
