#ifndef RES_AM2_H
#define RES_AM2_H

#include "global.h" // IWYU pragma: keep

enum AM2_RES_FILE_ID { // IDs and indexes are synced
    /* BCK */
    AM2_BCK_BURUBURU=0x6,
    AM2_BCK_DAMAGE=0x7,
    AM2_BCK_DEAD1=0x8,
    AM2_BCK_DEAD2=0x9,
    AM2_BCK_DEAD3=0xA,
    AM2_BCK_JUMP=0xB,
    AM2_BCK_MAHI=0xC,
    AM2_BCK_SLEEP=0xD,
    AM2_BCK_START=0xE,
    AM2_BCK_WAIT=0xF,
    
    /* BDLM */
    AM2_BDL_AM2=0x12,
    
    /* BRK */
    AM2_BRK_AM2=0x15,
    
    /* BTK */
    AM2_BTK_AM2=0x18,
};

#endif /* RES_AM2_H */
