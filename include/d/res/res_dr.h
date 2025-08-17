#ifndef RES_DR_H
#define RES_DR_H

#include "global.h" // IWYU pragma: keep

enum DR_RES_FILE_ID { // IDs and indexes are synced
    /* BAS */
    DR_BAS_ABARE1=0x5,
    DR_BAS_ABARE2=0x6,
    DR_BAS_AKUBI1=0x7,
    DR_BAS_BIKU1=0x8,
    
    /* BCK */
    DR_BCK_DR_ABARE1=0xB,
    DR_BCK_DR_ABARE2=0xC,
    DR_BCK_DR_AKUBI1=0xD,
    DR_BCK_DR_BIKU1=0xE,
    DR_BCK_DR_HO1=0xF,
    DR_BCK_DR_WAIT1=0x10,
    
    /* BMD */
    DR_BMD_DR1=0x13,
};

#endif /* RES_DR_H */
