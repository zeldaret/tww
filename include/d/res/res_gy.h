#ifndef RES_GY_H
#define RES_GY_H

#include "global.h" // IWYU pragma: keep

enum GY_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    GY_BCK_ATTACK1=0x4,
    GY_BCK_ATTACK2=0x5,
    GY_BCK_BUTUKARU1=0x6,
    GY_BCK_DAMAGE1=0x7,
    GY_BCK_DEATH1=0x8,
    GY_BCK_DEATH2=0x9,
    GY_BCK_JUMP1=0xA,
    GY_BCK_SWIM1=0xB,
    GY_BCK_SWIM2=0xC,
    
    /* BMD */
    GY_BMD_GY=0xF,
};

#endif /* RES_GY_H */
